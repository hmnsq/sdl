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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_PSP

#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_pspvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_pspgl_c.h"

/*****************************************************************************/
// SDL OpenGL/OpenGL ES functions
/*****************************************************************************/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGLCHK(stmt)                           \
    ਕਰੋ {                                       \
        EGLint err;                            \
                                               \
        stmt;                                  \
        err = eglGetError();                   \
        ਜੇ (err != EGL_SUCCESS) {              \
            SDL_ਸੈੱਟ_Error("EGL error %d", err); \
            ਵਾਪਸ ਨਿਰਾ;                          \
        }                                      \
    } ਜਦੋਂ (0)

bool PSP_GL_ਲੱਦੋ_Library(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *ਰਸਤਾ)
{
    ਵਾਪਸ true;
}

/* pspgl doesn't provide this call, so stub it out since SDL requires it.
#define GLSTUB(func,params) void func params {}

GLSTUB(glOrtho,(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top,
                    GLdouble zNear, GLdouble zFar))
*/
SDL_Function_ਸੂਚਕ PSP_GL_Get_Proc_ਪਤਾ(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *proc)
{
    ਵਾਪਸ egl_Get_Proc_ਪਤਾ(proc);
}

ਖਾਲੀ PSP_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    eglTerminate(_this->gl_ਅੰਕੜੇ->display);
}

ਸਥਿਰ EGLint ਚੌੜਾਈ = 480;
ਸਥਿਰ EGLint ਉਚਾਈ = 272;

SDL_GLContext PSP_GL_CreateContext(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{

    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wdata = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    EGLint attribs[32];
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    EGLConfig config;
    EGLint ਅੰਕ_configs;
    ਪੂਰਨ i;

    // EGL init taken from glutCreateWindow() in PSPGL's glut.c.
    EGLCHK(display = eglGetDisplay(0));
    EGLCHK(eglInitialize(display, ਨਿਰਾ, ਨਿਰਾ));
    wdata->ਵਰਤਦਾ_gles = true;
    ਖਿੜਕੀ->flags |= SDL_ਖਿੜਕੀ_FULLSCREEN;

    // Setup the config based on SDL's current values.
    i = 0;
    attribs[i++] = EGL_RED_ਮਾਪ;
    attribs[i++] = _this->gl_config.red_ਮਾਪ;
    attribs[i++] = EGL_GREEN_ਮਾਪ;
    attribs[i++] = _this->gl_config.green_ਮਾਪ;
    attribs[i++] = EGL_BLUE_ਮਾਪ;
    attribs[i++] = _this->gl_config.blue_ਮਾਪ;
    attribs[i++] = EGL_ਡੂੰਘਾਈ_ਮਾਪ;
    attribs[i++] = _this->gl_config.ਡੂੰਘਾਈ_ਮਾਪ;

    ਜੇ (_this->gl_config.alpha_ਮਾਪ) {
        attribs[i++] = EGL_ALPHA_ਮਾਪ;
        attribs[i++] = _this->gl_config.alpha_ਮਾਪ;
    }
    ਜੇ (_this->gl_config.stencil_ਮਾਪ) {
        attribs[i++] = EGL_STENCIL_ਮਾਪ;
        attribs[i++] = _this->gl_config.stencil_ਮਾਪ;
    }

    attribs[i++] = EGL_NONE;

    EGLCHK(egl_ਚੁਣੋ_Config(display, attribs, &config, 1, &ਅੰਕ_configs));

    ਜੇ (ਅੰਕ_configs == 0) {
        SDL_ਸੈੱਟ_Error("No valid EGL configs for requested mode");
        ਵਾਪਸ ਨਿਰਾ;
    }

    EGLCHK(eglGetConfigAttrib(display, config, EGL_ਚੌੜਾਈ, &ਚੌੜਾਈ));
    EGLCHK(eglGetConfigAttrib(display, config, EGL_ਉਚਾਈ, &ਉਚਾਈ));

    EGLCHK(context = eglCreateContext(display, config, ਨਿਰਾ, ਨਿਰਾ));
    EGLCHK(surface = egl_Create_ਖਿੜਕੀ_Surface(display, config, 0, ਨਿਰਾ));
    EGLCHK(eglMakeCurrent(display, surface, surface, context));

    _this->gl_ਅੰਕੜੇ->display = display;
    _this->gl_ਅੰਕੜੇ->context = context;
    _this->gl_ਅੰਕੜੇ->surface = surface;

    ਵਾਪਸ context;
}

bool PSP_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_GLContext context)
{
    ਜੇ (!eglMakeCurrent(_this->gl_ਅੰਕੜੇ->display, _this->gl_ਅੰਕੜੇ->surface,
                        _this->gl_ਅੰਕੜੇ->surface, _this->gl_ਅੰਕੜੇ->context)) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Unable to make EGL context current");
    }
    ਵਾਪਸ true;
}

bool PSP_GL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval(SDL_VideoDevice *_this, ਪੂਰਨ interval)
{
    EGLBoolean ਸਥਿਤੀ;
    ਸਥਿਤੀ = egl_ਅਦਲਾ_ਬਦਲੀ_Interval(_this->gl_ਅੰਕੜੇ->display, interval);
    ਜੇ (ਸਥਿਤੀ == EGL_TRUE) {
        // Return success to upper level
        _this->gl_ਅੰਕੜੇ->swapinterval = interval;
        ਵਾਪਸ true;
    }
    // Failed to set swap interval
    ਵਾਪਸ SDL_ਸੈੱਟ_Error("Unable to set the EGL swap interval");
}

bool PSP_GL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval(SDL_VideoDevice *_this, ਪੂਰਨ *interval)
{
    *interval = _this->gl_ਅੰਕੜੇ->swapinterval;
    ਵਾਪਸ true;
}

bool PSP_GL_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    ਜੇ (!egl_ਅਦਲਾ_ਬਦਲੀ_Buffers(_this->gl_ਅੰਕੜੇ->display, _this->gl_ਅੰਕੜੇ->surface)) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("eglSwapBuffers() failed");
    }
    ਵਾਪਸ true;
}

bool PSP_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_Video_ਅੰਕੜੇ *phdata = _this->ਅੰਦਰੂਨੀ;
    EGLBoolean ਸਥਿਤੀ;

    ਜੇ (phdata->egl_initialized != true) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("PSP: GLES initialization failed, no OpenGL ES support");
    }

    // Check if OpenGL ES connection has been initialized
    ਜੇ (_this->gl_ਅੰਕੜੇ->display != EGL_NO_DISPLAY) {
        ਜੇ (context != EGL_NO_CONTEXT) {
            ਸਥਿਤੀ = eglDestroyContext(_this->gl_ਅੰਕੜੇ->display, context);
            ਜੇ (ਸਥਿਤੀ != EGL_TRUE) {
                // Error during OpenGL ES context destroying
                ਵਾਪਸ SDL_ਸੈੱਟ_Error("PSP: OpenGL ES context destroy error");
            }
        }
    }
    ਵਾਪਸ true;
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_PSP
