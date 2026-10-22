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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_PSP

#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ "SDL_pspvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_pspgl_c.h"

/*****************************************************************************/
// SDL OpenGL/OpenGL ES functions
/*****************************************************************************/
#define EGLCHK(stmt)                           \
    ಕುರು {                                       \
        EGLint err;                            \
                                               \
        stmt;                                  \
        err = eglGetError();                   \
        ಯದಿ (err != EGL_SUCCESS) {              \
            SDL_SetError("EGL error %d", err); \
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;                          \
        }                                      \
    } ಯಾವತ್ (0)

bool PSP_GL_LoadLibrary(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *path)
{
    ಪ್ರತ್ಯಾಗಮ true;
}

/* pspgl doesn't provide this call, so stub it out since SDL requires it.
#define GLSTUB(func,params) void func params {}

GLSTUB(glOrtho,(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top,
                    GLdouble zNear, GLdouble zFar))
*/
SDL_FunctionPointer PSP_GL_GetProcAddress(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *proc)
{
    ಪ್ರತ್ಯಾಗಮ eglGetProcAddress(proc);
}

ಶೂನ್ಯ PSP_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    eglTerminate(_this->gl_data->display);
}

ಸ್ಥಿರ EGLint width = 480;
ಸ್ಥಿರ EGLint height = 272;

SDL_GLContext PSP_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{

    SDL_WindowData *wdata = window->internal;

    EGLint attribs[32];
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    EGLConfig config;
    EGLint ಅಂಕೆ_configs;
    ಪೂರ್ಣಾಙ್ಕ i;

    // EGL init taken from glutCreateWindow() in PSPGL's glut.c.
    EGLCHK(display = eglGetDisplay(0));
    EGLCHK(eglInitialize(display, ರಿಕ್ತ, ರಿಕ್ತ));
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

    ಯದಿ (_this->gl_config.alpha_size) {
        attribs[i++] = EGL_ALPHA_SIZE;
        attribs[i++] = _this->gl_config.alpha_size;
    }
    ಯದಿ (_this->gl_config.stencil_size) {
        attribs[i++] = EGL_STENCIL_SIZE;
        attribs[i++] = _this->gl_config.stencil_size;
    }

    attribs[i++] = EGL_NONE;

    EGLCHK(eglChooseConfig(display, attribs, &config, 1, &ಅಂಕೆ_configs));

    ಯದಿ (ಅಂಕೆ_configs == 0) {
        SDL_SetError("No valid EGL configs for requested mode");
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    EGLCHK(eglGetConfigAttrib(display, config, EGL_WIDTH, &width));
    EGLCHK(eglGetConfigAttrib(display, config, EGL_HEIGHT, &height));

    EGLCHK(context = eglCreateContext(display, config, ರಿಕ್ತ, ರಿಕ್ತ));
    EGLCHK(surface = eglCreateWindowSurface(display, config, 0, ರಿಕ್ತ));
    EGLCHK(eglMakeCurrent(display, surface, surface, context));

    _this->gl_data->display = display;
    _this->gl_data->context = context;
    _this->gl_data->surface = surface;

    ಪ್ರತ್ಯಾಗಮ context;
}

bool PSP_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context)
{
    ಯದಿ (!eglMakeCurrent(_this->gl_data->display, _this->gl_data->surface,
                        _this->gl_data->surface, _this->gl_data->context)) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Unable to make EGL context current");
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

bool PSP_GL_SetSwapInterval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಙ್ಕ interval)
{
    EGLBoolean status;
    status = eglSwapInterval(_this->gl_data->display, interval);
    ಯದಿ (status == EGL_TRUE) {
        // Return success to upper level
        _this->gl_data->swapinterval = interval;
        ಪ್ರತ್ಯಾಗಮ true;
    }
    // Failed to set swap interval
    ಪ್ರತ್ಯಾಗಮ SDL_SetError("Unable to set the EGL swap interval");
}

bool PSP_GL_GetSwapInterval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಙ್ಕ *interval)
{
    *interval = _this->gl_data->swapinterval;
    ಪ್ರತ್ಯಾಗಮ true;
}

bool PSP_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    ಯದಿ (!eglSwapBuffers(_this->gl_data->display, _this->gl_data->surface)) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("eglSwapBuffers() failed");
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

bool PSP_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_VideoData *phdata = _this->internal;
    EGLBoolean status;

    ಯದಿ (phdata->egl_initialized != true) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("PSP: GLES initialization failed, no OpenGL ES support");
    }

    // Check if OpenGL ES connection has been initialized
    ಯದಿ (_this->gl_data->display != EGL_NO_DISPLAY) {
        ಯದಿ (context != EGL_NO_CONTEXT) {
            status = eglDestroyContext(_this->gl_data->display, context);
            ಯದಿ (status != EGL_TRUE) {
                // Error during OpenGL ES context destroying
                ಪ್ರತ್ಯಾಗಮ SDL_SetError("PSP: OpenGL ES context destroy error");
            }
        }
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

#endif // SDL_VIDEO_DRIVER_PSP
