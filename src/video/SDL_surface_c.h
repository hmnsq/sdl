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

#ifndef SDL_surface_c_h_
#define SDL_surface_c_h_

// Useful functions and variables from SDL_surface.c

#ಅನ್ತರ್ಭಾವ "SDL_blit.h"

// Surface internal flags
ಪ್ರಕಾರನಿರ್ದೇಶ Uint32 SDL_SurfaceDataFlags;

#define SDL_INTERNAL_SURFACE_DONTFREE   0x00000001u /**< Surface is referenced internally */
#define SDL_INTERNAL_SURFACE_ರಾಶಿ      0x00000002u /**< Surface is allocated on the stack */
#define SDL_INTERNAL_SURFACE_RLEACCEL   0x00000004u /**< Surface is RLE encoded */

// Surface internal data definition
ಸಂರಚನಾ SDL_Surface
{
    // Public API definition
    SDL_SurfaceFlags flags;     /**< The flags of the surface, read-only */
    SDL_PixelFormat format;     /**< The format of the surface, read-only */
    ಪೂರ್ಣಾಙ್ಕ w;                      /**< The width of the surface, read-only. */
    ಪೂರ್ಣಾಙ್ಕ h;                      /**< The height of the surface, read-only. */
    ಪೂರ್ಣಾಙ್ಕ pitch;                  /**< The distance in bytes between rows of pixels, read-only */
    ಶೂನ್ಯ *pixels;               /**< A pointer to the pixels of the surface, the pixels are writeable if non-NULL */

    ಪೂರ್ಣಾಙ್ಕ refcount;               /**< Application reference count, used when freeing surface */

    ಶೂನ್ಯ *reserved;             /**< Reserved for internal use */

    // Private API definition

    /** flags for this surface */
    SDL_SurfaceDataFlags internal_flags;

    /** properties for this surface */
    SDL_PropertiesID props;

    /** detailed format for this surface */
    ಧ್ರುವ SDL_PixelFormatDetails *fmt;

    /** Pixel colorspace */
    SDL_Colorspace colorspace;

    /** palette for indexed surfaces */
    SDL_Palette *palette;

    /** Alternate representation of images */
    ಪೂರ್ಣಾಙ್ಕ ಅಂಕೆ_images;
    SDL_Surface **images;

    /** information needed for surfaces requiring locks */
    ಪೂರ್ಣಾಙ್ಕ locked;

    /** clipping information */
    SDL_Rect clip_rect;

    /** info for fast blit mapping to other surfaces */
    SDL_BlitMap map;

    /** Original pixels when RLE is enabled */
    ಶೂನ್ಯ *saved_pixels;
};

// Surface functions
ಬಾಹ್ಯ bool SDL_SurfaceValid(SDL_Surface *surface);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_UpdateSurfaceLockFlag(SDL_Surface *surface);
ಬಾಹ್ಯ bool SDL_CalculateSurfaceSize(SDL_PixelFormat format, ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, size_t *size, size_t *pitch, bool minimalPitch);
ಬಾಹ್ಯ ಭಿನ್ನ SDL_GetDefaultSDRWhitePoint(SDL_Colorspace colorspace);
ಬಾಹ್ಯ ಭಿನ್ನ SDL_GetSurfaceSDRWhitePoint(SDL_Surface *surface, SDL_Colorspace colorspace);
ಬಾಹ್ಯ ಭಿನ್ನ SDL_GetDefaultHDRHeadroom(SDL_Colorspace colorspace);
ಬಾಹ್ಯ ಭಿನ್ನ SDL_GetSurfaceHDRHeadroom(SDL_Surface *surface, SDL_Colorspace colorspace);
ಬಾಹ್ಯ SDL_Surface *SDL_CreateSurfaceZeroed(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, SDL_PixelFormat format);
ಬಾಹ್ಯ SDL_Surface *SDL_CreateSurfaceUninitialized(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, SDL_PixelFormat format);
ಬಾಹ್ಯ SDL_Surface *SDL_GetSurfaceImage(SDL_Surface *surface, ಭಿನ್ನ display_scale);
ಬಾಹ್ಯ SDL_Surface *SDL_ConvertSurfaceRect(SDL_Surface *surface, ಧ್ರುವ SDL_Rect *rect, SDL_PixelFormat format);
ಬಾಹ್ಯ bool SDL_IsBMP(SDL_IOStream *src);
ಬಾಹ್ಯ bool SDL_IsJPG(SDL_IOStream *src);
ಬಾಹ್ಯ bool SDL_IsPNG(SDL_IOStream *src);

#endif // SDL_surface_c_h_
