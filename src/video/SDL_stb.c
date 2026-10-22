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
#شامل "SDL_internal.h"

#شامل "SDL_stb_c.h"
#شامل "SDL_surface_c.h"
#شامل "SDL_yuv_c.h"

/* STB image conversion */
#اگر_غیر_تعریف_شدہ SDL_DISABLE_STB
#تعریف_کرو SDL_HAVE_STB
#اگر_ختم

#اگر_تعریف_شدہ SDL_HAVE_STB
////////////////////////////////////////////////////////////////////////////
#تعریف_کرو حافظہ_دو SDL_malloc
#تعریف_کرو realloc SDL_realloc
#تعریف_کرو آزاد SDL_free
#تعریف_منسوخ حافظہ_نقل
#تعریف_کرو حافظہ_نقل SDL_memcpy
#تعریف_منسوخ memset
#تعریف_کرو memset SDL_memset
#تعریف_منسوخ strcmp
#تعریف_کرو strcmp SDL_strcmp
#تعریف_منسوخ لڑی_موازنہ
#تعریف_کرو لڑی_موازنہ SDL_strncmp
#تعریف_کرو strtol SDL_strtol

#تعریف_کرو مطلق_قدر SDL_abs
#تعریف_کرو قوت SDL_pow
#تعریف_کرو ldexp SDL_scalbn

#تعریف_کرو STB_IMAGE_STATIC
#تعریف_کرو STBI_NO_THREAD_LOCALS
#تعریف_کرو STBI_FAILURE_USERMSG
#اگر defined(SDL_NEON_INTRINSICS)
#تعریف_کرو STBI_NEON
#اگر_ختم
#تعریف_کرو STBI_ONLY_PNG
#تعریف_کرو STBI_ONLY_JPEG
#تعریف_کرو STBI_NO_GIF
#تعریف_کرو STBI_NO_HDR
#تعریف_کرو STBI_NO_خطی
#تعریف_کرو STBI_NO_STDIO
#تعریف_کرو STBI_ASSERT SDL_assert
#تعریف_کرو STB_IMAGE_IMPLEMENTATION
#شامل "stb_image.h"

////////////////////////////////////////////////////////////////////////////
#تعریف_کرو MZ_ASSERT(x) SDL_assert(x)
//#undef memcpy
//#define memcpy SDL_memcpy
//#undef memset
//#define memset SDL_memset
#اگر SDL_BYTEORDER == SDL_LIL_ENDIAN
#تعریف_کرو MINIZ_LITTLE_ENDIAN 1
#ورنہ
#تعریف_کرو MINIZ_LITTLE_ENDIAN 0
#اگر_ختم
#تعریف_کرو MINIZ_USE_UNALIGNED_LOADS_AND_STORES 0
#تعریف_کرو MINIZ_SDL_NOUNUSED
#شامل "miniz.h"

#تعریف_منسوخ memset
#اگر_ختم // SDL_HAVE_STB

#اگر_تعریف_شدہ SDL_HAVE_STB
ساکن bool SDL_Convert_Pixels_MJPG_مقصد_NV12(صحیح چوڑائی, صحیح اونچائی, ثابت خالی *src, صحیح src_pitch, خالی *dst, صحیح dst_pitch)
{
    صحیح w = 0, h = 0, format = 0;
    stbi__context s;
    stbi_آغاز_mem(&s, src, src_pitch);

    stbi_نتیجہ_info ri;
    SDL_zero(ri);
    ri.بٹ_فی_channel = 8;
    ri.channel_ترتیب = STBI_ترتیب_RGB;
    ri.عدد_channels = 0;

    stbi__nv12 nv12;
    nv12.w = چوڑائی;
    nv12.h = اونچائی;
    nv12.pitch = dst_pitch;
    nv12.y = (stbi_uc *)dst;
    nv12.uv = nv12.y + (nv12.h * nv12.pitch);

    خالی *pixels = stbi_jpeg_بھرو(&s, &w, &h, &format, 4, &nv12, &ri);
    اگر (!pixels) {
        واپس false;
    }
    واپس true;
}
#اگر_ختم // SDL_HAVE_STB

bool SDL_ConvertPixels_STB(صحیح چوڑائی, صحیح اونچائی,
                           SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ثابت خالی *src, صحیح src_pitch,
                           SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, خالی *dst, صحیح dst_pitch)
{
#اگر_تعریف_شدہ SDL_HAVE_STB
    اگر (src_format == SDL_PIXELFORMAT_MJPG) {
        اگر (dst_format == SDL_PIXELFORMAT_NV12) {
            واپس SDL_Convert_Pixels_MJPG_مقصد_NV12(چوڑائی, اونچائی, src, src_pitch, dst, dst_pitch);
        } ورنہ اگر (
            dst_format == SDL_PIXELFORMAT_YV12 ||
            dst_format == SDL_PIXELFORMAT_IYUV ||
            dst_format == SDL_PIXELFORMAT_YUY2 ||
            dst_format == SDL_PIXELFORMAT_UYVY ||
            dst_format == SDL_PIXELFORMAT_YVYU ||
            dst_format == SDL_PIXELFORMAT_NV21 ||
            dst_format == SDL_PIXELFORMAT_P010
        ) {
            size_t عارضی_سائز = 0;
            size_t عارضی_pitch = 0;
            اگر (!SDL_CalculateYUVSize(dst_format, چوڑائی, اونچائی, &عارضی_سائز, &عارضی_pitch)) {
                واپس false;
            }
            خالی *عارضی_pixels = SDL_malloc(عارضی_سائز);
            اگر (!عارضی_pixels) {
                واپس false;
            }

            اگر (!SDL_Convert_Pixels_MJPG_مقصد_NV12(چوڑائی, اونچائی, src, src_pitch, عارضی_pixels, (صحیح)عارضی_pitch)) {
                SDL_free(عارضی_pixels);
                واپس false;
            }

            bool نتیجہ = SDL_ConvertPixelsAndColorspace(چوڑائی, اونچائی, SDL_PIXELFORMAT_NV12, src_colorspace, 0 /*props*/, عارضی_pixels, (صحیح)عارضی_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
            SDL_free(عارضی_pixels);
            واپس نتیجہ;
        }
    }

    bool نتیجہ;
    صحیح w = 0, h = 0, format = 0;
    صحیح len = (src_format == SDL_PIXELFORMAT_MJPG) ? src_pitch : (اونچائی * src_pitch);
    خالی *pixels = stbi_بھرو_from_حافظہ(src, len, &w, &h, &format, 4);
    اگر (!pixels) {
        واپس false;
    }

    اگر (w == چوڑائی && h == اونچائی) {
        نتیجہ = SDL_ConvertPixelsAndColorspace(w, h, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, pixels, چوڑائی * 4, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } ورنہ {
        نتیجہ = SDL_سیٹ_Error("Expected image size %dx%d, actual size %dx%d", چوڑائی, اونچائی, w, h);
    }
    stbi_image_free(pixels);

    واپس نتیجہ;
#ورنہ
    واپس SDL_سیٹ_Error("SDL not built with STB image support");
#اگر_ختم
}

#اگر_تعریف_شدہ SDL_HAVE_STB
ساکن صحیح IMG_بھرو_STB_IO_read(خالی *user, حرف *ڈیٹا, صحیح سائز)
{
    size_t amount = SDL_ReadIO((SDL_IOStream*)user, ڈیٹا, سائز);
    واپس (صحیح)amount;
}

ساکن خالی IMG_بھرو_STB_IO_skip(خالی *user, صحیح n)
{
    SDL_SeekIO((SDL_IOStream*)user, n, SDL_IO_SEEK_CUR);
}

ساکن صحیح IMG_بھرو_STB_IO_eof(خالی *user)
{
    SDL_IOStream *src = (SDL_IOStream*)user;
    واپس SDL_GetIOStatus(src) == SDL_IO_حالت_EOF;
}

ساکن SDL_Surface *SDL_بھرو_STB_IO(SDL_IOStream *src)
{
    Sint64 آغاز;
    Uint8 magic[26];
    صحیح w, h, format;
    stbi_uc *pixels;
    stbi_io_callbacks rw_callbacks;
    SDL_Surface *surface = تہی;
    bool use_palette = false;
    غیرعلامتی صحیح palette_colors[256];

    // src has already been validated
    آغاز = SDL_TellIO(src);

    اگر (SDL_ReadIO(src, magic, حجم(magic)) == حجم(magic)) {
        ثابت Uint8 PNG_COLOR_اشاریہ_دار = 3;
        اگر (magic[0] == 0x89 &&
            magic[1] == 'P' &&
            magic[2] == 'N' &&
            magic[3] == 'G' &&
            magic[12] == 'I' &&
            magic[13] == 'H' &&
            magic[14] == 'D' &&
            magic[15] == 'R' &&
            magic[25] == PNG_COLOR_اشاریہ_دار) {
            use_palette = true;
        }
    }
    SDL_SeekIO(src, آغاز, SDL_IO_SEEK_سیٹ);

    /* Load the image data */
    rw_callbacks.اقرأ = IMG_بھرو_STB_IO_read;
    rw_callbacks.skip = IMG_بھرو_STB_IO_skip;
    rw_callbacks.eof = IMG_بھرو_STB_IO_eof;
    w = h = format = 0; /* silence warning */
    اگر (use_palette) {
        /* Unused palette entries will be opaque white */
        SDL_memset(palette_colors, 0xff, حجم(palette_colors));

        pixels = stbi_بھرو_from_callbacks_with_palette(
            &rw_callbacks,
            src,
            &w,
            &h,
            palette_colors,
            SDL_arraysize(palette_colors)
        );
    } ورنہ {
        pixels = stbi_بھرو_from_callbacks(
            &rw_callbacks,
            src,
            &w,
            &h,
            &format,
            STBI_default
        );
    }
    اگر (!pixels) {
        SDL_SeekIO(src, آغاز, SDL_IO_SEEK_سیٹ);
        واپس تہی;
    }

    اگر (use_palette) {
        surface = SDL_CreateSurfaceFrom(
            w,
            h,
            SDL_PIXELFORMAT_INDEX8,
            pixels,
            w
        );
        اگر (surface) {
            bool has_colorkey = false;
            صحیح colorkey_اشاریہ = -1;
            bool has_alpha = false;
            SDL_Palette *palette = SDL_CreateSurfacePalette(surface);
            اگر (palette) {
                صحیح i;
                Uint8 *palette_بائٹیں = (Uint8 *)palette_colors;

                برائے (i = 0; i < palette->ncolors; i++) {
                    palette->colors[i].r = *palette_بائٹیں++;
                    palette->colors[i].g = *palette_بائٹیں++;
                    palette->colors[i].b = *palette_بائٹیں++;
                    palette->colors[i].a = *palette_بائٹیں++;
                    اگر (palette->colors[i].a != SDL_ALPHA_OPAQUE) {
                        اگر (palette->colors[i].a == SDL_ALPHA_TRANSPARENT && !has_colorkey) {
                            has_colorkey = true;
                            colorkey_اشاریہ = i;
                        } ورنہ {
                            /* Partial opacity or multiple colorkeys */
                            has_alpha = true;
                        }
                    }
                }
            }
            اگر (has_alpha) {
                SDL_سیٹ_Surface_Blend_منوال(surface, SDL_BLENDMODE_BLEND);
            } ورنہ اگر (has_colorkey) {
                SDL_سیٹ_Surface_Color_کلید(surface, true, colorkey_اشاریہ);
            }

            /* FIXME: This sucks. It'd be better to allocate the surface first, then
             * write directly to the pixel buffer:
             * https://github.com/nothings/stb/issues/58
             * -flibit
             */
            surface->flags &= ~SDL_SURFACE_PREALLOCATED;
        }

    } ورنہ اگر (format == STBI_grey || format == STBI_rgb || format == STBI_rgb_alpha) {
        surface = SDL_CreateSurfaceFrom(
            w,
            h,
            (format == STBI_rgb_alpha) ? SDL_PIXELFORMAT_RGBA32 :
            (format == STBI_rgb) ? SDL_PIXELFORMAT_RGB24 :
            SDL_PIXELFORMAT_INDEX8,
            pixels,
            w * format
        );
        اگر (surface) {
            /* Set a grayscale palette for gray images */
            اگر (surface->format == SDL_PIXELFORMAT_INDEX8) {
                SDL_Palette *palette = SDL_CreateSurfacePalette(surface);
                اگر (palette) {
                    صحیح i;

                    برائے (i = 0; i < palette->ncolors; i++) {
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

    } ورنہ اگر (format == STBI_grey_alpha) {
        surface = SDL_CreateSurfaceUninitialized(w, h, SDL_PIXELFORMAT_RGBA32);
        اگر (surface) {
            Uint8 *src_ptr = pixels;
            Uint8 *dst = (Uint8 *)surface->pixels;
            صحیح skip = surface->pitch - (surface->w * 4);
            صحیح صف, ستون;

            برائے (صف = 0; صف < h; ++صف) {
                برائے (ستون = 0; ستون < w; ++ستون) {
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
    } ورنہ {
        SDL_سیٹ_Error("Unknown image format: %d", format);
    }

    اگر (!surface) {
        /* The error message should already be set */
        stbi_image_free(pixels); /* calls SDL_free() */
        SDL_SeekIO(src, آغاز, SDL_IO_SEEK_سیٹ);
    }
    واپس surface;
}
#اگر_ختم // SDL_HAVE_STB

/* FIXME: This is a copypaste from JPEGLIB! Pull that out of the ifdefs */
/* Define this for quicker (but less perfect) JPEG identification */
#تعریف_کرو FAST_IS_JPEG

/* See if an image is contained in a data source */
bool SDL_IsJPG(SDL_IOStream *src)
{
    Sint64 آغاز;
    bool is_JPG;
    bool اندر_جائزہ;
    Uint8 magic[4];

    /* This detection code is by Steaphan Greene <stea@cs.binghamton.edu> */
    /* Blame me, not Sam, if this doesn't work right. */
    /* And don't forget to report the problem to the the sdl list too! */

    اگر (!src) {
        واپس false;
    }

    آغاز = SDL_TellIO(src);
    is_JPG = false;
    اندر_جائزہ = false;
    اگر (SDL_ReadIO(src, magic, 2) == 2) {
        اگر ( (magic[0] == 0xFF) && (magic[1] == 0xD8) ) {
            is_JPG = true;
            جب (is_JPG) {
                اگر (SDL_ReadIO(src, magic, 2) != 2) {
                    is_JPG = false;
                } ورنہ اگر ( (magic[0] != 0xFF) && !اندر_جائزہ ) {
                    is_JPG = false;
                } ورنہ اگر ( (magic[0] != 0xFF) || (magic[1] == 0xFF) ) {
                    /* Extra padding in JPEG (legal) */
                    /* or this is data and we are scanning */
                    SDL_SeekIO(src, -1, SDL_IO_SEEK_CUR);
                } ورنہ اگر (magic[1] == 0xD9) {
                    /* Got to end of good JPEG */
                    توڑو;
                } ورنہ اگر ( اندر_جائزہ && (magic[1] == 0x00) ) {
                    /* This is an encoded 0xFF within the data */
                } ورنہ اگر ( (magic[1] >= 0xD0) && (magic[1] < 0xD9) ) {
                    /* These have nothing else */
                } ورنہ اگر (SDL_ReadIO(src, magic+2, 2) != 2) {
                    is_JPG = false;
                } ورنہ {
                    /* Yes, it's big-endian */
                    Sint64 inner_آغاز;
                    Uint32 سائز;
                    Sint64 انتہا;
                    inner_آغاز = SDL_TellIO(src);
                    سائز = (magic[2] << 8) + magic[3];
                    انتہا = SDL_SeekIO(src, سائز-2, SDL_IO_SEEK_CUR);
                    اگر ( انتہا != inner_آغاز + سائز - 2 ) {
                        is_JPG = false;
                    }
                    اگر ( magic[1] == 0xDA ) {
                        /* Now comes the actual JPEG meat */
#اگر_تعریف_شدہ  FAST_IS_JPEG
                        /* Ok, I'm convinced.  It is a JPEG. */
                        توڑو;
#ورنہ
                        /* I'm not convinced.  Prove it! */
                        اندر_جائزہ = true;
#اگر_ختم
                    }
                }
            }
        }
    }
    SDL_SeekIO(src, آغاز, SDL_IO_SEEK_سیٹ);
    واپس is_JPG;
}

SDL_Surface *SDL_بھرو_JPG_IO(SDL_IOStream *src, bool closeio)
{
    SDL_Surface *surface = تہی;

    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        جاؤ مکمل;
    }

    اگر (!SDL_IsJPG(src)) {
        SDL_سیٹ_Error("File is not a JPEG file");
        جاؤ مکمل;
    }

#اگر_تعریف_شدہ SDL_HAVE_STB
    surface = SDL_بھرو_STB_IO(src);
#ورنہ
    SDL_سیٹ_Error("SDL not built with STB image support");
#اگر_ختم // SDL_HAVE_STB

مکمل:
    اگر (src && closeio) {
        SDL_CloseIO(src);
    }
    واپس surface;
}

SDL_Surface *SDL_بھرو_JPG(ثابت حرف *file)
{
    SDL_IOStream *دھارا = SDL_IOFromFile(file, "rb");
    اگر (!دھارا) {
        واپس تہی;
    }

    واپس SDL_بھرو_JPG_IO(دھارا, true);
}

bool SDL_IsPNG(SDL_IOStream *src)
{
    Sint64 آغاز;
    Uint8 magic[4];
    bool is_PNG;

    is_PNG = false;
    آغاز = SDL_TellIO(src);
    اگر (آغاز >= 0) {
        اگر (SDL_ReadIO(src, magic, حجم(magic)) == حجم(magic)) {
            اگر (magic[0] == 0x89 &&
                magic[1] == 'P' &&
                magic[2] == 'N' &&
                magic[3] == 'G') {
                is_PNG = true;
            }
        }
        SDL_SeekIO(src, آغاز, SDL_IO_SEEK_سیٹ);
    }

    واپس is_PNG;
}

SDL_Surface *SDL_بھرو_PNG_IO(SDL_IOStream *src, bool closeio)
{
    SDL_Surface *surface = تہی;

    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        جاؤ مکمل;
    }

    اگر (!SDL_IsPNG(src)) {
        SDL_سیٹ_Error("File is not a PNG file");
        جاؤ مکمل;
    }

#اگر_تعریف_شدہ SDL_HAVE_STB
    surface = SDL_بھرو_STB_IO(src);
#ورنہ
    SDL_سیٹ_Error("SDL not built with STB image support");
#اگر_ختم // SDL_HAVE_STB

مکمل:
    اگر (src && closeio) {
        SDL_CloseIO(src);
    }
    واپس surface;
}

SDL_Surface *SDL_بھرو_PNG(ثابت حرف *file)
{
    SDL_IOStream *دھارا = SDL_IOFromFile(file, "rb");
    اگر (!دھارا) {
        واپس تہی;
    }

    واپس SDL_بھرو_PNG_IO(دھارا, true);
}

bool SDL_SavePNG_IO(SDL_Surface *surface, SDL_IOStream *dst, bool closeio)
{
    bool retval = false;
    Uint8 *plte = تہی;
    Uint8 *trns = تہی;
    bool free_surface = false;

    // Make sure we have something to save
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        جاؤ مکمل;
    }
    CHECK_PARAM(!dst) {
        SDL_InvalidParamError("dst");
        جاؤ مکمل;
    }

#اگر_تعریف_شدہ SDL_HAVE_STB
    صحیح plte_سائز = 0;
    صحیح trns_سائز = 0;

    اگر (SDL_ISPIXELFORMAT_اشاریہ_دار(surface->format)) {
        اگر (!surface->palette) {
            SDL_سیٹ_Error("Indexed surfaces must have a palette");
            جاؤ مکمل;
        }

        اگر (surface->format != SDL_PIXELFORMAT_INDEX8) {
            surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_INDEX8);
            اگر (!surface) {
                جاؤ مکمل;
            }
            free_surface = true;
        }

        plte_سائز = surface->palette->ncolors * 3;
        trns_سائز = surface->palette->ncolors;
        plte = (Uint8 *)SDL_malloc(plte_سائز);
        trns = (Uint8 *)SDL_malloc(trns_سائز);
        اگر (!plte || !trns) {
            جاؤ مکمل;
        }
        SDL_Color *colors = surface->palette->colors;
        برائے (صحیح i = 0; i < surface->palette->ncolors; ++i) {
            plte[i * 3 + 0] = colors[i].r;
            plte[i * 3 + 1] = colors[i].g;
            plte[i * 3 + 2] = colors[i].b;
            trns[i] = colors[i].a;
        }
    } ورنہ {
        اگر (surface->format != SDL_PIXELFORMAT_RGBA32) {
            surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);
            اگر (!surface) {
                جاؤ مکمل;
            }
            free_surface = true;
        }
    }

    size_t سائز = 0;
    خالی *png = tdefl_write_image_مقصد_png_file_اندر_حافظہ_ex(surface->pixels, surface->w, surface->h, SDL_BYTESPERPIXEL(surface->format), surface->pitch, &سائز, 6, MZ_FALSE, plte, plte_سائز, trns, trns_سائز);
    اگر (png) {
        اگر (SDL_WriteIO(dst, png, سائز)) {
            retval = true;
        }
        mz_free(png); /* calls SDL_free() */
    } ورنہ {
        SDL_سیٹ_Error("Failed to convert and save image");
    }

#ورنہ
    SDL_سیٹ_Error("SDL not built with STB image support");
#اگر_ختم

مکمل:
    اگر (free_surface) {
        SDL_DestroySurface(surface);
    }
    SDL_free(plte);
    SDL_free(trns);

    اگر (dst && closeio) {
        retval &= SDL_CloseIO(dst);
    }
    واپس retval;
}

bool SDL_SavePNG(SDL_Surface *surface, ثابت حرف *file)
{
#اگر_تعریف_شدہ SDL_HAVE_STB
    // Make sure we have something to save
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        واپس SDL_InvalidParamError("surface");
    }

    اگر (SDL_ISPIXELFORMAT_اشاریہ_دار(surface->format) && !surface->palette) {
        واپس SDL_سیٹ_Error("Indexed surfaces must have a palette");
    }
    SDL_IOStream *دھارا = SDL_IOFromFile(file, "wb");
    اگر (!دھارا) {
        واپس false;
    }

    واپس SDL_SavePNG_IO(surface, دھارا, true);
#ورنہ
    واپس SDL_سیٹ_Error("SDL not built with STB image support");
#اگر_ختم
}
