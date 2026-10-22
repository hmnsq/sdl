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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_EMSCRIPTEN

#ಅನ್ತರ್ಭಾವ <emscripten/emscripten.h>
#ಅನ್ತರ್ಭಾವ <emscripten/html5.h>
#ಅನ್ತರ್ಭಾವ <emscripten/threading.h>

#ಅನ್ತರ್ಭಾವ "SDL_emscriptenmouse.h"
#ಅನ್ತರ್ಭಾವ "SDL_emscriptenvideo.h"

#ಅನ್ತರ್ಭಾವ "../SDL_video_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_mouse_c.h"

// older Emscriptens don't have this, but we need to for wasm64 compatibility.
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MAIN_THREAD_EM_ASM_PTR
    #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __wasm64__
        #ದೋಷ You need ಗಮ್ಯ upgrade your Emscripten compiler ಗಮ್ಯ support wasm64
    #ಇಲ್ಲದಿದ್ದರೆ
        #ವ್ಯಾಖ್ಯಾನಿಸು MAIN_THREAD_EM_ASM_PTR MAIN_THREAD_EM_ASM_INT
    #ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ SDL_Cursor *Emscripten_CreateCursorFromString(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *cursor_str, bool is_custom)
{
    SDL_Cursor_ದತ್ತಾಂಶ *curdata;
    SDL_Cursor *cursor = SDL_calloc(1, ಗಾತ್ರ(SDL_Cursor));
    ಆದರೆ (cursor) {
        curdata = (SDL_Cursor_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(*curdata));
        ಆದರೆ (!curdata) {
            SDL_free(cursor);
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }

        curdata->system_cursor = cursor_str;
        curdata->is_custom = is_custom;
        cursor->ಆಂತರಿಕ = curdata;
    }

    ಹಿಂತಿರುಗಿ cursor;
}

ಸ್ಥಿರ SDL_Cursor *Emscripten_CreateDefaultCursor(ಶೂನ್ಯ)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *cursor_name = SDL_GetCSSCursorName(id, ಖಾಲಿ);
    ಹಿಂತಿರುಗಿ Emscripten_CreateCursorFromString(cursor_name, false);
}

EM_JS_DEPS(sdlmouse, "$stringToUTF8,$UTF8ToString");

ಸ್ಥಿರ SDL_Cursor *Emscripten_CreateCursor(SDL_Surface *surface, ಪೂರ್ಣಾಂಕ hot_x, ಪೂರ್ಣಾಂಕ hot_y)
{
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *cursor_url = ಖಾಲಿ;
    SDL_Surface *conv_surf;

    conv_surf = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);

    ಆದರೆ (!conv_surf) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    /* *INDENT-OFF* */ // clang-format off
    cursor_url = (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *)MAIN_THREAD_EM_ASM_PTR({
        var w = $0;
        var h = $1;
        var hot_x = $2;
        var hot_y = $3;
        var pixels = $4;

        var canvas = document.createElement("canvas");
        canvas.ಅಗಲ = w;
        canvas.ಎತ್ತರ = h;

        var ctx = canvas.getContext("2d");

        var image = ctx.create_Image_ದತ್ತಾಂಶ(w, h);
        var ದತ್ತಾಂಶ = image.ದತ್ತಾಂಶ;
        var src = pixels / 4;

        var data32 = new Int32Array(ದತ್ತಾಂಶ.ಬಫರ್_2);
        data32.ಗಣ(HEAP32.subarray(src, src + data32.ಉದ್ದಳತೆ));

        ctx.put_Image_ದತ್ತಾಂಶ(image, 0, 0);
        var url = hot_x === 0 && hot_y === 0
            ? "url(" + canvas.ಗಮ್ಯ_ದತ್ತಾಂಶ_URL() + "), auto"
            : "url(" + canvas.ಗಮ್ಯ_ದತ್ತಾಂಶ_URL() + ") " + hot_x + " " + hot_y + ", auto";

        var urlBuf = _SDL_malloc(url.ಉದ್ದಳತೆ + 1);
        string_ಗಮ್ಯ_UTF8(url, urlBuf, url.ಉದ್ದಳತೆ + 1);

        ಹಿಂತಿರುಗಿ urlBuf;
    }, surface->w, surface->h, hot_x, hot_y, conv_surf->pixels);
    /* *INDENT-ON* */ // clang-format on

    SDL_DestroySurface(conv_surf);

    ಹಿಂತಿರುಗಿ Emscripten_CreateCursorFromString(cursor_url, true);
}

ಸ್ಥಿರ SDL_Cursor *Emscripten_CreateSystemCursor(SDL_SystemCursor id)
{
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *cursor_name = SDL_GetCSSCursorName(id, ಖಾಲಿ);

    ಹಿಂತಿರುಗಿ Emscripten_CreateCursorFromString(cursor_name, false);
}

ಸ್ಥಿರ ಶೂನ್ಯ Emscripten_FreeCursor(SDL_Cursor *cursor)
{
    SDL_Cursor_ದತ್ತಾಂಶ *curdata;
    ಆದರೆ (cursor) {
        curdata = cursor->ಆಂತರಿಕ;

        ಆದರೆ (curdata) {
            ಆದರೆ (curdata->is_custom) {
                SDL_free((ಅಕ್ಷರ *)curdata->system_cursor);
            }
            SDL_free(cursor->ಆಂತರಿಕ);
        }

        SDL_free(cursor);
    }
}

ಸ್ಥಿರ bool Emscripten_ShowCursor(SDL_Cursor *cursor)
{
    SDL_Cursor_ದತ್ತಾಂಶ *curdata;
    ಆದರೆ (SDL_GetMouseFocus() != ಖಾಲಿ) {
        ಆದರೆ (cursor && cursor->ಆಂತರಿಕ) {
            curdata = cursor->ಆಂತರಿಕ;

            ಆದರೆ (curdata->system_cursor) {
                /* *INDENT-OFF* */ // clang-format off
                MAIN_THREAD_EM_ASM({
                    ಆದರೆ (Module['canvas']) {
                        Module['canvas'].style['cursor'] = UTF8_ಗಮ್ಯ_String($0);
                    }
                }, curdata->system_cursor);
                /* *INDENT-ON* */ // clang-format on
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            /* *INDENT-OFF* */ // clang-format off
            MAIN_THREAD_EM_ASM(
                ಆದರೆ (Module['canvas']) {
                    Module['canvas'].style['cursor'] = 'none';
                }
            );
            /* *INDENT-ON* */ // clang-format on
        }
    }
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool Emscripten_ಗಣ_Relative_Mouse_ಬಹುಲಕ(bool enabled)
{
    SDL_ಕಿಟಕಿ *ಕಿಟಕಿ;
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ_2;

    // TODO: pointer lock isn't actually enabled yet
    ಆದರೆ (enabled) {
        ಕಿಟಕಿ = SDL_GetMouseFocus();
        ಆದರೆ (!ಕಿಟಕಿ) {
            ಹಿಂತಿರುಗಿ false;
        }

        ಕಿಟಕಿ_ದತ್ತಾಂಶ_2 = ಕಿಟಕಿ->ಆಂತರಿಕ;

        ಆದರೆ (emscripten_request_pointerlock(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->canvas_id, 1) >= EMSCRIPTEN_ಫಲಿತಾಂಶ_SUCCESS) {
            ಹಿಂತಿರುಗಿ true;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (emscripten_exit_pointerlock() >= EMSCRIPTEN_ಫಲಿತಾಂಶ_SUCCESS) {
            ಹಿಂತಿರುಗಿ true;
        }
    }
    ಹಿಂತಿರುಗಿ false;
}

ಸ್ಥಿರ SDL_MouseButtonFlags Emscripten_GetGlobalMouseState(ದಶಮಾಂಶ *x, ದಶಮಾಂಶ *y)
{
    *x = MAIN_THREAD_EM_ASM_DOUBLE({
        ಹಿಂತಿರುಗಿ Module['SDL3']['mouse_x'];
    });
    *y = MAIN_THREAD_EM_ASM_DOUBLE({
        ಹಿಂತಿರುಗಿ Module['SDL3']['mouse_y'];
    });
    SDL_MouseButtonFlags flags = 0;
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < 5; ++i) {
        ಸ್ಥಿರಾಂಕ bool button_ಕೆಳಕ್ಕೆ = MAIN_THREAD_EM_ASM_INT({
            ಹಿಂತಿರುಗಿ Module['SDL3']['mouse_buttons'][$0];
        }, i);
        ಆದರೆ (button_ಕೆಳಕ್ಕೆ) {
            flags |= 1 << i;
        }
    }
    ಹಿಂತಿರುಗಿ flags;
}

ಶೂನ್ಯ Emscripten_InitMouse(ಶೂನ್ಯ)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    mouse->CreateCursor = Emscripten_CreateCursor;
    mouse->ShowCursor = Emscripten_ShowCursor;
    mouse->FreeCursor = Emscripten_FreeCursor;
    mouse->CreateSystemCursor = Emscripten_CreateSystemCursor;
    mouse->ಗಣ_Relative_Mouse_ಬಹುಲಕ = Emscripten_ಗಣ_Relative_Mouse_ಬಹುಲಕ;

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
        ಗಾಗಿ (var i = 0; i < 5; ++i) {
            SDL3['mouse_buttons'][i] = false;
        }
        document.ಕೂಡಿಸು_Event_Listener('mousemove', function(e) {
            // Reacquire from object in case it changed for some reason
            var SDL3 = Module['SDL3'];
            SDL3['mouse_x'] = e.clientX;
            SDL3['mouse_y'] = e.clientY;
        });
        document.ಕೂಡಿಸು_Event_Listener('mousedown', function(e) {
            // Reacquire from object in case it changed for some reason
            var SDL3 = Module['SDL3'];
            ಆದರೆ (0 <= e.button && e.button < SDL3['mouse_buttons'].ಉದ್ದಳತೆ) {
                SDL3['mouse_buttons'][e.button] = true;
            }
        });
        document.ಕೂಡಿಸು_Event_Listener('mouseup', function(e) {
            // Reacquire from object in case it changed for some reason
            var SDL3 = Module['SDL3'];
            ಆದರೆ (0 <= e.button && e.button < SDL3['mouse_buttons'].ಉದ್ದಳತೆ) {
                SDL3['mouse_buttons'][e.button] = false;
            }
        });
    });
    mouse->GetGlobalMouseState = Emscripten_GetGlobalMouseState;

    SDL_ಗಣ_Default_Cursor(Emscripten_CreateDefaultCursor());
}

ಶೂನ್ಯ Emscripten_QuitMouse(ಶೂನ್ಯ)
{
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_EMSCRIPTEN
