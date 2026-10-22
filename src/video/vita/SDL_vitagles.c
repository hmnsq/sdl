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
#تعریف_کن EGLCHK(stmt)                           \
    افعل {                                       \
        EGLint err;                            \
                                               \
        stmt;                                  \
        err = eglGetError();                   \
        إذا (err != EGL_SUCCESS) {              \
            SDL_مجموعه_Error("EGL error %d", err); \
            أرجع عدم;                          \
        }                                      \
    } طالما (0)

فراغ VITA_GLES_KeyboardCallback(Sce_Piglet_Pre_جابجا_داده *داده)
{
    SceCommonDialogUpdateParam commonDialogParam;
    SDL_zero(commonDialogParam);
    commonDialogParam.render_هدف.colorFormat = داده->colorFormat;
    commonDialogParam.render_هدف.surfaceType = داده->surfaceType;
    commonDialogParam.render_هدف.color_Surface_داده = داده->color_Surface_داده;
    commonDialogParam.render_هدف.عمق_Surface_داده = داده->عمق_Surface_داده;
    commonDialogParam.render_هدف.عرض = داده->عرض;
    commonDialogParam.render_هدف.ارتفاع = داده->ارتفاع;
    commonDialogParam.render_هدف.stride_درون_Pixels = داده->stride_درون_Pixels;
    commonDialogParam.displaySyncObject = داده->displaySyncObject;

    sceCommonDialogUpdate(&commonDialogParam);
}

bool VITA_GLES_بارگیری_Library(SDL_VideoDevice *_this, ثابت حرف *مسیر)
{
    pibInit(PIB_SHACCCG | PIB_GET_PROC_ADDR_CORE);
    أرجع true;
}

SDL_Function_اشاره_گر VITA_GLES_Get_Proc_آدرس(SDL_VideoDevice *_this, ثابت حرف *proc)
{
    أرجع egl_Get_Proc_آدرس(proc);
}

فراغ VITA_GLES_UnloadLibrary(SDL_VideoDevice *_this)
{
    eglTerminate(_this->gl_داده->display);
}

ساكن EGLint عرض = 960;
ساكن EGLint ارتفاع = 544;

SDL_GLContext VITA_GLES_CreateContext(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{

    SDL_پنجره_داده *wdata = پنجره->داخلی;

    EGLint attribs[32];
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    EGLConfig config;
    EGLint رقم_configs;
    PFNEGLPIGLETVITASETPRESWAPCALLBACKSCEPROC pre_جابجا_Callback;
    صحيح i;

    ثابت EGLint contextAttribs[] = {
        EGL_CONTEXT_CLIENT_نسخه, 2,
        EGL_NONE
    };

    EGLCHK(display = eglGetDisplay(0));

    EGLCHK(eglInitialize(display, عدم, عدم));
    wdata->استفاده_میکند_gles = true;
    پنجره->flags |= SDL_پنجره_FULLSCREEN;

    EGLCHK(eglBindAPI(EGL_OPENGL_ES_API));

    i = 0;
    attribs[i++] = EGL_RED_اندازه;
    attribs[i++] = 8;
    attribs[i++] = EGL_GREEN_اندازه;
    attribs[i++] = 8;
    attribs[i++] = EGL_BLUE_اندازه;
    attribs[i++] = 8;
    attribs[i++] = EGL_عمق_اندازه;
    attribs[i++] = 0;
    attribs[i++] = EGL_ALPHA_اندازه;
    attribs[i++] = 8;
    attribs[i++] = EGL_STENCIL_اندازه;
    attribs[i++] = 0;

    attribs[i++] = EGL_SURFACE_TYPE;
    attribs[i++] = 5;

    attribs[i++] = EGL_RENDERABLE_TYPE;
    attribs[i++] = EGL_OPENGL_ES2_بیت;

    attribs[i++] = EGL_CONFORMANT;
    attribs[i++] = EGL_OPENGL_ES2_بیت;

    attribs[i++] = EGL_NONE;

    EGLCHK(egl_انتخاب_Config(display, attribs, &config, 1, &رقم_configs));

    إذا (رقم_configs == 0) {
        SDL_مجموعه_Error("No valid EGL configs for requested mode");
        أرجع عدم;
    }

    EGLCHK(surface = egl_Create_پنجره_Surface(display, config, VITA_پنجره_960_X544, عدم));

    EGLCHK(context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs));

    EGLCHK(eglMakeCurrent(display, surface, surface, context));

    EGLCHK(eglQuerySurface(display, surface, EGL_عرض, &عرض));
    EGLCHK(eglQuerySurface(display, surface, EGL_ارتفاع, &ارتفاع));

    _this->gl_داده->display = display;
    _this->gl_داده->context = context;
    _this->gl_داده->surface = surface;

    pre_جابجا_Callback = (PFNEGLPIGLETVITASETPRESWAPCALLBACKSCEPROC)egl_Get_Proc_آدرس("eglPigletVitaSetPreSwapCallbackSCE");
    pre_جابجا_Callback(VITA_GLES_KeyboardCallback);

    أرجع context;
}

bool VITA_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_GLContext context)
{
    إذا (!eglMakeCurrent(_this->gl_داده->display, _this->gl_داده->surface,
                        _this->gl_داده->surface, _this->gl_داده->context)) {
        أرجع SDL_مجموعه_Error("Unable to make EGL context current");
    }
    أرجع true;
}

bool VITA_GLES_مجموعه_جابجا_Interval(SDL_VideoDevice *_this, صحيح interval)
{
    EGLBoolean وضعیت;
    وضعیت = egl_جابجا_Interval(_this->gl_داده->display, interval);
    إذا (وضعیت == EGL_TRUE) {
        // Return success to upper level
        _this->gl_داده->swapinterval = interval;
        أرجع true;
    }
    // Failed to set swap interval
    أرجع SDL_مجموعه_Error("Unable to set the EGL swap interval");
}

bool VITA_GLES_Get_جابجا_Interval(SDL_VideoDevice *_this, صحيح *interval)
{
    *interval = _this->gl_داده->swapinterval;
    أرجع true;
}

bool VITA_GLES_جابجا_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    إذا (!egl_جابجا_Buffers(_this->gl_داده->display, _this->gl_داده->surface)) {
        أرجع SDL_مجموعه_Error("eglSwapBuffers() failed");
    }
    أرجع true;
}

bool VITA_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_Video_داده *phdata = _this->داخلی;
    EGLBoolean وضعیت;

    إذا (phdata->egl_initialized != true) {
        أرجع SDL_مجموعه_Error("VITA: GLES initialization failed, no OpenGL ES support");
    }

    // Check if OpenGL ES connection has been initialized
    إذا (_this->gl_داده->display != EGL_NO_DISPLAY) {
        إذا (context != EGL_NO_CONTEXT) {
            وضعیت = eglDestroyContext(_this->gl_داده->display, context);
            إذا (وضعیت != EGL_TRUE) {
                // Error during OpenGL ES context destroying
                أرجع SDL_مجموعه_Error("VITA: OpenGL ES context destroy error");
            }
        }
    }

    أرجع true;
}

#پایان_اگر // SDL_VIDEO_DRIVER_VITA
