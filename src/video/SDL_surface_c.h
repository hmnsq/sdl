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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_surface_c_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_surface_c_h_

// Useful functions and variables from SDL_surface.c

#ಅನ್ತರ್ಭಾವ "SDL_blit.h"

// Surface internal flags
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Uint32 SDL_Surface_ದತ್ತಾಂಶ_Flags;

#ವ್ಯಾಖ್ಯಾನಿಸು SDL_ಆಂತರಿಕ_SURFACE_DONTFREE   0x00000001u /**< Surface is referenced internally */
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_ಆಂತರಿಕ_SURFACE_ರಾಶಿ      0x00000002u /**< Surface is allocated on the stack */
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_ಆಂತರಿಕ_SURFACE_RLEACCEL   0x00000004u /**< Surface is RLE encoded */

// Surface internal data definition
ರಚನೆ SDL_Surface
{
    // Public API definition
    SDL_SurfaceFlags flags;     /**< The flags of the surface, read-only */
    SDL_PixelFormat format;     /**< The format of the surface, read-only */
    ಪೂರ್ಣಾಂಕ w;                      /**< The width of the surface, read-only. */
    ಪೂರ್ಣಾಂಕ h;                      /**< The height of the surface, read-only. */
    ಪೂರ್ಣಾಂಕ pitch;                  /**< The distance in bytes between rows of pixels, read-only */
    ಶೂನ್ಯ *pixels;               /**< A pointer to the pixels of the surface, the pixels are writeable if non-NULL */

    ಪೂರ್ಣಾಂಕ refcount;               /**< Application reference count, used when freeing surface */

    ಶೂನ್ಯ *reserved;             /**< Reserved for internal use */

    // Private API definition

    /** flags for this surface */
    SDL_Surface_ದತ್ತಾಂಶ_Flags ಆಂತರಿಕ_flags;

    /** properties for this surface */
    SDL_PropertiesID props;

    /** detailed format for this surface */
    ಸ್ಥಿರಾಂಕ SDL_PixelFormatDetails *fmt;

    /** Pixel colorspace */
    SDL_Colorspace colorspace;

    /** palette for indexed surfaces */
    SDL_Palette *palette;

    /** Alternate representation of images */
    ಪೂರ್ಣಾಂಕ ಅಂಕೆ_images;
    SDL_Surface **images;

    /** information needed for surfaces requiring locks */
    ಪೂರ್ಣಾಂಕ locked;

    /** clipping information */
    SDL_Rect clip_rect;

    /** info for fast blit mapping to other surfaces */
    SDL_BlitMap map;

    /** Original pixels when RLE is enabled */
    ಶೂನ್ಯ *saved_pixels;
};

// Surface functions
ಬಾಹ್ಯ bool SDL_SurfaceValid(SDL_Surface *surface);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_Update_Surface_ಬೀಗ_Flag(SDL_Surface *surface);
ಬಾಹ್ಯ bool SDL_Calculate_Surface_ಗಾತ್ರ(SDL_PixelFormat format, ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, size_t *ಗಾತ್ರ_2, size_t *pitch, bool ಕನಿಷ್ಠತಮ_Pitch);
ಬಾಹ್ಯ ದಶಮಾಂಶ SDL_Get_Default_SDRWhite_ಬಿಂದು(SDL_Colorspace colorspace);
ಬಾಹ್ಯ ದಶಮಾಂಶ SDL_Get_Surface_SDRWhite_ಬಿಂದು(SDL_Surface *surface, SDL_Colorspace colorspace);
ಬಾಹ್ಯ ದಶಮಾಂಶ SDL_GetDefaultHDRHeadroom(SDL_Colorspace colorspace);
ಬಾಹ್ಯ ದಶಮಾಂಶ SDL_GetSurfaceHDRHeadroom(SDL_Surface *surface, SDL_Colorspace colorspace);
ಬಾಹ್ಯ SDL_Surface *SDL_CreateSurfaceZeroed(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, SDL_PixelFormat format);
ಬಾಹ್ಯ SDL_Surface *SDL_CreateSurfaceUninitialized(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, SDL_PixelFormat format);
ಬಾಹ್ಯ SDL_Surface *SDL_GetSurfaceImage(SDL_Surface *surface, ದಶಮಾಂಶ display_scale);
ಬಾಹ್ಯ SDL_Surface *SDL_ConvertSurfaceRect(SDL_Surface *surface, ಸ್ಥಿರಾಂಕ SDL_Rect *rect, SDL_PixelFormat format);
ಬಾಹ್ಯ bool SDL_IsBMP(SDL_IOStream *src);
ಬಾಹ್ಯ bool SDL_IsJPG(SDL_IOStream *src);
ಬಾಹ್ಯ bool SDL_IsPNG(SDL_IOStream *src);

#ಆದರೆ_ಅಂತ್ಯ // SDL_surface_c_h_
