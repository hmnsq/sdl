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
    पटिनिवत्त (surface && surface->reserved == &SDL_surface_magic);
}

शून्य SDL_UpdateSurfaceLockFlag(SDL_Surface *surface)
{
    // We need to mark the surface as needing unlock while locked
    सचे ((surface->flags & SDL_SURFACE_LOCKED) ||
        (surface->internal_flags & SDL_INTERNAL_SURFACE_RLEACCEL)) {
        surface->flags |= SDL_SURFACE_LOCK_NEEDED;
    } अञ्ञथा {
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
    सचे (SDL_BITSPERPIXEL(format) >= 8) {
        सचे (!SDL_size_mul_check_overflow(width, SDL_BYTESPERPIXEL(format), pitch)) {
            पटिनिवत्त SDL_SetError("width * bpp would overflow");
        }
    } अञ्ञथा {
        सचे (!SDL_size_mul_check_overflow(width, SDL_BITSPERPIXEL(format), pitch)) {
            पटिनिवत्त SDL_SetError("width * bpp would overflow");
        }
        सचे (!SDL_size_add_check_overflow(*pitch, 7, pitch)) {
            पटिनिवत्त SDL_SetError("aligning pitch would overflow");
        }
        *pitch /= 8;
    }
    सचे (!minimal) {
        // 4-byte aligning for speed
        सचे (!SDL_size_add_check_overflow(*pitch, 3, pitch)) {
            पटिनिवत्त SDL_SetError("aligning pitch would overflow");
        }
        *pitch &= ~3;
    }

    सचे (!SDL_size_mul_check_overflow(height, *pitch, size)) {
        पटिनिवत्त SDL_SetError("height * pitch would overflow");
    }

    पटिनिवत्त true;
}

bool SDL_CalculateSurfaceSize(SDL_PixelFormat format, पूर्णाङ्क width, पूर्णाङ्क height, size_t *size, size_t *pitch, bool minimalPitch)
{
    size_t p = 0, sz = 0;

    सचे (size) {
        *size = 0;
    }

    सचे (pitch) {
        *pitch = 0;
    }

    सचे (SDL_ISPIXELFORMAT_FOURCC(format)) {
        सचे (format == SDL_PIXELFORMAT_MJPG) {
            // We don't know in advance what it will be, we'll figure it out later.
            पटिनिवत्त true;
        }

        सचे (!SDL_CalculateYUVSize(format, width, height, &sz, &p)) {
            // Overflow...
            पटिनिवत्त false;
        }
    } अञ्ञथा {
        सचे (!SDL_CalculateRGBSize(format, width, height, &sz, &p, minimalPitch)) {
            // Overflow...
            पटिनिवत्त false;
        }
    }

    सचे (size) {
        *size = sz;
    }

    सचे (pitch) {
        *pitch = p;
    }

    पटिनिवत्त true;
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

    सचे (onstack) {
        surface->internal_flags |= SDL_INTERNAL_SURFACE_राशिः;
    }

    surface->fmt = SDL_GetPixelFormatDetails(format);
    सचे (!surface->fmt) {
        SDL_DestroySurface(surface);
        पटिनिवत्त false;
    }

    // Initialize the clip rect
    surface->clip_rect.w = width;
    surface->clip_rect.h = height;

    // Allocate an empty mapping
    surface->map.info.r = 0xFF;
    surface->map.info.g = 0xFF;
    surface->map.info.b = 0xFF;
    surface->map.info.a = 0xFF;

    सचे (colorspace == SDL_COLORSPACE_UNKNOWN) {
        surface->colorspace = SDL_GetDefaultColorspaceForFormat(format);
    } अञ्ञथा {
        surface->colorspace = colorspace;
    }

    सचे (props) {
        सचे (!SDL_CopyProperties(props, SDL_GetSurfaceProperties(surface))) {
            SDL_DestroySurface(surface);
            पटिनिवत्त false;
        }
    }

    // By default surfaces with an alpha mask are set up for blending
    सचे (SDL_ISPIXELFORMAT_ALPHA(surface->format)) {
        SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
    }

    // The surface is ready to go
    surface->refcount = 1;
    पटिनिवत्त true;
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
        पटिनिवत्त रिक्त;
    }

    CHECK_PARAM(height < 0) {
        SDL_InvalidParamError("height");
        पटिनिवत्त रिक्त;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        पटिनिवत्त रिक्त;
    }

    सचे (!SDL_CalculateSurfaceSize(format, width, height, &size, &pitch, false /* not minimal pitch */)) {
        // Overflow...
        पटिनिवत्त रिक्त;
    }

    // Allocate and initialize the surface
    surface = (SDL_Surface *)SDL_malloc(परिमाण(*surface));
    सचे (!surface) {
        पटिनिवत्त रिक्त;
    }

    सचे (!SDL_InitializeSurface(surface, width, height, format, SDL_COLORSPACE_UNKNOWN, 0, रिक्त, (पूर्णाङ्क)pitch, false)) {
        पटिनिवत्त रिक्त;
    }

    सचे (surface->w && surface->h && format != SDL_PIXELFORMAT_MJPG) {
        surface->flags &= ~SDL_SURFACE_PREALLOCATED;
        सचे (SDL_GetHintBoolean("SDL_SURFACE_MALLOC", false)) {
            सचे (clear_surface) {
                surface->pixels = SDL_calloc(1, size);
            } अञ्ञथा {
                surface->pixels = SDL_malloc(size);
            }
        } अञ्ञथा {
            surface->flags |= SDL_SURFACE_SIMD_ALIGNED;
            सचे (clear_surface) {
                surface->pixels = SDL_aligned_alloc_zero(SDL_GetSIMDAlignment(), size);
            } अञ्ञथा {
                surface->pixels = SDL_aligned_alloc(SDL_GetSIMDAlignment(), size);
            }
        }
        सचे (!surface->pixels) {
            SDL_DestroySurface(surface);
            पटिनिवत्त रिक्त;
        }
    }
    पटिनिवत्त surface;
}

SDL_Surface *SDL_CreateSurfaceZeroed(पूर्णाङ्क width, पूर्णाङ्क height, SDL_PixelFormat format)
{
    पटिनिवत्त SDL_CreateSurfaceInternal(width, height, format, true);
}

SDL_Surface *SDL_CreateSurfaceUninitialized(पूर्णाङ्क width, पूर्णाङ्क height, SDL_PixelFormat format)
{
    पटिनिवत्त SDL_CreateSurfaceInternal(width, height, format, false);
}

SDL_Surface *SDL_CreateSurface(पूर्णाङ्क width, पूर्णाङ्क height, SDL_PixelFormat format)
{
    पटिनिवत्त SDL_CreateSurfaceZeroed(width, height, format);
}


/*
 * Create an RGB surface from an existing memory buffer using the given
 * enum SDL_PIXELFORMAT_* format
 */
SDL_Surface *SDL_CreateSurfaceFrom(पूर्णाङ्क width, पूर्णाङ्क height, SDL_PixelFormat format, शून्य *pixels, पूर्णाङ्क pitch)
{
    CHECK_PARAM(width < 0) {
        SDL_InvalidParamError("width");
        पटिनिवत्त रिक्त;
    }

    CHECK_PARAM(height < 0) {
        SDL_InvalidParamError("height");
        पटिनिवत्त रिक्त;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        पटिनिवत्त रिक्त;
    }

    सचे (pitch == 0 && !pixels) {
        // The application will fill these in later with valid values
    } अञ्ञथा {
        size_t minimalPitch;

        सचे (!SDL_CalculateSurfaceSize(format, width, height, रिक्त, &minimalPitch, true /* minimal pitch */)) {
            // Overflow...
            पटिनिवत्त रिक्त;
        }

        CHECK_PARAM(pitch < 0 || (size_t)pitch < minimalPitch) {
            SDL_InvalidParamError("pitch");
            पटिनिवत्त रिक्त;
        }
    }

    // Allocate and initialize the surface
    SDL_Surface *surface = (SDL_Surface *)SDL_malloc(परिमाण(*surface));
    सचे (!surface ||
        !SDL_InitializeSurface(surface, width, height, format, SDL_COLORSPACE_UNKNOWN, 0, pixels, pitch, false)) {
        पटिनिवत्त रिक्त;
    }
    पटिनिवत्त surface;
}

SDL_PropertiesID SDL_GetSurfaceProperties(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        पटिनिवत्त 0;
    }

    सचे (!surface->props) {
        surface->props = SDL_CreateProperties();
    }
    पटिनिवत्त surface->props;
}

bool SDL_SetSurfaceColorspace(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        पटिनिवत्त SDL_InvalidParamError("surface");
    }

    surface->colorspace = colorspace;
    पटिनिवत्त true;
}

SDL_Colorspace SDL_GetSurfaceColorspace(SDL_Surface *surface)
{
    सचे (!SDL_SurfaceValid(surface)) {
        पटिनिवत्त SDL_COLORSPACE_UNKNOWN;
    }

    पटिनिवत्त surface->colorspace;
}

भिन्न SDL_GetDefaultSDRWhitePoint(SDL_Colorspace colorspace)
{
    पटिनिवत्त SDL_GetSurfaceSDRWhitePoint(रिक्त, colorspace);
}

भिन्न SDL_GetSurfaceSDRWhitePoint(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    SDL_TransferCharacteristics transfer = SDL_COLORSPACETRANSFER(colorspace);

    सचे (transfer == SDL_TRANSFER_CHARACTERISTICS_LINEAR ||
        transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
        SDL_PropertiesID props;
        भिन्न default_मानम् = 1.0f;

        सचे (SDL_SurfaceValid(surface)) {
            props = surface->props;
        } अञ्ञथा {
            props = 0;
        }
        सचे (transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
            /* The older standards use an SDR white point of 100 nits.
             * ITU-R BT.2408-6 recommends using an SDR white point of 203 nits.
             * This is the default Chrome uses, and what a lot of game content
             * assumes, so we'll go with that.
             */
            ध्रुव भिन्न DEFAULT_PQ_SDR_WHITE_POINT = 203.0f;
            default_मानम् = DEFAULT_PQ_SDR_WHITE_POINT;
        }
        पटिनिवत्त SDL_GetFloatProperty(props, SDL_PROP_SURFACE_SDR_WHITE_POINT_FLOAT, default_मानम्);
    }
    पटिनिवत्त 1.0f;
}

भिन्न SDL_GetDefaultHDRHeadroom(SDL_Colorspace colorspace)
{
    पटिनिवत्त SDL_GetSurfaceHDRHeadroom(रिक्त, colorspace);
}

भिन्न SDL_GetSurfaceHDRHeadroom(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    SDL_TransferCharacteristics transfer = SDL_COLORSPACETRANSFER(colorspace);

    सचे (transfer == SDL_TRANSFER_CHARACTERISTICS_LINEAR ||
        transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
        SDL_PropertiesID props;
        भिन्न default_मानम् = 0.0f;

        सचे (SDL_SurfaceValid(surface)) {
            props = surface->props;
        } अञ्ञथा {
            props = 0;
        }
        पटिनिवत्त SDL_GetFloatProperty(props, SDL_PROP_SURFACE_HDR_HEADROOM_FLOAT, default_मानम्);
    }
    पटिनिवत्त 1.0f;
}

SDL_Palette *SDL_CreateSurfacePalette(SDL_Surface *surface)
{
    SDL_Palette *palette;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        पटिनिवत्त रिक्त;
    }

    CHECK_PARAM(!SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        SDL_SetError("The surface is not indexed format");
        पटिनिवत्त रिक्त;
    }

    palette = SDL_CreatePalette((1 << SDL_BITSPERPIXEL(surface->format)));
    सचे (!palette) {
        पटिनिवत्त रिक्त;
    }

    सचे (palette->ncolors == 2) {
        // Create a black and white bitmap palette
        palette->colors[0].r = 0xFF;
        palette->colors[0].g = 0xFF;
        palette->colors[0].b = 0xFF;
        palette->colors[1].r = 0x00;
        palette->colors[1].g = 0x00;
        palette->colors[1].b = 0x00;
    }

    सचे (!SDL_SetSurfacePalette(surface, palette)) {
        SDL_DestroyPalette(palette);
        पटिनिवत्त रिक्त;
    }

    // The surface has retained the palette, we can remove the reference here
    SDL_assert(palette->refcount == 2);
    SDL_DestroyPalette(palette);
    पटिनिवत्त palette;
}

bool SDL_SetSurfacePalette(SDL_Surface *surface, SDL_Palette *palette)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        पटिनिवत्त SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(palette && !SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        पटिनिवत्त SDL_SetError("Surface doesn't use a palette");
    }

    CHECK_PARAM(palette && palette->ncolors > (1 << SDL_BITSPERPIXEL(surface->format))) {
        पटिनिवत्त SDL_SetError("Palette doesn't match surface format");
    }

    सचे (palette != surface->palette) {
        सचे (surface->palette) {
            SDL_DestroyPalette(surface->palette);
        }

        surface->palette = palette;

        सचे (surface->palette) {
            ++surface->palette->refcount;
        }
    }

    SDL_InvalidateMap(&surface->map);

    पटिनिवत्त true;
}

SDL_Palette *SDL_GetSurfacePalette(SDL_Surface *surface)
{
    सचे (!SDL_SurfaceValid(surface)) {
        पटिनिवत्त रिक्त;
    }

    पटिनिवत्त surface->palette;
}

bool SDL_AddSurfaceAlternateImage(SDL_Surface *surface, SDL_Surface *image)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        पटिनिवत्त SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(!SDL_SurfaceValid(image)) {
        पटिनिवत्त SDL_InvalidParamError("image");
    }

    SDL_Surface **images = (SDL_Surface **)SDL_realloc(surface->images, (surface->अङ्कः_images + 1) * परिमाण(*images));
    सचे (!images) {
        पटिनिवत्त false;
    }
    images[surface->अङ्कः_images] = image;
    surface->images = images;
    ++surface->अङ्कः_images;
    ++image->refcount;
    पटिनिवत्त true;
}

bool SDL_SurfaceHasAlternateImages(SDL_Surface *surface)
{
    सचे (!SDL_SurfaceValid(surface)) {
        पटिनिवत्त false;
    }

    पटिनिवत्त (surface->अङ्कः_images > 0);
}

SDL_Surface **SDL_GetSurfaceImages(SDL_Surface *surface, पूर्णाङ्क *गणनम्)
{
    सचे (गणनम्) {
        *गणनम् = 0;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        पटिनिवत्त रिक्त;
    }

    पूर्णाङ्क अङ्कः_images = 1 + surface->अङ्कः_images;
    SDL_Surface **images = (SDL_Surface **)SDL_malloc((अङ्कः_images + 1) * परिमाण(*images));
    सचे (!images) {
        पटिनिवत्त रिक्त;
    }
    images[0] = surface;
    सचे (surface->अङ्कः_images > 0) {
        SDL_memcpy(&images[1], surface->images, (surface->अङ्कः_images * परिमाण(images[1])));
    }
    images[अङ्कः_images] = रिक्त;

    सचे (गणनम्) {
        *गणनम् = अङ्कः_images;
    }
    पटिनिवत्त images;
}

SDL_Surface *SDL_GetSurfaceImage(SDL_Surface *surface, भिन्न display_scale)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        पटिनिवत्त रिक्त;
    }

    सचे (!SDL_SurfaceHasAlternateImages(surface)) {
        ++surface->refcount;
        पटिनिवत्त surface;
    }

    // This surface has high DPI images, pick the best one available, or scale one to the correct size
    SDL_Surface **images = SDL_GetSurfaceImages(surface, रिक्त);
    सचे (!images) {
        // Failure, fall back to the existing surface
        ++surface->refcount;
        पटिनिवत्त surface;
    }

    // Find closest image. Images that are larger than the
    // desired size are preferred over images that are smaller.
    SDL_Surface *closest = रिक्त;
    पूर्णाङ्क desired_w = (पूर्णाङ्क)SDL_round(surface->w * display_scale);
    पूर्णाङ्क desired_h = (पूर्णाङ्क)SDL_round(surface->h * display_scale);
    पूर्णाङ्क desired_size = desired_w * desired_h;
    पूर्णाङ्क closest_distance = -1;
    पूर्णाङ्क closest_size = -1;
    अत्थाय (पूर्णाङ्क i = 0; images[i]; ++i) {
        SDL_Surface *candidate = images[i];
        पूर्णाङ्क size = candidate->w * candidate->h;
        पूर्णाङ्क delta_w = (candidate->w - desired_w);
        पूर्णाङ्क delta_h = (candidate->h - desired_h);
        पूर्णाङ्क distance = (delta_w * delta_w) + (delta_h * delta_h);
        सचे (closest_distance < 0 || distance < closest_distance ||
            (size > desired_size && closest_size < desired_size)) {
            closest = candidate;
            closest_distance = distance;
            closest_size = size;
        }
    }
    SDL_free(images);
    SDL_assert(closest != रिक्त);    // We should always have at least one surface

    सचे (closest->w == desired_w && closest->h == desired_h) {
        ++closest->refcount;
        पटिनिवत्त closest;
    }

    // We need to scale the image to the correct size. To maintain good image quality, downscaling
    // is done in steps, never reducing the width and height by more than half each time.
    SDL_Surface *scaled = closest;
    करोहि {
        पूर्णाङ्क next_scaled_w = SDL_max(desired_w, (scaled->w + 1) / 2);
        पूर्णाङ्क next_scaled_h = SDL_max(desired_h, (scaled->h + 1) / 2);
        SDL_Surface *next_scaled = SDL_ScaleSurface(scaled, next_scaled_w, next_scaled_h, SDL_SCALEMODE_LINEAR);
        सचे (scaled != closest) {
            SDL_DestroySurface(scaled);
        }
        scaled = next_scaled;
        सचे (!scaled) {
            // Failure, fall back to the closest surface
            ++closest->refcount;
            पटिनिवत्त closest;
        }
    } याव (scaled->w != desired_w || scaled->h != desired_h);

    पटिनिवत्त scaled;
}

शून्य SDL_RemoveSurfaceAlternateImages(SDL_Surface *surface)
{
    सचे (!SDL_SurfaceValid(surface)) {
        पटिनिवत्त;
    }

    सचे (surface->अङ्कः_images > 0) {
        अत्थाय (पूर्णाङ्क i = 0; i < surface->अङ्कः_images; ++i) {
            SDL_DestroySurface(surface->images[i]);
        }
        SDL_free(surface->images);
        surface->images = रिक्त;
        surface->अङ्कः_images = 0;
    }
}

bool SDL_SetSurfaceRLE(SDL_Surface *surface, bool enabled)
{
    पूर्णाङ्क flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        पटिनिवत्त SDL_InvalidParamError("surface");
    }

    flags = surface->map.info.flags;
    सचे (enabled) {
        surface->map.info.flags |= SDL_COPY_RLE_DESIRED;
    } अञ्ञथा {
        surface->map.info.flags &= ~SDL_COPY_RLE_DESIRED;
    }
    सचे (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    पटिनिवत्त true;
}

bool SDL_SurfaceHasRLE(SDL_Surface *surface)
{
    सचे (!SDL_SurfaceValid(surface)) {
        पटिनिवत्त false;
    }

    सचे (!(surface->map.info.flags & SDL_COPY_RLE_DESIRED)) {
        पटिनिवत्त false;
    }

    पटिनिवत्त true;
}

bool SDL_Set_Surface_Color_कुञ्चिका(SDL_Surface *surface, bool enabled, Uint32 कुञ्चिका)
{
    पूर्णाङ्क flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        पटिनिवत्त SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(surface->palette && कुञ्चिका >= ((Uint32)surface->palette->ncolors)) {
        पटिनिवत्त SDL_InvalidParamError("key");
    }

    flags = surface->map.info.flags;
    सचे (enabled) {
        surface->map.info.flags |= SDL_COPY_COLORKEY;
        surface->map.info.colorkey = कुञ्चिका;
    } अञ्ञथा {
        surface->map.info.flags &= ~SDL_COPY_COLORKEY;
    }
    सचे (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }

    पटिनिवत्त true;
}

bool SDL_Surface_Has_Color_कुञ्चिका(SDL_Surface *surface)
{
    सचे (!SDL_SurfaceValid(surface)) {
        पटिनिवत्त false;
    }

    सचे (!(surface->map.info.flags & SDL_COPY_COLORKEY)) {
        पटिनिवत्त false;
    }

    पटिनिवत्त true;
}

bool SDL_Get_Surface_Color_कुञ्चिका(SDL_Surface *surface, Uint32 *कुञ्चिका)
{
    सचे (कुञ्चिका) {
        *कुञ्चिका = 0;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        पटिनिवत्त SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(!(surface->map.info.flags & SDL_COPY_COLORKEY)) {
        पटिनिवत्त SDL_SetError("Surface doesn't have a colorkey");
    }

    सचे (कुञ्चिका) {
        *कुञ्चिका = surface->map.info.colorkey;
    }
    पटिनिवत्त true;
}

/* This is a fairly slow function to switch from colorkey to alpha
   NB: it doesn't handle bpp 1 or 3, because they have no alpha channel */
स्थिर शून्य SDL_ConvertColorkeyToAlpha(SDL_Surface *surface, bool ignore_alpha)
{
    पूर्णाङ्क x, y, bpp;

    सचे (!SDL_SurfaceValid(surface)) {
        पटिनिवत्त;
    }

    सचे (!(surface->map.info.flags & SDL_COPY_COLORKEY) ||
        !SDL_ISPIXELFORMAT_ALPHA(surface->format)) {
        पटिनिवत्त;
    }

    bpp = SDL_BYTESPERPIXEL(surface->format);

    SDL_LockSurface(surface);

    सचे (bpp == 2) {
        Uint16 *row, *spot;
        Uint16 ckey = (Uint16)surface->map.info.colorkey;
        Uint16 mask = (Uint16)(~surface->fmt->Amask);

        // Ignore, or not, alpha in colorkey comparison
        सचे (ignore_alpha) {
            ckey &= mask;
            row = (Uint16 *)surface->pixels;
            अत्थाय (y = surface->h; y--;) {
                spot = row;
                अत्थाय (x = surface->w; x--;) {
                    सचे ((*spot & mask) == ckey) {
                        *spot &= mask;
                    }
                    ++spot;
                }
                row += surface->pitch / 2;
            }
        } अञ्ञथा {
            row = (Uint16 *)surface->pixels;
            अत्थाय (y = surface->h; y--;) {
                spot = row;
                अत्थाय (x = surface->w; x--;) {
                    सचे (*spot == ckey) {
                        *spot &= mask;
                    }
                    ++spot;
                }
                row += surface->pitch / 2;
            }
        }
    } अञ्ञथा सचे (bpp == 4) {
        Uint32 *row, *spot;
        Uint32 ckey = surface->map.info.colorkey;
        Uint32 mask = ~surface->fmt->Amask;

        // Ignore, or not, alpha in colorkey comparison
        सचे (ignore_alpha) {
            ckey &= mask;
            row = (Uint32 *)surface->pixels;
            अत्थाय (y = surface->h; y--;) {
                spot = row;
                अत्थाय (x = surface->w; x--;) {
                    सचे ((*spot & mask) == ckey) {
                        *spot &= mask;
                    }
                    ++spot;
                }
                row += surface->pitch / 4;
            }
        } अञ्ञथा {
            row = (Uint32 *)surface->pixels;
            अत्थाय (y = surface->h; y--;) {
                spot = row;
                अत्थाय (x = surface->w; x--;) {
                    सचे (*spot == ckey) {
                        *spot &= mask;
                    }
                    ++spot;
                }
                row += surface->pitch / 4;
            }
        }
    }

    SDL_UnlockSurface(surface);

    SDL_Set_Surface_Color_कुञ्चिका(surface, false, 0);
    SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
}

bool SDL_SetSurfaceColorMod(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b)
{
    पूर्णाङ्क flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        पटिनिवत्त SDL_InvalidParamError("surface");
    }

    surface->map.info.r = r;
    surface->map.info.g = g;
    surface->map.info.b = b;

    flags = surface->map.info.flags;
    सचे (r != 0xFF || g != 0xFF || b != 0xFF) {
        surface->map.info.flags |= SDL_COPY_MODULATE_COLOR;
    } अञ्ञथा {
        surface->map.info.flags &= ~SDL_COPY_MODULATE_COLOR;
    }
    सचे (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    पटिनिवत्त true;
}

bool SDL_GetSurfaceColorMod(SDL_Surface *surface, Uint8 *r, Uint8 *g, Uint8 *b)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        सचे (r) {
            *r = 255;
        }
        सचे (g) {
            *g = 255;
        }
        सचे (b) {
            *b = 255;
        }
        पटिनिवत्त SDL_InvalidParamError("surface");
    }

    सचे (r) {
        *r = surface->map.info.r;
    }
    सचे (g) {
        *g = surface->map.info.g;
    }
    सचे (b) {
        *b = surface->map.info.b;
    }
    पटिनिवत्त true;
}

bool SDL_SetSurfaceAlphaMod(SDL_Surface *surface, Uint8 alpha)
{
    पूर्णाङ्क flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        पटिनिवत्त SDL_InvalidParamError("surface");
    }

    surface->map.info.a = alpha;

    flags = surface->map.info.flags;
    सचे (alpha != 0xFF) {
        surface->map.info.flags |= SDL_COPY_MODULATE_ALPHA;
    } अञ्ञथा {
        surface->map.info.flags &= ~SDL_COPY_MODULATE_ALPHA;
    }
    सचे (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    पटिनिवत्त true;
}

bool SDL_GetSurfaceAlphaMod(SDL_Surface *surface, Uint8 *alpha)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        सचे (alpha) {
            *alpha = 255;
        }
        पटिनिवत्त SDL_InvalidParamError("surface");
    }

    सचे (alpha) {
        *alpha = surface->map.info.a;
    }
    पटिनिवत्त true;
}

bool SDL_SetSurfaceBlendMode(SDL_Surface *surface, SDL_BlendMode blendMode)
{
    पूर्णाङ्क flags;
    bool result = true;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        पटिनिवत्त SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(blendMode == SDL_BLENDMODE_INVALID) {
        पटिनिवत्त SDL_InvalidParamError("blendMode");
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

    सचे (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }

    पटिनिवत्त result;
}

bool SDL_GetSurfaceBlendMode(SDL_Surface *surface, SDL_BlendMode *blendMode)
{
    सचे (blendMode) {
        *blendMode = SDL_BLENDMODE_INVALID;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        पटिनिवत्त SDL_InvalidParamError("surface");
    }

    सचे (!blendMode) {
        पटिनिवत्त true;
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
    पटिनिवत्त true;
}

bool SDL_SetSurfaceClipRect(SDL_Surface *surface, ध्रुव SDL_Rect *rect)
{
    SDL_Rect full_rect;

    // Don't do anything if there's no surface to act on
    सचे (!SDL_SurfaceValid(surface)) {
        पटिनिवत्त false;
    }

    // Set up the full surface rectangle
    full_rect.x = 0;
    full_rect.y = 0;
    full_rect.w = surface->w;
    full_rect.h = surface->h;

    // Set the clipping rectangle
    सचे (!rect) {
        surface->clip_rect = full_rect;
        पटिनिवत्त true;
    }
    पटिनिवत्त SDL_GetRectIntersection(rect, &full_rect, &surface->clip_rect);
}

bool SDL_GetSurfaceClipRect(SDL_Surface *surface, SDL_Rect *rect)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        सचे (rect) {
            SDL_zerop(rect);
        }
        पटिनिवत्त SDL_InvalidParamError("surface");
    }
    CHECK_PARAM(!rect) {
        पटिनिवत्त SDL_InvalidParamError("rect");
    }
    *rect = surface->clip_rect;
    पटिनिवत्त true;
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
    सचे (!SDL_ValidateMap(src, dst)) {
        पटिनिवत्त false;
    }
    पटिनिवत्त src->map.blit(src, srcrect, dst, dstrect);
}

bool SDL_BlitSurface(SDL_Surface *src, ध्रुव SDL_Rect *srcrect, SDL_Surface *dst, ध्रुव SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src) || (!src->pixels && !SDL_MUSTLOCK(src))) {
        पटिनिवत्त SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst) || (!dst->pixels && !SDL_MUSTLOCK(dst))) {
        पटिनिवत्त SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        पटिनिवत्त SDL_SetError("Surfaces must not be locked during blit");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    सचे (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
    } अञ्ञथा {
        r_dst.x = 0;
        r_dst.y = 0;
    }

    // clip the source rectangle to the source surface
    सचे (srcrect) {
        SDL_Rect tmp;
        सचे (SDL_GetRectIntersection(srcrect, &r_src, &tmp) == false) {
            पटिनिवत्त true;
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
        सचे (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &tmp) == false) {
            पटिनिवत्त true;
        }

        // Shift srcrect, if dstrect has changed
        r_src.x += tmp.x - r_dst.x;
        r_src.y += tmp.y - r_dst.y;
        r_src.w = tmp.w;
        r_src.h = tmp.h;

        // Update dstrect
        r_dst = tmp;
    }

    सचे (r_dst.w <= 0 || r_dst.h <= 0) {
        // No-op.
        पटिनिवत्त true;
    }

    // Switch back to a fast blit if we were previously stretching
    सचे (src->map.info.flags & SDL_COPY_NEAREST) {
        src->map.info.flags &= ~SDL_COPY_NEAREST;
        SDL_InvalidateMap(&src->map);
    }

    पटिनिवत्त SDL_BlitSurfaceUnchecked(src, &r_src, dst, &r_dst);
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
    सचे (scaled) {
        result = SDL_BlitSurface(scaled, रिक्त, dst, dstrect);
        SDL_DestroySurface(scaled);
    } अञ्ञथा {
        result = false;
    }
    src->w = saved_w;
    src->h = saved_h;
    src->pixels = saved_pixels;
    पटिनिवत्त result;
}

bool SDL_BlitSurfaceScaled(SDL_Surface *src, ध्रुव SDL_Rect *srcrect, SDL_Surface *dst, ध्रुव SDL_Rect *dstrect, SDL_ScaleMode scaleMode)
{
    SDL_Rect r_src, r_dst;
    bool result;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src) || (!src->pixels && !SDL_MUSTLOCK(src))) {
        पटिनिवत्त SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst) || (!dst->pixels && !SDL_MUSTLOCK(dst))) {
        पटिनिवत्त SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        पटिनिवत्त SDL_SetError("Surfaces must not be locked during blit");
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
        पटिनिवत्त SDL_InvalidParamError("scaleMode");
    }

    पूर्णाङ्क src_w = srcrect ? srcrect->w : src->w;
    पूर्णाङ्क src_h = srcrect ? srcrect->h : src->h;
    पूर्णाङ्क dst_w = dstrect ? dstrect->w : dst->w;
    पूर्णाङ्क dst_h = dstrect ? dstrect->h : dst->h;
    सचे (src_w == dst_w && src_h == dst_h) {
        // No scaling, defer to regular blit
        पटिनिवत्त SDL_BlitSurface(src, srcrect, dst, dstrect);
    }

    सचे (src->w == 0 || src->h == 0) {
        // Nothing to do
        पटिनिवत्त true;
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    सचे (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
        r_dst.w = dstrect->w;
        r_dst.h = dstrect->h;
    } अञ्ञथा {
        r_dst.x = 0;
        r_dst.y = 0;
        r_dst.w = dst->w;
        r_dst.h = dst->h;
    }

    // clip the source rectangle to the source surface
    सचे (srcrect) {
        SDL_Rect desired, tmp;
        desired.x = srcrect->x;
        desired.y = srcrect->y;
        desired.w = SDL_max(srcrect->w, 1);
        desired.h = SDL_max(srcrect->h, 1);
        सचे (SDL_GetRectIntersection(&desired, &r_src, &tmp) == false) {
            पटिनिवत्त true;
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
    सचे (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &tmp) == false) {
        पटिनिवत्त true;
    }

    सचे (tmp.x != r_dst.x || tmp.y != r_dst.y || tmp.w != r_dst.w || tmp.h != r_dst.h) {
        // Need to do a clipped and scaled blit
        पटिनिवत्त SDL_BlitSurfaceClippedScaled(src, &r_src, dst, &r_dst, scaleMode);
    }

    सचे (SDL_MUSTLOCK(src)) {
        सचे (!SDL_LockSurface(src)) {
            पटिनिवत्त false;
        }
    }
    सचे (SDL_MUSTLOCK(dst)) {
        सचे (!SDL_LockSurface(dst)) {
            सचे (SDL_MUSTLOCK(src)) {
                SDL_UnlockSurface(src);
            }
            पटिनिवत्त false;
        }
    }

    result = SDL_BlitSurfaceUncheckedScaled(src, &r_src, dst, &r_dst, scaleMode);

    सचे (SDL_MUSTLOCK(src)) {
        SDL_UnlockSurface(src);
    }
    सचे (SDL_MUSTLOCK(dst)) {
        SDL_UnlockSurface(dst);
    }
    पटिनिवत्त result;
}

/**
 *  This is a semi-private blit function and it performs low-level surface
 *  scaled blitting only.
 */
bool SDL_BlitSurfaceUncheckedScaled(SDL_Surface *src, ध्रुव SDL_Rect *srcrect, SDL_Surface *dst, ध्रुव SDL_Rect *dstrect, SDL_ScaleMode scaleMode)
{
    स्थिर ध्रुव Uint32 complex_copy_flags = (SDL_COPY_MODULATE_MASK | SDL_COPY_BLEND_MASK | SDL_COPY_COLORKEY);

    सचे (srcrect->w > SDL_MAX_UINT16 || srcrect->h > SDL_MAX_UINT16 ||
        dstrect->w > SDL_MAX_UINT16 || dstrect->h > SDL_MAX_UINT16) {
        पटिनिवत्त SDL_SetError("Size too large for scaling");
    }

    सचे (!(src->map.info.flags & SDL_COPY_NEAREST)) {
        src->map.info.flags |= SDL_COPY_NEAREST;
        SDL_InvalidateMap(&src->map);
    }

    सचे (scaleMode == SDL_SCALEMODE_NEAREST || scaleMode == SDL_SCALEMODE_PIXELART) {
        सचे (!(src->map.info.flags & complex_copy_flags) &&
            src->format == dst->format &&
            (!SDL_ISPIXELFORMAT_INDEXED(src->format) ||
             (SDL_BITSPERPIXEL(src->format) == 8 && SDL_IsSamePalette(src->palette, dst->palette))) &&
            SDL_BYTESPERPIXEL(src->format) <= 4) {
            पटिनिवत्त SDL_StretchSurface(src, srcrect, dst, dstrect, SDL_SCALEMODE_NEAREST);
        } अञ्ञथा सचे (SDL_BITSPERPIXEL(src->format) < 8) {
            // Scaling bitmap not yet supported, convert to RGBA for blit
            bool result = false;
            SDL_Surface *tmp = SDL_ConvertSurface(src, SDL_PIXELFORMAT_ARGB8888);
            सचे (tmp) {
                result = SDL_BlitSurfaceUncheckedScaled(tmp, srcrect, dst, dstrect, SDL_SCALEMODE_NEAREST);
                SDL_DestroySurface(tmp);
            }
            पटिनिवत्त result;
        } अञ्ञथा {
            पटिनिवत्त SDL_BlitSurfaceUnchecked(src, srcrect, dst, dstrect);
        }
    } अञ्ञथा {
        सचे (!(src->map.info.flags & complex_copy_flags) &&
            src->format == dst->format &&
            !SDL_ISPIXELFORMAT_INDEXED(src->format) &&
            SDL_BYTESPERPIXEL(src->format) == 4 &&
            src->format != SDL_PIXELFORMAT_ARGB2101010) {
            // fast path
            पटिनिवत्त SDL_StretchSurface(src, srcrect, dst, dstrect, SDL_SCALEMODE_LINEAR);
        } अञ्ञथा सचे (SDL_BITSPERPIXEL(src->format) < 8) {
            // Scaling bitmap not yet supported, convert to RGBA for blit
            bool result = false;
            SDL_Surface *tmp = SDL_ConvertSurface(src, SDL_PIXELFORMAT_ARGB8888);
            सचे (tmp) {
                result = SDL_BlitSurfaceUncheckedScaled(tmp, srcrect, dst, dstrect, scaleMode);
                SDL_DestroySurface(tmp);
            }
            पटिनिवत्त result;
        } अञ्ञथा {
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
            सचे (SDL_BYTESPERPIXEL(src->format) != 4 || src->format == SDL_PIXELFORMAT_ARGB2101010) {
                SDL_PixelFormat fmt;
                सचे (SDL_BYTESPERPIXEL(dst->format) == 4 && dst->format != SDL_PIXELFORMAT_ARGB2101010 &&
                    (SDL_ISPIXELFORMAT_ALPHA(dst->format) || !is_complex_copy_flags)) {
                    fmt = dst->format;
                } अञ्ञथा {
                    fmt = SDL_PIXELFORMAT_ARGB8888;
                }
                tmp1 = SDL_ConvertSurfaceRect(src, srcrect, fmt);
                सचे (!tmp1) {
                    पटिनिवत्त false;
                }
                src = tmp1;
                srcrect2.x = 0;
                srcrect2.y = 0;
            }

            // Intermediate scaling
            सचे (is_complex_copy_flags || src->format != dst->format) {
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
            } अञ्ञथा {
                result = SDL_StretchSurface(src, &srcrect2, dst, dstrect, SDL_SCALEMODE_LINEAR);
            }

            SDL_DestroySurface(tmp1);
            पटिनिवत्त result;
        }
    }
}

bool SDL_BlitSurfaceTiled(SDL_Surface *src, ध्रुव SDL_Rect *srcrect, SDL_Surface *dst, ध्रुव SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        पटिनिवत्त SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        पटिनिवत्त SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        पटिनिवत्त SDL_SetError("Surfaces must not be locked during blit");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    सचे (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
        r_dst.w = dstrect->w;
        r_dst.h = dstrect->h;
    } अञ्ञथा {
        r_dst.x = 0;
        r_dst.y = 0;
        r_dst.w = dst->w;
        r_dst.h = dst->h;
    }

    // clip the source rectangle to the source surface
    सचे (srcrect) {
        सचे (SDL_GetRectIntersection(srcrect, &r_src, &r_src) == false) {
            पटिनिवत्त true;
        }

        // For tiling we don't adjust the destination rectangle
    }

    // clip the destination rectangle against the clip rectangle
    {
        सचे (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &r_dst) == false) {
            पटिनिवत्त true;
        }

        // For tiling we don't adjust the source rectangle
    }

    // Switch back to a fast blit if we were previously stretching
    सचे (src->map.info.flags & SDL_COPY_NEAREST) {
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
    अत्थाय (पूर्णाङ्क y = 0; y < rows; ++y) {
        curr_dst.x = r_dst.x;
        अत्थाय (पूर्णाङ्क x = 0; x < cols; ++x) {
            सचे (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                पटिनिवत्त false;
            }
            curr_dst.x += curr_dst.w;
        }
        सचे (remaining_w) {
            curr_src.w = remaining_w;
            curr_dst.w = remaining_w;
            सचे (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                पटिनिवत्त false;
            }
            curr_src.w = r_src.w;
            curr_dst.w = r_src.w;
        }
        curr_dst.y += curr_dst.h;
    }
    सचे (remaining_h) {
        curr_src.h = remaining_h;
        curr_dst.h = remaining_h;
        curr_dst.x = r_dst.x;
        अत्थाय (पूर्णाङ्क x = 0; x < cols; ++x) {
            सचे (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                पटिनिवत्त false;
            }
            curr_dst.x += curr_dst.w;
        }
        सचे (remaining_w) {
            curr_src.w = remaining_w;
            curr_dst.w = remaining_w;
            सचे (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                पटिनिवत्त false;
            }
        }
    }
    पटिनिवत्त true;
}

bool SDL_BlitSurfaceTiledWithScale(SDL_Surface *src, ध्रुव SDL_Rect *srcrect, भिन्न scale, SDL_ScaleMode scaleMode, SDL_Surface *dst, ध्रुव SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        पटिनिवत्त SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        पटिनिवत्त SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        पटिनिवत्त SDL_SetError("Surfaces must not be locked during blit");
    }
    CHECK_PARAM(scale < 0.0f) {
        पटिनिवत्त SDL_InvalidParamError("scale");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    सचे (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
        r_dst.w = dstrect->w;
        r_dst.h = dstrect->h;
    } अञ्ञथा {
        r_dst.x = 0;
        r_dst.y = 0;
        r_dst.w = dst->w;
        r_dst.h = dst->h;
    }

    // clip the source rectangle to the source surface
    सचे (srcrect) {
        सचे (SDL_GetRectIntersection(srcrect, &r_src, &r_src) == false) {
            पटिनिवत्त true;
        }

        // For tiling we don't adjust the destination rectangle
    }

    // clip the destination rectangle against the clip rectangle
    {
        सचे (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &r_dst) == false) {
            पटिनिवत्त true;
        }

        // For tiling we don't adjust the source rectangle
    }

    // Switch back to a fast blit if we were previously stretching
    सचे (src->map.info.flags & SDL_COPY_NEAREST) {
        src->map.info.flags &= ~SDL_COPY_NEAREST;
        SDL_InvalidateMap(&src->map);
    }

    पूर्णाङ्क tile_width = (पूर्णाङ्क)SDL_roundf(r_src.w * scale);
    पूर्णाङ्क tile_height = (पूर्णाङ्क)SDL_roundf(r_src.h * scale);
    सचे (tile_width <= 0 || tile_height <= 0) {
        // Nothing to do
        पटिनिवत्त true;
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
    अत्थाय (पूर्णाङ्क y = 0; y < rows; ++y) {
        curr_dst.x = r_dst.x;
        अत्थाय (पूर्णाङ्क x = 0; x < cols; ++x) {
            सचे (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
                पटिनिवत्त false;
            }
            curr_dst.x += curr_dst.w;
        }
        सचे (remaining_dst_w > 0) {
            curr_src.w = remaining_src_w;
            curr_dst.w = remaining_dst_w;
            सचे (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
                पटिनिवत्त false;
            }
            curr_src.w = r_src.w;
            curr_dst.w = tile_width;
        }
        curr_dst.y += curr_dst.h;
    }
    सचे (remaining_dst_h > 0) {
        curr_src.h = remaining_src_h;
        curr_dst.h = remaining_dst_h;
        curr_dst.x = r_dst.x;
        अत्थाय (पूर्णाङ्क x = 0; x < cols; ++x) {
            सचे (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
                पटिनिवत्त false;
            }
            curr_dst.x += curr_dst.w;
        }
        सचे (remaining_dst_w > 0) {
            curr_src.w = remaining_src_w;
            curr_dst.w = remaining_dst_w;
            सचे (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
                पटिनिवत्त false;
            }
        }
    }
    पटिनिवत्त true;
}

bool SDL_BlitSurface9Grid(SDL_Surface *src, ध्रुव SDL_Rect *srcrect, पूर्णाङ्क वामः_width, पूर्णाङ्क दक्षिणः_width, पूर्णाङ्क शिखरम्_height, पूर्णाङ्क bottom_height, भिन्न scale, SDL_ScaleMode scaleMode, SDL_Surface *dst, ध्रुव SDL_Rect *dstrect)
{
    SDL_Rect full_src, full_dst;
    SDL_Rect curr_src, curr_dst;
    पूर्णाङ्क dst_वामः_width;
    पूर्णाङ्क dst_दक्षिणः_width;
    पूर्णाङ्क dst_शिखरम्_height;
    पूर्णाङ्क dst_bottom_height;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        पटिनिवत्त SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        पटिनिवत्त SDL_InvalidParamError("dst");
    }

    सचे (!srcrect) {
        full_src.x = 0;
        full_src.y = 0;
        full_src.w = src->w;
        full_src.h = src->h;
        srcrect = &full_src;
    }

    सचे (!dstrect) {
        full_dst.x = 0;
        full_dst.y = 0;
        full_dst.w = dst->w;
        full_dst.h = dst->h;
        dstrect = &full_dst;
    }

    सचे (scale <= 0.0f || scale == 1.0f) {
        dst_वामः_width = वामः_width;
        dst_दक्षिणः_width = दक्षिणः_width;
        dst_शिखरम्_height = शिखरम्_height;
        dst_bottom_height = bottom_height;
    } अञ्ञथा {
        dst_वामः_width = (पूर्णाङ्क)SDL_roundf(वामः_width * scale);
        dst_दक्षिणः_width = (पूर्णाङ्क)SDL_roundf(दक्षिणः_width * scale);
        dst_शिखरम्_height = (पूर्णाङ्क)SDL_roundf(शिखरम्_height * scale);
        dst_bottom_height = (पूर्णाङ्क)SDL_roundf(bottom_height * scale);
    }

    // Upper-left corner
    curr_src.x = srcrect->x;
    curr_src.y = srcrect->y;
    curr_src.w = वामः_width;
    curr_src.h = शिखरम्_height;
    curr_dst.x = dstrect->x;
    curr_dst.y = dstrect->y;
    curr_dst.w = dst_वामः_width;
    curr_dst.h = dst_शिखरम्_height;
    सचे (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        पटिनिवत्त false;
    }

    // Upper-right corner
    curr_src.x = srcrect->x + srcrect->w - दक्षिणः_width;
    curr_src.w = दक्षिणः_width;
    curr_dst.x = dstrect->x + dstrect->w - dst_दक्षिणः_width;
    curr_dst.w = dst_दक्षिणः_width;
    सचे (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        पटिनिवत्त false;
    }

    // Lower-right corner
    curr_src.y = srcrect->y + srcrect->h - bottom_height;
    curr_dst.y = dstrect->y + dstrect->h - dst_bottom_height;
    curr_dst.h = dst_bottom_height;
    सचे (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        पटिनिवत्त false;
    }

    // Lower-left corner
    curr_src.x = srcrect->x;
    curr_src.w = वामः_width;
    curr_dst.x = dstrect->x;
    curr_dst.w = dst_वामः_width;
    सचे (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        पटिनिवत्त false;
    }

    //वामः
    curr_src.y = srcrect->y + शिखरम्_height;
    curr_src.h = srcrect->h - शिखरम्_height - bottom_height;
    curr_dst.y = dstrect->y + dst_शिखरम्_height;
    curr_dst.h = dstrect->h - dst_शिखरम्_height - dst_bottom_height;
    सचे (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        पटिनिवत्त false;
    }

    //दक्षिणः
    curr_src.x = srcrect->x + srcrect->w - दक्षिणः_width;
    curr_src.w = दक्षिणः_width;
    curr_dst.x = dstrect->x + dstrect->w - dst_दक्षिणः_width;
    curr_dst.w = dst_दक्षिणः_width;
    सचे (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        पटिनिवत्त false;
    }

    //शिखरम्
    curr_src.x = srcrect->x + वामः_width;
    curr_src.y = srcrect->y;
    curr_src.w = srcrect->w - वामः_width - दक्षिणः_width;
    curr_src.h = शिखरम्_height;
    curr_dst.x = dstrect->x + dst_वामः_width;
    curr_dst.y = dstrect->y;
    curr_dst.w = dstrect->w - dst_वामः_width - dst_दक्षिणः_width;
    curr_dst.h = dst_शिखरम्_height;
    सचे (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        पटिनिवत्त false;
    }

    // Bottom
    curr_src.y = srcrect->y + srcrect->h - bottom_height;
    curr_dst.y = dstrect->y + dstrect->h - dst_bottom_height;
    curr_dst.h = dst_bottom_height;
    सचे (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        पटिनिवत्त false;
    }

    // Center
    curr_src.x = srcrect->x + वामः_width;
    curr_src.y = srcrect->y + शिखरम्_height;
    curr_src.w = srcrect->w - वामः_width - दक्षिणः_width;
    curr_src.h = srcrect->h - शिखरम्_height - bottom_height;
    curr_dst.x = dstrect->x + dst_वामः_width;
    curr_dst.y = dstrect->y + dst_शिखरम्_height;
    curr_dst.w = dstrect->w - dst_वामः_width - dst_दक्षिणः_width;
    curr_dst.h = dstrect->h - dst_शिखरम्_height - dst_bottom_height;
    सचे (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        पटिनिवत्त false;
    }

    पटिनिवत्त true;
}

/*
 * Lock a surface to directly access the pixels
 */
bool SDL_LockSurface(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        पटिनिवत्त SDL_InvalidParamError("surface");
    }

    सचे (!surface->locked) {
#ifdef SDL_HAVE_RLE
        // Perform the lock
        सचे (surface->internal_flags & SDL_INTERNAL_SURFACE_RLEACCEL) {
            SDL_UnRLESurface(surface);
        }
#endif
    }

    // Increment the surface lock count, for recursive locks
    ++surface->locked;
    surface->flags |= SDL_SURFACE_LOCKED;
    SDL_UpdateSurfaceLockFlag(surface);

    // Ready to go..
    पटिनिवत्त true;
}

/*
 * Unlock a previously locked surface
 */
शून्य SDL_UnlockSurface(SDL_Surface *surface)
{
    सचे (!SDL_SurfaceValid(surface)) {
        पटिनिवत्त;
    }

    // Only perform an unlock if we are locked
    सचे (!surface->locked || (--surface->locked > 0)) {
        पटिनिवत्त;
    }

    surface->flags &= ~SDL_SURFACE_LOCKED;
    SDL_UpdateSurfaceLockFlag(surface);
}

स्थिर bool SDL_FlipSurfaceHorizontal(SDL_Surface *surface)
{
    bool isstack;
    Uint8 *row, *a, *b, *tmp;
    पूर्णाङ्क i, j, bpp;

    सचे (SDL_BITSPERPIXEL(surface->format) < 8) {
        // We could implement this if needed, but we'd have to flip sets of bits within a byte
        पटिनिवत्त SDL_Unsupported();
    }

    सचे (surface->h <= 0) {
        पटिनिवत्त true;
    }

    सचे (surface->w <= 1) {
        पटिनिवत्त true;
    }

    bpp = SDL_BYTESPERPIXEL(surface->format);
    row = (Uint8 *)surface->pixels;
    tmp = SDL_small_alloc(Uint8, surface->pitch, &isstack);
    सचे (!tmp) {
        पटिनिवत्त false;
    }
    अत्थाय (i = surface->h; i--; ) {
        a = row;
        b = a + (surface->w - 1) * bpp;
        अत्थाय (j = surface->w / 2; j--; ) {
            SDL_memcpy(tmp, a, bpp);
            SDL_memcpy(a, b, bpp);
            SDL_memcpy(b, tmp, bpp);
            a += bpp;
            b -= bpp;
        }
        row += surface->pitch;
    }
    SDL_small_free(tmp, isstack);
    पटिनिवत्त true;
}

स्थिर bool SDL_FlipSurfaceVertical(SDL_Surface *surface)
{
    bool isstack;
    Uint8 *a, *b, *tmp;
    पूर्णाङ्क i;

    सचे (surface->h <= 1) {
        पटिनिवत्त true;
    }

    a = (Uint8 *)surface->pixels;
    b = a + (surface->h - 1) * surface->pitch;
    tmp = SDL_small_alloc(Uint8, surface->pitch, &isstack);
    सचे (!tmp) {
        पटिनिवत्त false;
    }
    अत्थाय (i = surface->h / 2; i--; ) {
        SDL_memcpy(tmp, a, surface->pitch);
        SDL_memcpy(a, b, surface->pitch);
        SDL_memcpy(b, tmp, surface->pitch);
        a += surface->pitch;
        b -= surface->pitch;
    }
    SDL_small_free(tmp, isstack);
    पटिनिवत्त true;
}

bool SDL_FlipSurface(SDL_Surface *surface, SDL_FlipMode flip)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        पटिनिवत्त SDL_InvalidParamError("surface");
    }
    सचे (!surface->pixels) {
        पटिनिवत्त true;
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
    पटिनिवत्त result;
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
    Uint8 palette_ck_मानम् = 0;
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
    सचे (rect) {
        bounds.w = rect->w;
        bounds.h = rect->h;
    } अञ्ञथा {
        rect = &bounds;
    }

    // Check for empty destination palette! (results in empty image)
    सचे (palette) {
        पूर्णाङ्क i;
        अत्थाय (i = 0; i < palette->ncolors; ++i) {
            सचे ((palette->colors[i].r != 0xFF) || (palette->colors[i].g != 0xFF) || (palette->colors[i].b != 0xFF)) {
                भङ्ग;
            }
        }
        सचे (i == palette->ncolors) {
            SDL_SetError("Empty destination palette");
            गच्छ error;
        }
    } अञ्ञथा सचे (SDL_ISPIXELFORMAT_INDEXED(format)) {
        // Create a dither palette for conversion
        temp_palette = SDL_CreatePalette(1 << SDL_BITSPERPIXEL(format));
        सचे (temp_palette) {
            SDL_DitherPalette(temp_palette);
            palette = temp_palette;
        }
    }

    src_colorspace = surface->colorspace;
    src_properties = surface->props;

    // Create a new surface with the desired format
    सचे (surface->pixels || SDL_MUSTLOCK(surface)) {
        convert = SDL_CreateSurfaceUninitialized(rect->w, rect->h, format);
    } अञ्ञथा {
        convert = SDL_CreateSurfaceFrom(rect->w, rect->h, format, रिक्त, 0);
    }
    सचे (!convert) {
        गच्छ error;
    }
    सचे (SDL_ISPIXELFORMAT_INDEXED(format)) {
        SDL_SetSurfacePalette(convert, palette);
    }

    सचे (colorspace == SDL_COLORSPACE_UNKNOWN) {
        colorspace = src_colorspace;
    }
    SDL_SetSurfaceColorspace(convert, colorspace);

    सचे (SDL_ISPIXELFORMAT_FOURCC(format) || SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        सचे (surface->format == SDL_PIXELFORMAT_MJPG && format == SDL_PIXELFORMAT_MJPG) {
            // Just do a straight pixel copy of the JPEG image
            size_t size = (size_t)surface->pitch;
            convert->pixels = SDL_malloc(size);
            सचे (!convert->pixels) {
                गच्छ error;
            }
            convert->flags &= ~SDL_SURFACE_PREALLOCATED;
            convert->pitch = surface->pitch;
            SDL_memcpy(convert->pixels, surface->pixels, size);

        } अञ्ञथा सचे (!SDL_ConvertPixelsAndColorspace(surface->w, surface->h, surface->format, src_colorspace, src_properties, surface->pixels, surface->pitch, convert->format, colorspace, props, convert->pixels, convert->pitch)) {
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
    सचे (surface->palette && SDL_ISPIXELFORMAT_ALPHA(format)) {
        bool set_opaque = false;

        bool is_opaque, has_alpha_channel;
        SDL_DetectPalette(surface->palette, &is_opaque, &has_alpha_channel);

        सचे (is_opaque) {
            सचे (!has_alpha_channel) {
                set_opaque = true;
            }
        }

        // Set opaque and backup palette alpha values
        सचे (set_opaque) {
            पूर्णाङ्क i;
            palette_saved_alpha_ncolors = surface->palette->ncolors;
            सचे (palette_saved_alpha_ncolors > 0) {
                palette_saved_alpha = SDL_राशिः_alloc(Uint8, palette_saved_alpha_ncolors);
                अत्थाय (i = 0; i < palette_saved_alpha_ncolors; i++) {
                    palette_saved_alpha[i] = surface->palette->colors[i].a;
                    surface->palette->colors[i].a = SDL_ALPHA_OPAQUE;
                }
            }
        }
    }

    // Transform colorkey to alpha. for cases where source palette has duplicate values, and colorkey is one of them
    सचे (copy_flags & SDL_COPY_COLORKEY) {
        सचे (surface->palette && !palette) {
            palette_ck_transform = true;
            palette_ck_मानम् = surface->palette->colors[surface->map.info.colorkey].a;
            surface->palette->colors[surface->map.info.colorkey].a = SDL_ALPHA_TRANSPARENT;
        }
    }

    सचे (surface->pixels || SDL_MUSTLOCK(surface)) {
        result = SDL_BlitSurfaceUnchecked(surface, rect, convert, &bounds);
    } अञ्ञथा {
        result = true;
    }

    // Restore colorkey alpha value
    सचे (palette_ck_transform) {
        surface->palette->colors[surface->map.info.colorkey].a = palette_ck_मानम्;
    }

    // Restore palette alpha values
    सचे (palette_saved_alpha) {
        पूर्णाङ्क i;
        अत्थाय (i = 0; i < palette_saved_alpha_ncolors; i++) {
            surface->palette->colors[i].a = palette_saved_alpha[i];
        }
        SDL_राशिः_free(palette_saved_alpha);
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
    सचे (!result) {
        गच्छ error;
    }

    सचे (copy_flags & SDL_COPY_COLORKEY) {
        bool set_colorkey_by_color = false;
        bool convert_colorkey = true;

        सचे (surface->palette) {
            सचे (palette &&
                surface->palette->ncolors <= palette->ncolors &&
                (SDL_memcmp(surface->palette->colors, palette->colors,
                            surface->palette->ncolors * परिमाण(SDL_Color)) == 0)) {
                // The palette is identical, just set the same colorkey
                SDL_Set_Surface_Color_कुञ्चिका(convert, true, surface->map.info.colorkey);
            } अञ्ञथा सचे (!palette) {
                सचे (SDL_ISPIXELFORMAT_ALPHA(format)) {
                    // No need to add the colorkey, transparency is in the alpha channel
                } अञ्ञथा {
                    // Only set the colorkey information
                    set_colorkey_by_color = true;
                    convert_colorkey = false;
                }
            } अञ्ञथा {
                set_colorkey_by_color = true;
            }
        } अञ्ञथा {
            set_colorkey_by_color = true;
        }

        सचे (set_colorkey_by_color) {
            SDL_Surface *tmp;
            SDL_Surface *tmp2;
            पूर्णाङ्क converted_colorkey = 0;

            // Create a dummy surface to get the colorkey converted
            tmp = SDL_CreateSurfaceUninitialized(1, 1, surface->format);
            सचे (!tmp) {
                गच्छ error;
            }

            // Share the palette, if any
            सचे (surface->palette) {
                SDL_SetSurfacePalette(tmp, surface->palette);
            }

            SDL_FillSurfaceRect(tmp, रिक्त, surface->map.info.colorkey);

            tmp->map.info.flags &= ~SDL_COPY_COLORKEY;

            // Conversion of the colorkey
            tmp2 = SDL_ConvertSurfaceAndColorspace(tmp, format, palette, colorspace, props);
            सचे (!tmp2) {
                SDL_DestroySurface(tmp);
                गच्छ error;
            }

            // Get the converted colorkey
            SDL_memcpy(&converted_colorkey, tmp2->pixels, tmp2->fmt->bytes_per_pixel);

            SDL_DestroySurface(tmp);
            SDL_DestroySurface(tmp2);

            // Set the converted colorkey on the new surface
            SDL_Set_Surface_Color_कुञ्चिका(convert, true, converted_colorkey);

            // This is needed when converting for 3D texture upload
            सचे (convert_colorkey) {
                SDL_ConvertColorkeyToAlpha(convert, true);
            }
        }
    }

end:
    सचे (temp_palette) {
        SDL_DestroyPalette(temp_palette);
    }

    SDL_SetSurfaceClipRect(convert, &surface->clip_rect);

    /* Enable alpha blending by default if the new surface has an
     * alpha channel or alpha modulation */
    सचे (SDL_ISPIXELFORMAT_ALPHA(format) ||
        (copy_flags & SDL_COPY_MODULATE_ALPHA)) {
        SDL_SetSurfaceBlendMode(convert, SDL_BLENDMODE_BLEND);
    }
    सचे (copy_flags & SDL_COPY_RLE_DESIRED) {
        SDL_SetSurfaceRLE(convert, true);
    }

    // Copy alternate images
    अत्थाय (पूर्णाङ्क i = 0; i < surface->अङ्कः_images; ++i) {
        सचे (!SDL_AddSurfaceAlternateImage(convert, surface->images[i])) {
            गच्छ error;
        }
    }

    // Copy properties
    सचे (surface->props) {
        सचे (!SDL_CopyProperties(surface->props, SDL_GetSurfaceProperties(convert))) {
            गच्छ error;
        }

        // Make sure the new surface doesn't reference an old SDL2 surface.
        SDL_ClearProperty(SDL_GetSurfaceProperties(convert), "sdl2-compat.surface2");
    }

    // We're ready to go!
    पटिनिवत्त convert;

error:
    सचे (temp_palette) {
        SDL_DestroyPalette(temp_palette);
    }
    सचे (convert) {
        SDL_DestroySurface(convert);
    }
    पटिनिवत्त रिक्त;
}

SDL_Surface *SDL_ConvertSurfaceAndColorspace(SDL_Surface *surface, SDL_PixelFormat format, SDL_Palette *palette, SDL_Colorspace colorspace, SDL_PropertiesID props)
{
    पटिनिवत्त SDL_ConvertSurfaceRectAndColorspace(surface, रिक्त, format, palette, colorspace, props);
}

SDL_Surface *SDL_RotateSurface(SDL_Surface *surface, भिन्न angle)
{
    SDL_Surface *rotated = रिक्त;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        पटिनिवत्त रिक्त;
    }

    SDL_Rect rect_dest;
    द्विगुण cangle, sangle;
    SDL_FPoint center = { surface->w * 0.5f, surface->h * 0.5f };
    SDLgfx_rotozoomSurfaceSizeTrig(surface->w, surface->h, angle, &center, &rect_dest, &cangle, &sangle);

    // This function requires a 32-bit surface or 8-bit surface with a colorkey
    सचे ((SDL_BITSPERPIXEL(surface->format) == 32 && SDL_PIXELLAYOUT(surface->format) == SDL_PACKEDLAYOUT_8888) ||
        (surface->format == SDL_PIXELFORMAT_INDEX8 && SDL_Surface_Has_Color_कुञ्चिका(surface))) {
        rotated = SDLgfx_rotateSurface(surface, angle, 1, 0, 0, &rect_dest, cangle, sangle, &center);
    } अञ्ञथा {
        SDL_Surface *convert = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);
        सचे (convert) {
            SDL_Surface *tmp = SDLgfx_rotateSurface(convert, angle, 1, 0, 0, &rect_dest, cangle, sangle, &center);
            सचे (tmp) {
                rotated = SDL_ConvertSurfaceAndColorspace(tmp, surface->format, surface->palette, surface->colorspace, surface->props);
                SDL_DestroySurface(tmp);
            }
            SDL_DestroySurface(convert);
        }
    }

    सचे (rotated) {
        सचे (SDL_HasProperty(surface->props, SDL_PROP_SURFACE_ROTATION_FLOAT)) {
            ध्रुव भिन्न rotation = (SDL_Get_सङ्ख्या_Property(surface->props, SDL_PROP_SURFACE_ROTATION_FLOAT, 0) - angle);
            SDL_SetFloatProperty(SDL_GetSurfaceProperties(rotated), SDL_PROP_SURFACE_ROTATION_FLOAT, rotation);
        }
    }

    पटिनिवत्त rotated;
}

SDL_Surface *SDL_DuplicateSurface(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        पटिनिवत्त रिक्त;
    }

    पटिनिवत्त SDL_ConvertSurfaceAndColorspace(surface, surface->format, surface->palette, surface->colorspace, surface->props);
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

    सचे (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // We can't directly scale a YUV surface (yet!)
        SDL_Surface *tmp = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        सचे (!tmp) {
            पटिनिवत्त रिक्त;
        }

        SDL_Surface *scaled = SDL_ScaleSurface(tmp, width, height, scaleMode);
        SDL_DestroySurface(tmp);
        सचे (!scaled) {
            पटिनिवत्त रिक्त;
        }

        SDL_Surface *result = SDL_ConvertSurfaceAndColorspace(scaled, surface->format, रिक्त, surface->colorspace, surface->props);
        SDL_DestroySurface(scaled);
        पटिनिवत्त result;
    }

    सचे (SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        // Linear scaling requires conversion to RGBA and then slow pixel color lookup
        scaleMode = SDL_SCALEMODE_NEAREST;
    }

    // Create a new surface with the desired size
    सचे (surface->pixels || SDL_MUSTLOCK(surface)) {
        convert = SDL_CreateSurfaceUninitialized(width, height, surface->format);
    } अञ्ञथा {
        convert = SDL_CreateSurfaceFrom(width, height, surface->format, रिक्त, 0);
    }
    सचे (!convert) {
        गच्छ error;
    }
    SDL_SetSurfacePalette(convert, surface->palette);
    SDL_SetSurfaceColorspace(convert, surface->colorspace);
    SDL_SetSurfaceRLE(convert, SDL_SurfaceHasRLE(surface));

    सचे (surface->pixels || SDL_MUSTLOCK(surface)) {
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
    } अञ्ञथा {
        rc = true;
    }

    // SDL_BlitSurfaceScaled failed, and so the conversion
    सचे (!rc) {
        गच्छ error;
    }

    // We're ready to go!
    पटिनिवत्त convert;

error:
    सचे (convert) {
        SDL_DestroySurface(convert);
    }
    पटिनिवत्त रिक्त;
}

SDL_Surface *SDL_ConvertSurfaceRect(SDL_Surface *surface, ध्रुव SDL_Rect *rect, SDL_PixelFormat format)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        पटिनिवत्त रिक्त;
    }

    पटिनिवत्त SDL_ConvertSurfaceRectAndColorspace(surface, rect, format, रिक्त, SDL_GetDefaultColorspaceForFormat(format), surface->props);
}

SDL_Surface *SDL_ConvertSurface(SDL_Surface *surface, SDL_PixelFormat format)
{
    पटिनिवत्त SDL_ConvertSurfaceRect(surface, रिक्त, format);
}

SDL_Surface *SDL_DuplicatePixels(पूर्णाङ्क width, पूर्णाङ्क height, SDL_PixelFormat format, SDL_Colorspace colorspace, शून्य *pixels, पूर्णाङ्क pitch)
{
    SDL_Surface *surface;
    सचे (pixels) {
        surface = SDL_CreateSurfaceUninitialized(width, height, format);
    } अञ्ञथा {
        surface = SDL_CreateSurfaceFrom(width, height, format, रिक्त, 0);
    }
    सचे (!surface) {
        पटिनिवत्त रिक्त;
    }
    SDL_SetSurfaceColorspace(surface, colorspace);

    सचे (surface->pixels) {
        पूर्णाङ्क length = width * SDL_BYTESPERPIXEL(format);
        Uint8 *src = (Uint8 *)pixels;
        Uint8 *dst = (Uint8 *)surface->pixels;
        पूर्णाङ्क rows = height;
        याव (rows--) {
            SDL_memcpy(dst, src, length);
            dst += surface->pitch;
            src += pitch;
        }
    }
    पटिनिवत्त surface;
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
        पटिनिवत्त SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!src_pitch) {
        पटिनिवत्त SDL_InvalidParamError("src_pitch");
    }
    CHECK_PARAM(!dst) {
        पटिनिवत्त SDL_InvalidParamError("dst");
    }
    CHECK_PARAM(!dst_pitch) {
        पटिनिवत्त SDL_InvalidParamError("dst_pitch");
    }

    सचे (src_colorspace == SDL_COLORSPACE_UNKNOWN) {
        src_colorspace = SDL_GetDefaultColorspaceForFormat(src_format);
    }
    सचे (dst_colorspace == SDL_COLORSPACE_UNKNOWN) {
        dst_colorspace = SDL_GetDefaultColorspaceForFormat(dst_format);
    }

    सचे (src_format == SDL_PIXELFORMAT_MJPG) {
        पटिनिवत्त SDL_ConvertPixels_STB(width, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    }

#ifdef SDL_HAVE_YUV
    सचे (SDL_ISPIXELFORMAT_FOURCC(src_format) && SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        पटिनिवत्त SDL_ConvertPixels_YUV_to_YUV(width, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } अञ्ञथा सचे (SDL_ISPIXELFORMAT_FOURCC(src_format)) {
        पटिनिवत्त SDL_ConvertPixels_YUV_to_RGB(width, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } अञ्ञथा सचे (SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        पटिनिवत्त SDL_ConvertPixels_RGB_to_YUV(width, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    }
#अञ्ञथा
    सचे (SDL_ISPIXELFORMAT_FOURCC(src_format) || SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        पटिनिवत्त SDL_SetError("SDL not built with YUV support");
    }
#endif

    // Fast path for same format copy
    सचे (src_format == dst_format && src_colorspace == dst_colorspace) {
        सचे (src_pitch == dst_pitch) {
            SDL_memcpy(dst, src, height * src_pitch);
        } अञ्ञथा {
            पूर्णाङ्क i;
            ध्रुव पूर्णाङ्क bpp = SDL_BYTESPERPIXEL(src_format);
            width *= bpp;
            अत्थाय (i = height; i--;) {
                SDL_memcpy(dst, src, width);
                src = (ध्रुव Uint8 *)src + src_pitch;
                dst = (Uint8 *)dst + dst_pitch;
            }
        }
        पटिनिवत्त true;
    }

    सचे (!SDL_InitializeSurface(&src_surface, width, height, src_format, src_colorspace, src_properties, nonconst_src, src_pitch, true)) {
        पटिनिवत्त false;
    }
    SDL_SetSurfaceBlendMode(&src_surface, SDL_BLENDMODE_NONE);

    सचे (!SDL_InitializeSurface(&dst_surface, width, height, dst_format, dst_colorspace, dst_properties, dst, dst_pitch, true)) {
        पटिनिवत्त false;
    }

    // Set up the rect and go!
    rect.x = 0;
    rect.y = 0;
    rect.w = width;
    rect.h = height;
    result = SDL_BlitSurfaceUnchecked(&src_surface, &rect, &dst_surface, &rect);

    SDL_DestroySurface(&src_surface);
    SDL_DestroySurface(&dst_surface);

    पटिनिवत्त result;
}

bool SDL_ConvertPixels(पूर्णाङ्क width, पूर्णाङ्क height, SDL_PixelFormat src_format, ध्रुव शून्य *src, पूर्णाङ्क src_pitch, SDL_PixelFormat dst_format, शून्य *dst, पूर्णाङ्क dst_pitch)
{
    पटिनिवत्त SDL_ConvertPixelsAndColorspace(width, height,
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

    याव (height--) {
        ध्रुव Uint32 *src_px = (ध्रुव Uint32 *)src;
        Uint32 *dst_px = (Uint32 *)dst;
        अत्थाय (c = width; c; --c) {
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

    याव (height--) {
        ध्रुव Uint32 *src_px = (ध्रुव Uint32 *)src;
        Uint32 *dst_px = (Uint32 *)dst;
        अत्थाय (c = width; c; --c) {
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

    याव (height--) {
        ध्रुव भिन्न *src_px = (ध्रुव भिन्न *)src;
        भिन्न *dst_px = (भिन्न *)dst;
        अत्थाय (c = width; c; --c) {
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
        पटिनिवत्त SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!src_pitch) {
        पटिनिवत्त SDL_InvalidParamError("src_pitch");
    }
    CHECK_PARAM(!dst) {
        पटिनिवत्त SDL_InvalidParamError("dst");
    }
    CHECK_PARAM(!dst_pitch) {
        पटिनिवत्त SDL_InvalidParamError("dst_pitch");
    }

    // Use a high precision format if we're converting to linear colorspace or using high precision pixel formats
    सचे (linear ||
        SDL_ISPIXELFORMAT_10BIT(src_format) || SDL_BITSPERPIXEL(src_format) > 32 ||
        SDL_ISPIXELFORMAT_10BIT(dst_format) || SDL_BITSPERPIXEL(dst_format) > 32) {
        सचे (src_format == SDL_PIXELFORMAT_ARGB128_FLOAT ||
            src_format == SDL_PIXELFORMAT_ABGR128_FLOAT) {
            format = src_format;
        } अञ्ञथा {
            format = SDL_PIXELFORMAT_ARGB128_FLOAT;
        }
    } अञ्ञथा {
        सचे (src_format == SDL_PIXELFORMAT_ARGB8888 ||
            src_format == SDL_PIXELFORMAT_ABGR8888 ||
            src_format == SDL_PIXELFORMAT_RGBA8888 ||
            src_format == SDL_PIXELFORMAT_BGRA8888) {
            format = src_format;
        } अञ्ञथा {
            format = SDL_PIXELFORMAT_ARGB8888;
        }
    }
    सचे (linear) {
        colorspace = SDL_COLORSPACE_SRGB_LINEAR;
    } अञ्ञथा {
        colorspace = SDL_COLORSPACE_SRGB;
    }

    सचे (src_format != format || src_colorspace != colorspace) {
        convert = SDL_CreateSurfaceUninitialized(width, height, format);
        सचे (!convert) {
            गच्छ done;
        }
        सचे (!SDL_ConvertPixelsAndColorspace(width, height, src_format, src_colorspace, src_properties, src, src_pitch, format, colorspace, 0, convert->pixels, convert->pitch)) {
            गच्छ done;
        }

        src = convert->pixels;
        src_pitch = convert->pitch;
        dst = convert->pixels;
        dst_pitch = convert->pitch;

    } अञ्ञथा सचे (dst_format != format || dst_colorspace != colorspace) {
        convert = SDL_CreateSurfaceUninitialized(width, height, format);
        सचे (!convert) {
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

    सचे (dst != final_dst) {
        सचे (!SDL_ConvertPixelsAndColorspace(width, height, format, colorspace, 0, convert->pixels, convert->pitch, dst_format, dst_colorspace, dst_properties, final_dst, final_dst_pitch)) {
            गच्छ done;
        }
    }
    result = true;

done:
    सचे (convert) {
        SDL_DestroySurface(convert);
    }
    पटिनिवत्त result;
}

bool SDL_PremultiplyAlpha(पूर्णाङ्क width, पूर्णाङ्क height,
                         SDL_PixelFormat src_format, ध्रुव शून्य *src, पूर्णाङ्क src_pitch,
                         SDL_PixelFormat dst_format, शून्य *dst, पूर्णाङ्क dst_pitch, bool linear)
{
    SDL_Colorspace src_colorspace = SDL_GetDefaultColorspaceForFormat(src_format);
    SDL_Colorspace dst_colorspace = SDL_GetDefaultColorspaceForFormat(dst_format);

    पटिनिवत्त SDL_PremultiplyAlphaPixelsAndColorspace(width, height, src_format, src_colorspace, 0, src, src_pitch, dst_format, dst_colorspace, 0, dst, dst_pitch, linear);
}

bool SDL_PremultiplySurfaceAlpha(SDL_Surface *surface, bool linear)
{
    SDL_Colorspace colorspace;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        पटिनिवत्त SDL_InvalidParamError("surface");
    }

    colorspace = surface->colorspace;

    पटिनिवत्त SDL_PremultiplyAlphaPixelsAndColorspace(surface->w, surface->h, surface->format, colorspace, surface->props, surface->pixels, surface->pitch, surface->format, colorspace, surface->props, surface->pixels, surface->pitch, linear);
}

bool SDL_ClearSurface(SDL_Surface *surface, भिन्न r, भिन्न g, भिन्न b, भिन्न a)
{
    SDL_Rect clip_rect;
    bool result = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        पटिनिवत्त SDL_InvalidParamError("surface");
    }

    SDL_GetSurfaceClipRect(surface, &clip_rect);
    SDL_SetSurfaceClipRect(surface, रिक्त);

    सचे (!SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_BYTESPERPIXEL(surface->format) <= परिमाण(Uint32)) {
        Uint32 color;

        color = SDL_MapSurfaceRGBA(surface,
                    (Uint8)SDL_roundf(SDL_clamp(r, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(g, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(b, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(a, 0.0f, 1.0f) * 255.0f));
        result = SDL_FillSurfaceRect(surface, रिक्त, color);
    } अञ्ञथा सचे (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // We can't directly set an RGB value on a YUV surface
        SDL_Surface *tmp = SDL_CreateSurfaceUninitialized(surface->w, surface->h, SDL_PIXELFORMAT_ARGB8888);
        सचे (!tmp) {
            गच्छ done;
        }

        सचे (SDL_ClearSurface(tmp, r, g, b, a)) {
            result = SDL_ConvertPixelsAndColorspace(surface->w, surface->h, tmp->format, tmp->colorspace, tmp->props, tmp->pixels, tmp->pitch, surface->format, surface->colorspace, surface->props, surface->pixels, surface->pitch);
        }
        SDL_DestroySurface(tmp);
    } अञ्ञथा {
        // Take advantage of blit color conversion
        SDL_Surface *tmp = SDL_CreateSurfaceUninitialized(1, 1, SDL_PIXELFORMAT_RGBA128_FLOAT);
        सचे (!tmp) {
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

    पटिनिवत्त result;
}

Uint32 SDL_MapSurfaceRGB(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b)
{
    पटिनिवत्त SDL_MapSurfaceRGBA(surface, r, g, b, SDL_ALPHA_OPAQUE);
}

Uint32 SDL_MapSurfaceRGBA(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        पटिनिवत्त true;
    }
    पटिनिवत्त SDL_MapRGBA(surface->fmt, surface->palette, r, g, b, a);
}

// This function Copyright 2023 Collabora Ltd., contributed to SDL under the ZLib license
bool SDL_ReadSurfacePixel(SDL_Surface *surface, पूर्णाङ्क x, पूर्णाङ्क y, Uint8 *r, Uint8 *g, Uint8 *b, Uint8 *a)
{
    Uint32 pixel = 0;
    size_t bytes_per_pixel;
    Uint8 unused;
    Uint8 *p;
    bool result = false;

    सचे (r) {
        *r = 0;
    } अञ्ञथा {
        r = &unused;
    }

    सचे (g) {
        *g = 0;
    } अञ्ञथा {
        g = &unused;
    }

    सचे (b) {
        *b = 0;
    } अञ्ञथा {
        b = &unused;
    }

    सचे (a) {
        *a = 0;
    } अञ्ञथा {
        a = &unused;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        पटिनिवत्त SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        पटिनिवत्त SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        पटिनिवत्त SDL_InvalidParamError("y");
    }

    bytes_per_pixel = SDL_BYTESPERPIXEL(surface->format);

    सचे (SDL_MUSTLOCK(surface)) {
        सचे (!SDL_LockSurface(surface)) {
            पटिनिवत्त false;
        }
    }

    p = (Uint8 *)surface->pixels + y * surface->pitch + x * bytes_per_pixel;

    सचे (bytes_per_pixel <= परिमाण(pixel) &&
        !SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_COLORSPACEPRIMARIES(surface->colorspace) == SDL_COLOR_PRIMARIES_BT709) {
        /* Fill the appropriate number of least-significant bytes of pixel,
         * leaving the most-significant bytes set to zero */
#सचे SDL_BYTEORDER == SDL_BIG_ENDIAN
        SDL_memcpy(((Uint8 *)&pixel) + (परिमाण(pixel) - bytes_per_pixel), p, bytes_per_pixel);
#अञ्ञथा
        SDL_memcpy(&pixel, p, bytes_per_pixel);
#endif
        SDL_GetRGBA(pixel, surface->fmt, surface->palette, r, g, b, a);
        result = true;
    } अञ्ञथा सचे (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // FIXME: We need code to extract a single macroblock from a YUV surface
        SDL_Surface *converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        सचे (converted) {
            result = SDL_ReadSurfacePixel(converted, x, y, r, g, b, a);
            SDL_DestroySurface(converted);
        }
    } अञ्ञथा {
        // This is really slow, but it gets the job done
        Uint8 rgba[4];

        सचे (SDL_ConvertPixelsAndColorspace(1, 1, surface->format, surface->colorspace, surface->props, p, surface->pitch, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, rgba, परिमाण(rgba))) {
            *r = rgba[0];
            *g = rgba[1];
            *b = rgba[2];
            *a = rgba[3];
            result = true;
        }
    }

    सचे (SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }
    पटिनिवत्त result;
}

bool SDL_ReadSurfacePixelFloat(SDL_Surface *surface, पूर्णाङ्क x, पूर्णाङ्क y, भिन्न *r, भिन्न *g, भिन्न *b, भिन्न *a)
{
    भिन्न unused;
    bool result = false;

    सचे (r) {
        *r = 0.0f;
    } अञ्ञथा {
        r = &unused;
    }

    सचे (g) {
        *g = 0.0f;
    } अञ्ञथा {
        g = &unused;
    }

    सचे (b) {
        *b = 0.0f;
    } अञ्ञथा {
        b = &unused;
    }

    सचे (a) {
        *a = 0.0f;
    } अञ्ञथा {
        a = &unused;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        पटिनिवत्त SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        पटिनिवत्त SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        पटिनिवत्त SDL_InvalidParamError("y");
    }

    सचे (SDL_BYTESPERPIXEL(surface->format) <= परिमाण(Uint32) &&
        !SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_COLORSPACEPRIMARIES(surface->colorspace) == SDL_COLOR_PRIMARIES_BT709) {
        Uint8 r8, g8, b8, a8;

        सचे (SDL_ReadSurfacePixel(surface, x, y, &r8, &g8, &b8, &a8)) {
            *r = (भिन्न)r8 / 255.0f;
            *g = (भिन्न)g8 / 255.0f;
            *b = (भिन्न)b8 / 255.0f;
            *a = (भिन्न)a8 / 255.0f;
            result = true;
        }
    } अञ्ञथा सचे (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // FIXME: We need code to extract a single macroblock from a YUV surface
        SDL_Surface *converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        सचे (converted) {
            result = SDL_ReadSurfacePixelFloat(converted, x, y, r, g, b, a);
            SDL_DestroySurface(converted);
        }
    } अञ्ञथा {
        // This is really slow, but it gets the job done
        भिन्न rgba[4];
        Uint8 *p;

        सचे (SDL_MUSTLOCK(surface)) {
            सचे (!SDL_LockSurface(surface)) {
                पटिनिवत्त false;
            }
        }

        p = (Uint8 *)surface->pixels + y * surface->pitch + x * SDL_BYTESPERPIXEL(surface->format);

        सचे (surface->format == SDL_PIXELFORMAT_RGBA128_FLOAT) {
            SDL_memcpy(rgba, p, परिमाण(rgba));
            result = true;
        } अञ्ञथा {
            SDL_Colorspace src_colorspace = surface->colorspace;
            SDL_Colorspace dst_colorspace = (src_colorspace == SDL_COLORSPACE_SRGB_LINEAR ? SDL_COLORSPACE_SRGB_LINEAR : SDL_COLORSPACE_SRGB);

            सचे (SDL_ConvertPixelsAndColorspace(1, 1, surface->format, src_colorspace, surface->props, p, surface->pitch, SDL_PIXELFORMAT_RGBA128_FLOAT, dst_colorspace, 0, rgba, परिमाण(rgba))) {
                result = true;
            }
        }

        सचे (result) {
            *r = rgba[0];
            *g = rgba[1];
            *b = rgba[2];
            *a = rgba[3];
        }

        सचे (SDL_MUSTLOCK(surface)) {
            SDL_UnlockSurface(surface);
        }
    }
    पटिनिवत्त result;
}

bool SDL_WriteSurfacePixel(SDL_Surface *surface, पूर्णाङ्क x, पूर्णाङ्क y, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    Uint32 pixel = 0;
    size_t bytes_per_pixel;
    Uint8 *p;
    bool result = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        पटिनिवत्त SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        पटिनिवत्त SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        पटिनिवत्त SDL_InvalidParamError("y");
    }

    bytes_per_pixel = SDL_BYTESPERPIXEL(surface->format);

    सचे (SDL_MUSTLOCK(surface)) {
        सचे (!SDL_LockSurface(surface)) {
            पटिनिवत्त false;
        }
    }

    p = (Uint8 *)surface->pixels + y * surface->pitch + x * bytes_per_pixel;

    सचे (bytes_per_pixel <= परिमाण(pixel) && !SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        pixel = SDL_MapRGBA(surface->fmt, surface->palette, r, g, b, a);
#सचे SDL_BYTEORDER == SDL_BIG_ENDIAN
        SDL_memcpy(p, ((Uint8 *)&pixel) + (परिमाण(pixel) - bytes_per_pixel), bytes_per_pixel);
#अञ्ञथा
        SDL_memcpy(p, &pixel, bytes_per_pixel);
#endif
        result = true;
    } अञ्ञथा सचे (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        result = SDL_Unsupported();
    } अञ्ञथा {
        // This is really slow, but it gets the job done
        Uint8 rgba[4];

        rgba[0] = r;
        rgba[1] = g;
        rgba[2] = b;
        rgba[3] = a;
        result = SDL_ConvertPixelsAndColorspace(1, 1, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, rgba, परिमाण(rgba), surface->format, surface->colorspace, surface->props, p, surface->pitch);
    }

    सचे (SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }
    पटिनिवत्त result;
}

bool SDL_WriteSurfacePixelFloat(SDL_Surface *surface, पूर्णाङ्क x, पूर्णाङ्क y, भिन्न r, भिन्न g, भिन्न b, भिन्न a)
{
    bool result = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        पटिनिवत्त SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        पटिनिवत्त SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        पटिनिवत्त SDL_InvalidParamError("y");
    }

    सचे (SDL_BYTESPERPIXEL(surface->format) <= परिमाण(Uint32) && !SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        Uint8 r8, g8, b8, a8;

        r8 = (Uint8)SDL_round(SDL_clamp(r, 0.0f, 1.0f) * 255.0f);
        g8 = (Uint8)SDL_round(SDL_clamp(g, 0.0f, 1.0f) * 255.0f);
        b8 = (Uint8)SDL_round(SDL_clamp(b, 0.0f, 1.0f) * 255.0f);
        a8 = (Uint8)SDL_round(SDL_clamp(a, 0.0f, 1.0f) * 255.0f);
        सचे (SDL_WriteSurfacePixel(surface, x, y, r8, g8, b8, a8)) {
            result = true;
        }
    } अञ्ञथा सचे (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        result = SDL_Unsupported();
    } अञ्ञथा {
        // This is really slow, but it gets the job done
        भिन्न rgba[4];
        Uint8 *p;

        सचे (SDL_MUSTLOCK(surface)) {
            सचे (!SDL_LockSurface(surface)) {
                पटिनिवत्त false;
            }
        }

        p = (Uint8 *)surface->pixels + y * surface->pitch + x * SDL_BYTESPERPIXEL(surface->format);

        rgba[0] = r;
        rgba[1] = g;
        rgba[2] = b;
        rgba[3] = a;

        सचे (surface->format == SDL_PIXELFORMAT_RGBA128_FLOAT) {
            SDL_memcpy(p, rgba, परिमाण(rgba));
            result = true;
        } अञ्ञथा {
            SDL_Colorspace dst_colorspace = surface->colorspace;
            SDL_Colorspace src_colorspace = (dst_colorspace == SDL_COLORSPACE_SRGB_LINEAR ? SDL_COLORSPACE_SRGB_LINEAR : SDL_COLORSPACE_SRGB);

            result = SDL_ConvertPixelsAndColorspace(1, 1, SDL_PIXELFORMAT_RGBA128_FLOAT, src_colorspace, 0, rgba, परिमाण(rgba), surface->format, dst_colorspace, surface->props, p, surface->pitch);
        }

        सचे (SDL_MUSTLOCK(surface)) {
            SDL_UnlockSurface(surface);
        }
    }
    पटिनिवत्त result;
}

/*
 * Free a surface created by the above function.
 */
शून्य SDL_DestroySurface(SDL_Surface *surface)
{
    सचे (!SDL_SurfaceValid(surface)) {
        पटिनिवत्त;
    }
    सचे (surface->internal_flags & SDL_INTERNAL_SURFACE_DONTFREE) {
        पटिनिवत्त;
    }
    सचे (--surface->refcount > 0) {
        पटिनिवत्त;
    }

    SDL_RemoveSurfaceAlternateImages(surface);

    SDL_DestroyProperties(surface->props);

    SDL_InvalidateMap(&surface->map);

    याव (surface->locked > 0) {
        SDL_UnlockSurface(surface);
    }
#ifdef SDL_HAVE_RLE
    सचे (surface->internal_flags & SDL_INTERNAL_SURFACE_RLEACCEL) {
        SDL_UnRLESurface(surface);
    }
#endif
    SDL_SetSurfacePalette(surface, रिक्त);

    सचे (surface->flags & SDL_SURFACE_PREALLOCATED) {
        // Don't free
    } अञ्ञथा सचे (surface->flags & SDL_SURFACE_SIMD_ALIGNED) {
        // Free aligned
        SDL_aligned_free(surface->pixels);
    } अञ्ञथा {
        // Normal
        SDL_free(surface->pixels);
    }

    surface->reserved = रिक्त;

    सचे (!(surface->internal_flags & SDL_INTERNAL_SURFACE_राशिः)) {
        SDL_free(surface);
    }
}

SDL_Surface *SDL_LoadSurface_IO(SDL_IOStream *src, bool closeio)
{
    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        पटिनिवत्त रिक्त;
    }

    सचे (SDL_IsBMP(src)) {
        पटिनिवत्त SDL_LoadBMP_IO(src, closeio);
    } अञ्ञथा सचे (SDL_IsPNG(src)) {
        पटिनिवत्त SDL_LoadPNG_IO(src, closeio);
    } अञ्ञथा सचे (SDL_IsJPG(src)) {
        पटिनिवत्त SDL_LoadJPG_IO(src, closeio);
    } अञ्ञथा {
        सचे (closeio) {
            SDL_CloseIO(src);
        }
        SDL_SetError("Unsupported image format");
        पटिनिवत्त रिक्त;
    }
}

SDL_Surface *SDL_LoadSurface(ध्रुव वर्ण *file)
{
    SDL_IOStream *stream = SDL_IOFromFile(file, "rb");
    सचे (!stream) {
        पटिनिवत्त रिक्त;
    }

    पटिनिवत्त SDL_LoadSurface_IO(stream, true);
}
