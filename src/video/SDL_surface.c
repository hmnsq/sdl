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
#அந்தர்பாவ "SDL_internal.h"

#அந்தர்பாவ "SDL_sysvideo.h"
#அந்தர்பாவ "SDL_video_c.h"
#அந்தர்பாவ "SDL_RLEaccel_c.h"
#அந்தர்பாவ "SDL_pixels_c.h"
#அந்தர்பாவ "SDL_rotate.h"
#அந்தர்பாவ "SDL_stb_c.h"
#அந்தர்பாவ "SDL_yuv_c.h"
#அந்தர்பாவ "../render/SDL_sysrender.h"

#அந்தர்பாவ "SDL_surface_c.h"


// Check to make sure we can safely check multiplication of surface w and pitch and it won't overflow size_t
SDL_COMPILE_TIME_ASSERT(surface_size_assumptions,
                        அளவு(முழு) == அளவு(Sint32) && அளவு(size_t) >= அளவு(Sint32));

SDL_COMPILE_TIME_ASSERT(can_indicate_overflow, SDL_SIZE_MAX > SDL_MAX_SINT32);

// Magic!
நிலையான எழுத்து SDL_surface_magic;

// Public routines

bool SDL_SurfaceValid(SDL_Surface *surface)
{
    திரும்பு (surface && surface->reserved == &SDL_surface_magic);
}

வெறுமை SDL_UpdateSurfaceLockFlag(SDL_Surface *surface)
{
    // We need to mark the surface as needing unlock while locked
    எனில் ((surface->flags & SDL_SURFACE_LOCKED) ||
        (surface->internal_flags & SDL_INTERNAL_SURFACE_RLEACCEL)) {
        surface->flags |= SDL_SURFACE_LOCK_NEEDED;
    } இல்லையெனில் {
        surface->flags &= ~SDL_SURFACE_LOCK_NEEDED;
    }
}

/*
 * Calculate the pad-aligned scanline width of a surface.
 *
 * for FOURCC, use SDL_CalculateYUVSize()
 */
நிலையான bool SDL_CalculateRGBSize(Uint32 format, size_t width, size_t height, size_t *size, size_t *pitch, bool minimal)
{
    எனில் (SDL_BITSPERPIXEL(format) >= 8) {
        எனில் (!SDL_size_mul_check_overflow(width, SDL_BYTESPERPIXEL(format), pitch)) {
            திரும்பு SDL_SetError("width * bpp would overflow");
        }
    } இல்லையெனில் {
        எனில் (!SDL_size_mul_check_overflow(width, SDL_BITSPERPIXEL(format), pitch)) {
            திரும்பு SDL_SetError("width * bpp would overflow");
        }
        எனில் (!SDL_size_add_check_overflow(*pitch, 7, pitch)) {
            திரும்பு SDL_SetError("aligning pitch would overflow");
        }
        *pitch /= 8;
    }
    எனில் (!minimal) {
        // 4-byte aligning for speed
        எனில் (!SDL_size_add_check_overflow(*pitch, 3, pitch)) {
            திரும்பு SDL_SetError("aligning pitch would overflow");
        }
        *pitch &= ~3;
    }

    எனில் (!SDL_size_mul_check_overflow(height, *pitch, size)) {
        திரும்பு SDL_SetError("height * pitch would overflow");
    }

    திரும்பு true;
}

bool SDL_CalculateSurfaceSize(SDL_PixelFormat format, முழு width, முழு height, size_t *size, size_t *pitch, bool minimalPitch)
{
    size_t p = 0, sz = 0;

    எனில் (size) {
        *size = 0;
    }

    எனில் (pitch) {
        *pitch = 0;
    }

    எனில் (SDL_ISPIXELFORMAT_FOURCC(format)) {
        எனில் (format == SDL_PIXELFORMAT_MJPG) {
            // We don't know in advance what it will be, we'll figure it out later.
            திரும்பு true;
        }

        எனில் (!SDL_CalculateYUVSize(format, width, height, &sz, &p)) {
            // Overflow...
            திரும்பு false;
        }
    } இல்லையெனில் {
        எனில் (!SDL_CalculateRGBSize(format, width, height, &sz, &p, minimalPitch)) {
            // Overflow...
            திரும்பு false;
        }
    }

    எனில் (size) {
        *size = sz;
    }

    எனில் (pitch) {
        *pitch = p;
    }

    திரும்பு true;
}

நிலையான bool SDL_InitializeSurface(SDL_Surface *surface, முழு width, முழு height, SDL_PixelFormat format, SDL_Colorspace colorspace, SDL_PropertiesID props, வெறுமை *pixels, முழு pitch, bool onstack)
{
    SDL_zerop(surface);

    surface->flags = SDL_SURFACE_PREALLOCATED;
    surface->format = format;
    surface->w = width;
    surface->h = height;
    surface->pixels = pixels;
    surface->pitch = pitch;
    surface->reserved = &SDL_surface_magic;

    எனில் (onstack) {
        surface->internal_flags |= SDL_INTERNAL_SURFACE_அடுக்கு;
    }

    surface->fmt = SDL_GetPixelFormatDetails(format);
    எனில் (!surface->fmt) {
        SDL_DestroySurface(surface);
        திரும்பு false;
    }

    // Initialize the clip rect
    surface->clip_rect.w = width;
    surface->clip_rect.h = height;

    // Allocate an empty mapping
    surface->map.info.r = 0xFF;
    surface->map.info.g = 0xFF;
    surface->map.info.b = 0xFF;
    surface->map.info.a = 0xFF;

    எனில் (colorspace == SDL_COLORSPACE_UNKNOWN) {
        surface->colorspace = SDL_GetDefaultColorspaceForFormat(format);
    } இல்லையெனில் {
        surface->colorspace = colorspace;
    }

    எனில் (props) {
        எனில் (!SDL_CopyProperties(props, SDL_GetSurfaceProperties(surface))) {
            SDL_DestroySurface(surface);
            திரும்பு false;
        }
    }

    // By default surfaces with an alpha mask are set up for blending
    எனில் (SDL_ISPIXELFORMAT_ALPHA(surface->format)) {
        SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
    }

    // The surface is ready to go
    surface->refcount = 1;
    திரும்பு true;
}

/*
 * Create an empty surface of the appropriate depth using the given format
 */
நிலையான SDL_Surface *SDL_CreateSurfaceInternal(முழு width, முழு height, SDL_PixelFormat format, bool clear_surface)
{
    size_t pitch, size;
    SDL_Surface *surface;

    CHECK_PARAM(width < 0) {
        SDL_InvalidParamError("width");
        திரும்பு வெற்று;
    }

    CHECK_PARAM(height < 0) {
        SDL_InvalidParamError("height");
        திரும்பு வெற்று;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        திரும்பு வெற்று;
    }

    எனில் (!SDL_CalculateSurfaceSize(format, width, height, &size, &pitch, false /* not minimal pitch */)) {
        // Overflow...
        திரும்பு வெற்று;
    }

    // Allocate and initialize the surface
    surface = (SDL_Surface *)SDL_malloc(அளவு(*surface));
    எனில் (!surface) {
        திரும்பு வெற்று;
    }

    எனில் (!SDL_InitializeSurface(surface, width, height, format, SDL_COLORSPACE_UNKNOWN, 0, வெற்று, (முழு)pitch, false)) {
        திரும்பு வெற்று;
    }

    எனில் (surface->w && surface->h && format != SDL_PIXELFORMAT_MJPG) {
        surface->flags &= ~SDL_SURFACE_PREALLOCATED;
        எனில் (SDL_GetHintBoolean("SDL_SURFACE_MALLOC", false)) {
            எனில் (clear_surface) {
                surface->pixels = SDL_calloc(1, size);
            } இல்லையெனில் {
                surface->pixels = SDL_malloc(size);
            }
        } இல்லையெனில் {
            surface->flags |= SDL_SURFACE_SIMD_ALIGNED;
            எனில் (clear_surface) {
                surface->pixels = SDL_aligned_alloc_zero(SDL_GetSIMDAlignment(), size);
            } இல்லையெனில் {
                surface->pixels = SDL_aligned_alloc(SDL_GetSIMDAlignment(), size);
            }
        }
        எனில் (!surface->pixels) {
            SDL_DestroySurface(surface);
            திரும்பு வெற்று;
        }
    }
    திரும்பு surface;
}

SDL_Surface *SDL_CreateSurfaceZeroed(முழு width, முழு height, SDL_PixelFormat format)
{
    திரும்பு SDL_CreateSurfaceInternal(width, height, format, true);
}

SDL_Surface *SDL_CreateSurfaceUninitialized(முழு width, முழு height, SDL_PixelFormat format)
{
    திரும்பு SDL_CreateSurfaceInternal(width, height, format, false);
}

SDL_Surface *SDL_CreateSurface(முழு width, முழு height, SDL_PixelFormat format)
{
    திரும்பு SDL_CreateSurfaceZeroed(width, height, format);
}


/*
 * Create an RGB surface from an existing memory buffer using the given
 * enum SDL_PIXELFORMAT_* format
 */
SDL_Surface *SDL_CreateSurfaceFrom(முழு width, முழு height, SDL_PixelFormat format, வெறுமை *pixels, முழு pitch)
{
    CHECK_PARAM(width < 0) {
        SDL_InvalidParamError("width");
        திரும்பு வெற்று;
    }

    CHECK_PARAM(height < 0) {
        SDL_InvalidParamError("height");
        திரும்பு வெற்று;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        திரும்பு வெற்று;
    }

    எனில் (pitch == 0 && !pixels) {
        // The application will fill these in later with valid values
    } இல்லையெனில் {
        size_t minimalPitch;

        எனில் (!SDL_CalculateSurfaceSize(format, width, height, வெற்று, &minimalPitch, true /* minimal pitch */)) {
            // Overflow...
            திரும்பு வெற்று;
        }

        CHECK_PARAM(pitch < 0 || (size_t)pitch < minimalPitch) {
            SDL_InvalidParamError("pitch");
            திரும்பு வெற்று;
        }
    }

    // Allocate and initialize the surface
    SDL_Surface *surface = (SDL_Surface *)SDL_malloc(அளவு(*surface));
    எனில் (!surface ||
        !SDL_InitializeSurface(surface, width, height, format, SDL_COLORSPACE_UNKNOWN, 0, pixels, pitch, false)) {
        திரும்பு வெற்று;
    }
    திரும்பு surface;
}

SDL_PropertiesID SDL_GetSurfaceProperties(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        திரும்பு 0;
    }

    எனில் (!surface->props) {
        surface->props = SDL_CreateProperties();
    }
    திரும்பு surface->props;
}

bool SDL_SetSurfaceColorspace(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        திரும்பு SDL_InvalidParamError("surface");
    }

    surface->colorspace = colorspace;
    திரும்பு true;
}

SDL_Colorspace SDL_GetSurfaceColorspace(SDL_Surface *surface)
{
    எனில் (!SDL_SurfaceValid(surface)) {
        திரும்பு SDL_COLORSPACE_UNKNOWN;
    }

    திரும்பு surface->colorspace;
}

தசம SDL_GetDefaultSDRWhitePoint(SDL_Colorspace colorspace)
{
    திரும்பு SDL_GetSurfaceSDRWhitePoint(வெற்று, colorspace);
}

தசம SDL_GetSurfaceSDRWhitePoint(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    SDL_TransferCharacteristics transfer = SDL_COLORSPACETRANSFER(colorspace);

    எனில் (transfer == SDL_TRANSFER_CHARACTERISTICS_LINEAR ||
        transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
        SDL_PropertiesID props;
        தசம default_மதிப்பு = 1.0f;

        எனில் (SDL_SurfaceValid(surface)) {
            props = surface->props;
        } இல்லையெனில் {
            props = 0;
        }
        எனில் (transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
            /* The older standards use an SDR white point of 100 nits.
             * ITU-R BT.2408-6 recommends using an SDR white point of 203 nits.
             * This is the default Chrome uses, and what a lot of game content
             * assumes, so we'll go with that.
             */
            மாறிலி தசம DEFAULT_PQ_SDR_WHITE_POINT = 203.0f;
            default_மதிப்பு = DEFAULT_PQ_SDR_WHITE_POINT;
        }
        திரும்பு SDL_GetFloatProperty(props, SDL_PROP_SURFACE_SDR_WHITE_POINT_FLOAT, default_மதிப்பு);
    }
    திரும்பு 1.0f;
}

தசம SDL_GetDefaultHDRHeadroom(SDL_Colorspace colorspace)
{
    திரும்பு SDL_GetSurfaceHDRHeadroom(வெற்று, colorspace);
}

தசம SDL_GetSurfaceHDRHeadroom(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    SDL_TransferCharacteristics transfer = SDL_COLORSPACETRANSFER(colorspace);

    எனில் (transfer == SDL_TRANSFER_CHARACTERISTICS_LINEAR ||
        transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
        SDL_PropertiesID props;
        தசம default_மதிப்பு = 0.0f;

        எனில் (SDL_SurfaceValid(surface)) {
            props = surface->props;
        } இல்லையெனில் {
            props = 0;
        }
        திரும்பு SDL_GetFloatProperty(props, SDL_PROP_SURFACE_HDR_HEADROOM_FLOAT, default_மதிப்பு);
    }
    திரும்பு 1.0f;
}

SDL_Palette *SDL_CreateSurfacePalette(SDL_Surface *surface)
{
    SDL_Palette *palette;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        திரும்பு வெற்று;
    }

    CHECK_PARAM(!SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        SDL_SetError("The surface is not indexed format");
        திரும்பு வெற்று;
    }

    palette = SDL_CreatePalette((1 << SDL_BITSPERPIXEL(surface->format)));
    எனில் (!palette) {
        திரும்பு வெற்று;
    }

    எனில் (palette->ncolors == 2) {
        // Create a black and white bitmap palette
        palette->colors[0].r = 0xFF;
        palette->colors[0].g = 0xFF;
        palette->colors[0].b = 0xFF;
        palette->colors[1].r = 0x00;
        palette->colors[1].g = 0x00;
        palette->colors[1].b = 0x00;
    }

    எனில் (!SDL_SetSurfacePalette(surface, palette)) {
        SDL_DestroyPalette(palette);
        திரும்பு வெற்று;
    }

    // The surface has retained the palette, we can remove the reference here
    SDL_assert(palette->refcount == 2);
    SDL_DestroyPalette(palette);
    திரும்பு palette;
}

bool SDL_SetSurfacePalette(SDL_Surface *surface, SDL_Palette *palette)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        திரும்பு SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(palette && !SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        திரும்பு SDL_SetError("Surface doesn't use a palette");
    }

    CHECK_PARAM(palette && palette->ncolors > (1 << SDL_BITSPERPIXEL(surface->format))) {
        திரும்பு SDL_SetError("Palette doesn't match surface format");
    }

    எனில் (palette != surface->palette) {
        எனில் (surface->palette) {
            SDL_DestroyPalette(surface->palette);
        }

        surface->palette = palette;

        எனில் (surface->palette) {
            ++surface->palette->refcount;
        }
    }

    SDL_InvalidateMap(&surface->map);

    திரும்பு true;
}

SDL_Palette *SDL_GetSurfacePalette(SDL_Surface *surface)
{
    எனில் (!SDL_SurfaceValid(surface)) {
        திரும்பு வெற்று;
    }

    திரும்பு surface->palette;
}

bool SDL_AddSurfaceAlternateImage(SDL_Surface *surface, SDL_Surface *image)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        திரும்பு SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(!SDL_SurfaceValid(image)) {
        திரும்பு SDL_InvalidParamError("image");
    }

    SDL_Surface **images = (SDL_Surface **)SDL_realloc(surface->images, (surface->இலக்கம்_images + 1) * அளவு(*images));
    எனில் (!images) {
        திரும்பு false;
    }
    images[surface->இலக்கம்_images] = image;
    surface->images = images;
    ++surface->இலக்கம்_images;
    ++image->refcount;
    திரும்பு true;
}

bool SDL_SurfaceHasAlternateImages(SDL_Surface *surface)
{
    எனில் (!SDL_SurfaceValid(surface)) {
        திரும்பு false;
    }

    திரும்பு (surface->இலக்கம்_images > 0);
}

SDL_Surface **SDL_GetSurfaceImages(SDL_Surface *surface, முழு *மொத்தம்)
{
    எனில் (மொத்தம்) {
        *மொத்தம் = 0;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        திரும்பு வெற்று;
    }

    முழு இலக்கம்_images = 1 + surface->இலக்கம்_images;
    SDL_Surface **images = (SDL_Surface **)SDL_malloc((இலக்கம்_images + 1) * அளவு(*images));
    எனில் (!images) {
        திரும்பு வெற்று;
    }
    images[0] = surface;
    எனில் (surface->இலக்கம்_images > 0) {
        SDL_memcpy(&images[1], surface->images, (surface->இலக்கம்_images * அளவு(images[1])));
    }
    images[இலக்கம்_images] = வெற்று;

    எனில் (மொத்தம்) {
        *மொத்தம் = இலக்கம்_images;
    }
    திரும்பு images;
}

SDL_Surface *SDL_GetSurfaceImage(SDL_Surface *surface, தசம display_scale)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        திரும்பு வெற்று;
    }

    எனில் (!SDL_SurfaceHasAlternateImages(surface)) {
        ++surface->refcount;
        திரும்பு surface;
    }

    // This surface has high DPI images, pick the best one available, or scale one to the correct size
    SDL_Surface **images = SDL_GetSurfaceImages(surface, வெற்று);
    எனில் (!images) {
        // Failure, fall back to the existing surface
        ++surface->refcount;
        திரும்பு surface;
    }

    // Find closest image. Images that are larger than the
    // desired size are preferred over images that are smaller.
    SDL_Surface *closest = வெற்று;
    முழு desired_w = (முழு)SDL_round(surface->w * display_scale);
    முழு desired_h = (முழு)SDL_round(surface->h * display_scale);
    முழு desired_size = desired_w * desired_h;
    முழு closest_distance = -1;
    முழு closest_size = -1;
    க்கு (முழு i = 0; images[i]; ++i) {
        SDL_Surface *candidate = images[i];
        முழு size = candidate->w * candidate->h;
        முழு delta_w = (candidate->w - desired_w);
        முழு delta_h = (candidate->h - desired_h);
        முழு distance = (delta_w * delta_w) + (delta_h * delta_h);
        எனில் (closest_distance < 0 || distance < closest_distance ||
            (size > desired_size && closest_size < desired_size)) {
            closest = candidate;
            closest_distance = distance;
            closest_size = size;
        }
    }
    SDL_free(images);
    SDL_assert(closest != வெற்று);    // We should always have at least one surface

    எனில் (closest->w == desired_w && closest->h == desired_h) {
        ++closest->refcount;
        திரும்பு closest;
    }

    // We need to scale the image to the correct size. To maintain good image quality, downscaling
    // is done in steps, never reducing the width and height by more than half each time.
    SDL_Surface *scaled = closest;
    செய் {
        முழு next_scaled_w = SDL_max(desired_w, (scaled->w + 1) / 2);
        முழு next_scaled_h = SDL_max(desired_h, (scaled->h + 1) / 2);
        SDL_Surface *next_scaled = SDL_ScaleSurface(scaled, next_scaled_w, next_scaled_h, SDL_SCALEMODE_LINEAR);
        எனில் (scaled != closest) {
            SDL_DestroySurface(scaled);
        }
        scaled = next_scaled;
        எனில் (!scaled) {
            // Failure, fall back to the closest surface
            ++closest->refcount;
            திரும்பு closest;
        }
    } போது (scaled->w != desired_w || scaled->h != desired_h);

    திரும்பு scaled;
}

வெறுமை SDL_RemoveSurfaceAlternateImages(SDL_Surface *surface)
{
    எனில் (!SDL_SurfaceValid(surface)) {
        திரும்பு;
    }

    எனில் (surface->இலக்கம்_images > 0) {
        க்கு (முழு i = 0; i < surface->இலக்கம்_images; ++i) {
            SDL_DestroySurface(surface->images[i]);
        }
        SDL_free(surface->images);
        surface->images = வெற்று;
        surface->இலக்கம்_images = 0;
    }
}

bool SDL_SetSurfaceRLE(SDL_Surface *surface, bool enabled)
{
    முழு flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        திரும்பு SDL_InvalidParamError("surface");
    }

    flags = surface->map.info.flags;
    எனில் (enabled) {
        surface->map.info.flags |= SDL_COPY_RLE_DESIRED;
    } இல்லையெனில் {
        surface->map.info.flags &= ~SDL_COPY_RLE_DESIRED;
    }
    எனில் (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    திரும்பு true;
}

bool SDL_SurfaceHasRLE(SDL_Surface *surface)
{
    எனில் (!SDL_SurfaceValid(surface)) {
        திரும்பு false;
    }

    எனில் (!(surface->map.info.flags & SDL_COPY_RLE_DESIRED)) {
        திரும்பு false;
    }

    திரும்பு true;
}

bool SDL_Set_Surface_Color_சாவி(SDL_Surface *surface, bool enabled, Uint32 சாவி)
{
    முழு flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        திரும்பு SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(surface->palette && சாவி >= ((Uint32)surface->palette->ncolors)) {
        திரும்பு SDL_InvalidParamError("key");
    }

    flags = surface->map.info.flags;
    எனில் (enabled) {
        surface->map.info.flags |= SDL_COPY_COLORKEY;
        surface->map.info.colorkey = சாவி;
    } இல்லையெனில் {
        surface->map.info.flags &= ~SDL_COPY_COLORKEY;
    }
    எனில் (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }

    திரும்பு true;
}

bool SDL_Surface_Has_Color_சாவி(SDL_Surface *surface)
{
    எனில் (!SDL_SurfaceValid(surface)) {
        திரும்பு false;
    }

    எனில் (!(surface->map.info.flags & SDL_COPY_COLORKEY)) {
        திரும்பு false;
    }

    திரும்பு true;
}

bool SDL_Get_Surface_Color_சாவி(SDL_Surface *surface, Uint32 *சாவி)
{
    எனில் (சாவி) {
        *சாவி = 0;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        திரும்பு SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(!(surface->map.info.flags & SDL_COPY_COLORKEY)) {
        திரும்பு SDL_SetError("Surface doesn't have a colorkey");
    }

    எனில் (சாவி) {
        *சாவி = surface->map.info.colorkey;
    }
    திரும்பு true;
}

/* This is a fairly slow function to switch from colorkey to alpha
   NB: it doesn't handle bpp 1 or 3, because they have no alpha channel */
நிலையான வெறுமை SDL_ConvertColorkeyToAlpha(SDL_Surface *surface, bool ignore_alpha)
{
    முழு x, y, bpp;

    எனில் (!SDL_SurfaceValid(surface)) {
        திரும்பு;
    }

    எனில் (!(surface->map.info.flags & SDL_COPY_COLORKEY) ||
        !SDL_ISPIXELFORMAT_ALPHA(surface->format)) {
        திரும்பு;
    }

    bpp = SDL_BYTESPERPIXEL(surface->format);

    SDL_LockSurface(surface);

    எனில் (bpp == 2) {
        Uint16 *row, *spot;
        Uint16 ckey = (Uint16)surface->map.info.colorkey;
        Uint16 mask = (Uint16)(~surface->fmt->Amask);

        // Ignore, or not, alpha in colorkey comparison
        எனில் (ignore_alpha) {
            ckey &= mask;
            row = (Uint16 *)surface->pixels;
            க்கு (y = surface->h; y--;) {
                spot = row;
                க்கு (x = surface->w; x--;) {
                    எனில் ((*spot & mask) == ckey) {
                        *spot &= mask;
                    }
                    ++spot;
                }
                row += surface->pitch / 2;
            }
        } இல்லையெனில் {
            row = (Uint16 *)surface->pixels;
            க்கு (y = surface->h; y--;) {
                spot = row;
                க்கு (x = surface->w; x--;) {
                    எனில் (*spot == ckey) {
                        *spot &= mask;
                    }
                    ++spot;
                }
                row += surface->pitch / 2;
            }
        }
    } இல்லையெனில் எனில் (bpp == 4) {
        Uint32 *row, *spot;
        Uint32 ckey = surface->map.info.colorkey;
        Uint32 mask = ~surface->fmt->Amask;

        // Ignore, or not, alpha in colorkey comparison
        எனில் (ignore_alpha) {
            ckey &= mask;
            row = (Uint32 *)surface->pixels;
            க்கு (y = surface->h; y--;) {
                spot = row;
                க்கு (x = surface->w; x--;) {
                    எனில் ((*spot & mask) == ckey) {
                        *spot &= mask;
                    }
                    ++spot;
                }
                row += surface->pitch / 4;
            }
        } இல்லையெனில் {
            row = (Uint32 *)surface->pixels;
            க்கு (y = surface->h; y--;) {
                spot = row;
                க்கு (x = surface->w; x--;) {
                    எனில் (*spot == ckey) {
                        *spot &= mask;
                    }
                    ++spot;
                }
                row += surface->pitch / 4;
            }
        }
    }

    SDL_UnlockSurface(surface);

    SDL_Set_Surface_Color_சாவி(surface, false, 0);
    SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
}

bool SDL_SetSurfaceColorMod(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b)
{
    முழு flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        திரும்பு SDL_InvalidParamError("surface");
    }

    surface->map.info.r = r;
    surface->map.info.g = g;
    surface->map.info.b = b;

    flags = surface->map.info.flags;
    எனில் (r != 0xFF || g != 0xFF || b != 0xFF) {
        surface->map.info.flags |= SDL_COPY_MODULATE_COLOR;
    } இல்லையெனில் {
        surface->map.info.flags &= ~SDL_COPY_MODULATE_COLOR;
    }
    எனில் (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    திரும்பு true;
}

bool SDL_GetSurfaceColorMod(SDL_Surface *surface, Uint8 *r, Uint8 *g, Uint8 *b)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        எனில் (r) {
            *r = 255;
        }
        எனில் (g) {
            *g = 255;
        }
        எனில் (b) {
            *b = 255;
        }
        திரும்பு SDL_InvalidParamError("surface");
    }

    எனில் (r) {
        *r = surface->map.info.r;
    }
    எனில் (g) {
        *g = surface->map.info.g;
    }
    எனில் (b) {
        *b = surface->map.info.b;
    }
    திரும்பு true;
}

bool SDL_SetSurfaceAlphaMod(SDL_Surface *surface, Uint8 alpha)
{
    முழு flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        திரும்பு SDL_InvalidParamError("surface");
    }

    surface->map.info.a = alpha;

    flags = surface->map.info.flags;
    எனில் (alpha != 0xFF) {
        surface->map.info.flags |= SDL_COPY_MODULATE_ALPHA;
    } இல்லையெனில் {
        surface->map.info.flags &= ~SDL_COPY_MODULATE_ALPHA;
    }
    எனில் (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    திரும்பு true;
}

bool SDL_GetSurfaceAlphaMod(SDL_Surface *surface, Uint8 *alpha)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        எனில் (alpha) {
            *alpha = 255;
        }
        திரும்பு SDL_InvalidParamError("surface");
    }

    எனில் (alpha) {
        *alpha = surface->map.info.a;
    }
    திரும்பு true;
}

bool SDL_SetSurfaceBlendMode(SDL_Surface *surface, SDL_BlendMode blendMode)
{
    முழு flags;
    bool result = true;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        திரும்பு SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(blendMode == SDL_BLENDMODE_INVALID) {
        திரும்பு SDL_InvalidParamError("blendMode");
    }

    flags = surface->map.info.flags;
    surface->map.info.flags &= ~SDL_COPY_BLEND_MASK;
    தேர்வு (blendMode) {
    நிலை SDL_BLENDMODE_NONE:
        நிறுத்து;
    நிலை SDL_BLENDMODE_BLEND:
        surface->map.info.flags |= SDL_COPY_BLEND;
        நிறுத்து;
    நிலை SDL_BLENDMODE_BLEND_PREMULTIPLIED:
        surface->map.info.flags |= SDL_COPY_BLEND_PREMULTIPLIED;
        நிறுத்து;
    நிலை SDL_BLENDMODE_ADD:
        surface->map.info.flags |= SDL_COPY_ADD;
        நிறுத்து;
    நிலை SDL_BLENDMODE_ADD_PREMULTIPLIED:
        surface->map.info.flags |= SDL_COPY_ADD_PREMULTIPLIED;
        நிறுத்து;
    நிலை SDL_BLENDMODE_MOD:
        surface->map.info.flags |= SDL_COPY_MOD;
        நிறுத்து;
    நிலை SDL_BLENDMODE_MUL:
        surface->map.info.flags |= SDL_COPY_MUL;
        நிறுத்து;
    இயல்பு:
        result = SDL_Unsupported();
        நிறுத்து;
    }

    எனில் (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }

    திரும்பு result;
}

bool SDL_GetSurfaceBlendMode(SDL_Surface *surface, SDL_BlendMode *blendMode)
{
    எனில் (blendMode) {
        *blendMode = SDL_BLENDMODE_INVALID;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        திரும்பு SDL_InvalidParamError("surface");
    }

    எனில் (!blendMode) {
        திரும்பு true;
    }

    தேர்வு (surface->map.info.flags & SDL_COPY_BLEND_MASK) {
    நிலை SDL_COPY_BLEND:
        *blendMode = SDL_BLENDMODE_BLEND;
        நிறுத்து;
    நிலை SDL_COPY_BLEND_PREMULTIPLIED:
        *blendMode = SDL_BLENDMODE_BLEND_PREMULTIPLIED;
        நிறுத்து;
    நிலை SDL_COPY_ADD:
        *blendMode = SDL_BLENDMODE_ADD;
        நிறுத்து;
    நிலை SDL_COPY_ADD_PREMULTIPLIED:
        *blendMode = SDL_BLENDMODE_ADD_PREMULTIPLIED;
        நிறுத்து;
    நிலை SDL_COPY_MOD:
        *blendMode = SDL_BLENDMODE_MOD;
        நிறுத்து;
    நிலை SDL_COPY_MUL:
        *blendMode = SDL_BLENDMODE_MUL;
        நிறுத்து;
    இயல்பு:
        *blendMode = SDL_BLENDMODE_NONE;
        நிறுத்து;
    }
    திரும்பு true;
}

bool SDL_SetSurfaceClipRect(SDL_Surface *surface, மாறிலி SDL_Rect *rect)
{
    SDL_Rect full_rect;

    // Don't do anything if there's no surface to act on
    எனில் (!SDL_SurfaceValid(surface)) {
        திரும்பு false;
    }

    // Set up the full surface rectangle
    full_rect.x = 0;
    full_rect.y = 0;
    full_rect.w = surface->w;
    full_rect.h = surface->h;

    // Set the clipping rectangle
    எனில் (!rect) {
        surface->clip_rect = full_rect;
        திரும்பு true;
    }
    திரும்பு SDL_GetRectIntersection(rect, &full_rect, &surface->clip_rect);
}

bool SDL_GetSurfaceClipRect(SDL_Surface *surface, SDL_Rect *rect)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        எனில் (rect) {
            SDL_zerop(rect);
        }
        திரும்பு SDL_InvalidParamError("surface");
    }
    CHECK_PARAM(!rect) {
        திரும்பு SDL_InvalidParamError("rect");
    }
    *rect = surface->clip_rect;
    திரும்பு true;
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
bool SDL_BlitSurfaceUnchecked(SDL_Surface *src, மாறிலி SDL_Rect *srcrect,
                             SDL_Surface *dst, மாறிலி SDL_Rect *dstrect)
{
    // Check to make sure the blit mapping is valid
    எனில் (!SDL_ValidateMap(src, dst)) {
        திரும்பு false;
    }
    திரும்பு src->map.blit(src, srcrect, dst, dstrect);
}

bool SDL_BlitSurface(SDL_Surface *src, மாறிலி SDL_Rect *srcrect, SDL_Surface *dst, மாறிலி SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src) || (!src->pixels && !SDL_MUSTLOCK(src))) {
        திரும்பு SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst) || (!dst->pixels && !SDL_MUSTLOCK(dst))) {
        திரும்பு SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        திரும்பு SDL_SetError("Surfaces must not be locked during blit");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    எனில் (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
    } இல்லையெனில் {
        r_dst.x = 0;
        r_dst.y = 0;
    }

    // clip the source rectangle to the source surface
    எனில் (srcrect) {
        SDL_Rect tmp;
        எனில் (SDL_GetRectIntersection(srcrect, &r_src, &tmp) == false) {
            திரும்பு true;
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
        எனில் (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &tmp) == false) {
            திரும்பு true;
        }

        // Shift srcrect, if dstrect has changed
        r_src.x += tmp.x - r_dst.x;
        r_src.y += tmp.y - r_dst.y;
        r_src.w = tmp.w;
        r_src.h = tmp.h;

        // Update dstrect
        r_dst = tmp;
    }

    எனில் (r_dst.w <= 0 || r_dst.h <= 0) {
        // No-op.
        திரும்பு true;
    }

    // Switch back to a fast blit if we were previously stretching
    எனில் (src->map.info.flags & SDL_COPY_NEAREST) {
        src->map.info.flags &= ~SDL_COPY_NEAREST;
        SDL_InvalidateMap(&src->map);
    }

    திரும்பு SDL_BlitSurfaceUnchecked(src, &r_src, dst, &r_dst);
}

நிலையான bool SDL_BlitSurfaceClippedScaled(SDL_Surface *src, மாறிலி SDL_Rect *srcrect, SDL_Surface *dst, மாறிலி SDL_Rect *dstrect, SDL_ScaleMode scaleMode)
{
    // We need to scale first, then blit into dst because we're clipping in the destination surface pixel coordinates
    bool result;
    முழு saved_w = src->w;
    முழு saved_h = src->h;
    வெறுமை *saved_pixels = src->pixels;
    src->w = srcrect->w;
    src->h = srcrect->h;
    src->pixels = (Uint8 *)src->pixels + srcrect->y * src->pitch + srcrect->x * SDL_BYTESPERPIXEL(src->format);
    SDL_Surface *scaled = SDL_ScaleSurface(src, dstrect->w, dstrect->h, scaleMode);
    எனில் (scaled) {
        result = SDL_BlitSurface(scaled, வெற்று, dst, dstrect);
        SDL_DestroySurface(scaled);
    } இல்லையெனில் {
        result = false;
    }
    src->w = saved_w;
    src->h = saved_h;
    src->pixels = saved_pixels;
    திரும்பு result;
}

bool SDL_BlitSurfaceScaled(SDL_Surface *src, மாறிலி SDL_Rect *srcrect, SDL_Surface *dst, மாறிலி SDL_Rect *dstrect, SDL_ScaleMode scaleMode)
{
    SDL_Rect r_src, r_dst;
    bool result;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src) || (!src->pixels && !SDL_MUSTLOCK(src))) {
        திரும்பு SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst) || (!dst->pixels && !SDL_MUSTLOCK(dst))) {
        திரும்பு SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        திரும்பு SDL_SetError("Surfaces must not be locked during blit");
    }

    தேர்வு (scaleMode) {
    நிலை SDL_SCALEMODE_NEAREST:
        நிறுத்து;
    நிலை SDL_SCALEMODE_LINEAR:
        நிறுத்து;
    நிலை SDL_SCALEMODE_PIXELART:
        scaleMode = SDL_SCALEMODE_NEAREST;
        நிறுத்து;
    இயல்பு:
        திரும்பு SDL_InvalidParamError("scaleMode");
    }

    முழு src_w = srcrect ? srcrect->w : src->w;
    முழு src_h = srcrect ? srcrect->h : src->h;
    முழு dst_w = dstrect ? dstrect->w : dst->w;
    முழு dst_h = dstrect ? dstrect->h : dst->h;
    எனில் (src_w == dst_w && src_h == dst_h) {
        // No scaling, defer to regular blit
        திரும்பு SDL_BlitSurface(src, srcrect, dst, dstrect);
    }

    எனில் (src->w == 0 || src->h == 0) {
        // Nothing to do
        திரும்பு true;
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    எனில் (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
        r_dst.w = dstrect->w;
        r_dst.h = dstrect->h;
    } இல்லையெனில் {
        r_dst.x = 0;
        r_dst.y = 0;
        r_dst.w = dst->w;
        r_dst.h = dst->h;
    }

    // clip the source rectangle to the source surface
    எனில் (srcrect) {
        SDL_Rect desired, tmp;
        desired.x = srcrect->x;
        desired.y = srcrect->y;
        desired.w = SDL_max(srcrect->w, 1);
        desired.h = SDL_max(srcrect->h, 1);
        எனில் (SDL_GetRectIntersection(&desired, &r_src, &tmp) == false) {
            திரும்பு true;
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
    எனில் (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &tmp) == false) {
        திரும்பு true;
    }

    எனில் (tmp.x != r_dst.x || tmp.y != r_dst.y || tmp.w != r_dst.w || tmp.h != r_dst.h) {
        // Need to do a clipped and scaled blit
        திரும்பு SDL_BlitSurfaceClippedScaled(src, &r_src, dst, &r_dst, scaleMode);
    }

    எனில் (SDL_MUSTLOCK(src)) {
        எனில் (!SDL_LockSurface(src)) {
            திரும்பு false;
        }
    }
    எனில் (SDL_MUSTLOCK(dst)) {
        எனில் (!SDL_LockSurface(dst)) {
            எனில் (SDL_MUSTLOCK(src)) {
                SDL_UnlockSurface(src);
            }
            திரும்பு false;
        }
    }

    result = SDL_BlitSurfaceUncheckedScaled(src, &r_src, dst, &r_dst, scaleMode);

    எனில் (SDL_MUSTLOCK(src)) {
        SDL_UnlockSurface(src);
    }
    எனில் (SDL_MUSTLOCK(dst)) {
        SDL_UnlockSurface(dst);
    }
    திரும்பு result;
}

/**
 *  This is a semi-private blit function and it performs low-level surface
 *  scaled blitting only.
 */
bool SDL_BlitSurfaceUncheckedScaled(SDL_Surface *src, மாறிலி SDL_Rect *srcrect, SDL_Surface *dst, மாறிலி SDL_Rect *dstrect, SDL_ScaleMode scaleMode)
{
    நிலையான மாறிலி Uint32 complex_copy_flags = (SDL_COPY_MODULATE_MASK | SDL_COPY_BLEND_MASK | SDL_COPY_COLORKEY);

    எனில் (srcrect->w > SDL_MAX_UINT16 || srcrect->h > SDL_MAX_UINT16 ||
        dstrect->w > SDL_MAX_UINT16 || dstrect->h > SDL_MAX_UINT16) {
        திரும்பு SDL_SetError("Size too large for scaling");
    }

    எனில் (!(src->map.info.flags & SDL_COPY_NEAREST)) {
        src->map.info.flags |= SDL_COPY_NEAREST;
        SDL_InvalidateMap(&src->map);
    }

    எனில் (scaleMode == SDL_SCALEMODE_NEAREST || scaleMode == SDL_SCALEMODE_PIXELART) {
        எனில் (!(src->map.info.flags & complex_copy_flags) &&
            src->format == dst->format &&
            (!SDL_ISPIXELFORMAT_INDEXED(src->format) ||
             (SDL_BITSPERPIXEL(src->format) == 8 && SDL_IsSamePalette(src->palette, dst->palette))) &&
            SDL_BYTESPERPIXEL(src->format) <= 4) {
            திரும்பு SDL_StretchSurface(src, srcrect, dst, dstrect, SDL_SCALEMODE_NEAREST);
        } இல்லையெனில் எனில் (SDL_BITSPERPIXEL(src->format) < 8) {
            // Scaling bitmap not yet supported, convert to RGBA for blit
            bool result = false;
            SDL_Surface *tmp = SDL_ConvertSurface(src, SDL_PIXELFORMAT_ARGB8888);
            எனில் (tmp) {
                result = SDL_BlitSurfaceUncheckedScaled(tmp, srcrect, dst, dstrect, SDL_SCALEMODE_NEAREST);
                SDL_DestroySurface(tmp);
            }
            திரும்பு result;
        } இல்லையெனில் {
            திரும்பு SDL_BlitSurfaceUnchecked(src, srcrect, dst, dstrect);
        }
    } இல்லையெனில் {
        எனில் (!(src->map.info.flags & complex_copy_flags) &&
            src->format == dst->format &&
            !SDL_ISPIXELFORMAT_INDEXED(src->format) &&
            SDL_BYTESPERPIXEL(src->format) == 4 &&
            src->format != SDL_PIXELFORMAT_ARGB2101010) {
            // fast path
            திரும்பு SDL_StretchSurface(src, srcrect, dst, dstrect, SDL_SCALEMODE_LINEAR);
        } இல்லையெனில் எனில் (SDL_BITSPERPIXEL(src->format) < 8) {
            // Scaling bitmap not yet supported, convert to RGBA for blit
            bool result = false;
            SDL_Surface *tmp = SDL_ConvertSurface(src, SDL_PIXELFORMAT_ARGB8888);
            எனில் (tmp) {
                result = SDL_BlitSurfaceUncheckedScaled(tmp, srcrect, dst, dstrect, scaleMode);
                SDL_DestroySurface(tmp);
            }
            திரும்பு result;
        } இல்லையெனில் {
            // Use intermediate surface(s)
            SDL_Surface *tmp1 = வெற்று;
            bool result;
            SDL_Rect srcrect2;
            முழு is_complex_copy_flags = (src->map.info.flags & complex_copy_flags);

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
            எனில் (SDL_BYTESPERPIXEL(src->format) != 4 || src->format == SDL_PIXELFORMAT_ARGB2101010) {
                SDL_PixelFormat fmt;
                எனில் (SDL_BYTESPERPIXEL(dst->format) == 4 && dst->format != SDL_PIXELFORMAT_ARGB2101010 &&
                    (SDL_ISPIXELFORMAT_ALPHA(dst->format) || !is_complex_copy_flags)) {
                    fmt = dst->format;
                } இல்லையெனில் {
                    fmt = SDL_PIXELFORMAT_ARGB8888;
                }
                tmp1 = SDL_ConvertSurfaceRect(src, srcrect, fmt);
                எனில் (!tmp1) {
                    திரும்பு false;
                }
                src = tmp1;
                srcrect2.x = 0;
                srcrect2.y = 0;
            }

            // Intermediate scaling
            எனில் (is_complex_copy_flags || src->format != dst->format) {
                SDL_Rect tmprect;
                SDL_Surface *tmp2 = SDL_CreateSurfaceUninitialized(dstrect->w, dstrect->h, src->format);
                SDL_StretchSurface(src, &srcrect2, tmp2, வெற்று, SDL_SCALEMODE_LINEAR);

                SDL_SetSurfaceColorMod(tmp2, r, g, b);
                SDL_SetSurfaceAlphaMod(tmp2, alpha);
                SDL_SetSurfaceBlendMode(tmp2, blendMode);

                tmprect.x = 0;
                tmprect.y = 0;
                tmprect.w = dstrect->w;
                tmprect.h = dstrect->h;
                result = SDL_BlitSurfaceUnchecked(tmp2, &tmprect, dst, dstrect);
                SDL_DestroySurface(tmp2);
            } இல்லையெனில் {
                result = SDL_StretchSurface(src, &srcrect2, dst, dstrect, SDL_SCALEMODE_LINEAR);
            }

            SDL_DestroySurface(tmp1);
            திரும்பு result;
        }
    }
}

bool SDL_BlitSurfaceTiled(SDL_Surface *src, மாறிலி SDL_Rect *srcrect, SDL_Surface *dst, மாறிலி SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        திரும்பு SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        திரும்பு SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        திரும்பு SDL_SetError("Surfaces must not be locked during blit");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    எனில் (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
        r_dst.w = dstrect->w;
        r_dst.h = dstrect->h;
    } இல்லையெனில் {
        r_dst.x = 0;
        r_dst.y = 0;
        r_dst.w = dst->w;
        r_dst.h = dst->h;
    }

    // clip the source rectangle to the source surface
    எனில் (srcrect) {
        எனில் (SDL_GetRectIntersection(srcrect, &r_src, &r_src) == false) {
            திரும்பு true;
        }

        // For tiling we don't adjust the destination rectangle
    }

    // clip the destination rectangle against the clip rectangle
    {
        எனில் (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &r_dst) == false) {
            திரும்பு true;
        }

        // For tiling we don't adjust the source rectangle
    }

    // Switch back to a fast blit if we were previously stretching
    எனில் (src->map.info.flags & SDL_COPY_NEAREST) {
        src->map.info.flags &= ~SDL_COPY_NEAREST;
        SDL_InvalidateMap(&src->map);
    }

    முழு rows = r_dst.h / r_src.h;
    முழு cols = r_dst.w / r_src.w;
    முழு remaining_w = r_dst.w % r_src.w;
    முழு remaining_h = r_dst.h % r_src.h;
    SDL_Rect curr_src, curr_dst;

    SDL_copyp(&curr_src, &r_src);
    curr_dst.y = r_dst.y;
    curr_dst.w = r_src.w;
    curr_dst.h = r_src.h;
    க்கு (முழு y = 0; y < rows; ++y) {
        curr_dst.x = r_dst.x;
        க்கு (முழு x = 0; x < cols; ++x) {
            எனில் (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                திரும்பு false;
            }
            curr_dst.x += curr_dst.w;
        }
        எனில் (remaining_w) {
            curr_src.w = remaining_w;
            curr_dst.w = remaining_w;
            எனில் (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                திரும்பு false;
            }
            curr_src.w = r_src.w;
            curr_dst.w = r_src.w;
        }
        curr_dst.y += curr_dst.h;
    }
    எனில் (remaining_h) {
        curr_src.h = remaining_h;
        curr_dst.h = remaining_h;
        curr_dst.x = r_dst.x;
        க்கு (முழு x = 0; x < cols; ++x) {
            எனில் (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                திரும்பு false;
            }
            curr_dst.x += curr_dst.w;
        }
        எனில் (remaining_w) {
            curr_src.w = remaining_w;
            curr_dst.w = remaining_w;
            எனில் (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                திரும்பு false;
            }
        }
    }
    திரும்பு true;
}

bool SDL_BlitSurfaceTiledWithScale(SDL_Surface *src, மாறிலி SDL_Rect *srcrect, தசம scale, SDL_ScaleMode scaleMode, SDL_Surface *dst, மாறிலி SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        திரும்பு SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        திரும்பு SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        திரும்பு SDL_SetError("Surfaces must not be locked during blit");
    }
    CHECK_PARAM(scale < 0.0f) {
        திரும்பு SDL_InvalidParamError("scale");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    எனில் (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
        r_dst.w = dstrect->w;
        r_dst.h = dstrect->h;
    } இல்லையெனில் {
        r_dst.x = 0;
        r_dst.y = 0;
        r_dst.w = dst->w;
        r_dst.h = dst->h;
    }

    // clip the source rectangle to the source surface
    எனில் (srcrect) {
        எனில் (SDL_GetRectIntersection(srcrect, &r_src, &r_src) == false) {
            திரும்பு true;
        }

        // For tiling we don't adjust the destination rectangle
    }

    // clip the destination rectangle against the clip rectangle
    {
        எனில் (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &r_dst) == false) {
            திரும்பு true;
        }

        // For tiling we don't adjust the source rectangle
    }

    // Switch back to a fast blit if we were previously stretching
    எனில் (src->map.info.flags & SDL_COPY_NEAREST) {
        src->map.info.flags &= ~SDL_COPY_NEAREST;
        SDL_InvalidateMap(&src->map);
    }

    முழு tile_width = (முழு)SDL_roundf(r_src.w * scale);
    முழு tile_height = (முழு)SDL_roundf(r_src.h * scale);
    எனில் (tile_width <= 0 || tile_height <= 0) {
        // Nothing to do
        திரும்பு true;
    }
    முழு rows = r_dst.h / tile_height;
    முழு cols = r_dst.w / tile_width;
    முழு remaining_dst_w = (r_dst.w - cols * tile_width);
    முழு remaining_dst_h = (r_dst.h - rows * tile_height);
    முழு remaining_src_w = (முழு)(remaining_dst_w / scale);
    முழு remaining_src_h = (முழு)(remaining_dst_h / scale);
    SDL_Rect curr_src, curr_dst;

    SDL_copyp(&curr_src, &r_src);
    curr_dst.y = r_dst.y;
    curr_dst.w = tile_width;
    curr_dst.h = tile_height;
    க்கு (முழு y = 0; y < rows; ++y) {
        curr_dst.x = r_dst.x;
        க்கு (முழு x = 0; x < cols; ++x) {
            எனில் (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
                திரும்பு false;
            }
            curr_dst.x += curr_dst.w;
        }
        எனில் (remaining_dst_w > 0) {
            curr_src.w = remaining_src_w;
            curr_dst.w = remaining_dst_w;
            எனில் (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
                திரும்பு false;
            }
            curr_src.w = r_src.w;
            curr_dst.w = tile_width;
        }
        curr_dst.y += curr_dst.h;
    }
    எனில் (remaining_dst_h > 0) {
        curr_src.h = remaining_src_h;
        curr_dst.h = remaining_dst_h;
        curr_dst.x = r_dst.x;
        க்கு (முழு x = 0; x < cols; ++x) {
            எனில் (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
                திரும்பு false;
            }
            curr_dst.x += curr_dst.w;
        }
        எனில் (remaining_dst_w > 0) {
            curr_src.w = remaining_src_w;
            curr_dst.w = remaining_dst_w;
            எனில் (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
                திரும்பு false;
            }
        }
    }
    திரும்பு true;
}

bool SDL_BlitSurface9Grid(SDL_Surface *src, மாறிலி SDL_Rect *srcrect, முழு இடது_width, முழு வலது_width, முழு உச்சி_height, முழு bottom_height, தசம scale, SDL_ScaleMode scaleMode, SDL_Surface *dst, மாறிலி SDL_Rect *dstrect)
{
    SDL_Rect full_src, full_dst;
    SDL_Rect curr_src, curr_dst;
    முழு dst_இடது_width;
    முழு dst_வலது_width;
    முழு dst_உச்சி_height;
    முழு dst_bottom_height;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        திரும்பு SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        திரும்பு SDL_InvalidParamError("dst");
    }

    எனில் (!srcrect) {
        full_src.x = 0;
        full_src.y = 0;
        full_src.w = src->w;
        full_src.h = src->h;
        srcrect = &full_src;
    }

    எனில் (!dstrect) {
        full_dst.x = 0;
        full_dst.y = 0;
        full_dst.w = dst->w;
        full_dst.h = dst->h;
        dstrect = &full_dst;
    }

    எனில் (scale <= 0.0f || scale == 1.0f) {
        dst_இடது_width = இடது_width;
        dst_வலது_width = வலது_width;
        dst_உச்சி_height = உச்சி_height;
        dst_bottom_height = bottom_height;
    } இல்லையெனில் {
        dst_இடது_width = (முழு)SDL_roundf(இடது_width * scale);
        dst_வலது_width = (முழு)SDL_roundf(வலது_width * scale);
        dst_உச்சி_height = (முழு)SDL_roundf(உச்சி_height * scale);
        dst_bottom_height = (முழு)SDL_roundf(bottom_height * scale);
    }

    // Upper-left corner
    curr_src.x = srcrect->x;
    curr_src.y = srcrect->y;
    curr_src.w = இடது_width;
    curr_src.h = உச்சி_height;
    curr_dst.x = dstrect->x;
    curr_dst.y = dstrect->y;
    curr_dst.w = dst_இடது_width;
    curr_dst.h = dst_உச்சி_height;
    எனில் (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        திரும்பு false;
    }

    // Upper-right corner
    curr_src.x = srcrect->x + srcrect->w - வலது_width;
    curr_src.w = வலது_width;
    curr_dst.x = dstrect->x + dstrect->w - dst_வலது_width;
    curr_dst.w = dst_வலது_width;
    எனில் (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        திரும்பு false;
    }

    // Lower-right corner
    curr_src.y = srcrect->y + srcrect->h - bottom_height;
    curr_dst.y = dstrect->y + dstrect->h - dst_bottom_height;
    curr_dst.h = dst_bottom_height;
    எனில் (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        திரும்பு false;
    }

    // Lower-left corner
    curr_src.x = srcrect->x;
    curr_src.w = இடது_width;
    curr_dst.x = dstrect->x;
    curr_dst.w = dst_இடது_width;
    எனில் (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        திரும்பு false;
    }

    //இடது
    curr_src.y = srcrect->y + உச்சி_height;
    curr_src.h = srcrect->h - உச்சி_height - bottom_height;
    curr_dst.y = dstrect->y + dst_உச்சி_height;
    curr_dst.h = dstrect->h - dst_உச்சி_height - dst_bottom_height;
    எனில் (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        திரும்பு false;
    }

    //வலது
    curr_src.x = srcrect->x + srcrect->w - வலது_width;
    curr_src.w = வலது_width;
    curr_dst.x = dstrect->x + dstrect->w - dst_வலது_width;
    curr_dst.w = dst_வலது_width;
    எனில் (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        திரும்பு false;
    }

    //உச்சி
    curr_src.x = srcrect->x + இடது_width;
    curr_src.y = srcrect->y;
    curr_src.w = srcrect->w - இடது_width - வலது_width;
    curr_src.h = உச்சி_height;
    curr_dst.x = dstrect->x + dst_இடது_width;
    curr_dst.y = dstrect->y;
    curr_dst.w = dstrect->w - dst_இடது_width - dst_வலது_width;
    curr_dst.h = dst_உச்சி_height;
    எனில் (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        திரும்பு false;
    }

    // Bottom
    curr_src.y = srcrect->y + srcrect->h - bottom_height;
    curr_dst.y = dstrect->y + dstrect->h - dst_bottom_height;
    curr_dst.h = dst_bottom_height;
    எனில் (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        திரும்பு false;
    }

    // Center
    curr_src.x = srcrect->x + இடது_width;
    curr_src.y = srcrect->y + உச்சி_height;
    curr_src.w = srcrect->w - இடது_width - வலது_width;
    curr_src.h = srcrect->h - உச்சி_height - bottom_height;
    curr_dst.x = dstrect->x + dst_இடது_width;
    curr_dst.y = dstrect->y + dst_உச்சி_height;
    curr_dst.w = dstrect->w - dst_இடது_width - dst_வலது_width;
    curr_dst.h = dstrect->h - dst_உச்சி_height - dst_bottom_height;
    எனில் (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        திரும்பு false;
    }

    திரும்பு true;
}

/*
 * Lock a surface to directly access the pixels
 */
bool SDL_LockSurface(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        திரும்பு SDL_InvalidParamError("surface");
    }

    எனில் (!surface->locked) {
#ifdef SDL_HAVE_RLE
        // Perform the lock
        எனில் (surface->internal_flags & SDL_INTERNAL_SURFACE_RLEACCEL) {
            SDL_UnRLESurface(surface);
        }
#endif
    }

    // Increment the surface lock count, for recursive locks
    ++surface->locked;
    surface->flags |= SDL_SURFACE_LOCKED;
    SDL_UpdateSurfaceLockFlag(surface);

    // Ready to go..
    திரும்பு true;
}

/*
 * Unlock a previously locked surface
 */
வெறுமை SDL_UnlockSurface(SDL_Surface *surface)
{
    எனில் (!SDL_SurfaceValid(surface)) {
        திரும்பு;
    }

    // Only perform an unlock if we are locked
    எனில் (!surface->locked || (--surface->locked > 0)) {
        திரும்பு;
    }

    surface->flags &= ~SDL_SURFACE_LOCKED;
    SDL_UpdateSurfaceLockFlag(surface);
}

நிலையான bool SDL_FlipSurfaceHorizontal(SDL_Surface *surface)
{
    bool isstack;
    Uint8 *row, *a, *b, *tmp;
    முழு i, j, bpp;

    எனில் (SDL_BITSPERPIXEL(surface->format) < 8) {
        // We could implement this if needed, but we'd have to flip sets of bits within a byte
        திரும்பு SDL_Unsupported();
    }

    எனில் (surface->h <= 0) {
        திரும்பு true;
    }

    எனில் (surface->w <= 1) {
        திரும்பு true;
    }

    bpp = SDL_BYTESPERPIXEL(surface->format);
    row = (Uint8 *)surface->pixels;
    tmp = SDL_small_alloc(Uint8, surface->pitch, &isstack);
    எனில் (!tmp) {
        திரும்பு false;
    }
    க்கு (i = surface->h; i--; ) {
        a = row;
        b = a + (surface->w - 1) * bpp;
        க்கு (j = surface->w / 2; j--; ) {
            SDL_memcpy(tmp, a, bpp);
            SDL_memcpy(a, b, bpp);
            SDL_memcpy(b, tmp, bpp);
            a += bpp;
            b -= bpp;
        }
        row += surface->pitch;
    }
    SDL_small_free(tmp, isstack);
    திரும்பு true;
}

நிலையான bool SDL_FlipSurfaceVertical(SDL_Surface *surface)
{
    bool isstack;
    Uint8 *a, *b, *tmp;
    முழு i;

    எனில் (surface->h <= 1) {
        திரும்பு true;
    }

    a = (Uint8 *)surface->pixels;
    b = a + (surface->h - 1) * surface->pitch;
    tmp = SDL_small_alloc(Uint8, surface->pitch, &isstack);
    எனில் (!tmp) {
        திரும்பு false;
    }
    க்கு (i = surface->h / 2; i--; ) {
        SDL_memcpy(tmp, a, surface->pitch);
        SDL_memcpy(a, b, surface->pitch);
        SDL_memcpy(b, tmp, surface->pitch);
        a += surface->pitch;
        b -= surface->pitch;
    }
    SDL_small_free(tmp, isstack);
    திரும்பு true;
}

bool SDL_FlipSurface(SDL_Surface *surface, SDL_FlipMode flip)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        திரும்பு SDL_InvalidParamError("surface");
    }
    எனில் (!surface->pixels) {
        திரும்பு true;
    }

    bool result = true;
    தேர்வு (flip) {
    நிலை SDL_FLIP_HORIZONTAL:
        result = SDL_FlipSurfaceHorizontal(surface);
        நிறுத்து;
    நிலை SDL_FLIP_VERTICAL:
        result = SDL_FlipSurfaceVertical(surface);
        நிறுத்து;
    நிலை SDL_FLIP_HORIZONTAL_AND_VERTICAL:
        result &= SDL_FlipSurfaceHorizontal(surface);
        result &= SDL_FlipSurfaceVertical(surface);
        நிறுத்து;
    இயல்பு:
        result = SDL_InvalidParamError("flip");
        நிறுத்து;
    }
    திரும்பு result;
}

நிலையான SDL_Surface *SDL_ConvertSurfaceRectAndColorspace(SDL_Surface *surface, மாறிலி SDL_Rect *rect, SDL_PixelFormat format, SDL_Palette *palette, SDL_Colorspace colorspace, SDL_PropertiesID props)
{
    SDL_Palette *temp_palette = வெற்று;
    SDL_Surface *convert = வெற்று;
    SDL_Colorspace src_colorspace;
    SDL_PropertiesID src_properties;
    Uint32 copy_flags;
    SDL_Color copy_color;
    SDL_Rect bounds;
    bool result;
    bool palette_ck_transform = false;
    Uint8 palette_ck_மதிப்பு = 0;
    Uint8 *palette_saved_alpha = வெற்று;
    முழு palette_saved_alpha_ncolors = 0;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        செல் error;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        செல் error;
    }

    // Set the bounds of the new surface
    bounds.x = 0;
    bounds.y = 0;
    bounds.w = surface->w;
    bounds.h = surface->h;
    எனில் (rect) {
        bounds.w = rect->w;
        bounds.h = rect->h;
    } இல்லையெனில் {
        rect = &bounds;
    }

    // Check for empty destination palette! (results in empty image)
    எனில் (palette) {
        முழு i;
        க்கு (i = 0; i < palette->ncolors; ++i) {
            எனில் ((palette->colors[i].r != 0xFF) || (palette->colors[i].g != 0xFF) || (palette->colors[i].b != 0xFF)) {
                நிறுத்து;
            }
        }
        எனில் (i == palette->ncolors) {
            SDL_SetError("Empty destination palette");
            செல் error;
        }
    } இல்லையெனில் எனில் (SDL_ISPIXELFORMAT_INDEXED(format)) {
        // Create a dither palette for conversion
        temp_palette = SDL_CreatePalette(1 << SDL_BITSPERPIXEL(format));
        எனில் (temp_palette) {
            SDL_DitherPalette(temp_palette);
            palette = temp_palette;
        }
    }

    src_colorspace = surface->colorspace;
    src_properties = surface->props;

    // Create a new surface with the desired format
    எனில் (surface->pixels || SDL_MUSTLOCK(surface)) {
        convert = SDL_CreateSurfaceUninitialized(rect->w, rect->h, format);
    } இல்லையெனில் {
        convert = SDL_CreateSurfaceFrom(rect->w, rect->h, format, வெற்று, 0);
    }
    எனில் (!convert) {
        செல் error;
    }
    எனில் (SDL_ISPIXELFORMAT_INDEXED(format)) {
        SDL_SetSurfacePalette(convert, palette);
    }

    எனில் (colorspace == SDL_COLORSPACE_UNKNOWN) {
        colorspace = src_colorspace;
    }
    SDL_SetSurfaceColorspace(convert, colorspace);

    எனில் (SDL_ISPIXELFORMAT_FOURCC(format) || SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        எனில் (surface->format == SDL_PIXELFORMAT_MJPG && format == SDL_PIXELFORMAT_MJPG) {
            // Just do a straight pixel copy of the JPEG image
            size_t size = (size_t)surface->pitch;
            convert->pixels = SDL_malloc(size);
            எனில் (!convert->pixels) {
                செல் error;
            }
            convert->flags &= ~SDL_SURFACE_PREALLOCATED;
            convert->pitch = surface->pitch;
            SDL_memcpy(convert->pixels, surface->pixels, size);

        } இல்லையெனில் எனில் (!SDL_ConvertPixelsAndColorspace(surface->w, surface->h, surface->format, src_colorspace, src_properties, surface->pixels, surface->pitch, convert->format, colorspace, props, convert->pixels, convert->pitch)) {
            செல் error;
        }

        // Save the original copy flags
        copy_flags = surface->map.info.flags;

        செல் end;
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
    எனில் (surface->palette && SDL_ISPIXELFORMAT_ALPHA(format)) {
        bool set_opaque = false;

        bool is_opaque, has_alpha_channel;
        SDL_DetectPalette(surface->palette, &is_opaque, &has_alpha_channel);

        எனில் (is_opaque) {
            எனில் (!has_alpha_channel) {
                set_opaque = true;
            }
        }

        // Set opaque and backup palette alpha values
        எனில் (set_opaque) {
            முழு i;
            palette_saved_alpha_ncolors = surface->palette->ncolors;
            எனில் (palette_saved_alpha_ncolors > 0) {
                palette_saved_alpha = SDL_அடுக்கு_alloc(Uint8, palette_saved_alpha_ncolors);
                க்கு (i = 0; i < palette_saved_alpha_ncolors; i++) {
                    palette_saved_alpha[i] = surface->palette->colors[i].a;
                    surface->palette->colors[i].a = SDL_ALPHA_OPAQUE;
                }
            }
        }
    }

    // Transform colorkey to alpha. for cases where source palette has duplicate values, and colorkey is one of them
    எனில் (copy_flags & SDL_COPY_COLORKEY) {
        எனில் (surface->palette && !palette) {
            palette_ck_transform = true;
            palette_ck_மதிப்பு = surface->palette->colors[surface->map.info.colorkey].a;
            surface->palette->colors[surface->map.info.colorkey].a = SDL_ALPHA_TRANSPARENT;
        }
    }

    எனில் (surface->pixels || SDL_MUSTLOCK(surface)) {
        result = SDL_BlitSurfaceUnchecked(surface, rect, convert, &bounds);
    } இல்லையெனில் {
        result = true;
    }

    // Restore colorkey alpha value
    எனில் (palette_ck_transform) {
        surface->palette->colors[surface->map.info.colorkey].a = palette_ck_மதிப்பு;
    }

    // Restore palette alpha values
    எனில் (palette_saved_alpha) {
        முழு i;
        க்கு (i = 0; i < palette_saved_alpha_ncolors; i++) {
            surface->palette->colors[i].a = palette_saved_alpha[i];
        }
        SDL_அடுக்கு_free(palette_saved_alpha);
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
    எனில் (!result) {
        செல் error;
    }

    எனில் (copy_flags & SDL_COPY_COLORKEY) {
        bool set_colorkey_by_color = false;
        bool convert_colorkey = true;

        எனில் (surface->palette) {
            எனில் (palette &&
                surface->palette->ncolors <= palette->ncolors &&
                (SDL_memcmp(surface->palette->colors, palette->colors,
                            surface->palette->ncolors * அளவு(SDL_Color)) == 0)) {
                // The palette is identical, just set the same colorkey
                SDL_Set_Surface_Color_சாவி(convert, true, surface->map.info.colorkey);
            } இல்லையெனில் எனில் (!palette) {
                எனில் (SDL_ISPIXELFORMAT_ALPHA(format)) {
                    // No need to add the colorkey, transparency is in the alpha channel
                } இல்லையெனில் {
                    // Only set the colorkey information
                    set_colorkey_by_color = true;
                    convert_colorkey = false;
                }
            } இல்லையெனில் {
                set_colorkey_by_color = true;
            }
        } இல்லையெனில் {
            set_colorkey_by_color = true;
        }

        எனில் (set_colorkey_by_color) {
            SDL_Surface *tmp;
            SDL_Surface *tmp2;
            முழு converted_colorkey = 0;

            // Create a dummy surface to get the colorkey converted
            tmp = SDL_CreateSurfaceUninitialized(1, 1, surface->format);
            எனில் (!tmp) {
                செல் error;
            }

            // Share the palette, if any
            எனில் (surface->palette) {
                SDL_SetSurfacePalette(tmp, surface->palette);
            }

            SDL_FillSurfaceRect(tmp, வெற்று, surface->map.info.colorkey);

            tmp->map.info.flags &= ~SDL_COPY_COLORKEY;

            // Conversion of the colorkey
            tmp2 = SDL_ConvertSurfaceAndColorspace(tmp, format, palette, colorspace, props);
            எனில் (!tmp2) {
                SDL_DestroySurface(tmp);
                செல் error;
            }

            // Get the converted colorkey
            SDL_memcpy(&converted_colorkey, tmp2->pixels, tmp2->fmt->bytes_per_pixel);

            SDL_DestroySurface(tmp);
            SDL_DestroySurface(tmp2);

            // Set the converted colorkey on the new surface
            SDL_Set_Surface_Color_சாவி(convert, true, converted_colorkey);

            // This is needed when converting for 3D texture upload
            எனில் (convert_colorkey) {
                SDL_ConvertColorkeyToAlpha(convert, true);
            }
        }
    }

end:
    எனில் (temp_palette) {
        SDL_DestroyPalette(temp_palette);
    }

    SDL_SetSurfaceClipRect(convert, &surface->clip_rect);

    /* Enable alpha blending by default if the new surface has an
     * alpha channel or alpha modulation */
    எனில் (SDL_ISPIXELFORMAT_ALPHA(format) ||
        (copy_flags & SDL_COPY_MODULATE_ALPHA)) {
        SDL_SetSurfaceBlendMode(convert, SDL_BLENDMODE_BLEND);
    }
    எனில் (copy_flags & SDL_COPY_RLE_DESIRED) {
        SDL_SetSurfaceRLE(convert, true);
    }

    // Copy alternate images
    க்கு (முழு i = 0; i < surface->இலக்கம்_images; ++i) {
        எனில் (!SDL_AddSurfaceAlternateImage(convert, surface->images[i])) {
            செல் error;
        }
    }

    // Copy properties
    எனில் (surface->props) {
        எனில் (!SDL_CopyProperties(surface->props, SDL_GetSurfaceProperties(convert))) {
            செல் error;
        }

        // Make sure the new surface doesn't reference an old SDL2 surface.
        SDL_ClearProperty(SDL_GetSurfaceProperties(convert), "sdl2-compat.surface2");
    }

    // We're ready to go!
    திரும்பு convert;

error:
    எனில் (temp_palette) {
        SDL_DestroyPalette(temp_palette);
    }
    எனில் (convert) {
        SDL_DestroySurface(convert);
    }
    திரும்பு வெற்று;
}

SDL_Surface *SDL_ConvertSurfaceAndColorspace(SDL_Surface *surface, SDL_PixelFormat format, SDL_Palette *palette, SDL_Colorspace colorspace, SDL_PropertiesID props)
{
    திரும்பு SDL_ConvertSurfaceRectAndColorspace(surface, வெற்று, format, palette, colorspace, props);
}

SDL_Surface *SDL_RotateSurface(SDL_Surface *surface, தசம angle)
{
    SDL_Surface *rotated = வெற்று;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        திரும்பு வெற்று;
    }

    SDL_Rect rect_dest;
    இரட்டை cangle, sangle;
    SDL_FPoint center = { surface->w * 0.5f, surface->h * 0.5f };
    SDLgfx_rotozoomSurfaceSizeTrig(surface->w, surface->h, angle, &center, &rect_dest, &cangle, &sangle);

    // This function requires a 32-bit surface or 8-bit surface with a colorkey
    எனில் ((SDL_BITSPERPIXEL(surface->format) == 32 && SDL_PIXELLAYOUT(surface->format) == SDL_PACKEDLAYOUT_8888) ||
        (surface->format == SDL_PIXELFORMAT_INDEX8 && SDL_Surface_Has_Color_சாவி(surface))) {
        rotated = SDLgfx_rotateSurface(surface, angle, 1, 0, 0, &rect_dest, cangle, sangle, &center);
    } இல்லையெனில் {
        SDL_Surface *convert = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);
        எனில் (convert) {
            SDL_Surface *tmp = SDLgfx_rotateSurface(convert, angle, 1, 0, 0, &rect_dest, cangle, sangle, &center);
            எனில் (tmp) {
                rotated = SDL_ConvertSurfaceAndColorspace(tmp, surface->format, surface->palette, surface->colorspace, surface->props);
                SDL_DestroySurface(tmp);
            }
            SDL_DestroySurface(convert);
        }
    }

    எனில் (rotated) {
        எனில் (SDL_HasProperty(surface->props, SDL_PROP_SURFACE_ROTATION_FLOAT)) {
            மாறிலி தசம rotation = (SDL_Get_எண்_Property(surface->props, SDL_PROP_SURFACE_ROTATION_FLOAT, 0) - angle);
            SDL_SetFloatProperty(SDL_GetSurfaceProperties(rotated), SDL_PROP_SURFACE_ROTATION_FLOAT, rotation);
        }
    }

    திரும்பு rotated;
}

SDL_Surface *SDL_DuplicateSurface(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        திரும்பு வெற்று;
    }

    திரும்பு SDL_ConvertSurfaceAndColorspace(surface, surface->format, surface->palette, surface->colorspace, surface->props);
}

SDL_Surface *SDL_ScaleSurface(SDL_Surface *surface, முழு width, முழு height, SDL_ScaleMode scaleMode)
{
    SDL_Surface *convert = வெற்று;
    Uint32 copy_flags;
    SDL_Color copy_color;
    bool rc;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        செல் error;
    }

    எனில் (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // We can't directly scale a YUV surface (yet!)
        SDL_Surface *tmp = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        எனில் (!tmp) {
            திரும்பு வெற்று;
        }

        SDL_Surface *scaled = SDL_ScaleSurface(tmp, width, height, scaleMode);
        SDL_DestroySurface(tmp);
        எனில் (!scaled) {
            திரும்பு வெற்று;
        }

        SDL_Surface *result = SDL_ConvertSurfaceAndColorspace(scaled, surface->format, வெற்று, surface->colorspace, surface->props);
        SDL_DestroySurface(scaled);
        திரும்பு result;
    }

    எனில் (SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        // Linear scaling requires conversion to RGBA and then slow pixel color lookup
        scaleMode = SDL_SCALEMODE_NEAREST;
    }

    // Create a new surface with the desired size
    எனில் (surface->pixels || SDL_MUSTLOCK(surface)) {
        convert = SDL_CreateSurfaceUninitialized(width, height, surface->format);
    } இல்லையெனில் {
        convert = SDL_CreateSurfaceFrom(width, height, surface->format, வெற்று, 0);
    }
    எனில் (!convert) {
        செல் error;
    }
    SDL_SetSurfacePalette(convert, surface->palette);
    SDL_SetSurfaceColorspace(convert, surface->colorspace);
    SDL_SetSurfaceRLE(convert, SDL_SurfaceHasRLE(surface));

    எனில் (surface->pixels || SDL_MUSTLOCK(surface)) {
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

        rc = SDL_BlitSurfaceScaled(surface, வெற்று, convert, வெற்று, scaleMode);

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
    } இல்லையெனில் {
        rc = true;
    }

    // SDL_BlitSurfaceScaled failed, and so the conversion
    எனில் (!rc) {
        செல் error;
    }

    // We're ready to go!
    திரும்பு convert;

error:
    எனில் (convert) {
        SDL_DestroySurface(convert);
    }
    திரும்பு வெற்று;
}

SDL_Surface *SDL_ConvertSurfaceRect(SDL_Surface *surface, மாறிலி SDL_Rect *rect, SDL_PixelFormat format)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        திரும்பு வெற்று;
    }

    திரும்பு SDL_ConvertSurfaceRectAndColorspace(surface, rect, format, வெற்று, SDL_GetDefaultColorspaceForFormat(format), surface->props);
}

SDL_Surface *SDL_ConvertSurface(SDL_Surface *surface, SDL_PixelFormat format)
{
    திரும்பு SDL_ConvertSurfaceRect(surface, வெற்று, format);
}

SDL_Surface *SDL_DuplicatePixels(முழு width, முழு height, SDL_PixelFormat format, SDL_Colorspace colorspace, வெறுமை *pixels, முழு pitch)
{
    SDL_Surface *surface;
    எனில் (pixels) {
        surface = SDL_CreateSurfaceUninitialized(width, height, format);
    } இல்லையெனில் {
        surface = SDL_CreateSurfaceFrom(width, height, format, வெற்று, 0);
    }
    எனில் (!surface) {
        திரும்பு வெற்று;
    }
    SDL_SetSurfaceColorspace(surface, colorspace);

    எனில் (surface->pixels) {
        முழு length = width * SDL_BYTESPERPIXEL(format);
        Uint8 *src = (Uint8 *)pixels;
        Uint8 *dst = (Uint8 *)surface->pixels;
        முழு rows = height;
        போது (rows--) {
            SDL_memcpy(dst, src, length);
            dst += surface->pitch;
            src += pitch;
        }
    }
    திரும்பு surface;
}

bool SDL_ConvertPixelsAndColorspace(முழு width, முழு height,
                      SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, மாறிலி வெறுமை *src, முழு src_pitch,
                      SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, வெறுமை *dst, முழு dst_pitch)
{
    SDL_Surface src_surface;
    SDL_Surface dst_surface;
    SDL_Rect rect;
    வெறுமை *nonconst_src = (வெறுமை *)src;
    bool result;

    CHECK_PARAM(!src) {
        திரும்பு SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!src_pitch) {
        திரும்பு SDL_InvalidParamError("src_pitch");
    }
    CHECK_PARAM(!dst) {
        திரும்பு SDL_InvalidParamError("dst");
    }
    CHECK_PARAM(!dst_pitch) {
        திரும்பு SDL_InvalidParamError("dst_pitch");
    }

    எனில் (src_colorspace == SDL_COLORSPACE_UNKNOWN) {
        src_colorspace = SDL_GetDefaultColorspaceForFormat(src_format);
    }
    எனில் (dst_colorspace == SDL_COLORSPACE_UNKNOWN) {
        dst_colorspace = SDL_GetDefaultColorspaceForFormat(dst_format);
    }

    எனில் (src_format == SDL_PIXELFORMAT_MJPG) {
        திரும்பு SDL_ConvertPixels_STB(width, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    }

#ifdef SDL_HAVE_YUV
    எனில் (SDL_ISPIXELFORMAT_FOURCC(src_format) && SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        திரும்பு SDL_ConvertPixels_YUV_to_YUV(width, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } இல்லையெனில் எனில் (SDL_ISPIXELFORMAT_FOURCC(src_format)) {
        திரும்பு SDL_ConvertPixels_YUV_to_RGB(width, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } இல்லையெனில் எனில் (SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        திரும்பு SDL_ConvertPixels_RGB_to_YUV(width, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    }
#இல்லையெனில்
    எனில் (SDL_ISPIXELFORMAT_FOURCC(src_format) || SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        திரும்பு SDL_SetError("SDL not built with YUV support");
    }
#endif

    // Fast path for same format copy
    எனில் (src_format == dst_format && src_colorspace == dst_colorspace) {
        எனில் (src_pitch == dst_pitch) {
            SDL_memcpy(dst, src, height * src_pitch);
        } இல்லையெனில் {
            முழு i;
            மாறிலி முழு bpp = SDL_BYTESPERPIXEL(src_format);
            width *= bpp;
            க்கு (i = height; i--;) {
                SDL_memcpy(dst, src, width);
                src = (மாறிலி Uint8 *)src + src_pitch;
                dst = (Uint8 *)dst + dst_pitch;
            }
        }
        திரும்பு true;
    }

    எனில் (!SDL_InitializeSurface(&src_surface, width, height, src_format, src_colorspace, src_properties, nonconst_src, src_pitch, true)) {
        திரும்பு false;
    }
    SDL_SetSurfaceBlendMode(&src_surface, SDL_BLENDMODE_NONE);

    எனில் (!SDL_InitializeSurface(&dst_surface, width, height, dst_format, dst_colorspace, dst_properties, dst, dst_pitch, true)) {
        திரும்பு false;
    }

    // Set up the rect and go!
    rect.x = 0;
    rect.y = 0;
    rect.w = width;
    rect.h = height;
    result = SDL_BlitSurfaceUnchecked(&src_surface, &rect, &dst_surface, &rect);

    SDL_DestroySurface(&src_surface);
    SDL_DestroySurface(&dst_surface);

    திரும்பு result;
}

bool SDL_ConvertPixels(முழு width, முழு height, SDL_PixelFormat src_format, மாறிலி வெறுமை *src, முழு src_pitch, SDL_PixelFormat dst_format, வெறுமை *dst, முழு dst_pitch)
{
    திரும்பு SDL_ConvertPixelsAndColorspace(width, height,
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

நிலையான வெறுமை SDL_PremultiplyAlpha_AXYZ8888(முழு width, முழு height, மாறிலி வெறுமை *src, முழு src_pitch, வெறுமை *dst, முழு dst_pitch)
{
    முழு c;
    Uint32 srcpixel;
    Uint32 srcR, srcG, srcB, srcA;
    Uint32 dstpixel;
    Uint32 dstR, dstG, dstB, dstA;

    போது (height--) {
        மாறிலி Uint32 *src_px = (மாறிலி Uint32 *)src;
        Uint32 *dst_px = (Uint32 *)dst;
        க்கு (c = width; c; --c) {
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
        src = (மாறிலி Uint8 *)src + src_pitch;
        dst = (Uint8 *)dst + dst_pitch;
    }
}

நிலையான வெறுமை SDL_PremultiplyAlpha_XYZA8888(முழு width, முழு height, மாறிலி வெறுமை *src, முழு src_pitch, வெறுமை *dst, முழு dst_pitch)
{
    முழு c;
    Uint32 srcpixel;
    Uint32 srcR, srcG, srcB, srcA;
    Uint32 dstpixel;
    Uint32 dstR, dstG, dstB, dstA;

    போது (height--) {
        மாறிலி Uint32 *src_px = (மாறிலி Uint32 *)src;
        Uint32 *dst_px = (Uint32 *)dst;
        க்கு (c = width; c; --c) {
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
        src = (மாறிலி Uint8 *)src + src_pitch;
        dst = (Uint8 *)dst + dst_pitch;
    }
}

நிலையான வெறுமை SDL_PremultiplyAlpha_AXYZ128(முழு width, முழு height, மாறிலி வெறுமை *src, முழு src_pitch, வெறுமை *dst, முழு dst_pitch)
{
    முழு c;
    தசம flR, flG, flB, flA;

    போது (height--) {
        மாறிலி தசம *src_px = (மாறிலி தசம *)src;
        தசம *dst_px = (தசம *)dst;
        க்கு (c = width; c; --c) {
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
        src = (மாறிலி Uint8 *)src + src_pitch;
        dst = (Uint8 *)dst + dst_pitch;
    }
}

நிலையான bool SDL_PremultiplyAlphaPixelsAndColorspace(முழு width, முழு height, SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, மாறிலி வெறுமை *src, முழு src_pitch, SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, வெறுமை *dst, முழு dst_pitch, bool linear)
{
    SDL_Surface *convert = வெற்று;
    வெறுமை *final_dst = dst;
    முழு final_dst_pitch = dst_pitch;
    SDL_PixelFormat format;
    SDL_Colorspace colorspace;
    bool result = false;

    CHECK_PARAM(!src) {
        திரும்பு SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!src_pitch) {
        திரும்பு SDL_InvalidParamError("src_pitch");
    }
    CHECK_PARAM(!dst) {
        திரும்பு SDL_InvalidParamError("dst");
    }
    CHECK_PARAM(!dst_pitch) {
        திரும்பு SDL_InvalidParamError("dst_pitch");
    }

    // Use a high precision format if we're converting to linear colorspace or using high precision pixel formats
    எனில் (linear ||
        SDL_ISPIXELFORMAT_10BIT(src_format) || SDL_BITSPERPIXEL(src_format) > 32 ||
        SDL_ISPIXELFORMAT_10BIT(dst_format) || SDL_BITSPERPIXEL(dst_format) > 32) {
        எனில் (src_format == SDL_PIXELFORMAT_ARGB128_FLOAT ||
            src_format == SDL_PIXELFORMAT_ABGR128_FLOAT) {
            format = src_format;
        } இல்லையெனில் {
            format = SDL_PIXELFORMAT_ARGB128_FLOAT;
        }
    } இல்லையெனில் {
        எனில் (src_format == SDL_PIXELFORMAT_ARGB8888 ||
            src_format == SDL_PIXELFORMAT_ABGR8888 ||
            src_format == SDL_PIXELFORMAT_RGBA8888 ||
            src_format == SDL_PIXELFORMAT_BGRA8888) {
            format = src_format;
        } இல்லையெனில் {
            format = SDL_PIXELFORMAT_ARGB8888;
        }
    }
    எனில் (linear) {
        colorspace = SDL_COLORSPACE_SRGB_LINEAR;
    } இல்லையெனில் {
        colorspace = SDL_COLORSPACE_SRGB;
    }

    எனில் (src_format != format || src_colorspace != colorspace) {
        convert = SDL_CreateSurfaceUninitialized(width, height, format);
        எனில் (!convert) {
            செல் done;
        }
        எனில் (!SDL_ConvertPixelsAndColorspace(width, height, src_format, src_colorspace, src_properties, src, src_pitch, format, colorspace, 0, convert->pixels, convert->pitch)) {
            செல் done;
        }

        src = convert->pixels;
        src_pitch = convert->pitch;
        dst = convert->pixels;
        dst_pitch = convert->pitch;

    } இல்லையெனில் எனில் (dst_format != format || dst_colorspace != colorspace) {
        convert = SDL_CreateSurfaceUninitialized(width, height, format);
        எனில் (!convert) {
            செல் done;
        }
        dst = convert->pixels;
        dst_pitch = convert->pitch;
    }

    தேர்வு (format) {
    நிலை SDL_PIXELFORMAT_ARGB8888:
    நிலை SDL_PIXELFORMAT_ABGR8888:
        SDL_PremultiplyAlpha_AXYZ8888(width, height, src, src_pitch, dst, dst_pitch);
        நிறுத்து;
    நிலை SDL_PIXELFORMAT_RGBA8888:
    நிலை SDL_PIXELFORMAT_BGRA8888:
        SDL_PremultiplyAlpha_XYZA8888(width, height, src, src_pitch, dst, dst_pitch);
        நிறுத்து;
    நிலை SDL_PIXELFORMAT_ARGB128_FLOAT:
    நிலை SDL_PIXELFORMAT_ABGR128_FLOAT:
        SDL_PremultiplyAlpha_AXYZ128(width, height, src, src_pitch, dst, dst_pitch);
        நிறுத்து;
    இயல்பு:
        SDL_SetError("Unexpected internal pixel format");
        செல் done;
    }

    எனில் (dst != final_dst) {
        எனில் (!SDL_ConvertPixelsAndColorspace(width, height, format, colorspace, 0, convert->pixels, convert->pitch, dst_format, dst_colorspace, dst_properties, final_dst, final_dst_pitch)) {
            செல் done;
        }
    }
    result = true;

done:
    எனில் (convert) {
        SDL_DestroySurface(convert);
    }
    திரும்பு result;
}

bool SDL_PremultiplyAlpha(முழு width, முழு height,
                         SDL_PixelFormat src_format, மாறிலி வெறுமை *src, முழு src_pitch,
                         SDL_PixelFormat dst_format, வெறுமை *dst, முழு dst_pitch, bool linear)
{
    SDL_Colorspace src_colorspace = SDL_GetDefaultColorspaceForFormat(src_format);
    SDL_Colorspace dst_colorspace = SDL_GetDefaultColorspaceForFormat(dst_format);

    திரும்பு SDL_PremultiplyAlphaPixelsAndColorspace(width, height, src_format, src_colorspace, 0, src, src_pitch, dst_format, dst_colorspace, 0, dst, dst_pitch, linear);
}

bool SDL_PremultiplySurfaceAlpha(SDL_Surface *surface, bool linear)
{
    SDL_Colorspace colorspace;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        திரும்பு SDL_InvalidParamError("surface");
    }

    colorspace = surface->colorspace;

    திரும்பு SDL_PremultiplyAlphaPixelsAndColorspace(surface->w, surface->h, surface->format, colorspace, surface->props, surface->pixels, surface->pitch, surface->format, colorspace, surface->props, surface->pixels, surface->pitch, linear);
}

bool SDL_ClearSurface(SDL_Surface *surface, தசம r, தசம g, தசம b, தசம a)
{
    SDL_Rect clip_rect;
    bool result = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        திரும்பு SDL_InvalidParamError("surface");
    }

    SDL_GetSurfaceClipRect(surface, &clip_rect);
    SDL_SetSurfaceClipRect(surface, வெற்று);

    எனில் (!SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_BYTESPERPIXEL(surface->format) <= அளவு(Uint32)) {
        Uint32 color;

        color = SDL_MapSurfaceRGBA(surface,
                    (Uint8)SDL_roundf(SDL_clamp(r, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(g, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(b, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(a, 0.0f, 1.0f) * 255.0f));
        result = SDL_FillSurfaceRect(surface, வெற்று, color);
    } இல்லையெனில் எனில் (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // We can't directly set an RGB value on a YUV surface
        SDL_Surface *tmp = SDL_CreateSurfaceUninitialized(surface->w, surface->h, SDL_PIXELFORMAT_ARGB8888);
        எனில் (!tmp) {
            செல் done;
        }

        எனில் (SDL_ClearSurface(tmp, r, g, b, a)) {
            result = SDL_ConvertPixelsAndColorspace(surface->w, surface->h, tmp->format, tmp->colorspace, tmp->props, tmp->pixels, tmp->pitch, surface->format, surface->colorspace, surface->props, surface->pixels, surface->pitch);
        }
        SDL_DestroySurface(tmp);
    } இல்லையெனில் {
        // Take advantage of blit color conversion
        SDL_Surface *tmp = SDL_CreateSurfaceUninitialized(1, 1, SDL_PIXELFORMAT_RGBA128_FLOAT);
        எனில் (!tmp) {
            செல் done;
        }
        SDL_SetSurfaceColorspace(tmp, surface->colorspace);
        SDL_SetSurfaceBlendMode(tmp, SDL_BLENDMODE_NONE);

        தசம *pixels = (தசம *)tmp->pixels;
        pixels[0] = r;
        pixels[1] = g;
        pixels[2] = b;
        pixels[3] = a;

        result = SDL_BlitSurfaceScaled(tmp, வெற்று, surface, வெற்று, SDL_SCALEMODE_NEAREST);
        SDL_DestroySurface(tmp);
    }

done:
    SDL_SetSurfaceClipRect(surface, &clip_rect);

    திரும்பு result;
}

Uint32 SDL_MapSurfaceRGB(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b)
{
    திரும்பு SDL_MapSurfaceRGBA(surface, r, g, b, SDL_ALPHA_OPAQUE);
}

Uint32 SDL_MapSurfaceRGBA(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        திரும்பு true;
    }
    திரும்பு SDL_MapRGBA(surface->fmt, surface->palette, r, g, b, a);
}

// This function Copyright 2023 Collabora Ltd., contributed to SDL under the ZLib license
bool SDL_ReadSurfacePixel(SDL_Surface *surface, முழு x, முழு y, Uint8 *r, Uint8 *g, Uint8 *b, Uint8 *a)
{
    Uint32 pixel = 0;
    size_t bytes_per_pixel;
    Uint8 unused;
    Uint8 *p;
    bool result = false;

    எனில் (r) {
        *r = 0;
    } இல்லையெனில் {
        r = &unused;
    }

    எனில் (g) {
        *g = 0;
    } இல்லையெனில் {
        g = &unused;
    }

    எனில் (b) {
        *b = 0;
    } இல்லையெனில் {
        b = &unused;
    }

    எனில் (a) {
        *a = 0;
    } இல்லையெனில் {
        a = &unused;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        திரும்பு SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        திரும்பு SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        திரும்பு SDL_InvalidParamError("y");
    }

    bytes_per_pixel = SDL_BYTESPERPIXEL(surface->format);

    எனில் (SDL_MUSTLOCK(surface)) {
        எனில் (!SDL_LockSurface(surface)) {
            திரும்பு false;
        }
    }

    p = (Uint8 *)surface->pixels + y * surface->pitch + x * bytes_per_pixel;

    எனில் (bytes_per_pixel <= அளவு(pixel) &&
        !SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_COLORSPACEPRIMARIES(surface->colorspace) == SDL_COLOR_PRIMARIES_BT709) {
        /* Fill the appropriate number of least-significant bytes of pixel,
         * leaving the most-significant bytes set to zero */
#எனில் SDL_BYTEORDER == SDL_BIG_ENDIAN
        SDL_memcpy(((Uint8 *)&pixel) + (அளவு(pixel) - bytes_per_pixel), p, bytes_per_pixel);
#இல்லையெனில்
        SDL_memcpy(&pixel, p, bytes_per_pixel);
#endif
        SDL_GetRGBA(pixel, surface->fmt, surface->palette, r, g, b, a);
        result = true;
    } இல்லையெனில் எனில் (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // FIXME: We need code to extract a single macroblock from a YUV surface
        SDL_Surface *converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        எனில் (converted) {
            result = SDL_ReadSurfacePixel(converted, x, y, r, g, b, a);
            SDL_DestroySurface(converted);
        }
    } இல்லையெனில் {
        // This is really slow, but it gets the job done
        Uint8 rgba[4];

        எனில் (SDL_ConvertPixelsAndColorspace(1, 1, surface->format, surface->colorspace, surface->props, p, surface->pitch, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, rgba, அளவு(rgba))) {
            *r = rgba[0];
            *g = rgba[1];
            *b = rgba[2];
            *a = rgba[3];
            result = true;
        }
    }

    எனில் (SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }
    திரும்பு result;
}

bool SDL_ReadSurfacePixelFloat(SDL_Surface *surface, முழு x, முழு y, தசம *r, தசம *g, தசம *b, தசம *a)
{
    தசம unused;
    bool result = false;

    எனில் (r) {
        *r = 0.0f;
    } இல்லையெனில் {
        r = &unused;
    }

    எனில் (g) {
        *g = 0.0f;
    } இல்லையெனில் {
        g = &unused;
    }

    எனில் (b) {
        *b = 0.0f;
    } இல்லையெனில் {
        b = &unused;
    }

    எனில் (a) {
        *a = 0.0f;
    } இல்லையெனில் {
        a = &unused;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        திரும்பு SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        திரும்பு SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        திரும்பு SDL_InvalidParamError("y");
    }

    எனில் (SDL_BYTESPERPIXEL(surface->format) <= அளவு(Uint32) &&
        !SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_COLORSPACEPRIMARIES(surface->colorspace) == SDL_COLOR_PRIMARIES_BT709) {
        Uint8 r8, g8, b8, a8;

        எனில் (SDL_ReadSurfacePixel(surface, x, y, &r8, &g8, &b8, &a8)) {
            *r = (தசம)r8 / 255.0f;
            *g = (தசம)g8 / 255.0f;
            *b = (தசம)b8 / 255.0f;
            *a = (தசம)a8 / 255.0f;
            result = true;
        }
    } இல்லையெனில் எனில் (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // FIXME: We need code to extract a single macroblock from a YUV surface
        SDL_Surface *converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        எனில் (converted) {
            result = SDL_ReadSurfacePixelFloat(converted, x, y, r, g, b, a);
            SDL_DestroySurface(converted);
        }
    } இல்லையெனில் {
        // This is really slow, but it gets the job done
        தசம rgba[4];
        Uint8 *p;

        எனில் (SDL_MUSTLOCK(surface)) {
            எனில் (!SDL_LockSurface(surface)) {
                திரும்பு false;
            }
        }

        p = (Uint8 *)surface->pixels + y * surface->pitch + x * SDL_BYTESPERPIXEL(surface->format);

        எனில் (surface->format == SDL_PIXELFORMAT_RGBA128_FLOAT) {
            SDL_memcpy(rgba, p, அளவு(rgba));
            result = true;
        } இல்லையெனில் {
            SDL_Colorspace src_colorspace = surface->colorspace;
            SDL_Colorspace dst_colorspace = (src_colorspace == SDL_COLORSPACE_SRGB_LINEAR ? SDL_COLORSPACE_SRGB_LINEAR : SDL_COLORSPACE_SRGB);

            எனில் (SDL_ConvertPixelsAndColorspace(1, 1, surface->format, src_colorspace, surface->props, p, surface->pitch, SDL_PIXELFORMAT_RGBA128_FLOAT, dst_colorspace, 0, rgba, அளவு(rgba))) {
                result = true;
            }
        }

        எனில் (result) {
            *r = rgba[0];
            *g = rgba[1];
            *b = rgba[2];
            *a = rgba[3];
        }

        எனில் (SDL_MUSTLOCK(surface)) {
            SDL_UnlockSurface(surface);
        }
    }
    திரும்பு result;
}

bool SDL_WriteSurfacePixel(SDL_Surface *surface, முழு x, முழு y, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    Uint32 pixel = 0;
    size_t bytes_per_pixel;
    Uint8 *p;
    bool result = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        திரும்பு SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        திரும்பு SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        திரும்பு SDL_InvalidParamError("y");
    }

    bytes_per_pixel = SDL_BYTESPERPIXEL(surface->format);

    எனில் (SDL_MUSTLOCK(surface)) {
        எனில் (!SDL_LockSurface(surface)) {
            திரும்பு false;
        }
    }

    p = (Uint8 *)surface->pixels + y * surface->pitch + x * bytes_per_pixel;

    எனில் (bytes_per_pixel <= அளவு(pixel) && !SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        pixel = SDL_MapRGBA(surface->fmt, surface->palette, r, g, b, a);
#எனில் SDL_BYTEORDER == SDL_BIG_ENDIAN
        SDL_memcpy(p, ((Uint8 *)&pixel) + (அளவு(pixel) - bytes_per_pixel), bytes_per_pixel);
#இல்லையெனில்
        SDL_memcpy(p, &pixel, bytes_per_pixel);
#endif
        result = true;
    } இல்லையெனில் எனில் (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        result = SDL_Unsupported();
    } இல்லையெனில் {
        // This is really slow, but it gets the job done
        Uint8 rgba[4];

        rgba[0] = r;
        rgba[1] = g;
        rgba[2] = b;
        rgba[3] = a;
        result = SDL_ConvertPixelsAndColorspace(1, 1, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, rgba, அளவு(rgba), surface->format, surface->colorspace, surface->props, p, surface->pitch);
    }

    எனில் (SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }
    திரும்பு result;
}

bool SDL_WriteSurfacePixelFloat(SDL_Surface *surface, முழு x, முழு y, தசம r, தசம g, தசம b, தசம a)
{
    bool result = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        திரும்பு SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        திரும்பு SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        திரும்பு SDL_InvalidParamError("y");
    }

    எனில் (SDL_BYTESPERPIXEL(surface->format) <= அளவு(Uint32) && !SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        Uint8 r8, g8, b8, a8;

        r8 = (Uint8)SDL_round(SDL_clamp(r, 0.0f, 1.0f) * 255.0f);
        g8 = (Uint8)SDL_round(SDL_clamp(g, 0.0f, 1.0f) * 255.0f);
        b8 = (Uint8)SDL_round(SDL_clamp(b, 0.0f, 1.0f) * 255.0f);
        a8 = (Uint8)SDL_round(SDL_clamp(a, 0.0f, 1.0f) * 255.0f);
        எனில் (SDL_WriteSurfacePixel(surface, x, y, r8, g8, b8, a8)) {
            result = true;
        }
    } இல்லையெனில் எனில் (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        result = SDL_Unsupported();
    } இல்லையெனில் {
        // This is really slow, but it gets the job done
        தசம rgba[4];
        Uint8 *p;

        எனில் (SDL_MUSTLOCK(surface)) {
            எனில் (!SDL_LockSurface(surface)) {
                திரும்பு false;
            }
        }

        p = (Uint8 *)surface->pixels + y * surface->pitch + x * SDL_BYTESPERPIXEL(surface->format);

        rgba[0] = r;
        rgba[1] = g;
        rgba[2] = b;
        rgba[3] = a;

        எனில் (surface->format == SDL_PIXELFORMAT_RGBA128_FLOAT) {
            SDL_memcpy(p, rgba, அளவு(rgba));
            result = true;
        } இல்லையெனில் {
            SDL_Colorspace dst_colorspace = surface->colorspace;
            SDL_Colorspace src_colorspace = (dst_colorspace == SDL_COLORSPACE_SRGB_LINEAR ? SDL_COLORSPACE_SRGB_LINEAR : SDL_COLORSPACE_SRGB);

            result = SDL_ConvertPixelsAndColorspace(1, 1, SDL_PIXELFORMAT_RGBA128_FLOAT, src_colorspace, 0, rgba, அளவு(rgba), surface->format, dst_colorspace, surface->props, p, surface->pitch);
        }

        எனில் (SDL_MUSTLOCK(surface)) {
            SDL_UnlockSurface(surface);
        }
    }
    திரும்பு result;
}

/*
 * Free a surface created by the above function.
 */
வெறுமை SDL_DestroySurface(SDL_Surface *surface)
{
    எனில் (!SDL_SurfaceValid(surface)) {
        திரும்பு;
    }
    எனில் (surface->internal_flags & SDL_INTERNAL_SURFACE_DONTFREE) {
        திரும்பு;
    }
    எனில் (--surface->refcount > 0) {
        திரும்பு;
    }

    SDL_RemoveSurfaceAlternateImages(surface);

    SDL_DestroyProperties(surface->props);

    SDL_InvalidateMap(&surface->map);

    போது (surface->locked > 0) {
        SDL_UnlockSurface(surface);
    }
#ifdef SDL_HAVE_RLE
    எனில் (surface->internal_flags & SDL_INTERNAL_SURFACE_RLEACCEL) {
        SDL_UnRLESurface(surface);
    }
#endif
    SDL_SetSurfacePalette(surface, வெற்று);

    எனில் (surface->flags & SDL_SURFACE_PREALLOCATED) {
        // Don't free
    } இல்லையெனில் எனில் (surface->flags & SDL_SURFACE_SIMD_ALIGNED) {
        // Free aligned
        SDL_aligned_free(surface->pixels);
    } இல்லையெனில் {
        // Normal
        SDL_free(surface->pixels);
    }

    surface->reserved = வெற்று;

    எனில் (!(surface->internal_flags & SDL_INTERNAL_SURFACE_அடுக்கு)) {
        SDL_free(surface);
    }
}

SDL_Surface *SDL_LoadSurface_IO(SDL_IOStream *src, bool closeio)
{
    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        திரும்பு வெற்று;
    }

    எனில் (SDL_IsBMP(src)) {
        திரும்பு SDL_LoadBMP_IO(src, closeio);
    } இல்லையெனில் எனில் (SDL_IsPNG(src)) {
        திரும்பு SDL_LoadPNG_IO(src, closeio);
    } இல்லையெனில் எனில் (SDL_IsJPG(src)) {
        திரும்பு SDL_LoadJPG_IO(src, closeio);
    } இல்லையெனில் {
        எனில் (closeio) {
            SDL_CloseIO(src);
        }
        SDL_SetError("Unsupported image format");
        திரும்பு வெற்று;
    }
}

SDL_Surface *SDL_LoadSurface(மாறிலி எழுத்து *file)
{
    SDL_IOStream *stream = SDL_IOFromFile(file, "rb");
    எனில் (!stream) {
        திரும்பு வெற்று;
    }

    திரும்பு SDL_LoadSurface_IO(stream, true);
}
