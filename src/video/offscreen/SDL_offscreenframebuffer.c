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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_OFFSCREEN

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "../../SDL_properties_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_offscreenframebuffer_c.h"

#ವ್ಯಾಖ್ಯಾನಿಸು OFFSCREEN_SURFACE "SDL.internal.window.surface"


bool SDL_OFFSCREEN_Create_ಕಿಟಕಿ_Framebuffer(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PixelFormat *format, ಶೂನ್ಯ **pixels, ಪೂರ್ಣಾಂಕ *pitch)
{
    SDL_Surface *surface;
    ಸ್ಥಿರಾಂಕ SDL_PixelFormat surface_format = SDL_PIXELFORMAT_XRGB8888;
    ಪೂರ್ಣಾಂಕ w, h;

    // Create a new framebuffer
    SDL_Get_ಕಿಟಕಿ_ಗಾತ್ರ_ಒಳ_Pixels(ಕಿಟಕಿ, &w, &h);
    surface = SDL_CreateSurfaceZeroed(w, h, surface_format);
    ಆದರೆ (!surface) {
        ಹಿಂತಿರುಗಿ false;
    }

    // Save the info and return!
    SDL_ಗಣ_Surface_Property(SDL_Get_ಕಿಟಕಿ_Properties(ಕಿಟಕಿ), OFFSCREEN_SURFACE, surface);
    *format = surface_format;
    *pixels = surface->pixels;
    *pitch = surface->pitch;

    ಹಿಂತಿರುಗಿ true;
}

bool SDL_OFFSCREEN_Update_ಕಿಟಕಿ_Framebuffer(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಸ್ಥಿರಾಂಕ SDL_Rect *rects, ಪೂರ್ಣಾಂಕ numrects)
{
    ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ ಚೌಕಟ್ಟು_ಸಂಖ್ಯೆ;
    SDL_Surface *surface;

    surface = (SDL_Surface *)SDL_Get_ಸೂಚಕ_Property(SDL_Get_ಕಿಟಕಿ_Properties(ಕಿಟಕಿ), OFFSCREEN_SURFACE, ಖಾಲಿ);
    ಆದರೆ (!surface) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Couldn't find offscreen surface for window");
    }

    // Send the data to the display
    ಆದರೆ (SDL_GetHintBoolean(SDL_HINT_VIDEO_OFFSCREEN_SAVE_ಚೌಕಟ್ಟುಗಳು, false)) {
        ಅಕ್ಷರ file[128];
        (ಶೂನ್ಯ)SDL_snprintf(file, ಗಾತ್ರ(file), "SDL_window%" SDL_PRIu32 "-%8.8d.bmp",
                           SDL_Get_ಕಿಟಕಿ_ID(ಕಿಟಕಿ), ++ಚೌಕಟ್ಟು_ಸಂಖ್ಯೆ);
        SDL_SaveBMP(surface, file);
    }
    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ SDL_OFFSCREEN_Destroy_ಕಿಟಕಿ_Framebuffer(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ClearProperty(SDL_Get_ಕಿಟಕಿ_Properties(ಕಿಟಕಿ), OFFSCREEN_SURFACE);
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_OFFSCREEN
