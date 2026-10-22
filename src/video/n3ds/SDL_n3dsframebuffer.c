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

#ifdef SDL_VIDEO_DRIVER_N3DS

#അന്തര്ഭാവ "../SDL_sysvideo.h"
#അന്തര്ഭാവ "../../SDL_properties_c.h"
#അന്തര്ഭാവ "SDL_n3dsframebuffer_c.h"
#അന്തര്ഭാവ "SDL_n3dsvideo.h"

#define N3DS_SURFACE "SDL.internal.window.surface"

തരനിർവചനം ഘടന
{
    പൂർണ്ണസംഖ്യ width, height;
} Dimensions;

സ്ഥിതം ശൂന്യം CopyFramebuffertoN3DS_16(u16 *dest, സ്ഥിരം Dimensions dest_dim, സ്ഥിരം u16 *source, സ്ഥിരം Dimensions source_dim);
സ്ഥിതം ശൂന്യം CopyFramebuffertoN3DS_24(u8  *dest, സ്ഥിരം Dimensions dest_dim, സ്ഥിരം u8  *source, സ്ഥിരം Dimensions source_dim);
സ്ഥിതം ശൂന്യം CopyFramebuffertoN3DS_32(u32 *dest, സ്ഥിരം Dimensions dest_dim, സ്ഥിരം u32 *source, സ്ഥിരം Dimensions source_dim);
സ്ഥിതം പൂർണ്ണസംഖ്യ GetDestOffset(പൂർണ്ണസംഖ്യ x, പൂർണ്ണസംഖ്യ y, പൂർണ്ണസംഖ്യ dest_width);
സ്ഥിതം പൂർണ്ണസംഖ്യ GetSourceOffset(പൂർണ്ണസംഖ്യ x, പൂർണ്ണസംഖ്യ y, പൂർണ്ണസംഖ്യ source_width);
സ്ഥിതം ശൂന്യം FlushN3DSBuffer(സ്ഥിരം ശൂന്യം *buffer, u32 bufsize, gfxScreen_t screen);


bool SDL_N3DS_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, ശൂന്യം **pixels, പൂർണ്ണസംഖ്യ *pitch)
{
    SDL_Surface *framebuffer;
    സ്ഥിരം SDL_DisplayMode *mode;
    പൂർണ്ണസംഖ്യ w, h;

    SDL_N3DS_DestroyWindowFramebuffer(_this, window);

    mode = SDL_GetCurrentDisplayMode(SDL_GetDisplayForWindow(window));
    SDL_GetWindowSizeInPixels(window, &w, &h);
    framebuffer = SDL_CreateSurfaceZeroed(w, h, mode->format);

    എങ്കിൽ (!framebuffer) {
        തിരികെ false;
    }

    SDL_SetSurfaceProperty(SDL_GetWindowProperties(window), N3DS_SURFACE, framebuffer);
    *format = mode->format;
    *pixels = framebuffer->pixels;
    *pitch = framebuffer->pitch;
    തിരികെ true;
}

bool SDL_N3DS_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, സ്ഥിരം SDL_Rect *rects, പൂർണ്ണസംഖ്യ numrects)
{
    SDL_WindowData *drv_data = window->internal;
    SDL_Surface *surface;
    u16 width, height;
    ശൂന്യം *framebuffer;
    u32 bufsize;

    surface = (SDL_Surface *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), N3DS_SURFACE, ശൂന്യ);
    എങ്കിൽ (!surface) {
        തിരികെ SDL_SetError("%s: Unable to get the window surface.", SDL_FUNCTION);
    }

    // Get the N3DS internal framebuffer and its size
    framebuffer = gfxGetFramebuffer(drv_data->screen, GFX_ഇടത്, &width, &height);
    bufsize = width * height * 4;

    എങ്കിൽ (SDL_BYTESPERPIXEL(surface->format) == 2)
        CopyFramebuffertoN3DS_16(framebuffer, (Dimensions){ width, height },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    അല്ലെങ്കിൽ എങ്കിൽ (SDL_BYTESPERPIXEL(surface->format) == 3)
        CopyFramebuffertoN3DS_24(framebuffer, (Dimensions){ width, height },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    അല്ലെങ്കിൽ
        CopyFramebuffertoN3DS_32(framebuffer, (Dimensions){ width, height },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    FlushN3DSBuffer(framebuffer, bufsize, drv_data->screen);

    തിരികെ true;
}

സ്ഥിതം ശൂന്യം CopyFramebuffertoN3DS_16(u16 *dest, സ്ഥിരം Dimensions dest_dim, സ്ഥിരം u16 *source, സ്ഥിരം Dimensions source_dim)
{
    പൂർണ്ണസംഖ്യ rows = SDL_min(dest_dim.width, source_dim.height);
    പൂർണ്ണസംഖ്യ cols = SDL_min(dest_dim.height, source_dim.width);
    വേണ്ടി (പൂർണ്ണസംഖ്യ y = 0; y < rows; ++y) {
        വേണ്ടി (പൂർണ്ണസംഖ്യ x = 0; x < cols; ++x) {
            സ്ഥിരം u16 *s = source + GetSourceOffset(x, y, source_dim.width);
            u16 *d = dest + GetDestOffset(x, y, dest_dim.width);
            *d = *s;
        }
    }
}

സ്ഥിതം ശൂന്യം CopyFramebuffertoN3DS_24(u8 *dest, സ്ഥിരം Dimensions dest_dim, സ്ഥിരം u8 *source, സ്ഥിരം Dimensions source_dim)
{
    പൂർണ്ണസംഖ്യ rows = SDL_min(dest_dim.width, source_dim.height);
    പൂർണ്ണസംഖ്യ cols = SDL_min(dest_dim.height, source_dim.width);
    വേണ്ടി (പൂർണ്ണസംഖ്യ y = 0; y < rows; ++y) {
        വേണ്ടി (പൂർണ്ണസംഖ്യ x = 0; x < cols; ++x) {
            സ്ഥിരം u8 *s = source + GetSourceOffset(x, y, source_dim.width) * 3;
            u8 *d = dest + GetDestOffset(x, y, dest_dim.width) * 3;
            d[0] = s[0];
            d[1] = s[1];
            d[2] = s[2];
        }
    }
}

സ്ഥിതം ശൂന്യം CopyFramebuffertoN3DS_32(u32 *dest, സ്ഥിരം Dimensions dest_dim, സ്ഥിരം u32 *source, സ്ഥിരം Dimensions source_dim)
{
    പൂർണ്ണസംഖ്യ rows = SDL_min(dest_dim.width, source_dim.height);
    പൂർണ്ണസംഖ്യ cols = SDL_min(dest_dim.height, source_dim.width);
    വേണ്ടി (പൂർണ്ണസംഖ്യ y = 0; y < rows; ++y) {
        വേണ്ടി (പൂർണ്ണസംഖ്യ x = 0; x < cols; ++x) {
            സ്ഥിരം u32 *s = source + GetSourceOffset(x, y, source_dim.width);
            u32 *d = dest + GetDestOffset(x, y, dest_dim.width);
            *d = *s;
        }
    }
}

സ്ഥിതം പൂർണ്ണസംഖ്യ GetDestOffset(പൂർണ്ണസംഖ്യ x, പൂർണ്ണസംഖ്യ y, പൂർണ്ണസംഖ്യ dest_width)
{
    തിരികെ dest_width - y - 1 + dest_width * x;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ GetSourceOffset(പൂർണ്ണസംഖ്യ x, പൂർണ്ണസംഖ്യ y, പൂർണ്ണസംഖ്യ source_width)
{
    തിരികെ x + y * source_width;
}

സ്ഥിതം ശൂന്യം FlushN3DSBuffer(സ്ഥിരം ശൂന്യം *buffer, u32 bufsize, gfxScreen_t screen)
{
    GSPGPU_FlushDataCache(buffer, bufsize);
    gfxScreenSwapBuffers(screen, false);
}

ശൂന്യം SDL_N3DS_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_ClearProperty(SDL_GetWindowProperties(window), N3DS_SURFACE);
}

#endif // SDL_VIDEO_DRIVER_N3DS
