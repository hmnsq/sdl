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
#include "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_EMSCRIPTEN

#include <emscripten/emscripten.h>
#include <emscripten/html5_webgl.h>
#include <GLES2/gl2.h>

#include "SDL_emscriptenvideo.h"
#include "SDL_emscriptenopengles.h"
#include "../../main/SDL_main_callbacks.h"

bool Emscripten_GLES_LoadLibrary(SDL_VideoDevice *_this, const char *path)
{
    반환 true;
}

void Emscripten_GLES_UnloadLibrary(SDL_VideoDevice *_this)
{
}

SDL_FunctionPointer Emscripten_GLES_GetProcAddress(SDL_VideoDevice *_this, const char *proc)
{
    반환 emscripten_webgl_get_proc_address(proc);
}

bool Emscripten_GLES_SetSwapInterval(SDL_VideoDevice *_this, 정수 interval)
{
    만약 (interval < 0) {
        반환 SDL_SetError("Late swap tearing currently unsupported");
    }

    만약 (Emscripten_ShouldSetSwapInterval(interval)) {
        // don't change the mainloop timing if the app is also driving a main callback with this hint,
        //  as we assume that was the more deliberate action.
        만약 (!SDL_HasMainCallbacks() || !SDL_GetHint(SDL_HINT_MAIN_CALLBACK_RATE)) {
            만약 (interval == 0) {
                emscripten_set_main_loop_timing(EM_TIMING_SETTIMEOUT, 0);
            } 아니면 {
                emscripten_set_main_loop_timing(EM_TIMING_RAF, interval);
            }
        }
    }

    반환 true;
}

bool Emscripten_GLES_GetSwapInterval(SDL_VideoDevice *_this, 정수 *interval)
{
    const 정수 pending = Emscripten_GetPendingSwapInterval();
    만약 (pending >= 0) {
        *interval = pending;
        반환 true;  // we're planning to set it to this once the system settles down.
    }

    정수 mode, value;

    emscripten_get_main_loop_timing(&mode, &value);

    만약 (mode == EM_TIMING_RAF) {
        *interval = value;
        반환 true;
    } 아니면 {
        *interval = 0;
        반환 true;
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

    만약 (_this->gl_config.major_version == 3)
        attribs.majorVersion = 2; // WebGL 2.0 ~= GLES 3.0

    window_data = window->internal;

    만약 (window_data->gl_context) {
        SDL_SetError("Cannot create multiple webgl contexts per window");
        반환 NULL;
    }

    context = emscripten_webgl_create_context(window_data->canvas_id, &attribs);

    만약 (!context) {
        SDL_SetError("Could not create webgl context");
        반환 NULL;
    }

    만약 (emscripten_webgl_make_context_current(context) != EMSCRIPTEN_RESULT_SUCCESS) {
        emscripten_webgl_destroy_context(context);
        반환 NULL;
    }

    window_data->gl_context = (SDL_GLContext)context;

    반환 (SDL_GLContext)context;
}

bool Emscripten_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_Window *window;

    // remove the context from its window
    위해 (window = _this->windows; window; window = window->next) {
        SDL_WindowData *window_data = window->internal;

        만약 (window_data->gl_context == context) {
            window_data->gl_context = NULL;
        }
    }

    emscripten_webgl_destroy_context((EMSCRIPTEN_WEBGL_CONTEXT_HANDLE)context);
    반환 true;
}

bool Emscripten_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    만약 (emscripten_has_asyncify() && SDL_GetHintBoolean(SDL_HINT_EMSCRIPTEN_ASYNCIFY, true)) {
        // give back control to browser for screen refresh
        emscripten_sleep(0);
    }
    반환 true;
}

bool Emscripten_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context)
{
    // it isn't possible to reuse contexts across canvases
    만약 (window && context) {
        SDL_WindowData *window_data = window->internal;

        만약 (context != window_data->gl_context) {
            반환 SDL_SetError("Cannot make context current to another window");
        }
    }

    만약 (emscripten_webgl_make_context_current((EMSCRIPTEN_WEBGL_CONTEXT_HANDLE)context) != EMSCRIPTEN_RESULT_SUCCESS) {
        반환 SDL_SetError("Unable to make context current");
    }
    반환 true;
}

#endif // SDL_VIDEO_DRIVER_EMSCRIPTEN
