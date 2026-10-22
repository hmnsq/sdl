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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_EMSCRIPTEN

#ଅନ୍ତର୍ଭାଵ <emscripten/emscripten.h>
#ଅନ୍ତର୍ଭାଵ <emscripten/html5.h>
#ଅନ୍ତର୍ଭାଵ <emscripten/threading.h>

#ଅନ୍ତର୍ଭାଵ "SDL_emscriptenmouse.h"
#ଅନ୍ତର୍ଭାଵ "SDL_emscriptenvideo.h"

#ଅନ୍ତର୍ଭାଵ "../SDL_video_c.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_mouse_c.h"

// older Emscriptens don't have this, but we need to for wasm64 compatibility.
#ifndef MAIN_THREAD_EM_ASM_PTR
    #ifdef __wasm64__
        #error You need to upgrade your Emscripten compiler to support wasm64
    #ଅନ୍ୟଥା
        #define MAIN_THREAD_EM_ASM_PTR MAIN_THREAD_EM_ASM_INT
    #endif
#endif

ସ୍ଥିର SDL_Cursor *Emscripten_CreateCursorFromString(ଅଚଳ ଅକ୍ଷର *cursor_str, bool is_custom)
{
    SDL_CursorData *curdata;
    SDL_Cursor *cursor = SDL_calloc(1, ଆକାର(SDL_Cursor));
    ଯଦି (cursor) {
        curdata = (SDL_CursorData *)SDL_calloc(1, ଆକାର(*curdata));
        ଯଦି (!curdata) {
            SDL_free(cursor);
            ଫେରନ୍ତୁ ଖାଲି;
        }

        curdata->system_cursor = cursor_str;
        curdata->is_custom = is_custom;
        cursor->internal = curdata;
    }

    ଫେରନ୍ତୁ cursor;
}

ସ୍ଥିର SDL_Cursor *Emscripten_CreateDefaultCursor(ଶୂନ୍ୟ)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    ଅଚଳ ଅକ୍ଷର *cursor_name = SDL_GetCSSCursorName(id, ଖାଲି);
    ଫେରନ୍ତୁ Emscripten_CreateCursorFromString(cursor_name, false);
}

EM_JS_DEPS(sdlmouse, "$stringToUTF8,$UTF8ToString");

ସ୍ଥିର SDL_Cursor *Emscripten_CreateCursor(SDL_Surface *surface, ପୂର୍ଣ୍ଣସଂଖ୍ୟା hot_x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା hot_y)
{
    ଅଚଳ ଅକ୍ଷର *cursor_url = ଖାଲି;
    SDL_Surface *conv_surf;

    conv_surf = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);

    ଯଦି (!conv_surf) {
        ଫେରନ୍ତୁ ଖାଲି;
    }

    /* *INDENT-OFF* */ // clang-format off
    cursor_url = (ଅଚଳ ଅକ୍ଷର *)MAIN_THREAD_EM_ASM_PTR({
        var w = $0;
        var h = $1;
        var hot_x = $2;
        var hot_y = $3;
        var pixels = $4;

        var canvas = document.createElement("canvas");
        canvas.width = w;
        canvas.height = h;

        var ctx = canvas.getContext("2d");

        var image = ctx.createImageData(w, h);
        var data = image.data;
        var src = pixels / 4;

        var data32 = new Int32Array(data.buffer);
        data32.set(HEAP32.subarray(src, src + data32.length));

        ctx.putImageData(image, 0, 0);
        var url = hot_x === 0 && hot_y === 0
            ? "url(" + canvas.toDataURL() + "), auto"
            : "url(" + canvas.toDataURL() + ") " + hot_x + " " + hot_y + ", auto";

        var urlBuf = _SDL_malloc(url.length + 1);
        stringToUTF8(url, urlBuf, url.length + 1);

        ଫେରନ୍ତୁ urlBuf;
    }, surface->w, surface->h, hot_x, hot_y, conv_surf->pixels);
    /* *INDENT-ON* */ // clang-format on

    SDL_DestroySurface(conv_surf);

    ଫେରନ୍ତୁ Emscripten_CreateCursorFromString(cursor_url, true);
}

ସ୍ଥିର SDL_Cursor *Emscripten_CreateSystemCursor(SDL_SystemCursor id)
{
    ଅଚଳ ଅକ୍ଷର *cursor_name = SDL_GetCSSCursorName(id, ଖାଲି);

    ଫେରନ୍ତୁ Emscripten_CreateCursorFromString(cursor_name, false);
}

ସ୍ଥିର ଶୂନ୍ୟ Emscripten_FreeCursor(SDL_Cursor *cursor)
{
    SDL_CursorData *curdata;
    ଯଦି (cursor) {
        curdata = cursor->internal;

        ଯଦି (curdata) {
            ଯଦି (curdata->is_custom) {
                SDL_free((ଅକ୍ଷର *)curdata->system_cursor);
            }
            SDL_free(cursor->internal);
        }

        SDL_free(cursor);
    }
}

ସ୍ଥିର bool Emscripten_ShowCursor(SDL_Cursor *cursor)
{
    SDL_CursorData *curdata;
    ଯଦି (SDL_GetMouseFocus() != ଖାଲି) {
        ଯଦି (cursor && cursor->internal) {
            curdata = cursor->internal;

            ଯଦି (curdata->system_cursor) {
                /* *INDENT-OFF* */ // clang-format off
                MAIN_THREAD_EM_ASM({
                    ଯଦି (Module['canvas']) {
                        Module['canvas'].style['cursor'] = UTF8ToString($0);
                    }
                }, curdata->system_cursor);
                /* *INDENT-ON* */ // clang-format on
            }
        } ଅନ୍ୟଥା {
            /* *INDENT-OFF* */ // clang-format off
            MAIN_THREAD_EM_ASM(
                ଯଦି (Module['canvas']) {
                    Module['canvas'].style['cursor'] = 'none';
                }
            );
            /* *INDENT-ON* */ // clang-format on
        }
    }
    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର bool Emscripten_SetRelativeMouseMode(bool enabled)
{
    SDL_Window *window;
    SDL_WindowData *window_data;

    // TODO: pointer lock isn't actually enabled yet
    ଯଦି (enabled) {
        window = SDL_GetMouseFocus();
        ଯଦି (!window) {
            ଫେରନ୍ତୁ false;
        }

        window_data = window->internal;

        ଯଦି (emscripten_request_pointerlock(window_data->canvas_id, 1) >= EMSCRIPTEN_RESULT_SUCCESS) {
            ଫେରନ୍ତୁ true;
        }
    } ଅନ୍ୟଥା {
        ଯଦି (emscripten_exit_pointerlock() >= EMSCRIPTEN_RESULT_SUCCESS) {
            ଫେରନ୍ତୁ true;
        }
    }
    ଫେରନ୍ତୁ false;
}

ସ୍ଥିର SDL_MouseButtonFlags Emscripten_GetGlobalMouseState(ଦଶମିକ *x, ଦଶମିକ *y)
{
    *x = MAIN_THREAD_EM_ASM_DOUBLE({
        ଫେରନ୍ତୁ Module['SDL3']['mouse_x'];
    });
    *y = MAIN_THREAD_EM_ASM_DOUBLE({
        ଫେରନ୍ତୁ Module['SDL3']['mouse_y'];
    });
    SDL_MouseButtonFlags flags = 0;
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < 5; ++i) {
        ଅଚଳ bool button_down = MAIN_THREAD_EM_ASM_INT({
            ଫେରନ୍ତୁ Module['SDL3']['mouse_buttons'][$0];
        }, i);
        ଯଦି (button_down) {
            flags |= 1 << i;
        }
    }
    ଫେରନ୍ତୁ flags;
}

ଶୂନ୍ୟ Emscripten_InitMouse(ଶୂନ୍ୟ)
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
        ପାଇଁ (var i = 0; i < 5; ++i) {
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
            ଯଦି (0 <= e.button && e.button < SDL3['mouse_buttons'].length) {
                SDL3['mouse_buttons'][e.button] = true;
            }
        });
        document.addEventListener('mouseup', function(e) {
            // Reacquire from object in case it changed for some reason
            var SDL3 = Module['SDL3'];
            ଯଦି (0 <= e.button && e.button < SDL3['mouse_buttons'].length) {
                SDL3['mouse_buttons'][e.button] = false;
            }
        });
    });
    mouse->GetGlobalMouseState = Emscripten_GetGlobalMouseState;

    SDL_SetDefaultCursor(Emscripten_CreateDefaultCursor());
}

ଶୂନ୍ୟ Emscripten_QuitMouse(ଶୂନ୍ୟ)
{
}

#endif // SDL_VIDEO_DRIVER_EMSCRIPTEN
