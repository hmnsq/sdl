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
#समावेश "SDL_internal.h"

#समावेश "SDL_sysvideo.h"
#समावेश "SDL_video_c.h"
#समावेश "SDL_RLEaccel_c.h"
#समावेश "SDL_pixels_c.h"
#समावेश "SDL_rotate.h"
#समावेश "SDL_stb_c.h"
#समावेश "SDL_yuv_c.h"
#समावेश "../render/SDL_sysrender.h"

#समावेश "SDL_surface_c.h"


// Check to make sure we can safely check multiplication of surface w and pitch and it won't overflow size_t
SDL_COMPILE_TIME_ASSERT(surface_आकार_assumptions,
                        माप(पूर्णांक) == माप(Sint32) && माप(माप_प्रकार) >= माप(Sint32));

SDL_COMPILE_TIME_ASSERT(can_indicate_overflow, SDL_आकार_MAX > SDL_MAX_SINT32);

// Magic!
अटल अक्षर SDL_surface_magic;

// Public routines

bool SDL_SurfaceValid(SDL_Surface *surface)
{
    वापस (surface && surface->reserved == &SDL_surface_magic);
}

व्योम SDL_UpdateSurfaceLockFlag(SDL_Surface *surface)
{
    // We need to mark the surface as needing unlock while locked
    अगर ((surface->flags & SDL_SURFACE_LOCKED) ||
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
अटल bool SDL_CalculateRGBSize(Uint32 format, माप_प्रकार width, माप_प्रकार height, माप_प्रकार *आकार, माप_प्रकार *pitch, bool minimal)
{
    अगर (SDL_BITSPERPIXEL(format) >= 8) {
        अगर (!SDL_आकार_mul_check_overflow(width, SDL_BYTESPERPIXEL(format), pitch)) {
            वापस SDL_SetError("width * bpp would overflow");
        }
    } अन्यथा {
        अगर (!SDL_आकार_mul_check_overflow(width, SDL_BITSPERPIXEL(format), pitch)) {
            वापस SDL_SetError("width * bpp would overflow");
        }
        अगर (!SDL_आकार_add_check_overflow(*pitch, 7, pitch)) {
            वापस SDL_SetError("aligning pitch would overflow");
        }
        *pitch /= 8;
    }
    अगर (!minimal) {
        // 4-byte aligning for speed
        अगर (!SDL_आकार_add_check_overflow(*pitch, 3, pitch)) {
            वापस SDL_SetError("aligning pitch would overflow");
        }
        *pitch &= ~3;
    }

    अगर (!SDL_आकार_mul_check_overflow(height, *pitch, आकार)) {
        वापस SDL_SetError("height * pitch would overflow");
    }

    वापस true;
}

bool SDL_Calculate_Surface_आकार(SDL_PixelFormat format, पूर्णांक width, पूर्णांक height, माप_प्रकार *आकार, माप_प्रकार *pitch, bool minimalPitch)
{
    माप_प्रकार p = 0, sz = 0;

    अगर (आकार) {
        *आकार = 0;
    }

    अगर (pitch) {
        *pitch = 0;
    }

    अगर (SDL_ISPIXELFORMAT_FOURCC(format)) {
        अगर (format == SDL_PIXELFORMAT_MJPG) {
            // We don't know in advance what it will be, we'll figure it out later.
            वापस true;
        }

        अगर (!SDL_CalculateYUVSize(format, width, height, &sz, &p)) {
            // Overflow...
            वापस false;
        }
    } अन्यथा {
        अगर (!SDL_CalculateRGBSize(format, width, height, &sz, &p, minimalPitch)) {
            // Overflow...
            वापस false;
        }
    }

    अगर (आकार) {
        *आकार = sz;
    }

    अगर (pitch) {
        *pitch = p;
    }

    वापस true;
}

अटल bool SDL_InitializeSurface(SDL_Surface *surface, पूर्णांक width, पूर्णांक height, SDL_PixelFormat format, SDL_Colorspace colorspace, SDL_PropertiesID props, व्योम *pixels, पूर्णांक pitch, bool onstack)
{
    SDL_zerop(surface);

    surface->flags = SDL_SURFACE_PREALLOCATED;
    surface->format = format;
    surface->w = width;
    surface->h = height;
    surface->pixels = pixels;
    surface->pitch = pitch;
    surface->reserved = &SDL_surface_magic;

    अगर (onstack) {
        surface->internal_flags |= SDL_INTERNAL_SURFACE_ढेर;
    }

    surface->fmt = SDL_GetPixelFormatDetails(format);
    अगर (!surface->fmt) {
        SDL_DestroySurface(surface);
        वापस false;
    }

    // Initialize the clip rect
    surface->clip_rect.w = width;
    surface->clip_rect.h = height;

    // Allocate an empty mapping
    surface->map.info.r = 0xFF;
    surface->map.info.g = 0xFF;
    surface->map.info.b = 0xFF;
    surface->map.info.a = 0xFF;

    अगर (colorspace == SDL_COLORSPACE_UNKNOWN) {
        surface->colorspace = SDL_GetDefaultColorspaceForFormat(format);
    } अन्यथा {
        surface->colorspace = colorspace;
    }

    अगर (props) {
        अगर (!SDL_CopyProperties(props, SDL_GetSurfaceProperties(surface))) {
            SDL_DestroySurface(surface);
            वापस false;
        }
    }

    // By default surfaces with an alpha mask are set up for blending
    अगर (SDL_ISPIXELFORMAT_ALPHA(surface->format)) {
        SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
    }

    // The surface is ready to go
    surface->refcount = 1;
    वापस true;
}

/*
 * Create an empty surface of the appropriate depth using the given format
 */
अटल SDL_Surface *SDL_CreateSurfaceInternal(पूर्णांक width, पूर्णांक height, SDL_PixelFormat format, bool clear_surface)
{
    माप_प्रकार pitch, आकार;
    SDL_Surface *surface;

    CHECK_PARAM(width < 0) {
        SDL_InvalidParamError("width");
        वापस शून्य;
    }

    CHECK_PARAM(height < 0) {
        SDL_InvalidParamError("height");
        वापस शून्य;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        वापस शून्य;
    }

    अगर (!SDL_Calculate_Surface_आकार(format, width, height, &आकार, &pitch, false /* not minimal pitch */)) {
        // Overflow...
        वापस शून्य;
    }

    // Allocate and initialize the surface
    surface = (SDL_Surface *)SDL_malloc(माप(*surface));
    अगर (!surface) {
        वापस शून्य;
    }

    अगर (!SDL_InitializeSurface(surface, width, height, format, SDL_COLORSPACE_UNKNOWN, 0, शून्य, (पूर्णांक)pitch, false)) {
        वापस शून्य;
    }

    अगर (surface->w && surface->h && format != SDL_PIXELFORMAT_MJPG) {
        surface->flags &= ~SDL_SURFACE_PREALLOCATED;
        अगर (SDL_GetHintBoolean("SDL_SURFACE_MALLOC", false)) {
            अगर (clear_surface) {
                surface->pixels = SDL_calloc(1, आकार);
            } अन्यथा {
                surface->pixels = SDL_malloc(आकार);
            }
        } अन्यथा {
            surface->flags |= SDL_SURFACE_SIMD_ALIGNED;
            अगर (clear_surface) {
                surface->pixels = SDL_aligned_alloc_zero(SDL_GetSIMDAlignment(), आकार);
            } अन्यथा {
                surface->pixels = SDL_aligned_alloc(SDL_GetSIMDAlignment(), आकार);
            }
        }
        अगर (!surface->pixels) {
            SDL_DestroySurface(surface);
            वापस शून्य;
        }
    }
    वापस surface;
}

SDL_Surface *SDL_CreateSurfaceZeroed(पूर्णांक width, पूर्णांक height, SDL_PixelFormat format)
{
    वापस SDL_CreateSurfaceInternal(width, height, format, true);
}

SDL_Surface *SDL_CreateSurfaceUninitialized(पूर्णांक width, पूर्णांक height, SDL_PixelFormat format)
{
    वापस SDL_CreateSurfaceInternal(width, height, format, false);
}

SDL_Surface *SDL_CreateSurface(पूर्णांक width, पूर्णांक height, SDL_PixelFormat format)
{
    वापस SDL_CreateSurfaceZeroed(width, height, format);
}


/*
 * Create an RGB surface from an existing memory buffer using the given
 * enum SDL_PIXELFORMAT_* format
 */
SDL_Surface *SDL_CreateSurfaceFrom(पूर्णांक width, पूर्णांक height, SDL_PixelFormat format, व्योम *pixels, पूर्णांक pitch)
{
    CHECK_PARAM(width < 0) {
        SDL_InvalidParamError("width");
        वापस शून्य;
    }

    CHECK_PARAM(height < 0) {
        SDL_InvalidParamError("height");
        वापस शून्य;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        वापस शून्य;
    }

    अगर (pitch == 0 && !pixels) {
        // The application will fill these in later with valid values
    } अन्यथा {
        माप_प्रकार minimalPitch;

        अगर (!SDL_Calculate_Surface_आकार(format, width, height, शून्य, &minimalPitch, true /* minimal pitch */)) {
            // Overflow...
            वापस शून्य;
        }

        CHECK_PARAM(pitch < 0 || (माप_प्रकार)pitch < minimalPitch) {
            SDL_InvalidParamError("pitch");
            वापस शून्य;
        }
    }

    // Allocate and initialize the surface
    SDL_Surface *surface = (SDL_Surface *)SDL_malloc(माप(*surface));
    अगर (!surface ||
        !SDL_InitializeSurface(surface, width, height, format, SDL_COLORSPACE_UNKNOWN, 0, pixels, pitch, false)) {
        वापस शून्य;
    }
    वापस surface;
}

SDL_PropertiesID SDL_GetSurfaceProperties(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        वापस 0;
    }

    अगर (!surface->props) {
        surface->props = SDL_CreateProperties();
    }
    वापस surface->props;
}

bool SDL_SetSurfaceColorspace(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        वापस SDL_InvalidParamError("surface");
    }

    surface->colorspace = colorspace;
    वापस true;
}

SDL_Colorspace SDL_GetSurfaceColorspace(SDL_Surface *surface)
{
    अगर (!SDL_SurfaceValid(surface)) {
        वापस SDL_COLORSPACE_UNKNOWN;
    }

    वापस surface->colorspace;
}

भग्न SDL_GetDefaultSDRWhitePoint(SDL_Colorspace colorspace)
{
    वापस SDL_GetSurfaceSDRWhitePoint(शून्य, colorspace);
}

भग्न SDL_GetSurfaceSDRWhitePoint(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    SDL_TransferCharacteristics transfer = SDL_COLORSPACETRANSFER(colorspace);

    अगर (transfer == SDL_TRANSFER_CHARACTERISTICS_LINEAR ||
        transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
        SDL_PropertiesID props;
        भग्न default_मूल्य = 1.0f;

        अगर (SDL_SurfaceValid(surface)) {
            props = surface->props;
        } अन्यथा {
            props = 0;
        }
        अगर (transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
            /* The older standards use an SDR white point of 100 nits.
             * ITU-R BT.2408-6 recommends using an SDR white point of 203 nits.
             * This is the default Chrome uses, and what a lot of game content
             * assumes, so we'll go with that.
             */
            स्थिर भग्न DEFAULT_PQ_SDR_WHITE_POINT = 203.0f;
            default_मूल्य = DEFAULT_PQ_SDR_WHITE_POINT;
        }
        वापस SDL_GetFloatProperty(props, SDL_PROP_SURFACE_SDR_WHITE_POINT_FLOAT, default_मूल्य);
    }
    वापस 1.0f;
}

भग्न SDL_GetDefaultHDRHeadroom(SDL_Colorspace colorspace)
{
    वापस SDL_GetSurfaceHDRHeadroom(शून्य, colorspace);
}

भग्न SDL_GetSurfaceHDRHeadroom(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    SDL_TransferCharacteristics transfer = SDL_COLORSPACETRANSFER(colorspace);

    अगर (transfer == SDL_TRANSFER_CHARACTERISTICS_LINEAR ||
        transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
        SDL_PropertiesID props;
        भग्न default_मूल्य = 0.0f;

        अगर (SDL_SurfaceValid(surface)) {
            props = surface->props;
        } अन्यथा {
            props = 0;
        }
        वापस SDL_GetFloatProperty(props, SDL_PROP_SURFACE_HDR_HEADROOM_FLOAT, default_मूल्य);
    }
    वापस 1.0f;
}

SDL_Palette *SDL_CreateSurfacePalette(SDL_Surface *surface)
{
    SDL_Palette *palette;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        वापस शून्य;
    }

    CHECK_PARAM(!SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        SDL_SetError("The surface is not indexed format");
        वापस शून्य;
    }

    palette = SDL_CreatePalette((1 << SDL_BITSPERPIXEL(surface->format)));
    अगर (!palette) {
        वापस शून्य;
    }

    अगर (palette->ncolors == 2) {
        // Create a black and white bitmap palette
        palette->colors[0].r = 0xFF;
        palette->colors[0].g = 0xFF;
        palette->colors[0].b = 0xFF;
        palette->colors[1].r = 0x00;
        palette->colors[1].g = 0x00;
        palette->colors[1].b = 0x00;
    }

    अगर (!SDL_SetSurfacePalette(surface, palette)) {
        SDL_DestroyPalette(palette);
        वापस शून्य;
    }

    // The surface has retained the palette, we can remove the reference here
    SDL_assert(palette->refcount == 2);
    SDL_DestroyPalette(palette);
    वापस palette;
}

bool SDL_SetSurfacePalette(SDL_Surface *surface, SDL_Palette *palette)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        वापस SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(palette && !SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        वापस SDL_SetError("Surface doesn't use a palette");
    }

    CHECK_PARAM(palette && palette->ncolors > (1 << SDL_BITSPERPIXEL(surface->format))) {
        वापस SDL_SetError("Palette doesn't match surface format");
    }

    अगर (palette != surface->palette) {
        अगर (surface->palette) {
            SDL_DestroyPalette(surface->palette);
        }

        surface->palette = palette;

        अगर (surface->palette) {
            ++surface->palette->refcount;
        }
    }

    SDL_InvalidateMap(&surface->map);

    वापस true;
}

SDL_Palette *SDL_GetSurfacePalette(SDL_Surface *surface)
{
    अगर (!SDL_SurfaceValid(surface)) {
        वापस शून्य;
    }

    वापस surface->palette;
}

bool SDL_AddSurfaceAlternateImage(SDL_Surface *surface, SDL_Surface *image)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        वापस SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(!SDL_SurfaceValid(image)) {
        वापस SDL_InvalidParamError("image");
    }

    SDL_Surface **images = (SDL_Surface **)SDL_realloc(surface->images, (surface->अंक_images + 1) * माप(*images));
    अगर (!images) {
        वापस false;
    }
    images[surface->अंक_images] = image;
    surface->images = images;
    ++surface->अंक_images;
    ++image->refcount;
    वापस true;
}

bool SDL_SurfaceHasAlternateImages(SDL_Surface *surface)
{
    अगर (!SDL_SurfaceValid(surface)) {
        वापस false;
    }

    वापस (surface->अंक_images > 0);
}

SDL_Surface **SDL_GetSurfaceImages(SDL_Surface *surface, पूर्णांक *गिनती)
{
    अगर (गिनती) {
        *गिनती = 0;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        वापस शून्य;
    }

    पूर्णांक अंक_images = 1 + surface->अंक_images;
    SDL_Surface **images = (SDL_Surface **)SDL_malloc((अंक_images + 1) * माप(*images));
    अगर (!images) {
        वापस शून्य;
    }
    images[0] = surface;
    अगर (surface->अंक_images > 0) {
        SDL_memcpy(&images[1], surface->images, (surface->अंक_images * माप(images[1])));
    }
    images[अंक_images] = शून्य;

    अगर (गिनती) {
        *गिनती = अंक_images;
    }
    वापस images;
}

SDL_Surface *SDL_GetSurfaceImage(SDL_Surface *surface, भग्न display_scale)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        वापस शून्य;
    }

    अगर (!SDL_SurfaceHasAlternateImages(surface)) {
        ++surface->refcount;
        वापस surface;
    }

    // This surface has high DPI images, pick the best one available, or scale one to the correct size
    SDL_Surface **images = SDL_GetSurfaceImages(surface, शून्य);
    अगर (!images) {
        // Failure, fall back to the existing surface
        ++surface->refcount;
        वापस surface;
    }

    // Find closest image. Images that are larger than the
    // desired size are preferred over images that are smaller.
    SDL_Surface *closest = शून्य;
    पूर्णांक desired_w = (पूर्णांक)SDL_round(surface->w * display_scale);
    पूर्णांक desired_h = (पूर्णांक)SDL_round(surface->h * display_scale);
    पूर्णांक desired_आकार = desired_w * desired_h;
    पूर्णांक closest_distance = -1;
    पूर्णांक closest_आकार = -1;
    क्रम (पूर्णांक i = 0; images[i]; ++i) {
        SDL_Surface *candidate = images[i];
        पूर्णांक आकार = candidate->w * candidate->h;
        पूर्णांक delta_w = (candidate->w - desired_w);
        पूर्णांक delta_h = (candidate->h - desired_h);
        पूर्णांक distance = (delta_w * delta_w) + (delta_h * delta_h);
        अगर (closest_distance < 0 || distance < closest_distance ||
            (आकार > desired_आकार && closest_आकार < desired_आकार)) {
            closest = candidate;
            closest_distance = distance;
            closest_आकार = आकार;
        }
    }
    SDL_free(images);
    SDL_assert(closest != शून्य);    // We should always have at least one surface

    अगर (closest->w == desired_w && closest->h == desired_h) {
        ++closest->refcount;
        वापस closest;
    }

    // We need to scale the image to the correct size. To maintain good image quality, downscaling
    // is done in steps, never reducing the width and height by more than half each time.
    SDL_Surface *scaled = closest;
    करो {
        पूर्णांक अग्र_scaled_w = SDL_max(desired_w, (scaled->w + 1) / 2);
        पूर्णांक अग्र_scaled_h = SDL_max(desired_h, (scaled->h + 1) / 2);
        SDL_Surface *अग्र_scaled = SDL_ScaleSurface(scaled, अग्र_scaled_w, अग्र_scaled_h, SDL_SCALEMODE_LINEAR);
        अगर (scaled != closest) {
            SDL_DestroySurface(scaled);
        }
        scaled = अग्र_scaled;
        अगर (!scaled) {
            // Failure, fall back to the closest surface
            ++closest->refcount;
            वापस closest;
        }
    } जबतक (scaled->w != desired_w || scaled->h != desired_h);

    वापस scaled;
}

व्योम SDL_RemoveSurfaceAlternateImages(SDL_Surface *surface)
{
    अगर (!SDL_SurfaceValid(surface)) {
        वापस;
    }

    अगर (surface->अंक_images > 0) {
        क्रम (पूर्णांक i = 0; i < surface->अंक_images; ++i) {
            SDL_DestroySurface(surface->images[i]);
        }
        SDL_free(surface->images);
        surface->images = शून्य;
        surface->अंक_images = 0;
    }
}

bool SDL_SetSurfaceRLE(SDL_Surface *surface, bool enabled)
{
    पूर्णांक flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        वापस SDL_InvalidParamError("surface");
    }

    flags = surface->map.info.flags;
    अगर (enabled) {
        surface->map.info.flags |= SDL_COPY_RLE_DESIRED;
    } अन्यथा {
        surface->map.info.flags &= ~SDL_COPY_RLE_DESIRED;
    }
    अगर (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    वापस true;
}

bool SDL_SurfaceHasRLE(SDL_Surface *surface)
{
    अगर (!SDL_SurfaceValid(surface)) {
        वापस false;
    }

    अगर (!(surface->map.info.flags & SDL_COPY_RLE_DESIRED)) {
        वापस false;
    }

    वापस true;
}

bool SDL_Set_Surface_Color_कुंजी(SDL_Surface *surface, bool enabled, Uint32 कुंजी)
{
    पूर्णांक flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        वापस SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(surface->palette && कुंजी >= ((Uint32)surface->palette->ncolors)) {
        वापस SDL_InvalidParamError("key");
    }

    flags = surface->map.info.flags;
    अगर (enabled) {
        surface->map.info.flags |= SDL_COPY_COLORKEY;
        surface->map.info.colorkey = कुंजी;
    } अन्यथा {
        surface->map.info.flags &= ~SDL_COPY_COLORKEY;
    }
    अगर (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }

    वापस true;
}

bool SDL_Surface_Has_Color_कुंजी(SDL_Surface *surface)
{
    अगर (!SDL_SurfaceValid(surface)) {
        वापस false;
    }

    अगर (!(surface->map.info.flags & SDL_COPY_COLORKEY)) {
        वापस false;
    }

    वापस true;
}

bool SDL_Get_Surface_Color_कुंजी(SDL_Surface *surface, Uint32 *कुंजी)
{
    अगर (कुंजी) {
        *कुंजी = 0;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        वापस SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(!(surface->map.info.flags & SDL_COPY_COLORKEY)) {
        वापस SDL_SetError("Surface doesn't have a colorkey");
    }

    अगर (कुंजी) {
        *कुंजी = surface->map.info.colorkey;
    }
    वापस true;
}

/* This is a fairly slow function to switch from colorkey to alpha
   NB: it doesn't handle bpp 1 or 3, because they have no alpha channel */
अटल व्योम SDL_ConvertColorkeyToAlpha(SDL_Surface *surface, bool ignore_alpha)
{
    पूर्णांक x, y, bpp;

    अगर (!SDL_SurfaceValid(surface)) {
        वापस;
    }

    अगर (!(surface->map.info.flags & SDL_COPY_COLORKEY) ||
        !SDL_ISPIXELFORMAT_ALPHA(surface->format)) {
        वापस;
    }

    bpp = SDL_BYTESPERPIXEL(surface->format);

    SDL_LockSurface(surface);

    अगर (bpp == 2) {
        Uint16 *row, *spot;
        Uint16 ckey = (Uint16)surface->map.info.colorkey;
        Uint16 mask = (Uint16)(~surface->fmt->Amask);

        // Ignore, or not, alpha in colorkey comparison
        अगर (ignore_alpha) {
            ckey &= mask;
            row = (Uint16 *)surface->pixels;
            क्रम (y = surface->h; y--;) {
                spot = row;
                क्रम (x = surface->w; x--;) {
                    अगर ((*spot & mask) == ckey) {
                        *spot &= mask;
                    }
                    ++spot;
                }
                row += surface->pitch / 2;
            }
        } अन्यथा {
            row = (Uint16 *)surface->pixels;
            क्रम (y = surface->h; y--;) {
                spot = row;
                क्रम (x = surface->w; x--;) {
                    अगर (*spot == ckey) {
                        *spot &= mask;
                    }
                    ++spot;
                }
                row += surface->pitch / 2;
            }
        }
    } अन्यथा अगर (bpp == 4) {
        Uint32 *row, *spot;
        Uint32 ckey = surface->map.info.colorkey;
        Uint32 mask = ~surface->fmt->Amask;

        // Ignore, or not, alpha in colorkey comparison
        अगर (ignore_alpha) {
            ckey &= mask;
            row = (Uint32 *)surface->pixels;
            क्रम (y = surface->h; y--;) {
                spot = row;
                क्रम (x = surface->w; x--;) {
                    अगर ((*spot & mask) == ckey) {
                        *spot &= mask;
                    }
                    ++spot;
                }
                row += surface->pitch / 4;
            }
        } अन्यथा {
            row = (Uint32 *)surface->pixels;
            क्रम (y = surface->h; y--;) {
                spot = row;
                क्रम (x = surface->w; x--;) {
                    अगर (*spot == ckey) {
                        *spot &= mask;
                    }
                    ++spot;
                }
                row += surface->pitch / 4;
            }
        }
    }

    SDL_UnlockSurface(surface);

    SDL_Set_Surface_Color_कुंजी(surface, false, 0);
    SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
}

bool SDL_SetSurfaceColorMod(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b)
{
    पूर्णांक flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        वापस SDL_InvalidParamError("surface");
    }

    surface->map.info.r = r;
    surface->map.info.g = g;
    surface->map.info.b = b;

    flags = surface->map.info.flags;
    अगर (r != 0xFF || g != 0xFF || b != 0xFF) {
        surface->map.info.flags |= SDL_COPY_MODULATE_COLOR;
    } अन्यथा {
        surface->map.info.flags &= ~SDL_COPY_MODULATE_COLOR;
    }
    अगर (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    वापस true;
}

bool SDL_GetSurfaceColorMod(SDL_Surface *surface, Uint8 *r, Uint8 *g, Uint8 *b)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        अगर (r) {
            *r = 255;
        }
        अगर (g) {
            *g = 255;
        }
        अगर (b) {
            *b = 255;
        }
        वापस SDL_InvalidParamError("surface");
    }

    अगर (r) {
        *r = surface->map.info.r;
    }
    अगर (g) {
        *g = surface->map.info.g;
    }
    अगर (b) {
        *b = surface->map.info.b;
    }
    वापस true;
}

bool SDL_SetSurfaceAlphaMod(SDL_Surface *surface, Uint8 alpha)
{
    पूर्णांक flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        वापस SDL_InvalidParamError("surface");
    }

    surface->map.info.a = alpha;

    flags = surface->map.info.flags;
    अगर (alpha != 0xFF) {
        surface->map.info.flags |= SDL_COPY_MODULATE_ALPHA;
    } अन्यथा {
        surface->map.info.flags &= ~SDL_COPY_MODULATE_ALPHA;
    }
    अगर (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    वापस true;
}

bool SDL_GetSurfaceAlphaMod(SDL_Surface *surface, Uint8 *alpha)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        अगर (alpha) {
            *alpha = 255;
        }
        वापस SDL_InvalidParamError("surface");
    }

    अगर (alpha) {
        *alpha = surface->map.info.a;
    }
    वापस true;
}

bool SDL_SetSurfaceBlendMode(SDL_Surface *surface, SDL_BlendMode blendMode)
{
    पूर्णांक flags;
    bool परिणाम = true;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        वापस SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(blendMode == SDL_BLENDMODE_INVALID) {
        वापस SDL_InvalidParamError("blendMode");
    }

    flags = surface->map.info.flags;
    surface->map.info.flags &= ~SDL_COPY_BLEND_MASK;
    चयन (blendMode) {
    हाल SDL_BLENDMODE_NONE:
        अवरोध;
    हाल SDL_BLENDMODE_BLEND:
        surface->map.info.flags |= SDL_COPY_BLEND;
        अवरोध;
    हाल SDL_BLENDMODE_BLEND_PREMULTIPLIED:
        surface->map.info.flags |= SDL_COPY_BLEND_PREMULTIPLIED;
        अवरोध;
    हाल SDL_BLENDMODE_ADD:
        surface->map.info.flags |= SDL_COPY_ADD;
        अवरोध;
    हाल SDL_BLENDMODE_ADD_PREMULTIPLIED:
        surface->map.info.flags |= SDL_COPY_ADD_PREMULTIPLIED;
        अवरोध;
    हाल SDL_BLENDMODE_MOD:
        surface->map.info.flags |= SDL_COPY_MOD;
        अवरोध;
    हाल SDL_BLENDMODE_MUL:
        surface->map.info.flags |= SDL_COPY_MUL;
        अवरोध;
    शेष:
        परिणाम = SDL_Unsupported();
        अवरोध;
    }

    अगर (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }

    वापस परिणाम;
}

bool SDL_GetSurfaceBlendMode(SDL_Surface *surface, SDL_BlendMode *blendMode)
{
    अगर (blendMode) {
        *blendMode = SDL_BLENDMODE_INVALID;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        वापस SDL_InvalidParamError("surface");
    }

    अगर (!blendMode) {
        वापस true;
    }

    चयन (surface->map.info.flags & SDL_COPY_BLEND_MASK) {
    हाल SDL_COPY_BLEND:
        *blendMode = SDL_BLENDMODE_BLEND;
        अवरोध;
    हाल SDL_COPY_BLEND_PREMULTIPLIED:
        *blendMode = SDL_BLENDMODE_BLEND_PREMULTIPLIED;
        अवरोध;
    हाल SDL_COPY_ADD:
        *blendMode = SDL_BLENDMODE_ADD;
        अवरोध;
    हाल SDL_COPY_ADD_PREMULTIPLIED:
        *blendMode = SDL_BLENDMODE_ADD_PREMULTIPLIED;
        अवरोध;
    हाल SDL_COPY_MOD:
        *blendMode = SDL_BLENDMODE_MOD;
        अवरोध;
    हाल SDL_COPY_MUL:
        *blendMode = SDL_BLENDMODE_MUL;
        अवरोध;
    शेष:
        *blendMode = SDL_BLENDMODE_NONE;
        अवरोध;
    }
    वापस true;
}

bool SDL_SetSurfaceClipRect(SDL_Surface *surface, स्थिर SDL_Rect *rect)
{
    SDL_Rect full_rect;

    // Don't do anything if there's no surface to act on
    अगर (!SDL_SurfaceValid(surface)) {
        वापस false;
    }

    // Set up the full surface rectangle
    full_rect.x = 0;
    full_rect.y = 0;
    full_rect.w = surface->w;
    full_rect.h = surface->h;

    // Set the clipping rectangle
    अगर (!rect) {
        surface->clip_rect = full_rect;
        वापस true;
    }
    वापस SDL_GetRectIntersection(rect, &full_rect, &surface->clip_rect);
}

bool SDL_GetSurfaceClipRect(SDL_Surface *surface, SDL_Rect *rect)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        अगर (rect) {
            SDL_zerop(rect);
        }
        वापस SDL_InvalidParamError("surface");
    }
    CHECK_PARAM(!rect) {
        वापस SDL_InvalidParamError("rect");
    }
    *rect = surface->clip_rect;
    वापस true;
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
bool SDL_BlitSurfaceUnchecked(SDL_Surface *src, स्थिर SDL_Rect *srcrect,
                             SDL_Surface *dst, स्थिर SDL_Rect *dstrect)
{
    // Check to make sure the blit mapping is valid
    अगर (!SDL_ValidateMap(src, dst)) {
        वापस false;
    }
    वापस src->map.blit(src, srcrect, dst, dstrect);
}

bool SDL_BlitSurface(SDL_Surface *src, स्थिर SDL_Rect *srcrect, SDL_Surface *dst, स्थिर SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src) || (!src->pixels && !SDL_MUSTLOCK(src))) {
        वापस SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst) || (!dst->pixels && !SDL_MUSTLOCK(dst))) {
        वापस SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        वापस SDL_SetError("Surfaces must not be locked during blit");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    अगर (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
    } अन्यथा {
        r_dst.x = 0;
        r_dst.y = 0;
    }

    // clip the source rectangle to the source surface
    अगर (srcrect) {
        SDL_Rect tmp;
        अगर (SDL_GetRectIntersection(srcrect, &r_src, &tmp) == false) {
            वापस true;
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
        अगर (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &tmp) == false) {
            वापस true;
        }

        // Shift srcrect, if dstrect has changed
        r_src.x += tmp.x - r_dst.x;
        r_src.y += tmp.y - r_dst.y;
        r_src.w = tmp.w;
        r_src.h = tmp.h;

        // Update dstrect
        r_dst = tmp;
    }

    अगर (r_dst.w <= 0 || r_dst.h <= 0) {
        // No-op.
        वापस true;
    }

    // Switch back to a fast blit if we were previously stretching
    अगर (src->map.info.flags & SDL_COPY_NEAREST) {
        src->map.info.flags &= ~SDL_COPY_NEAREST;
        SDL_InvalidateMap(&src->map);
    }

    वापस SDL_BlitSurfaceUnchecked(src, &r_src, dst, &r_dst);
}

अटल bool SDL_BlitSurfaceClippedScaled(SDL_Surface *src, स्थिर SDL_Rect *srcrect, SDL_Surface *dst, स्थिर SDL_Rect *dstrect, SDL_ScaleMode scaleMode)
{
    // We need to scale first, then blit into dst because we're clipping in the destination surface pixel coordinates
    bool परिणाम;
    पूर्णांक saved_w = src->w;
    पूर्णांक saved_h = src->h;
    व्योम *saved_pixels = src->pixels;
    src->w = srcrect->w;
    src->h = srcrect->h;
    src->pixels = (Uint8 *)src->pixels + srcrect->y * src->pitch + srcrect->x * SDL_BYTESPERPIXEL(src->format);
    SDL_Surface *scaled = SDL_ScaleSurface(src, dstrect->w, dstrect->h, scaleMode);
    अगर (scaled) {
        परिणाम = SDL_BlitSurface(scaled, शून्य, dst, dstrect);
        SDL_DestroySurface(scaled);
    } अन्यथा {
        परिणाम = false;
    }
    src->w = saved_w;
    src->h = saved_h;
    src->pixels = saved_pixels;
    वापस परिणाम;
}

bool SDL_BlitSurfaceScaled(SDL_Surface *src, स्थिर SDL_Rect *srcrect, SDL_Surface *dst, स्थिर SDL_Rect *dstrect, SDL_ScaleMode scaleMode)
{
    SDL_Rect r_src, r_dst;
    bool परिणाम;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src) || (!src->pixels && !SDL_MUSTLOCK(src))) {
        वापस SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst) || (!dst->pixels && !SDL_MUSTLOCK(dst))) {
        वापस SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        वापस SDL_SetError("Surfaces must not be locked during blit");
    }

    चयन (scaleMode) {
    हाल SDL_SCALEMODE_NEAREST:
        अवरोध;
    हाल SDL_SCALEMODE_LINEAR:
        अवरोध;
    हाल SDL_SCALEMODE_PIXELART:
        scaleMode = SDL_SCALEMODE_NEAREST;
        अवरोध;
    शेष:
        वापस SDL_InvalidParamError("scaleMode");
    }

    पूर्णांक src_w = srcrect ? srcrect->w : src->w;
    पूर्णांक src_h = srcrect ? srcrect->h : src->h;
    पूर्णांक dst_w = dstrect ? dstrect->w : dst->w;
    पूर्णांक dst_h = dstrect ? dstrect->h : dst->h;
    अगर (src_w == dst_w && src_h == dst_h) {
        // No scaling, defer to regular blit
        वापस SDL_BlitSurface(src, srcrect, dst, dstrect);
    }

    अगर (src->w == 0 || src->h == 0) {
        // Nothing to do
        वापस true;
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    अगर (dstrect) {
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
    अगर (srcrect) {
        SDL_Rect desired, tmp;
        desired.x = srcrect->x;
        desired.y = srcrect->y;
        desired.w = SDL_max(srcrect->w, 1);
        desired.h = SDL_max(srcrect->h, 1);
        अगर (SDL_GetRectIntersection(&desired, &r_src, &tmp) == false) {
            वापस true;
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
    अगर (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &tmp) == false) {
        वापस true;
    }

    अगर (tmp.x != r_dst.x || tmp.y != r_dst.y || tmp.w != r_dst.w || tmp.h != r_dst.h) {
        // Need to do a clipped and scaled blit
        वापस SDL_BlitSurfaceClippedScaled(src, &r_src, dst, &r_dst, scaleMode);
    }

    अगर (SDL_MUSTLOCK(src)) {
        अगर (!SDL_LockSurface(src)) {
            वापस false;
        }
    }
    अगर (SDL_MUSTLOCK(dst)) {
        अगर (!SDL_LockSurface(dst)) {
            अगर (SDL_MUSTLOCK(src)) {
                SDL_UnlockSurface(src);
            }
            वापस false;
        }
    }

    परिणाम = SDL_BlitSurfaceUncheckedScaled(src, &r_src, dst, &r_dst, scaleMode);

    अगर (SDL_MUSTLOCK(src)) {
        SDL_UnlockSurface(src);
    }
    अगर (SDL_MUSTLOCK(dst)) {
        SDL_UnlockSurface(dst);
    }
    वापस परिणाम;
}

/**
 *  This is a semi-private blit function and it performs low-level surface
 *  scaled blitting only.
 */
bool SDL_BlitSurfaceUncheckedScaled(SDL_Surface *src, स्थिर SDL_Rect *srcrect, SDL_Surface *dst, स्थिर SDL_Rect *dstrect, SDL_ScaleMode scaleMode)
{
    अटल स्थिर Uint32 complex_copy_flags = (SDL_COPY_MODULATE_MASK | SDL_COPY_BLEND_MASK | SDL_COPY_COLORKEY);

    अगर (srcrect->w > SDL_MAX_UINT16 || srcrect->h > SDL_MAX_UINT16 ||
        dstrect->w > SDL_MAX_UINT16 || dstrect->h > SDL_MAX_UINT16) {
        वापस SDL_SetError("Size too large for scaling");
    }

    अगर (!(src->map.info.flags & SDL_COPY_NEAREST)) {
        src->map.info.flags |= SDL_COPY_NEAREST;
        SDL_InvalidateMap(&src->map);
    }

    अगर (scaleMode == SDL_SCALEMODE_NEAREST || scaleMode == SDL_SCALEMODE_PIXELART) {
        अगर (!(src->map.info.flags & complex_copy_flags) &&
            src->format == dst->format &&
            (!SDL_ISPIXELFORMAT_INDEXED(src->format) ||
             (SDL_BITSPERPIXEL(src->format) == 8 && SDL_IsSamePalette(src->palette, dst->palette))) &&
            SDL_BYTESPERPIXEL(src->format) <= 4) {
            वापस SDL_StretchSurface(src, srcrect, dst, dstrect, SDL_SCALEMODE_NEAREST);
        } अन्यथा अगर (SDL_BITSPERPIXEL(src->format) < 8) {
            // Scaling bitmap not yet supported, convert to RGBA for blit
            bool परिणाम = false;
            SDL_Surface *tmp = SDL_ConvertSurface(src, SDL_PIXELFORMAT_ARGB8888);
            अगर (tmp) {
                परिणाम = SDL_BlitSurfaceUncheckedScaled(tmp, srcrect, dst, dstrect, SDL_SCALEMODE_NEAREST);
                SDL_DestroySurface(tmp);
            }
            वापस परिणाम;
        } अन्यथा {
            वापस SDL_BlitSurfaceUnchecked(src, srcrect, dst, dstrect);
        }
    } अन्यथा {
        अगर (!(src->map.info.flags & complex_copy_flags) &&
            src->format == dst->format &&
            !SDL_ISPIXELFORMAT_INDEXED(src->format) &&
            SDL_BYTESPERPIXEL(src->format) == 4 &&
            src->format != SDL_PIXELFORMAT_ARGB2101010) {
            // fast path
            वापस SDL_StretchSurface(src, srcrect, dst, dstrect, SDL_SCALEMODE_LINEAR);
        } अन्यथा अगर (SDL_BITSPERPIXEL(src->format) < 8) {
            // Scaling bitmap not yet supported, convert to RGBA for blit
            bool परिणाम = false;
            SDL_Surface *tmp = SDL_ConvertSurface(src, SDL_PIXELFORMAT_ARGB8888);
            अगर (tmp) {
                परिणाम = SDL_BlitSurfaceUncheckedScaled(tmp, srcrect, dst, dstrect, scaleMode);
                SDL_DestroySurface(tmp);
            }
            वापस परिणाम;
        } अन्यथा {
            // Use intermediate surface(s)
            SDL_Surface *tmp1 = शून्य;
            bool परिणाम;
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
            अगर (SDL_BYTESPERPIXEL(src->format) != 4 || src->format == SDL_PIXELFORMAT_ARGB2101010) {
                SDL_PixelFormat fmt;
                अगर (SDL_BYTESPERPIXEL(dst->format) == 4 && dst->format != SDL_PIXELFORMAT_ARGB2101010 &&
                    (SDL_ISPIXELFORMAT_ALPHA(dst->format) || !is_complex_copy_flags)) {
                    fmt = dst->format;
                } अन्यथा {
                    fmt = SDL_PIXELFORMAT_ARGB8888;
                }
                tmp1 = SDL_ConvertSurfaceRect(src, srcrect, fmt);
                अगर (!tmp1) {
                    वापस false;
                }
                src = tmp1;
                srcrect2.x = 0;
                srcrect2.y = 0;
            }

            // Intermediate scaling
            अगर (is_complex_copy_flags || src->format != dst->format) {
                SDL_Rect tmprect;
                SDL_Surface *tmp2 = SDL_CreateSurfaceUninitialized(dstrect->w, dstrect->h, src->format);
                SDL_StretchSurface(src, &srcrect2, tmp2, शून्य, SDL_SCALEMODE_LINEAR);

                SDL_SetSurfaceColorMod(tmp2, r, g, b);
                SDL_SetSurfaceAlphaMod(tmp2, alpha);
                SDL_SetSurfaceBlendMode(tmp2, blendMode);

                tmprect.x = 0;
                tmprect.y = 0;
                tmprect.w = dstrect->w;
                tmprect.h = dstrect->h;
                परिणाम = SDL_BlitSurfaceUnchecked(tmp2, &tmprect, dst, dstrect);
                SDL_DestroySurface(tmp2);
            } अन्यथा {
                परिणाम = SDL_StretchSurface(src, &srcrect2, dst, dstrect, SDL_SCALEMODE_LINEAR);
            }

            SDL_DestroySurface(tmp1);
            वापस परिणाम;
        }
    }
}

bool SDL_BlitSurfaceTiled(SDL_Surface *src, स्थिर SDL_Rect *srcrect, SDL_Surface *dst, स्थिर SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        वापस SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        वापस SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        वापस SDL_SetError("Surfaces must not be locked during blit");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    अगर (dstrect) {
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
    अगर (srcrect) {
        अगर (SDL_GetRectIntersection(srcrect, &r_src, &r_src) == false) {
            वापस true;
        }

        // For tiling we don't adjust the destination rectangle
    }

    // clip the destination rectangle against the clip rectangle
    {
        अगर (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &r_dst) == false) {
            वापस true;
        }

        // For tiling we don't adjust the source rectangle
    }

    // Switch back to a fast blit if we were previously stretching
    अगर (src->map.info.flags & SDL_COPY_NEAREST) {
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
    क्रम (पूर्णांक y = 0; y < rows; ++y) {
        curr_dst.x = r_dst.x;
        क्रम (पूर्णांक x = 0; x < cols; ++x) {
            अगर (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                वापस false;
            }
            curr_dst.x += curr_dst.w;
        }
        अगर (remaining_w) {
            curr_src.w = remaining_w;
            curr_dst.w = remaining_w;
            अगर (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                वापस false;
            }
            curr_src.w = r_src.w;
            curr_dst.w = r_src.w;
        }
        curr_dst.y += curr_dst.h;
    }
    अगर (remaining_h) {
        curr_src.h = remaining_h;
        curr_dst.h = remaining_h;
        curr_dst.x = r_dst.x;
        क्रम (पूर्णांक x = 0; x < cols; ++x) {
            अगर (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                वापस false;
            }
            curr_dst.x += curr_dst.w;
        }
        अगर (remaining_w) {
            curr_src.w = remaining_w;
            curr_dst.w = remaining_w;
            अगर (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                वापस false;
            }
        }
    }
    वापस true;
}

bool SDL_BlitSurfaceTiledWithScale(SDL_Surface *src, स्थिर SDL_Rect *srcrect, भग्न scale, SDL_ScaleMode scaleMode, SDL_Surface *dst, स्थिर SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        वापस SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        वापस SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        वापस SDL_SetError("Surfaces must not be locked during blit");
    }
    CHECK_PARAM(scale < 0.0f) {
        वापस SDL_InvalidParamError("scale");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    अगर (dstrect) {
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
    अगर (srcrect) {
        अगर (SDL_GetRectIntersection(srcrect, &r_src, &r_src) == false) {
            वापस true;
        }

        // For tiling we don't adjust the destination rectangle
    }

    // clip the destination rectangle against the clip rectangle
    {
        अगर (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &r_dst) == false) {
            वापस true;
        }

        // For tiling we don't adjust the source rectangle
    }

    // Switch back to a fast blit if we were previously stretching
    अगर (src->map.info.flags & SDL_COPY_NEAREST) {
        src->map.info.flags &= ~SDL_COPY_NEAREST;
        SDL_InvalidateMap(&src->map);
    }

    पूर्णांक tile_width = (पूर्णांक)SDL_roundf(r_src.w * scale);
    पूर्णांक tile_height = (पूर्णांक)SDL_roundf(r_src.h * scale);
    अगर (tile_width <= 0 || tile_height <= 0) {
        // Nothing to do
        वापस true;
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
    क्रम (पूर्णांक y = 0; y < rows; ++y) {
        curr_dst.x = r_dst.x;
        क्रम (पूर्णांक x = 0; x < cols; ++x) {
            अगर (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
                वापस false;
            }
            curr_dst.x += curr_dst.w;
        }
        अगर (remaining_dst_w > 0) {
            curr_src.w = remaining_src_w;
            curr_dst.w = remaining_dst_w;
            अगर (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
                वापस false;
            }
            curr_src.w = r_src.w;
            curr_dst.w = tile_width;
        }
        curr_dst.y += curr_dst.h;
    }
    अगर (remaining_dst_h > 0) {
        curr_src.h = remaining_src_h;
        curr_dst.h = remaining_dst_h;
        curr_dst.x = r_dst.x;
        क्रम (पूर्णांक x = 0; x < cols; ++x) {
            अगर (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
                वापस false;
            }
            curr_dst.x += curr_dst.w;
        }
        अगर (remaining_dst_w > 0) {
            curr_src.w = remaining_src_w;
            curr_dst.w = remaining_dst_w;
            अगर (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
                वापस false;
            }
        }
    }
    वापस true;
}

bool SDL_BlitSurface9Grid(SDL_Surface *src, स्थिर SDL_Rect *srcrect, पूर्णांक बायाँ_width, पूर्णांक दायाँ_width, पूर्णांक शीर्ष_height, पूर्णांक bottom_height, भग्न scale, SDL_ScaleMode scaleMode, SDL_Surface *dst, स्थिर SDL_Rect *dstrect)
{
    SDL_Rect full_src, full_dst;
    SDL_Rect curr_src, curr_dst;
    पूर्णांक dst_बायाँ_width;
    पूर्णांक dst_दायाँ_width;
    पूर्णांक dst_शीर्ष_height;
    पूर्णांक dst_bottom_height;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        वापस SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        वापस SDL_InvalidParamError("dst");
    }

    अगर (!srcrect) {
        full_src.x = 0;
        full_src.y = 0;
        full_src.w = src->w;
        full_src.h = src->h;
        srcrect = &full_src;
    }

    अगर (!dstrect) {
        full_dst.x = 0;
        full_dst.y = 0;
        full_dst.w = dst->w;
        full_dst.h = dst->h;
        dstrect = &full_dst;
    }

    अगर (scale <= 0.0f || scale == 1.0f) {
        dst_बायाँ_width = बायाँ_width;
        dst_दायाँ_width = दायाँ_width;
        dst_शीर्ष_height = शीर्ष_height;
        dst_bottom_height = bottom_height;
    } अन्यथा {
        dst_बायाँ_width = (पूर्णांक)SDL_roundf(बायाँ_width * scale);
        dst_दायाँ_width = (पूर्णांक)SDL_roundf(दायाँ_width * scale);
        dst_शीर्ष_height = (पूर्णांक)SDL_roundf(शीर्ष_height * scale);
        dst_bottom_height = (पूर्णांक)SDL_roundf(bottom_height * scale);
    }

    // Upper-left corner
    curr_src.x = srcrect->x;
    curr_src.y = srcrect->y;
    curr_src.w = बायाँ_width;
    curr_src.h = शीर्ष_height;
    curr_dst.x = dstrect->x;
    curr_dst.y = dstrect->y;
    curr_dst.w = dst_बायाँ_width;
    curr_dst.h = dst_शीर्ष_height;
    अगर (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        वापस false;
    }

    // Upper-right corner
    curr_src.x = srcrect->x + srcrect->w - दायाँ_width;
    curr_src.w = दायाँ_width;
    curr_dst.x = dstrect->x + dstrect->w - dst_दायाँ_width;
    curr_dst.w = dst_दायाँ_width;
    अगर (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        वापस false;
    }

    // Lower-right corner
    curr_src.y = srcrect->y + srcrect->h - bottom_height;
    curr_dst.y = dstrect->y + dstrect->h - dst_bottom_height;
    curr_dst.h = dst_bottom_height;
    अगर (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        वापस false;
    }

    // Lower-left corner
    curr_src.x = srcrect->x;
    curr_src.w = बायाँ_width;
    curr_dst.x = dstrect->x;
    curr_dst.w = dst_बायाँ_width;
    अगर (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        वापस false;
    }

    //बायाँ
    curr_src.y = srcrect->y + शीर्ष_height;
    curr_src.h = srcrect->h - शीर्ष_height - bottom_height;
    curr_dst.y = dstrect->y + dst_शीर्ष_height;
    curr_dst.h = dstrect->h - dst_शीर्ष_height - dst_bottom_height;
    अगर (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        वापस false;
    }

    //दायाँ
    curr_src.x = srcrect->x + srcrect->w - दायाँ_width;
    curr_src.w = दायाँ_width;
    curr_dst.x = dstrect->x + dstrect->w - dst_दायाँ_width;
    curr_dst.w = dst_दायाँ_width;
    अगर (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        वापस false;
    }

    //शीर्ष
    curr_src.x = srcrect->x + बायाँ_width;
    curr_src.y = srcrect->y;
    curr_src.w = srcrect->w - बायाँ_width - दायाँ_width;
    curr_src.h = शीर्ष_height;
    curr_dst.x = dstrect->x + dst_बायाँ_width;
    curr_dst.y = dstrect->y;
    curr_dst.w = dstrect->w - dst_बायाँ_width - dst_दायाँ_width;
    curr_dst.h = dst_शीर्ष_height;
    अगर (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        वापस false;
    }

    // Bottom
    curr_src.y = srcrect->y + srcrect->h - bottom_height;
    curr_dst.y = dstrect->y + dstrect->h - dst_bottom_height;
    curr_dst.h = dst_bottom_height;
    अगर (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        वापस false;
    }

    // Center
    curr_src.x = srcrect->x + बायाँ_width;
    curr_src.y = srcrect->y + शीर्ष_height;
    curr_src.w = srcrect->w - बायाँ_width - दायाँ_width;
    curr_src.h = srcrect->h - शीर्ष_height - bottom_height;
    curr_dst.x = dstrect->x + dst_बायाँ_width;
    curr_dst.y = dstrect->y + dst_शीर्ष_height;
    curr_dst.w = dstrect->w - dst_बायाँ_width - dst_दायाँ_width;
    curr_dst.h = dstrect->h - dst_शीर्ष_height - dst_bottom_height;
    अगर (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        वापस false;
    }

    वापस true;
}

/*
 * Lock a surface to directly access the pixels
 */
bool SDL_LockSurface(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        वापस SDL_InvalidParamError("surface");
    }

    अगर (!surface->locked) {
#अगर_घोषित SDL_HAVE_RLE
        // Perform the lock
        अगर (surface->internal_flags & SDL_INTERNAL_SURFACE_RLEACCEL) {
            SDL_UnRLESurface(surface);
        }
#पूर्ण_अगर
    }

    // Increment the surface lock count, for recursive locks
    ++surface->locked;
    surface->flags |= SDL_SURFACE_LOCKED;
    SDL_UpdateSurfaceLockFlag(surface);

    // Ready to go..
    वापस true;
}

/*
 * Unlock a previously locked surface
 */
व्योम SDL_UnlockSurface(SDL_Surface *surface)
{
    अगर (!SDL_SurfaceValid(surface)) {
        वापस;
    }

    // Only perform an unlock if we are locked
    अगर (!surface->locked || (--surface->locked > 0)) {
        वापस;
    }

    surface->flags &= ~SDL_SURFACE_LOCKED;
    SDL_UpdateSurfaceLockFlag(surface);
}

अटल bool SDL_FlipSurfaceHorizontal(SDL_Surface *surface)
{
    bool isstack;
    Uint8 *row, *a, *b, *tmp;
    पूर्णांक i, j, bpp;

    अगर (SDL_BITSPERPIXEL(surface->format) < 8) {
        // We could implement this if needed, but we'd have to flip sets of bits within a byte
        वापस SDL_Unsupported();
    }

    अगर (surface->h <= 0) {
        वापस true;
    }

    अगर (surface->w <= 1) {
        वापस true;
    }

    bpp = SDL_BYTESPERPIXEL(surface->format);
    row = (Uint8 *)surface->pixels;
    tmp = SDL_small_alloc(Uint8, surface->pitch, &isstack);
    अगर (!tmp) {
        वापस false;
    }
    क्रम (i = surface->h; i--; ) {
        a = row;
        b = a + (surface->w - 1) * bpp;
        क्रम (j = surface->w / 2; j--; ) {
            SDL_memcpy(tmp, a, bpp);
            SDL_memcpy(a, b, bpp);
            SDL_memcpy(b, tmp, bpp);
            a += bpp;
            b -= bpp;
        }
        row += surface->pitch;
    }
    SDL_small_free(tmp, isstack);
    वापस true;
}

अटल bool SDL_FlipSurfaceVertical(SDL_Surface *surface)
{
    bool isstack;
    Uint8 *a, *b, *tmp;
    पूर्णांक i;

    अगर (surface->h <= 1) {
        वापस true;
    }

    a = (Uint8 *)surface->pixels;
    b = a + (surface->h - 1) * surface->pitch;
    tmp = SDL_small_alloc(Uint8, surface->pitch, &isstack);
    अगर (!tmp) {
        वापस false;
    }
    क्रम (i = surface->h / 2; i--; ) {
        SDL_memcpy(tmp, a, surface->pitch);
        SDL_memcpy(a, b, surface->pitch);
        SDL_memcpy(b, tmp, surface->pitch);
        a += surface->pitch;
        b -= surface->pitch;
    }
    SDL_small_free(tmp, isstack);
    वापस true;
}

bool SDL_FlipSurface(SDL_Surface *surface, SDL_FlipMode flip)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        वापस SDL_InvalidParamError("surface");
    }
    अगर (!surface->pixels) {
        वापस true;
    }

    bool परिणाम = true;
    चयन (flip) {
    हाल SDL_FLIP_HORIZONTAL:
        परिणाम = SDL_FlipSurfaceHorizontal(surface);
        अवरोध;
    हाल SDL_FLIP_VERTICAL:
        परिणाम = SDL_FlipSurfaceVertical(surface);
        अवरोध;
    हाल SDL_FLIP_HORIZONTAL_AND_VERTICAL:
        परिणाम &= SDL_FlipSurfaceHorizontal(surface);
        परिणाम &= SDL_FlipSurfaceVertical(surface);
        अवरोध;
    शेष:
        परिणाम = SDL_InvalidParamError("flip");
        अवरोध;
    }
    वापस परिणाम;
}

अटल SDL_Surface *SDL_ConvertSurfaceRectAndColorspace(SDL_Surface *surface, स्थिर SDL_Rect *rect, SDL_PixelFormat format, SDL_Palette *palette, SDL_Colorspace colorspace, SDL_PropertiesID props)
{
    SDL_Palette *अस्थायी_palette = शून्य;
    SDL_Surface *convert = शून्य;
    SDL_Colorspace src_colorspace;
    SDL_PropertiesID src_properties;
    Uint32 copy_flags;
    SDL_Color copy_color;
    SDL_Rect bounds;
    bool परिणाम;
    bool palette_ck_transform = false;
    Uint8 palette_ck_मूल्य = 0;
    Uint8 *palette_saved_alpha = शून्य;
    पूर्णांक palette_saved_alpha_ncolors = 0;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        जाओ error;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        जाओ error;
    }

    // Set the bounds of the new surface
    bounds.x = 0;
    bounds.y = 0;
    bounds.w = surface->w;
    bounds.h = surface->h;
    अगर (rect) {
        bounds.w = rect->w;
        bounds.h = rect->h;
    } अन्यथा {
        rect = &bounds;
    }

    // Check for empty destination palette! (results in empty image)
    अगर (palette) {
        पूर्णांक i;
        क्रम (i = 0; i < palette->ncolors; ++i) {
            अगर ((palette->colors[i].r != 0xFF) || (palette->colors[i].g != 0xFF) || (palette->colors[i].b != 0xFF)) {
                अवरोध;
            }
        }
        अगर (i == palette->ncolors) {
            SDL_SetError("Empty destination palette");
            जाओ error;
        }
    } अन्यथा अगर (SDL_ISPIXELFORMAT_INDEXED(format)) {
        // Create a dither palette for conversion
        अस्थायी_palette = SDL_CreatePalette(1 << SDL_BITSPERPIXEL(format));
        अगर (अस्थायी_palette) {
            SDL_DitherPalette(अस्थायी_palette);
            palette = अस्थायी_palette;
        }
    }

    src_colorspace = surface->colorspace;
    src_properties = surface->props;

    // Create a new surface with the desired format
    अगर (surface->pixels || SDL_MUSTLOCK(surface)) {
        convert = SDL_CreateSurfaceUninitialized(rect->w, rect->h, format);
    } अन्यथा {
        convert = SDL_CreateSurfaceFrom(rect->w, rect->h, format, शून्य, 0);
    }
    अगर (!convert) {
        जाओ error;
    }
    अगर (SDL_ISPIXELFORMAT_INDEXED(format)) {
        SDL_SetSurfacePalette(convert, palette);
    }

    अगर (colorspace == SDL_COLORSPACE_UNKNOWN) {
        colorspace = src_colorspace;
    }
    SDL_SetSurfaceColorspace(convert, colorspace);

    अगर (SDL_ISPIXELFORMAT_FOURCC(format) || SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        अगर (surface->format == SDL_PIXELFORMAT_MJPG && format == SDL_PIXELFORMAT_MJPG) {
            // Just do a straight pixel copy of the JPEG image
            माप_प्रकार आकार = (माप_प्रकार)surface->pitch;
            convert->pixels = SDL_malloc(आकार);
            अगर (!convert->pixels) {
                जाओ error;
            }
            convert->flags &= ~SDL_SURFACE_PREALLOCATED;
            convert->pitch = surface->pitch;
            SDL_memcpy(convert->pixels, surface->pixels, आकार);

        } अन्यथा अगर (!SDL_ConvertPixelsAndColorspace(surface->w, surface->h, surface->format, src_colorspace, src_properties, surface->pixels, surface->pitch, convert->format, colorspace, props, convert->pixels, convert->pitch)) {
            जाओ error;
        }

        // Save the original copy flags
        copy_flags = surface->map.info.flags;

        जाओ end;
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
    अगर (surface->palette && SDL_ISPIXELFORMAT_ALPHA(format)) {
        bool set_opaque = false;

        bool is_opaque, has_alpha_channel;
        SDL_DetectPalette(surface->palette, &is_opaque, &has_alpha_channel);

        अगर (is_opaque) {
            अगर (!has_alpha_channel) {
                set_opaque = true;
            }
        }

        // Set opaque and backup palette alpha values
        अगर (set_opaque) {
            पूर्णांक i;
            palette_saved_alpha_ncolors = surface->palette->ncolors;
            अगर (palette_saved_alpha_ncolors > 0) {
                palette_saved_alpha = SDL_ढेर_alloc(Uint8, palette_saved_alpha_ncolors);
                क्रम (i = 0; i < palette_saved_alpha_ncolors; i++) {
                    palette_saved_alpha[i] = surface->palette->colors[i].a;
                    surface->palette->colors[i].a = SDL_ALPHA_OPAQUE;
                }
            }
        }
    }

    // Transform colorkey to alpha. for cases where source palette has duplicate values, and colorkey is one of them
    अगर (copy_flags & SDL_COPY_COLORKEY) {
        अगर (surface->palette && !palette) {
            palette_ck_transform = true;
            palette_ck_मूल्य = surface->palette->colors[surface->map.info.colorkey].a;
            surface->palette->colors[surface->map.info.colorkey].a = SDL_ALPHA_TRANSPARENT;
        }
    }

    अगर (surface->pixels || SDL_MUSTLOCK(surface)) {
        परिणाम = SDL_BlitSurfaceUnchecked(surface, rect, convert, &bounds);
    } अन्यथा {
        परिणाम = true;
    }

    // Restore colorkey alpha value
    अगर (palette_ck_transform) {
        surface->palette->colors[surface->map.info.colorkey].a = palette_ck_मूल्य;
    }

    // Restore palette alpha values
    अगर (palette_saved_alpha) {
        पूर्णांक i;
        क्रम (i = 0; i < palette_saved_alpha_ncolors; i++) {
            surface->palette->colors[i].a = palette_saved_alpha[i];
        }
        SDL_ढेर_free(palette_saved_alpha);
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
    अगर (!परिणाम) {
        जाओ error;
    }

    अगर (copy_flags & SDL_COPY_COLORKEY) {
        bool set_colorkey_by_color = false;
        bool convert_colorkey = true;

        अगर (surface->palette) {
            अगर (palette &&
                surface->palette->ncolors <= palette->ncolors &&
                (SDL_memcmp(surface->palette->colors, palette->colors,
                            surface->palette->ncolors * माप(SDL_Color)) == 0)) {
                // The palette is identical, just set the same colorkey
                SDL_Set_Surface_Color_कुंजी(convert, true, surface->map.info.colorkey);
            } अन्यथा अगर (!palette) {
                अगर (SDL_ISPIXELFORMAT_ALPHA(format)) {
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

        अगर (set_colorkey_by_color) {
            SDL_Surface *tmp;
            SDL_Surface *tmp2;
            पूर्णांक converted_colorkey = 0;

            // Create a dummy surface to get the colorkey converted
            tmp = SDL_CreateSurfaceUninitialized(1, 1, surface->format);
            अगर (!tmp) {
                जाओ error;
            }

            // Share the palette, if any
            अगर (surface->palette) {
                SDL_SetSurfacePalette(tmp, surface->palette);
            }

            SDL_FillSurfaceRect(tmp, शून्य, surface->map.info.colorkey);

            tmp->map.info.flags &= ~SDL_COPY_COLORKEY;

            // Conversion of the colorkey
            tmp2 = SDL_ConvertSurfaceAndColorspace(tmp, format, palette, colorspace, props);
            अगर (!tmp2) {
                SDL_DestroySurface(tmp);
                जाओ error;
            }

            // Get the converted colorkey
            SDL_memcpy(&converted_colorkey, tmp2->pixels, tmp2->fmt->bytes_per_pixel);

            SDL_DestroySurface(tmp);
            SDL_DestroySurface(tmp2);

            // Set the converted colorkey on the new surface
            SDL_Set_Surface_Color_कुंजी(convert, true, converted_colorkey);

            // This is needed when converting for 3D texture upload
            अगर (convert_colorkey) {
                SDL_ConvertColorkeyToAlpha(convert, true);
            }
        }
    }

end:
    अगर (अस्थायी_palette) {
        SDL_DestroyPalette(अस्थायी_palette);
    }

    SDL_SetSurfaceClipRect(convert, &surface->clip_rect);

    /* Enable alpha blending by default if the new surface has an
     * alpha channel or alpha modulation */
    अगर (SDL_ISPIXELFORMAT_ALPHA(format) ||
        (copy_flags & SDL_COPY_MODULATE_ALPHA)) {
        SDL_SetSurfaceBlendMode(convert, SDL_BLENDMODE_BLEND);
    }
    अगर (copy_flags & SDL_COPY_RLE_DESIRED) {
        SDL_SetSurfaceRLE(convert, true);
    }

    // Copy alternate images
    क्रम (पूर्णांक i = 0; i < surface->अंक_images; ++i) {
        अगर (!SDL_AddSurfaceAlternateImage(convert, surface->images[i])) {
            जाओ error;
        }
    }

    // Copy properties
    अगर (surface->props) {
        अगर (!SDL_CopyProperties(surface->props, SDL_GetSurfaceProperties(convert))) {
            जाओ error;
        }

        // Make sure the new surface doesn't reference an old SDL2 surface.
        SDL_ClearProperty(SDL_GetSurfaceProperties(convert), "sdl2-compat.surface2");
    }

    // We're ready to go!
    वापस convert;

error:
    अगर (अस्थायी_palette) {
        SDL_DestroyPalette(अस्थायी_palette);
    }
    अगर (convert) {
        SDL_DestroySurface(convert);
    }
    वापस शून्य;
}

SDL_Surface *SDL_ConvertSurfaceAndColorspace(SDL_Surface *surface, SDL_PixelFormat format, SDL_Palette *palette, SDL_Colorspace colorspace, SDL_PropertiesID props)
{
    वापस SDL_ConvertSurfaceRectAndColorspace(surface, शून्य, format, palette, colorspace, props);
}

SDL_Surface *SDL_RotateSurface(SDL_Surface *surface, भग्न angle)
{
    SDL_Surface *rotated = शून्य;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        वापस शून्य;
    }

    SDL_Rect rect_dest;
    द्विगुन cangle, sangle;
    SDL_FPoint center = { surface->w * 0.5f, surface->h * 0.5f };
    SDLgfx_rotozoom_Surface_आकार_Trig(surface->w, surface->h, angle, &center, &rect_dest, &cangle, &sangle);

    // This function requires a 32-bit surface or 8-bit surface with a colorkey
    अगर ((SDL_BITSPERPIXEL(surface->format) == 32 && SDL_PIXELLAYOUT(surface->format) == SDL_PACKEDLAYOUT_8888) ||
        (surface->format == SDL_PIXELFORMAT_INDEX8 && SDL_Surface_Has_Color_कुंजी(surface))) {
        rotated = SDLgfx_rotateSurface(surface, angle, 1, 0, 0, &rect_dest, cangle, sangle, &center);
    } अन्यथा {
        SDL_Surface *convert = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);
        अगर (convert) {
            SDL_Surface *tmp = SDLgfx_rotateSurface(convert, angle, 1, 0, 0, &rect_dest, cangle, sangle, &center);
            अगर (tmp) {
                rotated = SDL_ConvertSurfaceAndColorspace(tmp, surface->format, surface->palette, surface->colorspace, surface->props);
                SDL_DestroySurface(tmp);
            }
            SDL_DestroySurface(convert);
        }
    }

    अगर (rotated) {
        अगर (SDL_HasProperty(surface->props, SDL_PROP_SURFACE_ROTATION_FLOAT)) {
            स्थिर भग्न rotation = (SDL_Get_संख्या_Property(surface->props, SDL_PROP_SURFACE_ROTATION_FLOAT, 0) - angle);
            SDL_SetFloatProperty(SDL_GetSurfaceProperties(rotated), SDL_PROP_SURFACE_ROTATION_FLOAT, rotation);
        }
    }

    वापस rotated;
}

SDL_Surface *SDL_DuplicateSurface(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        वापस शून्य;
    }

    वापस SDL_ConvertSurfaceAndColorspace(surface, surface->format, surface->palette, surface->colorspace, surface->props);
}

SDL_Surface *SDL_ScaleSurface(SDL_Surface *surface, पूर्णांक width, पूर्णांक height, SDL_ScaleMode scaleMode)
{
    SDL_Surface *convert = शून्य;
    Uint32 copy_flags;
    SDL_Color copy_color;
    bool rc;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        जाओ error;
    }

    अगर (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // We can't directly scale a YUV surface (yet!)
        SDL_Surface *tmp = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        अगर (!tmp) {
            वापस शून्य;
        }

        SDL_Surface *scaled = SDL_ScaleSurface(tmp, width, height, scaleMode);
        SDL_DestroySurface(tmp);
        अगर (!scaled) {
            वापस शून्य;
        }

        SDL_Surface *परिणाम = SDL_ConvertSurfaceAndColorspace(scaled, surface->format, शून्य, surface->colorspace, surface->props);
        SDL_DestroySurface(scaled);
        वापस परिणाम;
    }

    अगर (SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        // Linear scaling requires conversion to RGBA and then slow pixel color lookup
        scaleMode = SDL_SCALEMODE_NEAREST;
    }

    // Create a new surface with the desired size
    अगर (surface->pixels || SDL_MUSTLOCK(surface)) {
        convert = SDL_CreateSurfaceUninitialized(width, height, surface->format);
    } अन्यथा {
        convert = SDL_CreateSurfaceFrom(width, height, surface->format, शून्य, 0);
    }
    अगर (!convert) {
        जाओ error;
    }
    SDL_SetSurfacePalette(convert, surface->palette);
    SDL_SetSurfaceColorspace(convert, surface->colorspace);
    SDL_SetSurfaceRLE(convert, SDL_SurfaceHasRLE(surface));

    अगर (surface->pixels || SDL_MUSTLOCK(surface)) {
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

        rc = SDL_BlitSurfaceScaled(surface, शून्य, convert, शून्य, scaleMode);

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
    अगर (!rc) {
        जाओ error;
    }

    // We're ready to go!
    वापस convert;

error:
    अगर (convert) {
        SDL_DestroySurface(convert);
    }
    वापस शून्य;
}

SDL_Surface *SDL_ConvertSurfaceRect(SDL_Surface *surface, स्थिर SDL_Rect *rect, SDL_PixelFormat format)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        वापस शून्य;
    }

    वापस SDL_ConvertSurfaceRectAndColorspace(surface, rect, format, शून्य, SDL_GetDefaultColorspaceForFormat(format), surface->props);
}

SDL_Surface *SDL_ConvertSurface(SDL_Surface *surface, SDL_PixelFormat format)
{
    वापस SDL_ConvertSurfaceRect(surface, शून्य, format);
}

SDL_Surface *SDL_DuplicatePixels(पूर्णांक width, पूर्णांक height, SDL_PixelFormat format, SDL_Colorspace colorspace, व्योम *pixels, पूर्णांक pitch)
{
    SDL_Surface *surface;
    अगर (pixels) {
        surface = SDL_CreateSurfaceUninitialized(width, height, format);
    } अन्यथा {
        surface = SDL_CreateSurfaceFrom(width, height, format, शून्य, 0);
    }
    अगर (!surface) {
        वापस शून्य;
    }
    SDL_SetSurfaceColorspace(surface, colorspace);

    अगर (surface->pixels) {
        पूर्णांक लंबाई = width * SDL_BYTESPERPIXEL(format);
        Uint8 *src = (Uint8 *)pixels;
        Uint8 *dst = (Uint8 *)surface->pixels;
        पूर्णांक rows = height;
        जबतक (rows--) {
            SDL_memcpy(dst, src, लंबाई);
            dst += surface->pitch;
            src += pitch;
        }
    }
    वापस surface;
}

bool SDL_ConvertPixelsAndColorspace(पूर्णांक width, पूर्णांक height,
                      SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, स्थिर व्योम *src, पूर्णांक src_pitch,
                      SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, व्योम *dst, पूर्णांक dst_pitch)
{
    SDL_Surface src_surface;
    SDL_Surface dst_surface;
    SDL_Rect rect;
    व्योम *nonconst_src = (व्योम *)src;
    bool परिणाम;

    CHECK_PARAM(!src) {
        वापस SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!src_pitch) {
        वापस SDL_InvalidParamError("src_pitch");
    }
    CHECK_PARAM(!dst) {
        वापस SDL_InvalidParamError("dst");
    }
    CHECK_PARAM(!dst_pitch) {
        वापस SDL_InvalidParamError("dst_pitch");
    }

    अगर (src_colorspace == SDL_COLORSPACE_UNKNOWN) {
        src_colorspace = SDL_GetDefaultColorspaceForFormat(src_format);
    }
    अगर (dst_colorspace == SDL_COLORSPACE_UNKNOWN) {
        dst_colorspace = SDL_GetDefaultColorspaceForFormat(dst_format);
    }

    अगर (src_format == SDL_PIXELFORMAT_MJPG) {
        वापस SDL_ConvertPixels_STB(width, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    }

#अगर_घोषित SDL_HAVE_YUV
    अगर (SDL_ISPIXELFORMAT_FOURCC(src_format) && SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        वापस SDL_ConvertPixels_YUV_to_YUV(width, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } अन्यथा अगर (SDL_ISPIXELFORMAT_FOURCC(src_format)) {
        वापस SDL_ConvertPixels_YUV_to_RGB(width, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } अन्यथा अगर (SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        वापस SDL_ConvertPixels_RGB_to_YUV(width, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    }
#अन्यथा
    अगर (SDL_ISPIXELFORMAT_FOURCC(src_format) || SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        वापस SDL_SetError("SDL not built with YUV support");
    }
#पूर्ण_अगर

    // Fast path for same format copy
    अगर (src_format == dst_format && src_colorspace == dst_colorspace) {
        अगर (src_pitch == dst_pitch) {
            SDL_memcpy(dst, src, height * src_pitch);
        } अन्यथा {
            पूर्णांक i;
            स्थिर पूर्णांक bpp = SDL_BYTESPERPIXEL(src_format);
            width *= bpp;
            क्रम (i = height; i--;) {
                SDL_memcpy(dst, src, width);
                src = (स्थिर Uint8 *)src + src_pitch;
                dst = (Uint8 *)dst + dst_pitch;
            }
        }
        वापस true;
    }

    अगर (!SDL_InitializeSurface(&src_surface, width, height, src_format, src_colorspace, src_properties, nonconst_src, src_pitch, true)) {
        वापस false;
    }
    SDL_SetSurfaceBlendMode(&src_surface, SDL_BLENDMODE_NONE);

    अगर (!SDL_InitializeSurface(&dst_surface, width, height, dst_format, dst_colorspace, dst_properties, dst, dst_pitch, true)) {
        वापस false;
    }

    // Set up the rect and go!
    rect.x = 0;
    rect.y = 0;
    rect.w = width;
    rect.h = height;
    परिणाम = SDL_BlitSurfaceUnchecked(&src_surface, &rect, &dst_surface, &rect);

    SDL_DestroySurface(&src_surface);
    SDL_DestroySurface(&dst_surface);

    वापस परिणाम;
}

bool SDL_ConvertPixels(पूर्णांक width, पूर्णांक height, SDL_PixelFormat src_format, स्थिर व्योम *src, पूर्णांक src_pitch, SDL_PixelFormat dst_format, व्योम *dst, पूर्णांक dst_pitch)
{
    वापस SDL_ConvertPixelsAndColorspace(width, height,
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

अटल व्योम SDL_PremultiplyAlpha_AXYZ8888(पूर्णांक width, पूर्णांक height, स्थिर व्योम *src, पूर्णांक src_pitch, व्योम *dst, पूर्णांक dst_pitch)
{
    पूर्णांक c;
    Uint32 srcpixel;
    Uint32 srcR, srcG, srcB, srcA;
    Uint32 dstpixel;
    Uint32 dstR, dstG, dstB, dstA;

    जबतक (height--) {
        स्थिर Uint32 *src_px = (स्थिर Uint32 *)src;
        Uint32 *dst_px = (Uint32 *)dst;
        क्रम (c = width; c; --c) {
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
        src = (स्थिर Uint8 *)src + src_pitch;
        dst = (Uint8 *)dst + dst_pitch;
    }
}

अटल व्योम SDL_PremultiplyAlpha_XYZA8888(पूर्णांक width, पूर्णांक height, स्थिर व्योम *src, पूर्णांक src_pitch, व्योम *dst, पूर्णांक dst_pitch)
{
    पूर्णांक c;
    Uint32 srcpixel;
    Uint32 srcR, srcG, srcB, srcA;
    Uint32 dstpixel;
    Uint32 dstR, dstG, dstB, dstA;

    जबतक (height--) {
        स्थिर Uint32 *src_px = (स्थिर Uint32 *)src;
        Uint32 *dst_px = (Uint32 *)dst;
        क्रम (c = width; c; --c) {
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
        src = (स्थिर Uint8 *)src + src_pitch;
        dst = (Uint8 *)dst + dst_pitch;
    }
}

अटल व्योम SDL_PremultiplyAlpha_AXYZ128(पूर्णांक width, पूर्णांक height, स्थिर व्योम *src, पूर्णांक src_pitch, व्योम *dst, पूर्णांक dst_pitch)
{
    पूर्णांक c;
    भग्न flR, flG, flB, flA;

    जबतक (height--) {
        स्थिर भग्न *src_px = (स्थिर भग्न *)src;
        भग्न *dst_px = (भग्न *)dst;
        क्रम (c = width; c; --c) {
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
        src = (स्थिर Uint8 *)src + src_pitch;
        dst = (Uint8 *)dst + dst_pitch;
    }
}

अटल bool SDL_PremultiplyAlphaPixelsAndColorspace(पूर्णांक width, पूर्णांक height, SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, स्थिर व्योम *src, पूर्णांक src_pitch, SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, व्योम *dst, पूर्णांक dst_pitch, bool linear)
{
    SDL_Surface *convert = शून्य;
    व्योम *final_dst = dst;
    पूर्णांक final_dst_pitch = dst_pitch;
    SDL_PixelFormat format;
    SDL_Colorspace colorspace;
    bool परिणाम = false;

    CHECK_PARAM(!src) {
        वापस SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!src_pitch) {
        वापस SDL_InvalidParamError("src_pitch");
    }
    CHECK_PARAM(!dst) {
        वापस SDL_InvalidParamError("dst");
    }
    CHECK_PARAM(!dst_pitch) {
        वापस SDL_InvalidParamError("dst_pitch");
    }

    // Use a high precision format if we're converting to linear colorspace or using high precision pixel formats
    अगर (linear ||
        SDL_ISPIXELFORMAT_10BIT(src_format) || SDL_BITSPERPIXEL(src_format) > 32 ||
        SDL_ISPIXELFORMAT_10BIT(dst_format) || SDL_BITSPERPIXEL(dst_format) > 32) {
        अगर (src_format == SDL_PIXELFORMAT_ARGB128_FLOAT ||
            src_format == SDL_PIXELFORMAT_ABGR128_FLOAT) {
            format = src_format;
        } अन्यथा {
            format = SDL_PIXELFORMAT_ARGB128_FLOAT;
        }
    } अन्यथा {
        अगर (src_format == SDL_PIXELFORMAT_ARGB8888 ||
            src_format == SDL_PIXELFORMAT_ABGR8888 ||
            src_format == SDL_PIXELFORMAT_RGBA8888 ||
            src_format == SDL_PIXELFORMAT_BGRA8888) {
            format = src_format;
        } अन्यथा {
            format = SDL_PIXELFORMAT_ARGB8888;
        }
    }
    अगर (linear) {
        colorspace = SDL_COLORSPACE_SRGB_LINEAR;
    } अन्यथा {
        colorspace = SDL_COLORSPACE_SRGB;
    }

    अगर (src_format != format || src_colorspace != colorspace) {
        convert = SDL_CreateSurfaceUninitialized(width, height, format);
        अगर (!convert) {
            जाओ done;
        }
        अगर (!SDL_ConvertPixelsAndColorspace(width, height, src_format, src_colorspace, src_properties, src, src_pitch, format, colorspace, 0, convert->pixels, convert->pitch)) {
            जाओ done;
        }

        src = convert->pixels;
        src_pitch = convert->pitch;
        dst = convert->pixels;
        dst_pitch = convert->pitch;

    } अन्यथा अगर (dst_format != format || dst_colorspace != colorspace) {
        convert = SDL_CreateSurfaceUninitialized(width, height, format);
        अगर (!convert) {
            जाओ done;
        }
        dst = convert->pixels;
        dst_pitch = convert->pitch;
    }

    चयन (format) {
    हाल SDL_PIXELFORMAT_ARGB8888:
    हाल SDL_PIXELFORMAT_ABGR8888:
        SDL_PremultiplyAlpha_AXYZ8888(width, height, src, src_pitch, dst, dst_pitch);
        अवरोध;
    हाल SDL_PIXELFORMAT_RGBA8888:
    हाल SDL_PIXELFORMAT_BGRA8888:
        SDL_PremultiplyAlpha_XYZA8888(width, height, src, src_pitch, dst, dst_pitch);
        अवरोध;
    हाल SDL_PIXELFORMAT_ARGB128_FLOAT:
    हाल SDL_PIXELFORMAT_ABGR128_FLOAT:
        SDL_PremultiplyAlpha_AXYZ128(width, height, src, src_pitch, dst, dst_pitch);
        अवरोध;
    शेष:
        SDL_SetError("Unexpected internal pixel format");
        जाओ done;
    }

    अगर (dst != final_dst) {
        अगर (!SDL_ConvertPixelsAndColorspace(width, height, format, colorspace, 0, convert->pixels, convert->pitch, dst_format, dst_colorspace, dst_properties, final_dst, final_dst_pitch)) {
            जाओ done;
        }
    }
    परिणाम = true;

done:
    अगर (convert) {
        SDL_DestroySurface(convert);
    }
    वापस परिणाम;
}

bool SDL_PremultiplyAlpha(पूर्णांक width, पूर्णांक height,
                         SDL_PixelFormat src_format, स्थिर व्योम *src, पूर्णांक src_pitch,
                         SDL_PixelFormat dst_format, व्योम *dst, पूर्णांक dst_pitch, bool linear)
{
    SDL_Colorspace src_colorspace = SDL_GetDefaultColorspaceForFormat(src_format);
    SDL_Colorspace dst_colorspace = SDL_GetDefaultColorspaceForFormat(dst_format);

    वापस SDL_PremultiplyAlphaPixelsAndColorspace(width, height, src_format, src_colorspace, 0, src, src_pitch, dst_format, dst_colorspace, 0, dst, dst_pitch, linear);
}

bool SDL_PremultiplySurfaceAlpha(SDL_Surface *surface, bool linear)
{
    SDL_Colorspace colorspace;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        वापस SDL_InvalidParamError("surface");
    }

    colorspace = surface->colorspace;

    वापस SDL_PremultiplyAlphaPixelsAndColorspace(surface->w, surface->h, surface->format, colorspace, surface->props, surface->pixels, surface->pitch, surface->format, colorspace, surface->props, surface->pixels, surface->pitch, linear);
}

bool SDL_ClearSurface(SDL_Surface *surface, भग्न r, भग्न g, भग्न b, भग्न a)
{
    SDL_Rect clip_rect;
    bool परिणाम = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        वापस SDL_InvalidParamError("surface");
    }

    SDL_GetSurfaceClipRect(surface, &clip_rect);
    SDL_SetSurfaceClipRect(surface, शून्य);

    अगर (!SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_BYTESPERPIXEL(surface->format) <= माप(Uint32)) {
        Uint32 color;

        color = SDL_MapSurfaceRGBA(surface,
                    (Uint8)SDL_roundf(SDL_clamp(r, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(g, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(b, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(a, 0.0f, 1.0f) * 255.0f));
        परिणाम = SDL_FillSurfaceRect(surface, शून्य, color);
    } अन्यथा अगर (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // We can't directly set an RGB value on a YUV surface
        SDL_Surface *tmp = SDL_CreateSurfaceUninitialized(surface->w, surface->h, SDL_PIXELFORMAT_ARGB8888);
        अगर (!tmp) {
            जाओ done;
        }

        अगर (SDL_ClearSurface(tmp, r, g, b, a)) {
            परिणाम = SDL_ConvertPixelsAndColorspace(surface->w, surface->h, tmp->format, tmp->colorspace, tmp->props, tmp->pixels, tmp->pitch, surface->format, surface->colorspace, surface->props, surface->pixels, surface->pitch);
        }
        SDL_DestroySurface(tmp);
    } अन्यथा {
        // Take advantage of blit color conversion
        SDL_Surface *tmp = SDL_CreateSurfaceUninitialized(1, 1, SDL_PIXELFORMAT_RGBA128_FLOAT);
        अगर (!tmp) {
            जाओ done;
        }
        SDL_SetSurfaceColorspace(tmp, surface->colorspace);
        SDL_SetSurfaceBlendMode(tmp, SDL_BLENDMODE_NONE);

        भग्न *pixels = (भग्न *)tmp->pixels;
        pixels[0] = r;
        pixels[1] = g;
        pixels[2] = b;
        pixels[3] = a;

        परिणाम = SDL_BlitSurfaceScaled(tmp, शून्य, surface, शून्य, SDL_SCALEMODE_NEAREST);
        SDL_DestroySurface(tmp);
    }

done:
    SDL_SetSurfaceClipRect(surface, &clip_rect);

    वापस परिणाम;
}

Uint32 SDL_MapSurfaceRGB(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b)
{
    वापस SDL_MapSurfaceRGBA(surface, r, g, b, SDL_ALPHA_OPAQUE);
}

Uint32 SDL_MapSurfaceRGBA(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        वापस true;
    }
    वापस SDL_MapRGBA(surface->fmt, surface->palette, r, g, b, a);
}

// This function Copyright 2023 Collabora Ltd., contributed to SDL under the ZLib license
bool SDL_ReadSurfacePixel(SDL_Surface *surface, पूर्णांक x, पूर्णांक y, Uint8 *r, Uint8 *g, Uint8 *b, Uint8 *a)
{
    Uint32 pixel = 0;
    माप_प्रकार bytes_per_pixel;
    Uint8 unused;
    Uint8 *p;
    bool परिणाम = false;

    अगर (r) {
        *r = 0;
    } अन्यथा {
        r = &unused;
    }

    अगर (g) {
        *g = 0;
    } अन्यथा {
        g = &unused;
    }

    अगर (b) {
        *b = 0;
    } अन्यथा {
        b = &unused;
    }

    अगर (a) {
        *a = 0;
    } अन्यथा {
        a = &unused;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        वापस SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        वापस SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        वापस SDL_InvalidParamError("y");
    }

    bytes_per_pixel = SDL_BYTESPERPIXEL(surface->format);

    अगर (SDL_MUSTLOCK(surface)) {
        अगर (!SDL_LockSurface(surface)) {
            वापस false;
        }
    }

    p = (Uint8 *)surface->pixels + y * surface->pitch + x * bytes_per_pixel;

    अगर (bytes_per_pixel <= माप(pixel) &&
        !SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_COLORSPACEPRIMARIES(surface->colorspace) == SDL_COLOR_PRIMARIES_BT709) {
        /* Fill the appropriate number of least-significant bytes of pixel,
         * leaving the most-significant bytes set to zero */
#अगर SDL_BYTEORDER == SDL_BIG_ENDIAN
        SDL_memcpy(((Uint8 *)&pixel) + (माप(pixel) - bytes_per_pixel), p, bytes_per_pixel);
#अन्यथा
        SDL_memcpy(&pixel, p, bytes_per_pixel);
#पूर्ण_अगर
        SDL_GetRGBA(pixel, surface->fmt, surface->palette, r, g, b, a);
        परिणाम = true;
    } अन्यथा अगर (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // FIXME: We need code to extract a single macroblock from a YUV surface
        SDL_Surface *converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        अगर (converted) {
            परिणाम = SDL_ReadSurfacePixel(converted, x, y, r, g, b, a);
            SDL_DestroySurface(converted);
        }
    } अन्यथा {
        // This is really slow, but it gets the job done
        Uint8 rgba[4];

        अगर (SDL_ConvertPixelsAndColorspace(1, 1, surface->format, surface->colorspace, surface->props, p, surface->pitch, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, rgba, माप(rgba))) {
            *r = rgba[0];
            *g = rgba[1];
            *b = rgba[2];
            *a = rgba[3];
            परिणाम = true;
        }
    }

    अगर (SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }
    वापस परिणाम;
}

bool SDL_ReadSurfacePixelFloat(SDL_Surface *surface, पूर्णांक x, पूर्णांक y, भग्न *r, भग्न *g, भग्न *b, भग्न *a)
{
    भग्न unused;
    bool परिणाम = false;

    अगर (r) {
        *r = 0.0f;
    } अन्यथा {
        r = &unused;
    }

    अगर (g) {
        *g = 0.0f;
    } अन्यथा {
        g = &unused;
    }

    अगर (b) {
        *b = 0.0f;
    } अन्यथा {
        b = &unused;
    }

    अगर (a) {
        *a = 0.0f;
    } अन्यथा {
        a = &unused;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        वापस SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        वापस SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        वापस SDL_InvalidParamError("y");
    }

    अगर (SDL_BYTESPERPIXEL(surface->format) <= माप(Uint32) &&
        !SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_COLORSPACEPRIMARIES(surface->colorspace) == SDL_COLOR_PRIMARIES_BT709) {
        Uint8 r8, g8, b8, a8;

        अगर (SDL_ReadSurfacePixel(surface, x, y, &r8, &g8, &b8, &a8)) {
            *r = (भग्न)r8 / 255.0f;
            *g = (भग्न)g8 / 255.0f;
            *b = (भग्न)b8 / 255.0f;
            *a = (भग्न)a8 / 255.0f;
            परिणाम = true;
        }
    } अन्यथा अगर (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // FIXME: We need code to extract a single macroblock from a YUV surface
        SDL_Surface *converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        अगर (converted) {
            परिणाम = SDL_ReadSurfacePixelFloat(converted, x, y, r, g, b, a);
            SDL_DestroySurface(converted);
        }
    } अन्यथा {
        // This is really slow, but it gets the job done
        भग्न rgba[4];
        Uint8 *p;

        अगर (SDL_MUSTLOCK(surface)) {
            अगर (!SDL_LockSurface(surface)) {
                वापस false;
            }
        }

        p = (Uint8 *)surface->pixels + y * surface->pitch + x * SDL_BYTESPERPIXEL(surface->format);

        अगर (surface->format == SDL_PIXELFORMAT_RGBA128_FLOAT) {
            SDL_memcpy(rgba, p, माप(rgba));
            परिणाम = true;
        } अन्यथा {
            SDL_Colorspace src_colorspace = surface->colorspace;
            SDL_Colorspace dst_colorspace = (src_colorspace == SDL_COLORSPACE_SRGB_LINEAR ? SDL_COLORSPACE_SRGB_LINEAR : SDL_COLORSPACE_SRGB);

            अगर (SDL_ConvertPixelsAndColorspace(1, 1, surface->format, src_colorspace, surface->props, p, surface->pitch, SDL_PIXELFORMAT_RGBA128_FLOAT, dst_colorspace, 0, rgba, माप(rgba))) {
                परिणाम = true;
            }
        }

        अगर (परिणाम) {
            *r = rgba[0];
            *g = rgba[1];
            *b = rgba[2];
            *a = rgba[3];
        }

        अगर (SDL_MUSTLOCK(surface)) {
            SDL_UnlockSurface(surface);
        }
    }
    वापस परिणाम;
}

bool SDL_WriteSurfacePixel(SDL_Surface *surface, पूर्णांक x, पूर्णांक y, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    Uint32 pixel = 0;
    माप_प्रकार bytes_per_pixel;
    Uint8 *p;
    bool परिणाम = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        वापस SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        वापस SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        वापस SDL_InvalidParamError("y");
    }

    bytes_per_pixel = SDL_BYTESPERPIXEL(surface->format);

    अगर (SDL_MUSTLOCK(surface)) {
        अगर (!SDL_LockSurface(surface)) {
            वापस false;
        }
    }

    p = (Uint8 *)surface->pixels + y * surface->pitch + x * bytes_per_pixel;

    अगर (bytes_per_pixel <= माप(pixel) && !SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        pixel = SDL_MapRGBA(surface->fmt, surface->palette, r, g, b, a);
#अगर SDL_BYTEORDER == SDL_BIG_ENDIAN
        SDL_memcpy(p, ((Uint8 *)&pixel) + (माप(pixel) - bytes_per_pixel), bytes_per_pixel);
#अन्यथा
        SDL_memcpy(p, &pixel, bytes_per_pixel);
#पूर्ण_अगर
        परिणाम = true;
    } अन्यथा अगर (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        परिणाम = SDL_Unsupported();
    } अन्यथा {
        // This is really slow, but it gets the job done
        Uint8 rgba[4];

        rgba[0] = r;
        rgba[1] = g;
        rgba[2] = b;
        rgba[3] = a;
        परिणाम = SDL_ConvertPixelsAndColorspace(1, 1, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, rgba, माप(rgba), surface->format, surface->colorspace, surface->props, p, surface->pitch);
    }

    अगर (SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }
    वापस परिणाम;
}

bool SDL_WriteSurfacePixelFloat(SDL_Surface *surface, पूर्णांक x, पूर्णांक y, भग्न r, भग्न g, भग्न b, भग्न a)
{
    bool परिणाम = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        वापस SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        वापस SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        वापस SDL_InvalidParamError("y");
    }

    अगर (SDL_BYTESPERPIXEL(surface->format) <= माप(Uint32) && !SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        Uint8 r8, g8, b8, a8;

        r8 = (Uint8)SDL_round(SDL_clamp(r, 0.0f, 1.0f) * 255.0f);
        g8 = (Uint8)SDL_round(SDL_clamp(g, 0.0f, 1.0f) * 255.0f);
        b8 = (Uint8)SDL_round(SDL_clamp(b, 0.0f, 1.0f) * 255.0f);
        a8 = (Uint8)SDL_round(SDL_clamp(a, 0.0f, 1.0f) * 255.0f);
        अगर (SDL_WriteSurfacePixel(surface, x, y, r8, g8, b8, a8)) {
            परिणाम = true;
        }
    } अन्यथा अगर (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        परिणाम = SDL_Unsupported();
    } अन्यथा {
        // This is really slow, but it gets the job done
        भग्न rgba[4];
        Uint8 *p;

        अगर (SDL_MUSTLOCK(surface)) {
            अगर (!SDL_LockSurface(surface)) {
                वापस false;
            }
        }

        p = (Uint8 *)surface->pixels + y * surface->pitch + x * SDL_BYTESPERPIXEL(surface->format);

        rgba[0] = r;
        rgba[1] = g;
        rgba[2] = b;
        rgba[3] = a;

        अगर (surface->format == SDL_PIXELFORMAT_RGBA128_FLOAT) {
            SDL_memcpy(p, rgba, माप(rgba));
            परिणाम = true;
        } अन्यथा {
            SDL_Colorspace dst_colorspace = surface->colorspace;
            SDL_Colorspace src_colorspace = (dst_colorspace == SDL_COLORSPACE_SRGB_LINEAR ? SDL_COLORSPACE_SRGB_LINEAR : SDL_COLORSPACE_SRGB);

            परिणाम = SDL_ConvertPixelsAndColorspace(1, 1, SDL_PIXELFORMAT_RGBA128_FLOAT, src_colorspace, 0, rgba, माप(rgba), surface->format, dst_colorspace, surface->props, p, surface->pitch);
        }

        अगर (SDL_MUSTLOCK(surface)) {
            SDL_UnlockSurface(surface);
        }
    }
    वापस परिणाम;
}

/*
 * Free a surface created by the above function.
 */
व्योम SDL_DestroySurface(SDL_Surface *surface)
{
    अगर (!SDL_SurfaceValid(surface)) {
        वापस;
    }
    अगर (surface->internal_flags & SDL_INTERNAL_SURFACE_DONTFREE) {
        वापस;
    }
    अगर (--surface->refcount > 0) {
        वापस;
    }

    SDL_RemoveSurfaceAlternateImages(surface);

    SDL_DestroyProperties(surface->props);

    SDL_InvalidateMap(&surface->map);

    जबतक (surface->locked > 0) {
        SDL_UnlockSurface(surface);
    }
#अगर_घोषित SDL_HAVE_RLE
    अगर (surface->internal_flags & SDL_INTERNAL_SURFACE_RLEACCEL) {
        SDL_UnRLESurface(surface);
    }
#पूर्ण_अगर
    SDL_SetSurfacePalette(surface, शून्य);

    अगर (surface->flags & SDL_SURFACE_PREALLOCATED) {
        // Don't free
    } अन्यथा अगर (surface->flags & SDL_SURFACE_SIMD_ALIGNED) {
        // Free aligned
        SDL_aligned_free(surface->pixels);
    } अन्यथा {
        // Normal
        SDL_free(surface->pixels);
    }

    surface->reserved = शून्य;

    अगर (!(surface->internal_flags & SDL_INTERNAL_SURFACE_ढेर)) {
        SDL_free(surface);
    }
}

SDL_Surface *SDL_LoadSurface_IO(SDL_IOStream *src, bool closeio)
{
    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        वापस शून्य;
    }

    अगर (SDL_IsBMP(src)) {
        वापस SDL_LoadBMP_IO(src, closeio);
    } अन्यथा अगर (SDL_IsPNG(src)) {
        वापस SDL_LoadPNG_IO(src, closeio);
    } अन्यथा अगर (SDL_IsJPG(src)) {
        वापस SDL_LoadJPG_IO(src, closeio);
    } अन्यथा {
        अगर (closeio) {
            SDL_CloseIO(src);
        }
        SDL_SetError("Unsupported image format");
        वापस शून्य;
    }
}

SDL_Surface *SDL_LoadSurface(स्थिर अक्षर *file)
{
    SDL_IOStream *stream = SDL_IOFromFile(file, "rb");
    अगर (!stream) {
        वापस शून्य;
    }

    वापस SDL_LoadSurface_IO(stream, true);
}
