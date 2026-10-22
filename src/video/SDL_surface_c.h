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

#अगर_अघोषित SDL_surface_c_h_
#घोषणा SDL_surface_c_h_

// Useful functions and variables from SDL_surface.c

#समावेश "SDL_blit.h"

// Surface internal flags
प्रकार Uint32 SDL_Surface_तथ्य_Flags;

#घोषणा SDL_INTERNAL_SURFACE_DONTFREE   0x00000001u /**< Surface is referenced internally */
#घोषणा SDL_INTERNAL_SURFACE_ढेर      0x00000002u /**< Surface is allocated on the stack */
#घोषणा SDL_INTERNAL_SURFACE_RLEACCEL   0x00000004u /**< Surface is RLE encoded */

// Surface internal data definition
काष्ठा SDL_Surface
{
    // Public API definition
    SDL_SurfaceFlags flags;     /**< The flags of the surface, read-only */
    SDL_PixelFormat format;     /**< The format of the surface, read-only */
    पूर्णांक w;                      /**< The width of the surface, read-only. */
    पूर्णांक h;                      /**< The height of the surface, read-only. */
    पूर्णांक pitch;                  /**< The distance in bytes between rows of pixels, read-only */
    व्योम *pixels;               /**< A pointer to the pixels of the surface, the pixels are writeable if non-NULL */

    पूर्णांक refcount;               /**< Application reference count, used when freeing surface */

    व्योम *reserved;             /**< Reserved for internal use */

    // Private API definition

    /** flags for this surface */
    SDL_Surface_तथ्य_Flags internal_flags;

    /** properties for this surface */
    SDL_PropertiesID props;

    /** detailed format for this surface */
    स्थिर SDL_PixelFormatDetails *fmt;

    /** Pixel colorspace */
    SDL_Colorspace colorspace;

    /** palette for indexed surfaces */
    SDL_Palette *palette;

    /** Alternate representation of images */
    पूर्णांक अंक_images;
    SDL_Surface **images;

    /** information needed for surfaces requiring locks */
    पूर्णांक locked;

    /** clipping information */
    SDL_Rect clip_rect;

    /** info for fast blit mapping to other surfaces */
    SDL_BlitMap map;

    /** Original pixels when RLE is enabled */
    व्योम *saved_pixels;
};

// Surface functions
बाह्य bool SDL_SurfaceValid(SDL_Surface *surface);
बाह्य व्योम SDL_UpdateSurfaceLockFlag(SDL_Surface *surface);
बाह्य bool SDL_Calculate_Surface_आकार(SDL_PixelFormat format, पूर्णांक width, पूर्णांक height, माप_प्रकार *आकार, माप_प्रकार *pitch, bool minimalPitch);
बाह्य भग्न SDL_GetDefaultSDRWhitePoint(SDL_Colorspace colorspace);
बाह्य भग्न SDL_GetSurfaceSDRWhitePoint(SDL_Surface *surface, SDL_Colorspace colorspace);
बाह्य भग्न SDL_GetDefaultHDRHeadroom(SDL_Colorspace colorspace);
बाह्य भग्न SDL_GetSurfaceHDRHeadroom(SDL_Surface *surface, SDL_Colorspace colorspace);
बाह्य SDL_Surface *SDL_CreateSurfaceZeroed(पूर्णांक width, पूर्णांक height, SDL_PixelFormat format);
बाह्य SDL_Surface *SDL_CreateSurfaceUninitialized(पूर्णांक width, पूर्णांक height, SDL_PixelFormat format);
बाह्य SDL_Surface *SDL_GetSurfaceImage(SDL_Surface *surface, भग्न display_scale);
बाह्य SDL_Surface *SDL_ConvertSurfaceRect(SDL_Surface *surface, स्थिर SDL_Rect *rect, SDL_PixelFormat format);
बाह्य bool SDL_IsBMP(SDL_IOStream *src);
बाह्य bool SDL_IsJPG(SDL_IOStream *src);
बाह्य bool SDL_IsPNG(SDL_IOStream *src);

#पूर्ण_अगर // SDL_surface_c_h_
