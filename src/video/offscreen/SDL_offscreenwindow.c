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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_OFFSCREEN

#అన్తర్భావ "../SDL_sysvideo.h"
#అన్తర్భావ "../../events/SDL_windowevents_c.h"
#అన్తర్భావ "../SDL_egl_c.h"

#అన్తర్భావ "SDL_offscreenwindow.h"

bool OFFSCREEN_Create_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID create_props)
{
    SDL_కిటికీ_దత్తాంశం *offscreen_కిటికీ = (SDL_కిటికీ_దత్తాంశం *)SDL_calloc(1, పరిమాణం(SDL_కిటికీ_దత్తాంశం));

    ఒకవేళ (!offscreen_కిటికీ) {
        తిరిగి false;
    }

    కిటికీ->అంతర్గత = offscreen_కిటికీ;

    ఒకవేళ (కిటికీ->x == SDL_WINDOWPOS_UNDEFINED) {
        కిటికీ->x = 0;
    }

    ఒకవేళ (కిటికీ->y == SDL_WINDOWPOS_UNDEFINED) {
        కిటికీ->y = 0;
    }

    offscreen_కిటికీ->sdl_కిటికీ = కిటికీ;

#నిర్వచితమైతే SDL_VIDEO_OPENGL_EGL
    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_OPENGL) {

        ఒకవేళ (!_this->egl_దత్తాంశం) {
            తిరిగి SDL_సమితి_Error("Cannot create an OPENGL window invalid egl_data");
        }

        offscreen_కిటికీ->egl_surface = SDL_EGL_CreateOffscreenSurface(_this, కిటికీ->w, కిటికీ->h);

        ఒకవేళ (offscreen_కిటికీ->egl_surface == EGL_NO_SURFACE) {
            తిరిగి SDL_సమితి_Error("Failed to created an offscreen surface (EGL display: %p)",
                                _this->egl_దత్తాంశం->egl_display);
        }
    } లేకపోతే {
        offscreen_కిటికీ->egl_surface = EGL_NO_SURFACE;
    }
#అయితే_ముగింపు // SDL_VIDEO_OPENGL_EGL

    తిరిగి true;
}

శూన్య OFFSCREEN_Destroy_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *offscreen_కిటికీ = కిటికీ->అంతర్గత;

    ఒకవేళ (offscreen_కిటికీ) {
#నిర్వచితమైతే SDL_VIDEO_OPENGL_EGL
        SDL_EGL_DestroySurface(_this, offscreen_కిటికీ->egl_surface);
#అయితే_ముగింపు
        SDL_free(offscreen_కిటికీ);
    }

    కిటికీ->అంతర్గత = ఖాళీ;
}

శూన్య OFFSCREEN_సమితి_కిటికీ_కొలత(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_RESIZED, కిటికీ->pending.w, కిటికీ->pending.h);
}
#అయితే_ముగింపు // SDL_VIDEO_DRIVER_OFFSCREEN
