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
#અન્તર્ભાવ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_EMSCRIPTEN

#અન્તર્ભાવ <emscripten/emscripten.h>
#અન્તર્ભાવ <emscripten/html5.h>
#અન્તર્ભાવ <emscripten/threading.h>

#અન્તર્ભાવ "SDL_emscriptenmouse.h"
#અન્તર્ભાવ "SDL_emscriptenvideo.h"

#અન્તર્ભાવ "../SDL_video_c.h"
#અન્તર્ભાવ "../../events/SDL_mouse_c.h"

// older Emscriptens don't have this, but we need to for wasm64 compatibility.
#ifndef MAIN_THREAD_EM_ASM_PTR
    #ifdef __wasm64__
        #error You need to upgrade your Emscripten compiler to support wasm64
    #નહીંતર
        #define MAIN_THREAD_EM_ASM_PTR MAIN_THREAD_EM_ASM_INT
    #endif
#endif

સ્થિર SDL_Cursor *Emscripten_CreateCursorFromString(અચલ અક્ષર *cursor_str, bool is_custom)
{
    SDL_CursorData *curdata;
    SDL_Cursor *cursor = SDL_calloc(1, કદ(SDL_Cursor));
    જો (cursor) {
        curdata = (SDL_CursorData *)SDL_calloc(1, કદ(*curdata));
        જો (!curdata) {
            SDL_free(cursor);
            પાછા ખાલી;
        }

        curdata->system_cursor = cursor_str;
        curdata->is_custom = is_custom;
        cursor->internal = curdata;
    }

    પાછા cursor;
}

સ્થિર SDL_Cursor *Emscripten_CreateDefaultCursor(શૂન્ય)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    અચલ અક્ષર *cursor_name = SDL_GetCSSCursorName(id, ખાલી);
    પાછા Emscripten_CreateCursorFromString(cursor_name, false);
}

EM_JS_DEPS(sdlmouse, "$stringToUTF8,$UTF8ToString");

સ્થિર SDL_Cursor *Emscripten_CreateCursor(SDL_Surface *surface, પૂર્ણાંક hot_x, પૂર્ણાંક hot_y)
{
    અચલ અક્ષર *cursor_url = ખાલી;
    SDL_Surface *conv_surf;

    conv_surf = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);

    જો (!conv_surf) {
        પાછા ખાલી;
    }

    /* *INDENT-OFF* */ // clang-format off
    cursor_url = (અચલ અક્ષર *)MAIN_THREAD_EM_ASM_PTR({
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

        પાછા urlBuf;
    }, surface->w, surface->h, hot_x, hot_y, conv_surf->pixels);
    /* *INDENT-ON* */ // clang-format on

    SDL_DestroySurface(conv_surf);

    પાછા Emscripten_CreateCursorFromString(cursor_url, true);
}

સ્થિર SDL_Cursor *Emscripten_CreateSystemCursor(SDL_SystemCursor id)
{
    અચલ અક્ષર *cursor_name = SDL_GetCSSCursorName(id, ખાલી);

    પાછા Emscripten_CreateCursorFromString(cursor_name, false);
}

સ્થિર શૂન્ય Emscripten_FreeCursor(SDL_Cursor *cursor)
{
    SDL_CursorData *curdata;
    જો (cursor) {
        curdata = cursor->internal;

        જો (curdata) {
            જો (curdata->is_custom) {
                SDL_free((અક્ષર *)curdata->system_cursor);
            }
            SDL_free(cursor->internal);
        }

        SDL_free(cursor);
    }
}

સ્થિર bool Emscripten_ShowCursor(SDL_Cursor *cursor)
{
    SDL_CursorData *curdata;
    જો (SDL_GetMouseFocus() != ખાલી) {
        જો (cursor && cursor->internal) {
            curdata = cursor->internal;

            જો (curdata->system_cursor) {
                /* *INDENT-OFF* */ // clang-format off
                MAIN_THREAD_EM_ASM({
                    જો (Module['canvas']) {
                        Module['canvas'].style['cursor'] = UTF8ToString($0);
                    }
                }, curdata->system_cursor);
                /* *INDENT-ON* */ // clang-format on
            }
        } નહીંતર {
            /* *INDENT-OFF* */ // clang-format off
            MAIN_THREAD_EM_ASM(
                જો (Module['canvas']) {
                    Module['canvas'].style['cursor'] = 'none';
                }
            );
            /* *INDENT-ON* */ // clang-format on
        }
    }
    પાછા true;
}

સ્થિર bool Emscripten_SetRelativeMouseMode(bool enabled)
{
    SDL_Window *window;
    SDL_WindowData *window_data;

    // TODO: pointer lock isn't actually enabled yet
    જો (enabled) {
        window = SDL_GetMouseFocus();
        જો (!window) {
            પાછા false;
        }

        window_data = window->internal;

        જો (emscripten_request_pointerlock(window_data->canvas_id, 1) >= EMSCRIPTEN_RESULT_SUCCESS) {
            પાછા true;
        }
    } નહીંતર {
        જો (emscripten_exit_pointerlock() >= EMSCRIPTEN_RESULT_SUCCESS) {
            પાછા true;
        }
    }
    પાછા false;
}

સ્થિર SDL_MouseButtonFlags Emscripten_GetGlobalMouseState(દશાંશ *x, દશાંશ *y)
{
    *x = MAIN_THREAD_EM_ASM_DOUBLE({
        પાછા Module['SDL3']['mouse_x'];
    });
    *y = MAIN_THREAD_EM_ASM_DOUBLE({
        પાછા Module['SDL3']['mouse_y'];
    });
    SDL_MouseButtonFlags flags = 0;
    માટે (પૂર્ણાંક i = 0; i < 5; ++i) {
        અચલ bool button_down = MAIN_THREAD_EM_ASM_INT({
            પાછા Module['SDL3']['mouse_buttons'][$0];
        }, i);
        જો (button_down) {
            flags |= 1 << i;
        }
    }
    પાછા flags;
}

શૂન્ય Emscripten_InitMouse(શૂન્ય)
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
        માટે (var i = 0; i < 5; ++i) {
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
            જો (0 <= e.button && e.button < SDL3['mouse_buttons'].length) {
                SDL3['mouse_buttons'][e.button] = true;
            }
        });
        document.addEventListener('mouseup', function(e) {
            // Reacquire from object in case it changed for some reason
            var SDL3 = Module['SDL3'];
            જો (0 <= e.button && e.button < SDL3['mouse_buttons'].length) {
                SDL3['mouse_buttons'][e.button] = false;
            }
        });
    });
    mouse->GetGlobalMouseState = Emscripten_GetGlobalMouseState;

    SDL_SetDefaultCursor(Emscripten_CreateDefaultCursor());
}

શૂન્ય Emscripten_QuitMouse(શૂન્ય)
{
}

#endif // SDL_VIDEO_DRIVER_EMSCRIPTEN
