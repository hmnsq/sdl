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

#ifdef SDL_VIDEO_DRIVER_N3DS

#অন্তর্ভাব "../SDL_sysvideo.h"
#অন্তর্ভাব "../../SDL_properties_c.h"
#অন্তর্ভাব "SDL_n3dsframebuffer_c.h"
#অন্তর্ভাব "SDL_n3dsvideo.h"

#define N3DS_SURFACE "SDL.internal.window.surface"

প্রকারলেখ কাঠামো
{
    পূর্ণসংখ্যা width, height;
} Dimensions;

স্থির শূন্য CopyFramebuffertoN3DS_16(u16 *dest, ধ্রুবক Dimensions dest_dim, ধ্রুবক u16 *source, ধ্রুবক Dimensions source_dim);
স্থির শূন্য CopyFramebuffertoN3DS_24(u8  *dest, ধ্রুবক Dimensions dest_dim, ধ্রুবক u8  *source, ধ্রুবক Dimensions source_dim);
স্থির শূন্য CopyFramebuffertoN3DS_32(u32 *dest, ধ্রুবক Dimensions dest_dim, ধ্রুবক u32 *source, ধ্রুবক Dimensions source_dim);
স্থির পূর্ণসংখ্যা GetDestOffset(পূর্ণসংখ্যা x, পূর্ণসংখ্যা y, পূর্ণসংখ্যা dest_width);
স্থির পূর্ণসংখ্যা GetSourceOffset(পূর্ণসংখ্যা x, পূর্ণসংখ্যা y, পূর্ণসংখ্যা source_width);
স্থির শূন্য FlushN3DSBuffer(ধ্রুবক শূন্য *বাফার_2, u32 bufsize, gfxScreen_t screen);


bool SDL_N3DS_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, শূন্য **pixels, পূর্ণসংখ্যা *pitch)
{
    SDL_Surface *framebuffer;
    ধ্রুবক SDL_DisplayMode *mode;
    পূর্ণসংখ্যা w, h;

    SDL_N3DS_DestroyWindowFramebuffer(_this, window);

    mode = SDL_GetCurrentDisplayMode(SDL_GetDisplayForWindow(window));
    SDL_Get_Window_আকার_In_Pixels(window, &w, &h);
    framebuffer = SDL_CreateSurfaceZeroed(w, h, mode->format);

    যদি (!framebuffer) {
        ফেরত false;
    }

    SDL_SetSurfaceProperty(SDL_GetWindowProperties(window), N3DS_SURFACE, framebuffer);
    *format = mode->format;
    *pixels = framebuffer->pixels;
    *pitch = framebuffer->pitch;
    ফেরত true;
}

bool SDL_N3DS_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, ধ্রুবক SDL_Rect *rects, পূর্ণসংখ্যা numrects)
{
    SDL_Window_তথ্য *drv_তথ্য = window->internal;
    SDL_Surface *surface;
    u16 width, height;
    শূন্য *framebuffer;
    u32 bufsize;

    surface = (SDL_Surface *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), N3DS_SURFACE, ফাঁকা);
    যদি (!surface) {
        ফেরত SDL_SetError("%s: Unable to get the window surface.", SDL_FUNCTION);
    }

    // Get the N3DS internal framebuffer and its size
    framebuffer = gfxGetFramebuffer(drv_তথ্য->screen, GFX_বাম, &width, &height);
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
    FlushN3DSBuffer(framebuffer, bufsize, drv_তথ্য->screen);

    ফেরত true;
}

স্থির শূন্য CopyFramebuffertoN3DS_16(u16 *dest, ধ্রুবক Dimensions dest_dim, ধ্রুবক u16 *source, ধ্রুবক Dimensions source_dim)
{
    পূর্ণসংখ্যা rows = SDL_min(dest_dim.width, source_dim.height);
    পূর্ণসংখ্যা cols = SDL_min(dest_dim.height, source_dim.width);
    জন্য (পূর্ণসংখ্যা y = 0; y < rows; ++y) {
        জন্য (পূর্ণসংখ্যা x = 0; x < cols; ++x) {
            ধ্রুবক u16 *s = source + GetSourceOffset(x, y, source_dim.width);
            u16 *d = dest + GetDestOffset(x, y, dest_dim.width);
            *d = *s;
        }
    }
}

স্থির শূন্য CopyFramebuffertoN3DS_24(u8 *dest, ধ্রুবক Dimensions dest_dim, ধ্রুবক u8 *source, ধ্রুবক Dimensions source_dim)
{
    পূর্ণসংখ্যা rows = SDL_min(dest_dim.width, source_dim.height);
    পূর্ণসংখ্যা cols = SDL_min(dest_dim.height, source_dim.width);
    জন্য (পূর্ণসংখ্যা y = 0; y < rows; ++y) {
        জন্য (পূর্ণসংখ্যা x = 0; x < cols; ++x) {
            ধ্রুবক u8 *s = source + GetSourceOffset(x, y, source_dim.width) * 3;
            u8 *d = dest + GetDestOffset(x, y, dest_dim.width) * 3;
            d[0] = s[0];
            d[1] = s[1];
            d[2] = s[2];
        }
    }
}

স্থির শূন্য CopyFramebuffertoN3DS_32(u32 *dest, ধ্রুবক Dimensions dest_dim, ধ্রুবক u32 *source, ধ্রুবক Dimensions source_dim)
{
    পূর্ণসংখ্যা rows = SDL_min(dest_dim.width, source_dim.height);
    পূর্ণসংখ্যা cols = SDL_min(dest_dim.height, source_dim.width);
    জন্য (পূর্ণসংখ্যা y = 0; y < rows; ++y) {
        জন্য (পূর্ণসংখ্যা x = 0; x < cols; ++x) {
            ধ্রুবক u32 *s = source + GetSourceOffset(x, y, source_dim.width);
            u32 *d = dest + GetDestOffset(x, y, dest_dim.width);
            *d = *s;
        }
    }
}

স্থির পূর্ণসংখ্যা GetDestOffset(পূর্ণসংখ্যা x, পূর্ণসংখ্যা y, পূর্ণসংখ্যা dest_width)
{
    ফেরত dest_width - y - 1 + dest_width * x;
}

স্থির পূর্ণসংখ্যা GetSourceOffset(পূর্ণসংখ্যা x, পূর্ণসংখ্যা y, পূর্ণসংখ্যা source_width)
{
    ফেরত x + y * source_width;
}

স্থির শূন্য FlushN3DSBuffer(ধ্রুবক শূন্য *বাফার_2, u32 bufsize, gfxScreen_t screen)
{
    GSPGPU_Flush_তথ্য_Cache(বাফার_2, bufsize);
    gfxScreenSwapBuffers(screen, false);
}

শূন্য SDL_N3DS_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_ClearProperty(SDL_GetWindowProperties(window), N3DS_SURFACE);
}

#endif // SDL_VIDEO_DRIVER_N3DS
