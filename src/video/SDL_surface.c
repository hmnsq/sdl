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
SDL_COMPILE_وقت_ASSERT(surface_سائز_assumptions,
                        حجم(صحیح) == حجم(Sint32) && حجم(size_t) >= حجم(Sint32));

SDL_COMPILE_وقت_ASSERT(can_indicate_حد_سے_تجاوز, SDL_سائز_MAX > SDL_MAX_SINT32);

// Magic!
ساکن حرف SDL_surface_magic;

// Public routines

bool SDL_SurfaceValid(SDL_Surface *surface)
{
    واپس (surface && surface->reserved == &SDL_surface_magic);
}

خالی SDL_Update_Surface_تالا_Flag(SDL_Surface *surface)
{
    // We need to mark the surface as needing unlock while locked
    اگر ((surface->flags & SDL_SURFACE_LOCKED) ||
        (surface->اندرونی_flags & SDL_اندرونی_SURFACE_RLEACCEL)) {
        surface->flags |= SDL_SURFACE_تالا_NEEDED;
    } ورنہ {
        surface->flags &= ~SDL_SURFACE_تالا_NEEDED;
    }
}

/*
 * Calculate the pad-aligned scanline width of a surface.
 *
 * for FOURCC, use SDL_CalculateYUVSize()
 */
ساکن bool SDL_CalculateRGBSize(Uint32 format, size_t چوڑائی, size_t اونچائی, size_t *سائز, size_t *pitch, bool اقل)
{
    اگر (SDL_BITSPERPIXEL(format) >= 8) {
        اگر (!SDL_سائز_mul_check_حد_سے_تجاوز(چوڑائی, SDL_BYTESPERPIXEL(format), pitch)) {
            واپس SDL_سیٹ_Error("width * bpp would overflow");
        }
    } ورنہ {
        اگر (!SDL_سائز_mul_check_حد_سے_تجاوز(چوڑائی, SDL_BITSPERPIXEL(format), pitch)) {
            واپس SDL_سیٹ_Error("width * bpp would overflow");
        }
        اگر (!SDL_سائز_جوڑو_check_حد_سے_تجاوز(*pitch, 7, pitch)) {
            واپس SDL_سیٹ_Error("aligning pitch would overflow");
        }
        *pitch /= 8;
    }
    اگر (!اقل) {
        // 4-byte aligning for speed
        اگر (!SDL_سائز_جوڑو_check_حد_سے_تجاوز(*pitch, 3, pitch)) {
            واپس SDL_سیٹ_Error("aligning pitch would overflow");
        }
        *pitch &= ~3;
    }

    اگر (!SDL_سائز_mul_check_حد_سے_تجاوز(اونچائی, *pitch, سائز)) {
        واپس SDL_سیٹ_Error("height * pitch would overflow");
    }

    واپس true;
}

bool SDL_Calculate_Surface_سائز(SDL_PixelFormat format, صحیح چوڑائی, صحیح اونچائی, size_t *سائز, size_t *pitch, bool اقل_Pitch)
{
    size_t p = 0, sz = 0;

    اگر (سائز) {
        *سائز = 0;
    }

    اگر (pitch) {
        *pitch = 0;
    }

    اگر (SDL_ISPIXELFORMAT_FOURCC(format)) {
        اگر (format == SDL_PIXELFORMAT_MJPG) {
            // We don't know in advance what it will be, we'll figure it out later.
            واپس true;
        }

        اگر (!SDL_CalculateYUVSize(format, چوڑائی, اونچائی, &sz, &p)) {
            // Overflow...
            واپس false;
        }
    } ورنہ {
        اگر (!SDL_CalculateRGBSize(format, چوڑائی, اونچائی, &sz, &p, اقل_Pitch)) {
            // Overflow...
            واپس false;
        }
    }

    اگر (سائز) {
        *سائز = sz;
    }

    اگر (pitch) {
        *pitch = p;
    }

    واپس true;
}

ساکن bool SDL_InitializeSurface(SDL_Surface *surface, صحیح چوڑائی, صحیح اونچائی, SDL_PixelFormat format, SDL_Colorspace colorspace, SDL_PropertiesID props, خالی *pixels, صحیح pitch, bool onstack)
{
    SDL_zerop(surface);

    surface->flags = SDL_SURFACE_PREALLOCATED;
    surface->format = format;
    surface->w = چوڑائی;
    surface->h = اونچائی;
    surface->pixels = pixels;
    surface->pitch = pitch;
    surface->reserved = &SDL_surface_magic;

    اگر (onstack) {
        surface->اندرونی_flags |= SDL_اندرونی_SURFACE_ڈھیر;
    }

    surface->fmt = SDL_GetPixelFormatDetails(format);
    اگر (!surface->fmt) {
        SDL_DestroySurface(surface);
        واپس false;
    }

    // Initialize the clip rect
    surface->clip_rect.w = چوڑائی;
    surface->clip_rect.h = اونچائی;

    // Allocate an empty mapping
    surface->map.info.r = 0xFF;
    surface->map.info.g = 0xFF;
    surface->map.info.b = 0xFF;
    surface->map.info.a = 0xFF;

    اگر (colorspace == SDL_COLORSPACE_UNKNOWN) {
        surface->colorspace = SDL_GetDefaultColorspaceForFormat(format);
    } ورنہ {
        surface->colorspace = colorspace;
    }

    اگر (props) {
        اگر (!SDL_CopyProperties(props, SDL_GetSurfaceProperties(surface))) {
            SDL_DestroySurface(surface);
            واپس false;
        }
    }

    // By default surfaces with an alpha mask are set up for blending
    اگر (SDL_ISPIXELFORMAT_ALPHA(surface->format)) {
        SDL_سیٹ_Surface_Blend_منوال(surface, SDL_BLENDMODE_BLEND);
    }

    // The surface is ready to go
    surface->refcount = 1;
    واپس true;
}

/*
 * Create an empty surface of the appropriate depth using the given format
 */
ساکن SDL_Surface *SDL_Create_Surface_اندرونی(صحیح چوڑائی, صحیح اونچائی, SDL_PixelFormat format, bool clear_surface)
{
    size_t pitch, سائز;
    SDL_Surface *surface;

    CHECK_PARAM(چوڑائی < 0) {
        SDL_InvalidParamError("width");
        واپس تہی;
    }

    CHECK_PARAM(اونچائی < 0) {
        SDL_InvalidParamError("height");
        واپس تہی;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        واپس تہی;
    }

    اگر (!SDL_Calculate_Surface_سائز(format, چوڑائی, اونچائی, &سائز, &pitch, false /* not minimal pitch */)) {
        // Overflow...
        واپس تہی;
    }

    // Allocate and initialize the surface
    surface = (SDL_Surface *)SDL_malloc(حجم(*surface));
    اگر (!surface) {
        واپس تہی;
    }

    اگر (!SDL_InitializeSurface(surface, چوڑائی, اونچائی, format, SDL_COLORSPACE_UNKNOWN, 0, تہی, (صحیح)pitch, false)) {
        واپس تہی;
    }

    اگر (surface->w && surface->h && format != SDL_PIXELFORMAT_MJPG) {
        surface->flags &= ~SDL_SURFACE_PREALLOCATED;
        اگر (SDL_GetHintBoolean("SDL_SURFACE_MALLOC", false)) {
            اگر (clear_surface) {
                surface->pixels = SDL_calloc(1, سائز);
            } ورنہ {
                surface->pixels = SDL_malloc(سائز);
            }
        } ورنہ {
            surface->flags |= SDL_SURFACE_SIMD_ALIGNED;
            اگر (clear_surface) {
                surface->pixels = SDL_aligned_alloc_zero(SDL_GetSIMDAlignment(), سائز);
            } ورنہ {
                surface->pixels = SDL_aligned_alloc(SDL_GetSIMDAlignment(), سائز);
            }
        }
        اگر (!surface->pixels) {
            SDL_DestroySurface(surface);
            واپس تہی;
        }
    }
    واپس surface;
}

SDL_Surface *SDL_CreateSurfaceZeroed(صحیح چوڑائی, صحیح اونچائی, SDL_PixelFormat format)
{
    واپس SDL_Create_Surface_اندرونی(چوڑائی, اونچائی, format, true);
}

SDL_Surface *SDL_CreateSurfaceUninitialized(صحیح چوڑائی, صحیح اونچائی, SDL_PixelFormat format)
{
    واپس SDL_Create_Surface_اندرونی(چوڑائی, اونچائی, format, false);
}

SDL_Surface *SDL_CreateSurface(صحیح چوڑائی, صحیح اونچائی, SDL_PixelFormat format)
{
    واپس SDL_CreateSurfaceZeroed(چوڑائی, اونچائی, format);
}


/*
 * Create an RGB surface from an existing memory buffer using the given
 * enum SDL_PIXELFORMAT_* format
 */
SDL_Surface *SDL_CreateSurfaceFrom(صحیح چوڑائی, صحیح اونچائی, SDL_PixelFormat format, خالی *pixels, صحیح pitch)
{
    CHECK_PARAM(چوڑائی < 0) {
        SDL_InvalidParamError("width");
        واپس تہی;
    }

    CHECK_PARAM(اونچائی < 0) {
        SDL_InvalidParamError("height");
        واپس تہی;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        واپس تہی;
    }

    اگر (pitch == 0 && !pixels) {
        // The application will fill these in later with valid values
    } ورنہ {
        size_t اقل_Pitch;

        اگر (!SDL_Calculate_Surface_سائز(format, چوڑائی, اونچائی, تہی, &اقل_Pitch, true /* minimal pitch */)) {
            // Overflow...
            واپس تہی;
        }

        CHECK_PARAM(pitch < 0 || (size_t)pitch < اقل_Pitch) {
            SDL_InvalidParamError("pitch");
            واپس تہی;
        }
    }

    // Allocate and initialize the surface
    SDL_Surface *surface = (SDL_Surface *)SDL_malloc(حجم(*surface));
    اگر (!surface ||
        !SDL_InitializeSurface(surface, چوڑائی, اونچائی, format, SDL_COLORSPACE_UNKNOWN, 0, pixels, pitch, false)) {
        واپس تہی;
    }
    واپس surface;
}

SDL_PropertiesID SDL_GetSurfaceProperties(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        واپس 0;
    }

    اگر (!surface->props) {
        surface->props = SDL_CreateProperties();
    }
    واپس surface->props;
}

bool SDL_سیٹ_Surface_Colorspace(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        واپس SDL_InvalidParamError("surface");
    }

    surface->colorspace = colorspace;
    واپس true;
}

SDL_Colorspace SDL_GetSurfaceColorspace(SDL_Surface *surface)
{
    اگر (!SDL_SurfaceValid(surface)) {
        واپس SDL_COLORSPACE_UNKNOWN;
    }

    واپس surface->colorspace;
}

اعشاری SDL_Get_Default_SDRWhite_نقطہ(SDL_Colorspace colorspace)
{
    واپس SDL_Get_Surface_SDRWhite_نقطہ(تہی, colorspace);
}

اعشاری SDL_Get_Surface_SDRWhite_نقطہ(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    SDL_TransferCharacteristics transfer = SDL_COLORSPACETRANSFER(colorspace);

    اگر (transfer == SDL_TRANSFER_CHARACTERISTICS_خطی ||
        transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
        SDL_PropertiesID props;
        اعشاری default_قدر = 1.0f;

        اگر (SDL_SurfaceValid(surface)) {
            props = surface->props;
        } ورنہ {
            props = 0;
        }
        اگر (transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
            /* The older standards use an SDR white point of 100 nits.
             * ITU-R BT.2408-6 recommends using an SDR white point of 203 nits.
             * This is the default Chrome uses, and what a lot of game content
             * assumes, so we'll go with that.
             */
            ثابت اعشاری DEFAULT_PQ_SDR_WHITE_نقطہ = 203.0f;
            default_قدر = DEFAULT_PQ_SDR_WHITE_نقطہ;
        }
        واپس SDL_GetFloatProperty(props, SDL_PROP_SURFACE_SDR_WHITE_نقطہ_FLOAT, default_قدر);
    }
    واپس 1.0f;
}

اعشاری SDL_GetDefaultHDRHeadroom(SDL_Colorspace colorspace)
{
    واپس SDL_GetSurfaceHDRHeadroom(تہی, colorspace);
}

اعشاری SDL_GetSurfaceHDRHeadroom(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    SDL_TransferCharacteristics transfer = SDL_COLORSPACETRANSFER(colorspace);

    اگر (transfer == SDL_TRANSFER_CHARACTERISTICS_خطی ||
        transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
        SDL_PropertiesID props;
        اعشاری default_قدر = 0.0f;

        اگر (SDL_SurfaceValid(surface)) {
            props = surface->props;
        } ورنہ {
            props = 0;
        }
        واپس SDL_GetFloatProperty(props, SDL_PROP_SURFACE_HDR_HEADROOM_FLOAT, default_قدر);
    }
    واپس 1.0f;
}

SDL_Palette *SDL_CreateSurfacePalette(SDL_Surface *surface)
{
    SDL_Palette *palette;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        واپس تہی;
    }

    CHECK_PARAM(!SDL_ISPIXELFORMAT_اشاریہ_دار(surface->format)) {
        SDL_سیٹ_Error("The surface is not indexed format");
        واپس تہی;
    }

    palette = SDL_CreatePalette((1 << SDL_BITSPERPIXEL(surface->format)));
    اگر (!palette) {
        واپس تہی;
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

    اگر (!SDL_سیٹ_Surface_Palette(surface, palette)) {
        SDL_DestroyPalette(palette);
        واپس تہی;
    }

    // The surface has retained the palette, we can remove the reference here
    SDL_assert(palette->refcount == 2);
    SDL_DestroyPalette(palette);
    واپس palette;
}

bool SDL_سیٹ_Surface_Palette(SDL_Surface *surface, SDL_Palette *palette)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        واپس SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(palette && !SDL_ISPIXELFORMAT_اشاریہ_دار(surface->format)) {
        واپس SDL_سیٹ_Error("Surface doesn't use a palette");
    }

    CHECK_PARAM(palette && palette->ncolors > (1 << SDL_BITSPERPIXEL(surface->format))) {
        واپس SDL_سیٹ_Error("Palette doesn't match surface format");
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

    واپس true;
}

SDL_Palette *SDL_GetSurfacePalette(SDL_Surface *surface)
{
    اگر (!SDL_SurfaceValid(surface)) {
        واپس تہی;
    }

    واپس surface->palette;
}

bool SDL_جوڑو_Surface_Alternate_Image(SDL_Surface *surface, SDL_Surface *image)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        واپس SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(!SDL_SurfaceValid(image)) {
        واپس SDL_InvalidParamError("image");
    }

    SDL_Surface **images = (SDL_Surface **)SDL_realloc(surface->images, (surface->عدد_images + 1) * حجم(*images));
    اگر (!images) {
        واپس false;
    }
    images[surface->عدد_images] = image;
    surface->images = images;
    ++surface->عدد_images;
    ++image->refcount;
    واپس true;
}

bool SDL_SurfaceHasAlternateImages(SDL_Surface *surface)
{
    اگر (!SDL_SurfaceValid(surface)) {
        واپس false;
    }

    واپس (surface->عدد_images > 0);
}

SDL_Surface **SDL_GetSurfaceImages(SDL_Surface *surface, صحیح *گنتی)
{
    اگر (گنتی) {
        *گنتی = 0;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        واپس تہی;
    }

    صحیح عدد_images = 1 + surface->عدد_images;
    SDL_Surface **images = (SDL_Surface **)SDL_malloc((عدد_images + 1) * حجم(*images));
    اگر (!images) {
        واپس تہی;
    }
    images[0] = surface;
    اگر (surface->عدد_images > 0) {
        SDL_memcpy(&images[1], surface->images, (surface->عدد_images * حجم(images[1])));
    }
    images[عدد_images] = تہی;

    اگر (گنتی) {
        *گنتی = عدد_images;
    }
    واپس images;
}

SDL_Surface *SDL_GetSurfaceImage(SDL_Surface *surface, اعشاری display_scale)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        واپس تہی;
    }

    اگر (!SDL_SurfaceHasAlternateImages(surface)) {
        ++surface->refcount;
        واپس surface;
    }

    // This surface has high DPI images, pick the best one available, or scale one to the correct size
    SDL_Surface **images = SDL_GetSurfaceImages(surface, تہی);
    اگر (!images) {
        // Failure, fall back to the existing surface
        ++surface->refcount;
        واپس surface;
    }

    // Find closest image. Images that are larger than the
    // desired size are preferred over images that are smaller.
    SDL_Surface *closest = تہی;
    صحیح desired_w = (صحیح)SDL_باری(surface->w * display_scale);
    صحیح desired_h = (صحیح)SDL_باری(surface->h * display_scale);
    صحیح desired_سائز = desired_w * desired_h;
    صحیح closest_فاصلہ = -1;
    صحیح closest_سائز = -1;
    برائے (صحیح i = 0; images[i]; ++i) {
        SDL_Surface *candidate = images[i];
        صحیح سائز = candidate->w * candidate->h;
        صحیح delta_w = (candidate->w - desired_w);
        صحیح delta_h = (candidate->h - desired_h);
        صحیح فاصلہ = (delta_w * delta_w) + (delta_h * delta_h);
        اگر (closest_فاصلہ < 0 || فاصلہ < closest_فاصلہ ||
            (سائز > desired_سائز && closest_سائز < desired_سائز)) {
            closest = candidate;
            closest_فاصلہ = فاصلہ;
            closest_سائز = سائز;
        }
    }
    SDL_free(images);
    SDL_assert(closest != تہی);    // We should always have at least one surface

    اگر (closest->w == desired_w && closest->h == desired_h) {
        ++closest->refcount;
        واپس closest;
    }

    // We need to scale the image to the correct size. To maintain good image quality, downscaling
    // is done in steps, never reducing the width and height by more than half each time.
    SDL_Surface *scaled = closest;
    کرو {
        صحیح اگلا_scaled_w = SDL_max(desired_w, (scaled->w + 1) / 2);
        صحیح اگلا_scaled_h = SDL_max(desired_h, (scaled->h + 1) / 2);
        SDL_Surface *اگلا_scaled = SDL_ScaleSurface(scaled, اگلا_scaled_w, اگلا_scaled_h, SDL_SCALEMODE_خطی);
        اگر (scaled != closest) {
            SDL_DestroySurface(scaled);
        }
        scaled = اگلا_scaled;
        اگر (!scaled) {
            // Failure, fall back to the closest surface
            ++closest->refcount;
            واپس closest;
        }
    } جب (scaled->w != desired_w || scaled->h != desired_h);

    واپس scaled;
}

خالی SDL_RemoveSurfaceAlternateImages(SDL_Surface *surface)
{
    اگر (!SDL_SurfaceValid(surface)) {
        واپس;
    }

    اگر (surface->عدد_images > 0) {
        برائے (صحیح i = 0; i < surface->عدد_images; ++i) {
            SDL_DestroySurface(surface->images[i]);
        }
        SDL_free(surface->images);
        surface->images = تہی;
        surface->عدد_images = 0;
    }
}

bool SDL_سیٹ_Surface_RLE(SDL_Surface *surface, bool enabled)
{
    صحیح flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        واپس SDL_InvalidParamError("surface");
    }

    flags = surface->map.info.flags;
    اگر (enabled) {
        surface->map.info.flags |= SDL_COPY_RLE_DESIRED;
    } ورنہ {
        surface->map.info.flags &= ~SDL_COPY_RLE_DESIRED;
    }
    اگر (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    واپس true;
}

bool SDL_SurfaceHasRLE(SDL_Surface *surface)
{
    اگر (!SDL_SurfaceValid(surface)) {
        واپس false;
    }

    اگر (!(surface->map.info.flags & SDL_COPY_RLE_DESIRED)) {
        واپس false;
    }

    واپس true;
}

bool SDL_سیٹ_Surface_Color_کلید(SDL_Surface *surface, bool enabled, Uint32 کلید)
{
    صحیح flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        واپس SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(surface->palette && کلید >= ((Uint32)surface->palette->ncolors)) {
        واپس SDL_InvalidParamError("key");
    }

    flags = surface->map.info.flags;
    اگر (enabled) {
        surface->map.info.flags |= SDL_COPY_COLORKEY;
        surface->map.info.colorkey = کلید;
    } ورنہ {
        surface->map.info.flags &= ~SDL_COPY_COLORKEY;
    }
    اگر (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }

    واپس true;
}

bool SDL_Surface_Has_Color_کلید(SDL_Surface *surface)
{
    اگر (!SDL_SurfaceValid(surface)) {
        واپس false;
    }

    اگر (!(surface->map.info.flags & SDL_COPY_COLORKEY)) {
        واپس false;
    }

    واپس true;
}

bool SDL_Get_Surface_Color_کلید(SDL_Surface *surface, Uint32 *کلید)
{
    اگر (کلید) {
        *کلید = 0;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        واپس SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(!(surface->map.info.flags & SDL_COPY_COLORKEY)) {
        واپس SDL_سیٹ_Error("Surface doesn't have a colorkey");
    }

    اگر (کلید) {
        *کلید = surface->map.info.colorkey;
    }
    واپس true;
}

/* This is a fairly slow function to switch from colorkey to alpha
   NB: it doesn't handle bpp 1 or 3, because they have no alpha channel */
ساکن خالی SDL_Convert_Colorkey_مقصد_Alpha(SDL_Surface *surface, bool ignore_alpha)
{
    صحیح x, y, bpp;

    اگر (!SDL_SurfaceValid(surface)) {
        واپس;
    }

    اگر (!(surface->map.info.flags & SDL_COPY_COLORKEY) ||
        !SDL_ISPIXELFORMAT_ALPHA(surface->format)) {
        واپس;
    }

    bpp = SDL_BYTESPERPIXEL(surface->format);

    SDL_تالا_Surface(surface);

    اگر (bpp == 2) {
        Uint16 *صف, *spot;
        Uint16 ckey = (Uint16)surface->map.info.colorkey;
        Uint16 نقاب = (Uint16)(~surface->fmt->Amask);

        // Ignore, or not, alpha in colorkey comparison
        اگر (ignore_alpha) {
            ckey &= نقاب;
            صف = (Uint16 *)surface->pixels;
            برائے (y = surface->h; y--;) {
                spot = صف;
                برائے (x = surface->w; x--;) {
                    اگر ((*spot & نقاب) == ckey) {
                        *spot &= نقاب;
                    }
                    ++spot;
                }
                صف += surface->pitch / 2;
            }
        } ورنہ {
            صف = (Uint16 *)surface->pixels;
            برائے (y = surface->h; y--;) {
                spot = صف;
                برائے (x = surface->w; x--;) {
                    اگر (*spot == ckey) {
                        *spot &= نقاب;
                    }
                    ++spot;
                }
                صف += surface->pitch / 2;
            }
        }
    } ورنہ اگر (bpp == 4) {
        Uint32 *صف, *spot;
        Uint32 ckey = surface->map.info.colorkey;
        Uint32 نقاب = ~surface->fmt->Amask;

        // Ignore, or not, alpha in colorkey comparison
        اگر (ignore_alpha) {
            ckey &= نقاب;
            صف = (Uint32 *)surface->pixels;
            برائے (y = surface->h; y--;) {
                spot = صف;
                برائے (x = surface->w; x--;) {
                    اگر ((*spot & نقاب) == ckey) {
                        *spot &= نقاب;
                    }
                    ++spot;
                }
                صف += surface->pitch / 4;
            }
        } ورنہ {
            صف = (Uint32 *)surface->pixels;
            برائے (y = surface->h; y--;) {
                spot = صف;
                برائے (x = surface->w; x--;) {
                    اگر (*spot == ckey) {
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
    صحیح flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        واپس SDL_InvalidParamError("surface");
    }

    surface->map.info.r = r;
    surface->map.info.g = g;
    surface->map.info.b = b;

    flags = surface->map.info.flags;
    اگر (r != 0xFF || g != 0xFF || b != 0xFF) {
        surface->map.info.flags |= SDL_COPY_MODULATE_COLOR;
    } ورنہ {
        surface->map.info.flags &= ~SDL_COPY_MODULATE_COLOR;
    }
    اگر (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    واپس true;
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
        واپس SDL_InvalidParamError("surface");
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
    واپس true;
}

bool SDL_سیٹ_Surface_Alpha_Mod(SDL_Surface *surface, Uint8 alpha)
{
    صحیح flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        واپس SDL_InvalidParamError("surface");
    }

    surface->map.info.a = alpha;

    flags = surface->map.info.flags;
    اگر (alpha != 0xFF) {
        surface->map.info.flags |= SDL_COPY_MODULATE_ALPHA;
    } ورنہ {
        surface->map.info.flags &= ~SDL_COPY_MODULATE_ALPHA;
    }
    اگر (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    واپس true;
}

bool SDL_GetSurfaceAlphaMod(SDL_Surface *surface, Uint8 *alpha)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        اگر (alpha) {
            *alpha = 255;
        }
        واپس SDL_InvalidParamError("surface");
    }

    اگر (alpha) {
        *alpha = surface->map.info.a;
    }
    واپس true;
}

bool SDL_سیٹ_Surface_Blend_منوال(SDL_Surface *surface, SDL_Blend_منوال blend_منوال)
{
    صحیح flags;
    bool نتیجہ = true;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        واپس SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(blend_منوال == SDL_BLENDMODE_INVALID) {
        واپس SDL_InvalidParamError("blendMode");
    }

    flags = surface->map.info.flags;
    surface->map.info.flags &= ~SDL_COPY_BLEND_نقاب;
    انتخاب (blend_منوال) {
    حالت SDL_BLENDMODE_NONE:
        توڑو;
    حالت SDL_BLENDMODE_BLEND:
        surface->map.info.flags |= SDL_COPY_BLEND;
        توڑو;
    حالت SDL_BLENDMODE_BLEND_PREMULTIPLIED:
        surface->map.info.flags |= SDL_COPY_BLEND_PREMULTIPLIED;
        توڑو;
    حالت SDL_BLENDMODE_جوڑو:
        surface->map.info.flags |= SDL_COPY_جوڑو;
        توڑو;
    حالت SDL_BLENDMODE_جوڑو_PREMULTIPLIED:
        surface->map.info.flags |= SDL_COPY_جوڑو_PREMULTIPLIED;
        توڑو;
    حالت SDL_BLENDMODE_MOD:
        surface->map.info.flags |= SDL_COPY_MOD;
        توڑو;
    حالت SDL_BLENDMODE_MUL:
        surface->map.info.flags |= SDL_COPY_MUL;
        توڑو;
    طےشدہ:
        نتیجہ = SDL_Unsupported();
        توڑو;
    }

    اگر (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }

    واپس نتیجہ;
}

bool SDL_Get_Surface_Blend_منوال(SDL_Surface *surface, SDL_Blend_منوال *blend_منوال)
{
    اگر (blend_منوال) {
        *blend_منوال = SDL_BLENDMODE_INVALID;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        واپس SDL_InvalidParamError("surface");
    }

    اگر (!blend_منوال) {
        واپس true;
    }

    انتخاب (surface->map.info.flags & SDL_COPY_BLEND_نقاب) {
    حالت SDL_COPY_BLEND:
        *blend_منوال = SDL_BLENDMODE_BLEND;
        توڑو;
    حالت SDL_COPY_BLEND_PREMULTIPLIED:
        *blend_منوال = SDL_BLENDMODE_BLEND_PREMULTIPLIED;
        توڑو;
    حالت SDL_COPY_جوڑو:
        *blend_منوال = SDL_BLENDMODE_جوڑو;
        توڑو;
    حالت SDL_COPY_جوڑو_PREMULTIPLIED:
        *blend_منوال = SDL_BLENDMODE_جوڑو_PREMULTIPLIED;
        توڑو;
    حالت SDL_COPY_MOD:
        *blend_منوال = SDL_BLENDMODE_MOD;
        توڑو;
    حالت SDL_COPY_MUL:
        *blend_منوال = SDL_BLENDMODE_MUL;
        توڑو;
    طےشدہ:
        *blend_منوال = SDL_BLENDMODE_NONE;
        توڑو;
    }
    واپس true;
}

bool SDL_سیٹ_Surface_Clip_Rect(SDL_Surface *surface, ثابت SDL_Rect *rect)
{
    SDL_Rect بھرا_rect;

    // Don't do anything if there's no surface to act on
    اگر (!SDL_SurfaceValid(surface)) {
        واپس false;
    }

    // Set up the full surface rectangle
    بھرا_rect.x = 0;
    بھرا_rect.y = 0;
    بھرا_rect.w = surface->w;
    بھرا_rect.h = surface->h;

    // Set the clipping rectangle
    اگر (!rect) {
        surface->clip_rect = بھرا_rect;
        واپس true;
    }
    واپس SDL_GetRectIntersection(rect, &بھرا_rect, &surface->clip_rect);
}

bool SDL_GetSurfaceClipRect(SDL_Surface *surface, SDL_Rect *rect)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        اگر (rect) {
            SDL_zerop(rect);
        }
        واپس SDL_InvalidParamError("surface");
    }
    CHECK_PARAM(!rect) {
        واپس SDL_InvalidParamError("rect");
    }
    *rect = surface->clip_rect;
    واپس true;
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
        واپس false;
    }
    واپس src->map.blit(src, srcrect, dst, dstrect);
}

bool SDL_BlitSurface(SDL_Surface *src, ثابت SDL_Rect *srcrect, SDL_Surface *dst, ثابت SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src) || (!src->pixels && !SDL_MUSTLOCK(src))) {
        واپس SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst) || (!dst->pixels && !SDL_MUSTLOCK(dst))) {
        واپس SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        واپس SDL_سیٹ_Error("Surfaces must not be locked during blit");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    اگر (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
    } ورنہ {
        r_dst.x = 0;
        r_dst.y = 0;
    }

    // clip the source rectangle to the source surface
    اگر (srcrect) {
        SDL_Rect tmp;
        اگر (SDL_GetRectIntersection(srcrect, &r_src, &tmp) == false) {
            واپس true;
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
            واپس true;
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
        واپس true;
    }

    // Switch back to a fast blit if we were previously stretching
    اگر (src->map.info.flags & SDL_COPY_قریب_ترین) {
        src->map.info.flags &= ~SDL_COPY_قریب_ترین;
        SDL_InvalidateMap(&src->map);
    }

    واپس SDL_BlitSurfaceUnchecked(src, &r_src, dst, &r_dst);
}

ساکن bool SDL_BlitSurfaceClippedScaled(SDL_Surface *src, ثابت SDL_Rect *srcrect, SDL_Surface *dst, ثابت SDL_Rect *dstrect, SDL_Scale_منوال scale_منوال)
{
    // We need to scale first, then blit into dst because we're clipping in the destination surface pixel coordinates
    bool نتیجہ;
    صحیح saved_w = src->w;
    صحیح saved_h = src->h;
    خالی *saved_pixels = src->pixels;
    src->w = srcrect->w;
    src->h = srcrect->h;
    src->pixels = (Uint8 *)src->pixels + srcrect->y * src->pitch + srcrect->x * SDL_BYTESPERPIXEL(src->format);
    SDL_Surface *scaled = SDL_ScaleSurface(src, dstrect->w, dstrect->h, scale_منوال);
    اگر (scaled) {
        نتیجہ = SDL_BlitSurface(scaled, تہی, dst, dstrect);
        SDL_DestroySurface(scaled);
    } ورنہ {
        نتیجہ = false;
    }
    src->w = saved_w;
    src->h = saved_h;
    src->pixels = saved_pixels;
    واپس نتیجہ;
}

bool SDL_BlitSurfaceScaled(SDL_Surface *src, ثابت SDL_Rect *srcrect, SDL_Surface *dst, ثابت SDL_Rect *dstrect, SDL_Scale_منوال scale_منوال)
{
    SDL_Rect r_src, r_dst;
    bool نتیجہ;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src) || (!src->pixels && !SDL_MUSTLOCK(src))) {
        واپس SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst) || (!dst->pixels && !SDL_MUSTLOCK(dst))) {
        واپس SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        واپس SDL_سیٹ_Error("Surfaces must not be locked during blit");
    }

    انتخاب (scale_منوال) {
    حالت SDL_SCALEMODE_قریب_ترین:
        توڑو;
    حالت SDL_SCALEMODE_خطی:
        توڑو;
    حالت SDL_SCALEMODE_PIXELART:
        scale_منوال = SDL_SCALEMODE_قریب_ترین;
        توڑو;
    طےشدہ:
        واپس SDL_InvalidParamError("scaleMode");
    }

    صحیح src_w = srcrect ? srcrect->w : src->w;
    صحیح src_h = srcrect ? srcrect->h : src->h;
    صحیح dst_w = dstrect ? dstrect->w : dst->w;
    صحیح dst_h = dstrect ? dstrect->h : dst->h;
    اگر (src_w == dst_w && src_h == dst_h) {
        // No scaling, defer to regular blit
        واپس SDL_BlitSurface(src, srcrect, dst, dstrect);
    }

    اگر (src->w == 0 || src->h == 0) {
        // Nothing to do
        واپس true;
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
    } ورنہ {
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
            واپس true;
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
        واپس true;
    }

    اگر (tmp.x != r_dst.x || tmp.y != r_dst.y || tmp.w != r_dst.w || tmp.h != r_dst.h) {
        // Need to do a clipped and scaled blit
        واپس SDL_BlitSurfaceClippedScaled(src, &r_src, dst, &r_dst, scale_منوال);
    }

    اگر (SDL_MUSTLOCK(src)) {
        اگر (!SDL_تالا_Surface(src)) {
            واپس false;
        }
    }
    اگر (SDL_MUSTLOCK(dst)) {
        اگر (!SDL_تالا_Surface(dst)) {
            اگر (SDL_MUSTLOCK(src)) {
                SDL_UnlockSurface(src);
            }
            واپس false;
        }
    }

    نتیجہ = SDL_BlitSurfaceUncheckedScaled(src, &r_src, dst, &r_dst, scale_منوال);

    اگر (SDL_MUSTLOCK(src)) {
        SDL_UnlockSurface(src);
    }
    اگر (SDL_MUSTLOCK(dst)) {
        SDL_UnlockSurface(dst);
    }
    واپس نتیجہ;
}

/**
 *  This is a semi-private blit function and it performs low-level surface
 *  scaled blitting only.
 */
bool SDL_BlitSurfaceUncheckedScaled(SDL_Surface *src, ثابت SDL_Rect *srcrect, SDL_Surface *dst, ثابت SDL_Rect *dstrect, SDL_Scale_منوال scale_منوال)
{
    ساکن ثابت Uint32 complex_copy_flags = (SDL_COPY_MODULATE_نقاب | SDL_COPY_BLEND_نقاب | SDL_COPY_COLORKEY);

    اگر (srcrect->w > SDL_MAX_UINT16 || srcrect->h > SDL_MAX_UINT16 ||
        dstrect->w > SDL_MAX_UINT16 || dstrect->h > SDL_MAX_UINT16) {
        واپس SDL_سیٹ_Error("Size too large for scaling");
    }

    اگر (!(src->map.info.flags & SDL_COPY_قریب_ترین)) {
        src->map.info.flags |= SDL_COPY_قریب_ترین;
        SDL_InvalidateMap(&src->map);
    }

    اگر (scale_منوال == SDL_SCALEMODE_قریب_ترین || scale_منوال == SDL_SCALEMODE_PIXELART) {
        اگر (!(src->map.info.flags & complex_copy_flags) &&
            src->format == dst->format &&
            (!SDL_ISPIXELFORMAT_اشاریہ_دار(src->format) ||
             (SDL_BITSPERPIXEL(src->format) == 8 && SDL_IsSamePalette(src->palette, dst->palette))) &&
            SDL_BYTESPERPIXEL(src->format) <= 4) {
            واپس SDL_StretchSurface(src, srcrect, dst, dstrect, SDL_SCALEMODE_قریب_ترین);
        } ورنہ اگر (SDL_BITSPERPIXEL(src->format) < 8) {
            // Scaling bitmap not yet supported, convert to RGBA for blit
            bool نتیجہ = false;
            SDL_Surface *tmp = SDL_ConvertSurface(src, SDL_PIXELFORMAT_ARGB8888);
            اگر (tmp) {
                نتیجہ = SDL_BlitSurfaceUncheckedScaled(tmp, srcrect, dst, dstrect, SDL_SCALEMODE_قریب_ترین);
                SDL_DestroySurface(tmp);
            }
            واپس نتیجہ;
        } ورنہ {
            واپس SDL_BlitSurfaceUnchecked(src, srcrect, dst, dstrect);
        }
    } ورنہ {
        اگر (!(src->map.info.flags & complex_copy_flags) &&
            src->format == dst->format &&
            !SDL_ISPIXELFORMAT_اشاریہ_دار(src->format) &&
            SDL_BYTESPERPIXEL(src->format) == 4 &&
            src->format != SDL_PIXELFORMAT_ARGB2101010) {
            // fast path
            واپس SDL_StretchSurface(src, srcrect, dst, dstrect, SDL_SCALEMODE_خطی);
        } ورنہ اگر (SDL_BITSPERPIXEL(src->format) < 8) {
            // Scaling bitmap not yet supported, convert to RGBA for blit
            bool نتیجہ = false;
            SDL_Surface *tmp = SDL_ConvertSurface(src, SDL_PIXELFORMAT_ARGB8888);
            اگر (tmp) {
                نتیجہ = SDL_BlitSurfaceUncheckedScaled(tmp, srcrect, dst, dstrect, scale_منوال);
                SDL_DestroySurface(tmp);
            }
            واپس نتیجہ;
        } ورنہ {
            // Use intermediate surface(s)
            SDL_Surface *tmp1 = تہی;
            bool نتیجہ;
            SDL_Rect srcrect2;
            صحیح is_complex_copy_flags = (src->map.info.flags & complex_copy_flags);

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
            اگر (SDL_BYTESPERPIXEL(src->format) != 4 || src->format == SDL_PIXELFORMAT_ARGB2101010) {
                SDL_PixelFormat fmt;
                اگر (SDL_BYTESPERPIXEL(dst->format) == 4 && dst->format != SDL_PIXELFORMAT_ARGB2101010 &&
                    (SDL_ISPIXELFORMAT_ALPHA(dst->format) || !is_complex_copy_flags)) {
                    fmt = dst->format;
                } ورنہ {
                    fmt = SDL_PIXELFORMAT_ARGB8888;
                }
                tmp1 = SDL_ConvertSurfaceRect(src, srcrect, fmt);
                اگر (!tmp1) {
                    واپس false;
                }
                src = tmp1;
                srcrect2.x = 0;
                srcrect2.y = 0;
            }

            // Intermediate scaling
            اگر (is_complex_copy_flags || src->format != dst->format) {
                SDL_Rect tmprect;
                SDL_Surface *tmp2 = SDL_CreateSurfaceUninitialized(dstrect->w, dstrect->h, src->format);
                SDL_StretchSurface(src, &srcrect2, tmp2, تہی, SDL_SCALEMODE_خطی);

                SDL_سیٹ_Surface_Color_Mod(tmp2, r, g, b);
                SDL_سیٹ_Surface_Alpha_Mod(tmp2, alpha);
                SDL_سیٹ_Surface_Blend_منوال(tmp2, blend_منوال);

                tmprect.x = 0;
                tmprect.y = 0;
                tmprect.w = dstrect->w;
                tmprect.h = dstrect->h;
                نتیجہ = SDL_BlitSurfaceUnchecked(tmp2, &tmprect, dst, dstrect);
                SDL_DestroySurface(tmp2);
            } ورنہ {
                نتیجہ = SDL_StretchSurface(src, &srcrect2, dst, dstrect, SDL_SCALEMODE_خطی);
            }

            SDL_DestroySurface(tmp1);
            واپس نتیجہ;
        }
    }
}

bool SDL_BlitSurfaceTiled(SDL_Surface *src, ثابت SDL_Rect *srcrect, SDL_Surface *dst, ثابت SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        واپس SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        واپس SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        واپس SDL_سیٹ_Error("Surfaces must not be locked during blit");
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
    } ورنہ {
        r_dst.x = 0;
        r_dst.y = 0;
        r_dst.w = dst->w;
        r_dst.h = dst->h;
    }

    // clip the source rectangle to the source surface
    اگر (srcrect) {
        اگر (SDL_GetRectIntersection(srcrect, &r_src, &r_src) == false) {
            واپس true;
        }

        // For tiling we don't adjust the destination rectangle
    }

    // clip the destination rectangle against the clip rectangle
    {
        اگر (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &r_dst) == false) {
            واپس true;
        }

        // For tiling we don't adjust the source rectangle
    }

    // Switch back to a fast blit if we were previously stretching
    اگر (src->map.info.flags & SDL_COPY_قریب_ترین) {
        src->map.info.flags &= ~SDL_COPY_قریب_ترین;
        SDL_InvalidateMap(&src->map);
    }

    صحیح صفیں = r_dst.h / r_src.h;
    صحیح ستون_تعداد = r_dst.w / r_src.w;
    صحیح بقایا_w = r_dst.w % r_src.w;
    صحیح بقایا_h = r_dst.h % r_src.h;
    SDL_Rect curr_src, curr_dst;

    SDL_copyp(&curr_src, &r_src);
    curr_dst.y = r_dst.y;
    curr_dst.w = r_src.w;
    curr_dst.h = r_src.h;
    برائے (صحیح y = 0; y < صفیں; ++y) {
        curr_dst.x = r_dst.x;
        برائے (صحیح x = 0; x < ستون_تعداد; ++x) {
            اگر (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                واپس false;
            }
            curr_dst.x += curr_dst.w;
        }
        اگر (بقایا_w) {
            curr_src.w = بقایا_w;
            curr_dst.w = بقایا_w;
            اگر (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                واپس false;
            }
            curr_src.w = r_src.w;
            curr_dst.w = r_src.w;
        }
        curr_dst.y += curr_dst.h;
    }
    اگر (بقایا_h) {
        curr_src.h = بقایا_h;
        curr_dst.h = بقایا_h;
        curr_dst.x = r_dst.x;
        برائے (صحیح x = 0; x < ستون_تعداد; ++x) {
            اگر (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                واپس false;
            }
            curr_dst.x += curr_dst.w;
        }
        اگر (بقایا_w) {
            curr_src.w = بقایا_w;
            curr_dst.w = بقایا_w;
            اگر (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                واپس false;
            }
        }
    }
    واپس true;
}

bool SDL_BlitSurfaceTiledWithScale(SDL_Surface *src, ثابت SDL_Rect *srcrect, اعشاری scale, SDL_Scale_منوال scale_منوال, SDL_Surface *dst, ثابت SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        واپس SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        واپس SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        واپس SDL_سیٹ_Error("Surfaces must not be locked during blit");
    }
    CHECK_PARAM(scale < 0.0f) {
        واپس SDL_InvalidParamError("scale");
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
    } ورنہ {
        r_dst.x = 0;
        r_dst.y = 0;
        r_dst.w = dst->w;
        r_dst.h = dst->h;
    }

    // clip the source rectangle to the source surface
    اگر (srcrect) {
        اگر (SDL_GetRectIntersection(srcrect, &r_src, &r_src) == false) {
            واپس true;
        }

        // For tiling we don't adjust the destination rectangle
    }

    // clip the destination rectangle against the clip rectangle
    {
        اگر (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &r_dst) == false) {
            واپس true;
        }

        // For tiling we don't adjust the source rectangle
    }

    // Switch back to a fast blit if we were previously stretching
    اگر (src->map.info.flags & SDL_COPY_قریب_ترین) {
        src->map.info.flags &= ~SDL_COPY_قریب_ترین;
        SDL_InvalidateMap(&src->map);
    }

    صحیح tile_چوڑائی = (صحیح)SDL_roundf(r_src.w * scale);
    صحیح tile_اونچائی = (صحیح)SDL_roundf(r_src.h * scale);
    اگر (tile_چوڑائی <= 0 || tile_اونچائی <= 0) {
        // Nothing to do
        واپس true;
    }
    صحیح صفیں = r_dst.h / tile_اونچائی;
    صحیح ستون_تعداد = r_dst.w / tile_چوڑائی;
    صحیح بقایا_dst_w = (r_dst.w - ستون_تعداد * tile_چوڑائی);
    صحیح بقایا_dst_h = (r_dst.h - صفیں * tile_اونچائی);
    صحیح بقایا_src_w = (صحیح)(بقایا_dst_w / scale);
    صحیح بقایا_src_h = (صحیح)(بقایا_dst_h / scale);
    SDL_Rect curr_src, curr_dst;

    SDL_copyp(&curr_src, &r_src);
    curr_dst.y = r_dst.y;
    curr_dst.w = tile_چوڑائی;
    curr_dst.h = tile_اونچائی;
    برائے (صحیح y = 0; y < صفیں; ++y) {
        curr_dst.x = r_dst.x;
        برائے (صحیح x = 0; x < ستون_تعداد; ++x) {
            اگر (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scale_منوال)) {
                واپس false;
            }
            curr_dst.x += curr_dst.w;
        }
        اگر (بقایا_dst_w > 0) {
            curr_src.w = بقایا_src_w;
            curr_dst.w = بقایا_dst_w;
            اگر (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scale_منوال)) {
                واپس false;
            }
            curr_src.w = r_src.w;
            curr_dst.w = tile_چوڑائی;
        }
        curr_dst.y += curr_dst.h;
    }
    اگر (بقایا_dst_h > 0) {
        curr_src.h = بقایا_src_h;
        curr_dst.h = بقایا_dst_h;
        curr_dst.x = r_dst.x;
        برائے (صحیح x = 0; x < ستون_تعداد; ++x) {
            اگر (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scale_منوال)) {
                واپس false;
            }
            curr_dst.x += curr_dst.w;
        }
        اگر (بقایا_dst_w > 0) {
            curr_src.w = بقایا_src_w;
            curr_dst.w = بقایا_dst_w;
            اگر (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scale_منوال)) {
                واپس false;
            }
        }
    }
    واپس true;
}

bool SDL_BlitSurface9Grid(SDL_Surface *src, ثابت SDL_Rect *srcrect, صحیح بایاں_چوڑائی, صحیح دایاں_چوڑائی, صحیح چوٹی_اونچائی, صحیح bottom_اونچائی, اعشاری scale, SDL_Scale_منوال scale_منوال, SDL_Surface *dst, ثابت SDL_Rect *dstrect)
{
    SDL_Rect بھرا_src, بھرا_dst;
    SDL_Rect curr_src, curr_dst;
    صحیح dst_بایاں_چوڑائی;
    صحیح dst_دایاں_چوڑائی;
    صحیح dst_چوٹی_اونچائی;
    صحیح dst_bottom_اونچائی;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        واپس SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        واپس SDL_InvalidParamError("dst");
    }

    اگر (!srcrect) {
        بھرا_src.x = 0;
        بھرا_src.y = 0;
        بھرا_src.w = src->w;
        بھرا_src.h = src->h;
        srcrect = &بھرا_src;
    }

    اگر (!dstrect) {
        بھرا_dst.x = 0;
        بھرا_dst.y = 0;
        بھرا_dst.w = dst->w;
        بھرا_dst.h = dst->h;
        dstrect = &بھرا_dst;
    }

    اگر (scale <= 0.0f || scale == 1.0f) {
        dst_بایاں_چوڑائی = بایاں_چوڑائی;
        dst_دایاں_چوڑائی = دایاں_چوڑائی;
        dst_چوٹی_اونچائی = چوٹی_اونچائی;
        dst_bottom_اونچائی = bottom_اونچائی;
    } ورنہ {
        dst_بایاں_چوڑائی = (صحیح)SDL_roundf(بایاں_چوڑائی * scale);
        dst_دایاں_چوڑائی = (صحیح)SDL_roundf(دایاں_چوڑائی * scale);
        dst_چوٹی_اونچائی = (صحیح)SDL_roundf(چوٹی_اونچائی * scale);
        dst_bottom_اونچائی = (صحیح)SDL_roundf(bottom_اونچائی * scale);
    }

    // Upper-left corner
    curr_src.x = srcrect->x;
    curr_src.y = srcrect->y;
    curr_src.w = بایاں_چوڑائی;
    curr_src.h = چوٹی_اونچائی;
    curr_dst.x = dstrect->x;
    curr_dst.y = dstrect->y;
    curr_dst.w = dst_بایاں_چوڑائی;
    curr_dst.h = dst_چوٹی_اونچائی;
    اگر (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_منوال)) {
        واپس false;
    }

    // Upper-right corner
    curr_src.x = srcrect->x + srcrect->w - دایاں_چوڑائی;
    curr_src.w = دایاں_چوڑائی;
    curr_dst.x = dstrect->x + dstrect->w - dst_دایاں_چوڑائی;
    curr_dst.w = dst_دایاں_چوڑائی;
    اگر (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_منوال)) {
        واپس false;
    }

    // Lower-right corner
    curr_src.y = srcrect->y + srcrect->h - bottom_اونچائی;
    curr_dst.y = dstrect->y + dstrect->h - dst_bottom_اونچائی;
    curr_dst.h = dst_bottom_اونچائی;
    اگر (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_منوال)) {
        واپس false;
    }

    // Lower-left corner
    curr_src.x = srcrect->x;
    curr_src.w = بایاں_چوڑائی;
    curr_dst.x = dstrect->x;
    curr_dst.w = dst_بایاں_چوڑائی;
    اگر (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_منوال)) {
        واپس false;
    }

    //بایاں
    curr_src.y = srcrect->y + چوٹی_اونچائی;
    curr_src.h = srcrect->h - چوٹی_اونچائی - bottom_اونچائی;
    curr_dst.y = dstrect->y + dst_چوٹی_اونچائی;
    curr_dst.h = dstrect->h - dst_چوٹی_اونچائی - dst_bottom_اونچائی;
    اگر (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_منوال)) {
        واپس false;
    }

    //دایاں
    curr_src.x = srcrect->x + srcrect->w - دایاں_چوڑائی;
    curr_src.w = دایاں_چوڑائی;
    curr_dst.x = dstrect->x + dstrect->w - dst_دایاں_چوڑائی;
    curr_dst.w = dst_دایاں_چوڑائی;
    اگر (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_منوال)) {
        واپس false;
    }

    //چوٹی
    curr_src.x = srcrect->x + بایاں_چوڑائی;
    curr_src.y = srcrect->y;
    curr_src.w = srcrect->w - بایاں_چوڑائی - دایاں_چوڑائی;
    curr_src.h = چوٹی_اونچائی;
    curr_dst.x = dstrect->x + dst_بایاں_چوڑائی;
    curr_dst.y = dstrect->y;
    curr_dst.w = dstrect->w - dst_بایاں_چوڑائی - dst_دایاں_چوڑائی;
    curr_dst.h = dst_چوٹی_اونچائی;
    اگر (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_منوال)) {
        واپس false;
    }

    // Bottom
    curr_src.y = srcrect->y + srcrect->h - bottom_اونچائی;
    curr_dst.y = dstrect->y + dstrect->h - dst_bottom_اونچائی;
    curr_dst.h = dst_bottom_اونچائی;
    اگر (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_منوال)) {
        واپس false;
    }

    // Center
    curr_src.x = srcrect->x + بایاں_چوڑائی;
    curr_src.y = srcrect->y + چوٹی_اونچائی;
    curr_src.w = srcrect->w - بایاں_چوڑائی - دایاں_چوڑائی;
    curr_src.h = srcrect->h - چوٹی_اونچائی - bottom_اونچائی;
    curr_dst.x = dstrect->x + dst_بایاں_چوڑائی;
    curr_dst.y = dstrect->y + dst_چوٹی_اونچائی;
    curr_dst.w = dstrect->w - dst_بایاں_چوڑائی - dst_دایاں_چوڑائی;
    curr_dst.h = dstrect->h - dst_چوٹی_اونچائی - dst_bottom_اونچائی;
    اگر (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_منوال)) {
        واپس false;
    }

    واپس true;
}

/*
 * Lock a surface to directly access the pixels
 */
bool SDL_تالا_Surface(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        واپس SDL_InvalidParamError("surface");
    }

    اگر (!surface->locked) {
#اگر_تعریف_شدہ SDL_HAVE_RLE
        // Perform the lock
        اگر (surface->اندرونی_flags & SDL_اندرونی_SURFACE_RLEACCEL) {
            SDL_UnRLESurface(surface);
        }
#اگر_ختم
    }

    // Increment the surface lock count, for recursive locks
    ++surface->locked;
    surface->flags |= SDL_SURFACE_LOCKED;
    SDL_Update_Surface_تالا_Flag(surface);

    // Ready to go..
    واپس true;
}

/*
 * Unlock a previously locked surface
 */
خالی SDL_UnlockSurface(SDL_Surface *surface)
{
    اگر (!SDL_SurfaceValid(surface)) {
        واپس;
    }

    // Only perform an unlock if we are locked
    اگر (!surface->locked || (--surface->locked > 0)) {
        واپس;
    }

    surface->flags &= ~SDL_SURFACE_LOCKED;
    SDL_Update_Surface_تالا_Flag(surface);
}

ساکن bool SDL_FlipSurfaceHorizontal(SDL_Surface *surface)
{
    bool isstack;
    Uint8 *صف, *a, *b, *tmp;
    صحیح i, j, bpp;

    اگر (SDL_BITSPERPIXEL(surface->format) < 8) {
        // We could implement this if needed, but we'd have to flip sets of bits within a byte
        واپس SDL_Unsupported();
    }

    اگر (surface->h <= 0) {
        واپس true;
    }

    اگر (surface->w <= 1) {
        واپس true;
    }

    bpp = SDL_BYTESPERPIXEL(surface->format);
    صف = (Uint8 *)surface->pixels;
    tmp = SDL_small_alloc(Uint8, surface->pitch, &isstack);
    اگر (!tmp) {
        واپس false;
    }
    برائے (i = surface->h; i--; ) {
        a = صف;
        b = a + (surface->w - 1) * bpp;
        برائے (j = surface->w / 2; j--; ) {
            SDL_memcpy(tmp, a, bpp);
            SDL_memcpy(a, b, bpp);
            SDL_memcpy(b, tmp, bpp);
            a += bpp;
            b -= bpp;
        }
        صف += surface->pitch;
    }
    SDL_small_free(tmp, isstack);
    واپس true;
}

ساکن bool SDL_FlipSurfaceVertical(SDL_Surface *surface)
{
    bool isstack;
    Uint8 *a, *b, *tmp;
    صحیح i;

    اگر (surface->h <= 1) {
        واپس true;
    }

    a = (Uint8 *)surface->pixels;
    b = a + (surface->h - 1) * surface->pitch;
    tmp = SDL_small_alloc(Uint8, surface->pitch, &isstack);
    اگر (!tmp) {
        واپس false;
    }
    برائے (i = surface->h / 2; i--; ) {
        SDL_memcpy(tmp, a, surface->pitch);
        SDL_memcpy(a, b, surface->pitch);
        SDL_memcpy(b, tmp, surface->pitch);
        a += surface->pitch;
        b -= surface->pitch;
    }
    SDL_small_free(tmp, isstack);
    واپس true;
}

bool SDL_FlipSurface(SDL_Surface *surface, SDL_Flip_منوال flip)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        واپس SDL_InvalidParamError("surface");
    }
    اگر (!surface->pixels) {
        واپس true;
    }

    bool نتیجہ = true;
    انتخاب (flip) {
    حالت SDL_FLIP_HORIZONTAL:
        نتیجہ = SDL_FlipSurfaceHorizontal(surface);
        توڑو;
    حالت SDL_FLIP_VERTICAL:
        نتیجہ = SDL_FlipSurfaceVertical(surface);
        توڑو;
    حالت SDL_FLIP_HORIZONTAL_AND_VERTICAL:
        نتیجہ &= SDL_FlipSurfaceHorizontal(surface);
        نتیجہ &= SDL_FlipSurfaceVertical(surface);
        توڑو;
    طےشدہ:
        نتیجہ = SDL_InvalidParamError("flip");
        توڑو;
    }
    واپس نتیجہ;
}

ساکن SDL_Surface *SDL_ConvertSurfaceRectAndColorspace(SDL_Surface *surface, ثابت SDL_Rect *rect, SDL_PixelFormat format, SDL_Palette *palette, SDL_Colorspace colorspace, SDL_PropertiesID props)
{
    SDL_Palette *عارضی_palette = تہی;
    SDL_Surface *convert = تہی;
    SDL_Colorspace src_colorspace;
    SDL_PropertiesID src_properties;
    Uint32 copy_flags;
    SDL_Color copy_color;
    SDL_Rect bounds;
    bool نتیجہ;
    bool palette_ck_transform = false;
    Uint8 palette_ck_قدر = 0;
    Uint8 *palette_saved_alpha = تہی;
    صحیح palette_saved_alpha_ncolors = 0;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        جاؤ error;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        جاؤ error;
    }

    // Set the bounds of the new surface
    bounds.x = 0;
    bounds.y = 0;
    bounds.w = surface->w;
    bounds.h = surface->h;
    اگر (rect) {
        bounds.w = rect->w;
        bounds.h = rect->h;
    } ورنہ {
        rect = &bounds;
    }

    // Check for empty destination palette! (results in empty image)
    اگر (palette) {
        صحیح i;
        برائے (i = 0; i < palette->ncolors; ++i) {
            اگر ((palette->colors[i].r != 0xFF) || (palette->colors[i].g != 0xFF) || (palette->colors[i].b != 0xFF)) {
                توڑو;
            }
        }
        اگر (i == palette->ncolors) {
            SDL_سیٹ_Error("Empty destination palette");
            جاؤ error;
        }
    } ورنہ اگر (SDL_ISPIXELFORMAT_اشاریہ_دار(format)) {
        // Create a dither palette for conversion
        عارضی_palette = SDL_CreatePalette(1 << SDL_BITSPERPIXEL(format));
        اگر (عارضی_palette) {
            SDL_DitherPalette(عارضی_palette);
            palette = عارضی_palette;
        }
    }

    src_colorspace = surface->colorspace;
    src_properties = surface->props;

    // Create a new surface with the desired format
    اگر (surface->pixels || SDL_MUSTLOCK(surface)) {
        convert = SDL_CreateSurfaceUninitialized(rect->w, rect->h, format);
    } ورنہ {
        convert = SDL_CreateSurfaceFrom(rect->w, rect->h, format, تہی, 0);
    }
    اگر (!convert) {
        جاؤ error;
    }
    اگر (SDL_ISPIXELFORMAT_اشاریہ_دار(format)) {
        SDL_سیٹ_Surface_Palette(convert, palette);
    }

    اگر (colorspace == SDL_COLORSPACE_UNKNOWN) {
        colorspace = src_colorspace;
    }
    SDL_سیٹ_Surface_Colorspace(convert, colorspace);

    اگر (SDL_ISPIXELFORMAT_FOURCC(format) || SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        اگر (surface->format == SDL_PIXELFORMAT_MJPG && format == SDL_PIXELFORMAT_MJPG) {
            // Just do a straight pixel copy of the JPEG image
            size_t سائز = (size_t)surface->pitch;
            convert->pixels = SDL_malloc(سائز);
            اگر (!convert->pixels) {
                جاؤ error;
            }
            convert->flags &= ~SDL_SURFACE_PREALLOCATED;
            convert->pitch = surface->pitch;
            SDL_memcpy(convert->pixels, surface->pixels, سائز);

        } ورنہ اگر (!SDL_ConvertPixelsAndColorspace(surface->w, surface->h, surface->format, src_colorspace, src_properties, surface->pixels, surface->pitch, convert->format, colorspace, props, convert->pixels, convert->pitch)) {
            جاؤ error;
        }

        // Save the original copy flags
        copy_flags = surface->map.info.flags;

        جاؤ انتہا;
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
        bool سیٹ_opaque = false;

        bool is_opaque, has_alpha_channel;
        SDL_DetectPalette(surface->palette, &is_opaque, &has_alpha_channel);

        اگر (is_opaque) {
            اگر (!has_alpha_channel) {
                سیٹ_opaque = true;
            }
        }

        // Set opaque and backup palette alpha values
        اگر (سیٹ_opaque) {
            صحیح i;
            palette_saved_alpha_ncolors = surface->palette->ncolors;
            اگر (palette_saved_alpha_ncolors > 0) {
                palette_saved_alpha = SDL_ڈھیر_alloc(Uint8, palette_saved_alpha_ncolors);
                برائے (i = 0; i < palette_saved_alpha_ncolors; i++) {
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
            palette_ck_قدر = surface->palette->colors[surface->map.info.colorkey].a;
            surface->palette->colors[surface->map.info.colorkey].a = SDL_ALPHA_TRANSPARENT;
        }
    }

    اگر (surface->pixels || SDL_MUSTLOCK(surface)) {
        نتیجہ = SDL_BlitSurfaceUnchecked(surface, rect, convert, &bounds);
    } ورنہ {
        نتیجہ = true;
    }

    // Restore colorkey alpha value
    اگر (palette_ck_transform) {
        surface->palette->colors[surface->map.info.colorkey].a = palette_ck_قدر;
    }

    // Restore palette alpha values
    اگر (palette_saved_alpha) {
        صحیح i;
        برائے (i = 0; i < palette_saved_alpha_ncolors; i++) {
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
    اگر (!نتیجہ) {
        جاؤ error;
    }

    اگر (copy_flags & SDL_COPY_COLORKEY) {
        bool سیٹ_colorkey_by_color = false;
        bool convert_colorkey = true;

        اگر (surface->palette) {
            اگر (palette &&
                surface->palette->ncolors <= palette->ncolors &&
                (SDL_memcmp(surface->palette->colors, palette->colors,
                            surface->palette->ncolors * حجم(SDL_Color)) == 0)) {
                // The palette is identical, just set the same colorkey
                SDL_سیٹ_Surface_Color_کلید(convert, true, surface->map.info.colorkey);
            } ورنہ اگر (!palette) {
                اگر (SDL_ISPIXELFORMAT_ALPHA(format)) {
                    // No need to add the colorkey, transparency is in the alpha channel
                } ورنہ {
                    // Only set the colorkey information
                    سیٹ_colorkey_by_color = true;
                    convert_colorkey = false;
                }
            } ورنہ {
                سیٹ_colorkey_by_color = true;
            }
        } ورنہ {
            سیٹ_colorkey_by_color = true;
        }

        اگر (سیٹ_colorkey_by_color) {
            SDL_Surface *tmp;
            SDL_Surface *tmp2;
            صحیح converted_colorkey = 0;

            // Create a dummy surface to get the colorkey converted
            tmp = SDL_CreateSurfaceUninitialized(1, 1, surface->format);
            اگر (!tmp) {
                جاؤ error;
            }

            // Share the palette, if any
            اگر (surface->palette) {
                SDL_سیٹ_Surface_Palette(tmp, surface->palette);
            }

            SDL_FillSurfaceRect(tmp, تہی, surface->map.info.colorkey);

            tmp->map.info.flags &= ~SDL_COPY_COLORKEY;

            // Conversion of the colorkey
            tmp2 = SDL_ConvertSurfaceAndColorspace(tmp, format, palette, colorspace, props);
            اگر (!tmp2) {
                SDL_DestroySurface(tmp);
                جاؤ error;
            }

            // Get the converted colorkey
            SDL_memcpy(&converted_colorkey, tmp2->pixels, tmp2->fmt->بائٹیں_فی_pixel);

            SDL_DestroySurface(tmp);
            SDL_DestroySurface(tmp2);

            // Set the converted colorkey on the new surface
            SDL_سیٹ_Surface_Color_کلید(convert, true, converted_colorkey);

            // This is needed when converting for 3D texture upload
            اگر (convert_colorkey) {
                SDL_Convert_Colorkey_مقصد_Alpha(convert, true);
            }
        }
    }

انتہا:
    اگر (عارضی_palette) {
        SDL_DestroyPalette(عارضی_palette);
    }

    SDL_سیٹ_Surface_Clip_Rect(convert, &surface->clip_rect);

    /* Enable alpha blending by default if the new surface has an
     * alpha channel or alpha modulation */
    اگر (SDL_ISPIXELFORMAT_ALPHA(format) ||
        (copy_flags & SDL_COPY_MODULATE_ALPHA)) {
        SDL_سیٹ_Surface_Blend_منوال(convert, SDL_BLENDMODE_BLEND);
    }
    اگر (copy_flags & SDL_COPY_RLE_DESIRED) {
        SDL_سیٹ_Surface_RLE(convert, true);
    }

    // Copy alternate images
    برائے (صحیح i = 0; i < surface->عدد_images; ++i) {
        اگر (!SDL_جوڑو_Surface_Alternate_Image(convert, surface->images[i])) {
            جاؤ error;
        }
    }

    // Copy properties
    اگر (surface->props) {
        اگر (!SDL_CopyProperties(surface->props, SDL_GetSurfaceProperties(convert))) {
            جاؤ error;
        }

        // Make sure the new surface doesn't reference an old SDL2 surface.
        SDL_ClearProperty(SDL_GetSurfaceProperties(convert), "sdl2-compat.surface2");
    }

    // We're ready to go!
    واپس convert;

error:
    اگر (عارضی_palette) {
        SDL_DestroyPalette(عارضی_palette);
    }
    اگر (convert) {
        SDL_DestroySurface(convert);
    }
    واپس تہی;
}

SDL_Surface *SDL_ConvertSurfaceAndColorspace(SDL_Surface *surface, SDL_PixelFormat format, SDL_Palette *palette, SDL_Colorspace colorspace, SDL_PropertiesID props)
{
    واپس SDL_ConvertSurfaceRectAndColorspace(surface, تہی, format, palette, colorspace, props);
}

SDL_Surface *SDL_RotateSurface(SDL_Surface *surface, اعشاری angle)
{
    SDL_Surface *rotated = تہی;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        واپس تہی;
    }

    SDL_Rect rect_dest;
    دوہرا cangle, sangle;
    SDL_FPoint center = { surface->w * 0.5f, surface->h * 0.5f };
    SDLgfx_rotozoom_Surface_سائز_Trig(surface->w, surface->h, angle, &center, &rect_dest, &cangle, &sangle);

    // This function requires a 32-bit surface or 8-bit surface with a colorkey
    اگر ((SDL_BITSPERPIXEL(surface->format) == 32 && SDL_PIXELLAYOUT(surface->format) == SDL_PACKEDLAYOUT_8888) ||
        (surface->format == SDL_PIXELFORMAT_INDEX8 && SDL_Surface_Has_Color_کلید(surface))) {
        rotated = SDLgfx_rotateSurface(surface, angle, 1, 0, 0, &rect_dest, cangle, sangle, &center);
    } ورنہ {
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
            ثابت اعشاری rotation = (SDL_Get_نمبر_Property(surface->props, SDL_PROP_SURFACE_ROTATION_FLOAT, 0) - angle);
            SDL_سیٹ_Float_Property(SDL_GetSurfaceProperties(rotated), SDL_PROP_SURFACE_ROTATION_FLOAT, rotation);
        }
    }

    واپس rotated;
}

SDL_Surface *SDL_DuplicateSurface(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        واپس تہی;
    }

    واپس SDL_ConvertSurfaceAndColorspace(surface, surface->format, surface->palette, surface->colorspace, surface->props);
}

SDL_Surface *SDL_ScaleSurface(SDL_Surface *surface, صحیح چوڑائی, صحیح اونچائی, SDL_Scale_منوال scale_منوال)
{
    SDL_Surface *convert = تہی;
    Uint32 copy_flags;
    SDL_Color copy_color;
    bool rc;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        جاؤ error;
    }

    اگر (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // We can't directly scale a YUV surface (yet!)
        SDL_Surface *tmp = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        اگر (!tmp) {
            واپس تہی;
        }

        SDL_Surface *scaled = SDL_ScaleSurface(tmp, چوڑائی, اونچائی, scale_منوال);
        SDL_DestroySurface(tmp);
        اگر (!scaled) {
            واپس تہی;
        }

        SDL_Surface *نتیجہ = SDL_ConvertSurfaceAndColorspace(scaled, surface->format, تہی, surface->colorspace, surface->props);
        SDL_DestroySurface(scaled);
        واپس نتیجہ;
    }

    اگر (SDL_ISPIXELFORMAT_اشاریہ_دار(surface->format)) {
        // Linear scaling requires conversion to RGBA and then slow pixel color lookup
        scale_منوال = SDL_SCALEMODE_قریب_ترین;
    }

    // Create a new surface with the desired size
    اگر (surface->pixels || SDL_MUSTLOCK(surface)) {
        convert = SDL_CreateSurfaceUninitialized(چوڑائی, اونچائی, surface->format);
    } ورنہ {
        convert = SDL_CreateSurfaceFrom(چوڑائی, اونچائی, surface->format, تہی, 0);
    }
    اگر (!convert) {
        جاؤ error;
    }
    SDL_سیٹ_Surface_Palette(convert, surface->palette);
    SDL_سیٹ_Surface_Colorspace(convert, surface->colorspace);
    SDL_سیٹ_Surface_RLE(convert, SDL_SurfaceHasRLE(surface));

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

        rc = SDL_BlitSurfaceScaled(surface, تہی, convert, تہی, scale_منوال);

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
    } ورنہ {
        rc = true;
    }

    // SDL_BlitSurfaceScaled failed, and so the conversion
    اگر (!rc) {
        جاؤ error;
    }

    // We're ready to go!
    واپس convert;

error:
    اگر (convert) {
        SDL_DestroySurface(convert);
    }
    واپس تہی;
}

SDL_Surface *SDL_ConvertSurfaceRect(SDL_Surface *surface, ثابت SDL_Rect *rect, SDL_PixelFormat format)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        واپس تہی;
    }

    واپس SDL_ConvertSurfaceRectAndColorspace(surface, rect, format, تہی, SDL_GetDefaultColorspaceForFormat(format), surface->props);
}

SDL_Surface *SDL_ConvertSurface(SDL_Surface *surface, SDL_PixelFormat format)
{
    واپس SDL_ConvertSurfaceRect(surface, تہی, format);
}

SDL_Surface *SDL_DuplicatePixels(صحیح چوڑائی, صحیح اونچائی, SDL_PixelFormat format, SDL_Colorspace colorspace, خالی *pixels, صحیح pitch)
{
    SDL_Surface *surface;
    اگر (pixels) {
        surface = SDL_CreateSurfaceUninitialized(چوڑائی, اونچائی, format);
    } ورنہ {
        surface = SDL_CreateSurfaceFrom(چوڑائی, اونچائی, format, تہی, 0);
    }
    اگر (!surface) {
        واپس تہی;
    }
    SDL_سیٹ_Surface_Colorspace(surface, colorspace);

    اگر (surface->pixels) {
        صحیح لمبائی = چوڑائی * SDL_BYTESPERPIXEL(format);
        Uint8 *src = (Uint8 *)pixels;
        Uint8 *dst = (Uint8 *)surface->pixels;
        صحیح صفیں = اونچائی;
        جب (صفیں--) {
            SDL_memcpy(dst, src, لمبائی);
            dst += surface->pitch;
            src += pitch;
        }
    }
    واپس surface;
}

bool SDL_ConvertPixelsAndColorspace(صحیح چوڑائی, صحیح اونچائی,
                      SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ثابت خالی *src, صحیح src_pitch,
                      SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, خالی *dst, صحیح dst_pitch)
{
    SDL_Surface src_surface;
    SDL_Surface dst_surface;
    SDL_Rect rect;
    خالی *nonconst_src = (خالی *)src;
    bool نتیجہ;

    CHECK_PARAM(!src) {
        واپس SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!src_pitch) {
        واپس SDL_InvalidParamError("src_pitch");
    }
    CHECK_PARAM(!dst) {
        واپس SDL_InvalidParamError("dst");
    }
    CHECK_PARAM(!dst_pitch) {
        واپس SDL_InvalidParamError("dst_pitch");
    }

    اگر (src_colorspace == SDL_COLORSPACE_UNKNOWN) {
        src_colorspace = SDL_GetDefaultColorspaceForFormat(src_format);
    }
    اگر (dst_colorspace == SDL_COLORSPACE_UNKNOWN) {
        dst_colorspace = SDL_GetDefaultColorspaceForFormat(dst_format);
    }

    اگر (src_format == SDL_PIXELFORMAT_MJPG) {
        واپس SDL_ConvertPixels_STB(چوڑائی, اونچائی, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    }

#اگر_تعریف_شدہ SDL_HAVE_YUV
    اگر (SDL_ISPIXELFORMAT_FOURCC(src_format) && SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        واپس SDL_Convert_Pixels_YUV_مقصد_YUV(چوڑائی, اونچائی, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } ورنہ اگر (SDL_ISPIXELFORMAT_FOURCC(src_format)) {
        واپس SDL_Convert_Pixels_YUV_مقصد_RGB(چوڑائی, اونچائی, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } ورنہ اگر (SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        واپس SDL_Convert_Pixels_RGB_مقصد_YUV(چوڑائی, اونچائی, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    }
#ورنہ
    اگر (SDL_ISPIXELFORMAT_FOURCC(src_format) || SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        واپس SDL_سیٹ_Error("SDL not built with YUV support");
    }
#اگر_ختم

    // Fast path for same format copy
    اگر (src_format == dst_format && src_colorspace == dst_colorspace) {
        اگر (src_pitch == dst_pitch) {
            SDL_memcpy(dst, src, اونچائی * src_pitch);
        } ورنہ {
            صحیح i;
            ثابت صحیح bpp = SDL_BYTESPERPIXEL(src_format);
            چوڑائی *= bpp;
            برائے (i = اونچائی; i--;) {
                SDL_memcpy(dst, src, چوڑائی);
                src = (ثابت Uint8 *)src + src_pitch;
                dst = (Uint8 *)dst + dst_pitch;
            }
        }
        واپس true;
    }

    اگر (!SDL_InitializeSurface(&src_surface, چوڑائی, اونچائی, src_format, src_colorspace, src_properties, nonconst_src, src_pitch, true)) {
        واپس false;
    }
    SDL_سیٹ_Surface_Blend_منوال(&src_surface, SDL_BLENDMODE_NONE);

    اگر (!SDL_InitializeSurface(&dst_surface, چوڑائی, اونچائی, dst_format, dst_colorspace, dst_properties, dst, dst_pitch, true)) {
        واپس false;
    }

    // Set up the rect and go!
    rect.x = 0;
    rect.y = 0;
    rect.w = چوڑائی;
    rect.h = اونچائی;
    نتیجہ = SDL_BlitSurfaceUnchecked(&src_surface, &rect, &dst_surface, &rect);

    SDL_DestroySurface(&src_surface);
    SDL_DestroySurface(&dst_surface);

    واپس نتیجہ;
}

bool SDL_ConvertPixels(صحیح چوڑائی, صحیح اونچائی, SDL_PixelFormat src_format, ثابت خالی *src, صحیح src_pitch, SDL_PixelFormat dst_format, خالی *dst, صحیح dst_pitch)
{
    واپس SDL_ConvertPixelsAndColorspace(چوڑائی, اونچائی,
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

ساکن خالی SDL_PremultiplyAlpha_AXYZ8888(صحیح چوڑائی, صحیح اونچائی, ثابت خالی *src, صحیح src_pitch, خالی *dst, صحیح dst_pitch)
{
    صحیح c;
    Uint32 srcpixel;
    Uint32 srcR, srcG, srcB, srcA;
    Uint32 dstpixel;
    Uint32 dstR, dstG, dstB, dstA;

    جب (اونچائی--) {
        ثابت Uint32 *src_px = (ثابت Uint32 *)src;
        Uint32 *dst_px = (Uint32 *)dst;
        برائے (c = چوڑائی; c; --c) {
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

ساکن خالی SDL_PremultiplyAlpha_XYZA8888(صحیح چوڑائی, صحیح اونچائی, ثابت خالی *src, صحیح src_pitch, خالی *dst, صحیح dst_pitch)
{
    صحیح c;
    Uint32 srcpixel;
    Uint32 srcR, srcG, srcB, srcA;
    Uint32 dstpixel;
    Uint32 dstR, dstG, dstB, dstA;

    جب (اونچائی--) {
        ثابت Uint32 *src_px = (ثابت Uint32 *)src;
        Uint32 *dst_px = (Uint32 *)dst;
        برائے (c = چوڑائی; c; --c) {
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

ساکن خالی SDL_PremultiplyAlpha_AXYZ128(صحیح چوڑائی, صحیح اونچائی, ثابت خالی *src, صحیح src_pitch, خالی *dst, صحیح dst_pitch)
{
    صحیح c;
    اعشاری flR, flG, flB, flA;

    جب (اونچائی--) {
        ثابت اعشاری *src_px = (ثابت اعشاری *)src;
        اعشاری *dst_px = (اعشاری *)dst;
        برائے (c = چوڑائی; c; --c) {
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

ساکن bool SDL_PremultiplyAlphaPixelsAndColorspace(صحیح چوڑائی, صحیح اونچائی, SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ثابت خالی *src, صحیح src_pitch, SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, خالی *dst, صحیح dst_pitch, bool خطی)
{
    SDL_Surface *convert = تہی;
    خالی *final_dst = dst;
    صحیح final_dst_pitch = dst_pitch;
    SDL_PixelFormat format;
    SDL_Colorspace colorspace;
    bool نتیجہ = false;

    CHECK_PARAM(!src) {
        واپس SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!src_pitch) {
        واپس SDL_InvalidParamError("src_pitch");
    }
    CHECK_PARAM(!dst) {
        واپس SDL_InvalidParamError("dst");
    }
    CHECK_PARAM(!dst_pitch) {
        واپس SDL_InvalidParamError("dst_pitch");
    }

    // Use a high precision format if we're converting to linear colorspace or using high precision pixel formats
    اگر (خطی ||
        SDL_ISPIXELFORMAT_10_ثنائی_ہندسہ(src_format) || SDL_BITSPERPIXEL(src_format) > 32 ||
        SDL_ISPIXELFORMAT_10_ثنائی_ہندسہ(dst_format) || SDL_BITSPERPIXEL(dst_format) > 32) {
        اگر (src_format == SDL_PIXELFORMAT_ARGB128_FLOAT ||
            src_format == SDL_PIXELFORMAT_ABGR128_FLOAT) {
            format = src_format;
        } ورنہ {
            format = SDL_PIXELFORMAT_ARGB128_FLOAT;
        }
    } ورنہ {
        اگر (src_format == SDL_PIXELFORMAT_ARGB8888 ||
            src_format == SDL_PIXELFORMAT_ABGR8888 ||
            src_format == SDL_PIXELFORMAT_RGBA8888 ||
            src_format == SDL_PIXELFORMAT_BGRA8888) {
            format = src_format;
        } ورنہ {
            format = SDL_PIXELFORMAT_ARGB8888;
        }
    }
    اگر (خطی) {
        colorspace = SDL_COLORSPACE_SRGB_خطی;
    } ورنہ {
        colorspace = SDL_COLORSPACE_SRGB;
    }

    اگر (src_format != format || src_colorspace != colorspace) {
        convert = SDL_CreateSurfaceUninitialized(چوڑائی, اونچائی, format);
        اگر (!convert) {
            جاؤ مکمل;
        }
        اگر (!SDL_ConvertPixelsAndColorspace(چوڑائی, اونچائی, src_format, src_colorspace, src_properties, src, src_pitch, format, colorspace, 0, convert->pixels, convert->pitch)) {
            جاؤ مکمل;
        }

        src = convert->pixels;
        src_pitch = convert->pitch;
        dst = convert->pixels;
        dst_pitch = convert->pitch;

    } ورنہ اگر (dst_format != format || dst_colorspace != colorspace) {
        convert = SDL_CreateSurfaceUninitialized(چوڑائی, اونچائی, format);
        اگر (!convert) {
            جاؤ مکمل;
        }
        dst = convert->pixels;
        dst_pitch = convert->pitch;
    }

    انتخاب (format) {
    حالت SDL_PIXELFORMAT_ARGB8888:
    حالت SDL_PIXELFORMAT_ABGR8888:
        SDL_PremultiplyAlpha_AXYZ8888(چوڑائی, اونچائی, src, src_pitch, dst, dst_pitch);
        توڑو;
    حالت SDL_PIXELFORMAT_RGBA8888:
    حالت SDL_PIXELFORMAT_BGRA8888:
        SDL_PremultiplyAlpha_XYZA8888(چوڑائی, اونچائی, src, src_pitch, dst, dst_pitch);
        توڑو;
    حالت SDL_PIXELFORMAT_ARGB128_FLOAT:
    حالت SDL_PIXELFORMAT_ABGR128_FLOAT:
        SDL_PremultiplyAlpha_AXYZ128(چوڑائی, اونچائی, src, src_pitch, dst, dst_pitch);
        توڑو;
    طےشدہ:
        SDL_سیٹ_Error("Unexpected internal pixel format");
        جاؤ مکمل;
    }

    اگر (dst != final_dst) {
        اگر (!SDL_ConvertPixelsAndColorspace(چوڑائی, اونچائی, format, colorspace, 0, convert->pixels, convert->pitch, dst_format, dst_colorspace, dst_properties, final_dst, final_dst_pitch)) {
            جاؤ مکمل;
        }
    }
    نتیجہ = true;

مکمل:
    اگر (convert) {
        SDL_DestroySurface(convert);
    }
    واپس نتیجہ;
}

bool SDL_PremultiplyAlpha(صحیح چوڑائی, صحیح اونچائی,
                         SDL_PixelFormat src_format, ثابت خالی *src, صحیح src_pitch,
                         SDL_PixelFormat dst_format, خالی *dst, صحیح dst_pitch, bool خطی)
{
    SDL_Colorspace src_colorspace = SDL_GetDefaultColorspaceForFormat(src_format);
    SDL_Colorspace dst_colorspace = SDL_GetDefaultColorspaceForFormat(dst_format);

    واپس SDL_PremultiplyAlphaPixelsAndColorspace(چوڑائی, اونچائی, src_format, src_colorspace, 0, src, src_pitch, dst_format, dst_colorspace, 0, dst, dst_pitch, خطی);
}

bool SDL_PremultiplySurfaceAlpha(SDL_Surface *surface, bool خطی)
{
    SDL_Colorspace colorspace;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        واپس SDL_InvalidParamError("surface");
    }

    colorspace = surface->colorspace;

    واپس SDL_PremultiplyAlphaPixelsAndColorspace(surface->w, surface->h, surface->format, colorspace, surface->props, surface->pixels, surface->pitch, surface->format, colorspace, surface->props, surface->pixels, surface->pitch, خطی);
}

bool SDL_ClearSurface(SDL_Surface *surface, اعشاری r, اعشاری g, اعشاری b, اعشاری a)
{
    SDL_Rect clip_rect;
    bool نتیجہ = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        واپس SDL_InvalidParamError("surface");
    }

    SDL_GetSurfaceClipRect(surface, &clip_rect);
    SDL_سیٹ_Surface_Clip_Rect(surface, تہی);

    اگر (!SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_BYTESPERPIXEL(surface->format) <= حجم(Uint32)) {
        Uint32 color;

        color = SDL_MapSurfaceRGBA(surface,
                    (Uint8)SDL_roundf(SDL_clamp(r, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(g, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(b, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(a, 0.0f, 1.0f) * 255.0f));
        نتیجہ = SDL_FillSurfaceRect(surface, تہی, color);
    } ورنہ اگر (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // We can't directly set an RGB value on a YUV surface
        SDL_Surface *tmp = SDL_CreateSurfaceUninitialized(surface->w, surface->h, SDL_PIXELFORMAT_ARGB8888);
        اگر (!tmp) {
            جاؤ مکمل;
        }

        اگر (SDL_ClearSurface(tmp, r, g, b, a)) {
            نتیجہ = SDL_ConvertPixelsAndColorspace(surface->w, surface->h, tmp->format, tmp->colorspace, tmp->props, tmp->pixels, tmp->pitch, surface->format, surface->colorspace, surface->props, surface->pixels, surface->pitch);
        }
        SDL_DestroySurface(tmp);
    } ورنہ {
        // Take advantage of blit color conversion
        SDL_Surface *tmp = SDL_CreateSurfaceUninitialized(1, 1, SDL_PIXELFORMAT_RGBA128_FLOAT);
        اگر (!tmp) {
            جاؤ مکمل;
        }
        SDL_سیٹ_Surface_Colorspace(tmp, surface->colorspace);
        SDL_سیٹ_Surface_Blend_منوال(tmp, SDL_BLENDMODE_NONE);

        اعشاری *pixels = (اعشاری *)tmp->pixels;
        pixels[0] = r;
        pixels[1] = g;
        pixels[2] = b;
        pixels[3] = a;

        نتیجہ = SDL_BlitSurfaceScaled(tmp, تہی, surface, تہی, SDL_SCALEMODE_قریب_ترین);
        SDL_DestroySurface(tmp);
    }

مکمل:
    SDL_سیٹ_Surface_Clip_Rect(surface, &clip_rect);

    واپس نتیجہ;
}

Uint32 SDL_MapSurfaceRGB(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b)
{
    واپس SDL_MapSurfaceRGBA(surface, r, g, b, SDL_ALPHA_OPAQUE);
}

Uint32 SDL_MapSurfaceRGBA(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        واپس true;
    }
    واپس SDL_MapRGBA(surface->fmt, surface->palette, r, g, b, a);
}

// This function Copyright 2023 Collabora Ltd., contributed to SDL under the ZLib license
bool SDL_ReadSurfacePixel(SDL_Surface *surface, صحیح x, صحیح y, Uint8 *r, Uint8 *g, Uint8 *b, Uint8 *a)
{
    Uint32 pixel = 0;
    size_t بائٹیں_فی_pixel;
    Uint8 غیر_مستعمل;
    Uint8 *p;
    bool نتیجہ = false;

    اگر (r) {
        *r = 0;
    } ورنہ {
        r = &غیر_مستعمل;
    }

    اگر (g) {
        *g = 0;
    } ورنہ {
        g = &غیر_مستعمل;
    }

    اگر (b) {
        *b = 0;
    } ورنہ {
        b = &غیر_مستعمل;
    }

    اگر (a) {
        *a = 0;
    } ورنہ {
        a = &غیر_مستعمل;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        واپس SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        واپس SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        واپس SDL_InvalidParamError("y");
    }

    بائٹیں_فی_pixel = SDL_BYTESPERPIXEL(surface->format);

    اگر (SDL_MUSTLOCK(surface)) {
        اگر (!SDL_تالا_Surface(surface)) {
            واپس false;
        }
    }

    p = (Uint8 *)surface->pixels + y * surface->pitch + x * بائٹیں_فی_pixel;

    اگر (بائٹیں_فی_pixel <= حجم(pixel) &&
        !SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_COLORSPACEPRIMARIES(surface->colorspace) == SDL_COLOR_PRIMARIES_BT709) {
        /* Fill the appropriate number of least-significant bytes of pixel,
         * leaving the most-significant bytes set to zero */
#اگر SDL_BYTEORDER == SDL_BIG_ENDIAN
        SDL_memcpy(((Uint8 *)&pixel) + (حجم(pixel) - بائٹیں_فی_pixel), p, بائٹیں_فی_pixel);
#ورنہ
        SDL_memcpy(&pixel, p, بائٹیں_فی_pixel);
#اگر_ختم
        SDL_GetRGBA(pixel, surface->fmt, surface->palette, r, g, b, a);
        نتیجہ = true;
    } ورنہ اگر (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // FIXME: We need code to extract a single macroblock from a YUV surface
        SDL_Surface *converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        اگر (converted) {
            نتیجہ = SDL_ReadSurfacePixel(converted, x, y, r, g, b, a);
            SDL_DestroySurface(converted);
        }
    } ورنہ {
        // This is really slow, but it gets the job done
        Uint8 rgba[4];

        اگر (SDL_ConvertPixelsAndColorspace(1, 1, surface->format, surface->colorspace, surface->props, p, surface->pitch, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, rgba, حجم(rgba))) {
            *r = rgba[0];
            *g = rgba[1];
            *b = rgba[2];
            *a = rgba[3];
            نتیجہ = true;
        }
    }

    اگر (SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }
    واپس نتیجہ;
}

bool SDL_ReadSurfacePixelFloat(SDL_Surface *surface, صحیح x, صحیح y, اعشاری *r, اعشاری *g, اعشاری *b, اعشاری *a)
{
    اعشاری غیر_مستعمل;
    bool نتیجہ = false;

    اگر (r) {
        *r = 0.0f;
    } ورنہ {
        r = &غیر_مستعمل;
    }

    اگر (g) {
        *g = 0.0f;
    } ورنہ {
        g = &غیر_مستعمل;
    }

    اگر (b) {
        *b = 0.0f;
    } ورنہ {
        b = &غیر_مستعمل;
    }

    اگر (a) {
        *a = 0.0f;
    } ورنہ {
        a = &غیر_مستعمل;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        واپس SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        واپس SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        واپس SDL_InvalidParamError("y");
    }

    اگر (SDL_BYTESPERPIXEL(surface->format) <= حجم(Uint32) &&
        !SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_COLORSPACEPRIMARIES(surface->colorspace) == SDL_COLOR_PRIMARIES_BT709) {
        Uint8 r8, g8, b8, a8;

        اگر (SDL_ReadSurfacePixel(surface, x, y, &r8, &g8, &b8, &a8)) {
            *r = (اعشاری)r8 / 255.0f;
            *g = (اعشاری)g8 / 255.0f;
            *b = (اعشاری)b8 / 255.0f;
            *a = (اعشاری)a8 / 255.0f;
            نتیجہ = true;
        }
    } ورنہ اگر (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // FIXME: We need code to extract a single macroblock from a YUV surface
        SDL_Surface *converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        اگر (converted) {
            نتیجہ = SDL_ReadSurfacePixelFloat(converted, x, y, r, g, b, a);
            SDL_DestroySurface(converted);
        }
    } ورنہ {
        // This is really slow, but it gets the job done
        اعشاری rgba[4];
        Uint8 *p;

        اگر (SDL_MUSTLOCK(surface)) {
            اگر (!SDL_تالا_Surface(surface)) {
                واپس false;
            }
        }

        p = (Uint8 *)surface->pixels + y * surface->pitch + x * SDL_BYTESPERPIXEL(surface->format);

        اگر (surface->format == SDL_PIXELFORMAT_RGBA128_FLOAT) {
            SDL_memcpy(rgba, p, حجم(rgba));
            نتیجہ = true;
        } ورنہ {
            SDL_Colorspace src_colorspace = surface->colorspace;
            SDL_Colorspace dst_colorspace = (src_colorspace == SDL_COLORSPACE_SRGB_خطی ? SDL_COLORSPACE_SRGB_خطی : SDL_COLORSPACE_SRGB);

            اگر (SDL_ConvertPixelsAndColorspace(1, 1, surface->format, src_colorspace, surface->props, p, surface->pitch, SDL_PIXELFORMAT_RGBA128_FLOAT, dst_colorspace, 0, rgba, حجم(rgba))) {
                نتیجہ = true;
            }
        }

        اگر (نتیجہ) {
            *r = rgba[0];
            *g = rgba[1];
            *b = rgba[2];
            *a = rgba[3];
        }

        اگر (SDL_MUSTLOCK(surface)) {
            SDL_UnlockSurface(surface);
        }
    }
    واپس نتیجہ;
}

bool SDL_WriteSurfacePixel(SDL_Surface *surface, صحیح x, صحیح y, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    Uint32 pixel = 0;
    size_t بائٹیں_فی_pixel;
    Uint8 *p;
    bool نتیجہ = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        واپس SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        واپس SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        واپس SDL_InvalidParamError("y");
    }

    بائٹیں_فی_pixel = SDL_BYTESPERPIXEL(surface->format);

    اگر (SDL_MUSTLOCK(surface)) {
        اگر (!SDL_تالا_Surface(surface)) {
            واپس false;
        }
    }

    p = (Uint8 *)surface->pixels + y * surface->pitch + x * بائٹیں_فی_pixel;

    اگر (بائٹیں_فی_pixel <= حجم(pixel) && !SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        pixel = SDL_MapRGBA(surface->fmt, surface->palette, r, g, b, a);
#اگر SDL_BYTEORDER == SDL_BIG_ENDIAN
        SDL_memcpy(p, ((Uint8 *)&pixel) + (حجم(pixel) - بائٹیں_فی_pixel), بائٹیں_فی_pixel);
#ورنہ
        SDL_memcpy(p, &pixel, بائٹیں_فی_pixel);
#اگر_ختم
        نتیجہ = true;
    } ورنہ اگر (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        نتیجہ = SDL_Unsupported();
    } ورنہ {
        // This is really slow, but it gets the job done
        Uint8 rgba[4];

        rgba[0] = r;
        rgba[1] = g;
        rgba[2] = b;
        rgba[3] = a;
        نتیجہ = SDL_ConvertPixelsAndColorspace(1, 1, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, rgba, حجم(rgba), surface->format, surface->colorspace, surface->props, p, surface->pitch);
    }

    اگر (SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }
    واپس نتیجہ;
}

bool SDL_WriteSurfacePixelFloat(SDL_Surface *surface, صحیح x, صحیح y, اعشاری r, اعشاری g, اعشاری b, اعشاری a)
{
    bool نتیجہ = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        واپس SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        واپس SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        واپس SDL_InvalidParamError("y");
    }

    اگر (SDL_BYTESPERPIXEL(surface->format) <= حجم(Uint32) && !SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        Uint8 r8, g8, b8, a8;

        r8 = (Uint8)SDL_باری(SDL_clamp(r, 0.0f, 1.0f) * 255.0f);
        g8 = (Uint8)SDL_باری(SDL_clamp(g, 0.0f, 1.0f) * 255.0f);
        b8 = (Uint8)SDL_باری(SDL_clamp(b, 0.0f, 1.0f) * 255.0f);
        a8 = (Uint8)SDL_باری(SDL_clamp(a, 0.0f, 1.0f) * 255.0f);
        اگر (SDL_WriteSurfacePixel(surface, x, y, r8, g8, b8, a8)) {
            نتیجہ = true;
        }
    } ورنہ اگر (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        نتیجہ = SDL_Unsupported();
    } ورنہ {
        // This is really slow, but it gets the job done
        اعشاری rgba[4];
        Uint8 *p;

        اگر (SDL_MUSTLOCK(surface)) {
            اگر (!SDL_تالا_Surface(surface)) {
                واپس false;
            }
        }

        p = (Uint8 *)surface->pixels + y * surface->pitch + x * SDL_BYTESPERPIXEL(surface->format);

        rgba[0] = r;
        rgba[1] = g;
        rgba[2] = b;
        rgba[3] = a;

        اگر (surface->format == SDL_PIXELFORMAT_RGBA128_FLOAT) {
            SDL_memcpy(p, rgba, حجم(rgba));
            نتیجہ = true;
        } ورنہ {
            SDL_Colorspace dst_colorspace = surface->colorspace;
            SDL_Colorspace src_colorspace = (dst_colorspace == SDL_COLORSPACE_SRGB_خطی ? SDL_COLORSPACE_SRGB_خطی : SDL_COLORSPACE_SRGB);

            نتیجہ = SDL_ConvertPixelsAndColorspace(1, 1, SDL_PIXELFORMAT_RGBA128_FLOAT, src_colorspace, 0, rgba, حجم(rgba), surface->format, dst_colorspace, surface->props, p, surface->pitch);
        }

        اگر (SDL_MUSTLOCK(surface)) {
            SDL_UnlockSurface(surface);
        }
    }
    واپس نتیجہ;
}

/*
 * Free a surface created by the above function.
 */
خالی SDL_DestroySurface(SDL_Surface *surface)
{
    اگر (!SDL_SurfaceValid(surface)) {
        واپس;
    }
    اگر (surface->اندرونی_flags & SDL_اندرونی_SURFACE_DONTFREE) {
        واپس;
    }
    اگر (--surface->refcount > 0) {
        واپس;
    }

    SDL_RemoveSurfaceAlternateImages(surface);

    SDL_DestroyProperties(surface->props);

    SDL_InvalidateMap(&surface->map);

    جب (surface->locked > 0) {
        SDL_UnlockSurface(surface);
    }
#اگر_تعریف_شدہ SDL_HAVE_RLE
    اگر (surface->اندرونی_flags & SDL_اندرونی_SURFACE_RLEACCEL) {
        SDL_UnRLESurface(surface);
    }
#اگر_ختم
    SDL_سیٹ_Surface_Palette(surface, تہی);

    اگر (surface->flags & SDL_SURFACE_PREALLOCATED) {
        // Don't free
    } ورنہ اگر (surface->flags & SDL_SURFACE_SIMD_ALIGNED) {
        // Free aligned
        SDL_aligned_free(surface->pixels);
    } ورنہ {
        // Normal
        SDL_free(surface->pixels);
    }

    surface->reserved = تہی;

    اگر (!(surface->اندرونی_flags & SDL_اندرونی_SURFACE_ڈھیر)) {
        SDL_free(surface);
    }
}

SDL_Surface *SDL_بھرو_Surface_IO(SDL_IOStream *src, bool closeio)
{
    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        واپس تہی;
    }

    اگر (SDL_IsBMP(src)) {
        واپس SDL_بھرو_BMP_IO(src, closeio);
    } ورنہ اگر (SDL_IsPNG(src)) {
        واپس SDL_بھرو_PNG_IO(src, closeio);
    } ورنہ اگر (SDL_IsJPG(src)) {
        واپس SDL_بھرو_JPG_IO(src, closeio);
    } ورنہ {
        اگر (closeio) {
            SDL_CloseIO(src);
        }
        SDL_سیٹ_Error("Unsupported image format");
        واپس تہی;
    }
}

SDL_Surface *SDL_بھرو_Surface(ثابت حرف *file)
{
    SDL_IOStream *دھارا = SDL_IOFromFile(file, "rb");
    اگر (!دھارا) {
        واپس تہی;
    }

    واپس SDL_بھرو_Surface_IO(دھارا, true);
}
