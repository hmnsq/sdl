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
#അന്തര്ഭാവ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_EMSCRIPTEN

#അന്തര്ഭാവ <emscripten/emscripten.h>
#അന്തര്ഭാവ <emscripten/html5_webgl.h>
#അന്തര്ഭാവ <GLES2/gl2.h>

#അന്തര്ഭാവ "SDL_emscriptenvideo.h"
#അന്തര്ഭാവ "SDL_emscriptenopengles.h"
#അന്തര്ഭാവ "../../main/SDL_main_callbacks.h"

bool Emscripten_GLES_LoadLibrary(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *path)
{
    തിരികെ true;
}

ശൂന്യം Emscripten_GLES_UnloadLibrary(SDL_VideoDevice *_this)
{
}

SDL_FunctionPointer Emscripten_GLES_GetProcAddress(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *proc)
{
    തിരികെ emscripten_webgl_get_proc_address(proc);
}

bool Emscripten_GLES_SetSwapInterval(SDL_VideoDevice *_this, പൂർണ്ണസംഖ്യ interval)
{
    എങ്കിൽ (interval < 0) {
        തിരികെ SDL_SetError("Late swap tearing currently unsupported");
    }

    എങ്കിൽ (Emscripten_ShouldSetSwapInterval(interval)) {
        // don't change the mainloop timing if the app is also driving a main callback with this hint,
        //  as we assume that was the more deliberate action.
        എങ്കിൽ (!SDL_HasMainCallbacks() || !SDL_GetHint(SDL_HINT_MAIN_CALLBACK_RATE)) {
            എങ്കിൽ (interval == 0) {
                emscripten_set_main_loop_timing(EM_TIMING_SETTIMEOUT, 0);
            } അല്ലെങ്കിൽ {
                emscripten_set_main_loop_timing(EM_TIMING_RAF, interval);
            }
        }
    }

    തിരികെ true;
}

bool Emscripten_GLES_GetSwapInterval(SDL_VideoDevice *_this, പൂർണ്ണസംഖ്യ *interval)
{
    സ്ഥിരം പൂർണ്ണസംഖ്യ pending = Emscripten_GetPendingSwapInterval();
    എങ്കിൽ (pending >= 0) {
        *interval = pending;
        തിരികെ true;  // we're planning to set it to this once the system settles down.
    }

    പൂർണ്ണസംഖ്യ mode, മൂല്യം;

    emscripten_get_main_loop_timing(&mode, &മൂല്യം);

    എങ്കിൽ (mode == EM_TIMING_RAF) {
        *interval = മൂല്യം;
        തിരികെ true;
    } അല്ലെങ്കിൽ {
        *interval = 0;
        തിരികെ true;
    }
}

SDL_GLContext Emscripten_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *window_data;

    EmscriptenWebGLContextAttributes attribs;
    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context;

    emscripten_webgl_init_context_attributes(&attribs);

    attribs.alpha = _this->gl_config.alpha_size > 0;
    attribs.depth = _this->gl_config.depth_size > 0;
    attribs.stencil = _this->gl_config.stencil_size > 0;
    attribs.antialias = _this->gl_config.multisamplebuffers == 1;

    എങ്കിൽ (_this->gl_config.major_version == 3)
        attribs.majorVersion = 2; // WebGL 2.0 ~= GLES 3.0

    window_data = window->internal;

    എങ്കിൽ (window_data->gl_context) {
        SDL_SetError("Cannot create multiple webgl contexts per window");
        തിരികെ ശൂന്യ;
    }

    context = emscripten_webgl_create_context(window_data->canvas_id, &attribs);

    എങ്കിൽ (!context) {
        SDL_SetError("Could not create webgl context");
        തിരികെ ശൂന്യ;
    }

    എങ്കിൽ (emscripten_webgl_make_context_current(context) != EMSCRIPTEN_RESULT_SUCCESS) {
        emscripten_webgl_destroy_context(context);
        തിരികെ ശൂന്യ;
    }

    window_data->gl_context = (SDL_GLContext)context;

    തിരികെ (SDL_GLContext)context;
}

bool Emscripten_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_Window *window;

    // remove the context from its window
    വേണ്ടി (window = _this->windows; window; window = window->next) {
        SDL_WindowData *window_data = window->internal;

        എങ്കിൽ (window_data->gl_context == context) {
            window_data->gl_context = ശൂന്യ;
        }
    }

    emscripten_webgl_destroy_context((EMSCRIPTEN_WEBGL_CONTEXT_HANDLE)context);
    തിരികെ true;
}

bool Emscripten_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    എങ്കിൽ (emscripten_has_asyncify() && SDL_GetHintBoolean(SDL_HINT_EMSCRIPTEN_ASYNCIFY, true)) {
        // give back control to browser for screen refresh
        emscripten_sleep(0);
    }
    തിരികെ true;
}

bool Emscripten_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context)
{
    // it isn't possible to reuse contexts across canvases
    എങ്കിൽ (window && context) {
        SDL_WindowData *window_data = window->internal;

        എങ്കിൽ (context != window_data->gl_context) {
            തിരികെ SDL_SetError("Cannot make context current to another window");
        }
    }

    എങ്കിൽ (emscripten_webgl_make_context_current((EMSCRIPTEN_WEBGL_CONTEXT_HANDLE)context) != EMSCRIPTEN_RESULT_SUCCESS) {
        തിരികെ SDL_SetError("Unable to make context current");
    }
    തിരികെ true;
}

#endif // SDL_VIDEO_DRIVER_EMSCRIPTEN
