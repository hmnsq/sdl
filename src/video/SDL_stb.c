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
#അന്തര്ഭാവ "SDL_internal.h"

#അന്തര്ഭാവ "SDL_stb_c.h"
#അന്തര്ഭാവ "SDL_surface_c.h"
#അന്തര്ഭാവ "SDL_yuv_c.h"

/* STB image conversion */
#ifndef SDL_DISABLE_STB
#define SDL_HAVE_STB
#endif

#ifdef SDL_HAVE_STB
////////////////////////////////////////////////////////////////////////////
#define malloc SDL_malloc
#define realloc SDL_realloc
#define സ്വതന്ത്രം SDL_free
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
#എങ്കിൽ defined(SDL_NEON_INTRINSICS)
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
#അന്തര്ഭാവ "stb_image.h"

////////////////////////////////////////////////////////////////////////////
#define MZ_ASSERT(x) SDL_assert(x)
//#undef memcpy
//#define memcpy SDL_memcpy
//#undef memset
//#define memset SDL_memset
#എങ്കിൽ SDL_BYTEORDER == SDL_LIL_ENDIAN
#define MINIZ_LITTLE_ENDIAN 1
#അല്ലെങ്കിൽ
#define MINIZ_LITTLE_ENDIAN 0
#endif
#define MINIZ_USE_UNALIGNED_LOADS_AND_STORES 0
#define MINIZ_SDL_NOUNUSED
#അന്തര്ഭാവ "miniz.h"

#undef memset
#endif // SDL_HAVE_STB

#ifdef SDL_HAVE_STB
സ്ഥിതം bool SDL_ConvertPixels_MJPG_to_NV12(പൂർണ്ണസംഖ്യ width, പൂർണ്ണസംഖ്യ height, സ്ഥിരം ശൂന്യം *src, പൂർണ്ണസംഖ്യ src_pitch, ശൂന്യം *dst, പൂർണ്ണസംഖ്യ dst_pitch)
{
    പൂർണ്ണസംഖ്യ w = 0, h = 0, format = 0;
    stbi__context s;
    stbi__start_mem(&s, src, src_pitch);

    stbi__result_info ri;
    SDL_zero(ri);
    ri.bits_per_channel = 8;
    ri.channel_order = STBI_ORDER_RGB;
    ri.അക്കം_channels = 0;

    stbi__nv12 nv12;
    nv12.w = width;
    nv12.h = height;
    nv12.pitch = dst_pitch;
    nv12.y = (stbi_uc *)dst;
    nv12.uv = nv12.y + (nv12.h * nv12.pitch);

    ശൂന്യം *pixels = stbi__jpeg_load(&s, &w, &h, &format, 4, &nv12, &ri);
    എങ്കിൽ (!pixels) {
        തിരികെ false;
    }
    തിരികെ true;
}
#endif // SDL_HAVE_STB

bool SDL_ConvertPixels_STB(പൂർണ്ണസംഖ്യ width, പൂർണ്ണസംഖ്യ height,
                           SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, സ്ഥിരം ശൂന്യം *src, പൂർണ്ണസംഖ്യ src_pitch,
                           SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, ശൂന്യം *dst, പൂർണ്ണസംഖ്യ dst_pitch)
{
#ifdef SDL_HAVE_STB
    എങ്കിൽ (src_format == SDL_PIXELFORMAT_MJPG) {
        എങ്കിൽ (dst_format == SDL_PIXELFORMAT_NV12) {
            തിരികെ SDL_ConvertPixels_MJPG_to_NV12(width, height, src, src_pitch, dst, dst_pitch);
        } അല്ലെങ്കിൽ എങ്കിൽ (
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
            എങ്കിൽ (!SDL_CalculateYUVSize(dst_format, width, height, &temp_size, &temp_pitch)) {
                തിരികെ false;
            }
            ശൂന്യം *temp_pixels = SDL_malloc(temp_size);
            എങ്കിൽ (!temp_pixels) {
                തിരികെ false;
            }

            എങ്കിൽ (!SDL_ConvertPixels_MJPG_to_NV12(width, height, src, src_pitch, temp_pixels, (പൂർണ്ണസംഖ്യ)temp_pitch)) {
                SDL_free(temp_pixels);
                തിരികെ false;
            }

            bool result = SDL_ConvertPixelsAndColorspace(width, height, SDL_PIXELFORMAT_NV12, src_colorspace, 0 /*props*/, temp_pixels, (പൂർണ്ണസംഖ്യ)temp_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
            SDL_free(temp_pixels);
            തിരികെ result;
        }
    }

    bool result;
    പൂർണ്ണസംഖ്യ w = 0, h = 0, format = 0;
    പൂർണ്ണസംഖ്യ len = (src_format == SDL_PIXELFORMAT_MJPG) ? src_pitch : (height * src_pitch);
    ശൂന്യം *pixels = stbi_load_from_memory(src, len, &w, &h, &format, 4);
    എങ്കിൽ (!pixels) {
        തിരികെ false;
    }

    എങ്കിൽ (w == width && h == height) {
        result = SDL_ConvertPixelsAndColorspace(w, h, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, pixels, width * 4, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } അല്ലെങ്കിൽ {
        result = SDL_SetError("Expected image size %dx%d, actual size %dx%d", width, height, w, h);
    }
    stbi_image_free(pixels);

    തിരികെ result;
#അല്ലെങ്കിൽ
    തിരികെ SDL_SetError("SDL not built with STB image support");
#endif
}

#ifdef SDL_HAVE_STB
സ്ഥിതം പൂർണ്ണസംഖ്യ IMG_LoadSTB_IO_read(ശൂന്യം *user, അക്ഷരം *data, പൂർണ്ണസംഖ്യ size)
{
    size_t amount = SDL_ReadIO((SDL_IOStream*)user, data, size);
    തിരികെ (പൂർണ്ണസംഖ്യ)amount;
}

സ്ഥിതം ശൂന്യം IMG_LoadSTB_IO_skip(ശൂന്യം *user, പൂർണ്ണസംഖ്യ n)
{
    SDL_SeekIO((SDL_IOStream*)user, n, SDL_IO_SEEK_CUR);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ IMG_LoadSTB_IO_eof(ശൂന്യം *user)
{
    SDL_IOStream *src = (SDL_IOStream*)user;
    തിരികെ SDL_GetIOStatus(src) == SDL_IO_STATUS_EOF;
}

സ്ഥിതം SDL_Surface *SDL_LoadSTB_IO(SDL_IOStream *src)
{
    Sint64 start;
    Uint8 magic[26];
    പൂർണ്ണസംഖ്യ w, h, format;
    stbi_uc *pixels;
    stbi_io_callbacks rw_callbacks;
    SDL_Surface *surface = ശൂന്യ;
    bool use_palette = false;
    unsigned പൂർണ്ണസംഖ്യ palette_colors[256];

    // src has already been validated
    start = SDL_TellIO(src);

    എങ്കിൽ (SDL_ReadIO(src, magic, വലുപ്പം(magic)) == വലുപ്പം(magic)) {
        സ്ഥിരം Uint8 PNG_COLOR_INDEXED = 3;
        എങ്കിൽ (magic[0] == 0x89 &&
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
    rw_callbacks.പഠ = IMG_LoadSTB_IO_read;
    rw_callbacks.skip = IMG_LoadSTB_IO_skip;
    rw_callbacks.eof = IMG_LoadSTB_IO_eof;
    w = h = format = 0; /* silence warning */
    എങ്കിൽ (use_palette) {
        /* Unused palette entries will be opaque white */
        SDL_memset(palette_colors, 0xff, വലുപ്പം(palette_colors));

        pixels = stbi_load_from_callbacks_with_palette(
            &rw_callbacks,
            src,
            &w,
            &h,
            palette_colors,
            SDL_arraysize(palette_colors)
        );
    } അല്ലെങ്കിൽ {
        pixels = stbi_load_from_callbacks(
            &rw_callbacks,
            src,
            &w,
            &h,
            &format,
            STBI_default
        );
    }
    എങ്കിൽ (!pixels) {
        SDL_SeekIO(src, start, SDL_IO_SEEK_SET);
        തിരികെ ശൂന്യ;
    }

    എങ്കിൽ (use_palette) {
        surface = SDL_CreateSurfaceFrom(
            w,
            h,
            SDL_PIXELFORMAT_INDEX8,
            pixels,
            w
        );
        എങ്കിൽ (surface) {
            bool has_colorkey = false;
            പൂർണ്ണസംഖ്യ colorkey_index = -1;
            bool has_alpha = false;
            SDL_Palette *palette = SDL_CreateSurfacePalette(surface);
            എങ്കിൽ (palette) {
                പൂർണ്ണസംഖ്യ i;
                Uint8 *palette_bytes = (Uint8 *)palette_colors;

                വേണ്ടി (i = 0; i < palette->ncolors; i++) {
                    palette->colors[i].r = *palette_bytes++;
                    palette->colors[i].g = *palette_bytes++;
                    palette->colors[i].b = *palette_bytes++;
                    palette->colors[i].a = *palette_bytes++;
                    എങ്കിൽ (palette->colors[i].a != SDL_ALPHA_OPAQUE) {
                        എങ്കിൽ (palette->colors[i].a == SDL_ALPHA_TRANSPARENT && !has_colorkey) {
                            has_colorkey = true;
                            colorkey_index = i;
                        } അല്ലെങ്കിൽ {
                            /* Partial opacity or multiple colorkeys */
                            has_alpha = true;
                        }
                    }
                }
            }
            എങ്കിൽ (has_alpha) {
                SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
            } അല്ലെങ്കിൽ എങ്കിൽ (has_colorkey) {
                SDL_Set_Surface_Color_താക്കോൽ(surface, true, colorkey_index);
            }

            /* FIXME: This sucks. It'd be better to allocate the surface first, then
             * write directly to the pixel buffer:
             * https://github.com/nothings/stb/issues/58
             * -flibit
             */
            surface->flags &= ~SDL_SURFACE_PREALLOCATED;
        }

    } അല്ലെങ്കിൽ എങ്കിൽ (format == STBI_grey || format == STBI_rgb || format == STBI_rgb_alpha) {
        surface = SDL_CreateSurfaceFrom(
            w,
            h,
            (format == STBI_rgb_alpha) ? SDL_PIXELFORMAT_RGBA32 :
            (format == STBI_rgb) ? SDL_PIXELFORMAT_RGB24 :
            SDL_PIXELFORMAT_INDEX8,
            pixels,
            w * format
        );
        എങ്കിൽ (surface) {
            /* Set a grayscale palette for gray images */
            എങ്കിൽ (surface->format == SDL_PIXELFORMAT_INDEX8) {
                SDL_Palette *palette = SDL_CreateSurfacePalette(surface);
                എങ്കിൽ (palette) {
                    പൂർണ്ണസംഖ്യ i;

                    വേണ്ടി (i = 0; i < palette->ncolors; i++) {
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

    } അല്ലെങ്കിൽ എങ്കിൽ (format == STBI_grey_alpha) {
        surface = SDL_CreateSurfaceUninitialized(w, h, SDL_PIXELFORMAT_RGBA32);
        എങ്കിൽ (surface) {
            Uint8 *src_ptr = pixels;
            Uint8 *dst = (Uint8 *)surface->pixels;
            പൂർണ്ണസംഖ്യ skip = surface->pitch - (surface->w * 4);
            പൂർണ്ണസംഖ്യ row, col;

            വേണ്ടി (row = 0; row < h; ++row) {
                വേണ്ടി (col = 0; col < w; ++col) {
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
    } അല്ലെങ്കിൽ {
        SDL_SetError("Unknown image format: %d", format);
    }

    എങ്കിൽ (!surface) {
        /* The error message should already be set */
        stbi_image_free(pixels); /* calls SDL_free() */
        SDL_SeekIO(src, start, SDL_IO_SEEK_SET);
    }
    തിരികെ surface;
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

    എങ്കിൽ (!src) {
        തിരികെ false;
    }

    start = SDL_TellIO(src);
    is_JPG = false;
    in_scan = false;
    എങ്കിൽ (SDL_ReadIO(src, magic, 2) == 2) {
        എങ്കിൽ ( (magic[0] == 0xFF) && (magic[1] == 0xD8) ) {
            is_JPG = true;
            ആകുമ്പോൾ (is_JPG) {
                എങ്കിൽ (SDL_ReadIO(src, magic, 2) != 2) {
                    is_JPG = false;
                } അല്ലെങ്കിൽ എങ്കിൽ ( (magic[0] != 0xFF) && !in_scan ) {
                    is_JPG = false;
                } അല്ലെങ്കിൽ എങ്കിൽ ( (magic[0] != 0xFF) || (magic[1] == 0xFF) ) {
                    /* Extra padding in JPEG (legal) */
                    /* or this is data and we are scanning */
                    SDL_SeekIO(src, -1, SDL_IO_SEEK_CUR);
                } അല്ലെങ്കിൽ എങ്കിൽ (magic[1] == 0xD9) {
                    /* Got to end of good JPEG */
                    നിർത്തുക;
                } അല്ലെങ്കിൽ എങ്കിൽ ( in_scan && (magic[1] == 0x00) ) {
                    /* This is an encoded 0xFF within the data */
                } അല്ലെങ്കിൽ എങ്കിൽ ( (magic[1] >= 0xD0) && (magic[1] < 0xD9) ) {
                    /* These have nothing else */
                } അല്ലെങ്കിൽ എങ്കിൽ (SDL_ReadIO(src, magic+2, 2) != 2) {
                    is_JPG = false;
                } അല്ലെങ്കിൽ {
                    /* Yes, it's big-endian */
                    Sint64 innerStart;
                    Uint32 size;
                    Sint64 end;
                    innerStart = SDL_TellIO(src);
                    size = (magic[2] << 8) + magic[3];
                    end = SDL_SeekIO(src, size-2, SDL_IO_SEEK_CUR);
                    എങ്കിൽ ( end != innerStart + size - 2 ) {
                        is_JPG = false;
                    }
                    എങ്കിൽ ( magic[1] == 0xDA ) {
                        /* Now comes the actual JPEG meat */
#ifdef  FAST_IS_JPEG
                        /* Ok, I'm convinced.  It is a JPEG. */
                        നിർത്തുക;
#അല്ലെങ്കിൽ
                        /* I'm not convinced.  Prove it! */
                        in_scan = true;
#endif
                    }
                }
            }
        }
    }
    SDL_SeekIO(src, start, SDL_IO_SEEK_SET);
    തിരികെ is_JPG;
}

SDL_Surface *SDL_LoadJPG_IO(SDL_IOStream *src, bool closeio)
{
    SDL_Surface *surface = ശൂന്യ;

    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        പോകുക done;
    }

    എങ്കിൽ (!SDL_IsJPG(src)) {
        SDL_SetError("File is not a JPEG file");
        പോകുക done;
    }

#ifdef SDL_HAVE_STB
    surface = SDL_LoadSTB_IO(src);
#അല്ലെങ്കിൽ
    SDL_SetError("SDL not built with STB image support");
#endif // SDL_HAVE_STB

done:
    എങ്കിൽ (src && closeio) {
        SDL_CloseIO(src);
    }
    തിരികെ surface;
}

SDL_Surface *SDL_LoadJPG(സ്ഥിരം അക്ഷരം *file)
{
    SDL_IOStream *stream = SDL_IOFromFile(file, "rb");
    എങ്കിൽ (!stream) {
        തിരികെ ശൂന്യ;
    }

    തിരികെ SDL_LoadJPG_IO(stream, true);
}

bool SDL_IsPNG(SDL_IOStream *src)
{
    Sint64 start;
    Uint8 magic[4];
    bool is_PNG;

    is_PNG = false;
    start = SDL_TellIO(src);
    എങ്കിൽ (start >= 0) {
        എങ്കിൽ (SDL_ReadIO(src, magic, വലുപ്പം(magic)) == വലുപ്പം(magic)) {
            എങ്കിൽ (magic[0] == 0x89 &&
                magic[1] == 'P' &&
                magic[2] == 'N' &&
                magic[3] == 'G') {
                is_PNG = true;
            }
        }
        SDL_SeekIO(src, start, SDL_IO_SEEK_SET);
    }

    തിരികെ is_PNG;
}

SDL_Surface *SDL_LoadPNG_IO(SDL_IOStream *src, bool closeio)
{
    SDL_Surface *surface = ശൂന്യ;

    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        പോകുക done;
    }

    എങ്കിൽ (!SDL_IsPNG(src)) {
        SDL_SetError("File is not a PNG file");
        പോകുക done;
    }

#ifdef SDL_HAVE_STB
    surface = SDL_LoadSTB_IO(src);
#അല്ലെങ്കിൽ
    SDL_SetError("SDL not built with STB image support");
#endif // SDL_HAVE_STB

done:
    എങ്കിൽ (src && closeio) {
        SDL_CloseIO(src);
    }
    തിരികെ surface;
}

SDL_Surface *SDL_LoadPNG(സ്ഥിരം അക്ഷരം *file)
{
    SDL_IOStream *stream = SDL_IOFromFile(file, "rb");
    എങ്കിൽ (!stream) {
        തിരികെ ശൂന്യ;
    }

    തിരികെ SDL_LoadPNG_IO(stream, true);
}

bool SDL_SavePNG_IO(SDL_Surface *surface, SDL_IOStream *dst, bool closeio)
{
    bool retval = false;
    Uint8 *plte = ശൂന്യ;
    Uint8 *trns = ശൂന്യ;
    bool free_surface = false;

    // Make sure we have something to save
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        പോകുക done;
    }
    CHECK_PARAM(!dst) {
        SDL_InvalidParamError("dst");
        പോകുക done;
    }

#ifdef SDL_HAVE_STB
    പൂർണ്ണസംഖ്യ plte_size = 0;
    പൂർണ്ണസംഖ്യ trns_size = 0;

    എങ്കിൽ (SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        എങ്കിൽ (!surface->palette) {
            SDL_SetError("Indexed surfaces must have a palette");
            പോകുക done;
        }

        എങ്കിൽ (surface->format != SDL_PIXELFORMAT_INDEX8) {
            surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_INDEX8);
            എങ്കിൽ (!surface) {
                പോകുക done;
            }
            free_surface = true;
        }

        plte_size = surface->palette->ncolors * 3;
        trns_size = surface->palette->ncolors;
        plte = (Uint8 *)SDL_malloc(plte_size);
        trns = (Uint8 *)SDL_malloc(trns_size);
        എങ്കിൽ (!plte || !trns) {
            പോകുക done;
        }
        SDL_Color *colors = surface->palette->colors;
        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < surface->palette->ncolors; ++i) {
            plte[i * 3 + 0] = colors[i].r;
            plte[i * 3 + 1] = colors[i].g;
            plte[i * 3 + 2] = colors[i].b;
            trns[i] = colors[i].a;
        }
    } അല്ലെങ്കിൽ {
        എങ്കിൽ (surface->format != SDL_PIXELFORMAT_RGBA32) {
            surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);
            എങ്കിൽ (!surface) {
                പോകുക done;
            }
            free_surface = true;
        }
    }

    size_t size = 0;
    ശൂന്യം *png = tdefl_write_image_to_png_file_in_memory_ex(surface->pixels, surface->w, surface->h, SDL_BYTESPERPIXEL(surface->format), surface->pitch, &size, 6, MZ_FALSE, plte, plte_size, trns, trns_size);
    എങ്കിൽ (png) {
        എങ്കിൽ (SDL_WriteIO(dst, png, size)) {
            retval = true;
        }
        mz_free(png); /* calls SDL_free() */
    } അല്ലെങ്കിൽ {
        SDL_SetError("Failed to convert and save image");
    }

#അല്ലെങ്കിൽ
    SDL_SetError("SDL not built with STB image support");
#endif

done:
    എങ്കിൽ (free_surface) {
        SDL_DestroySurface(surface);
    }
    SDL_free(plte);
    SDL_free(trns);

    എങ്കിൽ (dst && closeio) {
        retval &= SDL_CloseIO(dst);
    }
    തിരികെ retval;
}

bool SDL_SavePNG(SDL_Surface *surface, സ്ഥിരം അക്ഷരം *file)
{
#ifdef SDL_HAVE_STB
    // Make sure we have something to save
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        തിരികെ SDL_InvalidParamError("surface");
    }

    എങ്കിൽ (SDL_ISPIXELFORMAT_INDEXED(surface->format) && !surface->palette) {
        തിരികെ SDL_SetError("Indexed surfaces must have a palette");
    }
    SDL_IOStream *stream = SDL_IOFromFile(file, "wb");
    എങ്കിൽ (!stream) {
        തിരികെ false;
    }

    തിരികെ SDL_SavePNG_IO(surface, stream, true);
#അല്ലെങ്കിൽ
    തിരികെ SDL_SetError("SDL not built with STB image support");
#endif
}
