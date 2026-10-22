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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ଅନ୍ତର୍ଭାଵ "SDL_pixels_c.h"
#ଅନ୍ତର୍ଭାଵ "SDL_yuv_c.h"

#ଅନ୍ତର୍ଭାଵ "yuv2rgb/yuv_rgb.h"


ସ୍ଥିର bool IsPlanar1x1Format(SDL_PixelFormat format)
{
    ଫେରନ୍ତୁ format == SDL_PIXELFORMAT_I444 || format == SDL_PIXELFORMAT_I4FL;
}

ସ୍ଥିର bool IsPlanar2x2Format(SDL_PixelFormat format)
{
    ଫେରନ୍ତୁ format == SDL_PIXELFORMAT_YV12 ||
           format == SDL_PIXELFORMAT_IYUV ||
           format == SDL_PIXELFORMAT_NV12 ||
           format == SDL_PIXELFORMAT_NV21 ||
           format == SDL_PIXELFORMAT_P010 ||
           format == SDL_PIXELFORMAT_I0FL;
}

ସ୍ଥିର bool IsPacked4Format(Uint32 format)
{
    ଫେରନ୍ତୁ format == SDL_PIXELFORMAT_YUY2 || format == SDL_PIXELFORMAT_UYVY || format == SDL_PIXELFORMAT_YVYU;
}

/*
 * Calculate YUV size and pitch. Check for overflow.
 * Output 'pitch' that can be used with SDL_ConvertPixels()
 */
bool SDL_CalculateYUVSize(SDL_PixelFormat format, ପୂର୍ଣ୍ଣସଂଖ୍ୟା w, ପୂର୍ଣ୍ଣସଂଖ୍ୟା h, size_t *size, size_t *pitch)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା sz_plane = 0, sz_plane_chroma = 0, sz_plane_packed = 0;

    ଯଦି (IsPlanar1x1Format(format)) {
        /* sz_plane == w * h * bpp; */
        size_t s1;
        ଯଦି (!SDL_size_mul_check_overflow(w, h, &s1)) {
            ଫେରନ୍ତୁ SDL_SetError("width * height would overflow");
        }
        ଯଦି (!SDL_size_mul_check_overflow(s1, SDL_BYTESPERPIXEL(format), &s1)) {
            ଫେରନ୍ତୁ SDL_SetError("width * height * bpp would overflow");
        }
        sz_plane = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)s1;
        sz_plane_chroma = sz_plane;
    } ଅନ୍ୟଥା ଯଦି (IsPlanar2x2Format(format)) {
        {
            /* sz_plane == w * h * bpp; */
            size_t s1;
            ଯଦି (!SDL_size_mul_check_overflow(w, h, &s1)) {
                ଫେରନ୍ତୁ SDL_SetError("width * height would overflow");
            }
            ଯଦି (!SDL_size_mul_check_overflow(s1, SDL_BYTESPERPIXEL(format), &s1)) {
                ଫେରନ୍ତୁ SDL_SetError("width * height * bpp would overflow");
            }
            sz_plane = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)s1;
        }

        {
            /* sz_plane_chroma == ((w + 1) / 2) * ((h + 1) / 2) * bpp; */
            size_t s1, s2, s3;
            ଯଦି (!SDL_size_add_check_overflow(w, 1, &s1)) {
                ଫେରନ୍ତୁ SDL_SetError("width + 1 would overflow");
            }
            s1 = s1 / 2;
            ଯଦି (!SDL_size_add_check_overflow(h, 1, &s2)) {
                ଫେରନ୍ତୁ SDL_SetError("height + 1 would overflow");
            }
            s2 = s2 / 2;
            ଯଦି (!SDL_size_mul_check_overflow(s1, s2, &s3)) {
                ଫେରନ୍ତୁ SDL_SetError("width * height would overflow");
            }
            ଯଦି (!SDL_size_mul_check_overflow(s3, SDL_BYTESPERPIXEL(format), &s3)) {
                ଫେରନ୍ତୁ SDL_SetError("width * height * bpp would overflow");
            }
            sz_plane_chroma = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)s3;
        }
    } ଅନ୍ୟଥା ଯଦି (IsPacked4Format(format)) {
        /* sz_plane_packed == ((w + 1) / 2) * h; */
        size_t s1, s2;
        ଯଦି (!SDL_size_add_check_overflow(w, 1, &s1)) {
            ଫେରନ୍ତୁ SDL_SetError("width + 1 would overflow");
        }
        s1 = s1 / 2;
        ଯଦି (!SDL_size_mul_check_overflow(s1, h, &s2)) {
            ଫେରନ୍ତୁ SDL_SetError("width * height would overflow");
        }
        sz_plane_packed = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା) s2;
    } ଅନ୍ୟଥା {
        ଫେରନ୍ତୁ SDL_Unsupported();
    }

    ବାଛ (format) {
    ସ୍ଥିତି SDL_PIXELFORMAT_YV12: /**< Planar mode: Y + V + U  (3 planes) */
    ସ୍ଥିତି SDL_PIXELFORMAT_IYUV: /**< Planar mode: Y + U + V  (3 planes) */
    ସ୍ଥିତି SDL_PIXELFORMAT_I444: /**< Planar mode: Y + U + V  (3 planes) */
    ସ୍ଥିତି SDL_PIXELFORMAT_I0FL: /**< Planar mode: Y + U + V  (3 planes) */
    ସ୍ଥିତି SDL_PIXELFORMAT_I4FL: /**< Planar mode: Y + U + V  (3 planes) */

        ଯଦି (pitch) {
            *pitch = w * SDL_BYTESPERPIXEL(format);
        }

        ଯଦି (size) {
            // dst_size == sz_plane + sz_plane_chroma + sz_plane_chroma;
            size_t s1, s2;
            ଯଦି (!SDL_size_add_check_overflow(sz_plane, sz_plane_chroma, &s1)) {
                ଫେରନ୍ତୁ SDL_SetError("Y + U would overflow");
            }
            ଯଦି (!SDL_size_add_check_overflow(s1, sz_plane_chroma, &s2)) {
                ଫେରନ୍ତୁ SDL_SetError("Y + U + V would overflow");
            }
            *size = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)s2;
        }
        ଭାଙ୍ଗ;

    ସ୍ଥିତି SDL_PIXELFORMAT_YUY2: /**< Packed mode: Y0+U0+Y1+V0 (1 plane) */
    ସ୍ଥିତି SDL_PIXELFORMAT_UYVY: /**< Packed mode: U0+Y0+V0+Y1 (1 plane) */
    ସ୍ଥିତି SDL_PIXELFORMAT_YVYU: /**< Packed mode: Y0+V0+Y1+U0 (1 plane) */

        ଯଦି (pitch) {
            /* pitch == ((w + 1) / 2) * 4; */
           size_t p1, p2;
           ଯଦି (!SDL_size_add_check_overflow(w, 1, &p1)) {
               ଫେରନ୍ତୁ SDL_SetError("width + 1 would overflow");
           }
           p1 = p1 / 2;
           ଯଦି (!SDL_size_mul_check_overflow(p1, 4, &p2)) {
               ଫେରନ୍ତୁ SDL_SetError("width * 4 would overflow");
           }
           *pitch = p2;
        }

        ଯଦି (size) {
            /* dst_size == 4 * sz_plane_packed; */
            size_t s1;
            ଯଦି (!SDL_size_mul_check_overflow(sz_plane_packed, 4, &s1)) {
                ଫେରନ୍ତୁ SDL_SetError("plane * 4 would overflow");
            }
            *size = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା) s1;
        }
        ଭାଙ୍ଗ;

    ସ୍ଥିତି SDL_PIXELFORMAT_NV12: /**< Planar mode: Y + U/V interleaved  (2 planes) */
    ସ୍ଥିତି SDL_PIXELFORMAT_NV21: /**< Planar mode: Y + V/U interleaved  (2 planes) */
    ସ୍ଥିତି SDL_PIXELFORMAT_P010: /**< Planar mode: Y + U/V interleaved, 10 bit  (2 planes) */
        ଯଦି (pitch) {
            *pitch = w * SDL_BYTESPERPIXEL(format);
        }

        ଯଦି (size) {
            // dst_size == sz_plane + sz_plane_chroma + sz_plane_chroma;
            size_t s1, s2;
            ଯଦି (!SDL_size_add_check_overflow(sz_plane, sz_plane_chroma, &s1)) {
                ଫେରନ୍ତୁ SDL_SetError("Y + U would overflow");
            }
            ଯଦି (!SDL_size_add_check_overflow(s1, sz_plane_chroma, &s2)) {
                ଫେରନ୍ତୁ SDL_SetError("Y + U + V would overflow");
            }
            *size = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା) s2;
        }
        ଭାଙ୍ଗ;

    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଫେରନ୍ତୁ SDL_Unsupported();
    }

    ଫେରନ୍ତୁ true;
}

#ifdef SDL_HAVE_YUV

ସ୍ଥିର bool GetYUVConversionType(SDL_Colorspace colorspace, ପୂର୍ଣ୍ଣସଂଖ୍ୟା w, ପୂର୍ଣ୍ଣସଂଖ୍ୟା h, ପୂର୍ଣ୍ଣସଂଖ୍ୟା bits_per_pixel, YCbCrType *yuv_type)
{
    ଯଦି (SDL_ISCOLORSPACE_MATRIX_BT601(colorspace)) {
        ଯଦି (SDL_ISCOLORSPACE_LIMITED_RANGE(colorspace)) {
            *yuv_type = YCBCR_601_LIMITED;
        } ଅନ୍ୟଥା {
            *yuv_type = YCBCR_601_FULL;
        }
        ଫେରନ୍ତୁ true;
    }

    ଯଦି (SDL_ISCOLORSPACE_MATRIX_BT709(colorspace)) {
        ଯଦି (SDL_ISCOLORSPACE_LIMITED_RANGE(colorspace)) {
            *yuv_type = YCBCR_709_LIMITED;
        } ଅନ୍ୟଥା {
            *yuv_type = YCBCR_709_FULL;
        }
        ଫେରନ୍ତୁ true;
    }

    ଯଦି (SDL_ISCOLORSPACE_MATRIX_BT2020_NCL(colorspace)) {
        ଯଦି (SDL_ISCOLORSPACE_FULL_RANGE(colorspace)) {
            *yuv_type = YCBCR_2020_NCL_FULL;
            ଫେରନ୍ତୁ true;
        }
    }

    ଯଦି (SDL_COLORSPACEMATRIX(colorspace) == SDL_MATRIX_COEFFICIENTS_UNSPECIFIED) {
        ବାଛ (bits_per_pixel) {
        ସ୍ଥିତି 8:
            ଯଦି (h <= YUV_SD_THRESHOLD) {
                ଯଦି (SDL_ISCOLORSPACE_LIMITED_RANGE(colorspace)) {
                    *yuv_type = YCBCR_601_LIMITED;
                } ଅନ୍ୟଥା {
                    *yuv_type = YCBCR_601_FULL;
                }
            } ଅନ୍ୟଥା {
                ଯଦି (SDL_ISCOLORSPACE_LIMITED_RANGE(colorspace)) {
                    *yuv_type = YCBCR_709_LIMITED;
                } ଅନ୍ୟଥା {
                    *yuv_type = YCBCR_709_FULL;
                }
            }
			ଫେରନ୍ତୁ true;
        ସ୍ଥିତି 10:
        ସ୍ଥିତି 16:
            ଯଦି (SDL_ISCOLORSPACE_FULL_RANGE(colorspace)) {
                *yuv_type = YCBCR_2020_NCL_FULL;
                ଫେରନ୍ତୁ true;
            }
            ଭାଙ୍ଗ;
        ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
            ଭାଙ୍ଗ;
        }
    }

    ଫେରନ୍ତୁ SDL_SetError("Unsupported YUV colorspace");
}

ସ୍ଥିର bool GetYUVPlanes(ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height, SDL_PixelFormat format, ଅଚଳ ଶୂନ୍ୟ *yuv, ପୂର୍ଣ୍ଣସଂଖ୍ୟା yuv_pitch,
                         ଅଚଳ Uint8 **y, ଅଚଳ Uint8 **u, ଅଚଳ Uint8 **v, Uint32 *y_stride, Uint32 *uv_stride)
{
    ଅଚଳ Uint8 *planes[3] = { ଖାଲି, ଖାଲି, ଖାଲି };
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା pitches[3] = { 0, 0, 0 };
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା uv_width;

    ବାଛ (format) {
    ସ୍ଥିତି SDL_PIXELFORMAT_YV12:
    ସ୍ଥିତି SDL_PIXELFORMAT_IYUV:
    ସ୍ଥିତି SDL_PIXELFORMAT_I0FL:
        pitches[0] = yuv_pitch;
        pitches[1] = ((pitches[0] / SDL_BYTESPERPIXEL(format) + 1) / 2) * SDL_BYTESPERPIXEL(format);
        pitches[2] = pitches[1];
        planes[0] = (ଅଚଳ Uint8 *)yuv;
        planes[1] = planes[0] + pitches[0] * height;
        planes[2] = planes[1] + pitches[1] * ((height + 1) / 2);
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_PIXELFORMAT_YUY2:
    ସ୍ଥିତି SDL_PIXELFORMAT_UYVY:
    ସ୍ଥିତି SDL_PIXELFORMAT_YVYU:
        pitches[0] = yuv_pitch;
        planes[0] = (ଅଚଳ Uint8 *)yuv;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_PIXELFORMAT_NV12:
    ସ୍ଥିତି SDL_PIXELFORMAT_NV21:
        pitches[0] = yuv_pitch;
        pitches[1] = 2 * ((pitches[0] + 1) / 2);
        planes[0] = (ଅଚଳ Uint8 *)yuv;
        planes[1] = planes[0] + pitches[0] * height;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_PIXELFORMAT_P010:
        pitches[0] = yuv_pitch;
        uv_width = ((width + 1) / 2) * 2;
        pitches[1] = SDL_max(pitches[0], (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)(uv_width * ଆକାର(Uint16)));
        planes[0] = (ଅଚଳ Uint8 *)yuv;
        planes[1] = planes[0] + pitches[0] * height;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_PIXELFORMAT_I444:
    ସ୍ଥିତି SDL_PIXELFORMAT_I4FL:
        pitches[0] = yuv_pitch;
        pitches[1] = pitches[0];
        pitches[2] = pitches[1];
        planes[0] = (ଅଚଳ Uint8 *)yuv;
        planes[1] = planes[0] + pitches[0] * height;
        planes[2] = planes[1] + pitches[1] * height;
        ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଫେରନ୍ତୁ SDL_SetError("GetYUVPlanes(): Unsupported YUV format: %s", SDL_GetPixelFormatName(format));
    }

    ବାଛ (format) {
    ସ୍ଥିତି SDL_PIXELFORMAT_YV12:
        *y = planes[0];
        *y_stride = pitches[0];
        *v = planes[1];
        *u = planes[2];
        *uv_stride = pitches[1];
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_PIXELFORMAT_IYUV:
    ସ୍ଥିତି SDL_PIXELFORMAT_I444:
    ସ୍ଥିତି SDL_PIXELFORMAT_I0FL:
    ସ୍ଥିତି SDL_PIXELFORMAT_I4FL:
        *y = planes[0];
        *y_stride = pitches[0];
        *v = planes[2];
        *u = planes[1];
        *uv_stride = pitches[1];
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_PIXELFORMAT_YUY2:
        *y = planes[0];
        *y_stride = pitches[0];
        *v = *y + 3;
        *u = *y + 1;
        *uv_stride = pitches[0];
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_PIXELFORMAT_UYVY:
        *y = planes[0] + 1;
        *y_stride = pitches[0];
        *v = *y + 1;
        *u = *y - 1;
        *uv_stride = pitches[0];
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_PIXELFORMAT_YVYU:
        *y = planes[0];
        *y_stride = pitches[0];
        *v = *y + 1;
        *u = *y + 3;
        *uv_stride = pitches[0];
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_PIXELFORMAT_NV12:
        *y = planes[0];
        *y_stride = pitches[0];
        *u = planes[1];
        *v = *u + 1;
        *uv_stride = pitches[1];
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_PIXELFORMAT_NV21:
        *y = planes[0];
        *y_stride = pitches[0];
        *v = planes[1];
        *u = *v + 1;
        *uv_stride = pitches[1];
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_PIXELFORMAT_P010:
        *y = planes[0];
        *y_stride = pitches[0];
        *u = planes[1];
        *v = *u + ଆକାର(Uint16);
        *uv_stride = pitches[1];
        ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        // Should have caught this above
        ଫେରନ୍ତୁ SDL_SetError("GetYUVPlanes[2]: Unsupported YUV format: %s", SDL_GetPixelFormatName(format));
    }
    ଫେରନ୍ତୁ true;
}

#ifdef SDL_SSE2_INTRINSICS
ସ୍ଥିର bool SDL_TARGETING("sse2") yuv_rgb_sse(
    SDL_PixelFormat src_format, SDL_PixelFormat dst_format,
    Uint32 width, Uint32 height,
    ଅଚଳ Uint8 *y, ଅଚଳ Uint8 *u, ଅଚଳ Uint8 *v, Uint32 y_stride, Uint32 uv_stride,
    Uint8 *rgb, Uint32 rgb_stride,
    YCbCrType yuv_type)
{
    ଯଦି (!SDL_HasSSE2()) {
        ଫେରନ୍ତୁ false;
    }

    ଯଦି (src_format == SDL_PIXELFORMAT_YV12 ||
        src_format == SDL_PIXELFORMAT_IYUV) {

        ବାଛ (dst_format) {
        ସ୍ଥିତି SDL_PIXELFORMAT_RGB565:
            yuv420_rgb565_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ଫେରନ୍ତୁ true;
        ସ୍ଥିତି SDL_PIXELFORMAT_RGB24:
            yuv420_rgb24_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ଫେରନ୍ତୁ true;
        ସ୍ଥିତି SDL_PIXELFORMAT_RGBX8888:
        ସ୍ଥିତି SDL_PIXELFORMAT_RGBA8888:
            yuv420_rgba_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ଫେରନ୍ତୁ true;
        ସ୍ଥିତି SDL_PIXELFORMAT_BGRX8888:
        ସ୍ଥିତି SDL_PIXELFORMAT_BGRA8888:
            yuv420_bgra_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ଫେରନ୍ତୁ true;
        ସ୍ଥିତି SDL_PIXELFORMAT_XRGB8888:
        ସ୍ଥିତି SDL_PIXELFORMAT_ARGB8888:
            yuv420_argb_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ଫେରନ୍ତୁ true;
        ସ୍ଥିତି SDL_PIXELFORMAT_XBGR8888:
        ସ୍ଥିତି SDL_PIXELFORMAT_ABGR8888:
            yuv420_abgr_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ଫେରନ୍ତୁ true;
        ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
            ଭାଙ୍ଗ;
        }
    }

    ଯଦି (src_format == SDL_PIXELFORMAT_YUY2 ||
        src_format == SDL_PIXELFORMAT_UYVY ||
        src_format == SDL_PIXELFORMAT_YVYU) {

        ବାଛ (dst_format) {
        ସ୍ଥିତି SDL_PIXELFORMAT_RGB565:
            yuv422_rgb565_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ଫେରନ୍ତୁ true;
        ସ୍ଥିତି SDL_PIXELFORMAT_RGB24:
            yuv422_rgb24_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ଫେରନ୍ତୁ true;
        ସ୍ଥିତି SDL_PIXELFORMAT_RGBX8888:
        ସ୍ଥିତି SDL_PIXELFORMAT_RGBA8888:
            yuv422_rgba_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ଫେରନ୍ତୁ true;
        ସ୍ଥିତି SDL_PIXELFORMAT_BGRX8888:
        ସ୍ଥିତି SDL_PIXELFORMAT_BGRA8888:
            yuv422_bgra_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ଫେରନ୍ତୁ true;
        ସ୍ଥିତି SDL_PIXELFORMAT_XRGB8888:
        ସ୍ଥିତି SDL_PIXELFORMAT_ARGB8888:
            yuv422_argb_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ଫେରନ୍ତୁ true;
        ସ୍ଥିତି SDL_PIXELFORMAT_XBGR8888:
        ସ୍ଥିତି SDL_PIXELFORMAT_ABGR8888:
            yuv422_abgr_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ଫେରନ୍ତୁ true;
        ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
            ଭାଙ୍ଗ;
        }
    }

    ଯଦି (src_format == SDL_PIXELFORMAT_NV12 ||
        src_format == SDL_PIXELFORMAT_NV21) {

        ବାଛ (dst_format) {
        ସ୍ଥିତି SDL_PIXELFORMAT_RGB565:
            yuvnv12_rgb565_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ଫେରନ୍ତୁ true;
        ସ୍ଥିତି SDL_PIXELFORMAT_RGB24:
            yuvnv12_rgb24_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ଫେରନ୍ତୁ true;
        ସ୍ଥିତି SDL_PIXELFORMAT_RGBX8888:
        ସ୍ଥିତି SDL_PIXELFORMAT_RGBA8888:
            yuvnv12_rgba_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ଫେରନ୍ତୁ true;
        ସ୍ଥିତି SDL_PIXELFORMAT_BGRX8888:
        ସ୍ଥିତି SDL_PIXELFORMAT_BGRA8888:
            yuvnv12_bgra_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ଫେରନ୍ତୁ true;
        ସ୍ଥିତି SDL_PIXELFORMAT_XRGB8888:
        ସ୍ଥିତି SDL_PIXELFORMAT_ARGB8888:
            yuvnv12_argb_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ଫେରନ୍ତୁ true;
        ସ୍ଥିତି SDL_PIXELFORMAT_XBGR8888:
        ସ୍ଥିତି SDL_PIXELFORMAT_ABGR8888:
            yuvnv12_abgr_sseu(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ଫେରନ୍ତୁ true;
        ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
            ଭାଙ୍ଗ;
        }
    }
    ଫେରନ୍ତୁ false;
}
#ଅନ୍ୟଥା
ସ୍ଥିର bool yuv_rgb_sse(
    SDL_PixelFormat src_format, SDL_PixelFormat dst_format,
    Uint32 width, Uint32 height,
    ଅଚଳ Uint8 *y, ଅଚଳ Uint8 *u, ଅଚଳ Uint8 *v, Uint32 y_stride, Uint32 uv_stride,
    Uint8 *rgb, Uint32 rgb_stride,
    YCbCrType yuv_type)
{
    ଫେରନ୍ତୁ false;
}
#endif

#ifdef SDL_LSX_INTRINSICS
ସ୍ଥିର bool yuv_rgb_lsx(
    SDL_PixelFormat src_format, SDL_PixelFormat dst_format,
    Uint32 width, Uint32 height,
    ଅଚଳ Uint8 *y, ଅଚଳ Uint8 *u, ଅଚଳ Uint8 *v, Uint32 y_stride, Uint32 uv_stride,
    Uint8 *rgb, Uint32 rgb_stride,
    YCbCrType yuv_type)
{
    ଯଦି (!SDL_HasLSX()) {
        ଫେରନ୍ତୁ false;
    }
    ଯଦି (src_format == SDL_PIXELFORMAT_YV12 ||
        src_format == SDL_PIXELFORMAT_IYUV) {

        ବାଛ (dst_format) {
        ସ୍ଥିତି SDL_PIXELFORMAT_RGB24:
            yuv420_rgb24_lsx(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ଫେରନ୍ତୁ true;
        ସ୍ଥିତି SDL_PIXELFORMAT_RGBX8888:
        ସ୍ଥିତି SDL_PIXELFORMAT_RGBA8888:
            yuv420_rgba_lsx(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ଫେରନ୍ତୁ true;
        ସ୍ଥିତି SDL_PIXELFORMAT_BGRX8888:
        ସ୍ଥିତି SDL_PIXELFORMAT_BGRA8888:
            yuv420_bgra_lsx(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ଫେରନ୍ତୁ true;
        ସ୍ଥିତି SDL_PIXELFORMAT_XRGB8888:
        ସ୍ଥିତି SDL_PIXELFORMAT_ARGB8888:
            yuv420_argb_lsx(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ଫେରନ୍ତୁ true;
        ସ୍ଥିତି SDL_PIXELFORMAT_XBGR8888:
        ସ୍ଥିତି SDL_PIXELFORMAT_ABGR8888:
            yuv420_abgr_lsx(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ଫେରନ୍ତୁ true;
        ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
            ଭାଙ୍ଗ;
        }
    }
    ଫେରନ୍ତୁ false;
}
#ଅନ୍ୟଥା
ସ୍ଥିର bool yuv_rgb_lsx(
    SDL_PixelFormat src_format, SDL_PixelFormat dst_format,
    Uint32 width, Uint32 height,
    ଅଚଳ Uint8 *y, ଅଚଳ Uint8 *u, ଅଚଳ Uint8 *v, Uint32 y_stride, Uint32 uv_stride,
    Uint8 *rgb, Uint32 rgb_stride,
    YCbCrType yuv_type)
{
    ଫେରନ୍ତୁ false;
}
#endif

ସ୍ଥିର bool yuv_rgb_std(
    SDL_PixelFormat src_format, SDL_PixelFormat dst_format,
    Uint32 width, Uint32 height,
    ଅଚଳ Uint8 *y, ଅଚଳ Uint8 *u, ଅଚଳ Uint8 *v, Uint32 y_stride, Uint32 uv_stride,
    Uint8 *rgb, Uint32 rgb_stride,
    YCbCrType yuv_type)
{
    ଯଦି (src_format == SDL_PIXELFORMAT_YV12 ||
        src_format == SDL_PIXELFORMAT_IYUV) {

        ବାଛ (dst_format) {
        ସ୍ଥିତି SDL_PIXELFORMAT_RGB565:
            yuv420_rgb565_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ଫେରନ୍ତୁ true;
        ସ୍ଥିତି SDL_PIXELFORMAT_RGB24:
            yuv420_rgb24_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ଫେରନ୍ତୁ true;
        ସ୍ଥିତି SDL_PIXELFORMAT_RGBX8888:
        ସ୍ଥିତି SDL_PIXELFORMAT_RGBA8888:
            yuv420_rgba_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ଫେରନ୍ତୁ true;
        ସ୍ଥିତି SDL_PIXELFORMAT_BGRX8888:
        ସ୍ଥିତି SDL_PIXELFORMAT_BGRA8888:
            yuv420_bgra_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ଫେରନ୍ତୁ true;
        ସ୍ଥିତି SDL_PIXELFORMAT_XRGB8888:
        ସ୍ଥିତି SDL_PIXELFORMAT_ARGB8888:
            yuv420_argb_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ଫେରନ୍ତୁ true;
        ସ୍ଥିତି SDL_PIXELFORMAT_XBGR8888:
        ସ୍ଥିତି SDL_PIXELFORMAT_ABGR8888:
            yuv420_abgr_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ଫେରନ୍ତୁ true;
        ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
            ଭାଙ୍ଗ;
        }
    }

    ଯଦି (src_format == SDL_PIXELFORMAT_I444) {

        ବାଛ (dst_format) {
        ସ୍ଥିତି SDL_PIXELFORMAT_RGBX8888:
        ସ୍ଥିତି SDL_PIXELFORMAT_RGBA8888:
            yuv444_rgba_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ଫେରନ୍ତୁ true;
        ସ୍ଥିତି SDL_PIXELFORMAT_BGRX8888:
        ସ୍ଥିତି SDL_PIXELFORMAT_BGRA8888:
            yuv444_bgra_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ଫେରନ୍ତୁ true;
        ସ୍ଥିତି SDL_PIXELFORMAT_XRGB8888:
        ସ୍ଥିତି SDL_PIXELFORMAT_ARGB8888:
            yuv444_argb_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ଫେରନ୍ତୁ true;
        ସ୍ଥିତି SDL_PIXELFORMAT_XBGR8888:
        ସ୍ଥିତି SDL_PIXELFORMAT_ABGR8888:
            yuv444_abgr_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ଫେରନ୍ତୁ true;
        ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
            ଭାଙ୍ଗ;
        }
    }

    ଯଦି (src_format == SDL_PIXELFORMAT_YUY2 ||
        src_format == SDL_PIXELFORMAT_UYVY ||
        src_format == SDL_PIXELFORMAT_YVYU) {

        ବାଛ (dst_format) {
        ସ୍ଥିତି SDL_PIXELFORMAT_RGB565:
            yuv422_rgb565_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ଫେରନ୍ତୁ true;
        ସ୍ଥିତି SDL_PIXELFORMAT_RGB24:
            yuv422_rgb24_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ଫେରନ୍ତୁ true;
        ସ୍ଥିତି SDL_PIXELFORMAT_RGBX8888:
        ସ୍ଥିତି SDL_PIXELFORMAT_RGBA8888:
            yuv422_rgba_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ଫେରନ୍ତୁ true;
        ସ୍ଥିତି SDL_PIXELFORMAT_BGRX8888:
        ସ୍ଥିତି SDL_PIXELFORMAT_BGRA8888:
            yuv422_bgra_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ଫେରନ୍ତୁ true;
        ସ୍ଥିତି SDL_PIXELFORMAT_XRGB8888:
        ସ୍ଥିତି SDL_PIXELFORMAT_ARGB8888:
            yuv422_argb_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ଫେରନ୍ତୁ true;
        ସ୍ଥିତି SDL_PIXELFORMAT_XBGR8888:
        ସ୍ଥିତି SDL_PIXELFORMAT_ABGR8888:
            yuv422_abgr_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ଫେରନ୍ତୁ true;
        ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
            ଭାଙ୍ଗ;
        }
    }

    ଯଦି (src_format == SDL_PIXELFORMAT_NV12 ||
        src_format == SDL_PIXELFORMAT_NV21) {

        ବାଛ (dst_format) {
        ସ୍ଥିତି SDL_PIXELFORMAT_RGB565:
            yuvnv12_rgb565_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ଫେରନ୍ତୁ true;
        ସ୍ଥିତି SDL_PIXELFORMAT_RGB24:
            yuvnv12_rgb24_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ଫେରନ୍ତୁ true;
        ସ୍ଥିତି SDL_PIXELFORMAT_RGBX8888:
        ସ୍ଥିତି SDL_PIXELFORMAT_RGBA8888:
            yuvnv12_rgba_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ଫେରନ୍ତୁ true;
        ସ୍ଥିତି SDL_PIXELFORMAT_BGRX8888:
        ସ୍ଥିତି SDL_PIXELFORMAT_BGRA8888:
            yuvnv12_bgra_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ଫେରନ୍ତୁ true;
        ସ୍ଥିତି SDL_PIXELFORMAT_XRGB8888:
        ସ୍ଥିତି SDL_PIXELFORMAT_ARGB8888:
            yuvnv12_argb_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ଫେରନ୍ତୁ true;
        ସ୍ଥିତି SDL_PIXELFORMAT_XBGR8888:
        ସ୍ଥିତି SDL_PIXELFORMAT_ABGR8888:
            yuvnv12_abgr_std(width, height, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ଫେରନ୍ତୁ true;
        ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
            ଭାଙ୍ଗ;
        }
    }

    ଯଦି (src_format == SDL_PIXELFORMAT_P010) {
        ବାଛ (dst_format) {
        ସ୍ଥିତି SDL_PIXELFORMAT_XBGR2101010:
            yuvp010_xbgr2101010_std(width, height, (ଅଚଳ uint16_t *)y, (ଅଚଳ uint16_t *)u, (ଅଚଳ uint16_t *)v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ଫେରନ୍ତୁ true;
        ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
            ଭାଙ୍ଗ;
        }
    }

    ଯଦି (src_format == SDL_PIXELFORMAT_I0FL) {
        ବାଛ (dst_format) {
        ସ୍ଥିତି SDL_PIXELFORMAT_RGB48:
            yuvi0fl_rgb48_std(width, height, (ଅଚଳ uint16_t *)y, (ଅଚଳ uint16_t *)u, (ଅଚଳ uint16_t *)v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ଫେରନ୍ତୁ true;
        ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
            ଭାଙ୍ଗ;
        }
    }

    ଯଦି (src_format == SDL_PIXELFORMAT_I4FL) {
        ବାଛ (dst_format) {
        ସ୍ଥିତି SDL_PIXELFORMAT_RGB48:
            yuvi4fl_rgb48_std(width, height, (ଅଚଳ uint16_t *)y, (ଅଚଳ uint16_t *)u, (ଅଚଳ uint16_t *)v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ଫେରନ୍ତୁ true;
        ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
            ଭାଙ୍ଗ;
        }
    }
    ଫେରନ୍ତୁ false;
}

bool SDL_ConvertPixels_YUV_to_RGB(ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height,
                                  SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ଅଚଳ ଶୂନ୍ୟ *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_pitch,
                                  SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, ଶୂନ୍ୟ *dst, ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_pitch)
{
    ଅଚଳ Uint8 *y = ଖାଲି;
    ଅଚଳ Uint8 *u = ଖାଲି;
    ଅଚଳ Uint8 *v = ଖାଲି;
    Uint32 y_stride = 0;
    Uint32 uv_stride = 0;
    YCbCrType yuv_type = YCBCR_601_LIMITED;

    ଯଦି (!GetYUVPlanes(width, height, src_format, src, src_pitch, &y, &u, &v, &y_stride, &uv_stride)) {
        ଫେରନ୍ତୁ false;
    }

    ଯଦି (!GetYUVConversionType(src_colorspace, width, height, 8, &yuv_type)) {
        ଫେରନ୍ତୁ false;
    }

    ଯଦି (yuv_rgb_sse(src_format, dst_format, width, height, y, u, v, y_stride, uv_stride, (Uint8 *)dst, dst_pitch, yuv_type)) {
        ଫେରନ୍ତୁ true;
    }

    ଯଦି (yuv_rgb_lsx(src_format, dst_format, width, height, y, u, v, y_stride, uv_stride, (Uint8 *)dst, dst_pitch, yuv_type)) {
        ଫେରନ୍ତୁ true;
    }

    ଯଦି (yuv_rgb_std(src_format, dst_format, width, height, y, u, v, y_stride, uv_stride, (Uint8 *)dst, dst_pitch, yuv_type)) {
        ଫେରନ୍ତୁ true;
    }

    // No fast path for the RGB format, instead convert using an intermediate buffer
    ଯଦି (src_format == SDL_PIXELFORMAT_P010 && dst_format != SDL_PIXELFORMAT_XBGR2101010) {
        bool result;
        ଶୂନ୍ୟ *tmp;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା tmp_pitch = (width * ଆକାର(Uint32));

        tmp = SDL_malloc((size_t)tmp_pitch * height);
        ଯଦି (!tmp) {
            ଫେରନ୍ତୁ false;
        }

        // convert src/src_format to tmp/XBGR2101010
        result = SDL_ConvertPixels_YUV_to_RGB(width, height, src_format, src_colorspace, src_properties, src, src_pitch, SDL_PIXELFORMAT_XBGR2101010, src_colorspace, src_properties, tmp, tmp_pitch);
        ଯଦି (!result) {
            SDL_free(tmp);
            ଫେରନ୍ତୁ false;
        }

        // convert tmp/XBGR2101010 to dst/RGB
        result = SDL_ConvertPixelsAndColorspace(width, height, SDL_PIXELFORMAT_XBGR2101010, src_colorspace, src_properties, tmp, tmp_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
        SDL_free(tmp);
        ଫେରନ୍ତୁ result;
    }

    ଯଦି ((src_format == SDL_PIXELFORMAT_I0FL || src_format == SDL_PIXELFORMAT_I4FL) && dst_format != SDL_PIXELFORMAT_RGB48) {
        bool result;
        ଶୂନ୍ୟ *tmp;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା tmp_pitch = (width * 3 * ଆକାର(Uint16));

        tmp = SDL_malloc((size_t)tmp_pitch * height);
        ଯଦି (!tmp) {
            ଫେରନ୍ତୁ false;
        }

        // convert src/src_format to tmp/RGB48
        result = SDL_ConvertPixels_YUV_to_RGB(width, height, src_format, src_colorspace, src_properties, src, src_pitch, SDL_PIXELFORMAT_RGB48, src_colorspace, src_properties, tmp, tmp_pitch);
        ଯଦି (!result) {
            SDL_free(tmp);
            ଫେରନ୍ତୁ false;
        }

        // convert tmp/RGB48 to dst/RGB
        result = SDL_ConvertPixelsAndColorspace(width, height, SDL_PIXELFORMAT_RGB48, src_colorspace, src_properties, tmp, tmp_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
        SDL_free(tmp);
        ଫେରନ୍ତୁ result;
    }

    ଯଦି (dst_format != SDL_PIXELFORMAT_ARGB8888) {
        bool result;
        ଶୂନ୍ୟ *tmp;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା tmp_pitch = (width * ଆକାର(Uint32));

        tmp = SDL_malloc((size_t)tmp_pitch * height);
        ଯଦି (!tmp) {
            ଫେରନ୍ତୁ false;
        }

        // convert src/src_format to tmp/ARGB8888
        result = SDL_ConvertPixels_YUV_to_RGB(width, height, src_format, src_colorspace, src_properties, src, src_pitch, SDL_PIXELFORMAT_ARGB8888, SDL_COLORSPACE_SRGB, 0, tmp, tmp_pitch);
        ଯଦି (!result) {
            SDL_free(tmp);
            ଫେରନ୍ତୁ false;
        }

        // convert tmp/ARGB8888 to dst/RGB
        result = SDL_ConvertPixelsAndColorspace(width, height, SDL_PIXELFORMAT_ARGB8888, SDL_COLORSPACE_SRGB, 0, tmp, tmp_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
        SDL_free(tmp);
        ଫେରନ୍ତୁ result;
    }

    ଫେରନ୍ତୁ SDL_SetError("Unsupported YUV conversion");
}

ସଂରଚନା RGB2YUVFactors
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା y_offset;
    ଦଶମିକ y[3]; // Rfactor, Gfactor, Bfactor
    ଦଶମିକ u[3]; // Rfactor, Gfactor, Bfactor
    ଦଶମିକ v[3]; // Rfactor, Gfactor, Bfactor
};

ସ୍ଥିର ସଂରଚନା RGB2YUVFactors RGB2YUVFactorTables[] = {
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

ସ୍ଥିର bool SDL_ConvertPixels_XRGB8888_to_YUV(ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height, ଅଚଳ ଶୂନ୍ୟ *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_pitch, SDL_PixelFormat dst_format, ଶୂନ୍ୟ *dst, ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_pitch, YCbCrType yuv_type)
{
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_pitch_x_2 = src_pitch * 2;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା height_half = height / 2;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା height_remainder = (height & 0x1);
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା width_half = width / 2;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା width_remainder = (width & 0x1);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, j;

    ଅଚଳ ସଂରଚନା RGB2YUVFactors *cvt = &RGB2YUVFactorTables[yuv_type];

#define MAKE_Y(r, g, b) (Uint8)SDL_clamp(((ପୂର୍ଣ୍ଣସଂଖ୍ୟା)(cvt->y[0] * (r) + cvt->y[1] * (g) + cvt->y[2] * (b) + 0.5f) + cvt->y_offset), 0, 255)
#define MAKE_U(r, g, b) (Uint8)SDL_clamp(((ପୂର୍ଣ୍ଣସଂଖ୍ୟା)(cvt->u[0] * (r) + cvt->u[1] * (g) + cvt->u[2] * (b) + 0.5f) + 128), 0, 255)
#define MAKE_V(r, g, b) (Uint8)SDL_clamp(((ପୂର୍ଣ୍ଣସଂଖ୍ୟା)(cvt->v[0] * (r) + cvt->v[1] * (g) + cvt->v[2] * (b) + 0.5f) + 128), 0, 255)

#define READ_2x2_PIXELS                                                                                     \
    ଅଚଳ Uint32 p1 = ((ଅଚଳ Uint32 *)curr_row)[2 * i];                                                    \
    ଅଚଳ Uint32 p2 = ((ଅଚଳ Uint32 *)curr_row)[2 * i + 1];                                                \
    ଅଚଳ Uint32 p3 = ((ଅଚଳ Uint32 *)next_row)[2 * i];                                                    \
    ଅଚଳ Uint32 p4 = ((ଅଚଳ Uint32 *)next_row)[2 * i + 1];                                                \
    ଅଚଳ Uint32 r = ((p1 & 0x00ff0000) + (p2 & 0x00ff0000) + (p3 & 0x00ff0000) + (p4 & 0x00ff0000)) >> 18; \
    ଅଚଳ Uint32 g = ((p1 & 0x0000ff00) + (p2 & 0x0000ff00) + (p3 & 0x0000ff00) + (p4 & 0x0000ff00)) >> 10; \
    ଅଚଳ Uint32 b = ((p1 & 0x000000ff) + (p2 & 0x000000ff) + (p3 & 0x000000ff) + (p4 & 0x000000ff)) >> 2

#define READ_2x1_PIXELS                                             \
    ଅଚଳ Uint32 p1 = ((ଅଚଳ Uint32 *)curr_row)[2 * i];            \
    ଅଚଳ Uint32 p2 = ((ଅଚଳ Uint32 *)next_row)[2 * i];            \
    ଅଚଳ Uint32 r = ((p1 & 0x00ff0000) + (p2 & 0x00ff0000)) >> 17; \
    ଅଚଳ Uint32 g = ((p1 & 0x0000ff00) + (p2 & 0x0000ff00)) >> 9;  \
    ଅଚଳ Uint32 b = ((p1 & 0x000000ff) + (p2 & 0x000000ff)) >> 1

#define READ_1x2_PIXELS                                             \
    ଅଚଳ Uint32 p1 = ((ଅଚଳ Uint32 *)curr_row)[2 * i];            \
    ଅଚଳ Uint32 p2 = ((ଅଚଳ Uint32 *)curr_row)[2 * i + 1];        \
    ଅଚଳ Uint32 r = ((p1 & 0x00ff0000) + (p2 & 0x00ff0000)) >> 17; \
    ଅଚଳ Uint32 g = ((p1 & 0x0000ff00) + (p2 & 0x0000ff00)) >> 9;  \
    ଅଚଳ Uint32 b = ((p1 & 0x000000ff) + (p2 & 0x000000ff)) >> 1

#define READ_1x1_PIXEL                                  \
    ଅଚଳ Uint32 p = ((ଅଚଳ Uint32 *)curr_row)[2 * i]; \
    ଅଚଳ Uint32 r = (p & 0x00ff0000) >> 16;            \
    ଅଚଳ Uint32 g = (p & 0x0000ff00) >> 8;             \
    ଅଚଳ Uint32 b = (p & 0x000000ff)

#define READ_TWO_RGB_PIXELS                                  \
    ଅଚଳ Uint32 p = ((ଅଚଳ Uint32 *)curr_row)[2 * i];      \
    ଅଚଳ Uint32 r = (p & 0x00ff0000) >> 16;                 \
    ଅଚଳ Uint32 g = (p & 0x0000ff00) >> 8;                  \
    ଅଚଳ Uint32 b = (p & 0x000000ff);                       \
    ଅଚଳ Uint32 p1 = ((ଅଚଳ Uint32 *)curr_row)[2 * i + 1]; \
    ଅଚଳ Uint32 r1 = (p1 & 0x00ff0000) >> 16;               \
    ଅଚଳ Uint32 g1 = (p1 & 0x0000ff00) >> 8;                \
    ଅଚଳ Uint32 b1 = (p1 & 0x000000ff);                     \
    ଅଚଳ Uint32 R = (r + r1) / 2;                           \
    ଅଚଳ Uint32 G = (g + g1) / 2;                           \
    ଅଚଳ Uint32 B = (b + b1) / 2

#define READ_ONE_RGB_PIXEL READ_1x1_PIXEL

    ବାଛ (dst_format) {
    ସ୍ଥିତି SDL_PIXELFORMAT_YV12:
    ସ୍ଥିତି SDL_PIXELFORMAT_IYUV:
    ସ୍ଥିତି SDL_PIXELFORMAT_I444:
    ସ୍ଥିତି SDL_PIXELFORMAT_NV12:
    ସ୍ଥିତି SDL_PIXELFORMAT_NV21:
    {
        ଅଚଳ Uint8 *curr_row, *next_row;

        Uint8 *plane_y;
        Uint8 *plane_u;
        Uint8 *plane_v;
        Uint8 *plane_interleaved_uv;
        Uint32 y_stride, uv_stride, y_skip, uv_skip;

        ଯଦି (!GetYUVPlanes(width, height, dst_format, dst, dst_pitch,
                          (ଅଚଳ Uint8 **)&plane_y, (ଅଚଳ Uint8 **)&plane_u, (ଅଚଳ Uint8 **)&plane_v,
                          &y_stride, &uv_stride)) {
            ଫେରନ୍ତୁ false;
        }

        plane_interleaved_uv = (plane_y + height * y_stride);
        y_skip = (y_stride - width);

        curr_row = (ଅଚଳ Uint8 *)src;

        // Write Y plane
        ପାଇଁ (j = 0; j < height; j++) {
            ପାଇଁ (i = 0; i < width; i++) {
                ଅଚଳ Uint32 p1 = ((ଅଚଳ Uint32 *)curr_row)[i];
                ଅଚଳ Uint32 r = (p1 & 0x00ff0000) >> 16;
                ଅଚଳ Uint32 g = (p1 & 0x0000ff00) >> 8;
                ଅଚଳ Uint32 b = (p1 & 0x000000ff);
                *plane_y++ = MAKE_Y(r, g, b);
            }
            plane_y += y_skip;
            curr_row += src_pitch;
        }

        curr_row = (ଅଚଳ Uint8 *)src;
        next_row = (ଅଚଳ Uint8 *)src;
        next_row += src_pitch;

        ଯଦି (dst_format == SDL_PIXELFORMAT_YV12 || dst_format == SDL_PIXELFORMAT_IYUV) {
            // Write UV planes, not interleaved
            uv_skip = (uv_stride - (width + 1) / 2);
            ପାଇଁ (j = 0; j < height_half; j++) {
                ପାଇଁ (i = 0; i < width_half; i++) {
                    READ_2x2_PIXELS;
                    *plane_u++ = MAKE_U(r, g, b);
                    *plane_v++ = MAKE_V(r, g, b);
                }
                ଯଦି (width_remainder) {
                    READ_2x1_PIXELS;
                    *plane_u++ = MAKE_U(r, g, b);
                    *plane_v++ = MAKE_V(r, g, b);
                }
                plane_u += uv_skip;
                plane_v += uv_skip;
                curr_row += src_pitch_x_2;
                next_row += src_pitch_x_2;
            }
            ଯଦି (height_remainder) {
                ପାଇଁ (i = 0; i < width_half; i++) {
                    READ_1x2_PIXELS;
                    *plane_u++ = MAKE_U(r, g, b);
                    *plane_v++ = MAKE_V(r, g, b);
                }
                ଯଦି (width_remainder) {
                    READ_1x1_PIXEL;
                    *plane_u++ = MAKE_U(r, g, b);
                    *plane_v++ = MAKE_V(r, g, b);
                }
                plane_u += uv_skip;
                plane_v += uv_skip;
            }
        } ଅନ୍ୟଥା ଯଦି (dst_format == SDL_PIXELFORMAT_I444) {
            // Write UV planes, not interleaved
            uv_skip = (uv_stride - width);
            ପାଇଁ (j = 0; j < height; j++) {
                ପାଇଁ (i = 0; i < width; i++) {
                    ଅଚଳ Uint32 p1 = ((ଅଚଳ Uint32 *)curr_row)[i];
                    ଅଚଳ Uint32 r = (p1 & 0x00ff0000) >> 16;
                    ଅଚଳ Uint32 g = (p1 & 0x0000ff00) >> 8;
                    ଅଚଳ Uint32 b = (p1 & 0x000000ff);
                    *plane_u++ = MAKE_U(r, g, b);
                    *plane_v++ = MAKE_V(r, g, b);
                }
                plane_u += uv_skip;
                plane_v += uv_skip;
                curr_row += src_pitch;
            }
        } ଅନ୍ୟଥା ଯଦି (dst_format == SDL_PIXELFORMAT_NV12) {
            uv_skip = (uv_stride - ((width + 1) / 2) * 2);
            ପାଇଁ (j = 0; j < height_half; j++) {
                ପାଇଁ (i = 0; i < width_half; i++) {
                    READ_2x2_PIXELS;
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                }
                ଯଦି (width_remainder) {
                    READ_2x1_PIXELS;
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                }
                plane_interleaved_uv += uv_skip;
                curr_row += src_pitch_x_2;
                next_row += src_pitch_x_2;
            }
            ଯଦି (height_remainder) {
                ପାଇଁ (i = 0; i < width_half; i++) {
                    READ_1x2_PIXELS;
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                }
                ଯଦି (width_remainder) {
                    READ_1x1_PIXEL;
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                }
            }
        } ଅନ୍ୟଥା /* dst_format == SDL_PIXELFORMAT_NV21 */ {
            uv_skip = (uv_stride - ((width + 1) / 2) * 2);
            ପାଇଁ (j = 0; j < height_half; j++) {
                ପାଇଁ (i = 0; i < width_half; i++) {
                    READ_2x2_PIXELS;
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                }
                ଯଦି (width_remainder) {
                    READ_2x1_PIXELS;
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                }
                plane_interleaved_uv += uv_skip;
                curr_row += src_pitch_x_2;
                next_row += src_pitch_x_2;
            }
            ଯଦି (height_remainder) {
                ପାଇଁ (i = 0; i < width_half; i++) {
                    READ_1x2_PIXELS;
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                }
                ଯଦି (width_remainder) {
                    READ_1x1_PIXEL;
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                }
            }
        }
    } ଭାଙ୍ଗ;

    ସ୍ଥିତି SDL_PIXELFORMAT_YUY2:
    ସ୍ଥିତି SDL_PIXELFORMAT_UYVY:
    ସ୍ଥିତି SDL_PIXELFORMAT_YVYU:
    {
        ଅଚଳ Uint8 *curr_row = (ଅଚଳ Uint8 *)src;
        Uint8 *plane = (Uint8 *)dst;
        ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା row_size = (4 * ((width + 1) / 2));
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା plane_skip;

        ଯଦି (dst_pitch < row_size) {
            ଫେରନ୍ତୁ SDL_SetError("Destination pitch is too small, expected at least %d", row_size);
        }
        plane_skip = (dst_pitch - row_size);

        // Write YUV plane, packed
        ଯଦି (dst_format == SDL_PIXELFORMAT_YUY2) {
            ପାଇଁ (j = 0; j < height; j++) {
                ପାଇଁ (i = 0; i < width_half; i++) {
                    READ_TWO_RGB_PIXELS;
                    // Y U Y1 V
                    *plane++ = MAKE_Y(r, g, b);
                    *plane++ = MAKE_U(R, G, B);
                    *plane++ = MAKE_Y(r1, g1, b1);
                    *plane++ = MAKE_V(R, G, B);
                }
                ଯଦି (width_remainder) {
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
        } ଅନ୍ୟଥା ଯଦି (dst_format == SDL_PIXELFORMAT_UYVY) {
            ପାଇଁ (j = 0; j < height; j++) {
                ପାଇଁ (i = 0; i < width_half; i++) {
                    READ_TWO_RGB_PIXELS;
                    // U Y V Y1
                    *plane++ = MAKE_U(R, G, B);
                    *plane++ = MAKE_Y(r, g, b);
                    *plane++ = MAKE_V(R, G, B);
                    *plane++ = MAKE_Y(r1, g1, b1);
                }
                ଯଦି (width_remainder) {
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
        } ଅନ୍ୟଥା ଯଦି (dst_format == SDL_PIXELFORMAT_YVYU) {
            ପାଇଁ (j = 0; j < height; j++) {
                ପାଇଁ (i = 0; i < width_half; i++) {
                    READ_TWO_RGB_PIXELS;
                    // Y V Y1 U
                    *plane++ = MAKE_Y(r, g, b);
                    *plane++ = MAKE_V(R, G, B);
                    *plane++ = MAKE_Y(r1, g1, b1);
                    *plane++ = MAKE_U(R, G, B);
                }
                ଯଦି (width_remainder) {
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
    } ଭାଙ୍ଗ;

    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଫେରନ୍ତୁ SDL_SetError("Unsupported YUV destination format: %s", SDL_GetPixelFormatName(dst_format));
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
    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର bool SDL_ConvertPixels_XBGR2101010_to_P010(ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height, ଅଚଳ ଶୂନ୍ୟ *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_pitch, SDL_PixelFormat dst_format, ଶୂନ୍ୟ *dst, ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_pitch, YCbCrType yuv_type)
{
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_pitch_x_2 = src_pitch * 2;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା height_half = height / 2;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା height_remainder = (height & 0x1);
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା width_half = width / 2;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା width_remainder = (width & 0x1);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, j;

    ଅଚଳ ସଂରଚନା RGB2YUVFactors *cvt = &RGB2YUVFactorTables[yuv_type];

#define MAKE_Y(r, g, b) (Uint16)(((ପୂର୍ଣ୍ଣସଂଖ୍ୟା)(cvt->y[0] * (r) + cvt->y[1] * (g) + cvt->y[2] * (b) + 0.5f) + cvt->y_offset) << 6)
#define MAKE_U(r, g, b) (Uint16)(((ପୂର୍ଣ୍ଣସଂଖ୍ୟା)(cvt->u[0] * (r) + cvt->u[1] * (g) + cvt->u[2] * (b) + 0.5f) + 512) << 6)
#define MAKE_V(r, g, b) (Uint16)(((ପୂର୍ଣ୍ଣସଂଖ୍ୟା)(cvt->v[0] * (r) + cvt->v[1] * (g) + cvt->v[2] * (b) + 0.5f) + 512) << 6)

#define READ_2x2_PIXELS                                                                                     \
    ଅଚଳ Uint32 p1 = ((ଅଚଳ Uint32 *)curr_row)[2 * i];                                                    \
    ଅଚଳ Uint32 p2 = ((ଅଚଳ Uint32 *)curr_row)[2 * i + 1];                                                \
    ଅଚଳ Uint32 p3 = ((ଅଚଳ Uint32 *)next_row)[2 * i];                                                    \
    ଅଚଳ Uint32 p4 = ((ଅଚଳ Uint32 *)next_row)[2 * i + 1];                                                \
    ଅଚଳ Uint32 r = ((p1 & 0x000003ff) + (p2 & 0x000003ff) + (p3 & 0x000003ff) + (p4 & 0x000003ff)) >> 2;  \
    ଅଚଳ Uint32 g = ((p1 & 0x000ffc00) + (p2 & 0x000ffc00) + (p3 & 0x000ffc00) + (p4 & 0x000ffc00)) >> 12; \
    ଅଚଳ Uint32 b = ((p1 & 0x3ff00000) + (p2 & 0x3ff00000) + (p3 & 0x3ff00000) + (p4 & 0x3ff00000)) >> 22

#define READ_2x1_PIXELS                                             \
    ଅଚଳ Uint32 p1 = ((ଅଚଳ Uint32 *)curr_row)[2 * i];            \
    ଅଚଳ Uint32 p2 = ((ଅଚଳ Uint32 *)next_row)[2 * i];            \
    ଅଚଳ Uint32 r = ((p1 & 0x000003ff) + (p2 & 0x000003ff)) >> 1;  \
    ଅଚଳ Uint32 g = ((p1 & 0x000ffc00) + (p2 & 0x000ffc00)) >> 11; \
    ଅଚଳ Uint32 b = ((p1 & 0x3ff00000) + (p2 & 0x3ff00000)) >> 21

#define READ_1x2_PIXELS                                             \
    ଅଚଳ Uint32 p1 = ((ଅଚଳ Uint32 *)curr_row)[2 * i];            \
    ଅଚଳ Uint32 p2 = ((ଅଚଳ Uint32 *)curr_row)[2 * i + 1];        \
    ଅଚଳ Uint32 r = ((p1 & 0x000003ff) + (p2 & 0x000003ff)) >> 1;  \
    ଅଚଳ Uint32 g = ((p1 & 0x000ffc00) + (p2 & 0x000ffc00)) >> 11; \
    ଅଚଳ Uint32 b = ((p1 & 0x3ff00000) + (p2 & 0x3ff00000)) >> 21

#define READ_1x1_PIXEL                                  \
    ଅଚଳ Uint32 p = ((ଅଚଳ Uint32 *)curr_row)[2 * i]; \
    ଅଚଳ Uint32 r = (p & 0x000003ff);                  \
    ଅଚଳ Uint32 g = (p & 0x000ffc00) >> 10;            \
    ଅଚଳ Uint32 b = (p & 0x3ff00000) >> 20

    ଅଚଳ Uint8 *curr_row, *next_row;

    Uint16 *plane_y;
    Uint16 *plane_u;
    Uint16 *plane_v;
    Uint16 *plane_interleaved_uv;
    Uint32 y_stride, uv_stride, y_skip, uv_skip;

    ଯଦି (!GetYUVPlanes(width, height, dst_format, dst, dst_pitch,
                      (ଅଚଳ Uint8 **)&plane_y, (ଅଚଳ Uint8 **)&plane_u, (ଅଚଳ Uint8 **)&plane_v,
                      &y_stride, &uv_stride)) {
        ଫେରନ୍ତୁ false;
    }

    y_stride /= ଆକାର(Uint16);
    uv_stride /= ଆକାର(Uint16);

    plane_interleaved_uv = (plane_y + height * y_stride);
    y_skip = (y_stride - width);

    curr_row = (ଅଚଳ Uint8 *)src;

    // Write Y plane
    ପାଇଁ (j = 0; j < height; j++) {
        ପାଇଁ (i = 0; i < width; i++) {
            ଅଚଳ Uint32 p1 = ((ଅଚଳ Uint32 *)curr_row)[i];
            ଅଚଳ Uint32 r = (p1 >>  0) & 0x03ff;
            ଅଚଳ Uint32 g = (p1 >> 10) & 0x03ff;
            ଅଚଳ Uint32 b = (p1 >> 20) & 0x03ff;
            *plane_y++ = MAKE_Y(r, g, b);
        }
        plane_y += y_skip;
        curr_row += src_pitch;
    }

    curr_row = (ଅଚଳ Uint8 *)src;
    next_row = (ଅଚଳ Uint8 *)src;
    next_row += src_pitch;

    uv_skip = (uv_stride - ((width + 1) / 2) * 2);
    ପାଇଁ (j = 0; j < height_half; j++) {
        ପାଇଁ (i = 0; i < width_half; i++) {
            READ_2x2_PIXELS;
            *plane_interleaved_uv++ = MAKE_U(r, g, b);
            *plane_interleaved_uv++ = MAKE_V(r, g, b);
        }
        ଯଦି (width_remainder) {
            READ_2x1_PIXELS;
            *plane_interleaved_uv++ = MAKE_U(r, g, b);
            *plane_interleaved_uv++ = MAKE_V(r, g, b);
        }
        plane_interleaved_uv += uv_skip;
        curr_row += src_pitch_x_2;
        next_row += src_pitch_x_2;
    }
    ଯଦି (height_remainder) {
        ପାଇଁ (i = 0; i < width_half; i++) {
            READ_1x2_PIXELS;
            *plane_interleaved_uv++ = MAKE_U(r, g, b);
            *plane_interleaved_uv++ = MAKE_V(r, g, b);
        }
        ଯଦି (width_remainder) {
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
    ଫେରନ୍ତୁ true;
}

bool SDL_ConvertPixels_RGB_to_YUV(ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height,
                                  SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ଅଚଳ ଶୂନ୍ୟ *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_pitch,
                                  SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, ଶୂନ୍ୟ *dst, ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_pitch)
{
    YCbCrType yuv_type = YCBCR_601_LIMITED;

    ଯଦି (!GetYUVConversionType(dst_colorspace, width, height, 8, &yuv_type)) {
        ଫେରନ୍ତୁ false;
    }

#ଯଦି 0 // Doesn't handle odd widths
    // RGB24 to FOURCC
    ଯଦି (src_format == SDL_PIXELFORMAT_RGB24) {
        Uint8 *y;
        Uint8 *u;
        Uint8 *v;
        Uint32 y_stride;
        Uint32 uv_stride;

        ଯଦି (GetYUVPlanes(width, height, dst_format, dst, dst_pitch, (ଅଚଳ Uint8 **)&y, (ଅଚଳ Uint8 **)&u, (ଅଚଳ Uint8 **)&v, &y_stride, &uv_stride) < 0) {
            ଫେରନ୍ତୁ false;
        }

        rgb24_yuv420_std(width, height, src, src_pitch, y, u, v, y_stride, uv_stride, yuv_type);
        ଫେରନ୍ତୁ true;
    }
#endif

    // ARGB8888 to FOURCC
    ଯଦି (src_format == SDL_PIXELFORMAT_ARGB8888 || src_format == SDL_PIXELFORMAT_XRGB8888) {
        ଫେରନ୍ତୁ SDL_ConvertPixels_XRGB8888_to_YUV(width, height, src, src_pitch, dst_format, dst, dst_pitch, yuv_type);
    }

    ଯଦି (dst_format == SDL_PIXELFORMAT_P010) {
        ଯଦି (src_format == SDL_PIXELFORMAT_XBGR2101010) {
            ଫେରନ୍ତୁ SDL_ConvertPixels_XBGR2101010_to_P010(width, height, src, src_pitch, dst_format, dst, dst_pitch, yuv_type);
        }

        // We currently only support converting from XBGR2101010 to P010
        bool result;
        ଶୂନ୍ୟ *tmp;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା tmp_pitch = (width * ଆକାର(Uint32));

        tmp = SDL_malloc((size_t)tmp_pitch * height);
        ଯଦି (!tmp) {
            ଫେରନ୍ତୁ false;
        }

        // convert src/src_format to tmp/XBGR2101010
        result = SDL_ConvertPixelsAndColorspace(width, height, src_format, src_colorspace, src_properties, src, src_pitch, SDL_PIXELFORMAT_XBGR2101010, dst_colorspace, dst_properties, tmp, tmp_pitch);
        ଯଦି (!result) {
            SDL_free(tmp);
            ଫେରନ୍ତୁ false;
        }

        // convert tmp/XBGR2101010 to dst/P010
        result = SDL_ConvertPixels_XBGR2101010_to_P010(width, height, tmp, tmp_pitch, dst_format, dst, dst_pitch, yuv_type);
        SDL_free(tmp);
        ଫେରନ୍ତୁ result;
    }

    // not ARGB8888 to FOURCC : need an intermediate conversion
    {
        bool result;
        ଶୂନ୍ୟ *tmp;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା tmp_pitch = (width * ଆକାର(Uint32));

        tmp = SDL_malloc((size_t)tmp_pitch * height);
        ଯଦି (!tmp) {
            ଫେରନ୍ତୁ false;
        }

        // convert src/src_format to tmp/XRGB8888
        result = SDL_ConvertPixelsAndColorspace(width, height, src_format, src_colorspace, src_properties, src, src_pitch, SDL_PIXELFORMAT_XRGB8888, SDL_COLORSPACE_SRGB, 0, tmp, tmp_pitch);
        ଯଦି (!result) {
            SDL_free(tmp);
            ଫେରନ୍ତୁ false;
        }

        // convert tmp/XRGB8888 to dst/FOURCC
        result = SDL_ConvertPixels_XRGB8888_to_YUV(width, height, tmp, tmp_pitch, dst_format, dst, dst_pitch, yuv_type);
        SDL_free(tmp);
        ଫେରନ୍ତୁ result;
    }
}

ସ୍ଥିର bool SDL_ConvertPixels_YUV_to_YUV_Copy(ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height, SDL_PixelFormat format, ଅଚଳ ଶୂନ୍ୟ *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_pitch, ଶୂନ୍ୟ *dst, ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_pitch)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    ଯଦି (IsPlanar1x1Format(format)) {
        // YUV planes
        ଅଚଳ size_t length = width * SDL_BYTESPERPIXEL(format);
        ପାଇଁ (i = height * 3; i--;) {
            SDL_memcpy(dst, src, length);
            src = (ଅଚଳ Uint8 *)src + src_pitch;
            dst = (Uint8 *)dst + dst_pitch;
        }
        ଫେରନ୍ତୁ true;
    }

    ଯଦି (IsPlanar2x2Format(format)) {
        ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା bpp = SDL_BYTESPERPIXEL(format);

        // Y plane
        ଅଚଳ size_t length = width * bpp;
        ପାଇଁ (i = height; i--;) {
            SDL_memcpy(dst, src, length);
            src = (ଅଚଳ Uint8 *)src + src_pitch;
            dst = (Uint8 *)dst + dst_pitch;
        }

        ଯଦି (format == SDL_PIXELFORMAT_YV12 ||
            format == SDL_PIXELFORMAT_IYUV ||
            format == SDL_PIXELFORMAT_I0FL) {
            // U and V planes are a quarter the size of the Y plane, rounded up
            width = ((width + 1) / 2) * bpp;
            height = (height + 1) / 2;
            src_pitch = ((src_pitch / bpp + 1) / 2) * bpp;
            dst_pitch = ((dst_pitch / bpp + 1) / 2) * bpp;
            ପାଇଁ (i = height * 2; i--;) {
                SDL_memcpy(dst, src, width);
                src = (ଅଚଳ Uint8 *)src + src_pitch;
                dst = (Uint8 *)dst + dst_pitch;
            }
        } ଅନ୍ୟଥା ଯଦି (format == SDL_PIXELFORMAT_NV12 ||
                   format == SDL_PIXELFORMAT_NV21 ||
                   format == SDL_PIXELFORMAT_P010) {
            // U/V plane is half the height of the Y plane, rounded up, with packed CrCb
            width = ((width + 1) / 2) * 2 * bpp;
            height = (height + 1) / 2;
            src_pitch = ((src_pitch / bpp + 1) / 2) * 2 * bpp;
            dst_pitch = ((dst_pitch / bpp + 1) / 2) * 2 * bpp;
            ପାଇଁ (i = height; i--;) {
                SDL_memcpy(dst, src, width);
                src = (ଅଚଳ Uint8 *)src + src_pitch;
                dst = (Uint8 *)dst + dst_pitch;
            }
        }
        ଫେରନ୍ତୁ true;
    }

    ଯଦି (IsPacked4Format(format)) {
        // Packed planes
        width = 4 * ((width + 1) / 2);
        ପାଇଁ (i = height; i--;) {
            SDL_memcpy(dst, src, width);
            src = (ଅଚଳ Uint8 *)src + src_pitch;
            dst = (Uint8 *)dst + dst_pitch;
        }
        ଫେରନ୍ତୁ true;
    }

    ଫେରନ୍ତୁ SDL_SetError("SDL_ConvertPixels_YUV_to_YUV_Copy: Unsupported YUV format: %s", SDL_GetPixelFormatName(format));
}

ସ୍ଥିର bool SDL_ConvertPixels_SwapUVPlanes(ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height, ଅଚଳ ଶୂନ୍ୟ *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_pitch, ଶୂନ୍ୟ *dst, ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_pitch)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା y;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା UVwidth = (width + 1) / 2;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା UVheight = (height + 1) / 2;

    // Skip the Y plane
    src = (ଅଚଳ Uint8 *)src + height * src_pitch;
    dst = (Uint8 *)dst + height * dst_pitch;

    ଯଦି (src == dst) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା UVpitch = (dst_pitch + 1) / 2;
        Uint8 *tmp;
        Uint8 *row1 = (Uint8 *)dst;
        Uint8 *row2 = row1 + UVheight * UVpitch;

        // Allocate a temporary row for the swap
        tmp = (Uint8 *)SDL_malloc(UVwidth);
        ଯଦି (!tmp) {
            ଫେରନ୍ତୁ false;
        }
        ପାଇଁ (y = 0; y < UVheight; ++y) {
            SDL_memcpy(tmp, row1, UVwidth);
            SDL_memcpy(row1, row2, UVwidth);
            SDL_memcpy(row2, tmp, UVwidth);
            row1 += UVpitch;
            row2 += UVpitch;
        }
        SDL_free(tmp);
    } ଅନ୍ୟଥା {
        ଅଚଳ Uint8 *srcUV;
        Uint8 *dstUV;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା srcUVPitch = ((src_pitch + 1) / 2);
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା dstUVPitch = ((dst_pitch + 1) / 2);

        // Copy the first plane
        srcUV = (ଅଚଳ Uint8 *)src;
        dstUV = (Uint8 *)dst + UVheight * dstUVPitch;
        ପାଇଁ (y = 0; y < UVheight; ++y) {
            SDL_memcpy(dstUV, srcUV, UVwidth);
            srcUV += srcUVPitch;
            dstUV += dstUVPitch;
        }

        // Copy the second plane
        dstUV = (Uint8 *)dst;
        ପାଇଁ (y = 0; y < UVheight; ++y) {
            SDL_memcpy(dstUV, srcUV, UVwidth);
            srcUV += srcUVPitch;
            dstUV += dstUVPitch;
        }
    }
    ଫେରନ୍ତୁ true;
}

#ifdef SDL_SSE2_INTRINSICS
ସ୍ଥିର bool SDL_TARGETING("sse2") SDL_ConvertPixels_PackUVPlanes_to_NV_SSE2(ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height, ଅଚଳ ଶୂନ୍ୟ *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_pitch, ଶୂନ୍ୟ *dst, ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_pitch, bool reverseUV)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, y;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା UVwidth = (width + 1) / 2;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା UVheight = (height + 1) / 2;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା srcUVPitch = ((src_pitch + 1) / 2);
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_UVPitch_ବାମ = srcUVPitch - UVwidth;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା dstUVPitch = ((dst_pitch + 1) / 2) * 2;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_UVPitch_ବାମ = dstUVPitch - UVwidth * 2;
    ଅଚଳ Uint8 *src1, *src2;
    Uint8 *dstUV;
    Uint8 *tmp = ଖାଲି;

    // Skip the Y plane
    src = (ଅଚଳ Uint8 *)src + height * src_pitch;
    dst = (Uint8 *)dst + height * dst_pitch;

    ଯଦି (src == dst) {
        // Need to make a copy of the buffer so we don't clobber it while converting
        tmp = (Uint8 *)SDL_malloc((size_t)2 * UVheight * srcUVPitch);
        ଯଦି (tmp == ଖାଲି) {
            ଫେରନ୍ତୁ false;
        }
        SDL_memcpy(tmp, src, (size_t)2 * UVheight * srcUVPitch);
        src = tmp;
    }

    ଯଦି (reverseUV) {
        src2 = (ଅଚଳ Uint8 *)src;
        src1 = src2 + UVheight * srcUVPitch;
    } ଅନ୍ୟଥା {
        src1 = (ଅଚଳ Uint8 *)src;
        src2 = src1 + UVheight * srcUVPitch;
    }
    dstUV = (Uint8 *)dst;

    y = UVheight;
    ଯେତେବେଳେ (y--) {
        x = UVwidth;
        ଯେତେବେଳେ (x >= 16) {
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
        ଯେତେବେଳେ (x--) {
            *dstUV++ = *src1++;
            *dstUV++ = *src2++;
        }
        src1 += src_UVPitch_ବାମ;
        src2 += src_UVPitch_ବାମ;
        dstUV += dst_UVPitch_ବାମ;
    }

    ଯଦି (tmp) {
        SDL_free(tmp);
    }
    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର bool SDL_TARGETING("sse2") SDL_ConvertPixels_SplitNV_to_UVPlanes_SSE2(ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height, ଅଚଳ ଶୂନ୍ୟ *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_pitch, ଶୂନ୍ୟ *dst, ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_pitch, bool reverseUV)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, y;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା UVwidth = (width + 1) / 2;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା UVheight = (height + 1) / 2;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା srcUVPitch = ((src_pitch + 1) / 2) * 2;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_UVPitch_ବାମ = srcUVPitch - UVwidth * 2;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା dstUVPitch = ((dst_pitch + 1) / 2);
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_UVPitch_ବାମ = dstUVPitch - UVwidth;
    ଅଚଳ Uint8 *srcUV;
    Uint8 *dst1, *dst2;
    Uint8 *tmp = ଖାଲି;

    // Skip the Y plane
    src = (ଅଚଳ Uint8 *)src + height * src_pitch;
    dst = (Uint8 *)dst + height * dst_pitch;

    ଯଦି (src == dst) {
        // Need to make a copy of the buffer so we don't clobber it while converting
        tmp = (Uint8 *)SDL_malloc((size_t)UVheight * srcUVPitch);
        ଯଦି (tmp == ଖାଲି) {
            ଫେରନ୍ତୁ false;
        }
        SDL_memcpy(tmp, src, (size_t)UVheight * srcUVPitch);
        src = tmp;
    }

    ଯଦି (reverseUV) {
        dst2 = (Uint8 *)dst;
        dst1 = dst2 + UVheight * dstUVPitch;
    } ଅନ୍ୟଥା {
        dst1 = (Uint8 *)dst;
        dst2 = dst1 + UVheight * dstUVPitch;
    }
    srcUV = (ଅଚଳ Uint8 *)src;

    y = UVheight;
    ଯେତେବେଳେ (y--) {
        __m128i mask = _mm_set1_epi16(0x00FF);
        x = UVwidth;
        ଯେତେବେଳେ (x >= 16) {
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
        ଯେତେବେଳେ (x--) {
            *dst1++ = *srcUV++;
            *dst2++ = *srcUV++;
        }
        srcUV += src_UVPitch_ବାମ;
        dst1 += dst_UVPitch_ବାମ;
        dst2 += dst_UVPitch_ବାମ;
    }

    ଯଦି (tmp) {
        SDL_free(tmp);
    }
    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର bool SDL_TARGETING("sse2") SDL_ConvertPixels_SwapNV_SSE2(ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height, ଅଚଳ ଶୂନ୍ୟ *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_pitch, ଶୂନ୍ୟ *dst, ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_pitch)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, y;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା UVwidth = (width + 1) / 2;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା UVheight = (height + 1) / 2;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା srcUVPitch = ((src_pitch + 1) / 2) * 2;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_UVPitch_ବାମ = (srcUVPitch - UVwidth * 2) / ଆକାର(Uint16);
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା dstUVPitch = ((dst_pitch + 1) / 2) * 2;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_UVPitch_ବାମ = (dstUVPitch - UVwidth * 2) / ଆକାର(Uint16);
    ଅଚଳ Uint16 *srcUV;
    Uint16 *dstUV;

    // Skip the Y plane
    src = (ଅଚଳ Uint8 *)src + height * src_pitch;
    dst = (Uint8 *)dst + height * dst_pitch;

    srcUV = (ଅଚଳ Uint16 *)src;
    dstUV = (Uint16 *)dst;
    y = UVheight;
    ଯେତେବେଳେ (y--) {
        x = UVwidth;
        ଯେତେବେଳେ (x >= 8) {
            __m128i uv = _mm_loadu_si128((__m128i *)srcUV);
            __m128i v = _mm_slli_epi16(uv, 8);
            __m128i u = _mm_srli_epi16(uv, 8);
            __m128i vu = _mm_or_si128(v, u);
            _mm_storeu_si128((__m128i *)dstUV, vu);
            srcUV += 8;
            dstUV += 8;
            x -= 8;
        }
        ଯଦି (x > 0) {
            ଅଚଳ Uint8 *srcUV8 = (ଅଚଳ Uint8 *)srcUV;
            Uint8 *dstUV8 = (Uint8 *)dstUV;
            srcUV += x;
            dstUV += x;
            ଯେତେବେଳେ (x--) {
                Uint8 u = *srcUV8++;
                Uint8 v = *srcUV8++;
                *dstUV8++ = v;
                *dstUV8++ = u;
            }
        }
        srcUV += src_UVPitch_ବାମ;
        dstUV += dst_UVPitch_ବାମ;
    }
    ଫେରନ୍ତୁ true;
}
#endif

ସ୍ଥିର bool SDL_ConvertPixels_PackUVPlanes_to_NV_std(ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height, ଅଚଳ ଶୂନ୍ୟ *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_pitch, ଶୂନ୍ୟ *dst, ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_pitch, bool reverseUV)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, y;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା UVwidth = (width + 1) / 2;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା UVheight = (height + 1) / 2;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା srcUVPitch = ((src_pitch + 1) / 2);
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_UVPitch_ବାମ = srcUVPitch - UVwidth;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା dstUVPitch = ((dst_pitch + 1) / 2) * 2;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_UVPitch_ବାମ = dstUVPitch - UVwidth * 2;
    ଅଚଳ Uint8 *src1, *src2;
    Uint8 *dstUV;
    Uint8 *tmp = ଖାଲି;

    // Skip the Y plane
    src = (ଅଚଳ Uint8 *)src + height * src_pitch;
    dst = (Uint8 *)dst + height * dst_pitch;

    ଯଦି (src == dst) {
        // Need to make a copy of the buffer so we don't clobber it while converting
        tmp = (Uint8 *)SDL_malloc((size_t)2 * UVheight * srcUVPitch);
        ଯଦି (!tmp) {
            ଫେରନ୍ତୁ false;
        }
        SDL_memcpy(tmp, src, (size_t)2 * UVheight * srcUVPitch);
        src = tmp;
    }

    ଯଦି (reverseUV) {
        src2 = (ଅଚଳ Uint8 *)src;
        src1 = src2 + UVheight * srcUVPitch;
    } ଅନ୍ୟଥା {
        src1 = (ଅଚଳ Uint8 *)src;
        src2 = src1 + UVheight * srcUVPitch;
    }
    dstUV = (Uint8 *)dst;

    y = UVheight;
    ଯେତେବେଳେ (y--) {
        x = UVwidth;
        ଯେତେବେଳେ (x--) {
            *dstUV++ = *src1++;
            *dstUV++ = *src2++;
        }
        src1 += src_UVPitch_ବାମ;
        src2 += src_UVPitch_ବାମ;
        dstUV += dst_UVPitch_ବାମ;
    }

    SDL_free(tmp);
    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର bool SDL_ConvertPixels_SplitNV_to_UVPlanes_std(ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height, ଅଚଳ ଶୂନ୍ୟ *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_pitch, ଶୂନ୍ୟ *dst, ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_pitch, bool reverseUV)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, y;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା UVwidth = (width + 1) / 2;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା UVheight = (height + 1) / 2;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା srcUVPitch = ((src_pitch + 1) / 2) * 2;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_UVPitch_ବାମ = srcUVPitch - UVwidth * 2;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା dstUVPitch = ((dst_pitch + 1) / 2);
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_UVPitch_ବାମ = dstUVPitch - UVwidth;
    ଅଚଳ Uint8 *srcUV;
    Uint8 *dst1, *dst2;
    Uint8 *tmp = ଖାଲି;

    // Skip the Y plane
    src = (ଅଚଳ Uint8 *)src + height * src_pitch;
    dst = (Uint8 *)dst + height * dst_pitch;

    ଯଦି (src == dst) {
        // Need to make a copy of the buffer so we don't clobber it while converting
        tmp = (Uint8 *)SDL_malloc((size_t)UVheight * srcUVPitch);
        ଯଦି (!tmp) {
            ଫେରନ୍ତୁ false;
        }
        SDL_memcpy(tmp, src, (size_t)UVheight * srcUVPitch);
        src = tmp;
    }

    ଯଦି (reverseUV) {
        dst2 = (Uint8 *)dst;
        dst1 = dst2 + UVheight * dstUVPitch;
    } ଅନ୍ୟଥା {
        dst1 = (Uint8 *)dst;
        dst2 = dst1 + UVheight * dstUVPitch;
    }
    srcUV = (ଅଚଳ Uint8 *)src;

    y = UVheight;
    ଯେତେବେଳେ (y--) {
        x = UVwidth;
        ଯେତେବେଳେ (x--) {
            *dst1++ = *srcUV++;
            *dst2++ = *srcUV++;
        }
        srcUV += src_UVPitch_ବାମ;
        dst1 += dst_UVPitch_ବାମ;
        dst2 += dst_UVPitch_ବାମ;
    }

    SDL_free(tmp);
    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର bool SDL_ConvertPixels_SwapNV_std(ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height, ଅଚଳ ଶୂନ୍ୟ *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_pitch, ଶୂନ୍ୟ *dst, ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_pitch)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, y;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା UVwidth = (width + 1) / 2;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା UVheight = (height + 1) / 2;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା srcUVPitch = ((src_pitch + 1) / 2) * 2;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା dstUVPitch = ((dst_pitch + 1) / 2) * 2;

    // Skip the Y plane
    src = (ଅଚଳ Uint8 *)src + height * src_pitch;
    dst = (Uint8 *)dst + height * dst_pitch;

    bool aligned = (((uintptr_t)src | (uintptr_t)dst) & 1) == 0;
    ଯଦି (aligned) {
        ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_UVPitch_ବାମ = (srcUVPitch - UVwidth * 2) / ଆକାର(Uint16);
        ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_UVPitch_ବାମ = (dstUVPitch - UVwidth * 2) / ଆକାର(Uint16);
        ଅଚଳ Uint16 *srcUV = (ଅଚଳ Uint16 *)src;
        Uint16 *dstUV = (Uint16 *)dst;
        y = UVheight;
        ଯେତେବେଳେ (y--) {
            x = UVwidth;
            ଯେତେବେଳେ (x--) {
                *dstUV++ = SDL_Swap16(*srcUV++);
            }
            srcUV += src_UVPitch_ବାମ;
            dstUV += dst_UVPitch_ବାମ;
        }
    } ଅନ୍ୟଥା {
        ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_UVPitch_ବାମ = (srcUVPitch - UVwidth * 2);
        ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_UVPitch_ବାମ = (dstUVPitch - UVwidth * 2);
        ଅଚଳ Uint8 *srcUV = (ଅଚଳ Uint8 *)src;
        Uint8 *dstUV = (Uint8 *)dst;
        y = UVheight;
        ଯେତେବେଳେ (y--) {
            x = UVwidth;
            ଯେତେବେଳେ (x--) {
                Uint8 u = *srcUV++;
                Uint8 v = *srcUV++;
                *dstUV++ = v;
                *dstUV++ = u;
            }
            srcUV += src_UVPitch_ବାମ;
            dstUV += dst_UVPitch_ବାମ;
        }
    }
    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର bool SDL_ConvertPixels_PackUVPlanes_to_NV(ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height, ଅଚଳ ଶୂନ୍ୟ *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_pitch, ଶୂନ୍ୟ *dst, ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_pitch, bool reverseUV)
{
#ifdef SDL_SSE2_INTRINSICS
    ଯଦି (SDL_HasSSE2()) {
      ଫେରନ୍ତୁ SDL_ConvertPixels_PackUVPlanes_to_NV_SSE2(width, height, src, src_pitch, dst, dst_pitch, reverseUV);
    }
#endif
    ଫେରନ୍ତୁ SDL_ConvertPixels_PackUVPlanes_to_NV_std(width, height, src, src_pitch, dst, dst_pitch, reverseUV);
}

ସ୍ଥିର bool SDL_ConvertPixels_SplitNV_to_UVPlanes(ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height, ଅଚଳ ଶୂନ୍ୟ *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_pitch, ଶୂନ୍ୟ *dst, ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_pitch, bool reverseUV)
{
#ifdef SDL_SSE2_INTRINSICS
    ଯଦି (SDL_HasSSE2()) {
      ଫେରନ୍ତୁ SDL_ConvertPixels_SplitNV_to_UVPlanes_SSE2(width, height, src, src_pitch, dst, dst_pitch, reverseUV);
    }
#endif
    ଫେରନ୍ତୁ SDL_ConvertPixels_SplitNV_to_UVPlanes_std(width, height, src, src_pitch, dst, dst_pitch, reverseUV);
}

ସ୍ଥିର bool SDL_ConvertPixels_SwapNV(ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height, ଅଚଳ ଶୂନ୍ୟ *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_pitch, ଶୂନ୍ୟ *dst, ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_pitch)
{
#ifdef SDL_SSE2_INTRINSICS
    ଯଦି (SDL_HasSSE2()) {
      ଫେରନ୍ତୁ SDL_ConvertPixels_SwapNV_SSE2(width, height, src, src_pitch, dst, dst_pitch);
    }
#endif
    ଫେରନ୍ତୁ SDL_ConvertPixels_SwapNV_std(width, height, src, src_pitch, dst, dst_pitch);
}

ସ୍ଥିର bool SDL_ConvertPixels_Planar2x2_to_Planar2x2(ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height,
                                                     SDL_PixelFormat src_format, ଅଚଳ ଶୂନ୍ୟ *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_pitch,
                                                     SDL_PixelFormat dst_format, ଶୂନ୍ୟ *dst, ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_pitch)
{
    ଯଦି (src != dst) {
        // Copy Y plane
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
        ଅଚଳ Uint8 *srcY = (ଅଚଳ Uint8 *)src;
        Uint8 *dstY = (Uint8 *)dst;
        ପାଇଁ (i = height; i--;) {
            SDL_memcpy(dstY, srcY, width);
            srcY += src_pitch;
            dstY += dst_pitch;
        }
    }

    ବାଛ (src_format) {
    ସ୍ଥିତି SDL_PIXELFORMAT_YV12:
        ବାଛ (dst_format) {
        ସ୍ଥିତି SDL_PIXELFORMAT_IYUV:
            ଫେରନ୍ତୁ SDL_ConvertPixels_SwapUVPlanes(width, height, src, src_pitch, dst, dst_pitch);
        ସ୍ଥିତି SDL_PIXELFORMAT_NV12:
            ଫେରନ୍ତୁ SDL_ConvertPixels_PackUVPlanes_to_NV(width, height, src, src_pitch, dst, dst_pitch, true);
        ସ୍ଥିତି SDL_PIXELFORMAT_NV21:
            ଫେରନ୍ତୁ SDL_ConvertPixels_PackUVPlanes_to_NV(width, height, src, src_pitch, dst, dst_pitch, false);
        ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
            ଭାଙ୍ଗ;
        }
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_PIXELFORMAT_IYUV:
        ବାଛ (dst_format) {
        ସ୍ଥିତି SDL_PIXELFORMAT_YV12:
            ଫେରନ୍ତୁ SDL_ConvertPixels_SwapUVPlanes(width, height, src, src_pitch, dst, dst_pitch);
        ସ୍ଥିତି SDL_PIXELFORMAT_NV12:
            ଫେରନ୍ତୁ SDL_ConvertPixels_PackUVPlanes_to_NV(width, height, src, src_pitch, dst, dst_pitch, false);
        ସ୍ଥିତି SDL_PIXELFORMAT_NV21:
            ଫେରନ୍ତୁ SDL_ConvertPixels_PackUVPlanes_to_NV(width, height, src, src_pitch, dst, dst_pitch, true);
        ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
            ଭାଙ୍ଗ;
        }
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_PIXELFORMAT_NV12:
        ବାଛ (dst_format) {
        ସ୍ଥିତି SDL_PIXELFORMAT_YV12:
            ଫେରନ୍ତୁ SDL_ConvertPixels_SplitNV_to_UVPlanes(width, height, src, src_pitch, dst, dst_pitch, true);
        ସ୍ଥିତି SDL_PIXELFORMAT_IYUV:
            ଫେରନ୍ତୁ SDL_ConvertPixels_SplitNV_to_UVPlanes(width, height, src, src_pitch, dst, dst_pitch, false);
        ସ୍ଥିତି SDL_PIXELFORMAT_NV21:
            ଫେରନ୍ତୁ SDL_ConvertPixels_SwapNV(width, height, src, src_pitch, dst, dst_pitch);
        ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
            ଭାଙ୍ଗ;
        }
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_PIXELFORMAT_NV21:
        ବାଛ (dst_format) {
        ସ୍ଥିତି SDL_PIXELFORMAT_YV12:
            ଫେରନ୍ତୁ SDL_ConvertPixels_SplitNV_to_UVPlanes(width, height, src, src_pitch, dst, dst_pitch, false);
        ସ୍ଥିତି SDL_PIXELFORMAT_IYUV:
            ଫେରନ୍ତୁ SDL_ConvertPixels_SplitNV_to_UVPlanes(width, height, src, src_pitch, dst, dst_pitch, true);
        ସ୍ଥିତି SDL_PIXELFORMAT_NV12:
            ଫେରନ୍ତୁ SDL_ConvertPixels_SwapNV(width, height, src, src_pitch, dst, dst_pitch);
        ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
            ଭାଙ୍ଗ;
        }
        ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଭାଙ୍ଗ;
    }
    ଫେରନ୍ତୁ SDL_SetError("SDL_ConvertPixels_Planar2x2_to_Planar2x2: Unsupported YUV conversion: %s -> %s", SDL_GetPixelFormatName(src_format),
                        SDL_GetPixelFormatName(dst_format));
}

#ifdef SDL_SSE2_INTRINSICS
#define PACKED4_TO_PACKED4_ROW_SSE2(shuffle)                      \
    ଯେତେବେଳେ (x >= 4) {                                              \
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

ସ୍ଥିର bool SDL_TARGETING("sse2") SDL_ConvertPixels_YUY2_to_UYVY_SSE2(ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height, ଅଚଳ ଶୂନ୍ୟ *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_pitch, ଶୂନ୍ୟ *dst, ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_pitch)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, y;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା YUVwidth = (width + 1) / 2;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_YUVPitch_ବାମ = (src_pitch - YUVwidth * 4);
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_YUVPitch_ବାମ = (dst_pitch - YUVwidth * 4);
    ଅଚଳ Uint8 *srcYUV = (ଅଚଳ Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = height;
    x = YUVwidth;
    ଯେତେବେଳେ (y--) {
        PACKED4_TO_PACKED4_ROW_SSE2(_MM_SHUFFLE(2, 3, 0, 1));
        ଯେତେବେଳେ (x--) {
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
        srcYUV += src_YUVPitch_ବାମ;
        dstYUV += dst_YUVPitch_ବାମ;
        x = YUVwidth;
    }
    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର bool SDL_TARGETING("sse2") SDL_ConvertPixels_YUY2_to_YVYU_SSE2(ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height, ଅଚଳ ଶୂନ୍ୟ *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_pitch, ଶୂନ୍ୟ *dst, ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_pitch)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, y;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା YUVwidth = (width + 1) / 2;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_YUVPitch_ବାମ = (src_pitch - YUVwidth * 4);
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_YUVPitch_ବାମ = (dst_pitch - YUVwidth * 4);
    ଅଚଳ Uint8 *srcYUV = (ଅଚଳ Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = height;
    x = YUVwidth;
    ଯେତେବେଳେ (y--) {
        PACKED4_TO_PACKED4_ROW_SSE2(_MM_SHUFFLE(1, 2, 3, 0));
        ଯେତେବେଳେ (x--) {
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
        srcYUV += src_YUVPitch_ବାମ;
        dstYUV += dst_YUVPitch_ବାମ;
        x = YUVwidth;
    }
    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର bool SDL_TARGETING("sse2") SDL_ConvertPixels_UYVY_to_YUY2_SSE2(ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height, ଅଚଳ ଶୂନ୍ୟ *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_pitch, ଶୂନ୍ୟ *dst, ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_pitch)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, y;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା YUVwidth = (width + 1) / 2;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_YUVPitch_ବାମ = (src_pitch - YUVwidth * 4);
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_YUVPitch_ବାମ = (dst_pitch - YUVwidth * 4);
    ଅଚଳ Uint8 *srcYUV = (ଅଚଳ Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = height;
    x = YUVwidth;
    ଯେତେବେଳେ (y--) {
        PACKED4_TO_PACKED4_ROW_SSE2(_MM_SHUFFLE(2, 3, 0, 1));
        ଯେତେବେଳେ (x--) {
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
        srcYUV += src_YUVPitch_ବାମ;
        dstYUV += dst_YUVPitch_ବାମ;
        x = YUVwidth;
    }
    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର bool SDL_TARGETING("sse2") SDL_ConvertPixels_UYVY_to_YVYU_SSE2(ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height, ଅଚଳ ଶୂନ୍ୟ *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_pitch, ଶୂନ୍ୟ *dst, ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_pitch)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, y;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା YUVwidth = (width + 1) / 2;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_YUVPitch_ବାମ = (src_pitch - YUVwidth * 4);
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_YUVPitch_ବାମ = (dst_pitch - YUVwidth * 4);
    ଅଚଳ Uint8 *srcYUV = (ଅଚଳ Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = height;
    x = YUVwidth;
    ଯେତେବେଳେ (y--) {
        PACKED4_TO_PACKED4_ROW_SSE2(_MM_SHUFFLE(0, 3, 2, 1));
        ଯେତେବେଳେ (x--) {
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
        srcYUV += src_YUVPitch_ବାମ;
        dstYUV += dst_YUVPitch_ବାମ;
        x = YUVwidth;
    }
    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର bool SDL_TARGETING("sse2") SDL_ConvertPixels_YVYU_to_YUY2_SSE2(ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height, ଅଚଳ ଶୂନ୍ୟ *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_pitch, ଶୂନ୍ୟ *dst, ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_pitch)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, y;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା YUVwidth = (width + 1) / 2;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_YUVPitch_ବାମ = (src_pitch - YUVwidth * 4);
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_YUVPitch_ବାମ = (dst_pitch - YUVwidth * 4);
    ଅଚଳ Uint8 *srcYUV = (ଅଚଳ Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = height;
    x = YUVwidth;
    ଯେତେବେଳେ (y--) {
        PACKED4_TO_PACKED4_ROW_SSE2(_MM_SHUFFLE(1, 2, 3, 0));
        ଯେତେବେଳେ (x--) {
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
        srcYUV += src_YUVPitch_ବାମ;
        dstYUV += dst_YUVPitch_ବାମ;
        x = YUVwidth;
    }
    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର bool SDL_TARGETING("sse2") SDL_ConvertPixels_YVYU_to_UYVY_SSE2(ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height, ଅଚଳ ଶୂନ୍ୟ *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_pitch, ଶୂନ୍ୟ *dst, ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_pitch)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, y;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା YUVwidth = (width + 1) / 2;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_YUVPitch_ବାମ = (src_pitch - YUVwidth * 4);
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_YUVPitch_ବାମ = (dst_pitch - YUVwidth * 4);
    ଅଚଳ Uint8 *srcYUV = (ଅଚଳ Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = height;
    x = YUVwidth;
    ଯେତେବେଳେ (y--) {
        PACKED4_TO_PACKED4_ROW_SSE2(_MM_SHUFFLE(2, 1, 0, 3));
        ଯେତେବେଳେ (x--) {
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
        srcYUV += src_YUVPitch_ବାମ;
        dstYUV += dst_YUVPitch_ବାମ;
        x = YUVwidth;
    }
    ଫେରନ୍ତୁ true;
}
#endif

ସ୍ଥିର bool SDL_ConvertPixels_YUY2_to_UYVY_std(ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height, ଅଚଳ ଶୂନ୍ୟ *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_pitch, ଶୂନ୍ୟ *dst, ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_pitch)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, y;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା YUVwidth = (width + 1) / 2;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_YUVPitch_ବାମ = (src_pitch - YUVwidth * 4);
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_YUVPitch_ବାମ = (dst_pitch - YUVwidth * 4);
    ଅଚଳ Uint8 *srcYUV = (ଅଚଳ Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = height;
    ଯେତେବେଳେ (y--) {
        x = YUVwidth;
        ଯେତେବେଳେ (x--) {
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
        srcYUV += src_YUVPitch_ବାମ;
        dstYUV += dst_YUVPitch_ବାମ;
    }
    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର bool SDL_ConvertPixels_YUY2_to_YVYU_std(ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height, ଅଚଳ ଶୂନ୍ୟ *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_pitch, ଶୂନ୍ୟ *dst, ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_pitch)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, y;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା YUVwidth = (width + 1) / 2;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_YUVPitch_ବାମ = (src_pitch - YUVwidth * 4);
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_YUVPitch_ବାମ = (dst_pitch - YUVwidth * 4);
    ଅଚଳ Uint8 *srcYUV = (ଅଚଳ Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = height;
    ଯେତେବେଳେ (y--) {
        x = YUVwidth;
        ଯେତେବେଳେ (x--) {
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
        srcYUV += src_YUVPitch_ବାମ;
        dstYUV += dst_YUVPitch_ବାମ;
    }
    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର bool SDL_ConvertPixels_UYVY_to_YUY2_std(ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height, ଅଚଳ ଶୂନ୍ୟ *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_pitch, ଶୂନ୍ୟ *dst, ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_pitch)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, y;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା YUVwidth = (width + 1) / 2;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_YUVPitch_ବାମ = (src_pitch - YUVwidth * 4);
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_YUVPitch_ବାମ = (dst_pitch - YUVwidth * 4);
    ଅଚଳ Uint8 *srcYUV = (ଅଚଳ Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = height;
    ଯେତେବେଳେ (y--) {
        x = YUVwidth;
        ଯେତେବେଳେ (x--) {
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
        srcYUV += src_YUVPitch_ବାମ;
        dstYUV += dst_YUVPitch_ବାମ;
    }
    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର bool SDL_ConvertPixels_UYVY_to_YVYU_std(ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height, ଅଚଳ ଶୂନ୍ୟ *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_pitch, ଶୂନ୍ୟ *dst, ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_pitch)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, y;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା YUVwidth = (width + 1) / 2;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_YUVPitch_ବାମ = (src_pitch - YUVwidth * 4);
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_YUVPitch_ବାମ = (dst_pitch - YUVwidth * 4);
    ଅଚଳ Uint8 *srcYUV = (ଅଚଳ Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = height;
    ଯେତେବେଳେ (y--) {
        x = YUVwidth;
        ଯେତେବେଳେ (x--) {
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
        srcYUV += src_YUVPitch_ବାମ;
        dstYUV += dst_YUVPitch_ବାମ;
    }
    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର bool SDL_ConvertPixels_YVYU_to_YUY2_std(ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height, ଅଚଳ ଶୂନ୍ୟ *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_pitch, ଶୂନ୍ୟ *dst, ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_pitch)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, y;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା YUVwidth = (width + 1) / 2;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_YUVPitch_ବାମ = (src_pitch - YUVwidth * 4);
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_YUVPitch_ବାମ = (dst_pitch - YUVwidth * 4);
    ଅଚଳ Uint8 *srcYUV = (ଅଚଳ Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = height;
    ଯେତେବେଳେ (y--) {
        x = YUVwidth;
        ଯେତେବେଳେ (x--) {
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
        srcYUV += src_YUVPitch_ବାମ;
        dstYUV += dst_YUVPitch_ବାମ;
    }
    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର bool SDL_ConvertPixels_YVYU_to_UYVY_std(ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height, ଅଚଳ ଶୂନ୍ୟ *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_pitch, ଶୂନ୍ୟ *dst, ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_pitch)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, y;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା YUVwidth = (width + 1) / 2;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_YUVPitch_ବାମ = (src_pitch - YUVwidth * 4);
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_YUVPitch_ବାମ = (dst_pitch - YUVwidth * 4);
    ଅଚଳ Uint8 *srcYUV = (ଅଚଳ Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = height;
    ଯେତେବେଳେ (y--) {
        x = YUVwidth;
        ଯେତେବେଳେ (x--) {
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
        srcYUV += src_YUVPitch_ବାମ;
        dstYUV += dst_YUVPitch_ବାମ;
    }
    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର bool SDL_ConvertPixels_YUY2_to_UYVY(ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height, ଅଚଳ ଶୂନ୍ୟ *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_pitch, ଶୂନ୍ୟ *dst, ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_pitch)
{
#ifdef SDL_SSE2_INTRINSICS
    ଯଦି (SDL_HasSSE2()) {
      ଫେରନ୍ତୁ SDL_ConvertPixels_YUY2_to_UYVY_SSE2(width, height, src, src_pitch, dst, dst_pitch);
    }
#endif
    ଫେରନ୍ତୁ SDL_ConvertPixels_YUY2_to_UYVY_std(width, height, src, src_pitch, dst, dst_pitch);
}

ସ୍ଥିର bool SDL_ConvertPixels_YUY2_to_YVYU(ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height, ଅଚଳ ଶୂନ୍ୟ *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_pitch, ଶୂନ୍ୟ *dst, ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_pitch)
{
#ifdef SDL_SSE2_INTRINSICS
    ଯଦି (SDL_HasSSE2()) {
      ଫେରନ୍ତୁ SDL_ConvertPixels_YUY2_to_YVYU_SSE2(width, height, src, src_pitch, dst, dst_pitch);
    }
#endif
    ଫେରନ୍ତୁ SDL_ConvertPixels_YUY2_to_YVYU_std(width, height, src, src_pitch, dst, dst_pitch);
}

ସ୍ଥିର bool SDL_ConvertPixels_UYVY_to_YUY2(ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height, ଅଚଳ ଶୂନ୍ୟ *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_pitch, ଶୂନ୍ୟ *dst, ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_pitch)
{
#ifdef SDL_SSE2_INTRINSICS
    ଯଦି (SDL_HasSSE2()) {
      ଫେରନ୍ତୁ SDL_ConvertPixels_UYVY_to_YUY2_SSE2(width, height, src, src_pitch, dst, dst_pitch);
    }
#endif
    ଫେରନ୍ତୁ SDL_ConvertPixels_UYVY_to_YUY2_std(width, height, src, src_pitch, dst, dst_pitch);
}

ସ୍ଥିର bool SDL_ConvertPixels_UYVY_to_YVYU(ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height, ଅଚଳ ଶୂନ୍ୟ *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_pitch, ଶୂନ୍ୟ *dst, ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_pitch)
{
#ifdef SDL_SSE2_INTRINSICS
    ଯଦି (SDL_HasSSE2()) {
      ଫେରନ୍ତୁ SDL_ConvertPixels_UYVY_to_YVYU_SSE2(width, height, src, src_pitch, dst, dst_pitch);
    }
#endif
    ଫେରନ୍ତୁ SDL_ConvertPixels_UYVY_to_YVYU_std(width, height, src, src_pitch, dst, dst_pitch);
}

ସ୍ଥିର bool SDL_ConvertPixels_YVYU_to_YUY2(ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height, ଅଚଳ ଶୂନ୍ୟ *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_pitch, ଶୂନ୍ୟ *dst, ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_pitch)
{
#ifdef SDL_SSE2_INTRINSICS
    ଯଦି (SDL_HasSSE2()) {
      ଫେରନ୍ତୁ SDL_ConvertPixels_YVYU_to_YUY2_SSE2(width, height, src, src_pitch, dst, dst_pitch);
    }
#endif
    ଫେରନ୍ତୁ SDL_ConvertPixels_YVYU_to_YUY2_std(width, height, src, src_pitch, dst, dst_pitch);
}

ସ୍ଥିର bool SDL_ConvertPixels_YVYU_to_UYVY(ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height, ଅଚଳ ଶୂନ୍ୟ *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_pitch, ଶୂନ୍ୟ *dst, ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_pitch)
{
#ifdef SDL_SSE2_INTRINSICS
    ଯଦି (SDL_HasSSE2()) {
      ଫେରନ୍ତୁ SDL_ConvertPixels_YVYU_to_UYVY_SSE2(width, height, src, src_pitch, dst, dst_pitch);
    }
#endif
    ଫେରନ୍ତୁ SDL_ConvertPixels_YVYU_to_UYVY_std(width, height, src, src_pitch, dst, dst_pitch);
}

ସ୍ଥିର bool SDL_ConvertPixels_Packed4_to_Packed4(ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height,
                                                SDL_PixelFormat src_format, ଅଚଳ ଶୂନ୍ୟ *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_pitch,
                                                SDL_PixelFormat dst_format, ଶୂନ୍ୟ *dst, ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_pitch)
{
    ବାଛ (src_format) {
    ସ୍ଥିତି SDL_PIXELFORMAT_YUY2:
        ବାଛ (dst_format) {
        ସ୍ଥିତି SDL_PIXELFORMAT_UYVY:
            ଫେରନ୍ତୁ SDL_ConvertPixels_YUY2_to_UYVY(width, height, src, src_pitch, dst, dst_pitch);
        ସ୍ଥିତି SDL_PIXELFORMAT_YVYU:
            ଫେରନ୍ତୁ SDL_ConvertPixels_YUY2_to_YVYU(width, height, src, src_pitch, dst, dst_pitch);
        ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
            ଭାଙ୍ଗ;
        }
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_PIXELFORMAT_UYVY:
        ବାଛ (dst_format) {
        ସ୍ଥିତି SDL_PIXELFORMAT_YUY2:
            ଫେରନ୍ତୁ SDL_ConvertPixels_UYVY_to_YUY2(width, height, src, src_pitch, dst, dst_pitch);
        ସ୍ଥିତି SDL_PIXELFORMAT_YVYU:
            ଫେରନ୍ତୁ SDL_ConvertPixels_UYVY_to_YVYU(width, height, src, src_pitch, dst, dst_pitch);
        ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
            ଭାଙ୍ଗ;
        }
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_PIXELFORMAT_YVYU:
        ବାଛ (dst_format) {
        ସ୍ଥିତି SDL_PIXELFORMAT_YUY2:
            ଫେରନ୍ତୁ SDL_ConvertPixels_YVYU_to_YUY2(width, height, src, src_pitch, dst, dst_pitch);
        ସ୍ଥିତି SDL_PIXELFORMAT_UYVY:
            ଫେରନ୍ତୁ SDL_ConvertPixels_YVYU_to_UYVY(width, height, src, src_pitch, dst, dst_pitch);
        ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
            ଭାଙ୍ଗ;
        }
        ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଭାଙ୍ଗ;
    }
    ଫେରନ୍ତୁ SDL_SetError("SDL_ConvertPixels_Packed4_to_Packed4: Unsupported YUV conversion: %s -> %s", SDL_GetPixelFormatName(src_format),
                        SDL_GetPixelFormatName(dst_format));
}

ସ୍ଥିର bool SDL_ConvertPixels_Planar2x2_to_Packed4(ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height,
                                                   SDL_PixelFormat src_format, ଅଚଳ ଶୂନ୍ୟ *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_pitch,
                                                   SDL_PixelFormat dst_format, ଶୂନ୍ୟ *dst, ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_pitch)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, y;
    ଅଚଳ Uint8 *srcY1, *srcY2, *srcU, *srcV;
    Uint32 srcY_pitch, srcUV_pitch;
    Uint32 src_Y_pitch_ବାମ, src_UV_pitch_ବାମ, srcUV_pixel_stride;
    Uint8 *dstY1, *dstY2, *dstU1, *dstU2, *dstV1, *dstV2;
    Uint32 dstY_pitch, dstUV_pitch;
    Uint32 dst_pitch_ବାମ;

    ଯଦି (src == dst) {
        ଫେରନ୍ତୁ SDL_SetError("Can't change YUV plane types in-place");
    }

    ଯଦି (!GetYUVPlanes(width, height, src_format, src, src_pitch,
                      &srcY1, &srcU, &srcV, &srcY_pitch, &srcUV_pitch)) {
        ଫେରନ୍ତୁ false;
    }
    srcY2 = srcY1 + srcY_pitch;
    src_Y_pitch_ବାମ = (srcY_pitch - width);

    ଯଦି (src_format == SDL_PIXELFORMAT_NV12 || src_format == SDL_PIXELFORMAT_NV21) {
        srcUV_pixel_stride = 2;
        src_UV_pitch_ବାମ = (srcUV_pitch - 2 * ((width + 1) / 2));
    } ଅନ୍ୟଥା {
        srcUV_pixel_stride = 1;
        src_UV_pitch_ବାମ = (srcUV_pitch - ((width + 1) / 2));
    }

    ଯଦି (!GetYUVPlanes(width, height, dst_format, dst, dst_pitch,
                      (ଅଚଳ Uint8 **)&dstY1, (ଅଚଳ Uint8 **)&dstU1, (ଅଚଳ Uint8 **)&dstV1,
                      &dstY_pitch, &dstUV_pitch)) {
        ଫେରନ୍ତୁ false;
    }
    dstY2 = dstY1 + dstY_pitch;
    dstU2 = dstU1 + dstUV_pitch;
    dstV2 = dstV1 + dstUV_pitch;
    dst_pitch_ବାମ = (dstY_pitch - 4 * ((width + 1) / 2));

    // Copy 2x2 blocks of pixels at a time
    ପାଇଁ (y = 0; y < (height - 1); y += 2) {
        ପାଇଁ (x = 0; x < (width - 1); x += 2) {
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
        ଯଦି (x == (width - 1)) {
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

        srcY1 += src_Y_pitch_ବାମ + srcY_pitch;
        srcY2 += src_Y_pitch_ବାମ + srcY_pitch;
        srcU += src_UV_pitch_ବାମ;
        srcV += src_UV_pitch_ବାମ;
        dstY1 += dst_pitch_ବାମ + dstY_pitch;
        dstY2 += dst_pitch_ବାମ + dstY_pitch;
        dstU1 += dst_pitch_ବାମ + dstUV_pitch;
        dstU2 += dst_pitch_ବାମ + dstUV_pitch;
        dstV1 += dst_pitch_ବାମ + dstUV_pitch;
        dstV2 += dst_pitch_ବାମ + dstUV_pitch;
    }

    // Last row
    ଯଦି (y == (height - 1)) {
        ପାଇଁ (x = 0; x < (width - 1); x += 2) {
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
        ଯଦି (x == (width - 1)) {
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
    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର bool SDL_ConvertPixels_Packed4_to_Planar2x2(ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height,
                                                   SDL_PixelFormat src_format, ଅଚଳ ଶୂନ୍ୟ *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_pitch,
                                                   SDL_PixelFormat dst_format, ଶୂନ୍ୟ *dst, ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_pitch)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, y;
    ଅଚଳ Uint8 *srcY1, *srcY2, *srcU1, *srcU2, *srcV1, *srcV2;
    Uint32 srcY_pitch, srcUV_pitch;
    Uint32 src_pitch_ବାମ;
    Uint8 *dstY1, *dstY2, *dstU, *dstV;
    Uint32 dstY_pitch, dstUV_pitch;
    Uint32 dst_Y_pitch_ବାମ, dst_UV_pitch_ବାମ, dstUV_pixel_stride;

    ଯଦି (src == dst) {
        ଫେରନ୍ତୁ SDL_SetError("Can't change YUV plane types in-place");
    }

    ଯଦି (!GetYUVPlanes(width, height, src_format, src, src_pitch,
                      &srcY1, &srcU1, &srcV1, &srcY_pitch, &srcUV_pitch)) {
        ଫେରନ୍ତୁ false;
    }
    srcY2 = srcY1 + srcY_pitch;
    srcU2 = srcU1 + srcUV_pitch;
    srcV2 = srcV1 + srcUV_pitch;
    src_pitch_ବାମ = (srcY_pitch - 4 * ((width + 1) / 2));

    ଯଦି (!GetYUVPlanes(width, height, dst_format, dst, dst_pitch,
                      (ଅଚଳ Uint8 **)&dstY1, (ଅଚଳ Uint8 **)&dstU, (ଅଚଳ Uint8 **)&dstV,
                      &dstY_pitch, &dstUV_pitch)) {
        ଫେରନ୍ତୁ false;
    }
    dstY2 = dstY1 + dstY_pitch;
    dst_Y_pitch_ବାମ = (dstY_pitch - width);

    ଯଦି (dst_format == SDL_PIXELFORMAT_NV12 || dst_format == SDL_PIXELFORMAT_NV21) {
        dstUV_pixel_stride = 2;
        dst_UV_pitch_ବାମ = (dstUV_pitch - 2 * ((width + 1) / 2));
    } ଅନ୍ୟଥା {
        dstUV_pixel_stride = 1;
        dst_UV_pitch_ବାମ = (dstUV_pitch - ((width + 1) / 2));
    }

    // Copy 2x2 blocks of pixels at a time
    ପାଇଁ (y = 0; y < (height - 1); y += 2) {
        ପାଇଁ (x = 0; x < (width - 1); x += 2) {
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
        ଯଦି (x == (width - 1)) {
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

        srcY1 += src_pitch_ବାମ + srcY_pitch;
        srcY2 += src_pitch_ବାମ + srcY_pitch;
        srcU1 += src_pitch_ବାମ + srcUV_pitch;
        srcU2 += src_pitch_ବାମ + srcUV_pitch;
        srcV1 += src_pitch_ବାମ + srcUV_pitch;
        srcV2 += src_pitch_ବାମ + srcUV_pitch;
        dstY1 += dst_Y_pitch_ବାମ + dstY_pitch;
        dstY2 += dst_Y_pitch_ବାମ + dstY_pitch;
        dstU += dst_UV_pitch_ବାମ;
        dstV += dst_UV_pitch_ବାମ;
    }

    // Last row
    ଯଦି (y == (height - 1)) {
        ପାଇଁ (x = 0; x < (width - 1); x += 2) {
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
        ଯଦି (x == (width - 1)) {
            *dstY1 = *srcY1;
            *dstU = *srcU1;
            *dstV = *srcV1;
        }
    }
    ଫେରନ୍ତୁ true;
}

#endif // SDL_HAVE_YUV

bool SDL_ConvertPixels_YUV_to_YUV(ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height,
                                  SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ଅଚଳ ଶୂନ୍ୟ *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_pitch,
                                  SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, ଶୂନ୍ୟ *dst, ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_pitch)
{
#ifdef SDL_HAVE_YUV
    ଯଦି (src_colorspace != dst_colorspace) {
        ଫେରନ୍ତୁ SDL_SetError("SDL_ConvertPixels_YUV_to_YUV: colorspace conversion not supported");
    }

    ଯଦି (src_format == dst_format) {
        ଯଦି (src == dst) {
            // Nothing to do
            ଫେରନ୍ତୁ true;
        }
        ଫେରନ୍ତୁ SDL_ConvertPixels_YUV_to_YUV_Copy(width, height, src_format, src, src_pitch, dst, dst_pitch);
    }

    ଯଦି (IsPlanar2x2Format(src_format) && IsPlanar2x2Format(dst_format)) {
        ଫେରନ୍ତୁ SDL_ConvertPixels_Planar2x2_to_Planar2x2(width, height, src_format, src, src_pitch, dst_format, dst, dst_pitch);
    } ଅନ୍ୟଥା ଯଦି (IsPacked4Format(src_format) && IsPacked4Format(dst_format)) {
        ଫେରନ୍ତୁ SDL_ConvertPixels_Packed4_to_Packed4(width, height, src_format, src, src_pitch, dst_format, dst, dst_pitch);
    } ଅନ୍ୟଥା ଯଦି (IsPlanar2x2Format(src_format) && IsPacked4Format(dst_format)) {
        ଫେରନ୍ତୁ SDL_ConvertPixels_Planar2x2_to_Packed4(width, height, src_format, src, src_pitch, dst_format, dst, dst_pitch);
    } ଅନ୍ୟଥା ଯଦି (IsPacked4Format(src_format) && IsPlanar2x2Format(dst_format)) {
        ଫେରନ୍ତୁ SDL_ConvertPixels_Packed4_to_Planar2x2(width, height, src_format, src, src_pitch, dst_format, dst, dst_pitch);
    } ଅନ୍ୟଥା {
        ଫେରନ୍ତୁ SDL_SetError("SDL_ConvertPixels_YUV_to_YUV: Unsupported YUV conversion: %s -> %s", SDL_GetPixelFormatName(src_format),
                            SDL_GetPixelFormatName(dst_format));
    }
#ଅନ୍ୟଥା
    ଫେରନ୍ତୁ SDL_SetError("SDL not built with YUV support");
#endif
}
