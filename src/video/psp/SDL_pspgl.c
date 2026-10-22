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
    কুরু {                                       \
        EGLint err;                            \
                                               \
        stmt;                                  \
        err = eglGetError();                   \
        যদি (err != EGL_SUCCESS) {              \
            SDL_SetError("EGL error %d", err); \
            প্রত্যাগম রিক্ত;                          \
        }                                      \
    } যাবত্ (0)

bool PSP_GL_LoadLibrary(SDL_VideoDevice *_this, ধ্রুব বর্ণ *path)
{
    প্রত্যাগম true;
}

/* pspgl doesn't provide this call, so stub it out since SDL requires it.
#define GLSTUB(func,params) void func params {}

GLSTUB(glOrtho,(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top,
                    GLdouble zNear, GLdouble zFar))
*/
SDL_FunctionPointer PSP_GL_GetProcAddress(SDL_VideoDevice *_this, ধ্রুব বর্ণ *proc)
{
    প্রত্যাগম eglGetProcAddress(proc);
}

শূন্য PSP_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    eglTerminate(_this->gl_data->display);
}

স্থির EGLint width = 480;
স্থির EGLint height = 272;

SDL_GLContext PSP_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{

    SDL_WindowData *wdata = window->internal;

    EGLint attribs[32];
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    EGLConfig config;
    EGLint অঙ্ক_configs;
    পূর্ণাঙ্ক i;

    // EGL init taken from glutCreateWindow() in PSPGL's glut.c.
    EGLCHK(display = eglGetDisplay(0));
    EGLCHK(eglInitialize(display, রিক্ত, রিক্ত));
    wdata->uses_gles = true;
    window->flags |= SDL_WINDOW_FULLSCREEN;

    // Setup the config based on SDL's current values.
    i = 0;
    attribs[i++] = EGL_RED_SIZE;
    attribs[i++] = _this->gl_config.red_size;
    attribs[i++] = EGL_GREEN_SIZE;
    attribs[i++] = _this->gl_config.green_size;
    attribs[i++] = EGL_BLUE_SIZE;
    attribs[i++] = _this->gl_config.blue_size;
    attribs[i++] = EGL_DEPTH_SIZE;
    attribs[i++] = _this->gl_config.depth_size;

    যদি (_this->gl_config.alpha_size) {
        attribs[i++] = EGL_ALPHA_SIZE;
        attribs[i++] = _this->gl_config.alpha_size;
    }
    যদি (_this->gl_config.stencil_size) {
        attribs[i++] = EGL_STENCIL_SIZE;
        attribs[i++] = _this->gl_config.stencil_size;
    }

    attribs[i++] = EGL_NONE;

    EGLCHK(eglChooseConfig(display, attribs, &config, 1, &অঙ্ক_configs));

    যদি (অঙ্ক_configs == 0) {
        SDL_SetError("No valid EGL configs for requested mode");
        প্রত্যাগম রিক্ত;
    }

    EGLCHK(eglGetConfigAttrib(display, config, EGL_WIDTH, &width));
    EGLCHK(eglGetConfigAttrib(display, config, EGL_HEIGHT, &height));

    EGLCHK(context = eglCreateContext(display, config, রিক্ত, রিক্ত));
    EGLCHK(surface = eglCreateWindowSurface(display, config, 0, রিক্ত));
    EGLCHK(eglMakeCurrent(display, surface, surface, context));

    _this->gl_data->display = display;
    _this->gl_data->context = context;
    _this->gl_data->surface = surface;

    প্রত্যাগম context;
}

bool PSP_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context)
{
    যদি (!eglMakeCurrent(_this->gl_data->display, _this->gl_data->surface,
                        _this->gl_data->surface, _this->gl_data->context)) {
        প্রত্যাগম SDL_SetError("Unable to make EGL context current");
    }
    প্রত্যাগম true;
}

bool PSP_GL_SetSwapInterval(SDL_VideoDevice *_this, পূর্ণাঙ্ক interval)
{
    EGLBoolean status;
    status = eglSwapInterval(_this->gl_data->display, interval);
    যদি (status == EGL_TRUE) {
        // Return success to upper level
        _this->gl_data->swapinterval = interval;
        প্রত্যাগম true;
    }
    // Failed to set swap interval
    প্রত্যাগম SDL_SetError("Unable to set the EGL swap interval");
}

bool PSP_GL_GetSwapInterval(SDL_VideoDevice *_this, পূর্ণাঙ্ক *interval)
{
    *interval = _this->gl_data->swapinterval;
    প্রত্যাগম true;
}

bool PSP_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    যদি (!eglSwapBuffers(_this->gl_data->display, _this->gl_data->surface)) {
        প্রত্যাগম SDL_SetError("eglSwapBuffers() failed");
    }
    প্রত্যাগম true;
}

bool PSP_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_VideoData *phdata = _this->internal;
    EGLBoolean status;

    যদি (phdata->egl_initialized != true) {
        প্রত্যাগম SDL_SetError("PSP: GLES initialization failed, no OpenGL ES support");
    }

    // Check if OpenGL ES connection has been initialized
    যদি (_this->gl_data->display != EGL_NO_DISPLAY) {
        যদি (context != EGL_NO_CONTEXT) {
            status = eglDestroyContext(_this->gl_data->display, context);
            যদি (status != EGL_TRUE) {
                // Error during OpenGL ES context destroying
                প্রত্যাগম SDL_SetError("PSP: OpenGL ES context destroy error");
            }
        }
    }
    প্রত্যাগম true;
}

#endif // SDL_VIDEO_DRIVER_PSP
