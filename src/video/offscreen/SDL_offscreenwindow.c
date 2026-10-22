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
#شامل "SDL_internal.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_OFFSCREEN

#شامل "../SDL_sysvideo.h"
#شامل "../../events/SDL_windowevents_c.h"
#شامل "../SDL_egl_c.h"

#شامل "SDL_offscreenwindow.h"

bool OFFSCREEN_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props)
{
    SDL_کھڑکی_ڈیٹا *offscreen_کھڑکی = (SDL_کھڑکی_ڈیٹا *)SDL_calloc(1, حجم(SDL_کھڑکی_ڈیٹا));

    اگر (!offscreen_کھڑکی) {
        واپس false;
    }

    کھڑکی->اندرونی_2 = offscreen_کھڑکی;

    اگر (کھڑکی->x == SDL_WINDOWPOS_UNDEFINED) {
        کھڑکی->x = 0;
    }

    اگر (کھڑکی->y == SDL_WINDOWPOS_UNDEFINED) {
        کھڑکی->y = 0;
    }

    offscreen_کھڑکی->sdl_کھڑکی = کھڑکی;

#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
    اگر (کھڑکی->flags & SDL_کھڑکی_OPENGL) {

        اگر (!_this->egl_ڈیٹا) {
            واپس SDL_سیٹ_Error("Cannot create an OPENGL window invalid egl_data");
        }

        offscreen_کھڑکی->egl_surface = SDL_EGL_CreateOffscreenSurface(_this, کھڑکی->w, کھڑکی->h);

        اگر (offscreen_کھڑکی->egl_surface == EGL_NO_SURFACE) {
            واپس SDL_سیٹ_Error("Failed to created an offscreen surface (EGL display: %p)",
                                _this->egl_ڈیٹا->egl_display);
        }
    } ورنہ {
        offscreen_کھڑکی->egl_surface = EGL_NO_SURFACE;
    }
#اگر_ختم // SDL_VIDEO_OPENGL_EGL

    واپس true;
}

خالی OFFSCREEN_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *offscreen_کھڑکی = کھڑکی->اندرونی_2;

    اگر (offscreen_کھڑکی) {
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
        SDL_EGL_DestroySurface(_this, offscreen_کھڑکی->egl_surface);
#اگر_ختم
        SDL_free(offscreen_کھڑکی);
    }

    کھڑکی->اندرونی_2 = تہی;
}

خالی OFFSCREEN_سیٹ_کھڑکی_سائز(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_RESIZED, کھڑکی->pending.w, کھڑکی->pending.h);
}
#اگر_ختم // SDL_VIDEO_DRIVER_OFFSCREEN
