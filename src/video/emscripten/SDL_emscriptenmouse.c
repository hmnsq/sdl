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
#ضمن "SDL_internal.h"

#اگر_تعریف_شده SDL_VIDEO_DRIVER_EMSCRIPTEN

#ضمن <emscripten/emscripten.h>
#ضمن <emscripten/html5.h>
#ضمن <emscripten/threading.h>

#ضمن "SDL_emscriptenmouse.h"
#ضمن "SDL_emscriptenvideo.h"

#ضمن "../SDL_video_c.h"
#ضمن "../../events/SDL_mouse_c.h"

// older Emscriptens don't have this, but we need to for wasm64 compatibility.
#اگر_تعریف_نشده MAIN_THREAD_EM_ASM_PTR
    #اگر_تعریف_شده __wasm64__
        #خطا You need مقصد upgrade your Emscripten compiler مقصد support wasm64
    #وإلا
        #تعریف_کن MAIN_THREAD_EM_ASM_PTR MAIN_THREAD_EM_ASM_INT
    #پایان_اگر
#پایان_اگر

ساكن SDL_Cursor *Emscripten_CreateCursorFromString(ثابت حرف *cursor_str, bool is_custom)
{
    SDL_Cursor_داده *curdata;
    SDL_Cursor *cursor = SDL_calloc(1, حجم(SDL_Cursor));
    إذا (cursor) {
        curdata = (SDL_Cursor_داده *)SDL_calloc(1, حجم(*curdata));
        إذا (!curdata) {
            SDL_free(cursor);
            أرجع عدم;
        }

        curdata->system_cursor = cursor_str;
        curdata->is_custom = is_custom;
        cursor->داخلی = curdata;
    }

    أرجع cursor;
}

ساكن SDL_Cursor *Emscripten_CreateDefaultCursor(فراغ)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    ثابت حرف *cursor_name = SDL_GetCSSCursorName(id, عدم);
    أرجع Emscripten_CreateCursorFromString(cursor_name, false);
}

EM_JS_DEPS(sdlmouse, "$stringToUTF8,$UTF8ToString");

ساكن SDL_Cursor *Emscripten_CreateCursor(SDL_Surface *surface, صحيح hot_x, صحيح hot_y)
{
    ثابت حرف *cursor_url = عدم;
    SDL_Surface *conv_surf;

    conv_surf = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);

    إذا (!conv_surf) {
        أرجع عدم;
    }

    /* *INDENT-OFF* */ // clang-format off
    cursor_url = (ثابت حرف *)MAIN_THREAD_EM_ASM_PTR({
        var w = $0;
        var h = $1;
        var hot_x = $2;
        var hot_y = $3;
        var pixels = $4;

        var canvas = document.createElement("canvas");
        canvas.عرض = w;
        canvas.ارتفاع = h;

        var ctx = canvas.getContext("2d");

        var image = ctx.create_Image_داده(w, h);
        var داده = image.داده;
        var src = pixels / 4;

        var data32 = new Int32Array(داده.میانگیر_2);
        data32.مجموعه(HEAP32.subarray(src, src + data32.درازی));

        ctx.put_Image_داده(image, 0, 0);
        var url = hot_x === 0 && hot_y === 0
            ? "url(" + canvas.مقصد_داده_URL() + "), auto"
            : "url(" + canvas.مقصد_داده_URL() + ") " + hot_x + " " + hot_y + ", auto";

        var urlBuf = _SDL_malloc(url.درازی + 1);
        string_مقصد_UTF8(url, urlBuf, url.درازی + 1);

        أرجع urlBuf;
    }, surface->w, surface->h, hot_x, hot_y, conv_surf->pixels);
    /* *INDENT-ON* */ // clang-format on

    SDL_DestroySurface(conv_surf);

    أرجع Emscripten_CreateCursorFromString(cursor_url, true);
}

ساكن SDL_Cursor *Emscripten_CreateSystemCursor(SDL_SystemCursor id)
{
    ثابت حرف *cursor_name = SDL_GetCSSCursorName(id, عدم);

    أرجع Emscripten_CreateCursorFromString(cursor_name, false);
}

ساكن فراغ Emscripten_FreeCursor(SDL_Cursor *cursor)
{
    SDL_Cursor_داده *curdata;
    إذا (cursor) {
        curdata = cursor->داخلی;

        إذا (curdata) {
            إذا (curdata->is_custom) {
                SDL_free((حرف *)curdata->system_cursor);
            }
            SDL_free(cursor->داخلی);
        }

        SDL_free(cursor);
    }
}

ساكن bool Emscripten_ShowCursor(SDL_Cursor *cursor)
{
    SDL_Cursor_داده *curdata;
    إذا (SDL_GetMouseFocus() != عدم) {
        إذا (cursor && cursor->داخلی) {
            curdata = cursor->داخلی;

            إذا (curdata->system_cursor) {
                /* *INDENT-OFF* */ // clang-format off
                MAIN_THREAD_EM_ASM({
                    إذا (Module['canvas']) {
                        Module['canvas'].style['cursor'] = UTF8_مقصد_String($0);
                    }
                }, curdata->system_cursor);
                /* *INDENT-ON* */ // clang-format on
            }
        } وإلا {
            /* *INDENT-OFF* */ // clang-format off
            MAIN_THREAD_EM_ASM(
                إذا (Module['canvas']) {
                    Module['canvas'].style['cursor'] = 'none';
                }
            );
            /* *INDENT-ON* */ // clang-format on
        }
    }
    أرجع true;
}

ساكن bool Emscripten_مجموعه_Relative_Mouse_نما(bool enabled)
{
    SDL_پنجره *پنجره;
    SDL_پنجره_داده *پنجره_داده_2;

    // TODO: pointer lock isn't actually enabled yet
    إذا (enabled) {
        پنجره = SDL_GetMouseFocus();
        إذا (!پنجره) {
            أرجع false;
        }

        پنجره_داده_2 = پنجره->داخلی;

        إذا (emscripten_request_pointerlock(پنجره_داده_2->canvas_id, 1) >= EMSCRIPTEN_نتیجه_SUCCESS) {
            أرجع true;
        }
    } وإلا {
        إذا (emscripten_exit_pointerlock() >= EMSCRIPTEN_نتیجه_SUCCESS) {
            أرجع true;
        }
    }
    أرجع false;
}

ساكن SDL_MouseButtonFlags Emscripten_GetGlobalMouseState(عائم *x, عائم *y)
{
    *x = MAIN_THREAD_EM_ASM_DOUBLE({
        أرجع Module['SDL3']['mouse_x'];
    });
    *y = MAIN_THREAD_EM_ASM_DOUBLE({
        أرجع Module['SDL3']['mouse_y'];
    });
    SDL_MouseButtonFlags flags = 0;
    لكل (صحيح i = 0; i < 5; ++i) {
        ثابت bool button_پایین = MAIN_THREAD_EM_ASM_INT({
            أرجع Module['SDL3']['mouse_buttons'][$0];
        }, i);
        إذا (button_پایین) {
            flags |= 1 << i;
        }
    }
    أرجع flags;
}

فراغ Emscripten_InitMouse(فراغ)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    mouse->CreateCursor = Emscripten_CreateCursor;
    mouse->ShowCursor = Emscripten_ShowCursor;
    mouse->FreeCursor = Emscripten_FreeCursor;
    mouse->CreateSystemCursor = Emscripten_CreateSystemCursor;
    mouse->مجموعه_Relative_Mouse_نما = Emscripten_مجموعه_Relative_Mouse_نما;

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
        لكل (var i = 0; i < 5; ++i) {
            SDL3['mouse_buttons'][i] = false;
        }
        document.جمع_کن_Event_Listener('mousemove', function(e) {
            // Reacquire from object in case it changed for some reason
            var SDL3 = Module['SDL3'];
            SDL3['mouse_x'] = e.clientX;
            SDL3['mouse_y'] = e.clientY;
        });
        document.جمع_کن_Event_Listener('mousedown', function(e) {
            // Reacquire from object in case it changed for some reason
            var SDL3 = Module['SDL3'];
            إذا (0 <= e.button && e.button < SDL3['mouse_buttons'].درازی) {
                SDL3['mouse_buttons'][e.button] = true;
            }
        });
        document.جمع_کن_Event_Listener('mouseup', function(e) {
            // Reacquire from object in case it changed for some reason
            var SDL3 = Module['SDL3'];
            إذا (0 <= e.button && e.button < SDL3['mouse_buttons'].درازی) {
                SDL3['mouse_buttons'][e.button] = false;
            }
        });
    });
    mouse->GetGlobalMouseState = Emscripten_GetGlobalMouseState;

    SDL_مجموعه_Default_Cursor(Emscripten_CreateDefaultCursor());
}

فراغ Emscripten_QuitMouse(فراغ)
{
}

#پایان_اگر // SDL_VIDEO_DRIVER_EMSCRIPTEN
