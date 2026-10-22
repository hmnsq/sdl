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
#அந்தர்பாவ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_OFFSCREEN

#அந்தர்பாவ "../SDL_sysvideo.h"
#அந்தர்பாவ "../../events/SDL_windowevents_c.h"
#அந்தர்பாவ "../SDL_egl_c.h"

#அந்தர்பாவ "SDL_offscreenwindow.h"

bool OFFSCREEN_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_WindowData *offscreen_window = (SDL_WindowData *)SDL_calloc(1, அளவு(SDL_WindowData));

    எனில் (!offscreen_window) {
        திரும்பு false;
    }

    window->internal = offscreen_window;

    எனில் (window->x == SDL_WINDOWPOS_UNDEFINED) {
        window->x = 0;
    }

    எனில் (window->y == SDL_WINDOWPOS_UNDEFINED) {
        window->y = 0;
    }

    offscreen_window->sdl_window = window;

#ifdef SDL_VIDEO_OPENGL_EGL
    எனில் (window->flags & SDL_WINDOW_OPENGL) {

        எனில் (!_this->egl_data) {
            திரும்பு SDL_SetError("Cannot create an OPENGL window invalid egl_data");
        }

        offscreen_window->egl_surface = SDL_EGL_CreateOffscreenSurface(_this, window->w, window->h);

        எனில் (offscreen_window->egl_surface == EGL_NO_SURFACE) {
            திரும்பு SDL_SetError("Failed to created an offscreen surface (EGL display: %p)",
                                _this->egl_data->egl_display);
        }
    } இல்லையெனில் {
        offscreen_window->egl_surface = EGL_NO_SURFACE;
    }
#endif // SDL_VIDEO_OPENGL_EGL

    திரும்பு true;
}

வெறுமை OFFSCREEN_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *offscreen_window = window->internal;

    எனில் (offscreen_window) {
#ifdef SDL_VIDEO_OPENGL_EGL
        SDL_EGL_DestroySurface(_this, offscreen_window->egl_surface);
#endif
        SDL_free(offscreen_window);
    }

    window->internal = வெற்று;
}

வெறுமை OFFSCREEN_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, window->pending.w, window->pending.h);
}
#endif // SDL_VIDEO_DRIVER_OFFSCREEN
