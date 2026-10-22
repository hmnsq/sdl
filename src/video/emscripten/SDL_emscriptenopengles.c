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

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_EMSCRIPTEN

#ضمن <emscripten/emscripten.h>
#ضمن <emscripten/html5_webgl.h>
#ضمن <GLES2/gl2.h>

#ضمن "SDL_emscriptenvideo.h"
#ضمن "SDL_emscriptenopengles.h"
#ضمن "../../main/SDL_main_callbacks.h"

bool Emscripten_GLES_لدو_Library(SDL_VideoDevice *_this, ثابت حرف *رستہ)
{
    أرجع true;
}

فراغ Emscripten_GLES_UnloadLibrary(SDL_VideoDevice *_this)
{
}

SDL_Function_اشارہ_گر Emscripten_GLES_Get_Proc_پتہ(SDL_VideoDevice *_this, ثابت حرف *proc)
{
    أرجع emscripten_webgl_get_proc_پتہ(proc);
}

bool Emscripten_GLES_سیٹ_وٹاندرا_Interval(SDL_VideoDevice *_this, صحيح interval)
{
    إذا (interval < 0) {
        أرجع SDL_سیٹ_Error("Late swap tearing currently unsupported");
    }

    إذا (Emscripten_Should_سیٹ_وٹاندرا_Interval(interval)) {
        // don't change the mainloop timing if the app is also driving a main callback with this hint,
        //  as we assume that was the more deliberate action.
        إذا (!SDL_HasMainCallbacks() || !SDL_GetHint(SDL_HINT_MAIN_CALLBACK_شرح)) {
            إذا (interval == 0) {
                emscripten_سیٹ_main_loop_timing(EM_TIMING_SETTIMEOUT, 0);
            } وإلا {
                emscripten_سیٹ_main_loop_timing(EM_TIMING_RAF, interval);
            }
        }
    }

    أرجع true;
}

bool Emscripten_GLES_Get_وٹاندرا_Interval(SDL_VideoDevice *_this, صحيح *interval)
{
    ثابت صحيح pending = Emscripten_Get_Pending_وٹاندرا_Interval();
    إذا (pending >= 0) {
        *interval = pending;
        أرجع true;  // we're planning to set it to this once the system settles down.
    }

    صحيح منوال, قدر;

    emscripten_get_main_loop_timing(&منوال, &قدر);

    إذا (منوال == EM_TIMING_RAF) {
        *interval = قدر;
        أرجع true;
    } وإلا {
        *interval = 0;
        أرجع true;
    }
}

SDL_GLContext Emscripten_GLES_CreateContext(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے *کھڑکی_انکڑے_2;

    Emscripten_Web_GLContext_گن attribs;
    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context;

    emscripten_webgl_init_context_گن(&attribs);

    attribs.alpha = _this->gl_config.alpha_ناپ > 0;
    attribs.ڈونگھائی_2 = _this->gl_config.ڈونگھائی_ناپ > 0;
    attribs.stencil = _this->gl_config.stencil_ناپ > 0;
    attribs.antialias = _this->gl_config.multisamplebuffers == 1;

    إذا (_this->gl_config.major_نسخہ == 3)
        attribs.major_نسخہ_2 = 2; // WebGL 2.0 ~= GLES 3.0

    کھڑکی_انکڑے_2 = کھڑکی->اندرونی;

    إذا (کھڑکی_انکڑے_2->gl_context) {
        SDL_سیٹ_Error("Cannot create multiple webgl contexts per window");
        أرجع عدم;
    }

    context = emscripten_webgl_create_context(کھڑکی_انکڑے_2->canvas_id, &attribs);

    إذا (!context) {
        SDL_سیٹ_Error("Could not create webgl context");
        أرجع عدم;
    }

    إذا (emscripten_webgl_make_context_current(context) != EMSCRIPTEN_نتیجہ_SUCCESS) {
        emscripten_webgl_destroy_context(context);
        أرجع عدم;
    }

    کھڑکی_انکڑے_2->gl_context = (SDL_GLContext)context;

    أرجع (SDL_GLContext)context;
}

bool Emscripten_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_کھڑکی *کھڑکی;

    // remove the context from its window
    لكل (کھڑکی = _this->windows; کھڑکی; کھڑکی = کھڑکی->اگلا) {
        SDL_کھڑکی_انکڑے *کھڑکی_انکڑے_2 = کھڑکی->اندرونی;

        إذا (کھڑکی_انکڑے_2->gl_context == context) {
            کھڑکی_انکڑے_2->gl_context = عدم;
        }
    }

    emscripten_webgl_destroy_context((EMSCRIPTEN_WEBGL_CONTEXT_HANDLE)context);
    أرجع true;
}

bool Emscripten_GLES_وٹاندرا_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    إذا (emscripten_has_asyncify() && SDL_GetHintBoolean(SDL_HINT_EMSCRIPTEN_ASYNCIFY, true)) {
        // give back control to browser for screen refresh
        emscripten_sleep(0);
    }
    أرجع true;
}

bool Emscripten_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_GLContext context)
{
    // it isn't possible to reuse contexts across canvases
    إذا (کھڑکی && context) {
        SDL_کھڑکی_انکڑے *کھڑکی_انکڑے_2 = کھڑکی->اندرونی;

        إذا (context != کھڑکی_انکڑے_2->gl_context) {
            أرجع SDL_سیٹ_Error("Cannot make context current to another window");
        }
    }

    إذا (emscripten_webgl_make_context_current((EMSCRIPTEN_WEBGL_CONTEXT_HANDLE)context) != EMSCRIPTEN_نتیجہ_SUCCESS) {
        أرجع SDL_سیٹ_Error("Unable to make context current");
    }
    أرجع true;
}

#جے_انت // SDL_VIDEO_DRIVER_EMSCRIPTEN
