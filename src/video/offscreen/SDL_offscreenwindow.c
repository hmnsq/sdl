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

#ifdef SDL_VIDEO_DRIVER_OFFSCREEN

#شامل "../SDL_sysvideo.h"
#شامل "../../events/SDL_windowevents_c.h"
#شامل "../SDL_egl_c.h"

#شامل "SDL_offscreenwindow.h"

bool OFFSCREEN_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_WindowData *offscreen_window = (SDL_WindowData *)SDL_calloc(1, اندازه(SDL_WindowData));

    اگر (!offscreen_window) {
        بازگشت false;
    }

    window->internal = offscreen_window;

    اگر (window->x == SDL_WINDOWPOS_UNDEFINED) {
        window->x = 0;
    }

    اگر (window->y == SDL_WINDOWPOS_UNDEFINED) {
        window->y = 0;
    }

    offscreen_window->sdl_window = window;

#ifdef SDL_VIDEO_OPENGL_EGL
    اگر (window->flags & SDL_WINDOW_OPENGL) {

        اگر (!_this->egl_data) {
            بازگشت SDL_SetError("Cannot create an OPENGL window invalid egl_data");
        }

        offscreen_window->egl_surface = SDL_EGL_CreateOffscreenSurface(_this, window->w, window->h);

        اگر (offscreen_window->egl_surface == EGL_NO_SURFACE) {
            بازگشت SDL_SetError("Failed to created an offscreen surface (EGL display: %p)",
                                _this->egl_data->egl_display);
        }
    } وگرنه {
        offscreen_window->egl_surface = EGL_NO_SURFACE;
    }
#endif // SDL_VIDEO_OPENGL_EGL

    بازگشت true;
}

تهی OFFSCREEN_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *offscreen_window = window->internal;

    اگر (offscreen_window) {
#ifdef SDL_VIDEO_OPENGL_EGL
        SDL_EGL_DestroySurface(_this, offscreen_window->egl_surface);
#endif
        SDL_free(offscreen_window);
    }

    window->internal = پوچ;
}

تهی OFFSCREEN_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, window->pending.w, window->pending.h);
}
#endif // SDL_VIDEO_DRIVER_OFFSCREEN
