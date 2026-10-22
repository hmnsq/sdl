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
#अन्तर्भाव "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_PSP

#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <string.h>

#अन्तर्भाव "SDL_pspvideo.h"
#अन्तर्भाव "SDL_pspgl_c.h"

/*****************************************************************************/
// SDL OpenGL/OpenGL ES functions
/*****************************************************************************/
#define EGLCHK(stmt)                           \
    करोहि {                                       \
        EGLint err;                            \
                                               \
        stmt;                                  \
        err = eglGetError();                   \
        सचे (err != EGL_SUCCESS) {              \
            SDL_SetError("EGL error %d", err); \
            पटिनिवत्त रिक्त;                          \
        }                                      \
    } याव (0)

bool PSP_GL_LoadLibrary(SDL_VideoDevice *_this, ध्रुव वर्ण *path)
{
    पटिनिवत्त true;
}

/* pspgl doesn't provide this call, so stub it out since SDL requires it.
#define GLSTUB(func,params) void func params {}

GLSTUB(glOrtho,(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top,
                    GLdouble zNear, GLdouble zFar))
*/
SDL_FunctionPointer PSP_GL_GetProcAddress(SDL_VideoDevice *_this, ध्रुव वर्ण *proc)
{
    पटिनिवत्त eglGetProcAddress(proc);
}

शून्य PSP_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    eglTerminate(_this->gl_data->display);
}

स्थिर EGLint width = 480;
स्थिर EGLint height = 272;

SDL_GLContext PSP_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{

    SDL_WindowData *wdata = window->internal;

    EGLint attribs[32];
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    EGLConfig config;
    EGLint अङ्कः_configs;
    पूर्णाङ्क i;

    // EGL init taken from glutCreateWindow() in PSPGL's glut.c.
    EGLCHK(display = eglGetDisplay(0));
    EGLCHK(eglInitialize(display, रिक्त, रिक्त));
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

    सचे (_this->gl_config.alpha_size) {
        attribs[i++] = EGL_ALPHA_SIZE;
        attribs[i++] = _this->gl_config.alpha_size;
    }
    सचे (_this->gl_config.stencil_size) {
        attribs[i++] = EGL_STENCIL_SIZE;
        attribs[i++] = _this->gl_config.stencil_size;
    }

    attribs[i++] = EGL_NONE;

    EGLCHK(eglChooseConfig(display, attribs, &config, 1, &अङ्कः_configs));

    सचे (अङ्कः_configs == 0) {
        SDL_SetError("No valid EGL configs for requested mode");
        पटिनिवत्त रिक्त;
    }

    EGLCHK(eglGetConfigAttrib(display, config, EGL_WIDTH, &width));
    EGLCHK(eglGetConfigAttrib(display, config, EGL_HEIGHT, &height));

    EGLCHK(context = eglCreateContext(display, config, रिक्त, रिक्त));
    EGLCHK(surface = eglCreateWindowSurface(display, config, 0, रिक्त));
    EGLCHK(eglMakeCurrent(display, surface, surface, context));

    _this->gl_data->display = display;
    _this->gl_data->context = context;
    _this->gl_data->surface = surface;

    पटिनिवत्त context;
}

bool PSP_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context)
{
    सचे (!eglMakeCurrent(_this->gl_data->display, _this->gl_data->surface,
                        _this->gl_data->surface, _this->gl_data->context)) {
        पटिनिवत्त SDL_SetError("Unable to make EGL context current");
    }
    पटिनिवत्त true;
}

bool PSP_GL_SetSwapInterval(SDL_VideoDevice *_this, पूर्णाङ्क interval)
{
    EGLBoolean status;
    status = eglSwapInterval(_this->gl_data->display, interval);
    सचे (status == EGL_TRUE) {
        // Return success to upper level
        _this->gl_data->swapinterval = interval;
        पटिनिवत्त true;
    }
    // Failed to set swap interval
    पटिनिवत्त SDL_SetError("Unable to set the EGL swap interval");
}

bool PSP_GL_GetSwapInterval(SDL_VideoDevice *_this, पूर्णाङ्क *interval)
{
    *interval = _this->gl_data->swapinterval;
    पटिनिवत्त true;
}

bool PSP_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    सचे (!eglSwapBuffers(_this->gl_data->display, _this->gl_data->surface)) {
        पटिनिवत्त SDL_SetError("eglSwapBuffers() failed");
    }
    पटिनिवत्त true;
}

bool PSP_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_VideoData *phdata = _this->internal;
    EGLBoolean status;

    सचे (phdata->egl_initialized != true) {
        पटिनिवत्त SDL_SetError("PSP: GLES initialization failed, no OpenGL ES support");
    }

    // Check if OpenGL ES connection has been initialized
    सचे (_this->gl_data->display != EGL_NO_DISPLAY) {
        सचे (context != EGL_NO_CONTEXT) {
            status = eglDestroyContext(_this->gl_data->display, context);
            सचे (status != EGL_TRUE) {
                // Error during OpenGL ES context destroying
                पटिनिवत्त SDL_SetError("PSP: OpenGL ES context destroy error");
            }
        }
    }
    पटिनिवत्त true;
}

#endif // SDL_VIDEO_DRIVER_PSP
