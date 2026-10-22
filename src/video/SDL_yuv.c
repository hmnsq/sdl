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

#ضمن "SDL_pixels_c.h"
#ضمن "SDL_yuv_c.h"

#ضمن "yuv2rgb/yuv_rgb.h"


ساكن bool IsPlanar1x1Format(SDL_PixelFormat format)
{
    أرجع format == SDL_PIXELFORMAT_I444 || format == SDL_PIXELFORMAT_I4FL;
}

ساكن bool IsPlanar2x2Format(SDL_PixelFormat format)
{
    أرجع format == SDL_PIXELFORMAT_YV12 ||
           format == SDL_PIXELFORMAT_IYUV ||
           format == SDL_PIXELFORMAT_NV12 ||
           format == SDL_PIXELFORMAT_NV21 ||
           format == SDL_PIXELFORMAT_P010 ||
           format == SDL_PIXELFORMAT_I0FL;
}

ساكن bool IsPacked4Format(Uint32 format)
{
    أرجع format == SDL_PIXELFORMAT_YUY2 || format == SDL_PIXELFORMAT_UYVY || format == SDL_PIXELFORMAT_YVYU;
}

/*
 * Calculate YUV size and pitch. Check for overflow.
 * Output 'pitch' that can be used with SDL_ConvertPixels()
 */
bool SDL_CalculateYUVSize(SDL_PixelFormat format, صحيح w, صحيح h, size_t *اندازه, size_t *pitch)
{
    صحيح sz_plane = 0, sz_plane_chroma = 0, sz_plane_packed = 0;

    إذا (IsPlanar1x1Format(format)) {
        /* sz_plane == w * h * bpp; */
        size_t s1;
        إذا (!SDL_اندازه_mul_check_سرریز(w, h, &s1)) {
            أرجع SDL_مجموعه_Error("width * height would overflow");
        }
        إذا (!SDL_اندازه_mul_check_سرریز(s1, SDL_BYTESPERPIXEL(format), &s1)) {
            أرجع SDL_مجموعه_Error("width * height * bpp would overflow");
        }
        sz_plane = (صحيح)s1;
        sz_plane_chroma = sz_plane;
    } وإلا إذا (IsPlanar2x2Format(format)) {
        {
            /* sz_plane == w * h * bpp; */
            size_t s1;
            إذا (!SDL_اندازه_mul_check_سرریز(w, h, &s1)) {
                أرجع SDL_مجموعه_Error("width * height would overflow");
            }
            إذا (!SDL_اندازه_mul_check_سرریز(s1, SDL_BYTESPERPIXEL(format), &s1)) {
                أرجع SDL_مجموعه_Error("width * height * bpp would overflow");
            }
            sz_plane = (صحيح)s1;
        }

        {
            /* sz_plane_chroma == ((w + 1) / 2) * ((h + 1) / 2) * bpp; */
            size_t s1, s2, s3;
            إذا (!SDL_اندازه_جمع_کن_check_سرریز(w, 1, &s1)) {
                أرجع SDL_مجموعه_Error("width + 1 would overflow");
            }
            s1 = s1 / 2;
            إذا (!SDL_اندازه_جمع_کن_check_سرریز(h, 1, &s2)) {
                أرجع SDL_مجموعه_Error("height + 1 would overflow");
            }
            s2 = s2 / 2;
            إذا (!SDL_اندازه_mul_check_سرریز(s1, s2, &s3)) {
                أرجع SDL_مجموعه_Error("width * height would overflow");
            }
            إذا (!SDL_اندازه_mul_check_سرریز(s3, SDL_BYTESPERPIXEL(format), &s3)) {
                أرجع SDL_مجموعه_Error("width * height * bpp would overflow");
            }
            sz_plane_chroma = (صحيح)s3;
        }
    } وإلا إذا (IsPacked4Format(format)) {
        /* sz_plane_packed == ((w + 1) / 2) * h; */
        size_t s1, s2;
        إذا (!SDL_اندازه_جمع_کن_check_سرریز(w, 1, &s1)) {
            أرجع SDL_مجموعه_Error("width + 1 would overflow");
        }
        s1 = s1 / 2;
        إذا (!SDL_اندازه_mul_check_سرریز(s1, h, &s2)) {
            أرجع SDL_مجموعه_Error("width * height would overflow");
        }
        sz_plane_packed = (صحيح) s2;
    } وإلا {
        أرجع SDL_Unsupported();
    }

    بدل (format) {
    حالة SDL_PIXELFORMAT_YV12: /**< Planar mode: Y + V + U  (3 planes) */
    حالة SDL_PIXELFORMAT_IYUV: /**< Planar mode: Y + U + V  (3 planes) */
    حالة SDL_PIXELFORMAT_I444: /**< Planar mode: Y + U + V  (3 planes) */
    حالة SDL_PIXELFORMAT_I0FL: /**< Planar mode: Y + U + V  (3 planes) */
    حالة SDL_PIXELFORMAT_I4FL: /**< Planar mode: Y + U + V  (3 planes) */

        إذا (pitch) {
            *pitch = w * SDL_BYTESPERPIXEL(format);
        }

        إذا (اندازه) {
            // dst_size == sz_plane + sz_plane_chroma + sz_plane_chroma;
            size_t s1, s2;
            إذا (!SDL_اندازه_جمع_کن_check_سرریز(sz_plane, sz_plane_chroma, &s1)) {
                أرجع SDL_مجموعه_Error("Y + U would overflow");
            }
            إذا (!SDL_اندازه_جمع_کن_check_سرریز(s1, sz_plane_chroma, &s2)) {
                أرجع SDL_مجموعه_Error("Y + U + V would overflow");
            }
            *اندازه = (صحيح)s2;
        }
        اكسر;

    حالة SDL_PIXELFORMAT_YUY2: /**< Packed mode: Y0+U0+Y1+V0 (1 plane) */
    حالة SDL_PIXELFORMAT_UYVY: /**< Packed mode: U0+Y0+V0+Y1 (1 plane) */
    حالة SDL_PIXELFORMAT_YVYU: /**< Packed mode: Y0+V0+Y1+U0 (1 plane) */

        إذا (pitch) {
            /* pitch == ((w + 1) / 2) * 4; */
           size_t p1, p2;
           إذا (!SDL_اندازه_جمع_کن_check_سرریز(w, 1, &p1)) {
               أرجع SDL_مجموعه_Error("width + 1 would overflow");
           }
           p1 = p1 / 2;
           إذا (!SDL_اندازه_mul_check_سرریز(p1, 4, &p2)) {
               أرجع SDL_مجموعه_Error("width * 4 would overflow");
           }
           *pitch = p2;
        }

        إذا (اندازه) {
            /* dst_size == 4 * sz_plane_packed; */
            size_t s1;
            إذا (!SDL_اندازه_mul_check_سرریز(sz_plane_packed, 4, &s1)) {
                أرجع SDL_مجموعه_Error("plane * 4 would overflow");
            }
            *اندازه = (صحيح) s1;
        }
        اكسر;

    حالة SDL_PIXELFORMAT_NV12: /**< Planar mode: Y + U/V interleaved  (2 planes) */
    حالة SDL_PIXELFORMAT_NV21: /**< Planar mode: Y + V/U interleaved  (2 planes) */
    حالة SDL_PIXELFORMAT_P010: /**< Planar mode: Y + U/V interleaved, 10 bit  (2 planes) */
        إذا (pitch) {
            *pitch = w * SDL_BYTESPERPIXEL(format);
        }

        إذا (اندازه) {
            // dst_size == sz_plane + sz_plane_chroma + sz_plane_chroma;
            size_t s1, s2;
            إذا (!SDL_اندازه_جمع_کن_check_سرریز(sz_plane, sz_plane_chroma, &s1)) {
                أرجع SDL_مجموعه_Error("Y + U would overflow");
            }
            إذا (!SDL_اندازه_جمع_کن_check_سرریز(s1, sz_plane_chroma, &s2)) {
                أرجع SDL_مجموعه_Error("Y + U + V would overflow");
            }
            *اندازه = (صحيح) s2;
        }
        اكسر;

    افتراضي:
        أرجع SDL_Unsupported();
    }

    أرجع true;
}

#اگر_تعریف_شده SDL_HAVE_YUV

ساكن bool GetYUVConversionType(SDL_Colorspace colorspace, صحيح w, صحيح h, صحيح بیتها_در_هر_pixel, YCbCrType *yuv_type)
{
    إذا (SDL_ISCOLORSPACE_ماتریس_BT601(colorspace)) {
        إذا (SDL_ISCOLORSPACE_LIMITED_RANGE(colorspace)) {
            *yuv_type = YCBCR_601_LIMITED;
        } وإلا {
            *yuv_type = YCBCR_601_پر;
        }
        أرجع true;
    }

    إذا (SDL_ISCOLORSPACE_ماتریس_BT709(colorspace)) {
        إذا (SDL_ISCOLORSPACE_LIMITED_RANGE(colorspace)) {
            *yuv_type = YCBCR_709_LIMITED;
        } وإلا {
            *yuv_type = YCBCR_709_پر;
        }
        أرجع true;
    }

    إذا (SDL_ISCOLORSPACE_ماتریس_BT2020_NCL(colorspace)) {
        إذا (SDL_ISCOLORSPACE_پر_RANGE(colorspace)) {
            *yuv_type = YCBCR_2020_NCL_پر;
            أرجع true;
        }
    }

    إذا (SDL_COLORSPACEMATRIX(colorspace) == SDL_ماتریس_COEFFICIENTS_UNSPECIFIED) {
        بدل (بیتها_در_هر_pixel) {
        حالة 8:
            إذا (h <= YUV_SD_آستانه) {
                إذا (SDL_ISCOLORSPACE_LIMITED_RANGE(colorspace)) {
                    *yuv_type = YCBCR_601_LIMITED;
                } وإلا {
                    *yuv_type = YCBCR_601_پر;
                }
            } وإلا {
                إذا (SDL_ISCOLORSPACE_LIMITED_RANGE(colorspace)) {
                    *yuv_type = YCBCR_709_LIMITED;
                } وإلا {
                    *yuv_type = YCBCR_709_پر;
                }
            }
			أرجع true;
        حالة 10:
        حالة 16:
            إذا (SDL_ISCOLORSPACE_پر_RANGE(colorspace)) {
                *yuv_type = YCBCR_2020_NCL_پر;
                أرجع true;
            }
            اكسر;
        افتراضي:
            اكسر;
        }
    }

    أرجع SDL_مجموعه_Error("Unsupported YUV colorspace");
}

ساكن bool GetYUVPlanes(صحيح عرض, صحيح ارتفاع, SDL_PixelFormat format, ثابت فراغ *yuv, صحيح yuv_pitch,
                         ثابت Uint8 **y, ثابت Uint8 **u, ثابت Uint8 **v, Uint32 *y_stride, Uint32 *uv_stride)
{
    ثابت Uint8 *planes[3] = { عدم, عدم, عدم };
    صحيح pitches[3] = { 0, 0, 0 };
    صحيح uv_عرض;

    بدل (format) {
    حالة SDL_PIXELFORMAT_YV12:
    حالة SDL_PIXELFORMAT_IYUV:
    حالة SDL_PIXELFORMAT_I0FL:
        pitches[0] = yuv_pitch;
        pitches[1] = ((pitches[0] / SDL_BYTESPERPIXEL(format) + 1) / 2) * SDL_BYTESPERPIXEL(format);
        pitches[2] = pitches[1];
        planes[0] = (ثابت Uint8 *)yuv;
        planes[1] = planes[0] + pitches[0] * ارتفاع;
        planes[2] = planes[1] + pitches[1] * ((ارتفاع + 1) / 2);
        اكسر;
    حالة SDL_PIXELFORMAT_YUY2:
    حالة SDL_PIXELFORMAT_UYVY:
    حالة SDL_PIXELFORMAT_YVYU:
        pitches[0] = yuv_pitch;
        planes[0] = (ثابت Uint8 *)yuv;
        اكسر;
    حالة SDL_PIXELFORMAT_NV12:
    حالة SDL_PIXELFORMAT_NV21:
        pitches[0] = yuv_pitch;
        pitches[1] = 2 * ((pitches[0] + 1) / 2);
        planes[0] = (ثابت Uint8 *)yuv;
        planes[1] = planes[0] + pitches[0] * ارتفاع;
        اكسر;
    حالة SDL_PIXELFORMAT_P010:
        pitches[0] = yuv_pitch;
        uv_عرض = ((عرض + 1) / 2) * 2;
        pitches[1] = SDL_max(pitches[0], (صحيح)(uv_عرض * حجم(Uint16)));
        planes[0] = (ثابت Uint8 *)yuv;
        planes[1] = planes[0] + pitches[0] * ارتفاع;
        اكسر;
    حالة SDL_PIXELFORMAT_I444:
    حالة SDL_PIXELFORMAT_I4FL:
        pitches[0] = yuv_pitch;
        pitches[1] = pitches[0];
        pitches[2] = pitches[1];
        planes[0] = (ثابت Uint8 *)yuv;
        planes[1] = planes[0] + pitches[0] * ارتفاع;
        planes[2] = planes[1] + pitches[1] * ارتفاع;
        اكسر;
    افتراضي:
        أرجع SDL_مجموعه_Error("GetYUVPlanes(): Unsupported YUV format: %s", SDL_GetPixelFormatName(format));
    }

    بدل (format) {
    حالة SDL_PIXELFORMAT_YV12:
        *y = planes[0];
        *y_stride = pitches[0];
        *v = planes[1];
        *u = planes[2];
        *uv_stride = pitches[1];
        اكسر;
    حالة SDL_PIXELFORMAT_IYUV:
    حالة SDL_PIXELFORMAT_I444:
    حالة SDL_PIXELFORMAT_I0FL:
    حالة SDL_PIXELFORMAT_I4FL:
        *y = planes[0];
        *y_stride = pitches[0];
        *v = planes[2];
        *u = planes[1];
        *uv_stride = pitches[1];
        اكسر;
    حالة SDL_PIXELFORMAT_YUY2:
        *y = planes[0];
        *y_stride = pitches[0];
        *v = *y + 3;
        *u = *y + 1;
        *uv_stride = pitches[0];
        اكسر;
    حالة SDL_PIXELFORMAT_UYVY:
        *y = planes[0] + 1;
        *y_stride = pitches[0];
        *v = *y + 1;
        *u = *y - 1;
        *uv_stride = pitches[0];
        اكسر;
    حالة SDL_PIXELFORMAT_YVYU:
        *y = planes[0];
        *y_stride = pitches[0];
        *v = *y + 1;
        *u = *y + 3;
        *uv_stride = pitches[0];
        اكسر;
    حالة SDL_PIXELFORMAT_NV12:
        *y = planes[0];
        *y_stride = pitches[0];
        *u = planes[1];
        *v = *u + 1;
        *uv_stride = pitches[1];
        اكسر;
    حالة SDL_PIXELFORMAT_NV21:
        *y = planes[0];
        *y_stride = pitches[0];
        *v = planes[1];
        *u = *v + 1;
        *uv_stride = pitches[1];
        اكسر;
    حالة SDL_PIXELFORMAT_P010:
        *y = planes[0];
        *y_stride = pitches[0];
        *u = planes[1];
        *v = *u + حجم(Uint16);
        *uv_stride = pitches[1];
        اكسر;
    افتراضي:
        // Should have caught this above
        أرجع SDL_مجموعه_Error("GetYUVPlanes[2]: Unsupported YUV format: %s", SDL_GetPixelFormatName(format));
    }
    أرجع true;
}

#اگر_تعریف_شده SDL_SSE2_INTRINSICS
ساكن bool SDL_TARGETING("sse2") yuv_rgb_sse(
    SDL_PixelFormat src_format, SDL_PixelFormat dst_format,
    Uint32 عرض, Uint32 ارتفاع,
    ثابت Uint8 *y, ثابت Uint8 *u, ثابت Uint8 *v, Uint32 y_stride, Uint32 uv_stride,
    Uint8 *rgb, Uint32 rgb_stride,
    YCbCrType yuv_type)
{
    إذا (!SDL_HasSSE2()) {
        أرجع false;
    }

    إذا (src_format == SDL_PIXELFORMAT_YV12 ||
        src_format == SDL_PIXELFORMAT_IYUV) {

        بدل (dst_format) {
        حالة SDL_PIXELFORMAT_RGB565:
            yuv420_rgb565_sseu(عرض, ارتفاع, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            أرجع true;
        حالة SDL_PIXELFORMAT_RGB24:
            yuv420_rgb24_sseu(عرض, ارتفاع, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            أرجع true;
        حالة SDL_PIXELFORMAT_RGBX8888:
        حالة SDL_PIXELFORMAT_RGBA8888:
            yuv420_rgba_sseu(عرض, ارتفاع, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            أرجع true;
        حالة SDL_PIXELFORMAT_BGRX8888:
        حالة SDL_PIXELFORMAT_BGRA8888:
            yuv420_bgra_sseu(عرض, ارتفاع, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            أرجع true;
        حالة SDL_PIXELFORMAT_XRGB8888:
        حالة SDL_PIXELFORMAT_ARGB8888:
            yuv420_argb_sseu(عرض, ارتفاع, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            أرجع true;
        حالة SDL_PIXELFORMAT_XBGR8888:
        حالة SDL_PIXELFORMAT_ABGR8888:
            yuv420_abgr_sseu(عرض, ارتفاع, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            أرجع true;
        افتراضي:
            اكسر;
        }
    }

    إذا (src_format == SDL_PIXELFORMAT_YUY2 ||
        src_format == SDL_PIXELFORMAT_UYVY ||
        src_format == SDL_PIXELFORMAT_YVYU) {

        بدل (dst_format) {
        حالة SDL_PIXELFORMAT_RGB565:
            yuv422_rgb565_sseu(عرض, ارتفاع, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            أرجع true;
        حالة SDL_PIXELFORMAT_RGB24:
            yuv422_rgb24_sseu(عرض, ارتفاع, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            أرجع true;
        حالة SDL_PIXELFORMAT_RGBX8888:
        حالة SDL_PIXELFORMAT_RGBA8888:
            yuv422_rgba_sseu(عرض, ارتفاع, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            أرجع true;
        حالة SDL_PIXELFORMAT_BGRX8888:
        حالة SDL_PIXELFORMAT_BGRA8888:
            yuv422_bgra_sseu(عرض, ارتفاع, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            أرجع true;
        حالة SDL_PIXELFORMAT_XRGB8888:
        حالة SDL_PIXELFORMAT_ARGB8888:
            yuv422_argb_sseu(عرض, ارتفاع, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            أرجع true;
        حالة SDL_PIXELFORMAT_XBGR8888:
        حالة SDL_PIXELFORMAT_ABGR8888:
            yuv422_abgr_sseu(عرض, ارتفاع, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            أرجع true;
        افتراضي:
            اكسر;
        }
    }

    إذا (src_format == SDL_PIXELFORMAT_NV12 ||
        src_format == SDL_PIXELFORMAT_NV21) {

        بدل (dst_format) {
        حالة SDL_PIXELFORMAT_RGB565:
            yuvnv12_rgb565_sseu(عرض, ارتفاع, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            أرجع true;
        حالة SDL_PIXELFORMAT_RGB24:
            yuvnv12_rgb24_sseu(عرض, ارتفاع, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            أرجع true;
        حالة SDL_PIXELFORMAT_RGBX8888:
        حالة SDL_PIXELFORMAT_RGBA8888:
            yuvnv12_rgba_sseu(عرض, ارتفاع, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            أرجع true;
        حالة SDL_PIXELFORMAT_BGRX8888:
        حالة SDL_PIXELFORMAT_BGRA8888:
            yuvnv12_bgra_sseu(عرض, ارتفاع, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            أرجع true;
        حالة SDL_PIXELFORMAT_XRGB8888:
        حالة SDL_PIXELFORMAT_ARGB8888:
            yuvnv12_argb_sseu(عرض, ارتفاع, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            أرجع true;
        حالة SDL_PIXELFORMAT_XBGR8888:
        حالة SDL_PIXELFORMAT_ABGR8888:
            yuvnv12_abgr_sseu(عرض, ارتفاع, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            أرجع true;
        افتراضي:
            اكسر;
        }
    }
    أرجع false;
}
#وإلا
ساكن bool yuv_rgb_sse(
    SDL_PixelFormat src_format, SDL_PixelFormat dst_format,
    Uint32 عرض, Uint32 ارتفاع,
    ثابت Uint8 *y, ثابت Uint8 *u, ثابت Uint8 *v, Uint32 y_stride, Uint32 uv_stride,
    Uint8 *rgb, Uint32 rgb_stride,
    YCbCrType yuv_type)
{
    أرجع false;
}
#پایان_اگر

#اگر_تعریف_شده SDL_LSX_INTRINSICS
ساكن bool yuv_rgb_lsx(
    SDL_PixelFormat src_format, SDL_PixelFormat dst_format,
    Uint32 عرض, Uint32 ارتفاع,
    ثابت Uint8 *y, ثابت Uint8 *u, ثابت Uint8 *v, Uint32 y_stride, Uint32 uv_stride,
    Uint8 *rgb, Uint32 rgb_stride,
    YCbCrType yuv_type)
{
    إذا (!SDL_HasLSX()) {
        أرجع false;
    }
    إذا (src_format == SDL_PIXELFORMAT_YV12 ||
        src_format == SDL_PIXELFORMAT_IYUV) {

        بدل (dst_format) {
        حالة SDL_PIXELFORMAT_RGB24:
            yuv420_rgb24_lsx(عرض, ارتفاع, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            أرجع true;
        حالة SDL_PIXELFORMAT_RGBX8888:
        حالة SDL_PIXELFORMAT_RGBA8888:
            yuv420_rgba_lsx(عرض, ارتفاع, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            أرجع true;
        حالة SDL_PIXELFORMAT_BGRX8888:
        حالة SDL_PIXELFORMAT_BGRA8888:
            yuv420_bgra_lsx(عرض, ارتفاع, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            أرجع true;
        حالة SDL_PIXELFORMAT_XRGB8888:
        حالة SDL_PIXELFORMAT_ARGB8888:
            yuv420_argb_lsx(عرض, ارتفاع, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            أرجع true;
        حالة SDL_PIXELFORMAT_XBGR8888:
        حالة SDL_PIXELFORMAT_ABGR8888:
            yuv420_abgr_lsx(عرض, ارتفاع, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            أرجع true;
        افتراضي:
            اكسر;
        }
    }
    أرجع false;
}
#وإلا
ساكن bool yuv_rgb_lsx(
    SDL_PixelFormat src_format, SDL_PixelFormat dst_format,
    Uint32 عرض, Uint32 ارتفاع,
    ثابت Uint8 *y, ثابت Uint8 *u, ثابت Uint8 *v, Uint32 y_stride, Uint32 uv_stride,
    Uint8 *rgb, Uint32 rgb_stride,
    YCbCrType yuv_type)
{
    أرجع false;
}
#پایان_اگر

ساكن bool yuv_rgb_std(
    SDL_PixelFormat src_format, SDL_PixelFormat dst_format,
    Uint32 عرض, Uint32 ارتفاع,
    ثابت Uint8 *y, ثابت Uint8 *u, ثابت Uint8 *v, Uint32 y_stride, Uint32 uv_stride,
    Uint8 *rgb, Uint32 rgb_stride,
    YCbCrType yuv_type)
{
    إذا (src_format == SDL_PIXELFORMAT_YV12 ||
        src_format == SDL_PIXELFORMAT_IYUV) {

        بدل (dst_format) {
        حالة SDL_PIXELFORMAT_RGB565:
            yuv420_rgb565_std(عرض, ارتفاع, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            أرجع true;
        حالة SDL_PIXELFORMAT_RGB24:
            yuv420_rgb24_std(عرض, ارتفاع, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            أرجع true;
        حالة SDL_PIXELFORMAT_RGBX8888:
        حالة SDL_PIXELFORMAT_RGBA8888:
            yuv420_rgba_std(عرض, ارتفاع, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            أرجع true;
        حالة SDL_PIXELFORMAT_BGRX8888:
        حالة SDL_PIXELFORMAT_BGRA8888:
            yuv420_bgra_std(عرض, ارتفاع, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            أرجع true;
        حالة SDL_PIXELFORMAT_XRGB8888:
        حالة SDL_PIXELFORMAT_ARGB8888:
            yuv420_argb_std(عرض, ارتفاع, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            أرجع true;
        حالة SDL_PIXELFORMAT_XBGR8888:
        حالة SDL_PIXELFORMAT_ABGR8888:
            yuv420_abgr_std(عرض, ارتفاع, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            أرجع true;
        افتراضي:
            اكسر;
        }
    }

    إذا (src_format == SDL_PIXELFORMAT_I444) {

        بدل (dst_format) {
        حالة SDL_PIXELFORMAT_RGBX8888:
        حالة SDL_PIXELFORMAT_RGBA8888:
            yuv444_rgba_std(عرض, ارتفاع, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            أرجع true;
        حالة SDL_PIXELFORMAT_BGRX8888:
        حالة SDL_PIXELFORMAT_BGRA8888:
            yuv444_bgra_std(عرض, ارتفاع, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            أرجع true;
        حالة SDL_PIXELFORMAT_XRGB8888:
        حالة SDL_PIXELFORMAT_ARGB8888:
            yuv444_argb_std(عرض, ارتفاع, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            أرجع true;
        حالة SDL_PIXELFORMAT_XBGR8888:
        حالة SDL_PIXELFORMAT_ABGR8888:
            yuv444_abgr_std(عرض, ارتفاع, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            أرجع true;
        افتراضي:
            اكسر;
        }
    }

    إذا (src_format == SDL_PIXELFORMAT_YUY2 ||
        src_format == SDL_PIXELFORMAT_UYVY ||
        src_format == SDL_PIXELFORMAT_YVYU) {

        بدل (dst_format) {
        حالة SDL_PIXELFORMAT_RGB565:
            yuv422_rgb565_std(عرض, ارتفاع, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            أرجع true;
        حالة SDL_PIXELFORMAT_RGB24:
            yuv422_rgb24_std(عرض, ارتفاع, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            أرجع true;
        حالة SDL_PIXELFORMAT_RGBX8888:
        حالة SDL_PIXELFORMAT_RGBA8888:
            yuv422_rgba_std(عرض, ارتفاع, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            أرجع true;
        حالة SDL_PIXELFORMAT_BGRX8888:
        حالة SDL_PIXELFORMAT_BGRA8888:
            yuv422_bgra_std(عرض, ارتفاع, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            أرجع true;
        حالة SDL_PIXELFORMAT_XRGB8888:
        حالة SDL_PIXELFORMAT_ARGB8888:
            yuv422_argb_std(عرض, ارتفاع, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            أرجع true;
        حالة SDL_PIXELFORMAT_XBGR8888:
        حالة SDL_PIXELFORMAT_ABGR8888:
            yuv422_abgr_std(عرض, ارتفاع, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            أرجع true;
        افتراضي:
            اكسر;
        }
    }

    إذا (src_format == SDL_PIXELFORMAT_NV12 ||
        src_format == SDL_PIXELFORMAT_NV21) {

        بدل (dst_format) {
        حالة SDL_PIXELFORMAT_RGB565:
            yuvnv12_rgb565_std(عرض, ارتفاع, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            أرجع true;
        حالة SDL_PIXELFORMAT_RGB24:
            yuvnv12_rgb24_std(عرض, ارتفاع, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            أرجع true;
        حالة SDL_PIXELFORMAT_RGBX8888:
        حالة SDL_PIXELFORMAT_RGBA8888:
            yuvnv12_rgba_std(عرض, ارتفاع, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            أرجع true;
        حالة SDL_PIXELFORMAT_BGRX8888:
        حالة SDL_PIXELFORMAT_BGRA8888:
            yuvnv12_bgra_std(عرض, ارتفاع, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            أرجع true;
        حالة SDL_PIXELFORMAT_XRGB8888:
        حالة SDL_PIXELFORMAT_ARGB8888:
            yuvnv12_argb_std(عرض, ارتفاع, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            أرجع true;
        حالة SDL_PIXELFORMAT_XBGR8888:
        حالة SDL_PIXELFORMAT_ABGR8888:
            yuvnv12_abgr_std(عرض, ارتفاع, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            أرجع true;
        افتراضي:
            اكسر;
        }
    }

    إذا (src_format == SDL_PIXELFORMAT_P010) {
        بدل (dst_format) {
        حالة SDL_PIXELFORMAT_XBGR2101010:
            yuvp010_xbgr2101010_std(عرض, ارتفاع, (ثابت uint16_t *)y, (ثابت uint16_t *)u, (ثابت uint16_t *)v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            أرجع true;
        افتراضي:
            اكسر;
        }
    }

    إذا (src_format == SDL_PIXELFORMAT_I0FL) {
        بدل (dst_format) {
        حالة SDL_PIXELFORMAT_RGB48:
            yuvi0fl_rgb48_std(عرض, ارتفاع, (ثابت uint16_t *)y, (ثابت uint16_t *)u, (ثابت uint16_t *)v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            أرجع true;
        افتراضي:
            اكسر;
        }
    }

    إذا (src_format == SDL_PIXELFORMAT_I4FL) {
        بدل (dst_format) {
        حالة SDL_PIXELFORMAT_RGB48:
            yuvi4fl_rgb48_std(عرض, ارتفاع, (ثابت uint16_t *)y, (ثابت uint16_t *)u, (ثابت uint16_t *)v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            أرجع true;
        افتراضي:
            اكسر;
        }
    }
    أرجع false;
}

bool SDL_Convert_Pixels_YUV_مقصد_RGB(صحيح عرض, صحيح ارتفاع,
                                  SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ثابت فراغ *src, صحيح src_pitch,
                                  SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, فراغ *dst, صحيح dst_pitch)
{
    ثابت Uint8 *y = عدم;
    ثابت Uint8 *u = عدم;
    ثابت Uint8 *v = عدم;
    Uint32 y_stride = 0;
    Uint32 uv_stride = 0;
    YCbCrType yuv_type = YCBCR_601_LIMITED;

    إذا (!GetYUVPlanes(عرض, ارتفاع, src_format, src, src_pitch, &y, &u, &v, &y_stride, &uv_stride)) {
        أرجع false;
    }

    إذا (!GetYUVConversionType(src_colorspace, عرض, ارتفاع, 8, &yuv_type)) {
        أرجع false;
    }

    إذا (yuv_rgb_sse(src_format, dst_format, عرض, ارتفاع, y, u, v, y_stride, uv_stride, (Uint8 *)dst, dst_pitch, yuv_type)) {
        أرجع true;
    }

    إذا (yuv_rgb_lsx(src_format, dst_format, عرض, ارتفاع, y, u, v, y_stride, uv_stride, (Uint8 *)dst, dst_pitch, yuv_type)) {
        أرجع true;
    }

    إذا (yuv_rgb_std(src_format, dst_format, عرض, ارتفاع, y, u, v, y_stride, uv_stride, (Uint8 *)dst, dst_pitch, yuv_type)) {
        أرجع true;
    }

    // No fast path for the RGB format, instead convert using an intermediate buffer
    إذا (src_format == SDL_PIXELFORMAT_P010 && dst_format != SDL_PIXELFORMAT_XBGR2101010) {
        bool نتیجه;
        فراغ *tmp;
        صحيح tmp_pitch = (عرض * حجم(Uint32));

        tmp = SDL_malloc((size_t)tmp_pitch * ارتفاع);
        إذا (!tmp) {
            أرجع false;
        }

        // convert src/src_format to tmp/XBGR2101010
        نتیجه = SDL_Convert_Pixels_YUV_مقصد_RGB(عرض, ارتفاع, src_format, src_colorspace, src_properties, src, src_pitch, SDL_PIXELFORMAT_XBGR2101010, src_colorspace, src_properties, tmp, tmp_pitch);
        إذا (!نتیجه) {
            SDL_free(tmp);
            أرجع false;
        }

        // convert tmp/XBGR2101010 to dst/RGB
        نتیجه = SDL_ConvertPixelsAndColorspace(عرض, ارتفاع, SDL_PIXELFORMAT_XBGR2101010, src_colorspace, src_properties, tmp, tmp_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
        SDL_free(tmp);
        أرجع نتیجه;
    }

    إذا ((src_format == SDL_PIXELFORMAT_I0FL || src_format == SDL_PIXELFORMAT_I4FL) && dst_format != SDL_PIXELFORMAT_RGB48) {
        bool نتیجه;
        فراغ *tmp;
        صحيح tmp_pitch = (عرض * 3 * حجم(Uint16));

        tmp = SDL_malloc((size_t)tmp_pitch * ارتفاع);
        إذا (!tmp) {
            أرجع false;
        }

        // convert src/src_format to tmp/RGB48
        نتیجه = SDL_Convert_Pixels_YUV_مقصد_RGB(عرض, ارتفاع, src_format, src_colorspace, src_properties, src, src_pitch, SDL_PIXELFORMAT_RGB48, src_colorspace, src_properties, tmp, tmp_pitch);
        إذا (!نتیجه) {
            SDL_free(tmp);
            أرجع false;
        }

        // convert tmp/RGB48 to dst/RGB
        نتیجه = SDL_ConvertPixelsAndColorspace(عرض, ارتفاع, SDL_PIXELFORMAT_RGB48, src_colorspace, src_properties, tmp, tmp_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
        SDL_free(tmp);
        أرجع نتیجه;
    }

    إذا (dst_format != SDL_PIXELFORMAT_ARGB8888) {
        bool نتیجه;
        فراغ *tmp;
        صحيح tmp_pitch = (عرض * حجم(Uint32));

        tmp = SDL_malloc((size_t)tmp_pitch * ارتفاع);
        إذا (!tmp) {
            أرجع false;
        }

        // convert src/src_format to tmp/ARGB8888
        نتیجه = SDL_Convert_Pixels_YUV_مقصد_RGB(عرض, ارتفاع, src_format, src_colorspace, src_properties, src, src_pitch, SDL_PIXELFORMAT_ARGB8888, SDL_COLORSPACE_SRGB, 0, tmp, tmp_pitch);
        إذا (!نتیجه) {
            SDL_free(tmp);
            أرجع false;
        }

        // convert tmp/ARGB8888 to dst/RGB
        نتیجه = SDL_ConvertPixelsAndColorspace(عرض, ارتفاع, SDL_PIXELFORMAT_ARGB8888, SDL_COLORSPACE_SRGB, 0, tmp, tmp_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
        SDL_free(tmp);
        أرجع نتیجه;
    }

    أرجع SDL_مجموعه_Error("Unsupported YUV conversion");
}

بنية RGB2YUVFactors
{
    صحيح y_جابه_جایی;
    عائم y[3]; // Rfactor, Gfactor, Bfactor
    عائم u[3]; // Rfactor, Gfactor, Bfactor
    عائم v[3]; // Rfactor, Gfactor, Bfactor
};

ساكن بنية RGB2YUVFactors RGB2YUVFactorTables[] = {
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

ساكن bool SDL_Convert_Pixels_XRGB8888_مقصد_YUV(صحيح عرض, صحيح ارتفاع, ثابت فراغ *src, صحيح src_pitch, SDL_PixelFormat dst_format, فراغ *dst, صحيح dst_pitch, YCbCrType yuv_type)
{
    ثابت صحيح src_pitch_x_2 = src_pitch * 2;
    ثابت صحيح ارتفاع_half = ارتفاع / 2;
    ثابت صحيح ارتفاع_remainder = (ارتفاع & 0x1);
    ثابت صحيح عرض_half = عرض / 2;
    ثابت صحيح عرض_remainder = (عرض & 0x1);
    صحيح i, j;

    ثابت بنية RGB2YUVFactors *cvt = &RGB2YUVFactorTables[yuv_type];

#تعریف_کن MAKE_Y(r, g, b) (Uint8)SDL_clamp(((صحيح)(cvt->y[0] * (r) + cvt->y[1] * (g) + cvt->y[2] * (b) + 0.5f) + cvt->y_جابه_جایی), 0, 255)
#تعریف_کن MAKE_U(r, g, b) (Uint8)SDL_clamp(((صحيح)(cvt->u[0] * (r) + cvt->u[1] * (g) + cvt->u[2] * (b) + 0.5f) + 128), 0, 255)
#تعریف_کن MAKE_V(r, g, b) (Uint8)SDL_clamp(((صحيح)(cvt->v[0] * (r) + cvt->v[1] * (g) + cvt->v[2] * (b) + 0.5f) + 128), 0, 255)

#تعریف_کن READ_2x2_PIXELS                                                                                     \
    ثابت Uint32 p1 = ((ثابت Uint32 *)curr_ردیف)[2 * i];                                                    \
    ثابت Uint32 p2 = ((ثابت Uint32 *)curr_ردیف)[2 * i + 1];                                                \
    ثابت Uint32 p3 = ((ثابت Uint32 *)بعدی_ردیف)[2 * i];                                                    \
    ثابت Uint32 p4 = ((ثابت Uint32 *)بعدی_ردیف)[2 * i + 1];                                                \
    ثابت Uint32 r = ((p1 & 0x00ff0000) + (p2 & 0x00ff0000) + (p3 & 0x00ff0000) + (p4 & 0x00ff0000)) >> 18; \
    ثابت Uint32 g = ((p1 & 0x0000ff00) + (p2 & 0x0000ff00) + (p3 & 0x0000ff00) + (p4 & 0x0000ff00)) >> 10; \
    ثابت Uint32 b = ((p1 & 0x000000ff) + (p2 & 0x000000ff) + (p3 & 0x000000ff) + (p4 & 0x000000ff)) >> 2

#تعریف_کن READ_2x1_PIXELS                                             \
    ثابت Uint32 p1 = ((ثابت Uint32 *)curr_ردیف)[2 * i];            \
    ثابت Uint32 p2 = ((ثابت Uint32 *)بعدی_ردیف)[2 * i];            \
    ثابت Uint32 r = ((p1 & 0x00ff0000) + (p2 & 0x00ff0000)) >> 17; \
    ثابت Uint32 g = ((p1 & 0x0000ff00) + (p2 & 0x0000ff00)) >> 9;  \
    ثابت Uint32 b = ((p1 & 0x000000ff) + (p2 & 0x000000ff)) >> 1

#تعریف_کن READ_1x2_PIXELS                                             \
    ثابت Uint32 p1 = ((ثابت Uint32 *)curr_ردیف)[2 * i];            \
    ثابت Uint32 p2 = ((ثابت Uint32 *)curr_ردیف)[2 * i + 1];        \
    ثابت Uint32 r = ((p1 & 0x00ff0000) + (p2 & 0x00ff0000)) >> 17; \
    ثابت Uint32 g = ((p1 & 0x0000ff00) + (p2 & 0x0000ff00)) >> 9;  \
    ثابت Uint32 b = ((p1 & 0x000000ff) + (p2 & 0x000000ff)) >> 1

#تعریف_کن READ_1x1_PIXEL                                  \
    ثابت Uint32 p = ((ثابت Uint32 *)curr_ردیف)[2 * i]; \
    ثابت Uint32 r = (p & 0x00ff0000) >> 16;            \
    ثابت Uint32 g = (p & 0x0000ff00) >> 8;             \
    ثابت Uint32 b = (p & 0x000000ff)

#تعریف_کن READ_TWO_RGB_PIXELS                                  \
    ثابت Uint32 p = ((ثابت Uint32 *)curr_ردیف)[2 * i];      \
    ثابت Uint32 r = (p & 0x00ff0000) >> 16;                 \
    ثابت Uint32 g = (p & 0x0000ff00) >> 8;                  \
    ثابت Uint32 b = (p & 0x000000ff);                       \
    ثابت Uint32 p1 = ((ثابت Uint32 *)curr_ردیف)[2 * i + 1]; \
    ثابت Uint32 r1 = (p1 & 0x00ff0000) >> 16;               \
    ثابت Uint32 g1 = (p1 & 0x0000ff00) >> 8;                \
    ثابت Uint32 b1 = (p1 & 0x000000ff);                     \
    ثابت Uint32 R = (r + r1) / 2;                           \
    ثابت Uint32 G = (g + g1) / 2;                           \
    ثابت Uint32 B = (b + b1) / 2

#تعریف_کن READ_ONE_RGB_PIXEL READ_1x1_PIXEL

    بدل (dst_format) {
    حالة SDL_PIXELFORMAT_YV12:
    حالة SDL_PIXELFORMAT_IYUV:
    حالة SDL_PIXELFORMAT_I444:
    حالة SDL_PIXELFORMAT_NV12:
    حالة SDL_PIXELFORMAT_NV21:
    {
        ثابت Uint8 *curr_ردیف, *بعدی_ردیف;

        Uint8 *plane_y;
        Uint8 *plane_u;
        Uint8 *plane_v;
        Uint8 *plane_interleaved_uv;
        Uint32 y_stride, uv_stride, y_skip, uv_skip;

        إذا (!GetYUVPlanes(عرض, ارتفاع, dst_format, dst, dst_pitch,
                          (ثابت Uint8 **)&plane_y, (ثابت Uint8 **)&plane_u, (ثابت Uint8 **)&plane_v,
                          &y_stride, &uv_stride)) {
            أرجع false;
        }

        plane_interleaved_uv = (plane_y + ارتفاع * y_stride);
        y_skip = (y_stride - عرض);

        curr_ردیف = (ثابت Uint8 *)src;

        // Write Y plane
        لكل (j = 0; j < ارتفاع; j++) {
            لكل (i = 0; i < عرض; i++) {
                ثابت Uint32 p1 = ((ثابت Uint32 *)curr_ردیف)[i];
                ثابت Uint32 r = (p1 & 0x00ff0000) >> 16;
                ثابت Uint32 g = (p1 & 0x0000ff00) >> 8;
                ثابت Uint32 b = (p1 & 0x000000ff);
                *plane_y++ = MAKE_Y(r, g, b);
            }
            plane_y += y_skip;
            curr_ردیف += src_pitch;
        }

        curr_ردیف = (ثابت Uint8 *)src;
        بعدی_ردیف = (ثابت Uint8 *)src;
        بعدی_ردیف += src_pitch;

        إذا (dst_format == SDL_PIXELFORMAT_YV12 || dst_format == SDL_PIXELFORMAT_IYUV) {
            // Write UV planes, not interleaved
            uv_skip = (uv_stride - (عرض + 1) / 2);
            لكل (j = 0; j < ارتفاع_half; j++) {
                لكل (i = 0; i < عرض_half; i++) {
                    READ_2x2_PIXELS;
                    *plane_u++ = MAKE_U(r, g, b);
                    *plane_v++ = MAKE_V(r, g, b);
                }
                إذا (عرض_remainder) {
                    READ_2x1_PIXELS;
                    *plane_u++ = MAKE_U(r, g, b);
                    *plane_v++ = MAKE_V(r, g, b);
                }
                plane_u += uv_skip;
                plane_v += uv_skip;
                curr_ردیف += src_pitch_x_2;
                بعدی_ردیف += src_pitch_x_2;
            }
            إذا (ارتفاع_remainder) {
                لكل (i = 0; i < عرض_half; i++) {
                    READ_1x2_PIXELS;
                    *plane_u++ = MAKE_U(r, g, b);
                    *plane_v++ = MAKE_V(r, g, b);
                }
                إذا (عرض_remainder) {
                    READ_1x1_PIXEL;
                    *plane_u++ = MAKE_U(r, g, b);
                    *plane_v++ = MAKE_V(r, g, b);
                }
                plane_u += uv_skip;
                plane_v += uv_skip;
            }
        } وإلا إذا (dst_format == SDL_PIXELFORMAT_I444) {
            // Write UV planes, not interleaved
            uv_skip = (uv_stride - عرض);
            لكل (j = 0; j < ارتفاع; j++) {
                لكل (i = 0; i < عرض; i++) {
                    ثابت Uint32 p1 = ((ثابت Uint32 *)curr_ردیف)[i];
                    ثابت Uint32 r = (p1 & 0x00ff0000) >> 16;
                    ثابت Uint32 g = (p1 & 0x0000ff00) >> 8;
                    ثابت Uint32 b = (p1 & 0x000000ff);
                    *plane_u++ = MAKE_U(r, g, b);
                    *plane_v++ = MAKE_V(r, g, b);
                }
                plane_u += uv_skip;
                plane_v += uv_skip;
                curr_ردیف += src_pitch;
            }
        } وإلا إذا (dst_format == SDL_PIXELFORMAT_NV12) {
            uv_skip = (uv_stride - ((عرض + 1) / 2) * 2);
            لكل (j = 0; j < ارتفاع_half; j++) {
                لكل (i = 0; i < عرض_half; i++) {
                    READ_2x2_PIXELS;
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                }
                إذا (عرض_remainder) {
                    READ_2x1_PIXELS;
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                }
                plane_interleaved_uv += uv_skip;
                curr_ردیف += src_pitch_x_2;
                بعدی_ردیف += src_pitch_x_2;
            }
            إذا (ارتفاع_remainder) {
                لكل (i = 0; i < عرض_half; i++) {
                    READ_1x2_PIXELS;
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                }
                إذا (عرض_remainder) {
                    READ_1x1_PIXEL;
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                }
            }
        } وإلا /* dst_format == SDL_PIXELFORMAT_NV21 */ {
            uv_skip = (uv_stride - ((عرض + 1) / 2) * 2);
            لكل (j = 0; j < ارتفاع_half; j++) {
                لكل (i = 0; i < عرض_half; i++) {
                    READ_2x2_PIXELS;
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                }
                إذا (عرض_remainder) {
                    READ_2x1_PIXELS;
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                }
                plane_interleaved_uv += uv_skip;
                curr_ردیف += src_pitch_x_2;
                بعدی_ردیف += src_pitch_x_2;
            }
            إذا (ارتفاع_remainder) {
                لكل (i = 0; i < عرض_half; i++) {
                    READ_1x2_PIXELS;
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                }
                إذا (عرض_remainder) {
                    READ_1x1_PIXEL;
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                }
            }
        }
    } اكسر;

    حالة SDL_PIXELFORMAT_YUY2:
    حالة SDL_PIXELFORMAT_UYVY:
    حالة SDL_PIXELFORMAT_YVYU:
    {
        ثابت Uint8 *curr_ردیف = (ثابت Uint8 *)src;
        Uint8 *plane = (Uint8 *)dst;
        ثابت صحيح ردیف_اندازه = (4 * ((عرض + 1) / 2));
        صحيح plane_skip;

        إذا (dst_pitch < ردیف_اندازه) {
            أرجع SDL_مجموعه_Error("Destination pitch is too small, expected at least %d", ردیف_اندازه);
        }
        plane_skip = (dst_pitch - ردیف_اندازه);

        // Write YUV plane, packed
        إذا (dst_format == SDL_PIXELFORMAT_YUY2) {
            لكل (j = 0; j < ارتفاع; j++) {
                لكل (i = 0; i < عرض_half; i++) {
                    READ_TWO_RGB_PIXELS;
                    // Y U Y1 V
                    *plane++ = MAKE_Y(r, g, b);
                    *plane++ = MAKE_U(R, G, B);
                    *plane++ = MAKE_Y(r1, g1, b1);
                    *plane++ = MAKE_V(R, G, B);
                }
                إذا (عرض_remainder) {
                    READ_ONE_RGB_PIXEL;
                    // Y U Y V
                    *plane++ = MAKE_Y(r, g, b);
                    *plane++ = MAKE_U(r, g, b);
                    *plane++ = MAKE_Y(r, g, b);
                    *plane++ = MAKE_V(r, g, b);
                }
                plane += plane_skip;
                curr_ردیف += src_pitch;
            }
        } وإلا إذا (dst_format == SDL_PIXELFORMAT_UYVY) {
            لكل (j = 0; j < ارتفاع; j++) {
                لكل (i = 0; i < عرض_half; i++) {
                    READ_TWO_RGB_PIXELS;
                    // U Y V Y1
                    *plane++ = MAKE_U(R, G, B);
                    *plane++ = MAKE_Y(r, g, b);
                    *plane++ = MAKE_V(R, G, B);
                    *plane++ = MAKE_Y(r1, g1, b1);
                }
                إذا (عرض_remainder) {
                    READ_ONE_RGB_PIXEL;
                    // U Y V Y
                    *plane++ = MAKE_U(r, g, b);
                    *plane++ = MAKE_Y(r, g, b);
                    *plane++ = MAKE_V(r, g, b);
                    *plane++ = MAKE_Y(r, g, b);
                }
                plane += plane_skip;
                curr_ردیف += src_pitch;
            }
        } وإلا إذا (dst_format == SDL_PIXELFORMAT_YVYU) {
            لكل (j = 0; j < ارتفاع; j++) {
                لكل (i = 0; i < عرض_half; i++) {
                    READ_TWO_RGB_PIXELS;
                    // Y V Y1 U
                    *plane++ = MAKE_Y(r, g, b);
                    *plane++ = MAKE_V(R, G, B);
                    *plane++ = MAKE_Y(r1, g1, b1);
                    *plane++ = MAKE_U(R, G, B);
                }
                إذا (عرض_remainder) {
                    READ_ONE_RGB_PIXEL;
                    // Y V Y U
                    *plane++ = MAKE_Y(r, g, b);
                    *plane++ = MAKE_V(r, g, b);
                    *plane++ = MAKE_Y(r, g, b);
                    *plane++ = MAKE_U(r, g, b);
                }
                plane += plane_skip;
                curr_ردیف += src_pitch;
            }
        }
    } اكسر;

    افتراضي:
        أرجع SDL_مجموعه_Error("Unsupported YUV destination format: %s", SDL_GetPixelFormatName(dst_format));
    }
#لغو_تعریف MAKE_Y
#لغو_تعریف MAKE_U
#لغو_تعریف MAKE_V
#لغو_تعریف READ_2x2_PIXELS
#لغو_تعریف READ_2x1_PIXELS
#لغو_تعریف READ_1x2_PIXELS
#لغو_تعریف READ_1x1_PIXEL
#لغو_تعریف READ_TWO_RGB_PIXELS
#لغو_تعریف READ_ONE_RGB_PIXEL
    أرجع true;
}

ساكن bool SDL_Convert_Pixels_XBGR2101010_مقصد_P010(صحيح عرض, صحيح ارتفاع, ثابت فراغ *src, صحيح src_pitch, SDL_PixelFormat dst_format, فراغ *dst, صحيح dst_pitch, YCbCrType yuv_type)
{
    ثابت صحيح src_pitch_x_2 = src_pitch * 2;
    ثابت صحيح ارتفاع_half = ارتفاع / 2;
    ثابت صحيح ارتفاع_remainder = (ارتفاع & 0x1);
    ثابت صحيح عرض_half = عرض / 2;
    ثابت صحيح عرض_remainder = (عرض & 0x1);
    صحيح i, j;

    ثابت بنية RGB2YUVFactors *cvt = &RGB2YUVFactorTables[yuv_type];

#تعریف_کن MAKE_Y(r, g, b) (Uint16)(((صحيح)(cvt->y[0] * (r) + cvt->y[1] * (g) + cvt->y[2] * (b) + 0.5f) + cvt->y_جابه_جایی) << 6)
#تعریف_کن MAKE_U(r, g, b) (Uint16)(((صحيح)(cvt->u[0] * (r) + cvt->u[1] * (g) + cvt->u[2] * (b) + 0.5f) + 512) << 6)
#تعریف_کن MAKE_V(r, g, b) (Uint16)(((صحيح)(cvt->v[0] * (r) + cvt->v[1] * (g) + cvt->v[2] * (b) + 0.5f) + 512) << 6)

#تعریف_کن READ_2x2_PIXELS                                                                                     \
    ثابت Uint32 p1 = ((ثابت Uint32 *)curr_ردیف)[2 * i];                                                    \
    ثابت Uint32 p2 = ((ثابت Uint32 *)curr_ردیف)[2 * i + 1];                                                \
    ثابت Uint32 p3 = ((ثابت Uint32 *)بعدی_ردیف)[2 * i];                                                    \
    ثابت Uint32 p4 = ((ثابت Uint32 *)بعدی_ردیف)[2 * i + 1];                                                \
    ثابت Uint32 r = ((p1 & 0x000003ff) + (p2 & 0x000003ff) + (p3 & 0x000003ff) + (p4 & 0x000003ff)) >> 2;  \
    ثابت Uint32 g = ((p1 & 0x000ffc00) + (p2 & 0x000ffc00) + (p3 & 0x000ffc00) + (p4 & 0x000ffc00)) >> 12; \
    ثابت Uint32 b = ((p1 & 0x3ff00000) + (p2 & 0x3ff00000) + (p3 & 0x3ff00000) + (p4 & 0x3ff00000)) >> 22

#تعریف_کن READ_2x1_PIXELS                                             \
    ثابت Uint32 p1 = ((ثابت Uint32 *)curr_ردیف)[2 * i];            \
    ثابت Uint32 p2 = ((ثابت Uint32 *)بعدی_ردیف)[2 * i];            \
    ثابت Uint32 r = ((p1 & 0x000003ff) + (p2 & 0x000003ff)) >> 1;  \
    ثابت Uint32 g = ((p1 & 0x000ffc00) + (p2 & 0x000ffc00)) >> 11; \
    ثابت Uint32 b = ((p1 & 0x3ff00000) + (p2 & 0x3ff00000)) >> 21

#تعریف_کن READ_1x2_PIXELS                                             \
    ثابت Uint32 p1 = ((ثابت Uint32 *)curr_ردیف)[2 * i];            \
    ثابت Uint32 p2 = ((ثابت Uint32 *)curr_ردیف)[2 * i + 1];        \
    ثابت Uint32 r = ((p1 & 0x000003ff) + (p2 & 0x000003ff)) >> 1;  \
    ثابت Uint32 g = ((p1 & 0x000ffc00) + (p2 & 0x000ffc00)) >> 11; \
    ثابت Uint32 b = ((p1 & 0x3ff00000) + (p2 & 0x3ff00000)) >> 21

#تعریف_کن READ_1x1_PIXEL                                  \
    ثابت Uint32 p = ((ثابت Uint32 *)curr_ردیف)[2 * i]; \
    ثابت Uint32 r = (p & 0x000003ff);                  \
    ثابت Uint32 g = (p & 0x000ffc00) >> 10;            \
    ثابت Uint32 b = (p & 0x3ff00000) >> 20

    ثابت Uint8 *curr_ردیف, *بعدی_ردیف;

    Uint16 *plane_y;
    Uint16 *plane_u;
    Uint16 *plane_v;
    Uint16 *plane_interleaved_uv;
    Uint32 y_stride, uv_stride, y_skip, uv_skip;

    إذا (!GetYUVPlanes(عرض, ارتفاع, dst_format, dst, dst_pitch,
                      (ثابت Uint8 **)&plane_y, (ثابت Uint8 **)&plane_u, (ثابت Uint8 **)&plane_v,
                      &y_stride, &uv_stride)) {
        أرجع false;
    }

    y_stride /= حجم(Uint16);
    uv_stride /= حجم(Uint16);

    plane_interleaved_uv = (plane_y + ارتفاع * y_stride);
    y_skip = (y_stride - عرض);

    curr_ردیف = (ثابت Uint8 *)src;

    // Write Y plane
    لكل (j = 0; j < ارتفاع; j++) {
        لكل (i = 0; i < عرض; i++) {
            ثابت Uint32 p1 = ((ثابت Uint32 *)curr_ردیف)[i];
            ثابت Uint32 r = (p1 >>  0) & 0x03ff;
            ثابت Uint32 g = (p1 >> 10) & 0x03ff;
            ثابت Uint32 b = (p1 >> 20) & 0x03ff;
            *plane_y++ = MAKE_Y(r, g, b);
        }
        plane_y += y_skip;
        curr_ردیف += src_pitch;
    }

    curr_ردیف = (ثابت Uint8 *)src;
    بعدی_ردیف = (ثابت Uint8 *)src;
    بعدی_ردیف += src_pitch;

    uv_skip = (uv_stride - ((عرض + 1) / 2) * 2);
    لكل (j = 0; j < ارتفاع_half; j++) {
        لكل (i = 0; i < عرض_half; i++) {
            READ_2x2_PIXELS;
            *plane_interleaved_uv++ = MAKE_U(r, g, b);
            *plane_interleaved_uv++ = MAKE_V(r, g, b);
        }
        إذا (عرض_remainder) {
            READ_2x1_PIXELS;
            *plane_interleaved_uv++ = MAKE_U(r, g, b);
            *plane_interleaved_uv++ = MAKE_V(r, g, b);
        }
        plane_interleaved_uv += uv_skip;
        curr_ردیف += src_pitch_x_2;
        بعدی_ردیف += src_pitch_x_2;
    }
    إذا (ارتفاع_remainder) {
        لكل (i = 0; i < عرض_half; i++) {
            READ_1x2_PIXELS;
            *plane_interleaved_uv++ = MAKE_U(r, g, b);
            *plane_interleaved_uv++ = MAKE_V(r, g, b);
        }
        إذا (عرض_remainder) {
            READ_1x1_PIXEL;
            *plane_interleaved_uv++ = MAKE_U(r, g, b);
            *plane_interleaved_uv++ = MAKE_V(r, g, b);
        }
    }

#لغو_تعریف MAKE_Y
#لغو_تعریف MAKE_U
#لغو_تعریف MAKE_V
#لغو_تعریف READ_2x2_PIXELS
#لغو_تعریف READ_2x1_PIXELS
#لغو_تعریف READ_1x2_PIXELS
#لغو_تعریف READ_1x1_PIXEL
    أرجع true;
}

bool SDL_Convert_Pixels_RGB_مقصد_YUV(صحيح عرض, صحيح ارتفاع,
                                  SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ثابت فراغ *src, صحيح src_pitch,
                                  SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, فراغ *dst, صحيح dst_pitch)
{
    YCbCrType yuv_type = YCBCR_601_LIMITED;

    إذا (!GetYUVConversionType(dst_colorspace, عرض, ارتفاع, 8, &yuv_type)) {
        أرجع false;
    }

#إذا 0 // Doesn't handle odd widths
    // RGB24 to FOURCC
    إذا (src_format == SDL_PIXELFORMAT_RGB24) {
        Uint8 *y;
        Uint8 *u;
        Uint8 *v;
        Uint32 y_stride;
        Uint32 uv_stride;

        إذا (GetYUVPlanes(عرض, ارتفاع, dst_format, dst, dst_pitch, (ثابت Uint8 **)&y, (ثابت Uint8 **)&u, (ثابت Uint8 **)&v, &y_stride, &uv_stride) < 0) {
            أرجع false;
        }

        rgb24_yuv420_std(عرض, ارتفاع, src, src_pitch, y, u, v, y_stride, uv_stride, yuv_type);
        أرجع true;
    }
#پایان_اگر

    // ARGB8888 to FOURCC
    إذا (src_format == SDL_PIXELFORMAT_ARGB8888 || src_format == SDL_PIXELFORMAT_XRGB8888) {
        أرجع SDL_Convert_Pixels_XRGB8888_مقصد_YUV(عرض, ارتفاع, src, src_pitch, dst_format, dst, dst_pitch, yuv_type);
    }

    إذا (dst_format == SDL_PIXELFORMAT_P010) {
        إذا (src_format == SDL_PIXELFORMAT_XBGR2101010) {
            أرجع SDL_Convert_Pixels_XBGR2101010_مقصد_P010(عرض, ارتفاع, src, src_pitch, dst_format, dst, dst_pitch, yuv_type);
        }

        // We currently only support converting from XBGR2101010 to P010
        bool نتیجه;
        فراغ *tmp;
        صحيح tmp_pitch = (عرض * حجم(Uint32));

        tmp = SDL_malloc((size_t)tmp_pitch * ارتفاع);
        إذا (!tmp) {
            أرجع false;
        }

        // convert src/src_format to tmp/XBGR2101010
        نتیجه = SDL_ConvertPixelsAndColorspace(عرض, ارتفاع, src_format, src_colorspace, src_properties, src, src_pitch, SDL_PIXELFORMAT_XBGR2101010, dst_colorspace, dst_properties, tmp, tmp_pitch);
        إذا (!نتیجه) {
            SDL_free(tmp);
            أرجع false;
        }

        // convert tmp/XBGR2101010 to dst/P010
        نتیجه = SDL_Convert_Pixels_XBGR2101010_مقصد_P010(عرض, ارتفاع, tmp, tmp_pitch, dst_format, dst, dst_pitch, yuv_type);
        SDL_free(tmp);
        أرجع نتیجه;
    }

    // not ARGB8888 to FOURCC : need an intermediate conversion
    {
        bool نتیجه;
        فراغ *tmp;
        صحيح tmp_pitch = (عرض * حجم(Uint32));

        tmp = SDL_malloc((size_t)tmp_pitch * ارتفاع);
        إذا (!tmp) {
            أرجع false;
        }

        // convert src/src_format to tmp/XRGB8888
        نتیجه = SDL_ConvertPixelsAndColorspace(عرض, ارتفاع, src_format, src_colorspace, src_properties, src, src_pitch, SDL_PIXELFORMAT_XRGB8888, SDL_COLORSPACE_SRGB, 0, tmp, tmp_pitch);
        إذا (!نتیجه) {
            SDL_free(tmp);
            أرجع false;
        }

        // convert tmp/XRGB8888 to dst/FOURCC
        نتیجه = SDL_Convert_Pixels_XRGB8888_مقصد_YUV(عرض, ارتفاع, tmp, tmp_pitch, dst_format, dst, dst_pitch, yuv_type);
        SDL_free(tmp);
        أرجع نتیجه;
    }
}

ساكن bool SDL_Convert_Pixels_YUV_مقصد_YUV_Copy(صحيح عرض, صحيح ارتفاع, SDL_PixelFormat format, ثابت فراغ *src, صحيح src_pitch, فراغ *dst, صحيح dst_pitch)
{
    صحيح i;

    إذا (IsPlanar1x1Format(format)) {
        // YUV planes
        ثابت size_t درازی = عرض * SDL_BYTESPERPIXEL(format);
        لكل (i = ارتفاع * 3; i--;) {
            SDL_memcpy(dst, src, درازی);
            src = (ثابت Uint8 *)src + src_pitch;
            dst = (Uint8 *)dst + dst_pitch;
        }
        أرجع true;
    }

    إذا (IsPlanar2x2Format(format)) {
        ثابت صحيح bpp = SDL_BYTESPERPIXEL(format);

        // Y plane
        ثابت size_t درازی = عرض * bpp;
        لكل (i = ارتفاع; i--;) {
            SDL_memcpy(dst, src, درازی);
            src = (ثابت Uint8 *)src + src_pitch;
            dst = (Uint8 *)dst + dst_pitch;
        }

        إذا (format == SDL_PIXELFORMAT_YV12 ||
            format == SDL_PIXELFORMAT_IYUV ||
            format == SDL_PIXELFORMAT_I0FL) {
            // U and V planes are a quarter the size of the Y plane, rounded up
            عرض = ((عرض + 1) / 2) * bpp;
            ارتفاع = (ارتفاع + 1) / 2;
            src_pitch = ((src_pitch / bpp + 1) / 2) * bpp;
            dst_pitch = ((dst_pitch / bpp + 1) / 2) * bpp;
            لكل (i = ارتفاع * 2; i--;) {
                SDL_memcpy(dst, src, عرض);
                src = (ثابت Uint8 *)src + src_pitch;
                dst = (Uint8 *)dst + dst_pitch;
            }
        } وإلا إذا (format == SDL_PIXELFORMAT_NV12 ||
                   format == SDL_PIXELFORMAT_NV21 ||
                   format == SDL_PIXELFORMAT_P010) {
            // U/V plane is half the height of the Y plane, rounded up, with packed CrCb
            عرض = ((عرض + 1) / 2) * 2 * bpp;
            ارتفاع = (ارتفاع + 1) / 2;
            src_pitch = ((src_pitch / bpp + 1) / 2) * 2 * bpp;
            dst_pitch = ((dst_pitch / bpp + 1) / 2) * 2 * bpp;
            لكل (i = ارتفاع; i--;) {
                SDL_memcpy(dst, src, عرض);
                src = (ثابت Uint8 *)src + src_pitch;
                dst = (Uint8 *)dst + dst_pitch;
            }
        }
        أرجع true;
    }

    إذا (IsPacked4Format(format)) {
        // Packed planes
        عرض = 4 * ((عرض + 1) / 2);
        لكل (i = ارتفاع; i--;) {
            SDL_memcpy(dst, src, عرض);
            src = (ثابت Uint8 *)src + src_pitch;
            dst = (Uint8 *)dst + dst_pitch;
        }
        أرجع true;
    }

    أرجع SDL_مجموعه_Error("SDL_ConvertPixels_YUV_to_YUV_Copy: Unsupported YUV format: %s", SDL_GetPixelFormatName(format));
}

ساكن bool SDL_Convert_Pixels_جابجا_UVPlanes(صحيح عرض, صحيح ارتفاع, ثابت فراغ *src, صحيح src_pitch, فراغ *dst, صحيح dst_pitch)
{
    صحيح y;
    ثابت صحيح UVwidth = (عرض + 1) / 2;
    ثابت صحيح UVheight = (ارتفاع + 1) / 2;

    // Skip the Y plane
    src = (ثابت Uint8 *)src + ارتفاع * src_pitch;
    dst = (Uint8 *)dst + ارتفاع * dst_pitch;

    إذا (src == dst) {
        صحيح UVpitch = (dst_pitch + 1) / 2;
        Uint8 *tmp;
        Uint8 *row1 = (Uint8 *)dst;
        Uint8 *row2 = row1 + UVheight * UVpitch;

        // Allocate a temporary row for the swap
        tmp = (Uint8 *)SDL_malloc(UVwidth);
        إذا (!tmp) {
            أرجع false;
        }
        لكل (y = 0; y < UVheight; ++y) {
            SDL_memcpy(tmp, row1, UVwidth);
            SDL_memcpy(row1, row2, UVwidth);
            SDL_memcpy(row2, tmp, UVwidth);
            row1 += UVpitch;
            row2 += UVpitch;
        }
        SDL_free(tmp);
    } وإلا {
        ثابت Uint8 *srcUV;
        Uint8 *dstUV;
        صحيح srcUVPitch = ((src_pitch + 1) / 2);
        صحيح dstUVPitch = ((dst_pitch + 1) / 2);

        // Copy the first plane
        srcUV = (ثابت Uint8 *)src;
        dstUV = (Uint8 *)dst + UVheight * dstUVPitch;
        لكل (y = 0; y < UVheight; ++y) {
            SDL_memcpy(dstUV, srcUV, UVwidth);
            srcUV += srcUVPitch;
            dstUV += dstUVPitch;
        }

        // Copy the second plane
        dstUV = (Uint8 *)dst;
        لكل (y = 0; y < UVheight; ++y) {
            SDL_memcpy(dstUV, srcUV, UVwidth);
            srcUV += srcUVPitch;
            dstUV += dstUVPitch;
        }
    }
    أرجع true;
}

#اگر_تعریف_شده SDL_SSE2_INTRINSICS
ساكن bool SDL_TARGETING("sse2") SDL_Convert_Pixels_Pack_UVPlanes_مقصد_NV_SSE2(صحيح عرض, صحيح ارتفاع, ثابت فراغ *src, صحيح src_pitch, فراغ *dst, صحيح dst_pitch, bool معکوس_UV)
{
    صحيح x, y;
    ثابت صحيح UVwidth = (عرض + 1) / 2;
    ثابت صحيح UVheight = (ارتفاع + 1) / 2;
    ثابت صحيح srcUVPitch = ((src_pitch + 1) / 2);
    ثابت صحيح src_UVPitch_چپ = srcUVPitch - UVwidth;
    ثابت صحيح dstUVPitch = ((dst_pitch + 1) / 2) * 2;
    ثابت صحيح dst_UVPitch_چپ = dstUVPitch - UVwidth * 2;
    ثابت Uint8 *src1, *src2;
    Uint8 *dstUV;
    Uint8 *tmp = عدم;

    // Skip the Y plane
    src = (ثابت Uint8 *)src + ارتفاع * src_pitch;
    dst = (Uint8 *)dst + ارتفاع * dst_pitch;

    إذا (src == dst) {
        // Need to make a copy of the buffer so we don't clobber it while converting
        tmp = (Uint8 *)SDL_malloc((size_t)2 * UVheight * srcUVPitch);
        إذا (tmp == عدم) {
            أرجع false;
        }
        SDL_memcpy(tmp, src, (size_t)2 * UVheight * srcUVPitch);
        src = tmp;
    }

    إذا (معکوس_UV) {
        src2 = (ثابت Uint8 *)src;
        src1 = src2 + UVheight * srcUVPitch;
    } وإلا {
        src1 = (ثابت Uint8 *)src;
        src2 = src1 + UVheight * srcUVPitch;
    }
    dstUV = (Uint8 *)dst;

    y = UVheight;
    طالما (y--) {
        x = UVwidth;
        طالما (x >= 16) {
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
        طالما (x--) {
            *dstUV++ = *src1++;
            *dstUV++ = *src2++;
        }
        src1 += src_UVPitch_چپ;
        src2 += src_UVPitch_چپ;
        dstUV += dst_UVPitch_چپ;
    }

    إذا (tmp) {
        SDL_free(tmp);
    }
    أرجع true;
}

ساكن bool SDL_TARGETING("sse2") SDL_Convert_Pixels_تقسیم_NV_مقصد_UVPlanes_SSE2(صحيح عرض, صحيح ارتفاع, ثابت فراغ *src, صحيح src_pitch, فراغ *dst, صحيح dst_pitch, bool معکوس_UV)
{
    صحيح x, y;
    ثابت صحيح UVwidth = (عرض + 1) / 2;
    ثابت صحيح UVheight = (ارتفاع + 1) / 2;
    ثابت صحيح srcUVPitch = ((src_pitch + 1) / 2) * 2;
    ثابت صحيح src_UVPitch_چپ = srcUVPitch - UVwidth * 2;
    ثابت صحيح dstUVPitch = ((dst_pitch + 1) / 2);
    ثابت صحيح dst_UVPitch_چپ = dstUVPitch - UVwidth;
    ثابت Uint8 *srcUV;
    Uint8 *dst1, *dst2;
    Uint8 *tmp = عدم;

    // Skip the Y plane
    src = (ثابت Uint8 *)src + ارتفاع * src_pitch;
    dst = (Uint8 *)dst + ارتفاع * dst_pitch;

    إذا (src == dst) {
        // Need to make a copy of the buffer so we don't clobber it while converting
        tmp = (Uint8 *)SDL_malloc((size_t)UVheight * srcUVPitch);
        إذا (tmp == عدم) {
            أرجع false;
        }
        SDL_memcpy(tmp, src, (size_t)UVheight * srcUVPitch);
        src = tmp;
    }

    إذا (معکوس_UV) {
        dst2 = (Uint8 *)dst;
        dst1 = dst2 + UVheight * dstUVPitch;
    } وإلا {
        dst1 = (Uint8 *)dst;
        dst2 = dst1 + UVheight * dstUVPitch;
    }
    srcUV = (ثابت Uint8 *)src;

    y = UVheight;
    طالما (y--) {
        __m128i ماسک = _mm_set1_epi16(0x00FF);
        x = UVwidth;
        طالما (x >= 16) {
            __m128i uv1 = _mm_loadu_si128((__m128i *)srcUV);
            __m128i uv2 = _mm_loadu_si128((__m128i *)(srcUV + 16));
            __m128i u1 = _mm_and_si128(uv1, ماسک);
            __m128i u2 = _mm_and_si128(uv2, ماسک);
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
        طالما (x--) {
            *dst1++ = *srcUV++;
            *dst2++ = *srcUV++;
        }
        srcUV += src_UVPitch_چپ;
        dst1 += dst_UVPitch_چپ;
        dst2 += dst_UVPitch_چپ;
    }

    إذا (tmp) {
        SDL_free(tmp);
    }
    أرجع true;
}

ساكن bool SDL_TARGETING("sse2") SDL_Convert_Pixels_جابجا_NV_SSE2(صحيح عرض, صحيح ارتفاع, ثابت فراغ *src, صحيح src_pitch, فراغ *dst, صحيح dst_pitch)
{
    صحيح x, y;
    ثابت صحيح UVwidth = (عرض + 1) / 2;
    ثابت صحيح UVheight = (ارتفاع + 1) / 2;
    ثابت صحيح srcUVPitch = ((src_pitch + 1) / 2) * 2;
    ثابت صحيح src_UVPitch_چپ = (srcUVPitch - UVwidth * 2) / حجم(Uint16);
    ثابت صحيح dstUVPitch = ((dst_pitch + 1) / 2) * 2;
    ثابت صحيح dst_UVPitch_چپ = (dstUVPitch - UVwidth * 2) / حجم(Uint16);
    ثابت Uint16 *srcUV;
    Uint16 *dstUV;

    // Skip the Y plane
    src = (ثابت Uint8 *)src + ارتفاع * src_pitch;
    dst = (Uint8 *)dst + ارتفاع * dst_pitch;

    srcUV = (ثابت Uint16 *)src;
    dstUV = (Uint16 *)dst;
    y = UVheight;
    طالما (y--) {
        x = UVwidth;
        طالما (x >= 8) {
            __m128i uv = _mm_loadu_si128((__m128i *)srcUV);
            __m128i v = _mm_slli_epi16(uv, 8);
            __m128i u = _mm_srli_epi16(uv, 8);
            __m128i vu = _mm_or_si128(v, u);
            _mm_storeu_si128((__m128i *)dstUV, vu);
            srcUV += 8;
            dstUV += 8;
            x -= 8;
        }
        إذا (x > 0) {
            ثابت Uint8 *srcUV8 = (ثابت Uint8 *)srcUV;
            Uint8 *dstUV8 = (Uint8 *)dstUV;
            srcUV += x;
            dstUV += x;
            طالما (x--) {
                Uint8 u = *srcUV8++;
                Uint8 v = *srcUV8++;
                *dstUV8++ = v;
                *dstUV8++ = u;
            }
        }
        srcUV += src_UVPitch_چپ;
        dstUV += dst_UVPitch_چپ;
    }
    أرجع true;
}
#پایان_اگر

ساكن bool SDL_Convert_Pixels_Pack_UVPlanes_مقصد_NV_std(صحيح عرض, صحيح ارتفاع, ثابت فراغ *src, صحيح src_pitch, فراغ *dst, صحيح dst_pitch, bool معکوس_UV)
{
    صحيح x, y;
    ثابت صحيح UVwidth = (عرض + 1) / 2;
    ثابت صحيح UVheight = (ارتفاع + 1) / 2;
    ثابت صحيح srcUVPitch = ((src_pitch + 1) / 2);
    ثابت صحيح src_UVPitch_چپ = srcUVPitch - UVwidth;
    ثابت صحيح dstUVPitch = ((dst_pitch + 1) / 2) * 2;
    ثابت صحيح dst_UVPitch_چپ = dstUVPitch - UVwidth * 2;
    ثابت Uint8 *src1, *src2;
    Uint8 *dstUV;
    Uint8 *tmp = عدم;

    // Skip the Y plane
    src = (ثابت Uint8 *)src + ارتفاع * src_pitch;
    dst = (Uint8 *)dst + ارتفاع * dst_pitch;

    إذا (src == dst) {
        // Need to make a copy of the buffer so we don't clobber it while converting
        tmp = (Uint8 *)SDL_malloc((size_t)2 * UVheight * srcUVPitch);
        إذا (!tmp) {
            أرجع false;
        }
        SDL_memcpy(tmp, src, (size_t)2 * UVheight * srcUVPitch);
        src = tmp;
    }

    إذا (معکوس_UV) {
        src2 = (ثابت Uint8 *)src;
        src1 = src2 + UVheight * srcUVPitch;
    } وإلا {
        src1 = (ثابت Uint8 *)src;
        src2 = src1 + UVheight * srcUVPitch;
    }
    dstUV = (Uint8 *)dst;

    y = UVheight;
    طالما (y--) {
        x = UVwidth;
        طالما (x--) {
            *dstUV++ = *src1++;
            *dstUV++ = *src2++;
        }
        src1 += src_UVPitch_چپ;
        src2 += src_UVPitch_چپ;
        dstUV += dst_UVPitch_چپ;
    }

    SDL_free(tmp);
    أرجع true;
}

ساكن bool SDL_Convert_Pixels_تقسیم_NV_مقصد_UVPlanes_std(صحيح عرض, صحيح ارتفاع, ثابت فراغ *src, صحيح src_pitch, فراغ *dst, صحيح dst_pitch, bool معکوس_UV)
{
    صحيح x, y;
    ثابت صحيح UVwidth = (عرض + 1) / 2;
    ثابت صحيح UVheight = (ارتفاع + 1) / 2;
    ثابت صحيح srcUVPitch = ((src_pitch + 1) / 2) * 2;
    ثابت صحيح src_UVPitch_چپ = srcUVPitch - UVwidth * 2;
    ثابت صحيح dstUVPitch = ((dst_pitch + 1) / 2);
    ثابت صحيح dst_UVPitch_چپ = dstUVPitch - UVwidth;
    ثابت Uint8 *srcUV;
    Uint8 *dst1, *dst2;
    Uint8 *tmp = عدم;

    // Skip the Y plane
    src = (ثابت Uint8 *)src + ارتفاع * src_pitch;
    dst = (Uint8 *)dst + ارتفاع * dst_pitch;

    إذا (src == dst) {
        // Need to make a copy of the buffer so we don't clobber it while converting
        tmp = (Uint8 *)SDL_malloc((size_t)UVheight * srcUVPitch);
        إذا (!tmp) {
            أرجع false;
        }
        SDL_memcpy(tmp, src, (size_t)UVheight * srcUVPitch);
        src = tmp;
    }

    إذا (معکوس_UV) {
        dst2 = (Uint8 *)dst;
        dst1 = dst2 + UVheight * dstUVPitch;
    } وإلا {
        dst1 = (Uint8 *)dst;
        dst2 = dst1 + UVheight * dstUVPitch;
    }
    srcUV = (ثابت Uint8 *)src;

    y = UVheight;
    طالما (y--) {
        x = UVwidth;
        طالما (x--) {
            *dst1++ = *srcUV++;
            *dst2++ = *srcUV++;
        }
        srcUV += src_UVPitch_چپ;
        dst1 += dst_UVPitch_چپ;
        dst2 += dst_UVPitch_چپ;
    }

    SDL_free(tmp);
    أرجع true;
}

ساكن bool SDL_Convert_Pixels_جابجا_NV_std(صحيح عرض, صحيح ارتفاع, ثابت فراغ *src, صحيح src_pitch, فراغ *dst, صحيح dst_pitch)
{
    صحيح x, y;
    ثابت صحيح UVwidth = (عرض + 1) / 2;
    ثابت صحيح UVheight = (ارتفاع + 1) / 2;
    ثابت صحيح srcUVPitch = ((src_pitch + 1) / 2) * 2;
    ثابت صحيح dstUVPitch = ((dst_pitch + 1) / 2) * 2;

    // Skip the Y plane
    src = (ثابت Uint8 *)src + ارتفاع * src_pitch;
    dst = (Uint8 *)dst + ارتفاع * dst_pitch;

    bool aligned = (((uintptr_t)src | (uintptr_t)dst) & 1) == 0;
    إذا (aligned) {
        ثابت صحيح src_UVPitch_چپ = (srcUVPitch - UVwidth * 2) / حجم(Uint16);
        ثابت صحيح dst_UVPitch_چپ = (dstUVPitch - UVwidth * 2) / حجم(Uint16);
        ثابت Uint16 *srcUV = (ثابت Uint16 *)src;
        Uint16 *dstUV = (Uint16 *)dst;
        y = UVheight;
        طالما (y--) {
            x = UVwidth;
            طالما (x--) {
                *dstUV++ = SDL_Swap16(*srcUV++);
            }
            srcUV += src_UVPitch_چپ;
            dstUV += dst_UVPitch_چپ;
        }
    } وإلا {
        ثابت صحيح src_UVPitch_چپ = (srcUVPitch - UVwidth * 2);
        ثابت صحيح dst_UVPitch_چپ = (dstUVPitch - UVwidth * 2);
        ثابت Uint8 *srcUV = (ثابت Uint8 *)src;
        Uint8 *dstUV = (Uint8 *)dst;
        y = UVheight;
        طالما (y--) {
            x = UVwidth;
            طالما (x--) {
                Uint8 u = *srcUV++;
                Uint8 v = *srcUV++;
                *dstUV++ = v;
                *dstUV++ = u;
            }
            srcUV += src_UVPitch_چپ;
            dstUV += dst_UVPitch_چپ;
        }
    }
    أرجع true;
}

ساكن bool SDL_Convert_Pixels_Pack_UVPlanes_مقصد_NV(صحيح عرض, صحيح ارتفاع, ثابت فراغ *src, صحيح src_pitch, فراغ *dst, صحيح dst_pitch, bool معکوس_UV)
{
#اگر_تعریف_شده SDL_SSE2_INTRINSICS
    إذا (SDL_HasSSE2()) {
      أرجع SDL_Convert_Pixels_Pack_UVPlanes_مقصد_NV_SSE2(عرض, ارتفاع, src, src_pitch, dst, dst_pitch, معکوس_UV);
    }
#پایان_اگر
    أرجع SDL_Convert_Pixels_Pack_UVPlanes_مقصد_NV_std(عرض, ارتفاع, src, src_pitch, dst, dst_pitch, معکوس_UV);
}

ساكن bool SDL_Convert_Pixels_تقسیم_NV_مقصد_UVPlanes(صحيح عرض, صحيح ارتفاع, ثابت فراغ *src, صحيح src_pitch, فراغ *dst, صحيح dst_pitch, bool معکوس_UV)
{
#اگر_تعریف_شده SDL_SSE2_INTRINSICS
    إذا (SDL_HasSSE2()) {
      أرجع SDL_Convert_Pixels_تقسیم_NV_مقصد_UVPlanes_SSE2(عرض, ارتفاع, src, src_pitch, dst, dst_pitch, معکوس_UV);
    }
#پایان_اگر
    أرجع SDL_Convert_Pixels_تقسیم_NV_مقصد_UVPlanes_std(عرض, ارتفاع, src, src_pitch, dst, dst_pitch, معکوس_UV);
}

ساكن bool SDL_Convert_Pixels_جابجا_NV(صحيح عرض, صحيح ارتفاع, ثابت فراغ *src, صحيح src_pitch, فراغ *dst, صحيح dst_pitch)
{
#اگر_تعریف_شده SDL_SSE2_INTRINSICS
    إذا (SDL_HasSSE2()) {
      أرجع SDL_Convert_Pixels_جابجا_NV_SSE2(عرض, ارتفاع, src, src_pitch, dst, dst_pitch);
    }
#پایان_اگر
    أرجع SDL_Convert_Pixels_جابجا_NV_std(عرض, ارتفاع, src, src_pitch, dst, dst_pitch);
}

ساكن bool SDL_Convert_Pixels_Planar2x2_مقصد_Planar2x2(صحيح عرض, صحيح ارتفاع,
                                                     SDL_PixelFormat src_format, ثابت فراغ *src, صحيح src_pitch,
                                                     SDL_PixelFormat dst_format, فراغ *dst, صحيح dst_pitch)
{
    إذا (src != dst) {
        // Copy Y plane
        صحيح i;
        ثابت Uint8 *srcY = (ثابت Uint8 *)src;
        Uint8 *dstY = (Uint8 *)dst;
        لكل (i = ارتفاع; i--;) {
            SDL_memcpy(dstY, srcY, عرض);
            srcY += src_pitch;
            dstY += dst_pitch;
        }
    }

    بدل (src_format) {
    حالة SDL_PIXELFORMAT_YV12:
        بدل (dst_format) {
        حالة SDL_PIXELFORMAT_IYUV:
            أرجع SDL_Convert_Pixels_جابجا_UVPlanes(عرض, ارتفاع, src, src_pitch, dst, dst_pitch);
        حالة SDL_PIXELFORMAT_NV12:
            أرجع SDL_Convert_Pixels_Pack_UVPlanes_مقصد_NV(عرض, ارتفاع, src, src_pitch, dst, dst_pitch, true);
        حالة SDL_PIXELFORMAT_NV21:
            أرجع SDL_Convert_Pixels_Pack_UVPlanes_مقصد_NV(عرض, ارتفاع, src, src_pitch, dst, dst_pitch, false);
        افتراضي:
            اكسر;
        }
        اكسر;
    حالة SDL_PIXELFORMAT_IYUV:
        بدل (dst_format) {
        حالة SDL_PIXELFORMAT_YV12:
            أرجع SDL_Convert_Pixels_جابجا_UVPlanes(عرض, ارتفاع, src, src_pitch, dst, dst_pitch);
        حالة SDL_PIXELFORMAT_NV12:
            أرجع SDL_Convert_Pixels_Pack_UVPlanes_مقصد_NV(عرض, ارتفاع, src, src_pitch, dst, dst_pitch, false);
        حالة SDL_PIXELFORMAT_NV21:
            أرجع SDL_Convert_Pixels_Pack_UVPlanes_مقصد_NV(عرض, ارتفاع, src, src_pitch, dst, dst_pitch, true);
        افتراضي:
            اكسر;
        }
        اكسر;
    حالة SDL_PIXELFORMAT_NV12:
        بدل (dst_format) {
        حالة SDL_PIXELFORMAT_YV12:
            أرجع SDL_Convert_Pixels_تقسیم_NV_مقصد_UVPlanes(عرض, ارتفاع, src, src_pitch, dst, dst_pitch, true);
        حالة SDL_PIXELFORMAT_IYUV:
            أرجع SDL_Convert_Pixels_تقسیم_NV_مقصد_UVPlanes(عرض, ارتفاع, src, src_pitch, dst, dst_pitch, false);
        حالة SDL_PIXELFORMAT_NV21:
            أرجع SDL_Convert_Pixels_جابجا_NV(عرض, ارتفاع, src, src_pitch, dst, dst_pitch);
        افتراضي:
            اكسر;
        }
        اكسر;
    حالة SDL_PIXELFORMAT_NV21:
        بدل (dst_format) {
        حالة SDL_PIXELFORMAT_YV12:
            أرجع SDL_Convert_Pixels_تقسیم_NV_مقصد_UVPlanes(عرض, ارتفاع, src, src_pitch, dst, dst_pitch, false);
        حالة SDL_PIXELFORMAT_IYUV:
            أرجع SDL_Convert_Pixels_تقسیم_NV_مقصد_UVPlanes(عرض, ارتفاع, src, src_pitch, dst, dst_pitch, true);
        حالة SDL_PIXELFORMAT_NV12:
            أرجع SDL_Convert_Pixels_جابجا_NV(عرض, ارتفاع, src, src_pitch, dst, dst_pitch);
        افتراضي:
            اكسر;
        }
        اكسر;
    افتراضي:
        اكسر;
    }
    أرجع SDL_مجموعه_Error("SDL_ConvertPixels_Planar2x2_to_Planar2x2: Unsupported YUV conversion: %s -> %s", SDL_GetPixelFormatName(src_format),
                        SDL_GetPixelFormatName(dst_format));
}

#اگر_تعریف_شده SDL_SSE2_INTRINSICS
#تعریف_کن PACKED4_مقصد_PACKED4_ردیف_SSE2(shuffle)                      \
    طالما (x >= 4) {                                              \
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

ساكن bool SDL_TARGETING("sse2") SDL_Convert_Pixels_YUY2_مقصد_UYVY_SSE2(صحيح عرض, صحيح ارتفاع, ثابت فراغ *src, صحيح src_pitch, فراغ *dst, صحيح dst_pitch)
{
    صحيح x, y;
    ثابت صحيح YUVwidth = (عرض + 1) / 2;
    ثابت صحيح src_YUVPitch_چپ = (src_pitch - YUVwidth * 4);
    ثابت صحيح dst_YUVPitch_چپ = (dst_pitch - YUVwidth * 4);
    ثابت Uint8 *srcYUV = (ثابت Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = ارتفاع;
    x = YUVwidth;
    طالما (y--) {
        PACKED4_مقصد_PACKED4_ردیف_SSE2(_MM_SHUFFLE(2, 3, 0, 1));
        طالما (x--) {
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
        srcYUV += src_YUVPitch_چپ;
        dstYUV += dst_YUVPitch_چپ;
        x = YUVwidth;
    }
    أرجع true;
}

ساكن bool SDL_TARGETING("sse2") SDL_Convert_Pixels_YUY2_مقصد_YVYU_SSE2(صحيح عرض, صحيح ارتفاع, ثابت فراغ *src, صحيح src_pitch, فراغ *dst, صحيح dst_pitch)
{
    صحيح x, y;
    ثابت صحيح YUVwidth = (عرض + 1) / 2;
    ثابت صحيح src_YUVPitch_چپ = (src_pitch - YUVwidth * 4);
    ثابت صحيح dst_YUVPitch_چپ = (dst_pitch - YUVwidth * 4);
    ثابت Uint8 *srcYUV = (ثابت Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = ارتفاع;
    x = YUVwidth;
    طالما (y--) {
        PACKED4_مقصد_PACKED4_ردیف_SSE2(_MM_SHUFFLE(1, 2, 3, 0));
        طالما (x--) {
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
        srcYUV += src_YUVPitch_چپ;
        dstYUV += dst_YUVPitch_چپ;
        x = YUVwidth;
    }
    أرجع true;
}

ساكن bool SDL_TARGETING("sse2") SDL_Convert_Pixels_UYVY_مقصد_YUY2_SSE2(صحيح عرض, صحيح ارتفاع, ثابت فراغ *src, صحيح src_pitch, فراغ *dst, صحيح dst_pitch)
{
    صحيح x, y;
    ثابت صحيح YUVwidth = (عرض + 1) / 2;
    ثابت صحيح src_YUVPitch_چپ = (src_pitch - YUVwidth * 4);
    ثابت صحيح dst_YUVPitch_چپ = (dst_pitch - YUVwidth * 4);
    ثابت Uint8 *srcYUV = (ثابت Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = ارتفاع;
    x = YUVwidth;
    طالما (y--) {
        PACKED4_مقصد_PACKED4_ردیف_SSE2(_MM_SHUFFLE(2, 3, 0, 1));
        طالما (x--) {
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
        srcYUV += src_YUVPitch_چپ;
        dstYUV += dst_YUVPitch_چپ;
        x = YUVwidth;
    }
    أرجع true;
}

ساكن bool SDL_TARGETING("sse2") SDL_Convert_Pixels_UYVY_مقصد_YVYU_SSE2(صحيح عرض, صحيح ارتفاع, ثابت فراغ *src, صحيح src_pitch, فراغ *dst, صحيح dst_pitch)
{
    صحيح x, y;
    ثابت صحيح YUVwidth = (عرض + 1) / 2;
    ثابت صحيح src_YUVPitch_چپ = (src_pitch - YUVwidth * 4);
    ثابت صحيح dst_YUVPitch_چپ = (dst_pitch - YUVwidth * 4);
    ثابت Uint8 *srcYUV = (ثابت Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = ارتفاع;
    x = YUVwidth;
    طالما (y--) {
        PACKED4_مقصد_PACKED4_ردیف_SSE2(_MM_SHUFFLE(0, 3, 2, 1));
        طالما (x--) {
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
        srcYUV += src_YUVPitch_چپ;
        dstYUV += dst_YUVPitch_چپ;
        x = YUVwidth;
    }
    أرجع true;
}

ساكن bool SDL_TARGETING("sse2") SDL_Convert_Pixels_YVYU_مقصد_YUY2_SSE2(صحيح عرض, صحيح ارتفاع, ثابت فراغ *src, صحيح src_pitch, فراغ *dst, صحيح dst_pitch)
{
    صحيح x, y;
    ثابت صحيح YUVwidth = (عرض + 1) / 2;
    ثابت صحيح src_YUVPitch_چپ = (src_pitch - YUVwidth * 4);
    ثابت صحيح dst_YUVPitch_چپ = (dst_pitch - YUVwidth * 4);
    ثابت Uint8 *srcYUV = (ثابت Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = ارتفاع;
    x = YUVwidth;
    طالما (y--) {
        PACKED4_مقصد_PACKED4_ردیف_SSE2(_MM_SHUFFLE(1, 2, 3, 0));
        طالما (x--) {
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
        srcYUV += src_YUVPitch_چپ;
        dstYUV += dst_YUVPitch_چپ;
        x = YUVwidth;
    }
    أرجع true;
}

ساكن bool SDL_TARGETING("sse2") SDL_Convert_Pixels_YVYU_مقصد_UYVY_SSE2(صحيح عرض, صحيح ارتفاع, ثابت فراغ *src, صحيح src_pitch, فراغ *dst, صحيح dst_pitch)
{
    صحيح x, y;
    ثابت صحيح YUVwidth = (عرض + 1) / 2;
    ثابت صحيح src_YUVPitch_چپ = (src_pitch - YUVwidth * 4);
    ثابت صحيح dst_YUVPitch_چپ = (dst_pitch - YUVwidth * 4);
    ثابت Uint8 *srcYUV = (ثابت Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = ارتفاع;
    x = YUVwidth;
    طالما (y--) {
        PACKED4_مقصد_PACKED4_ردیف_SSE2(_MM_SHUFFLE(2, 1, 0, 3));
        طالما (x--) {
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
        srcYUV += src_YUVPitch_چپ;
        dstYUV += dst_YUVPitch_چپ;
        x = YUVwidth;
    }
    أرجع true;
}
#پایان_اگر

ساكن bool SDL_Convert_Pixels_YUY2_مقصد_UYVY_std(صحيح عرض, صحيح ارتفاع, ثابت فراغ *src, صحيح src_pitch, فراغ *dst, صحيح dst_pitch)
{
    صحيح x, y;
    ثابت صحيح YUVwidth = (عرض + 1) / 2;
    ثابت صحيح src_YUVPitch_چپ = (src_pitch - YUVwidth * 4);
    ثابت صحيح dst_YUVPitch_چپ = (dst_pitch - YUVwidth * 4);
    ثابت Uint8 *srcYUV = (ثابت Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = ارتفاع;
    طالما (y--) {
        x = YUVwidth;
        طالما (x--) {
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
        srcYUV += src_YUVPitch_چپ;
        dstYUV += dst_YUVPitch_چپ;
    }
    أرجع true;
}

ساكن bool SDL_Convert_Pixels_YUY2_مقصد_YVYU_std(صحيح عرض, صحيح ارتفاع, ثابت فراغ *src, صحيح src_pitch, فراغ *dst, صحيح dst_pitch)
{
    صحيح x, y;
    ثابت صحيح YUVwidth = (عرض + 1) / 2;
    ثابت صحيح src_YUVPitch_چپ = (src_pitch - YUVwidth * 4);
    ثابت صحيح dst_YUVPitch_چپ = (dst_pitch - YUVwidth * 4);
    ثابت Uint8 *srcYUV = (ثابت Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = ارتفاع;
    طالما (y--) {
        x = YUVwidth;
        طالما (x--) {
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
        srcYUV += src_YUVPitch_چپ;
        dstYUV += dst_YUVPitch_چپ;
    }
    أرجع true;
}

ساكن bool SDL_Convert_Pixels_UYVY_مقصد_YUY2_std(صحيح عرض, صحيح ارتفاع, ثابت فراغ *src, صحيح src_pitch, فراغ *dst, صحيح dst_pitch)
{
    صحيح x, y;
    ثابت صحيح YUVwidth = (عرض + 1) / 2;
    ثابت صحيح src_YUVPitch_چپ = (src_pitch - YUVwidth * 4);
    ثابت صحيح dst_YUVPitch_چپ = (dst_pitch - YUVwidth * 4);
    ثابت Uint8 *srcYUV = (ثابت Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = ارتفاع;
    طالما (y--) {
        x = YUVwidth;
        طالما (x--) {
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
        srcYUV += src_YUVPitch_چپ;
        dstYUV += dst_YUVPitch_چپ;
    }
    أرجع true;
}

ساكن bool SDL_Convert_Pixels_UYVY_مقصد_YVYU_std(صحيح عرض, صحيح ارتفاع, ثابت فراغ *src, صحيح src_pitch, فراغ *dst, صحيح dst_pitch)
{
    صحيح x, y;
    ثابت صحيح YUVwidth = (عرض + 1) / 2;
    ثابت صحيح src_YUVPitch_چپ = (src_pitch - YUVwidth * 4);
    ثابت صحيح dst_YUVPitch_چپ = (dst_pitch - YUVwidth * 4);
    ثابت Uint8 *srcYUV = (ثابت Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = ارتفاع;
    طالما (y--) {
        x = YUVwidth;
        طالما (x--) {
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
        srcYUV += src_YUVPitch_چپ;
        dstYUV += dst_YUVPitch_چپ;
    }
    أرجع true;
}

ساكن bool SDL_Convert_Pixels_YVYU_مقصد_YUY2_std(صحيح عرض, صحيح ارتفاع, ثابت فراغ *src, صحيح src_pitch, فراغ *dst, صحيح dst_pitch)
{
    صحيح x, y;
    ثابت صحيح YUVwidth = (عرض + 1) / 2;
    ثابت صحيح src_YUVPitch_چپ = (src_pitch - YUVwidth * 4);
    ثابت صحيح dst_YUVPitch_چپ = (dst_pitch - YUVwidth * 4);
    ثابت Uint8 *srcYUV = (ثابت Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = ارتفاع;
    طالما (y--) {
        x = YUVwidth;
        طالما (x--) {
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
        srcYUV += src_YUVPitch_چپ;
        dstYUV += dst_YUVPitch_چپ;
    }
    أرجع true;
}

ساكن bool SDL_Convert_Pixels_YVYU_مقصد_UYVY_std(صحيح عرض, صحيح ارتفاع, ثابت فراغ *src, صحيح src_pitch, فراغ *dst, صحيح dst_pitch)
{
    صحيح x, y;
    ثابت صحيح YUVwidth = (عرض + 1) / 2;
    ثابت صحيح src_YUVPitch_چپ = (src_pitch - YUVwidth * 4);
    ثابت صحيح dst_YUVPitch_چپ = (dst_pitch - YUVwidth * 4);
    ثابت Uint8 *srcYUV = (ثابت Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = ارتفاع;
    طالما (y--) {
        x = YUVwidth;
        طالما (x--) {
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
        srcYUV += src_YUVPitch_چپ;
        dstYUV += dst_YUVPitch_چپ;
    }
    أرجع true;
}

ساكن bool SDL_Convert_Pixels_YUY2_مقصد_UYVY(صحيح عرض, صحيح ارتفاع, ثابت فراغ *src, صحيح src_pitch, فراغ *dst, صحيح dst_pitch)
{
#اگر_تعریف_شده SDL_SSE2_INTRINSICS
    إذا (SDL_HasSSE2()) {
      أرجع SDL_Convert_Pixels_YUY2_مقصد_UYVY_SSE2(عرض, ارتفاع, src, src_pitch, dst, dst_pitch);
    }
#پایان_اگر
    أرجع SDL_Convert_Pixels_YUY2_مقصد_UYVY_std(عرض, ارتفاع, src, src_pitch, dst, dst_pitch);
}

ساكن bool SDL_Convert_Pixels_YUY2_مقصد_YVYU(صحيح عرض, صحيح ارتفاع, ثابت فراغ *src, صحيح src_pitch, فراغ *dst, صحيح dst_pitch)
{
#اگر_تعریف_شده SDL_SSE2_INTRINSICS
    إذا (SDL_HasSSE2()) {
      أرجع SDL_Convert_Pixels_YUY2_مقصد_YVYU_SSE2(عرض, ارتفاع, src, src_pitch, dst, dst_pitch);
    }
#پایان_اگر
    أرجع SDL_Convert_Pixels_YUY2_مقصد_YVYU_std(عرض, ارتفاع, src, src_pitch, dst, dst_pitch);
}

ساكن bool SDL_Convert_Pixels_UYVY_مقصد_YUY2(صحيح عرض, صحيح ارتفاع, ثابت فراغ *src, صحيح src_pitch, فراغ *dst, صحيح dst_pitch)
{
#اگر_تعریف_شده SDL_SSE2_INTRINSICS
    إذا (SDL_HasSSE2()) {
      أرجع SDL_Convert_Pixels_UYVY_مقصد_YUY2_SSE2(عرض, ارتفاع, src, src_pitch, dst, dst_pitch);
    }
#پایان_اگر
    أرجع SDL_Convert_Pixels_UYVY_مقصد_YUY2_std(عرض, ارتفاع, src, src_pitch, dst, dst_pitch);
}

ساكن bool SDL_Convert_Pixels_UYVY_مقصد_YVYU(صحيح عرض, صحيح ارتفاع, ثابت فراغ *src, صحيح src_pitch, فراغ *dst, صحيح dst_pitch)
{
#اگر_تعریف_شده SDL_SSE2_INTRINSICS
    إذا (SDL_HasSSE2()) {
      أرجع SDL_Convert_Pixels_UYVY_مقصد_YVYU_SSE2(عرض, ارتفاع, src, src_pitch, dst, dst_pitch);
    }
#پایان_اگر
    أرجع SDL_Convert_Pixels_UYVY_مقصد_YVYU_std(عرض, ارتفاع, src, src_pitch, dst, dst_pitch);
}

ساكن bool SDL_Convert_Pixels_YVYU_مقصد_YUY2(صحيح عرض, صحيح ارتفاع, ثابت فراغ *src, صحيح src_pitch, فراغ *dst, صحيح dst_pitch)
{
#اگر_تعریف_شده SDL_SSE2_INTRINSICS
    إذا (SDL_HasSSE2()) {
      أرجع SDL_Convert_Pixels_YVYU_مقصد_YUY2_SSE2(عرض, ارتفاع, src, src_pitch, dst, dst_pitch);
    }
#پایان_اگر
    أرجع SDL_Convert_Pixels_YVYU_مقصد_YUY2_std(عرض, ارتفاع, src, src_pitch, dst, dst_pitch);
}

ساكن bool SDL_Convert_Pixels_YVYU_مقصد_UYVY(صحيح عرض, صحيح ارتفاع, ثابت فراغ *src, صحيح src_pitch, فراغ *dst, صحيح dst_pitch)
{
#اگر_تعریف_شده SDL_SSE2_INTRINSICS
    إذا (SDL_HasSSE2()) {
      أرجع SDL_Convert_Pixels_YVYU_مقصد_UYVY_SSE2(عرض, ارتفاع, src, src_pitch, dst, dst_pitch);
    }
#پایان_اگر
    أرجع SDL_Convert_Pixels_YVYU_مقصد_UYVY_std(عرض, ارتفاع, src, src_pitch, dst, dst_pitch);
}

ساكن bool SDL_Convert_Pixels_Packed4_مقصد_Packed4(صحيح عرض, صحيح ارتفاع,
                                                SDL_PixelFormat src_format, ثابت فراغ *src, صحيح src_pitch,
                                                SDL_PixelFormat dst_format, فراغ *dst, صحيح dst_pitch)
{
    بدل (src_format) {
    حالة SDL_PIXELFORMAT_YUY2:
        بدل (dst_format) {
        حالة SDL_PIXELFORMAT_UYVY:
            أرجع SDL_Convert_Pixels_YUY2_مقصد_UYVY(عرض, ارتفاع, src, src_pitch, dst, dst_pitch);
        حالة SDL_PIXELFORMAT_YVYU:
            أرجع SDL_Convert_Pixels_YUY2_مقصد_YVYU(عرض, ارتفاع, src, src_pitch, dst, dst_pitch);
        افتراضي:
            اكسر;
        }
        اكسر;
    حالة SDL_PIXELFORMAT_UYVY:
        بدل (dst_format) {
        حالة SDL_PIXELFORMAT_YUY2:
            أرجع SDL_Convert_Pixels_UYVY_مقصد_YUY2(عرض, ارتفاع, src, src_pitch, dst, dst_pitch);
        حالة SDL_PIXELFORMAT_YVYU:
            أرجع SDL_Convert_Pixels_UYVY_مقصد_YVYU(عرض, ارتفاع, src, src_pitch, dst, dst_pitch);
        افتراضي:
            اكسر;
        }
        اكسر;
    حالة SDL_PIXELFORMAT_YVYU:
        بدل (dst_format) {
        حالة SDL_PIXELFORMAT_YUY2:
            أرجع SDL_Convert_Pixels_YVYU_مقصد_YUY2(عرض, ارتفاع, src, src_pitch, dst, dst_pitch);
        حالة SDL_PIXELFORMAT_UYVY:
            أرجع SDL_Convert_Pixels_YVYU_مقصد_UYVY(عرض, ارتفاع, src, src_pitch, dst, dst_pitch);
        افتراضي:
            اكسر;
        }
        اكسر;
    افتراضي:
        اكسر;
    }
    أرجع SDL_مجموعه_Error("SDL_ConvertPixels_Packed4_to_Packed4: Unsupported YUV conversion: %s -> %s", SDL_GetPixelFormatName(src_format),
                        SDL_GetPixelFormatName(dst_format));
}

ساكن bool SDL_Convert_Pixels_Planar2x2_مقصد_Packed4(صحيح عرض, صحيح ارتفاع,
                                                   SDL_PixelFormat src_format, ثابت فراغ *src, صحيح src_pitch,
                                                   SDL_PixelFormat dst_format, فراغ *dst, صحيح dst_pitch)
{
    صحيح x, y;
    ثابت Uint8 *srcY1, *srcY2, *srcU, *srcV;
    Uint32 srcY_pitch, srcUV_pitch;
    Uint32 src_Y_pitch_چپ, src_UV_pitch_چپ, srcUV_pixel_stride;
    Uint8 *dstY1, *dstY2, *dstU1, *dstU2, *dstV1, *dstV2;
    Uint32 dstY_pitch, dstUV_pitch;
    Uint32 dst_pitch_چپ;

    إذا (src == dst) {
        أرجع SDL_مجموعه_Error("Can't change YUV plane types in-place");
    }

    إذا (!GetYUVPlanes(عرض, ارتفاع, src_format, src, src_pitch,
                      &srcY1, &srcU, &srcV, &srcY_pitch, &srcUV_pitch)) {
        أرجع false;
    }
    srcY2 = srcY1 + srcY_pitch;
    src_Y_pitch_چپ = (srcY_pitch - عرض);

    إذا (src_format == SDL_PIXELFORMAT_NV12 || src_format == SDL_PIXELFORMAT_NV21) {
        srcUV_pixel_stride = 2;
        src_UV_pitch_چپ = (srcUV_pitch - 2 * ((عرض + 1) / 2));
    } وإلا {
        srcUV_pixel_stride = 1;
        src_UV_pitch_چپ = (srcUV_pitch - ((عرض + 1) / 2));
    }

    إذا (!GetYUVPlanes(عرض, ارتفاع, dst_format, dst, dst_pitch,
                      (ثابت Uint8 **)&dstY1, (ثابت Uint8 **)&dstU1, (ثابت Uint8 **)&dstV1,
                      &dstY_pitch, &dstUV_pitch)) {
        أرجع false;
    }
    dstY2 = dstY1 + dstY_pitch;
    dstU2 = dstU1 + dstUV_pitch;
    dstV2 = dstV1 + dstUV_pitch;
    dst_pitch_چپ = (dstY_pitch - 4 * ((عرض + 1) / 2));

    // Copy 2x2 blocks of pixels at a time
    لكل (y = 0; y < (ارتفاع - 1); y += 2) {
        لكل (x = 0; x < (عرض - 1); x += 2) {
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
        إذا (x == (عرض - 1)) {
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

        srcY1 += src_Y_pitch_چپ + srcY_pitch;
        srcY2 += src_Y_pitch_چپ + srcY_pitch;
        srcU += src_UV_pitch_چپ;
        srcV += src_UV_pitch_چپ;
        dstY1 += dst_pitch_چپ + dstY_pitch;
        dstY2 += dst_pitch_چپ + dstY_pitch;
        dstU1 += dst_pitch_چپ + dstUV_pitch;
        dstU2 += dst_pitch_چپ + dstUV_pitch;
        dstV1 += dst_pitch_چپ + dstUV_pitch;
        dstV2 += dst_pitch_چپ + dstUV_pitch;
    }

    // Last row
    إذا (y == (ارتفاع - 1)) {
        لكل (x = 0; x < (عرض - 1); x += 2) {
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
        إذا (x == (عرض - 1)) {
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
    أرجع true;
}

ساكن bool SDL_Convert_Pixels_Packed4_مقصد_Planar2x2(صحيح عرض, صحيح ارتفاع,
                                                   SDL_PixelFormat src_format, ثابت فراغ *src, صحيح src_pitch,
                                                   SDL_PixelFormat dst_format, فراغ *dst, صحيح dst_pitch)
{
    صحيح x, y;
    ثابت Uint8 *srcY1, *srcY2, *srcU1, *srcU2, *srcV1, *srcV2;
    Uint32 srcY_pitch, srcUV_pitch;
    Uint32 src_pitch_چپ;
    Uint8 *dstY1, *dstY2, *dstU, *dstV;
    Uint32 dstY_pitch, dstUV_pitch;
    Uint32 dst_Y_pitch_چپ, dst_UV_pitch_چپ, dstUV_pixel_stride;

    إذا (src == dst) {
        أرجع SDL_مجموعه_Error("Can't change YUV plane types in-place");
    }

    إذا (!GetYUVPlanes(عرض, ارتفاع, src_format, src, src_pitch,
                      &srcY1, &srcU1, &srcV1, &srcY_pitch, &srcUV_pitch)) {
        أرجع false;
    }
    srcY2 = srcY1 + srcY_pitch;
    srcU2 = srcU1 + srcUV_pitch;
    srcV2 = srcV1 + srcUV_pitch;
    src_pitch_چپ = (srcY_pitch - 4 * ((عرض + 1) / 2));

    إذا (!GetYUVPlanes(عرض, ارتفاع, dst_format, dst, dst_pitch,
                      (ثابت Uint8 **)&dstY1, (ثابت Uint8 **)&dstU, (ثابت Uint8 **)&dstV,
                      &dstY_pitch, &dstUV_pitch)) {
        أرجع false;
    }
    dstY2 = dstY1 + dstY_pitch;
    dst_Y_pitch_چپ = (dstY_pitch - عرض);

    إذا (dst_format == SDL_PIXELFORMAT_NV12 || dst_format == SDL_PIXELFORMAT_NV21) {
        dstUV_pixel_stride = 2;
        dst_UV_pitch_چپ = (dstUV_pitch - 2 * ((عرض + 1) / 2));
    } وإلا {
        dstUV_pixel_stride = 1;
        dst_UV_pitch_چپ = (dstUV_pitch - ((عرض + 1) / 2));
    }

    // Copy 2x2 blocks of pixels at a time
    لكل (y = 0; y < (ارتفاع - 1); y += 2) {
        لكل (x = 0; x < (عرض - 1); x += 2) {
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
        إذا (x == (عرض - 1)) {
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

        srcY1 += src_pitch_چپ + srcY_pitch;
        srcY2 += src_pitch_چپ + srcY_pitch;
        srcU1 += src_pitch_چپ + srcUV_pitch;
        srcU2 += src_pitch_چپ + srcUV_pitch;
        srcV1 += src_pitch_چپ + srcUV_pitch;
        srcV2 += src_pitch_چپ + srcUV_pitch;
        dstY1 += dst_Y_pitch_چپ + dstY_pitch;
        dstY2 += dst_Y_pitch_چپ + dstY_pitch;
        dstU += dst_UV_pitch_چپ;
        dstV += dst_UV_pitch_چپ;
    }

    // Last row
    إذا (y == (ارتفاع - 1)) {
        لكل (x = 0; x < (عرض - 1); x += 2) {
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
        إذا (x == (عرض - 1)) {
            *dstY1 = *srcY1;
            *dstU = *srcU1;
            *dstV = *srcV1;
        }
    }
    أرجع true;
}

#پایان_اگر // SDL_HAVE_YUV

bool SDL_Convert_Pixels_YUV_مقصد_YUV(صحيح عرض, صحيح ارتفاع,
                                  SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ثابت فراغ *src, صحيح src_pitch,
                                  SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, فراغ *dst, صحيح dst_pitch)
{
#اگر_تعریف_شده SDL_HAVE_YUV
    إذا (src_colorspace != dst_colorspace) {
        أرجع SDL_مجموعه_Error("SDL_ConvertPixels_YUV_to_YUV: colorspace conversion not supported");
    }

    إذا (src_format == dst_format) {
        إذا (src == dst) {
            // Nothing to do
            أرجع true;
        }
        أرجع SDL_Convert_Pixels_YUV_مقصد_YUV_Copy(عرض, ارتفاع, src_format, src, src_pitch, dst, dst_pitch);
    }

    إذا (IsPlanar2x2Format(src_format) && IsPlanar2x2Format(dst_format)) {
        أرجع SDL_Convert_Pixels_Planar2x2_مقصد_Planar2x2(عرض, ارتفاع, src_format, src, src_pitch, dst_format, dst, dst_pitch);
    } وإلا إذا (IsPacked4Format(src_format) && IsPacked4Format(dst_format)) {
        أرجع SDL_Convert_Pixels_Packed4_مقصد_Packed4(عرض, ارتفاع, src_format, src, src_pitch, dst_format, dst, dst_pitch);
    } وإلا إذا (IsPlanar2x2Format(src_format) && IsPacked4Format(dst_format)) {
        أرجع SDL_Convert_Pixels_Planar2x2_مقصد_Packed4(عرض, ارتفاع, src_format, src, src_pitch, dst_format, dst, dst_pitch);
    } وإلا إذا (IsPacked4Format(src_format) && IsPlanar2x2Format(dst_format)) {
        أرجع SDL_Convert_Pixels_Packed4_مقصد_Planar2x2(عرض, ارتفاع, src_format, src, src_pitch, dst_format, dst, dst_pitch);
    } وإلا {
        أرجع SDL_مجموعه_Error("SDL_ConvertPixels_YUV_to_YUV: Unsupported YUV conversion: %s -> %s", SDL_GetPixelFormatName(src_format),
                            SDL_GetPixelFormatName(dst_format));
    }
#وإلا
    أرجع SDL_مجموعه_Error("SDL not built with YUV support");
#پایان_اگر
}
