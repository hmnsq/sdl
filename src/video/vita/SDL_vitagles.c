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
#وصف_ڪريو EGLCHK(stmt)                           \
    افعل {                                       \
        EGLint err;                            \
                                               \
        stmt;                                  \
        err = eglGetError();                   \
        إذا (err != EGL_SUCCESS) {              \
            SDL_سيٽ_Error("EGL error %d", err); \
            أرجع عدم;                          \
        }                                      \
    } طالما (0)

فراغ VITA_GLES_KeyboardCallback(Sce_Piglet_Pre_مٽا_سٽا_معلومات *معلومات)
{
    SceCommonDialogUpdateParam commonDialogParam;
    SDL_zero(commonDialogParam);
    commonDialogParam.render_هدف.colorFormat = معلومات->colorFormat;
    commonDialogParam.render_هدف.surfaceType = معلومات->surfaceType;
    commonDialogParam.render_هدف.color_Surface_معلومات = معلومات->color_Surface_معلومات;
    commonDialogParam.render_هدف.اونهائي_Surface_معلومات = معلومات->اونهائي_Surface_معلومات;
    commonDialogParam.render_هدف.ويڪر = معلومات->ويڪر;
    commonDialogParam.render_هدف.اوچائي = معلومات->اوچائي;
    commonDialogParam.render_هدف.stride_اندريون_Pixels = معلومات->stride_اندريون_Pixels;
    commonDialogParam.displaySyncObject = معلومات->displaySyncObject;

    sceCommonDialogUpdate(&commonDialogParam);
}

bool VITA_GLES_ڀريو_Library(SDL_VideoDevice *_this, ثابت حرف *رستو)
{
    pibInit(PIB_SHACCCG | PIB_GET_PROC_ADDR_CORE);
    أرجع true;
}

SDL_Function_اشارو VITA_GLES_Get_Proc_پتو(SDL_VideoDevice *_this, ثابت حرف *proc)
{
    أرجع egl_Get_Proc_پتو(proc);
}

فراغ VITA_GLES_UnloadLibrary(SDL_VideoDevice *_this)
{
    eglTerminate(_this->gl_معلومات->display);
}

ساكن EGLint ويڪر = 960;
ساكن EGLint اوچائي = 544;

SDL_GLContext VITA_GLES_CreateContext(SDL_VideoDevice *_this, SDL_دري *دري)
{

    SDL_دري_معلومات *wdata = دري->اندروني;

    EGLint attribs[32];
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    EGLConfig config;
    EGLint انگ_configs;
    PFNEGLPIGLETVITASETPRESWAPCALLBACKSCEPROC pre_مٽا_سٽا_Callback;
    صحيح i;

    ثابت EGLint contextAttribs[] = {
        EGL_CONTEXT_CLIENT_نسخو, 2,
        EGL_NONE
    };

    EGLCHK(display = eglGetDisplay(0));

    EGLCHK(eglInitialize(display, عدم, عدم));
    wdata->استعمال_ڪري_gles = true;
    دري->flags |= SDL_دري_FULLSCREEN;

    EGLCHK(eglBindAPI(EGL_OPENGL_ES_API));

    i = 0;
    attribs[i++] = EGL_RED_سائيز;
    attribs[i++] = 8;
    attribs[i++] = EGL_GREEN_سائيز;
    attribs[i++] = 8;
    attribs[i++] = EGL_BLUE_سائيز;
    attribs[i++] = 8;
    attribs[i++] = EGL_اونهائي_سائيز;
    attribs[i++] = 0;
    attribs[i++] = EGL_ALPHA_سائيز;
    attribs[i++] = 8;
    attribs[i++] = EGL_STENCIL_سائيز;
    attribs[i++] = 0;

    attribs[i++] = EGL_SURFACE_TYPE;
    attribs[i++] = 5;

    attribs[i++] = EGL_RENDERABLE_TYPE;
    attribs[i++] = EGL_OPENGL_ES2_ٻٽو_انگ;

    attribs[i++] = EGL_CONFORMANT;
    attribs[i++] = EGL_OPENGL_ES2_ٻٽو_انگ;

    attribs[i++] = EGL_NONE;

    EGLCHK(egl_چونڊيو_Config(display, attribs, &config, 1, &انگ_configs));

    إذا (انگ_configs == 0) {
        SDL_سيٽ_Error("No valid EGL configs for requested mode");
        أرجع عدم;
    }

    EGLCHK(surface = egl_Create_دري_Surface(display, config, VITA_دري_960_X544, عدم));

    EGLCHK(context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs));

    EGLCHK(eglMakeCurrent(display, surface, surface, context));

    EGLCHK(eglQuerySurface(display, surface, EGL_ويڪر, &ويڪر));
    EGLCHK(eglQuerySurface(display, surface, EGL_اوچائي, &اوچائي));

    _this->gl_معلومات->display = display;
    _this->gl_معلومات->context = context;
    _this->gl_معلومات->surface = surface;

    pre_مٽا_سٽا_Callback = (PFNEGLPIGLETVITASETPRESWAPCALLBACKSCEPROC)egl_Get_Proc_پتو("eglPigletVitaSetPreSwapCallbackSCE");
    pre_مٽا_سٽا_Callback(VITA_GLES_KeyboardCallback);

    أرجع context;
}

bool VITA_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_دري *دري, SDL_GLContext context)
{
    إذا (!eglMakeCurrent(_this->gl_معلومات->display, _this->gl_معلومات->surface,
                        _this->gl_معلومات->surface, _this->gl_معلومات->context)) {
        أرجع SDL_سيٽ_Error("Unable to make EGL context current");
    }
    أرجع true;
}

bool VITA_GLES_سيٽ_مٽا_سٽا_Interval(SDL_VideoDevice *_this, صحيح interval)
{
    EGLBoolean حالت;
    حالت = egl_مٽا_سٽا_Interval(_this->gl_معلومات->display, interval);
    إذا (حالت == EGL_TRUE) {
        // Return success to upper level
        _this->gl_معلومات->swapinterval = interval;
        أرجع true;
    }
    // Failed to set swap interval
    أرجع SDL_سيٽ_Error("Unable to set the EGL swap interval");
}

bool VITA_GLES_Get_مٽا_سٽا_Interval(SDL_VideoDevice *_this, صحيح *interval)
{
    *interval = _this->gl_معلومات->swapinterval;
    أرجع true;
}

bool VITA_GLES_مٽا_سٽا_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
    إذا (!egl_مٽا_سٽا_Buffers(_this->gl_معلومات->display, _this->gl_معلومات->surface)) {
        أرجع SDL_سيٽ_Error("eglSwapBuffers() failed");
    }
    أرجع true;
}

bool VITA_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_Video_معلومات *phdata = _this->اندروني;
    EGLBoolean حالت;

    إذا (phdata->egl_initialized != true) {
        أرجع SDL_سيٽ_Error("VITA: GLES initialization failed, no OpenGL ES support");
    }

    // Check if OpenGL ES connection has been initialized
    إذا (_this->gl_معلومات->display != EGL_NO_DISPLAY) {
        إذا (context != EGL_NO_CONTEXT) {
            حالت = eglDestroyContext(_this->gl_معلومات->display, context);
            إذا (حالت != EGL_TRUE) {
                // Error during OpenGL ES context destroying
                أرجع SDL_سيٽ_Error("VITA: OpenGL ES context destroy error");
            }
        }
    }

    أرجع true;
}

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_VITA
