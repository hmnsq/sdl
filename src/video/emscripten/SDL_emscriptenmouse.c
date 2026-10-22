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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_EMSCRIPTEN

#ਅਨ੍ਤਰ੍ਭਾਵ <emscripten/emscripten.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <emscripten/html5.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <emscripten/threading.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_emscriptenmouse.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_emscriptenvideo.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_video_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_mouse_c.h"

// older Emscriptens don't have this, but we need to for wasm64 compatibility.
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MAIN_THREAD_EM_ASM_PTR
    #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __wasm64__
        #ਗਲਤੀ You need ਮੰਜ਼ਿਲ upgrade your Emscripten compiler ਮੰਜ਼ਿਲ support wasm64
    #ਨਹੀਂਤਾਂ
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAIN_THREAD_EM_ASM_PTR MAIN_THREAD_EM_ASM_INT
    #ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ

ਸਥਿਰ SDL_Cursor *Emscripten_CreateCursorFromString(ਅਚਲ ਅੱਖਰ *cursor_str, bool is_custom)
{
    SDL_Cursor_ਅੰਕੜੇ *curdata;
    SDL_Cursor *cursor = SDL_calloc(1, ਆਕਾਰ(SDL_Cursor));
    ਜੇ (cursor) {
        curdata = (SDL_Cursor_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(*curdata));
        ਜੇ (!curdata) {
            SDL_free(cursor);
            ਵਾਪਸ ਨਿਰਾ;
        }

        curdata->system_cursor = cursor_str;
        curdata->is_custom = is_custom;
        cursor->ਅੰਦਰੂਨੀ = curdata;
    }

    ਵਾਪਸ cursor;
}

ਸਥਿਰ SDL_Cursor *Emscripten_CreateDefaultCursor(ਖਾਲੀ)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    ਅਚਲ ਅੱਖਰ *cursor_name = SDL_GetCSSCursorName(id, ਨਿਰਾ);
    ਵਾਪਸ Emscripten_CreateCursorFromString(cursor_name, false);
}

EM_JS_DEPS(sdlmouse, "$stringToUTF8,$UTF8ToString");

ਸਥਿਰ SDL_Cursor *Emscripten_CreateCursor(SDL_Surface *surface, ਪੂਰਨ hot_x, ਪੂਰਨ hot_y)
{
    ਅਚਲ ਅੱਖਰ *cursor_url = ਨਿਰਾ;
    SDL_Surface *conv_surf;

    conv_surf = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);

    ਜੇ (!conv_surf) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    /* *INDENT-OFF* */ // clang-format off
    cursor_url = (ਅਚਲ ਅੱਖਰ *)MAIN_THREAD_EM_ASM_PTR({
        var w = $0;
        var h = $1;
        var hot_x = $2;
        var hot_y = $3;
        var pixels = $4;

        var canvas = document.createElement("canvas");
        canvas.ਚੌੜਾਈ = w;
        canvas.ਉਚਾਈ = h;

        var ctx = canvas.getContext("2d");

        var image = ctx.create_Image_ਅੰਕੜੇ(w, h);
        var ਅੰਕੜੇ = image.ਅੰਕੜੇ;
        var src = pixels / 4;

        var data32 = new Int32Array(ਅੰਕੜੇ.ਬਫਰ_2);
        data32.ਸੈੱਟ(HEAP32.subarray(src, src + data32.ਲੰਮਾਈ));

        ctx.put_Image_ਅੰਕੜੇ(image, 0, 0);
        var url = hot_x === 0 && hot_y === 0
            ? "url(" + canvas.ਮੰਜ਼ਿਲ_ਅੰਕੜੇ_URL() + "), auto"
            : "url(" + canvas.ਮੰਜ਼ਿਲ_ਅੰਕੜੇ_URL() + ") " + hot_x + " " + hot_y + ", auto";

        var urlBuf = _SDL_malloc(url.ਲੰਮਾਈ + 1);
        string_ਮੰਜ਼ਿਲ_UTF8(url, urlBuf, url.ਲੰਮਾਈ + 1);

        ਵਾਪਸ urlBuf;
    }, surface->w, surface->h, hot_x, hot_y, conv_surf->pixels);
    /* *INDENT-ON* */ // clang-format on

    SDL_DestroySurface(conv_surf);

    ਵਾਪਸ Emscripten_CreateCursorFromString(cursor_url, true);
}

ਸਥਿਰ SDL_Cursor *Emscripten_CreateSystemCursor(SDL_SystemCursor id)
{
    ਅਚਲ ਅੱਖਰ *cursor_name = SDL_GetCSSCursorName(id, ਨਿਰਾ);

    ਵਾਪਸ Emscripten_CreateCursorFromString(cursor_name, false);
}

ਸਥਿਰ ਖਾਲੀ Emscripten_FreeCursor(SDL_Cursor *cursor)
{
    SDL_Cursor_ਅੰਕੜੇ *curdata;
    ਜੇ (cursor) {
        curdata = cursor->ਅੰਦਰੂਨੀ;

        ਜੇ (curdata) {
            ਜੇ (curdata->is_custom) {
                SDL_free((ਅੱਖਰ *)curdata->system_cursor);
            }
            SDL_free(cursor->ਅੰਦਰੂਨੀ);
        }

        SDL_free(cursor);
    }
}

ਸਥਿਰ bool Emscripten_ShowCursor(SDL_Cursor *cursor)
{
    SDL_Cursor_ਅੰਕੜੇ *curdata;
    ਜੇ (SDL_GetMouseFocus() != ਨਿਰਾ) {
        ਜੇ (cursor && cursor->ਅੰਦਰੂਨੀ) {
            curdata = cursor->ਅੰਦਰੂਨੀ;

            ਜੇ (curdata->system_cursor) {
                /* *INDENT-OFF* */ // clang-format off
                MAIN_THREAD_EM_ASM({
                    ਜੇ (Module['canvas']) {
                        Module['canvas'].style['cursor'] = UTF8_ਮੰਜ਼ਿਲ_String($0);
                    }
                }, curdata->system_cursor);
                /* *INDENT-ON* */ // clang-format on
            }
        } ਨਹੀਂਤਾਂ {
            /* *INDENT-OFF* */ // clang-format off
            MAIN_THREAD_EM_ASM(
                ਜੇ (Module['canvas']) {
                    Module['canvas'].style['cursor'] = 'none';
                }
            );
            /* *INDENT-ON* */ // clang-format on
        }
    }
    ਵਾਪਸ true;
}

ਸਥਿਰ bool Emscripten_ਸੈੱਟ_Relative_Mouse_ਬਹੁਲਕ(bool enabled)
{
    SDL_ਖਿੜਕੀ *ਖਿੜਕੀ;
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ_ਅੰਕੜੇ_2;

    // TODO: pointer lock isn't actually enabled yet
    ਜੇ (enabled) {
        ਖਿੜਕੀ = SDL_GetMouseFocus();
        ਜੇ (!ਖਿੜਕੀ) {
            ਵਾਪਸ false;
        }

        ਖਿੜਕੀ_ਅੰਕੜੇ_2 = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

        ਜੇ (emscripten_request_pointerlock(ਖਿੜਕੀ_ਅੰਕੜੇ_2->canvas_id, 1) >= EMSCRIPTEN_ਨਤੀਜਾ_SUCCESS) {
            ਵਾਪਸ true;
        }
    } ਨਹੀਂਤਾਂ {
        ਜੇ (emscripten_exit_pointerlock() >= EMSCRIPTEN_ਨਤੀਜਾ_SUCCESS) {
            ਵਾਪਸ true;
        }
    }
    ਵਾਪਸ false;
}

ਸਥਿਰ SDL_MouseButtonFlags Emscripten_GetGlobalMouseState(ਦਸ਼ਮਲਵ *x, ਦਸ਼ਮਲਵ *y)
{
    *x = MAIN_THREAD_EM_ASM_DOUBLE({
        ਵਾਪਸ Module['SDL3']['mouse_x'];
    });
    *y = MAIN_THREAD_EM_ASM_DOUBLE({
        ਵਾਪਸ Module['SDL3']['mouse_y'];
    });
    SDL_MouseButtonFlags flags = 0;
    ਲਈ (ਪੂਰਨ i = 0; i < 5; ++i) {
        ਅਚਲ bool button_ਥੱਲੇ = MAIN_THREAD_EM_ASM_INT({
            ਵਾਪਸ Module['SDL3']['mouse_buttons'][$0];
        }, i);
        ਜੇ (button_ਥੱਲੇ) {
            flags |= 1 << i;
        }
    }
    ਵਾਪਸ flags;
}

ਖਾਲੀ Emscripten_InitMouse(ਖਾਲੀ)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    mouse->CreateCursor = Emscripten_CreateCursor;
    mouse->ShowCursor = Emscripten_ShowCursor;
    mouse->FreeCursor = Emscripten_FreeCursor;
    mouse->CreateSystemCursor = Emscripten_CreateSystemCursor;
    mouse->ਸੈੱਟ_Relative_Mouse_ਬਹੁਲਕ = Emscripten_ਸੈੱਟ_Relative_Mouse_ਬਹੁਲਕ;

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
        ਲਈ (var i = 0; i < 5; ++i) {
            SDL3['mouse_buttons'][i] = false;
        }
        document.ਜੋੜੋ_Event_Listener('mousemove', function(e) {
            // Reacquire from object in case it changed for some reason
            var SDL3 = Module['SDL3'];
            SDL3['mouse_x'] = e.clientX;
            SDL3['mouse_y'] = e.clientY;
        });
        document.ਜੋੜੋ_Event_Listener('mousedown', function(e) {
            // Reacquire from object in case it changed for some reason
            var SDL3 = Module['SDL3'];
            ਜੇ (0 <= e.button && e.button < SDL3['mouse_buttons'].ਲੰਮਾਈ) {
                SDL3['mouse_buttons'][e.button] = true;
            }
        });
        document.ਜੋੜੋ_Event_Listener('mouseup', function(e) {
            // Reacquire from object in case it changed for some reason
            var SDL3 = Module['SDL3'];
            ਜੇ (0 <= e.button && e.button < SDL3['mouse_buttons'].ਲੰਮਾਈ) {
                SDL3['mouse_buttons'][e.button] = false;
            }
        });
    });
    mouse->GetGlobalMouseState = Emscripten_GetGlobalMouseState;

    SDL_ਸੈੱਟ_Default_Cursor(Emscripten_CreateDefaultCursor());
}

ਖਾਲੀ Emscripten_QuitMouse(ਖਾਲੀ)
{
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_EMSCRIPTEN
