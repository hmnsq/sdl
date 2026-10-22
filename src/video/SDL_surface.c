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
#অন্তর্ভাব "SDL_internal.h"

#অন্তর্ভাব "SDL_sysvideo.h"
#অন্তর্ভাব "SDL_video_c.h"
#অন্তর্ভাব "SDL_RLEaccel_c.h"
#অন্তর্ভাব "SDL_pixels_c.h"
#অন্তর্ভাব "SDL_rotate.h"
#অন্তর্ভাব "SDL_stb_c.h"
#অন্তর্ভাব "SDL_yuv_c.h"
#অন্তর্ভাব "../render/SDL_sysrender.h"

#অন্তর্ভাব "SDL_surface_c.h"


// Check to make sure we can safely check multiplication of surface w and pitch and it won't overflow size_t
SDL_COMPILE_TIME_ASSERT(surface_আকার_assumptions,
                        আকার(পূর্ণসংখ্যা) == আকার(Sint32) && আকার(size_t) >= আকার(Sint32));

SDL_COMPILE_TIME_ASSERT(can_indicate_overflow, SDL_আকার_MAX > SDL_MAX_SINT32);

// Magic!
স্থির অক্ষর SDL_surface_magic;

// Public routines

bool SDL_SurfaceValid(SDL_Surface *surface)
{
    ফেরত (surface && surface->reserved == &SDL_surface_magic);
}

শূন্য SDL_UpdateSurfaceLockFlag(SDL_Surface *surface)
{
    // We need to mark the surface as needing unlock while locked
    যদি ((surface->flags & SDL_SURFACE_LOCKED) ||
        (surface->internal_flags & SDL_INTERNAL_SURFACE_RLEACCEL)) {
        surface->flags |= SDL_SURFACE_LOCK_NEEDED;
    } অন্যথা {
        surface->flags &= ~SDL_SURFACE_LOCK_NEEDED;
    }
}

/*
 * Calculate the pad-aligned scanline width of a surface.
 *
 * for FOURCC, use SDL_CalculateYUVSize()
 */
স্থির bool SDL_CalculateRGBSize(Uint32 format, size_t width, size_t height, size_t *আকার_2, size_t *pitch, bool minimal)
{
    যদি (SDL_BITSPERPIXEL(format) >= 8) {
        যদি (!SDL_আকার_mul_check_overflow(width, SDL_BYTESPERPIXEL(format), pitch)) {
            ফেরত SDL_SetError("width * bpp would overflow");
        }
    } অন্যথা {
        যদি (!SDL_আকার_mul_check_overflow(width, SDL_BITSPERPIXEL(format), pitch)) {
            ফেরত SDL_SetError("width * bpp would overflow");
        }
        যদি (!SDL_আকার_add_check_overflow(*pitch, 7, pitch)) {
            ফেরত SDL_SetError("aligning pitch would overflow");
        }
        *pitch /= 8;
    }
    যদি (!minimal) {
        // 4-byte aligning for speed
        যদি (!SDL_আকার_add_check_overflow(*pitch, 3, pitch)) {
            ফেরত SDL_SetError("aligning pitch would overflow");
        }
        *pitch &= ~3;
    }

    যদি (!SDL_আকার_mul_check_overflow(height, *pitch, আকার_2)) {
        ফেরত SDL_SetError("height * pitch would overflow");
    }

    ফেরত true;
}

bool SDL_Calculate_Surface_আকার(SDL_PixelFormat format, পূর্ণসংখ্যা width, পূর্ণসংখ্যা height, size_t *আকার_2, size_t *pitch, bool minimalPitch)
{
    size_t p = 0, sz = 0;

    যদি (আকার_2) {
        *আকার_2 = 0;
    }

    যদি (pitch) {
        *pitch = 0;
    }

    যদি (SDL_ISPIXELFORMAT_FOURCC(format)) {
        যদি (format == SDL_PIXELFORMAT_MJPG) {
            // We don't know in advance what it will be, we'll figure it out later.
            ফেরত true;
        }

        যদি (!SDL_CalculateYUVSize(format, width, height, &sz, &p)) {
            // Overflow...
            ফেরত false;
        }
    } অন্যথা {
        যদি (!SDL_CalculateRGBSize(format, width, height, &sz, &p, minimalPitch)) {
            // Overflow...
            ফেরত false;
        }
    }

    যদি (আকার_2) {
        *আকার_2 = sz;
    }

    যদি (pitch) {
        *pitch = p;
    }

    ফেরত true;
}

স্থির bool SDL_InitializeSurface(SDL_Surface *surface, পূর্ণসংখ্যা width, পূর্ণসংখ্যা height, SDL_PixelFormat format, SDL_Colorspace colorspace, SDL_PropertiesID props, শূন্য *pixels, পূর্ণসংখ্যা pitch, bool onstack)
{
    SDL_zerop(surface);

    surface->flags = SDL_SURFACE_PREALLOCATED;
    surface->format = format;
    surface->w = width;
    surface->h = height;
    surface->pixels = pixels;
    surface->pitch = pitch;
    surface->reserved = &SDL_surface_magic;

    যদি (onstack) {
        surface->internal_flags |= SDL_INTERNAL_SURFACE_স্তূপ;
    }

    surface->fmt = SDL_GetPixelFormatDetails(format);
    যদি (!surface->fmt) {
        SDL_DestroySurface(surface);
        ফেরত false;
    }

    // Initialize the clip rect
    surface->clip_rect.w = width;
    surface->clip_rect.h = height;

    // Allocate an empty mapping
    surface->map.info.r = 0xFF;
    surface->map.info.g = 0xFF;
    surface->map.info.b = 0xFF;
    surface->map.info.a = 0xFF;

    যদি (colorspace == SDL_COLORSPACE_UNKNOWN) {
        surface->colorspace = SDL_GetDefaultColorspaceForFormat(format);
    } অন্যথা {
        surface->colorspace = colorspace;
    }

    যদি (props) {
        যদি (!SDL_CopyProperties(props, SDL_GetSurfaceProperties(surface))) {
            SDL_DestroySurface(surface);
            ফেরত false;
        }
    }

    // By default surfaces with an alpha mask are set up for blending
    যদি (SDL_ISPIXELFORMAT_ALPHA(surface->format)) {
        SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
    }

    // The surface is ready to go
    surface->refcount = 1;
    ফেরত true;
}

/*
 * Create an empty surface of the appropriate depth using the given format
 */
স্থির SDL_Surface *SDL_CreateSurfaceInternal(পূর্ণসংখ্যা width, পূর্ণসংখ্যা height, SDL_PixelFormat format, bool clear_surface)
{
    size_t pitch, আকার_2;
    SDL_Surface *surface;

    CHECK_PARAM(width < 0) {
        SDL_InvalidParamError("width");
        ফেরত ফাঁকা;
    }

    CHECK_PARAM(height < 0) {
        SDL_InvalidParamError("height");
        ফেরত ফাঁকা;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        ফেরত ফাঁকা;
    }

    যদি (!SDL_Calculate_Surface_আকার(format, width, height, &আকার_2, &pitch, false /* not minimal pitch */)) {
        // Overflow...
        ফেরত ফাঁকা;
    }

    // Allocate and initialize the surface
    surface = (SDL_Surface *)SDL_malloc(আকার(*surface));
    যদি (!surface) {
        ফেরত ফাঁকা;
    }

    যদি (!SDL_InitializeSurface(surface, width, height, format, SDL_COLORSPACE_UNKNOWN, 0, ফাঁকা, (পূর্ণসংখ্যা)pitch, false)) {
        ফেরত ফাঁকা;
    }

    যদি (surface->w && surface->h && format != SDL_PIXELFORMAT_MJPG) {
        surface->flags &= ~SDL_SURFACE_PREALLOCATED;
        যদি (SDL_GetHintBoolean("SDL_SURFACE_MALLOC", false)) {
            যদি (clear_surface) {
                surface->pixels = SDL_calloc(1, আকার_2);
            } অন্যথা {
                surface->pixels = SDL_malloc(আকার_2);
            }
        } অন্যথা {
            surface->flags |= SDL_SURFACE_SIMD_ALIGNED;
            যদি (clear_surface) {
                surface->pixels = SDL_aligned_alloc_zero(SDL_GetSIMDAlignment(), আকার_2);
            } অন্যথা {
                surface->pixels = SDL_aligned_alloc(SDL_GetSIMDAlignment(), আকার_2);
            }
        }
        যদি (!surface->pixels) {
            SDL_DestroySurface(surface);
            ফেরত ফাঁকা;
        }
    }
    ফেরত surface;
}

SDL_Surface *SDL_CreateSurfaceZeroed(পূর্ণসংখ্যা width, পূর্ণসংখ্যা height, SDL_PixelFormat format)
{
    ফেরত SDL_CreateSurfaceInternal(width, height, format, true);
}

SDL_Surface *SDL_CreateSurfaceUninitialized(পূর্ণসংখ্যা width, পূর্ণসংখ্যা height, SDL_PixelFormat format)
{
    ফেরত SDL_CreateSurfaceInternal(width, height, format, false);
}

SDL_Surface *SDL_CreateSurface(পূর্ণসংখ্যা width, পূর্ণসংখ্যা height, SDL_PixelFormat format)
{
    ফেরত SDL_CreateSurfaceZeroed(width, height, format);
}


/*
 * Create an RGB surface from an existing memory buffer using the given
 * enum SDL_PIXELFORMAT_* format
 */
SDL_Surface *SDL_CreateSurfaceFrom(পূর্ণসংখ্যা width, পূর্ণসংখ্যা height, SDL_PixelFormat format, শূন্য *pixels, পূর্ণসংখ্যা pitch)
{
    CHECK_PARAM(width < 0) {
        SDL_InvalidParamError("width");
        ফেরত ফাঁকা;
    }

    CHECK_PARAM(height < 0) {
        SDL_InvalidParamError("height");
        ফেরত ফাঁকা;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        ফেরত ফাঁকা;
    }

    যদি (pitch == 0 && !pixels) {
        // The application will fill these in later with valid values
    } অন্যথা {
        size_t minimalPitch;

        যদি (!SDL_Calculate_Surface_আকার(format, width, height, ফাঁকা, &minimalPitch, true /* minimal pitch */)) {
            // Overflow...
            ফেরত ফাঁকা;
        }

        CHECK_PARAM(pitch < 0 || (size_t)pitch < minimalPitch) {
            SDL_InvalidParamError("pitch");
            ফেরত ফাঁকা;
        }
    }

    // Allocate and initialize the surface
    SDL_Surface *surface = (SDL_Surface *)SDL_malloc(আকার(*surface));
    যদি (!surface ||
        !SDL_InitializeSurface(surface, width, height, format, SDL_COLORSPACE_UNKNOWN, 0, pixels, pitch, false)) {
        ফেরত ফাঁকা;
    }
    ফেরত surface;
}

SDL_PropertiesID SDL_GetSurfaceProperties(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        ফেরত 0;
    }

    যদি (!surface->props) {
        surface->props = SDL_CreateProperties();
    }
    ফেরত surface->props;
}

bool SDL_SetSurfaceColorspace(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ফেরত SDL_InvalidParamError("surface");
    }

    surface->colorspace = colorspace;
    ফেরত true;
}

SDL_Colorspace SDL_GetSurfaceColorspace(SDL_Surface *surface)
{
    যদি (!SDL_SurfaceValid(surface)) {
        ফেরত SDL_COLORSPACE_UNKNOWN;
    }

    ফেরত surface->colorspace;
}

দশমিক SDL_GetDefaultSDRWhitePoint(SDL_Colorspace colorspace)
{
    ফেরত SDL_GetSurfaceSDRWhitePoint(ফাঁকা, colorspace);
}

দশমিক SDL_GetSurfaceSDRWhitePoint(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    SDL_TransferCharacteristics transfer = SDL_COLORSPACETRANSFER(colorspace);

    যদি (transfer == SDL_TRANSFER_CHARACTERISTICS_LINEAR ||
        transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
        SDL_PropertiesID props;
        দশমিক default_মান = 1.0f;

        যদি (SDL_SurfaceValid(surface)) {
            props = surface->props;
        } অন্যথা {
            props = 0;
        }
        যদি (transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
            /* The older standards use an SDR white point of 100 nits.
             * ITU-R BT.2408-6 recommends using an SDR white point of 203 nits.
             * This is the default Chrome uses, and what a lot of game content
             * assumes, so we'll go with that.
             */
            ধ্রুবক দশমিক DEFAULT_PQ_SDR_WHITE_POINT = 203.0f;
            default_মান = DEFAULT_PQ_SDR_WHITE_POINT;
        }
        ফেরত SDL_GetFloatProperty(props, SDL_PROP_SURFACE_SDR_WHITE_POINT_FLOAT, default_মান);
    }
    ফেরত 1.0f;
}

দশমিক SDL_GetDefaultHDRHeadroom(SDL_Colorspace colorspace)
{
    ফেরত SDL_GetSurfaceHDRHeadroom(ফাঁকা, colorspace);
}

দশমিক SDL_GetSurfaceHDRHeadroom(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    SDL_TransferCharacteristics transfer = SDL_COLORSPACETRANSFER(colorspace);

    যদি (transfer == SDL_TRANSFER_CHARACTERISTICS_LINEAR ||
        transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
        SDL_PropertiesID props;
        দশমিক default_মান = 0.0f;

        যদি (SDL_SurfaceValid(surface)) {
            props = surface->props;
        } অন্যথা {
            props = 0;
        }
        ফেরত SDL_GetFloatProperty(props, SDL_PROP_SURFACE_HDR_HEADROOM_FLOAT, default_মান);
    }
    ফেরত 1.0f;
}

SDL_Palette *SDL_CreateSurfacePalette(SDL_Surface *surface)
{
    SDL_Palette *palette;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        ফেরত ফাঁকা;
    }

    CHECK_PARAM(!SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        SDL_SetError("The surface is not indexed format");
        ফেরত ফাঁকা;
    }

    palette = SDL_CreatePalette((1 << SDL_BITSPERPIXEL(surface->format)));
    যদি (!palette) {
        ফেরত ফাঁকা;
    }

    যদি (palette->ncolors == 2) {
        // Create a black and white bitmap palette
        palette->colors[0].r = 0xFF;
        palette->colors[0].g = 0xFF;
        palette->colors[0].b = 0xFF;
        palette->colors[1].r = 0x00;
        palette->colors[1].g = 0x00;
        palette->colors[1].b = 0x00;
    }

    যদি (!SDL_SetSurfacePalette(surface, palette)) {
        SDL_DestroyPalette(palette);
        ফেরত ফাঁকা;
    }

    // The surface has retained the palette, we can remove the reference here
    SDL_assert(palette->refcount == 2);
    SDL_DestroyPalette(palette);
    ফেরত palette;
}

bool SDL_SetSurfacePalette(SDL_Surface *surface, SDL_Palette *palette)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ফেরত SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(palette && !SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        ফেরত SDL_SetError("Surface doesn't use a palette");
    }

    CHECK_PARAM(palette && palette->ncolors > (1 << SDL_BITSPERPIXEL(surface->format))) {
        ফেরত SDL_SetError("Palette doesn't match surface format");
    }

    যদি (palette != surface->palette) {
        যদি (surface->palette) {
            SDL_DestroyPalette(surface->palette);
        }

        surface->palette = palette;

        যদি (surface->palette) {
            ++surface->palette->refcount;
        }
    }

    SDL_InvalidateMap(&surface->map);

    ফেরত true;
}

SDL_Palette *SDL_GetSurfacePalette(SDL_Surface *surface)
{
    যদি (!SDL_SurfaceValid(surface)) {
        ফেরত ফাঁকা;
    }

    ফেরত surface->palette;
}

bool SDL_AddSurfaceAlternateImage(SDL_Surface *surface, SDL_Surface *image)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ফেরত SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(!SDL_SurfaceValid(image)) {
        ফেরত SDL_InvalidParamError("image");
    }

    SDL_Surface **images = (SDL_Surface **)SDL_realloc(surface->images, (surface->অঙ্ক_images + 1) * আকার(*images));
    যদি (!images) {
        ফেরত false;
    }
    images[surface->অঙ্ক_images] = image;
    surface->images = images;
    ++surface->অঙ্ক_images;
    ++image->refcount;
    ফেরত true;
}

bool SDL_SurfaceHasAlternateImages(SDL_Surface *surface)
{
    যদি (!SDL_SurfaceValid(surface)) {
        ফেরত false;
    }

    ফেরত (surface->অঙ্ক_images > 0);
}

SDL_Surface **SDL_GetSurfaceImages(SDL_Surface *surface, পূর্ণসংখ্যা *গুনতি)
{
    যদি (গুনতি) {
        *গুনতি = 0;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        ফেরত ফাঁকা;
    }

    পূর্ণসংখ্যা অঙ্ক_images = 1 + surface->অঙ্ক_images;
    SDL_Surface **images = (SDL_Surface **)SDL_malloc((অঙ্ক_images + 1) * আকার(*images));
    যদি (!images) {
        ফেরত ফাঁকা;
    }
    images[0] = surface;
    যদি (surface->অঙ্ক_images > 0) {
        SDL_memcpy(&images[1], surface->images, (surface->অঙ্ক_images * আকার(images[1])));
    }
    images[অঙ্ক_images] = ফাঁকা;

    যদি (গুনতি) {
        *গুনতি = অঙ্ক_images;
    }
    ফেরত images;
}

SDL_Surface *SDL_GetSurfaceImage(SDL_Surface *surface, দশমিক display_scale)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        ফেরত ফাঁকা;
    }

    যদি (!SDL_SurfaceHasAlternateImages(surface)) {
        ++surface->refcount;
        ফেরত surface;
    }

    // This surface has high DPI images, pick the best one available, or scale one to the correct size
    SDL_Surface **images = SDL_GetSurfaceImages(surface, ফাঁকা);
    যদি (!images) {
        // Failure, fall back to the existing surface
        ++surface->refcount;
        ফেরত surface;
    }

    // Find closest image. Images that are larger than the
    // desired size are preferred over images that are smaller.
    SDL_Surface *closest = ফাঁকা;
    পূর্ণসংখ্যা desired_w = (পূর্ণসংখ্যা)SDL_round(surface->w * display_scale);
    পূর্ণসংখ্যা desired_h = (পূর্ণসংখ্যা)SDL_round(surface->h * display_scale);
    পূর্ণসংখ্যা desired_আকার = desired_w * desired_h;
    পূর্ণসংখ্যা closest_distance = -1;
    পূর্ণসংখ্যা closest_আকার = -1;
    জন্য (পূর্ণসংখ্যা i = 0; images[i]; ++i) {
        SDL_Surface *candidate = images[i];
        পূর্ণসংখ্যা আকার_2 = candidate->w * candidate->h;
        পূর্ণসংখ্যা delta_w = (candidate->w - desired_w);
        পূর্ণসংখ্যা delta_h = (candidate->h - desired_h);
        পূর্ণসংখ্যা distance = (delta_w * delta_w) + (delta_h * delta_h);
        যদি (closest_distance < 0 || distance < closest_distance ||
            (আকার_2 > desired_আকার && closest_আকার < desired_আকার)) {
            closest = candidate;
            closest_distance = distance;
            closest_আকার = আকার_2;
        }
    }
    SDL_free(images);
    SDL_assert(closest != ফাঁকা);    // We should always have at least one surface

    যদি (closest->w == desired_w && closest->h == desired_h) {
        ++closest->refcount;
        ফেরত closest;
    }

    // We need to scale the image to the correct size. To maintain good image quality, downscaling
    // is done in steps, never reducing the width and height by more than half each time.
    SDL_Surface *scaled = closest;
    করো {
        পূর্ণসংখ্যা পরবর্তী_scaled_w = SDL_max(desired_w, (scaled->w + 1) / 2);
        পূর্ণসংখ্যা পরবর্তী_scaled_h = SDL_max(desired_h, (scaled->h + 1) / 2);
        SDL_Surface *পরবর্তী_scaled = SDL_ScaleSurface(scaled, পরবর্তী_scaled_w, পরবর্তী_scaled_h, SDL_SCALEMODE_LINEAR);
        যদি (scaled != closest) {
            SDL_DestroySurface(scaled);
        }
        scaled = পরবর্তী_scaled;
        যদি (!scaled) {
            // Failure, fall back to the closest surface
            ++closest->refcount;
            ফেরত closest;
        }
    } যখন (scaled->w != desired_w || scaled->h != desired_h);

    ফেরত scaled;
}

শূন্য SDL_RemoveSurfaceAlternateImages(SDL_Surface *surface)
{
    যদি (!SDL_SurfaceValid(surface)) {
        ফেরত;
    }

    যদি (surface->অঙ্ক_images > 0) {
        জন্য (পূর্ণসংখ্যা i = 0; i < surface->অঙ্ক_images; ++i) {
            SDL_DestroySurface(surface->images[i]);
        }
        SDL_free(surface->images);
        surface->images = ফাঁকা;
        surface->অঙ্ক_images = 0;
    }
}

bool SDL_SetSurfaceRLE(SDL_Surface *surface, bool enabled)
{
    পূর্ণসংখ্যা flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        ফেরত SDL_InvalidParamError("surface");
    }

    flags = surface->map.info.flags;
    যদি (enabled) {
        surface->map.info.flags |= SDL_COPY_RLE_DESIRED;
    } অন্যথা {
        surface->map.info.flags &= ~SDL_COPY_RLE_DESIRED;
    }
    যদি (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    ফেরত true;
}

bool SDL_SurfaceHasRLE(SDL_Surface *surface)
{
    যদি (!SDL_SurfaceValid(surface)) {
        ফেরত false;
    }

    যদি (!(surface->map.info.flags & SDL_COPY_RLE_DESIRED)) {
        ফেরত false;
    }

    ফেরত true;
}

bool SDL_Set_Surface_Color_চাবি(SDL_Surface *surface, bool enabled, Uint32 চাবি)
{
    পূর্ণসংখ্যা flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ফেরত SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(surface->palette && চাবি >= ((Uint32)surface->palette->ncolors)) {
        ফেরত SDL_InvalidParamError("key");
    }

    flags = surface->map.info.flags;
    যদি (enabled) {
        surface->map.info.flags |= SDL_COPY_COLORKEY;
        surface->map.info.colorkey = চাবি;
    } অন্যথা {
        surface->map.info.flags &= ~SDL_COPY_COLORKEY;
    }
    যদি (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }

    ফেরত true;
}

bool SDL_Surface_Has_Color_চাবি(SDL_Surface *surface)
{
    যদি (!SDL_SurfaceValid(surface)) {
        ফেরত false;
    }

    যদি (!(surface->map.info.flags & SDL_COPY_COLORKEY)) {
        ফেরত false;
    }

    ফেরত true;
}

bool SDL_Get_Surface_Color_চাবি(SDL_Surface *surface, Uint32 *চাবি)
{
    যদি (চাবি) {
        *চাবি = 0;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ফেরত SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(!(surface->map.info.flags & SDL_COPY_COLORKEY)) {
        ফেরত SDL_SetError("Surface doesn't have a colorkey");
    }

    যদি (চাবি) {
        *চাবি = surface->map.info.colorkey;
    }
    ফেরত true;
}

/* This is a fairly slow function to switch from colorkey to alpha
   NB: it doesn't handle bpp 1 or 3, because they have no alpha channel */
স্থির শূন্য SDL_ConvertColorkeyToAlpha(SDL_Surface *surface, bool ignore_alpha)
{
    পূর্ণসংখ্যা x, y, bpp;

    যদি (!SDL_SurfaceValid(surface)) {
        ফেরত;
    }

    যদি (!(surface->map.info.flags & SDL_COPY_COLORKEY) ||
        !SDL_ISPIXELFORMAT_ALPHA(surface->format)) {
        ফেরত;
    }

    bpp = SDL_BYTESPERPIXEL(surface->format);

    SDL_LockSurface(surface);

    যদি (bpp == 2) {
        Uint16 *row, *spot;
        Uint16 ckey = (Uint16)surface->map.info.colorkey;
        Uint16 mask = (Uint16)(~surface->fmt->Amask);

        // Ignore, or not, alpha in colorkey comparison
        যদি (ignore_alpha) {
            ckey &= mask;
            row = (Uint16 *)surface->pixels;
            জন্য (y = surface->h; y--;) {
                spot = row;
                জন্য (x = surface->w; x--;) {
                    যদি ((*spot & mask) == ckey) {
                        *spot &= mask;
                    }
                    ++spot;
                }
                row += surface->pitch / 2;
            }
        } অন্যথা {
            row = (Uint16 *)surface->pixels;
            জন্য (y = surface->h; y--;) {
                spot = row;
                জন্য (x = surface->w; x--;) {
                    যদি (*spot == ckey) {
                        *spot &= mask;
                    }
                    ++spot;
                }
                row += surface->pitch / 2;
            }
        }
    } অন্যথা যদি (bpp == 4) {
        Uint32 *row, *spot;
        Uint32 ckey = surface->map.info.colorkey;
        Uint32 mask = ~surface->fmt->Amask;

        // Ignore, or not, alpha in colorkey comparison
        যদি (ignore_alpha) {
            ckey &= mask;
            row = (Uint32 *)surface->pixels;
            জন্য (y = surface->h; y--;) {
                spot = row;
                জন্য (x = surface->w; x--;) {
                    যদি ((*spot & mask) == ckey) {
                        *spot &= mask;
                    }
                    ++spot;
                }
                row += surface->pitch / 4;
            }
        } অন্যথা {
            row = (Uint32 *)surface->pixels;
            জন্য (y = surface->h; y--;) {
                spot = row;
                জন্য (x = surface->w; x--;) {
                    যদি (*spot == ckey) {
                        *spot &= mask;
                    }
                    ++spot;
                }
                row += surface->pitch / 4;
            }
        }
    }

    SDL_UnlockSurface(surface);

    SDL_Set_Surface_Color_চাবি(surface, false, 0);
    SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
}

bool SDL_SetSurfaceColorMod(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b)
{
    পূর্ণসংখ্যা flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ফেরত SDL_InvalidParamError("surface");
    }

    surface->map.info.r = r;
    surface->map.info.g = g;
    surface->map.info.b = b;

    flags = surface->map.info.flags;
    যদি (r != 0xFF || g != 0xFF || b != 0xFF) {
        surface->map.info.flags |= SDL_COPY_MODULATE_COLOR;
    } অন্যথা {
        surface->map.info.flags &= ~SDL_COPY_MODULATE_COLOR;
    }
    যদি (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    ফেরত true;
}

bool SDL_GetSurfaceColorMod(SDL_Surface *surface, Uint8 *r, Uint8 *g, Uint8 *b)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        যদি (r) {
            *r = 255;
        }
        যদি (g) {
            *g = 255;
        }
        যদি (b) {
            *b = 255;
        }
        ফেরত SDL_InvalidParamError("surface");
    }

    যদি (r) {
        *r = surface->map.info.r;
    }
    যদি (g) {
        *g = surface->map.info.g;
    }
    যদি (b) {
        *b = surface->map.info.b;
    }
    ফেরত true;
}

bool SDL_SetSurfaceAlphaMod(SDL_Surface *surface, Uint8 alpha)
{
    পূর্ণসংখ্যা flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ফেরত SDL_InvalidParamError("surface");
    }

    surface->map.info.a = alpha;

    flags = surface->map.info.flags;
    যদি (alpha != 0xFF) {
        surface->map.info.flags |= SDL_COPY_MODULATE_ALPHA;
    } অন্যথা {
        surface->map.info.flags &= ~SDL_COPY_MODULATE_ALPHA;
    }
    যদি (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    ফেরত true;
}

bool SDL_GetSurfaceAlphaMod(SDL_Surface *surface, Uint8 *alpha)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        যদি (alpha) {
            *alpha = 255;
        }
        ফেরত SDL_InvalidParamError("surface");
    }

    যদি (alpha) {
        *alpha = surface->map.info.a;
    }
    ফেরত true;
}

bool SDL_SetSurfaceBlendMode(SDL_Surface *surface, SDL_BlendMode blendMode)
{
    পূর্ণসংখ্যা flags;
    bool ফলাফল = true;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ফেরত SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(blendMode == SDL_BLENDMODE_INVALID) {
        ফেরত SDL_InvalidParamError("blendMode");
    }

    flags = surface->map.info.flags;
    surface->map.info.flags &= ~SDL_COPY_BLEND_MASK;
    নির্বাচন (blendMode) {
    ক্ষেত্র SDL_BLENDMODE_NONE:
        বিরতি;
    ক্ষেত্র SDL_BLENDMODE_BLEND:
        surface->map.info.flags |= SDL_COPY_BLEND;
        বিরতি;
    ক্ষেত্র SDL_BLENDMODE_BLEND_PREMULTIPLIED:
        surface->map.info.flags |= SDL_COPY_BLEND_PREMULTIPLIED;
        বিরতি;
    ক্ষেত্র SDL_BLENDMODE_ADD:
        surface->map.info.flags |= SDL_COPY_ADD;
        বিরতি;
    ক্ষেত্র SDL_BLENDMODE_ADD_PREMULTIPLIED:
        surface->map.info.flags |= SDL_COPY_ADD_PREMULTIPLIED;
        বিরতি;
    ক্ষেত্র SDL_BLENDMODE_MOD:
        surface->map.info.flags |= SDL_COPY_MOD;
        বিরতি;
    ক্ষেত্র SDL_BLENDMODE_MUL:
        surface->map.info.flags |= SDL_COPY_MUL;
        বিরতি;
    পূর্বনির্ধারিত:
        ফলাফল = SDL_Unsupported();
        বিরতি;
    }

    যদি (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }

    ফেরত ফলাফল;
}

bool SDL_GetSurfaceBlendMode(SDL_Surface *surface, SDL_BlendMode *blendMode)
{
    যদি (blendMode) {
        *blendMode = SDL_BLENDMODE_INVALID;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ফেরত SDL_InvalidParamError("surface");
    }

    যদি (!blendMode) {
        ফেরত true;
    }

    নির্বাচন (surface->map.info.flags & SDL_COPY_BLEND_MASK) {
    ক্ষেত্র SDL_COPY_BLEND:
        *blendMode = SDL_BLENDMODE_BLEND;
        বিরতি;
    ক্ষেত্র SDL_COPY_BLEND_PREMULTIPLIED:
        *blendMode = SDL_BLENDMODE_BLEND_PREMULTIPLIED;
        বিরতি;
    ক্ষেত্র SDL_COPY_ADD:
        *blendMode = SDL_BLENDMODE_ADD;
        বিরতি;
    ক্ষেত্র SDL_COPY_ADD_PREMULTIPLIED:
        *blendMode = SDL_BLENDMODE_ADD_PREMULTIPLIED;
        বিরতি;
    ক্ষেত্র SDL_COPY_MOD:
        *blendMode = SDL_BLENDMODE_MOD;
        বিরতি;
    ক্ষেত্র SDL_COPY_MUL:
        *blendMode = SDL_BLENDMODE_MUL;
        বিরতি;
    পূর্বনির্ধারিত:
        *blendMode = SDL_BLENDMODE_NONE;
        বিরতি;
    }
    ফেরত true;
}

bool SDL_SetSurfaceClipRect(SDL_Surface *surface, ধ্রুবক SDL_Rect *rect)
{
    SDL_Rect full_rect;

    // Don't do anything if there's no surface to act on
    যদি (!SDL_SurfaceValid(surface)) {
        ফেরত false;
    }

    // Set up the full surface rectangle
    full_rect.x = 0;
    full_rect.y = 0;
    full_rect.w = surface->w;
    full_rect.h = surface->h;

    // Set the clipping rectangle
    যদি (!rect) {
        surface->clip_rect = full_rect;
        ফেরত true;
    }
    ফেরত SDL_GetRectIntersection(rect, &full_rect, &surface->clip_rect);
}

bool SDL_GetSurfaceClipRect(SDL_Surface *surface, SDL_Rect *rect)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        যদি (rect) {
            SDL_zerop(rect);
        }
        ফেরত SDL_InvalidParamError("surface");
    }
    CHECK_PARAM(!rect) {
        ফেরত SDL_InvalidParamError("rect");
    }
    *rect = surface->clip_rect;
    ফেরত true;
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
bool SDL_BlitSurfaceUnchecked(SDL_Surface *src, ধ্রুবক SDL_Rect *srcrect,
                             SDL_Surface *dst, ধ্রুবক SDL_Rect *dstrect)
{
    // Check to make sure the blit mapping is valid
    যদি (!SDL_ValidateMap(src, dst)) {
        ফেরত false;
    }
    ফেরত src->map.blit(src, srcrect, dst, dstrect);
}

bool SDL_BlitSurface(SDL_Surface *src, ধ্রুবক SDL_Rect *srcrect, SDL_Surface *dst, ধ্রুবক SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src) || (!src->pixels && !SDL_MUSTLOCK(src))) {
        ফেরত SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst) || (!dst->pixels && !SDL_MUSTLOCK(dst))) {
        ফেরত SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        ফেরত SDL_SetError("Surfaces must not be locked during blit");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    যদি (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
    } অন্যথা {
        r_dst.x = 0;
        r_dst.y = 0;
    }

    // clip the source rectangle to the source surface
    যদি (srcrect) {
        SDL_Rect tmp;
        যদি (SDL_GetRectIntersection(srcrect, &r_src, &tmp) == false) {
            ফেরত true;
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
        যদি (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &tmp) == false) {
            ফেরত true;
        }

        // Shift srcrect, if dstrect has changed
        r_src.x += tmp.x - r_dst.x;
        r_src.y += tmp.y - r_dst.y;
        r_src.w = tmp.w;
        r_src.h = tmp.h;

        // Update dstrect
        r_dst = tmp;
    }

    যদি (r_dst.w <= 0 || r_dst.h <= 0) {
        // No-op.
        ফেরত true;
    }

    // Switch back to a fast blit if we were previously stretching
    যদি (src->map.info.flags & SDL_COPY_NEAREST) {
        src->map.info.flags &= ~SDL_COPY_NEAREST;
        SDL_InvalidateMap(&src->map);
    }

    ফেরত SDL_BlitSurfaceUnchecked(src, &r_src, dst, &r_dst);
}

স্থির bool SDL_BlitSurfaceClippedScaled(SDL_Surface *src, ধ্রুবক SDL_Rect *srcrect, SDL_Surface *dst, ধ্রুবক SDL_Rect *dstrect, SDL_ScaleMode scaleMode)
{
    // We need to scale first, then blit into dst because we're clipping in the destination surface pixel coordinates
    bool ফলাফল;
    পূর্ণসংখ্যা saved_w = src->w;
    পূর্ণসংখ্যা saved_h = src->h;
    শূন্য *saved_pixels = src->pixels;
    src->w = srcrect->w;
    src->h = srcrect->h;
    src->pixels = (Uint8 *)src->pixels + srcrect->y * src->pitch + srcrect->x * SDL_BYTESPERPIXEL(src->format);
    SDL_Surface *scaled = SDL_ScaleSurface(src, dstrect->w, dstrect->h, scaleMode);
    যদি (scaled) {
        ফলাফল = SDL_BlitSurface(scaled, ফাঁকা, dst, dstrect);
        SDL_DestroySurface(scaled);
    } অন্যথা {
        ফলাফল = false;
    }
    src->w = saved_w;
    src->h = saved_h;
    src->pixels = saved_pixels;
    ফেরত ফলাফল;
}

bool SDL_BlitSurfaceScaled(SDL_Surface *src, ধ্রুবক SDL_Rect *srcrect, SDL_Surface *dst, ধ্রুবক SDL_Rect *dstrect, SDL_ScaleMode scaleMode)
{
    SDL_Rect r_src, r_dst;
    bool ফলাফল;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src) || (!src->pixels && !SDL_MUSTLOCK(src))) {
        ফেরত SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst) || (!dst->pixels && !SDL_MUSTLOCK(dst))) {
        ফেরত SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        ফেরত SDL_SetError("Surfaces must not be locked during blit");
    }

    নির্বাচন (scaleMode) {
    ক্ষেত্র SDL_SCALEMODE_NEAREST:
        বিরতি;
    ক্ষেত্র SDL_SCALEMODE_LINEAR:
        বিরতি;
    ক্ষেত্র SDL_SCALEMODE_PIXELART:
        scaleMode = SDL_SCALEMODE_NEAREST;
        বিরতি;
    পূর্বনির্ধারিত:
        ফেরত SDL_InvalidParamError("scaleMode");
    }

    পূর্ণসংখ্যা src_w = srcrect ? srcrect->w : src->w;
    পূর্ণসংখ্যা src_h = srcrect ? srcrect->h : src->h;
    পূর্ণসংখ্যা dst_w = dstrect ? dstrect->w : dst->w;
    পূর্ণসংখ্যা dst_h = dstrect ? dstrect->h : dst->h;
    যদি (src_w == dst_w && src_h == dst_h) {
        // No scaling, defer to regular blit
        ফেরত SDL_BlitSurface(src, srcrect, dst, dstrect);
    }

    যদি (src->w == 0 || src->h == 0) {
        // Nothing to do
        ফেরত true;
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    যদি (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
        r_dst.w = dstrect->w;
        r_dst.h = dstrect->h;
    } অন্যথা {
        r_dst.x = 0;
        r_dst.y = 0;
        r_dst.w = dst->w;
        r_dst.h = dst->h;
    }

    // clip the source rectangle to the source surface
    যদি (srcrect) {
        SDL_Rect desired, tmp;
        desired.x = srcrect->x;
        desired.y = srcrect->y;
        desired.w = SDL_max(srcrect->w, 1);
        desired.h = SDL_max(srcrect->h, 1);
        যদি (SDL_GetRectIntersection(&desired, &r_src, &tmp) == false) {
            ফেরত true;
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
    যদি (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &tmp) == false) {
        ফেরত true;
    }

    যদি (tmp.x != r_dst.x || tmp.y != r_dst.y || tmp.w != r_dst.w || tmp.h != r_dst.h) {
        // Need to do a clipped and scaled blit
        ফেরত SDL_BlitSurfaceClippedScaled(src, &r_src, dst, &r_dst, scaleMode);
    }

    যদি (SDL_MUSTLOCK(src)) {
        যদি (!SDL_LockSurface(src)) {
            ফেরত false;
        }
    }
    যদি (SDL_MUSTLOCK(dst)) {
        যদি (!SDL_LockSurface(dst)) {
            যদি (SDL_MUSTLOCK(src)) {
                SDL_UnlockSurface(src);
            }
            ফেরত false;
        }
    }

    ফলাফল = SDL_BlitSurfaceUncheckedScaled(src, &r_src, dst, &r_dst, scaleMode);

    যদি (SDL_MUSTLOCK(src)) {
        SDL_UnlockSurface(src);
    }
    যদি (SDL_MUSTLOCK(dst)) {
        SDL_UnlockSurface(dst);
    }
    ফেরত ফলাফল;
}

/**
 *  This is a semi-private blit function and it performs low-level surface
 *  scaled blitting only.
 */
bool SDL_BlitSurfaceUncheckedScaled(SDL_Surface *src, ধ্রুবক SDL_Rect *srcrect, SDL_Surface *dst, ধ্রুবক SDL_Rect *dstrect, SDL_ScaleMode scaleMode)
{
    স্থির ধ্রুবক Uint32 complex_copy_flags = (SDL_COPY_MODULATE_MASK | SDL_COPY_BLEND_MASK | SDL_COPY_COLORKEY);

    যদি (srcrect->w > SDL_MAX_UINT16 || srcrect->h > SDL_MAX_UINT16 ||
        dstrect->w > SDL_MAX_UINT16 || dstrect->h > SDL_MAX_UINT16) {
        ফেরত SDL_SetError("Size too large for scaling");
    }

    যদি (!(src->map.info.flags & SDL_COPY_NEAREST)) {
        src->map.info.flags |= SDL_COPY_NEAREST;
        SDL_InvalidateMap(&src->map);
    }

    যদি (scaleMode == SDL_SCALEMODE_NEAREST || scaleMode == SDL_SCALEMODE_PIXELART) {
        যদি (!(src->map.info.flags & complex_copy_flags) &&
            src->format == dst->format &&
            (!SDL_ISPIXELFORMAT_INDEXED(src->format) ||
             (SDL_BITSPERPIXEL(src->format) == 8 && SDL_IsSamePalette(src->palette, dst->palette))) &&
            SDL_BYTESPERPIXEL(src->format) <= 4) {
            ফেরত SDL_StretchSurface(src, srcrect, dst, dstrect, SDL_SCALEMODE_NEAREST);
        } অন্যথা যদি (SDL_BITSPERPIXEL(src->format) < 8) {
            // Scaling bitmap not yet supported, convert to RGBA for blit
            bool ফলাফল = false;
            SDL_Surface *tmp = SDL_ConvertSurface(src, SDL_PIXELFORMAT_ARGB8888);
            যদি (tmp) {
                ফলাফল = SDL_BlitSurfaceUncheckedScaled(tmp, srcrect, dst, dstrect, SDL_SCALEMODE_NEAREST);
                SDL_DestroySurface(tmp);
            }
            ফেরত ফলাফল;
        } অন্যথা {
            ফেরত SDL_BlitSurfaceUnchecked(src, srcrect, dst, dstrect);
        }
    } অন্যথা {
        যদি (!(src->map.info.flags & complex_copy_flags) &&
            src->format == dst->format &&
            !SDL_ISPIXELFORMAT_INDEXED(src->format) &&
            SDL_BYTESPERPIXEL(src->format) == 4 &&
            src->format != SDL_PIXELFORMAT_ARGB2101010) {
            // fast path
            ফেরত SDL_StretchSurface(src, srcrect, dst, dstrect, SDL_SCALEMODE_LINEAR);
        } অন্যথা যদি (SDL_BITSPERPIXEL(src->format) < 8) {
            // Scaling bitmap not yet supported, convert to RGBA for blit
            bool ফলাফল = false;
            SDL_Surface *tmp = SDL_ConvertSurface(src, SDL_PIXELFORMAT_ARGB8888);
            যদি (tmp) {
                ফলাফল = SDL_BlitSurfaceUncheckedScaled(tmp, srcrect, dst, dstrect, scaleMode);
                SDL_DestroySurface(tmp);
            }
            ফেরত ফলাফল;
        } অন্যথা {
            // Use intermediate surface(s)
            SDL_Surface *tmp1 = ফাঁকা;
            bool ফলাফল;
            SDL_Rect srcrect2;
            পূর্ণসংখ্যা is_complex_copy_flags = (src->map.info.flags & complex_copy_flags);

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
            যদি (SDL_BYTESPERPIXEL(src->format) != 4 || src->format == SDL_PIXELFORMAT_ARGB2101010) {
                SDL_PixelFormat fmt;
                যদি (SDL_BYTESPERPIXEL(dst->format) == 4 && dst->format != SDL_PIXELFORMAT_ARGB2101010 &&
                    (SDL_ISPIXELFORMAT_ALPHA(dst->format) || !is_complex_copy_flags)) {
                    fmt = dst->format;
                } অন্যথা {
                    fmt = SDL_PIXELFORMAT_ARGB8888;
                }
                tmp1 = SDL_ConvertSurfaceRect(src, srcrect, fmt);
                যদি (!tmp1) {
                    ফেরত false;
                }
                src = tmp1;
                srcrect2.x = 0;
                srcrect2.y = 0;
            }

            // Intermediate scaling
            যদি (is_complex_copy_flags || src->format != dst->format) {
                SDL_Rect tmprect;
                SDL_Surface *tmp2 = SDL_CreateSurfaceUninitialized(dstrect->w, dstrect->h, src->format);
                SDL_StretchSurface(src, &srcrect2, tmp2, ফাঁকা, SDL_SCALEMODE_LINEAR);

                SDL_SetSurfaceColorMod(tmp2, r, g, b);
                SDL_SetSurfaceAlphaMod(tmp2, alpha);
                SDL_SetSurfaceBlendMode(tmp2, blendMode);

                tmprect.x = 0;
                tmprect.y = 0;
                tmprect.w = dstrect->w;
                tmprect.h = dstrect->h;
                ফলাফল = SDL_BlitSurfaceUnchecked(tmp2, &tmprect, dst, dstrect);
                SDL_DestroySurface(tmp2);
            } অন্যথা {
                ফলাফল = SDL_StretchSurface(src, &srcrect2, dst, dstrect, SDL_SCALEMODE_LINEAR);
            }

            SDL_DestroySurface(tmp1);
            ফেরত ফলাফল;
        }
    }
}

bool SDL_BlitSurfaceTiled(SDL_Surface *src, ধ্রুবক SDL_Rect *srcrect, SDL_Surface *dst, ধ্রুবক SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        ফেরত SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        ফেরত SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        ফেরত SDL_SetError("Surfaces must not be locked during blit");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    যদি (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
        r_dst.w = dstrect->w;
        r_dst.h = dstrect->h;
    } অন্যথা {
        r_dst.x = 0;
        r_dst.y = 0;
        r_dst.w = dst->w;
        r_dst.h = dst->h;
    }

    // clip the source rectangle to the source surface
    যদি (srcrect) {
        যদি (SDL_GetRectIntersection(srcrect, &r_src, &r_src) == false) {
            ফেরত true;
        }

        // For tiling we don't adjust the destination rectangle
    }

    // clip the destination rectangle against the clip rectangle
    {
        যদি (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &r_dst) == false) {
            ফেরত true;
        }

        // For tiling we don't adjust the source rectangle
    }

    // Switch back to a fast blit if we were previously stretching
    যদি (src->map.info.flags & SDL_COPY_NEAREST) {
        src->map.info.flags &= ~SDL_COPY_NEAREST;
        SDL_InvalidateMap(&src->map);
    }

    পূর্ণসংখ্যা rows = r_dst.h / r_src.h;
    পূর্ণসংখ্যা cols = r_dst.w / r_src.w;
    পূর্ণসংখ্যা remaining_w = r_dst.w % r_src.w;
    পূর্ণসংখ্যা remaining_h = r_dst.h % r_src.h;
    SDL_Rect curr_src, curr_dst;

    SDL_copyp(&curr_src, &r_src);
    curr_dst.y = r_dst.y;
    curr_dst.w = r_src.w;
    curr_dst.h = r_src.h;
    জন্য (পূর্ণসংখ্যা y = 0; y < rows; ++y) {
        curr_dst.x = r_dst.x;
        জন্য (পূর্ণসংখ্যা x = 0; x < cols; ++x) {
            যদি (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                ফেরত false;
            }
            curr_dst.x += curr_dst.w;
        }
        যদি (remaining_w) {
            curr_src.w = remaining_w;
            curr_dst.w = remaining_w;
            যদি (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                ফেরত false;
            }
            curr_src.w = r_src.w;
            curr_dst.w = r_src.w;
        }
        curr_dst.y += curr_dst.h;
    }
    যদি (remaining_h) {
        curr_src.h = remaining_h;
        curr_dst.h = remaining_h;
        curr_dst.x = r_dst.x;
        জন্য (পূর্ণসংখ্যা x = 0; x < cols; ++x) {
            যদি (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                ফেরত false;
            }
            curr_dst.x += curr_dst.w;
        }
        যদি (remaining_w) {
            curr_src.w = remaining_w;
            curr_dst.w = remaining_w;
            যদি (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                ফেরত false;
            }
        }
    }
    ফেরত true;
}

bool SDL_BlitSurfaceTiledWithScale(SDL_Surface *src, ধ্রুবক SDL_Rect *srcrect, দশমিক scale, SDL_ScaleMode scaleMode, SDL_Surface *dst, ধ্রুবক SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        ফেরত SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        ফেরত SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        ফেরত SDL_SetError("Surfaces must not be locked during blit");
    }
    CHECK_PARAM(scale < 0.0f) {
        ফেরত SDL_InvalidParamError("scale");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    যদি (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
        r_dst.w = dstrect->w;
        r_dst.h = dstrect->h;
    } অন্যথা {
        r_dst.x = 0;
        r_dst.y = 0;
        r_dst.w = dst->w;
        r_dst.h = dst->h;
    }

    // clip the source rectangle to the source surface
    যদি (srcrect) {
        যদি (SDL_GetRectIntersection(srcrect, &r_src, &r_src) == false) {
            ফেরত true;
        }

        // For tiling we don't adjust the destination rectangle
    }

    // clip the destination rectangle against the clip rectangle
    {
        যদি (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &r_dst) == false) {
            ফেরত true;
        }

        // For tiling we don't adjust the source rectangle
    }

    // Switch back to a fast blit if we were previously stretching
    যদি (src->map.info.flags & SDL_COPY_NEAREST) {
        src->map.info.flags &= ~SDL_COPY_NEAREST;
        SDL_InvalidateMap(&src->map);
    }

    পূর্ণসংখ্যা tile_width = (পূর্ণসংখ্যা)SDL_roundf(r_src.w * scale);
    পূর্ণসংখ্যা tile_height = (পূর্ণসংখ্যা)SDL_roundf(r_src.h * scale);
    যদি (tile_width <= 0 || tile_height <= 0) {
        // Nothing to do
        ফেরত true;
    }
    পূর্ণসংখ্যা rows = r_dst.h / tile_height;
    পূর্ণসংখ্যা cols = r_dst.w / tile_width;
    পূর্ণসংখ্যা remaining_dst_w = (r_dst.w - cols * tile_width);
    পূর্ণসংখ্যা remaining_dst_h = (r_dst.h - rows * tile_height);
    পূর্ণসংখ্যা remaining_src_w = (পূর্ণসংখ্যা)(remaining_dst_w / scale);
    পূর্ণসংখ্যা remaining_src_h = (পূর্ণসংখ্যা)(remaining_dst_h / scale);
    SDL_Rect curr_src, curr_dst;

    SDL_copyp(&curr_src, &r_src);
    curr_dst.y = r_dst.y;
    curr_dst.w = tile_width;
    curr_dst.h = tile_height;
    জন্য (পূর্ণসংখ্যা y = 0; y < rows; ++y) {
        curr_dst.x = r_dst.x;
        জন্য (পূর্ণসংখ্যা x = 0; x < cols; ++x) {
            যদি (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
                ফেরত false;
            }
            curr_dst.x += curr_dst.w;
        }
        যদি (remaining_dst_w > 0) {
            curr_src.w = remaining_src_w;
            curr_dst.w = remaining_dst_w;
            যদি (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
                ফেরত false;
            }
            curr_src.w = r_src.w;
            curr_dst.w = tile_width;
        }
        curr_dst.y += curr_dst.h;
    }
    যদি (remaining_dst_h > 0) {
        curr_src.h = remaining_src_h;
        curr_dst.h = remaining_dst_h;
        curr_dst.x = r_dst.x;
        জন্য (পূর্ণসংখ্যা x = 0; x < cols; ++x) {
            যদি (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
                ফেরত false;
            }
            curr_dst.x += curr_dst.w;
        }
        যদি (remaining_dst_w > 0) {
            curr_src.w = remaining_src_w;
            curr_dst.w = remaining_dst_w;
            যদি (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
                ফেরত false;
            }
        }
    }
    ফেরত true;
}

bool SDL_BlitSurface9Grid(SDL_Surface *src, ধ্রুবক SDL_Rect *srcrect, পূর্ণসংখ্যা বাম_width, পূর্ণসংখ্যা ডান_width, পূর্ণসংখ্যা শীর্ষ_height, পূর্ণসংখ্যা bottom_height, দশমিক scale, SDL_ScaleMode scaleMode, SDL_Surface *dst, ধ্রুবক SDL_Rect *dstrect)
{
    SDL_Rect full_src, full_dst;
    SDL_Rect curr_src, curr_dst;
    পূর্ণসংখ্যা dst_বাম_width;
    পূর্ণসংখ্যা dst_ডান_width;
    পূর্ণসংখ্যা dst_শীর্ষ_height;
    পূর্ণসংখ্যা dst_bottom_height;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        ফেরত SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        ফেরত SDL_InvalidParamError("dst");
    }

    যদি (!srcrect) {
        full_src.x = 0;
        full_src.y = 0;
        full_src.w = src->w;
        full_src.h = src->h;
        srcrect = &full_src;
    }

    যদি (!dstrect) {
        full_dst.x = 0;
        full_dst.y = 0;
        full_dst.w = dst->w;
        full_dst.h = dst->h;
        dstrect = &full_dst;
    }

    যদি (scale <= 0.0f || scale == 1.0f) {
        dst_বাম_width = বাম_width;
        dst_ডান_width = ডান_width;
        dst_শীর্ষ_height = শীর্ষ_height;
        dst_bottom_height = bottom_height;
    } অন্যথা {
        dst_বাম_width = (পূর্ণসংখ্যা)SDL_roundf(বাম_width * scale);
        dst_ডান_width = (পূর্ণসংখ্যা)SDL_roundf(ডান_width * scale);
        dst_শীর্ষ_height = (পূর্ণসংখ্যা)SDL_roundf(শীর্ষ_height * scale);
        dst_bottom_height = (পূর্ণসংখ্যা)SDL_roundf(bottom_height * scale);
    }

    // Upper-left corner
    curr_src.x = srcrect->x;
    curr_src.y = srcrect->y;
    curr_src.w = বাম_width;
    curr_src.h = শীর্ষ_height;
    curr_dst.x = dstrect->x;
    curr_dst.y = dstrect->y;
    curr_dst.w = dst_বাম_width;
    curr_dst.h = dst_শীর্ষ_height;
    যদি (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        ফেরত false;
    }

    // Upper-right corner
    curr_src.x = srcrect->x + srcrect->w - ডান_width;
    curr_src.w = ডান_width;
    curr_dst.x = dstrect->x + dstrect->w - dst_ডান_width;
    curr_dst.w = dst_ডান_width;
    যদি (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        ফেরত false;
    }

    // Lower-right corner
    curr_src.y = srcrect->y + srcrect->h - bottom_height;
    curr_dst.y = dstrect->y + dstrect->h - dst_bottom_height;
    curr_dst.h = dst_bottom_height;
    যদি (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        ফেরত false;
    }

    // Lower-left corner
    curr_src.x = srcrect->x;
    curr_src.w = বাম_width;
    curr_dst.x = dstrect->x;
    curr_dst.w = dst_বাম_width;
    যদি (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        ফেরত false;
    }

    //বাম
    curr_src.y = srcrect->y + শীর্ষ_height;
    curr_src.h = srcrect->h - শীর্ষ_height - bottom_height;
    curr_dst.y = dstrect->y + dst_শীর্ষ_height;
    curr_dst.h = dstrect->h - dst_শীর্ষ_height - dst_bottom_height;
    যদি (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        ফেরত false;
    }

    //ডান
    curr_src.x = srcrect->x + srcrect->w - ডান_width;
    curr_src.w = ডান_width;
    curr_dst.x = dstrect->x + dstrect->w - dst_ডান_width;
    curr_dst.w = dst_ডান_width;
    যদি (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        ফেরত false;
    }

    //শীর্ষ
    curr_src.x = srcrect->x + বাম_width;
    curr_src.y = srcrect->y;
    curr_src.w = srcrect->w - বাম_width - ডান_width;
    curr_src.h = শীর্ষ_height;
    curr_dst.x = dstrect->x + dst_বাম_width;
    curr_dst.y = dstrect->y;
    curr_dst.w = dstrect->w - dst_বাম_width - dst_ডান_width;
    curr_dst.h = dst_শীর্ষ_height;
    যদি (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        ফেরত false;
    }

    // Bottom
    curr_src.y = srcrect->y + srcrect->h - bottom_height;
    curr_dst.y = dstrect->y + dstrect->h - dst_bottom_height;
    curr_dst.h = dst_bottom_height;
    যদি (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        ফেরত false;
    }

    // Center
    curr_src.x = srcrect->x + বাম_width;
    curr_src.y = srcrect->y + শীর্ষ_height;
    curr_src.w = srcrect->w - বাম_width - ডান_width;
    curr_src.h = srcrect->h - শীর্ষ_height - bottom_height;
    curr_dst.x = dstrect->x + dst_বাম_width;
    curr_dst.y = dstrect->y + dst_শীর্ষ_height;
    curr_dst.w = dstrect->w - dst_বাম_width - dst_ডান_width;
    curr_dst.h = dstrect->h - dst_শীর্ষ_height - dst_bottom_height;
    যদি (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        ফেরত false;
    }

    ফেরত true;
}

/*
 * Lock a surface to directly access the pixels
 */
bool SDL_LockSurface(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ফেরত SDL_InvalidParamError("surface");
    }

    যদি (!surface->locked) {
#ifdef SDL_HAVE_RLE
        // Perform the lock
        যদি (surface->internal_flags & SDL_INTERNAL_SURFACE_RLEACCEL) {
            SDL_UnRLESurface(surface);
        }
#endif
    }

    // Increment the surface lock count, for recursive locks
    ++surface->locked;
    surface->flags |= SDL_SURFACE_LOCKED;
    SDL_UpdateSurfaceLockFlag(surface);

    // Ready to go..
    ফেরত true;
}

/*
 * Unlock a previously locked surface
 */
শূন্য SDL_UnlockSurface(SDL_Surface *surface)
{
    যদি (!SDL_SurfaceValid(surface)) {
        ফেরত;
    }

    // Only perform an unlock if we are locked
    যদি (!surface->locked || (--surface->locked > 0)) {
        ফেরত;
    }

    surface->flags &= ~SDL_SURFACE_LOCKED;
    SDL_UpdateSurfaceLockFlag(surface);
}

স্থির bool SDL_FlipSurfaceHorizontal(SDL_Surface *surface)
{
    bool isstack;
    Uint8 *row, *a, *b, *tmp;
    পূর্ণসংখ্যা i, j, bpp;

    যদি (SDL_BITSPERPIXEL(surface->format) < 8) {
        // We could implement this if needed, but we'd have to flip sets of bits within a byte
        ফেরত SDL_Unsupported();
    }

    যদি (surface->h <= 0) {
        ফেরত true;
    }

    যদি (surface->w <= 1) {
        ফেরত true;
    }

    bpp = SDL_BYTESPERPIXEL(surface->format);
    row = (Uint8 *)surface->pixels;
    tmp = SDL_small_alloc(Uint8, surface->pitch, &isstack);
    যদি (!tmp) {
        ফেরত false;
    }
    জন্য (i = surface->h; i--; ) {
        a = row;
        b = a + (surface->w - 1) * bpp;
        জন্য (j = surface->w / 2; j--; ) {
            SDL_memcpy(tmp, a, bpp);
            SDL_memcpy(a, b, bpp);
            SDL_memcpy(b, tmp, bpp);
            a += bpp;
            b -= bpp;
        }
        row += surface->pitch;
    }
    SDL_small_free(tmp, isstack);
    ফেরত true;
}

স্থির bool SDL_FlipSurfaceVertical(SDL_Surface *surface)
{
    bool isstack;
    Uint8 *a, *b, *tmp;
    পূর্ণসংখ্যা i;

    যদি (surface->h <= 1) {
        ফেরত true;
    }

    a = (Uint8 *)surface->pixels;
    b = a + (surface->h - 1) * surface->pitch;
    tmp = SDL_small_alloc(Uint8, surface->pitch, &isstack);
    যদি (!tmp) {
        ফেরত false;
    }
    জন্য (i = surface->h / 2; i--; ) {
        SDL_memcpy(tmp, a, surface->pitch);
        SDL_memcpy(a, b, surface->pitch);
        SDL_memcpy(b, tmp, surface->pitch);
        a += surface->pitch;
        b -= surface->pitch;
    }
    SDL_small_free(tmp, isstack);
    ফেরত true;
}

bool SDL_FlipSurface(SDL_Surface *surface, SDL_FlipMode flip)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ফেরত SDL_InvalidParamError("surface");
    }
    যদি (!surface->pixels) {
        ফেরত true;
    }

    bool ফলাফল = true;
    নির্বাচন (flip) {
    ক্ষেত্র SDL_FLIP_HORIZONTAL:
        ফলাফল = SDL_FlipSurfaceHorizontal(surface);
        বিরতি;
    ক্ষেত্র SDL_FLIP_VERTICAL:
        ফলাফল = SDL_FlipSurfaceVertical(surface);
        বিরতি;
    ক্ষেত্র SDL_FLIP_HORIZONTAL_AND_VERTICAL:
        ফলাফল &= SDL_FlipSurfaceHorizontal(surface);
        ফলাফল &= SDL_FlipSurfaceVertical(surface);
        বিরতি;
    পূর্বনির্ধারিত:
        ফলাফল = SDL_InvalidParamError("flip");
        বিরতি;
    }
    ফেরত ফলাফল;
}

স্থির SDL_Surface *SDL_ConvertSurfaceRectAndColorspace(SDL_Surface *surface, ধ্রুবক SDL_Rect *rect, SDL_PixelFormat format, SDL_Palette *palette, SDL_Colorspace colorspace, SDL_PropertiesID props)
{
    SDL_Palette *অস্থায়ী_palette = ফাঁকা;
    SDL_Surface *convert = ফাঁকা;
    SDL_Colorspace src_colorspace;
    SDL_PropertiesID src_properties;
    Uint32 copy_flags;
    SDL_Color copy_color;
    SDL_Rect bounds;
    bool ফলাফল;
    bool palette_ck_transform = false;
    Uint8 palette_ck_মান = 0;
    Uint8 *palette_saved_alpha = ফাঁকা;
    পূর্ণসংখ্যা palette_saved_alpha_ncolors = 0;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        যাও error;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        যাও error;
    }

    // Set the bounds of the new surface
    bounds.x = 0;
    bounds.y = 0;
    bounds.w = surface->w;
    bounds.h = surface->h;
    যদি (rect) {
        bounds.w = rect->w;
        bounds.h = rect->h;
    } অন্যথা {
        rect = &bounds;
    }

    // Check for empty destination palette! (results in empty image)
    যদি (palette) {
        পূর্ণসংখ্যা i;
        জন্য (i = 0; i < palette->ncolors; ++i) {
            যদি ((palette->colors[i].r != 0xFF) || (palette->colors[i].g != 0xFF) || (palette->colors[i].b != 0xFF)) {
                বিরতি;
            }
        }
        যদি (i == palette->ncolors) {
            SDL_SetError("Empty destination palette");
            যাও error;
        }
    } অন্যথা যদি (SDL_ISPIXELFORMAT_INDEXED(format)) {
        // Create a dither palette for conversion
        অস্থায়ী_palette = SDL_CreatePalette(1 << SDL_BITSPERPIXEL(format));
        যদি (অস্থায়ী_palette) {
            SDL_DitherPalette(অস্থায়ী_palette);
            palette = অস্থায়ী_palette;
        }
    }

    src_colorspace = surface->colorspace;
    src_properties = surface->props;

    // Create a new surface with the desired format
    যদি (surface->pixels || SDL_MUSTLOCK(surface)) {
        convert = SDL_CreateSurfaceUninitialized(rect->w, rect->h, format);
    } অন্যথা {
        convert = SDL_CreateSurfaceFrom(rect->w, rect->h, format, ফাঁকা, 0);
    }
    যদি (!convert) {
        যাও error;
    }
    যদি (SDL_ISPIXELFORMAT_INDEXED(format)) {
        SDL_SetSurfacePalette(convert, palette);
    }

    যদি (colorspace == SDL_COLORSPACE_UNKNOWN) {
        colorspace = src_colorspace;
    }
    SDL_SetSurfaceColorspace(convert, colorspace);

    যদি (SDL_ISPIXELFORMAT_FOURCC(format) || SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        যদি (surface->format == SDL_PIXELFORMAT_MJPG && format == SDL_PIXELFORMAT_MJPG) {
            // Just do a straight pixel copy of the JPEG image
            size_t আকার_2 = (size_t)surface->pitch;
            convert->pixels = SDL_malloc(আকার_2);
            যদি (!convert->pixels) {
                যাও error;
            }
            convert->flags &= ~SDL_SURFACE_PREALLOCATED;
            convert->pitch = surface->pitch;
            SDL_memcpy(convert->pixels, surface->pixels, আকার_2);

        } অন্যথা যদি (!SDL_ConvertPixelsAndColorspace(surface->w, surface->h, surface->format, src_colorspace, src_properties, surface->pixels, surface->pitch, convert->format, colorspace, props, convert->pixels, convert->pitch)) {
            যাও error;
        }

        // Save the original copy flags
        copy_flags = surface->map.info.flags;

        যাও end;
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
    যদি (surface->palette && SDL_ISPIXELFORMAT_ALPHA(format)) {
        bool set_opaque = false;

        bool is_opaque, has_alpha_channel;
        SDL_DetectPalette(surface->palette, &is_opaque, &has_alpha_channel);

        যদি (is_opaque) {
            যদি (!has_alpha_channel) {
                set_opaque = true;
            }
        }

        // Set opaque and backup palette alpha values
        যদি (set_opaque) {
            পূর্ণসংখ্যা i;
            palette_saved_alpha_ncolors = surface->palette->ncolors;
            যদি (palette_saved_alpha_ncolors > 0) {
                palette_saved_alpha = SDL_স্তূপ_alloc(Uint8, palette_saved_alpha_ncolors);
                জন্য (i = 0; i < palette_saved_alpha_ncolors; i++) {
                    palette_saved_alpha[i] = surface->palette->colors[i].a;
                    surface->palette->colors[i].a = SDL_ALPHA_OPAQUE;
                }
            }
        }
    }

    // Transform colorkey to alpha. for cases where source palette has duplicate values, and colorkey is one of them
    যদি (copy_flags & SDL_COPY_COLORKEY) {
        যদি (surface->palette && !palette) {
            palette_ck_transform = true;
            palette_ck_মান = surface->palette->colors[surface->map.info.colorkey].a;
            surface->palette->colors[surface->map.info.colorkey].a = SDL_ALPHA_TRANSPARENT;
        }
    }

    যদি (surface->pixels || SDL_MUSTLOCK(surface)) {
        ফলাফল = SDL_BlitSurfaceUnchecked(surface, rect, convert, &bounds);
    } অন্যথা {
        ফলাফল = true;
    }

    // Restore colorkey alpha value
    যদি (palette_ck_transform) {
        surface->palette->colors[surface->map.info.colorkey].a = palette_ck_মান;
    }

    // Restore palette alpha values
    যদি (palette_saved_alpha) {
        পূর্ণসংখ্যা i;
        জন্য (i = 0; i < palette_saved_alpha_ncolors; i++) {
            surface->palette->colors[i].a = palette_saved_alpha[i];
        }
        SDL_স্তূপ_free(palette_saved_alpha);
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
    যদি (!ফলাফল) {
        যাও error;
    }

    যদি (copy_flags & SDL_COPY_COLORKEY) {
        bool set_colorkey_by_color = false;
        bool convert_colorkey = true;

        যদি (surface->palette) {
            যদি (palette &&
                surface->palette->ncolors <= palette->ncolors &&
                (SDL_memcmp(surface->palette->colors, palette->colors,
                            surface->palette->ncolors * আকার(SDL_Color)) == 0)) {
                // The palette is identical, just set the same colorkey
                SDL_Set_Surface_Color_চাবি(convert, true, surface->map.info.colorkey);
            } অন্যথা যদি (!palette) {
                যদি (SDL_ISPIXELFORMAT_ALPHA(format)) {
                    // No need to add the colorkey, transparency is in the alpha channel
                } অন্যথা {
                    // Only set the colorkey information
                    set_colorkey_by_color = true;
                    convert_colorkey = false;
                }
            } অন্যথা {
                set_colorkey_by_color = true;
            }
        } অন্যথা {
            set_colorkey_by_color = true;
        }

        যদি (set_colorkey_by_color) {
            SDL_Surface *tmp;
            SDL_Surface *tmp2;
            পূর্ণসংখ্যা converted_colorkey = 0;

            // Create a dummy surface to get the colorkey converted
            tmp = SDL_CreateSurfaceUninitialized(1, 1, surface->format);
            যদি (!tmp) {
                যাও error;
            }

            // Share the palette, if any
            যদি (surface->palette) {
                SDL_SetSurfacePalette(tmp, surface->palette);
            }

            SDL_FillSurfaceRect(tmp, ফাঁকা, surface->map.info.colorkey);

            tmp->map.info.flags &= ~SDL_COPY_COLORKEY;

            // Conversion of the colorkey
            tmp2 = SDL_ConvertSurfaceAndColorspace(tmp, format, palette, colorspace, props);
            যদি (!tmp2) {
                SDL_DestroySurface(tmp);
                যাও error;
            }

            // Get the converted colorkey
            SDL_memcpy(&converted_colorkey, tmp2->pixels, tmp2->fmt->bytes_per_pixel);

            SDL_DestroySurface(tmp);
            SDL_DestroySurface(tmp2);

            // Set the converted colorkey on the new surface
            SDL_Set_Surface_Color_চাবি(convert, true, converted_colorkey);

            // This is needed when converting for 3D texture upload
            যদি (convert_colorkey) {
                SDL_ConvertColorkeyToAlpha(convert, true);
            }
        }
    }

end:
    যদি (অস্থায়ী_palette) {
        SDL_DestroyPalette(অস্থায়ী_palette);
    }

    SDL_SetSurfaceClipRect(convert, &surface->clip_rect);

    /* Enable alpha blending by default if the new surface has an
     * alpha channel or alpha modulation */
    যদি (SDL_ISPIXELFORMAT_ALPHA(format) ||
        (copy_flags & SDL_COPY_MODULATE_ALPHA)) {
        SDL_SetSurfaceBlendMode(convert, SDL_BLENDMODE_BLEND);
    }
    যদি (copy_flags & SDL_COPY_RLE_DESIRED) {
        SDL_SetSurfaceRLE(convert, true);
    }

    // Copy alternate images
    জন্য (পূর্ণসংখ্যা i = 0; i < surface->অঙ্ক_images; ++i) {
        যদি (!SDL_AddSurfaceAlternateImage(convert, surface->images[i])) {
            যাও error;
        }
    }

    // Copy properties
    যদি (surface->props) {
        যদি (!SDL_CopyProperties(surface->props, SDL_GetSurfaceProperties(convert))) {
            যাও error;
        }

        // Make sure the new surface doesn't reference an old SDL2 surface.
        SDL_ClearProperty(SDL_GetSurfaceProperties(convert), "sdl2-compat.surface2");
    }

    // We're ready to go!
    ফেরত convert;

error:
    যদি (অস্থায়ী_palette) {
        SDL_DestroyPalette(অস্থায়ী_palette);
    }
    যদি (convert) {
        SDL_DestroySurface(convert);
    }
    ফেরত ফাঁকা;
}

SDL_Surface *SDL_ConvertSurfaceAndColorspace(SDL_Surface *surface, SDL_PixelFormat format, SDL_Palette *palette, SDL_Colorspace colorspace, SDL_PropertiesID props)
{
    ফেরত SDL_ConvertSurfaceRectAndColorspace(surface, ফাঁকা, format, palette, colorspace, props);
}

SDL_Surface *SDL_RotateSurface(SDL_Surface *surface, দশমিক angle)
{
    SDL_Surface *rotated = ফাঁকা;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        ফেরত ফাঁকা;
    }

    SDL_Rect rect_dest;
    দ্বিগুণ cangle, sangle;
    SDL_FPoint center = { surface->w * 0.5f, surface->h * 0.5f };
    SDLgfx_rotozoom_Surface_আকার_Trig(surface->w, surface->h, angle, &center, &rect_dest, &cangle, &sangle);

    // This function requires a 32-bit surface or 8-bit surface with a colorkey
    যদি ((SDL_BITSPERPIXEL(surface->format) == 32 && SDL_PIXELLAYOUT(surface->format) == SDL_PACKEDLAYOUT_8888) ||
        (surface->format == SDL_PIXELFORMAT_INDEX8 && SDL_Surface_Has_Color_চাবি(surface))) {
        rotated = SDLgfx_rotateSurface(surface, angle, 1, 0, 0, &rect_dest, cangle, sangle, &center);
    } অন্যথা {
        SDL_Surface *convert = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);
        যদি (convert) {
            SDL_Surface *tmp = SDLgfx_rotateSurface(convert, angle, 1, 0, 0, &rect_dest, cangle, sangle, &center);
            যদি (tmp) {
                rotated = SDL_ConvertSurfaceAndColorspace(tmp, surface->format, surface->palette, surface->colorspace, surface->props);
                SDL_DestroySurface(tmp);
            }
            SDL_DestroySurface(convert);
        }
    }

    যদি (rotated) {
        যদি (SDL_HasProperty(surface->props, SDL_PROP_SURFACE_ROTATION_FLOAT)) {
            ধ্রুবক দশমিক rotation = (SDL_Get_সংখ্যা_Property(surface->props, SDL_PROP_SURFACE_ROTATION_FLOAT, 0) - angle);
            SDL_SetFloatProperty(SDL_GetSurfaceProperties(rotated), SDL_PROP_SURFACE_ROTATION_FLOAT, rotation);
        }
    }

    ফেরত rotated;
}

SDL_Surface *SDL_DuplicateSurface(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        ফেরত ফাঁকা;
    }

    ফেরত SDL_ConvertSurfaceAndColorspace(surface, surface->format, surface->palette, surface->colorspace, surface->props);
}

SDL_Surface *SDL_ScaleSurface(SDL_Surface *surface, পূর্ণসংখ্যা width, পূর্ণসংখ্যা height, SDL_ScaleMode scaleMode)
{
    SDL_Surface *convert = ফাঁকা;
    Uint32 copy_flags;
    SDL_Color copy_color;
    bool rc;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        যাও error;
    }

    যদি (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // We can't directly scale a YUV surface (yet!)
        SDL_Surface *tmp = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        যদি (!tmp) {
            ফেরত ফাঁকা;
        }

        SDL_Surface *scaled = SDL_ScaleSurface(tmp, width, height, scaleMode);
        SDL_DestroySurface(tmp);
        যদি (!scaled) {
            ফেরত ফাঁকা;
        }

        SDL_Surface *ফলাফল = SDL_ConvertSurfaceAndColorspace(scaled, surface->format, ফাঁকা, surface->colorspace, surface->props);
        SDL_DestroySurface(scaled);
        ফেরত ফলাফল;
    }

    যদি (SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        // Linear scaling requires conversion to RGBA and then slow pixel color lookup
        scaleMode = SDL_SCALEMODE_NEAREST;
    }

    // Create a new surface with the desired size
    যদি (surface->pixels || SDL_MUSTLOCK(surface)) {
        convert = SDL_CreateSurfaceUninitialized(width, height, surface->format);
    } অন্যথা {
        convert = SDL_CreateSurfaceFrom(width, height, surface->format, ফাঁকা, 0);
    }
    যদি (!convert) {
        যাও error;
    }
    SDL_SetSurfacePalette(convert, surface->palette);
    SDL_SetSurfaceColorspace(convert, surface->colorspace);
    SDL_SetSurfaceRLE(convert, SDL_SurfaceHasRLE(surface));

    যদি (surface->pixels || SDL_MUSTLOCK(surface)) {
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

        rc = SDL_BlitSurfaceScaled(surface, ফাঁকা, convert, ফাঁকা, scaleMode);

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
    } অন্যথা {
        rc = true;
    }

    // SDL_BlitSurfaceScaled failed, and so the conversion
    যদি (!rc) {
        যাও error;
    }

    // We're ready to go!
    ফেরত convert;

error:
    যদি (convert) {
        SDL_DestroySurface(convert);
    }
    ফেরত ফাঁকা;
}

SDL_Surface *SDL_ConvertSurfaceRect(SDL_Surface *surface, ধ্রুবক SDL_Rect *rect, SDL_PixelFormat format)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        ফেরত ফাঁকা;
    }

    ফেরত SDL_ConvertSurfaceRectAndColorspace(surface, rect, format, ফাঁকা, SDL_GetDefaultColorspaceForFormat(format), surface->props);
}

SDL_Surface *SDL_ConvertSurface(SDL_Surface *surface, SDL_PixelFormat format)
{
    ফেরত SDL_ConvertSurfaceRect(surface, ফাঁকা, format);
}

SDL_Surface *SDL_DuplicatePixels(পূর্ণসংখ্যা width, পূর্ণসংখ্যা height, SDL_PixelFormat format, SDL_Colorspace colorspace, শূন্য *pixels, পূর্ণসংখ্যা pitch)
{
    SDL_Surface *surface;
    যদি (pixels) {
        surface = SDL_CreateSurfaceUninitialized(width, height, format);
    } অন্যথা {
        surface = SDL_CreateSurfaceFrom(width, height, format, ফাঁকা, 0);
    }
    যদি (!surface) {
        ফেরত ফাঁকা;
    }
    SDL_SetSurfaceColorspace(surface, colorspace);

    যদি (surface->pixels) {
        পূর্ণসংখ্যা দৈর্ঘ্য = width * SDL_BYTESPERPIXEL(format);
        Uint8 *src = (Uint8 *)pixels;
        Uint8 *dst = (Uint8 *)surface->pixels;
        পূর্ণসংখ্যা rows = height;
        যখন (rows--) {
            SDL_memcpy(dst, src, দৈর্ঘ্য);
            dst += surface->pitch;
            src += pitch;
        }
    }
    ফেরত surface;
}

bool SDL_ConvertPixelsAndColorspace(পূর্ণসংখ্যা width, পূর্ণসংখ্যা height,
                      SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ধ্রুবক শূন্য *src, পূর্ণসংখ্যা src_pitch,
                      SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, শূন্য *dst, পূর্ণসংখ্যা dst_pitch)
{
    SDL_Surface src_surface;
    SDL_Surface dst_surface;
    SDL_Rect rect;
    শূন্য *nonconst_src = (শূন্য *)src;
    bool ফলাফল;

    CHECK_PARAM(!src) {
        ফেরত SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!src_pitch) {
        ফেরত SDL_InvalidParamError("src_pitch");
    }
    CHECK_PARAM(!dst) {
        ফেরত SDL_InvalidParamError("dst");
    }
    CHECK_PARAM(!dst_pitch) {
        ফেরত SDL_InvalidParamError("dst_pitch");
    }

    যদি (src_colorspace == SDL_COLORSPACE_UNKNOWN) {
        src_colorspace = SDL_GetDefaultColorspaceForFormat(src_format);
    }
    যদি (dst_colorspace == SDL_COLORSPACE_UNKNOWN) {
        dst_colorspace = SDL_GetDefaultColorspaceForFormat(dst_format);
    }

    যদি (src_format == SDL_PIXELFORMAT_MJPG) {
        ফেরত SDL_ConvertPixels_STB(width, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    }

#ifdef SDL_HAVE_YUV
    যদি (SDL_ISPIXELFORMAT_FOURCC(src_format) && SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        ফেরত SDL_ConvertPixels_YUV_to_YUV(width, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } অন্যথা যদি (SDL_ISPIXELFORMAT_FOURCC(src_format)) {
        ফেরত SDL_ConvertPixels_YUV_to_RGB(width, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } অন্যথা যদি (SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        ফেরত SDL_ConvertPixels_RGB_to_YUV(width, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    }
#অন্যথা
    যদি (SDL_ISPIXELFORMAT_FOURCC(src_format) || SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        ফেরত SDL_SetError("SDL not built with YUV support");
    }
#endif

    // Fast path for same format copy
    যদি (src_format == dst_format && src_colorspace == dst_colorspace) {
        যদি (src_pitch == dst_pitch) {
            SDL_memcpy(dst, src, height * src_pitch);
        } অন্যথা {
            পূর্ণসংখ্যা i;
            ধ্রুবক পূর্ণসংখ্যা bpp = SDL_BYTESPERPIXEL(src_format);
            width *= bpp;
            জন্য (i = height; i--;) {
                SDL_memcpy(dst, src, width);
                src = (ধ্রুবক Uint8 *)src + src_pitch;
                dst = (Uint8 *)dst + dst_pitch;
            }
        }
        ফেরত true;
    }

    যদি (!SDL_InitializeSurface(&src_surface, width, height, src_format, src_colorspace, src_properties, nonconst_src, src_pitch, true)) {
        ফেরত false;
    }
    SDL_SetSurfaceBlendMode(&src_surface, SDL_BLENDMODE_NONE);

    যদি (!SDL_InitializeSurface(&dst_surface, width, height, dst_format, dst_colorspace, dst_properties, dst, dst_pitch, true)) {
        ফেরত false;
    }

    // Set up the rect and go!
    rect.x = 0;
    rect.y = 0;
    rect.w = width;
    rect.h = height;
    ফলাফল = SDL_BlitSurfaceUnchecked(&src_surface, &rect, &dst_surface, &rect);

    SDL_DestroySurface(&src_surface);
    SDL_DestroySurface(&dst_surface);

    ফেরত ফলাফল;
}

bool SDL_ConvertPixels(পূর্ণসংখ্যা width, পূর্ণসংখ্যা height, SDL_PixelFormat src_format, ধ্রুবক শূন্য *src, পূর্ণসংখ্যা src_pitch, SDL_PixelFormat dst_format, শূন্য *dst, পূর্ণসংখ্যা dst_pitch)
{
    ফেরত SDL_ConvertPixelsAndColorspace(width, height,
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

স্থির শূন্য SDL_PremultiplyAlpha_AXYZ8888(পূর্ণসংখ্যা width, পূর্ণসংখ্যা height, ধ্রুবক শূন্য *src, পূর্ণসংখ্যা src_pitch, শূন্য *dst, পূর্ণসংখ্যা dst_pitch)
{
    পূর্ণসংখ্যা c;
    Uint32 srcpixel;
    Uint32 srcR, srcG, srcB, srcA;
    Uint32 dstpixel;
    Uint32 dstR, dstG, dstB, dstA;

    যখন (height--) {
        ধ্রুবক Uint32 *src_px = (ধ্রুবক Uint32 *)src;
        Uint32 *dst_px = (Uint32 *)dst;
        জন্য (c = width; c; --c) {
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
        src = (ধ্রুবক Uint8 *)src + src_pitch;
        dst = (Uint8 *)dst + dst_pitch;
    }
}

স্থির শূন্য SDL_PremultiplyAlpha_XYZA8888(পূর্ণসংখ্যা width, পূর্ণসংখ্যা height, ধ্রুবক শূন্য *src, পূর্ণসংখ্যা src_pitch, শূন্য *dst, পূর্ণসংখ্যা dst_pitch)
{
    পূর্ণসংখ্যা c;
    Uint32 srcpixel;
    Uint32 srcR, srcG, srcB, srcA;
    Uint32 dstpixel;
    Uint32 dstR, dstG, dstB, dstA;

    যখন (height--) {
        ধ্রুবক Uint32 *src_px = (ধ্রুবক Uint32 *)src;
        Uint32 *dst_px = (Uint32 *)dst;
        জন্য (c = width; c; --c) {
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
        src = (ধ্রুবক Uint8 *)src + src_pitch;
        dst = (Uint8 *)dst + dst_pitch;
    }
}

স্থির শূন্য SDL_PremultiplyAlpha_AXYZ128(পূর্ণসংখ্যা width, পূর্ণসংখ্যা height, ধ্রুবক শূন্য *src, পূর্ণসংখ্যা src_pitch, শূন্য *dst, পূর্ণসংখ্যা dst_pitch)
{
    পূর্ণসংখ্যা c;
    দশমিক flR, flG, flB, flA;

    যখন (height--) {
        ধ্রুবক দশমিক *src_px = (ধ্রুবক দশমিক *)src;
        দশমিক *dst_px = (দশমিক *)dst;
        জন্য (c = width; c; --c) {
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
        src = (ধ্রুবক Uint8 *)src + src_pitch;
        dst = (Uint8 *)dst + dst_pitch;
    }
}

স্থির bool SDL_PremultiplyAlphaPixelsAndColorspace(পূর্ণসংখ্যা width, পূর্ণসংখ্যা height, SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ধ্রুবক শূন্য *src, পূর্ণসংখ্যা src_pitch, SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, শূন্য *dst, পূর্ণসংখ্যা dst_pitch, bool linear)
{
    SDL_Surface *convert = ফাঁকা;
    শূন্য *final_dst = dst;
    পূর্ণসংখ্যা final_dst_pitch = dst_pitch;
    SDL_PixelFormat format;
    SDL_Colorspace colorspace;
    bool ফলাফল = false;

    CHECK_PARAM(!src) {
        ফেরত SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!src_pitch) {
        ফেরত SDL_InvalidParamError("src_pitch");
    }
    CHECK_PARAM(!dst) {
        ফেরত SDL_InvalidParamError("dst");
    }
    CHECK_PARAM(!dst_pitch) {
        ফেরত SDL_InvalidParamError("dst_pitch");
    }

    // Use a high precision format if we're converting to linear colorspace or using high precision pixel formats
    যদি (linear ||
        SDL_ISPIXELFORMAT_10BIT(src_format) || SDL_BITSPERPIXEL(src_format) > 32 ||
        SDL_ISPIXELFORMAT_10BIT(dst_format) || SDL_BITSPERPIXEL(dst_format) > 32) {
        যদি (src_format == SDL_PIXELFORMAT_ARGB128_FLOAT ||
            src_format == SDL_PIXELFORMAT_ABGR128_FLOAT) {
            format = src_format;
        } অন্যথা {
            format = SDL_PIXELFORMAT_ARGB128_FLOAT;
        }
    } অন্যথা {
        যদি (src_format == SDL_PIXELFORMAT_ARGB8888 ||
            src_format == SDL_PIXELFORMAT_ABGR8888 ||
            src_format == SDL_PIXELFORMAT_RGBA8888 ||
            src_format == SDL_PIXELFORMAT_BGRA8888) {
            format = src_format;
        } অন্যথা {
            format = SDL_PIXELFORMAT_ARGB8888;
        }
    }
    যদি (linear) {
        colorspace = SDL_COLORSPACE_SRGB_LINEAR;
    } অন্যথা {
        colorspace = SDL_COLORSPACE_SRGB;
    }

    যদি (src_format != format || src_colorspace != colorspace) {
        convert = SDL_CreateSurfaceUninitialized(width, height, format);
        যদি (!convert) {
            যাও done;
        }
        যদি (!SDL_ConvertPixelsAndColorspace(width, height, src_format, src_colorspace, src_properties, src, src_pitch, format, colorspace, 0, convert->pixels, convert->pitch)) {
            যাও done;
        }

        src = convert->pixels;
        src_pitch = convert->pitch;
        dst = convert->pixels;
        dst_pitch = convert->pitch;

    } অন্যথা যদি (dst_format != format || dst_colorspace != colorspace) {
        convert = SDL_CreateSurfaceUninitialized(width, height, format);
        যদি (!convert) {
            যাও done;
        }
        dst = convert->pixels;
        dst_pitch = convert->pitch;
    }

    নির্বাচন (format) {
    ক্ষেত্র SDL_PIXELFORMAT_ARGB8888:
    ক্ষেত্র SDL_PIXELFORMAT_ABGR8888:
        SDL_PremultiplyAlpha_AXYZ8888(width, height, src, src_pitch, dst, dst_pitch);
        বিরতি;
    ক্ষেত্র SDL_PIXELFORMAT_RGBA8888:
    ক্ষেত্র SDL_PIXELFORMAT_BGRA8888:
        SDL_PremultiplyAlpha_XYZA8888(width, height, src, src_pitch, dst, dst_pitch);
        বিরতি;
    ক্ষেত্র SDL_PIXELFORMAT_ARGB128_FLOAT:
    ক্ষেত্র SDL_PIXELFORMAT_ABGR128_FLOAT:
        SDL_PremultiplyAlpha_AXYZ128(width, height, src, src_pitch, dst, dst_pitch);
        বিরতি;
    পূর্বনির্ধারিত:
        SDL_SetError("Unexpected internal pixel format");
        যাও done;
    }

    যদি (dst != final_dst) {
        যদি (!SDL_ConvertPixelsAndColorspace(width, height, format, colorspace, 0, convert->pixels, convert->pitch, dst_format, dst_colorspace, dst_properties, final_dst, final_dst_pitch)) {
            যাও done;
        }
    }
    ফলাফল = true;

done:
    যদি (convert) {
        SDL_DestroySurface(convert);
    }
    ফেরত ফলাফল;
}

bool SDL_PremultiplyAlpha(পূর্ণসংখ্যা width, পূর্ণসংখ্যা height,
                         SDL_PixelFormat src_format, ধ্রুবক শূন্য *src, পূর্ণসংখ্যা src_pitch,
                         SDL_PixelFormat dst_format, শূন্য *dst, পূর্ণসংখ্যা dst_pitch, bool linear)
{
    SDL_Colorspace src_colorspace = SDL_GetDefaultColorspaceForFormat(src_format);
    SDL_Colorspace dst_colorspace = SDL_GetDefaultColorspaceForFormat(dst_format);

    ফেরত SDL_PremultiplyAlphaPixelsAndColorspace(width, height, src_format, src_colorspace, 0, src, src_pitch, dst_format, dst_colorspace, 0, dst, dst_pitch, linear);
}

bool SDL_PremultiplySurfaceAlpha(SDL_Surface *surface, bool linear)
{
    SDL_Colorspace colorspace;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ফেরত SDL_InvalidParamError("surface");
    }

    colorspace = surface->colorspace;

    ফেরত SDL_PremultiplyAlphaPixelsAndColorspace(surface->w, surface->h, surface->format, colorspace, surface->props, surface->pixels, surface->pitch, surface->format, colorspace, surface->props, surface->pixels, surface->pitch, linear);
}

bool SDL_ClearSurface(SDL_Surface *surface, দশমিক r, দশমিক g, দশমিক b, দশমিক a)
{
    SDL_Rect clip_rect;
    bool ফলাফল = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ফেরত SDL_InvalidParamError("surface");
    }

    SDL_GetSurfaceClipRect(surface, &clip_rect);
    SDL_SetSurfaceClipRect(surface, ফাঁকা);

    যদি (!SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_BYTESPERPIXEL(surface->format) <= আকার(Uint32)) {
        Uint32 color;

        color = SDL_MapSurfaceRGBA(surface,
                    (Uint8)SDL_roundf(SDL_clamp(r, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(g, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(b, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(a, 0.0f, 1.0f) * 255.0f));
        ফলাফল = SDL_FillSurfaceRect(surface, ফাঁকা, color);
    } অন্যথা যদি (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // We can't directly set an RGB value on a YUV surface
        SDL_Surface *tmp = SDL_CreateSurfaceUninitialized(surface->w, surface->h, SDL_PIXELFORMAT_ARGB8888);
        যদি (!tmp) {
            যাও done;
        }

        যদি (SDL_ClearSurface(tmp, r, g, b, a)) {
            ফলাফল = SDL_ConvertPixelsAndColorspace(surface->w, surface->h, tmp->format, tmp->colorspace, tmp->props, tmp->pixels, tmp->pitch, surface->format, surface->colorspace, surface->props, surface->pixels, surface->pitch);
        }
        SDL_DestroySurface(tmp);
    } অন্যথা {
        // Take advantage of blit color conversion
        SDL_Surface *tmp = SDL_CreateSurfaceUninitialized(1, 1, SDL_PIXELFORMAT_RGBA128_FLOAT);
        যদি (!tmp) {
            যাও done;
        }
        SDL_SetSurfaceColorspace(tmp, surface->colorspace);
        SDL_SetSurfaceBlendMode(tmp, SDL_BLENDMODE_NONE);

        দশমিক *pixels = (দশমিক *)tmp->pixels;
        pixels[0] = r;
        pixels[1] = g;
        pixels[2] = b;
        pixels[3] = a;

        ফলাফল = SDL_BlitSurfaceScaled(tmp, ফাঁকা, surface, ফাঁকা, SDL_SCALEMODE_NEAREST);
        SDL_DestroySurface(tmp);
    }

done:
    SDL_SetSurfaceClipRect(surface, &clip_rect);

    ফেরত ফলাফল;
}

Uint32 SDL_MapSurfaceRGB(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b)
{
    ফেরত SDL_MapSurfaceRGBA(surface, r, g, b, SDL_ALPHA_OPAQUE);
}

Uint32 SDL_MapSurfaceRGBA(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        ফেরত true;
    }
    ফেরত SDL_MapRGBA(surface->fmt, surface->palette, r, g, b, a);
}

// This function Copyright 2023 Collabora Ltd., contributed to SDL under the ZLib license
bool SDL_ReadSurfacePixel(SDL_Surface *surface, পূর্ণসংখ্যা x, পূর্ণসংখ্যা y, Uint8 *r, Uint8 *g, Uint8 *b, Uint8 *a)
{
    Uint32 pixel = 0;
    size_t bytes_per_pixel;
    Uint8 unused;
    Uint8 *p;
    bool ফলাফল = false;

    যদি (r) {
        *r = 0;
    } অন্যথা {
        r = &unused;
    }

    যদি (g) {
        *g = 0;
    } অন্যথা {
        g = &unused;
    }

    যদি (b) {
        *b = 0;
    } অন্যথা {
        b = &unused;
    }

    যদি (a) {
        *a = 0;
    } অন্যথা {
        a = &unused;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        ফেরত SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        ফেরত SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        ফেরত SDL_InvalidParamError("y");
    }

    bytes_per_pixel = SDL_BYTESPERPIXEL(surface->format);

    যদি (SDL_MUSTLOCK(surface)) {
        যদি (!SDL_LockSurface(surface)) {
            ফেরত false;
        }
    }

    p = (Uint8 *)surface->pixels + y * surface->pitch + x * bytes_per_pixel;

    যদি (bytes_per_pixel <= আকার(pixel) &&
        !SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_COLORSPACEPRIMARIES(surface->colorspace) == SDL_COLOR_PRIMARIES_BT709) {
        /* Fill the appropriate number of least-significant bytes of pixel,
         * leaving the most-significant bytes set to zero */
#যদি SDL_BYTEORDER == SDL_BIG_ENDIAN
        SDL_memcpy(((Uint8 *)&pixel) + (আকার(pixel) - bytes_per_pixel), p, bytes_per_pixel);
#অন্যথা
        SDL_memcpy(&pixel, p, bytes_per_pixel);
#endif
        SDL_GetRGBA(pixel, surface->fmt, surface->palette, r, g, b, a);
        ফলাফল = true;
    } অন্যথা যদি (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // FIXME: We need code to extract a single macroblock from a YUV surface
        SDL_Surface *converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        যদি (converted) {
            ফলাফল = SDL_ReadSurfacePixel(converted, x, y, r, g, b, a);
            SDL_DestroySurface(converted);
        }
    } অন্যথা {
        // This is really slow, but it gets the job done
        Uint8 rgba[4];

        যদি (SDL_ConvertPixelsAndColorspace(1, 1, surface->format, surface->colorspace, surface->props, p, surface->pitch, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, rgba, আকার(rgba))) {
            *r = rgba[0];
            *g = rgba[1];
            *b = rgba[2];
            *a = rgba[3];
            ফলাফল = true;
        }
    }

    যদি (SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }
    ফেরত ফলাফল;
}

bool SDL_ReadSurfacePixelFloat(SDL_Surface *surface, পূর্ণসংখ্যা x, পূর্ণসংখ্যা y, দশমিক *r, দশমিক *g, দশমিক *b, দশমিক *a)
{
    দশমিক unused;
    bool ফলাফল = false;

    যদি (r) {
        *r = 0.0f;
    } অন্যথা {
        r = &unused;
    }

    যদি (g) {
        *g = 0.0f;
    } অন্যথা {
        g = &unused;
    }

    যদি (b) {
        *b = 0.0f;
    } অন্যথা {
        b = &unused;
    }

    যদি (a) {
        *a = 0.0f;
    } অন্যথা {
        a = &unused;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        ফেরত SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        ফেরত SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        ফেরত SDL_InvalidParamError("y");
    }

    যদি (SDL_BYTESPERPIXEL(surface->format) <= আকার(Uint32) &&
        !SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_COLORSPACEPRIMARIES(surface->colorspace) == SDL_COLOR_PRIMARIES_BT709) {
        Uint8 r8, g8, b8, a8;

        যদি (SDL_ReadSurfacePixel(surface, x, y, &r8, &g8, &b8, &a8)) {
            *r = (দশমিক)r8 / 255.0f;
            *g = (দশমিক)g8 / 255.0f;
            *b = (দশমিক)b8 / 255.0f;
            *a = (দশমিক)a8 / 255.0f;
            ফলাফল = true;
        }
    } অন্যথা যদি (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // FIXME: We need code to extract a single macroblock from a YUV surface
        SDL_Surface *converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        যদি (converted) {
            ফলাফল = SDL_ReadSurfacePixelFloat(converted, x, y, r, g, b, a);
            SDL_DestroySurface(converted);
        }
    } অন্যথা {
        // This is really slow, but it gets the job done
        দশমিক rgba[4];
        Uint8 *p;

        যদি (SDL_MUSTLOCK(surface)) {
            যদি (!SDL_LockSurface(surface)) {
                ফেরত false;
            }
        }

        p = (Uint8 *)surface->pixels + y * surface->pitch + x * SDL_BYTESPERPIXEL(surface->format);

        যদি (surface->format == SDL_PIXELFORMAT_RGBA128_FLOAT) {
            SDL_memcpy(rgba, p, আকার(rgba));
            ফলাফল = true;
        } অন্যথা {
            SDL_Colorspace src_colorspace = surface->colorspace;
            SDL_Colorspace dst_colorspace = (src_colorspace == SDL_COLORSPACE_SRGB_LINEAR ? SDL_COLORSPACE_SRGB_LINEAR : SDL_COLORSPACE_SRGB);

            যদি (SDL_ConvertPixelsAndColorspace(1, 1, surface->format, src_colorspace, surface->props, p, surface->pitch, SDL_PIXELFORMAT_RGBA128_FLOAT, dst_colorspace, 0, rgba, আকার(rgba))) {
                ফলাফল = true;
            }
        }

        যদি (ফলাফল) {
            *r = rgba[0];
            *g = rgba[1];
            *b = rgba[2];
            *a = rgba[3];
        }

        যদি (SDL_MUSTLOCK(surface)) {
            SDL_UnlockSurface(surface);
        }
    }
    ফেরত ফলাফল;
}

bool SDL_WriteSurfacePixel(SDL_Surface *surface, পূর্ণসংখ্যা x, পূর্ণসংখ্যা y, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    Uint32 pixel = 0;
    size_t bytes_per_pixel;
    Uint8 *p;
    bool ফলাফল = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        ফেরত SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        ফেরত SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        ফেরত SDL_InvalidParamError("y");
    }

    bytes_per_pixel = SDL_BYTESPERPIXEL(surface->format);

    যদি (SDL_MUSTLOCK(surface)) {
        যদি (!SDL_LockSurface(surface)) {
            ফেরত false;
        }
    }

    p = (Uint8 *)surface->pixels + y * surface->pitch + x * bytes_per_pixel;

    যদি (bytes_per_pixel <= আকার(pixel) && !SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        pixel = SDL_MapRGBA(surface->fmt, surface->palette, r, g, b, a);
#যদি SDL_BYTEORDER == SDL_BIG_ENDIAN
        SDL_memcpy(p, ((Uint8 *)&pixel) + (আকার(pixel) - bytes_per_pixel), bytes_per_pixel);
#অন্যথা
        SDL_memcpy(p, &pixel, bytes_per_pixel);
#endif
        ফলাফল = true;
    } অন্যথা যদি (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        ফলাফল = SDL_Unsupported();
    } অন্যথা {
        // This is really slow, but it gets the job done
        Uint8 rgba[4];

        rgba[0] = r;
        rgba[1] = g;
        rgba[2] = b;
        rgba[3] = a;
        ফলাফল = SDL_ConvertPixelsAndColorspace(1, 1, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, rgba, আকার(rgba), surface->format, surface->colorspace, surface->props, p, surface->pitch);
    }

    যদি (SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }
    ফেরত ফলাফল;
}

bool SDL_WriteSurfacePixelFloat(SDL_Surface *surface, পূর্ণসংখ্যা x, পূর্ণসংখ্যা y, দশমিক r, দশমিক g, দশমিক b, দশমিক a)
{
    bool ফলাফল = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        ফেরত SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        ফেরত SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        ফেরত SDL_InvalidParamError("y");
    }

    যদি (SDL_BYTESPERPIXEL(surface->format) <= আকার(Uint32) && !SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        Uint8 r8, g8, b8, a8;

        r8 = (Uint8)SDL_round(SDL_clamp(r, 0.0f, 1.0f) * 255.0f);
        g8 = (Uint8)SDL_round(SDL_clamp(g, 0.0f, 1.0f) * 255.0f);
        b8 = (Uint8)SDL_round(SDL_clamp(b, 0.0f, 1.0f) * 255.0f);
        a8 = (Uint8)SDL_round(SDL_clamp(a, 0.0f, 1.0f) * 255.0f);
        যদি (SDL_WriteSurfacePixel(surface, x, y, r8, g8, b8, a8)) {
            ফলাফল = true;
        }
    } অন্যথা যদি (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        ফলাফল = SDL_Unsupported();
    } অন্যথা {
        // This is really slow, but it gets the job done
        দশমিক rgba[4];
        Uint8 *p;

        যদি (SDL_MUSTLOCK(surface)) {
            যদি (!SDL_LockSurface(surface)) {
                ফেরত false;
            }
        }

        p = (Uint8 *)surface->pixels + y * surface->pitch + x * SDL_BYTESPERPIXEL(surface->format);

        rgba[0] = r;
        rgba[1] = g;
        rgba[2] = b;
        rgba[3] = a;

        যদি (surface->format == SDL_PIXELFORMAT_RGBA128_FLOAT) {
            SDL_memcpy(p, rgba, আকার(rgba));
            ফলাফল = true;
        } অন্যথা {
            SDL_Colorspace dst_colorspace = surface->colorspace;
            SDL_Colorspace src_colorspace = (dst_colorspace == SDL_COLORSPACE_SRGB_LINEAR ? SDL_COLORSPACE_SRGB_LINEAR : SDL_COLORSPACE_SRGB);

            ফলাফল = SDL_ConvertPixelsAndColorspace(1, 1, SDL_PIXELFORMAT_RGBA128_FLOAT, src_colorspace, 0, rgba, আকার(rgba), surface->format, dst_colorspace, surface->props, p, surface->pitch);
        }

        যদি (SDL_MUSTLOCK(surface)) {
            SDL_UnlockSurface(surface);
        }
    }
    ফেরত ফলাফল;
}

/*
 * Free a surface created by the above function.
 */
শূন্য SDL_DestroySurface(SDL_Surface *surface)
{
    যদি (!SDL_SurfaceValid(surface)) {
        ফেরত;
    }
    যদি (surface->internal_flags & SDL_INTERNAL_SURFACE_DONTFREE) {
        ফেরত;
    }
    যদি (--surface->refcount > 0) {
        ফেরত;
    }

    SDL_RemoveSurfaceAlternateImages(surface);

    SDL_DestroyProperties(surface->props);

    SDL_InvalidateMap(&surface->map);

    যখন (surface->locked > 0) {
        SDL_UnlockSurface(surface);
    }
#ifdef SDL_HAVE_RLE
    যদি (surface->internal_flags & SDL_INTERNAL_SURFACE_RLEACCEL) {
        SDL_UnRLESurface(surface);
    }
#endif
    SDL_SetSurfacePalette(surface, ফাঁকা);

    যদি (surface->flags & SDL_SURFACE_PREALLOCATED) {
        // Don't free
    } অন্যথা যদি (surface->flags & SDL_SURFACE_SIMD_ALIGNED) {
        // Free aligned
        SDL_aligned_free(surface->pixels);
    } অন্যথা {
        // Normal
        SDL_free(surface->pixels);
    }

    surface->reserved = ফাঁকা;

    যদি (!(surface->internal_flags & SDL_INTERNAL_SURFACE_স্তূপ)) {
        SDL_free(surface);
    }
}

SDL_Surface *SDL_LoadSurface_IO(SDL_IOStream *src, bool closeio)
{
    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        ফেরত ফাঁকা;
    }

    যদি (SDL_IsBMP(src)) {
        ফেরত SDL_LoadBMP_IO(src, closeio);
    } অন্যথা যদি (SDL_IsPNG(src)) {
        ফেরত SDL_LoadPNG_IO(src, closeio);
    } অন্যথা যদি (SDL_IsJPG(src)) {
        ফেরত SDL_LoadJPG_IO(src, closeio);
    } অন্যথা {
        যদি (closeio) {
            SDL_CloseIO(src);
        }
        SDL_SetError("Unsupported image format");
        ফেরত ফাঁকা;
    }
}

SDL_Surface *SDL_LoadSurface(ধ্রুবক অক্ষর *file)
{
    SDL_IOStream *stream = SDL_IOFromFile(file, "rb");
    যদি (!stream) {
        ফেরত ফাঁকা;
    }

    ফেরত SDL_LoadSurface_IO(stream, true);
}
