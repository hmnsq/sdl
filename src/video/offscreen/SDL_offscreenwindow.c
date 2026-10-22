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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_OFFSCREEN

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_windowevents_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_egl_c.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_offscreenwindow.h"

bool OFFSCREEN_Create_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID create_props)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *offscreen_ਖਿੜਕੀ = (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ));

    ਜੇ (!offscreen_ਖਿੜਕੀ) {
        ਵਾਪਸ false;
    }

    ਖਿੜਕੀ->ਅੰਦਰੂਨੀ = offscreen_ਖਿੜਕੀ;

    ਜੇ (ਖਿੜਕੀ->x == SDL_WINDOWPOS_UNDEFINED) {
        ਖਿੜਕੀ->x = 0;
    }

    ਜੇ (ਖਿੜਕੀ->y == SDL_WINDOWPOS_UNDEFINED) {
        ਖਿੜਕੀ->y = 0;
    }

    offscreen_ਖਿੜਕੀ->sdl_ਖਿੜਕੀ = ਖਿੜਕੀ;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_EGL
    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_OPENGL) {

        ਜੇ (!_this->egl_ਅੰਕੜੇ) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("Cannot create an OPENGL window invalid egl_data");
        }

        offscreen_ਖਿੜਕੀ->egl_surface = SDL_EGL_CreateOffscreenSurface(_this, ਖਿੜਕੀ->w, ਖਿੜਕੀ->h);

        ਜੇ (offscreen_ਖਿੜਕੀ->egl_surface == EGL_NO_SURFACE) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("Failed to created an offscreen surface (EGL display: %p)",
                                _this->egl_ਅੰਕੜੇ->egl_display);
        }
    } ਨਹੀਂਤਾਂ {
        offscreen_ਖਿੜਕੀ->egl_surface = EGL_NO_SURFACE;
    }
#ਜੇ_ਅੰਤ // SDL_VIDEO_OPENGL_EGL

    ਵਾਪਸ true;
}

ਖਾਲੀ OFFSCREEN_Destroy_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *offscreen_ਖਿੜਕੀ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    ਜੇ (offscreen_ਖਿੜਕੀ) {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_EGL
        SDL_EGL_DestroySurface(_this, offscreen_ਖਿੜਕੀ->egl_surface);
#ਜੇ_ਅੰਤ
        SDL_free(offscreen_ਖਿੜਕੀ);
    }

    ਖਿੜਕੀ->ਅੰਦਰੂਨੀ = ਨਿਰਾ;
}

ਖਾਲੀ OFFSCREEN_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_RESIZED, ਖਿੜਕੀ->pending.w, ਖਿੜਕੀ->pending.h);
}
#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_OFFSCREEN
