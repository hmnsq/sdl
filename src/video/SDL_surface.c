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
#అన్తర్భావ "SDL_internal.h"

#అన్తర్భావ "SDL_sysvideo.h"
#అన్తర్భావ "SDL_video_c.h"
#అన్తర్భావ "SDL_RLEaccel_c.h"
#అన్తర్భావ "SDL_pixels_c.h"
#అన్తర్భావ "SDL_rotate.h"
#అన్తర్భావ "SDL_stb_c.h"
#అన్తర్భావ "SDL_yuv_c.h"
#అన్తర్భావ "../render/SDL_sysrender.h"

#అన్తర్భావ "SDL_surface_c.h"


// Check to make sure we can safely check multiplication of surface w and pitch and it won't overflow size_t
SDL_COMPILE_సమయం_ASSERT(surface_కొలత_assumptions,
                        పరిమాణం(పూర్ణాంకం) == పరిమాణం(Sint32) && పరిమాణం(size_t) >= పరిమాణం(Sint32));

SDL_COMPILE_సమయం_ASSERT(can_indicate_అధికప్రవాహం, SDL_కొలత_MAX > SDL_MAX_SINT32);

// Magic!
స్థిర అక్షరం SDL_surface_magic;

// Public routines

bool SDL_SurfaceValid(SDL_Surface *surface)
{
    తిరిగి (surface && surface->reserved == &SDL_surface_magic);
}

శూన్య SDL_Update_Surface_తాళం_Flag(SDL_Surface *surface)
{
    // We need to mark the surface as needing unlock while locked
    ఒకవేళ ((surface->flags & SDL_SURFACE_LOCKED) ||
        (surface->అంతర్గత_flags & SDL_అంతర్గత_SURFACE_RLEACCEL)) {
        surface->flags |= SDL_SURFACE_తాళం_NEEDED;
    } లేకపోతే {
        surface->flags &= ~SDL_SURFACE_తాళం_NEEDED;
    }
}

/*
 * Calculate the pad-aligned scanline width of a surface.
 *
 * for FOURCC, use SDL_CalculateYUVSize()
 */
స్థిర bool SDL_CalculateRGBSize(Uint32 format, size_t వెడల్పు, size_t ఎత్తు, size_t *కొలత, size_t *pitch, bool కనీస)
{
    ఒకవేళ (SDL_BITSPERPIXEL(format) >= 8) {
        ఒకవేళ (!SDL_కొలత_mul_check_అధికప్రవాహం(వెడల్పు, SDL_BYTESPERPIXEL(format), pitch)) {
            తిరిగి SDL_సమితి_Error("width * bpp would overflow");
        }
    } లేకపోతే {
        ఒకవేళ (!SDL_కొలత_mul_check_అధికప్రవాహం(వెడల్పు, SDL_BITSPERPIXEL(format), pitch)) {
            తిరిగి SDL_సమితి_Error("width * bpp would overflow");
        }
        ఒకవేళ (!SDL_కొలత_కూడు_check_అధికప్రవాహం(*pitch, 7, pitch)) {
            తిరిగి SDL_సమితి_Error("aligning pitch would overflow");
        }
        *pitch /= 8;
    }
    ఒకవేళ (!కనీస) {
        // 4-byte aligning for speed
        ఒకవేళ (!SDL_కొలత_కూడు_check_అధికప్రవాహం(*pitch, 3, pitch)) {
            తిరిగి SDL_సమితి_Error("aligning pitch would overflow");
        }
        *pitch &= ~3;
    }

    ఒకవేళ (!SDL_కొలత_mul_check_అధికప్రవాహం(ఎత్తు, *pitch, కొలత)) {
        తిరిగి SDL_సమితి_Error("height * pitch would overflow");
    }

    తిరిగి true;
}

bool SDL_Calculate_Surface_కొలత(SDL_PixelFormat format, పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, size_t *కొలత, size_t *pitch, bool కనీస_Pitch)
{
    size_t p = 0, sz = 0;

    ఒకవేళ (కొలత) {
        *కొలత = 0;
    }

    ఒకవేళ (pitch) {
        *pitch = 0;
    }

    ఒకవేళ (SDL_ISPIXELFORMAT_FOURCC(format)) {
        ఒకవేళ (format == SDL_PIXELFORMAT_MJPG) {
            // We don't know in advance what it will be, we'll figure it out later.
            తిరిగి true;
        }

        ఒకవేళ (!SDL_CalculateYUVSize(format, వెడల్పు, ఎత్తు, &sz, &p)) {
            // Overflow...
            తిరిగి false;
        }
    } లేకపోతే {
        ఒకవేళ (!SDL_CalculateRGBSize(format, వెడల్పు, ఎత్తు, &sz, &p, కనీస_Pitch)) {
            // Overflow...
            తిరిగి false;
        }
    }

    ఒకవేళ (కొలత) {
        *కొలత = sz;
    }

    ఒకవేళ (pitch) {
        *pitch = p;
    }

    తిరిగి true;
}

స్థిర bool SDL_InitializeSurface(SDL_Surface *surface, పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, SDL_PixelFormat format, SDL_Colorspace colorspace, SDL_PropertiesID props, శూన్య *pixels, పూర్ణాంకం pitch, bool onstack)
{
    SDL_zerop(surface);

    surface->flags = SDL_SURFACE_PREALLOCATED;
    surface->format = format;
    surface->w = వెడల్పు;
    surface->h = ఎత్తు;
    surface->pixels = pixels;
    surface->pitch = pitch;
    surface->reserved = &SDL_surface_magic;

    ఒకవేళ (onstack) {
        surface->అంతర్గత_flags |= SDL_అంతర్గత_SURFACE_దొంతర;
    }

    surface->fmt = SDL_GetPixelFormatDetails(format);
    ఒకవేళ (!surface->fmt) {
        SDL_DestroySurface(surface);
        తిరిగి false;
    }

    // Initialize the clip rect
    surface->clip_rect.w = వెడల్పు;
    surface->clip_rect.h = ఎత్తు;

    // Allocate an empty mapping
    surface->map.info.r = 0xFF;
    surface->map.info.g = 0xFF;
    surface->map.info.b = 0xFF;
    surface->map.info.a = 0xFF;

    ఒకవేళ (colorspace == SDL_COLORSPACE_UNKNOWN) {
        surface->colorspace = SDL_GetDefaultColorspaceForFormat(format);
    } లేకపోతే {
        surface->colorspace = colorspace;
    }

    ఒకవేళ (props) {
        ఒకవేళ (!SDL_CopyProperties(props, SDL_GetSurfaceProperties(surface))) {
            SDL_DestroySurface(surface);
            తిరిగి false;
        }
    }

    // By default surfaces with an alpha mask are set up for blending
    ఒకవేళ (SDL_ISPIXELFORMAT_ALPHA(surface->format)) {
        SDL_సమితి_Surface_Blend_బహుళకం(surface, SDL_BLENDMODE_BLEND);
    }

    // The surface is ready to go
    surface->refcount = 1;
    తిరిగి true;
}

/*
 * Create an empty surface of the appropriate depth using the given format
 */
స్థిర SDL_Surface *SDL_Create_Surface_అంతర్గత(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, SDL_PixelFormat format, bool clear_surface)
{
    size_t pitch, కొలత;
    SDL_Surface *surface;

    CHECK_PARAM(వెడల్పు < 0) {
        SDL_InvalidParamError("width");
        తిరిగి ఖాళీ;
    }

    CHECK_PARAM(ఎత్తు < 0) {
        SDL_InvalidParamError("height");
        తిరిగి ఖాళీ;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        తిరిగి ఖాళీ;
    }

    ఒకవేళ (!SDL_Calculate_Surface_కొలత(format, వెడల్పు, ఎత్తు, &కొలత, &pitch, false /* not minimal pitch */)) {
        // Overflow...
        తిరిగి ఖాళీ;
    }

    // Allocate and initialize the surface
    surface = (SDL_Surface *)SDL_malloc(పరిమాణం(*surface));
    ఒకవేళ (!surface) {
        తిరిగి ఖాళీ;
    }

    ఒకవేళ (!SDL_InitializeSurface(surface, వెడల్పు, ఎత్తు, format, SDL_COLORSPACE_UNKNOWN, 0, ఖాళీ, (పూర్ణాంకం)pitch, false)) {
        తిరిగి ఖాళీ;
    }

    ఒకవేళ (surface->w && surface->h && format != SDL_PIXELFORMAT_MJPG) {
        surface->flags &= ~SDL_SURFACE_PREALLOCATED;
        ఒకవేళ (SDL_GetHintBoolean("SDL_SURFACE_MALLOC", false)) {
            ఒకవేళ (clear_surface) {
                surface->pixels = SDL_calloc(1, కొలత);
            } లేకపోతే {
                surface->pixels = SDL_malloc(కొలత);
            }
        } లేకపోతే {
            surface->flags |= SDL_SURFACE_SIMD_ALIGNED;
            ఒకవేళ (clear_surface) {
                surface->pixels = SDL_aligned_alloc_zero(SDL_GetSIMDAlignment(), కొలత);
            } లేకపోతే {
                surface->pixels = SDL_aligned_alloc(SDL_GetSIMDAlignment(), కొలత);
            }
        }
        ఒకవేళ (!surface->pixels) {
            SDL_DestroySurface(surface);
            తిరిగి ఖాళీ;
        }
    }
    తిరిగి surface;
}

SDL_Surface *SDL_CreateSurfaceZeroed(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, SDL_PixelFormat format)
{
    తిరిగి SDL_Create_Surface_అంతర్గత(వెడల్పు, ఎత్తు, format, true);
}

SDL_Surface *SDL_CreateSurfaceUninitialized(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, SDL_PixelFormat format)
{
    తిరిగి SDL_Create_Surface_అంతర్గత(వెడల్పు, ఎత్తు, format, false);
}

SDL_Surface *SDL_CreateSurface(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, SDL_PixelFormat format)
{
    తిరిగి SDL_CreateSurfaceZeroed(వెడల్పు, ఎత్తు, format);
}


/*
 * Create an RGB surface from an existing memory buffer using the given
 * enum SDL_PIXELFORMAT_* format
 */
SDL_Surface *SDL_CreateSurfaceFrom(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, SDL_PixelFormat format, శూన్య *pixels, పూర్ణాంకం pitch)
{
    CHECK_PARAM(వెడల్పు < 0) {
        SDL_InvalidParamError("width");
        తిరిగి ఖాళీ;
    }

    CHECK_PARAM(ఎత్తు < 0) {
        SDL_InvalidParamError("height");
        తిరిగి ఖాళీ;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        తిరిగి ఖాళీ;
    }

    ఒకవేళ (pitch == 0 && !pixels) {
        // The application will fill these in later with valid values
    } లేకపోతే {
        size_t కనీస_Pitch;

        ఒకవేళ (!SDL_Calculate_Surface_కొలత(format, వెడల్పు, ఎత్తు, ఖాళీ, &కనీస_Pitch, true /* minimal pitch */)) {
            // Overflow...
            తిరిగి ఖాళీ;
        }

        CHECK_PARAM(pitch < 0 || (size_t)pitch < కనీస_Pitch) {
            SDL_InvalidParamError("pitch");
            తిరిగి ఖాళీ;
        }
    }

    // Allocate and initialize the surface
    SDL_Surface *surface = (SDL_Surface *)SDL_malloc(పరిమాణం(*surface));
    ఒకవేళ (!surface ||
        !SDL_InitializeSurface(surface, వెడల్పు, ఎత్తు, format, SDL_COLORSPACE_UNKNOWN, 0, pixels, pitch, false)) {
        తిరిగి ఖాళీ;
    }
    తిరిగి surface;
}

SDL_PropertiesID SDL_GetSurfaceProperties(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        తిరిగి 0;
    }

    ఒకవేళ (!surface->props) {
        surface->props = SDL_CreateProperties();
    }
    తిరిగి surface->props;
}

bool SDL_సమితి_Surface_Colorspace(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        తిరిగి SDL_InvalidParamError("surface");
    }

    surface->colorspace = colorspace;
    తిరిగి true;
}

SDL_Colorspace SDL_GetSurfaceColorspace(SDL_Surface *surface)
{
    ఒకవేళ (!SDL_SurfaceValid(surface)) {
        తిరిగి SDL_COLORSPACE_UNKNOWN;
    }

    తిరిగి surface->colorspace;
}

దశాంశం SDL_Get_Default_SDRWhite_బిందువు(SDL_Colorspace colorspace)
{
    తిరిగి SDL_Get_Surface_SDRWhite_బిందువు(ఖాళీ, colorspace);
}

దశాంశం SDL_Get_Surface_SDRWhite_బిందువు(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    SDL_TransferCharacteristics transfer = SDL_COLORSPACETRANSFER(colorspace);

    ఒకవేళ (transfer == SDL_TRANSFER_CHARACTERISTICS_రేఖీయ ||
        transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
        SDL_PropertiesID props;
        దశాంశం default_విలువ = 1.0f;

        ఒకవేళ (SDL_SurfaceValid(surface)) {
            props = surface->props;
        } లేకపోతే {
            props = 0;
        }
        ఒకవేళ (transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
            /* The older standards use an SDR white point of 100 nits.
             * ITU-R BT.2408-6 recommends using an SDR white point of 203 nits.
             * This is the default Chrome uses, and what a lot of game content
             * assumes, so we'll go with that.
             */
            స్థిరరాశి దశాంశం DEFAULT_PQ_SDR_WHITE_బిందువు = 203.0f;
            default_విలువ = DEFAULT_PQ_SDR_WHITE_బిందువు;
        }
        తిరిగి SDL_GetFloatProperty(props, SDL_PROP_SURFACE_SDR_WHITE_బిందువు_FLOAT, default_విలువ);
    }
    తిరిగి 1.0f;
}

దశాంశం SDL_GetDefaultHDRHeadroom(SDL_Colorspace colorspace)
{
    తిరిగి SDL_GetSurfaceHDRHeadroom(ఖాళీ, colorspace);
}

దశాంశం SDL_GetSurfaceHDRHeadroom(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    SDL_TransferCharacteristics transfer = SDL_COLORSPACETRANSFER(colorspace);

    ఒకవేళ (transfer == SDL_TRANSFER_CHARACTERISTICS_రేఖీయ ||
        transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
        SDL_PropertiesID props;
        దశాంశం default_విలువ = 0.0f;

        ఒకవేళ (SDL_SurfaceValid(surface)) {
            props = surface->props;
        } లేకపోతే {
            props = 0;
        }
        తిరిగి SDL_GetFloatProperty(props, SDL_PROP_SURFACE_HDR_HEADROOM_FLOAT, default_విలువ);
    }
    తిరిగి 1.0f;
}

SDL_Palette *SDL_CreateSurfacePalette(SDL_Surface *surface)
{
    SDL_Palette *palette;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        తిరిగి ఖాళీ;
    }

    CHECK_PARAM(!SDL_ISPIXELFORMAT_సూచీకృత(surface->format)) {
        SDL_సమితి_Error("The surface is not indexed format");
        తిరిగి ఖాళీ;
    }

    palette = SDL_CreatePalette((1 << SDL_BITSPERPIXEL(surface->format)));
    ఒకవేళ (!palette) {
        తిరిగి ఖాళీ;
    }

    ఒకవేళ (palette->ncolors == 2) {
        // Create a black and white bitmap palette
        palette->colors[0].r = 0xFF;
        palette->colors[0].g = 0xFF;
        palette->colors[0].b = 0xFF;
        palette->colors[1].r = 0x00;
        palette->colors[1].g = 0x00;
        palette->colors[1].b = 0x00;
    }

    ఒకవేళ (!SDL_సమితి_Surface_Palette(surface, palette)) {
        SDL_DestroyPalette(palette);
        తిరిగి ఖాళీ;
    }

    // The surface has retained the palette, we can remove the reference here
    SDL_assert(palette->refcount == 2);
    SDL_DestroyPalette(palette);
    తిరిగి palette;
}

bool SDL_సమితి_Surface_Palette(SDL_Surface *surface, SDL_Palette *palette)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        తిరిగి SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(palette && !SDL_ISPIXELFORMAT_సూచీకృత(surface->format)) {
        తిరిగి SDL_సమితి_Error("Surface doesn't use a palette");
    }

    CHECK_PARAM(palette && palette->ncolors > (1 << SDL_BITSPERPIXEL(surface->format))) {
        తిరిగి SDL_సమితి_Error("Palette doesn't match surface format");
    }

    ఒకవేళ (palette != surface->palette) {
        ఒకవేళ (surface->palette) {
            SDL_DestroyPalette(surface->palette);
        }

        surface->palette = palette;

        ఒకవేళ (surface->palette) {
            ++surface->palette->refcount;
        }
    }

    SDL_InvalidateMap(&surface->map);

    తిరిగి true;
}

SDL_Palette *SDL_GetSurfacePalette(SDL_Surface *surface)
{
    ఒకవేళ (!SDL_SurfaceValid(surface)) {
        తిరిగి ఖాళీ;
    }

    తిరిగి surface->palette;
}

bool SDL_కూడు_Surface_Alternate_Image(SDL_Surface *surface, SDL_Surface *image)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        తిరిగి SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(!SDL_SurfaceValid(image)) {
        తిరిగి SDL_InvalidParamError("image");
    }

    SDL_Surface **images = (SDL_Surface **)SDL_realloc(surface->images, (surface->అంకె_images + 1) * పరిమాణం(*images));
    ఒకవేళ (!images) {
        తిరిగి false;
    }
    images[surface->అంకె_images] = image;
    surface->images = images;
    ++surface->అంకె_images;
    ++image->refcount;
    తిరిగి true;
}

bool SDL_SurfaceHasAlternateImages(SDL_Surface *surface)
{
    ఒకవేళ (!SDL_SurfaceValid(surface)) {
        తిరిగి false;
    }

    తిరిగి (surface->అంకె_images > 0);
}

SDL_Surface **SDL_GetSurfaceImages(SDL_Surface *surface, పూర్ణాంకం *లెక్క)
{
    ఒకవేళ (లెక్క) {
        *లెక్క = 0;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        తిరిగి ఖాళీ;
    }

    పూర్ణాంకం అంకె_images = 1 + surface->అంకె_images;
    SDL_Surface **images = (SDL_Surface **)SDL_malloc((అంకె_images + 1) * పరిమాణం(*images));
    ఒకవేళ (!images) {
        తిరిగి ఖాళీ;
    }
    images[0] = surface;
    ఒకవేళ (surface->అంకె_images > 0) {
        SDL_memcpy(&images[1], surface->images, (surface->అంకె_images * పరిమాణం(images[1])));
    }
    images[అంకె_images] = ఖాళీ;

    ఒకవేళ (లెక్క) {
        *లెక్క = అంకె_images;
    }
    తిరిగి images;
}

SDL_Surface *SDL_GetSurfaceImage(SDL_Surface *surface, దశాంశం display_scale)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        తిరిగి ఖాళీ;
    }

    ఒకవేళ (!SDL_SurfaceHasAlternateImages(surface)) {
        ++surface->refcount;
        తిరిగి surface;
    }

    // This surface has high DPI images, pick the best one available, or scale one to the correct size
    SDL_Surface **images = SDL_GetSurfaceImages(surface, ఖాళీ);
    ఒకవేళ (!images) {
        // Failure, fall back to the existing surface
        ++surface->refcount;
        తిరిగి surface;
    }

    // Find closest image. Images that are larger than the
    // desired size are preferred over images that are smaller.
    SDL_Surface *closest = ఖాళీ;
    పూర్ణాంకం desired_w = (పూర్ణాంకం)SDL_విడత(surface->w * display_scale);
    పూర్ణాంకం desired_h = (పూర్ణాంకం)SDL_విడత(surface->h * display_scale);
    పూర్ణాంకం desired_కొలత = desired_w * desired_h;
    పూర్ణాంకం closest_దూరం = -1;
    పూర్ణాంకం closest_కొలత = -1;
    కొరకు (పూర్ణాంకం i = 0; images[i]; ++i) {
        SDL_Surface *candidate = images[i];
        పూర్ణాంకం కొలత = candidate->w * candidate->h;
        పూర్ణాంకం delta_w = (candidate->w - desired_w);
        పూర్ణాంకం delta_h = (candidate->h - desired_h);
        పూర్ణాంకం దూరం = (delta_w * delta_w) + (delta_h * delta_h);
        ఒకవేళ (closest_దూరం < 0 || దూరం < closest_దూరం ||
            (కొలత > desired_కొలత && closest_కొలత < desired_కొలత)) {
            closest = candidate;
            closest_దూరం = దూరం;
            closest_కొలత = కొలత;
        }
    }
    SDL_free(images);
    SDL_assert(closest != ఖాళీ);    // We should always have at least one surface

    ఒకవేళ (closest->w == desired_w && closest->h == desired_h) {
        ++closest->refcount;
        తిరిగి closest;
    }

    // We need to scale the image to the correct size. To maintain good image quality, downscaling
    // is done in steps, never reducing the width and height by more than half each time.
    SDL_Surface *scaled = closest;
    చేయి {
        పూర్ణాంకం తదుపరి_scaled_w = SDL_max(desired_w, (scaled->w + 1) / 2);
        పూర్ణాంకం తదుపరి_scaled_h = SDL_max(desired_h, (scaled->h + 1) / 2);
        SDL_Surface *తదుపరి_scaled = SDL_ScaleSurface(scaled, తదుపరి_scaled_w, తదుపరి_scaled_h, SDL_SCALEMODE_రేఖీయ);
        ఒకవేళ (scaled != closest) {
            SDL_DestroySurface(scaled);
        }
        scaled = తదుపరి_scaled;
        ఒకవేళ (!scaled) {
            // Failure, fall back to the closest surface
            ++closest->refcount;
            తిరిగి closest;
        }
    } అయితే (scaled->w != desired_w || scaled->h != desired_h);

    తిరిగి scaled;
}

శూన్య SDL_RemoveSurfaceAlternateImages(SDL_Surface *surface)
{
    ఒకవేళ (!SDL_SurfaceValid(surface)) {
        తిరిగి;
    }

    ఒకవేళ (surface->అంకె_images > 0) {
        కొరకు (పూర్ణాంకం i = 0; i < surface->అంకె_images; ++i) {
            SDL_DestroySurface(surface->images[i]);
        }
        SDL_free(surface->images);
        surface->images = ఖాళీ;
        surface->అంకె_images = 0;
    }
}

bool SDL_సమితి_Surface_RLE(SDL_Surface *surface, bool enabled)
{
    పూర్ణాంకం flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        తిరిగి SDL_InvalidParamError("surface");
    }

    flags = surface->map.info.flags;
    ఒకవేళ (enabled) {
        surface->map.info.flags |= SDL_COPY_RLE_DESIRED;
    } లేకపోతే {
        surface->map.info.flags &= ~SDL_COPY_RLE_DESIRED;
    }
    ఒకవేళ (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    తిరిగి true;
}

bool SDL_SurfaceHasRLE(SDL_Surface *surface)
{
    ఒకవేళ (!SDL_SurfaceValid(surface)) {
        తిరిగి false;
    }

    ఒకవేళ (!(surface->map.info.flags & SDL_COPY_RLE_DESIRED)) {
        తిరిగి false;
    }

    తిరిగి true;
}

bool SDL_సమితి_Surface_Color_కీలకం(SDL_Surface *surface, bool enabled, Uint32 కీలకం)
{
    పూర్ణాంకం flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        తిరిగి SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(surface->palette && కీలకం >= ((Uint32)surface->palette->ncolors)) {
        తిరిగి SDL_InvalidParamError("key");
    }

    flags = surface->map.info.flags;
    ఒకవేళ (enabled) {
        surface->map.info.flags |= SDL_COPY_COLORKEY;
        surface->map.info.colorkey = కీలకం;
    } లేకపోతే {
        surface->map.info.flags &= ~SDL_COPY_COLORKEY;
    }
    ఒకవేళ (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }

    తిరిగి true;
}

bool SDL_Surface_Has_Color_కీలకం(SDL_Surface *surface)
{
    ఒకవేళ (!SDL_SurfaceValid(surface)) {
        తిరిగి false;
    }

    ఒకవేళ (!(surface->map.info.flags & SDL_COPY_COLORKEY)) {
        తిరిగి false;
    }

    తిరిగి true;
}

bool SDL_Get_Surface_Color_కీలకం(SDL_Surface *surface, Uint32 *కీలకం)
{
    ఒకవేళ (కీలకం) {
        *కీలకం = 0;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        తిరిగి SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(!(surface->map.info.flags & SDL_COPY_COLORKEY)) {
        తిరిగి SDL_సమితి_Error("Surface doesn't have a colorkey");
    }

    ఒకవేళ (కీలకం) {
        *కీలకం = surface->map.info.colorkey;
    }
    తిరిగి true;
}

/* This is a fairly slow function to switch from colorkey to alpha
   NB: it doesn't handle bpp 1 or 3, because they have no alpha channel */
స్థిర శూన్య SDL_Convert_Colorkey_గమ్యం_Alpha(SDL_Surface *surface, bool ignore_alpha)
{
    పూర్ణాంకం x, y, bpp;

    ఒకవేళ (!SDL_SurfaceValid(surface)) {
        తిరిగి;
    }

    ఒకవేళ (!(surface->map.info.flags & SDL_COPY_COLORKEY) ||
        !SDL_ISPIXELFORMAT_ALPHA(surface->format)) {
        తిరిగి;
    }

    bpp = SDL_BYTESPERPIXEL(surface->format);

    SDL_తాళం_Surface(surface);

    ఒకవేళ (bpp == 2) {
        Uint16 *అడ్డువరుస, *spot;
        Uint16 ckey = (Uint16)surface->map.info.colorkey;
        Uint16 ముసుగు = (Uint16)(~surface->fmt->Amask);

        // Ignore, or not, alpha in colorkey comparison
        ఒకవేళ (ignore_alpha) {
            ckey &= ముసుగు;
            అడ్డువరుస = (Uint16 *)surface->pixels;
            కొరకు (y = surface->h; y--;) {
                spot = అడ్డువరుస;
                కొరకు (x = surface->w; x--;) {
                    ఒకవేళ ((*spot & ముసుగు) == ckey) {
                        *spot &= ముసుగు;
                    }
                    ++spot;
                }
                అడ్డువరుస += surface->pitch / 2;
            }
        } లేకపోతే {
            అడ్డువరుస = (Uint16 *)surface->pixels;
            కొరకు (y = surface->h; y--;) {
                spot = అడ్డువరుస;
                కొరకు (x = surface->w; x--;) {
                    ఒకవేళ (*spot == ckey) {
                        *spot &= ముసుగు;
                    }
                    ++spot;
                }
                అడ్డువరుస += surface->pitch / 2;
            }
        }
    } లేకపోతే ఒకవేళ (bpp == 4) {
        Uint32 *అడ్డువరుస, *spot;
        Uint32 ckey = surface->map.info.colorkey;
        Uint32 ముసుగు = ~surface->fmt->Amask;

        // Ignore, or not, alpha in colorkey comparison
        ఒకవేళ (ignore_alpha) {
            ckey &= ముసుగు;
            అడ్డువరుస = (Uint32 *)surface->pixels;
            కొరకు (y = surface->h; y--;) {
                spot = అడ్డువరుస;
                కొరకు (x = surface->w; x--;) {
                    ఒకవేళ ((*spot & ముసుగు) == ckey) {
                        *spot &= ముసుగు;
                    }
                    ++spot;
                }
                అడ్డువరుస += surface->pitch / 4;
            }
        } లేకపోతే {
            అడ్డువరుస = (Uint32 *)surface->pixels;
            కొరకు (y = surface->h; y--;) {
                spot = అడ్డువరుస;
                కొరకు (x = surface->w; x--;) {
                    ఒకవేళ (*spot == ckey) {
                        *spot &= ముసుగు;
                    }
                    ++spot;
                }
                అడ్డువరుస += surface->pitch / 4;
            }
        }
    }

    SDL_UnlockSurface(surface);

    SDL_సమితి_Surface_Color_కీలకం(surface, false, 0);
    SDL_సమితి_Surface_Blend_బహుళకం(surface, SDL_BLENDMODE_BLEND);
}

bool SDL_సమితి_Surface_Color_Mod(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b)
{
    పూర్ణాంకం flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        తిరిగి SDL_InvalidParamError("surface");
    }

    surface->map.info.r = r;
    surface->map.info.g = g;
    surface->map.info.b = b;

    flags = surface->map.info.flags;
    ఒకవేళ (r != 0xFF || g != 0xFF || b != 0xFF) {
        surface->map.info.flags |= SDL_COPY_MODULATE_COLOR;
    } లేకపోతే {
        surface->map.info.flags &= ~SDL_COPY_MODULATE_COLOR;
    }
    ఒకవేళ (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    తిరిగి true;
}

bool SDL_GetSurfaceColorMod(SDL_Surface *surface, Uint8 *r, Uint8 *g, Uint8 *b)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ఒకవేళ (r) {
            *r = 255;
        }
        ఒకవేళ (g) {
            *g = 255;
        }
        ఒకవేళ (b) {
            *b = 255;
        }
        తిరిగి SDL_InvalidParamError("surface");
    }

    ఒకవేళ (r) {
        *r = surface->map.info.r;
    }
    ఒకవేళ (g) {
        *g = surface->map.info.g;
    }
    ఒకవేళ (b) {
        *b = surface->map.info.b;
    }
    తిరిగి true;
}

bool SDL_సమితి_Surface_Alpha_Mod(SDL_Surface *surface, Uint8 alpha)
{
    పూర్ణాంకం flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        తిరిగి SDL_InvalidParamError("surface");
    }

    surface->map.info.a = alpha;

    flags = surface->map.info.flags;
    ఒకవేళ (alpha != 0xFF) {
        surface->map.info.flags |= SDL_COPY_MODULATE_ALPHA;
    } లేకపోతే {
        surface->map.info.flags &= ~SDL_COPY_MODULATE_ALPHA;
    }
    ఒకవేళ (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    తిరిగి true;
}

bool SDL_GetSurfaceAlphaMod(SDL_Surface *surface, Uint8 *alpha)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ఒకవేళ (alpha) {
            *alpha = 255;
        }
        తిరిగి SDL_InvalidParamError("surface");
    }

    ఒకవేళ (alpha) {
        *alpha = surface->map.info.a;
    }
    తిరిగి true;
}

bool SDL_సమితి_Surface_Blend_బహుళకం(SDL_Surface *surface, SDL_Blend_బహుళకం blend_బహుళకం)
{
    పూర్ణాంకం flags;
    bool ఫలితం = true;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        తిరిగి SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(blend_బహుళకం == SDL_BLENDMODE_INVALID) {
        తిరిగి SDL_InvalidParamError("blendMode");
    }

    flags = surface->map.info.flags;
    surface->map.info.flags &= ~SDL_COPY_BLEND_ముసుగు;
    ఎంపిక (blend_బహుళకం) {
    స్థితి SDL_BLENDMODE_NONE:
        ఆపు;
    స్థితి SDL_BLENDMODE_BLEND:
        surface->map.info.flags |= SDL_COPY_BLEND;
        ఆపు;
    స్థితి SDL_BLENDMODE_BLEND_PREMULTIPLIED:
        surface->map.info.flags |= SDL_COPY_BLEND_PREMULTIPLIED;
        ఆపు;
    స్థితి SDL_BLENDMODE_కూడు:
        surface->map.info.flags |= SDL_COPY_కూడు;
        ఆపు;
    స్థితి SDL_BLENDMODE_కూడు_PREMULTIPLIED:
        surface->map.info.flags |= SDL_COPY_కూడు_PREMULTIPLIED;
        ఆపు;
    స్థితి SDL_BLENDMODE_MOD:
        surface->map.info.flags |= SDL_COPY_MOD;
        ఆపు;
    స్థితి SDL_BLENDMODE_MUL:
        surface->map.info.flags |= SDL_COPY_MUL;
        ఆపు;
    అప్రమేయ:
        ఫలితం = SDL_Unsupported();
        ఆపు;
    }

    ఒకవేళ (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }

    తిరిగి ఫలితం;
}

bool SDL_Get_Surface_Blend_బహుళకం(SDL_Surface *surface, SDL_Blend_బహుళకం *blend_బహుళకం)
{
    ఒకవేళ (blend_బహుళకం) {
        *blend_బహుళకం = SDL_BLENDMODE_INVALID;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        తిరిగి SDL_InvalidParamError("surface");
    }

    ఒకవేళ (!blend_బహుళకం) {
        తిరిగి true;
    }

    ఎంపిక (surface->map.info.flags & SDL_COPY_BLEND_ముసుగు) {
    స్థితి SDL_COPY_BLEND:
        *blend_బహుళకం = SDL_BLENDMODE_BLEND;
        ఆపు;
    స్థితి SDL_COPY_BLEND_PREMULTIPLIED:
        *blend_బహుళకం = SDL_BLENDMODE_BLEND_PREMULTIPLIED;
        ఆపు;
    స్థితి SDL_COPY_కూడు:
        *blend_బహుళకం = SDL_BLENDMODE_కూడు;
        ఆపు;
    స్థితి SDL_COPY_కూడు_PREMULTIPLIED:
        *blend_బహుళకం = SDL_BLENDMODE_కూడు_PREMULTIPLIED;
        ఆపు;
    స్థితి SDL_COPY_MOD:
        *blend_బహుళకం = SDL_BLENDMODE_MOD;
        ఆపు;
    స్థితి SDL_COPY_MUL:
        *blend_బహుళకం = SDL_BLENDMODE_MUL;
        ఆపు;
    అప్రమేయ:
        *blend_బహుళకం = SDL_BLENDMODE_NONE;
        ఆపు;
    }
    తిరిగి true;
}

bool SDL_సమితి_Surface_Clip_Rect(SDL_Surface *surface, స్థిరరాశి SDL_Rect *rect)
{
    SDL_Rect నిండిన_rect;

    // Don't do anything if there's no surface to act on
    ఒకవేళ (!SDL_SurfaceValid(surface)) {
        తిరిగి false;
    }

    // Set up the full surface rectangle
    నిండిన_rect.x = 0;
    నిండిన_rect.y = 0;
    నిండిన_rect.w = surface->w;
    నిండిన_rect.h = surface->h;

    // Set the clipping rectangle
    ఒకవేళ (!rect) {
        surface->clip_rect = నిండిన_rect;
        తిరిగి true;
    }
    తిరిగి SDL_GetRectIntersection(rect, &నిండిన_rect, &surface->clip_rect);
}

bool SDL_GetSurfaceClipRect(SDL_Surface *surface, SDL_Rect *rect)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ఒకవేళ (rect) {
            SDL_zerop(rect);
        }
        తిరిగి SDL_InvalidParamError("surface");
    }
    CHECK_PARAM(!rect) {
        తిరిగి SDL_InvalidParamError("rect");
    }
    *rect = surface->clip_rect;
    తిరిగి true;
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
bool SDL_BlitSurfaceUnchecked(SDL_Surface *src, స్థిరరాశి SDL_Rect *srcrect,
                             SDL_Surface *dst, స్థిరరాశి SDL_Rect *dstrect)
{
    // Check to make sure the blit mapping is valid
    ఒకవేళ (!SDL_ValidateMap(src, dst)) {
        తిరిగి false;
    }
    తిరిగి src->map.blit(src, srcrect, dst, dstrect);
}

bool SDL_BlitSurface(SDL_Surface *src, స్థిరరాశి SDL_Rect *srcrect, SDL_Surface *dst, స్థిరరాశి SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src) || (!src->pixels && !SDL_MUSTLOCK(src))) {
        తిరిగి SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst) || (!dst->pixels && !SDL_MUSTLOCK(dst))) {
        తిరిగి SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        తిరిగి SDL_సమితి_Error("Surfaces must not be locked during blit");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    ఒకవేళ (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
    } లేకపోతే {
        r_dst.x = 0;
        r_dst.y = 0;
    }

    // clip the source rectangle to the source surface
    ఒకవేళ (srcrect) {
        SDL_Rect tmp;
        ఒకవేళ (SDL_GetRectIntersection(srcrect, &r_src, &tmp) == false) {
            తిరిగి true;
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
        ఒకవేళ (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &tmp) == false) {
            తిరిగి true;
        }

        // Shift srcrect, if dstrect has changed
        r_src.x += tmp.x - r_dst.x;
        r_src.y += tmp.y - r_dst.y;
        r_src.w = tmp.w;
        r_src.h = tmp.h;

        // Update dstrect
        r_dst = tmp;
    }

    ఒకవేళ (r_dst.w <= 0 || r_dst.h <= 0) {
        // No-op.
        తిరిగి true;
    }

    // Switch back to a fast blit if we were previously stretching
    ఒకవేళ (src->map.info.flags & SDL_COPY_సమీప) {
        src->map.info.flags &= ~SDL_COPY_సమీప;
        SDL_InvalidateMap(&src->map);
    }

    తిరిగి SDL_BlitSurfaceUnchecked(src, &r_src, dst, &r_dst);
}

స్థిర bool SDL_BlitSurfaceClippedScaled(SDL_Surface *src, స్థిరరాశి SDL_Rect *srcrect, SDL_Surface *dst, స్థిరరాశి SDL_Rect *dstrect, SDL_Scale_బహుళకం scale_బహుళకం)
{
    // We need to scale first, then blit into dst because we're clipping in the destination surface pixel coordinates
    bool ఫలితం;
    పూర్ణాంకం saved_w = src->w;
    పూర్ణాంకం saved_h = src->h;
    శూన్య *saved_pixels = src->pixels;
    src->w = srcrect->w;
    src->h = srcrect->h;
    src->pixels = (Uint8 *)src->pixels + srcrect->y * src->pitch + srcrect->x * SDL_BYTESPERPIXEL(src->format);
    SDL_Surface *scaled = SDL_ScaleSurface(src, dstrect->w, dstrect->h, scale_బహుళకం);
    ఒకవేళ (scaled) {
        ఫలితం = SDL_BlitSurface(scaled, ఖాళీ, dst, dstrect);
        SDL_DestroySurface(scaled);
    } లేకపోతే {
        ఫలితం = false;
    }
    src->w = saved_w;
    src->h = saved_h;
    src->pixels = saved_pixels;
    తిరిగి ఫలితం;
}

bool SDL_BlitSurfaceScaled(SDL_Surface *src, స్థిరరాశి SDL_Rect *srcrect, SDL_Surface *dst, స్థిరరాశి SDL_Rect *dstrect, SDL_Scale_బహుళకం scale_బహుళకం)
{
    SDL_Rect r_src, r_dst;
    bool ఫలితం;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src) || (!src->pixels && !SDL_MUSTLOCK(src))) {
        తిరిగి SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst) || (!dst->pixels && !SDL_MUSTLOCK(dst))) {
        తిరిగి SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        తిరిగి SDL_సమితి_Error("Surfaces must not be locked during blit");
    }

    ఎంపిక (scale_బహుళకం) {
    స్థితి SDL_SCALEMODE_సమీప:
        ఆపు;
    స్థితి SDL_SCALEMODE_రేఖీయ:
        ఆపు;
    స్థితి SDL_SCALEMODE_PIXELART:
        scale_బహుళకం = SDL_SCALEMODE_సమీప;
        ఆపు;
    అప్రమేయ:
        తిరిగి SDL_InvalidParamError("scaleMode");
    }

    పూర్ణాంకం src_w = srcrect ? srcrect->w : src->w;
    పూర్ణాంకం src_h = srcrect ? srcrect->h : src->h;
    పూర్ణాంకం dst_w = dstrect ? dstrect->w : dst->w;
    పూర్ణాంకం dst_h = dstrect ? dstrect->h : dst->h;
    ఒకవేళ (src_w == dst_w && src_h == dst_h) {
        // No scaling, defer to regular blit
        తిరిగి SDL_BlitSurface(src, srcrect, dst, dstrect);
    }

    ఒకవేళ (src->w == 0 || src->h == 0) {
        // Nothing to do
        తిరిగి true;
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    ఒకవేళ (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
        r_dst.w = dstrect->w;
        r_dst.h = dstrect->h;
    } లేకపోతే {
        r_dst.x = 0;
        r_dst.y = 0;
        r_dst.w = dst->w;
        r_dst.h = dst->h;
    }

    // clip the source rectangle to the source surface
    ఒకవేళ (srcrect) {
        SDL_Rect desired, tmp;
        desired.x = srcrect->x;
        desired.y = srcrect->y;
        desired.w = SDL_max(srcrect->w, 1);
        desired.h = SDL_max(srcrect->h, 1);
        ఒకవేళ (SDL_GetRectIntersection(&desired, &r_src, &tmp) == false) {
            తిరిగి true;
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
    ఒకవేళ (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &tmp) == false) {
        తిరిగి true;
    }

    ఒకవేళ (tmp.x != r_dst.x || tmp.y != r_dst.y || tmp.w != r_dst.w || tmp.h != r_dst.h) {
        // Need to do a clipped and scaled blit
        తిరిగి SDL_BlitSurfaceClippedScaled(src, &r_src, dst, &r_dst, scale_బహుళకం);
    }

    ఒకవేళ (SDL_MUSTLOCK(src)) {
        ఒకవేళ (!SDL_తాళం_Surface(src)) {
            తిరిగి false;
        }
    }
    ఒకవేళ (SDL_MUSTLOCK(dst)) {
        ఒకవేళ (!SDL_తాళం_Surface(dst)) {
            ఒకవేళ (SDL_MUSTLOCK(src)) {
                SDL_UnlockSurface(src);
            }
            తిరిగి false;
        }
    }

    ఫలితం = SDL_BlitSurfaceUncheckedScaled(src, &r_src, dst, &r_dst, scale_బహుళకం);

    ఒకవేళ (SDL_MUSTLOCK(src)) {
        SDL_UnlockSurface(src);
    }
    ఒకవేళ (SDL_MUSTLOCK(dst)) {
        SDL_UnlockSurface(dst);
    }
    తిరిగి ఫలితం;
}

/**
 *  This is a semi-private blit function and it performs low-level surface
 *  scaled blitting only.
 */
bool SDL_BlitSurfaceUncheckedScaled(SDL_Surface *src, స్థిరరాశి SDL_Rect *srcrect, SDL_Surface *dst, స్థిరరాశి SDL_Rect *dstrect, SDL_Scale_బహుళకం scale_బహుళకం)
{
    స్థిర స్థిరరాశి Uint32 complex_copy_flags = (SDL_COPY_MODULATE_ముసుగు | SDL_COPY_BLEND_ముసుగు | SDL_COPY_COLORKEY);

    ఒకవేళ (srcrect->w > SDL_MAX_UINT16 || srcrect->h > SDL_MAX_UINT16 ||
        dstrect->w > SDL_MAX_UINT16 || dstrect->h > SDL_MAX_UINT16) {
        తిరిగి SDL_సమితి_Error("Size too large for scaling");
    }

    ఒకవేళ (!(src->map.info.flags & SDL_COPY_సమీప)) {
        src->map.info.flags |= SDL_COPY_సమీప;
        SDL_InvalidateMap(&src->map);
    }

    ఒకవేళ (scale_బహుళకం == SDL_SCALEMODE_సమీప || scale_బహుళకం == SDL_SCALEMODE_PIXELART) {
        ఒకవేళ (!(src->map.info.flags & complex_copy_flags) &&
            src->format == dst->format &&
            (!SDL_ISPIXELFORMAT_సూచీకృత(src->format) ||
             (SDL_BITSPERPIXEL(src->format) == 8 && SDL_IsSamePalette(src->palette, dst->palette))) &&
            SDL_BYTESPERPIXEL(src->format) <= 4) {
            తిరిగి SDL_StretchSurface(src, srcrect, dst, dstrect, SDL_SCALEMODE_సమీప);
        } లేకపోతే ఒకవేళ (SDL_BITSPERPIXEL(src->format) < 8) {
            // Scaling bitmap not yet supported, convert to RGBA for blit
            bool ఫలితం = false;
            SDL_Surface *tmp = SDL_ConvertSurface(src, SDL_PIXELFORMAT_ARGB8888);
            ఒకవేళ (tmp) {
                ఫలితం = SDL_BlitSurfaceUncheckedScaled(tmp, srcrect, dst, dstrect, SDL_SCALEMODE_సమీప);
                SDL_DestroySurface(tmp);
            }
            తిరిగి ఫలితం;
        } లేకపోతే {
            తిరిగి SDL_BlitSurfaceUnchecked(src, srcrect, dst, dstrect);
        }
    } లేకపోతే {
        ఒకవేళ (!(src->map.info.flags & complex_copy_flags) &&
            src->format == dst->format &&
            !SDL_ISPIXELFORMAT_సూచీకృత(src->format) &&
            SDL_BYTESPERPIXEL(src->format) == 4 &&
            src->format != SDL_PIXELFORMAT_ARGB2101010) {
            // fast path
            తిరిగి SDL_StretchSurface(src, srcrect, dst, dstrect, SDL_SCALEMODE_రేఖీయ);
        } లేకపోతే ఒకవేళ (SDL_BITSPERPIXEL(src->format) < 8) {
            // Scaling bitmap not yet supported, convert to RGBA for blit
            bool ఫలితం = false;
            SDL_Surface *tmp = SDL_ConvertSurface(src, SDL_PIXELFORMAT_ARGB8888);
            ఒకవేళ (tmp) {
                ఫలితం = SDL_BlitSurfaceUncheckedScaled(tmp, srcrect, dst, dstrect, scale_బహుళకం);
                SDL_DestroySurface(tmp);
            }
            తిరిగి ఫలితం;
        } లేకపోతే {
            // Use intermediate surface(s)
            SDL_Surface *tmp1 = ఖాళీ;
            bool ఫలితం;
            SDL_Rect srcrect2;
            పూర్ణాంకం is_complex_copy_flags = (src->map.info.flags & complex_copy_flags);

            Uint8 r, g, b;
            Uint8 alpha;
            SDL_Blend_బహుళకం blend_బహుళకం;

            // Save source infos
            SDL_GetSurfaceColorMod(src, &r, &g, &b);
            SDL_GetSurfaceAlphaMod(src, &alpha);
            SDL_Get_Surface_Blend_బహుళకం(src, &blend_బహుళకం);
            srcrect2.x = srcrect->x;
            srcrect2.y = srcrect->y;
            srcrect2.w = srcrect->w;
            srcrect2.h = srcrect->h;

            // Change source format if not appropriate for scaling
            ఒకవేళ (SDL_BYTESPERPIXEL(src->format) != 4 || src->format == SDL_PIXELFORMAT_ARGB2101010) {
                SDL_PixelFormat fmt;
                ఒకవేళ (SDL_BYTESPERPIXEL(dst->format) == 4 && dst->format != SDL_PIXELFORMAT_ARGB2101010 &&
                    (SDL_ISPIXELFORMAT_ALPHA(dst->format) || !is_complex_copy_flags)) {
                    fmt = dst->format;
                } లేకపోతే {
                    fmt = SDL_PIXELFORMAT_ARGB8888;
                }
                tmp1 = SDL_ConvertSurfaceRect(src, srcrect, fmt);
                ఒకవేళ (!tmp1) {
                    తిరిగి false;
                }
                src = tmp1;
                srcrect2.x = 0;
                srcrect2.y = 0;
            }

            // Intermediate scaling
            ఒకవేళ (is_complex_copy_flags || src->format != dst->format) {
                SDL_Rect tmprect;
                SDL_Surface *tmp2 = SDL_CreateSurfaceUninitialized(dstrect->w, dstrect->h, src->format);
                SDL_StretchSurface(src, &srcrect2, tmp2, ఖాళీ, SDL_SCALEMODE_రేఖీయ);

                SDL_సమితి_Surface_Color_Mod(tmp2, r, g, b);
                SDL_సమితి_Surface_Alpha_Mod(tmp2, alpha);
                SDL_సమితి_Surface_Blend_బహుళకం(tmp2, blend_బహుళకం);

                tmprect.x = 0;
                tmprect.y = 0;
                tmprect.w = dstrect->w;
                tmprect.h = dstrect->h;
                ఫలితం = SDL_BlitSurfaceUnchecked(tmp2, &tmprect, dst, dstrect);
                SDL_DestroySurface(tmp2);
            } లేకపోతే {
                ఫలితం = SDL_StretchSurface(src, &srcrect2, dst, dstrect, SDL_SCALEMODE_రేఖీయ);
            }

            SDL_DestroySurface(tmp1);
            తిరిగి ఫలితం;
        }
    }
}

bool SDL_BlitSurfaceTiled(SDL_Surface *src, స్థిరరాశి SDL_Rect *srcrect, SDL_Surface *dst, స్థిరరాశి SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        తిరిగి SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        తిరిగి SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        తిరిగి SDL_సమితి_Error("Surfaces must not be locked during blit");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    ఒకవేళ (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
        r_dst.w = dstrect->w;
        r_dst.h = dstrect->h;
    } లేకపోతే {
        r_dst.x = 0;
        r_dst.y = 0;
        r_dst.w = dst->w;
        r_dst.h = dst->h;
    }

    // clip the source rectangle to the source surface
    ఒకవేళ (srcrect) {
        ఒకవేళ (SDL_GetRectIntersection(srcrect, &r_src, &r_src) == false) {
            తిరిగి true;
        }

        // For tiling we don't adjust the destination rectangle
    }

    // clip the destination rectangle against the clip rectangle
    {
        ఒకవేళ (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &r_dst) == false) {
            తిరిగి true;
        }

        // For tiling we don't adjust the source rectangle
    }

    // Switch back to a fast blit if we were previously stretching
    ఒకవేళ (src->map.info.flags & SDL_COPY_సమీప) {
        src->map.info.flags &= ~SDL_COPY_సమీప;
        SDL_InvalidateMap(&src->map);
    }

    పూర్ణాంకం అడ్డువరుసలు = r_dst.h / r_src.h;
    పూర్ణాంకం నిలువుల_సంఖ్య = r_dst.w / r_src.w;
    పూర్ణాంకం మిగిలిన_w = r_dst.w % r_src.w;
    పూర్ణాంకం మిగిలిన_h = r_dst.h % r_src.h;
    SDL_Rect curr_src, curr_dst;

    SDL_copyp(&curr_src, &r_src);
    curr_dst.y = r_dst.y;
    curr_dst.w = r_src.w;
    curr_dst.h = r_src.h;
    కొరకు (పూర్ణాంకం y = 0; y < అడ్డువరుసలు; ++y) {
        curr_dst.x = r_dst.x;
        కొరకు (పూర్ణాంకం x = 0; x < నిలువుల_సంఖ్య; ++x) {
            ఒకవేళ (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                తిరిగి false;
            }
            curr_dst.x += curr_dst.w;
        }
        ఒకవేళ (మిగిలిన_w) {
            curr_src.w = మిగిలిన_w;
            curr_dst.w = మిగిలిన_w;
            ఒకవేళ (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                తిరిగి false;
            }
            curr_src.w = r_src.w;
            curr_dst.w = r_src.w;
        }
        curr_dst.y += curr_dst.h;
    }
    ఒకవేళ (మిగిలిన_h) {
        curr_src.h = మిగిలిన_h;
        curr_dst.h = మిగిలిన_h;
        curr_dst.x = r_dst.x;
        కొరకు (పూర్ణాంకం x = 0; x < నిలువుల_సంఖ్య; ++x) {
            ఒకవేళ (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                తిరిగి false;
            }
            curr_dst.x += curr_dst.w;
        }
        ఒకవేళ (మిగిలిన_w) {
            curr_src.w = మిగిలిన_w;
            curr_dst.w = మిగిలిన_w;
            ఒకవేళ (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                తిరిగి false;
            }
        }
    }
    తిరిగి true;
}

bool SDL_BlitSurfaceTiledWithScale(SDL_Surface *src, స్థిరరాశి SDL_Rect *srcrect, దశాంశం scale, SDL_Scale_బహుళకం scale_బహుళకం, SDL_Surface *dst, స్థిరరాశి SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        తిరిగి SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        తిరిగి SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        తిరిగి SDL_సమితి_Error("Surfaces must not be locked during blit");
    }
    CHECK_PARAM(scale < 0.0f) {
        తిరిగి SDL_InvalidParamError("scale");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    ఒకవేళ (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
        r_dst.w = dstrect->w;
        r_dst.h = dstrect->h;
    } లేకపోతే {
        r_dst.x = 0;
        r_dst.y = 0;
        r_dst.w = dst->w;
        r_dst.h = dst->h;
    }

    // clip the source rectangle to the source surface
    ఒకవేళ (srcrect) {
        ఒకవేళ (SDL_GetRectIntersection(srcrect, &r_src, &r_src) == false) {
            తిరిగి true;
        }

        // For tiling we don't adjust the destination rectangle
    }

    // clip the destination rectangle against the clip rectangle
    {
        ఒకవేళ (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &r_dst) == false) {
            తిరిగి true;
        }

        // For tiling we don't adjust the source rectangle
    }

    // Switch back to a fast blit if we were previously stretching
    ఒకవేళ (src->map.info.flags & SDL_COPY_సమీప) {
        src->map.info.flags &= ~SDL_COPY_సమీప;
        SDL_InvalidateMap(&src->map);
    }

    పూర్ణాంకం tile_వెడల్పు = (పూర్ణాంకం)SDL_roundf(r_src.w * scale);
    పూర్ణాంకం tile_ఎత్తు = (పూర్ణాంకం)SDL_roundf(r_src.h * scale);
    ఒకవేళ (tile_వెడల్పు <= 0 || tile_ఎత్తు <= 0) {
        // Nothing to do
        తిరిగి true;
    }
    పూర్ణాంకం అడ్డువరుసలు = r_dst.h / tile_ఎత్తు;
    పూర్ణాంకం నిలువుల_సంఖ్య = r_dst.w / tile_వెడల్పు;
    పూర్ణాంకం మిగిలిన_dst_w = (r_dst.w - నిలువుల_సంఖ్య * tile_వెడల్పు);
    పూర్ణాంకం మిగిలిన_dst_h = (r_dst.h - అడ్డువరుసలు * tile_ఎత్తు);
    పూర్ణాంకం మిగిలిన_src_w = (పూర్ణాంకం)(మిగిలిన_dst_w / scale);
    పూర్ణాంకం మిగిలిన_src_h = (పూర్ణాంకం)(మిగిలిన_dst_h / scale);
    SDL_Rect curr_src, curr_dst;

    SDL_copyp(&curr_src, &r_src);
    curr_dst.y = r_dst.y;
    curr_dst.w = tile_వెడల్పు;
    curr_dst.h = tile_ఎత్తు;
    కొరకు (పూర్ణాంకం y = 0; y < అడ్డువరుసలు; ++y) {
        curr_dst.x = r_dst.x;
        కొరకు (పూర్ణాంకం x = 0; x < నిలువుల_సంఖ్య; ++x) {
            ఒకవేళ (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scale_బహుళకం)) {
                తిరిగి false;
            }
            curr_dst.x += curr_dst.w;
        }
        ఒకవేళ (మిగిలిన_dst_w > 0) {
            curr_src.w = మిగిలిన_src_w;
            curr_dst.w = మిగిలిన_dst_w;
            ఒకవేళ (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scale_బహుళకం)) {
                తిరిగి false;
            }
            curr_src.w = r_src.w;
            curr_dst.w = tile_వెడల్పు;
        }
        curr_dst.y += curr_dst.h;
    }
    ఒకవేళ (మిగిలిన_dst_h > 0) {
        curr_src.h = మిగిలిన_src_h;
        curr_dst.h = మిగిలిన_dst_h;
        curr_dst.x = r_dst.x;
        కొరకు (పూర్ణాంకం x = 0; x < నిలువుల_సంఖ్య; ++x) {
            ఒకవేళ (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scale_బహుళకం)) {
                తిరిగి false;
            }
            curr_dst.x += curr_dst.w;
        }
        ఒకవేళ (మిగిలిన_dst_w > 0) {
            curr_src.w = మిగిలిన_src_w;
            curr_dst.w = మిగిలిన_dst_w;
            ఒకవేళ (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scale_బహుళకం)) {
                తిరిగి false;
            }
        }
    }
    తిరిగి true;
}

bool SDL_BlitSurface9Grid(SDL_Surface *src, స్థిరరాశి SDL_Rect *srcrect, పూర్ణాంకం ఎడమ_వెడల్పు, పూర్ణాంకం కుడి_వెడల్పు, పూర్ణాంకం శిఖరం_ఎత్తు, పూర్ణాంకం bottom_ఎత్తు, దశాంశం scale, SDL_Scale_బహుళకం scale_బహుళకం, SDL_Surface *dst, స్థిరరాశి SDL_Rect *dstrect)
{
    SDL_Rect నిండిన_src, నిండిన_dst;
    SDL_Rect curr_src, curr_dst;
    పూర్ణాంకం dst_ఎడమ_వెడల్పు;
    పూర్ణాంకం dst_కుడి_వెడల్పు;
    పూర్ణాంకం dst_శిఖరం_ఎత్తు;
    పూర్ణాంకం dst_bottom_ఎత్తు;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        తిరిగి SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        తిరిగి SDL_InvalidParamError("dst");
    }

    ఒకవేళ (!srcrect) {
        నిండిన_src.x = 0;
        నిండిన_src.y = 0;
        నిండిన_src.w = src->w;
        నిండిన_src.h = src->h;
        srcrect = &నిండిన_src;
    }

    ఒకవేళ (!dstrect) {
        నిండిన_dst.x = 0;
        నిండిన_dst.y = 0;
        నిండిన_dst.w = dst->w;
        నిండిన_dst.h = dst->h;
        dstrect = &నిండిన_dst;
    }

    ఒకవేళ (scale <= 0.0f || scale == 1.0f) {
        dst_ఎడమ_వెడల్పు = ఎడమ_వెడల్పు;
        dst_కుడి_వెడల్పు = కుడి_వెడల్పు;
        dst_శిఖరం_ఎత్తు = శిఖరం_ఎత్తు;
        dst_bottom_ఎత్తు = bottom_ఎత్తు;
    } లేకపోతే {
        dst_ఎడమ_వెడల్పు = (పూర్ణాంకం)SDL_roundf(ఎడమ_వెడల్పు * scale);
        dst_కుడి_వెడల్పు = (పూర్ణాంకం)SDL_roundf(కుడి_వెడల్పు * scale);
        dst_శిఖరం_ఎత్తు = (పూర్ణాంకం)SDL_roundf(శిఖరం_ఎత్తు * scale);
        dst_bottom_ఎత్తు = (పూర్ణాంకం)SDL_roundf(bottom_ఎత్తు * scale);
    }

    // Upper-left corner
    curr_src.x = srcrect->x;
    curr_src.y = srcrect->y;
    curr_src.w = ఎడమ_వెడల్పు;
    curr_src.h = శిఖరం_ఎత్తు;
    curr_dst.x = dstrect->x;
    curr_dst.y = dstrect->y;
    curr_dst.w = dst_ఎడమ_వెడల్పు;
    curr_dst.h = dst_శిఖరం_ఎత్తు;
    ఒకవేళ (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_బహుళకం)) {
        తిరిగి false;
    }

    // Upper-right corner
    curr_src.x = srcrect->x + srcrect->w - కుడి_వెడల్పు;
    curr_src.w = కుడి_వెడల్పు;
    curr_dst.x = dstrect->x + dstrect->w - dst_కుడి_వెడల్పు;
    curr_dst.w = dst_కుడి_వెడల్పు;
    ఒకవేళ (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_బహుళకం)) {
        తిరిగి false;
    }

    // Lower-right corner
    curr_src.y = srcrect->y + srcrect->h - bottom_ఎత్తు;
    curr_dst.y = dstrect->y + dstrect->h - dst_bottom_ఎత్తు;
    curr_dst.h = dst_bottom_ఎత్తు;
    ఒకవేళ (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_బహుళకం)) {
        తిరిగి false;
    }

    // Lower-left corner
    curr_src.x = srcrect->x;
    curr_src.w = ఎడమ_వెడల్పు;
    curr_dst.x = dstrect->x;
    curr_dst.w = dst_ఎడమ_వెడల్పు;
    ఒకవేళ (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_బహుళకం)) {
        తిరిగి false;
    }

    //ఎడమ
    curr_src.y = srcrect->y + శిఖరం_ఎత్తు;
    curr_src.h = srcrect->h - శిఖరం_ఎత్తు - bottom_ఎత్తు;
    curr_dst.y = dstrect->y + dst_శిఖరం_ఎత్తు;
    curr_dst.h = dstrect->h - dst_శిఖరం_ఎత్తు - dst_bottom_ఎత్తు;
    ఒకవేళ (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_బహుళకం)) {
        తిరిగి false;
    }

    //కుడి
    curr_src.x = srcrect->x + srcrect->w - కుడి_వెడల్పు;
    curr_src.w = కుడి_వెడల్పు;
    curr_dst.x = dstrect->x + dstrect->w - dst_కుడి_వెడల్పు;
    curr_dst.w = dst_కుడి_వెడల్పు;
    ఒకవేళ (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_బహుళకం)) {
        తిరిగి false;
    }

    //శిఖరం
    curr_src.x = srcrect->x + ఎడమ_వెడల్పు;
    curr_src.y = srcrect->y;
    curr_src.w = srcrect->w - ఎడమ_వెడల్పు - కుడి_వెడల్పు;
    curr_src.h = శిఖరం_ఎత్తు;
    curr_dst.x = dstrect->x + dst_ఎడమ_వెడల్పు;
    curr_dst.y = dstrect->y;
    curr_dst.w = dstrect->w - dst_ఎడమ_వెడల్పు - dst_కుడి_వెడల్పు;
    curr_dst.h = dst_శిఖరం_ఎత్తు;
    ఒకవేళ (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_బహుళకం)) {
        తిరిగి false;
    }

    // Bottom
    curr_src.y = srcrect->y + srcrect->h - bottom_ఎత్తు;
    curr_dst.y = dstrect->y + dstrect->h - dst_bottom_ఎత్తు;
    curr_dst.h = dst_bottom_ఎత్తు;
    ఒకవేళ (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_బహుళకం)) {
        తిరిగి false;
    }

    // Center
    curr_src.x = srcrect->x + ఎడమ_వెడల్పు;
    curr_src.y = srcrect->y + శిఖరం_ఎత్తు;
    curr_src.w = srcrect->w - ఎడమ_వెడల్పు - కుడి_వెడల్పు;
    curr_src.h = srcrect->h - శిఖరం_ఎత్తు - bottom_ఎత్తు;
    curr_dst.x = dstrect->x + dst_ఎడమ_వెడల్పు;
    curr_dst.y = dstrect->y + dst_శిఖరం_ఎత్తు;
    curr_dst.w = dstrect->w - dst_ఎడమ_వెడల్పు - dst_కుడి_వెడల్పు;
    curr_dst.h = dstrect->h - dst_శిఖరం_ఎత్తు - dst_bottom_ఎత్తు;
    ఒకవేళ (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_బహుళకం)) {
        తిరిగి false;
    }

    తిరిగి true;
}

/*
 * Lock a surface to directly access the pixels
 */
bool SDL_తాళం_Surface(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        తిరిగి SDL_InvalidParamError("surface");
    }

    ఒకవేళ (!surface->locked) {
#నిర్వచితమైతే SDL_HAVE_RLE
        // Perform the lock
        ఒకవేళ (surface->అంతర్గత_flags & SDL_అంతర్గత_SURFACE_RLEACCEL) {
            SDL_UnRLESurface(surface);
        }
#అయితే_ముగింపు
    }

    // Increment the surface lock count, for recursive locks
    ++surface->locked;
    surface->flags |= SDL_SURFACE_LOCKED;
    SDL_Update_Surface_తాళం_Flag(surface);

    // Ready to go..
    తిరిగి true;
}

/*
 * Unlock a previously locked surface
 */
శూన్య SDL_UnlockSurface(SDL_Surface *surface)
{
    ఒకవేళ (!SDL_SurfaceValid(surface)) {
        తిరిగి;
    }

    // Only perform an unlock if we are locked
    ఒకవేళ (!surface->locked || (--surface->locked > 0)) {
        తిరిగి;
    }

    surface->flags &= ~SDL_SURFACE_LOCKED;
    SDL_Update_Surface_తాళం_Flag(surface);
}

స్థిర bool SDL_FlipSurfaceHorizontal(SDL_Surface *surface)
{
    bool isstack;
    Uint8 *అడ్డువరుస, *a, *b, *tmp;
    పూర్ణాంకం i, j, bpp;

    ఒకవేళ (SDL_BITSPERPIXEL(surface->format) < 8) {
        // We could implement this if needed, but we'd have to flip sets of bits within a byte
        తిరిగి SDL_Unsupported();
    }

    ఒకవేళ (surface->h <= 0) {
        తిరిగి true;
    }

    ఒకవేళ (surface->w <= 1) {
        తిరిగి true;
    }

    bpp = SDL_BYTESPERPIXEL(surface->format);
    అడ్డువరుస = (Uint8 *)surface->pixels;
    tmp = SDL_small_alloc(Uint8, surface->pitch, &isstack);
    ఒకవేళ (!tmp) {
        తిరిగి false;
    }
    కొరకు (i = surface->h; i--; ) {
        a = అడ్డువరుస;
        b = a + (surface->w - 1) * bpp;
        కొరకు (j = surface->w / 2; j--; ) {
            SDL_memcpy(tmp, a, bpp);
            SDL_memcpy(a, b, bpp);
            SDL_memcpy(b, tmp, bpp);
            a += bpp;
            b -= bpp;
        }
        అడ్డువరుస += surface->pitch;
    }
    SDL_small_free(tmp, isstack);
    తిరిగి true;
}

స్థిర bool SDL_FlipSurfaceVertical(SDL_Surface *surface)
{
    bool isstack;
    Uint8 *a, *b, *tmp;
    పూర్ణాంకం i;

    ఒకవేళ (surface->h <= 1) {
        తిరిగి true;
    }

    a = (Uint8 *)surface->pixels;
    b = a + (surface->h - 1) * surface->pitch;
    tmp = SDL_small_alloc(Uint8, surface->pitch, &isstack);
    ఒకవేళ (!tmp) {
        తిరిగి false;
    }
    కొరకు (i = surface->h / 2; i--; ) {
        SDL_memcpy(tmp, a, surface->pitch);
        SDL_memcpy(a, b, surface->pitch);
        SDL_memcpy(b, tmp, surface->pitch);
        a += surface->pitch;
        b -= surface->pitch;
    }
    SDL_small_free(tmp, isstack);
    తిరిగి true;
}

bool SDL_FlipSurface(SDL_Surface *surface, SDL_Flip_బహుళకం flip)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        తిరిగి SDL_InvalidParamError("surface");
    }
    ఒకవేళ (!surface->pixels) {
        తిరిగి true;
    }

    bool ఫలితం = true;
    ఎంపిక (flip) {
    స్థితి SDL_FLIP_HORIZONTAL:
        ఫలితం = SDL_FlipSurfaceHorizontal(surface);
        ఆపు;
    స్థితి SDL_FLIP_VERTICAL:
        ఫలితం = SDL_FlipSurfaceVertical(surface);
        ఆపు;
    స్థితి SDL_FLIP_HORIZONTAL_AND_VERTICAL:
        ఫలితం &= SDL_FlipSurfaceHorizontal(surface);
        ఫలితం &= SDL_FlipSurfaceVertical(surface);
        ఆపు;
    అప్రమేయ:
        ఫలితం = SDL_InvalidParamError("flip");
        ఆపు;
    }
    తిరిగి ఫలితం;
}

స్థిర SDL_Surface *SDL_ConvertSurfaceRectAndColorspace(SDL_Surface *surface, స్థిరరాశి SDL_Rect *rect, SDL_PixelFormat format, SDL_Palette *palette, SDL_Colorspace colorspace, SDL_PropertiesID props)
{
    SDL_Palette *తాత్కాలిక_palette = ఖాళీ;
    SDL_Surface *convert = ఖాళీ;
    SDL_Colorspace src_colorspace;
    SDL_PropertiesID src_properties;
    Uint32 copy_flags;
    SDL_Color copy_color;
    SDL_Rect bounds;
    bool ఫలితం;
    bool palette_ck_transform = false;
    Uint8 palette_ck_విలువ = 0;
    Uint8 *palette_saved_alpha = ఖాళీ;
    పూర్ణాంకం palette_saved_alpha_ncolors = 0;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        వెళ్ళు error;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        వెళ్ళు error;
    }

    // Set the bounds of the new surface
    bounds.x = 0;
    bounds.y = 0;
    bounds.w = surface->w;
    bounds.h = surface->h;
    ఒకవేళ (rect) {
        bounds.w = rect->w;
        bounds.h = rect->h;
    } లేకపోతే {
        rect = &bounds;
    }

    // Check for empty destination palette! (results in empty image)
    ఒకవేళ (palette) {
        పూర్ణాంకం i;
        కొరకు (i = 0; i < palette->ncolors; ++i) {
            ఒకవేళ ((palette->colors[i].r != 0xFF) || (palette->colors[i].g != 0xFF) || (palette->colors[i].b != 0xFF)) {
                ఆపు;
            }
        }
        ఒకవేళ (i == palette->ncolors) {
            SDL_సమితి_Error("Empty destination palette");
            వెళ్ళు error;
        }
    } లేకపోతే ఒకవేళ (SDL_ISPIXELFORMAT_సూచీకృత(format)) {
        // Create a dither palette for conversion
        తాత్కాలిక_palette = SDL_CreatePalette(1 << SDL_BITSPERPIXEL(format));
        ఒకవేళ (తాత్కాలిక_palette) {
            SDL_DitherPalette(తాత్కాలిక_palette);
            palette = తాత్కాలిక_palette;
        }
    }

    src_colorspace = surface->colorspace;
    src_properties = surface->props;

    // Create a new surface with the desired format
    ఒకవేళ (surface->pixels || SDL_MUSTLOCK(surface)) {
        convert = SDL_CreateSurfaceUninitialized(rect->w, rect->h, format);
    } లేకపోతే {
        convert = SDL_CreateSurfaceFrom(rect->w, rect->h, format, ఖాళీ, 0);
    }
    ఒకవేళ (!convert) {
        వెళ్ళు error;
    }
    ఒకవేళ (SDL_ISPIXELFORMAT_సూచీకృత(format)) {
        SDL_సమితి_Surface_Palette(convert, palette);
    }

    ఒకవేళ (colorspace == SDL_COLORSPACE_UNKNOWN) {
        colorspace = src_colorspace;
    }
    SDL_సమితి_Surface_Colorspace(convert, colorspace);

    ఒకవేళ (SDL_ISPIXELFORMAT_FOURCC(format) || SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        ఒకవేళ (surface->format == SDL_PIXELFORMAT_MJPG && format == SDL_PIXELFORMAT_MJPG) {
            // Just do a straight pixel copy of the JPEG image
            size_t కొలత = (size_t)surface->pitch;
            convert->pixels = SDL_malloc(కొలత);
            ఒకవేళ (!convert->pixels) {
                వెళ్ళు error;
            }
            convert->flags &= ~SDL_SURFACE_PREALLOCATED;
            convert->pitch = surface->pitch;
            SDL_memcpy(convert->pixels, surface->pixels, కొలత);

        } లేకపోతే ఒకవేళ (!SDL_ConvertPixelsAndColorspace(surface->w, surface->h, surface->format, src_colorspace, src_properties, surface->pixels, surface->pitch, convert->format, colorspace, props, convert->pixels, convert->pitch)) {
            వెళ్ళు error;
        }

        // Save the original copy flags
        copy_flags = surface->map.info.flags;

        వెళ్ళు చివర;
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
    ఒకవేళ (surface->palette && SDL_ISPIXELFORMAT_ALPHA(format)) {
        bool సమితి_opaque = false;

        bool is_opaque, has_alpha_channel;
        SDL_DetectPalette(surface->palette, &is_opaque, &has_alpha_channel);

        ఒకవేళ (is_opaque) {
            ఒకవేళ (!has_alpha_channel) {
                సమితి_opaque = true;
            }
        }

        // Set opaque and backup palette alpha values
        ఒకవేళ (సమితి_opaque) {
            పూర్ణాంకం i;
            palette_saved_alpha_ncolors = surface->palette->ncolors;
            ఒకవేళ (palette_saved_alpha_ncolors > 0) {
                palette_saved_alpha = SDL_దొంతర_alloc(Uint8, palette_saved_alpha_ncolors);
                కొరకు (i = 0; i < palette_saved_alpha_ncolors; i++) {
                    palette_saved_alpha[i] = surface->palette->colors[i].a;
                    surface->palette->colors[i].a = SDL_ALPHA_OPAQUE;
                }
            }
        }
    }

    // Transform colorkey to alpha. for cases where source palette has duplicate values, and colorkey is one of them
    ఒకవేళ (copy_flags & SDL_COPY_COLORKEY) {
        ఒకవేళ (surface->palette && !palette) {
            palette_ck_transform = true;
            palette_ck_విలువ = surface->palette->colors[surface->map.info.colorkey].a;
            surface->palette->colors[surface->map.info.colorkey].a = SDL_ALPHA_TRANSPARENT;
        }
    }

    ఒకవేళ (surface->pixels || SDL_MUSTLOCK(surface)) {
        ఫలితం = SDL_BlitSurfaceUnchecked(surface, rect, convert, &bounds);
    } లేకపోతే {
        ఫలితం = true;
    }

    // Restore colorkey alpha value
    ఒకవేళ (palette_ck_transform) {
        surface->palette->colors[surface->map.info.colorkey].a = palette_ck_విలువ;
    }

    // Restore palette alpha values
    ఒకవేళ (palette_saved_alpha) {
        పూర్ణాంకం i;
        కొరకు (i = 0; i < palette_saved_alpha_ncolors; i++) {
            surface->palette->colors[i].a = palette_saved_alpha[i];
        }
        SDL_దొంతర_free(palette_saved_alpha);
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
    ఒకవేళ (!ఫలితం) {
        వెళ్ళు error;
    }

    ఒకవేళ (copy_flags & SDL_COPY_COLORKEY) {
        bool సమితి_colorkey_by_color = false;
        bool convert_colorkey = true;

        ఒకవేళ (surface->palette) {
            ఒకవేళ (palette &&
                surface->palette->ncolors <= palette->ncolors &&
                (SDL_memcmp(surface->palette->colors, palette->colors,
                            surface->palette->ncolors * పరిమాణం(SDL_Color)) == 0)) {
                // The palette is identical, just set the same colorkey
                SDL_సమితి_Surface_Color_కీలకం(convert, true, surface->map.info.colorkey);
            } లేకపోతే ఒకవేళ (!palette) {
                ఒకవేళ (SDL_ISPIXELFORMAT_ALPHA(format)) {
                    // No need to add the colorkey, transparency is in the alpha channel
                } లేకపోతే {
                    // Only set the colorkey information
                    సమితి_colorkey_by_color = true;
                    convert_colorkey = false;
                }
            } లేకపోతే {
                సమితి_colorkey_by_color = true;
            }
        } లేకపోతే {
            సమితి_colorkey_by_color = true;
        }

        ఒకవేళ (సమితి_colorkey_by_color) {
            SDL_Surface *tmp;
            SDL_Surface *tmp2;
            పూర్ణాంకం converted_colorkey = 0;

            // Create a dummy surface to get the colorkey converted
            tmp = SDL_CreateSurfaceUninitialized(1, 1, surface->format);
            ఒకవేళ (!tmp) {
                వెళ్ళు error;
            }

            // Share the palette, if any
            ఒకవేళ (surface->palette) {
                SDL_సమితి_Surface_Palette(tmp, surface->palette);
            }

            SDL_FillSurfaceRect(tmp, ఖాళీ, surface->map.info.colorkey);

            tmp->map.info.flags &= ~SDL_COPY_COLORKEY;

            // Conversion of the colorkey
            tmp2 = SDL_ConvertSurfaceAndColorspace(tmp, format, palette, colorspace, props);
            ఒకవేళ (!tmp2) {
                SDL_DestroySurface(tmp);
                వెళ్ళు error;
            }

            // Get the converted colorkey
            SDL_memcpy(&converted_colorkey, tmp2->pixels, tmp2->fmt->బైట్లు_చొప్పున_pixel);

            SDL_DestroySurface(tmp);
            SDL_DestroySurface(tmp2);

            // Set the converted colorkey on the new surface
            SDL_సమితి_Surface_Color_కీలకం(convert, true, converted_colorkey);

            // This is needed when converting for 3D texture upload
            ఒకవేళ (convert_colorkey) {
                SDL_Convert_Colorkey_గమ్యం_Alpha(convert, true);
            }
        }
    }

చివర:
    ఒకవేళ (తాత్కాలిక_palette) {
        SDL_DestroyPalette(తాత్కాలిక_palette);
    }

    SDL_సమితి_Surface_Clip_Rect(convert, &surface->clip_rect);

    /* Enable alpha blending by default if the new surface has an
     * alpha channel or alpha modulation */
    ఒకవేళ (SDL_ISPIXELFORMAT_ALPHA(format) ||
        (copy_flags & SDL_COPY_MODULATE_ALPHA)) {
        SDL_సమితి_Surface_Blend_బహుళకం(convert, SDL_BLENDMODE_BLEND);
    }
    ఒకవేళ (copy_flags & SDL_COPY_RLE_DESIRED) {
        SDL_సమితి_Surface_RLE(convert, true);
    }

    // Copy alternate images
    కొరకు (పూర్ణాంకం i = 0; i < surface->అంకె_images; ++i) {
        ఒకవేళ (!SDL_కూడు_Surface_Alternate_Image(convert, surface->images[i])) {
            వెళ్ళు error;
        }
    }

    // Copy properties
    ఒకవేళ (surface->props) {
        ఒకవేళ (!SDL_CopyProperties(surface->props, SDL_GetSurfaceProperties(convert))) {
            వెళ్ళు error;
        }

        // Make sure the new surface doesn't reference an old SDL2 surface.
        SDL_ClearProperty(SDL_GetSurfaceProperties(convert), "sdl2-compat.surface2");
    }

    // We're ready to go!
    తిరిగి convert;

error:
    ఒకవేళ (తాత్కాలిక_palette) {
        SDL_DestroyPalette(తాత్కాలిక_palette);
    }
    ఒకవేళ (convert) {
        SDL_DestroySurface(convert);
    }
    తిరిగి ఖాళీ;
}

SDL_Surface *SDL_ConvertSurfaceAndColorspace(SDL_Surface *surface, SDL_PixelFormat format, SDL_Palette *palette, SDL_Colorspace colorspace, SDL_PropertiesID props)
{
    తిరిగి SDL_ConvertSurfaceRectAndColorspace(surface, ఖాళీ, format, palette, colorspace, props);
}

SDL_Surface *SDL_RotateSurface(SDL_Surface *surface, దశాంశం angle)
{
    SDL_Surface *rotated = ఖాళీ;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        తిరిగి ఖాళీ;
    }

    SDL_Rect rect_dest;
    ద్విగుణ cangle, sangle;
    SDL_FPoint center = { surface->w * 0.5f, surface->h * 0.5f };
    SDLgfx_rotozoom_Surface_కొలత_Trig(surface->w, surface->h, angle, &center, &rect_dest, &cangle, &sangle);

    // This function requires a 32-bit surface or 8-bit surface with a colorkey
    ఒకవేళ ((SDL_BITSPERPIXEL(surface->format) == 32 && SDL_PIXELLAYOUT(surface->format) == SDL_PACKEDLAYOUT_8888) ||
        (surface->format == SDL_PIXELFORMAT_INDEX8 && SDL_Surface_Has_Color_కీలకం(surface))) {
        rotated = SDLgfx_rotateSurface(surface, angle, 1, 0, 0, &rect_dest, cangle, sangle, &center);
    } లేకపోతే {
        SDL_Surface *convert = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);
        ఒకవేళ (convert) {
            SDL_Surface *tmp = SDLgfx_rotateSurface(convert, angle, 1, 0, 0, &rect_dest, cangle, sangle, &center);
            ఒకవేళ (tmp) {
                rotated = SDL_ConvertSurfaceAndColorspace(tmp, surface->format, surface->palette, surface->colorspace, surface->props);
                SDL_DestroySurface(tmp);
            }
            SDL_DestroySurface(convert);
        }
    }

    ఒకవేళ (rotated) {
        ఒకవేళ (SDL_HasProperty(surface->props, SDL_PROP_SURFACE_ROTATION_FLOAT)) {
            స్థిరరాశి దశాంశం rotation = (SDL_Get_సంఖ్య_Property(surface->props, SDL_PROP_SURFACE_ROTATION_FLOAT, 0) - angle);
            SDL_సమితి_Float_Property(SDL_GetSurfaceProperties(rotated), SDL_PROP_SURFACE_ROTATION_FLOAT, rotation);
        }
    }

    తిరిగి rotated;
}

SDL_Surface *SDL_DuplicateSurface(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        తిరిగి ఖాళీ;
    }

    తిరిగి SDL_ConvertSurfaceAndColorspace(surface, surface->format, surface->palette, surface->colorspace, surface->props);
}

SDL_Surface *SDL_ScaleSurface(SDL_Surface *surface, పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, SDL_Scale_బహుళకం scale_బహుళకం)
{
    SDL_Surface *convert = ఖాళీ;
    Uint32 copy_flags;
    SDL_Color copy_color;
    bool rc;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        వెళ్ళు error;
    }

    ఒకవేళ (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // We can't directly scale a YUV surface (yet!)
        SDL_Surface *tmp = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        ఒకవేళ (!tmp) {
            తిరిగి ఖాళీ;
        }

        SDL_Surface *scaled = SDL_ScaleSurface(tmp, వెడల్పు, ఎత్తు, scale_బహుళకం);
        SDL_DestroySurface(tmp);
        ఒకవేళ (!scaled) {
            తిరిగి ఖాళీ;
        }

        SDL_Surface *ఫలితం = SDL_ConvertSurfaceAndColorspace(scaled, surface->format, ఖాళీ, surface->colorspace, surface->props);
        SDL_DestroySurface(scaled);
        తిరిగి ఫలితం;
    }

    ఒకవేళ (SDL_ISPIXELFORMAT_సూచీకృత(surface->format)) {
        // Linear scaling requires conversion to RGBA and then slow pixel color lookup
        scale_బహుళకం = SDL_SCALEMODE_సమీప;
    }

    // Create a new surface with the desired size
    ఒకవేళ (surface->pixels || SDL_MUSTLOCK(surface)) {
        convert = SDL_CreateSurfaceUninitialized(వెడల్పు, ఎత్తు, surface->format);
    } లేకపోతే {
        convert = SDL_CreateSurfaceFrom(వెడల్పు, ఎత్తు, surface->format, ఖాళీ, 0);
    }
    ఒకవేళ (!convert) {
        వెళ్ళు error;
    }
    SDL_సమితి_Surface_Palette(convert, surface->palette);
    SDL_సమితి_Surface_Colorspace(convert, surface->colorspace);
    SDL_సమితి_Surface_RLE(convert, SDL_SurfaceHasRLE(surface));

    ఒకవేళ (surface->pixels || SDL_MUSTLOCK(surface)) {
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

        rc = SDL_BlitSurfaceScaled(surface, ఖాళీ, convert, ఖాళీ, scale_బహుళకం);

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
    } లేకపోతే {
        rc = true;
    }

    // SDL_BlitSurfaceScaled failed, and so the conversion
    ఒకవేళ (!rc) {
        వెళ్ళు error;
    }

    // We're ready to go!
    తిరిగి convert;

error:
    ఒకవేళ (convert) {
        SDL_DestroySurface(convert);
    }
    తిరిగి ఖాళీ;
}

SDL_Surface *SDL_ConvertSurfaceRect(SDL_Surface *surface, స్థిరరాశి SDL_Rect *rect, SDL_PixelFormat format)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        తిరిగి ఖాళీ;
    }

    తిరిగి SDL_ConvertSurfaceRectAndColorspace(surface, rect, format, ఖాళీ, SDL_GetDefaultColorspaceForFormat(format), surface->props);
}

SDL_Surface *SDL_ConvertSurface(SDL_Surface *surface, SDL_PixelFormat format)
{
    తిరిగి SDL_ConvertSurfaceRect(surface, ఖాళీ, format);
}

SDL_Surface *SDL_DuplicatePixels(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, SDL_PixelFormat format, SDL_Colorspace colorspace, శూన్య *pixels, పూర్ణాంకం pitch)
{
    SDL_Surface *surface;
    ఒకవేళ (pixels) {
        surface = SDL_CreateSurfaceUninitialized(వెడల్పు, ఎత్తు, format);
    } లేకపోతే {
        surface = SDL_CreateSurfaceFrom(వెడల్పు, ఎత్తు, format, ఖాళీ, 0);
    }
    ఒకవేళ (!surface) {
        తిరిగి ఖాళీ;
    }
    SDL_సమితి_Surface_Colorspace(surface, colorspace);

    ఒకవేళ (surface->pixels) {
        పూర్ణాంకం నిడివి = వెడల్పు * SDL_BYTESPERPIXEL(format);
        Uint8 *src = (Uint8 *)pixels;
        Uint8 *dst = (Uint8 *)surface->pixels;
        పూర్ణాంకం అడ్డువరుసలు = ఎత్తు;
        అయితే (అడ్డువరుసలు--) {
            SDL_memcpy(dst, src, నిడివి);
            dst += surface->pitch;
            src += pitch;
        }
    }
    తిరిగి surface;
}

bool SDL_ConvertPixelsAndColorspace(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు,
                      SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, స్థిరరాశి శూన్య *src, పూర్ణాంకం src_pitch,
                      SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, శూన్య *dst, పూర్ణాంకం dst_pitch)
{
    SDL_Surface src_surface;
    SDL_Surface dst_surface;
    SDL_Rect rect;
    శూన్య *nonconst_src = (శూన్య *)src;
    bool ఫలితం;

    CHECK_PARAM(!src) {
        తిరిగి SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!src_pitch) {
        తిరిగి SDL_InvalidParamError("src_pitch");
    }
    CHECK_PARAM(!dst) {
        తిరిగి SDL_InvalidParamError("dst");
    }
    CHECK_PARAM(!dst_pitch) {
        తిరిగి SDL_InvalidParamError("dst_pitch");
    }

    ఒకవేళ (src_colorspace == SDL_COLORSPACE_UNKNOWN) {
        src_colorspace = SDL_GetDefaultColorspaceForFormat(src_format);
    }
    ఒకవేళ (dst_colorspace == SDL_COLORSPACE_UNKNOWN) {
        dst_colorspace = SDL_GetDefaultColorspaceForFormat(dst_format);
    }

    ఒకవేళ (src_format == SDL_PIXELFORMAT_MJPG) {
        తిరిగి SDL_ConvertPixels_STB(వెడల్పు, ఎత్తు, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    }

#నిర్వచితమైతే SDL_HAVE_YUV
    ఒకవేళ (SDL_ISPIXELFORMAT_FOURCC(src_format) && SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        తిరిగి SDL_Convert_Pixels_YUV_గమ్యం_YUV(వెడల్పు, ఎత్తు, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } లేకపోతే ఒకవేళ (SDL_ISPIXELFORMAT_FOURCC(src_format)) {
        తిరిగి SDL_Convert_Pixels_YUV_గమ్యం_RGB(వెడల్పు, ఎత్తు, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } లేకపోతే ఒకవేళ (SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        తిరిగి SDL_Convert_Pixels_RGB_గమ్యం_YUV(వెడల్పు, ఎత్తు, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    }
#లేకపోతే
    ఒకవేళ (SDL_ISPIXELFORMAT_FOURCC(src_format) || SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        తిరిగి SDL_సమితి_Error("SDL not built with YUV support");
    }
#అయితే_ముగింపు

    // Fast path for same format copy
    ఒకవేళ (src_format == dst_format && src_colorspace == dst_colorspace) {
        ఒకవేళ (src_pitch == dst_pitch) {
            SDL_memcpy(dst, src, ఎత్తు * src_pitch);
        } లేకపోతే {
            పూర్ణాంకం i;
            స్థిరరాశి పూర్ణాంకం bpp = SDL_BYTESPERPIXEL(src_format);
            వెడల్పు *= bpp;
            కొరకు (i = ఎత్తు; i--;) {
                SDL_memcpy(dst, src, వెడల్పు);
                src = (స్థిరరాశి Uint8 *)src + src_pitch;
                dst = (Uint8 *)dst + dst_pitch;
            }
        }
        తిరిగి true;
    }

    ఒకవేళ (!SDL_InitializeSurface(&src_surface, వెడల్పు, ఎత్తు, src_format, src_colorspace, src_properties, nonconst_src, src_pitch, true)) {
        తిరిగి false;
    }
    SDL_సమితి_Surface_Blend_బహుళకం(&src_surface, SDL_BLENDMODE_NONE);

    ఒకవేళ (!SDL_InitializeSurface(&dst_surface, వెడల్పు, ఎత్తు, dst_format, dst_colorspace, dst_properties, dst, dst_pitch, true)) {
        తిరిగి false;
    }

    // Set up the rect and go!
    rect.x = 0;
    rect.y = 0;
    rect.w = వెడల్పు;
    rect.h = ఎత్తు;
    ఫలితం = SDL_BlitSurfaceUnchecked(&src_surface, &rect, &dst_surface, &rect);

    SDL_DestroySurface(&src_surface);
    SDL_DestroySurface(&dst_surface);

    తిరిగి ఫలితం;
}

bool SDL_ConvertPixels(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, SDL_PixelFormat src_format, స్థిరరాశి శూన్య *src, పూర్ణాంకం src_pitch, SDL_PixelFormat dst_format, శూన్య *dst, పూర్ణాంకం dst_pitch)
{
    తిరిగి SDL_ConvertPixelsAndColorspace(వెడల్పు, ఎత్తు,
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

స్థిర శూన్య SDL_PremultiplyAlpha_AXYZ8888(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, స్థిరరాశి శూన్య *src, పూర్ణాంకం src_pitch, శూన్య *dst, పూర్ణాంకం dst_pitch)
{
    పూర్ణాంకం c;
    Uint32 srcpixel;
    Uint32 srcR, srcG, srcB, srcA;
    Uint32 dstpixel;
    Uint32 dstR, dstG, dstB, dstA;

    అయితే (ఎత్తు--) {
        స్థిరరాశి Uint32 *src_px = (స్థిరరాశి Uint32 *)src;
        Uint32 *dst_px = (Uint32 *)dst;
        కొరకు (c = వెడల్పు; c; --c) {
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
        src = (స్థిరరాశి Uint8 *)src + src_pitch;
        dst = (Uint8 *)dst + dst_pitch;
    }
}

స్థిర శూన్య SDL_PremultiplyAlpha_XYZA8888(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, స్థిరరాశి శూన్య *src, పూర్ణాంకం src_pitch, శూన్య *dst, పూర్ణాంకం dst_pitch)
{
    పూర్ణాంకం c;
    Uint32 srcpixel;
    Uint32 srcR, srcG, srcB, srcA;
    Uint32 dstpixel;
    Uint32 dstR, dstG, dstB, dstA;

    అయితే (ఎత్తు--) {
        స్థిరరాశి Uint32 *src_px = (స్థిరరాశి Uint32 *)src;
        Uint32 *dst_px = (Uint32 *)dst;
        కొరకు (c = వెడల్పు; c; --c) {
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
        src = (స్థిరరాశి Uint8 *)src + src_pitch;
        dst = (Uint8 *)dst + dst_pitch;
    }
}

స్థిర శూన్య SDL_PremultiplyAlpha_AXYZ128(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, స్థిరరాశి శూన్య *src, పూర్ణాంకం src_pitch, శూన్య *dst, పూర్ణాంకం dst_pitch)
{
    పూర్ణాంకం c;
    దశాంశం flR, flG, flB, flA;

    అయితే (ఎత్తు--) {
        స్థిరరాశి దశాంశం *src_px = (స్థిరరాశి దశాంశం *)src;
        దశాంశం *dst_px = (దశాంశం *)dst;
        కొరకు (c = వెడల్పు; c; --c) {
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
        src = (స్థిరరాశి Uint8 *)src + src_pitch;
        dst = (Uint8 *)dst + dst_pitch;
    }
}

స్థిర bool SDL_PremultiplyAlphaPixelsAndColorspace(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, స్థిరరాశి శూన్య *src, పూర్ణాంకం src_pitch, SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, శూన్య *dst, పూర్ణాంకం dst_pitch, bool రేఖీయ)
{
    SDL_Surface *convert = ఖాళీ;
    శూన్య *final_dst = dst;
    పూర్ణాంకం final_dst_pitch = dst_pitch;
    SDL_PixelFormat format;
    SDL_Colorspace colorspace;
    bool ఫలితం = false;

    CHECK_PARAM(!src) {
        తిరిగి SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!src_pitch) {
        తిరిగి SDL_InvalidParamError("src_pitch");
    }
    CHECK_PARAM(!dst) {
        తిరిగి SDL_InvalidParamError("dst");
    }
    CHECK_PARAM(!dst_pitch) {
        తిరిగి SDL_InvalidParamError("dst_pitch");
    }

    // Use a high precision format if we're converting to linear colorspace or using high precision pixel formats
    ఒకవేళ (రేఖీయ ||
        SDL_ISPIXELFORMAT_10_బిట్టు(src_format) || SDL_BITSPERPIXEL(src_format) > 32 ||
        SDL_ISPIXELFORMAT_10_బిట్టు(dst_format) || SDL_BITSPERPIXEL(dst_format) > 32) {
        ఒకవేళ (src_format == SDL_PIXELFORMAT_ARGB128_FLOAT ||
            src_format == SDL_PIXELFORMAT_ABGR128_FLOAT) {
            format = src_format;
        } లేకపోతే {
            format = SDL_PIXELFORMAT_ARGB128_FLOAT;
        }
    } లేకపోతే {
        ఒకవేళ (src_format == SDL_PIXELFORMAT_ARGB8888 ||
            src_format == SDL_PIXELFORMAT_ABGR8888 ||
            src_format == SDL_PIXELFORMAT_RGBA8888 ||
            src_format == SDL_PIXELFORMAT_BGRA8888) {
            format = src_format;
        } లేకపోతే {
            format = SDL_PIXELFORMAT_ARGB8888;
        }
    }
    ఒకవేళ (రేఖీయ) {
        colorspace = SDL_COLORSPACE_SRGB_రేఖీయ;
    } లేకపోతే {
        colorspace = SDL_COLORSPACE_SRGB;
    }

    ఒకవేళ (src_format != format || src_colorspace != colorspace) {
        convert = SDL_CreateSurfaceUninitialized(వెడల్పు, ఎత్తు, format);
        ఒకవేళ (!convert) {
            వెళ్ళు పూర్తి;
        }
        ఒకవేళ (!SDL_ConvertPixelsAndColorspace(వెడల్పు, ఎత్తు, src_format, src_colorspace, src_properties, src, src_pitch, format, colorspace, 0, convert->pixels, convert->pitch)) {
            వెళ్ళు పూర్తి;
        }

        src = convert->pixels;
        src_pitch = convert->pitch;
        dst = convert->pixels;
        dst_pitch = convert->pitch;

    } లేకపోతే ఒకవేళ (dst_format != format || dst_colorspace != colorspace) {
        convert = SDL_CreateSurfaceUninitialized(వెడల్పు, ఎత్తు, format);
        ఒకవేళ (!convert) {
            వెళ్ళు పూర్తి;
        }
        dst = convert->pixels;
        dst_pitch = convert->pitch;
    }

    ఎంపిక (format) {
    స్థితి SDL_PIXELFORMAT_ARGB8888:
    స్థితి SDL_PIXELFORMAT_ABGR8888:
        SDL_PremultiplyAlpha_AXYZ8888(వెడల్పు, ఎత్తు, src, src_pitch, dst, dst_pitch);
        ఆపు;
    స్థితి SDL_PIXELFORMAT_RGBA8888:
    స్థితి SDL_PIXELFORMAT_BGRA8888:
        SDL_PremultiplyAlpha_XYZA8888(వెడల్పు, ఎత్తు, src, src_pitch, dst, dst_pitch);
        ఆపు;
    స్థితి SDL_PIXELFORMAT_ARGB128_FLOAT:
    స్థితి SDL_PIXELFORMAT_ABGR128_FLOAT:
        SDL_PremultiplyAlpha_AXYZ128(వెడల్పు, ఎత్తు, src, src_pitch, dst, dst_pitch);
        ఆపు;
    అప్రమేయ:
        SDL_సమితి_Error("Unexpected internal pixel format");
        వెళ్ళు పూర్తి;
    }

    ఒకవేళ (dst != final_dst) {
        ఒకవేళ (!SDL_ConvertPixelsAndColorspace(వెడల్పు, ఎత్తు, format, colorspace, 0, convert->pixels, convert->pitch, dst_format, dst_colorspace, dst_properties, final_dst, final_dst_pitch)) {
            వెళ్ళు పూర్తి;
        }
    }
    ఫలితం = true;

పూర్తి:
    ఒకవేళ (convert) {
        SDL_DestroySurface(convert);
    }
    తిరిగి ఫలితం;
}

bool SDL_PremultiplyAlpha(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు,
                         SDL_PixelFormat src_format, స్థిరరాశి శూన్య *src, పూర్ణాంకం src_pitch,
                         SDL_PixelFormat dst_format, శూన్య *dst, పూర్ణాంకం dst_pitch, bool రేఖీయ)
{
    SDL_Colorspace src_colorspace = SDL_GetDefaultColorspaceForFormat(src_format);
    SDL_Colorspace dst_colorspace = SDL_GetDefaultColorspaceForFormat(dst_format);

    తిరిగి SDL_PremultiplyAlphaPixelsAndColorspace(వెడల్పు, ఎత్తు, src_format, src_colorspace, 0, src, src_pitch, dst_format, dst_colorspace, 0, dst, dst_pitch, రేఖీయ);
}

bool SDL_PremultiplySurfaceAlpha(SDL_Surface *surface, bool రేఖీయ)
{
    SDL_Colorspace colorspace;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        తిరిగి SDL_InvalidParamError("surface");
    }

    colorspace = surface->colorspace;

    తిరిగి SDL_PremultiplyAlphaPixelsAndColorspace(surface->w, surface->h, surface->format, colorspace, surface->props, surface->pixels, surface->pitch, surface->format, colorspace, surface->props, surface->pixels, surface->pitch, రేఖీయ);
}

bool SDL_ClearSurface(SDL_Surface *surface, దశాంశం r, దశాంశం g, దశాంశం b, దశాంశం a)
{
    SDL_Rect clip_rect;
    bool ఫలితం = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        తిరిగి SDL_InvalidParamError("surface");
    }

    SDL_GetSurfaceClipRect(surface, &clip_rect);
    SDL_సమితి_Surface_Clip_Rect(surface, ఖాళీ);

    ఒకవేళ (!SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_BYTESPERPIXEL(surface->format) <= పరిమాణం(Uint32)) {
        Uint32 color;

        color = SDL_MapSurfaceRGBA(surface,
                    (Uint8)SDL_roundf(SDL_clamp(r, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(g, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(b, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(a, 0.0f, 1.0f) * 255.0f));
        ఫలితం = SDL_FillSurfaceRect(surface, ఖాళీ, color);
    } లేకపోతే ఒకవేళ (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // We can't directly set an RGB value on a YUV surface
        SDL_Surface *tmp = SDL_CreateSurfaceUninitialized(surface->w, surface->h, SDL_PIXELFORMAT_ARGB8888);
        ఒకవేళ (!tmp) {
            వెళ్ళు పూర్తి;
        }

        ఒకవేళ (SDL_ClearSurface(tmp, r, g, b, a)) {
            ఫలితం = SDL_ConvertPixelsAndColorspace(surface->w, surface->h, tmp->format, tmp->colorspace, tmp->props, tmp->pixels, tmp->pitch, surface->format, surface->colorspace, surface->props, surface->pixels, surface->pitch);
        }
        SDL_DestroySurface(tmp);
    } లేకపోతే {
        // Take advantage of blit color conversion
        SDL_Surface *tmp = SDL_CreateSurfaceUninitialized(1, 1, SDL_PIXELFORMAT_RGBA128_FLOAT);
        ఒకవేళ (!tmp) {
            వెళ్ళు పూర్తి;
        }
        SDL_సమితి_Surface_Colorspace(tmp, surface->colorspace);
        SDL_సమితి_Surface_Blend_బహుళకం(tmp, SDL_BLENDMODE_NONE);

        దశాంశం *pixels = (దశాంశం *)tmp->pixels;
        pixels[0] = r;
        pixels[1] = g;
        pixels[2] = b;
        pixels[3] = a;

        ఫలితం = SDL_BlitSurfaceScaled(tmp, ఖాళీ, surface, ఖాళీ, SDL_SCALEMODE_సమీప);
        SDL_DestroySurface(tmp);
    }

పూర్తి:
    SDL_సమితి_Surface_Clip_Rect(surface, &clip_rect);

    తిరిగి ఫలితం;
}

Uint32 SDL_MapSurfaceRGB(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b)
{
    తిరిగి SDL_MapSurfaceRGBA(surface, r, g, b, SDL_ALPHA_OPAQUE);
}

Uint32 SDL_MapSurfaceRGBA(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        తిరిగి true;
    }
    తిరిగి SDL_MapRGBA(surface->fmt, surface->palette, r, g, b, a);
}

// This function Copyright 2023 Collabora Ltd., contributed to SDL under the ZLib license
bool SDL_ReadSurfacePixel(SDL_Surface *surface, పూర్ణాంకం x, పూర్ణాంకం y, Uint8 *r, Uint8 *g, Uint8 *b, Uint8 *a)
{
    Uint32 pixel = 0;
    size_t బైట్లు_చొప్పున_pixel;
    Uint8 వాడని;
    Uint8 *p;
    bool ఫలితం = false;

    ఒకవేళ (r) {
        *r = 0;
    } లేకపోతే {
        r = &వాడని;
    }

    ఒకవేళ (g) {
        *g = 0;
    } లేకపోతే {
        g = &వాడని;
    }

    ఒకవేళ (b) {
        *b = 0;
    } లేకపోతే {
        b = &వాడని;
    }

    ఒకవేళ (a) {
        *a = 0;
    } లేకపోతే {
        a = &వాడని;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        తిరిగి SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        తిరిగి SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        తిరిగి SDL_InvalidParamError("y");
    }

    బైట్లు_చొప్పున_pixel = SDL_BYTESPERPIXEL(surface->format);

    ఒకవేళ (SDL_MUSTLOCK(surface)) {
        ఒకవేళ (!SDL_తాళం_Surface(surface)) {
            తిరిగి false;
        }
    }

    p = (Uint8 *)surface->pixels + y * surface->pitch + x * బైట్లు_చొప్పున_pixel;

    ఒకవేళ (బైట్లు_చొప్పున_pixel <= పరిమాణం(pixel) &&
        !SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_COLORSPACEPRIMARIES(surface->colorspace) == SDL_COLOR_PRIMARIES_BT709) {
        /* Fill the appropriate number of least-significant bytes of pixel,
         * leaving the most-significant bytes set to zero */
#ఒకవేళ SDL_BYTEORDER == SDL_BIG_ENDIAN
        SDL_memcpy(((Uint8 *)&pixel) + (పరిమాణం(pixel) - బైట్లు_చొప్పున_pixel), p, బైట్లు_చొప్పున_pixel);
#లేకపోతే
        SDL_memcpy(&pixel, p, బైట్లు_చొప్పున_pixel);
#అయితే_ముగింపు
        SDL_GetRGBA(pixel, surface->fmt, surface->palette, r, g, b, a);
        ఫలితం = true;
    } లేకపోతే ఒకవేళ (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // FIXME: We need code to extract a single macroblock from a YUV surface
        SDL_Surface *converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        ఒకవేళ (converted) {
            ఫలితం = SDL_ReadSurfacePixel(converted, x, y, r, g, b, a);
            SDL_DestroySurface(converted);
        }
    } లేకపోతే {
        // This is really slow, but it gets the job done
        Uint8 rgba[4];

        ఒకవేళ (SDL_ConvertPixelsAndColorspace(1, 1, surface->format, surface->colorspace, surface->props, p, surface->pitch, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, rgba, పరిమాణం(rgba))) {
            *r = rgba[0];
            *g = rgba[1];
            *b = rgba[2];
            *a = rgba[3];
            ఫలితం = true;
        }
    }

    ఒకవేళ (SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }
    తిరిగి ఫలితం;
}

bool SDL_ReadSurfacePixelFloat(SDL_Surface *surface, పూర్ణాంకం x, పూర్ణాంకం y, దశాంశం *r, దశాంశం *g, దశాంశం *b, దశాంశం *a)
{
    దశాంశం వాడని;
    bool ఫలితం = false;

    ఒకవేళ (r) {
        *r = 0.0f;
    } లేకపోతే {
        r = &వాడని;
    }

    ఒకవేళ (g) {
        *g = 0.0f;
    } లేకపోతే {
        g = &వాడని;
    }

    ఒకవేళ (b) {
        *b = 0.0f;
    } లేకపోతే {
        b = &వాడని;
    }

    ఒకవేళ (a) {
        *a = 0.0f;
    } లేకపోతే {
        a = &వాడని;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        తిరిగి SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        తిరిగి SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        తిరిగి SDL_InvalidParamError("y");
    }

    ఒకవేళ (SDL_BYTESPERPIXEL(surface->format) <= పరిమాణం(Uint32) &&
        !SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_COLORSPACEPRIMARIES(surface->colorspace) == SDL_COLOR_PRIMARIES_BT709) {
        Uint8 r8, g8, b8, a8;

        ఒకవేళ (SDL_ReadSurfacePixel(surface, x, y, &r8, &g8, &b8, &a8)) {
            *r = (దశాంశం)r8 / 255.0f;
            *g = (దశాంశం)g8 / 255.0f;
            *b = (దశాంశం)b8 / 255.0f;
            *a = (దశాంశం)a8 / 255.0f;
            ఫలితం = true;
        }
    } లేకపోతే ఒకవేళ (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // FIXME: We need code to extract a single macroblock from a YUV surface
        SDL_Surface *converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        ఒకవేళ (converted) {
            ఫలితం = SDL_ReadSurfacePixelFloat(converted, x, y, r, g, b, a);
            SDL_DestroySurface(converted);
        }
    } లేకపోతే {
        // This is really slow, but it gets the job done
        దశాంశం rgba[4];
        Uint8 *p;

        ఒకవేళ (SDL_MUSTLOCK(surface)) {
            ఒకవేళ (!SDL_తాళం_Surface(surface)) {
                తిరిగి false;
            }
        }

        p = (Uint8 *)surface->pixels + y * surface->pitch + x * SDL_BYTESPERPIXEL(surface->format);

        ఒకవేళ (surface->format == SDL_PIXELFORMAT_RGBA128_FLOAT) {
            SDL_memcpy(rgba, p, పరిమాణం(rgba));
            ఫలితం = true;
        } లేకపోతే {
            SDL_Colorspace src_colorspace = surface->colorspace;
            SDL_Colorspace dst_colorspace = (src_colorspace == SDL_COLORSPACE_SRGB_రేఖీయ ? SDL_COLORSPACE_SRGB_రేఖీయ : SDL_COLORSPACE_SRGB);

            ఒకవేళ (SDL_ConvertPixelsAndColorspace(1, 1, surface->format, src_colorspace, surface->props, p, surface->pitch, SDL_PIXELFORMAT_RGBA128_FLOAT, dst_colorspace, 0, rgba, పరిమాణం(rgba))) {
                ఫలితం = true;
            }
        }

        ఒకవేళ (ఫలితం) {
            *r = rgba[0];
            *g = rgba[1];
            *b = rgba[2];
            *a = rgba[3];
        }

        ఒకవేళ (SDL_MUSTLOCK(surface)) {
            SDL_UnlockSurface(surface);
        }
    }
    తిరిగి ఫలితం;
}

bool SDL_WriteSurfacePixel(SDL_Surface *surface, పూర్ణాంకం x, పూర్ణాంకం y, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    Uint32 pixel = 0;
    size_t బైట్లు_చొప్పున_pixel;
    Uint8 *p;
    bool ఫలితం = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        తిరిగి SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        తిరిగి SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        తిరిగి SDL_InvalidParamError("y");
    }

    బైట్లు_చొప్పున_pixel = SDL_BYTESPERPIXEL(surface->format);

    ఒకవేళ (SDL_MUSTLOCK(surface)) {
        ఒకవేళ (!SDL_తాళం_Surface(surface)) {
            తిరిగి false;
        }
    }

    p = (Uint8 *)surface->pixels + y * surface->pitch + x * బైట్లు_చొప్పున_pixel;

    ఒకవేళ (బైట్లు_చొప్పున_pixel <= పరిమాణం(pixel) && !SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        pixel = SDL_MapRGBA(surface->fmt, surface->palette, r, g, b, a);
#ఒకవేళ SDL_BYTEORDER == SDL_BIG_ENDIAN
        SDL_memcpy(p, ((Uint8 *)&pixel) + (పరిమాణం(pixel) - బైట్లు_చొప్పున_pixel), బైట్లు_చొప్పున_pixel);
#లేకపోతే
        SDL_memcpy(p, &pixel, బైట్లు_చొప్పున_pixel);
#అయితే_ముగింపు
        ఫలితం = true;
    } లేకపోతే ఒకవేళ (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        ఫలితం = SDL_Unsupported();
    } లేకపోతే {
        // This is really slow, but it gets the job done
        Uint8 rgba[4];

        rgba[0] = r;
        rgba[1] = g;
        rgba[2] = b;
        rgba[3] = a;
        ఫలితం = SDL_ConvertPixelsAndColorspace(1, 1, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, rgba, పరిమాణం(rgba), surface->format, surface->colorspace, surface->props, p, surface->pitch);
    }

    ఒకవేళ (SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }
    తిరిగి ఫలితం;
}

bool SDL_WriteSurfacePixelFloat(SDL_Surface *surface, పూర్ణాంకం x, పూర్ణాంకం y, దశాంశం r, దశాంశం g, దశాంశం b, దశాంశం a)
{
    bool ఫలితం = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        తిరిగి SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        తిరిగి SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        తిరిగి SDL_InvalidParamError("y");
    }

    ఒకవేళ (SDL_BYTESPERPIXEL(surface->format) <= పరిమాణం(Uint32) && !SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        Uint8 r8, g8, b8, a8;

        r8 = (Uint8)SDL_విడత(SDL_clamp(r, 0.0f, 1.0f) * 255.0f);
        g8 = (Uint8)SDL_విడత(SDL_clamp(g, 0.0f, 1.0f) * 255.0f);
        b8 = (Uint8)SDL_విడత(SDL_clamp(b, 0.0f, 1.0f) * 255.0f);
        a8 = (Uint8)SDL_విడత(SDL_clamp(a, 0.0f, 1.0f) * 255.0f);
        ఒకవేళ (SDL_WriteSurfacePixel(surface, x, y, r8, g8, b8, a8)) {
            ఫలితం = true;
        }
    } లేకపోతే ఒకవేళ (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        ఫలితం = SDL_Unsupported();
    } లేకపోతే {
        // This is really slow, but it gets the job done
        దశాంశం rgba[4];
        Uint8 *p;

        ఒకవేళ (SDL_MUSTLOCK(surface)) {
            ఒకవేళ (!SDL_తాళం_Surface(surface)) {
                తిరిగి false;
            }
        }

        p = (Uint8 *)surface->pixels + y * surface->pitch + x * SDL_BYTESPERPIXEL(surface->format);

        rgba[0] = r;
        rgba[1] = g;
        rgba[2] = b;
        rgba[3] = a;

        ఒకవేళ (surface->format == SDL_PIXELFORMAT_RGBA128_FLOAT) {
            SDL_memcpy(p, rgba, పరిమాణం(rgba));
            ఫలితం = true;
        } లేకపోతే {
            SDL_Colorspace dst_colorspace = surface->colorspace;
            SDL_Colorspace src_colorspace = (dst_colorspace == SDL_COLORSPACE_SRGB_రేఖీయ ? SDL_COLORSPACE_SRGB_రేఖీయ : SDL_COLORSPACE_SRGB);

            ఫలితం = SDL_ConvertPixelsAndColorspace(1, 1, SDL_PIXELFORMAT_RGBA128_FLOAT, src_colorspace, 0, rgba, పరిమాణం(rgba), surface->format, dst_colorspace, surface->props, p, surface->pitch);
        }

        ఒకవేళ (SDL_MUSTLOCK(surface)) {
            SDL_UnlockSurface(surface);
        }
    }
    తిరిగి ఫలితం;
}

/*
 * Free a surface created by the above function.
 */
శూన్య SDL_DestroySurface(SDL_Surface *surface)
{
    ఒకవేళ (!SDL_SurfaceValid(surface)) {
        తిరిగి;
    }
    ఒకవేళ (surface->అంతర్గత_flags & SDL_అంతర్గత_SURFACE_DONTFREE) {
        తిరిగి;
    }
    ఒకవేళ (--surface->refcount > 0) {
        తిరిగి;
    }

    SDL_RemoveSurfaceAlternateImages(surface);

    SDL_DestroyProperties(surface->props);

    SDL_InvalidateMap(&surface->map);

    అయితే (surface->locked > 0) {
        SDL_UnlockSurface(surface);
    }
#నిర్వచితమైతే SDL_HAVE_RLE
    ఒకవేళ (surface->అంతర్గత_flags & SDL_అంతర్గత_SURFACE_RLEACCEL) {
        SDL_UnRLESurface(surface);
    }
#అయితే_ముగింపు
    SDL_సమితి_Surface_Palette(surface, ఖాళీ);

    ఒకవేళ (surface->flags & SDL_SURFACE_PREALLOCATED) {
        // Don't free
    } లేకపోతే ఒకవేళ (surface->flags & SDL_SURFACE_SIMD_ALIGNED) {
        // Free aligned
        SDL_aligned_free(surface->pixels);
    } లేకపోతే {
        // Normal
        SDL_free(surface->pixels);
    }

    surface->reserved = ఖాళీ;

    ఒకవేళ (!(surface->అంతర్గత_flags & SDL_అంతర్గత_SURFACE_దొంతర)) {
        SDL_free(surface);
    }
}

SDL_Surface *SDL_ఎక్కించు_Surface_IO(SDL_IOStream *src, bool closeio)
{
    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        తిరిగి ఖాళీ;
    }

    ఒకవేళ (SDL_IsBMP(src)) {
        తిరిగి SDL_ఎక్కించు_BMP_IO(src, closeio);
    } లేకపోతే ఒకవేళ (SDL_IsPNG(src)) {
        తిరిగి SDL_ఎక్కించు_PNG_IO(src, closeio);
    } లేకపోతే ఒకవేళ (SDL_IsJPG(src)) {
        తిరిగి SDL_ఎక్కించు_JPG_IO(src, closeio);
    } లేకపోతే {
        ఒకవేళ (closeio) {
            SDL_CloseIO(src);
        }
        SDL_సమితి_Error("Unsupported image format");
        తిరిగి ఖాళీ;
    }
}

SDL_Surface *SDL_ఎక్కించు_Surface(స్థిరరాశి అక్షరం *file)
{
    SDL_IOStream *ప్రవాహం = SDL_IOFromFile(file, "rb");
    ఒకవేళ (!ప్రవాహం) {
        తిరిగి ఖాళీ;
    }

    తిరిగి SDL_ఎక్కించు_Surface_IO(ప్రవాహం, true);
}
