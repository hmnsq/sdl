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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_EMSCRIPTEN

#అన్తర్భావ <emscripten/emscripten.h>
#అన్తర్భావ <emscripten/html5.h>
#అన్తర్భావ <emscripten/threading.h>

#అన్తర్భావ "SDL_emscriptenmouse.h"
#అన్తర్భావ "SDL_emscriptenvideo.h"

#అన్తర్భావ "../SDL_video_c.h"
#అన్తర్భావ "../../events/SDL_mouse_c.h"

// older Emscriptens don't have this, but we need to for wasm64 compatibility.
#నిర్వచితం_కాకపోతే MAIN_THREAD_EM_ASM_PTR
    #నిర్వచితమైతే __wasm64__
        #దోషం You need గమ్యం upgrade your Emscripten compiler గమ్యం support wasm64
    #లేకపోతే
        #నిర్వచించు MAIN_THREAD_EM_ASM_PTR MAIN_THREAD_EM_ASM_INT
    #అయితే_ముగింపు
#అయితే_ముగింపు

స్థిర SDL_Cursor *Emscripten_CreateCursorFromString(స్థిరరాశి అక్షరం *cursor_str, bool is_custom)
{
    SDL_Cursor_దత్తాంశం *curdata;
    SDL_Cursor *cursor = SDL_calloc(1, పరిమాణం(SDL_Cursor));
    ఒకవేళ (cursor) {
        curdata = (SDL_Cursor_దత్తాంశం *)SDL_calloc(1, పరిమాణం(*curdata));
        ఒకవేళ (!curdata) {
            SDL_free(cursor);
            తిరిగి ఖాళీ;
        }

        curdata->system_cursor = cursor_str;
        curdata->is_custom = is_custom;
        cursor->అంతర్గత = curdata;
    }

    తిరిగి cursor;
}

స్థిర SDL_Cursor *Emscripten_CreateDefaultCursor(శూన్య)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    స్థిరరాశి అక్షరం *cursor_name = SDL_GetCSSCursorName(id, ఖాళీ);
    తిరిగి Emscripten_CreateCursorFromString(cursor_name, false);
}

EM_JS_DEPS(sdlmouse, "$stringToUTF8,$UTF8ToString");

స్థిర SDL_Cursor *Emscripten_CreateCursor(SDL_Surface *surface, పూర్ణాంకం hot_x, పూర్ణాంకం hot_y)
{
    స్థిరరాశి అక్షరం *cursor_url = ఖాళీ;
    SDL_Surface *conv_surf;

    conv_surf = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);

    ఒకవేళ (!conv_surf) {
        తిరిగి ఖాళీ;
    }

    /* *INDENT-OFF* */ // clang-format off
    cursor_url = (స్థిరరాశి అక్షరం *)MAIN_THREAD_EM_ASM_PTR({
        var w = $0;
        var h = $1;
        var hot_x = $2;
        var hot_y = $3;
        var pixels = $4;

        var canvas = document.createElement("canvas");
        canvas.వెడల్పు = w;
        canvas.ఎత్తు = h;

        var ctx = canvas.getContext("2d");

        var image = ctx.create_Image_దత్తాంశం(w, h);
        var దత్తాంశం = image.దత్తాంశం;
        var src = pixels / 4;

        var data32 = new Int32Array(దత్తాంశం.బఫరు_2);
        data32.సమితి(HEAP32.subarray(src, src + data32.నిడివి));

        ctx.put_Image_దత్తాంశం(image, 0, 0);
        var url = hot_x === 0 && hot_y === 0
            ? "url(" + canvas.గమ్యం_దత్తాంశం_URL() + "), auto"
            : "url(" + canvas.గమ్యం_దత్తాంశం_URL() + ") " + hot_x + " " + hot_y + ", auto";

        var urlBuf = _SDL_malloc(url.నిడివి + 1);
        string_గమ్యం_UTF8(url, urlBuf, url.నిడివి + 1);

        తిరిగి urlBuf;
    }, surface->w, surface->h, hot_x, hot_y, conv_surf->pixels);
    /* *INDENT-ON* */ // clang-format on

    SDL_DestroySurface(conv_surf);

    తిరిగి Emscripten_CreateCursorFromString(cursor_url, true);
}

స్థిర SDL_Cursor *Emscripten_CreateSystemCursor(SDL_SystemCursor id)
{
    స్థిరరాశి అక్షరం *cursor_name = SDL_GetCSSCursorName(id, ఖాళీ);

    తిరిగి Emscripten_CreateCursorFromString(cursor_name, false);
}

స్థిర శూన్య Emscripten_FreeCursor(SDL_Cursor *cursor)
{
    SDL_Cursor_దత్తాంశం *curdata;
    ఒకవేళ (cursor) {
        curdata = cursor->అంతర్గత;

        ఒకవేళ (curdata) {
            ఒకవేళ (curdata->is_custom) {
                SDL_free((అక్షరం *)curdata->system_cursor);
            }
            SDL_free(cursor->అంతర్గత);
        }

        SDL_free(cursor);
    }
}

స్థిర bool Emscripten_ShowCursor(SDL_Cursor *cursor)
{
    SDL_Cursor_దత్తాంశం *curdata;
    ఒకవేళ (SDL_GetMouseFocus() != ఖాళీ) {
        ఒకవేళ (cursor && cursor->అంతర్గత) {
            curdata = cursor->అంతర్గత;

            ఒకవేళ (curdata->system_cursor) {
                /* *INDENT-OFF* */ // clang-format off
                MAIN_THREAD_EM_ASM({
                    ఒకవేళ (Module['canvas']) {
                        Module['canvas'].style['cursor'] = UTF8_గమ్యం_String($0);
                    }
                }, curdata->system_cursor);
                /* *INDENT-ON* */ // clang-format on
            }
        } లేకపోతే {
            /* *INDENT-OFF* */ // clang-format off
            MAIN_THREAD_EM_ASM(
                ఒకవేళ (Module['canvas']) {
                    Module['canvas'].style['cursor'] = 'none';
                }
            );
            /* *INDENT-ON* */ // clang-format on
        }
    }
    తిరిగి true;
}

స్థిర bool Emscripten_సమితి_Relative_Mouse_బహుళకం(bool enabled)
{
    SDL_కిటికీ *కిటికీ;
    SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం_2;

    // TODO: pointer lock isn't actually enabled yet
    ఒకవేళ (enabled) {
        కిటికీ = SDL_GetMouseFocus();
        ఒకవేళ (!కిటికీ) {
            తిరిగి false;
        }

        కిటికీ_దత్తాంశం_2 = కిటికీ->అంతర్గత;

        ఒకవేళ (emscripten_request_pointerlock(కిటికీ_దత్తాంశం_2->canvas_id, 1) >= EMSCRIPTEN_ఫలితం_SUCCESS) {
            తిరిగి true;
        }
    } లేకపోతే {
        ఒకవేళ (emscripten_exit_pointerlock() >= EMSCRIPTEN_ఫలితం_SUCCESS) {
            తిరిగి true;
        }
    }
    తిరిగి false;
}

స్థిర SDL_MouseButtonFlags Emscripten_GetGlobalMouseState(దశాంశం *x, దశాంశం *y)
{
    *x = MAIN_THREAD_EM_ASM_DOUBLE({
        తిరిగి Module['SDL3']['mouse_x'];
    });
    *y = MAIN_THREAD_EM_ASM_DOUBLE({
        తిరిగి Module['SDL3']['mouse_y'];
    });
    SDL_MouseButtonFlags flags = 0;
    కొరకు (పూర్ణాంకం i = 0; i < 5; ++i) {
        స్థిరరాశి bool button_కిందికి = MAIN_THREAD_EM_ASM_INT({
            తిరిగి Module['SDL3']['mouse_buttons'][$0];
        }, i);
        ఒకవేళ (button_కిందికి) {
            flags |= 1 << i;
        }
    }
    తిరిగి flags;
}

శూన్య Emscripten_InitMouse(శూన్య)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    mouse->CreateCursor = Emscripten_CreateCursor;
    mouse->ShowCursor = Emscripten_ShowCursor;
    mouse->FreeCursor = Emscripten_FreeCursor;
    mouse->CreateSystemCursor = Emscripten_CreateSystemCursor;
    mouse->సమితి_Relative_Mouse_బహుళకం = Emscripten_సమితి_Relative_Mouse_బహుళకం;

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
        కొరకు (var i = 0; i < 5; ++i) {
            SDL3['mouse_buttons'][i] = false;
        }
        document.కూడు_Event_Listener('mousemove', function(e) {
            // Reacquire from object in case it changed for some reason
            var SDL3 = Module['SDL3'];
            SDL3['mouse_x'] = e.clientX;
            SDL3['mouse_y'] = e.clientY;
        });
        document.కూడు_Event_Listener('mousedown', function(e) {
            // Reacquire from object in case it changed for some reason
            var SDL3 = Module['SDL3'];
            ఒకవేళ (0 <= e.button && e.button < SDL3['mouse_buttons'].నిడివి) {
                SDL3['mouse_buttons'][e.button] = true;
            }
        });
        document.కూడు_Event_Listener('mouseup', function(e) {
            // Reacquire from object in case it changed for some reason
            var SDL3 = Module['SDL3'];
            ఒకవేళ (0 <= e.button && e.button < SDL3['mouse_buttons'].నిడివి) {
                SDL3['mouse_buttons'][e.button] = false;
            }
        });
    });
    mouse->GetGlobalMouseState = Emscripten_GetGlobalMouseState;

    SDL_సమితి_Default_Cursor(Emscripten_CreateDefaultCursor());
}

శూన్య Emscripten_QuitMouse(శూన్య)
{
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_EMSCRIPTEN
