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
#जर defined(SDL_NEON_INTRINSICS)
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
#जर SDL_BYTEORDER == SDL_LIL_ENDIAN
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
स्थिर bool SDL_ConvertPixels_MJPG_to_NV12(पूर्णांक width, पूर्णांक height, स्थिरांक शून्य *src, पूर्णांक src_pitch, शून्य *dst, पूर्णांक dst_pitch)
{
    पूर्णांक w = 0, h = 0, format = 0;
    stbi__context s;
    stbi__start_mem(&s, src, src_pitch);

    stbi__result_info ri;
    SDL_zero(ri);
    ri.bits_per_channel = 8;
    ri.channel_order = STBI_ORDER_RGB;
    ri.अंक_channels = 0;

    stbi__nv12 nv12;
    nv12.w = width;
    nv12.h = height;
    nv12.pitch = dst_pitch;
    nv12.y = (stbi_uc *)dst;
    nv12.uv = nv12.y + (nv12.h * nv12.pitch);

    शून्य *pixels = stbi__jpeg_load(&s, &w, &h, &format, 4, &nv12, &ri);
    जर (!pixels) {
        परत false;
    }
    परत true;
}
#endif // SDL_HAVE_STB

bool SDL_ConvertPixels_STB(पूर्णांक width, पूर्णांक height,
                           SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, स्थिरांक शून्य *src, पूर्णांक src_pitch,
                           SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, शून्य *dst, पूर्णांक dst_pitch)
{
#ifdef SDL_HAVE_STB
    जर (src_format == SDL_PIXELFORMAT_MJPG) {
        जर (dst_format == SDL_PIXELFORMAT_NV12) {
            परत SDL_ConvertPixels_MJPG_to_NV12(width, height, src, src_pitch, dst, dst_pitch);
        } अन्यथा जर (
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
            जर (!SDL_CalculateYUVSize(dst_format, width, height, &temp_size, &temp_pitch)) {
                परत false;
            }
            शून्य *temp_pixels = SDL_malloc(temp_size);
            जर (!temp_pixels) {
                परत false;
            }

            जर (!SDL_ConvertPixels_MJPG_to_NV12(width, height, src, src_pitch, temp_pixels, (पूर्णांक)temp_pitch)) {
                SDL_free(temp_pixels);
                परत false;
            }

            bool result = SDL_ConvertPixelsAndColorspace(width, height, SDL_PIXELFORMAT_NV12, src_colorspace, 0 /*props*/, temp_pixels, (पूर्णांक)temp_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
            SDL_free(temp_pixels);
            परत result;
        }
    }

    bool result;
    पूर्णांक w = 0, h = 0, format = 0;
    पूर्णांक len = (src_format == SDL_PIXELFORMAT_MJPG) ? src_pitch : (height * src_pitch);
    शून्य *pixels = stbi_load_from_memory(src, len, &w, &h, &format, 4);
    जर (!pixels) {
        परत false;
    }

    जर (w == width && h == height) {
        result = SDL_ConvertPixelsAndColorspace(w, h, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, pixels, width * 4, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } अन्यथा {
        result = SDL_SetError("Expected image size %dx%d, actual size %dx%d", width, height, w, h);
    }
    stbi_image_free(pixels);

    परत result;
#अन्यथा
    परत SDL_SetError("SDL not built with STB image support");
#endif
}

#ifdef SDL_HAVE_STB
स्थिर पूर्णांक IMG_LoadSTB_IO_read(शून्य *user, अक्षर *data, पूर्णांक size)
{
    माप_प्रकार amount = SDL_ReadIO((SDL_IOStream*)user, data, size);
    परत (पूर्णांक)amount;
}

स्थिर शून्य IMG_LoadSTB_IO_skip(शून्य *user, पूर्णांक n)
{
    SDL_SeekIO((SDL_IOStream*)user, n, SDL_IO_SEEK_CUR);
}

स्थिर पूर्णांक IMG_LoadSTB_IO_eof(शून्य *user)
{
    SDL_IOStream *src = (SDL_IOStream*)user;
    परत SDL_GetIOStatus(src) == SDL_IO_STATUS_EOF;
}

स्थिर SDL_Surface *SDL_LoadSTB_IO(SDL_IOStream *src)
{
    Sint64 start;
    Uint8 magic[26];
    पूर्णांक w, h, format;
    stbi_uc *pixels;
    stbi_io_callbacks rw_callbacks;
    SDL_Surface *surface = रिक्त;
    bool use_palette = false;
    अचिन्हित पूर्णांक palette_colors[256];

    // src has already been validated
    start = SDL_TellIO(src);

    जर (SDL_ReadIO(src, magic, आकार(magic)) == आकार(magic)) {
        स्थिरांक Uint8 PNG_COLOR_INDEXED = 3;
        जर (magic[0] == 0x89 &&
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
    जर (use_palette) {
        /* Unused palette entries will be opaque white */
        SDL_memset(palette_colors, 0xff, आकार(palette_colors));

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
    जर (!pixels) {
        SDL_SeekIO(src, start, SDL_IO_SEEK_SET);
        परत रिक्त;
    }

    जर (use_palette) {
        surface = SDL_CreateSurfaceFrom(
            w,
            h,
            SDL_PIXELFORMAT_INDEX8,
            pixels,
            w
        );
        जर (surface) {
            bool has_colorkey = false;
            पूर्णांक colorkey_index = -1;
            bool has_alpha = false;
            SDL_Palette *palette = SDL_CreateSurfacePalette(surface);
            जर (palette) {
                पूर्णांक i;
                Uint8 *palette_bytes = (Uint8 *)palette_colors;

                साठी (i = 0; i < palette->ncolors; i++) {
                    palette->colors[i].r = *palette_bytes++;
                    palette->colors[i].g = *palette_bytes++;
                    palette->colors[i].b = *palette_bytes++;
                    palette->colors[i].a = *palette_bytes++;
                    जर (palette->colors[i].a != SDL_ALPHA_OPAQUE) {
                        जर (palette->colors[i].a == SDL_ALPHA_TRANSPARENT && !has_colorkey) {
                            has_colorkey = true;
                            colorkey_index = i;
                        } अन्यथा {
                            /* Partial opacity or multiple colorkeys */
                            has_alpha = true;
                        }
                    }
                }
            }
            जर (has_alpha) {
                SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
            } अन्यथा जर (has_colorkey) {
                SDL_Set_Surface_Color_किल्ली(surface, true, colorkey_index);
            }

            /* FIXME: This sucks. It'd be better to allocate the surface first, then
             * write directly to the pixel buffer:
             * https://github.com/nothings/stb/issues/58
             * -flibit
             */
            surface->flags &= ~SDL_SURFACE_PREALLOCATED;
        }

    } अन्यथा जर (format == STBI_grey || format == STBI_rgb || format == STBI_rgb_alpha) {
        surface = SDL_CreateSurfaceFrom(
            w,
            h,
            (format == STBI_rgb_alpha) ? SDL_PIXELFORMAT_RGBA32 :
            (format == STBI_rgb) ? SDL_PIXELFORMAT_RGB24 :
            SDL_PIXELFORMAT_INDEX8,
            pixels,
            w * format
        );
        जर (surface) {
            /* Set a grayscale palette for gray images */
            जर (surface->format == SDL_PIXELFORMAT_INDEX8) {
                SDL_Palette *palette = SDL_CreateSurfacePalette(surface);
                जर (palette) {
                    पूर्णांक i;

                    साठी (i = 0; i < palette->ncolors; i++) {
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

    } अन्यथा जर (format == STBI_grey_alpha) {
        surface = SDL_CreateSurfaceUninitialized(w, h, SDL_PIXELFORMAT_RGBA32);
        जर (surface) {
            Uint8 *src_ptr = pixels;
            Uint8 *dst = (Uint8 *)surface->pixels;
            पूर्णांक skip = surface->pitch - (surface->w * 4);
            पूर्णांक row, col;

            साठी (row = 0; row < h; ++row) {
                साठी (col = 0; col < w; ++col) {
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

    जर (!surface) {
        /* The error message should already be set */
        stbi_image_free(pixels); /* calls SDL_free() */
        SDL_SeekIO(src, start, SDL_IO_SEEK_SET);
    }
    परत surface;
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

    जर (!src) {
        परत false;
    }

    start = SDL_TellIO(src);
    is_JPG = false;
    in_scan = false;
    जर (SDL_ReadIO(src, magic, 2) == 2) {
        जर ( (magic[0] == 0xFF) && (magic[1] == 0xD8) ) {
            is_JPG = true;
            पर्यंत (is_JPG) {
                जर (SDL_ReadIO(src, magic, 2) != 2) {
                    is_JPG = false;
                } अन्यथा जर ( (magic[0] != 0xFF) && !in_scan ) {
                    is_JPG = false;
                } अन्यथा जर ( (magic[0] != 0xFF) || (magic[1] == 0xFF) ) {
                    /* Extra padding in JPEG (legal) */
                    /* or this is data and we are scanning */
                    SDL_SeekIO(src, -1, SDL_IO_SEEK_CUR);
                } अन्यथा जर (magic[1] == 0xD9) {
                    /* Got to end of good JPEG */
                    थांबा;
                } अन्यथा जर ( in_scan && (magic[1] == 0x00) ) {
                    /* This is an encoded 0xFF within the data */
                } अन्यथा जर ( (magic[1] >= 0xD0) && (magic[1] < 0xD9) ) {
                    /* These have nothing else */
                } अन्यथा जर (SDL_ReadIO(src, magic+2, 2) != 2) {
                    is_JPG = false;
                } अन्यथा {
                    /* Yes, it's big-endian */
                    Sint64 innerStart;
                    Uint32 size;
                    Sint64 end;
                    innerStart = SDL_TellIO(src);
                    size = (magic[2] << 8) + magic[3];
                    end = SDL_SeekIO(src, size-2, SDL_IO_SEEK_CUR);
                    जर ( end != innerStart + size - 2 ) {
                        is_JPG = false;
                    }
                    जर ( magic[1] == 0xDA ) {
                        /* Now comes the actual JPEG meat */
#ifdef  FAST_IS_JPEG
                        /* Ok, I'm convinced.  It is a JPEG. */
                        थांबा;
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
    परत is_JPG;
}

SDL_Surface *SDL_LoadJPG_IO(SDL_IOStream *src, bool closeio)
{
    SDL_Surface *surface = रिक्त;

    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        जा done;
    }

    जर (!SDL_IsJPG(src)) {
        SDL_SetError("File is not a JPEG file");
        जा done;
    }

#ifdef SDL_HAVE_STB
    surface = SDL_LoadSTB_IO(src);
#अन्यथा
    SDL_SetError("SDL not built with STB image support");
#endif // SDL_HAVE_STB

done:
    जर (src && closeio) {
        SDL_CloseIO(src);
    }
    परत surface;
}

SDL_Surface *SDL_LoadJPG(स्थिरांक अक्षर *file)
{
    SDL_IOStream *stream = SDL_IOFromFile(file, "rb");
    जर (!stream) {
        परत रिक्त;
    }

    परत SDL_LoadJPG_IO(stream, true);
}

bool SDL_IsPNG(SDL_IOStream *src)
{
    Sint64 start;
    Uint8 magic[4];
    bool is_PNG;

    is_PNG = false;
    start = SDL_TellIO(src);
    जर (start >= 0) {
        जर (SDL_ReadIO(src, magic, आकार(magic)) == आकार(magic)) {
            जर (magic[0] == 0x89 &&
                magic[1] == 'P' &&
                magic[2] == 'N' &&
                magic[3] == 'G') {
                is_PNG = true;
            }
        }
        SDL_SeekIO(src, start, SDL_IO_SEEK_SET);
    }

    परत is_PNG;
}

SDL_Surface *SDL_LoadPNG_IO(SDL_IOStream *src, bool closeio)
{
    SDL_Surface *surface = रिक्त;

    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        जा done;
    }

    जर (!SDL_IsPNG(src)) {
        SDL_SetError("File is not a PNG file");
        जा done;
    }

#ifdef SDL_HAVE_STB
    surface = SDL_LoadSTB_IO(src);
#अन्यथा
    SDL_SetError("SDL not built with STB image support");
#endif // SDL_HAVE_STB

done:
    जर (src && closeio) {
        SDL_CloseIO(src);
    }
    परत surface;
}

SDL_Surface *SDL_LoadPNG(स्थिरांक अक्षर *file)
{
    SDL_IOStream *stream = SDL_IOFromFile(file, "rb");
    जर (!stream) {
        परत रिक्त;
    }

    परत SDL_LoadPNG_IO(stream, true);
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
        जा done;
    }
    CHECK_PARAM(!dst) {
        SDL_InvalidParamError("dst");
        जा done;
    }

#ifdef SDL_HAVE_STB
    पूर्णांक plte_size = 0;
    पूर्णांक trns_size = 0;

    जर (SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        जर (!surface->palette) {
            SDL_SetError("Indexed surfaces must have a palette");
            जा done;
        }

        जर (surface->format != SDL_PIXELFORMAT_INDEX8) {
            surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_INDEX8);
            जर (!surface) {
                जा done;
            }
            free_surface = true;
        }

        plte_size = surface->palette->ncolors * 3;
        trns_size = surface->palette->ncolors;
        plte = (Uint8 *)SDL_malloc(plte_size);
        trns = (Uint8 *)SDL_malloc(trns_size);
        जर (!plte || !trns) {
            जा done;
        }
        SDL_Color *colors = surface->palette->colors;
        साठी (पूर्णांक i = 0; i < surface->palette->ncolors; ++i) {
            plte[i * 3 + 0] = colors[i].r;
            plte[i * 3 + 1] = colors[i].g;
            plte[i * 3 + 2] = colors[i].b;
            trns[i] = colors[i].a;
        }
    } अन्यथा {
        जर (surface->format != SDL_PIXELFORMAT_RGBA32) {
            surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);
            जर (!surface) {
                जा done;
            }
            free_surface = true;
        }
    }

    माप_प्रकार size = 0;
    शून्य *png = tdefl_write_image_to_png_file_in_memory_ex(surface->pixels, surface->w, surface->h, SDL_BYTESPERPIXEL(surface->format), surface->pitch, &size, 6, MZ_FALSE, plte, plte_size, trns, trns_size);
    जर (png) {
        जर (SDL_WriteIO(dst, png, size)) {
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
    जर (free_surface) {
        SDL_DestroySurface(surface);
    }
    SDL_free(plte);
    SDL_free(trns);

    जर (dst && closeio) {
        retval &= SDL_CloseIO(dst);
    }
    परत retval;
}

bool SDL_SavePNG(SDL_Surface *surface, स्थिरांक अक्षर *file)
{
#ifdef SDL_HAVE_STB
    // Make sure we have something to save
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        परत SDL_InvalidParamError("surface");
    }

    जर (SDL_ISPIXELFORMAT_INDEXED(surface->format) && !surface->palette) {
        परत SDL_SetError("Indexed surfaces must have a palette");
    }
    SDL_IOStream *stream = SDL_IOFromFile(file, "wb");
    जर (!stream) {
        परत false;
    }

    परत SDL_SavePNG_IO(surface, stream, true);
#अन्यथा
    परत SDL_SetError("SDL not built with STB image support");
#endif
}
