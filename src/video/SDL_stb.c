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
#اگر_تعریف_نشده SDL_DISABLE_STB
#تعریف_کن SDL_HAVE_STB
#پایان_اگر

#اگر_تعریف_شده SDL_HAVE_STB
////////////////////////////////////////////////////////////////////////////
#تعریف_کن حافظه_بده SDL_malloc
#تعریف_کن realloc SDL_realloc
#تعریف_کن حرر SDL_free
#لغو_تعریف کپی_حافظه
#تعریف_کن کپی_حافظه SDL_memcpy
#لغو_تعریف memset
#تعریف_کن memset SDL_memset
#لغو_تعریف strcmp
#تعریف_کن strcmp SDL_strcmp
#لغو_تعریف مقایسه_رشته
#تعریف_کن مقایسه_رشته SDL_strncmp
#تعریف_کن strtol SDL_strtol

#تعریف_کن قدر_مطلق SDL_abs
#تعریف_کن توان SDL_pow
#تعریف_کن ldexp SDL_scalbn

#تعریف_کن STB_IMAGE_STATIC
#تعریف_کن STBI_NO_THREAD_LOCALS
#تعریف_کن STBI_FAILURE_USERMSG
#إذا defined(SDL_NEON_INTRINSICS)
#تعریف_کن STBI_NEON
#پایان_اگر
#تعریف_کن STBI_ONLY_PNG
#تعریف_کن STBI_ONLY_JPEG
#تعریف_کن STBI_NO_GIF
#تعریف_کن STBI_NO_HDR
#تعریف_کن STBI_NO_خطی
#تعریف_کن STBI_NO_STDIO
#تعریف_کن STBI_ASSERT SDL_assert
#تعریف_کن STB_IMAGE_IMPLEMENTATION
#ضمن "stb_image.h"

////////////////////////////////////////////////////////////////////////////
#تعریف_کن MZ_ASSERT(x) SDL_assert(x)
//#undef memcpy
//#define memcpy SDL_memcpy
//#undef memset
//#define memset SDL_memset
#إذا SDL_BYTEORDER == SDL_LIL_ENDIAN
#تعریف_کن MINIZ_LITTLE_ENDIAN 1
#وإلا
#تعریف_کن MINIZ_LITTLE_ENDIAN 0
#پایان_اگر
#تعریف_کن MINIZ_USE_UNALIGNED_LOADS_AND_STORES 0
#تعریف_کن MINIZ_SDL_NOUNUSED
#ضمن "miniz.h"

#لغو_تعریف memset
#پایان_اگر // SDL_HAVE_STB

#اگر_تعریف_شده SDL_HAVE_STB
ساكن bool SDL_Convert_Pixels_MJPG_مقصد_NV12(صحيح عرض, صحيح ارتفاع, ثابت فراغ *src, صحيح src_pitch, فراغ *dst, صحيح dst_pitch)
{
    صحيح w = 0, h = 0, format = 0;
    stbi__context s;
    stbi_شروع_mem(&s, src, src_pitch);

    stbi_نتیجه_info ri;
    SDL_zero(ri);
    ri.بیتها_در_هر_channel = 8;
    ri.channel_ترتیب = STBI_ترتیب_RGB;
    ri.رقم_channels = 0;

    stbi__nv12 nv12;
    nv12.w = عرض;
    nv12.h = ارتفاع;
    nv12.pitch = dst_pitch;
    nv12.y = (stbi_uc *)dst;
    nv12.uv = nv12.y + (nv12.h * nv12.pitch);

    فراغ *pixels = stbi_jpeg_بارگیری(&s, &w, &h, &format, 4, &nv12, &ri);
    إذا (!pixels) {
        أرجع false;
    }
    أرجع true;
}
#پایان_اگر // SDL_HAVE_STB

bool SDL_ConvertPixels_STB(صحيح عرض, صحيح ارتفاع,
                           SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ثابت فراغ *src, صحيح src_pitch,
                           SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, فراغ *dst, صحيح dst_pitch)
{
#اگر_تعریف_شده SDL_HAVE_STB
    إذا (src_format == SDL_PIXELFORMAT_MJPG) {
        إذا (dst_format == SDL_PIXELFORMAT_NV12) {
            أرجع SDL_Convert_Pixels_MJPG_مقصد_NV12(عرض, ارتفاع, src, src_pitch, dst, dst_pitch);
        } وإلا إذا (
            dst_format == SDL_PIXELFORMAT_YV12 ||
            dst_format == SDL_PIXELFORMAT_IYUV ||
            dst_format == SDL_PIXELFORMAT_YUY2 ||
            dst_format == SDL_PIXELFORMAT_UYVY ||
            dst_format == SDL_PIXELFORMAT_YVYU ||
            dst_format == SDL_PIXELFORMAT_NV21 ||
            dst_format == SDL_PIXELFORMAT_P010
        ) {
            size_t موقت_اندازه = 0;
            size_t موقت_pitch = 0;
            إذا (!SDL_CalculateYUVSize(dst_format, عرض, ارتفاع, &موقت_اندازه, &موقت_pitch)) {
                أرجع false;
            }
            فراغ *موقت_pixels = SDL_malloc(موقت_اندازه);
            إذا (!موقت_pixels) {
                أرجع false;
            }

            إذا (!SDL_Convert_Pixels_MJPG_مقصد_NV12(عرض, ارتفاع, src, src_pitch, موقت_pixels, (صحيح)موقت_pitch)) {
                SDL_free(موقت_pixels);
                أرجع false;
            }

            bool نتیجه = SDL_ConvertPixelsAndColorspace(عرض, ارتفاع, SDL_PIXELFORMAT_NV12, src_colorspace, 0 /*props*/, موقت_pixels, (صحيح)موقت_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
            SDL_free(موقت_pixels);
            أرجع نتیجه;
        }
    }

    bool نتیجه;
    صحيح w = 0, h = 0, format = 0;
    صحيح len = (src_format == SDL_PIXELFORMAT_MJPG) ? src_pitch : (ارتفاع * src_pitch);
    فراغ *pixels = stbi_بارگیری_from_حافظه(src, len, &w, &h, &format, 4);
    إذا (!pixels) {
        أرجع false;
    }

    إذا (w == عرض && h == ارتفاع) {
        نتیجه = SDL_ConvertPixelsAndColorspace(w, h, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, pixels, عرض * 4, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } وإلا {
        نتیجه = SDL_مجموعه_Error("Expected image size %dx%d, actual size %dx%d", عرض, ارتفاع, w, h);
    }
    stbi_image_free(pixels);

    أرجع نتیجه;
#وإلا
    أرجع SDL_مجموعه_Error("SDL not built with STB image support");
#پایان_اگر
}

#اگر_تعریف_شده SDL_HAVE_STB
ساكن صحيح IMG_بارگیری_STB_IO_read(فراغ *user, حرف *داده, صحيح اندازه)
{
    size_t amount = SDL_ReadIO((SDL_IOStream*)user, داده, اندازه);
    أرجع (صحيح)amount;
}

ساكن فراغ IMG_بارگیری_STB_IO_skip(فراغ *user, صحيح n)
{
    SDL_SeekIO((SDL_IOStream*)user, n, SDL_IO_SEEK_CUR);
}

ساكن صحيح IMG_بارگیری_STB_IO_eof(فراغ *user)
{
    SDL_IOStream *src = (SDL_IOStream*)user;
    أرجع SDL_GetIOStatus(src) == SDL_IO_وضعیت_EOF;
}

ساكن SDL_Surface *SDL_بارگیری_STB_IO(SDL_IOStream *src)
{
    Sint64 شروع;
    Uint8 magic[26];
    صحيح w, h, format;
    stbi_uc *pixels;
    stbi_io_callbacks rw_callbacks;
    SDL_Surface *surface = عدم;
    bool use_palette = false;
    بیعلامت صحيح palette_colors[256];

    // src has already been validated
    شروع = SDL_TellIO(src);

    إذا (SDL_ReadIO(src, magic, حجم(magic)) == حجم(magic)) {
        ثابت Uint8 PNG_COLOR_نمایهای = 3;
        إذا (magic[0] == 0x89 &&
            magic[1] == 'P' &&
            magic[2] == 'N' &&
            magic[3] == 'G' &&
            magic[12] == 'I' &&
            magic[13] == 'H' &&
            magic[14] == 'D' &&
            magic[15] == 'R' &&
            magic[25] == PNG_COLOR_نمایهای) {
            use_palette = true;
        }
    }
    SDL_SeekIO(src, شروع, SDL_IO_SEEK_مجموعه);

    /* Load the image data */
    rw_callbacks.اقرأ = IMG_بارگیری_STB_IO_read;
    rw_callbacks.skip = IMG_بارگیری_STB_IO_skip;
    rw_callbacks.eof = IMG_بارگیری_STB_IO_eof;
    w = h = format = 0; /* silence warning */
    إذا (use_palette) {
        /* Unused palette entries will be opaque white */
        SDL_memset(palette_colors, 0xff, حجم(palette_colors));

        pixels = stbi_بارگیری_from_callbacks_with_palette(
            &rw_callbacks,
            src,
            &w,
            &h,
            palette_colors,
            SDL_arraysize(palette_colors)
        );
    } وإلا {
        pixels = stbi_بارگیری_from_callbacks(
            &rw_callbacks,
            src,
            &w,
            &h,
            &format,
            STBI_default
        );
    }
    إذا (!pixels) {
        SDL_SeekIO(src, شروع, SDL_IO_SEEK_مجموعه);
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
            صحيح colorkey_شاخص = -1;
            bool has_alpha = false;
            SDL_Palette *palette = SDL_CreateSurfacePalette(surface);
            إذا (palette) {
                صحيح i;
                Uint8 *palette_بایتها = (Uint8 *)palette_colors;

                لكل (i = 0; i < palette->ncolors; i++) {
                    palette->colors[i].r = *palette_بایتها++;
                    palette->colors[i].g = *palette_بایتها++;
                    palette->colors[i].b = *palette_بایتها++;
                    palette->colors[i].a = *palette_بایتها++;
                    إذا (palette->colors[i].a != SDL_ALPHA_OPAQUE) {
                        إذا (palette->colors[i].a == SDL_ALPHA_TRANSPARENT && !has_colorkey) {
                            has_colorkey = true;
                            colorkey_شاخص = i;
                        } وإلا {
                            /* Partial opacity or multiple colorkeys */
                            has_alpha = true;
                        }
                    }
                }
            }
            إذا (has_alpha) {
                SDL_مجموعه_Surface_Blend_نما(surface, SDL_BLENDMODE_BLEND);
            } وإلا إذا (has_colorkey) {
                SDL_مجموعه_Surface_Color_کلید(surface, true, colorkey_شاخص);
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
            صحيح ردیف, ستون;

            لكل (ردیف = 0; ردیف < h; ++ردیف) {
                لكل (ستون = 0; ستون < w; ++ستون) {
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
        SDL_مجموعه_Error("Unknown image format: %d", format);
    }

    إذا (!surface) {
        /* The error message should already be set */
        stbi_image_free(pixels); /* calls SDL_free() */
        SDL_SeekIO(src, شروع, SDL_IO_SEEK_مجموعه);
    }
    أرجع surface;
}
#پایان_اگر // SDL_HAVE_STB

/* FIXME: This is a copypaste from JPEGLIB! Pull that out of the ifdefs */
/* Define this for quicker (but less perfect) JPEG identification */
#تعریف_کن FAST_IS_JPEG

/* See if an image is contained in a data source */
bool SDL_IsJPG(SDL_IOStream *src)
{
    Sint64 شروع;
    bool is_JPG;
    bool درون_پیمایش;
    Uint8 magic[4];

    /* This detection code is by Steaphan Greene <stea@cs.binghamton.edu> */
    /* Blame me, not Sam, if this doesn't work right. */
    /* And don't forget to report the problem to the the sdl list too! */

    إذا (!src) {
        أرجع false;
    }

    شروع = SDL_TellIO(src);
    is_JPG = false;
    درون_پیمایش = false;
    إذا (SDL_ReadIO(src, magic, 2) == 2) {
        إذا ( (magic[0] == 0xFF) && (magic[1] == 0xD8) ) {
            is_JPG = true;
            طالما (is_JPG) {
                إذا (SDL_ReadIO(src, magic, 2) != 2) {
                    is_JPG = false;
                } وإلا إذا ( (magic[0] != 0xFF) && !درون_پیمایش ) {
                    is_JPG = false;
                } وإلا إذا ( (magic[0] != 0xFF) || (magic[1] == 0xFF) ) {
                    /* Extra padding in JPEG (legal) */
                    /* or this is data and we are scanning */
                    SDL_SeekIO(src, -1, SDL_IO_SEEK_CUR);
                } وإلا إذا (magic[1] == 0xD9) {
                    /* Got to end of good JPEG */
                    اكسر;
                } وإلا إذا ( درون_پیمایش && (magic[1] == 0x00) ) {
                    /* This is an encoded 0xFF within the data */
                } وإلا إذا ( (magic[1] >= 0xD0) && (magic[1] < 0xD9) ) {
                    /* These have nothing else */
                } وإلا إذا (SDL_ReadIO(src, magic+2, 2) != 2) {
                    is_JPG = false;
                } وإلا {
                    /* Yes, it's big-endian */
                    Sint64 inner_شروع;
                    Uint32 اندازه;
                    Sint64 انتها;
                    inner_شروع = SDL_TellIO(src);
                    اندازه = (magic[2] << 8) + magic[3];
                    انتها = SDL_SeekIO(src, اندازه-2, SDL_IO_SEEK_CUR);
                    إذا ( انتها != inner_شروع + اندازه - 2 ) {
                        is_JPG = false;
                    }
                    إذا ( magic[1] == 0xDA ) {
                        /* Now comes the actual JPEG meat */
#اگر_تعریف_شده  FAST_IS_JPEG
                        /* Ok, I'm convinced.  It is a JPEG. */
                        اكسر;
#وإلا
                        /* I'm not convinced.  Prove it! */
                        درون_پیمایش = true;
#پایان_اگر
                    }
                }
            }
        }
    }
    SDL_SeekIO(src, شروع, SDL_IO_SEEK_مجموعه);
    أرجع is_JPG;
}

SDL_Surface *SDL_بارگیری_JPG_IO(SDL_IOStream *src, bool closeio)
{
    SDL_Surface *surface = عدم;

    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        اذهب انجامشده;
    }

    إذا (!SDL_IsJPG(src)) {
        SDL_مجموعه_Error("File is not a JPEG file");
        اذهب انجامشده;
    }

#اگر_تعریف_شده SDL_HAVE_STB
    surface = SDL_بارگیری_STB_IO(src);
#وإلا
    SDL_مجموعه_Error("SDL not built with STB image support");
#پایان_اگر // SDL_HAVE_STB

انجامشده:
    إذا (src && closeio) {
        SDL_CloseIO(src);
    }
    أرجع surface;
}

SDL_Surface *SDL_بارگیری_JPG(ثابت حرف *file)
{
    SDL_IOStream *جریان = SDL_IOFromFile(file, "rb");
    إذا (!جریان) {
        أرجع عدم;
    }

    أرجع SDL_بارگیری_JPG_IO(جریان, true);
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
        SDL_SeekIO(src, شروع, SDL_IO_SEEK_مجموعه);
    }

    أرجع is_PNG;
}

SDL_Surface *SDL_بارگیری_PNG_IO(SDL_IOStream *src, bool closeio)
{
    SDL_Surface *surface = عدم;

    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        اذهب انجامشده;
    }

    إذا (!SDL_IsPNG(src)) {
        SDL_مجموعه_Error("File is not a PNG file");
        اذهب انجامشده;
    }

#اگر_تعریف_شده SDL_HAVE_STB
    surface = SDL_بارگیری_STB_IO(src);
#وإلا
    SDL_مجموعه_Error("SDL not built with STB image support");
#پایان_اگر // SDL_HAVE_STB

انجامشده:
    إذا (src && closeio) {
        SDL_CloseIO(src);
    }
    أرجع surface;
}

SDL_Surface *SDL_بارگیری_PNG(ثابت حرف *file)
{
    SDL_IOStream *جریان = SDL_IOFromFile(file, "rb");
    إذا (!جریان) {
        أرجع عدم;
    }

    أرجع SDL_بارگیری_PNG_IO(جریان, true);
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
        اذهب انجامشده;
    }
    CHECK_PARAM(!dst) {
        SDL_InvalidParamError("dst");
        اذهب انجامشده;
    }

#اگر_تعریف_شده SDL_HAVE_STB
    صحيح plte_اندازه = 0;
    صحيح trns_اندازه = 0;

    إذا (SDL_ISPIXELFORMAT_نمایهای(surface->format)) {
        إذا (!surface->palette) {
            SDL_مجموعه_Error("Indexed surfaces must have a palette");
            اذهب انجامشده;
        }

        إذا (surface->format != SDL_PIXELFORMAT_INDEX8) {
            surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_INDEX8);
            إذا (!surface) {
                اذهب انجامشده;
            }
            free_surface = true;
        }

        plte_اندازه = surface->palette->ncolors * 3;
        trns_اندازه = surface->palette->ncolors;
        plte = (Uint8 *)SDL_malloc(plte_اندازه);
        trns = (Uint8 *)SDL_malloc(trns_اندازه);
        إذا (!plte || !trns) {
            اذهب انجامشده;
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
                اذهب انجامشده;
            }
            free_surface = true;
        }
    }

    size_t اندازه = 0;
    فراغ *png = tdefl_write_image_مقصد_png_file_درون_حافظه_ex(surface->pixels, surface->w, surface->h, SDL_BYTESPERPIXEL(surface->format), surface->pitch, &اندازه, 6, MZ_FALSE, plte, plte_اندازه, trns, trns_اندازه);
    إذا (png) {
        إذا (SDL_WriteIO(dst, png, اندازه)) {
            retval = true;
        }
        mz_free(png); /* calls SDL_free() */
    } وإلا {
        SDL_مجموعه_Error("Failed to convert and save image");
    }

#وإلا
    SDL_مجموعه_Error("SDL not built with STB image support");
#پایان_اگر

انجامشده:
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
#اگر_تعریف_شده SDL_HAVE_STB
    // Make sure we have something to save
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        أرجع SDL_InvalidParamError("surface");
    }

    إذا (SDL_ISPIXELFORMAT_نمایهای(surface->format) && !surface->palette) {
        أرجع SDL_مجموعه_Error("Indexed surfaces must have a palette");
    }
    SDL_IOStream *جریان = SDL_IOFromFile(file, "wb");
    إذا (!جریان) {
        أرجع false;
    }

    أرجع SDL_SavePNG_IO(surface, جریان, true);
#وإلا
    أرجع SDL_مجموعه_Error("SDL not built with STB image support");
#پایان_اگر
}
