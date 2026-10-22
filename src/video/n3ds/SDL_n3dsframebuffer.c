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
#অন্তর্ভাৱ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_N3DS

#অন্তর্ভাৱ "../SDL_sysvideo.h"
#অন্তর্ভাৱ "../../SDL_properties_c.h"
#অন্তর্ভাৱ "SDL_n3dsframebuffer_c.h"
#অন্তর্ভাৱ "SDL_n3dsvideo.h"

#define N3DS_SURFACE "SDL.internal.window.surface"

প্রকারনির্দেশ সংরচনা
{
    পূর্ণাঙ্ক width, height;
} Dimensions;

স্থির শূন্য CopyFramebuffertoN3DS_16(u16 *dest, ধ্রুৱ Dimensions dest_dim, ধ্রুৱ u16 *source, ধ্রুৱ Dimensions source_dim);
স্থির শূন্য CopyFramebuffertoN3DS_24(u8  *dest, ধ্রুৱ Dimensions dest_dim, ধ্রুৱ u8  *source, ধ্রুৱ Dimensions source_dim);
স্থির শূন্য CopyFramebuffertoN3DS_32(u32 *dest, ধ্রুৱ Dimensions dest_dim, ধ্রুৱ u32 *source, ধ্রুৱ Dimensions source_dim);
স্থির পূর্ণাঙ্ক GetDestOffset(পূর্ণাঙ্ক x, পূর্ণাঙ্ক y, পূর্ণাঙ্ক dest_width);
স্থির পূর্ণাঙ্ক GetSourceOffset(পূর্ণাঙ্ক x, পূর্ণাঙ্ক y, পূর্ণাঙ্ক source_width);
স্থির শূন্য FlushN3DSBuffer(ধ্রুৱ শূন্য *buffer, u32 bufsize, gfxScreen_t screen);


bool SDL_N3DS_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, শূন্য **pixels, পূর্ণাঙ্ক *pitch)
{
    SDL_Surface *framebuffer;
    ধ্রুৱ SDL_DisplayMode *mode;
    পূর্ণাঙ্ক w, h;

    SDL_N3DS_DestroyWindowFramebuffer(_this, window);

    mode = SDL_GetCurrentDisplayMode(SDL_GetDisplayForWindow(window));
    SDL_GetWindowSizeInPixels(window, &w, &h);
    framebuffer = SDL_CreateSurfaceZeroed(w, h, mode->format);

    যদি (!framebuffer) {
        ঘূৰাই false;
    }

    SDL_SetSurfaceProperty(SDL_GetWindowProperties(window), N3DS_SURFACE, framebuffer);
    *format = mode->format;
    *pixels = framebuffer->pixels;
    *pitch = framebuffer->pitch;
    ঘূৰাই true;
}

bool SDL_N3DS_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, ধ্রুৱ SDL_Rect *rects, পূর্ণাঙ্ক numrects)
{
    SDL_WindowData *drv_data = window->internal;
    SDL_Surface *surface;
    u16 width, height;
    শূন্য *framebuffer;
    u32 bufsize;

    surface = (SDL_Surface *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), N3DS_SURFACE, রিক্ত);
    যদি (!surface) {
        ঘূৰাই SDL_SetError("%s: Unable to get the window surface.", SDL_FUNCTION);
    }

    // Get the N3DS internal framebuffer and its size
    framebuffer = gfxGetFramebuffer(drv_data->screen, GFX_বাম, &width, &height);
    bufsize = width * height * 4;

    যদি (SDL_BYTESPERPIXEL(surface->format) == 2)
        CopyFramebuffertoN3DS_16(framebuffer, (Dimensions){ width, height },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    অন্যথা যদি (SDL_BYTESPERPIXEL(surface->format) == 3)
        CopyFramebuffertoN3DS_24(framebuffer, (Dimensions){ width, height },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    অন্যথা
        CopyFramebuffertoN3DS_32(framebuffer, (Dimensions){ width, height },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    FlushN3DSBuffer(framebuffer, bufsize, drv_data->screen);

    ঘূৰাই true;
}

স্থির শূন্য CopyFramebuffertoN3DS_16(u16 *dest, ধ্রুৱ Dimensions dest_dim, ধ্রুৱ u16 *source, ধ্রুৱ Dimensions source_dim)
{
    পূর্ণাঙ্ক rows = SDL_min(dest_dim.width, source_dim.height);
    পূর্ণাঙ্ক cols = SDL_min(dest_dim.height, source_dim.width);
    বাবে (পূর্ণাঙ্ক y = 0; y < rows; ++y) {
        বাবে (পূর্ণাঙ্ক x = 0; x < cols; ++x) {
            ধ্রুৱ u16 *s = source + GetSourceOffset(x, y, source_dim.width);
            u16 *d = dest + GetDestOffset(x, y, dest_dim.width);
            *d = *s;
        }
    }
}

স্থির শূন্য CopyFramebuffertoN3DS_24(u8 *dest, ধ্রুৱ Dimensions dest_dim, ধ্রুৱ u8 *source, ধ্রুৱ Dimensions source_dim)
{
    পূর্ণাঙ্ক rows = SDL_min(dest_dim.width, source_dim.height);
    পূর্ণাঙ্ক cols = SDL_min(dest_dim.height, source_dim.width);
    বাবে (পূর্ণাঙ্ক y = 0; y < rows; ++y) {
        বাবে (পূর্ণাঙ্ক x = 0; x < cols; ++x) {
            ধ্রুৱ u8 *s = source + GetSourceOffset(x, y, source_dim.width) * 3;
            u8 *d = dest + GetDestOffset(x, y, dest_dim.width) * 3;
            d[0] = s[0];
            d[1] = s[1];
            d[2] = s[2];
        }
    }
}

স্থির শূন্য CopyFramebuffertoN3DS_32(u32 *dest, ধ্রুৱ Dimensions dest_dim, ধ্রুৱ u32 *source, ধ্রুৱ Dimensions source_dim)
{
    পূর্ণাঙ্ক rows = SDL_min(dest_dim.width, source_dim.height);
    পূর্ণাঙ্ক cols = SDL_min(dest_dim.height, source_dim.width);
    বাবে (পূর্ণাঙ্ক y = 0; y < rows; ++y) {
        বাবে (পূর্ণাঙ্ক x = 0; x < cols; ++x) {
            ধ্রুৱ u32 *s = source + GetSourceOffset(x, y, source_dim.width);
            u32 *d = dest + GetDestOffset(x, y, dest_dim.width);
            *d = *s;
        }
    }
}

স্থির পূর্ণাঙ্ক GetDestOffset(পূর্ণাঙ্ক x, পূর্ণাঙ্ক y, পূর্ণাঙ্ক dest_width)
{
    ঘূৰাই dest_width - y - 1 + dest_width * x;
}

স্থির পূর্ণাঙ্ক GetSourceOffset(পূর্ণাঙ্ক x, পূর্ণাঙ্ক y, পূর্ণাঙ্ক source_width)
{
    ঘূৰাই x + y * source_width;
}

স্থির শূন্য FlushN3DSBuffer(ধ্রুৱ শূন্য *buffer, u32 bufsize, gfxScreen_t screen)
{
    GSPGPU_FlushDataCache(buffer, bufsize);
    gfxScreenSwapBuffers(screen, false);
}

শূন্য SDL_N3DS_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_ClearProperty(SDL_GetWindowProperties(window), N3DS_SURFACE);
}

#endif // SDL_VIDEO_DRIVER_N3DS
