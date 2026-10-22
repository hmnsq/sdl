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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_EMSCRIPTEN

#ಅನ್ತರ್ಭಾವ <emscripten/emscripten.h>
#ಅನ್ತರ್ಭಾವ <emscripten/html5_webgl.h>
#ಅನ್ತರ್ಭಾವ <GLES2/gl2.h>

#ಅನ್ತರ್ಭಾವ "SDL_emscriptenvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_emscriptenopengles.h"
#ಅನ್ತರ್ಭಾವ "../../main/SDL_main_callbacks.h"

bool Emscripten_GLES_ತುಂಬು_Library(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಮಾರ್ಗ)
{
    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ Emscripten_GLES_UnloadLibrary(SDL_VideoDevice *_this)
{
}

SDL_Function_ಸೂಚಕ Emscripten_GLES_Get_Proc_ವಿಳಾಸ(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *proc)
{
    ಹಿಂತಿರುಗಿ emscripten_webgl_get_proc_ವಿಳಾಸ(proc);
}

bool Emscripten_GLES_ಗಣ_ಅದಲುಬದಲು_Interval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ interval)
{
    ಆದರೆ (interval < 0) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Late swap tearing currently unsupported");
    }

    ಆದರೆ (Emscripten_Should_ಗಣ_ಅದಲುಬದಲು_Interval(interval)) {
        // don't change the mainloop timing if the app is also driving a main callback with this hint,
        //  as we assume that was the more deliberate action.
        ಆದರೆ (!SDL_HasMainCallbacks() || !SDL_GetHint(SDL_HINT_MAIN_CALLBACK_ದರ)) {
            ಆದರೆ (interval == 0) {
                emscripten_ಗಣ_main_loop_timing(EM_TIMING_SETTIMEOUT, 0);
            } ಇಲ್ಲದಿದ್ದರೆ {
                emscripten_ಗಣ_main_loop_timing(EM_TIMING_RAF, interval);
            }
        }
    }

    ಹಿಂತಿರುಗಿ true;
}

bool Emscripten_GLES_Get_ಅದಲುಬದಲು_Interval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ *interval)
{
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ pending = Emscripten_Get_Pending_ಅದಲುಬದಲು_Interval();
    ಆದರೆ (pending >= 0) {
        *interval = pending;
        ಹಿಂತಿರುಗಿ true;  // we're planning to set it to this once the system settles down.
    }

    ಪೂರ್ಣಾಂಕ ಬಹುಲಕ, ಮೌಲ್ಯ;

    emscripten_get_main_loop_timing(&ಬಹುಲಕ, &ಮೌಲ್ಯ);

    ಆದರೆ (ಬಹುಲಕ == EM_TIMING_RAF) {
        *interval = ಮೌಲ್ಯ;
        ಹಿಂತಿರುಗಿ true;
    } ಇಲ್ಲದಿದ್ದರೆ {
        *interval = 0;
        ಹಿಂತಿರುಗಿ true;
    }
}

SDL_GLContext Emscripten_GLES_CreateContext(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ_2;

    Emscripten_Web_GLContext_ಗುಣಲಕ್ಷಣಗಳು attribs;
    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context;

    emscripten_webgl_init_context_ಗುಣಲಕ್ಷಣಗಳು(&attribs);

    attribs.alpha = _this->gl_config.alpha_ಗಾತ್ರ > 0;
    attribs.ಆಳ_2 = _this->gl_config.ಆಳ_ಗಾತ್ರ > 0;
    attribs.stencil = _this->gl_config.stencil_ಗಾತ್ರ > 0;
    attribs.antialias = _this->gl_config.multisamplebuffers == 1;

    ಆದರೆ (_this->gl_config.major_ಆವೃತ್ತಿ == 3)
        attribs.major_ಆವೃತ್ತಿ_2 = 2; // WebGL 2.0 ~= GLES 3.0

    ಕಿಟಕಿ_ದತ್ತಾಂಶ_2 = ಕಿಟಕಿ->ಆಂತರಿಕ;

    ಆದರೆ (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->gl_context) {
        SDL_ಗಣ_Error("Cannot create multiple webgl contexts per window");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    context = emscripten_webgl_create_context(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->canvas_id, &attribs);

    ಆದರೆ (!context) {
        SDL_ಗಣ_Error("Could not create webgl context");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಆದರೆ (emscripten_webgl_make_context_current(context) != EMSCRIPTEN_ಫಲಿತಾಂಶ_SUCCESS) {
        emscripten_webgl_destroy_context(context);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->gl_context = (SDL_GLContext)context;

    ಹಿಂತಿರುಗಿ (SDL_GLContext)context;
}

bool Emscripten_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_ಕಿಟಕಿ *ಕಿಟಕಿ;

    // remove the context from its window
    ಗಾಗಿ (ಕಿಟಕಿ = _this->windows; ಕಿಟಕಿ; ಕಿಟಕಿ = ಕಿಟಕಿ->ಮುಂದಿನ) {
        SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ_2 = ಕಿಟಕಿ->ಆಂತರಿಕ;

        ಆದರೆ (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->gl_context == context) {
            ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->gl_context = ಖಾಲಿ;
        }
    }

    emscripten_webgl_destroy_context((EMSCRIPTEN_WEBGL_CONTEXT_HANDLE)context);
    ಹಿಂತಿರುಗಿ true;
}

bool Emscripten_GLES_ಅದಲುಬದಲು_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    ಆದರೆ (emscripten_has_asyncify() && SDL_GetHintBoolean(SDL_HINT_EMSCRIPTEN_ASYNCIFY, true)) {
        // give back control to browser for screen refresh
        emscripten_sleep(0);
    }
    ಹಿಂತಿರುಗಿ true;
}

bool Emscripten_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_GLContext context)
{
    // it isn't possible to reuse contexts across canvases
    ಆದರೆ (ಕಿಟಕಿ && context) {
        SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ_2 = ಕಿಟಕಿ->ಆಂತರಿಕ;

        ಆದರೆ (context != ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->gl_context) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Cannot make context current to another window");
        }
    }

    ಆದರೆ (emscripten_webgl_make_context_current((EMSCRIPTEN_WEBGL_CONTEXT_HANDLE)context) != EMSCRIPTEN_ಫಲಿತಾಂಶ_SUCCESS) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Unable to make context current");
    }
    ಹಿಂತಿರುಗಿ true;
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_EMSCRIPTEN
