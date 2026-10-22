/*
  Simple DirectMedia Layer
  Copyright (C) 2026 BlackBerry Limited

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
#ಅನ್ತರ್ಭಾವ "SDL_qnx.h"

#ಅನ್ತರ್ಭಾವ "../SDL_egl_c.h"

/**
 * Detertmines the pixel format to use based on the current display and EGL
 * configuration.
 */
ಪೂರ್ಣಾಂಕ QNX_ಆರಿಸು_Format(SDL_VideoDevice *_this, EGLConfig egl_conf)
{
    EGLint ಬಫರ್_ಬಿಟ್_ಆಳ;
    EGLint alpha_ಬಿಟ್_ಆಳ;

    _this->egl_ದತ್ತಾಂಶ->eglGetConfigAttrib(_this->egl_ದತ್ತಾಂಶ->egl_display, egl_conf, EGL_ಬಫರ್_ಗಾತ್ರ, &ಬಫರ್_ಬಿಟ್_ಆಳ);
    _this->egl_ದತ್ತಾಂಶ->eglGetConfigAttrib(_this->egl_ದತ್ತಾಂಶ->egl_display, egl_conf, EGL_ALPHA_ಗಾತ್ರ, &alpha_ಬಿಟ್_ಆಳ);

    ಆಯ್ಕೆ (ಬಫರ್_ಬಿಟ್_ಆಳ) {
        ಸ್ಥಿತಿ 32:
            ಹಿಂತಿರುಗಿ SCREEN_FORMAT_RGBX8888;
        ಸ್ಥಿತಿ 24:
            ಹಿಂತಿರುಗಿ SCREEN_FORMAT_RGB888;
        ಸ್ಥಿತಿ 16:
            ಆಯ್ಕೆ (alpha_ಬಿಟ್_ಆಳ) {
                ಸ್ಥಿತಿ 4:
                    ಹಿಂತಿರುಗಿ SCREEN_FORMAT_RGBX4444;
                ಸ್ಥಿತಿ 1:
                    ಹಿಂತಿರುಗಿ SCREEN_FORMAT_RGBA5551;
                ಪೂರ್ವನಿಯೋಜಿತ:
                    ಹಿಂತಿರುಗಿ SCREEN_FORMAT_RGB565;
            }
        ಪೂರ್ವನಿಯೋಜಿತ:
            ಹಿಂತಿರುಗಿ 0;
    }
}

/**
 * Initializes the EGL library.
 */
bool QNX_GLES_ತುಂಬು_Library(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *egl_ಮಾರ್ಗ)
{
    ಹಿಂತಿರುಗಿ SDL_EGL_ತುಂಬು_Library(_this, egl_ಮಾರ್ಗ, EGL_DEFAULT_DISPLAY);
}

/**
 * Finds the address of an EGL extension function.
 */
SDL_Function_ಸೂಚಕ QNX_GLES_Get_Proc_ವಿಳಾಸ(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *proc)
{
    ಹಿಂತಿರುಗಿ SDL_EGL_Get_Proc_ವಿಳಾಸ_ಆಂತರಿಕ(_this, proc);
}

/**
 * Associates the given window with the necessary EGL structures for drawing and
 * displaying content.
 */
SDL_GLContext QNX_GLES_CreateContext(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ   *impl = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)ಕಿಟಕಿ->ಆಂತರಿಕ;
    EGLContext      context;

    context = SDL_EGL_CreateContext(_this, impl->egl_surface);
    impl->context = context;

    ಹಿಂತಿರುಗಿ context;
}

/**
 * Sets a new value for the number of frames to display before swapping buffers.
 */
bool QNX_GLES_ಗಣ_ಅದಲುಬದಲು_Interval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ interval)
{
    ಹಿಂತಿರುಗಿ SDL_EGL_ಗಣ_ಅದಲುಬದಲು_Interval(_this, interval);
}

/**
 * Gets the value for the number of frames to display before swapping buffers.
 */
bool QNX_GLES_Get_ಅದಲುಬದಲು_Interval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ *interval)
{
    ಹಿಂತಿರುಗಿ SDL_EGL_Get_ಅದಲುಬದಲು_Interval(_this, interval);
}

/**
 * Swaps the EGL buffers associated with the given window
 */
bool QNX_GLES_ಅದಲುಬದಲು_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ   *impl = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)ಕಿಟಕಿ->ಆಂತರಿಕ;
    {
        ಆದರೆ (impl->resize) {
            EGLSurface surface;

            ಆದರೆ (!SDL_EGL_MakeCurrent(_this, EGL_NO_SURFACE, impl->context)) {
                ಹಿಂತಿರುಗಿ false;
            }
            SDL_EGL_DestroySurface(_this, impl->egl_surface);

            surface = SDL_EGL_CreateSurface(_this, ಕಿಟಕಿ, (Native_ಕಿಟಕಿ_Type)impl->ಕಿಟಕಿ);
            ಆದರೆ (surface == EGL_NO_SURFACE) {
                ಹಿಂತಿರುಗಿ false;
            }
            SDL_ಗಣ_ಸೂಚಕ_Property(SDL_Get_ಕಿಟಕಿ_Properties(ಕಿಟಕಿ), SDL_PROP_ಕಿಟಕಿ_QNX_SURFACE_ಸೂಚಕ, surface);

            ಆದರೆ (!SDL_EGL_MakeCurrent(_this, surface, impl->context)) {
                ಹಿಂತಿರುಗಿ false;
            }

            impl->egl_surface = surface;
            impl->resize = false;
        }
    }

    ಹಿಂತಿರುಗಿ SDL_EGL_ಅದಲುಬದಲು_Buffers(_this, impl->egl_surface);
}

/**
 * Destroys a context.
 */
bool QNX_GLES_DeleteContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    ಹಿಂತಿರುಗಿ SDL_EGL_DestroyContext(_this, context);
}

/**
 * Terminates access to the EGL library.
 */
ಶೂನ್ಯ QNX_GLES_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_EGL_UnloadLibrary(_this);
}

SDL_EGL_MakeCurrent_impl(QNX)
