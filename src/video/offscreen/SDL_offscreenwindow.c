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

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_OFFSCREEN

#ضمن "../SDL_sysvideo.h"
#ضمن "../../events/SDL_windowevents_c.h"
#ضمن "../SDL_egl_c.h"

#ضمن "SDL_offscreenwindow.h"

bool OFFSCREEN_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props)
{
    SDL_کھڑکی_انکڑے *offscreen_کھڑکی = (SDL_کھڑکی_انکڑے *)SDL_calloc(1, حجم(SDL_کھڑکی_انکڑے));

    إذا (!offscreen_کھڑکی) {
        أرجع false;
    }

    کھڑکی->اندرونی = offscreen_کھڑکی;

    إذا (کھڑکی->x == SDL_WINDOWPOS_UNDEFINED) {
        کھڑکی->x = 0;
    }

    إذا (کھڑکی->y == SDL_WINDOWPOS_UNDEFINED) {
        کھڑکی->y = 0;
    }

    offscreen_کھڑکی->sdl_کھڑکی = کھڑکی;

#جے_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
    إذا (کھڑکی->flags & SDL_کھڑکی_OPENGL) {

        إذا (!_this->egl_انکڑے) {
            أرجع SDL_سیٹ_Error("Cannot create an OPENGL window invalid egl_data");
        }

        offscreen_کھڑکی->egl_surface = SDL_EGL_CreateOffscreenSurface(_this, کھڑکی->w, کھڑکی->h);

        إذا (offscreen_کھڑکی->egl_surface == EGL_NO_SURFACE) {
            أرجع SDL_سیٹ_Error("Failed to created an offscreen surface (EGL display: %p)",
                                _this->egl_انکڑے->egl_display);
        }
    } وإلا {
        offscreen_کھڑکی->egl_surface = EGL_NO_SURFACE;
    }
#جے_انت // SDL_VIDEO_OPENGL_EGL

    أرجع true;
}

فراغ OFFSCREEN_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے *offscreen_کھڑکی = کھڑکی->اندرونی;

    إذا (offscreen_کھڑکی) {
#جے_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
        SDL_EGL_DestroySurface(_this, offscreen_کھڑکی->egl_surface);
#جے_انت
        SDL_free(offscreen_کھڑکی);
    }

    کھڑکی->اندرونی = عدم;
}

فراغ OFFSCREEN_سیٹ_کھڑکی_ناپ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_RESIZED, کھڑکی->pending.w, کھڑکی->pending.h);
}
#جے_انت // SDL_VIDEO_DRIVER_OFFSCREEN
