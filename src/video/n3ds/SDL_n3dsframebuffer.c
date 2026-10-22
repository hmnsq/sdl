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
#अन्तर्भाव "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_N3DS

#अन्तर्भाव "../SDL_sysvideo.h"
#अन्तर्भाव "../../SDL_properties_c.h"
#अन्तर्भाव "SDL_n3dsframebuffer_c.h"
#अन्तर्भाव "SDL_n3dsvideo.h"

#define N3DS_SURFACE "SDL.internal.window.surface"

प्रकारव्याख्या संरचना
{
    पूर्णांक width, height;
} Dimensions;

स्थिर शून्य CopyFramebuffertoN3DS_16(u16 *dest, स्थिरांक Dimensions dest_dim, स्थिरांक u16 *source, स्थिरांक Dimensions source_dim);
स्थिर शून्य CopyFramebuffertoN3DS_24(u8  *dest, स्थिरांक Dimensions dest_dim, स्थिरांक u8  *source, स्थिरांक Dimensions source_dim);
स्थिर शून्य CopyFramebuffertoN3DS_32(u32 *dest, स्थिरांक Dimensions dest_dim, स्थिरांक u32 *source, स्थिरांक Dimensions source_dim);
स्थिर पूर्णांक GetDestOffset(पूर्णांक x, पूर्णांक y, पूर्णांक dest_width);
स्थिर पूर्णांक GetSourceOffset(पूर्णांक x, पूर्णांक y, पूर्णांक source_width);
स्थिर शून्य FlushN3DSBuffer(स्थिरांक शून्य *buffer, u32 bufsize, gfxScreen_t screen);


bool SDL_N3DS_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, शून्य **pixels, पूर्णांक *pitch)
{
    SDL_Surface *framebuffer;
    स्थिरांक SDL_DisplayMode *mode;
    पूर्णांक w, h;

    SDL_N3DS_DestroyWindowFramebuffer(_this, window);

    mode = SDL_GetCurrentDisplayMode(SDL_GetDisplayForWindow(window));
    SDL_GetWindowSizeInPixels(window, &w, &h);
    framebuffer = SDL_CreateSurfaceZeroed(w, h, mode->format);

    जर (!framebuffer) {
        परत false;
    }

    SDL_SetSurfaceProperty(SDL_GetWindowProperties(window), N3DS_SURFACE, framebuffer);
    *format = mode->format;
    *pixels = framebuffer->pixels;
    *pitch = framebuffer->pitch;
    परत true;
}

bool SDL_N3DS_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, स्थिरांक SDL_Rect *rects, पूर्णांक numrects)
{
    SDL_WindowData *drv_data = window->internal;
    SDL_Surface *surface;
    u16 width, height;
    शून्य *framebuffer;
    u32 bufsize;

    surface = (SDL_Surface *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), N3DS_SURFACE, रिक्त);
    जर (!surface) {
        परत SDL_SetError("%s: Unable to get the window surface.", SDL_FUNCTION);
    }

    // Get the N3DS internal framebuffer and its size
    framebuffer = gfxGetFramebuffer(drv_data->screen, GFX_डावा, &width, &height);
    bufsize = width * height * 4;

    जर (SDL_BYTESPERPIXEL(surface->format) == 2)
        CopyFramebuffertoN3DS_16(framebuffer, (Dimensions){ width, height },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    अन्यथा जर (SDL_BYTESPERPIXEL(surface->format) == 3)
        CopyFramebuffertoN3DS_24(framebuffer, (Dimensions){ width, height },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    अन्यथा
        CopyFramebuffertoN3DS_32(framebuffer, (Dimensions){ width, height },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    FlushN3DSBuffer(framebuffer, bufsize, drv_data->screen);

    परत true;
}

स्थिर शून्य CopyFramebuffertoN3DS_16(u16 *dest, स्थिरांक Dimensions dest_dim, स्थिरांक u16 *source, स्थिरांक Dimensions source_dim)
{
    पूर्णांक rows = SDL_min(dest_dim.width, source_dim.height);
    पूर्णांक cols = SDL_min(dest_dim.height, source_dim.width);
    साठी (पूर्णांक y = 0; y < rows; ++y) {
        साठी (पूर्णांक x = 0; x < cols; ++x) {
            स्थिरांक u16 *s = source + GetSourceOffset(x, y, source_dim.width);
            u16 *d = dest + GetDestOffset(x, y, dest_dim.width);
            *d = *s;
        }
    }
}

स्थिर शून्य CopyFramebuffertoN3DS_24(u8 *dest, स्थिरांक Dimensions dest_dim, स्थिरांक u8 *source, स्थिरांक Dimensions source_dim)
{
    पूर्णांक rows = SDL_min(dest_dim.width, source_dim.height);
    पूर्णांक cols = SDL_min(dest_dim.height, source_dim.width);
    साठी (पूर्णांक y = 0; y < rows; ++y) {
        साठी (पूर्णांक x = 0; x < cols; ++x) {
            स्थिरांक u8 *s = source + GetSourceOffset(x, y, source_dim.width) * 3;
            u8 *d = dest + GetDestOffset(x, y, dest_dim.width) * 3;
            d[0] = s[0];
            d[1] = s[1];
            d[2] = s[2];
        }
    }
}

स्थिर शून्य CopyFramebuffertoN3DS_32(u32 *dest, स्थिरांक Dimensions dest_dim, स्थिरांक u32 *source, स्थिरांक Dimensions source_dim)
{
    पूर्णांक rows = SDL_min(dest_dim.width, source_dim.height);
    पूर्णांक cols = SDL_min(dest_dim.height, source_dim.width);
    साठी (पूर्णांक y = 0; y < rows; ++y) {
        साठी (पूर्णांक x = 0; x < cols; ++x) {
            स्थिरांक u32 *s = source + GetSourceOffset(x, y, source_dim.width);
            u32 *d = dest + GetDestOffset(x, y, dest_dim.width);
            *d = *s;
        }
    }
}

स्थिर पूर्णांक GetDestOffset(पूर्णांक x, पूर्णांक y, पूर्णांक dest_width)
{
    परत dest_width - y - 1 + dest_width * x;
}

स्थिर पूर्णांक GetSourceOffset(पूर्णांक x, पूर्णांक y, पूर्णांक source_width)
{
    परत x + y * source_width;
}

स्थिर शून्य FlushN3DSBuffer(स्थिरांक शून्य *buffer, u32 bufsize, gfxScreen_t screen)
{
    GSPGPU_FlushDataCache(buffer, bufsize);
    gfxScreenSwapBuffers(screen, false);
}

शून्य SDL_N3DS_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_ClearProperty(SDL_GetWindowProperties(window), N3DS_SURFACE);
}

#endif // SDL_VIDEO_DRIVER_N3DS
