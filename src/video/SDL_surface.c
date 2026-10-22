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
#شامل "SDL_internal.h"

#شامل "SDL_sysvideo.h"
#شامل "SDL_video_c.h"
#شامل "SDL_RLEaccel_c.h"
#شامل "SDL_pixels_c.h"
#شامل "SDL_rotate.h"
#شامل "SDL_stb_c.h"
#شامل "SDL_yuv_c.h"
#شامل "../render/SDL_sysrender.h"

#شامل "SDL_surface_c.h"


// Check to make sure we can safely check multiplication of surface w and pitch and it won't overflow size_t
SDL_COMPILE_TIME_ASSERT(surface_size_assumptions,
                        اندازه(صحیح) == اندازه(Sint32) && اندازه(size_t) >= اندازه(Sint32));

SDL_COMPILE_TIME_ASSERT(can_indicate_overflow, SDL_SIZE_MAX > SDL_MAX_SINT32);

// Magic!
ایستا نویسه SDL_surface_magic;

// Public routines

bool SDL_SurfaceValid(SDL_Surface *surface)
{
    بازگشت (surface && surface->reserved == &SDL_surface_magic);
}

تهی SDL_UpdateSurfaceLockFlag(SDL_Surface *surface)
{
    // We need to mark the surface as needing unlock while locked
    اگر ((surface->flags & SDL_SURFACE_LOCKED) ||
        (surface->internal_flags & SDL_INTERNAL_SURFACE_RLEACCEL)) {
        surface->flags |= SDL_SURFACE_LOCK_NEEDED;
    } وگرنه {
        surface->flags &= ~SDL_SURFACE_LOCK_NEEDED;
    }
}

/*
 * Calculate the pad-aligned scanline width of a surface.
 *
 * for FOURCC, use SDL_CalculateYUVSize()
 */
ایستا bool SDL_CalculateRGBSize(Uint32 format, size_t width, size_t height, size_t *size, size_t *pitch, bool minimal)
{
    اگر (SDL_BITSPERPIXEL(format) >= 8) {
        اگر (!SDL_size_mul_check_overflow(width, SDL_BYTESPERPIXEL(format), pitch)) {
            بازگشت SDL_SetError("width * bpp would overflow");
        }
    } وگرنه {
        اگر (!SDL_size_mul_check_overflow(width, SDL_BITSPERPIXEL(format), pitch)) {
            بازگشت SDL_SetError("width * bpp would overflow");
        }
        اگر (!SDL_size_add_check_overflow(*pitch, 7, pitch)) {
            بازگشت SDL_SetError("aligning pitch would overflow");
        }
        *pitch /= 8;
    }
    اگر (!minimal) {
        // 4-byte aligning for speed
        اگر (!SDL_size_add_check_overflow(*pitch, 3, pitch)) {
            بازگشت SDL_SetError("aligning pitch would overflow");
        }
        *pitch &= ~3;
    }

    اگر (!SDL_size_mul_check_overflow(height, *pitch, size)) {
        بازگشت SDL_SetError("height * pitch would overflow");
    }

    بازگشت true;
}

bool SDL_CalculateSurfaceSize(SDL_PixelFormat format, صحیح width, صحیح height, size_t *size, size_t *pitch, bool minimalPitch)
{
    size_t p = 0, sz = 0;

    اگر (size) {
        *size = 0;
    }

    اگر (pitch) {
        *pitch = 0;
    }

    اگر (SDL_ISPIXELFORMAT_FOURCC(format)) {
        اگر (format == SDL_PIXELFORMAT_MJPG) {
            // We don't know in advance what it will be, we'll figure it out later.
            بازگشت true;
        }

        اگر (!SDL_CalculateYUVSize(format, width, height, &sz, &p)) {
            // Overflow...
            بازگشت false;
        }
    } وگرنه {
        اگر (!SDL_CalculateRGBSize(format, width, height, &sz, &p, minimalPitch)) {
            // Overflow...
            بازگشت false;
        }
    }

    اگر (size) {
        *size = sz;
    }

    اگر (pitch) {
        *pitch = p;
    }

    بازگشت true;
}

ایستا bool SDL_InitializeSurface(SDL_Surface *surface, صحیح width, صحیح height, SDL_PixelFormat format, SDL_Colorspace colorspace, SDL_PropertiesID props, تهی *pixels, صحیح pitch, bool onstack)
{
    SDL_zerop(surface);

    surface->flags = SDL_SURFACE_PREALLOCATED;
    surface->format = format;
    surface->w = width;
    surface->h = height;
    surface->pixels = pixels;
    surface->pitch = pitch;
    surface->reserved = &SDL_surface_magic;

    اگر (onstack) {
        surface->internal_flags |= SDL_INTERNAL_SURFACE_پشته;
    }

    surface->fmt = SDL_GetPixelFormatDetails(format);
    اگر (!surface->fmt) {
        SDL_DestroySurface(surface);
        بازگشت false;
    }

    // Initialize the clip rect
    surface->clip_rect.w = width;
    surface->clip_rect.h = height;

    // Allocate an empty mapping
    surface->map.info.r = 0xFF;
    surface->map.info.g = 0xFF;
    surface->map.info.b = 0xFF;
    surface->map.info.a = 0xFF;

    اگر (colorspace == SDL_COLORSPACE_UNKNOWN) {
        surface->colorspace = SDL_GetDefaultColorspaceForFormat(format);
    } وگرنه {
        surface->colorspace = colorspace;
    }

    اگر (props) {
        اگر (!SDL_CopyProperties(props, SDL_GetSurfaceProperties(surface))) {
            SDL_DestroySurface(surface);
            بازگشت false;
        }
    }

    // By default surfaces with an alpha mask are set up for blending
    اگر (SDL_ISPIXELFORMAT_ALPHA(surface->format)) {
        SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
    }

    // The surface is ready to go
    surface->refcount = 1;
    بازگشت true;
}

/*
 * Create an empty surface of the appropriate depth using the given format
 */
ایستا SDL_Surface *SDL_CreateSurfaceInternal(صحیح width, صحیح height, SDL_PixelFormat format, bool clear_surface)
{
    size_t pitch, size;
    SDL_Surface *surface;

    CHECK_PARAM(width < 0) {
        SDL_InvalidParamError("width");
        بازگشت پوچ;
    }

    CHECK_PARAM(height < 0) {
        SDL_InvalidParamError("height");
        بازگشت پوچ;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        بازگشت پوچ;
    }

    اگر (!SDL_CalculateSurfaceSize(format, width, height, &size, &pitch, false /* not minimal pitch */)) {
        // Overflow...
        بازگشت پوچ;
    }

    // Allocate and initialize the surface
    surface = (SDL_Surface *)SDL_malloc(اندازه(*surface));
    اگر (!surface) {
        بازگشت پوچ;
    }

    اگر (!SDL_InitializeSurface(surface, width, height, format, SDL_COLORSPACE_UNKNOWN, 0, پوچ, (صحیح)pitch, false)) {
        بازگشت پوچ;
    }

    اگر (surface->w && surface->h && format != SDL_PIXELFORMAT_MJPG) {
        surface->flags &= ~SDL_SURFACE_PREALLOCATED;
        اگر (SDL_GetHintBoolean("SDL_SURFACE_MALLOC", false)) {
            اگر (clear_surface) {
                surface->pixels = SDL_calloc(1, size);
            } وگرنه {
                surface->pixels = SDL_malloc(size);
            }
        } وگرنه {
            surface->flags |= SDL_SURFACE_SIMD_ALIGNED;
            اگر (clear_surface) {
                surface->pixels = SDL_aligned_alloc_zero(SDL_GetSIMDAlignment(), size);
            } وگرنه {
                surface->pixels = SDL_aligned_alloc(SDL_GetSIMDAlignment(), size);
            }
        }
        اگر (!surface->pixels) {
            SDL_DestroySurface(surface);
            بازگشت پوچ;
        }
    }
    بازگشت surface;
}

SDL_Surface *SDL_CreateSurfaceZeroed(صحیح width, صحیح height, SDL_PixelFormat format)
{
    بازگشت SDL_CreateSurfaceInternal(width, height, format, true);
}

SDL_Surface *SDL_CreateSurfaceUninitialized(صحیح width, صحیح height, SDL_PixelFormat format)
{
    بازگشت SDL_CreateSurfaceInternal(width, height, format, false);
}

SDL_Surface *SDL_CreateSurface(صحیح width, صحیح height, SDL_PixelFormat format)
{
    بازگشت SDL_CreateSurfaceZeroed(width, height, format);
}


/*
 * Create an RGB surface from an existing memory buffer using the given
 * enum SDL_PIXELFORMAT_* format
 */
SDL_Surface *SDL_CreateSurfaceFrom(صحیح width, صحیح height, SDL_PixelFormat format, تهی *pixels, صحیح pitch)
{
    CHECK_PARAM(width < 0) {
        SDL_InvalidParamError("width");
        بازگشت پوچ;
    }

    CHECK_PARAM(height < 0) {
        SDL_InvalidParamError("height");
        بازگشت پوچ;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        بازگشت پوچ;
    }

    اگر (pitch == 0 && !pixels) {
        // The application will fill these in later with valid values
    } وگرنه {
        size_t minimalPitch;

        اگر (!SDL_CalculateSurfaceSize(format, width, height, پوچ, &minimalPitch, true /* minimal pitch */)) {
            // Overflow...
            بازگشت پوچ;
        }

        CHECK_PARAM(pitch < 0 || (size_t)pitch < minimalPitch) {
            SDL_InvalidParamError("pitch");
            بازگشت پوچ;
        }
    }

    // Allocate and initialize the surface
    SDL_Surface *surface = (SDL_Surface *)SDL_malloc(اندازه(*surface));
    اگر (!surface ||
        !SDL_InitializeSurface(surface, width, height, format, SDL_COLORSPACE_UNKNOWN, 0, pixels, pitch, false)) {
        بازگشت پوچ;
    }
    بازگشت surface;
}

SDL_PropertiesID SDL_GetSurfaceProperties(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        بازگشت 0;
    }

    اگر (!surface->props) {
        surface->props = SDL_CreateProperties();
    }
    بازگشت surface->props;
}

bool SDL_SetSurfaceColorspace(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        بازگشت SDL_InvalidParamError("surface");
    }

    surface->colorspace = colorspace;
    بازگشت true;
}

SDL_Colorspace SDL_GetSurfaceColorspace(SDL_Surface *surface)
{
    اگر (!SDL_SurfaceValid(surface)) {
        بازگشت SDL_COLORSPACE_UNKNOWN;
    }

    بازگشت surface->colorspace;
}

اعشاری SDL_GetDefaultSDRWhitePoint(SDL_Colorspace colorspace)
{
    بازگشت SDL_GetSurfaceSDRWhitePoint(پوچ, colorspace);
}

اعشاری SDL_GetSurfaceSDRWhitePoint(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    SDL_TransferCharacteristics transfer = SDL_COLORSPACETRANSFER(colorspace);

    اگر (transfer == SDL_TRANSFER_CHARACTERISTICS_LINEAR ||
        transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
        SDL_PropertiesID props;
        اعشاری default_مقدار = 1.0f;

        اگر (SDL_SurfaceValid(surface)) {
            props = surface->props;
        } وگرنه {
            props = 0;
        }
        اگر (transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
            /* The older standards use an SDR white point of 100 nits.
             * ITU-R BT.2408-6 recommends using an SDR white point of 203 nits.
             * This is the default Chrome uses, and what a lot of game content
             * assumes, so we'll go with that.
             */
            ثابت اعشاری DEFAULT_PQ_SDR_WHITE_POINT = 203.0f;
            default_مقدار = DEFAULT_PQ_SDR_WHITE_POINT;
        }
        بازگشت SDL_GetFloatProperty(props, SDL_PROP_SURFACE_SDR_WHITE_POINT_FLOAT, default_مقدار);
    }
    بازگشت 1.0f;
}

اعشاری SDL_GetDefaultHDRHeadroom(SDL_Colorspace colorspace)
{
    بازگشت SDL_GetSurfaceHDRHeadroom(پوچ, colorspace);
}

اعشاری SDL_GetSurfaceHDRHeadroom(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    SDL_TransferCharacteristics transfer = SDL_COLORSPACETRANSFER(colorspace);

    اگر (transfer == SDL_TRANSFER_CHARACTERISTICS_LINEAR ||
        transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
        SDL_PropertiesID props;
        اعشاری default_مقدار = 0.0f;

        اگر (SDL_SurfaceValid(surface)) {
            props = surface->props;
        } وگرنه {
            props = 0;
        }
        بازگشت SDL_GetFloatProperty(props, SDL_PROP_SURFACE_HDR_HEADROOM_FLOAT, default_مقدار);
    }
    بازگشت 1.0f;
}

SDL_Palette *SDL_CreateSurfacePalette(SDL_Surface *surface)
{
    SDL_Palette *palette;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        بازگشت پوچ;
    }

    CHECK_PARAM(!SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        SDL_SetError("The surface is not indexed format");
        بازگشت پوچ;
    }

    palette = SDL_CreatePalette((1 << SDL_BITSPERPIXEL(surface->format)));
    اگر (!palette) {
        بازگشت پوچ;
    }

    اگر (palette->ncolors == 2) {
        // Create a black and white bitmap palette
        palette->colors[0].r = 0xFF;
        palette->colors[0].g = 0xFF;
        palette->colors[0].b = 0xFF;
        palette->colors[1].r = 0x00;
        palette->colors[1].g = 0x00;
        palette->colors[1].b = 0x00;
    }

    اگر (!SDL_SetSurfacePalette(surface, palette)) {
        SDL_DestroyPalette(palette);
        بازگشت پوچ;
    }

    // The surface has retained the palette, we can remove the reference here
    SDL_assert(palette->refcount == 2);
    SDL_DestroyPalette(palette);
    بازگشت palette;
}

bool SDL_SetSurfacePalette(SDL_Surface *surface, SDL_Palette *palette)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        بازگشت SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(palette && !SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        بازگشت SDL_SetError("Surface doesn't use a palette");
    }

    CHECK_PARAM(palette && palette->ncolors > (1 << SDL_BITSPERPIXEL(surface->format))) {
        بازگشت SDL_SetError("Palette doesn't match surface format");
    }

    اگر (palette != surface->palette) {
        اگر (surface->palette) {
            SDL_DestroyPalette(surface->palette);
        }

        surface->palette = palette;

        اگر (surface->palette) {
            ++surface->palette->refcount;
        }
    }

    SDL_InvalidateMap(&surface->map);

    بازگشت true;
}

SDL_Palette *SDL_GetSurfacePalette(SDL_Surface *surface)
{
    اگر (!SDL_SurfaceValid(surface)) {
        بازگشت پوچ;
    }

    بازگشت surface->palette;
}

bool SDL_AddSurfaceAlternateImage(SDL_Surface *surface, SDL_Surface *image)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        بازگشت SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(!SDL_SurfaceValid(image)) {
        بازگشت SDL_InvalidParamError("image");
    }

    SDL_Surface **images = (SDL_Surface **)SDL_realloc(surface->images, (surface->رقم_images + 1) * اندازه(*images));
    اگر (!images) {
        بازگشت false;
    }
    images[surface->رقم_images] = image;
    surface->images = images;
    ++surface->رقم_images;
    ++image->refcount;
    بازگشت true;
}

bool SDL_SurfaceHasAlternateImages(SDL_Surface *surface)
{
    اگر (!SDL_SurfaceValid(surface)) {
        بازگشت false;
    }

    بازگشت (surface->رقم_images > 0);
}

SDL_Surface **SDL_GetSurfaceImages(SDL_Surface *surface, صحیح *شمار)
{
    اگر (شمار) {
        *شمار = 0;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        بازگشت پوچ;
    }

    صحیح رقم_images = 1 + surface->رقم_images;
    SDL_Surface **images = (SDL_Surface **)SDL_malloc((رقم_images + 1) * اندازه(*images));
    اگر (!images) {
        بازگشت پوچ;
    }
    images[0] = surface;
    اگر (surface->رقم_images > 0) {
        SDL_memcpy(&images[1], surface->images, (surface->رقم_images * اندازه(images[1])));
    }
    images[رقم_images] = پوچ;

    اگر (شمار) {
        *شمار = رقم_images;
    }
    بازگشت images;
}

SDL_Surface *SDL_GetSurfaceImage(SDL_Surface *surface, اعشاری display_scale)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        بازگشت پوچ;
    }

    اگر (!SDL_SurfaceHasAlternateImages(surface)) {
        ++surface->refcount;
        بازگشت surface;
    }

    // This surface has high DPI images, pick the best one available, or scale one to the correct size
    SDL_Surface **images = SDL_GetSurfaceImages(surface, پوچ);
    اگر (!images) {
        // Failure, fall back to the existing surface
        ++surface->refcount;
        بازگشت surface;
    }

    // Find closest image. Images that are larger than the
    // desired size are preferred over images that are smaller.
    SDL_Surface *closest = پوچ;
    صحیح desired_w = (صحیح)SDL_round(surface->w * display_scale);
    صحیح desired_h = (صحیح)SDL_round(surface->h * display_scale);
    صحیح desired_size = desired_w * desired_h;
    صحیح closest_distance = -1;
    صحیح closest_size = -1;
    برای (صحیح i = 0; images[i]; ++i) {
        SDL_Surface *candidate = images[i];
        صحیح size = candidate->w * candidate->h;
        صحیح delta_w = (candidate->w - desired_w);
        صحیح delta_h = (candidate->h - desired_h);
        صحیح distance = (delta_w * delta_w) + (delta_h * delta_h);
        اگر (closest_distance < 0 || distance < closest_distance ||
            (size > desired_size && closest_size < desired_size)) {
            closest = candidate;
            closest_distance = distance;
            closest_size = size;
        }
    }
    SDL_free(images);
    SDL_assert(closest != پوچ);    // We should always have at least one surface

    اگر (closest->w == desired_w && closest->h == desired_h) {
        ++closest->refcount;
        بازگشت closest;
    }

    // We need to scale the image to the correct size. To maintain good image quality, downscaling
    // is done in steps, never reducing the width and height by more than half each time.
    SDL_Surface *scaled = closest;
    انجامبده {
        صحیح next_scaled_w = SDL_max(desired_w, (scaled->w + 1) / 2);
        صحیح next_scaled_h = SDL_max(desired_h, (scaled->h + 1) / 2);
        SDL_Surface *next_scaled = SDL_ScaleSurface(scaled, next_scaled_w, next_scaled_h, SDL_SCALEMODE_LINEAR);
        اگر (scaled != closest) {
            SDL_DestroySurface(scaled);
        }
        scaled = next_scaled;
        اگر (!scaled) {
            // Failure, fall back to the closest surface
            ++closest->refcount;
            بازگشت closest;
        }
    } وقتی (scaled->w != desired_w || scaled->h != desired_h);

    بازگشت scaled;
}

تهی SDL_RemoveSurfaceAlternateImages(SDL_Surface *surface)
{
    اگر (!SDL_SurfaceValid(surface)) {
        بازگشت;
    }

    اگر (surface->رقم_images > 0) {
        برای (صحیح i = 0; i < surface->رقم_images; ++i) {
            SDL_DestroySurface(surface->images[i]);
        }
        SDL_free(surface->images);
        surface->images = پوچ;
        surface->رقم_images = 0;
    }
}

bool SDL_SetSurfaceRLE(SDL_Surface *surface, bool enabled)
{
    صحیح flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        بازگشت SDL_InvalidParamError("surface");
    }

    flags = surface->map.info.flags;
    اگر (enabled) {
        surface->map.info.flags |= SDL_COPY_RLE_DESIRED;
    } وگرنه {
        surface->map.info.flags &= ~SDL_COPY_RLE_DESIRED;
    }
    اگر (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    بازگشت true;
}

bool SDL_SurfaceHasRLE(SDL_Surface *surface)
{
    اگر (!SDL_SurfaceValid(surface)) {
        بازگشت false;
    }

    اگر (!(surface->map.info.flags & SDL_COPY_RLE_DESIRED)) {
        بازگشت false;
    }

    بازگشت true;
}

bool SDL_Set_Surface_Color_کلید(SDL_Surface *surface, bool enabled, Uint32 کلید)
{
    صحیح flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        بازگشت SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(surface->palette && کلید >= ((Uint32)surface->palette->ncolors)) {
        بازگشت SDL_InvalidParamError("key");
    }

    flags = surface->map.info.flags;
    اگر (enabled) {
        surface->map.info.flags |= SDL_COPY_COLORKEY;
        surface->map.info.colorkey = کلید;
    } وگرنه {
        surface->map.info.flags &= ~SDL_COPY_COLORKEY;
    }
    اگر (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }

    بازگشت true;
}

bool SDL_Surface_Has_Color_کلید(SDL_Surface *surface)
{
    اگر (!SDL_SurfaceValid(surface)) {
        بازگشت false;
    }

    اگر (!(surface->map.info.flags & SDL_COPY_COLORKEY)) {
        بازگشت false;
    }

    بازگشت true;
}

bool SDL_Get_Surface_Color_کلید(SDL_Surface *surface, Uint32 *کلید)
{
    اگر (کلید) {
        *کلید = 0;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        بازگشت SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(!(surface->map.info.flags & SDL_COPY_COLORKEY)) {
        بازگشت SDL_SetError("Surface doesn't have a colorkey");
    }

    اگر (کلید) {
        *کلید = surface->map.info.colorkey;
    }
    بازگشت true;
}

/* This is a fairly slow function to switch from colorkey to alpha
   NB: it doesn't handle bpp 1 or 3, because they have no alpha channel */
ایستا تهی SDL_ConvertColorkeyToAlpha(SDL_Surface *surface, bool ignore_alpha)
{
    صحیح x, y, bpp;

    اگر (!SDL_SurfaceValid(surface)) {
        بازگشت;
    }

    اگر (!(surface->map.info.flags & SDL_COPY_COLORKEY) ||
        !SDL_ISPIXELFORMAT_ALPHA(surface->format)) {
        بازگشت;
    }

    bpp = SDL_BYTESPERPIXEL(surface->format);

    SDL_LockSurface(surface);

    اگر (bpp == 2) {
        Uint16 *row, *spot;
        Uint16 ckey = (Uint16)surface->map.info.colorkey;
        Uint16 mask = (Uint16)(~surface->fmt->Amask);

        // Ignore, or not, alpha in colorkey comparison
        اگر (ignore_alpha) {
            ckey &= mask;
            row = (Uint16 *)surface->pixels;
            برای (y = surface->h; y--;) {
                spot = row;
                برای (x = surface->w; x--;) {
                    اگر ((*spot & mask) == ckey) {
                        *spot &= mask;
                    }
                    ++spot;
                }
                row += surface->pitch / 2;
            }
        } وگرنه {
            row = (Uint16 *)surface->pixels;
            برای (y = surface->h; y--;) {
                spot = row;
                برای (x = surface->w; x--;) {
                    اگر (*spot == ckey) {
                        *spot &= mask;
                    }
                    ++spot;
                }
                row += surface->pitch / 2;
            }
        }
    } وگرنه اگر (bpp == 4) {
        Uint32 *row, *spot;
        Uint32 ckey = surface->map.info.colorkey;
        Uint32 mask = ~surface->fmt->Amask;

        // Ignore, or not, alpha in colorkey comparison
        اگر (ignore_alpha) {
            ckey &= mask;
            row = (Uint32 *)surface->pixels;
            برای (y = surface->h; y--;) {
                spot = row;
                برای (x = surface->w; x--;) {
                    اگر ((*spot & mask) == ckey) {
                        *spot &= mask;
                    }
                    ++spot;
                }
                row += surface->pitch / 4;
            }
        } وگرنه {
            row = (Uint32 *)surface->pixels;
            برای (y = surface->h; y--;) {
                spot = row;
                برای (x = surface->w; x--;) {
                    اگر (*spot == ckey) {
                        *spot &= mask;
                    }
                    ++spot;
                }
                row += surface->pitch / 4;
            }
        }
    }

    SDL_UnlockSurface(surface);

    SDL_Set_Surface_Color_کلید(surface, false, 0);
    SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
}

bool SDL_SetSurfaceColorMod(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b)
{
    صحیح flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        بازگشت SDL_InvalidParamError("surface");
    }

    surface->map.info.r = r;
    surface->map.info.g = g;
    surface->map.info.b = b;

    flags = surface->map.info.flags;
    اگر (r != 0xFF || g != 0xFF || b != 0xFF) {
        surface->map.info.flags |= SDL_COPY_MODULATE_COLOR;
    } وگرنه {
        surface->map.info.flags &= ~SDL_COPY_MODULATE_COLOR;
    }
    اگر (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    بازگشت true;
}

bool SDL_GetSurfaceColorMod(SDL_Surface *surface, Uint8 *r, Uint8 *g, Uint8 *b)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        اگر (r) {
            *r = 255;
        }
        اگر (g) {
            *g = 255;
        }
        اگر (b) {
            *b = 255;
        }
        بازگشت SDL_InvalidParamError("surface");
    }

    اگر (r) {
        *r = surface->map.info.r;
    }
    اگر (g) {
        *g = surface->map.info.g;
    }
    اگر (b) {
        *b = surface->map.info.b;
    }
    بازگشت true;
}

bool SDL_SetSurfaceAlphaMod(SDL_Surface *surface, Uint8 alpha)
{
    صحیح flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        بازگشت SDL_InvalidParamError("surface");
    }

    surface->map.info.a = alpha;

    flags = surface->map.info.flags;
    اگر (alpha != 0xFF) {
        surface->map.info.flags |= SDL_COPY_MODULATE_ALPHA;
    } وگرنه {
        surface->map.info.flags &= ~SDL_COPY_MODULATE_ALPHA;
    }
    اگر (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    بازگشت true;
}

bool SDL_GetSurfaceAlphaMod(SDL_Surface *surface, Uint8 *alpha)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        اگر (alpha) {
            *alpha = 255;
        }
        بازگشت SDL_InvalidParamError("surface");
    }

    اگر (alpha) {
        *alpha = surface->map.info.a;
    }
    بازگشت true;
}

bool SDL_SetSurfaceBlendMode(SDL_Surface *surface, SDL_BlendMode blendMode)
{
    صحیح flags;
    bool result = true;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        بازگشت SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(blendMode == SDL_BLENDMODE_INVALID) {
        بازگشت SDL_InvalidParamError("blendMode");
    }

    flags = surface->map.info.flags;
    surface->map.info.flags &= ~SDL_COPY_BLEND_MASK;
    انتخاب (blendMode) {
    حالت SDL_BLENDMODE_NONE:
        بشکن;
    حالت SDL_BLENDMODE_BLEND:
        surface->map.info.flags |= SDL_COPY_BLEND;
        بشکن;
    حالت SDL_BLENDMODE_BLEND_PREMULTIPLIED:
        surface->map.info.flags |= SDL_COPY_BLEND_PREMULTIPLIED;
        بشکن;
    حالت SDL_BLENDMODE_ADD:
        surface->map.info.flags |= SDL_COPY_ADD;
        بشکن;
    حالت SDL_BLENDMODE_ADD_PREMULTIPLIED:
        surface->map.info.flags |= SDL_COPY_ADD_PREMULTIPLIED;
        بشکن;
    حالت SDL_BLENDMODE_MOD:
        surface->map.info.flags |= SDL_COPY_MOD;
        بشکن;
    حالت SDL_BLENDMODE_MUL:
        surface->map.info.flags |= SDL_COPY_MUL;
        بشکن;
    پیشفرض:
        result = SDL_Unsupported();
        بشکن;
    }

    اگر (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }

    بازگشت result;
}

bool SDL_GetSurfaceBlendMode(SDL_Surface *surface, SDL_BlendMode *blendMode)
{
    اگر (blendMode) {
        *blendMode = SDL_BLENDMODE_INVALID;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        بازگشت SDL_InvalidParamError("surface");
    }

    اگر (!blendMode) {
        بازگشت true;
    }

    انتخاب (surface->map.info.flags & SDL_COPY_BLEND_MASK) {
    حالت SDL_COPY_BLEND:
        *blendMode = SDL_BLENDMODE_BLEND;
        بشکن;
    حالت SDL_COPY_BLEND_PREMULTIPLIED:
        *blendMode = SDL_BLENDMODE_BLEND_PREMULTIPLIED;
        بشکن;
    حالت SDL_COPY_ADD:
        *blendMode = SDL_BLENDMODE_ADD;
        بشکن;
    حالت SDL_COPY_ADD_PREMULTIPLIED:
        *blendMode = SDL_BLENDMODE_ADD_PREMULTIPLIED;
        بشکن;
    حالت SDL_COPY_MOD:
        *blendMode = SDL_BLENDMODE_MOD;
        بشکن;
    حالت SDL_COPY_MUL:
        *blendMode = SDL_BLENDMODE_MUL;
        بشکن;
    پیشفرض:
        *blendMode = SDL_BLENDMODE_NONE;
        بشکن;
    }
    بازگشت true;
}

bool SDL_SetSurfaceClipRect(SDL_Surface *surface, ثابت SDL_Rect *rect)
{
    SDL_Rect full_rect;

    // Don't do anything if there's no surface to act on
    اگر (!SDL_SurfaceValid(surface)) {
        بازگشت false;
    }

    // Set up the full surface rectangle
    full_rect.x = 0;
    full_rect.y = 0;
    full_rect.w = surface->w;
    full_rect.h = surface->h;

    // Set the clipping rectangle
    اگر (!rect) {
        surface->clip_rect = full_rect;
        بازگشت true;
    }
    بازگشت SDL_GetRectIntersection(rect, &full_rect, &surface->clip_rect);
}

bool SDL_GetSurfaceClipRect(SDL_Surface *surface, SDL_Rect *rect)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        اگر (rect) {
            SDL_zerop(rect);
        }
        بازگشت SDL_InvalidParamError("surface");
    }
    CHECK_PARAM(!rect) {
        بازگشت SDL_InvalidParamError("rect");
    }
    *rect = surface->clip_rect;
    بازگشت true;
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
bool SDL_BlitSurfaceUnchecked(SDL_Surface *src, ثابت SDL_Rect *srcrect,
                             SDL_Surface *dst, ثابت SDL_Rect *dstrect)
{
    // Check to make sure the blit mapping is valid
    اگر (!SDL_ValidateMap(src, dst)) {
        بازگشت false;
    }
    بازگشت src->map.blit(src, srcrect, dst, dstrect);
}

bool SDL_BlitSurface(SDL_Surface *src, ثابت SDL_Rect *srcrect, SDL_Surface *dst, ثابت SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src) || (!src->pixels && !SDL_MUSTLOCK(src))) {
        بازگشت SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst) || (!dst->pixels && !SDL_MUSTLOCK(dst))) {
        بازگشت SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        بازگشت SDL_SetError("Surfaces must not be locked during blit");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    اگر (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
    } وگرنه {
        r_dst.x = 0;
        r_dst.y = 0;
    }

    // clip the source rectangle to the source surface
    اگر (srcrect) {
        SDL_Rect tmp;
        اگر (SDL_GetRectIntersection(srcrect, &r_src, &tmp) == false) {
            بازگشت true;
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
        اگر (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &tmp) == false) {
            بازگشت true;
        }

        // Shift srcrect, if dstrect has changed
        r_src.x += tmp.x - r_dst.x;
        r_src.y += tmp.y - r_dst.y;
        r_src.w = tmp.w;
        r_src.h = tmp.h;

        // Update dstrect
        r_dst = tmp;
    }

    اگر (r_dst.w <= 0 || r_dst.h <= 0) {
        // No-op.
        بازگشت true;
    }

    // Switch back to a fast blit if we were previously stretching
    اگر (src->map.info.flags & SDL_COPY_NEAREST) {
        src->map.info.flags &= ~SDL_COPY_NEAREST;
        SDL_InvalidateMap(&src->map);
    }

    بازگشت SDL_BlitSurfaceUnchecked(src, &r_src, dst, &r_dst);
}

ایستا bool SDL_BlitSurfaceClippedScaled(SDL_Surface *src, ثابت SDL_Rect *srcrect, SDL_Surface *dst, ثابت SDL_Rect *dstrect, SDL_ScaleMode scaleMode)
{
    // We need to scale first, then blit into dst because we're clipping in the destination surface pixel coordinates
    bool result;
    صحیح saved_w = src->w;
    صحیح saved_h = src->h;
    تهی *saved_pixels = src->pixels;
    src->w = srcrect->w;
    src->h = srcrect->h;
    src->pixels = (Uint8 *)src->pixels + srcrect->y * src->pitch + srcrect->x * SDL_BYTESPERPIXEL(src->format);
    SDL_Surface *scaled = SDL_ScaleSurface(src, dstrect->w, dstrect->h, scaleMode);
    اگر (scaled) {
        result = SDL_BlitSurface(scaled, پوچ, dst, dstrect);
        SDL_DestroySurface(scaled);
    } وگرنه {
        result = false;
    }
    src->w = saved_w;
    src->h = saved_h;
    src->pixels = saved_pixels;
    بازگشت result;
}

bool SDL_BlitSurfaceScaled(SDL_Surface *src, ثابت SDL_Rect *srcrect, SDL_Surface *dst, ثابت SDL_Rect *dstrect, SDL_ScaleMode scaleMode)
{
    SDL_Rect r_src, r_dst;
    bool result;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src) || (!src->pixels && !SDL_MUSTLOCK(src))) {
        بازگشت SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst) || (!dst->pixels && !SDL_MUSTLOCK(dst))) {
        بازگشت SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        بازگشت SDL_SetError("Surfaces must not be locked during blit");
    }

    انتخاب (scaleMode) {
    حالت SDL_SCALEMODE_NEAREST:
        بشکن;
    حالت SDL_SCALEMODE_LINEAR:
        بشکن;
    حالت SDL_SCALEMODE_PIXELART:
        scaleMode = SDL_SCALEMODE_NEAREST;
        بشکن;
    پیشفرض:
        بازگشت SDL_InvalidParamError("scaleMode");
    }

    صحیح src_w = srcrect ? srcrect->w : src->w;
    صحیح src_h = srcrect ? srcrect->h : src->h;
    صحیح dst_w = dstrect ? dstrect->w : dst->w;
    صحیح dst_h = dstrect ? dstrect->h : dst->h;
    اگر (src_w == dst_w && src_h == dst_h) {
        // No scaling, defer to regular blit
        بازگشت SDL_BlitSurface(src, srcrect, dst, dstrect);
    }

    اگر (src->w == 0 || src->h == 0) {
        // Nothing to do
        بازگشت true;
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    اگر (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
        r_dst.w = dstrect->w;
        r_dst.h = dstrect->h;
    } وگرنه {
        r_dst.x = 0;
        r_dst.y = 0;
        r_dst.w = dst->w;
        r_dst.h = dst->h;
    }

    // clip the source rectangle to the source surface
    اگر (srcrect) {
        SDL_Rect desired, tmp;
        desired.x = srcrect->x;
        desired.y = srcrect->y;
        desired.w = SDL_max(srcrect->w, 1);
        desired.h = SDL_max(srcrect->h, 1);
        اگر (SDL_GetRectIntersection(&desired, &r_src, &tmp) == false) {
            بازگشت true;
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
    اگر (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &tmp) == false) {
        بازگشت true;
    }

    اگر (tmp.x != r_dst.x || tmp.y != r_dst.y || tmp.w != r_dst.w || tmp.h != r_dst.h) {
        // Need to do a clipped and scaled blit
        بازگشت SDL_BlitSurfaceClippedScaled(src, &r_src, dst, &r_dst, scaleMode);
    }

    اگر (SDL_MUSTLOCK(src)) {
        اگر (!SDL_LockSurface(src)) {
            بازگشت false;
        }
    }
    اگر (SDL_MUSTLOCK(dst)) {
        اگر (!SDL_LockSurface(dst)) {
            اگر (SDL_MUSTLOCK(src)) {
                SDL_UnlockSurface(src);
            }
            بازگشت false;
        }
    }

    result = SDL_BlitSurfaceUncheckedScaled(src, &r_src, dst, &r_dst, scaleMode);

    اگر (SDL_MUSTLOCK(src)) {
        SDL_UnlockSurface(src);
    }
    اگر (SDL_MUSTLOCK(dst)) {
        SDL_UnlockSurface(dst);
    }
    بازگشت result;
}

/**
 *  This is a semi-private blit function and it performs low-level surface
 *  scaled blitting only.
 */
bool SDL_BlitSurfaceUncheckedScaled(SDL_Surface *src, ثابت SDL_Rect *srcrect, SDL_Surface *dst, ثابت SDL_Rect *dstrect, SDL_ScaleMode scaleMode)
{
    ایستا ثابت Uint32 complex_copy_flags = (SDL_COPY_MODULATE_MASK | SDL_COPY_BLEND_MASK | SDL_COPY_COLORKEY);

    اگر (srcrect->w > SDL_MAX_UINT16 || srcrect->h > SDL_MAX_UINT16 ||
        dstrect->w > SDL_MAX_UINT16 || dstrect->h > SDL_MAX_UINT16) {
        بازگشت SDL_SetError("Size too large for scaling");
    }

    اگر (!(src->map.info.flags & SDL_COPY_NEAREST)) {
        src->map.info.flags |= SDL_COPY_NEAREST;
        SDL_InvalidateMap(&src->map);
    }

    اگر (scaleMode == SDL_SCALEMODE_NEAREST || scaleMode == SDL_SCALEMODE_PIXELART) {
        اگر (!(src->map.info.flags & complex_copy_flags) &&
            src->format == dst->format &&
            (!SDL_ISPIXELFORMAT_INDEXED(src->format) ||
             (SDL_BITSPERPIXEL(src->format) == 8 && SDL_IsSamePalette(src->palette, dst->palette))) &&
            SDL_BYTESPERPIXEL(src->format) <= 4) {
            بازگشت SDL_StretchSurface(src, srcrect, dst, dstrect, SDL_SCALEMODE_NEAREST);
        } وگرنه اگر (SDL_BITSPERPIXEL(src->format) < 8) {
            // Scaling bitmap not yet supported, convert to RGBA for blit
            bool result = false;
            SDL_Surface *tmp = SDL_ConvertSurface(src, SDL_PIXELFORMAT_ARGB8888);
            اگر (tmp) {
                result = SDL_BlitSurfaceUncheckedScaled(tmp, srcrect, dst, dstrect, SDL_SCALEMODE_NEAREST);
                SDL_DestroySurface(tmp);
            }
            بازگشت result;
        } وگرنه {
            بازگشت SDL_BlitSurfaceUnchecked(src, srcrect, dst, dstrect);
        }
    } وگرنه {
        اگر (!(src->map.info.flags & complex_copy_flags) &&
            src->format == dst->format &&
            !SDL_ISPIXELFORMAT_INDEXED(src->format) &&
            SDL_BYTESPERPIXEL(src->format) == 4 &&
            src->format != SDL_PIXELFORMAT_ARGB2101010) {
            // fast path
            بازگشت SDL_StretchSurface(src, srcrect, dst, dstrect, SDL_SCALEMODE_LINEAR);
        } وگرنه اگر (SDL_BITSPERPIXEL(src->format) < 8) {
            // Scaling bitmap not yet supported, convert to RGBA for blit
            bool result = false;
            SDL_Surface *tmp = SDL_ConvertSurface(src, SDL_PIXELFORMAT_ARGB8888);
            اگر (tmp) {
                result = SDL_BlitSurfaceUncheckedScaled(tmp, srcrect, dst, dstrect, scaleMode);
                SDL_DestroySurface(tmp);
            }
            بازگشت result;
        } وگرنه {
            // Use intermediate surface(s)
            SDL_Surface *tmp1 = پوچ;
            bool result;
            SDL_Rect srcrect2;
            صحیح is_complex_copy_flags = (src->map.info.flags & complex_copy_flags);

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
            اگر (SDL_BYTESPERPIXEL(src->format) != 4 || src->format == SDL_PIXELFORMAT_ARGB2101010) {
                SDL_PixelFormat fmt;
                اگر (SDL_BYTESPERPIXEL(dst->format) == 4 && dst->format != SDL_PIXELFORMAT_ARGB2101010 &&
                    (SDL_ISPIXELFORMAT_ALPHA(dst->format) || !is_complex_copy_flags)) {
                    fmt = dst->format;
                } وگرنه {
                    fmt = SDL_PIXELFORMAT_ARGB8888;
                }
                tmp1 = SDL_ConvertSurfaceRect(src, srcrect, fmt);
                اگر (!tmp1) {
                    بازگشت false;
                }
                src = tmp1;
                srcrect2.x = 0;
                srcrect2.y = 0;
            }

            // Intermediate scaling
            اگر (is_complex_copy_flags || src->format != dst->format) {
                SDL_Rect tmprect;
                SDL_Surface *tmp2 = SDL_CreateSurfaceUninitialized(dstrect->w, dstrect->h, src->format);
                SDL_StretchSurface(src, &srcrect2, tmp2, پوچ, SDL_SCALEMODE_LINEAR);

                SDL_SetSurfaceColorMod(tmp2, r, g, b);
                SDL_SetSurfaceAlphaMod(tmp2, alpha);
                SDL_SetSurfaceBlendMode(tmp2, blendMode);

                tmprect.x = 0;
                tmprect.y = 0;
                tmprect.w = dstrect->w;
                tmprect.h = dstrect->h;
                result = SDL_BlitSurfaceUnchecked(tmp2, &tmprect, dst, dstrect);
                SDL_DestroySurface(tmp2);
            } وگرنه {
                result = SDL_StretchSurface(src, &srcrect2, dst, dstrect, SDL_SCALEMODE_LINEAR);
            }

            SDL_DestroySurface(tmp1);
            بازگشت result;
        }
    }
}

bool SDL_BlitSurfaceTiled(SDL_Surface *src, ثابت SDL_Rect *srcrect, SDL_Surface *dst, ثابت SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        بازگشت SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        بازگشت SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        بازگشت SDL_SetError("Surfaces must not be locked during blit");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    اگر (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
        r_dst.w = dstrect->w;
        r_dst.h = dstrect->h;
    } وگرنه {
        r_dst.x = 0;
        r_dst.y = 0;
        r_dst.w = dst->w;
        r_dst.h = dst->h;
    }

    // clip the source rectangle to the source surface
    اگر (srcrect) {
        اگر (SDL_GetRectIntersection(srcrect, &r_src, &r_src) == false) {
            بازگشت true;
        }

        // For tiling we don't adjust the destination rectangle
    }

    // clip the destination rectangle against the clip rectangle
    {
        اگر (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &r_dst) == false) {
            بازگشت true;
        }

        // For tiling we don't adjust the source rectangle
    }

    // Switch back to a fast blit if we were previously stretching
    اگر (src->map.info.flags & SDL_COPY_NEAREST) {
        src->map.info.flags &= ~SDL_COPY_NEAREST;
        SDL_InvalidateMap(&src->map);
    }

    صحیح rows = r_dst.h / r_src.h;
    صحیح cols = r_dst.w / r_src.w;
    صحیح remaining_w = r_dst.w % r_src.w;
    صحیح remaining_h = r_dst.h % r_src.h;
    SDL_Rect curr_src, curr_dst;

    SDL_copyp(&curr_src, &r_src);
    curr_dst.y = r_dst.y;
    curr_dst.w = r_src.w;
    curr_dst.h = r_src.h;
    برای (صحیح y = 0; y < rows; ++y) {
        curr_dst.x = r_dst.x;
        برای (صحیح x = 0; x < cols; ++x) {
            اگر (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                بازگشت false;
            }
            curr_dst.x += curr_dst.w;
        }
        اگر (remaining_w) {
            curr_src.w = remaining_w;
            curr_dst.w = remaining_w;
            اگر (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                بازگشت false;
            }
            curr_src.w = r_src.w;
            curr_dst.w = r_src.w;
        }
        curr_dst.y += curr_dst.h;
    }
    اگر (remaining_h) {
        curr_src.h = remaining_h;
        curr_dst.h = remaining_h;
        curr_dst.x = r_dst.x;
        برای (صحیح x = 0; x < cols; ++x) {
            اگر (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                بازگشت false;
            }
            curr_dst.x += curr_dst.w;
        }
        اگر (remaining_w) {
            curr_src.w = remaining_w;
            curr_dst.w = remaining_w;
            اگر (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                بازگشت false;
            }
        }
    }
    بازگشت true;
}

bool SDL_BlitSurfaceTiledWithScale(SDL_Surface *src, ثابت SDL_Rect *srcrect, اعشاری scale, SDL_ScaleMode scaleMode, SDL_Surface *dst, ثابت SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        بازگشت SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        بازگشت SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        بازگشت SDL_SetError("Surfaces must not be locked during blit");
    }
    CHECK_PARAM(scale < 0.0f) {
        بازگشت SDL_InvalidParamError("scale");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    اگر (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
        r_dst.w = dstrect->w;
        r_dst.h = dstrect->h;
    } وگرنه {
        r_dst.x = 0;
        r_dst.y = 0;
        r_dst.w = dst->w;
        r_dst.h = dst->h;
    }

    // clip the source rectangle to the source surface
    اگر (srcrect) {
        اگر (SDL_GetRectIntersection(srcrect, &r_src, &r_src) == false) {
            بازگشت true;
        }

        // For tiling we don't adjust the destination rectangle
    }

    // clip the destination rectangle against the clip rectangle
    {
        اگر (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &r_dst) == false) {
            بازگشت true;
        }

        // For tiling we don't adjust the source rectangle
    }

    // Switch back to a fast blit if we were previously stretching
    اگر (src->map.info.flags & SDL_COPY_NEAREST) {
        src->map.info.flags &= ~SDL_COPY_NEAREST;
        SDL_InvalidateMap(&src->map);
    }

    صحیح tile_width = (صحیح)SDL_roundf(r_src.w * scale);
    صحیح tile_height = (صحیح)SDL_roundf(r_src.h * scale);
    اگر (tile_width <= 0 || tile_height <= 0) {
        // Nothing to do
        بازگشت true;
    }
    صحیح rows = r_dst.h / tile_height;
    صحیح cols = r_dst.w / tile_width;
    صحیح remaining_dst_w = (r_dst.w - cols * tile_width);
    صحیح remaining_dst_h = (r_dst.h - rows * tile_height);
    صحیح remaining_src_w = (صحیح)(remaining_dst_w / scale);
    صحیح remaining_src_h = (صحیح)(remaining_dst_h / scale);
    SDL_Rect curr_src, curr_dst;

    SDL_copyp(&curr_src, &r_src);
    curr_dst.y = r_dst.y;
    curr_dst.w = tile_width;
    curr_dst.h = tile_height;
    برای (صحیح y = 0; y < rows; ++y) {
        curr_dst.x = r_dst.x;
        برای (صحیح x = 0; x < cols; ++x) {
            اگر (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
                بازگشت false;
            }
            curr_dst.x += curr_dst.w;
        }
        اگر (remaining_dst_w > 0) {
            curr_src.w = remaining_src_w;
            curr_dst.w = remaining_dst_w;
            اگر (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
                بازگشت false;
            }
            curr_src.w = r_src.w;
            curr_dst.w = tile_width;
        }
        curr_dst.y += curr_dst.h;
    }
    اگر (remaining_dst_h > 0) {
        curr_src.h = remaining_src_h;
        curr_dst.h = remaining_dst_h;
        curr_dst.x = r_dst.x;
        برای (صحیح x = 0; x < cols; ++x) {
            اگر (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
                بازگشت false;
            }
            curr_dst.x += curr_dst.w;
        }
        اگر (remaining_dst_w > 0) {
            curr_src.w = remaining_src_w;
            curr_dst.w = remaining_dst_w;
            اگر (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
                بازگشت false;
            }
        }
    }
    بازگشت true;
}

bool SDL_BlitSurface9Grid(SDL_Surface *src, ثابت SDL_Rect *srcrect, صحیح چپ_width, صحیح راست_width, صحیح بالاترین_height, صحیح bottom_height, اعشاری scale, SDL_ScaleMode scaleMode, SDL_Surface *dst, ثابت SDL_Rect *dstrect)
{
    SDL_Rect full_src, full_dst;
    SDL_Rect curr_src, curr_dst;
    صحیح dst_چپ_width;
    صحیح dst_راست_width;
    صحیح dst_بالاترین_height;
    صحیح dst_bottom_height;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        بازگشت SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        بازگشت SDL_InvalidParamError("dst");
    }

    اگر (!srcrect) {
        full_src.x = 0;
        full_src.y = 0;
        full_src.w = src->w;
        full_src.h = src->h;
        srcrect = &full_src;
    }

    اگر (!dstrect) {
        full_dst.x = 0;
        full_dst.y = 0;
        full_dst.w = dst->w;
        full_dst.h = dst->h;
        dstrect = &full_dst;
    }

    اگر (scale <= 0.0f || scale == 1.0f) {
        dst_چپ_width = چپ_width;
        dst_راست_width = راست_width;
        dst_بالاترین_height = بالاترین_height;
        dst_bottom_height = bottom_height;
    } وگرنه {
        dst_چپ_width = (صحیح)SDL_roundf(چپ_width * scale);
        dst_راست_width = (صحیح)SDL_roundf(راست_width * scale);
        dst_بالاترین_height = (صحیح)SDL_roundf(بالاترین_height * scale);
        dst_bottom_height = (صحیح)SDL_roundf(bottom_height * scale);
    }

    // Upper-left corner
    curr_src.x = srcrect->x;
    curr_src.y = srcrect->y;
    curr_src.w = چپ_width;
    curr_src.h = بالاترین_height;
    curr_dst.x = dstrect->x;
    curr_dst.y = dstrect->y;
    curr_dst.w = dst_چپ_width;
    curr_dst.h = dst_بالاترین_height;
    اگر (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        بازگشت false;
    }

    // Upper-right corner
    curr_src.x = srcrect->x + srcrect->w - راست_width;
    curr_src.w = راست_width;
    curr_dst.x = dstrect->x + dstrect->w - dst_راست_width;
    curr_dst.w = dst_راست_width;
    اگر (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        بازگشت false;
    }

    // Lower-right corner
    curr_src.y = srcrect->y + srcrect->h - bottom_height;
    curr_dst.y = dstrect->y + dstrect->h - dst_bottom_height;
    curr_dst.h = dst_bottom_height;
    اگر (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        بازگشت false;
    }

    // Lower-left corner
    curr_src.x = srcrect->x;
    curr_src.w = چپ_width;
    curr_dst.x = dstrect->x;
    curr_dst.w = dst_چپ_width;
    اگر (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        بازگشت false;
    }

    //چپ
    curr_src.y = srcrect->y + بالاترین_height;
    curr_src.h = srcrect->h - بالاترین_height - bottom_height;
    curr_dst.y = dstrect->y + dst_بالاترین_height;
    curr_dst.h = dstrect->h - dst_بالاترین_height - dst_bottom_height;
    اگر (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        بازگشت false;
    }

    //راست
    curr_src.x = srcrect->x + srcrect->w - راست_width;
    curr_src.w = راست_width;
    curr_dst.x = dstrect->x + dstrect->w - dst_راست_width;
    curr_dst.w = dst_راست_width;
    اگر (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        بازگشت false;
    }

    //بالاترین
    curr_src.x = srcrect->x + چپ_width;
    curr_src.y = srcrect->y;
    curr_src.w = srcrect->w - چپ_width - راست_width;
    curr_src.h = بالاترین_height;
    curr_dst.x = dstrect->x + dst_چپ_width;
    curr_dst.y = dstrect->y;
    curr_dst.w = dstrect->w - dst_چپ_width - dst_راست_width;
    curr_dst.h = dst_بالاترین_height;
    اگر (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        بازگشت false;
    }

    // Bottom
    curr_src.y = srcrect->y + srcrect->h - bottom_height;
    curr_dst.y = dstrect->y + dstrect->h - dst_bottom_height;
    curr_dst.h = dst_bottom_height;
    اگر (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        بازگشت false;
    }

    // Center
    curr_src.x = srcrect->x + چپ_width;
    curr_src.y = srcrect->y + بالاترین_height;
    curr_src.w = srcrect->w - چپ_width - راست_width;
    curr_src.h = srcrect->h - بالاترین_height - bottom_height;
    curr_dst.x = dstrect->x + dst_چپ_width;
    curr_dst.y = dstrect->y + dst_بالاترین_height;
    curr_dst.w = dstrect->w - dst_چپ_width - dst_راست_width;
    curr_dst.h = dstrect->h - dst_بالاترین_height - dst_bottom_height;
    اگر (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        بازگشت false;
    }

    بازگشت true;
}

/*
 * Lock a surface to directly access the pixels
 */
bool SDL_LockSurface(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        بازگشت SDL_InvalidParamError("surface");
    }

    اگر (!surface->locked) {
#ifdef SDL_HAVE_RLE
        // Perform the lock
        اگر (surface->internal_flags & SDL_INTERNAL_SURFACE_RLEACCEL) {
            SDL_UnRLESurface(surface);
        }
#endif
    }

    // Increment the surface lock count, for recursive locks
    ++surface->locked;
    surface->flags |= SDL_SURFACE_LOCKED;
    SDL_UpdateSurfaceLockFlag(surface);

    // Ready to go..
    بازگشت true;
}

/*
 * Unlock a previously locked surface
 */
تهی SDL_UnlockSurface(SDL_Surface *surface)
{
    اگر (!SDL_SurfaceValid(surface)) {
        بازگشت;
    }

    // Only perform an unlock if we are locked
    اگر (!surface->locked || (--surface->locked > 0)) {
        بازگشت;
    }

    surface->flags &= ~SDL_SURFACE_LOCKED;
    SDL_UpdateSurfaceLockFlag(surface);
}

ایستا bool SDL_FlipSurfaceHorizontal(SDL_Surface *surface)
{
    bool isstack;
    Uint8 *row, *a, *b, *tmp;
    صحیح i, j, bpp;

    اگر (SDL_BITSPERPIXEL(surface->format) < 8) {
        // We could implement this if needed, but we'd have to flip sets of bits within a byte
        بازگشت SDL_Unsupported();
    }

    اگر (surface->h <= 0) {
        بازگشت true;
    }

    اگر (surface->w <= 1) {
        بازگشت true;
    }

    bpp = SDL_BYTESPERPIXEL(surface->format);
    row = (Uint8 *)surface->pixels;
    tmp = SDL_small_alloc(Uint8, surface->pitch, &isstack);
    اگر (!tmp) {
        بازگشت false;
    }
    برای (i = surface->h; i--; ) {
        a = row;
        b = a + (surface->w - 1) * bpp;
        برای (j = surface->w / 2; j--; ) {
            SDL_memcpy(tmp, a, bpp);
            SDL_memcpy(a, b, bpp);
            SDL_memcpy(b, tmp, bpp);
            a += bpp;
            b -= bpp;
        }
        row += surface->pitch;
    }
    SDL_small_free(tmp, isstack);
    بازگشت true;
}

ایستا bool SDL_FlipSurfaceVertical(SDL_Surface *surface)
{
    bool isstack;
    Uint8 *a, *b, *tmp;
    صحیح i;

    اگر (surface->h <= 1) {
        بازگشت true;
    }

    a = (Uint8 *)surface->pixels;
    b = a + (surface->h - 1) * surface->pitch;
    tmp = SDL_small_alloc(Uint8, surface->pitch, &isstack);
    اگر (!tmp) {
        بازگشت false;
    }
    برای (i = surface->h / 2; i--; ) {
        SDL_memcpy(tmp, a, surface->pitch);
        SDL_memcpy(a, b, surface->pitch);
        SDL_memcpy(b, tmp, surface->pitch);
        a += surface->pitch;
        b -= surface->pitch;
    }
    SDL_small_free(tmp, isstack);
    بازگشت true;
}

bool SDL_FlipSurface(SDL_Surface *surface, SDL_FlipMode flip)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        بازگشت SDL_InvalidParamError("surface");
    }
    اگر (!surface->pixels) {
        بازگشت true;
    }

    bool result = true;
    انتخاب (flip) {
    حالت SDL_FLIP_HORIZONTAL:
        result = SDL_FlipSurfaceHorizontal(surface);
        بشکن;
    حالت SDL_FLIP_VERTICAL:
        result = SDL_FlipSurfaceVertical(surface);
        بشکن;
    حالت SDL_FLIP_HORIZONTAL_AND_VERTICAL:
        result &= SDL_FlipSurfaceHorizontal(surface);
        result &= SDL_FlipSurfaceVertical(surface);
        بشکن;
    پیشفرض:
        result = SDL_InvalidParamError("flip");
        بشکن;
    }
    بازگشت result;
}

ایستا SDL_Surface *SDL_ConvertSurfaceRectAndColorspace(SDL_Surface *surface, ثابت SDL_Rect *rect, SDL_PixelFormat format, SDL_Palette *palette, SDL_Colorspace colorspace, SDL_PropertiesID props)
{
    SDL_Palette *temp_palette = پوچ;
    SDL_Surface *convert = پوچ;
    SDL_Colorspace src_colorspace;
    SDL_PropertiesID src_properties;
    Uint32 copy_flags;
    SDL_Color copy_color;
    SDL_Rect bounds;
    bool result;
    bool palette_ck_transform = false;
    Uint8 palette_ck_مقدار = 0;
    Uint8 *palette_saved_alpha = پوچ;
    صحیح palette_saved_alpha_ncolors = 0;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        برو error;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        برو error;
    }

    // Set the bounds of the new surface
    bounds.x = 0;
    bounds.y = 0;
    bounds.w = surface->w;
    bounds.h = surface->h;
    اگر (rect) {
        bounds.w = rect->w;
        bounds.h = rect->h;
    } وگرنه {
        rect = &bounds;
    }

    // Check for empty destination palette! (results in empty image)
    اگر (palette) {
        صحیح i;
        برای (i = 0; i < palette->ncolors; ++i) {
            اگر ((palette->colors[i].r != 0xFF) || (palette->colors[i].g != 0xFF) || (palette->colors[i].b != 0xFF)) {
                بشکن;
            }
        }
        اگر (i == palette->ncolors) {
            SDL_SetError("Empty destination palette");
            برو error;
        }
    } وگرنه اگر (SDL_ISPIXELFORMAT_INDEXED(format)) {
        // Create a dither palette for conversion
        temp_palette = SDL_CreatePalette(1 << SDL_BITSPERPIXEL(format));
        اگر (temp_palette) {
            SDL_DitherPalette(temp_palette);
            palette = temp_palette;
        }
    }

    src_colorspace = surface->colorspace;
    src_properties = surface->props;

    // Create a new surface with the desired format
    اگر (surface->pixels || SDL_MUSTLOCK(surface)) {
        convert = SDL_CreateSurfaceUninitialized(rect->w, rect->h, format);
    } وگرنه {
        convert = SDL_CreateSurfaceFrom(rect->w, rect->h, format, پوچ, 0);
    }
    اگر (!convert) {
        برو error;
    }
    اگر (SDL_ISPIXELFORMAT_INDEXED(format)) {
        SDL_SetSurfacePalette(convert, palette);
    }

    اگر (colorspace == SDL_COLORSPACE_UNKNOWN) {
        colorspace = src_colorspace;
    }
    SDL_SetSurfaceColorspace(convert, colorspace);

    اگر (SDL_ISPIXELFORMAT_FOURCC(format) || SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        اگر (surface->format == SDL_PIXELFORMAT_MJPG && format == SDL_PIXELFORMAT_MJPG) {
            // Just do a straight pixel copy of the JPEG image
            size_t size = (size_t)surface->pitch;
            convert->pixels = SDL_malloc(size);
            اگر (!convert->pixels) {
                برو error;
            }
            convert->flags &= ~SDL_SURFACE_PREALLOCATED;
            convert->pitch = surface->pitch;
            SDL_memcpy(convert->pixels, surface->pixels, size);

        } وگرنه اگر (!SDL_ConvertPixelsAndColorspace(surface->w, surface->h, surface->format, src_colorspace, src_properties, surface->pixels, surface->pitch, convert->format, colorspace, props, convert->pixels, convert->pitch)) {
            برو error;
        }

        // Save the original copy flags
        copy_flags = surface->map.info.flags;

        برو end;
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
    اگر (surface->palette && SDL_ISPIXELFORMAT_ALPHA(format)) {
        bool set_opaque = false;

        bool is_opaque, has_alpha_channel;
        SDL_DetectPalette(surface->palette, &is_opaque, &has_alpha_channel);

        اگر (is_opaque) {
            اگر (!has_alpha_channel) {
                set_opaque = true;
            }
        }

        // Set opaque and backup palette alpha values
        اگر (set_opaque) {
            صحیح i;
            palette_saved_alpha_ncolors = surface->palette->ncolors;
            اگر (palette_saved_alpha_ncolors > 0) {
                palette_saved_alpha = SDL_پشته_alloc(Uint8, palette_saved_alpha_ncolors);
                برای (i = 0; i < palette_saved_alpha_ncolors; i++) {
                    palette_saved_alpha[i] = surface->palette->colors[i].a;
                    surface->palette->colors[i].a = SDL_ALPHA_OPAQUE;
                }
            }
        }
    }

    // Transform colorkey to alpha. for cases where source palette has duplicate values, and colorkey is one of them
    اگر (copy_flags & SDL_COPY_COLORKEY) {
        اگر (surface->palette && !palette) {
            palette_ck_transform = true;
            palette_ck_مقدار = surface->palette->colors[surface->map.info.colorkey].a;
            surface->palette->colors[surface->map.info.colorkey].a = SDL_ALPHA_TRANSPARENT;
        }
    }

    اگر (surface->pixels || SDL_MUSTLOCK(surface)) {
        result = SDL_BlitSurfaceUnchecked(surface, rect, convert, &bounds);
    } وگرنه {
        result = true;
    }

    // Restore colorkey alpha value
    اگر (palette_ck_transform) {
        surface->palette->colors[surface->map.info.colorkey].a = palette_ck_مقدار;
    }

    // Restore palette alpha values
    اگر (palette_saved_alpha) {
        صحیح i;
        برای (i = 0; i < palette_saved_alpha_ncolors; i++) {
            surface->palette->colors[i].a = palette_saved_alpha[i];
        }
        SDL_پشته_free(palette_saved_alpha);
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
    اگر (!result) {
        برو error;
    }

    اگر (copy_flags & SDL_COPY_COLORKEY) {
        bool set_colorkey_by_color = false;
        bool convert_colorkey = true;

        اگر (surface->palette) {
            اگر (palette &&
                surface->palette->ncolors <= palette->ncolors &&
                (SDL_memcmp(surface->palette->colors, palette->colors,
                            surface->palette->ncolors * اندازه(SDL_Color)) == 0)) {
                // The palette is identical, just set the same colorkey
                SDL_Set_Surface_Color_کلید(convert, true, surface->map.info.colorkey);
            } وگرنه اگر (!palette) {
                اگر (SDL_ISPIXELFORMAT_ALPHA(format)) {
                    // No need to add the colorkey, transparency is in the alpha channel
                } وگرنه {
                    // Only set the colorkey information
                    set_colorkey_by_color = true;
                    convert_colorkey = false;
                }
            } وگرنه {
                set_colorkey_by_color = true;
            }
        } وگرنه {
            set_colorkey_by_color = true;
        }

        اگر (set_colorkey_by_color) {
            SDL_Surface *tmp;
            SDL_Surface *tmp2;
            صحیح converted_colorkey = 0;

            // Create a dummy surface to get the colorkey converted
            tmp = SDL_CreateSurfaceUninitialized(1, 1, surface->format);
            اگر (!tmp) {
                برو error;
            }

            // Share the palette, if any
            اگر (surface->palette) {
                SDL_SetSurfacePalette(tmp, surface->palette);
            }

            SDL_FillSurfaceRect(tmp, پوچ, surface->map.info.colorkey);

            tmp->map.info.flags &= ~SDL_COPY_COLORKEY;

            // Conversion of the colorkey
            tmp2 = SDL_ConvertSurfaceAndColorspace(tmp, format, palette, colorspace, props);
            اگر (!tmp2) {
                SDL_DestroySurface(tmp);
                برو error;
            }

            // Get the converted colorkey
            SDL_memcpy(&converted_colorkey, tmp2->pixels, tmp2->fmt->bytes_per_pixel);

            SDL_DestroySurface(tmp);
            SDL_DestroySurface(tmp2);

            // Set the converted colorkey on the new surface
            SDL_Set_Surface_Color_کلید(convert, true, converted_colorkey);

            // This is needed when converting for 3D texture upload
            اگر (convert_colorkey) {
                SDL_ConvertColorkeyToAlpha(convert, true);
            }
        }
    }

end:
    اگر (temp_palette) {
        SDL_DestroyPalette(temp_palette);
    }

    SDL_SetSurfaceClipRect(convert, &surface->clip_rect);

    /* Enable alpha blending by default if the new surface has an
     * alpha channel or alpha modulation */
    اگر (SDL_ISPIXELFORMAT_ALPHA(format) ||
        (copy_flags & SDL_COPY_MODULATE_ALPHA)) {
        SDL_SetSurfaceBlendMode(convert, SDL_BLENDMODE_BLEND);
    }
    اگر (copy_flags & SDL_COPY_RLE_DESIRED) {
        SDL_SetSurfaceRLE(convert, true);
    }

    // Copy alternate images
    برای (صحیح i = 0; i < surface->رقم_images; ++i) {
        اگر (!SDL_AddSurfaceAlternateImage(convert, surface->images[i])) {
            برو error;
        }
    }

    // Copy properties
    اگر (surface->props) {
        اگر (!SDL_CopyProperties(surface->props, SDL_GetSurfaceProperties(convert))) {
            برو error;
        }

        // Make sure the new surface doesn't reference an old SDL2 surface.
        SDL_ClearProperty(SDL_GetSurfaceProperties(convert), "sdl2-compat.surface2");
    }

    // We're ready to go!
    بازگشت convert;

error:
    اگر (temp_palette) {
        SDL_DestroyPalette(temp_palette);
    }
    اگر (convert) {
        SDL_DestroySurface(convert);
    }
    بازگشت پوچ;
}

SDL_Surface *SDL_ConvertSurfaceAndColorspace(SDL_Surface *surface, SDL_PixelFormat format, SDL_Palette *palette, SDL_Colorspace colorspace, SDL_PropertiesID props)
{
    بازگشت SDL_ConvertSurfaceRectAndColorspace(surface, پوچ, format, palette, colorspace, props);
}

SDL_Surface *SDL_RotateSurface(SDL_Surface *surface, اعشاری angle)
{
    SDL_Surface *rotated = پوچ;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        بازگشت پوچ;
    }

    SDL_Rect rect_dest;
    دوگانه cangle, sangle;
    SDL_FPoint center = { surface->w * 0.5f, surface->h * 0.5f };
    SDLgfx_rotozoomSurfaceSizeTrig(surface->w, surface->h, angle, &center, &rect_dest, &cangle, &sangle);

    // This function requires a 32-bit surface or 8-bit surface with a colorkey
    اگر ((SDL_BITSPERPIXEL(surface->format) == 32 && SDL_PIXELLAYOUT(surface->format) == SDL_PACKEDLAYOUT_8888) ||
        (surface->format == SDL_PIXELFORMAT_INDEX8 && SDL_Surface_Has_Color_کلید(surface))) {
        rotated = SDLgfx_rotateSurface(surface, angle, 1, 0, 0, &rect_dest, cangle, sangle, &center);
    } وگرنه {
        SDL_Surface *convert = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);
        اگر (convert) {
            SDL_Surface *tmp = SDLgfx_rotateSurface(convert, angle, 1, 0, 0, &rect_dest, cangle, sangle, &center);
            اگر (tmp) {
                rotated = SDL_ConvertSurfaceAndColorspace(tmp, surface->format, surface->palette, surface->colorspace, surface->props);
                SDL_DestroySurface(tmp);
            }
            SDL_DestroySurface(convert);
        }
    }

    اگر (rotated) {
        اگر (SDL_HasProperty(surface->props, SDL_PROP_SURFACE_ROTATION_FLOAT)) {
            ثابت اعشاری rotation = (SDL_Get_عدد_Property(surface->props, SDL_PROP_SURFACE_ROTATION_FLOAT, 0) - angle);
            SDL_SetFloatProperty(SDL_GetSurfaceProperties(rotated), SDL_PROP_SURFACE_ROTATION_FLOAT, rotation);
        }
    }

    بازگشت rotated;
}

SDL_Surface *SDL_DuplicateSurface(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        بازگشت پوچ;
    }

    بازگشت SDL_ConvertSurfaceAndColorspace(surface, surface->format, surface->palette, surface->colorspace, surface->props);
}

SDL_Surface *SDL_ScaleSurface(SDL_Surface *surface, صحیح width, صحیح height, SDL_ScaleMode scaleMode)
{
    SDL_Surface *convert = پوچ;
    Uint32 copy_flags;
    SDL_Color copy_color;
    bool rc;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        برو error;
    }

    اگر (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // We can't directly scale a YUV surface (yet!)
        SDL_Surface *tmp = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        اگر (!tmp) {
            بازگشت پوچ;
        }

        SDL_Surface *scaled = SDL_ScaleSurface(tmp, width, height, scaleMode);
        SDL_DestroySurface(tmp);
        اگر (!scaled) {
            بازگشت پوچ;
        }

        SDL_Surface *result = SDL_ConvertSurfaceAndColorspace(scaled, surface->format, پوچ, surface->colorspace, surface->props);
        SDL_DestroySurface(scaled);
        بازگشت result;
    }

    اگر (SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        // Linear scaling requires conversion to RGBA and then slow pixel color lookup
        scaleMode = SDL_SCALEMODE_NEAREST;
    }

    // Create a new surface with the desired size
    اگر (surface->pixels || SDL_MUSTLOCK(surface)) {
        convert = SDL_CreateSurfaceUninitialized(width, height, surface->format);
    } وگرنه {
        convert = SDL_CreateSurfaceFrom(width, height, surface->format, پوچ, 0);
    }
    اگر (!convert) {
        برو error;
    }
    SDL_SetSurfacePalette(convert, surface->palette);
    SDL_SetSurfaceColorspace(convert, surface->colorspace);
    SDL_SetSurfaceRLE(convert, SDL_SurfaceHasRLE(surface));

    اگر (surface->pixels || SDL_MUSTLOCK(surface)) {
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

        rc = SDL_BlitSurfaceScaled(surface, پوچ, convert, پوچ, scaleMode);

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
    } وگرنه {
        rc = true;
    }

    // SDL_BlitSurfaceScaled failed, and so the conversion
    اگر (!rc) {
        برو error;
    }

    // We're ready to go!
    بازگشت convert;

error:
    اگر (convert) {
        SDL_DestroySurface(convert);
    }
    بازگشت پوچ;
}

SDL_Surface *SDL_ConvertSurfaceRect(SDL_Surface *surface, ثابت SDL_Rect *rect, SDL_PixelFormat format)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        بازگشت پوچ;
    }

    بازگشت SDL_ConvertSurfaceRectAndColorspace(surface, rect, format, پوچ, SDL_GetDefaultColorspaceForFormat(format), surface->props);
}

SDL_Surface *SDL_ConvertSurface(SDL_Surface *surface, SDL_PixelFormat format)
{
    بازگشت SDL_ConvertSurfaceRect(surface, پوچ, format);
}

SDL_Surface *SDL_DuplicatePixels(صحیح width, صحیح height, SDL_PixelFormat format, SDL_Colorspace colorspace, تهی *pixels, صحیح pitch)
{
    SDL_Surface *surface;
    اگر (pixels) {
        surface = SDL_CreateSurfaceUninitialized(width, height, format);
    } وگرنه {
        surface = SDL_CreateSurfaceFrom(width, height, format, پوچ, 0);
    }
    اگر (!surface) {
        بازگشت پوچ;
    }
    SDL_SetSurfaceColorspace(surface, colorspace);

    اگر (surface->pixels) {
        صحیح length = width * SDL_BYTESPERPIXEL(format);
        Uint8 *src = (Uint8 *)pixels;
        Uint8 *dst = (Uint8 *)surface->pixels;
        صحیح rows = height;
        وقتی (rows--) {
            SDL_memcpy(dst, src, length);
            dst += surface->pitch;
            src += pitch;
        }
    }
    بازگشت surface;
}

bool SDL_ConvertPixelsAndColorspace(صحیح width, صحیح height,
                      SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ثابت تهی *src, صحیح src_pitch,
                      SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, تهی *dst, صحیح dst_pitch)
{
    SDL_Surface src_surface;
    SDL_Surface dst_surface;
    SDL_Rect rect;
    تهی *nonconst_src = (تهی *)src;
    bool result;

    CHECK_PARAM(!src) {
        بازگشت SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!src_pitch) {
        بازگشت SDL_InvalidParamError("src_pitch");
    }
    CHECK_PARAM(!dst) {
        بازگشت SDL_InvalidParamError("dst");
    }
    CHECK_PARAM(!dst_pitch) {
        بازگشت SDL_InvalidParamError("dst_pitch");
    }

    اگر (src_colorspace == SDL_COLORSPACE_UNKNOWN) {
        src_colorspace = SDL_GetDefaultColorspaceForFormat(src_format);
    }
    اگر (dst_colorspace == SDL_COLORSPACE_UNKNOWN) {
        dst_colorspace = SDL_GetDefaultColorspaceForFormat(dst_format);
    }

    اگر (src_format == SDL_PIXELFORMAT_MJPG) {
        بازگشت SDL_ConvertPixels_STB(width, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    }

#ifdef SDL_HAVE_YUV
    اگر (SDL_ISPIXELFORMAT_FOURCC(src_format) && SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        بازگشت SDL_ConvertPixels_YUV_to_YUV(width, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } وگرنه اگر (SDL_ISPIXELFORMAT_FOURCC(src_format)) {
        بازگشت SDL_ConvertPixels_YUV_to_RGB(width, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } وگرنه اگر (SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        بازگشت SDL_ConvertPixels_RGB_to_YUV(width, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    }
#وگرنه
    اگر (SDL_ISPIXELFORMAT_FOURCC(src_format) || SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        بازگشت SDL_SetError("SDL not built with YUV support");
    }
#endif

    // Fast path for same format copy
    اگر (src_format == dst_format && src_colorspace == dst_colorspace) {
        اگر (src_pitch == dst_pitch) {
            SDL_memcpy(dst, src, height * src_pitch);
        } وگرنه {
            صحیح i;
            ثابت صحیح bpp = SDL_BYTESPERPIXEL(src_format);
            width *= bpp;
            برای (i = height; i--;) {
                SDL_memcpy(dst, src, width);
                src = (ثابت Uint8 *)src + src_pitch;
                dst = (Uint8 *)dst + dst_pitch;
            }
        }
        بازگشت true;
    }

    اگر (!SDL_InitializeSurface(&src_surface, width, height, src_format, src_colorspace, src_properties, nonconst_src, src_pitch, true)) {
        بازگشت false;
    }
    SDL_SetSurfaceBlendMode(&src_surface, SDL_BLENDMODE_NONE);

    اگر (!SDL_InitializeSurface(&dst_surface, width, height, dst_format, dst_colorspace, dst_properties, dst, dst_pitch, true)) {
        بازگشت false;
    }

    // Set up the rect and go!
    rect.x = 0;
    rect.y = 0;
    rect.w = width;
    rect.h = height;
    result = SDL_BlitSurfaceUnchecked(&src_surface, &rect, &dst_surface, &rect);

    SDL_DestroySurface(&src_surface);
    SDL_DestroySurface(&dst_surface);

    بازگشت result;
}

bool SDL_ConvertPixels(صحیح width, صحیح height, SDL_PixelFormat src_format, ثابت تهی *src, صحیح src_pitch, SDL_PixelFormat dst_format, تهی *dst, صحیح dst_pitch)
{
    بازگشت SDL_ConvertPixelsAndColorspace(width, height,
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

ایستا تهی SDL_PremultiplyAlpha_AXYZ8888(صحیح width, صحیح height, ثابت تهی *src, صحیح src_pitch, تهی *dst, صحیح dst_pitch)
{
    صحیح c;
    Uint32 srcpixel;
    Uint32 srcR, srcG, srcB, srcA;
    Uint32 dstpixel;
    Uint32 dstR, dstG, dstB, dstA;

    وقتی (height--) {
        ثابت Uint32 *src_px = (ثابت Uint32 *)src;
        Uint32 *dst_px = (Uint32 *)dst;
        برای (c = width; c; --c) {
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
        src = (ثابت Uint8 *)src + src_pitch;
        dst = (Uint8 *)dst + dst_pitch;
    }
}

ایستا تهی SDL_PremultiplyAlpha_XYZA8888(صحیح width, صحیح height, ثابت تهی *src, صحیح src_pitch, تهی *dst, صحیح dst_pitch)
{
    صحیح c;
    Uint32 srcpixel;
    Uint32 srcR, srcG, srcB, srcA;
    Uint32 dstpixel;
    Uint32 dstR, dstG, dstB, dstA;

    وقتی (height--) {
        ثابت Uint32 *src_px = (ثابت Uint32 *)src;
        Uint32 *dst_px = (Uint32 *)dst;
        برای (c = width; c; --c) {
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
        src = (ثابت Uint8 *)src + src_pitch;
        dst = (Uint8 *)dst + dst_pitch;
    }
}

ایستا تهی SDL_PremultiplyAlpha_AXYZ128(صحیح width, صحیح height, ثابت تهی *src, صحیح src_pitch, تهی *dst, صحیح dst_pitch)
{
    صحیح c;
    اعشاری flR, flG, flB, flA;

    وقتی (height--) {
        ثابت اعشاری *src_px = (ثابت اعشاری *)src;
        اعشاری *dst_px = (اعشاری *)dst;
        برای (c = width; c; --c) {
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
        src = (ثابت Uint8 *)src + src_pitch;
        dst = (Uint8 *)dst + dst_pitch;
    }
}

ایستا bool SDL_PremultiplyAlphaPixelsAndColorspace(صحیح width, صحیح height, SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ثابت تهی *src, صحیح src_pitch, SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, تهی *dst, صحیح dst_pitch, bool linear)
{
    SDL_Surface *convert = پوچ;
    تهی *final_dst = dst;
    صحیح final_dst_pitch = dst_pitch;
    SDL_PixelFormat format;
    SDL_Colorspace colorspace;
    bool result = false;

    CHECK_PARAM(!src) {
        بازگشت SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!src_pitch) {
        بازگشت SDL_InvalidParamError("src_pitch");
    }
    CHECK_PARAM(!dst) {
        بازگشت SDL_InvalidParamError("dst");
    }
    CHECK_PARAM(!dst_pitch) {
        بازگشت SDL_InvalidParamError("dst_pitch");
    }

    // Use a high precision format if we're converting to linear colorspace or using high precision pixel formats
    اگر (linear ||
        SDL_ISPIXELFORMAT_10BIT(src_format) || SDL_BITSPERPIXEL(src_format) > 32 ||
        SDL_ISPIXELFORMAT_10BIT(dst_format) || SDL_BITSPERPIXEL(dst_format) > 32) {
        اگر (src_format == SDL_PIXELFORMAT_ARGB128_FLOAT ||
            src_format == SDL_PIXELFORMAT_ABGR128_FLOAT) {
            format = src_format;
        } وگرنه {
            format = SDL_PIXELFORMAT_ARGB128_FLOAT;
        }
    } وگرنه {
        اگر (src_format == SDL_PIXELFORMAT_ARGB8888 ||
            src_format == SDL_PIXELFORMAT_ABGR8888 ||
            src_format == SDL_PIXELFORMAT_RGBA8888 ||
            src_format == SDL_PIXELFORMAT_BGRA8888) {
            format = src_format;
        } وگرنه {
            format = SDL_PIXELFORMAT_ARGB8888;
        }
    }
    اگر (linear) {
        colorspace = SDL_COLORSPACE_SRGB_LINEAR;
    } وگرنه {
        colorspace = SDL_COLORSPACE_SRGB;
    }

    اگر (src_format != format || src_colorspace != colorspace) {
        convert = SDL_CreateSurfaceUninitialized(width, height, format);
        اگر (!convert) {
            برو done;
        }
        اگر (!SDL_ConvertPixelsAndColorspace(width, height, src_format, src_colorspace, src_properties, src, src_pitch, format, colorspace, 0, convert->pixels, convert->pitch)) {
            برو done;
        }

        src = convert->pixels;
        src_pitch = convert->pitch;
        dst = convert->pixels;
        dst_pitch = convert->pitch;

    } وگرنه اگر (dst_format != format || dst_colorspace != colorspace) {
        convert = SDL_CreateSurfaceUninitialized(width, height, format);
        اگر (!convert) {
            برو done;
        }
        dst = convert->pixels;
        dst_pitch = convert->pitch;
    }

    انتخاب (format) {
    حالت SDL_PIXELFORMAT_ARGB8888:
    حالت SDL_PIXELFORMAT_ABGR8888:
        SDL_PremultiplyAlpha_AXYZ8888(width, height, src, src_pitch, dst, dst_pitch);
        بشکن;
    حالت SDL_PIXELFORMAT_RGBA8888:
    حالت SDL_PIXELFORMAT_BGRA8888:
        SDL_PremultiplyAlpha_XYZA8888(width, height, src, src_pitch, dst, dst_pitch);
        بشکن;
    حالت SDL_PIXELFORMAT_ARGB128_FLOAT:
    حالت SDL_PIXELFORMAT_ABGR128_FLOAT:
        SDL_PremultiplyAlpha_AXYZ128(width, height, src, src_pitch, dst, dst_pitch);
        بشکن;
    پیشفرض:
        SDL_SetError("Unexpected internal pixel format");
        برو done;
    }

    اگر (dst != final_dst) {
        اگر (!SDL_ConvertPixelsAndColorspace(width, height, format, colorspace, 0, convert->pixels, convert->pitch, dst_format, dst_colorspace, dst_properties, final_dst, final_dst_pitch)) {
            برو done;
        }
    }
    result = true;

done:
    اگر (convert) {
        SDL_DestroySurface(convert);
    }
    بازگشت result;
}

bool SDL_PremultiplyAlpha(صحیح width, صحیح height,
                         SDL_PixelFormat src_format, ثابت تهی *src, صحیح src_pitch,
                         SDL_PixelFormat dst_format, تهی *dst, صحیح dst_pitch, bool linear)
{
    SDL_Colorspace src_colorspace = SDL_GetDefaultColorspaceForFormat(src_format);
    SDL_Colorspace dst_colorspace = SDL_GetDefaultColorspaceForFormat(dst_format);

    بازگشت SDL_PremultiplyAlphaPixelsAndColorspace(width, height, src_format, src_colorspace, 0, src, src_pitch, dst_format, dst_colorspace, 0, dst, dst_pitch, linear);
}

bool SDL_PremultiplySurfaceAlpha(SDL_Surface *surface, bool linear)
{
    SDL_Colorspace colorspace;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        بازگشت SDL_InvalidParamError("surface");
    }

    colorspace = surface->colorspace;

    بازگشت SDL_PremultiplyAlphaPixelsAndColorspace(surface->w, surface->h, surface->format, colorspace, surface->props, surface->pixels, surface->pitch, surface->format, colorspace, surface->props, surface->pixels, surface->pitch, linear);
}

bool SDL_ClearSurface(SDL_Surface *surface, اعشاری r, اعشاری g, اعشاری b, اعشاری a)
{
    SDL_Rect clip_rect;
    bool result = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        بازگشت SDL_InvalidParamError("surface");
    }

    SDL_GetSurfaceClipRect(surface, &clip_rect);
    SDL_SetSurfaceClipRect(surface, پوچ);

    اگر (!SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_BYTESPERPIXEL(surface->format) <= اندازه(Uint32)) {
        Uint32 color;

        color = SDL_MapSurfaceRGBA(surface,
                    (Uint8)SDL_roundf(SDL_clamp(r, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(g, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(b, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(a, 0.0f, 1.0f) * 255.0f));
        result = SDL_FillSurfaceRect(surface, پوچ, color);
    } وگرنه اگر (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // We can't directly set an RGB value on a YUV surface
        SDL_Surface *tmp = SDL_CreateSurfaceUninitialized(surface->w, surface->h, SDL_PIXELFORMAT_ARGB8888);
        اگر (!tmp) {
            برو done;
        }

        اگر (SDL_ClearSurface(tmp, r, g, b, a)) {
            result = SDL_ConvertPixelsAndColorspace(surface->w, surface->h, tmp->format, tmp->colorspace, tmp->props, tmp->pixels, tmp->pitch, surface->format, surface->colorspace, surface->props, surface->pixels, surface->pitch);
        }
        SDL_DestroySurface(tmp);
    } وگرنه {
        // Take advantage of blit color conversion
        SDL_Surface *tmp = SDL_CreateSurfaceUninitialized(1, 1, SDL_PIXELFORMAT_RGBA128_FLOAT);
        اگر (!tmp) {
            برو done;
        }
        SDL_SetSurfaceColorspace(tmp, surface->colorspace);
        SDL_SetSurfaceBlendMode(tmp, SDL_BLENDMODE_NONE);

        اعشاری *pixels = (اعشاری *)tmp->pixels;
        pixels[0] = r;
        pixels[1] = g;
        pixels[2] = b;
        pixels[3] = a;

        result = SDL_BlitSurfaceScaled(tmp, پوچ, surface, پوچ, SDL_SCALEMODE_NEAREST);
        SDL_DestroySurface(tmp);
    }

done:
    SDL_SetSurfaceClipRect(surface, &clip_rect);

    بازگشت result;
}

Uint32 SDL_MapSurfaceRGB(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b)
{
    بازگشت SDL_MapSurfaceRGBA(surface, r, g, b, SDL_ALPHA_OPAQUE);
}

Uint32 SDL_MapSurfaceRGBA(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        بازگشت true;
    }
    بازگشت SDL_MapRGBA(surface->fmt, surface->palette, r, g, b, a);
}

// This function Copyright 2023 Collabora Ltd., contributed to SDL under the ZLib license
bool SDL_ReadSurfacePixel(SDL_Surface *surface, صحیح x, صحیح y, Uint8 *r, Uint8 *g, Uint8 *b, Uint8 *a)
{
    Uint32 pixel = 0;
    size_t bytes_per_pixel;
    Uint8 unused;
    Uint8 *p;
    bool result = false;

    اگر (r) {
        *r = 0;
    } وگرنه {
        r = &unused;
    }

    اگر (g) {
        *g = 0;
    } وگرنه {
        g = &unused;
    }

    اگر (b) {
        *b = 0;
    } وگرنه {
        b = &unused;
    }

    اگر (a) {
        *a = 0;
    } وگرنه {
        a = &unused;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        بازگشت SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        بازگشت SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        بازگشت SDL_InvalidParamError("y");
    }

    bytes_per_pixel = SDL_BYTESPERPIXEL(surface->format);

    اگر (SDL_MUSTLOCK(surface)) {
        اگر (!SDL_LockSurface(surface)) {
            بازگشت false;
        }
    }

    p = (Uint8 *)surface->pixels + y * surface->pitch + x * bytes_per_pixel;

    اگر (bytes_per_pixel <= اندازه(pixel) &&
        !SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_COLORSPACEPRIMARIES(surface->colorspace) == SDL_COLOR_PRIMARIES_BT709) {
        /* Fill the appropriate number of least-significant bytes of pixel,
         * leaving the most-significant bytes set to zero */
#اگر SDL_BYTEORDER == SDL_BIG_ENDIAN
        SDL_memcpy(((Uint8 *)&pixel) + (اندازه(pixel) - bytes_per_pixel), p, bytes_per_pixel);
#وگرنه
        SDL_memcpy(&pixel, p, bytes_per_pixel);
#endif
        SDL_GetRGBA(pixel, surface->fmt, surface->palette, r, g, b, a);
        result = true;
    } وگرنه اگر (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // FIXME: We need code to extract a single macroblock from a YUV surface
        SDL_Surface *converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        اگر (converted) {
            result = SDL_ReadSurfacePixel(converted, x, y, r, g, b, a);
            SDL_DestroySurface(converted);
        }
    } وگرنه {
        // This is really slow, but it gets the job done
        Uint8 rgba[4];

        اگر (SDL_ConvertPixelsAndColorspace(1, 1, surface->format, surface->colorspace, surface->props, p, surface->pitch, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, rgba, اندازه(rgba))) {
            *r = rgba[0];
            *g = rgba[1];
            *b = rgba[2];
            *a = rgba[3];
            result = true;
        }
    }

    اگر (SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }
    بازگشت result;
}

bool SDL_ReadSurfacePixelFloat(SDL_Surface *surface, صحیح x, صحیح y, اعشاری *r, اعشاری *g, اعشاری *b, اعشاری *a)
{
    اعشاری unused;
    bool result = false;

    اگر (r) {
        *r = 0.0f;
    } وگرنه {
        r = &unused;
    }

    اگر (g) {
        *g = 0.0f;
    } وگرنه {
        g = &unused;
    }

    اگر (b) {
        *b = 0.0f;
    } وگرنه {
        b = &unused;
    }

    اگر (a) {
        *a = 0.0f;
    } وگرنه {
        a = &unused;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        بازگشت SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        بازگشت SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        بازگشت SDL_InvalidParamError("y");
    }

    اگر (SDL_BYTESPERPIXEL(surface->format) <= اندازه(Uint32) &&
        !SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_COLORSPACEPRIMARIES(surface->colorspace) == SDL_COLOR_PRIMARIES_BT709) {
        Uint8 r8, g8, b8, a8;

        اگر (SDL_ReadSurfacePixel(surface, x, y, &r8, &g8, &b8, &a8)) {
            *r = (اعشاری)r8 / 255.0f;
            *g = (اعشاری)g8 / 255.0f;
            *b = (اعشاری)b8 / 255.0f;
            *a = (اعشاری)a8 / 255.0f;
            result = true;
        }
    } وگرنه اگر (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // FIXME: We need code to extract a single macroblock from a YUV surface
        SDL_Surface *converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        اگر (converted) {
            result = SDL_ReadSurfacePixelFloat(converted, x, y, r, g, b, a);
            SDL_DestroySurface(converted);
        }
    } وگرنه {
        // This is really slow, but it gets the job done
        اعشاری rgba[4];
        Uint8 *p;

        اگر (SDL_MUSTLOCK(surface)) {
            اگر (!SDL_LockSurface(surface)) {
                بازگشت false;
            }
        }

        p = (Uint8 *)surface->pixels + y * surface->pitch + x * SDL_BYTESPERPIXEL(surface->format);

        اگر (surface->format == SDL_PIXELFORMAT_RGBA128_FLOAT) {
            SDL_memcpy(rgba, p, اندازه(rgba));
            result = true;
        } وگرنه {
            SDL_Colorspace src_colorspace = surface->colorspace;
            SDL_Colorspace dst_colorspace = (src_colorspace == SDL_COLORSPACE_SRGB_LINEAR ? SDL_COLORSPACE_SRGB_LINEAR : SDL_COLORSPACE_SRGB);

            اگر (SDL_ConvertPixelsAndColorspace(1, 1, surface->format, src_colorspace, surface->props, p, surface->pitch, SDL_PIXELFORMAT_RGBA128_FLOAT, dst_colorspace, 0, rgba, اندازه(rgba))) {
                result = true;
            }
        }

        اگر (result) {
            *r = rgba[0];
            *g = rgba[1];
            *b = rgba[2];
            *a = rgba[3];
        }

        اگر (SDL_MUSTLOCK(surface)) {
            SDL_UnlockSurface(surface);
        }
    }
    بازگشت result;
}

bool SDL_WriteSurfacePixel(SDL_Surface *surface, صحیح x, صحیح y, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    Uint32 pixel = 0;
    size_t bytes_per_pixel;
    Uint8 *p;
    bool result = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        بازگشت SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        بازگشت SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        بازگشت SDL_InvalidParamError("y");
    }

    bytes_per_pixel = SDL_BYTESPERPIXEL(surface->format);

    اگر (SDL_MUSTLOCK(surface)) {
        اگر (!SDL_LockSurface(surface)) {
            بازگشت false;
        }
    }

    p = (Uint8 *)surface->pixels + y * surface->pitch + x * bytes_per_pixel;

    اگر (bytes_per_pixel <= اندازه(pixel) && !SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        pixel = SDL_MapRGBA(surface->fmt, surface->palette, r, g, b, a);
#اگر SDL_BYTEORDER == SDL_BIG_ENDIAN
        SDL_memcpy(p, ((Uint8 *)&pixel) + (اندازه(pixel) - bytes_per_pixel), bytes_per_pixel);
#وگرنه
        SDL_memcpy(p, &pixel, bytes_per_pixel);
#endif
        result = true;
    } وگرنه اگر (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        result = SDL_Unsupported();
    } وگرنه {
        // This is really slow, but it gets the job done
        Uint8 rgba[4];

        rgba[0] = r;
        rgba[1] = g;
        rgba[2] = b;
        rgba[3] = a;
        result = SDL_ConvertPixelsAndColorspace(1, 1, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, rgba, اندازه(rgba), surface->format, surface->colorspace, surface->props, p, surface->pitch);
    }

    اگر (SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }
    بازگشت result;
}

bool SDL_WriteSurfacePixelFloat(SDL_Surface *surface, صحیح x, صحیح y, اعشاری r, اعشاری g, اعشاری b, اعشاری a)
{
    bool result = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        بازگشت SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        بازگشت SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        بازگشت SDL_InvalidParamError("y");
    }

    اگر (SDL_BYTESPERPIXEL(surface->format) <= اندازه(Uint32) && !SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        Uint8 r8, g8, b8, a8;

        r8 = (Uint8)SDL_round(SDL_clamp(r, 0.0f, 1.0f) * 255.0f);
        g8 = (Uint8)SDL_round(SDL_clamp(g, 0.0f, 1.0f) * 255.0f);
        b8 = (Uint8)SDL_round(SDL_clamp(b, 0.0f, 1.0f) * 255.0f);
        a8 = (Uint8)SDL_round(SDL_clamp(a, 0.0f, 1.0f) * 255.0f);
        اگر (SDL_WriteSurfacePixel(surface, x, y, r8, g8, b8, a8)) {
            result = true;
        }
    } وگرنه اگر (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        result = SDL_Unsupported();
    } وگرنه {
        // This is really slow, but it gets the job done
        اعشاری rgba[4];
        Uint8 *p;

        اگر (SDL_MUSTLOCK(surface)) {
            اگر (!SDL_LockSurface(surface)) {
                بازگشت false;
            }
        }

        p = (Uint8 *)surface->pixels + y * surface->pitch + x * SDL_BYTESPERPIXEL(surface->format);

        rgba[0] = r;
        rgba[1] = g;
        rgba[2] = b;
        rgba[3] = a;

        اگر (surface->format == SDL_PIXELFORMAT_RGBA128_FLOAT) {
            SDL_memcpy(p, rgba, اندازه(rgba));
            result = true;
        } وگرنه {
            SDL_Colorspace dst_colorspace = surface->colorspace;
            SDL_Colorspace src_colorspace = (dst_colorspace == SDL_COLORSPACE_SRGB_LINEAR ? SDL_COLORSPACE_SRGB_LINEAR : SDL_COLORSPACE_SRGB);

            result = SDL_ConvertPixelsAndColorspace(1, 1, SDL_PIXELFORMAT_RGBA128_FLOAT, src_colorspace, 0, rgba, اندازه(rgba), surface->format, dst_colorspace, surface->props, p, surface->pitch);
        }

        اگر (SDL_MUSTLOCK(surface)) {
            SDL_UnlockSurface(surface);
        }
    }
    بازگشت result;
}

/*
 * Free a surface created by the above function.
 */
تهی SDL_DestroySurface(SDL_Surface *surface)
{
    اگر (!SDL_SurfaceValid(surface)) {
        بازگشت;
    }
    اگر (surface->internal_flags & SDL_INTERNAL_SURFACE_DONTFREE) {
        بازگشت;
    }
    اگر (--surface->refcount > 0) {
        بازگشت;
    }

    SDL_RemoveSurfaceAlternateImages(surface);

    SDL_DestroyProperties(surface->props);

    SDL_InvalidateMap(&surface->map);

    وقتی (surface->locked > 0) {
        SDL_UnlockSurface(surface);
    }
#ifdef SDL_HAVE_RLE
    اگر (surface->internal_flags & SDL_INTERNAL_SURFACE_RLEACCEL) {
        SDL_UnRLESurface(surface);
    }
#endif
    SDL_SetSurfacePalette(surface, پوچ);

    اگر (surface->flags & SDL_SURFACE_PREALLOCATED) {
        // Don't free
    } وگرنه اگر (surface->flags & SDL_SURFACE_SIMD_ALIGNED) {
        // Free aligned
        SDL_aligned_free(surface->pixels);
    } وگرنه {
        // Normal
        SDL_free(surface->pixels);
    }

    surface->reserved = پوچ;

    اگر (!(surface->internal_flags & SDL_INTERNAL_SURFACE_پشته)) {
        SDL_free(surface);
    }
}

SDL_Surface *SDL_LoadSurface_IO(SDL_IOStream *src, bool closeio)
{
    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        بازگشت پوچ;
    }

    اگر (SDL_IsBMP(src)) {
        بازگشت SDL_LoadBMP_IO(src, closeio);
    } وگرنه اگر (SDL_IsPNG(src)) {
        بازگشت SDL_LoadPNG_IO(src, closeio);
    } وگرنه اگر (SDL_IsJPG(src)) {
        بازگشت SDL_LoadJPG_IO(src, closeio);
    } وگرنه {
        اگر (closeio) {
            SDL_CloseIO(src);
        }
        SDL_SetError("Unsupported image format");
        بازگشت پوچ;
    }
}

SDL_Surface *SDL_LoadSurface(ثابت نویسه *file)
{
    SDL_IOStream *stream = SDL_IOFromFile(file, "rb");
    اگر (!stream) {
        بازگشت پوچ;
    }

    بازگشت SDL_LoadSurface_IO(stream, true);
}
