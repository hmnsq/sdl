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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_stb_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_surface_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_yuv_c.h"

/* STB image conversion */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_DISABLE_STB
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_HAVE_STB
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_HAVE_STB
////////////////////////////////////////////////////////////////////////////
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਸਮ੍ਰਿਤੀ_ਦਿਓ SDL_malloc
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ realloc SDL_realloc
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਮੁਕਤ SDL_free
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ ਸਮ੍ਰਿਤੀ_ਨਕਲ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਸਮ੍ਰਿਤੀ_ਨਕਲ SDL_memcpy
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ memset
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ memset SDL_memset
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ strcmp
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ strcmp SDL_strcmp
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ ਲੜੀ_ਤੁਲਨਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਲੜੀ_ਤੁਲਨਾ SDL_strncmp
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ strtol SDL_strtol

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਨਿਰਪੇਖ SDL_abs
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਘਾਤ SDL_pow
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ldexp SDL_scalbn

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STB_IMAGE_STATIC
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STBI_NO_THREAD_LOCALS
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STBI_FAILURE_USERMSG
#ਜੇ defined(SDL_NEON_INTRINSICS)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STBI_NEON
#ਜੇ_ਅੰਤ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STBI_ONLY_PNG
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STBI_ONLY_JPEG
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STBI_NO_GIF
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STBI_NO_HDR
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STBI_NO_ਰੇਖਿਕ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STBI_NO_STDIO
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STBI_ASSERT SDL_assert
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STB_IMAGE_IMPLEMENTATION
#ਅਨ੍ਤਰ੍ਭਾਵ "stb_image.h"

////////////////////////////////////////////////////////////////////////////
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_ASSERT(x) SDL_assert(x)
//#undef memcpy
//#define memcpy SDL_memcpy
//#undef memset
//#define memset SDL_memset
#ਜੇ SDL_BYTEORDER == SDL_LIL_ENDIAN
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MINIZ_LITTLE_ENDIAN 1
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MINIZ_LITTLE_ENDIAN 0
#ਜੇ_ਅੰਤ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MINIZ_USE_UNALIGNED_LOADS_AND_STORES 0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MINIZ_SDL_NOUNUSED
#ਅਨ੍ਤਰ੍ਭਾਵ "miniz.h"

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ memset
#ਜੇ_ਅੰਤ // SDL_HAVE_STB

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_HAVE_STB
ਸਥਿਰ bool SDL_Convert_Pixels_MJPG_ਮੰਜ਼ਿਲ_NV12(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, ਅਚਲ ਖਾਲੀ *src, ਪੂਰਨ src_pitch, ਖਾਲੀ *dst, ਪੂਰਨ dst_pitch)
{
    ਪੂਰਨ w = 0, h = 0, format = 0;
    stbi__context s;
    stbi_ਸ਼ੁਰੂ_mem(&s, src, src_pitch);

    stbi_ਨਤੀਜਾ_info ri;
    SDL_zero(ri);
    ri.ਬਿੱਟ_ਪ੍ਰਤੀ_channel = 8;
    ri.channel_ਕ੍ਰਮ = STBI_ਕ੍ਰਮ_RGB;
    ri.ਅੰਕ_channels = 0;

    stbi__nv12 nv12;
    nv12.w = ਚੌੜਾਈ;
    nv12.h = ਉਚਾਈ;
    nv12.pitch = dst_pitch;
    nv12.y = (stbi_uc *)dst;
    nv12.uv = nv12.y + (nv12.h * nv12.pitch);

    ਖਾਲੀ *pixels = stbi_jpeg_ਲੱਦੋ(&s, &w, &h, &format, 4, &nv12, &ri);
    ਜੇ (!pixels) {
        ਵਾਪਸ false;
    }
    ਵਾਪਸ true;
}
#ਜੇ_ਅੰਤ // SDL_HAVE_STB

bool SDL_ConvertPixels_STB(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ,
                           SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ਅਚਲ ਖਾਲੀ *src, ਪੂਰਨ src_pitch,
                           SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, ਖਾਲੀ *dst, ਪੂਰਨ dst_pitch)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_HAVE_STB
    ਜੇ (src_format == SDL_PIXELFORMAT_MJPG) {
        ਜੇ (dst_format == SDL_PIXELFORMAT_NV12) {
            ਵਾਪਸ SDL_Convert_Pixels_MJPG_ਮੰਜ਼ਿਲ_NV12(ਚੌੜਾਈ, ਉਚਾਈ, src, src_pitch, dst, dst_pitch);
        } ਨਹੀਂਤਾਂ ਜੇ (
            dst_format == SDL_PIXELFORMAT_YV12 ||
            dst_format == SDL_PIXELFORMAT_IYUV ||
            dst_format == SDL_PIXELFORMAT_YUY2 ||
            dst_format == SDL_PIXELFORMAT_UYVY ||
            dst_format == SDL_PIXELFORMAT_YVYU ||
            dst_format == SDL_PIXELFORMAT_NV21 ||
            dst_format == SDL_PIXELFORMAT_P010
        ) {
            size_t ਆਰਜ਼ੀ_ਮਾਪ = 0;
            size_t ਆਰਜ਼ੀ_pitch = 0;
            ਜੇ (!SDL_CalculateYUVSize(dst_format, ਚੌੜਾਈ, ਉਚਾਈ, &ਆਰਜ਼ੀ_ਮਾਪ, &ਆਰਜ਼ੀ_pitch)) {
                ਵਾਪਸ false;
            }
            ਖਾਲੀ *ਆਰਜ਼ੀ_pixels = SDL_malloc(ਆਰਜ਼ੀ_ਮਾਪ);
            ਜੇ (!ਆਰਜ਼ੀ_pixels) {
                ਵਾਪਸ false;
            }

            ਜੇ (!SDL_Convert_Pixels_MJPG_ਮੰਜ਼ਿਲ_NV12(ਚੌੜਾਈ, ਉਚਾਈ, src, src_pitch, ਆਰਜ਼ੀ_pixels, (ਪੂਰਨ)ਆਰਜ਼ੀ_pitch)) {
                SDL_free(ਆਰਜ਼ੀ_pixels);
                ਵਾਪਸ false;
            }

            bool ਨਤੀਜਾ = SDL_ConvertPixelsAndColorspace(ਚੌੜਾਈ, ਉਚਾਈ, SDL_PIXELFORMAT_NV12, src_colorspace, 0 /*props*/, ਆਰਜ਼ੀ_pixels, (ਪੂਰਨ)ਆਰਜ਼ੀ_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
            SDL_free(ਆਰਜ਼ੀ_pixels);
            ਵਾਪਸ ਨਤੀਜਾ;
        }
    }

    bool ਨਤੀਜਾ;
    ਪੂਰਨ w = 0, h = 0, format = 0;
    ਪੂਰਨ len = (src_format == SDL_PIXELFORMAT_MJPG) ? src_pitch : (ਉਚਾਈ * src_pitch);
    ਖਾਲੀ *pixels = stbi_ਲੱਦੋ_from_ਸਮ੍ਰਿਤੀ(src, len, &w, &h, &format, 4);
    ਜੇ (!pixels) {
        ਵਾਪਸ false;
    }

    ਜੇ (w == ਚੌੜਾਈ && h == ਉਚਾਈ) {
        ਨਤੀਜਾ = SDL_ConvertPixelsAndColorspace(w, h, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, pixels, ਚੌੜਾਈ * 4, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } ਨਹੀਂਤਾਂ {
        ਨਤੀਜਾ = SDL_ਸੈੱਟ_Error("Expected image size %dx%d, actual size %dx%d", ਚੌੜਾਈ, ਉਚਾਈ, w, h);
    }
    stbi_image_free(pixels);

    ਵਾਪਸ ਨਤੀਜਾ;
#ਨਹੀਂਤਾਂ
    ਵਾਪਸ SDL_ਸੈੱਟ_Error("SDL not built with STB image support");
#ਜੇ_ਅੰਤ
}

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_HAVE_STB
ਸਥਿਰ ਪੂਰਨ IMG_ਲੱਦੋ_STB_IO_read(ਖਾਲੀ *user, ਅੱਖਰ *ਅੰਕੜੇ, ਪੂਰਨ ਮਾਪ)
{
    size_t amount = SDL_ReadIO((SDL_IOStream*)user, ਅੰਕੜੇ, ਮਾਪ);
    ਵਾਪਸ (ਪੂਰਨ)amount;
}

ਸਥਿਰ ਖਾਲੀ IMG_ਲੱਦੋ_STB_IO_skip(ਖਾਲੀ *user, ਪੂਰਨ n)
{
    SDL_SeekIO((SDL_IOStream*)user, n, SDL_IO_SEEK_CUR);
}

ਸਥਿਰ ਪੂਰਨ IMG_ਲੱਦੋ_STB_IO_eof(ਖਾਲੀ *user)
{
    SDL_IOStream *src = (SDL_IOStream*)user;
    ਵਾਪਸ SDL_GetIOStatus(src) == SDL_IO_ਸਥਿਤੀ_EOF;
}

ਸਥਿਰ SDL_Surface *SDL_ਲੱਦੋ_STB_IO(SDL_IOStream *src)
{
    Sint64 ਸ਼ੁਰੂ;
    Uint8 magic[26];
    ਪੂਰਨ w, h, format;
    stbi_uc *pixels;
    stbi_io_callbacks rw_callbacks;
    SDL_Surface *surface = ਨਿਰਾ;
    bool use_palette = false;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ palette_colors[256];

    // src has already been validated
    ਸ਼ੁਰੂ = SDL_TellIO(src);

    ਜੇ (SDL_ReadIO(src, magic, ਆਕਾਰ(magic)) == ਆਕਾਰ(magic)) {
        ਅਚਲ Uint8 PNG_COLOR_ਸੂਚਕਾਂਕਿਤ = 3;
        ਜੇ (magic[0] == 0x89 &&
            magic[1] == 'P' &&
            magic[2] == 'N' &&
            magic[3] == 'G' &&
            magic[12] == 'I' &&
            magic[13] == 'H' &&
            magic[14] == 'D' &&
            magic[15] == 'R' &&
            magic[25] == PNG_COLOR_ਸੂਚਕਾਂਕਿਤ) {
            use_palette = true;
        }
    }
    SDL_SeekIO(src, ਸ਼ੁਰੂ, SDL_IO_SEEK_ਸੈੱਟ);

    /* Load the image data */
    rw_callbacks.ਪਠ = IMG_ਲੱਦੋ_STB_IO_read;
    rw_callbacks.skip = IMG_ਲੱਦੋ_STB_IO_skip;
    rw_callbacks.eof = IMG_ਲੱਦੋ_STB_IO_eof;
    w = h = format = 0; /* silence warning */
    ਜੇ (use_palette) {
        /* Unused palette entries will be opaque white */
        SDL_memset(palette_colors, 0xff, ਆਕਾਰ(palette_colors));

        pixels = stbi_ਲੱਦੋ_from_callbacks_with_palette(
            &rw_callbacks,
            src,
            &w,
            &h,
            palette_colors,
            SDL_arraysize(palette_colors)
        );
    } ਨਹੀਂਤਾਂ {
        pixels = stbi_ਲੱਦੋ_from_callbacks(
            &rw_callbacks,
            src,
            &w,
            &h,
            &format,
            STBI_default
        );
    }
    ਜੇ (!pixels) {
        SDL_SeekIO(src, ਸ਼ੁਰੂ, SDL_IO_SEEK_ਸੈੱਟ);
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਜੇ (use_palette) {
        surface = SDL_CreateSurfaceFrom(
            w,
            h,
            SDL_PIXELFORMAT_INDEX8,
            pixels,
            w
        );
        ਜੇ (surface) {
            bool has_colorkey = false;
            ਪੂਰਨ colorkey_ਸੂਚਕਾਂਕ = -1;
            bool has_alpha = false;
            SDL_Palette *palette = SDL_CreateSurfacePalette(surface);
            ਜੇ (palette) {
                ਪੂਰਨ i;
                Uint8 *palette_ਬਾਈਟਾਂ = (Uint8 *)palette_colors;

                ਲਈ (i = 0; i < palette->ncolors; i++) {
                    palette->colors[i].r = *palette_ਬਾਈਟਾਂ++;
                    palette->colors[i].g = *palette_ਬਾਈਟਾਂ++;
                    palette->colors[i].b = *palette_ਬਾਈਟਾਂ++;
                    palette->colors[i].a = *palette_ਬਾਈਟਾਂ++;
                    ਜੇ (palette->colors[i].a != SDL_ALPHA_OPAQUE) {
                        ਜੇ (palette->colors[i].a == SDL_ALPHA_TRANSPARENT && !has_colorkey) {
                            has_colorkey = true;
                            colorkey_ਸੂਚਕਾਂਕ = i;
                        } ਨਹੀਂਤਾਂ {
                            /* Partial opacity or multiple colorkeys */
                            has_alpha = true;
                        }
                    }
                }
            }
            ਜੇ (has_alpha) {
                SDL_ਸੈੱਟ_Surface_Blend_ਬਹੁਲਕ(surface, SDL_BLENDMODE_BLEND);
            } ਨਹੀਂਤਾਂ ਜੇ (has_colorkey) {
                SDL_ਸੈੱਟ_Surface_Color_ਕੁੰਜੀ(surface, true, colorkey_ਸੂਚਕਾਂਕ);
            }

            /* FIXME: This sucks. It'd be better to allocate the surface first, then
             * write directly to the pixel buffer:
             * https://github.com/nothings/stb/issues/58
             * -flibit
             */
            surface->flags &= ~SDL_SURFACE_PREALLOCATED;
        }

    } ਨਹੀਂਤਾਂ ਜੇ (format == STBI_grey || format == STBI_rgb || format == STBI_rgb_alpha) {
        surface = SDL_CreateSurfaceFrom(
            w,
            h,
            (format == STBI_rgb_alpha) ? SDL_PIXELFORMAT_RGBA32 :
            (format == STBI_rgb) ? SDL_PIXELFORMAT_RGB24 :
            SDL_PIXELFORMAT_INDEX8,
            pixels,
            w * format
        );
        ਜੇ (surface) {
            /* Set a grayscale palette for gray images */
            ਜੇ (surface->format == SDL_PIXELFORMAT_INDEX8) {
                SDL_Palette *palette = SDL_CreateSurfacePalette(surface);
                ਜੇ (palette) {
                    ਪੂਰਨ i;

                    ਲਈ (i = 0; i < palette->ncolors; i++) {
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

    } ਨਹੀਂਤਾਂ ਜੇ (format == STBI_grey_alpha) {
        surface = SDL_CreateSurfaceUninitialized(w, h, SDL_PIXELFORMAT_RGBA32);
        ਜੇ (surface) {
            Uint8 *src_ptr = pixels;
            Uint8 *dst = (Uint8 *)surface->pixels;
            ਪੂਰਨ skip = surface->pitch - (surface->w * 4);
            ਪੂਰਨ ਪੰਕਤੀ, ਖਾਨਾ;

            ਲਈ (ਪੰਕਤੀ = 0; ਪੰਕਤੀ < h; ++ਪੰਕਤੀ) {
                ਲਈ (ਖਾਨਾ = 0; ਖਾਨਾ < w; ++ਖਾਨਾ) {
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
    } ਨਹੀਂਤਾਂ {
        SDL_ਸੈੱਟ_Error("Unknown image format: %d", format);
    }

    ਜੇ (!surface) {
        /* The error message should already be set */
        stbi_image_free(pixels); /* calls SDL_free() */
        SDL_SeekIO(src, ਸ਼ੁਰੂ, SDL_IO_SEEK_ਸੈੱਟ);
    }
    ਵਾਪਸ surface;
}
#ਜੇ_ਅੰਤ // SDL_HAVE_STB

/* FIXME: This is a copypaste from JPEGLIB! Pull that out of the ifdefs */
/* Define this for quicker (but less perfect) JPEG identification */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FAST_IS_JPEG

/* See if an image is contained in a data source */
bool SDL_IsJPG(SDL_IOStream *src)
{
    Sint64 ਸ਼ੁਰੂ;
    bool is_JPG;
    bool ਵਿੱਚ_ਜਾਂਚ;
    Uint8 magic[4];

    /* This detection code is by Steaphan Greene <stea@cs.binghamton.edu> */
    /* Blame me, not Sam, if this doesn't work right. */
    /* And don't forget to report the problem to the the sdl list too! */

    ਜੇ (!src) {
        ਵਾਪਸ false;
    }

    ਸ਼ੁਰੂ = SDL_TellIO(src);
    is_JPG = false;
    ਵਿੱਚ_ਜਾਂਚ = false;
    ਜੇ (SDL_ReadIO(src, magic, 2) == 2) {
        ਜੇ ( (magic[0] == 0xFF) && (magic[1] == 0xD8) ) {
            is_JPG = true;
            ਜਦੋਂ (is_JPG) {
                ਜੇ (SDL_ReadIO(src, magic, 2) != 2) {
                    is_JPG = false;
                } ਨਹੀਂਤਾਂ ਜੇ ( (magic[0] != 0xFF) && !ਵਿੱਚ_ਜਾਂਚ ) {
                    is_JPG = false;
                } ਨਹੀਂਤਾਂ ਜੇ ( (magic[0] != 0xFF) || (magic[1] == 0xFF) ) {
                    /* Extra padding in JPEG (legal) */
                    /* or this is data and we are scanning */
                    SDL_SeekIO(src, -1, SDL_IO_SEEK_CUR);
                } ਨਹੀਂਤਾਂ ਜੇ (magic[1] == 0xD9) {
                    /* Got to end of good JPEG */
                    ਰੋਕੋ;
                } ਨਹੀਂਤਾਂ ਜੇ ( ਵਿੱਚ_ਜਾਂਚ && (magic[1] == 0x00) ) {
                    /* This is an encoded 0xFF within the data */
                } ਨਹੀਂਤਾਂ ਜੇ ( (magic[1] >= 0xD0) && (magic[1] < 0xD9) ) {
                    /* These have nothing else */
                } ਨਹੀਂਤਾਂ ਜੇ (SDL_ReadIO(src, magic+2, 2) != 2) {
                    is_JPG = false;
                } ਨਹੀਂਤਾਂ {
                    /* Yes, it's big-endian */
                    Sint64 inner_ਸ਼ੁਰੂ;
                    Uint32 ਮਾਪ;
                    Sint64 ਸਿਰਾ;
                    inner_ਸ਼ੁਰੂ = SDL_TellIO(src);
                    ਮਾਪ = (magic[2] << 8) + magic[3];
                    ਸਿਰਾ = SDL_SeekIO(src, ਮਾਪ-2, SDL_IO_SEEK_CUR);
                    ਜੇ ( ਸਿਰਾ != inner_ਸ਼ੁਰੂ + ਮਾਪ - 2 ) {
                        is_JPG = false;
                    }
                    ਜੇ ( magic[1] == 0xDA ) {
                        /* Now comes the actual JPEG meat */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ  FAST_IS_JPEG
                        /* Ok, I'm convinced.  It is a JPEG. */
                        ਰੋਕੋ;
#ਨਹੀਂਤਾਂ
                        /* I'm not convinced.  Prove it! */
                        ਵਿੱਚ_ਜਾਂਚ = true;
#ਜੇ_ਅੰਤ
                    }
                }
            }
        }
    }
    SDL_SeekIO(src, ਸ਼ੁਰੂ, SDL_IO_SEEK_ਸੈੱਟ);
    ਵਾਪਸ is_JPG;
}

SDL_Surface *SDL_ਲੱਦੋ_JPG_IO(SDL_IOStream *src, bool closeio)
{
    SDL_Surface *surface = ਨਿਰਾ;

    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        ਜਾਓ ਪੂਰਾ;
    }

    ਜੇ (!SDL_IsJPG(src)) {
        SDL_ਸੈੱਟ_Error("File is not a JPEG file");
        ਜਾਓ ਪੂਰਾ;
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_HAVE_STB
    surface = SDL_ਲੱਦੋ_STB_IO(src);
#ਨਹੀਂਤਾਂ
    SDL_ਸੈੱਟ_Error("SDL not built with STB image support");
#ਜੇ_ਅੰਤ // SDL_HAVE_STB

ਪੂਰਾ:
    ਜੇ (src && closeio) {
        SDL_CloseIO(src);
    }
    ਵਾਪਸ surface;
}

SDL_Surface *SDL_ਲੱਦੋ_JPG(ਅਚਲ ਅੱਖਰ *file)
{
    SDL_IOStream *ਧਾਰਾ = SDL_IOFromFile(file, "rb");
    ਜੇ (!ਧਾਰਾ) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਵਾਪਸ SDL_ਲੱਦੋ_JPG_IO(ਧਾਰਾ, true);
}

bool SDL_IsPNG(SDL_IOStream *src)
{
    Sint64 ਸ਼ੁਰੂ;
    Uint8 magic[4];
    bool is_PNG;

    is_PNG = false;
    ਸ਼ੁਰੂ = SDL_TellIO(src);
    ਜੇ (ਸ਼ੁਰੂ >= 0) {
        ਜੇ (SDL_ReadIO(src, magic, ਆਕਾਰ(magic)) == ਆਕਾਰ(magic)) {
            ਜੇ (magic[0] == 0x89 &&
                magic[1] == 'P' &&
                magic[2] == 'N' &&
                magic[3] == 'G') {
                is_PNG = true;
            }
        }
        SDL_SeekIO(src, ਸ਼ੁਰੂ, SDL_IO_SEEK_ਸੈੱਟ);
    }

    ਵਾਪਸ is_PNG;
}

SDL_Surface *SDL_ਲੱਦੋ_PNG_IO(SDL_IOStream *src, bool closeio)
{
    SDL_Surface *surface = ਨਿਰਾ;

    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        ਜਾਓ ਪੂਰਾ;
    }

    ਜੇ (!SDL_IsPNG(src)) {
        SDL_ਸੈੱਟ_Error("File is not a PNG file");
        ਜਾਓ ਪੂਰਾ;
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_HAVE_STB
    surface = SDL_ਲੱਦੋ_STB_IO(src);
#ਨਹੀਂਤਾਂ
    SDL_ਸੈੱਟ_Error("SDL not built with STB image support");
#ਜੇ_ਅੰਤ // SDL_HAVE_STB

ਪੂਰਾ:
    ਜੇ (src && closeio) {
        SDL_CloseIO(src);
    }
    ਵਾਪਸ surface;
}

SDL_Surface *SDL_ਲੱਦੋ_PNG(ਅਚਲ ਅੱਖਰ *file)
{
    SDL_IOStream *ਧਾਰਾ = SDL_IOFromFile(file, "rb");
    ਜੇ (!ਧਾਰਾ) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਵਾਪਸ SDL_ਲੱਦੋ_PNG_IO(ਧਾਰਾ, true);
}

bool SDL_SavePNG_IO(SDL_Surface *surface, SDL_IOStream *dst, bool closeio)
{
    bool retval = false;
    Uint8 *plte = ਨਿਰਾ;
    Uint8 *trns = ਨਿਰਾ;
    bool free_surface = false;

    // Make sure we have something to save
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        ਜਾਓ ਪੂਰਾ;
    }
    CHECK_PARAM(!dst) {
        SDL_InvalidParamError("dst");
        ਜਾਓ ਪੂਰਾ;
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_HAVE_STB
    ਪੂਰਨ plte_ਮਾਪ = 0;
    ਪੂਰਨ trns_ਮਾਪ = 0;

    ਜੇ (SDL_ISPIXELFORMAT_ਸੂਚਕਾਂਕਿਤ(surface->format)) {
        ਜੇ (!surface->palette) {
            SDL_ਸੈੱਟ_Error("Indexed surfaces must have a palette");
            ਜਾਓ ਪੂਰਾ;
        }

        ਜੇ (surface->format != SDL_PIXELFORMAT_INDEX8) {
            surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_INDEX8);
            ਜੇ (!surface) {
                ਜਾਓ ਪੂਰਾ;
            }
            free_surface = true;
        }

        plte_ਮਾਪ = surface->palette->ncolors * 3;
        trns_ਮਾਪ = surface->palette->ncolors;
        plte = (Uint8 *)SDL_malloc(plte_ਮਾਪ);
        trns = (Uint8 *)SDL_malloc(trns_ਮਾਪ);
        ਜੇ (!plte || !trns) {
            ਜਾਓ ਪੂਰਾ;
        }
        SDL_Color *colors = surface->palette->colors;
        ਲਈ (ਪੂਰਨ i = 0; i < surface->palette->ncolors; ++i) {
            plte[i * 3 + 0] = colors[i].r;
            plte[i * 3 + 1] = colors[i].g;
            plte[i * 3 + 2] = colors[i].b;
            trns[i] = colors[i].a;
        }
    } ਨਹੀਂਤਾਂ {
        ਜੇ (surface->format != SDL_PIXELFORMAT_RGBA32) {
            surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);
            ਜੇ (!surface) {
                ਜਾਓ ਪੂਰਾ;
            }
            free_surface = true;
        }
    }

    size_t ਮਾਪ = 0;
    ਖਾਲੀ *png = tdefl_write_image_ਮੰਜ਼ਿਲ_png_file_ਵਿੱਚ_ਸਮ੍ਰਿਤੀ_ex(surface->pixels, surface->w, surface->h, SDL_BYTESPERPIXEL(surface->format), surface->pitch, &ਮਾਪ, 6, MZ_FALSE, plte, plte_ਮਾਪ, trns, trns_ਮਾਪ);
    ਜੇ (png) {
        ਜੇ (SDL_WriteIO(dst, png, ਮਾਪ)) {
            retval = true;
        }
        mz_free(png); /* calls SDL_free() */
    } ਨਹੀਂਤਾਂ {
        SDL_ਸੈੱਟ_Error("Failed to convert and save image");
    }

#ਨਹੀਂਤਾਂ
    SDL_ਸੈੱਟ_Error("SDL not built with STB image support");
#ਜੇ_ਅੰਤ

ਪੂਰਾ:
    ਜੇ (free_surface) {
        SDL_DestroySurface(surface);
    }
    SDL_free(plte);
    SDL_free(trns);

    ਜੇ (dst && closeio) {
        retval &= SDL_CloseIO(dst);
    }
    ਵਾਪਸ retval;
}

bool SDL_SavePNG(SDL_Surface *surface, ਅਚਲ ਅੱਖਰ *file)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_HAVE_STB
    // Make sure we have something to save
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ਵਾਪਸ SDL_InvalidParamError("surface");
    }

    ਜੇ (SDL_ISPIXELFORMAT_ਸੂਚਕਾਂਕਿਤ(surface->format) && !surface->palette) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Indexed surfaces must have a palette");
    }
    SDL_IOStream *ਧਾਰਾ = SDL_IOFromFile(file, "wb");
    ਜੇ (!ਧਾਰਾ) {
        ਵਾਪਸ false;
    }

    ਵਾਪਸ SDL_SavePNG_IO(surface, ਧਾਰਾ, true);
#ਨਹੀਂਤਾਂ
    ਵਾਪਸ SDL_ਸੈੱਟ_Error("SDL not built with STB image support");
#ਜੇ_ਅੰਤ
}
