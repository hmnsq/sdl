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

#اگر defined(SDL_VIDEO_DRIVER_VITA) && defined(SDL_VIDEO_VITA_PIB)
#شامل <stdlib.h>
#شامل <string.h>

#شامل "SDL_vitavideo.h"

/*****************************************************************************/
// SDL OpenGL/OpenGL ES functions
/*****************************************************************************/
#تعریف_کرو EGLCHK(stmt)                           \
    کرو {                                       \
        EGLint err;                            \
                                               \
        stmt;                                  \
        err = eglGetError();                   \
        اگر (err != EGL_SUCCESS) {              \
            SDL_سیٹ_Error("EGL error %d", err); \
            واپس تہی;                          \
        }                                      \
    } جب (0)

خالی VITA_GLES_KeyboardCallback(Sce_Piglet_Pre_تبادلہ_ڈیٹا *ڈیٹا)
{
    SceCommonDialogUpdateParam commonDialogParam;
    SDL_zero(commonDialogParam);
    commonDialogParam.render_ہدف.colorFormat = ڈیٹا->colorFormat;
    commonDialogParam.render_ہدف.surfaceType = ڈیٹا->surfaceType;
    commonDialogParam.render_ہدف.color_Surface_ڈیٹا = ڈیٹا->color_Surface_ڈیٹا;
    commonDialogParam.render_ہدف.گہرائی_Surface_ڈیٹا = ڈیٹا->گہرائی_Surface_ڈیٹا;
    commonDialogParam.render_ہدف.چوڑائی = ڈیٹا->چوڑائی;
    commonDialogParam.render_ہدف.اونچائی = ڈیٹا->اونچائی;
    commonDialogParam.render_ہدف.stride_اندر_Pixels = ڈیٹا->stride_اندر_Pixels;
    commonDialogParam.displaySyncObject = ڈیٹا->displaySyncObject;

    sceCommonDialogUpdate(&commonDialogParam);
}

bool VITA_GLES_بھرو_Library(SDL_VideoDevice *_this, ثابت حرف *راستہ)
{
    pibInit(PIB_SHACCCG | PIB_GET_PROC_ADDR_CORE);
    واپس true;
}

SDL_Function_اشارہ_گر VITA_GLES_Get_Proc_پتہ(SDL_VideoDevice *_this, ثابت حرف *proc)
{
    واپس egl_Get_Proc_پتہ(proc);
}

خالی VITA_GLES_UnloadLibrary(SDL_VideoDevice *_this)
{
    eglTerminate(_this->gl_ڈیٹا->display);
}

ساکن EGLint چوڑائی = 960;
ساکن EGLint اونچائی = 544;

SDL_GLContext VITA_GLES_CreateContext(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{

    SDL_کھڑکی_ڈیٹا *wdata = کھڑکی->اندرونی_2;

    EGLint attribs[32];
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    EGLConfig config;
    EGLint عدد_configs;
    PFNEGLPIGLETVITASETPRESWAPCALLBACKSCEPROC pre_تبادلہ_Callback;
    صحیح i;

    ثابت EGLint contextAttribs[] = {
        EGL_CONTEXT_CLIENT_نسخہ, 2,
        EGL_NONE
    };

    EGLCHK(display = eglGetDisplay(0));

    EGLCHK(eglInitialize(display, تہی, تہی));
    wdata->استعمال_کرتا_gles = true;
    کھڑکی->flags |= SDL_کھڑکی_FULLSCREEN;

    EGLCHK(eglBindAPI(EGL_OPENGL_ES_API));

    i = 0;
    attribs[i++] = EGL_RED_سائز;
    attribs[i++] = 8;
    attribs[i++] = EGL_GREEN_سائز;
    attribs[i++] = 8;
    attribs[i++] = EGL_BLUE_سائز;
    attribs[i++] = 8;
    attribs[i++] = EGL_گہرائی_سائز;
    attribs[i++] = 0;
    attribs[i++] = EGL_ALPHA_سائز;
    attribs[i++] = 8;
    attribs[i++] = EGL_STENCIL_سائز;
    attribs[i++] = 0;

    attribs[i++] = EGL_SURFACE_TYPE;
    attribs[i++] = 5;

    attribs[i++] = EGL_RENDERABLE_TYPE;
    attribs[i++] = EGL_OPENGL_ES2_ثنائی_ہندسہ;

    attribs[i++] = EGL_CONFORMANT;
    attribs[i++] = EGL_OPENGL_ES2_ثنائی_ہندسہ;

    attribs[i++] = EGL_NONE;

    EGLCHK(egl_انتخاب_Config(display, attribs, &config, 1, &عدد_configs));

    اگر (عدد_configs == 0) {
        SDL_سیٹ_Error("No valid EGL configs for requested mode");
        واپس تہی;
    }

    EGLCHK(surface = egl_Create_کھڑکی_Surface(display, config, VITA_کھڑکی_960_X544, تہی));

    EGLCHK(context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs));

    EGLCHK(eglMakeCurrent(display, surface, surface, context));

    EGLCHK(eglQuerySurface(display, surface, EGL_چوڑائی, &چوڑائی));
    EGLCHK(eglQuerySurface(display, surface, EGL_اونچائی, &اونچائی));

    _this->gl_ڈیٹا->display = display;
    _this->gl_ڈیٹا->context = context;
    _this->gl_ڈیٹا->surface = surface;

    pre_تبادلہ_Callback = (PFNEGLPIGLETVITASETPRESWAPCALLBACKSCEPROC)egl_Get_Proc_پتہ("eglPigletVitaSetPreSwapCallbackSCE");
    pre_تبادلہ_Callback(VITA_GLES_KeyboardCallback);

    واپس context;
}

bool VITA_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_GLContext context)
{
    اگر (!eglMakeCurrent(_this->gl_ڈیٹا->display, _this->gl_ڈیٹا->surface,
                        _this->gl_ڈیٹا->surface, _this->gl_ڈیٹا->context)) {
        واپس SDL_سیٹ_Error("Unable to make EGL context current");
    }
    واپس true;
}

bool VITA_GLES_سیٹ_تبادلہ_Interval(SDL_VideoDevice *_this, صحیح interval)
{
    EGLBoolean حالت_2;
    حالت_2 = egl_تبادلہ_Interval(_this->gl_ڈیٹا->display, interval);
    اگر (حالت_2 == EGL_TRUE) {
        // Return success to upper level
        _this->gl_ڈیٹا->swapinterval = interval;
        واپس true;
    }
    // Failed to set swap interval
    واپس SDL_سیٹ_Error("Unable to set the EGL swap interval");
}

bool VITA_GLES_Get_تبادلہ_Interval(SDL_VideoDevice *_this, صحیح *interval)
{
    *interval = _this->gl_ڈیٹا->swapinterval;
    واپس true;
}

bool VITA_GLES_تبادلہ_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    اگر (!egl_تبادلہ_Buffers(_this->gl_ڈیٹا->display, _this->gl_ڈیٹا->surface)) {
        واپس SDL_سیٹ_Error("eglSwapBuffers() failed");
    }
    واپس true;
}

bool VITA_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_Video_ڈیٹا *phdata = _this->اندرونی_2;
    EGLBoolean حالت_2;

    اگر (phdata->egl_initialized != true) {
        واپس SDL_سیٹ_Error("VITA: GLES initialization failed, no OpenGL ES support");
    }

    // Check if OpenGL ES connection has been initialized
    اگر (_this->gl_ڈیٹا->display != EGL_NO_DISPLAY) {
        اگر (context != EGL_NO_CONTEXT) {
            حالت_2 = eglDestroyContext(_this->gl_ڈیٹا->display, context);
            اگر (حالت_2 != EGL_TRUE) {
                // Error during OpenGL ES context destroying
                واپس SDL_سیٹ_Error("VITA: OpenGL ES context destroy error");
            }
        }
    }

    واپس true;
}

#اگر_ختم // SDL_VIDEO_DRIVER_VITA
