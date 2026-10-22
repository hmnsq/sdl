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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_PSP

#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ "SDL_pspvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_pspgl_c.h"

/*****************************************************************************/
// SDL OpenGL/OpenGL ES functions
/*****************************************************************************/
#ವ್ಯಾಖ್ಯಾನಿಸು EGLCHK(stmt)                           \
    ಮಾಡು {                                       \
        EGLint err;                            \
                                               \
        stmt;                                  \
        err = eglGetError();                   \
        ಆದರೆ (err != EGL_SUCCESS) {              \
            SDL_ಗಣ_Error("EGL error %d", err); \
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;                          \
        }                                      \
    } ಆಗ (0)

bool PSP_GL_ತುಂಬು_Library(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಮಾರ್ಗ)
{
    ಹಿಂತಿರುಗಿ true;
}

/* pspgl doesn't provide this call, so stub it out since SDL requires it.
#define GLSTUB(func,params) void func params {}

GLSTUB(glOrtho,(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top,
                    GLdouble zNear, GLdouble zFar))
*/
SDL_Function_ಸೂಚಕ PSP_GL_Get_Proc_ವಿಳಾಸ(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *proc)
{
    ಹಿಂತಿರುಗಿ egl_Get_Proc_ವಿಳಾಸ(proc);
}

ಶೂನ್ಯ PSP_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    eglTerminate(_this->gl_ದತ್ತಾಂಶ->display);
}

ಸ್ಥಿರ EGLint ಅಗಲ = 480;
ಸ್ಥಿರ EGLint ಎತ್ತರ = 272;

SDL_GLContext PSP_GL_CreateContext(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{

    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wdata = ಕಿಟಕಿ->ಆಂತರಿಕ;

    EGLint attribs[32];
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    EGLConfig config;
    EGLint ಅಂಕೆ_configs;
    ಪೂರ್ಣಾಂಕ i;

    // EGL init taken from glutCreateWindow() in PSPGL's glut.c.
    EGLCHK(display = eglGetDisplay(0));
    EGLCHK(eglInitialize(display, ಖಾಲಿ, ಖಾಲಿ));
    wdata->ಬಳಸುತ್ತದೆ_gles = true;
    ಕಿಟಕಿ->flags |= SDL_ಕಿಟಕಿ_FULLSCREEN;

    // Setup the config based on SDL's current values.
    i = 0;
    attribs[i++] = EGL_RED_ಗಾತ್ರ;
    attribs[i++] = _this->gl_config.red_ಗಾತ್ರ;
    attribs[i++] = EGL_GREEN_ಗಾತ್ರ;
    attribs[i++] = _this->gl_config.green_ಗಾತ್ರ;
    attribs[i++] = EGL_BLUE_ಗಾತ್ರ;
    attribs[i++] = _this->gl_config.blue_ಗಾತ್ರ;
    attribs[i++] = EGL_ಆಳ_ಗಾತ್ರ;
    attribs[i++] = _this->gl_config.ಆಳ_ಗಾತ್ರ;

    ಆದರೆ (_this->gl_config.alpha_ಗಾತ್ರ) {
        attribs[i++] = EGL_ALPHA_ಗಾತ್ರ;
        attribs[i++] = _this->gl_config.alpha_ಗಾತ್ರ;
    }
    ಆದರೆ (_this->gl_config.stencil_ಗಾತ್ರ) {
        attribs[i++] = EGL_STENCIL_ಗಾತ್ರ;
        attribs[i++] = _this->gl_config.stencil_ಗಾತ್ರ;
    }

    attribs[i++] = EGL_NONE;

    EGLCHK(egl_ಆರಿಸು_Config(display, attribs, &config, 1, &ಅಂಕೆ_configs));

    ಆದರೆ (ಅಂಕೆ_configs == 0) {
        SDL_ಗಣ_Error("No valid EGL configs for requested mode");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    EGLCHK(eglGetConfigAttrib(display, config, EGL_ಅಗಲ, &ಅಗಲ));
    EGLCHK(eglGetConfigAttrib(display, config, EGL_ಎತ್ತರ, &ಎತ್ತರ));

    EGLCHK(context = eglCreateContext(display, config, ಖಾಲಿ, ಖಾಲಿ));
    EGLCHK(surface = egl_Create_ಕಿಟಕಿ_Surface(display, config, 0, ಖಾಲಿ));
    EGLCHK(eglMakeCurrent(display, surface, surface, context));

    _this->gl_ದತ್ತಾಂಶ->display = display;
    _this->gl_ದತ್ತಾಂಶ->context = context;
    _this->gl_ದತ್ತಾಂಶ->surface = surface;

    ಹಿಂತಿರುಗಿ context;
}

bool PSP_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_GLContext context)
{
    ಆದರೆ (!eglMakeCurrent(_this->gl_ದತ್ತಾಂಶ->display, _this->gl_ದತ್ತಾಂಶ->surface,
                        _this->gl_ದತ್ತಾಂಶ->surface, _this->gl_ದತ್ತಾಂಶ->context)) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Unable to make EGL context current");
    }
    ಹಿಂತಿರುಗಿ true;
}

bool PSP_GL_ಗಣ_ಅದಲುಬದಲು_Interval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ interval)
{
    EGLBoolean ಸ್ಥಿತಿ_2;
    ಸ್ಥಿತಿ_2 = egl_ಅದಲುಬದಲು_Interval(_this->gl_ದತ್ತಾಂಶ->display, interval);
    ಆದರೆ (ಸ್ಥಿತಿ_2 == EGL_TRUE) {
        // Return success to upper level
        _this->gl_ದತ್ತಾಂಶ->swapinterval = interval;
        ಹಿಂತಿರುಗಿ true;
    }
    // Failed to set swap interval
    ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Unable to set the EGL swap interval");
}

bool PSP_GL_Get_ಅದಲುಬದಲು_Interval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ *interval)
{
    *interval = _this->gl_ದತ್ತಾಂಶ->swapinterval;
    ಹಿಂತಿರುಗಿ true;
}

bool PSP_GL_ಅದಲುಬದಲು_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    ಆದರೆ (!egl_ಅದಲುಬದಲು_Buffers(_this->gl_ದತ್ತಾಂಶ->display, _this->gl_ದತ್ತಾಂಶ->surface)) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("eglSwapBuffers() failed");
    }
    ಹಿಂತಿರುಗಿ true;
}

bool PSP_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_Video_ದತ್ತಾಂಶ *phdata = _this->ಆಂತರಿಕ;
    EGLBoolean ಸ್ಥಿತಿ_2;

    ಆದರೆ (phdata->egl_initialized != true) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("PSP: GLES initialization failed, no OpenGL ES support");
    }

    // Check if OpenGL ES connection has been initialized
    ಆದರೆ (_this->gl_ದತ್ತಾಂಶ->display != EGL_NO_DISPLAY) {
        ಆದರೆ (context != EGL_NO_CONTEXT) {
            ಸ್ಥಿತಿ_2 = eglDestroyContext(_this->gl_ದತ್ತಾಂಶ->display, context);
            ಆದರೆ (ಸ್ಥಿತಿ_2 != EGL_TRUE) {
                // Error during OpenGL ES context destroying
                ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("PSP: OpenGL ES context destroy error");
            }
        }
    }
    ಹಿಂತಿರುಗಿ true;
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_PSP
