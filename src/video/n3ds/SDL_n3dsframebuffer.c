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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_N3DS

#ଅନ୍ତର୍ଭାଵ "../SDL_sysvideo.h"
#ଅନ୍ତର୍ଭାଵ "../../SDL_properties_c.h"
#ଅନ୍ତର୍ଭାଵ "SDL_n3dsframebuffer_c.h"
#ଅନ୍ତର୍ଭାଵ "SDL_n3dsvideo.h"

#define N3DS_SURFACE "SDL.internal.window.surface"

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, height;
} Dimensions;

ସ୍ଥିର ଶୂନ୍ୟ CopyFramebuffertoN3DS_16(u16 *dest, ଅଚଳ Dimensions dest_dim, ଅଚଳ u16 *source, ଅଚଳ Dimensions source_dim);
ସ୍ଥିର ଶୂନ୍ୟ CopyFramebuffertoN3DS_24(u8  *dest, ଅଚଳ Dimensions dest_dim, ଅଚଳ u8  *source, ଅଚଳ Dimensions source_dim);
ସ୍ଥିର ଶୂନ୍ୟ CopyFramebuffertoN3DS_32(u32 *dest, ଅଚଳ Dimensions dest_dim, ଅଚଳ u32 *source, ଅଚଳ Dimensions source_dim);
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା GetDestOffset(ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା y, ପୂର୍ଣ୍ଣସଂଖ୍ୟା dest_width);
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା GetSourceOffset(ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା y, ପୂର୍ଣ୍ଣସଂଖ୍ୟା source_width);
ସ୍ଥିର ଶୂନ୍ୟ FlushN3DSBuffer(ଅଚଳ ଶୂନ୍ୟ *buffer, u32 bufsize, gfxScreen_t screen);


bool SDL_N3DS_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, ଶୂନ୍ୟ **pixels, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *pitch)
{
    SDL_Surface *framebuffer;
    ଅଚଳ SDL_DisplayMode *mode;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା w, h;

    SDL_N3DS_DestroyWindowFramebuffer(_this, window);

    mode = SDL_GetCurrentDisplayMode(SDL_GetDisplayForWindow(window));
    SDL_GetWindowSizeInPixels(window, &w, &h);
    framebuffer = SDL_CreateSurfaceZeroed(w, h, mode->format);

    ଯଦି (!framebuffer) {
        ଫେରନ୍ତୁ false;
    }

    SDL_SetSurfaceProperty(SDL_GetWindowProperties(window), N3DS_SURFACE, framebuffer);
    *format = mode->format;
    *pixels = framebuffer->pixels;
    *pitch = framebuffer->pitch;
    ଫେରନ୍ତୁ true;
}

bool SDL_N3DS_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, ଅଚଳ SDL_Rect *rects, ପୂର୍ଣ୍ଣସଂଖ୍ୟା numrects)
{
    SDL_WindowData *drv_data = window->internal;
    SDL_Surface *surface;
    u16 width, height;
    ଶୂନ୍ୟ *framebuffer;
    u32 bufsize;

    surface = (SDL_Surface *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), N3DS_SURFACE, ଖାଲି);
    ଯଦି (!surface) {
        ଫେରନ୍ତୁ SDL_SetError("%s: Unable to get the window surface.", SDL_FUNCTION);
    }

    // Get the N3DS internal framebuffer and its size
    framebuffer = gfxGetFramebuffer(drv_data->screen, GFX_ବାମ, &width, &height);
    bufsize = width * height * 4;

    ଯଦି (SDL_BYTESPERPIXEL(surface->format) == 2)
        CopyFramebuffertoN3DS_16(framebuffer, (Dimensions){ width, height },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    ଅନ୍ୟଥା ଯଦି (SDL_BYTESPERPIXEL(surface->format) == 3)
        CopyFramebuffertoN3DS_24(framebuffer, (Dimensions){ width, height },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    ଅନ୍ୟଥା
        CopyFramebuffertoN3DS_32(framebuffer, (Dimensions){ width, height },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    FlushN3DSBuffer(framebuffer, bufsize, drv_data->screen);

    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର ଶୂନ୍ୟ CopyFramebuffertoN3DS_16(u16 *dest, ଅଚଳ Dimensions dest_dim, ଅଚଳ u16 *source, ଅଚଳ Dimensions source_dim)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା rows = SDL_min(dest_dim.width, source_dim.height);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା cols = SDL_min(dest_dim.height, source_dim.width);
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା y = 0; y < rows; ++y) {
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା x = 0; x < cols; ++x) {
            ଅଚଳ u16 *s = source + GetSourceOffset(x, y, source_dim.width);
            u16 *d = dest + GetDestOffset(x, y, dest_dim.width);
            *d = *s;
        }
    }
}

ସ୍ଥିର ଶୂନ୍ୟ CopyFramebuffertoN3DS_24(u8 *dest, ଅଚଳ Dimensions dest_dim, ଅଚଳ u8 *source, ଅଚଳ Dimensions source_dim)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା rows = SDL_min(dest_dim.width, source_dim.height);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା cols = SDL_min(dest_dim.height, source_dim.width);
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା y = 0; y < rows; ++y) {
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା x = 0; x < cols; ++x) {
            ଅଚଳ u8 *s = source + GetSourceOffset(x, y, source_dim.width) * 3;
            u8 *d = dest + GetDestOffset(x, y, dest_dim.width) * 3;
            d[0] = s[0];
            d[1] = s[1];
            d[2] = s[2];
        }
    }
}

ସ୍ଥିର ଶୂନ୍ୟ CopyFramebuffertoN3DS_32(u32 *dest, ଅଚଳ Dimensions dest_dim, ଅଚଳ u32 *source, ଅଚଳ Dimensions source_dim)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା rows = SDL_min(dest_dim.width, source_dim.height);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା cols = SDL_min(dest_dim.height, source_dim.width);
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା y = 0; y < rows; ++y) {
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା x = 0; x < cols; ++x) {
            ଅଚଳ u32 *s = source + GetSourceOffset(x, y, source_dim.width);
            u32 *d = dest + GetDestOffset(x, y, dest_dim.width);
            *d = *s;
        }
    }
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା GetDestOffset(ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା y, ପୂର୍ଣ୍ଣସଂଖ୍ୟା dest_width)
{
    ଫେରନ୍ତୁ dest_width - y - 1 + dest_width * x;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା GetSourceOffset(ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା y, ପୂର୍ଣ୍ଣସଂଖ୍ୟା source_width)
{
    ଫେରନ୍ତୁ x + y * source_width;
}

ସ୍ଥିର ଶୂନ୍ୟ FlushN3DSBuffer(ଅଚଳ ଶୂନ୍ୟ *buffer, u32 bufsize, gfxScreen_t screen)
{
    GSPGPU_FlushDataCache(buffer, bufsize);
    gfxScreenSwapBuffers(screen, false);
}

ଶୂନ୍ୟ SDL_N3DS_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_ClearProperty(SDL_GetWindowProperties(window), N3DS_SURFACE);
}

#endif // SDL_VIDEO_DRIVER_N3DS
