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
#ضمن "SDL_internal.h"

#ضمن "SDL_sysvideo.h"
#ضمن "SDL_video_c.h"
#ضمن "SDL_RLEaccel_c.h"
#ضمن "SDL_pixels_c.h"
#ضمن "SDL_rotate.h"
#ضمن "SDL_stb_c.h"
#ضمن "SDL_yuv_c.h"
#ضمن "../render/SDL_sysrender.h"

#ضمن "SDL_surface_c.h"


// Check to make sure we can safely check multiplication of surface w and pitch and it won't overflow size_t
SDL_COMPILE_TIME_ASSERT(surface_size_assumptions,
                        حجم(صحيح) == حجم(Sint32) && حجم(size_t) >= حجم(Sint32));

SDL_COMPILE_TIME_ASSERT(can_indicate_overflow, SDL_SIZE_MAX > SDL_MAX_SINT32);

// Magic!
ساكن حرف SDL_surface_magic;

// Public routines

bool SDL_SurfaceValid(SDL_Surface *surface)
{
    החזר (surface && surface->reserved == &SDL_surface_magic);
}

فراغ SDL_UpdateSurfaceLockFlag(SDL_Surface *surface)
{
    // We need to mark the surface as needing unlock while locked
    אם ((surface->flags & SDL_SURFACE_LOCKED) ||
        (surface->internal_flags & SDL_INTERNAL_SURFACE_RLEACCEL)) {
        surface->flags |= SDL_SURFACE_LOCK_NEEDED;
    } אחרת {
        surface->flags &= ~SDL_SURFACE_LOCK_NEEDED;
    }
}

/*
 * Calculate the pad-aligned scanline width of a surface.
 *
 * for FOURCC, use SDL_CalculateYUVSize()
 */
ساكن bool SDL_CalculateRGBSize(Uint32 format, size_t width, size_t height, size_t *size, size_t *pitch, bool minimal)
{
    אם (SDL_BITSPERPIXEL(format) >= 8) {
        אם (!SDL_size_mul_check_overflow(width, SDL_BYTESPERPIXEL(format), pitch)) {
            החזר SDL_SetError("width * bpp would overflow");
        }
    } אחרת {
        אם (!SDL_size_mul_check_overflow(width, SDL_BITSPERPIXEL(format), pitch)) {
            החזר SDL_SetError("width * bpp would overflow");
        }
        אם (!SDL_size_add_check_overflow(*pitch, 7, pitch)) {
            החזר SDL_SetError("aligning pitch would overflow");
        }
        *pitch /= 8;
    }
    אם (!minimal) {
        // 4-byte aligning for speed
        אם (!SDL_size_add_check_overflow(*pitch, 3, pitch)) {
            החזר SDL_SetError("aligning pitch would overflow");
        }
        *pitch &= ~3;
    }

    אם (!SDL_size_mul_check_overflow(height, *pitch, size)) {
        החזר SDL_SetError("height * pitch would overflow");
    }

    החזר true;
}

bool SDL_CalculateSurfaceSize(SDL_PixelFormat format, صحيح width, صحيح height, size_t *size, size_t *pitch, bool minimalPitch)
{
    size_t p = 0, sz = 0;

    אם (size) {
        *size = 0;
    }

    אם (pitch) {
        *pitch = 0;
    }

    אם (SDL_ISPIXELFORMAT_FOURCC(format)) {
        אם (format == SDL_PIXELFORMAT_MJPG) {
            // We don't know in advance what it will be, we'll figure it out later.
            החזר true;
        }

        אם (!SDL_CalculateYUVSize(format, width, height, &sz, &p)) {
            // Overflow...
            החזר false;
        }
    } אחרת {
        אם (!SDL_CalculateRGBSize(format, width, height, &sz, &p, minimalPitch)) {
            // Overflow...
            החזר false;
        }
    }

    אם (size) {
        *size = sz;
    }

    אם (pitch) {
        *pitch = p;
    }

    החזר true;
}

ساكن bool SDL_InitializeSurface(SDL_Surface *surface, صحيح width, صحيح height, SDL_PixelFormat format, SDL_Colorspace colorspace, SDL_PropertiesID props, فراغ *pixels, صحيح pitch, bool onstack)
{
    SDL_zerop(surface);

    surface->flags = SDL_SURFACE_PREALLOCATED;
    surface->format = format;
    surface->w = width;
    surface->h = height;
    surface->pixels = pixels;
    surface->pitch = pitch;
    surface->reserved = &SDL_surface_magic;

    אם (onstack) {
        surface->internal_flags |= SDL_INTERNAL_SURFACE_STACK;
    }

    surface->fmt = SDL_GetPixelFormatDetails(format);
    אם (!surface->fmt) {
        SDL_DestroySurface(surface);
        החזר false;
    }

    // Initialize the clip rect
    surface->clip_rect.w = width;
    surface->clip_rect.h = height;

    // Allocate an empty mapping
    surface->map.info.r = 0xFF;
    surface->map.info.g = 0xFF;
    surface->map.info.b = 0xFF;
    surface->map.info.a = 0xFF;

    אם (colorspace == SDL_COLORSPACE_UNKNOWN) {
        surface->colorspace = SDL_GetDefaultColorspaceForFormat(format);
    } אחרת {
        surface->colorspace = colorspace;
    }

    אם (props) {
        אם (!SDL_CopyProperties(props, SDL_GetSurfaceProperties(surface))) {
            SDL_DestroySurface(surface);
            החזר false;
        }
    }

    // By default surfaces with an alpha mask are set up for blending
    אם (SDL_ISPIXELFORMAT_ALPHA(surface->format)) {
        SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
    }

    // The surface is ready to go
    surface->refcount = 1;
    החזר true;
}

/*
 * Create an empty surface of the appropriate depth using the given format
 */
ساكن SDL_Surface *SDL_CreateSurfaceInternal(صحيح width, صحيح height, SDL_PixelFormat format, bool clear_surface)
{
    size_t pitch, size;
    SDL_Surface *surface;

    CHECK_PARAM(width < 0) {
        SDL_InvalidParamError("width");
        החזר عدم;
    }

    CHECK_PARAM(height < 0) {
        SDL_InvalidParamError("height");
        החזר عدم;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        החזר عدم;
    }

    אם (!SDL_CalculateSurfaceSize(format, width, height, &size, &pitch, false /* not minimal pitch */)) {
        // Overflow...
        החזר عدم;
    }

    // Allocate and initialize the surface
    surface = (SDL_Surface *)SDL_malloc(حجم(*surface));
    אם (!surface) {
        החזר عدم;
    }

    אם (!SDL_InitializeSurface(surface, width, height, format, SDL_COLORSPACE_UNKNOWN, 0, عدم, (صحيح)pitch, false)) {
        החזר عدم;
    }

    אם (surface->w && surface->h && format != SDL_PIXELFORMAT_MJPG) {
        surface->flags &= ~SDL_SURFACE_PREALLOCATED;
        אם (SDL_GetHintBoolean("SDL_SURFACE_MALLOC", false)) {
            אם (clear_surface) {
                surface->pixels = SDL_calloc(1, size);
            } אחרת {
                surface->pixels = SDL_malloc(size);
            }
        } אחרת {
            surface->flags |= SDL_SURFACE_SIMD_ALIGNED;
            אם (clear_surface) {
                surface->pixels = SDL_aligned_alloc_zero(SDL_GetSIMDAlignment(), size);
            } אחרת {
                surface->pixels = SDL_aligned_alloc(SDL_GetSIMDAlignment(), size);
            }
        }
        אם (!surface->pixels) {
            SDL_DestroySurface(surface);
            החזר عدم;
        }
    }
    החזר surface;
}

SDL_Surface *SDL_CreateSurfaceZeroed(صحيح width, صحيح height, SDL_PixelFormat format)
{
    החזר SDL_CreateSurfaceInternal(width, height, format, true);
}

SDL_Surface *SDL_CreateSurfaceUninitialized(صحيح width, صحيح height, SDL_PixelFormat format)
{
    החזר SDL_CreateSurfaceInternal(width, height, format, false);
}

SDL_Surface *SDL_CreateSurface(صحيح width, صحيح height, SDL_PixelFormat format)
{
    החזר SDL_CreateSurfaceZeroed(width, height, format);
}


/*
 * Create an RGB surface from an existing memory buffer using the given
 * enum SDL_PIXELFORMAT_* format
 */
SDL_Surface *SDL_CreateSurfaceFrom(صحيح width, صحيح height, SDL_PixelFormat format, فراغ *pixels, صحيح pitch)
{
    CHECK_PARAM(width < 0) {
        SDL_InvalidParamError("width");
        החזר عدم;
    }

    CHECK_PARAM(height < 0) {
        SDL_InvalidParamError("height");
        החזר عدم;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        החזר عدم;
    }

    אם (pitch == 0 && !pixels) {
        // The application will fill these in later with valid values
    } אחרת {
        size_t minimalPitch;

        אם (!SDL_CalculateSurfaceSize(format, width, height, عدم, &minimalPitch, true /* minimal pitch */)) {
            // Overflow...
            החזר عدم;
        }

        CHECK_PARAM(pitch < 0 || (size_t)pitch < minimalPitch) {
            SDL_InvalidParamError("pitch");
            החזר عدم;
        }
    }

    // Allocate and initialize the surface
    SDL_Surface *surface = (SDL_Surface *)SDL_malloc(حجم(*surface));
    אם (!surface ||
        !SDL_InitializeSurface(surface, width, height, format, SDL_COLORSPACE_UNKNOWN, 0, pixels, pitch, false)) {
        החזר عدم;
    }
    החזר surface;
}

SDL_PropertiesID SDL_GetSurfaceProperties(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        החזר 0;
    }

    אם (!surface->props) {
        surface->props = SDL_CreateProperties();
    }
    החזר surface->props;
}

bool SDL_SetSurfaceColorspace(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        החזר SDL_InvalidParamError("surface");
    }

    surface->colorspace = colorspace;
    החזר true;
}

SDL_Colorspace SDL_GetSurfaceColorspace(SDL_Surface *surface)
{
    אם (!SDL_SurfaceValid(surface)) {
        החזר SDL_COLORSPACE_UNKNOWN;
    }

    החזר surface->colorspace;
}

عائم SDL_GetDefaultSDRWhitePoint(SDL_Colorspace colorspace)
{
    החזר SDL_GetSurfaceSDRWhitePoint(عدم, colorspace);
}

عائم SDL_GetSurfaceSDRWhitePoint(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    SDL_TransferCharacteristics transfer = SDL_COLORSPACETRANSFER(colorspace);

    אם (transfer == SDL_TRANSFER_CHARACTERISTICS_LINEAR ||
        transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
        SDL_PropertiesID props;
        عائم default_value = 1.0f;

        אם (SDL_SurfaceValid(surface)) {
            props = surface->props;
        } אחרת {
            props = 0;
        }
        אם (transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
            /* The older standards use an SDR white point of 100 nits.
             * ITU-R BT.2408-6 recommends using an SDR white point of 203 nits.
             * This is the default Chrome uses, and what a lot of game content
             * assumes, so we'll go with that.
             */
            ثابت عائم DEFAULT_PQ_SDR_WHITE_POINT = 203.0f;
            default_value = DEFAULT_PQ_SDR_WHITE_POINT;
        }
        החזר SDL_GetFloatProperty(props, SDL_PROP_SURFACE_SDR_WHITE_POINT_FLOAT, default_value);
    }
    החזר 1.0f;
}

عائم SDL_GetDefaultHDRHeadroom(SDL_Colorspace colorspace)
{
    החזר SDL_GetSurfaceHDRHeadroom(عدم, colorspace);
}

عائم SDL_GetSurfaceHDRHeadroom(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    SDL_TransferCharacteristics transfer = SDL_COLORSPACETRANSFER(colorspace);

    אם (transfer == SDL_TRANSFER_CHARACTERISTICS_LINEAR ||
        transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
        SDL_PropertiesID props;
        عائم default_value = 0.0f;

        אם (SDL_SurfaceValid(surface)) {
            props = surface->props;
        } אחרת {
            props = 0;
        }
        החזר SDL_GetFloatProperty(props, SDL_PROP_SURFACE_HDR_HEADROOM_FLOAT, default_value);
    }
    החזר 1.0f;
}

SDL_Palette *SDL_CreateSurfacePalette(SDL_Surface *surface)
{
    SDL_Palette *palette;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        החזר عدم;
    }

    CHECK_PARAM(!SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        SDL_SetError("The surface is not indexed format");
        החזר عدم;
    }

    palette = SDL_CreatePalette((1 << SDL_BITSPERPIXEL(surface->format)));
    אם (!palette) {
        החזר عدم;
    }

    אם (palette->ncolors == 2) {
        // Create a black and white bitmap palette
        palette->colors[0].r = 0xFF;
        palette->colors[0].g = 0xFF;
        palette->colors[0].b = 0xFF;
        palette->colors[1].r = 0x00;
        palette->colors[1].g = 0x00;
        palette->colors[1].b = 0x00;
    }

    אם (!SDL_SetSurfacePalette(surface, palette)) {
        SDL_DestroyPalette(palette);
        החזר عدم;
    }

    // The surface has retained the palette, we can remove the reference here
    SDL_assert(palette->refcount == 2);
    SDL_DestroyPalette(palette);
    החזר palette;
}

bool SDL_SetSurfacePalette(SDL_Surface *surface, SDL_Palette *palette)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        החזר SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(palette && !SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        החזר SDL_SetError("Surface doesn't use a palette");
    }

    CHECK_PARAM(palette && palette->ncolors > (1 << SDL_BITSPERPIXEL(surface->format))) {
        החזר SDL_SetError("Palette doesn't match surface format");
    }

    אם (palette != surface->palette) {
        אם (surface->palette) {
            SDL_DestroyPalette(surface->palette);
        }

        surface->palette = palette;

        אם (surface->palette) {
            ++surface->palette->refcount;
        }
    }

    SDL_InvalidateMap(&surface->map);

    החזר true;
}

SDL_Palette *SDL_GetSurfacePalette(SDL_Surface *surface)
{
    אם (!SDL_SurfaceValid(surface)) {
        החזר عدم;
    }

    החזר surface->palette;
}

bool SDL_AddSurfaceAlternateImage(SDL_Surface *surface, SDL_Surface *image)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        החזר SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(!SDL_SurfaceValid(image)) {
        החזר SDL_InvalidParamError("image");
    }

    SDL_Surface **images = (SDL_Surface **)SDL_realloc(surface->images, (surface->num_images + 1) * حجم(*images));
    אם (!images) {
        החזר false;
    }
    images[surface->num_images] = image;
    surface->images = images;
    ++surface->num_images;
    ++image->refcount;
    החזר true;
}

bool SDL_SurfaceHasAlternateImages(SDL_Surface *surface)
{
    אם (!SDL_SurfaceValid(surface)) {
        החזר false;
    }

    החזר (surface->num_images > 0);
}

SDL_Surface **SDL_GetSurfaceImages(SDL_Surface *surface, صحيح *count)
{
    אם (count) {
        *count = 0;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        החזר عدم;
    }

    صحيح num_images = 1 + surface->num_images;
    SDL_Surface **images = (SDL_Surface **)SDL_malloc((num_images + 1) * حجم(*images));
    אם (!images) {
        החזר عدم;
    }
    images[0] = surface;
    אם (surface->num_images > 0) {
        SDL_memcpy(&images[1], surface->images, (surface->num_images * حجم(images[1])));
    }
    images[num_images] = عدم;

    אם (count) {
        *count = num_images;
    }
    החזר images;
}

SDL_Surface *SDL_GetSurfaceImage(SDL_Surface *surface, عائم display_scale)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        החזר عدم;
    }

    אם (!SDL_SurfaceHasAlternateImages(surface)) {
        ++surface->refcount;
        החזר surface;
    }

    // This surface has high DPI images, pick the best one available, or scale one to the correct size
    SDL_Surface **images = SDL_GetSurfaceImages(surface, عدم);
    אם (!images) {
        // Failure, fall back to the existing surface
        ++surface->refcount;
        החזר surface;
    }

    // Find closest image. Images that are larger than the
    // desired size are preferred over images that are smaller.
    SDL_Surface *closest = عدم;
    صحيح desired_w = (صحيح)SDL_round(surface->w * display_scale);
    صحيح desired_h = (صحيح)SDL_round(surface->h * display_scale);
    صحيح desired_size = desired_w * desired_h;
    صحيح closest_distance = -1;
    صحيح closest_size = -1;
    עבור (صحيح i = 0; images[i]; ++i) {
        SDL_Surface *candidate = images[i];
        صحيح size = candidate->w * candidate->h;
        صحيح delta_w = (candidate->w - desired_w);
        صحيح delta_h = (candidate->h - desired_h);
        صحيح distance = (delta_w * delta_w) + (delta_h * delta_h);
        אם (closest_distance < 0 || distance < closest_distance ||
            (size > desired_size && closest_size < desired_size)) {
            closest = candidate;
            closest_distance = distance;
            closest_size = size;
        }
    }
    SDL_free(images);
    SDL_assert(closest != عدم);    // We should always have at least one surface

    אם (closest->w == desired_w && closest->h == desired_h) {
        ++closest->refcount;
        החזר closest;
    }

    // We need to scale the image to the correct size. To maintain good image quality, downscaling
    // is done in steps, never reducing the width and height by more than half each time.
    SDL_Surface *scaled = closest;
    עשה {
        صحيح next_scaled_w = SDL_max(desired_w, (scaled->w + 1) / 2);
        صحيح next_scaled_h = SDL_max(desired_h, (scaled->h + 1) / 2);
        SDL_Surface *next_scaled = SDL_ScaleSurface(scaled, next_scaled_w, next_scaled_h, SDL_SCALEMODE_LINEAR);
        אם (scaled != closest) {
            SDL_DestroySurface(scaled);
        }
        scaled = next_scaled;
        אם (!scaled) {
            // Failure, fall back to the closest surface
            ++closest->refcount;
            החזר closest;
        }
    } כלעוד (scaled->w != desired_w || scaled->h != desired_h);

    החזר scaled;
}

فراغ SDL_RemoveSurfaceAlternateImages(SDL_Surface *surface)
{
    אם (!SDL_SurfaceValid(surface)) {
        החזר;
    }

    אם (surface->num_images > 0) {
        עבור (صحيح i = 0; i < surface->num_images; ++i) {
            SDL_DestroySurface(surface->images[i]);
        }
        SDL_free(surface->images);
        surface->images = عدم;
        surface->num_images = 0;
    }
}

bool SDL_SetSurfaceRLE(SDL_Surface *surface, bool enabled)
{
    صحيح flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        החזר SDL_InvalidParamError("surface");
    }

    flags = surface->map.info.flags;
    אם (enabled) {
        surface->map.info.flags |= SDL_COPY_RLE_DESIRED;
    } אחרת {
        surface->map.info.flags &= ~SDL_COPY_RLE_DESIRED;
    }
    אם (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    החזר true;
}

bool SDL_SurfaceHasRLE(SDL_Surface *surface)
{
    אם (!SDL_SurfaceValid(surface)) {
        החזר false;
    }

    אם (!(surface->map.info.flags & SDL_COPY_RLE_DESIRED)) {
        החזר false;
    }

    החזר true;
}

bool SDL_SetSurfaceColorKey(SDL_Surface *surface, bool enabled, Uint32 key)
{
    صحيح flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        החזר SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(surface->palette && key >= ((Uint32)surface->palette->ncolors)) {
        החזר SDL_InvalidParamError("key");
    }

    flags = surface->map.info.flags;
    אם (enabled) {
        surface->map.info.flags |= SDL_COPY_COLORKEY;
        surface->map.info.colorkey = key;
    } אחרת {
        surface->map.info.flags &= ~SDL_COPY_COLORKEY;
    }
    אם (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }

    החזר true;
}

bool SDL_SurfaceHasColorKey(SDL_Surface *surface)
{
    אם (!SDL_SurfaceValid(surface)) {
        החזר false;
    }

    אם (!(surface->map.info.flags & SDL_COPY_COLORKEY)) {
        החזר false;
    }

    החזר true;
}

bool SDL_GetSurfaceColorKey(SDL_Surface *surface, Uint32 *key)
{
    אם (key) {
        *key = 0;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        החזר SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(!(surface->map.info.flags & SDL_COPY_COLORKEY)) {
        החזר SDL_SetError("Surface doesn't have a colorkey");
    }

    אם (key) {
        *key = surface->map.info.colorkey;
    }
    החזר true;
}

/* This is a fairly slow function to switch from colorkey to alpha
   NB: it doesn't handle bpp 1 or 3, because they have no alpha channel */
ساكن فراغ SDL_ConvertColorkeyToAlpha(SDL_Surface *surface, bool ignore_alpha)
{
    صحيح x, y, bpp;

    אם (!SDL_SurfaceValid(surface)) {
        החזר;
    }

    אם (!(surface->map.info.flags & SDL_COPY_COLORKEY) ||
        !SDL_ISPIXELFORMAT_ALPHA(surface->format)) {
        החזר;
    }

    bpp = SDL_BYTESPERPIXEL(surface->format);

    SDL_LockSurface(surface);

    אם (bpp == 2) {
        Uint16 *row, *spot;
        Uint16 ckey = (Uint16)surface->map.info.colorkey;
        Uint16 mask = (Uint16)(~surface->fmt->Amask);

        // Ignore, or not, alpha in colorkey comparison
        אם (ignore_alpha) {
            ckey &= mask;
            row = (Uint16 *)surface->pixels;
            עבור (y = surface->h; y--;) {
                spot = row;
                עבור (x = surface->w; x--;) {
                    אם ((*spot & mask) == ckey) {
                        *spot &= mask;
                    }
                    ++spot;
                }
                row += surface->pitch / 2;
            }
        } אחרת {
            row = (Uint16 *)surface->pixels;
            עבור (y = surface->h; y--;) {
                spot = row;
                עבור (x = surface->w; x--;) {
                    אם (*spot == ckey) {
                        *spot &= mask;
                    }
                    ++spot;
                }
                row += surface->pitch / 2;
            }
        }
    } אחרת אם (bpp == 4) {
        Uint32 *row, *spot;
        Uint32 ckey = surface->map.info.colorkey;
        Uint32 mask = ~surface->fmt->Amask;

        // Ignore, or not, alpha in colorkey comparison
        אם (ignore_alpha) {
            ckey &= mask;
            row = (Uint32 *)surface->pixels;
            עבור (y = surface->h; y--;) {
                spot = row;
                עבור (x = surface->w; x--;) {
                    אם ((*spot & mask) == ckey) {
                        *spot &= mask;
                    }
                    ++spot;
                }
                row += surface->pitch / 4;
            }
        } אחרת {
            row = (Uint32 *)surface->pixels;
            עבור (y = surface->h; y--;) {
                spot = row;
                עבור (x = surface->w; x--;) {
                    אם (*spot == ckey) {
                        *spot &= mask;
                    }
                    ++spot;
                }
                row += surface->pitch / 4;
            }
        }
    }

    SDL_UnlockSurface(surface);

    SDL_SetSurfaceColorKey(surface, false, 0);
    SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
}

bool SDL_SetSurfaceColorMod(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b)
{
    صحيح flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        החזר SDL_InvalidParamError("surface");
    }

    surface->map.info.r = r;
    surface->map.info.g = g;
    surface->map.info.b = b;

    flags = surface->map.info.flags;
    אם (r != 0xFF || g != 0xFF || b != 0xFF) {
        surface->map.info.flags |= SDL_COPY_MODULATE_COLOR;
    } אחרת {
        surface->map.info.flags &= ~SDL_COPY_MODULATE_COLOR;
    }
    אם (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    החזר true;
}

bool SDL_GetSurfaceColorMod(SDL_Surface *surface, Uint8 *r, Uint8 *g, Uint8 *b)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        אם (r) {
            *r = 255;
        }
        אם (g) {
            *g = 255;
        }
        אם (b) {
            *b = 255;
        }
        החזר SDL_InvalidParamError("surface");
    }

    אם (r) {
        *r = surface->map.info.r;
    }
    אם (g) {
        *g = surface->map.info.g;
    }
    אם (b) {
        *b = surface->map.info.b;
    }
    החזר true;
}

bool SDL_SetSurfaceAlphaMod(SDL_Surface *surface, Uint8 alpha)
{
    صحيح flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        החזר SDL_InvalidParamError("surface");
    }

    surface->map.info.a = alpha;

    flags = surface->map.info.flags;
    אם (alpha != 0xFF) {
        surface->map.info.flags |= SDL_COPY_MODULATE_ALPHA;
    } אחרת {
        surface->map.info.flags &= ~SDL_COPY_MODULATE_ALPHA;
    }
    אם (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    החזר true;
}

bool SDL_GetSurfaceAlphaMod(SDL_Surface *surface, Uint8 *alpha)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        אם (alpha) {
            *alpha = 255;
        }
        החזר SDL_InvalidParamError("surface");
    }

    אם (alpha) {
        *alpha = surface->map.info.a;
    }
    החזר true;
}

bool SDL_SetSurfaceBlendMode(SDL_Surface *surface, SDL_BlendMode blendMode)
{
    صحيح flags;
    bool result = true;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        החזר SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(blendMode == SDL_BLENDMODE_INVALID) {
        החזר SDL_InvalidParamError("blendMode");
    }

    flags = surface->map.info.flags;
    surface->map.info.flags &= ~SDL_COPY_BLEND_MASK;
    بدل (blendMode) {
    حالة SDL_BLENDMODE_NONE:
        اكسر;
    حالة SDL_BLENDMODE_BLEND:
        surface->map.info.flags |= SDL_COPY_BLEND;
        اكسر;
    حالة SDL_BLENDMODE_BLEND_PREMULTIPLIED:
        surface->map.info.flags |= SDL_COPY_BLEND_PREMULTIPLIED;
        اكسر;
    حالة SDL_BLENDMODE_ADD:
        surface->map.info.flags |= SDL_COPY_ADD;
        اكسر;
    حالة SDL_BLENDMODE_ADD_PREMULTIPLIED:
        surface->map.info.flags |= SDL_COPY_ADD_PREMULTIPLIED;
        اكسر;
    حالة SDL_BLENDMODE_MOD:
        surface->map.info.flags |= SDL_COPY_MOD;
        اكسر;
    حالة SDL_BLENDMODE_MUL:
        surface->map.info.flags |= SDL_COPY_MUL;
        اكسر;
    افتراضي:
        result = SDL_Unsupported();
        اكسر;
    }

    אם (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }

    החזר result;
}

bool SDL_GetSurfaceBlendMode(SDL_Surface *surface, SDL_BlendMode *blendMode)
{
    אם (blendMode) {
        *blendMode = SDL_BLENDMODE_INVALID;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        החזר SDL_InvalidParamError("surface");
    }

    אם (!blendMode) {
        החזר true;
    }

    بدل (surface->map.info.flags & SDL_COPY_BLEND_MASK) {
    حالة SDL_COPY_BLEND:
        *blendMode = SDL_BLENDMODE_BLEND;
        اكسر;
    حالة SDL_COPY_BLEND_PREMULTIPLIED:
        *blendMode = SDL_BLENDMODE_BLEND_PREMULTIPLIED;
        اكسر;
    حالة SDL_COPY_ADD:
        *blendMode = SDL_BLENDMODE_ADD;
        اكسر;
    حالة SDL_COPY_ADD_PREMULTIPLIED:
        *blendMode = SDL_BLENDMODE_ADD_PREMULTIPLIED;
        اكسر;
    حالة SDL_COPY_MOD:
        *blendMode = SDL_BLENDMODE_MOD;
        اكسر;
    حالة SDL_COPY_MUL:
        *blendMode = SDL_BLENDMODE_MUL;
        اكسر;
    افتراضي:
        *blendMode = SDL_BLENDMODE_NONE;
        اكسر;
    }
    החזר true;
}

bool SDL_SetSurfaceClipRect(SDL_Surface *surface, ثابت SDL_Rect *rect)
{
    SDL_Rect full_rect;

    // Don't do anything if there's no surface to act on
    אם (!SDL_SurfaceValid(surface)) {
        החזר false;
    }

    // Set up the full surface rectangle
    full_rect.x = 0;
    full_rect.y = 0;
    full_rect.w = surface->w;
    full_rect.h = surface->h;

    // Set the clipping rectangle
    אם (!rect) {
        surface->clip_rect = full_rect;
        החזר true;
    }
    החזר SDL_GetRectIntersection(rect, &full_rect, &surface->clip_rect);
}

bool SDL_GetSurfaceClipRect(SDL_Surface *surface, SDL_Rect *rect)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        אם (rect) {
            SDL_zerop(rect);
        }
        החזר SDL_InvalidParamError("surface");
    }
    CHECK_PARAM(!rect) {
        החזר SDL_InvalidParamError("rect");
    }
    *rect = surface->clip_rect;
    החזר true;
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
    אם (!SDL_ValidateMap(src, dst)) {
        החזר false;
    }
    החזר src->map.blit(src, srcrect, dst, dstrect);
}

bool SDL_BlitSurface(SDL_Surface *src, ثابت SDL_Rect *srcrect, SDL_Surface *dst, ثابت SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src) || (!src->pixels && !SDL_MUSTLOCK(src))) {
        החזר SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst) || (!dst->pixels && !SDL_MUSTLOCK(dst))) {
        החזר SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        החזר SDL_SetError("Surfaces must not be locked during blit");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    אם (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
    } אחרת {
        r_dst.x = 0;
        r_dst.y = 0;
    }

    // clip the source rectangle to the source surface
    אם (srcrect) {
        SDL_Rect tmp;
        אם (SDL_GetRectIntersection(srcrect, &r_src, &tmp) == false) {
            החזר true;
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
        אם (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &tmp) == false) {
            החזר true;
        }

        // Shift srcrect, if dstrect has changed
        r_src.x += tmp.x - r_dst.x;
        r_src.y += tmp.y - r_dst.y;
        r_src.w = tmp.w;
        r_src.h = tmp.h;

        // Update dstrect
        r_dst = tmp;
    }

    אם (r_dst.w <= 0 || r_dst.h <= 0) {
        // No-op.
        החזר true;
    }

    // Switch back to a fast blit if we were previously stretching
    אם (src->map.info.flags & SDL_COPY_NEAREST) {
        src->map.info.flags &= ~SDL_COPY_NEAREST;
        SDL_InvalidateMap(&src->map);
    }

    החזר SDL_BlitSurfaceUnchecked(src, &r_src, dst, &r_dst);
}

ساكن bool SDL_BlitSurfaceClippedScaled(SDL_Surface *src, ثابت SDL_Rect *srcrect, SDL_Surface *dst, ثابت SDL_Rect *dstrect, SDL_ScaleMode scaleMode)
{
    // We need to scale first, then blit into dst because we're clipping in the destination surface pixel coordinates
    bool result;
    صحيح saved_w = src->w;
    صحيح saved_h = src->h;
    فراغ *saved_pixels = src->pixels;
    src->w = srcrect->w;
    src->h = srcrect->h;
    src->pixels = (Uint8 *)src->pixels + srcrect->y * src->pitch + srcrect->x * SDL_BYTESPERPIXEL(src->format);
    SDL_Surface *scaled = SDL_ScaleSurface(src, dstrect->w, dstrect->h, scaleMode);
    אם (scaled) {
        result = SDL_BlitSurface(scaled, عدم, dst, dstrect);
        SDL_DestroySurface(scaled);
    } אחרת {
        result = false;
    }
    src->w = saved_w;
    src->h = saved_h;
    src->pixels = saved_pixels;
    החזר result;
}

bool SDL_BlitSurfaceScaled(SDL_Surface *src, ثابت SDL_Rect *srcrect, SDL_Surface *dst, ثابت SDL_Rect *dstrect, SDL_ScaleMode scaleMode)
{
    SDL_Rect r_src, r_dst;
    bool result;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src) || (!src->pixels && !SDL_MUSTLOCK(src))) {
        החזר SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst) || (!dst->pixels && !SDL_MUSTLOCK(dst))) {
        החזר SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        החזר SDL_SetError("Surfaces must not be locked during blit");
    }

    بدل (scaleMode) {
    حالة SDL_SCALEMODE_NEAREST:
        اكسر;
    حالة SDL_SCALEMODE_LINEAR:
        اكسر;
    حالة SDL_SCALEMODE_PIXELART:
        scaleMode = SDL_SCALEMODE_NEAREST;
        اكسر;
    افتراضي:
        החזר SDL_InvalidParamError("scaleMode");
    }

    صحيح src_w = srcrect ? srcrect->w : src->w;
    صحيح src_h = srcrect ? srcrect->h : src->h;
    صحيح dst_w = dstrect ? dstrect->w : dst->w;
    صحيح dst_h = dstrect ? dstrect->h : dst->h;
    אם (src_w == dst_w && src_h == dst_h) {
        // No scaling, defer to regular blit
        החזר SDL_BlitSurface(src, srcrect, dst, dstrect);
    }

    אם (src->w == 0 || src->h == 0) {
        // Nothing to do
        החזר true;
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    אם (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
        r_dst.w = dstrect->w;
        r_dst.h = dstrect->h;
    } אחרת {
        r_dst.x = 0;
        r_dst.y = 0;
        r_dst.w = dst->w;
        r_dst.h = dst->h;
    }

    // clip the source rectangle to the source surface
    אם (srcrect) {
        SDL_Rect desired, tmp;
        desired.x = srcrect->x;
        desired.y = srcrect->y;
        desired.w = SDL_max(srcrect->w, 1);
        desired.h = SDL_max(srcrect->h, 1);
        אם (SDL_GetRectIntersection(&desired, &r_src, &tmp) == false) {
            החזר true;
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
    אם (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &tmp) == false) {
        החזר true;
    }

    אם (tmp.x != r_dst.x || tmp.y != r_dst.y || tmp.w != r_dst.w || tmp.h != r_dst.h) {
        // Need to do a clipped and scaled blit
        החזר SDL_BlitSurfaceClippedScaled(src, &r_src, dst, &r_dst, scaleMode);
    }

    אם (SDL_MUSTLOCK(src)) {
        אם (!SDL_LockSurface(src)) {
            החזר false;
        }
    }
    אם (SDL_MUSTLOCK(dst)) {
        אם (!SDL_LockSurface(dst)) {
            אם (SDL_MUSTLOCK(src)) {
                SDL_UnlockSurface(src);
            }
            החזר false;
        }
    }

    result = SDL_BlitSurfaceUncheckedScaled(src, &r_src, dst, &r_dst, scaleMode);

    אם (SDL_MUSTLOCK(src)) {
        SDL_UnlockSurface(src);
    }
    אם (SDL_MUSTLOCK(dst)) {
        SDL_UnlockSurface(dst);
    }
    החזר result;
}

/**
 *  This is a semi-private blit function and it performs low-level surface
 *  scaled blitting only.
 */
bool SDL_BlitSurfaceUncheckedScaled(SDL_Surface *src, ثابت SDL_Rect *srcrect, SDL_Surface *dst, ثابت SDL_Rect *dstrect, SDL_ScaleMode scaleMode)
{
    ساكن ثابت Uint32 complex_copy_flags = (SDL_COPY_MODULATE_MASK | SDL_COPY_BLEND_MASK | SDL_COPY_COLORKEY);

    אם (srcrect->w > SDL_MAX_UINT16 || srcrect->h > SDL_MAX_UINT16 ||
        dstrect->w > SDL_MAX_UINT16 || dstrect->h > SDL_MAX_UINT16) {
        החזר SDL_SetError("Size too large for scaling");
    }

    אם (!(src->map.info.flags & SDL_COPY_NEAREST)) {
        src->map.info.flags |= SDL_COPY_NEAREST;
        SDL_InvalidateMap(&src->map);
    }

    אם (scaleMode == SDL_SCALEMODE_NEAREST || scaleMode == SDL_SCALEMODE_PIXELART) {
        אם (!(src->map.info.flags & complex_copy_flags) &&
            src->format == dst->format &&
            (!SDL_ISPIXELFORMAT_INDEXED(src->format) ||
             (SDL_BITSPERPIXEL(src->format) == 8 && SDL_IsSamePalette(src->palette, dst->palette))) &&
            SDL_BYTESPERPIXEL(src->format) <= 4) {
            החזר SDL_StretchSurface(src, srcrect, dst, dstrect, SDL_SCALEMODE_NEAREST);
        } אחרת אם (SDL_BITSPERPIXEL(src->format) < 8) {
            // Scaling bitmap not yet supported, convert to RGBA for blit
            bool result = false;
            SDL_Surface *tmp = SDL_ConvertSurface(src, SDL_PIXELFORMAT_ARGB8888);
            אם (tmp) {
                result = SDL_BlitSurfaceUncheckedScaled(tmp, srcrect, dst, dstrect, SDL_SCALEMODE_NEAREST);
                SDL_DestroySurface(tmp);
            }
            החזר result;
        } אחרת {
            החזר SDL_BlitSurfaceUnchecked(src, srcrect, dst, dstrect);
        }
    } אחרת {
        אם (!(src->map.info.flags & complex_copy_flags) &&
            src->format == dst->format &&
            !SDL_ISPIXELFORMAT_INDEXED(src->format) &&
            SDL_BYTESPERPIXEL(src->format) == 4 &&
            src->format != SDL_PIXELFORMAT_ARGB2101010) {
            // fast path
            החזר SDL_StretchSurface(src, srcrect, dst, dstrect, SDL_SCALEMODE_LINEAR);
        } אחרת אם (SDL_BITSPERPIXEL(src->format) < 8) {
            // Scaling bitmap not yet supported, convert to RGBA for blit
            bool result = false;
            SDL_Surface *tmp = SDL_ConvertSurface(src, SDL_PIXELFORMAT_ARGB8888);
            אם (tmp) {
                result = SDL_BlitSurfaceUncheckedScaled(tmp, srcrect, dst, dstrect, scaleMode);
                SDL_DestroySurface(tmp);
            }
            החזר result;
        } אחרת {
            // Use intermediate surface(s)
            SDL_Surface *tmp1 = عدم;
            bool result;
            SDL_Rect srcrect2;
            صحيح is_complex_copy_flags = (src->map.info.flags & complex_copy_flags);

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
            אם (SDL_BYTESPERPIXEL(src->format) != 4 || src->format == SDL_PIXELFORMAT_ARGB2101010) {
                SDL_PixelFormat fmt;
                אם (SDL_BYTESPERPIXEL(dst->format) == 4 && dst->format != SDL_PIXELFORMAT_ARGB2101010 &&
                    (SDL_ISPIXELFORMAT_ALPHA(dst->format) || !is_complex_copy_flags)) {
                    fmt = dst->format;
                } אחרת {
                    fmt = SDL_PIXELFORMAT_ARGB8888;
                }
                tmp1 = SDL_ConvertSurfaceRect(src, srcrect, fmt);
                אם (!tmp1) {
                    החזר false;
                }
                src = tmp1;
                srcrect2.x = 0;
                srcrect2.y = 0;
            }

            // Intermediate scaling
            אם (is_complex_copy_flags || src->format != dst->format) {
                SDL_Rect tmprect;
                SDL_Surface *tmp2 = SDL_CreateSurfaceUninitialized(dstrect->w, dstrect->h, src->format);
                SDL_StretchSurface(src, &srcrect2, tmp2, عدم, SDL_SCALEMODE_LINEAR);

                SDL_SetSurfaceColorMod(tmp2, r, g, b);
                SDL_SetSurfaceAlphaMod(tmp2, alpha);
                SDL_SetSurfaceBlendMode(tmp2, blendMode);

                tmprect.x = 0;
                tmprect.y = 0;
                tmprect.w = dstrect->w;
                tmprect.h = dstrect->h;
                result = SDL_BlitSurfaceUnchecked(tmp2, &tmprect, dst, dstrect);
                SDL_DestroySurface(tmp2);
            } אחרת {
                result = SDL_StretchSurface(src, &srcrect2, dst, dstrect, SDL_SCALEMODE_LINEAR);
            }

            SDL_DestroySurface(tmp1);
            החזר result;
        }
    }
}

bool SDL_BlitSurfaceTiled(SDL_Surface *src, ثابت SDL_Rect *srcrect, SDL_Surface *dst, ثابت SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        החזר SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        החזר SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        החזר SDL_SetError("Surfaces must not be locked during blit");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    אם (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
        r_dst.w = dstrect->w;
        r_dst.h = dstrect->h;
    } אחרת {
        r_dst.x = 0;
        r_dst.y = 0;
        r_dst.w = dst->w;
        r_dst.h = dst->h;
    }

    // clip the source rectangle to the source surface
    אם (srcrect) {
        אם (SDL_GetRectIntersection(srcrect, &r_src, &r_src) == false) {
            החזר true;
        }

        // For tiling we don't adjust the destination rectangle
    }

    // clip the destination rectangle against the clip rectangle
    {
        אם (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &r_dst) == false) {
            החזר true;
        }

        // For tiling we don't adjust the source rectangle
    }

    // Switch back to a fast blit if we were previously stretching
    אם (src->map.info.flags & SDL_COPY_NEAREST) {
        src->map.info.flags &= ~SDL_COPY_NEAREST;
        SDL_InvalidateMap(&src->map);
    }

    صحيح rows = r_dst.h / r_src.h;
    صحيح cols = r_dst.w / r_src.w;
    صحيح remaining_w = r_dst.w % r_src.w;
    صحيح remaining_h = r_dst.h % r_src.h;
    SDL_Rect curr_src, curr_dst;

    SDL_copyp(&curr_src, &r_src);
    curr_dst.y = r_dst.y;
    curr_dst.w = r_src.w;
    curr_dst.h = r_src.h;
    עבור (صحيح y = 0; y < rows; ++y) {
        curr_dst.x = r_dst.x;
        עבור (صحيح x = 0; x < cols; ++x) {
            אם (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                החזר false;
            }
            curr_dst.x += curr_dst.w;
        }
        אם (remaining_w) {
            curr_src.w = remaining_w;
            curr_dst.w = remaining_w;
            אם (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                החזר false;
            }
            curr_src.w = r_src.w;
            curr_dst.w = r_src.w;
        }
        curr_dst.y += curr_dst.h;
    }
    אם (remaining_h) {
        curr_src.h = remaining_h;
        curr_dst.h = remaining_h;
        curr_dst.x = r_dst.x;
        עבור (صحيح x = 0; x < cols; ++x) {
            אם (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                החזר false;
            }
            curr_dst.x += curr_dst.w;
        }
        אם (remaining_w) {
            curr_src.w = remaining_w;
            curr_dst.w = remaining_w;
            אם (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                החזר false;
            }
        }
    }
    החזר true;
}

bool SDL_BlitSurfaceTiledWithScale(SDL_Surface *src, ثابت SDL_Rect *srcrect, عائم scale, SDL_ScaleMode scaleMode, SDL_Surface *dst, ثابت SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        החזר SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        החזר SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        החזר SDL_SetError("Surfaces must not be locked during blit");
    }
    CHECK_PARAM(scale < 0.0f) {
        החזר SDL_InvalidParamError("scale");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    אם (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
        r_dst.w = dstrect->w;
        r_dst.h = dstrect->h;
    } אחרת {
        r_dst.x = 0;
        r_dst.y = 0;
        r_dst.w = dst->w;
        r_dst.h = dst->h;
    }

    // clip the source rectangle to the source surface
    אם (srcrect) {
        אם (SDL_GetRectIntersection(srcrect, &r_src, &r_src) == false) {
            החזר true;
        }

        // For tiling we don't adjust the destination rectangle
    }

    // clip the destination rectangle against the clip rectangle
    {
        אם (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &r_dst) == false) {
            החזר true;
        }

        // For tiling we don't adjust the source rectangle
    }

    // Switch back to a fast blit if we were previously stretching
    אם (src->map.info.flags & SDL_COPY_NEAREST) {
        src->map.info.flags &= ~SDL_COPY_NEAREST;
        SDL_InvalidateMap(&src->map);
    }

    صحيح tile_width = (صحيح)SDL_roundf(r_src.w * scale);
    صحيح tile_height = (صحيح)SDL_roundf(r_src.h * scale);
    אם (tile_width <= 0 || tile_height <= 0) {
        // Nothing to do
        החזר true;
    }
    صحيح rows = r_dst.h / tile_height;
    صحيح cols = r_dst.w / tile_width;
    صحيح remaining_dst_w = (r_dst.w - cols * tile_width);
    صحيح remaining_dst_h = (r_dst.h - rows * tile_height);
    صحيح remaining_src_w = (صحيح)(remaining_dst_w / scale);
    صحيح remaining_src_h = (صحيح)(remaining_dst_h / scale);
    SDL_Rect curr_src, curr_dst;

    SDL_copyp(&curr_src, &r_src);
    curr_dst.y = r_dst.y;
    curr_dst.w = tile_width;
    curr_dst.h = tile_height;
    עבור (صحيح y = 0; y < rows; ++y) {
        curr_dst.x = r_dst.x;
        עבור (صحيح x = 0; x < cols; ++x) {
            אם (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
                החזר false;
            }
            curr_dst.x += curr_dst.w;
        }
        אם (remaining_dst_w > 0) {
            curr_src.w = remaining_src_w;
            curr_dst.w = remaining_dst_w;
            אם (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
                החזר false;
            }
            curr_src.w = r_src.w;
            curr_dst.w = tile_width;
        }
        curr_dst.y += curr_dst.h;
    }
    אם (remaining_dst_h > 0) {
        curr_src.h = remaining_src_h;
        curr_dst.h = remaining_dst_h;
        curr_dst.x = r_dst.x;
        עבור (صحيح x = 0; x < cols; ++x) {
            אם (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
                החזר false;
            }
            curr_dst.x += curr_dst.w;
        }
        אם (remaining_dst_w > 0) {
            curr_src.w = remaining_src_w;
            curr_dst.w = remaining_dst_w;
            אם (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
                החזר false;
            }
        }
    }
    החזר true;
}

bool SDL_BlitSurface9Grid(SDL_Surface *src, ثابت SDL_Rect *srcrect, صحيح left_width, صحيح right_width, صحيح top_height, صحيح bottom_height, عائم scale, SDL_ScaleMode scaleMode, SDL_Surface *dst, ثابت SDL_Rect *dstrect)
{
    SDL_Rect full_src, full_dst;
    SDL_Rect curr_src, curr_dst;
    صحيح dst_left_width;
    صحيح dst_right_width;
    صحيح dst_top_height;
    صحيح dst_bottom_height;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        החזר SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        החזר SDL_InvalidParamError("dst");
    }

    אם (!srcrect) {
        full_src.x = 0;
        full_src.y = 0;
        full_src.w = src->w;
        full_src.h = src->h;
        srcrect = &full_src;
    }

    אם (!dstrect) {
        full_dst.x = 0;
        full_dst.y = 0;
        full_dst.w = dst->w;
        full_dst.h = dst->h;
        dstrect = &full_dst;
    }

    אם (scale <= 0.0f || scale == 1.0f) {
        dst_left_width = left_width;
        dst_right_width = right_width;
        dst_top_height = top_height;
        dst_bottom_height = bottom_height;
    } אחרת {
        dst_left_width = (صحيح)SDL_roundf(left_width * scale);
        dst_right_width = (صحيح)SDL_roundf(right_width * scale);
        dst_top_height = (صحيح)SDL_roundf(top_height * scale);
        dst_bottom_height = (صحيح)SDL_roundf(bottom_height * scale);
    }

    // Upper-left corner
    curr_src.x = srcrect->x;
    curr_src.y = srcrect->y;
    curr_src.w = left_width;
    curr_src.h = top_height;
    curr_dst.x = dstrect->x;
    curr_dst.y = dstrect->y;
    curr_dst.w = dst_left_width;
    curr_dst.h = dst_top_height;
    אם (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        החזר false;
    }

    // Upper-right corner
    curr_src.x = srcrect->x + srcrect->w - right_width;
    curr_src.w = right_width;
    curr_dst.x = dstrect->x + dstrect->w - dst_right_width;
    curr_dst.w = dst_right_width;
    אם (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        החזר false;
    }

    // Lower-right corner
    curr_src.y = srcrect->y + srcrect->h - bottom_height;
    curr_dst.y = dstrect->y + dstrect->h - dst_bottom_height;
    curr_dst.h = dst_bottom_height;
    אם (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        החזר false;
    }

    // Lower-left corner
    curr_src.x = srcrect->x;
    curr_src.w = left_width;
    curr_dst.x = dstrect->x;
    curr_dst.w = dst_left_width;
    אם (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        החזר false;
    }

    // Left
    curr_src.y = srcrect->y + top_height;
    curr_src.h = srcrect->h - top_height - bottom_height;
    curr_dst.y = dstrect->y + dst_top_height;
    curr_dst.h = dstrect->h - dst_top_height - dst_bottom_height;
    אם (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        החזר false;
    }

    // Right
    curr_src.x = srcrect->x + srcrect->w - right_width;
    curr_src.w = right_width;
    curr_dst.x = dstrect->x + dstrect->w - dst_right_width;
    curr_dst.w = dst_right_width;
    אם (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        החזר false;
    }

    // Top
    curr_src.x = srcrect->x + left_width;
    curr_src.y = srcrect->y;
    curr_src.w = srcrect->w - left_width - right_width;
    curr_src.h = top_height;
    curr_dst.x = dstrect->x + dst_left_width;
    curr_dst.y = dstrect->y;
    curr_dst.w = dstrect->w - dst_left_width - dst_right_width;
    curr_dst.h = dst_top_height;
    אם (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        החזר false;
    }

    // Bottom
    curr_src.y = srcrect->y + srcrect->h - bottom_height;
    curr_dst.y = dstrect->y + dstrect->h - dst_bottom_height;
    curr_dst.h = dst_bottom_height;
    אם (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        החזר false;
    }

    // Center
    curr_src.x = srcrect->x + left_width;
    curr_src.y = srcrect->y + top_height;
    curr_src.w = srcrect->w - left_width - right_width;
    curr_src.h = srcrect->h - top_height - bottom_height;
    curr_dst.x = dstrect->x + dst_left_width;
    curr_dst.y = dstrect->y + dst_top_height;
    curr_dst.w = dstrect->w - dst_left_width - dst_right_width;
    curr_dst.h = dstrect->h - dst_top_height - dst_bottom_height;
    אם (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        החזר false;
    }

    החזר true;
}

/*
 * Lock a surface to directly access the pixels
 */
bool SDL_LockSurface(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        החזר SDL_InvalidParamError("surface");
    }

    אם (!surface->locked) {
#ifdef SDL_HAVE_RLE
        // Perform the lock
        אם (surface->internal_flags & SDL_INTERNAL_SURFACE_RLEACCEL) {
            SDL_UnRLESurface(surface);
        }
#endif
    }

    // Increment the surface lock count, for recursive locks
    ++surface->locked;
    surface->flags |= SDL_SURFACE_LOCKED;
    SDL_UpdateSurfaceLockFlag(surface);

    // Ready to go..
    החזר true;
}

/*
 * Unlock a previously locked surface
 */
فراغ SDL_UnlockSurface(SDL_Surface *surface)
{
    אם (!SDL_SurfaceValid(surface)) {
        החזר;
    }

    // Only perform an unlock if we are locked
    אם (!surface->locked || (--surface->locked > 0)) {
        החזר;
    }

    surface->flags &= ~SDL_SURFACE_LOCKED;
    SDL_UpdateSurfaceLockFlag(surface);
}

ساكن bool SDL_FlipSurfaceHorizontal(SDL_Surface *surface)
{
    bool isstack;
    Uint8 *row, *a, *b, *tmp;
    صحيح i, j, bpp;

    אם (SDL_BITSPERPIXEL(surface->format) < 8) {
        // We could implement this if needed, but we'd have to flip sets of bits within a byte
        החזר SDL_Unsupported();
    }

    אם (surface->h <= 0) {
        החזר true;
    }

    אם (surface->w <= 1) {
        החזר true;
    }

    bpp = SDL_BYTESPERPIXEL(surface->format);
    row = (Uint8 *)surface->pixels;
    tmp = SDL_small_alloc(Uint8, surface->pitch, &isstack);
    אם (!tmp) {
        החזר false;
    }
    עבור (i = surface->h; i--; ) {
        a = row;
        b = a + (surface->w - 1) * bpp;
        עבור (j = surface->w / 2; j--; ) {
            SDL_memcpy(tmp, a, bpp);
            SDL_memcpy(a, b, bpp);
            SDL_memcpy(b, tmp, bpp);
            a += bpp;
            b -= bpp;
        }
        row += surface->pitch;
    }
    SDL_small_free(tmp, isstack);
    החזר true;
}

ساكن bool SDL_FlipSurfaceVertical(SDL_Surface *surface)
{
    bool isstack;
    Uint8 *a, *b, *tmp;
    صحيح i;

    אם (surface->h <= 1) {
        החזר true;
    }

    a = (Uint8 *)surface->pixels;
    b = a + (surface->h - 1) * surface->pitch;
    tmp = SDL_small_alloc(Uint8, surface->pitch, &isstack);
    אם (!tmp) {
        החזר false;
    }
    עבור (i = surface->h / 2; i--; ) {
        SDL_memcpy(tmp, a, surface->pitch);
        SDL_memcpy(a, b, surface->pitch);
        SDL_memcpy(b, tmp, surface->pitch);
        a += surface->pitch;
        b -= surface->pitch;
    }
    SDL_small_free(tmp, isstack);
    החזר true;
}

bool SDL_FlipSurface(SDL_Surface *surface, SDL_FlipMode flip)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        החזר SDL_InvalidParamError("surface");
    }
    אם (!surface->pixels) {
        החזר true;
    }

    bool result = true;
    بدل (flip) {
    حالة SDL_FLIP_HORIZONTAL:
        result = SDL_FlipSurfaceHorizontal(surface);
        اكسر;
    حالة SDL_FLIP_VERTICAL:
        result = SDL_FlipSurfaceVertical(surface);
        اكسر;
    حالة SDL_FLIP_HORIZONTAL_AND_VERTICAL:
        result &= SDL_FlipSurfaceHorizontal(surface);
        result &= SDL_FlipSurfaceVertical(surface);
        اكسر;
    افتراضي:
        result = SDL_InvalidParamError("flip");
        اكسر;
    }
    החזר result;
}

ساكن SDL_Surface *SDL_ConvertSurfaceRectAndColorspace(SDL_Surface *surface, ثابت SDL_Rect *rect, SDL_PixelFormat format, SDL_Palette *palette, SDL_Colorspace colorspace, SDL_PropertiesID props)
{
    SDL_Palette *temp_palette = عدم;
    SDL_Surface *convert = عدم;
    SDL_Colorspace src_colorspace;
    SDL_PropertiesID src_properties;
    Uint32 copy_flags;
    SDL_Color copy_color;
    SDL_Rect bounds;
    bool result;
    bool palette_ck_transform = false;
    Uint8 palette_ck_value = 0;
    Uint8 *palette_saved_alpha = عدم;
    صحيح palette_saved_alpha_ncolors = 0;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        اذهب error;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        اذهب error;
    }

    // Set the bounds of the new surface
    bounds.x = 0;
    bounds.y = 0;
    bounds.w = surface->w;
    bounds.h = surface->h;
    אם (rect) {
        bounds.w = rect->w;
        bounds.h = rect->h;
    } אחרת {
        rect = &bounds;
    }

    // Check for empty destination palette! (results in empty image)
    אם (palette) {
        صحيح i;
        עבור (i = 0; i < palette->ncolors; ++i) {
            אם ((palette->colors[i].r != 0xFF) || (palette->colors[i].g != 0xFF) || (palette->colors[i].b != 0xFF)) {
                اكسر;
            }
        }
        אם (i == palette->ncolors) {
            SDL_SetError("Empty destination palette");
            اذهب error;
        }
    } אחרת אם (SDL_ISPIXELFORMAT_INDEXED(format)) {
        // Create a dither palette for conversion
        temp_palette = SDL_CreatePalette(1 << SDL_BITSPERPIXEL(format));
        אם (temp_palette) {
            SDL_DitherPalette(temp_palette);
            palette = temp_palette;
        }
    }

    src_colorspace = surface->colorspace;
    src_properties = surface->props;

    // Create a new surface with the desired format
    אם (surface->pixels || SDL_MUSTLOCK(surface)) {
        convert = SDL_CreateSurfaceUninitialized(rect->w, rect->h, format);
    } אחרת {
        convert = SDL_CreateSurfaceFrom(rect->w, rect->h, format, عدم, 0);
    }
    אם (!convert) {
        اذهب error;
    }
    אם (SDL_ISPIXELFORMAT_INDEXED(format)) {
        SDL_SetSurfacePalette(convert, palette);
    }

    אם (colorspace == SDL_COLORSPACE_UNKNOWN) {
        colorspace = src_colorspace;
    }
    SDL_SetSurfaceColorspace(convert, colorspace);

    אם (SDL_ISPIXELFORMAT_FOURCC(format) || SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        אם (surface->format == SDL_PIXELFORMAT_MJPG && format == SDL_PIXELFORMAT_MJPG) {
            // Just do a straight pixel copy of the JPEG image
            size_t size = (size_t)surface->pitch;
            convert->pixels = SDL_malloc(size);
            אם (!convert->pixels) {
                اذهب error;
            }
            convert->flags &= ~SDL_SURFACE_PREALLOCATED;
            convert->pitch = surface->pitch;
            SDL_memcpy(convert->pixels, surface->pixels, size);

        } אחרת אם (!SDL_ConvertPixelsAndColorspace(surface->w, surface->h, surface->format, src_colorspace, src_properties, surface->pixels, surface->pitch, convert->format, colorspace, props, convert->pixels, convert->pitch)) {
            اذهب error;
        }

        // Save the original copy flags
        copy_flags = surface->map.info.flags;

        اذهب end;
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
    אם (surface->palette && SDL_ISPIXELFORMAT_ALPHA(format)) {
        bool set_opaque = false;

        bool is_opaque, has_alpha_channel;
        SDL_DetectPalette(surface->palette, &is_opaque, &has_alpha_channel);

        אם (is_opaque) {
            אם (!has_alpha_channel) {
                set_opaque = true;
            }
        }

        // Set opaque and backup palette alpha values
        אם (set_opaque) {
            صحيح i;
            palette_saved_alpha_ncolors = surface->palette->ncolors;
            אם (palette_saved_alpha_ncolors > 0) {
                palette_saved_alpha = SDL_stack_alloc(Uint8, palette_saved_alpha_ncolors);
                עבור (i = 0; i < palette_saved_alpha_ncolors; i++) {
                    palette_saved_alpha[i] = surface->palette->colors[i].a;
                    surface->palette->colors[i].a = SDL_ALPHA_OPAQUE;
                }
            }
        }
    }

    // Transform colorkey to alpha. for cases where source palette has duplicate values, and colorkey is one of them
    אם (copy_flags & SDL_COPY_COLORKEY) {
        אם (surface->palette && !palette) {
            palette_ck_transform = true;
            palette_ck_value = surface->palette->colors[surface->map.info.colorkey].a;
            surface->palette->colors[surface->map.info.colorkey].a = SDL_ALPHA_TRANSPARENT;
        }
    }

    אם (surface->pixels || SDL_MUSTLOCK(surface)) {
        result = SDL_BlitSurfaceUnchecked(surface, rect, convert, &bounds);
    } אחרת {
        result = true;
    }

    // Restore colorkey alpha value
    אם (palette_ck_transform) {
        surface->palette->colors[surface->map.info.colorkey].a = palette_ck_value;
    }

    // Restore palette alpha values
    אם (palette_saved_alpha) {
        صحيح i;
        עבור (i = 0; i < palette_saved_alpha_ncolors; i++) {
            surface->palette->colors[i].a = palette_saved_alpha[i];
        }
        SDL_stack_free(palette_saved_alpha);
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
    אם (!result) {
        اذهب error;
    }

    אם (copy_flags & SDL_COPY_COLORKEY) {
        bool set_colorkey_by_color = false;
        bool convert_colorkey = true;

        אם (surface->palette) {
            אם (palette &&
                surface->palette->ncolors <= palette->ncolors &&
                (SDL_memcmp(surface->palette->colors, palette->colors,
                            surface->palette->ncolors * حجم(SDL_Color)) == 0)) {
                // The palette is identical, just set the same colorkey
                SDL_SetSurfaceColorKey(convert, true, surface->map.info.colorkey);
            } אחרת אם (!palette) {
                אם (SDL_ISPIXELFORMAT_ALPHA(format)) {
                    // No need to add the colorkey, transparency is in the alpha channel
                } אחרת {
                    // Only set the colorkey information
                    set_colorkey_by_color = true;
                    convert_colorkey = false;
                }
            } אחרת {
                set_colorkey_by_color = true;
            }
        } אחרת {
            set_colorkey_by_color = true;
        }

        אם (set_colorkey_by_color) {
            SDL_Surface *tmp;
            SDL_Surface *tmp2;
            صحيح converted_colorkey = 0;

            // Create a dummy surface to get the colorkey converted
            tmp = SDL_CreateSurfaceUninitialized(1, 1, surface->format);
            אם (!tmp) {
                اذهب error;
            }

            // Share the palette, if any
            אם (surface->palette) {
                SDL_SetSurfacePalette(tmp, surface->palette);
            }

            SDL_FillSurfaceRect(tmp, عدم, surface->map.info.colorkey);

            tmp->map.info.flags &= ~SDL_COPY_COLORKEY;

            // Conversion of the colorkey
            tmp2 = SDL_ConvertSurfaceAndColorspace(tmp, format, palette, colorspace, props);
            אם (!tmp2) {
                SDL_DestroySurface(tmp);
                اذهب error;
            }

            // Get the converted colorkey
            SDL_memcpy(&converted_colorkey, tmp2->pixels, tmp2->fmt->bytes_per_pixel);

            SDL_DestroySurface(tmp);
            SDL_DestroySurface(tmp2);

            // Set the converted colorkey on the new surface
            SDL_SetSurfaceColorKey(convert, true, converted_colorkey);

            // This is needed when converting for 3D texture upload
            אם (convert_colorkey) {
                SDL_ConvertColorkeyToAlpha(convert, true);
            }
        }
    }

end:
    אם (temp_palette) {
        SDL_DestroyPalette(temp_palette);
    }

    SDL_SetSurfaceClipRect(convert, &surface->clip_rect);

    /* Enable alpha blending by default if the new surface has an
     * alpha channel or alpha modulation */
    אם (SDL_ISPIXELFORMAT_ALPHA(format) ||
        (copy_flags & SDL_COPY_MODULATE_ALPHA)) {
        SDL_SetSurfaceBlendMode(convert, SDL_BLENDMODE_BLEND);
    }
    אם (copy_flags & SDL_COPY_RLE_DESIRED) {
        SDL_SetSurfaceRLE(convert, true);
    }

    // Copy alternate images
    עבור (صحيح i = 0; i < surface->num_images; ++i) {
        אם (!SDL_AddSurfaceAlternateImage(convert, surface->images[i])) {
            اذهب error;
        }
    }

    // Copy properties
    אם (surface->props) {
        אם (!SDL_CopyProperties(surface->props, SDL_GetSurfaceProperties(convert))) {
            اذهب error;
        }

        // Make sure the new surface doesn't reference an old SDL2 surface.
        SDL_ClearProperty(SDL_GetSurfaceProperties(convert), "sdl2-compat.surface2");
    }

    // We're ready to go!
    החזר convert;

error:
    אם (temp_palette) {
        SDL_DestroyPalette(temp_palette);
    }
    אם (convert) {
        SDL_DestroySurface(convert);
    }
    החזר عدم;
}

SDL_Surface *SDL_ConvertSurfaceAndColorspace(SDL_Surface *surface, SDL_PixelFormat format, SDL_Palette *palette, SDL_Colorspace colorspace, SDL_PropertiesID props)
{
    החזר SDL_ConvertSurfaceRectAndColorspace(surface, عدم, format, palette, colorspace, props);
}

SDL_Surface *SDL_RotateSurface(SDL_Surface *surface, عائم angle)
{
    SDL_Surface *rotated = عدم;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        החזר عدم;
    }

    SDL_Rect rect_dest;
    مزدوج cangle, sangle;
    SDL_FPoint center = { surface->w * 0.5f, surface->h * 0.5f };
    SDLgfx_rotozoomSurfaceSizeTrig(surface->w, surface->h, angle, &center, &rect_dest, &cangle, &sangle);

    // This function requires a 32-bit surface or 8-bit surface with a colorkey
    אם ((SDL_BITSPERPIXEL(surface->format) == 32 && SDL_PIXELLAYOUT(surface->format) == SDL_PACKEDLAYOUT_8888) ||
        (surface->format == SDL_PIXELFORMAT_INDEX8 && SDL_SurfaceHasColorKey(surface))) {
        rotated = SDLgfx_rotateSurface(surface, angle, 1, 0, 0, &rect_dest, cangle, sangle, &center);
    } אחרת {
        SDL_Surface *convert = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);
        אם (convert) {
            SDL_Surface *tmp = SDLgfx_rotateSurface(convert, angle, 1, 0, 0, &rect_dest, cangle, sangle, &center);
            אם (tmp) {
                rotated = SDL_ConvertSurfaceAndColorspace(tmp, surface->format, surface->palette, surface->colorspace, surface->props);
                SDL_DestroySurface(tmp);
            }
            SDL_DestroySurface(convert);
        }
    }

    אם (rotated) {
        אם (SDL_HasProperty(surface->props, SDL_PROP_SURFACE_ROTATION_FLOAT)) {
            ثابت عائم rotation = (SDL_GetNumberProperty(surface->props, SDL_PROP_SURFACE_ROTATION_FLOAT, 0) - angle);
            SDL_SetFloatProperty(SDL_GetSurfaceProperties(rotated), SDL_PROP_SURFACE_ROTATION_FLOAT, rotation);
        }
    }

    החזר rotated;
}

SDL_Surface *SDL_DuplicateSurface(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        החזר عدم;
    }

    החזר SDL_ConvertSurfaceAndColorspace(surface, surface->format, surface->palette, surface->colorspace, surface->props);
}

SDL_Surface *SDL_ScaleSurface(SDL_Surface *surface, صحيح width, صحيح height, SDL_ScaleMode scaleMode)
{
    SDL_Surface *convert = عدم;
    Uint32 copy_flags;
    SDL_Color copy_color;
    bool rc;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        اذهب error;
    }

    אם (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // We can't directly scale a YUV surface (yet!)
        SDL_Surface *tmp = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        אם (!tmp) {
            החזר عدم;
        }

        SDL_Surface *scaled = SDL_ScaleSurface(tmp, width, height, scaleMode);
        SDL_DestroySurface(tmp);
        אם (!scaled) {
            החזר عدم;
        }

        SDL_Surface *result = SDL_ConvertSurfaceAndColorspace(scaled, surface->format, عدم, surface->colorspace, surface->props);
        SDL_DestroySurface(scaled);
        החזר result;
    }

    אם (SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        // Linear scaling requires conversion to RGBA and then slow pixel color lookup
        scaleMode = SDL_SCALEMODE_NEAREST;
    }

    // Create a new surface with the desired size
    אם (surface->pixels || SDL_MUSTLOCK(surface)) {
        convert = SDL_CreateSurfaceUninitialized(width, height, surface->format);
    } אחרת {
        convert = SDL_CreateSurfaceFrom(width, height, surface->format, عدم, 0);
    }
    אם (!convert) {
        اذهب error;
    }
    SDL_SetSurfacePalette(convert, surface->palette);
    SDL_SetSurfaceColorspace(convert, surface->colorspace);
    SDL_SetSurfaceRLE(convert, SDL_SurfaceHasRLE(surface));

    אם (surface->pixels || SDL_MUSTLOCK(surface)) {
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

        rc = SDL_BlitSurfaceScaled(surface, عدم, convert, عدم, scaleMode);

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
    } אחרת {
        rc = true;
    }

    // SDL_BlitSurfaceScaled failed, and so the conversion
    אם (!rc) {
        اذهب error;
    }

    // We're ready to go!
    החזר convert;

error:
    אם (convert) {
        SDL_DestroySurface(convert);
    }
    החזר عدم;
}

SDL_Surface *SDL_ConvertSurfaceRect(SDL_Surface *surface, ثابت SDL_Rect *rect, SDL_PixelFormat format)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        החזר عدم;
    }

    החזר SDL_ConvertSurfaceRectAndColorspace(surface, rect, format, عدم, SDL_GetDefaultColorspaceForFormat(format), surface->props);
}

SDL_Surface *SDL_ConvertSurface(SDL_Surface *surface, SDL_PixelFormat format)
{
    החזר SDL_ConvertSurfaceRect(surface, عدم, format);
}

SDL_Surface *SDL_DuplicatePixels(صحيح width, صحيح height, SDL_PixelFormat format, SDL_Colorspace colorspace, فراغ *pixels, صحيح pitch)
{
    SDL_Surface *surface;
    אם (pixels) {
        surface = SDL_CreateSurfaceUninitialized(width, height, format);
    } אחרת {
        surface = SDL_CreateSurfaceFrom(width, height, format, عدم, 0);
    }
    אם (!surface) {
        החזר عدم;
    }
    SDL_SetSurfaceColorspace(surface, colorspace);

    אם (surface->pixels) {
        صحيح length = width * SDL_BYTESPERPIXEL(format);
        Uint8 *src = (Uint8 *)pixels;
        Uint8 *dst = (Uint8 *)surface->pixels;
        صحيح rows = height;
        כלעוד (rows--) {
            SDL_memcpy(dst, src, length);
            dst += surface->pitch;
            src += pitch;
        }
    }
    החזר surface;
}

bool SDL_ConvertPixelsAndColorspace(صحيح width, صحيح height,
                      SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ثابت فراغ *src, صحيح src_pitch,
                      SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, فراغ *dst, صحيح dst_pitch)
{
    SDL_Surface src_surface;
    SDL_Surface dst_surface;
    SDL_Rect rect;
    فراغ *nonconst_src = (فراغ *)src;
    bool result;

    CHECK_PARAM(!src) {
        החזר SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!src_pitch) {
        החזר SDL_InvalidParamError("src_pitch");
    }
    CHECK_PARAM(!dst) {
        החזר SDL_InvalidParamError("dst");
    }
    CHECK_PARAM(!dst_pitch) {
        החזר SDL_InvalidParamError("dst_pitch");
    }

    אם (src_colorspace == SDL_COLORSPACE_UNKNOWN) {
        src_colorspace = SDL_GetDefaultColorspaceForFormat(src_format);
    }
    אם (dst_colorspace == SDL_COLORSPACE_UNKNOWN) {
        dst_colorspace = SDL_GetDefaultColorspaceForFormat(dst_format);
    }

    אם (src_format == SDL_PIXELFORMAT_MJPG) {
        החזר SDL_ConvertPixels_STB(width, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    }

#ifdef SDL_HAVE_YUV
    אם (SDL_ISPIXELFORMAT_FOURCC(src_format) && SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        החזר SDL_ConvertPixels_YUV_to_YUV(width, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } אחרת אם (SDL_ISPIXELFORMAT_FOURCC(src_format)) {
        החזר SDL_ConvertPixels_YUV_to_RGB(width, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } אחרת אם (SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        החזר SDL_ConvertPixels_RGB_to_YUV(width, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    }
#אחרת
    אם (SDL_ISPIXELFORMAT_FOURCC(src_format) || SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        החזר SDL_SetError("SDL not built with YUV support");
    }
#endif

    // Fast path for same format copy
    אם (src_format == dst_format && src_colorspace == dst_colorspace) {
        אם (src_pitch == dst_pitch) {
            SDL_memcpy(dst, src, height * src_pitch);
        } אחרת {
            صحيح i;
            ثابت صحيح bpp = SDL_BYTESPERPIXEL(src_format);
            width *= bpp;
            עבור (i = height; i--;) {
                SDL_memcpy(dst, src, width);
                src = (ثابت Uint8 *)src + src_pitch;
                dst = (Uint8 *)dst + dst_pitch;
            }
        }
        החזר true;
    }

    אם (!SDL_InitializeSurface(&src_surface, width, height, src_format, src_colorspace, src_properties, nonconst_src, src_pitch, true)) {
        החזר false;
    }
    SDL_SetSurfaceBlendMode(&src_surface, SDL_BLENDMODE_NONE);

    אם (!SDL_InitializeSurface(&dst_surface, width, height, dst_format, dst_colorspace, dst_properties, dst, dst_pitch, true)) {
        החזר false;
    }

    // Set up the rect and go!
    rect.x = 0;
    rect.y = 0;
    rect.w = width;
    rect.h = height;
    result = SDL_BlitSurfaceUnchecked(&src_surface, &rect, &dst_surface, &rect);

    SDL_DestroySurface(&src_surface);
    SDL_DestroySurface(&dst_surface);

    החזר result;
}

bool SDL_ConvertPixels(صحيح width, صحيح height, SDL_PixelFormat src_format, ثابت فراغ *src, صحيح src_pitch, SDL_PixelFormat dst_format, فراغ *dst, صحيح dst_pitch)
{
    החזר SDL_ConvertPixelsAndColorspace(width, height,
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

ساكن فراغ SDL_PremultiplyAlpha_AXYZ8888(صحيح width, صحيح height, ثابت فراغ *src, صحيح src_pitch, فراغ *dst, صحيح dst_pitch)
{
    صحيح c;
    Uint32 srcpixel;
    Uint32 srcR, srcG, srcB, srcA;
    Uint32 dstpixel;
    Uint32 dstR, dstG, dstB, dstA;

    כלעוד (height--) {
        ثابت Uint32 *src_px = (ثابت Uint32 *)src;
        Uint32 *dst_px = (Uint32 *)dst;
        עבור (c = width; c; --c) {
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

ساكن فراغ SDL_PremultiplyAlpha_XYZA8888(صحيح width, صحيح height, ثابت فراغ *src, صحيح src_pitch, فراغ *dst, صحيح dst_pitch)
{
    صحيح c;
    Uint32 srcpixel;
    Uint32 srcR, srcG, srcB, srcA;
    Uint32 dstpixel;
    Uint32 dstR, dstG, dstB, dstA;

    כלעוד (height--) {
        ثابت Uint32 *src_px = (ثابت Uint32 *)src;
        Uint32 *dst_px = (Uint32 *)dst;
        עבור (c = width; c; --c) {
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

ساكن فراغ SDL_PremultiplyAlpha_AXYZ128(صحيح width, صحيح height, ثابت فراغ *src, صحيح src_pitch, فراغ *dst, صحيح dst_pitch)
{
    صحيح c;
    عائم flR, flG, flB, flA;

    כלעוד (height--) {
        ثابت عائم *src_px = (ثابت عائم *)src;
        عائم *dst_px = (عائم *)dst;
        עבור (c = width; c; --c) {
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

ساكن bool SDL_PremultiplyAlphaPixelsAndColorspace(صحيح width, صحيح height, SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ثابت فراغ *src, صحيح src_pitch, SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, فراغ *dst, صحيح dst_pitch, bool linear)
{
    SDL_Surface *convert = عدم;
    فراغ *final_dst = dst;
    صحيح final_dst_pitch = dst_pitch;
    SDL_PixelFormat format;
    SDL_Colorspace colorspace;
    bool result = false;

    CHECK_PARAM(!src) {
        החזר SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!src_pitch) {
        החזר SDL_InvalidParamError("src_pitch");
    }
    CHECK_PARAM(!dst) {
        החזר SDL_InvalidParamError("dst");
    }
    CHECK_PARAM(!dst_pitch) {
        החזר SDL_InvalidParamError("dst_pitch");
    }

    // Use a high precision format if we're converting to linear colorspace or using high precision pixel formats
    אם (linear ||
        SDL_ISPIXELFORMAT_10BIT(src_format) || SDL_BITSPERPIXEL(src_format) > 32 ||
        SDL_ISPIXELFORMAT_10BIT(dst_format) || SDL_BITSPERPIXEL(dst_format) > 32) {
        אם (src_format == SDL_PIXELFORMAT_ARGB128_FLOAT ||
            src_format == SDL_PIXELFORMAT_ABGR128_FLOAT) {
            format = src_format;
        } אחרת {
            format = SDL_PIXELFORMAT_ARGB128_FLOAT;
        }
    } אחרת {
        אם (src_format == SDL_PIXELFORMAT_ARGB8888 ||
            src_format == SDL_PIXELFORMAT_ABGR8888 ||
            src_format == SDL_PIXELFORMAT_RGBA8888 ||
            src_format == SDL_PIXELFORMAT_BGRA8888) {
            format = src_format;
        } אחרת {
            format = SDL_PIXELFORMAT_ARGB8888;
        }
    }
    אם (linear) {
        colorspace = SDL_COLORSPACE_SRGB_LINEAR;
    } אחרת {
        colorspace = SDL_COLORSPACE_SRGB;
    }

    אם (src_format != format || src_colorspace != colorspace) {
        convert = SDL_CreateSurfaceUninitialized(width, height, format);
        אם (!convert) {
            اذهب done;
        }
        אם (!SDL_ConvertPixelsAndColorspace(width, height, src_format, src_colorspace, src_properties, src, src_pitch, format, colorspace, 0, convert->pixels, convert->pitch)) {
            اذهب done;
        }

        src = convert->pixels;
        src_pitch = convert->pitch;
        dst = convert->pixels;
        dst_pitch = convert->pitch;

    } אחרת אם (dst_format != format || dst_colorspace != colorspace) {
        convert = SDL_CreateSurfaceUninitialized(width, height, format);
        אם (!convert) {
            اذهب done;
        }
        dst = convert->pixels;
        dst_pitch = convert->pitch;
    }

    بدل (format) {
    حالة SDL_PIXELFORMAT_ARGB8888:
    حالة SDL_PIXELFORMAT_ABGR8888:
        SDL_PremultiplyAlpha_AXYZ8888(width, height, src, src_pitch, dst, dst_pitch);
        اكسر;
    حالة SDL_PIXELFORMAT_RGBA8888:
    حالة SDL_PIXELFORMAT_BGRA8888:
        SDL_PremultiplyAlpha_XYZA8888(width, height, src, src_pitch, dst, dst_pitch);
        اكسر;
    حالة SDL_PIXELFORMAT_ARGB128_FLOAT:
    حالة SDL_PIXELFORMAT_ABGR128_FLOAT:
        SDL_PremultiplyAlpha_AXYZ128(width, height, src, src_pitch, dst, dst_pitch);
        اكسر;
    افتراضي:
        SDL_SetError("Unexpected internal pixel format");
        اذهب done;
    }

    אם (dst != final_dst) {
        אם (!SDL_ConvertPixelsAndColorspace(width, height, format, colorspace, 0, convert->pixels, convert->pitch, dst_format, dst_colorspace, dst_properties, final_dst, final_dst_pitch)) {
            اذهب done;
        }
    }
    result = true;

done:
    אם (convert) {
        SDL_DestroySurface(convert);
    }
    החזר result;
}

bool SDL_PremultiplyAlpha(صحيح width, صحيح height,
                         SDL_PixelFormat src_format, ثابت فراغ *src, صحيح src_pitch,
                         SDL_PixelFormat dst_format, فراغ *dst, صحيح dst_pitch, bool linear)
{
    SDL_Colorspace src_colorspace = SDL_GetDefaultColorspaceForFormat(src_format);
    SDL_Colorspace dst_colorspace = SDL_GetDefaultColorspaceForFormat(dst_format);

    החזר SDL_PremultiplyAlphaPixelsAndColorspace(width, height, src_format, src_colorspace, 0, src, src_pitch, dst_format, dst_colorspace, 0, dst, dst_pitch, linear);
}

bool SDL_PremultiplySurfaceAlpha(SDL_Surface *surface, bool linear)
{
    SDL_Colorspace colorspace;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        החזר SDL_InvalidParamError("surface");
    }

    colorspace = surface->colorspace;

    החזר SDL_PremultiplyAlphaPixelsAndColorspace(surface->w, surface->h, surface->format, colorspace, surface->props, surface->pixels, surface->pitch, surface->format, colorspace, surface->props, surface->pixels, surface->pitch, linear);
}

bool SDL_ClearSurface(SDL_Surface *surface, عائم r, عائم g, عائم b, عائم a)
{
    SDL_Rect clip_rect;
    bool result = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        החזר SDL_InvalidParamError("surface");
    }

    SDL_GetSurfaceClipRect(surface, &clip_rect);
    SDL_SetSurfaceClipRect(surface, عدم);

    אם (!SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_BYTESPERPIXEL(surface->format) <= حجم(Uint32)) {
        Uint32 color;

        color = SDL_MapSurfaceRGBA(surface,
                    (Uint8)SDL_roundf(SDL_clamp(r, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(g, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(b, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(a, 0.0f, 1.0f) * 255.0f));
        result = SDL_FillSurfaceRect(surface, عدم, color);
    } אחרת אם (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // We can't directly set an RGB value on a YUV surface
        SDL_Surface *tmp = SDL_CreateSurfaceUninitialized(surface->w, surface->h, SDL_PIXELFORMAT_ARGB8888);
        אם (!tmp) {
            اذهب done;
        }

        אם (SDL_ClearSurface(tmp, r, g, b, a)) {
            result = SDL_ConvertPixelsAndColorspace(surface->w, surface->h, tmp->format, tmp->colorspace, tmp->props, tmp->pixels, tmp->pitch, surface->format, surface->colorspace, surface->props, surface->pixels, surface->pitch);
        }
        SDL_DestroySurface(tmp);
    } אחרת {
        // Take advantage of blit color conversion
        SDL_Surface *tmp = SDL_CreateSurfaceUninitialized(1, 1, SDL_PIXELFORMAT_RGBA128_FLOAT);
        אם (!tmp) {
            اذهب done;
        }
        SDL_SetSurfaceColorspace(tmp, surface->colorspace);
        SDL_SetSurfaceBlendMode(tmp, SDL_BLENDMODE_NONE);

        عائم *pixels = (عائم *)tmp->pixels;
        pixels[0] = r;
        pixels[1] = g;
        pixels[2] = b;
        pixels[3] = a;

        result = SDL_BlitSurfaceScaled(tmp, عدم, surface, عدم, SDL_SCALEMODE_NEAREST);
        SDL_DestroySurface(tmp);
    }

done:
    SDL_SetSurfaceClipRect(surface, &clip_rect);

    החזר result;
}

Uint32 SDL_MapSurfaceRGB(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b)
{
    החזר SDL_MapSurfaceRGBA(surface, r, g, b, SDL_ALPHA_OPAQUE);
}

Uint32 SDL_MapSurfaceRGBA(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        החזר true;
    }
    החזר SDL_MapRGBA(surface->fmt, surface->palette, r, g, b, a);
}

// This function Copyright 2023 Collabora Ltd., contributed to SDL under the ZLib license
bool SDL_ReadSurfacePixel(SDL_Surface *surface, صحيح x, صحيح y, Uint8 *r, Uint8 *g, Uint8 *b, Uint8 *a)
{
    Uint32 pixel = 0;
    size_t bytes_per_pixel;
    Uint8 unused;
    Uint8 *p;
    bool result = false;

    אם (r) {
        *r = 0;
    } אחרת {
        r = &unused;
    }

    אם (g) {
        *g = 0;
    } אחרת {
        g = &unused;
    }

    אם (b) {
        *b = 0;
    } אחרת {
        b = &unused;
    }

    אם (a) {
        *a = 0;
    } אחרת {
        a = &unused;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        החזר SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        החזר SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        החזר SDL_InvalidParamError("y");
    }

    bytes_per_pixel = SDL_BYTESPERPIXEL(surface->format);

    אם (SDL_MUSTLOCK(surface)) {
        אם (!SDL_LockSurface(surface)) {
            החזר false;
        }
    }

    p = (Uint8 *)surface->pixels + y * surface->pitch + x * bytes_per_pixel;

    אם (bytes_per_pixel <= حجم(pixel) &&
        !SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_COLORSPACEPRIMARIES(surface->colorspace) == SDL_COLOR_PRIMARIES_BT709) {
        /* Fill the appropriate number of least-significant bytes of pixel,
         * leaving the most-significant bytes set to zero */
#אם SDL_BYTEORDER == SDL_BIG_ENDIAN
        SDL_memcpy(((Uint8 *)&pixel) + (حجم(pixel) - bytes_per_pixel), p, bytes_per_pixel);
#אחרת
        SDL_memcpy(&pixel, p, bytes_per_pixel);
#endif
        SDL_GetRGBA(pixel, surface->fmt, surface->palette, r, g, b, a);
        result = true;
    } אחרת אם (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // FIXME: We need code to extract a single macroblock from a YUV surface
        SDL_Surface *converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        אם (converted) {
            result = SDL_ReadSurfacePixel(converted, x, y, r, g, b, a);
            SDL_DestroySurface(converted);
        }
    } אחרת {
        // This is really slow, but it gets the job done
        Uint8 rgba[4];

        אם (SDL_ConvertPixelsAndColorspace(1, 1, surface->format, surface->colorspace, surface->props, p, surface->pitch, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, rgba, حجم(rgba))) {
            *r = rgba[0];
            *g = rgba[1];
            *b = rgba[2];
            *a = rgba[3];
            result = true;
        }
    }

    אם (SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }
    החזר result;
}

bool SDL_ReadSurfacePixelFloat(SDL_Surface *surface, صحيح x, صحيح y, عائم *r, عائم *g, عائم *b, عائم *a)
{
    عائم unused;
    bool result = false;

    אם (r) {
        *r = 0.0f;
    } אחרת {
        r = &unused;
    }

    אם (g) {
        *g = 0.0f;
    } אחרת {
        g = &unused;
    }

    אם (b) {
        *b = 0.0f;
    } אחרת {
        b = &unused;
    }

    אם (a) {
        *a = 0.0f;
    } אחרת {
        a = &unused;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        החזר SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        החזר SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        החזר SDL_InvalidParamError("y");
    }

    אם (SDL_BYTESPERPIXEL(surface->format) <= حجم(Uint32) &&
        !SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_COLORSPACEPRIMARIES(surface->colorspace) == SDL_COLOR_PRIMARIES_BT709) {
        Uint8 r8, g8, b8, a8;

        אם (SDL_ReadSurfacePixel(surface, x, y, &r8, &g8, &b8, &a8)) {
            *r = (عائم)r8 / 255.0f;
            *g = (عائم)g8 / 255.0f;
            *b = (عائم)b8 / 255.0f;
            *a = (عائم)a8 / 255.0f;
            result = true;
        }
    } אחרת אם (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // FIXME: We need code to extract a single macroblock from a YUV surface
        SDL_Surface *converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        אם (converted) {
            result = SDL_ReadSurfacePixelFloat(converted, x, y, r, g, b, a);
            SDL_DestroySurface(converted);
        }
    } אחרת {
        // This is really slow, but it gets the job done
        عائم rgba[4];
        Uint8 *p;

        אם (SDL_MUSTLOCK(surface)) {
            אם (!SDL_LockSurface(surface)) {
                החזר false;
            }
        }

        p = (Uint8 *)surface->pixels + y * surface->pitch + x * SDL_BYTESPERPIXEL(surface->format);

        אם (surface->format == SDL_PIXELFORMAT_RGBA128_FLOAT) {
            SDL_memcpy(rgba, p, حجم(rgba));
            result = true;
        } אחרת {
            SDL_Colorspace src_colorspace = surface->colorspace;
            SDL_Colorspace dst_colorspace = (src_colorspace == SDL_COLORSPACE_SRGB_LINEAR ? SDL_COLORSPACE_SRGB_LINEAR : SDL_COLORSPACE_SRGB);

            אם (SDL_ConvertPixelsAndColorspace(1, 1, surface->format, src_colorspace, surface->props, p, surface->pitch, SDL_PIXELFORMAT_RGBA128_FLOAT, dst_colorspace, 0, rgba, حجم(rgba))) {
                result = true;
            }
        }

        אם (result) {
            *r = rgba[0];
            *g = rgba[1];
            *b = rgba[2];
            *a = rgba[3];
        }

        אם (SDL_MUSTLOCK(surface)) {
            SDL_UnlockSurface(surface);
        }
    }
    החזר result;
}

bool SDL_WriteSurfacePixel(SDL_Surface *surface, صحيح x, صحيح y, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    Uint32 pixel = 0;
    size_t bytes_per_pixel;
    Uint8 *p;
    bool result = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        החזר SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        החזר SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        החזר SDL_InvalidParamError("y");
    }

    bytes_per_pixel = SDL_BYTESPERPIXEL(surface->format);

    אם (SDL_MUSTLOCK(surface)) {
        אם (!SDL_LockSurface(surface)) {
            החזר false;
        }
    }

    p = (Uint8 *)surface->pixels + y * surface->pitch + x * bytes_per_pixel;

    אם (bytes_per_pixel <= حجم(pixel) && !SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        pixel = SDL_MapRGBA(surface->fmt, surface->palette, r, g, b, a);
#אם SDL_BYTEORDER == SDL_BIG_ENDIAN
        SDL_memcpy(p, ((Uint8 *)&pixel) + (حجم(pixel) - bytes_per_pixel), bytes_per_pixel);
#אחרת
        SDL_memcpy(p, &pixel, bytes_per_pixel);
#endif
        result = true;
    } אחרת אם (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        result = SDL_Unsupported();
    } אחרת {
        // This is really slow, but it gets the job done
        Uint8 rgba[4];

        rgba[0] = r;
        rgba[1] = g;
        rgba[2] = b;
        rgba[3] = a;
        result = SDL_ConvertPixelsAndColorspace(1, 1, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, rgba, حجم(rgba), surface->format, surface->colorspace, surface->props, p, surface->pitch);
    }

    אם (SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }
    החזר result;
}

bool SDL_WriteSurfacePixelFloat(SDL_Surface *surface, صحيح x, صحيح y, عائم r, عائم g, عائم b, عائم a)
{
    bool result = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        החזר SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        החזר SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        החזר SDL_InvalidParamError("y");
    }

    אם (SDL_BYTESPERPIXEL(surface->format) <= حجم(Uint32) && !SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        Uint8 r8, g8, b8, a8;

        r8 = (Uint8)SDL_round(SDL_clamp(r, 0.0f, 1.0f) * 255.0f);
        g8 = (Uint8)SDL_round(SDL_clamp(g, 0.0f, 1.0f) * 255.0f);
        b8 = (Uint8)SDL_round(SDL_clamp(b, 0.0f, 1.0f) * 255.0f);
        a8 = (Uint8)SDL_round(SDL_clamp(a, 0.0f, 1.0f) * 255.0f);
        אם (SDL_WriteSurfacePixel(surface, x, y, r8, g8, b8, a8)) {
            result = true;
        }
    } אחרת אם (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        result = SDL_Unsupported();
    } אחרת {
        // This is really slow, but it gets the job done
        عائم rgba[4];
        Uint8 *p;

        אם (SDL_MUSTLOCK(surface)) {
            אם (!SDL_LockSurface(surface)) {
                החזר false;
            }
        }

        p = (Uint8 *)surface->pixels + y * surface->pitch + x * SDL_BYTESPERPIXEL(surface->format);

        rgba[0] = r;
        rgba[1] = g;
        rgba[2] = b;
        rgba[3] = a;

        אם (surface->format == SDL_PIXELFORMAT_RGBA128_FLOAT) {
            SDL_memcpy(p, rgba, حجم(rgba));
            result = true;
        } אחרת {
            SDL_Colorspace dst_colorspace = surface->colorspace;
            SDL_Colorspace src_colorspace = (dst_colorspace == SDL_COLORSPACE_SRGB_LINEAR ? SDL_COLORSPACE_SRGB_LINEAR : SDL_COLORSPACE_SRGB);

            result = SDL_ConvertPixelsAndColorspace(1, 1, SDL_PIXELFORMAT_RGBA128_FLOAT, src_colorspace, 0, rgba, حجم(rgba), surface->format, dst_colorspace, surface->props, p, surface->pitch);
        }

        אם (SDL_MUSTLOCK(surface)) {
            SDL_UnlockSurface(surface);
        }
    }
    החזר result;
}

/*
 * Free a surface created by the above function.
 */
فراغ SDL_DestroySurface(SDL_Surface *surface)
{
    אם (!SDL_SurfaceValid(surface)) {
        החזר;
    }
    אם (surface->internal_flags & SDL_INTERNAL_SURFACE_DONTFREE) {
        החזר;
    }
    אם (--surface->refcount > 0) {
        החזר;
    }

    SDL_RemoveSurfaceAlternateImages(surface);

    SDL_DestroyProperties(surface->props);

    SDL_InvalidateMap(&surface->map);

    כלעוד (surface->locked > 0) {
        SDL_UnlockSurface(surface);
    }
#ifdef SDL_HAVE_RLE
    אם (surface->internal_flags & SDL_INTERNAL_SURFACE_RLEACCEL) {
        SDL_UnRLESurface(surface);
    }
#endif
    SDL_SetSurfacePalette(surface, عدم);

    אם (surface->flags & SDL_SURFACE_PREALLOCATED) {
        // Don't free
    } אחרת אם (surface->flags & SDL_SURFACE_SIMD_ALIGNED) {
        // Free aligned
        SDL_aligned_free(surface->pixels);
    } אחרת {
        // Normal
        SDL_free(surface->pixels);
    }

    surface->reserved = عدم;

    אם (!(surface->internal_flags & SDL_INTERNAL_SURFACE_STACK)) {
        SDL_free(surface);
    }
}

SDL_Surface *SDL_LoadSurface_IO(SDL_IOStream *src, bool closeio)
{
    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        החזר عدم;
    }

    אם (SDL_IsBMP(src)) {
        החזר SDL_LoadBMP_IO(src, closeio);
    } אחרת אם (SDL_IsPNG(src)) {
        החזר SDL_LoadPNG_IO(src, closeio);
    } אחרת אם (SDL_IsJPG(src)) {
        החזר SDL_LoadJPG_IO(src, closeio);
    } אחרת {
        אם (closeio) {
            SDL_CloseIO(src);
        }
        SDL_SetError("Unsupported image format");
        החזר عدم;
    }
}

SDL_Surface *SDL_LoadSurface(ثابت حرف *file)
{
    SDL_IOStream *stream = SDL_IOFromFile(file, "rb");
    אם (!stream) {
        החזר عدم;
    }

    החזר SDL_LoadSurface_IO(stream, true);
}
