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
#समावेश <emscripten/html5_webgl.h>
#समावेश <GLES2/gl2.h>

#समावेश "SDL_emscriptenvideo.h"
#समावेश "SDL_emscriptenopengles.h"
#समावेश "../../main/SDL_main_callbacks.h"

bool Emscripten_GLES_LoadLibrary(SDL_VideoDevice *_this, स्थिर अक्षर *path)
{
    वापस true;
}

व्योम Emscripten_GLES_UnloadLibrary(SDL_VideoDevice *_this)
{
}

SDL_FunctionPointer Emscripten_GLES_GetProcAddress(SDL_VideoDevice *_this, स्थिर अक्षर *proc)
{
    वापस emscripten_webgl_get_proc_address(proc);
}

bool Emscripten_GLES_SetSwapInterval(SDL_VideoDevice *_this, पूर्णांक interval)
{
    अगर (interval < 0) {
        वापस SDL_SetError("Late swap tearing currently unsupported");
    }

    अगर (Emscripten_ShouldSetSwapInterval(interval)) {
        // don't change the mainloop timing if the app is also driving a main callback with this hint,
        //  as we assume that was the more deliberate action.
        अगर (!SDL_HasMainCallbacks() || !SDL_GetHint(SDL_HINT_MAIN_CALLBACK_RATE)) {
            अगर (interval == 0) {
                emscripten_set_main_loop_timing(EM_TIMING_SETTIMEOUT, 0);
            } अन्यथा {
                emscripten_set_main_loop_timing(EM_TIMING_RAF, interval);
            }
        }
    }

    वापस true;
}

bool Emscripten_GLES_GetSwapInterval(SDL_VideoDevice *_this, पूर्णांक *interval)
{
    स्थिर पूर्णांक pending = Emscripten_GetPendingSwapInterval();
    अगर (pending >= 0) {
        *interval = pending;
        वापस true;  // we're planning to set it to this once the system settles down.
    }

    पूर्णांक mode, मूल्य;

    emscripten_get_main_loop_timing(&mode, &मूल्य);

    अगर (mode == EM_TIMING_RAF) {
        *interval = मूल्य;
        वापस true;
    } अन्यथा {
        *interval = 0;
        वापस true;
    }
}

SDL_GLContext Emscripten_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_तथ्य *window_तथ्य_2;

    EmscriptenWebGLContextAttributes attribs;
    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context;

    emscripten_webgl_init_context_attributes(&attribs);

    attribs.alpha = _this->gl_config.alpha_आकार > 0;
    attribs.depth = _this->gl_config.depth_आकार > 0;
    attribs.stencil = _this->gl_config.stencil_आकार > 0;
    attribs.antialias = _this->gl_config.multisamplebuffers == 1;

    अगर (_this->gl_config.major_version == 3)
        attribs.majorVersion = 2; // WebGL 2.0 ~= GLES 3.0

    window_तथ्य_2 = window->internal;

    अगर (window_तथ्य_2->gl_context) {
        SDL_SetError("Cannot create multiple webgl contexts per window");
        वापस शून्य;
    }

    context = emscripten_webgl_create_context(window_तथ्य_2->canvas_id, &attribs);

    अगर (!context) {
        SDL_SetError("Could not create webgl context");
        वापस शून्य;
    }

    अगर (emscripten_webgl_make_context_current(context) != EMSCRIPTEN_परिणाम_SUCCESS) {
        emscripten_webgl_destroy_context(context);
        वापस शून्य;
    }

    window_तथ्य_2->gl_context = (SDL_GLContext)context;

    वापस (SDL_GLContext)context;
}

bool Emscripten_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_Window *window;

    // remove the context from its window
    क्रम (window = _this->windows; window; window = window->अग्र) {
        SDL_Window_तथ्य *window_तथ्य_2 = window->internal;

        अगर (window_तथ्य_2->gl_context == context) {
            window_तथ्य_2->gl_context = शून्य;
        }
    }

    emscripten_webgl_destroy_context((EMSCRIPTEN_WEBGL_CONTEXT_HANDLE)context);
    वापस true;
}

bool Emscripten_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    अगर (emscripten_has_asyncify() && SDL_GetHintBoolean(SDL_HINT_EMSCRIPTEN_ASYNCIFY, true)) {
        // give back control to browser for screen refresh
        emscripten_sleep(0);
    }
    वापस true;
}

bool Emscripten_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context)
{
    // it isn't possible to reuse contexts across canvases
    अगर (window && context) {
        SDL_Window_तथ्य *window_तथ्य_2 = window->internal;

        अगर (context != window_तथ्य_2->gl_context) {
            वापस SDL_SetError("Cannot make context current to another window");
        }
    }

    अगर (emscripten_webgl_make_context_current((EMSCRIPTEN_WEBGL_CONTEXT_HANDLE)context) != EMSCRIPTEN_परिणाम_SUCCESS) {
        वापस SDL_SetError("Unable to make context current");
    }
    वापस true;
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_EMSCRIPTEN
