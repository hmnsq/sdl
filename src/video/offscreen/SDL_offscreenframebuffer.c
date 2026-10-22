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

#ifdef SDL_VIDEO_DRIVER_OFFSCREEN

#ضمن "../SDL_sysvideo.h"
#ضمن "../../SDL_properties_c.h"
#ضمن "SDL_offscreenframebuffer_c.h"

#define OFFSCREEN_SURFACE "SDL.internal.window.surface"


bool SDL_OFFSCREEN_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, فراغ **pixels, صحيح *pitch)
{
    SDL_Surface *surface;
    ثابت SDL_PixelFormat surface_format = SDL_PIXELFORMAT_XRGB8888;
    صحيح w, h;

    // Create a new framebuffer
    SDL_GetWindowSizeInPixels(window, &w, &h);
    surface = SDL_CreateSurfaceZeroed(w, h, surface_format);
    إذا (!surface) {
        أرجع false;
    }

    // Save the info and return!
    SDL_SetSurfaceProperty(SDL_GetWindowProperties(window), OFFSCREEN_SURFACE, surface);
    *format = surface_format;
    *pixels = surface->pixels;
    *pitch = surface->pitch;

    أرجع true;
}

bool SDL_OFFSCREEN_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, ثابت SDL_Rect *rects, صحيح numrects)
{
    ساكن صحيح frame_رقم;
    SDL_Surface *surface;

    surface = (SDL_Surface *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), OFFSCREEN_SURFACE, عدم);
    إذا (!surface) {
        أرجع SDL_SetError("Couldn't find offscreen surface for window");
    }

    // Send the data to the display
    إذا (SDL_GetHintBoolean(SDL_HINT_VIDEO_OFFSCREEN_SAVE_FRAMES, false)) {
        حرف file[128];
        (فراغ)SDL_snprintf(file, حجم(file), "SDL_window%" SDL_PRIu32 "-%8.8d.bmp",
                           SDL_GetWindowID(window), ++frame_رقم);
        SDL_SaveBMP(surface, file);
    }
    أرجع true;
}

فراغ SDL_OFFSCREEN_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_ClearProperty(SDL_GetWindowProperties(window), OFFSCREEN_SURFACE);
}

#endif // SDL_VIDEO_DRIVER_OFFSCREEN
