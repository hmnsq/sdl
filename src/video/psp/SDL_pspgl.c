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
#അന്തര്ഭാവ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_PSP

#അന്തര്ഭാവ <stdlib.h>
#അന്തര്ഭാവ <string.h>

#അന്തര്ഭാവ "SDL_pspvideo.h"
#അന്തര്ഭാവ "SDL_pspgl_c.h"

/*****************************************************************************/
// SDL OpenGL/OpenGL ES functions
/*****************************************************************************/
#define EGLCHK(stmt)                           \
    ചെയ്യുക {                                       \
        EGLint err;                            \
                                               \
        stmt;                                  \
        err = eglGetError();                   \
        എങ്കിൽ (err != EGL_SUCCESS) {              \
            SDL_SetError("EGL error %d", err); \
            തിരികെ ശൂന്യ;                          \
        }                                      \
    } ആകുമ്പോൾ (0)

bool PSP_GL_LoadLibrary(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *path)
{
    തിരികെ true;
}

/* pspgl doesn't provide this call, so stub it out since SDL requires it.
#define GLSTUB(func,params) void func params {}

GLSTUB(glOrtho,(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top,
                    GLdouble zNear, GLdouble zFar))
*/
SDL_FunctionPointer PSP_GL_GetProcAddress(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *proc)
{
    തിരികെ eglGetProcAddress(proc);
}

ശൂന്യം PSP_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    eglTerminate(_this->gl_data->display);
}

സ്ഥിതം EGLint width = 480;
സ്ഥിതം EGLint height = 272;

SDL_GLContext PSP_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{

    SDL_WindowData *wdata = window->internal;

    EGLint attribs[32];
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    EGLConfig config;
    EGLint അക്കം_configs;
    പൂർണ്ണസംഖ്യ i;

    // EGL init taken from glutCreateWindow() in PSPGL's glut.c.
    EGLCHK(display = eglGetDisplay(0));
    EGLCHK(eglInitialize(display, ശൂന്യ, ശൂന്യ));
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

    എങ്കിൽ (_this->gl_config.alpha_size) {
        attribs[i++] = EGL_ALPHA_SIZE;
        attribs[i++] = _this->gl_config.alpha_size;
    }
    എങ്കിൽ (_this->gl_config.stencil_size) {
        attribs[i++] = EGL_STENCIL_SIZE;
        attribs[i++] = _this->gl_config.stencil_size;
    }

    attribs[i++] = EGL_NONE;

    EGLCHK(eglChooseConfig(display, attribs, &config, 1, &അക്കം_configs));

    എങ്കിൽ (അക്കം_configs == 0) {
        SDL_SetError("No valid EGL configs for requested mode");
        തിരികെ ശൂന്യ;
    }

    EGLCHK(eglGetConfigAttrib(display, config, EGL_WIDTH, &width));
    EGLCHK(eglGetConfigAttrib(display, config, EGL_HEIGHT, &height));

    EGLCHK(context = eglCreateContext(display, config, ശൂന്യ, ശൂന്യ));
    EGLCHK(surface = eglCreateWindowSurface(display, config, 0, ശൂന്യ));
    EGLCHK(eglMakeCurrent(display, surface, surface, context));

    _this->gl_data->display = display;
    _this->gl_data->context = context;
    _this->gl_data->surface = surface;

    തിരികെ context;
}

bool PSP_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context)
{
    എങ്കിൽ (!eglMakeCurrent(_this->gl_data->display, _this->gl_data->surface,
                        _this->gl_data->surface, _this->gl_data->context)) {
        തിരികെ SDL_SetError("Unable to make EGL context current");
    }
    തിരികെ true;
}

bool PSP_GL_SetSwapInterval(SDL_VideoDevice *_this, പൂർണ്ണസംഖ്യ interval)
{
    EGLBoolean status;
    status = eglSwapInterval(_this->gl_data->display, interval);
    എങ്കിൽ (status == EGL_TRUE) {
        // Return success to upper level
        _this->gl_data->swapinterval = interval;
        തിരികെ true;
    }
    // Failed to set swap interval
    തിരികെ SDL_SetError("Unable to set the EGL swap interval");
}

bool PSP_GL_GetSwapInterval(SDL_VideoDevice *_this, പൂർണ്ണസംഖ്യ *interval)
{
    *interval = _this->gl_data->swapinterval;
    തിരികെ true;
}

bool PSP_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    എങ്കിൽ (!eglSwapBuffers(_this->gl_data->display, _this->gl_data->surface)) {
        തിരികെ SDL_SetError("eglSwapBuffers() failed");
    }
    തിരികെ true;
}

bool PSP_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_VideoData *phdata = _this->internal;
    EGLBoolean status;

    എങ്കിൽ (phdata->egl_initialized != true) {
        തിരികെ SDL_SetError("PSP: GLES initialization failed, no OpenGL ES support");
    }

    // Check if OpenGL ES connection has been initialized
    എങ്കിൽ (_this->gl_data->display != EGL_NO_DISPLAY) {
        എങ്കിൽ (context != EGL_NO_CONTEXT) {
            status = eglDestroyContext(_this->gl_data->display, context);
            എങ്കിൽ (status != EGL_TRUE) {
                // Error during OpenGL ES context destroying
                തിരികെ SDL_SetError("PSP: OpenGL ES context destroy error");
            }
        }
    }
    തിരികെ true;
}

#endif // SDL_VIDEO_DRIVER_PSP
