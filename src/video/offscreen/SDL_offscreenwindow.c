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
#अन्तर्भाव "SDL_internal.h"

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_OFFSCREEN

#अन्तर्भाव "../SDL_sysvideo.h"
#अन्तर्भाव "../../events/SDL_windowevents_c.h"
#अन्तर्भाव "../SDL_egl_c.h"

#अन्तर्भाव "SDL_offscreenwindow.h"

bool OFFSCREEN_Create_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PropertiesID create_props)
{
    SDL_गवाक्षः_दत्त *offscreen_गवाक्षः = (SDL_गवाक्षः_दत्त *)SDL_calloc(1, परिमाण(SDL_गवाक्षः_दत्त));

    यदि (!offscreen_गवाक्षः) {
        प्रत्यागम false;
    }

    गवाक्षः->आन्तरिकम् = offscreen_गवाक्षः;

    यदि (गवाक्षः->x == SDL_WINDOWPOS_UNDEFINED) {
        गवाक्षः->x = 0;
    }

    यदि (गवाक्षः->y == SDL_WINDOWPOS_UNDEFINED) {
        गवाक्षः->y = 0;
    }

    offscreen_गवाक्षः->sdl_गवाक्षः = गवाक्षः;

#यदि_परिभाषितम् SDL_VIDEO_OPENGL_EGL
    यदि (गवाक्षः->flags & SDL_गवाक्षः_OPENGL) {

        यदि (!_this->egl_दत्त) {
            प्रत्यागम SDL_समुच्चयः_Error("Cannot create an OPENGL window invalid egl_data");
        }

        offscreen_गवाक्षः->egl_surface = SDL_EGL_CreateOffscreenSurface(_this, गवाक्षः->w, गवाक्षः->h);

        यदि (offscreen_गवाक्षः->egl_surface == EGL_NO_SURFACE) {
            प्रत्यागम SDL_समुच्चयः_Error("Failed to created an offscreen surface (EGL display: %p)",
                                _this->egl_दत्त->egl_display);
        }
    } अन्यथा {
        offscreen_गवाक्षः->egl_surface = EGL_NO_SURFACE;
    }
#यदि_अन्तः // SDL_VIDEO_OPENGL_EGL

    प्रत्यागम true;
}

शून्य OFFSCREEN_Destroy_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *offscreen_गवाक्षः = गवाक्षः->आन्तरिकम्;

    यदि (offscreen_गवाक्षः) {
#यदि_परिभाषितम् SDL_VIDEO_OPENGL_EGL
        SDL_EGL_DestroySurface(_this, offscreen_गवाक्षः->egl_surface);
#यदि_अन्तः
        SDL_free(offscreen_गवाक्षः);
    }

    गवाक्षः->आन्तरिकम् = रिक्त;
}

शून्य OFFSCREEN_समुच्चयः_गवाक्षः_आकार(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_RESIZED, गवाक्षः->pending.w, गवाक्षः->pending.h);
}
#यदि_अन्तः // SDL_VIDEO_DRIVER_OFFSCREEN
