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
#यदि_अपरिभाषितम् SDL_DISABLE_STB
#परिभाषय SDL_HAVE_STB
#यदि_अन्तः

#यदि_परिभाषितम् SDL_HAVE_STB
////////////////////////////////////////////////////////////////////////////
#परिभाषय स्मृतिं_देहि SDL_malloc
#परिभाषय realloc SDL_realloc
#परिभाषय मुक्त SDL_free
#अपरिभाषय स्मृतिं_प्रतिलिख
#परिभाषय स्मृतिं_प्रतिलिख SDL_memcpy
#अपरिभाषय स्मृतिं_पूरय
#परिभाषय स्मृतिं_पूरय SDL_memset
#अपरिभाषय वाक्यं_तुलय
#परिभाषय वाक्यं_तुलय SDL_strcmp
#अपरिभाषय वाक्ये_तुलय
#परिभाषय वाक्ये_तुलय SDL_strncmp
#परिभाषय strtol SDL_strtol

#परिभाषय निरपेक्षम् SDL_abs
#परिभाषय घातः SDL_pow
#परिभाषय ldexp SDL_scalbn

#परिभाषय STB_IMAGE_STATIC
#परिभाषय STBI_NO_THREAD_LOCALS
#परिभाषय STBI_FAILURE_USERMSG
#यदि defined(SDL_NEON_INTRINSICS)
#परिभाषय STBI_NEON
#यदि_अन्तः
#परिभाषय STBI_ONLY_PNG
#परिभाषय STBI_ONLY_JPEG
#परिभाषय STBI_NO_GIF
#परिभाषय STBI_NO_HDR
#परिभाषय STBI_NO_रैखिकम्
#परिभाषय STBI_NO_STDIO
#परिभाषय STBI_ASSERT SDL_assert
#परिभाषय STB_IMAGE_IMPLEMENTATION
#अन्तर्भाव "stb_image.h"

////////////////////////////////////////////////////////////////////////////
#परिभाषय MZ_ASSERT(x) SDL_assert(x)
//#undef memcpy
//#define memcpy SDL_memcpy
//#undef memset
//#define memset SDL_memset
#यदि SDL_BYTEORDER == SDL_LIL_ENDIAN
#परिभाषय MINIZ_LITTLE_ENDIAN 1
#अन्यथा
#परिभाषय MINIZ_LITTLE_ENDIAN 0
#यदि_अन्तः
#परिभाषय MINIZ_USE_UNALIGNED_LOADS_AND_STORES 0
#परिभाषय MINIZ_SDL_NOUNUSED
#अन्तर्भाव "miniz.h"

#अपरिभाषय स्मृतिं_पूरय
#यदि_अन्तः // SDL_HAVE_STB

#यदि_परिभाषितम् SDL_HAVE_STB
स्थिर bool SDL_Convert_Pixels_MJPG_गन्तव्यम्_NV12(पूर्णाङ्क विस्तारः, पूर्णाङ्क height, ध्रुव शून्य *src, पूर्णाङ्क src_pitch, शून्य *dst, पूर्णाङ्क dst_pitch)
{
    पूर्णाङ्क w = 0, h = 0, format = 0;
    stbi__context s;
    stbi__start_mem(&s, src, src_pitch);

    stbi_परिणाम_info ri;
    SDL_zero(ri);
    ri.द्वयङ्काः_प्रत्येकम्_channel = 8;
    ri.channel_क्रमः = STBI_क्रमः_RGB;
    ri.अङ्कः_channels = 0;

    stbi__nv12 nv12;
    nv12.w = विस्तारः;
    nv12.h = height;
    nv12.pitch = dst_pitch;
    nv12.y = (stbi_uc *)dst;
    nv12.uv = nv12.y + (nv12.h * nv12.pitch);

    शून्य *pixels = stbi_jpeg_आरोपय(&s, &w, &h, &format, 4, &nv12, &ri);
    यदि (!pixels) {
        प्रत्यागम false;
    }
    प्रत्यागम true;
}
#यदि_अन्तः // SDL_HAVE_STB

bool SDL_ConvertPixels_STB(पूर्णाङ्क विस्तारः, पूर्णाङ्क height,
                           SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ध्रुव शून्य *src, पूर्णाङ्क src_pitch,
                           SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, शून्य *dst, पूर्णाङ्क dst_pitch)
{
#यदि_परिभाषितम् SDL_HAVE_STB
    यदि (src_format == SDL_PIXELFORMAT_MJPG) {
        यदि (dst_format == SDL_PIXELFORMAT_NV12) {
            प्रत्यागम SDL_Convert_Pixels_MJPG_गन्तव्यम्_NV12(विस्तारः, height, src, src_pitch, dst, dst_pitch);
        } अन्यथा यदि (
            dst_format == SDL_PIXELFORMAT_YV12 ||
            dst_format == SDL_PIXELFORMAT_IYUV ||
            dst_format == SDL_PIXELFORMAT_YUY2 ||
            dst_format == SDL_PIXELFORMAT_UYVY ||
            dst_format == SDL_PIXELFORMAT_YVYU ||
            dst_format == SDL_PIXELFORMAT_NV21 ||
            dst_format == SDL_PIXELFORMAT_P010
        ) {
            size_t अस्थायी_आकार = 0;
            size_t अस्थायी_pitch = 0;
            यदि (!SDL_CalculateYUVSize(dst_format, विस्तारः, height, &अस्थायी_आकार, &अस्थायी_pitch)) {
                प्रत्यागम false;
            }
            शून्य *अस्थायी_pixels = SDL_malloc(अस्थायी_आकार);
            यदि (!अस्थायी_pixels) {
                प्रत्यागम false;
            }

            यदि (!SDL_Convert_Pixels_MJPG_गन्तव्यम्_NV12(विस्तारः, height, src, src_pitch, अस्थायी_pixels, (पूर्णाङ्क)अस्थायी_pitch)) {
                SDL_free(अस्थायी_pixels);
                प्रत्यागम false;
            }

            bool परिणाम = SDL_ConvertPixelsAndColorspace(विस्तारः, height, SDL_PIXELFORMAT_NV12, src_colorspace, 0 /*props*/, अस्थायी_pixels, (पूर्णाङ्क)अस्थायी_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
            SDL_free(अस्थायी_pixels);
            प्रत्यागम परिणाम;
        }
    }

    bool परिणाम;
    पूर्णाङ्क w = 0, h = 0, format = 0;
    पूर्णाङ्क len = (src_format == SDL_PIXELFORMAT_MJPG) ? src_pitch : (height * src_pitch);
    शून्य *pixels = stbi_आरोपय_from_स्मृतिः(src, len, &w, &h, &format, 4);
    यदि (!pixels) {
        प्रत्यागम false;
    }

    यदि (w == विस्तारः && h == height) {
        परिणाम = SDL_ConvertPixelsAndColorspace(w, h, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, pixels, विस्तारः * 4, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } अन्यथा {
        परिणाम = SDL_समुच्चयः_Error("Expected image size %dx%d, actual size %dx%d", विस्तारः, height, w, h);
    }
    stbi_image_free(pixels);

    प्रत्यागम परिणाम;
#अन्यथा
    प्रत्यागम SDL_समुच्चयः_Error("SDL not built with STB image support");
#यदि_अन्तः
}

#यदि_परिभाषितम् SDL_HAVE_STB
स्थिर पूर्णाङ्क IMG_आरोपय_STB_IO_read(शून्य *user, वर्ण *दत्त, पूर्णाङ्क आकार)
{
    size_t amount = SDL_ReadIO((SDL_IOStream*)user, दत्त, आकार);
    प्रत्यागम (पूर्णाङ्क)amount;
}

स्थिर शून्य IMG_आरोपय_STB_IO_skip(शून्य *user, पूर्णाङ्क n)
{
    SDL_SeekIO((SDL_IOStream*)user, n, SDL_IO_SEEK_CUR);
}

स्थिर पूर्णाङ्क IMG_आरोपय_STB_IO_eof(शून्य *user)
{
    SDL_IOStream *src = (SDL_IOStream*)user;
    प्रत्यागम SDL_GetIOStatus(src) == SDL_IO_स्थितिः_EOF;
}

स्थिर SDL_Surface *SDL_आरोपय_STB_IO(SDL_IOStream *src)
{
    Sint64 start;
    Uint8 magic[26];
    पूर्णाङ्क w, h, format;
    stbi_uc *pixels;
    stbi_io_callbacks rw_callbacks;
    SDL_Surface *surface = रिक्त;
    bool use_palette = false;
    अचिह्नित पूर्णाङ्क palette_colors[256];

    // src has already been validated
    start = SDL_TellIO(src);

    यदि (SDL_ReadIO(src, magic, परिमाण(magic)) == परिमाण(magic)) {
        ध्रुव Uint8 PNG_COLOR_अनुक्रमितम् = 3;
        यदि (magic[0] == 0x89 &&
            magic[1] == 'P' &&
            magic[2] == 'N' &&
            magic[3] == 'G' &&
            magic[12] == 'I' &&
            magic[13] == 'H' &&
            magic[14] == 'D' &&
            magic[15] == 'R' &&
            magic[25] == PNG_COLOR_अनुक्रमितम्) {
            use_palette = true;
        }
    }
    SDL_SeekIO(src, start, SDL_IO_SEEK_समुच्चयः);

    /* Load the image data */
    rw_callbacks.पठ = IMG_आरोपय_STB_IO_read;
    rw_callbacks.skip = IMG_आरोपय_STB_IO_skip;
    rw_callbacks.eof = IMG_आरोपय_STB_IO_eof;
    w = h = format = 0; /* silence warning */
    यदि (use_palette) {
        /* Unused palette entries will be opaque white */
        SDL_memset(palette_colors, 0xff, परिमाण(palette_colors));

        pixels = stbi_आरोपय_from_callbacks_with_palette(
            &rw_callbacks,
            src,
            &w,
            &h,
            palette_colors,
            SDL_arraysize(palette_colors)
        );
    } अन्यथा {
        pixels = stbi_आरोपय_from_callbacks(
            &rw_callbacks,
            src,
            &w,
            &h,
            &format,
            STBI_default
        );
    }
    यदि (!pixels) {
        SDL_SeekIO(src, start, SDL_IO_SEEK_समुच्चयः);
        प्रत्यागम रिक्त;
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
            पूर्णाङ्क colorkey_सूचकांक = -1;
            bool has_alpha = false;
            SDL_Palette *palette = SDL_CreateSurfacePalette(surface);
            यदि (palette) {
                पूर्णाङ्क i;
                Uint8 *palette_अष्टकानि = (Uint8 *)palette_colors;

                प्रति (i = 0; i < palette->ncolors; i++) {
                    palette->colors[i].r = *palette_अष्टकानि++;
                    palette->colors[i].g = *palette_अष्टकानि++;
                    palette->colors[i].b = *palette_अष्टकानि++;
                    palette->colors[i].a = *palette_अष्टकानि++;
                    यदि (palette->colors[i].a != SDL_ALPHA_OPAQUE) {
                        यदि (palette->colors[i].a == SDL_ALPHA_TRANSPARENT && !has_colorkey) {
                            has_colorkey = true;
                            colorkey_सूचकांक = i;
                        } अन्यथा {
                            /* Partial opacity or multiple colorkeys */
                            has_alpha = true;
                        }
                    }
                }
            }
            यदि (has_alpha) {
                SDL_समुच्चयः_Surface_Blend_बहुलकम्(surface, SDL_BLENDMODE_BLEND);
            } अन्यथा यदि (has_colorkey) {
                SDL_समुच्चयः_Surface_Color_कुञ्चिका(surface, true, colorkey_सूचकांक);
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

                    प्रति (i = 0; i < palette->ncolors; i++) {
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

            प्रति (row = 0; row < h; ++row) {
                प्रति (col = 0; col < w; ++col) {
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
        SDL_समुच्चयः_Error("Unknown image format: %d", format);
    }

    यदि (!surface) {
        /* The error message should already be set */
        stbi_image_free(pixels); /* calls SDL_free() */
        SDL_SeekIO(src, start, SDL_IO_SEEK_समुच्चयः);
    }
    प्रत्यागम surface;
}
#यदि_अन्तः // SDL_HAVE_STB

/* FIXME: This is a copypaste from JPEGLIB! Pull that out of the ifdefs */
/* Define this for quicker (but less perfect) JPEG identification */
#परिभाषय FAST_IS_JPEG

/* See if an image is contained in a data source */
bool SDL_IsJPG(SDL_IOStream *src)
{
    Sint64 start;
    bool is_JPG;
    bool अन्तर्_अवलोकनम्;
    Uint8 magic[4];

    /* This detection code is by Steaphan Greene <stea@cs.binghamton.edu> */
    /* Blame me, not Sam, if this doesn't work right. */
    /* And don't forget to report the problem to the the sdl list too! */

    यदि (!src) {
        प्रत्यागम false;
    }

    start = SDL_TellIO(src);
    is_JPG = false;
    अन्तर्_अवलोकनम् = false;
    यदि (SDL_ReadIO(src, magic, 2) == 2) {
        यदि ( (magic[0] == 0xFF) && (magic[1] == 0xD8) ) {
            is_JPG = true;
            यावत् (is_JPG) {
                यदि (SDL_ReadIO(src, magic, 2) != 2) {
                    is_JPG = false;
                } अन्यथा यदि ( (magic[0] != 0xFF) && !अन्तर्_अवलोकनम् ) {
                    is_JPG = false;
                } अन्यथा यदि ( (magic[0] != 0xFF) || (magic[1] == 0xFF) ) {
                    /* Extra padding in JPEG (legal) */
                    /* or this is data and we are scanning */
                    SDL_SeekIO(src, -1, SDL_IO_SEEK_CUR);
                } अन्यथा यदि (magic[1] == 0xD9) {
                    /* Got to end of good JPEG */
                    भङ्ग;
                } अन्यथा यदि ( अन्तर्_अवलोकनम् && (magic[1] == 0x00) ) {
                    /* This is an encoded 0xFF within the data */
                } अन्यथा यदि ( (magic[1] >= 0xD0) && (magic[1] < 0xD9) ) {
                    /* These have nothing else */
                } अन्यथा यदि (SDL_ReadIO(src, magic+2, 2) != 2) {
                    is_JPG = false;
                } अन्यथा {
                    /* Yes, it's big-endian */
                    Sint64 innerStart;
                    Uint32 आकार;
                    Sint64 अन्तः;
                    innerStart = SDL_TellIO(src);
                    आकार = (magic[2] << 8) + magic[3];
                    अन्तः = SDL_SeekIO(src, आकार-2, SDL_IO_SEEK_CUR);
                    यदि ( अन्तः != innerStart + आकार - 2 ) {
                        is_JPG = false;
                    }
                    यदि ( magic[1] == 0xDA ) {
                        /* Now comes the actual JPEG meat */
#यदि_परिभाषितम्  FAST_IS_JPEG
                        /* Ok, I'm convinced.  It is a JPEG. */
                        भङ्ग;
#अन्यथा
                        /* I'm not convinced.  Prove it! */
                        अन्तर्_अवलोकनम् = true;
#यदि_अन्तः
                    }
                }
            }
        }
    }
    SDL_SeekIO(src, start, SDL_IO_SEEK_समुच्चयः);
    प्रत्यागम is_JPG;
}

SDL_Surface *SDL_आरोपय_JPG_IO(SDL_IOStream *src, bool closeio)
{
    SDL_Surface *surface = रिक्त;

    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        गच्छ समाप्तम्;
    }

    यदि (!SDL_IsJPG(src)) {
        SDL_समुच्चयः_Error("File is not a JPEG file");
        गच्छ समाप्तम्;
    }

#यदि_परिभाषितम् SDL_HAVE_STB
    surface = SDL_आरोपय_STB_IO(src);
#अन्यथा
    SDL_समुच्चयः_Error("SDL not built with STB image support");
#यदि_अन्तः // SDL_HAVE_STB

समाप्तम्:
    यदि (src && closeio) {
        SDL_CloseIO(src);
    }
    प्रत्यागम surface;
}

SDL_Surface *SDL_आरोपय_JPG(ध्रुव वर्ण *file)
{
    SDL_IOStream *प्रवाहः = SDL_IOFromFile(file, "rb");
    यदि (!प्रवाहः) {
        प्रत्यागम रिक्त;
    }

    प्रत्यागम SDL_आरोपय_JPG_IO(प्रवाहः, true);
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
        SDL_SeekIO(src, start, SDL_IO_SEEK_समुच्चयः);
    }

    प्रत्यागम is_PNG;
}

SDL_Surface *SDL_आरोपय_PNG_IO(SDL_IOStream *src, bool closeio)
{
    SDL_Surface *surface = रिक्त;

    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        गच्छ समाप्तम्;
    }

    यदि (!SDL_IsPNG(src)) {
        SDL_समुच्चयः_Error("File is not a PNG file");
        गच्छ समाप्तम्;
    }

#यदि_परिभाषितम् SDL_HAVE_STB
    surface = SDL_आरोपय_STB_IO(src);
#अन्यथा
    SDL_समुच्चयः_Error("SDL not built with STB image support");
#यदि_अन्तः // SDL_HAVE_STB

समाप्तम्:
    यदि (src && closeio) {
        SDL_CloseIO(src);
    }
    प्रत्यागम surface;
}

SDL_Surface *SDL_आरोपय_PNG(ध्रुव वर्ण *file)
{
    SDL_IOStream *प्रवाहः = SDL_IOFromFile(file, "rb");
    यदि (!प्रवाहः) {
        प्रत्यागम रिक्त;
    }

    प्रत्यागम SDL_आरोपय_PNG_IO(प्रवाहः, true);
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
        गच्छ समाप्तम्;
    }
    CHECK_PARAM(!dst) {
        SDL_InvalidParamError("dst");
        गच्छ समाप्तम्;
    }

#यदि_परिभाषितम् SDL_HAVE_STB
    पूर्णाङ्क plte_आकार = 0;
    पूर्णाङ्क trns_आकार = 0;

    यदि (SDL_ISPIXELFORMAT_अनुक्रमितम्(surface->format)) {
        यदि (!surface->palette) {
            SDL_समुच्चयः_Error("Indexed surfaces must have a palette");
            गच्छ समाप्तम्;
        }

        यदि (surface->format != SDL_PIXELFORMAT_INDEX8) {
            surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_INDEX8);
            यदि (!surface) {
                गच्छ समाप्तम्;
            }
            free_surface = true;
        }

        plte_आकार = surface->palette->ncolors * 3;
        trns_आकार = surface->palette->ncolors;
        plte = (Uint8 *)SDL_malloc(plte_आकार);
        trns = (Uint8 *)SDL_malloc(trns_आकार);
        यदि (!plte || !trns) {
            गच्छ समाप्तम्;
        }
        SDL_Color *colors = surface->palette->colors;
        प्रति (पूर्णाङ्क i = 0; i < surface->palette->ncolors; ++i) {
            plte[i * 3 + 0] = colors[i].r;
            plte[i * 3 + 1] = colors[i].g;
            plte[i * 3 + 2] = colors[i].b;
            trns[i] = colors[i].a;
        }
    } अन्यथा {
        यदि (surface->format != SDL_PIXELFORMAT_RGBA32) {
            surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);
            यदि (!surface) {
                गच्छ समाप्तम्;
            }
            free_surface = true;
        }
    }

    size_t आकार = 0;
    शून्य *png = tdefl_write_image_गन्तव्यम्_png_file_अन्तर्_स्मृतिः_ex(surface->pixels, surface->w, surface->h, SDL_BYTESPERPIXEL(surface->format), surface->pitch, &आकार, 6, MZ_FALSE, plte, plte_आकार, trns, trns_आकार);
    यदि (png) {
        यदि (SDL_WriteIO(dst, png, आकार)) {
            retval = true;
        }
        mz_free(png); /* calls SDL_free() */
    } अन्यथा {
        SDL_समुच्चयः_Error("Failed to convert and save image");
    }

#अन्यथा
    SDL_समुच्चयः_Error("SDL not built with STB image support");
#यदि_अन्तः

समाप्तम्:
    यदि (free_surface) {
        SDL_DestroySurface(surface);
    }
    SDL_free(plte);
    SDL_free(trns);

    यदि (dst && closeio) {
        retval &= SDL_CloseIO(dst);
    }
    प्रत्यागम retval;
}

bool SDL_SavePNG(SDL_Surface *surface, ध्रुव वर्ण *file)
{
#यदि_परिभाषितम् SDL_HAVE_STB
    // Make sure we have something to save
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        प्रत्यागम SDL_InvalidParamError("surface");
    }

    यदि (SDL_ISPIXELFORMAT_अनुक्रमितम्(surface->format) && !surface->palette) {
        प्रत्यागम SDL_समुच्चयः_Error("Indexed surfaces must have a palette");
    }
    SDL_IOStream *प्रवाहः = SDL_IOFromFile(file, "wb");
    यदि (!प्रवाहः) {
        प्रत्यागम false;
    }

    प्रत्यागम SDL_SavePNG_IO(surface, प्रवाहः, true);
#अन्यथा
    प्रत्यागम SDL_समुच्चयः_Error("SDL not built with STB image support");
#यदि_अन्तः
}
