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

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_OFFSCREEN

#ضمن "../SDL_sysvideo.h"
#ضمن "../../SDL_properties_c.h"
#ضمن "SDL_offscreenframebuffer_c.h"

#تعریف_کرو OFFSCREEN_SURFACE "SDL.internal.window.surface"


bool SDL_OFFSCREEN_Create_کھڑکی_Framebuffer(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PixelFormat *format, فراغ **pixels, صحيح *pitch)
{
    SDL_Surface *surface;
    ثابت SDL_PixelFormat surface_format = SDL_PIXELFORMAT_XRGB8888;
    صحيح w, h;

    // Create a new framebuffer
    SDL_Get_کھڑکی_ناپ_وچ_Pixels(کھڑکی, &w, &h);
    surface = SDL_CreateSurfaceZeroed(w, h, surface_format);
    إذا (!surface) {
        أرجع false;
    }

    // Save the info and return!
    SDL_سیٹ_Surface_Property(SDL_Get_کھڑکی_Properties(کھڑکی), OFFSCREEN_SURFACE, surface);
    *format = surface_format;
    *pixels = surface->pixels;
    *pitch = surface->pitch;

    أرجع true;
}

bool SDL_OFFSCREEN_Update_کھڑکی_Framebuffer(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, ثابت SDL_Rect *rects, صحيح numrects)
{
    ساكن صحيح چوکھٹا_نمبر;
    SDL_Surface *surface;

    surface = (SDL_Surface *)SDL_Get_اشارہ_گر_Property(SDL_Get_کھڑکی_Properties(کھڑکی), OFFSCREEN_SURFACE, عدم);
    إذا (!surface) {
        أرجع SDL_سیٹ_Error("Couldn't find offscreen surface for window");
    }

    // Send the data to the display
    إذا (SDL_GetHintBoolean(SDL_HINT_VIDEO_OFFSCREEN_SAVE_چوکھٹے, false)) {
        حرف file[128];
        (فراغ)SDL_snprintf(file, حجم(file), "SDL_window%" SDL_PRIu32 "-%8.8d.bmp",
                           SDL_Get_کھڑکی_ID(کھڑکی), ++چوکھٹا_نمبر);
        SDL_SaveBMP(surface, file);
    }
    أرجع true;
}

فراغ SDL_OFFSCREEN_Destroy_کھڑکی_Framebuffer(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_ClearProperty(SDL_Get_کھڑکی_Properties(کھڑکی), OFFSCREEN_SURFACE);
}

#جے_انت // SDL_VIDEO_DRIVER_OFFSCREEN
