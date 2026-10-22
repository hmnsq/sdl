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

#ಅನ್ತರ್ಭಾವ "SDL_pixels_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_yuv_c.h"

#ಅನ್ತರ್ಭಾವ "yuv2rgb/yuv_rgb.h"


ಸ್ಥಿರ bool IsPlanar1x1Format(SDL_PixelFormat format)
{
    ಪ್ರತ್ಯಾಗಮ format == SDL_PIXELFORMAT_I444 || format == SDL_PIXELFORMAT_I4FL;
}

ಸ್ಥಿರ bool IsPlanar2x2Format(SDL_PixelFormat format)
{
    ಪ್ರತ್ಯಾಗಮ format == SDL_PIXELFORMAT_YV12 ||
           format == SDL_PIXELFORMAT_IYUV ||
           format == SDL_PIXELFORMAT_NV12 ||
           format == SDL_PIXELFORMAT_NV21 ||
           format == SDL_PIXELFORMAT_P010 ||
           format == SDL_PIXELFORMAT_I0FL;
}

ಸ್ಥಿರ bool IsPacked4Format(Uint32 format)
{
    ಪ್ರತ್ಯಾಗಮ format == SDL_PIXELFORMAT_YUY2 || format == SDL_PIXELFORMAT_UYVY || format == SDL_PIXELFORMAT_YVYU;
}

/*
 * Calculate YUV size and pitch. Check for overflow.
 * Output 'pitch' that can be used with SDL_ConvertPixels()
 */
bool SDL_CalculateYUVSize(SDL_PixelFormat format, ಪೂರ್ಣಾಙ್ಕ w, ಪೂರ್ಣಾಙ್ಕ h, size_t *size, size_t *pitch)
{
    ಪೂರ್ಣಾಙ್ಕ sz_plane = 0, sz_plane_chroma = 0, sz_plane_packed = 0;

    ಯದಿ (IsPlanar1x1Format(format)) {
        /* sz_plane == w * h * bpp; */
        size_t s1;
        ಯದಿ (!SDL_size_mul_check_overflow(w, h, &s1)) {
            ಪ್ರತ್ಯಾಗಮ SDL_SetError("width * height would overflow");
        }
        ಯದಿ (!SDL_size_mul_check_overflow(s1, SDL_BYTESPERPIXEL(format), &s1)) {
            ಪ್ರತ್ಯಾಗಮ SDL_SetError("width * height * bpp would overflow");
        }
        sz_plane = (ಪೂರ್ಣಾಙ್ಕ)s1;
        sz_plane_chroma = sz_plane;
    } ಅನ್ಯಥಾ ಯದಿ (IsPlanar2x2Format(format)) {
        {
            /* sz_plane == w * h * bpp; */
            size_t s1;
            ಯದಿ (!SDL_size_mul_check_overflow(w, h, &s1)) {
                ಪ್ರತ್ಯಾಗಮ SDL_SetError("width * height would overflow");
            }
            ಯದಿ (!SDL_size_mul_check_overflow(s1, SDL_BYTESPERPIXEL(format), &s1)) {
                ಪ್ರತ್ಯಾಗಮ SDL_SetError("width * height * bpp would overflow");
            }
            sz_plane = (ಪೂರ್ಣಾಙ್ಕ)s1;
        }

        {
            /* sz_plane_chroma == ((w + 1) / 2) * ((h + 1) / 2) * bpp; */
            size_t s1, s2, s3;
            ಯದಿ (!SDL_size_add_check_overflow(w, 1, &s1)) {
                ಪ್ರತ್ಯಾಗಮ SDL_SetError("width + 1 would overflow");
            }
            s1 = s1 / 2;
            ಯದಿ (!SDL_size_add_check_overflow(h, 1, &s2)) {
                ಪ್ರತ್ಯಾಗಮ SDL_SetError("height + 1 would overflow");
            }
            s2 = s2 / 2;
            ಯದಿ (!SDL_size_mul_check_overflow(s1, s2, &s3)) {
                ಪ್ರತ್ಯಾಗಮ SDL_SetError("width * height would overflow");
            }
            ಯದಿ (!SDL_size_mul_check_overflow(s3, SDL_BYTESPERPIXEL(format), &s3)) {
                ಪ್ರತ್ಯಾಗಮ SDL_SetError("width * height * bpp would overflow");
            }
            sz_plane_chroma = (ಪೂರ್ಣಾಙ್ಕ)s3;
        }
    } ಅನ್ಯಥಾ ಯದಿ (IsPacked4Format(format)) {
        /* sz_plane_packed == ((w + 1) / 2) * h; */
        size_t s1, s2;
        ಯದಿ (!SDL_size_add_check_overflow(w, 1, &s1)) {
            ಪ್ರತ್ಯಾಗಮ SDL_SetError("width + 1 would overflow");
        }
        s1 = s1 / 2;
        ಯದಿ (!SDL_size_mul_check_overflow(s1, h, &s2)) {
            ಪ್ರತ್ಯಾಗಮ SDL_SetError("width * height would overflow");
        }
        sz_plane_packed = (ಪೂರ್ಣಾಙ್ಕ) s2;
    } ಅನ್ಯಥಾ {
        ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
    }

    ವಿಕಲ್ಪ (format) {
    ಪಕ್ಷ SDL_PIXELFORMAT_YV12: /**< Planar mode: Y + V + U  (3 planes) */
    ಪಕ್ಷ SDL_PIXELFORMAT_IYUV: /**< Planar mode: Y + U + V  (3 planes) */
    ಪಕ್ಷ SDL_PIXELFORMAT_I444: /**< Planar mode: Y + U + V  (3 planes) */
    ಪಕ್ಷ SDL_PIXELFORMAT_I0FL: /**< Planar mode: Y + U + V  (3 planes) */
    ಪಕ್ಷ SDL_PIXELFORMAT_I4FL: /**< Planar mode: Y + U + V  (3 planes) */

        ಯದಿ (pitch) {
            *pitch = w * SDL_BYTESPERPIXEL(format);
        }

        ಯದಿ (size) {
            // dst_size == sz_plane + sz_plane_chroma + sz_plane_chroma;
            size_t s1, s2;
            ಯದಿ (!SDL_size_add_check_overflow(sz_plane, sz_plane_chroma, &s1)) {
                ಪ್ರತ್ಯಾಗಮ SDL_SetError("Y + U would overflow");
            }
            ಯದಿ (!SDL_size_add_check_overflow(s1, sz_plane_chroma, &s2)) {
                ಪ್ರತ್ಯಾಗಮ SDL_SetError("Y + U + V would overflow");
            }
            *size = (ಪೂರ್ಣಾಙ್ಕ)s2;
        }
        ಭಙ್ಗ;

    ಪಕ್ಷ SDL_PIXELFORMAT_YUY2: /**< Packed mode: Y0+U0+Y1+V0 (1 plane) */
    ಪಕ್ಷ SDL_PIXELFORMAT_UYVY: /**< Packed mode: U0+Y0+V0+Y1 (1 plane) */
    ಪಕ್ಷ SDL_PIXELFORMAT_YVYU: /**< Packed mode: Y0+V0+Y1+U0 (1 plane) */

        ಯದಿ (pitch) {
            /* pitch == ((w + 1) / 2) * 4; */
           size_t p1, p2;
           ಯದಿ (!SDL_size_add_check_overflow(w, 1, &p1)) {
               ಪ್ರತ್ಯಾಗಮ SDL_SetError("width + 1 would overflow");
           }
           p1 = p1 / 2;
           ಯದಿ (!SDL_size_mul_check_overflow(p1, 4, &p2)) {
               ಪ್ರತ್ಯಾಗಮ SDL_SetError("width * 4 would overflow");
           }
           *pitch = p2;
        }

        ಯದಿ (size) {
            /* dst_size == 4 * sz_plane_packed; */
            size_t s1;
            ಯದಿ (!SDL_size_mul_check_overflow(sz_plane_packed, 4, &s1)) {
                ಪ್ರತ್ಯಾಗಮ SDL_SetError("plane * 4 would overflow");
            }
            *size = (ಪೂರ್ಣಾಙ್ಕ) s1;
        }
        ಭಙ್ಗ;

    ಪಕ್ಷ SDL_PIXELFORMAT_NV12: /**< Planar mode: Y + U/V interleaved  (2 planes) */
    ಪಕ್ಷ SDL_PIXELFORMAT_NV21: /**< Planar mode: Y + V/U interleaved  (2 planes) */
    ಪಕ್ಷ SDL_PIXELFORMAT_P010: /**< Planar mode: Y + U/V interleaved, 10 bit  (2 planes) */
        ಯದಿ (pitch) {
            *pitch = w * SDL_BYTESPERPIXEL(format);
        }

        ಯದಿ (size) {
            // dst_size == sz_plane + sz_plane_chroma + sz_plane_chroma;
            size_t s1, s2;
            ಯದಿ (!SDL_size_add_check_overflow(sz_plane, sz_plane_chroma, &s1)) {
                ಪ್ರತ್ಯಾಗಮ SDL_SetError("Y + U would overflow");
            }
            ಯದಿ (!SDL_size_add_check_overflow(s1, sz_plane_chroma, &s2)) {
                ಪ್ರತ್ಯಾಗಮ SDL_SetError("Y + U + V would overflow");
            }
            *size = (ಪೂರ್ಣಾಙ್ಕ) s2;
        }
        ಭಙ್ಗ;

    ಸ್ವಭಾವ:
        ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
    }

    ಪ್ರತ್ಯಾಗಮ true;
}

#ifdef SDL_HAVE_YUV

ಸ್ಥಿರ bool GetYUVConversionType(SDL_Colorspace colorspace, ಪೂರ್ಣಾಙ್ಕ w, ಪೂರ್ಣಾಙ್ಕ h, ಪೂರ್ಣಾಙ್ಕ bits_per_pixel, YCbCrType *yuv_type)
{
    ಯದಿ (SDL_ISCOLORSPACE_MATRIX_BT601(colorspace)) {
        ಯದಿ (SDL_ISCOLORSPACE_LIMITED_RANGE(colorspace)) {
            *yuv_type = YCBCR_601_LIMITED;
        } ಅನ್ಯಥಾ {
            *yuv_type = YCBCR_601_FULL;
        }
        ಪ್ರತ್ಯಾಗಮ true;
    }

    ಯದಿ (SDL_ISCOLORSPACE_MATRIX_BT709(colorspace)) {
        ಯದಿ (SDL_ISCOLORSPACE_LIMITED_RANGE(colorspace)) {
            *yuv_type = YCBCR_709_LIMITED;
        } ಅನ್ಯಥಾ {
            *yuv_type = YCBCR_709_FULL;
        }
        ಪ್ರತ್ಯಾಗಮ true;
    }

    ಯದಿ (SDL_ISCOLORSPACE_MATRIX_BT2020_NCL(colorspace)) {
        ಯದಿ (SDL_ISCOLORSPACE_FULL_RANGE(colorspace)) {
            *yuv_type = YCBCR_2020_NCL_FULL;
            ಪ್ರತ್ಯಾಗಮ true;
        }
    }

    ಯದಿ (SDL_COLORSPACEMATRIX(colorspace) == SDL_MATRIX_COEFFICIENTS_UNSPECIFIED) {
        ವಿಕಲ್ಪ (bits_per_pixel) {
        ಪಕ್ಷ 8:
            ಯದಿ (h <= YUV_SD_THRESHOLD) {
                ಯದಿ (SDL_ISCOLORSPACE_LIMITED_RANGE(colorspace)) {
                    *yuv_type = YCBCR_601_LIMITED;
                } ಅನ್ಯಥಾ {
                    *yuv_type = YCBCR_601_FULL;
                }
            } ಅನ್ಯಥಾ {
                ಯದಿ (SDL_ISCOLORSPACE_LIMITED_RANGE(colorspace)) {
                    *yuv_type = YCBCR_709_LIMITED;
                } ಅನ್ಯಥಾ {
                    *yuv_type = YCBCR_709_FULL;
                }
            }
			ಪ್ರತ್ಯಾಗಮ true;
        ಪಕ್ಷ 10:
        ಪಕ್ಷ 16:
            ಯದಿ (SDL_ISCOLORSPACE_FULL_RANGE(colorspace)) {
                *yuv_type = YCBCR_2020_NCL_FULL;
                ಪ್ರತ್ಯಾಗಮ true;
            }
            ಭಙ್ಗ;
        ಸ್ವಭಾವ:
            ಭಙ್ಗ;
        }
    }

    ಪ್ರತ್ಯಾಗಮ SDL_SetError("Unsupported YUV colorspace");
}

ಸ್ಥಿರ bool GetYUVPlanes(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, SDL_PixelFormat format, ಧ್ರುವ ಶೂನ್ಯ *yuv, ಪೂರ್ಣಾಙ್ಕ yuv_pitch,
                         ಧ್ರುವ Uint8 **y, ಧ್ರುವ Uint8 **u, ಧ್ರುವ Uint8 **v, Uint32 *y_stride, Uint32 *uv_stride)
{
    ಧ್ರುವ Uint8 *planes[3] = { ರಿಕ್ತ, ರಿಕ್ತ, ರಿಕ್ತ };
    ಪೂರ್ಣಾಙ್ಕ pitches[3] = { 0, 0, 0 };
    ಪೂರ್ಣಾಙ್ಕ uv_width;

    ವಿಕಲ್ಪ (format) {
    ಪಕ್ಷ SDL_PIXELFORMAT_YV12:
    ಪಕ್ಷ SDL_PIXELFORMAT_IYUV:
    ಪಕ್ಷ SDL_PIXELFORMAT_I0FL:
        pitches[0] = yuv_pitch;
        pitches[1] = ((pitches[0] / SDL_BYTESPERPIXEL(format) + 1) / 2) * SDL_BYTESPERPIXEL(format);
        pitches[2] = pitches[1];
        planes[0] = (ಧ್ರುವ Uint8 *)yuv;
        planes[1] = planes[0] + pitches[0] * height;
        planes[2] = planes[1] + pitches[1] * ((height + 1) / 2);
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_PIXELFORMAT_YUY2:
    ಪಕ್ಷ SDL_PIXELFORMAT_UYVY:
    ಪಕ್ಷ SDL_PIXELFORMAT_YVYU:
        pitches[0] = yuv_pitch;
        planes[0] = (ಧ್ರುವ Uint8 *)yuv;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_PIXELFORMAT_NV12:
    ಪಕ್ಷ SDL_PIXELFORMAT_NV21:
        pitches[0] = yuv_pitch;
        pitches[1] = 2 * ((pitches[0] + 1) / 2);
        planes[0] = (ಧ್ರುವ Uint8 *)yuv;
        planes[1] = planes[0] + pitches[0] * height;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_PIXELFORMAT_P010:
        pitches[0] = yuv_pitch;
        uv_width = ((width + 1) / 2) * 2;
        pitches[1] = SDL_max(pitches[0], (ಪೂರ್ಣಾಙ್ಕ)(uv_width * ಪರಿಮಾಣ(Uint16)));
        planes[0] = (ಧ್ರುವ Uint8 *)yuv;
        planes[1] = planes[0] + pitches[0] * height;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_PIXELFORMAT_I444:
    ಪಕ್ಷ SDL_PIXELFORMAT_I4FL:
        pitches[0] = yuv_pitch;
        pitches[1] = pitches[0];
        pitches[2] = pitches[1];
        planes[0] = (ಧ್ರುವ Uint8 *)yuv;
        planes[1] = planes[0] + pitches[0] * height;
        planes[2] = planes[1] + pitches[1] * height;
        ಭಙ್ಗ;
    ಸ್ವಭಾವ:
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("GetYUVPlanes(): Unsupported YUV format: %s", SDL_GetPixelFormatName(format));
    }

    ವಿಕಲ್ಪ (format) {
    ಪಕ್ಷ SDL_PIXELFORMAT_YV12:
        *y = planes[0];
        *y_stride = pitches[0];
        *v = planes[1];
        *u = planes[2];
        *uv_stride = pitches[1];
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_PIXELFORMAT_IYUV:
    ಪಕ್ಷ SDL_PIXELFORMAT_I444:
    ಪಕ್ಷ SDL_PIXELFORMAT_I0FL:
    ಪಕ್ಷ SDL_PIXELFORMAT_I4FL:
        *y = planes[0];
        *y_stride = pitches[0];
        *v = planes[2];
        *u = planes[1];
        *uv_stride = pitches[1];
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_PIXELFORMAT_YUY2:
        *y = planes[0];
        *y_stride = pitches[0];
        *v = *y + 3;
        *u = *y + 1;
        *uv_stride = pitches[0];
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_PIXELFORMAT_UYVY:
        *y = planes[0] + 1;
        *y_stride = pitches[0];
        *v = *y + 1;
        *u = *y - 1;
        *uv_stride = pitches[0];
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_PIXELFORMAT_YVYU:
        *y = planes[0];
        *y_stride = pitches[0];
        *v = *y + 1;
        *u = *y + 3;
        *uv_stride = pitches[0];
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_PIXELFORMAT_NV12:
        *y = planes[0];
        *y_stride = pitches[0];
        *u = planes[1];
        *v = *u + 1;
        *uv_stride = pitches[1];
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_PIXELFORMAT_NV21:
        *y = planes[0];
        *y_stride = pitches[0];
        *v = planes[1];
        *u = *v + 1;
        *uv_stride = pitches[1];
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_PIXELFORMAT_P010:
        *y = planes[0];
        *y_stride = pitches[0];
        *u = planes[1];
        *v = *u + ಪರಿಮಾಣ(Uint16);
        *uv_stride = pitches[1];
        ಭಙ್ಗ;
    ಸ್ವಭಾವ:
        // Should have caught this above
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("GetYUVPlanes[2]: Unsupported YUV format: %s", SDL_GetPixelFormatName(format));
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

#ifdef SDL_SSE2_INTRINSICS
ಸ್ಥಿರ bool SDL_TARGETING("sse2") yuv_rgb_sse(
    SDL_PixelFormat src_format, SDL_PixelFormat dst_format,
    Uint32 width, Uint32 height,
    ಧ್ರುವ Uint8 *y, ಧ್ರುವ Uint8 *u, ಧ್ರುವ Uint8 *v, Uint32 y_stride, Uint32 uv_stride,
    Uint8 *rgb, Uint32 rgb_stride,
    YCbCrType yuv_type)
{
    ಯದಿ (!SDL_HasSSE2()) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    ಯದಿ (src_format == SDL_PIXELFORMAT_YV12 ||
        src_format == SDL_PIXELFORMAT_IYUV) {

        ವಿಕಲ್ಪ (dst_format) {
        ಪಕ್ಷ SDL_PIXELFORMAT_RGB565:
            yuv420_rgb565_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಪ್ರತ್ಯಾಗಮ true;
        ಪಕ್ಷ SDL_PIXELFORMAT_RGB24:
            yuv420_rgb24_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಪ್ರತ್ಯಾಗಮ true;
        ಪಕ್ಷ SDL_PIXELFORMAT_RGBX8888:
        ಪಕ್ಷ SDL_PIXELFORMAT_RGBA8888:
            yuv420_rgba_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಪ್ರತ್ಯಾಗಮ true;
        ಪಕ್ಷ SDL_PIXELFORMAT_BGRX8888:
        ಪಕ್ಷ SDL_PIXELFORMAT_BGRA8888:
            yuv420_bgra_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಪ್ರತ್ಯಾಗಮ true;
        ಪಕ್ಷ SDL_PIXELFORMAT_XRGB8888:
        ಪಕ್ಷ SDL_PIXELFORMAT_ARGB8888:
            yuv420_argb_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಪ್ರತ್ಯಾಗಮ true;
        ಪಕ್ಷ SDL_PIXELFORMAT_XBGR8888:
        ಪಕ್ಷ SDL_PIXELFORMAT_ABGR8888:
            yuv420_abgr_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಪ್ರತ್ಯಾಗಮ true;
        ಸ್ವಭಾವ:
            ಭಙ್ಗ;
        }
    }

    ಯದಿ (src_format == SDL_PIXELFORMAT_YUY2 ||
        src_format == SDL_PIXELFORMAT_UYVY ||
        src_format == SDL_PIXELFORMAT_YVYU) {

        ವಿಕಲ್ಪ (dst_format) {
        ಪಕ್ಷ SDL_PIXELFORMAT_RGB565:
            yuv422_rgb565_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಪ್ರತ್ಯಾಗಮ true;
        ಪಕ್ಷ SDL_PIXELFORMAT_RGB24:
            yuv422_rgb24_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಪ್ರತ್ಯಾಗಮ true;
        ಪಕ್ಷ SDL_PIXELFORMAT_RGBX8888:
        ಪಕ್ಷ SDL_PIXELFORMAT_RGBA8888:
            yuv422_rgba_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಪ್ರತ್ಯಾಗಮ true;
        ಪಕ್ಷ SDL_PIXELFORMAT_BGRX8888:
        ಪಕ್ಷ SDL_PIXELFORMAT_BGRA8888:
            yuv422_bgra_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಪ್ರತ್ಯಾಗಮ true;
        ಪಕ್ಷ SDL_PIXELFORMAT_XRGB8888:
        ಪಕ್ಷ SDL_PIXELFORMAT_ARGB8888:
            yuv422_argb_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಪ್ರತ್ಯಾಗಮ true;
        ಪಕ್ಷ SDL_PIXELFORMAT_XBGR8888:
        ಪಕ್ಷ SDL_PIXELFORMAT_ABGR8888:
            yuv422_abgr_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಪ್ರತ್ಯಾಗಮ true;
        ಸ್ವಭಾವ:
            ಭಙ್ಗ;
        }
    }

    ಯದಿ (src_format == SDL_PIXELFORMAT_NV12 ||
        src_format == SDL_PIXELFORMAT_NV21) {

        ವಿಕಲ್ಪ (dst_format) {
        ಪಕ್ಷ SDL_PIXELFORMAT_RGB565:
            yuvnv12_rgb565_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಪ್ರತ್ಯಾಗಮ true;
        ಪಕ್ಷ SDL_PIXELFORMAT_RGB24:
            yuvnv12_rgb24_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಪ್ರತ್ಯಾಗಮ true;
        ಪಕ್ಷ SDL_PIXELFORMAT_RGBX8888:
        ಪಕ್ಷ SDL_PIXELFORMAT_RGBA8888:
            yuvnv12_rgba_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಪ್ರತ್ಯಾಗಮ true;
        ಪಕ್ಷ SDL_PIXELFORMAT_BGRX8888:
        ಪಕ್ಷ SDL_PIXELFORMAT_BGRA8888:
            yuvnv12_bgra_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಪ್ರತ್ಯಾಗಮ true;
        ಪಕ್ಷ SDL_PIXELFORMAT_XRGB8888:
        ಪಕ್ಷ SDL_PIXELFORMAT_ARGB8888:
            yuvnv12_argb_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಪ್ರತ್ಯಾಗಮ true;
        ಪಕ್ಷ SDL_PIXELFORMAT_XBGR8888:
        ಪಕ್ಷ SDL_PIXELFORMAT_ABGR8888:
            yuvnv12_abgr_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಪ್ರತ್ಯಾಗಮ true;
        ಸ್ವಭಾವ:
            ಭಙ್ಗ;
        }
    }
    ಪ್ರತ್ಯಾಗಮ false;
}
#ಅನ್ಯಥಾ
ಸ್ಥಿರ bool yuv_rgb_sse(
    SDL_PixelFormat src_format, SDL_PixelFormat dst_format,
    Uint32 width, Uint32 height,
    ಧ್ರುವ Uint8 *y, ಧ್ರುವ Uint8 *u, ಧ್ರುವ Uint8 *v, Uint32 y_stride, Uint32 uv_stride,
    Uint8 *rgb, Uint32 rgb_stride,
    YCbCrType yuv_type)
{
    ಪ್ರತ್ಯಾಗಮ false;
}
#endif

#ifdef SDL_LSX_INTRINSICS
ಸ್ಥಿರ bool yuv_rgb_lsx(
    SDL_PixelFormat src_format, SDL_PixelFormat dst_format,
    Uint32 width, Uint32 height,
    ಧ್ರುವ Uint8 *y, ಧ್ರುವ Uint8 *u, ಧ್ರುವ Uint8 *v, Uint32 y_stride, Uint32 uv_stride,
    Uint8 *rgb, Uint32 rgb_stride,
    YCbCrType yuv_type)
{
    ಯದಿ (!SDL_HasLSX()) {
        ಪ್ರತ್ಯಾಗಮ false;
    }
    ಯದಿ (src_format == SDL_PIXELFORMAT_YV12 ||
        src_format == SDL_PIXELFORMAT_IYUV) {

        ವಿಕಲ್ಪ (dst_format) {
        ಪಕ್ಷ SDL_PIXELFORMAT_RGB24:
            yuv420_rgb24_lsx(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಪ್ರತ್ಯಾಗಮ true;
        ಪಕ್ಷ SDL_PIXELFORMAT_RGBX8888:
        ಪಕ್ಷ SDL_PIXELFORMAT_RGBA8888:
            yuv420_rgba_lsx(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಪ್ರತ್ಯಾಗಮ true;
        ಪಕ್ಷ SDL_PIXELFORMAT_BGRX8888:
        ಪಕ್ಷ SDL_PIXELFORMAT_BGRA8888:
            yuv420_bgra_lsx(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಪ್ರತ್ಯಾಗಮ true;
        ಪಕ್ಷ SDL_PIXELFORMAT_XRGB8888:
        ಪಕ್ಷ SDL_PIXELFORMAT_ARGB8888:
            yuv420_argb_lsx(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಪ್ರತ್ಯಾಗಮ true;
        ಪಕ್ಷ SDL_PIXELFORMAT_XBGR8888:
        ಪಕ್ಷ SDL_PIXELFORMAT_ABGR8888:
            yuv420_abgr_lsx(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಪ್ರತ್ಯಾಗಮ true;
        ಸ್ವಭಾವ:
            ಭಙ್ಗ;
        }
    }
    ಪ್ರತ್ಯಾಗಮ false;
}
#ಅನ್ಯಥಾ
ಸ್ಥಿರ bool yuv_rgb_lsx(
    SDL_PixelFormat src_format, SDL_PixelFormat dst_format,
    Uint32 width, Uint32 height,
    ಧ್ರುವ Uint8 *y, ಧ್ರುವ Uint8 *u, ಧ್ರುವ Uint8 *v, Uint32 y_stride, Uint32 uv_stride,
    Uint8 *rgb, Uint32 rgb_stride,
    YCbCrType yuv_type)
{
    ಪ್ರತ್ಯಾಗಮ false;
}
#endif

ಸ್ಥಿರ bool yuv_rgb_std(
    SDL_PixelFormat src_format, SDL_PixelFormat dst_format,
    Uint32 width, Uint32 height,
    ಧ್ರುವ Uint8 *y, ಧ್ರುವ Uint8 *u, ಧ್ರುವ Uint8 *v, Uint32 y_stride, Uint32 uv_stride,
    Uint8 *rgb, Uint32 rgb_stride,
    YCbCrType yuv_type)
{
    ಯದಿ (src_format == SDL_PIXELFORMAT_YV12 ||
        src_format == SDL_PIXELFORMAT_IYUV) {

        ವಿಕಲ್ಪ (dst_format) {
        ಪಕ್ಷ SDL_PIXELFORMAT_RGB565:
            yuv420_rgb565_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಪ್ರತ್ಯಾಗಮ true;
        ಪಕ್ಷ SDL_PIXELFORMAT_RGB24:
            yuv420_rgb24_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಪ್ರತ್ಯಾಗಮ true;
        ಪಕ್ಷ SDL_PIXELFORMAT_RGBX8888:
        ಪಕ್ಷ SDL_PIXELFORMAT_RGBA8888:
            yuv420_rgba_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಪ್ರತ್ಯಾಗಮ true;
        ಪಕ್ಷ SDL_PIXELFORMAT_BGRX8888:
        ಪಕ್ಷ SDL_PIXELFORMAT_BGRA8888:
            yuv420_bgra_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಪ್ರತ್ಯಾಗಮ true;
        ಪಕ್ಷ SDL_PIXELFORMAT_XRGB8888:
        ಪಕ್ಷ SDL_PIXELFORMAT_ARGB8888:
            yuv420_argb_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಪ್ರತ್ಯಾಗಮ true;
        ಪಕ್ಷ SDL_PIXELFORMAT_XBGR8888:
        ಪಕ್ಷ SDL_PIXELFORMAT_ABGR8888:
            yuv420_abgr_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಪ್ರತ್ಯಾಗಮ true;
        ಸ್ವಭಾವ:
            ಭಙ್ಗ;
        }
    }

    ಯದಿ (src_format == SDL_PIXELFORMAT_I444) {

        ವಿಕಲ್ಪ (dst_format) {
        ಪಕ್ಷ SDL_PIXELFORMAT_RGBX8888:
        ಪಕ್ಷ SDL_PIXELFORMAT_RGBA8888:
            yuv444_rgba_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಪ್ರತ್ಯಾಗಮ true;
        ಪಕ್ಷ SDL_PIXELFORMAT_BGRX8888:
        ಪಕ್ಷ SDL_PIXELFORMAT_BGRA8888:
            yuv444_bgra_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಪ್ರತ್ಯಾಗಮ true;
        ಪಕ್ಷ SDL_PIXELFORMAT_XRGB8888:
        ಪಕ್ಷ SDL_PIXELFORMAT_ARGB8888:
            yuv444_argb_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಪ್ರತ್ಯಾಗಮ true;
        ಪಕ್ಷ SDL_PIXELFORMAT_XBGR8888:
        ಪಕ್ಷ SDL_PIXELFORMAT_ABGR8888:
            yuv444_abgr_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಪ್ರತ್ಯಾಗಮ true;
        ಸ್ವಭಾವ:
            ಭಙ್ಗ;
        }
    }

    ಯದಿ (src_format == SDL_PIXELFORMAT_YUY2 ||
        src_format == SDL_PIXELFORMAT_UYVY ||
        src_format == SDL_PIXELFORMAT_YVYU) {

        ವಿಕಲ್ಪ (dst_format) {
        ಪಕ್ಷ SDL_PIXELFORMAT_RGB565:
            yuv422_rgb565_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಪ್ರತ್ಯಾಗಮ true;
        ಪಕ್ಷ SDL_PIXELFORMAT_RGB24:
            yuv422_rgb24_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಪ್ರತ್ಯಾಗಮ true;
        ಪಕ್ಷ SDL_PIXELFORMAT_RGBX8888:
        ಪಕ್ಷ SDL_PIXELFORMAT_RGBA8888:
            yuv422_rgba_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಪ್ರತ್ಯಾಗಮ true;
        ಪಕ್ಷ SDL_PIXELFORMAT_BGRX8888:
        ಪಕ್ಷ SDL_PIXELFORMAT_BGRA8888:
            yuv422_bgra_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಪ್ರತ್ಯಾಗಮ true;
        ಪಕ್ಷ SDL_PIXELFORMAT_XRGB8888:
        ಪಕ್ಷ SDL_PIXELFORMAT_ARGB8888:
            yuv422_argb_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಪ್ರತ್ಯಾಗಮ true;
        ಪಕ್ಷ SDL_PIXELFORMAT_XBGR8888:
        ಪಕ್ಷ SDL_PIXELFORMAT_ABGR8888:
            yuv422_abgr_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಪ್ರತ್ಯಾಗಮ true;
        ಸ್ವಭಾವ:
            ಭಙ್ಗ;
        }
    }

    ಯದಿ (src_format == SDL_PIXELFORMAT_NV12 ||
        src_format == SDL_PIXELFORMAT_NV21) {

        ವಿಕಲ್ಪ (dst_format) {
        ಪಕ್ಷ SDL_PIXELFORMAT_RGB565:
            yuvnv12_rgb565_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಪ್ರತ್ಯಾಗಮ true;
        ಪಕ್ಷ SDL_PIXELFORMAT_RGB24:
            yuvnv12_rgb24_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಪ್ರತ್ಯಾಗಮ true;
        ಪಕ್ಷ SDL_PIXELFORMAT_RGBX8888:
        ಪಕ್ಷ SDL_PIXELFORMAT_RGBA8888:
            yuvnv12_rgba_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಪ್ರತ್ಯಾಗಮ true;
        ಪಕ್ಷ SDL_PIXELFORMAT_BGRX8888:
        ಪಕ್ಷ SDL_PIXELFORMAT_BGRA8888:
            yuvnv12_bgra_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಪ್ರತ್ಯಾಗಮ true;
        ಪಕ್ಷ SDL_PIXELFORMAT_XRGB8888:
        ಪಕ್ಷ SDL_PIXELFORMAT_ARGB8888:
            yuvnv12_argb_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಪ್ರತ್ಯಾಗಮ true;
        ಪಕ್ಷ SDL_PIXELFORMAT_XBGR8888:
        ಪಕ್ಷ SDL_PIXELFORMAT_ABGR8888:
            yuvnv12_abgr_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಪ್ರತ್ಯಾಗಮ true;
        ಸ್ವಭಾವ:
            ಭಙ್ಗ;
        }
    }

    ಯದಿ (src_format == SDL_PIXELFORMAT_P010) {
        ವಿಕಲ್ಪ (dst_format) {
        ಪಕ್ಷ SDL_PIXELFORMAT_XBGR2101010:
            yuvp010_xbgr2101010_std(width, height, (ಧ್ರುವ uint16_t *)y, (ಧ್ರುವ uint16_t *)u, (ಧ್ರುವ uint16_t *)v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಪ್ರತ್ಯಾಗಮ true;
        ಸ್ವಭಾವ:
            ಭಙ್ಗ;
        }
    }

    ಯದಿ (src_format == SDL_PIXELFORMAT_I0FL) {
        ವಿಕಲ್ಪ (dst_format) {
        ಪಕ್ಷ SDL_PIXELFORMAT_RGB48:
            yuvi0fl_rgb48_std(width, height, (ಧ್ರುವ uint16_t *)y, (ಧ್ರುವ uint16_t *)u, (ಧ್ರುವ uint16_t *)v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಪ್ರತ್ಯಾಗಮ true;
        ಸ್ವಭಾವ:
            ಭಙ್ಗ;
        }
    }

    ಯದಿ (src_format == SDL_PIXELFORMAT_I4FL) {
        ವಿಕಲ್ಪ (dst_format) {
        ಪಕ್ಷ SDL_PIXELFORMAT_RGB48:
            yuvi4fl_rgb48_std(width, height, (ಧ್ರುವ uint16_t *)y, (ಧ್ರುವ uint16_t *)u, (ಧ್ರುವ uint16_t *)v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಪ್ರತ್ಯಾಗಮ true;
        ಸ್ವಭಾವ:
            ಭಙ್ಗ;
        }
    }
    ಪ್ರತ್ಯಾಗಮ false;
}

bool SDL_ConvertPixels_YUV_to_RGB(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height,
                                  SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ಧ್ರುವ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಙ್ಕ src_pitch,
                                  SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಙ್ಕ dst_pitch)
{
    ಧ್ರುವ Uint8 *y = ರಿಕ್ತ;
    ಧ್ರುವ Uint8 *u = ರಿಕ್ತ;
    ಧ್ರುವ Uint8 *v = ರಿಕ್ತ;
    Uint32 y_stride = 0;
    Uint32 uv_stride = 0;
    YCbCrType yuv_type = YCBCR_601_LIMITED;

    ಯದಿ (!GetYUVPlanes(width, height, src_format, src, src_pitch, &y, &u, &v, &y_stride, &uv_stride)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    ಯದಿ (!GetYUVConversionType(src_colorspace, width, height, 8, &yuv_type)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    ಯದಿ (yuv_rgb_sse(src_format, dst_format, width, height, y, u, v, y_stride, uv_stride, (Uint8 *)dst, dst_pitch, yuv_type)) {
        ಪ್ರತ್ಯಾಗಮ true;
    }

    ಯದಿ (yuv_rgb_lsx(src_format, dst_format, width, height, y, u, v, y_stride, uv_stride, (Uint8 *)dst, dst_pitch, yuv_type)) {
        ಪ್ರತ್ಯಾಗಮ true;
    }

    ಯದಿ (yuv_rgb_std(src_format, dst_format, width, height, y, u, v, y_stride, uv_stride, (Uint8 *)dst, dst_pitch, yuv_type)) {
        ಪ್ರತ್ಯಾಗಮ true;
    }

    // No fast path for the RGB format, instead convert using an intermediate buffer
    ಯದಿ (src_format == SDL_PIXELFORMAT_P010 && dst_format != SDL_PIXELFORMAT_XBGR2101010) {
        bool result;
        ಶೂನ್ಯ *tmp;
        ಪೂರ್ಣಾಙ್ಕ tmp_pitch = (width * ಪರಿಮಾಣ(Uint32));

        tmp = SDL_malloc((size_t)tmp_pitch * height);
        ಯದಿ (!tmp) {
            ಪ್ರತ್ಯಾಗಮ false;
        }

        // convert src/src_format to tmp/XBGR2101010
        result = SDL_ConvertPixels_YUV_to_RGB(width, height, src_format, src_colorspace, src_properties, src, src_pitch, SDL_PIXELFORMAT_XBGR2101010, src_colorspace, src_properties, tmp, tmp_pitch);
        ಯದಿ (!result) {
            SDL_free(tmp);
            ಪ್ರತ್ಯಾಗಮ false;
        }

        // convert tmp/XBGR2101010 to dst/RGB
        result = SDL_ConvertPixelsAndColorspace(width, height, SDL_PIXELFORMAT_XBGR2101010, src_colorspace, src_properties, tmp, tmp_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
        SDL_free(tmp);
        ಪ್ರತ್ಯಾಗಮ result;
    }

    ಯದಿ ((src_format == SDL_PIXELFORMAT_I0FL || src_format == SDL_PIXELFORMAT_I4FL) && dst_format != SDL_PIXELFORMAT_RGB48) {
        bool result;
        ಶೂನ್ಯ *tmp;
        ಪೂರ್ಣಾಙ್ಕ tmp_pitch = (width * 3 * ಪರಿಮಾಣ(Uint16));

        tmp = SDL_malloc((size_t)tmp_pitch * height);
        ಯದಿ (!tmp) {
            ಪ್ರತ್ಯಾಗಮ false;
        }

        // convert src/src_format to tmp/RGB48
        result = SDL_ConvertPixels_YUV_to_RGB(width, height, src_format, src_colorspace, src_properties, src, src_pitch, SDL_PIXELFORMAT_RGB48, src_colorspace, src_properties, tmp, tmp_pitch);
        ಯದಿ (!result) {
            SDL_free(tmp);
            ಪ್ರತ್ಯಾಗಮ false;
        }

        // convert tmp/RGB48 to dst/RGB
        result = SDL_ConvertPixelsAndColorspace(width, height, SDL_PIXELFORMAT_RGB48, src_colorspace, src_properties, tmp, tmp_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
        SDL_free(tmp);
        ಪ್ರತ್ಯಾಗಮ result;
    }

    ಯದಿ (dst_format != SDL_PIXELFORMAT_ARGB8888) {
        bool result;
        ಶೂನ್ಯ *tmp;
        ಪೂರ್ಣಾಙ್ಕ tmp_pitch = (width * ಪರಿಮಾಣ(Uint32));

        tmp = SDL_malloc((size_t)tmp_pitch * height);
        ಯದಿ (!tmp) {
            ಪ್ರತ್ಯಾಗಮ false;
        }

        // convert src/src_format to tmp/ARGB8888
        result = SDL_ConvertPixels_YUV_to_RGB(width, height, src_format, src_colorspace, src_properties, src, src_pitch, SDL_PIXELFORMAT_ARGB8888, SDL_COLORSPACE_SRGB, 0, tmp, tmp_pitch);
        ಯದಿ (!result) {
            SDL_free(tmp);
            ಪ್ರತ್ಯಾಗಮ false;
        }

        // convert tmp/ARGB8888 to dst/RGB
        result = SDL_ConvertPixelsAndColorspace(width, height, SDL_PIXELFORMAT_ARGB8888, SDL_COLORSPACE_SRGB, 0, tmp, tmp_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
        SDL_free(tmp);
        ಪ್ರತ್ಯಾಗಮ result;
    }

    ಪ್ರತ್ಯಾಗಮ SDL_SetError("Unsupported YUV conversion");
}

ಸಂರಚನಾ RGB2YUVFactors
{
    ಪೂರ್ಣಾಙ್ಕ y_offset;
    ಭಿನ್ನ y[3]; // Rfactor, Gfactor, Bfactor
    ಭಿನ್ನ u[3]; // Rfactor, Gfactor, Bfactor
    ಭಿನ್ನ v[3]; // Rfactor, Gfactor, Bfactor
};

ಸ್ಥಿರ ಸಂರಚನಾ RGB2YUVFactors RGB2YUVFactorTables[] = {
    // ITU-T T.871 (JPEG)
    {
        0,
        { 0.2990f, 0.5870f, 0.1140f },
        { -0.1687f, -0.3313f, 0.5000f },
        { 0.5000f, -0.4187f, -0.0813f },
    },
    // ITU-R BT.601-7
    {
        16,
        { 0.2568f, 0.5041f, 0.0979f },
        { -0.1482f, -0.2910f, 0.4392f },
        { 0.4392f, -0.3678f, -0.0714f },
    },
    // ITU-R BT.709-6 full range
    {
        0,
        { 0.2126f, 0.7152f, 0.0722f },
        { -0.1141f, -0.3839f, 0.498f },
        { 0.498f, -0.4524f, -0.0457f },
    },
    // ITU-R BT.709-6
    {
        16,
        { 0.1826f, 0.6142f, 0.0620f },
        { -0.1006f, -0.3386f, 0.4392f },
        { 0.4392f, -0.3989f, -0.0403f },
    },
    // ITU-R BT.2020 10-bit full range
    {
        0,
        { 0.2627f, 0.6780f, 0.0593f },
        { -0.1395f, -0.3600f, 0.4995f },
        { 0.4995f, -0.4593f, -0.0402f },
    },
};

ಸ್ಥಿರ bool SDL_ConvertPixels_XRGB8888_to_YUV(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, ಧ್ರುವ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಙ್ಕ src_pitch, SDL_PixelFormat dst_format, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಙ್ಕ dst_pitch, YCbCrType yuv_type)
{
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ src_pitch_x_2 = src_pitch * 2;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ height_half = height / 2;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ height_remainder = (height & 0x1);
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ width_half = width / 2;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ width_remainder = (width & 0x1);
    ಪೂರ್ಣಾಙ್ಕ i, j;

    ಧ್ರುವ ಸಂರಚನಾ RGB2YUVFactors *cvt = &RGB2YUVFactorTables[yuv_type];

#define MAKE_Y(r, g, b) (Uint8)SDL_clamp(((ಪೂರ್ಣಾಙ್ಕ)(cvt->y[0] * (r) + cvt->y[1] * (g) + cvt->y[2] * (b) + 0.5f) + cvt->y_offset), 0, 255)
#define MAKE_U(r, g, b) (Uint8)SDL_clamp(((ಪೂರ್ಣಾಙ್ಕ)(cvt->u[0] * (r) + cvt->u[1] * (g) + cvt->u[2] * (b) + 0.5f) + 128), 0, 255)
#define MAKE_V(r, g, b) (Uint8)SDL_clamp(((ಪೂರ್ಣಾಙ್ಕ)(cvt->v[0] * (r) + cvt->v[1] * (g) + cvt->v[2] * (b) + 0.5f) + 128), 0, 255)

#define READ_2x2_PIXELS                                                                                     \
    ಧ್ರುವ Uint32 p1 = ((ಧ್ರುವ Uint32 *)curr_row)[2 * i];                                                    \
    ಧ್ರುವ Uint32 p2 = ((ಧ್ರುವ Uint32 *)curr_row)[2 * i + 1];                                                \
    ಧ್ರುವ Uint32 p3 = ((ಧ್ರುವ Uint32 *)next_row)[2 * i];                                                    \
    ಧ್ರುವ Uint32 p4 = ((ಧ್ರುವ Uint32 *)next_row)[2 * i + 1];                                                \
    ಧ್ರುವ Uint32 r = ((p1 & 0x00ff0000) + (p2 & 0x00ff0000) + (p3 & 0x00ff0000) + (p4 & 0x00ff0000)) >> 18; \
    ಧ್ರುವ Uint32 g = ((p1 & 0x0000ff00) + (p2 & 0x0000ff00) + (p3 & 0x0000ff00) + (p4 & 0x0000ff00)) >> 10; \
    ಧ್ರುವ Uint32 b = ((p1 & 0x000000ff) + (p2 & 0x000000ff) + (p3 & 0x000000ff) + (p4 & 0x000000ff)) >> 2

#define READ_2x1_PIXELS                                             \
    ಧ್ರುವ Uint32 p1 = ((ಧ್ರುವ Uint32 *)curr_row)[2 * i];            \
    ಧ್ರುವ Uint32 p2 = ((ಧ್ರುವ Uint32 *)next_row)[2 * i];            \
    ಧ್ರುವ Uint32 r = ((p1 & 0x00ff0000) + (p2 & 0x00ff0000)) >> 17; \
    ಧ್ರುವ Uint32 g = ((p1 & 0x0000ff00) + (p2 & 0x0000ff00)) >> 9;  \
    ಧ್ರುವ Uint32 b = ((p1 & 0x000000ff) + (p2 & 0x000000ff)) >> 1

#define READ_1x2_PIXELS                                             \
    ಧ್ರುವ Uint32 p1 = ((ಧ್ರುವ Uint32 *)curr_row)[2 * i];            \
    ಧ್ರುವ Uint32 p2 = ((ಧ್ರುವ Uint32 *)curr_row)[2 * i + 1];        \
    ಧ್ರುವ Uint32 r = ((p1 & 0x00ff0000) + (p2 & 0x00ff0000)) >> 17; \
    ಧ್ರುವ Uint32 g = ((p1 & 0x0000ff00) + (p2 & 0x0000ff00)) >> 9;  \
    ಧ್ರುವ Uint32 b = ((p1 & 0x000000ff) + (p2 & 0x000000ff)) >> 1

#define READ_1x1_PIXEL                                  \
    ಧ್ರುವ Uint32 p = ((ಧ್ರುವ Uint32 *)curr_row)[2 * i]; \
    ಧ್ರುವ Uint32 r = (p & 0x00ff0000) >> 16;            \
    ಧ್ರುವ Uint32 g = (p & 0x0000ff00) >> 8;             \
    ಧ್ರುವ Uint32 b = (p & 0x000000ff)

#define READ_TWO_RGB_PIXELS                                  \
    ಧ್ರುವ Uint32 p = ((ಧ್ರುವ Uint32 *)curr_row)[2 * i];      \
    ಧ್ರುವ Uint32 r = (p & 0x00ff0000) >> 16;                 \
    ಧ್ರುವ Uint32 g = (p & 0x0000ff00) >> 8;                  \
    ಧ್ರುವ Uint32 b = (p & 0x000000ff);                       \
    ಧ್ರುವ Uint32 p1 = ((ಧ್ರುವ Uint32 *)curr_row)[2 * i + 1]; \
    ಧ್ರುವ Uint32 r1 = (p1 & 0x00ff0000) >> 16;               \
    ಧ್ರುವ Uint32 g1 = (p1 & 0x0000ff00) >> 8;                \
    ಧ್ರುವ Uint32 b1 = (p1 & 0x000000ff);                     \
    ಧ್ರುವ Uint32 R = (r + r1) / 2;                           \
    ಧ್ರುವ Uint32 G = (g + g1) / 2;                           \
    ಧ್ರುವ Uint32 B = (b + b1) / 2

#define READ_ONE_RGB_PIXEL READ_1x1_PIXEL

    ವಿಕಲ್ಪ (dst_format) {
    ಪಕ್ಷ SDL_PIXELFORMAT_YV12:
    ಪಕ್ಷ SDL_PIXELFORMAT_IYUV:
    ಪಕ್ಷ SDL_PIXELFORMAT_I444:
    ಪಕ್ಷ SDL_PIXELFORMAT_NV12:
    ಪಕ್ಷ SDL_PIXELFORMAT_NV21:
    {
        ಧ್ರುವ Uint8 *curr_row, *next_row;

        Uint8 *plane_y;
        Uint8 *plane_u;
        Uint8 *plane_v;
        Uint8 *plane_interleaved_uv;
        Uint32 y_stride, uv_stride, y_skip, uv_skip;

        ಯದಿ (!GetYUVPlanes(width, height, dst_format, dst, dst_pitch,
                          (ಧ್ರುವ Uint8 **)&plane_y, (ಧ್ರುವ Uint8 **)&plane_u, (ಧ್ರುವ Uint8 **)&plane_v,
                          &y_stride, &uv_stride)) {
            ಪ್ರತ್ಯಾಗಮ false;
        }

        plane_interleaved_uv = (plane_y + height * y_stride);
        y_skip = (y_stride - width);

        curr_row = (ಧ್ರುವ Uint8 *)src;

        // Write Y plane
        ಪ್ರತಿ (j = 0; j < height; j++) {
            ಪ್ರತಿ (i = 0; i < width; i++) {
                ಧ್ರುವ Uint32 p1 = ((ಧ್ರುವ Uint32 *)curr_row)[i];
                ಧ್ರುವ Uint32 r = (p1 & 0x00ff0000) >> 16;
                ಧ್ರುವ Uint32 g = (p1 & 0x0000ff00) >> 8;
                ಧ್ರುವ Uint32 b = (p1 & 0x000000ff);
                *plane_y++ = MAKE_Y(r, g, b);
            }
            plane_y += y_skip;
            curr_row += src_pitch;
        }

        curr_row = (ಧ್ರುವ Uint8 *)src;
        next_row = (ಧ್ರುವ Uint8 *)src;
        next_row += src_pitch;

        ಯದಿ (dst_format == SDL_PIXELFORMAT_YV12 || dst_format == SDL_PIXELFORMAT_IYUV) {
            // Write UV planes, not interleaved
            uv_skip = (uv_stride - (width + 1) / 2);
            ಪ್ರತಿ (j = 0; j < height_half; j++) {
                ಪ್ರತಿ (i = 0; i < width_half; i++) {
                    READ_2x2_PIXELS;
                    *plane_u++ = MAKE_U(r, g, b);
                    *plane_v++ = MAKE_V(r, g, b);
                }
                ಯದಿ (width_remainder) {
                    READ_2x1_PIXELS;
                    *plane_u++ = MAKE_U(r, g, b);
                    *plane_v++ = MAKE_V(r, g, b);
                }
                plane_u += uv_skip;
                plane_v += uv_skip;
                curr_row += src_pitch_x_2;
                next_row += src_pitch_x_2;
            }
            ಯದಿ (height_remainder) {
                ಪ್ರತಿ (i = 0; i < width_half; i++) {
                    READ_1x2_PIXELS;
                    *plane_u++ = MAKE_U(r, g, b);
                    *plane_v++ = MAKE_V(r, g, b);
                }
                ಯದಿ (width_remainder) {
                    READ_1x1_PIXEL;
                    *plane_u++ = MAKE_U(r, g, b);
                    *plane_v++ = MAKE_V(r, g, b);
                }
                plane_u += uv_skip;
                plane_v += uv_skip;
            }
        } ಅನ್ಯಥಾ ಯದಿ (dst_format == SDL_PIXELFORMAT_I444) {
            // Write UV planes, not interleaved
            uv_skip = (uv_stride - width);
            ಪ್ರತಿ (j = 0; j < height; j++) {
                ಪ್ರತಿ (i = 0; i < width; i++) {
                    ಧ್ರುವ Uint32 p1 = ((ಧ್ರುವ Uint32 *)curr_row)[i];
                    ಧ್ರುವ Uint32 r = (p1 & 0x00ff0000) >> 16;
                    ಧ್ರುವ Uint32 g = (p1 & 0x0000ff00) >> 8;
                    ಧ್ರುವ Uint32 b = (p1 & 0x000000ff);
                    *plane_u++ = MAKE_U(r, g, b);
                    *plane_v++ = MAKE_V(r, g, b);
                }
                plane_u += uv_skip;
                plane_v += uv_skip;
                curr_row += src_pitch;
            }
        } ಅನ್ಯಥಾ ಯದಿ (dst_format == SDL_PIXELFORMAT_NV12) {
            uv_skip = (uv_stride - ((width + 1) / 2) * 2);
            ಪ್ರತಿ (j = 0; j < height_half; j++) {
                ಪ್ರತಿ (i = 0; i < width_half; i++) {
                    READ_2x2_PIXELS;
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                }
                ಯದಿ (width_remainder) {
                    READ_2x1_PIXELS;
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                }
                plane_interleaved_uv += uv_skip;
                curr_row += src_pitch_x_2;
                next_row += src_pitch_x_2;
            }
            ಯದಿ (height_remainder) {
                ಪ್ರತಿ (i = 0; i < width_half; i++) {
                    READ_1x2_PIXELS;
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                }
                ಯದಿ (width_remainder) {
                    READ_1x1_PIXEL;
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                }
            }
        } ಅನ್ಯಥಾ /* dst_format == SDL_PIXELFORMAT_NV21 */ {
            uv_skip = (uv_stride - ((width + 1) / 2) * 2);
            ಪ್ರತಿ (j = 0; j < height_half; j++) {
                ಪ್ರತಿ (i = 0; i < width_half; i++) {
                    READ_2x2_PIXELS;
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                }
                ಯದಿ (width_remainder) {
                    READ_2x1_PIXELS;
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                }
                plane_interleaved_uv += uv_skip;
                curr_row += src_pitch_x_2;
                next_row += src_pitch_x_2;
            }
            ಯದಿ (height_remainder) {
                ಪ್ರತಿ (i = 0; i < width_half; i++) {
                    READ_1x2_PIXELS;
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                }
                ಯದಿ (width_remainder) {
                    READ_1x1_PIXEL;
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                }
            }
        }
    } ಭಙ್ಗ;

    ಪಕ್ಷ SDL_PIXELFORMAT_YUY2:
    ಪಕ್ಷ SDL_PIXELFORMAT_UYVY:
    ಪಕ್ಷ SDL_PIXELFORMAT_YVYU:
    {
        ಧ್ರುವ Uint8 *curr_row = (ಧ್ರುವ Uint8 *)src;
        Uint8 *plane = (Uint8 *)dst;
        ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ row_size = (4 * ((width + 1) / 2));
        ಪೂರ್ಣಾಙ್ಕ plane_skip;

        ಯದಿ (dst_pitch < row_size) {
            ಪ್ರತ್ಯಾಗಮ SDL_SetError("Destination pitch is too small, expected at least %d", row_size);
        }
        plane_skip = (dst_pitch - row_size);

        // Write YUV plane, packed
        ಯದಿ (dst_format == SDL_PIXELFORMAT_YUY2) {
            ಪ್ರತಿ (j = 0; j < height; j++) {
                ಪ್ರತಿ (i = 0; i < width_half; i++) {
                    READ_TWO_RGB_PIXELS;
                    // Y U Y1 V
                    *plane++ = MAKE_Y(r, g, b);
                    *plane++ = MAKE_U(R, G, B);
                    *plane++ = MAKE_Y(r1, g1, b1);
                    *plane++ = MAKE_V(R, G, B);
                }
                ಯದಿ (width_remainder) {
                    READ_ONE_RGB_PIXEL;
                    // Y U Y V
                    *plane++ = MAKE_Y(r, g, b);
                    *plane++ = MAKE_U(r, g, b);
                    *plane++ = MAKE_Y(r, g, b);
                    *plane++ = MAKE_V(r, g, b);
                }
                plane += plane_skip;
                curr_row += src_pitch;
            }
        } ಅನ್ಯಥಾ ಯದಿ (dst_format == SDL_PIXELFORMAT_UYVY) {
            ಪ್ರತಿ (j = 0; j < height; j++) {
                ಪ್ರತಿ (i = 0; i < width_half; i++) {
                    READ_TWO_RGB_PIXELS;
                    // U Y V Y1
                    *plane++ = MAKE_U(R, G, B);
                    *plane++ = MAKE_Y(r, g, b);
                    *plane++ = MAKE_V(R, G, B);
                    *plane++ = MAKE_Y(r1, g1, b1);
                }
                ಯದಿ (width_remainder) {
                    READ_ONE_RGB_PIXEL;
                    // U Y V Y
                    *plane++ = MAKE_U(r, g, b);
                    *plane++ = MAKE_Y(r, g, b);
                    *plane++ = MAKE_V(r, g, b);
                    *plane++ = MAKE_Y(r, g, b);
                }
                plane += plane_skip;
                curr_row += src_pitch;
            }
        } ಅನ್ಯಥಾ ಯದಿ (dst_format == SDL_PIXELFORMAT_YVYU) {
            ಪ್ರತಿ (j = 0; j < height; j++) {
                ಪ್ರತಿ (i = 0; i < width_half; i++) {
                    READ_TWO_RGB_PIXELS;
                    // Y V Y1 U
                    *plane++ = MAKE_Y(r, g, b);
                    *plane++ = MAKE_V(R, G, B);
                    *plane++ = MAKE_Y(r1, g1, b1);
                    *plane++ = MAKE_U(R, G, B);
                }
                ಯದಿ (width_remainder) {
                    READ_ONE_RGB_PIXEL;
                    // Y V Y U
                    *plane++ = MAKE_Y(r, g, b);
                    *plane++ = MAKE_V(r, g, b);
                    *plane++ = MAKE_Y(r, g, b);
                    *plane++ = MAKE_U(r, g, b);
                }
                plane += plane_skip;
                curr_row += src_pitch;
            }
        }
    } ಭಙ್ಗ;

    ಸ್ವಭಾವ:
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Unsupported YUV destination format: %s", SDL_GetPixelFormatName(dst_format));
    }
#undef MAKE_Y
#undef MAKE_U
#undef MAKE_V
#undef READ_2x2_PIXELS
#undef READ_2x1_PIXELS
#undef READ_1x2_PIXELS
#undef READ_1x1_PIXEL
#undef READ_TWO_RGB_PIXELS
#undef READ_ONE_RGB_PIXEL
    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ bool SDL_ConvertPixels_XBGR2101010_to_P010(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, ಧ್ರುವ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಙ್ಕ src_pitch, SDL_PixelFormat dst_format, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಙ್ಕ dst_pitch, YCbCrType yuv_type)
{
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ src_pitch_x_2 = src_pitch * 2;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ height_half = height / 2;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ height_remainder = (height & 0x1);
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ width_half = width / 2;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ width_remainder = (width & 0x1);
    ಪೂರ್ಣಾಙ್ಕ i, j;

    ಧ್ರುವ ಸಂರಚನಾ RGB2YUVFactors *cvt = &RGB2YUVFactorTables[yuv_type];

#define MAKE_Y(r, g, b) (Uint16)(((ಪೂರ್ಣಾಙ್ಕ)(cvt->y[0] * (r) + cvt->y[1] * (g) + cvt->y[2] * (b) + 0.5f) + cvt->y_offset) << 6)
#define MAKE_U(r, g, b) (Uint16)(((ಪೂರ್ಣಾಙ್ಕ)(cvt->u[0] * (r) + cvt->u[1] * (g) + cvt->u[2] * (b) + 0.5f) + 512) << 6)
#define MAKE_V(r, g, b) (Uint16)(((ಪೂರ್ಣಾಙ್ಕ)(cvt->v[0] * (r) + cvt->v[1] * (g) + cvt->v[2] * (b) + 0.5f) + 512) << 6)

#define READ_2x2_PIXELS                                                                                     \
    ಧ್ರುವ Uint32 p1 = ((ಧ್ರುವ Uint32 *)curr_row)[2 * i];                                                    \
    ಧ್ರುವ Uint32 p2 = ((ಧ್ರುವ Uint32 *)curr_row)[2 * i + 1];                                                \
    ಧ್ರುವ Uint32 p3 = ((ಧ್ರುವ Uint32 *)next_row)[2 * i];                                                    \
    ಧ್ರುವ Uint32 p4 = ((ಧ್ರುವ Uint32 *)next_row)[2 * i + 1];                                                \
    ಧ್ರುವ Uint32 r = ((p1 & 0x000003ff) + (p2 & 0x000003ff) + (p3 & 0x000003ff) + (p4 & 0x000003ff)) >> 2;  \
    ಧ್ರುವ Uint32 g = ((p1 & 0x000ffc00) + (p2 & 0x000ffc00) + (p3 & 0x000ffc00) + (p4 & 0x000ffc00)) >> 12; \
    ಧ್ರುವ Uint32 b = ((p1 & 0x3ff00000) + (p2 & 0x3ff00000) + (p3 & 0x3ff00000) + (p4 & 0x3ff00000)) >> 22

#define READ_2x1_PIXELS                                             \
    ಧ್ರುವ Uint32 p1 = ((ಧ್ರುವ Uint32 *)curr_row)[2 * i];            \
    ಧ್ರುವ Uint32 p2 = ((ಧ್ರುವ Uint32 *)next_row)[2 * i];            \
    ಧ್ರುವ Uint32 r = ((p1 & 0x000003ff) + (p2 & 0x000003ff)) >> 1;  \
    ಧ್ರುವ Uint32 g = ((p1 & 0x000ffc00) + (p2 & 0x000ffc00)) >> 11; \
    ಧ್ರುವ Uint32 b = ((p1 & 0x3ff00000) + (p2 & 0x3ff00000)) >> 21

#define READ_1x2_PIXELS                                             \
    ಧ್ರುವ Uint32 p1 = ((ಧ್ರುವ Uint32 *)curr_row)[2 * i];            \
    ಧ್ರುವ Uint32 p2 = ((ಧ್ರುವ Uint32 *)curr_row)[2 * i + 1];        \
    ಧ್ರುವ Uint32 r = ((p1 & 0x000003ff) + (p2 & 0x000003ff)) >> 1;  \
    ಧ್ರುವ Uint32 g = ((p1 & 0x000ffc00) + (p2 & 0x000ffc00)) >> 11; \
    ಧ್ರುವ Uint32 b = ((p1 & 0x3ff00000) + (p2 & 0x3ff00000)) >> 21

#define READ_1x1_PIXEL                                  \
    ಧ್ರುವ Uint32 p = ((ಧ್ರುವ Uint32 *)curr_row)[2 * i]; \
    ಧ್ರುವ Uint32 r = (p & 0x000003ff);                  \
    ಧ್ರುವ Uint32 g = (p & 0x000ffc00) >> 10;            \
    ಧ್ರುವ Uint32 b = (p & 0x3ff00000) >> 20

    ಧ್ರುವ Uint8 *curr_row, *next_row;

    Uint16 *plane_y;
    Uint16 *plane_u;
    Uint16 *plane_v;
    Uint16 *plane_interleaved_uv;
    Uint32 y_stride, uv_stride, y_skip, uv_skip;

    ಯದಿ (!GetYUVPlanes(width, height, dst_format, dst, dst_pitch,
                      (ಧ್ರುವ Uint8 **)&plane_y, (ಧ್ರುವ Uint8 **)&plane_u, (ಧ್ರುವ Uint8 **)&plane_v,
                      &y_stride, &uv_stride)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    y_stride /= ಪರಿಮಾಣ(Uint16);
    uv_stride /= ಪರಿಮಾಣ(Uint16);

    plane_interleaved_uv = (plane_y + height * y_stride);
    y_skip = (y_stride - width);

    curr_row = (ಧ್ರುವ Uint8 *)src;

    // Write Y plane
    ಪ್ರತಿ (j = 0; j < height; j++) {
        ಪ್ರತಿ (i = 0; i < width; i++) {
            ಧ್ರುವ Uint32 p1 = ((ಧ್ರುವ Uint32 *)curr_row)[i];
            ಧ್ರುವ Uint32 r = (p1 >>  0) & 0x03ff;
            ಧ್ರುವ Uint32 g = (p1 >> 10) & 0x03ff;
            ಧ್ರುವ Uint32 b = (p1 >> 20) & 0x03ff;
            *plane_y++ = MAKE_Y(r, g, b);
        }
        plane_y += y_skip;
        curr_row += src_pitch;
    }

    curr_row = (ಧ್ರುವ Uint8 *)src;
    next_row = (ಧ್ರುವ Uint8 *)src;
    next_row += src_pitch;

    uv_skip = (uv_stride - ((width + 1) / 2) * 2);
    ಪ್ರತಿ (j = 0; j < height_half; j++) {
        ಪ್ರತಿ (i = 0; i < width_half; i++) {
            READ_2x2_PIXELS;
            *plane_interleaved_uv++ = MAKE_U(r, g, b);
            *plane_interleaved_uv++ = MAKE_V(r, g, b);
        }
        ಯದಿ (width_remainder) {
            READ_2x1_PIXELS;
            *plane_interleaved_uv++ = MAKE_U(r, g, b);
            *plane_interleaved_uv++ = MAKE_V(r, g, b);
        }
        plane_interleaved_uv += uv_skip;
        curr_row += src_pitch_x_2;
        next_row += src_pitch_x_2;
    }
    ಯದಿ (height_remainder) {
        ಪ್ರತಿ (i = 0; i < width_half; i++) {
            READ_1x2_PIXELS;
            *plane_interleaved_uv++ = MAKE_U(r, g, b);
            *plane_interleaved_uv++ = MAKE_V(r, g, b);
        }
        ಯದಿ (width_remainder) {
            READ_1x1_PIXEL;
            *plane_interleaved_uv++ = MAKE_U(r, g, b);
            *plane_interleaved_uv++ = MAKE_V(r, g, b);
        }
    }

#undef MAKE_Y
#undef MAKE_U
#undef MAKE_V
#undef READ_2x2_PIXELS
#undef READ_2x1_PIXELS
#undef READ_1x2_PIXELS
#undef READ_1x1_PIXEL
    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_ConvertPixels_RGB_to_YUV(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height,
                                  SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ಧ್ರುವ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಙ್ಕ src_pitch,
                                  SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಙ್ಕ dst_pitch)
{
    YCbCrType yuv_type = YCBCR_601_LIMITED;

    ಯದಿ (!GetYUVConversionType(dst_colorspace, width, height, 8, &yuv_type)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

#ಯದಿ 0 // Doesn't handle odd widths
    // RGB24 to FOURCC
    ಯದಿ (src_format == SDL_PIXELFORMAT_RGB24) {
        Uint8 *y;
        Uint8 *u;
        Uint8 *v;
        Uint32 y_stride;
        Uint32 uv_stride;

        ಯದಿ (GetYUVPlanes(width, height, dst_format, dst, dst_pitch, (ಧ್ರುವ Uint8 **)&y, (ಧ್ರುವ Uint8 **)&u, (ಧ್ರುವ Uint8 **)&v, &y_stride, &uv_stride) < 0) {
            ಪ್ರತ್ಯಾಗಮ false;
        }

        rgb24_yuv420_std(width, height, src, src_pitch, y, u, v, y_stride, uv_stride, yuv_type);
        ಪ್ರತ್ಯಾಗಮ true;
    }
#endif

    // ARGB8888 to FOURCC
    ಯದಿ (src_format == SDL_PIXELFORMAT_ARGB8888 || src_format == SDL_PIXELFORMAT_XRGB8888) {
        ಪ್ರತ್ಯಾಗಮ SDL_ConvertPixels_XRGB8888_to_YUV(width, height, src, src_pitch, dst_format, dst, dst_pitch, yuv_type);
    }

    ಯದಿ (dst_format == SDL_PIXELFORMAT_P010) {
        ಯದಿ (src_format == SDL_PIXELFORMAT_XBGR2101010) {
            ಪ್ರತ್ಯಾಗಮ SDL_ConvertPixels_XBGR2101010_to_P010(width, height, src, src_pitch, dst_format, dst, dst_pitch, yuv_type);
        }

        // We currently only support converting from XBGR2101010 to P010
        bool result;
        ಶೂನ್ಯ *tmp;
        ಪೂರ್ಣಾಙ್ಕ tmp_pitch = (width * ಪರಿಮಾಣ(Uint32));

        tmp = SDL_malloc((size_t)tmp_pitch * height);
        ಯದಿ (!tmp) {
            ಪ್ರತ್ಯಾಗಮ false;
        }

        // convert src/src_format to tmp/XBGR2101010
        result = SDL_ConvertPixelsAndColorspace(width, height, src_format, src_colorspace, src_properties, src, src_pitch, SDL_PIXELFORMAT_XBGR2101010, dst_colorspace, dst_properties, tmp, tmp_pitch);
        ಯದಿ (!result) {
            SDL_free(tmp);
            ಪ್ರತ್ಯಾಗಮ false;
        }

        // convert tmp/XBGR2101010 to dst/P010
        result = SDL_ConvertPixels_XBGR2101010_to_P010(width, height, tmp, tmp_pitch, dst_format, dst, dst_pitch, yuv_type);
        SDL_free(tmp);
        ಪ್ರತ್ಯಾಗಮ result;
    }

    // not ARGB8888 to FOURCC : need an intermediate conversion
    {
        bool result;
        ಶೂನ್ಯ *tmp;
        ಪೂರ್ಣಾಙ್ಕ tmp_pitch = (width * ಪರಿಮಾಣ(Uint32));

        tmp = SDL_malloc((size_t)tmp_pitch * height);
        ಯದಿ (!tmp) {
            ಪ್ರತ್ಯಾಗಮ false;
        }

        // convert src/src_format to tmp/XRGB8888
        result = SDL_ConvertPixelsAndColorspace(width, height, src_format, src_colorspace, src_properties, src, src_pitch, SDL_PIXELFORMAT_XRGB8888, SDL_COLORSPACE_SRGB, 0, tmp, tmp_pitch);
        ಯದಿ (!result) {
            SDL_free(tmp);
            ಪ್ರತ್ಯಾಗಮ false;
        }

        // convert tmp/XRGB8888 to dst/FOURCC
        result = SDL_ConvertPixels_XRGB8888_to_YUV(width, height, tmp, tmp_pitch, dst_format, dst, dst_pitch, yuv_type);
        SDL_free(tmp);
        ಪ್ರತ್ಯಾಗಮ result;
    }
}

ಸ್ಥಿರ bool SDL_ConvertPixels_YUV_to_YUV_Copy(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, SDL_PixelFormat format, ಧ್ರುವ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಙ್ಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಙ್ಕ dst_pitch)
{
    ಪೂರ್ಣಾಙ್ಕ i;

    ಯದಿ (IsPlanar1x1Format(format)) {
        // YUV planes
        ಧ್ರುವ size_t length = width * SDL_BYTESPERPIXEL(format);
        ಪ್ರತಿ (i = height * 3; i--;) {
            SDL_memcpy(dst, src, length);
            src = (ಧ್ರುವ Uint8 *)src + src_pitch;
            dst = (Uint8 *)dst + dst_pitch;
        }
        ಪ್ರತ್ಯಾಗಮ true;
    }

    ಯದಿ (IsPlanar2x2Format(format)) {
        ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ bpp = SDL_BYTESPERPIXEL(format);

        // Y plane
        ಧ್ರುವ size_t length = width * bpp;
        ಪ್ರತಿ (i = height; i--;) {
            SDL_memcpy(dst, src, length);
            src = (ಧ್ರುವ Uint8 *)src + src_pitch;
            dst = (Uint8 *)dst + dst_pitch;
        }

        ಯದಿ (format == SDL_PIXELFORMAT_YV12 ||
            format == SDL_PIXELFORMAT_IYUV ||
            format == SDL_PIXELFORMAT_I0FL) {
            // U and V planes are a quarter the size of the Y plane, rounded up
            width = ((width + 1) / 2) * bpp;
            height = (height + 1) / 2;
            src_pitch = ((src_pitch / bpp + 1) / 2) * bpp;
            dst_pitch = ((dst_pitch / bpp + 1) / 2) * bpp;
            ಪ್ರತಿ (i = height * 2; i--;) {
                SDL_memcpy(dst, src, width);
                src = (ಧ್ರುವ Uint8 *)src + src_pitch;
                dst = (Uint8 *)dst + dst_pitch;
            }
        } ಅನ್ಯಥಾ ಯದಿ (format == SDL_PIXELFORMAT_NV12 ||
                   format == SDL_PIXELFORMAT_NV21 ||
                   format == SDL_PIXELFORMAT_P010) {
            // U/V plane is half the height of the Y plane, rounded up, with packed CrCb
            width = ((width + 1) / 2) * 2 * bpp;
            height = (height + 1) / 2;
            src_pitch = ((src_pitch / bpp + 1) / 2) * 2 * bpp;
            dst_pitch = ((dst_pitch / bpp + 1) / 2) * 2 * bpp;
            ಪ್ರತಿ (i = height; i--;) {
                SDL_memcpy(dst, src, width);
                src = (ಧ್ರುವ Uint8 *)src + src_pitch;
                dst = (Uint8 *)dst + dst_pitch;
            }
        }
        ಪ್ರತ್ಯಾಗಮ true;
    }

    ಯದಿ (IsPacked4Format(format)) {
        // Packed planes
        width = 4 * ((width + 1) / 2);
        ಪ್ರತಿ (i = height; i--;) {
            SDL_memcpy(dst, src, width);
            src = (ಧ್ರುವ Uint8 *)src + src_pitch;
            dst = (Uint8 *)dst + dst_pitch;
        }
        ಪ್ರತ್ಯಾಗಮ true;
    }

    ಪ್ರತ್ಯಾಗಮ SDL_SetError("SDL_ConvertPixels_YUV_to_YUV_Copy: Unsupported YUV format: %s", SDL_GetPixelFormatName(format));
}

ಸ್ಥಿರ bool SDL_ConvertPixels_SwapUVPlanes(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, ಧ್ರುವ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಙ್ಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಙ್ಕ dst_pitch)
{
    ಪೂರ್ಣಾಙ್ಕ y;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ UVwidth = (width + 1) / 2;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ UVheight = (height + 1) / 2;

    // Skip the Y plane
    src = (ಧ್ರುವ Uint8 *)src + height * src_pitch;
    dst = (Uint8 *)dst + height * dst_pitch;

    ಯದಿ (src == dst) {
        ಪೂರ್ಣಾಙ್ಕ UVpitch = (dst_pitch + 1) / 2;
        Uint8 *tmp;
        Uint8 *row1 = (Uint8 *)dst;
        Uint8 *row2 = row1 + UVheight * UVpitch;

        // Allocate a temporary row for the swap
        tmp = (Uint8 *)SDL_malloc(UVwidth);
        ಯದಿ (!tmp) {
            ಪ್ರತ್ಯಾಗಮ false;
        }
        ಪ್ರತಿ (y = 0; y < UVheight; ++y) {
            SDL_memcpy(tmp, row1, UVwidth);
            SDL_memcpy(row1, row2, UVwidth);
            SDL_memcpy(row2, tmp, UVwidth);
            row1 += UVpitch;
            row2 += UVpitch;
        }
        SDL_free(tmp);
    } ಅನ್ಯಥಾ {
        ಧ್ರುವ Uint8 *srcUV;
        Uint8 *dstUV;
        ಪೂರ್ಣಾಙ್ಕ srcUVPitch = ((src_pitch + 1) / 2);
        ಪೂರ್ಣಾಙ್ಕ dstUVPitch = ((dst_pitch + 1) / 2);

        // Copy the first plane
        srcUV = (ಧ್ರುವ Uint8 *)src;
        dstUV = (Uint8 *)dst + UVheight * dstUVPitch;
        ಪ್ರತಿ (y = 0; y < UVheight; ++y) {
            SDL_memcpy(dstUV, srcUV, UVwidth);
            srcUV += srcUVPitch;
            dstUV += dstUVPitch;
        }

        // Copy the second plane
        dstUV = (Uint8 *)dst;
        ಪ್ರತಿ (y = 0; y < UVheight; ++y) {
            SDL_memcpy(dstUV, srcUV, UVwidth);
            srcUV += srcUVPitch;
            dstUV += dstUVPitch;
        }
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

#ifdef SDL_SSE2_INTRINSICS
ಸ್ಥಿರ bool SDL_TARGETING("sse2") SDL_ConvertPixels_PackUVPlanes_to_NV_SSE2(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, ಧ್ರುವ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಙ್ಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಙ್ಕ dst_pitch, bool reverseUV)
{
    ಪೂರ್ಣಾಙ್ಕ x, y;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ UVwidth = (width + 1) / 2;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ UVheight = (height + 1) / 2;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ srcUVPitch = ((src_pitch + 1) / 2);
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ src_UVPitch_ಎಡ = srcUVPitch - UVwidth;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ dstUVPitch = ((dst_pitch + 1) / 2) * 2;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ dst_UVPitch_ಎಡ = dstUVPitch - UVwidth * 2;
    ಧ್ರುವ Uint8 *src1, *src2;
    Uint8 *dstUV;
    Uint8 *tmp = ರಿಕ್ತ;

    // Skip the Y plane
    src = (ಧ್ರುವ Uint8 *)src + height * src_pitch;
    dst = (Uint8 *)dst + height * dst_pitch;

    ಯದಿ (src == dst) {
        // Need to make a copy of the buffer so we don't clobber it while converting
        tmp = (Uint8 *)SDL_malloc((size_t)2 * UVheight * srcUVPitch);
        ಯದಿ (tmp == ರಿಕ್ತ) {
            ಪ್ರತ್ಯಾಗಮ false;
        }
        SDL_memcpy(tmp, src, (size_t)2 * UVheight * srcUVPitch);
        src = tmp;
    }

    ಯದಿ (reverseUV) {
        src2 = (ಧ್ರುವ Uint8 *)src;
        src1 = src2 + UVheight * srcUVPitch;
    } ಅನ್ಯಥಾ {
        src1 = (ಧ್ರುವ Uint8 *)src;
        src2 = src1 + UVheight * srcUVPitch;
    }
    dstUV = (Uint8 *)dst;

    y = UVheight;
    ಯಾವತ್ (y--) {
        x = UVwidth;
        ಯಾವತ್ (x >= 16) {
            __m128i u = _mm_loadu_si128((__m128i *)src1);
            __m128i v = _mm_loadu_si128((__m128i *)src2);
            __m128i uv1 = _mm_unpacklo_epi8(u, v);
            __m128i uv2 = _mm_unpackhi_epi8(u, v);
            _mm_storeu_si128((__m128i *)dstUV, uv1);
            _mm_storeu_si128((__m128i *)(dstUV + 16), uv2);
            src1 += 16;
            src2 += 16;
            dstUV += 32;
            x -= 16;
        }
        ಯಾವತ್ (x--) {
            *dstUV++ = *src1++;
            *dstUV++ = *src2++;
        }
        src1 += src_UVPitch_ಎಡ;
        src2 += src_UVPitch_ಎಡ;
        dstUV += dst_UVPitch_ಎಡ;
    }

    ಯದಿ (tmp) {
        SDL_free(tmp);
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ bool SDL_TARGETING("sse2") SDL_ConvertPixels_SplitNV_to_UVPlanes_SSE2(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, ಧ್ರುವ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಙ್ಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಙ್ಕ dst_pitch, bool reverseUV)
{
    ಪೂರ್ಣಾಙ್ಕ x, y;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ UVwidth = (width + 1) / 2;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ UVheight = (height + 1) / 2;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ srcUVPitch = ((src_pitch + 1) / 2) * 2;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ src_UVPitch_ಎಡ = srcUVPitch - UVwidth * 2;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ dstUVPitch = ((dst_pitch + 1) / 2);
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ dst_UVPitch_ಎಡ = dstUVPitch - UVwidth;
    ಧ್ರುವ Uint8 *srcUV;
    Uint8 *dst1, *dst2;
    Uint8 *tmp = ರಿಕ್ತ;

    // Skip the Y plane
    src = (ಧ್ರುವ Uint8 *)src + height * src_pitch;
    dst = (Uint8 *)dst + height * dst_pitch;

    ಯದಿ (src == dst) {
        // Need to make a copy of the buffer so we don't clobber it while converting
        tmp = (Uint8 *)SDL_malloc((size_t)UVheight * srcUVPitch);
        ಯದಿ (tmp == ರಿಕ್ತ) {
            ಪ್ರತ್ಯಾಗಮ false;
        }
        SDL_memcpy(tmp, src, (size_t)UVheight * srcUVPitch);
        src = tmp;
    }

    ಯದಿ (reverseUV) {
        dst2 = (Uint8 *)dst;
        dst1 = dst2 + UVheight * dstUVPitch;
    } ಅನ್ಯಥಾ {
        dst1 = (Uint8 *)dst;
        dst2 = dst1 + UVheight * dstUVPitch;
    }
    srcUV = (ಧ್ರುವ Uint8 *)src;

    y = UVheight;
    ಯಾವತ್ (y--) {
        __m128i mask = _mm_set1_epi16(0x00FF);
        x = UVwidth;
        ಯಾವತ್ (x >= 16) {
            __m128i uv1 = _mm_loadu_si128((__m128i *)srcUV);
            __m128i uv2 = _mm_loadu_si128((__m128i *)(srcUV + 16));
            __m128i u1 = _mm_and_si128(uv1, mask);
            __m128i u2 = _mm_and_si128(uv2, mask);
            __m128i u = _mm_packus_epi16(u1, u2);
            __m128i v1 = _mm_srli_epi16(uv1, 8);
            __m128i v2 = _mm_srli_epi16(uv2, 8);
            __m128i v = _mm_packus_epi16(v1, v2);
            _mm_storeu_si128((__m128i *)dst1, u);
            _mm_storeu_si128((__m128i *)dst2, v);
            srcUV += 32;
            dst1 += 16;
            dst2 += 16;
            x -= 16;
        }
        ಯಾವತ್ (x--) {
            *dst1++ = *srcUV++;
            *dst2++ = *srcUV++;
        }
        srcUV += src_UVPitch_ಎಡ;
        dst1 += dst_UVPitch_ಎಡ;
        dst2 += dst_UVPitch_ಎಡ;
    }

    ಯದಿ (tmp) {
        SDL_free(tmp);
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ bool SDL_TARGETING("sse2") SDL_ConvertPixels_SwapNV_SSE2(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, ಧ್ರುವ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಙ್ಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಙ್ಕ dst_pitch)
{
    ಪೂರ್ಣಾಙ್ಕ x, y;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ UVwidth = (width + 1) / 2;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ UVheight = (height + 1) / 2;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ srcUVPitch = ((src_pitch + 1) / 2) * 2;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ src_UVPitch_ಎಡ = (srcUVPitch - UVwidth * 2) / ಪರಿಮಾಣ(Uint16);
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ dstUVPitch = ((dst_pitch + 1) / 2) * 2;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ dst_UVPitch_ಎಡ = (dstUVPitch - UVwidth * 2) / ಪರಿಮಾಣ(Uint16);
    ಧ್ರುವ Uint16 *srcUV;
    Uint16 *dstUV;

    // Skip the Y plane
    src = (ಧ್ರುವ Uint8 *)src + height * src_pitch;
    dst = (Uint8 *)dst + height * dst_pitch;

    srcUV = (ಧ್ರುವ Uint16 *)src;
    dstUV = (Uint16 *)dst;
    y = UVheight;
    ಯಾವತ್ (y--) {
        x = UVwidth;
        ಯಾವತ್ (x >= 8) {
            __m128i uv = _mm_loadu_si128((__m128i *)srcUV);
            __m128i v = _mm_slli_epi16(uv, 8);
            __m128i u = _mm_srli_epi16(uv, 8);
            __m128i vu = _mm_or_si128(v, u);
            _mm_storeu_si128((__m128i *)dstUV, vu);
            srcUV += 8;
            dstUV += 8;
            x -= 8;
        }
        ಯದಿ (x > 0) {
            ಧ್ರುವ Uint8 *srcUV8 = (ಧ್ರುವ Uint8 *)srcUV;
            Uint8 *dstUV8 = (Uint8 *)dstUV;
            srcUV += x;
            dstUV += x;
            ಯಾವತ್ (x--) {
                Uint8 u = *srcUV8++;
                Uint8 v = *srcUV8++;
                *dstUV8++ = v;
                *dstUV8++ = u;
            }
        }
        srcUV += src_UVPitch_ಎಡ;
        dstUV += dst_UVPitch_ಎಡ;
    }
    ಪ್ರತ್ಯಾಗಮ true;
}
#endif

ಸ್ಥಿರ bool SDL_ConvertPixels_PackUVPlanes_to_NV_std(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, ಧ್ರುವ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಙ್ಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಙ್ಕ dst_pitch, bool reverseUV)
{
    ಪೂರ್ಣಾಙ್ಕ x, y;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ UVwidth = (width + 1) / 2;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ UVheight = (height + 1) / 2;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ srcUVPitch = ((src_pitch + 1) / 2);
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ src_UVPitch_ಎಡ = srcUVPitch - UVwidth;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ dstUVPitch = ((dst_pitch + 1) / 2) * 2;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ dst_UVPitch_ಎಡ = dstUVPitch - UVwidth * 2;
    ಧ್ರುವ Uint8 *src1, *src2;
    Uint8 *dstUV;
    Uint8 *tmp = ರಿಕ್ತ;

    // Skip the Y plane
    src = (ಧ್ರುವ Uint8 *)src + height * src_pitch;
    dst = (Uint8 *)dst + height * dst_pitch;

    ಯದಿ (src == dst) {
        // Need to make a copy of the buffer so we don't clobber it while converting
        tmp = (Uint8 *)SDL_malloc((size_t)2 * UVheight * srcUVPitch);
        ಯದಿ (!tmp) {
            ಪ್ರತ್ಯಾಗಮ false;
        }
        SDL_memcpy(tmp, src, (size_t)2 * UVheight * srcUVPitch);
        src = tmp;
    }

    ಯದಿ (reverseUV) {
        src2 = (ಧ್ರುವ Uint8 *)src;
        src1 = src2 + UVheight * srcUVPitch;
    } ಅನ್ಯಥಾ {
        src1 = (ಧ್ರುವ Uint8 *)src;
        src2 = src1 + UVheight * srcUVPitch;
    }
    dstUV = (Uint8 *)dst;

    y = UVheight;
    ಯಾವತ್ (y--) {
        x = UVwidth;
        ಯಾವತ್ (x--) {
            *dstUV++ = *src1++;
            *dstUV++ = *src2++;
        }
        src1 += src_UVPitch_ಎಡ;
        src2 += src_UVPitch_ಎಡ;
        dstUV += dst_UVPitch_ಎಡ;
    }

    SDL_free(tmp);
    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ bool SDL_ConvertPixels_SplitNV_to_UVPlanes_std(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, ಧ್ರುವ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಙ್ಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಙ್ಕ dst_pitch, bool reverseUV)
{
    ಪೂರ್ಣಾಙ್ಕ x, y;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ UVwidth = (width + 1) / 2;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ UVheight = (height + 1) / 2;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ srcUVPitch = ((src_pitch + 1) / 2) * 2;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ src_UVPitch_ಎಡ = srcUVPitch - UVwidth * 2;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ dstUVPitch = ((dst_pitch + 1) / 2);
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ dst_UVPitch_ಎಡ = dstUVPitch - UVwidth;
    ಧ್ರುವ Uint8 *srcUV;
    Uint8 *dst1, *dst2;
    Uint8 *tmp = ರಿಕ್ತ;

    // Skip the Y plane
    src = (ಧ್ರುವ Uint8 *)src + height * src_pitch;
    dst = (Uint8 *)dst + height * dst_pitch;

    ಯದಿ (src == dst) {
        // Need to make a copy of the buffer so we don't clobber it while converting
        tmp = (Uint8 *)SDL_malloc((size_t)UVheight * srcUVPitch);
        ಯದಿ (!tmp) {
            ಪ್ರತ್ಯಾಗಮ false;
        }
        SDL_memcpy(tmp, src, (size_t)UVheight * srcUVPitch);
        src = tmp;
    }

    ಯದಿ (reverseUV) {
        dst2 = (Uint8 *)dst;
        dst1 = dst2 + UVheight * dstUVPitch;
    } ಅನ್ಯಥಾ {
        dst1 = (Uint8 *)dst;
        dst2 = dst1 + UVheight * dstUVPitch;
    }
    srcUV = (ಧ್ರುವ Uint8 *)src;

    y = UVheight;
    ಯಾವತ್ (y--) {
        x = UVwidth;
        ಯಾವತ್ (x--) {
            *dst1++ = *srcUV++;
            *dst2++ = *srcUV++;
        }
        srcUV += src_UVPitch_ಎಡ;
        dst1 += dst_UVPitch_ಎಡ;
        dst2 += dst_UVPitch_ಎಡ;
    }

    SDL_free(tmp);
    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ bool SDL_ConvertPixels_SwapNV_std(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, ಧ್ರುವ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಙ್ಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಙ್ಕ dst_pitch)
{
    ಪೂರ್ಣಾಙ್ಕ x, y;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ UVwidth = (width + 1) / 2;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ UVheight = (height + 1) / 2;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ srcUVPitch = ((src_pitch + 1) / 2) * 2;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ dstUVPitch = ((dst_pitch + 1) / 2) * 2;

    // Skip the Y plane
    src = (ಧ್ರುವ Uint8 *)src + height * src_pitch;
    dst = (Uint8 *)dst + height * dst_pitch;

    bool aligned = (((uintptr_t)src | (uintptr_t)dst) & 1) == 0;
    ಯದಿ (aligned) {
        ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ src_UVPitch_ಎಡ = (srcUVPitch - UVwidth * 2) / ಪರಿಮಾಣ(Uint16);
        ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ dst_UVPitch_ಎಡ = (dstUVPitch - UVwidth * 2) / ಪರಿಮಾಣ(Uint16);
        ಧ್ರುವ Uint16 *srcUV = (ಧ್ರುವ Uint16 *)src;
        Uint16 *dstUV = (Uint16 *)dst;
        y = UVheight;
        ಯಾವತ್ (y--) {
            x = UVwidth;
            ಯಾವತ್ (x--) {
                *dstUV++ = SDL_Swap16(*srcUV++);
            }
            srcUV += src_UVPitch_ಎಡ;
            dstUV += dst_UVPitch_ಎಡ;
        }
    } ಅನ್ಯಥಾ {
        ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ src_UVPitch_ಎಡ = (srcUVPitch - UVwidth * 2);
        ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ dst_UVPitch_ಎಡ = (dstUVPitch - UVwidth * 2);
        ಧ್ರುವ Uint8 *srcUV = (ಧ್ರುವ Uint8 *)src;
        Uint8 *dstUV = (Uint8 *)dst;
        y = UVheight;
        ಯಾವತ್ (y--) {
            x = UVwidth;
            ಯಾವತ್ (x--) {
                Uint8 u = *srcUV++;
                Uint8 v = *srcUV++;
                *dstUV++ = v;
                *dstUV++ = u;
            }
            srcUV += src_UVPitch_ಎಡ;
            dstUV += dst_UVPitch_ಎಡ;
        }
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ bool SDL_ConvertPixels_PackUVPlanes_to_NV(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, ಧ್ರುವ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಙ್ಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಙ್ಕ dst_pitch, bool reverseUV)
{
#ifdef SDL_SSE2_INTRINSICS
    ಯದಿ (SDL_HasSSE2()) {
      ಪ್ರತ್ಯಾಗಮ SDL_ConvertPixels_PackUVPlanes_to_NV_SSE2(width, height, src, src_pitch, dst, dst_pitch, reverseUV);
    }
#endif
    ಪ್ರತ್ಯಾಗಮ SDL_ConvertPixels_PackUVPlanes_to_NV_std(width, height, src, src_pitch, dst, dst_pitch, reverseUV);
}

ಸ್ಥಿರ bool SDL_ConvertPixels_SplitNV_to_UVPlanes(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, ಧ್ರುವ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಙ್ಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಙ್ಕ dst_pitch, bool reverseUV)
{
#ifdef SDL_SSE2_INTRINSICS
    ಯದಿ (SDL_HasSSE2()) {
      ಪ್ರತ್ಯಾಗಮ SDL_ConvertPixels_SplitNV_to_UVPlanes_SSE2(width, height, src, src_pitch, dst, dst_pitch, reverseUV);
    }
#endif
    ಪ್ರತ್ಯಾಗಮ SDL_ConvertPixels_SplitNV_to_UVPlanes_std(width, height, src, src_pitch, dst, dst_pitch, reverseUV);
}

ಸ್ಥಿರ bool SDL_ConvertPixels_SwapNV(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, ಧ್ರುವ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಙ್ಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಙ್ಕ dst_pitch)
{
#ifdef SDL_SSE2_INTRINSICS
    ಯದಿ (SDL_HasSSE2()) {
      ಪ್ರತ್ಯಾಗಮ SDL_ConvertPixels_SwapNV_SSE2(width, height, src, src_pitch, dst, dst_pitch);
    }
#endif
    ಪ್ರತ್ಯಾಗಮ SDL_ConvertPixels_SwapNV_std(width, height, src, src_pitch, dst, dst_pitch);
}

ಸ್ಥಿರ bool SDL_ConvertPixels_Planar2x2_to_Planar2x2(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height,
                                                     SDL_PixelFormat src_format, ಧ್ರುವ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಙ್ಕ src_pitch,
                                                     SDL_PixelFormat dst_format, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಙ್ಕ dst_pitch)
{
    ಯದಿ (src != dst) {
        // Copy Y plane
        ಪೂರ್ಣಾಙ್ಕ i;
        ಧ್ರುವ Uint8 *srcY = (ಧ್ರುವ Uint8 *)src;
        Uint8 *dstY = (Uint8 *)dst;
        ಪ್ರತಿ (i = height; i--;) {
            SDL_memcpy(dstY, srcY, width);
            srcY += src_pitch;
            dstY += dst_pitch;
        }
    }

    ವಿಕಲ್ಪ (src_format) {
    ಪಕ್ಷ SDL_PIXELFORMAT_YV12:
        ವಿಕಲ್ಪ (dst_format) {
        ಪಕ್ಷ SDL_PIXELFORMAT_IYUV:
            ಪ್ರತ್ಯಾಗಮ SDL_ConvertPixels_SwapUVPlanes(width, height, src, src_pitch, dst, dst_pitch);
        ಪಕ್ಷ SDL_PIXELFORMAT_NV12:
            ಪ್ರತ್ಯಾಗಮ SDL_ConvertPixels_PackUVPlanes_to_NV(width, height, src, src_pitch, dst, dst_pitch, true);
        ಪಕ್ಷ SDL_PIXELFORMAT_NV21:
            ಪ್ರತ್ಯಾಗಮ SDL_ConvertPixels_PackUVPlanes_to_NV(width, height, src, src_pitch, dst, dst_pitch, false);
        ಸ್ವಭಾವ:
            ಭಙ್ಗ;
        }
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_PIXELFORMAT_IYUV:
        ವಿಕಲ್ಪ (dst_format) {
        ಪಕ್ಷ SDL_PIXELFORMAT_YV12:
            ಪ್ರತ್ಯಾಗಮ SDL_ConvertPixels_SwapUVPlanes(width, height, src, src_pitch, dst, dst_pitch);
        ಪಕ್ಷ SDL_PIXELFORMAT_NV12:
            ಪ್ರತ್ಯಾಗಮ SDL_ConvertPixels_PackUVPlanes_to_NV(width, height, src, src_pitch, dst, dst_pitch, false);
        ಪಕ್ಷ SDL_PIXELFORMAT_NV21:
            ಪ್ರತ್ಯಾಗಮ SDL_ConvertPixels_PackUVPlanes_to_NV(width, height, src, src_pitch, dst, dst_pitch, true);
        ಸ್ವಭಾವ:
            ಭಙ್ಗ;
        }
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_PIXELFORMAT_NV12:
        ವಿಕಲ್ಪ (dst_format) {
        ಪಕ್ಷ SDL_PIXELFORMAT_YV12:
            ಪ್ರತ್ಯಾಗಮ SDL_ConvertPixels_SplitNV_to_UVPlanes(width, height, src, src_pitch, dst, dst_pitch, true);
        ಪಕ್ಷ SDL_PIXELFORMAT_IYUV:
            ಪ್ರತ್ಯಾಗಮ SDL_ConvertPixels_SplitNV_to_UVPlanes(width, height, src, src_pitch, dst, dst_pitch, false);
        ಪಕ್ಷ SDL_PIXELFORMAT_NV21:
            ಪ್ರತ್ಯಾಗಮ SDL_ConvertPixels_SwapNV(width, height, src, src_pitch, dst, dst_pitch);
        ಸ್ವಭಾವ:
            ಭಙ್ಗ;
        }
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_PIXELFORMAT_NV21:
        ವಿಕಲ್ಪ (dst_format) {
        ಪಕ್ಷ SDL_PIXELFORMAT_YV12:
            ಪ್ರತ್ಯಾಗಮ SDL_ConvertPixels_SplitNV_to_UVPlanes(width, height, src, src_pitch, dst, dst_pitch, false);
        ಪಕ್ಷ SDL_PIXELFORMAT_IYUV:
            ಪ್ರತ್ಯಾಗಮ SDL_ConvertPixels_SplitNV_to_UVPlanes(width, height, src, src_pitch, dst, dst_pitch, true);
        ಪಕ್ಷ SDL_PIXELFORMAT_NV12:
            ಪ್ರತ್ಯಾಗಮ SDL_ConvertPixels_SwapNV(width, height, src, src_pitch, dst, dst_pitch);
        ಸ್ವಭಾವ:
            ಭಙ್ಗ;
        }
        ಭಙ್ಗ;
    ಸ್ವಭಾವ:
        ಭಙ್ಗ;
    }
    ಪ್ರತ್ಯಾಗಮ SDL_SetError("SDL_ConvertPixels_Planar2x2_to_Planar2x2: Unsupported YUV conversion: %s -> %s", SDL_GetPixelFormatName(src_format),
                        SDL_GetPixelFormatName(dst_format));
}

#ifdef SDL_SSE2_INTRINSICS
#define PACKED4_TO_PACKED4_ROW_SSE2(shuffle)                      \
    ಯಾವತ್ (x >= 4) {                                              \
        __m128i yuv = _mm_loadu_si128((__m128i *)srcYUV);         \
        __m128i lo = _mm_unpacklo_epi8(yuv, _mm_setzero_si128()); \
        __m128i hi = _mm_unpackhi_epi8(yuv, _mm_setzero_si128()); \
        lo = _mm_shufflelo_epi16(lo, shuffle);                    \
        lo = _mm_shufflehi_epi16(lo, shuffle);                    \
        hi = _mm_shufflelo_epi16(hi, shuffle);                    \
        hi = _mm_shufflehi_epi16(hi, shuffle);                    \
        yuv = _mm_packus_epi16(lo, hi);                           \
        _mm_storeu_si128((__m128i *)dstYUV, yuv);                 \
        srcYUV += 16;                                             \
        dstYUV += 16;                                             \
        x -= 4;                                                   \
    }

ಸ್ಥಿರ bool SDL_TARGETING("sse2") SDL_ConvertPixels_YUY2_to_UYVY_SSE2(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, ಧ್ರುವ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಙ್ಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಙ್ಕ dst_pitch)
{
    ಪೂರ್ಣಾಙ್ಕ x, y;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ YUVwidth = (width + 1) / 2;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ src_YUVPitch_ಎಡ = (src_pitch - YUVwidth * 4);
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ dst_YUVPitch_ಎಡ = (dst_pitch - YUVwidth * 4);
    ಧ್ರುವ Uint8 *srcYUV = (ಧ್ರುವ Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = height;
    x = YUVwidth;
    ಯಾವತ್ (y--) {
        PACKED4_TO_PACKED4_ROW_SSE2(_MM_SHUFFLE(2, 3, 0, 1));
        ಯಾವತ್ (x--) {
            Uint8 Y1, U, Y2, V;

            Y1 = srcYUV[0];
            U = srcYUV[1];
            Y2 = srcYUV[2];
            V = srcYUV[3];
            srcYUV += 4;

            dstYUV[0] = U;
            dstYUV[1] = Y1;
            dstYUV[2] = V;
            dstYUV[3] = Y2;
            dstYUV += 4;
        }
        srcYUV += src_YUVPitch_ಎಡ;
        dstYUV += dst_YUVPitch_ಎಡ;
        x = YUVwidth;
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ bool SDL_TARGETING("sse2") SDL_ConvertPixels_YUY2_to_YVYU_SSE2(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, ಧ್ರುವ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಙ್ಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಙ್ಕ dst_pitch)
{
    ಪೂರ್ಣಾಙ್ಕ x, y;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ YUVwidth = (width + 1) / 2;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ src_YUVPitch_ಎಡ = (src_pitch - YUVwidth * 4);
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ dst_YUVPitch_ಎಡ = (dst_pitch - YUVwidth * 4);
    ಧ್ರುವ Uint8 *srcYUV = (ಧ್ರುವ Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = height;
    x = YUVwidth;
    ಯಾವತ್ (y--) {
        PACKED4_TO_PACKED4_ROW_SSE2(_MM_SHUFFLE(1, 2, 3, 0));
        ಯಾವತ್ (x--) {
            Uint8 Y1, U, Y2, V;

            Y1 = srcYUV[0];
            U = srcYUV[1];
            Y2 = srcYUV[2];
            V = srcYUV[3];
            srcYUV += 4;

            dstYUV[0] = Y1;
            dstYUV[1] = V;
            dstYUV[2] = Y2;
            dstYUV[3] = U;
            dstYUV += 4;
        }
        srcYUV += src_YUVPitch_ಎಡ;
        dstYUV += dst_YUVPitch_ಎಡ;
        x = YUVwidth;
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ bool SDL_TARGETING("sse2") SDL_ConvertPixels_UYVY_to_YUY2_SSE2(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, ಧ್ರುವ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಙ್ಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಙ್ಕ dst_pitch)
{
    ಪೂರ್ಣಾಙ್ಕ x, y;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ YUVwidth = (width + 1) / 2;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ src_YUVPitch_ಎಡ = (src_pitch - YUVwidth * 4);
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ dst_YUVPitch_ಎಡ = (dst_pitch - YUVwidth * 4);
    ಧ್ರುವ Uint8 *srcYUV = (ಧ್ರುವ Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = height;
    x = YUVwidth;
    ಯಾವತ್ (y--) {
        PACKED4_TO_PACKED4_ROW_SSE2(_MM_SHUFFLE(2, 3, 0, 1));
        ಯಾವತ್ (x--) {
            Uint8 Y1, U, Y2, V;

            U = srcYUV[0];
            Y1 = srcYUV[1];
            V = srcYUV[2];
            Y2 = srcYUV[3];
            srcYUV += 4;

            dstYUV[0] = Y1;
            dstYUV[1] = U;
            dstYUV[2] = Y2;
            dstYUV[3] = V;
            dstYUV += 4;
        }
        srcYUV += src_YUVPitch_ಎಡ;
        dstYUV += dst_YUVPitch_ಎಡ;
        x = YUVwidth;
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ bool SDL_TARGETING("sse2") SDL_ConvertPixels_UYVY_to_YVYU_SSE2(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, ಧ್ರುವ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಙ್ಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಙ್ಕ dst_pitch)
{
    ಪೂರ್ಣಾಙ್ಕ x, y;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ YUVwidth = (width + 1) / 2;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ src_YUVPitch_ಎಡ = (src_pitch - YUVwidth * 4);
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ dst_YUVPitch_ಎಡ = (dst_pitch - YUVwidth * 4);
    ಧ್ರುವ Uint8 *srcYUV = (ಧ್ರುವ Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = height;
    x = YUVwidth;
    ಯಾವತ್ (y--) {
        PACKED4_TO_PACKED4_ROW_SSE2(_MM_SHUFFLE(0, 3, 2, 1));
        ಯಾವತ್ (x--) {
            Uint8 Y1, U, Y2, V;

            U = srcYUV[0];
            Y1 = srcYUV[1];
            V = srcYUV[2];
            Y2 = srcYUV[3];
            srcYUV += 4;

            dstYUV[0] = Y1;
            dstYUV[1] = V;
            dstYUV[2] = Y2;
            dstYUV[3] = U;
            dstYUV += 4;
        }
        srcYUV += src_YUVPitch_ಎಡ;
        dstYUV += dst_YUVPitch_ಎಡ;
        x = YUVwidth;
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ bool SDL_TARGETING("sse2") SDL_ConvertPixels_YVYU_to_YUY2_SSE2(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, ಧ್ರುವ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಙ್ಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಙ್ಕ dst_pitch)
{
    ಪೂರ್ಣಾಙ್ಕ x, y;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ YUVwidth = (width + 1) / 2;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ src_YUVPitch_ಎಡ = (src_pitch - YUVwidth * 4);
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ dst_YUVPitch_ಎಡ = (dst_pitch - YUVwidth * 4);
    ಧ್ರುವ Uint8 *srcYUV = (ಧ್ರುವ Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = height;
    x = YUVwidth;
    ಯಾವತ್ (y--) {
        PACKED4_TO_PACKED4_ROW_SSE2(_MM_SHUFFLE(1, 2, 3, 0));
        ಯಾವತ್ (x--) {
            Uint8 Y1, U, Y2, V;

            Y1 = srcYUV[0];
            V = srcYUV[1];
            Y2 = srcYUV[2];
            U = srcYUV[3];
            srcYUV += 4;

            dstYUV[0] = Y1;
            dstYUV[1] = U;
            dstYUV[2] = Y2;
            dstYUV[3] = V;
            dstYUV += 4;
        }
        srcYUV += src_YUVPitch_ಎಡ;
        dstYUV += dst_YUVPitch_ಎಡ;
        x = YUVwidth;
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ bool SDL_TARGETING("sse2") SDL_ConvertPixels_YVYU_to_UYVY_SSE2(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, ಧ್ರುವ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಙ್ಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಙ್ಕ dst_pitch)
{
    ಪೂರ್ಣಾಙ್ಕ x, y;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ YUVwidth = (width + 1) / 2;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ src_YUVPitch_ಎಡ = (src_pitch - YUVwidth * 4);
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ dst_YUVPitch_ಎಡ = (dst_pitch - YUVwidth * 4);
    ಧ್ರುವ Uint8 *srcYUV = (ಧ್ರುವ Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = height;
    x = YUVwidth;
    ಯಾವತ್ (y--) {
        PACKED4_TO_PACKED4_ROW_SSE2(_MM_SHUFFLE(2, 1, 0, 3));
        ಯಾವತ್ (x--) {
            Uint8 Y1, U, Y2, V;

            Y1 = srcYUV[0];
            V = srcYUV[1];
            Y2 = srcYUV[2];
            U = srcYUV[3];
            srcYUV += 4;

            dstYUV[0] = U;
            dstYUV[1] = Y1;
            dstYUV[2] = V;
            dstYUV[3] = Y2;
            dstYUV += 4;
        }
        srcYUV += src_YUVPitch_ಎಡ;
        dstYUV += dst_YUVPitch_ಎಡ;
        x = YUVwidth;
    }
    ಪ್ರತ್ಯಾಗಮ true;
}
#endif

ಸ್ಥಿರ bool SDL_ConvertPixels_YUY2_to_UYVY_std(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, ಧ್ರುವ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಙ್ಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಙ್ಕ dst_pitch)
{
    ಪೂರ್ಣಾಙ್ಕ x, y;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ YUVwidth = (width + 1) / 2;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ src_YUVPitch_ಎಡ = (src_pitch - YUVwidth * 4);
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ dst_YUVPitch_ಎಡ = (dst_pitch - YUVwidth * 4);
    ಧ್ರುವ Uint8 *srcYUV = (ಧ್ರುವ Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = height;
    ಯಾವತ್ (y--) {
        x = YUVwidth;
        ಯಾವತ್ (x--) {
            Uint8 Y1, U, Y2, V;

            Y1 = srcYUV[0];
            U = srcYUV[1];
            Y2 = srcYUV[2];
            V = srcYUV[3];
            srcYUV += 4;

            dstYUV[0] = U;
            dstYUV[1] = Y1;
            dstYUV[2] = V;
            dstYUV[3] = Y2;
            dstYUV += 4;
        }
        srcYUV += src_YUVPitch_ಎಡ;
        dstYUV += dst_YUVPitch_ಎಡ;
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ bool SDL_ConvertPixels_YUY2_to_YVYU_std(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, ಧ್ರುವ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಙ್ಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಙ್ಕ dst_pitch)
{
    ಪೂರ್ಣಾಙ್ಕ x, y;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ YUVwidth = (width + 1) / 2;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ src_YUVPitch_ಎಡ = (src_pitch - YUVwidth * 4);
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ dst_YUVPitch_ಎಡ = (dst_pitch - YUVwidth * 4);
    ಧ್ರುವ Uint8 *srcYUV = (ಧ್ರುವ Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = height;
    ಯಾವತ್ (y--) {
        x = YUVwidth;
        ಯಾವತ್ (x--) {
            Uint8 Y1, U, Y2, V;

            Y1 = srcYUV[0];
            U = srcYUV[1];
            Y2 = srcYUV[2];
            V = srcYUV[3];
            srcYUV += 4;

            dstYUV[0] = Y1;
            dstYUV[1] = V;
            dstYUV[2] = Y2;
            dstYUV[3] = U;
            dstYUV += 4;
        }
        srcYUV += src_YUVPitch_ಎಡ;
        dstYUV += dst_YUVPitch_ಎಡ;
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ bool SDL_ConvertPixels_UYVY_to_YUY2_std(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, ಧ್ರುವ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಙ್ಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಙ್ಕ dst_pitch)
{
    ಪೂರ್ಣಾಙ್ಕ x, y;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ YUVwidth = (width + 1) / 2;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ src_YUVPitch_ಎಡ = (src_pitch - YUVwidth * 4);
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ dst_YUVPitch_ಎಡ = (dst_pitch - YUVwidth * 4);
    ಧ್ರುವ Uint8 *srcYUV = (ಧ್ರುವ Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = height;
    ಯಾವತ್ (y--) {
        x = YUVwidth;
        ಯಾವತ್ (x--) {
            Uint8 Y1, U, Y2, V;

            U = srcYUV[0];
            Y1 = srcYUV[1];
            V = srcYUV[2];
            Y2 = srcYUV[3];
            srcYUV += 4;

            dstYUV[0] = Y1;
            dstYUV[1] = U;
            dstYUV[2] = Y2;
            dstYUV[3] = V;
            dstYUV += 4;
        }
        srcYUV += src_YUVPitch_ಎಡ;
        dstYUV += dst_YUVPitch_ಎಡ;
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ bool SDL_ConvertPixels_UYVY_to_YVYU_std(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, ಧ್ರುವ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಙ್ಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಙ್ಕ dst_pitch)
{
    ಪೂರ್ಣಾಙ್ಕ x, y;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ YUVwidth = (width + 1) / 2;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ src_YUVPitch_ಎಡ = (src_pitch - YUVwidth * 4);
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ dst_YUVPitch_ಎಡ = (dst_pitch - YUVwidth * 4);
    ಧ್ರುವ Uint8 *srcYUV = (ಧ್ರುವ Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = height;
    ಯಾವತ್ (y--) {
        x = YUVwidth;
        ಯಾವತ್ (x--) {
            Uint8 Y1, U, Y2, V;

            U = srcYUV[0];
            Y1 = srcYUV[1];
            V = srcYUV[2];
            Y2 = srcYUV[3];
            srcYUV += 4;

            dstYUV[0] = Y1;
            dstYUV[1] = V;
            dstYUV[2] = Y2;
            dstYUV[3] = U;
            dstYUV += 4;
        }
        srcYUV += src_YUVPitch_ಎಡ;
        dstYUV += dst_YUVPitch_ಎಡ;
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ bool SDL_ConvertPixels_YVYU_to_YUY2_std(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, ಧ್ರುವ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಙ್ಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಙ್ಕ dst_pitch)
{
    ಪೂರ್ಣಾಙ್ಕ x, y;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ YUVwidth = (width + 1) / 2;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ src_YUVPitch_ಎಡ = (src_pitch - YUVwidth * 4);
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ dst_YUVPitch_ಎಡ = (dst_pitch - YUVwidth * 4);
    ಧ್ರುವ Uint8 *srcYUV = (ಧ್ರುವ Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = height;
    ಯಾವತ್ (y--) {
        x = YUVwidth;
        ಯಾವತ್ (x--) {
            Uint8 Y1, U, Y2, V;

            Y1 = srcYUV[0];
            V = srcYUV[1];
            Y2 = srcYUV[2];
            U = srcYUV[3];
            srcYUV += 4;

            dstYUV[0] = Y1;
            dstYUV[1] = U;
            dstYUV[2] = Y2;
            dstYUV[3] = V;
            dstYUV += 4;
        }
        srcYUV += src_YUVPitch_ಎಡ;
        dstYUV += dst_YUVPitch_ಎಡ;
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ bool SDL_ConvertPixels_YVYU_to_UYVY_std(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, ಧ್ರುವ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಙ್ಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಙ್ಕ dst_pitch)
{
    ಪೂರ್ಣಾಙ್ಕ x, y;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ YUVwidth = (width + 1) / 2;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ src_YUVPitch_ಎಡ = (src_pitch - YUVwidth * 4);
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ dst_YUVPitch_ಎಡ = (dst_pitch - YUVwidth * 4);
    ಧ್ರುವ Uint8 *srcYUV = (ಧ್ರುವ Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = height;
    ಯಾವತ್ (y--) {
        x = YUVwidth;
        ಯಾವತ್ (x--) {
            Uint8 Y1, U, Y2, V;

            Y1 = srcYUV[0];
            V = srcYUV[1];
            Y2 = srcYUV[2];
            U = srcYUV[3];
            srcYUV += 4;

            dstYUV[0] = U;
            dstYUV[1] = Y1;
            dstYUV[2] = V;
            dstYUV[3] = Y2;
            dstYUV += 4;
        }
        srcYUV += src_YUVPitch_ಎಡ;
        dstYUV += dst_YUVPitch_ಎಡ;
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ bool SDL_ConvertPixels_YUY2_to_UYVY(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, ಧ್ರುವ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಙ್ಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಙ್ಕ dst_pitch)
{
#ifdef SDL_SSE2_INTRINSICS
    ಯದಿ (SDL_HasSSE2()) {
      ಪ್ರತ್ಯಾಗಮ SDL_ConvertPixels_YUY2_to_UYVY_SSE2(width, height, src, src_pitch, dst, dst_pitch);
    }
#endif
    ಪ್ರತ್ಯಾಗಮ SDL_ConvertPixels_YUY2_to_UYVY_std(width, height, src, src_pitch, dst, dst_pitch);
}

ಸ್ಥಿರ bool SDL_ConvertPixels_YUY2_to_YVYU(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, ಧ್ರುವ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಙ್ಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಙ್ಕ dst_pitch)
{
#ifdef SDL_SSE2_INTRINSICS
    ಯದಿ (SDL_HasSSE2()) {
      ಪ್ರತ್ಯಾಗಮ SDL_ConvertPixels_YUY2_to_YVYU_SSE2(width, height, src, src_pitch, dst, dst_pitch);
    }
#endif
    ಪ್ರತ್ಯಾಗಮ SDL_ConvertPixels_YUY2_to_YVYU_std(width, height, src, src_pitch, dst, dst_pitch);
}

ಸ್ಥಿರ bool SDL_ConvertPixels_UYVY_to_YUY2(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, ಧ್ರುವ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಙ್ಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಙ್ಕ dst_pitch)
{
#ifdef SDL_SSE2_INTRINSICS
    ಯದಿ (SDL_HasSSE2()) {
      ಪ್ರತ್ಯಾಗಮ SDL_ConvertPixels_UYVY_to_YUY2_SSE2(width, height, src, src_pitch, dst, dst_pitch);
    }
#endif
    ಪ್ರತ್ಯಾಗಮ SDL_ConvertPixels_UYVY_to_YUY2_std(width, height, src, src_pitch, dst, dst_pitch);
}

ಸ್ಥಿರ bool SDL_ConvertPixels_UYVY_to_YVYU(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, ಧ್ರುವ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಙ್ಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಙ್ಕ dst_pitch)
{
#ifdef SDL_SSE2_INTRINSICS
    ಯದಿ (SDL_HasSSE2()) {
      ಪ್ರತ್ಯಾಗಮ SDL_ConvertPixels_UYVY_to_YVYU_SSE2(width, height, src, src_pitch, dst, dst_pitch);
    }
#endif
    ಪ್ರತ್ಯಾಗಮ SDL_ConvertPixels_UYVY_to_YVYU_std(width, height, src, src_pitch, dst, dst_pitch);
}

ಸ್ಥಿರ bool SDL_ConvertPixels_YVYU_to_YUY2(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, ಧ್ರುವ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಙ್ಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಙ್ಕ dst_pitch)
{
#ifdef SDL_SSE2_INTRINSICS
    ಯದಿ (SDL_HasSSE2()) {
      ಪ್ರತ್ಯಾಗಮ SDL_ConvertPixels_YVYU_to_YUY2_SSE2(width, height, src, src_pitch, dst, dst_pitch);
    }
#endif
    ಪ್ರತ್ಯಾಗಮ SDL_ConvertPixels_YVYU_to_YUY2_std(width, height, src, src_pitch, dst, dst_pitch);
}

ಸ್ಥಿರ bool SDL_ConvertPixels_YVYU_to_UYVY(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, ಧ್ರುವ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಙ್ಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಙ್ಕ dst_pitch)
{
#ifdef SDL_SSE2_INTRINSICS
    ಯದಿ (SDL_HasSSE2()) {
      ಪ್ರತ್ಯಾಗಮ SDL_ConvertPixels_YVYU_to_UYVY_SSE2(width, height, src, src_pitch, dst, dst_pitch);
    }
#endif
    ಪ್ರತ್ಯಾಗಮ SDL_ConvertPixels_YVYU_to_UYVY_std(width, height, src, src_pitch, dst, dst_pitch);
}

ಸ್ಥಿರ bool SDL_ConvertPixels_Packed4_to_Packed4(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height,
                                                SDL_PixelFormat src_format, ಧ್ರುವ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಙ್ಕ src_pitch,
                                                SDL_PixelFormat dst_format, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಙ್ಕ dst_pitch)
{
    ವಿಕಲ್ಪ (src_format) {
    ಪಕ್ಷ SDL_PIXELFORMAT_YUY2:
        ವಿಕಲ್ಪ (dst_format) {
        ಪಕ್ಷ SDL_PIXELFORMAT_UYVY:
            ಪ್ರತ್ಯಾಗಮ SDL_ConvertPixels_YUY2_to_UYVY(width, height, src, src_pitch, dst, dst_pitch);
        ಪಕ್ಷ SDL_PIXELFORMAT_YVYU:
            ಪ್ರತ್ಯಾಗಮ SDL_ConvertPixels_YUY2_to_YVYU(width, height, src, src_pitch, dst, dst_pitch);
        ಸ್ವಭಾವ:
            ಭಙ್ಗ;
        }
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_PIXELFORMAT_UYVY:
        ವಿಕಲ್ಪ (dst_format) {
        ಪಕ್ಷ SDL_PIXELFORMAT_YUY2:
            ಪ್ರತ್ಯಾಗಮ SDL_ConvertPixels_UYVY_to_YUY2(width, height, src, src_pitch, dst, dst_pitch);
        ಪಕ್ಷ SDL_PIXELFORMAT_YVYU:
            ಪ್ರತ್ಯಾಗಮ SDL_ConvertPixels_UYVY_to_YVYU(width, height, src, src_pitch, dst, dst_pitch);
        ಸ್ವಭಾವ:
            ಭಙ್ಗ;
        }
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_PIXELFORMAT_YVYU:
        ವಿಕಲ್ಪ (dst_format) {
        ಪಕ್ಷ SDL_PIXELFORMAT_YUY2:
            ಪ್ರತ್ಯಾಗಮ SDL_ConvertPixels_YVYU_to_YUY2(width, height, src, src_pitch, dst, dst_pitch);
        ಪಕ್ಷ SDL_PIXELFORMAT_UYVY:
            ಪ್ರತ್ಯಾಗಮ SDL_ConvertPixels_YVYU_to_UYVY(width, height, src, src_pitch, dst, dst_pitch);
        ಸ್ವಭಾವ:
            ಭಙ್ಗ;
        }
        ಭಙ್ಗ;
    ಸ್ವಭಾವ:
        ಭಙ್ಗ;
    }
    ಪ್ರತ್ಯಾಗಮ SDL_SetError("SDL_ConvertPixels_Packed4_to_Packed4: Unsupported YUV conversion: %s -> %s", SDL_GetPixelFormatName(src_format),
                        SDL_GetPixelFormatName(dst_format));
}

ಸ್ಥಿರ bool SDL_ConvertPixels_Planar2x2_to_Packed4(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height,
                                                   SDL_PixelFormat src_format, ಧ್ರುವ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಙ್ಕ src_pitch,
                                                   SDL_PixelFormat dst_format, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಙ್ಕ dst_pitch)
{
    ಪೂರ್ಣಾಙ್ಕ x, y;
    ಧ್ರುವ Uint8 *srcY1, *srcY2, *srcU, *srcV;
    Uint32 srcY_pitch, srcUV_pitch;
    Uint32 src_Y_pitch_ಎಡ, src_UV_pitch_ಎಡ, srcUV_pixel_stride;
    Uint8 *dstY1, *dstY2, *dstU1, *dstU2, *dstV1, *dstV2;
    Uint32 dstY_pitch, dstUV_pitch;
    Uint32 dst_pitch_ಎಡ;

    ಯದಿ (src == dst) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Can't change YUV plane types in-place");
    }

    ಯದಿ (!GetYUVPlanes(width, height, src_format, src, src_pitch,
                      &srcY1, &srcU, &srcV, &srcY_pitch, &srcUV_pitch)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }
    srcY2 = srcY1 + srcY_pitch;
    src_Y_pitch_ಎಡ = (srcY_pitch - width);

    ಯದಿ (src_format == SDL_PIXELFORMAT_NV12 || src_format == SDL_PIXELFORMAT_NV21) {
        srcUV_pixel_stride = 2;
        src_UV_pitch_ಎಡ = (srcUV_pitch - 2 * ((width + 1) / 2));
    } ಅನ್ಯಥಾ {
        srcUV_pixel_stride = 1;
        src_UV_pitch_ಎಡ = (srcUV_pitch - ((width + 1) / 2));
    }

    ಯದಿ (!GetYUVPlanes(width, height, dst_format, dst, dst_pitch,
                      (ಧ್ರುವ Uint8 **)&dstY1, (ಧ್ರುವ Uint8 **)&dstU1, (ಧ್ರುವ Uint8 **)&dstV1,
                      &dstY_pitch, &dstUV_pitch)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }
    dstY2 = dstY1 + dstY_pitch;
    dstU2 = dstU1 + dstUV_pitch;
    dstV2 = dstV1 + dstUV_pitch;
    dst_pitch_ಎಡ = (dstY_pitch - 4 * ((width + 1) / 2));

    // Copy 2x2 blocks of pixels at a time
    ಪ್ರತಿ (y = 0; y < (height - 1); y += 2) {
        ಪ್ರತಿ (x = 0; x < (width - 1); x += 2) {
            // Row 1
            *dstY1 = *srcY1++;
            dstY1 += 2;
            *dstY1 = *srcY1++;
            dstY1 += 2;
            *dstU1 = *srcU;
            *dstV1 = *srcV;

            // Row 2
            *dstY2 = *srcY2++;
            dstY2 += 2;
            *dstY2 = *srcY2++;
            dstY2 += 2;
            *dstU2 = *srcU;
            *dstV2 = *srcV;

            srcU += srcUV_pixel_stride;
            srcV += srcUV_pixel_stride;
            dstU1 += 4;
            dstU2 += 4;
            dstV1 += 4;
            dstV2 += 4;
        }

        // Last column
        ಯದಿ (x == (width - 1)) {
            // Row 1
            *dstY1 = *srcY1;
            dstY1 += 2;
            *dstY1 = *srcY1++;
            dstY1 += 2;
            *dstU1 = *srcU;
            *dstV1 = *srcV;

            // Row 2
            *dstY2 = *srcY2;
            dstY2 += 2;
            *dstY2 = *srcY2++;
            dstY2 += 2;
            *dstU2 = *srcU;
            *dstV2 = *srcV;

            srcU += srcUV_pixel_stride;
            srcV += srcUV_pixel_stride;
            dstU1 += 4;
            dstU2 += 4;
            dstV1 += 4;
            dstV2 += 4;
        }

        srcY1 += src_Y_pitch_ಎಡ + srcY_pitch;
        srcY2 += src_Y_pitch_ಎಡ + srcY_pitch;
        srcU += src_UV_pitch_ಎಡ;
        srcV += src_UV_pitch_ಎಡ;
        dstY1 += dst_pitch_ಎಡ + dstY_pitch;
        dstY2 += dst_pitch_ಎಡ + dstY_pitch;
        dstU1 += dst_pitch_ಎಡ + dstUV_pitch;
        dstU2 += dst_pitch_ಎಡ + dstUV_pitch;
        dstV1 += dst_pitch_ಎಡ + dstUV_pitch;
        dstV2 += dst_pitch_ಎಡ + dstUV_pitch;
    }

    // Last row
    ಯದಿ (y == (height - 1)) {
        ಪ್ರತಿ (x = 0; x < (width - 1); x += 2) {
            // Row 1
            *dstY1 = *srcY1++;
            dstY1 += 2;
            *dstY1 = *srcY1++;
            dstY1 += 2;
            *dstU1 = *srcU;
            *dstV1 = *srcV;

            srcU += srcUV_pixel_stride;
            srcV += srcUV_pixel_stride;
            dstU1 += 4;
            dstV1 += 4;
        }

        // Last column
        ಯದಿ (x == (width - 1)) {
            // Row 1
            *dstY1 = *srcY1;
            dstY1 += 2;
            *dstY1 = *srcY1++;
            dstY1 += 2;
            *dstU1 = *srcU;
            *dstV1 = *srcV;

            srcU += srcUV_pixel_stride;
            srcV += srcUV_pixel_stride;
            dstU1 += 4;
            dstV1 += 4;
        }
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ bool SDL_ConvertPixels_Packed4_to_Planar2x2(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height,
                                                   SDL_PixelFormat src_format, ಧ್ರುವ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಙ್ಕ src_pitch,
                                                   SDL_PixelFormat dst_format, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಙ್ಕ dst_pitch)
{
    ಪೂರ್ಣಾಙ್ಕ x, y;
    ಧ್ರುವ Uint8 *srcY1, *srcY2, *srcU1, *srcU2, *srcV1, *srcV2;
    Uint32 srcY_pitch, srcUV_pitch;
    Uint32 src_pitch_ಎಡ;
    Uint8 *dstY1, *dstY2, *dstU, *dstV;
    Uint32 dstY_pitch, dstUV_pitch;
    Uint32 dst_Y_pitch_ಎಡ, dst_UV_pitch_ಎಡ, dstUV_pixel_stride;

    ಯದಿ (src == dst) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Can't change YUV plane types in-place");
    }

    ಯದಿ (!GetYUVPlanes(width, height, src_format, src, src_pitch,
                      &srcY1, &srcU1, &srcV1, &srcY_pitch, &srcUV_pitch)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }
    srcY2 = srcY1 + srcY_pitch;
    srcU2 = srcU1 + srcUV_pitch;
    srcV2 = srcV1 + srcUV_pitch;
    src_pitch_ಎಡ = (srcY_pitch - 4 * ((width + 1) / 2));

    ಯದಿ (!GetYUVPlanes(width, height, dst_format, dst, dst_pitch,
                      (ಧ್ರುವ Uint8 **)&dstY1, (ಧ್ರುವ Uint8 **)&dstU, (ಧ್ರುವ Uint8 **)&dstV,
                      &dstY_pitch, &dstUV_pitch)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }
    dstY2 = dstY1 + dstY_pitch;
    dst_Y_pitch_ಎಡ = (dstY_pitch - width);

    ಯದಿ (dst_format == SDL_PIXELFORMAT_NV12 || dst_format == SDL_PIXELFORMAT_NV21) {
        dstUV_pixel_stride = 2;
        dst_UV_pitch_ಎಡ = (dstUV_pitch - 2 * ((width + 1) / 2));
    } ಅನ್ಯಥಾ {
        dstUV_pixel_stride = 1;
        dst_UV_pitch_ಎಡ = (dstUV_pitch - ((width + 1) / 2));
    }

    // Copy 2x2 blocks of pixels at a time
    ಪ್ರತಿ (y = 0; y < (height - 1); y += 2) {
        ಪ್ರತಿ (x = 0; x < (width - 1); x += 2) {
            // Row 1
            *dstY1++ = *srcY1;
            srcY1 += 2;
            *dstY1++ = *srcY1;
            srcY1 += 2;

            // Row 2
            *dstY2++ = *srcY2;
            srcY2 += 2;
            *dstY2++ = *srcY2;
            srcY2 += 2;

            *dstU = (Uint8)(((Uint32)*srcU1 + *srcU2) / 2);
            *dstV = (Uint8)(((Uint32)*srcV1 + *srcV2) / 2);

            srcU1 += 4;
            srcU2 += 4;
            srcV1 += 4;
            srcV2 += 4;
            dstU += dstUV_pixel_stride;
            dstV += dstUV_pixel_stride;
        }

        // Last column
        ಯದಿ (x == (width - 1)) {
            // Row 1
            *dstY1 = *srcY1;
            srcY1 += 2;
            *dstY1++ = *srcY1;
            srcY1 += 2;

            // Row 2
            *dstY2 = *srcY2;
            srcY2 += 2;
            *dstY2++ = *srcY2;
            srcY2 += 2;

            *dstU = (Uint8)(((Uint32)*srcU1 + *srcU2) / 2);
            *dstV = (Uint8)(((Uint32)*srcV1 + *srcV2) / 2);

            srcU1 += 4;
            srcU2 += 4;
            srcV1 += 4;
            srcV2 += 4;
            dstU += dstUV_pixel_stride;
            dstV += dstUV_pixel_stride;
        }

        srcY1 += src_pitch_ಎಡ + srcY_pitch;
        srcY2 += src_pitch_ಎಡ + srcY_pitch;
        srcU1 += src_pitch_ಎಡ + srcUV_pitch;
        srcU2 += src_pitch_ಎಡ + srcUV_pitch;
        srcV1 += src_pitch_ಎಡ + srcUV_pitch;
        srcV2 += src_pitch_ಎಡ + srcUV_pitch;
        dstY1 += dst_Y_pitch_ಎಡ + dstY_pitch;
        dstY2 += dst_Y_pitch_ಎಡ + dstY_pitch;
        dstU += dst_UV_pitch_ಎಡ;
        dstV += dst_UV_pitch_ಎಡ;
    }

    // Last row
    ಯದಿ (y == (height - 1)) {
        ಪ್ರತಿ (x = 0; x < (width - 1); x += 2) {
            *dstY1++ = *srcY1;
            srcY1 += 2;
            *dstY1++ = *srcY1;
            srcY1 += 2;

            *dstU = *srcU1;
            *dstV = *srcV1;

            srcU1 += 4;
            srcV1 += 4;
            dstU += dstUV_pixel_stride;
            dstV += dstUV_pixel_stride;
        }

        // Last column
        ಯದಿ (x == (width - 1)) {
            *dstY1 = *srcY1;
            *dstU = *srcU1;
            *dstV = *srcV1;
        }
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

#endif // SDL_HAVE_YUV

bool SDL_ConvertPixels_YUV_to_YUV(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height,
                                  SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ಧ್ರುವ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಙ್ಕ src_pitch,
                                  SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಙ್ಕ dst_pitch)
{
#ifdef SDL_HAVE_YUV
    ಯದಿ (src_colorspace != dst_colorspace) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("SDL_ConvertPixels_YUV_to_YUV: colorspace conversion not supported");
    }

    ಯದಿ (src_format == dst_format) {
        ಯದಿ (src == dst) {
            // Nothing to do
            ಪ್ರತ್ಯಾಗಮ true;
        }
        ಪ್ರತ್ಯಾಗಮ SDL_ConvertPixels_YUV_to_YUV_Copy(width, height, src_format, src, src_pitch, dst, dst_pitch);
    }

    ಯದಿ (IsPlanar2x2Format(src_format) && IsPlanar2x2Format(dst_format)) {
        ಪ್ರತ್ಯಾಗಮ SDL_ConvertPixels_Planar2x2_to_Planar2x2(width, height, src_format, src, src_pitch, dst_format, dst, dst_pitch);
    } ಅನ್ಯಥಾ ಯದಿ (IsPacked4Format(src_format) && IsPacked4Format(dst_format)) {
        ಪ್ರತ್ಯಾಗಮ SDL_ConvertPixels_Packed4_to_Packed4(width, height, src_format, src, src_pitch, dst_format, dst, dst_pitch);
    } ಅನ್ಯಥಾ ಯದಿ (IsPlanar2x2Format(src_format) && IsPacked4Format(dst_format)) {
        ಪ್ರತ್ಯಾಗಮ SDL_ConvertPixels_Planar2x2_to_Packed4(width, height, src_format, src, src_pitch, dst_format, dst, dst_pitch);
    } ಅನ್ಯಥಾ ಯದಿ (IsPacked4Format(src_format) && IsPlanar2x2Format(dst_format)) {
        ಪ್ರತ್ಯಾಗಮ SDL_ConvertPixels_Packed4_to_Planar2x2(width, height, src_format, src, src_pitch, dst_format, dst, dst_pitch);
    } ಅನ್ಯಥಾ {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("SDL_ConvertPixels_YUV_to_YUV: Unsupported YUV conversion: %s -> %s", SDL_GetPixelFormatName(src_format),
                            SDL_GetPixelFormatName(dst_format));
    }
#ಅನ್ಯಥಾ
    ಪ್ರತ್ಯಾಗಮ SDL_SetError("SDL not built with YUV support");
#endif
}
