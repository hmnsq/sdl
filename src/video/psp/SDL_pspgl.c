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

#اگر_تعریف_شده SDL_VIDEO_DRIVER_PSP

#ضمن <stdlib.h>
#ضمن <string.h>

#ضمن "SDL_pspvideo.h"
#ضمن "SDL_pspgl_c.h"

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

bool PSP_GL_بارگیری_Library(SDL_VideoDevice *_this, ثابت حرف *مسیر)
{
    أرجع true;
}

/* pspgl doesn't provide this call, so stub it out since SDL requires it.
#define GLSTUB(func,params) void func params {}

GLSTUB(glOrtho,(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top,
                    GLdouble zNear, GLdouble zFar))
*/
SDL_Function_اشاره_گر PSP_GL_Get_Proc_آدرس(SDL_VideoDevice *_this, ثابت حرف *proc)
{
    أرجع egl_Get_Proc_آدرس(proc);
}

فراغ PSP_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    eglTerminate(_this->gl_داده->display);
}

ساكن EGLint عرض = 480;
ساكن EGLint ارتفاع = 272;

SDL_GLContext PSP_GL_CreateContext(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{

    SDL_پنجره_داده *wdata = پنجره->داخلی;

    EGLint attribs[32];
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    EGLConfig config;
    EGLint رقم_configs;
    صحيح i;

    // EGL init taken from glutCreateWindow() in PSPGL's glut.c.
    EGLCHK(display = eglGetDisplay(0));
    EGLCHK(eglInitialize(display, عدم, عدم));
    wdata->استفاده_میکند_gles = true;
    پنجره->flags |= SDL_پنجره_FULLSCREEN;

    // Setup the config based on SDL's current values.
    i = 0;
    attribs[i++] = EGL_RED_اندازه;
    attribs[i++] = _this->gl_config.red_اندازه;
    attribs[i++] = EGL_GREEN_اندازه;
    attribs[i++] = _this->gl_config.green_اندازه;
    attribs[i++] = EGL_BLUE_اندازه;
    attribs[i++] = _this->gl_config.blue_اندازه;
    attribs[i++] = EGL_عمق_اندازه;
    attribs[i++] = _this->gl_config.عمق_اندازه;

    إذا (_this->gl_config.alpha_اندازه) {
        attribs[i++] = EGL_ALPHA_اندازه;
        attribs[i++] = _this->gl_config.alpha_اندازه;
    }
    إذا (_this->gl_config.stencil_اندازه) {
        attribs[i++] = EGL_STENCIL_اندازه;
        attribs[i++] = _this->gl_config.stencil_اندازه;
    }

    attribs[i++] = EGL_NONE;

    EGLCHK(egl_انتخاب_Config(display, attribs, &config, 1, &رقم_configs));

    إذا (رقم_configs == 0) {
        SDL_مجموعه_Error("No valid EGL configs for requested mode");
        أرجع عدم;
    }

    EGLCHK(eglGetConfigAttrib(display, config, EGL_عرض, &عرض));
    EGLCHK(eglGetConfigAttrib(display, config, EGL_ارتفاع, &ارتفاع));

    EGLCHK(context = eglCreateContext(display, config, عدم, عدم));
    EGLCHK(surface = egl_Create_پنجره_Surface(display, config, 0, عدم));
    EGLCHK(eglMakeCurrent(display, surface, surface, context));

    _this->gl_داده->display = display;
    _this->gl_داده->context = context;
    _this->gl_داده->surface = surface;

    أرجع context;
}

bool PSP_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_GLContext context)
{
    إذا (!eglMakeCurrent(_this->gl_داده->display, _this->gl_داده->surface,
                        _this->gl_داده->surface, _this->gl_داده->context)) {
        أرجع SDL_مجموعه_Error("Unable to make EGL context current");
    }
    أرجع true;
}

bool PSP_GL_مجموعه_جابجا_Interval(SDL_VideoDevice *_this, صحيح interval)
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

bool PSP_GL_Get_جابجا_Interval(SDL_VideoDevice *_this, صحيح *interval)
{
    *interval = _this->gl_داده->swapinterval;
    أرجع true;
}

bool PSP_GL_جابجا_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    إذا (!egl_جابجا_Buffers(_this->gl_داده->display, _this->gl_داده->surface)) {
        أرجع SDL_مجموعه_Error("eglSwapBuffers() failed");
    }
    أرجع true;
}

bool PSP_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_Video_داده *phdata = _this->داخلی;
    EGLBoolean وضعیت;

    إذا (phdata->egl_initialized != true) {
        أرجع SDL_مجموعه_Error("PSP: GLES initialization failed, no OpenGL ES support");
    }

    // Check if OpenGL ES connection has been initialized
    إذا (_this->gl_داده->display != EGL_NO_DISPLAY) {
        إذا (context != EGL_NO_CONTEXT) {
            وضعیت = eglDestroyContext(_this->gl_داده->display, context);
            إذا (وضعیت != EGL_TRUE) {
                // Error during OpenGL ES context destroying
                أرجع SDL_مجموعه_Error("PSP: OpenGL ES context destroy error");
            }
        }
    }
    أرجع true;
}

#پایان_اگر // SDL_VIDEO_DRIVER_PSP
