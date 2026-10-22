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
#جيڪڏهن_وصف_نه_ٿيل SDL_DISABLE_STB
#وصف_ڪريو SDL_HAVE_STB
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل SDL_HAVE_STB
////////////////////////////////////////////////////////////////////////////
#وصف_ڪريو يادگيري_ڏيو SDL_malloc
#وصف_ڪريو realloc SDL_realloc
#وصف_ڪريو حرر SDL_free
#وصف_رد يادگيري_نقل
#وصف_ڪريو يادگيري_نقل SDL_memcpy
#وصف_رد memset
#وصف_ڪريو memset SDL_memset
#وصف_رد strcmp
#وصف_ڪريو strcmp SDL_strcmp
#وصف_رد لڙي_ڀيٽ
#وصف_ڪريو لڙي_ڀيٽ SDL_strncmp
#وصف_ڪريو strtol SDL_strtol

#وصف_ڪريو مطلق_قدر SDL_abs
#وصف_ڪريو قوت SDL_pow
#وصف_ڪريو ldexp SDL_scalbn

#وصف_ڪريو STB_IMAGE_STATIC
#وصف_ڪريو STBI_NO_THREAD_LOCALS
#وصف_ڪريو STBI_FAILURE_USERMSG
#إذا defined(SDL_NEON_INTRINSICS)
#وصف_ڪريو STBI_NEON
#جيڪڏهن_پورو
#وصف_ڪريو STBI_ONLY_PNG
#وصف_ڪريو STBI_ONLY_JPEG
#وصف_ڪريو STBI_NO_GIF
#وصف_ڪريو STBI_NO_HDR
#وصف_ڪريو STBI_NO_لڪيري
#وصف_ڪريو STBI_NO_STDIO
#وصف_ڪريو STBI_ASSERT SDL_assert
#وصف_ڪريو STB_IMAGE_IMPLEMENTATION
#ضمن "stb_image.h"

////////////////////////////////////////////////////////////////////////////
#وصف_ڪريو MZ_ASSERT(x) SDL_assert(x)
//#undef memcpy
//#define memcpy SDL_memcpy
//#undef memset
//#define memset SDL_memset
#إذا SDL_BYTEORDER == SDL_LIL_ENDIAN
#وصف_ڪريو MINIZ_LITTLE_ENDIAN 1
#وإلا
#وصف_ڪريو MINIZ_LITTLE_ENDIAN 0
#جيڪڏهن_پورو
#وصف_ڪريو MINIZ_USE_UNALIGNED_LOADS_AND_STORES 0
#وصف_ڪريو MINIZ_SDL_NOUNUSED
#ضمن "miniz.h"

#وصف_رد memset
#جيڪڏهن_پورو // SDL_HAVE_STB

#جيڪڏهن_وصف_ٿيل SDL_HAVE_STB
ساكن bool SDL_Convert_Pixels_MJPG_منزل_NV12(صحيح ويڪر, صحيح اوچائي, ثابت فراغ *src, صحيح src_pitch, فراغ *dst, صحيح dst_pitch)
{
    صحيح w = 0, h = 0, format = 0;
    stbi__context s;
    stbi_شروعات_mem(&s, src, src_pitch);

    stbi_نتيجو_info ri;
    SDL_zero(ri);
    ri.بٽ_في_channel = 8;
    ri.channel_ترتيب = STBI_ترتيب_RGB;
    ri.انگ_channels = 0;

    stbi__nv12 nv12;
    nv12.w = ويڪر;
    nv12.h = اوچائي;
    nv12.pitch = dst_pitch;
    nv12.y = (stbi_uc *)dst;
    nv12.uv = nv12.y + (nv12.h * nv12.pitch);

    فراغ *pixels = stbi_jpeg_ڀريو(&s, &w, &h, &format, 4, &nv12, &ri);
    إذا (!pixels) {
        أرجع false;
    }
    أرجع true;
}
#جيڪڏهن_پورو // SDL_HAVE_STB

bool SDL_ConvertPixels_STB(صحيح ويڪر, صحيح اوچائي,
                           SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ثابت فراغ *src, صحيح src_pitch,
                           SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, فراغ *dst, صحيح dst_pitch)
{
#جيڪڏهن_وصف_ٿيل SDL_HAVE_STB
    إذا (src_format == SDL_PIXELFORMAT_MJPG) {
        إذا (dst_format == SDL_PIXELFORMAT_NV12) {
            أرجع SDL_Convert_Pixels_MJPG_منزل_NV12(ويڪر, اوچائي, src, src_pitch, dst, dst_pitch);
        } وإلا إذا (
            dst_format == SDL_PIXELFORMAT_YV12 ||
            dst_format == SDL_PIXELFORMAT_IYUV ||
            dst_format == SDL_PIXELFORMAT_YUY2 ||
            dst_format == SDL_PIXELFORMAT_UYVY ||
            dst_format == SDL_PIXELFORMAT_YVYU ||
            dst_format == SDL_PIXELFORMAT_NV21 ||
            dst_format == SDL_PIXELFORMAT_P010
        ) {
            size_t عارضي_سائيز = 0;
            size_t عارضي_pitch = 0;
            إذا (!SDL_CalculateYUVSize(dst_format, ويڪر, اوچائي, &عارضي_سائيز, &عارضي_pitch)) {
                أرجع false;
            }
            فراغ *عارضي_pixels = SDL_malloc(عارضي_سائيز);
            إذا (!عارضي_pixels) {
                أرجع false;
            }

            إذا (!SDL_Convert_Pixels_MJPG_منزل_NV12(ويڪر, اوچائي, src, src_pitch, عارضي_pixels, (صحيح)عارضي_pitch)) {
                SDL_free(عارضي_pixels);
                أرجع false;
            }

            bool نتيجو = SDL_ConvertPixelsAndColorspace(ويڪر, اوچائي, SDL_PIXELFORMAT_NV12, src_colorspace, 0 /*props*/, عارضي_pixels, (صحيح)عارضي_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
            SDL_free(عارضي_pixels);
            أرجع نتيجو;
        }
    }

    bool نتيجو;
    صحيح w = 0, h = 0, format = 0;
    صحيح len = (src_format == SDL_PIXELFORMAT_MJPG) ? src_pitch : (اوچائي * src_pitch);
    فراغ *pixels = stbi_ڀريو_from_يادگيري(src, len, &w, &h, &format, 4);
    إذا (!pixels) {
        أرجع false;
    }

    إذا (w == ويڪر && h == اوچائي) {
        نتيجو = SDL_ConvertPixelsAndColorspace(w, h, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, pixels, ويڪر * 4, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } وإلا {
        نتيجو = SDL_سيٽ_Error("Expected image size %dx%d, actual size %dx%d", ويڪر, اوچائي, w, h);
    }
    stbi_image_free(pixels);

    أرجع نتيجو;
#وإلا
    أرجع SDL_سيٽ_Error("SDL not built with STB image support");
#جيڪڏهن_پورو
}

#جيڪڏهن_وصف_ٿيل SDL_HAVE_STB
ساكن صحيح IMG_ڀريو_STB_IO_read(فراغ *user, حرف *معلومات, صحيح سائيز)
{
    size_t amount = SDL_ReadIO((SDL_IOStream*)user, معلومات, سائيز);
    أرجع (صحيح)amount;
}

ساكن فراغ IMG_ڀريو_STB_IO_skip(فراغ *user, صحيح n)
{
    SDL_SeekIO((SDL_IOStream*)user, n, SDL_IO_SEEK_CUR);
}

ساكن صحيح IMG_ڀريو_STB_IO_eof(فراغ *user)
{
    SDL_IOStream *src = (SDL_IOStream*)user;
    أرجع SDL_GetIOStatus(src) == SDL_IO_حالت_EOF;
}

ساكن SDL_Surface *SDL_ڀريو_STB_IO(SDL_IOStream *src)
{
    Sint64 شروعات;
    Uint8 magic[26];
    صحيح w, h, format;
    stbi_uc *pixels;
    stbi_io_callbacks rw_callbacks;
    SDL_Surface *surface = عدم;
    bool use_palette = false;
    بنانشان صحيح palette_colors[256];

    // src has already been validated
    شروعات = SDL_TellIO(src);

    إذا (SDL_ReadIO(src, magic, حجم(magic)) == حجم(magic)) {
        ثابت Uint8 PNG_COLOR_اشاريي_وارو = 3;
        إذا (magic[0] == 0x89 &&
            magic[1] == 'P' &&
            magic[2] == 'N' &&
            magic[3] == 'G' &&
            magic[12] == 'I' &&
            magic[13] == 'H' &&
            magic[14] == 'D' &&
            magic[15] == 'R' &&
            magic[25] == PNG_COLOR_اشاريي_وارو) {
            use_palette = true;
        }
    }
    SDL_SeekIO(src, شروعات, SDL_IO_SEEK_سيٽ);

    /* Load the image data */
    rw_callbacks.اقرأ = IMG_ڀريو_STB_IO_read;
    rw_callbacks.skip = IMG_ڀريو_STB_IO_skip;
    rw_callbacks.eof = IMG_ڀريو_STB_IO_eof;
    w = h = format = 0; /* silence warning */
    إذا (use_palette) {
        /* Unused palette entries will be opaque white */
        SDL_memset(palette_colors, 0xff, حجم(palette_colors));

        pixels = stbi_ڀريو_from_callbacks_with_palette(
            &rw_callbacks,
            src,
            &w,
            &h,
            palette_colors,
            SDL_arraysize(palette_colors)
        );
    } وإلا {
        pixels = stbi_ڀريو_from_callbacks(
            &rw_callbacks,
            src,
            &w,
            &h,
            &format,
            STBI_default
        );
    }
    إذا (!pixels) {
        SDL_SeekIO(src, شروعات, SDL_IO_SEEK_سيٽ);
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
            صحيح colorkey_اشاريو = -1;
            bool has_alpha = false;
            SDL_Palette *palette = SDL_CreateSurfacePalette(surface);
            إذا (palette) {
                صحيح i;
                Uint8 *palette_بائيٽون = (Uint8 *)palette_colors;

                لكل (i = 0; i < palette->ncolors; i++) {
                    palette->colors[i].r = *palette_بائيٽون++;
                    palette->colors[i].g = *palette_بائيٽون++;
                    palette->colors[i].b = *palette_بائيٽون++;
                    palette->colors[i].a = *palette_بائيٽون++;
                    إذا (palette->colors[i].a != SDL_ALPHA_OPAQUE) {
                        إذا (palette->colors[i].a == SDL_ALPHA_TRANSPARENT && !has_colorkey) {
                            has_colorkey = true;
                            colorkey_اشاريو = i;
                        } وإلا {
                            /* Partial opacity or multiple colorkeys */
                            has_alpha = true;
                        }
                    }
                }
            }
            إذا (has_alpha) {
                SDL_سيٽ_Surface_Blend_گهڻائي(surface, SDL_BLENDMODE_BLEND);
            } وإلا إذا (has_colorkey) {
                SDL_سيٽ_Surface_Color_ڪنجي(surface, true, colorkey_اشاريو);
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
            صحيح صف, کانو;

            لكل (صف = 0; صف < h; ++صف) {
                لكل (کانو = 0; کانو < w; ++کانو) {
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
        SDL_سيٽ_Error("Unknown image format: %d", format);
    }

    إذا (!surface) {
        /* The error message should already be set */
        stbi_image_free(pixels); /* calls SDL_free() */
        SDL_SeekIO(src, شروعات, SDL_IO_SEEK_سيٽ);
    }
    أرجع surface;
}
#جيڪڏهن_پورو // SDL_HAVE_STB

/* FIXME: This is a copypaste from JPEGLIB! Pull that out of the ifdefs */
/* Define this for quicker (but less perfect) JPEG identification */
#وصف_ڪريو FAST_IS_JPEG

/* See if an image is contained in a data source */
bool SDL_IsJPG(SDL_IOStream *src)
{
    Sint64 شروعات;
    bool is_JPG;
    bool اندريون_جاچ;
    Uint8 magic[4];

    /* This detection code is by Steaphan Greene <stea@cs.binghamton.edu> */
    /* Blame me, not Sam, if this doesn't work right. */
    /* And don't forget to report the problem to the the sdl list too! */

    إذا (!src) {
        أرجع false;
    }

    شروعات = SDL_TellIO(src);
    is_JPG = false;
    اندريون_جاچ = false;
    إذا (SDL_ReadIO(src, magic, 2) == 2) {
        إذا ( (magic[0] == 0xFF) && (magic[1] == 0xD8) ) {
            is_JPG = true;
            طالما (is_JPG) {
                إذا (SDL_ReadIO(src, magic, 2) != 2) {
                    is_JPG = false;
                } وإلا إذا ( (magic[0] != 0xFF) && !اندريون_جاچ ) {
                    is_JPG = false;
                } وإلا إذا ( (magic[0] != 0xFF) || (magic[1] == 0xFF) ) {
                    /* Extra padding in JPEG (legal) */
                    /* or this is data and we are scanning */
                    SDL_SeekIO(src, -1, SDL_IO_SEEK_CUR);
                } وإلا إذا (magic[1] == 0xD9) {
                    /* Got to end of good JPEG */
                    اكسر;
                } وإلا إذا ( اندريون_جاچ && (magic[1] == 0x00) ) {
                    /* This is an encoded 0xFF within the data */
                } وإلا إذا ( (magic[1] >= 0xD0) && (magic[1] < 0xD9) ) {
                    /* These have nothing else */
                } وإلا إذا (SDL_ReadIO(src, magic+2, 2) != 2) {
                    is_JPG = false;
                } وإلا {
                    /* Yes, it's big-endian */
                    Sint64 inner_شروعات;
                    Uint32 سائيز;
                    Sint64 پڇاڙي;
                    inner_شروعات = SDL_TellIO(src);
                    سائيز = (magic[2] << 8) + magic[3];
                    پڇاڙي = SDL_SeekIO(src, سائيز-2, SDL_IO_SEEK_CUR);
                    إذا ( پڇاڙي != inner_شروعات + سائيز - 2 ) {
                        is_JPG = false;
                    }
                    إذا ( magic[1] == 0xDA ) {
                        /* Now comes the actual JPEG meat */
#جيڪڏهن_وصف_ٿيل  FAST_IS_JPEG
                        /* Ok, I'm convinced.  It is a JPEG. */
                        اكسر;
#وإلا
                        /* I'm not convinced.  Prove it! */
                        اندريون_جاچ = true;
#جيڪڏهن_پورو
                    }
                }
            }
        }
    }
    SDL_SeekIO(src, شروعات, SDL_IO_SEEK_سيٽ);
    أرجع is_JPG;
}

SDL_Surface *SDL_ڀريو_JPG_IO(SDL_IOStream *src, bool closeio)
{
    SDL_Surface *surface = عدم;

    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        اذهب پورو;
    }

    إذا (!SDL_IsJPG(src)) {
        SDL_سيٽ_Error("File is not a JPEG file");
        اذهب پورو;
    }

#جيڪڏهن_وصف_ٿيل SDL_HAVE_STB
    surface = SDL_ڀريو_STB_IO(src);
#وإلا
    SDL_سيٽ_Error("SDL not built with STB image support");
#جيڪڏهن_پورو // SDL_HAVE_STB

پورو:
    إذا (src && closeio) {
        SDL_CloseIO(src);
    }
    أرجع surface;
}

SDL_Surface *SDL_ڀريو_JPG(ثابت حرف *file)
{
    SDL_IOStream *وهڪرو = SDL_IOFromFile(file, "rb");
    إذا (!وهڪرو) {
        أرجع عدم;
    }

    أرجع SDL_ڀريو_JPG_IO(وهڪرو, true);
}

bool SDL_IsPNG(SDL_IOStream *src)
{
    Sint64 شروعات;
    Uint8 magic[4];
    bool is_PNG;

    is_PNG = false;
    شروعات = SDL_TellIO(src);
    إذا (شروعات >= 0) {
        إذا (SDL_ReadIO(src, magic, حجم(magic)) == حجم(magic)) {
            إذا (magic[0] == 0x89 &&
                magic[1] == 'P' &&
                magic[2] == 'N' &&
                magic[3] == 'G') {
                is_PNG = true;
            }
        }
        SDL_SeekIO(src, شروعات, SDL_IO_SEEK_سيٽ);
    }

    أرجع is_PNG;
}

SDL_Surface *SDL_ڀريو_PNG_IO(SDL_IOStream *src, bool closeio)
{
    SDL_Surface *surface = عدم;

    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        اذهب پورو;
    }

    إذا (!SDL_IsPNG(src)) {
        SDL_سيٽ_Error("File is not a PNG file");
        اذهب پورو;
    }

#جيڪڏهن_وصف_ٿيل SDL_HAVE_STB
    surface = SDL_ڀريو_STB_IO(src);
#وإلا
    SDL_سيٽ_Error("SDL not built with STB image support");
#جيڪڏهن_پورو // SDL_HAVE_STB

پورو:
    إذا (src && closeio) {
        SDL_CloseIO(src);
    }
    أرجع surface;
}

SDL_Surface *SDL_ڀريو_PNG(ثابت حرف *file)
{
    SDL_IOStream *وهڪرو = SDL_IOFromFile(file, "rb");
    إذا (!وهڪرو) {
        أرجع عدم;
    }

    أرجع SDL_ڀريو_PNG_IO(وهڪرو, true);
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
        اذهب پورو;
    }
    CHECK_PARAM(!dst) {
        SDL_InvalidParamError("dst");
        اذهب پورو;
    }

#جيڪڏهن_وصف_ٿيل SDL_HAVE_STB
    صحيح plte_سائيز = 0;
    صحيح trns_سائيز = 0;

    إذا (SDL_ISPIXELFORMAT_اشاريي_وارو(surface->format)) {
        إذا (!surface->palette) {
            SDL_سيٽ_Error("Indexed surfaces must have a palette");
            اذهب پورو;
        }

        إذا (surface->format != SDL_PIXELFORMAT_INDEX8) {
            surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_INDEX8);
            إذا (!surface) {
                اذهب پورو;
            }
            free_surface = true;
        }

        plte_سائيز = surface->palette->ncolors * 3;
        trns_سائيز = surface->palette->ncolors;
        plte = (Uint8 *)SDL_malloc(plte_سائيز);
        trns = (Uint8 *)SDL_malloc(trns_سائيز);
        إذا (!plte || !trns) {
            اذهب پورو;
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
                اذهب پورو;
            }
            free_surface = true;
        }
    }

    size_t سائيز = 0;
    فراغ *png = tdefl_write_image_منزل_png_file_اندريون_يادگيري_ex(surface->pixels, surface->w, surface->h, SDL_BYTESPERPIXEL(surface->format), surface->pitch, &سائيز, 6, MZ_FALSE, plte, plte_سائيز, trns, trns_سائيز);
    إذا (png) {
        إذا (SDL_WriteIO(dst, png, سائيز)) {
            retval = true;
        }
        mz_free(png); /* calls SDL_free() */
    } وإلا {
        SDL_سيٽ_Error("Failed to convert and save image");
    }

#وإلا
    SDL_سيٽ_Error("SDL not built with STB image support");
#جيڪڏهن_پورو

پورو:
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
#جيڪڏهن_وصف_ٿيل SDL_HAVE_STB
    // Make sure we have something to save
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        أرجع SDL_InvalidParamError("surface");
    }

    إذا (SDL_ISPIXELFORMAT_اشاريي_وارو(surface->format) && !surface->palette) {
        أرجع SDL_سيٽ_Error("Indexed surfaces must have a palette");
    }
    SDL_IOStream *وهڪرو = SDL_IOFromFile(file, "wb");
    إذا (!وهڪرو) {
        أرجع false;
    }

    أرجع SDL_SavePNG_IO(surface, وهڪرو, true);
#وإلا
    أرجع SDL_سيٽ_Error("SDL not built with STB image support");
#جيڪڏهن_پورو
}
