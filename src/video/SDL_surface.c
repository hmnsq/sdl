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
SDL_COMPILE_TIME_ASSERT(surface_आकार_assumptions,
                        परिमाण(पूर्णाङ्क) == परिमाण(Sint32) && परिमाण(size_t) >= परिमाण(Sint32));

SDL_COMPILE_TIME_ASSERT(can_indicate_अतिप्रवाहः, SDL_आकार_MAX > SDL_MAX_SINT32);

// Magic!
स्थिर वर्ण SDL_surface_magic;

// Public routines

bool SDL_SurfaceValid(SDL_Surface *surface)
{
    प्रत्यागम (surface && surface->reserved == &SDL_surface_magic);
}

शून्य SDL_Update_Surface_तालकम्_Flag(SDL_Surface *surface)
{
    // We need to mark the surface as needing unlock while locked
    यदि ((surface->flags & SDL_SURFACE_LOCKED) ||
        (surface->आन्तरिकम्_flags & SDL_आन्तरिकम्_SURFACE_RLEACCEL)) {
        surface->flags |= SDL_SURFACE_तालकम्_NEEDED;
    } अन्यथा {
        surface->flags &= ~SDL_SURFACE_तालकम्_NEEDED;
    }
}

/*
 * Calculate the pad-aligned scanline width of a surface.
 *
 * for FOURCC, use SDL_CalculateYUVSize()
 */
स्थिर bool SDL_CalculateRGBSize(Uint32 format, size_t विस्तारः, size_t height, size_t *आकार, size_t *pitch, bool अल्पिष्ठम्)
{
    यदि (SDL_BITSPERPIXEL(format) >= 8) {
        यदि (!SDL_आकार_mul_check_अतिप्रवाहः(विस्तारः, SDL_BYTESPERPIXEL(format), pitch)) {
            प्रत्यागम SDL_समुच्चयः_Error("width * bpp would overflow");
        }
    } अन्यथा {
        यदि (!SDL_आकार_mul_check_अतिप्रवाहः(विस्तारः, SDL_BITSPERPIXEL(format), pitch)) {
            प्रत्यागम SDL_समुच्चयः_Error("width * bpp would overflow");
        }
        यदि (!SDL_आकार_सङ्कलय_check_अतिप्रवाहः(*pitch, 7, pitch)) {
            प्रत्यागम SDL_समुच्चयः_Error("aligning pitch would overflow");
        }
        *pitch /= 8;
    }
    यदि (!अल्पिष्ठम्) {
        // 4-byte aligning for speed
        यदि (!SDL_आकार_सङ्कलय_check_अतिप्रवाहः(*pitch, 3, pitch)) {
            प्रत्यागम SDL_समुच्चयः_Error("aligning pitch would overflow");
        }
        *pitch &= ~3;
    }

    यदि (!SDL_आकार_mul_check_अतिप्रवाहः(height, *pitch, आकार)) {
        प्रत्यागम SDL_समुच्चयः_Error("height * pitch would overflow");
    }

    प्रत्यागम true;
}

bool SDL_Calculate_Surface_आकार(SDL_PixelFormat format, पूर्णाङ्क विस्तारः, पूर्णाङ्क height, size_t *आकार, size_t *pitch, bool अल्पिष्ठम्_Pitch)
{
    size_t p = 0, sz = 0;

    यदि (आकार) {
        *आकार = 0;
    }

    यदि (pitch) {
        *pitch = 0;
    }

    यदि (SDL_ISPIXELFORMAT_FOURCC(format)) {
        यदि (format == SDL_PIXELFORMAT_MJPG) {
            // We don't know in advance what it will be, we'll figure it out later.
            प्रत्यागम true;
        }

        यदि (!SDL_CalculateYUVSize(format, विस्तारः, height, &sz, &p)) {
            // Overflow...
            प्रत्यागम false;
        }
    } अन्यथा {
        यदि (!SDL_CalculateRGBSize(format, विस्तारः, height, &sz, &p, अल्पिष्ठम्_Pitch)) {
            // Overflow...
            प्रत्यागम false;
        }
    }

    यदि (आकार) {
        *आकार = sz;
    }

    यदि (pitch) {
        *pitch = p;
    }

    प्रत्यागम true;
}

स्थिर bool SDL_InitializeSurface(SDL_Surface *surface, पूर्णाङ्क विस्तारः, पूर्णाङ्क height, SDL_PixelFormat format, SDL_Colorspace colorspace, SDL_PropertiesID props, शून्य *pixels, पूर्णाङ्क pitch, bool onstack)
{
    SDL_zerop(surface);

    surface->flags = SDL_SURFACE_PREALLOCATED;
    surface->format = format;
    surface->w = विस्तारः;
    surface->h = height;
    surface->pixels = pixels;
    surface->pitch = pitch;
    surface->reserved = &SDL_surface_magic;

    यदि (onstack) {
        surface->आन्तरिकम्_flags |= SDL_आन्तरिकम्_SURFACE_राशिः;
    }

    surface->fmt = SDL_GetPixelFormatDetails(format);
    यदि (!surface->fmt) {
        SDL_DestroySurface(surface);
        प्रत्यागम false;
    }

    // Initialize the clip rect
    surface->clip_rect.w = विस्तारः;
    surface->clip_rect.h = height;

    // Allocate an empty mapping
    surface->map.info.r = 0xFF;
    surface->map.info.g = 0xFF;
    surface->map.info.b = 0xFF;
    surface->map.info.a = 0xFF;

    यदि (colorspace == SDL_COLORSPACE_UNKNOWN) {
        surface->colorspace = SDL_GetDefaultColorspaceForFormat(format);
    } अन्यथा {
        surface->colorspace = colorspace;
    }

    यदि (props) {
        यदि (!SDL_CopyProperties(props, SDL_GetSurfaceProperties(surface))) {
            SDL_DestroySurface(surface);
            प्रत्यागम false;
        }
    }

    // By default surfaces with an alpha mask are set up for blending
    यदि (SDL_ISPIXELFORMAT_ALPHA(surface->format)) {
        SDL_समुच्चयः_Surface_Blend_बहुलकम्(surface, SDL_BLENDMODE_BLEND);
    }

    // The surface is ready to go
    surface->refcount = 1;
    प्रत्यागम true;
}

/*
 * Create an empty surface of the appropriate depth using the given format
 */
स्थिर SDL_Surface *SDL_Create_Surface_आन्तरिकम्(पूर्णाङ्क विस्तारः, पूर्णाङ्क height, SDL_PixelFormat format, bool clear_surface)
{
    size_t pitch, आकार;
    SDL_Surface *surface;

    CHECK_PARAM(विस्तारः < 0) {
        SDL_InvalidParamError("width");
        प्रत्यागम रिक्त;
    }

    CHECK_PARAM(height < 0) {
        SDL_InvalidParamError("height");
        प्रत्यागम रिक्त;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        प्रत्यागम रिक्त;
    }

    यदि (!SDL_Calculate_Surface_आकार(format, विस्तारः, height, &आकार, &pitch, false /* not minimal pitch */)) {
        // Overflow...
        प्रत्यागम रिक्त;
    }

    // Allocate and initialize the surface
    surface = (SDL_Surface *)SDL_malloc(परिमाण(*surface));
    यदि (!surface) {
        प्रत्यागम रिक्त;
    }

    यदि (!SDL_InitializeSurface(surface, विस्तारः, height, format, SDL_COLORSPACE_UNKNOWN, 0, रिक्त, (पूर्णाङ्क)pitch, false)) {
        प्रत्यागम रिक्त;
    }

    यदि (surface->w && surface->h && format != SDL_PIXELFORMAT_MJPG) {
        surface->flags &= ~SDL_SURFACE_PREALLOCATED;
        यदि (SDL_GetHintBoolean("SDL_SURFACE_MALLOC", false)) {
            यदि (clear_surface) {
                surface->pixels = SDL_calloc(1, आकार);
            } अन्यथा {
                surface->pixels = SDL_malloc(आकार);
            }
        } अन्यथा {
            surface->flags |= SDL_SURFACE_SIMD_ALIGNED;
            यदि (clear_surface) {
                surface->pixels = SDL_aligned_alloc_zero(SDL_GetSIMDAlignment(), आकार);
            } अन्यथा {
                surface->pixels = SDL_aligned_alloc(SDL_GetSIMDAlignment(), आकार);
            }
        }
        यदि (!surface->pixels) {
            SDL_DestroySurface(surface);
            प्रत्यागम रिक्त;
        }
    }
    प्रत्यागम surface;
}

SDL_Surface *SDL_CreateSurfaceZeroed(पूर्णाङ्क विस्तारः, पूर्णाङ्क height, SDL_PixelFormat format)
{
    प्रत्यागम SDL_Create_Surface_आन्तरिकम्(विस्तारः, height, format, true);
}

SDL_Surface *SDL_CreateSurfaceUninitialized(पूर्णाङ्क विस्तारः, पूर्णाङ्क height, SDL_PixelFormat format)
{
    प्रत्यागम SDL_Create_Surface_आन्तरिकम्(विस्तारः, height, format, false);
}

SDL_Surface *SDL_CreateSurface(पूर्णाङ्क विस्तारः, पूर्णाङ्क height, SDL_PixelFormat format)
{
    प्रत्यागम SDL_CreateSurfaceZeroed(विस्तारः, height, format);
}


/*
 * Create an RGB surface from an existing memory buffer using the given
 * enum SDL_PIXELFORMAT_* format
 */
SDL_Surface *SDL_CreateSurfaceFrom(पूर्णाङ्क विस्तारः, पूर्णाङ्क height, SDL_PixelFormat format, शून्य *pixels, पूर्णाङ्क pitch)
{
    CHECK_PARAM(विस्तारः < 0) {
        SDL_InvalidParamError("width");
        प्रत्यागम रिक्त;
    }

    CHECK_PARAM(height < 0) {
        SDL_InvalidParamError("height");
        प्रत्यागम रिक्त;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        प्रत्यागम रिक्त;
    }

    यदि (pitch == 0 && !pixels) {
        // The application will fill these in later with valid values
    } अन्यथा {
        size_t अल्पिष्ठम्_Pitch;

        यदि (!SDL_Calculate_Surface_आकार(format, विस्तारः, height, रिक्त, &अल्पिष्ठम्_Pitch, true /* minimal pitch */)) {
            // Overflow...
            प्रत्यागम रिक्त;
        }

        CHECK_PARAM(pitch < 0 || (size_t)pitch < अल्पिष्ठम्_Pitch) {
            SDL_InvalidParamError("pitch");
            प्रत्यागम रिक्त;
        }
    }

    // Allocate and initialize the surface
    SDL_Surface *surface = (SDL_Surface *)SDL_malloc(परिमाण(*surface));
    यदि (!surface ||
        !SDL_InitializeSurface(surface, विस्तारः, height, format, SDL_COLORSPACE_UNKNOWN, 0, pixels, pitch, false)) {
        प्रत्यागम रिक्त;
    }
    प्रत्यागम surface;
}

SDL_PropertiesID SDL_GetSurfaceProperties(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        प्रत्यागम 0;
    }

    यदि (!surface->props) {
        surface->props = SDL_CreateProperties();
    }
    प्रत्यागम surface->props;
}

bool SDL_समुच्चयः_Surface_Colorspace(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        प्रत्यागम SDL_InvalidParamError("surface");
    }

    surface->colorspace = colorspace;
    प्रत्यागम true;
}

SDL_Colorspace SDL_GetSurfaceColorspace(SDL_Surface *surface)
{
    यदि (!SDL_SurfaceValid(surface)) {
        प्रत्यागम SDL_COLORSPACE_UNKNOWN;
    }

    प्रत्यागम surface->colorspace;
}

भिन्न SDL_GetDefaultSDRWhitePoint(SDL_Colorspace colorspace)
{
    प्रत्यागम SDL_GetSurfaceSDRWhitePoint(रिक्त, colorspace);
}

भिन्न SDL_GetSurfaceSDRWhitePoint(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    SDL_TransferCharacteristics transfer = SDL_COLORSPACETRANSFER(colorspace);

    यदि (transfer == SDL_TRANSFER_CHARACTERISTICS_रैखिकम् ||
        transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
        SDL_PropertiesID props;
        भिन्न default_मानम् = 1.0f;

        यदि (SDL_SurfaceValid(surface)) {
            props = surface->props;
        } अन्यथा {
            props = 0;
        }
        यदि (transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
            /* The older standards use an SDR white point of 100 nits.
             * ITU-R BT.2408-6 recommends using an SDR white point of 203 nits.
             * This is the default Chrome uses, and what a lot of game content
             * assumes, so we'll go with that.
             */
            ध्रुव भिन्न DEFAULT_PQ_SDR_WHITE_POINT = 203.0f;
            default_मानम् = DEFAULT_PQ_SDR_WHITE_POINT;
        }
        प्रत्यागम SDL_GetFloatProperty(props, SDL_PROP_SURFACE_SDR_WHITE_POINT_FLOAT, default_मानम्);
    }
    प्रत्यागम 1.0f;
}

भिन्न SDL_GetDefaultHDRHeadroom(SDL_Colorspace colorspace)
{
    प्रत्यागम SDL_GetSurfaceHDRHeadroom(रिक्त, colorspace);
}

भिन्न SDL_GetSurfaceHDRHeadroom(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    SDL_TransferCharacteristics transfer = SDL_COLORSPACETRANSFER(colorspace);

    यदि (transfer == SDL_TRANSFER_CHARACTERISTICS_रैखिकम् ||
        transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
        SDL_PropertiesID props;
        भिन्न default_मानम् = 0.0f;

        यदि (SDL_SurfaceValid(surface)) {
            props = surface->props;
        } अन्यथा {
            props = 0;
        }
        प्रत्यागम SDL_GetFloatProperty(props, SDL_PROP_SURFACE_HDR_HEADROOM_FLOAT, default_मानम्);
    }
    प्रत्यागम 1.0f;
}

SDL_Palette *SDL_CreateSurfacePalette(SDL_Surface *surface)
{
    SDL_Palette *palette;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        प्रत्यागम रिक्त;
    }

    CHECK_PARAM(!SDL_ISPIXELFORMAT_अनुक्रमितम्(surface->format)) {
        SDL_समुच्चयः_Error("The surface is not indexed format");
        प्रत्यागम रिक्त;
    }

    palette = SDL_CreatePalette((1 << SDL_BITSPERPIXEL(surface->format)));
    यदि (!palette) {
        प्रत्यागम रिक्त;
    }

    यदि (palette->ncolors == 2) {
        // Create a black and white bitmap palette
        palette->colors[0].r = 0xFF;
        palette->colors[0].g = 0xFF;
        palette->colors[0].b = 0xFF;
        palette->colors[1].r = 0x00;
        palette->colors[1].g = 0x00;
        palette->colors[1].b = 0x00;
    }

    यदि (!SDL_समुच्चयः_Surface_Palette(surface, palette)) {
        SDL_DestroyPalette(palette);
        प्रत्यागम रिक्त;
    }

    // The surface has retained the palette, we can remove the reference here
    SDL_assert(palette->refcount == 2);
    SDL_DestroyPalette(palette);
    प्रत्यागम palette;
}

bool SDL_समुच्चयः_Surface_Palette(SDL_Surface *surface, SDL_Palette *palette)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        प्रत्यागम SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(palette && !SDL_ISPIXELFORMAT_अनुक्रमितम्(surface->format)) {
        प्रत्यागम SDL_समुच्चयः_Error("Surface doesn't use a palette");
    }

    CHECK_PARAM(palette && palette->ncolors > (1 << SDL_BITSPERPIXEL(surface->format))) {
        प्रत्यागम SDL_समुच्चयः_Error("Palette doesn't match surface format");
    }

    यदि (palette != surface->palette) {
        यदि (surface->palette) {
            SDL_DestroyPalette(surface->palette);
        }

        surface->palette = palette;

        यदि (surface->palette) {
            ++surface->palette->refcount;
        }
    }

    SDL_InvalidateMap(&surface->map);

    प्रत्यागम true;
}

SDL_Palette *SDL_GetSurfacePalette(SDL_Surface *surface)
{
    यदि (!SDL_SurfaceValid(surface)) {
        प्रत्यागम रिक्त;
    }

    प्रत्यागम surface->palette;
}

bool SDL_सङ्कलय_Surface_Alternate_Image(SDL_Surface *surface, SDL_Surface *image)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        प्रत्यागम SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(!SDL_SurfaceValid(image)) {
        प्रत्यागम SDL_InvalidParamError("image");
    }

    SDL_Surface **images = (SDL_Surface **)SDL_realloc(surface->images, (surface->अङ्कः_images + 1) * परिमाण(*images));
    यदि (!images) {
        प्रत्यागम false;
    }
    images[surface->अङ्कः_images] = image;
    surface->images = images;
    ++surface->अङ्कः_images;
    ++image->refcount;
    प्रत्यागम true;
}

bool SDL_SurfaceHasAlternateImages(SDL_Surface *surface)
{
    यदि (!SDL_SurfaceValid(surface)) {
        प्रत्यागम false;
    }

    प्रत्यागम (surface->अङ्कः_images > 0);
}

SDL_Surface **SDL_GetSurfaceImages(SDL_Surface *surface, पूर्णाङ्क *गणनम्)
{
    यदि (गणनम्) {
        *गणनम् = 0;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        प्रत्यागम रिक्त;
    }

    पूर्णाङ्क अङ्कः_images = 1 + surface->अङ्कः_images;
    SDL_Surface **images = (SDL_Surface **)SDL_malloc((अङ्कः_images + 1) * परिमाण(*images));
    यदि (!images) {
        प्रत्यागम रिक्त;
    }
    images[0] = surface;
    यदि (surface->अङ्कः_images > 0) {
        SDL_memcpy(&images[1], surface->images, (surface->अङ्कः_images * परिमाण(images[1])));
    }
    images[अङ्कः_images] = रिक्त;

    यदि (गणनम्) {
        *गणनम् = अङ्कः_images;
    }
    प्रत्यागम images;
}

SDL_Surface *SDL_GetSurfaceImage(SDL_Surface *surface, भिन्न display_scale)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        प्रत्यागम रिक्त;
    }

    यदि (!SDL_SurfaceHasAlternateImages(surface)) {
        ++surface->refcount;
        प्रत्यागम surface;
    }

    // This surface has high DPI images, pick the best one available, or scale one to the correct size
    SDL_Surface **images = SDL_GetSurfaceImages(surface, रिक्त);
    यदि (!images) {
        // Failure, fall back to the existing surface
        ++surface->refcount;
        प्रत्यागम surface;
    }

    // Find closest image. Images that are larger than the
    // desired size are preferred over images that are smaller.
    SDL_Surface *closest = रिक्त;
    पूर्णाङ्क desired_w = (पूर्णाङ्क)SDL_आवर्तनम्(surface->w * display_scale);
    पूर्णाङ्क desired_h = (पूर्णाङ्क)SDL_आवर्तनम्(surface->h * display_scale);
    पूर्णाङ्क desired_आकार = desired_w * desired_h;
    पूर्णाङ्क closest_distance = -1;
    पूर्णाङ्क closest_आकार = -1;
    प्रति (पूर्णाङ्क i = 0; images[i]; ++i) {
        SDL_Surface *candidate = images[i];
        पूर्णाङ्क आकार = candidate->w * candidate->h;
        पूर्णाङ्क delta_w = (candidate->w - desired_w);
        पूर्णाङ्क delta_h = (candidate->h - desired_h);
        पूर्णाङ्क distance = (delta_w * delta_w) + (delta_h * delta_h);
        यदि (closest_distance < 0 || distance < closest_distance ||
            (आकार > desired_आकार && closest_आकार < desired_आकार)) {
            closest = candidate;
            closest_distance = distance;
            closest_आकार = आकार;
        }
    }
    SDL_free(images);
    SDL_assert(closest != रिक्त);    // We should always have at least one surface

    यदि (closest->w == desired_w && closest->h == desired_h) {
        ++closest->refcount;
        प्रत्यागम closest;
    }

    // We need to scale the image to the correct size. To maintain good image quality, downscaling
    // is done in steps, never reducing the width and height by more than half each time.
    SDL_Surface *scaled = closest;
    कुरु {
        पूर्णाङ्क अग्र_scaled_w = SDL_max(desired_w, (scaled->w + 1) / 2);
        पूर्णाङ्क अग्र_scaled_h = SDL_max(desired_h, (scaled->h + 1) / 2);
        SDL_Surface *अग्र_scaled = SDL_ScaleSurface(scaled, अग्र_scaled_w, अग्र_scaled_h, SDL_SCALEMODE_रैखिकम्);
        यदि (scaled != closest) {
            SDL_DestroySurface(scaled);
        }
        scaled = अग्र_scaled;
        यदि (!scaled) {
            // Failure, fall back to the closest surface
            ++closest->refcount;
            प्रत्यागम closest;
        }
    } यावत् (scaled->w != desired_w || scaled->h != desired_h);

    प्रत्यागम scaled;
}

शून्य SDL_RemoveSurfaceAlternateImages(SDL_Surface *surface)
{
    यदि (!SDL_SurfaceValid(surface)) {
        प्रत्यागम;
    }

    यदि (surface->अङ्कः_images > 0) {
        प्रति (पूर्णाङ्क i = 0; i < surface->अङ्कः_images; ++i) {
            SDL_DestroySurface(surface->images[i]);
        }
        SDL_free(surface->images);
        surface->images = रिक्त;
        surface->अङ्कः_images = 0;
    }
}

bool SDL_समुच्चयः_Surface_RLE(SDL_Surface *surface, bool enabled)
{
    पूर्णाङ्क flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        प्रत्यागम SDL_InvalidParamError("surface");
    }

    flags = surface->map.info.flags;
    यदि (enabled) {
        surface->map.info.flags |= SDL_COPY_RLE_DESIRED;
    } अन्यथा {
        surface->map.info.flags &= ~SDL_COPY_RLE_DESIRED;
    }
    यदि (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    प्रत्यागम true;
}

bool SDL_SurfaceHasRLE(SDL_Surface *surface)
{
    यदि (!SDL_SurfaceValid(surface)) {
        प्रत्यागम false;
    }

    यदि (!(surface->map.info.flags & SDL_COPY_RLE_DESIRED)) {
        प्रत्यागम false;
    }

    प्रत्यागम true;
}

bool SDL_समुच्चयः_Surface_Color_कुञ्चिका(SDL_Surface *surface, bool enabled, Uint32 कुञ्चिका)
{
    पूर्णाङ्क flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        प्रत्यागम SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(surface->palette && कुञ्चिका >= ((Uint32)surface->palette->ncolors)) {
        प्रत्यागम SDL_InvalidParamError("key");
    }

    flags = surface->map.info.flags;
    यदि (enabled) {
        surface->map.info.flags |= SDL_COPY_COLORKEY;
        surface->map.info.colorkey = कुञ्चिका;
    } अन्यथा {
        surface->map.info.flags &= ~SDL_COPY_COLORKEY;
    }
    यदि (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }

    प्रत्यागम true;
}

bool SDL_Surface_Has_Color_कुञ्चिका(SDL_Surface *surface)
{
    यदि (!SDL_SurfaceValid(surface)) {
        प्रत्यागम false;
    }

    यदि (!(surface->map.info.flags & SDL_COPY_COLORKEY)) {
        प्रत्यागम false;
    }

    प्रत्यागम true;
}

bool SDL_Get_Surface_Color_कुञ्चिका(SDL_Surface *surface, Uint32 *कुञ्चिका)
{
    यदि (कुञ्चिका) {
        *कुञ्चिका = 0;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        प्रत्यागम SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(!(surface->map.info.flags & SDL_COPY_COLORKEY)) {
        प्रत्यागम SDL_समुच्चयः_Error("Surface doesn't have a colorkey");
    }

    यदि (कुञ्चिका) {
        *कुञ्चिका = surface->map.info.colorkey;
    }
    प्रत्यागम true;
}

/* This is a fairly slow function to switch from colorkey to alpha
   NB: it doesn't handle bpp 1 or 3, because they have no alpha channel */
स्थिर शून्य SDL_Convert_Colorkey_गन्तव्यम्_Alpha(SDL_Surface *surface, bool ignore_alpha)
{
    पूर्णाङ्क x, y, bpp;

    यदि (!SDL_SurfaceValid(surface)) {
        प्रत्यागम;
    }

    यदि (!(surface->map.info.flags & SDL_COPY_COLORKEY) ||
        !SDL_ISPIXELFORMAT_ALPHA(surface->format)) {
        प्रत्यागम;
    }

    bpp = SDL_BYTESPERPIXEL(surface->format);

    SDL_तालकम्_Surface(surface);

    यदि (bpp == 2) {
        Uint16 *row, *spot;
        Uint16 ckey = (Uint16)surface->map.info.colorkey;
        Uint16 आवरणम् = (Uint16)(~surface->fmt->Amask);

        // Ignore, or not, alpha in colorkey comparison
        यदि (ignore_alpha) {
            ckey &= आवरणम्;
            row = (Uint16 *)surface->pixels;
            प्रति (y = surface->h; y--;) {
                spot = row;
                प्रति (x = surface->w; x--;) {
                    यदि ((*spot & आवरणम्) == ckey) {
                        *spot &= आवरणम्;
                    }
                    ++spot;
                }
                row += surface->pitch / 2;
            }
        } अन्यथा {
            row = (Uint16 *)surface->pixels;
            प्रति (y = surface->h; y--;) {
                spot = row;
                प्रति (x = surface->w; x--;) {
                    यदि (*spot == ckey) {
                        *spot &= आवरणम्;
                    }
                    ++spot;
                }
                row += surface->pitch / 2;
            }
        }
    } अन्यथा यदि (bpp == 4) {
        Uint32 *row, *spot;
        Uint32 ckey = surface->map.info.colorkey;
        Uint32 आवरणम् = ~surface->fmt->Amask;

        // Ignore, or not, alpha in colorkey comparison
        यदि (ignore_alpha) {
            ckey &= आवरणम्;
            row = (Uint32 *)surface->pixels;
            प्रति (y = surface->h; y--;) {
                spot = row;
                प्रति (x = surface->w; x--;) {
                    यदि ((*spot & आवरणम्) == ckey) {
                        *spot &= आवरणम्;
                    }
                    ++spot;
                }
                row += surface->pitch / 4;
            }
        } अन्यथा {
            row = (Uint32 *)surface->pixels;
            प्रति (y = surface->h; y--;) {
                spot = row;
                प्रति (x = surface->w; x--;) {
                    यदि (*spot == ckey) {
                        *spot &= आवरणम्;
                    }
                    ++spot;
                }
                row += surface->pitch / 4;
            }
        }
    }

    SDL_UnlockSurface(surface);

    SDL_समुच्चयः_Surface_Color_कुञ्चिका(surface, false, 0);
    SDL_समुच्चयः_Surface_Blend_बहुलकम्(surface, SDL_BLENDMODE_BLEND);
}

bool SDL_समुच्चयः_Surface_Color_Mod(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b)
{
    पूर्णाङ्क flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        प्रत्यागम SDL_InvalidParamError("surface");
    }

    surface->map.info.r = r;
    surface->map.info.g = g;
    surface->map.info.b = b;

    flags = surface->map.info.flags;
    यदि (r != 0xFF || g != 0xFF || b != 0xFF) {
        surface->map.info.flags |= SDL_COPY_MODULATE_COLOR;
    } अन्यथा {
        surface->map.info.flags &= ~SDL_COPY_MODULATE_COLOR;
    }
    यदि (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    प्रत्यागम true;
}

bool SDL_GetSurfaceColorMod(SDL_Surface *surface, Uint8 *r, Uint8 *g, Uint8 *b)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        यदि (r) {
            *r = 255;
        }
        यदि (g) {
            *g = 255;
        }
        यदि (b) {
            *b = 255;
        }
        प्रत्यागम SDL_InvalidParamError("surface");
    }

    यदि (r) {
        *r = surface->map.info.r;
    }
    यदि (g) {
        *g = surface->map.info.g;
    }
    यदि (b) {
        *b = surface->map.info.b;
    }
    प्रत्यागम true;
}

bool SDL_समुच्चयः_Surface_Alpha_Mod(SDL_Surface *surface, Uint8 alpha)
{
    पूर्णाङ्क flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        प्रत्यागम SDL_InvalidParamError("surface");
    }

    surface->map.info.a = alpha;

    flags = surface->map.info.flags;
    यदि (alpha != 0xFF) {
        surface->map.info.flags |= SDL_COPY_MODULATE_ALPHA;
    } अन्यथा {
        surface->map.info.flags &= ~SDL_COPY_MODULATE_ALPHA;
    }
    यदि (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    प्रत्यागम true;
}

bool SDL_GetSurfaceAlphaMod(SDL_Surface *surface, Uint8 *alpha)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        यदि (alpha) {
            *alpha = 255;
        }
        प्रत्यागम SDL_InvalidParamError("surface");
    }

    यदि (alpha) {
        *alpha = surface->map.info.a;
    }
    प्रत्यागम true;
}

bool SDL_समुच्चयः_Surface_Blend_बहुलकम्(SDL_Surface *surface, SDL_Blend_बहुलकम् blend_बहुलकम्)
{
    पूर्णाङ्क flags;
    bool परिणाम = true;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        प्रत्यागम SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(blend_बहुलकम् == SDL_BLENDMODE_INVALID) {
        प्रत्यागम SDL_InvalidParamError("blendMode");
    }

    flags = surface->map.info.flags;
    surface->map.info.flags &= ~SDL_COPY_BLEND_आवरणम्;
    विकल्प (blend_बहुलकम्) {
    पक्ष SDL_BLENDMODE_NONE:
        भङ्ग;
    पक्ष SDL_BLENDMODE_BLEND:
        surface->map.info.flags |= SDL_COPY_BLEND;
        भङ्ग;
    पक्ष SDL_BLENDMODE_BLEND_PREMULTIPLIED:
        surface->map.info.flags |= SDL_COPY_BLEND_PREMULTIPLIED;
        भङ्ग;
    पक्ष SDL_BLENDMODE_सङ्कलय:
        surface->map.info.flags |= SDL_COPY_सङ्कलय;
        भङ्ग;
    पक्ष SDL_BLENDMODE_सङ्कलय_PREMULTIPLIED:
        surface->map.info.flags |= SDL_COPY_सङ्कलय_PREMULTIPLIED;
        भङ्ग;
    पक्ष SDL_BLENDMODE_MOD:
        surface->map.info.flags |= SDL_COPY_MOD;
        भङ्ग;
    पक्ष SDL_BLENDMODE_MUL:
        surface->map.info.flags |= SDL_COPY_MUL;
        भङ्ग;
    स्वभाव:
        परिणाम = SDL_Unsupported();
        भङ्ग;
    }

    यदि (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }

    प्रत्यागम परिणाम;
}

bool SDL_Get_Surface_Blend_बहुलकम्(SDL_Surface *surface, SDL_Blend_बहुलकम् *blend_बहुलकम्)
{
    यदि (blend_बहुलकम्) {
        *blend_बहुलकम् = SDL_BLENDMODE_INVALID;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        प्रत्यागम SDL_InvalidParamError("surface");
    }

    यदि (!blend_बहुलकम्) {
        प्रत्यागम true;
    }

    विकल्प (surface->map.info.flags & SDL_COPY_BLEND_आवरणम्) {
    पक्ष SDL_COPY_BLEND:
        *blend_बहुलकम् = SDL_BLENDMODE_BLEND;
        भङ्ग;
    पक्ष SDL_COPY_BLEND_PREMULTIPLIED:
        *blend_बहुलकम् = SDL_BLENDMODE_BLEND_PREMULTIPLIED;
        भङ्ग;
    पक्ष SDL_COPY_सङ्कलय:
        *blend_बहुलकम् = SDL_BLENDMODE_सङ्कलय;
        भङ्ग;
    पक्ष SDL_COPY_सङ्कलय_PREMULTIPLIED:
        *blend_बहुलकम् = SDL_BLENDMODE_सङ्कलय_PREMULTIPLIED;
        भङ्ग;
    पक्ष SDL_COPY_MOD:
        *blend_बहुलकम् = SDL_BLENDMODE_MOD;
        भङ्ग;
    पक्ष SDL_COPY_MUL:
        *blend_बहुलकम् = SDL_BLENDMODE_MUL;
        भङ्ग;
    स्वभाव:
        *blend_बहुलकम् = SDL_BLENDMODE_NONE;
        भङ्ग;
    }
    प्रत्यागम true;
}

bool SDL_समुच्चयः_Surface_Clip_Rect(SDL_Surface *surface, ध्रुव SDL_Rect *rect)
{
    SDL_Rect पूर्णम्_rect;

    // Don't do anything if there's no surface to act on
    यदि (!SDL_SurfaceValid(surface)) {
        प्रत्यागम false;
    }

    // Set up the full surface rectangle
    पूर्णम्_rect.x = 0;
    पूर्णम्_rect.y = 0;
    पूर्णम्_rect.w = surface->w;
    पूर्णम्_rect.h = surface->h;

    // Set the clipping rectangle
    यदि (!rect) {
        surface->clip_rect = पूर्णम्_rect;
        प्रत्यागम true;
    }
    प्रत्यागम SDL_GetRectIntersection(rect, &पूर्णम्_rect, &surface->clip_rect);
}

bool SDL_GetSurfaceClipRect(SDL_Surface *surface, SDL_Rect *rect)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        यदि (rect) {
            SDL_zerop(rect);
        }
        प्रत्यागम SDL_InvalidParamError("surface");
    }
    CHECK_PARAM(!rect) {
        प्रत्यागम SDL_InvalidParamError("rect");
    }
    *rect = surface->clip_rect;
    प्रत्यागम true;
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
bool SDL_BlitSurfaceUnchecked(SDL_Surface *src, ध्रुव SDL_Rect *srcrect,
                             SDL_Surface *dst, ध्रुव SDL_Rect *dstrect)
{
    // Check to make sure the blit mapping is valid
    यदि (!SDL_ValidateMap(src, dst)) {
        प्रत्यागम false;
    }
    प्रत्यागम src->map.blit(src, srcrect, dst, dstrect);
}

bool SDL_BlitSurface(SDL_Surface *src, ध्रुव SDL_Rect *srcrect, SDL_Surface *dst, ध्रुव SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src) || (!src->pixels && !SDL_MUSTLOCK(src))) {
        प्रत्यागम SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst) || (!dst->pixels && !SDL_MUSTLOCK(dst))) {
        प्रत्यागम SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        प्रत्यागम SDL_समुच्चयः_Error("Surfaces must not be locked during blit");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    यदि (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
    } अन्यथा {
        r_dst.x = 0;
        r_dst.y = 0;
    }

    // clip the source rectangle to the source surface
    यदि (srcrect) {
        SDL_Rect tmp;
        यदि (SDL_GetRectIntersection(srcrect, &r_src, &tmp) == false) {
            प्रत्यागम true;
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
        यदि (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &tmp) == false) {
            प्रत्यागम true;
        }

        // Shift srcrect, if dstrect has changed
        r_src.x += tmp.x - r_dst.x;
        r_src.y += tmp.y - r_dst.y;
        r_src.w = tmp.w;
        r_src.h = tmp.h;

        // Update dstrect
        r_dst = tmp;
    }

    यदि (r_dst.w <= 0 || r_dst.h <= 0) {
        // No-op.
        प्रत्यागम true;
    }

    // Switch back to a fast blit if we were previously stretching
    यदि (src->map.info.flags & SDL_COPY_निकटतमः) {
        src->map.info.flags &= ~SDL_COPY_निकटतमः;
        SDL_InvalidateMap(&src->map);
    }

    प्रत्यागम SDL_BlitSurfaceUnchecked(src, &r_src, dst, &r_dst);
}

स्थिर bool SDL_BlitSurfaceClippedScaled(SDL_Surface *src, ध्रुव SDL_Rect *srcrect, SDL_Surface *dst, ध्रुव SDL_Rect *dstrect, SDL_Scale_बहुलकम् scale_बहुलकम्)
{
    // We need to scale first, then blit into dst because we're clipping in the destination surface pixel coordinates
    bool परिणाम;
    पूर्णाङ्क saved_w = src->w;
    पूर्णाङ्क saved_h = src->h;
    शून्य *saved_pixels = src->pixels;
    src->w = srcrect->w;
    src->h = srcrect->h;
    src->pixels = (Uint8 *)src->pixels + srcrect->y * src->pitch + srcrect->x * SDL_BYTESPERPIXEL(src->format);
    SDL_Surface *scaled = SDL_ScaleSurface(src, dstrect->w, dstrect->h, scale_बहुलकम्);
    यदि (scaled) {
        परिणाम = SDL_BlitSurface(scaled, रिक्त, dst, dstrect);
        SDL_DestroySurface(scaled);
    } अन्यथा {
        परिणाम = false;
    }
    src->w = saved_w;
    src->h = saved_h;
    src->pixels = saved_pixels;
    प्रत्यागम परिणाम;
}

bool SDL_BlitSurfaceScaled(SDL_Surface *src, ध्रुव SDL_Rect *srcrect, SDL_Surface *dst, ध्रुव SDL_Rect *dstrect, SDL_Scale_बहुलकम् scale_बहुलकम्)
{
    SDL_Rect r_src, r_dst;
    bool परिणाम;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src) || (!src->pixels && !SDL_MUSTLOCK(src))) {
        प्रत्यागम SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst) || (!dst->pixels && !SDL_MUSTLOCK(dst))) {
        प्रत्यागम SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        प्रत्यागम SDL_समुच्चयः_Error("Surfaces must not be locked during blit");
    }

    विकल्प (scale_बहुलकम्) {
    पक्ष SDL_SCALEMODE_निकटतमः:
        भङ्ग;
    पक्ष SDL_SCALEMODE_रैखिकम्:
        भङ्ग;
    पक्ष SDL_SCALEMODE_PIXELART:
        scale_बहुलकम् = SDL_SCALEMODE_निकटतमः;
        भङ्ग;
    स्वभाव:
        प्रत्यागम SDL_InvalidParamError("scaleMode");
    }

    पूर्णाङ्क src_w = srcrect ? srcrect->w : src->w;
    पूर्णाङ्क src_h = srcrect ? srcrect->h : src->h;
    पूर्णाङ्क dst_w = dstrect ? dstrect->w : dst->w;
    पूर्णाङ्क dst_h = dstrect ? dstrect->h : dst->h;
    यदि (src_w == dst_w && src_h == dst_h) {
        // No scaling, defer to regular blit
        प्रत्यागम SDL_BlitSurface(src, srcrect, dst, dstrect);
    }

    यदि (src->w == 0 || src->h == 0) {
        // Nothing to do
        प्रत्यागम true;
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    यदि (dstrect) {
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
    यदि (srcrect) {
        SDL_Rect desired, tmp;
        desired.x = srcrect->x;
        desired.y = srcrect->y;
        desired.w = SDL_max(srcrect->w, 1);
        desired.h = SDL_max(srcrect->h, 1);
        यदि (SDL_GetRectIntersection(&desired, &r_src, &tmp) == false) {
            प्रत्यागम true;
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
    यदि (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &tmp) == false) {
        प्रत्यागम true;
    }

    यदि (tmp.x != r_dst.x || tmp.y != r_dst.y || tmp.w != r_dst.w || tmp.h != r_dst.h) {
        // Need to do a clipped and scaled blit
        प्रत्यागम SDL_BlitSurfaceClippedScaled(src, &r_src, dst, &r_dst, scale_बहुलकम्);
    }

    यदि (SDL_MUSTLOCK(src)) {
        यदि (!SDL_तालकम्_Surface(src)) {
            प्रत्यागम false;
        }
    }
    यदि (SDL_MUSTLOCK(dst)) {
        यदि (!SDL_तालकम्_Surface(dst)) {
            यदि (SDL_MUSTLOCK(src)) {
                SDL_UnlockSurface(src);
            }
            प्रत्यागम false;
        }
    }

    परिणाम = SDL_BlitSurfaceUncheckedScaled(src, &r_src, dst, &r_dst, scale_बहुलकम्);

    यदि (SDL_MUSTLOCK(src)) {
        SDL_UnlockSurface(src);
    }
    यदि (SDL_MUSTLOCK(dst)) {
        SDL_UnlockSurface(dst);
    }
    प्रत्यागम परिणाम;
}

/**
 *  This is a semi-private blit function and it performs low-level surface
 *  scaled blitting only.
 */
bool SDL_BlitSurfaceUncheckedScaled(SDL_Surface *src, ध्रुव SDL_Rect *srcrect, SDL_Surface *dst, ध्रुव SDL_Rect *dstrect, SDL_Scale_बहुलकम् scale_बहुलकम्)
{
    स्थिर ध्रुव Uint32 complex_copy_flags = (SDL_COPY_MODULATE_आवरणम् | SDL_COPY_BLEND_आवरणम् | SDL_COPY_COLORKEY);

    यदि (srcrect->w > SDL_MAX_UINT16 || srcrect->h > SDL_MAX_UINT16 ||
        dstrect->w > SDL_MAX_UINT16 || dstrect->h > SDL_MAX_UINT16) {
        प्रत्यागम SDL_समुच्चयः_Error("Size too large for scaling");
    }

    यदि (!(src->map.info.flags & SDL_COPY_निकटतमः)) {
        src->map.info.flags |= SDL_COPY_निकटतमः;
        SDL_InvalidateMap(&src->map);
    }

    यदि (scale_बहुलकम् == SDL_SCALEMODE_निकटतमः || scale_बहुलकम् == SDL_SCALEMODE_PIXELART) {
        यदि (!(src->map.info.flags & complex_copy_flags) &&
            src->format == dst->format &&
            (!SDL_ISPIXELFORMAT_अनुक्रमितम्(src->format) ||
             (SDL_BITSPERPIXEL(src->format) == 8 && SDL_IsSamePalette(src->palette, dst->palette))) &&
            SDL_BYTESPERPIXEL(src->format) <= 4) {
            प्रत्यागम SDL_StretchSurface(src, srcrect, dst, dstrect, SDL_SCALEMODE_निकटतमः);
        } अन्यथा यदि (SDL_BITSPERPIXEL(src->format) < 8) {
            // Scaling bitmap not yet supported, convert to RGBA for blit
            bool परिणाम = false;
            SDL_Surface *tmp = SDL_ConvertSurface(src, SDL_PIXELFORMAT_ARGB8888);
            यदि (tmp) {
                परिणाम = SDL_BlitSurfaceUncheckedScaled(tmp, srcrect, dst, dstrect, SDL_SCALEMODE_निकटतमः);
                SDL_DestroySurface(tmp);
            }
            प्रत्यागम परिणाम;
        } अन्यथा {
            प्रत्यागम SDL_BlitSurfaceUnchecked(src, srcrect, dst, dstrect);
        }
    } अन्यथा {
        यदि (!(src->map.info.flags & complex_copy_flags) &&
            src->format == dst->format &&
            !SDL_ISPIXELFORMAT_अनुक्रमितम्(src->format) &&
            SDL_BYTESPERPIXEL(src->format) == 4 &&
            src->format != SDL_PIXELFORMAT_ARGB2101010) {
            // fast path
            प्रत्यागम SDL_StretchSurface(src, srcrect, dst, dstrect, SDL_SCALEMODE_रैखिकम्);
        } अन्यथा यदि (SDL_BITSPERPIXEL(src->format) < 8) {
            // Scaling bitmap not yet supported, convert to RGBA for blit
            bool परिणाम = false;
            SDL_Surface *tmp = SDL_ConvertSurface(src, SDL_PIXELFORMAT_ARGB8888);
            यदि (tmp) {
                परिणाम = SDL_BlitSurfaceUncheckedScaled(tmp, srcrect, dst, dstrect, scale_बहुलकम्);
                SDL_DestroySurface(tmp);
            }
            प्रत्यागम परिणाम;
        } अन्यथा {
            // Use intermediate surface(s)
            SDL_Surface *tmp1 = रिक्त;
            bool परिणाम;
            SDL_Rect srcrect2;
            पूर्णाङ्क is_complex_copy_flags = (src->map.info.flags & complex_copy_flags);

            Uint8 r, g, b;
            Uint8 alpha;
            SDL_Blend_बहुलकम् blend_बहुलकम्;

            // Save source infos
            SDL_GetSurfaceColorMod(src, &r, &g, &b);
            SDL_GetSurfaceAlphaMod(src, &alpha);
            SDL_Get_Surface_Blend_बहुलकम्(src, &blend_बहुलकम्);
            srcrect2.x = srcrect->x;
            srcrect2.y = srcrect->y;
            srcrect2.w = srcrect->w;
            srcrect2.h = srcrect->h;

            // Change source format if not appropriate for scaling
            यदि (SDL_BYTESPERPIXEL(src->format) != 4 || src->format == SDL_PIXELFORMAT_ARGB2101010) {
                SDL_PixelFormat fmt;
                यदि (SDL_BYTESPERPIXEL(dst->format) == 4 && dst->format != SDL_PIXELFORMAT_ARGB2101010 &&
                    (SDL_ISPIXELFORMAT_ALPHA(dst->format) || !is_complex_copy_flags)) {
                    fmt = dst->format;
                } अन्यथा {
                    fmt = SDL_PIXELFORMAT_ARGB8888;
                }
                tmp1 = SDL_ConvertSurfaceRect(src, srcrect, fmt);
                यदि (!tmp1) {
                    प्रत्यागम false;
                }
                src = tmp1;
                srcrect2.x = 0;
                srcrect2.y = 0;
            }

            // Intermediate scaling
            यदि (is_complex_copy_flags || src->format != dst->format) {
                SDL_Rect tmprect;
                SDL_Surface *tmp2 = SDL_CreateSurfaceUninitialized(dstrect->w, dstrect->h, src->format);
                SDL_StretchSurface(src, &srcrect2, tmp2, रिक्त, SDL_SCALEMODE_रैखिकम्);

                SDL_समुच्चयः_Surface_Color_Mod(tmp2, r, g, b);
                SDL_समुच्चयः_Surface_Alpha_Mod(tmp2, alpha);
                SDL_समुच्चयः_Surface_Blend_बहुलकम्(tmp2, blend_बहुलकम्);

                tmprect.x = 0;
                tmprect.y = 0;
                tmprect.w = dstrect->w;
                tmprect.h = dstrect->h;
                परिणाम = SDL_BlitSurfaceUnchecked(tmp2, &tmprect, dst, dstrect);
                SDL_DestroySurface(tmp2);
            } अन्यथा {
                परिणाम = SDL_StretchSurface(src, &srcrect2, dst, dstrect, SDL_SCALEMODE_रैखिकम्);
            }

            SDL_DestroySurface(tmp1);
            प्रत्यागम परिणाम;
        }
    }
}

bool SDL_BlitSurfaceTiled(SDL_Surface *src, ध्रुव SDL_Rect *srcrect, SDL_Surface *dst, ध्रुव SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        प्रत्यागम SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        प्रत्यागम SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        प्रत्यागम SDL_समुच्चयः_Error("Surfaces must not be locked during blit");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    यदि (dstrect) {
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
    यदि (srcrect) {
        यदि (SDL_GetRectIntersection(srcrect, &r_src, &r_src) == false) {
            प्रत्यागम true;
        }

        // For tiling we don't adjust the destination rectangle
    }

    // clip the destination rectangle against the clip rectangle
    {
        यदि (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &r_dst) == false) {
            प्रत्यागम true;
        }

        // For tiling we don't adjust the source rectangle
    }

    // Switch back to a fast blit if we were previously stretching
    यदि (src->map.info.flags & SDL_COPY_निकटतमः) {
        src->map.info.flags &= ~SDL_COPY_निकटतमः;
        SDL_InvalidateMap(&src->map);
    }

    पूर्णाङ्क पङ्क्तिकाः = r_dst.h / r_src.h;
    पूर्णाङ्क स्तम्भसङ्ख्या = r_dst.w / r_src.w;
    पूर्णाङ्क remaining_w = r_dst.w % r_src.w;
    पूर्णाङ्क remaining_h = r_dst.h % r_src.h;
    SDL_Rect curr_src, curr_dst;

    SDL_copyp(&curr_src, &r_src);
    curr_dst.y = r_dst.y;
    curr_dst.w = r_src.w;
    curr_dst.h = r_src.h;
    प्रति (पूर्णाङ्क y = 0; y < पङ्क्तिकाः; ++y) {
        curr_dst.x = r_dst.x;
        प्रति (पूर्णाङ्क x = 0; x < स्तम्भसङ्ख्या; ++x) {
            यदि (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                प्रत्यागम false;
            }
            curr_dst.x += curr_dst.w;
        }
        यदि (remaining_w) {
            curr_src.w = remaining_w;
            curr_dst.w = remaining_w;
            यदि (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                प्रत्यागम false;
            }
            curr_src.w = r_src.w;
            curr_dst.w = r_src.w;
        }
        curr_dst.y += curr_dst.h;
    }
    यदि (remaining_h) {
        curr_src.h = remaining_h;
        curr_dst.h = remaining_h;
        curr_dst.x = r_dst.x;
        प्रति (पूर्णाङ्क x = 0; x < स्तम्भसङ्ख्या; ++x) {
            यदि (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                प्रत्यागम false;
            }
            curr_dst.x += curr_dst.w;
        }
        यदि (remaining_w) {
            curr_src.w = remaining_w;
            curr_dst.w = remaining_w;
            यदि (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                प्रत्यागम false;
            }
        }
    }
    प्रत्यागम true;
}

bool SDL_BlitSurfaceTiledWithScale(SDL_Surface *src, ध्रुव SDL_Rect *srcrect, भिन्न scale, SDL_Scale_बहुलकम् scale_बहुलकम्, SDL_Surface *dst, ध्रुव SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        प्रत्यागम SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        प्रत्यागम SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        प्रत्यागम SDL_समुच्चयः_Error("Surfaces must not be locked during blit");
    }
    CHECK_PARAM(scale < 0.0f) {
        प्रत्यागम SDL_InvalidParamError("scale");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    यदि (dstrect) {
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
    यदि (srcrect) {
        यदि (SDL_GetRectIntersection(srcrect, &r_src, &r_src) == false) {
            प्रत्यागम true;
        }

        // For tiling we don't adjust the destination rectangle
    }

    // clip the destination rectangle against the clip rectangle
    {
        यदि (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &r_dst) == false) {
            प्रत्यागम true;
        }

        // For tiling we don't adjust the source rectangle
    }

    // Switch back to a fast blit if we were previously stretching
    यदि (src->map.info.flags & SDL_COPY_निकटतमः) {
        src->map.info.flags &= ~SDL_COPY_निकटतमः;
        SDL_InvalidateMap(&src->map);
    }

    पूर्णाङ्क tile_विस्तारः = (पूर्णाङ्क)SDL_roundf(r_src.w * scale);
    पूर्णाङ्क tile_height = (पूर्णाङ्क)SDL_roundf(r_src.h * scale);
    यदि (tile_विस्तारः <= 0 || tile_height <= 0) {
        // Nothing to do
        प्रत्यागम true;
    }
    पूर्णाङ्क पङ्क्तिकाः = r_dst.h / tile_height;
    पूर्णाङ्क स्तम्भसङ्ख्या = r_dst.w / tile_विस्तारः;
    पूर्णाङ्क remaining_dst_w = (r_dst.w - स्तम्भसङ्ख्या * tile_विस्तारः);
    पूर्णाङ्क remaining_dst_h = (r_dst.h - पङ्क्तिकाः * tile_height);
    पूर्णाङ्क remaining_src_w = (पूर्णाङ्क)(remaining_dst_w / scale);
    पूर्णाङ्क remaining_src_h = (पूर्णाङ्क)(remaining_dst_h / scale);
    SDL_Rect curr_src, curr_dst;

    SDL_copyp(&curr_src, &r_src);
    curr_dst.y = r_dst.y;
    curr_dst.w = tile_विस्तारः;
    curr_dst.h = tile_height;
    प्रति (पूर्णाङ्क y = 0; y < पङ्क्तिकाः; ++y) {
        curr_dst.x = r_dst.x;
        प्रति (पूर्णाङ्क x = 0; x < स्तम्भसङ्ख्या; ++x) {
            यदि (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scale_बहुलकम्)) {
                प्रत्यागम false;
            }
            curr_dst.x += curr_dst.w;
        }
        यदि (remaining_dst_w > 0) {
            curr_src.w = remaining_src_w;
            curr_dst.w = remaining_dst_w;
            यदि (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scale_बहुलकम्)) {
                प्रत्यागम false;
            }
            curr_src.w = r_src.w;
            curr_dst.w = tile_विस्तारः;
        }
        curr_dst.y += curr_dst.h;
    }
    यदि (remaining_dst_h > 0) {
        curr_src.h = remaining_src_h;
        curr_dst.h = remaining_dst_h;
        curr_dst.x = r_dst.x;
        प्रति (पूर्णाङ्क x = 0; x < स्तम्भसङ्ख्या; ++x) {
            यदि (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scale_बहुलकम्)) {
                प्रत्यागम false;
            }
            curr_dst.x += curr_dst.w;
        }
        यदि (remaining_dst_w > 0) {
            curr_src.w = remaining_src_w;
            curr_dst.w = remaining_dst_w;
            यदि (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scale_बहुलकम्)) {
                प्रत्यागम false;
            }
        }
    }
    प्रत्यागम true;
}

bool SDL_BlitSurface9Grid(SDL_Surface *src, ध्रुव SDL_Rect *srcrect, पूर्णाङ्क वामः_विस्तारः, पूर्णाङ्क दक्षिणः_विस्तारः, पूर्णाङ्क शिखरम्_height, पूर्णाङ्क bottom_height, भिन्न scale, SDL_Scale_बहुलकम् scale_बहुलकम्, SDL_Surface *dst, ध्रुव SDL_Rect *dstrect)
{
    SDL_Rect पूर्णम्_src, पूर्णम्_dst;
    SDL_Rect curr_src, curr_dst;
    पूर्णाङ्क dst_वामः_विस्तारः;
    पूर्णाङ्क dst_दक्षिणः_विस्तारः;
    पूर्णाङ्क dst_शिखरम्_height;
    पूर्णाङ्क dst_bottom_height;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        प्रत्यागम SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        प्रत्यागम SDL_InvalidParamError("dst");
    }

    यदि (!srcrect) {
        पूर्णम्_src.x = 0;
        पूर्णम्_src.y = 0;
        पूर्णम्_src.w = src->w;
        पूर्णम्_src.h = src->h;
        srcrect = &पूर्णम्_src;
    }

    यदि (!dstrect) {
        पूर्णम्_dst.x = 0;
        पूर्णम्_dst.y = 0;
        पूर्णम्_dst.w = dst->w;
        पूर्णम्_dst.h = dst->h;
        dstrect = &पूर्णम्_dst;
    }

    यदि (scale <= 0.0f || scale == 1.0f) {
        dst_वामः_विस्तारः = वामः_विस्तारः;
        dst_दक्षिणः_विस्तारः = दक्षिणः_विस्तारः;
        dst_शिखरम्_height = शिखरम्_height;
        dst_bottom_height = bottom_height;
    } अन्यथा {
        dst_वामः_विस्तारः = (पूर्णाङ्क)SDL_roundf(वामः_विस्तारः * scale);
        dst_दक्षिणः_विस्तारः = (पूर्णाङ्क)SDL_roundf(दक्षिणः_विस्तारः * scale);
        dst_शिखरम्_height = (पूर्णाङ्क)SDL_roundf(शिखरम्_height * scale);
        dst_bottom_height = (पूर्णाङ्क)SDL_roundf(bottom_height * scale);
    }

    // Upper-left corner
    curr_src.x = srcrect->x;
    curr_src.y = srcrect->y;
    curr_src.w = वामः_विस्तारः;
    curr_src.h = शिखरम्_height;
    curr_dst.x = dstrect->x;
    curr_dst.y = dstrect->y;
    curr_dst.w = dst_वामः_विस्तारः;
    curr_dst.h = dst_शिखरम्_height;
    यदि (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_बहुलकम्)) {
        प्रत्यागम false;
    }

    // Upper-right corner
    curr_src.x = srcrect->x + srcrect->w - दक्षिणः_विस्तारः;
    curr_src.w = दक्षिणः_विस्तारः;
    curr_dst.x = dstrect->x + dstrect->w - dst_दक्षिणः_विस्तारः;
    curr_dst.w = dst_दक्षिणः_विस्तारः;
    यदि (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_बहुलकम्)) {
        प्रत्यागम false;
    }

    // Lower-right corner
    curr_src.y = srcrect->y + srcrect->h - bottom_height;
    curr_dst.y = dstrect->y + dstrect->h - dst_bottom_height;
    curr_dst.h = dst_bottom_height;
    यदि (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_बहुलकम्)) {
        प्रत्यागम false;
    }

    // Lower-left corner
    curr_src.x = srcrect->x;
    curr_src.w = वामः_विस्तारः;
    curr_dst.x = dstrect->x;
    curr_dst.w = dst_वामः_विस्तारः;
    यदि (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_बहुलकम्)) {
        प्रत्यागम false;
    }

    //वामः
    curr_src.y = srcrect->y + शिखरम्_height;
    curr_src.h = srcrect->h - शिखरम्_height - bottom_height;
    curr_dst.y = dstrect->y + dst_शिखरम्_height;
    curr_dst.h = dstrect->h - dst_शिखरम्_height - dst_bottom_height;
    यदि (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_बहुलकम्)) {
        प्रत्यागम false;
    }

    //दक्षिणः
    curr_src.x = srcrect->x + srcrect->w - दक्षिणः_विस्तारः;
    curr_src.w = दक्षिणः_विस्तारः;
    curr_dst.x = dstrect->x + dstrect->w - dst_दक्षिणः_विस्तारः;
    curr_dst.w = dst_दक्षिणः_विस्तारः;
    यदि (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_बहुलकम्)) {
        प्रत्यागम false;
    }

    //शिखरम्
    curr_src.x = srcrect->x + वामः_विस्तारः;
    curr_src.y = srcrect->y;
    curr_src.w = srcrect->w - वामः_विस्तारः - दक्षिणः_विस्तारः;
    curr_src.h = शिखरम्_height;
    curr_dst.x = dstrect->x + dst_वामः_विस्तारः;
    curr_dst.y = dstrect->y;
    curr_dst.w = dstrect->w - dst_वामः_विस्तारः - dst_दक्षिणः_विस्तारः;
    curr_dst.h = dst_शिखरम्_height;
    यदि (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_बहुलकम्)) {
        प्रत्यागम false;
    }

    // Bottom
    curr_src.y = srcrect->y + srcrect->h - bottom_height;
    curr_dst.y = dstrect->y + dstrect->h - dst_bottom_height;
    curr_dst.h = dst_bottom_height;
    यदि (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_बहुलकम्)) {
        प्रत्यागम false;
    }

    // Center
    curr_src.x = srcrect->x + वामः_विस्तारः;
    curr_src.y = srcrect->y + शिखरम्_height;
    curr_src.w = srcrect->w - वामः_विस्तारः - दक्षिणः_विस्तारः;
    curr_src.h = srcrect->h - शिखरम्_height - bottom_height;
    curr_dst.x = dstrect->x + dst_वामः_विस्तारः;
    curr_dst.y = dstrect->y + dst_शिखरम्_height;
    curr_dst.w = dstrect->w - dst_वामः_विस्तारः - dst_दक्षिणः_विस्तारः;
    curr_dst.h = dstrect->h - dst_शिखरम्_height - dst_bottom_height;
    यदि (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scale_बहुलकम्)) {
        प्रत्यागम false;
    }

    प्रत्यागम true;
}

/*
 * Lock a surface to directly access the pixels
 */
bool SDL_तालकम्_Surface(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        प्रत्यागम SDL_InvalidParamError("surface");
    }

    यदि (!surface->locked) {
#यदि_परिभाषितम् SDL_HAVE_RLE
        // Perform the lock
        यदि (surface->आन्तरिकम्_flags & SDL_आन्तरिकम्_SURFACE_RLEACCEL) {
            SDL_UnRLESurface(surface);
        }
#यदि_अन्तः
    }

    // Increment the surface lock count, for recursive locks
    ++surface->locked;
    surface->flags |= SDL_SURFACE_LOCKED;
    SDL_Update_Surface_तालकम्_Flag(surface);

    // Ready to go..
    प्रत्यागम true;
}

/*
 * Unlock a previously locked surface
 */
शून्य SDL_UnlockSurface(SDL_Surface *surface)
{
    यदि (!SDL_SurfaceValid(surface)) {
        प्रत्यागम;
    }

    // Only perform an unlock if we are locked
    यदि (!surface->locked || (--surface->locked > 0)) {
        प्रत्यागम;
    }

    surface->flags &= ~SDL_SURFACE_LOCKED;
    SDL_Update_Surface_तालकम्_Flag(surface);
}

स्थिर bool SDL_FlipSurfaceHorizontal(SDL_Surface *surface)
{
    bool isstack;
    Uint8 *row, *a, *b, *tmp;
    पूर्णाङ्क i, j, bpp;

    यदि (SDL_BITSPERPIXEL(surface->format) < 8) {
        // We could implement this if needed, but we'd have to flip sets of bits within a byte
        प्रत्यागम SDL_Unsupported();
    }

    यदि (surface->h <= 0) {
        प्रत्यागम true;
    }

    यदि (surface->w <= 1) {
        प्रत्यागम true;
    }

    bpp = SDL_BYTESPERPIXEL(surface->format);
    row = (Uint8 *)surface->pixels;
    tmp = SDL_small_alloc(Uint8, surface->pitch, &isstack);
    यदि (!tmp) {
        प्रत्यागम false;
    }
    प्रति (i = surface->h; i--; ) {
        a = row;
        b = a + (surface->w - 1) * bpp;
        प्रति (j = surface->w / 2; j--; ) {
            SDL_memcpy(tmp, a, bpp);
            SDL_memcpy(a, b, bpp);
            SDL_memcpy(b, tmp, bpp);
            a += bpp;
            b -= bpp;
        }
        row += surface->pitch;
    }
    SDL_small_free(tmp, isstack);
    प्रत्यागम true;
}

स्थिर bool SDL_FlipSurfaceVertical(SDL_Surface *surface)
{
    bool isstack;
    Uint8 *a, *b, *tmp;
    पूर्णाङ्क i;

    यदि (surface->h <= 1) {
        प्रत्यागम true;
    }

    a = (Uint8 *)surface->pixels;
    b = a + (surface->h - 1) * surface->pitch;
    tmp = SDL_small_alloc(Uint8, surface->pitch, &isstack);
    यदि (!tmp) {
        प्रत्यागम false;
    }
    प्रति (i = surface->h / 2; i--; ) {
        SDL_memcpy(tmp, a, surface->pitch);
        SDL_memcpy(a, b, surface->pitch);
        SDL_memcpy(b, tmp, surface->pitch);
        a += surface->pitch;
        b -= surface->pitch;
    }
    SDL_small_free(tmp, isstack);
    प्रत्यागम true;
}

bool SDL_FlipSurface(SDL_Surface *surface, SDL_Flip_बहुलकम् flip)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        प्रत्यागम SDL_InvalidParamError("surface");
    }
    यदि (!surface->pixels) {
        प्रत्यागम true;
    }

    bool परिणाम = true;
    विकल्प (flip) {
    पक्ष SDL_FLIP_HORIZONTAL:
        परिणाम = SDL_FlipSurfaceHorizontal(surface);
        भङ्ग;
    पक्ष SDL_FLIP_VERTICAL:
        परिणाम = SDL_FlipSurfaceVertical(surface);
        भङ्ग;
    पक्ष SDL_FLIP_HORIZONTAL_AND_VERTICAL:
        परिणाम &= SDL_FlipSurfaceHorizontal(surface);
        परिणाम &= SDL_FlipSurfaceVertical(surface);
        भङ्ग;
    स्वभाव:
        परिणाम = SDL_InvalidParamError("flip");
        भङ्ग;
    }
    प्रत्यागम परिणाम;
}

स्थिर SDL_Surface *SDL_ConvertSurfaceRectAndColorspace(SDL_Surface *surface, ध्रुव SDL_Rect *rect, SDL_PixelFormat format, SDL_Palette *palette, SDL_Colorspace colorspace, SDL_PropertiesID props)
{
    SDL_Palette *अस्थायी_palette = रिक्त;
    SDL_Surface *convert = रिक्त;
    SDL_Colorspace src_colorspace;
    SDL_PropertiesID src_properties;
    Uint32 copy_flags;
    SDL_Color copy_color;
    SDL_Rect bounds;
    bool परिणाम;
    bool palette_ck_transform = false;
    Uint8 palette_ck_मानम् = 0;
    Uint8 *palette_saved_alpha = रिक्त;
    पूर्णाङ्क palette_saved_alpha_ncolors = 0;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        गच्छ error;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        गच्छ error;
    }

    // Set the bounds of the new surface
    bounds.x = 0;
    bounds.y = 0;
    bounds.w = surface->w;
    bounds.h = surface->h;
    यदि (rect) {
        bounds.w = rect->w;
        bounds.h = rect->h;
    } अन्यथा {
        rect = &bounds;
    }

    // Check for empty destination palette! (results in empty image)
    यदि (palette) {
        पूर्णाङ्क i;
        प्रति (i = 0; i < palette->ncolors; ++i) {
            यदि ((palette->colors[i].r != 0xFF) || (palette->colors[i].g != 0xFF) || (palette->colors[i].b != 0xFF)) {
                भङ्ग;
            }
        }
        यदि (i == palette->ncolors) {
            SDL_समुच्चयः_Error("Empty destination palette");
            गच्छ error;
        }
    } अन्यथा यदि (SDL_ISPIXELFORMAT_अनुक्रमितम्(format)) {
        // Create a dither palette for conversion
        अस्थायी_palette = SDL_CreatePalette(1 << SDL_BITSPERPIXEL(format));
        यदि (अस्थायी_palette) {
            SDL_DitherPalette(अस्थायी_palette);
            palette = अस्थायी_palette;
        }
    }

    src_colorspace = surface->colorspace;
    src_properties = surface->props;

    // Create a new surface with the desired format
    यदि (surface->pixels || SDL_MUSTLOCK(surface)) {
        convert = SDL_CreateSurfaceUninitialized(rect->w, rect->h, format);
    } अन्यथा {
        convert = SDL_CreateSurfaceFrom(rect->w, rect->h, format, रिक्त, 0);
    }
    यदि (!convert) {
        गच्छ error;
    }
    यदि (SDL_ISPIXELFORMAT_अनुक्रमितम्(format)) {
        SDL_समुच्चयः_Surface_Palette(convert, palette);
    }

    यदि (colorspace == SDL_COLORSPACE_UNKNOWN) {
        colorspace = src_colorspace;
    }
    SDL_समुच्चयः_Surface_Colorspace(convert, colorspace);

    यदि (SDL_ISPIXELFORMAT_FOURCC(format) || SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        यदि (surface->format == SDL_PIXELFORMAT_MJPG && format == SDL_PIXELFORMAT_MJPG) {
            // Just do a straight pixel copy of the JPEG image
            size_t आकार = (size_t)surface->pitch;
            convert->pixels = SDL_malloc(आकार);
            यदि (!convert->pixels) {
                गच्छ error;
            }
            convert->flags &= ~SDL_SURFACE_PREALLOCATED;
            convert->pitch = surface->pitch;
            SDL_memcpy(convert->pixels, surface->pixels, आकार);

        } अन्यथा यदि (!SDL_ConvertPixelsAndColorspace(surface->w, surface->h, surface->format, src_colorspace, src_properties, surface->pixels, surface->pitch, convert->format, colorspace, props, convert->pixels, convert->pitch)) {
            गच्छ error;
        }

        // Save the original copy flags
        copy_flags = surface->map.info.flags;

        गच्छ अन्तः;
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
    यदि (surface->palette && SDL_ISPIXELFORMAT_ALPHA(format)) {
        bool समुच्चयः_opaque = false;

        bool is_opaque, has_alpha_channel;
        SDL_DetectPalette(surface->palette, &is_opaque, &has_alpha_channel);

        यदि (is_opaque) {
            यदि (!has_alpha_channel) {
                समुच्चयः_opaque = true;
            }
        }

        // Set opaque and backup palette alpha values
        यदि (समुच्चयः_opaque) {
            पूर्णाङ्क i;
            palette_saved_alpha_ncolors = surface->palette->ncolors;
            यदि (palette_saved_alpha_ncolors > 0) {
                palette_saved_alpha = SDL_राशिः_alloc(Uint8, palette_saved_alpha_ncolors);
                प्रति (i = 0; i < palette_saved_alpha_ncolors; i++) {
                    palette_saved_alpha[i] = surface->palette->colors[i].a;
                    surface->palette->colors[i].a = SDL_ALPHA_OPAQUE;
                }
            }
        }
    }

    // Transform colorkey to alpha. for cases where source palette has duplicate values, and colorkey is one of them
    यदि (copy_flags & SDL_COPY_COLORKEY) {
        यदि (surface->palette && !palette) {
            palette_ck_transform = true;
            palette_ck_मानम् = surface->palette->colors[surface->map.info.colorkey].a;
            surface->palette->colors[surface->map.info.colorkey].a = SDL_ALPHA_TRANSPARENT;
        }
    }

    यदि (surface->pixels || SDL_MUSTLOCK(surface)) {
        परिणाम = SDL_BlitSurfaceUnchecked(surface, rect, convert, &bounds);
    } अन्यथा {
        परिणाम = true;
    }

    // Restore colorkey alpha value
    यदि (palette_ck_transform) {
        surface->palette->colors[surface->map.info.colorkey].a = palette_ck_मानम्;
    }

    // Restore palette alpha values
    यदि (palette_saved_alpha) {
        पूर्णाङ्क i;
        प्रति (i = 0; i < palette_saved_alpha_ncolors; i++) {
            surface->palette->colors[i].a = palette_saved_alpha[i];
        }
        SDL_राशिः_free(palette_saved_alpha);
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
    यदि (!परिणाम) {
        गच्छ error;
    }

    यदि (copy_flags & SDL_COPY_COLORKEY) {
        bool समुच्चयः_colorkey_by_color = false;
        bool convert_colorkey = true;

        यदि (surface->palette) {
            यदि (palette &&
                surface->palette->ncolors <= palette->ncolors &&
                (SDL_memcmp(surface->palette->colors, palette->colors,
                            surface->palette->ncolors * परिमाण(SDL_Color)) == 0)) {
                // The palette is identical, just set the same colorkey
                SDL_समुच्चयः_Surface_Color_कुञ्चिका(convert, true, surface->map.info.colorkey);
            } अन्यथा यदि (!palette) {
                यदि (SDL_ISPIXELFORMAT_ALPHA(format)) {
                    // No need to add the colorkey, transparency is in the alpha channel
                } अन्यथा {
                    // Only set the colorkey information
                    समुच्चयः_colorkey_by_color = true;
                    convert_colorkey = false;
                }
            } अन्यथा {
                समुच्चयः_colorkey_by_color = true;
            }
        } अन्यथा {
            समुच्चयः_colorkey_by_color = true;
        }

        यदि (समुच्चयः_colorkey_by_color) {
            SDL_Surface *tmp;
            SDL_Surface *tmp2;
            पूर्णाङ्क converted_colorkey = 0;

            // Create a dummy surface to get the colorkey converted
            tmp = SDL_CreateSurfaceUninitialized(1, 1, surface->format);
            यदि (!tmp) {
                गच्छ error;
            }

            // Share the palette, if any
            यदि (surface->palette) {
                SDL_समुच्चयः_Surface_Palette(tmp, surface->palette);
            }

            SDL_FillSurfaceRect(tmp, रिक्त, surface->map.info.colorkey);

            tmp->map.info.flags &= ~SDL_COPY_COLORKEY;

            // Conversion of the colorkey
            tmp2 = SDL_ConvertSurfaceAndColorspace(tmp, format, palette, colorspace, props);
            यदि (!tmp2) {
                SDL_DestroySurface(tmp);
                गच्छ error;
            }

            // Get the converted colorkey
            SDL_memcpy(&converted_colorkey, tmp2->pixels, tmp2->fmt->अष्टकानि_प्रत्येकम्_pixel);

            SDL_DestroySurface(tmp);
            SDL_DestroySurface(tmp2);

            // Set the converted colorkey on the new surface
            SDL_समुच्चयः_Surface_Color_कुञ्चिका(convert, true, converted_colorkey);

            // This is needed when converting for 3D texture upload
            यदि (convert_colorkey) {
                SDL_Convert_Colorkey_गन्तव्यम्_Alpha(convert, true);
            }
        }
    }

अन्तः:
    यदि (अस्थायी_palette) {
        SDL_DestroyPalette(अस्थायी_palette);
    }

    SDL_समुच्चयः_Surface_Clip_Rect(convert, &surface->clip_rect);

    /* Enable alpha blending by default if the new surface has an
     * alpha channel or alpha modulation */
    यदि (SDL_ISPIXELFORMAT_ALPHA(format) ||
        (copy_flags & SDL_COPY_MODULATE_ALPHA)) {
        SDL_समुच्चयः_Surface_Blend_बहुलकम्(convert, SDL_BLENDMODE_BLEND);
    }
    यदि (copy_flags & SDL_COPY_RLE_DESIRED) {
        SDL_समुच्चयः_Surface_RLE(convert, true);
    }

    // Copy alternate images
    प्रति (पूर्णाङ्क i = 0; i < surface->अङ्कः_images; ++i) {
        यदि (!SDL_सङ्कलय_Surface_Alternate_Image(convert, surface->images[i])) {
            गच्छ error;
        }
    }

    // Copy properties
    यदि (surface->props) {
        यदि (!SDL_CopyProperties(surface->props, SDL_GetSurfaceProperties(convert))) {
            गच्छ error;
        }

        // Make sure the new surface doesn't reference an old SDL2 surface.
        SDL_ClearProperty(SDL_GetSurfaceProperties(convert), "sdl2-compat.surface2");
    }

    // We're ready to go!
    प्रत्यागम convert;

error:
    यदि (अस्थायी_palette) {
        SDL_DestroyPalette(अस्थायी_palette);
    }
    यदि (convert) {
        SDL_DestroySurface(convert);
    }
    प्रत्यागम रिक्त;
}

SDL_Surface *SDL_ConvertSurfaceAndColorspace(SDL_Surface *surface, SDL_PixelFormat format, SDL_Palette *palette, SDL_Colorspace colorspace, SDL_PropertiesID props)
{
    प्रत्यागम SDL_ConvertSurfaceRectAndColorspace(surface, रिक्त, format, palette, colorspace, props);
}

SDL_Surface *SDL_RotateSurface(SDL_Surface *surface, भिन्न angle)
{
    SDL_Surface *rotated = रिक्त;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        प्रत्यागम रिक्त;
    }

    SDL_Rect rect_dest;
    द्विगुण cangle, sangle;
    SDL_FPoint center = { surface->w * 0.5f, surface->h * 0.5f };
    SDLgfx_rotozoom_Surface_आकार_Trig(surface->w, surface->h, angle, &center, &rect_dest, &cangle, &sangle);

    // This function requires a 32-bit surface or 8-bit surface with a colorkey
    यदि ((SDL_BITSPERPIXEL(surface->format) == 32 && SDL_PIXELLAYOUT(surface->format) == SDL_PACKEDLAYOUT_8888) ||
        (surface->format == SDL_PIXELFORMAT_INDEX8 && SDL_Surface_Has_Color_कुञ्चिका(surface))) {
        rotated = SDLgfx_rotateSurface(surface, angle, 1, 0, 0, &rect_dest, cangle, sangle, &center);
    } अन्यथा {
        SDL_Surface *convert = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);
        यदि (convert) {
            SDL_Surface *tmp = SDLgfx_rotateSurface(convert, angle, 1, 0, 0, &rect_dest, cangle, sangle, &center);
            यदि (tmp) {
                rotated = SDL_ConvertSurfaceAndColorspace(tmp, surface->format, surface->palette, surface->colorspace, surface->props);
                SDL_DestroySurface(tmp);
            }
            SDL_DestroySurface(convert);
        }
    }

    यदि (rotated) {
        यदि (SDL_HasProperty(surface->props, SDL_PROP_SURFACE_ROTATION_FLOAT)) {
            ध्रुव भिन्न rotation = (SDL_Get_सङ्ख्या_Property(surface->props, SDL_PROP_SURFACE_ROTATION_FLOAT, 0) - angle);
            SDL_समुच्चयः_Float_Property(SDL_GetSurfaceProperties(rotated), SDL_PROP_SURFACE_ROTATION_FLOAT, rotation);
        }
    }

    प्रत्यागम rotated;
}

SDL_Surface *SDL_DuplicateSurface(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        प्रत्यागम रिक्त;
    }

    प्रत्यागम SDL_ConvertSurfaceAndColorspace(surface, surface->format, surface->palette, surface->colorspace, surface->props);
}

SDL_Surface *SDL_ScaleSurface(SDL_Surface *surface, पूर्णाङ्क विस्तारः, पूर्णाङ्क height, SDL_Scale_बहुलकम् scale_बहुलकम्)
{
    SDL_Surface *convert = रिक्त;
    Uint32 copy_flags;
    SDL_Color copy_color;
    bool rc;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        गच्छ error;
    }

    यदि (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // We can't directly scale a YUV surface (yet!)
        SDL_Surface *tmp = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        यदि (!tmp) {
            प्रत्यागम रिक्त;
        }

        SDL_Surface *scaled = SDL_ScaleSurface(tmp, विस्तारः, height, scale_बहुलकम्);
        SDL_DestroySurface(tmp);
        यदि (!scaled) {
            प्रत्यागम रिक्त;
        }

        SDL_Surface *परिणाम = SDL_ConvertSurfaceAndColorspace(scaled, surface->format, रिक्त, surface->colorspace, surface->props);
        SDL_DestroySurface(scaled);
        प्रत्यागम परिणाम;
    }

    यदि (SDL_ISPIXELFORMAT_अनुक्रमितम्(surface->format)) {
        // Linear scaling requires conversion to RGBA and then slow pixel color lookup
        scale_बहुलकम् = SDL_SCALEMODE_निकटतमः;
    }

    // Create a new surface with the desired size
    यदि (surface->pixels || SDL_MUSTLOCK(surface)) {
        convert = SDL_CreateSurfaceUninitialized(विस्तारः, height, surface->format);
    } अन्यथा {
        convert = SDL_CreateSurfaceFrom(विस्तारः, height, surface->format, रिक्त, 0);
    }
    यदि (!convert) {
        गच्छ error;
    }
    SDL_समुच्चयः_Surface_Palette(convert, surface->palette);
    SDL_समुच्चयः_Surface_Colorspace(convert, surface->colorspace);
    SDL_समुच्चयः_Surface_RLE(convert, SDL_SurfaceHasRLE(surface));

    यदि (surface->pixels || SDL_MUSTLOCK(surface)) {
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

        rc = SDL_BlitSurfaceScaled(surface, रिक्त, convert, रिक्त, scale_बहुलकम्);

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
    यदि (!rc) {
        गच्छ error;
    }

    // We're ready to go!
    प्रत्यागम convert;

error:
    यदि (convert) {
        SDL_DestroySurface(convert);
    }
    प्रत्यागम रिक्त;
}

SDL_Surface *SDL_ConvertSurfaceRect(SDL_Surface *surface, ध्रुव SDL_Rect *rect, SDL_PixelFormat format)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        प्रत्यागम रिक्त;
    }

    प्रत्यागम SDL_ConvertSurfaceRectAndColorspace(surface, rect, format, रिक्त, SDL_GetDefaultColorspaceForFormat(format), surface->props);
}

SDL_Surface *SDL_ConvertSurface(SDL_Surface *surface, SDL_PixelFormat format)
{
    प्रत्यागम SDL_ConvertSurfaceRect(surface, रिक्त, format);
}

SDL_Surface *SDL_DuplicatePixels(पूर्णाङ्क विस्तारः, पूर्णाङ्क height, SDL_PixelFormat format, SDL_Colorspace colorspace, शून्य *pixels, पूर्णाङ्क pitch)
{
    SDL_Surface *surface;
    यदि (pixels) {
        surface = SDL_CreateSurfaceUninitialized(विस्तारः, height, format);
    } अन्यथा {
        surface = SDL_CreateSurfaceFrom(विस्तारः, height, format, रिक्त, 0);
    }
    यदि (!surface) {
        प्रत्यागम रिक्त;
    }
    SDL_समुच्चयः_Surface_Colorspace(surface, colorspace);

    यदि (surface->pixels) {
        पूर्णाङ्क दीर्घता = विस्तारः * SDL_BYTESPERPIXEL(format);
        Uint8 *src = (Uint8 *)pixels;
        Uint8 *dst = (Uint8 *)surface->pixels;
        पूर्णाङ्क पङ्क्तिकाः = height;
        यावत् (पङ्क्तिकाः--) {
            SDL_memcpy(dst, src, दीर्घता);
            dst += surface->pitch;
            src += pitch;
        }
    }
    प्रत्यागम surface;
}

bool SDL_ConvertPixelsAndColorspace(पूर्णाङ्क विस्तारः, पूर्णाङ्क height,
                      SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ध्रुव शून्य *src, पूर्णाङ्क src_pitch,
                      SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, शून्य *dst, पूर्णाङ्क dst_pitch)
{
    SDL_Surface src_surface;
    SDL_Surface dst_surface;
    SDL_Rect rect;
    शून्य *nonconst_src = (शून्य *)src;
    bool परिणाम;

    CHECK_PARAM(!src) {
        प्रत्यागम SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!src_pitch) {
        प्रत्यागम SDL_InvalidParamError("src_pitch");
    }
    CHECK_PARAM(!dst) {
        प्रत्यागम SDL_InvalidParamError("dst");
    }
    CHECK_PARAM(!dst_pitch) {
        प्रत्यागम SDL_InvalidParamError("dst_pitch");
    }

    यदि (src_colorspace == SDL_COLORSPACE_UNKNOWN) {
        src_colorspace = SDL_GetDefaultColorspaceForFormat(src_format);
    }
    यदि (dst_colorspace == SDL_COLORSPACE_UNKNOWN) {
        dst_colorspace = SDL_GetDefaultColorspaceForFormat(dst_format);
    }

    यदि (src_format == SDL_PIXELFORMAT_MJPG) {
        प्रत्यागम SDL_ConvertPixels_STB(विस्तारः, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    }

#यदि_परिभाषितम् SDL_HAVE_YUV
    यदि (SDL_ISPIXELFORMAT_FOURCC(src_format) && SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        प्रत्यागम SDL_Convert_Pixels_YUV_गन्तव्यम्_YUV(विस्तारः, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } अन्यथा यदि (SDL_ISPIXELFORMAT_FOURCC(src_format)) {
        प्रत्यागम SDL_Convert_Pixels_YUV_गन्तव्यम्_RGB(विस्तारः, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } अन्यथा यदि (SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        प्रत्यागम SDL_Convert_Pixels_RGB_गन्तव्यम्_YUV(विस्तारः, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    }
#अन्यथा
    यदि (SDL_ISPIXELFORMAT_FOURCC(src_format) || SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        प्रत्यागम SDL_समुच्चयः_Error("SDL not built with YUV support");
    }
#यदि_अन्तः

    // Fast path for same format copy
    यदि (src_format == dst_format && src_colorspace == dst_colorspace) {
        यदि (src_pitch == dst_pitch) {
            SDL_memcpy(dst, src, height * src_pitch);
        } अन्यथा {
            पूर्णाङ्क i;
            ध्रुव पूर्णाङ्क bpp = SDL_BYTESPERPIXEL(src_format);
            विस्तारः *= bpp;
            प्रति (i = height; i--;) {
                SDL_memcpy(dst, src, विस्तारः);
                src = (ध्रुव Uint8 *)src + src_pitch;
                dst = (Uint8 *)dst + dst_pitch;
            }
        }
        प्रत्यागम true;
    }

    यदि (!SDL_InitializeSurface(&src_surface, विस्तारः, height, src_format, src_colorspace, src_properties, nonconst_src, src_pitch, true)) {
        प्रत्यागम false;
    }
    SDL_समुच्चयः_Surface_Blend_बहुलकम्(&src_surface, SDL_BLENDMODE_NONE);

    यदि (!SDL_InitializeSurface(&dst_surface, विस्तारः, height, dst_format, dst_colorspace, dst_properties, dst, dst_pitch, true)) {
        प्रत्यागम false;
    }

    // Set up the rect and go!
    rect.x = 0;
    rect.y = 0;
    rect.w = विस्तारः;
    rect.h = height;
    परिणाम = SDL_BlitSurfaceUnchecked(&src_surface, &rect, &dst_surface, &rect);

    SDL_DestroySurface(&src_surface);
    SDL_DestroySurface(&dst_surface);

    प्रत्यागम परिणाम;
}

bool SDL_ConvertPixels(पूर्णाङ्क विस्तारः, पूर्णाङ्क height, SDL_PixelFormat src_format, ध्रुव शून्य *src, पूर्णाङ्क src_pitch, SDL_PixelFormat dst_format, शून्य *dst, पूर्णाङ्क dst_pitch)
{
    प्रत्यागम SDL_ConvertPixelsAndColorspace(विस्तारः, height,
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

स्थिर शून्य SDL_PremultiplyAlpha_AXYZ8888(पूर्णाङ्क विस्तारः, पूर्णाङ्क height, ध्रुव शून्य *src, पूर्णाङ्क src_pitch, शून्य *dst, पूर्णाङ्क dst_pitch)
{
    पूर्णाङ्क c;
    Uint32 srcpixel;
    Uint32 srcR, srcG, srcB, srcA;
    Uint32 dstpixel;
    Uint32 dstR, dstG, dstB, dstA;

    यावत् (height--) {
        ध्रुव Uint32 *src_px = (ध्रुव Uint32 *)src;
        Uint32 *dst_px = (Uint32 *)dst;
        प्रति (c = विस्तारः; c; --c) {
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
        src = (ध्रुव Uint8 *)src + src_pitch;
        dst = (Uint8 *)dst + dst_pitch;
    }
}

स्थिर शून्य SDL_PremultiplyAlpha_XYZA8888(पूर्णाङ्क विस्तारः, पूर्णाङ्क height, ध्रुव शून्य *src, पूर्णाङ्क src_pitch, शून्य *dst, पूर्णाङ्क dst_pitch)
{
    पूर्णाङ्क c;
    Uint32 srcpixel;
    Uint32 srcR, srcG, srcB, srcA;
    Uint32 dstpixel;
    Uint32 dstR, dstG, dstB, dstA;

    यावत् (height--) {
        ध्रुव Uint32 *src_px = (ध्रुव Uint32 *)src;
        Uint32 *dst_px = (Uint32 *)dst;
        प्रति (c = विस्तारः; c; --c) {
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
        src = (ध्रुव Uint8 *)src + src_pitch;
        dst = (Uint8 *)dst + dst_pitch;
    }
}

स्थिर शून्य SDL_PremultiplyAlpha_AXYZ128(पूर्णाङ्क विस्तारः, पूर्णाङ्क height, ध्रुव शून्य *src, पूर्णाङ्क src_pitch, शून्य *dst, पूर्णाङ्क dst_pitch)
{
    पूर्णाङ्क c;
    भिन्न flR, flG, flB, flA;

    यावत् (height--) {
        ध्रुव भिन्न *src_px = (ध्रुव भिन्न *)src;
        भिन्न *dst_px = (भिन्न *)dst;
        प्रति (c = विस्तारः; c; --c) {
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
        src = (ध्रुव Uint8 *)src + src_pitch;
        dst = (Uint8 *)dst + dst_pitch;
    }
}

स्थिर bool SDL_PremultiplyAlphaPixelsAndColorspace(पूर्णाङ्क विस्तारः, पूर्णाङ्क height, SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ध्रुव शून्य *src, पूर्णाङ्क src_pitch, SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, शून्य *dst, पूर्णाङ्क dst_pitch, bool रैखिकम्)
{
    SDL_Surface *convert = रिक्त;
    शून्य *final_dst = dst;
    पूर्णाङ्क final_dst_pitch = dst_pitch;
    SDL_PixelFormat format;
    SDL_Colorspace colorspace;
    bool परिणाम = false;

    CHECK_PARAM(!src) {
        प्रत्यागम SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!src_pitch) {
        प्रत्यागम SDL_InvalidParamError("src_pitch");
    }
    CHECK_PARAM(!dst) {
        प्रत्यागम SDL_InvalidParamError("dst");
    }
    CHECK_PARAM(!dst_pitch) {
        प्रत्यागम SDL_InvalidParamError("dst_pitch");
    }

    // Use a high precision format if we're converting to linear colorspace or using high precision pixel formats
    यदि (रैखिकम् ||
        SDL_ISPIXELFORMAT_10BIT(src_format) || SDL_BITSPERPIXEL(src_format) > 32 ||
        SDL_ISPIXELFORMAT_10BIT(dst_format) || SDL_BITSPERPIXEL(dst_format) > 32) {
        यदि (src_format == SDL_PIXELFORMAT_ARGB128_FLOAT ||
            src_format == SDL_PIXELFORMAT_ABGR128_FLOAT) {
            format = src_format;
        } अन्यथा {
            format = SDL_PIXELFORMAT_ARGB128_FLOAT;
        }
    } अन्यथा {
        यदि (src_format == SDL_PIXELFORMAT_ARGB8888 ||
            src_format == SDL_PIXELFORMAT_ABGR8888 ||
            src_format == SDL_PIXELFORMAT_RGBA8888 ||
            src_format == SDL_PIXELFORMAT_BGRA8888) {
            format = src_format;
        } अन्यथा {
            format = SDL_PIXELFORMAT_ARGB8888;
        }
    }
    यदि (रैखिकम्) {
        colorspace = SDL_COLORSPACE_SRGB_रैखिकम्;
    } अन्यथा {
        colorspace = SDL_COLORSPACE_SRGB;
    }

    यदि (src_format != format || src_colorspace != colorspace) {
        convert = SDL_CreateSurfaceUninitialized(विस्तारः, height, format);
        यदि (!convert) {
            गच्छ समाप्तम्;
        }
        यदि (!SDL_ConvertPixelsAndColorspace(विस्तारः, height, src_format, src_colorspace, src_properties, src, src_pitch, format, colorspace, 0, convert->pixels, convert->pitch)) {
            गच्छ समाप्तम्;
        }

        src = convert->pixels;
        src_pitch = convert->pitch;
        dst = convert->pixels;
        dst_pitch = convert->pitch;

    } अन्यथा यदि (dst_format != format || dst_colorspace != colorspace) {
        convert = SDL_CreateSurfaceUninitialized(विस्तारः, height, format);
        यदि (!convert) {
            गच्छ समाप्तम्;
        }
        dst = convert->pixels;
        dst_pitch = convert->pitch;
    }

    विकल्प (format) {
    पक्ष SDL_PIXELFORMAT_ARGB8888:
    पक्ष SDL_PIXELFORMAT_ABGR8888:
        SDL_PremultiplyAlpha_AXYZ8888(विस्तारः, height, src, src_pitch, dst, dst_pitch);
        भङ्ग;
    पक्ष SDL_PIXELFORMAT_RGBA8888:
    पक्ष SDL_PIXELFORMAT_BGRA8888:
        SDL_PremultiplyAlpha_XYZA8888(विस्तारः, height, src, src_pitch, dst, dst_pitch);
        भङ्ग;
    पक्ष SDL_PIXELFORMAT_ARGB128_FLOAT:
    पक्ष SDL_PIXELFORMAT_ABGR128_FLOAT:
        SDL_PremultiplyAlpha_AXYZ128(विस्तारः, height, src, src_pitch, dst, dst_pitch);
        भङ्ग;
    स्वभाव:
        SDL_समुच्चयः_Error("Unexpected internal pixel format");
        गच्छ समाप्तम्;
    }

    यदि (dst != final_dst) {
        यदि (!SDL_ConvertPixelsAndColorspace(विस्तारः, height, format, colorspace, 0, convert->pixels, convert->pitch, dst_format, dst_colorspace, dst_properties, final_dst, final_dst_pitch)) {
            गच्छ समाप्तम्;
        }
    }
    परिणाम = true;

समाप्तम्:
    यदि (convert) {
        SDL_DestroySurface(convert);
    }
    प्रत्यागम परिणाम;
}

bool SDL_PremultiplyAlpha(पूर्णाङ्क विस्तारः, पूर्णाङ्क height,
                         SDL_PixelFormat src_format, ध्रुव शून्य *src, पूर्णाङ्क src_pitch,
                         SDL_PixelFormat dst_format, शून्य *dst, पूर्णाङ्क dst_pitch, bool रैखिकम्)
{
    SDL_Colorspace src_colorspace = SDL_GetDefaultColorspaceForFormat(src_format);
    SDL_Colorspace dst_colorspace = SDL_GetDefaultColorspaceForFormat(dst_format);

    प्रत्यागम SDL_PremultiplyAlphaPixelsAndColorspace(विस्तारः, height, src_format, src_colorspace, 0, src, src_pitch, dst_format, dst_colorspace, 0, dst, dst_pitch, रैखिकम्);
}

bool SDL_PremultiplySurfaceAlpha(SDL_Surface *surface, bool रैखिकम्)
{
    SDL_Colorspace colorspace;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        प्रत्यागम SDL_InvalidParamError("surface");
    }

    colorspace = surface->colorspace;

    प्रत्यागम SDL_PremultiplyAlphaPixelsAndColorspace(surface->w, surface->h, surface->format, colorspace, surface->props, surface->pixels, surface->pitch, surface->format, colorspace, surface->props, surface->pixels, surface->pitch, रैखिकम्);
}

bool SDL_ClearSurface(SDL_Surface *surface, भिन्न r, भिन्न g, भिन्न b, भिन्न a)
{
    SDL_Rect clip_rect;
    bool परिणाम = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        प्रत्यागम SDL_InvalidParamError("surface");
    }

    SDL_GetSurfaceClipRect(surface, &clip_rect);
    SDL_समुच्चयः_Surface_Clip_Rect(surface, रिक्त);

    यदि (!SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_BYTESPERPIXEL(surface->format) <= परिमाण(Uint32)) {
        Uint32 color;

        color = SDL_MapSurfaceRGBA(surface,
                    (Uint8)SDL_roundf(SDL_clamp(r, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(g, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(b, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(a, 0.0f, 1.0f) * 255.0f));
        परिणाम = SDL_FillSurfaceRect(surface, रिक्त, color);
    } अन्यथा यदि (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // We can't directly set an RGB value on a YUV surface
        SDL_Surface *tmp = SDL_CreateSurfaceUninitialized(surface->w, surface->h, SDL_PIXELFORMAT_ARGB8888);
        यदि (!tmp) {
            गच्छ समाप्तम्;
        }

        यदि (SDL_ClearSurface(tmp, r, g, b, a)) {
            परिणाम = SDL_ConvertPixelsAndColorspace(surface->w, surface->h, tmp->format, tmp->colorspace, tmp->props, tmp->pixels, tmp->pitch, surface->format, surface->colorspace, surface->props, surface->pixels, surface->pitch);
        }
        SDL_DestroySurface(tmp);
    } अन्यथा {
        // Take advantage of blit color conversion
        SDL_Surface *tmp = SDL_CreateSurfaceUninitialized(1, 1, SDL_PIXELFORMAT_RGBA128_FLOAT);
        यदि (!tmp) {
            गच्छ समाप्तम्;
        }
        SDL_समुच्चयः_Surface_Colorspace(tmp, surface->colorspace);
        SDL_समुच्चयः_Surface_Blend_बहुलकम्(tmp, SDL_BLENDMODE_NONE);

        भिन्न *pixels = (भिन्न *)tmp->pixels;
        pixels[0] = r;
        pixels[1] = g;
        pixels[2] = b;
        pixels[3] = a;

        परिणाम = SDL_BlitSurfaceScaled(tmp, रिक्त, surface, रिक्त, SDL_SCALEMODE_निकटतमः);
        SDL_DestroySurface(tmp);
    }

समाप्तम्:
    SDL_समुच्चयः_Surface_Clip_Rect(surface, &clip_rect);

    प्रत्यागम परिणाम;
}

Uint32 SDL_MapSurfaceRGB(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b)
{
    प्रत्यागम SDL_MapSurfaceRGBA(surface, r, g, b, SDL_ALPHA_OPAQUE);
}

Uint32 SDL_MapSurfaceRGBA(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        प्रत्यागम true;
    }
    प्रत्यागम SDL_MapRGBA(surface->fmt, surface->palette, r, g, b, a);
}

// This function Copyright 2023 Collabora Ltd., contributed to SDL under the ZLib license
bool SDL_ReadSurfacePixel(SDL_Surface *surface, पूर्णाङ्क x, पूर्णाङ्क y, Uint8 *r, Uint8 *g, Uint8 *b, Uint8 *a)
{
    Uint32 pixel = 0;
    size_t अष्टकानि_प्रत्येकम्_pixel;
    Uint8 अप्रयुक्तम्;
    Uint8 *p;
    bool परिणाम = false;

    यदि (r) {
        *r = 0;
    } अन्यथा {
        r = &अप्रयुक्तम्;
    }

    यदि (g) {
        *g = 0;
    } अन्यथा {
        g = &अप्रयुक्तम्;
    }

    यदि (b) {
        *b = 0;
    } अन्यथा {
        b = &अप्रयुक्तम्;
    }

    यदि (a) {
        *a = 0;
    } अन्यथा {
        a = &अप्रयुक्तम्;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        प्रत्यागम SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        प्रत्यागम SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        प्रत्यागम SDL_InvalidParamError("y");
    }

    अष्टकानि_प्रत्येकम्_pixel = SDL_BYTESPERPIXEL(surface->format);

    यदि (SDL_MUSTLOCK(surface)) {
        यदि (!SDL_तालकम्_Surface(surface)) {
            प्रत्यागम false;
        }
    }

    p = (Uint8 *)surface->pixels + y * surface->pitch + x * अष्टकानि_प्रत्येकम्_pixel;

    यदि (अष्टकानि_प्रत्येकम्_pixel <= परिमाण(pixel) &&
        !SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_COLORSPACEPRIMARIES(surface->colorspace) == SDL_COLOR_PRIMARIES_BT709) {
        /* Fill the appropriate number of least-significant bytes of pixel,
         * leaving the most-significant bytes set to zero */
#यदि SDL_BYTEORDER == SDL_BIG_ENDIAN
        SDL_memcpy(((Uint8 *)&pixel) + (परिमाण(pixel) - अष्टकानि_प्रत्येकम्_pixel), p, अष्टकानि_प्रत्येकम्_pixel);
#अन्यथा
        SDL_memcpy(&pixel, p, अष्टकानि_प्रत्येकम्_pixel);
#यदि_अन्तः
        SDL_GetRGBA(pixel, surface->fmt, surface->palette, r, g, b, a);
        परिणाम = true;
    } अन्यथा यदि (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // FIXME: We need code to extract a single macroblock from a YUV surface
        SDL_Surface *converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        यदि (converted) {
            परिणाम = SDL_ReadSurfacePixel(converted, x, y, r, g, b, a);
            SDL_DestroySurface(converted);
        }
    } अन्यथा {
        // This is really slow, but it gets the job done
        Uint8 rgba[4];

        यदि (SDL_ConvertPixelsAndColorspace(1, 1, surface->format, surface->colorspace, surface->props, p, surface->pitch, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, rgba, परिमाण(rgba))) {
            *r = rgba[0];
            *g = rgba[1];
            *b = rgba[2];
            *a = rgba[3];
            परिणाम = true;
        }
    }

    यदि (SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }
    प्रत्यागम परिणाम;
}

bool SDL_ReadSurfacePixelFloat(SDL_Surface *surface, पूर्णाङ्क x, पूर्णाङ्क y, भिन्न *r, भिन्न *g, भिन्न *b, भिन्न *a)
{
    भिन्न अप्रयुक्तम्;
    bool परिणाम = false;

    यदि (r) {
        *r = 0.0f;
    } अन्यथा {
        r = &अप्रयुक्तम्;
    }

    यदि (g) {
        *g = 0.0f;
    } अन्यथा {
        g = &अप्रयुक्तम्;
    }

    यदि (b) {
        *b = 0.0f;
    } अन्यथा {
        b = &अप्रयुक्तम्;
    }

    यदि (a) {
        *a = 0.0f;
    } अन्यथा {
        a = &अप्रयुक्तम्;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        प्रत्यागम SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        प्रत्यागम SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        प्रत्यागम SDL_InvalidParamError("y");
    }

    यदि (SDL_BYTESPERPIXEL(surface->format) <= परिमाण(Uint32) &&
        !SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_COLORSPACEPRIMARIES(surface->colorspace) == SDL_COLOR_PRIMARIES_BT709) {
        Uint8 r8, g8, b8, a8;

        यदि (SDL_ReadSurfacePixel(surface, x, y, &r8, &g8, &b8, &a8)) {
            *r = (भिन्न)r8 / 255.0f;
            *g = (भिन्न)g8 / 255.0f;
            *b = (भिन्न)b8 / 255.0f;
            *a = (भिन्न)a8 / 255.0f;
            परिणाम = true;
        }
    } अन्यथा यदि (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // FIXME: We need code to extract a single macroblock from a YUV surface
        SDL_Surface *converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        यदि (converted) {
            परिणाम = SDL_ReadSurfacePixelFloat(converted, x, y, r, g, b, a);
            SDL_DestroySurface(converted);
        }
    } अन्यथा {
        // This is really slow, but it gets the job done
        भिन्न rgba[4];
        Uint8 *p;

        यदि (SDL_MUSTLOCK(surface)) {
            यदि (!SDL_तालकम्_Surface(surface)) {
                प्रत्यागम false;
            }
        }

        p = (Uint8 *)surface->pixels + y * surface->pitch + x * SDL_BYTESPERPIXEL(surface->format);

        यदि (surface->format == SDL_PIXELFORMAT_RGBA128_FLOAT) {
            SDL_memcpy(rgba, p, परिमाण(rgba));
            परिणाम = true;
        } अन्यथा {
            SDL_Colorspace src_colorspace = surface->colorspace;
            SDL_Colorspace dst_colorspace = (src_colorspace == SDL_COLORSPACE_SRGB_रैखिकम् ? SDL_COLORSPACE_SRGB_रैखिकम् : SDL_COLORSPACE_SRGB);

            यदि (SDL_ConvertPixelsAndColorspace(1, 1, surface->format, src_colorspace, surface->props, p, surface->pitch, SDL_PIXELFORMAT_RGBA128_FLOAT, dst_colorspace, 0, rgba, परिमाण(rgba))) {
                परिणाम = true;
            }
        }

        यदि (परिणाम) {
            *r = rgba[0];
            *g = rgba[1];
            *b = rgba[2];
            *a = rgba[3];
        }

        यदि (SDL_MUSTLOCK(surface)) {
            SDL_UnlockSurface(surface);
        }
    }
    प्रत्यागम परिणाम;
}

bool SDL_WriteSurfacePixel(SDL_Surface *surface, पूर्णाङ्क x, पूर्णाङ्क y, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    Uint32 pixel = 0;
    size_t अष्टकानि_प्रत्येकम्_pixel;
    Uint8 *p;
    bool परिणाम = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        प्रत्यागम SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        प्रत्यागम SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        प्रत्यागम SDL_InvalidParamError("y");
    }

    अष्टकानि_प्रत्येकम्_pixel = SDL_BYTESPERPIXEL(surface->format);

    यदि (SDL_MUSTLOCK(surface)) {
        यदि (!SDL_तालकम्_Surface(surface)) {
            प्रत्यागम false;
        }
    }

    p = (Uint8 *)surface->pixels + y * surface->pitch + x * अष्टकानि_प्रत्येकम्_pixel;

    यदि (अष्टकानि_प्रत्येकम्_pixel <= परिमाण(pixel) && !SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        pixel = SDL_MapRGBA(surface->fmt, surface->palette, r, g, b, a);
#यदि SDL_BYTEORDER == SDL_BIG_ENDIAN
        SDL_memcpy(p, ((Uint8 *)&pixel) + (परिमाण(pixel) - अष्टकानि_प्रत्येकम्_pixel), अष्टकानि_प्रत्येकम्_pixel);
#अन्यथा
        SDL_memcpy(p, &pixel, अष्टकानि_प्रत्येकम्_pixel);
#यदि_अन्तः
        परिणाम = true;
    } अन्यथा यदि (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        परिणाम = SDL_Unsupported();
    } अन्यथा {
        // This is really slow, but it gets the job done
        Uint8 rgba[4];

        rgba[0] = r;
        rgba[1] = g;
        rgba[2] = b;
        rgba[3] = a;
        परिणाम = SDL_ConvertPixelsAndColorspace(1, 1, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, rgba, परिमाण(rgba), surface->format, surface->colorspace, surface->props, p, surface->pitch);
    }

    यदि (SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }
    प्रत्यागम परिणाम;
}

bool SDL_WriteSurfacePixelFloat(SDL_Surface *surface, पूर्णाङ्क x, पूर्णाङ्क y, भिन्न r, भिन्न g, भिन्न b, भिन्न a)
{
    bool परिणाम = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        प्रत्यागम SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        प्रत्यागम SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        प्रत्यागम SDL_InvalidParamError("y");
    }

    यदि (SDL_BYTESPERPIXEL(surface->format) <= परिमाण(Uint32) && !SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        Uint8 r8, g8, b8, a8;

        r8 = (Uint8)SDL_आवर्तनम्(SDL_clamp(r, 0.0f, 1.0f) * 255.0f);
        g8 = (Uint8)SDL_आवर्तनम्(SDL_clamp(g, 0.0f, 1.0f) * 255.0f);
        b8 = (Uint8)SDL_आवर्तनम्(SDL_clamp(b, 0.0f, 1.0f) * 255.0f);
        a8 = (Uint8)SDL_आवर्तनम्(SDL_clamp(a, 0.0f, 1.0f) * 255.0f);
        यदि (SDL_WriteSurfacePixel(surface, x, y, r8, g8, b8, a8)) {
            परिणाम = true;
        }
    } अन्यथा यदि (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        परिणाम = SDL_Unsupported();
    } अन्यथा {
        // This is really slow, but it gets the job done
        भिन्न rgba[4];
        Uint8 *p;

        यदि (SDL_MUSTLOCK(surface)) {
            यदि (!SDL_तालकम्_Surface(surface)) {
                प्रत्यागम false;
            }
        }

        p = (Uint8 *)surface->pixels + y * surface->pitch + x * SDL_BYTESPERPIXEL(surface->format);

        rgba[0] = r;
        rgba[1] = g;
        rgba[2] = b;
        rgba[3] = a;

        यदि (surface->format == SDL_PIXELFORMAT_RGBA128_FLOAT) {
            SDL_memcpy(p, rgba, परिमाण(rgba));
            परिणाम = true;
        } अन्यथा {
            SDL_Colorspace dst_colorspace = surface->colorspace;
            SDL_Colorspace src_colorspace = (dst_colorspace == SDL_COLORSPACE_SRGB_रैखिकम् ? SDL_COLORSPACE_SRGB_रैखिकम् : SDL_COLORSPACE_SRGB);

            परिणाम = SDL_ConvertPixelsAndColorspace(1, 1, SDL_PIXELFORMAT_RGBA128_FLOAT, src_colorspace, 0, rgba, परिमाण(rgba), surface->format, dst_colorspace, surface->props, p, surface->pitch);
        }

        यदि (SDL_MUSTLOCK(surface)) {
            SDL_UnlockSurface(surface);
        }
    }
    प्रत्यागम परिणाम;
}

/*
 * Free a surface created by the above function.
 */
शून्य SDL_DestroySurface(SDL_Surface *surface)
{
    यदि (!SDL_SurfaceValid(surface)) {
        प्रत्यागम;
    }
    यदि (surface->आन्तरिकम्_flags & SDL_आन्तरिकम्_SURFACE_DONTFREE) {
        प्रत्यागम;
    }
    यदि (--surface->refcount > 0) {
        प्रत्यागम;
    }

    SDL_RemoveSurfaceAlternateImages(surface);

    SDL_DestroyProperties(surface->props);

    SDL_InvalidateMap(&surface->map);

    यावत् (surface->locked > 0) {
        SDL_UnlockSurface(surface);
    }
#यदि_परिभाषितम् SDL_HAVE_RLE
    यदि (surface->आन्तरिकम्_flags & SDL_आन्तरिकम्_SURFACE_RLEACCEL) {
        SDL_UnRLESurface(surface);
    }
#यदि_अन्तः
    SDL_समुच्चयः_Surface_Palette(surface, रिक्त);

    यदि (surface->flags & SDL_SURFACE_PREALLOCATED) {
        // Don't free
    } अन्यथा यदि (surface->flags & SDL_SURFACE_SIMD_ALIGNED) {
        // Free aligned
        SDL_aligned_free(surface->pixels);
    } अन्यथा {
        // Normal
        SDL_free(surface->pixels);
    }

    surface->reserved = रिक्त;

    यदि (!(surface->आन्तरिकम्_flags & SDL_आन्तरिकम्_SURFACE_राशिः)) {
        SDL_free(surface);
    }
}

SDL_Surface *SDL_आरोपय_Surface_IO(SDL_IOStream *src, bool closeio)
{
    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        प्रत्यागम रिक्त;
    }

    यदि (SDL_IsBMP(src)) {
        प्रत्यागम SDL_आरोपय_BMP_IO(src, closeio);
    } अन्यथा यदि (SDL_IsPNG(src)) {
        प्रत्यागम SDL_आरोपय_PNG_IO(src, closeio);
    } अन्यथा यदि (SDL_IsJPG(src)) {
        प्रत्यागम SDL_आरोपय_JPG_IO(src, closeio);
    } अन्यथा {
        यदि (closeio) {
            SDL_CloseIO(src);
        }
        SDL_समुच्चयः_Error("Unsupported image format");
        प्रत्यागम रिक्त;
    }
}

SDL_Surface *SDL_आरोपय_Surface(ध्रुव वर्ण *file)
{
    SDL_IOStream *प्रवाहः = SDL_IOFromFile(file, "rb");
    यदि (!प्रवाहः) {
        प्रत्यागम रिक्त;
    }

    प्रत्यागम SDL_आरोपय_Surface_IO(प्रवाहः, true);
}
