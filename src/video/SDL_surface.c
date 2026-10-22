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
#अन्तर्भाव "SDL_internal.h"

#अन्तर्भाव "SDL_sysvideo.h"
#अन्तर्भाव "SDL_video_c.h"
#अन्तर्भाव "SDL_RLEaccel_c.h"
#अन्तर्भाव "SDL_pixels_c.h"
#अन्तर्भाव "SDL_rotate.h"
#अन्तर्भाव "SDL_stb_c.h"
#अन्तर्भाव "SDL_yuv_c.h"
#अन्तर्भाव "../render/SDL_sysrender.h"

#अन्तर्भाव "SDL_surface_c.h"


// Check to make sure we can safely check multiplication of surface w and pitch and it won't overflow size_t
SDL_COMPILE_TIME_ASSERT(surface_size_assumptions,
                        आकार(पूर्णांक) == आकार(Sint32) && आकार(माप_प्रकार) >= आकार(Sint32));

SDL_COMPILE_TIME_ASSERT(can_indicate_overflow, SDL_SIZE_MAX > SDL_MAX_SINT32);

// Magic!
स्थिर अक्षर SDL_surface_magic;

// Public routines

bool SDL_SurfaceValid(SDL_Surface *surface)
{
    परत (surface && surface->reserved == &SDL_surface_magic);
}

शून्य SDL_UpdateSurfaceLockFlag(SDL_Surface *surface)
{
    // We need to mark the surface as needing unlock while locked
    जर ((surface->flags & SDL_SURFACE_LOCKED) ||
        (surface->internal_flags & SDL_INTERNAL_SURFACE_RLEACCEL)) {
        surface->flags |= SDL_SURFACE_LOCK_NEEDED;
    } अन्यथा {
        surface->flags &= ~SDL_SURFACE_LOCK_NEEDED;
    }
}

/*
 * Calculate the pad-aligned scanline width of a surface.
 *
 * for FOURCC, use SDL_CalculateYUVSize()
 */
स्थिर bool SDL_CalculateRGBSize(Uint32 format, माप_प्रकार width, माप_प्रकार height, माप_प्रकार *size, माप_प्रकार *pitch, bool minimal)
{
    जर (SDL_BITSPERPIXEL(format) >= 8) {
        जर (!SDL_size_mul_check_overflow(width, SDL_BYTESPERPIXEL(format), pitch)) {
            परत SDL_SetError("width * bpp would overflow");
        }
    } अन्यथा {
        जर (!SDL_size_mul_check_overflow(width, SDL_BITSPERPIXEL(format), pitch)) {
            परत SDL_SetError("width * bpp would overflow");
        }
        जर (!SDL_size_add_check_overflow(*pitch, 7, pitch)) {
            परत SDL_SetError("aligning pitch would overflow");
        }
        *pitch /= 8;
    }
    जर (!minimal) {
        // 4-byte aligning for speed
        जर (!SDL_size_add_check_overflow(*pitch, 3, pitch)) {
            परत SDL_SetError("aligning pitch would overflow");
        }
        *pitch &= ~3;
    }

    जर (!SDL_size_mul_check_overflow(height, *pitch, size)) {
        परत SDL_SetError("height * pitch would overflow");
    }

    परत true;
}

bool SDL_CalculateSurfaceSize(SDL_PixelFormat format, पूर्णांक width, पूर्णांक height, माप_प्रकार *size, माप_प्रकार *pitch, bool minimalPitch)
{
    माप_प्रकार p = 0, sz = 0;

    जर (size) {
        *size = 0;
    }

    जर (pitch) {
        *pitch = 0;
    }

    जर (SDL_ISPIXELFORMAT_FOURCC(format)) {
        जर (format == SDL_PIXELFORMAT_MJPG) {
            // We don't know in advance what it will be, we'll figure it out later.
            परत true;
        }

        जर (!SDL_CalculateYUVSize(format, width, height, &sz, &p)) {
            // Overflow...
            परत false;
        }
    } अन्यथा {
        जर (!SDL_CalculateRGBSize(format, width, height, &sz, &p, minimalPitch)) {
            // Overflow...
            परत false;
        }
    }

    जर (size) {
        *size = sz;
    }

    जर (pitch) {
        *pitch = p;
    }

    परत true;
}

स्थिर bool SDL_InitializeSurface(SDL_Surface *surface, पूर्णांक width, पूर्णांक height, SDL_PixelFormat format, SDL_Colorspace colorspace, SDL_PropertiesID props, शून्य *pixels, पूर्णांक pitch, bool onstack)
{
    SDL_zerop(surface);

    surface->flags = SDL_SURFACE_PREALLOCATED;
    surface->format = format;
    surface->w = width;
    surface->h = height;
    surface->pixels = pixels;
    surface->pitch = pitch;
    surface->reserved = &SDL_surface_magic;

    जर (onstack) {
        surface->internal_flags |= SDL_INTERNAL_SURFACE_चळत;
    }

    surface->fmt = SDL_GetPixelFormatDetails(format);
    जर (!surface->fmt) {
        SDL_DestroySurface(surface);
        परत false;
    }

    // Initialize the clip rect
    surface->clip_rect.w = width;
    surface->clip_rect.h = height;

    // Allocate an empty mapping
    surface->map.info.r = 0xFF;
    surface->map.info.g = 0xFF;
    surface->map.info.b = 0xFF;
    surface->map.info.a = 0xFF;

    जर (colorspace == SDL_COLORSPACE_UNKNOWN) {
        surface->colorspace = SDL_GetDefaultColorspaceForFormat(format);
    } अन्यथा {
        surface->colorspace = colorspace;
    }

    जर (props) {
        जर (!SDL_CopyProperties(props, SDL_GetSurfaceProperties(surface))) {
            SDL_DestroySurface(surface);
            परत false;
        }
    }

    // By default surfaces with an alpha mask are set up for blending
    जर (SDL_ISPIXELFORMAT_ALPHA(surface->format)) {
        SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
    }

    // The surface is ready to go
    surface->refcount = 1;
    परत true;
}

/*
 * Create an empty surface of the appropriate depth using the given format
 */
स्थिर SDL_Surface *SDL_CreateSurfaceInternal(पूर्णांक width, पूर्णांक height, SDL_PixelFormat format, bool clear_surface)
{
    माप_प्रकार pitch, size;
    SDL_Surface *surface;

    CHECK_PARAM(width < 0) {
        SDL_InvalidParamError("width");
        परत रिक्त;
    }

    CHECK_PARAM(height < 0) {
        SDL_InvalidParamError("height");
        परत रिक्त;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        परत रिक्त;
    }

    जर (!SDL_CalculateSurfaceSize(format, width, height, &size, &pitch, false /* not minimal pitch */)) {
        // Overflow...
        परत रिक्त;
    }

    // Allocate and initialize the surface
    surface = (SDL_Surface *)SDL_malloc(आकार(*surface));
    जर (!surface) {
        परत रिक्त;
    }

    जर (!SDL_InitializeSurface(surface, width, height, format, SDL_COLORSPACE_UNKNOWN, 0, रिक्त, (पूर्णांक)pitch, false)) {
        परत रिक्त;
    }

    जर (surface->w && surface->h && format != SDL_PIXELFORMAT_MJPG) {
        surface->flags &= ~SDL_SURFACE_PREALLOCATED;
        जर (SDL_GetHintBoolean("SDL_SURFACE_MALLOC", false)) {
            जर (clear_surface) {
                surface->pixels = SDL_calloc(1, size);
            } अन्यथा {
                surface->pixels = SDL_malloc(size);
            }
        } अन्यथा {
            surface->flags |= SDL_SURFACE_SIMD_ALIGNED;
            जर (clear_surface) {
                surface->pixels = SDL_aligned_alloc_zero(SDL_GetSIMDAlignment(), size);
            } अन्यथा {
                surface->pixels = SDL_aligned_alloc(SDL_GetSIMDAlignment(), size);
            }
        }
        जर (!surface->pixels) {
            SDL_DestroySurface(surface);
            परत रिक्त;
        }
    }
    परत surface;
}

SDL_Surface *SDL_CreateSurfaceZeroed(पूर्णांक width, पूर्णांक height, SDL_PixelFormat format)
{
    परत SDL_CreateSurfaceInternal(width, height, format, true);
}

SDL_Surface *SDL_CreateSurfaceUninitialized(पूर्णांक width, पूर्णांक height, SDL_PixelFormat format)
{
    परत SDL_CreateSurfaceInternal(width, height, format, false);
}

SDL_Surface *SDL_CreateSurface(पूर्णांक width, पूर्णांक height, SDL_PixelFormat format)
{
    परत SDL_CreateSurfaceZeroed(width, height, format);
}


/*
 * Create an RGB surface from an existing memory buffer using the given
 * enum SDL_PIXELFORMAT_* format
 */
SDL_Surface *SDL_CreateSurfaceFrom(पूर्णांक width, पूर्णांक height, SDL_PixelFormat format, शून्य *pixels, पूर्णांक pitch)
{
    CHECK_PARAM(width < 0) {
        SDL_InvalidParamError("width");
        परत रिक्त;
    }

    CHECK_PARAM(height < 0) {
        SDL_InvalidParamError("height");
        परत रिक्त;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        परत रिक्त;
    }

    जर (pitch == 0 && !pixels) {
        // The application will fill these in later with valid values
    } अन्यथा {
        माप_प्रकार minimalPitch;

        जर (!SDL_CalculateSurfaceSize(format, width, height, रिक्त, &minimalPitch, true /* minimal pitch */)) {
            // Overflow...
            परत रिक्त;
        }

        CHECK_PARAM(pitch < 0 || (माप_प्रकार)pitch < minimalPitch) {
            SDL_InvalidParamError("pitch");
            परत रिक्त;
        }
    }

    // Allocate and initialize the surface
    SDL_Surface *surface = (SDL_Surface *)SDL_malloc(आकार(*surface));
    जर (!surface ||
        !SDL_InitializeSurface(surface, width, height, format, SDL_COLORSPACE_UNKNOWN, 0, pixels, pitch, false)) {
        परत रिक्त;
    }
    परत surface;
}

SDL_PropertiesID SDL_GetSurfaceProperties(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        परत 0;
    }

    जर (!surface->props) {
        surface->props = SDL_CreateProperties();
    }
    परत surface->props;
}

bool SDL_SetSurfaceColorspace(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        परत SDL_InvalidParamError("surface");
    }

    surface->colorspace = colorspace;
    परत true;
}

SDL_Colorspace SDL_GetSurfaceColorspace(SDL_Surface *surface)
{
    जर (!SDL_SurfaceValid(surface)) {
        परत SDL_COLORSPACE_UNKNOWN;
    }

    परत surface->colorspace;
}

दशांश SDL_GetDefaultSDRWhitePoint(SDL_Colorspace colorspace)
{
    परत SDL_GetSurfaceSDRWhitePoint(रिक्त, colorspace);
}

दशांश SDL_GetSurfaceSDRWhitePoint(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    SDL_TransferCharacteristics transfer = SDL_COLORSPACETRANSFER(colorspace);

    जर (transfer == SDL_TRANSFER_CHARACTERISTICS_LINEAR ||
        transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
        SDL_PropertiesID props;
        दशांश default_मूल्य = 1.0f;

        जर (SDL_SurfaceValid(surface)) {
            props = surface->props;
        } अन्यथा {
            props = 0;
        }
        जर (transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
            /* The older standards use an SDR white point of 100 nits.
             * ITU-R BT.2408-6 recommends using an SDR white point of 203 nits.
             * This is the default Chrome uses, and what a lot of game content
             * assumes, so we'll go with that.
             */
            स्थिरांक दशांश DEFAULT_PQ_SDR_WHITE_POINT = 203.0f;
            default_मूल्य = DEFAULT_PQ_SDR_WHITE_POINT;
        }
        परत SDL_GetFloatProperty(props, SDL_PROP_SURFACE_SDR_WHITE_POINT_FLOAT, default_मूल्य);
    }
    परत 1.0f;
}

दशांश SDL_GetDefaultHDRHeadroom(SDL_Colorspace colorspace)
{
    परत SDL_GetSurfaceHDRHeadroom(रिक्त, colorspace);
}

दशांश SDL_GetSurfaceHDRHeadroom(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    SDL_TransferCharacteristics transfer = SDL_COLORSPACETRANSFER(colorspace);

    जर (transfer == SDL_TRANSFER_CHARACTERISTICS_LINEAR ||
        transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
        SDL_PropertiesID props;
        दशांश default_मूल्य = 0.0f;

        जर (SDL_SurfaceValid(surface)) {
            props = surface->props;
        } अन्यथा {
            props = 0;
        }
        परत SDL_GetFloatProperty(props, SDL_PROP_SURFACE_HDR_HEADROOM_FLOAT, default_मूल्य);
    }
    परत 1.0f;
}

SDL_Palette *SDL_CreateSurfacePalette(SDL_Surface *surface)
{
    SDL_Palette *palette;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        परत रिक्त;
    }

    CHECK_PARAM(!SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        SDL_SetError("The surface is not indexed format");
        परत रिक्त;
    }

    palette = SDL_CreatePalette((1 << SDL_BITSPERPIXEL(surface->format)));
    जर (!palette) {
        परत रिक्त;
    }

    जर (palette->ncolors == 2) {
        // Create a black and white bitmap palette
        palette->colors[0].r = 0xFF;
        palette->colors[0].g = 0xFF;
        palette->colors[0].b = 0xFF;
        palette->colors[1].r = 0x00;
        palette->colors[1].g = 0x00;
        palette->colors[1].b = 0x00;
    }

    जर (!SDL_SetSurfacePalette(surface, palette)) {
        SDL_DestroyPalette(palette);
        परत रिक्त;
    }

    // The surface has retained the palette, we can remove the reference here
    SDL_assert(palette->refcount == 2);
    SDL_DestroyPalette(palette);
    परत palette;
}

bool SDL_SetSurfacePalette(SDL_Surface *surface, SDL_Palette *palette)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        परत SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(palette && !SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        परत SDL_SetError("Surface doesn't use a palette");
    }

    CHECK_PARAM(palette && palette->ncolors > (1 << SDL_BITSPERPIXEL(surface->format))) {
        परत SDL_SetError("Palette doesn't match surface format");
    }

    जर (palette != surface->palette) {
        जर (surface->palette) {
            SDL_DestroyPalette(surface->palette);
        }

        surface->palette = palette;

        जर (surface->palette) {
            ++surface->palette->refcount;
        }
    }

    SDL_InvalidateMap(&surface->map);

    परत true;
}

SDL_Palette *SDL_GetSurfacePalette(SDL_Surface *surface)
{
    जर (!SDL_SurfaceValid(surface)) {
        परत रिक्त;
    }

    परत surface->palette;
}

bool SDL_AddSurfaceAlternateImage(SDL_Surface *surface, SDL_Surface *image)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        परत SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(!SDL_SurfaceValid(image)) {
        परत SDL_InvalidParamError("image");
    }

    SDL_Surface **images = (SDL_Surface **)SDL_realloc(surface->images, (surface->अंक_images + 1) * आकार(*images));
    जर (!images) {
        परत false;
    }
    images[surface->अंक_images] = image;
    surface->images = images;
    ++surface->अंक_images;
    ++image->refcount;
    परत true;
}

bool SDL_SurfaceHasAlternateImages(SDL_Surface *surface)
{
    जर (!SDL_SurfaceValid(surface)) {
        परत false;
    }

    परत (surface->अंक_images > 0);
}

SDL_Surface **SDL_GetSurfaceImages(SDL_Surface *surface, पूर्णांक *मोजणी)
{
    जर (मोजणी) {
        *मोजणी = 0;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        परत रिक्त;
    }

    पूर्णांक अंक_images = 1 + surface->अंक_images;
    SDL_Surface **images = (SDL_Surface **)SDL_malloc((अंक_images + 1) * आकार(*images));
    जर (!images) {
        परत रिक्त;
    }
    images[0] = surface;
    जर (surface->अंक_images > 0) {
        SDL_memcpy(&images[1], surface->images, (surface->अंक_images * आकार(images[1])));
    }
    images[अंक_images] = रिक्त;

    जर (मोजणी) {
        *मोजणी = अंक_images;
    }
    परत images;
}

SDL_Surface *SDL_GetSurfaceImage(SDL_Surface *surface, दशांश display_scale)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        परत रिक्त;
    }

    जर (!SDL_SurfaceHasAlternateImages(surface)) {
        ++surface->refcount;
        परत surface;
    }

    // This surface has high DPI images, pick the best one available, or scale one to the correct size
    SDL_Surface **images = SDL_GetSurfaceImages(surface, रिक्त);
    जर (!images) {
        // Failure, fall back to the existing surface
        ++surface->refcount;
        परत surface;
    }

    // Find closest image. Images that are larger than the
    // desired size are preferred over images that are smaller.
    SDL_Surface *closest = रिक्त;
    पूर्णांक desired_w = (पूर्णांक)SDL_round(surface->w * display_scale);
    पूर्णांक desired_h = (पूर्णांक)SDL_round(surface->h * display_scale);
    पूर्णांक desired_size = desired_w * desired_h;
    पूर्णांक closest_distance = -1;
    पूर्णांक closest_size = -1;
    साठी (पूर्णांक i = 0; images[i]; ++i) {
        SDL_Surface *candidate = images[i];
        पूर्णांक size = candidate->w * candidate->h;
        पूर्णांक delta_w = (candidate->w - desired_w);
        पूर्णांक delta_h = (candidate->h - desired_h);
        पूर्णांक distance = (delta_w * delta_w) + (delta_h * delta_h);
        जर (closest_distance < 0 || distance < closest_distance ||
            (size > desired_size && closest_size < desired_size)) {
            closest = candidate;
            closest_distance = distance;
            closest_size = size;
        }
    }
    SDL_free(images);
    SDL_assert(closest != रिक्त);    // We should always have at least one surface

    जर (closest->w == desired_w && closest->h == desired_h) {
        ++closest->refcount;
        परत closest;
    }

    // We need to scale the image to the correct size. To maintain good image quality, downscaling
    // is done in steps, never reducing the width and height by more than half each time.
    SDL_Surface *scaled = closest;
    करा {
        पूर्णांक next_scaled_w = SDL_max(desired_w, (scaled->w + 1) / 2);
        पूर्णांक next_scaled_h = SDL_max(desired_h, (scaled->h + 1) / 2);
        SDL_Surface *next_scaled = SDL_ScaleSurface(scaled, next_scaled_w, next_scaled_h, SDL_SCALEMODE_LINEAR);
        जर (scaled != closest) {
            SDL_DestroySurface(scaled);
        }
        scaled = next_scaled;
        जर (!scaled) {
            // Failure, fall back to the closest surface
            ++closest->refcount;
            परत closest;
        }
    } पर्यंत (scaled->w != desired_w || scaled->h != desired_h);

    परत scaled;
}

शून्य SDL_RemoveSurfaceAlternateImages(SDL_Surface *surface)
{
    जर (!SDL_SurfaceValid(surface)) {
        परत;
    }

    जर (surface->अंक_images > 0) {
        साठी (पूर्णांक i = 0; i < surface->अंक_images; ++i) {
            SDL_DestroySurface(surface->images[i]);
        }
        SDL_free(surface->images);
        surface->images = रिक्त;
        surface->अंक_images = 0;
    }
}

bool SDL_SetSurfaceRLE(SDL_Surface *surface, bool enabled)
{
    पूर्णांक flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        परत SDL_InvalidParamError("surface");
    }

    flags = surface->map.info.flags;
    जर (enabled) {
        surface->map.info.flags |= SDL_COPY_RLE_DESIRED;
    } अन्यथा {
        surface->map.info.flags &= ~SDL_COPY_RLE_DESIRED;
    }
    जर (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    परत true;
}

bool SDL_SurfaceHasRLE(SDL_Surface *surface)
{
    जर (!SDL_SurfaceValid(surface)) {
        परत false;
    }

    जर (!(surface->map.info.flags & SDL_COPY_RLE_DESIRED)) {
        परत false;
    }

    परत true;
}

bool SDL_Set_Surface_Color_किल्ली(SDL_Surface *surface, bool enabled, Uint32 किल्ली)
{
    पूर्णांक flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        परत SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(surface->palette && किल्ली >= ((Uint32)surface->palette->ncolors)) {
        परत SDL_InvalidParamError("key");
    }

    flags = surface->map.info.flags;
    जर (enabled) {
        surface->map.info.flags |= SDL_COPY_COLORKEY;
        surface->map.info.colorkey = किल्ली;
    } अन्यथा {
        surface->map.info.flags &= ~SDL_COPY_COLORKEY;
    }
    जर (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }

    परत true;
}

bool SDL_Surface_Has_Color_किल्ली(SDL_Surface *surface)
{
    जर (!SDL_SurfaceValid(surface)) {
        परत false;
    }

    जर (!(surface->map.info.flags & SDL_COPY_COLORKEY)) {
        परत false;
    }

    परत true;
}

bool SDL_Get_Surface_Color_किल्ली(SDL_Surface *surface, Uint32 *किल्ली)
{
    जर (किल्ली) {
        *किल्ली = 0;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        परत SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(!(surface->map.info.flags & SDL_COPY_COLORKEY)) {
        परत SDL_SetError("Surface doesn't have a colorkey");
    }

    जर (किल्ली) {
        *किल्ली = surface->map.info.colorkey;
    }
    परत true;
}

/* This is a fairly slow function to switch from colorkey to alpha
   NB: it doesn't handle bpp 1 or 3, because they have no alpha channel */
स्थिर शून्य SDL_ConvertColorkeyToAlpha(SDL_Surface *surface, bool ignore_alpha)
{
    पूर्णांक x, y, bpp;

    जर (!SDL_SurfaceValid(surface)) {
        परत;
    }

    जर (!(surface->map.info.flags & SDL_COPY_COLORKEY) ||
        !SDL_ISPIXELFORMAT_ALPHA(surface->format)) {
        परत;
    }

    bpp = SDL_BYTESPERPIXEL(surface->format);

    SDL_LockSurface(surface);

    जर (bpp == 2) {
        Uint16 *row, *spot;
        Uint16 ckey = (Uint16)surface->map.info.colorkey;
        Uint16 mask = (Uint16)(~surface->fmt->Amask);

        // Ignore, or not, alpha in colorkey comparison
        जर (ignore_alpha) {
            ckey &= mask;
            row = (Uint16 *)surface->pixels;
            साठी (y = surface->h; y--;) {
                spot = row;
                साठी (x = surface->w; x--;) {
                    जर ((*spot & mask) == ckey) {
                        *spot &= mask;
                    }
                    ++spot;
                }
                row += surface->pitch / 2;
            }
        } अन्यथा {
            row = (Uint16 *)surface->pixels;
            साठी (y = surface->h; y--;) {
                spot = row;
                साठी (x = surface->w; x--;) {
                    जर (*spot == ckey) {
                        *spot &= mask;
                    }
                    ++spot;
                }
                row += surface->pitch / 2;
            }
        }
    } अन्यथा जर (bpp == 4) {
        Uint32 *row, *spot;
        Uint32 ckey = surface->map.info.colorkey;
        Uint32 mask = ~surface->fmt->Amask;

        // Ignore, or not, alpha in colorkey comparison
        जर (ignore_alpha) {
            ckey &= mask;
            row = (Uint32 *)surface->pixels;
            साठी (y = surface->h; y--;) {
                spot = row;
                साठी (x = surface->w; x--;) {
                    जर ((*spot & mask) == ckey) {
                        *spot &= mask;
                    }
                    ++spot;
                }
                row += surface->pitch / 4;
            }
        } अन्यथा {
            row = (Uint32 *)surface->pixels;
            साठी (y = surface->h; y--;) {
                spot = row;
                साठी (x = surface->w; x--;) {
                    जर (*spot == ckey) {
                        *spot &= mask;
                    }
                    ++spot;
                }
                row += surface->pitch / 4;
            }
        }
    }

    SDL_UnlockSurface(surface);

    SDL_Set_Surface_Color_किल्ली(surface, false, 0);
    SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
}

bool SDL_SetSurfaceColorMod(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b)
{
    पूर्णांक flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        परत SDL_InvalidParamError("surface");
    }

    surface->map.info.r = r;
    surface->map.info.g = g;
    surface->map.info.b = b;

    flags = surface->map.info.flags;
    जर (r != 0xFF || g != 0xFF || b != 0xFF) {
        surface->map.info.flags |= SDL_COPY_MODULATE_COLOR;
    } अन्यथा {
        surface->map.info.flags &= ~SDL_COPY_MODULATE_COLOR;
    }
    जर (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    परत true;
}

bool SDL_GetSurfaceColorMod(SDL_Surface *surface, Uint8 *r, Uint8 *g, Uint8 *b)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        जर (r) {
            *r = 255;
        }
        जर (g) {
            *g = 255;
        }
        जर (b) {
            *b = 255;
        }
        परत SDL_InvalidParamError("surface");
    }

    जर (r) {
        *r = surface->map.info.r;
    }
    जर (g) {
        *g = surface->map.info.g;
    }
    जर (b) {
        *b = surface->map.info.b;
    }
    परत true;
}

bool SDL_SetSurfaceAlphaMod(SDL_Surface *surface, Uint8 alpha)
{
    पूर्णांक flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        परत SDL_InvalidParamError("surface");
    }

    surface->map.info.a = alpha;

    flags = surface->map.info.flags;
    जर (alpha != 0xFF) {
        surface->map.info.flags |= SDL_COPY_MODULATE_ALPHA;
    } अन्यथा {
        surface->map.info.flags &= ~SDL_COPY_MODULATE_ALPHA;
    }
    जर (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    परत true;
}

bool SDL_GetSurfaceAlphaMod(SDL_Surface *surface, Uint8 *alpha)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        जर (alpha) {
            *alpha = 255;
        }
        परत SDL_InvalidParamError("surface");
    }

    जर (alpha) {
        *alpha = surface->map.info.a;
    }
    परत true;
}

bool SDL_SetSurfaceBlendMode(SDL_Surface *surface, SDL_BlendMode blendMode)
{
    पूर्णांक flags;
    bool result = true;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        परत SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(blendMode == SDL_BLENDMODE_INVALID) {
        परत SDL_InvalidParamError("blendMode");
    }

    flags = surface->map.info.flags;
    surface->map.info.flags &= ~SDL_COPY_BLEND_MASK;
    निवड (blendMode) {
    स्थिती SDL_BLENDMODE_NONE:
        थांबा;
    स्थिती SDL_BLENDMODE_BLEND:
        surface->map.info.flags |= SDL_COPY_BLEND;
        थांबा;
    स्थिती SDL_BLENDMODE_BLEND_PREMULTIPLIED:
        surface->map.info.flags |= SDL_COPY_BLEND_PREMULTIPLIED;
        थांबा;
    स्थिती SDL_BLENDMODE_ADD:
        surface->map.info.flags |= SDL_COPY_ADD;
        थांबा;
    स्थिती SDL_BLENDMODE_ADD_PREMULTIPLIED:
        surface->map.info.flags |= SDL_COPY_ADD_PREMULTIPLIED;
        थांबा;
    स्थिती SDL_BLENDMODE_MOD:
        surface->map.info.flags |= SDL_COPY_MOD;
        थांबा;
    स्थिती SDL_BLENDMODE_MUL:
        surface->map.info.flags |= SDL_COPY_MUL;
        थांबा;
    पूर्वनिर्धारित:
        result = SDL_Unsupported();
        थांबा;
    }

    जर (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }

    परत result;
}

bool SDL_GetSurfaceBlendMode(SDL_Surface *surface, SDL_BlendMode *blendMode)
{
    जर (blendMode) {
        *blendMode = SDL_BLENDMODE_INVALID;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        परत SDL_InvalidParamError("surface");
    }

    जर (!blendMode) {
        परत true;
    }

    निवड (surface->map.info.flags & SDL_COPY_BLEND_MASK) {
    स्थिती SDL_COPY_BLEND:
        *blendMode = SDL_BLENDMODE_BLEND;
        थांबा;
    स्थिती SDL_COPY_BLEND_PREMULTIPLIED:
        *blendMode = SDL_BLENDMODE_BLEND_PREMULTIPLIED;
        थांबा;
    स्थिती SDL_COPY_ADD:
        *blendMode = SDL_BLENDMODE_ADD;
        थांबा;
    स्थिती SDL_COPY_ADD_PREMULTIPLIED:
        *blendMode = SDL_BLENDMODE_ADD_PREMULTIPLIED;
        थांबा;
    स्थिती SDL_COPY_MOD:
        *blendMode = SDL_BLENDMODE_MOD;
        थांबा;
    स्थिती SDL_COPY_MUL:
        *blendMode = SDL_BLENDMODE_MUL;
        थांबा;
    पूर्वनिर्धारित:
        *blendMode = SDL_BLENDMODE_NONE;
        थांबा;
    }
    परत true;
}

bool SDL_SetSurfaceClipRect(SDL_Surface *surface, स्थिरांक SDL_Rect *rect)
{
    SDL_Rect full_rect;

    // Don't do anything if there's no surface to act on
    जर (!SDL_SurfaceValid(surface)) {
        परत false;
    }

    // Set up the full surface rectangle
    full_rect.x = 0;
    full_rect.y = 0;
    full_rect.w = surface->w;
    full_rect.h = surface->h;

    // Set the clipping rectangle
    जर (!rect) {
        surface->clip_rect = full_rect;
        परत true;
    }
    परत SDL_GetRectIntersection(rect, &full_rect, &surface->clip_rect);
}

bool SDL_GetSurfaceClipRect(SDL_Surface *surface, SDL_Rect *rect)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        जर (rect) {
            SDL_zerop(rect);
        }
        परत SDL_InvalidParamError("surface");
    }
    CHECK_PARAM(!rect) {
        परत SDL_InvalidParamError("rect");
    }
    *rect = surface->clip_rect;
    परत true;
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
bool SDL_BlitSurfaceUnchecked(SDL_Surface *src, स्थिरांक SDL_Rect *srcrect,
                             SDL_Surface *dst, स्थिरांक SDL_Rect *dstrect)
{
    // Check to make sure the blit mapping is valid
    जर (!SDL_ValidateMap(src, dst)) {
        परत false;
    }
    परत src->map.blit(src, srcrect, dst, dstrect);
}

bool SDL_BlitSurface(SDL_Surface *src, स्थिरांक SDL_Rect *srcrect, SDL_Surface *dst, स्थिरांक SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src) || (!src->pixels && !SDL_MUSTLOCK(src))) {
        परत SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst) || (!dst->pixels && !SDL_MUSTLOCK(dst))) {
        परत SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        परत SDL_SetError("Surfaces must not be locked during blit");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    जर (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
    } अन्यथा {
        r_dst.x = 0;
        r_dst.y = 0;
    }

    // clip the source rectangle to the source surface
    जर (srcrect) {
        SDL_Rect tmp;
        जर (SDL_GetRectIntersection(srcrect, &r_src, &tmp) == false) {
            परत true;
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
        जर (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &tmp) == false) {
            परत true;
        }

        // Shift srcrect, if dstrect has changed
        r_src.x += tmp.x - r_dst.x;
        r_src.y += tmp.y - r_dst.y;
        r_src.w = tmp.w;
        r_src.h = tmp.h;

        // Update dstrect
        r_dst = tmp;
    }

    जर (r_dst.w <= 0 || r_dst.h <= 0) {
        // No-op.
        परत true;
    }

    // Switch back to a fast blit if we were previously stretching
    जर (src->map.info.flags & SDL_COPY_NEAREST) {
        src->map.info.flags &= ~SDL_COPY_NEAREST;
        SDL_InvalidateMap(&src->map);
    }

    परत SDL_BlitSurfaceUnchecked(src, &r_src, dst, &r_dst);
}

स्थिर bool SDL_BlitSurfaceClippedScaled(SDL_Surface *src, स्थिरांक SDL_Rect *srcrect, SDL_Surface *dst, स्थिरांक SDL_Rect *dstrect, SDL_ScaleMode scaleMode)
{
    // We need to scale first, then blit into dst because we're clipping in the destination surface pixel coordinates
    bool result;
    पूर्णांक saved_w = src->w;
    पूर्णांक saved_h = src->h;
    शून्य *saved_pixels = src->pixels;
    src->w = srcrect->w;
    src->h = srcrect->h;
    src->pixels = (Uint8 *)src->pixels + srcrect->y * src->pitch + srcrect->x * SDL_BYTESPERPIXEL(src->format);
    SDL_Surface *scaled = SDL_ScaleSurface(src, dstrect->w, dstrect->h, scaleMode);
    जर (scaled) {
        result = SDL_BlitSurface(scaled, रिक्त, dst, dstrect);
        SDL_DestroySurface(scaled);
    } अन्यथा {
        result = false;
    }
    src->w = saved_w;
    src->h = saved_h;
    src->pixels = saved_pixels;
    परत result;
}

bool SDL_BlitSurfaceScaled(SDL_Surface *src, स्थिरांक SDL_Rect *srcrect, SDL_Surface *dst, स्थिरांक SDL_Rect *dstrect, SDL_ScaleMode scaleMode)
{
    SDL_Rect r_src, r_dst;
    bool result;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src) || (!src->pixels && !SDL_MUSTLOCK(src))) {
        परत SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst) || (!dst->pixels && !SDL_MUSTLOCK(dst))) {
        परत SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        परत SDL_SetError("Surfaces must not be locked during blit");
    }

    निवड (scaleMode) {
    स्थिती SDL_SCALEMODE_NEAREST:
        थांबा;
    स्थिती SDL_SCALEMODE_LINEAR:
        थांबा;
    स्थिती SDL_SCALEMODE_PIXELART:
        scaleMode = SDL_SCALEMODE_NEAREST;
        थांबा;
    पूर्वनिर्धारित:
        परत SDL_InvalidParamError("scaleMode");
    }

    पूर्णांक src_w = srcrect ? srcrect->w : src->w;
    पूर्णांक src_h = srcrect ? srcrect->h : src->h;
    पूर्णांक dst_w = dstrect ? dstrect->w : dst->w;
    पूर्णांक dst_h = dstrect ? dstrect->h : dst->h;
    जर (src_w == dst_w && src_h == dst_h) {
        // No scaling, defer to regular blit
        परत SDL_BlitSurface(src, srcrect, dst, dstrect);
    }

    जर (src->w == 0 || src->h == 0) {
        // Nothing to do
        परत true;
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    जर (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
        r_dst.w = dstrect->w;
        r_dst.h = dstrect->h;
    } अन्यथा {
        r_dst.x = 0;
        r_dst.y = 0;
        r_dst.w = dst->w;
        r_dst.h = dst->h;
    }

    // clip the source rectangle to the source surface
    जर (srcrect) {
        SDL_Rect desired, tmp;
        desired.x = srcrect->x;
        desired.y = srcrect->y;
        desired.w = SDL_max(srcrect->w, 1);
        desired.h = SDL_max(srcrect->h, 1);
        जर (SDL_GetRectIntersection(&desired, &r_src, &tmp) == false) {
            परत true;
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
    जर (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &tmp) == false) {
        परत true;
    }

    जर (tmp.x != r_dst.x || tmp.y != r_dst.y || tmp.w != r_dst.w || tmp.h != r_dst.h) {
        // Need to do a clipped and scaled blit
        परत SDL_BlitSurfaceClippedScaled(src, &r_src, dst, &r_dst, scaleMode);
    }

    जर (SDL_MUSTLOCK(src)) {
        जर (!SDL_LockSurface(src)) {
            परत false;
        }
    }
    जर (SDL_MUSTLOCK(dst)) {
        जर (!SDL_LockSurface(dst)) {
            जर (SDL_MUSTLOCK(src)) {
                SDL_UnlockSurface(src);
            }
            परत false;
        }
    }

    result = SDL_BlitSurfaceUncheckedScaled(src, &r_src, dst, &r_dst, scaleMode);

    जर (SDL_MUSTLOCK(src)) {
        SDL_UnlockSurface(src);
    }
    जर (SDL_MUSTLOCK(dst)) {
        SDL_UnlockSurface(dst);
    }
    परत result;
}

/**
 *  This is a semi-private blit function and it performs low-level surface
 *  scaled blitting only.
 */
bool SDL_BlitSurfaceUncheckedScaled(SDL_Surface *src, स्थिरांक SDL_Rect *srcrect, SDL_Surface *dst, स्थिरांक SDL_Rect *dstrect, SDL_ScaleMode scaleMode)
{
    स्थिर स्थिरांक Uint32 complex_copy_flags = (SDL_COPY_MODULATE_MASK | SDL_COPY_BLEND_MASK | SDL_COPY_COLORKEY);

    जर (srcrect->w > SDL_MAX_UINT16 || srcrect->h > SDL_MAX_UINT16 ||
        dstrect->w > SDL_MAX_UINT16 || dstrect->h > SDL_MAX_UINT16) {
        परत SDL_SetError("Size too large for scaling");
    }

    जर (!(src->map.info.flags & SDL_COPY_NEAREST)) {
        src->map.info.flags |= SDL_COPY_NEAREST;
        SDL_InvalidateMap(&src->map);
    }

    जर (scaleMode == SDL_SCALEMODE_NEAREST || scaleMode == SDL_SCALEMODE_PIXELART) {
        जर (!(src->map.info.flags & complex_copy_flags) &&
            src->format == dst->format &&
            (!SDL_ISPIXELFORMAT_INDEXED(src->format) ||
             (SDL_BITSPERPIXEL(src->format) == 8 && SDL_IsSamePalette(src->palette, dst->palette))) &&
            SDL_BYTESPERPIXEL(src->format) <= 4) {
            परत SDL_StretchSurface(src, srcrect, dst, dstrect, SDL_SCALEMODE_NEAREST);
        } अन्यथा जर (SDL_BITSPERPIXEL(src->format) < 8) {
            // Scaling bitmap not yet supported, convert to RGBA for blit
            bool result = false;
            SDL_Surface *tmp = SDL_ConvertSurface(src, SDL_PIXELFORMAT_ARGB8888);
            जर (tmp) {
                result = SDL_BlitSurfaceUncheckedScaled(tmp, srcrect, dst, dstrect, SDL_SCALEMODE_NEAREST);
                SDL_DestroySurface(tmp);
            }
            परत result;
        } अन्यथा {
            परत SDL_BlitSurfaceUnchecked(src, srcrect, dst, dstrect);
        }
    } अन्यथा {
        जर (!(src->map.info.flags & complex_copy_flags) &&
            src->format == dst->format &&
            !SDL_ISPIXELFORMAT_INDEXED(src->format) &&
            SDL_BYTESPERPIXEL(src->format) == 4 &&
            src->format != SDL_PIXELFORMAT_ARGB2101010) {
            // fast path
            परत SDL_StretchSurface(src, srcrect, dst, dstrect, SDL_SCALEMODE_LINEAR);
        } अन्यथा जर (SDL_BITSPERPIXEL(src->format) < 8) {
            // Scaling bitmap not yet supported, convert to RGBA for blit
            bool result = false;
            SDL_Surface *tmp = SDL_ConvertSurface(src, SDL_PIXELFORMAT_ARGB8888);
            जर (tmp) {
                result = SDL_BlitSurfaceUncheckedScaled(tmp, srcrect, dst, dstrect, scaleMode);
                SDL_DestroySurface(tmp);
            }
            परत result;
        } अन्यथा {
            // Use intermediate surface(s)
            SDL_Surface *tmp1 = रिक्त;
            bool result;
            SDL_Rect srcrect2;
            पूर्णांक is_complex_copy_flags = (src->map.info.flags & complex_copy_flags);

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
            जर (SDL_BYTESPERPIXEL(src->format) != 4 || src->format == SDL_PIXELFORMAT_ARGB2101010) {
                SDL_PixelFormat fmt;
                जर (SDL_BYTESPERPIXEL(dst->format) == 4 && dst->format != SDL_PIXELFORMAT_ARGB2101010 &&
                    (SDL_ISPIXELFORMAT_ALPHA(dst->format) || !is_complex_copy_flags)) {
                    fmt = dst->format;
                } अन्यथा {
                    fmt = SDL_PIXELFORMAT_ARGB8888;
                }
                tmp1 = SDL_ConvertSurfaceRect(src, srcrect, fmt);
                जर (!tmp1) {
                    परत false;
                }
                src = tmp1;
                srcrect2.x = 0;
                srcrect2.y = 0;
            }

            // Intermediate scaling
            जर (is_complex_copy_flags || src->format != dst->format) {
                SDL_Rect tmprect;
                SDL_Surface *tmp2 = SDL_CreateSurfaceUninitialized(dstrect->w, dstrect->h, src->format);
                SDL_StretchSurface(src, &srcrect2, tmp2, रिक्त, SDL_SCALEMODE_LINEAR);

                SDL_SetSurfaceColorMod(tmp2, r, g, b);
                SDL_SetSurfaceAlphaMod(tmp2, alpha);
                SDL_SetSurfaceBlendMode(tmp2, blendMode);

                tmprect.x = 0;
                tmprect.y = 0;
                tmprect.w = dstrect->w;
                tmprect.h = dstrect->h;
                result = SDL_BlitSurfaceUnchecked(tmp2, &tmprect, dst, dstrect);
                SDL_DestroySurface(tmp2);
            } अन्यथा {
                result = SDL_StretchSurface(src, &srcrect2, dst, dstrect, SDL_SCALEMODE_LINEAR);
            }

            SDL_DestroySurface(tmp1);
            परत result;
        }
    }
}

bool SDL_BlitSurfaceTiled(SDL_Surface *src, स्थिरांक SDL_Rect *srcrect, SDL_Surface *dst, स्थिरांक SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        परत SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        परत SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        परत SDL_SetError("Surfaces must not be locked during blit");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    जर (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
        r_dst.w = dstrect->w;
        r_dst.h = dstrect->h;
    } अन्यथा {
        r_dst.x = 0;
        r_dst.y = 0;
        r_dst.w = dst->w;
        r_dst.h = dst->h;
    }

    // clip the source rectangle to the source surface
    जर (srcrect) {
        जर (SDL_GetRectIntersection(srcrect, &r_src, &r_src) == false) {
            परत true;
        }

        // For tiling we don't adjust the destination rectangle
    }

    // clip the destination rectangle against the clip rectangle
    {
        जर (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &r_dst) == false) {
            परत true;
        }

        // For tiling we don't adjust the source rectangle
    }

    // Switch back to a fast blit if we were previously stretching
    जर (src->map.info.flags & SDL_COPY_NEAREST) {
        src->map.info.flags &= ~SDL_COPY_NEAREST;
        SDL_InvalidateMap(&src->map);
    }

    पूर्णांक rows = r_dst.h / r_src.h;
    पूर्णांक cols = r_dst.w / r_src.w;
    पूर्णांक remaining_w = r_dst.w % r_src.w;
    पूर्णांक remaining_h = r_dst.h % r_src.h;
    SDL_Rect curr_src, curr_dst;

    SDL_copyp(&curr_src, &r_src);
    curr_dst.y = r_dst.y;
    curr_dst.w = r_src.w;
    curr_dst.h = r_src.h;
    साठी (पूर्णांक y = 0; y < rows; ++y) {
        curr_dst.x = r_dst.x;
        साठी (पूर्णांक x = 0; x < cols; ++x) {
            जर (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                परत false;
            }
            curr_dst.x += curr_dst.w;
        }
        जर (remaining_w) {
            curr_src.w = remaining_w;
            curr_dst.w = remaining_w;
            जर (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                परत false;
            }
            curr_src.w = r_src.w;
            curr_dst.w = r_src.w;
        }
        curr_dst.y += curr_dst.h;
    }
    जर (remaining_h) {
        curr_src.h = remaining_h;
        curr_dst.h = remaining_h;
        curr_dst.x = r_dst.x;
        साठी (पूर्णांक x = 0; x < cols; ++x) {
            जर (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                परत false;
            }
            curr_dst.x += curr_dst.w;
        }
        जर (remaining_w) {
            curr_src.w = remaining_w;
            curr_dst.w = remaining_w;
            जर (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                परत false;
            }
        }
    }
    परत true;
}

bool SDL_BlitSurfaceTiledWithScale(SDL_Surface *src, स्थिरांक SDL_Rect *srcrect, दशांश scale, SDL_ScaleMode scaleMode, SDL_Surface *dst, स्थिरांक SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        परत SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        परत SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        परत SDL_SetError("Surfaces must not be locked during blit");
    }
    CHECK_PARAM(scale < 0.0f) {
        परत SDL_InvalidParamError("scale");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    जर (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
        r_dst.w = dstrect->w;
        r_dst.h = dstrect->h;
    } अन्यथा {
        r_dst.x = 0;
        r_dst.y = 0;
        r_dst.w = dst->w;
        r_dst.h = dst->h;
    }

    // clip the source rectangle to the source surface
    जर (srcrect) {
        जर (SDL_GetRectIntersection(srcrect, &r_src, &r_src) == false) {
            परत true;
        }

        // For tiling we don't adjust the destination rectangle
    }

    // clip the destination rectangle against the clip rectangle
    {
        जर (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &r_dst) == false) {
            परत true;
        }

        // For tiling we don't adjust the source rectangle
    }

    // Switch back to a fast blit if we were previously stretching
    जर (src->map.info.flags & SDL_COPY_NEAREST) {
        src->map.info.flags &= ~SDL_COPY_NEAREST;
        SDL_InvalidateMap(&src->map);
    }

    पूर्णांक tile_width = (पूर्णांक)SDL_roundf(r_src.w * scale);
    पूर्णांक tile_height = (पूर्णांक)SDL_roundf(r_src.h * scale);
    जर (tile_width <= 0 || tile_height <= 0) {
        // Nothing to do
        परत true;
    }
    पूर्णांक rows = r_dst.h / tile_height;
    पूर्णांक cols = r_dst.w / tile_width;
    पूर्णांक remaining_dst_w = (r_dst.w - cols * tile_width);
    पूर्णांक remaining_dst_h = (r_dst.h - rows * tile_height);
    पूर्णांक remaining_src_w = (पूर्णांक)(remaining_dst_w / scale);
    पूर्णांक remaining_src_h = (पूर्णांक)(remaining_dst_h / scale);
    SDL_Rect curr_src, curr_dst;

    SDL_copyp(&curr_src, &r_src);
    curr_dst.y = r_dst.y;
    curr_dst.w = tile_width;
    curr_dst.h = tile_height;
    साठी (पूर्णांक y = 0; y < rows; ++y) {
        curr_dst.x = r_dst.x;
        साठी (पूर्णांक x = 0; x < cols; ++x) {
            जर (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
                परत false;
            }
            curr_dst.x += curr_dst.w;
        }
        जर (remaining_dst_w > 0) {
            curr_src.w = remaining_src_w;
            curr_dst.w = remaining_dst_w;
            जर (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
                परत false;
            }
            curr_src.w = r_src.w;
            curr_dst.w = tile_width;
        }
        curr_dst.y += curr_dst.h;
    }
    जर (remaining_dst_h > 0) {
        curr_src.h = remaining_src_h;
        curr_dst.h = remaining_dst_h;
        curr_dst.x = r_dst.x;
        साठी (पूर्णांक x = 0; x < cols; ++x) {
            जर (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
                परत false;
            }
            curr_dst.x += curr_dst.w;
        }
        जर (remaining_dst_w > 0) {
            curr_src.w = remaining_src_w;
            curr_dst.w = remaining_dst_w;
            जर (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
                परत false;
            }
        }
    }
    परत true;
}

bool SDL_BlitSurface9Grid(SDL_Surface *src, स्थिरांक SDL_Rect *srcrect, पूर्णांक डावा_width, पूर्णांक उजवा_width, पूर्णांक शीर्ष_height, पूर्णांक bottom_height, दशांश scale, SDL_ScaleMode scaleMode, SDL_Surface *dst, स्थिरांक SDL_Rect *dstrect)
{
    SDL_Rect full_src, full_dst;
    SDL_Rect curr_src, curr_dst;
    पूर्णांक dst_डावा_width;
    पूर्णांक dst_उजवा_width;
    पूर्णांक dst_शीर्ष_height;
    पूर्णांक dst_bottom_height;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        परत SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        परत SDL_InvalidParamError("dst");
    }

    जर (!srcrect) {
        full_src.x = 0;
        full_src.y = 0;
        full_src.w = src->w;
        full_src.h = src->h;
        srcrect = &full_src;
    }

    जर (!dstrect) {
        full_dst.x = 0;
        full_dst.y = 0;
        full_dst.w = dst->w;
        full_dst.h = dst->h;
        dstrect = &full_dst;
    }

    जर (scale <= 0.0f || scale == 1.0f) {
        dst_डावा_width = डावा_width;
        dst_उजवा_width = उजवा_width;
        dst_शीर्ष_height = शीर्ष_height;
        dst_bottom_height = bottom_height;
    } अन्यथा {
        dst_डावा_width = (पूर्णांक)SDL_roundf(डावा_width * scale);
        dst_उजवा_width = (पूर्णांक)SDL_roundf(उजवा_width * scale);
        dst_शीर्ष_height = (पूर्णांक)SDL_roundf(शीर्ष_height * scale);
        dst_bottom_height = (पूर्णांक)SDL_roundf(bottom_height * scale);
    }

    // Upper-left corner
    curr_src.x = srcrect->x;
    curr_src.y = srcrect->y;
    curr_src.w = डावा_width;
    curr_src.h = शीर्ष_height;
    curr_dst.x = dstrect->x;
    curr_dst.y = dstrect->y;
    curr_dst.w = dst_डावा_width;
    curr_dst.h = dst_शीर्ष_height;
    जर (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        परत false;
    }

    // Upper-right corner
    curr_src.x = srcrect->x + srcrect->w - उजवा_width;
    curr_src.w = उजवा_width;
    curr_dst.x = dstrect->x + dstrect->w - dst_उजवा_width;
    curr_dst.w = dst_उजवा_width;
    जर (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        परत false;
    }

    // Lower-right corner
    curr_src.y = srcrect->y + srcrect->h - bottom_height;
    curr_dst.y = dstrect->y + dstrect->h - dst_bottom_height;
    curr_dst.h = dst_bottom_height;
    जर (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        परत false;
    }

    // Lower-left corner
    curr_src.x = srcrect->x;
    curr_src.w = डावा_width;
    curr_dst.x = dstrect->x;
    curr_dst.w = dst_डावा_width;
    जर (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        परत false;
    }

    //डावा
    curr_src.y = srcrect->y + शीर्ष_height;
    curr_src.h = srcrect->h - शीर्ष_height - bottom_height;
    curr_dst.y = dstrect->y + dst_शीर्ष_height;
    curr_dst.h = dstrect->h - dst_शीर्ष_height - dst_bottom_height;
    जर (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        परत false;
    }

    //उजवा
    curr_src.x = srcrect->x + srcrect->w - उजवा_width;
    curr_src.w = उजवा_width;
    curr_dst.x = dstrect->x + dstrect->w - dst_उजवा_width;
    curr_dst.w = dst_उजवा_width;
    जर (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        परत false;
    }

    //शीर्ष
    curr_src.x = srcrect->x + डावा_width;
    curr_src.y = srcrect->y;
    curr_src.w = srcrect->w - डावा_width - उजवा_width;
    curr_src.h = शीर्ष_height;
    curr_dst.x = dstrect->x + dst_डावा_width;
    curr_dst.y = dstrect->y;
    curr_dst.w = dstrect->w - dst_डावा_width - dst_उजवा_width;
    curr_dst.h = dst_शीर्ष_height;
    जर (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        परत false;
    }

    // Bottom
    curr_src.y = srcrect->y + srcrect->h - bottom_height;
    curr_dst.y = dstrect->y + dstrect->h - dst_bottom_height;
    curr_dst.h = dst_bottom_height;
    जर (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        परत false;
    }

    // Center
    curr_src.x = srcrect->x + डावा_width;
    curr_src.y = srcrect->y + शीर्ष_height;
    curr_src.w = srcrect->w - डावा_width - उजवा_width;
    curr_src.h = srcrect->h - शीर्ष_height - bottom_height;
    curr_dst.x = dstrect->x + dst_डावा_width;
    curr_dst.y = dstrect->y + dst_शीर्ष_height;
    curr_dst.w = dstrect->w - dst_डावा_width - dst_उजवा_width;
    curr_dst.h = dstrect->h - dst_शीर्ष_height - dst_bottom_height;
    जर (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        परत false;
    }

    परत true;
}

/*
 * Lock a surface to directly access the pixels
 */
bool SDL_LockSurface(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        परत SDL_InvalidParamError("surface");
    }

    जर (!surface->locked) {
#ifdef SDL_HAVE_RLE
        // Perform the lock
        जर (surface->internal_flags & SDL_INTERNAL_SURFACE_RLEACCEL) {
            SDL_UnRLESurface(surface);
        }
#endif
    }

    // Increment the surface lock count, for recursive locks
    ++surface->locked;
    surface->flags |= SDL_SURFACE_LOCKED;
    SDL_UpdateSurfaceLockFlag(surface);

    // Ready to go..
    परत true;
}

/*
 * Unlock a previously locked surface
 */
शून्य SDL_UnlockSurface(SDL_Surface *surface)
{
    जर (!SDL_SurfaceValid(surface)) {
        परत;
    }

    // Only perform an unlock if we are locked
    जर (!surface->locked || (--surface->locked > 0)) {
        परत;
    }

    surface->flags &= ~SDL_SURFACE_LOCKED;
    SDL_UpdateSurfaceLockFlag(surface);
}

स्थिर bool SDL_FlipSurfaceHorizontal(SDL_Surface *surface)
{
    bool isstack;
    Uint8 *row, *a, *b, *tmp;
    पूर्णांक i, j, bpp;

    जर (SDL_BITSPERPIXEL(surface->format) < 8) {
        // We could implement this if needed, but we'd have to flip sets of bits within a byte
        परत SDL_Unsupported();
    }

    जर (surface->h <= 0) {
        परत true;
    }

    जर (surface->w <= 1) {
        परत true;
    }

    bpp = SDL_BYTESPERPIXEL(surface->format);
    row = (Uint8 *)surface->pixels;
    tmp = SDL_small_alloc(Uint8, surface->pitch, &isstack);
    जर (!tmp) {
        परत false;
    }
    साठी (i = surface->h; i--; ) {
        a = row;
        b = a + (surface->w - 1) * bpp;
        साठी (j = surface->w / 2; j--; ) {
            SDL_memcpy(tmp, a, bpp);
            SDL_memcpy(a, b, bpp);
            SDL_memcpy(b, tmp, bpp);
            a += bpp;
            b -= bpp;
        }
        row += surface->pitch;
    }
    SDL_small_free(tmp, isstack);
    परत true;
}

स्थिर bool SDL_FlipSurfaceVertical(SDL_Surface *surface)
{
    bool isstack;
    Uint8 *a, *b, *tmp;
    पूर्णांक i;

    जर (surface->h <= 1) {
        परत true;
    }

    a = (Uint8 *)surface->pixels;
    b = a + (surface->h - 1) * surface->pitch;
    tmp = SDL_small_alloc(Uint8, surface->pitch, &isstack);
    जर (!tmp) {
        परत false;
    }
    साठी (i = surface->h / 2; i--; ) {
        SDL_memcpy(tmp, a, surface->pitch);
        SDL_memcpy(a, b, surface->pitch);
        SDL_memcpy(b, tmp, surface->pitch);
        a += surface->pitch;
        b -= surface->pitch;
    }
    SDL_small_free(tmp, isstack);
    परत true;
}

bool SDL_FlipSurface(SDL_Surface *surface, SDL_FlipMode flip)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        परत SDL_InvalidParamError("surface");
    }
    जर (!surface->pixels) {
        परत true;
    }

    bool result = true;
    निवड (flip) {
    स्थिती SDL_FLIP_HORIZONTAL:
        result = SDL_FlipSurfaceHorizontal(surface);
        थांबा;
    स्थिती SDL_FLIP_VERTICAL:
        result = SDL_FlipSurfaceVertical(surface);
        थांबा;
    स्थिती SDL_FLIP_HORIZONTAL_AND_VERTICAL:
        result &= SDL_FlipSurfaceHorizontal(surface);
        result &= SDL_FlipSurfaceVertical(surface);
        थांबा;
    पूर्वनिर्धारित:
        result = SDL_InvalidParamError("flip");
        थांबा;
    }
    परत result;
}

स्थिर SDL_Surface *SDL_ConvertSurfaceRectAndColorspace(SDL_Surface *surface, स्थिरांक SDL_Rect *rect, SDL_PixelFormat format, SDL_Palette *palette, SDL_Colorspace colorspace, SDL_PropertiesID props)
{
    SDL_Palette *temp_palette = रिक्त;
    SDL_Surface *convert = रिक्त;
    SDL_Colorspace src_colorspace;
    SDL_PropertiesID src_properties;
    Uint32 copy_flags;
    SDL_Color copy_color;
    SDL_Rect bounds;
    bool result;
    bool palette_ck_transform = false;
    Uint8 palette_ck_मूल्य = 0;
    Uint8 *palette_saved_alpha = रिक्त;
    पूर्णांक palette_saved_alpha_ncolors = 0;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        जा error;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        जा error;
    }

    // Set the bounds of the new surface
    bounds.x = 0;
    bounds.y = 0;
    bounds.w = surface->w;
    bounds.h = surface->h;
    जर (rect) {
        bounds.w = rect->w;
        bounds.h = rect->h;
    } अन्यथा {
        rect = &bounds;
    }

    // Check for empty destination palette! (results in empty image)
    जर (palette) {
        पूर्णांक i;
        साठी (i = 0; i < palette->ncolors; ++i) {
            जर ((palette->colors[i].r != 0xFF) || (palette->colors[i].g != 0xFF) || (palette->colors[i].b != 0xFF)) {
                थांबा;
            }
        }
        जर (i == palette->ncolors) {
            SDL_SetError("Empty destination palette");
            जा error;
        }
    } अन्यथा जर (SDL_ISPIXELFORMAT_INDEXED(format)) {
        // Create a dither palette for conversion
        temp_palette = SDL_CreatePalette(1 << SDL_BITSPERPIXEL(format));
        जर (temp_palette) {
            SDL_DitherPalette(temp_palette);
            palette = temp_palette;
        }
    }

    src_colorspace = surface->colorspace;
    src_properties = surface->props;

    // Create a new surface with the desired format
    जर (surface->pixels || SDL_MUSTLOCK(surface)) {
        convert = SDL_CreateSurfaceUninitialized(rect->w, rect->h, format);
    } अन्यथा {
        convert = SDL_CreateSurfaceFrom(rect->w, rect->h, format, रिक्त, 0);
    }
    जर (!convert) {
        जा error;
    }
    जर (SDL_ISPIXELFORMAT_INDEXED(format)) {
        SDL_SetSurfacePalette(convert, palette);
    }

    जर (colorspace == SDL_COLORSPACE_UNKNOWN) {
        colorspace = src_colorspace;
    }
    SDL_SetSurfaceColorspace(convert, colorspace);

    जर (SDL_ISPIXELFORMAT_FOURCC(format) || SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        जर (surface->format == SDL_PIXELFORMAT_MJPG && format == SDL_PIXELFORMAT_MJPG) {
            // Just do a straight pixel copy of the JPEG image
            माप_प्रकार size = (माप_प्रकार)surface->pitch;
            convert->pixels = SDL_malloc(size);
            जर (!convert->pixels) {
                जा error;
            }
            convert->flags &= ~SDL_SURFACE_PREALLOCATED;
            convert->pitch = surface->pitch;
            SDL_memcpy(convert->pixels, surface->pixels, size);

        } अन्यथा जर (!SDL_ConvertPixelsAndColorspace(surface->w, surface->h, surface->format, src_colorspace, src_properties, surface->pixels, surface->pitch, convert->format, colorspace, props, convert->pixels, convert->pitch)) {
            जा error;
        }

        // Save the original copy flags
        copy_flags = surface->map.info.flags;

        जा end;
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
    जर (surface->palette && SDL_ISPIXELFORMAT_ALPHA(format)) {
        bool set_opaque = false;

        bool is_opaque, has_alpha_channel;
        SDL_DetectPalette(surface->palette, &is_opaque, &has_alpha_channel);

        जर (is_opaque) {
            जर (!has_alpha_channel) {
                set_opaque = true;
            }
        }

        // Set opaque and backup palette alpha values
        जर (set_opaque) {
            पूर्णांक i;
            palette_saved_alpha_ncolors = surface->palette->ncolors;
            जर (palette_saved_alpha_ncolors > 0) {
                palette_saved_alpha = SDL_चळत_alloc(Uint8, palette_saved_alpha_ncolors);
                साठी (i = 0; i < palette_saved_alpha_ncolors; i++) {
                    palette_saved_alpha[i] = surface->palette->colors[i].a;
                    surface->palette->colors[i].a = SDL_ALPHA_OPAQUE;
                }
            }
        }
    }

    // Transform colorkey to alpha. for cases where source palette has duplicate values, and colorkey is one of them
    जर (copy_flags & SDL_COPY_COLORKEY) {
        जर (surface->palette && !palette) {
            palette_ck_transform = true;
            palette_ck_मूल्य = surface->palette->colors[surface->map.info.colorkey].a;
            surface->palette->colors[surface->map.info.colorkey].a = SDL_ALPHA_TRANSPARENT;
        }
    }

    जर (surface->pixels || SDL_MUSTLOCK(surface)) {
        result = SDL_BlitSurfaceUnchecked(surface, rect, convert, &bounds);
    } अन्यथा {
        result = true;
    }

    // Restore colorkey alpha value
    जर (palette_ck_transform) {
        surface->palette->colors[surface->map.info.colorkey].a = palette_ck_मूल्य;
    }

    // Restore palette alpha values
    जर (palette_saved_alpha) {
        पूर्णांक i;
        साठी (i = 0; i < palette_saved_alpha_ncolors; i++) {
            surface->palette->colors[i].a = palette_saved_alpha[i];
        }
        SDL_चळत_free(palette_saved_alpha);
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
    जर (!result) {
        जा error;
    }

    जर (copy_flags & SDL_COPY_COLORKEY) {
        bool set_colorkey_by_color = false;
        bool convert_colorkey = true;

        जर (surface->palette) {
            जर (palette &&
                surface->palette->ncolors <= palette->ncolors &&
                (SDL_memcmp(surface->palette->colors, palette->colors,
                            surface->palette->ncolors * आकार(SDL_Color)) == 0)) {
                // The palette is identical, just set the same colorkey
                SDL_Set_Surface_Color_किल्ली(convert, true, surface->map.info.colorkey);
            } अन्यथा जर (!palette) {
                जर (SDL_ISPIXELFORMAT_ALPHA(format)) {
                    // No need to add the colorkey, transparency is in the alpha channel
                } अन्यथा {
                    // Only set the colorkey information
                    set_colorkey_by_color = true;
                    convert_colorkey = false;
                }
            } अन्यथा {
                set_colorkey_by_color = true;
            }
        } अन्यथा {
            set_colorkey_by_color = true;
        }

        जर (set_colorkey_by_color) {
            SDL_Surface *tmp;
            SDL_Surface *tmp2;
            पूर्णांक converted_colorkey = 0;

            // Create a dummy surface to get the colorkey converted
            tmp = SDL_CreateSurfaceUninitialized(1, 1, surface->format);
            जर (!tmp) {
                जा error;
            }

            // Share the palette, if any
            जर (surface->palette) {
                SDL_SetSurfacePalette(tmp, surface->palette);
            }

            SDL_FillSurfaceRect(tmp, रिक्त, surface->map.info.colorkey);

            tmp->map.info.flags &= ~SDL_COPY_COLORKEY;

            // Conversion of the colorkey
            tmp2 = SDL_ConvertSurfaceAndColorspace(tmp, format, palette, colorspace, props);
            जर (!tmp2) {
                SDL_DestroySurface(tmp);
                जा error;
            }

            // Get the converted colorkey
            SDL_memcpy(&converted_colorkey, tmp2->pixels, tmp2->fmt->bytes_per_pixel);

            SDL_DestroySurface(tmp);
            SDL_DestroySurface(tmp2);

            // Set the converted colorkey on the new surface
            SDL_Set_Surface_Color_किल्ली(convert, true, converted_colorkey);

            // This is needed when converting for 3D texture upload
            जर (convert_colorkey) {
                SDL_ConvertColorkeyToAlpha(convert, true);
            }
        }
    }

end:
    जर (temp_palette) {
        SDL_DestroyPalette(temp_palette);
    }

    SDL_SetSurfaceClipRect(convert, &surface->clip_rect);

    /* Enable alpha blending by default if the new surface has an
     * alpha channel or alpha modulation */
    जर (SDL_ISPIXELFORMAT_ALPHA(format) ||
        (copy_flags & SDL_COPY_MODULATE_ALPHA)) {
        SDL_SetSurfaceBlendMode(convert, SDL_BLENDMODE_BLEND);
    }
    जर (copy_flags & SDL_COPY_RLE_DESIRED) {
        SDL_SetSurfaceRLE(convert, true);
    }

    // Copy alternate images
    साठी (पूर्णांक i = 0; i < surface->अंक_images; ++i) {
        जर (!SDL_AddSurfaceAlternateImage(convert, surface->images[i])) {
            जा error;
        }
    }

    // Copy properties
    जर (surface->props) {
        जर (!SDL_CopyProperties(surface->props, SDL_GetSurfaceProperties(convert))) {
            जा error;
        }

        // Make sure the new surface doesn't reference an old SDL2 surface.
        SDL_ClearProperty(SDL_GetSurfaceProperties(convert), "sdl2-compat.surface2");
    }

    // We're ready to go!
    परत convert;

error:
    जर (temp_palette) {
        SDL_DestroyPalette(temp_palette);
    }
    जर (convert) {
        SDL_DestroySurface(convert);
    }
    परत रिक्त;
}

SDL_Surface *SDL_ConvertSurfaceAndColorspace(SDL_Surface *surface, SDL_PixelFormat format, SDL_Palette *palette, SDL_Colorspace colorspace, SDL_PropertiesID props)
{
    परत SDL_ConvertSurfaceRectAndColorspace(surface, रिक्त, format, palette, colorspace, props);
}

SDL_Surface *SDL_RotateSurface(SDL_Surface *surface, दशांश angle)
{
    SDL_Surface *rotated = रिक्त;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        परत रिक्त;
    }

    SDL_Rect rect_dest;
    द्विगुण cangle, sangle;
    SDL_FPoint center = { surface->w * 0.5f, surface->h * 0.5f };
    SDLgfx_rotozoomSurfaceSizeTrig(surface->w, surface->h, angle, &center, &rect_dest, &cangle, &sangle);

    // This function requires a 32-bit surface or 8-bit surface with a colorkey
    जर ((SDL_BITSPERPIXEL(surface->format) == 32 && SDL_PIXELLAYOUT(surface->format) == SDL_PACKEDLAYOUT_8888) ||
        (surface->format == SDL_PIXELFORMAT_INDEX8 && SDL_Surface_Has_Color_किल्ली(surface))) {
        rotated = SDLgfx_rotateSurface(surface, angle, 1, 0, 0, &rect_dest, cangle, sangle, &center);
    } अन्यथा {
        SDL_Surface *convert = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);
        जर (convert) {
            SDL_Surface *tmp = SDLgfx_rotateSurface(convert, angle, 1, 0, 0, &rect_dest, cangle, sangle, &center);
            जर (tmp) {
                rotated = SDL_ConvertSurfaceAndColorspace(tmp, surface->format, surface->palette, surface->colorspace, surface->props);
                SDL_DestroySurface(tmp);
            }
            SDL_DestroySurface(convert);
        }
    }

    जर (rotated) {
        जर (SDL_HasProperty(surface->props, SDL_PROP_SURFACE_ROTATION_FLOAT)) {
            स्थिरांक दशांश rotation = (SDL_Get_संख्या_Property(surface->props, SDL_PROP_SURFACE_ROTATION_FLOAT, 0) - angle);
            SDL_SetFloatProperty(SDL_GetSurfaceProperties(rotated), SDL_PROP_SURFACE_ROTATION_FLOAT, rotation);
        }
    }

    परत rotated;
}

SDL_Surface *SDL_DuplicateSurface(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        परत रिक्त;
    }

    परत SDL_ConvertSurfaceAndColorspace(surface, surface->format, surface->palette, surface->colorspace, surface->props);
}

SDL_Surface *SDL_ScaleSurface(SDL_Surface *surface, पूर्णांक width, पूर्णांक height, SDL_ScaleMode scaleMode)
{
    SDL_Surface *convert = रिक्त;
    Uint32 copy_flags;
    SDL_Color copy_color;
    bool rc;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        जा error;
    }

    जर (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // We can't directly scale a YUV surface (yet!)
        SDL_Surface *tmp = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        जर (!tmp) {
            परत रिक्त;
        }

        SDL_Surface *scaled = SDL_ScaleSurface(tmp, width, height, scaleMode);
        SDL_DestroySurface(tmp);
        जर (!scaled) {
            परत रिक्त;
        }

        SDL_Surface *result = SDL_ConvertSurfaceAndColorspace(scaled, surface->format, रिक्त, surface->colorspace, surface->props);
        SDL_DestroySurface(scaled);
        परत result;
    }

    जर (SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        // Linear scaling requires conversion to RGBA and then slow pixel color lookup
        scaleMode = SDL_SCALEMODE_NEAREST;
    }

    // Create a new surface with the desired size
    जर (surface->pixels || SDL_MUSTLOCK(surface)) {
        convert = SDL_CreateSurfaceUninitialized(width, height, surface->format);
    } अन्यथा {
        convert = SDL_CreateSurfaceFrom(width, height, surface->format, रिक्त, 0);
    }
    जर (!convert) {
        जा error;
    }
    SDL_SetSurfacePalette(convert, surface->palette);
    SDL_SetSurfaceColorspace(convert, surface->colorspace);
    SDL_SetSurfaceRLE(convert, SDL_SurfaceHasRLE(surface));

    जर (surface->pixels || SDL_MUSTLOCK(surface)) {
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

        rc = SDL_BlitSurfaceScaled(surface, रिक्त, convert, रिक्त, scaleMode);

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
    } अन्यथा {
        rc = true;
    }

    // SDL_BlitSurfaceScaled failed, and so the conversion
    जर (!rc) {
        जा error;
    }

    // We're ready to go!
    परत convert;

error:
    जर (convert) {
        SDL_DestroySurface(convert);
    }
    परत रिक्त;
}

SDL_Surface *SDL_ConvertSurfaceRect(SDL_Surface *surface, स्थिरांक SDL_Rect *rect, SDL_PixelFormat format)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        परत रिक्त;
    }

    परत SDL_ConvertSurfaceRectAndColorspace(surface, rect, format, रिक्त, SDL_GetDefaultColorspaceForFormat(format), surface->props);
}

SDL_Surface *SDL_ConvertSurface(SDL_Surface *surface, SDL_PixelFormat format)
{
    परत SDL_ConvertSurfaceRect(surface, रिक्त, format);
}

SDL_Surface *SDL_DuplicatePixels(पूर्णांक width, पूर्णांक height, SDL_PixelFormat format, SDL_Colorspace colorspace, शून्य *pixels, पूर्णांक pitch)
{
    SDL_Surface *surface;
    जर (pixels) {
        surface = SDL_CreateSurfaceUninitialized(width, height, format);
    } अन्यथा {
        surface = SDL_CreateSurfaceFrom(width, height, format, रिक्त, 0);
    }
    जर (!surface) {
        परत रिक्त;
    }
    SDL_SetSurfaceColorspace(surface, colorspace);

    जर (surface->pixels) {
        पूर्णांक length = width * SDL_BYTESPERPIXEL(format);
        Uint8 *src = (Uint8 *)pixels;
        Uint8 *dst = (Uint8 *)surface->pixels;
        पूर्णांक rows = height;
        पर्यंत (rows--) {
            SDL_memcpy(dst, src, length);
            dst += surface->pitch;
            src += pitch;
        }
    }
    परत surface;
}

bool SDL_ConvertPixelsAndColorspace(पूर्णांक width, पूर्णांक height,
                      SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, स्थिरांक शून्य *src, पूर्णांक src_pitch,
                      SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, शून्य *dst, पूर्णांक dst_pitch)
{
    SDL_Surface src_surface;
    SDL_Surface dst_surface;
    SDL_Rect rect;
    शून्य *nonconst_src = (शून्य *)src;
    bool result;

    CHECK_PARAM(!src) {
        परत SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!src_pitch) {
        परत SDL_InvalidParamError("src_pitch");
    }
    CHECK_PARAM(!dst) {
        परत SDL_InvalidParamError("dst");
    }
    CHECK_PARAM(!dst_pitch) {
        परत SDL_InvalidParamError("dst_pitch");
    }

    जर (src_colorspace == SDL_COLORSPACE_UNKNOWN) {
        src_colorspace = SDL_GetDefaultColorspaceForFormat(src_format);
    }
    जर (dst_colorspace == SDL_COLORSPACE_UNKNOWN) {
        dst_colorspace = SDL_GetDefaultColorspaceForFormat(dst_format);
    }

    जर (src_format == SDL_PIXELFORMAT_MJPG) {
        परत SDL_ConvertPixels_STB(width, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    }

#ifdef SDL_HAVE_YUV
    जर (SDL_ISPIXELFORMAT_FOURCC(src_format) && SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        परत SDL_ConvertPixels_YUV_to_YUV(width, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } अन्यथा जर (SDL_ISPIXELFORMAT_FOURCC(src_format)) {
        परत SDL_ConvertPixels_YUV_to_RGB(width, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } अन्यथा जर (SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        परत SDL_ConvertPixels_RGB_to_YUV(width, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    }
#अन्यथा
    जर (SDL_ISPIXELFORMAT_FOURCC(src_format) || SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        परत SDL_SetError("SDL not built with YUV support");
    }
#endif

    // Fast path for same format copy
    जर (src_format == dst_format && src_colorspace == dst_colorspace) {
        जर (src_pitch == dst_pitch) {
            SDL_memcpy(dst, src, height * src_pitch);
        } अन्यथा {
            पूर्णांक i;
            स्थिरांक पूर्णांक bpp = SDL_BYTESPERPIXEL(src_format);
            width *= bpp;
            साठी (i = height; i--;) {
                SDL_memcpy(dst, src, width);
                src = (स्थिरांक Uint8 *)src + src_pitch;
                dst = (Uint8 *)dst + dst_pitch;
            }
        }
        परत true;
    }

    जर (!SDL_InitializeSurface(&src_surface, width, height, src_format, src_colorspace, src_properties, nonconst_src, src_pitch, true)) {
        परत false;
    }
    SDL_SetSurfaceBlendMode(&src_surface, SDL_BLENDMODE_NONE);

    जर (!SDL_InitializeSurface(&dst_surface, width, height, dst_format, dst_colorspace, dst_properties, dst, dst_pitch, true)) {
        परत false;
    }

    // Set up the rect and go!
    rect.x = 0;
    rect.y = 0;
    rect.w = width;
    rect.h = height;
    result = SDL_BlitSurfaceUnchecked(&src_surface, &rect, &dst_surface, &rect);

    SDL_DestroySurface(&src_surface);
    SDL_DestroySurface(&dst_surface);

    परत result;
}

bool SDL_ConvertPixels(पूर्णांक width, पूर्णांक height, SDL_PixelFormat src_format, स्थिरांक शून्य *src, पूर्णांक src_pitch, SDL_PixelFormat dst_format, शून्य *dst, पूर्णांक dst_pitch)
{
    परत SDL_ConvertPixelsAndColorspace(width, height,
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

स्थिर शून्य SDL_PremultiplyAlpha_AXYZ8888(पूर्णांक width, पूर्णांक height, स्थिरांक शून्य *src, पूर्णांक src_pitch, शून्य *dst, पूर्णांक dst_pitch)
{
    पूर्णांक c;
    Uint32 srcpixel;
    Uint32 srcR, srcG, srcB, srcA;
    Uint32 dstpixel;
    Uint32 dstR, dstG, dstB, dstA;

    पर्यंत (height--) {
        स्थिरांक Uint32 *src_px = (स्थिरांक Uint32 *)src;
        Uint32 *dst_px = (Uint32 *)dst;
        साठी (c = width; c; --c) {
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
        src = (स्थिरांक Uint8 *)src + src_pitch;
        dst = (Uint8 *)dst + dst_pitch;
    }
}

स्थिर शून्य SDL_PremultiplyAlpha_XYZA8888(पूर्णांक width, पूर्णांक height, स्थिरांक शून्य *src, पूर्णांक src_pitch, शून्य *dst, पूर्णांक dst_pitch)
{
    पूर्णांक c;
    Uint32 srcpixel;
    Uint32 srcR, srcG, srcB, srcA;
    Uint32 dstpixel;
    Uint32 dstR, dstG, dstB, dstA;

    पर्यंत (height--) {
        स्थिरांक Uint32 *src_px = (स्थिरांक Uint32 *)src;
        Uint32 *dst_px = (Uint32 *)dst;
        साठी (c = width; c; --c) {
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
        src = (स्थिरांक Uint8 *)src + src_pitch;
        dst = (Uint8 *)dst + dst_pitch;
    }
}

स्थिर शून्य SDL_PremultiplyAlpha_AXYZ128(पूर्णांक width, पूर्णांक height, स्थिरांक शून्य *src, पूर्णांक src_pitch, शून्य *dst, पूर्णांक dst_pitch)
{
    पूर्णांक c;
    दशांश flR, flG, flB, flA;

    पर्यंत (height--) {
        स्थिरांक दशांश *src_px = (स्थिरांक दशांश *)src;
        दशांश *dst_px = (दशांश *)dst;
        साठी (c = width; c; --c) {
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
        src = (स्थिरांक Uint8 *)src + src_pitch;
        dst = (Uint8 *)dst + dst_pitch;
    }
}

स्थिर bool SDL_PremultiplyAlphaPixelsAndColorspace(पूर्णांक width, पूर्णांक height, SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, स्थिरांक शून्य *src, पूर्णांक src_pitch, SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, शून्य *dst, पूर्णांक dst_pitch, bool linear)
{
    SDL_Surface *convert = रिक्त;
    शून्य *final_dst = dst;
    पूर्णांक final_dst_pitch = dst_pitch;
    SDL_PixelFormat format;
    SDL_Colorspace colorspace;
    bool result = false;

    CHECK_PARAM(!src) {
        परत SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!src_pitch) {
        परत SDL_InvalidParamError("src_pitch");
    }
    CHECK_PARAM(!dst) {
        परत SDL_InvalidParamError("dst");
    }
    CHECK_PARAM(!dst_pitch) {
        परत SDL_InvalidParamError("dst_pitch");
    }

    // Use a high precision format if we're converting to linear colorspace or using high precision pixel formats
    जर (linear ||
        SDL_ISPIXELFORMAT_10BIT(src_format) || SDL_BITSPERPIXEL(src_format) > 32 ||
        SDL_ISPIXELFORMAT_10BIT(dst_format) || SDL_BITSPERPIXEL(dst_format) > 32) {
        जर (src_format == SDL_PIXELFORMAT_ARGB128_FLOAT ||
            src_format == SDL_PIXELFORMAT_ABGR128_FLOAT) {
            format = src_format;
        } अन्यथा {
            format = SDL_PIXELFORMAT_ARGB128_FLOAT;
        }
    } अन्यथा {
        जर (src_format == SDL_PIXELFORMAT_ARGB8888 ||
            src_format == SDL_PIXELFORMAT_ABGR8888 ||
            src_format == SDL_PIXELFORMAT_RGBA8888 ||
            src_format == SDL_PIXELFORMAT_BGRA8888) {
            format = src_format;
        } अन्यथा {
            format = SDL_PIXELFORMAT_ARGB8888;
        }
    }
    जर (linear) {
        colorspace = SDL_COLORSPACE_SRGB_LINEAR;
    } अन्यथा {
        colorspace = SDL_COLORSPACE_SRGB;
    }

    जर (src_format != format || src_colorspace != colorspace) {
        convert = SDL_CreateSurfaceUninitialized(width, height, format);
        जर (!convert) {
            जा done;
        }
        जर (!SDL_ConvertPixelsAndColorspace(width, height, src_format, src_colorspace, src_properties, src, src_pitch, format, colorspace, 0, convert->pixels, convert->pitch)) {
            जा done;
        }

        src = convert->pixels;
        src_pitch = convert->pitch;
        dst = convert->pixels;
        dst_pitch = convert->pitch;

    } अन्यथा जर (dst_format != format || dst_colorspace != colorspace) {
        convert = SDL_CreateSurfaceUninitialized(width, height, format);
        जर (!convert) {
            जा done;
        }
        dst = convert->pixels;
        dst_pitch = convert->pitch;
    }

    निवड (format) {
    स्थिती SDL_PIXELFORMAT_ARGB8888:
    स्थिती SDL_PIXELFORMAT_ABGR8888:
        SDL_PremultiplyAlpha_AXYZ8888(width, height, src, src_pitch, dst, dst_pitch);
        थांबा;
    स्थिती SDL_PIXELFORMAT_RGBA8888:
    स्थिती SDL_PIXELFORMAT_BGRA8888:
        SDL_PremultiplyAlpha_XYZA8888(width, height, src, src_pitch, dst, dst_pitch);
        थांबा;
    स्थिती SDL_PIXELFORMAT_ARGB128_FLOAT:
    स्थिती SDL_PIXELFORMAT_ABGR128_FLOAT:
        SDL_PremultiplyAlpha_AXYZ128(width, height, src, src_pitch, dst, dst_pitch);
        थांबा;
    पूर्वनिर्धारित:
        SDL_SetError("Unexpected internal pixel format");
        जा done;
    }

    जर (dst != final_dst) {
        जर (!SDL_ConvertPixelsAndColorspace(width, height, format, colorspace, 0, convert->pixels, convert->pitch, dst_format, dst_colorspace, dst_properties, final_dst, final_dst_pitch)) {
            जा done;
        }
    }
    result = true;

done:
    जर (convert) {
        SDL_DestroySurface(convert);
    }
    परत result;
}

bool SDL_PremultiplyAlpha(पूर्णांक width, पूर्णांक height,
                         SDL_PixelFormat src_format, स्थिरांक शून्य *src, पूर्णांक src_pitch,
                         SDL_PixelFormat dst_format, शून्य *dst, पूर्णांक dst_pitch, bool linear)
{
    SDL_Colorspace src_colorspace = SDL_GetDefaultColorspaceForFormat(src_format);
    SDL_Colorspace dst_colorspace = SDL_GetDefaultColorspaceForFormat(dst_format);

    परत SDL_PremultiplyAlphaPixelsAndColorspace(width, height, src_format, src_colorspace, 0, src, src_pitch, dst_format, dst_colorspace, 0, dst, dst_pitch, linear);
}

bool SDL_PremultiplySurfaceAlpha(SDL_Surface *surface, bool linear)
{
    SDL_Colorspace colorspace;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        परत SDL_InvalidParamError("surface");
    }

    colorspace = surface->colorspace;

    परत SDL_PremultiplyAlphaPixelsAndColorspace(surface->w, surface->h, surface->format, colorspace, surface->props, surface->pixels, surface->pitch, surface->format, colorspace, surface->props, surface->pixels, surface->pitch, linear);
}

bool SDL_ClearSurface(SDL_Surface *surface, दशांश r, दशांश g, दशांश b, दशांश a)
{
    SDL_Rect clip_rect;
    bool result = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        परत SDL_InvalidParamError("surface");
    }

    SDL_GetSurfaceClipRect(surface, &clip_rect);
    SDL_SetSurfaceClipRect(surface, रिक्त);

    जर (!SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_BYTESPERPIXEL(surface->format) <= आकार(Uint32)) {
        Uint32 color;

        color = SDL_MapSurfaceRGBA(surface,
                    (Uint8)SDL_roundf(SDL_clamp(r, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(g, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(b, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(a, 0.0f, 1.0f) * 255.0f));
        result = SDL_FillSurfaceRect(surface, रिक्त, color);
    } अन्यथा जर (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // We can't directly set an RGB value on a YUV surface
        SDL_Surface *tmp = SDL_CreateSurfaceUninitialized(surface->w, surface->h, SDL_PIXELFORMAT_ARGB8888);
        जर (!tmp) {
            जा done;
        }

        जर (SDL_ClearSurface(tmp, r, g, b, a)) {
            result = SDL_ConvertPixelsAndColorspace(surface->w, surface->h, tmp->format, tmp->colorspace, tmp->props, tmp->pixels, tmp->pitch, surface->format, surface->colorspace, surface->props, surface->pixels, surface->pitch);
        }
        SDL_DestroySurface(tmp);
    } अन्यथा {
        // Take advantage of blit color conversion
        SDL_Surface *tmp = SDL_CreateSurfaceUninitialized(1, 1, SDL_PIXELFORMAT_RGBA128_FLOAT);
        जर (!tmp) {
            जा done;
        }
        SDL_SetSurfaceColorspace(tmp, surface->colorspace);
        SDL_SetSurfaceBlendMode(tmp, SDL_BLENDMODE_NONE);

        दशांश *pixels = (दशांश *)tmp->pixels;
        pixels[0] = r;
        pixels[1] = g;
        pixels[2] = b;
        pixels[3] = a;

        result = SDL_BlitSurfaceScaled(tmp, रिक्त, surface, रिक्त, SDL_SCALEMODE_NEAREST);
        SDL_DestroySurface(tmp);
    }

done:
    SDL_SetSurfaceClipRect(surface, &clip_rect);

    परत result;
}

Uint32 SDL_MapSurfaceRGB(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b)
{
    परत SDL_MapSurfaceRGBA(surface, r, g, b, SDL_ALPHA_OPAQUE);
}

Uint32 SDL_MapSurfaceRGBA(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        परत true;
    }
    परत SDL_MapRGBA(surface->fmt, surface->palette, r, g, b, a);
}

// This function Copyright 2023 Collabora Ltd., contributed to SDL under the ZLib license
bool SDL_ReadSurfacePixel(SDL_Surface *surface, पूर्णांक x, पूर्णांक y, Uint8 *r, Uint8 *g, Uint8 *b, Uint8 *a)
{
    Uint32 pixel = 0;
    माप_प्रकार bytes_per_pixel;
    Uint8 unused;
    Uint8 *p;
    bool result = false;

    जर (r) {
        *r = 0;
    } अन्यथा {
        r = &unused;
    }

    जर (g) {
        *g = 0;
    } अन्यथा {
        g = &unused;
    }

    जर (b) {
        *b = 0;
    } अन्यथा {
        b = &unused;
    }

    जर (a) {
        *a = 0;
    } अन्यथा {
        a = &unused;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        परत SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        परत SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        परत SDL_InvalidParamError("y");
    }

    bytes_per_pixel = SDL_BYTESPERPIXEL(surface->format);

    जर (SDL_MUSTLOCK(surface)) {
        जर (!SDL_LockSurface(surface)) {
            परत false;
        }
    }

    p = (Uint8 *)surface->pixels + y * surface->pitch + x * bytes_per_pixel;

    जर (bytes_per_pixel <= आकार(pixel) &&
        !SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_COLORSPACEPRIMARIES(surface->colorspace) == SDL_COLOR_PRIMARIES_BT709) {
        /* Fill the appropriate number of least-significant bytes of pixel,
         * leaving the most-significant bytes set to zero */
#जर SDL_BYTEORDER == SDL_BIG_ENDIAN
        SDL_memcpy(((Uint8 *)&pixel) + (आकार(pixel) - bytes_per_pixel), p, bytes_per_pixel);
#अन्यथा
        SDL_memcpy(&pixel, p, bytes_per_pixel);
#endif
        SDL_GetRGBA(pixel, surface->fmt, surface->palette, r, g, b, a);
        result = true;
    } अन्यथा जर (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // FIXME: We need code to extract a single macroblock from a YUV surface
        SDL_Surface *converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        जर (converted) {
            result = SDL_ReadSurfacePixel(converted, x, y, r, g, b, a);
            SDL_DestroySurface(converted);
        }
    } अन्यथा {
        // This is really slow, but it gets the job done
        Uint8 rgba[4];

        जर (SDL_ConvertPixelsAndColorspace(1, 1, surface->format, surface->colorspace, surface->props, p, surface->pitch, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, rgba, आकार(rgba))) {
            *r = rgba[0];
            *g = rgba[1];
            *b = rgba[2];
            *a = rgba[3];
            result = true;
        }
    }

    जर (SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }
    परत result;
}

bool SDL_ReadSurfacePixelFloat(SDL_Surface *surface, पूर्णांक x, पूर्णांक y, दशांश *r, दशांश *g, दशांश *b, दशांश *a)
{
    दशांश unused;
    bool result = false;

    जर (r) {
        *r = 0.0f;
    } अन्यथा {
        r = &unused;
    }

    जर (g) {
        *g = 0.0f;
    } अन्यथा {
        g = &unused;
    }

    जर (b) {
        *b = 0.0f;
    } अन्यथा {
        b = &unused;
    }

    जर (a) {
        *a = 0.0f;
    } अन्यथा {
        a = &unused;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        परत SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        परत SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        परत SDL_InvalidParamError("y");
    }

    जर (SDL_BYTESPERPIXEL(surface->format) <= आकार(Uint32) &&
        !SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_COLORSPACEPRIMARIES(surface->colorspace) == SDL_COLOR_PRIMARIES_BT709) {
        Uint8 r8, g8, b8, a8;

        जर (SDL_ReadSurfacePixel(surface, x, y, &r8, &g8, &b8, &a8)) {
            *r = (दशांश)r8 / 255.0f;
            *g = (दशांश)g8 / 255.0f;
            *b = (दशांश)b8 / 255.0f;
            *a = (दशांश)a8 / 255.0f;
            result = true;
        }
    } अन्यथा जर (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // FIXME: We need code to extract a single macroblock from a YUV surface
        SDL_Surface *converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        जर (converted) {
            result = SDL_ReadSurfacePixelFloat(converted, x, y, r, g, b, a);
            SDL_DestroySurface(converted);
        }
    } अन्यथा {
        // This is really slow, but it gets the job done
        दशांश rgba[4];
        Uint8 *p;

        जर (SDL_MUSTLOCK(surface)) {
            जर (!SDL_LockSurface(surface)) {
                परत false;
            }
        }

        p = (Uint8 *)surface->pixels + y * surface->pitch + x * SDL_BYTESPERPIXEL(surface->format);

        जर (surface->format == SDL_PIXELFORMAT_RGBA128_FLOAT) {
            SDL_memcpy(rgba, p, आकार(rgba));
            result = true;
        } अन्यथा {
            SDL_Colorspace src_colorspace = surface->colorspace;
            SDL_Colorspace dst_colorspace = (src_colorspace == SDL_COLORSPACE_SRGB_LINEAR ? SDL_COLORSPACE_SRGB_LINEAR : SDL_COLORSPACE_SRGB);

            जर (SDL_ConvertPixelsAndColorspace(1, 1, surface->format, src_colorspace, surface->props, p, surface->pitch, SDL_PIXELFORMAT_RGBA128_FLOAT, dst_colorspace, 0, rgba, आकार(rgba))) {
                result = true;
            }
        }

        जर (result) {
            *r = rgba[0];
            *g = rgba[1];
            *b = rgba[2];
            *a = rgba[3];
        }

        जर (SDL_MUSTLOCK(surface)) {
            SDL_UnlockSurface(surface);
        }
    }
    परत result;
}

bool SDL_WriteSurfacePixel(SDL_Surface *surface, पूर्णांक x, पूर्णांक y, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    Uint32 pixel = 0;
    माप_प्रकार bytes_per_pixel;
    Uint8 *p;
    bool result = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        परत SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        परत SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        परत SDL_InvalidParamError("y");
    }

    bytes_per_pixel = SDL_BYTESPERPIXEL(surface->format);

    जर (SDL_MUSTLOCK(surface)) {
        जर (!SDL_LockSurface(surface)) {
            परत false;
        }
    }

    p = (Uint8 *)surface->pixels + y * surface->pitch + x * bytes_per_pixel;

    जर (bytes_per_pixel <= आकार(pixel) && !SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        pixel = SDL_MapRGBA(surface->fmt, surface->palette, r, g, b, a);
#जर SDL_BYTEORDER == SDL_BIG_ENDIAN
        SDL_memcpy(p, ((Uint8 *)&pixel) + (आकार(pixel) - bytes_per_pixel), bytes_per_pixel);
#अन्यथा
        SDL_memcpy(p, &pixel, bytes_per_pixel);
#endif
        result = true;
    } अन्यथा जर (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        result = SDL_Unsupported();
    } अन्यथा {
        // This is really slow, but it gets the job done
        Uint8 rgba[4];

        rgba[0] = r;
        rgba[1] = g;
        rgba[2] = b;
        rgba[3] = a;
        result = SDL_ConvertPixelsAndColorspace(1, 1, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, rgba, आकार(rgba), surface->format, surface->colorspace, surface->props, p, surface->pitch);
    }

    जर (SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }
    परत result;
}

bool SDL_WriteSurfacePixelFloat(SDL_Surface *surface, पूर्णांक x, पूर्णांक y, दशांश r, दशांश g, दशांश b, दशांश a)
{
    bool result = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        परत SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        परत SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        परत SDL_InvalidParamError("y");
    }

    जर (SDL_BYTESPERPIXEL(surface->format) <= आकार(Uint32) && !SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        Uint8 r8, g8, b8, a8;

        r8 = (Uint8)SDL_round(SDL_clamp(r, 0.0f, 1.0f) * 255.0f);
        g8 = (Uint8)SDL_round(SDL_clamp(g, 0.0f, 1.0f) * 255.0f);
        b8 = (Uint8)SDL_round(SDL_clamp(b, 0.0f, 1.0f) * 255.0f);
        a8 = (Uint8)SDL_round(SDL_clamp(a, 0.0f, 1.0f) * 255.0f);
        जर (SDL_WriteSurfacePixel(surface, x, y, r8, g8, b8, a8)) {
            result = true;
        }
    } अन्यथा जर (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        result = SDL_Unsupported();
    } अन्यथा {
        // This is really slow, but it gets the job done
        दशांश rgba[4];
        Uint8 *p;

        जर (SDL_MUSTLOCK(surface)) {
            जर (!SDL_LockSurface(surface)) {
                परत false;
            }
        }

        p = (Uint8 *)surface->pixels + y * surface->pitch + x * SDL_BYTESPERPIXEL(surface->format);

        rgba[0] = r;
        rgba[1] = g;
        rgba[2] = b;
        rgba[3] = a;

        जर (surface->format == SDL_PIXELFORMAT_RGBA128_FLOAT) {
            SDL_memcpy(p, rgba, आकार(rgba));
            result = true;
        } अन्यथा {
            SDL_Colorspace dst_colorspace = surface->colorspace;
            SDL_Colorspace src_colorspace = (dst_colorspace == SDL_COLORSPACE_SRGB_LINEAR ? SDL_COLORSPACE_SRGB_LINEAR : SDL_COLORSPACE_SRGB);

            result = SDL_ConvertPixelsAndColorspace(1, 1, SDL_PIXELFORMAT_RGBA128_FLOAT, src_colorspace, 0, rgba, आकार(rgba), surface->format, dst_colorspace, surface->props, p, surface->pitch);
        }

        जर (SDL_MUSTLOCK(surface)) {
            SDL_UnlockSurface(surface);
        }
    }
    परत result;
}

/*
 * Free a surface created by the above function.
 */
शून्य SDL_DestroySurface(SDL_Surface *surface)
{
    जर (!SDL_SurfaceValid(surface)) {
        परत;
    }
    जर (surface->internal_flags & SDL_INTERNAL_SURFACE_DONTFREE) {
        परत;
    }
    जर (--surface->refcount > 0) {
        परत;
    }

    SDL_RemoveSurfaceAlternateImages(surface);

    SDL_DestroyProperties(surface->props);

    SDL_InvalidateMap(&surface->map);

    पर्यंत (surface->locked > 0) {
        SDL_UnlockSurface(surface);
    }
#ifdef SDL_HAVE_RLE
    जर (surface->internal_flags & SDL_INTERNAL_SURFACE_RLEACCEL) {
        SDL_UnRLESurface(surface);
    }
#endif
    SDL_SetSurfacePalette(surface, रिक्त);

    जर (surface->flags & SDL_SURFACE_PREALLOCATED) {
        // Don't free
    } अन्यथा जर (surface->flags & SDL_SURFACE_SIMD_ALIGNED) {
        // Free aligned
        SDL_aligned_free(surface->pixels);
    } अन्यथा {
        // Normal
        SDL_free(surface->pixels);
    }

    surface->reserved = रिक्त;

    जर (!(surface->internal_flags & SDL_INTERNAL_SURFACE_चळत)) {
        SDL_free(surface);
    }
}

SDL_Surface *SDL_LoadSurface_IO(SDL_IOStream *src, bool closeio)
{
    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        परत रिक्त;
    }

    जर (SDL_IsBMP(src)) {
        परत SDL_LoadBMP_IO(src, closeio);
    } अन्यथा जर (SDL_IsPNG(src)) {
        परत SDL_LoadPNG_IO(src, closeio);
    } अन्यथा जर (SDL_IsJPG(src)) {
        परत SDL_LoadJPG_IO(src, closeio);
    } अन्यथा {
        जर (closeio) {
            SDL_CloseIO(src);
        }
        SDL_SetError("Unsupported image format");
        परत रिक्त;
    }
}

SDL_Surface *SDL_LoadSurface(स्थिरांक अक्षर *file)
{
    SDL_IOStream *stream = SDL_IOFromFile(file, "rb");
    जर (!stream) {
        परत रिक्त;
    }

    परत SDL_LoadSurface_IO(stream, true);
}
