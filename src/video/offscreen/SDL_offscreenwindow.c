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
#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_OFFSCREEN

#समावेश "../SDL_sysvideo.h"
#समावेश "../../events/SDL_windowevents_c.h"
#समावेश "../SDL_egl_c.h"

#समावेश "SDL_offscreenwindow.h"

bool OFFSCREEN_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_Window_तथ्य *offscreen_window = (SDL_Window_तथ्य *)SDL_calloc(1, माप(SDL_Window_तथ्य));

    अगर (!offscreen_window) {
        वापस false;
    }

    window->internal = offscreen_window;

    अगर (window->x == SDL_WINDOWPOS_UNDEFINED) {
        window->x = 0;
    }

    अगर (window->y == SDL_WINDOWPOS_UNDEFINED) {
        window->y = 0;
    }

    offscreen_window->sdl_window = window;

#अगर_घोषित SDL_VIDEO_OPENGL_EGL
    अगर (window->flags & SDL_WINDOW_OPENGL) {

        अगर (!_this->egl_तथ्य) {
            वापस SDL_SetError("Cannot create an OPENGL window invalid egl_data");
        }

        offscreen_window->egl_surface = SDL_EGL_CreateOffscreenSurface(_this, window->w, window->h);

        अगर (offscreen_window->egl_surface == EGL_NO_SURFACE) {
            वापस SDL_SetError("Failed to created an offscreen surface (EGL display: %p)",
                                _this->egl_तथ्य->egl_display);
        }
    } अन्यथा {
        offscreen_window->egl_surface = EGL_NO_SURFACE;
    }
#पूर्ण_अगर // SDL_VIDEO_OPENGL_EGL

    वापस true;
}

व्योम OFFSCREEN_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_तथ्य *offscreen_window = window->internal;

    अगर (offscreen_window) {
#अगर_घोषित SDL_VIDEO_OPENGL_EGL
        SDL_EGL_DestroySurface(_this, offscreen_window->egl_surface);
#पूर्ण_अगर
        SDL_free(offscreen_window);
    }

    window->internal = शून्य;
}

व्योम OFFSCREEN_Set_Window_आकार(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, window->pending.w, window->pending.h);
}
#पूर्ण_अगर // SDL_VIDEO_DRIVER_OFFSCREEN
