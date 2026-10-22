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

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_OFFSCREEN

#ضمن "../SDL_sysvideo.h"
#ضمن "../../events/SDL_windowevents_c.h"
#ضمن "../SDL_egl_c.h"

#ضمن "SDL_offscreenwindow.h"

bool OFFSCREEN_Create_دري(SDL_VideoDevice *_this, SDL_دري *دري, SDL_PropertiesID create_props)
{
    SDL_دري_معلومات *offscreen_دري = (SDL_دري_معلومات *)SDL_calloc(1, حجم(SDL_دري_معلومات));

    إذا (!offscreen_دري) {
        أرجع false;
    }

    دري->اندروني = offscreen_دري;

    إذا (دري->x == SDL_WINDOWPOS_UNDEFINED) {
        دري->x = 0;
    }

    إذا (دري->y == SDL_WINDOWPOS_UNDEFINED) {
        دري->y = 0;
    }

    offscreen_دري->sdl_دري = دري;

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_EGL
    إذا (دري->flags & SDL_دري_OPENGL) {

        إذا (!_this->egl_معلومات) {
            أرجع SDL_سيٽ_Error("Cannot create an OPENGL window invalid egl_data");
        }

        offscreen_دري->egl_surface = SDL_EGL_CreateOffscreenSurface(_this, دري->w, دري->h);

        إذا (offscreen_دري->egl_surface == EGL_NO_SURFACE) {
            أرجع SDL_سيٽ_Error("Failed to created an offscreen surface (EGL display: %p)",
                                _this->egl_معلومات->egl_display);
        }
    } وإلا {
        offscreen_دري->egl_surface = EGL_NO_SURFACE;
    }
#جيڪڏهن_پورو // SDL_VIDEO_OPENGL_EGL

    أرجع true;
}

فراغ OFFSCREEN_Destroy_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_دري_معلومات *offscreen_دري = دري->اندروني;

    إذا (offscreen_دري) {
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_EGL
        SDL_EGL_DestroySurface(_this, offscreen_دري->egl_surface);
#جيڪڏهن_پورو
        SDL_free(offscreen_دري);
    }

    دري->اندروني = عدم;
}

فراغ OFFSCREEN_سيٽ_دري_سائيز(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_Send_دري_Event(دري, SDL_EVENT_دري_RESIZED, دري->pending.w, دري->pending.h);
}
#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_OFFSCREEN
