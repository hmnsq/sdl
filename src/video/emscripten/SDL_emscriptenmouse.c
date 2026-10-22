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
#अन्तर्भाव "SDL_internal.h"

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_EMSCRIPTEN

#अन्तर्भाव <emscripten/emscripten.h>
#अन्तर्भाव <emscripten/html5.h>
#अन्तर्भाव <emscripten/threading.h>

#अन्तर्भाव "SDL_emscriptenmouse.h"
#अन्तर्भाव "SDL_emscriptenvideo.h"

#अन्तर्भाव "../SDL_video_c.h"
#अन्तर्भाव "../../events/SDL_mouse_c.h"

// older Emscriptens don't have this, but we need to for wasm64 compatibility.
#यदि_अपरिभाषितम् MAIN_THREAD_EM_ASM_PTR
    #यदि_परिभाषितम् __wasm64__
        #दोषः You need गन्तव्यम् upgrade your Emscripten compiler गन्तव्यम् support wasm64
    #अन्यथा
        #परिभाषय MAIN_THREAD_EM_ASM_PTR MAIN_THREAD_EM_ASM_INT
    #यदि_अन्तः
#यदि_अन्तः

स्थिर SDL_Cursor *Emscripten_CreateCursorFromString(ध्रुव वर्ण *cursor_str, bool is_custom)
{
    SDL_Cursor_दत्त *curdata;
    SDL_Cursor *cursor = SDL_calloc(1, परिमाण(SDL_Cursor));
    यदि (cursor) {
        curdata = (SDL_Cursor_दत्त *)SDL_calloc(1, परिमाण(*curdata));
        यदि (!curdata) {
            SDL_free(cursor);
            प्रत्यागम रिक्त;
        }

        curdata->system_cursor = cursor_str;
        curdata->is_custom = is_custom;
        cursor->आन्तरिकम् = curdata;
    }

    प्रत्यागम cursor;
}

स्थिर SDL_Cursor *Emscripten_CreateDefaultCursor(शून्य)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    ध्रुव वर्ण *cursor_name = SDL_GetCSSCursorName(id, रिक्त);
    प्रत्यागम Emscripten_CreateCursorFromString(cursor_name, false);
}

EM_JS_DEPS(sdlmouse, "$stringToUTF8,$UTF8ToString");

स्थिर SDL_Cursor *Emscripten_CreateCursor(SDL_Surface *surface, पूर्णाङ्क hot_x, पूर्णाङ्क hot_y)
{
    ध्रुव वर्ण *cursor_url = रिक्त;
    SDL_Surface *conv_surf;

    conv_surf = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);

    यदि (!conv_surf) {
        प्रत्यागम रिक्त;
    }

    /* *INDENT-OFF* */ // clang-format off
    cursor_url = (ध्रुव वर्ण *)MAIN_THREAD_EM_ASM_PTR({
        var w = $0;
        var h = $1;
        var hot_x = $2;
        var hot_y = $3;
        var pixels = $4;

        var canvas = document.createElement("canvas");
        canvas.विस्तारः = w;
        canvas.height = h;

        var ctx = canvas.getContext("2d");

        var image = ctx.create_Image_दत्त(w, h);
        var दत्त = image.दत्त;
        var src = pixels / 4;

        var data32 = new Int32Array(दत्त.बफर_2);
        data32.समुच्चयः(HEAP32.subarray(src, src + data32.दीर्घता));

        ctx.put_Image_दत्त(image, 0, 0);
        var url = hot_x === 0 && hot_y === 0
            ? "url(" + canvas.गन्तव्यम्_दत्त_URL() + "), auto"
            : "url(" + canvas.गन्तव्यम्_दत्त_URL() + ") " + hot_x + " " + hot_y + ", auto";

        var urlBuf = _SDL_malloc(url.दीर्घता + 1);
        string_गन्तव्यम्_UTF8(url, urlBuf, url.दीर्घता + 1);

        प्रत्यागम urlBuf;
    }, surface->w, surface->h, hot_x, hot_y, conv_surf->pixels);
    /* *INDENT-ON* */ // clang-format on

    SDL_DestroySurface(conv_surf);

    प्रत्यागम Emscripten_CreateCursorFromString(cursor_url, true);
}

स्थिर SDL_Cursor *Emscripten_CreateSystemCursor(SDL_SystemCursor id)
{
    ध्रुव वर्ण *cursor_name = SDL_GetCSSCursorName(id, रिक्त);

    प्रत्यागम Emscripten_CreateCursorFromString(cursor_name, false);
}

स्थिर शून्य Emscripten_FreeCursor(SDL_Cursor *cursor)
{
    SDL_Cursor_दत्त *curdata;
    यदि (cursor) {
        curdata = cursor->आन्तरिकम्;

        यदि (curdata) {
            यदि (curdata->is_custom) {
                SDL_free((वर्ण *)curdata->system_cursor);
            }
            SDL_free(cursor->आन्तरिकम्);
        }

        SDL_free(cursor);
    }
}

स्थिर bool Emscripten_ShowCursor(SDL_Cursor *cursor)
{
    SDL_Cursor_दत्त *curdata;
    यदि (SDL_GetMouseFocus() != रिक्त) {
        यदि (cursor && cursor->आन्तरिकम्) {
            curdata = cursor->आन्तरिकम्;

            यदि (curdata->system_cursor) {
                /* *INDENT-OFF* */ // clang-format off
                MAIN_THREAD_EM_ASM({
                    यदि (Module['canvas']) {
                        Module['canvas'].style['cursor'] = UTF8_गन्तव्यम्_String($0);
                    }
                }, curdata->system_cursor);
                /* *INDENT-ON* */ // clang-format on
            }
        } अन्यथा {
            /* *INDENT-OFF* */ // clang-format off
            MAIN_THREAD_EM_ASM(
                यदि (Module['canvas']) {
                    Module['canvas'].style['cursor'] = 'none';
                }
            );
            /* *INDENT-ON* */ // clang-format on
        }
    }
    प्रत्यागम true;
}

स्थिर bool Emscripten_समुच्चयः_Relative_Mouse_बहुलकम्(bool enabled)
{
    SDL_गवाक्षः *गवाक्षः;
    SDL_गवाक्षः_दत्त *गवाक्षः_दत्त_2;

    // TODO: pointer lock isn't actually enabled yet
    यदि (enabled) {
        गवाक्षः = SDL_GetMouseFocus();
        यदि (!गवाक्षः) {
            प्रत्यागम false;
        }

        गवाक्षः_दत्त_2 = गवाक्षः->आन्तरिकम्;

        यदि (emscripten_request_pointerlock(गवाक्षः_दत्त_2->canvas_id, 1) >= EMSCRIPTEN_परिणाम_SUCCESS) {
            प्रत्यागम true;
        }
    } अन्यथा {
        यदि (emscripten_exit_pointerlock() >= EMSCRIPTEN_परिणाम_SUCCESS) {
            प्रत्यागम true;
        }
    }
    प्रत्यागम false;
}

स्थिर SDL_MouseButtonFlags Emscripten_GetGlobalMouseState(भिन्न *x, भिन्न *y)
{
    *x = MAIN_THREAD_EM_ASM_DOUBLE({
        प्रत्यागम Module['SDL3']['mouse_x'];
    });
    *y = MAIN_THREAD_EM_ASM_DOUBLE({
        प्रत्यागम Module['SDL3']['mouse_y'];
    });
    SDL_MouseButtonFlags flags = 0;
    प्रति (पूर्णाङ्क i = 0; i < 5; ++i) {
        ध्रुव bool button_अधस्तात् = MAIN_THREAD_EM_ASM_INT({
            प्रत्यागम Module['SDL3']['mouse_buttons'][$0];
        }, i);
        यदि (button_अधस्तात्) {
            flags |= 1 << i;
        }
    }
    प्रत्यागम flags;
}

शून्य Emscripten_InitMouse(शून्य)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    mouse->CreateCursor = Emscripten_CreateCursor;
    mouse->ShowCursor = Emscripten_ShowCursor;
    mouse->FreeCursor = Emscripten_FreeCursor;
    mouse->CreateSystemCursor = Emscripten_CreateSystemCursor;
    mouse->समुच्चयः_Relative_Mouse_बहुलकम् = Emscripten_समुच्चयः_Relative_Mouse_बहुलकम्;

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
        प्रति (var i = 0; i < 5; ++i) {
            SDL3['mouse_buttons'][i] = false;
        }
        document.सङ्कलय_Event_Listener('mousemove', function(e) {
            // Reacquire from object in case it changed for some reason
            var SDL3 = Module['SDL3'];
            SDL3['mouse_x'] = e.clientX;
            SDL3['mouse_y'] = e.clientY;
        });
        document.सङ्कलय_Event_Listener('mousedown', function(e) {
            // Reacquire from object in case it changed for some reason
            var SDL3 = Module['SDL3'];
            यदि (0 <= e.button && e.button < SDL3['mouse_buttons'].दीर्घता) {
                SDL3['mouse_buttons'][e.button] = true;
            }
        });
        document.सङ्कलय_Event_Listener('mouseup', function(e) {
            // Reacquire from object in case it changed for some reason
            var SDL3 = Module['SDL3'];
            यदि (0 <= e.button && e.button < SDL3['mouse_buttons'].दीर्घता) {
                SDL3['mouse_buttons'][e.button] = false;
            }
        });
    });
    mouse->GetGlobalMouseState = Emscripten_GetGlobalMouseState;

    SDL_समुच्चयः_Default_Cursor(Emscripten_CreateDefaultCursor());
}

शून्य Emscripten_QuitMouse(शून्य)
{
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_EMSCRIPTEN
