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

#ifdef SDL_VIDEO_DRIVER_DUMMY

#شامل "../SDL_sysvideo.h"
#شامل "../../SDL_properties_c.h"
#شامل "SDL_nullframebuffer_c.h"

#define DUMMY_SURFACE "SDL.internal.window.surface"


bool SDL_DUMMY_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, تهی **pixels, صحیح *pitch)
{
    SDL_Surface *surface;
    ثابت SDL_PixelFormat surface_format = SDL_PIXELFORMAT_XRGB8888;
    صحیح w, h;

    // Create a new framebuffer
    SDL_GetWindowSizeInPixels(window, &w, &h);
    surface = SDL_CreateSurfaceZeroed(w, h, surface_format);
    اگر (!surface) {
        بازگشت false;
    }

    // Save the info and return!
    SDL_SetSurfaceProperty(SDL_GetWindowProperties(window), DUMMY_SURFACE, surface);
    *format = surface_format;
    *pixels = surface->pixels;
    *pitch = surface->pitch;
    بازگشت true;
}

bool SDL_DUMMY_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, ثابت SDL_Rect *rects, صحیح numrects)
{
    ایستا صحیح frame_عدد;
    SDL_Surface *surface;

    surface = (SDL_Surface *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), DUMMY_SURFACE, پوچ);
    اگر (!surface) {
        بازگشت SDL_SetError("Couldn't find dummy surface for window");
    }

    // Send the data to the display
    اگر (SDL_GetHintBoolean(SDL_HINT_VIDEO_DUMMY_SAVE_FRAMES, false)) {
        نویسه file[128];
        (تهی)SDL_snprintf(file, اندازه(file), "SDL_window%" SDL_PRIu32 "-%8.8d.bmp",
                           SDL_GetWindowID(window), ++frame_عدد);
        SDL_SaveBMP(surface, file);
    }
    بازگشت true;
}

تهی SDL_DUMMY_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_ClearProperty(SDL_GetWindowProperties(window), DUMMY_SURFACE);
}

#endif // SDL_VIDEO_DRIVER_DUMMY
