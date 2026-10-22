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
#ضمن "SDL_internal.h"

#ifndef SDL_surface_c_h_
#define SDL_surface_c_h_

// Useful functions and variables from SDL_surface.c

#ضمن "SDL_blit.h"

// Surface internal flags
تعريفنوع Uint32 SDL_SurfaceDataFlags;

#define SDL_INTERNAL_SURFACE_DONTFREE   0x00000001u /**< Surface is referenced internally */
#define SDL_INTERNAL_SURFACE_کەڵەکە      0x00000002u /**< Surface is allocated on the stack */
#define SDL_INTERNAL_SURFACE_RLEACCEL   0x00000004u /**< Surface is RLE encoded */

// Surface internal data definition
بنية SDL_Surface
{
    // Public API definition
    SDL_SurfaceFlags flags;     /**< The flags of the surface, read-only */
    SDL_PixelFormat format;     /**< The format of the surface, read-only */
    صحيح w;                      /**< The width of the surface, read-only. */
    صحيح h;                      /**< The height of the surface, read-only. */
    صحيح pitch;                  /**< The distance in bytes between rows of pixels, read-only */
    فراغ *pixels;               /**< A pointer to the pixels of the surface, the pixels are writeable if non-NULL */

    صحيح refcount;               /**< Application reference count, used when freeing surface */

    فراغ *reserved;             /**< Reserved for internal use */

    // Private API definition

    /** flags for this surface */
    SDL_SurfaceDataFlags internal_flags;

    /** properties for this surface */
    SDL_PropertiesID props;

    /** detailed format for this surface */
    ثابت SDL_PixelFormatDetails *fmt;

    /** Pixel colorspace */
    SDL_Colorspace colorspace;

    /** palette for indexed surfaces */
    SDL_Palette *palette;

    /** Alternate representation of images */
    صحيح ژمارە_images;
    SDL_Surface **images;

    /** information needed for surfaces requiring locks */
    صحيح locked;

    /** clipping information */
    SDL_Rect clip_rect;

    /** info for fast blit mapping to other surfaces */
    SDL_BlitMap map;

    /** Original pixels when RLE is enabled */
    فراغ *saved_pixels;
};

// Surface functions
خارجي bool SDL_SurfaceValid(SDL_Surface *surface);
خارجي فراغ SDL_UpdateSurfaceLockFlag(SDL_Surface *surface);
خارجي bool SDL_CalculateSurfaceSize(SDL_PixelFormat format, صحيح width, صحيح height, size_t *size, size_t *pitch, bool minimalPitch);
خارجي عائم SDL_GetDefaultSDRWhitePoint(SDL_Colorspace colorspace);
خارجي عائم SDL_GetSurfaceSDRWhitePoint(SDL_Surface *surface, SDL_Colorspace colorspace);
خارجي عائم SDL_GetDefaultHDRHeadroom(SDL_Colorspace colorspace);
خارجي عائم SDL_GetSurfaceHDRHeadroom(SDL_Surface *surface, SDL_Colorspace colorspace);
خارجي SDL_Surface *SDL_CreateSurfaceZeroed(صحيح width, صحيح height, SDL_PixelFormat format);
خارجي SDL_Surface *SDL_CreateSurfaceUninitialized(صحيح width, صحيح height, SDL_PixelFormat format);
خارجي SDL_Surface *SDL_GetSurfaceImage(SDL_Surface *surface, عائم display_scale);
خارجي SDL_Surface *SDL_ConvertSurfaceRect(SDL_Surface *surface, ثابت SDL_Rect *rect, SDL_PixelFormat format);
خارجي bool SDL_IsBMP(SDL_IOStream *src);
خارجي bool SDL_IsJPG(SDL_IOStream *src);
خارجي bool SDL_IsPNG(SDL_IOStream *src);

#endif // SDL_surface_c_h_
