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
#ضمن "SDL_internal.h"

#که_تعریف_شوی SDL_VIDEO_DRIVER_OFFSCREEN

#ضمن "../SDL_sysvideo.h"
#ضمن "../../events/SDL_windowevents_c.h"
#ضمن "../SDL_egl_c.h"

#ضمن "SDL_offscreenwindow.h"

bool OFFSCREEN_Create_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_PropertiesID create_props)
{
    SDL_کړکۍ_معلومات *offscreen_کړکۍ = (SDL_کړکۍ_معلومات *)SDL_calloc(1, حجم(SDL_کړکۍ_معلومات));

    إذا (!offscreen_کړکۍ) {
        أرجع false;
    }

    کړکۍ->دننی = offscreen_کړکۍ;

    إذا (کړکۍ->x == SDL_WINDOWPOS_UNDEFINED) {
        کړکۍ->x = 0;
    }

    إذا (کړکۍ->y == SDL_WINDOWPOS_UNDEFINED) {
        کړکۍ->y = 0;
    }

    offscreen_کړکۍ->sdl_کړکۍ = کړکۍ;

#که_تعریف_شوی SDL_VIDEO_OPENGL_EGL
    إذا (کړکۍ->flags & SDL_کړکۍ_OPENGL) {

        إذا (!_this->egl_معلومات) {
            أرجع SDL_سېټ_Error("Cannot create an OPENGL window invalid egl_data");
        }

        offscreen_کړکۍ->egl_surface = SDL_EGL_CreateOffscreenSurface(_this, کړکۍ->w, کړکۍ->h);

        إذا (offscreen_کړکۍ->egl_surface == EGL_NO_SURFACE) {
            أرجع SDL_سېټ_Error("Failed to created an offscreen surface (EGL display: %p)",
                                _this->egl_معلومات->egl_display);
        }
    } وإلا {
        offscreen_کړکۍ->egl_surface = EGL_NO_SURFACE;
    }
#د_که_پای // SDL_VIDEO_OPENGL_EGL

    أرجع true;
}

فراغ OFFSCREEN_Destroy_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_کړکۍ_معلومات *offscreen_کړکۍ = کړکۍ->دننی;

    إذا (offscreen_کړکۍ) {
#که_تعریف_شوی SDL_VIDEO_OPENGL_EGL
        SDL_EGL_DestroySurface(_this, offscreen_کړکۍ->egl_surface);
#د_که_پای
        SDL_free(offscreen_کړکۍ);
    }

    کړکۍ->دننی = عدم;
}

فراغ OFFSCREEN_سېټ_کړکۍ_اندازه(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_RESIZED, کړکۍ->pending.w, کړکۍ->pending.h);
}
#د_که_پای // SDL_VIDEO_DRIVER_OFFSCREEN
