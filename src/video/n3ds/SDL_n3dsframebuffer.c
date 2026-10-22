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
#અન્તર્ભાવ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_N3DS

#અન્તર્ભાવ "../SDL_sysvideo.h"
#અન્તર્ભાવ "../../SDL_properties_c.h"
#અન્તર્ભાવ "SDL_n3dsframebuffer_c.h"
#અન્તર્ભાવ "SDL_n3dsvideo.h"

#define N3DS_SURFACE "SDL.internal.window.surface"

પ્રકારવ્યાખ્યા સંરચના
{
    પૂર્ણાંક width, height;
} Dimensions;

સ્થિર શૂન્ય CopyFramebuffertoN3DS_16(u16 *dest, અચલ Dimensions dest_dim, અચલ u16 *source, અચલ Dimensions source_dim);
સ્થિર શૂન્ય CopyFramebuffertoN3DS_24(u8  *dest, અચલ Dimensions dest_dim, અચલ u8  *source, અચલ Dimensions source_dim);
સ્થિર શૂન્ય CopyFramebuffertoN3DS_32(u32 *dest, અચલ Dimensions dest_dim, અચલ u32 *source, અચલ Dimensions source_dim);
સ્થિર પૂર્ણાંક GetDestOffset(પૂર્ણાંક x, પૂર્ણાંક y, પૂર્ણાંક dest_width);
સ્થિર પૂર્ણાંક GetSourceOffset(પૂર્ણાંક x, પૂર્ણાંક y, પૂર્ણાંક source_width);
સ્થિર શૂન્ય FlushN3DSBuffer(અચલ શૂન્ય *buffer, u32 bufsize, gfxScreen_t screen);


bool SDL_N3DS_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, શૂન્ય **pixels, પૂર્ણાંક *pitch)
{
    SDL_Surface *framebuffer;
    અચલ SDL_DisplayMode *mode;
    પૂર્ણાંક w, h;

    SDL_N3DS_DestroyWindowFramebuffer(_this, window);

    mode = SDL_GetCurrentDisplayMode(SDL_GetDisplayForWindow(window));
    SDL_GetWindowSizeInPixels(window, &w, &h);
    framebuffer = SDL_CreateSurfaceZeroed(w, h, mode->format);

    જો (!framebuffer) {
        પાછા false;
    }

    SDL_SetSurfaceProperty(SDL_GetWindowProperties(window), N3DS_SURFACE, framebuffer);
    *format = mode->format;
    *pixels = framebuffer->pixels;
    *pitch = framebuffer->pitch;
    પાછા true;
}

bool SDL_N3DS_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, અચલ SDL_Rect *rects, પૂર્ણાંક numrects)
{
    SDL_WindowData *drv_data = window->internal;
    SDL_Surface *surface;
    u16 width, height;
    શૂન્ય *framebuffer;
    u32 bufsize;

    surface = (SDL_Surface *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), N3DS_SURFACE, ખાલી);
    જો (!surface) {
        પાછા SDL_SetError("%s: Unable to get the window surface.", SDL_FUNCTION);
    }

    // Get the N3DS internal framebuffer and its size
    framebuffer = gfxGetFramebuffer(drv_data->screen, GFX_ડાબું, &width, &height);
    bufsize = width * height * 4;

    જો (SDL_BYTESPERPIXEL(surface->format) == 2)
        CopyFramebuffertoN3DS_16(framebuffer, (Dimensions){ width, height },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    નહીંતર જો (SDL_BYTESPERPIXEL(surface->format) == 3)
        CopyFramebuffertoN3DS_24(framebuffer, (Dimensions){ width, height },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    નહીંતર
        CopyFramebuffertoN3DS_32(framebuffer, (Dimensions){ width, height },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    FlushN3DSBuffer(framebuffer, bufsize, drv_data->screen);

    પાછા true;
}

સ્થિર શૂન્ય CopyFramebuffertoN3DS_16(u16 *dest, અચલ Dimensions dest_dim, અચલ u16 *source, અચલ Dimensions source_dim)
{
    પૂર્ણાંક rows = SDL_min(dest_dim.width, source_dim.height);
    પૂર્ણાંક cols = SDL_min(dest_dim.height, source_dim.width);
    માટે (પૂર્ણાંક y = 0; y < rows; ++y) {
        માટે (પૂર્ણાંક x = 0; x < cols; ++x) {
            અચલ u16 *s = source + GetSourceOffset(x, y, source_dim.width);
            u16 *d = dest + GetDestOffset(x, y, dest_dim.width);
            *d = *s;
        }
    }
}

સ્થિર શૂન્ય CopyFramebuffertoN3DS_24(u8 *dest, અચલ Dimensions dest_dim, અચલ u8 *source, અચલ Dimensions source_dim)
{
    પૂર્ણાંક rows = SDL_min(dest_dim.width, source_dim.height);
    પૂર્ણાંક cols = SDL_min(dest_dim.height, source_dim.width);
    માટે (પૂર્ણાંક y = 0; y < rows; ++y) {
        માટે (પૂર્ણાંક x = 0; x < cols; ++x) {
            અચલ u8 *s = source + GetSourceOffset(x, y, source_dim.width) * 3;
            u8 *d = dest + GetDestOffset(x, y, dest_dim.width) * 3;
            d[0] = s[0];
            d[1] = s[1];
            d[2] = s[2];
        }
    }
}

સ્થિર શૂન્ય CopyFramebuffertoN3DS_32(u32 *dest, અચલ Dimensions dest_dim, અચલ u32 *source, અચલ Dimensions source_dim)
{
    પૂર્ણાંક rows = SDL_min(dest_dim.width, source_dim.height);
    પૂર્ણાંક cols = SDL_min(dest_dim.height, source_dim.width);
    માટે (પૂર્ણાંક y = 0; y < rows; ++y) {
        માટે (પૂર્ણાંક x = 0; x < cols; ++x) {
            અચલ u32 *s = source + GetSourceOffset(x, y, source_dim.width);
            u32 *d = dest + GetDestOffset(x, y, dest_dim.width);
            *d = *s;
        }
    }
}

સ્થિર પૂર્ણાંક GetDestOffset(પૂર્ણાંક x, પૂર્ણાંક y, પૂર્ણાંક dest_width)
{
    પાછા dest_width - y - 1 + dest_width * x;
}

સ્થિર પૂર્ણાંક GetSourceOffset(પૂર્ણાંક x, પૂર્ણાંક y, પૂર્ણાંક source_width)
{
    પાછા x + y * source_width;
}

સ્થિર શૂન્ય FlushN3DSBuffer(અચલ શૂન્ય *buffer, u32 bufsize, gfxScreen_t screen)
{
    GSPGPU_FlushDataCache(buffer, bufsize);
    gfxScreenSwapBuffers(screen, false);
}

શૂન્ય SDL_N3DS_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_ClearProperty(SDL_GetWindowProperties(window), N3DS_SURFACE);
}

#endif // SDL_VIDEO_DRIVER_N3DS
