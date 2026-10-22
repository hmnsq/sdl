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
#شامل "SDL_internal.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_EMSCRIPTEN

#شامل <emscripten/emscripten.h>
#شامل <emscripten/html5_webgl.h>
#شامل <GLES2/gl2.h>

#شامل "SDL_emscriptenvideo.h"
#شامل "SDL_emscriptenopengles.h"
#شامل "../../main/SDL_main_callbacks.h"

bool Emscripten_GLES_بھرو_Library(SDL_VideoDevice *_this, ثابت حرف *راستہ)
{
    واپس true;
}

خالی Emscripten_GLES_UnloadLibrary(SDL_VideoDevice *_this)
{
}

SDL_Function_اشارہ_گر Emscripten_GLES_Get_Proc_پتہ(SDL_VideoDevice *_this, ثابت حرف *proc)
{
    واپس emscripten_webgl_get_proc_پتہ(proc);
}

bool Emscripten_GLES_سیٹ_تبادلہ_Interval(SDL_VideoDevice *_this, صحیح interval)
{
    اگر (interval < 0) {
        واپس SDL_سیٹ_Error("Late swap tearing currently unsupported");
    }

    اگر (Emscripten_Should_سیٹ_تبادلہ_Interval(interval)) {
        // don't change the mainloop timing if the app is also driving a main callback with this hint,
        //  as we assume that was the more deliberate action.
        اگر (!SDL_HasMainCallbacks() || !SDL_GetHint(SDL_HINT_MAIN_CALLBACK_شرح)) {
            اگر (interval == 0) {
                emscripten_سیٹ_main_loop_timing(EM_TIMING_SETTIMEOUT, 0);
            } ورنہ {
                emscripten_سیٹ_main_loop_timing(EM_TIMING_RAF, interval);
            }
        }
    }

    واپس true;
}

bool Emscripten_GLES_Get_تبادلہ_Interval(SDL_VideoDevice *_this, صحیح *interval)
{
    ثابت صحیح pending = Emscripten_Get_Pending_تبادلہ_Interval();
    اگر (pending >= 0) {
        *interval = pending;
        واپس true;  // we're planning to set it to this once the system settles down.
    }

    صحیح منوال, قدر;

    emscripten_get_main_loop_timing(&منوال, &قدر);

    اگر (منوال == EM_TIMING_RAF) {
        *interval = قدر;
        واپس true;
    } ورنہ {
        *interval = 0;
        واپس true;
    }
}

SDL_GLContext Emscripten_GLES_CreateContext(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *کھڑکی_ڈیٹا_2;

    Emscripten_Web_GLContext_اوصاف attribs;
    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context;

    emscripten_webgl_init_context_اوصاف(&attribs);

    attribs.alpha = _this->gl_config.alpha_سائز > 0;
    attribs.گہرائی_2 = _this->gl_config.گہرائی_سائز > 0;
    attribs.stencil = _this->gl_config.stencil_سائز > 0;
    attribs.antialias = _this->gl_config.multisamplebuffers == 1;

    اگر (_this->gl_config.major_نسخہ == 3)
        attribs.major_نسخہ_2 = 2; // WebGL 2.0 ~= GLES 3.0

    کھڑکی_ڈیٹا_2 = کھڑکی->اندرونی_2;

    اگر (کھڑکی_ڈیٹا_2->gl_context) {
        SDL_سیٹ_Error("Cannot create multiple webgl contexts per window");
        واپس تہی;
    }

    context = emscripten_webgl_create_context(کھڑکی_ڈیٹا_2->canvas_id, &attribs);

    اگر (!context) {
        SDL_سیٹ_Error("Could not create webgl context");
        واپس تہی;
    }

    اگر (emscripten_webgl_make_context_current(context) != EMSCRIPTEN_نتیجہ_SUCCESS) {
        emscripten_webgl_destroy_context(context);
        واپس تہی;
    }

    کھڑکی_ڈیٹا_2->gl_context = (SDL_GLContext)context;

    واپس (SDL_GLContext)context;
}

bool Emscripten_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_کھڑکی *کھڑکی;

    // remove the context from its window
    برائے (کھڑکی = _this->windows; کھڑکی; کھڑکی = کھڑکی->اگلا) {
        SDL_کھڑکی_ڈیٹا *کھڑکی_ڈیٹا_2 = کھڑکی->اندرونی_2;

        اگر (کھڑکی_ڈیٹا_2->gl_context == context) {
            کھڑکی_ڈیٹا_2->gl_context = تہی;
        }
    }

    emscripten_webgl_destroy_context((EMSCRIPTEN_WEBGL_CONTEXT_HANDLE)context);
    واپس true;
}

bool Emscripten_GLES_تبادلہ_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    اگر (emscripten_has_asyncify() && SDL_GetHintBoolean(SDL_HINT_EMSCRIPTEN_ASYNCIFY, true)) {
        // give back control to browser for screen refresh
        emscripten_sleep(0);
    }
    واپس true;
}

bool Emscripten_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_GLContext context)
{
    // it isn't possible to reuse contexts across canvases
    اگر (کھڑکی && context) {
        SDL_کھڑکی_ڈیٹا *کھڑکی_ڈیٹا_2 = کھڑکی->اندرونی_2;

        اگر (context != کھڑکی_ڈیٹا_2->gl_context) {
            واپس SDL_سیٹ_Error("Cannot make context current to another window");
        }
    }

    اگر (emscripten_webgl_make_context_current((EMSCRIPTEN_WEBGL_CONTEXT_HANDLE)context) != EMSCRIPTEN_نتیجہ_SUCCESS) {
        واپس SDL_سیٹ_Error("Unable to make context current");
    }
    واپس true;
}

#اگر_ختم // SDL_VIDEO_DRIVER_EMSCRIPTEN
