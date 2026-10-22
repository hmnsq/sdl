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
#অন্তর্ভাব "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_PSP

#অন্তর্ভাব <stdlib.h>
#অন্তর্ভাব <string.h>

#অন্তর্ভাব "SDL_pspvideo.h"
#অন্তর্ভাব "SDL_pspgl_c.h"

/*****************************************************************************/
// SDL OpenGL/OpenGL ES functions
/*****************************************************************************/
#define EGLCHK(stmt)                           \
    করো {                                       \
        EGLint err;                            \
                                               \
        stmt;                                  \
        err = eglGetError();                   \
        যদি (err != EGL_SUCCESS) {              \
            SDL_SetError("EGL error %d", err); \
            ফেরত ফাঁকা;                          \
        }                                      \
    } যখন (0)

bool PSP_GL_LoadLibrary(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *path)
{
    ফেরত true;
}

/* pspgl doesn't provide this call, so stub it out since SDL requires it.
#define GLSTUB(func,params) void func params {}

GLSTUB(glOrtho,(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top,
                    GLdouble zNear, GLdouble zFar))
*/
SDL_FunctionPointer PSP_GL_GetProcAddress(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *proc)
{
    ফেরত eglGetProcAddress(proc);
}

শূন্য PSP_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    eglTerminate(_this->gl_তথ্য->display);
}

স্থির EGLint width = 480;
স্থির EGLint height = 272;

SDL_GLContext PSP_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{

    SDL_Window_তথ্য *wdata = window->internal;

    EGLint attribs[32];
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    EGLConfig config;
    EGLint অঙ্ক_configs;
    পূর্ণসংখ্যা i;

    // EGL init taken from glutCreateWindow() in PSPGL's glut.c.
    EGLCHK(display = eglGetDisplay(0));
    EGLCHK(eglInitialize(display, ফাঁকা, ফাঁকা));
    wdata->uses_gles = true;
    window->flags |= SDL_WINDOW_FULLSCREEN;

    // Setup the config based on SDL's current values.
    i = 0;
    attribs[i++] = EGL_RED_আকার;
    attribs[i++] = _this->gl_config.red_আকার;
    attribs[i++] = EGL_GREEN_আকার;
    attribs[i++] = _this->gl_config.green_আকার;
    attribs[i++] = EGL_BLUE_আকার;
    attribs[i++] = _this->gl_config.blue_আকার;
    attribs[i++] = EGL_DEPTH_আকার;
    attribs[i++] = _this->gl_config.depth_আকার;

    যদি (_this->gl_config.alpha_আকার) {
        attribs[i++] = EGL_ALPHA_আকার;
        attribs[i++] = _this->gl_config.alpha_আকার;
    }
    যদি (_this->gl_config.stencil_আকার) {
        attribs[i++] = EGL_STENCIL_আকার;
        attribs[i++] = _this->gl_config.stencil_আকার;
    }

    attribs[i++] = EGL_NONE;

    EGLCHK(eglChooseConfig(display, attribs, &config, 1, &অঙ্ক_configs));

    যদি (অঙ্ক_configs == 0) {
        SDL_SetError("No valid EGL configs for requested mode");
        ফেরত ফাঁকা;
    }

    EGLCHK(eglGetConfigAttrib(display, config, EGL_WIDTH, &width));
    EGLCHK(eglGetConfigAttrib(display, config, EGL_HEIGHT, &height));

    EGLCHK(context = eglCreateContext(display, config, ফাঁকা, ফাঁকা));
    EGLCHK(surface = eglCreateWindowSurface(display, config, 0, ফাঁকা));
    EGLCHK(eglMakeCurrent(display, surface, surface, context));

    _this->gl_তথ্য->display = display;
    _this->gl_তথ্য->context = context;
    _this->gl_তথ্য->surface = surface;

    ফেরত context;
}

bool PSP_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context)
{
    যদি (!eglMakeCurrent(_this->gl_তথ্য->display, _this->gl_তথ্য->surface,
                        _this->gl_তথ্য->surface, _this->gl_তথ্য->context)) {
        ফেরত SDL_SetError("Unable to make EGL context current");
    }
    ফেরত true;
}

bool PSP_GL_SetSwapInterval(SDL_VideoDevice *_this, পূর্ণসংখ্যা interval)
{
    EGLBoolean status;
    status = eglSwapInterval(_this->gl_তথ্য->display, interval);
    যদি (status == EGL_TRUE) {
        // Return success to upper level
        _this->gl_তথ্য->swapinterval = interval;
        ফেরত true;
    }
    // Failed to set swap interval
    ফেরত SDL_SetError("Unable to set the EGL swap interval");
}

bool PSP_GL_GetSwapInterval(SDL_VideoDevice *_this, পূর্ণসংখ্যা *interval)
{
    *interval = _this->gl_তথ্য->swapinterval;
    ফেরত true;
}

bool PSP_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    যদি (!eglSwapBuffers(_this->gl_তথ্য->display, _this->gl_তথ্য->surface)) {
        ফেরত SDL_SetError("eglSwapBuffers() failed");
    }
    ফেরত true;
}

bool PSP_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_Video_তথ্য *phdata = _this->internal;
    EGLBoolean status;

    যদি (phdata->egl_initialized != true) {
        ফেরত SDL_SetError("PSP: GLES initialization failed, no OpenGL ES support");
    }

    // Check if OpenGL ES connection has been initialized
    যদি (_this->gl_তথ্য->display != EGL_NO_DISPLAY) {
        যদি (context != EGL_NO_CONTEXT) {
            status = eglDestroyContext(_this->gl_তথ্য->display, context);
            যদি (status != EGL_TRUE) {
                // Error during OpenGL ES context destroying
                ফেরত SDL_SetError("PSP: OpenGL ES context destroy error");
            }
        }
    }
    ফেরত true;
}

#endif // SDL_VIDEO_DRIVER_PSP
