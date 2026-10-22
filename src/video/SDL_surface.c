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
#अन्तर्भाव "SDL_internal.h"

#अन्तर्भाव "SDL_sysvideo.h"
#अन्तर्भाव "SDL_video_c.h"
#अन्तर्भाव "SDL_RLEaccel_c.h"
#अन्तर्भाव "SDL_pixels_c.h"
#अन्तर्भाव "SDL_rotate.h"
#अन्तर्भाव "SDL_stb_c.h"
#अन्तर्भाव "SDL_yuv_c.h"
#अन्तर्भाव "../render/SDL_sysrender.h"

#अन्तर्भाव "SDL_surface_c.h"


// Check to make sure we can safely check multiplication of surface w and pitch and it won't overflow size_t
SDL_COMPILE_TIME_ASSERT(surface_size_assumptions,
                        परिमाण(पूर्णाङ्क) == परिमाण(Sint32) && परिमाण(size_t) >= परिमाण(Sint32));

SDL_COMPILE_TIME_ASSERT(can_indicate_overflow, SDL_SIZE_MAX > SDL_MAX_SINT32);

// Magic!
स्थिर वर्ण SDL_surface_magic;

// Public routines

bool SDL_SurfaceValid(SDL_Surface *surface)
{
    प्रत्यागम (surface && surface->reserved == &SDL_surface_magic);
}

शून्य SDL_UpdateSurfaceLockFlag(SDL_Surface *surface)
{
    // We need to mark the surface as needing unlock while locked
    यदि ((surface->flags & SDL_SURFACE_LOCKED) ||
        (surface->internal_flags & SDL_INTERNAL_SURFACE_RLEACCEL)) {
        surface->flags |= SDL_SURFACE_LOCK_NEEDED;
    } अन्यथा {
        surface->flags &= ~SDL_SURFACE_LOCK_NEEDED;
    }
}

/*
 * Calculate the pad-aligned scanline width of a surface.
 *
 * for FOURCC, use SDL_CalculateYUVSize()
 */
स्थिर bool SDL_CalculateRGBSize(Uint32 format, size_t width, size_t height, size_t *size, size_t *pitch, bool minimal)
{
    यदि (SDL_BITSPERPIXEL(format) >= 8) {
        यदि (!SDL_size_mul_check_overflow(width, SDL_BYTESPERPIXEL(format), pitch)) {
            प्रत्यागम SDL_SetError("width * bpp would overflow");
        }
    } अन्यथा {
        यदि (!SDL_size_mul_check_overflow(width, SDL_BITSPERPIXEL(format), pitch)) {
            प्रत्यागम SDL_SetError("width * bpp would overflow");
        }
        यदि (!SDL_size_add_check_overflow(*pitch, 7, pitch)) {
            प्रत्यागम SDL_SetError("aligning pitch would overflow");
        }
        *pitch /= 8;
    }
    यदि (!minimal) {
        // 4-byte aligning for speed
        यदि (!SDL_size_add_check_overflow(*pitch, 3, pitch)) {
            प्रत्यागम SDL_SetError("aligning pitch would overflow");
        }
        *pitch &= ~3;
    }

    यदि (!SDL_size_mul_check_overflow(height, *pitch, size)) {
        प्रत्यागम SDL_SetError("height * pitch would overflow");
    }

    प्रत्यागम true;
}

bool SDL_CalculateSurfaceSize(SDL_PixelFormat format, पूर्णाङ्क width, पूर्णाङ्क height, size_t *size, size_t *pitch, bool minimalPitch)
{
    size_t p = 0, sz = 0;

    यदि (size) {
        *size = 0;
    }

    यदि (pitch) {
        *pitch = 0;
    }

    यदि (SDL_ISPIXELFORMAT_FOURCC(format)) {
        यदि (format == SDL_PIXELFORMAT_MJPG) {
            // We don't know in advance what it will be, we'll figure it out later.
            प्रत्यागम true;
        }

        यदि (!SDL_CalculateYUVSize(format, width, height, &sz, &p)) {
            // Overflow...
            प्रत्यागम false;
        }
    } अन्यथा {
        यदि (!SDL_CalculateRGBSize(format, width, height, &sz, &p, minimalPitch)) {
            // Overflow...
            प्रत्यागम false;
        }
    }

    यदि (size) {
        *size = sz;
    }

    यदि (pitch) {
        *pitch = p;
    }

    प्रत्यागम true;
}

स्थिर bool SDL_InitializeSurface(SDL_Surface *surface, पूर्णाङ्क width, पूर्णाङ्क height, SDL_PixelFormat format, SDL_Colorspace colorspace, SDL_PropertiesID props, शून्य *pixels, पूर्णाङ्क pitch, bool onstack)
{
    SDL_zerop(surface);

    surface->flags = SDL_SURFACE_PREALLOCATED;
    surface->format = format;
    surface->w = width;
    surface->h = height;
    surface->pixels = pixels;
    surface->pitch = pitch;
    surface->reserved = &SDL_surface_magic;

    यदि (onstack) {
        surface->internal_flags |= SDL_INTERNAL_SURFACE_चळत;
    }

    surface->fmt = SDL_GetPixelFormatDetails(format);
    यदि (!surface->fmt) {
        SDL_DestroySurface(surface);
        प्रत्यागम false;
    }

    // Initialize the clip rect
    surface->clip_rect.w = width;
    surface->clip_rect.h = height;

    // Allocate an empty mapping
    surface->map.info.r = 0xFF;
    surface->map.info.g = 0xFF;
    surface->map.info.b = 0xFF;
    surface->map.info.a = 0xFF;

    यदि (colorspace == SDL_COLORSPACE_UNKNOWN) {
        surface->colorspace = SDL_GetDefaultColorspaceForFormat(format);
    } अन्यथा {
        surface->colorspace = colorspace;
    }

    यदि (props) {
        यदि (!SDL_CopyProperties(props, SDL_GetSurfaceProperties(surface))) {
            SDL_DestroySurface(surface);
            प्रत्यागम false;
        }
    }

    // By default surfaces with an alpha mask are set up for blending
    यदि (SDL_ISPIXELFORMAT_ALPHA(surface->format)) {
        SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
    }

    // The surface is ready to go
    surface->refcount = 1;
    प्रत्यागम true;
}

/*
 * Create an empty surface of the appropriate depth using the given format
 */
स्थिर SDL_Surface *SDL_CreateSurfaceInternal(पूर्णाङ्क width, पूर्णाङ्क height, SDL_PixelFormat format, bool clear_surface)
{
    size_t pitch, size;
    SDL_Surface *surface;

    CHECK_PARAM(width < 0) {
        SDL_InvalidParamError("width");
        प्रत्यागम रिक्त;
    }

    CHECK_PARAM(height < 0) {
        SDL_InvalidParamError("height");
        प्रत्यागम रिक्त;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        प्रत्यागम रिक्त;
    }

    यदि (!SDL_CalculateSurfaceSize(format, width, height, &size, &pitch, false /* not minimal pitch */)) {
        // Overflow...
        प्रत्यागम रिक्त;
    }

    // Allocate and initialize the surface
    surface = (SDL_Surface *)SDL_malloc(परिमाण(*surface));
    यदि (!surface) {
        प्रत्यागम रिक्त;
    }

    यदि (!SDL_InitializeSurface(surface, width, height, format, SDL_COLORSPACE_UNKNOWN, 0, रिक्त, (पूर्णाङ्क)pitch, false)) {
        प्रत्यागम रिक्त;
    }

    यदि (surface->w && surface->h && format != SDL_PIXELFORMAT_MJPG) {
        surface->flags &= ~SDL_SURFACE_PREALLOCATED;
        यदि (SDL_GetHintBoolean("SDL_SURFACE_MALLOC", false)) {
            यदि (clear_surface) {
                surface->pixels = SDL_calloc(1, size);
            } अन्यथा {
                surface->pixels = SDL_malloc(size);
            }
        } अन्यथा {
            surface->flags |= SDL_SURFACE_SIMD_ALIGNED;
            यदि (clear_surface) {
                surface->pixels = SDL_aligned_alloc_zero(SDL_GetSIMDAlignment(), size);
            } अन्यथा {
                surface->pixels = SDL_aligned_alloc(SDL_GetSIMDAlignment(), size);
            }
        }
        यदि (!surface->pixels) {
            SDL_DestroySurface(surface);
            प्रत्यागम रिक्त;
        }
    }
    प्रत्यागम surface;
}

SDL_Surface *SDL_CreateSurfaceZeroed(पूर्णाङ्क width, पूर्णाङ्क height, SDL_PixelFormat format)
{
    प्रत्यागम SDL_CreateSurfaceInternal(width, height, format, true);
}

SDL_Surface *SDL_CreateSurfaceUninitialized(पूर्णाङ्क width, पूर्णाङ्क height, SDL_PixelFormat format)
{
    प्रत्यागम SDL_CreateSurfaceInternal(width, height, format, false);
}

SDL_Surface *SDL_CreateSurface(पूर्णाङ्क width, पूर्णाङ्क height, SDL_PixelFormat format)
{
    प्रत्यागम SDL_CreateSurfaceZeroed(width, height, format);
}


/*
 * Create an RGB surface from an existing memory buffer using the given
 * enum SDL_PIXELFORMAT_* format
 */
SDL_Surface *SDL_CreateSurfaceFrom(पूर्णाङ्क width, पूर्णाङ्क height, SDL_PixelFormat format, शून्य *pixels, पूर्णाङ्क pitch)
{
    CHECK_PARAM(width < 0) {
        SDL_InvalidParamError("width");
        प्रत्यागम रिक्त;
    }

    CHECK_PARAM(height < 0) {
        SDL_InvalidParamError("height");
        प्रत्यागम रिक्त;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        प्रत्यागम रिक्त;
    }

    यदि (pitch == 0 && !pixels) {
        // The application will fill these in later with valid values
    } अन्यथा {
        size_t minimalPitch;

        यदि (!SDL_CalculateSurfaceSize(format, width, height, रिक्त, &minimalPitch, true /* minimal pitch */)) {
            // Overflow...
            प्रत्यागम रिक्त;
        }

        CHECK_PARAM(pitch < 0 || (size_t)pitch < minimalPitch) {
            SDL_InvalidParamError("pitch");
            प्रत्यागम रिक्त;
        }
    }

    // Allocate and initialize the surface
    SDL_Surface *surface = (SDL_Surface *)SDL_malloc(परिमाण(*surface));
    यदि (!surface ||
        !SDL_InitializeSurface(surface, width, height, format, SDL_COLORSPACE_UNKNOWN, 0, pixels, pitch, false)) {
        प्रत्यागम रिक्त;
    }
    प्रत्यागम surface;
}

SDL_PropertiesID SDL_GetSurfaceProperties(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        प्रत्यागम 0;
    }

    यदि (!surface->props) {
        surface->props = SDL_CreateProperties();
    }
    प्रत्यागम surface->props;
}

bool SDL_SetSurfaceColorspace(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        प्रत्यागम SDL_InvalidParamError("surface");
    }

    surface->colorspace = colorspace;
    प्रत्यागम true;
}

SDL_Colorspace SDL_GetSurfaceColorspace(SDL_Surface *surface)
{
    यदि (!SDL_SurfaceValid(surface)) {
        प्रत्यागम SDL_COLORSPACE_UNKNOWN;
    }

    प्रत्यागम surface->colorspace;
}

भिन्न SDL_GetDefaultSDRWhitePoint(SDL_Colorspace colorspace)
{
    प्रत्यागम SDL_GetSurfaceSDRWhitePoint(रिक्त, colorspace);
}

भिन्न SDL_GetSurfaceSDRWhitePoint(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    SDL_TransferCharacteristics transfer = SDL_COLORSPACETRANSFER(colorspace);

    यदि (transfer == SDL_TRANSFER_CHARACTERISTICS_LINEAR ||
        transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
        SDL_PropertiesID props;
        भिन्न default_मूल्य = 1.0f;

        यदि (SDL_SurfaceValid(surface)) {
            props = surface->props;
        } अन्यथा {
            props = 0;
        }
        यदि (transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
            /* The older standards use an SDR white point of 100 nits.
             * ITU-R BT.2408-6 recommends using an SDR white point of 203 nits.
             * This is the default Chrome uses, and what a lot of game content
             * assumes, so we'll go with that.
             */
            ध्रुव भिन्न DEFAULT_PQ_SDR_WHITE_POINT = 203.0f;
            default_मूल्य = DEFAULT_PQ_SDR_WHITE_POINT;
        }
        प्रत्यागम SDL_GetFloatProperty(props, SDL_PROP_SURFACE_SDR_WHITE_POINT_FLOAT, default_मूल्य);
    }
    प्रत्यागम 1.0f;
}

भिन्न SDL_GetDefaultHDRHeadroom(SDL_Colorspace colorspace)
{
    प्रत्यागम SDL_GetSurfaceHDRHeadroom(रिक्त, colorspace);
}

भिन्न SDL_GetSurfaceHDRHeadroom(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    SDL_TransferCharacteristics transfer = SDL_COLORSPACETRANSFER(colorspace);

    यदि (transfer == SDL_TRANSFER_CHARACTERISTICS_LINEAR ||
        transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
        SDL_PropertiesID props;
        भिन्न default_मूल्य = 0.0f;

        यदि (SDL_SurfaceValid(surface)) {
            props = surface->props;
        } अन्यथा {
            props = 0;
        }
        प्रत्यागम SDL_GetFloatProperty(props, SDL_PROP_SURFACE_HDR_HEADROOM_FLOAT, default_मूल्य);
    }
    प्रत्यागम 1.0f;
}

SDL_Palette *SDL_CreateSurfacePalette(SDL_Surface *surface)
{
    SDL_Palette *palette;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        प्रत्यागम रिक्त;
    }

    CHECK_PARAM(!SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        SDL_SetError("The surface is not indexed format");
        प्रत्यागम रिक्त;
    }

    palette = SDL_CreatePalette((1 << SDL_BITSPERPIXEL(surface->format)));
    यदि (!palette) {
        प्रत्यागम रिक्त;
    }

    यदि (palette->ncolors == 2) {
        // Create a black and white bitmap palette
        palette->colors[0].r = 0xFF;
        palette->colors[0].g = 0xFF;
        palette->colors[0].b = 0xFF;
        palette->colors[1].r = 0x00;
        palette->colors[1].g = 0x00;
        palette->colors[1].b = 0x00;
    }

    यदि (!SDL_SetSurfacePalette(surface, palette)) {
        SDL_DestroyPalette(palette);
        प्रत्यागम रिक्त;
    }

    // The surface has retained the palette, we can remove the reference here
    SDL_assert(palette->refcount == 2);
    SDL_DestroyPalette(palette);
    प्रत्यागम palette;
}

bool SDL_SetSurfacePalette(SDL_Surface *surface, SDL_Palette *palette)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        प्रत्यागम SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(palette && !SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        प्रत्यागम SDL_SetError("Surface doesn't use a palette");
    }

    CHECK_PARAM(palette && palette->ncolors > (1 << SDL_BITSPERPIXEL(surface->format))) {
        प्रत्यागम SDL_SetError("Palette doesn't match surface format");
    }

    यदि (palette != surface->palette) {
        यदि (surface->palette) {
            SDL_DestroyPalette(surface->palette);
        }

        surface->palette = palette;

        यदि (surface->palette) {
            ++surface->palette->refcount;
        }
    }

    SDL_InvalidateMap(&surface->map);

    प्रत्यागम true;
}

SDL_Palette *SDL_GetSurfacePalette(SDL_Surface *surface)
{
    यदि (!SDL_SurfaceValid(surface)) {
        प्रत्यागम रिक्त;
    }

    प्रत्यागम surface->palette;
}

bool SDL_AddSurfaceAlternateImage(SDL_Surface *surface, SDL_Surface *image)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        प्रत्यागम SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(!SDL_SurfaceValid(image)) {
        प्रत्यागम SDL_InvalidParamError("image");
    }

    SDL_Surface **images = (SDL_Surface **)SDL_realloc(surface->images, (surface->अंक_images + 1) * परिमाण(*images));
    यदि (!images) {
        प्रत्यागम false;
    }
    images[surface->अंक_images] = image;
    surface->images = images;
    ++surface->अंक_images;
    ++image->refcount;
    प्रत्यागम true;
}

bool SDL_SurfaceHasAlternateImages(SDL_Surface *surface)
{
    यदि (!SDL_SurfaceValid(surface)) {
        प्रत्यागम false;
    }

    प्रत्यागम (surface->अंक_images > 0);
}

SDL_Surface **SDL_GetSurfaceImages(SDL_Surface *surface, पूर्णाङ्क *मोजणी)
{
    यदि (मोजणी) {
        *मोजणी = 0;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        प्रत्यागम रिक्त;
    }

    पूर्णाङ्क अंक_images = 1 + surface->अंक_images;
    SDL_Surface **images = (SDL_Surface **)SDL_malloc((अंक_images + 1) * परिमाण(*images));
    यदि (!images) {
        प्रत्यागम रिक्त;
    }
    images[0] = surface;
    यदि (surface->अंक_images > 0) {
        SDL_memcpy(&images[1], surface->images, (surface->अंक_images * परिमाण(images[1])));
    }
    images[अंक_images] = रिक्त;

    यदि (मोजणी) {
        *मोजणी = अंक_images;
    }
    प्रत्यागम images;
}

SDL_Surface *SDL_GetSurfaceImage(SDL_Surface *surface, भिन्न display_scale)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        प्रत्यागम रिक्त;
    }

    यदि (!SDL_SurfaceHasAlternateImages(surface)) {
        ++surface->refcount;
        प्रत्यागम surface;
    }

    // This surface has high DPI images, pick the best one available, or scale one to the correct size
    SDL_Surface **images = SDL_GetSurfaceImages(surface, रिक्त);
    यदि (!images) {
        // Failure, fall back to the existing surface
        ++surface->refcount;
        प्रत्यागम surface;
    }

    // Find closest image. Images that are larger than the
    // desired size are preferred over images that are smaller.
    SDL_Surface *closest = रिक्त;
    पूर्णाङ्क desired_w = (पूर्णाङ्क)SDL_round(surface->w * display_scale);
    पूर्णाङ्क desired_h = (पूर्णाङ्क)SDL_round(surface->h * display_scale);
    पूर्णाङ्क desired_size = desired_w * desired_h;
    पूर्णाङ्क closest_distance = -1;
    पूर्णाङ्क closest_size = -1;
    प्रति (पूर्णाङ्क i = 0; images[i]; ++i) {
        SDL_Surface *candidate = images[i];
        पूर्णाङ्क size = candidate->w * candidate->h;
        पूर्णाङ्क delta_w = (candidate->w - desired_w);
        पूर्णाङ्क delta_h = (candidate->h - desired_h);
        पूर्णाङ्क distance = (delta_w * delta_w) + (delta_h * delta_h);
        यदि (closest_distance < 0 || distance < closest_distance ||
            (size > desired_size && closest_size < desired_size)) {
            closest = candidate;
            closest_distance = distance;
            closest_size = size;
        }
    }
    SDL_free(images);
    SDL_assert(closest != रिक्त);    // We should always have at least one surface

    यदि (closest->w == desired_w && closest->h == desired_h) {
        ++closest->refcount;
        प्रत्यागम closest;
    }

    // We need to scale the image to the correct size. To maintain good image quality, downscaling
    // is done in steps, never reducing the width and height by more than half each time.
    SDL_Surface *scaled = closest;
    कुरु {
        पूर्णाङ्क next_scaled_w = SDL_max(desired_w, (scaled->w + 1) / 2);
        पूर्णाङ्क next_scaled_h = SDL_max(desired_h, (scaled->h + 1) / 2);
        SDL_Surface *next_scaled = SDL_ScaleSurface(scaled, next_scaled_w, next_scaled_h, SDL_SCALEMODE_LINEAR);
        यदि (scaled != closest) {
            SDL_DestroySurface(scaled);
        }
        scaled = next_scaled;
        यदि (!scaled) {
            // Failure, fall back to the closest surface
            ++closest->refcount;
            प्रत्यागम closest;
        }
    } यावत् (scaled->w != desired_w || scaled->h != desired_h);

    प्रत्यागम scaled;
}

शून्य SDL_RemoveSurfaceAlternateImages(SDL_Surface *surface)
{
    यदि (!SDL_SurfaceValid(surface)) {
        प्रत्यागम;
    }

    यदि (surface->अंक_images > 0) {
        प्रति (पूर्णाङ्क i = 0; i < surface->अंक_images; ++i) {
            SDL_DestroySurface(surface->images[i]);
        }
        SDL_free(surface->images);
        surface->images = रिक्त;
        surface->अंक_images = 0;
    }
}

bool SDL_SetSurfaceRLE(SDL_Surface *surface, bool enabled)
{
    पूर्णाङ्क flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        प्रत्यागम SDL_InvalidParamError("surface");
    }

    flags = surface->map.info.flags;
    यदि (enabled) {
        surface->map.info.flags |= SDL_COPY_RLE_DESIRED;
    } अन्यथा {
        surface->map.info.flags &= ~SDL_COPY_RLE_DESIRED;
    }
    यदि (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    प्रत्यागम true;
}

bool SDL_SurfaceHasRLE(SDL_Surface *surface)
{
    यदि (!SDL_SurfaceValid(surface)) {
        प्रत्यागम false;
    }

    यदि (!(surface->map.info.flags & SDL_COPY_RLE_DESIRED)) {
        प्रत्यागम false;
    }

    प्रत्यागम true;
}

bool SDL_Set_Surface_Color_किल्ली(SDL_Surface *surface, bool enabled, Uint32 किल्ली)
{
    पूर्णाङ्क flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        प्रत्यागम SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(surface->palette && किल्ली >= ((Uint32)surface->palette->ncolors)) {
        प्रत्यागम SDL_InvalidParamError("key");
    }

    flags = surface->map.info.flags;
    यदि (enabled) {
        surface->map.info.flags |= SDL_COPY_COLORKEY;
        surface->map.info.colorkey = किल्ली;
    } अन्यथा {
        surface->map.info.flags &= ~SDL_COPY_COLORKEY;
    }
    यदि (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }

    प्रत्यागम true;
}

bool SDL_Surface_Has_Color_किल्ली(SDL_Surface *surface)
{
    यदि (!SDL_SurfaceValid(surface)) {
        प्रत्यागम false;
    }

    यदि (!(surface->map.info.flags & SDL_COPY_COLORKEY)) {
        प्रत्यागम false;
    }

    प्रत्यागम true;
}

bool SDL_Get_Surface_Color_किल्ली(SDL_Surface *surface, Uint32 *किल्ली)
{
    यदि (किल्ली) {
        *किल्ली = 0;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        प्रत्यागम SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(!(surface->map.info.flags & SDL_COPY_COLORKEY)) {
        प्रत्यागम SDL_SetError("Surface doesn't have a colorkey");
    }

    यदि (किल्ली) {
        *किल्ली = surface->map.info.colorkey;
    }
    प्रत्यागम true;
}

/* This is a fairly slow function to switch from colorkey to alpha
   NB: it doesn't handle bpp 1 or 3, because they have no alpha channel */
स्थिर शून्य SDL_ConvertColorkeyToAlpha(SDL_Surface *surface, bool ignore_alpha)
{
    पूर्णाङ्क x, y, bpp;

    यदि (!SDL_SurfaceValid(surface)) {
        प्रत्यागम;
    }

    यदि (!(surface->map.info.flags & SDL_COPY_COLORKEY) ||
        !SDL_ISPIXELFORMAT_ALPHA(surface->format)) {
        प्रत्यागम;
    }

    bpp = SDL_BYTESPERPIXEL(surface->format);

    SDL_LockSurface(surface);

    यदि (bpp == 2) {
        Uint16 *row, *spot;
        Uint16 ckey = (Uint16)surface->map.info.colorkey;
        Uint16 mask = (Uint16)(~surface->fmt->Amask);

        // Ignore, or not, alpha in colorkey comparison
        यदि (ignore_alpha) {
            ckey &= mask;
            row = (Uint16 *)surface->pixels;
            प्रति (y = surface->h; y--;) {
                spot = row;
                प्रति (x = surface->w; x--;) {
                    यदि ((*spot & mask) == ckey) {
                        *spot &= mask;
                    }
                    ++spot;
                }
                row += surface->pitch / 2;
            }
        } अन्यथा {
            row = (Uint16 *)surface->pixels;
            प्रति (y = surface->h; y--;) {
                spot = row;
                प्रति (x = surface->w; x--;) {
                    यदि (*spot == ckey) {
                        *spot &= mask;
                    }
                    ++spot;
                }
                row += surface->pitch / 2;
            }
        }
    } अन्यथा यदि (bpp == 4) {
        Uint32 *row, *spot;
        Uint32 ckey = surface->map.info.colorkey;
        Uint32 mask = ~surface->fmt->Amask;

        // Ignore, or not, alpha in colorkey comparison
        यदि (ignore_alpha) {
            ckey &= mask;
            row = (Uint32 *)surface->pixels;
            प्रति (y = surface->h; y--;) {
                spot = row;
                प्रति (x = surface->w; x--;) {
                    यदि ((*spot & mask) == ckey) {
                        *spot &= mask;
                    }
                    ++spot;
                }
                row += surface->pitch / 4;
            }
        } अन्यथा {
            row = (Uint32 *)surface->pixels;
            प्रति (y = surface->h; y--;) {
                spot = row;
                प्रति (x = surface->w; x--;) {
                    यदि (*spot == ckey) {
                        *spot &= mask;
                    }
                    ++spot;
                }
                row += surface->pitch / 4;
            }
        }
    }

    SDL_UnlockSurface(surface);

    SDL_Set_Surface_Color_किल्ली(surface, false, 0);
    SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
}

bool SDL_SetSurfaceColorMod(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b)
{
    पूर्णाङ्क flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        प्रत्यागम SDL_InvalidParamError("surface");
    }

    surface->map.info.r = r;
    surface->map.info.g = g;
    surface->map.info.b = b;

    flags = surface->map.info.flags;
    यदि (r != 0xFF || g != 0xFF || b != 0xFF) {
        surface->map.info.flags |= SDL_COPY_MODULATE_COLOR;
    } अन्यथा {
        surface->map.info.flags &= ~SDL_COPY_MODULATE_COLOR;
    }
    यदि (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    प्रत्यागम true;
}

bool SDL_GetSurfaceColorMod(SDL_Surface *surface, Uint8 *r, Uint8 *g, Uint8 *b)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        यदि (r) {
            *r = 255;
        }
        यदि (g) {
            *g = 255;
        }
        यदि (b) {
            *b = 255;
        }
        प्रत्यागम SDL_InvalidParamError("surface");
    }

    यदि (r) {
        *r = surface->map.info.r;
    }
    यदि (g) {
        *g = surface->map.info.g;
    }
    यदि (b) {
        *b = surface->map.info.b;
    }
    प्रत्यागम true;
}

bool SDL_SetSurfaceAlphaMod(SDL_Surface *surface, Uint8 alpha)
{
    पूर्णाङ्क flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        प्रत्यागम SDL_InvalidParamError("surface");
    }

    surface->map.info.a = alpha;

    flags = surface->map.info.flags;
    यदि (alpha != 0xFF) {
        surface->map.info.flags |= SDL_COPY_MODULATE_ALPHA;
    } अन्यथा {
        surface->map.info.flags &= ~SDL_COPY_MODULATE_ALPHA;
    }
    यदि (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    प्रत्यागम true;
}

bool SDL_GetSurfaceAlphaMod(SDL_Surface *surface, Uint8 *alpha)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        यदि (alpha) {
            *alpha = 255;
        }
        प्रत्यागम SDL_InvalidParamError("surface");
    }

    यदि (alpha) {
        *alpha = surface->map.info.a;
    }
    प्रत्यागम true;
}

bool SDL_SetSurfaceBlendMode(SDL_Surface *surface, SDL_BlendMode blendMode)
{
    पूर्णाङ्क flags;
    bool result = true;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        प्रत्यागम SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(blendMode == SDL_BLENDMODE_INVALID) {
        प्रत्यागम SDL_InvalidParamError("blendMode");
    }

    flags = surface->map.info.flags;
    surface->map.info.flags &= ~SDL_COPY_BLEND_MASK;
    विकल्प (blendMode) {
    पक्ष SDL_BLENDMODE_NONE:
        भङ्ग;
    पक्ष SDL_BLENDMODE_BLEND:
        surface->map.info.flags |= SDL_COPY_BLEND;
        भङ्ग;
    पक्ष SDL_BLENDMODE_BLEND_PREMULTIPLIED:
        surface->map.info.flags |= SDL_COPY_BLEND_PREMULTIPLIED;
        भङ्ग;
    पक्ष SDL_BLENDMODE_ADD:
        surface->map.info.flags |= SDL_COPY_ADD;
        भङ्ग;
    पक्ष SDL_BLENDMODE_ADD_PREMULTIPLIED:
        surface->map.info.flags |= SDL_COPY_ADD_PREMULTIPLIED;
        भङ्ग;
    पक्ष SDL_BLENDMODE_MOD:
        surface->map.info.flags |= SDL_COPY_MOD;
        भङ्ग;
    पक्ष SDL_BLENDMODE_MUL:
        surface->map.info.flags |= SDL_COPY_MUL;
        भङ्ग;
    स्वभाव:
        result = SDL_Unsupported();
        भङ्ग;
    }

    यदि (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }

    प्रत्यागम result;
}

bool SDL_GetSurfaceBlendMode(SDL_Surface *surface, SDL_BlendMode *blendMode)
{
    यदि (blendMode) {
        *blendMode = SDL_BLENDMODE_INVALID;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        प्रत्यागम SDL_InvalidParamError("surface");
    }

    यदि (!blendMode) {
        प्रत्यागम true;
    }

    विकल्प (surface->map.info.flags & SDL_COPY_BLEND_MASK) {
    पक्ष SDL_COPY_BLEND:
        *blendMode = SDL_BLENDMODE_BLEND;
        भङ्ग;
    पक्ष SDL_COPY_BLEND_PREMULTIPLIED:
        *blendMode = SDL_BLENDMODE_BLEND_PREMULTIPLIED;
        भङ्ग;
    पक्ष SDL_COPY_ADD:
        *blendMode = SDL_BLENDMODE_ADD;
        भङ्ग;
    पक्ष SDL_COPY_ADD_PREMULTIPLIED:
        *blendMode = SDL_BLENDMODE_ADD_PREMULTIPLIED;
        भङ्ग;
    पक्ष SDL_COPY_MOD:
        *blendMode = SDL_BLENDMODE_MOD;
        भङ्ग;
    पक्ष SDL_COPY_MUL:
        *blendMode = SDL_BLENDMODE_MUL;
        भङ्ग;
    स्वभाव:
        *blendMode = SDL_BLENDMODE_NONE;
        भङ्ग;
    }
    प्रत्यागम true;
}

bool SDL_SetSurfaceClipRect(SDL_Surface *surface, ध्रुव SDL_Rect *rect)
{
    SDL_Rect full_rect;

    // Don't do anything if there's no surface to act on
    यदि (!SDL_SurfaceValid(surface)) {
        प्रत्यागम false;
    }

    // Set up the full surface rectangle
    full_rect.x = 0;
    full_rect.y = 0;
    full_rect.w = surface->w;
    full_rect.h = surface->h;

    // Set the clipping rectangle
    यदि (!rect) {
        surface->clip_rect = full_rect;
        प्रत्यागम true;
    }
    प्रत्यागम SDL_GetRectIntersection(rect, &full_rect, &surface->clip_rect);
}

bool SDL_GetSurfaceClipRect(SDL_Surface *surface, SDL_Rect *rect)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        यदि (rect) {
            SDL_zerop(rect);
        }
        प्रत्यागम SDL_InvalidParamError("surface");
    }
    CHECK_PARAM(!rect) {
        प्रत्यागम SDL_InvalidParamError("rect");
    }
    *rect = surface->clip_rect;
    प्रत्यागम true;
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
bool SDL_BlitSurfaceUnchecked(SDL_Surface *src, ध्रुव SDL_Rect *srcrect,
                             SDL_Surface *dst, ध्रुव SDL_Rect *dstrect)
{
    // Check to make sure the blit mapping is valid
    यदि (!SDL_ValidateMap(src, dst)) {
        प्रत्यागम false;
    }
    प्रत्यागम src->map.blit(src, srcrect, dst, dstrect);
}

bool SDL_BlitSurface(SDL_Surface *src, ध्रुव SDL_Rect *srcrect, SDL_Surface *dst, ध्रुव SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src) || (!src->pixels && !SDL_MUSTLOCK(src))) {
        प्रत्यागम SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst) || (!dst->pixels && !SDL_MUSTLOCK(dst))) {
        प्रत्यागम SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        प्रत्यागम SDL_SetError("Surfaces must not be locked during blit");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    यदि (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
    } अन्यथा {
        r_dst.x = 0;
        r_dst.y = 0;
    }

    // clip the source rectangle to the source surface
    यदि (srcrect) {
        SDL_Rect tmp;
        यदि (SDL_GetRectIntersection(srcrect, &r_src, &tmp) == false) {
            प्रत्यागम true;
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
        यदि (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &tmp) == false) {
            प्रत्यागम true;
        }

        // Shift srcrect, if dstrect has changed
        r_src.x += tmp.x - r_dst.x;
        r_src.y += tmp.y - r_dst.y;
        r_src.w = tmp.w;
        r_src.h = tmp.h;

        // Update dstrect
        r_dst = tmp;
    }

    यदि (r_dst.w <= 0 || r_dst.h <= 0) {
        // No-op.
        प्रत्यागम true;
    }

    // Switch back to a fast blit if we were previously stretching
    यदि (src->map.info.flags & SDL_COPY_NEAREST) {
        src->map.info.flags &= ~SDL_COPY_NEAREST;
        SDL_InvalidateMap(&src->map);
    }

    प्रत्यागम SDL_BlitSurfaceUnchecked(src, &r_src, dst, &r_dst);
}

स्थिर bool SDL_BlitSurfaceClippedScaled(SDL_Surface *src, ध्रुव SDL_Rect *srcrect, SDL_Surface *dst, ध्रुव SDL_Rect *dstrect, SDL_ScaleMode scaleMode)
{
    // We need to scale first, then blit into dst because we're clipping in the destination surface pixel coordinates
    bool result;
    पूर्णाङ्क saved_w = src->w;
    पूर्णाङ्क saved_h = src->h;
    शून्य *saved_pixels = src->pixels;
    src->w = srcrect->w;
    src->h = srcrect->h;
    src->pixels = (Uint8 *)src->pixels + srcrect->y * src->pitch + srcrect->x * SDL_BYTESPERPIXEL(src->format);
    SDL_Surface *scaled = SDL_ScaleSurface(src, dstrect->w, dstrect->h, scaleMode);
    यदि (scaled) {
        result = SDL_BlitSurface(scaled, रिक्त, dst, dstrect);
        SDL_DestroySurface(scaled);
    } अन्यथा {
        result = false;
    }
    src->w = saved_w;
    src->h = saved_h;
    src->pixels = saved_pixels;
    प्रत्यागम result;
}

bool SDL_BlitSurfaceScaled(SDL_Surface *src, ध्रुव SDL_Rect *srcrect, SDL_Surface *dst, ध्रुव SDL_Rect *dstrect, SDL_ScaleMode scaleMode)
{
    SDL_Rect r_src, r_dst;
    bool result;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src) || (!src->pixels && !SDL_MUSTLOCK(src))) {
        प्रत्यागम SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst) || (!dst->pixels && !SDL_MUSTLOCK(dst))) {
        प्रत्यागम SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        प्रत्यागम SDL_SetError("Surfaces must not be locked during blit");
    }

    विकल्प (scaleMode) {
    पक्ष SDL_SCALEMODE_NEAREST:
        भङ्ग;
    पक्ष SDL_SCALEMODE_LINEAR:
        भङ्ग;
    पक्ष SDL_SCALEMODE_PIXELART:
        scaleMode = SDL_SCALEMODE_NEAREST;
        भङ्ग;
    स्वभाव:
        प्रत्यागम SDL_InvalidParamError("scaleMode");
    }

    पूर्णाङ्क src_w = srcrect ? srcrect->w : src->w;
    पूर्णाङ्क src_h = srcrect ? srcrect->h : src->h;
    पूर्णाङ्क dst_w = dstrect ? dstrect->w : dst->w;
    पूर्णाङ्क dst_h = dstrect ? dstrect->h : dst->h;
    यदि (src_w == dst_w && src_h == dst_h) {
        // No scaling, defer to regular blit
        प्रत्यागम SDL_BlitSurface(src, srcrect, dst, dstrect);
    }

    यदि (src->w == 0 || src->h == 0) {
        // Nothing to do
        प्रत्यागम true;
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    यदि (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
        r_dst.w = dstrect->w;
        r_dst.h = dstrect->h;
    } अन्यथा {
        r_dst.x = 0;
        r_dst.y = 0;
        r_dst.w = dst->w;
        r_dst.h = dst->h;
    }

    // clip the source rectangle to the source surface
    यदि (srcrect) {
        SDL_Rect desired, tmp;
        desired.x = srcrect->x;
        desired.y = srcrect->y;
        desired.w = SDL_max(srcrect->w, 1);
        desired.h = SDL_max(srcrect->h, 1);
        यदि (SDL_GetRectIntersection(&desired, &r_src, &tmp) == false) {
            प्रत्यागम true;
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
    यदि (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &tmp) == false) {
        प्रत्यागम true;
    }

    यदि (tmp.x != r_dst.x || tmp.y != r_dst.y || tmp.w != r_dst.w || tmp.h != r_dst.h) {
        // Need to do a clipped and scaled blit
        प्रत्यागम SDL_BlitSurfaceClippedScaled(src, &r_src, dst, &r_dst, scaleMode);
    }

    यदि (SDL_MUSTLOCK(src)) {
        यदि (!SDL_LockSurface(src)) {
            प्रत्यागम false;
        }
    }
    यदि (SDL_MUSTLOCK(dst)) {
        यदि (!SDL_LockSurface(dst)) {
            यदि (SDL_MUSTLOCK(src)) {
                SDL_UnlockSurface(src);
            }
            प्रत्यागम false;
        }
    }

    result = SDL_BlitSurfaceUncheckedScaled(src, &r_src, dst, &r_dst, scaleMode);

    यदि (SDL_MUSTLOCK(src)) {
        SDL_UnlockSurface(src);
    }
    यदि (SDL_MUSTLOCK(dst)) {
        SDL_UnlockSurface(dst);
    }
    प्रत्यागम result;
}

/**
 *  This is a semi-private blit function and it performs low-level surface
 *  scaled blitting only.
 */
bool SDL_BlitSurfaceUncheckedScaled(SDL_Surface *src, ध्रुव SDL_Rect *srcrect, SDL_Surface *dst, ध्रुव SDL_Rect *dstrect, SDL_ScaleMode scaleMode)
{
    स्थिर ध्रुव Uint32 complex_copy_flags = (SDL_COPY_MODULATE_MASK | SDL_COPY_BLEND_MASK | SDL_COPY_COLORKEY);

    यदि (srcrect->w > SDL_MAX_UINT16 || srcrect->h > SDL_MAX_UINT16 ||
        dstrect->w > SDL_MAX_UINT16 || dstrect->h > SDL_MAX_UINT16) {
        प्रत्यागम SDL_SetError("Size too large for scaling");
    }

    यदि (!(src->map.info.flags & SDL_COPY_NEAREST)) {
        src->map.info.flags |= SDL_COPY_NEAREST;
        SDL_InvalidateMap(&src->map);
    }

    यदि (scaleMode == SDL_SCALEMODE_NEAREST || scaleMode == SDL_SCALEMODE_PIXELART) {
        यदि (!(src->map.info.flags & complex_copy_flags) &&
            src->format == dst->format &&
            (!SDL_ISPIXELFORMAT_INDEXED(src->format) ||
             (SDL_BITSPERPIXEL(src->format) == 8 && SDL_IsSamePalette(src->palette, dst->palette))) &&
            SDL_BYTESPERPIXEL(src->format) <= 4) {
            प्रत्यागम SDL_StretchSurface(src, srcrect, dst, dstrect, SDL_SCALEMODE_NEAREST);
        } अन्यथा यदि (SDL_BITSPERPIXEL(src->format) < 8) {
            // Scaling bitmap not yet supported, convert to RGBA for blit
            bool result = false;
            SDL_Surface *tmp = SDL_ConvertSurface(src, SDL_PIXELFORMAT_ARGB8888);
            यदि (tmp) {
                result = SDL_BlitSurfaceUncheckedScaled(tmp, srcrect, dst, dstrect, SDL_SCALEMODE_NEAREST);
                SDL_DestroySurface(tmp);
            }
            प्रत्यागम result;
        } अन्यथा {
            प्रत्यागम SDL_BlitSurfaceUnchecked(src, srcrect, dst, dstrect);
        }
    } अन्यथा {
        यदि (!(src->map.info.flags & complex_copy_flags) &&
            src->format == dst->format &&
            !SDL_ISPIXELFORMAT_INDEXED(src->format) &&
            SDL_BYTESPERPIXEL(src->format) == 4 &&
            src->format != SDL_PIXELFORMAT_ARGB2101010) {
            // fast path
            प्रत्यागम SDL_StretchSurface(src, srcrect, dst, dstrect, SDL_SCALEMODE_LINEAR);
        } अन्यथा यदि (SDL_BITSPERPIXEL(src->format) < 8) {
            // Scaling bitmap not yet supported, convert to RGBA for blit
            bool result = false;
            SDL_Surface *tmp = SDL_ConvertSurface(src, SDL_PIXELFORMAT_ARGB8888);
            यदि (tmp) {
                result = SDL_BlitSurfaceUncheckedScaled(tmp, srcrect, dst, dstrect, scaleMode);
                SDL_DestroySurface(tmp);
            }
            प्रत्यागम result;
        } अन्यथा {
            // Use intermediate surface(s)
            SDL_Surface *tmp1 = रिक्त;
            bool result;
            SDL_Rect srcrect2;
            पूर्णाङ्क is_complex_copy_flags = (src->map.info.flags & complex_copy_flags);

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
            यदि (SDL_BYTESPERPIXEL(src->format) != 4 || src->format == SDL_PIXELFORMAT_ARGB2101010) {
                SDL_PixelFormat fmt;
                यदि (SDL_BYTESPERPIXEL(dst->format) == 4 && dst->format != SDL_PIXELFORMAT_ARGB2101010 &&
                    (SDL_ISPIXELFORMAT_ALPHA(dst->format) || !is_complex_copy_flags)) {
                    fmt = dst->format;
                } अन्यथा {
                    fmt = SDL_PIXELFORMAT_ARGB8888;
                }
                tmp1 = SDL_ConvertSurfaceRect(src, srcrect, fmt);
                यदि (!tmp1) {
                    प्रत्यागम false;
                }
                src = tmp1;
                srcrect2.x = 0;
                srcrect2.y = 0;
            }

            // Intermediate scaling
            यदि (is_complex_copy_flags || src->format != dst->format) {
                SDL_Rect tmprect;
                SDL_Surface *tmp2 = SDL_CreateSurfaceUninitialized(dstrect->w, dstrect->h, src->format);
                SDL_StretchSurface(src, &srcrect2, tmp2, रिक्त, SDL_SCALEMODE_LINEAR);

                SDL_SetSurfaceColorMod(tmp2, r, g, b);
                SDL_SetSurfaceAlphaMod(tmp2, alpha);
                SDL_SetSurfaceBlendMode(tmp2, blendMode);

                tmprect.x = 0;
                tmprect.y = 0;
                tmprect.w = dstrect->w;
                tmprect.h = dstrect->h;
                result = SDL_BlitSurfaceUnchecked(tmp2, &tmprect, dst, dstrect);
                SDL_DestroySurface(tmp2);
            } अन्यथा {
                result = SDL_StretchSurface(src, &srcrect2, dst, dstrect, SDL_SCALEMODE_LINEAR);
            }

            SDL_DestroySurface(tmp1);
            प्रत्यागम result;
        }
    }
}

bool SDL_BlitSurfaceTiled(SDL_Surface *src, ध्रुव SDL_Rect *srcrect, SDL_Surface *dst, ध्रुव SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        प्रत्यागम SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        प्रत्यागम SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        प्रत्यागम SDL_SetError("Surfaces must not be locked during blit");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    यदि (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
        r_dst.w = dstrect->w;
        r_dst.h = dstrect->h;
    } अन्यथा {
        r_dst.x = 0;
        r_dst.y = 0;
        r_dst.w = dst->w;
        r_dst.h = dst->h;
    }

    // clip the source rectangle to the source surface
    यदि (srcrect) {
        यदि (SDL_GetRectIntersection(srcrect, &r_src, &r_src) == false) {
            प्रत्यागम true;
        }

        // For tiling we don't adjust the destination rectangle
    }

    // clip the destination rectangle against the clip rectangle
    {
        यदि (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &r_dst) == false) {
            प्रत्यागम true;
        }

        // For tiling we don't adjust the source rectangle
    }

    // Switch back to a fast blit if we were previously stretching
    यदि (src->map.info.flags & SDL_COPY_NEAREST) {
        src->map.info.flags &= ~SDL_COPY_NEAREST;
        SDL_InvalidateMap(&src->map);
    }

    पूर्णाङ्क rows = r_dst.h / r_src.h;
    पूर्णाङ्क cols = r_dst.w / r_src.w;
    पूर्णाङ्क remaining_w = r_dst.w % r_src.w;
    पूर्णाङ्क remaining_h = r_dst.h % r_src.h;
    SDL_Rect curr_src, curr_dst;

    SDL_copyp(&curr_src, &r_src);
    curr_dst.y = r_dst.y;
    curr_dst.w = r_src.w;
    curr_dst.h = r_src.h;
    प्रति (पूर्णाङ्क y = 0; y < rows; ++y) {
        curr_dst.x = r_dst.x;
        प्रति (पूर्णाङ्क x = 0; x < cols; ++x) {
            यदि (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                प्रत्यागम false;
            }
            curr_dst.x += curr_dst.w;
        }
        यदि (remaining_w) {
            curr_src.w = remaining_w;
            curr_dst.w = remaining_w;
            यदि (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                प्रत्यागम false;
            }
            curr_src.w = r_src.w;
            curr_dst.w = r_src.w;
        }
        curr_dst.y += curr_dst.h;
    }
    यदि (remaining_h) {
        curr_src.h = remaining_h;
        curr_dst.h = remaining_h;
        curr_dst.x = r_dst.x;
        प्रति (पूर्णाङ्क x = 0; x < cols; ++x) {
            यदि (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                प्रत्यागम false;
            }
            curr_dst.x += curr_dst.w;
        }
        यदि (remaining_w) {
            curr_src.w = remaining_w;
            curr_dst.w = remaining_w;
            यदि (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                प्रत्यागम false;
            }
        }
    }
    प्रत्यागम true;
}

bool SDL_BlitSurfaceTiledWithScale(SDL_Surface *src, ध्रुव SDL_Rect *srcrect, भिन्न scale, SDL_ScaleMode scaleMode, SDL_Surface *dst, ध्रुव SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        प्रत्यागम SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        प्रत्यागम SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        प्रत्यागम SDL_SetError("Surfaces must not be locked during blit");
    }
    CHECK_PARAM(scale < 0.0f) {
        प्रत्यागम SDL_InvalidParamError("scale");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    यदि (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
        r_dst.w = dstrect->w;
        r_dst.h = dstrect->h;
    } अन्यथा {
        r_dst.x = 0;
        r_dst.y = 0;
        r_dst.w = dst->w;
        r_dst.h = dst->h;
    }

    // clip the source rectangle to the source surface
    यदि (srcrect) {
        यदि (SDL_GetRectIntersection(srcrect, &r_src, &r_src) == false) {
            प्रत्यागम true;
        }

        // For tiling we don't adjust the destination rectangle
    }

    // clip the destination rectangle against the clip rectangle
    {
        यदि (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &r_dst) == false) {
            प्रत्यागम true;
        }

        // For tiling we don't adjust the source rectangle
    }

    // Switch back to a fast blit if we were previously stretching
    यदि (src->map.info.flags & SDL_COPY_NEAREST) {
        src->map.info.flags &= ~SDL_COPY_NEAREST;
        SDL_InvalidateMap(&src->map);
    }

    पूर्णाङ्क tile_width = (पूर्णाङ्क)SDL_roundf(r_src.w * scale);
    पूर्णाङ्क tile_height = (पूर्णाङ्क)SDL_roundf(r_src.h * scale);
    यदि (tile_width <= 0 || tile_height <= 0) {
        // Nothing to do
        प्रत्यागम true;
    }
    पूर्णाङ्क rows = r_dst.h / tile_height;
    पूर्णाङ्क cols = r_dst.w / tile_width;
    पूर्णाङ्क remaining_dst_w = (r_dst.w - cols * tile_width);
    पूर्णाङ्क remaining_dst_h = (r_dst.h - rows * tile_height);
    पूर्णाङ्क remaining_src_w = (पूर्णाङ्क)(remaining_dst_w / scale);
    पूर्णाङ्क remaining_src_h = (पूर्णाङ्क)(remaining_dst_h / scale);
    SDL_Rect curr_src, curr_dst;

    SDL_copyp(&curr_src, &r_src);
    curr_dst.y = r_dst.y;
    curr_dst.w = tile_width;
    curr_dst.h = tile_height;
    प्रति (पूर्णाङ्क y = 0; y < rows; ++y) {
        curr_dst.x = r_dst.x;
        प्रति (पूर्णाङ्क x = 0; x < cols; ++x) {
            यदि (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
                प्रत्यागम false;
            }
            curr_dst.x += curr_dst.w;
        }
        यदि (remaining_dst_w > 0) {
            curr_src.w = remaining_src_w;
            curr_dst.w = remaining_dst_w;
            यदि (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
                प्रत्यागम false;
            }
            curr_src.w = r_src.w;
            curr_dst.w = tile_width;
        }
        curr_dst.y += curr_dst.h;
    }
    यदि (remaining_dst_h > 0) {
        curr_src.h = remaining_src_h;
        curr_dst.h = remaining_dst_h;
        curr_dst.x = r_dst.x;
        प्रति (पूर्णाङ्क x = 0; x < cols; ++x) {
            यदि (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
                प्रत्यागम false;
            }
            curr_dst.x += curr_dst.w;
        }
        यदि (remaining_dst_w > 0) {
            curr_src.w = remaining_src_w;
            curr_dst.w = remaining_dst_w;
            यदि (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
                प्रत्यागम false;
            }
        }
    }
    प्रत्यागम true;
}

bool SDL_BlitSurface9Grid(SDL_Surface *src, ध्रुव SDL_Rect *srcrect, पूर्णाङ्क डावा_width, पूर्णाङ्क उजवा_width, पूर्णाङ्क शीर्ष_height, पूर्णाङ्क bottom_height, भिन्न scale, SDL_ScaleMode scaleMode, SDL_Surface *dst, ध्रुव SDL_Rect *dstrect)
{
    SDL_Rect full_src, full_dst;
    SDL_Rect curr_src, curr_dst;
    पूर्णाङ्क dst_डावा_width;
    पूर्णाङ्क dst_उजवा_width;
    पूर्णाङ्क dst_शीर्ष_height;
    पूर्णाङ्क dst_bottom_height;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        प्रत्यागम SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        प्रत्यागम SDL_InvalidParamError("dst");
    }

    यदि (!srcrect) {
        full_src.x = 0;
        full_src.y = 0;
        full_src.w = src->w;
        full_src.h = src->h;
        srcrect = &full_src;
    }

    यदि (!dstrect) {
        full_dst.x = 0;
        full_dst.y = 0;
        full_dst.w = dst->w;
        full_dst.h = dst->h;
        dstrect = &full_dst;
    }

    यदि (scale <= 0.0f || scale == 1.0f) {
        dst_डावा_width = डावा_width;
        dst_उजवा_width = उजवा_width;
        dst_शीर्ष_height = शीर्ष_height;
        dst_bottom_height = bottom_height;
    } अन्यथा {
        dst_डावा_width = (पूर्णाङ्क)SDL_roundf(डावा_width * scale);
        dst_उजवा_width = (पूर्णाङ्क)SDL_roundf(उजवा_width * scale);
        dst_शीर्ष_height = (पूर्णाङ्क)SDL_roundf(शीर्ष_height * scale);
        dst_bottom_height = (पूर्णाङ्क)SDL_roundf(bottom_height * scale);
    }

    // Upper-left corner
    curr_src.x = srcrect->x;
    curr_src.y = srcrect->y;
    curr_src.w = डावा_width;
    curr_src.h = शीर्ष_height;
    curr_dst.x = dstrect->x;
    curr_dst.y = dstrect->y;
    curr_dst.w = dst_डावा_width;
    curr_dst.h = dst_शीर्ष_height;
    यदि (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        प्रत्यागम false;
    }

    // Upper-right corner
    curr_src.x = srcrect->x + srcrect->w - उजवा_width;
    curr_src.w = उजवा_width;
    curr_dst.x = dstrect->x + dstrect->w - dst_उजवा_width;
    curr_dst.w = dst_उजवा_width;
    यदि (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        प्रत्यागम false;
    }

    // Lower-right corner
    curr_src.y = srcrect->y + srcrect->h - bottom_height;
    curr_dst.y = dstrect->y + dstrect->h - dst_bottom_height;
    curr_dst.h = dst_bottom_height;
    यदि (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        प्रत्यागम false;
    }

    // Lower-left corner
    curr_src.x = srcrect->x;
    curr_src.w = डावा_width;
    curr_dst.x = dstrect->x;
    curr_dst.w = dst_डावा_width;
    यदि (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        प्रत्यागम false;
    }

    //डावा
    curr_src.y = srcrect->y + शीर्ष_height;
    curr_src.h = srcrect->h - शीर्ष_height - bottom_height;
    curr_dst.y = dstrect->y + dst_शीर्ष_height;
    curr_dst.h = dstrect->h - dst_शीर्ष_height - dst_bottom_height;
    यदि (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        प्रत्यागम false;
    }

    //उजवा
    curr_src.x = srcrect->x + srcrect->w - उजवा_width;
    curr_src.w = उजवा_width;
    curr_dst.x = dstrect->x + dstrect->w - dst_उजवा_width;
    curr_dst.w = dst_उजवा_width;
    यदि (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        प्रत्यागम false;
    }

    //शीर्ष
    curr_src.x = srcrect->x + डावा_width;
    curr_src.y = srcrect->y;
    curr_src.w = srcrect->w - डावा_width - उजवा_width;
    curr_src.h = शीर्ष_height;
    curr_dst.x = dstrect->x + dst_डावा_width;
    curr_dst.y = dstrect->y;
    curr_dst.w = dstrect->w - dst_डावा_width - dst_उजवा_width;
    curr_dst.h = dst_शीर्ष_height;
    यदि (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        प्रत्यागम false;
    }

    // Bottom
    curr_src.y = srcrect->y + srcrect->h - bottom_height;
    curr_dst.y = dstrect->y + dstrect->h - dst_bottom_height;
    curr_dst.h = dst_bottom_height;
    यदि (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        प्रत्यागम false;
    }

    // Center
    curr_src.x = srcrect->x + डावा_width;
    curr_src.y = srcrect->y + शीर्ष_height;
    curr_src.w = srcrect->w - डावा_width - उजवा_width;
    curr_src.h = srcrect->h - शीर्ष_height - bottom_height;
    curr_dst.x = dstrect->x + dst_डावा_width;
    curr_dst.y = dstrect->y + dst_शीर्ष_height;
    curr_dst.w = dstrect->w - dst_डावा_width - dst_उजवा_width;
    curr_dst.h = dstrect->h - dst_शीर्ष_height - dst_bottom_height;
    यदि (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        प्रत्यागम false;
    }

    प्रत्यागम true;
}

/*
 * Lock a surface to directly access the pixels
 */
bool SDL_LockSurface(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        प्रत्यागम SDL_InvalidParamError("surface");
    }

    यदि (!surface->locked) {
#ifdef SDL_HAVE_RLE
        // Perform the lock
        यदि (surface->internal_flags & SDL_INTERNAL_SURFACE_RLEACCEL) {
            SDL_UnRLESurface(surface);
        }
#endif
    }

    // Increment the surface lock count, for recursive locks
    ++surface->locked;
    surface->flags |= SDL_SURFACE_LOCKED;
    SDL_UpdateSurfaceLockFlag(surface);

    // Ready to go..
    प्रत्यागम true;
}

/*
 * Unlock a previously locked surface
 */
शून्य SDL_UnlockSurface(SDL_Surface *surface)
{
    यदि (!SDL_SurfaceValid(surface)) {
        प्रत्यागम;
    }

    // Only perform an unlock if we are locked
    यदि (!surface->locked || (--surface->locked > 0)) {
        प्रत्यागम;
    }

    surface->flags &= ~SDL_SURFACE_LOCKED;
    SDL_UpdateSurfaceLockFlag(surface);
}

स्थिर bool SDL_FlipSurfaceHorizontal(SDL_Surface *surface)
{
    bool isstack;
    Uint8 *row, *a, *b, *tmp;
    पूर्णाङ्क i, j, bpp;

    यदि (SDL_BITSPERPIXEL(surface->format) < 8) {
        // We could implement this if needed, but we'd have to flip sets of bits within a byte
        प्रत्यागम SDL_Unsupported();
    }

    यदि (surface->h <= 0) {
        प्रत्यागम true;
    }

    यदि (surface->w <= 1) {
        प्रत्यागम true;
    }

    bpp = SDL_BYTESPERPIXEL(surface->format);
    row = (Uint8 *)surface->pixels;
    tmp = SDL_small_alloc(Uint8, surface->pitch, &isstack);
    यदि (!tmp) {
        प्रत्यागम false;
    }
    प्रति (i = surface->h; i--; ) {
        a = row;
        b = a + (surface->w - 1) * bpp;
        प्रति (j = surface->w / 2; j--; ) {
            SDL_memcpy(tmp, a, bpp);
            SDL_memcpy(a, b, bpp);
            SDL_memcpy(b, tmp, bpp);
            a += bpp;
            b -= bpp;
        }
        row += surface->pitch;
    }
    SDL_small_free(tmp, isstack);
    प्रत्यागम true;
}

स्थिर bool SDL_FlipSurfaceVertical(SDL_Surface *surface)
{
    bool isstack;
    Uint8 *a, *b, *tmp;
    पूर्णाङ्क i;

    यदि (surface->h <= 1) {
        प्रत्यागम true;
    }

    a = (Uint8 *)surface->pixels;
    b = a + (surface->h - 1) * surface->pitch;
    tmp = SDL_small_alloc(Uint8, surface->pitch, &isstack);
    यदि (!tmp) {
        प्रत्यागम false;
    }
    प्रति (i = surface->h / 2; i--; ) {
        SDL_memcpy(tmp, a, surface->pitch);
        SDL_memcpy(a, b, surface->pitch);
        SDL_memcpy(b, tmp, surface->pitch);
        a += surface->pitch;
        b -= surface->pitch;
    }
    SDL_small_free(tmp, isstack);
    प्रत्यागम true;
}

bool SDL_FlipSurface(SDL_Surface *surface, SDL_FlipMode flip)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        प्रत्यागम SDL_InvalidParamError("surface");
    }
    यदि (!surface->pixels) {
        प्रत्यागम true;
    }

    bool result = true;
    विकल्प (flip) {
    पक्ष SDL_FLIP_HORIZONTAL:
        result = SDL_FlipSurfaceHorizontal(surface);
        भङ्ग;
    पक्ष SDL_FLIP_VERTICAL:
        result = SDL_FlipSurfaceVertical(surface);
        भङ्ग;
    पक्ष SDL_FLIP_HORIZONTAL_AND_VERTICAL:
        result &= SDL_FlipSurfaceHorizontal(surface);
        result &= SDL_FlipSurfaceVertical(surface);
        भङ्ग;
    स्वभाव:
        result = SDL_InvalidParamError("flip");
        भङ्ग;
    }
    प्रत्यागम result;
}

स्थिर SDL_Surface *SDL_ConvertSurfaceRectAndColorspace(SDL_Surface *surface, ध्रुव SDL_Rect *rect, SDL_PixelFormat format, SDL_Palette *palette, SDL_Colorspace colorspace, SDL_PropertiesID props)
{
    SDL_Palette *temp_palette = रिक्त;
    SDL_Surface *convert = रिक्त;
    SDL_Colorspace src_colorspace;
    SDL_PropertiesID src_properties;
    Uint32 copy_flags;
    SDL_Color copy_color;
    SDL_Rect bounds;
    bool result;
    bool palette_ck_transform = false;
    Uint8 palette_ck_मूल्य = 0;
    Uint8 *palette_saved_alpha = रिक्त;
    पूर्णाङ्क palette_saved_alpha_ncolors = 0;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        गच्छ error;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        गच्छ error;
    }

    // Set the bounds of the new surface
    bounds.x = 0;
    bounds.y = 0;
    bounds.w = surface->w;
    bounds.h = surface->h;
    यदि (rect) {
        bounds.w = rect->w;
        bounds.h = rect->h;
    } अन्यथा {
        rect = &bounds;
    }

    // Check for empty destination palette! (results in empty image)
    यदि (palette) {
        पूर्णाङ्क i;
        प्रति (i = 0; i < palette->ncolors; ++i) {
            यदि ((palette->colors[i].r != 0xFF) || (palette->colors[i].g != 0xFF) || (palette->colors[i].b != 0xFF)) {
                भङ्ग;
            }
        }
        यदि (i == palette->ncolors) {
            SDL_SetError("Empty destination palette");
            गच्छ error;
        }
    } अन्यथा यदि (SDL_ISPIXELFORMAT_INDEXED(format)) {
        // Create a dither palette for conversion
        temp_palette = SDL_CreatePalette(1 << SDL_BITSPERPIXEL(format));
        यदि (temp_palette) {
            SDL_DitherPalette(temp_palette);
            palette = temp_palette;
        }
    }

    src_colorspace = surface->colorspace;
    src_properties = surface->props;

    // Create a new surface with the desired format
    यदि (surface->pixels || SDL_MUSTLOCK(surface)) {
        convert = SDL_CreateSurfaceUninitialized(rect->w, rect->h, format);
    } अन्यथा {
        convert = SDL_CreateSurfaceFrom(rect->w, rect->h, format, रिक्त, 0);
    }
    यदि (!convert) {
        गच्छ error;
    }
    यदि (SDL_ISPIXELFORMAT_INDEXED(format)) {
        SDL_SetSurfacePalette(convert, palette);
    }

    यदि (colorspace == SDL_COLORSPACE_UNKNOWN) {
        colorspace = src_colorspace;
    }
    SDL_SetSurfaceColorspace(convert, colorspace);

    यदि (SDL_ISPIXELFORMAT_FOURCC(format) || SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        यदि (surface->format == SDL_PIXELFORMAT_MJPG && format == SDL_PIXELFORMAT_MJPG) {
            // Just do a straight pixel copy of the JPEG image
            size_t size = (size_t)surface->pitch;
            convert->pixels = SDL_malloc(size);
            यदि (!convert->pixels) {
                गच्छ error;
            }
            convert->flags &= ~SDL_SURFACE_PREALLOCATED;
            convert->pitch = surface->pitch;
            SDL_memcpy(convert->pixels, surface->pixels, size);

        } अन्यथा यदि (!SDL_ConvertPixelsAndColorspace(surface->w, surface->h, surface->format, src_colorspace, src_properties, surface->pixels, surface->pitch, convert->format, colorspace, props, convert->pixels, convert->pitch)) {
            गच्छ error;
        }

        // Save the original copy flags
        copy_flags = surface->map.info.flags;

        गच्छ end;
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
    यदि (surface->palette && SDL_ISPIXELFORMAT_ALPHA(format)) {
        bool set_opaque = false;

        bool is_opaque, has_alpha_channel;
        SDL_DetectPalette(surface->palette, &is_opaque, &has_alpha_channel);

        यदि (is_opaque) {
            यदि (!has_alpha_channel) {
                set_opaque = true;
            }
        }

        // Set opaque and backup palette alpha values
        यदि (set_opaque) {
            पूर्णाङ्क i;
            palette_saved_alpha_ncolors = surface->palette->ncolors;
            यदि (palette_saved_alpha_ncolors > 0) {
                palette_saved_alpha = SDL_चळत_alloc(Uint8, palette_saved_alpha_ncolors);
                प्रति (i = 0; i < palette_saved_alpha_ncolors; i++) {
                    palette_saved_alpha[i] = surface->palette->colors[i].a;
                    surface->palette->colors[i].a = SDL_ALPHA_OPAQUE;
                }
            }
        }
    }

    // Transform colorkey to alpha. for cases where source palette has duplicate values, and colorkey is one of them
    यदि (copy_flags & SDL_COPY_COLORKEY) {
        यदि (surface->palette && !palette) {
            palette_ck_transform = true;
            palette_ck_मूल्य = surface->palette->colors[surface->map.info.colorkey].a;
            surface->palette->colors[surface->map.info.colorkey].a = SDL_ALPHA_TRANSPARENT;
        }
    }

    यदि (surface->pixels || SDL_MUSTLOCK(surface)) {
        result = SDL_BlitSurfaceUnchecked(surface, rect, convert, &bounds);
    } अन्यथा {
        result = true;
    }

    // Restore colorkey alpha value
    यदि (palette_ck_transform) {
        surface->palette->colors[surface->map.info.colorkey].a = palette_ck_मूल्य;
    }

    // Restore palette alpha values
    यदि (palette_saved_alpha) {
        पूर्णाङ्क i;
        प्रति (i = 0; i < palette_saved_alpha_ncolors; i++) {
            surface->palette->colors[i].a = palette_saved_alpha[i];
        }
        SDL_चळत_free(palette_saved_alpha);
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
    यदि (!result) {
        गच्छ error;
    }

    यदि (copy_flags & SDL_COPY_COLORKEY) {
        bool set_colorkey_by_color = false;
        bool convert_colorkey = true;

        यदि (surface->palette) {
            यदि (palette &&
                surface->palette->ncolors <= palette->ncolors &&
                (SDL_memcmp(surface->palette->colors, palette->colors,
                            surface->palette->ncolors * परिमाण(SDL_Color)) == 0)) {
                // The palette is identical, just set the same colorkey
                SDL_Set_Surface_Color_किल्ली(convert, true, surface->map.info.colorkey);
            } अन्यथा यदि (!palette) {
                यदि (SDL_ISPIXELFORMAT_ALPHA(format)) {
                    // No need to add the colorkey, transparency is in the alpha channel
                } अन्यथा {
                    // Only set the colorkey information
                    set_colorkey_by_color = true;
                    convert_colorkey = false;
                }
            } अन्यथा {
                set_colorkey_by_color = true;
            }
        } अन्यथा {
            set_colorkey_by_color = true;
        }

        यदि (set_colorkey_by_color) {
            SDL_Surface *tmp;
            SDL_Surface *tmp2;
            पूर्णाङ्क converted_colorkey = 0;

            // Create a dummy surface to get the colorkey converted
            tmp = SDL_CreateSurfaceUninitialized(1, 1, surface->format);
            यदि (!tmp) {
                गच्छ error;
            }

            // Share the palette, if any
            यदि (surface->palette) {
                SDL_SetSurfacePalette(tmp, surface->palette);
            }

            SDL_FillSurfaceRect(tmp, रिक्त, surface->map.info.colorkey);

            tmp->map.info.flags &= ~SDL_COPY_COLORKEY;

            // Conversion of the colorkey
            tmp2 = SDL_ConvertSurfaceAndColorspace(tmp, format, palette, colorspace, props);
            यदि (!tmp2) {
                SDL_DestroySurface(tmp);
                गच्छ error;
            }

            // Get the converted colorkey
            SDL_memcpy(&converted_colorkey, tmp2->pixels, tmp2->fmt->bytes_per_pixel);

            SDL_DestroySurface(tmp);
            SDL_DestroySurface(tmp2);

            // Set the converted colorkey on the new surface
            SDL_Set_Surface_Color_किल्ली(convert, true, converted_colorkey);

            // This is needed when converting for 3D texture upload
            यदि (convert_colorkey) {
                SDL_ConvertColorkeyToAlpha(convert, true);
            }
        }
    }

end:
    यदि (temp_palette) {
        SDL_DestroyPalette(temp_palette);
    }

    SDL_SetSurfaceClipRect(convert, &surface->clip_rect);

    /* Enable alpha blending by default if the new surface has an
     * alpha channel or alpha modulation */
    यदि (SDL_ISPIXELFORMAT_ALPHA(format) ||
        (copy_flags & SDL_COPY_MODULATE_ALPHA)) {
        SDL_SetSurfaceBlendMode(convert, SDL_BLENDMODE_BLEND);
    }
    यदि (copy_flags & SDL_COPY_RLE_DESIRED) {
        SDL_SetSurfaceRLE(convert, true);
    }

    // Copy alternate images
    प्रति (पूर्णाङ्क i = 0; i < surface->अंक_images; ++i) {
        यदि (!SDL_AddSurfaceAlternateImage(convert, surface->images[i])) {
            गच्छ error;
        }
    }

    // Copy properties
    यदि (surface->props) {
        यदि (!SDL_CopyProperties(surface->props, SDL_GetSurfaceProperties(convert))) {
            गच्छ error;
        }

        // Make sure the new surface doesn't reference an old SDL2 surface.
        SDL_ClearProperty(SDL_GetSurfaceProperties(convert), "sdl2-compat.surface2");
    }

    // We're ready to go!
    प्रत्यागम convert;

error:
    यदि (temp_palette) {
        SDL_DestroyPalette(temp_palette);
    }
    यदि (convert) {
        SDL_DestroySurface(convert);
    }
    प्रत्यागम रिक्त;
}

SDL_Surface *SDL_ConvertSurfaceAndColorspace(SDL_Surface *surface, SDL_PixelFormat format, SDL_Palette *palette, SDL_Colorspace colorspace, SDL_PropertiesID props)
{
    प्रत्यागम SDL_ConvertSurfaceRectAndColorspace(surface, रिक्त, format, palette, colorspace, props);
}

SDL_Surface *SDL_RotateSurface(SDL_Surface *surface, भिन्न angle)
{
    SDL_Surface *rotated = रिक्त;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        प्रत्यागम रिक्त;
    }

    SDL_Rect rect_dest;
    द्विगुण cangle, sangle;
    SDL_FPoint center = { surface->w * 0.5f, surface->h * 0.5f };
    SDLgfx_rotozoomSurfaceSizeTrig(surface->w, surface->h, angle, &center, &rect_dest, &cangle, &sangle);

    // This function requires a 32-bit surface or 8-bit surface with a colorkey
    यदि ((SDL_BITSPERPIXEL(surface->format) == 32 && SDL_PIXELLAYOUT(surface->format) == SDL_PACKEDLAYOUT_8888) ||
        (surface->format == SDL_PIXELFORMAT_INDEX8 && SDL_Surface_Has_Color_किल्ली(surface))) {
        rotated = SDLgfx_rotateSurface(surface, angle, 1, 0, 0, &rect_dest, cangle, sangle, &center);
    } अन्यथा {
        SDL_Surface *convert = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);
        यदि (convert) {
            SDL_Surface *tmp = SDLgfx_rotateSurface(convert, angle, 1, 0, 0, &rect_dest, cangle, sangle, &center);
            यदि (tmp) {
                rotated = SDL_ConvertSurfaceAndColorspace(tmp, surface->format, surface->palette, surface->colorspace, surface->props);
                SDL_DestroySurface(tmp);
            }
            SDL_DestroySurface(convert);
        }
    }

    यदि (rotated) {
        यदि (SDL_HasProperty(surface->props, SDL_PROP_SURFACE_ROTATION_FLOAT)) {
            ध्रुव भिन्न rotation = (SDL_Get_संख्या_Property(surface->props, SDL_PROP_SURFACE_ROTATION_FLOAT, 0) - angle);
            SDL_SetFloatProperty(SDL_GetSurfaceProperties(rotated), SDL_PROP_SURFACE_ROTATION_FLOAT, rotation);
        }
    }

    प्रत्यागम rotated;
}

SDL_Surface *SDL_DuplicateSurface(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        प्रत्यागम रिक्त;
    }

    प्रत्यागम SDL_ConvertSurfaceAndColorspace(surface, surface->format, surface->palette, surface->colorspace, surface->props);
}

SDL_Surface *SDL_ScaleSurface(SDL_Surface *surface, पूर्णाङ्क width, पूर्णाङ्क height, SDL_ScaleMode scaleMode)
{
    SDL_Surface *convert = रिक्त;
    Uint32 copy_flags;
    SDL_Color copy_color;
    bool rc;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        गच्छ error;
    }

    यदि (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // We can't directly scale a YUV surface (yet!)
        SDL_Surface *tmp = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        यदि (!tmp) {
            प्रत्यागम रिक्त;
        }

        SDL_Surface *scaled = SDL_ScaleSurface(tmp, width, height, scaleMode);
        SDL_DestroySurface(tmp);
        यदि (!scaled) {
            प्रत्यागम रिक्त;
        }

        SDL_Surface *result = SDL_ConvertSurfaceAndColorspace(scaled, surface->format, रिक्त, surface->colorspace, surface->props);
        SDL_DestroySurface(scaled);
        प्रत्यागम result;
    }

    यदि (SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        // Linear scaling requires conversion to RGBA and then slow pixel color lookup
        scaleMode = SDL_SCALEMODE_NEAREST;
    }

    // Create a new surface with the desired size
    यदि (surface->pixels || SDL_MUSTLOCK(surface)) {
        convert = SDL_CreateSurfaceUninitialized(width, height, surface->format);
    } अन्यथा {
        convert = SDL_CreateSurfaceFrom(width, height, surface->format, रिक्त, 0);
    }
    यदि (!convert) {
        गच्छ error;
    }
    SDL_SetSurfacePalette(convert, surface->palette);
    SDL_SetSurfaceColorspace(convert, surface->colorspace);
    SDL_SetSurfaceRLE(convert, SDL_SurfaceHasRLE(surface));

    यदि (surface->pixels || SDL_MUSTLOCK(surface)) {
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

        rc = SDL_BlitSurfaceScaled(surface, रिक्त, convert, रिक्त, scaleMode);

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
    } अन्यथा {
        rc = true;
    }

    // SDL_BlitSurfaceScaled failed, and so the conversion
    यदि (!rc) {
        गच्छ error;
    }

    // We're ready to go!
    प्रत्यागम convert;

error:
    यदि (convert) {
        SDL_DestroySurface(convert);
    }
    प्रत्यागम रिक्त;
}

SDL_Surface *SDL_ConvertSurfaceRect(SDL_Surface *surface, ध्रुव SDL_Rect *rect, SDL_PixelFormat format)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        प्रत्यागम रिक्त;
    }

    प्रत्यागम SDL_ConvertSurfaceRectAndColorspace(surface, rect, format, रिक्त, SDL_GetDefaultColorspaceForFormat(format), surface->props);
}

SDL_Surface *SDL_ConvertSurface(SDL_Surface *surface, SDL_PixelFormat format)
{
    प्रत्यागम SDL_ConvertSurfaceRect(surface, रिक्त, format);
}

SDL_Surface *SDL_DuplicatePixels(पूर्णाङ्क width, पूर्णाङ्क height, SDL_PixelFormat format, SDL_Colorspace colorspace, शून्य *pixels, पूर्णाङ्क pitch)
{
    SDL_Surface *surface;
    यदि (pixels) {
        surface = SDL_CreateSurfaceUninitialized(width, height, format);
    } अन्यथा {
        surface = SDL_CreateSurfaceFrom(width, height, format, रिक्त, 0);
    }
    यदि (!surface) {
        प्रत्यागम रिक्त;
    }
    SDL_SetSurfaceColorspace(surface, colorspace);

    यदि (surface->pixels) {
        पूर्णाङ्क length = width * SDL_BYTESPERPIXEL(format);
        Uint8 *src = (Uint8 *)pixels;
        Uint8 *dst = (Uint8 *)surface->pixels;
        पूर्णाङ्क rows = height;
        यावत् (rows--) {
            SDL_memcpy(dst, src, length);
            dst += surface->pitch;
            src += pitch;
        }
    }
    प्रत्यागम surface;
}

bool SDL_ConvertPixelsAndColorspace(पूर्णाङ्क width, पूर्णाङ्क height,
                      SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ध्रुव शून्य *src, पूर्णाङ्क src_pitch,
                      SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, शून्य *dst, पूर्णाङ्क dst_pitch)
{
    SDL_Surface src_surface;
    SDL_Surface dst_surface;
    SDL_Rect rect;
    शून्य *nonconst_src = (शून्य *)src;
    bool result;

    CHECK_PARAM(!src) {
        प्रत्यागम SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!src_pitch) {
        प्रत्यागम SDL_InvalidParamError("src_pitch");
    }
    CHECK_PARAM(!dst) {
        प्रत्यागम SDL_InvalidParamError("dst");
    }
    CHECK_PARAM(!dst_pitch) {
        प्रत्यागम SDL_InvalidParamError("dst_pitch");
    }

    यदि (src_colorspace == SDL_COLORSPACE_UNKNOWN) {
        src_colorspace = SDL_GetDefaultColorspaceForFormat(src_format);
    }
    यदि (dst_colorspace == SDL_COLORSPACE_UNKNOWN) {
        dst_colorspace = SDL_GetDefaultColorspaceForFormat(dst_format);
    }

    यदि (src_format == SDL_PIXELFORMAT_MJPG) {
        प्रत्यागम SDL_ConvertPixels_STB(width, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    }

#ifdef SDL_HAVE_YUV
    यदि (SDL_ISPIXELFORMAT_FOURCC(src_format) && SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        प्रत्यागम SDL_ConvertPixels_YUV_to_YUV(width, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } अन्यथा यदि (SDL_ISPIXELFORMAT_FOURCC(src_format)) {
        प्रत्यागम SDL_ConvertPixels_YUV_to_RGB(width, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } अन्यथा यदि (SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        प्रत्यागम SDL_ConvertPixels_RGB_to_YUV(width, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    }
#अन्यथा
    यदि (SDL_ISPIXELFORMAT_FOURCC(src_format) || SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        प्रत्यागम SDL_SetError("SDL not built with YUV support");
    }
#endif

    // Fast path for same format copy
    यदि (src_format == dst_format && src_colorspace == dst_colorspace) {
        यदि (src_pitch == dst_pitch) {
            SDL_memcpy(dst, src, height * src_pitch);
        } अन्यथा {
            पूर्णाङ्क i;
            ध्रुव पूर्णाङ्क bpp = SDL_BYTESPERPIXEL(src_format);
            width *= bpp;
            प्रति (i = height; i--;) {
                SDL_memcpy(dst, src, width);
                src = (ध्रुव Uint8 *)src + src_pitch;
                dst = (Uint8 *)dst + dst_pitch;
            }
        }
        प्रत्यागम true;
    }

    यदि (!SDL_InitializeSurface(&src_surface, width, height, src_format, src_colorspace, src_properties, nonconst_src, src_pitch, true)) {
        प्रत्यागम false;
    }
    SDL_SetSurfaceBlendMode(&src_surface, SDL_BLENDMODE_NONE);

    यदि (!SDL_InitializeSurface(&dst_surface, width, height, dst_format, dst_colorspace, dst_properties, dst, dst_pitch, true)) {
        प्रत्यागम false;
    }

    // Set up the rect and go!
    rect.x = 0;
    rect.y = 0;
    rect.w = width;
    rect.h = height;
    result = SDL_BlitSurfaceUnchecked(&src_surface, &rect, &dst_surface, &rect);

    SDL_DestroySurface(&src_surface);
    SDL_DestroySurface(&dst_surface);

    प्रत्यागम result;
}

bool SDL_ConvertPixels(पूर्णाङ्क width, पूर्णाङ्क height, SDL_PixelFormat src_format, ध्रुव शून्य *src, पूर्णाङ्क src_pitch, SDL_PixelFormat dst_format, शून्य *dst, पूर्णाङ्क dst_pitch)
{
    प्रत्यागम SDL_ConvertPixelsAndColorspace(width, height,
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

स्थिर शून्य SDL_PremultiplyAlpha_AXYZ8888(पूर्णाङ्क width, पूर्णाङ्क height, ध्रुव शून्य *src, पूर्णाङ्क src_pitch, शून्य *dst, पूर्णाङ्क dst_pitch)
{
    पूर्णाङ्क c;
    Uint32 srcpixel;
    Uint32 srcR, srcG, srcB, srcA;
    Uint32 dstpixel;
    Uint32 dstR, dstG, dstB, dstA;

    यावत् (height--) {
        ध्रुव Uint32 *src_px = (ध्रुव Uint32 *)src;
        Uint32 *dst_px = (Uint32 *)dst;
        प्रति (c = width; c; --c) {
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
        src = (ध्रुव Uint8 *)src + src_pitch;
        dst = (Uint8 *)dst + dst_pitch;
    }
}

स्थिर शून्य SDL_PremultiplyAlpha_XYZA8888(पूर्णाङ्क width, पूर्णाङ्क height, ध्रुव शून्य *src, पूर्णाङ्क src_pitch, शून्य *dst, पूर्णाङ्क dst_pitch)
{
    पूर्णाङ्क c;
    Uint32 srcpixel;
    Uint32 srcR, srcG, srcB, srcA;
    Uint32 dstpixel;
    Uint32 dstR, dstG, dstB, dstA;

    यावत् (height--) {
        ध्रुव Uint32 *src_px = (ध्रुव Uint32 *)src;
        Uint32 *dst_px = (Uint32 *)dst;
        प्रति (c = width; c; --c) {
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
        src = (ध्रुव Uint8 *)src + src_pitch;
        dst = (Uint8 *)dst + dst_pitch;
    }
}

स्थिर शून्य SDL_PremultiplyAlpha_AXYZ128(पूर्णाङ्क width, पूर्णाङ्क height, ध्रुव शून्य *src, पूर्णाङ्क src_pitch, शून्य *dst, पूर्णाङ्क dst_pitch)
{
    पूर्णाङ्क c;
    भिन्न flR, flG, flB, flA;

    यावत् (height--) {
        ध्रुव भिन्न *src_px = (ध्रुव भिन्न *)src;
        भिन्न *dst_px = (भिन्न *)dst;
        प्रति (c = width; c; --c) {
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
        src = (ध्रुव Uint8 *)src + src_pitch;
        dst = (Uint8 *)dst + dst_pitch;
    }
}

स्थिर bool SDL_PremultiplyAlphaPixelsAndColorspace(पूर्णाङ्क width, पूर्णाङ्क height, SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ध्रुव शून्य *src, पूर्णाङ्क src_pitch, SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, शून्य *dst, पूर्णाङ्क dst_pitch, bool linear)
{
    SDL_Surface *convert = रिक्त;
    शून्य *final_dst = dst;
    पूर्णाङ्क final_dst_pitch = dst_pitch;
    SDL_PixelFormat format;
    SDL_Colorspace colorspace;
    bool result = false;

    CHECK_PARAM(!src) {
        प्रत्यागम SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!src_pitch) {
        प्रत्यागम SDL_InvalidParamError("src_pitch");
    }
    CHECK_PARAM(!dst) {
        प्रत्यागम SDL_InvalidParamError("dst");
    }
    CHECK_PARAM(!dst_pitch) {
        प्रत्यागम SDL_InvalidParamError("dst_pitch");
    }

    // Use a high precision format if we're converting to linear colorspace or using high precision pixel formats
    यदि (linear ||
        SDL_ISPIXELFORMAT_10BIT(src_format) || SDL_BITSPERPIXEL(src_format) > 32 ||
        SDL_ISPIXELFORMAT_10BIT(dst_format) || SDL_BITSPERPIXEL(dst_format) > 32) {
        यदि (src_format == SDL_PIXELFORMAT_ARGB128_FLOAT ||
            src_format == SDL_PIXELFORMAT_ABGR128_FLOAT) {
            format = src_format;
        } अन्यथा {
            format = SDL_PIXELFORMAT_ARGB128_FLOAT;
        }
    } अन्यथा {
        यदि (src_format == SDL_PIXELFORMAT_ARGB8888 ||
            src_format == SDL_PIXELFORMAT_ABGR8888 ||
            src_format == SDL_PIXELFORMAT_RGBA8888 ||
            src_format == SDL_PIXELFORMAT_BGRA8888) {
            format = src_format;
        } अन्यथा {
            format = SDL_PIXELFORMAT_ARGB8888;
        }
    }
    यदि (linear) {
        colorspace = SDL_COLORSPACE_SRGB_LINEAR;
    } अन्यथा {
        colorspace = SDL_COLORSPACE_SRGB;
    }

    यदि (src_format != format || src_colorspace != colorspace) {
        convert = SDL_CreateSurfaceUninitialized(width, height, format);
        यदि (!convert) {
            गच्छ done;
        }
        यदि (!SDL_ConvertPixelsAndColorspace(width, height, src_format, src_colorspace, src_properties, src, src_pitch, format, colorspace, 0, convert->pixels, convert->pitch)) {
            गच्छ done;
        }

        src = convert->pixels;
        src_pitch = convert->pitch;
        dst = convert->pixels;
        dst_pitch = convert->pitch;

    } अन्यथा यदि (dst_format != format || dst_colorspace != colorspace) {
        convert = SDL_CreateSurfaceUninitialized(width, height, format);
        यदि (!convert) {
            गच्छ done;
        }
        dst = convert->pixels;
        dst_pitch = convert->pitch;
    }

    विकल्प (format) {
    पक्ष SDL_PIXELFORMAT_ARGB8888:
    पक्ष SDL_PIXELFORMAT_ABGR8888:
        SDL_PremultiplyAlpha_AXYZ8888(width, height, src, src_pitch, dst, dst_pitch);
        भङ्ग;
    पक्ष SDL_PIXELFORMAT_RGBA8888:
    पक्ष SDL_PIXELFORMAT_BGRA8888:
        SDL_PremultiplyAlpha_XYZA8888(width, height, src, src_pitch, dst, dst_pitch);
        भङ्ग;
    पक्ष SDL_PIXELFORMAT_ARGB128_FLOAT:
    पक्ष SDL_PIXELFORMAT_ABGR128_FLOAT:
        SDL_PremultiplyAlpha_AXYZ128(width, height, src, src_pitch, dst, dst_pitch);
        भङ्ग;
    स्वभाव:
        SDL_SetError("Unexpected internal pixel format");
        गच्छ done;
    }

    यदि (dst != final_dst) {
        यदि (!SDL_ConvertPixelsAndColorspace(width, height, format, colorspace, 0, convert->pixels, convert->pitch, dst_format, dst_colorspace, dst_properties, final_dst, final_dst_pitch)) {
            गच्छ done;
        }
    }
    result = true;

done:
    यदि (convert) {
        SDL_DestroySurface(convert);
    }
    प्रत्यागम result;
}

bool SDL_PremultiplyAlpha(पूर्णाङ्क width, पूर्णाङ्क height,
                         SDL_PixelFormat src_format, ध्रुव शून्य *src, पूर्णाङ्क src_pitch,
                         SDL_PixelFormat dst_format, शून्य *dst, पूर्णाङ्क dst_pitch, bool linear)
{
    SDL_Colorspace src_colorspace = SDL_GetDefaultColorspaceForFormat(src_format);
    SDL_Colorspace dst_colorspace = SDL_GetDefaultColorspaceForFormat(dst_format);

    प्रत्यागम SDL_PremultiplyAlphaPixelsAndColorspace(width, height, src_format, src_colorspace, 0, src, src_pitch, dst_format, dst_colorspace, 0, dst, dst_pitch, linear);
}

bool SDL_PremultiplySurfaceAlpha(SDL_Surface *surface, bool linear)
{
    SDL_Colorspace colorspace;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        प्रत्यागम SDL_InvalidParamError("surface");
    }

    colorspace = surface->colorspace;

    प्रत्यागम SDL_PremultiplyAlphaPixelsAndColorspace(surface->w, surface->h, surface->format, colorspace, surface->props, surface->pixels, surface->pitch, surface->format, colorspace, surface->props, surface->pixels, surface->pitch, linear);
}

bool SDL_ClearSurface(SDL_Surface *surface, भिन्न r, भिन्न g, भिन्न b, भिन्न a)
{
    SDL_Rect clip_rect;
    bool result = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        प्रत्यागम SDL_InvalidParamError("surface");
    }

    SDL_GetSurfaceClipRect(surface, &clip_rect);
    SDL_SetSurfaceClipRect(surface, रिक्त);

    यदि (!SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_BYTESPERPIXEL(surface->format) <= परिमाण(Uint32)) {
        Uint32 color;

        color = SDL_MapSurfaceRGBA(surface,
                    (Uint8)SDL_roundf(SDL_clamp(r, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(g, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(b, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(a, 0.0f, 1.0f) * 255.0f));
        result = SDL_FillSurfaceRect(surface, रिक्त, color);
    } अन्यथा यदि (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // We can't directly set an RGB value on a YUV surface
        SDL_Surface *tmp = SDL_CreateSurfaceUninitialized(surface->w, surface->h, SDL_PIXELFORMAT_ARGB8888);
        यदि (!tmp) {
            गच्छ done;
        }

        यदि (SDL_ClearSurface(tmp, r, g, b, a)) {
            result = SDL_ConvertPixelsAndColorspace(surface->w, surface->h, tmp->format, tmp->colorspace, tmp->props, tmp->pixels, tmp->pitch, surface->format, surface->colorspace, surface->props, surface->pixels, surface->pitch);
        }
        SDL_DestroySurface(tmp);
    } अन्यथा {
        // Take advantage of blit color conversion
        SDL_Surface *tmp = SDL_CreateSurfaceUninitialized(1, 1, SDL_PIXELFORMAT_RGBA128_FLOAT);
        यदि (!tmp) {
            गच्छ done;
        }
        SDL_SetSurfaceColorspace(tmp, surface->colorspace);
        SDL_SetSurfaceBlendMode(tmp, SDL_BLENDMODE_NONE);

        भिन्न *pixels = (भिन्न *)tmp->pixels;
        pixels[0] = r;
        pixels[1] = g;
        pixels[2] = b;
        pixels[3] = a;

        result = SDL_BlitSurfaceScaled(tmp, रिक्त, surface, रिक्त, SDL_SCALEMODE_NEAREST);
        SDL_DestroySurface(tmp);
    }

done:
    SDL_SetSurfaceClipRect(surface, &clip_rect);

    प्रत्यागम result;
}

Uint32 SDL_MapSurfaceRGB(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b)
{
    प्रत्यागम SDL_MapSurfaceRGBA(surface, r, g, b, SDL_ALPHA_OPAQUE);
}

Uint32 SDL_MapSurfaceRGBA(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        प्रत्यागम true;
    }
    प्रत्यागम SDL_MapRGBA(surface->fmt, surface->palette, r, g, b, a);
}

// This function Copyright 2023 Collabora Ltd., contributed to SDL under the ZLib license
bool SDL_ReadSurfacePixel(SDL_Surface *surface, पूर्णाङ्क x, पूर्णाङ्क y, Uint8 *r, Uint8 *g, Uint8 *b, Uint8 *a)
{
    Uint32 pixel = 0;
    size_t bytes_per_pixel;
    Uint8 unused;
    Uint8 *p;
    bool result = false;

    यदि (r) {
        *r = 0;
    } अन्यथा {
        r = &unused;
    }

    यदि (g) {
        *g = 0;
    } अन्यथा {
        g = &unused;
    }

    यदि (b) {
        *b = 0;
    } अन्यथा {
        b = &unused;
    }

    यदि (a) {
        *a = 0;
    } अन्यथा {
        a = &unused;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        प्रत्यागम SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        प्रत्यागम SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        प्रत्यागम SDL_InvalidParamError("y");
    }

    bytes_per_pixel = SDL_BYTESPERPIXEL(surface->format);

    यदि (SDL_MUSTLOCK(surface)) {
        यदि (!SDL_LockSurface(surface)) {
            प्रत्यागम false;
        }
    }

    p = (Uint8 *)surface->pixels + y * surface->pitch + x * bytes_per_pixel;

    यदि (bytes_per_pixel <= परिमाण(pixel) &&
        !SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_COLORSPACEPRIMARIES(surface->colorspace) == SDL_COLOR_PRIMARIES_BT709) {
        /* Fill the appropriate number of least-significant bytes of pixel,
         * leaving the most-significant bytes set to zero */
#यदि SDL_BYTEORDER == SDL_BIG_ENDIAN
        SDL_memcpy(((Uint8 *)&pixel) + (परिमाण(pixel) - bytes_per_pixel), p, bytes_per_pixel);
#अन्यथा
        SDL_memcpy(&pixel, p, bytes_per_pixel);
#endif
        SDL_GetRGBA(pixel, surface->fmt, surface->palette, r, g, b, a);
        result = true;
    } अन्यथा यदि (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // FIXME: We need code to extract a single macroblock from a YUV surface
        SDL_Surface *converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        यदि (converted) {
            result = SDL_ReadSurfacePixel(converted, x, y, r, g, b, a);
            SDL_DestroySurface(converted);
        }
    } अन्यथा {
        // This is really slow, but it gets the job done
        Uint8 rgba[4];

        यदि (SDL_ConvertPixelsAndColorspace(1, 1, surface->format, surface->colorspace, surface->props, p, surface->pitch, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, rgba, परिमाण(rgba))) {
            *r = rgba[0];
            *g = rgba[1];
            *b = rgba[2];
            *a = rgba[3];
            result = true;
        }
    }

    यदि (SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }
    प्रत्यागम result;
}

bool SDL_ReadSurfacePixelFloat(SDL_Surface *surface, पूर्णाङ्क x, पूर्णाङ्क y, भिन्न *r, भिन्न *g, भिन्न *b, भिन्न *a)
{
    भिन्न unused;
    bool result = false;

    यदि (r) {
        *r = 0.0f;
    } अन्यथा {
        r = &unused;
    }

    यदि (g) {
        *g = 0.0f;
    } अन्यथा {
        g = &unused;
    }

    यदि (b) {
        *b = 0.0f;
    } अन्यथा {
        b = &unused;
    }

    यदि (a) {
        *a = 0.0f;
    } अन्यथा {
        a = &unused;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        प्रत्यागम SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        प्रत्यागम SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        प्रत्यागम SDL_InvalidParamError("y");
    }

    यदि (SDL_BYTESPERPIXEL(surface->format) <= परिमाण(Uint32) &&
        !SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_COLORSPACEPRIMARIES(surface->colorspace) == SDL_COLOR_PRIMARIES_BT709) {
        Uint8 r8, g8, b8, a8;

        यदि (SDL_ReadSurfacePixel(surface, x, y, &r8, &g8, &b8, &a8)) {
            *r = (भिन्न)r8 / 255.0f;
            *g = (भिन्न)g8 / 255.0f;
            *b = (भिन्न)b8 / 255.0f;
            *a = (भिन्न)a8 / 255.0f;
            result = true;
        }
    } अन्यथा यदि (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // FIXME: We need code to extract a single macroblock from a YUV surface
        SDL_Surface *converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        यदि (converted) {
            result = SDL_ReadSurfacePixelFloat(converted, x, y, r, g, b, a);
            SDL_DestroySurface(converted);
        }
    } अन्यथा {
        // This is really slow, but it gets the job done
        भिन्न rgba[4];
        Uint8 *p;

        यदि (SDL_MUSTLOCK(surface)) {
            यदि (!SDL_LockSurface(surface)) {
                प्रत्यागम false;
            }
        }

        p = (Uint8 *)surface->pixels + y * surface->pitch + x * SDL_BYTESPERPIXEL(surface->format);

        यदि (surface->format == SDL_PIXELFORMAT_RGBA128_FLOAT) {
            SDL_memcpy(rgba, p, परिमाण(rgba));
            result = true;
        } अन्यथा {
            SDL_Colorspace src_colorspace = surface->colorspace;
            SDL_Colorspace dst_colorspace = (src_colorspace == SDL_COLORSPACE_SRGB_LINEAR ? SDL_COLORSPACE_SRGB_LINEAR : SDL_COLORSPACE_SRGB);

            यदि (SDL_ConvertPixelsAndColorspace(1, 1, surface->format, src_colorspace, surface->props, p, surface->pitch, SDL_PIXELFORMAT_RGBA128_FLOAT, dst_colorspace, 0, rgba, परिमाण(rgba))) {
                result = true;
            }
        }

        यदि (result) {
            *r = rgba[0];
            *g = rgba[1];
            *b = rgba[2];
            *a = rgba[3];
        }

        यदि (SDL_MUSTLOCK(surface)) {
            SDL_UnlockSurface(surface);
        }
    }
    प्रत्यागम result;
}

bool SDL_WriteSurfacePixel(SDL_Surface *surface, पूर्णाङ्क x, पूर्णाङ्क y, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    Uint32 pixel = 0;
    size_t bytes_per_pixel;
    Uint8 *p;
    bool result = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        प्रत्यागम SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        प्रत्यागम SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        प्रत्यागम SDL_InvalidParamError("y");
    }

    bytes_per_pixel = SDL_BYTESPERPIXEL(surface->format);

    यदि (SDL_MUSTLOCK(surface)) {
        यदि (!SDL_LockSurface(surface)) {
            प्रत्यागम false;
        }
    }

    p = (Uint8 *)surface->pixels + y * surface->pitch + x * bytes_per_pixel;

    यदि (bytes_per_pixel <= परिमाण(pixel) && !SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        pixel = SDL_MapRGBA(surface->fmt, surface->palette, r, g, b, a);
#यदि SDL_BYTEORDER == SDL_BIG_ENDIAN
        SDL_memcpy(p, ((Uint8 *)&pixel) + (परिमाण(pixel) - bytes_per_pixel), bytes_per_pixel);
#अन्यथा
        SDL_memcpy(p, &pixel, bytes_per_pixel);
#endif
        result = true;
    } अन्यथा यदि (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        result = SDL_Unsupported();
    } अन्यथा {
        // This is really slow, but it gets the job done
        Uint8 rgba[4];

        rgba[0] = r;
        rgba[1] = g;
        rgba[2] = b;
        rgba[3] = a;
        result = SDL_ConvertPixelsAndColorspace(1, 1, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, rgba, परिमाण(rgba), surface->format, surface->colorspace, surface->props, p, surface->pitch);
    }

    यदि (SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }
    प्रत्यागम result;
}

bool SDL_WriteSurfacePixelFloat(SDL_Surface *surface, पूर्णाङ्क x, पूर्णाङ्क y, भिन्न r, भिन्न g, भिन्न b, भिन्न a)
{
    bool result = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        प्रत्यागम SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        प्रत्यागम SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        प्रत्यागम SDL_InvalidParamError("y");
    }

    यदि (SDL_BYTESPERPIXEL(surface->format) <= परिमाण(Uint32) && !SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        Uint8 r8, g8, b8, a8;

        r8 = (Uint8)SDL_round(SDL_clamp(r, 0.0f, 1.0f) * 255.0f);
        g8 = (Uint8)SDL_round(SDL_clamp(g, 0.0f, 1.0f) * 255.0f);
        b8 = (Uint8)SDL_round(SDL_clamp(b, 0.0f, 1.0f) * 255.0f);
        a8 = (Uint8)SDL_round(SDL_clamp(a, 0.0f, 1.0f) * 255.0f);
        यदि (SDL_WriteSurfacePixel(surface, x, y, r8, g8, b8, a8)) {
            result = true;
        }
    } अन्यथा यदि (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        result = SDL_Unsupported();
    } अन्यथा {
        // This is really slow, but it gets the job done
        भिन्न rgba[4];
        Uint8 *p;

        यदि (SDL_MUSTLOCK(surface)) {
            यदि (!SDL_LockSurface(surface)) {
                प्रत्यागम false;
            }
        }

        p = (Uint8 *)surface->pixels + y * surface->pitch + x * SDL_BYTESPERPIXEL(surface->format);

        rgba[0] = r;
        rgba[1] = g;
        rgba[2] = b;
        rgba[3] = a;

        यदि (surface->format == SDL_PIXELFORMAT_RGBA128_FLOAT) {
            SDL_memcpy(p, rgba, परिमाण(rgba));
            result = true;
        } अन्यथा {
            SDL_Colorspace dst_colorspace = surface->colorspace;
            SDL_Colorspace src_colorspace = (dst_colorspace == SDL_COLORSPACE_SRGB_LINEAR ? SDL_COLORSPACE_SRGB_LINEAR : SDL_COLORSPACE_SRGB);

            result = SDL_ConvertPixelsAndColorspace(1, 1, SDL_PIXELFORMAT_RGBA128_FLOAT, src_colorspace, 0, rgba, परिमाण(rgba), surface->format, dst_colorspace, surface->props, p, surface->pitch);
        }

        यदि (SDL_MUSTLOCK(surface)) {
            SDL_UnlockSurface(surface);
        }
    }
    प्रत्यागम result;
}

/*
 * Free a surface created by the above function.
 */
शून्य SDL_DestroySurface(SDL_Surface *surface)
{
    यदि (!SDL_SurfaceValid(surface)) {
        प्रत्यागम;
    }
    यदि (surface->internal_flags & SDL_INTERNAL_SURFACE_DONTFREE) {
        प्रत्यागम;
    }
    यदि (--surface->refcount > 0) {
        प्रत्यागम;
    }

    SDL_RemoveSurfaceAlternateImages(surface);

    SDL_DestroyProperties(surface->props);

    SDL_InvalidateMap(&surface->map);

    यावत् (surface->locked > 0) {
        SDL_UnlockSurface(surface);
    }
#ifdef SDL_HAVE_RLE
    यदि (surface->internal_flags & SDL_INTERNAL_SURFACE_RLEACCEL) {
        SDL_UnRLESurface(surface);
    }
#endif
    SDL_SetSurfacePalette(surface, रिक्त);

    यदि (surface->flags & SDL_SURFACE_PREALLOCATED) {
        // Don't free
    } अन्यथा यदि (surface->flags & SDL_SURFACE_SIMD_ALIGNED) {
        // Free aligned
        SDL_aligned_free(surface->pixels);
    } अन्यथा {
        // Normal
        SDL_free(surface->pixels);
    }

    surface->reserved = रिक्त;

    यदि (!(surface->internal_flags & SDL_INTERNAL_SURFACE_चळत)) {
        SDL_free(surface);
    }
}

SDL_Surface *SDL_LoadSurface_IO(SDL_IOStream *src, bool closeio)
{
    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        प्रत्यागम रिक्त;
    }

    यदि (SDL_IsBMP(src)) {
        प्रत्यागम SDL_LoadBMP_IO(src, closeio);
    } अन्यथा यदि (SDL_IsPNG(src)) {
        प्रत्यागम SDL_LoadPNG_IO(src, closeio);
    } अन्यथा यदि (SDL_IsJPG(src)) {
        प्रत्यागम SDL_LoadJPG_IO(src, closeio);
    } अन्यथा {
        यदि (closeio) {
            SDL_CloseIO(src);
        }
        SDL_SetError("Unsupported image format");
        प्रत्यागम रिक्त;
    }
}

SDL_Surface *SDL_LoadSurface(ध्रुव वर्ण *file)
{
    SDL_IOStream *stream = SDL_IOFromFile(file, "rb");
    यदि (!stream) {
        प्रत्यागम रिक्त;
    }

    प्रत्यागम SDL_LoadSurface_IO(stream, true);
}
