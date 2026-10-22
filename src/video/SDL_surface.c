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

#ಅನ್ತರ್ಭಾವ "SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_video_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_RLEaccel_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_pixels_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_rotate.h"
#ಅನ್ತರ್ಭಾವ "SDL_stb_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_yuv_c.h"
#ಅನ್ತರ್ಭಾವ "../render/SDL_sysrender.h"

#ಅನ್ತರ್ಭಾವ "SDL_surface_c.h"


// Check to make sure we can safely check multiplication of surface w and pitch and it won't overflow size_t
SDL_COMPILE_TIME_ASSERT(surface_size_assumptions,
                        ಪರಿಮಾಣ(ಪೂರ್ಣಾಙ್ಕ) == ಪರಿಮಾಣ(Sint32) && ಪರಿಮಾಣ(size_t) >= ಪರಿಮಾಣ(Sint32));

SDL_COMPILE_TIME_ASSERT(can_indicate_overflow, SDL_SIZE_MAX > SDL_MAX_SINT32);

// Magic!
ಸ್ಥಿರ ವರ್ಣ SDL_surface_magic;

// Public routines

bool SDL_SurfaceValid(SDL_Surface *surface)
{
    ಪ್ರತ್ಯಾಗಮ (surface && surface->reserved == &SDL_surface_magic);
}

ಶೂನ್ಯ SDL_UpdateSurfaceLockFlag(SDL_Surface *surface)
{
    // We need to mark the surface as needing unlock while locked
    ಯದಿ ((surface->flags & SDL_SURFACE_LOCKED) ||
        (surface->internal_flags & SDL_INTERNAL_SURFACE_RLEACCEL)) {
        surface->flags |= SDL_SURFACE_LOCK_NEEDED;
    } ಅನ್ಯಥಾ {
        surface->flags &= ~SDL_SURFACE_LOCK_NEEDED;
    }
}

/*
 * Calculate the pad-aligned scanline width of a surface.
 *
 * for FOURCC, use SDL_CalculateYUVSize()
 */
ಸ್ಥಿರ bool SDL_CalculateRGBSize(Uint32 format, size_t width, size_t height, size_t *size, size_t *pitch, bool minimal)
{
    ಯದಿ (SDL_BITSPERPIXEL(format) >= 8) {
        ಯದಿ (!SDL_size_mul_check_overflow(width, SDL_BYTESPERPIXEL(format), pitch)) {
            ಪ್ರತ್ಯಾಗಮ SDL_SetError("width * bpp would overflow");
        }
    } ಅನ್ಯಥಾ {
        ಯದಿ (!SDL_size_mul_check_overflow(width, SDL_BITSPERPIXEL(format), pitch)) {
            ಪ್ರತ್ಯಾಗಮ SDL_SetError("width * bpp would overflow");
        }
        ಯದಿ (!SDL_size_add_check_overflow(*pitch, 7, pitch)) {
            ಪ್ರತ್ಯಾಗಮ SDL_SetError("aligning pitch would overflow");
        }
        *pitch /= 8;
    }
    ಯದಿ (!minimal) {
        // 4-byte aligning for speed
        ಯದಿ (!SDL_size_add_check_overflow(*pitch, 3, pitch)) {
            ಪ್ರತ್ಯಾಗಮ SDL_SetError("aligning pitch would overflow");
        }
        *pitch &= ~3;
    }

    ಯದಿ (!SDL_size_mul_check_overflow(height, *pitch, size)) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("height * pitch would overflow");
    }

    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_CalculateSurfaceSize(SDL_PixelFormat format, ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, size_t *size, size_t *pitch, bool minimalPitch)
{
    size_t p = 0, sz = 0;

    ಯದಿ (size) {
        *size = 0;
    }

    ಯದಿ (pitch) {
        *pitch = 0;
    }

    ಯದಿ (SDL_ISPIXELFORMAT_FOURCC(format)) {
        ಯದಿ (format == SDL_PIXELFORMAT_MJPG) {
            // We don't know in advance what it will be, we'll figure it out later.
            ಪ್ರತ್ಯಾಗಮ true;
        }

        ಯದಿ (!SDL_CalculateYUVSize(format, width, height, &sz, &p)) {
            // Overflow...
            ಪ್ರತ್ಯಾಗಮ false;
        }
    } ಅನ್ಯಥಾ {
        ಯದಿ (!SDL_CalculateRGBSize(format, width, height, &sz, &p, minimalPitch)) {
            // Overflow...
            ಪ್ರತ್ಯಾಗಮ false;
        }
    }

    ಯದಿ (size) {
        *size = sz;
    }

    ಯದಿ (pitch) {
        *pitch = p;
    }

    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ bool SDL_InitializeSurface(SDL_Surface *surface, ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, SDL_PixelFormat format, SDL_Colorspace colorspace, SDL_PropertiesID props, ಶೂನ್ಯ *pixels, ಪೂರ್ಣಾಙ್ಕ pitch, bool onstack)
{
    SDL_zerop(surface);

    surface->flags = SDL_SURFACE_PREALLOCATED;
    surface->format = format;
    surface->w = width;
    surface->h = height;
    surface->pixels = pixels;
    surface->pitch = pitch;
    surface->reserved = &SDL_surface_magic;

    ಯದಿ (onstack) {
        surface->internal_flags |= SDL_INTERNAL_SURFACE_ರಾಶಿ;
    }

    surface->fmt = SDL_GetPixelFormatDetails(format);
    ಯದಿ (!surface->fmt) {
        SDL_DestroySurface(surface);
        ಪ್ರತ್ಯಾಗಮ false;
    }

    // Initialize the clip rect
    surface->clip_rect.w = width;
    surface->clip_rect.h = height;

    // Allocate an empty mapping
    surface->map.info.r = 0xFF;
    surface->map.info.g = 0xFF;
    surface->map.info.b = 0xFF;
    surface->map.info.a = 0xFF;

    ಯದಿ (colorspace == SDL_COLORSPACE_UNKNOWN) {
        surface->colorspace = SDL_GetDefaultColorspaceForFormat(format);
    } ಅನ್ಯಥಾ {
        surface->colorspace = colorspace;
    }

    ಯದಿ (props) {
        ಯದಿ (!SDL_CopyProperties(props, SDL_GetSurfaceProperties(surface))) {
            SDL_DestroySurface(surface);
            ಪ್ರತ್ಯಾಗಮ false;
        }
    }

    // By default surfaces with an alpha mask are set up for blending
    ಯದಿ (SDL_ISPIXELFORMAT_ALPHA(surface->format)) {
        SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
    }

    // The surface is ready to go
    surface->refcount = 1;
    ಪ್ರತ್ಯಾಗಮ true;
}

/*
 * Create an empty surface of the appropriate depth using the given format
 */
ಸ್ಥಿರ SDL_Surface *SDL_CreateSurfaceInternal(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, SDL_PixelFormat format, bool clear_surface)
{
    size_t pitch, size;
    SDL_Surface *surface;

    CHECK_PARAM(width < 0) {
        SDL_InvalidParamError("width");
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    CHECK_PARAM(height < 0) {
        SDL_InvalidParamError("height");
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    ಯದಿ (!SDL_CalculateSurfaceSize(format, width, height, &size, &pitch, false /* not minimal pitch */)) {
        // Overflow...
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    // Allocate and initialize the surface
    surface = (SDL_Surface *)SDL_malloc(ಪರಿಮಾಣ(*surface));
    ಯದಿ (!surface) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    ಯದಿ (!SDL_InitializeSurface(surface, width, height, format, SDL_COLORSPACE_UNKNOWN, 0, ರಿಕ್ತ, (ಪೂರ್ಣಾಙ್ಕ)pitch, false)) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    ಯದಿ (surface->w && surface->h && format != SDL_PIXELFORMAT_MJPG) {
        surface->flags &= ~SDL_SURFACE_PREALLOCATED;
        ಯದಿ (SDL_GetHintBoolean("SDL_SURFACE_MALLOC", false)) {
            ಯದಿ (clear_surface) {
                surface->pixels = SDL_calloc(1, size);
            } ಅನ್ಯಥಾ {
                surface->pixels = SDL_malloc(size);
            }
        } ಅನ್ಯಥಾ {
            surface->flags |= SDL_SURFACE_SIMD_ALIGNED;
            ಯದಿ (clear_surface) {
                surface->pixels = SDL_aligned_alloc_zero(SDL_GetSIMDAlignment(), size);
            } ಅನ್ಯಥಾ {
                surface->pixels = SDL_aligned_alloc(SDL_GetSIMDAlignment(), size);
            }
        }
        ಯದಿ (!surface->pixels) {
            SDL_DestroySurface(surface);
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        }
    }
    ಪ್ರತ್ಯಾಗಮ surface;
}

SDL_Surface *SDL_CreateSurfaceZeroed(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, SDL_PixelFormat format)
{
    ಪ್ರತ್ಯಾಗಮ SDL_CreateSurfaceInternal(width, height, format, true);
}

SDL_Surface *SDL_CreateSurfaceUninitialized(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, SDL_PixelFormat format)
{
    ಪ್ರತ್ಯಾಗಮ SDL_CreateSurfaceInternal(width, height, format, false);
}

SDL_Surface *SDL_CreateSurface(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, SDL_PixelFormat format)
{
    ಪ್ರತ್ಯಾಗಮ SDL_CreateSurfaceZeroed(width, height, format);
}


/*
 * Create an RGB surface from an existing memory buffer using the given
 * enum SDL_PIXELFORMAT_* format
 */
SDL_Surface *SDL_CreateSurfaceFrom(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, SDL_PixelFormat format, ಶೂನ್ಯ *pixels, ಪೂರ್ಣಾಙ್ಕ pitch)
{
    CHECK_PARAM(width < 0) {
        SDL_InvalidParamError("width");
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    CHECK_PARAM(height < 0) {
        SDL_InvalidParamError("height");
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    ಯದಿ (pitch == 0 && !pixels) {
        // The application will fill these in later with valid values
    } ಅನ್ಯಥಾ {
        size_t minimalPitch;

        ಯದಿ (!SDL_CalculateSurfaceSize(format, width, height, ರಿಕ್ತ, &minimalPitch, true /* minimal pitch */)) {
            // Overflow...
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        }

        CHECK_PARAM(pitch < 0 || (size_t)pitch < minimalPitch) {
            SDL_InvalidParamError("pitch");
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        }
    }

    // Allocate and initialize the surface
    SDL_Surface *surface = (SDL_Surface *)SDL_malloc(ಪರಿಮಾಣ(*surface));
    ಯದಿ (!surface ||
        !SDL_InitializeSurface(surface, width, height, format, SDL_COLORSPACE_UNKNOWN, 0, pixels, pitch, false)) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
    ಪ್ರತ್ಯಾಗಮ surface;
}

SDL_PropertiesID SDL_GetSurfaceProperties(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        ಪ್ರತ್ಯಾಗಮ 0;
    }

    ಯದಿ (!surface->props) {
        surface->props = SDL_CreateProperties();
    }
    ಪ್ರತ್ಯಾಗಮ surface->props;
}

bool SDL_SetSurfaceColorspace(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("surface");
    }

    surface->colorspace = colorspace;
    ಪ್ರತ್ಯಾಗಮ true;
}

SDL_Colorspace SDL_GetSurfaceColorspace(SDL_Surface *surface)
{
    ಯದಿ (!SDL_SurfaceValid(surface)) {
        ಪ್ರತ್ಯಾಗಮ SDL_COLORSPACE_UNKNOWN;
    }

    ಪ್ರತ್ಯಾಗಮ surface->colorspace;
}

ಭಿನ್ನ SDL_GetDefaultSDRWhitePoint(SDL_Colorspace colorspace)
{
    ಪ್ರತ್ಯಾಗಮ SDL_GetSurfaceSDRWhitePoint(ರಿಕ್ತ, colorspace);
}

ಭಿನ್ನ SDL_GetSurfaceSDRWhitePoint(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    SDL_TransferCharacteristics transfer = SDL_COLORSPACETRANSFER(colorspace);

    ಯದಿ (transfer == SDL_TRANSFER_CHARACTERISTICS_LINEAR ||
        transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
        SDL_PropertiesID props;
        ಭಿನ್ನ default_ಮೌಲ್ಯ = 1.0f;

        ಯದಿ (SDL_SurfaceValid(surface)) {
            props = surface->props;
        } ಅನ್ಯಥಾ {
            props = 0;
        }
        ಯದಿ (transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
            /* The older standards use an SDR white point of 100 nits.
             * ITU-R BT.2408-6 recommends using an SDR white point of 203 nits.
             * This is the default Chrome uses, and what a lot of game content
             * assumes, so we'll go with that.
             */
            ಧ್ರುವ ಭಿನ್ನ DEFAULT_PQ_SDR_WHITE_POINT = 203.0f;
            default_ಮೌಲ್ಯ = DEFAULT_PQ_SDR_WHITE_POINT;
        }
        ಪ್ರತ್ಯಾಗಮ SDL_GetFloatProperty(props, SDL_PROP_SURFACE_SDR_WHITE_POINT_FLOAT, default_ಮೌಲ್ಯ);
    }
    ಪ್ರತ್ಯಾಗಮ 1.0f;
}

ಭಿನ್ನ SDL_GetDefaultHDRHeadroom(SDL_Colorspace colorspace)
{
    ಪ್ರತ್ಯಾಗಮ SDL_GetSurfaceHDRHeadroom(ರಿಕ್ತ, colorspace);
}

ಭಿನ್ನ SDL_GetSurfaceHDRHeadroom(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    SDL_TransferCharacteristics transfer = SDL_COLORSPACETRANSFER(colorspace);

    ಯದಿ (transfer == SDL_TRANSFER_CHARACTERISTICS_LINEAR ||
        transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
        SDL_PropertiesID props;
        ಭಿನ್ನ default_ಮೌಲ್ಯ = 0.0f;

        ಯದಿ (SDL_SurfaceValid(surface)) {
            props = surface->props;
        } ಅನ್ಯಥಾ {
            props = 0;
        }
        ಪ್ರತ್ಯಾಗಮ SDL_GetFloatProperty(props, SDL_PROP_SURFACE_HDR_HEADROOM_FLOAT, default_ಮೌಲ್ಯ);
    }
    ಪ್ರತ್ಯಾಗಮ 1.0f;
}

SDL_Palette *SDL_CreateSurfacePalette(SDL_Surface *surface)
{
    SDL_Palette *palette;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    CHECK_PARAM(!SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        SDL_SetError("The surface is not indexed format");
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    palette = SDL_CreatePalette((1 << SDL_BITSPERPIXEL(surface->format)));
    ಯದಿ (!palette) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    ಯದಿ (palette->ncolors == 2) {
        // Create a black and white bitmap palette
        palette->colors[0].r = 0xFF;
        palette->colors[0].g = 0xFF;
        palette->colors[0].b = 0xFF;
        palette->colors[1].r = 0x00;
        palette->colors[1].g = 0x00;
        palette->colors[1].b = 0x00;
    }

    ಯದಿ (!SDL_SetSurfacePalette(surface, palette)) {
        SDL_DestroyPalette(palette);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    // The surface has retained the palette, we can remove the reference here
    SDL_assert(palette->refcount == 2);
    SDL_DestroyPalette(palette);
    ಪ್ರತ್ಯಾಗಮ palette;
}

bool SDL_SetSurfacePalette(SDL_Surface *surface, SDL_Palette *palette)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(palette && !SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Surface doesn't use a palette");
    }

    CHECK_PARAM(palette && palette->ncolors > (1 << SDL_BITSPERPIXEL(surface->format))) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Palette doesn't match surface format");
    }

    ಯದಿ (palette != surface->palette) {
        ಯದಿ (surface->palette) {
            SDL_DestroyPalette(surface->palette);
        }

        surface->palette = palette;

        ಯದಿ (surface->palette) {
            ++surface->palette->refcount;
        }
    }

    SDL_InvalidateMap(&surface->map);

    ಪ್ರತ್ಯಾಗಮ true;
}

SDL_Palette *SDL_GetSurfacePalette(SDL_Surface *surface)
{
    ಯದಿ (!SDL_SurfaceValid(surface)) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    ಪ್ರತ್ಯಾಗಮ surface->palette;
}

bool SDL_AddSurfaceAlternateImage(SDL_Surface *surface, SDL_Surface *image)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(!SDL_SurfaceValid(image)) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("image");
    }

    SDL_Surface **images = (SDL_Surface **)SDL_realloc(surface->images, (surface->ಅಂಕೆ_images + 1) * ಪರಿಮಾಣ(*images));
    ಯದಿ (!images) {
        ಪ್ರತ್ಯಾಗಮ false;
    }
    images[surface->ಅಂಕೆ_images] = image;
    surface->images = images;
    ++surface->ಅಂಕೆ_images;
    ++image->refcount;
    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_SurfaceHasAlternateImages(SDL_Surface *surface)
{
    ಯದಿ (!SDL_SurfaceValid(surface)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    ಪ್ರತ್ಯಾಗಮ (surface->ಅಂಕೆ_images > 0);
}

SDL_Surface **SDL_GetSurfaceImages(SDL_Surface *surface, ಪೂರ್ಣಾಙ್ಕ *ಎಣಿಕೆ)
{
    ಯದಿ (ಎಣಿಕೆ) {
        *ಎಣಿಕೆ = 0;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    ಪೂರ್ಣಾಙ್ಕ ಅಂಕೆ_images = 1 + surface->ಅಂಕೆ_images;
    SDL_Surface **images = (SDL_Surface **)SDL_malloc((ಅಂಕೆ_images + 1) * ಪರಿಮಾಣ(*images));
    ಯದಿ (!images) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
    images[0] = surface;
    ಯದಿ (surface->ಅಂಕೆ_images > 0) {
        SDL_memcpy(&images[1], surface->images, (surface->ಅಂಕೆ_images * ಪರಿಮಾಣ(images[1])));
    }
    images[ಅಂಕೆ_images] = ರಿಕ್ತ;

    ಯದಿ (ಎಣಿಕೆ) {
        *ಎಣಿಕೆ = ಅಂಕೆ_images;
    }
    ಪ್ರತ್ಯಾಗಮ images;
}

SDL_Surface *SDL_GetSurfaceImage(SDL_Surface *surface, ಭಿನ್ನ display_scale)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    ಯದಿ (!SDL_SurfaceHasAlternateImages(surface)) {
        ++surface->refcount;
        ಪ್ರತ್ಯಾಗಮ surface;
    }

    // This surface has high DPI images, pick the best one available, or scale one to the correct size
    SDL_Surface **images = SDL_GetSurfaceImages(surface, ರಿಕ್ತ);
    ಯದಿ (!images) {
        // Failure, fall back to the existing surface
        ++surface->refcount;
        ಪ್ರತ್ಯಾಗಮ surface;
    }

    // Find closest image. Images that are larger than the
    // desired size are preferred over images that are smaller.
    SDL_Surface *closest = ರಿಕ್ತ;
    ಪೂರ್ಣಾಙ್ಕ desired_w = (ಪೂರ್ಣಾಙ್ಕ)SDL_round(surface->w * display_scale);
    ಪೂರ್ಣಾಙ್ಕ desired_h = (ಪೂರ್ಣಾಙ್ಕ)SDL_round(surface->h * display_scale);
    ಪೂರ್ಣಾಙ್ಕ desired_size = desired_w * desired_h;
    ಪೂರ್ಣಾಙ್ಕ closest_distance = -1;
    ಪೂರ್ಣಾಙ್ಕ closest_size = -1;
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; images[i]; ++i) {
        SDL_Surface *candidate = images[i];
        ಪೂರ್ಣಾಙ್ಕ size = candidate->w * candidate->h;
        ಪೂರ್ಣಾಙ್ಕ delta_w = (candidate->w - desired_w);
        ಪೂರ್ಣಾಙ್ಕ delta_h = (candidate->h - desired_h);
        ಪೂರ್ಣಾಙ್ಕ distance = (delta_w * delta_w) + (delta_h * delta_h);
        ಯದಿ (closest_distance < 0 || distance < closest_distance ||
            (size > desired_size && closest_size < desired_size)) {
            closest = candidate;
            closest_distance = distance;
            closest_size = size;
        }
    }
    SDL_free(images);
    SDL_assert(closest != ರಿಕ್ತ);    // We should always have at least one surface

    ಯದಿ (closest->w == desired_w && closest->h == desired_h) {
        ++closest->refcount;
        ಪ್ರತ್ಯಾಗಮ closest;
    }

    // We need to scale the image to the correct size. To maintain good image quality, downscaling
    // is done in steps, never reducing the width and height by more than half each time.
    SDL_Surface *scaled = closest;
    ಕುರು {
        ಪೂರ್ಣಾಙ್ಕ next_scaled_w = SDL_max(desired_w, (scaled->w + 1) / 2);
        ಪೂರ್ಣಾಙ್ಕ next_scaled_h = SDL_max(desired_h, (scaled->h + 1) / 2);
        SDL_Surface *next_scaled = SDL_ScaleSurface(scaled, next_scaled_w, next_scaled_h, SDL_SCALEMODE_LINEAR);
        ಯದಿ (scaled != closest) {
            SDL_DestroySurface(scaled);
        }
        scaled = next_scaled;
        ಯದಿ (!scaled) {
            // Failure, fall back to the closest surface
            ++closest->refcount;
            ಪ್ರತ್ಯಾಗಮ closest;
        }
    } ಯಾವತ್ (scaled->w != desired_w || scaled->h != desired_h);

    ಪ್ರತ್ಯಾಗಮ scaled;
}

ಶೂನ್ಯ SDL_RemoveSurfaceAlternateImages(SDL_Surface *surface)
{
    ಯದಿ (!SDL_SurfaceValid(surface)) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    ಯದಿ (surface->ಅಂಕೆ_images > 0) {
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < surface->ಅಂಕೆ_images; ++i) {
            SDL_DestroySurface(surface->images[i]);
        }
        SDL_free(surface->images);
        surface->images = ರಿಕ್ತ;
        surface->ಅಂಕೆ_images = 0;
    }
}

bool SDL_SetSurfaceRLE(SDL_Surface *surface, bool enabled)
{
    ಪೂರ್ಣಾಙ್ಕ flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("surface");
    }

    flags = surface->map.info.flags;
    ಯದಿ (enabled) {
        surface->map.info.flags |= SDL_COPY_RLE_DESIRED;
    } ಅನ್ಯಥಾ {
        surface->map.info.flags &= ~SDL_COPY_RLE_DESIRED;
    }
    ಯದಿ (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_SurfaceHasRLE(SDL_Surface *surface)
{
    ಯದಿ (!SDL_SurfaceValid(surface)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    ಯದಿ (!(surface->map.info.flags & SDL_COPY_RLE_DESIRED)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_Set_Surface_Color_ಕೀಲಿ(SDL_Surface *surface, bool enabled, Uint32 ಕೀಲಿ)
{
    ಪೂರ್ಣಾಙ್ಕ flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(surface->palette && ಕೀಲಿ >= ((Uint32)surface->palette->ncolors)) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("key");
    }

    flags = surface->map.info.flags;
    ಯದಿ (enabled) {
        surface->map.info.flags |= SDL_COPY_COLORKEY;
        surface->map.info.colorkey = ಕೀಲಿ;
    } ಅನ್ಯಥಾ {
        surface->map.info.flags &= ~SDL_COPY_COLORKEY;
    }
    ಯದಿ (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }

    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_Surface_Has_Color_ಕೀಲಿ(SDL_Surface *surface)
{
    ಯದಿ (!SDL_SurfaceValid(surface)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    ಯದಿ (!(surface->map.info.flags & SDL_COPY_COLORKEY)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_Get_Surface_Color_ಕೀಲಿ(SDL_Surface *surface, Uint32 *ಕೀಲಿ)
{
    ಯದಿ (ಕೀಲಿ) {
        *ಕೀಲಿ = 0;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(!(surface->map.info.flags & SDL_COPY_COLORKEY)) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Surface doesn't have a colorkey");
    }

    ಯದಿ (ಕೀಲಿ) {
        *ಕೀಲಿ = surface->map.info.colorkey;
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

/* This is a fairly slow function to switch from colorkey to alpha
   NB: it doesn't handle bpp 1 or 3, because they have no alpha channel */
ಸ್ಥಿರ ಶೂನ್ಯ SDL_ConvertColorkeyToAlpha(SDL_Surface *surface, bool ignore_alpha)
{
    ಪೂರ್ಣಾಙ್ಕ x, y, bpp;

    ಯದಿ (!SDL_SurfaceValid(surface)) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    ಯದಿ (!(surface->map.info.flags & SDL_COPY_COLORKEY) ||
        !SDL_ISPIXELFORMAT_ALPHA(surface->format)) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    bpp = SDL_BYTESPERPIXEL(surface->format);

    SDL_LockSurface(surface);

    ಯದಿ (bpp == 2) {
        Uint16 *row, *spot;
        Uint16 ckey = (Uint16)surface->map.info.colorkey;
        Uint16 mask = (Uint16)(~surface->fmt->Amask);

        // Ignore, or not, alpha in colorkey comparison
        ಯದಿ (ignore_alpha) {
            ckey &= mask;
            row = (Uint16 *)surface->pixels;
            ಪ್ರತಿ (y = surface->h; y--;) {
                spot = row;
                ಪ್ರತಿ (x = surface->w; x--;) {
                    ಯದಿ ((*spot & mask) == ckey) {
                        *spot &= mask;
                    }
                    ++spot;
                }
                row += surface->pitch / 2;
            }
        } ಅನ್ಯಥಾ {
            row = (Uint16 *)surface->pixels;
            ಪ್ರತಿ (y = surface->h; y--;) {
                spot = row;
                ಪ್ರತಿ (x = surface->w; x--;) {
                    ಯದಿ (*spot == ckey) {
                        *spot &= mask;
                    }
                    ++spot;
                }
                row += surface->pitch / 2;
            }
        }
    } ಅನ್ಯಥಾ ಯದಿ (bpp == 4) {
        Uint32 *row, *spot;
        Uint32 ckey = surface->map.info.colorkey;
        Uint32 mask = ~surface->fmt->Amask;

        // Ignore, or not, alpha in colorkey comparison
        ಯದಿ (ignore_alpha) {
            ckey &= mask;
            row = (Uint32 *)surface->pixels;
            ಪ್ರತಿ (y = surface->h; y--;) {
                spot = row;
                ಪ್ರತಿ (x = surface->w; x--;) {
                    ಯದಿ ((*spot & mask) == ckey) {
                        *spot &= mask;
                    }
                    ++spot;
                }
                row += surface->pitch / 4;
            }
        } ಅನ್ಯಥಾ {
            row = (Uint32 *)surface->pixels;
            ಪ್ರತಿ (y = surface->h; y--;) {
                spot = row;
                ಪ್ರತಿ (x = surface->w; x--;) {
                    ಯದಿ (*spot == ckey) {
                        *spot &= mask;
                    }
                    ++spot;
                }
                row += surface->pitch / 4;
            }
        }
    }

    SDL_UnlockSurface(surface);

    SDL_Set_Surface_Color_ಕೀಲಿ(surface, false, 0);
    SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
}

bool SDL_SetSurfaceColorMod(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b)
{
    ಪೂರ್ಣಾಙ್ಕ flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("surface");
    }

    surface->map.info.r = r;
    surface->map.info.g = g;
    surface->map.info.b = b;

    flags = surface->map.info.flags;
    ಯದಿ (r != 0xFF || g != 0xFF || b != 0xFF) {
        surface->map.info.flags |= SDL_COPY_MODULATE_COLOR;
    } ಅನ್ಯಥಾ {
        surface->map.info.flags &= ~SDL_COPY_MODULATE_COLOR;
    }
    ಯದಿ (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_GetSurfaceColorMod(SDL_Surface *surface, Uint8 *r, Uint8 *g, Uint8 *b)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ಯದಿ (r) {
            *r = 255;
        }
        ಯದಿ (g) {
            *g = 255;
        }
        ಯದಿ (b) {
            *b = 255;
        }
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("surface");
    }

    ಯದಿ (r) {
        *r = surface->map.info.r;
    }
    ಯದಿ (g) {
        *g = surface->map.info.g;
    }
    ಯದಿ (b) {
        *b = surface->map.info.b;
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_SetSurfaceAlphaMod(SDL_Surface *surface, Uint8 alpha)
{
    ಪೂರ್ಣಾಙ್ಕ flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("surface");
    }

    surface->map.info.a = alpha;

    flags = surface->map.info.flags;
    ಯದಿ (alpha != 0xFF) {
        surface->map.info.flags |= SDL_COPY_MODULATE_ALPHA;
    } ಅನ್ಯಥಾ {
        surface->map.info.flags &= ~SDL_COPY_MODULATE_ALPHA;
    }
    ಯದಿ (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_GetSurfaceAlphaMod(SDL_Surface *surface, Uint8 *alpha)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ಯದಿ (alpha) {
            *alpha = 255;
        }
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("surface");
    }

    ಯದಿ (alpha) {
        *alpha = surface->map.info.a;
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_SetSurfaceBlendMode(SDL_Surface *surface, SDL_BlendMode blendMode)
{
    ಪೂರ್ಣಾಙ್ಕ flags;
    bool result = true;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(blendMode == SDL_BLENDMODE_INVALID) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("blendMode");
    }

    flags = surface->map.info.flags;
    surface->map.info.flags &= ~SDL_COPY_BLEND_MASK;
    ವಿಕಲ್ಪ (blendMode) {
    ಪಕ್ಷ SDL_BLENDMODE_NONE:
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_BLENDMODE_BLEND:
        surface->map.info.flags |= SDL_COPY_BLEND;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_BLENDMODE_BLEND_PREMULTIPLIED:
        surface->map.info.flags |= SDL_COPY_BLEND_PREMULTIPLIED;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_BLENDMODE_ADD:
        surface->map.info.flags |= SDL_COPY_ADD;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_BLENDMODE_ADD_PREMULTIPLIED:
        surface->map.info.flags |= SDL_COPY_ADD_PREMULTIPLIED;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_BLENDMODE_MOD:
        surface->map.info.flags |= SDL_COPY_MOD;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_BLENDMODE_MUL:
        surface->map.info.flags |= SDL_COPY_MUL;
        ಭಙ್ಗ;
    ಸ್ವಭಾವ:
        result = SDL_Unsupported();
        ಭಙ್ಗ;
    }

    ಯದಿ (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }

    ಪ್ರತ್ಯಾಗಮ result;
}

bool SDL_GetSurfaceBlendMode(SDL_Surface *surface, SDL_BlendMode *blendMode)
{
    ಯದಿ (blendMode) {
        *blendMode = SDL_BLENDMODE_INVALID;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("surface");
    }

    ಯದಿ (!blendMode) {
        ಪ್ರತ್ಯಾಗಮ true;
    }

    ವಿಕಲ್ಪ (surface->map.info.flags & SDL_COPY_BLEND_MASK) {
    ಪಕ್ಷ SDL_COPY_BLEND:
        *blendMode = SDL_BLENDMODE_BLEND;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_COPY_BLEND_PREMULTIPLIED:
        *blendMode = SDL_BLENDMODE_BLEND_PREMULTIPLIED;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_COPY_ADD:
        *blendMode = SDL_BLENDMODE_ADD;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_COPY_ADD_PREMULTIPLIED:
        *blendMode = SDL_BLENDMODE_ADD_PREMULTIPLIED;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_COPY_MOD:
        *blendMode = SDL_BLENDMODE_MOD;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_COPY_MUL:
        *blendMode = SDL_BLENDMODE_MUL;
        ಭಙ್ಗ;
    ಸ್ವಭಾವ:
        *blendMode = SDL_BLENDMODE_NONE;
        ಭಙ್ಗ;
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_SetSurfaceClipRect(SDL_Surface *surface, ಧ್ರುವ SDL_Rect *rect)
{
    SDL_Rect full_rect;

    // Don't do anything if there's no surface to act on
    ಯದಿ (!SDL_SurfaceValid(surface)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    // Set up the full surface rectangle
    full_rect.x = 0;
    full_rect.y = 0;
    full_rect.w = surface->w;
    full_rect.h = surface->h;

    // Set the clipping rectangle
    ಯದಿ (!rect) {
        surface->clip_rect = full_rect;
        ಪ್ರತ್ಯಾಗಮ true;
    }
    ಪ್ರತ್ಯಾಗಮ SDL_GetRectIntersection(rect, &full_rect, &surface->clip_rect);
}

bool SDL_GetSurfaceClipRect(SDL_Surface *surface, SDL_Rect *rect)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ಯದಿ (rect) {
            SDL_zerop(rect);
        }
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("surface");
    }
    CHECK_PARAM(!rect) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("rect");
    }
    *rect = surface->clip_rect;
    ಪ್ರತ್ಯಾಗಮ true;
}

/*
 * Set up a blit between two surfaces -- split into three parts:
 * The upper part, SDL_BlitSurface(), performs clipping and rectangle
 * verification.  The lower part is a pointer to a low level
 * accelerated blitting function.
 *
 * These parts are separated out and each used internally by this
 * library in the optimum places.  They are exported so that if
 * you know exactly what you are doing, you can optimize your code
 * by calling the one(s) you need.
 */
bool SDL_BlitSurfaceUnchecked(SDL_Surface *src, ಧ್ರುವ SDL_Rect *srcrect,
                             SDL_Surface *dst, ಧ್ರುವ SDL_Rect *dstrect)
{
    // Check to make sure the blit mapping is valid
    ಯದಿ (!SDL_ValidateMap(src, dst)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }
    ಪ್ರತ್ಯಾಗಮ src->map.blit(src, srcrect, dst, dstrect);
}

bool SDL_BlitSurface(SDL_Surface *src, ಧ್ರುವ SDL_Rect *srcrect, SDL_Surface *dst, ಧ್ರುವ SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src) || (!src->pixels && !SDL_MUSTLOCK(src))) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst) || (!dst->pixels && !SDL_MUSTLOCK(dst))) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Surfaces must not be locked during blit");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    ಯದಿ (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
    } ಅನ್ಯಥಾ {
        r_dst.x = 0;
        r_dst.y = 0;
    }

    // clip the source rectangle to the source surface
    ಯದಿ (srcrect) {
        SDL_Rect tmp;
        ಯದಿ (SDL_GetRectIntersection(srcrect, &r_src, &tmp) == false) {
            ಪ್ರತ್ಯಾಗಮ true;
        }

        // Shift dstrect, if srcrect origin has changed
        r_dst.x += tmp.x - srcrect->x;
        r_dst.y += tmp.y - srcrect->y;

        // Update srcrect
        r_src = tmp;
    }

    // There're no dstrect.w/h parameters. It's the same as srcrect
    r_dst.w = r_src.w;
    r_dst.h = r_src.h;

    // clip the destination rectangle against the clip rectangle
    {
        SDL_Rect tmp;
        ಯದಿ (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &tmp) == false) {
            ಪ್ರತ್ಯಾಗಮ true;
        }

        // Shift srcrect, if dstrect has changed
        r_src.x += tmp.x - r_dst.x;
        r_src.y += tmp.y - r_dst.y;
        r_src.w = tmp.w;
        r_src.h = tmp.h;

        // Update dstrect
        r_dst = tmp;
    }

    ಯದಿ (r_dst.w <= 0 || r_dst.h <= 0) {
        // No-op.
        ಪ್ರತ್ಯಾಗಮ true;
    }

    // Switch back to a fast blit if we were previously stretching
    ಯದಿ (src->map.info.flags & SDL_COPY_NEAREST) {
        src->map.info.flags &= ~SDL_COPY_NEAREST;
        SDL_InvalidateMap(&src->map);
    }

    ಪ್ರತ್ಯಾಗಮ SDL_BlitSurfaceUnchecked(src, &r_src, dst, &r_dst);
}

ಸ್ಥಿರ bool SDL_BlitSurfaceClippedScaled(SDL_Surface *src, ಧ್ರುವ SDL_Rect *srcrect, SDL_Surface *dst, ಧ್ರುವ SDL_Rect *dstrect, SDL_ScaleMode scaleMode)
{
    // We need to scale first, then blit into dst because we're clipping in the destination surface pixel coordinates
    bool result;
    ಪೂರ್ಣಾಙ್ಕ saved_w = src->w;
    ಪೂರ್ಣಾಙ್ಕ saved_h = src->h;
    ಶೂನ್ಯ *saved_pixels = src->pixels;
    src->w = srcrect->w;
    src->h = srcrect->h;
    src->pixels = (Uint8 *)src->pixels + srcrect->y * src->pitch + srcrect->x * SDL_BYTESPERPIXEL(src->format);
    SDL_Surface *scaled = SDL_ScaleSurface(src, dstrect->w, dstrect->h, scaleMode);
    ಯದಿ (scaled) {
        result = SDL_BlitSurface(scaled, ರಿಕ್ತ, dst, dstrect);
        SDL_DestroySurface(scaled);
    } ಅನ್ಯಥಾ {
        result = false;
    }
    src->w = saved_w;
    src->h = saved_h;
    src->pixels = saved_pixels;
    ಪ್ರತ್ಯಾಗಮ result;
}

bool SDL_BlitSurfaceScaled(SDL_Surface *src, ಧ್ರುವ SDL_Rect *srcrect, SDL_Surface *dst, ಧ್ರುವ SDL_Rect *dstrect, SDL_ScaleMode scaleMode)
{
    SDL_Rect r_src, r_dst;
    bool result;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src) || (!src->pixels && !SDL_MUSTLOCK(src))) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst) || (!dst->pixels && !SDL_MUSTLOCK(dst))) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Surfaces must not be locked during blit");
    }

    ವಿಕಲ್ಪ (scaleMode) {
    ಪಕ್ಷ SDL_SCALEMODE_NEAREST:
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SCALEMODE_LINEAR:
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SCALEMODE_PIXELART:
        scaleMode = SDL_SCALEMODE_NEAREST;
        ಭಙ್ಗ;
    ಸ್ವಭಾವ:
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("scaleMode");
    }

    ಪೂರ್ಣಾಙ್ಕ src_w = srcrect ? srcrect->w : src->w;
    ಪೂರ್ಣಾಙ್ಕ src_h = srcrect ? srcrect->h : src->h;
    ಪೂರ್ಣಾಙ್ಕ dst_w = dstrect ? dstrect->w : dst->w;
    ಪೂರ್ಣಾಙ್ಕ dst_h = dstrect ? dstrect->h : dst->h;
    ಯದಿ (src_w == dst_w && src_h == dst_h) {
        // No scaling, defer to regular blit
        ಪ್ರತ್ಯಾಗಮ SDL_BlitSurface(src, srcrect, dst, dstrect);
    }

    ಯದಿ (src->w == 0 || src->h == 0) {
        // Nothing to do
        ಪ್ರತ್ಯಾಗಮ true;
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    ಯದಿ (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
        r_dst.w = dstrect->w;
        r_dst.h = dstrect->h;
    } ಅನ್ಯಥಾ {
        r_dst.x = 0;
        r_dst.y = 0;
        r_dst.w = dst->w;
        r_dst.h = dst->h;
    }

    // clip the source rectangle to the source surface
    ಯದಿ (srcrect) {
        SDL_Rect desired, tmp;
        desired.x = srcrect->x;
        desired.y = srcrect->y;
        desired.w = SDL_max(srcrect->w, 1);
        desired.h = SDL_max(srcrect->h, 1);
        ಯದಿ (SDL_GetRectIntersection(&desired, &r_src, &tmp) == false) {
            ಪ್ರತ್ಯಾಗಮ true;
        }

        // Shift dstrect, if srcrect origin has changed
        r_dst.x += (tmp.x - desired.x) * r_dst.w / desired.w;
        r_dst.y += (tmp.y - desired.y) * r_dst.h / desired.h;
        r_dst.w += (tmp.w - desired.w) * r_dst.w / desired.w;
        r_dst.h += (tmp.h - desired.h) * r_dst.h / desired.h;

        // Update srcrect
        r_src = tmp;
    }

    SDL_Rect tmp;
    ಯದಿ (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &tmp) == false) {
        ಪ್ರತ್ಯಾಗಮ true;
    }

    ಯದಿ (tmp.x != r_dst.x || tmp.y != r_dst.y || tmp.w != r_dst.w || tmp.h != r_dst.h) {
        // Need to do a clipped and scaled blit
        ಪ್ರತ್ಯಾಗಮ SDL_BlitSurfaceClippedScaled(src, &r_src, dst, &r_dst, scaleMode);
    }

    ಯದಿ (SDL_MUSTLOCK(src)) {
        ಯದಿ (!SDL_LockSurface(src)) {
            ಪ್ರತ್ಯಾಗಮ false;
        }
    }
    ಯದಿ (SDL_MUSTLOCK(dst)) {
        ಯದಿ (!SDL_LockSurface(dst)) {
            ಯದಿ (SDL_MUSTLOCK(src)) {
                SDL_UnlockSurface(src);
            }
            ಪ್ರತ್ಯಾಗಮ false;
        }
    }

    result = SDL_BlitSurfaceUncheckedScaled(src, &r_src, dst, &r_dst, scaleMode);

    ಯದಿ (SDL_MUSTLOCK(src)) {
        SDL_UnlockSurface(src);
    }
    ಯದಿ (SDL_MUSTLOCK(dst)) {
        SDL_UnlockSurface(dst);
    }
    ಪ್ರತ್ಯಾಗಮ result;
}

/**
 *  This is a semi-private blit function and it performs low-level surface
 *  scaled blitting only.
 */
bool SDL_BlitSurfaceUncheckedScaled(SDL_Surface *src, ಧ್ರುವ SDL_Rect *srcrect, SDL_Surface *dst, ಧ್ರುವ SDL_Rect *dstrect, SDL_ScaleMode scaleMode)
{
    ಸ್ಥಿರ ಧ್ರುವ Uint32 complex_copy_flags = (SDL_COPY_MODULATE_MASK | SDL_COPY_BLEND_MASK | SDL_COPY_COLORKEY);

    ಯದಿ (srcrect->w > SDL_MAX_UINT16 || srcrect->h > SDL_MAX_UINT16 ||
        dstrect->w > SDL_MAX_UINT16 || dstrect->h > SDL_MAX_UINT16) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Size too large for scaling");
    }

    ಯದಿ (!(src->map.info.flags & SDL_COPY_NEAREST)) {
        src->map.info.flags |= SDL_COPY_NEAREST;
        SDL_InvalidateMap(&src->map);
    }

    ಯದಿ (scaleMode == SDL_SCALEMODE_NEAREST || scaleMode == SDL_SCALEMODE_PIXELART) {
        ಯದಿ (!(src->map.info.flags & complex_copy_flags) &&
            src->format == dst->format &&
            (!SDL_ISPIXELFORMAT_INDEXED(src->format) ||
             (SDL_BITSPERPIXEL(src->format) == 8 && SDL_IsSamePalette(src->palette, dst->palette))) &&
            SDL_BYTESPERPIXEL(src->format) <= 4) {
            ಪ್ರತ್ಯಾಗಮ SDL_StretchSurface(src, srcrect, dst, dstrect, SDL_SCALEMODE_NEAREST);
        } ಅನ್ಯಥಾ ಯದಿ (SDL_BITSPERPIXEL(src->format) < 8) {
            // Scaling bitmap not yet supported, convert to RGBA for blit
            bool result = false;
            SDL_Surface *tmp = SDL_ConvertSurface(src, SDL_PIXELFORMAT_ARGB8888);
            ಯದಿ (tmp) {
                result = SDL_BlitSurfaceUncheckedScaled(tmp, srcrect, dst, dstrect, SDL_SCALEMODE_NEAREST);
                SDL_DestroySurface(tmp);
            }
            ಪ್ರತ್ಯಾಗಮ result;
        } ಅನ್ಯಥಾ {
            ಪ್ರತ್ಯಾಗಮ SDL_BlitSurfaceUnchecked(src, srcrect, dst, dstrect);
        }
    } ಅನ್ಯಥಾ {
        ಯದಿ (!(src->map.info.flags & complex_copy_flags) &&
            src->format == dst->format &&
            !SDL_ISPIXELFORMAT_INDEXED(src->format) &&
            SDL_BYTESPERPIXEL(src->format) == 4 &&
            src->format != SDL_PIXELFORMAT_ARGB2101010) {
            // fast path
            ಪ್ರತ್ಯಾಗಮ SDL_StretchSurface(src, srcrect, dst, dstrect, SDL_SCALEMODE_LINEAR);
        } ಅನ್ಯಥಾ ಯದಿ (SDL_BITSPERPIXEL(src->format) < 8) {
            // Scaling bitmap not yet supported, convert to RGBA for blit
            bool result = false;
            SDL_Surface *tmp = SDL_ConvertSurface(src, SDL_PIXELFORMAT_ARGB8888);
            ಯದಿ (tmp) {
                result = SDL_BlitSurfaceUncheckedScaled(tmp, srcrect, dst, dstrect, scaleMode);
                SDL_DestroySurface(tmp);
            }
            ಪ್ರತ್ಯಾಗಮ result;
        } ಅನ್ಯಥಾ {
            // Use intermediate surface(s)
            SDL_Surface *tmp1 = ರಿಕ್ತ;
            bool result;
            SDL_Rect srcrect2;
            ಪೂರ್ಣಾಙ್ಕ is_complex_copy_flags = (src->map.info.flags & complex_copy_flags);

            Uint8 r, g, b;
            Uint8 alpha;
            SDL_BlendMode blendMode;

            // Save source infos
            SDL_GetSurfaceColorMod(src, &r, &g, &b);
            SDL_GetSurfaceAlphaMod(src, &alpha);
            SDL_GetSurfaceBlendMode(src, &blendMode);
            srcrect2.x = srcrect->x;
            srcrect2.y = srcrect->y;
            srcrect2.w = srcrect->w;
            srcrect2.h = srcrect->h;

            // Change source format if not appropriate for scaling
            ಯದಿ (SDL_BYTESPERPIXEL(src->format) != 4 || src->format == SDL_PIXELFORMAT_ARGB2101010) {
                SDL_PixelFormat fmt;
                ಯದಿ (SDL_BYTESPERPIXEL(dst->format) == 4 && dst->format != SDL_PIXELFORMAT_ARGB2101010 &&
                    (SDL_ISPIXELFORMAT_ALPHA(dst->format) || !is_complex_copy_flags)) {
                    fmt = dst->format;
                } ಅನ್ಯಥಾ {
                    fmt = SDL_PIXELFORMAT_ARGB8888;
                }
                tmp1 = SDL_ConvertSurfaceRect(src, srcrect, fmt);
                ಯದಿ (!tmp1) {
                    ಪ್ರತ್ಯಾಗಮ false;
                }
                src = tmp1;
                srcrect2.x = 0;
                srcrect2.y = 0;
            }

            // Intermediate scaling
            ಯದಿ (is_complex_copy_flags || src->format != dst->format) {
                SDL_Rect tmprect;
                SDL_Surface *tmp2 = SDL_CreateSurfaceUninitialized(dstrect->w, dstrect->h, src->format);
                SDL_StretchSurface(src, &srcrect2, tmp2, ರಿಕ್ತ, SDL_SCALEMODE_LINEAR);

                SDL_SetSurfaceColorMod(tmp2, r, g, b);
                SDL_SetSurfaceAlphaMod(tmp2, alpha);
                SDL_SetSurfaceBlendMode(tmp2, blendMode);

                tmprect.x = 0;
                tmprect.y = 0;
                tmprect.w = dstrect->w;
                tmprect.h = dstrect->h;
                result = SDL_BlitSurfaceUnchecked(tmp2, &tmprect, dst, dstrect);
                SDL_DestroySurface(tmp2);
            } ಅನ್ಯಥಾ {
                result = SDL_StretchSurface(src, &srcrect2, dst, dstrect, SDL_SCALEMODE_LINEAR);
            }

            SDL_DestroySurface(tmp1);
            ಪ್ರತ್ಯಾಗಮ result;
        }
    }
}

bool SDL_BlitSurfaceTiled(SDL_Surface *src, ಧ್ರುವ SDL_Rect *srcrect, SDL_Surface *dst, ಧ್ರುವ SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Surfaces must not be locked during blit");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    ಯದಿ (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
        r_dst.w = dstrect->w;
        r_dst.h = dstrect->h;
    } ಅನ್ಯಥಾ {
        r_dst.x = 0;
        r_dst.y = 0;
        r_dst.w = dst->w;
        r_dst.h = dst->h;
    }

    // clip the source rectangle to the source surface
    ಯದಿ (srcrect) {
        ಯದಿ (SDL_GetRectIntersection(srcrect, &r_src, &r_src) == false) {
            ಪ್ರತ್ಯಾಗಮ true;
        }

        // For tiling we don't adjust the destination rectangle
    }

    // clip the destination rectangle against the clip rectangle
    {
        ಯದಿ (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &r_dst) == false) {
            ಪ್ರತ್ಯಾಗಮ true;
        }

        // For tiling we don't adjust the source rectangle
    }

    // Switch back to a fast blit if we were previously stretching
    ಯದಿ (src->map.info.flags & SDL_COPY_NEAREST) {
        src->map.info.flags &= ~SDL_COPY_NEAREST;
        SDL_InvalidateMap(&src->map);
    }

    ಪೂರ್ಣಾಙ್ಕ rows = r_dst.h / r_src.h;
    ಪೂರ್ಣಾಙ್ಕ cols = r_dst.w / r_src.w;
    ಪೂರ್ಣಾಙ್ಕ remaining_w = r_dst.w % r_src.w;
    ಪೂರ್ಣಾಙ್ಕ remaining_h = r_dst.h % r_src.h;
    SDL_Rect curr_src, curr_dst;

    SDL_copyp(&curr_src, &r_src);
    curr_dst.y = r_dst.y;
    curr_dst.w = r_src.w;
    curr_dst.h = r_src.h;
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ y = 0; y < rows; ++y) {
        curr_dst.x = r_dst.x;
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ x = 0; x < cols; ++x) {
            ಯದಿ (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                ಪ್ರತ್ಯಾಗಮ false;
            }
            curr_dst.x += curr_dst.w;
        }
        ಯದಿ (remaining_w) {
            curr_src.w = remaining_w;
            curr_dst.w = remaining_w;
            ಯದಿ (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                ಪ್ರತ್ಯಾಗಮ false;
            }
            curr_src.w = r_src.w;
            curr_dst.w = r_src.w;
        }
        curr_dst.y += curr_dst.h;
    }
    ಯದಿ (remaining_h) {
        curr_src.h = remaining_h;
        curr_dst.h = remaining_h;
        curr_dst.x = r_dst.x;
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ x = 0; x < cols; ++x) {
            ಯದಿ (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                ಪ್ರತ್ಯಾಗಮ false;
            }
            curr_dst.x += curr_dst.w;
        }
        ಯದಿ (remaining_w) {
            curr_src.w = remaining_w;
            curr_dst.w = remaining_w;
            ಯದಿ (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                ಪ್ರತ್ಯಾಗಮ false;
            }
        }
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_BlitSurfaceTiledWithScale(SDL_Surface *src, ಧ್ರುವ SDL_Rect *srcrect, ಭಿನ್ನ scale, SDL_ScaleMode scaleMode, SDL_Surface *dst, ಧ್ರುವ SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Surfaces must not be locked during blit");
    }
    CHECK_PARAM(scale < 0.0f) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("scale");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    ಯದಿ (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
        r_dst.w = dstrect->w;
        r_dst.h = dstrect->h;
    } ಅನ್ಯಥಾ {
        r_dst.x = 0;
        r_dst.y = 0;
        r_dst.w = dst->w;
        r_dst.h = dst->h;
    }

    // clip the source rectangle to the source surface
    ಯದಿ (srcrect) {
        ಯದಿ (SDL_GetRectIntersection(srcrect, &r_src, &r_src) == false) {
            ಪ್ರತ್ಯಾಗಮ true;
        }

        // For tiling we don't adjust the destination rectangle
    }

    // clip the destination rectangle against the clip rectangle
    {
        ಯದಿ (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &r_dst) == false) {
            ಪ್ರತ್ಯಾಗಮ true;
        }

        // For tiling we don't adjust the source rectangle
    }

    // Switch back to a fast blit if we were previously stretching
    ಯದಿ (src->map.info.flags & SDL_COPY_NEAREST) {
        src->map.info.flags &= ~SDL_COPY_NEAREST;
        SDL_InvalidateMap(&src->map);
    }

    ಪೂರ್ಣಾಙ್ಕ tile_width = (ಪೂರ್ಣಾಙ್ಕ)SDL_roundf(r_src.w * scale);
    ಪೂರ್ಣಾಙ್ಕ tile_height = (ಪೂರ್ಣಾಙ್ಕ)SDL_roundf(r_src.h * scale);
    ಯದಿ (tile_width <= 0 || tile_height <= 0) {
        // Nothing to do
        ಪ್ರತ್ಯಾಗಮ true;
    }
    ಪೂರ್ಣಾಙ್ಕ rows = r_dst.h / tile_height;
    ಪೂರ್ಣಾಙ್ಕ cols = r_dst.w / tile_width;
    ಪೂರ್ಣಾಙ್ಕ remaining_dst_w = (r_dst.w - cols * tile_width);
    ಪೂರ್ಣಾಙ್ಕ remaining_dst_h = (r_dst.h - rows * tile_height);
    ಪೂರ್ಣಾಙ್ಕ remaining_src_w = (ಪೂರ್ಣಾಙ್ಕ)(remaining_dst_w / scale);
    ಪೂರ್ಣಾಙ್ಕ remaining_src_h = (ಪೂರ್ಣಾಙ್ಕ)(remaining_dst_h / scale);
    SDL_Rect curr_src, curr_dst;

    SDL_copyp(&curr_src, &r_src);
    curr_dst.y = r_dst.y;
    curr_dst.w = tile_width;
    curr_dst.h = tile_height;
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ y = 0; y < rows; ++y) {
        curr_dst.x = r_dst.x;
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ x = 0; x < cols; ++x) {
            ಯದಿ (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
                ಪ್ರತ್ಯಾಗಮ false;
            }
            curr_dst.x += curr_dst.w;
        }
        ಯದಿ (remaining_dst_w > 0) {
            curr_src.w = remaining_src_w;
            curr_dst.w = remaining_dst_w;
            ಯದಿ (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
                ಪ್ರತ್ಯಾಗಮ false;
            }
            curr_src.w = r_src.w;
            curr_dst.w = tile_width;
        }
        curr_dst.y += curr_dst.h;
    }
    ಯದಿ (remaining_dst_h > 0) {
        curr_src.h = remaining_src_h;
        curr_dst.h = remaining_dst_h;
        curr_dst.x = r_dst.x;
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ x = 0; x < cols; ++x) {
            ಯದಿ (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
                ಪ್ರತ್ಯಾಗಮ false;
            }
            curr_dst.x += curr_dst.w;
        }
        ಯದಿ (remaining_dst_w > 0) {
            curr_src.w = remaining_src_w;
            curr_dst.w = remaining_dst_w;
            ಯದಿ (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
                ಪ್ರತ್ಯಾಗಮ false;
            }
        }
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_BlitSurface9Grid(SDL_Surface *src, ಧ್ರುವ SDL_Rect *srcrect, ಪೂರ್ಣಾಙ್ಕ ಎಡ_width, ಪೂರ್ಣಾಙ್ಕ ಬಲ_width, ಪೂರ್ಣಾಙ್ಕ ತುದಿ_height, ಪೂರ್ಣಾಙ್ಕ bottom_height, ಭಿನ್ನ scale, SDL_ScaleMode scaleMode, SDL_Surface *dst, ಧ್ರುವ SDL_Rect *dstrect)
{
    SDL_Rect full_src, full_dst;
    SDL_Rect curr_src, curr_dst;
    ಪೂರ್ಣಾಙ್ಕ dst_ಎಡ_width;
    ಪೂರ್ಣಾಙ್ಕ dst_ಬಲ_width;
    ಪೂರ್ಣಾಙ್ಕ dst_ತುದಿ_height;
    ಪೂರ್ಣಾಙ್ಕ dst_bottom_height;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("dst");
    }

    ಯದಿ (!srcrect) {
        full_src.x = 0;
        full_src.y = 0;
        full_src.w = src->w;
        full_src.h = src->h;
        srcrect = &full_src;
    }

    ಯದಿ (!dstrect) {
        full_dst.x = 0;
        full_dst.y = 0;
        full_dst.w = dst->w;
        full_dst.h = dst->h;
        dstrect = &full_dst;
    }

    ಯದಿ (scale <= 0.0f || scale == 1.0f) {
        dst_ಎಡ_width = ಎಡ_width;
        dst_ಬಲ_width = ಬಲ_width;
        dst_ತುದಿ_height = ತುದಿ_height;
        dst_bottom_height = bottom_height;
    } ಅನ್ಯಥಾ {
        dst_ಎಡ_width = (ಪೂರ್ಣಾಙ್ಕ)SDL_roundf(ಎಡ_width * scale);
        dst_ಬಲ_width = (ಪೂರ್ಣಾಙ್ಕ)SDL_roundf(ಬಲ_width * scale);
        dst_ತುದಿ_height = (ಪೂರ್ಣಾಙ್ಕ)SDL_roundf(ತುದಿ_height * scale);
        dst_bottom_height = (ಪೂರ್ಣಾಙ್ಕ)SDL_roundf(bottom_height * scale);
    }

    // Upper-left corner
    curr_src.x = srcrect->x;
    curr_src.y = srcrect->y;
    curr_src.w = ಎಡ_width;
    curr_src.h = ತುದಿ_height;
    curr_dst.x = dstrect->x;
    curr_dst.y = dstrect->y;
    curr_dst.w = dst_ಎಡ_width;
    curr_dst.h = dst_ತುದಿ_height;
    ಯದಿ (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    // Upper-right corner
    curr_src.x = srcrect->x + srcrect->w - ಬಲ_width;
    curr_src.w = ಬಲ_width;
    curr_dst.x = dstrect->x + dstrect->w - dst_ಬಲ_width;
    curr_dst.w = dst_ಬಲ_width;
    ಯದಿ (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    // Lower-right corner
    curr_src.y = srcrect->y + srcrect->h - bottom_height;
    curr_dst.y = dstrect->y + dstrect->h - dst_bottom_height;
    curr_dst.h = dst_bottom_height;
    ಯದಿ (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    // Lower-left corner
    curr_src.x = srcrect->x;
    curr_src.w = ಎಡ_width;
    curr_dst.x = dstrect->x;
    curr_dst.w = dst_ಎಡ_width;
    ಯದಿ (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    //ಎಡ
    curr_src.y = srcrect->y + ತುದಿ_height;
    curr_src.h = srcrect->h - ತುದಿ_height - bottom_height;
    curr_dst.y = dstrect->y + dst_ತುದಿ_height;
    curr_dst.h = dstrect->h - dst_ತುದಿ_height - dst_bottom_height;
    ಯದಿ (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    //ಬಲ
    curr_src.x = srcrect->x + srcrect->w - ಬಲ_width;
    curr_src.w = ಬಲ_width;
    curr_dst.x = dstrect->x + dstrect->w - dst_ಬಲ_width;
    curr_dst.w = dst_ಬಲ_width;
    ಯದಿ (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    //ತುದಿ
    curr_src.x = srcrect->x + ಎಡ_width;
    curr_src.y = srcrect->y;
    curr_src.w = srcrect->w - ಎಡ_width - ಬಲ_width;
    curr_src.h = ತುದಿ_height;
    curr_dst.x = dstrect->x + dst_ಎಡ_width;
    curr_dst.y = dstrect->y;
    curr_dst.w = dstrect->w - dst_ಎಡ_width - dst_ಬಲ_width;
    curr_dst.h = dst_ತುದಿ_height;
    ಯದಿ (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    // Bottom
    curr_src.y = srcrect->y + srcrect->h - bottom_height;
    curr_dst.y = dstrect->y + dstrect->h - dst_bottom_height;
    curr_dst.h = dst_bottom_height;
    ಯದಿ (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    // Center
    curr_src.x = srcrect->x + ಎಡ_width;
    curr_src.y = srcrect->y + ತುದಿ_height;
    curr_src.w = srcrect->w - ಎಡ_width - ಬಲ_width;
    curr_src.h = srcrect->h - ತುದಿ_height - bottom_height;
    curr_dst.x = dstrect->x + dst_ಎಡ_width;
    curr_dst.y = dstrect->y + dst_ತುದಿ_height;
    curr_dst.w = dstrect->w - dst_ಎಡ_width - dst_ಬಲ_width;
    curr_dst.h = dstrect->h - dst_ತುದಿ_height - dst_bottom_height;
    ಯದಿ (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    ಪ್ರತ್ಯಾಗಮ true;
}

/*
 * Lock a surface to directly access the pixels
 */
bool SDL_LockSurface(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("surface");
    }

    ಯದಿ (!surface->locked) {
#ifdef SDL_HAVE_RLE
        // Perform the lock
        ಯದಿ (surface->internal_flags & SDL_INTERNAL_SURFACE_RLEACCEL) {
            SDL_UnRLESurface(surface);
        }
#endif
    }

    // Increment the surface lock count, for recursive locks
    ++surface->locked;
    surface->flags |= SDL_SURFACE_LOCKED;
    SDL_UpdateSurfaceLockFlag(surface);

    // Ready to go..
    ಪ್ರತ್ಯಾಗಮ true;
}

/*
 * Unlock a previously locked surface
 */
ಶೂನ್ಯ SDL_UnlockSurface(SDL_Surface *surface)
{
    ಯದಿ (!SDL_SurfaceValid(surface)) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    // Only perform an unlock if we are locked
    ಯದಿ (!surface->locked || (--surface->locked > 0)) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    surface->flags &= ~SDL_SURFACE_LOCKED;
    SDL_UpdateSurfaceLockFlag(surface);
}

ಸ್ಥಿರ bool SDL_FlipSurfaceHorizontal(SDL_Surface *surface)
{
    bool isstack;
    Uint8 *row, *a, *b, *tmp;
    ಪೂರ್ಣಾಙ್ಕ i, j, bpp;

    ಯದಿ (SDL_BITSPERPIXEL(surface->format) < 8) {
        // We could implement this if needed, but we'd have to flip sets of bits within a byte
        ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
    }

    ಯದಿ (surface->h <= 0) {
        ಪ್ರತ್ಯಾಗಮ true;
    }

    ಯದಿ (surface->w <= 1) {
        ಪ್ರತ್ಯಾಗಮ true;
    }

    bpp = SDL_BYTESPERPIXEL(surface->format);
    row = (Uint8 *)surface->pixels;
    tmp = SDL_small_alloc(Uint8, surface->pitch, &isstack);
    ಯದಿ (!tmp) {
        ಪ್ರತ್ಯಾಗಮ false;
    }
    ಪ್ರತಿ (i = surface->h; i--; ) {
        a = row;
        b = a + (surface->w - 1) * bpp;
        ಪ್ರತಿ (j = surface->w / 2; j--; ) {
            SDL_memcpy(tmp, a, bpp);
            SDL_memcpy(a, b, bpp);
            SDL_memcpy(b, tmp, bpp);
            a += bpp;
            b -= bpp;
        }
        row += surface->pitch;
    }
    SDL_small_free(tmp, isstack);
    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ bool SDL_FlipSurfaceVertical(SDL_Surface *surface)
{
    bool isstack;
    Uint8 *a, *b, *tmp;
    ಪೂರ್ಣಾಙ್ಕ i;

    ಯದಿ (surface->h <= 1) {
        ಪ್ರತ್ಯಾಗಮ true;
    }

    a = (Uint8 *)surface->pixels;
    b = a + (surface->h - 1) * surface->pitch;
    tmp = SDL_small_alloc(Uint8, surface->pitch, &isstack);
    ಯದಿ (!tmp) {
        ಪ್ರತ್ಯಾಗಮ false;
    }
    ಪ್ರತಿ (i = surface->h / 2; i--; ) {
        SDL_memcpy(tmp, a, surface->pitch);
        SDL_memcpy(a, b, surface->pitch);
        SDL_memcpy(b, tmp, surface->pitch);
        a += surface->pitch;
        b -= surface->pitch;
    }
    SDL_small_free(tmp, isstack);
    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_FlipSurface(SDL_Surface *surface, SDL_FlipMode flip)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("surface");
    }
    ಯದಿ (!surface->pixels) {
        ಪ್ರತ್ಯಾಗಮ true;
    }

    bool result = true;
    ವಿಕಲ್ಪ (flip) {
    ಪಕ್ಷ SDL_FLIP_HORIZONTAL:
        result = SDL_FlipSurfaceHorizontal(surface);
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_FLIP_VERTICAL:
        result = SDL_FlipSurfaceVertical(surface);
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_FLIP_HORIZONTAL_AND_VERTICAL:
        result &= SDL_FlipSurfaceHorizontal(surface);
        result &= SDL_FlipSurfaceVertical(surface);
        ಭಙ್ಗ;
    ಸ್ವಭಾವ:
        result = SDL_InvalidParamError("flip");
        ಭಙ್ಗ;
    }
    ಪ್ರತ್ಯಾಗಮ result;
}

ಸ್ಥಿರ SDL_Surface *SDL_ConvertSurfaceRectAndColorspace(SDL_Surface *surface, ಧ್ರುವ SDL_Rect *rect, SDL_PixelFormat format, SDL_Palette *palette, SDL_Colorspace colorspace, SDL_PropertiesID props)
{
    SDL_Palette *temp_palette = ರಿಕ್ತ;
    SDL_Surface *convert = ರಿಕ್ತ;
    SDL_Colorspace src_colorspace;
    SDL_PropertiesID src_properties;
    Uint32 copy_flags;
    SDL_Color copy_color;
    SDL_Rect bounds;
    bool result;
    bool palette_ck_transform = false;
    Uint8 palette_ck_ಮೌಲ್ಯ = 0;
    Uint8 *palette_saved_alpha = ರಿಕ್ತ;
    ಪೂರ್ಣಾಙ್ಕ palette_saved_alpha_ncolors = 0;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        ಗಚ್ಛ error;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        ಗಚ್ಛ error;
    }

    // Set the bounds of the new surface
    bounds.x = 0;
    bounds.y = 0;
    bounds.w = surface->w;
    bounds.h = surface->h;
    ಯದಿ (rect) {
        bounds.w = rect->w;
        bounds.h = rect->h;
    } ಅನ್ಯಥಾ {
        rect = &bounds;
    }

    // Check for empty destination palette! (results in empty image)
    ಯದಿ (palette) {
        ಪೂರ್ಣಾಙ್ಕ i;
        ಪ್ರತಿ (i = 0; i < palette->ncolors; ++i) {
            ಯದಿ ((palette->colors[i].r != 0xFF) || (palette->colors[i].g != 0xFF) || (palette->colors[i].b != 0xFF)) {
                ಭಙ್ಗ;
            }
        }
        ಯದಿ (i == palette->ncolors) {
            SDL_SetError("Empty destination palette");
            ಗಚ್ಛ error;
        }
    } ಅನ್ಯಥಾ ಯದಿ (SDL_ISPIXELFORMAT_INDEXED(format)) {
        // Create a dither palette for conversion
        temp_palette = SDL_CreatePalette(1 << SDL_BITSPERPIXEL(format));
        ಯದಿ (temp_palette) {
            SDL_DitherPalette(temp_palette);
            palette = temp_palette;
        }
    }

    src_colorspace = surface->colorspace;
    src_properties = surface->props;

    // Create a new surface with the desired format
    ಯದಿ (surface->pixels || SDL_MUSTLOCK(surface)) {
        convert = SDL_CreateSurfaceUninitialized(rect->w, rect->h, format);
    } ಅನ್ಯಥಾ {
        convert = SDL_CreateSurfaceFrom(rect->w, rect->h, format, ರಿಕ್ತ, 0);
    }
    ಯದಿ (!convert) {
        ಗಚ್ಛ error;
    }
    ಯದಿ (SDL_ISPIXELFORMAT_INDEXED(format)) {
        SDL_SetSurfacePalette(convert, palette);
    }

    ಯದಿ (colorspace == SDL_COLORSPACE_UNKNOWN) {
        colorspace = src_colorspace;
    }
    SDL_SetSurfaceColorspace(convert, colorspace);

    ಯದಿ (SDL_ISPIXELFORMAT_FOURCC(format) || SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        ಯದಿ (surface->format == SDL_PIXELFORMAT_MJPG && format == SDL_PIXELFORMAT_MJPG) {
            // Just do a straight pixel copy of the JPEG image
            size_t size = (size_t)surface->pitch;
            convert->pixels = SDL_malloc(size);
            ಯದಿ (!convert->pixels) {
                ಗಚ್ಛ error;
            }
            convert->flags &= ~SDL_SURFACE_PREALLOCATED;
            convert->pitch = surface->pitch;
            SDL_memcpy(convert->pixels, surface->pixels, size);

        } ಅನ್ಯಥಾ ಯದಿ (!SDL_ConvertPixelsAndColorspace(surface->w, surface->h, surface->format, src_colorspace, src_properties, surface->pixels, surface->pitch, convert->format, colorspace, props, convert->pixels, convert->pitch)) {
            ಗಚ್ಛ error;
        }

        // Save the original copy flags
        copy_flags = surface->map.info.flags;

        ಗಚ್ಛ end;
    }

    // Save the original copy flags
    copy_flags = surface->map.info.flags;
    copy_color.r = surface->map.info.r;
    copy_color.g = surface->map.info.g;
    copy_color.b = surface->map.info.b;
    copy_color.a = surface->map.info.a;
    surface->map.info.r = 0xFF;
    surface->map.info.g = 0xFF;
    surface->map.info.b = 0xFF;
    surface->map.info.a = 0xFF;
    surface->map.info.flags = (copy_flags & (SDL_COPY_RLE_COLORKEY | SDL_COPY_RLE_ALPHAKEY));
    SDL_InvalidateMap(&surface->map);

    /* Source surface has a palette with no real alpha (0 or OPAQUE).
     * Destination format has alpha.
     * -> set alpha channel to be opaque */
    ಯದಿ (surface->palette && SDL_ISPIXELFORMAT_ALPHA(format)) {
        bool set_opaque = false;

        bool is_opaque, has_alpha_channel;
        SDL_DetectPalette(surface->palette, &is_opaque, &has_alpha_channel);

        ಯದಿ (is_opaque) {
            ಯದಿ (!has_alpha_channel) {
                set_opaque = true;
            }
        }

        // Set opaque and backup palette alpha values
        ಯದಿ (set_opaque) {
            ಪೂರ್ಣಾಙ್ಕ i;
            palette_saved_alpha_ncolors = surface->palette->ncolors;
            ಯದಿ (palette_saved_alpha_ncolors > 0) {
                palette_saved_alpha = SDL_ರಾಶಿ_alloc(Uint8, palette_saved_alpha_ncolors);
                ಪ್ರತಿ (i = 0; i < palette_saved_alpha_ncolors; i++) {
                    palette_saved_alpha[i] = surface->palette->colors[i].a;
                    surface->palette->colors[i].a = SDL_ALPHA_OPAQUE;
                }
            }
        }
    }

    // Transform colorkey to alpha. for cases where source palette has duplicate values, and colorkey is one of them
    ಯದಿ (copy_flags & SDL_COPY_COLORKEY) {
        ಯದಿ (surface->palette && !palette) {
            palette_ck_transform = true;
            palette_ck_ಮೌಲ್ಯ = surface->palette->colors[surface->map.info.colorkey].a;
            surface->palette->colors[surface->map.info.colorkey].a = SDL_ALPHA_TRANSPARENT;
        }
    }

    ಯದಿ (surface->pixels || SDL_MUSTLOCK(surface)) {
        result = SDL_BlitSurfaceUnchecked(surface, rect, convert, &bounds);
    } ಅನ್ಯಥಾ {
        result = true;
    }

    // Restore colorkey alpha value
    ಯದಿ (palette_ck_transform) {
        surface->palette->colors[surface->map.info.colorkey].a = palette_ck_ಮೌಲ್ಯ;
    }

    // Restore palette alpha values
    ಯದಿ (palette_saved_alpha) {
        ಪೂರ್ಣಾಙ್ಕ i;
        ಪ್ರತಿ (i = 0; i < palette_saved_alpha_ncolors; i++) {
            surface->palette->colors[i].a = palette_saved_alpha[i];
        }
        SDL_ರಾಶಿ_free(palette_saved_alpha);
    }

    // Clean up the original surface, and update converted surface
    convert->map.info.r = copy_color.r;
    convert->map.info.g = copy_color.g;
    convert->map.info.b = copy_color.b;
    convert->map.info.a = copy_color.a;
    convert->map.info.flags =
        (copy_flags &
         ~(SDL_COPY_COLORKEY | SDL_COPY_BLEND | SDL_COPY_RLE_DESIRED | SDL_COPY_RLE_COLORKEY |
           SDL_COPY_RLE_ALPHAKEY));
    surface->map.info.r = copy_color.r;
    surface->map.info.g = copy_color.g;
    surface->map.info.b = copy_color.b;
    surface->map.info.a = copy_color.a;
    surface->map.info.flags = copy_flags;
    SDL_InvalidateMap(&surface->map);

    // SDL_BlitSurfaceUnchecked failed, and so the conversion
    ಯದಿ (!result) {
        ಗಚ್ಛ error;
    }

    ಯದಿ (copy_flags & SDL_COPY_COLORKEY) {
        bool set_colorkey_by_color = false;
        bool convert_colorkey = true;

        ಯದಿ (surface->palette) {
            ಯದಿ (palette &&
                surface->palette->ncolors <= palette->ncolors &&
                (SDL_memcmp(surface->palette->colors, palette->colors,
                            surface->palette->ncolors * ಪರಿಮಾಣ(SDL_Color)) == 0)) {
                // The palette is identical, just set the same colorkey
                SDL_Set_Surface_Color_ಕೀಲಿ(convert, true, surface->map.info.colorkey);
            } ಅನ್ಯಥಾ ಯದಿ (!palette) {
                ಯದಿ (SDL_ISPIXELFORMAT_ALPHA(format)) {
                    // No need to add the colorkey, transparency is in the alpha channel
                } ಅನ್ಯಥಾ {
                    // Only set the colorkey information
                    set_colorkey_by_color = true;
                    convert_colorkey = false;
                }
            } ಅನ್ಯಥಾ {
                set_colorkey_by_color = true;
            }
        } ಅನ್ಯಥಾ {
            set_colorkey_by_color = true;
        }

        ಯದಿ (set_colorkey_by_color) {
            SDL_Surface *tmp;
            SDL_Surface *tmp2;
            ಪೂರ್ಣಾಙ್ಕ converted_colorkey = 0;

            // Create a dummy surface to get the colorkey converted
            tmp = SDL_CreateSurfaceUninitialized(1, 1, surface->format);
            ಯದಿ (!tmp) {
                ಗಚ್ಛ error;
            }

            // Share the palette, if any
            ಯದಿ (surface->palette) {
                SDL_SetSurfacePalette(tmp, surface->palette);
            }

            SDL_FillSurfaceRect(tmp, ರಿಕ್ತ, surface->map.info.colorkey);

            tmp->map.info.flags &= ~SDL_COPY_COLORKEY;

            // Conversion of the colorkey
            tmp2 = SDL_ConvertSurfaceAndColorspace(tmp, format, palette, colorspace, props);
            ಯದಿ (!tmp2) {
                SDL_DestroySurface(tmp);
                ಗಚ್ಛ error;
            }

            // Get the converted colorkey
            SDL_memcpy(&converted_colorkey, tmp2->pixels, tmp2->fmt->bytes_per_pixel);

            SDL_DestroySurface(tmp);
            SDL_DestroySurface(tmp2);

            // Set the converted colorkey on the new surface
            SDL_Set_Surface_Color_ಕೀಲಿ(convert, true, converted_colorkey);

            // This is needed when converting for 3D texture upload
            ಯದಿ (convert_colorkey) {
                SDL_ConvertColorkeyToAlpha(convert, true);
            }
        }
    }

end:
    ಯದಿ (temp_palette) {
        SDL_DestroyPalette(temp_palette);
    }

    SDL_SetSurfaceClipRect(convert, &surface->clip_rect);

    /* Enable alpha blending by default if the new surface has an
     * alpha channel or alpha modulation */
    ಯದಿ (SDL_ISPIXELFORMAT_ALPHA(format) ||
        (copy_flags & SDL_COPY_MODULATE_ALPHA)) {
        SDL_SetSurfaceBlendMode(convert, SDL_BLENDMODE_BLEND);
    }
    ಯದಿ (copy_flags & SDL_COPY_RLE_DESIRED) {
        SDL_SetSurfaceRLE(convert, true);
    }

    // Copy alternate images
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < surface->ಅಂಕೆ_images; ++i) {
        ಯದಿ (!SDL_AddSurfaceAlternateImage(convert, surface->images[i])) {
            ಗಚ್ಛ error;
        }
    }

    // Copy properties
    ಯದಿ (surface->props) {
        ಯದಿ (!SDL_CopyProperties(surface->props, SDL_GetSurfaceProperties(convert))) {
            ಗಚ್ಛ error;
        }

        // Make sure the new surface doesn't reference an old SDL2 surface.
        SDL_ClearProperty(SDL_GetSurfaceProperties(convert), "sdl2-compat.surface2");
    }

    // We're ready to go!
    ಪ್ರತ್ಯಾಗಮ convert;

error:
    ಯದಿ (temp_palette) {
        SDL_DestroyPalette(temp_palette);
    }
    ಯದಿ (convert) {
        SDL_DestroySurface(convert);
    }
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

SDL_Surface *SDL_ConvertSurfaceAndColorspace(SDL_Surface *surface, SDL_PixelFormat format, SDL_Palette *palette, SDL_Colorspace colorspace, SDL_PropertiesID props)
{
    ಪ್ರತ್ಯಾಗಮ SDL_ConvertSurfaceRectAndColorspace(surface, ರಿಕ್ತ, format, palette, colorspace, props);
}

SDL_Surface *SDL_RotateSurface(SDL_Surface *surface, ಭಿನ್ನ angle)
{
    SDL_Surface *rotated = ರಿಕ್ತ;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    SDL_Rect rect_dest;
    ದ್ವಿಗುಣ cangle, sangle;
    SDL_FPoint center = { surface->w * 0.5f, surface->h * 0.5f };
    SDLgfx_rotozoomSurfaceSizeTrig(surface->w, surface->h, angle, &center, &rect_dest, &cangle, &sangle);

    // This function requires a 32-bit surface or 8-bit surface with a colorkey
    ಯದಿ ((SDL_BITSPERPIXEL(surface->format) == 32 && SDL_PIXELLAYOUT(surface->format) == SDL_PACKEDLAYOUT_8888) ||
        (surface->format == SDL_PIXELFORMAT_INDEX8 && SDL_Surface_Has_Color_ಕೀಲಿ(surface))) {
        rotated = SDLgfx_rotateSurface(surface, angle, 1, 0, 0, &rect_dest, cangle, sangle, &center);
    } ಅನ್ಯಥಾ {
        SDL_Surface *convert = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);
        ಯದಿ (convert) {
            SDL_Surface *tmp = SDLgfx_rotateSurface(convert, angle, 1, 0, 0, &rect_dest, cangle, sangle, &center);
            ಯದಿ (tmp) {
                rotated = SDL_ConvertSurfaceAndColorspace(tmp, surface->format, surface->palette, surface->colorspace, surface->props);
                SDL_DestroySurface(tmp);
            }
            SDL_DestroySurface(convert);
        }
    }

    ಯದಿ (rotated) {
        ಯದಿ (SDL_HasProperty(surface->props, SDL_PROP_SURFACE_ROTATION_FLOAT)) {
            ಧ್ರುವ ಭಿನ್ನ rotation = (SDL_Get_ಸಂಖ್ಯೆ_Property(surface->props, SDL_PROP_SURFACE_ROTATION_FLOAT, 0) - angle);
            SDL_SetFloatProperty(SDL_GetSurfaceProperties(rotated), SDL_PROP_SURFACE_ROTATION_FLOAT, rotation);
        }
    }

    ಪ್ರತ್ಯಾಗಮ rotated;
}

SDL_Surface *SDL_DuplicateSurface(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    ಪ್ರತ್ಯಾಗಮ SDL_ConvertSurfaceAndColorspace(surface, surface->format, surface->palette, surface->colorspace, surface->props);
}

SDL_Surface *SDL_ScaleSurface(SDL_Surface *surface, ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, SDL_ScaleMode scaleMode)
{
    SDL_Surface *convert = ರಿಕ್ತ;
    Uint32 copy_flags;
    SDL_Color copy_color;
    bool rc;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        ಗಚ್ಛ error;
    }

    ಯದಿ (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // We can't directly scale a YUV surface (yet!)
        SDL_Surface *tmp = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        ಯದಿ (!tmp) {
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        }

        SDL_Surface *scaled = SDL_ScaleSurface(tmp, width, height, scaleMode);
        SDL_DestroySurface(tmp);
        ಯದಿ (!scaled) {
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        }

        SDL_Surface *result = SDL_ConvertSurfaceAndColorspace(scaled, surface->format, ರಿಕ್ತ, surface->colorspace, surface->props);
        SDL_DestroySurface(scaled);
        ಪ್ರತ್ಯಾಗಮ result;
    }

    ಯದಿ (SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        // Linear scaling requires conversion to RGBA and then slow pixel color lookup
        scaleMode = SDL_SCALEMODE_NEAREST;
    }

    // Create a new surface with the desired size
    ಯದಿ (surface->pixels || SDL_MUSTLOCK(surface)) {
        convert = SDL_CreateSurfaceUninitialized(width, height, surface->format);
    } ಅನ್ಯಥಾ {
        convert = SDL_CreateSurfaceFrom(width, height, surface->format, ರಿಕ್ತ, 0);
    }
    ಯದಿ (!convert) {
        ಗಚ್ಛ error;
    }
    SDL_SetSurfacePalette(convert, surface->palette);
    SDL_SetSurfaceColorspace(convert, surface->colorspace);
    SDL_SetSurfaceRLE(convert, SDL_SurfaceHasRLE(surface));

    ಯದಿ (surface->pixels || SDL_MUSTLOCK(surface)) {
        // Save the original copy flags
        copy_flags = surface->map.info.flags;
        copy_color.r = surface->map.info.r;
        copy_color.g = surface->map.info.g;
        copy_color.b = surface->map.info.b;
        copy_color.a = surface->map.info.a;
        surface->map.info.r = 0xFF;
        surface->map.info.g = 0xFF;
        surface->map.info.b = 0xFF;
        surface->map.info.a = 0xFF;
        surface->map.info.flags = (copy_flags & (SDL_COPY_RLE_COLORKEY | SDL_COPY_RLE_ALPHAKEY));
        SDL_InvalidateMap(&surface->map);

        rc = SDL_BlitSurfaceScaled(surface, ರಿಕ್ತ, convert, ರಿಕ್ತ, scaleMode);

        // Clean up the original surface, and update converted surface
        convert->map.info.r = copy_color.r;
        convert->map.info.g = copy_color.g;
        convert->map.info.b = copy_color.b;
        convert->map.info.a = copy_color.a;
        convert->map.info.flags = (copy_flags & ~(SDL_COPY_RLE_COLORKEY | SDL_COPY_RLE_ALPHAKEY));
        surface->map.info.r = copy_color.r;
        surface->map.info.g = copy_color.g;
        surface->map.info.b = copy_color.b;
        surface->map.info.a = copy_color.a;
        surface->map.info.flags = copy_flags;
        SDL_InvalidateMap(&surface->map);
    } ಅನ್ಯಥಾ {
        rc = true;
    }

    // SDL_BlitSurfaceScaled failed, and so the conversion
    ಯದಿ (!rc) {
        ಗಚ್ಛ error;
    }

    // We're ready to go!
    ಪ್ರತ್ಯಾಗಮ convert;

error:
    ಯದಿ (convert) {
        SDL_DestroySurface(convert);
    }
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

SDL_Surface *SDL_ConvertSurfaceRect(SDL_Surface *surface, ಧ್ರುವ SDL_Rect *rect, SDL_PixelFormat format)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    ಪ್ರತ್ಯಾಗಮ SDL_ConvertSurfaceRectAndColorspace(surface, rect, format, ರಿಕ್ತ, SDL_GetDefaultColorspaceForFormat(format), surface->props);
}

SDL_Surface *SDL_ConvertSurface(SDL_Surface *surface, SDL_PixelFormat format)
{
    ಪ್ರತ್ಯಾಗಮ SDL_ConvertSurfaceRect(surface, ರಿಕ್ತ, format);
}

SDL_Surface *SDL_DuplicatePixels(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, SDL_PixelFormat format, SDL_Colorspace colorspace, ಶೂನ್ಯ *pixels, ಪೂರ್ಣಾಙ್ಕ pitch)
{
    SDL_Surface *surface;
    ಯದಿ (pixels) {
        surface = SDL_CreateSurfaceUninitialized(width, height, format);
    } ಅನ್ಯಥಾ {
        surface = SDL_CreateSurfaceFrom(width, height, format, ರಿಕ್ತ, 0);
    }
    ಯದಿ (!surface) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
    SDL_SetSurfaceColorspace(surface, colorspace);

    ಯದಿ (surface->pixels) {
        ಪೂರ್ಣಾಙ್ಕ length = width * SDL_BYTESPERPIXEL(format);
        Uint8 *src = (Uint8 *)pixels;
        Uint8 *dst = (Uint8 *)surface->pixels;
        ಪೂರ್ಣಾಙ್ಕ rows = height;
        ಯಾವತ್ (rows--) {
            SDL_memcpy(dst, src, length);
            dst += surface->pitch;
            src += pitch;
        }
    }
    ಪ್ರತ್ಯಾಗಮ surface;
}

bool SDL_ConvertPixelsAndColorspace(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height,
                      SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ಧ್ರುವ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಙ್ಕ src_pitch,
                      SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಙ್ಕ dst_pitch)
{
    SDL_Surface src_surface;
    SDL_Surface dst_surface;
    SDL_Rect rect;
    ಶೂನ್ಯ *nonconst_src = (ಶೂನ್ಯ *)src;
    bool result;

    CHECK_PARAM(!src) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!src_pitch) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("src_pitch");
    }
    CHECK_PARAM(!dst) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("dst");
    }
    CHECK_PARAM(!dst_pitch) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("dst_pitch");
    }

    ಯದಿ (src_colorspace == SDL_COLORSPACE_UNKNOWN) {
        src_colorspace = SDL_GetDefaultColorspaceForFormat(src_format);
    }
    ಯದಿ (dst_colorspace == SDL_COLORSPACE_UNKNOWN) {
        dst_colorspace = SDL_GetDefaultColorspaceForFormat(dst_format);
    }

    ಯದಿ (src_format == SDL_PIXELFORMAT_MJPG) {
        ಪ್ರತ್ಯಾಗಮ SDL_ConvertPixels_STB(width, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    }

#ifdef SDL_HAVE_YUV
    ಯದಿ (SDL_ISPIXELFORMAT_FOURCC(src_format) && SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        ಪ್ರತ್ಯಾಗಮ SDL_ConvertPixels_YUV_to_YUV(width, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } ಅನ್ಯಥಾ ಯದಿ (SDL_ISPIXELFORMAT_FOURCC(src_format)) {
        ಪ್ರತ್ಯಾಗಮ SDL_ConvertPixels_YUV_to_RGB(width, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } ಅನ್ಯಥಾ ಯದಿ (SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        ಪ್ರತ್ಯಾಗಮ SDL_ConvertPixels_RGB_to_YUV(width, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    }
#ಅನ್ಯಥಾ
    ಯದಿ (SDL_ISPIXELFORMAT_FOURCC(src_format) || SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("SDL not built with YUV support");
    }
#endif

    // Fast path for same format copy
    ಯದಿ (src_format == dst_format && src_colorspace == dst_colorspace) {
        ಯದಿ (src_pitch == dst_pitch) {
            SDL_memcpy(dst, src, height * src_pitch);
        } ಅನ್ಯಥಾ {
            ಪೂರ್ಣಾಙ್ಕ i;
            ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ bpp = SDL_BYTESPERPIXEL(src_format);
            width *= bpp;
            ಪ್ರತಿ (i = height; i--;) {
                SDL_memcpy(dst, src, width);
                src = (ಧ್ರುವ Uint8 *)src + src_pitch;
                dst = (Uint8 *)dst + dst_pitch;
            }
        }
        ಪ್ರತ್ಯಾಗಮ true;
    }

    ಯದಿ (!SDL_InitializeSurface(&src_surface, width, height, src_format, src_colorspace, src_properties, nonconst_src, src_pitch, true)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }
    SDL_SetSurfaceBlendMode(&src_surface, SDL_BLENDMODE_NONE);

    ಯದಿ (!SDL_InitializeSurface(&dst_surface, width, height, dst_format, dst_colorspace, dst_properties, dst, dst_pitch, true)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    // Set up the rect and go!
    rect.x = 0;
    rect.y = 0;
    rect.w = width;
    rect.h = height;
    result = SDL_BlitSurfaceUnchecked(&src_surface, &rect, &dst_surface, &rect);

    SDL_DestroySurface(&src_surface);
    SDL_DestroySurface(&dst_surface);

    ಪ್ರತ್ಯಾಗಮ result;
}

bool SDL_ConvertPixels(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, SDL_PixelFormat src_format, ಧ್ರುವ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಙ್ಕ src_pitch, SDL_PixelFormat dst_format, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಙ್ಕ dst_pitch)
{
    ಪ್ರತ್ಯಾಗಮ SDL_ConvertPixelsAndColorspace(width, height,
                      src_format, SDL_COLORSPACE_UNKNOWN, 0, src, src_pitch,
                      dst_format, SDL_COLORSPACE_UNKNOWN, 0, dst, dst_pitch);
}

/*
 * Premultiply the alpha on a block of pixels
 *
 * Here are some ideas for optimization:
 * https://github.com/Wizermil/premultiply_alpha/tree/master/premultiply_alpha
 * https://developer.arm.com/documentation/101964/0201/Pre-multiplied-alpha-channel-data
 */

ಸ್ಥಿರ ಶೂನ್ಯ SDL_PremultiplyAlpha_AXYZ8888(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, ಧ್ರುವ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಙ್ಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಙ್ಕ dst_pitch)
{
    ಪೂರ್ಣಾಙ್ಕ c;
    Uint32 srcpixel;
    Uint32 srcR, srcG, srcB, srcA;
    Uint32 dstpixel;
    Uint32 dstR, dstG, dstB, dstA;

    ಯಾವತ್ (height--) {
        ಧ್ರುವ Uint32 *src_px = (ಧ್ರುವ Uint32 *)src;
        Uint32 *dst_px = (Uint32 *)dst;
        ಪ್ರತಿ (c = width; c; --c) {
            // Component bytes extraction.
            srcpixel = *src_px++;
            RGBA_FROM_ARGB8888(srcpixel, srcR, srcG, srcB, srcA);

            // Alpha pre-multiplication of each component.
            dstA = srcA;
            dstR = (srcA * srcR) / 255;
            dstG = (srcA * srcG) / 255;
            dstB = (srcA * srcB) / 255;

            // ARGB8888 pixel recomposition.
            ARGB8888_FROM_RGBA(dstpixel, dstR, dstG, dstB, dstA);
            *dst_px++ = dstpixel;
        }
        src = (ಧ್ರುವ Uint8 *)src + src_pitch;
        dst = (Uint8 *)dst + dst_pitch;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ SDL_PremultiplyAlpha_XYZA8888(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, ಧ್ರುವ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಙ್ಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಙ್ಕ dst_pitch)
{
    ಪೂರ್ಣಾಙ್ಕ c;
    Uint32 srcpixel;
    Uint32 srcR, srcG, srcB, srcA;
    Uint32 dstpixel;
    Uint32 dstR, dstG, dstB, dstA;

    ಯಾವತ್ (height--) {
        ಧ್ರುವ Uint32 *src_px = (ಧ್ರುವ Uint32 *)src;
        Uint32 *dst_px = (Uint32 *)dst;
        ಪ್ರತಿ (c = width; c; --c) {
            // Component bytes extraction.
            srcpixel = *src_px++;
            RGBA_FROM_RGBA8888(srcpixel, srcR, srcG, srcB, srcA);

            // Alpha pre-multiplication of each component.
            dstA = srcA;
            dstR = (srcA * srcR) / 255;
            dstG = (srcA * srcG) / 255;
            dstB = (srcA * srcB) / 255;

            // RGBA8888 pixel recomposition.
            RGBA8888_FROM_RGBA(dstpixel, dstR, dstG, dstB, dstA);
            *dst_px++ = dstpixel;
        }
        src = (ಧ್ರುವ Uint8 *)src + src_pitch;
        dst = (Uint8 *)dst + dst_pitch;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ SDL_PremultiplyAlpha_AXYZ128(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, ಧ್ರುವ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಙ್ಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಙ್ಕ dst_pitch)
{
    ಪೂರ್ಣಾಙ್ಕ c;
    ಭಿನ್ನ flR, flG, flB, flA;

    ಯಾವತ್ (height--) {
        ಧ್ರುವ ಭಿನ್ನ *src_px = (ಧ್ರುವ ಭಿನ್ನ *)src;
        ಭಿನ್ನ *dst_px = (ಭಿನ್ನ *)dst;
        ಪ್ರತಿ (c = width; c; --c) {
            flA = *src_px++;
            flR = *src_px++;
            flG = *src_px++;
            flB = *src_px++;

            // Alpha pre-multiplication of each component.
            flR *= flA;
            flG *= flA;
            flB *= flA;

            *dst_px++ = flA;
            *dst_px++ = flR;
            *dst_px++ = flG;
            *dst_px++ = flB;
        }
        src = (ಧ್ರುವ Uint8 *)src + src_pitch;
        dst = (Uint8 *)dst + dst_pitch;
    }
}

ಸ್ಥಿರ bool SDL_PremultiplyAlphaPixelsAndColorspace(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ಧ್ರುವ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಙ್ಕ src_pitch, SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಙ್ಕ dst_pitch, bool linear)
{
    SDL_Surface *convert = ರಿಕ್ತ;
    ಶೂನ್ಯ *final_dst = dst;
    ಪೂರ್ಣಾಙ್ಕ final_dst_pitch = dst_pitch;
    SDL_PixelFormat format;
    SDL_Colorspace colorspace;
    bool result = false;

    CHECK_PARAM(!src) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!src_pitch) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("src_pitch");
    }
    CHECK_PARAM(!dst) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("dst");
    }
    CHECK_PARAM(!dst_pitch) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("dst_pitch");
    }

    // Use a high precision format if we're converting to linear colorspace or using high precision pixel formats
    ಯದಿ (linear ||
        SDL_ISPIXELFORMAT_10BIT(src_format) || SDL_BITSPERPIXEL(src_format) > 32 ||
        SDL_ISPIXELFORMAT_10BIT(dst_format) || SDL_BITSPERPIXEL(dst_format) > 32) {
        ಯದಿ (src_format == SDL_PIXELFORMAT_ARGB128_FLOAT ||
            src_format == SDL_PIXELFORMAT_ABGR128_FLOAT) {
            format = src_format;
        } ಅನ್ಯಥಾ {
            format = SDL_PIXELFORMAT_ARGB128_FLOAT;
        }
    } ಅನ್ಯಥಾ {
        ಯದಿ (src_format == SDL_PIXELFORMAT_ARGB8888 ||
            src_format == SDL_PIXELFORMAT_ABGR8888 ||
            src_format == SDL_PIXELFORMAT_RGBA8888 ||
            src_format == SDL_PIXELFORMAT_BGRA8888) {
            format = src_format;
        } ಅನ್ಯಥಾ {
            format = SDL_PIXELFORMAT_ARGB8888;
        }
    }
    ಯದಿ (linear) {
        colorspace = SDL_COLORSPACE_SRGB_LINEAR;
    } ಅನ್ಯಥಾ {
        colorspace = SDL_COLORSPACE_SRGB;
    }

    ಯದಿ (src_format != format || src_colorspace != colorspace) {
        convert = SDL_CreateSurfaceUninitialized(width, height, format);
        ಯದಿ (!convert) {
            ಗಚ್ಛ done;
        }
        ಯದಿ (!SDL_ConvertPixelsAndColorspace(width, height, src_format, src_colorspace, src_properties, src, src_pitch, format, colorspace, 0, convert->pixels, convert->pitch)) {
            ಗಚ್ಛ done;
        }

        src = convert->pixels;
        src_pitch = convert->pitch;
        dst = convert->pixels;
        dst_pitch = convert->pitch;

    } ಅನ್ಯಥಾ ಯದಿ (dst_format != format || dst_colorspace != colorspace) {
        convert = SDL_CreateSurfaceUninitialized(width, height, format);
        ಯದಿ (!convert) {
            ಗಚ್ಛ done;
        }
        dst = convert->pixels;
        dst_pitch = convert->pitch;
    }

    ವಿಕಲ್ಪ (format) {
    ಪಕ್ಷ SDL_PIXELFORMAT_ARGB8888:
    ಪಕ್ಷ SDL_PIXELFORMAT_ABGR8888:
        SDL_PremultiplyAlpha_AXYZ8888(width, height, src, src_pitch, dst, dst_pitch);
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_PIXELFORMAT_RGBA8888:
    ಪಕ್ಷ SDL_PIXELFORMAT_BGRA8888:
        SDL_PremultiplyAlpha_XYZA8888(width, height, src, src_pitch, dst, dst_pitch);
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_PIXELFORMAT_ARGB128_FLOAT:
    ಪಕ್ಷ SDL_PIXELFORMAT_ABGR128_FLOAT:
        SDL_PremultiplyAlpha_AXYZ128(width, height, src, src_pitch, dst, dst_pitch);
        ಭಙ್ಗ;
    ಸ್ವಭಾವ:
        SDL_SetError("Unexpected internal pixel format");
        ಗಚ್ಛ done;
    }

    ಯದಿ (dst != final_dst) {
        ಯದಿ (!SDL_ConvertPixelsAndColorspace(width, height, format, colorspace, 0, convert->pixels, convert->pitch, dst_format, dst_colorspace, dst_properties, final_dst, final_dst_pitch)) {
            ಗಚ್ಛ done;
        }
    }
    result = true;

done:
    ಯದಿ (convert) {
        SDL_DestroySurface(convert);
    }
    ಪ್ರತ್ಯಾಗಮ result;
}

bool SDL_PremultiplyAlpha(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height,
                         SDL_PixelFormat src_format, ಧ್ರುವ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಙ್ಕ src_pitch,
                         SDL_PixelFormat dst_format, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಙ್ಕ dst_pitch, bool linear)
{
    SDL_Colorspace src_colorspace = SDL_GetDefaultColorspaceForFormat(src_format);
    SDL_Colorspace dst_colorspace = SDL_GetDefaultColorspaceForFormat(dst_format);

    ಪ್ರತ್ಯಾಗಮ SDL_PremultiplyAlphaPixelsAndColorspace(width, height, src_format, src_colorspace, 0, src, src_pitch, dst_format, dst_colorspace, 0, dst, dst_pitch, linear);
}

bool SDL_PremultiplySurfaceAlpha(SDL_Surface *surface, bool linear)
{
    SDL_Colorspace colorspace;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("surface");
    }

    colorspace = surface->colorspace;

    ಪ್ರತ್ಯಾಗಮ SDL_PremultiplyAlphaPixelsAndColorspace(surface->w, surface->h, surface->format, colorspace, surface->props, surface->pixels, surface->pitch, surface->format, colorspace, surface->props, surface->pixels, surface->pitch, linear);
}

bool SDL_ClearSurface(SDL_Surface *surface, ಭಿನ್ನ r, ಭಿನ್ನ g, ಭಿನ್ನ b, ಭಿನ್ನ a)
{
    SDL_Rect clip_rect;
    bool result = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("surface");
    }

    SDL_GetSurfaceClipRect(surface, &clip_rect);
    SDL_SetSurfaceClipRect(surface, ರಿಕ್ತ);

    ಯದಿ (!SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_BYTESPERPIXEL(surface->format) <= ಪರಿಮಾಣ(Uint32)) {
        Uint32 color;

        color = SDL_MapSurfaceRGBA(surface,
                    (Uint8)SDL_roundf(SDL_clamp(r, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(g, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(b, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(a, 0.0f, 1.0f) * 255.0f));
        result = SDL_FillSurfaceRect(surface, ರಿಕ್ತ, color);
    } ಅನ್ಯಥಾ ಯದಿ (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // We can't directly set an RGB value on a YUV surface
        SDL_Surface *tmp = SDL_CreateSurfaceUninitialized(surface->w, surface->h, SDL_PIXELFORMAT_ARGB8888);
        ಯದಿ (!tmp) {
            ಗಚ್ಛ done;
        }

        ಯದಿ (SDL_ClearSurface(tmp, r, g, b, a)) {
            result = SDL_ConvertPixelsAndColorspace(surface->w, surface->h, tmp->format, tmp->colorspace, tmp->props, tmp->pixels, tmp->pitch, surface->format, surface->colorspace, surface->props, surface->pixels, surface->pitch);
        }
        SDL_DestroySurface(tmp);
    } ಅನ್ಯಥಾ {
        // Take advantage of blit color conversion
        SDL_Surface *tmp = SDL_CreateSurfaceUninitialized(1, 1, SDL_PIXELFORMAT_RGBA128_FLOAT);
        ಯದಿ (!tmp) {
            ಗಚ್ಛ done;
        }
        SDL_SetSurfaceColorspace(tmp, surface->colorspace);
        SDL_SetSurfaceBlendMode(tmp, SDL_BLENDMODE_NONE);

        ಭಿನ್ನ *pixels = (ಭಿನ್ನ *)tmp->pixels;
        pixels[0] = r;
        pixels[1] = g;
        pixels[2] = b;
        pixels[3] = a;

        result = SDL_BlitSurfaceScaled(tmp, ರಿಕ್ತ, surface, ರಿಕ್ತ, SDL_SCALEMODE_NEAREST);
        SDL_DestroySurface(tmp);
    }

done:
    SDL_SetSurfaceClipRect(surface, &clip_rect);

    ಪ್ರತ್ಯಾಗಮ result;
}

Uint32 SDL_MapSurfaceRGB(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b)
{
    ಪ್ರತ್ಯಾಗಮ SDL_MapSurfaceRGBA(surface, r, g, b, SDL_ALPHA_OPAQUE);
}

Uint32 SDL_MapSurfaceRGBA(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        ಪ್ರತ್ಯಾಗಮ true;
    }
    ಪ್ರತ್ಯಾಗಮ SDL_MapRGBA(surface->fmt, surface->palette, r, g, b, a);
}

// This function Copyright 2023 Collabora Ltd., contributed to SDL under the ZLib license
bool SDL_ReadSurfacePixel(SDL_Surface *surface, ಪೂರ್ಣಾಙ್ಕ x, ಪೂರ್ಣಾಙ್ಕ y, Uint8 *r, Uint8 *g, Uint8 *b, Uint8 *a)
{
    Uint32 pixel = 0;
    size_t bytes_per_pixel;
    Uint8 unused;
    Uint8 *p;
    bool result = false;

    ಯದಿ (r) {
        *r = 0;
    } ಅನ್ಯಥಾ {
        r = &unused;
    }

    ಯದಿ (g) {
        *g = 0;
    } ಅನ್ಯಥಾ {
        g = &unused;
    }

    ಯದಿ (b) {
        *b = 0;
    } ಅನ್ಯಥಾ {
        b = &unused;
    }

    ಯದಿ (a) {
        *a = 0;
    } ಅನ್ಯಥಾ {
        a = &unused;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("y");
    }

    bytes_per_pixel = SDL_BYTESPERPIXEL(surface->format);

    ಯದಿ (SDL_MUSTLOCK(surface)) {
        ಯದಿ (!SDL_LockSurface(surface)) {
            ಪ್ರತ್ಯಾಗಮ false;
        }
    }

    p = (Uint8 *)surface->pixels + y * surface->pitch + x * bytes_per_pixel;

    ಯದಿ (bytes_per_pixel <= ಪರಿಮಾಣ(pixel) &&
        !SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_COLORSPACEPRIMARIES(surface->colorspace) == SDL_COLOR_PRIMARIES_BT709) {
        /* Fill the appropriate number of least-significant bytes of pixel,
         * leaving the most-significant bytes set to zero */
#ಯದಿ SDL_BYTEORDER == SDL_BIG_ENDIAN
        SDL_memcpy(((Uint8 *)&pixel) + (ಪರಿಮಾಣ(pixel) - bytes_per_pixel), p, bytes_per_pixel);
#ಅನ್ಯಥಾ
        SDL_memcpy(&pixel, p, bytes_per_pixel);
#endif
        SDL_GetRGBA(pixel, surface->fmt, surface->palette, r, g, b, a);
        result = true;
    } ಅನ್ಯಥಾ ಯದಿ (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // FIXME: We need code to extract a single macroblock from a YUV surface
        SDL_Surface *converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        ಯದಿ (converted) {
            result = SDL_ReadSurfacePixel(converted, x, y, r, g, b, a);
            SDL_DestroySurface(converted);
        }
    } ಅನ್ಯಥಾ {
        // This is really slow, but it gets the job done
        Uint8 rgba[4];

        ಯದಿ (SDL_ConvertPixelsAndColorspace(1, 1, surface->format, surface->colorspace, surface->props, p, surface->pitch, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, rgba, ಪರಿಮಾಣ(rgba))) {
            *r = rgba[0];
            *g = rgba[1];
            *b = rgba[2];
            *a = rgba[3];
            result = true;
        }
    }

    ಯದಿ (SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }
    ಪ್ರತ್ಯಾಗಮ result;
}

bool SDL_ReadSurfacePixelFloat(SDL_Surface *surface, ಪೂರ್ಣಾಙ್ಕ x, ಪೂರ್ಣಾಙ್ಕ y, ಭಿನ್ನ *r, ಭಿನ್ನ *g, ಭಿನ್ನ *b, ಭಿನ್ನ *a)
{
    ಭಿನ್ನ unused;
    bool result = false;

    ಯದಿ (r) {
        *r = 0.0f;
    } ಅನ್ಯಥಾ {
        r = &unused;
    }

    ಯದಿ (g) {
        *g = 0.0f;
    } ಅನ್ಯಥಾ {
        g = &unused;
    }

    ಯದಿ (b) {
        *b = 0.0f;
    } ಅನ್ಯಥಾ {
        b = &unused;
    }

    ಯದಿ (a) {
        *a = 0.0f;
    } ಅನ್ಯಥಾ {
        a = &unused;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("y");
    }

    ಯದಿ (SDL_BYTESPERPIXEL(surface->format) <= ಪರಿಮಾಣ(Uint32) &&
        !SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_COLORSPACEPRIMARIES(surface->colorspace) == SDL_COLOR_PRIMARIES_BT709) {
        Uint8 r8, g8, b8, a8;

        ಯದಿ (SDL_ReadSurfacePixel(surface, x, y, &r8, &g8, &b8, &a8)) {
            *r = (ಭಿನ್ನ)r8 / 255.0f;
            *g = (ಭಿನ್ನ)g8 / 255.0f;
            *b = (ಭಿನ್ನ)b8 / 255.0f;
            *a = (ಭಿನ್ನ)a8 / 255.0f;
            result = true;
        }
    } ಅನ್ಯಥಾ ಯದಿ (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // FIXME: We need code to extract a single macroblock from a YUV surface
        SDL_Surface *converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        ಯದಿ (converted) {
            result = SDL_ReadSurfacePixelFloat(converted, x, y, r, g, b, a);
            SDL_DestroySurface(converted);
        }
    } ಅನ್ಯಥಾ {
        // This is really slow, but it gets the job done
        ಭಿನ್ನ rgba[4];
        Uint8 *p;

        ಯದಿ (SDL_MUSTLOCK(surface)) {
            ಯದಿ (!SDL_LockSurface(surface)) {
                ಪ್ರತ್ಯಾಗಮ false;
            }
        }

        p = (Uint8 *)surface->pixels + y * surface->pitch + x * SDL_BYTESPERPIXEL(surface->format);

        ಯದಿ (surface->format == SDL_PIXELFORMAT_RGBA128_FLOAT) {
            SDL_memcpy(rgba, p, ಪರಿಮಾಣ(rgba));
            result = true;
        } ಅನ್ಯಥಾ {
            SDL_Colorspace src_colorspace = surface->colorspace;
            SDL_Colorspace dst_colorspace = (src_colorspace == SDL_COLORSPACE_SRGB_LINEAR ? SDL_COLORSPACE_SRGB_LINEAR : SDL_COLORSPACE_SRGB);

            ಯದಿ (SDL_ConvertPixelsAndColorspace(1, 1, surface->format, src_colorspace, surface->props, p, surface->pitch, SDL_PIXELFORMAT_RGBA128_FLOAT, dst_colorspace, 0, rgba, ಪರಿಮಾಣ(rgba))) {
                result = true;
            }
        }

        ಯದಿ (result) {
            *r = rgba[0];
            *g = rgba[1];
            *b = rgba[2];
            *a = rgba[3];
        }

        ಯದಿ (SDL_MUSTLOCK(surface)) {
            SDL_UnlockSurface(surface);
        }
    }
    ಪ್ರತ್ಯಾಗಮ result;
}

bool SDL_WriteSurfacePixel(SDL_Surface *surface, ಪೂರ್ಣಾಙ್ಕ x, ಪೂರ್ಣಾಙ್ಕ y, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    Uint32 pixel = 0;
    size_t bytes_per_pixel;
    Uint8 *p;
    bool result = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("y");
    }

    bytes_per_pixel = SDL_BYTESPERPIXEL(surface->format);

    ಯದಿ (SDL_MUSTLOCK(surface)) {
        ಯದಿ (!SDL_LockSurface(surface)) {
            ಪ್ರತ್ಯಾಗಮ false;
        }
    }

    p = (Uint8 *)surface->pixels + y * surface->pitch + x * bytes_per_pixel;

    ಯದಿ (bytes_per_pixel <= ಪರಿಮಾಣ(pixel) && !SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        pixel = SDL_MapRGBA(surface->fmt, surface->palette, r, g, b, a);
#ಯದಿ SDL_BYTEORDER == SDL_BIG_ENDIAN
        SDL_memcpy(p, ((Uint8 *)&pixel) + (ಪರಿಮಾಣ(pixel) - bytes_per_pixel), bytes_per_pixel);
#ಅನ್ಯಥಾ
        SDL_memcpy(p, &pixel, bytes_per_pixel);
#endif
        result = true;
    } ಅನ್ಯಥಾ ಯದಿ (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        result = SDL_Unsupported();
    } ಅನ್ಯಥಾ {
        // This is really slow, but it gets the job done
        Uint8 rgba[4];

        rgba[0] = r;
        rgba[1] = g;
        rgba[2] = b;
        rgba[3] = a;
        result = SDL_ConvertPixelsAndColorspace(1, 1, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, rgba, ಪರಿಮಾಣ(rgba), surface->format, surface->colorspace, surface->props, p, surface->pitch);
    }

    ಯದಿ (SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }
    ಪ್ರತ್ಯಾಗಮ result;
}

bool SDL_WriteSurfacePixelFloat(SDL_Surface *surface, ಪೂರ್ಣಾಙ್ಕ x, ಪೂರ್ಣಾಙ್ಕ y, ಭಿನ್ನ r, ಭಿನ್ನ g, ಭಿನ್ನ b, ಭಿನ್ನ a)
{
    bool result = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("y");
    }

    ಯದಿ (SDL_BYTESPERPIXEL(surface->format) <= ಪರಿಮಾಣ(Uint32) && !SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        Uint8 r8, g8, b8, a8;

        r8 = (Uint8)SDL_round(SDL_clamp(r, 0.0f, 1.0f) * 255.0f);
        g8 = (Uint8)SDL_round(SDL_clamp(g, 0.0f, 1.0f) * 255.0f);
        b8 = (Uint8)SDL_round(SDL_clamp(b, 0.0f, 1.0f) * 255.0f);
        a8 = (Uint8)SDL_round(SDL_clamp(a, 0.0f, 1.0f) * 255.0f);
        ಯದಿ (SDL_WriteSurfacePixel(surface, x, y, r8, g8, b8, a8)) {
            result = true;
        }
    } ಅನ್ಯಥಾ ಯದಿ (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        result = SDL_Unsupported();
    } ಅನ್ಯಥಾ {
        // This is really slow, but it gets the job done
        ಭಿನ್ನ rgba[4];
        Uint8 *p;

        ಯದಿ (SDL_MUSTLOCK(surface)) {
            ಯದಿ (!SDL_LockSurface(surface)) {
                ಪ್ರತ್ಯಾಗಮ false;
            }
        }

        p = (Uint8 *)surface->pixels + y * surface->pitch + x * SDL_BYTESPERPIXEL(surface->format);

        rgba[0] = r;
        rgba[1] = g;
        rgba[2] = b;
        rgba[3] = a;

        ಯದಿ (surface->format == SDL_PIXELFORMAT_RGBA128_FLOAT) {
            SDL_memcpy(p, rgba, ಪರಿಮಾಣ(rgba));
            result = true;
        } ಅನ್ಯಥಾ {
            SDL_Colorspace dst_colorspace = surface->colorspace;
            SDL_Colorspace src_colorspace = (dst_colorspace == SDL_COLORSPACE_SRGB_LINEAR ? SDL_COLORSPACE_SRGB_LINEAR : SDL_COLORSPACE_SRGB);

            result = SDL_ConvertPixelsAndColorspace(1, 1, SDL_PIXELFORMAT_RGBA128_FLOAT, src_colorspace, 0, rgba, ಪರಿಮಾಣ(rgba), surface->format, dst_colorspace, surface->props, p, surface->pitch);
        }

        ಯದಿ (SDL_MUSTLOCK(surface)) {
            SDL_UnlockSurface(surface);
        }
    }
    ಪ್ರತ್ಯಾಗಮ result;
}

/*
 * Free a surface created by the above function.
 */
ಶೂನ್ಯ SDL_DestroySurface(SDL_Surface *surface)
{
    ಯದಿ (!SDL_SurfaceValid(surface)) {
        ಪ್ರತ್ಯಾಗಮ;
    }
    ಯದಿ (surface->internal_flags & SDL_INTERNAL_SURFACE_DONTFREE) {
        ಪ್ರತ್ಯಾಗಮ;
    }
    ಯದಿ (--surface->refcount > 0) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    SDL_RemoveSurfaceAlternateImages(surface);

    SDL_DestroyProperties(surface->props);

    SDL_InvalidateMap(&surface->map);

    ಯಾವತ್ (surface->locked > 0) {
        SDL_UnlockSurface(surface);
    }
#ifdef SDL_HAVE_RLE
    ಯದಿ (surface->internal_flags & SDL_INTERNAL_SURFACE_RLEACCEL) {
        SDL_UnRLESurface(surface);
    }
#endif
    SDL_SetSurfacePalette(surface, ರಿಕ್ತ);

    ಯದಿ (surface->flags & SDL_SURFACE_PREALLOCATED) {
        // Don't free
    } ಅನ್ಯಥಾ ಯದಿ (surface->flags & SDL_SURFACE_SIMD_ALIGNED) {
        // Free aligned
        SDL_aligned_free(surface->pixels);
    } ಅನ್ಯಥಾ {
        // Normal
        SDL_free(surface->pixels);
    }

    surface->reserved = ರಿಕ್ತ;

    ಯದಿ (!(surface->internal_flags & SDL_INTERNAL_SURFACE_ರಾಶಿ)) {
        SDL_free(surface);
    }
}

SDL_Surface *SDL_LoadSurface_IO(SDL_IOStream *src, bool closeio)
{
    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    ಯದಿ (SDL_IsBMP(src)) {
        ಪ್ರತ್ಯಾಗಮ SDL_LoadBMP_IO(src, closeio);
    } ಅನ್ಯಥಾ ಯದಿ (SDL_IsPNG(src)) {
        ಪ್ರತ್ಯಾಗಮ SDL_LoadPNG_IO(src, closeio);
    } ಅನ್ಯಥಾ ಯದಿ (SDL_IsJPG(src)) {
        ಪ್ರತ್ಯಾಗಮ SDL_LoadJPG_IO(src, closeio);
    } ಅನ್ಯಥಾ {
        ಯದಿ (closeio) {
            SDL_CloseIO(src);
        }
        SDL_SetError("Unsupported image format");
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
}

SDL_Surface *SDL_LoadSurface(ಧ್ರುವ ವರ್ಣ *file)
{
    SDL_IOStream *stream = SDL_IOFromFile(file, "rb");
    ಯದಿ (!stream) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    ಪ್ರತ್ಯಾಗಮ SDL_LoadSurface_IO(stream, true);
}
