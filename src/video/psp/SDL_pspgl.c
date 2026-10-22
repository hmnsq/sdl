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

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_PSP

#ضمن <stdlib.h>
#ضمن <string.h>

#ضمن "SDL_pspvideo.h"
#ضمن "SDL_pspgl_c.h"

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

bool PSP_GL_ڀريو_Library(SDL_VideoDevice *_this, ثابت حرف *رستو)
{
    أرجع true;
}

/* pspgl doesn't provide this call, so stub it out since SDL requires it.
#define GLSTUB(func,params) void func params {}

GLSTUB(glOrtho,(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top,
                    GLdouble zNear, GLdouble zFar))
*/
SDL_Function_اشارو PSP_GL_Get_Proc_پتو(SDL_VideoDevice *_this, ثابت حرف *proc)
{
    أرجع egl_Get_Proc_پتو(proc);
}

فراغ PSP_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    eglTerminate(_this->gl_معلومات->display);
}

ساكن EGLint ويڪر = 480;
ساكن EGLint اوچائي = 272;

SDL_GLContext PSP_GL_CreateContext(SDL_VideoDevice *_this, SDL_دري *دري)
{

    SDL_دري_معلومات *wdata = دري->اندروني;

    EGLint attribs[32];
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    EGLConfig config;
    EGLint انگ_configs;
    صحيح i;

    // EGL init taken from glutCreateWindow() in PSPGL's glut.c.
    EGLCHK(display = eglGetDisplay(0));
    EGLCHK(eglInitialize(display, عدم, عدم));
    wdata->استعمال_ڪري_gles = true;
    دري->flags |= SDL_دري_FULLSCREEN;

    // Setup the config based on SDL's current values.
    i = 0;
    attribs[i++] = EGL_RED_سائيز;
    attribs[i++] = _this->gl_config.red_سائيز;
    attribs[i++] = EGL_GREEN_سائيز;
    attribs[i++] = _this->gl_config.green_سائيز;
    attribs[i++] = EGL_BLUE_سائيز;
    attribs[i++] = _this->gl_config.blue_سائيز;
    attribs[i++] = EGL_اونهائي_سائيز;
    attribs[i++] = _this->gl_config.اونهائي_سائيز;

    إذا (_this->gl_config.alpha_سائيز) {
        attribs[i++] = EGL_ALPHA_سائيز;
        attribs[i++] = _this->gl_config.alpha_سائيز;
    }
    إذا (_this->gl_config.stencil_سائيز) {
        attribs[i++] = EGL_STENCIL_سائيز;
        attribs[i++] = _this->gl_config.stencil_سائيز;
    }

    attribs[i++] = EGL_NONE;

    EGLCHK(egl_چونڊيو_Config(display, attribs, &config, 1, &انگ_configs));

    إذا (انگ_configs == 0) {
        SDL_سيٽ_Error("No valid EGL configs for requested mode");
        أرجع عدم;
    }

    EGLCHK(eglGetConfigAttrib(display, config, EGL_ويڪر, &ويڪر));
    EGLCHK(eglGetConfigAttrib(display, config, EGL_اوچائي, &اوچائي));

    EGLCHK(context = eglCreateContext(display, config, عدم, عدم));
    EGLCHK(surface = egl_Create_دري_Surface(display, config, 0, عدم));
    EGLCHK(eglMakeCurrent(display, surface, surface, context));

    _this->gl_معلومات->display = display;
    _this->gl_معلومات->context = context;
    _this->gl_معلومات->surface = surface;

    أرجع context;
}

bool PSP_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_دري *دري, SDL_GLContext context)
{
    إذا (!eglMakeCurrent(_this->gl_معلومات->display, _this->gl_معلومات->surface,
                        _this->gl_معلومات->surface, _this->gl_معلومات->context)) {
        أرجع SDL_سيٽ_Error("Unable to make EGL context current");
    }
    أرجع true;
}

bool PSP_GL_سيٽ_مٽا_سٽا_Interval(SDL_VideoDevice *_this, صحيح interval)
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

bool PSP_GL_Get_مٽا_سٽا_Interval(SDL_VideoDevice *_this, صحيح *interval)
{
    *interval = _this->gl_معلومات->swapinterval;
    أرجع true;
}

bool PSP_GL_مٽا_سٽا_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
    إذا (!egl_مٽا_سٽا_Buffers(_this->gl_معلومات->display, _this->gl_معلومات->surface)) {
        أرجع SDL_سيٽ_Error("eglSwapBuffers() failed");
    }
    أرجع true;
}

bool PSP_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_Video_معلومات *phdata = _this->اندروني;
    EGLBoolean حالت;

    إذا (phdata->egl_initialized != true) {
        أرجع SDL_سيٽ_Error("PSP: GLES initialization failed, no OpenGL ES support");
    }

    // Check if OpenGL ES connection has been initialized
    إذا (_this->gl_معلومات->display != EGL_NO_DISPLAY) {
        إذا (context != EGL_NO_CONTEXT) {
            حالت = eglDestroyContext(_this->gl_معلومات->display, context);
            إذا (حالت != EGL_TRUE) {
                // Error during OpenGL ES context destroying
                أرجع SDL_سيٽ_Error("PSP: OpenGL ES context destroy error");
            }
        }
    }
    أرجع true;
}

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_PSP
