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

#اگر_تعریف_شده SDL_VIDEO_DRIVER_OFFSCREEN

#ضمن "../SDL_sysvideo.h"
#ضمن "../../events/SDL_windowevents_c.h"
#ضمن "../SDL_egl_c.h"

#ضمن "SDL_offscreenwindow.h"

bool OFFSCREEN_Create_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_PropertiesID create_props)
{
    SDL_پنجره_داده *offscreen_پنجره = (SDL_پنجره_داده *)SDL_calloc(1, حجم(SDL_پنجره_داده));

    إذا (!offscreen_پنجره) {
        أرجع false;
    }

    پنجره->داخلی = offscreen_پنجره;

    إذا (پنجره->x == SDL_WINDOWPOS_UNDEFINED) {
        پنجره->x = 0;
    }

    إذا (پنجره->y == SDL_WINDOWPOS_UNDEFINED) {
        پنجره->y = 0;
    }

    offscreen_پنجره->sdl_پنجره = پنجره;

#اگر_تعریف_شده SDL_VIDEO_OPENGL_EGL
    إذا (پنجره->flags & SDL_پنجره_OPENGL) {

        إذا (!_this->egl_داده) {
            أرجع SDL_مجموعه_Error("Cannot create an OPENGL window invalid egl_data");
        }

        offscreen_پنجره->egl_surface = SDL_EGL_CreateOffscreenSurface(_this, پنجره->w, پنجره->h);

        إذا (offscreen_پنجره->egl_surface == EGL_NO_SURFACE) {
            أرجع SDL_مجموعه_Error("Failed to created an offscreen surface (EGL display: %p)",
                                _this->egl_داده->egl_display);
        }
    } وإلا {
        offscreen_پنجره->egl_surface = EGL_NO_SURFACE;
    }
#پایان_اگر // SDL_VIDEO_OPENGL_EGL

    أرجع true;
}

فراغ OFFSCREEN_Destroy_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_پنجره_داده *offscreen_پنجره = پنجره->داخلی;

    إذا (offscreen_پنجره) {
#اگر_تعریف_شده SDL_VIDEO_OPENGL_EGL
        SDL_EGL_DestroySurface(_this, offscreen_پنجره->egl_surface);
#پایان_اگر
        SDL_free(offscreen_پنجره);
    }

    پنجره->داخلی = عدم;
}

فراغ OFFSCREEN_مجموعه_پنجره_اندازه(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_RESIZED, پنجره->pending.w, پنجره->pending.h);
}
#پایان_اگر // SDL_VIDEO_DRIVER_OFFSCREEN
