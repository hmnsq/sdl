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
#অন্তর্ভাব "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_EMSCRIPTEN

#অন্তর্ভাব <emscripten/emscripten.h>
#অন্তর্ভাব <emscripten/html5_webgl.h>
#অন্তর্ভাব <GLES2/gl2.h>

#অন্তর্ভাব "SDL_emscriptenvideo.h"
#অন্তর্ভাব "SDL_emscriptenopengles.h"
#অন্তর্ভাব "../../main/SDL_main_callbacks.h"

bool Emscripten_GLES_LoadLibrary(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *path)
{
    ফেরত true;
}

শূন্য Emscripten_GLES_UnloadLibrary(SDL_VideoDevice *_this)
{
}

SDL_FunctionPointer Emscripten_GLES_GetProcAddress(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *proc)
{
    ফেরত emscripten_webgl_get_proc_address(proc);
}

bool Emscripten_GLES_SetSwapInterval(SDL_VideoDevice *_this, পূর্ণসংখ্যা interval)
{
    যদি (interval < 0) {
        ফেরত SDL_SetError("Late swap tearing currently unsupported");
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

    ফেরত true;
}

bool Emscripten_GLES_GetSwapInterval(SDL_VideoDevice *_this, পূর্ণসংখ্যা *interval)
{
    ধ্রুবক পূর্ণসংখ্যা pending = Emscripten_GetPendingSwapInterval();
    যদি (pending >= 0) {
        *interval = pending;
        ফেরত true;  // we're planning to set it to this once the system settles down.
    }

    পূর্ণসংখ্যা mode, মান;

    emscripten_get_main_loop_timing(&mode, &মান);

    যদি (mode == EM_TIMING_RAF) {
        *interval = মান;
        ফেরত true;
    } অন্যথা {
        *interval = 0;
        ফেরত true;
    }
}

SDL_GLContext Emscripten_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_তথ্য *window_তথ্য_2;

    EmscriptenWebGLContextAttributes attribs;
    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context;

    emscripten_webgl_init_context_attributes(&attribs);

    attribs.alpha = _this->gl_config.alpha_আকার > 0;
    attribs.depth = _this->gl_config.depth_আকার > 0;
    attribs.stencil = _this->gl_config.stencil_আকার > 0;
    attribs.antialias = _this->gl_config.multisamplebuffers == 1;

    যদি (_this->gl_config.major_version == 3)
        attribs.majorVersion = 2; // WebGL 2.0 ~= GLES 3.0

    window_তথ্য_2 = window->internal;

    যদি (window_তথ্য_2->gl_context) {
        SDL_SetError("Cannot create multiple webgl contexts per window");
        ফেরত ফাঁকা;
    }

    context = emscripten_webgl_create_context(window_তথ্য_2->canvas_id, &attribs);

    যদি (!context) {
        SDL_SetError("Could not create webgl context");
        ফেরত ফাঁকা;
    }

    যদি (emscripten_webgl_make_context_current(context) != EMSCRIPTEN_ফলাফল_SUCCESS) {
        emscripten_webgl_destroy_context(context);
        ফেরত ফাঁকা;
    }

    window_তথ্য_2->gl_context = (SDL_GLContext)context;

    ফেরত (SDL_GLContext)context;
}

bool Emscripten_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_Window *window;

    // remove the context from its window
    জন্য (window = _this->windows; window; window = window->পরবর্তী) {
        SDL_Window_তথ্য *window_তথ্য_2 = window->internal;

        যদি (window_তথ্য_2->gl_context == context) {
            window_তথ্য_2->gl_context = ফাঁকা;
        }
    }

    emscripten_webgl_destroy_context((EMSCRIPTEN_WEBGL_CONTEXT_HANDLE)context);
    ফেরত true;
}

bool Emscripten_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    যদি (emscripten_has_asyncify() && SDL_GetHintBoolean(SDL_HINT_EMSCRIPTEN_ASYNCIFY, true)) {
        // give back control to browser for screen refresh
        emscripten_sleep(0);
    }
    ফেরত true;
}

bool Emscripten_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context)
{
    // it isn't possible to reuse contexts across canvases
    যদি (window && context) {
        SDL_Window_তথ্য *window_তথ্য_2 = window->internal;

        যদি (context != window_তথ্য_2->gl_context) {
            ফেরত SDL_SetError("Cannot make context current to another window");
        }
    }

    যদি (emscripten_webgl_make_context_current((EMSCRIPTEN_WEBGL_CONTEXT_HANDLE)context) != EMSCRIPTEN_ফলাফল_SUCCESS) {
        ফেরত SDL_SetError("Unable to make context current");
    }
    ফেরত true;
}

#endif // SDL_VIDEO_DRIVER_EMSCRIPTEN
