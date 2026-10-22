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
#அந்தர்பாவ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_N3DS

#அந்தர்பாவ "../SDL_sysvideo.h"
#அந்தர்பாவ "../../SDL_properties_c.h"
#அந்தர்பாவ "SDL_n3dsframebuffer_c.h"
#அந்தர்பாவ "SDL_n3dsvideo.h"

#define N3DS_SURFACE "SDL.internal.window.surface"

வகைவரை கட்டமைப்பு
{
    முழு width, height;
} Dimensions;

நிலையான வெறுமை CopyFramebuffertoN3DS_16(u16 *dest, மாறிலி Dimensions dest_dim, மாறிலி u16 *source, மாறிலி Dimensions source_dim);
நிலையான வெறுமை CopyFramebuffertoN3DS_24(u8  *dest, மாறிலி Dimensions dest_dim, மாறிலி u8  *source, மாறிலி Dimensions source_dim);
நிலையான வெறுமை CopyFramebuffertoN3DS_32(u32 *dest, மாறிலி Dimensions dest_dim, மாறிலி u32 *source, மாறிலி Dimensions source_dim);
நிலையான முழு GetDestOffset(முழு x, முழு y, முழு dest_width);
நிலையான முழு GetSourceOffset(முழு x, முழு y, முழு source_width);
நிலையான வெறுமை FlushN3DSBuffer(மாறிலி வெறுமை *buffer, u32 bufsize, gfxScreen_t screen);


bool SDL_N3DS_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, வெறுமை **pixels, முழு *pitch)
{
    SDL_Surface *framebuffer;
    மாறிலி SDL_DisplayMode *mode;
    முழு w, h;

    SDL_N3DS_DestroyWindowFramebuffer(_this, window);

    mode = SDL_GetCurrentDisplayMode(SDL_GetDisplayForWindow(window));
    SDL_GetWindowSizeInPixels(window, &w, &h);
    framebuffer = SDL_CreateSurfaceZeroed(w, h, mode->format);

    எனில் (!framebuffer) {
        திரும்பு false;
    }

    SDL_SetSurfaceProperty(SDL_GetWindowProperties(window), N3DS_SURFACE, framebuffer);
    *format = mode->format;
    *pixels = framebuffer->pixels;
    *pitch = framebuffer->pitch;
    திரும்பு true;
}

bool SDL_N3DS_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, மாறிலி SDL_Rect *rects, முழு numrects)
{
    SDL_WindowData *drv_data = window->internal;
    SDL_Surface *surface;
    u16 width, height;
    வெறுமை *framebuffer;
    u32 bufsize;

    surface = (SDL_Surface *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), N3DS_SURFACE, வெற்று);
    எனில் (!surface) {
        திரும்பு SDL_SetError("%s: Unable to get the window surface.", SDL_FUNCTION);
    }

    // Get the N3DS internal framebuffer and its size
    framebuffer = gfxGetFramebuffer(drv_data->screen, GFX_இடது, &width, &height);
    bufsize = width * height * 4;

    எனில் (SDL_BYTESPERPIXEL(surface->format) == 2)
        CopyFramebuffertoN3DS_16(framebuffer, (Dimensions){ width, height },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    இல்லையெனில் எனில் (SDL_BYTESPERPIXEL(surface->format) == 3)
        CopyFramebuffertoN3DS_24(framebuffer, (Dimensions){ width, height },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    இல்லையெனில்
        CopyFramebuffertoN3DS_32(framebuffer, (Dimensions){ width, height },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    FlushN3DSBuffer(framebuffer, bufsize, drv_data->screen);

    திரும்பு true;
}

நிலையான வெறுமை CopyFramebuffertoN3DS_16(u16 *dest, மாறிலி Dimensions dest_dim, மாறிலி u16 *source, மாறிலி Dimensions source_dim)
{
    முழு rows = SDL_min(dest_dim.width, source_dim.height);
    முழு cols = SDL_min(dest_dim.height, source_dim.width);
    க்கு (முழு y = 0; y < rows; ++y) {
        க்கு (முழு x = 0; x < cols; ++x) {
            மாறிலி u16 *s = source + GetSourceOffset(x, y, source_dim.width);
            u16 *d = dest + GetDestOffset(x, y, dest_dim.width);
            *d = *s;
        }
    }
}

நிலையான வெறுமை CopyFramebuffertoN3DS_24(u8 *dest, மாறிலி Dimensions dest_dim, மாறிலி u8 *source, மாறிலி Dimensions source_dim)
{
    முழு rows = SDL_min(dest_dim.width, source_dim.height);
    முழு cols = SDL_min(dest_dim.height, source_dim.width);
    க்கு (முழு y = 0; y < rows; ++y) {
        க்கு (முழு x = 0; x < cols; ++x) {
            மாறிலி u8 *s = source + GetSourceOffset(x, y, source_dim.width) * 3;
            u8 *d = dest + GetDestOffset(x, y, dest_dim.width) * 3;
            d[0] = s[0];
            d[1] = s[1];
            d[2] = s[2];
        }
    }
}

நிலையான வெறுமை CopyFramebuffertoN3DS_32(u32 *dest, மாறிலி Dimensions dest_dim, மாறிலி u32 *source, மாறிலி Dimensions source_dim)
{
    முழு rows = SDL_min(dest_dim.width, source_dim.height);
    முழு cols = SDL_min(dest_dim.height, source_dim.width);
    க்கு (முழு y = 0; y < rows; ++y) {
        க்கு (முழு x = 0; x < cols; ++x) {
            மாறிலி u32 *s = source + GetSourceOffset(x, y, source_dim.width);
            u32 *d = dest + GetDestOffset(x, y, dest_dim.width);
            *d = *s;
        }
    }
}

நிலையான முழு GetDestOffset(முழு x, முழு y, முழு dest_width)
{
    திரும்பு dest_width - y - 1 + dest_width * x;
}

நிலையான முழு GetSourceOffset(முழு x, முழு y, முழு source_width)
{
    திரும்பு x + y * source_width;
}

நிலையான வெறுமை FlushN3DSBuffer(மாறிலி வெறுமை *buffer, u32 bufsize, gfxScreen_t screen)
{
    GSPGPU_FlushDataCache(buffer, bufsize);
    gfxScreenSwapBuffers(screen, false);
}

வெறுமை SDL_N3DS_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_ClearProperty(SDL_GetWindowProperties(window), N3DS_SURFACE);
}

#endif // SDL_VIDEO_DRIVER_N3DS
