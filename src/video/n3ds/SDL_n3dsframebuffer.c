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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_N3DS

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "../../SDL_properties_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_n3dsframebuffer_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_n3dsvideo.h"

#ವ್ಯಾಖ್ಯಾನಿಸು N3DS_SURFACE "SDL.internal.window.surface"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
    ಪೂರ್ಣಾಂಕ ಅಗಲ, ಎತ್ತರ;
} Dimensions;

ಸ್ಥಿರ ಶೂನ್ಯ CopyFramebuffertoN3DS_16(u16 *dest, ಸ್ಥಿರಾಂಕ Dimensions dest_dim, ಸ್ಥಿರಾಂಕ u16 *ಮೂಲ, ಸ್ಥಿರಾಂಕ Dimensions ಮೂಲ_dim);
ಸ್ಥಿರ ಶೂನ್ಯ CopyFramebuffertoN3DS_24(u8  *dest, ಸ್ಥಿರಾಂಕ Dimensions dest_dim, ಸ್ಥಿರಾಂಕ u8  *ಮೂಲ, ಸ್ಥಿರಾಂಕ Dimensions ಮೂಲ_dim);
ಸ್ಥಿರ ಶೂನ್ಯ CopyFramebuffertoN3DS_32(u32 *dest, ಸ್ಥಿರಾಂಕ Dimensions dest_dim, ಸ್ಥಿರಾಂಕ u32 *ಮೂಲ, ಸ್ಥಿರಾಂಕ Dimensions ಮೂಲ_dim);
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ Get_Dest_ಸ್ಥಾನಾಂತರ(ಪೂರ್ಣಾಂಕ x, ಪೂರ್ಣಾಂಕ y, ಪೂರ್ಣಾಂಕ dest_ಅಗಲ);
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ Get_ಮೂಲ_ಸ್ಥಾನಾಂತರ(ಪೂರ್ಣಾಂಕ x, ಪೂರ್ಣಾಂಕ y, ಪೂರ್ಣಾಂಕ ಮೂಲ_ಅಗಲ);
ಸ್ಥಿರ ಶೂನ್ಯ FlushN3DSBuffer(ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *ಬಫರ್_2, u32 bufsize, gfxScreen_t screen);


bool SDL_N3_DS_Create_ಕಿಟಕಿ_Framebuffer(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PixelFormat *format, ಶೂನ್ಯ **pixels, ಪೂರ್ಣಾಂಕ *pitch)
{
    SDL_Surface *framebuffer;
    ಸ್ಥಿರಾಂಕ SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ;
    ಪೂರ್ಣಾಂಕ w, h;

    SDL_N3_DS_Destroy_ಕಿಟಕಿ_Framebuffer(_this, ಕಿಟಕಿ);

    ಬಹುಲಕ = SDL_Get_Current_Display_ಬಹುಲಕ(SDL_Get_Display_For_ಕಿಟಕಿ(ಕಿಟಕಿ));
    SDL_Get_ಕಿಟಕಿ_ಗಾತ್ರ_ಒಳ_Pixels(ಕಿಟಕಿ, &w, &h);
    framebuffer = SDL_CreateSurfaceZeroed(w, h, ಬಹುಲಕ->format);

    ಆದರೆ (!framebuffer) {
        ಹಿಂತಿರುಗಿ false;
    }

    SDL_ಗಣ_Surface_Property(SDL_Get_ಕಿಟಕಿ_Properties(ಕಿಟಕಿ), N3DS_SURFACE, framebuffer);
    *format = ಬಹುಲಕ->format;
    *pixels = framebuffer->pixels;
    *pitch = framebuffer->pitch;
    ಹಿಂತಿರುಗಿ true;
}

bool SDL_N3_DS_Update_ಕಿಟಕಿ_Framebuffer(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಸ್ಥಿರಾಂಕ SDL_Rect *rects, ಪೂರ್ಣಾಂಕ numrects)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *drv_ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    SDL_Surface *surface;
    u16 ಅಗಲ, ಎತ್ತರ;
    ಶೂನ್ಯ *framebuffer;
    u32 bufsize;

    surface = (SDL_Surface *)SDL_Get_ಸೂಚಕ_Property(SDL_Get_ಕಿಟಕಿ_Properties(ಕಿಟಕಿ), N3DS_SURFACE, ಖಾಲಿ);
    ಆದರೆ (!surface) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("%s: Unable to get the window surface.", SDL_FUNCTION);
    }

    // Get the N3DS internal framebuffer and its size
    framebuffer = gfxGetFramebuffer(drv_ದತ್ತಾಂಶ->screen, GFX_ಎಡ, &ಅಗಲ, &ಎತ್ತರ);
    bufsize = ಅಗಲ * ಎತ್ತರ * 4;

    ಆದರೆ (SDL_BYTESPERPIXEL(surface->format) == 2)
        CopyFramebuffertoN3DS_16(framebuffer, (Dimensions){ ಅಗಲ, ಎತ್ತರ },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_BYTESPERPIXEL(surface->format) == 3)
        CopyFramebuffertoN3DS_24(framebuffer, (Dimensions){ ಅಗಲ, ಎತ್ತರ },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    ಇಲ್ಲದಿದ್ದರೆ
        CopyFramebuffertoN3DS_32(framebuffer, (Dimensions){ ಅಗಲ, ಎತ್ತರ },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    FlushN3DSBuffer(framebuffer, bufsize, drv_ದತ್ತಾಂಶ->screen);

    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ ಶೂನ್ಯ CopyFramebuffertoN3DS_16(u16 *dest, ಸ್ಥಿರಾಂಕ Dimensions dest_dim, ಸ್ಥಿರಾಂಕ u16 *ಮೂಲ, ಸ್ಥಿರಾಂಕ Dimensions ಮೂಲ_dim)
{
    ಪೂರ್ಣಾಂಕ ಅಡ್ಡಸಾಲುಗಳು = SDL_min(dest_dim.ಅಗಲ, ಮೂಲ_dim.ಎತ್ತರ);
    ಪೂರ್ಣಾಂಕ ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ = SDL_min(dest_dim.ಎತ್ತರ, ಮೂಲ_dim.ಅಗಲ);
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ y = 0; y < ಅಡ್ಡಸಾಲುಗಳು; ++y) {
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ x = 0; x < ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ; ++x) {
            ಸ್ಥಿರಾಂಕ u16 *s = ಮೂಲ + Get_ಮೂಲ_ಸ್ಥಾನಾಂತರ(x, y, ಮೂಲ_dim.ಅಗಲ);
            u16 *d = dest + Get_Dest_ಸ್ಥಾನಾಂತರ(x, y, dest_dim.ಅಗಲ);
            *d = *s;
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ CopyFramebuffertoN3DS_24(u8 *dest, ಸ್ಥಿರಾಂಕ Dimensions dest_dim, ಸ್ಥಿರಾಂಕ u8 *ಮೂಲ, ಸ್ಥಿರಾಂಕ Dimensions ಮೂಲ_dim)
{
    ಪೂರ್ಣಾಂಕ ಅಡ್ಡಸಾಲುಗಳು = SDL_min(dest_dim.ಅಗಲ, ಮೂಲ_dim.ಎತ್ತರ);
    ಪೂರ್ಣಾಂಕ ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ = SDL_min(dest_dim.ಎತ್ತರ, ಮೂಲ_dim.ಅಗಲ);
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ y = 0; y < ಅಡ್ಡಸಾಲುಗಳು; ++y) {
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ x = 0; x < ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ; ++x) {
            ಸ್ಥಿರಾಂಕ u8 *s = ಮೂಲ + Get_ಮೂಲ_ಸ್ಥಾನಾಂತರ(x, y, ಮೂಲ_dim.ಅಗಲ) * 3;
            u8 *d = dest + Get_Dest_ಸ್ಥಾನಾಂತರ(x, y, dest_dim.ಅಗಲ) * 3;
            d[0] = s[0];
            d[1] = s[1];
            d[2] = s[2];
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ CopyFramebuffertoN3DS_32(u32 *dest, ಸ್ಥಿರಾಂಕ Dimensions dest_dim, ಸ್ಥಿರಾಂಕ u32 *ಮೂಲ, ಸ್ಥಿರಾಂಕ Dimensions ಮೂಲ_dim)
{
    ಪೂರ್ಣಾಂಕ ಅಡ್ಡಸಾಲುಗಳು = SDL_min(dest_dim.ಅಗಲ, ಮೂಲ_dim.ಎತ್ತರ);
    ಪೂರ್ಣಾಂಕ ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ = SDL_min(dest_dim.ಎತ್ತರ, ಮೂಲ_dim.ಅಗಲ);
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ y = 0; y < ಅಡ್ಡಸಾಲುಗಳು; ++y) {
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ x = 0; x < ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ; ++x) {
            ಸ್ಥಿರಾಂಕ u32 *s = ಮೂಲ + Get_ಮೂಲ_ಸ್ಥಾನಾಂತರ(x, y, ಮೂಲ_dim.ಅಗಲ);
            u32 *d = dest + Get_Dest_ಸ್ಥಾನಾಂತರ(x, y, dest_dim.ಅಗಲ);
            *d = *s;
        }
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ Get_Dest_ಸ್ಥಾನಾಂತರ(ಪೂರ್ಣಾಂಕ x, ಪೂರ್ಣಾಂಕ y, ಪೂರ್ಣಾಂಕ dest_ಅಗಲ)
{
    ಹಿಂತಿರುಗಿ dest_ಅಗಲ - y - 1 + dest_ಅಗಲ * x;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ Get_ಮೂಲ_ಸ್ಥಾನಾಂತರ(ಪೂರ್ಣಾಂಕ x, ಪೂರ್ಣಾಂಕ y, ಪೂರ್ಣಾಂಕ ಮೂಲ_ಅಗಲ)
{
    ಹಿಂತಿರುಗಿ x + y * ಮೂಲ_ಅಗಲ;
}

ಸ್ಥಿರ ಶೂನ್ಯ FlushN3DSBuffer(ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *ಬಫರ್_2, u32 bufsize, gfxScreen_t screen)
{
    GSPGPU_Flush_ದತ್ತಾಂಶ_Cache(ಬಫರ್_2, bufsize);
    gfx_Screen_ಅದಲುಬದಲು_Buffers(screen, false);
}

ಶೂನ್ಯ SDL_N3_DS_Destroy_ಕಿಟಕಿ_Framebuffer(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ClearProperty(SDL_Get_ಕಿಟಕಿ_Properties(ಕಿಟಕಿ), N3DS_SURFACE);
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_N3DS
