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

#ifndef SDL_surface_c_h_
#define SDL_surface_c_h_

// Useful functions and variables from SDL_surface.c

#ଅନ୍ତର୍ଭାଵ "SDL_blit.h"

// Surface internal flags
ପ୍ରକାରବ୍ୟାଖ୍ୟା Uint32 SDL_SurfaceDataFlags;

#define SDL_INTERNAL_SURFACE_DONTFREE   0x00000001u /**< Surface is referenced internally */
#define SDL_INTERNAL_SURFACE_ଗଦା      0x00000002u /**< Surface is allocated on the stack */
#define SDL_INTERNAL_SURFACE_RLEACCEL   0x00000004u /**< Surface is RLE encoded */

// Surface internal data definition
ସଂରଚନା SDL_Surface
{
    // Public API definition
    SDL_SurfaceFlags flags;     /**< The flags of the surface, read-only */
    SDL_PixelFormat format;     /**< The format of the surface, read-only */
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା w;                      /**< The width of the surface, read-only. */
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା h;                      /**< The height of the surface, read-only. */
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା pitch;                  /**< The distance in bytes between rows of pixels, read-only */
    ଶୂନ୍ୟ *pixels;               /**< A pointer to the pixels of the surface, the pixels are writeable if non-NULL */

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା refcount;               /**< Application reference count, used when freeing surface */

    ଶୂନ୍ୟ *reserved;             /**< Reserved for internal use */

    // Private API definition

    /** flags for this surface */
    SDL_SurfaceDataFlags internal_flags;

    /** properties for this surface */
    SDL_PropertiesID props;

    /** detailed format for this surface */
    ଅଚଳ SDL_PixelFormatDetails *fmt;

    /** Pixel colorspace */
    SDL_Colorspace colorspace;

    /** palette for indexed surfaces */
    SDL_Palette *palette;

    /** Alternate representation of images */
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଅଙ୍କ_images;
    SDL_Surface **images;

    /** information needed for surfaces requiring locks */
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା locked;

    /** clipping information */
    SDL_Rect clip_rect;

    /** info for fast blit mapping to other surfaces */
    SDL_BlitMap map;

    /** Original pixels when RLE is enabled */
    ଶୂନ୍ୟ *saved_pixels;
};

// Surface functions
ବାହ୍ୟ bool SDL_SurfaceValid(SDL_Surface *surface);
ବାହ୍ୟ ଶୂନ୍ୟ SDL_UpdateSurfaceLockFlag(SDL_Surface *surface);
ବାହ୍ୟ bool SDL_CalculateSurfaceSize(SDL_PixelFormat format, ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height, size_t *size, size_t *pitch, bool minimalPitch);
ବାହ୍ୟ ଦଶମିକ SDL_GetDefaultSDRWhitePoint(SDL_Colorspace colorspace);
ବାହ୍ୟ ଦଶମିକ SDL_GetSurfaceSDRWhitePoint(SDL_Surface *surface, SDL_Colorspace colorspace);
ବାହ୍ୟ ଦଶମିକ SDL_GetDefaultHDRHeadroom(SDL_Colorspace colorspace);
ବାହ୍ୟ ଦଶମିକ SDL_GetSurfaceHDRHeadroom(SDL_Surface *surface, SDL_Colorspace colorspace);
ବାହ୍ୟ SDL_Surface *SDL_CreateSurfaceZeroed(ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height, SDL_PixelFormat format);
ବାହ୍ୟ SDL_Surface *SDL_CreateSurfaceUninitialized(ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height, SDL_PixelFormat format);
ବାହ୍ୟ SDL_Surface *SDL_GetSurfaceImage(SDL_Surface *surface, ଦଶମିକ display_scale);
ବାହ୍ୟ SDL_Surface *SDL_ConvertSurfaceRect(SDL_Surface *surface, ଅଚଳ SDL_Rect *rect, SDL_PixelFormat format);
ବାହ୍ୟ bool SDL_IsBMP(SDL_IOStream *src);
ବାହ୍ୟ bool SDL_IsJPG(SDL_IOStream *src);
ବାହ୍ୟ bool SDL_IsPNG(SDL_IOStream *src);

#endif // SDL_surface_c_h_
