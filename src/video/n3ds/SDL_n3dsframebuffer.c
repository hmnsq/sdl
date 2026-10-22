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

#ifdef SDL_VIDEO_DRIVER_N3DS

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "../../SDL_properties_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_n3dsframebuffer_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_n3dsvideo.h"

#define N3DS_SURFACE "SDL.internal.window.surface"

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ
{
    ಪೂರ್ಣಾಙ್ಕ width, height;
} Dimensions;

ಸ್ಥಿರ ಶೂನ್ಯ CopyFramebuffertoN3DS_16(u16 *dest, ಧ್ರುವ Dimensions dest_dim, ಧ್ರುವ u16 *source, ಧ್ರುವ Dimensions source_dim);
ಸ್ಥಿರ ಶೂನ್ಯ CopyFramebuffertoN3DS_24(u8  *dest, ಧ್ರುವ Dimensions dest_dim, ಧ್ರುವ u8  *source, ಧ್ರುವ Dimensions source_dim);
ಸ್ಥಿರ ಶೂನ್ಯ CopyFramebuffertoN3DS_32(u32 *dest, ಧ್ರುವ Dimensions dest_dim, ಧ್ರುವ u32 *source, ಧ್ರುವ Dimensions source_dim);
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ GetDestOffset(ಪೂರ್ಣಾಙ್ಕ x, ಪೂರ್ಣಾಙ್ಕ y, ಪೂರ್ಣಾಙ್ಕ dest_width);
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ GetSourceOffset(ಪೂರ್ಣಾಙ್ಕ x, ಪೂರ್ಣಾಙ್ಕ y, ಪೂರ್ಣಾಙ್ಕ source_width);
ಸ್ಥಿರ ಶೂನ್ಯ FlushN3DSBuffer(ಧ್ರುವ ಶೂನ್ಯ *buffer, u32 bufsize, gfxScreen_t screen);


bool SDL_N3DS_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, ಶೂನ್ಯ **pixels, ಪೂರ್ಣಾಙ್ಕ *pitch)
{
    SDL_Surface *framebuffer;
    ಧ್ರುವ SDL_DisplayMode *mode;
    ಪೂರ್ಣಾಙ್ಕ w, h;

    SDL_N3DS_DestroyWindowFramebuffer(_this, window);

    mode = SDL_GetCurrentDisplayMode(SDL_GetDisplayForWindow(window));
    SDL_GetWindowSizeInPixels(window, &w, &h);
    framebuffer = SDL_CreateSurfaceZeroed(w, h, mode->format);

    ಯದಿ (!framebuffer) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    SDL_SetSurfaceProperty(SDL_GetWindowProperties(window), N3DS_SURFACE, framebuffer);
    *format = mode->format;
    *pixels = framebuffer->pixels;
    *pitch = framebuffer->pitch;
    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_N3DS_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, ಧ್ರುವ SDL_Rect *rects, ಪೂರ್ಣಾಙ್ಕ numrects)
{
    SDL_WindowData *drv_data = window->internal;
    SDL_Surface *surface;
    u16 width, height;
    ಶೂನ್ಯ *framebuffer;
    u32 bufsize;

    surface = (SDL_Surface *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), N3DS_SURFACE, ರಿಕ್ತ);
    ಯದಿ (!surface) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("%s: Unable to get the window surface.", SDL_FUNCTION);
    }

    // Get the N3DS internal framebuffer and its size
    framebuffer = gfxGetFramebuffer(drv_data->screen, GFX_ಎಡ, &width, &height);
    bufsize = width * height * 4;

    ಯದಿ (SDL_BYTESPERPIXEL(surface->format) == 2)
        CopyFramebuffertoN3DS_16(framebuffer, (Dimensions){ width, height },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    ಅನ್ಯಥಾ ಯದಿ (SDL_BYTESPERPIXEL(surface->format) == 3)
        CopyFramebuffertoN3DS_24(framebuffer, (Dimensions){ width, height },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    ಅನ್ಯಥಾ
        CopyFramebuffertoN3DS_32(framebuffer, (Dimensions){ width, height },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    FlushN3DSBuffer(framebuffer, bufsize, drv_data->screen);

    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ ಶೂನ್ಯ CopyFramebuffertoN3DS_16(u16 *dest, ಧ್ರುವ Dimensions dest_dim, ಧ್ರುವ u16 *source, ಧ್ರುವ Dimensions source_dim)
{
    ಪೂರ್ಣಾಙ್ಕ rows = SDL_min(dest_dim.width, source_dim.height);
    ಪೂರ್ಣಾಙ್ಕ cols = SDL_min(dest_dim.height, source_dim.width);
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ y = 0; y < rows; ++y) {
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ x = 0; x < cols; ++x) {
            ಧ್ರುವ u16 *s = source + GetSourceOffset(x, y, source_dim.width);
            u16 *d = dest + GetDestOffset(x, y, dest_dim.width);
            *d = *s;
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ CopyFramebuffertoN3DS_24(u8 *dest, ಧ್ರುವ Dimensions dest_dim, ಧ್ರುವ u8 *source, ಧ್ರುವ Dimensions source_dim)
{
    ಪೂರ್ಣಾಙ್ಕ rows = SDL_min(dest_dim.width, source_dim.height);
    ಪೂರ್ಣಾಙ್ಕ cols = SDL_min(dest_dim.height, source_dim.width);
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ y = 0; y < rows; ++y) {
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ x = 0; x < cols; ++x) {
            ಧ್ರುವ u8 *s = source + GetSourceOffset(x, y, source_dim.width) * 3;
            u8 *d = dest + GetDestOffset(x, y, dest_dim.width) * 3;
            d[0] = s[0];
            d[1] = s[1];
            d[2] = s[2];
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ CopyFramebuffertoN3DS_32(u32 *dest, ಧ್ರುವ Dimensions dest_dim, ಧ್ರುವ u32 *source, ಧ್ರುವ Dimensions source_dim)
{
    ಪೂರ್ಣಾಙ್ಕ rows = SDL_min(dest_dim.width, source_dim.height);
    ಪೂರ್ಣಾಙ್ಕ cols = SDL_min(dest_dim.height, source_dim.width);
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ y = 0; y < rows; ++y) {
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ x = 0; x < cols; ++x) {
            ಧ್ರುವ u32 *s = source + GetSourceOffset(x, y, source_dim.width);
            u32 *d = dest + GetDestOffset(x, y, dest_dim.width);
            *d = *s;
        }
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ GetDestOffset(ಪೂರ್ಣಾಙ್ಕ x, ಪೂರ್ಣಾಙ್ಕ y, ಪೂರ್ಣಾಙ್ಕ dest_width)
{
    ಪ್ರತ್ಯಾಗಮ dest_width - y - 1 + dest_width * x;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ GetSourceOffset(ಪೂರ್ಣಾಙ್ಕ x, ಪೂರ್ಣಾಙ್ಕ y, ಪೂರ್ಣಾಙ್ಕ source_width)
{
    ಪ್ರತ್ಯಾಗಮ x + y * source_width;
}

ಸ್ಥಿರ ಶೂನ್ಯ FlushN3DSBuffer(ಧ್ರುವ ಶೂನ್ಯ *buffer, u32 bufsize, gfxScreen_t screen)
{
    GSPGPU_FlushDataCache(buffer, bufsize);
    gfxScreenSwapBuffers(screen, false);
}

ಶೂನ್ಯ SDL_N3DS_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_ClearProperty(SDL_GetWindowProperties(window), N3DS_SURFACE);
}

#endif // SDL_VIDEO_DRIVER_N3DS
