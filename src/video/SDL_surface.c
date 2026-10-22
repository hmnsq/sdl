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
#include "SDL_internal.h"

#include "SDL_sysvideo.h"
#include "SDL_video_c.h"
#include "SDL_RLEaccel_c.h"
#include "SDL_pixels_c.h"
#include "SDL_rotate.h"
#include "SDL_stb_c.h"
#include "SDL_yuv_c.h"
#include "../render/SDL_sysrender.h"

#include "SDL_surface_c.h"


// Check to make sure we can safely check multiplication of surface w and pitch and it won't overflow size_t
SDL_COMPILE_TIME_ASSERT(surface_size_assumptions,
                        parimaa_na(จำนวนเต็ม) == parimaa_na(Sint32) && parimaa_na(size_t) >= parimaa_na(Sint32));

SDL_COMPILE_TIME_ASSERT(can_indicate_overflow, SDL_SIZE_MAX > SDL_MAX_SINT32);

// Magic!
static var_na SDL_surface_magic;

// Public routines

bool SDL_SurfaceValid(SDL_Surface *surface)
{
    คืน (surface && surface->reserved == &SDL_surface_magic);
}

void SDL_UpdateSurfaceLockFlag(SDL_Surface *surface)
{
    // We need to mark the surface as needing unlock while locked
    ถ้า ((surface->flags & SDL_SURFACE_LOCKED) ||
        (surface->internal_flags & SDL_INTERNAL_SURFACE_RLEACCEL)) {
        surface->flags |= SDL_SURFACE_LOCK_NEEDED;
    } มิฉะนั้น {
        surface->flags &= ~SDL_SURFACE_LOCK_NEEDED;
    }
}

/*
 * Calculate the pad-aligned scanline width of a surface.
 *
 * for FOURCC, use SDL_CalculateYUVSize()
 */
static bool SDL_CalculateRGBSize(Uint32 format, size_t width, size_t height, size_t *size, size_t *pitch, bool minimal)
{
    ถ้า (SDL_BITSPERPIXEL(format) >= 8) {
        ถ้า (!SDL_size_mul_check_overflow(width, SDL_BYTESPERPIXEL(format), pitch)) {
            คืน SDL_SetError("width * bpp would overflow");
        }
    } มิฉะนั้น {
        ถ้า (!SDL_size_mul_check_overflow(width, SDL_BITSPERPIXEL(format), pitch)) {
            คืน SDL_SetError("width * bpp would overflow");
        }
        ถ้า (!SDL_size_add_check_overflow(*pitch, 7, pitch)) {
            คืน SDL_SetError("aligning pitch would overflow");
        }
        *pitch /= 8;
    }
    ถ้า (!minimal) {
        // 4-byte aligning for speed
        ถ้า (!SDL_size_add_check_overflow(*pitch, 3, pitch)) {
            คืน SDL_SetError("aligning pitch would overflow");
        }
        *pitch &= ~3;
    }

    ถ้า (!SDL_size_mul_check_overflow(height, *pitch, size)) {
        คืน SDL_SetError("height * pitch would overflow");
    }

    คืน true;
}

bool SDL_CalculateSurfaceSize(SDL_PixelFormat format, จำนวนเต็ม width, จำนวนเต็ม height, size_t *size, size_t *pitch, bool minimalPitch)
{
    size_t p = 0, sz = 0;

    ถ้า (size) {
        *size = 0;
    }

    ถ้า (pitch) {
        *pitch = 0;
    }

    ถ้า (SDL_ISPIXELFORMAT_FOURCC(format)) {
        ถ้า (format == SDL_PIXELFORMAT_MJPG) {
            // We don't know in advance what it will be, we'll figure it out later.
            คืน true;
        }

        ถ้า (!SDL_CalculateYUVSize(format, width, height, &sz, &p)) {
            // Overflow...
            คืน false;
        }
    } มิฉะนั้น {
        ถ้า (!SDL_CalculateRGBSize(format, width, height, &sz, &p, minimalPitch)) {
            // Overflow...
            คืน false;
        }
    }

    ถ้า (size) {
        *size = sz;
    }

    ถ้า (pitch) {
        *pitch = p;
    }

    คืน true;
}

static bool SDL_InitializeSurface(SDL_Surface *surface, จำนวนเต็ม width, จำนวนเต็ม height, SDL_PixelFormat format, SDL_Colorspace colorspace, SDL_PropertiesID props, void *pixels, จำนวนเต็ม pitch, bool onstack)
{
    SDL_zerop(surface);

    surface->flags = SDL_SURFACE_PREALLOCATED;
    surface->format = format;
    surface->w = width;
    surface->h = height;
    surface->pixels = pixels;
    surface->pitch = pitch;
    surface->reserved = &SDL_surface_magic;

    ถ้า (onstack) {
        surface->internal_flags |= SDL_INTERNAL_SURFACE_STACK;
    }

    surface->fmt = SDL_GetPixelFormatDetails(format);
    ถ้า (!surface->fmt) {
        SDL_DestroySurface(surface);
        คืน false;
    }

    // Initialize the clip rect
    surface->clip_rect.w = width;
    surface->clip_rect.h = height;

    // Allocate an empty mapping
    surface->map.info.r = 0xFF;
    surface->map.info.g = 0xFF;
    surface->map.info.b = 0xFF;
    surface->map.info.a = 0xFF;

    ถ้า (colorspace == SDL_COLORSPACE_UNKNOWN) {
        surface->colorspace = SDL_GetDefaultColorspaceForFormat(format);
    } มิฉะนั้น {
        surface->colorspace = colorspace;
    }

    ถ้า (props) {
        ถ้า (!SDL_CopyProperties(props, SDL_GetSurfaceProperties(surface))) {
            SDL_DestroySurface(surface);
            คืน false;
        }
    }

    // By default surfaces with an alpha mask are set up for blending
    ถ้า (SDL_ISPIXELFORMAT_ALPHA(surface->format)) {
        SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
    }

    // The surface is ready to go
    surface->refcount = 1;
    คืน true;
}

/*
 * Create an empty surface of the appropriate depth using the given format
 */
static SDL_Surface *SDL_CreateSurfaceInternal(จำนวนเต็ม width, จำนวนเต็ม height, SDL_PixelFormat format, bool clear_surface)
{
    size_t pitch, size;
    SDL_Surface *surface;

    CHECK_PARAM(width < 0) {
        SDL_InvalidParamError("width");
        คืน NULL;
    }

    CHECK_PARAM(height < 0) {
        SDL_InvalidParamError("height");
        คืน NULL;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        คืน NULL;
    }

    ถ้า (!SDL_CalculateSurfaceSize(format, width, height, &size, &pitch, false /* not minimal pitch */)) {
        // Overflow...
        คืน NULL;
    }

    // Allocate and initialize the surface
    surface = (SDL_Surface *)SDL_malloc(parimaa_na(*surface));
    ถ้า (!surface) {
        คืน NULL;
    }

    ถ้า (!SDL_InitializeSurface(surface, width, height, format, SDL_COLORSPACE_UNKNOWN, 0, NULL, (จำนวนเต็ม)pitch, false)) {
        คืน NULL;
    }

    ถ้า (surface->w && surface->h && format != SDL_PIXELFORMAT_MJPG) {
        surface->flags &= ~SDL_SURFACE_PREALLOCATED;
        ถ้า (SDL_GetHintBoolean("SDL_SURFACE_MALLOC", false)) {
            ถ้า (clear_surface) {
                surface->pixels = SDL_calloc(1, size);
            } มิฉะนั้น {
                surface->pixels = SDL_malloc(size);
            }
        } มิฉะนั้น {
            surface->flags |= SDL_SURFACE_SIMD_ALIGNED;
            ถ้า (clear_surface) {
                surface->pixels = SDL_aligned_alloc_zero(SDL_GetSIMDAlignment(), size);
            } มิฉะนั้น {
                surface->pixels = SDL_aligned_alloc(SDL_GetSIMDAlignment(), size);
            }
        }
        ถ้า (!surface->pixels) {
            SDL_DestroySurface(surface);
            คืน NULL;
        }
    }
    คืน surface;
}

SDL_Surface *SDL_CreateSurfaceZeroed(จำนวนเต็ม width, จำนวนเต็ม height, SDL_PixelFormat format)
{
    คืน SDL_CreateSurfaceInternal(width, height, format, true);
}

SDL_Surface *SDL_CreateSurfaceUninitialized(จำนวนเต็ม width, จำนวนเต็ม height, SDL_PixelFormat format)
{
    คืน SDL_CreateSurfaceInternal(width, height, format, false);
}

SDL_Surface *SDL_CreateSurface(จำนวนเต็ม width, จำนวนเต็ม height, SDL_PixelFormat format)
{
    คืน SDL_CreateSurfaceZeroed(width, height, format);
}


/*
 * Create an RGB surface from an existing memory buffer using the given
 * enum SDL_PIXELFORMAT_* format
 */
SDL_Surface *SDL_CreateSurfaceFrom(จำนวนเต็ม width, จำนวนเต็ม height, SDL_PixelFormat format, void *pixels, จำนวนเต็ม pitch)
{
    CHECK_PARAM(width < 0) {
        SDL_InvalidParamError("width");
        คืน NULL;
    }

    CHECK_PARAM(height < 0) {
        SDL_InvalidParamError("height");
        คืน NULL;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        คืน NULL;
    }

    ถ้า (pitch == 0 && !pixels) {
        // The application will fill these in later with valid values
    } มิฉะนั้น {
        size_t minimalPitch;

        ถ้า (!SDL_CalculateSurfaceSize(format, width, height, NULL, &minimalPitch, true /* minimal pitch */)) {
            // Overflow...
            คืน NULL;
        }

        CHECK_PARAM(pitch < 0 || (size_t)pitch < minimalPitch) {
            SDL_InvalidParamError("pitch");
            คืน NULL;
        }
    }

    // Allocate and initialize the surface
    SDL_Surface *surface = (SDL_Surface *)SDL_malloc(parimaa_na(*surface));
    ถ้า (!surface ||
        !SDL_InitializeSurface(surface, width, height, format, SDL_COLORSPACE_UNKNOWN, 0, pixels, pitch, false)) {
        คืน NULL;
    }
    คืน surface;
}

SDL_PropertiesID SDL_GetSurfaceProperties(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        คืน 0;
    }

    ถ้า (!surface->props) {
        surface->props = SDL_CreateProperties();
    }
    คืน surface->props;
}

bool SDL_SetSurfaceColorspace(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        คืน SDL_InvalidParamError("surface");
    }

    surface->colorspace = colorspace;
    คืน true;
}

SDL_Colorspace SDL_GetSurfaceColorspace(SDL_Surface *surface)
{
    ถ้า (!SDL_SurfaceValid(surface)) {
        คืน SDL_COLORSPACE_UNKNOWN;
    }

    คืน surface->colorspace;
}

float SDL_GetDefaultSDRWhitePoint(SDL_Colorspace colorspace)
{
    คืน SDL_GetSurfaceSDRWhitePoint(NULL, colorspace);
}

float SDL_GetSurfaceSDRWhitePoint(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    SDL_TransferCharacteristics transfer = SDL_COLORSPACETRANSFER(colorspace);

    ถ้า (transfer == SDL_TRANSFER_CHARACTERISTICS_LINEAR ||
        transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
        SDL_PropertiesID props;
        float default_value = 1.0f;

        ถ้า (SDL_SurfaceValid(surface)) {
            props = surface->props;
        } มิฉะนั้น {
            props = 0;
        }
        ถ้า (transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
            /* The older standards use an SDR white point of 100 nits.
             * ITU-R BT.2408-6 recommends using an SDR white point of 203 nits.
             * This is the default Chrome uses, and what a lot of game content
             * assumes, so we'll go with that.
             */
            const float DEFAULT_PQ_SDR_WHITE_POINT = 203.0f;
            default_value = DEFAULT_PQ_SDR_WHITE_POINT;
        }
        คืน SDL_GetFloatProperty(props, SDL_PROP_SURFACE_SDR_WHITE_POINT_FLOAT, default_value);
    }
    คืน 1.0f;
}

float SDL_GetDefaultHDRHeadroom(SDL_Colorspace colorspace)
{
    คืน SDL_GetSurfaceHDRHeadroom(NULL, colorspace);
}

float SDL_GetSurfaceHDRHeadroom(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    SDL_TransferCharacteristics transfer = SDL_COLORSPACETRANSFER(colorspace);

    ถ้า (transfer == SDL_TRANSFER_CHARACTERISTICS_LINEAR ||
        transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
        SDL_PropertiesID props;
        float default_value = 0.0f;

        ถ้า (SDL_SurfaceValid(surface)) {
            props = surface->props;
        } มิฉะนั้น {
            props = 0;
        }
        คืน SDL_GetFloatProperty(props, SDL_PROP_SURFACE_HDR_HEADROOM_FLOAT, default_value);
    }
    คืน 1.0f;
}

SDL_Palette *SDL_CreateSurfacePalette(SDL_Surface *surface)
{
    SDL_Palette *palette;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        คืน NULL;
    }

    CHECK_PARAM(!SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        SDL_SetError("The surface is not indexed format");
        คืน NULL;
    }

    palette = SDL_CreatePalette((1 << SDL_BITSPERPIXEL(surface->format)));
    ถ้า (!palette) {
        คืน NULL;
    }

    ถ้า (palette->ncolors == 2) {
        // Create a black and white bitmap palette
        palette->colors[0].r = 0xFF;
        palette->colors[0].g = 0xFF;
        palette->colors[0].b = 0xFF;
        palette->colors[1].r = 0x00;
        palette->colors[1].g = 0x00;
        palette->colors[1].b = 0x00;
    }

    ถ้า (!SDL_SetSurfacePalette(surface, palette)) {
        SDL_DestroyPalette(palette);
        คืน NULL;
    }

    // The surface has retained the palette, we can remove the reference here
    SDL_assert(palette->refcount == 2);
    SDL_DestroyPalette(palette);
    คืน palette;
}

bool SDL_SetSurfacePalette(SDL_Surface *surface, SDL_Palette *palette)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        คืน SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(palette && !SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        คืน SDL_SetError("Surface doesn't use a palette");
    }

    CHECK_PARAM(palette && palette->ncolors > (1 << SDL_BITSPERPIXEL(surface->format))) {
        คืน SDL_SetError("Palette doesn't match surface format");
    }

    ถ้า (palette != surface->palette) {
        ถ้า (surface->palette) {
            SDL_DestroyPalette(surface->palette);
        }

        surface->palette = palette;

        ถ้า (surface->palette) {
            ++surface->palette->refcount;
        }
    }

    SDL_InvalidateMap(&surface->map);

    คืน true;
}

SDL_Palette *SDL_GetSurfacePalette(SDL_Surface *surface)
{
    ถ้า (!SDL_SurfaceValid(surface)) {
        คืน NULL;
    }

    คืน surface->palette;
}

bool SDL_AddSurfaceAlternateImage(SDL_Surface *surface, SDL_Surface *image)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        คืน SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(!SDL_SurfaceValid(image)) {
        คืน SDL_InvalidParamError("image");
    }

    SDL_Surface **images = (SDL_Surface **)SDL_realloc(surface->images, (surface->num_images + 1) * parimaa_na(*images));
    ถ้า (!images) {
        คืน false;
    }
    images[surface->num_images] = image;
    surface->images = images;
    ++surface->num_images;
    ++image->refcount;
    คืน true;
}

bool SDL_SurfaceHasAlternateImages(SDL_Surface *surface)
{
    ถ้า (!SDL_SurfaceValid(surface)) {
        คืน false;
    }

    คืน (surface->num_images > 0);
}

SDL_Surface **SDL_GetSurfaceImages(SDL_Surface *surface, จำนวนเต็ม *count)
{
    ถ้า (count) {
        *count = 0;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        คืน NULL;
    }

    จำนวนเต็ม num_images = 1 + surface->num_images;
    SDL_Surface **images = (SDL_Surface **)SDL_malloc((num_images + 1) * parimaa_na(*images));
    ถ้า (!images) {
        คืน NULL;
    }
    images[0] = surface;
    ถ้า (surface->num_images > 0) {
        SDL_memcpy(&images[1], surface->images, (surface->num_images * parimaa_na(images[1])));
    }
    images[num_images] = NULL;

    ถ้า (count) {
        *count = num_images;
    }
    คืน images;
}

SDL_Surface *SDL_GetSurfaceImage(SDL_Surface *surface, float display_scale)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        คืน NULL;
    }

    ถ้า (!SDL_SurfaceHasAlternateImages(surface)) {
        ++surface->refcount;
        คืน surface;
    }

    // This surface has high DPI images, pick the best one available, or scale one to the correct size
    SDL_Surface **images = SDL_GetSurfaceImages(surface, NULL);
    ถ้า (!images) {
        // Failure, fall back to the existing surface
        ++surface->refcount;
        คืน surface;
    }

    // Find closest image. Images that are larger than the
    // desired size are preferred over images that are smaller.
    SDL_Surface *closest = NULL;
    จำนวนเต็ม desired_w = (จำนวนเต็ม)SDL_round(surface->w * display_scale);
    จำนวนเต็ม desired_h = (จำนวนเต็ม)SDL_round(surface->h * display_scale);
    จำนวนเต็ม desired_size = desired_w * desired_h;
    จำนวนเต็ม closest_distance = -1;
    จำนวนเต็ม closest_size = -1;
    สำหรับ (จำนวนเต็ม i = 0; images[i]; ++i) {
        SDL_Surface *candidate = images[i];
        จำนวนเต็ม size = candidate->w * candidate->h;
        จำนวนเต็ม delta_w = (candidate->w - desired_w);
        จำนวนเต็ม delta_h = (candidate->h - desired_h);
        จำนวนเต็ม distance = (delta_w * delta_w) + (delta_h * delta_h);
        ถ้า (closest_distance < 0 || distance < closest_distance ||
            (size > desired_size && closest_size < desired_size)) {
            closest = candidate;
            closest_distance = distance;
            closest_size = size;
        }
    }
    SDL_free(images);
    SDL_assert(closest != NULL);    // We should always have at least one surface

    ถ้า (closest->w == desired_w && closest->h == desired_h) {
        ++closest->refcount;
        คืน closest;
    }

    // We need to scale the image to the correct size. To maintain good image quality, downscaling
    // is done in steps, never reducing the width and height by more than half each time.
    SDL_Surface *scaled = closest;
    do {
        จำนวนเต็ม next_scaled_w = SDL_max(desired_w, (scaled->w + 1) / 2);
        จำนวนเต็ม next_scaled_h = SDL_max(desired_h, (scaled->h + 1) / 2);
        SDL_Surface *next_scaled = SDL_ScaleSurface(scaled, next_scaled_w, next_scaled_h, SDL_SCALEMODE_LINEAR);
        ถ้า (scaled != closest) {
            SDL_DestroySurface(scaled);
        }
        scaled = next_scaled;
        ถ้า (!scaled) {
            // Failure, fall back to the closest surface
            ++closest->refcount;
            คืน closest;
        }
    } ขณะ (scaled->w != desired_w || scaled->h != desired_h);

    คืน scaled;
}

void SDL_RemoveSurfaceAlternateImages(SDL_Surface *surface)
{
    ถ้า (!SDL_SurfaceValid(surface)) {
        คืน;
    }

    ถ้า (surface->num_images > 0) {
        สำหรับ (จำนวนเต็ม i = 0; i < surface->num_images; ++i) {
            SDL_DestroySurface(surface->images[i]);
        }
        SDL_free(surface->images);
        surface->images = NULL;
        surface->num_images = 0;
    }
}

bool SDL_SetSurfaceRLE(SDL_Surface *surface, bool enabled)
{
    จำนวนเต็ม flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        คืน SDL_InvalidParamError("surface");
    }

    flags = surface->map.info.flags;
    ถ้า (enabled) {
        surface->map.info.flags |= SDL_COPY_RLE_DESIRED;
    } มิฉะนั้น {
        surface->map.info.flags &= ~SDL_COPY_RLE_DESIRED;
    }
    ถ้า (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    คืน true;
}

bool SDL_SurfaceHasRLE(SDL_Surface *surface)
{
    ถ้า (!SDL_SurfaceValid(surface)) {
        คืน false;
    }

    ถ้า (!(surface->map.info.flags & SDL_COPY_RLE_DESIRED)) {
        คืน false;
    }

    คืน true;
}

bool SDL_SetSurfaceColorKey(SDL_Surface *surface, bool enabled, Uint32 key)
{
    จำนวนเต็ม flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        คืน SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(surface->palette && key >= ((Uint32)surface->palette->ncolors)) {
        คืน SDL_InvalidParamError("key");
    }

    flags = surface->map.info.flags;
    ถ้า (enabled) {
        surface->map.info.flags |= SDL_COPY_COLORKEY;
        surface->map.info.colorkey = key;
    } มิฉะนั้น {
        surface->map.info.flags &= ~SDL_COPY_COLORKEY;
    }
    ถ้า (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }

    คืน true;
}

bool SDL_SurfaceHasColorKey(SDL_Surface *surface)
{
    ถ้า (!SDL_SurfaceValid(surface)) {
        คืน false;
    }

    ถ้า (!(surface->map.info.flags & SDL_COPY_COLORKEY)) {
        คืน false;
    }

    คืน true;
}

bool SDL_GetSurfaceColorKey(SDL_Surface *surface, Uint32 *key)
{
    ถ้า (key) {
        *key = 0;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        คืน SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(!(surface->map.info.flags & SDL_COPY_COLORKEY)) {
        คืน SDL_SetError("Surface doesn't have a colorkey");
    }

    ถ้า (key) {
        *key = surface->map.info.colorkey;
    }
    คืน true;
}

/* This is a fairly slow function to switch from colorkey to alpha
   NB: it doesn't handle bpp 1 or 3, because they have no alpha channel */
static void SDL_ConvertColorkeyToAlpha(SDL_Surface *surface, bool ignore_alpha)
{
    จำนวนเต็ม x, y, bpp;

    ถ้า (!SDL_SurfaceValid(surface)) {
        คืน;
    }

    ถ้า (!(surface->map.info.flags & SDL_COPY_COLORKEY) ||
        !SDL_ISPIXELFORMAT_ALPHA(surface->format)) {
        คืน;
    }

    bpp = SDL_BYTESPERPIXEL(surface->format);

    SDL_LockSurface(surface);

    ถ้า (bpp == 2) {
        Uint16 *row, *spot;
        Uint16 ckey = (Uint16)surface->map.info.colorkey;
        Uint16 mask = (Uint16)(~surface->fmt->Amask);

        // Ignore, or not, alpha in colorkey comparison
        ถ้า (ignore_alpha) {
            ckey &= mask;
            row = (Uint16 *)surface->pixels;
            สำหรับ (y = surface->h; y--;) {
                spot = row;
                สำหรับ (x = surface->w; x--;) {
                    ถ้า ((*spot & mask) == ckey) {
                        *spot &= mask;
                    }
                    ++spot;
                }
                row += surface->pitch / 2;
            }
        } มิฉะนั้น {
            row = (Uint16 *)surface->pixels;
            สำหรับ (y = surface->h; y--;) {
                spot = row;
                สำหรับ (x = surface->w; x--;) {
                    ถ้า (*spot == ckey) {
                        *spot &= mask;
                    }
                    ++spot;
                }
                row += surface->pitch / 2;
            }
        }
    } มิฉะนั้น ถ้า (bpp == 4) {
        Uint32 *row, *spot;
        Uint32 ckey = surface->map.info.colorkey;
        Uint32 mask = ~surface->fmt->Amask;

        // Ignore, or not, alpha in colorkey comparison
        ถ้า (ignore_alpha) {
            ckey &= mask;
            row = (Uint32 *)surface->pixels;
            สำหรับ (y = surface->h; y--;) {
                spot = row;
                สำหรับ (x = surface->w; x--;) {
                    ถ้า ((*spot & mask) == ckey) {
                        *spot &= mask;
                    }
                    ++spot;
                }
                row += surface->pitch / 4;
            }
        } มิฉะนั้น {
            row = (Uint32 *)surface->pixels;
            สำหรับ (y = surface->h; y--;) {
                spot = row;
                สำหรับ (x = surface->w; x--;) {
                    ถ้า (*spot == ckey) {
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
    จำนวนเต็ม flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        คืน SDL_InvalidParamError("surface");
    }

    surface->map.info.r = r;
    surface->map.info.g = g;
    surface->map.info.b = b;

    flags = surface->map.info.flags;
    ถ้า (r != 0xFF || g != 0xFF || b != 0xFF) {
        surface->map.info.flags |= SDL_COPY_MODULATE_COLOR;
    } มิฉะนั้น {
        surface->map.info.flags &= ~SDL_COPY_MODULATE_COLOR;
    }
    ถ้า (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    คืน true;
}

bool SDL_GetSurfaceColorMod(SDL_Surface *surface, Uint8 *r, Uint8 *g, Uint8 *b)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ถ้า (r) {
            *r = 255;
        }
        ถ้า (g) {
            *g = 255;
        }
        ถ้า (b) {
            *b = 255;
        }
        คืน SDL_InvalidParamError("surface");
    }

    ถ้า (r) {
        *r = surface->map.info.r;
    }
    ถ้า (g) {
        *g = surface->map.info.g;
    }
    ถ้า (b) {
        *b = surface->map.info.b;
    }
    คืน true;
}

bool SDL_SetSurfaceAlphaMod(SDL_Surface *surface, Uint8 alpha)
{
    จำนวนเต็ม flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        คืน SDL_InvalidParamError("surface");
    }

    surface->map.info.a = alpha;

    flags = surface->map.info.flags;
    ถ้า (alpha != 0xFF) {
        surface->map.info.flags |= SDL_COPY_MODULATE_ALPHA;
    } มิฉะนั้น {
        surface->map.info.flags &= ~SDL_COPY_MODULATE_ALPHA;
    }
    ถ้า (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    คืน true;
}

bool SDL_GetSurfaceAlphaMod(SDL_Surface *surface, Uint8 *alpha)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ถ้า (alpha) {
            *alpha = 255;
        }
        คืน SDL_InvalidParamError("surface");
    }

    ถ้า (alpha) {
        *alpha = surface->map.info.a;
    }
    คืน true;
}

bool SDL_SetSurfaceBlendMode(SDL_Surface *surface, SDL_BlendMode blendMode)
{
    จำนวนเต็ม flags;
    bool result = true;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        คืน SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(blendMode == SDL_BLENDMODE_INVALID) {
        คืน SDL_InvalidParamError("blendMode");
    }

    flags = surface->map.info.flags;
    surface->map.info.flags &= ~SDL_COPY_BLEND_MASK;
    switch (blendMode) {
    pak_sa SDL_BLENDMODE_NONE:
        bha_nga;
    pak_sa SDL_BLENDMODE_BLEND:
        surface->map.info.flags |= SDL_COPY_BLEND;
        bha_nga;
    pak_sa SDL_BLENDMODE_BLEND_PREMULTIPLIED:
        surface->map.info.flags |= SDL_COPY_BLEND_PREMULTIPLIED;
        bha_nga;
    pak_sa SDL_BLENDMODE_ADD:
        surface->map.info.flags |= SDL_COPY_ADD;
        bha_nga;
    pak_sa SDL_BLENDMODE_ADD_PREMULTIPLIED:
        surface->map.info.flags |= SDL_COPY_ADD_PREMULTIPLIED;
        bha_nga;
    pak_sa SDL_BLENDMODE_MOD:
        surface->map.info.flags |= SDL_COPY_MOD;
        bha_nga;
    pak_sa SDL_BLENDMODE_MUL:
        surface->map.info.flags |= SDL_COPY_MUL;
        bha_nga;
    default:
        result = SDL_Unsupported();
        bha_nga;
    }

    ถ้า (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }

    คืน result;
}

bool SDL_GetSurfaceBlendMode(SDL_Surface *surface, SDL_BlendMode *blendMode)
{
    ถ้า (blendMode) {
        *blendMode = SDL_BLENDMODE_INVALID;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        คืน SDL_InvalidParamError("surface");
    }

    ถ้า (!blendMode) {
        คืน true;
    }

    switch (surface->map.info.flags & SDL_COPY_BLEND_MASK) {
    pak_sa SDL_COPY_BLEND:
        *blendMode = SDL_BLENDMODE_BLEND;
        bha_nga;
    pak_sa SDL_COPY_BLEND_PREMULTIPLIED:
        *blendMode = SDL_BLENDMODE_BLEND_PREMULTIPLIED;
        bha_nga;
    pak_sa SDL_COPY_ADD:
        *blendMode = SDL_BLENDMODE_ADD;
        bha_nga;
    pak_sa SDL_COPY_ADD_PREMULTIPLIED:
        *blendMode = SDL_BLENDMODE_ADD_PREMULTIPLIED;
        bha_nga;
    pak_sa SDL_COPY_MOD:
        *blendMode = SDL_BLENDMODE_MOD;
        bha_nga;
    pak_sa SDL_COPY_MUL:
        *blendMode = SDL_BLENDMODE_MUL;
        bha_nga;
    default:
        *blendMode = SDL_BLENDMODE_NONE;
        bha_nga;
    }
    คืน true;
}

bool SDL_SetSurfaceClipRect(SDL_Surface *surface, const SDL_Rect *rect)
{
    SDL_Rect full_rect;

    // Don't do anything if there's no surface to act on
    ถ้า (!SDL_SurfaceValid(surface)) {
        คืน false;
    }

    // Set up the full surface rectangle
    full_rect.x = 0;
    full_rect.y = 0;
    full_rect.w = surface->w;
    full_rect.h = surface->h;

    // Set the clipping rectangle
    ถ้า (!rect) {
        surface->clip_rect = full_rect;
        คืน true;
    }
    คืน SDL_GetRectIntersection(rect, &full_rect, &surface->clip_rect);
}

bool SDL_GetSurfaceClipRect(SDL_Surface *surface, SDL_Rect *rect)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ถ้า (rect) {
            SDL_zerop(rect);
        }
        คืน SDL_InvalidParamError("surface");
    }
    CHECK_PARAM(!rect) {
        คืน SDL_InvalidParamError("rect");
    }
    *rect = surface->clip_rect;
    คืน true;
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
bool SDL_BlitSurfaceUnchecked(SDL_Surface *src, const SDL_Rect *srcrect,
                             SDL_Surface *dst, const SDL_Rect *dstrect)
{
    // Check to make sure the blit mapping is valid
    ถ้า (!SDL_ValidateMap(src, dst)) {
        คืน false;
    }
    คืน src->map.blit(src, srcrect, dst, dstrect);
}

bool SDL_BlitSurface(SDL_Surface *src, const SDL_Rect *srcrect, SDL_Surface *dst, const SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src) || (!src->pixels && !SDL_MUSTLOCK(src))) {
        คืน SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst) || (!dst->pixels && !SDL_MUSTLOCK(dst))) {
        คืน SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        คืน SDL_SetError("Surfaces must not be locked during blit");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    ถ้า (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
    } มิฉะนั้น {
        r_dst.x = 0;
        r_dst.y = 0;
    }

    // clip the source rectangle to the source surface
    ถ้า (srcrect) {
        SDL_Rect tmp;
        ถ้า (SDL_GetRectIntersection(srcrect, &r_src, &tmp) == false) {
            คืน true;
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
        ถ้า (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &tmp) == false) {
            คืน true;
        }

        // Shift srcrect, if dstrect has changed
        r_src.x += tmp.x - r_dst.x;
        r_src.y += tmp.y - r_dst.y;
        r_src.w = tmp.w;
        r_src.h = tmp.h;

        // Update dstrect
        r_dst = tmp;
    }

    ถ้า (r_dst.w <= 0 || r_dst.h <= 0) {
        // No-op.
        คืน true;
    }

    // Switch back to a fast blit if we were previously stretching
    ถ้า (src->map.info.flags & SDL_COPY_NEAREST) {
        src->map.info.flags &= ~SDL_COPY_NEAREST;
        SDL_InvalidateMap(&src->map);
    }

    คืน SDL_BlitSurfaceUnchecked(src, &r_src, dst, &r_dst);
}

static bool SDL_BlitSurfaceClippedScaled(SDL_Surface *src, const SDL_Rect *srcrect, SDL_Surface *dst, const SDL_Rect *dstrect, SDL_ScaleMode scaleMode)
{
    // We need to scale first, then blit into dst because we're clipping in the destination surface pixel coordinates
    bool result;
    จำนวนเต็ม saved_w = src->w;
    จำนวนเต็ม saved_h = src->h;
    void *saved_pixels = src->pixels;
    src->w = srcrect->w;
    src->h = srcrect->h;
    src->pixels = (Uint8 *)src->pixels + srcrect->y * src->pitch + srcrect->x * SDL_BYTESPERPIXEL(src->format);
    SDL_Surface *scaled = SDL_ScaleSurface(src, dstrect->w, dstrect->h, scaleMode);
    ถ้า (scaled) {
        result = SDL_BlitSurface(scaled, NULL, dst, dstrect);
        SDL_DestroySurface(scaled);
    } มิฉะนั้น {
        result = false;
    }
    src->w = saved_w;
    src->h = saved_h;
    src->pixels = saved_pixels;
    คืน result;
}

bool SDL_BlitSurfaceScaled(SDL_Surface *src, const SDL_Rect *srcrect, SDL_Surface *dst, const SDL_Rect *dstrect, SDL_ScaleMode scaleMode)
{
    SDL_Rect r_src, r_dst;
    bool result;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src) || (!src->pixels && !SDL_MUSTLOCK(src))) {
        คืน SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst) || (!dst->pixels && !SDL_MUSTLOCK(dst))) {
        คืน SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        คืน SDL_SetError("Surfaces must not be locked during blit");
    }

    switch (scaleMode) {
    pak_sa SDL_SCALEMODE_NEAREST:
        bha_nga;
    pak_sa SDL_SCALEMODE_LINEAR:
        bha_nga;
    pak_sa SDL_SCALEMODE_PIXELART:
        scaleMode = SDL_SCALEMODE_NEAREST;
        bha_nga;
    default:
        คืน SDL_InvalidParamError("scaleMode");
    }

    จำนวนเต็ม src_w = srcrect ? srcrect->w : src->w;
    จำนวนเต็ม src_h = srcrect ? srcrect->h : src->h;
    จำนวนเต็ม dst_w = dstrect ? dstrect->w : dst->w;
    จำนวนเต็ม dst_h = dstrect ? dstrect->h : dst->h;
    ถ้า (src_w == dst_w && src_h == dst_h) {
        // No scaling, defer to regular blit
        คืน SDL_BlitSurface(src, srcrect, dst, dstrect);
    }

    ถ้า (src->w == 0 || src->h == 0) {
        // Nothing to do
        คืน true;
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    ถ้า (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
        r_dst.w = dstrect->w;
        r_dst.h = dstrect->h;
    } มิฉะนั้น {
        r_dst.x = 0;
        r_dst.y = 0;
        r_dst.w = dst->w;
        r_dst.h = dst->h;
    }

    // clip the source rectangle to the source surface
    ถ้า (srcrect) {
        SDL_Rect desired, tmp;
        desired.x = srcrect->x;
        desired.y = srcrect->y;
        desired.w = SDL_max(srcrect->w, 1);
        desired.h = SDL_max(srcrect->h, 1);
        ถ้า (SDL_GetRectIntersection(&desired, &r_src, &tmp) == false) {
            คืน true;
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
    ถ้า (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &tmp) == false) {
        คืน true;
    }

    ถ้า (tmp.x != r_dst.x || tmp.y != r_dst.y || tmp.w != r_dst.w || tmp.h != r_dst.h) {
        // Need to do a clipped and scaled blit
        คืน SDL_BlitSurfaceClippedScaled(src, &r_src, dst, &r_dst, scaleMode);
    }

    ถ้า (SDL_MUSTLOCK(src)) {
        ถ้า (!SDL_LockSurface(src)) {
            คืน false;
        }
    }
    ถ้า (SDL_MUSTLOCK(dst)) {
        ถ้า (!SDL_LockSurface(dst)) {
            ถ้า (SDL_MUSTLOCK(src)) {
                SDL_UnlockSurface(src);
            }
            คืน false;
        }
    }

    result = SDL_BlitSurfaceUncheckedScaled(src, &r_src, dst, &r_dst, scaleMode);

    ถ้า (SDL_MUSTLOCK(src)) {
        SDL_UnlockSurface(src);
    }
    ถ้า (SDL_MUSTLOCK(dst)) {
        SDL_UnlockSurface(dst);
    }
    คืน result;
}

/**
 *  This is a semi-private blit function and it performs low-level surface
 *  scaled blitting only.
 */
bool SDL_BlitSurfaceUncheckedScaled(SDL_Surface *src, const SDL_Rect *srcrect, SDL_Surface *dst, const SDL_Rect *dstrect, SDL_ScaleMode scaleMode)
{
    static const Uint32 complex_copy_flags = (SDL_COPY_MODULATE_MASK | SDL_COPY_BLEND_MASK | SDL_COPY_COLORKEY);

    ถ้า (srcrect->w > SDL_MAX_UINT16 || srcrect->h > SDL_MAX_UINT16 ||
        dstrect->w > SDL_MAX_UINT16 || dstrect->h > SDL_MAX_UINT16) {
        คืน SDL_SetError("Size too large for scaling");
    }

    ถ้า (!(src->map.info.flags & SDL_COPY_NEAREST)) {
        src->map.info.flags |= SDL_COPY_NEAREST;
        SDL_InvalidateMap(&src->map);
    }

    ถ้า (scaleMode == SDL_SCALEMODE_NEAREST || scaleMode == SDL_SCALEMODE_PIXELART) {
        ถ้า (!(src->map.info.flags & complex_copy_flags) &&
            src->format == dst->format &&
            (!SDL_ISPIXELFORMAT_INDEXED(src->format) ||
             (SDL_BITSPERPIXEL(src->format) == 8 && SDL_IsSamePalette(src->palette, dst->palette))) &&
            SDL_BYTESPERPIXEL(src->format) <= 4) {
            คืน SDL_StretchSurface(src, srcrect, dst, dstrect, SDL_SCALEMODE_NEAREST);
        } มิฉะนั้น ถ้า (SDL_BITSPERPIXEL(src->format) < 8) {
            // Scaling bitmap not yet supported, convert to RGBA for blit
            bool result = false;
            SDL_Surface *tmp = SDL_ConvertSurface(src, SDL_PIXELFORMAT_ARGB8888);
            ถ้า (tmp) {
                result = SDL_BlitSurfaceUncheckedScaled(tmp, srcrect, dst, dstrect, SDL_SCALEMODE_NEAREST);
                SDL_DestroySurface(tmp);
            }
            คืน result;
        } มิฉะนั้น {
            คืน SDL_BlitSurfaceUnchecked(src, srcrect, dst, dstrect);
        }
    } มิฉะนั้น {
        ถ้า (!(src->map.info.flags & complex_copy_flags) &&
            src->format == dst->format &&
            !SDL_ISPIXELFORMAT_INDEXED(src->format) &&
            SDL_BYTESPERPIXEL(src->format) == 4 &&
            src->format != SDL_PIXELFORMAT_ARGB2101010) {
            // fast path
            คืน SDL_StretchSurface(src, srcrect, dst, dstrect, SDL_SCALEMODE_LINEAR);
        } มิฉะนั้น ถ้า (SDL_BITSPERPIXEL(src->format) < 8) {
            // Scaling bitmap not yet supported, convert to RGBA for blit
            bool result = false;
            SDL_Surface *tmp = SDL_ConvertSurface(src, SDL_PIXELFORMAT_ARGB8888);
            ถ้า (tmp) {
                result = SDL_BlitSurfaceUncheckedScaled(tmp, srcrect, dst, dstrect, scaleMode);
                SDL_DestroySurface(tmp);
            }
            คืน result;
        } มิฉะนั้น {
            // Use intermediate surface(s)
            SDL_Surface *tmp1 = NULL;
            bool result;
            SDL_Rect srcrect2;
            จำนวนเต็ม is_complex_copy_flags = (src->map.info.flags & complex_copy_flags);

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
            ถ้า (SDL_BYTESPERPIXEL(src->format) != 4 || src->format == SDL_PIXELFORMAT_ARGB2101010) {
                SDL_PixelFormat fmt;
                ถ้า (SDL_BYTESPERPIXEL(dst->format) == 4 && dst->format != SDL_PIXELFORMAT_ARGB2101010 &&
                    (SDL_ISPIXELFORMAT_ALPHA(dst->format) || !is_complex_copy_flags)) {
                    fmt = dst->format;
                } มิฉะนั้น {
                    fmt = SDL_PIXELFORMAT_ARGB8888;
                }
                tmp1 = SDL_ConvertSurfaceRect(src, srcrect, fmt);
                ถ้า (!tmp1) {
                    คืน false;
                }
                src = tmp1;
                srcrect2.x = 0;
                srcrect2.y = 0;
            }

            // Intermediate scaling
            ถ้า (is_complex_copy_flags || src->format != dst->format) {
                SDL_Rect tmprect;
                SDL_Surface *tmp2 = SDL_CreateSurfaceUninitialized(dstrect->w, dstrect->h, src->format);
                SDL_StretchSurface(src, &srcrect2, tmp2, NULL, SDL_SCALEMODE_LINEAR);

                SDL_SetSurfaceColorMod(tmp2, r, g, b);
                SDL_SetSurfaceAlphaMod(tmp2, alpha);
                SDL_SetSurfaceBlendMode(tmp2, blendMode);

                tmprect.x = 0;
                tmprect.y = 0;
                tmprect.w = dstrect->w;
                tmprect.h = dstrect->h;
                result = SDL_BlitSurfaceUnchecked(tmp2, &tmprect, dst, dstrect);
                SDL_DestroySurface(tmp2);
            } มิฉะนั้น {
                result = SDL_StretchSurface(src, &srcrect2, dst, dstrect, SDL_SCALEMODE_LINEAR);
            }

            SDL_DestroySurface(tmp1);
            คืน result;
        }
    }
}

bool SDL_BlitSurfaceTiled(SDL_Surface *src, const SDL_Rect *srcrect, SDL_Surface *dst, const SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        คืน SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        คืน SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        คืน SDL_SetError("Surfaces must not be locked during blit");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    ถ้า (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
        r_dst.w = dstrect->w;
        r_dst.h = dstrect->h;
    } มิฉะนั้น {
        r_dst.x = 0;
        r_dst.y = 0;
        r_dst.w = dst->w;
        r_dst.h = dst->h;
    }

    // clip the source rectangle to the source surface
    ถ้า (srcrect) {
        ถ้า (SDL_GetRectIntersection(srcrect, &r_src, &r_src) == false) {
            คืน true;
        }

        // For tiling we don't adjust the destination rectangle
    }

    // clip the destination rectangle against the clip rectangle
    {
        ถ้า (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &r_dst) == false) {
            คืน true;
        }

        // For tiling we don't adjust the source rectangle
    }

    // Switch back to a fast blit if we were previously stretching
    ถ้า (src->map.info.flags & SDL_COPY_NEAREST) {
        src->map.info.flags &= ~SDL_COPY_NEAREST;
        SDL_InvalidateMap(&src->map);
    }

    จำนวนเต็ม rows = r_dst.h / r_src.h;
    จำนวนเต็ม cols = r_dst.w / r_src.w;
    จำนวนเต็ม remaining_w = r_dst.w % r_src.w;
    จำนวนเต็ม remaining_h = r_dst.h % r_src.h;
    SDL_Rect curr_src, curr_dst;

    SDL_copyp(&curr_src, &r_src);
    curr_dst.y = r_dst.y;
    curr_dst.w = r_src.w;
    curr_dst.h = r_src.h;
    สำหรับ (จำนวนเต็ม y = 0; y < rows; ++y) {
        curr_dst.x = r_dst.x;
        สำหรับ (จำนวนเต็ม x = 0; x < cols; ++x) {
            ถ้า (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                คืน false;
            }
            curr_dst.x += curr_dst.w;
        }
        ถ้า (remaining_w) {
            curr_src.w = remaining_w;
            curr_dst.w = remaining_w;
            ถ้า (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                คืน false;
            }
            curr_src.w = r_src.w;
            curr_dst.w = r_src.w;
        }
        curr_dst.y += curr_dst.h;
    }
    ถ้า (remaining_h) {
        curr_src.h = remaining_h;
        curr_dst.h = remaining_h;
        curr_dst.x = r_dst.x;
        สำหรับ (จำนวนเต็ม x = 0; x < cols; ++x) {
            ถ้า (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                คืน false;
            }
            curr_dst.x += curr_dst.w;
        }
        ถ้า (remaining_w) {
            curr_src.w = remaining_w;
            curr_dst.w = remaining_w;
            ถ้า (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                คืน false;
            }
        }
    }
    คืน true;
}

bool SDL_BlitSurfaceTiledWithScale(SDL_Surface *src, const SDL_Rect *srcrect, float scale, SDL_ScaleMode scaleMode, SDL_Surface *dst, const SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        คืน SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        คืน SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        คืน SDL_SetError("Surfaces must not be locked during blit");
    }
    CHECK_PARAM(scale < 0.0f) {
        คืน SDL_InvalidParamError("scale");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    ถ้า (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
        r_dst.w = dstrect->w;
        r_dst.h = dstrect->h;
    } มิฉะนั้น {
        r_dst.x = 0;
        r_dst.y = 0;
        r_dst.w = dst->w;
        r_dst.h = dst->h;
    }

    // clip the source rectangle to the source surface
    ถ้า (srcrect) {
        ถ้า (SDL_GetRectIntersection(srcrect, &r_src, &r_src) == false) {
            คืน true;
        }

        // For tiling we don't adjust the destination rectangle
    }

    // clip the destination rectangle against the clip rectangle
    {
        ถ้า (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &r_dst) == false) {
            คืน true;
        }

        // For tiling we don't adjust the source rectangle
    }

    // Switch back to a fast blit if we were previously stretching
    ถ้า (src->map.info.flags & SDL_COPY_NEAREST) {
        src->map.info.flags &= ~SDL_COPY_NEAREST;
        SDL_InvalidateMap(&src->map);
    }

    จำนวนเต็ม tile_width = (จำนวนเต็ม)SDL_roundf(r_src.w * scale);
    จำนวนเต็ม tile_height = (จำนวนเต็ม)SDL_roundf(r_src.h * scale);
    ถ้า (tile_width <= 0 || tile_height <= 0) {
        // Nothing to do
        คืน true;
    }
    จำนวนเต็ม rows = r_dst.h / tile_height;
    จำนวนเต็ม cols = r_dst.w / tile_width;
    จำนวนเต็ม remaining_dst_w = (r_dst.w - cols * tile_width);
    จำนวนเต็ม remaining_dst_h = (r_dst.h - rows * tile_height);
    จำนวนเต็ม remaining_src_w = (จำนวนเต็ม)(remaining_dst_w / scale);
    จำนวนเต็ม remaining_src_h = (จำนวนเต็ม)(remaining_dst_h / scale);
    SDL_Rect curr_src, curr_dst;

    SDL_copyp(&curr_src, &r_src);
    curr_dst.y = r_dst.y;
    curr_dst.w = tile_width;
    curr_dst.h = tile_height;
    สำหรับ (จำนวนเต็ม y = 0; y < rows; ++y) {
        curr_dst.x = r_dst.x;
        สำหรับ (จำนวนเต็ม x = 0; x < cols; ++x) {
            ถ้า (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
                คืน false;
            }
            curr_dst.x += curr_dst.w;
        }
        ถ้า (remaining_dst_w > 0) {
            curr_src.w = remaining_src_w;
            curr_dst.w = remaining_dst_w;
            ถ้า (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
                คืน false;
            }
            curr_src.w = r_src.w;
            curr_dst.w = tile_width;
        }
        curr_dst.y += curr_dst.h;
    }
    ถ้า (remaining_dst_h > 0) {
        curr_src.h = remaining_src_h;
        curr_dst.h = remaining_dst_h;
        curr_dst.x = r_dst.x;
        สำหรับ (จำนวนเต็ม x = 0; x < cols; ++x) {
            ถ้า (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
                คืน false;
            }
            curr_dst.x += curr_dst.w;
        }
        ถ้า (remaining_dst_w > 0) {
            curr_src.w = remaining_src_w;
            curr_dst.w = remaining_dst_w;
            ถ้า (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
                คืน false;
            }
        }
    }
    คืน true;
}

bool SDL_BlitSurface9Grid(SDL_Surface *src, const SDL_Rect *srcrect, จำนวนเต็ม left_width, จำนวนเต็ม right_width, จำนวนเต็ม top_height, จำนวนเต็ม bottom_height, float scale, SDL_ScaleMode scaleMode, SDL_Surface *dst, const SDL_Rect *dstrect)
{
    SDL_Rect full_src, full_dst;
    SDL_Rect curr_src, curr_dst;
    จำนวนเต็ม dst_left_width;
    จำนวนเต็ม dst_right_width;
    จำนวนเต็ม dst_top_height;
    จำนวนเต็ม dst_bottom_height;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        คืน SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        คืน SDL_InvalidParamError("dst");
    }

    ถ้า (!srcrect) {
        full_src.x = 0;
        full_src.y = 0;
        full_src.w = src->w;
        full_src.h = src->h;
        srcrect = &full_src;
    }

    ถ้า (!dstrect) {
        full_dst.x = 0;
        full_dst.y = 0;
        full_dst.w = dst->w;
        full_dst.h = dst->h;
        dstrect = &full_dst;
    }

    ถ้า (scale <= 0.0f || scale == 1.0f) {
        dst_left_width = left_width;
        dst_right_width = right_width;
        dst_top_height = top_height;
        dst_bottom_height = bottom_height;
    } มิฉะนั้น {
        dst_left_width = (จำนวนเต็ม)SDL_roundf(left_width * scale);
        dst_right_width = (จำนวนเต็ม)SDL_roundf(right_width * scale);
        dst_top_height = (จำนวนเต็ม)SDL_roundf(top_height * scale);
        dst_bottom_height = (จำนวนเต็ม)SDL_roundf(bottom_height * scale);
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
    ถ้า (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        คืน false;
    }

    // Upper-right corner
    curr_src.x = srcrect->x + srcrect->w - right_width;
    curr_src.w = right_width;
    curr_dst.x = dstrect->x + dstrect->w - dst_right_width;
    curr_dst.w = dst_right_width;
    ถ้า (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        คืน false;
    }

    // Lower-right corner
    curr_src.y = srcrect->y + srcrect->h - bottom_height;
    curr_dst.y = dstrect->y + dstrect->h - dst_bottom_height;
    curr_dst.h = dst_bottom_height;
    ถ้า (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        คืน false;
    }

    // Lower-left corner
    curr_src.x = srcrect->x;
    curr_src.w = left_width;
    curr_dst.x = dstrect->x;
    curr_dst.w = dst_left_width;
    ถ้า (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        คืน false;
    }

    // Left
    curr_src.y = srcrect->y + top_height;
    curr_src.h = srcrect->h - top_height - bottom_height;
    curr_dst.y = dstrect->y + dst_top_height;
    curr_dst.h = dstrect->h - dst_top_height - dst_bottom_height;
    ถ้า (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        คืน false;
    }

    // Right
    curr_src.x = srcrect->x + srcrect->w - right_width;
    curr_src.w = right_width;
    curr_dst.x = dstrect->x + dstrect->w - dst_right_width;
    curr_dst.w = dst_right_width;
    ถ้า (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        คืน false;
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
    ถ้า (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        คืน false;
    }

    // Bottom
    curr_src.y = srcrect->y + srcrect->h - bottom_height;
    curr_dst.y = dstrect->y + dstrect->h - dst_bottom_height;
    curr_dst.h = dst_bottom_height;
    ถ้า (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        คืน false;
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
    ถ้า (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        คืน false;
    }

    คืน true;
}

/*
 * Lock a surface to directly access the pixels
 */
bool SDL_LockSurface(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        คืน SDL_InvalidParamError("surface");
    }

    ถ้า (!surface->locked) {
#ifdef SDL_HAVE_RLE
        // Perform the lock
        ถ้า (surface->internal_flags & SDL_INTERNAL_SURFACE_RLEACCEL) {
            SDL_UnRLESurface(surface);
        }
#endif
    }

    // Increment the surface lock count, for recursive locks
    ++surface->locked;
    surface->flags |= SDL_SURFACE_LOCKED;
    SDL_UpdateSurfaceLockFlag(surface);

    // Ready to go..
    คืน true;
}

/*
 * Unlock a previously locked surface
 */
void SDL_UnlockSurface(SDL_Surface *surface)
{
    ถ้า (!SDL_SurfaceValid(surface)) {
        คืน;
    }

    // Only perform an unlock if we are locked
    ถ้า (!surface->locked || (--surface->locked > 0)) {
        คืน;
    }

    surface->flags &= ~SDL_SURFACE_LOCKED;
    SDL_UpdateSurfaceLockFlag(surface);
}

static bool SDL_FlipSurfaceHorizontal(SDL_Surface *surface)
{
    bool isstack;
    Uint8 *row, *a, *b, *tmp;
    จำนวนเต็ม i, j, bpp;

    ถ้า (SDL_BITSPERPIXEL(surface->format) < 8) {
        // We could implement this if needed, but we'd have to flip sets of bits within a byte
        คืน SDL_Unsupported();
    }

    ถ้า (surface->h <= 0) {
        คืน true;
    }

    ถ้า (surface->w <= 1) {
        คืน true;
    }

    bpp = SDL_BYTESPERPIXEL(surface->format);
    row = (Uint8 *)surface->pixels;
    tmp = SDL_small_alloc(Uint8, surface->pitch, &isstack);
    ถ้า (!tmp) {
        คืน false;
    }
    สำหรับ (i = surface->h; i--; ) {
        a = row;
        b = a + (surface->w - 1) * bpp;
        สำหรับ (j = surface->w / 2; j--; ) {
            SDL_memcpy(tmp, a, bpp);
            SDL_memcpy(a, b, bpp);
            SDL_memcpy(b, tmp, bpp);
            a += bpp;
            b -= bpp;
        }
        row += surface->pitch;
    }
    SDL_small_free(tmp, isstack);
    คืน true;
}

static bool SDL_FlipSurfaceVertical(SDL_Surface *surface)
{
    bool isstack;
    Uint8 *a, *b, *tmp;
    จำนวนเต็ม i;

    ถ้า (surface->h <= 1) {
        คืน true;
    }

    a = (Uint8 *)surface->pixels;
    b = a + (surface->h - 1) * surface->pitch;
    tmp = SDL_small_alloc(Uint8, surface->pitch, &isstack);
    ถ้า (!tmp) {
        คืน false;
    }
    สำหรับ (i = surface->h / 2; i--; ) {
        SDL_memcpy(tmp, a, surface->pitch);
        SDL_memcpy(a, b, surface->pitch);
        SDL_memcpy(b, tmp, surface->pitch);
        a += surface->pitch;
        b -= surface->pitch;
    }
    SDL_small_free(tmp, isstack);
    คืน true;
}

bool SDL_FlipSurface(SDL_Surface *surface, SDL_FlipMode flip)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        คืน SDL_InvalidParamError("surface");
    }
    ถ้า (!surface->pixels) {
        คืน true;
    }

    bool result = true;
    switch (flip) {
    pak_sa SDL_FLIP_HORIZONTAL:
        result = SDL_FlipSurfaceHorizontal(surface);
        bha_nga;
    pak_sa SDL_FLIP_VERTICAL:
        result = SDL_FlipSurfaceVertical(surface);
        bha_nga;
    pak_sa SDL_FLIP_HORIZONTAL_AND_VERTICAL:
        result &= SDL_FlipSurfaceHorizontal(surface);
        result &= SDL_FlipSurfaceVertical(surface);
        bha_nga;
    default:
        result = SDL_InvalidParamError("flip");
        bha_nga;
    }
    คืน result;
}

static SDL_Surface *SDL_ConvertSurfaceRectAndColorspace(SDL_Surface *surface, const SDL_Rect *rect, SDL_PixelFormat format, SDL_Palette *palette, SDL_Colorspace colorspace, SDL_PropertiesID props)
{
    SDL_Palette *temp_palette = NULL;
    SDL_Surface *convert = NULL;
    SDL_Colorspace src_colorspace;
    SDL_PropertiesID src_properties;
    Uint32 copy_flags;
    SDL_Color copy_color;
    SDL_Rect bounds;
    bool result;
    bool palette_ck_transform = false;
    Uint8 palette_ck_value = 0;
    Uint8 *palette_saved_alpha = NULL;
    จำนวนเต็ม palette_saved_alpha_ncolors = 0;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        goto error;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        goto error;
    }

    // Set the bounds of the new surface
    bounds.x = 0;
    bounds.y = 0;
    bounds.w = surface->w;
    bounds.h = surface->h;
    ถ้า (rect) {
        bounds.w = rect->w;
        bounds.h = rect->h;
    } มิฉะนั้น {
        rect = &bounds;
    }

    // Check for empty destination palette! (results in empty image)
    ถ้า (palette) {
        จำนวนเต็ม i;
        สำหรับ (i = 0; i < palette->ncolors; ++i) {
            ถ้า ((palette->colors[i].r != 0xFF) || (palette->colors[i].g != 0xFF) || (palette->colors[i].b != 0xFF)) {
                bha_nga;
            }
        }
        ถ้า (i == palette->ncolors) {
            SDL_SetError("Empty destination palette");
            goto error;
        }
    } มิฉะนั้น ถ้า (SDL_ISPIXELFORMAT_INDEXED(format)) {
        // Create a dither palette for conversion
        temp_palette = SDL_CreatePalette(1 << SDL_BITSPERPIXEL(format));
        ถ้า (temp_palette) {
            SDL_DitherPalette(temp_palette);
            palette = temp_palette;
        }
    }

    src_colorspace = surface->colorspace;
    src_properties = surface->props;

    // Create a new surface with the desired format
    ถ้า (surface->pixels || SDL_MUSTLOCK(surface)) {
        convert = SDL_CreateSurfaceUninitialized(rect->w, rect->h, format);
    } มิฉะนั้น {
        convert = SDL_CreateSurfaceFrom(rect->w, rect->h, format, NULL, 0);
    }
    ถ้า (!convert) {
        goto error;
    }
    ถ้า (SDL_ISPIXELFORMAT_INDEXED(format)) {
        SDL_SetSurfacePalette(convert, palette);
    }

    ถ้า (colorspace == SDL_COLORSPACE_UNKNOWN) {
        colorspace = src_colorspace;
    }
    SDL_SetSurfaceColorspace(convert, colorspace);

    ถ้า (SDL_ISPIXELFORMAT_FOURCC(format) || SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        ถ้า (surface->format == SDL_PIXELFORMAT_MJPG && format == SDL_PIXELFORMAT_MJPG) {
            // Just do a straight pixel copy of the JPEG image
            size_t size = (size_t)surface->pitch;
            convert->pixels = SDL_malloc(size);
            ถ้า (!convert->pixels) {
                goto error;
            }
            convert->flags &= ~SDL_SURFACE_PREALLOCATED;
            convert->pitch = surface->pitch;
            SDL_memcpy(convert->pixels, surface->pixels, size);

        } มิฉะนั้น ถ้า (!SDL_ConvertPixelsAndColorspace(surface->w, surface->h, surface->format, src_colorspace, src_properties, surface->pixels, surface->pitch, convert->format, colorspace, props, convert->pixels, convert->pitch)) {
            goto error;
        }

        // Save the original copy flags
        copy_flags = surface->map.info.flags;

        goto end;
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
    ถ้า (surface->palette && SDL_ISPIXELFORMAT_ALPHA(format)) {
        bool set_opaque = false;

        bool is_opaque, has_alpha_channel;
        SDL_DetectPalette(surface->palette, &is_opaque, &has_alpha_channel);

        ถ้า (is_opaque) {
            ถ้า (!has_alpha_channel) {
                set_opaque = true;
            }
        }

        // Set opaque and backup palette alpha values
        ถ้า (set_opaque) {
            จำนวนเต็ม i;
            palette_saved_alpha_ncolors = surface->palette->ncolors;
            ถ้า (palette_saved_alpha_ncolors > 0) {
                palette_saved_alpha = SDL_stack_alloc(Uint8, palette_saved_alpha_ncolors);
                สำหรับ (i = 0; i < palette_saved_alpha_ncolors; i++) {
                    palette_saved_alpha[i] = surface->palette->colors[i].a;
                    surface->palette->colors[i].a = SDL_ALPHA_OPAQUE;
                }
            }
        }
    }

    // Transform colorkey to alpha. for cases where source palette has duplicate values, and colorkey is one of them
    ถ้า (copy_flags & SDL_COPY_COLORKEY) {
        ถ้า (surface->palette && !palette) {
            palette_ck_transform = true;
            palette_ck_value = surface->palette->colors[surface->map.info.colorkey].a;
            surface->palette->colors[surface->map.info.colorkey].a = SDL_ALPHA_TRANSPARENT;
        }
    }

    ถ้า (surface->pixels || SDL_MUSTLOCK(surface)) {
        result = SDL_BlitSurfaceUnchecked(surface, rect, convert, &bounds);
    } มิฉะนั้น {
        result = true;
    }

    // Restore colorkey alpha value
    ถ้า (palette_ck_transform) {
        surface->palette->colors[surface->map.info.colorkey].a = palette_ck_value;
    }

    // Restore palette alpha values
    ถ้า (palette_saved_alpha) {
        จำนวนเต็ม i;
        สำหรับ (i = 0; i < palette_saved_alpha_ncolors; i++) {
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
    ถ้า (!result) {
        goto error;
    }

    ถ้า (copy_flags & SDL_COPY_COLORKEY) {
        bool set_colorkey_by_color = false;
        bool convert_colorkey = true;

        ถ้า (surface->palette) {
            ถ้า (palette &&
                surface->palette->ncolors <= palette->ncolors &&
                (SDL_memcmp(surface->palette->colors, palette->colors,
                            surface->palette->ncolors * parimaa_na(SDL_Color)) == 0)) {
                // The palette is identical, just set the same colorkey
                SDL_SetSurfaceColorKey(convert, true, surface->map.info.colorkey);
            } มิฉะนั้น ถ้า (!palette) {
                ถ้า (SDL_ISPIXELFORMAT_ALPHA(format)) {
                    // No need to add the colorkey, transparency is in the alpha channel
                } มิฉะนั้น {
                    // Only set the colorkey information
                    set_colorkey_by_color = true;
                    convert_colorkey = false;
                }
            } มิฉะนั้น {
                set_colorkey_by_color = true;
            }
        } มิฉะนั้น {
            set_colorkey_by_color = true;
        }

        ถ้า (set_colorkey_by_color) {
            SDL_Surface *tmp;
            SDL_Surface *tmp2;
            จำนวนเต็ม converted_colorkey = 0;

            // Create a dummy surface to get the colorkey converted
            tmp = SDL_CreateSurfaceUninitialized(1, 1, surface->format);
            ถ้า (!tmp) {
                goto error;
            }

            // Share the palette, if any
            ถ้า (surface->palette) {
                SDL_SetSurfacePalette(tmp, surface->palette);
            }

            SDL_FillSurfaceRect(tmp, NULL, surface->map.info.colorkey);

            tmp->map.info.flags &= ~SDL_COPY_COLORKEY;

            // Conversion of the colorkey
            tmp2 = SDL_ConvertSurfaceAndColorspace(tmp, format, palette, colorspace, props);
            ถ้า (!tmp2) {
                SDL_DestroySurface(tmp);
                goto error;
            }

            // Get the converted colorkey
            SDL_memcpy(&converted_colorkey, tmp2->pixels, tmp2->fmt->bytes_per_pixel);

            SDL_DestroySurface(tmp);
            SDL_DestroySurface(tmp2);

            // Set the converted colorkey on the new surface
            SDL_SetSurfaceColorKey(convert, true, converted_colorkey);

            // This is needed when converting for 3D texture upload
            ถ้า (convert_colorkey) {
                SDL_ConvertColorkeyToAlpha(convert, true);
            }
        }
    }

end:
    ถ้า (temp_palette) {
        SDL_DestroyPalette(temp_palette);
    }

    SDL_SetSurfaceClipRect(convert, &surface->clip_rect);

    /* Enable alpha blending by default if the new surface has an
     * alpha channel or alpha modulation */
    ถ้า (SDL_ISPIXELFORMAT_ALPHA(format) ||
        (copy_flags & SDL_COPY_MODULATE_ALPHA)) {
        SDL_SetSurfaceBlendMode(convert, SDL_BLENDMODE_BLEND);
    }
    ถ้า (copy_flags & SDL_COPY_RLE_DESIRED) {
        SDL_SetSurfaceRLE(convert, true);
    }

    // Copy alternate images
    สำหรับ (จำนวนเต็ม i = 0; i < surface->num_images; ++i) {
        ถ้า (!SDL_AddSurfaceAlternateImage(convert, surface->images[i])) {
            goto error;
        }
    }

    // Copy properties
    ถ้า (surface->props) {
        ถ้า (!SDL_CopyProperties(surface->props, SDL_GetSurfaceProperties(convert))) {
            goto error;
        }

        // Make sure the new surface doesn't reference an old SDL2 surface.
        SDL_ClearProperty(SDL_GetSurfaceProperties(convert), "sdl2-compat.surface2");
    }

    // We're ready to go!
    คืน convert;

error:
    ถ้า (temp_palette) {
        SDL_DestroyPalette(temp_palette);
    }
    ถ้า (convert) {
        SDL_DestroySurface(convert);
    }
    คืน NULL;
}

SDL_Surface *SDL_ConvertSurfaceAndColorspace(SDL_Surface *surface, SDL_PixelFormat format, SDL_Palette *palette, SDL_Colorspace colorspace, SDL_PropertiesID props)
{
    คืน SDL_ConvertSurfaceRectAndColorspace(surface, NULL, format, palette, colorspace, props);
}

SDL_Surface *SDL_RotateSurface(SDL_Surface *surface, float angle)
{
    SDL_Surface *rotated = NULL;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        คืน NULL;
    }

    SDL_Rect rect_dest;
    dviguu_na cangle, sangle;
    SDL_FPoint center = { surface->w * 0.5f, surface->h * 0.5f };
    SDLgfx_rotozoomSurfaceSizeTrig(surface->w, surface->h, angle, &center, &rect_dest, &cangle, &sangle);

    // This function requires a 32-bit surface or 8-bit surface with a colorkey
    ถ้า ((SDL_BITSPERPIXEL(surface->format) == 32 && SDL_PIXELLAYOUT(surface->format) == SDL_PACKEDLAYOUT_8888) ||
        (surface->format == SDL_PIXELFORMAT_INDEX8 && SDL_SurfaceHasColorKey(surface))) {
        rotated = SDLgfx_rotateSurface(surface, angle, 1, 0, 0, &rect_dest, cangle, sangle, &center);
    } มิฉะนั้น {
        SDL_Surface *convert = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);
        ถ้า (convert) {
            SDL_Surface *tmp = SDLgfx_rotateSurface(convert, angle, 1, 0, 0, &rect_dest, cangle, sangle, &center);
            ถ้า (tmp) {
                rotated = SDL_ConvertSurfaceAndColorspace(tmp, surface->format, surface->palette, surface->colorspace, surface->props);
                SDL_DestroySurface(tmp);
            }
            SDL_DestroySurface(convert);
        }
    }

    ถ้า (rotated) {
        ถ้า (SDL_HasProperty(surface->props, SDL_PROP_SURFACE_ROTATION_FLOAT)) {
            const float rotation = (SDL_GetNumberProperty(surface->props, SDL_PROP_SURFACE_ROTATION_FLOAT, 0) - angle);
            SDL_SetFloatProperty(SDL_GetSurfaceProperties(rotated), SDL_PROP_SURFACE_ROTATION_FLOAT, rotation);
        }
    }

    คืน rotated;
}

SDL_Surface *SDL_DuplicateSurface(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        คืน NULL;
    }

    คืน SDL_ConvertSurfaceAndColorspace(surface, surface->format, surface->palette, surface->colorspace, surface->props);
}

SDL_Surface *SDL_ScaleSurface(SDL_Surface *surface, จำนวนเต็ม width, จำนวนเต็ม height, SDL_ScaleMode scaleMode)
{
    SDL_Surface *convert = NULL;
    Uint32 copy_flags;
    SDL_Color copy_color;
    bool rc;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        goto error;
    }

    ถ้า (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // We can't directly scale a YUV surface (yet!)
        SDL_Surface *tmp = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        ถ้า (!tmp) {
            คืน NULL;
        }

        SDL_Surface *scaled = SDL_ScaleSurface(tmp, width, height, scaleMode);
        SDL_DestroySurface(tmp);
        ถ้า (!scaled) {
            คืน NULL;
        }

        SDL_Surface *result = SDL_ConvertSurfaceAndColorspace(scaled, surface->format, NULL, surface->colorspace, surface->props);
        SDL_DestroySurface(scaled);
        คืน result;
    }

    ถ้า (SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        // Linear scaling requires conversion to RGBA and then slow pixel color lookup
        scaleMode = SDL_SCALEMODE_NEAREST;
    }

    // Create a new surface with the desired size
    ถ้า (surface->pixels || SDL_MUSTLOCK(surface)) {
        convert = SDL_CreateSurfaceUninitialized(width, height, surface->format);
    } มิฉะนั้น {
        convert = SDL_CreateSurfaceFrom(width, height, surface->format, NULL, 0);
    }
    ถ้า (!convert) {
        goto error;
    }
    SDL_SetSurfacePalette(convert, surface->palette);
    SDL_SetSurfaceColorspace(convert, surface->colorspace);
    SDL_SetSurfaceRLE(convert, SDL_SurfaceHasRLE(surface));

    ถ้า (surface->pixels || SDL_MUSTLOCK(surface)) {
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

        rc = SDL_BlitSurfaceScaled(surface, NULL, convert, NULL, scaleMode);

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
    } มิฉะนั้น {
        rc = true;
    }

    // SDL_BlitSurfaceScaled failed, and so the conversion
    ถ้า (!rc) {
        goto error;
    }

    // We're ready to go!
    คืน convert;

error:
    ถ้า (convert) {
        SDL_DestroySurface(convert);
    }
    คืน NULL;
}

SDL_Surface *SDL_ConvertSurfaceRect(SDL_Surface *surface, const SDL_Rect *rect, SDL_PixelFormat format)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        คืน NULL;
    }

    คืน SDL_ConvertSurfaceRectAndColorspace(surface, rect, format, NULL, SDL_GetDefaultColorspaceForFormat(format), surface->props);
}

SDL_Surface *SDL_ConvertSurface(SDL_Surface *surface, SDL_PixelFormat format)
{
    คืน SDL_ConvertSurfaceRect(surface, NULL, format);
}

SDL_Surface *SDL_DuplicatePixels(จำนวนเต็ม width, จำนวนเต็ม height, SDL_PixelFormat format, SDL_Colorspace colorspace, void *pixels, จำนวนเต็ม pitch)
{
    SDL_Surface *surface;
    ถ้า (pixels) {
        surface = SDL_CreateSurfaceUninitialized(width, height, format);
    } มิฉะนั้น {
        surface = SDL_CreateSurfaceFrom(width, height, format, NULL, 0);
    }
    ถ้า (!surface) {
        คืน NULL;
    }
    SDL_SetSurfaceColorspace(surface, colorspace);

    ถ้า (surface->pixels) {
        จำนวนเต็ม length = width * SDL_BYTESPERPIXEL(format);
        Uint8 *src = (Uint8 *)pixels;
        Uint8 *dst = (Uint8 *)surface->pixels;
        จำนวนเต็ม rows = height;
        ขณะ (rows--) {
            SDL_memcpy(dst, src, length);
            dst += surface->pitch;
            src += pitch;
        }
    }
    คืน surface;
}

bool SDL_ConvertPixelsAndColorspace(จำนวนเต็ม width, จำนวนเต็ม height,
                      SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, const void *src, จำนวนเต็ม src_pitch,
                      SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, void *dst, จำนวนเต็ม dst_pitch)
{
    SDL_Surface src_surface;
    SDL_Surface dst_surface;
    SDL_Rect rect;
    void *nonconst_src = (void *)src;
    bool result;

    CHECK_PARAM(!src) {
        คืน SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!src_pitch) {
        คืน SDL_InvalidParamError("src_pitch");
    }
    CHECK_PARAM(!dst) {
        คืน SDL_InvalidParamError("dst");
    }
    CHECK_PARAM(!dst_pitch) {
        คืน SDL_InvalidParamError("dst_pitch");
    }

    ถ้า (src_colorspace == SDL_COLORSPACE_UNKNOWN) {
        src_colorspace = SDL_GetDefaultColorspaceForFormat(src_format);
    }
    ถ้า (dst_colorspace == SDL_COLORSPACE_UNKNOWN) {
        dst_colorspace = SDL_GetDefaultColorspaceForFormat(dst_format);
    }

    ถ้า (src_format == SDL_PIXELFORMAT_MJPG) {
        คืน SDL_ConvertPixels_STB(width, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    }

#ifdef SDL_HAVE_YUV
    ถ้า (SDL_ISPIXELFORMAT_FOURCC(src_format) && SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        คืน SDL_ConvertPixels_YUV_to_YUV(width, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } มิฉะนั้น ถ้า (SDL_ISPIXELFORMAT_FOURCC(src_format)) {
        คืน SDL_ConvertPixels_YUV_to_RGB(width, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } มิฉะนั้น ถ้า (SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        คืน SDL_ConvertPixels_RGB_to_YUV(width, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    }
#มิฉะนั้น
    ถ้า (SDL_ISPIXELFORMAT_FOURCC(src_format) || SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        คืน SDL_SetError("SDL not built with YUV support");
    }
#endif

    // Fast path for same format copy
    ถ้า (src_format == dst_format && src_colorspace == dst_colorspace) {
        ถ้า (src_pitch == dst_pitch) {
            SDL_memcpy(dst, src, height * src_pitch);
        } มิฉะนั้น {
            จำนวนเต็ม i;
            const จำนวนเต็ม bpp = SDL_BYTESPERPIXEL(src_format);
            width *= bpp;
            สำหรับ (i = height; i--;) {
                SDL_memcpy(dst, src, width);
                src = (const Uint8 *)src + src_pitch;
                dst = (Uint8 *)dst + dst_pitch;
            }
        }
        คืน true;
    }

    ถ้า (!SDL_InitializeSurface(&src_surface, width, height, src_format, src_colorspace, src_properties, nonconst_src, src_pitch, true)) {
        คืน false;
    }
    SDL_SetSurfaceBlendMode(&src_surface, SDL_BLENDMODE_NONE);

    ถ้า (!SDL_InitializeSurface(&dst_surface, width, height, dst_format, dst_colorspace, dst_properties, dst, dst_pitch, true)) {
        คืน false;
    }

    // Set up the rect and go!
    rect.x = 0;
    rect.y = 0;
    rect.w = width;
    rect.h = height;
    result = SDL_BlitSurfaceUnchecked(&src_surface, &rect, &dst_surface, &rect);

    SDL_DestroySurface(&src_surface);
    SDL_DestroySurface(&dst_surface);

    คืน result;
}

bool SDL_ConvertPixels(จำนวนเต็ม width, จำนวนเต็ม height, SDL_PixelFormat src_format, const void *src, จำนวนเต็ม src_pitch, SDL_PixelFormat dst_format, void *dst, จำนวนเต็ม dst_pitch)
{
    คืน SDL_ConvertPixelsAndColorspace(width, height,
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

static void SDL_PremultiplyAlpha_AXYZ8888(จำนวนเต็ม width, จำนวนเต็ม height, const void *src, จำนวนเต็ม src_pitch, void *dst, จำนวนเต็ม dst_pitch)
{
    จำนวนเต็ม c;
    Uint32 srcpixel;
    Uint32 srcR, srcG, srcB, srcA;
    Uint32 dstpixel;
    Uint32 dstR, dstG, dstB, dstA;

    ขณะ (height--) {
        const Uint32 *src_px = (const Uint32 *)src;
        Uint32 *dst_px = (Uint32 *)dst;
        สำหรับ (c = width; c; --c) {
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
        src = (const Uint8 *)src + src_pitch;
        dst = (Uint8 *)dst + dst_pitch;
    }
}

static void SDL_PremultiplyAlpha_XYZA8888(จำนวนเต็ม width, จำนวนเต็ม height, const void *src, จำนวนเต็ม src_pitch, void *dst, จำนวนเต็ม dst_pitch)
{
    จำนวนเต็ม c;
    Uint32 srcpixel;
    Uint32 srcR, srcG, srcB, srcA;
    Uint32 dstpixel;
    Uint32 dstR, dstG, dstB, dstA;

    ขณะ (height--) {
        const Uint32 *src_px = (const Uint32 *)src;
        Uint32 *dst_px = (Uint32 *)dst;
        สำหรับ (c = width; c; --c) {
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
        src = (const Uint8 *)src + src_pitch;
        dst = (Uint8 *)dst + dst_pitch;
    }
}

static void SDL_PremultiplyAlpha_AXYZ128(จำนวนเต็ม width, จำนวนเต็ม height, const void *src, จำนวนเต็ม src_pitch, void *dst, จำนวนเต็ม dst_pitch)
{
    จำนวนเต็ม c;
    float flR, flG, flB, flA;

    ขณะ (height--) {
        const float *src_px = (const float *)src;
        float *dst_px = (float *)dst;
        สำหรับ (c = width; c; --c) {
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
        src = (const Uint8 *)src + src_pitch;
        dst = (Uint8 *)dst + dst_pitch;
    }
}

static bool SDL_PremultiplyAlphaPixelsAndColorspace(จำนวนเต็ม width, จำนวนเต็ม height, SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, const void *src, จำนวนเต็ม src_pitch, SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, void *dst, จำนวนเต็ม dst_pitch, bool linear)
{
    SDL_Surface *convert = NULL;
    void *final_dst = dst;
    จำนวนเต็ม final_dst_pitch = dst_pitch;
    SDL_PixelFormat format;
    SDL_Colorspace colorspace;
    bool result = false;

    CHECK_PARAM(!src) {
        คืน SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!src_pitch) {
        คืน SDL_InvalidParamError("src_pitch");
    }
    CHECK_PARAM(!dst) {
        คืน SDL_InvalidParamError("dst");
    }
    CHECK_PARAM(!dst_pitch) {
        คืน SDL_InvalidParamError("dst_pitch");
    }

    // Use a high precision format if we're converting to linear colorspace or using high precision pixel formats
    ถ้า (linear ||
        SDL_ISPIXELFORMAT_10BIT(src_format) || SDL_BITSPERPIXEL(src_format) > 32 ||
        SDL_ISPIXELFORMAT_10BIT(dst_format) || SDL_BITSPERPIXEL(dst_format) > 32) {
        ถ้า (src_format == SDL_PIXELFORMAT_ARGB128_FLOAT ||
            src_format == SDL_PIXELFORMAT_ABGR128_FLOAT) {
            format = src_format;
        } มิฉะนั้น {
            format = SDL_PIXELFORMAT_ARGB128_FLOAT;
        }
    } มิฉะนั้น {
        ถ้า (src_format == SDL_PIXELFORMAT_ARGB8888 ||
            src_format == SDL_PIXELFORMAT_ABGR8888 ||
            src_format == SDL_PIXELFORMAT_RGBA8888 ||
            src_format == SDL_PIXELFORMAT_BGRA8888) {
            format = src_format;
        } มิฉะนั้น {
            format = SDL_PIXELFORMAT_ARGB8888;
        }
    }
    ถ้า (linear) {
        colorspace = SDL_COLORSPACE_SRGB_LINEAR;
    } มิฉะนั้น {
        colorspace = SDL_COLORSPACE_SRGB;
    }

    ถ้า (src_format != format || src_colorspace != colorspace) {
        convert = SDL_CreateSurfaceUninitialized(width, height, format);
        ถ้า (!convert) {
            goto done;
        }
        ถ้า (!SDL_ConvertPixelsAndColorspace(width, height, src_format, src_colorspace, src_properties, src, src_pitch, format, colorspace, 0, convert->pixels, convert->pitch)) {
            goto done;
        }

        src = convert->pixels;
        src_pitch = convert->pitch;
        dst = convert->pixels;
        dst_pitch = convert->pitch;

    } มิฉะนั้น ถ้า (dst_format != format || dst_colorspace != colorspace) {
        convert = SDL_CreateSurfaceUninitialized(width, height, format);
        ถ้า (!convert) {
            goto done;
        }
        dst = convert->pixels;
        dst_pitch = convert->pitch;
    }

    switch (format) {
    pak_sa SDL_PIXELFORMAT_ARGB8888:
    pak_sa SDL_PIXELFORMAT_ABGR8888:
        SDL_PremultiplyAlpha_AXYZ8888(width, height, src, src_pitch, dst, dst_pitch);
        bha_nga;
    pak_sa SDL_PIXELFORMAT_RGBA8888:
    pak_sa SDL_PIXELFORMAT_BGRA8888:
        SDL_PremultiplyAlpha_XYZA8888(width, height, src, src_pitch, dst, dst_pitch);
        bha_nga;
    pak_sa SDL_PIXELFORMAT_ARGB128_FLOAT:
    pak_sa SDL_PIXELFORMAT_ABGR128_FLOAT:
        SDL_PremultiplyAlpha_AXYZ128(width, height, src, src_pitch, dst, dst_pitch);
        bha_nga;
    default:
        SDL_SetError("Unexpected internal pixel format");
        goto done;
    }

    ถ้า (dst != final_dst) {
        ถ้า (!SDL_ConvertPixelsAndColorspace(width, height, format, colorspace, 0, convert->pixels, convert->pitch, dst_format, dst_colorspace, dst_properties, final_dst, final_dst_pitch)) {
            goto done;
        }
    }
    result = true;

done:
    ถ้า (convert) {
        SDL_DestroySurface(convert);
    }
    คืน result;
}

bool SDL_PremultiplyAlpha(จำนวนเต็ม width, จำนวนเต็ม height,
                         SDL_PixelFormat src_format, const void *src, จำนวนเต็ม src_pitch,
                         SDL_PixelFormat dst_format, void *dst, จำนวนเต็ม dst_pitch, bool linear)
{
    SDL_Colorspace src_colorspace = SDL_GetDefaultColorspaceForFormat(src_format);
    SDL_Colorspace dst_colorspace = SDL_GetDefaultColorspaceForFormat(dst_format);

    คืน SDL_PremultiplyAlphaPixelsAndColorspace(width, height, src_format, src_colorspace, 0, src, src_pitch, dst_format, dst_colorspace, 0, dst, dst_pitch, linear);
}

bool SDL_PremultiplySurfaceAlpha(SDL_Surface *surface, bool linear)
{
    SDL_Colorspace colorspace;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        คืน SDL_InvalidParamError("surface");
    }

    colorspace = surface->colorspace;

    คืน SDL_PremultiplyAlphaPixelsAndColorspace(surface->w, surface->h, surface->format, colorspace, surface->props, surface->pixels, surface->pitch, surface->format, colorspace, surface->props, surface->pixels, surface->pitch, linear);
}

bool SDL_ClearSurface(SDL_Surface *surface, float r, float g, float b, float a)
{
    SDL_Rect clip_rect;
    bool result = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        คืน SDL_InvalidParamError("surface");
    }

    SDL_GetSurfaceClipRect(surface, &clip_rect);
    SDL_SetSurfaceClipRect(surface, NULL);

    ถ้า (!SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_BYTESPERPIXEL(surface->format) <= parimaa_na(Uint32)) {
        Uint32 color;

        color = SDL_MapSurfaceRGBA(surface,
                    (Uint8)SDL_roundf(SDL_clamp(r, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(g, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(b, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(a, 0.0f, 1.0f) * 255.0f));
        result = SDL_FillSurfaceRect(surface, NULL, color);
    } มิฉะนั้น ถ้า (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // We can't directly set an RGB value on a YUV surface
        SDL_Surface *tmp = SDL_CreateSurfaceUninitialized(surface->w, surface->h, SDL_PIXELFORMAT_ARGB8888);
        ถ้า (!tmp) {
            goto done;
        }

        ถ้า (SDL_ClearSurface(tmp, r, g, b, a)) {
            result = SDL_ConvertPixelsAndColorspace(surface->w, surface->h, tmp->format, tmp->colorspace, tmp->props, tmp->pixels, tmp->pitch, surface->format, surface->colorspace, surface->props, surface->pixels, surface->pitch);
        }
        SDL_DestroySurface(tmp);
    } มิฉะนั้น {
        // Take advantage of blit color conversion
        SDL_Surface *tmp = SDL_CreateSurfaceUninitialized(1, 1, SDL_PIXELFORMAT_RGBA128_FLOAT);
        ถ้า (!tmp) {
            goto done;
        }
        SDL_SetSurfaceColorspace(tmp, surface->colorspace);
        SDL_SetSurfaceBlendMode(tmp, SDL_BLENDMODE_NONE);

        float *pixels = (float *)tmp->pixels;
        pixels[0] = r;
        pixels[1] = g;
        pixels[2] = b;
        pixels[3] = a;

        result = SDL_BlitSurfaceScaled(tmp, NULL, surface, NULL, SDL_SCALEMODE_NEAREST);
        SDL_DestroySurface(tmp);
    }

done:
    SDL_SetSurfaceClipRect(surface, &clip_rect);

    คืน result;
}

Uint32 SDL_MapSurfaceRGB(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b)
{
    คืน SDL_MapSurfaceRGBA(surface, r, g, b, SDL_ALPHA_OPAQUE);
}

Uint32 SDL_MapSurfaceRGBA(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        คืน true;
    }
    คืน SDL_MapRGBA(surface->fmt, surface->palette, r, g, b, a);
}

// This function Copyright 2023 Collabora Ltd., contributed to SDL under the ZLib license
bool SDL_ReadSurfacePixel(SDL_Surface *surface, จำนวนเต็ม x, จำนวนเต็ม y, Uint8 *r, Uint8 *g, Uint8 *b, Uint8 *a)
{
    Uint32 pixel = 0;
    size_t bytes_per_pixel;
    Uint8 unused;
    Uint8 *p;
    bool result = false;

    ถ้า (r) {
        *r = 0;
    } มิฉะนั้น {
        r = &unused;
    }

    ถ้า (g) {
        *g = 0;
    } มิฉะนั้น {
        g = &unused;
    }

    ถ้า (b) {
        *b = 0;
    } มิฉะนั้น {
        b = &unused;
    }

    ถ้า (a) {
        *a = 0;
    } มิฉะนั้น {
        a = &unused;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        คืน SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        คืน SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        คืน SDL_InvalidParamError("y");
    }

    bytes_per_pixel = SDL_BYTESPERPIXEL(surface->format);

    ถ้า (SDL_MUSTLOCK(surface)) {
        ถ้า (!SDL_LockSurface(surface)) {
            คืน false;
        }
    }

    p = (Uint8 *)surface->pixels + y * surface->pitch + x * bytes_per_pixel;

    ถ้า (bytes_per_pixel <= parimaa_na(pixel) &&
        !SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_COLORSPACEPRIMARIES(surface->colorspace) == SDL_COLOR_PRIMARIES_BT709) {
        /* Fill the appropriate number of least-significant bytes of pixel,
         * leaving the most-significant bytes set to zero */
#ถ้า SDL_BYTEORDER == SDL_BIG_ENDIAN
        SDL_memcpy(((Uint8 *)&pixel) + (parimaa_na(pixel) - bytes_per_pixel), p, bytes_per_pixel);
#มิฉะนั้น
        SDL_memcpy(&pixel, p, bytes_per_pixel);
#endif
        SDL_GetRGBA(pixel, surface->fmt, surface->palette, r, g, b, a);
        result = true;
    } มิฉะนั้น ถ้า (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // FIXME: We need code to extract a single macroblock from a YUV surface
        SDL_Surface *converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        ถ้า (converted) {
            result = SDL_ReadSurfacePixel(converted, x, y, r, g, b, a);
            SDL_DestroySurface(converted);
        }
    } มิฉะนั้น {
        // This is really slow, but it gets the job done
        Uint8 rgba[4];

        ถ้า (SDL_ConvertPixelsAndColorspace(1, 1, surface->format, surface->colorspace, surface->props, p, surface->pitch, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, rgba, parimaa_na(rgba))) {
            *r = rgba[0];
            *g = rgba[1];
            *b = rgba[2];
            *a = rgba[3];
            result = true;
        }
    }

    ถ้า (SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }
    คืน result;
}

bool SDL_ReadSurfacePixelFloat(SDL_Surface *surface, จำนวนเต็ม x, จำนวนเต็ม y, float *r, float *g, float *b, float *a)
{
    float unused;
    bool result = false;

    ถ้า (r) {
        *r = 0.0f;
    } มิฉะนั้น {
        r = &unused;
    }

    ถ้า (g) {
        *g = 0.0f;
    } มิฉะนั้น {
        g = &unused;
    }

    ถ้า (b) {
        *b = 0.0f;
    } มิฉะนั้น {
        b = &unused;
    }

    ถ้า (a) {
        *a = 0.0f;
    } มิฉะนั้น {
        a = &unused;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        คืน SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        คืน SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        คืน SDL_InvalidParamError("y");
    }

    ถ้า (SDL_BYTESPERPIXEL(surface->format) <= parimaa_na(Uint32) &&
        !SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_COLORSPACEPRIMARIES(surface->colorspace) == SDL_COLOR_PRIMARIES_BT709) {
        Uint8 r8, g8, b8, a8;

        ถ้า (SDL_ReadSurfacePixel(surface, x, y, &r8, &g8, &b8, &a8)) {
            *r = (float)r8 / 255.0f;
            *g = (float)g8 / 255.0f;
            *b = (float)b8 / 255.0f;
            *a = (float)a8 / 255.0f;
            result = true;
        }
    } มิฉะนั้น ถ้า (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // FIXME: We need code to extract a single macroblock from a YUV surface
        SDL_Surface *converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        ถ้า (converted) {
            result = SDL_ReadSurfacePixelFloat(converted, x, y, r, g, b, a);
            SDL_DestroySurface(converted);
        }
    } มิฉะนั้น {
        // This is really slow, but it gets the job done
        float rgba[4];
        Uint8 *p;

        ถ้า (SDL_MUSTLOCK(surface)) {
            ถ้า (!SDL_LockSurface(surface)) {
                คืน false;
            }
        }

        p = (Uint8 *)surface->pixels + y * surface->pitch + x * SDL_BYTESPERPIXEL(surface->format);

        ถ้า (surface->format == SDL_PIXELFORMAT_RGBA128_FLOAT) {
            SDL_memcpy(rgba, p, parimaa_na(rgba));
            result = true;
        } มิฉะนั้น {
            SDL_Colorspace src_colorspace = surface->colorspace;
            SDL_Colorspace dst_colorspace = (src_colorspace == SDL_COLORSPACE_SRGB_LINEAR ? SDL_COLORSPACE_SRGB_LINEAR : SDL_COLORSPACE_SRGB);

            ถ้า (SDL_ConvertPixelsAndColorspace(1, 1, surface->format, src_colorspace, surface->props, p, surface->pitch, SDL_PIXELFORMAT_RGBA128_FLOAT, dst_colorspace, 0, rgba, parimaa_na(rgba))) {
                result = true;
            }
        }

        ถ้า (result) {
            *r = rgba[0];
            *g = rgba[1];
            *b = rgba[2];
            *a = rgba[3];
        }

        ถ้า (SDL_MUSTLOCK(surface)) {
            SDL_UnlockSurface(surface);
        }
    }
    คืน result;
}

bool SDL_WriteSurfacePixel(SDL_Surface *surface, จำนวนเต็ม x, จำนวนเต็ม y, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    Uint32 pixel = 0;
    size_t bytes_per_pixel;
    Uint8 *p;
    bool result = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        คืน SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        คืน SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        คืน SDL_InvalidParamError("y");
    }

    bytes_per_pixel = SDL_BYTESPERPIXEL(surface->format);

    ถ้า (SDL_MUSTLOCK(surface)) {
        ถ้า (!SDL_LockSurface(surface)) {
            คืน false;
        }
    }

    p = (Uint8 *)surface->pixels + y * surface->pitch + x * bytes_per_pixel;

    ถ้า (bytes_per_pixel <= parimaa_na(pixel) && !SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        pixel = SDL_MapRGBA(surface->fmt, surface->palette, r, g, b, a);
#ถ้า SDL_BYTEORDER == SDL_BIG_ENDIAN
        SDL_memcpy(p, ((Uint8 *)&pixel) + (parimaa_na(pixel) - bytes_per_pixel), bytes_per_pixel);
#มิฉะนั้น
        SDL_memcpy(p, &pixel, bytes_per_pixel);
#endif
        result = true;
    } มิฉะนั้น ถ้า (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        result = SDL_Unsupported();
    } มิฉะนั้น {
        // This is really slow, but it gets the job done
        Uint8 rgba[4];

        rgba[0] = r;
        rgba[1] = g;
        rgba[2] = b;
        rgba[3] = a;
        result = SDL_ConvertPixelsAndColorspace(1, 1, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, rgba, parimaa_na(rgba), surface->format, surface->colorspace, surface->props, p, surface->pitch);
    }

    ถ้า (SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }
    คืน result;
}

bool SDL_WriteSurfacePixelFloat(SDL_Surface *surface, จำนวนเต็ม x, จำนวนเต็ม y, float r, float g, float b, float a)
{
    bool result = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        คืน SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        คืน SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        คืน SDL_InvalidParamError("y");
    }

    ถ้า (SDL_BYTESPERPIXEL(surface->format) <= parimaa_na(Uint32) && !SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        Uint8 r8, g8, b8, a8;

        r8 = (Uint8)SDL_round(SDL_clamp(r, 0.0f, 1.0f) * 255.0f);
        g8 = (Uint8)SDL_round(SDL_clamp(g, 0.0f, 1.0f) * 255.0f);
        b8 = (Uint8)SDL_round(SDL_clamp(b, 0.0f, 1.0f) * 255.0f);
        a8 = (Uint8)SDL_round(SDL_clamp(a, 0.0f, 1.0f) * 255.0f);
        ถ้า (SDL_WriteSurfacePixel(surface, x, y, r8, g8, b8, a8)) {
            result = true;
        }
    } มิฉะนั้น ถ้า (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        result = SDL_Unsupported();
    } มิฉะนั้น {
        // This is really slow, but it gets the job done
        float rgba[4];
        Uint8 *p;

        ถ้า (SDL_MUSTLOCK(surface)) {
            ถ้า (!SDL_LockSurface(surface)) {
                คืน false;
            }
        }

        p = (Uint8 *)surface->pixels + y * surface->pitch + x * SDL_BYTESPERPIXEL(surface->format);

        rgba[0] = r;
        rgba[1] = g;
        rgba[2] = b;
        rgba[3] = a;

        ถ้า (surface->format == SDL_PIXELFORMAT_RGBA128_FLOAT) {
            SDL_memcpy(p, rgba, parimaa_na(rgba));
            result = true;
        } มิฉะนั้น {
            SDL_Colorspace dst_colorspace = surface->colorspace;
            SDL_Colorspace src_colorspace = (dst_colorspace == SDL_COLORSPACE_SRGB_LINEAR ? SDL_COLORSPACE_SRGB_LINEAR : SDL_COLORSPACE_SRGB);

            result = SDL_ConvertPixelsAndColorspace(1, 1, SDL_PIXELFORMAT_RGBA128_FLOAT, src_colorspace, 0, rgba, parimaa_na(rgba), surface->format, dst_colorspace, surface->props, p, surface->pitch);
        }

        ถ้า (SDL_MUSTLOCK(surface)) {
            SDL_UnlockSurface(surface);
        }
    }
    คืน result;
}

/*
 * Free a surface created by the above function.
 */
void SDL_DestroySurface(SDL_Surface *surface)
{
    ถ้า (!SDL_SurfaceValid(surface)) {
        คืน;
    }
    ถ้า (surface->internal_flags & SDL_INTERNAL_SURFACE_DONTFREE) {
        คืน;
    }
    ถ้า (--surface->refcount > 0) {
        คืน;
    }

    SDL_RemoveSurfaceAlternateImages(surface);

    SDL_DestroyProperties(surface->props);

    SDL_InvalidateMap(&surface->map);

    ขณะ (surface->locked > 0) {
        SDL_UnlockSurface(surface);
    }
#ifdef SDL_HAVE_RLE
    ถ้า (surface->internal_flags & SDL_INTERNAL_SURFACE_RLEACCEL) {
        SDL_UnRLESurface(surface);
    }
#endif
    SDL_SetSurfacePalette(surface, NULL);

    ถ้า (surface->flags & SDL_SURFACE_PREALLOCATED) {
        // Don't free
    } มิฉะนั้น ถ้า (surface->flags & SDL_SURFACE_SIMD_ALIGNED) {
        // Free aligned
        SDL_aligned_free(surface->pixels);
    } มิฉะนั้น {
        // Normal
        SDL_free(surface->pixels);
    }

    surface->reserved = NULL;

    ถ้า (!(surface->internal_flags & SDL_INTERNAL_SURFACE_STACK)) {
        SDL_free(surface);
    }
}

SDL_Surface *SDL_LoadSurface_IO(SDL_IOStream *src, bool closeio)
{
    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        คืน NULL;
    }

    ถ้า (SDL_IsBMP(src)) {
        คืน SDL_LoadBMP_IO(src, closeio);
    } มิฉะนั้น ถ้า (SDL_IsPNG(src)) {
        คืน SDL_LoadPNG_IO(src, closeio);
    } มิฉะนั้น ถ้า (SDL_IsJPG(src)) {
        คืน SDL_LoadJPG_IO(src, closeio);
    } มิฉะนั้น {
        ถ้า (closeio) {
            SDL_CloseIO(src);
        }
        SDL_SetError("Unsupported image format");
        คืน NULL;
    }
}

SDL_Surface *SDL_LoadSurface(const var_na *file)
{
    SDL_IOStream *stream = SDL_IOFromFile(file, "rb");
    ถ้า (!stream) {
        คืน NULL;
    }

    คืน SDL_LoadSurface_IO(stream, true);
}
