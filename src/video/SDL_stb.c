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
#অন্তর্ভাব "SDL_internal.h"

#অন্তর্ভাব "SDL_stb_c.h"
#অন্তর্ভাব "SDL_surface_c.h"
#অন্তর্ভাব "SDL_yuv_c.h"

/* STB image conversion */
#ifndef SDL_DISABLE_STB
#define SDL_HAVE_STB
#endif

#ifdef SDL_HAVE_STB
////////////////////////////////////////////////////////////////////////////
#define malloc SDL_malloc
#define realloc SDL_realloc
#define মুক্ত SDL_free
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
#যদি defined(SDL_NEON_INTRINSICS)
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
#অন্তর্ভাব "stb_image.h"

////////////////////////////////////////////////////////////////////////////
#define MZ_ASSERT(x) SDL_assert(x)
//#undef memcpy
//#define memcpy SDL_memcpy
//#undef memset
//#define memset SDL_memset
#যদি SDL_BYTEORDER == SDL_LIL_ENDIAN
#define MINIZ_LITTLE_ENDIAN 1
#অন্যথা
#define MINIZ_LITTLE_ENDIAN 0
#endif
#define MINIZ_USE_UNALIGNED_LOADS_AND_STORES 0
#define MINIZ_SDL_NOUNUSED
#অন্তর্ভাব "miniz.h"

#undef memset
#endif // SDL_HAVE_STB

#ifdef SDL_HAVE_STB
স্থির bool SDL_ConvertPixels_MJPG_to_NV12(পূর্ণসংখ্যা width, পূর্ণসংখ্যা height, ধ্রুবক শূন্য *src, পূর্ণসংখ্যা src_pitch, শূন্য *dst, পূর্ণসংখ্যা dst_pitch)
{
    পূর্ণসংখ্যা w = 0, h = 0, format = 0;
    stbi__context s;
    stbi__start_mem(&s, src, src_pitch);

    stbi_ফলাফল_info ri;
    SDL_zero(ri);
    ri.bits_per_channel = 8;
    ri.channel_order = STBI_ORDER_RGB;
    ri.অঙ্ক_channels = 0;

    stbi__nv12 nv12;
    nv12.w = width;
    nv12.h = height;
    nv12.pitch = dst_pitch;
    nv12.y = (stbi_uc *)dst;
    nv12.uv = nv12.y + (nv12.h * nv12.pitch);

    শূন্য *pixels = stbi__jpeg_load(&s, &w, &h, &format, 4, &nv12, &ri);
    যদি (!pixels) {
        ফেরত false;
    }
    ফেরত true;
}
#endif // SDL_HAVE_STB

bool SDL_ConvertPixels_STB(পূর্ণসংখ্যা width, পূর্ণসংখ্যা height,
                           SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ধ্রুবক শূন্য *src, পূর্ণসংখ্যা src_pitch,
                           SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, শূন্য *dst, পূর্ণসংখ্যা dst_pitch)
{
#ifdef SDL_HAVE_STB
    যদি (src_format == SDL_PIXELFORMAT_MJPG) {
        যদি (dst_format == SDL_PIXELFORMAT_NV12) {
            ফেরত SDL_ConvertPixels_MJPG_to_NV12(width, height, src, src_pitch, dst, dst_pitch);
        } অন্যথা যদি (
            dst_format == SDL_PIXELFORMAT_YV12 ||
            dst_format == SDL_PIXELFORMAT_IYUV ||
            dst_format == SDL_PIXELFORMAT_YUY2 ||
            dst_format == SDL_PIXELFORMAT_UYVY ||
            dst_format == SDL_PIXELFORMAT_YVYU ||
            dst_format == SDL_PIXELFORMAT_NV21 ||
            dst_format == SDL_PIXELFORMAT_P010
        ) {
            size_t অস্থায়ী_আকার = 0;
            size_t অস্থায়ী_pitch = 0;
            যদি (!SDL_CalculateYUVSize(dst_format, width, height, &অস্থায়ী_আকার, &অস্থায়ী_pitch)) {
                ফেরত false;
            }
            শূন্য *অস্থায়ী_pixels = SDL_malloc(অস্থায়ী_আকার);
            যদি (!অস্থায়ী_pixels) {
                ফেরত false;
            }

            যদি (!SDL_ConvertPixels_MJPG_to_NV12(width, height, src, src_pitch, অস্থায়ী_pixels, (পূর্ণসংখ্যা)অস্থায়ী_pitch)) {
                SDL_free(অস্থায়ী_pixels);
                ফেরত false;
            }

            bool ফলাফল = SDL_ConvertPixelsAndColorspace(width, height, SDL_PIXELFORMAT_NV12, src_colorspace, 0 /*props*/, অস্থায়ী_pixels, (পূর্ণসংখ্যা)অস্থায়ী_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
            SDL_free(অস্থায়ী_pixels);
            ফেরত ফলাফল;
        }
    }

    bool ফলাফল;
    পূর্ণসংখ্যা w = 0, h = 0, format = 0;
    পূর্ণসংখ্যা len = (src_format == SDL_PIXELFORMAT_MJPG) ? src_pitch : (height * src_pitch);
    শূন্য *pixels = stbi_load_from_memory(src, len, &w, &h, &format, 4);
    যদি (!pixels) {
        ফেরত false;
    }

    যদি (w == width && h == height) {
        ফলাফল = SDL_ConvertPixelsAndColorspace(w, h, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, pixels, width * 4, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } অন্যথা {
        ফলাফল = SDL_SetError("Expected image size %dx%d, actual size %dx%d", width, height, w, h);
    }
    stbi_image_free(pixels);

    ফেরত ফলাফল;
#অন্যথা
    ফেরত SDL_SetError("SDL not built with STB image support");
#endif
}

#ifdef SDL_HAVE_STB
স্থির পূর্ণসংখ্যা IMG_LoadSTB_IO_read(শূন্য *user, অক্ষর *তথ্য, পূর্ণসংখ্যা আকার_2)
{
    size_t amount = SDL_ReadIO((SDL_IOStream*)user, তথ্য, আকার_2);
    ফেরত (পূর্ণসংখ্যা)amount;
}

স্থির শূন্য IMG_LoadSTB_IO_skip(শূন্য *user, পূর্ণসংখ্যা n)
{
    SDL_SeekIO((SDL_IOStream*)user, n, SDL_IO_SEEK_CUR);
}

স্থির পূর্ণসংখ্যা IMG_LoadSTB_IO_eof(শূন্য *user)
{
    SDL_IOStream *src = (SDL_IOStream*)user;
    ফেরত SDL_GetIOStatus(src) == SDL_IO_STATUS_EOF;
}

স্থির SDL_Surface *SDL_LoadSTB_IO(SDL_IOStream *src)
{
    Sint64 start;
    Uint8 magic[26];
    পূর্ণসংখ্যা w, h, format;
    stbi_uc *pixels;
    stbi_io_callbacks rw_callbacks;
    SDL_Surface *surface = ফাঁকা;
    bool use_palette = false;
    unsigned পূর্ণসংখ্যা palette_colors[256];

    // src has already been validated
    start = SDL_TellIO(src);

    যদি (SDL_ReadIO(src, magic, আকার(magic)) == আকার(magic)) {
        ধ্রুবক Uint8 PNG_COLOR_INDEXED = 3;
        যদি (magic[0] == 0x89 &&
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
    rw_callbacks.পঠ = IMG_LoadSTB_IO_read;
    rw_callbacks.skip = IMG_LoadSTB_IO_skip;
    rw_callbacks.eof = IMG_LoadSTB_IO_eof;
    w = h = format = 0; /* silence warning */
    যদি (use_palette) {
        /* Unused palette entries will be opaque white */
        SDL_memset(palette_colors, 0xff, আকার(palette_colors));

        pixels = stbi_load_from_callbacks_with_palette(
            &rw_callbacks,
            src,
            &w,
            &h,
            palette_colors,
            SDL_arraysize(palette_colors)
        );
    } অন্যথা {
        pixels = stbi_load_from_callbacks(
            &rw_callbacks,
            src,
            &w,
            &h,
            &format,
            STBI_default
        );
    }
    যদি (!pixels) {
        SDL_SeekIO(src, start, SDL_IO_SEEK_SET);
        ফেরত ফাঁকা;
    }

    যদি (use_palette) {
        surface = SDL_CreateSurfaceFrom(
            w,
            h,
            SDL_PIXELFORMAT_INDEX8,
            pixels,
            w
        );
        যদি (surface) {
            bool has_colorkey = false;
            পূর্ণসংখ্যা colorkey_সূচক = -1;
            bool has_alpha = false;
            SDL_Palette *palette = SDL_CreateSurfacePalette(surface);
            যদি (palette) {
                পূর্ণসংখ্যা i;
                Uint8 *palette_bytes = (Uint8 *)palette_colors;

                জন্য (i = 0; i < palette->ncolors; i++) {
                    palette->colors[i].r = *palette_bytes++;
                    palette->colors[i].g = *palette_bytes++;
                    palette->colors[i].b = *palette_bytes++;
                    palette->colors[i].a = *palette_bytes++;
                    যদি (palette->colors[i].a != SDL_ALPHA_OPAQUE) {
                        যদি (palette->colors[i].a == SDL_ALPHA_TRANSPARENT && !has_colorkey) {
                            has_colorkey = true;
                            colorkey_সূচক = i;
                        } অন্যথা {
                            /* Partial opacity or multiple colorkeys */
                            has_alpha = true;
                        }
                    }
                }
            }
            যদি (has_alpha) {
                SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
            } অন্যথা যদি (has_colorkey) {
                SDL_Set_Surface_Color_চাবি(surface, true, colorkey_সূচক);
            }

            /* FIXME: This sucks. It'd be better to allocate the surface first, then
             * write directly to the pixel buffer:
             * https://github.com/nothings/stb/issues/58
             * -flibit
             */
            surface->flags &= ~SDL_SURFACE_PREALLOCATED;
        }

    } অন্যথা যদি (format == STBI_grey || format == STBI_rgb || format == STBI_rgb_alpha) {
        surface = SDL_CreateSurfaceFrom(
            w,
            h,
            (format == STBI_rgb_alpha) ? SDL_PIXELFORMAT_RGBA32 :
            (format == STBI_rgb) ? SDL_PIXELFORMAT_RGB24 :
            SDL_PIXELFORMAT_INDEX8,
            pixels,
            w * format
        );
        যদি (surface) {
            /* Set a grayscale palette for gray images */
            যদি (surface->format == SDL_PIXELFORMAT_INDEX8) {
                SDL_Palette *palette = SDL_CreateSurfacePalette(surface);
                যদি (palette) {
                    পূর্ণসংখ্যা i;

                    জন্য (i = 0; i < palette->ncolors; i++) {
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

    } অন্যথা যদি (format == STBI_grey_alpha) {
        surface = SDL_CreateSurfaceUninitialized(w, h, SDL_PIXELFORMAT_RGBA32);
        যদি (surface) {
            Uint8 *src_ptr = pixels;
            Uint8 *dst = (Uint8 *)surface->pixels;
            পূর্ণসংখ্যা skip = surface->pitch - (surface->w * 4);
            পূর্ণসংখ্যা row, col;

            জন্য (row = 0; row < h; ++row) {
                জন্য (col = 0; col < w; ++col) {
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
    } অন্যথা {
        SDL_SetError("Unknown image format: %d", format);
    }

    যদি (!surface) {
        /* The error message should already be set */
        stbi_image_free(pixels); /* calls SDL_free() */
        SDL_SeekIO(src, start, SDL_IO_SEEK_SET);
    }
    ফেরত surface;
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

    যদি (!src) {
        ফেরত false;
    }

    start = SDL_TellIO(src);
    is_JPG = false;
    in_scan = false;
    যদি (SDL_ReadIO(src, magic, 2) == 2) {
        যদি ( (magic[0] == 0xFF) && (magic[1] == 0xD8) ) {
            is_JPG = true;
            যখন (is_JPG) {
                যদি (SDL_ReadIO(src, magic, 2) != 2) {
                    is_JPG = false;
                } অন্যথা যদি ( (magic[0] != 0xFF) && !in_scan ) {
                    is_JPG = false;
                } অন্যথা যদি ( (magic[0] != 0xFF) || (magic[1] == 0xFF) ) {
                    /* Extra padding in JPEG (legal) */
                    /* or this is data and we are scanning */
                    SDL_SeekIO(src, -1, SDL_IO_SEEK_CUR);
                } অন্যথা যদি (magic[1] == 0xD9) {
                    /* Got to end of good JPEG */
                    বিরতি;
                } অন্যথা যদি ( in_scan && (magic[1] == 0x00) ) {
                    /* This is an encoded 0xFF within the data */
                } অন্যথা যদি ( (magic[1] >= 0xD0) && (magic[1] < 0xD9) ) {
                    /* These have nothing else */
                } অন্যথা যদি (SDL_ReadIO(src, magic+2, 2) != 2) {
                    is_JPG = false;
                } অন্যথা {
                    /* Yes, it's big-endian */
                    Sint64 innerStart;
                    Uint32 আকার_2;
                    Sint64 end;
                    innerStart = SDL_TellIO(src);
                    আকার_2 = (magic[2] << 8) + magic[3];
                    end = SDL_SeekIO(src, আকার_2-2, SDL_IO_SEEK_CUR);
                    যদি ( end != innerStart + আকার_2 - 2 ) {
                        is_JPG = false;
                    }
                    যদি ( magic[1] == 0xDA ) {
                        /* Now comes the actual JPEG meat */
#ifdef  FAST_IS_JPEG
                        /* Ok, I'm convinced.  It is a JPEG. */
                        বিরতি;
#অন্যথা
                        /* I'm not convinced.  Prove it! */
                        in_scan = true;
#endif
                    }
                }
            }
        }
    }
    SDL_SeekIO(src, start, SDL_IO_SEEK_SET);
    ফেরত is_JPG;
}

SDL_Surface *SDL_LoadJPG_IO(SDL_IOStream *src, bool closeio)
{
    SDL_Surface *surface = ফাঁকা;

    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        যাও done;
    }

    যদি (!SDL_IsJPG(src)) {
        SDL_SetError("File is not a JPEG file");
        যাও done;
    }

#ifdef SDL_HAVE_STB
    surface = SDL_LoadSTB_IO(src);
#অন্যথা
    SDL_SetError("SDL not built with STB image support");
#endif // SDL_HAVE_STB

done:
    যদি (src && closeio) {
        SDL_CloseIO(src);
    }
    ফেরত surface;
}

SDL_Surface *SDL_LoadJPG(ধ্রুবক অক্ষর *file)
{
    SDL_IOStream *stream = SDL_IOFromFile(file, "rb");
    যদি (!stream) {
        ফেরত ফাঁকা;
    }

    ফেরত SDL_LoadJPG_IO(stream, true);
}

bool SDL_IsPNG(SDL_IOStream *src)
{
    Sint64 start;
    Uint8 magic[4];
    bool is_PNG;

    is_PNG = false;
    start = SDL_TellIO(src);
    যদি (start >= 0) {
        যদি (SDL_ReadIO(src, magic, আকার(magic)) == আকার(magic)) {
            যদি (magic[0] == 0x89 &&
                magic[1] == 'P' &&
                magic[2] == 'N' &&
                magic[3] == 'G') {
                is_PNG = true;
            }
        }
        SDL_SeekIO(src, start, SDL_IO_SEEK_SET);
    }

    ফেরত is_PNG;
}

SDL_Surface *SDL_LoadPNG_IO(SDL_IOStream *src, bool closeio)
{
    SDL_Surface *surface = ফাঁকা;

    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        যাও done;
    }

    যদি (!SDL_IsPNG(src)) {
        SDL_SetError("File is not a PNG file");
        যাও done;
    }

#ifdef SDL_HAVE_STB
    surface = SDL_LoadSTB_IO(src);
#অন্যথা
    SDL_SetError("SDL not built with STB image support");
#endif // SDL_HAVE_STB

done:
    যদি (src && closeio) {
        SDL_CloseIO(src);
    }
    ফেরত surface;
}

SDL_Surface *SDL_LoadPNG(ধ্রুবক অক্ষর *file)
{
    SDL_IOStream *stream = SDL_IOFromFile(file, "rb");
    যদি (!stream) {
        ফেরত ফাঁকা;
    }

    ফেরত SDL_LoadPNG_IO(stream, true);
}

bool SDL_SavePNG_IO(SDL_Surface *surface, SDL_IOStream *dst, bool closeio)
{
    bool retval = false;
    Uint8 *plte = ফাঁকা;
    Uint8 *trns = ফাঁকা;
    bool free_surface = false;

    // Make sure we have something to save
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        যাও done;
    }
    CHECK_PARAM(!dst) {
        SDL_InvalidParamError("dst");
        যাও done;
    }

#ifdef SDL_HAVE_STB
    পূর্ণসংখ্যা plte_আকার = 0;
    পূর্ণসংখ্যা trns_আকার = 0;

    যদি (SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        যদি (!surface->palette) {
            SDL_SetError("Indexed surfaces must have a palette");
            যাও done;
        }

        যদি (surface->format != SDL_PIXELFORMAT_INDEX8) {
            surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_INDEX8);
            যদি (!surface) {
                যাও done;
            }
            free_surface = true;
        }

        plte_আকার = surface->palette->ncolors * 3;
        trns_আকার = surface->palette->ncolors;
        plte = (Uint8 *)SDL_malloc(plte_আকার);
        trns = (Uint8 *)SDL_malloc(trns_আকার);
        যদি (!plte || !trns) {
            যাও done;
        }
        SDL_Color *colors = surface->palette->colors;
        জন্য (পূর্ণসংখ্যা i = 0; i < surface->palette->ncolors; ++i) {
            plte[i * 3 + 0] = colors[i].r;
            plte[i * 3 + 1] = colors[i].g;
            plte[i * 3 + 2] = colors[i].b;
            trns[i] = colors[i].a;
        }
    } অন্যথা {
        যদি (surface->format != SDL_PIXELFORMAT_RGBA32) {
            surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);
            যদি (!surface) {
                যাও done;
            }
            free_surface = true;
        }
    }

    size_t আকার_2 = 0;
    শূন্য *png = tdefl_write_image_to_png_file_in_memory_ex(surface->pixels, surface->w, surface->h, SDL_BYTESPERPIXEL(surface->format), surface->pitch, &আকার_2, 6, MZ_FALSE, plte, plte_আকার, trns, trns_আকার);
    যদি (png) {
        যদি (SDL_WriteIO(dst, png, আকার_2)) {
            retval = true;
        }
        mz_free(png); /* calls SDL_free() */
    } অন্যথা {
        SDL_SetError("Failed to convert and save image");
    }

#অন্যথা
    SDL_SetError("SDL not built with STB image support");
#endif

done:
    যদি (free_surface) {
        SDL_DestroySurface(surface);
    }
    SDL_free(plte);
    SDL_free(trns);

    যদি (dst && closeio) {
        retval &= SDL_CloseIO(dst);
    }
    ফেরত retval;
}

bool SDL_SavePNG(SDL_Surface *surface, ধ্রুবক অক্ষর *file)
{
#ifdef SDL_HAVE_STB
    // Make sure we have something to save
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ফেরত SDL_InvalidParamError("surface");
    }

    যদি (SDL_ISPIXELFORMAT_INDEXED(surface->format) && !surface->palette) {
        ফেরত SDL_SetError("Indexed surfaces must have a palette");
    }
    SDL_IOStream *stream = SDL_IOFromFile(file, "wb");
    যদি (!stream) {
        ফেরত false;
    }

    ফেরত SDL_SavePNG_IO(surface, stream, true);
#অন্যথা
    ফেরত SDL_SetError("SDL not built with STB image support");
#endif
}
