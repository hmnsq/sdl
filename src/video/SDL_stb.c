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

#अन्तर्भाव "SDL_stb_c.h"
#अन्तर्भाव "SDL_surface_c.h"
#अन्तर्भाव "SDL_yuv_c.h"

/* STB image conversion */
#ifndef SDL_DISABLE_STB
#define SDL_HAVE_STB
#endif

#ifdef SDL_HAVE_STB
////////////////////////////////////////////////////////////////////////////
#define दो_स्मृति SDL_malloc
#define पुनः_स्मृति SDL_realloc
#define मुक्त SDL_free
#undef स_नकल
#define स_नकल SDL_memcpy
#undef स_रखो
#define स_रखो SDL_memset
#undef म_भेद
#define म_भेद SDL_strcmp
#undef म_भेदन
#define म_भेदन SDL_strncmp
#define म_से_दीर्घ SDL_strtol

#define असल SDL_abs
#define घात SDL_pow
#define ldexp SDL_scalbn

#define STB_IMAGE_STATIC
#define STBI_NO_THREAD_LOCALS
#define STBI_FAILURE_USERMSG
#यदि defined(SDL_NEON_INTRINSICS)
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
#अन्तर्भाव "stb_image.h"

////////////////////////////////////////////////////////////////////////////
#define MZ_ASSERT(x) SDL_assert(x)
//#undef memcpy
//#define memcpy SDL_memcpy
//#undef memset
//#define memset SDL_memset
#यदि SDL_BYTEORDER == SDL_LIL_ENDIAN
#define MINIZ_LITTLE_ENDIAN 1
#अन्यथा
#define MINIZ_LITTLE_ENDIAN 0
#endif
#define MINIZ_USE_UNALIGNED_LOADS_AND_STORES 0
#define MINIZ_SDL_NOUNUSED
#अन्तर्भाव "miniz.h"

#undef स_रखो
#endif // SDL_HAVE_STB

#ifdef SDL_HAVE_STB
स्थिर bool SDL_ConvertPixels_MJPG_to_NV12(पूर्णाङ्क width, पूर्णाङ्क height, अचर शून्य *src, पूर्णाङ्क src_pitch, शून्य *dst, पूर्णाङ्क dst_pitch)
{
    पूर्णाङ्क w = 0, h = 0, format = 0;
    stbi__context s;
    stbi__start_mem(&s, src, src_pitch);

    stbi__result_info ri;
    SDL_zero(ri);
    ri.bits_per_channel = 8;
    ri.channel_order = STBI_ORDER_RGB;
    ri.अङ्क_channels = 0;

    stbi__nv12 nv12;
    nv12.w = width;
    nv12.h = height;
    nv12.pitch = dst_pitch;
    nv12.y = (stbi_uc *)dst;
    nv12.uv = nv12.y + (nv12.h * nv12.pitch);

    शून्य *pixels = stbi__jpeg_load(&s, &w, &h, &format, 4, &nv12, &ri);
    यदि (!pixels) {
        फर्काऊ false;
    }
    फर्काऊ true;
}
#endif // SDL_HAVE_STB

bool SDL_ConvertPixels_STB(पूर्णाङ्क width, पूर्णाङ्क height,
                           SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, अचर शून्य *src, पूर्णाङ्क src_pitch,
                           SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, शून्य *dst, पूर्णाङ्क dst_pitch)
{
#ifdef SDL_HAVE_STB
    यदि (src_format == SDL_PIXELFORMAT_MJPG) {
        यदि (dst_format == SDL_PIXELFORMAT_NV12) {
            फर्काऊ SDL_ConvertPixels_MJPG_to_NV12(width, height, src, src_pitch, dst, dst_pitch);
        } अन्यथा यदि (
            dst_format == SDL_PIXELFORMAT_YV12 ||
            dst_format == SDL_PIXELFORMAT_IYUV ||
            dst_format == SDL_PIXELFORMAT_YUY2 ||
            dst_format == SDL_PIXELFORMAT_UYVY ||
            dst_format == SDL_PIXELFORMAT_YVYU ||
            dst_format == SDL_PIXELFORMAT_NV21 ||
            dst_format == SDL_PIXELFORMAT_P010
        ) {
            माप_प्रकार temp_size = 0;
            माप_प्रकार temp_pitch = 0;
            यदि (!SDL_CalculateYUVSize(dst_format, width, height, &temp_size, &temp_pitch)) {
                फर्काऊ false;
            }
            शून्य *temp_pixels = SDL_malloc(temp_size);
            यदि (!temp_pixels) {
                फर्काऊ false;
            }

            यदि (!SDL_ConvertPixels_MJPG_to_NV12(width, height, src, src_pitch, temp_pixels, (पूर्णाङ्क)temp_pitch)) {
                SDL_free(temp_pixels);
                फर्काऊ false;
            }

            bool result = SDL_ConvertPixelsAndColorspace(width, height, SDL_PIXELFORMAT_NV12, src_colorspace, 0 /*props*/, temp_pixels, (पूर्णाङ्क)temp_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
            SDL_free(temp_pixels);
            फर्काऊ result;
        }
    }

    bool result;
    पूर्णाङ्क w = 0, h = 0, format = 0;
    पूर्णाङ्क len = (src_format == SDL_PIXELFORMAT_MJPG) ? src_pitch : (height * src_pitch);
    शून्य *pixels = stbi_load_from_memory(src, len, &w, &h, &format, 4);
    यदि (!pixels) {
        फर्काऊ false;
    }

    यदि (w == width && h == height) {
        result = SDL_ConvertPixelsAndColorspace(w, h, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, pixels, width * 4, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } अन्यथा {
        result = SDL_SetError("Expected image size %dx%d, actual size %dx%d", width, height, w, h);
    }
    stbi_image_free(pixels);

    फर्काऊ result;
#अन्यथा
    फर्काऊ SDL_SetError("SDL not built with STB image support");
#endif
}

#ifdef SDL_HAVE_STB
स्थिर पूर्णाङ्क IMG_LoadSTB_IO_read(शून्य *user, वर्ण *data, पूर्णाङ्क size)
{
    माप_प्रकार amount = SDL_ReadIO((SDL_IOStream*)user, data, size);
    फर्काऊ (पूर्णाङ्क)amount;
}

स्थिर शून्य IMG_LoadSTB_IO_skip(शून्य *user, पूर्णाङ्क n)
{
    SDL_SeekIO((SDL_IOStream*)user, n, SDL_IO_SEEK_CUR);
}

स्थिर पूर्णाङ्क IMG_LoadSTB_IO_eof(शून्य *user)
{
    SDL_IOStream *src = (SDL_IOStream*)user;
    फर्काऊ SDL_GetIOStatus(src) == SDL_IO_STATUS_EOF;
}

स्थिर SDL_Surface *SDL_LoadSTB_IO(SDL_IOStream *src)
{
    Sint64 start;
    Uint8 magic[26];
    पूर्णाङ्क w, h, format;
    stbi_uc *pixels;
    stbi_io_callbacks rw_callbacks;
    SDL_Surface *surface = रिक्त;
    bool use_palette = false;
    अचिन्हित पूर्णाङ्क palette_colors[256];

    // src has already been validated
    start = SDL_TellIO(src);

    यदि (SDL_ReadIO(src, magic, परिमाण(magic)) == परिमाण(magic)) {
        अचर Uint8 PNG_COLOR_INDEXED = 3;
        यदि (magic[0] == 0x89 &&
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
    rw_callbacks.पठ = IMG_LoadSTB_IO_read;
    rw_callbacks.skip = IMG_LoadSTB_IO_skip;
    rw_callbacks.eof = IMG_LoadSTB_IO_eof;
    w = h = format = 0; /* silence warning */
    यदि (use_palette) {
        /* Unused palette entries will be opaque white */
        SDL_memset(palette_colors, 0xff, परिमाण(palette_colors));

        pixels = stbi_load_from_callbacks_with_palette(
            &rw_callbacks,
            src,
            &w,
            &h,
            palette_colors,
            SDL_arraysize(palette_colors)
        );
    } अन्यथा {
        pixels = stbi_load_from_callbacks(
            &rw_callbacks,
            src,
            &w,
            &h,
            &format,
            STBI_default
        );
    }
    यदि (!pixels) {
        SDL_SeekIO(src, start, SDL_IO_SEEK_SET);
        फर्काऊ रिक्त;
    }

    यदि (use_palette) {
        surface = SDL_CreateSurfaceFrom(
            w,
            h,
            SDL_PIXELFORMAT_INDEX8,
            pixels,
            w
        );
        यदि (surface) {
            bool has_colorkey = false;
            पूर्णाङ्क colorkey_index = -1;
            bool has_alpha = false;
            SDL_Palette *palette = SDL_CreateSurfacePalette(surface);
            यदि (palette) {
                पूर्णाङ्क i;
                Uint8 *palette_bytes = (Uint8 *)palette_colors;

                लागि (i = 0; i < palette->ncolors; i++) {
                    palette->colors[i].r = *palette_bytes++;
                    palette->colors[i].g = *palette_bytes++;
                    palette->colors[i].b = *palette_bytes++;
                    palette->colors[i].a = *palette_bytes++;
                    यदि (palette->colors[i].a != SDL_ALPHA_OPAQUE) {
                        यदि (palette->colors[i].a == SDL_ALPHA_TRANSPARENT && !has_colorkey) {
                            has_colorkey = true;
                            colorkey_index = i;
                        } अन्यथा {
                            /* Partial opacity or multiple colorkeys */
                            has_alpha = true;
                        }
                    }
                }
            }
            यदि (has_alpha) {
                SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
            } अन्यथा यदि (has_colorkey) {
                SDL_Set_Surface_Color_साँचो(surface, true, colorkey_index);
            }

            /* FIXME: This sucks. It'd be better to allocate the surface first, then
             * write directly to the pixel buffer:
             * https://github.com/nothings/stb/issues/58
             * -flibit
             */
            surface->flags &= ~SDL_SURFACE_PREALLOCATED;
        }

    } अन्यथा यदि (format == STBI_grey || format == STBI_rgb || format == STBI_rgb_alpha) {
        surface = SDL_CreateSurfaceFrom(
            w,
            h,
            (format == STBI_rgb_alpha) ? SDL_PIXELFORMAT_RGBA32 :
            (format == STBI_rgb) ? SDL_PIXELFORMAT_RGB24 :
            SDL_PIXELFORMAT_INDEX8,
            pixels,
            w * format
        );
        यदि (surface) {
            /* Set a grayscale palette for gray images */
            यदि (surface->format == SDL_PIXELFORMAT_INDEX8) {
                SDL_Palette *palette = SDL_CreateSurfacePalette(surface);
                यदि (palette) {
                    पूर्णाङ्क i;

                    लागि (i = 0; i < palette->ncolors; i++) {
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

    } अन्यथा यदि (format == STBI_grey_alpha) {
        surface = SDL_CreateSurfaceUninitialized(w, h, SDL_PIXELFORMAT_RGBA32);
        यदि (surface) {
            Uint8 *src_ptr = pixels;
            Uint8 *dst = (Uint8 *)surface->pixels;
            पूर्णाङ्क skip = surface->pitch - (surface->w * 4);
            पूर्णाङ्क row, col;

            लागि (row = 0; row < h; ++row) {
                लागि (col = 0; col < w; ++col) {
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
    } अन्यथा {
        SDL_SetError("Unknown image format: %d", format);
    }

    यदि (!surface) {
        /* The error message should already be set */
        stbi_image_free(pixels); /* calls SDL_free() */
        SDL_SeekIO(src, start, SDL_IO_SEEK_SET);
    }
    फर्काऊ surface;
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

    यदि (!src) {
        फर्काऊ false;
    }

    start = SDL_TellIO(src);
    is_JPG = false;
    in_scan = false;
    यदि (SDL_ReadIO(src, magic, 2) == 2) {
        यदि ( (magic[0] == 0xFF) && (magic[1] == 0xD8) ) {
            is_JPG = true;
            जबसम्म (is_JPG) {
                यदि (SDL_ReadIO(src, magic, 2) != 2) {
                    is_JPG = false;
                } अन्यथा यदि ( (magic[0] != 0xFF) && !in_scan ) {
                    is_JPG = false;
                } अन्यथा यदि ( (magic[0] != 0xFF) || (magic[1] == 0xFF) ) {
                    /* Extra padding in JPEG (legal) */
                    /* or this is data and we are scanning */
                    SDL_SeekIO(src, -1, SDL_IO_SEEK_CUR);
                } अन्यथा यदि (magic[1] == 0xD9) {
                    /* Got to end of good JPEG */
                    रोक;
                } अन्यथा यदि ( in_scan && (magic[1] == 0x00) ) {
                    /* This is an encoded 0xFF within the data */
                } अन्यथा यदि ( (magic[1] >= 0xD0) && (magic[1] < 0xD9) ) {
                    /* These have nothing else */
                } अन्यथा यदि (SDL_ReadIO(src, magic+2, 2) != 2) {
                    is_JPG = false;
                } अन्यथा {
                    /* Yes, it's big-endian */
                    Sint64 innerStart;
                    Uint32 size;
                    Sint64 end;
                    innerStart = SDL_TellIO(src);
                    size = (magic[2] << 8) + magic[3];
                    end = SDL_SeekIO(src, size-2, SDL_IO_SEEK_CUR);
                    यदि ( end != innerStart + size - 2 ) {
                        is_JPG = false;
                    }
                    यदि ( magic[1] == 0xDA ) {
                        /* Now comes the actual JPEG meat */
#ifdef  FAST_IS_JPEG
                        /* Ok, I'm convinced.  It is a JPEG. */
                        रोक;
#अन्यथा
                        /* I'm not convinced.  Prove it! */
                        in_scan = true;
#endif
                    }
                }
            }
        }
    }
    SDL_SeekIO(src, start, SDL_IO_SEEK_SET);
    फर्काऊ is_JPG;
}

SDL_Surface *SDL_LoadJPG_IO(SDL_IOStream *src, bool closeio)
{
    SDL_Surface *surface = रिक्त;

    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        गच्छ done;
    }

    यदि (!SDL_IsJPG(src)) {
        SDL_SetError("File is not a JPEG file");
        गच्छ done;
    }

#ifdef SDL_HAVE_STB
    surface = SDL_LoadSTB_IO(src);
#अन्यथा
    SDL_SetError("SDL not built with STB image support");
#endif // SDL_HAVE_STB

done:
    यदि (src && closeio) {
        SDL_CloseIO(src);
    }
    फर्काऊ surface;
}

SDL_Surface *SDL_LoadJPG(अचर वर्ण *file)
{
    SDL_IOStream *stream = SDL_IOFromFile(file, "rb");
    यदि (!stream) {
        फर्काऊ रिक्त;
    }

    फर्काऊ SDL_LoadJPG_IO(stream, true);
}

bool SDL_IsPNG(SDL_IOStream *src)
{
    Sint64 start;
    Uint8 magic[4];
    bool is_PNG;

    is_PNG = false;
    start = SDL_TellIO(src);
    यदि (start >= 0) {
        यदि (SDL_ReadIO(src, magic, परिमाण(magic)) == परिमाण(magic)) {
            यदि (magic[0] == 0x89 &&
                magic[1] == 'P' &&
                magic[2] == 'N' &&
                magic[3] == 'G') {
                is_PNG = true;
            }
        }
        SDL_SeekIO(src, start, SDL_IO_SEEK_SET);
    }

    फर्काऊ is_PNG;
}

SDL_Surface *SDL_LoadPNG_IO(SDL_IOStream *src, bool closeio)
{
    SDL_Surface *surface = रिक्त;

    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        गच्छ done;
    }

    यदि (!SDL_IsPNG(src)) {
        SDL_SetError("File is not a PNG file");
        गच्छ done;
    }

#ifdef SDL_HAVE_STB
    surface = SDL_LoadSTB_IO(src);
#अन्यथा
    SDL_SetError("SDL not built with STB image support");
#endif // SDL_HAVE_STB

done:
    यदि (src && closeio) {
        SDL_CloseIO(src);
    }
    फर्काऊ surface;
}

SDL_Surface *SDL_LoadPNG(अचर वर्ण *file)
{
    SDL_IOStream *stream = SDL_IOFromFile(file, "rb");
    यदि (!stream) {
        फर्काऊ रिक्त;
    }

    फर्काऊ SDL_LoadPNG_IO(stream, true);
}

bool SDL_SavePNG_IO(SDL_Surface *surface, SDL_IOStream *dst, bool closeio)
{
    bool retval = false;
    Uint8 *plte = रिक्त;
    Uint8 *trns = रिक्त;
    bool free_surface = false;

    // Make sure we have something to save
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        गच्छ done;
    }
    CHECK_PARAM(!dst) {
        SDL_InvalidParamError("dst");
        गच्छ done;
    }

#ifdef SDL_HAVE_STB
    पूर्णाङ्क plte_size = 0;
    पूर्णाङ्क trns_size = 0;

    यदि (SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        यदि (!surface->palette) {
            SDL_SetError("Indexed surfaces must have a palette");
            गच्छ done;
        }

        यदि (surface->format != SDL_PIXELFORMAT_INDEX8) {
            surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_INDEX8);
            यदि (!surface) {
                गच्छ done;
            }
            free_surface = true;
        }

        plte_size = surface->palette->ncolors * 3;
        trns_size = surface->palette->ncolors;
        plte = (Uint8 *)SDL_malloc(plte_size);
        trns = (Uint8 *)SDL_malloc(trns_size);
        यदि (!plte || !trns) {
            गच्छ done;
        }
        SDL_Color *colors = surface->palette->colors;
        लागि (पूर्णाङ्क i = 0; i < surface->palette->ncolors; ++i) {
            plte[i * 3 + 0] = colors[i].r;
            plte[i * 3 + 1] = colors[i].g;
            plte[i * 3 + 2] = colors[i].b;
            trns[i] = colors[i].a;
        }
    } अन्यथा {
        यदि (surface->format != SDL_PIXELFORMAT_RGBA32) {
            surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);
            यदि (!surface) {
                गच्छ done;
            }
            free_surface = true;
        }
    }

    माप_प्रकार size = 0;
    शून्य *png = tdefl_write_image_to_png_file_in_memory_ex(surface->pixels, surface->w, surface->h, SDL_BYTESPERPIXEL(surface->format), surface->pitch, &size, 6, MZ_FALSE, plte, plte_size, trns, trns_size);
    यदि (png) {
        यदि (SDL_WriteIO(dst, png, size)) {
            retval = true;
        }
        mz_free(png); /* calls SDL_free() */
    } अन्यथा {
        SDL_SetError("Failed to convert and save image");
    }

#अन्यथा
    SDL_SetError("SDL not built with STB image support");
#endif

done:
    यदि (free_surface) {
        SDL_DestroySurface(surface);
    }
    SDL_free(plte);
    SDL_free(trns);

    यदि (dst && closeio) {
        retval &= SDL_CloseIO(dst);
    }
    फर्काऊ retval;
}

bool SDL_SavePNG(SDL_Surface *surface, अचर वर्ण *file)
{
#ifdef SDL_HAVE_STB
    // Make sure we have something to save
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        फर्काऊ SDL_InvalidParamError("surface");
    }

    यदि (SDL_ISPIXELFORMAT_INDEXED(surface->format) && !surface->palette) {
        फर्काऊ SDL_SetError("Indexed surfaces must have a palette");
    }
    SDL_IOStream *stream = SDL_IOFromFile(file, "wb");
    यदि (!stream) {
        फर्काऊ false;
    }

    फर्काऊ SDL_SavePNG_IO(surface, stream, true);
#अन्यथा
    फर्काऊ SDL_SetError("SDL not built with STB image support");
#endif
}
