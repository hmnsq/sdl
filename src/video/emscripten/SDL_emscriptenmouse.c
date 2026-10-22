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
#அந்தர்பாவ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_EMSCRIPTEN

#அந்தர்பாவ <emscripten/emscripten.h>
#அந்தர்பாவ <emscripten/html5.h>
#அந்தர்பாவ <emscripten/threading.h>

#அந்தர்பாவ "SDL_emscriptenmouse.h"
#அந்தர்பாவ "SDL_emscriptenvideo.h"

#அந்தர்பாவ "../SDL_video_c.h"
#அந்தர்பாவ "../../events/SDL_mouse_c.h"

// older Emscriptens don't have this, but we need to for wasm64 compatibility.
#ifndef MAIN_THREAD_EM_ASM_PTR
    #ifdef __wasm64__
        #error You need to upgrade your Emscripten compiler to support wasm64
    #இல்லையெனில்
        #define MAIN_THREAD_EM_ASM_PTR MAIN_THREAD_EM_ASM_INT
    #endif
#endif

நிலையான SDL_Cursor *Emscripten_CreateCursorFromString(மாறிலி எழுத்து *cursor_str, bool is_custom)
{
    SDL_CursorData *curdata;
    SDL_Cursor *cursor = SDL_calloc(1, அளவு(SDL_Cursor));
    எனில் (cursor) {
        curdata = (SDL_CursorData *)SDL_calloc(1, அளவு(*curdata));
        எனில் (!curdata) {
            SDL_free(cursor);
            திரும்பு வெற்று;
        }

        curdata->system_cursor = cursor_str;
        curdata->is_custom = is_custom;
        cursor->internal = curdata;
    }

    திரும்பு cursor;
}

நிலையான SDL_Cursor *Emscripten_CreateDefaultCursor(வெறுமை)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    மாறிலி எழுத்து *cursor_name = SDL_GetCSSCursorName(id, வெற்று);
    திரும்பு Emscripten_CreateCursorFromString(cursor_name, false);
}

EM_JS_DEPS(sdlmouse, "$stringToUTF8,$UTF8ToString");

நிலையான SDL_Cursor *Emscripten_CreateCursor(SDL_Surface *surface, முழு hot_x, முழு hot_y)
{
    மாறிலி எழுத்து *cursor_url = வெற்று;
    SDL_Surface *conv_surf;

    conv_surf = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);

    எனில் (!conv_surf) {
        திரும்பு வெற்று;
    }

    /* *INDENT-OFF* */ // clang-format off
    cursor_url = (மாறிலி எழுத்து *)MAIN_THREAD_EM_ASM_PTR({
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

        திரும்பு urlBuf;
    }, surface->w, surface->h, hot_x, hot_y, conv_surf->pixels);
    /* *INDENT-ON* */ // clang-format on

    SDL_DestroySurface(conv_surf);

    திரும்பு Emscripten_CreateCursorFromString(cursor_url, true);
}

நிலையான SDL_Cursor *Emscripten_CreateSystemCursor(SDL_SystemCursor id)
{
    மாறிலி எழுத்து *cursor_name = SDL_GetCSSCursorName(id, வெற்று);

    திரும்பு Emscripten_CreateCursorFromString(cursor_name, false);
}

நிலையான வெறுமை Emscripten_FreeCursor(SDL_Cursor *cursor)
{
    SDL_CursorData *curdata;
    எனில் (cursor) {
        curdata = cursor->internal;

        எனில் (curdata) {
            எனில் (curdata->is_custom) {
                SDL_free((எழுத்து *)curdata->system_cursor);
            }
            SDL_free(cursor->internal);
        }

        SDL_free(cursor);
    }
}

நிலையான bool Emscripten_ShowCursor(SDL_Cursor *cursor)
{
    SDL_CursorData *curdata;
    எனில் (SDL_GetMouseFocus() != வெற்று) {
        எனில் (cursor && cursor->internal) {
            curdata = cursor->internal;

            எனில் (curdata->system_cursor) {
                /* *INDENT-OFF* */ // clang-format off
                MAIN_THREAD_EM_ASM({
                    எனில் (Module['canvas']) {
                        Module['canvas'].style['cursor'] = UTF8ToString($0);
                    }
                }, curdata->system_cursor);
                /* *INDENT-ON* */ // clang-format on
            }
        } இல்லையெனில் {
            /* *INDENT-OFF* */ // clang-format off
            MAIN_THREAD_EM_ASM(
                எனில் (Module['canvas']) {
                    Module['canvas'].style['cursor'] = 'none';
                }
            );
            /* *INDENT-ON* */ // clang-format on
        }
    }
    திரும்பு true;
}

நிலையான bool Emscripten_SetRelativeMouseMode(bool enabled)
{
    SDL_Window *window;
    SDL_WindowData *window_data;

    // TODO: pointer lock isn't actually enabled yet
    எனில் (enabled) {
        window = SDL_GetMouseFocus();
        எனில் (!window) {
            திரும்பு false;
        }

        window_data = window->internal;

        எனில் (emscripten_request_pointerlock(window_data->canvas_id, 1) >= EMSCRIPTEN_RESULT_SUCCESS) {
            திரும்பு true;
        }
    } இல்லையெனில் {
        எனில் (emscripten_exit_pointerlock() >= EMSCRIPTEN_RESULT_SUCCESS) {
            திரும்பு true;
        }
    }
    திரும்பு false;
}

நிலையான SDL_MouseButtonFlags Emscripten_GetGlobalMouseState(தசம *x, தசம *y)
{
    *x = MAIN_THREAD_EM_ASM_DOUBLE({
        திரும்பு Module['SDL3']['mouse_x'];
    });
    *y = MAIN_THREAD_EM_ASM_DOUBLE({
        திரும்பு Module['SDL3']['mouse_y'];
    });
    SDL_MouseButtonFlags flags = 0;
    க்கு (முழு i = 0; i < 5; ++i) {
        மாறிலி bool button_down = MAIN_THREAD_EM_ASM_INT({
            திரும்பு Module['SDL3']['mouse_buttons'][$0];
        }, i);
        எனில் (button_down) {
            flags |= 1 << i;
        }
    }
    திரும்பு flags;
}

வெறுமை Emscripten_InitMouse(வெறுமை)
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
        க்கு (var i = 0; i < 5; ++i) {
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
            எனில் (0 <= e.button && e.button < SDL3['mouse_buttons'].length) {
                SDL3['mouse_buttons'][e.button] = true;
            }
        });
        document.addEventListener('mouseup', function(e) {
            // Reacquire from object in case it changed for some reason
            var SDL3 = Module['SDL3'];
            எனில் (0 <= e.button && e.button < SDL3['mouse_buttons'].length) {
                SDL3['mouse_buttons'][e.button] = false;
            }
        });
    });
    mouse->GetGlobalMouseState = Emscripten_GetGlobalMouseState;

    SDL_SetDefaultCursor(Emscripten_CreateDefaultCursor());
}

வெறுமை Emscripten_QuitMouse(வெறுமை)
{
}

#endif // SDL_VIDEO_DRIVER_EMSCRIPTEN
