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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_OFFSCREEN

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_windowevents_c.h"
#ಅನ್ತರ್ಭಾವ "../SDL_egl_c.h"

#ಅನ್ತರ್ಭಾವ "SDL_offscreenwindow.h"

bool OFFSCREEN_Create_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PropertiesID create_props)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *offscreen_ಕಿಟಕಿ = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ));

    ಆದರೆ (!offscreen_ಕಿಟಕಿ) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಕಿಟಕಿ->ಆಂತರಿಕ = offscreen_ಕಿಟಕಿ;

    ಆದರೆ (ಕಿಟಕಿ->x == SDL_WINDOWPOS_UNDEFINED) {
        ಕಿಟಕಿ->x = 0;
    }

    ಆದರೆ (ಕಿಟಕಿ->y == SDL_WINDOWPOS_UNDEFINED) {
        ಕಿಟಕಿ->y = 0;
    }

    offscreen_ಕಿಟಕಿ->sdl_ಕಿಟಕಿ = ಕಿಟಕಿ;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_EGL
    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_OPENGL) {

        ಆದರೆ (!_this->egl_ದತ್ತಾಂಶ) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Cannot create an OPENGL window invalid egl_data");
        }

        offscreen_ಕಿಟಕಿ->egl_surface = SDL_EGL_CreateOffscreenSurface(_this, ಕಿಟಕಿ->w, ಕಿಟಕಿ->h);

        ಆದರೆ (offscreen_ಕಿಟಕಿ->egl_surface == EGL_NO_SURFACE) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Failed to created an offscreen surface (EGL display: %p)",
                                _this->egl_ದತ್ತಾಂಶ->egl_display);
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        offscreen_ಕಿಟಕಿ->egl_surface = EGL_NO_SURFACE;
    }
#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_OPENGL_EGL

    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ OFFSCREEN_Destroy_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *offscreen_ಕಿಟಕಿ = ಕಿಟಕಿ->ಆಂತರಿಕ;

    ಆದರೆ (offscreen_ಕಿಟಕಿ) {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_EGL
        SDL_EGL_DestroySurface(_this, offscreen_ಕಿಟಕಿ->egl_surface);
#ಆದರೆ_ಅಂತ್ಯ
        SDL_free(offscreen_ಕಿಟಕಿ);
    }

    ಕಿಟಕಿ->ಆಂತರಿಕ = ಖಾಲಿ;
}

ಶೂನ್ಯ OFFSCREEN_ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_RESIZED, ಕಿಟಕಿ->pending.w, ಕಿಟಕಿ->pending.h);
}
#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_OFFSCREEN
