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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ಅನ್ತರ್ಭಾವ "SDL_stb_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_surface_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_yuv_c.h"

/* STB image conversion */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_DISABLE_STB
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_HAVE_STB
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_HAVE_STB
////////////////////////////////////////////////////////////////////////////
#ವ್ಯಾಖ್ಯಾನಿಸು ಸ್ಮರಣೆ_ಕೊಡು SDL_malloc
#ವ್ಯಾಖ್ಯಾನಿಸು realloc SDL_realloc
#ವ್ಯಾಖ್ಯಾನಿಸು ಬಿಡುಗಡೆ SDL_free
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು ಸ್ಮರಣೆ_ನಕಲು
#ವ್ಯಾಖ್ಯಾನಿಸು ಸ್ಮರಣೆ_ನಕಲು SDL_memcpy
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು memset
#ವ್ಯಾಖ್ಯಾನಿಸು memset SDL_memset
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು strcmp
#ವ್ಯಾಖ್ಯಾನಿಸು strcmp SDL_strcmp
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು ಅಕ್ಷರಸರಣಿ_ಹೋಲಿಕೆ
#ವ್ಯಾಖ್ಯಾನಿಸು ಅಕ್ಷರಸರಣಿ_ಹೋಲಿಕೆ SDL_strncmp
#ವ್ಯಾಖ್ಯಾನಿಸು strtol SDL_strtol

#ವ್ಯಾಖ್ಯಾನಿಸು ನಿರಪೇಕ್ಷ SDL_abs
#ವ್ಯಾಖ್ಯಾನಿಸು ಘಾತ SDL_pow
#ವ್ಯಾಖ್ಯಾನಿಸು ldexp SDL_scalbn

#ವ್ಯಾಖ್ಯಾನಿಸು STB_IMAGE_STATIC
#ವ್ಯಾಖ್ಯಾನಿಸು STBI_NO_THREAD_LOCALS
#ವ್ಯಾಖ್ಯಾನಿಸು STBI_FAILURE_USERMSG
#ಆದರೆ defined(SDL_NEON_INTRINSICS)
#ವ್ಯಾಖ್ಯಾನಿಸು STBI_NEON
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿಸು STBI_ONLY_PNG
#ವ್ಯಾಖ್ಯಾನಿಸು STBI_ONLY_JPEG
#ವ್ಯಾಖ್ಯಾನಿಸು STBI_NO_GIF
#ವ್ಯಾಖ್ಯಾನಿಸು STBI_NO_HDR
#ವ್ಯಾಖ್ಯಾನಿಸು STBI_NO_ರೇಖೀಯ
#ವ್ಯಾಖ್ಯಾನಿಸು STBI_NO_STDIO
#ವ್ಯಾಖ್ಯಾನಿಸು STBI_ASSERT SDL_assert
#ವ್ಯಾಖ್ಯಾನಿಸು STB_IMAGE_IMPLEMENTATION
#ಅನ್ತರ್ಭಾವ "stb_image.h"

////////////////////////////////////////////////////////////////////////////
#ವ್ಯಾಖ್ಯಾನಿಸು MZ_ASSERT(x) SDL_assert(x)
//#undef memcpy
//#define memcpy SDL_memcpy
//#undef memset
//#define memset SDL_memset
#ಆದರೆ SDL_BYTEORDER == SDL_LIL_ENDIAN
#ವ್ಯಾಖ್ಯಾನಿಸು MINIZ_LITTLE_ENDIAN 1
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು MINIZ_LITTLE_ENDIAN 0
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿಸು MINIZ_USE_UNALIGNED_LOADS_AND_STORES 0
#ವ್ಯಾಖ್ಯಾನಿಸು MINIZ_SDL_NOUNUSED
#ಅನ್ತರ್ಭಾವ "miniz.h"

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು memset
#ಆದರೆ_ಅಂತ್ಯ // SDL_HAVE_STB

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_HAVE_STB
ಸ್ಥಿರ bool SDL_Convert_Pixels_MJPG_ಗಮ್ಯ_NV12(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಂಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಂಕ dst_pitch)
{
    ಪೂರ್ಣಾಂಕ w = 0, h = 0, format = 0;
    stbi__context s;
    stbi_ಆರಂಭ_mem(&s, src, src_pitch);

    stbi_ಫಲಿತಾಂಶ_info ri;
    SDL_zero(ri);
    ri.ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_channel = 8;
    ri.channel_ಕ್ರಮ = STBI_ಕ್ರಮ_RGB;
    ri.ಅಂಕೆ_channels = 0;

    stbi__nv12 nv12;
    nv12.w = ಅಗಲ;
    nv12.h = ಎತ್ತರ;
    nv12.pitch = dst_pitch;
    nv12.y = (stbi_uc *)dst;
    nv12.uv = nv12.y + (nv12.h * nv12.pitch);

    ಶೂನ್ಯ *pixels = stbi_jpeg_ತುಂಬು(&s, &w, &h, &format, 4, &nv12, &ri);
    ಆದರೆ (!pixels) {
        ಹಿಂತಿರುಗಿ false;
    }
    ಹಿಂತಿರುಗಿ true;
}
#ಆದರೆ_ಅಂತ್ಯ // SDL_HAVE_STB

bool SDL_ConvertPixels_STB(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ,
                           SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಂಕ src_pitch,
                           SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಂಕ dst_pitch)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_HAVE_STB
    ಆದರೆ (src_format == SDL_PIXELFORMAT_MJPG) {
        ಆದರೆ (dst_format == SDL_PIXELFORMAT_NV12) {
            ಹಿಂತಿರುಗಿ SDL_Convert_Pixels_MJPG_ಗಮ್ಯ_NV12(ಅಗಲ, ಎತ್ತರ, src, src_pitch, dst, dst_pitch);
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (
            dst_format == SDL_PIXELFORMAT_YV12 ||
            dst_format == SDL_PIXELFORMAT_IYUV ||
            dst_format == SDL_PIXELFORMAT_YUY2 ||
            dst_format == SDL_PIXELFORMAT_UYVY ||
            dst_format == SDL_PIXELFORMAT_YVYU ||
            dst_format == SDL_PIXELFORMAT_NV21 ||
            dst_format == SDL_PIXELFORMAT_P010
        ) {
            size_t ತಾತ್ಕಾಲಿಕ_ಗಾತ್ರ = 0;
            size_t ತಾತ್ಕಾಲಿಕ_pitch = 0;
            ಆದರೆ (!SDL_CalculateYUVSize(dst_format, ಅಗಲ, ಎತ್ತರ, &ತಾತ್ಕಾಲಿಕ_ಗಾತ್ರ, &ತಾತ್ಕಾಲಿಕ_pitch)) {
                ಹಿಂತಿರುಗಿ false;
            }
            ಶೂನ್ಯ *ತಾತ್ಕಾಲಿಕ_pixels = SDL_malloc(ತಾತ್ಕಾಲಿಕ_ಗಾತ್ರ);
            ಆದರೆ (!ತಾತ್ಕಾಲಿಕ_pixels) {
                ಹಿಂತಿರುಗಿ false;
            }

            ಆದರೆ (!SDL_Convert_Pixels_MJPG_ಗಮ್ಯ_NV12(ಅಗಲ, ಎತ್ತರ, src, src_pitch, ತಾತ್ಕಾಲಿಕ_pixels, (ಪೂರ್ಣಾಂಕ)ತಾತ್ಕಾಲಿಕ_pitch)) {
                SDL_free(ತಾತ್ಕಾಲಿಕ_pixels);
                ಹಿಂತಿರುಗಿ false;
            }

            bool ಫಲಿತಾಂಶ = SDL_ConvertPixelsAndColorspace(ಅಗಲ, ಎತ್ತರ, SDL_PIXELFORMAT_NV12, src_colorspace, 0 /*props*/, ತಾತ್ಕಾಲಿಕ_pixels, (ಪೂರ್ಣಾಂಕ)ತಾತ್ಕಾಲಿಕ_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
            SDL_free(ತಾತ್ಕಾಲಿಕ_pixels);
            ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
        }
    }

    bool ಫಲಿತಾಂಶ;
    ಪೂರ್ಣಾಂಕ w = 0, h = 0, format = 0;
    ಪೂರ್ಣಾಂಕ len = (src_format == SDL_PIXELFORMAT_MJPG) ? src_pitch : (ಎತ್ತರ * src_pitch);
    ಶೂನ್ಯ *pixels = stbi_ತುಂಬು_from_ಸ್ಮರಣೆ(src, len, &w, &h, &format, 4);
    ಆದರೆ (!pixels) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಆದರೆ (w == ಅಗಲ && h == ಎತ್ತರ) {
        ಫಲಿತಾಂಶ = SDL_ConvertPixelsAndColorspace(w, h, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, pixels, ಅಗಲ * 4, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಫಲಿತಾಂಶ = SDL_ಗಣ_Error("Expected image size %dx%d, actual size %dx%d", ಅಗಲ, ಎತ್ತರ, w, h);
    }
    stbi_image_free(pixels);

    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
#ಇಲ್ಲದಿದ್ದರೆ
    ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("SDL not built with STB image support");
#ಆದರೆ_ಅಂತ್ಯ
}

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_HAVE_STB
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ IMG_ತುಂಬು_STB_IO_read(ಶೂನ್ಯ *user, ಅಕ್ಷರ *ದತ್ತಾಂಶ, ಪೂರ್ಣಾಂಕ ಗಾತ್ರ_2)
{
    size_t amount = SDL_ReadIO((SDL_IOStream*)user, ದತ್ತಾಂಶ, ಗಾತ್ರ_2);
    ಹಿಂತಿರುಗಿ (ಪೂರ್ಣಾಂಕ)amount;
}

ಸ್ಥಿರ ಶೂನ್ಯ IMG_ತುಂಬು_STB_IO_skip(ಶೂನ್ಯ *user, ಪೂರ್ಣಾಂಕ n)
{
    SDL_SeekIO((SDL_IOStream*)user, n, SDL_IO_SEEK_CUR);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ IMG_ತುಂಬು_STB_IO_eof(ಶೂನ್ಯ *user)
{
    SDL_IOStream *src = (SDL_IOStream*)user;
    ಹಿಂತಿರುಗಿ SDL_GetIOStatus(src) == SDL_IO_ಸ್ಥಿತಿ_EOF;
}

ಸ್ಥಿರ SDL_Surface *SDL_ತುಂಬು_STB_IO(SDL_IOStream *src)
{
    Sint64 ಆರಂಭ;
    Uint8 magic[26];
    ಪೂರ್ಣಾಂಕ w, h, format;
    stbi_uc *pixels;
    stbi_io_callbacks rw_callbacks;
    SDL_Surface *surface = ಖಾಲಿ;
    bool use_palette = false;
    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ palette_colors[256];

    // src has already been validated
    ಆರಂಭ = SDL_TellIO(src);

    ಆದರೆ (SDL_ReadIO(src, magic, ಗಾತ್ರ(magic)) == ಗಾತ್ರ(magic)) {
        ಸ್ಥಿರಾಂಕ Uint8 PNG_COLOR_ಸೂಚ್ಯಂಕಿತ = 3;
        ಆದರೆ (magic[0] == 0x89 &&
            magic[1] == 'P' &&
            magic[2] == 'N' &&
            magic[3] == 'G' &&
            magic[12] == 'I' &&
            magic[13] == 'H' &&
            magic[14] == 'D' &&
            magic[15] == 'R' &&
            magic[25] == PNG_COLOR_ಸೂಚ್ಯಂಕಿತ) {
            use_palette = true;
        }
    }
    SDL_SeekIO(src, ಆರಂಭ, SDL_IO_SEEK_ಗಣ);

    /* Load the image data */
    rw_callbacks.ಪಠ = IMG_ತುಂಬು_STB_IO_read;
    rw_callbacks.skip = IMG_ತುಂಬು_STB_IO_skip;
    rw_callbacks.eof = IMG_ತುಂಬು_STB_IO_eof;
    w = h = format = 0; /* silence warning */
    ಆದರೆ (use_palette) {
        /* Unused palette entries will be opaque white */
        SDL_memset(palette_colors, 0xff, ಗಾತ್ರ(palette_colors));

        pixels = stbi_ತುಂಬು_from_callbacks_with_palette(
            &rw_callbacks,
            src,
            &w,
            &h,
            palette_colors,
            SDL_arraysize(palette_colors)
        );
    } ಇಲ್ಲದಿದ್ದರೆ {
        pixels = stbi_ತುಂಬು_from_callbacks(
            &rw_callbacks,
            src,
            &w,
            &h,
            &format,
            STBI_default
        );
    }
    ಆದರೆ (!pixels) {
        SDL_SeekIO(src, ಆರಂಭ, SDL_IO_SEEK_ಗಣ);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಆದರೆ (use_palette) {
        surface = SDL_CreateSurfaceFrom(
            w,
            h,
            SDL_PIXELFORMAT_INDEX8,
            pixels,
            w
        );
        ಆದರೆ (surface) {
            bool has_colorkey = false;
            ಪೂರ್ಣಾಂಕ colorkey_ಸೂಚ್ಯಂಕ = -1;
            bool has_alpha = false;
            SDL_Palette *palette = SDL_CreateSurfacePalette(surface);
            ಆದರೆ (palette) {
                ಪೂರ್ಣಾಂಕ i;
                Uint8 *palette_ಬೈಟುಗಳು = (Uint8 *)palette_colors;

                ಗಾಗಿ (i = 0; i < palette->ncolors; i++) {
                    palette->colors[i].r = *palette_ಬೈಟುಗಳು++;
                    palette->colors[i].g = *palette_ಬೈಟುಗಳು++;
                    palette->colors[i].b = *palette_ಬೈಟುಗಳು++;
                    palette->colors[i].a = *palette_ಬೈಟುಗಳು++;
                    ಆದರೆ (palette->colors[i].a != SDL_ALPHA_OPAQUE) {
                        ಆದರೆ (palette->colors[i].a == SDL_ALPHA_TRANSPARENT && !has_colorkey) {
                            has_colorkey = true;
                            colorkey_ಸೂಚ್ಯಂಕ = i;
                        } ಇಲ್ಲದಿದ್ದರೆ {
                            /* Partial opacity or multiple colorkeys */
                            has_alpha = true;
                        }
                    }
                }
            }
            ಆದರೆ (has_alpha) {
                SDL_ಗಣ_Surface_Blend_ಬಹುಲಕ(surface, SDL_BLENDMODE_BLEND);
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (has_colorkey) {
                SDL_ಗಣ_Surface_Color_ಕೀಲಿ(surface, true, colorkey_ಸೂಚ್ಯಂಕ);
            }

            /* FIXME: This sucks. It'd be better to allocate the surface first, then
             * write directly to the pixel buffer:
             * https://github.com/nothings/stb/issues/58
             * -flibit
             */
            surface->flags &= ~SDL_SURFACE_PREALLOCATED;
        }

    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (format == STBI_grey || format == STBI_rgb || format == STBI_rgb_alpha) {
        surface = SDL_CreateSurfaceFrom(
            w,
            h,
            (format == STBI_rgb_alpha) ? SDL_PIXELFORMAT_RGBA32 :
            (format == STBI_rgb) ? SDL_PIXELFORMAT_RGB24 :
            SDL_PIXELFORMAT_INDEX8,
            pixels,
            w * format
        );
        ಆದರೆ (surface) {
            /* Set a grayscale palette for gray images */
            ಆದರೆ (surface->format == SDL_PIXELFORMAT_INDEX8) {
                SDL_Palette *palette = SDL_CreateSurfacePalette(surface);
                ಆದರೆ (palette) {
                    ಪೂರ್ಣಾಂಕ i;

                    ಗಾಗಿ (i = 0; i < palette->ncolors; i++) {
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

    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (format == STBI_grey_alpha) {
        surface = SDL_CreateSurfaceUninitialized(w, h, SDL_PIXELFORMAT_RGBA32);
        ಆದರೆ (surface) {
            Uint8 *src_ptr = pixels;
            Uint8 *dst = (Uint8 *)surface->pixels;
            ಪೂರ್ಣಾಂಕ skip = surface->pitch - (surface->w * 4);
            ಪೂರ್ಣಾಂಕ ಅಡ್ಡಸಾಲು, ಲಂಬಸಾಲು;

            ಗಾಗಿ (ಅಡ್ಡಸಾಲು = 0; ಅಡ್ಡಸಾಲು < h; ++ಅಡ್ಡಸಾಲು) {
                ಗಾಗಿ (ಲಂಬಸಾಲು = 0; ಲಂಬಸಾಲು < w; ++ಲಂಬಸಾಲು) {
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
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_ಗಣ_Error("Unknown image format: %d", format);
    }

    ಆದರೆ (!surface) {
        /* The error message should already be set */
        stbi_image_free(pixels); /* calls SDL_free() */
        SDL_SeekIO(src, ಆರಂಭ, SDL_IO_SEEK_ಗಣ);
    }
    ಹಿಂತಿರುಗಿ surface;
}
#ಆದರೆ_ಅಂತ್ಯ // SDL_HAVE_STB

/* FIXME: This is a copypaste from JPEGLIB! Pull that out of the ifdefs */
/* Define this for quicker (but less perfect) JPEG identification */
#ವ್ಯಾಖ್ಯಾನಿಸು FAST_IS_JPEG

/* See if an image is contained in a data source */
bool SDL_IsJPG(SDL_IOStream *src)
{
    Sint64 ಆರಂಭ;
    bool is_JPG;
    bool ಒಳ_ಪರಿಶೀಲನೆ;
    Uint8 magic[4];

    /* This detection code is by Steaphan Greene <stea@cs.binghamton.edu> */
    /* Blame me, not Sam, if this doesn't work right. */
    /* And don't forget to report the problem to the the sdl list too! */

    ಆದರೆ (!src) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಆರಂಭ = SDL_TellIO(src);
    is_JPG = false;
    ಒಳ_ಪರಿಶೀಲನೆ = false;
    ಆದರೆ (SDL_ReadIO(src, magic, 2) == 2) {
        ಆದರೆ ( (magic[0] == 0xFF) && (magic[1] == 0xD8) ) {
            is_JPG = true;
            ಆಗ (is_JPG) {
                ಆದರೆ (SDL_ReadIO(src, magic, 2) != 2) {
                    is_JPG = false;
                } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ( (magic[0] != 0xFF) && !ಒಳ_ಪರಿಶೀಲನೆ ) {
                    is_JPG = false;
                } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ( (magic[0] != 0xFF) || (magic[1] == 0xFF) ) {
                    /* Extra padding in JPEG (legal) */
                    /* or this is data and we are scanning */
                    SDL_SeekIO(src, -1, SDL_IO_SEEK_CUR);
                } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (magic[1] == 0xD9) {
                    /* Got to end of good JPEG */
                    ನಿಲ್ಲಿಸು;
                } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ( ಒಳ_ಪರಿಶೀಲನೆ && (magic[1] == 0x00) ) {
                    /* This is an encoded 0xFF within the data */
                } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ( (magic[1] >= 0xD0) && (magic[1] < 0xD9) ) {
                    /* These have nothing else */
                } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_ReadIO(src, magic+2, 2) != 2) {
                    is_JPG = false;
                } ಇಲ್ಲದಿದ್ದರೆ {
                    /* Yes, it's big-endian */
                    Sint64 inner_ಆರಂಭ;
                    Uint32 ಗಾತ್ರ_2;
                    Sint64 ಕೊನೆ;
                    inner_ಆರಂಭ = SDL_TellIO(src);
                    ಗಾತ್ರ_2 = (magic[2] << 8) + magic[3];
                    ಕೊನೆ = SDL_SeekIO(src, ಗಾತ್ರ_2-2, SDL_IO_SEEK_CUR);
                    ಆದರೆ ( ಕೊನೆ != inner_ಆರಂಭ + ಗಾತ್ರ_2 - 2 ) {
                        is_JPG = false;
                    }
                    ಆದರೆ ( magic[1] == 0xDA ) {
                        /* Now comes the actual JPEG meat */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ  FAST_IS_JPEG
                        /* Ok, I'm convinced.  It is a JPEG. */
                        ನಿಲ್ಲಿಸು;
#ಇಲ್ಲದಿದ್ದರೆ
                        /* I'm not convinced.  Prove it! */
                        ಒಳ_ಪರಿಶೀಲನೆ = true;
#ಆದರೆ_ಅಂತ್ಯ
                    }
                }
            }
        }
    }
    SDL_SeekIO(src, ಆರಂಭ, SDL_IO_SEEK_ಗಣ);
    ಹಿಂತಿರುಗಿ is_JPG;
}

SDL_Surface *SDL_ತುಂಬು_JPG_IO(SDL_IOStream *src, bool closeio)
{
    SDL_Surface *surface = ಖಾಲಿ;

    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        ಹೋಗು ಮುಗಿದ;
    }

    ಆದರೆ (!SDL_IsJPG(src)) {
        SDL_ಗಣ_Error("File is not a JPEG file");
        ಹೋಗು ಮುಗಿದ;
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_HAVE_STB
    surface = SDL_ತುಂಬು_STB_IO(src);
#ಇಲ್ಲದಿದ್ದರೆ
    SDL_ಗಣ_Error("SDL not built with STB image support");
#ಆದರೆ_ಅಂತ್ಯ // SDL_HAVE_STB

ಮುಗಿದ:
    ಆದರೆ (src && closeio) {
        SDL_CloseIO(src);
    }
    ಹಿಂತಿರುಗಿ surface;
}

SDL_Surface *SDL_ತುಂಬು_JPG(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *file)
{
    SDL_IOStream *ಹರಿವು = SDL_IOFromFile(file, "rb");
    ಆದರೆ (!ಹರಿವು) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಹಿಂತಿರುಗಿ SDL_ತುಂಬು_JPG_IO(ಹರಿವು, true);
}

bool SDL_IsPNG(SDL_IOStream *src)
{
    Sint64 ಆರಂಭ;
    Uint8 magic[4];
    bool is_PNG;

    is_PNG = false;
    ಆರಂಭ = SDL_TellIO(src);
    ಆದರೆ (ಆರಂಭ >= 0) {
        ಆದರೆ (SDL_ReadIO(src, magic, ಗಾತ್ರ(magic)) == ಗಾತ್ರ(magic)) {
            ಆದರೆ (magic[0] == 0x89 &&
                magic[1] == 'P' &&
                magic[2] == 'N' &&
                magic[3] == 'G') {
                is_PNG = true;
            }
        }
        SDL_SeekIO(src, ಆರಂಭ, SDL_IO_SEEK_ಗಣ);
    }

    ಹಿಂತಿರುಗಿ is_PNG;
}

SDL_Surface *SDL_ತುಂಬು_PNG_IO(SDL_IOStream *src, bool closeio)
{
    SDL_Surface *surface = ಖಾಲಿ;

    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        ಹೋಗು ಮುಗಿದ;
    }

    ಆದರೆ (!SDL_IsPNG(src)) {
        SDL_ಗಣ_Error("File is not a PNG file");
        ಹೋಗು ಮುಗಿದ;
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_HAVE_STB
    surface = SDL_ತುಂಬು_STB_IO(src);
#ಇಲ್ಲದಿದ್ದರೆ
    SDL_ಗಣ_Error("SDL not built with STB image support");
#ಆದರೆ_ಅಂತ್ಯ // SDL_HAVE_STB

ಮುಗಿದ:
    ಆದರೆ (src && closeio) {
        SDL_CloseIO(src);
    }
    ಹಿಂತಿರುಗಿ surface;
}

SDL_Surface *SDL_ತುಂಬು_PNG(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *file)
{
    SDL_IOStream *ಹರಿವು = SDL_IOFromFile(file, "rb");
    ಆದರೆ (!ಹರಿವು) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಹಿಂತಿರುಗಿ SDL_ತುಂಬು_PNG_IO(ಹರಿವು, true);
}

bool SDL_SavePNG_IO(SDL_Surface *surface, SDL_IOStream *dst, bool closeio)
{
    bool retval = false;
    Uint8 *plte = ಖಾಲಿ;
    Uint8 *trns = ಖಾಲಿ;
    bool free_surface = false;

    // Make sure we have something to save
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        ಹೋಗು ಮುಗಿದ;
    }
    CHECK_PARAM(!dst) {
        SDL_InvalidParamError("dst");
        ಹೋಗು ಮುಗಿದ;
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_HAVE_STB
    ಪೂರ್ಣಾಂಕ plte_ಗಾತ್ರ = 0;
    ಪೂರ್ಣಾಂಕ trns_ಗಾತ್ರ = 0;

    ಆದರೆ (SDL_ISPIXELFORMAT_ಸೂಚ್ಯಂಕಿತ(surface->format)) {
        ಆದರೆ (!surface->palette) {
            SDL_ಗಣ_Error("Indexed surfaces must have a palette");
            ಹೋಗು ಮುಗಿದ;
        }

        ಆದರೆ (surface->format != SDL_PIXELFORMAT_INDEX8) {
            surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_INDEX8);
            ಆದರೆ (!surface) {
                ಹೋಗು ಮುಗಿದ;
            }
            free_surface = true;
        }

        plte_ಗಾತ್ರ = surface->palette->ncolors * 3;
        trns_ಗಾತ್ರ = surface->palette->ncolors;
        plte = (Uint8 *)SDL_malloc(plte_ಗಾತ್ರ);
        trns = (Uint8 *)SDL_malloc(trns_ಗಾತ್ರ);
        ಆದರೆ (!plte || !trns) {
            ಹೋಗು ಮುಗಿದ;
        }
        SDL_Color *colors = surface->palette->colors;
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < surface->palette->ncolors; ++i) {
            plte[i * 3 + 0] = colors[i].r;
            plte[i * 3 + 1] = colors[i].g;
            plte[i * 3 + 2] = colors[i].b;
            trns[i] = colors[i].a;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (surface->format != SDL_PIXELFORMAT_RGBA32) {
            surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);
            ಆದರೆ (!surface) {
                ಹೋಗು ಮುಗಿದ;
            }
            free_surface = true;
        }
    }

    size_t ಗಾತ್ರ_2 = 0;
    ಶೂನ್ಯ *png = tdefl_write_image_ಗಮ್ಯ_png_file_ಒಳ_ಸ್ಮರಣೆ_ex(surface->pixels, surface->w, surface->h, SDL_BYTESPERPIXEL(surface->format), surface->pitch, &ಗಾತ್ರ_2, 6, MZ_FALSE, plte, plte_ಗಾತ್ರ, trns, trns_ಗಾತ್ರ);
    ಆದರೆ (png) {
        ಆದರೆ (SDL_WriteIO(dst, png, ಗಾತ್ರ_2)) {
            retval = true;
        }
        mz_free(png); /* calls SDL_free() */
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_ಗಣ_Error("Failed to convert and save image");
    }

#ಇಲ್ಲದಿದ್ದರೆ
    SDL_ಗಣ_Error("SDL not built with STB image support");
#ಆದರೆ_ಅಂತ್ಯ

ಮುಗಿದ:
    ಆದರೆ (free_surface) {
        SDL_DestroySurface(surface);
    }
    SDL_free(plte);
    SDL_free(trns);

    ಆದರೆ (dst && closeio) {
        retval &= SDL_CloseIO(dst);
    }
    ಹಿಂತಿರುಗಿ retval;
}

bool SDL_SavePNG(SDL_Surface *surface, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *file)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_HAVE_STB
    // Make sure we have something to save
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("surface");
    }

    ಆದರೆ (SDL_ISPIXELFORMAT_ಸೂಚ್ಯಂಕಿತ(surface->format) && !surface->palette) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Indexed surfaces must have a palette");
    }
    SDL_IOStream *ಹರಿವು = SDL_IOFromFile(file, "wb");
    ಆದರೆ (!ಹರಿವು) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಹಿಂತಿರುಗಿ SDL_SavePNG_IO(surface, ಹರಿವು, true);
#ಇಲ್ಲದಿದ್ದರೆ
    ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("SDL not built with STB image support");
#ಆದರೆ_ಅಂತ್ಯ
}
