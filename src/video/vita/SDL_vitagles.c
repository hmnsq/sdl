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

#إذا defined(SDL_VIDEO_DRIVER_VITA) && defined(SDL_VIDEO_VITA_PIB)
#ضمن <stdlib.h>
#ضمن <string.h>

#ضمن "SDL_vitavideo.h"

/*****************************************************************************/
// SDL OpenGL/OpenGL ES functions
/*****************************************************************************/
#تعریف_کړه EGLCHK(stmt)                           \
    افعل {                                       \
        EGLint err;                            \
                                               \
        stmt;                                  \
        err = eglGetError();                   \
        إذا (err != EGL_SUCCESS) {              \
            SDL_سېټ_Error("EGL error %d", err); \
            أرجع عدم;                          \
        }                                      \
    } طالما (0)

فراغ VITA_GLES_KeyboardCallback(Sce_Piglet_Pre_بدلون_معلومات *معلومات)
{
    SceCommonDialogUpdateParam commonDialogParam;
    SDL_zero(commonDialogParam);
    commonDialogParam.render_موخه.colorFormat = معلومات->colorFormat;
    commonDialogParam.render_موخه.surfaceType = معلومات->surfaceType;
    commonDialogParam.render_موخه.color_Surface_معلومات = معلومات->color_Surface_معلومات;
    commonDialogParam.render_موخه.ژوروالی_Surface_معلومات = معلومات->ژوروالی_Surface_معلومات;
    commonDialogParam.render_موخه.پلنوالی = معلومات->پلنوالی;
    commonDialogParam.render_موخه.لوړوالی = معلومات->لوړوالی;
    commonDialogParam.render_موخه.stride_دننه_Pixels = معلومات->stride_دننه_Pixels;
    commonDialogParam.displaySyncObject = معلومات->displaySyncObject;

    sceCommonDialogUpdate(&commonDialogParam);
}

bool VITA_GLES_بارول_Library(SDL_VideoDevice *_this, ثابت حرف *لار)
{
    pibInit(PIB_SHACCCG | PIB_GET_PROC_ADDR_CORE);
    أرجع true;
}

SDL_Function_اشاره_ګر VITA_GLES_Get_Proc_پته(SDL_VideoDevice *_this, ثابت حرف *proc)
{
    أرجع egl_Get_Proc_پته(proc);
}

فراغ VITA_GLES_UnloadLibrary(SDL_VideoDevice *_this)
{
    eglTerminate(_this->gl_معلومات->display);
}

ساكن EGLint پلنوالی = 960;
ساكن EGLint لوړوالی = 544;

SDL_GLContext VITA_GLES_CreateContext(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{

    SDL_کړکۍ_معلومات *wdata = کړکۍ->دننی;

    EGLint attribs[32];
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    EGLConfig config;
    EGLint عدد_configs;
    PFNEGLPIGLETVITASETPRESWAPCALLBACKSCEPROC pre_بدلون_Callback;
    صحيح i;

    ثابت EGLint contextAttribs[] = {
        EGL_CONTEXT_CLIENT_نسخه, 2,
        EGL_NONE
    };

    EGLCHK(display = eglGetDisplay(0));

    EGLCHK(eglInitialize(display, عدم, عدم));
    wdata->کاروي_gles = true;
    کړکۍ->flags |= SDL_کړکۍ_FULLSCREEN;

    EGLCHK(eglBindAPI(EGL_OPENGL_ES_API));

    i = 0;
    attribs[i++] = EGL_RED_اندازه;
    attribs[i++] = 8;
    attribs[i++] = EGL_GREEN_اندازه;
    attribs[i++] = 8;
    attribs[i++] = EGL_BLUE_اندازه;
    attribs[i++] = 8;
    attribs[i++] = EGL_ژوروالی_اندازه;
    attribs[i++] = 0;
    attribs[i++] = EGL_ALPHA_اندازه;
    attribs[i++] = 8;
    attribs[i++] = EGL_STENCIL_اندازه;
    attribs[i++] = 0;

    attribs[i++] = EGL_SURFACE_TYPE;
    attribs[i++] = 5;

    attribs[i++] = EGL_RENDERABLE_TYPE;
    attribs[i++] = EGL_OPENGL_ES2_بټ;

    attribs[i++] = EGL_CONFORMANT;
    attribs[i++] = EGL_OPENGL_ES2_بټ;

    attribs[i++] = EGL_NONE;

    EGLCHK(egl_ټاکنه_Config(display, attribs, &config, 1, &عدد_configs));

    إذا (عدد_configs == 0) {
        SDL_سېټ_Error("No valid EGL configs for requested mode");
        أرجع عدم;
    }

    EGLCHK(surface = egl_Create_کړکۍ_Surface(display, config, VITA_کړکۍ_960_X544, عدم));

    EGLCHK(context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs));

    EGLCHK(eglMakeCurrent(display, surface, surface, context));

    EGLCHK(eglQuerySurface(display, surface, EGL_پلنوالی, &پلنوالی));
    EGLCHK(eglQuerySurface(display, surface, EGL_لوړوالی, &لوړوالی));

    _this->gl_معلومات->display = display;
    _this->gl_معلومات->context = context;
    _this->gl_معلومات->surface = surface;

    pre_بدلون_Callback = (PFNEGLPIGLETVITASETPRESWAPCALLBACKSCEPROC)egl_Get_Proc_پته("eglPigletVitaSetPreSwapCallbackSCE");
    pre_بدلون_Callback(VITA_GLES_KeyboardCallback);

    أرجع context;
}

bool VITA_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_GLContext context)
{
    إذا (!eglMakeCurrent(_this->gl_معلومات->display, _this->gl_معلومات->surface,
                        _this->gl_معلومات->surface, _this->gl_معلومات->context)) {
        أرجع SDL_سېټ_Error("Unable to make EGL context current");
    }
    أرجع true;
}

bool VITA_GLES_سېټ_بدلون_Interval(SDL_VideoDevice *_this, صحيح interval)
{
    EGLBoolean حالت;
    حالت = egl_بدلون_Interval(_this->gl_معلومات->display, interval);
    إذا (حالت == EGL_TRUE) {
        // Return success to upper level
        _this->gl_معلومات->swapinterval = interval;
        أرجع true;
    }
    // Failed to set swap interval
    أرجع SDL_سېټ_Error("Unable to set the EGL swap interval");
}

bool VITA_GLES_Get_بدلون_Interval(SDL_VideoDevice *_this, صحيح *interval)
{
    *interval = _this->gl_معلومات->swapinterval;
    أرجع true;
}

bool VITA_GLES_بدلون_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    إذا (!egl_بدلون_Buffers(_this->gl_معلومات->display, _this->gl_معلومات->surface)) {
        أرجع SDL_سېټ_Error("eglSwapBuffers() failed");
    }
    أرجع true;
}

bool VITA_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_Video_معلومات *phdata = _this->دننی;
    EGLBoolean حالت;

    إذا (phdata->egl_initialized != true) {
        أرجع SDL_سېټ_Error("VITA: GLES initialization failed, no OpenGL ES support");
    }

    // Check if OpenGL ES connection has been initialized
    إذا (_this->gl_معلومات->display != EGL_NO_DISPLAY) {
        إذا (context != EGL_NO_CONTEXT) {
            حالت = eglDestroyContext(_this->gl_معلومات->display, context);
            إذا (حالت != EGL_TRUE) {
                // Error during OpenGL ES context destroying
                أرجع SDL_سېټ_Error("VITA: OpenGL ES context destroy error");
            }
        }
    }

    أرجع true;
}

#د_که_پای // SDL_VIDEO_DRIVER_VITA
