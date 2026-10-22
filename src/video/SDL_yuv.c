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
#include "SDL_internal.h"

#include "SDL_pixels_c.h"
#include "SDL_yuv_c.h"

#include "yuv2rgb/yuv_rgb.h"


static bool IsPlanar1x1Format(SDL_PixelFormat format)
{
    返回 format == SDL_PIXELFORMAT_I444 || format == SDL_PIXELFORMAT_I4FL;
}

static bool IsPlanar2x2Format(SDL_PixelFormat format)
{
    返回 format == SDL_PIXELFORMAT_YV12 ||
           format == SDL_PIXELFORMAT_IYUV ||
           format == SDL_PIXELFORMAT_NV12 ||
           format == SDL_PIXELFORMAT_NV21 ||
           format == SDL_PIXELFORMAT_P010 ||
           format == SDL_PIXELFORMAT_I0FL;
}

static bool IsPacked4Format(Uint32 format)
{
    返回 format == SDL_PIXELFORMAT_YUY2 || format == SDL_PIXELFORMAT_UYVY || format == SDL_PIXELFORMAT_YVYU;
}

/*
 * Calculate YUV size and pitch. Check for overflow.
 * Output 'pitch' that can be used with SDL_ConvertPixels()
 */
bool SDL_CalculateYUVSize(SDL_PixelFormat format, 整数 w, 整数 h, size_t *size, size_t *pitch)
{
    整数 sz_plane = 0, sz_plane_chroma = 0, sz_plane_packed = 0;

    如果 (IsPlanar1x1Format(format)) {
        /* sz_plane == w * h * bpp; */
        size_t s1;
        如果 (!SDL_size_mul_check_overflow(w, h, &s1)) {
            返回 SDL_SetError("width * height would overflow");
        }
        如果 (!SDL_size_mul_check_overflow(s1, SDL_BYTESPERPIXEL(format), &s1)) {
            返回 SDL_SetError("width * height * bpp would overflow");
        }
        sz_plane = (整数)s1;
        sz_plane_chroma = sz_plane;
    } 否则 如果 (IsPlanar2x2Format(format)) {
        {
            /* sz_plane == w * h * bpp; */
            size_t s1;
            如果 (!SDL_size_mul_check_overflow(w, h, &s1)) {
                返回 SDL_SetError("width * height would overflow");
            }
            如果 (!SDL_size_mul_check_overflow(s1, SDL_BYTESPERPIXEL(format), &s1)) {
                返回 SDL_SetError("width * height * bpp would overflow");
            }
            sz_plane = (整数)s1;
        }

        {
            /* sz_plane_chroma == ((w + 1) / 2) * ((h + 1) / 2) * bpp; */
            size_t s1, s2, s3;
            如果 (!SDL_size_add_check_overflow(w, 1, &s1)) {
                返回 SDL_SetError("width + 1 would overflow");
            }
            s1 = s1 / 2;
            如果 (!SDL_size_add_check_overflow(h, 1, &s2)) {
                返回 SDL_SetError("height + 1 would overflow");
            }
            s2 = s2 / 2;
            如果 (!SDL_size_mul_check_overflow(s1, s2, &s3)) {
                返回 SDL_SetError("width * height would overflow");
            }
            如果 (!SDL_size_mul_check_overflow(s3, SDL_BYTESPERPIXEL(format), &s3)) {
                返回 SDL_SetError("width * height * bpp would overflow");
            }
            sz_plane_chroma = (整数)s3;
        }
    } 否则 如果 (IsPacked4Format(format)) {
        /* sz_plane_packed == ((w + 1) / 2) * h; */
        size_t s1, s2;
        如果 (!SDL_size_add_check_overflow(w, 1, &s1)) {
            返回 SDL_SetError("width + 1 would overflow");
        }
        s1 = s1 / 2;
        如果 (!SDL_size_mul_check_overflow(s1, h, &s2)) {
            返回 SDL_SetError("width * height would overflow");
        }
        sz_plane_packed = (整数) s2;
    } 否则 {
        返回 SDL_Unsupported();
    }

    switch (format) {
    case SDL_PIXELFORMAT_YV12: /**< Planar mode: Y + V + U  (3 planes) */
    case SDL_PIXELFORMAT_IYUV: /**< Planar mode: Y + U + V  (3 planes) */
    case SDL_PIXELFORMAT_I444: /**< Planar mode: Y + U + V  (3 planes) */
    case SDL_PIXELFORMAT_I0FL: /**< Planar mode: Y + U + V  (3 planes) */
    case SDL_PIXELFORMAT_I4FL: /**< Planar mode: Y + U + V  (3 planes) */

        如果 (pitch) {
            *pitch = w * SDL_BYTESPERPIXEL(format);
        }

        如果 (size) {
            // dst_size == sz_plane + sz_plane_chroma + sz_plane_chroma;
            size_t s1, s2;
            如果 (!SDL_size_add_check_overflow(sz_plane, sz_plane_chroma, &s1)) {
                返回 SDL_SetError("Y + U would overflow");
            }
            如果 (!SDL_size_add_check_overflow(s1, sz_plane_chroma, &s2)) {
                返回 SDL_SetError("Y + U + V would overflow");
            }
            *size = (整数)s2;
        }
        break;

    case SDL_PIXELFORMAT_YUY2: /**< Packed mode: Y0+U0+Y1+V0 (1 plane) */
    case SDL_PIXELFORMAT_UYVY: /**< Packed mode: U0+Y0+V0+Y1 (1 plane) */
    case SDL_PIXELFORMAT_YVYU: /**< Packed mode: Y0+V0+Y1+U0 (1 plane) */

        如果 (pitch) {
            /* pitch == ((w + 1) / 2) * 4; */
           size_t p1, p2;
           如果 (!SDL_size_add_check_overflow(w, 1, &p1)) {
               返回 SDL_SetError("width + 1 would overflow");
           }
           p1 = p1 / 2;
           如果 (!SDL_size_mul_check_overflow(p1, 4, &p2)) {
               返回 SDL_SetError("width * 4 would overflow");
           }
           *pitch = p2;
        }

        如果 (size) {
            /* dst_size == 4 * sz_plane_packed; */
            size_t s1;
            如果 (!SDL_size_mul_check_overflow(sz_plane_packed, 4, &s1)) {
                返回 SDL_SetError("plane * 4 would overflow");
            }
            *size = (整数) s1;
        }
        break;

    case SDL_PIXELFORMAT_NV12: /**< Planar mode: Y + U/V interleaved  (2 planes) */
    case SDL_PIXELFORMAT_NV21: /**< Planar mode: Y + V/U interleaved  (2 planes) */
    case SDL_PIXELFORMAT_P010: /**< Planar mode: Y + U/V interleaved, 10 bit  (2 planes) */
        如果 (pitch) {
            *pitch = w * SDL_BYTESPERPIXEL(format);
        }

        如果 (size) {
            // dst_size == sz_plane + sz_plane_chroma + sz_plane_chroma;
            size_t s1, s2;
            如果 (!SDL_size_add_check_overflow(sz_plane, sz_plane_chroma, &s1)) {
                返回 SDL_SetError("Y + U would overflow");
            }
            如果 (!SDL_size_add_check_overflow(s1, sz_plane_chroma, &s2)) {
                返回 SDL_SetError("Y + U + V would overflow");
            }
            *size = (整数) s2;
        }
        break;

    default:
        返回 SDL_Unsupported();
    }

    返回 true;
}

#ifdef SDL_HAVE_YUV

static bool GetYUVConversionType(SDL_Colorspace colorspace, 整数 w, 整数 h, 整数 bits_per_pixel, YCbCrType *yuv_type)
{
    如果 (SDL_ISCOLORSPACE_MATRIX_BT601(colorspace)) {
        如果 (SDL_ISCOLORSPACE_LIMITED_RANGE(colorspace)) {
            *yuv_type = YCBCR_601_LIMITED;
        } 否则 {
            *yuv_type = YCBCR_601_FULL;
        }
        返回 true;
    }

    如果 (SDL_ISCOLORSPACE_MATRIX_BT709(colorspace)) {
        如果 (SDL_ISCOLORSPACE_LIMITED_RANGE(colorspace)) {
            *yuv_type = YCBCR_709_LIMITED;
        } 否则 {
            *yuv_type = YCBCR_709_FULL;
        }
        返回 true;
    }

    如果 (SDL_ISCOLORSPACE_MATRIX_BT2020_NCL(colorspace)) {
        如果 (SDL_ISCOLORSPACE_FULL_RANGE(colorspace)) {
            *yuv_type = YCBCR_2020_NCL_FULL;
            返回 true;
        }
    }

    如果 (SDL_COLORSPACEMATRIX(colorspace) == SDL_MATRIX_COEFFICIENTS_UNSPECIFIED) {
        switch (bits_per_pixel) {
        case 8:
            如果 (h <= YUV_SD_THRESHOLD) {
                如果 (SDL_ISCOLORSPACE_LIMITED_RANGE(colorspace)) {
                    *yuv_type = YCBCR_601_LIMITED;
                } 否则 {
                    *yuv_type = YCBCR_601_FULL;
                }
            } 否则 {
                如果 (SDL_ISCOLORSPACE_LIMITED_RANGE(colorspace)) {
                    *yuv_type = YCBCR_709_LIMITED;
                } 否则 {
                    *yuv_type = YCBCR_709_FULL;
                }
            }
			返回 true;
        case 10:
        case 16:
            如果 (SDL_ISCOLORSPACE_FULL_RANGE(colorspace)) {
                *yuv_type = YCBCR_2020_NCL_FULL;
                返回 true;
            }
            break;
        default:
            break;
        }
    }

    返回 SDL_SetError("Unsupported YUV colorspace");
}

static bool GetYUVPlanes(整数 width, 整数 height, SDL_PixelFormat format, const void *yuv, 整数 yuv_pitch,
                         const Uint8 **y, const Uint8 **u, const Uint8 **v, Uint32 *y_stride, Uint32 *uv_stride)
{
    const Uint8 *planes[3] = { NULL, NULL, NULL };
    整数 pitches[3] = { 0, 0, 0 };
    整数 uv_width;

    switch (format) {
    case SDL_PIXELFORMAT_YV12:
    case SDL_PIXELFORMAT_IYUV:
    case SDL_PIXELFORMAT_I0FL:
        pitches[0] = yuv_pitch;
        pitches[1] = ((pitches[0] / SDL_BYTESPERPIXEL(format) + 1) / 2) * SDL_BYTESPERPIXEL(format);
        pitches[2] = pitches[1];
        planes[0] = (const Uint8 *)yuv;
        planes[1] = planes[0] + pitches[0] * height;
        planes[2] = planes[1] + pitches[1] * ((height + 1) / 2);
        break;
    case SDL_PIXELFORMAT_YUY2:
    case SDL_PIXELFORMAT_UYVY:
    case SDL_PIXELFORMAT_YVYU:
        pitches[0] = yuv_pitch;
        planes[0] = (const Uint8 *)yuv;
        break;
    case SDL_PIXELFORMAT_NV12:
    case SDL_PIXELFORMAT_NV21:
        pitches[0] = yuv_pitch;
        pitches[1] = 2 * ((pitches[0] + 1) / 2);
        planes[0] = (const Uint8 *)yuv;
        planes[1] = planes[0] + pitches[0] * height;
        break;
    case SDL_PIXELFORMAT_P010:
        pitches[0] = yuv_pitch;
        uv_width = ((width + 1) / 2) * 2;
        pitches[1] = SDL_max(pitches[0], (整数)(uv_width * sizeof(Uint16)));
        planes[0] = (const Uint8 *)yuv;
        planes[1] = planes[0] + pitches[0] * height;
        break;
    case SDL_PIXELFORMAT_I444:
    case SDL_PIXELFORMAT_I4FL:
        pitches[0] = yuv_pitch;
        pitches[1] = pitches[0];
        pitches[2] = pitches[1];
        planes[0] = (const Uint8 *)yuv;
        planes[1] = planes[0] + pitches[0] * height;
        planes[2] = planes[1] + pitches[1] * height;
        break;
    default:
        返回 SDL_SetError("GetYUVPlanes(): Unsupported YUV format: %s", SDL_GetPixelFormatName(format));
    }

    switch (format) {
    case SDL_PIXELFORMAT_YV12:
        *y = planes[0];
        *y_stride = pitches[0];
        *v = planes[1];
        *u = planes[2];
        *uv_stride = pitches[1];
        break;
    case SDL_PIXELFORMAT_IYUV:
    case SDL_PIXELFORMAT_I444:
    case SDL_PIXELFORMAT_I0FL:
    case SDL_PIXELFORMAT_I4FL:
        *y = planes[0];
        *y_stride = pitches[0];
        *v = planes[2];
        *u = planes[1];
        *uv_stride = pitches[1];
        break;
    case SDL_PIXELFORMAT_YUY2:
        *y = planes[0];
        *y_stride = pitches[0];
        *v = *y + 3;
        *u = *y + 1;
        *uv_stride = pitches[0];
        break;
    case SDL_PIXELFORMAT_UYVY:
        *y = planes[0] + 1;
        *y_stride = pitches[0];
        *v = *y + 1;
        *u = *y - 1;
        *uv_stride = pitches[0];
        break;
    case SDL_PIXELFORMAT_YVYU:
        *y = planes[0];
        *y_stride = pitches[0];
        *v = *y + 1;
        *u = *y + 3;
        *uv_stride = pitches[0];
        break;
    case SDL_PIXELFORMAT_NV12:
        *y = planes[0];
        *y_stride = pitches[0];
        *u = planes[1];
        *v = *u + 1;
        *uv_stride = pitches[1];
        break;
    case SDL_PIXELFORMAT_NV21:
        *y = planes[0];
        *y_stride = pitches[0];
        *v = planes[1];
        *u = *v + 1;
        *uv_stride = pitches[1];
        break;
    case SDL_PIXELFORMAT_P010:
        *y = planes[0];
        *y_stride = pitches[0];
        *u = planes[1];
        *v = *u + sizeof(Uint16);
        *uv_stride = pitches[1];
        break;
    default:
        // Should have caught this above
        返回 SDL_SetError("GetYUVPlanes[2]: Unsupported YUV format: %s", SDL_GetPixelFormatName(format));
    }
    返回 true;
}

#ifdef SDL_SSE2_INTRINSICS
static bool SDL_TARGETING("sse2") yuv_rgb_sse(
    SDL_PixelFormat src_format, SDL_PixelFormat dst_format,
    Uint32 width, Uint32 height,
    const Uint8 *y, const Uint8 *u, const Uint8 *v, Uint32 y_stride, Uint32 uv_stride,
    Uint8 *rgb, Uint32 rgb_stride,
    YCbCrType yuv_type)
{
    如果 (!SDL_HasSSE2()) {
        返回 false;
    }

    如果 (src_format == SDL_PIXELFORMAT_YV12 ||
        src_format == SDL_PIXELFORMAT_IYUV) {

        switch (dst_format) {
        case SDL_PIXELFORMAT_RGB565:
            yuv420_rgb565_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            返回 true;
        case SDL_PIXELFORMAT_RGB24:
            yuv420_rgb24_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            返回 true;
        case SDL_PIXELFORMAT_RGBX8888:
        case SDL_PIXELFORMAT_RGBA8888:
            yuv420_rgba_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            返回 true;
        case SDL_PIXELFORMAT_BGRX8888:
        case SDL_PIXELFORMAT_BGRA8888:
            yuv420_bgra_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            返回 true;
        case SDL_PIXELFORMAT_XRGB8888:
        case SDL_PIXELFORMAT_ARGB8888:
            yuv420_argb_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            返回 true;
        case SDL_PIXELFORMAT_XBGR8888:
        case SDL_PIXELFORMAT_ABGR8888:
            yuv420_abgr_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            返回 true;
        default:
            break;
        }
    }

    如果 (src_format == SDL_PIXELFORMAT_YUY2 ||
        src_format == SDL_PIXELFORMAT_UYVY ||
        src_format == SDL_PIXELFORMAT_YVYU) {

        switch (dst_format) {
        case SDL_PIXELFORMAT_RGB565:
            yuv422_rgb565_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            返回 true;
        case SDL_PIXELFORMAT_RGB24:
            yuv422_rgb24_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            返回 true;
        case SDL_PIXELFORMAT_RGBX8888:
        case SDL_PIXELFORMAT_RGBA8888:
            yuv422_rgba_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            返回 true;
        case SDL_PIXELFORMAT_BGRX8888:
        case SDL_PIXELFORMAT_BGRA8888:
            yuv422_bgra_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            返回 true;
        case SDL_PIXELFORMAT_XRGB8888:
        case SDL_PIXELFORMAT_ARGB8888:
            yuv422_argb_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            返回 true;
        case SDL_PIXELFORMAT_XBGR8888:
        case SDL_PIXELFORMAT_ABGR8888:
            yuv422_abgr_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            返回 true;
        default:
            break;
        }
    }

    如果 (src_format == SDL_PIXELFORMAT_NV12 ||
        src_format == SDL_PIXELFORMAT_NV21) {

        switch (dst_format) {
        case SDL_PIXELFORMAT_RGB565:
            yuvnv12_rgb565_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            返回 true;
        case SDL_PIXELFORMAT_RGB24:
            yuvnv12_rgb24_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            返回 true;
        case SDL_PIXELFORMAT_RGBX8888:
        case SDL_PIXELFORMAT_RGBA8888:
            yuvnv12_rgba_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            返回 true;
        case SDL_PIXELFORMAT_BGRX8888:
        case SDL_PIXELFORMAT_BGRA8888:
            yuvnv12_bgra_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            返回 true;
        case SDL_PIXELFORMAT_XRGB8888:
        case SDL_PIXELFORMAT_ARGB8888:
            yuvnv12_argb_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            返回 true;
        case SDL_PIXELFORMAT_XBGR8888:
        case SDL_PIXELFORMAT_ABGR8888:
            yuvnv12_abgr_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            返回 true;
        default:
            break;
        }
    }
    返回 false;
}
#否则
static bool yuv_rgb_sse(
    SDL_PixelFormat src_format, SDL_PixelFormat dst_format,
    Uint32 width, Uint32 height,
    const Uint8 *y, const Uint8 *u, const Uint8 *v, Uint32 y_stride, Uint32 uv_stride,
    Uint8 *rgb, Uint32 rgb_stride,
    YCbCrType yuv_type)
{
    返回 false;
}
#endif

#ifdef SDL_LSX_INTRINSICS
static bool yuv_rgb_lsx(
    SDL_PixelFormat src_format, SDL_PixelFormat dst_format,
    Uint32 width, Uint32 height,
    const Uint8 *y, const Uint8 *u, const Uint8 *v, Uint32 y_stride, Uint32 uv_stride,
    Uint8 *rgb, Uint32 rgb_stride,
    YCbCrType yuv_type)
{
    如果 (!SDL_HasLSX()) {
        返回 false;
    }
    如果 (src_format == SDL_PIXELFORMAT_YV12 ||
        src_format == SDL_PIXELFORMAT_IYUV) {

        switch (dst_format) {
        case SDL_PIXELFORMAT_RGB24:
            yuv420_rgb24_lsx(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            返回 true;
        case SDL_PIXELFORMAT_RGBX8888:
        case SDL_PIXELFORMAT_RGBA8888:
            yuv420_rgba_lsx(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            返回 true;
        case SDL_PIXELFORMAT_BGRX8888:
        case SDL_PIXELFORMAT_BGRA8888:
            yuv420_bgra_lsx(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            返回 true;
        case SDL_PIXELFORMAT_XRGB8888:
        case SDL_PIXELFORMAT_ARGB8888:
            yuv420_argb_lsx(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            返回 true;
        case SDL_PIXELFORMAT_XBGR8888:
        case SDL_PIXELFORMAT_ABGR8888:
            yuv420_abgr_lsx(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            返回 true;
        default:
            break;
        }
    }
    返回 false;
}
#否则
static bool yuv_rgb_lsx(
    SDL_PixelFormat src_format, SDL_PixelFormat dst_format,
    Uint32 width, Uint32 height,
    const Uint8 *y, const Uint8 *u, const Uint8 *v, Uint32 y_stride, Uint32 uv_stride,
    Uint8 *rgb, Uint32 rgb_stride,
    YCbCrType yuv_type)
{
    返回 false;
}
#endif

static bool yuv_rgb_std(
    SDL_PixelFormat src_format, SDL_PixelFormat dst_format,
    Uint32 width, Uint32 height,
    const Uint8 *y, const Uint8 *u, const Uint8 *v, Uint32 y_stride, Uint32 uv_stride,
    Uint8 *rgb, Uint32 rgb_stride,
    YCbCrType yuv_type)
{
    如果 (src_format == SDL_PIXELFORMAT_YV12 ||
        src_format == SDL_PIXELFORMAT_IYUV) {

        switch (dst_format) {
        case SDL_PIXELFORMAT_RGB565:
            yuv420_rgb565_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            返回 true;
        case SDL_PIXELFORMAT_RGB24:
            yuv420_rgb24_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            返回 true;
        case SDL_PIXELFORMAT_RGBX8888:
        case SDL_PIXELFORMAT_RGBA8888:
            yuv420_rgba_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            返回 true;
        case SDL_PIXELFORMAT_BGRX8888:
        case SDL_PIXELFORMAT_BGRA8888:
            yuv420_bgra_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            返回 true;
        case SDL_PIXELFORMAT_XRGB8888:
        case SDL_PIXELFORMAT_ARGB8888:
            yuv420_argb_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            返回 true;
        case SDL_PIXELFORMAT_XBGR8888:
        case SDL_PIXELFORMAT_ABGR8888:
            yuv420_abgr_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            返回 true;
        default:
            break;
        }
    }

    如果 (src_format == SDL_PIXELFORMAT_I444) {

        switch (dst_format) {
        case SDL_PIXELFORMAT_RGBX8888:
        case SDL_PIXELFORMAT_RGBA8888:
            yuv444_rgba_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            返回 true;
        case SDL_PIXELFORMAT_BGRX8888:
        case SDL_PIXELFORMAT_BGRA8888:
            yuv444_bgra_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            返回 true;
        case SDL_PIXELFORMAT_XRGB8888:
        case SDL_PIXELFORMAT_ARGB8888:
            yuv444_argb_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            返回 true;
        case SDL_PIXELFORMAT_XBGR8888:
        case SDL_PIXELFORMAT_ABGR8888:
            yuv444_abgr_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            返回 true;
        default:
            break;
        }
    }

    如果 (src_format == SDL_PIXELFORMAT_YUY2 ||
        src_format == SDL_PIXELFORMAT_UYVY ||
        src_format == SDL_PIXELFORMAT_YVYU) {

        switch (dst_format) {
        case SDL_PIXELFORMAT_RGB565:
            yuv422_rgb565_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            返回 true;
        case SDL_PIXELFORMAT_RGB24:
            yuv422_rgb24_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            返回 true;
        case SDL_PIXELFORMAT_RGBX8888:
        case SDL_PIXELFORMAT_RGBA8888:
            yuv422_rgba_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            返回 true;
        case SDL_PIXELFORMAT_BGRX8888:
        case SDL_PIXELFORMAT_BGRA8888:
            yuv422_bgra_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            返回 true;
        case SDL_PIXELFORMAT_XRGB8888:
        case SDL_PIXELFORMAT_ARGB8888:
            yuv422_argb_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            返回 true;
        case SDL_PIXELFORMAT_XBGR8888:
        case SDL_PIXELFORMAT_ABGR8888:
            yuv422_abgr_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            返回 true;
        default:
            break;
        }
    }

    如果 (src_format == SDL_PIXELFORMAT_NV12 ||
        src_format == SDL_PIXELFORMAT_NV21) {

        switch (dst_format) {
        case SDL_PIXELFORMAT_RGB565:
            yuvnv12_rgb565_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            返回 true;
        case SDL_PIXELFORMAT_RGB24:
            yuvnv12_rgb24_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            返回 true;
        case SDL_PIXELFORMAT_RGBX8888:
        case SDL_PIXELFORMAT_RGBA8888:
            yuvnv12_rgba_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            返回 true;
        case SDL_PIXELFORMAT_BGRX8888:
        case SDL_PIXELFORMAT_BGRA8888:
            yuvnv12_bgra_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            返回 true;
        case SDL_PIXELFORMAT_XRGB8888:
        case SDL_PIXELFORMAT_ARGB8888:
            yuvnv12_argb_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            返回 true;
        case SDL_PIXELFORMAT_XBGR8888:
        case SDL_PIXELFORMAT_ABGR8888:
            yuvnv12_abgr_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            返回 true;
        default:
            break;
        }
    }

    如果 (src_format == SDL_PIXELFORMAT_P010) {
        switch (dst_format) {
        case SDL_PIXELFORMAT_XBGR2101010:
            yuvp010_xbgr2101010_std(width, height, (const uint16_t *)y, (const uint16_t *)u, (const uint16_t *)v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            返回 true;
        default:
            break;
        }
    }

    如果 (src_format == SDL_PIXELFORMAT_I0FL) {
        switch (dst_format) {
        case SDL_PIXELFORMAT_RGB48:
            yuvi0fl_rgb48_std(width, height, (const uint16_t *)y, (const uint16_t *)u, (const uint16_t *)v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            返回 true;
        default:
            break;
        }
    }

    如果 (src_format == SDL_PIXELFORMAT_I4FL) {
        switch (dst_format) {
        case SDL_PIXELFORMAT_RGB48:
            yuvi4fl_rgb48_std(width, height, (const uint16_t *)y, (const uint16_t *)u, (const uint16_t *)v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            返回 true;
        default:
            break;
        }
    }
    返回 false;
}

bool SDL_ConvertPixels_YUV_to_RGB(整数 width, 整数 height,
                                  SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, const void *src, 整数 src_pitch,
                                  SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, void *dst, 整数 dst_pitch)
{
    const Uint8 *y = NULL;
    const Uint8 *u = NULL;
    const Uint8 *v = NULL;
    Uint32 y_stride = 0;
    Uint32 uv_stride = 0;
    YCbCrType yuv_type = YCBCR_601_LIMITED;

    如果 (!GetYUVPlanes(width, height, src_format, src, src_pitch, &y, &u, &v, &y_stride, &uv_stride)) {
        返回 false;
    }

    如果 (!GetYUVConversionType(src_colorspace, width, height, 8, &yuv_type)) {
        返回 false;
    }

    如果 (yuv_rgb_sse(src_format, dst_format, width, height, y, u, v, y_stride, uv_stride, (Uint8 *)dst, dst_pitch, yuv_type)) {
        返回 true;
    }

    如果 (yuv_rgb_lsx(src_format, dst_format, width, height, y, u, v, y_stride, uv_stride, (Uint8 *)dst, dst_pitch, yuv_type)) {
        返回 true;
    }

    如果 (yuv_rgb_std(src_format, dst_format, width, height, y, u, v, y_stride, uv_stride, (Uint8 *)dst, dst_pitch, yuv_type)) {
        返回 true;
    }

    // No fast path for the RGB format, instead convert using an intermediate buffer
    如果 (src_format == SDL_PIXELFORMAT_P010 && dst_format != SDL_PIXELFORMAT_XBGR2101010) {
        bool result;
        void *tmp;
        整数 tmp_pitch = (width * sizeof(Uint32));

        tmp = SDL_malloc((size_t)tmp_pitch * height);
        如果 (!tmp) {
            返回 false;
        }

        // convert src/src_format to tmp/XBGR2101010
        result = SDL_ConvertPixels_YUV_to_RGB(width, height, src_format, src_colorspace, src_properties, src, src_pitch, SDL_PIXELFORMAT_XBGR2101010, src_colorspace, src_properties, tmp, tmp_pitch);
        如果 (!result) {
            SDL_free(tmp);
            返回 false;
        }

        // convert tmp/XBGR2101010 to dst/RGB
        result = SDL_ConvertPixelsAndColorspace(width, height, SDL_PIXELFORMAT_XBGR2101010, src_colorspace, src_properties, tmp, tmp_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
        SDL_free(tmp);
        返回 result;
    }

    如果 ((src_format == SDL_PIXELFORMAT_I0FL || src_format == SDL_PIXELFORMAT_I4FL) && dst_format != SDL_PIXELFORMAT_RGB48) {
        bool result;
        void *tmp;
        整数 tmp_pitch = (width * 3 * sizeof(Uint16));

        tmp = SDL_malloc((size_t)tmp_pitch * height);
        如果 (!tmp) {
            返回 false;
        }

        // convert src/src_format to tmp/RGB48
        result = SDL_ConvertPixels_YUV_to_RGB(width, height, src_format, src_colorspace, src_properties, src, src_pitch, SDL_PIXELFORMAT_RGB48, src_colorspace, src_properties, tmp, tmp_pitch);
        如果 (!result) {
            SDL_free(tmp);
            返回 false;
        }

        // convert tmp/RGB48 to dst/RGB
        result = SDL_ConvertPixelsAndColorspace(width, height, SDL_PIXELFORMAT_RGB48, src_colorspace, src_properties, tmp, tmp_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
        SDL_free(tmp);
        返回 result;
    }

    如果 (dst_format != SDL_PIXELFORMAT_ARGB8888) {
        bool result;
        void *tmp;
        整数 tmp_pitch = (width * sizeof(Uint32));

        tmp = SDL_malloc((size_t)tmp_pitch * height);
        如果 (!tmp) {
            返回 false;
        }

        // convert src/src_format to tmp/ARGB8888
        result = SDL_ConvertPixels_YUV_to_RGB(width, height, src_format, src_colorspace, src_properties, src, src_pitch, SDL_PIXELFORMAT_ARGB8888, SDL_COLORSPACE_SRGB, 0, tmp, tmp_pitch);
        如果 (!result) {
            SDL_free(tmp);
            返回 false;
        }

        // convert tmp/ARGB8888 to dst/RGB
        result = SDL_ConvertPixelsAndColorspace(width, height, SDL_PIXELFORMAT_ARGB8888, SDL_COLORSPACE_SRGB, 0, tmp, tmp_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
        SDL_free(tmp);
        返回 result;
    }

    返回 SDL_SetError("Unsupported YUV conversion");
}

struct RGB2YUVFactors
{
    整数 y_offset;
    float y[3]; // Rfactor, Gfactor, Bfactor
    float u[3]; // Rfactor, Gfactor, Bfactor
    float v[3]; // Rfactor, Gfactor, Bfactor
};

static struct RGB2YUVFactors RGB2YUVFactorTables[] = {
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

static bool SDL_ConvertPixels_XRGB8888_to_YUV(整数 width, 整数 height, const void *src, 整数 src_pitch, SDL_PixelFormat dst_format, void *dst, 整数 dst_pitch, YCbCrType yuv_type)
{
    const 整数 src_pitch_x_2 = src_pitch * 2;
    const 整数 height_half = height / 2;
    const 整数 height_remainder = (height & 0x1);
    const 整数 width_half = width / 2;
    const 整数 width_remainder = (width & 0x1);
    整数 i, j;

    const struct RGB2YUVFactors *cvt = &RGB2YUVFactorTables[yuv_type];

#define MAKE_Y(r, g, b) (Uint8)SDL_clamp(((整数)(cvt->y[0] * (r) + cvt->y[1] * (g) + cvt->y[2] * (b) + 0.5f) + cvt->y_offset), 0, 255)
#define MAKE_U(r, g, b) (Uint8)SDL_clamp(((整数)(cvt->u[0] * (r) + cvt->u[1] * (g) + cvt->u[2] * (b) + 0.5f) + 128), 0, 255)
#define MAKE_V(r, g, b) (Uint8)SDL_clamp(((整数)(cvt->v[0] * (r) + cvt->v[1] * (g) + cvt->v[2] * (b) + 0.5f) + 128), 0, 255)

#define READ_2x2_PIXELS                                                                                     \
    const Uint32 p1 = ((const Uint32 *)curr_row)[2 * i];                                                    \
    const Uint32 p2 = ((const Uint32 *)curr_row)[2 * i + 1];                                                \
    const Uint32 p3 = ((const Uint32 *)next_row)[2 * i];                                                    \
    const Uint32 p4 = ((const Uint32 *)next_row)[2 * i + 1];                                                \
    const Uint32 r = ((p1 & 0x00ff0000) + (p2 & 0x00ff0000) + (p3 & 0x00ff0000) + (p4 & 0x00ff0000)) >> 18; \
    const Uint32 g = ((p1 & 0x0000ff00) + (p2 & 0x0000ff00) + (p3 & 0x0000ff00) + (p4 & 0x0000ff00)) >> 10; \
    const Uint32 b = ((p1 & 0x000000ff) + (p2 & 0x000000ff) + (p3 & 0x000000ff) + (p4 & 0x000000ff)) >> 2

#define READ_2x1_PIXELS                                             \
    const Uint32 p1 = ((const Uint32 *)curr_row)[2 * i];            \
    const Uint32 p2 = ((const Uint32 *)next_row)[2 * i];            \
    const Uint32 r = ((p1 & 0x00ff0000) + (p2 & 0x00ff0000)) >> 17; \
    const Uint32 g = ((p1 & 0x0000ff00) + (p2 & 0x0000ff00)) >> 9;  \
    const Uint32 b = ((p1 & 0x000000ff) + (p2 & 0x000000ff)) >> 1

#define READ_1x2_PIXELS                                             \
    const Uint32 p1 = ((const Uint32 *)curr_row)[2 * i];            \
    const Uint32 p2 = ((const Uint32 *)curr_row)[2 * i + 1];        \
    const Uint32 r = ((p1 & 0x00ff0000) + (p2 & 0x00ff0000)) >> 17; \
    const Uint32 g = ((p1 & 0x0000ff00) + (p2 & 0x0000ff00)) >> 9;  \
    const Uint32 b = ((p1 & 0x000000ff) + (p2 & 0x000000ff)) >> 1

#define READ_1x1_PIXEL                                  \
    const Uint32 p = ((const Uint32 *)curr_row)[2 * i]; \
    const Uint32 r = (p & 0x00ff0000) >> 16;            \
    const Uint32 g = (p & 0x0000ff00) >> 8;             \
    const Uint32 b = (p & 0x000000ff)

#define READ_TWO_RGB_PIXELS                                  \
    const Uint32 p = ((const Uint32 *)curr_row)[2 * i];      \
    const Uint32 r = (p & 0x00ff0000) >> 16;                 \
    const Uint32 g = (p & 0x0000ff00) >> 8;                  \
    const Uint32 b = (p & 0x000000ff);                       \
    const Uint32 p1 = ((const Uint32 *)curr_row)[2 * i + 1]; \
    const Uint32 r1 = (p1 & 0x00ff0000) >> 16;               \
    const Uint32 g1 = (p1 & 0x0000ff00) >> 8;                \
    const Uint32 b1 = (p1 & 0x000000ff);                     \
    const Uint32 R = (r + r1) / 2;                           \
    const Uint32 G = (g + g1) / 2;                           \
    const Uint32 B = (b + b1) / 2

#define READ_ONE_RGB_PIXEL READ_1x1_PIXEL

    switch (dst_format) {
    case SDL_PIXELFORMAT_YV12:
    case SDL_PIXELFORMAT_IYUV:
    case SDL_PIXELFORMAT_I444:
    case SDL_PIXELFORMAT_NV12:
    case SDL_PIXELFORMAT_NV21:
    {
        const Uint8 *curr_row, *next_row;

        Uint8 *plane_y;
        Uint8 *plane_u;
        Uint8 *plane_v;
        Uint8 *plane_interleaved_uv;
        Uint32 y_stride, uv_stride, y_skip, uv_skip;

        如果 (!GetYUVPlanes(width, height, dst_format, dst, dst_pitch,
                          (const Uint8 **)&plane_y, (const Uint8 **)&plane_u, (const Uint8 **)&plane_v,
                          &y_stride, &uv_stride)) {
            返回 false;
        }

        plane_interleaved_uv = (plane_y + height * y_stride);
        y_skip = (y_stride - width);

        curr_row = (const Uint8 *)src;

        // Write Y plane
        为 (j = 0; j < height; j++) {
            为 (i = 0; i < width; i++) {
                const Uint32 p1 = ((const Uint32 *)curr_row)[i];
                const Uint32 r = (p1 & 0x00ff0000) >> 16;
                const Uint32 g = (p1 & 0x0000ff00) >> 8;
                const Uint32 b = (p1 & 0x000000ff);
                *plane_y++ = MAKE_Y(r, g, b);
            }
            plane_y += y_skip;
            curr_row += src_pitch;
        }

        curr_row = (const Uint8 *)src;
        next_row = (const Uint8 *)src;
        next_row += src_pitch;

        如果 (dst_format == SDL_PIXELFORMAT_YV12 || dst_format == SDL_PIXELFORMAT_IYUV) {
            // Write UV planes, not interleaved
            uv_skip = (uv_stride - (width + 1) / 2);
            为 (j = 0; j < height_half; j++) {
                为 (i = 0; i < width_half; i++) {
                    READ_2x2_PIXELS;
                    *plane_u++ = MAKE_U(r, g, b);
                    *plane_v++ = MAKE_V(r, g, b);
                }
                如果 (width_remainder) {
                    READ_2x1_PIXELS;
                    *plane_u++ = MAKE_U(r, g, b);
                    *plane_v++ = MAKE_V(r, g, b);
                }
                plane_u += uv_skip;
                plane_v += uv_skip;
                curr_row += src_pitch_x_2;
                next_row += src_pitch_x_2;
            }
            如果 (height_remainder) {
                为 (i = 0; i < width_half; i++) {
                    READ_1x2_PIXELS;
                    *plane_u++ = MAKE_U(r, g, b);
                    *plane_v++ = MAKE_V(r, g, b);
                }
                如果 (width_remainder) {
                    READ_1x1_PIXEL;
                    *plane_u++ = MAKE_U(r, g, b);
                    *plane_v++ = MAKE_V(r, g, b);
                }
                plane_u += uv_skip;
                plane_v += uv_skip;
            }
        } 否则 如果 (dst_format == SDL_PIXELFORMAT_I444) {
            // Write UV planes, not interleaved
            uv_skip = (uv_stride - width);
            为 (j = 0; j < height; j++) {
                为 (i = 0; i < width; i++) {
                    const Uint32 p1 = ((const Uint32 *)curr_row)[i];
                    const Uint32 r = (p1 & 0x00ff0000) >> 16;
                    const Uint32 g = (p1 & 0x0000ff00) >> 8;
                    const Uint32 b = (p1 & 0x000000ff);
                    *plane_u++ = MAKE_U(r, g, b);
                    *plane_v++ = MAKE_V(r, g, b);
                }
                plane_u += uv_skip;
                plane_v += uv_skip;
                curr_row += src_pitch;
            }
        } 否则 如果 (dst_format == SDL_PIXELFORMAT_NV12) {
            uv_skip = (uv_stride - ((width + 1) / 2) * 2);
            为 (j = 0; j < height_half; j++) {
                为 (i = 0; i < width_half; i++) {
                    READ_2x2_PIXELS;
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                }
                如果 (width_remainder) {
                    READ_2x1_PIXELS;
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                }
                plane_interleaved_uv += uv_skip;
                curr_row += src_pitch_x_2;
                next_row += src_pitch_x_2;
            }
            如果 (height_remainder) {
                为 (i = 0; i < width_half; i++) {
                    READ_1x2_PIXELS;
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                }
                如果 (width_remainder) {
                    READ_1x1_PIXEL;
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                }
            }
        } 否则 /* dst_format == SDL_PIXELFORMAT_NV21 */ {
            uv_skip = (uv_stride - ((width + 1) / 2) * 2);
            为 (j = 0; j < height_half; j++) {
                为 (i = 0; i < width_half; i++) {
                    READ_2x2_PIXELS;
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                }
                如果 (width_remainder) {
                    READ_2x1_PIXELS;
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                }
                plane_interleaved_uv += uv_skip;
                curr_row += src_pitch_x_2;
                next_row += src_pitch_x_2;
            }
            如果 (height_remainder) {
                为 (i = 0; i < width_half; i++) {
                    READ_1x2_PIXELS;
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                }
                如果 (width_remainder) {
                    READ_1x1_PIXEL;
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                }
            }
        }
    } break;

    case SDL_PIXELFORMAT_YUY2:
    case SDL_PIXELFORMAT_UYVY:
    case SDL_PIXELFORMAT_YVYU:
    {
        const Uint8 *curr_row = (const Uint8 *)src;
        Uint8 *plane = (Uint8 *)dst;
        const 整数 row_size = (4 * ((width + 1) / 2));
        整数 plane_skip;

        如果 (dst_pitch < row_size) {
            返回 SDL_SetError("Destination pitch is too small, expected at least %d", row_size);
        }
        plane_skip = (dst_pitch - row_size);

        // Write YUV plane, packed
        如果 (dst_format == SDL_PIXELFORMAT_YUY2) {
            为 (j = 0; j < height; j++) {
                为 (i = 0; i < width_half; i++) {
                    READ_TWO_RGB_PIXELS;
                    // Y U Y1 V
                    *plane++ = MAKE_Y(r, g, b);
                    *plane++ = MAKE_U(R, G, B);
                    *plane++ = MAKE_Y(r1, g1, b1);
                    *plane++ = MAKE_V(R, G, B);
                }
                如果 (width_remainder) {
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
        } 否则 如果 (dst_format == SDL_PIXELFORMAT_UYVY) {
            为 (j = 0; j < height; j++) {
                为 (i = 0; i < width_half; i++) {
                    READ_TWO_RGB_PIXELS;
                    // U Y V Y1
                    *plane++ = MAKE_U(R, G, B);
                    *plane++ = MAKE_Y(r, g, b);
                    *plane++ = MAKE_V(R, G, B);
                    *plane++ = MAKE_Y(r1, g1, b1);
                }
                如果 (width_remainder) {
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
        } 否则 如果 (dst_format == SDL_PIXELFORMAT_YVYU) {
            为 (j = 0; j < height; j++) {
                为 (i = 0; i < width_half; i++) {
                    READ_TWO_RGB_PIXELS;
                    // Y V Y1 U
                    *plane++ = MAKE_Y(r, g, b);
                    *plane++ = MAKE_V(R, G, B);
                    *plane++ = MAKE_Y(r1, g1, b1);
                    *plane++ = MAKE_U(R, G, B);
                }
                如果 (width_remainder) {
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
    } break;

    default:
        返回 SDL_SetError("Unsupported YUV destination format: %s", SDL_GetPixelFormatName(dst_format));
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
    返回 true;
}

static bool SDL_ConvertPixels_XBGR2101010_to_P010(整数 width, 整数 height, const void *src, 整数 src_pitch, SDL_PixelFormat dst_format, void *dst, 整数 dst_pitch, YCbCrType yuv_type)
{
    const 整数 src_pitch_x_2 = src_pitch * 2;
    const 整数 height_half = height / 2;
    const 整数 height_remainder = (height & 0x1);
    const 整数 width_half = width / 2;
    const 整数 width_remainder = (width & 0x1);
    整数 i, j;

    const struct RGB2YUVFactors *cvt = &RGB2YUVFactorTables[yuv_type];

#define MAKE_Y(r, g, b) (Uint16)(((整数)(cvt->y[0] * (r) + cvt->y[1] * (g) + cvt->y[2] * (b) + 0.5f) + cvt->y_offset) << 6)
#define MAKE_U(r, g, b) (Uint16)(((整数)(cvt->u[0] * (r) + cvt->u[1] * (g) + cvt->u[2] * (b) + 0.5f) + 512) << 6)
#define MAKE_V(r, g, b) (Uint16)(((整数)(cvt->v[0] * (r) + cvt->v[1] * (g) + cvt->v[2] * (b) + 0.5f) + 512) << 6)

#define READ_2x2_PIXELS                                                                                     \
    const Uint32 p1 = ((const Uint32 *)curr_row)[2 * i];                                                    \
    const Uint32 p2 = ((const Uint32 *)curr_row)[2 * i + 1];                                                \
    const Uint32 p3 = ((const Uint32 *)next_row)[2 * i];                                                    \
    const Uint32 p4 = ((const Uint32 *)next_row)[2 * i + 1];                                                \
    const Uint32 r = ((p1 & 0x000003ff) + (p2 & 0x000003ff) + (p3 & 0x000003ff) + (p4 & 0x000003ff)) >> 2;  \
    const Uint32 g = ((p1 & 0x000ffc00) + (p2 & 0x000ffc00) + (p3 & 0x000ffc00) + (p4 & 0x000ffc00)) >> 12; \
    const Uint32 b = ((p1 & 0x3ff00000) + (p2 & 0x3ff00000) + (p3 & 0x3ff00000) + (p4 & 0x3ff00000)) >> 22

#define READ_2x1_PIXELS                                             \
    const Uint32 p1 = ((const Uint32 *)curr_row)[2 * i];            \
    const Uint32 p2 = ((const Uint32 *)next_row)[2 * i];            \
    const Uint32 r = ((p1 & 0x000003ff) + (p2 & 0x000003ff)) >> 1;  \
    const Uint32 g = ((p1 & 0x000ffc00) + (p2 & 0x000ffc00)) >> 11; \
    const Uint32 b = ((p1 & 0x3ff00000) + (p2 & 0x3ff00000)) >> 21

#define READ_1x2_PIXELS                                             \
    const Uint32 p1 = ((const Uint32 *)curr_row)[2 * i];            \
    const Uint32 p2 = ((const Uint32 *)curr_row)[2 * i + 1];        \
    const Uint32 r = ((p1 & 0x000003ff) + (p2 & 0x000003ff)) >> 1;  \
    const Uint32 g = ((p1 & 0x000ffc00) + (p2 & 0x000ffc00)) >> 11; \
    const Uint32 b = ((p1 & 0x3ff00000) + (p2 & 0x3ff00000)) >> 21

#define READ_1x1_PIXEL                                  \
    const Uint32 p = ((const Uint32 *)curr_row)[2 * i]; \
    const Uint32 r = (p & 0x000003ff);                  \
    const Uint32 g = (p & 0x000ffc00) >> 10;            \
    const Uint32 b = (p & 0x3ff00000) >> 20

    const Uint8 *curr_row, *next_row;

    Uint16 *plane_y;
    Uint16 *plane_u;
    Uint16 *plane_v;
    Uint16 *plane_interleaved_uv;
    Uint32 y_stride, uv_stride, y_skip, uv_skip;

    如果 (!GetYUVPlanes(width, height, dst_format, dst, dst_pitch,
                      (const Uint8 **)&plane_y, (const Uint8 **)&plane_u, (const Uint8 **)&plane_v,
                      &y_stride, &uv_stride)) {
        返回 false;
    }

    y_stride /= sizeof(Uint16);
    uv_stride /= sizeof(Uint16);

    plane_interleaved_uv = (plane_y + height * y_stride);
    y_skip = (y_stride - width);

    curr_row = (const Uint8 *)src;

    // Write Y plane
    为 (j = 0; j < height; j++) {
        为 (i = 0; i < width; i++) {
            const Uint32 p1 = ((const Uint32 *)curr_row)[i];
            const Uint32 r = (p1 >>  0) & 0x03ff;
            const Uint32 g = (p1 >> 10) & 0x03ff;
            const Uint32 b = (p1 >> 20) & 0x03ff;
            *plane_y++ = MAKE_Y(r, g, b);
        }
        plane_y += y_skip;
        curr_row += src_pitch;
    }

    curr_row = (const Uint8 *)src;
    next_row = (const Uint8 *)src;
    next_row += src_pitch;

    uv_skip = (uv_stride - ((width + 1) / 2) * 2);
    为 (j = 0; j < height_half; j++) {
        为 (i = 0; i < width_half; i++) {
            READ_2x2_PIXELS;
            *plane_interleaved_uv++ = MAKE_U(r, g, b);
            *plane_interleaved_uv++ = MAKE_V(r, g, b);
        }
        如果 (width_remainder) {
            READ_2x1_PIXELS;
            *plane_interleaved_uv++ = MAKE_U(r, g, b);
            *plane_interleaved_uv++ = MAKE_V(r, g, b);
        }
        plane_interleaved_uv += uv_skip;
        curr_row += src_pitch_x_2;
        next_row += src_pitch_x_2;
    }
    如果 (height_remainder) {
        为 (i = 0; i < width_half; i++) {
            READ_1x2_PIXELS;
            *plane_interleaved_uv++ = MAKE_U(r, g, b);
            *plane_interleaved_uv++ = MAKE_V(r, g, b);
        }
        如果 (width_remainder) {
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
    返回 true;
}

bool SDL_ConvertPixels_RGB_to_YUV(整数 width, 整数 height,
                                  SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, const void *src, 整数 src_pitch,
                                  SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, void *dst, 整数 dst_pitch)
{
    YCbCrType yuv_type = YCBCR_601_LIMITED;

    如果 (!GetYUVConversionType(dst_colorspace, width, height, 8, &yuv_type)) {
        返回 false;
    }

#如果 0 // Doesn't handle odd widths
    // RGB24 to FOURCC
    如果 (src_format == SDL_PIXELFORMAT_RGB24) {
        Uint8 *y;
        Uint8 *u;
        Uint8 *v;
        Uint32 y_stride;
        Uint32 uv_stride;

        如果 (GetYUVPlanes(width, height, dst_format, dst, dst_pitch, (const Uint8 **)&y, (const Uint8 **)&u, (const Uint8 **)&v, &y_stride, &uv_stride) < 0) {
            返回 false;
        }

        rgb24_yuv420_std(width, height, src, src_pitch, y, u, v, y_stride, uv_stride, yuv_type);
        返回 true;
    }
#endif

    // ARGB8888 to FOURCC
    如果 (src_format == SDL_PIXELFORMAT_ARGB8888 || src_format == SDL_PIXELFORMAT_XRGB8888) {
        返回 SDL_ConvertPixels_XRGB8888_to_YUV(width, height, src, src_pitch, dst_format, dst, dst_pitch, yuv_type);
    }

    如果 (dst_format == SDL_PIXELFORMAT_P010) {
        如果 (src_format == SDL_PIXELFORMAT_XBGR2101010) {
            返回 SDL_ConvertPixels_XBGR2101010_to_P010(width, height, src, src_pitch, dst_format, dst, dst_pitch, yuv_type);
        }

        // We currently only support converting from XBGR2101010 to P010
        bool result;
        void *tmp;
        整数 tmp_pitch = (width * sizeof(Uint32));

        tmp = SDL_malloc((size_t)tmp_pitch * height);
        如果 (!tmp) {
            返回 false;
        }

        // convert src/src_format to tmp/XBGR2101010
        result = SDL_ConvertPixelsAndColorspace(width, height, src_format, src_colorspace, src_properties, src, src_pitch, SDL_PIXELFORMAT_XBGR2101010, dst_colorspace, dst_properties, tmp, tmp_pitch);
        如果 (!result) {
            SDL_free(tmp);
            返回 false;
        }

        // convert tmp/XBGR2101010 to dst/P010
        result = SDL_ConvertPixels_XBGR2101010_to_P010(width, height, tmp, tmp_pitch, dst_format, dst, dst_pitch, yuv_type);
        SDL_free(tmp);
        返回 result;
    }

    // not ARGB8888 to FOURCC : need an intermediate conversion
    {
        bool result;
        void *tmp;
        整数 tmp_pitch = (width * sizeof(Uint32));

        tmp = SDL_malloc((size_t)tmp_pitch * height);
        如果 (!tmp) {
            返回 false;
        }

        // convert src/src_format to tmp/XRGB8888
        result = SDL_ConvertPixelsAndColorspace(width, height, src_format, src_colorspace, src_properties, src, src_pitch, SDL_PIXELFORMAT_XRGB8888, SDL_COLORSPACE_SRGB, 0, tmp, tmp_pitch);
        如果 (!result) {
            SDL_free(tmp);
            返回 false;
        }

        // convert tmp/XRGB8888 to dst/FOURCC
        result = SDL_ConvertPixels_XRGB8888_to_YUV(width, height, tmp, tmp_pitch, dst_format, dst, dst_pitch, yuv_type);
        SDL_free(tmp);
        返回 result;
    }
}

static bool SDL_ConvertPixels_YUV_to_YUV_Copy(整数 width, 整数 height, SDL_PixelFormat format, const void *src, 整数 src_pitch, void *dst, 整数 dst_pitch)
{
    整数 i;

    如果 (IsPlanar1x1Format(format)) {
        // YUV planes
        const size_t length = width * SDL_BYTESPERPIXEL(format);
        为 (i = height * 3; i--;) {
            SDL_memcpy(dst, src, length);
            src = (const Uint8 *)src + src_pitch;
            dst = (Uint8 *)dst + dst_pitch;
        }
        返回 true;
    }

    如果 (IsPlanar2x2Format(format)) {
        const 整数 bpp = SDL_BYTESPERPIXEL(format);

        // Y plane
        const size_t length = width * bpp;
        为 (i = height; i--;) {
            SDL_memcpy(dst, src, length);
            src = (const Uint8 *)src + src_pitch;
            dst = (Uint8 *)dst + dst_pitch;
        }

        如果 (format == SDL_PIXELFORMAT_YV12 ||
            format == SDL_PIXELFORMAT_IYUV ||
            format == SDL_PIXELFORMAT_I0FL) {
            // U and V planes are a quarter the size of the Y plane, rounded up
            width = ((width + 1) / 2) * bpp;
            height = (height + 1) / 2;
            src_pitch = ((src_pitch / bpp + 1) / 2) * bpp;
            dst_pitch = ((dst_pitch / bpp + 1) / 2) * bpp;
            为 (i = height * 2; i--;) {
                SDL_memcpy(dst, src, width);
                src = (const Uint8 *)src + src_pitch;
                dst = (Uint8 *)dst + dst_pitch;
            }
        } 否则 如果 (format == SDL_PIXELFORMAT_NV12 ||
                   format == SDL_PIXELFORMAT_NV21 ||
                   format == SDL_PIXELFORMAT_P010) {
            // U/V plane is half the height of the Y plane, rounded up, with packed CrCb
            width = ((width + 1) / 2) * 2 * bpp;
            height = (height + 1) / 2;
            src_pitch = ((src_pitch / bpp + 1) / 2) * 2 * bpp;
            dst_pitch = ((dst_pitch / bpp + 1) / 2) * 2 * bpp;
            为 (i = height; i--;) {
                SDL_memcpy(dst, src, width);
                src = (const Uint8 *)src + src_pitch;
                dst = (Uint8 *)dst + dst_pitch;
            }
        }
        返回 true;
    }

    如果 (IsPacked4Format(format)) {
        // Packed planes
        width = 4 * ((width + 1) / 2);
        为 (i = height; i--;) {
            SDL_memcpy(dst, src, width);
            src = (const Uint8 *)src + src_pitch;
            dst = (Uint8 *)dst + dst_pitch;
        }
        返回 true;
    }

    返回 SDL_SetError("SDL_ConvertPixels_YUV_to_YUV_Copy: Unsupported YUV format: %s", SDL_GetPixelFormatName(format));
}

static bool SDL_ConvertPixels_SwapUVPlanes(整数 width, 整数 height, const void *src, 整数 src_pitch, void *dst, 整数 dst_pitch)
{
    整数 y;
    const 整数 UVwidth = (width + 1) / 2;
    const 整数 UVheight = (height + 1) / 2;

    // Skip the Y plane
    src = (const Uint8 *)src + height * src_pitch;
    dst = (Uint8 *)dst + height * dst_pitch;

    如果 (src == dst) {
        整数 UVpitch = (dst_pitch + 1) / 2;
        Uint8 *tmp;
        Uint8 *row1 = (Uint8 *)dst;
        Uint8 *row2 = row1 + UVheight * UVpitch;

        // Allocate a temporary row for the swap
        tmp = (Uint8 *)SDL_malloc(UVwidth);
        如果 (!tmp) {
            返回 false;
        }
        为 (y = 0; y < UVheight; ++y) {
            SDL_memcpy(tmp, row1, UVwidth);
            SDL_memcpy(row1, row2, UVwidth);
            SDL_memcpy(row2, tmp, UVwidth);
            row1 += UVpitch;
            row2 += UVpitch;
        }
        SDL_free(tmp);
    } 否则 {
        const Uint8 *srcUV;
        Uint8 *dstUV;
        整数 srcUVPitch = ((src_pitch + 1) / 2);
        整数 dstUVPitch = ((dst_pitch + 1) / 2);

        // Copy the first plane
        srcUV = (const Uint8 *)src;
        dstUV = (Uint8 *)dst + UVheight * dstUVPitch;
        为 (y = 0; y < UVheight; ++y) {
            SDL_memcpy(dstUV, srcUV, UVwidth);
            srcUV += srcUVPitch;
            dstUV += dstUVPitch;
        }

        // Copy the second plane
        dstUV = (Uint8 *)dst;
        为 (y = 0; y < UVheight; ++y) {
            SDL_memcpy(dstUV, srcUV, UVwidth);
            srcUV += srcUVPitch;
            dstUV += dstUVPitch;
        }
    }
    返回 true;
}

#ifdef SDL_SSE2_INTRINSICS
static bool SDL_TARGETING("sse2") SDL_ConvertPixels_PackUVPlanes_to_NV_SSE2(整数 width, 整数 height, const void *src, 整数 src_pitch, void *dst, 整数 dst_pitch, bool reverseUV)
{
    整数 x, y;
    const 整数 UVwidth = (width + 1) / 2;
    const 整数 UVheight = (height + 1) / 2;
    const 整数 srcUVPitch = ((src_pitch + 1) / 2);
    const 整数 srcUVPitchLeft = srcUVPitch - UVwidth;
    const 整数 dstUVPitch = ((dst_pitch + 1) / 2) * 2;
    const 整数 dstUVPitchLeft = dstUVPitch - UVwidth * 2;
    const Uint8 *src1, *src2;
    Uint8 *dstUV;
    Uint8 *tmp = NULL;

    // Skip the Y plane
    src = (const Uint8 *)src + height * src_pitch;
    dst = (Uint8 *)dst + height * dst_pitch;

    如果 (src == dst) {
        // Need to make a copy of the buffer so we don't clobber it while converting
        tmp = (Uint8 *)SDL_malloc((size_t)2 * UVheight * srcUVPitch);
        如果 (tmp == NULL) {
            返回 false;
        }
        SDL_memcpy(tmp, src, (size_t)2 * UVheight * srcUVPitch);
        src = tmp;
    }

    如果 (reverseUV) {
        src2 = (const Uint8 *)src;
        src1 = src2 + UVheight * srcUVPitch;
    } 否则 {
        src1 = (const Uint8 *)src;
        src2 = src1 + UVheight * srcUVPitch;
    }
    dstUV = (Uint8 *)dst;

    y = UVheight;
    当 (y--) {
        x = UVwidth;
        当 (x >= 16) {
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
        当 (x--) {
            *dstUV++ = *src1++;
            *dstUV++ = *src2++;
        }
        src1 += srcUVPitchLeft;
        src2 += srcUVPitchLeft;
        dstUV += dstUVPitchLeft;
    }

    如果 (tmp) {
        SDL_free(tmp);
    }
    返回 true;
}

static bool SDL_TARGETING("sse2") SDL_ConvertPixels_SplitNV_to_UVPlanes_SSE2(整数 width, 整数 height, const void *src, 整数 src_pitch, void *dst, 整数 dst_pitch, bool reverseUV)
{
    整数 x, y;
    const 整数 UVwidth = (width + 1) / 2;
    const 整数 UVheight = (height + 1) / 2;
    const 整数 srcUVPitch = ((src_pitch + 1) / 2) * 2;
    const 整数 srcUVPitchLeft = srcUVPitch - UVwidth * 2;
    const 整数 dstUVPitch = ((dst_pitch + 1) / 2);
    const 整数 dstUVPitchLeft = dstUVPitch - UVwidth;
    const Uint8 *srcUV;
    Uint8 *dst1, *dst2;
    Uint8 *tmp = NULL;

    // Skip the Y plane
    src = (const Uint8 *)src + height * src_pitch;
    dst = (Uint8 *)dst + height * dst_pitch;

    如果 (src == dst) {
        // Need to make a copy of the buffer so we don't clobber it while converting
        tmp = (Uint8 *)SDL_malloc((size_t)UVheight * srcUVPitch);
        如果 (tmp == NULL) {
            返回 false;
        }
        SDL_memcpy(tmp, src, (size_t)UVheight * srcUVPitch);
        src = tmp;
    }

    如果 (reverseUV) {
        dst2 = (Uint8 *)dst;
        dst1 = dst2 + UVheight * dstUVPitch;
    } 否则 {
        dst1 = (Uint8 *)dst;
        dst2 = dst1 + UVheight * dstUVPitch;
    }
    srcUV = (const Uint8 *)src;

    y = UVheight;
    当 (y--) {
        __m128i mask = _mm_set1_epi16(0x00FF);
        x = UVwidth;
        当 (x >= 16) {
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
        当 (x--) {
            *dst1++ = *srcUV++;
            *dst2++ = *srcUV++;
        }
        srcUV += srcUVPitchLeft;
        dst1 += dstUVPitchLeft;
        dst2 += dstUVPitchLeft;
    }

    如果 (tmp) {
        SDL_free(tmp);
    }
    返回 true;
}

static bool SDL_TARGETING("sse2") SDL_ConvertPixels_SwapNV_SSE2(整数 width, 整数 height, const void *src, 整数 src_pitch, void *dst, 整数 dst_pitch)
{
    整数 x, y;
    const 整数 UVwidth = (width + 1) / 2;
    const 整数 UVheight = (height + 1) / 2;
    const 整数 srcUVPitch = ((src_pitch + 1) / 2) * 2;
    const 整数 srcUVPitchLeft = (srcUVPitch - UVwidth * 2) / sizeof(Uint16);
    const 整数 dstUVPitch = ((dst_pitch + 1) / 2) * 2;
    const 整数 dstUVPitchLeft = (dstUVPitch - UVwidth * 2) / sizeof(Uint16);
    const Uint16 *srcUV;
    Uint16 *dstUV;

    // Skip the Y plane
    src = (const Uint8 *)src + height * src_pitch;
    dst = (Uint8 *)dst + height * dst_pitch;

    srcUV = (const Uint16 *)src;
    dstUV = (Uint16 *)dst;
    y = UVheight;
    当 (y--) {
        x = UVwidth;
        当 (x >= 8) {
            __m128i uv = _mm_loadu_si128((__m128i *)srcUV);
            __m128i v = _mm_slli_epi16(uv, 8);
            __m128i u = _mm_srli_epi16(uv, 8);
            __m128i vu = _mm_or_si128(v, u);
            _mm_storeu_si128((__m128i *)dstUV, vu);
            srcUV += 8;
            dstUV += 8;
            x -= 8;
        }
        如果 (x > 0) {
            const Uint8 *srcUV8 = (const Uint8 *)srcUV;
            Uint8 *dstUV8 = (Uint8 *)dstUV;
            srcUV += x;
            dstUV += x;
            当 (x--) {
                Uint8 u = *srcUV8++;
                Uint8 v = *srcUV8++;
                *dstUV8++ = v;
                *dstUV8++ = u;
            }
        }
        srcUV += srcUVPitchLeft;
        dstUV += dstUVPitchLeft;
    }
    返回 true;
}
#endif

static bool SDL_ConvertPixels_PackUVPlanes_to_NV_std(整数 width, 整数 height, const void *src, 整数 src_pitch, void *dst, 整数 dst_pitch, bool reverseUV)
{
    整数 x, y;
    const 整数 UVwidth = (width + 1) / 2;
    const 整数 UVheight = (height + 1) / 2;
    const 整数 srcUVPitch = ((src_pitch + 1) / 2);
    const 整数 srcUVPitchLeft = srcUVPitch - UVwidth;
    const 整数 dstUVPitch = ((dst_pitch + 1) / 2) * 2;
    const 整数 dstUVPitchLeft = dstUVPitch - UVwidth * 2;
    const Uint8 *src1, *src2;
    Uint8 *dstUV;
    Uint8 *tmp = NULL;

    // Skip the Y plane
    src = (const Uint8 *)src + height * src_pitch;
    dst = (Uint8 *)dst + height * dst_pitch;

    如果 (src == dst) {
        // Need to make a copy of the buffer so we don't clobber it while converting
        tmp = (Uint8 *)SDL_malloc((size_t)2 * UVheight * srcUVPitch);
        如果 (!tmp) {
            返回 false;
        }
        SDL_memcpy(tmp, src, (size_t)2 * UVheight * srcUVPitch);
        src = tmp;
    }

    如果 (reverseUV) {
        src2 = (const Uint8 *)src;
        src1 = src2 + UVheight * srcUVPitch;
    } 否则 {
        src1 = (const Uint8 *)src;
        src2 = src1 + UVheight * srcUVPitch;
    }
    dstUV = (Uint8 *)dst;

    y = UVheight;
    当 (y--) {
        x = UVwidth;
        当 (x--) {
            *dstUV++ = *src1++;
            *dstUV++ = *src2++;
        }
        src1 += srcUVPitchLeft;
        src2 += srcUVPitchLeft;
        dstUV += dstUVPitchLeft;
    }

    SDL_free(tmp);
    返回 true;
}

static bool SDL_ConvertPixels_SplitNV_to_UVPlanes_std(整数 width, 整数 height, const void *src, 整数 src_pitch, void *dst, 整数 dst_pitch, bool reverseUV)
{
    整数 x, y;
    const 整数 UVwidth = (width + 1) / 2;
    const 整数 UVheight = (height + 1) / 2;
    const 整数 srcUVPitch = ((src_pitch + 1) / 2) * 2;
    const 整数 srcUVPitchLeft = srcUVPitch - UVwidth * 2;
    const 整数 dstUVPitch = ((dst_pitch + 1) / 2);
    const 整数 dstUVPitchLeft = dstUVPitch - UVwidth;
    const Uint8 *srcUV;
    Uint8 *dst1, *dst2;
    Uint8 *tmp = NULL;

    // Skip the Y plane
    src = (const Uint8 *)src + height * src_pitch;
    dst = (Uint8 *)dst + height * dst_pitch;

    如果 (src == dst) {
        // Need to make a copy of the buffer so we don't clobber it while converting
        tmp = (Uint8 *)SDL_malloc((size_t)UVheight * srcUVPitch);
        如果 (!tmp) {
            返回 false;
        }
        SDL_memcpy(tmp, src, (size_t)UVheight * srcUVPitch);
        src = tmp;
    }

    如果 (reverseUV) {
        dst2 = (Uint8 *)dst;
        dst1 = dst2 + UVheight * dstUVPitch;
    } 否则 {
        dst1 = (Uint8 *)dst;
        dst2 = dst1 + UVheight * dstUVPitch;
    }
    srcUV = (const Uint8 *)src;

    y = UVheight;
    当 (y--) {
        x = UVwidth;
        当 (x--) {
            *dst1++ = *srcUV++;
            *dst2++ = *srcUV++;
        }
        srcUV += srcUVPitchLeft;
        dst1 += dstUVPitchLeft;
        dst2 += dstUVPitchLeft;
    }

    SDL_free(tmp);
    返回 true;
}

static bool SDL_ConvertPixels_SwapNV_std(整数 width, 整数 height, const void *src, 整数 src_pitch, void *dst, 整数 dst_pitch)
{
    整数 x, y;
    const 整数 UVwidth = (width + 1) / 2;
    const 整数 UVheight = (height + 1) / 2;
    const 整数 srcUVPitch = ((src_pitch + 1) / 2) * 2;
    const 整数 dstUVPitch = ((dst_pitch + 1) / 2) * 2;

    // Skip the Y plane
    src = (const Uint8 *)src + height * src_pitch;
    dst = (Uint8 *)dst + height * dst_pitch;

    bool aligned = (((uintptr_t)src | (uintptr_t)dst) & 1) == 0;
    如果 (aligned) {
        const 整数 srcUVPitchLeft = (srcUVPitch - UVwidth * 2) / sizeof(Uint16);
        const 整数 dstUVPitchLeft = (dstUVPitch - UVwidth * 2) / sizeof(Uint16);
        const Uint16 *srcUV = (const Uint16 *)src;
        Uint16 *dstUV = (Uint16 *)dst;
        y = UVheight;
        当 (y--) {
            x = UVwidth;
            当 (x--) {
                *dstUV++ = SDL_Swap16(*srcUV++);
            }
            srcUV += srcUVPitchLeft;
            dstUV += dstUVPitchLeft;
        }
    } 否则 {
        const 整数 srcUVPitchLeft = (srcUVPitch - UVwidth * 2);
        const 整数 dstUVPitchLeft = (dstUVPitch - UVwidth * 2);
        const Uint8 *srcUV = (const Uint8 *)src;
        Uint8 *dstUV = (Uint8 *)dst;
        y = UVheight;
        当 (y--) {
            x = UVwidth;
            当 (x--) {
                Uint8 u = *srcUV++;
                Uint8 v = *srcUV++;
                *dstUV++ = v;
                *dstUV++ = u;
            }
            srcUV += srcUVPitchLeft;
            dstUV += dstUVPitchLeft;
        }
    }
    返回 true;
}

static bool SDL_ConvertPixels_PackUVPlanes_to_NV(整数 width, 整数 height, const void *src, 整数 src_pitch, void *dst, 整数 dst_pitch, bool reverseUV)
{
#ifdef SDL_SSE2_INTRINSICS
    如果 (SDL_HasSSE2()) {
      返回 SDL_ConvertPixels_PackUVPlanes_to_NV_SSE2(width, height, src, src_pitch, dst, dst_pitch, reverseUV);
    }
#endif
    返回 SDL_ConvertPixels_PackUVPlanes_to_NV_std(width, height, src, src_pitch, dst, dst_pitch, reverseUV);
}

static bool SDL_ConvertPixels_SplitNV_to_UVPlanes(整数 width, 整数 height, const void *src, 整数 src_pitch, void *dst, 整数 dst_pitch, bool reverseUV)
{
#ifdef SDL_SSE2_INTRINSICS
    如果 (SDL_HasSSE2()) {
      返回 SDL_ConvertPixels_SplitNV_to_UVPlanes_SSE2(width, height, src, src_pitch, dst, dst_pitch, reverseUV);
    }
#endif
    返回 SDL_ConvertPixels_SplitNV_to_UVPlanes_std(width, height, src, src_pitch, dst, dst_pitch, reverseUV);
}

static bool SDL_ConvertPixels_SwapNV(整数 width, 整数 height, const void *src, 整数 src_pitch, void *dst, 整数 dst_pitch)
{
#ifdef SDL_SSE2_INTRINSICS
    如果 (SDL_HasSSE2()) {
      返回 SDL_ConvertPixels_SwapNV_SSE2(width, height, src, src_pitch, dst, dst_pitch);
    }
#endif
    返回 SDL_ConvertPixels_SwapNV_std(width, height, src, src_pitch, dst, dst_pitch);
}

static bool SDL_ConvertPixels_Planar2x2_to_Planar2x2(整数 width, 整数 height,
                                                     SDL_PixelFormat src_format, const void *src, 整数 src_pitch,
                                                     SDL_PixelFormat dst_format, void *dst, 整数 dst_pitch)
{
    如果 (src != dst) {
        // Copy Y plane
        整数 i;
        const Uint8 *srcY = (const Uint8 *)src;
        Uint8 *dstY = (Uint8 *)dst;
        为 (i = height; i--;) {
            SDL_memcpy(dstY, srcY, width);
            srcY += src_pitch;
            dstY += dst_pitch;
        }
    }

    switch (src_format) {
    case SDL_PIXELFORMAT_YV12:
        switch (dst_format) {
        case SDL_PIXELFORMAT_IYUV:
            返回 SDL_ConvertPixels_SwapUVPlanes(width, height, src, src_pitch, dst, dst_pitch);
        case SDL_PIXELFORMAT_NV12:
            返回 SDL_ConvertPixels_PackUVPlanes_to_NV(width, height, src, src_pitch, dst, dst_pitch, true);
        case SDL_PIXELFORMAT_NV21:
            返回 SDL_ConvertPixels_PackUVPlanes_to_NV(width, height, src, src_pitch, dst, dst_pitch, false);
        default:
            break;
        }
        break;
    case SDL_PIXELFORMAT_IYUV:
        switch (dst_format) {
        case SDL_PIXELFORMAT_YV12:
            返回 SDL_ConvertPixels_SwapUVPlanes(width, height, src, src_pitch, dst, dst_pitch);
        case SDL_PIXELFORMAT_NV12:
            返回 SDL_ConvertPixels_PackUVPlanes_to_NV(width, height, src, src_pitch, dst, dst_pitch, false);
        case SDL_PIXELFORMAT_NV21:
            返回 SDL_ConvertPixels_PackUVPlanes_to_NV(width, height, src, src_pitch, dst, dst_pitch, true);
        default:
            break;
        }
        break;
    case SDL_PIXELFORMAT_NV12:
        switch (dst_format) {
        case SDL_PIXELFORMAT_YV12:
            返回 SDL_ConvertPixels_SplitNV_to_UVPlanes(width, height, src, src_pitch, dst, dst_pitch, true);
        case SDL_PIXELFORMAT_IYUV:
            返回 SDL_ConvertPixels_SplitNV_to_UVPlanes(width, height, src, src_pitch, dst, dst_pitch, false);
        case SDL_PIXELFORMAT_NV21:
            返回 SDL_ConvertPixels_SwapNV(width, height, src, src_pitch, dst, dst_pitch);
        default:
            break;
        }
        break;
    case SDL_PIXELFORMAT_NV21:
        switch (dst_format) {
        case SDL_PIXELFORMAT_YV12:
            返回 SDL_ConvertPixels_SplitNV_to_UVPlanes(width, height, src, src_pitch, dst, dst_pitch, false);
        case SDL_PIXELFORMAT_IYUV:
            返回 SDL_ConvertPixels_SplitNV_to_UVPlanes(width, height, src, src_pitch, dst, dst_pitch, true);
        case SDL_PIXELFORMAT_NV12:
            返回 SDL_ConvertPixels_SwapNV(width, height, src, src_pitch, dst, dst_pitch);
        default:
            break;
        }
        break;
    default:
        break;
    }
    返回 SDL_SetError("SDL_ConvertPixels_Planar2x2_to_Planar2x2: Unsupported YUV conversion: %s -> %s", SDL_GetPixelFormatName(src_format),
                        SDL_GetPixelFormatName(dst_format));
}

#ifdef SDL_SSE2_INTRINSICS
#define PACKED4_TO_PACKED4_ROW_SSE2(shuffle)                      \
    当 (x >= 4) {                                              \
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

static bool SDL_TARGETING("sse2") SDL_ConvertPixels_YUY2_to_UYVY_SSE2(整数 width, 整数 height, const void *src, 整数 src_pitch, void *dst, 整数 dst_pitch)
{
    整数 x, y;
    const 整数 YUVwidth = (width + 1) / 2;
    const 整数 srcYUVPitchLeft = (src_pitch - YUVwidth * 4);
    const 整数 dstYUVPitchLeft = (dst_pitch - YUVwidth * 4);
    const Uint8 *srcYUV = (const Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = height;
    x = YUVwidth;
    当 (y--) {
        PACKED4_TO_PACKED4_ROW_SSE2(_MM_SHUFFLE(2, 3, 0, 1));
        当 (x--) {
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
        srcYUV += srcYUVPitchLeft;
        dstYUV += dstYUVPitchLeft;
        x = YUVwidth;
    }
    返回 true;
}

static bool SDL_TARGETING("sse2") SDL_ConvertPixels_YUY2_to_YVYU_SSE2(整数 width, 整数 height, const void *src, 整数 src_pitch, void *dst, 整数 dst_pitch)
{
    整数 x, y;
    const 整数 YUVwidth = (width + 1) / 2;
    const 整数 srcYUVPitchLeft = (src_pitch - YUVwidth * 4);
    const 整数 dstYUVPitchLeft = (dst_pitch - YUVwidth * 4);
    const Uint8 *srcYUV = (const Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = height;
    x = YUVwidth;
    当 (y--) {
        PACKED4_TO_PACKED4_ROW_SSE2(_MM_SHUFFLE(1, 2, 3, 0));
        当 (x--) {
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
        srcYUV += srcYUVPitchLeft;
        dstYUV += dstYUVPitchLeft;
        x = YUVwidth;
    }
    返回 true;
}

static bool SDL_TARGETING("sse2") SDL_ConvertPixels_UYVY_to_YUY2_SSE2(整数 width, 整数 height, const void *src, 整数 src_pitch, void *dst, 整数 dst_pitch)
{
    整数 x, y;
    const 整数 YUVwidth = (width + 1) / 2;
    const 整数 srcYUVPitchLeft = (src_pitch - YUVwidth * 4);
    const 整数 dstYUVPitchLeft = (dst_pitch - YUVwidth * 4);
    const Uint8 *srcYUV = (const Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = height;
    x = YUVwidth;
    当 (y--) {
        PACKED4_TO_PACKED4_ROW_SSE2(_MM_SHUFFLE(2, 3, 0, 1));
        当 (x--) {
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
        srcYUV += srcYUVPitchLeft;
        dstYUV += dstYUVPitchLeft;
        x = YUVwidth;
    }
    返回 true;
}

static bool SDL_TARGETING("sse2") SDL_ConvertPixels_UYVY_to_YVYU_SSE2(整数 width, 整数 height, const void *src, 整数 src_pitch, void *dst, 整数 dst_pitch)
{
    整数 x, y;
    const 整数 YUVwidth = (width + 1) / 2;
    const 整数 srcYUVPitchLeft = (src_pitch - YUVwidth * 4);
    const 整数 dstYUVPitchLeft = (dst_pitch - YUVwidth * 4);
    const Uint8 *srcYUV = (const Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = height;
    x = YUVwidth;
    当 (y--) {
        PACKED4_TO_PACKED4_ROW_SSE2(_MM_SHUFFLE(0, 3, 2, 1));
        当 (x--) {
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
        srcYUV += srcYUVPitchLeft;
        dstYUV += dstYUVPitchLeft;
        x = YUVwidth;
    }
    返回 true;
}

static bool SDL_TARGETING("sse2") SDL_ConvertPixels_YVYU_to_YUY2_SSE2(整数 width, 整数 height, const void *src, 整数 src_pitch, void *dst, 整数 dst_pitch)
{
    整数 x, y;
    const 整数 YUVwidth = (width + 1) / 2;
    const 整数 srcYUVPitchLeft = (src_pitch - YUVwidth * 4);
    const 整数 dstYUVPitchLeft = (dst_pitch - YUVwidth * 4);
    const Uint8 *srcYUV = (const Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = height;
    x = YUVwidth;
    当 (y--) {
        PACKED4_TO_PACKED4_ROW_SSE2(_MM_SHUFFLE(1, 2, 3, 0));
        当 (x--) {
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
        srcYUV += srcYUVPitchLeft;
        dstYUV += dstYUVPitchLeft;
        x = YUVwidth;
    }
    返回 true;
}

static bool SDL_TARGETING("sse2") SDL_ConvertPixels_YVYU_to_UYVY_SSE2(整数 width, 整数 height, const void *src, 整数 src_pitch, void *dst, 整数 dst_pitch)
{
    整数 x, y;
    const 整数 YUVwidth = (width + 1) / 2;
    const 整数 srcYUVPitchLeft = (src_pitch - YUVwidth * 4);
    const 整数 dstYUVPitchLeft = (dst_pitch - YUVwidth * 4);
    const Uint8 *srcYUV = (const Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = height;
    x = YUVwidth;
    当 (y--) {
        PACKED4_TO_PACKED4_ROW_SSE2(_MM_SHUFFLE(2, 1, 0, 3));
        当 (x--) {
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
        srcYUV += srcYUVPitchLeft;
        dstYUV += dstYUVPitchLeft;
        x = YUVwidth;
    }
    返回 true;
}
#endif

static bool SDL_ConvertPixels_YUY2_to_UYVY_std(整数 width, 整数 height, const void *src, 整数 src_pitch, void *dst, 整数 dst_pitch)
{
    整数 x, y;
    const 整数 YUVwidth = (width + 1) / 2;
    const 整数 srcYUVPitchLeft = (src_pitch - YUVwidth * 4);
    const 整数 dstYUVPitchLeft = (dst_pitch - YUVwidth * 4);
    const Uint8 *srcYUV = (const Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = height;
    当 (y--) {
        x = YUVwidth;
        当 (x--) {
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
        srcYUV += srcYUVPitchLeft;
        dstYUV += dstYUVPitchLeft;
    }
    返回 true;
}

static bool SDL_ConvertPixels_YUY2_to_YVYU_std(整数 width, 整数 height, const void *src, 整数 src_pitch, void *dst, 整数 dst_pitch)
{
    整数 x, y;
    const 整数 YUVwidth = (width + 1) / 2;
    const 整数 srcYUVPitchLeft = (src_pitch - YUVwidth * 4);
    const 整数 dstYUVPitchLeft = (dst_pitch - YUVwidth * 4);
    const Uint8 *srcYUV = (const Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = height;
    当 (y--) {
        x = YUVwidth;
        当 (x--) {
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
        srcYUV += srcYUVPitchLeft;
        dstYUV += dstYUVPitchLeft;
    }
    返回 true;
}

static bool SDL_ConvertPixels_UYVY_to_YUY2_std(整数 width, 整数 height, const void *src, 整数 src_pitch, void *dst, 整数 dst_pitch)
{
    整数 x, y;
    const 整数 YUVwidth = (width + 1) / 2;
    const 整数 srcYUVPitchLeft = (src_pitch - YUVwidth * 4);
    const 整数 dstYUVPitchLeft = (dst_pitch - YUVwidth * 4);
    const Uint8 *srcYUV = (const Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = height;
    当 (y--) {
        x = YUVwidth;
        当 (x--) {
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
        srcYUV += srcYUVPitchLeft;
        dstYUV += dstYUVPitchLeft;
    }
    返回 true;
}

static bool SDL_ConvertPixels_UYVY_to_YVYU_std(整数 width, 整数 height, const void *src, 整数 src_pitch, void *dst, 整数 dst_pitch)
{
    整数 x, y;
    const 整数 YUVwidth = (width + 1) / 2;
    const 整数 srcYUVPitchLeft = (src_pitch - YUVwidth * 4);
    const 整数 dstYUVPitchLeft = (dst_pitch - YUVwidth * 4);
    const Uint8 *srcYUV = (const Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = height;
    当 (y--) {
        x = YUVwidth;
        当 (x--) {
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
        srcYUV += srcYUVPitchLeft;
        dstYUV += dstYUVPitchLeft;
    }
    返回 true;
}

static bool SDL_ConvertPixels_YVYU_to_YUY2_std(整数 width, 整数 height, const void *src, 整数 src_pitch, void *dst, 整数 dst_pitch)
{
    整数 x, y;
    const 整数 YUVwidth = (width + 1) / 2;
    const 整数 srcYUVPitchLeft = (src_pitch - YUVwidth * 4);
    const 整数 dstYUVPitchLeft = (dst_pitch - YUVwidth * 4);
    const Uint8 *srcYUV = (const Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = height;
    当 (y--) {
        x = YUVwidth;
        当 (x--) {
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
        srcYUV += srcYUVPitchLeft;
        dstYUV += dstYUVPitchLeft;
    }
    返回 true;
}

static bool SDL_ConvertPixels_YVYU_to_UYVY_std(整数 width, 整数 height, const void *src, 整数 src_pitch, void *dst, 整数 dst_pitch)
{
    整数 x, y;
    const 整数 YUVwidth = (width + 1) / 2;
    const 整数 srcYUVPitchLeft = (src_pitch - YUVwidth * 4);
    const 整数 dstYUVPitchLeft = (dst_pitch - YUVwidth * 4);
    const Uint8 *srcYUV = (const Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = height;
    当 (y--) {
        x = YUVwidth;
        当 (x--) {
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
        srcYUV += srcYUVPitchLeft;
        dstYUV += dstYUVPitchLeft;
    }
    返回 true;
}

static bool SDL_ConvertPixels_YUY2_to_UYVY(整数 width, 整数 height, const void *src, 整数 src_pitch, void *dst, 整数 dst_pitch)
{
#ifdef SDL_SSE2_INTRINSICS
    如果 (SDL_HasSSE2()) {
      返回 SDL_ConvertPixels_YUY2_to_UYVY_SSE2(width, height, src, src_pitch, dst, dst_pitch);
    }
#endif
    返回 SDL_ConvertPixels_YUY2_to_UYVY_std(width, height, src, src_pitch, dst, dst_pitch);
}

static bool SDL_ConvertPixels_YUY2_to_YVYU(整数 width, 整数 height, const void *src, 整数 src_pitch, void *dst, 整数 dst_pitch)
{
#ifdef SDL_SSE2_INTRINSICS
    如果 (SDL_HasSSE2()) {
      返回 SDL_ConvertPixels_YUY2_to_YVYU_SSE2(width, height, src, src_pitch, dst, dst_pitch);
    }
#endif
    返回 SDL_ConvertPixels_YUY2_to_YVYU_std(width, height, src, src_pitch, dst, dst_pitch);
}

static bool SDL_ConvertPixels_UYVY_to_YUY2(整数 width, 整数 height, const void *src, 整数 src_pitch, void *dst, 整数 dst_pitch)
{
#ifdef SDL_SSE2_INTRINSICS
    如果 (SDL_HasSSE2()) {
      返回 SDL_ConvertPixels_UYVY_to_YUY2_SSE2(width, height, src, src_pitch, dst, dst_pitch);
    }
#endif
    返回 SDL_ConvertPixels_UYVY_to_YUY2_std(width, height, src, src_pitch, dst, dst_pitch);
}

static bool SDL_ConvertPixels_UYVY_to_YVYU(整数 width, 整数 height, const void *src, 整数 src_pitch, void *dst, 整数 dst_pitch)
{
#ifdef SDL_SSE2_INTRINSICS
    如果 (SDL_HasSSE2()) {
      返回 SDL_ConvertPixels_UYVY_to_YVYU_SSE2(width, height, src, src_pitch, dst, dst_pitch);
    }
#endif
    返回 SDL_ConvertPixels_UYVY_to_YVYU_std(width, height, src, src_pitch, dst, dst_pitch);
}

static bool SDL_ConvertPixels_YVYU_to_YUY2(整数 width, 整数 height, const void *src, 整数 src_pitch, void *dst, 整数 dst_pitch)
{
#ifdef SDL_SSE2_INTRINSICS
    如果 (SDL_HasSSE2()) {
      返回 SDL_ConvertPixels_YVYU_to_YUY2_SSE2(width, height, src, src_pitch, dst, dst_pitch);
    }
#endif
    返回 SDL_ConvertPixels_YVYU_to_YUY2_std(width, height, src, src_pitch, dst, dst_pitch);
}

static bool SDL_ConvertPixels_YVYU_to_UYVY(整数 width, 整数 height, const void *src, 整数 src_pitch, void *dst, 整数 dst_pitch)
{
#ifdef SDL_SSE2_INTRINSICS
    如果 (SDL_HasSSE2()) {
      返回 SDL_ConvertPixels_YVYU_to_UYVY_SSE2(width, height, src, src_pitch, dst, dst_pitch);
    }
#endif
    返回 SDL_ConvertPixels_YVYU_to_UYVY_std(width, height, src, src_pitch, dst, dst_pitch);
}

static bool SDL_ConvertPixels_Packed4_to_Packed4(整数 width, 整数 height,
                                                SDL_PixelFormat src_format, const void *src, 整数 src_pitch,
                                                SDL_PixelFormat dst_format, void *dst, 整数 dst_pitch)
{
    switch (src_format) {
    case SDL_PIXELFORMAT_YUY2:
        switch (dst_format) {
        case SDL_PIXELFORMAT_UYVY:
            返回 SDL_ConvertPixels_YUY2_to_UYVY(width, height, src, src_pitch, dst, dst_pitch);
        case SDL_PIXELFORMAT_YVYU:
            返回 SDL_ConvertPixels_YUY2_to_YVYU(width, height, src, src_pitch, dst, dst_pitch);
        default:
            break;
        }
        break;
    case SDL_PIXELFORMAT_UYVY:
        switch (dst_format) {
        case SDL_PIXELFORMAT_YUY2:
            返回 SDL_ConvertPixels_UYVY_to_YUY2(width, height, src, src_pitch, dst, dst_pitch);
        case SDL_PIXELFORMAT_YVYU:
            返回 SDL_ConvertPixels_UYVY_to_YVYU(width, height, src, src_pitch, dst, dst_pitch);
        default:
            break;
        }
        break;
    case SDL_PIXELFORMAT_YVYU:
        switch (dst_format) {
        case SDL_PIXELFORMAT_YUY2:
            返回 SDL_ConvertPixels_YVYU_to_YUY2(width, height, src, src_pitch, dst, dst_pitch);
        case SDL_PIXELFORMAT_UYVY:
            返回 SDL_ConvertPixels_YVYU_to_UYVY(width, height, src, src_pitch, dst, dst_pitch);
        default:
            break;
        }
        break;
    default:
        break;
    }
    返回 SDL_SetError("SDL_ConvertPixels_Packed4_to_Packed4: Unsupported YUV conversion: %s -> %s", SDL_GetPixelFormatName(src_format),
                        SDL_GetPixelFormatName(dst_format));
}

static bool SDL_ConvertPixels_Planar2x2_to_Packed4(整数 width, 整数 height,
                                                   SDL_PixelFormat src_format, const void *src, 整数 src_pitch,
                                                   SDL_PixelFormat dst_format, void *dst, 整数 dst_pitch)
{
    整数 x, y;
    const Uint8 *srcY1, *srcY2, *srcU, *srcV;
    Uint32 srcY_pitch, srcUV_pitch;
    Uint32 srcY_pitch_left, srcUV_pitch_left, srcUV_pixel_stride;
    Uint8 *dstY1, *dstY2, *dstU1, *dstU2, *dstV1, *dstV2;
    Uint32 dstY_pitch, dstUV_pitch;
    Uint32 dst_pitch_left;

    如果 (src == dst) {
        返回 SDL_SetError("Can't change YUV plane types in-place");
    }

    如果 (!GetYUVPlanes(width, height, src_format, src, src_pitch,
                      &srcY1, &srcU, &srcV, &srcY_pitch, &srcUV_pitch)) {
        返回 false;
    }
    srcY2 = srcY1 + srcY_pitch;
    srcY_pitch_left = (srcY_pitch - width);

    如果 (src_format == SDL_PIXELFORMAT_NV12 || src_format == SDL_PIXELFORMAT_NV21) {
        srcUV_pixel_stride = 2;
        srcUV_pitch_left = (srcUV_pitch - 2 * ((width + 1) / 2));
    } 否则 {
        srcUV_pixel_stride = 1;
        srcUV_pitch_left = (srcUV_pitch - ((width + 1) / 2));
    }

    如果 (!GetYUVPlanes(width, height, dst_format, dst, dst_pitch,
                      (const Uint8 **)&dstY1, (const Uint8 **)&dstU1, (const Uint8 **)&dstV1,
                      &dstY_pitch, &dstUV_pitch)) {
        返回 false;
    }
    dstY2 = dstY1 + dstY_pitch;
    dstU2 = dstU1 + dstUV_pitch;
    dstV2 = dstV1 + dstUV_pitch;
    dst_pitch_left = (dstY_pitch - 4 * ((width + 1) / 2));

    // Copy 2x2 blocks of pixels at a time
    为 (y = 0; y < (height - 1); y += 2) {
        为 (x = 0; x < (width - 1); x += 2) {
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
        如果 (x == (width - 1)) {
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

        srcY1 += srcY_pitch_left + srcY_pitch;
        srcY2 += srcY_pitch_left + srcY_pitch;
        srcU += srcUV_pitch_left;
        srcV += srcUV_pitch_left;
        dstY1 += dst_pitch_left + dstY_pitch;
        dstY2 += dst_pitch_left + dstY_pitch;
        dstU1 += dst_pitch_left + dstUV_pitch;
        dstU2 += dst_pitch_left + dstUV_pitch;
        dstV1 += dst_pitch_left + dstUV_pitch;
        dstV2 += dst_pitch_left + dstUV_pitch;
    }

    // Last row
    如果 (y == (height - 1)) {
        为 (x = 0; x < (width - 1); x += 2) {
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
        如果 (x == (width - 1)) {
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
    返回 true;
}

static bool SDL_ConvertPixels_Packed4_to_Planar2x2(整数 width, 整数 height,
                                                   SDL_PixelFormat src_format, const void *src, 整数 src_pitch,
                                                   SDL_PixelFormat dst_format, void *dst, 整数 dst_pitch)
{
    整数 x, y;
    const Uint8 *srcY1, *srcY2, *srcU1, *srcU2, *srcV1, *srcV2;
    Uint32 srcY_pitch, srcUV_pitch;
    Uint32 src_pitch_left;
    Uint8 *dstY1, *dstY2, *dstU, *dstV;
    Uint32 dstY_pitch, dstUV_pitch;
    Uint32 dstY_pitch_left, dstUV_pitch_left, dstUV_pixel_stride;

    如果 (src == dst) {
        返回 SDL_SetError("Can't change YUV plane types in-place");
    }

    如果 (!GetYUVPlanes(width, height, src_format, src, src_pitch,
                      &srcY1, &srcU1, &srcV1, &srcY_pitch, &srcUV_pitch)) {
        返回 false;
    }
    srcY2 = srcY1 + srcY_pitch;
    srcU2 = srcU1 + srcUV_pitch;
    srcV2 = srcV1 + srcUV_pitch;
    src_pitch_left = (srcY_pitch - 4 * ((width + 1) / 2));

    如果 (!GetYUVPlanes(width, height, dst_format, dst, dst_pitch,
                      (const Uint8 **)&dstY1, (const Uint8 **)&dstU, (const Uint8 **)&dstV,
                      &dstY_pitch, &dstUV_pitch)) {
        返回 false;
    }
    dstY2 = dstY1 + dstY_pitch;
    dstY_pitch_left = (dstY_pitch - width);

    如果 (dst_format == SDL_PIXELFORMAT_NV12 || dst_format == SDL_PIXELFORMAT_NV21) {
        dstUV_pixel_stride = 2;
        dstUV_pitch_left = (dstUV_pitch - 2 * ((width + 1) / 2));
    } 否则 {
        dstUV_pixel_stride = 1;
        dstUV_pitch_left = (dstUV_pitch - ((width + 1) / 2));
    }

    // Copy 2x2 blocks of pixels at a time
    为 (y = 0; y < (height - 1); y += 2) {
        为 (x = 0; x < (width - 1); x += 2) {
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
        如果 (x == (width - 1)) {
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

        srcY1 += src_pitch_left + srcY_pitch;
        srcY2 += src_pitch_left + srcY_pitch;
        srcU1 += src_pitch_left + srcUV_pitch;
        srcU2 += src_pitch_left + srcUV_pitch;
        srcV1 += src_pitch_left + srcUV_pitch;
        srcV2 += src_pitch_left + srcUV_pitch;
        dstY1 += dstY_pitch_left + dstY_pitch;
        dstY2 += dstY_pitch_left + dstY_pitch;
        dstU += dstUV_pitch_left;
        dstV += dstUV_pitch_left;
    }

    // Last row
    如果 (y == (height - 1)) {
        为 (x = 0; x < (width - 1); x += 2) {
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
        如果 (x == (width - 1)) {
            *dstY1 = *srcY1;
            *dstU = *srcU1;
            *dstV = *srcV1;
        }
    }
    返回 true;
}

#endif // SDL_HAVE_YUV

bool SDL_ConvertPixels_YUV_to_YUV(整数 width, 整数 height,
                                  SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, const void *src, 整数 src_pitch,
                                  SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, void *dst, 整数 dst_pitch)
{
#ifdef SDL_HAVE_YUV
    如果 (src_colorspace != dst_colorspace) {
        返回 SDL_SetError("SDL_ConvertPixels_YUV_to_YUV: colorspace conversion not supported");
    }

    如果 (src_format == dst_format) {
        如果 (src == dst) {
            // Nothing to do
            返回 true;
        }
        返回 SDL_ConvertPixels_YUV_to_YUV_Copy(width, height, src_format, src, src_pitch, dst, dst_pitch);
    }

    如果 (IsPlanar2x2Format(src_format) && IsPlanar2x2Format(dst_format)) {
        返回 SDL_ConvertPixels_Planar2x2_to_Planar2x2(width, height, src_format, src, src_pitch, dst_format, dst, dst_pitch);
    } 否则 如果 (IsPacked4Format(src_format) && IsPacked4Format(dst_format)) {
        返回 SDL_ConvertPixels_Packed4_to_Packed4(width, height, src_format, src, src_pitch, dst_format, dst, dst_pitch);
    } 否则 如果 (IsPlanar2x2Format(src_format) && IsPacked4Format(dst_format)) {
        返回 SDL_ConvertPixels_Planar2x2_to_Packed4(width, height, src_format, src, src_pitch, dst_format, dst, dst_pitch);
    } 否则 如果 (IsPacked4Format(src_format) && IsPlanar2x2Format(dst_format)) {
        返回 SDL_ConvertPixels_Packed4_to_Planar2x2(width, height, src_format, src, src_pitch, dst_format, dst, dst_pitch);
    } 否则 {
        返回 SDL_SetError("SDL_ConvertPixels_YUV_to_YUV: Unsupported YUV conversion: %s -> %s", SDL_GetPixelFormatName(src_format),
                            SDL_GetPixelFormatName(dst_format));
    }
#否则
    返回 SDL_SetError("SDL not built with YUV support");
#endif
}
