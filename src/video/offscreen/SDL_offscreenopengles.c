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

#ಆದರೆ defined(SDL_VIDEO_DRIVER_OFFSCREEN) && defined(SDL_VIDEO_OPENGL_EGL)

#ಅನ್ತರ್ಭಾವ "SDL_offscreenopengles.h"
#ಅನ್ತರ್ಭಾವ "SDL_offscreenvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_offscreenwindow.h"

// EGL implementation of SDL OpenGL support

bool OFFSCREEN_GLES_ತುಂಬು_Library(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಮಾರ್ಗ)
{
    ಆದರೆ (!SDL_EGL_ತುಂಬು_Library_Only(_this, ಮಾರ್ಗ)) {
        ಹಿಂತಿರುಗಿ false;
    }

    /* driver_loaded gets incremented by SDL_GL_LoadLibrary when we return,
       but SDL_EGL_InitializeOffscreen checks that we're loaded before then,
       so temporarily bump it since we know that LoadLibraryOnly succeeded. */
    bool ಫಲಿತಾಂಶ;
    _this->gl_config.driver_loaded++;
    ಫಲಿತಾಂಶ = SDL_EGL_InitializeOffscreen(_this, 0);
    _this->gl_config.driver_loaded--;
    ಆದರೆ (!ಫಲಿತಾಂಶ) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಆದರೆ (!SDL_EGL_ಆರಿಸು_Config(_this)) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಹಿಂತಿರುಗಿ true;
}

SDL_GLContext OFFSCREEN_GLES_CreateContext(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *offscreen_ಕಿಟಕಿ = ಕಿಟಕಿ->ಆಂತರಿಕ;

    SDL_GLContext context;
    context = SDL_EGL_CreateContext(_this, offscreen_ಕಿಟಕಿ->egl_surface);

    ಹಿಂತಿರುಗಿ context;
}

bool OFFSCREEN_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_GLContext context)
{
    ಆದರೆ (ಕಿಟಕಿ) {
        EGLSurface egl_surface = ಕಿಟಕಿ->ಆಂತರಿಕ->egl_surface;
        ಹಿಂತಿರುಗಿ SDL_EGL_MakeCurrent(_this, egl_surface, context);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ SDL_EGL_MakeCurrent(_this, ಖಾಲಿ, ಖಾಲಿ);
    }
}

bool OFFSCREEN_GLES_ಅದಲುಬದಲು_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *offscreen_wind = ಕಿಟಕಿ->ಆಂತರಿಕ;

    ಹಿಂತಿರುಗಿ SDL_EGL_ಅದಲುಬದಲು_Buffers(_this, offscreen_wind->egl_surface);
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_OFFSCREEN && SDL_VIDEO_OPENGL_EGL
