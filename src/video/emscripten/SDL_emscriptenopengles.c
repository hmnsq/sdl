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
#অন্তর্ভাৱ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_EMSCRIPTEN

#অন্তর্ভাৱ <emscripten/emscripten.h>
#অন্তর্ভাৱ <emscripten/html5_webgl.h>
#অন্তর্ভাৱ <GLES2/gl2.h>

#অন্তর্ভাৱ "SDL_emscriptenvideo.h"
#অন্তর্ভাৱ "SDL_emscriptenopengles.h"
#অন্তর্ভাৱ "../../main/SDL_main_callbacks.h"

bool Emscripten_GLES_LoadLibrary(SDL_VideoDevice *_this, ধ্রুৱ ৱর্ণ *path)
{
    ঘূৰাই true;
}

শূন্য Emscripten_GLES_UnloadLibrary(SDL_VideoDevice *_this)
{
}

SDL_FunctionPointer Emscripten_GLES_GetProcAddress(SDL_VideoDevice *_this, ধ্রুৱ ৱর্ণ *proc)
{
    ঘূৰাই emscripten_webgl_get_proc_address(proc);
}

bool Emscripten_GLES_SetSwapInterval(SDL_VideoDevice *_this, পূর্ণাঙ্ক interval)
{
    যদি (interval < 0) {
        ঘূৰাই SDL_SetError("Late swap tearing currently unsupported");
    }

    যদি (Emscripten_ShouldSetSwapInterval(interval)) {
        // don't change the mainloop timing if the app is also driving a main callback with this hint,
        //  as we assume that was the more deliberate action.
        যদি (!SDL_HasMainCallbacks() || !SDL_GetHint(SDL_HINT_MAIN_CALLBACK_RATE)) {
            যদি (interval == 0) {
                emscripten_set_main_loop_timing(EM_TIMING_SETTIMEOUT, 0);
            } অন্যথা {
                emscripten_set_main_loop_timing(EM_TIMING_RAF, interval);
            }
        }
    }

    ঘূৰাই true;
}

bool Emscripten_GLES_GetSwapInterval(SDL_VideoDevice *_this, পূর্ণাঙ্ক *interval)
{
    ধ্রুৱ পূর্ণাঙ্ক pending = Emscripten_GetPendingSwapInterval();
    যদি (pending >= 0) {
        *interval = pending;
        ঘূৰাই true;  // we're planning to set it to this once the system settles down.
    }

    পূর্ণাঙ্ক mode, মান;

    emscripten_get_main_loop_timing(&mode, &মান);

    যদি (mode == EM_TIMING_RAF) {
        *interval = মান;
        ঘূৰাই true;
    } অন্যথা {
        *interval = 0;
        ঘূৰাই true;
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

    যদি (_this->gl_config.major_version == 3)
        attribs.majorVersion = 2; // WebGL 2.0 ~= GLES 3.0

    window_data = window->internal;

    যদি (window_data->gl_context) {
        SDL_SetError("Cannot create multiple webgl contexts per window");
        ঘূৰাই রিক্ত;
    }

    context = emscripten_webgl_create_context(window_data->canvas_id, &attribs);

    যদি (!context) {
        SDL_SetError("Could not create webgl context");
        ঘূৰাই রিক্ত;
    }

    যদি (emscripten_webgl_make_context_current(context) != EMSCRIPTEN_RESULT_SUCCESS) {
        emscripten_webgl_destroy_context(context);
        ঘূৰাই রিক্ত;
    }

    window_data->gl_context = (SDL_GLContext)context;

    ঘূৰাই (SDL_GLContext)context;
}

bool Emscripten_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_Window *window;

    // remove the context from its window
    বাবে (window = _this->windows; window; window = window->next) {
        SDL_WindowData *window_data = window->internal;

        যদি (window_data->gl_context == context) {
            window_data->gl_context = রিক্ত;
        }
    }

    emscripten_webgl_destroy_context((EMSCRIPTEN_WEBGL_CONTEXT_HANDLE)context);
    ঘূৰাই true;
}

bool Emscripten_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    যদি (emscripten_has_asyncify() && SDL_GetHintBoolean(SDL_HINT_EMSCRIPTEN_ASYNCIFY, true)) {
        // give back control to browser for screen refresh
        emscripten_sleep(0);
    }
    ঘূৰাই true;
}

bool Emscripten_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context)
{
    // it isn't possible to reuse contexts across canvases
    যদি (window && context) {
        SDL_WindowData *window_data = window->internal;

        যদি (context != window_data->gl_context) {
            ঘূৰাই SDL_SetError("Cannot make context current to another window");
        }
    }

    যদি (emscripten_webgl_make_context_current((EMSCRIPTEN_WEBGL_CONTEXT_HANDLE)context) != EMSCRIPTEN_RESULT_SUCCESS) {
        ঘূৰাই SDL_SetError("Unable to make context current");
    }
    ঘূৰাই true;
}

#endif // SDL_VIDEO_DRIVER_EMSCRIPTEN
