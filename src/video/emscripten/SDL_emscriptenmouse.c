/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2026 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/
#অন্তর্ভাব "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_EMSCRIPTEN

#অন্তর্ভাব <emscripten/emscripten.h>
#অন্তর্ভাব <emscripten/html5.h>
#অন্তর্ভাব <emscripten/threading.h>

#অন্তর্ভাব "SDL_emscriptenmouse.h"
#অন্তর্ভাব "SDL_emscriptenvideo.h"

#অন্তর্ভাব "../SDL_video_c.h"
#অন্তর্ভাব "../../events/SDL_mouse_c.h"

// older Emscriptens don't have this, but we need to for wasm64 compatibility.
#ifndef MAIN_THREAD_EM_ASM_PTR
    #ifdef __wasm64__
        #error You need to upgrade your Emscripten compiler to support wasm64
    #অন্যথা
        #define MAIN_THREAD_EM_ASM_PTR MAIN_THREAD_EM_ASM_INT
    #endif
#endif

স্থির SDL_Cursor *Emscripten_CreateCursorFromString(ধ্রুবক অক্ষর *cursor_str, bool is_custom)
{
    SDL_Cursor_তথ্য *curdata;
    SDL_Cursor *cursor = SDL_calloc(1, আকার(SDL_Cursor));
    যদি (cursor) {
        curdata = (SDL_Cursor_তথ্য *)SDL_calloc(1, আকার(*curdata));
        যদি (!curdata) {
            SDL_free(cursor);
            ফেরত ফাঁকা;
        }

        curdata->system_cursor = cursor_str;
        curdata->is_custom = is_custom;
        cursor->internal = curdata;
    }

    ফেরত cursor;
}

স্থির SDL_Cursor *Emscripten_CreateDefaultCursor(শূন্য)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    ধ্রুবক অক্ষর *cursor_name = SDL_GetCSSCursorName(id, ফাঁকা);
    ফেরত Emscripten_CreateCursorFromString(cursor_name, false);
}

EM_JS_DEPS(sdlmouse, "$stringToUTF8,$UTF8ToString");

স্থির SDL_Cursor *Emscripten_CreateCursor(SDL_Surface *surface, পূর্ণসংখ্যা hot_x, পূর্ণসংখ্যা hot_y)
{
    ধ্রুবক অক্ষর *cursor_url = ফাঁকা;
    SDL_Surface *conv_surf;

    conv_surf = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);

    যদি (!conv_surf) {
        ফেরত ফাঁকা;
    }

    /* *INDENT-OFF* */ // clang-format off
    cursor_url = (ধ্রুবক অক্ষর *)MAIN_THREAD_EM_ASM_PTR({
        var w = $0;
        var h = $1;
        var hot_x = $2;
        var hot_y = $3;
        var pixels = $4;

        var canvas = document.createElement("canvas");
        canvas.width = w;
        canvas.height = h;

        var ctx = canvas.getContext("2d");

        var image = ctx.create_Image_তথ্য(w, h);
        var তথ্য = image.তথ্য;
        var src = pixels / 4;

        var data32 = new Int32Array(তথ্য.বাফার_2);
        data32.set(HEAP32.subarray(src, src + data32.দৈর্ঘ্য));

        ctx.put_Image_তথ্য(image, 0, 0);
        var url = hot_x === 0 && hot_y === 0
            ? "url(" + canvas.to_তথ্য_URL() + "), auto"
            : "url(" + canvas.to_তথ্য_URL() + ") " + hot_x + " " + hot_y + ", auto";

        var urlBuf = _SDL_malloc(url.দৈর্ঘ্য + 1);
        stringToUTF8(url, urlBuf, url.দৈর্ঘ্য + 1);

        ফেরত urlBuf;
    }, surface->w, surface->h, hot_x, hot_y, conv_surf->pixels);
    /* *INDENT-ON* */ // clang-format on

    SDL_DestroySurface(conv_surf);

    ফেরত Emscripten_CreateCursorFromString(cursor_url, true);
}

স্থির SDL_Cursor *Emscripten_CreateSystemCursor(SDL_SystemCursor id)
{
    ধ্রুবক অক্ষর *cursor_name = SDL_GetCSSCursorName(id, ফাঁকা);

    ফেরত Emscripten_CreateCursorFromString(cursor_name, false);
}

স্থির শূন্য Emscripten_FreeCursor(SDL_Cursor *cursor)
{
    SDL_Cursor_তথ্য *curdata;
    যদি (cursor) {
        curdata = cursor->internal;

        যদি (curdata) {
            যদি (curdata->is_custom) {
                SDL_free((অক্ষর *)curdata->system_cursor);
            }
            SDL_free(cursor->internal);
        }

        SDL_free(cursor);
    }
}

স্থির bool Emscripten_ShowCursor(SDL_Cursor *cursor)
{
    SDL_Cursor_তথ্য *curdata;
    যদি (SDL_GetMouseFocus() != ফাঁকা) {
        যদি (cursor && cursor->internal) {
            curdata = cursor->internal;

            যদি (curdata->system_cursor) {
                /* *INDENT-OFF* */ // clang-format off
                MAIN_THREAD_EM_ASM({
                    যদি (Module['canvas']) {
                        Module['canvas'].style['cursor'] = UTF8ToString($0);
                    }
                }, curdata->system_cursor);
                /* *INDENT-ON* */ // clang-format on
            }
        } অন্যথা {
            /* *INDENT-OFF* */ // clang-format off
            MAIN_THREAD_EM_ASM(
                যদি (Module['canvas']) {
                    Module['canvas'].style['cursor'] = 'none';
                }
            );
            /* *INDENT-ON* */ // clang-format on
        }
    }
    ফেরত true;
}

স্থির bool Emscripten_SetRelativeMouseMode(bool enabled)
{
    SDL_Window *window;
    SDL_Window_তথ্য *window_তথ্য_2;

    // TODO: pointer lock isn't actually enabled yet
    যদি (enabled) {
        window = SDL_GetMouseFocus();
        যদি (!window) {
            ফেরত false;
        }

        window_তথ্য_2 = window->internal;

        যদি (emscripten_request_pointerlock(window_তথ্য_2->canvas_id, 1) >= EMSCRIPTEN_ফলাফল_SUCCESS) {
            ফেরত true;
        }
    } অন্যথা {
        যদি (emscripten_exit_pointerlock() >= EMSCRIPTEN_ফলাফল_SUCCESS) {
            ফেরত true;
        }
    }
    ফেরত false;
}

স্থির SDL_MouseButtonFlags Emscripten_GetGlobalMouseState(দশমিক *x, দশমিক *y)
{
    *x = MAIN_THREAD_EM_ASM_DOUBLE({
        ফেরত Module['SDL3']['mouse_x'];
    });
    *y = MAIN_THREAD_EM_ASM_DOUBLE({
        ফেরত Module['SDL3']['mouse_y'];
    });
    SDL_MouseButtonFlags flags = 0;
    জন্য (পূর্ণসংখ্যা i = 0; i < 5; ++i) {
        ধ্রুবক bool button_down = MAIN_THREAD_EM_ASM_INT({
            ফেরত Module['SDL3']['mouse_buttons'][$0];
        }, i);
        যদি (button_down) {
            flags |= 1 << i;
        }
    }
    ফেরত flags;
}

শূন্য Emscripten_InitMouse(শূন্য)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    mouse->CreateCursor = Emscripten_CreateCursor;
    mouse->ShowCursor = Emscripten_ShowCursor;
    mouse->FreeCursor = Emscripten_FreeCursor;
    mouse->CreateSystemCursor = Emscripten_CreateSystemCursor;
    mouse->SetRelativeMouseMode = Emscripten_SetRelativeMouseMode;

    // Add event listeners to track mouse events on the document
    MAIN_THREAD_EM_ASM({
        var SDL3 = Module['SDL3'];
        SDL3['mouse_x'] = 0;
        SDL3['mouse_y'] = 0;
        /*
            Based on https://developer.mozilla.org/en-US/docs/Web/API/MouseEvent/button
            Possible value for button in the event object is [0, 5)
            NOTE: Some browsers do not allow handling the forwards and backwards buttons
        */
        SDL3['mouse_buttons'] = [];
        জন্য (var i = 0; i < 5; ++i) {
            SDL3['mouse_buttons'][i] = false;
        }
        document.addEventListener('mousemove', function(e) {
            // Reacquire from object in case it changed for some reason
            var SDL3 = Module['SDL3'];
            SDL3['mouse_x'] = e.clientX;
            SDL3['mouse_y'] = e.clientY;
        });
        document.addEventListener('mousedown', function(e) {
            // Reacquire from object in case it changed for some reason
            var SDL3 = Module['SDL3'];
            যদি (0 <= e.button && e.button < SDL3['mouse_buttons'].দৈর্ঘ্য) {
                SDL3['mouse_buttons'][e.button] = true;
            }
        });
        document.addEventListener('mouseup', function(e) {
            // Reacquire from object in case it changed for some reason
            var SDL3 = Module['SDL3'];
            যদি (0 <= e.button && e.button < SDL3['mouse_buttons'].দৈর্ঘ্য) {
                SDL3['mouse_buttons'][e.button] = false;
            }
        });
    });
    mouse->GetGlobalMouseState = Emscripten_GetGlobalMouseState;

    SDL_SetDefaultCursor(Emscripten_CreateDefaultCursor());
}

শূন্য Emscripten_QuitMouse(শূন্য)
{
}

#endif // SDL_VIDEO_DRIVER_EMSCRIPTEN
