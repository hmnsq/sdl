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

#ifdef SDL_VIDEO_DRIVER_EMSCRIPTEN

#ضمن <emscripten/emscripten.h>
#ضمن <emscripten/html5_webgl.h>
#ضمن <GLES2/gl2.h>

#ضمن "SDL_emscriptenvideo.h"
#ضمن "SDL_emscriptenopengles.h"
#ضمن "../../main/SDL_main_callbacks.h"

bool Emscripten_GLES_LoadLibrary(SDL_VideoDevice *_this, ثابت حرف *path)
{
    أرجع true;
}

فراغ Emscripten_GLES_UnloadLibrary(SDL_VideoDevice *_this)
{
}

SDL_FunctionPointer Emscripten_GLES_GetProcAddress(SDL_VideoDevice *_this, ثابت حرف *proc)
{
    أرجع emscripten_webgl_get_proc_address(proc);
}

bool Emscripten_GLES_SetSwapInterval(SDL_VideoDevice *_this, صحيح interval)
{
    إذا (interval < 0) {
        أرجع SDL_SetError("Late swap tearing currently unsupported");
    }

    إذا (Emscripten_ShouldSetSwapInterval(interval)) {
        // don't change the mainloop timing if the app is also driving a main callback with this hint,
        //  as we assume that was the more deliberate action.
        إذا (!SDL_HasMainCallbacks() || !SDL_GetHint(SDL_HINT_MAIN_CALLBACK_RATE)) {
            إذا (interval == 0) {
                emscripten_set_main_loop_timing(EM_TIMING_SETTIMEOUT, 0);
            } وإلا {
                emscripten_set_main_loop_timing(EM_TIMING_RAF, interval);
            }
        }
    }

    أرجع true;
}

bool Emscripten_GLES_GetSwapInterval(SDL_VideoDevice *_this, صحيح *interval)
{
    ثابت صحيح pending = Emscripten_GetPendingSwapInterval();
    إذا (pending >= 0) {
        *interval = pending;
        أرجع true;  // we're planning to set it to this once the system settles down.
    }

    صحيح mode, قىممەت;

    emscripten_get_main_loop_timing(&mode, &قىممەت);

    إذا (mode == EM_TIMING_RAF) {
        *interval = قىممەت;
        أرجع true;
    } وإلا {
        *interval = 0;
        أرجع true;
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

    إذا (_this->gl_config.major_version == 3)
        attribs.majorVersion = 2; // WebGL 2.0 ~= GLES 3.0

    window_data = window->internal;

    إذا (window_data->gl_context) {
        SDL_SetError("Cannot create multiple webgl contexts per window");
        أرجع عدم;
    }

    context = emscripten_webgl_create_context(window_data->canvas_id, &attribs);

    إذا (!context) {
        SDL_SetError("Could not create webgl context");
        أرجع عدم;
    }

    إذا (emscripten_webgl_make_context_current(context) != EMSCRIPTEN_RESULT_SUCCESS) {
        emscripten_webgl_destroy_context(context);
        أرجع عدم;
    }

    window_data->gl_context = (SDL_GLContext)context;

    أرجع (SDL_GLContext)context;
}

bool Emscripten_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_Window *window;

    // remove the context from its window
    لكل (window = _this->windows; window; window = window->next) {
        SDL_WindowData *window_data = window->internal;

        إذا (window_data->gl_context == context) {
            window_data->gl_context = عدم;
        }
    }

    emscripten_webgl_destroy_context((EMSCRIPTEN_WEBGL_CONTEXT_HANDLE)context);
    أرجع true;
}

bool Emscripten_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    إذا (emscripten_has_asyncify() && SDL_GetHintBoolean(SDL_HINT_EMSCRIPTEN_ASYNCIFY, true)) {
        // give back control to browser for screen refresh
        emscripten_sleep(0);
    }
    أرجع true;
}

bool Emscripten_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context)
{
    // it isn't possible to reuse contexts across canvases
    إذا (window && context) {
        SDL_WindowData *window_data = window->internal;

        إذا (context != window_data->gl_context) {
            أرجع SDL_SetError("Cannot make context current to another window");
        }
    }

    إذا (emscripten_webgl_make_context_current((EMSCRIPTEN_WEBGL_CONTEXT_HANDLE)context) != EMSCRIPTEN_RESULT_SUCCESS) {
        أرجع SDL_SetError("Unable to make context current");
    }
    أرجع true;
}

#endif // SDL_VIDEO_DRIVER_EMSCRIPTEN
