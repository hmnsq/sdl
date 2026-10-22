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
#جے_بنا_تعریف SDL_DISABLE_STB
#تعریف_کرو SDL_HAVE_STB
#جے_انت

#جے_تعریف_شدہ SDL_HAVE_STB
////////////////////////////////////////////////////////////////////////////
#تعریف_کرو حافظہ_دیو SDL_malloc
#تعریف_کرو realloc SDL_realloc
#تعریف_کرو حرر SDL_free
#تعریف_رد حافظہ_نقل
#تعریف_کرو حافظہ_نقل SDL_memcpy
#تعریف_رد memset
#تعریف_کرو memset SDL_memset
#تعریف_رد strcmp
#تعریف_کرو strcmp SDL_strcmp
#تعریف_رد لڑی_مقابلہ
#تعریف_کرو لڑی_مقابلہ SDL_strncmp
#تعریف_کرو strtol SDL_strtol

#تعریف_کرو مطلق_قدر SDL_abs
#تعریف_کرو قوت SDL_pow
#تعریف_کرو ldexp SDL_scalbn

#تعریف_کرو STB_IMAGE_STATIC
#تعریف_کرو STBI_NO_THREAD_LOCALS
#تعریف_کرو STBI_FAILURE_USERMSG
#إذا defined(SDL_NEON_INTRINSICS)
#تعریف_کرو STBI_NEON
#جے_انت
#تعریف_کرو STBI_ONLY_PNG
#تعریف_کرو STBI_ONLY_JPEG
#تعریف_کرو STBI_NO_GIF
#تعریف_کرو STBI_NO_HDR
#تعریف_کرو STBI_NO_خطی
#تعریف_کرو STBI_NO_STDIO
#تعریف_کرو STBI_ASSERT SDL_assert
#تعریف_کرو STB_IMAGE_IMPLEMENTATION
#ضمن "stb_image.h"

////////////////////////////////////////////////////////////////////////////
#تعریف_کرو MZ_ASSERT(x) SDL_assert(x)
//#undef memcpy
//#define memcpy SDL_memcpy
//#undef memset
//#define memset SDL_memset
#إذا SDL_BYTEORDER == SDL_LIL_ENDIAN
#تعریف_کرو MINIZ_LITTLE_ENDIAN 1
#وإلا
#تعریف_کرو MINIZ_LITTLE_ENDIAN 0
#جے_انت
#تعریف_کرو MINIZ_USE_UNALIGNED_LOADS_AND_STORES 0
#تعریف_کرو MINIZ_SDL_NOUNUSED
#ضمن "miniz.h"

#تعریف_رد memset
#جے_انت // SDL_HAVE_STB

#جے_تعریف_شدہ SDL_HAVE_STB
ساكن bool SDL_Convert_Pixels_MJPG_منزل_NV12(صحيح چوڑائی, صحيح اچائی, ثابت فراغ *src, صحيح src_pitch, فراغ *dst, صحيح dst_pitch)
{
    صحيح w = 0, h = 0, format = 0;
    stbi__context s;
    stbi_شروع_mem(&s, src, src_pitch);

    stbi_نتیجہ_info ri;
    SDL_zero(ri);
    ri.بٹ_فی_channel = 8;
    ri.channel_ترتیب = STBI_ترتیب_RGB;
    ri.عدد_channels = 0;

    stbi__nv12 nv12;
    nv12.w = چوڑائی;
    nv12.h = اچائی;
    nv12.pitch = dst_pitch;
    nv12.y = (stbi_uc *)dst;
    nv12.uv = nv12.y + (nv12.h * nv12.pitch);

    فراغ *pixels = stbi_jpeg_لدو(&s, &w, &h, &format, 4, &nv12, &ri);
    إذا (!pixels) {
        أرجع false;
    }
    أرجع true;
}
#جے_انت // SDL_HAVE_STB

bool SDL_ConvertPixels_STB(صحيح چوڑائی, صحيح اچائی,
                           SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ثابت فراغ *src, صحيح src_pitch,
                           SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, فراغ *dst, صحيح dst_pitch)
{
#جے_تعریف_شدہ SDL_HAVE_STB
    إذا (src_format == SDL_PIXELFORMAT_MJPG) {
        إذا (dst_format == SDL_PIXELFORMAT_NV12) {
            أرجع SDL_Convert_Pixels_MJPG_منزل_NV12(چوڑائی, اچائی, src, src_pitch, dst, dst_pitch);
        } وإلا إذا (
            dst_format == SDL_PIXELFORMAT_YV12 ||
            dst_format == SDL_PIXELFORMAT_IYUV ||
            dst_format == SDL_PIXELFORMAT_YUY2 ||
            dst_format == SDL_PIXELFORMAT_UYVY ||
            dst_format == SDL_PIXELFORMAT_YVYU ||
            dst_format == SDL_PIXELFORMAT_NV21 ||
            dst_format == SDL_PIXELFORMAT_P010
        ) {
            size_t عارضی_ناپ = 0;
            size_t عارضی_pitch = 0;
            إذا (!SDL_CalculateYUVSize(dst_format, چوڑائی, اچائی, &عارضی_ناپ, &عارضی_pitch)) {
                أرجع false;
            }
            فراغ *عارضی_pixels = SDL_malloc(عارضی_ناپ);
            إذا (!عارضی_pixels) {
                أرجع false;
            }

            إذا (!SDL_Convert_Pixels_MJPG_منزل_NV12(چوڑائی, اچائی, src, src_pitch, عارضی_pixels, (صحيح)عارضی_pitch)) {
                SDL_free(عارضی_pixels);
                أرجع false;
            }

            bool نتیجہ = SDL_ConvertPixelsAndColorspace(چوڑائی, اچائی, SDL_PIXELFORMAT_NV12, src_colorspace, 0 /*props*/, عارضی_pixels, (صحيح)عارضی_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
            SDL_free(عارضی_pixels);
            أرجع نتیجہ;
        }
    }

    bool نتیجہ;
    صحيح w = 0, h = 0, format = 0;
    صحيح len = (src_format == SDL_PIXELFORMAT_MJPG) ? src_pitch : (اچائی * src_pitch);
    فراغ *pixels = stbi_لدو_from_حافظہ(src, len, &w, &h, &format, 4);
    إذا (!pixels) {
        أرجع false;
    }

    إذا (w == چوڑائی && h == اچائی) {
        نتیجہ = SDL_ConvertPixelsAndColorspace(w, h, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, pixels, چوڑائی * 4, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } وإلا {
        نتیجہ = SDL_سیٹ_Error("Expected image size %dx%d, actual size %dx%d", چوڑائی, اچائی, w, h);
    }
    stbi_image_free(pixels);

    أرجع نتیجہ;
#وإلا
    أرجع SDL_سیٹ_Error("SDL not built with STB image support");
#جے_انت
}

#جے_تعریف_شدہ SDL_HAVE_STB
ساكن صحيح IMG_لدو_STB_IO_read(فراغ *user, حرف *انکڑے, صحيح ناپ)
{
    size_t amount = SDL_ReadIO((SDL_IOStream*)user, انکڑے, ناپ);
    أرجع (صحيح)amount;
}

ساكن فراغ IMG_لدو_STB_IO_skip(فراغ *user, صحيح n)
{
    SDL_SeekIO((SDL_IOStream*)user, n, SDL_IO_SEEK_CUR);
}

ساكن صحيح IMG_لدو_STB_IO_eof(فراغ *user)
{
    SDL_IOStream *src = (SDL_IOStream*)user;
    أرجع SDL_GetIOStatus(src) == SDL_IO_حالت_EOF;
}

ساكن SDL_Surface *SDL_لدو_STB_IO(SDL_IOStream *src)
{
    Sint64 شروع;
    Uint8 magic[26];
    صحيح w, h, format;
    stbi_uc *pixels;
    stbi_io_callbacks rw_callbacks;
    SDL_Surface *surface = عدم;
    bool use_palette = false;
    بنانشانی صحيح palette_colors[256];

    // src has already been validated
    شروع = SDL_TellIO(src);

    إذا (SDL_ReadIO(src, magic, حجم(magic)) == حجم(magic)) {
        ثابت Uint8 PNG_COLOR_اشاریہ_دار = 3;
        إذا (magic[0] == 0x89 &&
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
    SDL_SeekIO(src, شروع, SDL_IO_SEEK_سیٹ);

    /* Load the image data */
    rw_callbacks.اقرأ = IMG_لدو_STB_IO_read;
    rw_callbacks.skip = IMG_لدو_STB_IO_skip;
    rw_callbacks.eof = IMG_لدو_STB_IO_eof;
    w = h = format = 0; /* silence warning */
    إذا (use_palette) {
        /* Unused palette entries will be opaque white */
        SDL_memset(palette_colors, 0xff, حجم(palette_colors));

        pixels = stbi_لدو_from_callbacks_with_palette(
            &rw_callbacks,
            src,
            &w,
            &h,
            palette_colors,
            SDL_arraysize(palette_colors)
        );
    } وإلا {
        pixels = stbi_لدو_from_callbacks(
            &rw_callbacks,
            src,
            &w,
            &h,
            &format,
            STBI_default
        );
    }
    إذا (!pixels) {
        SDL_SeekIO(src, شروع, SDL_IO_SEEK_سیٹ);
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
            صحيح colorkey_اشاریہ = -1;
            bool has_alpha = false;
            SDL_Palette *palette = SDL_CreateSurfacePalette(surface);
            إذا (palette) {
                صحيح i;
                Uint8 *palette_بائٹاں = (Uint8 *)palette_colors;

                لكل (i = 0; i < palette->ncolors; i++) {
                    palette->colors[i].r = *palette_بائٹاں++;
                    palette->colors[i].g = *palette_بائٹاں++;
                    palette->colors[i].b = *palette_بائٹاں++;
                    palette->colors[i].a = *palette_بائٹاں++;
                    إذا (palette->colors[i].a != SDL_ALPHA_OPAQUE) {
                        إذا (palette->colors[i].a == SDL_ALPHA_TRANSPARENT && !has_colorkey) {
                            has_colorkey = true;
                            colorkey_اشاریہ = i;
                        } وإلا {
                            /* Partial opacity or multiple colorkeys */
                            has_alpha = true;
                        }
                    }
                }
            }
            إذا (has_alpha) {
                SDL_سیٹ_Surface_Blend_منوال(surface, SDL_BLENDMODE_BLEND);
            } وإلا إذا (has_colorkey) {
                SDL_سیٹ_Surface_Color_کلید(surface, true, colorkey_اشاریہ);
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
            صحيح صف, خانہ;

            لكل (صف = 0; صف < h; ++صف) {
                لكل (خانہ = 0; خانہ < w; ++خانہ) {
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
        SDL_سیٹ_Error("Unknown image format: %d", format);
    }

    إذا (!surface) {
        /* The error message should already be set */
        stbi_image_free(pixels); /* calls SDL_free() */
        SDL_SeekIO(src, شروع, SDL_IO_SEEK_سیٹ);
    }
    أرجع surface;
}
#جے_انت // SDL_HAVE_STB

/* FIXME: This is a copypaste from JPEGLIB! Pull that out of the ifdefs */
/* Define this for quicker (but less perfect) JPEG identification */
#تعریف_کرو FAST_IS_JPEG

/* See if an image is contained in a data source */
bool SDL_IsJPG(SDL_IOStream *src)
{
    Sint64 شروع;
    bool is_JPG;
    bool وچ_جانچ;
    Uint8 magic[4];

    /* This detection code is by Steaphan Greene <stea@cs.binghamton.edu> */
    /* Blame me, not Sam, if this doesn't work right. */
    /* And don't forget to report the problem to the the sdl list too! */

    إذا (!src) {
        أرجع false;
    }

    شروع = SDL_TellIO(src);
    is_JPG = false;
    وچ_جانچ = false;
    إذا (SDL_ReadIO(src, magic, 2) == 2) {
        إذا ( (magic[0] == 0xFF) && (magic[1] == 0xD8) ) {
            is_JPG = true;
            طالما (is_JPG) {
                إذا (SDL_ReadIO(src, magic, 2) != 2) {
                    is_JPG = false;
                } وإلا إذا ( (magic[0] != 0xFF) && !وچ_جانچ ) {
                    is_JPG = false;
                } وإلا إذا ( (magic[0] != 0xFF) || (magic[1] == 0xFF) ) {
                    /* Extra padding in JPEG (legal) */
                    /* or this is data and we are scanning */
                    SDL_SeekIO(src, -1, SDL_IO_SEEK_CUR);
                } وإلا إذا (magic[1] == 0xD9) {
                    /* Got to end of good JPEG */
                    اكسر;
                } وإلا إذا ( وچ_جانچ && (magic[1] == 0x00) ) {
                    /* This is an encoded 0xFF within the data */
                } وإلا إذا ( (magic[1] >= 0xD0) && (magic[1] < 0xD9) ) {
                    /* These have nothing else */
                } وإلا إذا (SDL_ReadIO(src, magic+2, 2) != 2) {
                    is_JPG = false;
                } وإلا {
                    /* Yes, it's big-endian */
                    Sint64 inner_شروع;
                    Uint32 ناپ;
                    Sint64 سرا;
                    inner_شروع = SDL_TellIO(src);
                    ناپ = (magic[2] << 8) + magic[3];
                    سرا = SDL_SeekIO(src, ناپ-2, SDL_IO_SEEK_CUR);
                    إذا ( سرا != inner_شروع + ناپ - 2 ) {
                        is_JPG = false;
                    }
                    إذا ( magic[1] == 0xDA ) {
                        /* Now comes the actual JPEG meat */
#جے_تعریف_شدہ  FAST_IS_JPEG
                        /* Ok, I'm convinced.  It is a JPEG. */
                        اكسر;
#وإلا
                        /* I'm not convinced.  Prove it! */
                        وچ_جانچ = true;
#جے_انت
                    }
                }
            }
        }
    }
    SDL_SeekIO(src, شروع, SDL_IO_SEEK_سیٹ);
    أرجع is_JPG;
}

SDL_Surface *SDL_لدو_JPG_IO(SDL_IOStream *src, bool closeio)
{
    SDL_Surface *surface = عدم;

    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        اذهب پورا;
    }

    إذا (!SDL_IsJPG(src)) {
        SDL_سیٹ_Error("File is not a JPEG file");
        اذهب پورا;
    }

#جے_تعریف_شدہ SDL_HAVE_STB
    surface = SDL_لدو_STB_IO(src);
#وإلا
    SDL_سیٹ_Error("SDL not built with STB image support");
#جے_انت // SDL_HAVE_STB

پورا:
    إذا (src && closeio) {
        SDL_CloseIO(src);
    }
    أرجع surface;
}

SDL_Surface *SDL_لدو_JPG(ثابت حرف *file)
{
    SDL_IOStream *دھارا = SDL_IOFromFile(file, "rb");
    إذا (!دھارا) {
        أرجع عدم;
    }

    أرجع SDL_لدو_JPG_IO(دھارا, true);
}

bool SDL_IsPNG(SDL_IOStream *src)
{
    Sint64 شروع;
    Uint8 magic[4];
    bool is_PNG;

    is_PNG = false;
    شروع = SDL_TellIO(src);
    إذا (شروع >= 0) {
        إذا (SDL_ReadIO(src, magic, حجم(magic)) == حجم(magic)) {
            إذا (magic[0] == 0x89 &&
                magic[1] == 'P' &&
                magic[2] == 'N' &&
                magic[3] == 'G') {
                is_PNG = true;
            }
        }
        SDL_SeekIO(src, شروع, SDL_IO_SEEK_سیٹ);
    }

    أرجع is_PNG;
}

SDL_Surface *SDL_لدو_PNG_IO(SDL_IOStream *src, bool closeio)
{
    SDL_Surface *surface = عدم;

    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        اذهب پورا;
    }

    إذا (!SDL_IsPNG(src)) {
        SDL_سیٹ_Error("File is not a PNG file");
        اذهب پورا;
    }

#جے_تعریف_شدہ SDL_HAVE_STB
    surface = SDL_لدو_STB_IO(src);
#وإلا
    SDL_سیٹ_Error("SDL not built with STB image support");
#جے_انت // SDL_HAVE_STB

پورا:
    إذا (src && closeio) {
        SDL_CloseIO(src);
    }
    أرجع surface;
}

SDL_Surface *SDL_لدو_PNG(ثابت حرف *file)
{
    SDL_IOStream *دھارا = SDL_IOFromFile(file, "rb");
    إذا (!دھارا) {
        أرجع عدم;
    }

    أرجع SDL_لدو_PNG_IO(دھارا, true);
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
        اذهب پورا;
    }
    CHECK_PARAM(!dst) {
        SDL_InvalidParamError("dst");
        اذهب پورا;
    }

#جے_تعریف_شدہ SDL_HAVE_STB
    صحيح plte_ناپ = 0;
    صحيح trns_ناپ = 0;

    إذا (SDL_ISPIXELFORMAT_اشاریہ_دار(surface->format)) {
        إذا (!surface->palette) {
            SDL_سیٹ_Error("Indexed surfaces must have a palette");
            اذهب پورا;
        }

        إذا (surface->format != SDL_PIXELFORMAT_INDEX8) {
            surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_INDEX8);
            إذا (!surface) {
                اذهب پورا;
            }
            free_surface = true;
        }

        plte_ناپ = surface->palette->ncolors * 3;
        trns_ناپ = surface->palette->ncolors;
        plte = (Uint8 *)SDL_malloc(plte_ناپ);
        trns = (Uint8 *)SDL_malloc(trns_ناپ);
        إذا (!plte || !trns) {
            اذهب پورا;
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
                اذهب پورا;
            }
            free_surface = true;
        }
    }

    size_t ناپ = 0;
    فراغ *png = tdefl_write_image_منزل_png_file_وچ_حافظہ_ex(surface->pixels, surface->w, surface->h, SDL_BYTESPERPIXEL(surface->format), surface->pitch, &ناپ, 6, MZ_FALSE, plte, plte_ناپ, trns, trns_ناپ);
    إذا (png) {
        إذا (SDL_WriteIO(dst, png, ناپ)) {
            retval = true;
        }
        mz_free(png); /* calls SDL_free() */
    } وإلا {
        SDL_سیٹ_Error("Failed to convert and save image");
    }

#وإلا
    SDL_سیٹ_Error("SDL not built with STB image support");
#جے_انت

پورا:
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
#جے_تعریف_شدہ SDL_HAVE_STB
    // Make sure we have something to save
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        أرجع SDL_InvalidParamError("surface");
    }

    إذا (SDL_ISPIXELFORMAT_اشاریہ_دار(surface->format) && !surface->palette) {
        أرجع SDL_سیٹ_Error("Indexed surfaces must have a palette");
    }
    SDL_IOStream *دھارا = SDL_IOFromFile(file, "wb");
    إذا (!دھارا) {
        أرجع false;
    }

    أرجع SDL_SavePNG_IO(surface, دھارا, true);
#وإلا
    أرجع SDL_سیٹ_Error("SDL not built with STB image support");
#جے_انت
}
