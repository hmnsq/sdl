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

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_DUMMY

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../SDL_properties_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_nullframebuffer_c.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DUMMY_SURFACE "SDL.internal.window.surface"


bool SDL_DUMMY_Create_ਖਿੜਕੀ_Framebuffer(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PixelFormat *format, ਖਾਲੀ **pixels, ਪੂਰਨ *pitch)
{
    SDL_Surface *surface;
    ਅਚਲ SDL_PixelFormat surface_format = SDL_PIXELFORMAT_XRGB8888;
    ਪੂਰਨ w, h;

    // Create a new framebuffer
    SDL_Get_ਖਿੜਕੀ_ਮਾਪ_ਵਿੱਚ_Pixels(ਖਿੜਕੀ, &w, &h);
    surface = SDL_CreateSurfaceZeroed(w, h, surface_format);
    ਜੇ (!surface) {
        ਵਾਪਸ false;
    }

    // Save the info and return!
    SDL_ਸੈੱਟ_Surface_Property(SDL_Get_ਖਿੜਕੀ_Properties(ਖਿੜਕੀ), DUMMY_SURFACE, surface);
    *format = surface_format;
    *pixels = surface->pixels;
    *pitch = surface->pitch;
    ਵਾਪਸ true;
}

bool SDL_DUMMY_Update_ਖਿੜਕੀ_Framebuffer(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਅਚਲ SDL_Rect *rects, ਪੂਰਨ numrects)
{
    ਸਥਿਰ ਪੂਰਨ ਚੌਖਟਾ_ਸੰਖਿਆ;
    SDL_Surface *surface;

    surface = (SDL_Surface *)SDL_Get_ਸੂਚਕ_Property(SDL_Get_ਖਿੜਕੀ_Properties(ਖਿੜਕੀ), DUMMY_SURFACE, ਨਿਰਾ);
    ਜੇ (!surface) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Couldn't find dummy surface for window");
    }

    // Send the data to the display
    ਜੇ (SDL_GetHintBoolean(SDL_HINT_VIDEO_DUMMY_SAVE_ਚੌਖਟੇ, false)) {
        ਅੱਖਰ file[128];
        (ਖਾਲੀ)SDL_snprintf(file, ਆਕਾਰ(file), "SDL_window%" SDL_PRIu32 "-%8.8d.bmp",
                           SDL_Get_ਖਿੜਕੀ_ID(ਖਿੜਕੀ), ++ਚੌਖਟਾ_ਸੰਖਿਆ);
        SDL_SaveBMP(surface, file);
    }
    ਵਾਪਸ true;
}

ਖਾਲੀ SDL_DUMMY_Destroy_ਖਿੜਕੀ_Framebuffer(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ClearProperty(SDL_Get_ਖਿੜਕੀ_Properties(ਖਿੜਕੀ), DUMMY_SURFACE);
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_DUMMY
