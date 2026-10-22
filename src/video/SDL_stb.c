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

#ضمن "SDL_stb_c.h"
#ضمن "SDL_surface_c.h"
#ضمن "SDL_yuv_c.h"

/* STB image conversion */
#ifndef SDL_DISABLE_STB
#define SDL_HAVE_STB
#endif

#ifdef SDL_HAVE_STB
////////////////////////////////////////////////////////////////////////////
#define malloc SDL_malloc
#define realloc SDL_realloc
#define حرر SDL_free
#undef memcpy
#define memcpy SDL_memcpy
#undef memset
#define memset SDL_memset
#undef strcmp
#define strcmp SDL_strcmp
#undef strncmp
#define strncmp SDL_strncmp
#define strtol SDL_strtol

#define abs SDL_abs
#define pow SDL_pow
#define ldexp SDL_scalbn

#define STB_IMAGE_STATIC
#define STBI_NO_THREAD_LOCALS
#define STBI_FAILURE_USERMSG
#إذا defined(SDL_NEON_INTRINSICS)
#define STBI_NEON
#endif
#define STBI_ONLY_PNG
#define STBI_ONLY_JPEG
#define STBI_NO_GIF
#define STBI_NO_HDR
#define STBI_NO_LINEAR
#define STBI_NO_STDIO
#define STBI_ASSERT SDL_assert
#define STB_IMAGE_IMPLEMENTATION
#ضمن "stb_image.h"

////////////////////////////////////////////////////////////////////////////
#define MZ_ASSERT(x) SDL_assert(x)
//#undef memcpy
//#define memcpy SDL_memcpy
//#undef memset
//#define memset SDL_memset
#إذا SDL_BYTEORDER == SDL_LIL_ENDIAN
#define MINIZ_LITTLE_ENDIAN 1
#وإلا
#define MINIZ_LITTLE_ENDIAN 0
#endif
#define MINIZ_USE_UNALIGNED_LOADS_AND_STORES 0
#define MINIZ_SDL_NOUNUSED
#ضمن "miniz.h"

#undef memset
#endif // SDL_HAVE_STB

#ifdef SDL_HAVE_STB
ساكن bool SDL_ConvertPixels_MJPG_to_NV12(صحيح width, صحيح height, ثابت فراغ *src, صحيح src_pitch, فراغ *dst, صحيح dst_pitch)
{
    صحيح w = 0, h = 0, format = 0;
    stbi__context s;
    stbi__start_mem(&s, src, src_pitch);

    stbi__result_info ri;
    SDL_zero(ri);
    ri.bits_per_channel = 8;
    ri.channel_order = STBI_ORDER_RGB;
    ri.رقم_channels = 0;

    stbi__nv12 nv12;
    nv12.w = width;
    nv12.h = height;
    nv12.pitch = dst_pitch;
    nv12.y = (stbi_uc *)dst;
    nv12.uv = nv12.y + (nv12.h * nv12.pitch);

    فراغ *pixels = stbi__jpeg_load(&s, &w, &h, &format, 4, &nv12, &ri);
    إذا (!pixels) {
        أرجع false;
    }
    أرجع true;
}
#endif // SDL_HAVE_STB

bool SDL_ConvertPixels_STB(صحيح width, صحيح height,
                           SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ثابت فراغ *src, صحيح src_pitch,
                           SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, فراغ *dst, صحيح dst_pitch)
{
#ifdef SDL_HAVE_STB
    إذا (src_format == SDL_PIXELFORMAT_MJPG) {
        إذا (dst_format == SDL_PIXELFORMAT_NV12) {
            أرجع SDL_ConvertPixels_MJPG_to_NV12(width, height, src, src_pitch, dst, dst_pitch);
        } وإلا إذا (
            dst_format == SDL_PIXELFORMAT_YV12 ||
            dst_format == SDL_PIXELFORMAT_IYUV ||
            dst_format == SDL_PIXELFORMAT_YUY2 ||
            dst_format == SDL_PIXELFORMAT_UYVY ||
            dst_format == SDL_PIXELFORMAT_YVYU ||
            dst_format == SDL_PIXELFORMAT_NV21 ||
            dst_format == SDL_PIXELFORMAT_P010
        ) {
            size_t temp_size = 0;
            size_t temp_pitch = 0;
            إذا (!SDL_CalculateYUVSize(dst_format, width, height, &temp_size, &temp_pitch)) {
                أرجع false;
            }
            فراغ *temp_pixels = SDL_malloc(temp_size);
            إذا (!temp_pixels) {
                أرجع false;
            }

            إذا (!SDL_ConvertPixels_MJPG_to_NV12(width, height, src, src_pitch, temp_pixels, (صحيح)temp_pitch)) {
                SDL_free(temp_pixels);
                أرجع false;
            }

            bool result = SDL_ConvertPixelsAndColorspace(width, height, SDL_PIXELFORMAT_NV12, src_colorspace, 0 /*props*/, temp_pixels, (صحيح)temp_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
            SDL_free(temp_pixels);
            أرجع result;
        }
    }

    bool result;
    صحيح w = 0, h = 0, format = 0;
    صحيح len = (src_format == SDL_PIXELFORMAT_MJPG) ? src_pitch : (height * src_pitch);
    فراغ *pixels = stbi_load_from_memory(src, len, &w, &h, &format, 4);
    إذا (!pixels) {
        أرجع false;
    }

    إذا (w == width && h == height) {
        result = SDL_ConvertPixelsAndColorspace(w, h, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, pixels, width * 4, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } وإلا {
        result = SDL_SetError("Expected image size %dx%d, actual size %dx%d", width, height, w, h);
    }
    stbi_image_free(pixels);

    أرجع result;
#وإلا
    أرجع SDL_SetError("SDL not built with STB image support");
#endif
}

#ifdef SDL_HAVE_STB
ساكن صحيح IMG_LoadSTB_IO_read(فراغ *user, حرف *data, صحيح size)
{
    size_t amount = SDL_ReadIO((SDL_IOStream*)user, data, size);
    أرجع (صحيح)amount;
}

ساكن فراغ IMG_LoadSTB_IO_skip(فراغ *user, صحيح n)
{
    SDL_SeekIO((SDL_IOStream*)user, n, SDL_IO_SEEK_CUR);
}

ساكن صحيح IMG_LoadSTB_IO_eof(فراغ *user)
{
    SDL_IOStream *src = (SDL_IOStream*)user;
    أرجع SDL_GetIOStatus(src) == SDL_IO_STATUS_EOF;
}

ساكن SDL_Surface *SDL_LoadSTB_IO(SDL_IOStream *src)
{
    Sint64 start;
    Uint8 magic[26];
    صحيح w, h, format;
    stbi_uc *pixels;
    stbi_io_callbacks rw_callbacks;
    SDL_Surface *surface = عدم;
    bool use_palette = false;
    unsigned صحيح palette_colors[256];

    // src has already been validated
    start = SDL_TellIO(src);

    إذا (SDL_ReadIO(src, magic, حجم(magic)) == حجم(magic)) {
        ثابت Uint8 PNG_COLOR_INDEXED = 3;
        إذا (magic[0] == 0x89 &&
            magic[1] == 'P' &&
            magic[2] == 'N' &&
            magic[3] == 'G' &&
            magic[12] == 'I' &&
            magic[13] == 'H' &&
            magic[14] == 'D' &&
            magic[15] == 'R' &&
            magic[25] == PNG_COLOR_INDEXED) {
            use_palette = true;
        }
    }
    SDL_SeekIO(src, start, SDL_IO_SEEK_SET);

    /* Load the image data */
    rw_callbacks.اقرأ = IMG_LoadSTB_IO_read;
    rw_callbacks.skip = IMG_LoadSTB_IO_skip;
    rw_callbacks.eof = IMG_LoadSTB_IO_eof;
    w = h = format = 0; /* silence warning */
    إذا (use_palette) {
        /* Unused palette entries will be opaque white */
        SDL_memset(palette_colors, 0xff, حجم(palette_colors));

        pixels = stbi_load_from_callbacks_with_palette(
            &rw_callbacks,
            src,
            &w,
            &h,
            palette_colors,
            SDL_arraysize(palette_colors)
        );
    } وإلا {
        pixels = stbi_load_from_callbacks(
            &rw_callbacks,
            src,
            &w,
            &h,
            &format,
            STBI_default
        );
    }
    إذا (!pixels) {
        SDL_SeekIO(src, start, SDL_IO_SEEK_SET);
        أرجع عدم;
    }

    إذا (use_palette) {
        surface = SDL_CreateSurfaceFrom(
            w,
            h,
            SDL_PIXELFORMAT_INDEX8,
            pixels,
            w
        );
        إذا (surface) {
            bool has_colorkey = false;
            صحيح colorkey_index = -1;
            bool has_alpha = false;
            SDL_Palette *palette = SDL_CreateSurfacePalette(surface);
            إذا (palette) {
                صحيح i;
                Uint8 *palette_bytes = (Uint8 *)palette_colors;

                لكل (i = 0; i < palette->ncolors; i++) {
                    palette->colors[i].r = *palette_bytes++;
                    palette->colors[i].g = *palette_bytes++;
                    palette->colors[i].b = *palette_bytes++;
                    palette->colors[i].a = *palette_bytes++;
                    إذا (palette->colors[i].a != SDL_ALPHA_OPAQUE) {
                        إذا (palette->colors[i].a == SDL_ALPHA_TRANSPARENT && !has_colorkey) {
                            has_colorkey = true;
                            colorkey_index = i;
                        } وإلا {
                            /* Partial opacity or multiple colorkeys */
                            has_alpha = true;
                        }
                    }
                }
            }
            إذا (has_alpha) {
                SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
            } وإلا إذا (has_colorkey) {
                SDL_Set_Surface_Color_مفتاح(surface, true, colorkey_index);
            }

            /* FIXME: This sucks. It'd be better to allocate the surface first, then
             * write directly to the pixel buffer:
             * https://github.com/nothings/stb/issues/58
             * -flibit
             */
            surface->flags &= ~SDL_SURFACE_PREALLOCATED;
        }

    } وإلا إذا (format == STBI_grey || format == STBI_rgb || format == STBI_rgb_alpha) {
        surface = SDL_CreateSurfaceFrom(
            w,
            h,
            (format == STBI_rgb_alpha) ? SDL_PIXELFORMAT_RGBA32 :
            (format == STBI_rgb) ? SDL_PIXELFORMAT_RGB24 :
            SDL_PIXELFORMAT_INDEX8,
            pixels,
            w * format
        );
        إذا (surface) {
            /* Set a grayscale palette for gray images */
            إذا (surface->format == SDL_PIXELFORMAT_INDEX8) {
                SDL_Palette *palette = SDL_CreateSurfacePalette(surface);
                إذا (palette) {
                    صحيح i;

                    لكل (i = 0; i < palette->ncolors; i++) {
                        palette->colors[i].r = (Uint8)i;
                        palette->colors[i].g = (Uint8)i;
                        palette->colors[i].b = (Uint8)i;
                    }
                }
            }

            /* FIXME: This sucks. It'd be better to allocate the surface first, then
             * write directly to the pixel buffer:
             * https://github.com/nothings/stb/issues/58
             * -flibit
             */
            surface->flags &= ~SDL_SURFACE_PREALLOCATED;
        }

    } وإلا إذا (format == STBI_grey_alpha) {
        surface = SDL_CreateSurfaceUninitialized(w, h, SDL_PIXELFORMAT_RGBA32);
        إذا (surface) {
            Uint8 *src_ptr = pixels;
            Uint8 *dst = (Uint8 *)surface->pixels;
            صحيح skip = surface->pitch - (surface->w * 4);
            صحيح row, col;

            لكل (row = 0; row < h; ++row) {
                لكل (col = 0; col < w; ++col) {
                    Uint8 c = *src_ptr++;
                    Uint8 a = *src_ptr++;
                    *dst++ = c;
                    *dst++ = c;
                    *dst++ = c;
                    *dst++ = a;
                }
                dst += skip;
            }
            stbi_image_free(pixels);
        }
    } وإلا {
        SDL_SetError("Unknown image format: %d", format);
    }

    إذا (!surface) {
        /* The error message should already be set */
        stbi_image_free(pixels); /* calls SDL_free() */
        SDL_SeekIO(src, start, SDL_IO_SEEK_SET);
    }
    أرجع surface;
}
#endif // SDL_HAVE_STB

/* FIXME: This is a copypaste from JPEGLIB! Pull that out of the ifdefs */
/* Define this for quicker (but less perfect) JPEG identification */
#define FAST_IS_JPEG

/* See if an image is contained in a data source */
bool SDL_IsJPG(SDL_IOStream *src)
{
    Sint64 start;
    bool is_JPG;
    bool in_scan;
    Uint8 magic[4];

    /* This detection code is by Steaphan Greene <stea@cs.binghamton.edu> */
    /* Blame me, not Sam, if this doesn't work right. */
    /* And don't forget to report the problem to the the sdl list too! */

    إذا (!src) {
        أرجع false;
    }

    start = SDL_TellIO(src);
    is_JPG = false;
    in_scan = false;
    إذا (SDL_ReadIO(src, magic, 2) == 2) {
        إذا ( (magic[0] == 0xFF) && (magic[1] == 0xD8) ) {
            is_JPG = true;
            طالما (is_JPG) {
                إذا (SDL_ReadIO(src, magic, 2) != 2) {
                    is_JPG = false;
                } وإلا إذا ( (magic[0] != 0xFF) && !in_scan ) {
                    is_JPG = false;
                } وإلا إذا ( (magic[0] != 0xFF) || (magic[1] == 0xFF) ) {
                    /* Extra padding in JPEG (legal) */
                    /* or this is data and we are scanning */
                    SDL_SeekIO(src, -1, SDL_IO_SEEK_CUR);
                } وإلا إذا (magic[1] == 0xD9) {
                    /* Got to end of good JPEG */
                    اكسر;
                } وإلا إذا ( in_scan && (magic[1] == 0x00) ) {
                    /* This is an encoded 0xFF within the data */
                } وإلا إذا ( (magic[1] >= 0xD0) && (magic[1] < 0xD9) ) {
                    /* These have nothing else */
                } وإلا إذا (SDL_ReadIO(src, magic+2, 2) != 2) {
                    is_JPG = false;
                } وإلا {
                    /* Yes, it's big-endian */
                    Sint64 innerStart;
                    Uint32 size;
                    Sint64 end;
                    innerStart = SDL_TellIO(src);
                    size = (magic[2] << 8) + magic[3];
                    end = SDL_SeekIO(src, size-2, SDL_IO_SEEK_CUR);
                    إذا ( end != innerStart + size - 2 ) {
                        is_JPG = false;
                    }
                    إذا ( magic[1] == 0xDA ) {
                        /* Now comes the actual JPEG meat */
#ifdef  FAST_IS_JPEG
                        /* Ok, I'm convinced.  It is a JPEG. */
                        اكسر;
#وإلا
                        /* I'm not convinced.  Prove it! */
                        in_scan = true;
#endif
                    }
                }
            }
        }
    }
    SDL_SeekIO(src, start, SDL_IO_SEEK_SET);
    أرجع is_JPG;
}

SDL_Surface *SDL_LoadJPG_IO(SDL_IOStream *src, bool closeio)
{
    SDL_Surface *surface = عدم;

    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        اذهب done;
    }

    إذا (!SDL_IsJPG(src)) {
        SDL_SetError("File is not a JPEG file");
        اذهب done;
    }

#ifdef SDL_HAVE_STB
    surface = SDL_LoadSTB_IO(src);
#وإلا
    SDL_SetError("SDL not built with STB image support");
#endif // SDL_HAVE_STB

done:
    إذا (src && closeio) {
        SDL_CloseIO(src);
    }
    أرجع surface;
}

SDL_Surface *SDL_LoadJPG(ثابت حرف *file)
{
    SDL_IOStream *stream = SDL_IOFromFile(file, "rb");
    إذا (!stream) {
        أرجع عدم;
    }

    أرجع SDL_LoadJPG_IO(stream, true);
}

bool SDL_IsPNG(SDL_IOStream *src)
{
    Sint64 start;
    Uint8 magic[4];
    bool is_PNG;

    is_PNG = false;
    start = SDL_TellIO(src);
    إذا (start >= 0) {
        إذا (SDL_ReadIO(src, magic, حجم(magic)) == حجم(magic)) {
            إذا (magic[0] == 0x89 &&
                magic[1] == 'P' &&
                magic[2] == 'N' &&
                magic[3] == 'G') {
                is_PNG = true;
            }
        }
        SDL_SeekIO(src, start, SDL_IO_SEEK_SET);
    }

    أرجع is_PNG;
}

SDL_Surface *SDL_LoadPNG_IO(SDL_IOStream *src, bool closeio)
{
    SDL_Surface *surface = عدم;

    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        اذهب done;
    }

    إذا (!SDL_IsPNG(src)) {
        SDL_SetError("File is not a PNG file");
        اذهب done;
    }

#ifdef SDL_HAVE_STB
    surface = SDL_LoadSTB_IO(src);
#وإلا
    SDL_SetError("SDL not built with STB image support");
#endif // SDL_HAVE_STB

done:
    إذا (src && closeio) {
        SDL_CloseIO(src);
    }
    أرجع surface;
}

SDL_Surface *SDL_LoadPNG(ثابت حرف *file)
{
    SDL_IOStream *stream = SDL_IOFromFile(file, "rb");
    إذا (!stream) {
        أرجع عدم;
    }

    أرجع SDL_LoadPNG_IO(stream, true);
}

bool SDL_SavePNG_IO(SDL_Surface *surface, SDL_IOStream *dst, bool closeio)
{
    bool retval = false;
    Uint8 *plte = عدم;
    Uint8 *trns = عدم;
    bool free_surface = false;

    // Make sure we have something to save
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        اذهب done;
    }
    CHECK_PARAM(!dst) {
        SDL_InvalidParamError("dst");
        اذهب done;
    }

#ifdef SDL_HAVE_STB
    صحيح plte_size = 0;
    صحيح trns_size = 0;

    إذا (SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        إذا (!surface->palette) {
            SDL_SetError("Indexed surfaces must have a palette");
            اذهب done;
        }

        إذا (surface->format != SDL_PIXELFORMAT_INDEX8) {
            surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_INDEX8);
            إذا (!surface) {
                اذهب done;
            }
            free_surface = true;
        }

        plte_size = surface->palette->ncolors * 3;
        trns_size = surface->palette->ncolors;
        plte = (Uint8 *)SDL_malloc(plte_size);
        trns = (Uint8 *)SDL_malloc(trns_size);
        إذا (!plte || !trns) {
            اذهب done;
        }
        SDL_Color *colors = surface->palette->colors;
        لكل (صحيح i = 0; i < surface->palette->ncolors; ++i) {
            plte[i * 3 + 0] = colors[i].r;
            plte[i * 3 + 1] = colors[i].g;
            plte[i * 3 + 2] = colors[i].b;
            trns[i] = colors[i].a;
        }
    } وإلا {
        إذا (surface->format != SDL_PIXELFORMAT_RGBA32) {
            surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);
            إذا (!surface) {
                اذهب done;
            }
            free_surface = true;
        }
    }

    size_t size = 0;
    فراغ *png = tdefl_write_image_to_png_file_in_memory_ex(surface->pixels, surface->w, surface->h, SDL_BYTESPERPIXEL(surface->format), surface->pitch, &size, 6, MZ_FALSE, plte, plte_size, trns, trns_size);
    إذا (png) {
        إذا (SDL_WriteIO(dst, png, size)) {
            retval = true;
        }
        mz_free(png); /* calls SDL_free() */
    } وإلا {
        SDL_SetError("Failed to convert and save image");
    }

#وإلا
    SDL_SetError("SDL not built with STB image support");
#endif

done:
    إذا (free_surface) {
        SDL_DestroySurface(surface);
    }
    SDL_free(plte);
    SDL_free(trns);

    إذا (dst && closeio) {
        retval &= SDL_CloseIO(dst);
    }
    أرجع retval;
}

bool SDL_SavePNG(SDL_Surface *surface, ثابت حرف *file)
{
#ifdef SDL_HAVE_STB
    // Make sure we have something to save
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        أرجع SDL_InvalidParamError("surface");
    }

    إذا (SDL_ISPIXELFORMAT_INDEXED(surface->format) && !surface->palette) {
        أرجع SDL_SetError("Indexed surfaces must have a palette");
    }
    SDL_IOStream *stream = SDL_IOFromFile(file, "wb");
    إذا (!stream) {
        أرجع false;
    }

    أرجع SDL_SavePNG_IO(surface, stream, true);
#وإلا
    أرجع SDL_SetError("SDL not built with STB image support");
#endif
}
