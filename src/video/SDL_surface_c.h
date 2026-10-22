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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_surface_c_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_surface_c_h_

// Useful functions and variables from SDL_surface.c

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_blit.h"

// Surface internal flags
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Uint32 SDL_Surface_ਅੰਕੜੇ_Flags;

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_ਅੰਦਰੂਨੀ_SURFACE_DONTFREE   0x00000001u /**< Surface is referenced internally */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_ਅੰਦਰੂਨੀ_SURFACE_ਢੇਰ      0x00000002u /**< Surface is allocated on the stack */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_ਅੰਦਰੂਨੀ_SURFACE_RLEACCEL   0x00000004u /**< Surface is RLE encoded */

// Surface internal data definition
ਬਣਤਰ SDL_Surface
{
    // Public API definition
    SDL_SurfaceFlags flags;     /**< The flags of the surface, read-only */
    SDL_PixelFormat format;     /**< The format of the surface, read-only */
    ਪੂਰਨ w;                      /**< The width of the surface, read-only. */
    ਪੂਰਨ h;                      /**< The height of the surface, read-only. */
    ਪੂਰਨ pitch;                  /**< The distance in bytes between rows of pixels, read-only */
    ਖਾਲੀ *pixels;               /**< A pointer to the pixels of the surface, the pixels are writeable if non-NULL */

    ਪੂਰਨ refcount;               /**< Application reference count, used when freeing surface */

    ਖਾਲੀ *reserved;             /**< Reserved for internal use */

    // Private API definition

    /** flags for this surface */
    SDL_Surface_ਅੰਕੜੇ_Flags ਅੰਦਰੂਨੀ_flags;

    /** properties for this surface */
    SDL_PropertiesID props;

    /** detailed format for this surface */
    ਅਚਲ SDL_PixelFormatDetails *fmt;

    /** Pixel colorspace */
    SDL_Colorspace colorspace;

    /** palette for indexed surfaces */
    SDL_Palette *palette;

    /** Alternate representation of images */
    ਪੂਰਨ ਅੰਕ_images;
    SDL_Surface **images;

    /** information needed for surfaces requiring locks */
    ਪੂਰਨ locked;

    /** clipping information */
    SDL_Rect clip_rect;

    /** info for fast blit mapping to other surfaces */
    SDL_BlitMap map;

    /** Original pixels when RLE is enabled */
    ਖਾਲੀ *saved_pixels;
};

// Surface functions
ਬਾਹਰੀ bool SDL_SurfaceValid(SDL_Surface *surface);
ਬਾਹਰੀ ਖਾਲੀ SDL_Update_Surface_ਤਾਲਾ_Flag(SDL_Surface *surface);
ਬਾਹਰੀ bool SDL_Calculate_Surface_ਮਾਪ(SDL_PixelFormat format, ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, size_t *ਮਾਪ, size_t *pitch, bool ਨਿਊਨਤਮ_Pitch);
ਬਾਹਰੀ ਦਸ਼ਮਲਵ SDL_Get_Default_SDRWhite_ਬਿੰਦੂ(SDL_Colorspace colorspace);
ਬਾਹਰੀ ਦਸ਼ਮਲਵ SDL_Get_Surface_SDRWhite_ਬਿੰਦੂ(SDL_Surface *surface, SDL_Colorspace colorspace);
ਬਾਹਰੀ ਦਸ਼ਮਲਵ SDL_GetDefaultHDRHeadroom(SDL_Colorspace colorspace);
ਬਾਹਰੀ ਦਸ਼ਮਲਵ SDL_GetSurfaceHDRHeadroom(SDL_Surface *surface, SDL_Colorspace colorspace);
ਬਾਹਰੀ SDL_Surface *SDL_CreateSurfaceZeroed(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, SDL_PixelFormat format);
ਬਾਹਰੀ SDL_Surface *SDL_CreateSurfaceUninitialized(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, SDL_PixelFormat format);
ਬਾਹਰੀ SDL_Surface *SDL_GetSurfaceImage(SDL_Surface *surface, ਦਸ਼ਮਲਵ display_scale);
ਬਾਹਰੀ SDL_Surface *SDL_ConvertSurfaceRect(SDL_Surface *surface, ਅਚਲ SDL_Rect *rect, SDL_PixelFormat format);
ਬਾਹਰੀ bool SDL_IsBMP(SDL_IOStream *src);
ਬਾਹਰੀ bool SDL_IsJPG(SDL_IOStream *src);
ਬਾਹਰੀ bool SDL_IsPNG(SDL_IOStream *src);

#ਜੇ_ਅੰਤ // SDL_surface_c_h_
