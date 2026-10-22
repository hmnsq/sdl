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
#അന്തര്ഭാവ "SDL_internal.h"

#അന്തര്ഭാവ "SDL_sysvideo.h"
#അന്തര്ഭാവ "SDL_video_c.h"
#അന്തര്ഭാവ "SDL_RLEaccel_c.h"
#അന്തര്ഭാവ "SDL_pixels_c.h"
#അന്തര്ഭാവ "SDL_rotate.h"
#അന്തര്ഭാവ "SDL_stb_c.h"
#അന്തര്ഭാവ "SDL_yuv_c.h"
#അന്തര്ഭാവ "../render/SDL_sysrender.h"

#അന്തര്ഭാവ "SDL_surface_c.h"


// Check to make sure we can safely check multiplication of surface w and pitch and it won't overflow size_t
SDL_COMPILE_TIME_ASSERT(surface_size_assumptions,
                        വലുപ്പം(പൂർണ്ണസംഖ്യ) == വലുപ്പം(Sint32) && വലുപ്പം(size_t) >= വലുപ്പം(Sint32));

SDL_COMPILE_TIME_ASSERT(can_indicate_overflow, SDL_SIZE_MAX > SDL_MAX_SINT32);

// Magic!
സ്ഥിതം അക്ഷരം SDL_surface_magic;

// Public routines

bool SDL_SurfaceValid(SDL_Surface *surface)
{
    തിരികെ (surface && surface->reserved == &SDL_surface_magic);
}

ശൂന്യം SDL_UpdateSurfaceLockFlag(SDL_Surface *surface)
{
    // We need to mark the surface as needing unlock while locked
    എങ്കിൽ ((surface->flags & SDL_SURFACE_LOCKED) ||
        (surface->internal_flags & SDL_INTERNAL_SURFACE_RLEACCEL)) {
        surface->flags |= SDL_SURFACE_LOCK_NEEDED;
    } അല്ലെങ്കിൽ {
        surface->flags &= ~SDL_SURFACE_LOCK_NEEDED;
    }
}

/*
 * Calculate the pad-aligned scanline width of a surface.
 *
 * for FOURCC, use SDL_CalculateYUVSize()
 */
സ്ഥിതം bool SDL_CalculateRGBSize(Uint32 format, size_t width, size_t height, size_t *size, size_t *pitch, bool minimal)
{
    എങ്കിൽ (SDL_BITSPERPIXEL(format) >= 8) {
        എങ്കിൽ (!SDL_size_mul_check_overflow(width, SDL_BYTESPERPIXEL(format), pitch)) {
            തിരികെ SDL_SetError("width * bpp would overflow");
        }
    } അല്ലെങ്കിൽ {
        എങ്കിൽ (!SDL_size_mul_check_overflow(width, SDL_BITSPERPIXEL(format), pitch)) {
            തിരികെ SDL_SetError("width * bpp would overflow");
        }
        എങ്കിൽ (!SDL_size_add_check_overflow(*pitch, 7, pitch)) {
            തിരികെ SDL_SetError("aligning pitch would overflow");
        }
        *pitch /= 8;
    }
    എങ്കിൽ (!minimal) {
        // 4-byte aligning for speed
        എങ്കിൽ (!SDL_size_add_check_overflow(*pitch, 3, pitch)) {
            തിരികെ SDL_SetError("aligning pitch would overflow");
        }
        *pitch &= ~3;
    }

    എങ്കിൽ (!SDL_size_mul_check_overflow(height, *pitch, size)) {
        തിരികെ SDL_SetError("height * pitch would overflow");
    }

    തിരികെ true;
}

bool SDL_CalculateSurfaceSize(SDL_PixelFormat format, പൂർണ്ണസംഖ്യ width, പൂർണ്ണസംഖ്യ height, size_t *size, size_t *pitch, bool minimalPitch)
{
    size_t p = 0, sz = 0;

    എങ്കിൽ (size) {
        *size = 0;
    }

    എങ്കിൽ (pitch) {
        *pitch = 0;
    }

    എങ്കിൽ (SDL_ISPIXELFORMAT_FOURCC(format)) {
        എങ്കിൽ (format == SDL_PIXELFORMAT_MJPG) {
            // We don't know in advance what it will be, we'll figure it out later.
            തിരികെ true;
        }

        എങ്കിൽ (!SDL_CalculateYUVSize(format, width, height, &sz, &p)) {
            // Overflow...
            തിരികെ false;
        }
    } അല്ലെങ്കിൽ {
        എങ്കിൽ (!SDL_CalculateRGBSize(format, width, height, &sz, &p, minimalPitch)) {
            // Overflow...
            തിരികെ false;
        }
    }

    എങ്കിൽ (size) {
        *size = sz;
    }

    എങ്കിൽ (pitch) {
        *pitch = p;
    }

    തിരികെ true;
}

സ്ഥിതം bool SDL_InitializeSurface(SDL_Surface *surface, പൂർണ്ണസംഖ്യ width, പൂർണ്ണസംഖ്യ height, SDL_PixelFormat format, SDL_Colorspace colorspace, SDL_PropertiesID props, ശൂന്യം *pixels, പൂർണ്ണസംഖ്യ pitch, bool onstack)
{
    SDL_zerop(surface);

    surface->flags = SDL_SURFACE_PREALLOCATED;
    surface->format = format;
    surface->w = width;
    surface->h = height;
    surface->pixels = pixels;
    surface->pitch = pitch;
    surface->reserved = &SDL_surface_magic;

    എങ്കിൽ (onstack) {
        surface->internal_flags |= SDL_INTERNAL_SURFACE_അട്ടി;
    }

    surface->fmt = SDL_GetPixelFormatDetails(format);
    എങ്കിൽ (!surface->fmt) {
        SDL_DestroySurface(surface);
        തിരികെ false;
    }

    // Initialize the clip rect
    surface->clip_rect.w = width;
    surface->clip_rect.h = height;

    // Allocate an empty mapping
    surface->map.info.r = 0xFF;
    surface->map.info.g = 0xFF;
    surface->map.info.b = 0xFF;
    surface->map.info.a = 0xFF;

    എങ്കിൽ (colorspace == SDL_COLORSPACE_UNKNOWN) {
        surface->colorspace = SDL_GetDefaultColorspaceForFormat(format);
    } അല്ലെങ്കിൽ {
        surface->colorspace = colorspace;
    }

    എങ്കിൽ (props) {
        എങ്കിൽ (!SDL_CopyProperties(props, SDL_GetSurfaceProperties(surface))) {
            SDL_DestroySurface(surface);
            തിരികെ false;
        }
    }

    // By default surfaces with an alpha mask are set up for blending
    എങ്കിൽ (SDL_ISPIXELFORMAT_ALPHA(surface->format)) {
        SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
    }

    // The surface is ready to go
    surface->refcount = 1;
    തിരികെ true;
}

/*
 * Create an empty surface of the appropriate depth using the given format
 */
സ്ഥിതം SDL_Surface *SDL_CreateSurfaceInternal(പൂർണ്ണസംഖ്യ width, പൂർണ്ണസംഖ്യ height, SDL_PixelFormat format, bool clear_surface)
{
    size_t pitch, size;
    SDL_Surface *surface;

    CHECK_PARAM(width < 0) {
        SDL_InvalidParamError("width");
        തിരികെ ശൂന്യ;
    }

    CHECK_PARAM(height < 0) {
        SDL_InvalidParamError("height");
        തിരികെ ശൂന്യ;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        തിരികെ ശൂന്യ;
    }

    എങ്കിൽ (!SDL_CalculateSurfaceSize(format, width, height, &size, &pitch, false /* not minimal pitch */)) {
        // Overflow...
        തിരികെ ശൂന്യ;
    }

    // Allocate and initialize the surface
    surface = (SDL_Surface *)SDL_malloc(വലുപ്പം(*surface));
    എങ്കിൽ (!surface) {
        തിരികെ ശൂന്യ;
    }

    എങ്കിൽ (!SDL_InitializeSurface(surface, width, height, format, SDL_COLORSPACE_UNKNOWN, 0, ശൂന്യ, (പൂർണ്ണസംഖ്യ)pitch, false)) {
        തിരികെ ശൂന്യ;
    }

    എങ്കിൽ (surface->w && surface->h && format != SDL_PIXELFORMAT_MJPG) {
        surface->flags &= ~SDL_SURFACE_PREALLOCATED;
        എങ്കിൽ (SDL_GetHintBoolean("SDL_SURFACE_MALLOC", false)) {
            എങ്കിൽ (clear_surface) {
                surface->pixels = SDL_calloc(1, size);
            } അല്ലെങ്കിൽ {
                surface->pixels = SDL_malloc(size);
            }
        } അല്ലെങ്കിൽ {
            surface->flags |= SDL_SURFACE_SIMD_ALIGNED;
            എങ്കിൽ (clear_surface) {
                surface->pixels = SDL_aligned_alloc_zero(SDL_GetSIMDAlignment(), size);
            } അല്ലെങ്കിൽ {
                surface->pixels = SDL_aligned_alloc(SDL_GetSIMDAlignment(), size);
            }
        }
        എങ്കിൽ (!surface->pixels) {
            SDL_DestroySurface(surface);
            തിരികെ ശൂന്യ;
        }
    }
    തിരികെ surface;
}

SDL_Surface *SDL_CreateSurfaceZeroed(പൂർണ്ണസംഖ്യ width, പൂർണ്ണസംഖ്യ height, SDL_PixelFormat format)
{
    തിരികെ SDL_CreateSurfaceInternal(width, height, format, true);
}

SDL_Surface *SDL_CreateSurfaceUninitialized(പൂർണ്ണസംഖ്യ width, പൂർണ്ണസംഖ്യ height, SDL_PixelFormat format)
{
    തിരികെ SDL_CreateSurfaceInternal(width, height, format, false);
}

SDL_Surface *SDL_CreateSurface(പൂർണ്ണസംഖ്യ width, പൂർണ്ണസംഖ്യ height, SDL_PixelFormat format)
{
    തിരികെ SDL_CreateSurfaceZeroed(width, height, format);
}


/*
 * Create an RGB surface from an existing memory buffer using the given
 * enum SDL_PIXELFORMAT_* format
 */
SDL_Surface *SDL_CreateSurfaceFrom(പൂർണ്ണസംഖ്യ width, പൂർണ്ണസംഖ്യ height, SDL_PixelFormat format, ശൂന്യം *pixels, പൂർണ്ണസംഖ്യ pitch)
{
    CHECK_PARAM(width < 0) {
        SDL_InvalidParamError("width");
        തിരികെ ശൂന്യ;
    }

    CHECK_PARAM(height < 0) {
        SDL_InvalidParamError("height");
        തിരികെ ശൂന്യ;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        തിരികെ ശൂന്യ;
    }

    എങ്കിൽ (pitch == 0 && !pixels) {
        // The application will fill these in later with valid values
    } അല്ലെങ്കിൽ {
        size_t minimalPitch;

        എങ്കിൽ (!SDL_CalculateSurfaceSize(format, width, height, ശൂന്യ, &minimalPitch, true /* minimal pitch */)) {
            // Overflow...
            തിരികെ ശൂന്യ;
        }

        CHECK_PARAM(pitch < 0 || (size_t)pitch < minimalPitch) {
            SDL_InvalidParamError("pitch");
            തിരികെ ശൂന്യ;
        }
    }

    // Allocate and initialize the surface
    SDL_Surface *surface = (SDL_Surface *)SDL_malloc(വലുപ്പം(*surface));
    എങ്കിൽ (!surface ||
        !SDL_InitializeSurface(surface, width, height, format, SDL_COLORSPACE_UNKNOWN, 0, pixels, pitch, false)) {
        തിരികെ ശൂന്യ;
    }
    തിരികെ surface;
}

SDL_PropertiesID SDL_GetSurfaceProperties(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        തിരികെ 0;
    }

    എങ്കിൽ (!surface->props) {
        surface->props = SDL_CreateProperties();
    }
    തിരികെ surface->props;
}

bool SDL_SetSurfaceColorspace(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        തിരികെ SDL_InvalidParamError("surface");
    }

    surface->colorspace = colorspace;
    തിരികെ true;
}

SDL_Colorspace SDL_GetSurfaceColorspace(SDL_Surface *surface)
{
    എങ്കിൽ (!SDL_SurfaceValid(surface)) {
        തിരികെ SDL_COLORSPACE_UNKNOWN;
    }

    തിരികെ surface->colorspace;
}

ദശാംശം SDL_GetDefaultSDRWhitePoint(SDL_Colorspace colorspace)
{
    തിരികെ SDL_GetSurfaceSDRWhitePoint(ശൂന്യ, colorspace);
}

ദശാംശം SDL_GetSurfaceSDRWhitePoint(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    SDL_TransferCharacteristics transfer = SDL_COLORSPACETRANSFER(colorspace);

    എങ്കിൽ (transfer == SDL_TRANSFER_CHARACTERISTICS_LINEAR ||
        transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
        SDL_PropertiesID props;
        ദശാംശം default_മൂല്യം = 1.0f;

        എങ്കിൽ (SDL_SurfaceValid(surface)) {
            props = surface->props;
        } അല്ലെങ്കിൽ {
            props = 0;
        }
        എങ്കിൽ (transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
            /* The older standards use an SDR white point of 100 nits.
             * ITU-R BT.2408-6 recommends using an SDR white point of 203 nits.
             * This is the default Chrome uses, and what a lot of game content
             * assumes, so we'll go with that.
             */
            സ്ഥിരം ദശാംശം DEFAULT_PQ_SDR_WHITE_POINT = 203.0f;
            default_മൂല്യം = DEFAULT_PQ_SDR_WHITE_POINT;
        }
        തിരികെ SDL_GetFloatProperty(props, SDL_PROP_SURFACE_SDR_WHITE_POINT_FLOAT, default_മൂല്യം);
    }
    തിരികെ 1.0f;
}

ദശാംശം SDL_GetDefaultHDRHeadroom(SDL_Colorspace colorspace)
{
    തിരികെ SDL_GetSurfaceHDRHeadroom(ശൂന്യ, colorspace);
}

ദശാംശം SDL_GetSurfaceHDRHeadroom(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    SDL_TransferCharacteristics transfer = SDL_COLORSPACETRANSFER(colorspace);

    എങ്കിൽ (transfer == SDL_TRANSFER_CHARACTERISTICS_LINEAR ||
        transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
        SDL_PropertiesID props;
        ദശാംശം default_മൂല്യം = 0.0f;

        എങ്കിൽ (SDL_SurfaceValid(surface)) {
            props = surface->props;
        } അല്ലെങ്കിൽ {
            props = 0;
        }
        തിരികെ SDL_GetFloatProperty(props, SDL_PROP_SURFACE_HDR_HEADROOM_FLOAT, default_മൂല്യം);
    }
    തിരികെ 1.0f;
}

SDL_Palette *SDL_CreateSurfacePalette(SDL_Surface *surface)
{
    SDL_Palette *palette;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        തിരികെ ശൂന്യ;
    }

    CHECK_PARAM(!SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        SDL_SetError("The surface is not indexed format");
        തിരികെ ശൂന്യ;
    }

    palette = SDL_CreatePalette((1 << SDL_BITSPERPIXEL(surface->format)));
    എങ്കിൽ (!palette) {
        തിരികെ ശൂന്യ;
    }

    എങ്കിൽ (palette->ncolors == 2) {
        // Create a black and white bitmap palette
        palette->colors[0].r = 0xFF;
        palette->colors[0].g = 0xFF;
        palette->colors[0].b = 0xFF;
        palette->colors[1].r = 0x00;
        palette->colors[1].g = 0x00;
        palette->colors[1].b = 0x00;
    }

    എങ്കിൽ (!SDL_SetSurfacePalette(surface, palette)) {
        SDL_DestroyPalette(palette);
        തിരികെ ശൂന്യ;
    }

    // The surface has retained the palette, we can remove the reference here
    SDL_assert(palette->refcount == 2);
    SDL_DestroyPalette(palette);
    തിരികെ palette;
}

bool SDL_SetSurfacePalette(SDL_Surface *surface, SDL_Palette *palette)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        തിരികെ SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(palette && !SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        തിരികെ SDL_SetError("Surface doesn't use a palette");
    }

    CHECK_PARAM(palette && palette->ncolors > (1 << SDL_BITSPERPIXEL(surface->format))) {
        തിരികെ SDL_SetError("Palette doesn't match surface format");
    }

    എങ്കിൽ (palette != surface->palette) {
        എങ്കിൽ (surface->palette) {
            SDL_DestroyPalette(surface->palette);
        }

        surface->palette = palette;

        എങ്കിൽ (surface->palette) {
            ++surface->palette->refcount;
        }
    }

    SDL_InvalidateMap(&surface->map);

    തിരികെ true;
}

SDL_Palette *SDL_GetSurfacePalette(SDL_Surface *surface)
{
    എങ്കിൽ (!SDL_SurfaceValid(surface)) {
        തിരികെ ശൂന്യ;
    }

    തിരികെ surface->palette;
}

bool SDL_AddSurfaceAlternateImage(SDL_Surface *surface, SDL_Surface *image)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        തിരികെ SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(!SDL_SurfaceValid(image)) {
        തിരികെ SDL_InvalidParamError("image");
    }

    SDL_Surface **images = (SDL_Surface **)SDL_realloc(surface->images, (surface->അക്കം_images + 1) * വലുപ്പം(*images));
    എങ്കിൽ (!images) {
        തിരികെ false;
    }
    images[surface->അക്കം_images] = image;
    surface->images = images;
    ++surface->അക്കം_images;
    ++image->refcount;
    തിരികെ true;
}

bool SDL_SurfaceHasAlternateImages(SDL_Surface *surface)
{
    എങ്കിൽ (!SDL_SurfaceValid(surface)) {
        തിരികെ false;
    }

    തിരികെ (surface->അക്കം_images > 0);
}

SDL_Surface **SDL_GetSurfaceImages(SDL_Surface *surface, പൂർണ്ണസംഖ്യ *എണ്ണം)
{
    എങ്കിൽ (എണ്ണം) {
        *എണ്ണം = 0;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        തിരികെ ശൂന്യ;
    }

    പൂർണ്ണസംഖ്യ അക്കം_images = 1 + surface->അക്കം_images;
    SDL_Surface **images = (SDL_Surface **)SDL_malloc((അക്കം_images + 1) * വലുപ്പം(*images));
    എങ്കിൽ (!images) {
        തിരികെ ശൂന്യ;
    }
    images[0] = surface;
    എങ്കിൽ (surface->അക്കം_images > 0) {
        SDL_memcpy(&images[1], surface->images, (surface->അക്കം_images * വലുപ്പം(images[1])));
    }
    images[അക്കം_images] = ശൂന്യ;

    എങ്കിൽ (എണ്ണം) {
        *എണ്ണം = അക്കം_images;
    }
    തിരികെ images;
}

SDL_Surface *SDL_GetSurfaceImage(SDL_Surface *surface, ദശാംശം display_scale)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        തിരികെ ശൂന്യ;
    }

    എങ്കിൽ (!SDL_SurfaceHasAlternateImages(surface)) {
        ++surface->refcount;
        തിരികെ surface;
    }

    // This surface has high DPI images, pick the best one available, or scale one to the correct size
    SDL_Surface **images = SDL_GetSurfaceImages(surface, ശൂന്യ);
    എങ്കിൽ (!images) {
        // Failure, fall back to the existing surface
        ++surface->refcount;
        തിരികെ surface;
    }

    // Find closest image. Images that are larger than the
    // desired size are preferred over images that are smaller.
    SDL_Surface *closest = ശൂന്യ;
    പൂർണ്ണസംഖ്യ desired_w = (പൂർണ്ണസംഖ്യ)SDL_round(surface->w * display_scale);
    പൂർണ്ണസംഖ്യ desired_h = (പൂർണ്ണസംഖ്യ)SDL_round(surface->h * display_scale);
    പൂർണ്ണസംഖ്യ desired_size = desired_w * desired_h;
    പൂർണ്ണസംഖ്യ closest_distance = -1;
    പൂർണ്ണസംഖ്യ closest_size = -1;
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; images[i]; ++i) {
        SDL_Surface *candidate = images[i];
        പൂർണ്ണസംഖ്യ size = candidate->w * candidate->h;
        പൂർണ്ണസംഖ്യ delta_w = (candidate->w - desired_w);
        പൂർണ്ണസംഖ്യ delta_h = (candidate->h - desired_h);
        പൂർണ്ണസംഖ്യ distance = (delta_w * delta_w) + (delta_h * delta_h);
        എങ്കിൽ (closest_distance < 0 || distance < closest_distance ||
            (size > desired_size && closest_size < desired_size)) {
            closest = candidate;
            closest_distance = distance;
            closest_size = size;
        }
    }
    SDL_free(images);
    SDL_assert(closest != ശൂന്യ);    // We should always have at least one surface

    എങ്കിൽ (closest->w == desired_w && closest->h == desired_h) {
        ++closest->refcount;
        തിരികെ closest;
    }

    // We need to scale the image to the correct size. To maintain good image quality, downscaling
    // is done in steps, never reducing the width and height by more than half each time.
    SDL_Surface *scaled = closest;
    ചെയ്യുക {
        പൂർണ്ണസംഖ്യ next_scaled_w = SDL_max(desired_w, (scaled->w + 1) / 2);
        പൂർണ്ണസംഖ്യ next_scaled_h = SDL_max(desired_h, (scaled->h + 1) / 2);
        SDL_Surface *next_scaled = SDL_ScaleSurface(scaled, next_scaled_w, next_scaled_h, SDL_SCALEMODE_LINEAR);
        എങ്കിൽ (scaled != closest) {
            SDL_DestroySurface(scaled);
        }
        scaled = next_scaled;
        എങ്കിൽ (!scaled) {
            // Failure, fall back to the closest surface
            ++closest->refcount;
            തിരികെ closest;
        }
    } ആകുമ്പോൾ (scaled->w != desired_w || scaled->h != desired_h);

    തിരികെ scaled;
}

ശൂന്യം SDL_RemoveSurfaceAlternateImages(SDL_Surface *surface)
{
    എങ്കിൽ (!SDL_SurfaceValid(surface)) {
        തിരികെ;
    }

    എങ്കിൽ (surface->അക്കം_images > 0) {
        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < surface->അക്കം_images; ++i) {
            SDL_DestroySurface(surface->images[i]);
        }
        SDL_free(surface->images);
        surface->images = ശൂന്യ;
        surface->അക്കം_images = 0;
    }
}

bool SDL_SetSurfaceRLE(SDL_Surface *surface, bool enabled)
{
    പൂർണ്ണസംഖ്യ flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        തിരികെ SDL_InvalidParamError("surface");
    }

    flags = surface->map.info.flags;
    എങ്കിൽ (enabled) {
        surface->map.info.flags |= SDL_COPY_RLE_DESIRED;
    } അല്ലെങ്കിൽ {
        surface->map.info.flags &= ~SDL_COPY_RLE_DESIRED;
    }
    എങ്കിൽ (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    തിരികെ true;
}

bool SDL_SurfaceHasRLE(SDL_Surface *surface)
{
    എങ്കിൽ (!SDL_SurfaceValid(surface)) {
        തിരികെ false;
    }

    എങ്കിൽ (!(surface->map.info.flags & SDL_COPY_RLE_DESIRED)) {
        തിരികെ false;
    }

    തിരികെ true;
}

bool SDL_Set_Surface_Color_താക്കോൽ(SDL_Surface *surface, bool enabled, Uint32 താക്കോൽ)
{
    പൂർണ്ണസംഖ്യ flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        തിരികെ SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(surface->palette && താക്കോൽ >= ((Uint32)surface->palette->ncolors)) {
        തിരികെ SDL_InvalidParamError("key");
    }

    flags = surface->map.info.flags;
    എങ്കിൽ (enabled) {
        surface->map.info.flags |= SDL_COPY_COLORKEY;
        surface->map.info.colorkey = താക്കോൽ;
    } അല്ലെങ്കിൽ {
        surface->map.info.flags &= ~SDL_COPY_COLORKEY;
    }
    എങ്കിൽ (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }

    തിരികെ true;
}

bool SDL_Surface_Has_Color_താക്കോൽ(SDL_Surface *surface)
{
    എങ്കിൽ (!SDL_SurfaceValid(surface)) {
        തിരികെ false;
    }

    എങ്കിൽ (!(surface->map.info.flags & SDL_COPY_COLORKEY)) {
        തിരികെ false;
    }

    തിരികെ true;
}

bool SDL_Get_Surface_Color_താക്കോൽ(SDL_Surface *surface, Uint32 *താക്കോൽ)
{
    എങ്കിൽ (താക്കോൽ) {
        *താക്കോൽ = 0;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        തിരികെ SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(!(surface->map.info.flags & SDL_COPY_COLORKEY)) {
        തിരികെ SDL_SetError("Surface doesn't have a colorkey");
    }

    എങ്കിൽ (താക്കോൽ) {
        *താക്കോൽ = surface->map.info.colorkey;
    }
    തിരികെ true;
}

/* This is a fairly slow function to switch from colorkey to alpha
   NB: it doesn't handle bpp 1 or 3, because they have no alpha channel */
സ്ഥിതം ശൂന്യം SDL_ConvertColorkeyToAlpha(SDL_Surface *surface, bool ignore_alpha)
{
    പൂർണ്ണസംഖ്യ x, y, bpp;

    എങ്കിൽ (!SDL_SurfaceValid(surface)) {
        തിരികെ;
    }

    എങ്കിൽ (!(surface->map.info.flags & SDL_COPY_COLORKEY) ||
        !SDL_ISPIXELFORMAT_ALPHA(surface->format)) {
        തിരികെ;
    }

    bpp = SDL_BYTESPERPIXEL(surface->format);

    SDL_LockSurface(surface);

    എങ്കിൽ (bpp == 2) {
        Uint16 *row, *spot;
        Uint16 ckey = (Uint16)surface->map.info.colorkey;
        Uint16 mask = (Uint16)(~surface->fmt->Amask);

        // Ignore, or not, alpha in colorkey comparison
        എങ്കിൽ (ignore_alpha) {
            ckey &= mask;
            row = (Uint16 *)surface->pixels;
            വേണ്ടി (y = surface->h; y--;) {
                spot = row;
                വേണ്ടി (x = surface->w; x--;) {
                    എങ്കിൽ ((*spot & mask) == ckey) {
                        *spot &= mask;
                    }
                    ++spot;
                }
                row += surface->pitch / 2;
            }
        } അല്ലെങ്കിൽ {
            row = (Uint16 *)surface->pixels;
            വേണ്ടി (y = surface->h; y--;) {
                spot = row;
                വേണ്ടി (x = surface->w; x--;) {
                    എങ്കിൽ (*spot == ckey) {
                        *spot &= mask;
                    }
                    ++spot;
                }
                row += surface->pitch / 2;
            }
        }
    } അല്ലെങ്കിൽ എങ്കിൽ (bpp == 4) {
        Uint32 *row, *spot;
        Uint32 ckey = surface->map.info.colorkey;
        Uint32 mask = ~surface->fmt->Amask;

        // Ignore, or not, alpha in colorkey comparison
        എങ്കിൽ (ignore_alpha) {
            ckey &= mask;
            row = (Uint32 *)surface->pixels;
            വേണ്ടി (y = surface->h; y--;) {
                spot = row;
                വേണ്ടി (x = surface->w; x--;) {
                    എങ്കിൽ ((*spot & mask) == ckey) {
                        *spot &= mask;
                    }
                    ++spot;
                }
                row += surface->pitch / 4;
            }
        } അല്ലെങ്കിൽ {
            row = (Uint32 *)surface->pixels;
            വേണ്ടി (y = surface->h; y--;) {
                spot = row;
                വേണ്ടി (x = surface->w; x--;) {
                    എങ്കിൽ (*spot == ckey) {
                        *spot &= mask;
                    }
                    ++spot;
                }
                row += surface->pitch / 4;
            }
        }
    }

    SDL_UnlockSurface(surface);

    SDL_Set_Surface_Color_താക്കോൽ(surface, false, 0);
    SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
}

bool SDL_SetSurfaceColorMod(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b)
{
    പൂർണ്ണസംഖ്യ flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        തിരികെ SDL_InvalidParamError("surface");
    }

    surface->map.info.r = r;
    surface->map.info.g = g;
    surface->map.info.b = b;

    flags = surface->map.info.flags;
    എങ്കിൽ (r != 0xFF || g != 0xFF || b != 0xFF) {
        surface->map.info.flags |= SDL_COPY_MODULATE_COLOR;
    } അല്ലെങ്കിൽ {
        surface->map.info.flags &= ~SDL_COPY_MODULATE_COLOR;
    }
    എങ്കിൽ (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    തിരികെ true;
}

bool SDL_GetSurfaceColorMod(SDL_Surface *surface, Uint8 *r, Uint8 *g, Uint8 *b)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        എങ്കിൽ (r) {
            *r = 255;
        }
        എങ്കിൽ (g) {
            *g = 255;
        }
        എങ്കിൽ (b) {
            *b = 255;
        }
        തിരികെ SDL_InvalidParamError("surface");
    }

    എങ്കിൽ (r) {
        *r = surface->map.info.r;
    }
    എങ്കിൽ (g) {
        *g = surface->map.info.g;
    }
    എങ്കിൽ (b) {
        *b = surface->map.info.b;
    }
    തിരികെ true;
}

bool SDL_SetSurfaceAlphaMod(SDL_Surface *surface, Uint8 alpha)
{
    പൂർണ്ണസംഖ്യ flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        തിരികെ SDL_InvalidParamError("surface");
    }

    surface->map.info.a = alpha;

    flags = surface->map.info.flags;
    എങ്കിൽ (alpha != 0xFF) {
        surface->map.info.flags |= SDL_COPY_MODULATE_ALPHA;
    } അല്ലെങ്കിൽ {
        surface->map.info.flags &= ~SDL_COPY_MODULATE_ALPHA;
    }
    എങ്കിൽ (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    തിരികെ true;
}

bool SDL_GetSurfaceAlphaMod(SDL_Surface *surface, Uint8 *alpha)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        എങ്കിൽ (alpha) {
            *alpha = 255;
        }
        തിരികെ SDL_InvalidParamError("surface");
    }

    എങ്കിൽ (alpha) {
        *alpha = surface->map.info.a;
    }
    തിരികെ true;
}

bool SDL_SetSurfaceBlendMode(SDL_Surface *surface, SDL_BlendMode blendMode)
{
    പൂർണ്ണസംഖ്യ flags;
    bool result = true;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        തിരികെ SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(blendMode == SDL_BLENDMODE_INVALID) {
        തിരികെ SDL_InvalidParamError("blendMode");
    }

    flags = surface->map.info.flags;
    surface->map.info.flags &= ~SDL_COPY_BLEND_MASK;
    തിരഞ്ഞെടുപ്പ് (blendMode) {
    അവസ്ഥ SDL_BLENDMODE_NONE:
        നിർത്തുക;
    അവസ്ഥ SDL_BLENDMODE_BLEND:
        surface->map.info.flags |= SDL_COPY_BLEND;
        നിർത്തുക;
    അവസ്ഥ SDL_BLENDMODE_BLEND_PREMULTIPLIED:
        surface->map.info.flags |= SDL_COPY_BLEND_PREMULTIPLIED;
        നിർത്തുക;
    അവസ്ഥ SDL_BLENDMODE_ADD:
        surface->map.info.flags |= SDL_COPY_ADD;
        നിർത്തുക;
    അവസ്ഥ SDL_BLENDMODE_ADD_PREMULTIPLIED:
        surface->map.info.flags |= SDL_COPY_ADD_PREMULTIPLIED;
        നിർത്തുക;
    അവസ്ഥ SDL_BLENDMODE_MOD:
        surface->map.info.flags |= SDL_COPY_MOD;
        നിർത്തുക;
    അവസ്ഥ SDL_BLENDMODE_MUL:
        surface->map.info.flags |= SDL_COPY_MUL;
        നിർത്തുക;
    സ്ഥിരസ്ഥിതി:
        result = SDL_Unsupported();
        നിർത്തുക;
    }

    എങ്കിൽ (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }

    തിരികെ result;
}

bool SDL_GetSurfaceBlendMode(SDL_Surface *surface, SDL_BlendMode *blendMode)
{
    എങ്കിൽ (blendMode) {
        *blendMode = SDL_BLENDMODE_INVALID;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        തിരികെ SDL_InvalidParamError("surface");
    }

    എങ്കിൽ (!blendMode) {
        തിരികെ true;
    }

    തിരഞ്ഞെടുപ്പ് (surface->map.info.flags & SDL_COPY_BLEND_MASK) {
    അവസ്ഥ SDL_COPY_BLEND:
        *blendMode = SDL_BLENDMODE_BLEND;
        നിർത്തുക;
    അവസ്ഥ SDL_COPY_BLEND_PREMULTIPLIED:
        *blendMode = SDL_BLENDMODE_BLEND_PREMULTIPLIED;
        നിർത്തുക;
    അവസ്ഥ SDL_COPY_ADD:
        *blendMode = SDL_BLENDMODE_ADD;
        നിർത്തുക;
    അവസ്ഥ SDL_COPY_ADD_PREMULTIPLIED:
        *blendMode = SDL_BLENDMODE_ADD_PREMULTIPLIED;
        നിർത്തുക;
    അവസ്ഥ SDL_COPY_MOD:
        *blendMode = SDL_BLENDMODE_MOD;
        നിർത്തുക;
    അവസ്ഥ SDL_COPY_MUL:
        *blendMode = SDL_BLENDMODE_MUL;
        നിർത്തുക;
    സ്ഥിരസ്ഥിതി:
        *blendMode = SDL_BLENDMODE_NONE;
        നിർത്തുക;
    }
    തിരികെ true;
}

bool SDL_SetSurfaceClipRect(SDL_Surface *surface, സ്ഥിരം SDL_Rect *rect)
{
    SDL_Rect full_rect;

    // Don't do anything if there's no surface to act on
    എങ്കിൽ (!SDL_SurfaceValid(surface)) {
        തിരികെ false;
    }

    // Set up the full surface rectangle
    full_rect.x = 0;
    full_rect.y = 0;
    full_rect.w = surface->w;
    full_rect.h = surface->h;

    // Set the clipping rectangle
    എങ്കിൽ (!rect) {
        surface->clip_rect = full_rect;
        തിരികെ true;
    }
    തിരികെ SDL_GetRectIntersection(rect, &full_rect, &surface->clip_rect);
}

bool SDL_GetSurfaceClipRect(SDL_Surface *surface, SDL_Rect *rect)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        എങ്കിൽ (rect) {
            SDL_zerop(rect);
        }
        തിരികെ SDL_InvalidParamError("surface");
    }
    CHECK_PARAM(!rect) {
        തിരികെ SDL_InvalidParamError("rect");
    }
    *rect = surface->clip_rect;
    തിരികെ true;
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
bool SDL_BlitSurfaceUnchecked(SDL_Surface *src, സ്ഥിരം SDL_Rect *srcrect,
                             SDL_Surface *dst, സ്ഥിരം SDL_Rect *dstrect)
{
    // Check to make sure the blit mapping is valid
    എങ്കിൽ (!SDL_ValidateMap(src, dst)) {
        തിരികെ false;
    }
    തിരികെ src->map.blit(src, srcrect, dst, dstrect);
}

bool SDL_BlitSurface(SDL_Surface *src, സ്ഥിരം SDL_Rect *srcrect, SDL_Surface *dst, സ്ഥിരം SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src) || (!src->pixels && !SDL_MUSTLOCK(src))) {
        തിരികെ SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst) || (!dst->pixels && !SDL_MUSTLOCK(dst))) {
        തിരികെ SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        തിരികെ SDL_SetError("Surfaces must not be locked during blit");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    എങ്കിൽ (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
    } അല്ലെങ്കിൽ {
        r_dst.x = 0;
        r_dst.y = 0;
    }

    // clip the source rectangle to the source surface
    എങ്കിൽ (srcrect) {
        SDL_Rect tmp;
        എങ്കിൽ (SDL_GetRectIntersection(srcrect, &r_src, &tmp) == false) {
            തിരികെ true;
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
        എങ്കിൽ (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &tmp) == false) {
            തിരികെ true;
        }

        // Shift srcrect, if dstrect has changed
        r_src.x += tmp.x - r_dst.x;
        r_src.y += tmp.y - r_dst.y;
        r_src.w = tmp.w;
        r_src.h = tmp.h;

        // Update dstrect
        r_dst = tmp;
    }

    എങ്കിൽ (r_dst.w <= 0 || r_dst.h <= 0) {
        // No-op.
        തിരികെ true;
    }

    // Switch back to a fast blit if we were previously stretching
    എങ്കിൽ (src->map.info.flags & SDL_COPY_NEAREST) {
        src->map.info.flags &= ~SDL_COPY_NEAREST;
        SDL_InvalidateMap(&src->map);
    }

    തിരികെ SDL_BlitSurfaceUnchecked(src, &r_src, dst, &r_dst);
}

സ്ഥിതം bool SDL_BlitSurfaceClippedScaled(SDL_Surface *src, സ്ഥിരം SDL_Rect *srcrect, SDL_Surface *dst, സ്ഥിരം SDL_Rect *dstrect, SDL_ScaleMode scaleMode)
{
    // We need to scale first, then blit into dst because we're clipping in the destination surface pixel coordinates
    bool result;
    പൂർണ്ണസംഖ്യ saved_w = src->w;
    പൂർണ്ണസംഖ്യ saved_h = src->h;
    ശൂന്യം *saved_pixels = src->pixels;
    src->w = srcrect->w;
    src->h = srcrect->h;
    src->pixels = (Uint8 *)src->pixels + srcrect->y * src->pitch + srcrect->x * SDL_BYTESPERPIXEL(src->format);
    SDL_Surface *scaled = SDL_ScaleSurface(src, dstrect->w, dstrect->h, scaleMode);
    എങ്കിൽ (scaled) {
        result = SDL_BlitSurface(scaled, ശൂന്യ, dst, dstrect);
        SDL_DestroySurface(scaled);
    } അല്ലെങ്കിൽ {
        result = false;
    }
    src->w = saved_w;
    src->h = saved_h;
    src->pixels = saved_pixels;
    തിരികെ result;
}

bool SDL_BlitSurfaceScaled(SDL_Surface *src, സ്ഥിരം SDL_Rect *srcrect, SDL_Surface *dst, സ്ഥിരം SDL_Rect *dstrect, SDL_ScaleMode scaleMode)
{
    SDL_Rect r_src, r_dst;
    bool result;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src) || (!src->pixels && !SDL_MUSTLOCK(src))) {
        തിരികെ SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst) || (!dst->pixels && !SDL_MUSTLOCK(dst))) {
        തിരികെ SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        തിരികെ SDL_SetError("Surfaces must not be locked during blit");
    }

    തിരഞ്ഞെടുപ്പ് (scaleMode) {
    അവസ്ഥ SDL_SCALEMODE_NEAREST:
        നിർത്തുക;
    അവസ്ഥ SDL_SCALEMODE_LINEAR:
        നിർത്തുക;
    അവസ്ഥ SDL_SCALEMODE_PIXELART:
        scaleMode = SDL_SCALEMODE_NEAREST;
        നിർത്തുക;
    സ്ഥിരസ്ഥിതി:
        തിരികെ SDL_InvalidParamError("scaleMode");
    }

    പൂർണ്ണസംഖ്യ src_w = srcrect ? srcrect->w : src->w;
    പൂർണ്ണസംഖ്യ src_h = srcrect ? srcrect->h : src->h;
    പൂർണ്ണസംഖ്യ dst_w = dstrect ? dstrect->w : dst->w;
    പൂർണ്ണസംഖ്യ dst_h = dstrect ? dstrect->h : dst->h;
    എങ്കിൽ (src_w == dst_w && src_h == dst_h) {
        // No scaling, defer to regular blit
        തിരികെ SDL_BlitSurface(src, srcrect, dst, dstrect);
    }

    എങ്കിൽ (src->w == 0 || src->h == 0) {
        // Nothing to do
        തിരികെ true;
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    എങ്കിൽ (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
        r_dst.w = dstrect->w;
        r_dst.h = dstrect->h;
    } അല്ലെങ്കിൽ {
        r_dst.x = 0;
        r_dst.y = 0;
        r_dst.w = dst->w;
        r_dst.h = dst->h;
    }

    // clip the source rectangle to the source surface
    എങ്കിൽ (srcrect) {
        SDL_Rect desired, tmp;
        desired.x = srcrect->x;
        desired.y = srcrect->y;
        desired.w = SDL_max(srcrect->w, 1);
        desired.h = SDL_max(srcrect->h, 1);
        എങ്കിൽ (SDL_GetRectIntersection(&desired, &r_src, &tmp) == false) {
            തിരികെ true;
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
    എങ്കിൽ (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &tmp) == false) {
        തിരികെ true;
    }

    എങ്കിൽ (tmp.x != r_dst.x || tmp.y != r_dst.y || tmp.w != r_dst.w || tmp.h != r_dst.h) {
        // Need to do a clipped and scaled blit
        തിരികെ SDL_BlitSurfaceClippedScaled(src, &r_src, dst, &r_dst, scaleMode);
    }

    എങ്കിൽ (SDL_MUSTLOCK(src)) {
        എങ്കിൽ (!SDL_LockSurface(src)) {
            തിരികെ false;
        }
    }
    എങ്കിൽ (SDL_MUSTLOCK(dst)) {
        എങ്കിൽ (!SDL_LockSurface(dst)) {
            എങ്കിൽ (SDL_MUSTLOCK(src)) {
                SDL_UnlockSurface(src);
            }
            തിരികെ false;
        }
    }

    result = SDL_BlitSurfaceUncheckedScaled(src, &r_src, dst, &r_dst, scaleMode);

    എങ്കിൽ (SDL_MUSTLOCK(src)) {
        SDL_UnlockSurface(src);
    }
    എങ്കിൽ (SDL_MUSTLOCK(dst)) {
        SDL_UnlockSurface(dst);
    }
    തിരികെ result;
}

/**
 *  This is a semi-private blit function and it performs low-level surface
 *  scaled blitting only.
 */
bool SDL_BlitSurfaceUncheckedScaled(SDL_Surface *src, സ്ഥിരം SDL_Rect *srcrect, SDL_Surface *dst, സ്ഥിരം SDL_Rect *dstrect, SDL_ScaleMode scaleMode)
{
    സ്ഥിതം സ്ഥിരം Uint32 complex_copy_flags = (SDL_COPY_MODULATE_MASK | SDL_COPY_BLEND_MASK | SDL_COPY_COLORKEY);

    എങ്കിൽ (srcrect->w > SDL_MAX_UINT16 || srcrect->h > SDL_MAX_UINT16 ||
        dstrect->w > SDL_MAX_UINT16 || dstrect->h > SDL_MAX_UINT16) {
        തിരികെ SDL_SetError("Size too large for scaling");
    }

    എങ്കിൽ (!(src->map.info.flags & SDL_COPY_NEAREST)) {
        src->map.info.flags |= SDL_COPY_NEAREST;
        SDL_InvalidateMap(&src->map);
    }

    എങ്കിൽ (scaleMode == SDL_SCALEMODE_NEAREST || scaleMode == SDL_SCALEMODE_PIXELART) {
        എങ്കിൽ (!(src->map.info.flags & complex_copy_flags) &&
            src->format == dst->format &&
            (!SDL_ISPIXELFORMAT_INDEXED(src->format) ||
             (SDL_BITSPERPIXEL(src->format) == 8 && SDL_IsSamePalette(src->palette, dst->palette))) &&
            SDL_BYTESPERPIXEL(src->format) <= 4) {
            തിരികെ SDL_StretchSurface(src, srcrect, dst, dstrect, SDL_SCALEMODE_NEAREST);
        } അല്ലെങ്കിൽ എങ്കിൽ (SDL_BITSPERPIXEL(src->format) < 8) {
            // Scaling bitmap not yet supported, convert to RGBA for blit
            bool result = false;
            SDL_Surface *tmp = SDL_ConvertSurface(src, SDL_PIXELFORMAT_ARGB8888);
            എങ്കിൽ (tmp) {
                result = SDL_BlitSurfaceUncheckedScaled(tmp, srcrect, dst, dstrect, SDL_SCALEMODE_NEAREST);
                SDL_DestroySurface(tmp);
            }
            തിരികെ result;
        } അല്ലെങ്കിൽ {
            തിരികെ SDL_BlitSurfaceUnchecked(src, srcrect, dst, dstrect);
        }
    } അല്ലെങ്കിൽ {
        എങ്കിൽ (!(src->map.info.flags & complex_copy_flags) &&
            src->format == dst->format &&
            !SDL_ISPIXELFORMAT_INDEXED(src->format) &&
            SDL_BYTESPERPIXEL(src->format) == 4 &&
            src->format != SDL_PIXELFORMAT_ARGB2101010) {
            // fast path
            തിരികെ SDL_StretchSurface(src, srcrect, dst, dstrect, SDL_SCALEMODE_LINEAR);
        } അല്ലെങ്കിൽ എങ്കിൽ (SDL_BITSPERPIXEL(src->format) < 8) {
            // Scaling bitmap not yet supported, convert to RGBA for blit
            bool result = false;
            SDL_Surface *tmp = SDL_ConvertSurface(src, SDL_PIXELFORMAT_ARGB8888);
            എങ്കിൽ (tmp) {
                result = SDL_BlitSurfaceUncheckedScaled(tmp, srcrect, dst, dstrect, scaleMode);
                SDL_DestroySurface(tmp);
            }
            തിരികെ result;
        } അല്ലെങ്കിൽ {
            // Use intermediate surface(s)
            SDL_Surface *tmp1 = ശൂന്യ;
            bool result;
            SDL_Rect srcrect2;
            പൂർണ്ണസംഖ്യ is_complex_copy_flags = (src->map.info.flags & complex_copy_flags);

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
            എങ്കിൽ (SDL_BYTESPERPIXEL(src->format) != 4 || src->format == SDL_PIXELFORMAT_ARGB2101010) {
                SDL_PixelFormat fmt;
                എങ്കിൽ (SDL_BYTESPERPIXEL(dst->format) == 4 && dst->format != SDL_PIXELFORMAT_ARGB2101010 &&
                    (SDL_ISPIXELFORMAT_ALPHA(dst->format) || !is_complex_copy_flags)) {
                    fmt = dst->format;
                } അല്ലെങ്കിൽ {
                    fmt = SDL_PIXELFORMAT_ARGB8888;
                }
                tmp1 = SDL_ConvertSurfaceRect(src, srcrect, fmt);
                എങ്കിൽ (!tmp1) {
                    തിരികെ false;
                }
                src = tmp1;
                srcrect2.x = 0;
                srcrect2.y = 0;
            }

            // Intermediate scaling
            എങ്കിൽ (is_complex_copy_flags || src->format != dst->format) {
                SDL_Rect tmprect;
                SDL_Surface *tmp2 = SDL_CreateSurfaceUninitialized(dstrect->w, dstrect->h, src->format);
                SDL_StretchSurface(src, &srcrect2, tmp2, ശൂന്യ, SDL_SCALEMODE_LINEAR);

                SDL_SetSurfaceColorMod(tmp2, r, g, b);
                SDL_SetSurfaceAlphaMod(tmp2, alpha);
                SDL_SetSurfaceBlendMode(tmp2, blendMode);

                tmprect.x = 0;
                tmprect.y = 0;
                tmprect.w = dstrect->w;
                tmprect.h = dstrect->h;
                result = SDL_BlitSurfaceUnchecked(tmp2, &tmprect, dst, dstrect);
                SDL_DestroySurface(tmp2);
            } അല്ലെങ്കിൽ {
                result = SDL_StretchSurface(src, &srcrect2, dst, dstrect, SDL_SCALEMODE_LINEAR);
            }

            SDL_DestroySurface(tmp1);
            തിരികെ result;
        }
    }
}

bool SDL_BlitSurfaceTiled(SDL_Surface *src, സ്ഥിരം SDL_Rect *srcrect, SDL_Surface *dst, സ്ഥിരം SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        തിരികെ SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        തിരികെ SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        തിരികെ SDL_SetError("Surfaces must not be locked during blit");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    എങ്കിൽ (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
        r_dst.w = dstrect->w;
        r_dst.h = dstrect->h;
    } അല്ലെങ്കിൽ {
        r_dst.x = 0;
        r_dst.y = 0;
        r_dst.w = dst->w;
        r_dst.h = dst->h;
    }

    // clip the source rectangle to the source surface
    എങ്കിൽ (srcrect) {
        എങ്കിൽ (SDL_GetRectIntersection(srcrect, &r_src, &r_src) == false) {
            തിരികെ true;
        }

        // For tiling we don't adjust the destination rectangle
    }

    // clip the destination rectangle against the clip rectangle
    {
        എങ്കിൽ (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &r_dst) == false) {
            തിരികെ true;
        }

        // For tiling we don't adjust the source rectangle
    }

    // Switch back to a fast blit if we were previously stretching
    എങ്കിൽ (src->map.info.flags & SDL_COPY_NEAREST) {
        src->map.info.flags &= ~SDL_COPY_NEAREST;
        SDL_InvalidateMap(&src->map);
    }

    പൂർണ്ണസംഖ്യ rows = r_dst.h / r_src.h;
    പൂർണ്ണസംഖ്യ cols = r_dst.w / r_src.w;
    പൂർണ്ണസംഖ്യ remaining_w = r_dst.w % r_src.w;
    പൂർണ്ണസംഖ്യ remaining_h = r_dst.h % r_src.h;
    SDL_Rect curr_src, curr_dst;

    SDL_copyp(&curr_src, &r_src);
    curr_dst.y = r_dst.y;
    curr_dst.w = r_src.w;
    curr_dst.h = r_src.h;
    വേണ്ടി (പൂർണ്ണസംഖ്യ y = 0; y < rows; ++y) {
        curr_dst.x = r_dst.x;
        വേണ്ടി (പൂർണ്ണസംഖ്യ x = 0; x < cols; ++x) {
            എങ്കിൽ (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                തിരികെ false;
            }
            curr_dst.x += curr_dst.w;
        }
        എങ്കിൽ (remaining_w) {
            curr_src.w = remaining_w;
            curr_dst.w = remaining_w;
            എങ്കിൽ (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                തിരികെ false;
            }
            curr_src.w = r_src.w;
            curr_dst.w = r_src.w;
        }
        curr_dst.y += curr_dst.h;
    }
    എങ്കിൽ (remaining_h) {
        curr_src.h = remaining_h;
        curr_dst.h = remaining_h;
        curr_dst.x = r_dst.x;
        വേണ്ടി (പൂർണ്ണസംഖ്യ x = 0; x < cols; ++x) {
            എങ്കിൽ (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                തിരികെ false;
            }
            curr_dst.x += curr_dst.w;
        }
        എങ്കിൽ (remaining_w) {
            curr_src.w = remaining_w;
            curr_dst.w = remaining_w;
            എങ്കിൽ (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                തിരികെ false;
            }
        }
    }
    തിരികെ true;
}

bool SDL_BlitSurfaceTiledWithScale(SDL_Surface *src, സ്ഥിരം SDL_Rect *srcrect, ദശാംശം scale, SDL_ScaleMode scaleMode, SDL_Surface *dst, സ്ഥിരം SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        തിരികെ SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        തിരികെ SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        തിരികെ SDL_SetError("Surfaces must not be locked during blit");
    }
    CHECK_PARAM(scale < 0.0f) {
        തിരികെ SDL_InvalidParamError("scale");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    എങ്കിൽ (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
        r_dst.w = dstrect->w;
        r_dst.h = dstrect->h;
    } അല്ലെങ്കിൽ {
        r_dst.x = 0;
        r_dst.y = 0;
        r_dst.w = dst->w;
        r_dst.h = dst->h;
    }

    // clip the source rectangle to the source surface
    എങ്കിൽ (srcrect) {
        എങ്കിൽ (SDL_GetRectIntersection(srcrect, &r_src, &r_src) == false) {
            തിരികെ true;
        }

        // For tiling we don't adjust the destination rectangle
    }

    // clip the destination rectangle against the clip rectangle
    {
        എങ്കിൽ (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &r_dst) == false) {
            തിരികെ true;
        }

        // For tiling we don't adjust the source rectangle
    }

    // Switch back to a fast blit if we were previously stretching
    എങ്കിൽ (src->map.info.flags & SDL_COPY_NEAREST) {
        src->map.info.flags &= ~SDL_COPY_NEAREST;
        SDL_InvalidateMap(&src->map);
    }

    പൂർണ്ണസംഖ്യ tile_width = (പൂർണ്ണസംഖ്യ)SDL_roundf(r_src.w * scale);
    പൂർണ്ണസംഖ്യ tile_height = (പൂർണ്ണസംഖ്യ)SDL_roundf(r_src.h * scale);
    എങ്കിൽ (tile_width <= 0 || tile_height <= 0) {
        // Nothing to do
        തിരികെ true;
    }
    പൂർണ്ണസംഖ്യ rows = r_dst.h / tile_height;
    പൂർണ്ണസംഖ്യ cols = r_dst.w / tile_width;
    പൂർണ്ണസംഖ്യ remaining_dst_w = (r_dst.w - cols * tile_width);
    പൂർണ്ണസംഖ്യ remaining_dst_h = (r_dst.h - rows * tile_height);
    പൂർണ്ണസംഖ്യ remaining_src_w = (പൂർണ്ണസംഖ്യ)(remaining_dst_w / scale);
    പൂർണ്ണസംഖ്യ remaining_src_h = (പൂർണ്ണസംഖ്യ)(remaining_dst_h / scale);
    SDL_Rect curr_src, curr_dst;

    SDL_copyp(&curr_src, &r_src);
    curr_dst.y = r_dst.y;
    curr_dst.w = tile_width;
    curr_dst.h = tile_height;
    വേണ്ടി (പൂർണ്ണസംഖ്യ y = 0; y < rows; ++y) {
        curr_dst.x = r_dst.x;
        വേണ്ടി (പൂർണ്ണസംഖ്യ x = 0; x < cols; ++x) {
            എങ്കിൽ (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
                തിരികെ false;
            }
            curr_dst.x += curr_dst.w;
        }
        എങ്കിൽ (remaining_dst_w > 0) {
            curr_src.w = remaining_src_w;
            curr_dst.w = remaining_dst_w;
            എങ്കിൽ (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
                തിരികെ false;
            }
            curr_src.w = r_src.w;
            curr_dst.w = tile_width;
        }
        curr_dst.y += curr_dst.h;
    }
    എങ്കിൽ (remaining_dst_h > 0) {
        curr_src.h = remaining_src_h;
        curr_dst.h = remaining_dst_h;
        curr_dst.x = r_dst.x;
        വേണ്ടി (പൂർണ്ണസംഖ്യ x = 0; x < cols; ++x) {
            എങ്കിൽ (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
                തിരികെ false;
            }
            curr_dst.x += curr_dst.w;
        }
        എങ്കിൽ (remaining_dst_w > 0) {
            curr_src.w = remaining_src_w;
            curr_dst.w = remaining_dst_w;
            എങ്കിൽ (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
                തിരികെ false;
            }
        }
    }
    തിരികെ true;
}

bool SDL_BlitSurface9Grid(SDL_Surface *src, സ്ഥിരം SDL_Rect *srcrect, പൂർണ്ണസംഖ്യ ഇടത്_width, പൂർണ്ണസംഖ്യ വലത്_width, പൂർണ്ണസംഖ്യ മുകൾ_height, പൂർണ്ണസംഖ്യ bottom_height, ദശാംശം scale, SDL_ScaleMode scaleMode, SDL_Surface *dst, സ്ഥിരം SDL_Rect *dstrect)
{
    SDL_Rect full_src, full_dst;
    SDL_Rect curr_src, curr_dst;
    പൂർണ്ണസംഖ്യ dst_ഇടത്_width;
    പൂർണ്ണസംഖ്യ dst_വലത്_width;
    പൂർണ്ണസംഖ്യ dst_മുകൾ_height;
    പൂർണ്ണസംഖ്യ dst_bottom_height;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        തിരികെ SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        തിരികെ SDL_InvalidParamError("dst");
    }

    എങ്കിൽ (!srcrect) {
        full_src.x = 0;
        full_src.y = 0;
        full_src.w = src->w;
        full_src.h = src->h;
        srcrect = &full_src;
    }

    എങ്കിൽ (!dstrect) {
        full_dst.x = 0;
        full_dst.y = 0;
        full_dst.w = dst->w;
        full_dst.h = dst->h;
        dstrect = &full_dst;
    }

    എങ്കിൽ (scale <= 0.0f || scale == 1.0f) {
        dst_ഇടത്_width = ഇടത്_width;
        dst_വലത്_width = വലത്_width;
        dst_മുകൾ_height = മുകൾ_height;
        dst_bottom_height = bottom_height;
    } അല്ലെങ്കിൽ {
        dst_ഇടത്_width = (പൂർണ്ണസംഖ്യ)SDL_roundf(ഇടത്_width * scale);
        dst_വലത്_width = (പൂർണ്ണസംഖ്യ)SDL_roundf(വലത്_width * scale);
        dst_മുകൾ_height = (പൂർണ്ണസംഖ്യ)SDL_roundf(മുകൾ_height * scale);
        dst_bottom_height = (പൂർണ്ണസംഖ്യ)SDL_roundf(bottom_height * scale);
    }

    // Upper-left corner
    curr_src.x = srcrect->x;
    curr_src.y = srcrect->y;
    curr_src.w = ഇടത്_width;
    curr_src.h = മുകൾ_height;
    curr_dst.x = dstrect->x;
    curr_dst.y = dstrect->y;
    curr_dst.w = dst_ഇടത്_width;
    curr_dst.h = dst_മുകൾ_height;
    എങ്കിൽ (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        തിരികെ false;
    }

    // Upper-right corner
    curr_src.x = srcrect->x + srcrect->w - വലത്_width;
    curr_src.w = വലത്_width;
    curr_dst.x = dstrect->x + dstrect->w - dst_വലത്_width;
    curr_dst.w = dst_വലത്_width;
    എങ്കിൽ (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        തിരികെ false;
    }

    // Lower-right corner
    curr_src.y = srcrect->y + srcrect->h - bottom_height;
    curr_dst.y = dstrect->y + dstrect->h - dst_bottom_height;
    curr_dst.h = dst_bottom_height;
    എങ്കിൽ (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        തിരികെ false;
    }

    // Lower-left corner
    curr_src.x = srcrect->x;
    curr_src.w = ഇടത്_width;
    curr_dst.x = dstrect->x;
    curr_dst.w = dst_ഇടത്_width;
    എങ്കിൽ (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        തിരികെ false;
    }

    //ഇടത്
    curr_src.y = srcrect->y + മുകൾ_height;
    curr_src.h = srcrect->h - മുകൾ_height - bottom_height;
    curr_dst.y = dstrect->y + dst_മുകൾ_height;
    curr_dst.h = dstrect->h - dst_മുകൾ_height - dst_bottom_height;
    എങ്കിൽ (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        തിരികെ false;
    }

    //വലത്
    curr_src.x = srcrect->x + srcrect->w - വലത്_width;
    curr_src.w = വലത്_width;
    curr_dst.x = dstrect->x + dstrect->w - dst_വലത്_width;
    curr_dst.w = dst_വലത്_width;
    എങ്കിൽ (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        തിരികെ false;
    }

    //മുകൾ
    curr_src.x = srcrect->x + ഇടത്_width;
    curr_src.y = srcrect->y;
    curr_src.w = srcrect->w - ഇടത്_width - വലത്_width;
    curr_src.h = മുകൾ_height;
    curr_dst.x = dstrect->x + dst_ഇടത്_width;
    curr_dst.y = dstrect->y;
    curr_dst.w = dstrect->w - dst_ഇടത്_width - dst_വലത്_width;
    curr_dst.h = dst_മുകൾ_height;
    എങ്കിൽ (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        തിരികെ false;
    }

    // Bottom
    curr_src.y = srcrect->y + srcrect->h - bottom_height;
    curr_dst.y = dstrect->y + dstrect->h - dst_bottom_height;
    curr_dst.h = dst_bottom_height;
    എങ്കിൽ (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        തിരികെ false;
    }

    // Center
    curr_src.x = srcrect->x + ഇടത്_width;
    curr_src.y = srcrect->y + മുകൾ_height;
    curr_src.w = srcrect->w - ഇടത്_width - വലത്_width;
    curr_src.h = srcrect->h - മുകൾ_height - bottom_height;
    curr_dst.x = dstrect->x + dst_ഇടത്_width;
    curr_dst.y = dstrect->y + dst_മുകൾ_height;
    curr_dst.w = dstrect->w - dst_ഇടത്_width - dst_വലത്_width;
    curr_dst.h = dstrect->h - dst_മുകൾ_height - dst_bottom_height;
    എങ്കിൽ (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        തിരികെ false;
    }

    തിരികെ true;
}

/*
 * Lock a surface to directly access the pixels
 */
bool SDL_LockSurface(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        തിരികെ SDL_InvalidParamError("surface");
    }

    എങ്കിൽ (!surface->locked) {
#ifdef SDL_HAVE_RLE
        // Perform the lock
        എങ്കിൽ (surface->internal_flags & SDL_INTERNAL_SURFACE_RLEACCEL) {
            SDL_UnRLESurface(surface);
        }
#endif
    }

    // Increment the surface lock count, for recursive locks
    ++surface->locked;
    surface->flags |= SDL_SURFACE_LOCKED;
    SDL_UpdateSurfaceLockFlag(surface);

    // Ready to go..
    തിരികെ true;
}

/*
 * Unlock a previously locked surface
 */
ശൂന്യം SDL_UnlockSurface(SDL_Surface *surface)
{
    എങ്കിൽ (!SDL_SurfaceValid(surface)) {
        തിരികെ;
    }

    // Only perform an unlock if we are locked
    എങ്കിൽ (!surface->locked || (--surface->locked > 0)) {
        തിരികെ;
    }

    surface->flags &= ~SDL_SURFACE_LOCKED;
    SDL_UpdateSurfaceLockFlag(surface);
}

സ്ഥിതം bool SDL_FlipSurfaceHorizontal(SDL_Surface *surface)
{
    bool isstack;
    Uint8 *row, *a, *b, *tmp;
    പൂർണ്ണസംഖ്യ i, j, bpp;

    എങ്കിൽ (SDL_BITSPERPIXEL(surface->format) < 8) {
        // We could implement this if needed, but we'd have to flip sets of bits within a byte
        തിരികെ SDL_Unsupported();
    }

    എങ്കിൽ (surface->h <= 0) {
        തിരികെ true;
    }

    എങ്കിൽ (surface->w <= 1) {
        തിരികെ true;
    }

    bpp = SDL_BYTESPERPIXEL(surface->format);
    row = (Uint8 *)surface->pixels;
    tmp = SDL_small_alloc(Uint8, surface->pitch, &isstack);
    എങ്കിൽ (!tmp) {
        തിരികെ false;
    }
    വേണ്ടി (i = surface->h; i--; ) {
        a = row;
        b = a + (surface->w - 1) * bpp;
        വേണ്ടി (j = surface->w / 2; j--; ) {
            SDL_memcpy(tmp, a, bpp);
            SDL_memcpy(a, b, bpp);
            SDL_memcpy(b, tmp, bpp);
            a += bpp;
            b -= bpp;
        }
        row += surface->pitch;
    }
    SDL_small_free(tmp, isstack);
    തിരികെ true;
}

സ്ഥിതം bool SDL_FlipSurfaceVertical(SDL_Surface *surface)
{
    bool isstack;
    Uint8 *a, *b, *tmp;
    പൂർണ്ണസംഖ്യ i;

    എങ്കിൽ (surface->h <= 1) {
        തിരികെ true;
    }

    a = (Uint8 *)surface->pixels;
    b = a + (surface->h - 1) * surface->pitch;
    tmp = SDL_small_alloc(Uint8, surface->pitch, &isstack);
    എങ്കിൽ (!tmp) {
        തിരികെ false;
    }
    വേണ്ടി (i = surface->h / 2; i--; ) {
        SDL_memcpy(tmp, a, surface->pitch);
        SDL_memcpy(a, b, surface->pitch);
        SDL_memcpy(b, tmp, surface->pitch);
        a += surface->pitch;
        b -= surface->pitch;
    }
    SDL_small_free(tmp, isstack);
    തിരികെ true;
}

bool SDL_FlipSurface(SDL_Surface *surface, SDL_FlipMode flip)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        തിരികെ SDL_InvalidParamError("surface");
    }
    എങ്കിൽ (!surface->pixels) {
        തിരികെ true;
    }

    bool result = true;
    തിരഞ്ഞെടുപ്പ് (flip) {
    അവസ്ഥ SDL_FLIP_HORIZONTAL:
        result = SDL_FlipSurfaceHorizontal(surface);
        നിർത്തുക;
    അവസ്ഥ SDL_FLIP_VERTICAL:
        result = SDL_FlipSurfaceVertical(surface);
        നിർത്തുക;
    അവസ്ഥ SDL_FLIP_HORIZONTAL_AND_VERTICAL:
        result &= SDL_FlipSurfaceHorizontal(surface);
        result &= SDL_FlipSurfaceVertical(surface);
        നിർത്തുക;
    സ്ഥിരസ്ഥിതി:
        result = SDL_InvalidParamError("flip");
        നിർത്തുക;
    }
    തിരികെ result;
}

സ്ഥിതം SDL_Surface *SDL_ConvertSurfaceRectAndColorspace(SDL_Surface *surface, സ്ഥിരം SDL_Rect *rect, SDL_PixelFormat format, SDL_Palette *palette, SDL_Colorspace colorspace, SDL_PropertiesID props)
{
    SDL_Palette *temp_palette = ശൂന്യ;
    SDL_Surface *convert = ശൂന്യ;
    SDL_Colorspace src_colorspace;
    SDL_PropertiesID src_properties;
    Uint32 copy_flags;
    SDL_Color copy_color;
    SDL_Rect bounds;
    bool result;
    bool palette_ck_transform = false;
    Uint8 palette_ck_മൂല്യം = 0;
    Uint8 *palette_saved_alpha = ശൂന്യ;
    പൂർണ്ണസംഖ്യ palette_saved_alpha_ncolors = 0;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        പോകുക error;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        പോകുക error;
    }

    // Set the bounds of the new surface
    bounds.x = 0;
    bounds.y = 0;
    bounds.w = surface->w;
    bounds.h = surface->h;
    എങ്കിൽ (rect) {
        bounds.w = rect->w;
        bounds.h = rect->h;
    } അല്ലെങ്കിൽ {
        rect = &bounds;
    }

    // Check for empty destination palette! (results in empty image)
    എങ്കിൽ (palette) {
        പൂർണ്ണസംഖ്യ i;
        വേണ്ടി (i = 0; i < palette->ncolors; ++i) {
            എങ്കിൽ ((palette->colors[i].r != 0xFF) || (palette->colors[i].g != 0xFF) || (palette->colors[i].b != 0xFF)) {
                നിർത്തുക;
            }
        }
        എങ്കിൽ (i == palette->ncolors) {
            SDL_SetError("Empty destination palette");
            പോകുക error;
        }
    } അല്ലെങ്കിൽ എങ്കിൽ (SDL_ISPIXELFORMAT_INDEXED(format)) {
        // Create a dither palette for conversion
        temp_palette = SDL_CreatePalette(1 << SDL_BITSPERPIXEL(format));
        എങ്കിൽ (temp_palette) {
            SDL_DitherPalette(temp_palette);
            palette = temp_palette;
        }
    }

    src_colorspace = surface->colorspace;
    src_properties = surface->props;

    // Create a new surface with the desired format
    എങ്കിൽ (surface->pixels || SDL_MUSTLOCK(surface)) {
        convert = SDL_CreateSurfaceUninitialized(rect->w, rect->h, format);
    } അല്ലെങ്കിൽ {
        convert = SDL_CreateSurfaceFrom(rect->w, rect->h, format, ശൂന്യ, 0);
    }
    എങ്കിൽ (!convert) {
        പോകുക error;
    }
    എങ്കിൽ (SDL_ISPIXELFORMAT_INDEXED(format)) {
        SDL_SetSurfacePalette(convert, palette);
    }

    എങ്കിൽ (colorspace == SDL_COLORSPACE_UNKNOWN) {
        colorspace = src_colorspace;
    }
    SDL_SetSurfaceColorspace(convert, colorspace);

    എങ്കിൽ (SDL_ISPIXELFORMAT_FOURCC(format) || SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        എങ്കിൽ (surface->format == SDL_PIXELFORMAT_MJPG && format == SDL_PIXELFORMAT_MJPG) {
            // Just do a straight pixel copy of the JPEG image
            size_t size = (size_t)surface->pitch;
            convert->pixels = SDL_malloc(size);
            എങ്കിൽ (!convert->pixels) {
                പോകുക error;
            }
            convert->flags &= ~SDL_SURFACE_PREALLOCATED;
            convert->pitch = surface->pitch;
            SDL_memcpy(convert->pixels, surface->pixels, size);

        } അല്ലെങ്കിൽ എങ്കിൽ (!SDL_ConvertPixelsAndColorspace(surface->w, surface->h, surface->format, src_colorspace, src_properties, surface->pixels, surface->pitch, convert->format, colorspace, props, convert->pixels, convert->pitch)) {
            പോകുക error;
        }

        // Save the original copy flags
        copy_flags = surface->map.info.flags;

        പോകുക end;
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
    എങ്കിൽ (surface->palette && SDL_ISPIXELFORMAT_ALPHA(format)) {
        bool set_opaque = false;

        bool is_opaque, has_alpha_channel;
        SDL_DetectPalette(surface->palette, &is_opaque, &has_alpha_channel);

        എങ്കിൽ (is_opaque) {
            എങ്കിൽ (!has_alpha_channel) {
                set_opaque = true;
            }
        }

        // Set opaque and backup palette alpha values
        എങ്കിൽ (set_opaque) {
            പൂർണ്ണസംഖ്യ i;
            palette_saved_alpha_ncolors = surface->palette->ncolors;
            എങ്കിൽ (palette_saved_alpha_ncolors > 0) {
                palette_saved_alpha = SDL_അട്ടി_alloc(Uint8, palette_saved_alpha_ncolors);
                വേണ്ടി (i = 0; i < palette_saved_alpha_ncolors; i++) {
                    palette_saved_alpha[i] = surface->palette->colors[i].a;
                    surface->palette->colors[i].a = SDL_ALPHA_OPAQUE;
                }
            }
        }
    }

    // Transform colorkey to alpha. for cases where source palette has duplicate values, and colorkey is one of them
    എങ്കിൽ (copy_flags & SDL_COPY_COLORKEY) {
        എങ്കിൽ (surface->palette && !palette) {
            palette_ck_transform = true;
            palette_ck_മൂല്യം = surface->palette->colors[surface->map.info.colorkey].a;
            surface->palette->colors[surface->map.info.colorkey].a = SDL_ALPHA_TRANSPARENT;
        }
    }

    എങ്കിൽ (surface->pixels || SDL_MUSTLOCK(surface)) {
        result = SDL_BlitSurfaceUnchecked(surface, rect, convert, &bounds);
    } അല്ലെങ്കിൽ {
        result = true;
    }

    // Restore colorkey alpha value
    എങ്കിൽ (palette_ck_transform) {
        surface->palette->colors[surface->map.info.colorkey].a = palette_ck_മൂല്യം;
    }

    // Restore palette alpha values
    എങ്കിൽ (palette_saved_alpha) {
        പൂർണ്ണസംഖ്യ i;
        വേണ്ടി (i = 0; i < palette_saved_alpha_ncolors; i++) {
            surface->palette->colors[i].a = palette_saved_alpha[i];
        }
        SDL_അട്ടി_free(palette_saved_alpha);
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
    എങ്കിൽ (!result) {
        പോകുക error;
    }

    എങ്കിൽ (copy_flags & SDL_COPY_COLORKEY) {
        bool set_colorkey_by_color = false;
        bool convert_colorkey = true;

        എങ്കിൽ (surface->palette) {
            എങ്കിൽ (palette &&
                surface->palette->ncolors <= palette->ncolors &&
                (SDL_memcmp(surface->palette->colors, palette->colors,
                            surface->palette->ncolors * വലുപ്പം(SDL_Color)) == 0)) {
                // The palette is identical, just set the same colorkey
                SDL_Set_Surface_Color_താക്കോൽ(convert, true, surface->map.info.colorkey);
            } അല്ലെങ്കിൽ എങ്കിൽ (!palette) {
                എങ്കിൽ (SDL_ISPIXELFORMAT_ALPHA(format)) {
                    // No need to add the colorkey, transparency is in the alpha channel
                } അല്ലെങ്കിൽ {
                    // Only set the colorkey information
                    set_colorkey_by_color = true;
                    convert_colorkey = false;
                }
            } അല്ലെങ്കിൽ {
                set_colorkey_by_color = true;
            }
        } അല്ലെങ്കിൽ {
            set_colorkey_by_color = true;
        }

        എങ്കിൽ (set_colorkey_by_color) {
            SDL_Surface *tmp;
            SDL_Surface *tmp2;
            പൂർണ്ണസംഖ്യ converted_colorkey = 0;

            // Create a dummy surface to get the colorkey converted
            tmp = SDL_CreateSurfaceUninitialized(1, 1, surface->format);
            എങ്കിൽ (!tmp) {
                പോകുക error;
            }

            // Share the palette, if any
            എങ്കിൽ (surface->palette) {
                SDL_SetSurfacePalette(tmp, surface->palette);
            }

            SDL_FillSurfaceRect(tmp, ശൂന്യ, surface->map.info.colorkey);

            tmp->map.info.flags &= ~SDL_COPY_COLORKEY;

            // Conversion of the colorkey
            tmp2 = SDL_ConvertSurfaceAndColorspace(tmp, format, palette, colorspace, props);
            എങ്കിൽ (!tmp2) {
                SDL_DestroySurface(tmp);
                പോകുക error;
            }

            // Get the converted colorkey
            SDL_memcpy(&converted_colorkey, tmp2->pixels, tmp2->fmt->bytes_per_pixel);

            SDL_DestroySurface(tmp);
            SDL_DestroySurface(tmp2);

            // Set the converted colorkey on the new surface
            SDL_Set_Surface_Color_താക്കോൽ(convert, true, converted_colorkey);

            // This is needed when converting for 3D texture upload
            എങ്കിൽ (convert_colorkey) {
                SDL_ConvertColorkeyToAlpha(convert, true);
            }
        }
    }

end:
    എങ്കിൽ (temp_palette) {
        SDL_DestroyPalette(temp_palette);
    }

    SDL_SetSurfaceClipRect(convert, &surface->clip_rect);

    /* Enable alpha blending by default if the new surface has an
     * alpha channel or alpha modulation */
    എങ്കിൽ (SDL_ISPIXELFORMAT_ALPHA(format) ||
        (copy_flags & SDL_COPY_MODULATE_ALPHA)) {
        SDL_SetSurfaceBlendMode(convert, SDL_BLENDMODE_BLEND);
    }
    എങ്കിൽ (copy_flags & SDL_COPY_RLE_DESIRED) {
        SDL_SetSurfaceRLE(convert, true);
    }

    // Copy alternate images
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < surface->അക്കം_images; ++i) {
        എങ്കിൽ (!SDL_AddSurfaceAlternateImage(convert, surface->images[i])) {
            പോകുക error;
        }
    }

    // Copy properties
    എങ്കിൽ (surface->props) {
        എങ്കിൽ (!SDL_CopyProperties(surface->props, SDL_GetSurfaceProperties(convert))) {
            പോകുക error;
        }

        // Make sure the new surface doesn't reference an old SDL2 surface.
        SDL_ClearProperty(SDL_GetSurfaceProperties(convert), "sdl2-compat.surface2");
    }

    // We're ready to go!
    തിരികെ convert;

error:
    എങ്കിൽ (temp_palette) {
        SDL_DestroyPalette(temp_palette);
    }
    എങ്കിൽ (convert) {
        SDL_DestroySurface(convert);
    }
    തിരികെ ശൂന്യ;
}

SDL_Surface *SDL_ConvertSurfaceAndColorspace(SDL_Surface *surface, SDL_PixelFormat format, SDL_Palette *palette, SDL_Colorspace colorspace, SDL_PropertiesID props)
{
    തിരികെ SDL_ConvertSurfaceRectAndColorspace(surface, ശൂന്യ, format, palette, colorspace, props);
}

SDL_Surface *SDL_RotateSurface(SDL_Surface *surface, ദശാംശം angle)
{
    SDL_Surface *rotated = ശൂന്യ;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        തിരികെ ശൂന്യ;
    }

    SDL_Rect rect_dest;
    ഇരട്ട cangle, sangle;
    SDL_FPoint center = { surface->w * 0.5f, surface->h * 0.5f };
    SDLgfx_rotozoomSurfaceSizeTrig(surface->w, surface->h, angle, &center, &rect_dest, &cangle, &sangle);

    // This function requires a 32-bit surface or 8-bit surface with a colorkey
    എങ്കിൽ ((SDL_BITSPERPIXEL(surface->format) == 32 && SDL_PIXELLAYOUT(surface->format) == SDL_PACKEDLAYOUT_8888) ||
        (surface->format == SDL_PIXELFORMAT_INDEX8 && SDL_Surface_Has_Color_താക്കോൽ(surface))) {
        rotated = SDLgfx_rotateSurface(surface, angle, 1, 0, 0, &rect_dest, cangle, sangle, &center);
    } അല്ലെങ്കിൽ {
        SDL_Surface *convert = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);
        എങ്കിൽ (convert) {
            SDL_Surface *tmp = SDLgfx_rotateSurface(convert, angle, 1, 0, 0, &rect_dest, cangle, sangle, &center);
            എങ്കിൽ (tmp) {
                rotated = SDL_ConvertSurfaceAndColorspace(tmp, surface->format, surface->palette, surface->colorspace, surface->props);
                SDL_DestroySurface(tmp);
            }
            SDL_DestroySurface(convert);
        }
    }

    എങ്കിൽ (rotated) {
        എങ്കിൽ (SDL_HasProperty(surface->props, SDL_PROP_SURFACE_ROTATION_FLOAT)) {
            സ്ഥിരം ദശാംശം rotation = (SDL_Get_സംഖ്യ_Property(surface->props, SDL_PROP_SURFACE_ROTATION_FLOAT, 0) - angle);
            SDL_SetFloatProperty(SDL_GetSurfaceProperties(rotated), SDL_PROP_SURFACE_ROTATION_FLOAT, rotation);
        }
    }

    തിരികെ rotated;
}

SDL_Surface *SDL_DuplicateSurface(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        തിരികെ ശൂന്യ;
    }

    തിരികെ SDL_ConvertSurfaceAndColorspace(surface, surface->format, surface->palette, surface->colorspace, surface->props);
}

SDL_Surface *SDL_ScaleSurface(SDL_Surface *surface, പൂർണ്ണസംഖ്യ width, പൂർണ്ണസംഖ്യ height, SDL_ScaleMode scaleMode)
{
    SDL_Surface *convert = ശൂന്യ;
    Uint32 copy_flags;
    SDL_Color copy_color;
    bool rc;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        പോകുക error;
    }

    എങ്കിൽ (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // We can't directly scale a YUV surface (yet!)
        SDL_Surface *tmp = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        എങ്കിൽ (!tmp) {
            തിരികെ ശൂന്യ;
        }

        SDL_Surface *scaled = SDL_ScaleSurface(tmp, width, height, scaleMode);
        SDL_DestroySurface(tmp);
        എങ്കിൽ (!scaled) {
            തിരികെ ശൂന്യ;
        }

        SDL_Surface *result = SDL_ConvertSurfaceAndColorspace(scaled, surface->format, ശൂന്യ, surface->colorspace, surface->props);
        SDL_DestroySurface(scaled);
        തിരികെ result;
    }

    എങ്കിൽ (SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        // Linear scaling requires conversion to RGBA and then slow pixel color lookup
        scaleMode = SDL_SCALEMODE_NEAREST;
    }

    // Create a new surface with the desired size
    എങ്കിൽ (surface->pixels || SDL_MUSTLOCK(surface)) {
        convert = SDL_CreateSurfaceUninitialized(width, height, surface->format);
    } അല്ലെങ്കിൽ {
        convert = SDL_CreateSurfaceFrom(width, height, surface->format, ശൂന്യ, 0);
    }
    എങ്കിൽ (!convert) {
        പോകുക error;
    }
    SDL_SetSurfacePalette(convert, surface->palette);
    SDL_SetSurfaceColorspace(convert, surface->colorspace);
    SDL_SetSurfaceRLE(convert, SDL_SurfaceHasRLE(surface));

    എങ്കിൽ (surface->pixels || SDL_MUSTLOCK(surface)) {
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

        rc = SDL_BlitSurfaceScaled(surface, ശൂന്യ, convert, ശൂന്യ, scaleMode);

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
    } അല്ലെങ്കിൽ {
        rc = true;
    }

    // SDL_BlitSurfaceScaled failed, and so the conversion
    എങ്കിൽ (!rc) {
        പോകുക error;
    }

    // We're ready to go!
    തിരികെ convert;

error:
    എങ്കിൽ (convert) {
        SDL_DestroySurface(convert);
    }
    തിരികെ ശൂന്യ;
}

SDL_Surface *SDL_ConvertSurfaceRect(SDL_Surface *surface, സ്ഥിരം SDL_Rect *rect, SDL_PixelFormat format)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        തിരികെ ശൂന്യ;
    }

    തിരികെ SDL_ConvertSurfaceRectAndColorspace(surface, rect, format, ശൂന്യ, SDL_GetDefaultColorspaceForFormat(format), surface->props);
}

SDL_Surface *SDL_ConvertSurface(SDL_Surface *surface, SDL_PixelFormat format)
{
    തിരികെ SDL_ConvertSurfaceRect(surface, ശൂന്യ, format);
}

SDL_Surface *SDL_DuplicatePixels(പൂർണ്ണസംഖ്യ width, പൂർണ്ണസംഖ്യ height, SDL_PixelFormat format, SDL_Colorspace colorspace, ശൂന്യം *pixels, പൂർണ്ണസംഖ്യ pitch)
{
    SDL_Surface *surface;
    എങ്കിൽ (pixels) {
        surface = SDL_CreateSurfaceUninitialized(width, height, format);
    } അല്ലെങ്കിൽ {
        surface = SDL_CreateSurfaceFrom(width, height, format, ശൂന്യ, 0);
    }
    എങ്കിൽ (!surface) {
        തിരികെ ശൂന്യ;
    }
    SDL_SetSurfaceColorspace(surface, colorspace);

    എങ്കിൽ (surface->pixels) {
        പൂർണ്ണസംഖ്യ length = width * SDL_BYTESPERPIXEL(format);
        Uint8 *src = (Uint8 *)pixels;
        Uint8 *dst = (Uint8 *)surface->pixels;
        പൂർണ്ണസംഖ്യ rows = height;
        ആകുമ്പോൾ (rows--) {
            SDL_memcpy(dst, src, length);
            dst += surface->pitch;
            src += pitch;
        }
    }
    തിരികെ surface;
}

bool SDL_ConvertPixelsAndColorspace(പൂർണ്ണസംഖ്യ width, പൂർണ്ണസംഖ്യ height,
                      SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, സ്ഥിരം ശൂന്യം *src, പൂർണ്ണസംഖ്യ src_pitch,
                      SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, ശൂന്യം *dst, പൂർണ്ണസംഖ്യ dst_pitch)
{
    SDL_Surface src_surface;
    SDL_Surface dst_surface;
    SDL_Rect rect;
    ശൂന്യം *nonconst_src = (ശൂന്യം *)src;
    bool result;

    CHECK_PARAM(!src) {
        തിരികെ SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!src_pitch) {
        തിരികെ SDL_InvalidParamError("src_pitch");
    }
    CHECK_PARAM(!dst) {
        തിരികെ SDL_InvalidParamError("dst");
    }
    CHECK_PARAM(!dst_pitch) {
        തിരികെ SDL_InvalidParamError("dst_pitch");
    }

    എങ്കിൽ (src_colorspace == SDL_COLORSPACE_UNKNOWN) {
        src_colorspace = SDL_GetDefaultColorspaceForFormat(src_format);
    }
    എങ്കിൽ (dst_colorspace == SDL_COLORSPACE_UNKNOWN) {
        dst_colorspace = SDL_GetDefaultColorspaceForFormat(dst_format);
    }

    എങ്കിൽ (src_format == SDL_PIXELFORMAT_MJPG) {
        തിരികെ SDL_ConvertPixels_STB(width, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    }

#ifdef SDL_HAVE_YUV
    എങ്കിൽ (SDL_ISPIXELFORMAT_FOURCC(src_format) && SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        തിരികെ SDL_ConvertPixels_YUV_to_YUV(width, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } അല്ലെങ്കിൽ എങ്കിൽ (SDL_ISPIXELFORMAT_FOURCC(src_format)) {
        തിരികെ SDL_ConvertPixels_YUV_to_RGB(width, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } അല്ലെങ്കിൽ എങ്കിൽ (SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        തിരികെ SDL_ConvertPixels_RGB_to_YUV(width, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    }
#അല്ലെങ്കിൽ
    എങ്കിൽ (SDL_ISPIXELFORMAT_FOURCC(src_format) || SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        തിരികെ SDL_SetError("SDL not built with YUV support");
    }
#endif

    // Fast path for same format copy
    എങ്കിൽ (src_format == dst_format && src_colorspace == dst_colorspace) {
        എങ്കിൽ (src_pitch == dst_pitch) {
            SDL_memcpy(dst, src, height * src_pitch);
        } അല്ലെങ്കിൽ {
            പൂർണ്ണസംഖ്യ i;
            സ്ഥിരം പൂർണ്ണസംഖ്യ bpp = SDL_BYTESPERPIXEL(src_format);
            width *= bpp;
            വേണ്ടി (i = height; i--;) {
                SDL_memcpy(dst, src, width);
                src = (സ്ഥിരം Uint8 *)src + src_pitch;
                dst = (Uint8 *)dst + dst_pitch;
            }
        }
        തിരികെ true;
    }

    എങ്കിൽ (!SDL_InitializeSurface(&src_surface, width, height, src_format, src_colorspace, src_properties, nonconst_src, src_pitch, true)) {
        തിരികെ false;
    }
    SDL_SetSurfaceBlendMode(&src_surface, SDL_BLENDMODE_NONE);

    എങ്കിൽ (!SDL_InitializeSurface(&dst_surface, width, height, dst_format, dst_colorspace, dst_properties, dst, dst_pitch, true)) {
        തിരികെ false;
    }

    // Set up the rect and go!
    rect.x = 0;
    rect.y = 0;
    rect.w = width;
    rect.h = height;
    result = SDL_BlitSurfaceUnchecked(&src_surface, &rect, &dst_surface, &rect);

    SDL_DestroySurface(&src_surface);
    SDL_DestroySurface(&dst_surface);

    തിരികെ result;
}

bool SDL_ConvertPixels(പൂർണ്ണസംഖ്യ width, പൂർണ്ണസംഖ്യ height, SDL_PixelFormat src_format, സ്ഥിരം ശൂന്യം *src, പൂർണ്ണസംഖ്യ src_pitch, SDL_PixelFormat dst_format, ശൂന്യം *dst, പൂർണ്ണസംഖ്യ dst_pitch)
{
    തിരികെ SDL_ConvertPixelsAndColorspace(width, height,
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

സ്ഥിതം ശൂന്യം SDL_PremultiplyAlpha_AXYZ8888(പൂർണ്ണസംഖ്യ width, പൂർണ്ണസംഖ്യ height, സ്ഥിരം ശൂന്യം *src, പൂർണ്ണസംഖ്യ src_pitch, ശൂന്യം *dst, പൂർണ്ണസംഖ്യ dst_pitch)
{
    പൂർണ്ണസംഖ്യ c;
    Uint32 srcpixel;
    Uint32 srcR, srcG, srcB, srcA;
    Uint32 dstpixel;
    Uint32 dstR, dstG, dstB, dstA;

    ആകുമ്പോൾ (height--) {
        സ്ഥിരം Uint32 *src_px = (സ്ഥിരം Uint32 *)src;
        Uint32 *dst_px = (Uint32 *)dst;
        വേണ്ടി (c = width; c; --c) {
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
        src = (സ്ഥിരം Uint8 *)src + src_pitch;
        dst = (Uint8 *)dst + dst_pitch;
    }
}

സ്ഥിതം ശൂന്യം SDL_PremultiplyAlpha_XYZA8888(പൂർണ്ണസംഖ്യ width, പൂർണ്ണസംഖ്യ height, സ്ഥിരം ശൂന്യം *src, പൂർണ്ണസംഖ്യ src_pitch, ശൂന്യം *dst, പൂർണ്ണസംഖ്യ dst_pitch)
{
    പൂർണ്ണസംഖ്യ c;
    Uint32 srcpixel;
    Uint32 srcR, srcG, srcB, srcA;
    Uint32 dstpixel;
    Uint32 dstR, dstG, dstB, dstA;

    ആകുമ്പോൾ (height--) {
        സ്ഥിരം Uint32 *src_px = (സ്ഥിരം Uint32 *)src;
        Uint32 *dst_px = (Uint32 *)dst;
        വേണ്ടി (c = width; c; --c) {
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
        src = (സ്ഥിരം Uint8 *)src + src_pitch;
        dst = (Uint8 *)dst + dst_pitch;
    }
}

സ്ഥിതം ശൂന്യം SDL_PremultiplyAlpha_AXYZ128(പൂർണ്ണസംഖ്യ width, പൂർണ്ണസംഖ്യ height, സ്ഥിരം ശൂന്യം *src, പൂർണ്ണസംഖ്യ src_pitch, ശൂന്യം *dst, പൂർണ്ണസംഖ്യ dst_pitch)
{
    പൂർണ്ണസംഖ്യ c;
    ദശാംശം flR, flG, flB, flA;

    ആകുമ്പോൾ (height--) {
        സ്ഥിരം ദശാംശം *src_px = (സ്ഥിരം ദശാംശം *)src;
        ദശാംശം *dst_px = (ദശാംശം *)dst;
        വേണ്ടി (c = width; c; --c) {
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
        src = (സ്ഥിരം Uint8 *)src + src_pitch;
        dst = (Uint8 *)dst + dst_pitch;
    }
}

സ്ഥിതം bool SDL_PremultiplyAlphaPixelsAndColorspace(പൂർണ്ണസംഖ്യ width, പൂർണ്ണസംഖ്യ height, SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, സ്ഥിരം ശൂന്യം *src, പൂർണ്ണസംഖ്യ src_pitch, SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, ശൂന്യം *dst, പൂർണ്ണസംഖ്യ dst_pitch, bool linear)
{
    SDL_Surface *convert = ശൂന്യ;
    ശൂന്യം *final_dst = dst;
    പൂർണ്ണസംഖ്യ final_dst_pitch = dst_pitch;
    SDL_PixelFormat format;
    SDL_Colorspace colorspace;
    bool result = false;

    CHECK_PARAM(!src) {
        തിരികെ SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!src_pitch) {
        തിരികെ SDL_InvalidParamError("src_pitch");
    }
    CHECK_PARAM(!dst) {
        തിരികെ SDL_InvalidParamError("dst");
    }
    CHECK_PARAM(!dst_pitch) {
        തിരികെ SDL_InvalidParamError("dst_pitch");
    }

    // Use a high precision format if we're converting to linear colorspace or using high precision pixel formats
    എങ്കിൽ (linear ||
        SDL_ISPIXELFORMAT_10BIT(src_format) || SDL_BITSPERPIXEL(src_format) > 32 ||
        SDL_ISPIXELFORMAT_10BIT(dst_format) || SDL_BITSPERPIXEL(dst_format) > 32) {
        എങ്കിൽ (src_format == SDL_PIXELFORMAT_ARGB128_FLOAT ||
            src_format == SDL_PIXELFORMAT_ABGR128_FLOAT) {
            format = src_format;
        } അല്ലെങ്കിൽ {
            format = SDL_PIXELFORMAT_ARGB128_FLOAT;
        }
    } അല്ലെങ്കിൽ {
        എങ്കിൽ (src_format == SDL_PIXELFORMAT_ARGB8888 ||
            src_format == SDL_PIXELFORMAT_ABGR8888 ||
            src_format == SDL_PIXELFORMAT_RGBA8888 ||
            src_format == SDL_PIXELFORMAT_BGRA8888) {
            format = src_format;
        } അല്ലെങ്കിൽ {
            format = SDL_PIXELFORMAT_ARGB8888;
        }
    }
    എങ്കിൽ (linear) {
        colorspace = SDL_COLORSPACE_SRGB_LINEAR;
    } അല്ലെങ്കിൽ {
        colorspace = SDL_COLORSPACE_SRGB;
    }

    എങ്കിൽ (src_format != format || src_colorspace != colorspace) {
        convert = SDL_CreateSurfaceUninitialized(width, height, format);
        എങ്കിൽ (!convert) {
            പോകുക done;
        }
        എങ്കിൽ (!SDL_ConvertPixelsAndColorspace(width, height, src_format, src_colorspace, src_properties, src, src_pitch, format, colorspace, 0, convert->pixels, convert->pitch)) {
            പോകുക done;
        }

        src = convert->pixels;
        src_pitch = convert->pitch;
        dst = convert->pixels;
        dst_pitch = convert->pitch;

    } അല്ലെങ്കിൽ എങ്കിൽ (dst_format != format || dst_colorspace != colorspace) {
        convert = SDL_CreateSurfaceUninitialized(width, height, format);
        എങ്കിൽ (!convert) {
            പോകുക done;
        }
        dst = convert->pixels;
        dst_pitch = convert->pitch;
    }

    തിരഞ്ഞെടുപ്പ് (format) {
    അവസ്ഥ SDL_PIXELFORMAT_ARGB8888:
    അവസ്ഥ SDL_PIXELFORMAT_ABGR8888:
        SDL_PremultiplyAlpha_AXYZ8888(width, height, src, src_pitch, dst, dst_pitch);
        നിർത്തുക;
    അവസ്ഥ SDL_PIXELFORMAT_RGBA8888:
    അവസ്ഥ SDL_PIXELFORMAT_BGRA8888:
        SDL_PremultiplyAlpha_XYZA8888(width, height, src, src_pitch, dst, dst_pitch);
        നിർത്തുക;
    അവസ്ഥ SDL_PIXELFORMAT_ARGB128_FLOAT:
    അവസ്ഥ SDL_PIXELFORMAT_ABGR128_FLOAT:
        SDL_PremultiplyAlpha_AXYZ128(width, height, src, src_pitch, dst, dst_pitch);
        നിർത്തുക;
    സ്ഥിരസ്ഥിതി:
        SDL_SetError("Unexpected internal pixel format");
        പോകുക done;
    }

    എങ്കിൽ (dst != final_dst) {
        എങ്കിൽ (!SDL_ConvertPixelsAndColorspace(width, height, format, colorspace, 0, convert->pixels, convert->pitch, dst_format, dst_colorspace, dst_properties, final_dst, final_dst_pitch)) {
            പോകുക done;
        }
    }
    result = true;

done:
    എങ്കിൽ (convert) {
        SDL_DestroySurface(convert);
    }
    തിരികെ result;
}

bool SDL_PremultiplyAlpha(പൂർണ്ണസംഖ്യ width, പൂർണ്ണസംഖ്യ height,
                         SDL_PixelFormat src_format, സ്ഥിരം ശൂന്യം *src, പൂർണ്ണസംഖ്യ src_pitch,
                         SDL_PixelFormat dst_format, ശൂന്യം *dst, പൂർണ്ണസംഖ്യ dst_pitch, bool linear)
{
    SDL_Colorspace src_colorspace = SDL_GetDefaultColorspaceForFormat(src_format);
    SDL_Colorspace dst_colorspace = SDL_GetDefaultColorspaceForFormat(dst_format);

    തിരികെ SDL_PremultiplyAlphaPixelsAndColorspace(width, height, src_format, src_colorspace, 0, src, src_pitch, dst_format, dst_colorspace, 0, dst, dst_pitch, linear);
}

bool SDL_PremultiplySurfaceAlpha(SDL_Surface *surface, bool linear)
{
    SDL_Colorspace colorspace;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        തിരികെ SDL_InvalidParamError("surface");
    }

    colorspace = surface->colorspace;

    തിരികെ SDL_PremultiplyAlphaPixelsAndColorspace(surface->w, surface->h, surface->format, colorspace, surface->props, surface->pixels, surface->pitch, surface->format, colorspace, surface->props, surface->pixels, surface->pitch, linear);
}

bool SDL_ClearSurface(SDL_Surface *surface, ദശാംശം r, ദശാംശം g, ദശാംശം b, ദശാംശം a)
{
    SDL_Rect clip_rect;
    bool result = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        തിരികെ SDL_InvalidParamError("surface");
    }

    SDL_GetSurfaceClipRect(surface, &clip_rect);
    SDL_SetSurfaceClipRect(surface, ശൂന്യ);

    എങ്കിൽ (!SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_BYTESPERPIXEL(surface->format) <= വലുപ്പം(Uint32)) {
        Uint32 color;

        color = SDL_MapSurfaceRGBA(surface,
                    (Uint8)SDL_roundf(SDL_clamp(r, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(g, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(b, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(a, 0.0f, 1.0f) * 255.0f));
        result = SDL_FillSurfaceRect(surface, ശൂന്യ, color);
    } അല്ലെങ്കിൽ എങ്കിൽ (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // We can't directly set an RGB value on a YUV surface
        SDL_Surface *tmp = SDL_CreateSurfaceUninitialized(surface->w, surface->h, SDL_PIXELFORMAT_ARGB8888);
        എങ്കിൽ (!tmp) {
            പോകുക done;
        }

        എങ്കിൽ (SDL_ClearSurface(tmp, r, g, b, a)) {
            result = SDL_ConvertPixelsAndColorspace(surface->w, surface->h, tmp->format, tmp->colorspace, tmp->props, tmp->pixels, tmp->pitch, surface->format, surface->colorspace, surface->props, surface->pixels, surface->pitch);
        }
        SDL_DestroySurface(tmp);
    } അല്ലെങ്കിൽ {
        // Take advantage of blit color conversion
        SDL_Surface *tmp = SDL_CreateSurfaceUninitialized(1, 1, SDL_PIXELFORMAT_RGBA128_FLOAT);
        എങ്കിൽ (!tmp) {
            പോകുക done;
        }
        SDL_SetSurfaceColorspace(tmp, surface->colorspace);
        SDL_SetSurfaceBlendMode(tmp, SDL_BLENDMODE_NONE);

        ദശാംശം *pixels = (ദശാംശം *)tmp->pixels;
        pixels[0] = r;
        pixels[1] = g;
        pixels[2] = b;
        pixels[3] = a;

        result = SDL_BlitSurfaceScaled(tmp, ശൂന്യ, surface, ശൂന്യ, SDL_SCALEMODE_NEAREST);
        SDL_DestroySurface(tmp);
    }

done:
    SDL_SetSurfaceClipRect(surface, &clip_rect);

    തിരികെ result;
}

Uint32 SDL_MapSurfaceRGB(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b)
{
    തിരികെ SDL_MapSurfaceRGBA(surface, r, g, b, SDL_ALPHA_OPAQUE);
}

Uint32 SDL_MapSurfaceRGBA(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        തിരികെ true;
    }
    തിരികെ SDL_MapRGBA(surface->fmt, surface->palette, r, g, b, a);
}

// This function Copyright 2023 Collabora Ltd., contributed to SDL under the ZLib license
bool SDL_ReadSurfacePixel(SDL_Surface *surface, പൂർണ്ണസംഖ്യ x, പൂർണ്ണസംഖ്യ y, Uint8 *r, Uint8 *g, Uint8 *b, Uint8 *a)
{
    Uint32 pixel = 0;
    size_t bytes_per_pixel;
    Uint8 unused;
    Uint8 *p;
    bool result = false;

    എങ്കിൽ (r) {
        *r = 0;
    } അല്ലെങ്കിൽ {
        r = &unused;
    }

    എങ്കിൽ (g) {
        *g = 0;
    } അല്ലെങ്കിൽ {
        g = &unused;
    }

    എങ്കിൽ (b) {
        *b = 0;
    } അല്ലെങ്കിൽ {
        b = &unused;
    }

    എങ്കിൽ (a) {
        *a = 0;
    } അല്ലെങ്കിൽ {
        a = &unused;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        തിരികെ SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        തിരികെ SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        തിരികെ SDL_InvalidParamError("y");
    }

    bytes_per_pixel = SDL_BYTESPERPIXEL(surface->format);

    എങ്കിൽ (SDL_MUSTLOCK(surface)) {
        എങ്കിൽ (!SDL_LockSurface(surface)) {
            തിരികെ false;
        }
    }

    p = (Uint8 *)surface->pixels + y * surface->pitch + x * bytes_per_pixel;

    എങ്കിൽ (bytes_per_pixel <= വലുപ്പം(pixel) &&
        !SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_COLORSPACEPRIMARIES(surface->colorspace) == SDL_COLOR_PRIMARIES_BT709) {
        /* Fill the appropriate number of least-significant bytes of pixel,
         * leaving the most-significant bytes set to zero */
#എങ്കിൽ SDL_BYTEORDER == SDL_BIG_ENDIAN
        SDL_memcpy(((Uint8 *)&pixel) + (വലുപ്പം(pixel) - bytes_per_pixel), p, bytes_per_pixel);
#അല്ലെങ്കിൽ
        SDL_memcpy(&pixel, p, bytes_per_pixel);
#endif
        SDL_GetRGBA(pixel, surface->fmt, surface->palette, r, g, b, a);
        result = true;
    } അല്ലെങ്കിൽ എങ്കിൽ (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // FIXME: We need code to extract a single macroblock from a YUV surface
        SDL_Surface *converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        എങ്കിൽ (converted) {
            result = SDL_ReadSurfacePixel(converted, x, y, r, g, b, a);
            SDL_DestroySurface(converted);
        }
    } അല്ലെങ്കിൽ {
        // This is really slow, but it gets the job done
        Uint8 rgba[4];

        എങ്കിൽ (SDL_ConvertPixelsAndColorspace(1, 1, surface->format, surface->colorspace, surface->props, p, surface->pitch, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, rgba, വലുപ്പം(rgba))) {
            *r = rgba[0];
            *g = rgba[1];
            *b = rgba[2];
            *a = rgba[3];
            result = true;
        }
    }

    എങ്കിൽ (SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }
    തിരികെ result;
}

bool SDL_ReadSurfacePixelFloat(SDL_Surface *surface, പൂർണ്ണസംഖ്യ x, പൂർണ്ണസംഖ്യ y, ദശാംശം *r, ദശാംശം *g, ദശാംശം *b, ദശാംശം *a)
{
    ദശാംശം unused;
    bool result = false;

    എങ്കിൽ (r) {
        *r = 0.0f;
    } അല്ലെങ്കിൽ {
        r = &unused;
    }

    എങ്കിൽ (g) {
        *g = 0.0f;
    } അല്ലെങ്കിൽ {
        g = &unused;
    }

    എങ്കിൽ (b) {
        *b = 0.0f;
    } അല്ലെങ്കിൽ {
        b = &unused;
    }

    എങ്കിൽ (a) {
        *a = 0.0f;
    } അല്ലെങ്കിൽ {
        a = &unused;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        തിരികെ SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        തിരികെ SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        തിരികെ SDL_InvalidParamError("y");
    }

    എങ്കിൽ (SDL_BYTESPERPIXEL(surface->format) <= വലുപ്പം(Uint32) &&
        !SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_COLORSPACEPRIMARIES(surface->colorspace) == SDL_COLOR_PRIMARIES_BT709) {
        Uint8 r8, g8, b8, a8;

        എങ്കിൽ (SDL_ReadSurfacePixel(surface, x, y, &r8, &g8, &b8, &a8)) {
            *r = (ദശാംശം)r8 / 255.0f;
            *g = (ദശാംശം)g8 / 255.0f;
            *b = (ദശാംശം)b8 / 255.0f;
            *a = (ദശാംശം)a8 / 255.0f;
            result = true;
        }
    } അല്ലെങ്കിൽ എങ്കിൽ (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // FIXME: We need code to extract a single macroblock from a YUV surface
        SDL_Surface *converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        എങ്കിൽ (converted) {
            result = SDL_ReadSurfacePixelFloat(converted, x, y, r, g, b, a);
            SDL_DestroySurface(converted);
        }
    } അല്ലെങ്കിൽ {
        // This is really slow, but it gets the job done
        ദശാംശം rgba[4];
        Uint8 *p;

        എങ്കിൽ (SDL_MUSTLOCK(surface)) {
            എങ്കിൽ (!SDL_LockSurface(surface)) {
                തിരികെ false;
            }
        }

        p = (Uint8 *)surface->pixels + y * surface->pitch + x * SDL_BYTESPERPIXEL(surface->format);

        എങ്കിൽ (surface->format == SDL_PIXELFORMAT_RGBA128_FLOAT) {
            SDL_memcpy(rgba, p, വലുപ്പം(rgba));
            result = true;
        } അല്ലെങ്കിൽ {
            SDL_Colorspace src_colorspace = surface->colorspace;
            SDL_Colorspace dst_colorspace = (src_colorspace == SDL_COLORSPACE_SRGB_LINEAR ? SDL_COLORSPACE_SRGB_LINEAR : SDL_COLORSPACE_SRGB);

            എങ്കിൽ (SDL_ConvertPixelsAndColorspace(1, 1, surface->format, src_colorspace, surface->props, p, surface->pitch, SDL_PIXELFORMAT_RGBA128_FLOAT, dst_colorspace, 0, rgba, വലുപ്പം(rgba))) {
                result = true;
            }
        }

        എങ്കിൽ (result) {
            *r = rgba[0];
            *g = rgba[1];
            *b = rgba[2];
            *a = rgba[3];
        }

        എങ്കിൽ (SDL_MUSTLOCK(surface)) {
            SDL_UnlockSurface(surface);
        }
    }
    തിരികെ result;
}

bool SDL_WriteSurfacePixel(SDL_Surface *surface, പൂർണ്ണസംഖ്യ x, പൂർണ്ണസംഖ്യ y, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    Uint32 pixel = 0;
    size_t bytes_per_pixel;
    Uint8 *p;
    bool result = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        തിരികെ SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        തിരികെ SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        തിരികെ SDL_InvalidParamError("y");
    }

    bytes_per_pixel = SDL_BYTESPERPIXEL(surface->format);

    എങ്കിൽ (SDL_MUSTLOCK(surface)) {
        എങ്കിൽ (!SDL_LockSurface(surface)) {
            തിരികെ false;
        }
    }

    p = (Uint8 *)surface->pixels + y * surface->pitch + x * bytes_per_pixel;

    എങ്കിൽ (bytes_per_pixel <= വലുപ്പം(pixel) && !SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        pixel = SDL_MapRGBA(surface->fmt, surface->palette, r, g, b, a);
#എങ്കിൽ SDL_BYTEORDER == SDL_BIG_ENDIAN
        SDL_memcpy(p, ((Uint8 *)&pixel) + (വലുപ്പം(pixel) - bytes_per_pixel), bytes_per_pixel);
#അല്ലെങ്കിൽ
        SDL_memcpy(p, &pixel, bytes_per_pixel);
#endif
        result = true;
    } അല്ലെങ്കിൽ എങ്കിൽ (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        result = SDL_Unsupported();
    } അല്ലെങ്കിൽ {
        // This is really slow, but it gets the job done
        Uint8 rgba[4];

        rgba[0] = r;
        rgba[1] = g;
        rgba[2] = b;
        rgba[3] = a;
        result = SDL_ConvertPixelsAndColorspace(1, 1, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, rgba, വലുപ്പം(rgba), surface->format, surface->colorspace, surface->props, p, surface->pitch);
    }

    എങ്കിൽ (SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }
    തിരികെ result;
}

bool SDL_WriteSurfacePixelFloat(SDL_Surface *surface, പൂർണ്ണസംഖ്യ x, പൂർണ്ണസംഖ്യ y, ദശാംശം r, ദശാംശം g, ദശാംശം b, ദശാംശം a)
{
    bool result = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        തിരികെ SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        തിരികെ SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        തിരികെ SDL_InvalidParamError("y");
    }

    എങ്കിൽ (SDL_BYTESPERPIXEL(surface->format) <= വലുപ്പം(Uint32) && !SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        Uint8 r8, g8, b8, a8;

        r8 = (Uint8)SDL_round(SDL_clamp(r, 0.0f, 1.0f) * 255.0f);
        g8 = (Uint8)SDL_round(SDL_clamp(g, 0.0f, 1.0f) * 255.0f);
        b8 = (Uint8)SDL_round(SDL_clamp(b, 0.0f, 1.0f) * 255.0f);
        a8 = (Uint8)SDL_round(SDL_clamp(a, 0.0f, 1.0f) * 255.0f);
        എങ്കിൽ (SDL_WriteSurfacePixel(surface, x, y, r8, g8, b8, a8)) {
            result = true;
        }
    } അല്ലെങ്കിൽ എങ്കിൽ (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        result = SDL_Unsupported();
    } അല്ലെങ്കിൽ {
        // This is really slow, but it gets the job done
        ദശാംശം rgba[4];
        Uint8 *p;

        എങ്കിൽ (SDL_MUSTLOCK(surface)) {
            എങ്കിൽ (!SDL_LockSurface(surface)) {
                തിരികെ false;
            }
        }

        p = (Uint8 *)surface->pixels + y * surface->pitch + x * SDL_BYTESPERPIXEL(surface->format);

        rgba[0] = r;
        rgba[1] = g;
        rgba[2] = b;
        rgba[3] = a;

        എങ്കിൽ (surface->format == SDL_PIXELFORMAT_RGBA128_FLOAT) {
            SDL_memcpy(p, rgba, വലുപ്പം(rgba));
            result = true;
        } അല്ലെങ്കിൽ {
            SDL_Colorspace dst_colorspace = surface->colorspace;
            SDL_Colorspace src_colorspace = (dst_colorspace == SDL_COLORSPACE_SRGB_LINEAR ? SDL_COLORSPACE_SRGB_LINEAR : SDL_COLORSPACE_SRGB);

            result = SDL_ConvertPixelsAndColorspace(1, 1, SDL_PIXELFORMAT_RGBA128_FLOAT, src_colorspace, 0, rgba, വലുപ്പം(rgba), surface->format, dst_colorspace, surface->props, p, surface->pitch);
        }

        എങ്കിൽ (SDL_MUSTLOCK(surface)) {
            SDL_UnlockSurface(surface);
        }
    }
    തിരികെ result;
}

/*
 * Free a surface created by the above function.
 */
ശൂന്യം SDL_DestroySurface(SDL_Surface *surface)
{
    എങ്കിൽ (!SDL_SurfaceValid(surface)) {
        തിരികെ;
    }
    എങ്കിൽ (surface->internal_flags & SDL_INTERNAL_SURFACE_DONTFREE) {
        തിരികെ;
    }
    എങ്കിൽ (--surface->refcount > 0) {
        തിരികെ;
    }

    SDL_RemoveSurfaceAlternateImages(surface);

    SDL_DestroyProperties(surface->props);

    SDL_InvalidateMap(&surface->map);

    ആകുമ്പോൾ (surface->locked > 0) {
        SDL_UnlockSurface(surface);
    }
#ifdef SDL_HAVE_RLE
    എങ്കിൽ (surface->internal_flags & SDL_INTERNAL_SURFACE_RLEACCEL) {
        SDL_UnRLESurface(surface);
    }
#endif
    SDL_SetSurfacePalette(surface, ശൂന്യ);

    എങ്കിൽ (surface->flags & SDL_SURFACE_PREALLOCATED) {
        // Don't free
    } അല്ലെങ്കിൽ എങ്കിൽ (surface->flags & SDL_SURFACE_SIMD_ALIGNED) {
        // Free aligned
        SDL_aligned_free(surface->pixels);
    } അല്ലെങ്കിൽ {
        // Normal
        SDL_free(surface->pixels);
    }

    surface->reserved = ശൂന്യ;

    എങ്കിൽ (!(surface->internal_flags & SDL_INTERNAL_SURFACE_അട്ടി)) {
        SDL_free(surface);
    }
}

SDL_Surface *SDL_LoadSurface_IO(SDL_IOStream *src, bool closeio)
{
    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        തിരികെ ശൂന്യ;
    }

    എങ്കിൽ (SDL_IsBMP(src)) {
        തിരികെ SDL_LoadBMP_IO(src, closeio);
    } അല്ലെങ്കിൽ എങ്കിൽ (SDL_IsPNG(src)) {
        തിരികെ SDL_LoadPNG_IO(src, closeio);
    } അല്ലെങ്കിൽ എങ്കിൽ (SDL_IsJPG(src)) {
        തിരികെ SDL_LoadJPG_IO(src, closeio);
    } അല്ലെങ്കിൽ {
        എങ്കിൽ (closeio) {
            SDL_CloseIO(src);
        }
        SDL_SetError("Unsupported image format");
        തിരികെ ശൂന്യ;
    }
}

SDL_Surface *SDL_LoadSurface(സ്ഥിരം അക്ഷരം *file)
{
    SDL_IOStream *stream = SDL_IOFromFile(file, "rb");
    എങ്കിൽ (!stream) {
        തിരികെ ശൂന്യ;
    }

    തിരികെ SDL_LoadSurface_IO(stream, true);
}
