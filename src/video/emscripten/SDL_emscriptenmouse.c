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
#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_EMSCRIPTEN

#समावेश <emscripten/emscripten.h>
#समावेश <emscripten/html5.h>
#समावेश <emscripten/threading.h>

#समावेश "SDL_emscriptenmouse.h"
#समावेश "SDL_emscriptenvideo.h"

#समावेश "../SDL_video_c.h"
#समावेश "../../events/SDL_mouse_c.h"

// older Emscriptens don't have this, but we need to for wasm64 compatibility.
#अगर_अघोषित MAIN_THREAD_EM_ASM_PTR
    #अगर_घोषित __wasm64__
        #त्रुटि You need to upgrade your Emscripten compiler to support wasm64
    #अन्यथा
        #घोषणा MAIN_THREAD_EM_ASM_PTR MAIN_THREAD_EM_ASM_INT
    #पूर्ण_अगर
#पूर्ण_अगर

अटल SDL_Cursor *Emscripten_CreateCursorFromString(स्थिर अक्षर *cursor_str, bool is_custom)
{
    SDL_Cursor_तथ्य *curdata;
    SDL_Cursor *cursor = SDL_calloc(1, माप(SDL_Cursor));
    अगर (cursor) {
        curdata = (SDL_Cursor_तथ्य *)SDL_calloc(1, माप(*curdata));
        अगर (!curdata) {
            SDL_free(cursor);
            वापस शून्य;
        }

        curdata->system_cursor = cursor_str;
        curdata->is_custom = is_custom;
        cursor->internal = curdata;
    }

    वापस cursor;
}

अटल SDL_Cursor *Emscripten_CreateDefaultCursor(व्योम)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    स्थिर अक्षर *cursor_name = SDL_GetCSSCursorName(id, शून्य);
    वापस Emscripten_CreateCursorFromString(cursor_name, false);
}

EM_JS_DEPS(sdlmouse, "$stringToUTF8,$UTF8ToString");

अटल SDL_Cursor *Emscripten_CreateCursor(SDL_Surface *surface, पूर्णांक hot_x, पूर्णांक hot_y)
{
    स्थिर अक्षर *cursor_url = शून्य;
    SDL_Surface *conv_surf;

    conv_surf = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);

    अगर (!conv_surf) {
        वापस शून्य;
    }

    /* *INDENT-OFF* */ // clang-format off
    cursor_url = (स्थिर अक्षर *)MAIN_THREAD_EM_ASM_PTR({
        var w = $0;
        var h = $1;
        var hot_x = $2;
        var hot_y = $3;
        var pixels = $4;

        var canvas = document.createElement("canvas");
        canvas.width = w;
        canvas.height = h;

        var ctx = canvas.getContext("2d");

        var image = ctx.create_Image_तथ्य(w, h);
        var तथ्य = image.तथ्य;
        var src = pixels / 4;

        var data32 = new Int32Array(तथ्य.बफर_2);
        data32.set(HEAP32.subarray(src, src + data32.लंबाई));

        ctx.put_Image_तथ्य(image, 0, 0);
        var url = hot_x === 0 && hot_y === 0
            ? "url(" + canvas.to_तथ्य_URL() + "), auto"
            : "url(" + canvas.to_तथ्य_URL() + ") " + hot_x + " " + hot_y + ", auto";

        var urlBuf = _SDL_malloc(url.लंबाई + 1);
        stringToUTF8(url, urlBuf, url.लंबाई + 1);

        वापस urlBuf;
    }, surface->w, surface->h, hot_x, hot_y, conv_surf->pixels);
    /* *INDENT-ON* */ // clang-format on

    SDL_DestroySurface(conv_surf);

    वापस Emscripten_CreateCursorFromString(cursor_url, true);
}

अटल SDL_Cursor *Emscripten_CreateSystemCursor(SDL_SystemCursor id)
{
    स्थिर अक्षर *cursor_name = SDL_GetCSSCursorName(id, शून्य);

    वापस Emscripten_CreateCursorFromString(cursor_name, false);
}

अटल व्योम Emscripten_FreeCursor(SDL_Cursor *cursor)
{
    SDL_Cursor_तथ्य *curdata;
    अगर (cursor) {
        curdata = cursor->internal;

        अगर (curdata) {
            अगर (curdata->is_custom) {
                SDL_free((अक्षर *)curdata->system_cursor);
            }
            SDL_free(cursor->internal);
        }

        SDL_free(cursor);
    }
}

अटल bool Emscripten_ShowCursor(SDL_Cursor *cursor)
{
    SDL_Cursor_तथ्य *curdata;
    अगर (SDL_GetMouseFocus() != शून्य) {
        अगर (cursor && cursor->internal) {
            curdata = cursor->internal;

            अगर (curdata->system_cursor) {
                /* *INDENT-OFF* */ // clang-format off
                MAIN_THREAD_EM_ASM({
                    अगर (Module['canvas']) {
                        Module['canvas'].style['cursor'] = UTF8ToString($0);
                    }
                }, curdata->system_cursor);
                /* *INDENT-ON* */ // clang-format on
            }
        } अन्यथा {
            /* *INDENT-OFF* */ // clang-format off
            MAIN_THREAD_EM_ASM(
                अगर (Module['canvas']) {
                    Module['canvas'].style['cursor'] = 'none';
                }
            );
            /* *INDENT-ON* */ // clang-format on
        }
    }
    वापस true;
}

अटल bool Emscripten_SetRelativeMouseMode(bool enabled)
{
    SDL_Window *window;
    SDL_Window_तथ्य *window_तथ्य_2;

    // TODO: pointer lock isn't actually enabled yet
    अगर (enabled) {
        window = SDL_GetMouseFocus();
        अगर (!window) {
            वापस false;
        }

        window_तथ्य_2 = window->internal;

        अगर (emscripten_request_pointerlock(window_तथ्य_2->canvas_id, 1) >= EMSCRIPTEN_परिणाम_SUCCESS) {
            वापस true;
        }
    } अन्यथा {
        अगर (emscripten_exit_pointerlock() >= EMSCRIPTEN_परिणाम_SUCCESS) {
            वापस true;
        }
    }
    वापस false;
}

अटल SDL_MouseButtonFlags Emscripten_GetGlobalMouseState(भग्न *x, भग्न *y)
{
    *x = MAIN_THREAD_EM_ASM_DOUBLE({
        वापस Module['SDL3']['mouse_x'];
    });
    *y = MAIN_THREAD_EM_ASM_DOUBLE({
        वापस Module['SDL3']['mouse_y'];
    });
    SDL_MouseButtonFlags flags = 0;
    क्रम (पूर्णांक i = 0; i < 5; ++i) {
        स्थिर bool button_down = MAIN_THREAD_EM_ASM_INT({
            वापस Module['SDL3']['mouse_buttons'][$0];
        }, i);
        अगर (button_down) {
            flags |= 1 << i;
        }
    }
    वापस flags;
}

व्योम Emscripten_InitMouse(व्योम)
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
        क्रम (var i = 0; i < 5; ++i) {
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
            अगर (0 <= e.button && e.button < SDL3['mouse_buttons'].लंबाई) {
                SDL3['mouse_buttons'][e.button] = true;
            }
        });
        document.addEventListener('mouseup', function(e) {
            // Reacquire from object in case it changed for some reason
            var SDL3 = Module['SDL3'];
            अगर (0 <= e.button && e.button < SDL3['mouse_buttons'].लंबाई) {
                SDL3['mouse_buttons'][e.button] = false;
            }
        });
    });
    mouse->GetGlobalMouseState = Emscripten_GetGlobalMouseState;

    SDL_SetDefaultCursor(Emscripten_CreateDefaultCursor());
}

व्योम Emscripten_QuitMouse(व्योम)
{
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_EMSCRIPTEN
