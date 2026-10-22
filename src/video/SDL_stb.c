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

#समावेश "SDL_stb_c.h"
#समावेश "SDL_surface_c.h"
#समावेश "SDL_yuv_c.h"

/* STB image conversion */
#अगर_अघोषित SDL_DISABLE_STB
#घोषणा SDL_HAVE_STB
#पूर्ण_अगर

#अगर_घोषित SDL_HAVE_STB
////////////////////////////////////////////////////////////////////////////
#घोषणा दो_स्मृति SDL_malloc
#घोषणा पुनः_स्मृति SDL_realloc
#घोषणा मुक्त SDL_free
#अघोषित स_नकल
#घोषणा स_नकल SDL_memcpy
#अघोषित स_रखो
#घोषणा स_रखो SDL_memset
#अघोषित म_भेद
#घोषणा म_भेद SDL_strcmp
#अघोषित म_भेदन
#घोषणा म_भेदन SDL_strncmp
#घोषणा म_से_दीर्घ SDL_strtol

#घोषणा असल SDL_abs
#घोषणा घात SDL_pow
#घोषणा ldexp SDL_scalbn

#घोषणा STB_IMAGE_STATIC
#घोषणा STBI_NO_THREAD_LOCALS
#घोषणा STBI_FAILURE_USERMSG
#अगर defined(SDL_NEON_INTRINSICS)
#घोषणा STBI_NEON
#पूर्ण_अगर
#घोषणा STBI_ONLY_PNG
#घोषणा STBI_ONLY_JPEG
#घोषणा STBI_NO_GIF
#घोषणा STBI_NO_HDR
#घोषणा STBI_NO_LINEAR
#घोषणा STBI_NO_STDIO
#घोषणा STBI_ASSERT SDL_assert
#घोषणा STB_IMAGE_IMPLEMENTATION
#समावेश "stb_image.h"

////////////////////////////////////////////////////////////////////////////
#घोषणा MZ_ASSERT(x) SDL_assert(x)
//#undef memcpy
//#define memcpy SDL_memcpy
//#undef memset
//#define memset SDL_memset
#अगर SDL_BYTEORDER == SDL_LIL_ENDIAN
#घोषणा MINIZ_LITTLE_ENDIAN 1
#अन्यथा
#घोषणा MINIZ_LITTLE_ENDIAN 0
#पूर्ण_अगर
#घोषणा MINIZ_USE_UNALIGNED_LOADS_AND_STORES 0
#घोषणा MINIZ_SDL_NOUNUSED
#समावेश "miniz.h"

#अघोषित स_रखो
#पूर्ण_अगर // SDL_HAVE_STB

#अगर_घोषित SDL_HAVE_STB
अटल bool SDL_ConvertPixels_MJPG_to_NV12(पूर्णांक width, पूर्णांक height, स्थिर व्योम *src, पूर्णांक src_pitch, व्योम *dst, पूर्णांक dst_pitch)
{
    पूर्णांक w = 0, h = 0, format = 0;
    stbi__context s;
    stbi__start_mem(&s, src, src_pitch);

    stbi_परिणाम_info ri;
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

    व्योम *pixels = stbi__jpeg_load(&s, &w, &h, &format, 4, &nv12, &ri);
    अगर (!pixels) {
        वापस false;
    }
    वापस true;
}
#पूर्ण_अगर // SDL_HAVE_STB

bool SDL_ConvertPixels_STB(पूर्णांक width, पूर्णांक height,
                           SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, स्थिर व्योम *src, पूर्णांक src_pitch,
                           SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, व्योम *dst, पूर्णांक dst_pitch)
{
#अगर_घोषित SDL_HAVE_STB
    अगर (src_format == SDL_PIXELFORMAT_MJPG) {
        अगर (dst_format == SDL_PIXELFORMAT_NV12) {
            वापस SDL_ConvertPixels_MJPG_to_NV12(width, height, src, src_pitch, dst, dst_pitch);
        } अन्यथा अगर (
            dst_format == SDL_PIXELFORMAT_YV12 ||
            dst_format == SDL_PIXELFORMAT_IYUV ||
            dst_format == SDL_PIXELFORMAT_YUY2 ||
            dst_format == SDL_PIXELFORMAT_UYVY ||
            dst_format == SDL_PIXELFORMAT_YVYU ||
            dst_format == SDL_PIXELFORMAT_NV21 ||
            dst_format == SDL_PIXELFORMAT_P010
        ) {
            माप_प्रकार अस्थायी_आकार = 0;
            माप_प्रकार अस्थायी_pitch = 0;
            अगर (!SDL_CalculateYUVSize(dst_format, width, height, &अस्थायी_आकार, &अस्थायी_pitch)) {
                वापस false;
            }
            व्योम *अस्थायी_pixels = SDL_malloc(अस्थायी_आकार);
            अगर (!अस्थायी_pixels) {
                वापस false;
            }

            अगर (!SDL_ConvertPixels_MJPG_to_NV12(width, height, src, src_pitch, अस्थायी_pixels, (पूर्णांक)अस्थायी_pitch)) {
                SDL_free(अस्थायी_pixels);
                वापस false;
            }

            bool परिणाम = SDL_ConvertPixelsAndColorspace(width, height, SDL_PIXELFORMAT_NV12, src_colorspace, 0 /*props*/, अस्थायी_pixels, (पूर्णांक)अस्थायी_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
            SDL_free(अस्थायी_pixels);
            वापस परिणाम;
        }
    }

    bool परिणाम;
    पूर्णांक w = 0, h = 0, format = 0;
    पूर्णांक len = (src_format == SDL_PIXELFORMAT_MJPG) ? src_pitch : (height * src_pitch);
    व्योम *pixels = stbi_load_from_memory(src, len, &w, &h, &format, 4);
    अगर (!pixels) {
        वापस false;
    }

    अगर (w == width && h == height) {
        परिणाम = SDL_ConvertPixelsAndColorspace(w, h, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, pixels, width * 4, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } अन्यथा {
        परिणाम = SDL_SetError("Expected image size %dx%d, actual size %dx%d", width, height, w, h);
    }
    stbi_image_free(pixels);

    वापस परिणाम;
#अन्यथा
    वापस SDL_SetError("SDL not built with STB image support");
#पूर्ण_अगर
}

#अगर_घोषित SDL_HAVE_STB
अटल पूर्णांक IMG_LoadSTB_IO_read(व्योम *user, अक्षर *तथ्य, पूर्णांक आकार)
{
    माप_प्रकार amount = SDL_ReadIO((SDL_IOStream*)user, तथ्य, आकार);
    वापस (पूर्णांक)amount;
}

अटल व्योम IMG_LoadSTB_IO_skip(व्योम *user, पूर्णांक n)
{
    SDL_SeekIO((SDL_IOStream*)user, n, SDL_IO_SEEK_CUR);
}

अटल पूर्णांक IMG_LoadSTB_IO_eof(व्योम *user)
{
    SDL_IOStream *src = (SDL_IOStream*)user;
    वापस SDL_GetIOStatus(src) == SDL_IO_STATUS_EOF;
}

अटल SDL_Surface *SDL_LoadSTB_IO(SDL_IOStream *src)
{
    Sint64 start;
    Uint8 magic[26];
    पूर्णांक w, h, format;
    stbi_uc *pixels;
    stbi_io_callbacks rw_callbacks;
    SDL_Surface *surface = शून्य;
    bool use_palette = false;
    अचिन्हित पूर्णांक palette_colors[256];

    // src has already been validated
    start = SDL_TellIO(src);

    अगर (SDL_ReadIO(src, magic, माप(magic)) == माप(magic)) {
        स्थिर Uint8 PNG_COLOR_INDEXED = 3;
        अगर (magic[0] == 0x89 &&
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
    rw_callbacks.पढ़ो = IMG_LoadSTB_IO_read;
    rw_callbacks.skip = IMG_LoadSTB_IO_skip;
    rw_callbacks.eof = IMG_LoadSTB_IO_eof;
    w = h = format = 0; /* silence warning */
    अगर (use_palette) {
        /* Unused palette entries will be opaque white */
        SDL_memset(palette_colors, 0xff, माप(palette_colors));

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
    अगर (!pixels) {
        SDL_SeekIO(src, start, SDL_IO_SEEK_SET);
        वापस शून्य;
    }

    अगर (use_palette) {
        surface = SDL_CreateSurfaceFrom(
            w,
            h,
            SDL_PIXELFORMAT_INDEX8,
            pixels,
            w
        );
        अगर (surface) {
            bool has_colorkey = false;
            पूर्णांक colorkey_सूचकांक = -1;
            bool has_alpha = false;
            SDL_Palette *palette = SDL_CreateSurfacePalette(surface);
            अगर (palette) {
                पूर्णांक i;
                Uint8 *palette_bytes = (Uint8 *)palette_colors;

                क्रम (i = 0; i < palette->ncolors; i++) {
                    palette->colors[i].r = *palette_bytes++;
                    palette->colors[i].g = *palette_bytes++;
                    palette->colors[i].b = *palette_bytes++;
                    palette->colors[i].a = *palette_bytes++;
                    अगर (palette->colors[i].a != SDL_ALPHA_OPAQUE) {
                        अगर (palette->colors[i].a == SDL_ALPHA_TRANSPARENT && !has_colorkey) {
                            has_colorkey = true;
                            colorkey_सूचकांक = i;
                        } अन्यथा {
                            /* Partial opacity or multiple colorkeys */
                            has_alpha = true;
                        }
                    }
                }
            }
            अगर (has_alpha) {
                SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
            } अन्यथा अगर (has_colorkey) {
                SDL_Set_Surface_Color_कुंजी(surface, true, colorkey_सूचकांक);
            }

            /* FIXME: This sucks. It'd be better to allocate the surface first, then
             * write directly to the pixel buffer:
             * https://github.com/nothings/stb/issues/58
             * -flibit
             */
            surface->flags &= ~SDL_SURFACE_PREALLOCATED;
        }

    } अन्यथा अगर (format == STBI_grey || format == STBI_rgb || format == STBI_rgb_alpha) {
        surface = SDL_CreateSurfaceFrom(
            w,
            h,
            (format == STBI_rgb_alpha) ? SDL_PIXELFORMAT_RGBA32 :
            (format == STBI_rgb) ? SDL_PIXELFORMAT_RGB24 :
            SDL_PIXELFORMAT_INDEX8,
            pixels,
            w * format
        );
        अगर (surface) {
            /* Set a grayscale palette for gray images */
            अगर (surface->format == SDL_PIXELFORMAT_INDEX8) {
                SDL_Palette *palette = SDL_CreateSurfacePalette(surface);
                अगर (palette) {
                    पूर्णांक i;

                    क्रम (i = 0; i < palette->ncolors; i++) {
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

    } अन्यथा अगर (format == STBI_grey_alpha) {
        surface = SDL_CreateSurfaceUninitialized(w, h, SDL_PIXELFORMAT_RGBA32);
        अगर (surface) {
            Uint8 *src_ptr = pixels;
            Uint8 *dst = (Uint8 *)surface->pixels;
            पूर्णांक skip = surface->pitch - (surface->w * 4);
            पूर्णांक row, col;

            क्रम (row = 0; row < h; ++row) {
                क्रम (col = 0; col < w; ++col) {
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

    अगर (!surface) {
        /* The error message should already be set */
        stbi_image_free(pixels); /* calls SDL_free() */
        SDL_SeekIO(src, start, SDL_IO_SEEK_SET);
    }
    वापस surface;
}
#पूर्ण_अगर // SDL_HAVE_STB

/* FIXME: This is a copypaste from JPEGLIB! Pull that out of the ifdefs */
/* Define this for quicker (but less perfect) JPEG identification */
#घोषणा FAST_IS_JPEG

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

    अगर (!src) {
        वापस false;
    }

    start = SDL_TellIO(src);
    is_JPG = false;
    in_scan = false;
    अगर (SDL_ReadIO(src, magic, 2) == 2) {
        अगर ( (magic[0] == 0xFF) && (magic[1] == 0xD8) ) {
            is_JPG = true;
            जबतक (is_JPG) {
                अगर (SDL_ReadIO(src, magic, 2) != 2) {
                    is_JPG = false;
                } अन्यथा अगर ( (magic[0] != 0xFF) && !in_scan ) {
                    is_JPG = false;
                } अन्यथा अगर ( (magic[0] != 0xFF) || (magic[1] == 0xFF) ) {
                    /* Extra padding in JPEG (legal) */
                    /* or this is data and we are scanning */
                    SDL_SeekIO(src, -1, SDL_IO_SEEK_CUR);
                } अन्यथा अगर (magic[1] == 0xD9) {
                    /* Got to end of good JPEG */
                    अवरोध;
                } अन्यथा अगर ( in_scan && (magic[1] == 0x00) ) {
                    /* This is an encoded 0xFF within the data */
                } अन्यथा अगर ( (magic[1] >= 0xD0) && (magic[1] < 0xD9) ) {
                    /* These have nothing else */
                } अन्यथा अगर (SDL_ReadIO(src, magic+2, 2) != 2) {
                    is_JPG = false;
                } अन्यथा {
                    /* Yes, it's big-endian */
                    Sint64 innerStart;
                    Uint32 आकार;
                    Sint64 end;
                    innerStart = SDL_TellIO(src);
                    आकार = (magic[2] << 8) + magic[3];
                    end = SDL_SeekIO(src, आकार-2, SDL_IO_SEEK_CUR);
                    अगर ( end != innerStart + आकार - 2 ) {
                        is_JPG = false;
                    }
                    अगर ( magic[1] == 0xDA ) {
                        /* Now comes the actual JPEG meat */
#अगर_घोषित  FAST_IS_JPEG
                        /* Ok, I'm convinced.  It is a JPEG. */
                        अवरोध;
#अन्यथा
                        /* I'm not convinced.  Prove it! */
                        in_scan = true;
#पूर्ण_अगर
                    }
                }
            }
        }
    }
    SDL_SeekIO(src, start, SDL_IO_SEEK_SET);
    वापस is_JPG;
}

SDL_Surface *SDL_LoadJPG_IO(SDL_IOStream *src, bool closeio)
{
    SDL_Surface *surface = शून्य;

    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        जाओ done;
    }

    अगर (!SDL_IsJPG(src)) {
        SDL_SetError("File is not a JPEG file");
        जाओ done;
    }

#अगर_घोषित SDL_HAVE_STB
    surface = SDL_LoadSTB_IO(src);
#अन्यथा
    SDL_SetError("SDL not built with STB image support");
#पूर्ण_अगर // SDL_HAVE_STB

done:
    अगर (src && closeio) {
        SDL_CloseIO(src);
    }
    वापस surface;
}

SDL_Surface *SDL_LoadJPG(स्थिर अक्षर *file)
{
    SDL_IOStream *stream = SDL_IOFromFile(file, "rb");
    अगर (!stream) {
        वापस शून्य;
    }

    वापस SDL_LoadJPG_IO(stream, true);
}

bool SDL_IsPNG(SDL_IOStream *src)
{
    Sint64 start;
    Uint8 magic[4];
    bool is_PNG;

    is_PNG = false;
    start = SDL_TellIO(src);
    अगर (start >= 0) {
        अगर (SDL_ReadIO(src, magic, माप(magic)) == माप(magic)) {
            अगर (magic[0] == 0x89 &&
                magic[1] == 'P' &&
                magic[2] == 'N' &&
                magic[3] == 'G') {
                is_PNG = true;
            }
        }
        SDL_SeekIO(src, start, SDL_IO_SEEK_SET);
    }

    वापस is_PNG;
}

SDL_Surface *SDL_LoadPNG_IO(SDL_IOStream *src, bool closeio)
{
    SDL_Surface *surface = शून्य;

    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        जाओ done;
    }

    अगर (!SDL_IsPNG(src)) {
        SDL_SetError("File is not a PNG file");
        जाओ done;
    }

#अगर_घोषित SDL_HAVE_STB
    surface = SDL_LoadSTB_IO(src);
#अन्यथा
    SDL_SetError("SDL not built with STB image support");
#पूर्ण_अगर // SDL_HAVE_STB

done:
    अगर (src && closeio) {
        SDL_CloseIO(src);
    }
    वापस surface;
}

SDL_Surface *SDL_LoadPNG(स्थिर अक्षर *file)
{
    SDL_IOStream *stream = SDL_IOFromFile(file, "rb");
    अगर (!stream) {
        वापस शून्य;
    }

    वापस SDL_LoadPNG_IO(stream, true);
}

bool SDL_SavePNG_IO(SDL_Surface *surface, SDL_IOStream *dst, bool closeio)
{
    bool retval = false;
    Uint8 *plte = शून्य;
    Uint8 *trns = शून्य;
    bool free_surface = false;

    // Make sure we have something to save
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        जाओ done;
    }
    CHECK_PARAM(!dst) {
        SDL_InvalidParamError("dst");
        जाओ done;
    }

#अगर_घोषित SDL_HAVE_STB
    पूर्णांक plte_आकार = 0;
    पूर्णांक trns_आकार = 0;

    अगर (SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        अगर (!surface->palette) {
            SDL_SetError("Indexed surfaces must have a palette");
            जाओ done;
        }

        अगर (surface->format != SDL_PIXELFORMAT_INDEX8) {
            surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_INDEX8);
            अगर (!surface) {
                जाओ done;
            }
            free_surface = true;
        }

        plte_आकार = surface->palette->ncolors * 3;
        trns_आकार = surface->palette->ncolors;
        plte = (Uint8 *)SDL_malloc(plte_आकार);
        trns = (Uint8 *)SDL_malloc(trns_आकार);
        अगर (!plte || !trns) {
            जाओ done;
        }
        SDL_Color *colors = surface->palette->colors;
        क्रम (पूर्णांक i = 0; i < surface->palette->ncolors; ++i) {
            plte[i * 3 + 0] = colors[i].r;
            plte[i * 3 + 1] = colors[i].g;
            plte[i * 3 + 2] = colors[i].b;
            trns[i] = colors[i].a;
        }
    } अन्यथा {
        अगर (surface->format != SDL_PIXELFORMAT_RGBA32) {
            surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);
            अगर (!surface) {
                जाओ done;
            }
            free_surface = true;
        }
    }

    माप_प्रकार आकार = 0;
    व्योम *png = tdefl_write_image_to_png_file_in_memory_ex(surface->pixels, surface->w, surface->h, SDL_BYTESPERPIXEL(surface->format), surface->pitch, &आकार, 6, MZ_FALSE, plte, plte_आकार, trns, trns_आकार);
    अगर (png) {
        अगर (SDL_WriteIO(dst, png, आकार)) {
            retval = true;
        }
        mz_free(png); /* calls SDL_free() */
    } अन्यथा {
        SDL_SetError("Failed to convert and save image");
    }

#अन्यथा
    SDL_SetError("SDL not built with STB image support");
#पूर्ण_अगर

done:
    अगर (free_surface) {
        SDL_DestroySurface(surface);
    }
    SDL_free(plte);
    SDL_free(trns);

    अगर (dst && closeio) {
        retval &= SDL_CloseIO(dst);
    }
    वापस retval;
}

bool SDL_SavePNG(SDL_Surface *surface, स्थिर अक्षर *file)
{
#अगर_घोषित SDL_HAVE_STB
    // Make sure we have something to save
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        वापस SDL_InvalidParamError("surface");
    }

    अगर (SDL_ISPIXELFORMAT_INDEXED(surface->format) && !surface->palette) {
        वापस SDL_SetError("Indexed surfaces must have a palette");
    }
    SDL_IOStream *stream = SDL_IOFromFile(file, "wb");
    अगर (!stream) {
        वापस false;
    }

    वापस SDL_SavePNG_IO(surface, stream, true);
#अन्यथा
    वापस SDL_SetError("SDL not built with STB image support");
#पूर्ण_अगर
}
