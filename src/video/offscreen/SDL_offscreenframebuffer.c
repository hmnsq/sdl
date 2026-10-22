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
#അന്തര്ഭാവ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_OFFSCREEN

#അന്തര്ഭാവ "../SDL_sysvideo.h"
#അന്തര്ഭാവ "../../SDL_properties_c.h"
#അന്തര്ഭാവ "SDL_offscreenframebuffer_c.h"

#define OFFSCREEN_SURFACE "SDL.internal.window.surface"


bool SDL_OFFSCREEN_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, ശൂന്യം **pixels, പൂർണ്ണസംഖ്യ *pitch)
{
    SDL_Surface *surface;
    സ്ഥിരം SDL_PixelFormat surface_format = SDL_PIXELFORMAT_XRGB8888;
    പൂർണ്ണസംഖ്യ w, h;

    // Create a new framebuffer
    SDL_GetWindowSizeInPixels(window, &w, &h);
    surface = SDL_CreateSurfaceZeroed(w, h, surface_format);
    എങ്കിൽ (!surface) {
        തിരികെ false;
    }

    // Save the info and return!
    SDL_SetSurfaceProperty(SDL_GetWindowProperties(window), OFFSCREEN_SURFACE, surface);
    *format = surface_format;
    *pixels = surface->pixels;
    *pitch = surface->pitch;

    തിരികെ true;
}

bool SDL_OFFSCREEN_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, സ്ഥിരം SDL_Rect *rects, പൂർണ്ണസംഖ്യ numrects)
{
    സ്ഥിതം പൂർണ്ണസംഖ്യ frame_സംഖ്യ;
    SDL_Surface *surface;

    surface = (SDL_Surface *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), OFFSCREEN_SURFACE, ശൂന്യ);
    എങ്കിൽ (!surface) {
        തിരികെ SDL_SetError("Couldn't find offscreen surface for window");
    }

    // Send the data to the display
    എങ്കിൽ (SDL_GetHintBoolean(SDL_HINT_VIDEO_OFFSCREEN_SAVE_FRAMES, false)) {
        അക്ഷരം file[128];
        (ശൂന്യം)SDL_snprintf(file, വലുപ്പം(file), "SDL_window%" SDL_PRIu32 "-%8.8d.bmp",
                           SDL_GetWindowID(window), ++frame_സംഖ്യ);
        SDL_SaveBMP(surface, file);
    }
    തിരികെ true;
}

ശൂന്യം SDL_OFFSCREEN_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_ClearProperty(SDL_GetWindowProperties(window), OFFSCREEN_SURFACE);
}

#endif // SDL_VIDEO_DRIVER_OFFSCREEN
