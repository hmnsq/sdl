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
#अन्तर्भाव <emscripten/html5_webgl.h>
#अन्तर्भाव <GLES2/gl2.h>

#अन्तर्भाव "SDL_emscriptenvideo.h"
#अन्तर्भाव "SDL_emscriptenopengles.h"
#अन्तर्भाव "../../main/SDL_main_callbacks.h"

bool Emscripten_GLES_आरोपय_Library(SDL_VideoDevice *_this, ध्रुव वर्ण *मार्गः)
{
    प्रत्यागम true;
}

शून्य Emscripten_GLES_UnloadLibrary(SDL_VideoDevice *_this)
{
}

SDL_FunctionPointer Emscripten_GLES_Get_Proc_स्थानाङ्कः(SDL_VideoDevice *_this, ध्रुव वर्ण *proc)
{
    प्रत्यागम emscripten_webgl_get_proc_स्थानाङ्कः(proc);
}

bool Emscripten_GLES_समुच्चयः_Swap_Interval(SDL_VideoDevice *_this, पूर्णाङ्क interval)
{
    यदि (interval < 0) {
        प्रत्यागम SDL_समुच्चयः_Error("Late swap tearing currently unsupported");
    }

    यदि (Emscripten_Should_समुच्चयः_Swap_Interval(interval)) {
        // don't change the mainloop timing if the app is also driving a main callback with this hint,
        //  as we assume that was the more deliberate action.
        यदि (!SDL_HasMainCallbacks() || !SDL_GetHint(SDL_HINT_MAIN_CALLBACK_दरः)) {
            यदि (interval == 0) {
                emscripten_समुच्चयः_main_loop_timing(EM_TIMING_SETTIMEOUT, 0);
            } अन्यथा {
                emscripten_समुच्चयः_main_loop_timing(EM_TIMING_RAF, interval);
            }
        }
    }

    प्रत्यागम true;
}

bool Emscripten_GLES_GetSwapInterval(SDL_VideoDevice *_this, पूर्णाङ्क *interval)
{
    ध्रुव पूर्णाङ्क pending = Emscripten_GetPendingSwapInterval();
    यदि (pending >= 0) {
        *interval = pending;
        प्रत्यागम true;  // we're planning to set it to this once the system settles down.
    }

    पूर्णाङ्क बहुलकम्, मानम्;

    emscripten_get_main_loop_timing(&बहुलकम्, &मानम्);

    यदि (बहुलकम् == EM_TIMING_RAF) {
        *interval = मानम्;
        प्रत्यागम true;
    } अन्यथा {
        *interval = 0;
        प्रत्यागम true;
    }
}

SDL_GLContext Emscripten_GLES_CreateContext(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *गवाक्षः_दत्त_2;

    Emscripten_Web_GLContext_गुणाः attribs;
    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context;

    emscripten_webgl_init_context_गुणाः(&attribs);

    attribs.alpha = _this->gl_config.alpha_आकार > 0;
    attribs.गभीरता_2 = _this->gl_config.गभीरता_आकार > 0;
    attribs.stencil = _this->gl_config.stencil_आकार > 0;
    attribs.antialias = _this->gl_config.multisamplebuffers == 1;

    यदि (_this->gl_config.major_संस्करणम् == 3)
        attribs.major_संस्करणम्_2 = 2; // WebGL 2.0 ~= GLES 3.0

    गवाक्षः_दत्त_2 = गवाक्षः->आन्तरिकम्;

    यदि (गवाक्षः_दत्त_2->gl_context) {
        SDL_समुच्चयः_Error("Cannot create multiple webgl contexts per window");
        प्रत्यागम रिक्त;
    }

    context = emscripten_webgl_create_context(गवाक्षः_दत्त_2->canvas_id, &attribs);

    यदि (!context) {
        SDL_समुच्चयः_Error("Could not create webgl context");
        प्रत्यागम रिक्त;
    }

    यदि (emscripten_webgl_make_context_current(context) != EMSCRIPTEN_परिणाम_SUCCESS) {
        emscripten_webgl_destroy_context(context);
        प्रत्यागम रिक्त;
    }

    गवाक्षः_दत्त_2->gl_context = (SDL_GLContext)context;

    प्रत्यागम (SDL_GLContext)context;
}

bool Emscripten_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_गवाक्षः *गवाक्षः;

    // remove the context from its window
    प्रति (गवाक्षः = _this->windows; गवाक्षः; गवाक्षः = गवाक्षः->अग्र) {
        SDL_गवाक्षः_दत्त *गवाक्षः_दत्त_2 = गवाक्षः->आन्तरिकम्;

        यदि (गवाक्षः_दत्त_2->gl_context == context) {
            गवाक्षः_दत्त_2->gl_context = रिक्त;
        }
    }

    emscripten_webgl_destroy_context((EMSCRIPTEN_WEBGL_CONTEXT_HANDLE)context);
    प्रत्यागम true;
}

bool Emscripten_GLES_Swap_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    यदि (emscripten_has_asyncify() && SDL_GetHintBoolean(SDL_HINT_EMSCRIPTEN_ASYNCIFY, true)) {
        // give back control to browser for screen refresh
        emscripten_sleep(0);
    }
    प्रत्यागम true;
}

bool Emscripten_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_GLContext context)
{
    // it isn't possible to reuse contexts across canvases
    यदि (गवाक्षः && context) {
        SDL_गवाक्षः_दत्त *गवाक्षः_दत्त_2 = गवाक्षः->आन्तरिकम्;

        यदि (context != गवाक्षः_दत्त_2->gl_context) {
            प्रत्यागम SDL_समुच्चयः_Error("Cannot make context current to another window");
        }
    }

    यदि (emscripten_webgl_make_context_current((EMSCRIPTEN_WEBGL_CONTEXT_HANDLE)context) != EMSCRIPTEN_परिणाम_SUCCESS) {
        प्रत्यागम SDL_समुच्चयः_Error("Unable to make context current");
    }
    प्रत्यागम true;
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_EMSCRIPTEN
