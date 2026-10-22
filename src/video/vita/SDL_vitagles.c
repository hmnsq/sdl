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
#تعریف_کرو EGLCHK(stmt)                           \
    افعل {                                       \
        EGLint err;                            \
                                               \
        stmt;                                  \
        err = eglGetError();                   \
        إذا (err != EGL_SUCCESS) {              \
            SDL_سیٹ_Error("EGL error %d", err); \
            أرجع عدم;                          \
        }                                      \
    } طالما (0)

فراغ VITA_GLES_KeyboardCallback(Sce_Piglet_Pre_وٹاندرا_انکڑے *انکڑے)
{
    SceCommonDialogUpdateParam commonDialogParam;
    SDL_zero(commonDialogParam);
    commonDialogParam.render_نشانہ.colorFormat = انکڑے->colorFormat;
    commonDialogParam.render_نشانہ.surfaceType = انکڑے->surfaceType;
    commonDialogParam.render_نشانہ.color_Surface_انکڑے = انکڑے->color_Surface_انکڑے;
    commonDialogParam.render_نشانہ.ڈونگھائی_Surface_انکڑے = انکڑے->ڈونگھائی_Surface_انکڑے;
    commonDialogParam.render_نشانہ.چوڑائی = انکڑے->چوڑائی;
    commonDialogParam.render_نشانہ.اچائی = انکڑے->اچائی;
    commonDialogParam.render_نشانہ.stride_وچ_Pixels = انکڑے->stride_وچ_Pixels;
    commonDialogParam.displaySyncObject = انکڑے->displaySyncObject;

    sceCommonDialogUpdate(&commonDialogParam);
}

bool VITA_GLES_لدو_Library(SDL_VideoDevice *_this, ثابت حرف *رستہ)
{
    pibInit(PIB_SHACCCG | PIB_GET_PROC_ADDR_CORE);
    أرجع true;
}

SDL_Function_اشارہ_گر VITA_GLES_Get_Proc_پتہ(SDL_VideoDevice *_this, ثابت حرف *proc)
{
    أرجع egl_Get_Proc_پتہ(proc);
}

فراغ VITA_GLES_UnloadLibrary(SDL_VideoDevice *_this)
{
    eglTerminate(_this->gl_انکڑے->display);
}

ساكن EGLint چوڑائی = 960;
ساكن EGLint اچائی = 544;

SDL_GLContext VITA_GLES_CreateContext(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{

    SDL_کھڑکی_انکڑے *wdata = کھڑکی->اندرونی;

    EGLint attribs[32];
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    EGLConfig config;
    EGLint عدد_configs;
    PFNEGLPIGLETVITASETPRESWAPCALLBACKSCEPROC pre_وٹاندرا_Callback;
    صحيح i;

    ثابت EGLint contextAttribs[] = {
        EGL_CONTEXT_CLIENT_نسخہ, 2,
        EGL_NONE
    };

    EGLCHK(display = eglGetDisplay(0));

    EGLCHK(eglInitialize(display, عدم, عدم));
    wdata->ورتدا_gles = true;
    کھڑکی->flags |= SDL_کھڑکی_FULLSCREEN;

    EGLCHK(eglBindAPI(EGL_OPENGL_ES_API));

    i = 0;
    attribs[i++] = EGL_RED_ناپ;
    attribs[i++] = 8;
    attribs[i++] = EGL_GREEN_ناپ;
    attribs[i++] = 8;
    attribs[i++] = EGL_BLUE_ناپ;
    attribs[i++] = 8;
    attribs[i++] = EGL_ڈونگھائی_ناپ;
    attribs[i++] = 0;
    attribs[i++] = EGL_ALPHA_ناپ;
    attribs[i++] = 8;
    attribs[i++] = EGL_STENCIL_ناپ;
    attribs[i++] = 0;

    attribs[i++] = EGL_SURFACE_TYPE;
    attribs[i++] = 5;

    attribs[i++] = EGL_RENDERABLE_TYPE;
    attribs[i++] = EGL_OPENGL_ES2_ثنائی_ہندسہ;

    attribs[i++] = EGL_CONFORMANT;
    attribs[i++] = EGL_OPENGL_ES2_ثنائی_ہندسہ;

    attribs[i++] = EGL_NONE;

    EGLCHK(egl_چنو_Config(display, attribs, &config, 1, &عدد_configs));

    إذا (عدد_configs == 0) {
        SDL_سیٹ_Error("No valid EGL configs for requested mode");
        أرجع عدم;
    }

    EGLCHK(surface = egl_Create_کھڑکی_Surface(display, config, VITA_کھڑکی_960_X544, عدم));

    EGLCHK(context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs));

    EGLCHK(eglMakeCurrent(display, surface, surface, context));

    EGLCHK(eglQuerySurface(display, surface, EGL_چوڑائی, &چوڑائی));
    EGLCHK(eglQuerySurface(display, surface, EGL_اچائی, &اچائی));

    _this->gl_انکڑے->display = display;
    _this->gl_انکڑے->context = context;
    _this->gl_انکڑے->surface = surface;

    pre_وٹاندرا_Callback = (PFNEGLPIGLETVITASETPRESWAPCALLBACKSCEPROC)egl_Get_Proc_پتہ("eglPigletVitaSetPreSwapCallbackSCE");
    pre_وٹاندرا_Callback(VITA_GLES_KeyboardCallback);

    أرجع context;
}

bool VITA_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_GLContext context)
{
    إذا (!eglMakeCurrent(_this->gl_انکڑے->display, _this->gl_انکڑے->surface,
                        _this->gl_انکڑے->surface, _this->gl_انکڑے->context)) {
        أرجع SDL_سیٹ_Error("Unable to make EGL context current");
    }
    أرجع true;
}

bool VITA_GLES_سیٹ_وٹاندرا_Interval(SDL_VideoDevice *_this, صحيح interval)
{
    EGLBoolean حالت;
    حالت = egl_وٹاندرا_Interval(_this->gl_انکڑے->display, interval);
    إذا (حالت == EGL_TRUE) {
        // Return success to upper level
        _this->gl_انکڑے->swapinterval = interval;
        أرجع true;
    }
    // Failed to set swap interval
    أرجع SDL_سیٹ_Error("Unable to set the EGL swap interval");
}

bool VITA_GLES_Get_وٹاندرا_Interval(SDL_VideoDevice *_this, صحيح *interval)
{
    *interval = _this->gl_انکڑے->swapinterval;
    أرجع true;
}

bool VITA_GLES_وٹاندرا_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    إذا (!egl_وٹاندرا_Buffers(_this->gl_انکڑے->display, _this->gl_انکڑے->surface)) {
        أرجع SDL_سیٹ_Error("eglSwapBuffers() failed");
    }
    أرجع true;
}

bool VITA_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_Video_انکڑے *phdata = _this->اندرونی;
    EGLBoolean حالت;

    إذا (phdata->egl_initialized != true) {
        أرجع SDL_سیٹ_Error("VITA: GLES initialization failed, no OpenGL ES support");
    }

    // Check if OpenGL ES connection has been initialized
    إذا (_this->gl_انکڑے->display != EGL_NO_DISPLAY) {
        إذا (context != EGL_NO_CONTEXT) {
            حالت = eglDestroyContext(_this->gl_انکڑے->display, context);
            إذا (حالت != EGL_TRUE) {
                // Error during OpenGL ES context destroying
                أرجع SDL_سیٹ_Error("VITA: OpenGL ES context destroy error");
            }
        }
    }

    أرجع true;
}

#جے_انت // SDL_VIDEO_DRIVER_VITA
