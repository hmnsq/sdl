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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ಅನ್ತರ್ಭಾವ "SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_video_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_RLEaccel_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_pixels_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_rotate.h"
#ಅನ್ತರ್ಭಾವ "SDL_stb_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_yuv_c.h"
#ಅನ್ತರ್ಭಾವ "../render/SDL_sysrender.h"

#ಅನ್ತರ್ಭಾವ "SDL_surface_c.h"


// Check to make sure we can safely check multiplication of surface w and pitch and it won't overflow size_t
SDL_COMPILE_ಸಮಯ_ASSERT(surface_ಗಾತ್ರ_assumptions,
                        ಗಾತ್ರ(ಪೂರ್ಣಾಂಕ) == ಗಾತ್ರ(Sint32) && ಗಾತ್ರ(size_t) >= ಗಾತ್ರ(Sint32));

SDL_COMPILE_ಸಮಯ_ASSERT(can_indicate_ಅತಿಪ್ರವಾಹ, SDL_ಗಾತ್ರ_MAX > SDL_MAX_SINT32);

// Magic!
ಸ್ಥಿರ ಅಕ್ಷರ SDL_surface_magic;

// Public routines

bool SDL_SurfaceValid(SDL_Surface *surface)
{
    ಹಿಂತಿರುಗಿ (surface && surface->reserved == &SDL_surface_magic);
}

ಶೂನ್ಯ SDL_Update_Surface_ಬೀಗ_Flag(SDL_Surface *surface)
{
    // We need to mark the surface as needing unlock while locked
    ಆದರೆ ((surface->flags & SDL_SURFACE_LOCKED) ||
        (surface->ಆಂತರಿಕ_flags & SDL_ಆಂತರಿಕ_SURFACE_RLEACCEL)) {
        surface->flags |= SDL_SURFACE_ಬೀಗ_NEEDED;
    } ಇಲ್ಲದಿದ್ದರೆ {
        surface->flags &= ~SDL_SURFACE_ಬೀಗ_NEEDED;
    }
}

/*
 * Calculate the pad-aligned scanline width of a surface.
 *
 * for FOURCC, use SDL_CalculateYUVSize()
 */
ಸ್ಥಿರ bool SDL_CalculateRGBSize(Uint32 format, size_t ಅಗಲ, size_t ಎತ್ತರ, size_t *ಗಾತ್ರ_2, size_t *pitch, bool ಕನಿಷ್ಠತಮ)
{
    ಆದರೆ (SDL_BITSPERPIXEL(format) >= 8) {
        ಆದರೆ (!SDL_ಗಾತ್ರ_mul_check_ಅತಿಪ್ರವಾಹ(ಅಗಲ, SDL_BYTESPERPIXEL(format), pitch)) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("width * bpp would overflow");
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (!SDL_ಗಾತ್ರ_mul_check_ಅತಿಪ್ರವಾಹ(ಅಗಲ, SDL_BITSPERPIXEL(format), pitch)) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("width * bpp would overflow");
        }
        ಆದರೆ (!SDL_ಗಾತ್ರ_ಕೂಡಿಸು_check_ಅತಿಪ್ರವಾಹ(*pitch, 7, pitch)) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("aligning pitch would overflow");
        }
        *pitch /= 8;
    }
    ಆದರೆ (!ಕನಿಷ್ಠತಮ) {
        // 4-byte aligning for speed
        ಆದರೆ (!SDL_ಗಾತ್ರ_ಕೂಡಿಸು_check_ಅತಿಪ್ರವಾಹ(*pitch, 3, pitch)) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("aligning pitch would overflow");
        }
        *pitch &= ~3;
    }

    ಆದರೆ (!SDL_ಗಾತ್ರ_mul_check_ಅತಿಪ್ರವಾಹ(ಎತ್ತರ, *pitch, ಗಾತ್ರ_2)) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("height * pitch would overflow");
    }

    ಹಿಂತಿರುಗಿ true;
}

bool SDL_Calculate_Surface_ಗಾತ್ರ(SDL_PixelFormat format, ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, size_t *ಗಾತ್ರ_2, size_t *pitch, bool ಕನಿಷ್ಠತಮ_Pitch)
{
    size_t p = 0, sz = 0;

    ಆದರೆ (ಗಾತ್ರ_2) {
        *ಗಾತ್ರ_2 = 0;
    }

    ಆದರೆ (pitch) {
        *pitch = 0;
    }

    ಆದರೆ (SDL_ISPIXELFORMAT_FOURCC(format)) {
        ಆದರೆ (format == SDL_PIXELFORMAT_MJPG) {
            // We don't know in advance what it will be, we'll figure it out later.
            ಹಿಂತಿರುಗಿ true;
        }

        ಆದರೆ (!SDL_CalculateYUVSize(format, ಅಗಲ, ಎತ್ತರ, &sz, &p)) {
            // Overflow...
            ಹಿಂತಿರುಗಿ false;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (!SDL_CalculateRGBSize(format, ಅಗಲ, ಎತ್ತರ, &sz, &p, ಕನಿಷ್ಠತಮ_Pitch)) {
            // Overflow...
            ಹಿಂತಿರುಗಿ false;
        }
    }

    ಆದರೆ (ಗಾತ್ರ_2) {
        *ಗಾತ್ರ_2 = sz;
    }

    ಆದರೆ (pitch) {
        *pitch = p;
    }

    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool SDL_InitializeSurface(SDL_Surface *surface, ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, SDL_PixelFormat format, SDL_Colorspace colorspace, SDL_PropertiesID props, ಶೂನ್ಯ *pixels, ಪೂರ್ಣಾಂಕ pitch, bool onstack)
{
    SDL_zerop(surface);

    surface->flags = SDL_SURFACE_PREALLOCATED;
    surface->format = format;
    surface->w = ಅಗಲ;
    surface->h = ಎತ್ತರ;
    surface->pixels = pixels;
    surface->pitch = pitch;
    surface->reserved = &SDL_surface_magic;

    ಆದರೆ (onstack) {
        surface->ಆಂತರಿಕ_flags |= SDL_ಆಂತರಿಕ_SURFACE_ರಾಶಿ;
    }

    surface->fmt = SDL_GetPixelFormatDetails(format);
    ಆದರೆ (!surface->fmt) {
        SDL_DestroySurface(surface);
        ಹಿಂತಿರುಗಿ false;
    }

    // Initialize the clip rect
    surface->clip_rect.w = ಅಗಲ;
    surface->clip_rect.h = ಎತ್ತರ;

    // Allocate an empty mapping
    surface->map.info.r = 0xFF;
    surface->map.info.g = 0xFF;
    surface->map.info.b = 0xFF;
    surface->map.info.a = 0xFF;

    ಆದರೆ (colorspace == SDL_COLORSPACE_UNKNOWN) {
        surface->colorspace = SDL_GetDefaultColorspaceForFormat(format);
    } ಇಲ್ಲದಿದ್ದರೆ {
        surface->colorspace = colorspace;
    }

    ಆದರೆ (props) {
        ಆದರೆ (!SDL_CopyProperties(props, SDL_GetSurfaceProperties(surface))) {
            SDL_DestroySurface(surface);
            ಹಿಂತಿರುಗಿ false;
        }
    }

    // By default surfaces with an alpha mask are set up for blending
    ಆದರೆ (SDL_ISPIXELFORMAT_ALPHA(surface->format)) {
        SDL_ಗಣ_Surface_Blend_ಬಹುಲಕ(surface, SDL_BLENDMODE_BLEND);
    }

    // The surface is ready to go
    surface->refcount = 1;
    ಹಿಂತಿರುಗಿ true;
}

/*
 * Create an empty surface of the appropriate depth using the given format
 */
ಸ್ಥಿರ SDL_Surface *SDL_Create_Surface_ಆಂತರಿಕ(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, SDL_PixelFormat format, bool clear_surface)
{
    size_t pitch, ಗಾತ್ರ_2;
    SDL_Surface *surface;

    CHECK_PARAM(ಅಗಲ < 0) {
        SDL_InvalidParamError("width");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    CHECK_PARAM(ಎತ್ತರ < 0) {
        SDL_InvalidParamError("height");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಆದರೆ (!SDL_Calculate_Surface_ಗಾತ್ರ(format, ಅಗಲ, ಎತ್ತರ, &ಗಾತ್ರ_2, &pitch, false /* not minimal pitch */)) {
        // Overflow...
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    // Allocate and initialize the surface
    surface = (SDL_Surface *)SDL_malloc(ಗಾತ್ರ(*surface));
    ಆದರೆ (!surface) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಆದರೆ (!SDL_InitializeSurface(surface, ಅಗಲ, ಎತ್ತರ, format, SDL_COLORSPACE_UNKNOWN, 0, ಖಾಲಿ, (ಪೂರ್ಣಾಂಕ)pitch, false)) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಆದರೆ (surface->w && surface->h && format != SDL_PIXELFORMAT_MJPG) {
        surface->flags &= ~SDL_SURFACE_PREALLOCATED;
        ಆದರೆ (SDL_GetHintBoolean("SDL_SURFACE_MALLOC", false)) {
            ಆದರೆ (clear_surface) {
                surface->pixels = SDL_calloc(1, ಗಾತ್ರ_2);
            } ಇಲ್ಲದಿದ್ದರೆ {
                surface->pixels = SDL_malloc(ಗಾತ್ರ_2);
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            surface->flags |= SDL_SURFACE_SIMD_ALIGNED;
            ಆದರೆ (clear_surface) {
                surface->pixels = SDL_aligned_alloc_zero(SDL_GetSIMDAlignment(), ಗಾತ್ರ_2);
            } ಇಲ್ಲದಿದ್ದರೆ {
                surface->pixels = SDL_aligned_alloc(SDL_GetSIMDAlignment(), ಗಾತ್ರ_2);
            }
        }
        ಆದರೆ (!surface->pixels) {
            SDL_DestroySurface(surface);
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }
    }
    ಹಿಂತಿರುಗಿ surface;
}

SDL_Surface *SDL_CreateSurfaceZeroed(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, SDL_PixelFormat format)
{
    ಹಿಂತಿರುಗಿ SDL_Create_Surface_ಆಂತರಿಕ(ಅಗಲ, ಎತ್ತರ, format, true);
}

SDL_Surface *SDL_CreateSurfaceUninitialized(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, SDL_PixelFormat format)
{
    ಹಿಂತಿರುಗಿ SDL_Create_Surface_ಆಂತರಿಕ(ಅಗಲ, ಎತ್ತರ, format, false);
}

SDL_Surface *SDL_CreateSurface(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, SDL_PixelFormat format)
{
    ಹಿಂತಿರುಗಿ SDL_CreateSurfaceZeroed(ಅಗಲ, ಎತ್ತರ, format);
}


/*
 * Create an RGB surface from an existing memory buffer using the given
 * enum SDL_PIXELFORMAT_* format
 */
SDL_Surface *SDL_CreateSurfaceFrom(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, SDL_PixelFormat format, ಶೂನ್ಯ *pixels, ಪೂರ್ಣಾಂಕ pitch)
{
    CHECK_PARAM(ಅಗಲ < 0) {
        SDL_InvalidParamError("width");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    CHECK_PARAM(ಎತ್ತರ < 0) {
        SDL_InvalidParamError("height");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಆದರೆ (pitch == 0 && !pixels) {
        // The application will fill these in later with valid values
    } ಇಲ್ಲದಿದ್ದರೆ {
        size_t ಕನಿಷ್ಠತಮ_Pitch;

        ಆದರೆ (!SDL_Calculate_Surface_ಗಾತ್ರ(format, ಅಗಲ, ಎತ್ತರ, ಖಾಲಿ, &ಕನಿಷ್ಠತಮ_Pitch, true /* minimal pitch */)) {
            // Overflow...
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }

        CHECK_PARAM(pitch < 0 || (size_t)pitch < ಕನಿಷ್ಠತಮ_Pitch) {
            SDL_InvalidParamError("pitch");
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }
    }

    // Allocate and initialize the surface
    SDL_Surface *surface = (SDL_Surface *)SDL_malloc(ಗಾತ್ರ(*surface));
    ಆದರೆ (!surface ||
        !SDL_InitializeSurface(surface, ಅಗಲ, ಎತ್ತರ, format, SDL_COLORSPACE_UNKNOWN, 0, pixels, pitch, false)) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    ಹಿಂತಿರುಗಿ surface;
}

SDL_PropertiesID SDL_GetSurfaceProperties(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        ಹಿಂತಿರುಗಿ 0;
    }

    ಆದರೆ (!surface->props) {
        surface->props = SDL_CreateProperties();
    }
    ಹಿಂತಿರುಗಿ surface->props;
}

bool SDL_ಗಣ_Surface_Colorspace(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("surface");
    }

    surface->colorspace = colorspace;
    ಹಿಂತಿರುಗಿ true;
}

SDL_Colorspace SDL_GetSurfaceColorspace(SDL_Surface *surface)
{
    ಆದರೆ (!SDL_SurfaceValid(surface)) {
        ಹಿಂತಿರುಗಿ SDL_COLORSPACE_UNKNOWN;
    }

    ಹಿಂತಿರುಗಿ surface->colorspace;
}

ದಶಮಾಂಶ SDL_Get_Default_SDRWhite_ಬಿಂದು(SDL_Colorspace colorspace)
{
    ಹಿಂತಿರುಗಿ SDL_Get_Surface_SDRWhite_ಬಿಂದು(ಖಾಲಿ, colorspace);
}

ದಶಮಾಂಶ SDL_Get_Surface_SDRWhite_ಬಿಂದು(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    SDL_TransferCharacteristics transfer = SDL_COLORSPACETRANSFER(colorspace);

    ಆದರೆ (transfer == SDL_TRANSFER_CHARACTERISTICS_ರೇಖೀಯ ||
        transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
        SDL_PropertiesID props;
        ದಶಮಾಂಶ default_ಮೌಲ್ಯ = 1.0f;

        ಆದರೆ (SDL_SurfaceValid(surface)) {
            props = surface->props;
        } ಇಲ್ಲದಿದ್ದರೆ {
            props = 0;
        }
        ಆದರೆ (transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
            /* The older standards use an SDR white point of 100 nits.
             * ITU-R BT.2408-6 recommends using an SDR white point of 203 nits.
             * This is the default Chrome uses, and what a lot of game content
             * assumes, so we'll go with that.
             */
            ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ DEFAULT_PQ_SDR_WHITE_ಬಿಂದು = 203.0f;
            default_ಮೌಲ್ಯ = DEFAULT_PQ_SDR_WHITE_ಬಿಂದು;
        }
        ಹಿಂತಿರುಗಿ SDL_GetFloatProperty(props, SDL_PROP_SURFACE_SDR_WHITE_ಬಿಂದು_FLOAT, default_ಮೌಲ್ಯ);
    }
    ಹಿಂತಿರುಗಿ 1.0f;
}

ದಶಮಾಂಶ SDL_GetDefaultHDRHeadroom(SDL_Colorspace colorspace)
{
    ಹಿಂತಿರುಗಿ SDL_GetSurfaceHDRHeadroom(ಖಾಲಿ, colorspace);
}

ದಶಮಾಂಶ SDL_GetSurfaceHDRHeadroom(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    SDL_TransferCharacteristics transfer = SDL_COLORSPACETRANSFER(colorspace);

    ಆದರೆ (transfer == SDL_TRANSFER_CHARACTERISTICS_ರೇಖೀಯ ||
        transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
        SDL_PropertiesID props;
        ದಶಮಾಂಶ default_ಮೌಲ್ಯ = 0.0f;

        ಆದರೆ (SDL_SurfaceValid(surface)) {
            props = surface->props;
        } ಇಲ್ಲದಿದ್ದರೆ {
            props = 0;
        }
        ಹಿಂತಿರುಗಿ SDL_GetFloatProperty(props, SDL_PROP_SURFACE_HDR_HEADROOM_FLOAT, default_ಮೌಲ್ಯ);
    }
    ಹಿಂತಿರುಗಿ 1.0f;
}

SDL_Palette *SDL_CreateSurfacePalette(SDL_Surface *surface)
{
    SDL_Palette *palette;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    CHECK_PARAM(!SDL_ISPIXELFORMAT_ಸೂಚ್ಯಂಕಿತ(surface->format)) {
        SDL_ಗಣ_Error("The surface is not indexed format");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    palette = SDL_CreatePalette((1 << SDL_BITSPERPIXEL(surface->format)));
    ಆದರೆ (!palette) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಆದರೆ (palette->ncolors == 2) {
        // Create a black and white bitmap palette
        palette->colors[0].r = 0xFF;
        palette->colors[0].g = 0xFF;
        palette->colors[0].b = 0xFF;
        palette->colors[1].r = 0x00;
        palette->colors[1].g = 0x00;
        palette->colors[1].b = 0x00;
    }

    ಆದರೆ (!SDL_ಗಣ_Surface_Palette(surface, palette)) {
        SDL_DestroyPalette(palette);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    // The surface has retained the palette, we can remove the reference here
    SDL_assert(palette->refcount == 2);
    SDL_DestroyPalette(palette);
    ಹಿಂತಿರುಗಿ palette;
}

bool SDL_ಗಣ_Surface_Palette(SDL_Surface *surface, SDL_Palette *palette)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(palette && !SDL_ISPIXELFORMAT_ಸೂಚ್ಯಂಕಿತ(surface->format)) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Surface doesn't use a palette");
    }

    CHECK_PARAM(palette && palette->ncolors > (1 << SDL_BITSPERPIXEL(surface->format))) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Palette doesn't match surface format");
    }

    ಆದರೆ (palette != surface->palette) {
        ಆದರೆ (surface->palette) {
            SDL_DestroyPalette(surface->palette);
        }

        surface->palette = palette;

        ಆದರೆ (surface->palette) {
            ++surface->palette->refcount;
        }
    }

    SDL_InvalidateMap(&surface->map);

    ಹಿಂತಿರುಗಿ true;
}

SDL_Palette *SDL_GetSurfacePalette(SDL_Surface *surface)
{
    ಆದರೆ (!SDL_SurfaceValid(surface)) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಹಿಂತಿರುಗಿ surface->palette;
}

bool SDL_ಕೂಡಿಸು_Surface_Alternate_Image(SDL_Surface *surface, SDL_Surface *image)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(!SDL_SurfaceValid(image)) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("image");
    }

    SDL_Surface **images = (SDL_Surface **)SDL_realloc(surface->images, (surface->ಅಂಕೆ_images + 1) * ಗಾತ್ರ(*images));
    ಆದರೆ (!images) {
        ಹಿಂತಿರುಗಿ false;
    }
    images[surface->ಅಂಕೆ_images] = image;
    surface->images = images;
    ++surface->ಅಂಕೆ_images;
    ++image->refcount;
    ಹಿಂತಿರುಗಿ true;
}

bool SDL_SurfaceHasAlternateImages(SDL_Surface *surface)
{
    ಆದರೆ (!SDL_SurfaceValid(surface)) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಹಿಂತಿರುಗಿ (surface->ಅಂಕೆ_images > 0);
}

SDL_Surface **SDL_GetSurfaceImages(SDL_Surface *surface, ಪೂರ್ಣಾಂಕ *ಎಣಿಕೆ_2)
{
    ಆದರೆ (ಎಣಿಕೆ_2) {
        *ಎಣಿಕೆ_2 = 0;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಪೂರ್ಣಾಂಕ ಅಂಕೆ_images = 1 + surface->ಅಂಕೆ_images;
    SDL_Surface **images = (SDL_Surface **)SDL_malloc((ಅಂಕೆ_images + 1) * ಗಾತ್ರ(*images));
    ಆದರೆ (!images) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    images[0] = surface;
    ಆದರೆ (surface->ಅಂಕೆ_images > 0) {
        SDL_memcpy(&images[1], surface->images, (surface->ಅಂಕೆ_images * ಗಾತ್ರ(images[1])));
    }
    images[ಅಂಕೆ_images] = ಖಾಲಿ;

    ಆದರೆ (ಎಣಿಕೆ_2) {
        *ಎಣಿಕೆ_2 = ಅಂಕೆ_images;
    }
    ಹಿಂತಿರುಗಿ images;
}

SDL_Surface *SDL_GetSurfaceImage(SDL_Surface *surface, ದಶಮಾಂಶ display_scale)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಆದರೆ (!SDL_SurfaceHasAlternateImages(surface)) {
        ++surface->refcount;
        ಹಿಂತಿರುಗಿ surface;
    }

    // This surface has high DPI images, pick the best one available, or scale one to the correct size
    SDL_Surface **images = SDL_GetSurfaceImages(surface, ಖಾಲಿ);
    ಆದರೆ (!images) {
        // Failure, fall back to the existing surface
        ++surface->refcount;
        ಹಿಂತಿರುಗಿ surface;
    }

    // Find closest image. Images that are larger than the
    // desired size are preferred over images that are smaller.
    SDL_Surface *closest = ಖಾಲಿ;
    ಪೂರ್ಣಾಂಕ desired_w = (ಪೂರ್ಣಾಂಕ)SDL_ಸುತ್ತು(surface->w * display_scale);
    ಪೂರ್ಣಾಂಕ desired_h = (ಪೂರ್ಣಾಂಕ)SDL_ಸುತ್ತು(surface->h * display_scale);
    ಪೂರ್ಣಾಂಕ desired_ಗಾತ್ರ = desired_w * desired_h;
    ಪೂರ್ಣಾಂಕ closest_ದೂರ = -1;
    ಪೂರ್ಣಾಂಕ closest_ಗಾತ್ರ = -1;
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; images[i]; ++i) {
        SDL_Surface *candidate = images[i];
        ಪೂರ್ಣಾಂಕ ಗಾತ್ರ_2 = candidate->w * candidate->h;
        ಪೂರ್ಣಾಂಕ delta_w = (candidate->w - desired_w);
        ಪೂರ್ಣಾಂಕ delta_h = (candidate->h - desired_h);
        ಪೂರ್ಣಾಂಕ ದೂರ = (delta_w * delta_w) + (delta_h * delta_h);
        ಆದರೆ (closest_ದೂರ < 0 || ದೂರ < closest_ದೂರ ||
            (ಗಾತ್ರ_2 > desired_ಗಾತ್ರ && closest_ಗಾತ್ರ < desired_ಗಾತ್ರ)) {
            closest = candidate;
            closest_ದೂರ = ದೂರ;
            closest_ಗಾತ್ರ = ಗಾತ್ರ_2;
        }
    }
    SDL_free(images);
    SDL_assert(closest != ಖಾಲಿ);    // We should always have at least one surface

    ಆದರೆ (closest->w == desired_w && closest->h == desired_h) {
        ++closest->refcount;
        ಹಿಂತಿರುಗಿ closest;
    }

    // We need to scale the image to the correct size. To maintain good image quality, downscaling
    // is done in steps, never reducing the width and height by more than half each time.
    SDL_Surface *scaled = closest;
    ಮಾಡು {
        ಪೂರ್ಣಾಂಕ ಮುಂದಿನ_scaled_w = SDL_max(desired_w, (scaled->w + 1) / 2);
        ಪೂರ್ಣಾಂಕ ಮುಂದಿನ_scaled_h = SDL_max(desired_h, (scaled->h + 1) / 2);
        SDL_Surface *ಮುಂದಿನ_scaled = SDL_ScaleSurface(scaled, ಮುಂದಿನ_scaled_w, ಮುಂದಿನ_scaled_h, SDL_SCALEMODE_ರೇಖೀಯ);
        ಆದರೆ (scaled != closest) {
            SDL_DestroySurface(scaled);
        }
        scaled = ಮುಂದಿನ_scaled;
        ಆದರೆ (!scaled) {
            // Failure, fall back to the closest surface
            ++closest->refcount;
            ಹಿಂತಿರುಗಿ closest;
        }
    } ಆಗ (scaled->w != desired_w || scaled->h != desired_h);

    ಹಿಂತಿರುಗಿ scaled;
}

ಶೂನ್ಯ SDL_RemoveSurfaceAlternateImages(SDL_Surface *surface)
{
    ಆದರೆ (!SDL_SurfaceValid(surface)) {
        ಹಿಂತಿರುಗಿ;
    }

    ಆದರೆ (surface->ಅಂಕೆ_images > 0) {
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < surface->ಅಂಕೆ_images; ++i) {
            SDL_DestroySurface(surface->images[i]);
        }
        SDL_free(surface->images);
        surface->images = ಖಾಲಿ;
        surface->ಅಂಕೆ_images = 0;
    }
}

bool SDL_ಗಣ_Surface_RLE(SDL_Surface *surface, bool enabled)
{
    ಪೂರ್ಣಾಂಕ flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("surface");
    }

    flags = surface->map.info.flags;
    ಆದರೆ (enabled) {
        surface->map.info.flags |= SDL_COPY_RLE_DESIRED;
    } ಇಲ್ಲದಿದ್ದರೆ {
        surface->map.info.flags &= ~SDL_COPY_RLE_DESIRED;
    }
    ಆದರೆ (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    ಹಿಂತಿರುಗಿ true;
}

bool SDL_SurfaceHasRLE(SDL_Surface *surface)
{
    ಆದರೆ (!SDL_SurfaceValid(surface)) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಆದರೆ (!(surface->map.info.flags & SDL_COPY_RLE_DESIRED)) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಹಿಂತಿರುಗಿ true;
}

bool SDL_ಗಣ_Surface_Color_ಕೀಲಿ(SDL_Surface *surface, bool enabled, Uint32 ಕೀಲಿ)
{
    ಪೂರ್ಣಾಂಕ flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(surface->palette && ಕೀಲಿ >= ((Uint32)surface->palette->ncolors)) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("key");
    }

    flags = surface->map.info.flags;
    ಆದರೆ (enabled) {
        surface->map.info.flags |= SDL_COPY_COLORKEY;
        surface->map.info.colorkey = ಕೀಲಿ;
    } ಇಲ್ಲದಿದ್ದರೆ {
        surface->map.info.flags &= ~SDL_COPY_COLORKEY;
    }
    ಆದರೆ (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }

    ಹಿಂತಿರುಗಿ true;
}

bool SDL_Surface_Has_Color_ಕೀಲಿ(SDL_Surface *surface)
{
    ಆದರೆ (!SDL_SurfaceValid(surface)) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಆದರೆ (!(surface->map.info.flags & SDL_COPY_COLORKEY)) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಹಿಂತಿರುಗಿ true;
}

bool SDL_Get_Surface_Color_ಕೀಲಿ(SDL_Surface *surface, Uint32 *ಕೀಲಿ)
{
    ಆದರೆ (ಕೀಲಿ) {
        *ಕೀಲಿ = 0;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(!(surface->map.info.flags & SDL_COPY_COLORKEY)) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Surface doesn't have a colorkey");
    }

    ಆದರೆ (ಕೀಲಿ) {
        *ಕೀಲಿ = surface->map.info.colorkey;
    }
    ಹಿಂತಿರುಗಿ true;
}

/* This is a fairly slow function to switch from colorkey to alpha
   NB: it doesn't handle bpp 1 or 3, because they have no alpha channel */
ಸ್ಥಿರ ಶೂನ್ಯ SDL_Convert_Colorkey_ಗಮ್ಯ_Alpha(SDL_Surface *surface, bool ignore_alpha)
{
    ಪೂರ್ಣಾಂಕ x, y, bpp;

    ಆದರೆ (!SDL_SurfaceValid(surface)) {
        ಹಿಂತಿರುಗಿ;
    }

    ಆದರೆ (!(surface->map.info.flags & SDL_COPY_COLORKEY) ||
        !SDL_ISPIXELFORMAT_ALPHA(surface->format)) {
        ಹಿಂತಿರುಗಿ;
    }

    bpp = SDL_BYTESPERPIXEL(surface->format);

    SDL_ಬೀಗ_Surface(surface);

    ಆದರೆ (bpp == 2) {
        Uint16 *ಅಡ್ಡಸಾಲು, *spot;
        Uint16 ckey = (Uint16)surface->map.info.colorkey;
        Uint16 ಮುಖವಾಡ = (Uint16)(~surface->fmt->Amask);

        // Ignore, or not, alpha in colorkey comparison
        ಆದರೆ (ignore_alpha) {
            ckey &= ಮುಖವಾಡ;
            ಅಡ್ಡಸಾಲು = (Uint16 *)surface->pixels;
            ಗಾಗಿ (y = surface->h; y--;) {
                spot = ಅಡ್ಡಸಾಲು;
                ಗಾಗಿ (x = surface->w; x--;) {
                    ಆದರೆ ((*spot & ಮುಖವಾಡ) == ckey) {
                        *spot &= ಮುಖವಾಡ;
                    }
                    ++spot;
                }
                ಅಡ್ಡಸಾಲು += surface->pitch / 2;
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಅಡ್ಡಸಾಲು = (Uint16 *)surface->pixels;
            ಗಾಗಿ (y = surface->h; y--;) {
                spot = ಅಡ್ಡಸಾಲು;
                ಗಾಗಿ (x = surface->w; x--;) {
                    ಆದರೆ (*spot == ckey) {
                        *spot &= ಮುಖವಾಡ;
                    }
                    ++spot;
                }
                ಅಡ್ಡಸಾಲು += surface->pitch / 2;
            }
        }
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (bpp == 4) {
        Uint32 *ಅಡ್ಡಸಾಲು, *spot;
        Uint32 ckey = surface->map.info.colorkey;
        Uint32 ಮುಖವಾಡ = ~surface->fmt->Amask;

        // Ignore, or not, alpha in colorkey comparison
        ಆದರೆ (ignore_alpha) {
            ckey &= ಮುಖವಾಡ;
            ಅಡ್ಡಸಾಲು = (Uint32 *)surface->pixels;
            ಗಾಗಿ (y = surface->h; y--;) {
                spot = ಅಡ್ಡಸಾಲು;
                ಗಾಗಿ (x = surface->w; x--;) {
                    ಆದರೆ ((*spot & ಮುಖವಾಡ) == ckey) {
                        *spot &= ಮುಖವಾಡ;
                    }
                    ++spot;
                }
                ಅಡ್ಡಸಾಲು += surface->pitch / 4;
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಅಡ್ಡಸಾಲು = (Uint32 *)surface->pixels;
            ಗಾಗಿ (y = surface->h; y--;) {
                spot = ಅಡ್ಡಸಾಲು;
                ಗಾಗಿ (x = surface->w; x--;) {
                    ಆದರೆ (*spot == ckey) {
                        *spot &= ಮುಖವಾಡ;
                    }
                    ++spot;
                }
                ಅಡ್ಡಸಾಲು += surface->pitch / 4;
            }
        }
    }

    SDL_UnlockSurface(surface);

    SDL_ಗಣ_Surface_Color_ಕೀಲಿ(surface, false, 0);
    SDL_ಗಣ_Surface_Blend_ಬಹುಲಕ(surface, SDL_BLENDMODE_BLEND);
}

bool SDL_ಗಣ_Surface_Color_Mod(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b)
{
    ಪೂರ್ಣಾಂಕ flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("surface");
    }

    surface->map.info.r = r;
    surface->map.info.g = g;
    surface->map.info.b = b;

    flags = surface->map.info.flags;
    ಆದರೆ (r != 0xFF || g != 0xFF || b != 0xFF) {
        surface->map.info.flags |= SDL_COPY_MODULATE_COLOR;
    } ಇಲ್ಲದಿದ್ದರೆ {
        surface->map.info.flags &= ~SDL_COPY_MODULATE_COLOR;
    }
    ಆದರೆ (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    ಹಿಂತಿರುಗಿ true;
}

bool SDL_GetSurfaceColorMod(SDL_Surface *surface, Uint8 *r, Uint8 *g, Uint8 *b)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ಆದರೆ (r) {
            *r = 255;
        }
        ಆದರೆ (g) {
            *g = 255;
        }
        ಆದರೆ (b) {
            *b = 255;
        }
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("surface");
    }

    ಆದರೆ (r) {
        *r = surface->map.info.r;
    }
    ಆದರೆ (g) {
        *g = surface->map.info.g;
    }
    ಆದರೆ (b) {
        *b = surface->map.info.b;
    }
    ಹಿಂತಿರುಗಿ true;
}

bool SDL_ಗಣ_Surface_Alpha_Mod(SDL_Surface *surface, Uint8 alpha)
{
    ಪೂರ್ಣಾಂಕ flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("surface");
    }

    surface->map.info.a = alpha;

    flags = surface->map.info.flags;
    ಆದರೆ (alpha != 0xFF) {
        surface->map.info.flags |= SDL_COPY_MODULATE_ALPHA;
    } ಇಲ್ಲದಿದ್ದರೆ {
        surface->map.info.flags &= ~SDL_COPY_MODULATE_ALPHA;
    }
    ಆದರೆ (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    ಹಿಂತಿರುಗಿ true;
}

bool SDL_GetSurfaceAlphaMod(SDL_Surface *surface, Uint8 *alpha)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ಆದರೆ (alpha) {
            *alpha = 255;
        }
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("surface");
    }

    ಆದರೆ (alpha) {
        *alpha = surface->map.info.a;
    }
    ಹಿಂತಿರುಗಿ true;
}

bool SDL_ಗಣ_Surface_Blend_ಬಹುಲಕ(SDL_Surface *surface, SDL_Blend_ಬಹುಲಕ blend_ಬಹುಲಕ)
{
    ಪೂರ್ಣಾಂಕ flags;
    bool ಫಲಿತಾಂಶ = true;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(blend_ಬಹುಲಕ == SDL_BLENDMODE_INVALID) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("blendMode");
    }

    flags = surface->map.info.flags;
    surface->map.info.flags &= ~SDL_COPY_BLEND_ಮುಖವಾಡ;
    ಆಯ್ಕೆ (blend_ಬಹುಲಕ) {
    ಸ್ಥಿತಿ SDL_BLENDMODE_NONE:
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_BLENDMODE_BLEND:
        surface->map.info.flags |= SDL_COPY_BLEND;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_BLENDMODE_BLEND_PREMULTIPLIED:
        surface->map.info.flags |= SDL_COPY_BLEND_PREMULTIPLIED;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_BLENDMODE_ಕೂಡಿಸು:
        surface->map.info.flags |= SDL_COPY_ಕೂಡಿಸು;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_BLENDMODE_ಕೂಡಿಸು_PREMULTIPLIED:
        surface->map.info.flags |= SDL_COPY_ಕೂಡಿಸು_PREMULTIPLIED;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_BLENDMODE_MOD:
        surface->map.info.flags |= SDL_COPY_MOD;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_BLENDMODE_MUL:
        surface->map.info.flags |= SDL_COPY_MUL;
        ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        ಫಲಿತಾಂಶ = SDL_Unsupported();
        ನಿಲ್ಲಿಸು;
    }

    ಆದರೆ (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }

    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

bool SDL_Get_Surface_Blend_ಬಹುಲಕ(SDL_Surface *surface, SDL_Blend_ಬಹುಲಕ *blend_ಬಹುಲಕ)
{
    ಆದರೆ (blend_ಬಹುಲಕ) {
        *blend_ಬಹುಲಕ = SDL_BLENDMODE_INVALID;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("surface");
    }

    ಆದರೆ (!blend_ಬಹುಲಕ) {
        ಹಿಂತಿರುಗಿ true;
    }

    ಆಯ್ಕೆ (surface->map.info.flags & SDL_COPY_BLEND_ಮುಖವಾಡ) {
    ಸ್ಥಿತಿ SDL_COPY_BLEND:
        *blend_ಬಹುಲಕ = SDL_BLENDMODE_BLEND;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_COPY_BLEND_PREMULTIPLIED:
        *blend_ಬಹುಲಕ = SDL_BLENDMODE_BLEND_PREMULTIPLIED;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_COPY_ಕೂಡಿಸು:
        *blend_ಬಹುಲಕ = SDL_BLENDMODE_ಕೂಡಿಸು;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_COPY_ಕೂಡಿಸು_PREMULTIPLIED:
        *blend_ಬಹುಲಕ = SDL_BLENDMODE_ಕೂಡಿಸು_PREMULTIPLIED;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_COPY_MOD:
        *blend_ಬಹುಲಕ = SDL_BLENDMODE_MOD;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_COPY_MUL:
        *blend_ಬಹುಲಕ = SDL_BLENDMODE_MUL;
        ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        *blend_ಬಹುಲಕ = SDL_BLENDMODE_NONE;
        ನಿಲ್ಲಿಸು;
    }
    ಹಿಂತಿರುಗಿ true;
}

bool SDL_ಗಣ_Surface_Clip_Rect(SDL_Surface *surface, ಸ್ಥಿರಾಂಕ SDL_Rect *rect)
{
    SDL_Rect ತುಂಬಿದ_rect;

    // Don't do anything if there's no surface to act on
    ಆದರೆ (!SDL_SurfaceValid(surface)) {
        ಹಿಂತಿರುಗಿ false;
    }

    // Set up the full surface rectangle
    ತುಂಬಿದ_rect.x = 0;
    ತುಂಬಿದ_rect.y = 0;
    ತುಂಬಿದ_rect.w = surface->w;
    ತುಂಬಿದ_rect.h = surface->h;

    // Set the clipping rectangle
    ಆದರೆ (!rect) {
        surface->clip_rect = ತುಂಬಿದ_rect;
        ಹಿಂತಿರುಗಿ true;
    }
    ಹಿಂತಿರುಗಿ SDL_GetRectIntersection(rect, &ತುಂಬಿದ_rect, &surface->clip_rect);
}

bool SDL_GetSurfaceClipRect(SDL_Surface *surface, SDL_Rect *rect)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ಆದರೆ (rect) {
            SDL_zerop(rect);
        }
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("surface");
    }
    CHECK_PARAM(!rect) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("rect");
    }
    *rect = surface->clip_rect;
    ಹಿಂತಿರುಗಿ true;
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
bool SDL_BlitSurfaceUnchecked(SDL_Surface *src, ಸ್ಥಿರಾಂಕ SDL_Rect *srcrect,
                             SDL_Surface *dst, ಸ್ಥಿರಾಂಕ SDL_Rect *dstrect)
{
    // Check to make sure the blit mapping is valid
    ಆದರೆ (!SDL_ValidateMap(src, dst)) {
        ಹಿಂತಿರುಗಿ false;
    }
    ಹಿಂತಿರುಗಿ src->map.blit(src, srcrect, dst, dstrect);
}

bool SDL_BlitSurface(SDL_Surface *src, ಸ್ಥಿರಾಂಕ SDL_Rect *srcrect, SDL_Surface *dst, ಸ್ಥಿರಾಂಕ SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src) || (!src->pixels && !SDL_MUSTLOCK(src))) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst) || (!dst->pixels && !SDL_MUSTLOCK(dst))) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Surfaces must not be locked during blit");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    ಆದರೆ (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
    } ಇಲ್ಲದಿದ್ದರೆ {
        r_dst.x = 0;
        r_dst.y = 0;
    }

    // clip the source rectangle to the source surface
    ಆದರೆ (srcrect) {
        SDL_Rect tmp;
        ಆದರೆ (SDL_GetRectIntersection(srcrect, &r_src, &tmp) == false) {
            ಹಿಂತಿರುಗಿ true;
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
        ಆದರೆ (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &tmp) == false) {
            ಹಿಂತಿರುಗಿ true;
        }

        // Shift srcrect, if dstrect has changed
        r_src.x += tmp.x - r_dst.x;
        r_src.y += tmp.y - r_dst.y;
        r_src.w = tmp.w;
        r_src.h = tmp.h;

        // Update dstrect
        r_dst = tmp;
    }

    ಆದರೆ (r_dst.w <= 0 || r_dst.h <= 0) {
        // No-op.
        ಹಿಂತಿರುಗಿ true;
    }

    // Switch back to a fast blit if we were previously stretching
    ಆದರೆ (src->map.info.flags & SDL_COPY_ಹತ್ತಿರದ) {
        src->map.info.flags &= ~SDL_COPY_ಹತ್ತಿರದ;
        SDL_InvalidateMap(&src->map);
    }

    ಹಿಂತಿರುಗಿ SDL_BlitSurfaceUnchecked(src, &r_src, dst, &r_dst);
}

ಸ್ಥಿರ bool SDL_BlitSurfaceClippedScaled(SDL_Surface *src, ಸ್ಥಿರಾಂಕ SDL_Rect *srcrect, SDL_Surface *dst, ಸ್ಥಿರಾಂಕ SDL_Rect *dstrect, SDL_Scale_ಬಹುಲಕ scale_ಬಹುಲಕ)
{
    // We need to scale first, then blit into dst because we're clipping in the destination surface pixel coordinates
    bool ಫಲಿತಾಂಶ;
    ಪೂರ್ಣಾಂಕ saved_w = src->w;
    ಪೂರ್ಣಾಂಕ saved_h = src->h;
    ಶೂನ್ಯ *saved_pixels = src->pixels;
    src->w = srcrect->w;
    src->h = srcrect->h;
    src->pixels = (Uint8 *)src->pixels + srcrect->y * src->pitch + srcrect->x * SDL_BYTESPERPIXEL(src->format);
    SDL_Surface *scaled = SDL_ScaleSurface(src, dstrect->w, dstrect->h, scale_ಬಹುಲಕ);
    ಆದರೆ (scaled) {
        ಫಲಿತಾಂಶ = SDL_BlitSurface(scaled, ಖಾಲಿ, dst, dstrect);
        SDL_DestroySurface(scaled);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಫಲಿತಾಂಶ = false;
    }
    src->w = saved_w;
    src->h = saved_h;
    src->pixels = saved_pixels;
    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

bool SDL_BlitSurfaceScaled(SDL_Surface *src, ಸ್ಥಿರಾಂಕ SDL_Rect *srcrect, SDL_Surface *dst, ಸ್ಥಿರಾಂಕ SDL_Rect *dstrect, SDL_Scale_ಬಹುಲಕ scale_ಬಹುಲಕ)
{
    SDL_Rect r_src, r_dst;
    bool ಫಲಿತಾಂಶ;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src) || (!src->pixels && !SDL_MUSTLOCK(src))) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst) || (!dst->pixels && !SDL_MUSTLOCK(dst))) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Surfaces must not be locked during blit");
    }

    ಆಯ್ಕೆ (scale_ಬಹುಲಕ) {
    ಸ್ಥಿತಿ SDL_SCALEMODE_ಹತ್ತಿರದ:
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SCALEMODE_ರೇಖೀಯ:
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SCALEMODE_PIXELART:
        scale_ಬಹುಲಕ = SDL_SCALEMODE_ಹತ್ತಿರದ;
        ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("scaleMode");
    }

    ಪೂರ್ಣಾಂಕ src_w = srcrect ? srcrect->w : src->w;
    ಪೂರ್ಣಾಂಕ src_h = srcrect ? srcrect->h : src->h;
    ಪೂರ್ಣಾಂಕ dst_w = dstrect ? dstrect->w : dst->w;
    ಪೂರ್ಣಾಂಕ dst_h = dstrect ? dstrect->h : dst->h;
    ಆದರೆ (src_w == dst_w && src_h == dst_h) {
        // No scaling, defer to regular blit
        ಹಿಂತಿರುಗಿ SDL_BlitSurface(src, srcrect, dst, dstrect);
    }

    ಆದರೆ (src->w == 0 || src->h == 0) {
        // Nothing to do
        ಹಿಂತಿರುಗಿ true;
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    ಆದರೆ (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
        r_dst.w = dstrect->w;
        r_dst.h = dstrect->h;
    } ಇಲ್ಲದಿದ್ದರೆ {
        r_dst.x = 0;
        r_dst.y = 0;
        r_dst.w = dst->w;
        r_dst.h = dst->h;
    }

    // clip the source rectangle to the source surface
    ಆದರೆ (srcrect) {
        SDL_Rect desired, tmp;
        desired.x = srcrect->x;
        desired.y = srcrect->y;
        desired.w = SDL_max(srcrect->w, 1);
        desired.h = SDL_max(srcrect->h, 1);
        ಆದರೆ (SDL_GetRectIntersection(&desired, &r_src, &tmp) == false) {
            ಹಿಂತಿರುಗಿ true;
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
    ಆದರೆ (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &tmp) == false) {
        ಹಿಂತಿರುಗಿ true;
    }

    ಆದರೆ (tmp.x != r_dst.x || tmp.y != r_dst.y || tmp.w != r_dst.w || tmp.h != r_dst.h) {
        // Need to do a clipped and scaled blit
        ಹಿಂತಿರುಗಿ SDL_BlitSurfaceClippedScaled(src, &r_src, dst, &r_dst, scale_ಬಹುಲಕ);
    }

    ಆದರೆ (SDL_MUSTLOCK(src)) {
        ಆದರೆ (!SDL_ಬೀಗ_Surface(src)) {
            ಹಿಂತಿರುಗಿ false;
        }
    }
    ಆದರೆ (SDL_MUSTLOCK(dst)) {
        ಆದರೆ (!SDL_ಬೀಗ_Surface(dst)) {
            ಆದರೆ (SDL_MUSTLOCK(src)) {
                SDL_UnlockSurface(src);
            }
            ಹಿಂತಿರುಗಿ false;
        }
    }

    ಫಲಿತಾಂಶ = SDL_BlitSurfaceUncheckedScaled(src, &r_src, dst, &r_dst, scale_ಬಹುಲಕ);

    ಆದರೆ (SDL_MUSTLOCK(src)) {
        SDL_UnlockSurface(src);
    }
    ಆದರೆ (SDL_MUSTLOCK(dst)) {
        SDL_UnlockSurface(dst);
    }
    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

/**
 *  This is a semi-private blit function and it performs low-level surface
 *  scaled blitting only.
 */
bool SDL_BlitSurfaceUncheckedScaled(SDL_Surface *src, ಸ್ಥಿರಾಂಕ SDL_Rect *srcrect, SDL_Surface *dst, ಸ್ಥಿರಾಂಕ SDL_Rect *dstrect, SDL_Scale_ಬಹುಲಕ scale_ಬಹುಲಕ)
{
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ Uint32 complex_copy_flags = (SDL_COPY_MODULATE_ಮುಖವಾಡ | SDL_COPY_BLEND_ಮುಖವಾಡ | SDL_COPY_COLORKEY);

    ಆದರೆ (srcrect->w > SDL_MAX_UINT16 || srcrect->h > SDL_MAX_UINT16 ||
        dstrect->w > SDL_MAX_UINT16 || dstrect->h > SDL_MAX_UINT16) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Size too large for scaling");
    }

    ಆದರೆ (!(src->map.info.flags & SDL_COPY_ಹತ್ತಿರದ)) {
        src->map.info.flags |= SDL_COPY_ಹತ್ತಿರದ;
        SDL_InvalidateMap(&src->map);
    }

    ಆದರೆ (scale_ಬಹುಲಕ == SDL_SCALEMODE_ಹತ್ತಿರದ || scale_ಬಹುಲಕ == SDL_SCALEMODE_PIXELART) {
        ಆದರೆ (!(src->map.info.flags & complex_copy_flags) &&
            src->format == dst->format &&
            (!SDL_ISPIXELFORMAT_ಸೂಚ್ಯಂಕಿತ(src->format) ||
             (SDL_BITSPERPIXEL(src->format) == 8 && SDL_IsSamePalette(src->palette, dst->palette))) &&
            SDL_BYTESPERPIXEL(src->format) <= 4) {
            ಹಿಂತಿರುಗಿ SDL_StretchSurface(src, srcrect, dst, dstrect, SDL_SCALEMODE_ಹತ್ತಿರದ);
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_BITSPERPIXEL(src->format) < 8) {
            // Scaling bitmap not yet supported, convert to RGBA for blit
            bool ಫಲಿತಾಂಶ = false;
            SDL_Surface *tmp = SDL_ConvertSurface(src, SDL_PIXELFORMAT_ARGB8888);
            ಆದರೆ (tmp) {
                ಫಲಿತಾಂಶ = SDL_BlitSurfaceUncheckedScaled(tmp, srcrect, dst, dstrect, SDL_SCALEMODE_ಹತ್ತಿರದ);
                SDL_DestroySurface(tmp);
            }
            ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಹಿಂತಿರುಗಿ SDL_BlitSurfaceUnchecked(src, srcrect, dst, dstrect);
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (!(src->map.info.flags & complex_copy_flags) &&
            src->format == dst->format &&
            !SDL_ISPIXELFORMAT_ಸೂಚ್ಯಂಕಿತ(src->format) &&
            SDL_BYTESPERPIXEL(src->format) == 4 &&
            src->format != SDL_PIXELFORMAT_ARGB2101010) {
            // fast path
            ಹಿಂತಿರುಗಿ SDL_StretchSurface(src, srcrect, dst, dstrect, SDL_SCALEMODE_ರೇಖೀಯ);
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_BITSPERPIXEL(src->format) < 8) {
            // Scaling bitmap not yet supported, convert to RGBA for blit
            bool ಫಲಿತಾಂಶ = false;
            SDL_Surface *tmp = SDL_ConvertSurface(src, SDL_PIXELFORMAT_ARGB8888);
            ಆದರೆ (tmp) {
                ಫಲಿತಾಂಶ = SDL_BlitSurfaceUncheckedScaled(tmp, srcrect, dst, dstrect, scale_ಬಹುಲಕ);
                SDL_DestroySurface(tmp);
            }
            ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
        } ಇಲ್ಲದಿದ್ದರೆ {
            // Use intermediate surface(s)
            SDL_Surface *tmp1 = ಖಾಲಿ;
            bool ಫಲಿತಾಂಶ;
            SDL_Rect srcrect2;
            ಪೂರ್ಣಾಂಕ is_complex_copy_flags = (src->map.info.flags & complex_copy_flags);

            Uint8 r, g, b;
            Uint8 alpha;
            SDL_Blend_ಬಹುಲಕ blend_ಬಹುಲಕ;

            // Save source infos
            SDL_GetSurfaceColorMod(src, &r, &g, &b);
            SDL_GetSurfaceAlphaMod(src, &alpha);
            SDL_Get_Surface_Blend_ಬಹುಲಕ(src, &blend_ಬಹುಲಕ);
            srcrect2.x = srcrect->x;
            srcrect2.y = srcrect->y;
            srcrect2.w = srcrect->w;
            srcrect2.h = srcrect->h;

            // Change source format if not appropriate for scaling
            ಆದರೆ (SDL_BYTESPERPIXEL(src->format) != 4 || src->format == SDL_PIXELFORMAT_ARGB2101010) {
                SDL_PixelFormat fmt;
                ಆದರೆ (SDL_BYTESPERPIXEL(dst->format) == 4 && dst->format != SDL_PIXELFORMAT_ARGB2101010 &&
                    (SDL_ISPIXELFORMAT_ALPHA(dst->format) || !is_complex_copy_flags)) {
                    fmt = dst->format;
                } ಇಲ್ಲದಿದ್ದರೆ {
                    fmt = SDL_PIXELFORMAT_ARGB8888;
                }
                tmp1 = SDL_ConvertSurfaceRect(src, srcrect, fmt);
                ಆದರೆ (!tmp1) {
                    ಹಿಂತಿರುಗಿ false;
                }
                src = tmp1;
                srcrect2.x = 0;
                srcrect2.y = 0;
            }

            // Intermediate scaling
            ಆದರೆ (is_complex_copy_flags || src->format != dst->format) {
                SDL_Rect tmprect;
                SDL_Surface *tmp2 = SDL_CreateSurfaceUninitialized(dstrect->w, dstrect->h, src->format);
                SDL_StretchSurface(src, &srcrect2, tmp2, ಖಾಲಿ, SDL_SCALEMODE_ರೇಖೀಯ);

                SDL_ಗಣ_Surface_Color_Mod(tmp2, r, g, b);
                SDL_ಗಣ_Surface_Alpha_Mod(tmp2, alpha);
                SDL_ಗಣ_Surface_Blend_ಬಹುಲಕ(tmp2, blend_ಬಹುಲಕ);

                tmprect.x = 0;
                tmprect.y = 0;
                tmprect.w = dstrect->w;
                tmprect.h = dstrect->h;
                ಫಲಿತಾಂಶ = SDL_BlitSurfaceUnchecked(tmp2, &tmprect, dst, dstrect);
                SDL_DestroySurface(tmp2);
            } ಇಲ್ಲದಿದ್ದರೆ {
                ಫಲಿತಾಂಶ = SDL_StretchSurface(src, &srcrect2, dst, dstrect, SDL_SCALEMODE_ರೇಖೀಯ);
            }

            SDL_DestroySurface(tmp1);
            ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
        }
    }
}

bool SDL_BlitSurfaceTiled(SDL_Surface *src, ಸ್ಥಿರಾಂಕ SDL_Rect *srcrect, SDL_Surface *dst, ಸ್ಥಿರಾಂಕ SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Surfaces must not be locked during blit");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    ಆದರೆ (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
        r_dst.w = dstrect->w;
        r_dst.h = dstrect->h;
    } ಇಲ್ಲದಿದ್ದರೆ {
        r_dst.x = 0;
        r_dst.y = 0;
        r_dst.w = dst->w;
        r_dst.h = dst->h;
    }

    // clip the source rectangle to the source surface
    ಆದರೆ (srcrect) {
        ಆದರೆ (SDL_GetRectIntersection(srcrect, &r_src, &r_src) == false) {
            ಹಿಂತಿರುಗಿ true;
        }

        // For tiling we don't adjust the destination rectangle
    }

    // clip the destination rectangle against the clip rectangle
    {
        ಆದರೆ (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &r_dst) == false) {
            ಹಿಂತಿರುಗಿ true;
        }

        // For tiling we don't adjust the source rectangle
    }

    // Switch back to a fast blit if we were previously stretching
    ಆದರೆ (src->map.info.flags & SDL_COPY_ಹತ್ತಿರದ) {
        src->map.info.flags &= ~SDL_COPY_ಹತ್ತಿರದ;
        SDL_InvalidateMap(&src->map);
    }

    ಪೂರ್ಣಾಂಕ ಅಡ್ಡಸಾಲುಗಳು = r_dst.h / r_src.h;
    ಪೂರ್ಣಾಂಕ ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ = r_dst.w / r_src.w;
    ಪೂರ್ಣಾಂಕ ಉಳಿದ_w = r_dst.w % r_src.w;
    ಪೂರ್ಣಾಂಕ ಉಳಿದ_h = r_dst.h % r_src.h;
    SDL_Rect curr_src, curr_dst;

    SDL_copyp(&curr_src, &r_src);
    curr_dst.y = r_dst.y;
    curr_dst.w = r_src.w;
    curr_dst.h = r_src.h;
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ y = 0; y < ಅಡ್ಡಸಾಲುಗಳು; ++y) {
        curr_dst.x = r_dst.x;
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ x = 0; x < ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ; ++x) {
            ಆದರೆ (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                ಹಿಂತಿರುಗಿ false;
            }
            curr_dst.x += curr_dst.w;
        }
        ಆದರೆ (ಉಳಿದ_w) {
            curr_src.w = ಉಳಿದ_w;
            curr_dst.w = ಉಳಿದ_w;
            ಆದರೆ (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                ಹಿಂತಿರುಗಿ false;
            }
            curr_src.w = r_src.w;
            curr_dst.w = r_src.w;
        }
        curr_dst.y += curr_dst.h;
    }
    ಆದರೆ (ಉಳಿದ_h) {
        curr_src.h = ಉಳಿದ_h;
        curr_dst.h = ಉಳಿದ_h;
        curr_dst.x = r_dst.x;
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ x = 0; x < ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ; ++x) {
            ಆದರೆ (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                ಹಿಂತಿರುಗಿ false;
            }
            curr_dst.x += curr_dst.w;
        }
        ಆದರೆ (ಉಳಿದ_w) {
            curr_src.w = ಉಳಿದ_w;
            curr_dst.w = ಉಳಿದ_w;
            ಆದರೆ (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                ಹಿಂತಿರುಗಿ false;
            }
        }
    }
    ಹಿಂತಿರುಗಿ true;
}

bool SDL_BlitSurfaceTiledWithScale(SDL_Surface *src, ಸ್ಥಿರಾಂಕ SDL_Rect *srcrect, ದಶಮಾಂಶ scale, SDL_Scale_ಬಹುಲಕ scale_ಬಹುಲಕ, SDL_Surface *dst, ಸ್ಥಿರಾಂಕ SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Surfaces must not be locked during blit");
    }
    CHECK_PARAM(scale < 0.0f) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("scale");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    ಆದರೆ (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
        r_dst.w = dstrect->w;
        r_dst.h = dstrect->h;
    } ಇಲ್ಲದಿದ್ದರೆ {
        r_dst.x = 0;
        r_dst.y = 0;
        r_dst.w = dst->w;
        r_dst.h = dst->h;
    }

    // clip the source rectangle to the source surface
    ಆದರೆ (srcrect) {
        ಆದರೆ (SDL_GetRectIntersection(srcrect, &r_src, &r_src) == false) {
            ಹಿಂತಿರುಗಿ true;
        }

        // For tiling we don't adjust the destination rectangle
    }

    // clip the destination rectangle against the clip rectangle
    {
        ಆದರೆ (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &r_dst) == false) {
            ಹಿಂತಿರುಗಿ true;
        }

        // For tiling we don't adjust the source rectangle
    }

    // Switch back to a fast blit if we were previously stretching
    ಆದರೆ (src->map.info.flags & SDL_COPY_ಹತ್ತಿರದ) {
        src->map.info.flags &= ~SDL_COPY_ಹತ್ತಿರದ;
        SDL_InvalidateMap(&src->map);
    }

    ಪೂರ್ಣಾಂಕ tile_ಅಗಲ = (ಪೂರ್ಣಾಂಕ)SDL_roundf(r_src.w * scale);
    ಪೂರ್ಣಾಂಕ tile_ಎತ್ತರ = (ಪೂರ್ಣಾಂಕ)SDL_roundf(r_src.h * scale);
    ಆದರೆ (tile_ಅಗಲ <= 0 || tile_ಎತ್ತರ <= 0) {
        // Nothing to do
        ಹಿಂತಿರುಗಿ true;
    }
    ಪೂರ್ಣಾಂಕ ಅಡ್ಡಸಾಲುಗಳು = r_dst.h / tile_ಎತ್ತರ;
    ಪೂರ್ಣಾಂಕ ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ = r_dst.w / tile_ಅಗಲ;
    ಪೂರ್ಣಾಂಕ ಉಳಿದ_dst_w = (r_dst.w - ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ * tile_ಅಗಲ);
    ಪೂರ್ಣಾಂಕ ಉಳಿದ_dst_h = (r_dst.h - ಅಡ್ಡಸಾಲುಗಳು * tile_ಎತ್ತರ);
    ಪೂರ್ಣಾಂಕ ಉಳಿದ_src_w = (ಪೂರ್ಣಾಂಕ)(ಉಳಿದ_dst_w / scale);
    ಪೂರ್ಣಾಂಕ ಉಳಿದ_src_h = (ಪೂರ್ಣಾಂಕ)(ಉಳಿದ_dst_h / scale);
    SDL_Rect curr_src, curr_dst;

    SDL_copyp(&curr_src, &r_src);
    curr_dst.y = r_dst.y;
    curr_dst.w = tile_ಅಗಲ;
    curr_dst.h = tile_ಎತ್ತರ;
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ y = 0; y < ಅಡ್ಡಸಾಲುಗಳು; ++y) {
        curr_dst.x = r_dst.x;
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ x = 0; x < ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ; ++x) {
            ಆದರೆ (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scale_ಬಹುಲಕ)) {
                ಹಿಂತಿರುಗಿ false;
            }
            curr_dst.x += curr_dst.w;
        }
        ಆದರೆ (ಉಳಿದ_dst_w > 0) {
            curr_src.w = ಉಳಿದ_src_w;
            curr_dst.w = ಉಳಿದ_dst_w;
            ಆದರೆ (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scale_ಬಹುಲಕ)) {
                ಹಿಂತಿರುಗಿ false;
            }
            curr_src.w = r_src.w;
            curr_dst.w = tile_ಅಗಲ;
        }
        curr_dst.y += curr_dst.h;
    }
    ಆದರೆ (ಉಳಿದ_dst_h > 0) {
        curr_src.h = ಉಳಿದ_src_h;
        curr_dst.h = ಉಳಿದ_dst_h;
        curr_dst.x = r_dst.x;
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ x = 0; x < ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ; ++x) {
            ಆದರೆ (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scale_ಬಹುಲಕ)) {
                ಹಿಂತಿರುಗಿ false;
            }
            curr_dst.x += curr_dst.w;
        }
        ಆದರೆ (ಉಳಿದ_dst_w > 0) {
            curr_src.w = ಉಳಿದ_src_w;
            curr_dst.w = ಉಳಿದ_dst_w;
            ಆದರೆ (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scale_ಬಹುಲಕ)) {
                ಹಿಂತಿರುಗಿ false;
            }
        }
    }
    ಹಿಂತಿರುಗಿ true;
}

bool SDL_BlitSurface9Grid(SDL_Surface *src, ಸ್ಥಿರಾಂಕ SDL_Rect *srcrect, ಪೂರ್ಣಾಂಕ ಎಡ_ಅಗಲ, ಪೂರ್ಣಾಂಕ ಬಲ_ಅಗಲ, ಪೂರ್ಣಾಂಕ ತುದಿ_ಎತ್ತರ, ಪೂರ್ಣಾಂಕ bottom_ಎತ್ತರ, ದಶಮಾಂಶ scale, SDL_Scale_ಬಹುಲಕ scale_ಬಹುಲಕ, SDL_Surface *dst, ಸ್ಥಿರಾಂಕ SDL_Rect *dstrect)
{
    SDL_Rect ತುಂಬಿದ_src, ತುಂಬಿದ_dst;
    SDL_Rect curr_src, curr_dst;
    ಪೂರ್ಣಾಂಕ dst_ಎಡ_ಅಗಲ;
    ಪೂರ್ಣಾಂಕ dst_ಬಲ_ಅಗಲ;
    ಪೂರ್ಣಾಂಕ dst_ತುದಿ_ಎತ್ತರ;
    ಪೂರ್ಣಾಂಕ dst_bottom_ಎತ್ತರ;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("dst");
    }

    ಆದರೆ (!srcrect) {
        ತುಂಬಿದ_src.x = 0;
        ತುಂಬಿದ_src.y = 0;
        ತುಂಬಿದ_src.w = src->w;
        ತುಂಬಿದ_src.h = src->h;
        srcrect = &ತುಂಬಿದ_src;
    }

    ಆದರೆ (!dstrect) {
        ತುಂಬಿದ_dst.x = 0;
        ತುಂಬಿದ_dst.y = 0;
        ತುಂಬಿದ_dst.w = dst->w;
        ತುಂಬಿದ_dst.h = dst->h;
        dstrect = &ತುಂಬಿದ_dst;
    }

    ಆದರೆ (scale <= 0.0f || scale == 1.0f) {
        dst_ಎಡ_ಅಗಲ = ಎಡ_ಅಗಲ;
        dst_ಬಲ_ಅಗಲ = ಬಲ_ಅಗಲ;
        dst_ತುದಿ_ಎತ್ತರ = ತುದಿ_ಎತ್ತರ;
        dst_bottom_ಎತ್ತರ = bottom_ಎತ್ತರ;
    } ಇಲ್ಲದಿದ್ದರೆ {
        dst_ಎಡ_ಅಗಲ = (ಪೂರ್ಣಾಂಕ)SDL_roundf(ಎಡ_ಅಗಲ * scale);
        dst_ಬಲ_ಅಗಲ = (ಪೂರ್ಣಾಂಕ)SDL_roundf(ಬಲ_ಅಗಲ * scale);
        dst_ತುದಿ_ಎತ್ತರ = (ಪೂರ್ಣಾಂಕ)SDL_roundf(ತುದಿ_ಎತ್ತರ * scale);
        dst_bottom_ಎತ್ತರ = (ಪೂರ್ಣಾಂಕ)SDL_roundf(bottom_ಎತ್ತರ * scale);
    }

    // Upper-left corner
    curr_src.x = srcrect->x;
    curr_src.y = srcrect->y;
    curr_src.w = ಎಡ_ಅಗಲ;
    curr_src.h = ತುದಿ_ಎತ್ತರ;
    curr_dst.x = dstrect->x;
    curr_dst.y = dstrect->y;
    curr_dst.w = dst_ಎಡ_ಅಗಲ;
    curr_dst.h = dst_ತುದಿ_ಎತ್ತರ;
    ಆದರೆ (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_ಬಹುಲಕ)) {
        ಹಿಂತಿರುಗಿ false;
    }

    // Upper-right corner
    curr_src.x = srcrect->x + srcrect->w - ಬಲ_ಅಗಲ;
    curr_src.w = ಬಲ_ಅಗಲ;
    curr_dst.x = dstrect->x + dstrect->w - dst_ಬಲ_ಅಗಲ;
    curr_dst.w = dst_ಬಲ_ಅಗಲ;
    ಆದರೆ (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_ಬಹುಲಕ)) {
        ಹಿಂತಿರುಗಿ false;
    }

    // Lower-right corner
    curr_src.y = srcrect->y + srcrect->h - bottom_ಎತ್ತರ;
    curr_dst.y = dstrect->y + dstrect->h - dst_bottom_ಎತ್ತರ;
    curr_dst.h = dst_bottom_ಎತ್ತರ;
    ಆದರೆ (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_ಬಹುಲಕ)) {
        ಹಿಂತಿರುಗಿ false;
    }

    // Lower-left corner
    curr_src.x = srcrect->x;
    curr_src.w = ಎಡ_ಅಗಲ;
    curr_dst.x = dstrect->x;
    curr_dst.w = dst_ಎಡ_ಅಗಲ;
    ಆದರೆ (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_ಬಹುಲಕ)) {
        ಹಿಂತಿರುಗಿ false;
    }

    //ಎಡ
    curr_src.y = srcrect->y + ತುದಿ_ಎತ್ತರ;
    curr_src.h = srcrect->h - ತುದಿ_ಎತ್ತರ - bottom_ಎತ್ತರ;
    curr_dst.y = dstrect->y + dst_ತುದಿ_ಎತ್ತರ;
    curr_dst.h = dstrect->h - dst_ತುದಿ_ಎತ್ತರ - dst_bottom_ಎತ್ತರ;
    ಆದರೆ (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_ಬಹುಲಕ)) {
        ಹಿಂತಿರುಗಿ false;
    }

    //ಬಲ
    curr_src.x = srcrect->x + srcrect->w - ಬಲ_ಅಗಲ;
    curr_src.w = ಬಲ_ಅಗಲ;
    curr_dst.x = dstrect->x + dstrect->w - dst_ಬಲ_ಅಗಲ;
    curr_dst.w = dst_ಬಲ_ಅಗಲ;
    ಆದರೆ (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_ಬಹುಲಕ)) {
        ಹಿಂತಿರುಗಿ false;
    }

    //ತುದಿ
    curr_src.x = srcrect->x + ಎಡ_ಅಗಲ;
    curr_src.y = srcrect->y;
    curr_src.w = srcrect->w - ಎಡ_ಅಗಲ - ಬಲ_ಅಗಲ;
    curr_src.h = ತುದಿ_ಎತ್ತರ;
    curr_dst.x = dstrect->x + dst_ಎಡ_ಅಗಲ;
    curr_dst.y = dstrect->y;
    curr_dst.w = dstrect->w - dst_ಎಡ_ಅಗಲ - dst_ಬಲ_ಅಗಲ;
    curr_dst.h = dst_ತುದಿ_ಎತ್ತರ;
    ಆದರೆ (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_ಬಹುಲಕ)) {
        ಹಿಂತಿರುಗಿ false;
    }

    // Bottom
    curr_src.y = srcrect->y + srcrect->h - bottom_ಎತ್ತರ;
    curr_dst.y = dstrect->y + dstrect->h - dst_bottom_ಎತ್ತರ;
    curr_dst.h = dst_bottom_ಎತ್ತರ;
    ಆದರೆ (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_ಬಹುಲಕ)) {
        ಹಿಂತಿರುಗಿ false;
    }

    // Center
    curr_src.x = srcrect->x + ಎಡ_ಅಗಲ;
    curr_src.y = srcrect->y + ತುದಿ_ಎತ್ತರ;
    curr_src.w = srcrect->w - ಎಡ_ಅಗಲ - ಬಲ_ಅಗಲ;
    curr_src.h = srcrect->h - ತುದಿ_ಎತ್ತರ - bottom_ಎತ್ತರ;
    curr_dst.x = dstrect->x + dst_ಎಡ_ಅಗಲ;
    curr_dst.y = dstrect->y + dst_ತುದಿ_ಎತ್ತರ;
    curr_dst.w = dstrect->w - dst_ಎಡ_ಅಗಲ - dst_ಬಲ_ಅಗಲ;
    curr_dst.h = dstrect->h - dst_ತುದಿ_ಎತ್ತರ - dst_bottom_ಎತ್ತರ;
    ಆದರೆ (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_ಬಹುಲಕ)) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಹಿಂತಿರುಗಿ true;
}

/*
 * Lock a surface to directly access the pixels
 */
bool SDL_ಬೀಗ_Surface(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("surface");
    }

    ಆದರೆ (!surface->locked) {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_HAVE_RLE
        // Perform the lock
        ಆದರೆ (surface->ಆಂತರಿಕ_flags & SDL_ಆಂತರಿಕ_SURFACE_RLEACCEL) {
            SDL_UnRLESurface(surface);
        }
#ಆದರೆ_ಅಂತ್ಯ
    }

    // Increment the surface lock count, for recursive locks
    ++surface->locked;
    surface->flags |= SDL_SURFACE_LOCKED;
    SDL_Update_Surface_ಬೀಗ_Flag(surface);

    // Ready to go..
    ಹಿಂತಿರುಗಿ true;
}

/*
 * Unlock a previously locked surface
 */
ಶೂನ್ಯ SDL_UnlockSurface(SDL_Surface *surface)
{
    ಆದರೆ (!SDL_SurfaceValid(surface)) {
        ಹಿಂತಿರುಗಿ;
    }

    // Only perform an unlock if we are locked
    ಆದರೆ (!surface->locked || (--surface->locked > 0)) {
        ಹಿಂತಿರುಗಿ;
    }

    surface->flags &= ~SDL_SURFACE_LOCKED;
    SDL_Update_Surface_ಬೀಗ_Flag(surface);
}

ಸ್ಥಿರ bool SDL_FlipSurfaceHorizontal(SDL_Surface *surface)
{
    bool isstack;
    Uint8 *ಅಡ್ಡಸಾಲು, *a, *b, *tmp;
    ಪೂರ್ಣಾಂಕ i, j, bpp;

    ಆದರೆ (SDL_BITSPERPIXEL(surface->format) < 8) {
        // We could implement this if needed, but we'd have to flip sets of bits within a byte
        ಹಿಂತಿರುಗಿ SDL_Unsupported();
    }

    ಆದರೆ (surface->h <= 0) {
        ಹಿಂತಿರುಗಿ true;
    }

    ಆದರೆ (surface->w <= 1) {
        ಹಿಂತಿರುಗಿ true;
    }

    bpp = SDL_BYTESPERPIXEL(surface->format);
    ಅಡ್ಡಸಾಲು = (Uint8 *)surface->pixels;
    tmp = SDL_small_alloc(Uint8, surface->pitch, &isstack);
    ಆದರೆ (!tmp) {
        ಹಿಂತಿರುಗಿ false;
    }
    ಗಾಗಿ (i = surface->h; i--; ) {
        a = ಅಡ್ಡಸಾಲು;
        b = a + (surface->w - 1) * bpp;
        ಗಾಗಿ (j = surface->w / 2; j--; ) {
            SDL_memcpy(tmp, a, bpp);
            SDL_memcpy(a, b, bpp);
            SDL_memcpy(b, tmp, bpp);
            a += bpp;
            b -= bpp;
        }
        ಅಡ್ಡಸಾಲು += surface->pitch;
    }
    SDL_small_free(tmp, isstack);
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool SDL_FlipSurfaceVertical(SDL_Surface *surface)
{
    bool isstack;
    Uint8 *a, *b, *tmp;
    ಪೂರ್ಣಾಂಕ i;

    ಆದರೆ (surface->h <= 1) {
        ಹಿಂತಿರುಗಿ true;
    }

    a = (Uint8 *)surface->pixels;
    b = a + (surface->h - 1) * surface->pitch;
    tmp = SDL_small_alloc(Uint8, surface->pitch, &isstack);
    ಆದರೆ (!tmp) {
        ಹಿಂತಿರುಗಿ false;
    }
    ಗಾಗಿ (i = surface->h / 2; i--; ) {
        SDL_memcpy(tmp, a, surface->pitch);
        SDL_memcpy(a, b, surface->pitch);
        SDL_memcpy(b, tmp, surface->pitch);
        a += surface->pitch;
        b -= surface->pitch;
    }
    SDL_small_free(tmp, isstack);
    ಹಿಂತಿರುಗಿ true;
}

bool SDL_FlipSurface(SDL_Surface *surface, SDL_Flip_ಬಹುಲಕ flip)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("surface");
    }
    ಆದರೆ (!surface->pixels) {
        ಹಿಂತಿರುಗಿ true;
    }

    bool ಫಲಿತಾಂಶ = true;
    ಆಯ್ಕೆ (flip) {
    ಸ್ಥಿತಿ SDL_FLIP_HORIZONTAL:
        ಫಲಿತಾಂಶ = SDL_FlipSurfaceHorizontal(surface);
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_FLIP_VERTICAL:
        ಫಲಿತಾಂಶ = SDL_FlipSurfaceVertical(surface);
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_FLIP_HORIZONTAL_AND_VERTICAL:
        ಫಲಿತಾಂಶ &= SDL_FlipSurfaceHorizontal(surface);
        ಫಲಿತಾಂಶ &= SDL_FlipSurfaceVertical(surface);
        ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        ಫಲಿತಾಂಶ = SDL_InvalidParamError("flip");
        ನಿಲ್ಲಿಸು;
    }
    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

ಸ್ಥಿರ SDL_Surface *SDL_ConvertSurfaceRectAndColorspace(SDL_Surface *surface, ಸ್ಥಿರಾಂಕ SDL_Rect *rect, SDL_PixelFormat format, SDL_Palette *palette, SDL_Colorspace colorspace, SDL_PropertiesID props)
{
    SDL_Palette *ತಾತ್ಕಾಲಿಕ_palette = ಖಾಲಿ;
    SDL_Surface *convert = ಖಾಲಿ;
    SDL_Colorspace src_colorspace;
    SDL_PropertiesID src_properties;
    Uint32 copy_flags;
    SDL_Color copy_color;
    SDL_Rect bounds;
    bool ಫಲಿತಾಂಶ;
    bool palette_ck_transform = false;
    Uint8 palette_ck_ಮೌಲ್ಯ = 0;
    Uint8 *palette_saved_alpha = ಖಾಲಿ;
    ಪೂರ್ಣಾಂಕ palette_saved_alpha_ncolors = 0;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        ಹೋಗು error;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        ಹೋಗು error;
    }

    // Set the bounds of the new surface
    bounds.x = 0;
    bounds.y = 0;
    bounds.w = surface->w;
    bounds.h = surface->h;
    ಆದರೆ (rect) {
        bounds.w = rect->w;
        bounds.h = rect->h;
    } ಇಲ್ಲದಿದ್ದರೆ {
        rect = &bounds;
    }

    // Check for empty destination palette! (results in empty image)
    ಆದರೆ (palette) {
        ಪೂರ್ಣಾಂಕ i;
        ಗಾಗಿ (i = 0; i < palette->ncolors; ++i) {
            ಆದರೆ ((palette->colors[i].r != 0xFF) || (palette->colors[i].g != 0xFF) || (palette->colors[i].b != 0xFF)) {
                ನಿಲ್ಲಿಸು;
            }
        }
        ಆದರೆ (i == palette->ncolors) {
            SDL_ಗಣ_Error("Empty destination palette");
            ಹೋಗು error;
        }
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_ISPIXELFORMAT_ಸೂಚ್ಯಂಕಿತ(format)) {
        // Create a dither palette for conversion
        ತಾತ್ಕಾಲಿಕ_palette = SDL_CreatePalette(1 << SDL_BITSPERPIXEL(format));
        ಆದರೆ (ತಾತ್ಕಾಲಿಕ_palette) {
            SDL_DitherPalette(ತಾತ್ಕಾಲಿಕ_palette);
            palette = ತಾತ್ಕಾಲಿಕ_palette;
        }
    }

    src_colorspace = surface->colorspace;
    src_properties = surface->props;

    // Create a new surface with the desired format
    ಆದರೆ (surface->pixels || SDL_MUSTLOCK(surface)) {
        convert = SDL_CreateSurfaceUninitialized(rect->w, rect->h, format);
    } ಇಲ್ಲದಿದ್ದರೆ {
        convert = SDL_CreateSurfaceFrom(rect->w, rect->h, format, ಖಾಲಿ, 0);
    }
    ಆದರೆ (!convert) {
        ಹೋಗು error;
    }
    ಆದರೆ (SDL_ISPIXELFORMAT_ಸೂಚ್ಯಂಕಿತ(format)) {
        SDL_ಗಣ_Surface_Palette(convert, palette);
    }

    ಆದರೆ (colorspace == SDL_COLORSPACE_UNKNOWN) {
        colorspace = src_colorspace;
    }
    SDL_ಗಣ_Surface_Colorspace(convert, colorspace);

    ಆದರೆ (SDL_ISPIXELFORMAT_FOURCC(format) || SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        ಆದರೆ (surface->format == SDL_PIXELFORMAT_MJPG && format == SDL_PIXELFORMAT_MJPG) {
            // Just do a straight pixel copy of the JPEG image
            size_t ಗಾತ್ರ_2 = (size_t)surface->pitch;
            convert->pixels = SDL_malloc(ಗಾತ್ರ_2);
            ಆದರೆ (!convert->pixels) {
                ಹೋಗು error;
            }
            convert->flags &= ~SDL_SURFACE_PREALLOCATED;
            convert->pitch = surface->pitch;
            SDL_memcpy(convert->pixels, surface->pixels, ಗಾತ್ರ_2);

        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!SDL_ConvertPixelsAndColorspace(surface->w, surface->h, surface->format, src_colorspace, src_properties, surface->pixels, surface->pitch, convert->format, colorspace, props, convert->pixels, convert->pitch)) {
            ಹೋಗು error;
        }

        // Save the original copy flags
        copy_flags = surface->map.info.flags;

        ಹೋಗು ಕೊನೆ;
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
    ಆದರೆ (surface->palette && SDL_ISPIXELFORMAT_ALPHA(format)) {
        bool ಗಣ_opaque = false;

        bool is_opaque, has_alpha_channel;
        SDL_DetectPalette(surface->palette, &is_opaque, &has_alpha_channel);

        ಆದರೆ (is_opaque) {
            ಆದರೆ (!has_alpha_channel) {
                ಗಣ_opaque = true;
            }
        }

        // Set opaque and backup palette alpha values
        ಆದರೆ (ಗಣ_opaque) {
            ಪೂರ್ಣಾಂಕ i;
            palette_saved_alpha_ncolors = surface->palette->ncolors;
            ಆದರೆ (palette_saved_alpha_ncolors > 0) {
                palette_saved_alpha = SDL_ರಾಶಿ_alloc(Uint8, palette_saved_alpha_ncolors);
                ಗಾಗಿ (i = 0; i < palette_saved_alpha_ncolors; i++) {
                    palette_saved_alpha[i] = surface->palette->colors[i].a;
                    surface->palette->colors[i].a = SDL_ALPHA_OPAQUE;
                }
            }
        }
    }

    // Transform colorkey to alpha. for cases where source palette has duplicate values, and colorkey is one of them
    ಆದರೆ (copy_flags & SDL_COPY_COLORKEY) {
        ಆದರೆ (surface->palette && !palette) {
            palette_ck_transform = true;
            palette_ck_ಮೌಲ್ಯ = surface->palette->colors[surface->map.info.colorkey].a;
            surface->palette->colors[surface->map.info.colorkey].a = SDL_ALPHA_TRANSPARENT;
        }
    }

    ಆದರೆ (surface->pixels || SDL_MUSTLOCK(surface)) {
        ಫಲಿತಾಂಶ = SDL_BlitSurfaceUnchecked(surface, rect, convert, &bounds);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಫಲಿತಾಂಶ = true;
    }

    // Restore colorkey alpha value
    ಆದರೆ (palette_ck_transform) {
        surface->palette->colors[surface->map.info.colorkey].a = palette_ck_ಮೌಲ್ಯ;
    }

    // Restore palette alpha values
    ಆದರೆ (palette_saved_alpha) {
        ಪೂರ್ಣಾಂಕ i;
        ಗಾಗಿ (i = 0; i < palette_saved_alpha_ncolors; i++) {
            surface->palette->colors[i].a = palette_saved_alpha[i];
        }
        SDL_ರಾಶಿ_free(palette_saved_alpha);
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
    ಆದರೆ (!ಫಲಿತಾಂಶ) {
        ಹೋಗು error;
    }

    ಆದರೆ (copy_flags & SDL_COPY_COLORKEY) {
        bool ಗಣ_colorkey_by_color = false;
        bool convert_colorkey = true;

        ಆದರೆ (surface->palette) {
            ಆದರೆ (palette &&
                surface->palette->ncolors <= palette->ncolors &&
                (SDL_memcmp(surface->palette->colors, palette->colors,
                            surface->palette->ncolors * ಗಾತ್ರ(SDL_Color)) == 0)) {
                // The palette is identical, just set the same colorkey
                SDL_ಗಣ_Surface_Color_ಕೀಲಿ(convert, true, surface->map.info.colorkey);
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!palette) {
                ಆದರೆ (SDL_ISPIXELFORMAT_ALPHA(format)) {
                    // No need to add the colorkey, transparency is in the alpha channel
                } ಇಲ್ಲದಿದ್ದರೆ {
                    // Only set the colorkey information
                    ಗಣ_colorkey_by_color = true;
                    convert_colorkey = false;
                }
            } ಇಲ್ಲದಿದ್ದರೆ {
                ಗಣ_colorkey_by_color = true;
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಗಣ_colorkey_by_color = true;
        }

        ಆದರೆ (ಗಣ_colorkey_by_color) {
            SDL_Surface *tmp;
            SDL_Surface *tmp2;
            ಪೂರ್ಣಾಂಕ converted_colorkey = 0;

            // Create a dummy surface to get the colorkey converted
            tmp = SDL_CreateSurfaceUninitialized(1, 1, surface->format);
            ಆದರೆ (!tmp) {
                ಹೋಗು error;
            }

            // Share the palette, if any
            ಆದರೆ (surface->palette) {
                SDL_ಗಣ_Surface_Palette(tmp, surface->palette);
            }

            SDL_FillSurfaceRect(tmp, ಖಾಲಿ, surface->map.info.colorkey);

            tmp->map.info.flags &= ~SDL_COPY_COLORKEY;

            // Conversion of the colorkey
            tmp2 = SDL_ConvertSurfaceAndColorspace(tmp, format, palette, colorspace, props);
            ಆದರೆ (!tmp2) {
                SDL_DestroySurface(tmp);
                ಹೋಗು error;
            }

            // Get the converted colorkey
            SDL_memcpy(&converted_colorkey, tmp2->pixels, tmp2->fmt->ಬೈಟುಗಳು_ಪ್ರತಿ_pixel);

            SDL_DestroySurface(tmp);
            SDL_DestroySurface(tmp2);

            // Set the converted colorkey on the new surface
            SDL_ಗಣ_Surface_Color_ಕೀಲಿ(convert, true, converted_colorkey);

            // This is needed when converting for 3D texture upload
            ಆದರೆ (convert_colorkey) {
                SDL_Convert_Colorkey_ಗಮ್ಯ_Alpha(convert, true);
            }
        }
    }

ಕೊನೆ:
    ಆದರೆ (ತಾತ್ಕಾಲಿಕ_palette) {
        SDL_DestroyPalette(ತಾತ್ಕಾಲಿಕ_palette);
    }

    SDL_ಗಣ_Surface_Clip_Rect(convert, &surface->clip_rect);

    /* Enable alpha blending by default if the new surface has an
     * alpha channel or alpha modulation */
    ಆದರೆ (SDL_ISPIXELFORMAT_ALPHA(format) ||
        (copy_flags & SDL_COPY_MODULATE_ALPHA)) {
        SDL_ಗಣ_Surface_Blend_ಬಹುಲಕ(convert, SDL_BLENDMODE_BLEND);
    }
    ಆದರೆ (copy_flags & SDL_COPY_RLE_DESIRED) {
        SDL_ಗಣ_Surface_RLE(convert, true);
    }

    // Copy alternate images
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < surface->ಅಂಕೆ_images; ++i) {
        ಆದರೆ (!SDL_ಕೂಡಿಸು_Surface_Alternate_Image(convert, surface->images[i])) {
            ಹೋಗು error;
        }
    }

    // Copy properties
    ಆದರೆ (surface->props) {
        ಆದರೆ (!SDL_CopyProperties(surface->props, SDL_GetSurfaceProperties(convert))) {
            ಹೋಗು error;
        }

        // Make sure the new surface doesn't reference an old SDL2 surface.
        SDL_ClearProperty(SDL_GetSurfaceProperties(convert), "sdl2-compat.surface2");
    }

    // We're ready to go!
    ಹಿಂತಿರುಗಿ convert;

error:
    ಆದರೆ (ತಾತ್ಕಾಲಿಕ_palette) {
        SDL_DestroyPalette(ತಾತ್ಕಾಲಿಕ_palette);
    }
    ಆದರೆ (convert) {
        SDL_DestroySurface(convert);
    }
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

SDL_Surface *SDL_ConvertSurfaceAndColorspace(SDL_Surface *surface, SDL_PixelFormat format, SDL_Palette *palette, SDL_Colorspace colorspace, SDL_PropertiesID props)
{
    ಹಿಂತಿರುಗಿ SDL_ConvertSurfaceRectAndColorspace(surface, ಖಾಲಿ, format, palette, colorspace, props);
}

SDL_Surface *SDL_RotateSurface(SDL_Surface *surface, ದಶಮಾಂಶ angle)
{
    SDL_Surface *rotated = ಖಾಲಿ;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    SDL_Rect rect_dest;
    ದ್ವಿಗುಣ cangle, sangle;
    SDL_FPoint center = { surface->w * 0.5f, surface->h * 0.5f };
    SDLgfx_rotozoom_Surface_ಗಾತ್ರ_Trig(surface->w, surface->h, angle, &center, &rect_dest, &cangle, &sangle);

    // This function requires a 32-bit surface or 8-bit surface with a colorkey
    ಆದರೆ ((SDL_BITSPERPIXEL(surface->format) == 32 && SDL_PIXELLAYOUT(surface->format) == SDL_PACKEDLAYOUT_8888) ||
        (surface->format == SDL_PIXELFORMAT_INDEX8 && SDL_Surface_Has_Color_ಕೀಲಿ(surface))) {
        rotated = SDLgfx_rotateSurface(surface, angle, 1, 0, 0, &rect_dest, cangle, sangle, &center);
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_Surface *convert = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);
        ಆದರೆ (convert) {
            SDL_Surface *tmp = SDLgfx_rotateSurface(convert, angle, 1, 0, 0, &rect_dest, cangle, sangle, &center);
            ಆದರೆ (tmp) {
                rotated = SDL_ConvertSurfaceAndColorspace(tmp, surface->format, surface->palette, surface->colorspace, surface->props);
                SDL_DestroySurface(tmp);
            }
            SDL_DestroySurface(convert);
        }
    }

    ಆದರೆ (rotated) {
        ಆದರೆ (SDL_HasProperty(surface->props, SDL_PROP_SURFACE_ROTATION_FLOAT)) {
            ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ rotation = (SDL_Get_ಸಂಖ್ಯೆ_Property(surface->props, SDL_PROP_SURFACE_ROTATION_FLOAT, 0) - angle);
            SDL_ಗಣ_Float_Property(SDL_GetSurfaceProperties(rotated), SDL_PROP_SURFACE_ROTATION_FLOAT, rotation);
        }
    }

    ಹಿಂತಿರುಗಿ rotated;
}

SDL_Surface *SDL_DuplicateSurface(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಹಿಂತಿರುಗಿ SDL_ConvertSurfaceAndColorspace(surface, surface->format, surface->palette, surface->colorspace, surface->props);
}

SDL_Surface *SDL_ScaleSurface(SDL_Surface *surface, ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, SDL_Scale_ಬಹುಲಕ scale_ಬಹುಲಕ)
{
    SDL_Surface *convert = ಖಾಲಿ;
    Uint32 copy_flags;
    SDL_Color copy_color;
    bool rc;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        ಹೋಗು error;
    }

    ಆದರೆ (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // We can't directly scale a YUV surface (yet!)
        SDL_Surface *tmp = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        ಆದರೆ (!tmp) {
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }

        SDL_Surface *scaled = SDL_ScaleSurface(tmp, ಅಗಲ, ಎತ್ತರ, scale_ಬಹುಲಕ);
        SDL_DestroySurface(tmp);
        ಆದರೆ (!scaled) {
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }

        SDL_Surface *ಫಲಿತಾಂಶ = SDL_ConvertSurfaceAndColorspace(scaled, surface->format, ಖಾಲಿ, surface->colorspace, surface->props);
        SDL_DestroySurface(scaled);
        ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
    }

    ಆದರೆ (SDL_ISPIXELFORMAT_ಸೂಚ್ಯಂಕಿತ(surface->format)) {
        // Linear scaling requires conversion to RGBA and then slow pixel color lookup
        scale_ಬಹುಲಕ = SDL_SCALEMODE_ಹತ್ತಿರದ;
    }

    // Create a new surface with the desired size
    ಆದರೆ (surface->pixels || SDL_MUSTLOCK(surface)) {
        convert = SDL_CreateSurfaceUninitialized(ಅಗಲ, ಎತ್ತರ, surface->format);
    } ಇಲ್ಲದಿದ್ದರೆ {
        convert = SDL_CreateSurfaceFrom(ಅಗಲ, ಎತ್ತರ, surface->format, ಖಾಲಿ, 0);
    }
    ಆದರೆ (!convert) {
        ಹೋಗು error;
    }
    SDL_ಗಣ_Surface_Palette(convert, surface->palette);
    SDL_ಗಣ_Surface_Colorspace(convert, surface->colorspace);
    SDL_ಗಣ_Surface_RLE(convert, SDL_SurfaceHasRLE(surface));

    ಆದರೆ (surface->pixels || SDL_MUSTLOCK(surface)) {
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

        rc = SDL_BlitSurfaceScaled(surface, ಖಾಲಿ, convert, ಖಾಲಿ, scale_ಬಹುಲಕ);

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
    } ಇಲ್ಲದಿದ್ದರೆ {
        rc = true;
    }

    // SDL_BlitSurfaceScaled failed, and so the conversion
    ಆದರೆ (!rc) {
        ಹೋಗು error;
    }

    // We're ready to go!
    ಹಿಂತಿರುಗಿ convert;

error:
    ಆದರೆ (convert) {
        SDL_DestroySurface(convert);
    }
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

SDL_Surface *SDL_ConvertSurfaceRect(SDL_Surface *surface, ಸ್ಥಿರಾಂಕ SDL_Rect *rect, SDL_PixelFormat format)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಹಿಂತಿರುಗಿ SDL_ConvertSurfaceRectAndColorspace(surface, rect, format, ಖಾಲಿ, SDL_GetDefaultColorspaceForFormat(format), surface->props);
}

SDL_Surface *SDL_ConvertSurface(SDL_Surface *surface, SDL_PixelFormat format)
{
    ಹಿಂತಿರುಗಿ SDL_ConvertSurfaceRect(surface, ಖಾಲಿ, format);
}

SDL_Surface *SDL_DuplicatePixels(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, SDL_PixelFormat format, SDL_Colorspace colorspace, ಶೂನ್ಯ *pixels, ಪೂರ್ಣಾಂಕ pitch)
{
    SDL_Surface *surface;
    ಆದರೆ (pixels) {
        surface = SDL_CreateSurfaceUninitialized(ಅಗಲ, ಎತ್ತರ, format);
    } ಇಲ್ಲದಿದ್ದರೆ {
        surface = SDL_CreateSurfaceFrom(ಅಗಲ, ಎತ್ತರ, format, ಖಾಲಿ, 0);
    }
    ಆದರೆ (!surface) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    SDL_ಗಣ_Surface_Colorspace(surface, colorspace);

    ಆದರೆ (surface->pixels) {
        ಪೂರ್ಣಾಂಕ ಉದ್ದಳತೆ = ಅಗಲ * SDL_BYTESPERPIXEL(format);
        Uint8 *src = (Uint8 *)pixels;
        Uint8 *dst = (Uint8 *)surface->pixels;
        ಪೂರ್ಣಾಂಕ ಅಡ್ಡಸಾಲುಗಳು = ಎತ್ತರ;
        ಆಗ (ಅಡ್ಡಸಾಲುಗಳು--) {
            SDL_memcpy(dst, src, ಉದ್ದಳತೆ);
            dst += surface->pitch;
            src += pitch;
        }
    }
    ಹಿಂತಿರುಗಿ surface;
}

bool SDL_ConvertPixelsAndColorspace(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ,
                      SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಂಕ src_pitch,
                      SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಂಕ dst_pitch)
{
    SDL_Surface src_surface;
    SDL_Surface dst_surface;
    SDL_Rect rect;
    ಶೂನ್ಯ *nonconst_src = (ಶೂನ್ಯ *)src;
    bool ಫಲಿತಾಂಶ;

    CHECK_PARAM(!src) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!src_pitch) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("src_pitch");
    }
    CHECK_PARAM(!dst) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("dst");
    }
    CHECK_PARAM(!dst_pitch) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("dst_pitch");
    }

    ಆದರೆ (src_colorspace == SDL_COLORSPACE_UNKNOWN) {
        src_colorspace = SDL_GetDefaultColorspaceForFormat(src_format);
    }
    ಆದರೆ (dst_colorspace == SDL_COLORSPACE_UNKNOWN) {
        dst_colorspace = SDL_GetDefaultColorspaceForFormat(dst_format);
    }

    ಆದರೆ (src_format == SDL_PIXELFORMAT_MJPG) {
        ಹಿಂತಿರುಗಿ SDL_ConvertPixels_STB(ಅಗಲ, ಎತ್ತರ, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_HAVE_YUV
    ಆದರೆ (SDL_ISPIXELFORMAT_FOURCC(src_format) && SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        ಹಿಂತಿರುಗಿ SDL_Convert_Pixels_YUV_ಗಮ್ಯ_YUV(ಅಗಲ, ಎತ್ತರ, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_ISPIXELFORMAT_FOURCC(src_format)) {
        ಹಿಂತಿರುಗಿ SDL_Convert_Pixels_YUV_ಗಮ್ಯ_RGB(ಅಗಲ, ಎತ್ತರ, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        ಹಿಂತಿರುಗಿ SDL_Convert_Pixels_RGB_ಗಮ್ಯ_YUV(ಅಗಲ, ಎತ್ತರ, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    }
#ಇಲ್ಲದಿದ್ದರೆ
    ಆದರೆ (SDL_ISPIXELFORMAT_FOURCC(src_format) || SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("SDL not built with YUV support");
    }
#ಆದರೆ_ಅಂತ್ಯ

    // Fast path for same format copy
    ಆದರೆ (src_format == dst_format && src_colorspace == dst_colorspace) {
        ಆದರೆ (src_pitch == dst_pitch) {
            SDL_memcpy(dst, src, ಎತ್ತರ * src_pitch);
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಪೂರ್ಣಾಂಕ i;
            ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ bpp = SDL_BYTESPERPIXEL(src_format);
            ಅಗಲ *= bpp;
            ಗಾಗಿ (i = ಎತ್ತರ; i--;) {
                SDL_memcpy(dst, src, ಅಗಲ);
                src = (ಸ್ಥಿರಾಂಕ Uint8 *)src + src_pitch;
                dst = (Uint8 *)dst + dst_pitch;
            }
        }
        ಹಿಂತಿರುಗಿ true;
    }

    ಆದರೆ (!SDL_InitializeSurface(&src_surface, ಅಗಲ, ಎತ್ತರ, src_format, src_colorspace, src_properties, nonconst_src, src_pitch, true)) {
        ಹಿಂತಿರುಗಿ false;
    }
    SDL_ಗಣ_Surface_Blend_ಬಹುಲಕ(&src_surface, SDL_BLENDMODE_NONE);

    ಆದರೆ (!SDL_InitializeSurface(&dst_surface, ಅಗಲ, ಎತ್ತರ, dst_format, dst_colorspace, dst_properties, dst, dst_pitch, true)) {
        ಹಿಂತಿರುಗಿ false;
    }

    // Set up the rect and go!
    rect.x = 0;
    rect.y = 0;
    rect.w = ಅಗಲ;
    rect.h = ಎತ್ತರ;
    ಫಲಿತಾಂಶ = SDL_BlitSurfaceUnchecked(&src_surface, &rect, &dst_surface, &rect);

    SDL_DestroySurface(&src_surface);
    SDL_DestroySurface(&dst_surface);

    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

bool SDL_ConvertPixels(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, SDL_PixelFormat src_format, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಂಕ src_pitch, SDL_PixelFormat dst_format, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಂಕ dst_pitch)
{
    ಹಿಂತಿರುಗಿ SDL_ConvertPixelsAndColorspace(ಅಗಲ, ಎತ್ತರ,
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

ಸ್ಥಿರ ಶೂನ್ಯ SDL_PremultiplyAlpha_AXYZ8888(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಂಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಂಕ dst_pitch)
{
    ಪೂರ್ಣಾಂಕ c;
    Uint32 srcpixel;
    Uint32 srcR, srcG, srcB, srcA;
    Uint32 dstpixel;
    Uint32 dstR, dstG, dstB, dstA;

    ಆಗ (ಎತ್ತರ--) {
        ಸ್ಥಿರಾಂಕ Uint32 *src_px = (ಸ್ಥಿರಾಂಕ Uint32 *)src;
        Uint32 *dst_px = (Uint32 *)dst;
        ಗಾಗಿ (c = ಅಗಲ; c; --c) {
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
        src = (ಸ್ಥಿರಾಂಕ Uint8 *)src + src_pitch;
        dst = (Uint8 *)dst + dst_pitch;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ SDL_PremultiplyAlpha_XYZA8888(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಂಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಂಕ dst_pitch)
{
    ಪೂರ್ಣಾಂಕ c;
    Uint32 srcpixel;
    Uint32 srcR, srcG, srcB, srcA;
    Uint32 dstpixel;
    Uint32 dstR, dstG, dstB, dstA;

    ಆಗ (ಎತ್ತರ--) {
        ಸ್ಥಿರಾಂಕ Uint32 *src_px = (ಸ್ಥಿರಾಂಕ Uint32 *)src;
        Uint32 *dst_px = (Uint32 *)dst;
        ಗಾಗಿ (c = ಅಗಲ; c; --c) {
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
        src = (ಸ್ಥಿರಾಂಕ Uint8 *)src + src_pitch;
        dst = (Uint8 *)dst + dst_pitch;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ SDL_PremultiplyAlpha_AXYZ128(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಂಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಂಕ dst_pitch)
{
    ಪೂರ್ಣಾಂಕ c;
    ದಶಮಾಂಶ flR, flG, flB, flA;

    ಆಗ (ಎತ್ತರ--) {
        ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src_px = (ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *)src;
        ದಶಮಾಂಶ *dst_px = (ದಶಮಾಂಶ *)dst;
        ಗಾಗಿ (c = ಅಗಲ; c; --c) {
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
        src = (ಸ್ಥಿರಾಂಕ Uint8 *)src + src_pitch;
        dst = (Uint8 *)dst + dst_pitch;
    }
}

ಸ್ಥಿರ bool SDL_PremultiplyAlphaPixelsAndColorspace(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಂಕ src_pitch, SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಂಕ dst_pitch, bool ರೇಖೀಯ)
{
    SDL_Surface *convert = ಖಾಲಿ;
    ಶೂನ್ಯ *final_dst = dst;
    ಪೂರ್ಣಾಂಕ final_dst_pitch = dst_pitch;
    SDL_PixelFormat format;
    SDL_Colorspace colorspace;
    bool ಫಲಿತಾಂಶ = false;

    CHECK_PARAM(!src) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!src_pitch) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("src_pitch");
    }
    CHECK_PARAM(!dst) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("dst");
    }
    CHECK_PARAM(!dst_pitch) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("dst_pitch");
    }

    // Use a high precision format if we're converting to linear colorspace or using high precision pixel formats
    ಆದರೆ (ರೇಖೀಯ ||
        SDL_ISPIXELFORMAT_10_ಬಿಟ್(src_format) || SDL_BITSPERPIXEL(src_format) > 32 ||
        SDL_ISPIXELFORMAT_10_ಬಿಟ್(dst_format) || SDL_BITSPERPIXEL(dst_format) > 32) {
        ಆದರೆ (src_format == SDL_PIXELFORMAT_ARGB128_FLOAT ||
            src_format == SDL_PIXELFORMAT_ABGR128_FLOAT) {
            format = src_format;
        } ಇಲ್ಲದಿದ್ದರೆ {
            format = SDL_PIXELFORMAT_ARGB128_FLOAT;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (src_format == SDL_PIXELFORMAT_ARGB8888 ||
            src_format == SDL_PIXELFORMAT_ABGR8888 ||
            src_format == SDL_PIXELFORMAT_RGBA8888 ||
            src_format == SDL_PIXELFORMAT_BGRA8888) {
            format = src_format;
        } ಇಲ್ಲದಿದ್ದರೆ {
            format = SDL_PIXELFORMAT_ARGB8888;
        }
    }
    ಆದರೆ (ರೇಖೀಯ) {
        colorspace = SDL_COLORSPACE_SRGB_ರೇಖೀಯ;
    } ಇಲ್ಲದಿದ್ದರೆ {
        colorspace = SDL_COLORSPACE_SRGB;
    }

    ಆದರೆ (src_format != format || src_colorspace != colorspace) {
        convert = SDL_CreateSurfaceUninitialized(ಅಗಲ, ಎತ್ತರ, format);
        ಆದರೆ (!convert) {
            ಹೋಗು ಮುಗಿದ;
        }
        ಆದರೆ (!SDL_ConvertPixelsAndColorspace(ಅಗಲ, ಎತ್ತರ, src_format, src_colorspace, src_properties, src, src_pitch, format, colorspace, 0, convert->pixels, convert->pitch)) {
            ಹೋಗು ಮುಗಿದ;
        }

        src = convert->pixels;
        src_pitch = convert->pitch;
        dst = convert->pixels;
        dst_pitch = convert->pitch;

    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (dst_format != format || dst_colorspace != colorspace) {
        convert = SDL_CreateSurfaceUninitialized(ಅಗಲ, ಎತ್ತರ, format);
        ಆದರೆ (!convert) {
            ಹೋಗು ಮುಗಿದ;
        }
        dst = convert->pixels;
        dst_pitch = convert->pitch;
    }

    ಆಯ್ಕೆ (format) {
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_ARGB8888:
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_ABGR8888:
        SDL_PremultiplyAlpha_AXYZ8888(ಅಗಲ, ಎತ್ತರ, src, src_pitch, dst, dst_pitch);
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGBA8888:
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_BGRA8888:
        SDL_PremultiplyAlpha_XYZA8888(ಅಗಲ, ಎತ್ತರ, src, src_pitch, dst, dst_pitch);
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_ARGB128_FLOAT:
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_ABGR128_FLOAT:
        SDL_PremultiplyAlpha_AXYZ128(ಅಗಲ, ಎತ್ತರ, src, src_pitch, dst, dst_pitch);
        ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        SDL_ಗಣ_Error("Unexpected internal pixel format");
        ಹೋಗು ಮುಗಿದ;
    }

    ಆದರೆ (dst != final_dst) {
        ಆದರೆ (!SDL_ConvertPixelsAndColorspace(ಅಗಲ, ಎತ್ತರ, format, colorspace, 0, convert->pixels, convert->pitch, dst_format, dst_colorspace, dst_properties, final_dst, final_dst_pitch)) {
            ಹೋಗು ಮುಗಿದ;
        }
    }
    ಫಲಿತಾಂಶ = true;

ಮುಗಿದ:
    ಆದರೆ (convert) {
        SDL_DestroySurface(convert);
    }
    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

bool SDL_PremultiplyAlpha(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ,
                         SDL_PixelFormat src_format, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಂಕ src_pitch,
                         SDL_PixelFormat dst_format, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಂಕ dst_pitch, bool ರೇಖೀಯ)
{
    SDL_Colorspace src_colorspace = SDL_GetDefaultColorspaceForFormat(src_format);
    SDL_Colorspace dst_colorspace = SDL_GetDefaultColorspaceForFormat(dst_format);

    ಹಿಂತಿರುಗಿ SDL_PremultiplyAlphaPixelsAndColorspace(ಅಗಲ, ಎತ್ತರ, src_format, src_colorspace, 0, src, src_pitch, dst_format, dst_colorspace, 0, dst, dst_pitch, ರೇಖೀಯ);
}

bool SDL_PremultiplySurfaceAlpha(SDL_Surface *surface, bool ರೇಖೀಯ)
{
    SDL_Colorspace colorspace;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("surface");
    }

    colorspace = surface->colorspace;

    ಹಿಂತಿರುಗಿ SDL_PremultiplyAlphaPixelsAndColorspace(surface->w, surface->h, surface->format, colorspace, surface->props, surface->pixels, surface->pitch, surface->format, colorspace, surface->props, surface->pixels, surface->pitch, ರೇಖೀಯ);
}

bool SDL_ClearSurface(SDL_Surface *surface, ದಶಮಾಂಶ r, ದಶಮಾಂಶ g, ದಶಮಾಂಶ b, ದಶಮಾಂಶ a)
{
    SDL_Rect clip_rect;
    bool ಫಲಿತಾಂಶ = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("surface");
    }

    SDL_GetSurfaceClipRect(surface, &clip_rect);
    SDL_ಗಣ_Surface_Clip_Rect(surface, ಖಾಲಿ);

    ಆದರೆ (!SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_BYTESPERPIXEL(surface->format) <= ಗಾತ್ರ(Uint32)) {
        Uint32 color;

        color = SDL_MapSurfaceRGBA(surface,
                    (Uint8)SDL_roundf(SDL_clamp(r, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(g, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(b, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(a, 0.0f, 1.0f) * 255.0f));
        ಫಲಿತಾಂಶ = SDL_FillSurfaceRect(surface, ಖಾಲಿ, color);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // We can't directly set an RGB value on a YUV surface
        SDL_Surface *tmp = SDL_CreateSurfaceUninitialized(surface->w, surface->h, SDL_PIXELFORMAT_ARGB8888);
        ಆದರೆ (!tmp) {
            ಹೋಗು ಮುಗಿದ;
        }

        ಆದರೆ (SDL_ClearSurface(tmp, r, g, b, a)) {
            ಫಲಿತಾಂಶ = SDL_ConvertPixelsAndColorspace(surface->w, surface->h, tmp->format, tmp->colorspace, tmp->props, tmp->pixels, tmp->pitch, surface->format, surface->colorspace, surface->props, surface->pixels, surface->pitch);
        }
        SDL_DestroySurface(tmp);
    } ಇಲ್ಲದಿದ್ದರೆ {
        // Take advantage of blit color conversion
        SDL_Surface *tmp = SDL_CreateSurfaceUninitialized(1, 1, SDL_PIXELFORMAT_RGBA128_FLOAT);
        ಆದರೆ (!tmp) {
            ಹೋಗು ಮುಗಿದ;
        }
        SDL_ಗಣ_Surface_Colorspace(tmp, surface->colorspace);
        SDL_ಗಣ_Surface_Blend_ಬಹುಲಕ(tmp, SDL_BLENDMODE_NONE);

        ದಶಮಾಂಶ *pixels = (ದಶಮಾಂಶ *)tmp->pixels;
        pixels[0] = r;
        pixels[1] = g;
        pixels[2] = b;
        pixels[3] = a;

        ಫಲಿತಾಂಶ = SDL_BlitSurfaceScaled(tmp, ಖಾಲಿ, surface, ಖಾಲಿ, SDL_SCALEMODE_ಹತ್ತಿರದ);
        SDL_DestroySurface(tmp);
    }

ಮುಗಿದ:
    SDL_ಗಣ_Surface_Clip_Rect(surface, &clip_rect);

    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

Uint32 SDL_MapSurfaceRGB(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b)
{
    ಹಿಂತಿರುಗಿ SDL_MapSurfaceRGBA(surface, r, g, b, SDL_ALPHA_OPAQUE);
}

Uint32 SDL_MapSurfaceRGBA(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        ಹಿಂತಿರುಗಿ true;
    }
    ಹಿಂತಿರುಗಿ SDL_MapRGBA(surface->fmt, surface->palette, r, g, b, a);
}

// This function Copyright 2023 Collabora Ltd., contributed to SDL under the ZLib license
bool SDL_ReadSurfacePixel(SDL_Surface *surface, ಪೂರ್ಣಾಂಕ x, ಪೂರ್ಣಾಂಕ y, Uint8 *r, Uint8 *g, Uint8 *b, Uint8 *a)
{
    Uint32 pixel = 0;
    size_t ಬೈಟುಗಳು_ಪ್ರತಿ_pixel;
    Uint8 ಬಳಸದ;
    Uint8 *p;
    bool ಫಲಿತಾಂಶ = false;

    ಆದರೆ (r) {
        *r = 0;
    } ಇಲ್ಲದಿದ್ದರೆ {
        r = &ಬಳಸದ;
    }

    ಆದರೆ (g) {
        *g = 0;
    } ಇಲ್ಲದಿದ್ದರೆ {
        g = &ಬಳಸದ;
    }

    ಆದರೆ (b) {
        *b = 0;
    } ಇಲ್ಲದಿದ್ದರೆ {
        b = &ಬಳಸದ;
    }

    ಆದರೆ (a) {
        *a = 0;
    } ಇಲ್ಲದಿದ್ದರೆ {
        a = &ಬಳಸದ;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("y");
    }

    ಬೈಟುಗಳು_ಪ್ರತಿ_pixel = SDL_BYTESPERPIXEL(surface->format);

    ಆದರೆ (SDL_MUSTLOCK(surface)) {
        ಆದರೆ (!SDL_ಬೀಗ_Surface(surface)) {
            ಹಿಂತಿರುಗಿ false;
        }
    }

    p = (Uint8 *)surface->pixels + y * surface->pitch + x * ಬೈಟುಗಳು_ಪ್ರತಿ_pixel;

    ಆದರೆ (ಬೈಟುಗಳು_ಪ್ರತಿ_pixel <= ಗಾತ್ರ(pixel) &&
        !SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_COLORSPACEPRIMARIES(surface->colorspace) == SDL_COLOR_PRIMARIES_BT709) {
        /* Fill the appropriate number of least-significant bytes of pixel,
         * leaving the most-significant bytes set to zero */
#ಆದರೆ SDL_BYTEORDER == SDL_BIG_ENDIAN
        SDL_memcpy(((Uint8 *)&pixel) + (ಗಾತ್ರ(pixel) - ಬೈಟುಗಳು_ಪ್ರತಿ_pixel), p, ಬೈಟುಗಳು_ಪ್ರತಿ_pixel);
#ಇಲ್ಲದಿದ್ದರೆ
        SDL_memcpy(&pixel, p, ಬೈಟುಗಳು_ಪ್ರತಿ_pixel);
#ಆದರೆ_ಅಂತ್ಯ
        SDL_GetRGBA(pixel, surface->fmt, surface->palette, r, g, b, a);
        ಫಲಿತಾಂಶ = true;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // FIXME: We need code to extract a single macroblock from a YUV surface
        SDL_Surface *converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        ಆದರೆ (converted) {
            ಫಲಿತಾಂಶ = SDL_ReadSurfacePixel(converted, x, y, r, g, b, a);
            SDL_DestroySurface(converted);
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        // This is really slow, but it gets the job done
        Uint8 rgba[4];

        ಆದರೆ (SDL_ConvertPixelsAndColorspace(1, 1, surface->format, surface->colorspace, surface->props, p, surface->pitch, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, rgba, ಗಾತ್ರ(rgba))) {
            *r = rgba[0];
            *g = rgba[1];
            *b = rgba[2];
            *a = rgba[3];
            ಫಲಿತಾಂಶ = true;
        }
    }

    ಆದರೆ (SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }
    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

bool SDL_ReadSurfacePixelFloat(SDL_Surface *surface, ಪೂರ್ಣಾಂಕ x, ಪೂರ್ಣಾಂಕ y, ದಶಮಾಂಶ *r, ದಶಮಾಂಶ *g, ದಶಮಾಂಶ *b, ದಶಮಾಂಶ *a)
{
    ದಶಮಾಂಶ ಬಳಸದ;
    bool ಫಲಿತಾಂಶ = false;

    ಆದರೆ (r) {
        *r = 0.0f;
    } ಇಲ್ಲದಿದ್ದರೆ {
        r = &ಬಳಸದ;
    }

    ಆದರೆ (g) {
        *g = 0.0f;
    } ಇಲ್ಲದಿದ್ದರೆ {
        g = &ಬಳಸದ;
    }

    ಆದರೆ (b) {
        *b = 0.0f;
    } ಇಲ್ಲದಿದ್ದರೆ {
        b = &ಬಳಸದ;
    }

    ಆದರೆ (a) {
        *a = 0.0f;
    } ಇಲ್ಲದಿದ್ದರೆ {
        a = &ಬಳಸದ;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("y");
    }

    ಆದರೆ (SDL_BYTESPERPIXEL(surface->format) <= ಗಾತ್ರ(Uint32) &&
        !SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_COLORSPACEPRIMARIES(surface->colorspace) == SDL_COLOR_PRIMARIES_BT709) {
        Uint8 r8, g8, b8, a8;

        ಆದರೆ (SDL_ReadSurfacePixel(surface, x, y, &r8, &g8, &b8, &a8)) {
            *r = (ದಶಮಾಂಶ)r8 / 255.0f;
            *g = (ದಶಮಾಂಶ)g8 / 255.0f;
            *b = (ದಶಮಾಂಶ)b8 / 255.0f;
            *a = (ದಶಮಾಂಶ)a8 / 255.0f;
            ಫಲಿತಾಂಶ = true;
        }
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // FIXME: We need code to extract a single macroblock from a YUV surface
        SDL_Surface *converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        ಆದರೆ (converted) {
            ಫಲಿತಾಂಶ = SDL_ReadSurfacePixelFloat(converted, x, y, r, g, b, a);
            SDL_DestroySurface(converted);
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        // This is really slow, but it gets the job done
        ದಶಮಾಂಶ rgba[4];
        Uint8 *p;

        ಆದರೆ (SDL_MUSTLOCK(surface)) {
            ಆದರೆ (!SDL_ಬೀಗ_Surface(surface)) {
                ಹಿಂತಿರುಗಿ false;
            }
        }

        p = (Uint8 *)surface->pixels + y * surface->pitch + x * SDL_BYTESPERPIXEL(surface->format);

        ಆದರೆ (surface->format == SDL_PIXELFORMAT_RGBA128_FLOAT) {
            SDL_memcpy(rgba, p, ಗಾತ್ರ(rgba));
            ಫಲಿತಾಂಶ = true;
        } ಇಲ್ಲದಿದ್ದರೆ {
            SDL_Colorspace src_colorspace = surface->colorspace;
            SDL_Colorspace dst_colorspace = (src_colorspace == SDL_COLORSPACE_SRGB_ರೇಖೀಯ ? SDL_COLORSPACE_SRGB_ರೇಖೀಯ : SDL_COLORSPACE_SRGB);

            ಆದರೆ (SDL_ConvertPixelsAndColorspace(1, 1, surface->format, src_colorspace, surface->props, p, surface->pitch, SDL_PIXELFORMAT_RGBA128_FLOAT, dst_colorspace, 0, rgba, ಗಾತ್ರ(rgba))) {
                ಫಲಿತಾಂಶ = true;
            }
        }

        ಆದರೆ (ಫಲಿತಾಂಶ) {
            *r = rgba[0];
            *g = rgba[1];
            *b = rgba[2];
            *a = rgba[3];
        }

        ಆದರೆ (SDL_MUSTLOCK(surface)) {
            SDL_UnlockSurface(surface);
        }
    }
    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

bool SDL_WriteSurfacePixel(SDL_Surface *surface, ಪೂರ್ಣಾಂಕ x, ಪೂರ್ಣಾಂಕ y, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    Uint32 pixel = 0;
    size_t ಬೈಟುಗಳು_ಪ್ರತಿ_pixel;
    Uint8 *p;
    bool ಫಲಿತಾಂಶ = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("y");
    }

    ಬೈಟುಗಳು_ಪ್ರತಿ_pixel = SDL_BYTESPERPIXEL(surface->format);

    ಆದರೆ (SDL_MUSTLOCK(surface)) {
        ಆದರೆ (!SDL_ಬೀಗ_Surface(surface)) {
            ಹಿಂತಿರುಗಿ false;
        }
    }

    p = (Uint8 *)surface->pixels + y * surface->pitch + x * ಬೈಟುಗಳು_ಪ್ರತಿ_pixel;

    ಆದರೆ (ಬೈಟುಗಳು_ಪ್ರತಿ_pixel <= ಗಾತ್ರ(pixel) && !SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        pixel = SDL_MapRGBA(surface->fmt, surface->palette, r, g, b, a);
#ಆದರೆ SDL_BYTEORDER == SDL_BIG_ENDIAN
        SDL_memcpy(p, ((Uint8 *)&pixel) + (ಗಾತ್ರ(pixel) - ಬೈಟುಗಳು_ಪ್ರತಿ_pixel), ಬೈಟುಗಳು_ಪ್ರತಿ_pixel);
#ಇಲ್ಲದಿದ್ದರೆ
        SDL_memcpy(p, &pixel, ಬೈಟುಗಳು_ಪ್ರತಿ_pixel);
#ಆದರೆ_ಅಂತ್ಯ
        ಫಲಿತಾಂಶ = true;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        ಫಲಿತಾಂಶ = SDL_Unsupported();
    } ಇಲ್ಲದಿದ್ದರೆ {
        // This is really slow, but it gets the job done
        Uint8 rgba[4];

        rgba[0] = r;
        rgba[1] = g;
        rgba[2] = b;
        rgba[3] = a;
        ಫಲಿತಾಂಶ = SDL_ConvertPixelsAndColorspace(1, 1, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, rgba, ಗಾತ್ರ(rgba), surface->format, surface->colorspace, surface->props, p, surface->pitch);
    }

    ಆದರೆ (SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }
    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

bool SDL_WriteSurfacePixelFloat(SDL_Surface *surface, ಪೂರ್ಣಾಂಕ x, ಪೂರ್ಣಾಂಕ y, ದಶಮಾಂಶ r, ದಶಮಾಂಶ g, ದಶಮಾಂಶ b, ದಶಮಾಂಶ a)
{
    bool ಫಲಿತಾಂಶ = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("y");
    }

    ಆದರೆ (SDL_BYTESPERPIXEL(surface->format) <= ಗಾತ್ರ(Uint32) && !SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        Uint8 r8, g8, b8, a8;

        r8 = (Uint8)SDL_ಸುತ್ತು(SDL_clamp(r, 0.0f, 1.0f) * 255.0f);
        g8 = (Uint8)SDL_ಸುತ್ತು(SDL_clamp(g, 0.0f, 1.0f) * 255.0f);
        b8 = (Uint8)SDL_ಸುತ್ತು(SDL_clamp(b, 0.0f, 1.0f) * 255.0f);
        a8 = (Uint8)SDL_ಸುತ್ತು(SDL_clamp(a, 0.0f, 1.0f) * 255.0f);
        ಆದರೆ (SDL_WriteSurfacePixel(surface, x, y, r8, g8, b8, a8)) {
            ಫಲಿತಾಂಶ = true;
        }
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        ಫಲಿತಾಂಶ = SDL_Unsupported();
    } ಇಲ್ಲದಿದ್ದರೆ {
        // This is really slow, but it gets the job done
        ದಶಮಾಂಶ rgba[4];
        Uint8 *p;

        ಆದರೆ (SDL_MUSTLOCK(surface)) {
            ಆದರೆ (!SDL_ಬೀಗ_Surface(surface)) {
                ಹಿಂತಿರುಗಿ false;
            }
        }

        p = (Uint8 *)surface->pixels + y * surface->pitch + x * SDL_BYTESPERPIXEL(surface->format);

        rgba[0] = r;
        rgba[1] = g;
        rgba[2] = b;
        rgba[3] = a;

        ಆದರೆ (surface->format == SDL_PIXELFORMAT_RGBA128_FLOAT) {
            SDL_memcpy(p, rgba, ಗಾತ್ರ(rgba));
            ಫಲಿತಾಂಶ = true;
        } ಇಲ್ಲದಿದ್ದರೆ {
            SDL_Colorspace dst_colorspace = surface->colorspace;
            SDL_Colorspace src_colorspace = (dst_colorspace == SDL_COLORSPACE_SRGB_ರೇಖೀಯ ? SDL_COLORSPACE_SRGB_ರೇಖೀಯ : SDL_COLORSPACE_SRGB);

            ಫಲಿತಾಂಶ = SDL_ConvertPixelsAndColorspace(1, 1, SDL_PIXELFORMAT_RGBA128_FLOAT, src_colorspace, 0, rgba, ಗಾತ್ರ(rgba), surface->format, dst_colorspace, surface->props, p, surface->pitch);
        }

        ಆದರೆ (SDL_MUSTLOCK(surface)) {
            SDL_UnlockSurface(surface);
        }
    }
    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

/*
 * Free a surface created by the above function.
 */
ಶೂನ್ಯ SDL_DestroySurface(SDL_Surface *surface)
{
    ಆದರೆ (!SDL_SurfaceValid(surface)) {
        ಹಿಂತಿರುಗಿ;
    }
    ಆದರೆ (surface->ಆಂತರಿಕ_flags & SDL_ಆಂತರಿಕ_SURFACE_DONTFREE) {
        ಹಿಂತಿರುಗಿ;
    }
    ಆದರೆ (--surface->refcount > 0) {
        ಹಿಂತಿರುಗಿ;
    }

    SDL_RemoveSurfaceAlternateImages(surface);

    SDL_DestroyProperties(surface->props);

    SDL_InvalidateMap(&surface->map);

    ಆಗ (surface->locked > 0) {
        SDL_UnlockSurface(surface);
    }
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_HAVE_RLE
    ಆದರೆ (surface->ಆಂತರಿಕ_flags & SDL_ಆಂತರಿಕ_SURFACE_RLEACCEL) {
        SDL_UnRLESurface(surface);
    }
#ಆದರೆ_ಅಂತ್ಯ
    SDL_ಗಣ_Surface_Palette(surface, ಖಾಲಿ);

    ಆದರೆ (surface->flags & SDL_SURFACE_PREALLOCATED) {
        // Don't free
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (surface->flags & SDL_SURFACE_SIMD_ALIGNED) {
        // Free aligned
        SDL_aligned_free(surface->pixels);
    } ಇಲ್ಲದಿದ್ದರೆ {
        // Normal
        SDL_free(surface->pixels);
    }

    surface->reserved = ಖಾಲಿ;

    ಆದರೆ (!(surface->ಆಂತರಿಕ_flags & SDL_ಆಂತರಿಕ_SURFACE_ರಾಶಿ)) {
        SDL_free(surface);
    }
}

SDL_Surface *SDL_ತುಂಬು_Surface_IO(SDL_IOStream *src, bool closeio)
{
    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಆದರೆ (SDL_IsBMP(src)) {
        ಹಿಂತಿರುಗಿ SDL_ತುಂಬು_BMP_IO(src, closeio);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_IsPNG(src)) {
        ಹಿಂತಿರುಗಿ SDL_ತುಂಬು_PNG_IO(src, closeio);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_IsJPG(src)) {
        ಹಿಂತಿರುಗಿ SDL_ತುಂಬು_JPG_IO(src, closeio);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (closeio) {
            SDL_CloseIO(src);
        }
        SDL_ಗಣ_Error("Unsupported image format");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
}

SDL_Surface *SDL_ತುಂಬು_Surface(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *file)
{
    SDL_IOStream *ಹರಿವು = SDL_IOFromFile(file, "rb");
    ಆದರೆ (!ಹರಿವು) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಹಿಂತಿರುಗಿ SDL_ತುಂಬು_Surface_IO(ಹರಿವು, true);
}
