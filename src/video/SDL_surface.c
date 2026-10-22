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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_sysvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_video_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_RLEaccel_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_pixels_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_rotate.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_stb_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_yuv_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../render/SDL_sysrender.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_surface_c.h"


// Check to make sure we can safely check multiplication of surface w and pitch and it won't overflow size_t
SDL_COMPILE_ਸਮਾਂ_ASSERT(surface_ਮਾਪ_assumptions,
                        ਆਕਾਰ(ਪੂਰਨ) == ਆਕਾਰ(Sint32) && ਆਕਾਰ(size_t) >= ਆਕਾਰ(Sint32));

SDL_COMPILE_ਸਮਾਂ_ASSERT(can_indicate_ਉਛਾਲ, SDL_ਮਾਪ_MAX > SDL_MAX_SINT32);

// Magic!
ਸਥਿਰ ਅੱਖਰ SDL_surface_magic;

// Public routines

bool SDL_SurfaceValid(SDL_Surface *surface)
{
    ਵਾਪਸ (surface && surface->reserved == &SDL_surface_magic);
}

ਖਾਲੀ SDL_Update_Surface_ਤਾਲਾ_Flag(SDL_Surface *surface)
{
    // We need to mark the surface as needing unlock while locked
    ਜੇ ((surface->flags & SDL_SURFACE_LOCKED) ||
        (surface->ਅੰਦਰੂਨੀ_flags & SDL_ਅੰਦਰੂਨੀ_SURFACE_RLEACCEL)) {
        surface->flags |= SDL_SURFACE_ਤਾਲਾ_NEEDED;
    } ਨਹੀਂਤਾਂ {
        surface->flags &= ~SDL_SURFACE_ਤਾਲਾ_NEEDED;
    }
}

/*
 * Calculate the pad-aligned scanline width of a surface.
 *
 * for FOURCC, use SDL_CalculateYUVSize()
 */
ਸਥਿਰ bool SDL_CalculateRGBSize(Uint32 format, size_t ਚੌੜਾਈ, size_t ਉਚਾਈ, size_t *ਮਾਪ, size_t *pitch, bool ਨਿਊਨਤਮ)
{
    ਜੇ (SDL_BITSPERPIXEL(format) >= 8) {
        ਜੇ (!SDL_ਮਾਪ_mul_check_ਉਛਾਲ(ਚੌੜਾਈ, SDL_BYTESPERPIXEL(format), pitch)) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("width * bpp would overflow");
        }
    } ਨਹੀਂਤਾਂ {
        ਜੇ (!SDL_ਮਾਪ_mul_check_ਉਛਾਲ(ਚੌੜਾਈ, SDL_BITSPERPIXEL(format), pitch)) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("width * bpp would overflow");
        }
        ਜੇ (!SDL_ਮਾਪ_ਜੋੜੋ_check_ਉਛਾਲ(*pitch, 7, pitch)) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("aligning pitch would overflow");
        }
        *pitch /= 8;
    }
    ਜੇ (!ਨਿਊਨਤਮ) {
        // 4-byte aligning for speed
        ਜੇ (!SDL_ਮਾਪ_ਜੋੜੋ_check_ਉਛਾਲ(*pitch, 3, pitch)) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("aligning pitch would overflow");
        }
        *pitch &= ~3;
    }

    ਜੇ (!SDL_ਮਾਪ_mul_check_ਉਛਾਲ(ਉਚਾਈ, *pitch, ਮਾਪ)) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("height * pitch would overflow");
    }

    ਵਾਪਸ true;
}

bool SDL_Calculate_Surface_ਮਾਪ(SDL_PixelFormat format, ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, size_t *ਮਾਪ, size_t *pitch, bool ਨਿਊਨਤਮ_Pitch)
{
    size_t p = 0, sz = 0;

    ਜੇ (ਮਾਪ) {
        *ਮਾਪ = 0;
    }

    ਜੇ (pitch) {
        *pitch = 0;
    }

    ਜੇ (SDL_ISPIXELFORMAT_FOURCC(format)) {
        ਜੇ (format == SDL_PIXELFORMAT_MJPG) {
            // We don't know in advance what it will be, we'll figure it out later.
            ਵਾਪਸ true;
        }

        ਜੇ (!SDL_CalculateYUVSize(format, ਚੌੜਾਈ, ਉਚਾਈ, &sz, &p)) {
            // Overflow...
            ਵਾਪਸ false;
        }
    } ਨਹੀਂਤਾਂ {
        ਜੇ (!SDL_CalculateRGBSize(format, ਚੌੜਾਈ, ਉਚਾਈ, &sz, &p, ਨਿਊਨਤਮ_Pitch)) {
            // Overflow...
            ਵਾਪਸ false;
        }
    }

    ਜੇ (ਮਾਪ) {
        *ਮਾਪ = sz;
    }

    ਜੇ (pitch) {
        *pitch = p;
    }

    ਵਾਪਸ true;
}

ਸਥਿਰ bool SDL_InitializeSurface(SDL_Surface *surface, ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, SDL_PixelFormat format, SDL_Colorspace colorspace, SDL_PropertiesID props, ਖਾਲੀ *pixels, ਪੂਰਨ pitch, bool onstack)
{
    SDL_zerop(surface);

    surface->flags = SDL_SURFACE_PREALLOCATED;
    surface->format = format;
    surface->w = ਚੌੜਾਈ;
    surface->h = ਉਚਾਈ;
    surface->pixels = pixels;
    surface->pitch = pitch;
    surface->reserved = &SDL_surface_magic;

    ਜੇ (onstack) {
        surface->ਅੰਦਰੂਨੀ_flags |= SDL_ਅੰਦਰੂਨੀ_SURFACE_ਢੇਰ;
    }

    surface->fmt = SDL_GetPixelFormatDetails(format);
    ਜੇ (!surface->fmt) {
        SDL_DestroySurface(surface);
        ਵਾਪਸ false;
    }

    // Initialize the clip rect
    surface->clip_rect.w = ਚੌੜਾਈ;
    surface->clip_rect.h = ਉਚਾਈ;

    // Allocate an empty mapping
    surface->map.info.r = 0xFF;
    surface->map.info.g = 0xFF;
    surface->map.info.b = 0xFF;
    surface->map.info.a = 0xFF;

    ਜੇ (colorspace == SDL_COLORSPACE_UNKNOWN) {
        surface->colorspace = SDL_GetDefaultColorspaceForFormat(format);
    } ਨਹੀਂਤਾਂ {
        surface->colorspace = colorspace;
    }

    ਜੇ (props) {
        ਜੇ (!SDL_CopyProperties(props, SDL_GetSurfaceProperties(surface))) {
            SDL_DestroySurface(surface);
            ਵਾਪਸ false;
        }
    }

    // By default surfaces with an alpha mask are set up for blending
    ਜੇ (SDL_ISPIXELFORMAT_ALPHA(surface->format)) {
        SDL_ਸੈੱਟ_Surface_Blend_ਬਹੁਲਕ(surface, SDL_BLENDMODE_BLEND);
    }

    // The surface is ready to go
    surface->refcount = 1;
    ਵਾਪਸ true;
}

/*
 * Create an empty surface of the appropriate depth using the given format
 */
ਸਥਿਰ SDL_Surface *SDL_Create_Surface_ਅੰਦਰੂਨੀ(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, SDL_PixelFormat format, bool clear_surface)
{
    size_t pitch, ਮਾਪ;
    SDL_Surface *surface;

    CHECK_PARAM(ਚੌੜਾਈ < 0) {
        SDL_InvalidParamError("width");
        ਵਾਪਸ ਨਿਰਾ;
    }

    CHECK_PARAM(ਉਚਾਈ < 0) {
        SDL_InvalidParamError("height");
        ਵਾਪਸ ਨਿਰਾ;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਜੇ (!SDL_Calculate_Surface_ਮਾਪ(format, ਚੌੜਾਈ, ਉਚਾਈ, &ਮਾਪ, &pitch, false /* not minimal pitch */)) {
        // Overflow...
        ਵਾਪਸ ਨਿਰਾ;
    }

    // Allocate and initialize the surface
    surface = (SDL_Surface *)SDL_malloc(ਆਕਾਰ(*surface));
    ਜੇ (!surface) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਜੇ (!SDL_InitializeSurface(surface, ਚੌੜਾਈ, ਉਚਾਈ, format, SDL_COLORSPACE_UNKNOWN, 0, ਨਿਰਾ, (ਪੂਰਨ)pitch, false)) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਜੇ (surface->w && surface->h && format != SDL_PIXELFORMAT_MJPG) {
        surface->flags &= ~SDL_SURFACE_PREALLOCATED;
        ਜੇ (SDL_GetHintBoolean("SDL_SURFACE_MALLOC", false)) {
            ਜੇ (clear_surface) {
                surface->pixels = SDL_calloc(1, ਮਾਪ);
            } ਨਹੀਂਤਾਂ {
                surface->pixels = SDL_malloc(ਮਾਪ);
            }
        } ਨਹੀਂਤਾਂ {
            surface->flags |= SDL_SURFACE_SIMD_ALIGNED;
            ਜੇ (clear_surface) {
                surface->pixels = SDL_aligned_alloc_zero(SDL_GetSIMDAlignment(), ਮਾਪ);
            } ਨਹੀਂਤਾਂ {
                surface->pixels = SDL_aligned_alloc(SDL_GetSIMDAlignment(), ਮਾਪ);
            }
        }
        ਜੇ (!surface->pixels) {
            SDL_DestroySurface(surface);
            ਵਾਪਸ ਨਿਰਾ;
        }
    }
    ਵਾਪਸ surface;
}

SDL_Surface *SDL_CreateSurfaceZeroed(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, SDL_PixelFormat format)
{
    ਵਾਪਸ SDL_Create_Surface_ਅੰਦਰੂਨੀ(ਚੌੜਾਈ, ਉਚਾਈ, format, true);
}

SDL_Surface *SDL_CreateSurfaceUninitialized(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, SDL_PixelFormat format)
{
    ਵਾਪਸ SDL_Create_Surface_ਅੰਦਰੂਨੀ(ਚੌੜਾਈ, ਉਚਾਈ, format, false);
}

SDL_Surface *SDL_CreateSurface(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, SDL_PixelFormat format)
{
    ਵਾਪਸ SDL_CreateSurfaceZeroed(ਚੌੜਾਈ, ਉਚਾਈ, format);
}


/*
 * Create an RGB surface from an existing memory buffer using the given
 * enum SDL_PIXELFORMAT_* format
 */
SDL_Surface *SDL_CreateSurfaceFrom(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, SDL_PixelFormat format, ਖਾਲੀ *pixels, ਪੂਰਨ pitch)
{
    CHECK_PARAM(ਚੌੜਾਈ < 0) {
        SDL_InvalidParamError("width");
        ਵਾਪਸ ਨਿਰਾ;
    }

    CHECK_PARAM(ਉਚਾਈ < 0) {
        SDL_InvalidParamError("height");
        ਵਾਪਸ ਨਿਰਾ;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਜੇ (pitch == 0 && !pixels) {
        // The application will fill these in later with valid values
    } ਨਹੀਂਤਾਂ {
        size_t ਨਿਊਨਤਮ_Pitch;

        ਜੇ (!SDL_Calculate_Surface_ਮਾਪ(format, ਚੌੜਾਈ, ਉਚਾਈ, ਨਿਰਾ, &ਨਿਊਨਤਮ_Pitch, true /* minimal pitch */)) {
            // Overflow...
            ਵਾਪਸ ਨਿਰਾ;
        }

        CHECK_PARAM(pitch < 0 || (size_t)pitch < ਨਿਊਨਤਮ_Pitch) {
            SDL_InvalidParamError("pitch");
            ਵਾਪਸ ਨਿਰਾ;
        }
    }

    // Allocate and initialize the surface
    SDL_Surface *surface = (SDL_Surface *)SDL_malloc(ਆਕਾਰ(*surface));
    ਜੇ (!surface ||
        !SDL_InitializeSurface(surface, ਚੌੜਾਈ, ਉਚਾਈ, format, SDL_COLORSPACE_UNKNOWN, 0, pixels, pitch, false)) {
        ਵਾਪਸ ਨਿਰਾ;
    }
    ਵਾਪਸ surface;
}

SDL_PropertiesID SDL_GetSurfaceProperties(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        ਵਾਪਸ 0;
    }

    ਜੇ (!surface->props) {
        surface->props = SDL_CreateProperties();
    }
    ਵਾਪਸ surface->props;
}

bool SDL_ਸੈੱਟ_Surface_Colorspace(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ਵਾਪਸ SDL_InvalidParamError("surface");
    }

    surface->colorspace = colorspace;
    ਵਾਪਸ true;
}

SDL_Colorspace SDL_GetSurfaceColorspace(SDL_Surface *surface)
{
    ਜੇ (!SDL_SurfaceValid(surface)) {
        ਵਾਪਸ SDL_COLORSPACE_UNKNOWN;
    }

    ਵਾਪਸ surface->colorspace;
}

ਦਸ਼ਮਲਵ SDL_Get_Default_SDRWhite_ਬਿੰਦੂ(SDL_Colorspace colorspace)
{
    ਵਾਪਸ SDL_Get_Surface_SDRWhite_ਬਿੰਦੂ(ਨਿਰਾ, colorspace);
}

ਦਸ਼ਮਲਵ SDL_Get_Surface_SDRWhite_ਬਿੰਦੂ(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    SDL_TransferCharacteristics transfer = SDL_COLORSPACETRANSFER(colorspace);

    ਜੇ (transfer == SDL_TRANSFER_CHARACTERISTICS_ਰੇਖਿਕ ||
        transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
        SDL_PropertiesID props;
        ਦਸ਼ਮਲਵ default_ਮੁੱਲ = 1.0f;

        ਜੇ (SDL_SurfaceValid(surface)) {
            props = surface->props;
        } ਨਹੀਂਤਾਂ {
            props = 0;
        }
        ਜੇ (transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
            /* The older standards use an SDR white point of 100 nits.
             * ITU-R BT.2408-6 recommends using an SDR white point of 203 nits.
             * This is the default Chrome uses, and what a lot of game content
             * assumes, so we'll go with that.
             */
            ਅਚਲ ਦਸ਼ਮਲਵ DEFAULT_PQ_SDR_WHITE_ਬਿੰਦੂ = 203.0f;
            default_ਮੁੱਲ = DEFAULT_PQ_SDR_WHITE_ਬਿੰਦੂ;
        }
        ਵਾਪਸ SDL_GetFloatProperty(props, SDL_PROP_SURFACE_SDR_WHITE_ਬਿੰਦੂ_FLOAT, default_ਮੁੱਲ);
    }
    ਵਾਪਸ 1.0f;
}

ਦਸ਼ਮਲਵ SDL_GetDefaultHDRHeadroom(SDL_Colorspace colorspace)
{
    ਵਾਪਸ SDL_GetSurfaceHDRHeadroom(ਨਿਰਾ, colorspace);
}

ਦਸ਼ਮਲਵ SDL_GetSurfaceHDRHeadroom(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    SDL_TransferCharacteristics transfer = SDL_COLORSPACETRANSFER(colorspace);

    ਜੇ (transfer == SDL_TRANSFER_CHARACTERISTICS_ਰੇਖਿਕ ||
        transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
        SDL_PropertiesID props;
        ਦਸ਼ਮਲਵ default_ਮੁੱਲ = 0.0f;

        ਜੇ (SDL_SurfaceValid(surface)) {
            props = surface->props;
        } ਨਹੀਂਤਾਂ {
            props = 0;
        }
        ਵਾਪਸ SDL_GetFloatProperty(props, SDL_PROP_SURFACE_HDR_HEADROOM_FLOAT, default_ਮੁੱਲ);
    }
    ਵਾਪਸ 1.0f;
}

SDL_Palette *SDL_CreateSurfacePalette(SDL_Surface *surface)
{
    SDL_Palette *palette;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        ਵਾਪਸ ਨਿਰਾ;
    }

    CHECK_PARAM(!SDL_ISPIXELFORMAT_ਸੂਚਕਾਂਕਿਤ(surface->format)) {
        SDL_ਸੈੱਟ_Error("The surface is not indexed format");
        ਵਾਪਸ ਨਿਰਾ;
    }

    palette = SDL_CreatePalette((1 << SDL_BITSPERPIXEL(surface->format)));
    ਜੇ (!palette) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਜੇ (palette->ncolors == 2) {
        // Create a black and white bitmap palette
        palette->colors[0].r = 0xFF;
        palette->colors[0].g = 0xFF;
        palette->colors[0].b = 0xFF;
        palette->colors[1].r = 0x00;
        palette->colors[1].g = 0x00;
        palette->colors[1].b = 0x00;
    }

    ਜੇ (!SDL_ਸੈੱਟ_Surface_Palette(surface, palette)) {
        SDL_DestroyPalette(palette);
        ਵਾਪਸ ਨਿਰਾ;
    }

    // The surface has retained the palette, we can remove the reference here
    SDL_assert(palette->refcount == 2);
    SDL_DestroyPalette(palette);
    ਵਾਪਸ palette;
}

bool SDL_ਸੈੱਟ_Surface_Palette(SDL_Surface *surface, SDL_Palette *palette)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ਵਾਪਸ SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(palette && !SDL_ISPIXELFORMAT_ਸੂਚਕਾਂਕਿਤ(surface->format)) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Surface doesn't use a palette");
    }

    CHECK_PARAM(palette && palette->ncolors > (1 << SDL_BITSPERPIXEL(surface->format))) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Palette doesn't match surface format");
    }

    ਜੇ (palette != surface->palette) {
        ਜੇ (surface->palette) {
            SDL_DestroyPalette(surface->palette);
        }

        surface->palette = palette;

        ਜੇ (surface->palette) {
            ++surface->palette->refcount;
        }
    }

    SDL_InvalidateMap(&surface->map);

    ਵਾਪਸ true;
}

SDL_Palette *SDL_GetSurfacePalette(SDL_Surface *surface)
{
    ਜੇ (!SDL_SurfaceValid(surface)) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਵਾਪਸ surface->palette;
}

bool SDL_ਜੋੜੋ_Surface_Alternate_Image(SDL_Surface *surface, SDL_Surface *image)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ਵਾਪਸ SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(!SDL_SurfaceValid(image)) {
        ਵਾਪਸ SDL_InvalidParamError("image");
    }

    SDL_Surface **images = (SDL_Surface **)SDL_realloc(surface->images, (surface->ਅੰਕ_images + 1) * ਆਕਾਰ(*images));
    ਜੇ (!images) {
        ਵਾਪਸ false;
    }
    images[surface->ਅੰਕ_images] = image;
    surface->images = images;
    ++surface->ਅੰਕ_images;
    ++image->refcount;
    ਵਾਪਸ true;
}

bool SDL_SurfaceHasAlternateImages(SDL_Surface *surface)
{
    ਜੇ (!SDL_SurfaceValid(surface)) {
        ਵਾਪਸ false;
    }

    ਵਾਪਸ (surface->ਅੰਕ_images > 0);
}

SDL_Surface **SDL_GetSurfaceImages(SDL_Surface *surface, ਪੂਰਨ *ਗਿਣਤੀ_2)
{
    ਜੇ (ਗਿਣਤੀ_2) {
        *ਗਿਣਤੀ_2 = 0;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਪੂਰਨ ਅੰਕ_images = 1 + surface->ਅੰਕ_images;
    SDL_Surface **images = (SDL_Surface **)SDL_malloc((ਅੰਕ_images + 1) * ਆਕਾਰ(*images));
    ਜੇ (!images) {
        ਵਾਪਸ ਨਿਰਾ;
    }
    images[0] = surface;
    ਜੇ (surface->ਅੰਕ_images > 0) {
        SDL_memcpy(&images[1], surface->images, (surface->ਅੰਕ_images * ਆਕਾਰ(images[1])));
    }
    images[ਅੰਕ_images] = ਨਿਰਾ;

    ਜੇ (ਗਿਣਤੀ_2) {
        *ਗਿਣਤੀ_2 = ਅੰਕ_images;
    }
    ਵਾਪਸ images;
}

SDL_Surface *SDL_GetSurfaceImage(SDL_Surface *surface, ਦਸ਼ਮਲਵ display_scale)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਜੇ (!SDL_SurfaceHasAlternateImages(surface)) {
        ++surface->refcount;
        ਵਾਪਸ surface;
    }

    // This surface has high DPI images, pick the best one available, or scale one to the correct size
    SDL_Surface **images = SDL_GetSurfaceImages(surface, ਨਿਰਾ);
    ਜੇ (!images) {
        // Failure, fall back to the existing surface
        ++surface->refcount;
        ਵਾਪਸ surface;
    }

    // Find closest image. Images that are larger than the
    // desired size are preferred over images that are smaller.
    SDL_Surface *closest = ਨਿਰਾ;
    ਪੂਰਨ desired_w = (ਪੂਰਨ)SDL_ਗੇੜਾ(surface->w * display_scale);
    ਪੂਰਨ desired_h = (ਪੂਰਨ)SDL_ਗੇੜਾ(surface->h * display_scale);
    ਪੂਰਨ desired_ਮਾਪ = desired_w * desired_h;
    ਪੂਰਨ closest_ਦੂਰੀ = -1;
    ਪੂਰਨ closest_ਮਾਪ = -1;
    ਲਈ (ਪੂਰਨ i = 0; images[i]; ++i) {
        SDL_Surface *candidate = images[i];
        ਪੂਰਨ ਮਾਪ = candidate->w * candidate->h;
        ਪੂਰਨ delta_w = (candidate->w - desired_w);
        ਪੂਰਨ delta_h = (candidate->h - desired_h);
        ਪੂਰਨ ਦੂਰੀ = (delta_w * delta_w) + (delta_h * delta_h);
        ਜੇ (closest_ਦੂਰੀ < 0 || ਦੂਰੀ < closest_ਦੂਰੀ ||
            (ਮਾਪ > desired_ਮਾਪ && closest_ਮਾਪ < desired_ਮਾਪ)) {
            closest = candidate;
            closest_ਦੂਰੀ = ਦੂਰੀ;
            closest_ਮਾਪ = ਮਾਪ;
        }
    }
    SDL_free(images);
    SDL_assert(closest != ਨਿਰਾ);    // We should always have at least one surface

    ਜੇ (closest->w == desired_w && closest->h == desired_h) {
        ++closest->refcount;
        ਵਾਪਸ closest;
    }

    // We need to scale the image to the correct size. To maintain good image quality, downscaling
    // is done in steps, never reducing the width and height by more than half each time.
    SDL_Surface *scaled = closest;
    ਕਰੋ {
        ਪੂਰਨ ਅਗਲਾ_scaled_w = SDL_max(desired_w, (scaled->w + 1) / 2);
        ਪੂਰਨ ਅਗਲਾ_scaled_h = SDL_max(desired_h, (scaled->h + 1) / 2);
        SDL_Surface *ਅਗਲਾ_scaled = SDL_ScaleSurface(scaled, ਅਗਲਾ_scaled_w, ਅਗਲਾ_scaled_h, SDL_SCALEMODE_ਰੇਖਿਕ);
        ਜੇ (scaled != closest) {
            SDL_DestroySurface(scaled);
        }
        scaled = ਅਗਲਾ_scaled;
        ਜੇ (!scaled) {
            // Failure, fall back to the closest surface
            ++closest->refcount;
            ਵਾਪਸ closest;
        }
    } ਜਦੋਂ (scaled->w != desired_w || scaled->h != desired_h);

    ਵਾਪਸ scaled;
}

ਖਾਲੀ SDL_RemoveSurfaceAlternateImages(SDL_Surface *surface)
{
    ਜੇ (!SDL_SurfaceValid(surface)) {
        ਵਾਪਸ;
    }

    ਜੇ (surface->ਅੰਕ_images > 0) {
        ਲਈ (ਪੂਰਨ i = 0; i < surface->ਅੰਕ_images; ++i) {
            SDL_DestroySurface(surface->images[i]);
        }
        SDL_free(surface->images);
        surface->images = ਨਿਰਾ;
        surface->ਅੰਕ_images = 0;
    }
}

bool SDL_ਸੈੱਟ_Surface_RLE(SDL_Surface *surface, bool enabled)
{
    ਪੂਰਨ flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        ਵਾਪਸ SDL_InvalidParamError("surface");
    }

    flags = surface->map.info.flags;
    ਜੇ (enabled) {
        surface->map.info.flags |= SDL_COPY_RLE_DESIRED;
    } ਨਹੀਂਤਾਂ {
        surface->map.info.flags &= ~SDL_COPY_RLE_DESIRED;
    }
    ਜੇ (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    ਵਾਪਸ true;
}

bool SDL_SurfaceHasRLE(SDL_Surface *surface)
{
    ਜੇ (!SDL_SurfaceValid(surface)) {
        ਵਾਪਸ false;
    }

    ਜੇ (!(surface->map.info.flags & SDL_COPY_RLE_DESIRED)) {
        ਵਾਪਸ false;
    }

    ਵਾਪਸ true;
}

bool SDL_ਸੈੱਟ_Surface_Color_ਕੁੰਜੀ(SDL_Surface *surface, bool enabled, Uint32 ਕੁੰਜੀ)
{
    ਪੂਰਨ flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ਵਾਪਸ SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(surface->palette && ਕੁੰਜੀ >= ((Uint32)surface->palette->ncolors)) {
        ਵਾਪਸ SDL_InvalidParamError("key");
    }

    flags = surface->map.info.flags;
    ਜੇ (enabled) {
        surface->map.info.flags |= SDL_COPY_COLORKEY;
        surface->map.info.colorkey = ਕੁੰਜੀ;
    } ਨਹੀਂਤਾਂ {
        surface->map.info.flags &= ~SDL_COPY_COLORKEY;
    }
    ਜੇ (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }

    ਵਾਪਸ true;
}

bool SDL_Surface_Has_Color_ਕੁੰਜੀ(SDL_Surface *surface)
{
    ਜੇ (!SDL_SurfaceValid(surface)) {
        ਵਾਪਸ false;
    }

    ਜੇ (!(surface->map.info.flags & SDL_COPY_COLORKEY)) {
        ਵਾਪਸ false;
    }

    ਵਾਪਸ true;
}

bool SDL_Get_Surface_Color_ਕੁੰਜੀ(SDL_Surface *surface, Uint32 *ਕੁੰਜੀ)
{
    ਜੇ (ਕੁੰਜੀ) {
        *ਕੁੰਜੀ = 0;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ਵਾਪਸ SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(!(surface->map.info.flags & SDL_COPY_COLORKEY)) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Surface doesn't have a colorkey");
    }

    ਜੇ (ਕੁੰਜੀ) {
        *ਕੁੰਜੀ = surface->map.info.colorkey;
    }
    ਵਾਪਸ true;
}

/* This is a fairly slow function to switch from colorkey to alpha
   NB: it doesn't handle bpp 1 or 3, because they have no alpha channel */
ਸਥਿਰ ਖਾਲੀ SDL_Convert_Colorkey_ਮੰਜ਼ਿਲ_Alpha(SDL_Surface *surface, bool ignore_alpha)
{
    ਪੂਰਨ x, y, bpp;

    ਜੇ (!SDL_SurfaceValid(surface)) {
        ਵਾਪਸ;
    }

    ਜੇ (!(surface->map.info.flags & SDL_COPY_COLORKEY) ||
        !SDL_ISPIXELFORMAT_ALPHA(surface->format)) {
        ਵਾਪਸ;
    }

    bpp = SDL_BYTESPERPIXEL(surface->format);

    SDL_ਤਾਲਾ_Surface(surface);

    ਜੇ (bpp == 2) {
        Uint16 *ਪੰਕਤੀ, *spot;
        Uint16 ckey = (Uint16)surface->map.info.colorkey;
        Uint16 ਨਕਾਬ = (Uint16)(~surface->fmt->Amask);

        // Ignore, or not, alpha in colorkey comparison
        ਜੇ (ignore_alpha) {
            ckey &= ਨਕਾਬ;
            ਪੰਕਤੀ = (Uint16 *)surface->pixels;
            ਲਈ (y = surface->h; y--;) {
                spot = ਪੰਕਤੀ;
                ਲਈ (x = surface->w; x--;) {
                    ਜੇ ((*spot & ਨਕਾਬ) == ckey) {
                        *spot &= ਨਕਾਬ;
                    }
                    ++spot;
                }
                ਪੰਕਤੀ += surface->pitch / 2;
            }
        } ਨਹੀਂਤਾਂ {
            ਪੰਕਤੀ = (Uint16 *)surface->pixels;
            ਲਈ (y = surface->h; y--;) {
                spot = ਪੰਕਤੀ;
                ਲਈ (x = surface->w; x--;) {
                    ਜੇ (*spot == ckey) {
                        *spot &= ਨਕਾਬ;
                    }
                    ++spot;
                }
                ਪੰਕਤੀ += surface->pitch / 2;
            }
        }
    } ਨਹੀਂਤਾਂ ਜੇ (bpp == 4) {
        Uint32 *ਪੰਕਤੀ, *spot;
        Uint32 ckey = surface->map.info.colorkey;
        Uint32 ਨਕਾਬ = ~surface->fmt->Amask;

        // Ignore, or not, alpha in colorkey comparison
        ਜੇ (ignore_alpha) {
            ckey &= ਨਕਾਬ;
            ਪੰਕਤੀ = (Uint32 *)surface->pixels;
            ਲਈ (y = surface->h; y--;) {
                spot = ਪੰਕਤੀ;
                ਲਈ (x = surface->w; x--;) {
                    ਜੇ ((*spot & ਨਕਾਬ) == ckey) {
                        *spot &= ਨਕਾਬ;
                    }
                    ++spot;
                }
                ਪੰਕਤੀ += surface->pitch / 4;
            }
        } ਨਹੀਂਤਾਂ {
            ਪੰਕਤੀ = (Uint32 *)surface->pixels;
            ਲਈ (y = surface->h; y--;) {
                spot = ਪੰਕਤੀ;
                ਲਈ (x = surface->w; x--;) {
                    ਜੇ (*spot == ckey) {
                        *spot &= ਨਕਾਬ;
                    }
                    ++spot;
                }
                ਪੰਕਤੀ += surface->pitch / 4;
            }
        }
    }

    SDL_UnlockSurface(surface);

    SDL_ਸੈੱਟ_Surface_Color_ਕੁੰਜੀ(surface, false, 0);
    SDL_ਸੈੱਟ_Surface_Blend_ਬਹੁਲਕ(surface, SDL_BLENDMODE_BLEND);
}

bool SDL_ਸੈੱਟ_Surface_Color_Mod(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b)
{
    ਪੂਰਨ flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ਵਾਪਸ SDL_InvalidParamError("surface");
    }

    surface->map.info.r = r;
    surface->map.info.g = g;
    surface->map.info.b = b;

    flags = surface->map.info.flags;
    ਜੇ (r != 0xFF || g != 0xFF || b != 0xFF) {
        surface->map.info.flags |= SDL_COPY_MODULATE_COLOR;
    } ਨਹੀਂਤਾਂ {
        surface->map.info.flags &= ~SDL_COPY_MODULATE_COLOR;
    }
    ਜੇ (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    ਵਾਪਸ true;
}

bool SDL_GetSurfaceColorMod(SDL_Surface *surface, Uint8 *r, Uint8 *g, Uint8 *b)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ਜੇ (r) {
            *r = 255;
        }
        ਜੇ (g) {
            *g = 255;
        }
        ਜੇ (b) {
            *b = 255;
        }
        ਵਾਪਸ SDL_InvalidParamError("surface");
    }

    ਜੇ (r) {
        *r = surface->map.info.r;
    }
    ਜੇ (g) {
        *g = surface->map.info.g;
    }
    ਜੇ (b) {
        *b = surface->map.info.b;
    }
    ਵਾਪਸ true;
}

bool SDL_ਸੈੱਟ_Surface_Alpha_Mod(SDL_Surface *surface, Uint8 alpha)
{
    ਪੂਰਨ flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ਵਾਪਸ SDL_InvalidParamError("surface");
    }

    surface->map.info.a = alpha;

    flags = surface->map.info.flags;
    ਜੇ (alpha != 0xFF) {
        surface->map.info.flags |= SDL_COPY_MODULATE_ALPHA;
    } ਨਹੀਂਤਾਂ {
        surface->map.info.flags &= ~SDL_COPY_MODULATE_ALPHA;
    }
    ਜੇ (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    ਵਾਪਸ true;
}

bool SDL_GetSurfaceAlphaMod(SDL_Surface *surface, Uint8 *alpha)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ਜੇ (alpha) {
            *alpha = 255;
        }
        ਵਾਪਸ SDL_InvalidParamError("surface");
    }

    ਜੇ (alpha) {
        *alpha = surface->map.info.a;
    }
    ਵਾਪਸ true;
}

bool SDL_ਸੈੱਟ_Surface_Blend_ਬਹੁਲਕ(SDL_Surface *surface, SDL_Blend_ਬਹੁਲਕ blend_ਬਹੁਲਕ)
{
    ਪੂਰਨ flags;
    bool ਨਤੀਜਾ = true;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ਵਾਪਸ SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(blend_ਬਹੁਲਕ == SDL_BLENDMODE_INVALID) {
        ਵਾਪਸ SDL_InvalidParamError("blendMode");
    }

    flags = surface->map.info.flags;
    surface->map.info.flags &= ~SDL_COPY_BLEND_ਨਕਾਬ;
    ਚੋਣ (blend_ਬਹੁਲਕ) {
    ਹਾਲਤ SDL_BLENDMODE_NONE:
        ਰੋਕੋ;
    ਹਾਲਤ SDL_BLENDMODE_BLEND:
        surface->map.info.flags |= SDL_COPY_BLEND;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_BLENDMODE_BLEND_PREMULTIPLIED:
        surface->map.info.flags |= SDL_COPY_BLEND_PREMULTIPLIED;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_BLENDMODE_ਜੋੜੋ:
        surface->map.info.flags |= SDL_COPY_ਜੋੜੋ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_BLENDMODE_ਜੋੜੋ_PREMULTIPLIED:
        surface->map.info.flags |= SDL_COPY_ਜੋੜੋ_PREMULTIPLIED;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_BLENDMODE_MOD:
        surface->map.info.flags |= SDL_COPY_MOD;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_BLENDMODE_MUL:
        surface->map.info.flags |= SDL_COPY_MUL;
        ਰੋਕੋ;
    ਮੂਲ:
        ਨਤੀਜਾ = SDL_Unsupported();
        ਰੋਕੋ;
    }

    ਜੇ (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }

    ਵਾਪਸ ਨਤੀਜਾ;
}

bool SDL_Get_Surface_Blend_ਬਹੁਲਕ(SDL_Surface *surface, SDL_Blend_ਬਹੁਲਕ *blend_ਬਹੁਲਕ)
{
    ਜੇ (blend_ਬਹੁਲਕ) {
        *blend_ਬਹੁਲਕ = SDL_BLENDMODE_INVALID;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ਵਾਪਸ SDL_InvalidParamError("surface");
    }

    ਜੇ (!blend_ਬਹੁਲਕ) {
        ਵਾਪਸ true;
    }

    ਚੋਣ (surface->map.info.flags & SDL_COPY_BLEND_ਨਕਾਬ) {
    ਹਾਲਤ SDL_COPY_BLEND:
        *blend_ਬਹੁਲਕ = SDL_BLENDMODE_BLEND;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_COPY_BLEND_PREMULTIPLIED:
        *blend_ਬਹੁਲਕ = SDL_BLENDMODE_BLEND_PREMULTIPLIED;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_COPY_ਜੋੜੋ:
        *blend_ਬਹੁਲਕ = SDL_BLENDMODE_ਜੋੜੋ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_COPY_ਜੋੜੋ_PREMULTIPLIED:
        *blend_ਬਹੁਲਕ = SDL_BLENDMODE_ਜੋੜੋ_PREMULTIPLIED;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_COPY_MOD:
        *blend_ਬਹੁਲਕ = SDL_BLENDMODE_MOD;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_COPY_MUL:
        *blend_ਬਹੁਲਕ = SDL_BLENDMODE_MUL;
        ਰੋਕੋ;
    ਮੂਲ:
        *blend_ਬਹੁਲਕ = SDL_BLENDMODE_NONE;
        ਰੋਕੋ;
    }
    ਵਾਪਸ true;
}

bool SDL_ਸੈੱਟ_Surface_Clip_Rect(SDL_Surface *surface, ਅਚਲ SDL_Rect *rect)
{
    SDL_Rect ਭਰਿਆ_rect;

    // Don't do anything if there's no surface to act on
    ਜੇ (!SDL_SurfaceValid(surface)) {
        ਵਾਪਸ false;
    }

    // Set up the full surface rectangle
    ਭਰਿਆ_rect.x = 0;
    ਭਰਿਆ_rect.y = 0;
    ਭਰਿਆ_rect.w = surface->w;
    ਭਰਿਆ_rect.h = surface->h;

    // Set the clipping rectangle
    ਜੇ (!rect) {
        surface->clip_rect = ਭਰਿਆ_rect;
        ਵਾਪਸ true;
    }
    ਵਾਪਸ SDL_GetRectIntersection(rect, &ਭਰਿਆ_rect, &surface->clip_rect);
}

bool SDL_GetSurfaceClipRect(SDL_Surface *surface, SDL_Rect *rect)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ਜੇ (rect) {
            SDL_zerop(rect);
        }
        ਵਾਪਸ SDL_InvalidParamError("surface");
    }
    CHECK_PARAM(!rect) {
        ਵਾਪਸ SDL_InvalidParamError("rect");
    }
    *rect = surface->clip_rect;
    ਵਾਪਸ true;
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
bool SDL_BlitSurfaceUnchecked(SDL_Surface *src, ਅਚਲ SDL_Rect *srcrect,
                             SDL_Surface *dst, ਅਚਲ SDL_Rect *dstrect)
{
    // Check to make sure the blit mapping is valid
    ਜੇ (!SDL_ValidateMap(src, dst)) {
        ਵਾਪਸ false;
    }
    ਵਾਪਸ src->map.blit(src, srcrect, dst, dstrect);
}

bool SDL_BlitSurface(SDL_Surface *src, ਅਚਲ SDL_Rect *srcrect, SDL_Surface *dst, ਅਚਲ SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src) || (!src->pixels && !SDL_MUSTLOCK(src))) {
        ਵਾਪਸ SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst) || (!dst->pixels && !SDL_MUSTLOCK(dst))) {
        ਵਾਪਸ SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Surfaces must not be locked during blit");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    ਜੇ (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
    } ਨਹੀਂਤਾਂ {
        r_dst.x = 0;
        r_dst.y = 0;
    }

    // clip the source rectangle to the source surface
    ਜੇ (srcrect) {
        SDL_Rect tmp;
        ਜੇ (SDL_GetRectIntersection(srcrect, &r_src, &tmp) == false) {
            ਵਾਪਸ true;
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
        ਜੇ (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &tmp) == false) {
            ਵਾਪਸ true;
        }

        // Shift srcrect, if dstrect has changed
        r_src.x += tmp.x - r_dst.x;
        r_src.y += tmp.y - r_dst.y;
        r_src.w = tmp.w;
        r_src.h = tmp.h;

        // Update dstrect
        r_dst = tmp;
    }

    ਜੇ (r_dst.w <= 0 || r_dst.h <= 0) {
        // No-op.
        ਵਾਪਸ true;
    }

    // Switch back to a fast blit if we were previously stretching
    ਜੇ (src->map.info.flags & SDL_COPY_ਸਭ_ਤੋਂ_ਨੇੜੇ) {
        src->map.info.flags &= ~SDL_COPY_ਸਭ_ਤੋਂ_ਨੇੜੇ;
        SDL_InvalidateMap(&src->map);
    }

    ਵਾਪਸ SDL_BlitSurfaceUnchecked(src, &r_src, dst, &r_dst);
}

ਸਥਿਰ bool SDL_BlitSurfaceClippedScaled(SDL_Surface *src, ਅਚਲ SDL_Rect *srcrect, SDL_Surface *dst, ਅਚਲ SDL_Rect *dstrect, SDL_Scale_ਬਹੁਲਕ scale_ਬਹੁਲਕ)
{
    // We need to scale first, then blit into dst because we're clipping in the destination surface pixel coordinates
    bool ਨਤੀਜਾ;
    ਪੂਰਨ saved_w = src->w;
    ਪੂਰਨ saved_h = src->h;
    ਖਾਲੀ *saved_pixels = src->pixels;
    src->w = srcrect->w;
    src->h = srcrect->h;
    src->pixels = (Uint8 *)src->pixels + srcrect->y * src->pitch + srcrect->x * SDL_BYTESPERPIXEL(src->format);
    SDL_Surface *scaled = SDL_ScaleSurface(src, dstrect->w, dstrect->h, scale_ਬਹੁਲਕ);
    ਜੇ (scaled) {
        ਨਤੀਜਾ = SDL_BlitSurface(scaled, ਨਿਰਾ, dst, dstrect);
        SDL_DestroySurface(scaled);
    } ਨਹੀਂਤਾਂ {
        ਨਤੀਜਾ = false;
    }
    src->w = saved_w;
    src->h = saved_h;
    src->pixels = saved_pixels;
    ਵਾਪਸ ਨਤੀਜਾ;
}

bool SDL_BlitSurfaceScaled(SDL_Surface *src, ਅਚਲ SDL_Rect *srcrect, SDL_Surface *dst, ਅਚਲ SDL_Rect *dstrect, SDL_Scale_ਬਹੁਲਕ scale_ਬਹੁਲਕ)
{
    SDL_Rect r_src, r_dst;
    bool ਨਤੀਜਾ;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src) || (!src->pixels && !SDL_MUSTLOCK(src))) {
        ਵਾਪਸ SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst) || (!dst->pixels && !SDL_MUSTLOCK(dst))) {
        ਵਾਪਸ SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Surfaces must not be locked during blit");
    }

    ਚੋਣ (scale_ਬਹੁਲਕ) {
    ਹਾਲਤ SDL_SCALEMODE_ਸਭ_ਤੋਂ_ਨੇੜੇ:
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SCALEMODE_ਰੇਖਿਕ:
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SCALEMODE_PIXELART:
        scale_ਬਹੁਲਕ = SDL_SCALEMODE_ਸਭ_ਤੋਂ_ਨੇੜੇ;
        ਰੋਕੋ;
    ਮੂਲ:
        ਵਾਪਸ SDL_InvalidParamError("scaleMode");
    }

    ਪੂਰਨ src_w = srcrect ? srcrect->w : src->w;
    ਪੂਰਨ src_h = srcrect ? srcrect->h : src->h;
    ਪੂਰਨ dst_w = dstrect ? dstrect->w : dst->w;
    ਪੂਰਨ dst_h = dstrect ? dstrect->h : dst->h;
    ਜੇ (src_w == dst_w && src_h == dst_h) {
        // No scaling, defer to regular blit
        ਵਾਪਸ SDL_BlitSurface(src, srcrect, dst, dstrect);
    }

    ਜੇ (src->w == 0 || src->h == 0) {
        // Nothing to do
        ਵਾਪਸ true;
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    ਜੇ (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
        r_dst.w = dstrect->w;
        r_dst.h = dstrect->h;
    } ਨਹੀਂਤਾਂ {
        r_dst.x = 0;
        r_dst.y = 0;
        r_dst.w = dst->w;
        r_dst.h = dst->h;
    }

    // clip the source rectangle to the source surface
    ਜੇ (srcrect) {
        SDL_Rect desired, tmp;
        desired.x = srcrect->x;
        desired.y = srcrect->y;
        desired.w = SDL_max(srcrect->w, 1);
        desired.h = SDL_max(srcrect->h, 1);
        ਜੇ (SDL_GetRectIntersection(&desired, &r_src, &tmp) == false) {
            ਵਾਪਸ true;
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
    ਜੇ (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &tmp) == false) {
        ਵਾਪਸ true;
    }

    ਜੇ (tmp.x != r_dst.x || tmp.y != r_dst.y || tmp.w != r_dst.w || tmp.h != r_dst.h) {
        // Need to do a clipped and scaled blit
        ਵਾਪਸ SDL_BlitSurfaceClippedScaled(src, &r_src, dst, &r_dst, scale_ਬਹੁਲਕ);
    }

    ਜੇ (SDL_MUSTLOCK(src)) {
        ਜੇ (!SDL_ਤਾਲਾ_Surface(src)) {
            ਵਾਪਸ false;
        }
    }
    ਜੇ (SDL_MUSTLOCK(dst)) {
        ਜੇ (!SDL_ਤਾਲਾ_Surface(dst)) {
            ਜੇ (SDL_MUSTLOCK(src)) {
                SDL_UnlockSurface(src);
            }
            ਵਾਪਸ false;
        }
    }

    ਨਤੀਜਾ = SDL_BlitSurfaceUncheckedScaled(src, &r_src, dst, &r_dst, scale_ਬਹੁਲਕ);

    ਜੇ (SDL_MUSTLOCK(src)) {
        SDL_UnlockSurface(src);
    }
    ਜੇ (SDL_MUSTLOCK(dst)) {
        SDL_UnlockSurface(dst);
    }
    ਵਾਪਸ ਨਤੀਜਾ;
}

/**
 *  This is a semi-private blit function and it performs low-level surface
 *  scaled blitting only.
 */
bool SDL_BlitSurfaceUncheckedScaled(SDL_Surface *src, ਅਚਲ SDL_Rect *srcrect, SDL_Surface *dst, ਅਚਲ SDL_Rect *dstrect, SDL_Scale_ਬਹੁਲਕ scale_ਬਹੁਲਕ)
{
    ਸਥਿਰ ਅਚਲ Uint32 complex_copy_flags = (SDL_COPY_MODULATE_ਨਕਾਬ | SDL_COPY_BLEND_ਨਕਾਬ | SDL_COPY_COLORKEY);

    ਜੇ (srcrect->w > SDL_MAX_UINT16 || srcrect->h > SDL_MAX_UINT16 ||
        dstrect->w > SDL_MAX_UINT16 || dstrect->h > SDL_MAX_UINT16) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Size too large for scaling");
    }

    ਜੇ (!(src->map.info.flags & SDL_COPY_ਸਭ_ਤੋਂ_ਨੇੜੇ)) {
        src->map.info.flags |= SDL_COPY_ਸਭ_ਤੋਂ_ਨੇੜੇ;
        SDL_InvalidateMap(&src->map);
    }

    ਜੇ (scale_ਬਹੁਲਕ == SDL_SCALEMODE_ਸਭ_ਤੋਂ_ਨੇੜੇ || scale_ਬਹੁਲਕ == SDL_SCALEMODE_PIXELART) {
        ਜੇ (!(src->map.info.flags & complex_copy_flags) &&
            src->format == dst->format &&
            (!SDL_ISPIXELFORMAT_ਸੂਚਕਾਂਕਿਤ(src->format) ||
             (SDL_BITSPERPIXEL(src->format) == 8 && SDL_IsSamePalette(src->palette, dst->palette))) &&
            SDL_BYTESPERPIXEL(src->format) <= 4) {
            ਵਾਪਸ SDL_StretchSurface(src, srcrect, dst, dstrect, SDL_SCALEMODE_ਸਭ_ਤੋਂ_ਨੇੜੇ);
        } ਨਹੀਂਤਾਂ ਜੇ (SDL_BITSPERPIXEL(src->format) < 8) {
            // Scaling bitmap not yet supported, convert to RGBA for blit
            bool ਨਤੀਜਾ = false;
            SDL_Surface *tmp = SDL_ConvertSurface(src, SDL_PIXELFORMAT_ARGB8888);
            ਜੇ (tmp) {
                ਨਤੀਜਾ = SDL_BlitSurfaceUncheckedScaled(tmp, srcrect, dst, dstrect, SDL_SCALEMODE_ਸਭ_ਤੋਂ_ਨੇੜੇ);
                SDL_DestroySurface(tmp);
            }
            ਵਾਪਸ ਨਤੀਜਾ;
        } ਨਹੀਂਤਾਂ {
            ਵਾਪਸ SDL_BlitSurfaceUnchecked(src, srcrect, dst, dstrect);
        }
    } ਨਹੀਂਤਾਂ {
        ਜੇ (!(src->map.info.flags & complex_copy_flags) &&
            src->format == dst->format &&
            !SDL_ISPIXELFORMAT_ਸੂਚਕਾਂਕਿਤ(src->format) &&
            SDL_BYTESPERPIXEL(src->format) == 4 &&
            src->format != SDL_PIXELFORMAT_ARGB2101010) {
            // fast path
            ਵਾਪਸ SDL_StretchSurface(src, srcrect, dst, dstrect, SDL_SCALEMODE_ਰੇਖਿਕ);
        } ਨਹੀਂਤਾਂ ਜੇ (SDL_BITSPERPIXEL(src->format) < 8) {
            // Scaling bitmap not yet supported, convert to RGBA for blit
            bool ਨਤੀਜਾ = false;
            SDL_Surface *tmp = SDL_ConvertSurface(src, SDL_PIXELFORMAT_ARGB8888);
            ਜੇ (tmp) {
                ਨਤੀਜਾ = SDL_BlitSurfaceUncheckedScaled(tmp, srcrect, dst, dstrect, scale_ਬਹੁਲਕ);
                SDL_DestroySurface(tmp);
            }
            ਵਾਪਸ ਨਤੀਜਾ;
        } ਨਹੀਂਤਾਂ {
            // Use intermediate surface(s)
            SDL_Surface *tmp1 = ਨਿਰਾ;
            bool ਨਤੀਜਾ;
            SDL_Rect srcrect2;
            ਪੂਰਨ is_complex_copy_flags = (src->map.info.flags & complex_copy_flags);

            Uint8 r, g, b;
            Uint8 alpha;
            SDL_Blend_ਬਹੁਲਕ blend_ਬਹੁਲਕ;

            // Save source infos
            SDL_GetSurfaceColorMod(src, &r, &g, &b);
            SDL_GetSurfaceAlphaMod(src, &alpha);
            SDL_Get_Surface_Blend_ਬਹੁਲਕ(src, &blend_ਬਹੁਲਕ);
            srcrect2.x = srcrect->x;
            srcrect2.y = srcrect->y;
            srcrect2.w = srcrect->w;
            srcrect2.h = srcrect->h;

            // Change source format if not appropriate for scaling
            ਜੇ (SDL_BYTESPERPIXEL(src->format) != 4 || src->format == SDL_PIXELFORMAT_ARGB2101010) {
                SDL_PixelFormat fmt;
                ਜੇ (SDL_BYTESPERPIXEL(dst->format) == 4 && dst->format != SDL_PIXELFORMAT_ARGB2101010 &&
                    (SDL_ISPIXELFORMAT_ALPHA(dst->format) || !is_complex_copy_flags)) {
                    fmt = dst->format;
                } ਨਹੀਂਤਾਂ {
                    fmt = SDL_PIXELFORMAT_ARGB8888;
                }
                tmp1 = SDL_ConvertSurfaceRect(src, srcrect, fmt);
                ਜੇ (!tmp1) {
                    ਵਾਪਸ false;
                }
                src = tmp1;
                srcrect2.x = 0;
                srcrect2.y = 0;
            }

            // Intermediate scaling
            ਜੇ (is_complex_copy_flags || src->format != dst->format) {
                SDL_Rect tmprect;
                SDL_Surface *tmp2 = SDL_CreateSurfaceUninitialized(dstrect->w, dstrect->h, src->format);
                SDL_StretchSurface(src, &srcrect2, tmp2, ਨਿਰਾ, SDL_SCALEMODE_ਰੇਖਿਕ);

                SDL_ਸੈੱਟ_Surface_Color_Mod(tmp2, r, g, b);
                SDL_ਸੈੱਟ_Surface_Alpha_Mod(tmp2, alpha);
                SDL_ਸੈੱਟ_Surface_Blend_ਬਹੁਲਕ(tmp2, blend_ਬਹੁਲਕ);

                tmprect.x = 0;
                tmprect.y = 0;
                tmprect.w = dstrect->w;
                tmprect.h = dstrect->h;
                ਨਤੀਜਾ = SDL_BlitSurfaceUnchecked(tmp2, &tmprect, dst, dstrect);
                SDL_DestroySurface(tmp2);
            } ਨਹੀਂਤਾਂ {
                ਨਤੀਜਾ = SDL_StretchSurface(src, &srcrect2, dst, dstrect, SDL_SCALEMODE_ਰੇਖਿਕ);
            }

            SDL_DestroySurface(tmp1);
            ਵਾਪਸ ਨਤੀਜਾ;
        }
    }
}

bool SDL_BlitSurfaceTiled(SDL_Surface *src, ਅਚਲ SDL_Rect *srcrect, SDL_Surface *dst, ਅਚਲ SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        ਵਾਪਸ SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        ਵਾਪਸ SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Surfaces must not be locked during blit");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    ਜੇ (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
        r_dst.w = dstrect->w;
        r_dst.h = dstrect->h;
    } ਨਹੀਂਤਾਂ {
        r_dst.x = 0;
        r_dst.y = 0;
        r_dst.w = dst->w;
        r_dst.h = dst->h;
    }

    // clip the source rectangle to the source surface
    ਜੇ (srcrect) {
        ਜੇ (SDL_GetRectIntersection(srcrect, &r_src, &r_src) == false) {
            ਵਾਪਸ true;
        }

        // For tiling we don't adjust the destination rectangle
    }

    // clip the destination rectangle against the clip rectangle
    {
        ਜੇ (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &r_dst) == false) {
            ਵਾਪਸ true;
        }

        // For tiling we don't adjust the source rectangle
    }

    // Switch back to a fast blit if we were previously stretching
    ਜੇ (src->map.info.flags & SDL_COPY_ਸਭ_ਤੋਂ_ਨੇੜੇ) {
        src->map.info.flags &= ~SDL_COPY_ਸਭ_ਤੋਂ_ਨੇੜੇ;
        SDL_InvalidateMap(&src->map);
    }

    ਪੂਰਨ ਪੰਕਤੀਆਂ = r_dst.h / r_src.h;
    ਪੂਰਨ ਖਾਨੇ_ਗਿਣਤੀ = r_dst.w / r_src.w;
    ਪੂਰਨ ਬਚਿਆ_w = r_dst.w % r_src.w;
    ਪੂਰਨ ਬਚਿਆ_h = r_dst.h % r_src.h;
    SDL_Rect curr_src, curr_dst;

    SDL_copyp(&curr_src, &r_src);
    curr_dst.y = r_dst.y;
    curr_dst.w = r_src.w;
    curr_dst.h = r_src.h;
    ਲਈ (ਪੂਰਨ y = 0; y < ਪੰਕਤੀਆਂ; ++y) {
        curr_dst.x = r_dst.x;
        ਲਈ (ਪੂਰਨ x = 0; x < ਖਾਨੇ_ਗਿਣਤੀ; ++x) {
            ਜੇ (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                ਵਾਪਸ false;
            }
            curr_dst.x += curr_dst.w;
        }
        ਜੇ (ਬਚਿਆ_w) {
            curr_src.w = ਬਚਿਆ_w;
            curr_dst.w = ਬਚਿਆ_w;
            ਜੇ (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                ਵਾਪਸ false;
            }
            curr_src.w = r_src.w;
            curr_dst.w = r_src.w;
        }
        curr_dst.y += curr_dst.h;
    }
    ਜੇ (ਬਚਿਆ_h) {
        curr_src.h = ਬਚਿਆ_h;
        curr_dst.h = ਬਚਿਆ_h;
        curr_dst.x = r_dst.x;
        ਲਈ (ਪੂਰਨ x = 0; x < ਖਾਨੇ_ਗਿਣਤੀ; ++x) {
            ਜੇ (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                ਵਾਪਸ false;
            }
            curr_dst.x += curr_dst.w;
        }
        ਜੇ (ਬਚਿਆ_w) {
            curr_src.w = ਬਚਿਆ_w;
            curr_dst.w = ਬਚਿਆ_w;
            ਜੇ (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                ਵਾਪਸ false;
            }
        }
    }
    ਵਾਪਸ true;
}

bool SDL_BlitSurfaceTiledWithScale(SDL_Surface *src, ਅਚਲ SDL_Rect *srcrect, ਦਸ਼ਮਲਵ scale, SDL_Scale_ਬਹੁਲਕ scale_ਬਹੁਲਕ, SDL_Surface *dst, ਅਚਲ SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        ਵਾਪਸ SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        ਵਾਪਸ SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Surfaces must not be locked during blit");
    }
    CHECK_PARAM(scale < 0.0f) {
        ਵਾਪਸ SDL_InvalidParamError("scale");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    ਜੇ (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
        r_dst.w = dstrect->w;
        r_dst.h = dstrect->h;
    } ਨਹੀਂਤਾਂ {
        r_dst.x = 0;
        r_dst.y = 0;
        r_dst.w = dst->w;
        r_dst.h = dst->h;
    }

    // clip the source rectangle to the source surface
    ਜੇ (srcrect) {
        ਜੇ (SDL_GetRectIntersection(srcrect, &r_src, &r_src) == false) {
            ਵਾਪਸ true;
        }

        // For tiling we don't adjust the destination rectangle
    }

    // clip the destination rectangle against the clip rectangle
    {
        ਜੇ (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &r_dst) == false) {
            ਵਾਪਸ true;
        }

        // For tiling we don't adjust the source rectangle
    }

    // Switch back to a fast blit if we were previously stretching
    ਜੇ (src->map.info.flags & SDL_COPY_ਸਭ_ਤੋਂ_ਨੇੜੇ) {
        src->map.info.flags &= ~SDL_COPY_ਸਭ_ਤੋਂ_ਨੇੜੇ;
        SDL_InvalidateMap(&src->map);
    }

    ਪੂਰਨ tile_ਚੌੜਾਈ = (ਪੂਰਨ)SDL_roundf(r_src.w * scale);
    ਪੂਰਨ tile_ਉਚਾਈ = (ਪੂਰਨ)SDL_roundf(r_src.h * scale);
    ਜੇ (tile_ਚੌੜਾਈ <= 0 || tile_ਉਚਾਈ <= 0) {
        // Nothing to do
        ਵਾਪਸ true;
    }
    ਪੂਰਨ ਪੰਕਤੀਆਂ = r_dst.h / tile_ਉਚਾਈ;
    ਪੂਰਨ ਖਾਨੇ_ਗਿਣਤੀ = r_dst.w / tile_ਚੌੜਾਈ;
    ਪੂਰਨ ਬਚਿਆ_dst_w = (r_dst.w - ਖਾਨੇ_ਗਿਣਤੀ * tile_ਚੌੜਾਈ);
    ਪੂਰਨ ਬਚਿਆ_dst_h = (r_dst.h - ਪੰਕਤੀਆਂ * tile_ਉਚਾਈ);
    ਪੂਰਨ ਬਚਿਆ_src_w = (ਪੂਰਨ)(ਬਚਿਆ_dst_w / scale);
    ਪੂਰਨ ਬਚਿਆ_src_h = (ਪੂਰਨ)(ਬਚਿਆ_dst_h / scale);
    SDL_Rect curr_src, curr_dst;

    SDL_copyp(&curr_src, &r_src);
    curr_dst.y = r_dst.y;
    curr_dst.w = tile_ਚੌੜਾਈ;
    curr_dst.h = tile_ਉਚਾਈ;
    ਲਈ (ਪੂਰਨ y = 0; y < ਪੰਕਤੀਆਂ; ++y) {
        curr_dst.x = r_dst.x;
        ਲਈ (ਪੂਰਨ x = 0; x < ਖਾਨੇ_ਗਿਣਤੀ; ++x) {
            ਜੇ (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scale_ਬਹੁਲਕ)) {
                ਵਾਪਸ false;
            }
            curr_dst.x += curr_dst.w;
        }
        ਜੇ (ਬਚਿਆ_dst_w > 0) {
            curr_src.w = ਬਚਿਆ_src_w;
            curr_dst.w = ਬਚਿਆ_dst_w;
            ਜੇ (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scale_ਬਹੁਲਕ)) {
                ਵਾਪਸ false;
            }
            curr_src.w = r_src.w;
            curr_dst.w = tile_ਚੌੜਾਈ;
        }
        curr_dst.y += curr_dst.h;
    }
    ਜੇ (ਬਚਿਆ_dst_h > 0) {
        curr_src.h = ਬਚਿਆ_src_h;
        curr_dst.h = ਬਚਿਆ_dst_h;
        curr_dst.x = r_dst.x;
        ਲਈ (ਪੂਰਨ x = 0; x < ਖਾਨੇ_ਗਿਣਤੀ; ++x) {
            ਜੇ (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scale_ਬਹੁਲਕ)) {
                ਵਾਪਸ false;
            }
            curr_dst.x += curr_dst.w;
        }
        ਜੇ (ਬਚਿਆ_dst_w > 0) {
            curr_src.w = ਬਚਿਆ_src_w;
            curr_dst.w = ਬਚਿਆ_dst_w;
            ਜੇ (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scale_ਬਹੁਲਕ)) {
                ਵਾਪਸ false;
            }
        }
    }
    ਵਾਪਸ true;
}

bool SDL_BlitSurface9Grid(SDL_Surface *src, ਅਚਲ SDL_Rect *srcrect, ਪੂਰਨ ਖੱਬਾ_ਚੌੜਾਈ, ਪੂਰਨ ਸੱਜਾ_ਚੌੜਾਈ, ਪੂਰਨ ਸਿਖਰ_ਉਚਾਈ, ਪੂਰਨ bottom_ਉਚਾਈ, ਦਸ਼ਮਲਵ scale, SDL_Scale_ਬਹੁਲਕ scale_ਬਹੁਲਕ, SDL_Surface *dst, ਅਚਲ SDL_Rect *dstrect)
{
    SDL_Rect ਭਰਿਆ_src, ਭਰਿਆ_dst;
    SDL_Rect curr_src, curr_dst;
    ਪੂਰਨ dst_ਖੱਬਾ_ਚੌੜਾਈ;
    ਪੂਰਨ dst_ਸੱਜਾ_ਚੌੜਾਈ;
    ਪੂਰਨ dst_ਸਿਖਰ_ਉਚਾਈ;
    ਪੂਰਨ dst_bottom_ਉਚਾਈ;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        ਵਾਪਸ SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        ਵਾਪਸ SDL_InvalidParamError("dst");
    }

    ਜੇ (!srcrect) {
        ਭਰਿਆ_src.x = 0;
        ਭਰਿਆ_src.y = 0;
        ਭਰਿਆ_src.w = src->w;
        ਭਰਿਆ_src.h = src->h;
        srcrect = &ਭਰਿਆ_src;
    }

    ਜੇ (!dstrect) {
        ਭਰਿਆ_dst.x = 0;
        ਭਰਿਆ_dst.y = 0;
        ਭਰਿਆ_dst.w = dst->w;
        ਭਰਿਆ_dst.h = dst->h;
        dstrect = &ਭਰਿਆ_dst;
    }

    ਜੇ (scale <= 0.0f || scale == 1.0f) {
        dst_ਖੱਬਾ_ਚੌੜਾਈ = ਖੱਬਾ_ਚੌੜਾਈ;
        dst_ਸੱਜਾ_ਚੌੜਾਈ = ਸੱਜਾ_ਚੌੜਾਈ;
        dst_ਸਿਖਰ_ਉਚਾਈ = ਸਿਖਰ_ਉਚਾਈ;
        dst_bottom_ਉਚਾਈ = bottom_ਉਚਾਈ;
    } ਨਹੀਂਤਾਂ {
        dst_ਖੱਬਾ_ਚੌੜਾਈ = (ਪੂਰਨ)SDL_roundf(ਖੱਬਾ_ਚੌੜਾਈ * scale);
        dst_ਸੱਜਾ_ਚੌੜਾਈ = (ਪੂਰਨ)SDL_roundf(ਸੱਜਾ_ਚੌੜਾਈ * scale);
        dst_ਸਿਖਰ_ਉਚਾਈ = (ਪੂਰਨ)SDL_roundf(ਸਿਖਰ_ਉਚਾਈ * scale);
        dst_bottom_ਉਚਾਈ = (ਪੂਰਨ)SDL_roundf(bottom_ਉਚਾਈ * scale);
    }

    // Upper-left corner
    curr_src.x = srcrect->x;
    curr_src.y = srcrect->y;
    curr_src.w = ਖੱਬਾ_ਚੌੜਾਈ;
    curr_src.h = ਸਿਖਰ_ਉਚਾਈ;
    curr_dst.x = dstrect->x;
    curr_dst.y = dstrect->y;
    curr_dst.w = dst_ਖੱਬਾ_ਚੌੜਾਈ;
    curr_dst.h = dst_ਸਿਖਰ_ਉਚਾਈ;
    ਜੇ (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_ਬਹੁਲਕ)) {
        ਵਾਪਸ false;
    }

    // Upper-right corner
    curr_src.x = srcrect->x + srcrect->w - ਸੱਜਾ_ਚੌੜਾਈ;
    curr_src.w = ਸੱਜਾ_ਚੌੜਾਈ;
    curr_dst.x = dstrect->x + dstrect->w - dst_ਸੱਜਾ_ਚੌੜਾਈ;
    curr_dst.w = dst_ਸੱਜਾ_ਚੌੜਾਈ;
    ਜੇ (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_ਬਹੁਲਕ)) {
        ਵਾਪਸ false;
    }

    // Lower-right corner
    curr_src.y = srcrect->y + srcrect->h - bottom_ਉਚਾਈ;
    curr_dst.y = dstrect->y + dstrect->h - dst_bottom_ਉਚਾਈ;
    curr_dst.h = dst_bottom_ਉਚਾਈ;
    ਜੇ (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_ਬਹੁਲਕ)) {
        ਵਾਪਸ false;
    }

    // Lower-left corner
    curr_src.x = srcrect->x;
    curr_src.w = ਖੱਬਾ_ਚੌੜਾਈ;
    curr_dst.x = dstrect->x;
    curr_dst.w = dst_ਖੱਬਾ_ਚੌੜਾਈ;
    ਜੇ (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_ਬਹੁਲਕ)) {
        ਵਾਪਸ false;
    }

    //ਖੱਬਾ
    curr_src.y = srcrect->y + ਸਿਖਰ_ਉਚਾਈ;
    curr_src.h = srcrect->h - ਸਿਖਰ_ਉਚਾਈ - bottom_ਉਚਾਈ;
    curr_dst.y = dstrect->y + dst_ਸਿਖਰ_ਉਚਾਈ;
    curr_dst.h = dstrect->h - dst_ਸਿਖਰ_ਉਚਾਈ - dst_bottom_ਉਚਾਈ;
    ਜੇ (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_ਬਹੁਲਕ)) {
        ਵਾਪਸ false;
    }

    //ਸੱਜਾ
    curr_src.x = srcrect->x + srcrect->w - ਸੱਜਾ_ਚੌੜਾਈ;
    curr_src.w = ਸੱਜਾ_ਚੌੜਾਈ;
    curr_dst.x = dstrect->x + dstrect->w - dst_ਸੱਜਾ_ਚੌੜਾਈ;
    curr_dst.w = dst_ਸੱਜਾ_ਚੌੜਾਈ;
    ਜੇ (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_ਬਹੁਲਕ)) {
        ਵਾਪਸ false;
    }

    //ਸਿਖਰ
    curr_src.x = srcrect->x + ਖੱਬਾ_ਚੌੜਾਈ;
    curr_src.y = srcrect->y;
    curr_src.w = srcrect->w - ਖੱਬਾ_ਚੌੜਾਈ - ਸੱਜਾ_ਚੌੜਾਈ;
    curr_src.h = ਸਿਖਰ_ਉਚਾਈ;
    curr_dst.x = dstrect->x + dst_ਖੱਬਾ_ਚੌੜਾਈ;
    curr_dst.y = dstrect->y;
    curr_dst.w = dstrect->w - dst_ਖੱਬਾ_ਚੌੜਾਈ - dst_ਸੱਜਾ_ਚੌੜਾਈ;
    curr_dst.h = dst_ਸਿਖਰ_ਉਚਾਈ;
    ਜੇ (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_ਬਹੁਲਕ)) {
        ਵਾਪਸ false;
    }

    // Bottom
    curr_src.y = srcrect->y + srcrect->h - bottom_ਉਚਾਈ;
    curr_dst.y = dstrect->y + dstrect->h - dst_bottom_ਉਚਾਈ;
    curr_dst.h = dst_bottom_ਉਚਾਈ;
    ਜੇ (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_ਬਹੁਲਕ)) {
        ਵਾਪਸ false;
    }

    // Center
    curr_src.x = srcrect->x + ਖੱਬਾ_ਚੌੜਾਈ;
    curr_src.y = srcrect->y + ਸਿਖਰ_ਉਚਾਈ;
    curr_src.w = srcrect->w - ਖੱਬਾ_ਚੌੜਾਈ - ਸੱਜਾ_ਚੌੜਾਈ;
    curr_src.h = srcrect->h - ਸਿਖਰ_ਉਚਾਈ - bottom_ਉਚਾਈ;
    curr_dst.x = dstrect->x + dst_ਖੱਬਾ_ਚੌੜਾਈ;
    curr_dst.y = dstrect->y + dst_ਸਿਖਰ_ਉਚਾਈ;
    curr_dst.w = dstrect->w - dst_ਖੱਬਾ_ਚੌੜਾਈ - dst_ਸੱਜਾ_ਚੌੜਾਈ;
    curr_dst.h = dstrect->h - dst_ਸਿਖਰ_ਉਚਾਈ - dst_bottom_ਉਚਾਈ;
    ਜੇ (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_ਬਹੁਲਕ)) {
        ਵਾਪਸ false;
    }

    ਵਾਪਸ true;
}

/*
 * Lock a surface to directly access the pixels
 */
bool SDL_ਤਾਲਾ_Surface(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ਵਾਪਸ SDL_InvalidParamError("surface");
    }

    ਜੇ (!surface->locked) {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_HAVE_RLE
        // Perform the lock
        ਜੇ (surface->ਅੰਦਰੂਨੀ_flags & SDL_ਅੰਦਰੂਨੀ_SURFACE_RLEACCEL) {
            SDL_UnRLESurface(surface);
        }
#ਜੇ_ਅੰਤ
    }

    // Increment the surface lock count, for recursive locks
    ++surface->locked;
    surface->flags |= SDL_SURFACE_LOCKED;
    SDL_Update_Surface_ਤਾਲਾ_Flag(surface);

    // Ready to go..
    ਵਾਪਸ true;
}

/*
 * Unlock a previously locked surface
 */
ਖਾਲੀ SDL_UnlockSurface(SDL_Surface *surface)
{
    ਜੇ (!SDL_SurfaceValid(surface)) {
        ਵਾਪਸ;
    }

    // Only perform an unlock if we are locked
    ਜੇ (!surface->locked || (--surface->locked > 0)) {
        ਵਾਪਸ;
    }

    surface->flags &= ~SDL_SURFACE_LOCKED;
    SDL_Update_Surface_ਤਾਲਾ_Flag(surface);
}

ਸਥਿਰ bool SDL_FlipSurfaceHorizontal(SDL_Surface *surface)
{
    bool isstack;
    Uint8 *ਪੰਕਤੀ, *a, *b, *tmp;
    ਪੂਰਨ i, j, bpp;

    ਜੇ (SDL_BITSPERPIXEL(surface->format) < 8) {
        // We could implement this if needed, but we'd have to flip sets of bits within a byte
        ਵਾਪਸ SDL_Unsupported();
    }

    ਜੇ (surface->h <= 0) {
        ਵਾਪਸ true;
    }

    ਜੇ (surface->w <= 1) {
        ਵਾਪਸ true;
    }

    bpp = SDL_BYTESPERPIXEL(surface->format);
    ਪੰਕਤੀ = (Uint8 *)surface->pixels;
    tmp = SDL_small_alloc(Uint8, surface->pitch, &isstack);
    ਜੇ (!tmp) {
        ਵਾਪਸ false;
    }
    ਲਈ (i = surface->h; i--; ) {
        a = ਪੰਕਤੀ;
        b = a + (surface->w - 1) * bpp;
        ਲਈ (j = surface->w / 2; j--; ) {
            SDL_memcpy(tmp, a, bpp);
            SDL_memcpy(a, b, bpp);
            SDL_memcpy(b, tmp, bpp);
            a += bpp;
            b -= bpp;
        }
        ਪੰਕਤੀ += surface->pitch;
    }
    SDL_small_free(tmp, isstack);
    ਵਾਪਸ true;
}

ਸਥਿਰ bool SDL_FlipSurfaceVertical(SDL_Surface *surface)
{
    bool isstack;
    Uint8 *a, *b, *tmp;
    ਪੂਰਨ i;

    ਜੇ (surface->h <= 1) {
        ਵਾਪਸ true;
    }

    a = (Uint8 *)surface->pixels;
    b = a + (surface->h - 1) * surface->pitch;
    tmp = SDL_small_alloc(Uint8, surface->pitch, &isstack);
    ਜੇ (!tmp) {
        ਵਾਪਸ false;
    }
    ਲਈ (i = surface->h / 2; i--; ) {
        SDL_memcpy(tmp, a, surface->pitch);
        SDL_memcpy(a, b, surface->pitch);
        SDL_memcpy(b, tmp, surface->pitch);
        a += surface->pitch;
        b -= surface->pitch;
    }
    SDL_small_free(tmp, isstack);
    ਵਾਪਸ true;
}

bool SDL_FlipSurface(SDL_Surface *surface, SDL_Flip_ਬਹੁਲਕ flip)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ਵਾਪਸ SDL_InvalidParamError("surface");
    }
    ਜੇ (!surface->pixels) {
        ਵਾਪਸ true;
    }

    bool ਨਤੀਜਾ = true;
    ਚੋਣ (flip) {
    ਹਾਲਤ SDL_FLIP_HORIZONTAL:
        ਨਤੀਜਾ = SDL_FlipSurfaceHorizontal(surface);
        ਰੋਕੋ;
    ਹਾਲਤ SDL_FLIP_VERTICAL:
        ਨਤੀਜਾ = SDL_FlipSurfaceVertical(surface);
        ਰੋਕੋ;
    ਹਾਲਤ SDL_FLIP_HORIZONTAL_AND_VERTICAL:
        ਨਤੀਜਾ &= SDL_FlipSurfaceHorizontal(surface);
        ਨਤੀਜਾ &= SDL_FlipSurfaceVertical(surface);
        ਰੋਕੋ;
    ਮੂਲ:
        ਨਤੀਜਾ = SDL_InvalidParamError("flip");
        ਰੋਕੋ;
    }
    ਵਾਪਸ ਨਤੀਜਾ;
}

ਸਥਿਰ SDL_Surface *SDL_ConvertSurfaceRectAndColorspace(SDL_Surface *surface, ਅਚਲ SDL_Rect *rect, SDL_PixelFormat format, SDL_Palette *palette, SDL_Colorspace colorspace, SDL_PropertiesID props)
{
    SDL_Palette *ਆਰਜ਼ੀ_palette = ਨਿਰਾ;
    SDL_Surface *convert = ਨਿਰਾ;
    SDL_Colorspace src_colorspace;
    SDL_PropertiesID src_properties;
    Uint32 copy_flags;
    SDL_Color copy_color;
    SDL_Rect bounds;
    bool ਨਤੀਜਾ;
    bool palette_ck_transform = false;
    Uint8 palette_ck_ਮੁੱਲ = 0;
    Uint8 *palette_saved_alpha = ਨਿਰਾ;
    ਪੂਰਨ palette_saved_alpha_ncolors = 0;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        ਜਾਓ error;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        ਜਾਓ error;
    }

    // Set the bounds of the new surface
    bounds.x = 0;
    bounds.y = 0;
    bounds.w = surface->w;
    bounds.h = surface->h;
    ਜੇ (rect) {
        bounds.w = rect->w;
        bounds.h = rect->h;
    } ਨਹੀਂਤਾਂ {
        rect = &bounds;
    }

    // Check for empty destination palette! (results in empty image)
    ਜੇ (palette) {
        ਪੂਰਨ i;
        ਲਈ (i = 0; i < palette->ncolors; ++i) {
            ਜੇ ((palette->colors[i].r != 0xFF) || (palette->colors[i].g != 0xFF) || (palette->colors[i].b != 0xFF)) {
                ਰੋਕੋ;
            }
        }
        ਜੇ (i == palette->ncolors) {
            SDL_ਸੈੱਟ_Error("Empty destination palette");
            ਜਾਓ error;
        }
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_ISPIXELFORMAT_ਸੂਚਕਾਂਕਿਤ(format)) {
        // Create a dither palette for conversion
        ਆਰਜ਼ੀ_palette = SDL_CreatePalette(1 << SDL_BITSPERPIXEL(format));
        ਜੇ (ਆਰਜ਼ੀ_palette) {
            SDL_DitherPalette(ਆਰਜ਼ੀ_palette);
            palette = ਆਰਜ਼ੀ_palette;
        }
    }

    src_colorspace = surface->colorspace;
    src_properties = surface->props;

    // Create a new surface with the desired format
    ਜੇ (surface->pixels || SDL_MUSTLOCK(surface)) {
        convert = SDL_CreateSurfaceUninitialized(rect->w, rect->h, format);
    } ਨਹੀਂਤਾਂ {
        convert = SDL_CreateSurfaceFrom(rect->w, rect->h, format, ਨਿਰਾ, 0);
    }
    ਜੇ (!convert) {
        ਜਾਓ error;
    }
    ਜੇ (SDL_ISPIXELFORMAT_ਸੂਚਕਾਂਕਿਤ(format)) {
        SDL_ਸੈੱਟ_Surface_Palette(convert, palette);
    }

    ਜੇ (colorspace == SDL_COLORSPACE_UNKNOWN) {
        colorspace = src_colorspace;
    }
    SDL_ਸੈੱਟ_Surface_Colorspace(convert, colorspace);

    ਜੇ (SDL_ISPIXELFORMAT_FOURCC(format) || SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        ਜੇ (surface->format == SDL_PIXELFORMAT_MJPG && format == SDL_PIXELFORMAT_MJPG) {
            // Just do a straight pixel copy of the JPEG image
            size_t ਮਾਪ = (size_t)surface->pitch;
            convert->pixels = SDL_malloc(ਮਾਪ);
            ਜੇ (!convert->pixels) {
                ਜਾਓ error;
            }
            convert->flags &= ~SDL_SURFACE_PREALLOCATED;
            convert->pitch = surface->pitch;
            SDL_memcpy(convert->pixels, surface->pixels, ਮਾਪ);

        } ਨਹੀਂਤਾਂ ਜੇ (!SDL_ConvertPixelsAndColorspace(surface->w, surface->h, surface->format, src_colorspace, src_properties, surface->pixels, surface->pitch, convert->format, colorspace, props, convert->pixels, convert->pitch)) {
            ਜਾਓ error;
        }

        // Save the original copy flags
        copy_flags = surface->map.info.flags;

        ਜਾਓ ਸਿਰਾ;
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
    ਜੇ (surface->palette && SDL_ISPIXELFORMAT_ALPHA(format)) {
        bool ਸੈੱਟ_opaque = false;

        bool is_opaque, has_alpha_channel;
        SDL_DetectPalette(surface->palette, &is_opaque, &has_alpha_channel);

        ਜੇ (is_opaque) {
            ਜੇ (!has_alpha_channel) {
                ਸੈੱਟ_opaque = true;
            }
        }

        // Set opaque and backup palette alpha values
        ਜੇ (ਸੈੱਟ_opaque) {
            ਪੂਰਨ i;
            palette_saved_alpha_ncolors = surface->palette->ncolors;
            ਜੇ (palette_saved_alpha_ncolors > 0) {
                palette_saved_alpha = SDL_ਢੇਰ_alloc(Uint8, palette_saved_alpha_ncolors);
                ਲਈ (i = 0; i < palette_saved_alpha_ncolors; i++) {
                    palette_saved_alpha[i] = surface->palette->colors[i].a;
                    surface->palette->colors[i].a = SDL_ALPHA_OPAQUE;
                }
            }
        }
    }

    // Transform colorkey to alpha. for cases where source palette has duplicate values, and colorkey is one of them
    ਜੇ (copy_flags & SDL_COPY_COLORKEY) {
        ਜੇ (surface->palette && !palette) {
            palette_ck_transform = true;
            palette_ck_ਮੁੱਲ = surface->palette->colors[surface->map.info.colorkey].a;
            surface->palette->colors[surface->map.info.colorkey].a = SDL_ALPHA_TRANSPARENT;
        }
    }

    ਜੇ (surface->pixels || SDL_MUSTLOCK(surface)) {
        ਨਤੀਜਾ = SDL_BlitSurfaceUnchecked(surface, rect, convert, &bounds);
    } ਨਹੀਂਤਾਂ {
        ਨਤੀਜਾ = true;
    }

    // Restore colorkey alpha value
    ਜੇ (palette_ck_transform) {
        surface->palette->colors[surface->map.info.colorkey].a = palette_ck_ਮੁੱਲ;
    }

    // Restore palette alpha values
    ਜੇ (palette_saved_alpha) {
        ਪੂਰਨ i;
        ਲਈ (i = 0; i < palette_saved_alpha_ncolors; i++) {
            surface->palette->colors[i].a = palette_saved_alpha[i];
        }
        SDL_ਢੇਰ_free(palette_saved_alpha);
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
    ਜੇ (!ਨਤੀਜਾ) {
        ਜਾਓ error;
    }

    ਜੇ (copy_flags & SDL_COPY_COLORKEY) {
        bool ਸੈੱਟ_colorkey_by_color = false;
        bool convert_colorkey = true;

        ਜੇ (surface->palette) {
            ਜੇ (palette &&
                surface->palette->ncolors <= palette->ncolors &&
                (SDL_memcmp(surface->palette->colors, palette->colors,
                            surface->palette->ncolors * ਆਕਾਰ(SDL_Color)) == 0)) {
                // The palette is identical, just set the same colorkey
                SDL_ਸੈੱਟ_Surface_Color_ਕੁੰਜੀ(convert, true, surface->map.info.colorkey);
            } ਨਹੀਂਤਾਂ ਜੇ (!palette) {
                ਜੇ (SDL_ISPIXELFORMAT_ALPHA(format)) {
                    // No need to add the colorkey, transparency is in the alpha channel
                } ਨਹੀਂਤਾਂ {
                    // Only set the colorkey information
                    ਸੈੱਟ_colorkey_by_color = true;
                    convert_colorkey = false;
                }
            } ਨਹੀਂਤਾਂ {
                ਸੈੱਟ_colorkey_by_color = true;
            }
        } ਨਹੀਂਤਾਂ {
            ਸੈੱਟ_colorkey_by_color = true;
        }

        ਜੇ (ਸੈੱਟ_colorkey_by_color) {
            SDL_Surface *tmp;
            SDL_Surface *tmp2;
            ਪੂਰਨ converted_colorkey = 0;

            // Create a dummy surface to get the colorkey converted
            tmp = SDL_CreateSurfaceUninitialized(1, 1, surface->format);
            ਜੇ (!tmp) {
                ਜਾਓ error;
            }

            // Share the palette, if any
            ਜੇ (surface->palette) {
                SDL_ਸੈੱਟ_Surface_Palette(tmp, surface->palette);
            }

            SDL_FillSurfaceRect(tmp, ਨਿਰਾ, surface->map.info.colorkey);

            tmp->map.info.flags &= ~SDL_COPY_COLORKEY;

            // Conversion of the colorkey
            tmp2 = SDL_ConvertSurfaceAndColorspace(tmp, format, palette, colorspace, props);
            ਜੇ (!tmp2) {
                SDL_DestroySurface(tmp);
                ਜਾਓ error;
            }

            // Get the converted colorkey
            SDL_memcpy(&converted_colorkey, tmp2->pixels, tmp2->fmt->ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel);

            SDL_DestroySurface(tmp);
            SDL_DestroySurface(tmp2);

            // Set the converted colorkey on the new surface
            SDL_ਸੈੱਟ_Surface_Color_ਕੁੰਜੀ(convert, true, converted_colorkey);

            // This is needed when converting for 3D texture upload
            ਜੇ (convert_colorkey) {
                SDL_Convert_Colorkey_ਮੰਜ਼ਿਲ_Alpha(convert, true);
            }
        }
    }

ਸਿਰਾ:
    ਜੇ (ਆਰਜ਼ੀ_palette) {
        SDL_DestroyPalette(ਆਰਜ਼ੀ_palette);
    }

    SDL_ਸੈੱਟ_Surface_Clip_Rect(convert, &surface->clip_rect);

    /* Enable alpha blending by default if the new surface has an
     * alpha channel or alpha modulation */
    ਜੇ (SDL_ISPIXELFORMAT_ALPHA(format) ||
        (copy_flags & SDL_COPY_MODULATE_ALPHA)) {
        SDL_ਸੈੱਟ_Surface_Blend_ਬਹੁਲਕ(convert, SDL_BLENDMODE_BLEND);
    }
    ਜੇ (copy_flags & SDL_COPY_RLE_DESIRED) {
        SDL_ਸੈੱਟ_Surface_RLE(convert, true);
    }

    // Copy alternate images
    ਲਈ (ਪੂਰਨ i = 0; i < surface->ਅੰਕ_images; ++i) {
        ਜੇ (!SDL_ਜੋੜੋ_Surface_Alternate_Image(convert, surface->images[i])) {
            ਜਾਓ error;
        }
    }

    // Copy properties
    ਜੇ (surface->props) {
        ਜੇ (!SDL_CopyProperties(surface->props, SDL_GetSurfaceProperties(convert))) {
            ਜਾਓ error;
        }

        // Make sure the new surface doesn't reference an old SDL2 surface.
        SDL_ClearProperty(SDL_GetSurfaceProperties(convert), "sdl2-compat.surface2");
    }

    // We're ready to go!
    ਵਾਪਸ convert;

error:
    ਜੇ (ਆਰਜ਼ੀ_palette) {
        SDL_DestroyPalette(ਆਰਜ਼ੀ_palette);
    }
    ਜੇ (convert) {
        SDL_DestroySurface(convert);
    }
    ਵਾਪਸ ਨਿਰਾ;
}

SDL_Surface *SDL_ConvertSurfaceAndColorspace(SDL_Surface *surface, SDL_PixelFormat format, SDL_Palette *palette, SDL_Colorspace colorspace, SDL_PropertiesID props)
{
    ਵਾਪਸ SDL_ConvertSurfaceRectAndColorspace(surface, ਨਿਰਾ, format, palette, colorspace, props);
}

SDL_Surface *SDL_RotateSurface(SDL_Surface *surface, ਦਸ਼ਮਲਵ angle)
{
    SDL_Surface *rotated = ਨਿਰਾ;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        ਵਾਪਸ ਨਿਰਾ;
    }

    SDL_Rect rect_dest;
    ਦੁੱਗਣਾ cangle, sangle;
    SDL_FPoint center = { surface->w * 0.5f, surface->h * 0.5f };
    SDLgfx_rotozoom_Surface_ਮਾਪ_Trig(surface->w, surface->h, angle, &center, &rect_dest, &cangle, &sangle);

    // This function requires a 32-bit surface or 8-bit surface with a colorkey
    ਜੇ ((SDL_BITSPERPIXEL(surface->format) == 32 && SDL_PIXELLAYOUT(surface->format) == SDL_PACKEDLAYOUT_8888) ||
        (surface->format == SDL_PIXELFORMAT_INDEX8 && SDL_Surface_Has_Color_ਕੁੰਜੀ(surface))) {
        rotated = SDLgfx_rotateSurface(surface, angle, 1, 0, 0, &rect_dest, cangle, sangle, &center);
    } ਨਹੀਂਤਾਂ {
        SDL_Surface *convert = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);
        ਜੇ (convert) {
            SDL_Surface *tmp = SDLgfx_rotateSurface(convert, angle, 1, 0, 0, &rect_dest, cangle, sangle, &center);
            ਜੇ (tmp) {
                rotated = SDL_ConvertSurfaceAndColorspace(tmp, surface->format, surface->palette, surface->colorspace, surface->props);
                SDL_DestroySurface(tmp);
            }
            SDL_DestroySurface(convert);
        }
    }

    ਜੇ (rotated) {
        ਜੇ (SDL_HasProperty(surface->props, SDL_PROP_SURFACE_ROTATION_FLOAT)) {
            ਅਚਲ ਦਸ਼ਮਲਵ rotation = (SDL_Get_ਸੰਖਿਆ_Property(surface->props, SDL_PROP_SURFACE_ROTATION_FLOAT, 0) - angle);
            SDL_ਸੈੱਟ_Float_Property(SDL_GetSurfaceProperties(rotated), SDL_PROP_SURFACE_ROTATION_FLOAT, rotation);
        }
    }

    ਵਾਪਸ rotated;
}

SDL_Surface *SDL_DuplicateSurface(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਵਾਪਸ SDL_ConvertSurfaceAndColorspace(surface, surface->format, surface->palette, surface->colorspace, surface->props);
}

SDL_Surface *SDL_ScaleSurface(SDL_Surface *surface, ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, SDL_Scale_ਬਹੁਲਕ scale_ਬਹੁਲਕ)
{
    SDL_Surface *convert = ਨਿਰਾ;
    Uint32 copy_flags;
    SDL_Color copy_color;
    bool rc;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        ਜਾਓ error;
    }

    ਜੇ (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // We can't directly scale a YUV surface (yet!)
        SDL_Surface *tmp = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        ਜੇ (!tmp) {
            ਵਾਪਸ ਨਿਰਾ;
        }

        SDL_Surface *scaled = SDL_ScaleSurface(tmp, ਚੌੜਾਈ, ਉਚਾਈ, scale_ਬਹੁਲਕ);
        SDL_DestroySurface(tmp);
        ਜੇ (!scaled) {
            ਵਾਪਸ ਨਿਰਾ;
        }

        SDL_Surface *ਨਤੀਜਾ = SDL_ConvertSurfaceAndColorspace(scaled, surface->format, ਨਿਰਾ, surface->colorspace, surface->props);
        SDL_DestroySurface(scaled);
        ਵਾਪਸ ਨਤੀਜਾ;
    }

    ਜੇ (SDL_ISPIXELFORMAT_ਸੂਚਕਾਂਕਿਤ(surface->format)) {
        // Linear scaling requires conversion to RGBA and then slow pixel color lookup
        scale_ਬਹੁਲਕ = SDL_SCALEMODE_ਸਭ_ਤੋਂ_ਨੇੜੇ;
    }

    // Create a new surface with the desired size
    ਜੇ (surface->pixels || SDL_MUSTLOCK(surface)) {
        convert = SDL_CreateSurfaceUninitialized(ਚੌੜਾਈ, ਉਚਾਈ, surface->format);
    } ਨਹੀਂਤਾਂ {
        convert = SDL_CreateSurfaceFrom(ਚੌੜਾਈ, ਉਚਾਈ, surface->format, ਨਿਰਾ, 0);
    }
    ਜੇ (!convert) {
        ਜਾਓ error;
    }
    SDL_ਸੈੱਟ_Surface_Palette(convert, surface->palette);
    SDL_ਸੈੱਟ_Surface_Colorspace(convert, surface->colorspace);
    SDL_ਸੈੱਟ_Surface_RLE(convert, SDL_SurfaceHasRLE(surface));

    ਜੇ (surface->pixels || SDL_MUSTLOCK(surface)) {
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

        rc = SDL_BlitSurfaceScaled(surface, ਨਿਰਾ, convert, ਨਿਰਾ, scale_ਬਹੁਲਕ);

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
    } ਨਹੀਂਤਾਂ {
        rc = true;
    }

    // SDL_BlitSurfaceScaled failed, and so the conversion
    ਜੇ (!rc) {
        ਜਾਓ error;
    }

    // We're ready to go!
    ਵਾਪਸ convert;

error:
    ਜੇ (convert) {
        SDL_DestroySurface(convert);
    }
    ਵਾਪਸ ਨਿਰਾ;
}

SDL_Surface *SDL_ConvertSurfaceRect(SDL_Surface *surface, ਅਚਲ SDL_Rect *rect, SDL_PixelFormat format)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਵਾਪਸ SDL_ConvertSurfaceRectAndColorspace(surface, rect, format, ਨਿਰਾ, SDL_GetDefaultColorspaceForFormat(format), surface->props);
}

SDL_Surface *SDL_ConvertSurface(SDL_Surface *surface, SDL_PixelFormat format)
{
    ਵਾਪਸ SDL_ConvertSurfaceRect(surface, ਨਿਰਾ, format);
}

SDL_Surface *SDL_DuplicatePixels(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, SDL_PixelFormat format, SDL_Colorspace colorspace, ਖਾਲੀ *pixels, ਪੂਰਨ pitch)
{
    SDL_Surface *surface;
    ਜੇ (pixels) {
        surface = SDL_CreateSurfaceUninitialized(ਚੌੜਾਈ, ਉਚਾਈ, format);
    } ਨਹੀਂਤਾਂ {
        surface = SDL_CreateSurfaceFrom(ਚੌੜਾਈ, ਉਚਾਈ, format, ਨਿਰਾ, 0);
    }
    ਜੇ (!surface) {
        ਵਾਪਸ ਨਿਰਾ;
    }
    SDL_ਸੈੱਟ_Surface_Colorspace(surface, colorspace);

    ਜੇ (surface->pixels) {
        ਪੂਰਨ ਲੰਮਾਈ = ਚੌੜਾਈ * SDL_BYTESPERPIXEL(format);
        Uint8 *src = (Uint8 *)pixels;
        Uint8 *dst = (Uint8 *)surface->pixels;
        ਪੂਰਨ ਪੰਕਤੀਆਂ = ਉਚਾਈ;
        ਜਦੋਂ (ਪੰਕਤੀਆਂ--) {
            SDL_memcpy(dst, src, ਲੰਮਾਈ);
            dst += surface->pitch;
            src += pitch;
        }
    }
    ਵਾਪਸ surface;
}

bool SDL_ConvertPixelsAndColorspace(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ,
                      SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ਅਚਲ ਖਾਲੀ *src, ਪੂਰਨ src_pitch,
                      SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, ਖਾਲੀ *dst, ਪੂਰਨ dst_pitch)
{
    SDL_Surface src_surface;
    SDL_Surface dst_surface;
    SDL_Rect rect;
    ਖਾਲੀ *nonconst_src = (ਖਾਲੀ *)src;
    bool ਨਤੀਜਾ;

    CHECK_PARAM(!src) {
        ਵਾਪਸ SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!src_pitch) {
        ਵਾਪਸ SDL_InvalidParamError("src_pitch");
    }
    CHECK_PARAM(!dst) {
        ਵਾਪਸ SDL_InvalidParamError("dst");
    }
    CHECK_PARAM(!dst_pitch) {
        ਵਾਪਸ SDL_InvalidParamError("dst_pitch");
    }

    ਜੇ (src_colorspace == SDL_COLORSPACE_UNKNOWN) {
        src_colorspace = SDL_GetDefaultColorspaceForFormat(src_format);
    }
    ਜੇ (dst_colorspace == SDL_COLORSPACE_UNKNOWN) {
        dst_colorspace = SDL_GetDefaultColorspaceForFormat(dst_format);
    }

    ਜੇ (src_format == SDL_PIXELFORMAT_MJPG) {
        ਵਾਪਸ SDL_ConvertPixels_STB(ਚੌੜਾਈ, ਉਚਾਈ, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_HAVE_YUV
    ਜੇ (SDL_ISPIXELFORMAT_FOURCC(src_format) && SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        ਵਾਪਸ SDL_Convert_Pixels_YUV_ਮੰਜ਼ਿਲ_YUV(ਚੌੜਾਈ, ਉਚਾਈ, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_ISPIXELFORMAT_FOURCC(src_format)) {
        ਵਾਪਸ SDL_Convert_Pixels_YUV_ਮੰਜ਼ਿਲ_RGB(ਚੌੜਾਈ, ਉਚਾਈ, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        ਵਾਪਸ SDL_Convert_Pixels_RGB_ਮੰਜ਼ਿਲ_YUV(ਚੌੜਾਈ, ਉਚਾਈ, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    }
#ਨਹੀਂਤਾਂ
    ਜੇ (SDL_ISPIXELFORMAT_FOURCC(src_format) || SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("SDL not built with YUV support");
    }
#ਜੇ_ਅੰਤ

    // Fast path for same format copy
    ਜੇ (src_format == dst_format && src_colorspace == dst_colorspace) {
        ਜੇ (src_pitch == dst_pitch) {
            SDL_memcpy(dst, src, ਉਚਾਈ * src_pitch);
        } ਨਹੀਂਤਾਂ {
            ਪੂਰਨ i;
            ਅਚਲ ਪੂਰਨ bpp = SDL_BYTESPERPIXEL(src_format);
            ਚੌੜਾਈ *= bpp;
            ਲਈ (i = ਉਚਾਈ; i--;) {
                SDL_memcpy(dst, src, ਚੌੜਾਈ);
                src = (ਅਚਲ Uint8 *)src + src_pitch;
                dst = (Uint8 *)dst + dst_pitch;
            }
        }
        ਵਾਪਸ true;
    }

    ਜੇ (!SDL_InitializeSurface(&src_surface, ਚੌੜਾਈ, ਉਚਾਈ, src_format, src_colorspace, src_properties, nonconst_src, src_pitch, true)) {
        ਵਾਪਸ false;
    }
    SDL_ਸੈੱਟ_Surface_Blend_ਬਹੁਲਕ(&src_surface, SDL_BLENDMODE_NONE);

    ਜੇ (!SDL_InitializeSurface(&dst_surface, ਚੌੜਾਈ, ਉਚਾਈ, dst_format, dst_colorspace, dst_properties, dst, dst_pitch, true)) {
        ਵਾਪਸ false;
    }

    // Set up the rect and go!
    rect.x = 0;
    rect.y = 0;
    rect.w = ਚੌੜਾਈ;
    rect.h = ਉਚਾਈ;
    ਨਤੀਜਾ = SDL_BlitSurfaceUnchecked(&src_surface, &rect, &dst_surface, &rect);

    SDL_DestroySurface(&src_surface);
    SDL_DestroySurface(&dst_surface);

    ਵਾਪਸ ਨਤੀਜਾ;
}

bool SDL_ConvertPixels(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, SDL_PixelFormat src_format, ਅਚਲ ਖਾਲੀ *src, ਪੂਰਨ src_pitch, SDL_PixelFormat dst_format, ਖਾਲੀ *dst, ਪੂਰਨ dst_pitch)
{
    ਵਾਪਸ SDL_ConvertPixelsAndColorspace(ਚੌੜਾਈ, ਉਚਾਈ,
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

ਸਥਿਰ ਖਾਲੀ SDL_PremultiplyAlpha_AXYZ8888(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, ਅਚਲ ਖਾਲੀ *src, ਪੂਰਨ src_pitch, ਖਾਲੀ *dst, ਪੂਰਨ dst_pitch)
{
    ਪੂਰਨ c;
    Uint32 srcpixel;
    Uint32 srcR, srcG, srcB, srcA;
    Uint32 dstpixel;
    Uint32 dstR, dstG, dstB, dstA;

    ਜਦੋਂ (ਉਚਾਈ--) {
        ਅਚਲ Uint32 *src_px = (ਅਚਲ Uint32 *)src;
        Uint32 *dst_px = (Uint32 *)dst;
        ਲਈ (c = ਚੌੜਾਈ; c; --c) {
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
        src = (ਅਚਲ Uint8 *)src + src_pitch;
        dst = (Uint8 *)dst + dst_pitch;
    }
}

ਸਥਿਰ ਖਾਲੀ SDL_PremultiplyAlpha_XYZA8888(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, ਅਚਲ ਖਾਲੀ *src, ਪੂਰਨ src_pitch, ਖਾਲੀ *dst, ਪੂਰਨ dst_pitch)
{
    ਪੂਰਨ c;
    Uint32 srcpixel;
    Uint32 srcR, srcG, srcB, srcA;
    Uint32 dstpixel;
    Uint32 dstR, dstG, dstB, dstA;

    ਜਦੋਂ (ਉਚਾਈ--) {
        ਅਚਲ Uint32 *src_px = (ਅਚਲ Uint32 *)src;
        Uint32 *dst_px = (Uint32 *)dst;
        ਲਈ (c = ਚੌੜਾਈ; c; --c) {
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
        src = (ਅਚਲ Uint8 *)src + src_pitch;
        dst = (Uint8 *)dst + dst_pitch;
    }
}

ਸਥਿਰ ਖਾਲੀ SDL_PremultiplyAlpha_AXYZ128(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, ਅਚਲ ਖਾਲੀ *src, ਪੂਰਨ src_pitch, ਖਾਲੀ *dst, ਪੂਰਨ dst_pitch)
{
    ਪੂਰਨ c;
    ਦਸ਼ਮਲਵ flR, flG, flB, flA;

    ਜਦੋਂ (ਉਚਾਈ--) {
        ਅਚਲ ਦਸ਼ਮਲਵ *src_px = (ਅਚਲ ਦਸ਼ਮਲਵ *)src;
        ਦਸ਼ਮਲਵ *dst_px = (ਦਸ਼ਮਲਵ *)dst;
        ਲਈ (c = ਚੌੜਾਈ; c; --c) {
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
        src = (ਅਚਲ Uint8 *)src + src_pitch;
        dst = (Uint8 *)dst + dst_pitch;
    }
}

ਸਥਿਰ bool SDL_PremultiplyAlphaPixelsAndColorspace(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ਅਚਲ ਖਾਲੀ *src, ਪੂਰਨ src_pitch, SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, ਖਾਲੀ *dst, ਪੂਰਨ dst_pitch, bool ਰੇਖਿਕ)
{
    SDL_Surface *convert = ਨਿਰਾ;
    ਖਾਲੀ *final_dst = dst;
    ਪੂਰਨ final_dst_pitch = dst_pitch;
    SDL_PixelFormat format;
    SDL_Colorspace colorspace;
    bool ਨਤੀਜਾ = false;

    CHECK_PARAM(!src) {
        ਵਾਪਸ SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!src_pitch) {
        ਵਾਪਸ SDL_InvalidParamError("src_pitch");
    }
    CHECK_PARAM(!dst) {
        ਵਾਪਸ SDL_InvalidParamError("dst");
    }
    CHECK_PARAM(!dst_pitch) {
        ਵਾਪਸ SDL_InvalidParamError("dst_pitch");
    }

    // Use a high precision format if we're converting to linear colorspace or using high precision pixel formats
    ਜੇ (ਰੇਖਿਕ ||
        SDL_ISPIXELFORMAT_10_ਦੋਆਧਾਰੀ_ਅੰਕ(src_format) || SDL_BITSPERPIXEL(src_format) > 32 ||
        SDL_ISPIXELFORMAT_10_ਦੋਆਧਾਰੀ_ਅੰਕ(dst_format) || SDL_BITSPERPIXEL(dst_format) > 32) {
        ਜੇ (src_format == SDL_PIXELFORMAT_ARGB128_FLOAT ||
            src_format == SDL_PIXELFORMAT_ABGR128_FLOAT) {
            format = src_format;
        } ਨਹੀਂਤਾਂ {
            format = SDL_PIXELFORMAT_ARGB128_FLOAT;
        }
    } ਨਹੀਂਤਾਂ {
        ਜੇ (src_format == SDL_PIXELFORMAT_ARGB8888 ||
            src_format == SDL_PIXELFORMAT_ABGR8888 ||
            src_format == SDL_PIXELFORMAT_RGBA8888 ||
            src_format == SDL_PIXELFORMAT_BGRA8888) {
            format = src_format;
        } ਨਹੀਂਤਾਂ {
            format = SDL_PIXELFORMAT_ARGB8888;
        }
    }
    ਜੇ (ਰੇਖਿਕ) {
        colorspace = SDL_COLORSPACE_SRGB_ਰੇਖਿਕ;
    } ਨਹੀਂਤਾਂ {
        colorspace = SDL_COLORSPACE_SRGB;
    }

    ਜੇ (src_format != format || src_colorspace != colorspace) {
        convert = SDL_CreateSurfaceUninitialized(ਚੌੜਾਈ, ਉਚਾਈ, format);
        ਜੇ (!convert) {
            ਜਾਓ ਪੂਰਾ;
        }
        ਜੇ (!SDL_ConvertPixelsAndColorspace(ਚੌੜਾਈ, ਉਚਾਈ, src_format, src_colorspace, src_properties, src, src_pitch, format, colorspace, 0, convert->pixels, convert->pitch)) {
            ਜਾਓ ਪੂਰਾ;
        }

        src = convert->pixels;
        src_pitch = convert->pitch;
        dst = convert->pixels;
        dst_pitch = convert->pitch;

    } ਨਹੀਂਤਾਂ ਜੇ (dst_format != format || dst_colorspace != colorspace) {
        convert = SDL_CreateSurfaceUninitialized(ਚੌੜਾਈ, ਉਚਾਈ, format);
        ਜੇ (!convert) {
            ਜਾਓ ਪੂਰਾ;
        }
        dst = convert->pixels;
        dst_pitch = convert->pitch;
    }

    ਚੋਣ (format) {
    ਹਾਲਤ SDL_PIXELFORMAT_ARGB8888:
    ਹਾਲਤ SDL_PIXELFORMAT_ABGR8888:
        SDL_PremultiplyAlpha_AXYZ8888(ਚੌੜਾਈ, ਉਚਾਈ, src, src_pitch, dst, dst_pitch);
        ਰੋਕੋ;
    ਹਾਲਤ SDL_PIXELFORMAT_RGBA8888:
    ਹਾਲਤ SDL_PIXELFORMAT_BGRA8888:
        SDL_PremultiplyAlpha_XYZA8888(ਚੌੜਾਈ, ਉਚਾਈ, src, src_pitch, dst, dst_pitch);
        ਰੋਕੋ;
    ਹਾਲਤ SDL_PIXELFORMAT_ARGB128_FLOAT:
    ਹਾਲਤ SDL_PIXELFORMAT_ABGR128_FLOAT:
        SDL_PremultiplyAlpha_AXYZ128(ਚੌੜਾਈ, ਉਚਾਈ, src, src_pitch, dst, dst_pitch);
        ਰੋਕੋ;
    ਮੂਲ:
        SDL_ਸੈੱਟ_Error("Unexpected internal pixel format");
        ਜਾਓ ਪੂਰਾ;
    }

    ਜੇ (dst != final_dst) {
        ਜੇ (!SDL_ConvertPixelsAndColorspace(ਚੌੜਾਈ, ਉਚਾਈ, format, colorspace, 0, convert->pixels, convert->pitch, dst_format, dst_colorspace, dst_properties, final_dst, final_dst_pitch)) {
            ਜਾਓ ਪੂਰਾ;
        }
    }
    ਨਤੀਜਾ = true;

ਪੂਰਾ:
    ਜੇ (convert) {
        SDL_DestroySurface(convert);
    }
    ਵਾਪਸ ਨਤੀਜਾ;
}

bool SDL_PremultiplyAlpha(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ,
                         SDL_PixelFormat src_format, ਅਚਲ ਖਾਲੀ *src, ਪੂਰਨ src_pitch,
                         SDL_PixelFormat dst_format, ਖਾਲੀ *dst, ਪੂਰਨ dst_pitch, bool ਰੇਖਿਕ)
{
    SDL_Colorspace src_colorspace = SDL_GetDefaultColorspaceForFormat(src_format);
    SDL_Colorspace dst_colorspace = SDL_GetDefaultColorspaceForFormat(dst_format);

    ਵਾਪਸ SDL_PremultiplyAlphaPixelsAndColorspace(ਚੌੜਾਈ, ਉਚਾਈ, src_format, src_colorspace, 0, src, src_pitch, dst_format, dst_colorspace, 0, dst, dst_pitch, ਰੇਖਿਕ);
}

bool SDL_PremultiplySurfaceAlpha(SDL_Surface *surface, bool ਰੇਖਿਕ)
{
    SDL_Colorspace colorspace;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ਵਾਪਸ SDL_InvalidParamError("surface");
    }

    colorspace = surface->colorspace;

    ਵਾਪਸ SDL_PremultiplyAlphaPixelsAndColorspace(surface->w, surface->h, surface->format, colorspace, surface->props, surface->pixels, surface->pitch, surface->format, colorspace, surface->props, surface->pixels, surface->pitch, ਰੇਖਿਕ);
}

bool SDL_ClearSurface(SDL_Surface *surface, ਦਸ਼ਮਲਵ r, ਦਸ਼ਮਲਵ g, ਦਸ਼ਮਲਵ b, ਦਸ਼ਮਲਵ a)
{
    SDL_Rect clip_rect;
    bool ਨਤੀਜਾ = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ਵਾਪਸ SDL_InvalidParamError("surface");
    }

    SDL_GetSurfaceClipRect(surface, &clip_rect);
    SDL_ਸੈੱਟ_Surface_Clip_Rect(surface, ਨਿਰਾ);

    ਜੇ (!SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_BYTESPERPIXEL(surface->format) <= ਆਕਾਰ(Uint32)) {
        Uint32 color;

        color = SDL_MapSurfaceRGBA(surface,
                    (Uint8)SDL_roundf(SDL_clamp(r, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(g, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(b, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(a, 0.0f, 1.0f) * 255.0f));
        ਨਤੀਜਾ = SDL_FillSurfaceRect(surface, ਨਿਰਾ, color);
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // We can't directly set an RGB value on a YUV surface
        SDL_Surface *tmp = SDL_CreateSurfaceUninitialized(surface->w, surface->h, SDL_PIXELFORMAT_ARGB8888);
        ਜੇ (!tmp) {
            ਜਾਓ ਪੂਰਾ;
        }

        ਜੇ (SDL_ClearSurface(tmp, r, g, b, a)) {
            ਨਤੀਜਾ = SDL_ConvertPixelsAndColorspace(surface->w, surface->h, tmp->format, tmp->colorspace, tmp->props, tmp->pixels, tmp->pitch, surface->format, surface->colorspace, surface->props, surface->pixels, surface->pitch);
        }
        SDL_DestroySurface(tmp);
    } ਨਹੀਂਤਾਂ {
        // Take advantage of blit color conversion
        SDL_Surface *tmp = SDL_CreateSurfaceUninitialized(1, 1, SDL_PIXELFORMAT_RGBA128_FLOAT);
        ਜੇ (!tmp) {
            ਜਾਓ ਪੂਰਾ;
        }
        SDL_ਸੈੱਟ_Surface_Colorspace(tmp, surface->colorspace);
        SDL_ਸੈੱਟ_Surface_Blend_ਬਹੁਲਕ(tmp, SDL_BLENDMODE_NONE);

        ਦਸ਼ਮਲਵ *pixels = (ਦਸ਼ਮਲਵ *)tmp->pixels;
        pixels[0] = r;
        pixels[1] = g;
        pixels[2] = b;
        pixels[3] = a;

        ਨਤੀਜਾ = SDL_BlitSurfaceScaled(tmp, ਨਿਰਾ, surface, ਨਿਰਾ, SDL_SCALEMODE_ਸਭ_ਤੋਂ_ਨੇੜੇ);
        SDL_DestroySurface(tmp);
    }

ਪੂਰਾ:
    SDL_ਸੈੱਟ_Surface_Clip_Rect(surface, &clip_rect);

    ਵਾਪਸ ਨਤੀਜਾ;
}

Uint32 SDL_MapSurfaceRGB(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b)
{
    ਵਾਪਸ SDL_MapSurfaceRGBA(surface, r, g, b, SDL_ALPHA_OPAQUE);
}

Uint32 SDL_MapSurfaceRGBA(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        ਵਾਪਸ true;
    }
    ਵਾਪਸ SDL_MapRGBA(surface->fmt, surface->palette, r, g, b, a);
}

// This function Copyright 2023 Collabora Ltd., contributed to SDL under the ZLib license
bool SDL_ReadSurfacePixel(SDL_Surface *surface, ਪੂਰਨ x, ਪੂਰਨ y, Uint8 *r, Uint8 *g, Uint8 *b, Uint8 *a)
{
    Uint32 pixel = 0;
    size_t ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel;
    Uint8 ਅਣਵਰਤਿਆ;
    Uint8 *p;
    bool ਨਤੀਜਾ = false;

    ਜੇ (r) {
        *r = 0;
    } ਨਹੀਂਤਾਂ {
        r = &ਅਣਵਰਤਿਆ;
    }

    ਜੇ (g) {
        *g = 0;
    } ਨਹੀਂਤਾਂ {
        g = &ਅਣਵਰਤਿਆ;
    }

    ਜੇ (b) {
        *b = 0;
    } ਨਹੀਂਤਾਂ {
        b = &ਅਣਵਰਤਿਆ;
    }

    ਜੇ (a) {
        *a = 0;
    } ਨਹੀਂਤਾਂ {
        a = &ਅਣਵਰਤਿਆ;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        ਵਾਪਸ SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        ਵਾਪਸ SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        ਵਾਪਸ SDL_InvalidParamError("y");
    }

    ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel = SDL_BYTESPERPIXEL(surface->format);

    ਜੇ (SDL_MUSTLOCK(surface)) {
        ਜੇ (!SDL_ਤਾਲਾ_Surface(surface)) {
            ਵਾਪਸ false;
        }
    }

    p = (Uint8 *)surface->pixels + y * surface->pitch + x * ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel;

    ਜੇ (ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel <= ਆਕਾਰ(pixel) &&
        !SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_COLORSPACEPRIMARIES(surface->colorspace) == SDL_COLOR_PRIMARIES_BT709) {
        /* Fill the appropriate number of least-significant bytes of pixel,
         * leaving the most-significant bytes set to zero */
#ਜੇ SDL_BYTEORDER == SDL_BIG_ENDIAN
        SDL_memcpy(((Uint8 *)&pixel) + (ਆਕਾਰ(pixel) - ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel), p, ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel);
#ਨਹੀਂਤਾਂ
        SDL_memcpy(&pixel, p, ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel);
#ਜੇ_ਅੰਤ
        SDL_GetRGBA(pixel, surface->fmt, surface->palette, r, g, b, a);
        ਨਤੀਜਾ = true;
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // FIXME: We need code to extract a single macroblock from a YUV surface
        SDL_Surface *converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        ਜੇ (converted) {
            ਨਤੀਜਾ = SDL_ReadSurfacePixel(converted, x, y, r, g, b, a);
            SDL_DestroySurface(converted);
        }
    } ਨਹੀਂਤਾਂ {
        // This is really slow, but it gets the job done
        Uint8 rgba[4];

        ਜੇ (SDL_ConvertPixelsAndColorspace(1, 1, surface->format, surface->colorspace, surface->props, p, surface->pitch, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, rgba, ਆਕਾਰ(rgba))) {
            *r = rgba[0];
            *g = rgba[1];
            *b = rgba[2];
            *a = rgba[3];
            ਨਤੀਜਾ = true;
        }
    }

    ਜੇ (SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }
    ਵਾਪਸ ਨਤੀਜਾ;
}

bool SDL_ReadSurfacePixelFloat(SDL_Surface *surface, ਪੂਰਨ x, ਪੂਰਨ y, ਦਸ਼ਮਲਵ *r, ਦਸ਼ਮਲਵ *g, ਦਸ਼ਮਲਵ *b, ਦਸ਼ਮਲਵ *a)
{
    ਦਸ਼ਮਲਵ ਅਣਵਰਤਿਆ;
    bool ਨਤੀਜਾ = false;

    ਜੇ (r) {
        *r = 0.0f;
    } ਨਹੀਂਤਾਂ {
        r = &ਅਣਵਰਤਿਆ;
    }

    ਜੇ (g) {
        *g = 0.0f;
    } ਨਹੀਂਤਾਂ {
        g = &ਅਣਵਰਤਿਆ;
    }

    ਜੇ (b) {
        *b = 0.0f;
    } ਨਹੀਂਤਾਂ {
        b = &ਅਣਵਰਤਿਆ;
    }

    ਜੇ (a) {
        *a = 0.0f;
    } ਨਹੀਂਤਾਂ {
        a = &ਅਣਵਰਤਿਆ;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        ਵਾਪਸ SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        ਵਾਪਸ SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        ਵਾਪਸ SDL_InvalidParamError("y");
    }

    ਜੇ (SDL_BYTESPERPIXEL(surface->format) <= ਆਕਾਰ(Uint32) &&
        !SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_COLORSPACEPRIMARIES(surface->colorspace) == SDL_COLOR_PRIMARIES_BT709) {
        Uint8 r8, g8, b8, a8;

        ਜੇ (SDL_ReadSurfacePixel(surface, x, y, &r8, &g8, &b8, &a8)) {
            *r = (ਦਸ਼ਮਲਵ)r8 / 255.0f;
            *g = (ਦਸ਼ਮਲਵ)g8 / 255.0f;
            *b = (ਦਸ਼ਮਲਵ)b8 / 255.0f;
            *a = (ਦਸ਼ਮਲਵ)a8 / 255.0f;
            ਨਤੀਜਾ = true;
        }
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // FIXME: We need code to extract a single macroblock from a YUV surface
        SDL_Surface *converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        ਜੇ (converted) {
            ਨਤੀਜਾ = SDL_ReadSurfacePixelFloat(converted, x, y, r, g, b, a);
            SDL_DestroySurface(converted);
        }
    } ਨਹੀਂਤਾਂ {
        // This is really slow, but it gets the job done
        ਦਸ਼ਮਲਵ rgba[4];
        Uint8 *p;

        ਜੇ (SDL_MUSTLOCK(surface)) {
            ਜੇ (!SDL_ਤਾਲਾ_Surface(surface)) {
                ਵਾਪਸ false;
            }
        }

        p = (Uint8 *)surface->pixels + y * surface->pitch + x * SDL_BYTESPERPIXEL(surface->format);

        ਜੇ (surface->format == SDL_PIXELFORMAT_RGBA128_FLOAT) {
            SDL_memcpy(rgba, p, ਆਕਾਰ(rgba));
            ਨਤੀਜਾ = true;
        } ਨਹੀਂਤਾਂ {
            SDL_Colorspace src_colorspace = surface->colorspace;
            SDL_Colorspace dst_colorspace = (src_colorspace == SDL_COLORSPACE_SRGB_ਰੇਖਿਕ ? SDL_COLORSPACE_SRGB_ਰੇਖਿਕ : SDL_COLORSPACE_SRGB);

            ਜੇ (SDL_ConvertPixelsAndColorspace(1, 1, surface->format, src_colorspace, surface->props, p, surface->pitch, SDL_PIXELFORMAT_RGBA128_FLOAT, dst_colorspace, 0, rgba, ਆਕਾਰ(rgba))) {
                ਨਤੀਜਾ = true;
            }
        }

        ਜੇ (ਨਤੀਜਾ) {
            *r = rgba[0];
            *g = rgba[1];
            *b = rgba[2];
            *a = rgba[3];
        }

        ਜੇ (SDL_MUSTLOCK(surface)) {
            SDL_UnlockSurface(surface);
        }
    }
    ਵਾਪਸ ਨਤੀਜਾ;
}

bool SDL_WriteSurfacePixel(SDL_Surface *surface, ਪੂਰਨ x, ਪੂਰਨ y, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    Uint32 pixel = 0;
    size_t ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel;
    Uint8 *p;
    bool ਨਤੀਜਾ = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        ਵਾਪਸ SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        ਵਾਪਸ SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        ਵਾਪਸ SDL_InvalidParamError("y");
    }

    ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel = SDL_BYTESPERPIXEL(surface->format);

    ਜੇ (SDL_MUSTLOCK(surface)) {
        ਜੇ (!SDL_ਤਾਲਾ_Surface(surface)) {
            ਵਾਪਸ false;
        }
    }

    p = (Uint8 *)surface->pixels + y * surface->pitch + x * ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel;

    ਜੇ (ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel <= ਆਕਾਰ(pixel) && !SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        pixel = SDL_MapRGBA(surface->fmt, surface->palette, r, g, b, a);
#ਜੇ SDL_BYTEORDER == SDL_BIG_ENDIAN
        SDL_memcpy(p, ((Uint8 *)&pixel) + (ਆਕਾਰ(pixel) - ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel), ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel);
#ਨਹੀਂਤਾਂ
        SDL_memcpy(p, &pixel, ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel);
#ਜੇ_ਅੰਤ
        ਨਤੀਜਾ = true;
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        ਨਤੀਜਾ = SDL_Unsupported();
    } ਨਹੀਂਤਾਂ {
        // This is really slow, but it gets the job done
        Uint8 rgba[4];

        rgba[0] = r;
        rgba[1] = g;
        rgba[2] = b;
        rgba[3] = a;
        ਨਤੀਜਾ = SDL_ConvertPixelsAndColorspace(1, 1, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, rgba, ਆਕਾਰ(rgba), surface->format, surface->colorspace, surface->props, p, surface->pitch);
    }

    ਜੇ (SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }
    ਵਾਪਸ ਨਤੀਜਾ;
}

bool SDL_WriteSurfacePixelFloat(SDL_Surface *surface, ਪੂਰਨ x, ਪੂਰਨ y, ਦਸ਼ਮਲਵ r, ਦਸ਼ਮਲਵ g, ਦਸ਼ਮਲਵ b, ਦਸ਼ਮਲਵ a)
{
    bool ਨਤੀਜਾ = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        ਵਾਪਸ SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        ਵਾਪਸ SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        ਵਾਪਸ SDL_InvalidParamError("y");
    }

    ਜੇ (SDL_BYTESPERPIXEL(surface->format) <= ਆਕਾਰ(Uint32) && !SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        Uint8 r8, g8, b8, a8;

        r8 = (Uint8)SDL_ਗੇੜਾ(SDL_clamp(r, 0.0f, 1.0f) * 255.0f);
        g8 = (Uint8)SDL_ਗੇੜਾ(SDL_clamp(g, 0.0f, 1.0f) * 255.0f);
        b8 = (Uint8)SDL_ਗੇੜਾ(SDL_clamp(b, 0.0f, 1.0f) * 255.0f);
        a8 = (Uint8)SDL_ਗੇੜਾ(SDL_clamp(a, 0.0f, 1.0f) * 255.0f);
        ਜੇ (SDL_WriteSurfacePixel(surface, x, y, r8, g8, b8, a8)) {
            ਨਤੀਜਾ = true;
        }
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        ਨਤੀਜਾ = SDL_Unsupported();
    } ਨਹੀਂਤਾਂ {
        // This is really slow, but it gets the job done
        ਦਸ਼ਮਲਵ rgba[4];
        Uint8 *p;

        ਜੇ (SDL_MUSTLOCK(surface)) {
            ਜੇ (!SDL_ਤਾਲਾ_Surface(surface)) {
                ਵਾਪਸ false;
            }
        }

        p = (Uint8 *)surface->pixels + y * surface->pitch + x * SDL_BYTESPERPIXEL(surface->format);

        rgba[0] = r;
        rgba[1] = g;
        rgba[2] = b;
        rgba[3] = a;

        ਜੇ (surface->format == SDL_PIXELFORMAT_RGBA128_FLOAT) {
            SDL_memcpy(p, rgba, ਆਕਾਰ(rgba));
            ਨਤੀਜਾ = true;
        } ਨਹੀਂਤਾਂ {
            SDL_Colorspace dst_colorspace = surface->colorspace;
            SDL_Colorspace src_colorspace = (dst_colorspace == SDL_COLORSPACE_SRGB_ਰੇਖਿਕ ? SDL_COLORSPACE_SRGB_ਰੇਖਿਕ : SDL_COLORSPACE_SRGB);

            ਨਤੀਜਾ = SDL_ConvertPixelsAndColorspace(1, 1, SDL_PIXELFORMAT_RGBA128_FLOAT, src_colorspace, 0, rgba, ਆਕਾਰ(rgba), surface->format, dst_colorspace, surface->props, p, surface->pitch);
        }

        ਜੇ (SDL_MUSTLOCK(surface)) {
            SDL_UnlockSurface(surface);
        }
    }
    ਵਾਪਸ ਨਤੀਜਾ;
}

/*
 * Free a surface created by the above function.
 */
ਖਾਲੀ SDL_DestroySurface(SDL_Surface *surface)
{
    ਜੇ (!SDL_SurfaceValid(surface)) {
        ਵਾਪਸ;
    }
    ਜੇ (surface->ਅੰਦਰੂਨੀ_flags & SDL_ਅੰਦਰੂਨੀ_SURFACE_DONTFREE) {
        ਵਾਪਸ;
    }
    ਜੇ (--surface->refcount > 0) {
        ਵਾਪਸ;
    }

    SDL_RemoveSurfaceAlternateImages(surface);

    SDL_DestroyProperties(surface->props);

    SDL_InvalidateMap(&surface->map);

    ਜਦੋਂ (surface->locked > 0) {
        SDL_UnlockSurface(surface);
    }
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_HAVE_RLE
    ਜੇ (surface->ਅੰਦਰੂਨੀ_flags & SDL_ਅੰਦਰੂਨੀ_SURFACE_RLEACCEL) {
        SDL_UnRLESurface(surface);
    }
#ਜੇ_ਅੰਤ
    SDL_ਸੈੱਟ_Surface_Palette(surface, ਨਿਰਾ);

    ਜੇ (surface->flags & SDL_SURFACE_PREALLOCATED) {
        // Don't free
    } ਨਹੀਂਤਾਂ ਜੇ (surface->flags & SDL_SURFACE_SIMD_ALIGNED) {
        // Free aligned
        SDL_aligned_free(surface->pixels);
    } ਨਹੀਂਤਾਂ {
        // Normal
        SDL_free(surface->pixels);
    }

    surface->reserved = ਨਿਰਾ;

    ਜੇ (!(surface->ਅੰਦਰੂਨੀ_flags & SDL_ਅੰਦਰੂਨੀ_SURFACE_ਢੇਰ)) {
        SDL_free(surface);
    }
}

SDL_Surface *SDL_ਲੱਦੋ_Surface_IO(SDL_IOStream *src, bool closeio)
{
    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਜੇ (SDL_IsBMP(src)) {
        ਵਾਪਸ SDL_ਲੱਦੋ_BMP_IO(src, closeio);
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_IsPNG(src)) {
        ਵਾਪਸ SDL_ਲੱਦੋ_PNG_IO(src, closeio);
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_IsJPG(src)) {
        ਵਾਪਸ SDL_ਲੱਦੋ_JPG_IO(src, closeio);
    } ਨਹੀਂਤਾਂ {
        ਜੇ (closeio) {
            SDL_CloseIO(src);
        }
        SDL_ਸੈੱਟ_Error("Unsupported image format");
        ਵਾਪਸ ਨਿਰਾ;
    }
}

SDL_Surface *SDL_ਲੱਦੋ_Surface(ਅਚਲ ਅੱਖਰ *file)
{
    SDL_IOStream *ਧਾਰਾ = SDL_IOFromFile(file, "rb");
    ਜੇ (!ਧਾਰਾ) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਵਾਪਸ SDL_ਲੱਦੋ_Surface_IO(ਧਾਰਾ, true);
}
