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

#ಆದರೆ defined(SDL_VIDEO_DRIVER_VITA) && defined(SDL_VIDEO_VITA_PIB)
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ "SDL_vitavideo.h"

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

ಶೂನ್ಯ VITA_GLES_KeyboardCallback(Sce_Piglet_Pre_ಅದಲುಬದಲು_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ)
{
    SceCommonDialogUpdateParam commonDialogParam;
    SDL_zero(commonDialogParam);
    commonDialogParam.render_ಗುರಿ.colorFormat = ದತ್ತಾಂಶ->colorFormat;
    commonDialogParam.render_ಗುರಿ.surfaceType = ದತ್ತಾಂಶ->surfaceType;
    commonDialogParam.render_ಗುರಿ.color_Surface_ದತ್ತಾಂಶ = ದತ್ತಾಂಶ->color_Surface_ದತ್ತಾಂಶ;
    commonDialogParam.render_ಗುರಿ.ಆಳ_Surface_ದತ್ತಾಂಶ = ದತ್ತಾಂಶ->ಆಳ_Surface_ದತ್ತಾಂಶ;
    commonDialogParam.render_ಗುರಿ.ಅಗಲ = ದತ್ತಾಂಶ->ಅಗಲ;
    commonDialogParam.render_ಗುರಿ.ಎತ್ತರ = ದತ್ತಾಂಶ->ಎತ್ತರ;
    commonDialogParam.render_ಗುರಿ.stride_ಒಳ_Pixels = ದತ್ತಾಂಶ->stride_ಒಳ_Pixels;
    commonDialogParam.displaySyncObject = ದತ್ತಾಂಶ->displaySyncObject;

    sceCommonDialogUpdate(&commonDialogParam);
}

bool VITA_GLES_ತುಂಬು_Library(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಮಾರ್ಗ)
{
    pibInit(PIB_SHACCCG | PIB_GET_PROC_ADDR_CORE);
    ಹಿಂತಿರುಗಿ true;
}

SDL_Function_ಸೂಚಕ VITA_GLES_Get_Proc_ವಿಳಾಸ(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *proc)
{
    ಹಿಂತಿರುಗಿ egl_Get_Proc_ವಿಳಾಸ(proc);
}

ಶೂನ್ಯ VITA_GLES_UnloadLibrary(SDL_VideoDevice *_this)
{
    eglTerminate(_this->gl_ದತ್ತಾಂಶ->display);
}

ಸ್ಥಿರ EGLint ಅಗಲ = 960;
ಸ್ಥಿರ EGLint ಎತ್ತರ = 544;

SDL_GLContext VITA_GLES_CreateContext(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{

    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wdata = ಕಿಟಕಿ->ಆಂತರಿಕ;

    EGLint attribs[32];
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    EGLConfig config;
    EGLint ಅಂಕೆ_configs;
    PFNEGLPIGLETVITASETPRESWAPCALLBACKSCEPROC pre_ಅದಲುಬದಲು_Callback;
    ಪೂರ್ಣಾಂಕ i;

    ಸ್ಥಿರಾಂಕ EGLint contextAttribs[] = {
        EGL_CONTEXT_CLIENT_ಆವೃತ್ತಿ, 2,
        EGL_NONE
    };

    EGLCHK(display = eglGetDisplay(0));

    EGLCHK(eglInitialize(display, ಖಾಲಿ, ಖಾಲಿ));
    wdata->ಬಳಸುತ್ತದೆ_gles = true;
    ಕಿಟಕಿ->flags |= SDL_ಕಿಟಕಿ_FULLSCREEN;

    EGLCHK(eglBindAPI(EGL_OPENGL_ES_API));

    i = 0;
    attribs[i++] = EGL_RED_ಗಾತ್ರ;
    attribs[i++] = 8;
    attribs[i++] = EGL_GREEN_ಗಾತ್ರ;
    attribs[i++] = 8;
    attribs[i++] = EGL_BLUE_ಗಾತ್ರ;
    attribs[i++] = 8;
    attribs[i++] = EGL_ಆಳ_ಗಾತ್ರ;
    attribs[i++] = 0;
    attribs[i++] = EGL_ALPHA_ಗಾತ್ರ;
    attribs[i++] = 8;
    attribs[i++] = EGL_STENCIL_ಗಾತ್ರ;
    attribs[i++] = 0;

    attribs[i++] = EGL_SURFACE_TYPE;
    attribs[i++] = 5;

    attribs[i++] = EGL_RENDERABLE_TYPE;
    attribs[i++] = EGL_OPENGL_ES2_ಬಿಟ್;

    attribs[i++] = EGL_CONFORMANT;
    attribs[i++] = EGL_OPENGL_ES2_ಬಿಟ್;

    attribs[i++] = EGL_NONE;

    EGLCHK(egl_ಆರಿಸು_Config(display, attribs, &config, 1, &ಅಂಕೆ_configs));

    ಆದರೆ (ಅಂಕೆ_configs == 0) {
        SDL_ಗಣ_Error("No valid EGL configs for requested mode");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    EGLCHK(surface = egl_Create_ಕಿಟಕಿ_Surface(display, config, VITA_ಕಿಟಕಿ_960_X544, ಖಾಲಿ));

    EGLCHK(context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs));

    EGLCHK(eglMakeCurrent(display, surface, surface, context));

    EGLCHK(eglQuerySurface(display, surface, EGL_ಅಗಲ, &ಅಗಲ));
    EGLCHK(eglQuerySurface(display, surface, EGL_ಎತ್ತರ, &ಎತ್ತರ));

    _this->gl_ದತ್ತಾಂಶ->display = display;
    _this->gl_ದತ್ತಾಂಶ->context = context;
    _this->gl_ದತ್ತಾಂಶ->surface = surface;

    pre_ಅದಲುಬದಲು_Callback = (PFNEGLPIGLETVITASETPRESWAPCALLBACKSCEPROC)egl_Get_Proc_ವಿಳಾಸ("eglPigletVitaSetPreSwapCallbackSCE");
    pre_ಅದಲುಬದಲು_Callback(VITA_GLES_KeyboardCallback);

    ಹಿಂತಿರುಗಿ context;
}

bool VITA_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_GLContext context)
{
    ಆದರೆ (!eglMakeCurrent(_this->gl_ದತ್ತಾಂಶ->display, _this->gl_ದತ್ತಾಂಶ->surface,
                        _this->gl_ದತ್ತಾಂಶ->surface, _this->gl_ದತ್ತಾಂಶ->context)) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Unable to make EGL context current");
    }
    ಹಿಂತಿರುಗಿ true;
}

bool VITA_GLES_ಗಣ_ಅದಲುಬದಲು_Interval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ interval)
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

bool VITA_GLES_Get_ಅದಲುಬದಲು_Interval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ *interval)
{
    *interval = _this->gl_ದತ್ತಾಂಶ->swapinterval;
    ಹಿಂತಿರುಗಿ true;
}

bool VITA_GLES_ಅದಲುಬದಲು_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    ಆದರೆ (!egl_ಅದಲುಬದಲು_Buffers(_this->gl_ದತ್ತಾಂಶ->display, _this->gl_ದತ್ತಾಂಶ->surface)) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("eglSwapBuffers() failed");
    }
    ಹಿಂತಿರುಗಿ true;
}

bool VITA_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_Video_ದತ್ತಾಂಶ *phdata = _this->ಆಂತರಿಕ;
    EGLBoolean ಸ್ಥಿತಿ_2;

    ಆದರೆ (phdata->egl_initialized != true) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("VITA: GLES initialization failed, no OpenGL ES support");
    }

    // Check if OpenGL ES connection has been initialized
    ಆದರೆ (_this->gl_ದತ್ತಾಂಶ->display != EGL_NO_DISPLAY) {
        ಆದರೆ (context != EGL_NO_CONTEXT) {
            ಸ್ಥಿತಿ_2 = eglDestroyContext(_this->gl_ದತ್ತಾಂಶ->display, context);
            ಆದರೆ (ಸ್ಥಿತಿ_2 != EGL_TRUE) {
                // Error during OpenGL ES context destroying
                ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("VITA: OpenGL ES context destroy error");
            }
        }
    }

    ಹಿಂತಿರುಗಿ true;
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_VITA
