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
SDL_COMPILE_زمان_ASSERT(surface_اندازه_assumptions,
                        حجم(صحيح) == حجم(Sint32) && حجم(size_t) >= حجم(Sint32));

SDL_COMPILE_زمان_ASSERT(can_indicate_سرریز, SDL_اندازه_MAX > SDL_MAX_SINT32);

// Magic!
ساكن حرف SDL_surface_magic;

// Public routines

bool SDL_SurfaceValid(SDL_Surface *surface)
{
    أرجع (surface && surface->reserved == &SDL_surface_magic);
}

فراغ SDL_Update_Surface_قفل_Flag(SDL_Surface *surface)
{
    // We need to mark the surface as needing unlock while locked
    إذا ((surface->flags & SDL_SURFACE_LOCKED) ||
        (surface->داخلی_flags & SDL_داخلی_SURFACE_RLEACCEL)) {
        surface->flags |= SDL_SURFACE_قفل_NEEDED;
    } وإلا {
        surface->flags &= ~SDL_SURFACE_قفل_NEEDED;
    }
}

/*
 * Calculate the pad-aligned scanline width of a surface.
 *
 * for FOURCC, use SDL_CalculateYUVSize()
 */
ساكن bool SDL_CalculateRGBSize(Uint32 format, size_t عرض, size_t ارتفاع, size_t *اندازه, size_t *pitch, bool کمینه)
{
    إذا (SDL_BITSPERPIXEL(format) >= 8) {
        إذا (!SDL_اندازه_mul_check_سرریز(عرض, SDL_BYTESPERPIXEL(format), pitch)) {
            أرجع SDL_مجموعه_Error("width * bpp would overflow");
        }
    } وإلا {
        إذا (!SDL_اندازه_mul_check_سرریز(عرض, SDL_BITSPERPIXEL(format), pitch)) {
            أرجع SDL_مجموعه_Error("width * bpp would overflow");
        }
        إذا (!SDL_اندازه_جمع_کن_check_سرریز(*pitch, 7, pitch)) {
            أرجع SDL_مجموعه_Error("aligning pitch would overflow");
        }
        *pitch /= 8;
    }
    إذا (!کمینه) {
        // 4-byte aligning for speed
        إذا (!SDL_اندازه_جمع_کن_check_سرریز(*pitch, 3, pitch)) {
            أرجع SDL_مجموعه_Error("aligning pitch would overflow");
        }
        *pitch &= ~3;
    }

    إذا (!SDL_اندازه_mul_check_سرریز(ارتفاع, *pitch, اندازه)) {
        أرجع SDL_مجموعه_Error("height * pitch would overflow");
    }

    أرجع true;
}

bool SDL_Calculate_Surface_اندازه(SDL_PixelFormat format, صحيح عرض, صحيح ارتفاع, size_t *اندازه, size_t *pitch, bool کمینه_Pitch)
{
    size_t p = 0, sz = 0;

    إذا (اندازه) {
        *اندازه = 0;
    }

    إذا (pitch) {
        *pitch = 0;
    }

    إذا (SDL_ISPIXELFORMAT_FOURCC(format)) {
        إذا (format == SDL_PIXELFORMAT_MJPG) {
            // We don't know in advance what it will be, we'll figure it out later.
            أرجع true;
        }

        إذا (!SDL_CalculateYUVSize(format, عرض, ارتفاع, &sz, &p)) {
            // Overflow...
            أرجع false;
        }
    } وإلا {
        إذا (!SDL_CalculateRGBSize(format, عرض, ارتفاع, &sz, &p, کمینه_Pitch)) {
            // Overflow...
            أرجع false;
        }
    }

    إذا (اندازه) {
        *اندازه = sz;
    }

    إذا (pitch) {
        *pitch = p;
    }

    أرجع true;
}

ساكن bool SDL_InitializeSurface(SDL_Surface *surface, صحيح عرض, صحيح ارتفاع, SDL_PixelFormat format, SDL_Colorspace colorspace, SDL_PropertiesID props, فراغ *pixels, صحيح pitch, bool onstack)
{
    SDL_zerop(surface);

    surface->flags = SDL_SURFACE_PREALLOCATED;
    surface->format = format;
    surface->w = عرض;
    surface->h = ارتفاع;
    surface->pixels = pixels;
    surface->pitch = pitch;
    surface->reserved = &SDL_surface_magic;

    إذا (onstack) {
        surface->داخلی_flags |= SDL_داخلی_SURFACE_پشته;
    }

    surface->fmt = SDL_GetPixelFormatDetails(format);
    إذا (!surface->fmt) {
        SDL_DestroySurface(surface);
        أرجع false;
    }

    // Initialize the clip rect
    surface->clip_rect.w = عرض;
    surface->clip_rect.h = ارتفاع;

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
        SDL_مجموعه_Surface_Blend_نما(surface, SDL_BLENDMODE_BLEND);
    }

    // The surface is ready to go
    surface->refcount = 1;
    أرجع true;
}

/*
 * Create an empty surface of the appropriate depth using the given format
 */
ساكن SDL_Surface *SDL_Create_Surface_داخلی(صحيح عرض, صحيح ارتفاع, SDL_PixelFormat format, bool clear_surface)
{
    size_t pitch, اندازه;
    SDL_Surface *surface;

    CHECK_PARAM(عرض < 0) {
        SDL_InvalidParamError("width");
        أرجع عدم;
    }

    CHECK_PARAM(ارتفاع < 0) {
        SDL_InvalidParamError("height");
        أرجع عدم;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        أرجع عدم;
    }

    إذا (!SDL_Calculate_Surface_اندازه(format, عرض, ارتفاع, &اندازه, &pitch, false /* not minimal pitch */)) {
        // Overflow...
        أرجع عدم;
    }

    // Allocate and initialize the surface
    surface = (SDL_Surface *)SDL_malloc(حجم(*surface));
    إذا (!surface) {
        أرجع عدم;
    }

    إذا (!SDL_InitializeSurface(surface, عرض, ارتفاع, format, SDL_COLORSPACE_UNKNOWN, 0, عدم, (صحيح)pitch, false)) {
        أرجع عدم;
    }

    إذا (surface->w && surface->h && format != SDL_PIXELFORMAT_MJPG) {
        surface->flags &= ~SDL_SURFACE_PREALLOCATED;
        إذا (SDL_GetHintBoolean("SDL_SURFACE_MALLOC", false)) {
            إذا (clear_surface) {
                surface->pixels = SDL_calloc(1, اندازه);
            } وإلا {
                surface->pixels = SDL_malloc(اندازه);
            }
        } وإلا {
            surface->flags |= SDL_SURFACE_SIMD_ALIGNED;
            إذا (clear_surface) {
                surface->pixels = SDL_aligned_alloc_zero(SDL_GetSIMDAlignment(), اندازه);
            } وإلا {
                surface->pixels = SDL_aligned_alloc(SDL_GetSIMDAlignment(), اندازه);
            }
        }
        إذا (!surface->pixels) {
            SDL_DestroySurface(surface);
            أرجع عدم;
        }
    }
    أرجع surface;
}

SDL_Surface *SDL_CreateSurfaceZeroed(صحيح عرض, صحيح ارتفاع, SDL_PixelFormat format)
{
    أرجع SDL_Create_Surface_داخلی(عرض, ارتفاع, format, true);
}

SDL_Surface *SDL_CreateSurfaceUninitialized(صحيح عرض, صحيح ارتفاع, SDL_PixelFormat format)
{
    أرجع SDL_Create_Surface_داخلی(عرض, ارتفاع, format, false);
}

SDL_Surface *SDL_CreateSurface(صحيح عرض, صحيح ارتفاع, SDL_PixelFormat format)
{
    أرجع SDL_CreateSurfaceZeroed(عرض, ارتفاع, format);
}


/*
 * Create an RGB surface from an existing memory buffer using the given
 * enum SDL_PIXELFORMAT_* format
 */
SDL_Surface *SDL_CreateSurfaceFrom(صحيح عرض, صحيح ارتفاع, SDL_PixelFormat format, فراغ *pixels, صحيح pitch)
{
    CHECK_PARAM(عرض < 0) {
        SDL_InvalidParamError("width");
        أرجع عدم;
    }

    CHECK_PARAM(ارتفاع < 0) {
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
        size_t کمینه_Pitch;

        إذا (!SDL_Calculate_Surface_اندازه(format, عرض, ارتفاع, عدم, &کمینه_Pitch, true /* minimal pitch */)) {
            // Overflow...
            أرجع عدم;
        }

        CHECK_PARAM(pitch < 0 || (size_t)pitch < کمینه_Pitch) {
            SDL_InvalidParamError("pitch");
            أرجع عدم;
        }
    }

    // Allocate and initialize the surface
    SDL_Surface *surface = (SDL_Surface *)SDL_malloc(حجم(*surface));
    إذا (!surface ||
        !SDL_InitializeSurface(surface, عرض, ارتفاع, format, SDL_COLORSPACE_UNKNOWN, 0, pixels, pitch, false)) {
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

bool SDL_مجموعه_Surface_Colorspace(SDL_Surface *surface, SDL_Colorspace colorspace)
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

عائم SDL_Get_Default_SDRWhite_نقطه(SDL_Colorspace colorspace)
{
    أرجع SDL_Get_Surface_SDRWhite_نقطه(عدم, colorspace);
}

عائم SDL_Get_Surface_SDRWhite_نقطه(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    SDL_TransferCharacteristics transfer = SDL_COLORSPACETRANSFER(colorspace);

    إذا (transfer == SDL_TRANSFER_CHARACTERISTICS_خطی ||
        transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
        SDL_PropertiesID props;
        عائم default_مقدار = 1.0f;

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
            ثابت عائم DEFAULT_PQ_SDR_WHITE_نقطه = 203.0f;
            default_مقدار = DEFAULT_PQ_SDR_WHITE_نقطه;
        }
        أرجع SDL_GetFloatProperty(props, SDL_PROP_SURFACE_SDR_WHITE_نقطه_FLOAT, default_مقدار);
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
        عائم default_مقدار = 0.0f;

        إذا (SDL_SurfaceValid(surface)) {
            props = surface->props;
        } وإلا {
            props = 0;
        }
        أرجع SDL_GetFloatProperty(props, SDL_PROP_SURFACE_HDR_HEADROOM_FLOAT, default_مقدار);
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

    CHECK_PARAM(!SDL_ISPIXELFORMAT_نمایهای(surface->format)) {
        SDL_مجموعه_Error("The surface is not indexed format");
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

    إذا (!SDL_مجموعه_Surface_Palette(surface, palette)) {
        SDL_DestroyPalette(palette);
        أرجع عدم;
    }

    // The surface has retained the palette, we can remove the reference here
    SDL_assert(palette->refcount == 2);
    SDL_DestroyPalette(palette);
    أرجع palette;
}

bool SDL_مجموعه_Surface_Palette(SDL_Surface *surface, SDL_Palette *palette)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        أرجع SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(palette && !SDL_ISPIXELFORMAT_نمایهای(surface->format)) {
        أرجع SDL_مجموعه_Error("Surface doesn't use a palette");
    }

    CHECK_PARAM(palette && palette->ncolors > (1 << SDL_BITSPERPIXEL(surface->format))) {
        أرجع SDL_مجموعه_Error("Palette doesn't match surface format");
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

bool SDL_جمع_کن_Surface_Alternate_Image(SDL_Surface *surface, SDL_Surface *image)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        أرجع SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(!SDL_SurfaceValid(image)) {
        أرجع SDL_InvalidParamError("image");
    }

    SDL_Surface **images = (SDL_Surface **)SDL_realloc(surface->images, (surface->رقم_images + 1) * حجم(*images));
    إذا (!images) {
        أرجع false;
    }
    images[surface->رقم_images] = image;
    surface->images = images;
    ++surface->رقم_images;
    ++image->refcount;
    أرجع true;
}

bool SDL_SurfaceHasAlternateImages(SDL_Surface *surface)
{
    إذا (!SDL_SurfaceValid(surface)) {
        أرجع false;
    }

    أرجع (surface->رقم_images > 0);
}

SDL_Surface **SDL_GetSurfaceImages(SDL_Surface *surface, صحيح *شمار)
{
    إذا (شمار) {
        *شمار = 0;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        أرجع عدم;
    }

    صحيح رقم_images = 1 + surface->رقم_images;
    SDL_Surface **images = (SDL_Surface **)SDL_malloc((رقم_images + 1) * حجم(*images));
    إذا (!images) {
        أرجع عدم;
    }
    images[0] = surface;
    إذا (surface->رقم_images > 0) {
        SDL_memcpy(&images[1], surface->images, (surface->رقم_images * حجم(images[1])));
    }
    images[رقم_images] = عدم;

    إذا (شمار) {
        *شمار = رقم_images;
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
    صحيح desired_w = (صحيح)SDL_دور(surface->w * display_scale);
    صحيح desired_h = (صحيح)SDL_دور(surface->h * display_scale);
    صحيح desired_اندازه = desired_w * desired_h;
    صحيح closest_فاصله = -1;
    صحيح closest_اندازه = -1;
    لكل (صحيح i = 0; images[i]; ++i) {
        SDL_Surface *candidate = images[i];
        صحيح اندازه = candidate->w * candidate->h;
        صحيح delta_w = (candidate->w - desired_w);
        صحيح delta_h = (candidate->h - desired_h);
        صحيح فاصله = (delta_w * delta_w) + (delta_h * delta_h);
        إذا (closest_فاصله < 0 || فاصله < closest_فاصله ||
            (اندازه > desired_اندازه && closest_اندازه < desired_اندازه)) {
            closest = candidate;
            closest_فاصله = فاصله;
            closest_اندازه = اندازه;
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
        صحيح بعدی_scaled_w = SDL_max(desired_w, (scaled->w + 1) / 2);
        صحيح بعدی_scaled_h = SDL_max(desired_h, (scaled->h + 1) / 2);
        SDL_Surface *بعدی_scaled = SDL_ScaleSurface(scaled, بعدی_scaled_w, بعدی_scaled_h, SDL_SCALEMODE_خطی);
        إذا (scaled != closest) {
            SDL_DestroySurface(scaled);
        }
        scaled = بعدی_scaled;
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

    إذا (surface->رقم_images > 0) {
        لكل (صحيح i = 0; i < surface->رقم_images; ++i) {
            SDL_DestroySurface(surface->images[i]);
        }
        SDL_free(surface->images);
        surface->images = عدم;
        surface->رقم_images = 0;
    }
}

bool SDL_مجموعه_Surface_RLE(SDL_Surface *surface, bool enabled)
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

bool SDL_مجموعه_Surface_Color_کلید(SDL_Surface *surface, bool enabled, Uint32 کلید)
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
        أرجع SDL_مجموعه_Error("Surface doesn't have a colorkey");
    }

    إذا (کلید) {
        *کلید = surface->map.info.colorkey;
    }
    أرجع true;
}

/* This is a fairly slow function to switch from colorkey to alpha
   NB: it doesn't handle bpp 1 or 3, because they have no alpha channel */
ساكن فراغ SDL_Convert_Colorkey_مقصد_Alpha(SDL_Surface *surface, bool ignore_alpha)
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

    SDL_قفل_Surface(surface);

    إذا (bpp == 2) {
        Uint16 *ردیف, *spot;
        Uint16 ckey = (Uint16)surface->map.info.colorkey;
        Uint16 ماسک = (Uint16)(~surface->fmt->Amask);

        // Ignore, or not, alpha in colorkey comparison
        إذا (ignore_alpha) {
            ckey &= ماسک;
            ردیف = (Uint16 *)surface->pixels;
            لكل (y = surface->h; y--;) {
                spot = ردیف;
                لكل (x = surface->w; x--;) {
                    إذا ((*spot & ماسک) == ckey) {
                        *spot &= ماسک;
                    }
                    ++spot;
                }
                ردیف += surface->pitch / 2;
            }
        } وإلا {
            ردیف = (Uint16 *)surface->pixels;
            لكل (y = surface->h; y--;) {
                spot = ردیف;
                لكل (x = surface->w; x--;) {
                    إذا (*spot == ckey) {
                        *spot &= ماسک;
                    }
                    ++spot;
                }
                ردیف += surface->pitch / 2;
            }
        }
    } وإلا إذا (bpp == 4) {
        Uint32 *ردیف, *spot;
        Uint32 ckey = surface->map.info.colorkey;
        Uint32 ماسک = ~surface->fmt->Amask;

        // Ignore, or not, alpha in colorkey comparison
        إذا (ignore_alpha) {
            ckey &= ماسک;
            ردیف = (Uint32 *)surface->pixels;
            لكل (y = surface->h; y--;) {
                spot = ردیف;
                لكل (x = surface->w; x--;) {
                    إذا ((*spot & ماسک) == ckey) {
                        *spot &= ماسک;
                    }
                    ++spot;
                }
                ردیف += surface->pitch / 4;
            }
        } وإلا {
            ردیف = (Uint32 *)surface->pixels;
            لكل (y = surface->h; y--;) {
                spot = ردیف;
                لكل (x = surface->w; x--;) {
                    إذا (*spot == ckey) {
                        *spot &= ماسک;
                    }
                    ++spot;
                }
                ردیف += surface->pitch / 4;
            }
        }
    }

    SDL_UnlockSurface(surface);

    SDL_مجموعه_Surface_Color_کلید(surface, false, 0);
    SDL_مجموعه_Surface_Blend_نما(surface, SDL_BLENDMODE_BLEND);
}

bool SDL_مجموعه_Surface_Color_Mod(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b)
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

bool SDL_مجموعه_Surface_Alpha_Mod(SDL_Surface *surface, Uint8 alpha)
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

bool SDL_مجموعه_Surface_Blend_نما(SDL_Surface *surface, SDL_Blend_نما blend_نما)
{
    صحيح flags;
    bool نتیجه = true;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        أرجع SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(blend_نما == SDL_BLENDMODE_INVALID) {
        أرجع SDL_InvalidParamError("blendMode");
    }

    flags = surface->map.info.flags;
    surface->map.info.flags &= ~SDL_COPY_BLEND_ماسک;
    بدل (blend_نما) {
    حالة SDL_BLENDMODE_NONE:
        اكسر;
    حالة SDL_BLENDMODE_BLEND:
        surface->map.info.flags |= SDL_COPY_BLEND;
        اكسر;
    حالة SDL_BLENDMODE_BLEND_PREMULTIPLIED:
        surface->map.info.flags |= SDL_COPY_BLEND_PREMULTIPLIED;
        اكسر;
    حالة SDL_BLENDMODE_جمع_کن:
        surface->map.info.flags |= SDL_COPY_جمع_کن;
        اكسر;
    حالة SDL_BLENDMODE_جمع_کن_PREMULTIPLIED:
        surface->map.info.flags |= SDL_COPY_جمع_کن_PREMULTIPLIED;
        اكسر;
    حالة SDL_BLENDMODE_MOD:
        surface->map.info.flags |= SDL_COPY_MOD;
        اكسر;
    حالة SDL_BLENDMODE_MUL:
        surface->map.info.flags |= SDL_COPY_MUL;
        اكسر;
    افتراضي:
        نتیجه = SDL_Unsupported();
        اكسر;
    }

    إذا (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }

    أرجع نتیجه;
}

bool SDL_Get_Surface_Blend_نما(SDL_Surface *surface, SDL_Blend_نما *blend_نما)
{
    إذا (blend_نما) {
        *blend_نما = SDL_BLENDMODE_INVALID;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        أرجع SDL_InvalidParamError("surface");
    }

    إذا (!blend_نما) {
        أرجع true;
    }

    بدل (surface->map.info.flags & SDL_COPY_BLEND_ماسک) {
    حالة SDL_COPY_BLEND:
        *blend_نما = SDL_BLENDMODE_BLEND;
        اكسر;
    حالة SDL_COPY_BLEND_PREMULTIPLIED:
        *blend_نما = SDL_BLENDMODE_BLEND_PREMULTIPLIED;
        اكسر;
    حالة SDL_COPY_جمع_کن:
        *blend_نما = SDL_BLENDMODE_جمع_کن;
        اكسر;
    حالة SDL_COPY_جمع_کن_PREMULTIPLIED:
        *blend_نما = SDL_BLENDMODE_جمع_کن_PREMULTIPLIED;
        اكسر;
    حالة SDL_COPY_MOD:
        *blend_نما = SDL_BLENDMODE_MOD;
        اكسر;
    حالة SDL_COPY_MUL:
        *blend_نما = SDL_BLENDMODE_MUL;
        اكسر;
    افتراضي:
        *blend_نما = SDL_BLENDMODE_NONE;
        اكسر;
    }
    أرجع true;
}

bool SDL_مجموعه_Surface_Clip_Rect(SDL_Surface *surface, ثابت SDL_Rect *rect)
{
    SDL_Rect پر_rect;

    // Don't do anything if there's no surface to act on
    إذا (!SDL_SurfaceValid(surface)) {
        أرجع false;
    }

    // Set up the full surface rectangle
    پر_rect.x = 0;
    پر_rect.y = 0;
    پر_rect.w = surface->w;
    پر_rect.h = surface->h;

    // Set the clipping rectangle
    إذا (!rect) {
        surface->clip_rect = پر_rect;
        أرجع true;
    }
    أرجع SDL_GetRectIntersection(rect, &پر_rect, &surface->clip_rect);
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
        أرجع SDL_مجموعه_Error("Surfaces must not be locked during blit");
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
    إذا (src->map.info.flags & SDL_COPY_نزدیکترین) {
        src->map.info.flags &= ~SDL_COPY_نزدیکترین;
        SDL_InvalidateMap(&src->map);
    }

    أرجع SDL_BlitSurfaceUnchecked(src, &r_src, dst, &r_dst);
}

ساكن bool SDL_BlitSurfaceClippedScaled(SDL_Surface *src, ثابت SDL_Rect *srcrect, SDL_Surface *dst, ثابت SDL_Rect *dstrect, SDL_Scale_نما scale_نما)
{
    // We need to scale first, then blit into dst because we're clipping in the destination surface pixel coordinates
    bool نتیجه;
    صحيح saved_w = src->w;
    صحيح saved_h = src->h;
    فراغ *saved_pixels = src->pixels;
    src->w = srcrect->w;
    src->h = srcrect->h;
    src->pixels = (Uint8 *)src->pixels + srcrect->y * src->pitch + srcrect->x * SDL_BYTESPERPIXEL(src->format);
    SDL_Surface *scaled = SDL_ScaleSurface(src, dstrect->w, dstrect->h, scale_نما);
    إذا (scaled) {
        نتیجه = SDL_BlitSurface(scaled, عدم, dst, dstrect);
        SDL_DestroySurface(scaled);
    } وإلا {
        نتیجه = false;
    }
    src->w = saved_w;
    src->h = saved_h;
    src->pixels = saved_pixels;
    أرجع نتیجه;
}

bool SDL_BlitSurfaceScaled(SDL_Surface *src, ثابت SDL_Rect *srcrect, SDL_Surface *dst, ثابت SDL_Rect *dstrect, SDL_Scale_نما scale_نما)
{
    SDL_Rect r_src, r_dst;
    bool نتیجه;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src) || (!src->pixels && !SDL_MUSTLOCK(src))) {
        أرجع SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst) || (!dst->pixels && !SDL_MUSTLOCK(dst))) {
        أرجع SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        أرجع SDL_مجموعه_Error("Surfaces must not be locked during blit");
    }

    بدل (scale_نما) {
    حالة SDL_SCALEMODE_نزدیکترین:
        اكسر;
    حالة SDL_SCALEMODE_خطی:
        اكسر;
    حالة SDL_SCALEMODE_PIXELART:
        scale_نما = SDL_SCALEMODE_نزدیکترین;
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
        أرجع SDL_BlitSurfaceClippedScaled(src, &r_src, dst, &r_dst, scale_نما);
    }

    إذا (SDL_MUSTLOCK(src)) {
        إذا (!SDL_قفل_Surface(src)) {
            أرجع false;
        }
    }
    إذا (SDL_MUSTLOCK(dst)) {
        إذا (!SDL_قفل_Surface(dst)) {
            إذا (SDL_MUSTLOCK(src)) {
                SDL_UnlockSurface(src);
            }
            أرجع false;
        }
    }

    نتیجه = SDL_BlitSurfaceUncheckedScaled(src, &r_src, dst, &r_dst, scale_نما);

    إذا (SDL_MUSTLOCK(src)) {
        SDL_UnlockSurface(src);
    }
    إذا (SDL_MUSTLOCK(dst)) {
        SDL_UnlockSurface(dst);
    }
    أرجع نتیجه;
}

/**
 *  This is a semi-private blit function and it performs low-level surface
 *  scaled blitting only.
 */
bool SDL_BlitSurfaceUncheckedScaled(SDL_Surface *src, ثابت SDL_Rect *srcrect, SDL_Surface *dst, ثابت SDL_Rect *dstrect, SDL_Scale_نما scale_نما)
{
    ساكن ثابت Uint32 complex_copy_flags = (SDL_COPY_MODULATE_ماسک | SDL_COPY_BLEND_ماسک | SDL_COPY_COLORKEY);

    إذا (srcrect->w > SDL_MAX_UINT16 || srcrect->h > SDL_MAX_UINT16 ||
        dstrect->w > SDL_MAX_UINT16 || dstrect->h > SDL_MAX_UINT16) {
        أرجع SDL_مجموعه_Error("Size too large for scaling");
    }

    إذا (!(src->map.info.flags & SDL_COPY_نزدیکترین)) {
        src->map.info.flags |= SDL_COPY_نزدیکترین;
        SDL_InvalidateMap(&src->map);
    }

    إذا (scale_نما == SDL_SCALEMODE_نزدیکترین || scale_نما == SDL_SCALEMODE_PIXELART) {
        إذا (!(src->map.info.flags & complex_copy_flags) &&
            src->format == dst->format &&
            (!SDL_ISPIXELFORMAT_نمایهای(src->format) ||
             (SDL_BITSPERPIXEL(src->format) == 8 && SDL_IsSamePalette(src->palette, dst->palette))) &&
            SDL_BYTESPERPIXEL(src->format) <= 4) {
            أرجع SDL_StretchSurface(src, srcrect, dst, dstrect, SDL_SCALEMODE_نزدیکترین);
        } وإلا إذا (SDL_BITSPERPIXEL(src->format) < 8) {
            // Scaling bitmap not yet supported, convert to RGBA for blit
            bool نتیجه = false;
            SDL_Surface *tmp = SDL_ConvertSurface(src, SDL_PIXELFORMAT_ARGB8888);
            إذا (tmp) {
                نتیجه = SDL_BlitSurfaceUncheckedScaled(tmp, srcrect, dst, dstrect, SDL_SCALEMODE_نزدیکترین);
                SDL_DestroySurface(tmp);
            }
            أرجع نتیجه;
        } وإلا {
            أرجع SDL_BlitSurfaceUnchecked(src, srcrect, dst, dstrect);
        }
    } وإلا {
        إذا (!(src->map.info.flags & complex_copy_flags) &&
            src->format == dst->format &&
            !SDL_ISPIXELFORMAT_نمایهای(src->format) &&
            SDL_BYTESPERPIXEL(src->format) == 4 &&
            src->format != SDL_PIXELFORMAT_ARGB2101010) {
            // fast path
            أرجع SDL_StretchSurface(src, srcrect, dst, dstrect, SDL_SCALEMODE_خطی);
        } وإلا إذا (SDL_BITSPERPIXEL(src->format) < 8) {
            // Scaling bitmap not yet supported, convert to RGBA for blit
            bool نتیجه = false;
            SDL_Surface *tmp = SDL_ConvertSurface(src, SDL_PIXELFORMAT_ARGB8888);
            إذا (tmp) {
                نتیجه = SDL_BlitSurfaceUncheckedScaled(tmp, srcrect, dst, dstrect, scale_نما);
                SDL_DestroySurface(tmp);
            }
            أرجع نتیجه;
        } وإلا {
            // Use intermediate surface(s)
            SDL_Surface *tmp1 = عدم;
            bool نتیجه;
            SDL_Rect srcrect2;
            صحيح is_complex_copy_flags = (src->map.info.flags & complex_copy_flags);

            Uint8 r, g, b;
            Uint8 alpha;
            SDL_Blend_نما blend_نما;

            // Save source infos
            SDL_GetSurfaceColorMod(src, &r, &g, &b);
            SDL_GetSurfaceAlphaMod(src, &alpha);
            SDL_Get_Surface_Blend_نما(src, &blend_نما);
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

                SDL_مجموعه_Surface_Color_Mod(tmp2, r, g, b);
                SDL_مجموعه_Surface_Alpha_Mod(tmp2, alpha);
                SDL_مجموعه_Surface_Blend_نما(tmp2, blend_نما);

                tmprect.x = 0;
                tmprect.y = 0;
                tmprect.w = dstrect->w;
                tmprect.h = dstrect->h;
                نتیجه = SDL_BlitSurfaceUnchecked(tmp2, &tmprect, dst, dstrect);
                SDL_DestroySurface(tmp2);
            } وإلا {
                نتیجه = SDL_StretchSurface(src, &srcrect2, dst, dstrect, SDL_SCALEMODE_خطی);
            }

            SDL_DestroySurface(tmp1);
            أرجع نتیجه;
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
        أرجع SDL_مجموعه_Error("Surfaces must not be locked during blit");
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
    إذا (src->map.info.flags & SDL_COPY_نزدیکترین) {
        src->map.info.flags &= ~SDL_COPY_نزدیکترین;
        SDL_InvalidateMap(&src->map);
    }

    صحيح ردیفها = r_dst.h / r_src.h;
    صحيح تعداد_ستون = r_dst.w / r_src.w;
    صحيح مانده_w = r_dst.w % r_src.w;
    صحيح مانده_h = r_dst.h % r_src.h;
    SDL_Rect curr_src, curr_dst;

    SDL_copyp(&curr_src, &r_src);
    curr_dst.y = r_dst.y;
    curr_dst.w = r_src.w;
    curr_dst.h = r_src.h;
    لكل (صحيح y = 0; y < ردیفها; ++y) {
        curr_dst.x = r_dst.x;
        لكل (صحيح x = 0; x < تعداد_ستون; ++x) {
            إذا (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                أرجع false;
            }
            curr_dst.x += curr_dst.w;
        }
        إذا (مانده_w) {
            curr_src.w = مانده_w;
            curr_dst.w = مانده_w;
            إذا (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                أرجع false;
            }
            curr_src.w = r_src.w;
            curr_dst.w = r_src.w;
        }
        curr_dst.y += curr_dst.h;
    }
    إذا (مانده_h) {
        curr_src.h = مانده_h;
        curr_dst.h = مانده_h;
        curr_dst.x = r_dst.x;
        لكل (صحيح x = 0; x < تعداد_ستون; ++x) {
            إذا (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                أرجع false;
            }
            curr_dst.x += curr_dst.w;
        }
        إذا (مانده_w) {
            curr_src.w = مانده_w;
            curr_dst.w = مانده_w;
            إذا (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                أرجع false;
            }
        }
    }
    أرجع true;
}

bool SDL_BlitSurfaceTiledWithScale(SDL_Surface *src, ثابت SDL_Rect *srcrect, عائم scale, SDL_Scale_نما scale_نما, SDL_Surface *dst, ثابت SDL_Rect *dstrect)
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
        أرجع SDL_مجموعه_Error("Surfaces must not be locked during blit");
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
    إذا (src->map.info.flags & SDL_COPY_نزدیکترین) {
        src->map.info.flags &= ~SDL_COPY_نزدیکترین;
        SDL_InvalidateMap(&src->map);
    }

    صحيح tile_عرض = (صحيح)SDL_roundf(r_src.w * scale);
    صحيح tile_ارتفاع = (صحيح)SDL_roundf(r_src.h * scale);
    إذا (tile_عرض <= 0 || tile_ارتفاع <= 0) {
        // Nothing to do
        أرجع true;
    }
    صحيح ردیفها = r_dst.h / tile_ارتفاع;
    صحيح تعداد_ستون = r_dst.w / tile_عرض;
    صحيح مانده_dst_w = (r_dst.w - تعداد_ستون * tile_عرض);
    صحيح مانده_dst_h = (r_dst.h - ردیفها * tile_ارتفاع);
    صحيح مانده_src_w = (صحيح)(مانده_dst_w / scale);
    صحيح مانده_src_h = (صحيح)(مانده_dst_h / scale);
    SDL_Rect curr_src, curr_dst;

    SDL_copyp(&curr_src, &r_src);
    curr_dst.y = r_dst.y;
    curr_dst.w = tile_عرض;
    curr_dst.h = tile_ارتفاع;
    لكل (صحيح y = 0; y < ردیفها; ++y) {
        curr_dst.x = r_dst.x;
        لكل (صحيح x = 0; x < تعداد_ستون; ++x) {
            إذا (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scale_نما)) {
                أرجع false;
            }
            curr_dst.x += curr_dst.w;
        }
        إذا (مانده_dst_w > 0) {
            curr_src.w = مانده_src_w;
            curr_dst.w = مانده_dst_w;
            إذا (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scale_نما)) {
                أرجع false;
            }
            curr_src.w = r_src.w;
            curr_dst.w = tile_عرض;
        }
        curr_dst.y += curr_dst.h;
    }
    إذا (مانده_dst_h > 0) {
        curr_src.h = مانده_src_h;
        curr_dst.h = مانده_dst_h;
        curr_dst.x = r_dst.x;
        لكل (صحيح x = 0; x < تعداد_ستون; ++x) {
            إذا (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scale_نما)) {
                أرجع false;
            }
            curr_dst.x += curr_dst.w;
        }
        إذا (مانده_dst_w > 0) {
            curr_src.w = مانده_src_w;
            curr_dst.w = مانده_dst_w;
            إذا (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scale_نما)) {
                أرجع false;
            }
        }
    }
    أرجع true;
}

bool SDL_BlitSurface9Grid(SDL_Surface *src, ثابت SDL_Rect *srcrect, صحيح چپ_عرض, صحيح راست_عرض, صحيح بالاترین_ارتفاع, صحيح bottom_ارتفاع, عائم scale, SDL_Scale_نما scale_نما, SDL_Surface *dst, ثابت SDL_Rect *dstrect)
{
    SDL_Rect پر_src, پر_dst;
    SDL_Rect curr_src, curr_dst;
    صحيح dst_چپ_عرض;
    صحيح dst_راست_عرض;
    صحيح dst_بالاترین_ارتفاع;
    صحيح dst_bottom_ارتفاع;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        أرجع SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        أرجع SDL_InvalidParamError("dst");
    }

    إذا (!srcrect) {
        پر_src.x = 0;
        پر_src.y = 0;
        پر_src.w = src->w;
        پر_src.h = src->h;
        srcrect = &پر_src;
    }

    إذا (!dstrect) {
        پر_dst.x = 0;
        پر_dst.y = 0;
        پر_dst.w = dst->w;
        پر_dst.h = dst->h;
        dstrect = &پر_dst;
    }

    إذا (scale <= 0.0f || scale == 1.0f) {
        dst_چپ_عرض = چپ_عرض;
        dst_راست_عرض = راست_عرض;
        dst_بالاترین_ارتفاع = بالاترین_ارتفاع;
        dst_bottom_ارتفاع = bottom_ارتفاع;
    } وإلا {
        dst_چپ_عرض = (صحيح)SDL_roundf(چپ_عرض * scale);
        dst_راست_عرض = (صحيح)SDL_roundf(راست_عرض * scale);
        dst_بالاترین_ارتفاع = (صحيح)SDL_roundf(بالاترین_ارتفاع * scale);
        dst_bottom_ارتفاع = (صحيح)SDL_roundf(bottom_ارتفاع * scale);
    }

    // Upper-left corner
    curr_src.x = srcrect->x;
    curr_src.y = srcrect->y;
    curr_src.w = چپ_عرض;
    curr_src.h = بالاترین_ارتفاع;
    curr_dst.x = dstrect->x;
    curr_dst.y = dstrect->y;
    curr_dst.w = dst_چپ_عرض;
    curr_dst.h = dst_بالاترین_ارتفاع;
    إذا (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_نما)) {
        أرجع false;
    }

    // Upper-right corner
    curr_src.x = srcrect->x + srcrect->w - راست_عرض;
    curr_src.w = راست_عرض;
    curr_dst.x = dstrect->x + dstrect->w - dst_راست_عرض;
    curr_dst.w = dst_راست_عرض;
    إذا (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_نما)) {
        أرجع false;
    }

    // Lower-right corner
    curr_src.y = srcrect->y + srcrect->h - bottom_ارتفاع;
    curr_dst.y = dstrect->y + dstrect->h - dst_bottom_ارتفاع;
    curr_dst.h = dst_bottom_ارتفاع;
    إذا (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_نما)) {
        أرجع false;
    }

    // Lower-left corner
    curr_src.x = srcrect->x;
    curr_src.w = چپ_عرض;
    curr_dst.x = dstrect->x;
    curr_dst.w = dst_چپ_عرض;
    إذا (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_نما)) {
        أرجع false;
    }

    //چپ
    curr_src.y = srcrect->y + بالاترین_ارتفاع;
    curr_src.h = srcrect->h - بالاترین_ارتفاع - bottom_ارتفاع;
    curr_dst.y = dstrect->y + dst_بالاترین_ارتفاع;
    curr_dst.h = dstrect->h - dst_بالاترین_ارتفاع - dst_bottom_ارتفاع;
    إذا (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_نما)) {
        أرجع false;
    }

    //راست
    curr_src.x = srcrect->x + srcrect->w - راست_عرض;
    curr_src.w = راست_عرض;
    curr_dst.x = dstrect->x + dstrect->w - dst_راست_عرض;
    curr_dst.w = dst_راست_عرض;
    إذا (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_نما)) {
        أرجع false;
    }

    //بالاترین
    curr_src.x = srcrect->x + چپ_عرض;
    curr_src.y = srcrect->y;
    curr_src.w = srcrect->w - چپ_عرض - راست_عرض;
    curr_src.h = بالاترین_ارتفاع;
    curr_dst.x = dstrect->x + dst_چپ_عرض;
    curr_dst.y = dstrect->y;
    curr_dst.w = dstrect->w - dst_چپ_عرض - dst_راست_عرض;
    curr_dst.h = dst_بالاترین_ارتفاع;
    إذا (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_نما)) {
        أرجع false;
    }

    // Bottom
    curr_src.y = srcrect->y + srcrect->h - bottom_ارتفاع;
    curr_dst.y = dstrect->y + dstrect->h - dst_bottom_ارتفاع;
    curr_dst.h = dst_bottom_ارتفاع;
    إذا (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_نما)) {
        أرجع false;
    }

    // Center
    curr_src.x = srcrect->x + چپ_عرض;
    curr_src.y = srcrect->y + بالاترین_ارتفاع;
    curr_src.w = srcrect->w - چپ_عرض - راست_عرض;
    curr_src.h = srcrect->h - بالاترین_ارتفاع - bottom_ارتفاع;
    curr_dst.x = dstrect->x + dst_چپ_عرض;
    curr_dst.y = dstrect->y + dst_بالاترین_ارتفاع;
    curr_dst.w = dstrect->w - dst_چپ_عرض - dst_راست_عرض;
    curr_dst.h = dstrect->h - dst_بالاترین_ارتفاع - dst_bottom_ارتفاع;
    إذا (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_نما)) {
        أرجع false;
    }

    أرجع true;
}

/*
 * Lock a surface to directly access the pixels
 */
bool SDL_قفل_Surface(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        أرجع SDL_InvalidParamError("surface");
    }

    إذا (!surface->locked) {
#اگر_تعریف_شده SDL_HAVE_RLE
        // Perform the lock
        إذا (surface->داخلی_flags & SDL_داخلی_SURFACE_RLEACCEL) {
            SDL_UnRLESurface(surface);
        }
#پایان_اگر
    }

    // Increment the surface lock count, for recursive locks
    ++surface->locked;
    surface->flags |= SDL_SURFACE_LOCKED;
    SDL_Update_Surface_قفل_Flag(surface);

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
    SDL_Update_Surface_قفل_Flag(surface);
}

ساكن bool SDL_FlipSurfaceHorizontal(SDL_Surface *surface)
{
    bool isstack;
    Uint8 *ردیف, *a, *b, *tmp;
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
    ردیف = (Uint8 *)surface->pixels;
    tmp = SDL_small_alloc(Uint8, surface->pitch, &isstack);
    إذا (!tmp) {
        أرجع false;
    }
    لكل (i = surface->h; i--; ) {
        a = ردیف;
        b = a + (surface->w - 1) * bpp;
        لكل (j = surface->w / 2; j--; ) {
            SDL_memcpy(tmp, a, bpp);
            SDL_memcpy(a, b, bpp);
            SDL_memcpy(b, tmp, bpp);
            a += bpp;
            b -= bpp;
        }
        ردیف += surface->pitch;
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

bool SDL_FlipSurface(SDL_Surface *surface, SDL_Flip_نما flip)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        أرجع SDL_InvalidParamError("surface");
    }
    إذا (!surface->pixels) {
        أرجع true;
    }

    bool نتیجه = true;
    بدل (flip) {
    حالة SDL_FLIP_HORIZONTAL:
        نتیجه = SDL_FlipSurfaceHorizontal(surface);
        اكسر;
    حالة SDL_FLIP_VERTICAL:
        نتیجه = SDL_FlipSurfaceVertical(surface);
        اكسر;
    حالة SDL_FLIP_HORIZONTAL_AND_VERTICAL:
        نتیجه &= SDL_FlipSurfaceHorizontal(surface);
        نتیجه &= SDL_FlipSurfaceVertical(surface);
        اكسر;
    افتراضي:
        نتیجه = SDL_InvalidParamError("flip");
        اكسر;
    }
    أرجع نتیجه;
}

ساكن SDL_Surface *SDL_ConvertSurfaceRectAndColorspace(SDL_Surface *surface, ثابت SDL_Rect *rect, SDL_PixelFormat format, SDL_Palette *palette, SDL_Colorspace colorspace, SDL_PropertiesID props)
{
    SDL_Palette *موقت_palette = عدم;
    SDL_Surface *convert = عدم;
    SDL_Colorspace src_colorspace;
    SDL_PropertiesID src_properties;
    Uint32 copy_flags;
    SDL_Color copy_color;
    SDL_Rect bounds;
    bool نتیجه;
    bool palette_ck_transform = false;
    Uint8 palette_ck_مقدار = 0;
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
            SDL_مجموعه_Error("Empty destination palette");
            اذهب error;
        }
    } وإلا إذا (SDL_ISPIXELFORMAT_نمایهای(format)) {
        // Create a dither palette for conversion
        موقت_palette = SDL_CreatePalette(1 << SDL_BITSPERPIXEL(format));
        إذا (موقت_palette) {
            SDL_DitherPalette(موقت_palette);
            palette = موقت_palette;
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
    إذا (SDL_ISPIXELFORMAT_نمایهای(format)) {
        SDL_مجموعه_Surface_Palette(convert, palette);
    }

    إذا (colorspace == SDL_COLORSPACE_UNKNOWN) {
        colorspace = src_colorspace;
    }
    SDL_مجموعه_Surface_Colorspace(convert, colorspace);

    إذا (SDL_ISPIXELFORMAT_FOURCC(format) || SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        إذا (surface->format == SDL_PIXELFORMAT_MJPG && format == SDL_PIXELFORMAT_MJPG) {
            // Just do a straight pixel copy of the JPEG image
            size_t اندازه = (size_t)surface->pitch;
            convert->pixels = SDL_malloc(اندازه);
            إذا (!convert->pixels) {
                اذهب error;
            }
            convert->flags &= ~SDL_SURFACE_PREALLOCATED;
            convert->pitch = surface->pitch;
            SDL_memcpy(convert->pixels, surface->pixels, اندازه);

        } وإلا إذا (!SDL_ConvertPixelsAndColorspace(surface->w, surface->h, surface->format, src_colorspace, src_properties, surface->pixels, surface->pitch, convert->format, colorspace, props, convert->pixels, convert->pitch)) {
            اذهب error;
        }

        // Save the original copy flags
        copy_flags = surface->map.info.flags;

        اذهب انتها;
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
        bool مجموعه_opaque = false;

        bool is_opaque, has_alpha_channel;
        SDL_DetectPalette(surface->palette, &is_opaque, &has_alpha_channel);

        إذا (is_opaque) {
            إذا (!has_alpha_channel) {
                مجموعه_opaque = true;
            }
        }

        // Set opaque and backup palette alpha values
        إذا (مجموعه_opaque) {
            صحيح i;
            palette_saved_alpha_ncolors = surface->palette->ncolors;
            إذا (palette_saved_alpha_ncolors > 0) {
                palette_saved_alpha = SDL_پشته_alloc(Uint8, palette_saved_alpha_ncolors);
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
            palette_ck_مقدار = surface->palette->colors[surface->map.info.colorkey].a;
            surface->palette->colors[surface->map.info.colorkey].a = SDL_ALPHA_TRANSPARENT;
        }
    }

    إذا (surface->pixels || SDL_MUSTLOCK(surface)) {
        نتیجه = SDL_BlitSurfaceUnchecked(surface, rect, convert, &bounds);
    } وإلا {
        نتیجه = true;
    }

    // Restore colorkey alpha value
    إذا (palette_ck_transform) {
        surface->palette->colors[surface->map.info.colorkey].a = palette_ck_مقدار;
    }

    // Restore palette alpha values
    إذا (palette_saved_alpha) {
        صحيح i;
        لكل (i = 0; i < palette_saved_alpha_ncolors; i++) {
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
    إذا (!نتیجه) {
        اذهب error;
    }

    إذا (copy_flags & SDL_COPY_COLORKEY) {
        bool مجموعه_colorkey_by_color = false;
        bool convert_colorkey = true;

        إذا (surface->palette) {
            إذا (palette &&
                surface->palette->ncolors <= palette->ncolors &&
                (SDL_memcmp(surface->palette->colors, palette->colors,
                            surface->palette->ncolors * حجم(SDL_Color)) == 0)) {
                // The palette is identical, just set the same colorkey
                SDL_مجموعه_Surface_Color_کلید(convert, true, surface->map.info.colorkey);
            } وإلا إذا (!palette) {
                إذا (SDL_ISPIXELFORMAT_ALPHA(format)) {
                    // No need to add the colorkey, transparency is in the alpha channel
                } وإلا {
                    // Only set the colorkey information
                    مجموعه_colorkey_by_color = true;
                    convert_colorkey = false;
                }
            } وإلا {
                مجموعه_colorkey_by_color = true;
            }
        } وإلا {
            مجموعه_colorkey_by_color = true;
        }

        إذا (مجموعه_colorkey_by_color) {
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
                SDL_مجموعه_Surface_Palette(tmp, surface->palette);
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
            SDL_memcpy(&converted_colorkey, tmp2->pixels, tmp2->fmt->بایتها_در_هر_pixel);

            SDL_DestroySurface(tmp);
            SDL_DestroySurface(tmp2);

            // Set the converted colorkey on the new surface
            SDL_مجموعه_Surface_Color_کلید(convert, true, converted_colorkey);

            // This is needed when converting for 3D texture upload
            إذا (convert_colorkey) {
                SDL_Convert_Colorkey_مقصد_Alpha(convert, true);
            }
        }
    }

انتها:
    إذا (موقت_palette) {
        SDL_DestroyPalette(موقت_palette);
    }

    SDL_مجموعه_Surface_Clip_Rect(convert, &surface->clip_rect);

    /* Enable alpha blending by default if the new surface has an
     * alpha channel or alpha modulation */
    إذا (SDL_ISPIXELFORMAT_ALPHA(format) ||
        (copy_flags & SDL_COPY_MODULATE_ALPHA)) {
        SDL_مجموعه_Surface_Blend_نما(convert, SDL_BLENDMODE_BLEND);
    }
    إذا (copy_flags & SDL_COPY_RLE_DESIRED) {
        SDL_مجموعه_Surface_RLE(convert, true);
    }

    // Copy alternate images
    لكل (صحيح i = 0; i < surface->رقم_images; ++i) {
        إذا (!SDL_جمع_کن_Surface_Alternate_Image(convert, surface->images[i])) {
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
    إذا (موقت_palette) {
        SDL_DestroyPalette(موقت_palette);
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
    SDLgfx_rotozoom_Surface_اندازه_Trig(surface->w, surface->h, angle, &center, &rect_dest, &cangle, &sangle);

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
            ثابت عائم rotation = (SDL_Get_عدد_Property(surface->props, SDL_PROP_SURFACE_ROTATION_FLOAT, 0) - angle);
            SDL_مجموعه_Float_Property(SDL_GetSurfaceProperties(rotated), SDL_PROP_SURFACE_ROTATION_FLOAT, rotation);
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

SDL_Surface *SDL_ScaleSurface(SDL_Surface *surface, صحيح عرض, صحيح ارتفاع, SDL_Scale_نما scale_نما)
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

        SDL_Surface *scaled = SDL_ScaleSurface(tmp, عرض, ارتفاع, scale_نما);
        SDL_DestroySurface(tmp);
        إذا (!scaled) {
            أرجع عدم;
        }

        SDL_Surface *نتیجه = SDL_ConvertSurfaceAndColorspace(scaled, surface->format, عدم, surface->colorspace, surface->props);
        SDL_DestroySurface(scaled);
        أرجع نتیجه;
    }

    إذا (SDL_ISPIXELFORMAT_نمایهای(surface->format)) {
        // Linear scaling requires conversion to RGBA and then slow pixel color lookup
        scale_نما = SDL_SCALEMODE_نزدیکترین;
    }

    // Create a new surface with the desired size
    إذا (surface->pixels || SDL_MUSTLOCK(surface)) {
        convert = SDL_CreateSurfaceUninitialized(عرض, ارتفاع, surface->format);
    } وإلا {
        convert = SDL_CreateSurfaceFrom(عرض, ارتفاع, surface->format, عدم, 0);
    }
    إذا (!convert) {
        اذهب error;
    }
    SDL_مجموعه_Surface_Palette(convert, surface->palette);
    SDL_مجموعه_Surface_Colorspace(convert, surface->colorspace);
    SDL_مجموعه_Surface_RLE(convert, SDL_SurfaceHasRLE(surface));

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

        rc = SDL_BlitSurfaceScaled(surface, عدم, convert, عدم, scale_نما);

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

SDL_Surface *SDL_DuplicatePixels(صحيح عرض, صحيح ارتفاع, SDL_PixelFormat format, SDL_Colorspace colorspace, فراغ *pixels, صحيح pitch)
{
    SDL_Surface *surface;
    إذا (pixels) {
        surface = SDL_CreateSurfaceUninitialized(عرض, ارتفاع, format);
    } وإلا {
        surface = SDL_CreateSurfaceFrom(عرض, ارتفاع, format, عدم, 0);
    }
    إذا (!surface) {
        أرجع عدم;
    }
    SDL_مجموعه_Surface_Colorspace(surface, colorspace);

    إذا (surface->pixels) {
        صحيح درازی = عرض * SDL_BYTESPERPIXEL(format);
        Uint8 *src = (Uint8 *)pixels;
        Uint8 *dst = (Uint8 *)surface->pixels;
        صحيح ردیفها = ارتفاع;
        طالما (ردیفها--) {
            SDL_memcpy(dst, src, درازی);
            dst += surface->pitch;
            src += pitch;
        }
    }
    أرجع surface;
}

bool SDL_ConvertPixelsAndColorspace(صحيح عرض, صحيح ارتفاع,
                      SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ثابت فراغ *src, صحيح src_pitch,
                      SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, فراغ *dst, صحيح dst_pitch)
{
    SDL_Surface src_surface;
    SDL_Surface dst_surface;
    SDL_Rect rect;
    فراغ *nonconst_src = (فراغ *)src;
    bool نتیجه;

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
        أرجع SDL_ConvertPixels_STB(عرض, ارتفاع, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    }

#اگر_تعریف_شده SDL_HAVE_YUV
    إذا (SDL_ISPIXELFORMAT_FOURCC(src_format) && SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        أرجع SDL_Convert_Pixels_YUV_مقصد_YUV(عرض, ارتفاع, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } وإلا إذا (SDL_ISPIXELFORMAT_FOURCC(src_format)) {
        أرجع SDL_Convert_Pixels_YUV_مقصد_RGB(عرض, ارتفاع, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } وإلا إذا (SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        أرجع SDL_Convert_Pixels_RGB_مقصد_YUV(عرض, ارتفاع, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    }
#وإلا
    إذا (SDL_ISPIXELFORMAT_FOURCC(src_format) || SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        أرجع SDL_مجموعه_Error("SDL not built with YUV support");
    }
#پایان_اگر

    // Fast path for same format copy
    إذا (src_format == dst_format && src_colorspace == dst_colorspace) {
        إذا (src_pitch == dst_pitch) {
            SDL_memcpy(dst, src, ارتفاع * src_pitch);
        } وإلا {
            صحيح i;
            ثابت صحيح bpp = SDL_BYTESPERPIXEL(src_format);
            عرض *= bpp;
            لكل (i = ارتفاع; i--;) {
                SDL_memcpy(dst, src, عرض);
                src = (ثابت Uint8 *)src + src_pitch;
                dst = (Uint8 *)dst + dst_pitch;
            }
        }
        أرجع true;
    }

    إذا (!SDL_InitializeSurface(&src_surface, عرض, ارتفاع, src_format, src_colorspace, src_properties, nonconst_src, src_pitch, true)) {
        أرجع false;
    }
    SDL_مجموعه_Surface_Blend_نما(&src_surface, SDL_BLENDMODE_NONE);

    إذا (!SDL_InitializeSurface(&dst_surface, عرض, ارتفاع, dst_format, dst_colorspace, dst_properties, dst, dst_pitch, true)) {
        أرجع false;
    }

    // Set up the rect and go!
    rect.x = 0;
    rect.y = 0;
    rect.w = عرض;
    rect.h = ارتفاع;
    نتیجه = SDL_BlitSurfaceUnchecked(&src_surface, &rect, &dst_surface, &rect);

    SDL_DestroySurface(&src_surface);
    SDL_DestroySurface(&dst_surface);

    أرجع نتیجه;
}

bool SDL_ConvertPixels(صحيح عرض, صحيح ارتفاع, SDL_PixelFormat src_format, ثابت فراغ *src, صحيح src_pitch, SDL_PixelFormat dst_format, فراغ *dst, صحيح dst_pitch)
{
    أرجع SDL_ConvertPixelsAndColorspace(عرض, ارتفاع,
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

ساكن فراغ SDL_PremultiplyAlpha_AXYZ8888(صحيح عرض, صحيح ارتفاع, ثابت فراغ *src, صحيح src_pitch, فراغ *dst, صحيح dst_pitch)
{
    صحيح c;
    Uint32 srcpixel;
    Uint32 srcR, srcG, srcB, srcA;
    Uint32 dstpixel;
    Uint32 dstR, dstG, dstB, dstA;

    طالما (ارتفاع--) {
        ثابت Uint32 *src_px = (ثابت Uint32 *)src;
        Uint32 *dst_px = (Uint32 *)dst;
        لكل (c = عرض; c; --c) {
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

ساكن فراغ SDL_PremultiplyAlpha_XYZA8888(صحيح عرض, صحيح ارتفاع, ثابت فراغ *src, صحيح src_pitch, فراغ *dst, صحيح dst_pitch)
{
    صحيح c;
    Uint32 srcpixel;
    Uint32 srcR, srcG, srcB, srcA;
    Uint32 dstpixel;
    Uint32 dstR, dstG, dstB, dstA;

    طالما (ارتفاع--) {
        ثابت Uint32 *src_px = (ثابت Uint32 *)src;
        Uint32 *dst_px = (Uint32 *)dst;
        لكل (c = عرض; c; --c) {
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

ساكن فراغ SDL_PremultiplyAlpha_AXYZ128(صحيح عرض, صحيح ارتفاع, ثابت فراغ *src, صحيح src_pitch, فراغ *dst, صحيح dst_pitch)
{
    صحيح c;
    عائم flR, flG, flB, flA;

    طالما (ارتفاع--) {
        ثابت عائم *src_px = (ثابت عائم *)src;
        عائم *dst_px = (عائم *)dst;
        لكل (c = عرض; c; --c) {
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

ساكن bool SDL_PremultiplyAlphaPixelsAndColorspace(صحيح عرض, صحيح ارتفاع, SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ثابت فراغ *src, صحيح src_pitch, SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, فراغ *dst, صحيح dst_pitch, bool خطی)
{
    SDL_Surface *convert = عدم;
    فراغ *final_dst = dst;
    صحيح final_dst_pitch = dst_pitch;
    SDL_PixelFormat format;
    SDL_Colorspace colorspace;
    bool نتیجه = false;

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
        SDL_ISPIXELFORMAT_10_بیت(src_format) || SDL_BITSPERPIXEL(src_format) > 32 ||
        SDL_ISPIXELFORMAT_10_بیت(dst_format) || SDL_BITSPERPIXEL(dst_format) > 32) {
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
        convert = SDL_CreateSurfaceUninitialized(عرض, ارتفاع, format);
        إذا (!convert) {
            اذهب انجامشده;
        }
        إذا (!SDL_ConvertPixelsAndColorspace(عرض, ارتفاع, src_format, src_colorspace, src_properties, src, src_pitch, format, colorspace, 0, convert->pixels, convert->pitch)) {
            اذهب انجامشده;
        }

        src = convert->pixels;
        src_pitch = convert->pitch;
        dst = convert->pixels;
        dst_pitch = convert->pitch;

    } وإلا إذا (dst_format != format || dst_colorspace != colorspace) {
        convert = SDL_CreateSurfaceUninitialized(عرض, ارتفاع, format);
        إذا (!convert) {
            اذهب انجامشده;
        }
        dst = convert->pixels;
        dst_pitch = convert->pitch;
    }

    بدل (format) {
    حالة SDL_PIXELFORMAT_ARGB8888:
    حالة SDL_PIXELFORMAT_ABGR8888:
        SDL_PremultiplyAlpha_AXYZ8888(عرض, ارتفاع, src, src_pitch, dst, dst_pitch);
        اكسر;
    حالة SDL_PIXELFORMAT_RGBA8888:
    حالة SDL_PIXELFORMAT_BGRA8888:
        SDL_PremultiplyAlpha_XYZA8888(عرض, ارتفاع, src, src_pitch, dst, dst_pitch);
        اكسر;
    حالة SDL_PIXELFORMAT_ARGB128_FLOAT:
    حالة SDL_PIXELFORMAT_ABGR128_FLOAT:
        SDL_PremultiplyAlpha_AXYZ128(عرض, ارتفاع, src, src_pitch, dst, dst_pitch);
        اكسر;
    افتراضي:
        SDL_مجموعه_Error("Unexpected internal pixel format");
        اذهب انجامشده;
    }

    إذا (dst != final_dst) {
        إذا (!SDL_ConvertPixelsAndColorspace(عرض, ارتفاع, format, colorspace, 0, convert->pixels, convert->pitch, dst_format, dst_colorspace, dst_properties, final_dst, final_dst_pitch)) {
            اذهب انجامشده;
        }
    }
    نتیجه = true;

انجامشده:
    إذا (convert) {
        SDL_DestroySurface(convert);
    }
    أرجع نتیجه;
}

bool SDL_PremultiplyAlpha(صحيح عرض, صحيح ارتفاع,
                         SDL_PixelFormat src_format, ثابت فراغ *src, صحيح src_pitch,
                         SDL_PixelFormat dst_format, فراغ *dst, صحيح dst_pitch, bool خطی)
{
    SDL_Colorspace src_colorspace = SDL_GetDefaultColorspaceForFormat(src_format);
    SDL_Colorspace dst_colorspace = SDL_GetDefaultColorspaceForFormat(dst_format);

    أرجع SDL_PremultiplyAlphaPixelsAndColorspace(عرض, ارتفاع, src_format, src_colorspace, 0, src, src_pitch, dst_format, dst_colorspace, 0, dst, dst_pitch, خطی);
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
    bool نتیجه = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        أرجع SDL_InvalidParamError("surface");
    }

    SDL_GetSurfaceClipRect(surface, &clip_rect);
    SDL_مجموعه_Surface_Clip_Rect(surface, عدم);

    إذا (!SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_BYTESPERPIXEL(surface->format) <= حجم(Uint32)) {
        Uint32 color;

        color = SDL_MapSurfaceRGBA(surface,
                    (Uint8)SDL_roundf(SDL_clamp(r, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(g, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(b, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(a, 0.0f, 1.0f) * 255.0f));
        نتیجه = SDL_FillSurfaceRect(surface, عدم, color);
    } وإلا إذا (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // We can't directly set an RGB value on a YUV surface
        SDL_Surface *tmp = SDL_CreateSurfaceUninitialized(surface->w, surface->h, SDL_PIXELFORMAT_ARGB8888);
        إذا (!tmp) {
            اذهب انجامشده;
        }

        إذا (SDL_ClearSurface(tmp, r, g, b, a)) {
            نتیجه = SDL_ConvertPixelsAndColorspace(surface->w, surface->h, tmp->format, tmp->colorspace, tmp->props, tmp->pixels, tmp->pitch, surface->format, surface->colorspace, surface->props, surface->pixels, surface->pitch);
        }
        SDL_DestroySurface(tmp);
    } وإلا {
        // Take advantage of blit color conversion
        SDL_Surface *tmp = SDL_CreateSurfaceUninitialized(1, 1, SDL_PIXELFORMAT_RGBA128_FLOAT);
        إذا (!tmp) {
            اذهب انجامشده;
        }
        SDL_مجموعه_Surface_Colorspace(tmp, surface->colorspace);
        SDL_مجموعه_Surface_Blend_نما(tmp, SDL_BLENDMODE_NONE);

        عائم *pixels = (عائم *)tmp->pixels;
        pixels[0] = r;
        pixels[1] = g;
        pixels[2] = b;
        pixels[3] = a;

        نتیجه = SDL_BlitSurfaceScaled(tmp, عدم, surface, عدم, SDL_SCALEMODE_نزدیکترین);
        SDL_DestroySurface(tmp);
    }

انجامشده:
    SDL_مجموعه_Surface_Clip_Rect(surface, &clip_rect);

    أرجع نتیجه;
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
    size_t بایتها_در_هر_pixel;
    Uint8 استفادهنشده;
    Uint8 *p;
    bool نتیجه = false;

    إذا (r) {
        *r = 0;
    } وإلا {
        r = &استفادهنشده;
    }

    إذا (g) {
        *g = 0;
    } وإلا {
        g = &استفادهنشده;
    }

    إذا (b) {
        *b = 0;
    } وإلا {
        b = &استفادهنشده;
    }

    إذا (a) {
        *a = 0;
    } وإلا {
        a = &استفادهنشده;
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

    بایتها_در_هر_pixel = SDL_BYTESPERPIXEL(surface->format);

    إذا (SDL_MUSTLOCK(surface)) {
        إذا (!SDL_قفل_Surface(surface)) {
            أرجع false;
        }
    }

    p = (Uint8 *)surface->pixels + y * surface->pitch + x * بایتها_در_هر_pixel;

    إذا (بایتها_در_هر_pixel <= حجم(pixel) &&
        !SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_COLORSPACEPRIMARIES(surface->colorspace) == SDL_COLOR_PRIMARIES_BT709) {
        /* Fill the appropriate number of least-significant bytes of pixel,
         * leaving the most-significant bytes set to zero */
#إذا SDL_BYTEORDER == SDL_BIG_ENDIAN
        SDL_memcpy(((Uint8 *)&pixel) + (حجم(pixel) - بایتها_در_هر_pixel), p, بایتها_در_هر_pixel);
#وإلا
        SDL_memcpy(&pixel, p, بایتها_در_هر_pixel);
#پایان_اگر
        SDL_GetRGBA(pixel, surface->fmt, surface->palette, r, g, b, a);
        نتیجه = true;
    } وإلا إذا (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // FIXME: We need code to extract a single macroblock from a YUV surface
        SDL_Surface *converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        إذا (converted) {
            نتیجه = SDL_ReadSurfacePixel(converted, x, y, r, g, b, a);
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
            نتیجه = true;
        }
    }

    إذا (SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }
    أرجع نتیجه;
}

bool SDL_ReadSurfacePixelFloat(SDL_Surface *surface, صحيح x, صحيح y, عائم *r, عائم *g, عائم *b, عائم *a)
{
    عائم استفادهنشده;
    bool نتیجه = false;

    إذا (r) {
        *r = 0.0f;
    } وإلا {
        r = &استفادهنشده;
    }

    إذا (g) {
        *g = 0.0f;
    } وإلا {
        g = &استفادهنشده;
    }

    إذا (b) {
        *b = 0.0f;
    } وإلا {
        b = &استفادهنشده;
    }

    إذا (a) {
        *a = 0.0f;
    } وإلا {
        a = &استفادهنشده;
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
            نتیجه = true;
        }
    } وإلا إذا (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // FIXME: We need code to extract a single macroblock from a YUV surface
        SDL_Surface *converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        إذا (converted) {
            نتیجه = SDL_ReadSurfacePixelFloat(converted, x, y, r, g, b, a);
            SDL_DestroySurface(converted);
        }
    } وإلا {
        // This is really slow, but it gets the job done
        عائم rgba[4];
        Uint8 *p;

        إذا (SDL_MUSTLOCK(surface)) {
            إذا (!SDL_قفل_Surface(surface)) {
                أرجع false;
            }
        }

        p = (Uint8 *)surface->pixels + y * surface->pitch + x * SDL_BYTESPERPIXEL(surface->format);

        إذا (surface->format == SDL_PIXELFORMAT_RGBA128_FLOAT) {
            SDL_memcpy(rgba, p, حجم(rgba));
            نتیجه = true;
        } وإلا {
            SDL_Colorspace src_colorspace = surface->colorspace;
            SDL_Colorspace dst_colorspace = (src_colorspace == SDL_COLORSPACE_SRGB_خطی ? SDL_COLORSPACE_SRGB_خطی : SDL_COLORSPACE_SRGB);

            إذا (SDL_ConvertPixelsAndColorspace(1, 1, surface->format, src_colorspace, surface->props, p, surface->pitch, SDL_PIXELFORMAT_RGBA128_FLOAT, dst_colorspace, 0, rgba, حجم(rgba))) {
                نتیجه = true;
            }
        }

        إذا (نتیجه) {
            *r = rgba[0];
            *g = rgba[1];
            *b = rgba[2];
            *a = rgba[3];
        }

        إذا (SDL_MUSTLOCK(surface)) {
            SDL_UnlockSurface(surface);
        }
    }
    أرجع نتیجه;
}

bool SDL_WriteSurfacePixel(SDL_Surface *surface, صحيح x, صحيح y, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    Uint32 pixel = 0;
    size_t بایتها_در_هر_pixel;
    Uint8 *p;
    bool نتیجه = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        أرجع SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        أرجع SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        أرجع SDL_InvalidParamError("y");
    }

    بایتها_در_هر_pixel = SDL_BYTESPERPIXEL(surface->format);

    إذا (SDL_MUSTLOCK(surface)) {
        إذا (!SDL_قفل_Surface(surface)) {
            أرجع false;
        }
    }

    p = (Uint8 *)surface->pixels + y * surface->pitch + x * بایتها_در_هر_pixel;

    إذا (بایتها_در_هر_pixel <= حجم(pixel) && !SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        pixel = SDL_MapRGBA(surface->fmt, surface->palette, r, g, b, a);
#إذا SDL_BYTEORDER == SDL_BIG_ENDIAN
        SDL_memcpy(p, ((Uint8 *)&pixel) + (حجم(pixel) - بایتها_در_هر_pixel), بایتها_در_هر_pixel);
#وإلا
        SDL_memcpy(p, &pixel, بایتها_در_هر_pixel);
#پایان_اگر
        نتیجه = true;
    } وإلا إذا (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        نتیجه = SDL_Unsupported();
    } وإلا {
        // This is really slow, but it gets the job done
        Uint8 rgba[4];

        rgba[0] = r;
        rgba[1] = g;
        rgba[2] = b;
        rgba[3] = a;
        نتیجه = SDL_ConvertPixelsAndColorspace(1, 1, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, rgba, حجم(rgba), surface->format, surface->colorspace, surface->props, p, surface->pitch);
    }

    إذا (SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }
    أرجع نتیجه;
}

bool SDL_WriteSurfacePixelFloat(SDL_Surface *surface, صحيح x, صحيح y, عائم r, عائم g, عائم b, عائم a)
{
    bool نتیجه = false;

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

        r8 = (Uint8)SDL_دور(SDL_clamp(r, 0.0f, 1.0f) * 255.0f);
        g8 = (Uint8)SDL_دور(SDL_clamp(g, 0.0f, 1.0f) * 255.0f);
        b8 = (Uint8)SDL_دور(SDL_clamp(b, 0.0f, 1.0f) * 255.0f);
        a8 = (Uint8)SDL_دور(SDL_clamp(a, 0.0f, 1.0f) * 255.0f);
        إذا (SDL_WriteSurfacePixel(surface, x, y, r8, g8, b8, a8)) {
            نتیجه = true;
        }
    } وإلا إذا (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        نتیجه = SDL_Unsupported();
    } وإلا {
        // This is really slow, but it gets the job done
        عائم rgba[4];
        Uint8 *p;

        إذا (SDL_MUSTLOCK(surface)) {
            إذا (!SDL_قفل_Surface(surface)) {
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
            نتیجه = true;
        } وإلا {
            SDL_Colorspace dst_colorspace = surface->colorspace;
            SDL_Colorspace src_colorspace = (dst_colorspace == SDL_COLORSPACE_SRGB_خطی ? SDL_COLORSPACE_SRGB_خطی : SDL_COLORSPACE_SRGB);

            نتیجه = SDL_ConvertPixelsAndColorspace(1, 1, SDL_PIXELFORMAT_RGBA128_FLOAT, src_colorspace, 0, rgba, حجم(rgba), surface->format, dst_colorspace, surface->props, p, surface->pitch);
        }

        إذا (SDL_MUSTLOCK(surface)) {
            SDL_UnlockSurface(surface);
        }
    }
    أرجع نتیجه;
}

/*
 * Free a surface created by the above function.
 */
فراغ SDL_DestroySurface(SDL_Surface *surface)
{
    إذا (!SDL_SurfaceValid(surface)) {
        أرجع;
    }
    إذا (surface->داخلی_flags & SDL_داخلی_SURFACE_DONTFREE) {
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
#اگر_تعریف_شده SDL_HAVE_RLE
    إذا (surface->داخلی_flags & SDL_داخلی_SURFACE_RLEACCEL) {
        SDL_UnRLESurface(surface);
    }
#پایان_اگر
    SDL_مجموعه_Surface_Palette(surface, عدم);

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

    إذا (!(surface->داخلی_flags & SDL_داخلی_SURFACE_پشته)) {
        SDL_free(surface);
    }
}

SDL_Surface *SDL_بارگیری_Surface_IO(SDL_IOStream *src, bool closeio)
{
    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        أرجع عدم;
    }

    إذا (SDL_IsBMP(src)) {
        أرجع SDL_بارگیری_BMP_IO(src, closeio);
    } وإلا إذا (SDL_IsPNG(src)) {
        أرجع SDL_بارگیری_PNG_IO(src, closeio);
    } وإلا إذا (SDL_IsJPG(src)) {
        أرجع SDL_بارگیری_JPG_IO(src, closeio);
    } وإلا {
        إذا (closeio) {
            SDL_CloseIO(src);
        }
        SDL_مجموعه_Error("Unsupported image format");
        أرجع عدم;
    }
}

SDL_Surface *SDL_بارگیری_Surface(ثابت حرف *file)
{
    SDL_IOStream *جریان = SDL_IOFromFile(file, "rb");
    إذا (!جریان) {
        أرجع عدم;
    }

    أرجع SDL_بارگیری_Surface_IO(جریان, true);
}
