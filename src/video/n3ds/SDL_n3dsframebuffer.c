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
#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_N3DS

#समावेश "../SDL_sysvideo.h"
#समावेश "../../SDL_properties_c.h"
#समावेश "SDL_n3dsframebuffer_c.h"
#समावेश "SDL_n3dsvideo.h"

#घोषणा N3DS_SURFACE "SDL.internal.window.surface"

प्रकार काष्ठा
{
    पूर्णांक width, height;
} Dimensions;

अटल व्योम CopyFramebuffertoN3DS_16(u16 *dest, स्थिर Dimensions dest_dim, स्थिर u16 *source, स्थिर Dimensions source_dim);
अटल व्योम CopyFramebuffertoN3DS_24(u8  *dest, स्थिर Dimensions dest_dim, स्थिर u8  *source, स्थिर Dimensions source_dim);
अटल व्योम CopyFramebuffertoN3DS_32(u32 *dest, स्थिर Dimensions dest_dim, स्थिर u32 *source, स्थिर Dimensions source_dim);
अटल पूर्णांक GetDestOffset(पूर्णांक x, पूर्णांक y, पूर्णांक dest_width);
अटल पूर्णांक GetSourceOffset(पूर्णांक x, पूर्णांक y, पूर्णांक source_width);
अटल व्योम FlushN3DSBuffer(स्थिर व्योम *बफर_2, u32 bufsize, gfxScreen_t screen);


bool SDL_N3DS_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, व्योम **pixels, पूर्णांक *pitch)
{
    SDL_Surface *framebuffer;
    स्थिर SDL_DisplayMode *mode;
    पूर्णांक w, h;

    SDL_N3DS_DestroyWindowFramebuffer(_this, window);

    mode = SDL_GetCurrentDisplayMode(SDL_GetDisplayForWindow(window));
    SDL_Get_Window_आकार_In_Pixels(window, &w, &h);
    framebuffer = SDL_CreateSurfaceZeroed(w, h, mode->format);

    अगर (!framebuffer) {
        वापस false;
    }

    SDL_SetSurfaceProperty(SDL_GetWindowProperties(window), N3DS_SURFACE, framebuffer);
    *format = mode->format;
    *pixels = framebuffer->pixels;
    *pitch = framebuffer->pitch;
    वापस true;
}

bool SDL_N3DS_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, स्थिर SDL_Rect *rects, पूर्णांक numrects)
{
    SDL_Window_तथ्य *drv_तथ्य = window->internal;
    SDL_Surface *surface;
    u16 width, height;
    व्योम *framebuffer;
    u32 bufsize;

    surface = (SDL_Surface *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), N3DS_SURFACE, शून्य);
    अगर (!surface) {
        वापस SDL_SetError("%s: Unable to get the window surface.", SDL_FUNCTION);
    }

    // Get the N3DS internal framebuffer and its size
    framebuffer = gfxGetFramebuffer(drv_तथ्य->screen, GFX_बायाँ, &width, &height);
    bufsize = width * height * 4;

    अगर (SDL_BYTESPERPIXEL(surface->format) == 2)
        CopyFramebuffertoN3DS_16(framebuffer, (Dimensions){ width, height },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    अन्यथा अगर (SDL_BYTESPERPIXEL(surface->format) == 3)
        CopyFramebuffertoN3DS_24(framebuffer, (Dimensions){ width, height },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    अन्यथा
        CopyFramebuffertoN3DS_32(framebuffer, (Dimensions){ width, height },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    FlushN3DSBuffer(framebuffer, bufsize, drv_तथ्य->screen);

    वापस true;
}

अटल व्योम CopyFramebuffertoN3DS_16(u16 *dest, स्थिर Dimensions dest_dim, स्थिर u16 *source, स्थिर Dimensions source_dim)
{
    पूर्णांक rows = SDL_min(dest_dim.width, source_dim.height);
    पूर्णांक cols = SDL_min(dest_dim.height, source_dim.width);
    क्रम (पूर्णांक y = 0; y < rows; ++y) {
        क्रम (पूर्णांक x = 0; x < cols; ++x) {
            स्थिर u16 *s = source + GetSourceOffset(x, y, source_dim.width);
            u16 *d = dest + GetDestOffset(x, y, dest_dim.width);
            *d = *s;
        }
    }
}

अटल व्योम CopyFramebuffertoN3DS_24(u8 *dest, स्थिर Dimensions dest_dim, स्थिर u8 *source, स्थिर Dimensions source_dim)
{
    पूर्णांक rows = SDL_min(dest_dim.width, source_dim.height);
    पूर्णांक cols = SDL_min(dest_dim.height, source_dim.width);
    क्रम (पूर्णांक y = 0; y < rows; ++y) {
        क्रम (पूर्णांक x = 0; x < cols; ++x) {
            स्थिर u8 *s = source + GetSourceOffset(x, y, source_dim.width) * 3;
            u8 *d = dest + GetDestOffset(x, y, dest_dim.width) * 3;
            d[0] = s[0];
            d[1] = s[1];
            d[2] = s[2];
        }
    }
}

अटल व्योम CopyFramebuffertoN3DS_32(u32 *dest, स्थिर Dimensions dest_dim, स्थिर u32 *source, स्थिर Dimensions source_dim)
{
    पूर्णांक rows = SDL_min(dest_dim.width, source_dim.height);
    पूर्णांक cols = SDL_min(dest_dim.height, source_dim.width);
    क्रम (पूर्णांक y = 0; y < rows; ++y) {
        क्रम (पूर्णांक x = 0; x < cols; ++x) {
            स्थिर u32 *s = source + GetSourceOffset(x, y, source_dim.width);
            u32 *d = dest + GetDestOffset(x, y, dest_dim.width);
            *d = *s;
        }
    }
}

अटल पूर्णांक GetDestOffset(पूर्णांक x, पूर्णांक y, पूर्णांक dest_width)
{
    वापस dest_width - y - 1 + dest_width * x;
}

अटल पूर्णांक GetSourceOffset(पूर्णांक x, पूर्णांक y, पूर्णांक source_width)
{
    वापस x + y * source_width;
}

अटल व्योम FlushN3DSBuffer(स्थिर व्योम *बफर_2, u32 bufsize, gfxScreen_t screen)
{
    GSPGPU_Flush_तथ्य_Cache(बफर_2, bufsize);
    gfxScreenSwapBuffers(screen, false);
}

व्योम SDL_N3DS_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_ClearProperty(SDL_GetWindowProperties(window), N3DS_SURFACE);
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_N3DS
