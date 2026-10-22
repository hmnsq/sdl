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

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_PSP

#ضمن <stdlib.h>
#ضمن <string.h>

#ضمن "SDL_pspvideo.h"
#ضمن "SDL_pspgl_c.h"

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

bool PSP_GL_لدو_Library(SDL_VideoDevice *_this, ثابت حرف *رستہ)
{
    أرجع true;
}

/* pspgl doesn't provide this call, so stub it out since SDL requires it.
#define GLSTUB(func,params) void func params {}

GLSTUB(glOrtho,(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top,
                    GLdouble zNear, GLdouble zFar))
*/
SDL_Function_اشارہ_گر PSP_GL_Get_Proc_پتہ(SDL_VideoDevice *_this, ثابت حرف *proc)
{
    أرجع egl_Get_Proc_پتہ(proc);
}

فراغ PSP_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    eglTerminate(_this->gl_انکڑے->display);
}

ساكن EGLint چوڑائی = 480;
ساكن EGLint اچائی = 272;

SDL_GLContext PSP_GL_CreateContext(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{

    SDL_کھڑکی_انکڑے *wdata = کھڑکی->اندرونی;

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
    wdata->ورتدا_gles = true;
    کھڑکی->flags |= SDL_کھڑکی_FULLSCREEN;

    // Setup the config based on SDL's current values.
    i = 0;
    attribs[i++] = EGL_RED_ناپ;
    attribs[i++] = _this->gl_config.red_ناپ;
    attribs[i++] = EGL_GREEN_ناپ;
    attribs[i++] = _this->gl_config.green_ناپ;
    attribs[i++] = EGL_BLUE_ناپ;
    attribs[i++] = _this->gl_config.blue_ناپ;
    attribs[i++] = EGL_ڈونگھائی_ناپ;
    attribs[i++] = _this->gl_config.ڈونگھائی_ناپ;

    إذا (_this->gl_config.alpha_ناپ) {
        attribs[i++] = EGL_ALPHA_ناپ;
        attribs[i++] = _this->gl_config.alpha_ناپ;
    }
    إذا (_this->gl_config.stencil_ناپ) {
        attribs[i++] = EGL_STENCIL_ناپ;
        attribs[i++] = _this->gl_config.stencil_ناپ;
    }

    attribs[i++] = EGL_NONE;

    EGLCHK(egl_چنو_Config(display, attribs, &config, 1, &عدد_configs));

    إذا (عدد_configs == 0) {
        SDL_سیٹ_Error("No valid EGL configs for requested mode");
        أرجع عدم;
    }

    EGLCHK(eglGetConfigAttrib(display, config, EGL_چوڑائی, &چوڑائی));
    EGLCHK(eglGetConfigAttrib(display, config, EGL_اچائی, &اچائی));

    EGLCHK(context = eglCreateContext(display, config, عدم, عدم));
    EGLCHK(surface = egl_Create_کھڑکی_Surface(display, config, 0, عدم));
    EGLCHK(eglMakeCurrent(display, surface, surface, context));

    _this->gl_انکڑے->display = display;
    _this->gl_انکڑے->context = context;
    _this->gl_انکڑے->surface = surface;

    أرجع context;
}

bool PSP_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_GLContext context)
{
    إذا (!eglMakeCurrent(_this->gl_انکڑے->display, _this->gl_انکڑے->surface,
                        _this->gl_انکڑے->surface, _this->gl_انکڑے->context)) {
        أرجع SDL_سیٹ_Error("Unable to make EGL context current");
    }
    أرجع true;
}

bool PSP_GL_سیٹ_وٹاندرا_Interval(SDL_VideoDevice *_this, صحيح interval)
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

bool PSP_GL_Get_وٹاندرا_Interval(SDL_VideoDevice *_this, صحيح *interval)
{
    *interval = _this->gl_انکڑے->swapinterval;
    أرجع true;
}

bool PSP_GL_وٹاندرا_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    إذا (!egl_وٹاندرا_Buffers(_this->gl_انکڑے->display, _this->gl_انکڑے->surface)) {
        أرجع SDL_سیٹ_Error("eglSwapBuffers() failed");
    }
    أرجع true;
}

bool PSP_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_Video_انکڑے *phdata = _this->اندرونی;
    EGLBoolean حالت;

    إذا (phdata->egl_initialized != true) {
        أرجع SDL_سیٹ_Error("PSP: GLES initialization failed, no OpenGL ES support");
    }

    // Check if OpenGL ES connection has been initialized
    إذا (_this->gl_انکڑے->display != EGL_NO_DISPLAY) {
        إذا (context != EGL_NO_CONTEXT) {
            حالت = eglDestroyContext(_this->gl_انکڑے->display, context);
            إذا (حالت != EGL_TRUE) {
                // Error during OpenGL ES context destroying
                أرجع SDL_سیٹ_Error("PSP: OpenGL ES context destroy error");
            }
        }
    }
    أرجع true;
}

#جے_انت // SDL_VIDEO_DRIVER_PSP
