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
#అన్తర్భావ <emscripten/html5_webgl.h>
#అన్తర్భావ <GLES2/gl2.h>

#అన్తర్భావ "SDL_emscriptenvideo.h"
#అన్తర్భావ "SDL_emscriptenopengles.h"
#అన్తర్భావ "../../main/SDL_main_callbacks.h"

bool Emscripten_GLES_ఎక్కించు_Library(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *మార్గం)
{
    తిరిగి true;
}

శూన్య Emscripten_GLES_UnloadLibrary(SDL_VideoDevice *_this)
{
}

SDL_Function_సూచిక Emscripten_GLES_Get_Proc_చిరునామా(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *proc)
{
    తిరిగి emscripten_webgl_get_proc_చిరునామా(proc);
}

bool Emscripten_GLES_సమితి_మార్పిడి_Interval(SDL_VideoDevice *_this, పూర్ణాంకం interval)
{
    ఒకవేళ (interval < 0) {
        తిరిగి SDL_సమితి_Error("Late swap tearing currently unsupported");
    }

    ఒకవేళ (Emscripten_Should_సమితి_మార్పిడి_Interval(interval)) {
        // don't change the mainloop timing if the app is also driving a main callback with this hint,
        //  as we assume that was the more deliberate action.
        ఒకవేళ (!SDL_HasMainCallbacks() || !SDL_GetHint(SDL_HINT_MAIN_CALLBACK_రేటు)) {
            ఒకవేళ (interval == 0) {
                emscripten_సమితి_main_loop_timing(EM_TIMING_SETTIMEOUT, 0);
            } లేకపోతే {
                emscripten_సమితి_main_loop_timing(EM_TIMING_RAF, interval);
            }
        }
    }

    తిరిగి true;
}

bool Emscripten_GLES_Get_మార్పిడి_Interval(SDL_VideoDevice *_this, పూర్ణాంకం *interval)
{
    స్థిరరాశి పూర్ణాంకం pending = Emscripten_Get_Pending_మార్పిడి_Interval();
    ఒకవేళ (pending >= 0) {
        *interval = pending;
        తిరిగి true;  // we're planning to set it to this once the system settles down.
    }

    పూర్ణాంకం బహుళకం, విలువ;

    emscripten_get_main_loop_timing(&బహుళకం, &విలువ);

    ఒకవేళ (బహుళకం == EM_TIMING_RAF) {
        *interval = విలువ;
        తిరిగి true;
    } లేకపోతే {
        *interval = 0;
        తిరిగి true;
    }
}

SDL_GLContext Emscripten_GLES_CreateContext(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం_2;

    Emscripten_Web_GLContext_లక్షణాలు attribs;
    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context;

    emscripten_webgl_init_context_లక్షణాలు(&attribs);

    attribs.alpha = _this->gl_config.alpha_కొలత > 0;
    attribs.లోతు_2 = _this->gl_config.లోతు_కొలత > 0;
    attribs.stencil = _this->gl_config.stencil_కొలత > 0;
    attribs.antialias = _this->gl_config.multisamplebuffers == 1;

    ఒకవేళ (_this->gl_config.major_సంస్కరణ == 3)
        attribs.major_సంస్కరణ_2 = 2; // WebGL 2.0 ~= GLES 3.0

    కిటికీ_దత్తాంశం_2 = కిటికీ->అంతర్గత;

    ఒకవేళ (కిటికీ_దత్తాంశం_2->gl_context) {
        SDL_సమితి_Error("Cannot create multiple webgl contexts per window");
        తిరిగి ఖాళీ;
    }

    context = emscripten_webgl_create_context(కిటికీ_దత్తాంశం_2->canvas_id, &attribs);

    ఒకవేళ (!context) {
        SDL_సమితి_Error("Could not create webgl context");
        తిరిగి ఖాళీ;
    }

    ఒకవేళ (emscripten_webgl_make_context_current(context) != EMSCRIPTEN_ఫలితం_SUCCESS) {
        emscripten_webgl_destroy_context(context);
        తిరిగి ఖాళీ;
    }

    కిటికీ_దత్తాంశం_2->gl_context = (SDL_GLContext)context;

    తిరిగి (SDL_GLContext)context;
}

bool Emscripten_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_కిటికీ *కిటికీ;

    // remove the context from its window
    కొరకు (కిటికీ = _this->windows; కిటికీ; కిటికీ = కిటికీ->తదుపరి) {
        SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం_2 = కిటికీ->అంతర్గత;

        ఒకవేళ (కిటికీ_దత్తాంశం_2->gl_context == context) {
            కిటికీ_దత్తాంశం_2->gl_context = ఖాళీ;
        }
    }

    emscripten_webgl_destroy_context((EMSCRIPTEN_WEBGL_CONTEXT_HANDLE)context);
    తిరిగి true;
}

bool Emscripten_GLES_మార్పిడి_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    ఒకవేళ (emscripten_has_asyncify() && SDL_GetHintBoolean(SDL_HINT_EMSCRIPTEN_ASYNCIFY, true)) {
        // give back control to browser for screen refresh
        emscripten_sleep(0);
    }
    తిరిగి true;
}

bool Emscripten_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_GLContext context)
{
    // it isn't possible to reuse contexts across canvases
    ఒకవేళ (కిటికీ && context) {
        SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం_2 = కిటికీ->అంతర్గత;

        ఒకవేళ (context != కిటికీ_దత్తాంశం_2->gl_context) {
            తిరిగి SDL_సమితి_Error("Cannot make context current to another window");
        }
    }

    ఒకవేళ (emscripten_webgl_make_context_current((EMSCRIPTEN_WEBGL_CONTEXT_HANDLE)context) != EMSCRIPTEN_ఫలితం_SUCCESS) {
        తిరిగి SDL_సమితి_Error("Unable to make context current");
    }
    తిరిగి true;
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_EMSCRIPTEN
