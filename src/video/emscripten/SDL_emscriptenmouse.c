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
#شامل "SDL_internal.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_EMSCRIPTEN

#شامل <emscripten/emscripten.h>
#شامل <emscripten/html5.h>
#شامل <emscripten/threading.h>

#شامل "SDL_emscriptenmouse.h"
#شامل "SDL_emscriptenvideo.h"

#شامل "../SDL_video_c.h"
#شامل "../../events/SDL_mouse_c.h"

// older Emscriptens don't have this, but we need to for wasm64 compatibility.
#اگر_غیر_تعریف_شدہ MAIN_THREAD_EM_ASM_PTR
    #اگر_تعریف_شدہ __wasm64__
        #غلطی You need مقصد upgrade your Emscripten compiler مقصد support wasm64
    #ورنہ
        #تعریف_کرو MAIN_THREAD_EM_ASM_PTR MAIN_THREAD_EM_ASM_INT
    #اگر_ختم
#اگر_ختم

ساکن SDL_Cursor *Emscripten_CreateCursorFromString(ثابت حرف *cursor_str, bool is_custom)
{
    SDL_Cursor_ڈیٹا *curdata;
    SDL_Cursor *cursor = SDL_calloc(1, حجم(SDL_Cursor));
    اگر (cursor) {
        curdata = (SDL_Cursor_ڈیٹا *)SDL_calloc(1, حجم(*curdata));
        اگر (!curdata) {
            SDL_free(cursor);
            واپس تہی;
        }

        curdata->system_cursor = cursor_str;
        curdata->is_custom = is_custom;
        cursor->اندرونی_2 = curdata;
    }

    واپس cursor;
}

ساکن SDL_Cursor *Emscripten_CreateDefaultCursor(خالی)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    ثابت حرف *cursor_name = SDL_GetCSSCursorName(id, تہی);
    واپس Emscripten_CreateCursorFromString(cursor_name, false);
}

EM_JS_DEPS(sdlmouse, "$stringToUTF8,$UTF8ToString");

ساکن SDL_Cursor *Emscripten_CreateCursor(SDL_Surface *surface, صحیح hot_x, صحیح hot_y)
{
    ثابت حرف *cursor_url = تہی;
    SDL_Surface *conv_surf;

    conv_surf = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);

    اگر (!conv_surf) {
        واپس تہی;
    }

    /* *INDENT-OFF* */ // clang-format off
    cursor_url = (ثابت حرف *)MAIN_THREAD_EM_ASM_PTR({
        var w = $0;
        var h = $1;
        var hot_x = $2;
        var hot_y = $3;
        var pixels = $4;

        var canvas = document.createElement("canvas");
        canvas.چوڑائی = w;
        canvas.اونچائی = h;

        var ctx = canvas.getContext("2d");

        var image = ctx.create_Image_ڈیٹا(w, h);
        var ڈیٹا = image.ڈیٹا;
        var src = pixels / 4;

        var data32 = new Int32Array(ڈیٹا.بفر_2);
        data32.سیٹ(HEAP32.subarray(src, src + data32.لمبائی));

        ctx.put_Image_ڈیٹا(image, 0, 0);
        var url = hot_x === 0 && hot_y === 0
            ? "url(" + canvas.مقصد_ڈیٹا_URL() + "), auto"
            : "url(" + canvas.مقصد_ڈیٹا_URL() + ") " + hot_x + " " + hot_y + ", auto";

        var urlBuf = _SDL_malloc(url.لمبائی + 1);
        string_مقصد_UTF8(url, urlBuf, url.لمبائی + 1);

        واپس urlBuf;
    }, surface->w, surface->h, hot_x, hot_y, conv_surf->pixels);
    /* *INDENT-ON* */ // clang-format on

    SDL_DestroySurface(conv_surf);

    واپس Emscripten_CreateCursorFromString(cursor_url, true);
}

ساکن SDL_Cursor *Emscripten_CreateSystemCursor(SDL_SystemCursor id)
{
    ثابت حرف *cursor_name = SDL_GetCSSCursorName(id, تہی);

    واپس Emscripten_CreateCursorFromString(cursor_name, false);
}

ساکن خالی Emscripten_FreeCursor(SDL_Cursor *cursor)
{
    SDL_Cursor_ڈیٹا *curdata;
    اگر (cursor) {
        curdata = cursor->اندرونی_2;

        اگر (curdata) {
            اگر (curdata->is_custom) {
                SDL_free((حرف *)curdata->system_cursor);
            }
            SDL_free(cursor->اندرونی_2);
        }

        SDL_free(cursor);
    }
}

ساکن bool Emscripten_ShowCursor(SDL_Cursor *cursor)
{
    SDL_Cursor_ڈیٹا *curdata;
    اگر (SDL_GetMouseFocus() != تہی) {
        اگر (cursor && cursor->اندرونی_2) {
            curdata = cursor->اندرونی_2;

            اگر (curdata->system_cursor) {
                /* *INDENT-OFF* */ // clang-format off
                MAIN_THREAD_EM_ASM({
                    اگر (Module['canvas']) {
                        Module['canvas'].style['cursor'] = UTF8_مقصد_String($0);
                    }
                }, curdata->system_cursor);
                /* *INDENT-ON* */ // clang-format on
            }
        } ورنہ {
            /* *INDENT-OFF* */ // clang-format off
            MAIN_THREAD_EM_ASM(
                اگر (Module['canvas']) {
                    Module['canvas'].style['cursor'] = 'none';
                }
            );
            /* *INDENT-ON* */ // clang-format on
        }
    }
    واپس true;
}

ساکن bool Emscripten_سیٹ_Relative_Mouse_منوال(bool enabled)
{
    SDL_کھڑکی *کھڑکی;
    SDL_کھڑکی_ڈیٹا *کھڑکی_ڈیٹا_2;

    // TODO: pointer lock isn't actually enabled yet
    اگر (enabled) {
        کھڑکی = SDL_GetMouseFocus();
        اگر (!کھڑکی) {
            واپس false;
        }

        کھڑکی_ڈیٹا_2 = کھڑکی->اندرونی_2;

        اگر (emscripten_request_pointerlock(کھڑکی_ڈیٹا_2->canvas_id, 1) >= EMSCRIPTEN_نتیجہ_SUCCESS) {
            واپس true;
        }
    } ورنہ {
        اگر (emscripten_exit_pointerlock() >= EMSCRIPTEN_نتیجہ_SUCCESS) {
            واپس true;
        }
    }
    واپس false;
}

ساکن SDL_MouseButtonFlags Emscripten_GetGlobalMouseState(اعشاری *x, اعشاری *y)
{
    *x = MAIN_THREAD_EM_ASM_DOUBLE({
        واپس Module['SDL3']['mouse_x'];
    });
    *y = MAIN_THREAD_EM_ASM_DOUBLE({
        واپس Module['SDL3']['mouse_y'];
    });
    SDL_MouseButtonFlags flags = 0;
    برائے (صحیح i = 0; i < 5; ++i) {
        ثابت bool button_نیچے_کو = MAIN_THREAD_EM_ASM_INT({
            واپس Module['SDL3']['mouse_buttons'][$0];
        }, i);
        اگر (button_نیچے_کو) {
            flags |= 1 << i;
        }
    }
    واپس flags;
}

خالی Emscripten_InitMouse(خالی)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    mouse->CreateCursor = Emscripten_CreateCursor;
    mouse->ShowCursor = Emscripten_ShowCursor;
    mouse->FreeCursor = Emscripten_FreeCursor;
    mouse->CreateSystemCursor = Emscripten_CreateSystemCursor;
    mouse->سیٹ_Relative_Mouse_منوال = Emscripten_سیٹ_Relative_Mouse_منوال;

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
        برائے (var i = 0; i < 5; ++i) {
            SDL3['mouse_buttons'][i] = false;
        }
        document.جوڑو_Event_Listener('mousemove', function(e) {
            // Reacquire from object in case it changed for some reason
            var SDL3 = Module['SDL3'];
            SDL3['mouse_x'] = e.clientX;
            SDL3['mouse_y'] = e.clientY;
        });
        document.جوڑو_Event_Listener('mousedown', function(e) {
            // Reacquire from object in case it changed for some reason
            var SDL3 = Module['SDL3'];
            اگر (0 <= e.button && e.button < SDL3['mouse_buttons'].لمبائی) {
                SDL3['mouse_buttons'][e.button] = true;
            }
        });
        document.جوڑو_Event_Listener('mouseup', function(e) {
            // Reacquire from object in case it changed for some reason
            var SDL3 = Module['SDL3'];
            اگر (0 <= e.button && e.button < SDL3['mouse_buttons'].لمبائی) {
                SDL3['mouse_buttons'][e.button] = false;
            }
        });
    });
    mouse->GetGlobalMouseState = Emscripten_GetGlobalMouseState;

    SDL_سیٹ_Default_Cursor(Emscripten_CreateDefaultCursor());
}

خالی Emscripten_QuitMouse(خالی)
{
}

#اگر_ختم // SDL_VIDEO_DRIVER_EMSCRIPTEN
