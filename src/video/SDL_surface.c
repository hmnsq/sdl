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
SDL_COMPILE_ویلا_ASSERT(surface_ناپ_assumptions,
                        حجم(صحيح) == حجم(Sint32) && حجم(size_t) >= حجم(Sint32));

SDL_COMPILE_ویلا_ASSERT(can_indicate_حد_توں_ودھ, SDL_ناپ_MAX > SDL_MAX_SINT32);

// Magic!
ساكن حرف SDL_surface_magic;

// Public routines

bool SDL_SurfaceValid(SDL_Surface *surface)
{
    أرجع (surface && surface->reserved == &SDL_surface_magic);
}

فراغ SDL_Update_Surface_جندرا_Flag(SDL_Surface *surface)
{
    // We need to mark the surface as needing unlock while locked
    إذا ((surface->flags & SDL_SURFACE_LOCKED) ||
        (surface->اندرونی_flags & SDL_اندرونی_SURFACE_RLEACCEL)) {
        surface->flags |= SDL_SURFACE_جندرا_NEEDED;
    } وإلا {
        surface->flags &= ~SDL_SURFACE_جندرا_NEEDED;
    }
}

/*
 * Calculate the pad-aligned scanline width of a surface.
 *
 * for FOURCC, use SDL_CalculateYUVSize()
 */
ساكن bool SDL_CalculateRGBSize(Uint32 format, size_t چوڑائی, size_t اچائی, size_t *ناپ, size_t *pitch, bool اقل)
{
    إذا (SDL_BITSPERPIXEL(format) >= 8) {
        إذا (!SDL_ناپ_mul_check_حد_توں_ودھ(چوڑائی, SDL_BYTESPERPIXEL(format), pitch)) {
            أرجع SDL_سیٹ_Error("width * bpp would overflow");
        }
    } وإلا {
        إذا (!SDL_ناپ_mul_check_حد_توں_ودھ(چوڑائی, SDL_BITSPERPIXEL(format), pitch)) {
            أرجع SDL_سیٹ_Error("width * bpp would overflow");
        }
        إذا (!SDL_ناپ_جوڑو_check_حد_توں_ودھ(*pitch, 7, pitch)) {
            أرجع SDL_سیٹ_Error("aligning pitch would overflow");
        }
        *pitch /= 8;
    }
    إذا (!اقل) {
        // 4-byte aligning for speed
        إذا (!SDL_ناپ_جوڑو_check_حد_توں_ودھ(*pitch, 3, pitch)) {
            أرجع SDL_سیٹ_Error("aligning pitch would overflow");
        }
        *pitch &= ~3;
    }

    إذا (!SDL_ناپ_mul_check_حد_توں_ودھ(اچائی, *pitch, ناپ)) {
        أرجع SDL_سیٹ_Error("height * pitch would overflow");
    }

    أرجع true;
}

bool SDL_Calculate_Surface_ناپ(SDL_PixelFormat format, صحيح چوڑائی, صحيح اچائی, size_t *ناپ, size_t *pitch, bool اقل_Pitch)
{
    size_t p = 0, sz = 0;

    إذا (ناپ) {
        *ناپ = 0;
    }

    إذا (pitch) {
        *pitch = 0;
    }

    إذا (SDL_ISPIXELFORMAT_FOURCC(format)) {
        إذا (format == SDL_PIXELFORMAT_MJPG) {
            // We don't know in advance what it will be, we'll figure it out later.
            أرجع true;
        }

        إذا (!SDL_CalculateYUVSize(format, چوڑائی, اچائی, &sz, &p)) {
            // Overflow...
            أرجع false;
        }
    } وإلا {
        إذا (!SDL_CalculateRGBSize(format, چوڑائی, اچائی, &sz, &p, اقل_Pitch)) {
            // Overflow...
            أرجع false;
        }
    }

    إذا (ناپ) {
        *ناپ = sz;
    }

    إذا (pitch) {
        *pitch = p;
    }

    أرجع true;
}

ساكن bool SDL_InitializeSurface(SDL_Surface *surface, صحيح چوڑائی, صحيح اچائی, SDL_PixelFormat format, SDL_Colorspace colorspace, SDL_PropertiesID props, فراغ *pixels, صحيح pitch, bool onstack)
{
    SDL_zerop(surface);

    surface->flags = SDL_SURFACE_PREALLOCATED;
    surface->format = format;
    surface->w = چوڑائی;
    surface->h = اچائی;
    surface->pixels = pixels;
    surface->pitch = pitch;
    surface->reserved = &SDL_surface_magic;

    إذا (onstack) {
        surface->اندرونی_flags |= SDL_اندرونی_SURFACE_ڈھیر;
    }

    surface->fmt = SDL_GetPixelFormatDetails(format);
    إذا (!surface->fmt) {
        SDL_DestroySurface(surface);
        أرجع false;
    }

    // Initialize the clip rect
    surface->clip_rect.w = چوڑائی;
    surface->clip_rect.h = اچائی;

    // Allocate an empty mapping
    surface->map.info.r = 0xFF;
    surface->map.info.g = 0xFF;
    surface->map.info.b = 0xFF;
    surface->map.info.a = 0xFF;

    إذا (colorspace == SDL_COLORSPACE_UNKNOWN) {
        surface->colorspace = SDL_GetDefaultColorspaceForFormat(format);
    } وإلا {
        surface->colorspace = colorspace;
    }

    إذا (props) {
        إذا (!SDL_CopyProperties(props, SDL_GetSurfaceProperties(surface))) {
            SDL_DestroySurface(surface);
            أرجع false;
        }
    }

    // By default surfaces with an alpha mask are set up for blending
    إذا (SDL_ISPIXELFORMAT_ALPHA(surface->format)) {
        SDL_سیٹ_Surface_Blend_منوال(surface, SDL_BLENDMODE_BLEND);
    }

    // The surface is ready to go
    surface->refcount = 1;
    أرجع true;
}

/*
 * Create an empty surface of the appropriate depth using the given format
 */
ساكن SDL_Surface *SDL_Create_Surface_اندرونی(صحيح چوڑائی, صحيح اچائی, SDL_PixelFormat format, bool clear_surface)
{
    size_t pitch, ناپ;
    SDL_Surface *surface;

    CHECK_PARAM(چوڑائی < 0) {
        SDL_InvalidParamError("width");
        أرجع عدم;
    }

    CHECK_PARAM(اچائی < 0) {
        SDL_InvalidParamError("height");
        أرجع عدم;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        أرجع عدم;
    }

    إذا (!SDL_Calculate_Surface_ناپ(format, چوڑائی, اچائی, &ناپ, &pitch, false /* not minimal pitch */)) {
        // Overflow...
        أرجع عدم;
    }

    // Allocate and initialize the surface
    surface = (SDL_Surface *)SDL_malloc(حجم(*surface));
    إذا (!surface) {
        أرجع عدم;
    }

    إذا (!SDL_InitializeSurface(surface, چوڑائی, اچائی, format, SDL_COLORSPACE_UNKNOWN, 0, عدم, (صحيح)pitch, false)) {
        أرجع عدم;
    }

    إذا (surface->w && surface->h && format != SDL_PIXELFORMAT_MJPG) {
        surface->flags &= ~SDL_SURFACE_PREALLOCATED;
        إذا (SDL_GetHintBoolean("SDL_SURFACE_MALLOC", false)) {
            إذا (clear_surface) {
                surface->pixels = SDL_calloc(1, ناپ);
            } وإلا {
                surface->pixels = SDL_malloc(ناپ);
            }
        } وإلا {
            surface->flags |= SDL_SURFACE_SIMD_ALIGNED;
            إذا (clear_surface) {
                surface->pixels = SDL_aligned_alloc_zero(SDL_GetSIMDAlignment(), ناپ);
            } وإلا {
                surface->pixels = SDL_aligned_alloc(SDL_GetSIMDAlignment(), ناپ);
            }
        }
        إذا (!surface->pixels) {
            SDL_DestroySurface(surface);
            أرجع عدم;
        }
    }
    أرجع surface;
}

SDL_Surface *SDL_CreateSurfaceZeroed(صحيح چوڑائی, صحيح اچائی, SDL_PixelFormat format)
{
    أرجع SDL_Create_Surface_اندرونی(چوڑائی, اچائی, format, true);
}

SDL_Surface *SDL_CreateSurfaceUninitialized(صحيح چوڑائی, صحيح اچائی, SDL_PixelFormat format)
{
    أرجع SDL_Create_Surface_اندرونی(چوڑائی, اچائی, format, false);
}

SDL_Surface *SDL_CreateSurface(صحيح چوڑائی, صحيح اچائی, SDL_PixelFormat format)
{
    أرجع SDL_CreateSurfaceZeroed(چوڑائی, اچائی, format);
}


/*
 * Create an RGB surface from an existing memory buffer using the given
 * enum SDL_PIXELFORMAT_* format
 */
SDL_Surface *SDL_CreateSurfaceFrom(صحيح چوڑائی, صحيح اچائی, SDL_PixelFormat format, فراغ *pixels, صحيح pitch)
{
    CHECK_PARAM(چوڑائی < 0) {
        SDL_InvalidParamError("width");
        أرجع عدم;
    }

    CHECK_PARAM(اچائی < 0) {
        SDL_InvalidParamError("height");
        أرجع عدم;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        أرجع عدم;
    }

    إذا (pitch == 0 && !pixels) {
        // The application will fill these in later with valid values
    } وإلا {
        size_t اقل_Pitch;

        إذا (!SDL_Calculate_Surface_ناپ(format, چوڑائی, اچائی, عدم, &اقل_Pitch, true /* minimal pitch */)) {
            // Overflow...
            أرجع عدم;
        }

        CHECK_PARAM(pitch < 0 || (size_t)pitch < اقل_Pitch) {
            SDL_InvalidParamError("pitch");
            أرجع عدم;
        }
    }

    // Allocate and initialize the surface
    SDL_Surface *surface = (SDL_Surface *)SDL_malloc(حجم(*surface));
    إذا (!surface ||
        !SDL_InitializeSurface(surface, چوڑائی, اچائی, format, SDL_COLORSPACE_UNKNOWN, 0, pixels, pitch, false)) {
        أرجع عدم;
    }
    أرجع surface;
}

SDL_PropertiesID SDL_GetSurfaceProperties(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        أرجع 0;
    }

    إذا (!surface->props) {
        surface->props = SDL_CreateProperties();
    }
    أرجع surface->props;
}

bool SDL_سیٹ_Surface_Colorspace(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        أرجع SDL_InvalidParamError("surface");
    }

    surface->colorspace = colorspace;
    أرجع true;
}

SDL_Colorspace SDL_GetSurfaceColorspace(SDL_Surface *surface)
{
    إذا (!SDL_SurfaceValid(surface)) {
        أرجع SDL_COLORSPACE_UNKNOWN;
    }

    أرجع surface->colorspace;
}

عائم SDL_Get_Default_SDRWhite_نقطہ(SDL_Colorspace colorspace)
{
    أرجع SDL_Get_Surface_SDRWhite_نقطہ(عدم, colorspace);
}

عائم SDL_Get_Surface_SDRWhite_نقطہ(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    SDL_TransferCharacteristics transfer = SDL_COLORSPACETRANSFER(colorspace);

    إذا (transfer == SDL_TRANSFER_CHARACTERISTICS_خطی ||
        transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
        SDL_PropertiesID props;
        عائم default_قدر = 1.0f;

        إذا (SDL_SurfaceValid(surface)) {
            props = surface->props;
        } وإلا {
            props = 0;
        }
        إذا (transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
            /* The older standards use an SDR white point of 100 nits.
             * ITU-R BT.2408-6 recommends using an SDR white point of 203 nits.
             * This is the default Chrome uses, and what a lot of game content
             * assumes, so we'll go with that.
             */
            ثابت عائم DEFAULT_PQ_SDR_WHITE_نقطہ = 203.0f;
            default_قدر = DEFAULT_PQ_SDR_WHITE_نقطہ;
        }
        أرجع SDL_GetFloatProperty(props, SDL_PROP_SURFACE_SDR_WHITE_نقطہ_FLOAT, default_قدر);
    }
    أرجع 1.0f;
}

عائم SDL_GetDefaultHDRHeadroom(SDL_Colorspace colorspace)
{
    أرجع SDL_GetSurfaceHDRHeadroom(عدم, colorspace);
}

عائم SDL_GetSurfaceHDRHeadroom(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    SDL_TransferCharacteristics transfer = SDL_COLORSPACETRANSFER(colorspace);

    إذا (transfer == SDL_TRANSFER_CHARACTERISTICS_خطی ||
        transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
        SDL_PropertiesID props;
        عائم default_قدر = 0.0f;

        إذا (SDL_SurfaceValid(surface)) {
            props = surface->props;
        } وإلا {
            props = 0;
        }
        أرجع SDL_GetFloatProperty(props, SDL_PROP_SURFACE_HDR_HEADROOM_FLOAT, default_قدر);
    }
    أرجع 1.0f;
}

SDL_Palette *SDL_CreateSurfacePalette(SDL_Surface *surface)
{
    SDL_Palette *palette;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        أرجع عدم;
    }

    CHECK_PARAM(!SDL_ISPIXELFORMAT_اشاریہ_دار(surface->format)) {
        SDL_سیٹ_Error("The surface is not indexed format");
        أرجع عدم;
    }

    palette = SDL_CreatePalette((1 << SDL_BITSPERPIXEL(surface->format)));
    إذا (!palette) {
        أرجع عدم;
    }

    إذا (palette->ncolors == 2) {
        // Create a black and white bitmap palette
        palette->colors[0].r = 0xFF;
        palette->colors[0].g = 0xFF;
        palette->colors[0].b = 0xFF;
        palette->colors[1].r = 0x00;
        palette->colors[1].g = 0x00;
        palette->colors[1].b = 0x00;
    }

    إذا (!SDL_سیٹ_Surface_Palette(surface, palette)) {
        SDL_DestroyPalette(palette);
        أرجع عدم;
    }

    // The surface has retained the palette, we can remove the reference here
    SDL_assert(palette->refcount == 2);
    SDL_DestroyPalette(palette);
    أرجع palette;
}

bool SDL_سیٹ_Surface_Palette(SDL_Surface *surface, SDL_Palette *palette)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        أرجع SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(palette && !SDL_ISPIXELFORMAT_اشاریہ_دار(surface->format)) {
        أرجع SDL_سیٹ_Error("Surface doesn't use a palette");
    }

    CHECK_PARAM(palette && palette->ncolors > (1 << SDL_BITSPERPIXEL(surface->format))) {
        أرجع SDL_سیٹ_Error("Palette doesn't match surface format");
    }

    إذا (palette != surface->palette) {
        إذا (surface->palette) {
            SDL_DestroyPalette(surface->palette);
        }

        surface->palette = palette;

        إذا (surface->palette) {
            ++surface->palette->refcount;
        }
    }

    SDL_InvalidateMap(&surface->map);

    أرجع true;
}

SDL_Palette *SDL_GetSurfacePalette(SDL_Surface *surface)
{
    إذا (!SDL_SurfaceValid(surface)) {
        أرجع عدم;
    }

    أرجع surface->palette;
}

bool SDL_جوڑو_Surface_Alternate_Image(SDL_Surface *surface, SDL_Surface *image)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        أرجع SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(!SDL_SurfaceValid(image)) {
        أرجع SDL_InvalidParamError("image");
    }

    SDL_Surface **images = (SDL_Surface **)SDL_realloc(surface->images, (surface->عدد_images + 1) * حجم(*images));
    إذا (!images) {
        أرجع false;
    }
    images[surface->عدد_images] = image;
    surface->images = images;
    ++surface->عدد_images;
    ++image->refcount;
    أرجع true;
}

bool SDL_SurfaceHasAlternateImages(SDL_Surface *surface)
{
    إذا (!SDL_SurfaceValid(surface)) {
        أرجع false;
    }

    أرجع (surface->عدد_images > 0);
}

SDL_Surface **SDL_GetSurfaceImages(SDL_Surface *surface, صحيح *گنتی)
{
    إذا (گنتی) {
        *گنتی = 0;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        أرجع عدم;
    }

    صحيح عدد_images = 1 + surface->عدد_images;
    SDL_Surface **images = (SDL_Surface **)SDL_malloc((عدد_images + 1) * حجم(*images));
    إذا (!images) {
        أرجع عدم;
    }
    images[0] = surface;
    إذا (surface->عدد_images > 0) {
        SDL_memcpy(&images[1], surface->images, (surface->عدد_images * حجم(images[1])));
    }
    images[عدد_images] = عدم;

    إذا (گنتی) {
        *گنتی = عدد_images;
    }
    أرجع images;
}

SDL_Surface *SDL_GetSurfaceImage(SDL_Surface *surface, عائم display_scale)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        أرجع عدم;
    }

    إذا (!SDL_SurfaceHasAlternateImages(surface)) {
        ++surface->refcount;
        أرجع surface;
    }

    // This surface has high DPI images, pick the best one available, or scale one to the correct size
    SDL_Surface **images = SDL_GetSurfaceImages(surface, عدم);
    إذا (!images) {
        // Failure, fall back to the existing surface
        ++surface->refcount;
        أرجع surface;
    }

    // Find closest image. Images that are larger than the
    // desired size are preferred over images that are smaller.
    SDL_Surface *closest = عدم;
    صحيح desired_w = (صحيح)SDL_گیڑا(surface->w * display_scale);
    صحيح desired_h = (صحيح)SDL_گیڑا(surface->h * display_scale);
    صحيح desired_ناپ = desired_w * desired_h;
    صحيح closest_فاصلہ = -1;
    صحيح closest_ناپ = -1;
    لكل (صحيح i = 0; images[i]; ++i) {
        SDL_Surface *candidate = images[i];
        صحيح ناپ = candidate->w * candidate->h;
        صحيح delta_w = (candidate->w - desired_w);
        صحيح delta_h = (candidate->h - desired_h);
        صحيح فاصلہ = (delta_w * delta_w) + (delta_h * delta_h);
        إذا (closest_فاصلہ < 0 || فاصلہ < closest_فاصلہ ||
            (ناپ > desired_ناپ && closest_ناپ < desired_ناپ)) {
            closest = candidate;
            closest_فاصلہ = فاصلہ;
            closest_ناپ = ناپ;
        }
    }
    SDL_free(images);
    SDL_assert(closest != عدم);    // We should always have at least one surface

    إذا (closest->w == desired_w && closest->h == desired_h) {
        ++closest->refcount;
        أرجع closest;
    }

    // We need to scale the image to the correct size. To maintain good image quality, downscaling
    // is done in steps, never reducing the width and height by more than half each time.
    SDL_Surface *scaled = closest;
    افعل {
        صحيح اگلا_scaled_w = SDL_max(desired_w, (scaled->w + 1) / 2);
        صحيح اگلا_scaled_h = SDL_max(desired_h, (scaled->h + 1) / 2);
        SDL_Surface *اگلا_scaled = SDL_ScaleSurface(scaled, اگلا_scaled_w, اگلا_scaled_h, SDL_SCALEMODE_خطی);
        إذا (scaled != closest) {
            SDL_DestroySurface(scaled);
        }
        scaled = اگلا_scaled;
        إذا (!scaled) {
            // Failure, fall back to the closest surface
            ++closest->refcount;
            أرجع closest;
        }
    } طالما (scaled->w != desired_w || scaled->h != desired_h);

    أرجع scaled;
}

فراغ SDL_RemoveSurfaceAlternateImages(SDL_Surface *surface)
{
    إذا (!SDL_SurfaceValid(surface)) {
        أرجع;
    }

    إذا (surface->عدد_images > 0) {
        لكل (صحيح i = 0; i < surface->عدد_images; ++i) {
            SDL_DestroySurface(surface->images[i]);
        }
        SDL_free(surface->images);
        surface->images = عدم;
        surface->عدد_images = 0;
    }
}

bool SDL_سیٹ_Surface_RLE(SDL_Surface *surface, bool enabled)
{
    صحيح flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        أرجع SDL_InvalidParamError("surface");
    }

    flags = surface->map.info.flags;
    إذا (enabled) {
        surface->map.info.flags |= SDL_COPY_RLE_DESIRED;
    } وإلا {
        surface->map.info.flags &= ~SDL_COPY_RLE_DESIRED;
    }
    إذا (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    أرجع true;
}

bool SDL_SurfaceHasRLE(SDL_Surface *surface)
{
    إذا (!SDL_SurfaceValid(surface)) {
        أرجع false;
    }

    إذا (!(surface->map.info.flags & SDL_COPY_RLE_DESIRED)) {
        أرجع false;
    }

    أرجع true;
}

bool SDL_سیٹ_Surface_Color_کلید(SDL_Surface *surface, bool enabled, Uint32 کلید)
{
    صحيح flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        أرجع SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(surface->palette && کلید >= ((Uint32)surface->palette->ncolors)) {
        أرجع SDL_InvalidParamError("key");
    }

    flags = surface->map.info.flags;
    إذا (enabled) {
        surface->map.info.flags |= SDL_COPY_COLORKEY;
        surface->map.info.colorkey = کلید;
    } وإلا {
        surface->map.info.flags &= ~SDL_COPY_COLORKEY;
    }
    إذا (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }

    أرجع true;
}

bool SDL_Surface_Has_Color_کلید(SDL_Surface *surface)
{
    إذا (!SDL_SurfaceValid(surface)) {
        أرجع false;
    }

    إذا (!(surface->map.info.flags & SDL_COPY_COLORKEY)) {
        أرجع false;
    }

    أرجع true;
}

bool SDL_Get_Surface_Color_کلید(SDL_Surface *surface, Uint32 *کلید)
{
    إذا (کلید) {
        *کلید = 0;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        أرجع SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(!(surface->map.info.flags & SDL_COPY_COLORKEY)) {
        أرجع SDL_سیٹ_Error("Surface doesn't have a colorkey");
    }

    إذا (کلید) {
        *کلید = surface->map.info.colorkey;
    }
    أرجع true;
}

/* This is a fairly slow function to switch from colorkey to alpha
   NB: it doesn't handle bpp 1 or 3, because they have no alpha channel */
ساكن فراغ SDL_Convert_Colorkey_منزل_Alpha(SDL_Surface *surface, bool ignore_alpha)
{
    صحيح x, y, bpp;

    إذا (!SDL_SurfaceValid(surface)) {
        أرجع;
    }

    إذا (!(surface->map.info.flags & SDL_COPY_COLORKEY) ||
        !SDL_ISPIXELFORMAT_ALPHA(surface->format)) {
        أرجع;
    }

    bpp = SDL_BYTESPERPIXEL(surface->format);

    SDL_جندرا_Surface(surface);

    إذا (bpp == 2) {
        Uint16 *صف, *spot;
        Uint16 ckey = (Uint16)surface->map.info.colorkey;
        Uint16 نقاب = (Uint16)(~surface->fmt->Amask);

        // Ignore, or not, alpha in colorkey comparison
        إذا (ignore_alpha) {
            ckey &= نقاب;
            صف = (Uint16 *)surface->pixels;
            لكل (y = surface->h; y--;) {
                spot = صف;
                لكل (x = surface->w; x--;) {
                    إذا ((*spot & نقاب) == ckey) {
                        *spot &= نقاب;
                    }
                    ++spot;
                }
                صف += surface->pitch / 2;
            }
        } وإلا {
            صف = (Uint16 *)surface->pixels;
            لكل (y = surface->h; y--;) {
                spot = صف;
                لكل (x = surface->w; x--;) {
                    إذا (*spot == ckey) {
                        *spot &= نقاب;
                    }
                    ++spot;
                }
                صف += surface->pitch / 2;
            }
        }
    } وإلا إذا (bpp == 4) {
        Uint32 *صف, *spot;
        Uint32 ckey = surface->map.info.colorkey;
        Uint32 نقاب = ~surface->fmt->Amask;

        // Ignore, or not, alpha in colorkey comparison
        إذا (ignore_alpha) {
            ckey &= نقاب;
            صف = (Uint32 *)surface->pixels;
            لكل (y = surface->h; y--;) {
                spot = صف;
                لكل (x = surface->w; x--;) {
                    إذا ((*spot & نقاب) == ckey) {
                        *spot &= نقاب;
                    }
                    ++spot;
                }
                صف += surface->pitch / 4;
            }
        } وإلا {
            صف = (Uint32 *)surface->pixels;
            لكل (y = surface->h; y--;) {
                spot = صف;
                لكل (x = surface->w; x--;) {
                    إذا (*spot == ckey) {
                        *spot &= نقاب;
                    }
                    ++spot;
                }
                صف += surface->pitch / 4;
            }
        }
    }

    SDL_UnlockSurface(surface);

    SDL_سیٹ_Surface_Color_کلید(surface, false, 0);
    SDL_سیٹ_Surface_Blend_منوال(surface, SDL_BLENDMODE_BLEND);
}

bool SDL_سیٹ_Surface_Color_Mod(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b)
{
    صحيح flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        أرجع SDL_InvalidParamError("surface");
    }

    surface->map.info.r = r;
    surface->map.info.g = g;
    surface->map.info.b = b;

    flags = surface->map.info.flags;
    إذا (r != 0xFF || g != 0xFF || b != 0xFF) {
        surface->map.info.flags |= SDL_COPY_MODULATE_COLOR;
    } وإلا {
        surface->map.info.flags &= ~SDL_COPY_MODULATE_COLOR;
    }
    إذا (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    أرجع true;
}

bool SDL_GetSurfaceColorMod(SDL_Surface *surface, Uint8 *r, Uint8 *g, Uint8 *b)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        إذا (r) {
            *r = 255;
        }
        إذا (g) {
            *g = 255;
        }
        إذا (b) {
            *b = 255;
        }
        أرجع SDL_InvalidParamError("surface");
    }

    إذا (r) {
        *r = surface->map.info.r;
    }
    إذا (g) {
        *g = surface->map.info.g;
    }
    إذا (b) {
        *b = surface->map.info.b;
    }
    أرجع true;
}

bool SDL_سیٹ_Surface_Alpha_Mod(SDL_Surface *surface, Uint8 alpha)
{
    صحيح flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        أرجع SDL_InvalidParamError("surface");
    }

    surface->map.info.a = alpha;

    flags = surface->map.info.flags;
    إذا (alpha != 0xFF) {
        surface->map.info.flags |= SDL_COPY_MODULATE_ALPHA;
    } وإلا {
        surface->map.info.flags &= ~SDL_COPY_MODULATE_ALPHA;
    }
    إذا (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    أرجع true;
}

bool SDL_GetSurfaceAlphaMod(SDL_Surface *surface, Uint8 *alpha)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        إذا (alpha) {
            *alpha = 255;
        }
        أرجع SDL_InvalidParamError("surface");
    }

    إذا (alpha) {
        *alpha = surface->map.info.a;
    }
    أرجع true;
}

bool SDL_سیٹ_Surface_Blend_منوال(SDL_Surface *surface, SDL_Blend_منوال blend_منوال)
{
    صحيح flags;
    bool نتیجہ = true;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        أرجع SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(blend_منوال == SDL_BLENDMODE_INVALID) {
        أرجع SDL_InvalidParamError("blendMode");
    }

    flags = surface->map.info.flags;
    surface->map.info.flags &= ~SDL_COPY_BLEND_نقاب;
    بدل (blend_منوال) {
    حالة SDL_BLENDMODE_NONE:
        اكسر;
    حالة SDL_BLENDMODE_BLEND:
        surface->map.info.flags |= SDL_COPY_BLEND;
        اكسر;
    حالة SDL_BLENDMODE_BLEND_PREMULTIPLIED:
        surface->map.info.flags |= SDL_COPY_BLEND_PREMULTIPLIED;
        اكسر;
    حالة SDL_BLENDMODE_جوڑو:
        surface->map.info.flags |= SDL_COPY_جوڑو;
        اكسر;
    حالة SDL_BLENDMODE_جوڑو_PREMULTIPLIED:
        surface->map.info.flags |= SDL_COPY_جوڑو_PREMULTIPLIED;
        اكسر;
    حالة SDL_BLENDMODE_MOD:
        surface->map.info.flags |= SDL_COPY_MOD;
        اكسر;
    حالة SDL_BLENDMODE_MUL:
        surface->map.info.flags |= SDL_COPY_MUL;
        اكسر;
    افتراضي:
        نتیجہ = SDL_Unsupported();
        اكسر;
    }

    إذا (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }

    أرجع نتیجہ;
}

bool SDL_Get_Surface_Blend_منوال(SDL_Surface *surface, SDL_Blend_منوال *blend_منوال)
{
    إذا (blend_منوال) {
        *blend_منوال = SDL_BLENDMODE_INVALID;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        أرجع SDL_InvalidParamError("surface");
    }

    إذا (!blend_منوال) {
        أرجع true;
    }

    بدل (surface->map.info.flags & SDL_COPY_BLEND_نقاب) {
    حالة SDL_COPY_BLEND:
        *blend_منوال = SDL_BLENDMODE_BLEND;
        اكسر;
    حالة SDL_COPY_BLEND_PREMULTIPLIED:
        *blend_منوال = SDL_BLENDMODE_BLEND_PREMULTIPLIED;
        اكسر;
    حالة SDL_COPY_جوڑو:
        *blend_منوال = SDL_BLENDMODE_جوڑو;
        اكسر;
    حالة SDL_COPY_جوڑو_PREMULTIPLIED:
        *blend_منوال = SDL_BLENDMODE_جوڑو_PREMULTIPLIED;
        اكسر;
    حالة SDL_COPY_MOD:
        *blend_منوال = SDL_BLENDMODE_MOD;
        اكسر;
    حالة SDL_COPY_MUL:
        *blend_منوال = SDL_BLENDMODE_MUL;
        اكسر;
    افتراضي:
        *blend_منوال = SDL_BLENDMODE_NONE;
        اكسر;
    }
    أرجع true;
}

bool SDL_سیٹ_Surface_Clip_Rect(SDL_Surface *surface, ثابت SDL_Rect *rect)
{
    SDL_Rect بھریا_rect;

    // Don't do anything if there's no surface to act on
    إذا (!SDL_SurfaceValid(surface)) {
        أرجع false;
    }

    // Set up the full surface rectangle
    بھریا_rect.x = 0;
    بھریا_rect.y = 0;
    بھریا_rect.w = surface->w;
    بھریا_rect.h = surface->h;

    // Set the clipping rectangle
    إذا (!rect) {
        surface->clip_rect = بھریا_rect;
        أرجع true;
    }
    أرجع SDL_GetRectIntersection(rect, &بھریا_rect, &surface->clip_rect);
}

bool SDL_GetSurfaceClipRect(SDL_Surface *surface, SDL_Rect *rect)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        إذا (rect) {
            SDL_zerop(rect);
        }
        أرجع SDL_InvalidParamError("surface");
    }
    CHECK_PARAM(!rect) {
        أرجع SDL_InvalidParamError("rect");
    }
    *rect = surface->clip_rect;
    أرجع true;
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
    إذا (!SDL_ValidateMap(src, dst)) {
        أرجع false;
    }
    أرجع src->map.blit(src, srcrect, dst, dstrect);
}

bool SDL_BlitSurface(SDL_Surface *src, ثابت SDL_Rect *srcrect, SDL_Surface *dst, ثابت SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src) || (!src->pixels && !SDL_MUSTLOCK(src))) {
        أرجع SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst) || (!dst->pixels && !SDL_MUSTLOCK(dst))) {
        أرجع SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        أرجع SDL_سیٹ_Error("Surfaces must not be locked during blit");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    إذا (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
    } وإلا {
        r_dst.x = 0;
        r_dst.y = 0;
    }

    // clip the source rectangle to the source surface
    إذا (srcrect) {
        SDL_Rect tmp;
        إذا (SDL_GetRectIntersection(srcrect, &r_src, &tmp) == false) {
            أرجع true;
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
        إذا (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &tmp) == false) {
            أرجع true;
        }

        // Shift srcrect, if dstrect has changed
        r_src.x += tmp.x - r_dst.x;
        r_src.y += tmp.y - r_dst.y;
        r_src.w = tmp.w;
        r_src.h = tmp.h;

        // Update dstrect
        r_dst = tmp;
    }

    إذا (r_dst.w <= 0 || r_dst.h <= 0) {
        // No-op.
        أرجع true;
    }

    // Switch back to a fast blit if we were previously stretching
    إذا (src->map.info.flags & SDL_COPY_سبھ_توں_نیڑے) {
        src->map.info.flags &= ~SDL_COPY_سبھ_توں_نیڑے;
        SDL_InvalidateMap(&src->map);
    }

    أرجع SDL_BlitSurfaceUnchecked(src, &r_src, dst, &r_dst);
}

ساكن bool SDL_BlitSurfaceClippedScaled(SDL_Surface *src, ثابت SDL_Rect *srcrect, SDL_Surface *dst, ثابت SDL_Rect *dstrect, SDL_Scale_منوال scale_منوال)
{
    // We need to scale first, then blit into dst because we're clipping in the destination surface pixel coordinates
    bool نتیجہ;
    صحيح saved_w = src->w;
    صحيح saved_h = src->h;
    فراغ *saved_pixels = src->pixels;
    src->w = srcrect->w;
    src->h = srcrect->h;
    src->pixels = (Uint8 *)src->pixels + srcrect->y * src->pitch + srcrect->x * SDL_BYTESPERPIXEL(src->format);
    SDL_Surface *scaled = SDL_ScaleSurface(src, dstrect->w, dstrect->h, scale_منوال);
    إذا (scaled) {
        نتیجہ = SDL_BlitSurface(scaled, عدم, dst, dstrect);
        SDL_DestroySurface(scaled);
    } وإلا {
        نتیجہ = false;
    }
    src->w = saved_w;
    src->h = saved_h;
    src->pixels = saved_pixels;
    أرجع نتیجہ;
}

bool SDL_BlitSurfaceScaled(SDL_Surface *src, ثابت SDL_Rect *srcrect, SDL_Surface *dst, ثابت SDL_Rect *dstrect, SDL_Scale_منوال scale_منوال)
{
    SDL_Rect r_src, r_dst;
    bool نتیجہ;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src) || (!src->pixels && !SDL_MUSTLOCK(src))) {
        أرجع SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst) || (!dst->pixels && !SDL_MUSTLOCK(dst))) {
        أرجع SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        أرجع SDL_سیٹ_Error("Surfaces must not be locked during blit");
    }

    بدل (scale_منوال) {
    حالة SDL_SCALEMODE_سبھ_توں_نیڑے:
        اكسر;
    حالة SDL_SCALEMODE_خطی:
        اكسر;
    حالة SDL_SCALEMODE_PIXELART:
        scale_منوال = SDL_SCALEMODE_سبھ_توں_نیڑے;
        اكسر;
    افتراضي:
        أرجع SDL_InvalidParamError("scaleMode");
    }

    صحيح src_w = srcrect ? srcrect->w : src->w;
    صحيح src_h = srcrect ? srcrect->h : src->h;
    صحيح dst_w = dstrect ? dstrect->w : dst->w;
    صحيح dst_h = dstrect ? dstrect->h : dst->h;
    إذا (src_w == dst_w && src_h == dst_h) {
        // No scaling, defer to regular blit
        أرجع SDL_BlitSurface(src, srcrect, dst, dstrect);
    }

    إذا (src->w == 0 || src->h == 0) {
        // Nothing to do
        أرجع true;
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    إذا (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
        r_dst.w = dstrect->w;
        r_dst.h = dstrect->h;
    } وإلا {
        r_dst.x = 0;
        r_dst.y = 0;
        r_dst.w = dst->w;
        r_dst.h = dst->h;
    }

    // clip the source rectangle to the source surface
    إذا (srcrect) {
        SDL_Rect desired, tmp;
        desired.x = srcrect->x;
        desired.y = srcrect->y;
        desired.w = SDL_max(srcrect->w, 1);
        desired.h = SDL_max(srcrect->h, 1);
        إذا (SDL_GetRectIntersection(&desired, &r_src, &tmp) == false) {
            أرجع true;
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
    إذا (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &tmp) == false) {
        أرجع true;
    }

    إذا (tmp.x != r_dst.x || tmp.y != r_dst.y || tmp.w != r_dst.w || tmp.h != r_dst.h) {
        // Need to do a clipped and scaled blit
        أرجع SDL_BlitSurfaceClippedScaled(src, &r_src, dst, &r_dst, scale_منوال);
    }

    إذا (SDL_MUSTLOCK(src)) {
        إذا (!SDL_جندرا_Surface(src)) {
            أرجع false;
        }
    }
    إذا (SDL_MUSTLOCK(dst)) {
        إذا (!SDL_جندرا_Surface(dst)) {
            إذا (SDL_MUSTLOCK(src)) {
                SDL_UnlockSurface(src);
            }
            أرجع false;
        }
    }

    نتیجہ = SDL_BlitSurfaceUncheckedScaled(src, &r_src, dst, &r_dst, scale_منوال);

    إذا (SDL_MUSTLOCK(src)) {
        SDL_UnlockSurface(src);
    }
    إذا (SDL_MUSTLOCK(dst)) {
        SDL_UnlockSurface(dst);
    }
    أرجع نتیجہ;
}

/**
 *  This is a semi-private blit function and it performs low-level surface
 *  scaled blitting only.
 */
bool SDL_BlitSurfaceUncheckedScaled(SDL_Surface *src, ثابت SDL_Rect *srcrect, SDL_Surface *dst, ثابت SDL_Rect *dstrect, SDL_Scale_منوال scale_منوال)
{
    ساكن ثابت Uint32 complex_copy_flags = (SDL_COPY_MODULATE_نقاب | SDL_COPY_BLEND_نقاب | SDL_COPY_COLORKEY);

    إذا (srcrect->w > SDL_MAX_UINT16 || srcrect->h > SDL_MAX_UINT16 ||
        dstrect->w > SDL_MAX_UINT16 || dstrect->h > SDL_MAX_UINT16) {
        أرجع SDL_سیٹ_Error("Size too large for scaling");
    }

    إذا (!(src->map.info.flags & SDL_COPY_سبھ_توں_نیڑے)) {
        src->map.info.flags |= SDL_COPY_سبھ_توں_نیڑے;
        SDL_InvalidateMap(&src->map);
    }

    إذا (scale_منوال == SDL_SCALEMODE_سبھ_توں_نیڑے || scale_منوال == SDL_SCALEMODE_PIXELART) {
        إذا (!(src->map.info.flags & complex_copy_flags) &&
            src->format == dst->format &&
            (!SDL_ISPIXELFORMAT_اشاریہ_دار(src->format) ||
             (SDL_BITSPERPIXEL(src->format) == 8 && SDL_IsSamePalette(src->palette, dst->palette))) &&
            SDL_BYTESPERPIXEL(src->format) <= 4) {
            أرجع SDL_StretchSurface(src, srcrect, dst, dstrect, SDL_SCALEMODE_سبھ_توں_نیڑے);
        } وإلا إذا (SDL_BITSPERPIXEL(src->format) < 8) {
            // Scaling bitmap not yet supported, convert to RGBA for blit
            bool نتیجہ = false;
            SDL_Surface *tmp = SDL_ConvertSurface(src, SDL_PIXELFORMAT_ARGB8888);
            إذا (tmp) {
                نتیجہ = SDL_BlitSurfaceUncheckedScaled(tmp, srcrect, dst, dstrect, SDL_SCALEMODE_سبھ_توں_نیڑے);
                SDL_DestroySurface(tmp);
            }
            أرجع نتیجہ;
        } وإلا {
            أرجع SDL_BlitSurfaceUnchecked(src, srcrect, dst, dstrect);
        }
    } وإلا {
        إذا (!(src->map.info.flags & complex_copy_flags) &&
            src->format == dst->format &&
            !SDL_ISPIXELFORMAT_اشاریہ_دار(src->format) &&
            SDL_BYTESPERPIXEL(src->format) == 4 &&
            src->format != SDL_PIXELFORMAT_ARGB2101010) {
            // fast path
            أرجع SDL_StretchSurface(src, srcrect, dst, dstrect, SDL_SCALEMODE_خطی);
        } وإلا إذا (SDL_BITSPERPIXEL(src->format) < 8) {
            // Scaling bitmap not yet supported, convert to RGBA for blit
            bool نتیجہ = false;
            SDL_Surface *tmp = SDL_ConvertSurface(src, SDL_PIXELFORMAT_ARGB8888);
            إذا (tmp) {
                نتیجہ = SDL_BlitSurfaceUncheckedScaled(tmp, srcrect, dst, dstrect, scale_منوال);
                SDL_DestroySurface(tmp);
            }
            أرجع نتیجہ;
        } وإلا {
            // Use intermediate surface(s)
            SDL_Surface *tmp1 = عدم;
            bool نتیجہ;
            SDL_Rect srcrect2;
            صحيح is_complex_copy_flags = (src->map.info.flags & complex_copy_flags);

            Uint8 r, g, b;
            Uint8 alpha;
            SDL_Blend_منوال blend_منوال;

            // Save source infos
            SDL_GetSurfaceColorMod(src, &r, &g, &b);
            SDL_GetSurfaceAlphaMod(src, &alpha);
            SDL_Get_Surface_Blend_منوال(src, &blend_منوال);
            srcrect2.x = srcrect->x;
            srcrect2.y = srcrect->y;
            srcrect2.w = srcrect->w;
            srcrect2.h = srcrect->h;

            // Change source format if not appropriate for scaling
            إذا (SDL_BYTESPERPIXEL(src->format) != 4 || src->format == SDL_PIXELFORMAT_ARGB2101010) {
                SDL_PixelFormat fmt;
                إذا (SDL_BYTESPERPIXEL(dst->format) == 4 && dst->format != SDL_PIXELFORMAT_ARGB2101010 &&
                    (SDL_ISPIXELFORMAT_ALPHA(dst->format) || !is_complex_copy_flags)) {
                    fmt = dst->format;
                } وإلا {
                    fmt = SDL_PIXELFORMAT_ARGB8888;
                }
                tmp1 = SDL_ConvertSurfaceRect(src, srcrect, fmt);
                إذا (!tmp1) {
                    أرجع false;
                }
                src = tmp1;
                srcrect2.x = 0;
                srcrect2.y = 0;
            }

            // Intermediate scaling
            إذا (is_complex_copy_flags || src->format != dst->format) {
                SDL_Rect tmprect;
                SDL_Surface *tmp2 = SDL_CreateSurfaceUninitialized(dstrect->w, dstrect->h, src->format);
                SDL_StretchSurface(src, &srcrect2, tmp2, عدم, SDL_SCALEMODE_خطی);

                SDL_سیٹ_Surface_Color_Mod(tmp2, r, g, b);
                SDL_سیٹ_Surface_Alpha_Mod(tmp2, alpha);
                SDL_سیٹ_Surface_Blend_منوال(tmp2, blend_منوال);

                tmprect.x = 0;
                tmprect.y = 0;
                tmprect.w = dstrect->w;
                tmprect.h = dstrect->h;
                نتیجہ = SDL_BlitSurfaceUnchecked(tmp2, &tmprect, dst, dstrect);
                SDL_DestroySurface(tmp2);
            } وإلا {
                نتیجہ = SDL_StretchSurface(src, &srcrect2, dst, dstrect, SDL_SCALEMODE_خطی);
            }

            SDL_DestroySurface(tmp1);
            أرجع نتیجہ;
        }
    }
}

bool SDL_BlitSurfaceTiled(SDL_Surface *src, ثابت SDL_Rect *srcrect, SDL_Surface *dst, ثابت SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        أرجع SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        أرجع SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        أرجع SDL_سیٹ_Error("Surfaces must not be locked during blit");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    إذا (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
        r_dst.w = dstrect->w;
        r_dst.h = dstrect->h;
    } وإلا {
        r_dst.x = 0;
        r_dst.y = 0;
        r_dst.w = dst->w;
        r_dst.h = dst->h;
    }

    // clip the source rectangle to the source surface
    إذا (srcrect) {
        إذا (SDL_GetRectIntersection(srcrect, &r_src, &r_src) == false) {
            أرجع true;
        }

        // For tiling we don't adjust the destination rectangle
    }

    // clip the destination rectangle against the clip rectangle
    {
        إذا (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &r_dst) == false) {
            أرجع true;
        }

        // For tiling we don't adjust the source rectangle
    }

    // Switch back to a fast blit if we were previously stretching
    إذا (src->map.info.flags & SDL_COPY_سبھ_توں_نیڑے) {
        src->map.info.flags &= ~SDL_COPY_سبھ_توں_نیڑے;
        SDL_InvalidateMap(&src->map);
    }

    صحيح صفاں = r_dst.h / r_src.h;
    صحيح خانے_گنتی = r_dst.w / r_src.w;
    صحيح بچیا_w = r_dst.w % r_src.w;
    صحيح بچیا_h = r_dst.h % r_src.h;
    SDL_Rect curr_src, curr_dst;

    SDL_copyp(&curr_src, &r_src);
    curr_dst.y = r_dst.y;
    curr_dst.w = r_src.w;
    curr_dst.h = r_src.h;
    لكل (صحيح y = 0; y < صفاں; ++y) {
        curr_dst.x = r_dst.x;
        لكل (صحيح x = 0; x < خانے_گنتی; ++x) {
            إذا (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                أرجع false;
            }
            curr_dst.x += curr_dst.w;
        }
        إذا (بچیا_w) {
            curr_src.w = بچیا_w;
            curr_dst.w = بچیا_w;
            إذا (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                أرجع false;
            }
            curr_src.w = r_src.w;
            curr_dst.w = r_src.w;
        }
        curr_dst.y += curr_dst.h;
    }
    إذا (بچیا_h) {
        curr_src.h = بچیا_h;
        curr_dst.h = بچیا_h;
        curr_dst.x = r_dst.x;
        لكل (صحيح x = 0; x < خانے_گنتی; ++x) {
            إذا (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                أرجع false;
            }
            curr_dst.x += curr_dst.w;
        }
        إذا (بچیا_w) {
            curr_src.w = بچیا_w;
            curr_dst.w = بچیا_w;
            إذا (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                أرجع false;
            }
        }
    }
    أرجع true;
}

bool SDL_BlitSurfaceTiledWithScale(SDL_Surface *src, ثابت SDL_Rect *srcrect, عائم scale, SDL_Scale_منوال scale_منوال, SDL_Surface *dst, ثابت SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        أرجع SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        أرجع SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        أرجع SDL_سیٹ_Error("Surfaces must not be locked during blit");
    }
    CHECK_PARAM(scale < 0.0f) {
        أرجع SDL_InvalidParamError("scale");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    إذا (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
        r_dst.w = dstrect->w;
        r_dst.h = dstrect->h;
    } وإلا {
        r_dst.x = 0;
        r_dst.y = 0;
        r_dst.w = dst->w;
        r_dst.h = dst->h;
    }

    // clip the source rectangle to the source surface
    إذا (srcrect) {
        إذا (SDL_GetRectIntersection(srcrect, &r_src, &r_src) == false) {
            أرجع true;
        }

        // For tiling we don't adjust the destination rectangle
    }

    // clip the destination rectangle against the clip rectangle
    {
        إذا (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &r_dst) == false) {
            أرجع true;
        }

        // For tiling we don't adjust the source rectangle
    }

    // Switch back to a fast blit if we were previously stretching
    إذا (src->map.info.flags & SDL_COPY_سبھ_توں_نیڑے) {
        src->map.info.flags &= ~SDL_COPY_سبھ_توں_نیڑے;
        SDL_InvalidateMap(&src->map);
    }

    صحيح tile_چوڑائی = (صحيح)SDL_roundf(r_src.w * scale);
    صحيح tile_اچائی = (صحيح)SDL_roundf(r_src.h * scale);
    إذا (tile_چوڑائی <= 0 || tile_اچائی <= 0) {
        // Nothing to do
        أرجع true;
    }
    صحيح صفاں = r_dst.h / tile_اچائی;
    صحيح خانے_گنتی = r_dst.w / tile_چوڑائی;
    صحيح بچیا_dst_w = (r_dst.w - خانے_گنتی * tile_چوڑائی);
    صحيح بچیا_dst_h = (r_dst.h - صفاں * tile_اچائی);
    صحيح بچیا_src_w = (صحيح)(بچیا_dst_w / scale);
    صحيح بچیا_src_h = (صحيح)(بچیا_dst_h / scale);
    SDL_Rect curr_src, curr_dst;

    SDL_copyp(&curr_src, &r_src);
    curr_dst.y = r_dst.y;
    curr_dst.w = tile_چوڑائی;
    curr_dst.h = tile_اچائی;
    لكل (صحيح y = 0; y < صفاں; ++y) {
        curr_dst.x = r_dst.x;
        لكل (صحيح x = 0; x < خانے_گنتی; ++x) {
            إذا (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scale_منوال)) {
                أرجع false;
            }
            curr_dst.x += curr_dst.w;
        }
        إذا (بچیا_dst_w > 0) {
            curr_src.w = بچیا_src_w;
            curr_dst.w = بچیا_dst_w;
            إذا (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scale_منوال)) {
                أرجع false;
            }
            curr_src.w = r_src.w;
            curr_dst.w = tile_چوڑائی;
        }
        curr_dst.y += curr_dst.h;
    }
    إذا (بچیا_dst_h > 0) {
        curr_src.h = بچیا_src_h;
        curr_dst.h = بچیا_dst_h;
        curr_dst.x = r_dst.x;
        لكل (صحيح x = 0; x < خانے_گنتی; ++x) {
            إذا (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scale_منوال)) {
                أرجع false;
            }
            curr_dst.x += curr_dst.w;
        }
        إذا (بچیا_dst_w > 0) {
            curr_src.w = بچیا_src_w;
            curr_dst.w = بچیا_dst_w;
            إذا (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scale_منوال)) {
                أرجع false;
            }
        }
    }
    أرجع true;
}

bool SDL_BlitSurface9Grid(SDL_Surface *src, ثابت SDL_Rect *srcrect, صحيح بایاں_چوڑائی, صحيح دایاں_چوڑائی, صحيح چوٹی_اچائی, صحيح bottom_اچائی, عائم scale, SDL_Scale_منوال scale_منوال, SDL_Surface *dst, ثابت SDL_Rect *dstrect)
{
    SDL_Rect بھریا_src, بھریا_dst;
    SDL_Rect curr_src, curr_dst;
    صحيح dst_بایاں_چوڑائی;
    صحيح dst_دایاں_چوڑائی;
    صحيح dst_چوٹی_اچائی;
    صحيح dst_bottom_اچائی;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        أرجع SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        أرجع SDL_InvalidParamError("dst");
    }

    إذا (!srcrect) {
        بھریا_src.x = 0;
        بھریا_src.y = 0;
        بھریا_src.w = src->w;
        بھریا_src.h = src->h;
        srcrect = &بھریا_src;
    }

    إذا (!dstrect) {
        بھریا_dst.x = 0;
        بھریا_dst.y = 0;
        بھریا_dst.w = dst->w;
        بھریا_dst.h = dst->h;
        dstrect = &بھریا_dst;
    }

    إذا (scale <= 0.0f || scale == 1.0f) {
        dst_بایاں_چوڑائی = بایاں_چوڑائی;
        dst_دایاں_چوڑائی = دایاں_چوڑائی;
        dst_چوٹی_اچائی = چوٹی_اچائی;
        dst_bottom_اچائی = bottom_اچائی;
    } وإلا {
        dst_بایاں_چوڑائی = (صحيح)SDL_roundf(بایاں_چوڑائی * scale);
        dst_دایاں_چوڑائی = (صحيح)SDL_roundf(دایاں_چوڑائی * scale);
        dst_چوٹی_اچائی = (صحيح)SDL_roundf(چوٹی_اچائی * scale);
        dst_bottom_اچائی = (صحيح)SDL_roundf(bottom_اچائی * scale);
    }

    // Upper-left corner
    curr_src.x = srcrect->x;
    curr_src.y = srcrect->y;
    curr_src.w = بایاں_چوڑائی;
    curr_src.h = چوٹی_اچائی;
    curr_dst.x = dstrect->x;
    curr_dst.y = dstrect->y;
    curr_dst.w = dst_بایاں_چوڑائی;
    curr_dst.h = dst_چوٹی_اچائی;
    إذا (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_منوال)) {
        أرجع false;
    }

    // Upper-right corner
    curr_src.x = srcrect->x + srcrect->w - دایاں_چوڑائی;
    curr_src.w = دایاں_چوڑائی;
    curr_dst.x = dstrect->x + dstrect->w - dst_دایاں_چوڑائی;
    curr_dst.w = dst_دایاں_چوڑائی;
    إذا (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_منوال)) {
        أرجع false;
    }

    // Lower-right corner
    curr_src.y = srcrect->y + srcrect->h - bottom_اچائی;
    curr_dst.y = dstrect->y + dstrect->h - dst_bottom_اچائی;
    curr_dst.h = dst_bottom_اچائی;
    إذا (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_منوال)) {
        أرجع false;
    }

    // Lower-left corner
    curr_src.x = srcrect->x;
    curr_src.w = بایاں_چوڑائی;
    curr_dst.x = dstrect->x;
    curr_dst.w = dst_بایاں_چوڑائی;
    إذا (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_منوال)) {
        أرجع false;
    }

    //بایاں
    curr_src.y = srcrect->y + چوٹی_اچائی;
    curr_src.h = srcrect->h - چوٹی_اچائی - bottom_اچائی;
    curr_dst.y = dstrect->y + dst_چوٹی_اچائی;
    curr_dst.h = dstrect->h - dst_چوٹی_اچائی - dst_bottom_اچائی;
    إذا (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_منوال)) {
        أرجع false;
    }

    //دایاں
    curr_src.x = srcrect->x + srcrect->w - دایاں_چوڑائی;
    curr_src.w = دایاں_چوڑائی;
    curr_dst.x = dstrect->x + dstrect->w - dst_دایاں_چوڑائی;
    curr_dst.w = dst_دایاں_چوڑائی;
    إذا (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_منوال)) {
        أرجع false;
    }

    //چوٹی
    curr_src.x = srcrect->x + بایاں_چوڑائی;
    curr_src.y = srcrect->y;
    curr_src.w = srcrect->w - بایاں_چوڑائی - دایاں_چوڑائی;
    curr_src.h = چوٹی_اچائی;
    curr_dst.x = dstrect->x + dst_بایاں_چوڑائی;
    curr_dst.y = dstrect->y;
    curr_dst.w = dstrect->w - dst_بایاں_چوڑائی - dst_دایاں_چوڑائی;
    curr_dst.h = dst_چوٹی_اچائی;
    إذا (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_منوال)) {
        أرجع false;
    }

    // Bottom
    curr_src.y = srcrect->y + srcrect->h - bottom_اچائی;
    curr_dst.y = dstrect->y + dstrect->h - dst_bottom_اچائی;
    curr_dst.h = dst_bottom_اچائی;
    إذا (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_منوال)) {
        أرجع false;
    }

    // Center
    curr_src.x = srcrect->x + بایاں_چوڑائی;
    curr_src.y = srcrect->y + چوٹی_اچائی;
    curr_src.w = srcrect->w - بایاں_چوڑائی - دایاں_چوڑائی;
    curr_src.h = srcrect->h - چوٹی_اچائی - bottom_اچائی;
    curr_dst.x = dstrect->x + dst_بایاں_چوڑائی;
    curr_dst.y = dstrect->y + dst_چوٹی_اچائی;
    curr_dst.w = dstrect->w - dst_بایاں_چوڑائی - dst_دایاں_چوڑائی;
    curr_dst.h = dstrect->h - dst_چوٹی_اچائی - dst_bottom_اچائی;
    إذا (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_منوال)) {
        أرجع false;
    }

    أرجع true;
}

/*
 * Lock a surface to directly access the pixels
 */
bool SDL_جندرا_Surface(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        أرجع SDL_InvalidParamError("surface");
    }

    إذا (!surface->locked) {
#جے_تعریف_شدہ SDL_HAVE_RLE
        // Perform the lock
        إذا (surface->اندرونی_flags & SDL_اندرونی_SURFACE_RLEACCEL) {
            SDL_UnRLESurface(surface);
        }
#جے_انت
    }

    // Increment the surface lock count, for recursive locks
    ++surface->locked;
    surface->flags |= SDL_SURFACE_LOCKED;
    SDL_Update_Surface_جندرا_Flag(surface);

    // Ready to go..
    أرجع true;
}

/*
 * Unlock a previously locked surface
 */
فراغ SDL_UnlockSurface(SDL_Surface *surface)
{
    إذا (!SDL_SurfaceValid(surface)) {
        أرجع;
    }

    // Only perform an unlock if we are locked
    إذا (!surface->locked || (--surface->locked > 0)) {
        أرجع;
    }

    surface->flags &= ~SDL_SURFACE_LOCKED;
    SDL_Update_Surface_جندرا_Flag(surface);
}

ساكن bool SDL_FlipSurfaceHorizontal(SDL_Surface *surface)
{
    bool isstack;
    Uint8 *صف, *a, *b, *tmp;
    صحيح i, j, bpp;

    إذا (SDL_BITSPERPIXEL(surface->format) < 8) {
        // We could implement this if needed, but we'd have to flip sets of bits within a byte
        أرجع SDL_Unsupported();
    }

    إذا (surface->h <= 0) {
        أرجع true;
    }

    إذا (surface->w <= 1) {
        أرجع true;
    }

    bpp = SDL_BYTESPERPIXEL(surface->format);
    صف = (Uint8 *)surface->pixels;
    tmp = SDL_small_alloc(Uint8, surface->pitch, &isstack);
    إذا (!tmp) {
        أرجع false;
    }
    لكل (i = surface->h; i--; ) {
        a = صف;
        b = a + (surface->w - 1) * bpp;
        لكل (j = surface->w / 2; j--; ) {
            SDL_memcpy(tmp, a, bpp);
            SDL_memcpy(a, b, bpp);
            SDL_memcpy(b, tmp, bpp);
            a += bpp;
            b -= bpp;
        }
        صف += surface->pitch;
    }
    SDL_small_free(tmp, isstack);
    أرجع true;
}

ساكن bool SDL_FlipSurfaceVertical(SDL_Surface *surface)
{
    bool isstack;
    Uint8 *a, *b, *tmp;
    صحيح i;

    إذا (surface->h <= 1) {
        أرجع true;
    }

    a = (Uint8 *)surface->pixels;
    b = a + (surface->h - 1) * surface->pitch;
    tmp = SDL_small_alloc(Uint8, surface->pitch, &isstack);
    إذا (!tmp) {
        أرجع false;
    }
    لكل (i = surface->h / 2; i--; ) {
        SDL_memcpy(tmp, a, surface->pitch);
        SDL_memcpy(a, b, surface->pitch);
        SDL_memcpy(b, tmp, surface->pitch);
        a += surface->pitch;
        b -= surface->pitch;
    }
    SDL_small_free(tmp, isstack);
    أرجع true;
}

bool SDL_FlipSurface(SDL_Surface *surface, SDL_Flip_منوال flip)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        أرجع SDL_InvalidParamError("surface");
    }
    إذا (!surface->pixels) {
        أرجع true;
    }

    bool نتیجہ = true;
    بدل (flip) {
    حالة SDL_FLIP_HORIZONTAL:
        نتیجہ = SDL_FlipSurfaceHorizontal(surface);
        اكسر;
    حالة SDL_FLIP_VERTICAL:
        نتیجہ = SDL_FlipSurfaceVertical(surface);
        اكسر;
    حالة SDL_FLIP_HORIZONTAL_AND_VERTICAL:
        نتیجہ &= SDL_FlipSurfaceHorizontal(surface);
        نتیجہ &= SDL_FlipSurfaceVertical(surface);
        اكسر;
    افتراضي:
        نتیجہ = SDL_InvalidParamError("flip");
        اكسر;
    }
    أرجع نتیجہ;
}

ساكن SDL_Surface *SDL_ConvertSurfaceRectAndColorspace(SDL_Surface *surface, ثابت SDL_Rect *rect, SDL_PixelFormat format, SDL_Palette *palette, SDL_Colorspace colorspace, SDL_PropertiesID props)
{
    SDL_Palette *عارضی_palette = عدم;
    SDL_Surface *convert = عدم;
    SDL_Colorspace src_colorspace;
    SDL_PropertiesID src_properties;
    Uint32 copy_flags;
    SDL_Color copy_color;
    SDL_Rect bounds;
    bool نتیجہ;
    bool palette_ck_transform = false;
    Uint8 palette_ck_قدر = 0;
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
    إذا (rect) {
        bounds.w = rect->w;
        bounds.h = rect->h;
    } وإلا {
        rect = &bounds;
    }

    // Check for empty destination palette! (results in empty image)
    إذا (palette) {
        صحيح i;
        لكل (i = 0; i < palette->ncolors; ++i) {
            إذا ((palette->colors[i].r != 0xFF) || (palette->colors[i].g != 0xFF) || (palette->colors[i].b != 0xFF)) {
                اكسر;
            }
        }
        إذا (i == palette->ncolors) {
            SDL_سیٹ_Error("Empty destination palette");
            اذهب error;
        }
    } وإلا إذا (SDL_ISPIXELFORMAT_اشاریہ_دار(format)) {
        // Create a dither palette for conversion
        عارضی_palette = SDL_CreatePalette(1 << SDL_BITSPERPIXEL(format));
        إذا (عارضی_palette) {
            SDL_DitherPalette(عارضی_palette);
            palette = عارضی_palette;
        }
    }

    src_colorspace = surface->colorspace;
    src_properties = surface->props;

    // Create a new surface with the desired format
    إذا (surface->pixels || SDL_MUSTLOCK(surface)) {
        convert = SDL_CreateSurfaceUninitialized(rect->w, rect->h, format);
    } وإلا {
        convert = SDL_CreateSurfaceFrom(rect->w, rect->h, format, عدم, 0);
    }
    إذا (!convert) {
        اذهب error;
    }
    إذا (SDL_ISPIXELFORMAT_اشاریہ_دار(format)) {
        SDL_سیٹ_Surface_Palette(convert, palette);
    }

    إذا (colorspace == SDL_COLORSPACE_UNKNOWN) {
        colorspace = src_colorspace;
    }
    SDL_سیٹ_Surface_Colorspace(convert, colorspace);

    إذا (SDL_ISPIXELFORMAT_FOURCC(format) || SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        إذا (surface->format == SDL_PIXELFORMAT_MJPG && format == SDL_PIXELFORMAT_MJPG) {
            // Just do a straight pixel copy of the JPEG image
            size_t ناپ = (size_t)surface->pitch;
            convert->pixels = SDL_malloc(ناپ);
            إذا (!convert->pixels) {
                اذهب error;
            }
            convert->flags &= ~SDL_SURFACE_PREALLOCATED;
            convert->pitch = surface->pitch;
            SDL_memcpy(convert->pixels, surface->pixels, ناپ);

        } وإلا إذا (!SDL_ConvertPixelsAndColorspace(surface->w, surface->h, surface->format, src_colorspace, src_properties, surface->pixels, surface->pitch, convert->format, colorspace, props, convert->pixels, convert->pitch)) {
            اذهب error;
        }

        // Save the original copy flags
        copy_flags = surface->map.info.flags;

        اذهب سرا;
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
    إذا (surface->palette && SDL_ISPIXELFORMAT_ALPHA(format)) {
        bool سیٹ_opaque = false;

        bool is_opaque, has_alpha_channel;
        SDL_DetectPalette(surface->palette, &is_opaque, &has_alpha_channel);

        إذا (is_opaque) {
            إذا (!has_alpha_channel) {
                سیٹ_opaque = true;
            }
        }

        // Set opaque and backup palette alpha values
        إذا (سیٹ_opaque) {
            صحيح i;
            palette_saved_alpha_ncolors = surface->palette->ncolors;
            إذا (palette_saved_alpha_ncolors > 0) {
                palette_saved_alpha = SDL_ڈھیر_alloc(Uint8, palette_saved_alpha_ncolors);
                لكل (i = 0; i < palette_saved_alpha_ncolors; i++) {
                    palette_saved_alpha[i] = surface->palette->colors[i].a;
                    surface->palette->colors[i].a = SDL_ALPHA_OPAQUE;
                }
            }
        }
    }

    // Transform colorkey to alpha. for cases where source palette has duplicate values, and colorkey is one of them
    إذا (copy_flags & SDL_COPY_COLORKEY) {
        إذا (surface->palette && !palette) {
            palette_ck_transform = true;
            palette_ck_قدر = surface->palette->colors[surface->map.info.colorkey].a;
            surface->palette->colors[surface->map.info.colorkey].a = SDL_ALPHA_TRANSPARENT;
        }
    }

    إذا (surface->pixels || SDL_MUSTLOCK(surface)) {
        نتیجہ = SDL_BlitSurfaceUnchecked(surface, rect, convert, &bounds);
    } وإلا {
        نتیجہ = true;
    }

    // Restore colorkey alpha value
    إذا (palette_ck_transform) {
        surface->palette->colors[surface->map.info.colorkey].a = palette_ck_قدر;
    }

    // Restore palette alpha values
    إذا (palette_saved_alpha) {
        صحيح i;
        لكل (i = 0; i < palette_saved_alpha_ncolors; i++) {
            surface->palette->colors[i].a = palette_saved_alpha[i];
        }
        SDL_ڈھیر_free(palette_saved_alpha);
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
    إذا (!نتیجہ) {
        اذهب error;
    }

    إذا (copy_flags & SDL_COPY_COLORKEY) {
        bool سیٹ_colorkey_by_color = false;
        bool convert_colorkey = true;

        إذا (surface->palette) {
            إذا (palette &&
                surface->palette->ncolors <= palette->ncolors &&
                (SDL_memcmp(surface->palette->colors, palette->colors,
                            surface->palette->ncolors * حجم(SDL_Color)) == 0)) {
                // The palette is identical, just set the same colorkey
                SDL_سیٹ_Surface_Color_کلید(convert, true, surface->map.info.colorkey);
            } وإلا إذا (!palette) {
                إذا (SDL_ISPIXELFORMAT_ALPHA(format)) {
                    // No need to add the colorkey, transparency is in the alpha channel
                } وإلا {
                    // Only set the colorkey information
                    سیٹ_colorkey_by_color = true;
                    convert_colorkey = false;
                }
            } وإلا {
                سیٹ_colorkey_by_color = true;
            }
        } وإلا {
            سیٹ_colorkey_by_color = true;
        }

        إذا (سیٹ_colorkey_by_color) {
            SDL_Surface *tmp;
            SDL_Surface *tmp2;
            صحيح converted_colorkey = 0;

            // Create a dummy surface to get the colorkey converted
            tmp = SDL_CreateSurfaceUninitialized(1, 1, surface->format);
            إذا (!tmp) {
                اذهب error;
            }

            // Share the palette, if any
            إذا (surface->palette) {
                SDL_سیٹ_Surface_Palette(tmp, surface->palette);
            }

            SDL_FillSurfaceRect(tmp, عدم, surface->map.info.colorkey);

            tmp->map.info.flags &= ~SDL_COPY_COLORKEY;

            // Conversion of the colorkey
            tmp2 = SDL_ConvertSurfaceAndColorspace(tmp, format, palette, colorspace, props);
            إذا (!tmp2) {
                SDL_DestroySurface(tmp);
                اذهب error;
            }

            // Get the converted colorkey
            SDL_memcpy(&converted_colorkey, tmp2->pixels, tmp2->fmt->بائٹاں_فی_pixel);

            SDL_DestroySurface(tmp);
            SDL_DestroySurface(tmp2);

            // Set the converted colorkey on the new surface
            SDL_سیٹ_Surface_Color_کلید(convert, true, converted_colorkey);

            // This is needed when converting for 3D texture upload
            إذا (convert_colorkey) {
                SDL_Convert_Colorkey_منزل_Alpha(convert, true);
            }
        }
    }

سرا:
    إذا (عارضی_palette) {
        SDL_DestroyPalette(عارضی_palette);
    }

    SDL_سیٹ_Surface_Clip_Rect(convert, &surface->clip_rect);

    /* Enable alpha blending by default if the new surface has an
     * alpha channel or alpha modulation */
    إذا (SDL_ISPIXELFORMAT_ALPHA(format) ||
        (copy_flags & SDL_COPY_MODULATE_ALPHA)) {
        SDL_سیٹ_Surface_Blend_منوال(convert, SDL_BLENDMODE_BLEND);
    }
    إذا (copy_flags & SDL_COPY_RLE_DESIRED) {
        SDL_سیٹ_Surface_RLE(convert, true);
    }

    // Copy alternate images
    لكل (صحيح i = 0; i < surface->عدد_images; ++i) {
        إذا (!SDL_جوڑو_Surface_Alternate_Image(convert, surface->images[i])) {
            اذهب error;
        }
    }

    // Copy properties
    إذا (surface->props) {
        إذا (!SDL_CopyProperties(surface->props, SDL_GetSurfaceProperties(convert))) {
            اذهب error;
        }

        // Make sure the new surface doesn't reference an old SDL2 surface.
        SDL_ClearProperty(SDL_GetSurfaceProperties(convert), "sdl2-compat.surface2");
    }

    // We're ready to go!
    أرجع convert;

error:
    إذا (عارضی_palette) {
        SDL_DestroyPalette(عارضی_palette);
    }
    إذا (convert) {
        SDL_DestroySurface(convert);
    }
    أرجع عدم;
}

SDL_Surface *SDL_ConvertSurfaceAndColorspace(SDL_Surface *surface, SDL_PixelFormat format, SDL_Palette *palette, SDL_Colorspace colorspace, SDL_PropertiesID props)
{
    أرجع SDL_ConvertSurfaceRectAndColorspace(surface, عدم, format, palette, colorspace, props);
}

SDL_Surface *SDL_RotateSurface(SDL_Surface *surface, عائم angle)
{
    SDL_Surface *rotated = عدم;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        أرجع عدم;
    }

    SDL_Rect rect_dest;
    مزدوج cangle, sangle;
    SDL_FPoint center = { surface->w * 0.5f, surface->h * 0.5f };
    SDLgfx_rotozoom_Surface_ناپ_Trig(surface->w, surface->h, angle, &center, &rect_dest, &cangle, &sangle);

    // This function requires a 32-bit surface or 8-bit surface with a colorkey
    إذا ((SDL_BITSPERPIXEL(surface->format) == 32 && SDL_PIXELLAYOUT(surface->format) == SDL_PACKEDLAYOUT_8888) ||
        (surface->format == SDL_PIXELFORMAT_INDEX8 && SDL_Surface_Has_Color_کلید(surface))) {
        rotated = SDLgfx_rotateSurface(surface, angle, 1, 0, 0, &rect_dest, cangle, sangle, &center);
    } وإلا {
        SDL_Surface *convert = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);
        إذا (convert) {
            SDL_Surface *tmp = SDLgfx_rotateSurface(convert, angle, 1, 0, 0, &rect_dest, cangle, sangle, &center);
            إذا (tmp) {
                rotated = SDL_ConvertSurfaceAndColorspace(tmp, surface->format, surface->palette, surface->colorspace, surface->props);
                SDL_DestroySurface(tmp);
            }
            SDL_DestroySurface(convert);
        }
    }

    إذا (rotated) {
        إذا (SDL_HasProperty(surface->props, SDL_PROP_SURFACE_ROTATION_FLOAT)) {
            ثابت عائم rotation = (SDL_Get_نمبر_Property(surface->props, SDL_PROP_SURFACE_ROTATION_FLOAT, 0) - angle);
            SDL_سیٹ_Float_Property(SDL_GetSurfaceProperties(rotated), SDL_PROP_SURFACE_ROTATION_FLOAT, rotation);
        }
    }

    أرجع rotated;
}

SDL_Surface *SDL_DuplicateSurface(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        أرجع عدم;
    }

    أرجع SDL_ConvertSurfaceAndColorspace(surface, surface->format, surface->palette, surface->colorspace, surface->props);
}

SDL_Surface *SDL_ScaleSurface(SDL_Surface *surface, صحيح چوڑائی, صحيح اچائی, SDL_Scale_منوال scale_منوال)
{
    SDL_Surface *convert = عدم;
    Uint32 copy_flags;
    SDL_Color copy_color;
    bool rc;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        اذهب error;
    }

    إذا (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // We can't directly scale a YUV surface (yet!)
        SDL_Surface *tmp = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        إذا (!tmp) {
            أرجع عدم;
        }

        SDL_Surface *scaled = SDL_ScaleSurface(tmp, چوڑائی, اچائی, scale_منوال);
        SDL_DestroySurface(tmp);
        إذا (!scaled) {
            أرجع عدم;
        }

        SDL_Surface *نتیجہ = SDL_ConvertSurfaceAndColorspace(scaled, surface->format, عدم, surface->colorspace, surface->props);
        SDL_DestroySurface(scaled);
        أرجع نتیجہ;
    }

    إذا (SDL_ISPIXELFORMAT_اشاریہ_دار(surface->format)) {
        // Linear scaling requires conversion to RGBA and then slow pixel color lookup
        scale_منوال = SDL_SCALEMODE_سبھ_توں_نیڑے;
    }

    // Create a new surface with the desired size
    إذا (surface->pixels || SDL_MUSTLOCK(surface)) {
        convert = SDL_CreateSurfaceUninitialized(چوڑائی, اچائی, surface->format);
    } وإلا {
        convert = SDL_CreateSurfaceFrom(چوڑائی, اچائی, surface->format, عدم, 0);
    }
    إذا (!convert) {
        اذهب error;
    }
    SDL_سیٹ_Surface_Palette(convert, surface->palette);
    SDL_سیٹ_Surface_Colorspace(convert, surface->colorspace);
    SDL_سیٹ_Surface_RLE(convert, SDL_SurfaceHasRLE(surface));

    إذا (surface->pixels || SDL_MUSTLOCK(surface)) {
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

        rc = SDL_BlitSurfaceScaled(surface, عدم, convert, عدم, scale_منوال);

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
    } وإلا {
        rc = true;
    }

    // SDL_BlitSurfaceScaled failed, and so the conversion
    إذا (!rc) {
        اذهب error;
    }

    // We're ready to go!
    أرجع convert;

error:
    إذا (convert) {
        SDL_DestroySurface(convert);
    }
    أرجع عدم;
}

SDL_Surface *SDL_ConvertSurfaceRect(SDL_Surface *surface, ثابت SDL_Rect *rect, SDL_PixelFormat format)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        أرجع عدم;
    }

    أرجع SDL_ConvertSurfaceRectAndColorspace(surface, rect, format, عدم, SDL_GetDefaultColorspaceForFormat(format), surface->props);
}

SDL_Surface *SDL_ConvertSurface(SDL_Surface *surface, SDL_PixelFormat format)
{
    أرجع SDL_ConvertSurfaceRect(surface, عدم, format);
}

SDL_Surface *SDL_DuplicatePixels(صحيح چوڑائی, صحيح اچائی, SDL_PixelFormat format, SDL_Colorspace colorspace, فراغ *pixels, صحيح pitch)
{
    SDL_Surface *surface;
    إذا (pixels) {
        surface = SDL_CreateSurfaceUninitialized(چوڑائی, اچائی, format);
    } وإلا {
        surface = SDL_CreateSurfaceFrom(چوڑائی, اچائی, format, عدم, 0);
    }
    إذا (!surface) {
        أرجع عدم;
    }
    SDL_سیٹ_Surface_Colorspace(surface, colorspace);

    إذا (surface->pixels) {
        صحيح لمائی = چوڑائی * SDL_BYTESPERPIXEL(format);
        Uint8 *src = (Uint8 *)pixels;
        Uint8 *dst = (Uint8 *)surface->pixels;
        صحيح صفاں = اچائی;
        طالما (صفاں--) {
            SDL_memcpy(dst, src, لمائی);
            dst += surface->pitch;
            src += pitch;
        }
    }
    أرجع surface;
}

bool SDL_ConvertPixelsAndColorspace(صحيح چوڑائی, صحيح اچائی,
                      SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ثابت فراغ *src, صحيح src_pitch,
                      SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, فراغ *dst, صحيح dst_pitch)
{
    SDL_Surface src_surface;
    SDL_Surface dst_surface;
    SDL_Rect rect;
    فراغ *nonconst_src = (فراغ *)src;
    bool نتیجہ;

    CHECK_PARAM(!src) {
        أرجع SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!src_pitch) {
        أرجع SDL_InvalidParamError("src_pitch");
    }
    CHECK_PARAM(!dst) {
        أرجع SDL_InvalidParamError("dst");
    }
    CHECK_PARAM(!dst_pitch) {
        أرجع SDL_InvalidParamError("dst_pitch");
    }

    إذا (src_colorspace == SDL_COLORSPACE_UNKNOWN) {
        src_colorspace = SDL_GetDefaultColorspaceForFormat(src_format);
    }
    إذا (dst_colorspace == SDL_COLORSPACE_UNKNOWN) {
        dst_colorspace = SDL_GetDefaultColorspaceForFormat(dst_format);
    }

    إذا (src_format == SDL_PIXELFORMAT_MJPG) {
        أرجع SDL_ConvertPixels_STB(چوڑائی, اچائی, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    }

#جے_تعریف_شدہ SDL_HAVE_YUV
    إذا (SDL_ISPIXELFORMAT_FOURCC(src_format) && SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        أرجع SDL_Convert_Pixels_YUV_منزل_YUV(چوڑائی, اچائی, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } وإلا إذا (SDL_ISPIXELFORMAT_FOURCC(src_format)) {
        أرجع SDL_Convert_Pixels_YUV_منزل_RGB(چوڑائی, اچائی, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } وإلا إذا (SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        أرجع SDL_Convert_Pixels_RGB_منزل_YUV(چوڑائی, اچائی, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    }
#وإلا
    إذا (SDL_ISPIXELFORMAT_FOURCC(src_format) || SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        أرجع SDL_سیٹ_Error("SDL not built with YUV support");
    }
#جے_انت

    // Fast path for same format copy
    إذا (src_format == dst_format && src_colorspace == dst_colorspace) {
        إذا (src_pitch == dst_pitch) {
            SDL_memcpy(dst, src, اچائی * src_pitch);
        } وإلا {
            صحيح i;
            ثابت صحيح bpp = SDL_BYTESPERPIXEL(src_format);
            چوڑائی *= bpp;
            لكل (i = اچائی; i--;) {
                SDL_memcpy(dst, src, چوڑائی);
                src = (ثابت Uint8 *)src + src_pitch;
                dst = (Uint8 *)dst + dst_pitch;
            }
        }
        أرجع true;
    }

    إذا (!SDL_InitializeSurface(&src_surface, چوڑائی, اچائی, src_format, src_colorspace, src_properties, nonconst_src, src_pitch, true)) {
        أرجع false;
    }
    SDL_سیٹ_Surface_Blend_منوال(&src_surface, SDL_BLENDMODE_NONE);

    إذا (!SDL_InitializeSurface(&dst_surface, چوڑائی, اچائی, dst_format, dst_colorspace, dst_properties, dst, dst_pitch, true)) {
        أرجع false;
    }

    // Set up the rect and go!
    rect.x = 0;
    rect.y = 0;
    rect.w = چوڑائی;
    rect.h = اچائی;
    نتیجہ = SDL_BlitSurfaceUnchecked(&src_surface, &rect, &dst_surface, &rect);

    SDL_DestroySurface(&src_surface);
    SDL_DestroySurface(&dst_surface);

    أرجع نتیجہ;
}

bool SDL_ConvertPixels(صحيح چوڑائی, صحيح اچائی, SDL_PixelFormat src_format, ثابت فراغ *src, صحيح src_pitch, SDL_PixelFormat dst_format, فراغ *dst, صحيح dst_pitch)
{
    أرجع SDL_ConvertPixelsAndColorspace(چوڑائی, اچائی,
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

ساكن فراغ SDL_PremultiplyAlpha_AXYZ8888(صحيح چوڑائی, صحيح اچائی, ثابت فراغ *src, صحيح src_pitch, فراغ *dst, صحيح dst_pitch)
{
    صحيح c;
    Uint32 srcpixel;
    Uint32 srcR, srcG, srcB, srcA;
    Uint32 dstpixel;
    Uint32 dstR, dstG, dstB, dstA;

    طالما (اچائی--) {
        ثابت Uint32 *src_px = (ثابت Uint32 *)src;
        Uint32 *dst_px = (Uint32 *)dst;
        لكل (c = چوڑائی; c; --c) {
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

ساكن فراغ SDL_PremultiplyAlpha_XYZA8888(صحيح چوڑائی, صحيح اچائی, ثابت فراغ *src, صحيح src_pitch, فراغ *dst, صحيح dst_pitch)
{
    صحيح c;
    Uint32 srcpixel;
    Uint32 srcR, srcG, srcB, srcA;
    Uint32 dstpixel;
    Uint32 dstR, dstG, dstB, dstA;

    طالما (اچائی--) {
        ثابت Uint32 *src_px = (ثابت Uint32 *)src;
        Uint32 *dst_px = (Uint32 *)dst;
        لكل (c = چوڑائی; c; --c) {
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

ساكن فراغ SDL_PremultiplyAlpha_AXYZ128(صحيح چوڑائی, صحيح اچائی, ثابت فراغ *src, صحيح src_pitch, فراغ *dst, صحيح dst_pitch)
{
    صحيح c;
    عائم flR, flG, flB, flA;

    طالما (اچائی--) {
        ثابت عائم *src_px = (ثابت عائم *)src;
        عائم *dst_px = (عائم *)dst;
        لكل (c = چوڑائی; c; --c) {
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

ساكن bool SDL_PremultiplyAlphaPixelsAndColorspace(صحيح چوڑائی, صحيح اچائی, SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ثابت فراغ *src, صحيح src_pitch, SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, فراغ *dst, صحيح dst_pitch, bool خطی)
{
    SDL_Surface *convert = عدم;
    فراغ *final_dst = dst;
    صحيح final_dst_pitch = dst_pitch;
    SDL_PixelFormat format;
    SDL_Colorspace colorspace;
    bool نتیجہ = false;

    CHECK_PARAM(!src) {
        أرجع SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!src_pitch) {
        أرجع SDL_InvalidParamError("src_pitch");
    }
    CHECK_PARAM(!dst) {
        أرجع SDL_InvalidParamError("dst");
    }
    CHECK_PARAM(!dst_pitch) {
        أرجع SDL_InvalidParamError("dst_pitch");
    }

    // Use a high precision format if we're converting to linear colorspace or using high precision pixel formats
    إذا (خطی ||
        SDL_ISPIXELFORMAT_10_ثنائی_ہندسہ(src_format) || SDL_BITSPERPIXEL(src_format) > 32 ||
        SDL_ISPIXELFORMAT_10_ثنائی_ہندسہ(dst_format) || SDL_BITSPERPIXEL(dst_format) > 32) {
        إذا (src_format == SDL_PIXELFORMAT_ARGB128_FLOAT ||
            src_format == SDL_PIXELFORMAT_ABGR128_FLOAT) {
            format = src_format;
        } وإلا {
            format = SDL_PIXELFORMAT_ARGB128_FLOAT;
        }
    } وإلا {
        إذا (src_format == SDL_PIXELFORMAT_ARGB8888 ||
            src_format == SDL_PIXELFORMAT_ABGR8888 ||
            src_format == SDL_PIXELFORMAT_RGBA8888 ||
            src_format == SDL_PIXELFORMAT_BGRA8888) {
            format = src_format;
        } وإلا {
            format = SDL_PIXELFORMAT_ARGB8888;
        }
    }
    إذا (خطی) {
        colorspace = SDL_COLORSPACE_SRGB_خطی;
    } وإلا {
        colorspace = SDL_COLORSPACE_SRGB;
    }

    إذا (src_format != format || src_colorspace != colorspace) {
        convert = SDL_CreateSurfaceUninitialized(چوڑائی, اچائی, format);
        إذا (!convert) {
            اذهب پورا;
        }
        إذا (!SDL_ConvertPixelsAndColorspace(چوڑائی, اچائی, src_format, src_colorspace, src_properties, src, src_pitch, format, colorspace, 0, convert->pixels, convert->pitch)) {
            اذهب پورا;
        }

        src = convert->pixels;
        src_pitch = convert->pitch;
        dst = convert->pixels;
        dst_pitch = convert->pitch;

    } وإلا إذا (dst_format != format || dst_colorspace != colorspace) {
        convert = SDL_CreateSurfaceUninitialized(چوڑائی, اچائی, format);
        إذا (!convert) {
            اذهب پورا;
        }
        dst = convert->pixels;
        dst_pitch = convert->pitch;
    }

    بدل (format) {
    حالة SDL_PIXELFORMAT_ARGB8888:
    حالة SDL_PIXELFORMAT_ABGR8888:
        SDL_PremultiplyAlpha_AXYZ8888(چوڑائی, اچائی, src, src_pitch, dst, dst_pitch);
        اكسر;
    حالة SDL_PIXELFORMAT_RGBA8888:
    حالة SDL_PIXELFORMAT_BGRA8888:
        SDL_PremultiplyAlpha_XYZA8888(چوڑائی, اچائی, src, src_pitch, dst, dst_pitch);
        اكسر;
    حالة SDL_PIXELFORMAT_ARGB128_FLOAT:
    حالة SDL_PIXELFORMAT_ABGR128_FLOAT:
        SDL_PremultiplyAlpha_AXYZ128(چوڑائی, اچائی, src, src_pitch, dst, dst_pitch);
        اكسر;
    افتراضي:
        SDL_سیٹ_Error("Unexpected internal pixel format");
        اذهب پورا;
    }

    إذا (dst != final_dst) {
        إذا (!SDL_ConvertPixelsAndColorspace(چوڑائی, اچائی, format, colorspace, 0, convert->pixels, convert->pitch, dst_format, dst_colorspace, dst_properties, final_dst, final_dst_pitch)) {
            اذهب پورا;
        }
    }
    نتیجہ = true;

پورا:
    إذا (convert) {
        SDL_DestroySurface(convert);
    }
    أرجع نتیجہ;
}

bool SDL_PremultiplyAlpha(صحيح چوڑائی, صحيح اچائی,
                         SDL_PixelFormat src_format, ثابت فراغ *src, صحيح src_pitch,
                         SDL_PixelFormat dst_format, فراغ *dst, صحيح dst_pitch, bool خطی)
{
    SDL_Colorspace src_colorspace = SDL_GetDefaultColorspaceForFormat(src_format);
    SDL_Colorspace dst_colorspace = SDL_GetDefaultColorspaceForFormat(dst_format);

    أرجع SDL_PremultiplyAlphaPixelsAndColorspace(چوڑائی, اچائی, src_format, src_colorspace, 0, src, src_pitch, dst_format, dst_colorspace, 0, dst, dst_pitch, خطی);
}

bool SDL_PremultiplySurfaceAlpha(SDL_Surface *surface, bool خطی)
{
    SDL_Colorspace colorspace;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        أرجع SDL_InvalidParamError("surface");
    }

    colorspace = surface->colorspace;

    أرجع SDL_PremultiplyAlphaPixelsAndColorspace(surface->w, surface->h, surface->format, colorspace, surface->props, surface->pixels, surface->pitch, surface->format, colorspace, surface->props, surface->pixels, surface->pitch, خطی);
}

bool SDL_ClearSurface(SDL_Surface *surface, عائم r, عائم g, عائم b, عائم a)
{
    SDL_Rect clip_rect;
    bool نتیجہ = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        أرجع SDL_InvalidParamError("surface");
    }

    SDL_GetSurfaceClipRect(surface, &clip_rect);
    SDL_سیٹ_Surface_Clip_Rect(surface, عدم);

    إذا (!SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_BYTESPERPIXEL(surface->format) <= حجم(Uint32)) {
        Uint32 color;

        color = SDL_MapSurfaceRGBA(surface,
                    (Uint8)SDL_roundf(SDL_clamp(r, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(g, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(b, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(a, 0.0f, 1.0f) * 255.0f));
        نتیجہ = SDL_FillSurfaceRect(surface, عدم, color);
    } وإلا إذا (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // We can't directly set an RGB value on a YUV surface
        SDL_Surface *tmp = SDL_CreateSurfaceUninitialized(surface->w, surface->h, SDL_PIXELFORMAT_ARGB8888);
        إذا (!tmp) {
            اذهب پورا;
        }

        إذا (SDL_ClearSurface(tmp, r, g, b, a)) {
            نتیجہ = SDL_ConvertPixelsAndColorspace(surface->w, surface->h, tmp->format, tmp->colorspace, tmp->props, tmp->pixels, tmp->pitch, surface->format, surface->colorspace, surface->props, surface->pixels, surface->pitch);
        }
        SDL_DestroySurface(tmp);
    } وإلا {
        // Take advantage of blit color conversion
        SDL_Surface *tmp = SDL_CreateSurfaceUninitialized(1, 1, SDL_PIXELFORMAT_RGBA128_FLOAT);
        إذا (!tmp) {
            اذهب پورا;
        }
        SDL_سیٹ_Surface_Colorspace(tmp, surface->colorspace);
        SDL_سیٹ_Surface_Blend_منوال(tmp, SDL_BLENDMODE_NONE);

        عائم *pixels = (عائم *)tmp->pixels;
        pixels[0] = r;
        pixels[1] = g;
        pixels[2] = b;
        pixels[3] = a;

        نتیجہ = SDL_BlitSurfaceScaled(tmp, عدم, surface, عدم, SDL_SCALEMODE_سبھ_توں_نیڑے);
        SDL_DestroySurface(tmp);
    }

پورا:
    SDL_سیٹ_Surface_Clip_Rect(surface, &clip_rect);

    أرجع نتیجہ;
}

Uint32 SDL_MapSurfaceRGB(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b)
{
    أرجع SDL_MapSurfaceRGBA(surface, r, g, b, SDL_ALPHA_OPAQUE);
}

Uint32 SDL_MapSurfaceRGBA(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        أرجع true;
    }
    أرجع SDL_MapRGBA(surface->fmt, surface->palette, r, g, b, a);
}

// This function Copyright 2023 Collabora Ltd., contributed to SDL under the ZLib license
bool SDL_ReadSurfacePixel(SDL_Surface *surface, صحيح x, صحيح y, Uint8 *r, Uint8 *g, Uint8 *b, Uint8 *a)
{
    Uint32 pixel = 0;
    size_t بائٹاں_فی_pixel;
    Uint8 بن_ورتیا;
    Uint8 *p;
    bool نتیجہ = false;

    إذا (r) {
        *r = 0;
    } وإلا {
        r = &بن_ورتیا;
    }

    إذا (g) {
        *g = 0;
    } وإلا {
        g = &بن_ورتیا;
    }

    إذا (b) {
        *b = 0;
    } وإلا {
        b = &بن_ورتیا;
    }

    إذا (a) {
        *a = 0;
    } وإلا {
        a = &بن_ورتیا;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        أرجع SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        أرجع SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        أرجع SDL_InvalidParamError("y");
    }

    بائٹاں_فی_pixel = SDL_BYTESPERPIXEL(surface->format);

    إذا (SDL_MUSTLOCK(surface)) {
        إذا (!SDL_جندرا_Surface(surface)) {
            أرجع false;
        }
    }

    p = (Uint8 *)surface->pixels + y * surface->pitch + x * بائٹاں_فی_pixel;

    إذا (بائٹاں_فی_pixel <= حجم(pixel) &&
        !SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_COLORSPACEPRIMARIES(surface->colorspace) == SDL_COLOR_PRIMARIES_BT709) {
        /* Fill the appropriate number of least-significant bytes of pixel,
         * leaving the most-significant bytes set to zero */
#إذا SDL_BYTEORDER == SDL_BIG_ENDIAN
        SDL_memcpy(((Uint8 *)&pixel) + (حجم(pixel) - بائٹاں_فی_pixel), p, بائٹاں_فی_pixel);
#وإلا
        SDL_memcpy(&pixel, p, بائٹاں_فی_pixel);
#جے_انت
        SDL_GetRGBA(pixel, surface->fmt, surface->palette, r, g, b, a);
        نتیجہ = true;
    } وإلا إذا (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // FIXME: We need code to extract a single macroblock from a YUV surface
        SDL_Surface *converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        إذا (converted) {
            نتیجہ = SDL_ReadSurfacePixel(converted, x, y, r, g, b, a);
            SDL_DestroySurface(converted);
        }
    } وإلا {
        // This is really slow, but it gets the job done
        Uint8 rgba[4];

        إذا (SDL_ConvertPixelsAndColorspace(1, 1, surface->format, surface->colorspace, surface->props, p, surface->pitch, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, rgba, حجم(rgba))) {
            *r = rgba[0];
            *g = rgba[1];
            *b = rgba[2];
            *a = rgba[3];
            نتیجہ = true;
        }
    }

    إذا (SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }
    أرجع نتیجہ;
}

bool SDL_ReadSurfacePixelFloat(SDL_Surface *surface, صحيح x, صحيح y, عائم *r, عائم *g, عائم *b, عائم *a)
{
    عائم بن_ورتیا;
    bool نتیجہ = false;

    إذا (r) {
        *r = 0.0f;
    } وإلا {
        r = &بن_ورتیا;
    }

    إذا (g) {
        *g = 0.0f;
    } وإلا {
        g = &بن_ورتیا;
    }

    إذا (b) {
        *b = 0.0f;
    } وإلا {
        b = &بن_ورتیا;
    }

    إذا (a) {
        *a = 0.0f;
    } وإلا {
        a = &بن_ورتیا;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        أرجع SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        أرجع SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        أرجع SDL_InvalidParamError("y");
    }

    إذا (SDL_BYTESPERPIXEL(surface->format) <= حجم(Uint32) &&
        !SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_COLORSPACEPRIMARIES(surface->colorspace) == SDL_COLOR_PRIMARIES_BT709) {
        Uint8 r8, g8, b8, a8;

        إذا (SDL_ReadSurfacePixel(surface, x, y, &r8, &g8, &b8, &a8)) {
            *r = (عائم)r8 / 255.0f;
            *g = (عائم)g8 / 255.0f;
            *b = (عائم)b8 / 255.0f;
            *a = (عائم)a8 / 255.0f;
            نتیجہ = true;
        }
    } وإلا إذا (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // FIXME: We need code to extract a single macroblock from a YUV surface
        SDL_Surface *converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        إذا (converted) {
            نتیجہ = SDL_ReadSurfacePixelFloat(converted, x, y, r, g, b, a);
            SDL_DestroySurface(converted);
        }
    } وإلا {
        // This is really slow, but it gets the job done
        عائم rgba[4];
        Uint8 *p;

        إذا (SDL_MUSTLOCK(surface)) {
            إذا (!SDL_جندرا_Surface(surface)) {
                أرجع false;
            }
        }

        p = (Uint8 *)surface->pixels + y * surface->pitch + x * SDL_BYTESPERPIXEL(surface->format);

        إذا (surface->format == SDL_PIXELFORMAT_RGBA128_FLOAT) {
            SDL_memcpy(rgba, p, حجم(rgba));
            نتیجہ = true;
        } وإلا {
            SDL_Colorspace src_colorspace = surface->colorspace;
            SDL_Colorspace dst_colorspace = (src_colorspace == SDL_COLORSPACE_SRGB_خطی ? SDL_COLORSPACE_SRGB_خطی : SDL_COLORSPACE_SRGB);

            إذا (SDL_ConvertPixelsAndColorspace(1, 1, surface->format, src_colorspace, surface->props, p, surface->pitch, SDL_PIXELFORMAT_RGBA128_FLOAT, dst_colorspace, 0, rgba, حجم(rgba))) {
                نتیجہ = true;
            }
        }

        إذا (نتیجہ) {
            *r = rgba[0];
            *g = rgba[1];
            *b = rgba[2];
            *a = rgba[3];
        }

        إذا (SDL_MUSTLOCK(surface)) {
            SDL_UnlockSurface(surface);
        }
    }
    أرجع نتیجہ;
}

bool SDL_WriteSurfacePixel(SDL_Surface *surface, صحيح x, صحيح y, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    Uint32 pixel = 0;
    size_t بائٹاں_فی_pixel;
    Uint8 *p;
    bool نتیجہ = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        أرجع SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        أرجع SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        أرجع SDL_InvalidParamError("y");
    }

    بائٹاں_فی_pixel = SDL_BYTESPERPIXEL(surface->format);

    إذا (SDL_MUSTLOCK(surface)) {
        إذا (!SDL_جندرا_Surface(surface)) {
            أرجع false;
        }
    }

    p = (Uint8 *)surface->pixels + y * surface->pitch + x * بائٹاں_فی_pixel;

    إذا (بائٹاں_فی_pixel <= حجم(pixel) && !SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        pixel = SDL_MapRGBA(surface->fmt, surface->palette, r, g, b, a);
#إذا SDL_BYTEORDER == SDL_BIG_ENDIAN
        SDL_memcpy(p, ((Uint8 *)&pixel) + (حجم(pixel) - بائٹاں_فی_pixel), بائٹاں_فی_pixel);
#وإلا
        SDL_memcpy(p, &pixel, بائٹاں_فی_pixel);
#جے_انت
        نتیجہ = true;
    } وإلا إذا (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        نتیجہ = SDL_Unsupported();
    } وإلا {
        // This is really slow, but it gets the job done
        Uint8 rgba[4];

        rgba[0] = r;
        rgba[1] = g;
        rgba[2] = b;
        rgba[3] = a;
        نتیجہ = SDL_ConvertPixelsAndColorspace(1, 1, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, rgba, حجم(rgba), surface->format, surface->colorspace, surface->props, p, surface->pitch);
    }

    إذا (SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }
    أرجع نتیجہ;
}

bool SDL_WriteSurfacePixelFloat(SDL_Surface *surface, صحيح x, صحيح y, عائم r, عائم g, عائم b, عائم a)
{
    bool نتیجہ = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        أرجع SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        أرجع SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        أرجع SDL_InvalidParamError("y");
    }

    إذا (SDL_BYTESPERPIXEL(surface->format) <= حجم(Uint32) && !SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        Uint8 r8, g8, b8, a8;

        r8 = (Uint8)SDL_گیڑا(SDL_clamp(r, 0.0f, 1.0f) * 255.0f);
        g8 = (Uint8)SDL_گیڑا(SDL_clamp(g, 0.0f, 1.0f) * 255.0f);
        b8 = (Uint8)SDL_گیڑا(SDL_clamp(b, 0.0f, 1.0f) * 255.0f);
        a8 = (Uint8)SDL_گیڑا(SDL_clamp(a, 0.0f, 1.0f) * 255.0f);
        إذا (SDL_WriteSurfacePixel(surface, x, y, r8, g8, b8, a8)) {
            نتیجہ = true;
        }
    } وإلا إذا (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        نتیجہ = SDL_Unsupported();
    } وإلا {
        // This is really slow, but it gets the job done
        عائم rgba[4];
        Uint8 *p;

        إذا (SDL_MUSTLOCK(surface)) {
            إذا (!SDL_جندرا_Surface(surface)) {
                أرجع false;
            }
        }

        p = (Uint8 *)surface->pixels + y * surface->pitch + x * SDL_BYTESPERPIXEL(surface->format);

        rgba[0] = r;
        rgba[1] = g;
        rgba[2] = b;
        rgba[3] = a;

        إذا (surface->format == SDL_PIXELFORMAT_RGBA128_FLOAT) {
            SDL_memcpy(p, rgba, حجم(rgba));
            نتیجہ = true;
        } وإلا {
            SDL_Colorspace dst_colorspace = surface->colorspace;
            SDL_Colorspace src_colorspace = (dst_colorspace == SDL_COLORSPACE_SRGB_خطی ? SDL_COLORSPACE_SRGB_خطی : SDL_COLORSPACE_SRGB);

            نتیجہ = SDL_ConvertPixelsAndColorspace(1, 1, SDL_PIXELFORMAT_RGBA128_FLOAT, src_colorspace, 0, rgba, حجم(rgba), surface->format, dst_colorspace, surface->props, p, surface->pitch);
        }

        إذا (SDL_MUSTLOCK(surface)) {
            SDL_UnlockSurface(surface);
        }
    }
    أرجع نتیجہ;
}

/*
 * Free a surface created by the above function.
 */
فراغ SDL_DestroySurface(SDL_Surface *surface)
{
    إذا (!SDL_SurfaceValid(surface)) {
        أرجع;
    }
    إذا (surface->اندرونی_flags & SDL_اندرونی_SURFACE_DONTFREE) {
        أرجع;
    }
    إذا (--surface->refcount > 0) {
        أرجع;
    }

    SDL_RemoveSurfaceAlternateImages(surface);

    SDL_DestroyProperties(surface->props);

    SDL_InvalidateMap(&surface->map);

    طالما (surface->locked > 0) {
        SDL_UnlockSurface(surface);
    }
#جے_تعریف_شدہ SDL_HAVE_RLE
    إذا (surface->اندرونی_flags & SDL_اندرونی_SURFACE_RLEACCEL) {
        SDL_UnRLESurface(surface);
    }
#جے_انت
    SDL_سیٹ_Surface_Palette(surface, عدم);

    إذا (surface->flags & SDL_SURFACE_PREALLOCATED) {
        // Don't free
    } وإلا إذا (surface->flags & SDL_SURFACE_SIMD_ALIGNED) {
        // Free aligned
        SDL_aligned_free(surface->pixels);
    } وإلا {
        // Normal
        SDL_free(surface->pixels);
    }

    surface->reserved = عدم;

    إذا (!(surface->اندرونی_flags & SDL_اندرونی_SURFACE_ڈھیر)) {
        SDL_free(surface);
    }
}

SDL_Surface *SDL_لدو_Surface_IO(SDL_IOStream *src, bool closeio)
{
    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        أرجع عدم;
    }

    إذا (SDL_IsBMP(src)) {
        أرجع SDL_لدو_BMP_IO(src, closeio);
    } وإلا إذا (SDL_IsPNG(src)) {
        أرجع SDL_لدو_PNG_IO(src, closeio);
    } وإلا إذا (SDL_IsJPG(src)) {
        أرجع SDL_لدو_JPG_IO(src, closeio);
    } وإلا {
        إذا (closeio) {
            SDL_CloseIO(src);
        }
        SDL_سیٹ_Error("Unsupported image format");
        أرجع عدم;
    }
}

SDL_Surface *SDL_لدو_Surface(ثابت حرف *file)
{
    SDL_IOStream *دھارا = SDL_IOFromFile(file, "rb");
    إذا (!دھارا) {
        أرجع عدم;
    }

    أرجع SDL_لدو_Surface_IO(دھارا, true);
}
