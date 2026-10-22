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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_DUMMY

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "../../SDL_properties_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_nullframebuffer_c.h"

#define DUMMY_SURFACE "SDL.internal.window.surface"


bool SDL_DUMMY_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, ಶೂನ್ಯ **pixels, ಪೂರ್ಣಾಙ್ಕ *pitch)
{
    SDL_Surface *surface;
    ಧ್ರುವ SDL_PixelFormat surface_format = SDL_PIXELFORMAT_XRGB8888;
    ಪೂರ್ಣಾಙ್ಕ w, h;

    // Create a new framebuffer
    SDL_GetWindowSizeInPixels(window, &w, &h);
    surface = SDL_CreateSurfaceZeroed(w, h, surface_format);
    ಯದಿ (!surface) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    // Save the info and return!
    SDL_SetSurfaceProperty(SDL_GetWindowProperties(window), DUMMY_SURFACE, surface);
    *format = surface_format;
    *pixels = surface->pixels;
    *pitch = surface->pitch;
    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_DUMMY_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, ಧ್ರುವ SDL_Rect *rects, ಪೂರ್ಣಾಙ್ಕ numrects)
{
    ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ frame_ಸಂಖ್ಯೆ;
    SDL_Surface *surface;

    surface = (SDL_Surface *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), DUMMY_SURFACE, ರಿಕ್ತ);
    ಯದಿ (!surface) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Couldn't find dummy surface for window");
    }

    // Send the data to the display
    ಯದಿ (SDL_GetHintBoolean(SDL_HINT_VIDEO_DUMMY_SAVE_FRAMES, false)) {
        ವರ್ಣ file[128];
        (ಶೂನ್ಯ)SDL_snprintf(file, ಪರಿಮಾಣ(file), "SDL_window%" SDL_PRIu32 "-%8.8d.bmp",
                           SDL_GetWindowID(window), ++frame_ಸಂಖ್ಯೆ);
        SDL_SaveBMP(surface, file);
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

ಶೂನ್ಯ SDL_DUMMY_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_ClearProperty(SDL_GetWindowProperties(window), DUMMY_SURFACE);
}

#endif // SDL_VIDEO_DRIVER_DUMMY
