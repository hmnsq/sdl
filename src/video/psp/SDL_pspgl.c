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

#که_تعریف_شوی SDL_VIDEO_DRIVER_PSP

#ضمن <stdlib.h>
#ضمن <string.h>

#ضمن "SDL_pspvideo.h"
#ضمن "SDL_pspgl_c.h"

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

bool PSP_GL_بارول_Library(SDL_VideoDevice *_this, ثابت حرف *لار)
{
    أرجع true;
}

/* pspgl doesn't provide this call, so stub it out since SDL requires it.
#define GLSTUB(func,params) void func params {}

GLSTUB(glOrtho,(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top,
                    GLdouble zNear, GLdouble zFar))
*/
SDL_Function_اشاره_ګر PSP_GL_Get_Proc_پته(SDL_VideoDevice *_this, ثابت حرف *proc)
{
    أرجع egl_Get_Proc_پته(proc);
}

فراغ PSP_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    eglTerminate(_this->gl_معلومات->display);
}

ساكن EGLint پلنوالی = 480;
ساكن EGLint لوړوالی = 272;

SDL_GLContext PSP_GL_CreateContext(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{

    SDL_کړکۍ_معلومات *wdata = کړکۍ->دننی;

    EGLint attribs[32];
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    EGLConfig config;
    EGLint عدد_configs;
    صحيح i;

    // EGL init taken from glutCreateWindow() in PSPGL's glut.c.
    EGLCHK(display = eglGetDisplay(0));
    EGLCHK(eglInitialize(display, عدم, عدم));
    wdata->کاروي_gles = true;
    کړکۍ->flags |= SDL_کړکۍ_FULLSCREEN;

    // Setup the config based on SDL's current values.
    i = 0;
    attribs[i++] = EGL_RED_اندازه;
    attribs[i++] = _this->gl_config.red_اندازه;
    attribs[i++] = EGL_GREEN_اندازه;
    attribs[i++] = _this->gl_config.green_اندازه;
    attribs[i++] = EGL_BLUE_اندازه;
    attribs[i++] = _this->gl_config.blue_اندازه;
    attribs[i++] = EGL_ژوروالی_اندازه;
    attribs[i++] = _this->gl_config.ژوروالی_اندازه;

    إذا (_this->gl_config.alpha_اندازه) {
        attribs[i++] = EGL_ALPHA_اندازه;
        attribs[i++] = _this->gl_config.alpha_اندازه;
    }
    إذا (_this->gl_config.stencil_اندازه) {
        attribs[i++] = EGL_STENCIL_اندازه;
        attribs[i++] = _this->gl_config.stencil_اندازه;
    }

    attribs[i++] = EGL_NONE;

    EGLCHK(egl_ټاکنه_Config(display, attribs, &config, 1, &عدد_configs));

    إذا (عدد_configs == 0) {
        SDL_سېټ_Error("No valid EGL configs for requested mode");
        أرجع عدم;
    }

    EGLCHK(eglGetConfigAttrib(display, config, EGL_پلنوالی, &پلنوالی));
    EGLCHK(eglGetConfigAttrib(display, config, EGL_لوړوالی, &لوړوالی));

    EGLCHK(context = eglCreateContext(display, config, عدم, عدم));
    EGLCHK(surface = egl_Create_کړکۍ_Surface(display, config, 0, عدم));
    EGLCHK(eglMakeCurrent(display, surface, surface, context));

    _this->gl_معلومات->display = display;
    _this->gl_معلومات->context = context;
    _this->gl_معلومات->surface = surface;

    أرجع context;
}

bool PSP_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_GLContext context)
{
    إذا (!eglMakeCurrent(_this->gl_معلومات->display, _this->gl_معلومات->surface,
                        _this->gl_معلومات->surface, _this->gl_معلومات->context)) {
        أرجع SDL_سېټ_Error("Unable to make EGL context current");
    }
    أرجع true;
}

bool PSP_GL_سېټ_بدلون_Interval(SDL_VideoDevice *_this, صحيح interval)
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

bool PSP_GL_Get_بدلون_Interval(SDL_VideoDevice *_this, صحيح *interval)
{
    *interval = _this->gl_معلومات->swapinterval;
    أرجع true;
}

bool PSP_GL_بدلون_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    إذا (!egl_بدلون_Buffers(_this->gl_معلومات->display, _this->gl_معلومات->surface)) {
        أرجع SDL_سېټ_Error("eglSwapBuffers() failed");
    }
    أرجع true;
}

bool PSP_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_Video_معلومات *phdata = _this->دننی;
    EGLBoolean حالت;

    إذا (phdata->egl_initialized != true) {
        أرجع SDL_سېټ_Error("PSP: GLES initialization failed, no OpenGL ES support");
    }

    // Check if OpenGL ES connection has been initialized
    إذا (_this->gl_معلومات->display != EGL_NO_DISPLAY) {
        إذا (context != EGL_NO_CONTEXT) {
            حالت = eglDestroyContext(_this->gl_معلومات->display, context);
            إذا (حالت != EGL_TRUE) {
                // Error during OpenGL ES context destroying
                أرجع SDL_سېټ_Error("PSP: OpenGL ES context destroy error");
            }
        }
    }
    أرجع true;
}

#د_که_پای // SDL_VIDEO_DRIVER_PSP
