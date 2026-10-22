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
#অন্তর্ভাব "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_DUMMY

#অন্তর্ভাব "../SDL_sysvideo.h"
#অন্তর্ভাব "../../SDL_properties_c.h"
#অন্তর্ভাব "SDL_nullframebuffer_c.h"

#define DUMMY_SURFACE "SDL.internal.window.surface"


bool SDL_DUMMY_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, শূন্য **pixels, পূর্ণসংখ্যা *pitch)
{
    SDL_Surface *surface;
    ধ্রুবক SDL_PixelFormat surface_format = SDL_PIXELFORMAT_XRGB8888;
    পূর্ণসংখ্যা w, h;

    // Create a new framebuffer
    SDL_Get_Window_আকার_In_Pixels(window, &w, &h);
    surface = SDL_CreateSurfaceZeroed(w, h, surface_format);
    যদি (!surface) {
        ফেরত false;
    }

    // Save the info and return!
    SDL_SetSurfaceProperty(SDL_GetWindowProperties(window), DUMMY_SURFACE, surface);
    *format = surface_format;
    *pixels = surface->pixels;
    *pitch = surface->pitch;
    ফেরত true;
}

bool SDL_DUMMY_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, ধ্রুবক SDL_Rect *rects, পূর্ণসংখ্যা numrects)
{
    স্থির পূর্ণসংখ্যা frame_সংখ্যা;
    SDL_Surface *surface;

    surface = (SDL_Surface *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), DUMMY_SURFACE, ফাঁকা);
    যদি (!surface) {
        ফেরত SDL_SetError("Couldn't find dummy surface for window");
    }

    // Send the data to the display
    যদি (SDL_GetHintBoolean(SDL_HINT_VIDEO_DUMMY_SAVE_FRAMES, false)) {
        অক্ষর file[128];
        (শূন্য)SDL_snprintf(file, আকার(file), "SDL_window%" SDL_PRIu32 "-%8.8d.bmp",
                           SDL_GetWindowID(window), ++frame_সংখ্যা);
        SDL_SaveBMP(surface, file);
    }
    ফেরত true;
}

শূন্য SDL_DUMMY_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_ClearProperty(SDL_GetWindowProperties(window), DUMMY_SURFACE);
}

#endif // SDL_VIDEO_DRIVER_DUMMY
