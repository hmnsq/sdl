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

#ifdef SDL_VIDEO_DRIVER_N3DS

#شامل "../SDL_sysvideo.h"
#شامل "../../SDL_properties_c.h"
#شامل "SDL_n3dsframebuffer_c.h"
#شامل "SDL_n3dsvideo.h"

#define N3DS_SURFACE "SDL.internal.window.surface"

تعریفنوع ساختار
{
    صحیح width, height;
} Dimensions;

ایستا تهی CopyFramebuffertoN3DS_16(u16 *dest, ثابت Dimensions dest_dim, ثابت u16 *source, ثابت Dimensions source_dim);
ایستا تهی CopyFramebuffertoN3DS_24(u8  *dest, ثابت Dimensions dest_dim, ثابت u8  *source, ثابت Dimensions source_dim);
ایستا تهی CopyFramebuffertoN3DS_32(u32 *dest, ثابت Dimensions dest_dim, ثابت u32 *source, ثابت Dimensions source_dim);
ایستا صحیح GetDestOffset(صحیح x, صحیح y, صحیح dest_width);
ایستا صحیح GetSourceOffset(صحیح x, صحیح y, صحیح source_width);
ایستا تهی FlushN3DSBuffer(ثابت تهی *buffer, u32 bufsize, gfxScreen_t screen);


bool SDL_N3DS_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, تهی **pixels, صحیح *pitch)
{
    SDL_Surface *framebuffer;
    ثابت SDL_DisplayMode *mode;
    صحیح w, h;

    SDL_N3DS_DestroyWindowFramebuffer(_this, window);

    mode = SDL_GetCurrentDisplayMode(SDL_GetDisplayForWindow(window));
    SDL_GetWindowSizeInPixels(window, &w, &h);
    framebuffer = SDL_CreateSurfaceZeroed(w, h, mode->format);

    اگر (!framebuffer) {
        بازگشت false;
    }

    SDL_SetSurfaceProperty(SDL_GetWindowProperties(window), N3DS_SURFACE, framebuffer);
    *format = mode->format;
    *pixels = framebuffer->pixels;
    *pitch = framebuffer->pitch;
    بازگشت true;
}

bool SDL_N3DS_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, ثابت SDL_Rect *rects, صحیح numrects)
{
    SDL_WindowData *drv_data = window->internal;
    SDL_Surface *surface;
    u16 width, height;
    تهی *framebuffer;
    u32 bufsize;

    surface = (SDL_Surface *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), N3DS_SURFACE, پوچ);
    اگر (!surface) {
        بازگشت SDL_SetError("%s: Unable to get the window surface.", SDL_FUNCTION);
    }

    // Get the N3DS internal framebuffer and its size
    framebuffer = gfxGetFramebuffer(drv_data->screen, GFX_چپ, &width, &height);
    bufsize = width * height * 4;

    اگر (SDL_BYTESPERPIXEL(surface->format) == 2)
        CopyFramebuffertoN3DS_16(framebuffer, (Dimensions){ width, height },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    وگرنه اگر (SDL_BYTESPERPIXEL(surface->format) == 3)
        CopyFramebuffertoN3DS_24(framebuffer, (Dimensions){ width, height },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    وگرنه
        CopyFramebuffertoN3DS_32(framebuffer, (Dimensions){ width, height },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    FlushN3DSBuffer(framebuffer, bufsize, drv_data->screen);

    بازگشت true;
}

ایستا تهی CopyFramebuffertoN3DS_16(u16 *dest, ثابت Dimensions dest_dim, ثابت u16 *source, ثابت Dimensions source_dim)
{
    صحیح rows = SDL_min(dest_dim.width, source_dim.height);
    صحیح cols = SDL_min(dest_dim.height, source_dim.width);
    برای (صحیح y = 0; y < rows; ++y) {
        برای (صحیح x = 0; x < cols; ++x) {
            ثابت u16 *s = source + GetSourceOffset(x, y, source_dim.width);
            u16 *d = dest + GetDestOffset(x, y, dest_dim.width);
            *d = *s;
        }
    }
}

ایستا تهی CopyFramebuffertoN3DS_24(u8 *dest, ثابت Dimensions dest_dim, ثابت u8 *source, ثابت Dimensions source_dim)
{
    صحیح rows = SDL_min(dest_dim.width, source_dim.height);
    صحیح cols = SDL_min(dest_dim.height, source_dim.width);
    برای (صحیح y = 0; y < rows; ++y) {
        برای (صحیح x = 0; x < cols; ++x) {
            ثابت u8 *s = source + GetSourceOffset(x, y, source_dim.width) * 3;
            u8 *d = dest + GetDestOffset(x, y, dest_dim.width) * 3;
            d[0] = s[0];
            d[1] = s[1];
            d[2] = s[2];
        }
    }
}

ایستا تهی CopyFramebuffertoN3DS_32(u32 *dest, ثابت Dimensions dest_dim, ثابت u32 *source, ثابت Dimensions source_dim)
{
    صحیح rows = SDL_min(dest_dim.width, source_dim.height);
    صحیح cols = SDL_min(dest_dim.height, source_dim.width);
    برای (صحیح y = 0; y < rows; ++y) {
        برای (صحیح x = 0; x < cols; ++x) {
            ثابت u32 *s = source + GetSourceOffset(x, y, source_dim.width);
            u32 *d = dest + GetDestOffset(x, y, dest_dim.width);
            *d = *s;
        }
    }
}

ایستا صحیح GetDestOffset(صحیح x, صحیح y, صحیح dest_width)
{
    بازگشت dest_width - y - 1 + dest_width * x;
}

ایستا صحیح GetSourceOffset(صحیح x, صحیح y, صحیح source_width)
{
    بازگشت x + y * source_width;
}

ایستا تهی FlushN3DSBuffer(ثابت تهی *buffer, u32 bufsize, gfxScreen_t screen)
{
    GSPGPU_FlushDataCache(buffer, bufsize);
    gfxScreenSwapBuffers(screen, false);
}

تهی SDL_N3DS_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_ClearProperty(SDL_GetWindowProperties(window), N3DS_SURFACE);
}

#endif // SDL_VIDEO_DRIVER_N3DS
