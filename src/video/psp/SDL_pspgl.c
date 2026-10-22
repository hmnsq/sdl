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
#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_PSP

#समावेश <stdlib.h>
#समावेश <string.h>

#समावेश "SDL_pspvideo.h"
#समावेश "SDL_pspgl_c.h"

/*****************************************************************************/
// SDL OpenGL/OpenGL ES functions
/*****************************************************************************/
#घोषणा EGLCHK(stmt)                           \
    करो {                                       \
        EGLint err;                            \
                                               \
        stmt;                                  \
        err = eglGetError();                   \
        अगर (err != EGL_SUCCESS) {              \
            SDL_SetError("EGL error %d", err); \
            वापस शून्य;                          \
        }                                      \
    } जबतक (0)

bool PSP_GL_LoadLibrary(SDL_VideoDevice *_this, स्थिर अक्षर *path)
{
    वापस true;
}

/* pspgl doesn't provide this call, so stub it out since SDL requires it.
#define GLSTUB(func,params) void func params {}

GLSTUB(glOrtho,(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top,
                    GLdouble zNear, GLdouble zFar))
*/
SDL_FunctionPointer PSP_GL_GetProcAddress(SDL_VideoDevice *_this, स्थिर अक्षर *proc)
{
    वापस eglGetProcAddress(proc);
}

व्योम PSP_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    eglTerminate(_this->gl_तथ्य->display);
}

अटल EGLint width = 480;
अटल EGLint height = 272;

SDL_GLContext PSP_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{

    SDL_Window_तथ्य *wdata = window->internal;

    EGLint attribs[32];
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    EGLConfig config;
    EGLint अंक_configs;
    पूर्णांक i;

    // EGL init taken from glutCreateWindow() in PSPGL's glut.c.
    EGLCHK(display = eglGetDisplay(0));
    EGLCHK(eglInitialize(display, शून्य, शून्य));
    wdata->uses_gles = true;
    window->flags |= SDL_WINDOW_FULLSCREEN;

    // Setup the config based on SDL's current values.
    i = 0;
    attribs[i++] = EGL_RED_आकार;
    attribs[i++] = _this->gl_config.red_आकार;
    attribs[i++] = EGL_GREEN_आकार;
    attribs[i++] = _this->gl_config.green_आकार;
    attribs[i++] = EGL_BLUE_आकार;
    attribs[i++] = _this->gl_config.blue_आकार;
    attribs[i++] = EGL_DEPTH_आकार;
    attribs[i++] = _this->gl_config.depth_आकार;

    अगर (_this->gl_config.alpha_आकार) {
        attribs[i++] = EGL_ALPHA_आकार;
        attribs[i++] = _this->gl_config.alpha_आकार;
    }
    अगर (_this->gl_config.stencil_आकार) {
        attribs[i++] = EGL_STENCIL_आकार;
        attribs[i++] = _this->gl_config.stencil_आकार;
    }

    attribs[i++] = EGL_NONE;

    EGLCHK(eglChooseConfig(display, attribs, &config, 1, &अंक_configs));

    अगर (अंक_configs == 0) {
        SDL_SetError("No valid EGL configs for requested mode");
        वापस शून्य;
    }

    EGLCHK(eglGetConfigAttrib(display, config, EGL_WIDTH, &width));
    EGLCHK(eglGetConfigAttrib(display, config, EGL_HEIGHT, &height));

    EGLCHK(context = eglCreateContext(display, config, शून्य, शून्य));
    EGLCHK(surface = eglCreateWindowSurface(display, config, 0, शून्य));
    EGLCHK(eglMakeCurrent(display, surface, surface, context));

    _this->gl_तथ्य->display = display;
    _this->gl_तथ्य->context = context;
    _this->gl_तथ्य->surface = surface;

    वापस context;
}

bool PSP_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context)
{
    अगर (!eglMakeCurrent(_this->gl_तथ्य->display, _this->gl_तथ्य->surface,
                        _this->gl_तथ्य->surface, _this->gl_तथ्य->context)) {
        वापस SDL_SetError("Unable to make EGL context current");
    }
    वापस true;
}

bool PSP_GL_SetSwapInterval(SDL_VideoDevice *_this, पूर्णांक interval)
{
    EGLBoolean status;
    status = eglSwapInterval(_this->gl_तथ्य->display, interval);
    अगर (status == EGL_TRUE) {
        // Return success to upper level
        _this->gl_तथ्य->swapinterval = interval;
        वापस true;
    }
    // Failed to set swap interval
    वापस SDL_SetError("Unable to set the EGL swap interval");
}

bool PSP_GL_GetSwapInterval(SDL_VideoDevice *_this, पूर्णांक *interval)
{
    *interval = _this->gl_तथ्य->swapinterval;
    वापस true;
}

bool PSP_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    अगर (!eglSwapBuffers(_this->gl_तथ्य->display, _this->gl_तथ्य->surface)) {
        वापस SDL_SetError("eglSwapBuffers() failed");
    }
    वापस true;
}

bool PSP_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_Video_तथ्य *phdata = _this->internal;
    EGLBoolean status;

    अगर (phdata->egl_initialized != true) {
        वापस SDL_SetError("PSP: GLES initialization failed, no OpenGL ES support");
    }

    // Check if OpenGL ES connection has been initialized
    अगर (_this->gl_तथ्य->display != EGL_NO_DISPLAY) {
        अगर (context != EGL_NO_CONTEXT) {
            status = eglDestroyContext(_this->gl_तथ्य->display, context);
            अगर (status != EGL_TRUE) {
                // Error during OpenGL ES context destroying
                वापस SDL_SetError("PSP: OpenGL ES context destroy error");
            }
        }
    }
    वापस true;
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_PSP
