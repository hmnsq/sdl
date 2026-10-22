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
#અન્તર્ભાવ "SDL_internal.h"

#અન્તર્ભાવ "SDL_sysvideo.h"
#અન્તર્ભાવ "SDL_video_c.h"
#અન્તર્ભાવ "SDL_RLEaccel_c.h"
#અન્તર્ભાવ "SDL_pixels_c.h"
#અન્તર્ભાવ "SDL_rotate.h"
#અન્તર્ભાવ "SDL_stb_c.h"
#અન્તર્ભાવ "SDL_yuv_c.h"
#અન્તર્ભાવ "../render/SDL_sysrender.h"

#અન્તર્ભાવ "SDL_surface_c.h"


// Check to make sure we can safely check multiplication of surface w and pitch and it won't overflow size_t
SDL_COMPILE_TIME_ASSERT(surface_size_assumptions,
                        કદ(પૂર્ણાંક) == કદ(Sint32) && કદ(size_t) >= કદ(Sint32));

SDL_COMPILE_TIME_ASSERT(can_indicate_overflow, SDL_SIZE_MAX > SDL_MAX_SINT32);

// Magic!
સ્થિર અક્ષર SDL_surface_magic;

// Public routines

bool SDL_SurfaceValid(SDL_Surface *surface)
{
    પાછા (surface && surface->reserved == &SDL_surface_magic);
}

શૂન્ય SDL_UpdateSurfaceLockFlag(SDL_Surface *surface)
{
    // We need to mark the surface as needing unlock while locked
    જો ((surface->flags & SDL_SURFACE_LOCKED) ||
        (surface->internal_flags & SDL_INTERNAL_SURFACE_RLEACCEL)) {
        surface->flags |= SDL_SURFACE_LOCK_NEEDED;
    } નહીંતર {
        surface->flags &= ~SDL_SURFACE_LOCK_NEEDED;
    }
}

/*
 * Calculate the pad-aligned scanline width of a surface.
 *
 * for FOURCC, use SDL_CalculateYUVSize()
 */
સ્થિર bool SDL_CalculateRGBSize(Uint32 format, size_t width, size_t height, size_t *size, size_t *pitch, bool minimal)
{
    જો (SDL_BITSPERPIXEL(format) >= 8) {
        જો (!SDL_size_mul_check_overflow(width, SDL_BYTESPERPIXEL(format), pitch)) {
            પાછા SDL_SetError("width * bpp would overflow");
        }
    } નહીંતર {
        જો (!SDL_size_mul_check_overflow(width, SDL_BITSPERPIXEL(format), pitch)) {
            પાછા SDL_SetError("width * bpp would overflow");
        }
        જો (!SDL_size_add_check_overflow(*pitch, 7, pitch)) {
            પાછા SDL_SetError("aligning pitch would overflow");
        }
        *pitch /= 8;
    }
    જો (!minimal) {
        // 4-byte aligning for speed
        જો (!SDL_size_add_check_overflow(*pitch, 3, pitch)) {
            પાછા SDL_SetError("aligning pitch would overflow");
        }
        *pitch &= ~3;
    }

    જો (!SDL_size_mul_check_overflow(height, *pitch, size)) {
        પાછા SDL_SetError("height * pitch would overflow");
    }

    પાછા true;
}

bool SDL_CalculateSurfaceSize(SDL_PixelFormat format, પૂર્ણાંક width, પૂર્ણાંક height, size_t *size, size_t *pitch, bool minimalPitch)
{
    size_t p = 0, sz = 0;

    જો (size) {
        *size = 0;
    }

    જો (pitch) {
        *pitch = 0;
    }

    જો (SDL_ISPIXELFORMAT_FOURCC(format)) {
        જો (format == SDL_PIXELFORMAT_MJPG) {
            // We don't know in advance what it will be, we'll figure it out later.
            પાછા true;
        }

        જો (!SDL_CalculateYUVSize(format, width, height, &sz, &p)) {
            // Overflow...
            પાછા false;
        }
    } નહીંતર {
        જો (!SDL_CalculateRGBSize(format, width, height, &sz, &p, minimalPitch)) {
            // Overflow...
            પાછા false;
        }
    }

    જો (size) {
        *size = sz;
    }

    જો (pitch) {
        *pitch = p;
    }

    પાછા true;
}

સ્થિર bool SDL_InitializeSurface(SDL_Surface *surface, પૂર્ણાંક width, પૂર્ણાંક height, SDL_PixelFormat format, SDL_Colorspace colorspace, SDL_PropertiesID props, શૂન્ય *pixels, પૂર્ણાંક pitch, bool onstack)
{
    SDL_zerop(surface);

    surface->flags = SDL_SURFACE_PREALLOCATED;
    surface->format = format;
    surface->w = width;
    surface->h = height;
    surface->pixels = pixels;
    surface->pitch = pitch;
    surface->reserved = &SDL_surface_magic;

    જો (onstack) {
        surface->internal_flags |= SDL_INTERNAL_SURFACE_ઢગલો;
    }

    surface->fmt = SDL_GetPixelFormatDetails(format);
    જો (!surface->fmt) {
        SDL_DestroySurface(surface);
        પાછા false;
    }

    // Initialize the clip rect
    surface->clip_rect.w = width;
    surface->clip_rect.h = height;

    // Allocate an empty mapping
    surface->map.info.r = 0xFF;
    surface->map.info.g = 0xFF;
    surface->map.info.b = 0xFF;
    surface->map.info.a = 0xFF;

    જો (colorspace == SDL_COLORSPACE_UNKNOWN) {
        surface->colorspace = SDL_GetDefaultColorspaceForFormat(format);
    } નહીંતર {
        surface->colorspace = colorspace;
    }

    જો (props) {
        જો (!SDL_CopyProperties(props, SDL_GetSurfaceProperties(surface))) {
            SDL_DestroySurface(surface);
            પાછા false;
        }
    }

    // By default surfaces with an alpha mask are set up for blending
    જો (SDL_ISPIXELFORMAT_ALPHA(surface->format)) {
        SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
    }

    // The surface is ready to go
    surface->refcount = 1;
    પાછા true;
}

/*
 * Create an empty surface of the appropriate depth using the given format
 */
સ્થિર SDL_Surface *SDL_CreateSurfaceInternal(પૂર્ણાંક width, પૂર્ણાંક height, SDL_PixelFormat format, bool clear_surface)
{
    size_t pitch, size;
    SDL_Surface *surface;

    CHECK_PARAM(width < 0) {
        SDL_InvalidParamError("width");
        પાછા ખાલી;
    }

    CHECK_PARAM(height < 0) {
        SDL_InvalidParamError("height");
        પાછા ખાલી;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        પાછા ખાલી;
    }

    જો (!SDL_CalculateSurfaceSize(format, width, height, &size, &pitch, false /* not minimal pitch */)) {
        // Overflow...
        પાછા ખાલી;
    }

    // Allocate and initialize the surface
    surface = (SDL_Surface *)SDL_malloc(કદ(*surface));
    જો (!surface) {
        પાછા ખાલી;
    }

    જો (!SDL_InitializeSurface(surface, width, height, format, SDL_COLORSPACE_UNKNOWN, 0, ખાલી, (પૂર્ણાંક)pitch, false)) {
        પાછા ખાલી;
    }

    જો (surface->w && surface->h && format != SDL_PIXELFORMAT_MJPG) {
        surface->flags &= ~SDL_SURFACE_PREALLOCATED;
        જો (SDL_GetHintBoolean("SDL_SURFACE_MALLOC", false)) {
            જો (clear_surface) {
                surface->pixels = SDL_calloc(1, size);
            } નહીંતર {
                surface->pixels = SDL_malloc(size);
            }
        } નહીંતર {
            surface->flags |= SDL_SURFACE_SIMD_ALIGNED;
            જો (clear_surface) {
                surface->pixels = SDL_aligned_alloc_zero(SDL_GetSIMDAlignment(), size);
            } નહીંતર {
                surface->pixels = SDL_aligned_alloc(SDL_GetSIMDAlignment(), size);
            }
        }
        જો (!surface->pixels) {
            SDL_DestroySurface(surface);
            પાછા ખાલી;
        }
    }
    પાછા surface;
}

SDL_Surface *SDL_CreateSurfaceZeroed(પૂર્ણાંક width, પૂર્ણાંક height, SDL_PixelFormat format)
{
    પાછા SDL_CreateSurfaceInternal(width, height, format, true);
}

SDL_Surface *SDL_CreateSurfaceUninitialized(પૂર્ણાંક width, પૂર્ણાંક height, SDL_PixelFormat format)
{
    પાછા SDL_CreateSurfaceInternal(width, height, format, false);
}

SDL_Surface *SDL_CreateSurface(પૂર્ણાંક width, પૂર્ણાંક height, SDL_PixelFormat format)
{
    પાછા SDL_CreateSurfaceZeroed(width, height, format);
}


/*
 * Create an RGB surface from an existing memory buffer using the given
 * enum SDL_PIXELFORMAT_* format
 */
SDL_Surface *SDL_CreateSurfaceFrom(પૂર્ણાંક width, પૂર્ણાંક height, SDL_PixelFormat format, શૂન્ય *pixels, પૂર્ણાંક pitch)
{
    CHECK_PARAM(width < 0) {
        SDL_InvalidParamError("width");
        પાછા ખાલી;
    }

    CHECK_PARAM(height < 0) {
        SDL_InvalidParamError("height");
        પાછા ખાલી;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        પાછા ખાલી;
    }

    જો (pitch == 0 && !pixels) {
        // The application will fill these in later with valid values
    } નહીંતર {
        size_t minimalPitch;

        જો (!SDL_CalculateSurfaceSize(format, width, height, ખાલી, &minimalPitch, true /* minimal pitch */)) {
            // Overflow...
            પાછા ખાલી;
        }

        CHECK_PARAM(pitch < 0 || (size_t)pitch < minimalPitch) {
            SDL_InvalidParamError("pitch");
            પાછા ખાલી;
        }
    }

    // Allocate and initialize the surface
    SDL_Surface *surface = (SDL_Surface *)SDL_malloc(કદ(*surface));
    જો (!surface ||
        !SDL_InitializeSurface(surface, width, height, format, SDL_COLORSPACE_UNKNOWN, 0, pixels, pitch, false)) {
        પાછા ખાલી;
    }
    પાછા surface;
}

SDL_PropertiesID SDL_GetSurfaceProperties(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        પાછા 0;
    }

    જો (!surface->props) {
        surface->props = SDL_CreateProperties();
    }
    પાછા surface->props;
}

bool SDL_SetSurfaceColorspace(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        પાછા SDL_InvalidParamError("surface");
    }

    surface->colorspace = colorspace;
    પાછા true;
}

SDL_Colorspace SDL_GetSurfaceColorspace(SDL_Surface *surface)
{
    જો (!SDL_SurfaceValid(surface)) {
        પાછા SDL_COLORSPACE_UNKNOWN;
    }

    પાછા surface->colorspace;
}

દશાંશ SDL_GetDefaultSDRWhitePoint(SDL_Colorspace colorspace)
{
    પાછા SDL_GetSurfaceSDRWhitePoint(ખાલી, colorspace);
}

દશાંશ SDL_GetSurfaceSDRWhitePoint(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    SDL_TransferCharacteristics transfer = SDL_COLORSPACETRANSFER(colorspace);

    જો (transfer == SDL_TRANSFER_CHARACTERISTICS_LINEAR ||
        transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
        SDL_PropertiesID props;
        દશાંશ default_કિંમત = 1.0f;

        જો (SDL_SurfaceValid(surface)) {
            props = surface->props;
        } નહીંતર {
            props = 0;
        }
        જો (transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
            /* The older standards use an SDR white point of 100 nits.
             * ITU-R BT.2408-6 recommends using an SDR white point of 203 nits.
             * This is the default Chrome uses, and what a lot of game content
             * assumes, so we'll go with that.
             */
            અચલ દશાંશ DEFAULT_PQ_SDR_WHITE_POINT = 203.0f;
            default_કિંમત = DEFAULT_PQ_SDR_WHITE_POINT;
        }
        પાછા SDL_GetFloatProperty(props, SDL_PROP_SURFACE_SDR_WHITE_POINT_FLOAT, default_કિંમત);
    }
    પાછા 1.0f;
}

દશાંશ SDL_GetDefaultHDRHeadroom(SDL_Colorspace colorspace)
{
    પાછા SDL_GetSurfaceHDRHeadroom(ખાલી, colorspace);
}

દશાંશ SDL_GetSurfaceHDRHeadroom(SDL_Surface *surface, SDL_Colorspace colorspace)
{
    SDL_TransferCharacteristics transfer = SDL_COLORSPACETRANSFER(colorspace);

    જો (transfer == SDL_TRANSFER_CHARACTERISTICS_LINEAR ||
        transfer == SDL_TRANSFER_CHARACTERISTICS_PQ) {
        SDL_PropertiesID props;
        દશાંશ default_કિંમત = 0.0f;

        જો (SDL_SurfaceValid(surface)) {
            props = surface->props;
        } નહીંતર {
            props = 0;
        }
        પાછા SDL_GetFloatProperty(props, SDL_PROP_SURFACE_HDR_HEADROOM_FLOAT, default_કિંમત);
    }
    પાછા 1.0f;
}

SDL_Palette *SDL_CreateSurfacePalette(SDL_Surface *surface)
{
    SDL_Palette *palette;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        પાછા ખાલી;
    }

    CHECK_PARAM(!SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        SDL_SetError("The surface is not indexed format");
        પાછા ખાલી;
    }

    palette = SDL_CreatePalette((1 << SDL_BITSPERPIXEL(surface->format)));
    જો (!palette) {
        પાછા ખાલી;
    }

    જો (palette->ncolors == 2) {
        // Create a black and white bitmap palette
        palette->colors[0].r = 0xFF;
        palette->colors[0].g = 0xFF;
        palette->colors[0].b = 0xFF;
        palette->colors[1].r = 0x00;
        palette->colors[1].g = 0x00;
        palette->colors[1].b = 0x00;
    }

    જો (!SDL_SetSurfacePalette(surface, palette)) {
        SDL_DestroyPalette(palette);
        પાછા ખાલી;
    }

    // The surface has retained the palette, we can remove the reference here
    SDL_assert(palette->refcount == 2);
    SDL_DestroyPalette(palette);
    પાછા palette;
}

bool SDL_SetSurfacePalette(SDL_Surface *surface, SDL_Palette *palette)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        પાછા SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(palette && !SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        પાછા SDL_SetError("Surface doesn't use a palette");
    }

    CHECK_PARAM(palette && palette->ncolors > (1 << SDL_BITSPERPIXEL(surface->format))) {
        પાછા SDL_SetError("Palette doesn't match surface format");
    }

    જો (palette != surface->palette) {
        જો (surface->palette) {
            SDL_DestroyPalette(surface->palette);
        }

        surface->palette = palette;

        જો (surface->palette) {
            ++surface->palette->refcount;
        }
    }

    SDL_InvalidateMap(&surface->map);

    પાછા true;
}

SDL_Palette *SDL_GetSurfacePalette(SDL_Surface *surface)
{
    જો (!SDL_SurfaceValid(surface)) {
        પાછા ખાલી;
    }

    પાછા surface->palette;
}

bool SDL_AddSurfaceAlternateImage(SDL_Surface *surface, SDL_Surface *image)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        પાછા SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(!SDL_SurfaceValid(image)) {
        પાછા SDL_InvalidParamError("image");
    }

    SDL_Surface **images = (SDL_Surface **)SDL_realloc(surface->images, (surface->અંક_images + 1) * કદ(*images));
    જો (!images) {
        પાછા false;
    }
    images[surface->અંક_images] = image;
    surface->images = images;
    ++surface->અંક_images;
    ++image->refcount;
    પાછા true;
}

bool SDL_SurfaceHasAlternateImages(SDL_Surface *surface)
{
    જો (!SDL_SurfaceValid(surface)) {
        પાછા false;
    }

    પાછા (surface->અંક_images > 0);
}

SDL_Surface **SDL_GetSurfaceImages(SDL_Surface *surface, પૂર્ણાંક *ગણતરી)
{
    જો (ગણતરી) {
        *ગણતરી = 0;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        પાછા ખાલી;
    }

    પૂર્ણાંક અંક_images = 1 + surface->અંક_images;
    SDL_Surface **images = (SDL_Surface **)SDL_malloc((અંક_images + 1) * કદ(*images));
    જો (!images) {
        પાછા ખાલી;
    }
    images[0] = surface;
    જો (surface->અંક_images > 0) {
        SDL_memcpy(&images[1], surface->images, (surface->અંક_images * કદ(images[1])));
    }
    images[અંક_images] = ખાલી;

    જો (ગણતરી) {
        *ગણતરી = અંક_images;
    }
    પાછા images;
}

SDL_Surface *SDL_GetSurfaceImage(SDL_Surface *surface, દશાંશ display_scale)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        પાછા ખાલી;
    }

    જો (!SDL_SurfaceHasAlternateImages(surface)) {
        ++surface->refcount;
        પાછા surface;
    }

    // This surface has high DPI images, pick the best one available, or scale one to the correct size
    SDL_Surface **images = SDL_GetSurfaceImages(surface, ખાલી);
    જો (!images) {
        // Failure, fall back to the existing surface
        ++surface->refcount;
        પાછા surface;
    }

    // Find closest image. Images that are larger than the
    // desired size are preferred over images that are smaller.
    SDL_Surface *closest = ખાલી;
    પૂર્ણાંક desired_w = (પૂર્ણાંક)SDL_round(surface->w * display_scale);
    પૂર્ણાંક desired_h = (પૂર્ણાંક)SDL_round(surface->h * display_scale);
    પૂર્ણાંક desired_size = desired_w * desired_h;
    પૂર્ણાંક closest_distance = -1;
    પૂર્ણાંક closest_size = -1;
    માટે (પૂર્ણાંક i = 0; images[i]; ++i) {
        SDL_Surface *candidate = images[i];
        પૂર્ણાંક size = candidate->w * candidate->h;
        પૂર્ણાંક delta_w = (candidate->w - desired_w);
        પૂર્ણાંક delta_h = (candidate->h - desired_h);
        પૂર્ણાંક distance = (delta_w * delta_w) + (delta_h * delta_h);
        જો (closest_distance < 0 || distance < closest_distance ||
            (size > desired_size && closest_size < desired_size)) {
            closest = candidate;
            closest_distance = distance;
            closest_size = size;
        }
    }
    SDL_free(images);
    SDL_assert(closest != ખાલી);    // We should always have at least one surface

    જો (closest->w == desired_w && closest->h == desired_h) {
        ++closest->refcount;
        પાછા closest;
    }

    // We need to scale the image to the correct size. To maintain good image quality, downscaling
    // is done in steps, never reducing the width and height by more than half each time.
    SDL_Surface *scaled = closest;
    કરો {
        પૂર્ણાંક next_scaled_w = SDL_max(desired_w, (scaled->w + 1) / 2);
        પૂર્ણાંક next_scaled_h = SDL_max(desired_h, (scaled->h + 1) / 2);
        SDL_Surface *next_scaled = SDL_ScaleSurface(scaled, next_scaled_w, next_scaled_h, SDL_SCALEMODE_LINEAR);
        જો (scaled != closest) {
            SDL_DestroySurface(scaled);
        }
        scaled = next_scaled;
        જો (!scaled) {
            // Failure, fall back to the closest surface
            ++closest->refcount;
            પાછા closest;
        }
    } જ્યારે (scaled->w != desired_w || scaled->h != desired_h);

    પાછા scaled;
}

શૂન્ય SDL_RemoveSurfaceAlternateImages(SDL_Surface *surface)
{
    જો (!SDL_SurfaceValid(surface)) {
        પાછા;
    }

    જો (surface->અંક_images > 0) {
        માટે (પૂર્ણાંક i = 0; i < surface->અંક_images; ++i) {
            SDL_DestroySurface(surface->images[i]);
        }
        SDL_free(surface->images);
        surface->images = ખાલી;
        surface->અંક_images = 0;
    }
}

bool SDL_SetSurfaceRLE(SDL_Surface *surface, bool enabled)
{
    પૂર્ણાંક flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        પાછા SDL_InvalidParamError("surface");
    }

    flags = surface->map.info.flags;
    જો (enabled) {
        surface->map.info.flags |= SDL_COPY_RLE_DESIRED;
    } નહીંતર {
        surface->map.info.flags &= ~SDL_COPY_RLE_DESIRED;
    }
    જો (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    પાછા true;
}

bool SDL_SurfaceHasRLE(SDL_Surface *surface)
{
    જો (!SDL_SurfaceValid(surface)) {
        પાછા false;
    }

    જો (!(surface->map.info.flags & SDL_COPY_RLE_DESIRED)) {
        પાછા false;
    }

    પાછા true;
}

bool SDL_Set_Surface_Color_ચાવી(SDL_Surface *surface, bool enabled, Uint32 ચાવી)
{
    પૂર્ણાંક flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        પાછા SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(surface->palette && ચાવી >= ((Uint32)surface->palette->ncolors)) {
        પાછા SDL_InvalidParamError("key");
    }

    flags = surface->map.info.flags;
    જો (enabled) {
        surface->map.info.flags |= SDL_COPY_COLORKEY;
        surface->map.info.colorkey = ચાવી;
    } નહીંતર {
        surface->map.info.flags &= ~SDL_COPY_COLORKEY;
    }
    જો (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }

    પાછા true;
}

bool SDL_Surface_Has_Color_ચાવી(SDL_Surface *surface)
{
    જો (!SDL_SurfaceValid(surface)) {
        પાછા false;
    }

    જો (!(surface->map.info.flags & SDL_COPY_COLORKEY)) {
        પાછા false;
    }

    પાછા true;
}

bool SDL_Get_Surface_Color_ચાવી(SDL_Surface *surface, Uint32 *ચાવી)
{
    જો (ચાવી) {
        *ચાવી = 0;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        પાછા SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(!(surface->map.info.flags & SDL_COPY_COLORKEY)) {
        પાછા SDL_SetError("Surface doesn't have a colorkey");
    }

    જો (ચાવી) {
        *ચાવી = surface->map.info.colorkey;
    }
    પાછા true;
}

/* This is a fairly slow function to switch from colorkey to alpha
   NB: it doesn't handle bpp 1 or 3, because they have no alpha channel */
સ્થિર શૂન્ય SDL_ConvertColorkeyToAlpha(SDL_Surface *surface, bool ignore_alpha)
{
    પૂર્ણાંક x, y, bpp;

    જો (!SDL_SurfaceValid(surface)) {
        પાછા;
    }

    જો (!(surface->map.info.flags & SDL_COPY_COLORKEY) ||
        !SDL_ISPIXELFORMAT_ALPHA(surface->format)) {
        પાછા;
    }

    bpp = SDL_BYTESPERPIXEL(surface->format);

    SDL_LockSurface(surface);

    જો (bpp == 2) {
        Uint16 *row, *spot;
        Uint16 ckey = (Uint16)surface->map.info.colorkey;
        Uint16 mask = (Uint16)(~surface->fmt->Amask);

        // Ignore, or not, alpha in colorkey comparison
        જો (ignore_alpha) {
            ckey &= mask;
            row = (Uint16 *)surface->pixels;
            માટે (y = surface->h; y--;) {
                spot = row;
                માટે (x = surface->w; x--;) {
                    જો ((*spot & mask) == ckey) {
                        *spot &= mask;
                    }
                    ++spot;
                }
                row += surface->pitch / 2;
            }
        } નહીંતર {
            row = (Uint16 *)surface->pixels;
            માટે (y = surface->h; y--;) {
                spot = row;
                માટે (x = surface->w; x--;) {
                    જો (*spot == ckey) {
                        *spot &= mask;
                    }
                    ++spot;
                }
                row += surface->pitch / 2;
            }
        }
    } નહીંતર જો (bpp == 4) {
        Uint32 *row, *spot;
        Uint32 ckey = surface->map.info.colorkey;
        Uint32 mask = ~surface->fmt->Amask;

        // Ignore, or not, alpha in colorkey comparison
        જો (ignore_alpha) {
            ckey &= mask;
            row = (Uint32 *)surface->pixels;
            માટે (y = surface->h; y--;) {
                spot = row;
                માટે (x = surface->w; x--;) {
                    જો ((*spot & mask) == ckey) {
                        *spot &= mask;
                    }
                    ++spot;
                }
                row += surface->pitch / 4;
            }
        } નહીંતર {
            row = (Uint32 *)surface->pixels;
            માટે (y = surface->h; y--;) {
                spot = row;
                માટે (x = surface->w; x--;) {
                    જો (*spot == ckey) {
                        *spot &= mask;
                    }
                    ++spot;
                }
                row += surface->pitch / 4;
            }
        }
    }

    SDL_UnlockSurface(surface);

    SDL_Set_Surface_Color_ચાવી(surface, false, 0);
    SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
}

bool SDL_SetSurfaceColorMod(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b)
{
    પૂર્ણાંક flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        પાછા SDL_InvalidParamError("surface");
    }

    surface->map.info.r = r;
    surface->map.info.g = g;
    surface->map.info.b = b;

    flags = surface->map.info.flags;
    જો (r != 0xFF || g != 0xFF || b != 0xFF) {
        surface->map.info.flags |= SDL_COPY_MODULATE_COLOR;
    } નહીંતર {
        surface->map.info.flags &= ~SDL_COPY_MODULATE_COLOR;
    }
    જો (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    પાછા true;
}

bool SDL_GetSurfaceColorMod(SDL_Surface *surface, Uint8 *r, Uint8 *g, Uint8 *b)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        જો (r) {
            *r = 255;
        }
        જો (g) {
            *g = 255;
        }
        જો (b) {
            *b = 255;
        }
        પાછા SDL_InvalidParamError("surface");
    }

    જો (r) {
        *r = surface->map.info.r;
    }
    જો (g) {
        *g = surface->map.info.g;
    }
    જો (b) {
        *b = surface->map.info.b;
    }
    પાછા true;
}

bool SDL_SetSurfaceAlphaMod(SDL_Surface *surface, Uint8 alpha)
{
    પૂર્ણાંક flags;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        પાછા SDL_InvalidParamError("surface");
    }

    surface->map.info.a = alpha;

    flags = surface->map.info.flags;
    જો (alpha != 0xFF) {
        surface->map.info.flags |= SDL_COPY_MODULATE_ALPHA;
    } નહીંતર {
        surface->map.info.flags &= ~SDL_COPY_MODULATE_ALPHA;
    }
    જો (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }
    પાછા true;
}

bool SDL_GetSurfaceAlphaMod(SDL_Surface *surface, Uint8 *alpha)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        જો (alpha) {
            *alpha = 255;
        }
        પાછા SDL_InvalidParamError("surface");
    }

    જો (alpha) {
        *alpha = surface->map.info.a;
    }
    પાછા true;
}

bool SDL_SetSurfaceBlendMode(SDL_Surface *surface, SDL_BlendMode blendMode)
{
    પૂર્ણાંક flags;
    bool result = true;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        પાછા SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(blendMode == SDL_BLENDMODE_INVALID) {
        પાછા SDL_InvalidParamError("blendMode");
    }

    flags = surface->map.info.flags;
    surface->map.info.flags &= ~SDL_COPY_BLEND_MASK;
    પસંદગી (blendMode) {
    સ્થિતિ SDL_BLENDMODE_NONE:
        તોડો;
    સ્થિતિ SDL_BLENDMODE_BLEND:
        surface->map.info.flags |= SDL_COPY_BLEND;
        તોડો;
    સ્થિતિ SDL_BLENDMODE_BLEND_PREMULTIPLIED:
        surface->map.info.flags |= SDL_COPY_BLEND_PREMULTIPLIED;
        તોડો;
    સ્થિતિ SDL_BLENDMODE_ADD:
        surface->map.info.flags |= SDL_COPY_ADD;
        તોડો;
    સ્થિતિ SDL_BLENDMODE_ADD_PREMULTIPLIED:
        surface->map.info.flags |= SDL_COPY_ADD_PREMULTIPLIED;
        તોડો;
    સ્થિતિ SDL_BLENDMODE_MOD:
        surface->map.info.flags |= SDL_COPY_MOD;
        તોડો;
    સ્થિતિ SDL_BLENDMODE_MUL:
        surface->map.info.flags |= SDL_COPY_MUL;
        તોડો;
    મૂળભૂત:
        result = SDL_Unsupported();
        તોડો;
    }

    જો (surface->map.info.flags != flags) {
        SDL_InvalidateMap(&surface->map);
    }

    પાછા result;
}

bool SDL_GetSurfaceBlendMode(SDL_Surface *surface, SDL_BlendMode *blendMode)
{
    જો (blendMode) {
        *blendMode = SDL_BLENDMODE_INVALID;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        પાછા SDL_InvalidParamError("surface");
    }

    જો (!blendMode) {
        પાછા true;
    }

    પસંદગી (surface->map.info.flags & SDL_COPY_BLEND_MASK) {
    સ્થિતિ SDL_COPY_BLEND:
        *blendMode = SDL_BLENDMODE_BLEND;
        તોડો;
    સ્થિતિ SDL_COPY_BLEND_PREMULTIPLIED:
        *blendMode = SDL_BLENDMODE_BLEND_PREMULTIPLIED;
        તોડો;
    સ્થિતિ SDL_COPY_ADD:
        *blendMode = SDL_BLENDMODE_ADD;
        તોડો;
    સ્થિતિ SDL_COPY_ADD_PREMULTIPLIED:
        *blendMode = SDL_BLENDMODE_ADD_PREMULTIPLIED;
        તોડો;
    સ્થિતિ SDL_COPY_MOD:
        *blendMode = SDL_BLENDMODE_MOD;
        તોડો;
    સ્થિતિ SDL_COPY_MUL:
        *blendMode = SDL_BLENDMODE_MUL;
        તોડો;
    મૂળભૂત:
        *blendMode = SDL_BLENDMODE_NONE;
        તોડો;
    }
    પાછા true;
}

bool SDL_SetSurfaceClipRect(SDL_Surface *surface, અચલ SDL_Rect *rect)
{
    SDL_Rect full_rect;

    // Don't do anything if there's no surface to act on
    જો (!SDL_SurfaceValid(surface)) {
        પાછા false;
    }

    // Set up the full surface rectangle
    full_rect.x = 0;
    full_rect.y = 0;
    full_rect.w = surface->w;
    full_rect.h = surface->h;

    // Set the clipping rectangle
    જો (!rect) {
        surface->clip_rect = full_rect;
        પાછા true;
    }
    પાછા SDL_GetRectIntersection(rect, &full_rect, &surface->clip_rect);
}

bool SDL_GetSurfaceClipRect(SDL_Surface *surface, SDL_Rect *rect)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        જો (rect) {
            SDL_zerop(rect);
        }
        પાછા SDL_InvalidParamError("surface");
    }
    CHECK_PARAM(!rect) {
        પાછા SDL_InvalidParamError("rect");
    }
    *rect = surface->clip_rect;
    પાછા true;
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
bool SDL_BlitSurfaceUnchecked(SDL_Surface *src, અચલ SDL_Rect *srcrect,
                             SDL_Surface *dst, અચલ SDL_Rect *dstrect)
{
    // Check to make sure the blit mapping is valid
    જો (!SDL_ValidateMap(src, dst)) {
        પાછા false;
    }
    પાછા src->map.blit(src, srcrect, dst, dstrect);
}

bool SDL_BlitSurface(SDL_Surface *src, અચલ SDL_Rect *srcrect, SDL_Surface *dst, અચલ SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src) || (!src->pixels && !SDL_MUSTLOCK(src))) {
        પાછા SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst) || (!dst->pixels && !SDL_MUSTLOCK(dst))) {
        પાછા SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        પાછા SDL_SetError("Surfaces must not be locked during blit");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    જો (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
    } નહીંતર {
        r_dst.x = 0;
        r_dst.y = 0;
    }

    // clip the source rectangle to the source surface
    જો (srcrect) {
        SDL_Rect tmp;
        જો (SDL_GetRectIntersection(srcrect, &r_src, &tmp) == false) {
            પાછા true;
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
        જો (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &tmp) == false) {
            પાછા true;
        }

        // Shift srcrect, if dstrect has changed
        r_src.x += tmp.x - r_dst.x;
        r_src.y += tmp.y - r_dst.y;
        r_src.w = tmp.w;
        r_src.h = tmp.h;

        // Update dstrect
        r_dst = tmp;
    }

    જો (r_dst.w <= 0 || r_dst.h <= 0) {
        // No-op.
        પાછા true;
    }

    // Switch back to a fast blit if we were previously stretching
    જો (src->map.info.flags & SDL_COPY_NEAREST) {
        src->map.info.flags &= ~SDL_COPY_NEAREST;
        SDL_InvalidateMap(&src->map);
    }

    પાછા SDL_BlitSurfaceUnchecked(src, &r_src, dst, &r_dst);
}

સ્થિર bool SDL_BlitSurfaceClippedScaled(SDL_Surface *src, અચલ SDL_Rect *srcrect, SDL_Surface *dst, અચલ SDL_Rect *dstrect, SDL_ScaleMode scaleMode)
{
    // We need to scale first, then blit into dst because we're clipping in the destination surface pixel coordinates
    bool result;
    પૂર્ણાંક saved_w = src->w;
    પૂર્ણાંક saved_h = src->h;
    શૂન્ય *saved_pixels = src->pixels;
    src->w = srcrect->w;
    src->h = srcrect->h;
    src->pixels = (Uint8 *)src->pixels + srcrect->y * src->pitch + srcrect->x * SDL_BYTESPERPIXEL(src->format);
    SDL_Surface *scaled = SDL_ScaleSurface(src, dstrect->w, dstrect->h, scaleMode);
    જો (scaled) {
        result = SDL_BlitSurface(scaled, ખાલી, dst, dstrect);
        SDL_DestroySurface(scaled);
    } નહીંતર {
        result = false;
    }
    src->w = saved_w;
    src->h = saved_h;
    src->pixels = saved_pixels;
    પાછા result;
}

bool SDL_BlitSurfaceScaled(SDL_Surface *src, અચલ SDL_Rect *srcrect, SDL_Surface *dst, અચલ SDL_Rect *dstrect, SDL_ScaleMode scaleMode)
{
    SDL_Rect r_src, r_dst;
    bool result;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src) || (!src->pixels && !SDL_MUSTLOCK(src))) {
        પાછા SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst) || (!dst->pixels && !SDL_MUSTLOCK(dst))) {
        પાછા SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        પાછા SDL_SetError("Surfaces must not be locked during blit");
    }

    પસંદગી (scaleMode) {
    સ્થિતિ SDL_SCALEMODE_NEAREST:
        તોડો;
    સ્થિતિ SDL_SCALEMODE_LINEAR:
        તોડો;
    સ્થિતિ SDL_SCALEMODE_PIXELART:
        scaleMode = SDL_SCALEMODE_NEAREST;
        તોડો;
    મૂળભૂત:
        પાછા SDL_InvalidParamError("scaleMode");
    }

    પૂર્ણાંક src_w = srcrect ? srcrect->w : src->w;
    પૂર્ણાંક src_h = srcrect ? srcrect->h : src->h;
    પૂર્ણાંક dst_w = dstrect ? dstrect->w : dst->w;
    પૂર્ણાંક dst_h = dstrect ? dstrect->h : dst->h;
    જો (src_w == dst_w && src_h == dst_h) {
        // No scaling, defer to regular blit
        પાછા SDL_BlitSurface(src, srcrect, dst, dstrect);
    }

    જો (src->w == 0 || src->h == 0) {
        // Nothing to do
        પાછા true;
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    જો (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
        r_dst.w = dstrect->w;
        r_dst.h = dstrect->h;
    } નહીંતર {
        r_dst.x = 0;
        r_dst.y = 0;
        r_dst.w = dst->w;
        r_dst.h = dst->h;
    }

    // clip the source rectangle to the source surface
    જો (srcrect) {
        SDL_Rect desired, tmp;
        desired.x = srcrect->x;
        desired.y = srcrect->y;
        desired.w = SDL_max(srcrect->w, 1);
        desired.h = SDL_max(srcrect->h, 1);
        જો (SDL_GetRectIntersection(&desired, &r_src, &tmp) == false) {
            પાછા true;
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
    જો (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &tmp) == false) {
        પાછા true;
    }

    જો (tmp.x != r_dst.x || tmp.y != r_dst.y || tmp.w != r_dst.w || tmp.h != r_dst.h) {
        // Need to do a clipped and scaled blit
        પાછા SDL_BlitSurfaceClippedScaled(src, &r_src, dst, &r_dst, scaleMode);
    }

    જો (SDL_MUSTLOCK(src)) {
        જો (!SDL_LockSurface(src)) {
            પાછા false;
        }
    }
    જો (SDL_MUSTLOCK(dst)) {
        જો (!SDL_LockSurface(dst)) {
            જો (SDL_MUSTLOCK(src)) {
                SDL_UnlockSurface(src);
            }
            પાછા false;
        }
    }

    result = SDL_BlitSurfaceUncheckedScaled(src, &r_src, dst, &r_dst, scaleMode);

    જો (SDL_MUSTLOCK(src)) {
        SDL_UnlockSurface(src);
    }
    જો (SDL_MUSTLOCK(dst)) {
        SDL_UnlockSurface(dst);
    }
    પાછા result;
}

/**
 *  This is a semi-private blit function and it performs low-level surface
 *  scaled blitting only.
 */
bool SDL_BlitSurfaceUncheckedScaled(SDL_Surface *src, અચલ SDL_Rect *srcrect, SDL_Surface *dst, અચલ SDL_Rect *dstrect, SDL_ScaleMode scaleMode)
{
    સ્થિર અચલ Uint32 complex_copy_flags = (SDL_COPY_MODULATE_MASK | SDL_COPY_BLEND_MASK | SDL_COPY_COLORKEY);

    જો (srcrect->w > SDL_MAX_UINT16 || srcrect->h > SDL_MAX_UINT16 ||
        dstrect->w > SDL_MAX_UINT16 || dstrect->h > SDL_MAX_UINT16) {
        પાછા SDL_SetError("Size too large for scaling");
    }

    જો (!(src->map.info.flags & SDL_COPY_NEAREST)) {
        src->map.info.flags |= SDL_COPY_NEAREST;
        SDL_InvalidateMap(&src->map);
    }

    જો (scaleMode == SDL_SCALEMODE_NEAREST || scaleMode == SDL_SCALEMODE_PIXELART) {
        જો (!(src->map.info.flags & complex_copy_flags) &&
            src->format == dst->format &&
            (!SDL_ISPIXELFORMAT_INDEXED(src->format) ||
             (SDL_BITSPERPIXEL(src->format) == 8 && SDL_IsSamePalette(src->palette, dst->palette))) &&
            SDL_BYTESPERPIXEL(src->format) <= 4) {
            પાછા SDL_StretchSurface(src, srcrect, dst, dstrect, SDL_SCALEMODE_NEAREST);
        } નહીંતર જો (SDL_BITSPERPIXEL(src->format) < 8) {
            // Scaling bitmap not yet supported, convert to RGBA for blit
            bool result = false;
            SDL_Surface *tmp = SDL_ConvertSurface(src, SDL_PIXELFORMAT_ARGB8888);
            જો (tmp) {
                result = SDL_BlitSurfaceUncheckedScaled(tmp, srcrect, dst, dstrect, SDL_SCALEMODE_NEAREST);
                SDL_DestroySurface(tmp);
            }
            પાછા result;
        } નહીંતર {
            પાછા SDL_BlitSurfaceUnchecked(src, srcrect, dst, dstrect);
        }
    } નહીંતર {
        જો (!(src->map.info.flags & complex_copy_flags) &&
            src->format == dst->format &&
            !SDL_ISPIXELFORMAT_INDEXED(src->format) &&
            SDL_BYTESPERPIXEL(src->format) == 4 &&
            src->format != SDL_PIXELFORMAT_ARGB2101010) {
            // fast path
            પાછા SDL_StretchSurface(src, srcrect, dst, dstrect, SDL_SCALEMODE_LINEAR);
        } નહીંતર જો (SDL_BITSPERPIXEL(src->format) < 8) {
            // Scaling bitmap not yet supported, convert to RGBA for blit
            bool result = false;
            SDL_Surface *tmp = SDL_ConvertSurface(src, SDL_PIXELFORMAT_ARGB8888);
            જો (tmp) {
                result = SDL_BlitSurfaceUncheckedScaled(tmp, srcrect, dst, dstrect, scaleMode);
                SDL_DestroySurface(tmp);
            }
            પાછા result;
        } નહીંતર {
            // Use intermediate surface(s)
            SDL_Surface *tmp1 = ખાલી;
            bool result;
            SDL_Rect srcrect2;
            પૂર્ણાંક is_complex_copy_flags = (src->map.info.flags & complex_copy_flags);

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
            જો (SDL_BYTESPERPIXEL(src->format) != 4 || src->format == SDL_PIXELFORMAT_ARGB2101010) {
                SDL_PixelFormat fmt;
                જો (SDL_BYTESPERPIXEL(dst->format) == 4 && dst->format != SDL_PIXELFORMAT_ARGB2101010 &&
                    (SDL_ISPIXELFORMAT_ALPHA(dst->format) || !is_complex_copy_flags)) {
                    fmt = dst->format;
                } નહીંતર {
                    fmt = SDL_PIXELFORMAT_ARGB8888;
                }
                tmp1 = SDL_ConvertSurfaceRect(src, srcrect, fmt);
                જો (!tmp1) {
                    પાછા false;
                }
                src = tmp1;
                srcrect2.x = 0;
                srcrect2.y = 0;
            }

            // Intermediate scaling
            જો (is_complex_copy_flags || src->format != dst->format) {
                SDL_Rect tmprect;
                SDL_Surface *tmp2 = SDL_CreateSurfaceUninitialized(dstrect->w, dstrect->h, src->format);
                SDL_StretchSurface(src, &srcrect2, tmp2, ખાલી, SDL_SCALEMODE_LINEAR);

                SDL_SetSurfaceColorMod(tmp2, r, g, b);
                SDL_SetSurfaceAlphaMod(tmp2, alpha);
                SDL_SetSurfaceBlendMode(tmp2, blendMode);

                tmprect.x = 0;
                tmprect.y = 0;
                tmprect.w = dstrect->w;
                tmprect.h = dstrect->h;
                result = SDL_BlitSurfaceUnchecked(tmp2, &tmprect, dst, dstrect);
                SDL_DestroySurface(tmp2);
            } નહીંતર {
                result = SDL_StretchSurface(src, &srcrect2, dst, dstrect, SDL_SCALEMODE_LINEAR);
            }

            SDL_DestroySurface(tmp1);
            પાછા result;
        }
    }
}

bool SDL_BlitSurfaceTiled(SDL_Surface *src, અચલ SDL_Rect *srcrect, SDL_Surface *dst, અચલ SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        પાછા SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        પાછા SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        પાછા SDL_SetError("Surfaces must not be locked during blit");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    જો (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
        r_dst.w = dstrect->w;
        r_dst.h = dstrect->h;
    } નહીંતર {
        r_dst.x = 0;
        r_dst.y = 0;
        r_dst.w = dst->w;
        r_dst.h = dst->h;
    }

    // clip the source rectangle to the source surface
    જો (srcrect) {
        જો (SDL_GetRectIntersection(srcrect, &r_src, &r_src) == false) {
            પાછા true;
        }

        // For tiling we don't adjust the destination rectangle
    }

    // clip the destination rectangle against the clip rectangle
    {
        જો (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &r_dst) == false) {
            પાછા true;
        }

        // For tiling we don't adjust the source rectangle
    }

    // Switch back to a fast blit if we were previously stretching
    જો (src->map.info.flags & SDL_COPY_NEAREST) {
        src->map.info.flags &= ~SDL_COPY_NEAREST;
        SDL_InvalidateMap(&src->map);
    }

    પૂર્ણાંક rows = r_dst.h / r_src.h;
    પૂર્ણાંક cols = r_dst.w / r_src.w;
    પૂર્ણાંક remaining_w = r_dst.w % r_src.w;
    પૂર્ણાંક remaining_h = r_dst.h % r_src.h;
    SDL_Rect curr_src, curr_dst;

    SDL_copyp(&curr_src, &r_src);
    curr_dst.y = r_dst.y;
    curr_dst.w = r_src.w;
    curr_dst.h = r_src.h;
    માટે (પૂર્ણાંક y = 0; y < rows; ++y) {
        curr_dst.x = r_dst.x;
        માટે (પૂર્ણાંક x = 0; x < cols; ++x) {
            જો (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                પાછા false;
            }
            curr_dst.x += curr_dst.w;
        }
        જો (remaining_w) {
            curr_src.w = remaining_w;
            curr_dst.w = remaining_w;
            જો (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                પાછા false;
            }
            curr_src.w = r_src.w;
            curr_dst.w = r_src.w;
        }
        curr_dst.y += curr_dst.h;
    }
    જો (remaining_h) {
        curr_src.h = remaining_h;
        curr_dst.h = remaining_h;
        curr_dst.x = r_dst.x;
        માટે (પૂર્ણાંક x = 0; x < cols; ++x) {
            જો (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                પાછા false;
            }
            curr_dst.x += curr_dst.w;
        }
        જો (remaining_w) {
            curr_src.w = remaining_w;
            curr_dst.w = remaining_w;
            જો (!SDL_BlitSurfaceUnchecked(src, &curr_src, dst, &curr_dst)) {
                પાછા false;
            }
        }
    }
    પાછા true;
}

bool SDL_BlitSurfaceTiledWithScale(SDL_Surface *src, અચલ SDL_Rect *srcrect, દશાંશ scale, SDL_ScaleMode scaleMode, SDL_Surface *dst, અચલ SDL_Rect *dstrect)
{
    SDL_Rect r_src, r_dst;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        પાછા SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        પાછા SDL_InvalidParamError("dst");
    }
    CHECK_PARAM((src->flags & SDL_SURFACE_LOCKED) || (dst->flags & SDL_SURFACE_LOCKED)) {
        પાછા SDL_SetError("Surfaces must not be locked during blit");
    }
    CHECK_PARAM(scale < 0.0f) {
        પાછા SDL_InvalidParamError("scale");
    }

    // Full src surface
    r_src.x = 0;
    r_src.y = 0;
    r_src.w = src->w;
    r_src.h = src->h;

    જો (dstrect) {
        r_dst.x = dstrect->x;
        r_dst.y = dstrect->y;
        r_dst.w = dstrect->w;
        r_dst.h = dstrect->h;
    } નહીંતર {
        r_dst.x = 0;
        r_dst.y = 0;
        r_dst.w = dst->w;
        r_dst.h = dst->h;
    }

    // clip the source rectangle to the source surface
    જો (srcrect) {
        જો (SDL_GetRectIntersection(srcrect, &r_src, &r_src) == false) {
            પાછા true;
        }

        // For tiling we don't adjust the destination rectangle
    }

    // clip the destination rectangle against the clip rectangle
    {
        જો (SDL_GetRectIntersection(&r_dst, &dst->clip_rect, &r_dst) == false) {
            પાછા true;
        }

        // For tiling we don't adjust the source rectangle
    }

    // Switch back to a fast blit if we were previously stretching
    જો (src->map.info.flags & SDL_COPY_NEAREST) {
        src->map.info.flags &= ~SDL_COPY_NEAREST;
        SDL_InvalidateMap(&src->map);
    }

    પૂર્ણાંક tile_width = (પૂર્ણાંક)SDL_roundf(r_src.w * scale);
    પૂર્ણાંક tile_height = (પૂર્ણાંક)SDL_roundf(r_src.h * scale);
    જો (tile_width <= 0 || tile_height <= 0) {
        // Nothing to do
        પાછા true;
    }
    પૂર્ણાંક rows = r_dst.h / tile_height;
    પૂર્ણાંક cols = r_dst.w / tile_width;
    પૂર્ણાંક remaining_dst_w = (r_dst.w - cols * tile_width);
    પૂર્ણાંક remaining_dst_h = (r_dst.h - rows * tile_height);
    પૂર્ણાંક remaining_src_w = (પૂર્ણાંક)(remaining_dst_w / scale);
    પૂર્ણાંક remaining_src_h = (પૂર્ણાંક)(remaining_dst_h / scale);
    SDL_Rect curr_src, curr_dst;

    SDL_copyp(&curr_src, &r_src);
    curr_dst.y = r_dst.y;
    curr_dst.w = tile_width;
    curr_dst.h = tile_height;
    માટે (પૂર્ણાંક y = 0; y < rows; ++y) {
        curr_dst.x = r_dst.x;
        માટે (પૂર્ણાંક x = 0; x < cols; ++x) {
            જો (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
                પાછા false;
            }
            curr_dst.x += curr_dst.w;
        }
        જો (remaining_dst_w > 0) {
            curr_src.w = remaining_src_w;
            curr_dst.w = remaining_dst_w;
            જો (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
                પાછા false;
            }
            curr_src.w = r_src.w;
            curr_dst.w = tile_width;
        }
        curr_dst.y += curr_dst.h;
    }
    જો (remaining_dst_h > 0) {
        curr_src.h = remaining_src_h;
        curr_dst.h = remaining_dst_h;
        curr_dst.x = r_dst.x;
        માટે (પૂર્ણાંક x = 0; x < cols; ++x) {
            જો (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
                પાછા false;
            }
            curr_dst.x += curr_dst.w;
        }
        જો (remaining_dst_w > 0) {
            curr_src.w = remaining_src_w;
            curr_dst.w = remaining_dst_w;
            જો (!SDL_BlitSurfaceUncheckedScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
                પાછા false;
            }
        }
    }
    પાછા true;
}

bool SDL_BlitSurface9Grid(SDL_Surface *src, અચલ SDL_Rect *srcrect, પૂર્ણાંક ડાબું_width, પૂર્ણાંક જમણું_width, પૂર્ણાંક ટોચ_height, પૂર્ણાંક bottom_height, દશાંશ scale, SDL_ScaleMode scaleMode, SDL_Surface *dst, અચલ SDL_Rect *dstrect)
{
    SDL_Rect full_src, full_dst;
    SDL_Rect curr_src, curr_dst;
    પૂર્ણાંક dst_ડાબું_width;
    પૂર્ણાંક dst_જમણું_width;
    પૂર્ણાંક dst_ટોચ_height;
    પૂર્ણાંક dst_bottom_height;

    // Make sure the surfaces aren't locked
    CHECK_PARAM(!SDL_SurfaceValid(src)) {
        પાછા SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        પાછા SDL_InvalidParamError("dst");
    }

    જો (!srcrect) {
        full_src.x = 0;
        full_src.y = 0;
        full_src.w = src->w;
        full_src.h = src->h;
        srcrect = &full_src;
    }

    જો (!dstrect) {
        full_dst.x = 0;
        full_dst.y = 0;
        full_dst.w = dst->w;
        full_dst.h = dst->h;
        dstrect = &full_dst;
    }

    જો (scale <= 0.0f || scale == 1.0f) {
        dst_ડાબું_width = ડાબું_width;
        dst_જમણું_width = જમણું_width;
        dst_ટોચ_height = ટોચ_height;
        dst_bottom_height = bottom_height;
    } નહીંતર {
        dst_ડાબું_width = (પૂર્ણાંક)SDL_roundf(ડાબું_width * scale);
        dst_જમણું_width = (પૂર્ણાંક)SDL_roundf(જમણું_width * scale);
        dst_ટોચ_height = (પૂર્ણાંક)SDL_roundf(ટોચ_height * scale);
        dst_bottom_height = (પૂર્ણાંક)SDL_roundf(bottom_height * scale);
    }

    // Upper-left corner
    curr_src.x = srcrect->x;
    curr_src.y = srcrect->y;
    curr_src.w = ડાબું_width;
    curr_src.h = ટોચ_height;
    curr_dst.x = dstrect->x;
    curr_dst.y = dstrect->y;
    curr_dst.w = dst_ડાબું_width;
    curr_dst.h = dst_ટોચ_height;
    જો (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        પાછા false;
    }

    // Upper-right corner
    curr_src.x = srcrect->x + srcrect->w - જમણું_width;
    curr_src.w = જમણું_width;
    curr_dst.x = dstrect->x + dstrect->w - dst_જમણું_width;
    curr_dst.w = dst_જમણું_width;
    જો (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        પાછા false;
    }

    // Lower-right corner
    curr_src.y = srcrect->y + srcrect->h - bottom_height;
    curr_dst.y = dstrect->y + dstrect->h - dst_bottom_height;
    curr_dst.h = dst_bottom_height;
    જો (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        પાછા false;
    }

    // Lower-left corner
    curr_src.x = srcrect->x;
    curr_src.w = ડાબું_width;
    curr_dst.x = dstrect->x;
    curr_dst.w = dst_ડાબું_width;
    જો (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        પાછા false;
    }

    //ડાબું
    curr_src.y = srcrect->y + ટોચ_height;
    curr_src.h = srcrect->h - ટોચ_height - bottom_height;
    curr_dst.y = dstrect->y + dst_ટોચ_height;
    curr_dst.h = dstrect->h - dst_ટોચ_height - dst_bottom_height;
    જો (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        પાછા false;
    }

    //જમણું
    curr_src.x = srcrect->x + srcrect->w - જમણું_width;
    curr_src.w = જમણું_width;
    curr_dst.x = dstrect->x + dstrect->w - dst_જમણું_width;
    curr_dst.w = dst_જમણું_width;
    જો (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        પાછા false;
    }

    //ટોચ
    curr_src.x = srcrect->x + ડાબું_width;
    curr_src.y = srcrect->y;
    curr_src.w = srcrect->w - ડાબું_width - જમણું_width;
    curr_src.h = ટોચ_height;
    curr_dst.x = dstrect->x + dst_ડાબું_width;
    curr_dst.y = dstrect->y;
    curr_dst.w = dstrect->w - dst_ડાબું_width - dst_જમણું_width;
    curr_dst.h = dst_ટોચ_height;
    જો (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        પાછા false;
    }

    // Bottom
    curr_src.y = srcrect->y + srcrect->h - bottom_height;
    curr_dst.y = dstrect->y + dstrect->h - dst_bottom_height;
    curr_dst.h = dst_bottom_height;
    જો (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        પાછા false;
    }

    // Center
    curr_src.x = srcrect->x + ડાબું_width;
    curr_src.y = srcrect->y + ટોચ_height;
    curr_src.w = srcrect->w - ડાબું_width - જમણું_width;
    curr_src.h = srcrect->h - ટોચ_height - bottom_height;
    curr_dst.x = dstrect->x + dst_ડાબું_width;
    curr_dst.y = dstrect->y + dst_ટોચ_height;
    curr_dst.w = dstrect->w - dst_ડાબું_width - dst_જમણું_width;
    curr_dst.h = dstrect->h - dst_ટોચ_height - dst_bottom_height;
    જો (!SDL_BlitSurfaceScaled(src, &curr_src, dst, &curr_dst, scaleMode)) {
        પાછા false;
    }

    પાછા true;
}

/*
 * Lock a surface to directly access the pixels
 */
bool SDL_LockSurface(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        પાછા SDL_InvalidParamError("surface");
    }

    જો (!surface->locked) {
#ifdef SDL_HAVE_RLE
        // Perform the lock
        જો (surface->internal_flags & SDL_INTERNAL_SURFACE_RLEACCEL) {
            SDL_UnRLESurface(surface);
        }
#endif
    }

    // Increment the surface lock count, for recursive locks
    ++surface->locked;
    surface->flags |= SDL_SURFACE_LOCKED;
    SDL_UpdateSurfaceLockFlag(surface);

    // Ready to go..
    પાછા true;
}

/*
 * Unlock a previously locked surface
 */
શૂન્ય SDL_UnlockSurface(SDL_Surface *surface)
{
    જો (!SDL_SurfaceValid(surface)) {
        પાછા;
    }

    // Only perform an unlock if we are locked
    જો (!surface->locked || (--surface->locked > 0)) {
        પાછા;
    }

    surface->flags &= ~SDL_SURFACE_LOCKED;
    SDL_UpdateSurfaceLockFlag(surface);
}

સ્થિર bool SDL_FlipSurfaceHorizontal(SDL_Surface *surface)
{
    bool isstack;
    Uint8 *row, *a, *b, *tmp;
    પૂર્ણાંક i, j, bpp;

    જો (SDL_BITSPERPIXEL(surface->format) < 8) {
        // We could implement this if needed, but we'd have to flip sets of bits within a byte
        પાછા SDL_Unsupported();
    }

    જો (surface->h <= 0) {
        પાછા true;
    }

    જો (surface->w <= 1) {
        પાછા true;
    }

    bpp = SDL_BYTESPERPIXEL(surface->format);
    row = (Uint8 *)surface->pixels;
    tmp = SDL_small_alloc(Uint8, surface->pitch, &isstack);
    જો (!tmp) {
        પાછા false;
    }
    માટે (i = surface->h; i--; ) {
        a = row;
        b = a + (surface->w - 1) * bpp;
        માટે (j = surface->w / 2; j--; ) {
            SDL_memcpy(tmp, a, bpp);
            SDL_memcpy(a, b, bpp);
            SDL_memcpy(b, tmp, bpp);
            a += bpp;
            b -= bpp;
        }
        row += surface->pitch;
    }
    SDL_small_free(tmp, isstack);
    પાછા true;
}

સ્થિર bool SDL_FlipSurfaceVertical(SDL_Surface *surface)
{
    bool isstack;
    Uint8 *a, *b, *tmp;
    પૂર્ણાંક i;

    જો (surface->h <= 1) {
        પાછા true;
    }

    a = (Uint8 *)surface->pixels;
    b = a + (surface->h - 1) * surface->pitch;
    tmp = SDL_small_alloc(Uint8, surface->pitch, &isstack);
    જો (!tmp) {
        પાછા false;
    }
    માટે (i = surface->h / 2; i--; ) {
        SDL_memcpy(tmp, a, surface->pitch);
        SDL_memcpy(a, b, surface->pitch);
        SDL_memcpy(b, tmp, surface->pitch);
        a += surface->pitch;
        b -= surface->pitch;
    }
    SDL_small_free(tmp, isstack);
    પાછા true;
}

bool SDL_FlipSurface(SDL_Surface *surface, SDL_FlipMode flip)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        પાછા SDL_InvalidParamError("surface");
    }
    જો (!surface->pixels) {
        પાછા true;
    }

    bool result = true;
    પસંદગી (flip) {
    સ્થિતિ SDL_FLIP_HORIZONTAL:
        result = SDL_FlipSurfaceHorizontal(surface);
        તોડો;
    સ્થિતિ SDL_FLIP_VERTICAL:
        result = SDL_FlipSurfaceVertical(surface);
        તોડો;
    સ્થિતિ SDL_FLIP_HORIZONTAL_AND_VERTICAL:
        result &= SDL_FlipSurfaceHorizontal(surface);
        result &= SDL_FlipSurfaceVertical(surface);
        તોડો;
    મૂળભૂત:
        result = SDL_InvalidParamError("flip");
        તોડો;
    }
    પાછા result;
}

સ્થિર SDL_Surface *SDL_ConvertSurfaceRectAndColorspace(SDL_Surface *surface, અચલ SDL_Rect *rect, SDL_PixelFormat format, SDL_Palette *palette, SDL_Colorspace colorspace, SDL_PropertiesID props)
{
    SDL_Palette *temp_palette = ખાલી;
    SDL_Surface *convert = ખાલી;
    SDL_Colorspace src_colorspace;
    SDL_PropertiesID src_properties;
    Uint32 copy_flags;
    SDL_Color copy_color;
    SDL_Rect bounds;
    bool result;
    bool palette_ck_transform = false;
    Uint8 palette_ck_કિંમત = 0;
    Uint8 *palette_saved_alpha = ખાલી;
    પૂર્ણાંક palette_saved_alpha_ncolors = 0;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        જાઓ error;
    }

    CHECK_PARAM(format == SDL_PIXELFORMAT_UNKNOWN) {
        SDL_InvalidParamError("format");
        જાઓ error;
    }

    // Set the bounds of the new surface
    bounds.x = 0;
    bounds.y = 0;
    bounds.w = surface->w;
    bounds.h = surface->h;
    જો (rect) {
        bounds.w = rect->w;
        bounds.h = rect->h;
    } નહીંતર {
        rect = &bounds;
    }

    // Check for empty destination palette! (results in empty image)
    જો (palette) {
        પૂર્ણાંક i;
        માટે (i = 0; i < palette->ncolors; ++i) {
            જો ((palette->colors[i].r != 0xFF) || (palette->colors[i].g != 0xFF) || (palette->colors[i].b != 0xFF)) {
                તોડો;
            }
        }
        જો (i == palette->ncolors) {
            SDL_SetError("Empty destination palette");
            જાઓ error;
        }
    } નહીંતર જો (SDL_ISPIXELFORMAT_INDEXED(format)) {
        // Create a dither palette for conversion
        temp_palette = SDL_CreatePalette(1 << SDL_BITSPERPIXEL(format));
        જો (temp_palette) {
            SDL_DitherPalette(temp_palette);
            palette = temp_palette;
        }
    }

    src_colorspace = surface->colorspace;
    src_properties = surface->props;

    // Create a new surface with the desired format
    જો (surface->pixels || SDL_MUSTLOCK(surface)) {
        convert = SDL_CreateSurfaceUninitialized(rect->w, rect->h, format);
    } નહીંતર {
        convert = SDL_CreateSurfaceFrom(rect->w, rect->h, format, ખાલી, 0);
    }
    જો (!convert) {
        જાઓ error;
    }
    જો (SDL_ISPIXELFORMAT_INDEXED(format)) {
        SDL_SetSurfacePalette(convert, palette);
    }

    જો (colorspace == SDL_COLORSPACE_UNKNOWN) {
        colorspace = src_colorspace;
    }
    SDL_SetSurfaceColorspace(convert, colorspace);

    જો (SDL_ISPIXELFORMAT_FOURCC(format) || SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        જો (surface->format == SDL_PIXELFORMAT_MJPG && format == SDL_PIXELFORMAT_MJPG) {
            // Just do a straight pixel copy of the JPEG image
            size_t size = (size_t)surface->pitch;
            convert->pixels = SDL_malloc(size);
            જો (!convert->pixels) {
                જાઓ error;
            }
            convert->flags &= ~SDL_SURFACE_PREALLOCATED;
            convert->pitch = surface->pitch;
            SDL_memcpy(convert->pixels, surface->pixels, size);

        } નહીંતર જો (!SDL_ConvertPixelsAndColorspace(surface->w, surface->h, surface->format, src_colorspace, src_properties, surface->pixels, surface->pitch, convert->format, colorspace, props, convert->pixels, convert->pitch)) {
            જાઓ error;
        }

        // Save the original copy flags
        copy_flags = surface->map.info.flags;

        જાઓ end;
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
    જો (surface->palette && SDL_ISPIXELFORMAT_ALPHA(format)) {
        bool set_opaque = false;

        bool is_opaque, has_alpha_channel;
        SDL_DetectPalette(surface->palette, &is_opaque, &has_alpha_channel);

        જો (is_opaque) {
            જો (!has_alpha_channel) {
                set_opaque = true;
            }
        }

        // Set opaque and backup palette alpha values
        જો (set_opaque) {
            પૂર્ણાંક i;
            palette_saved_alpha_ncolors = surface->palette->ncolors;
            જો (palette_saved_alpha_ncolors > 0) {
                palette_saved_alpha = SDL_ઢગલો_alloc(Uint8, palette_saved_alpha_ncolors);
                માટે (i = 0; i < palette_saved_alpha_ncolors; i++) {
                    palette_saved_alpha[i] = surface->palette->colors[i].a;
                    surface->palette->colors[i].a = SDL_ALPHA_OPAQUE;
                }
            }
        }
    }

    // Transform colorkey to alpha. for cases where source palette has duplicate values, and colorkey is one of them
    જો (copy_flags & SDL_COPY_COLORKEY) {
        જો (surface->palette && !palette) {
            palette_ck_transform = true;
            palette_ck_કિંમત = surface->palette->colors[surface->map.info.colorkey].a;
            surface->palette->colors[surface->map.info.colorkey].a = SDL_ALPHA_TRANSPARENT;
        }
    }

    જો (surface->pixels || SDL_MUSTLOCK(surface)) {
        result = SDL_BlitSurfaceUnchecked(surface, rect, convert, &bounds);
    } નહીંતર {
        result = true;
    }

    // Restore colorkey alpha value
    જો (palette_ck_transform) {
        surface->palette->colors[surface->map.info.colorkey].a = palette_ck_કિંમત;
    }

    // Restore palette alpha values
    જો (palette_saved_alpha) {
        પૂર્ણાંક i;
        માટે (i = 0; i < palette_saved_alpha_ncolors; i++) {
            surface->palette->colors[i].a = palette_saved_alpha[i];
        }
        SDL_ઢગલો_free(palette_saved_alpha);
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
    જો (!result) {
        જાઓ error;
    }

    જો (copy_flags & SDL_COPY_COLORKEY) {
        bool set_colorkey_by_color = false;
        bool convert_colorkey = true;

        જો (surface->palette) {
            જો (palette &&
                surface->palette->ncolors <= palette->ncolors &&
                (SDL_memcmp(surface->palette->colors, palette->colors,
                            surface->palette->ncolors * કદ(SDL_Color)) == 0)) {
                // The palette is identical, just set the same colorkey
                SDL_Set_Surface_Color_ચાવી(convert, true, surface->map.info.colorkey);
            } નહીંતર જો (!palette) {
                જો (SDL_ISPIXELFORMAT_ALPHA(format)) {
                    // No need to add the colorkey, transparency is in the alpha channel
                } નહીંતર {
                    // Only set the colorkey information
                    set_colorkey_by_color = true;
                    convert_colorkey = false;
                }
            } નહીંતર {
                set_colorkey_by_color = true;
            }
        } નહીંતર {
            set_colorkey_by_color = true;
        }

        જો (set_colorkey_by_color) {
            SDL_Surface *tmp;
            SDL_Surface *tmp2;
            પૂર્ણાંક converted_colorkey = 0;

            // Create a dummy surface to get the colorkey converted
            tmp = SDL_CreateSurfaceUninitialized(1, 1, surface->format);
            જો (!tmp) {
                જાઓ error;
            }

            // Share the palette, if any
            જો (surface->palette) {
                SDL_SetSurfacePalette(tmp, surface->palette);
            }

            SDL_FillSurfaceRect(tmp, ખાલી, surface->map.info.colorkey);

            tmp->map.info.flags &= ~SDL_COPY_COLORKEY;

            // Conversion of the colorkey
            tmp2 = SDL_ConvertSurfaceAndColorspace(tmp, format, palette, colorspace, props);
            જો (!tmp2) {
                SDL_DestroySurface(tmp);
                જાઓ error;
            }

            // Get the converted colorkey
            SDL_memcpy(&converted_colorkey, tmp2->pixels, tmp2->fmt->bytes_per_pixel);

            SDL_DestroySurface(tmp);
            SDL_DestroySurface(tmp2);

            // Set the converted colorkey on the new surface
            SDL_Set_Surface_Color_ચાવી(convert, true, converted_colorkey);

            // This is needed when converting for 3D texture upload
            જો (convert_colorkey) {
                SDL_ConvertColorkeyToAlpha(convert, true);
            }
        }
    }

end:
    જો (temp_palette) {
        SDL_DestroyPalette(temp_palette);
    }

    SDL_SetSurfaceClipRect(convert, &surface->clip_rect);

    /* Enable alpha blending by default if the new surface has an
     * alpha channel or alpha modulation */
    જો (SDL_ISPIXELFORMAT_ALPHA(format) ||
        (copy_flags & SDL_COPY_MODULATE_ALPHA)) {
        SDL_SetSurfaceBlendMode(convert, SDL_BLENDMODE_BLEND);
    }
    જો (copy_flags & SDL_COPY_RLE_DESIRED) {
        SDL_SetSurfaceRLE(convert, true);
    }

    // Copy alternate images
    માટે (પૂર્ણાંક i = 0; i < surface->અંક_images; ++i) {
        જો (!SDL_AddSurfaceAlternateImage(convert, surface->images[i])) {
            જાઓ error;
        }
    }

    // Copy properties
    જો (surface->props) {
        જો (!SDL_CopyProperties(surface->props, SDL_GetSurfaceProperties(convert))) {
            જાઓ error;
        }

        // Make sure the new surface doesn't reference an old SDL2 surface.
        SDL_ClearProperty(SDL_GetSurfaceProperties(convert), "sdl2-compat.surface2");
    }

    // We're ready to go!
    પાછા convert;

error:
    જો (temp_palette) {
        SDL_DestroyPalette(temp_palette);
    }
    જો (convert) {
        SDL_DestroySurface(convert);
    }
    પાછા ખાલી;
}

SDL_Surface *SDL_ConvertSurfaceAndColorspace(SDL_Surface *surface, SDL_PixelFormat format, SDL_Palette *palette, SDL_Colorspace colorspace, SDL_PropertiesID props)
{
    પાછા SDL_ConvertSurfaceRectAndColorspace(surface, ખાલી, format, palette, colorspace, props);
}

SDL_Surface *SDL_RotateSurface(SDL_Surface *surface, દશાંશ angle)
{
    SDL_Surface *rotated = ખાલી;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        પાછા ખાલી;
    }

    SDL_Rect rect_dest;
    દ્વિગુણ cangle, sangle;
    SDL_FPoint center = { surface->w * 0.5f, surface->h * 0.5f };
    SDLgfx_rotozoomSurfaceSizeTrig(surface->w, surface->h, angle, &center, &rect_dest, &cangle, &sangle);

    // This function requires a 32-bit surface or 8-bit surface with a colorkey
    જો ((SDL_BITSPERPIXEL(surface->format) == 32 && SDL_PIXELLAYOUT(surface->format) == SDL_PACKEDLAYOUT_8888) ||
        (surface->format == SDL_PIXELFORMAT_INDEX8 && SDL_Surface_Has_Color_ચાવી(surface))) {
        rotated = SDLgfx_rotateSurface(surface, angle, 1, 0, 0, &rect_dest, cangle, sangle, &center);
    } નહીંતર {
        SDL_Surface *convert = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);
        જો (convert) {
            SDL_Surface *tmp = SDLgfx_rotateSurface(convert, angle, 1, 0, 0, &rect_dest, cangle, sangle, &center);
            જો (tmp) {
                rotated = SDL_ConvertSurfaceAndColorspace(tmp, surface->format, surface->palette, surface->colorspace, surface->props);
                SDL_DestroySurface(tmp);
            }
            SDL_DestroySurface(convert);
        }
    }

    જો (rotated) {
        જો (SDL_HasProperty(surface->props, SDL_PROP_SURFACE_ROTATION_FLOAT)) {
            અચલ દશાંશ rotation = (SDL_Get_સંખ્યા_Property(surface->props, SDL_PROP_SURFACE_ROTATION_FLOAT, 0) - angle);
            SDL_SetFloatProperty(SDL_GetSurfaceProperties(rotated), SDL_PROP_SURFACE_ROTATION_FLOAT, rotation);
        }
    }

    પાછા rotated;
}

SDL_Surface *SDL_DuplicateSurface(SDL_Surface *surface)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        પાછા ખાલી;
    }

    પાછા SDL_ConvertSurfaceAndColorspace(surface, surface->format, surface->palette, surface->colorspace, surface->props);
}

SDL_Surface *SDL_ScaleSurface(SDL_Surface *surface, પૂર્ણાંક width, પૂર્ણાંક height, SDL_ScaleMode scaleMode)
{
    SDL_Surface *convert = ખાલી;
    Uint32 copy_flags;
    SDL_Color copy_color;
    bool rc;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        જાઓ error;
    }

    જો (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // We can't directly scale a YUV surface (yet!)
        SDL_Surface *tmp = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        જો (!tmp) {
            પાછા ખાલી;
        }

        SDL_Surface *scaled = SDL_ScaleSurface(tmp, width, height, scaleMode);
        SDL_DestroySurface(tmp);
        જો (!scaled) {
            પાછા ખાલી;
        }

        SDL_Surface *result = SDL_ConvertSurfaceAndColorspace(scaled, surface->format, ખાલી, surface->colorspace, surface->props);
        SDL_DestroySurface(scaled);
        પાછા result;
    }

    જો (SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        // Linear scaling requires conversion to RGBA and then slow pixel color lookup
        scaleMode = SDL_SCALEMODE_NEAREST;
    }

    // Create a new surface with the desired size
    જો (surface->pixels || SDL_MUSTLOCK(surface)) {
        convert = SDL_CreateSurfaceUninitialized(width, height, surface->format);
    } નહીંતર {
        convert = SDL_CreateSurfaceFrom(width, height, surface->format, ખાલી, 0);
    }
    જો (!convert) {
        જાઓ error;
    }
    SDL_SetSurfacePalette(convert, surface->palette);
    SDL_SetSurfaceColorspace(convert, surface->colorspace);
    SDL_SetSurfaceRLE(convert, SDL_SurfaceHasRLE(surface));

    જો (surface->pixels || SDL_MUSTLOCK(surface)) {
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

        rc = SDL_BlitSurfaceScaled(surface, ખાલી, convert, ખાલી, scaleMode);

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
    } નહીંતર {
        rc = true;
    }

    // SDL_BlitSurfaceScaled failed, and so the conversion
    જો (!rc) {
        જાઓ error;
    }

    // We're ready to go!
    પાછા convert;

error:
    જો (convert) {
        SDL_DestroySurface(convert);
    }
    પાછા ખાલી;
}

SDL_Surface *SDL_ConvertSurfaceRect(SDL_Surface *surface, અચલ SDL_Rect *rect, SDL_PixelFormat format)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        પાછા ખાલી;
    }

    પાછા SDL_ConvertSurfaceRectAndColorspace(surface, rect, format, ખાલી, SDL_GetDefaultColorspaceForFormat(format), surface->props);
}

SDL_Surface *SDL_ConvertSurface(SDL_Surface *surface, SDL_PixelFormat format)
{
    પાછા SDL_ConvertSurfaceRect(surface, ખાલી, format);
}

SDL_Surface *SDL_DuplicatePixels(પૂર્ણાંક width, પૂર્ણાંક height, SDL_PixelFormat format, SDL_Colorspace colorspace, શૂન્ય *pixels, પૂર્ણાંક pitch)
{
    SDL_Surface *surface;
    જો (pixels) {
        surface = SDL_CreateSurfaceUninitialized(width, height, format);
    } નહીંતર {
        surface = SDL_CreateSurfaceFrom(width, height, format, ખાલી, 0);
    }
    જો (!surface) {
        પાછા ખાલી;
    }
    SDL_SetSurfaceColorspace(surface, colorspace);

    જો (surface->pixels) {
        પૂર્ણાંક length = width * SDL_BYTESPERPIXEL(format);
        Uint8 *src = (Uint8 *)pixels;
        Uint8 *dst = (Uint8 *)surface->pixels;
        પૂર્ણાંક rows = height;
        જ્યારે (rows--) {
            SDL_memcpy(dst, src, length);
            dst += surface->pitch;
            src += pitch;
        }
    }
    પાછા surface;
}

bool SDL_ConvertPixelsAndColorspace(પૂર્ણાંક width, પૂર્ણાંક height,
                      SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, અચલ શૂન્ય *src, પૂર્ણાંક src_pitch,
                      SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, શૂન્ય *dst, પૂર્ણાંક dst_pitch)
{
    SDL_Surface src_surface;
    SDL_Surface dst_surface;
    SDL_Rect rect;
    શૂન્ય *nonconst_src = (શૂન્ય *)src;
    bool result;

    CHECK_PARAM(!src) {
        પાછા SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!src_pitch) {
        પાછા SDL_InvalidParamError("src_pitch");
    }
    CHECK_PARAM(!dst) {
        પાછા SDL_InvalidParamError("dst");
    }
    CHECK_PARAM(!dst_pitch) {
        પાછા SDL_InvalidParamError("dst_pitch");
    }

    જો (src_colorspace == SDL_COLORSPACE_UNKNOWN) {
        src_colorspace = SDL_GetDefaultColorspaceForFormat(src_format);
    }
    જો (dst_colorspace == SDL_COLORSPACE_UNKNOWN) {
        dst_colorspace = SDL_GetDefaultColorspaceForFormat(dst_format);
    }

    જો (src_format == SDL_PIXELFORMAT_MJPG) {
        પાછા SDL_ConvertPixels_STB(width, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    }

#ifdef SDL_HAVE_YUV
    જો (SDL_ISPIXELFORMAT_FOURCC(src_format) && SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        પાછા SDL_ConvertPixels_YUV_to_YUV(width, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } નહીંતર જો (SDL_ISPIXELFORMAT_FOURCC(src_format)) {
        પાછા SDL_ConvertPixels_YUV_to_RGB(width, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } નહીંતર જો (SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        પાછા SDL_ConvertPixels_RGB_to_YUV(width, height, src_format, src_colorspace, src_properties, src, src_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    }
#નહીંતર
    જો (SDL_ISPIXELFORMAT_FOURCC(src_format) || SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
        પાછા SDL_SetError("SDL not built with YUV support");
    }
#endif

    // Fast path for same format copy
    જો (src_format == dst_format && src_colorspace == dst_colorspace) {
        જો (src_pitch == dst_pitch) {
            SDL_memcpy(dst, src, height * src_pitch);
        } નહીંતર {
            પૂર્ણાંક i;
            અચલ પૂર્ણાંક bpp = SDL_BYTESPERPIXEL(src_format);
            width *= bpp;
            માટે (i = height; i--;) {
                SDL_memcpy(dst, src, width);
                src = (અચલ Uint8 *)src + src_pitch;
                dst = (Uint8 *)dst + dst_pitch;
            }
        }
        પાછા true;
    }

    જો (!SDL_InitializeSurface(&src_surface, width, height, src_format, src_colorspace, src_properties, nonconst_src, src_pitch, true)) {
        પાછા false;
    }
    SDL_SetSurfaceBlendMode(&src_surface, SDL_BLENDMODE_NONE);

    જો (!SDL_InitializeSurface(&dst_surface, width, height, dst_format, dst_colorspace, dst_properties, dst, dst_pitch, true)) {
        પાછા false;
    }

    // Set up the rect and go!
    rect.x = 0;
    rect.y = 0;
    rect.w = width;
    rect.h = height;
    result = SDL_BlitSurfaceUnchecked(&src_surface, &rect, &dst_surface, &rect);

    SDL_DestroySurface(&src_surface);
    SDL_DestroySurface(&dst_surface);

    પાછા result;
}

bool SDL_ConvertPixels(પૂર્ણાંક width, પૂર્ણાંક height, SDL_PixelFormat src_format, અચલ શૂન્ય *src, પૂર્ણાંક src_pitch, SDL_PixelFormat dst_format, શૂન્ય *dst, પૂર્ણાંક dst_pitch)
{
    પાછા SDL_ConvertPixelsAndColorspace(width, height,
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

સ્થિર શૂન્ય SDL_PremultiplyAlpha_AXYZ8888(પૂર્ણાંક width, પૂર્ણાંક height, અચલ શૂન્ય *src, પૂર્ણાંક src_pitch, શૂન્ય *dst, પૂર્ણાંક dst_pitch)
{
    પૂર્ણાંક c;
    Uint32 srcpixel;
    Uint32 srcR, srcG, srcB, srcA;
    Uint32 dstpixel;
    Uint32 dstR, dstG, dstB, dstA;

    જ્યારે (height--) {
        અચલ Uint32 *src_px = (અચલ Uint32 *)src;
        Uint32 *dst_px = (Uint32 *)dst;
        માટે (c = width; c; --c) {
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
        src = (અચલ Uint8 *)src + src_pitch;
        dst = (Uint8 *)dst + dst_pitch;
    }
}

સ્થિર શૂન્ય SDL_PremultiplyAlpha_XYZA8888(પૂર્ણાંક width, પૂર્ણાંક height, અચલ શૂન્ય *src, પૂર્ણાંક src_pitch, શૂન્ય *dst, પૂર્ણાંક dst_pitch)
{
    પૂર્ણાંક c;
    Uint32 srcpixel;
    Uint32 srcR, srcG, srcB, srcA;
    Uint32 dstpixel;
    Uint32 dstR, dstG, dstB, dstA;

    જ્યારે (height--) {
        અચલ Uint32 *src_px = (અચલ Uint32 *)src;
        Uint32 *dst_px = (Uint32 *)dst;
        માટે (c = width; c; --c) {
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
        src = (અચલ Uint8 *)src + src_pitch;
        dst = (Uint8 *)dst + dst_pitch;
    }
}

સ્થિર શૂન્ય SDL_PremultiplyAlpha_AXYZ128(પૂર્ણાંક width, પૂર્ણાંક height, અચલ શૂન્ય *src, પૂર્ણાંક src_pitch, શૂન્ય *dst, પૂર્ણાંક dst_pitch)
{
    પૂર્ણાંક c;
    દશાંશ flR, flG, flB, flA;

    જ્યારે (height--) {
        અચલ દશાંશ *src_px = (અચલ દશાંશ *)src;
        દશાંશ *dst_px = (દશાંશ *)dst;
        માટે (c = width; c; --c) {
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
        src = (અચલ Uint8 *)src + src_pitch;
        dst = (Uint8 *)dst + dst_pitch;
    }
}

સ્થિર bool SDL_PremultiplyAlphaPixelsAndColorspace(પૂર્ણાંક width, પૂર્ણાંક height, SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, અચલ શૂન્ય *src, પૂર્ણાંક src_pitch, SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, શૂન્ય *dst, પૂર્ણાંક dst_pitch, bool linear)
{
    SDL_Surface *convert = ખાલી;
    શૂન્ય *final_dst = dst;
    પૂર્ણાંક final_dst_pitch = dst_pitch;
    SDL_PixelFormat format;
    SDL_Colorspace colorspace;
    bool result = false;

    CHECK_PARAM(!src) {
        પાછા SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!src_pitch) {
        પાછા SDL_InvalidParamError("src_pitch");
    }
    CHECK_PARAM(!dst) {
        પાછા SDL_InvalidParamError("dst");
    }
    CHECK_PARAM(!dst_pitch) {
        પાછા SDL_InvalidParamError("dst_pitch");
    }

    // Use a high precision format if we're converting to linear colorspace or using high precision pixel formats
    જો (linear ||
        SDL_ISPIXELFORMAT_10BIT(src_format) || SDL_BITSPERPIXEL(src_format) > 32 ||
        SDL_ISPIXELFORMAT_10BIT(dst_format) || SDL_BITSPERPIXEL(dst_format) > 32) {
        જો (src_format == SDL_PIXELFORMAT_ARGB128_FLOAT ||
            src_format == SDL_PIXELFORMAT_ABGR128_FLOAT) {
            format = src_format;
        } નહીંતર {
            format = SDL_PIXELFORMAT_ARGB128_FLOAT;
        }
    } નહીંતર {
        જો (src_format == SDL_PIXELFORMAT_ARGB8888 ||
            src_format == SDL_PIXELFORMAT_ABGR8888 ||
            src_format == SDL_PIXELFORMAT_RGBA8888 ||
            src_format == SDL_PIXELFORMAT_BGRA8888) {
            format = src_format;
        } નહીંતર {
            format = SDL_PIXELFORMAT_ARGB8888;
        }
    }
    જો (linear) {
        colorspace = SDL_COLORSPACE_SRGB_LINEAR;
    } નહીંતર {
        colorspace = SDL_COLORSPACE_SRGB;
    }

    જો (src_format != format || src_colorspace != colorspace) {
        convert = SDL_CreateSurfaceUninitialized(width, height, format);
        જો (!convert) {
            જાઓ done;
        }
        જો (!SDL_ConvertPixelsAndColorspace(width, height, src_format, src_colorspace, src_properties, src, src_pitch, format, colorspace, 0, convert->pixels, convert->pitch)) {
            જાઓ done;
        }

        src = convert->pixels;
        src_pitch = convert->pitch;
        dst = convert->pixels;
        dst_pitch = convert->pitch;

    } નહીંતર જો (dst_format != format || dst_colorspace != colorspace) {
        convert = SDL_CreateSurfaceUninitialized(width, height, format);
        જો (!convert) {
            જાઓ done;
        }
        dst = convert->pixels;
        dst_pitch = convert->pitch;
    }

    પસંદગી (format) {
    સ્થિતિ SDL_PIXELFORMAT_ARGB8888:
    સ્થિતિ SDL_PIXELFORMAT_ABGR8888:
        SDL_PremultiplyAlpha_AXYZ8888(width, height, src, src_pitch, dst, dst_pitch);
        તોડો;
    સ્થિતિ SDL_PIXELFORMAT_RGBA8888:
    સ્થિતિ SDL_PIXELFORMAT_BGRA8888:
        SDL_PremultiplyAlpha_XYZA8888(width, height, src, src_pitch, dst, dst_pitch);
        તોડો;
    સ્થિતિ SDL_PIXELFORMAT_ARGB128_FLOAT:
    સ્થિતિ SDL_PIXELFORMAT_ABGR128_FLOAT:
        SDL_PremultiplyAlpha_AXYZ128(width, height, src, src_pitch, dst, dst_pitch);
        તોડો;
    મૂળભૂત:
        SDL_SetError("Unexpected internal pixel format");
        જાઓ done;
    }

    જો (dst != final_dst) {
        જો (!SDL_ConvertPixelsAndColorspace(width, height, format, colorspace, 0, convert->pixels, convert->pitch, dst_format, dst_colorspace, dst_properties, final_dst, final_dst_pitch)) {
            જાઓ done;
        }
    }
    result = true;

done:
    જો (convert) {
        SDL_DestroySurface(convert);
    }
    પાછા result;
}

bool SDL_PremultiplyAlpha(પૂર્ણાંક width, પૂર્ણાંક height,
                         SDL_PixelFormat src_format, અચલ શૂન્ય *src, પૂર્ણાંક src_pitch,
                         SDL_PixelFormat dst_format, શૂન્ય *dst, પૂર્ણાંક dst_pitch, bool linear)
{
    SDL_Colorspace src_colorspace = SDL_GetDefaultColorspaceForFormat(src_format);
    SDL_Colorspace dst_colorspace = SDL_GetDefaultColorspaceForFormat(dst_format);

    પાછા SDL_PremultiplyAlphaPixelsAndColorspace(width, height, src_format, src_colorspace, 0, src, src_pitch, dst_format, dst_colorspace, 0, dst, dst_pitch, linear);
}

bool SDL_PremultiplySurfaceAlpha(SDL_Surface *surface, bool linear)
{
    SDL_Colorspace colorspace;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        પાછા SDL_InvalidParamError("surface");
    }

    colorspace = surface->colorspace;

    પાછા SDL_PremultiplyAlphaPixelsAndColorspace(surface->w, surface->h, surface->format, colorspace, surface->props, surface->pixels, surface->pitch, surface->format, colorspace, surface->props, surface->pixels, surface->pitch, linear);
}

bool SDL_ClearSurface(SDL_Surface *surface, દશાંશ r, દશાંશ g, દશાંશ b, દશાંશ a)
{
    SDL_Rect clip_rect;
    bool result = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        પાછા SDL_InvalidParamError("surface");
    }

    SDL_GetSurfaceClipRect(surface, &clip_rect);
    SDL_SetSurfaceClipRect(surface, ખાલી);

    જો (!SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_BYTESPERPIXEL(surface->format) <= કદ(Uint32)) {
        Uint32 color;

        color = SDL_MapSurfaceRGBA(surface,
                    (Uint8)SDL_roundf(SDL_clamp(r, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(g, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(b, 0.0f, 1.0f) * 255.0f),
                    (Uint8)SDL_roundf(SDL_clamp(a, 0.0f, 1.0f) * 255.0f));
        result = SDL_FillSurfaceRect(surface, ખાલી, color);
    } નહીંતર જો (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // We can't directly set an RGB value on a YUV surface
        SDL_Surface *tmp = SDL_CreateSurfaceUninitialized(surface->w, surface->h, SDL_PIXELFORMAT_ARGB8888);
        જો (!tmp) {
            જાઓ done;
        }

        જો (SDL_ClearSurface(tmp, r, g, b, a)) {
            result = SDL_ConvertPixelsAndColorspace(surface->w, surface->h, tmp->format, tmp->colorspace, tmp->props, tmp->pixels, tmp->pitch, surface->format, surface->colorspace, surface->props, surface->pixels, surface->pitch);
        }
        SDL_DestroySurface(tmp);
    } નહીંતર {
        // Take advantage of blit color conversion
        SDL_Surface *tmp = SDL_CreateSurfaceUninitialized(1, 1, SDL_PIXELFORMAT_RGBA128_FLOAT);
        જો (!tmp) {
            જાઓ done;
        }
        SDL_SetSurfaceColorspace(tmp, surface->colorspace);
        SDL_SetSurfaceBlendMode(tmp, SDL_BLENDMODE_NONE);

        દશાંશ *pixels = (દશાંશ *)tmp->pixels;
        pixels[0] = r;
        pixels[1] = g;
        pixels[2] = b;
        pixels[3] = a;

        result = SDL_BlitSurfaceScaled(tmp, ખાલી, surface, ખાલી, SDL_SCALEMODE_NEAREST);
        SDL_DestroySurface(tmp);
    }

done:
    SDL_SetSurfaceClipRect(surface, &clip_rect);

    પાછા result;
}

Uint32 SDL_MapSurfaceRGB(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b)
{
    પાછા SDL_MapSurfaceRGBA(surface, r, g, b, SDL_ALPHA_OPAQUE);
}

Uint32 SDL_MapSurfaceRGBA(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        પાછા true;
    }
    પાછા SDL_MapRGBA(surface->fmt, surface->palette, r, g, b, a);
}

// This function Copyright 2023 Collabora Ltd., contributed to SDL under the ZLib license
bool SDL_ReadSurfacePixel(SDL_Surface *surface, પૂર્ણાંક x, પૂર્ણાંક y, Uint8 *r, Uint8 *g, Uint8 *b, Uint8 *a)
{
    Uint32 pixel = 0;
    size_t bytes_per_pixel;
    Uint8 unused;
    Uint8 *p;
    bool result = false;

    જો (r) {
        *r = 0;
    } નહીંતર {
        r = &unused;
    }

    જો (g) {
        *g = 0;
    } નહીંતર {
        g = &unused;
    }

    જો (b) {
        *b = 0;
    } નહીંતર {
        b = &unused;
    }

    જો (a) {
        *a = 0;
    } નહીંતર {
        a = &unused;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        પાછા SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        પાછા SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        પાછા SDL_InvalidParamError("y");
    }

    bytes_per_pixel = SDL_BYTESPERPIXEL(surface->format);

    જો (SDL_MUSTLOCK(surface)) {
        જો (!SDL_LockSurface(surface)) {
            પાછા false;
        }
    }

    p = (Uint8 *)surface->pixels + y * surface->pitch + x * bytes_per_pixel;

    જો (bytes_per_pixel <= કદ(pixel) &&
        !SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_COLORSPACEPRIMARIES(surface->colorspace) == SDL_COLOR_PRIMARIES_BT709) {
        /* Fill the appropriate number of least-significant bytes of pixel,
         * leaving the most-significant bytes set to zero */
#જો SDL_BYTEORDER == SDL_BIG_ENDIAN
        SDL_memcpy(((Uint8 *)&pixel) + (કદ(pixel) - bytes_per_pixel), p, bytes_per_pixel);
#નહીંતર
        SDL_memcpy(&pixel, p, bytes_per_pixel);
#endif
        SDL_GetRGBA(pixel, surface->fmt, surface->palette, r, g, b, a);
        result = true;
    } નહીંતર જો (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // FIXME: We need code to extract a single macroblock from a YUV surface
        SDL_Surface *converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        જો (converted) {
            result = SDL_ReadSurfacePixel(converted, x, y, r, g, b, a);
            SDL_DestroySurface(converted);
        }
    } નહીંતર {
        // This is really slow, but it gets the job done
        Uint8 rgba[4];

        જો (SDL_ConvertPixelsAndColorspace(1, 1, surface->format, surface->colorspace, surface->props, p, surface->pitch, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, rgba, કદ(rgba))) {
            *r = rgba[0];
            *g = rgba[1];
            *b = rgba[2];
            *a = rgba[3];
            result = true;
        }
    }

    જો (SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }
    પાછા result;
}

bool SDL_ReadSurfacePixelFloat(SDL_Surface *surface, પૂર્ણાંક x, પૂર્ણાંક y, દશાંશ *r, દશાંશ *g, દશાંશ *b, દશાંશ *a)
{
    દશાંશ unused;
    bool result = false;

    જો (r) {
        *r = 0.0f;
    } નહીંતર {
        r = &unused;
    }

    જો (g) {
        *g = 0.0f;
    } નહીંતર {
        g = &unused;
    }

    જો (b) {
        *b = 0.0f;
    } નહીંતર {
        b = &unused;
    }

    જો (a) {
        *a = 0.0f;
    } નહીંતર {
        a = &unused;
    }

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        પાછા SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        પાછા SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        પાછા SDL_InvalidParamError("y");
    }

    જો (SDL_BYTESPERPIXEL(surface->format) <= કદ(Uint32) &&
        !SDL_ISPIXELFORMAT_FOURCC(surface->format) &&
        SDL_COLORSPACEPRIMARIES(surface->colorspace) == SDL_COLOR_PRIMARIES_BT709) {
        Uint8 r8, g8, b8, a8;

        જો (SDL_ReadSurfacePixel(surface, x, y, &r8, &g8, &b8, &a8)) {
            *r = (દશાંશ)r8 / 255.0f;
            *g = (દશાંશ)g8 / 255.0f;
            *b = (દશાંશ)b8 / 255.0f;
            *a = (દશાંશ)a8 / 255.0f;
            result = true;
        }
    } નહીંતર જો (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        // FIXME: We need code to extract a single macroblock from a YUV surface
        SDL_Surface *converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        જો (converted) {
            result = SDL_ReadSurfacePixelFloat(converted, x, y, r, g, b, a);
            SDL_DestroySurface(converted);
        }
    } નહીંતર {
        // This is really slow, but it gets the job done
        દશાંશ rgba[4];
        Uint8 *p;

        જો (SDL_MUSTLOCK(surface)) {
            જો (!SDL_LockSurface(surface)) {
                પાછા false;
            }
        }

        p = (Uint8 *)surface->pixels + y * surface->pitch + x * SDL_BYTESPERPIXEL(surface->format);

        જો (surface->format == SDL_PIXELFORMAT_RGBA128_FLOAT) {
            SDL_memcpy(rgba, p, કદ(rgba));
            result = true;
        } નહીંતર {
            SDL_Colorspace src_colorspace = surface->colorspace;
            SDL_Colorspace dst_colorspace = (src_colorspace == SDL_COLORSPACE_SRGB_LINEAR ? SDL_COLORSPACE_SRGB_LINEAR : SDL_COLORSPACE_SRGB);

            જો (SDL_ConvertPixelsAndColorspace(1, 1, surface->format, src_colorspace, surface->props, p, surface->pitch, SDL_PIXELFORMAT_RGBA128_FLOAT, dst_colorspace, 0, rgba, કદ(rgba))) {
                result = true;
            }
        }

        જો (result) {
            *r = rgba[0];
            *g = rgba[1];
            *b = rgba[2];
            *a = rgba[3];
        }

        જો (SDL_MUSTLOCK(surface)) {
            SDL_UnlockSurface(surface);
        }
    }
    પાછા result;
}

bool SDL_WriteSurfacePixel(SDL_Surface *surface, પૂર્ણાંક x, પૂર્ણાંક y, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    Uint32 pixel = 0;
    size_t bytes_per_pixel;
    Uint8 *p;
    bool result = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        પાછા SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        પાછા SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        પાછા SDL_InvalidParamError("y");
    }

    bytes_per_pixel = SDL_BYTESPERPIXEL(surface->format);

    જો (SDL_MUSTLOCK(surface)) {
        જો (!SDL_LockSurface(surface)) {
            પાછા false;
        }
    }

    p = (Uint8 *)surface->pixels + y * surface->pitch + x * bytes_per_pixel;

    જો (bytes_per_pixel <= કદ(pixel) && !SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        pixel = SDL_MapRGBA(surface->fmt, surface->palette, r, g, b, a);
#જો SDL_BYTEORDER == SDL_BIG_ENDIAN
        SDL_memcpy(p, ((Uint8 *)&pixel) + (કદ(pixel) - bytes_per_pixel), bytes_per_pixel);
#નહીંતર
        SDL_memcpy(p, &pixel, bytes_per_pixel);
#endif
        result = true;
    } નહીંતર જો (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        result = SDL_Unsupported();
    } નહીંતર {
        // This is really slow, but it gets the job done
        Uint8 rgba[4];

        rgba[0] = r;
        rgba[1] = g;
        rgba[2] = b;
        rgba[3] = a;
        result = SDL_ConvertPixelsAndColorspace(1, 1, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, rgba, કદ(rgba), surface->format, surface->colorspace, surface->props, p, surface->pitch);
    }

    જો (SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }
    પાછા result;
}

bool SDL_WriteSurfacePixelFloat(SDL_Surface *surface, પૂર્ણાંક x, પૂર્ણાંક y, દશાંશ r, દશાંશ g, દશાંશ b, દશાંશ a)
{
    bool result = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface) || !surface->format || !surface->pixels) {
        પાછા SDL_InvalidParamError("surface");
    }

    CHECK_PARAM(x < 0 || x >= surface->w) {
        પાછા SDL_InvalidParamError("x");
    }

    CHECK_PARAM(y < 0 || y >= surface->h) {
        પાછા SDL_InvalidParamError("y");
    }

    જો (SDL_BYTESPERPIXEL(surface->format) <= કદ(Uint32) && !SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        Uint8 r8, g8, b8, a8;

        r8 = (Uint8)SDL_round(SDL_clamp(r, 0.0f, 1.0f) * 255.0f);
        g8 = (Uint8)SDL_round(SDL_clamp(g, 0.0f, 1.0f) * 255.0f);
        b8 = (Uint8)SDL_round(SDL_clamp(b, 0.0f, 1.0f) * 255.0f);
        a8 = (Uint8)SDL_round(SDL_clamp(a, 0.0f, 1.0f) * 255.0f);
        જો (SDL_WriteSurfacePixel(surface, x, y, r8, g8, b8, a8)) {
            result = true;
        }
    } નહીંતર જો (SDL_ISPIXELFORMAT_FOURCC(surface->format)) {
        result = SDL_Unsupported();
    } નહીંતર {
        // This is really slow, but it gets the job done
        દશાંશ rgba[4];
        Uint8 *p;

        જો (SDL_MUSTLOCK(surface)) {
            જો (!SDL_LockSurface(surface)) {
                પાછા false;
            }
        }

        p = (Uint8 *)surface->pixels + y * surface->pitch + x * SDL_BYTESPERPIXEL(surface->format);

        rgba[0] = r;
        rgba[1] = g;
        rgba[2] = b;
        rgba[3] = a;

        જો (surface->format == SDL_PIXELFORMAT_RGBA128_FLOAT) {
            SDL_memcpy(p, rgba, કદ(rgba));
            result = true;
        } નહીંતર {
            SDL_Colorspace dst_colorspace = surface->colorspace;
            SDL_Colorspace src_colorspace = (dst_colorspace == SDL_COLORSPACE_SRGB_LINEAR ? SDL_COLORSPACE_SRGB_LINEAR : SDL_COLORSPACE_SRGB);

            result = SDL_ConvertPixelsAndColorspace(1, 1, SDL_PIXELFORMAT_RGBA128_FLOAT, src_colorspace, 0, rgba, કદ(rgba), surface->format, dst_colorspace, surface->props, p, surface->pitch);
        }

        જો (SDL_MUSTLOCK(surface)) {
            SDL_UnlockSurface(surface);
        }
    }
    પાછા result;
}

/*
 * Free a surface created by the above function.
 */
શૂન્ય SDL_DestroySurface(SDL_Surface *surface)
{
    જો (!SDL_SurfaceValid(surface)) {
        પાછા;
    }
    જો (surface->internal_flags & SDL_INTERNAL_SURFACE_DONTFREE) {
        પાછા;
    }
    જો (--surface->refcount > 0) {
        પાછા;
    }

    SDL_RemoveSurfaceAlternateImages(surface);

    SDL_DestroyProperties(surface->props);

    SDL_InvalidateMap(&surface->map);

    જ્યારે (surface->locked > 0) {
        SDL_UnlockSurface(surface);
    }
#ifdef SDL_HAVE_RLE
    જો (surface->internal_flags & SDL_INTERNAL_SURFACE_RLEACCEL) {
        SDL_UnRLESurface(surface);
    }
#endif
    SDL_SetSurfacePalette(surface, ખાલી);

    જો (surface->flags & SDL_SURFACE_PREALLOCATED) {
        // Don't free
    } નહીંતર જો (surface->flags & SDL_SURFACE_SIMD_ALIGNED) {
        // Free aligned
        SDL_aligned_free(surface->pixels);
    } નહીંતર {
        // Normal
        SDL_free(surface->pixels);
    }

    surface->reserved = ખાલી;

    જો (!(surface->internal_flags & SDL_INTERNAL_SURFACE_ઢગલો)) {
        SDL_free(surface);
    }
}

SDL_Surface *SDL_LoadSurface_IO(SDL_IOStream *src, bool closeio)
{
    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        પાછા ખાલી;
    }

    જો (SDL_IsBMP(src)) {
        પાછા SDL_LoadBMP_IO(src, closeio);
    } નહીંતર જો (SDL_IsPNG(src)) {
        પાછા SDL_LoadPNG_IO(src, closeio);
    } નહીંતર જો (SDL_IsJPG(src)) {
        પાછા SDL_LoadJPG_IO(src, closeio);
    } નહીંતર {
        જો (closeio) {
            SDL_CloseIO(src);
        }
        SDL_SetError("Unsupported image format");
        પાછા ખાલી;
    }
}

SDL_Surface *SDL_LoadSurface(અચલ અક્ષર *file)
{
    SDL_IOStream *stream = SDL_IOFromFile(file, "rb");
    જો (!stream) {
        પાછા ખાલી;
    }

    પાછા SDL_LoadSurface_IO(stream, true);
}
