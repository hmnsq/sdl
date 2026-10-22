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
#అన్తర్భావ "SDL_internal.h"

#అన్తర్భావ "SDL_pixels_c.h"
#అన్తర్భావ "SDL_yuv_c.h"

#అన్తర్భావ "yuv2rgb/yuv_rgb.h"


స్థిర bool IsPlanar1x1Format(SDL_PixelFormat format)
{
    తిరిగి format == SDL_PIXELFORMAT_I444 || format == SDL_PIXELFORMAT_I4FL;
}

స్థిర bool IsPlanar2x2Format(SDL_PixelFormat format)
{
    తిరిగి format == SDL_PIXELFORMAT_YV12 ||
           format == SDL_PIXELFORMAT_IYUV ||
           format == SDL_PIXELFORMAT_NV12 ||
           format == SDL_PIXELFORMAT_NV21 ||
           format == SDL_PIXELFORMAT_P010 ||
           format == SDL_PIXELFORMAT_I0FL;
}

స్థిర bool IsPacked4Format(Uint32 format)
{
    తిరిగి format == SDL_PIXELFORMAT_YUY2 || format == SDL_PIXELFORMAT_UYVY || format == SDL_PIXELFORMAT_YVYU;
}

/*
 * Calculate YUV size and pitch. Check for overflow.
 * Output 'pitch' that can be used with SDL_ConvertPixels()
 */
bool SDL_CalculateYUVSize(SDL_PixelFormat format, పూర్ణాంకం w, పూర్ణాంకం h, size_t *కొలత, size_t *pitch)
{
    పూర్ణాంకం sz_plane = 0, sz_plane_chroma = 0, sz_plane_packed = 0;

    ఒకవేళ (IsPlanar1x1Format(format)) {
        /* sz_plane == w * h * bpp; */
        size_t s1;
        ఒకవేళ (!SDL_కొలత_mul_check_అధికప్రవాహం(w, h, &s1)) {
            తిరిగి SDL_సమితి_Error("width * height would overflow");
        }
        ఒకవేళ (!SDL_కొలత_mul_check_అధికప్రవాహం(s1, SDL_BYTESPERPIXEL(format), &s1)) {
            తిరిగి SDL_సమితి_Error("width * height * bpp would overflow");
        }
        sz_plane = (పూర్ణాంకం)s1;
        sz_plane_chroma = sz_plane;
    } లేకపోతే ఒకవేళ (IsPlanar2x2Format(format)) {
        {
            /* sz_plane == w * h * bpp; */
            size_t s1;
            ఒకవేళ (!SDL_కొలత_mul_check_అధికప్రవాహం(w, h, &s1)) {
                తిరిగి SDL_సమితి_Error("width * height would overflow");
            }
            ఒకవేళ (!SDL_కొలత_mul_check_అధికప్రవాహం(s1, SDL_BYTESPERPIXEL(format), &s1)) {
                తిరిగి SDL_సమితి_Error("width * height * bpp would overflow");
            }
            sz_plane = (పూర్ణాంకం)s1;
        }

        {
            /* sz_plane_chroma == ((w + 1) / 2) * ((h + 1) / 2) * bpp; */
            size_t s1, s2, s3;
            ఒకవేళ (!SDL_కొలత_కూడు_check_అధికప్రవాహం(w, 1, &s1)) {
                తిరిగి SDL_సమితి_Error("width + 1 would overflow");
            }
            s1 = s1 / 2;
            ఒకవేళ (!SDL_కొలత_కూడు_check_అధికప్రవాహం(h, 1, &s2)) {
                తిరిగి SDL_సమితి_Error("height + 1 would overflow");
            }
            s2 = s2 / 2;
            ఒకవేళ (!SDL_కొలత_mul_check_అధికప్రవాహం(s1, s2, &s3)) {
                తిరిగి SDL_సమితి_Error("width * height would overflow");
            }
            ఒకవేళ (!SDL_కొలత_mul_check_అధికప్రవాహం(s3, SDL_BYTESPERPIXEL(format), &s3)) {
                తిరిగి SDL_సమితి_Error("width * height * bpp would overflow");
            }
            sz_plane_chroma = (పూర్ణాంకం)s3;
        }
    } లేకపోతే ఒకవేళ (IsPacked4Format(format)) {
        /* sz_plane_packed == ((w + 1) / 2) * h; */
        size_t s1, s2;
        ఒకవేళ (!SDL_కొలత_కూడు_check_అధికప్రవాహం(w, 1, &s1)) {
            తిరిగి SDL_సమితి_Error("width + 1 would overflow");
        }
        s1 = s1 / 2;
        ఒకవేళ (!SDL_కొలత_mul_check_అధికప్రవాహం(s1, h, &s2)) {
            తిరిగి SDL_సమితి_Error("width * height would overflow");
        }
        sz_plane_packed = (పూర్ణాంకం) s2;
    } లేకపోతే {
        తిరిగి SDL_Unsupported();
    }

    ఎంపిక (format) {
    స్థితి SDL_PIXELFORMAT_YV12: /**< Planar mode: Y + V + U  (3 planes) */
    స్థితి SDL_PIXELFORMAT_IYUV: /**< Planar mode: Y + U + V  (3 planes) */
    స్థితి SDL_PIXELFORMAT_I444: /**< Planar mode: Y + U + V  (3 planes) */
    స్థితి SDL_PIXELFORMAT_I0FL: /**< Planar mode: Y + U + V  (3 planes) */
    స్థితి SDL_PIXELFORMAT_I4FL: /**< Planar mode: Y + U + V  (3 planes) */

        ఒకవేళ (pitch) {
            *pitch = w * SDL_BYTESPERPIXEL(format);
        }

        ఒకవేళ (కొలత) {
            // dst_size == sz_plane + sz_plane_chroma + sz_plane_chroma;
            size_t s1, s2;
            ఒకవేళ (!SDL_కొలత_కూడు_check_అధికప్రవాహం(sz_plane, sz_plane_chroma, &s1)) {
                తిరిగి SDL_సమితి_Error("Y + U would overflow");
            }
            ఒకవేళ (!SDL_కొలత_కూడు_check_అధికప్రవాహం(s1, sz_plane_chroma, &s2)) {
                తిరిగి SDL_సమితి_Error("Y + U + V would overflow");
            }
            *కొలత = (పూర్ణాంకం)s2;
        }
        ఆపు;

    స్థితి SDL_PIXELFORMAT_YUY2: /**< Packed mode: Y0+U0+Y1+V0 (1 plane) */
    స్థితి SDL_PIXELFORMAT_UYVY: /**< Packed mode: U0+Y0+V0+Y1 (1 plane) */
    స్థితి SDL_PIXELFORMAT_YVYU: /**< Packed mode: Y0+V0+Y1+U0 (1 plane) */

        ఒకవేళ (pitch) {
            /* pitch == ((w + 1) / 2) * 4; */
           size_t p1, p2;
           ఒకవేళ (!SDL_కొలత_కూడు_check_అధికప్రవాహం(w, 1, &p1)) {
               తిరిగి SDL_సమితి_Error("width + 1 would overflow");
           }
           p1 = p1 / 2;
           ఒకవేళ (!SDL_కొలత_mul_check_అధికప్రవాహం(p1, 4, &p2)) {
               తిరిగి SDL_సమితి_Error("width * 4 would overflow");
           }
           *pitch = p2;
        }

        ఒకవేళ (కొలత) {
            /* dst_size == 4 * sz_plane_packed; */
            size_t s1;
            ఒకవేళ (!SDL_కొలత_mul_check_అధికప్రవాహం(sz_plane_packed, 4, &s1)) {
                తిరిగి SDL_సమితి_Error("plane * 4 would overflow");
            }
            *కొలత = (పూర్ణాంకం) s1;
        }
        ఆపు;

    స్థితి SDL_PIXELFORMAT_NV12: /**< Planar mode: Y + U/V interleaved  (2 planes) */
    స్థితి SDL_PIXELFORMAT_NV21: /**< Planar mode: Y + V/U interleaved  (2 planes) */
    స్థితి SDL_PIXELFORMAT_P010: /**< Planar mode: Y + U/V interleaved, 10 bit  (2 planes) */
        ఒకవేళ (pitch) {
            *pitch = w * SDL_BYTESPERPIXEL(format);
        }

        ఒకవేళ (కొలత) {
            // dst_size == sz_plane + sz_plane_chroma + sz_plane_chroma;
            size_t s1, s2;
            ఒకవేళ (!SDL_కొలత_కూడు_check_అధికప్రవాహం(sz_plane, sz_plane_chroma, &s1)) {
                తిరిగి SDL_సమితి_Error("Y + U would overflow");
            }
            ఒకవేళ (!SDL_కొలత_కూడు_check_అధికప్రవాహం(s1, sz_plane_chroma, &s2)) {
                తిరిగి SDL_సమితి_Error("Y + U + V would overflow");
            }
            *కొలత = (పూర్ణాంకం) s2;
        }
        ఆపు;

    అప్రమేయ:
        తిరిగి SDL_Unsupported();
    }

    తిరిగి true;
}

#నిర్వచితమైతే SDL_HAVE_YUV

స్థిర bool GetYUVConversionType(SDL_Colorspace colorspace, పూర్ణాంకం w, పూర్ణాంకం h, పూర్ణాంకం బిట్లు_చొప్పున_pixel, YCbCrType *yuv_type)
{
    ఒకవేళ (SDL_ISCOLORSPACE_మాతృక_BT601(colorspace)) {
        ఒకవేళ (SDL_ISCOLORSPACE_LIMITED_RANGE(colorspace)) {
            *yuv_type = YCBCR_601_LIMITED;
        } లేకపోతే {
            *yuv_type = YCBCR_601_నిండిన;
        }
        తిరిగి true;
    }

    ఒకవేళ (SDL_ISCOLORSPACE_మాతృక_BT709(colorspace)) {
        ఒకవేళ (SDL_ISCOLORSPACE_LIMITED_RANGE(colorspace)) {
            *yuv_type = YCBCR_709_LIMITED;
        } లేకపోతే {
            *yuv_type = YCBCR_709_నిండిన;
        }
        తిరిగి true;
    }

    ఒకవేళ (SDL_ISCOLORSPACE_మాతృక_BT2020_NCL(colorspace)) {
        ఒకవేళ (SDL_ISCOLORSPACE_నిండిన_RANGE(colorspace)) {
            *yuv_type = YCBCR_2020_NCL_నిండిన;
            తిరిగి true;
        }
    }

    ఒకవేళ (SDL_COLORSPACEMATRIX(colorspace) == SDL_మాతృక_COEFFICIENTS_UNSPECIFIED) {
        ఎంపిక (బిట్లు_చొప్పున_pixel) {
        స్థితి 8:
            ఒకవేళ (h <= YUV_SD_పరిమితి) {
                ఒకవేళ (SDL_ISCOLORSPACE_LIMITED_RANGE(colorspace)) {
                    *yuv_type = YCBCR_601_LIMITED;
                } లేకపోతే {
                    *yuv_type = YCBCR_601_నిండిన;
                }
            } లేకపోతే {
                ఒకవేళ (SDL_ISCOLORSPACE_LIMITED_RANGE(colorspace)) {
                    *yuv_type = YCBCR_709_LIMITED;
                } లేకపోతే {
                    *yuv_type = YCBCR_709_నిండిన;
                }
            }
			తిరిగి true;
        స్థితి 10:
        స్థితి 16:
            ఒకవేళ (SDL_ISCOLORSPACE_నిండిన_RANGE(colorspace)) {
                *yuv_type = YCBCR_2020_NCL_నిండిన;
                తిరిగి true;
            }
            ఆపు;
        అప్రమేయ:
            ఆపు;
        }
    }

    తిరిగి SDL_సమితి_Error("Unsupported YUV colorspace");
}

స్థిర bool GetYUVPlanes(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, SDL_PixelFormat format, స్థిరరాశి శూన్య *yuv, పూర్ణాంకం yuv_pitch,
                         స్థిరరాశి Uint8 **y, స్థిరరాశి Uint8 **u, స్థిరరాశి Uint8 **v, Uint32 *y_stride, Uint32 *uv_stride)
{
    స్థిరరాశి Uint8 *planes[3] = { ఖాళీ, ఖాళీ, ఖాళీ };
    పూర్ణాంకం pitches[3] = { 0, 0, 0 };
    పూర్ణాంకం uv_వెడల్పు;

    ఎంపిక (format) {
    స్థితి SDL_PIXELFORMAT_YV12:
    స్థితి SDL_PIXELFORMAT_IYUV:
    స్థితి SDL_PIXELFORMAT_I0FL:
        pitches[0] = yuv_pitch;
        pitches[1] = ((pitches[0] / SDL_BYTESPERPIXEL(format) + 1) / 2) * SDL_BYTESPERPIXEL(format);
        pitches[2] = pitches[1];
        planes[0] = (స్థిరరాశి Uint8 *)yuv;
        planes[1] = planes[0] + pitches[0] * ఎత్తు;
        planes[2] = planes[1] + pitches[1] * ((ఎత్తు + 1) / 2);
        ఆపు;
    స్థితి SDL_PIXELFORMAT_YUY2:
    స్థితి SDL_PIXELFORMAT_UYVY:
    స్థితి SDL_PIXELFORMAT_YVYU:
        pitches[0] = yuv_pitch;
        planes[0] = (స్థిరరాశి Uint8 *)yuv;
        ఆపు;
    స్థితి SDL_PIXELFORMAT_NV12:
    స్థితి SDL_PIXELFORMAT_NV21:
        pitches[0] = yuv_pitch;
        pitches[1] = 2 * ((pitches[0] + 1) / 2);
        planes[0] = (స్థిరరాశి Uint8 *)yuv;
        planes[1] = planes[0] + pitches[0] * ఎత్తు;
        ఆపు;
    స్థితి SDL_PIXELFORMAT_P010:
        pitches[0] = yuv_pitch;
        uv_వెడల్పు = ((వెడల్పు + 1) / 2) * 2;
        pitches[1] = SDL_max(pitches[0], (పూర్ణాంకం)(uv_వెడల్పు * పరిమాణం(Uint16)));
        planes[0] = (స్థిరరాశి Uint8 *)yuv;
        planes[1] = planes[0] + pitches[0] * ఎత్తు;
        ఆపు;
    స్థితి SDL_PIXELFORMAT_I444:
    స్థితి SDL_PIXELFORMAT_I4FL:
        pitches[0] = yuv_pitch;
        pitches[1] = pitches[0];
        pitches[2] = pitches[1];
        planes[0] = (స్థిరరాశి Uint8 *)yuv;
        planes[1] = planes[0] + pitches[0] * ఎత్తు;
        planes[2] = planes[1] + pitches[1] * ఎత్తు;
        ఆపు;
    అప్రమేయ:
        తిరిగి SDL_సమితి_Error("GetYUVPlanes(): Unsupported YUV format: %s", SDL_GetPixelFormatName(format));
    }

    ఎంపిక (format) {
    స్థితి SDL_PIXELFORMAT_YV12:
        *y = planes[0];
        *y_stride = pitches[0];
        *v = planes[1];
        *u = planes[2];
        *uv_stride = pitches[1];
        ఆపు;
    స్థితి SDL_PIXELFORMAT_IYUV:
    స్థితి SDL_PIXELFORMAT_I444:
    స్థితి SDL_PIXELFORMAT_I0FL:
    స్థితి SDL_PIXELFORMAT_I4FL:
        *y = planes[0];
        *y_stride = pitches[0];
        *v = planes[2];
        *u = planes[1];
        *uv_stride = pitches[1];
        ఆపు;
    స్థితి SDL_PIXELFORMAT_YUY2:
        *y = planes[0];
        *y_stride = pitches[0];
        *v = *y + 3;
        *u = *y + 1;
        *uv_stride = pitches[0];
        ఆపు;
    స్థితి SDL_PIXELFORMAT_UYVY:
        *y = planes[0] + 1;
        *y_stride = pitches[0];
        *v = *y + 1;
        *u = *y - 1;
        *uv_stride = pitches[0];
        ఆపు;
    స్థితి SDL_PIXELFORMAT_YVYU:
        *y = planes[0];
        *y_stride = pitches[0];
        *v = *y + 1;
        *u = *y + 3;
        *uv_stride = pitches[0];
        ఆపు;
    స్థితి SDL_PIXELFORMAT_NV12:
        *y = planes[0];
        *y_stride = pitches[0];
        *u = planes[1];
        *v = *u + 1;
        *uv_stride = pitches[1];
        ఆపు;
    స్థితి SDL_PIXELFORMAT_NV21:
        *y = planes[0];
        *y_stride = pitches[0];
        *v = planes[1];
        *u = *v + 1;
        *uv_stride = pitches[1];
        ఆపు;
    స్థితి SDL_PIXELFORMAT_P010:
        *y = planes[0];
        *y_stride = pitches[0];
        *u = planes[1];
        *v = *u + పరిమాణం(Uint16);
        *uv_stride = pitches[1];
        ఆపు;
    అప్రమేయ:
        // Should have caught this above
        తిరిగి SDL_సమితి_Error("GetYUVPlanes[2]: Unsupported YUV format: %s", SDL_GetPixelFormatName(format));
    }
    తిరిగి true;
}

#నిర్వచితమైతే SDL_SSE2_INTRINSICS
స్థిర bool SDL_TARGETING("sse2") yuv_rgb_sse(
    SDL_PixelFormat src_format, SDL_PixelFormat dst_format,
    Uint32 వెడల్పు, Uint32 ఎత్తు,
    స్థిరరాశి Uint8 *y, స్థిరరాశి Uint8 *u, స్థిరరాశి Uint8 *v, Uint32 y_stride, Uint32 uv_stride,
    Uint8 *rgb, Uint32 rgb_stride,
    YCbCrType yuv_type)
{
    ఒకవేళ (!SDL_HasSSE2()) {
        తిరిగి false;
    }

    ఒకవేళ (src_format == SDL_PIXELFORMAT_YV12 ||
        src_format == SDL_PIXELFORMAT_IYUV) {

        ఎంపిక (dst_format) {
        స్థితి SDL_PIXELFORMAT_RGB565:
            yuv420_rgb565_sseu(వెడల్పు, ఎత్తు, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            తిరిగి true;
        స్థితి SDL_PIXELFORMAT_RGB24:
            yuv420_rgb24_sseu(వెడల్పు, ఎత్తు, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            తిరిగి true;
        స్థితి SDL_PIXELFORMAT_RGBX8888:
        స్థితి SDL_PIXELFORMAT_RGBA8888:
            yuv420_rgba_sseu(వెడల్పు, ఎత్తు, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            తిరిగి true;
        స్థితి SDL_PIXELFORMAT_BGRX8888:
        స్థితి SDL_PIXELFORMAT_BGRA8888:
            yuv420_bgra_sseu(వెడల్పు, ఎత్తు, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            తిరిగి true;
        స్థితి SDL_PIXELFORMAT_XRGB8888:
        స్థితి SDL_PIXELFORMAT_ARGB8888:
            yuv420_argb_sseu(వెడల్పు, ఎత్తు, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            తిరిగి true;
        స్థితి SDL_PIXELFORMAT_XBGR8888:
        స్థితి SDL_PIXELFORMAT_ABGR8888:
            yuv420_abgr_sseu(వెడల్పు, ఎత్తు, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            తిరిగి true;
        అప్రమేయ:
            ఆపు;
        }
    }

    ఒకవేళ (src_format == SDL_PIXELFORMAT_YUY2 ||
        src_format == SDL_PIXELFORMAT_UYVY ||
        src_format == SDL_PIXELFORMAT_YVYU) {

        ఎంపిక (dst_format) {
        స్థితి SDL_PIXELFORMAT_RGB565:
            yuv422_rgb565_sseu(వెడల్పు, ఎత్తు, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            తిరిగి true;
        స్థితి SDL_PIXELFORMAT_RGB24:
            yuv422_rgb24_sseu(వెడల్పు, ఎత్తు, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            తిరిగి true;
        స్థితి SDL_PIXELFORMAT_RGBX8888:
        స్థితి SDL_PIXELFORMAT_RGBA8888:
            yuv422_rgba_sseu(వెడల్పు, ఎత్తు, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            తిరిగి true;
        స్థితి SDL_PIXELFORMAT_BGRX8888:
        స్థితి SDL_PIXELFORMAT_BGRA8888:
            yuv422_bgra_sseu(వెడల్పు, ఎత్తు, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            తిరిగి true;
        స్థితి SDL_PIXELFORMAT_XRGB8888:
        స్థితి SDL_PIXELFORMAT_ARGB8888:
            yuv422_argb_sseu(వెడల్పు, ఎత్తు, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            తిరిగి true;
        స్థితి SDL_PIXELFORMAT_XBGR8888:
        స్థితి SDL_PIXELFORMAT_ABGR8888:
            yuv422_abgr_sseu(వెడల్పు, ఎత్తు, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            తిరిగి true;
        అప్రమేయ:
            ఆపు;
        }
    }

    ఒకవేళ (src_format == SDL_PIXELFORMAT_NV12 ||
        src_format == SDL_PIXELFORMAT_NV21) {

        ఎంపిక (dst_format) {
        స్థితి SDL_PIXELFORMAT_RGB565:
            yuvnv12_rgb565_sseu(వెడల్పు, ఎత్తు, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            తిరిగి true;
        స్థితి SDL_PIXELFORMAT_RGB24:
            yuvnv12_rgb24_sseu(వెడల్పు, ఎత్తు, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            తిరిగి true;
        స్థితి SDL_PIXELFORMAT_RGBX8888:
        స్థితి SDL_PIXELFORMAT_RGBA8888:
            yuvnv12_rgba_sseu(వెడల్పు, ఎత్తు, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            తిరిగి true;
        స్థితి SDL_PIXELFORMAT_BGRX8888:
        స్థితి SDL_PIXELFORMAT_BGRA8888:
            yuvnv12_bgra_sseu(వెడల్పు, ఎత్తు, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            తిరిగి true;
        స్థితి SDL_PIXELFORMAT_XRGB8888:
        స్థితి SDL_PIXELFORMAT_ARGB8888:
            yuvnv12_argb_sseu(వెడల్పు, ఎత్తు, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            తిరిగి true;
        స్థితి SDL_PIXELFORMAT_XBGR8888:
        స్థితి SDL_PIXELFORMAT_ABGR8888:
            yuvnv12_abgr_sseu(వెడల్పు, ఎత్తు, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            తిరిగి true;
        అప్రమేయ:
            ఆపు;
        }
    }
    తిరిగి false;
}
#లేకపోతే
స్థిర bool yuv_rgb_sse(
    SDL_PixelFormat src_format, SDL_PixelFormat dst_format,
    Uint32 వెడల్పు, Uint32 ఎత్తు,
    స్థిరరాశి Uint8 *y, స్థిరరాశి Uint8 *u, స్థిరరాశి Uint8 *v, Uint32 y_stride, Uint32 uv_stride,
    Uint8 *rgb, Uint32 rgb_stride,
    YCbCrType yuv_type)
{
    తిరిగి false;
}
#అయితే_ముగింపు

#నిర్వచితమైతే SDL_LSX_INTRINSICS
స్థిర bool yuv_rgb_lsx(
    SDL_PixelFormat src_format, SDL_PixelFormat dst_format,
    Uint32 వెడల్పు, Uint32 ఎత్తు,
    స్థిరరాశి Uint8 *y, స్థిరరాశి Uint8 *u, స్థిరరాశి Uint8 *v, Uint32 y_stride, Uint32 uv_stride,
    Uint8 *rgb, Uint32 rgb_stride,
    YCbCrType yuv_type)
{
    ఒకవేళ (!SDL_HasLSX()) {
        తిరిగి false;
    }
    ఒకవేళ (src_format == SDL_PIXELFORMAT_YV12 ||
        src_format == SDL_PIXELFORMAT_IYUV) {

        ఎంపిక (dst_format) {
        స్థితి SDL_PIXELFORMAT_RGB24:
            yuv420_rgb24_lsx(వెడల్పు, ఎత్తు, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            తిరిగి true;
        స్థితి SDL_PIXELFORMAT_RGBX8888:
        స్థితి SDL_PIXELFORMAT_RGBA8888:
            yuv420_rgba_lsx(వెడల్పు, ఎత్తు, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            తిరిగి true;
        స్థితి SDL_PIXELFORMAT_BGRX8888:
        స్థితి SDL_PIXELFORMAT_BGRA8888:
            yuv420_bgra_lsx(వెడల్పు, ఎత్తు, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            తిరిగి true;
        స్థితి SDL_PIXELFORMAT_XRGB8888:
        స్థితి SDL_PIXELFORMAT_ARGB8888:
            yuv420_argb_lsx(వెడల్పు, ఎత్తు, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            తిరిగి true;
        స్థితి SDL_PIXELFORMAT_XBGR8888:
        స్థితి SDL_PIXELFORMAT_ABGR8888:
            yuv420_abgr_lsx(వెడల్పు, ఎత్తు, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            తిరిగి true;
        అప్రమేయ:
            ఆపు;
        }
    }
    తిరిగి false;
}
#లేకపోతే
స్థిర bool yuv_rgb_lsx(
    SDL_PixelFormat src_format, SDL_PixelFormat dst_format,
    Uint32 వెడల్పు, Uint32 ఎత్తు,
    స్థిరరాశి Uint8 *y, స్థిరరాశి Uint8 *u, స్థిరరాశి Uint8 *v, Uint32 y_stride, Uint32 uv_stride,
    Uint8 *rgb, Uint32 rgb_stride,
    YCbCrType yuv_type)
{
    తిరిగి false;
}
#అయితే_ముగింపు

స్థిర bool yuv_rgb_std(
    SDL_PixelFormat src_format, SDL_PixelFormat dst_format,
    Uint32 వెడల్పు, Uint32 ఎత్తు,
    స్థిరరాశి Uint8 *y, స్థిరరాశి Uint8 *u, స్థిరరాశి Uint8 *v, Uint32 y_stride, Uint32 uv_stride,
    Uint8 *rgb, Uint32 rgb_stride,
    YCbCrType yuv_type)
{
    ఒకవేళ (src_format == SDL_PIXELFORMAT_YV12 ||
        src_format == SDL_PIXELFORMAT_IYUV) {

        ఎంపిక (dst_format) {
        స్థితి SDL_PIXELFORMAT_RGB565:
            yuv420_rgb565_std(వెడల్పు, ఎత్తు, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            తిరిగి true;
        స్థితి SDL_PIXELFORMAT_RGB24:
            yuv420_rgb24_std(వెడల్పు, ఎత్తు, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            తిరిగి true;
        స్థితి SDL_PIXELFORMAT_RGBX8888:
        స్థితి SDL_PIXELFORMAT_RGBA8888:
            yuv420_rgba_std(వెడల్పు, ఎత్తు, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            తిరిగి true;
        స్థితి SDL_PIXELFORMAT_BGRX8888:
        స్థితి SDL_PIXELFORMAT_BGRA8888:
            yuv420_bgra_std(వెడల్పు, ఎత్తు, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            తిరిగి true;
        స్థితి SDL_PIXELFORMAT_XRGB8888:
        స్థితి SDL_PIXELFORMAT_ARGB8888:
            yuv420_argb_std(వెడల్పు, ఎత్తు, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            తిరిగి true;
        స్థితి SDL_PIXELFORMAT_XBGR8888:
        స్థితి SDL_PIXELFORMAT_ABGR8888:
            yuv420_abgr_std(వెడల్పు, ఎత్తు, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            తిరిగి true;
        అప్రమేయ:
            ఆపు;
        }
    }

    ఒకవేళ (src_format == SDL_PIXELFORMAT_I444) {

        ఎంపిక (dst_format) {
        స్థితి SDL_PIXELFORMAT_RGBX8888:
        స్థితి SDL_PIXELFORMAT_RGBA8888:
            yuv444_rgba_std(వెడల్పు, ఎత్తు, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            తిరిగి true;
        స్థితి SDL_PIXELFORMAT_BGRX8888:
        స్థితి SDL_PIXELFORMAT_BGRA8888:
            yuv444_bgra_std(వెడల్పు, ఎత్తు, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            తిరిగి true;
        స్థితి SDL_PIXELFORMAT_XRGB8888:
        స్థితి SDL_PIXELFORMAT_ARGB8888:
            yuv444_argb_std(వెడల్పు, ఎత్తు, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            తిరిగి true;
        స్థితి SDL_PIXELFORMAT_XBGR8888:
        స్థితి SDL_PIXELFORMAT_ABGR8888:
            yuv444_abgr_std(వెడల్పు, ఎత్తు, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            తిరిగి true;
        అప్రమేయ:
            ఆపు;
        }
    }

    ఒకవేళ (src_format == SDL_PIXELFORMAT_YUY2 ||
        src_format == SDL_PIXELFORMAT_UYVY ||
        src_format == SDL_PIXELFORMAT_YVYU) {

        ఎంపిక (dst_format) {
        స్థితి SDL_PIXELFORMAT_RGB565:
            yuv422_rgb565_std(వెడల్పు, ఎత్తు, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            తిరిగి true;
        స్థితి SDL_PIXELFORMAT_RGB24:
            yuv422_rgb24_std(వెడల్పు, ఎత్తు, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            తిరిగి true;
        స్థితి SDL_PIXELFORMAT_RGBX8888:
        స్థితి SDL_PIXELFORMAT_RGBA8888:
            yuv422_rgba_std(వెడల్పు, ఎత్తు, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            తిరిగి true;
        స్థితి SDL_PIXELFORMAT_BGRX8888:
        స్థితి SDL_PIXELFORMAT_BGRA8888:
            yuv422_bgra_std(వెడల్పు, ఎత్తు, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            తిరిగి true;
        స్థితి SDL_PIXELFORMAT_XRGB8888:
        స్థితి SDL_PIXELFORMAT_ARGB8888:
            yuv422_argb_std(వెడల్పు, ఎత్తు, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            తిరిగి true;
        స్థితి SDL_PIXELFORMAT_XBGR8888:
        స్థితి SDL_PIXELFORMAT_ABGR8888:
            yuv422_abgr_std(వెడల్పు, ఎత్తు, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            తిరిగి true;
        అప్రమేయ:
            ఆపు;
        }
    }

    ఒకవేళ (src_format == SDL_PIXELFORMAT_NV12 ||
        src_format == SDL_PIXELFORMAT_NV21) {

        ఎంపిక (dst_format) {
        స్థితి SDL_PIXELFORMAT_RGB565:
            yuvnv12_rgb565_std(వెడల్పు, ఎత్తు, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            తిరిగి true;
        స్థితి SDL_PIXELFORMAT_RGB24:
            yuvnv12_rgb24_std(వెడల్పు, ఎత్తు, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            తిరిగి true;
        స్థితి SDL_PIXELFORMAT_RGBX8888:
        స్థితి SDL_PIXELFORMAT_RGBA8888:
            yuvnv12_rgba_std(వెడల్పు, ఎత్తు, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            తిరిగి true;
        స్థితి SDL_PIXELFORMAT_BGRX8888:
        స్థితి SDL_PIXELFORMAT_BGRA8888:
            yuvnv12_bgra_std(వెడల్పు, ఎత్తు, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            తిరిగి true;
        స్థితి SDL_PIXELFORMAT_XRGB8888:
        స్థితి SDL_PIXELFORMAT_ARGB8888:
            yuvnv12_argb_std(వెడల్పు, ఎత్తు, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            తిరిగి true;
        స్థితి SDL_PIXELFORMAT_XBGR8888:
        స్థితి SDL_PIXELFORMAT_ABGR8888:
            yuvnv12_abgr_std(వెడల్పు, ఎత్తు, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            తిరిగి true;
        అప్రమేయ:
            ఆపు;
        }
    }

    ఒకవేళ (src_format == SDL_PIXELFORMAT_P010) {
        ఎంపిక (dst_format) {
        స్థితి SDL_PIXELFORMAT_XBGR2101010:
            yuvp010_xbgr2101010_std(వెడల్పు, ఎత్తు, (స్థిరరాశి uint16_t *)y, (స్థిరరాశి uint16_t *)u, (స్థిరరాశి uint16_t *)v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            తిరిగి true;
        అప్రమేయ:
            ఆపు;
        }
    }

    ఒకవేళ (src_format == SDL_PIXELFORMAT_I0FL) {
        ఎంపిక (dst_format) {
        స్థితి SDL_PIXELFORMAT_RGB48:
            yuvi0fl_rgb48_std(వెడల్పు, ఎత్తు, (స్థిరరాశి uint16_t *)y, (స్థిరరాశి uint16_t *)u, (స్థిరరాశి uint16_t *)v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            తిరిగి true;
        అప్రమేయ:
            ఆపు;
        }
    }

    ఒకవేళ (src_format == SDL_PIXELFORMAT_I4FL) {
        ఎంపిక (dst_format) {
        స్థితి SDL_PIXELFORMAT_RGB48:
            yuvi4fl_rgb48_std(వెడల్పు, ఎత్తు, (స్థిరరాశి uint16_t *)y, (స్థిరరాశి uint16_t *)u, (స్థిరరాశి uint16_t *)v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            తిరిగి true;
        అప్రమేయ:
            ఆపు;
        }
    }
    తిరిగి false;
}

bool SDL_Convert_Pixels_YUV_గమ్యం_RGB(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు,
                                  SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, స్థిరరాశి శూన్య *src, పూర్ణాంకం src_pitch,
                                  SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, శూన్య *dst, పూర్ణాంకం dst_pitch)
{
    స్థిరరాశి Uint8 *y = ఖాళీ;
    స్థిరరాశి Uint8 *u = ఖాళీ;
    స్థిరరాశి Uint8 *v = ఖాళీ;
    Uint32 y_stride = 0;
    Uint32 uv_stride = 0;
    YCbCrType yuv_type = YCBCR_601_LIMITED;

    ఒకవేళ (!GetYUVPlanes(వెడల్పు, ఎత్తు, src_format, src, src_pitch, &y, &u, &v, &y_stride, &uv_stride)) {
        తిరిగి false;
    }

    ఒకవేళ (!GetYUVConversionType(src_colorspace, వెడల్పు, ఎత్తు, 8, &yuv_type)) {
        తిరిగి false;
    }

    ఒకవేళ (yuv_rgb_sse(src_format, dst_format, వెడల్పు, ఎత్తు, y, u, v, y_stride, uv_stride, (Uint8 *)dst, dst_pitch, yuv_type)) {
        తిరిగి true;
    }

    ఒకవేళ (yuv_rgb_lsx(src_format, dst_format, వెడల్పు, ఎత్తు, y, u, v, y_stride, uv_stride, (Uint8 *)dst, dst_pitch, yuv_type)) {
        తిరిగి true;
    }

    ఒకవేళ (yuv_rgb_std(src_format, dst_format, వెడల్పు, ఎత్తు, y, u, v, y_stride, uv_stride, (Uint8 *)dst, dst_pitch, yuv_type)) {
        తిరిగి true;
    }

    // No fast path for the RGB format, instead convert using an intermediate buffer
    ఒకవేళ (src_format == SDL_PIXELFORMAT_P010 && dst_format != SDL_PIXELFORMAT_XBGR2101010) {
        bool ఫలితం;
        శూన్య *tmp;
        పూర్ణాంకం tmp_pitch = (వెడల్పు * పరిమాణం(Uint32));

        tmp = SDL_malloc((size_t)tmp_pitch * ఎత్తు);
        ఒకవేళ (!tmp) {
            తిరిగి false;
        }

        // convert src/src_format to tmp/XBGR2101010
        ఫలితం = SDL_Convert_Pixels_YUV_గమ్యం_RGB(వెడల్పు, ఎత్తు, src_format, src_colorspace, src_properties, src, src_pitch, SDL_PIXELFORMAT_XBGR2101010, src_colorspace, src_properties, tmp, tmp_pitch);
        ఒకవేళ (!ఫలితం) {
            SDL_free(tmp);
            తిరిగి false;
        }

        // convert tmp/XBGR2101010 to dst/RGB
        ఫలితం = SDL_ConvertPixelsAndColorspace(వెడల్పు, ఎత్తు, SDL_PIXELFORMAT_XBGR2101010, src_colorspace, src_properties, tmp, tmp_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
        SDL_free(tmp);
        తిరిగి ఫలితం;
    }

    ఒకవేళ ((src_format == SDL_PIXELFORMAT_I0FL || src_format == SDL_PIXELFORMAT_I4FL) && dst_format != SDL_PIXELFORMAT_RGB48) {
        bool ఫలితం;
        శూన్య *tmp;
        పూర్ణాంకం tmp_pitch = (వెడల్పు * 3 * పరిమాణం(Uint16));

        tmp = SDL_malloc((size_t)tmp_pitch * ఎత్తు);
        ఒకవేళ (!tmp) {
            తిరిగి false;
        }

        // convert src/src_format to tmp/RGB48
        ఫలితం = SDL_Convert_Pixels_YUV_గమ్యం_RGB(వెడల్పు, ఎత్తు, src_format, src_colorspace, src_properties, src, src_pitch, SDL_PIXELFORMAT_RGB48, src_colorspace, src_properties, tmp, tmp_pitch);
        ఒకవేళ (!ఫలితం) {
            SDL_free(tmp);
            తిరిగి false;
        }

        // convert tmp/RGB48 to dst/RGB
        ఫలితం = SDL_ConvertPixelsAndColorspace(వెడల్పు, ఎత్తు, SDL_PIXELFORMAT_RGB48, src_colorspace, src_properties, tmp, tmp_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
        SDL_free(tmp);
        తిరిగి ఫలితం;
    }

    ఒకవేళ (dst_format != SDL_PIXELFORMAT_ARGB8888) {
        bool ఫలితం;
        శూన్య *tmp;
        పూర్ణాంకం tmp_pitch = (వెడల్పు * పరిమాణం(Uint32));

        tmp = SDL_malloc((size_t)tmp_pitch * ఎత్తు);
        ఒకవేళ (!tmp) {
            తిరిగి false;
        }

        // convert src/src_format to tmp/ARGB8888
        ఫలితం = SDL_Convert_Pixels_YUV_గమ్యం_RGB(వెడల్పు, ఎత్తు, src_format, src_colorspace, src_properties, src, src_pitch, SDL_PIXELFORMAT_ARGB8888, SDL_COLORSPACE_SRGB, 0, tmp, tmp_pitch);
        ఒకవేళ (!ఫలితం) {
            SDL_free(tmp);
            తిరిగి false;
        }

        // convert tmp/ARGB8888 to dst/RGB
        ఫలితం = SDL_ConvertPixelsAndColorspace(వెడల్పు, ఎత్తు, SDL_PIXELFORMAT_ARGB8888, SDL_COLORSPACE_SRGB, 0, tmp, tmp_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
        SDL_free(tmp);
        తిరిగి ఫలితం;
    }

    తిరిగి SDL_సమితి_Error("Unsupported YUV conversion");
}

నిర్మాణం RGB2YUVFactors
{
    పూర్ణాంకం y_స్థానభ్రంశం;
    దశాంశం y[3]; // Rfactor, Gfactor, Bfactor
    దశాంశం u[3]; // Rfactor, Gfactor, Bfactor
    దశాంశం v[3]; // Rfactor, Gfactor, Bfactor
};

స్థిర నిర్మాణం RGB2YUVFactors RGB2YUVFactorTables[] = {
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

స్థిర bool SDL_Convert_Pixels_XRGB8888_గమ్యం_YUV(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, స్థిరరాశి శూన్య *src, పూర్ణాంకం src_pitch, SDL_PixelFormat dst_format, శూన్య *dst, పూర్ణాంకం dst_pitch, YCbCrType yuv_type)
{
    స్థిరరాశి పూర్ణాంకం src_pitch_x_2 = src_pitch * 2;
    స్థిరరాశి పూర్ణాంకం ఎత్తు_half = ఎత్తు / 2;
    స్థిరరాశి పూర్ణాంకం ఎత్తు_remainder = (ఎత్తు & 0x1);
    స్థిరరాశి పూర్ణాంకం వెడల్పు_half = వెడల్పు / 2;
    స్థిరరాశి పూర్ణాంకం వెడల్పు_remainder = (వెడల్పు & 0x1);
    పూర్ణాంకం i, j;

    స్థిరరాశి నిర్మాణం RGB2YUVFactors *cvt = &RGB2YUVFactorTables[yuv_type];

#నిర్వచించు MAKE_Y(r, g, b) (Uint8)SDL_clamp(((పూర్ణాంకం)(cvt->y[0] * (r) + cvt->y[1] * (g) + cvt->y[2] * (b) + 0.5f) + cvt->y_స్థానభ్రంశం), 0, 255)
#నిర్వచించు MAKE_U(r, g, b) (Uint8)SDL_clamp(((పూర్ణాంకం)(cvt->u[0] * (r) + cvt->u[1] * (g) + cvt->u[2] * (b) + 0.5f) + 128), 0, 255)
#నిర్వచించు MAKE_V(r, g, b) (Uint8)SDL_clamp(((పూర్ణాంకం)(cvt->v[0] * (r) + cvt->v[1] * (g) + cvt->v[2] * (b) + 0.5f) + 128), 0, 255)

#నిర్వచించు READ_2x2_PIXELS                                                                                     \
    స్థిరరాశి Uint32 p1 = ((స్థిరరాశి Uint32 *)curr_అడ్డువరుస)[2 * i];                                                    \
    స్థిరరాశి Uint32 p2 = ((స్థిరరాశి Uint32 *)curr_అడ్డువరుస)[2 * i + 1];                                                \
    స్థిరరాశి Uint32 p3 = ((స్థిరరాశి Uint32 *)తదుపరి_అడ్డువరుస)[2 * i];                                                    \
    స్థిరరాశి Uint32 p4 = ((స్థిరరాశి Uint32 *)తదుపరి_అడ్డువరుస)[2 * i + 1];                                                \
    స్థిరరాశి Uint32 r = ((p1 & 0x00ff0000) + (p2 & 0x00ff0000) + (p3 & 0x00ff0000) + (p4 & 0x00ff0000)) >> 18; \
    స్థిరరాశి Uint32 g = ((p1 & 0x0000ff00) + (p2 & 0x0000ff00) + (p3 & 0x0000ff00) + (p4 & 0x0000ff00)) >> 10; \
    స్థిరరాశి Uint32 b = ((p1 & 0x000000ff) + (p2 & 0x000000ff) + (p3 & 0x000000ff) + (p4 & 0x000000ff)) >> 2

#నిర్వచించు READ_2x1_PIXELS                                             \
    స్థిరరాశి Uint32 p1 = ((స్థిరరాశి Uint32 *)curr_అడ్డువరుస)[2 * i];            \
    స్థిరరాశి Uint32 p2 = ((స్థిరరాశి Uint32 *)తదుపరి_అడ్డువరుస)[2 * i];            \
    స్థిరరాశి Uint32 r = ((p1 & 0x00ff0000) + (p2 & 0x00ff0000)) >> 17; \
    స్థిరరాశి Uint32 g = ((p1 & 0x0000ff00) + (p2 & 0x0000ff00)) >> 9;  \
    స్థిరరాశి Uint32 b = ((p1 & 0x000000ff) + (p2 & 0x000000ff)) >> 1

#నిర్వచించు READ_1x2_PIXELS                                             \
    స్థిరరాశి Uint32 p1 = ((స్థిరరాశి Uint32 *)curr_అడ్డువరుస)[2 * i];            \
    స్థిరరాశి Uint32 p2 = ((స్థిరరాశి Uint32 *)curr_అడ్డువరుస)[2 * i + 1];        \
    స్థిరరాశి Uint32 r = ((p1 & 0x00ff0000) + (p2 & 0x00ff0000)) >> 17; \
    స్థిరరాశి Uint32 g = ((p1 & 0x0000ff00) + (p2 & 0x0000ff00)) >> 9;  \
    స్థిరరాశి Uint32 b = ((p1 & 0x000000ff) + (p2 & 0x000000ff)) >> 1

#నిర్వచించు READ_1x1_PIXEL                                  \
    స్థిరరాశి Uint32 p = ((స్థిరరాశి Uint32 *)curr_అడ్డువరుస)[2 * i]; \
    స్థిరరాశి Uint32 r = (p & 0x00ff0000) >> 16;            \
    స్థిరరాశి Uint32 g = (p & 0x0000ff00) >> 8;             \
    స్థిరరాశి Uint32 b = (p & 0x000000ff)

#నిర్వచించు READ_TWO_RGB_PIXELS                                  \
    స్థిరరాశి Uint32 p = ((స్థిరరాశి Uint32 *)curr_అడ్డువరుస)[2 * i];      \
    స్థిరరాశి Uint32 r = (p & 0x00ff0000) >> 16;                 \
    స్థిరరాశి Uint32 g = (p & 0x0000ff00) >> 8;                  \
    స్థిరరాశి Uint32 b = (p & 0x000000ff);                       \
    స్థిరరాశి Uint32 p1 = ((స్థిరరాశి Uint32 *)curr_అడ్డువరుస)[2 * i + 1]; \
    స్థిరరాశి Uint32 r1 = (p1 & 0x00ff0000) >> 16;               \
    స్థిరరాశి Uint32 g1 = (p1 & 0x0000ff00) >> 8;                \
    స్థిరరాశి Uint32 b1 = (p1 & 0x000000ff);                     \
    స్థిరరాశి Uint32 R = (r + r1) / 2;                           \
    స్థిరరాశి Uint32 G = (g + g1) / 2;                           \
    స్థిరరాశి Uint32 B = (b + b1) / 2

#నిర్వచించు READ_ONE_RGB_PIXEL READ_1x1_PIXEL

    ఎంపిక (dst_format) {
    స్థితి SDL_PIXELFORMAT_YV12:
    స్థితి SDL_PIXELFORMAT_IYUV:
    స్థితి SDL_PIXELFORMAT_I444:
    స్థితి SDL_PIXELFORMAT_NV12:
    స్థితి SDL_PIXELFORMAT_NV21:
    {
        స్థిరరాశి Uint8 *curr_అడ్డువరుస, *తదుపరి_అడ్డువరుస;

        Uint8 *plane_y;
        Uint8 *plane_u;
        Uint8 *plane_v;
        Uint8 *plane_interleaved_uv;
        Uint32 y_stride, uv_stride, y_skip, uv_skip;

        ఒకవేళ (!GetYUVPlanes(వెడల్పు, ఎత్తు, dst_format, dst, dst_pitch,
                          (స్థిరరాశి Uint8 **)&plane_y, (స్థిరరాశి Uint8 **)&plane_u, (స్థిరరాశి Uint8 **)&plane_v,
                          &y_stride, &uv_stride)) {
            తిరిగి false;
        }

        plane_interleaved_uv = (plane_y + ఎత్తు * y_stride);
        y_skip = (y_stride - వెడల్పు);

        curr_అడ్డువరుస = (స్థిరరాశి Uint8 *)src;

        // Write Y plane
        కొరకు (j = 0; j < ఎత్తు; j++) {
            కొరకు (i = 0; i < వెడల్పు; i++) {
                స్థిరరాశి Uint32 p1 = ((స్థిరరాశి Uint32 *)curr_అడ్డువరుస)[i];
                స్థిరరాశి Uint32 r = (p1 & 0x00ff0000) >> 16;
                స్థిరరాశి Uint32 g = (p1 & 0x0000ff00) >> 8;
                స్థిరరాశి Uint32 b = (p1 & 0x000000ff);
                *plane_y++ = MAKE_Y(r, g, b);
            }
            plane_y += y_skip;
            curr_అడ్డువరుస += src_pitch;
        }

        curr_అడ్డువరుస = (స్థిరరాశి Uint8 *)src;
        తదుపరి_అడ్డువరుస = (స్థిరరాశి Uint8 *)src;
        తదుపరి_అడ్డువరుస += src_pitch;

        ఒకవేళ (dst_format == SDL_PIXELFORMAT_YV12 || dst_format == SDL_PIXELFORMAT_IYUV) {
            // Write UV planes, not interleaved
            uv_skip = (uv_stride - (వెడల్పు + 1) / 2);
            కొరకు (j = 0; j < ఎత్తు_half; j++) {
                కొరకు (i = 0; i < వెడల్పు_half; i++) {
                    READ_2x2_PIXELS;
                    *plane_u++ = MAKE_U(r, g, b);
                    *plane_v++ = MAKE_V(r, g, b);
                }
                ఒకవేళ (వెడల్పు_remainder) {
                    READ_2x1_PIXELS;
                    *plane_u++ = MAKE_U(r, g, b);
                    *plane_v++ = MAKE_V(r, g, b);
                }
                plane_u += uv_skip;
                plane_v += uv_skip;
                curr_అడ్డువరుస += src_pitch_x_2;
                తదుపరి_అడ్డువరుస += src_pitch_x_2;
            }
            ఒకవేళ (ఎత్తు_remainder) {
                కొరకు (i = 0; i < వెడల్పు_half; i++) {
                    READ_1x2_PIXELS;
                    *plane_u++ = MAKE_U(r, g, b);
                    *plane_v++ = MAKE_V(r, g, b);
                }
                ఒకవేళ (వెడల్పు_remainder) {
                    READ_1x1_PIXEL;
                    *plane_u++ = MAKE_U(r, g, b);
                    *plane_v++ = MAKE_V(r, g, b);
                }
                plane_u += uv_skip;
                plane_v += uv_skip;
            }
        } లేకపోతే ఒకవేళ (dst_format == SDL_PIXELFORMAT_I444) {
            // Write UV planes, not interleaved
            uv_skip = (uv_stride - వెడల్పు);
            కొరకు (j = 0; j < ఎత్తు; j++) {
                కొరకు (i = 0; i < వెడల్పు; i++) {
                    స్థిరరాశి Uint32 p1 = ((స్థిరరాశి Uint32 *)curr_అడ్డువరుస)[i];
                    స్థిరరాశి Uint32 r = (p1 & 0x00ff0000) >> 16;
                    స్థిరరాశి Uint32 g = (p1 & 0x0000ff00) >> 8;
                    స్థిరరాశి Uint32 b = (p1 & 0x000000ff);
                    *plane_u++ = MAKE_U(r, g, b);
                    *plane_v++ = MAKE_V(r, g, b);
                }
                plane_u += uv_skip;
                plane_v += uv_skip;
                curr_అడ్డువరుస += src_pitch;
            }
        } లేకపోతే ఒకవేళ (dst_format == SDL_PIXELFORMAT_NV12) {
            uv_skip = (uv_stride - ((వెడల్పు + 1) / 2) * 2);
            కొరకు (j = 0; j < ఎత్తు_half; j++) {
                కొరకు (i = 0; i < వెడల్పు_half; i++) {
                    READ_2x2_PIXELS;
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                }
                ఒకవేళ (వెడల్పు_remainder) {
                    READ_2x1_PIXELS;
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                }
                plane_interleaved_uv += uv_skip;
                curr_అడ్డువరుస += src_pitch_x_2;
                తదుపరి_అడ్డువరుస += src_pitch_x_2;
            }
            ఒకవేళ (ఎత్తు_remainder) {
                కొరకు (i = 0; i < వెడల్పు_half; i++) {
                    READ_1x2_PIXELS;
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                }
                ఒకవేళ (వెడల్పు_remainder) {
                    READ_1x1_PIXEL;
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                }
            }
        } లేకపోతే /* dst_format == SDL_PIXELFORMAT_NV21 */ {
            uv_skip = (uv_stride - ((వెడల్పు + 1) / 2) * 2);
            కొరకు (j = 0; j < ఎత్తు_half; j++) {
                కొరకు (i = 0; i < వెడల్పు_half; i++) {
                    READ_2x2_PIXELS;
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                }
                ఒకవేళ (వెడల్పు_remainder) {
                    READ_2x1_PIXELS;
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                }
                plane_interleaved_uv += uv_skip;
                curr_అడ్డువరుస += src_pitch_x_2;
                తదుపరి_అడ్డువరుస += src_pitch_x_2;
            }
            ఒకవేళ (ఎత్తు_remainder) {
                కొరకు (i = 0; i < వెడల్పు_half; i++) {
                    READ_1x2_PIXELS;
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                }
                ఒకవేళ (వెడల్పు_remainder) {
                    READ_1x1_PIXEL;
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                }
            }
        }
    } ఆపు;

    స్థితి SDL_PIXELFORMAT_YUY2:
    స్థితి SDL_PIXELFORMAT_UYVY:
    స్థితి SDL_PIXELFORMAT_YVYU:
    {
        స్థిరరాశి Uint8 *curr_అడ్డువరుస = (స్థిరరాశి Uint8 *)src;
        Uint8 *plane = (Uint8 *)dst;
        స్థిరరాశి పూర్ణాంకం అడ్డువరుస_కొలత = (4 * ((వెడల్పు + 1) / 2));
        పూర్ణాంకం plane_skip;

        ఒకవేళ (dst_pitch < అడ్డువరుస_కొలత) {
            తిరిగి SDL_సమితి_Error("Destination pitch is too small, expected at least %d", అడ్డువరుస_కొలత);
        }
        plane_skip = (dst_pitch - అడ్డువరుస_కొలత);

        // Write YUV plane, packed
        ఒకవేళ (dst_format == SDL_PIXELFORMAT_YUY2) {
            కొరకు (j = 0; j < ఎత్తు; j++) {
                కొరకు (i = 0; i < వెడల్పు_half; i++) {
                    READ_TWO_RGB_PIXELS;
                    // Y U Y1 V
                    *plane++ = MAKE_Y(r, g, b);
                    *plane++ = MAKE_U(R, G, B);
                    *plane++ = MAKE_Y(r1, g1, b1);
                    *plane++ = MAKE_V(R, G, B);
                }
                ఒకవేళ (వెడల్పు_remainder) {
                    READ_ONE_RGB_PIXEL;
                    // Y U Y V
                    *plane++ = MAKE_Y(r, g, b);
                    *plane++ = MAKE_U(r, g, b);
                    *plane++ = MAKE_Y(r, g, b);
                    *plane++ = MAKE_V(r, g, b);
                }
                plane += plane_skip;
                curr_అడ్డువరుస += src_pitch;
            }
        } లేకపోతే ఒకవేళ (dst_format == SDL_PIXELFORMAT_UYVY) {
            కొరకు (j = 0; j < ఎత్తు; j++) {
                కొరకు (i = 0; i < వెడల్పు_half; i++) {
                    READ_TWO_RGB_PIXELS;
                    // U Y V Y1
                    *plane++ = MAKE_U(R, G, B);
                    *plane++ = MAKE_Y(r, g, b);
                    *plane++ = MAKE_V(R, G, B);
                    *plane++ = MAKE_Y(r1, g1, b1);
                }
                ఒకవేళ (వెడల్పు_remainder) {
                    READ_ONE_RGB_PIXEL;
                    // U Y V Y
                    *plane++ = MAKE_U(r, g, b);
                    *plane++ = MAKE_Y(r, g, b);
                    *plane++ = MAKE_V(r, g, b);
                    *plane++ = MAKE_Y(r, g, b);
                }
                plane += plane_skip;
                curr_అడ్డువరుస += src_pitch;
            }
        } లేకపోతే ఒకవేళ (dst_format == SDL_PIXELFORMAT_YVYU) {
            కొరకు (j = 0; j < ఎత్తు; j++) {
                కొరకు (i = 0; i < వెడల్పు_half; i++) {
                    READ_TWO_RGB_PIXELS;
                    // Y V Y1 U
                    *plane++ = MAKE_Y(r, g, b);
                    *plane++ = MAKE_V(R, G, B);
                    *plane++ = MAKE_Y(r1, g1, b1);
                    *plane++ = MAKE_U(R, G, B);
                }
                ఒకవేళ (వెడల్పు_remainder) {
                    READ_ONE_RGB_PIXEL;
                    // Y V Y U
                    *plane++ = MAKE_Y(r, g, b);
                    *plane++ = MAKE_V(r, g, b);
                    *plane++ = MAKE_Y(r, g, b);
                    *plane++ = MAKE_U(r, g, b);
                }
                plane += plane_skip;
                curr_అడ్డువరుస += src_pitch;
            }
        }
    } ఆపు;

    అప్రమేయ:
        తిరిగి SDL_సమితి_Error("Unsupported YUV destination format: %s", SDL_GetPixelFormatName(dst_format));
    }
#నిర్వచనం_రద్దు MAKE_Y
#నిర్వచనం_రద్దు MAKE_U
#నిర్వచనం_రద్దు MAKE_V
#నిర్వచనం_రద్దు READ_2x2_PIXELS
#నిర్వచనం_రద్దు READ_2x1_PIXELS
#నిర్వచనం_రద్దు READ_1x2_PIXELS
#నిర్వచనం_రద్దు READ_1x1_PIXEL
#నిర్వచనం_రద్దు READ_TWO_RGB_PIXELS
#నిర్వచనం_రద్దు READ_ONE_RGB_PIXEL
    తిరిగి true;
}

స్థిర bool SDL_Convert_Pixels_XBGR2101010_గమ్యం_P010(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, స్థిరరాశి శూన్య *src, పూర్ణాంకం src_pitch, SDL_PixelFormat dst_format, శూన్య *dst, పూర్ణాంకం dst_pitch, YCbCrType yuv_type)
{
    స్థిరరాశి పూర్ణాంకం src_pitch_x_2 = src_pitch * 2;
    స్థిరరాశి పూర్ణాంకం ఎత్తు_half = ఎత్తు / 2;
    స్థిరరాశి పూర్ణాంకం ఎత్తు_remainder = (ఎత్తు & 0x1);
    స్థిరరాశి పూర్ణాంకం వెడల్పు_half = వెడల్పు / 2;
    స్థిరరాశి పూర్ణాంకం వెడల్పు_remainder = (వెడల్పు & 0x1);
    పూర్ణాంకం i, j;

    స్థిరరాశి నిర్మాణం RGB2YUVFactors *cvt = &RGB2YUVFactorTables[yuv_type];

#నిర్వచించు MAKE_Y(r, g, b) (Uint16)(((పూర్ణాంకం)(cvt->y[0] * (r) + cvt->y[1] * (g) + cvt->y[2] * (b) + 0.5f) + cvt->y_స్థానభ్రంశం) << 6)
#నిర్వచించు MAKE_U(r, g, b) (Uint16)(((పూర్ణాంకం)(cvt->u[0] * (r) + cvt->u[1] * (g) + cvt->u[2] * (b) + 0.5f) + 512) << 6)
#నిర్వచించు MAKE_V(r, g, b) (Uint16)(((పూర్ణాంకం)(cvt->v[0] * (r) + cvt->v[1] * (g) + cvt->v[2] * (b) + 0.5f) + 512) << 6)

#నిర్వచించు READ_2x2_PIXELS                                                                                     \
    స్థిరరాశి Uint32 p1 = ((స్థిరరాశి Uint32 *)curr_అడ్డువరుస)[2 * i];                                                    \
    స్థిరరాశి Uint32 p2 = ((స్థిరరాశి Uint32 *)curr_అడ్డువరుస)[2 * i + 1];                                                \
    స్థిరరాశి Uint32 p3 = ((స్థిరరాశి Uint32 *)తదుపరి_అడ్డువరుస)[2 * i];                                                    \
    స్థిరరాశి Uint32 p4 = ((స్థిరరాశి Uint32 *)తదుపరి_అడ్డువరుస)[2 * i + 1];                                                \
    స్థిరరాశి Uint32 r = ((p1 & 0x000003ff) + (p2 & 0x000003ff) + (p3 & 0x000003ff) + (p4 & 0x000003ff)) >> 2;  \
    స్థిరరాశి Uint32 g = ((p1 & 0x000ffc00) + (p2 & 0x000ffc00) + (p3 & 0x000ffc00) + (p4 & 0x000ffc00)) >> 12; \
    స్థిరరాశి Uint32 b = ((p1 & 0x3ff00000) + (p2 & 0x3ff00000) + (p3 & 0x3ff00000) + (p4 & 0x3ff00000)) >> 22

#నిర్వచించు READ_2x1_PIXELS                                             \
    స్థిరరాశి Uint32 p1 = ((స్థిరరాశి Uint32 *)curr_అడ్డువరుస)[2 * i];            \
    స్థిరరాశి Uint32 p2 = ((స్థిరరాశి Uint32 *)తదుపరి_అడ్డువరుస)[2 * i];            \
    స్థిరరాశి Uint32 r = ((p1 & 0x000003ff) + (p2 & 0x000003ff)) >> 1;  \
    స్థిరరాశి Uint32 g = ((p1 & 0x000ffc00) + (p2 & 0x000ffc00)) >> 11; \
    స్థిరరాశి Uint32 b = ((p1 & 0x3ff00000) + (p2 & 0x3ff00000)) >> 21

#నిర్వచించు READ_1x2_PIXELS                                             \
    స్థిరరాశి Uint32 p1 = ((స్థిరరాశి Uint32 *)curr_అడ్డువరుస)[2 * i];            \
    స్థిరరాశి Uint32 p2 = ((స్థిరరాశి Uint32 *)curr_అడ్డువరుస)[2 * i + 1];        \
    స్థిరరాశి Uint32 r = ((p1 & 0x000003ff) + (p2 & 0x000003ff)) >> 1;  \
    స్థిరరాశి Uint32 g = ((p1 & 0x000ffc00) + (p2 & 0x000ffc00)) >> 11; \
    స్థిరరాశి Uint32 b = ((p1 & 0x3ff00000) + (p2 & 0x3ff00000)) >> 21

#నిర్వచించు READ_1x1_PIXEL                                  \
    స్థిరరాశి Uint32 p = ((స్థిరరాశి Uint32 *)curr_అడ్డువరుస)[2 * i]; \
    స్థిరరాశి Uint32 r = (p & 0x000003ff);                  \
    స్థిరరాశి Uint32 g = (p & 0x000ffc00) >> 10;            \
    స్థిరరాశి Uint32 b = (p & 0x3ff00000) >> 20

    స్థిరరాశి Uint8 *curr_అడ్డువరుస, *తదుపరి_అడ్డువరుస;

    Uint16 *plane_y;
    Uint16 *plane_u;
    Uint16 *plane_v;
    Uint16 *plane_interleaved_uv;
    Uint32 y_stride, uv_stride, y_skip, uv_skip;

    ఒకవేళ (!GetYUVPlanes(వెడల్పు, ఎత్తు, dst_format, dst, dst_pitch,
                      (స్థిరరాశి Uint8 **)&plane_y, (స్థిరరాశి Uint8 **)&plane_u, (స్థిరరాశి Uint8 **)&plane_v,
                      &y_stride, &uv_stride)) {
        తిరిగి false;
    }

    y_stride /= పరిమాణం(Uint16);
    uv_stride /= పరిమాణం(Uint16);

    plane_interleaved_uv = (plane_y + ఎత్తు * y_stride);
    y_skip = (y_stride - వెడల్పు);

    curr_అడ్డువరుస = (స్థిరరాశి Uint8 *)src;

    // Write Y plane
    కొరకు (j = 0; j < ఎత్తు; j++) {
        కొరకు (i = 0; i < వెడల్పు; i++) {
            స్థిరరాశి Uint32 p1 = ((స్థిరరాశి Uint32 *)curr_అడ్డువరుస)[i];
            స్థిరరాశి Uint32 r = (p1 >>  0) & 0x03ff;
            స్థిరరాశి Uint32 g = (p1 >> 10) & 0x03ff;
            స్థిరరాశి Uint32 b = (p1 >> 20) & 0x03ff;
            *plane_y++ = MAKE_Y(r, g, b);
        }
        plane_y += y_skip;
        curr_అడ్డువరుస += src_pitch;
    }

    curr_అడ్డువరుస = (స్థిరరాశి Uint8 *)src;
    తదుపరి_అడ్డువరుస = (స్థిరరాశి Uint8 *)src;
    తదుపరి_అడ్డువరుస += src_pitch;

    uv_skip = (uv_stride - ((వెడల్పు + 1) / 2) * 2);
    కొరకు (j = 0; j < ఎత్తు_half; j++) {
        కొరకు (i = 0; i < వెడల్పు_half; i++) {
            READ_2x2_PIXELS;
            *plane_interleaved_uv++ = MAKE_U(r, g, b);
            *plane_interleaved_uv++ = MAKE_V(r, g, b);
        }
        ఒకవేళ (వెడల్పు_remainder) {
            READ_2x1_PIXELS;
            *plane_interleaved_uv++ = MAKE_U(r, g, b);
            *plane_interleaved_uv++ = MAKE_V(r, g, b);
        }
        plane_interleaved_uv += uv_skip;
        curr_అడ్డువరుస += src_pitch_x_2;
        తదుపరి_అడ్డువరుస += src_pitch_x_2;
    }
    ఒకవేళ (ఎత్తు_remainder) {
        కొరకు (i = 0; i < వెడల్పు_half; i++) {
            READ_1x2_PIXELS;
            *plane_interleaved_uv++ = MAKE_U(r, g, b);
            *plane_interleaved_uv++ = MAKE_V(r, g, b);
        }
        ఒకవేళ (వెడల్పు_remainder) {
            READ_1x1_PIXEL;
            *plane_interleaved_uv++ = MAKE_U(r, g, b);
            *plane_interleaved_uv++ = MAKE_V(r, g, b);
        }
    }

#నిర్వచనం_రద్దు MAKE_Y
#నిర్వచనం_రద్దు MAKE_U
#నిర్వచనం_రద్దు MAKE_V
#నిర్వచనం_రద్దు READ_2x2_PIXELS
#నిర్వచనం_రద్దు READ_2x1_PIXELS
#నిర్వచనం_రద్దు READ_1x2_PIXELS
#నిర్వచనం_రద్దు READ_1x1_PIXEL
    తిరిగి true;
}

bool SDL_Convert_Pixels_RGB_గమ్యం_YUV(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు,
                                  SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, స్థిరరాశి శూన్య *src, పూర్ణాంకం src_pitch,
                                  SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, శూన్య *dst, పూర్ణాంకం dst_pitch)
{
    YCbCrType yuv_type = YCBCR_601_LIMITED;

    ఒకవేళ (!GetYUVConversionType(dst_colorspace, వెడల్పు, ఎత్తు, 8, &yuv_type)) {
        తిరిగి false;
    }

#ఒకవేళ 0 // Doesn't handle odd widths
    // RGB24 to FOURCC
    ఒకవేళ (src_format == SDL_PIXELFORMAT_RGB24) {
        Uint8 *y;
        Uint8 *u;
        Uint8 *v;
        Uint32 y_stride;
        Uint32 uv_stride;

        ఒకవేళ (GetYUVPlanes(వెడల్పు, ఎత్తు, dst_format, dst, dst_pitch, (స్థిరరాశి Uint8 **)&y, (స్థిరరాశి Uint8 **)&u, (స్థిరరాశి Uint8 **)&v, &y_stride, &uv_stride) < 0) {
            తిరిగి false;
        }

        rgb24_yuv420_std(వెడల్పు, ఎత్తు, src, src_pitch, y, u, v, y_stride, uv_stride, yuv_type);
        తిరిగి true;
    }
#అయితే_ముగింపు

    // ARGB8888 to FOURCC
    ఒకవేళ (src_format == SDL_PIXELFORMAT_ARGB8888 || src_format == SDL_PIXELFORMAT_XRGB8888) {
        తిరిగి SDL_Convert_Pixels_XRGB8888_గమ్యం_YUV(వెడల్పు, ఎత్తు, src, src_pitch, dst_format, dst, dst_pitch, yuv_type);
    }

    ఒకవేళ (dst_format == SDL_PIXELFORMAT_P010) {
        ఒకవేళ (src_format == SDL_PIXELFORMAT_XBGR2101010) {
            తిరిగి SDL_Convert_Pixels_XBGR2101010_గమ్యం_P010(వెడల్పు, ఎత్తు, src, src_pitch, dst_format, dst, dst_pitch, yuv_type);
        }

        // We currently only support converting from XBGR2101010 to P010
        bool ఫలితం;
        శూన్య *tmp;
        పూర్ణాంకం tmp_pitch = (వెడల్పు * పరిమాణం(Uint32));

        tmp = SDL_malloc((size_t)tmp_pitch * ఎత్తు);
        ఒకవేళ (!tmp) {
            తిరిగి false;
        }

        // convert src/src_format to tmp/XBGR2101010
        ఫలితం = SDL_ConvertPixelsAndColorspace(వెడల్పు, ఎత్తు, src_format, src_colorspace, src_properties, src, src_pitch, SDL_PIXELFORMAT_XBGR2101010, dst_colorspace, dst_properties, tmp, tmp_pitch);
        ఒకవేళ (!ఫలితం) {
            SDL_free(tmp);
            తిరిగి false;
        }

        // convert tmp/XBGR2101010 to dst/P010
        ఫలితం = SDL_Convert_Pixels_XBGR2101010_గమ్యం_P010(వెడల్పు, ఎత్తు, tmp, tmp_pitch, dst_format, dst, dst_pitch, yuv_type);
        SDL_free(tmp);
        తిరిగి ఫలితం;
    }

    // not ARGB8888 to FOURCC : need an intermediate conversion
    {
        bool ఫలితం;
        శూన్య *tmp;
        పూర్ణాంకం tmp_pitch = (వెడల్పు * పరిమాణం(Uint32));

        tmp = SDL_malloc((size_t)tmp_pitch * ఎత్తు);
        ఒకవేళ (!tmp) {
            తిరిగి false;
        }

        // convert src/src_format to tmp/XRGB8888
        ఫలితం = SDL_ConvertPixelsAndColorspace(వెడల్పు, ఎత్తు, src_format, src_colorspace, src_properties, src, src_pitch, SDL_PIXELFORMAT_XRGB8888, SDL_COLORSPACE_SRGB, 0, tmp, tmp_pitch);
        ఒకవేళ (!ఫలితం) {
            SDL_free(tmp);
            తిరిగి false;
        }

        // convert tmp/XRGB8888 to dst/FOURCC
        ఫలితం = SDL_Convert_Pixels_XRGB8888_గమ్యం_YUV(వెడల్పు, ఎత్తు, tmp, tmp_pitch, dst_format, dst, dst_pitch, yuv_type);
        SDL_free(tmp);
        తిరిగి ఫలితం;
    }
}

స్థిర bool SDL_Convert_Pixels_YUV_గమ్యం_YUV_Copy(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, SDL_PixelFormat format, స్థిరరాశి శూన్య *src, పూర్ణాంకం src_pitch, శూన్య *dst, పూర్ణాంకం dst_pitch)
{
    పూర్ణాంకం i;

    ఒకవేళ (IsPlanar1x1Format(format)) {
        // YUV planes
        స్థిరరాశి size_t నిడివి = వెడల్పు * SDL_BYTESPERPIXEL(format);
        కొరకు (i = ఎత్తు * 3; i--;) {
            SDL_memcpy(dst, src, నిడివి);
            src = (స్థిరరాశి Uint8 *)src + src_pitch;
            dst = (Uint8 *)dst + dst_pitch;
        }
        తిరిగి true;
    }

    ఒకవేళ (IsPlanar2x2Format(format)) {
        స్థిరరాశి పూర్ణాంకం bpp = SDL_BYTESPERPIXEL(format);

        // Y plane
        స్థిరరాశి size_t నిడివి = వెడల్పు * bpp;
        కొరకు (i = ఎత్తు; i--;) {
            SDL_memcpy(dst, src, నిడివి);
            src = (స్థిరరాశి Uint8 *)src + src_pitch;
            dst = (Uint8 *)dst + dst_pitch;
        }

        ఒకవేళ (format == SDL_PIXELFORMAT_YV12 ||
            format == SDL_PIXELFORMAT_IYUV ||
            format == SDL_PIXELFORMAT_I0FL) {
            // U and V planes are a quarter the size of the Y plane, rounded up
            వెడల్పు = ((వెడల్పు + 1) / 2) * bpp;
            ఎత్తు = (ఎత్తు + 1) / 2;
            src_pitch = ((src_pitch / bpp + 1) / 2) * bpp;
            dst_pitch = ((dst_pitch / bpp + 1) / 2) * bpp;
            కొరకు (i = ఎత్తు * 2; i--;) {
                SDL_memcpy(dst, src, వెడల్పు);
                src = (స్థిరరాశి Uint8 *)src + src_pitch;
                dst = (Uint8 *)dst + dst_pitch;
            }
        } లేకపోతే ఒకవేళ (format == SDL_PIXELFORMAT_NV12 ||
                   format == SDL_PIXELFORMAT_NV21 ||
                   format == SDL_PIXELFORMAT_P010) {
            // U/V plane is half the height of the Y plane, rounded up, with packed CrCb
            వెడల్పు = ((వెడల్పు + 1) / 2) * 2 * bpp;
            ఎత్తు = (ఎత్తు + 1) / 2;
            src_pitch = ((src_pitch / bpp + 1) / 2) * 2 * bpp;
            dst_pitch = ((dst_pitch / bpp + 1) / 2) * 2 * bpp;
            కొరకు (i = ఎత్తు; i--;) {
                SDL_memcpy(dst, src, వెడల్పు);
                src = (స్థిరరాశి Uint8 *)src + src_pitch;
                dst = (Uint8 *)dst + dst_pitch;
            }
        }
        తిరిగి true;
    }

    ఒకవేళ (IsPacked4Format(format)) {
        // Packed planes
        వెడల్పు = 4 * ((వెడల్పు + 1) / 2);
        కొరకు (i = ఎత్తు; i--;) {
            SDL_memcpy(dst, src, వెడల్పు);
            src = (స్థిరరాశి Uint8 *)src + src_pitch;
            dst = (Uint8 *)dst + dst_pitch;
        }
        తిరిగి true;
    }

    తిరిగి SDL_సమితి_Error("SDL_ConvertPixels_YUV_to_YUV_Copy: Unsupported YUV format: %s", SDL_GetPixelFormatName(format));
}

స్థిర bool SDL_Convert_Pixels_మార్పిడి_UVPlanes(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, స్థిరరాశి శూన్య *src, పూర్ణాంకం src_pitch, శూన్య *dst, పూర్ణాంకం dst_pitch)
{
    పూర్ణాంకం y;
    స్థిరరాశి పూర్ణాంకం UVwidth = (వెడల్పు + 1) / 2;
    స్థిరరాశి పూర్ణాంకం UVheight = (ఎత్తు + 1) / 2;

    // Skip the Y plane
    src = (స్థిరరాశి Uint8 *)src + ఎత్తు * src_pitch;
    dst = (Uint8 *)dst + ఎత్తు * dst_pitch;

    ఒకవేళ (src == dst) {
        పూర్ణాంకం UVpitch = (dst_pitch + 1) / 2;
        Uint8 *tmp;
        Uint8 *row1 = (Uint8 *)dst;
        Uint8 *row2 = row1 + UVheight * UVpitch;

        // Allocate a temporary row for the swap
        tmp = (Uint8 *)SDL_malloc(UVwidth);
        ఒకవేళ (!tmp) {
            తిరిగి false;
        }
        కొరకు (y = 0; y < UVheight; ++y) {
            SDL_memcpy(tmp, row1, UVwidth);
            SDL_memcpy(row1, row2, UVwidth);
            SDL_memcpy(row2, tmp, UVwidth);
            row1 += UVpitch;
            row2 += UVpitch;
        }
        SDL_free(tmp);
    } లేకపోతే {
        స్థిరరాశి Uint8 *srcUV;
        Uint8 *dstUV;
        పూర్ణాంకం srcUVPitch = ((src_pitch + 1) / 2);
        పూర్ణాంకం dstUVPitch = ((dst_pitch + 1) / 2);

        // Copy the first plane
        srcUV = (స్థిరరాశి Uint8 *)src;
        dstUV = (Uint8 *)dst + UVheight * dstUVPitch;
        కొరకు (y = 0; y < UVheight; ++y) {
            SDL_memcpy(dstUV, srcUV, UVwidth);
            srcUV += srcUVPitch;
            dstUV += dstUVPitch;
        }

        // Copy the second plane
        dstUV = (Uint8 *)dst;
        కొరకు (y = 0; y < UVheight; ++y) {
            SDL_memcpy(dstUV, srcUV, UVwidth);
            srcUV += srcUVPitch;
            dstUV += dstUVPitch;
        }
    }
    తిరిగి true;
}

#నిర్వచితమైతే SDL_SSE2_INTRINSICS
స్థిర bool SDL_TARGETING("sse2") SDL_Convert_Pixels_Pack_UVPlanes_గమ్యం_NV_SSE2(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, స్థిరరాశి శూన్య *src, పూర్ణాంకం src_pitch, శూన్య *dst, పూర్ణాంకం dst_pitch, bool తిరగేయి_UV)
{
    పూర్ణాంకం x, y;
    స్థిరరాశి పూర్ణాంకం UVwidth = (వెడల్పు + 1) / 2;
    స్థిరరాశి పూర్ణాంకం UVheight = (ఎత్తు + 1) / 2;
    స్థిరరాశి పూర్ణాంకం srcUVPitch = ((src_pitch + 1) / 2);
    స్థిరరాశి పూర్ణాంకం src_UVPitch_ఎడమ = srcUVPitch - UVwidth;
    స్థిరరాశి పూర్ణాంకం dstUVPitch = ((dst_pitch + 1) / 2) * 2;
    స్థిరరాశి పూర్ణాంకం dst_UVPitch_ఎడమ = dstUVPitch - UVwidth * 2;
    స్థిరరాశి Uint8 *src1, *src2;
    Uint8 *dstUV;
    Uint8 *tmp = ఖాళీ;

    // Skip the Y plane
    src = (స్థిరరాశి Uint8 *)src + ఎత్తు * src_pitch;
    dst = (Uint8 *)dst + ఎత్తు * dst_pitch;

    ఒకవేళ (src == dst) {
        // Need to make a copy of the buffer so we don't clobber it while converting
        tmp = (Uint8 *)SDL_malloc((size_t)2 * UVheight * srcUVPitch);
        ఒకవేళ (tmp == ఖాళీ) {
            తిరిగి false;
        }
        SDL_memcpy(tmp, src, (size_t)2 * UVheight * srcUVPitch);
        src = tmp;
    }

    ఒకవేళ (తిరగేయి_UV) {
        src2 = (స్థిరరాశి Uint8 *)src;
        src1 = src2 + UVheight * srcUVPitch;
    } లేకపోతే {
        src1 = (స్థిరరాశి Uint8 *)src;
        src2 = src1 + UVheight * srcUVPitch;
    }
    dstUV = (Uint8 *)dst;

    y = UVheight;
    అయితే (y--) {
        x = UVwidth;
        అయితే (x >= 16) {
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
        అయితే (x--) {
            *dstUV++ = *src1++;
            *dstUV++ = *src2++;
        }
        src1 += src_UVPitch_ఎడమ;
        src2 += src_UVPitch_ఎడమ;
        dstUV += dst_UVPitch_ఎడమ;
    }

    ఒకవేళ (tmp) {
        SDL_free(tmp);
    }
    తిరిగి true;
}

స్థిర bool SDL_TARGETING("sse2") SDL_Convert_Pixels_విభజించు_NV_గమ్యం_UVPlanes_SSE2(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, స్థిరరాశి శూన్య *src, పూర్ణాంకం src_pitch, శూన్య *dst, పూర్ణాంకం dst_pitch, bool తిరగేయి_UV)
{
    పూర్ణాంకం x, y;
    స్థిరరాశి పూర్ణాంకం UVwidth = (వెడల్పు + 1) / 2;
    స్థిరరాశి పూర్ణాంకం UVheight = (ఎత్తు + 1) / 2;
    స్థిరరాశి పూర్ణాంకం srcUVPitch = ((src_pitch + 1) / 2) * 2;
    స్థిరరాశి పూర్ణాంకం src_UVPitch_ఎడమ = srcUVPitch - UVwidth * 2;
    స్థిరరాశి పూర్ణాంకం dstUVPitch = ((dst_pitch + 1) / 2);
    స్థిరరాశి పూర్ణాంకం dst_UVPitch_ఎడమ = dstUVPitch - UVwidth;
    స్థిరరాశి Uint8 *srcUV;
    Uint8 *dst1, *dst2;
    Uint8 *tmp = ఖాళీ;

    // Skip the Y plane
    src = (స్థిరరాశి Uint8 *)src + ఎత్తు * src_pitch;
    dst = (Uint8 *)dst + ఎత్తు * dst_pitch;

    ఒకవేళ (src == dst) {
        // Need to make a copy of the buffer so we don't clobber it while converting
        tmp = (Uint8 *)SDL_malloc((size_t)UVheight * srcUVPitch);
        ఒకవేళ (tmp == ఖాళీ) {
            తిరిగి false;
        }
        SDL_memcpy(tmp, src, (size_t)UVheight * srcUVPitch);
        src = tmp;
    }

    ఒకవేళ (తిరగేయి_UV) {
        dst2 = (Uint8 *)dst;
        dst1 = dst2 + UVheight * dstUVPitch;
    } లేకపోతే {
        dst1 = (Uint8 *)dst;
        dst2 = dst1 + UVheight * dstUVPitch;
    }
    srcUV = (స్థిరరాశి Uint8 *)src;

    y = UVheight;
    అయితే (y--) {
        __m128i ముసుగు = _mm_set1_epi16(0x00FF);
        x = UVwidth;
        అయితే (x >= 16) {
            __m128i uv1 = _mm_loadu_si128((__m128i *)srcUV);
            __m128i uv2 = _mm_loadu_si128((__m128i *)(srcUV + 16));
            __m128i u1 = _mm_and_si128(uv1, ముసుగు);
            __m128i u2 = _mm_and_si128(uv2, ముసుగు);
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
        అయితే (x--) {
            *dst1++ = *srcUV++;
            *dst2++ = *srcUV++;
        }
        srcUV += src_UVPitch_ఎడమ;
        dst1 += dst_UVPitch_ఎడమ;
        dst2 += dst_UVPitch_ఎడమ;
    }

    ఒకవేళ (tmp) {
        SDL_free(tmp);
    }
    తిరిగి true;
}

స్థిర bool SDL_TARGETING("sse2") SDL_Convert_Pixels_మార్పిడి_NV_SSE2(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, స్థిరరాశి శూన్య *src, పూర్ణాంకం src_pitch, శూన్య *dst, పూర్ణాంకం dst_pitch)
{
    పూర్ణాంకం x, y;
    స్థిరరాశి పూర్ణాంకం UVwidth = (వెడల్పు + 1) / 2;
    స్థిరరాశి పూర్ణాంకం UVheight = (ఎత్తు + 1) / 2;
    స్థిరరాశి పూర్ణాంకం srcUVPitch = ((src_pitch + 1) / 2) * 2;
    స్థిరరాశి పూర్ణాంకం src_UVPitch_ఎడమ = (srcUVPitch - UVwidth * 2) / పరిమాణం(Uint16);
    స్థిరరాశి పూర్ణాంకం dstUVPitch = ((dst_pitch + 1) / 2) * 2;
    స్థిరరాశి పూర్ణాంకం dst_UVPitch_ఎడమ = (dstUVPitch - UVwidth * 2) / పరిమాణం(Uint16);
    స్థిరరాశి Uint16 *srcUV;
    Uint16 *dstUV;

    // Skip the Y plane
    src = (స్థిరరాశి Uint8 *)src + ఎత్తు * src_pitch;
    dst = (Uint8 *)dst + ఎత్తు * dst_pitch;

    srcUV = (స్థిరరాశి Uint16 *)src;
    dstUV = (Uint16 *)dst;
    y = UVheight;
    అయితే (y--) {
        x = UVwidth;
        అయితే (x >= 8) {
            __m128i uv = _mm_loadu_si128((__m128i *)srcUV);
            __m128i v = _mm_slli_epi16(uv, 8);
            __m128i u = _mm_srli_epi16(uv, 8);
            __m128i vu = _mm_or_si128(v, u);
            _mm_storeu_si128((__m128i *)dstUV, vu);
            srcUV += 8;
            dstUV += 8;
            x -= 8;
        }
        ఒకవేళ (x > 0) {
            స్థిరరాశి Uint8 *srcUV8 = (స్థిరరాశి Uint8 *)srcUV;
            Uint8 *dstUV8 = (Uint8 *)dstUV;
            srcUV += x;
            dstUV += x;
            అయితే (x--) {
                Uint8 u = *srcUV8++;
                Uint8 v = *srcUV8++;
                *dstUV8++ = v;
                *dstUV8++ = u;
            }
        }
        srcUV += src_UVPitch_ఎడమ;
        dstUV += dst_UVPitch_ఎడమ;
    }
    తిరిగి true;
}
#అయితే_ముగింపు

స్థిర bool SDL_Convert_Pixels_Pack_UVPlanes_గమ్యం_NV_std(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, స్థిరరాశి శూన్య *src, పూర్ణాంకం src_pitch, శూన్య *dst, పూర్ణాంకం dst_pitch, bool తిరగేయి_UV)
{
    పూర్ణాంకం x, y;
    స్థిరరాశి పూర్ణాంకం UVwidth = (వెడల్పు + 1) / 2;
    స్థిరరాశి పూర్ణాంకం UVheight = (ఎత్తు + 1) / 2;
    స్థిరరాశి పూర్ణాంకం srcUVPitch = ((src_pitch + 1) / 2);
    స్థిరరాశి పూర్ణాంకం src_UVPitch_ఎడమ = srcUVPitch - UVwidth;
    స్థిరరాశి పూర్ణాంకం dstUVPitch = ((dst_pitch + 1) / 2) * 2;
    స్థిరరాశి పూర్ణాంకం dst_UVPitch_ఎడమ = dstUVPitch - UVwidth * 2;
    స్థిరరాశి Uint8 *src1, *src2;
    Uint8 *dstUV;
    Uint8 *tmp = ఖాళీ;

    // Skip the Y plane
    src = (స్థిరరాశి Uint8 *)src + ఎత్తు * src_pitch;
    dst = (Uint8 *)dst + ఎత్తు * dst_pitch;

    ఒకవేళ (src == dst) {
        // Need to make a copy of the buffer so we don't clobber it while converting
        tmp = (Uint8 *)SDL_malloc((size_t)2 * UVheight * srcUVPitch);
        ఒకవేళ (!tmp) {
            తిరిగి false;
        }
        SDL_memcpy(tmp, src, (size_t)2 * UVheight * srcUVPitch);
        src = tmp;
    }

    ఒకవేళ (తిరగేయి_UV) {
        src2 = (స్థిరరాశి Uint8 *)src;
        src1 = src2 + UVheight * srcUVPitch;
    } లేకపోతే {
        src1 = (స్థిరరాశి Uint8 *)src;
        src2 = src1 + UVheight * srcUVPitch;
    }
    dstUV = (Uint8 *)dst;

    y = UVheight;
    అయితే (y--) {
        x = UVwidth;
        అయితే (x--) {
            *dstUV++ = *src1++;
            *dstUV++ = *src2++;
        }
        src1 += src_UVPitch_ఎడమ;
        src2 += src_UVPitch_ఎడమ;
        dstUV += dst_UVPitch_ఎడమ;
    }

    SDL_free(tmp);
    తిరిగి true;
}

స్థిర bool SDL_Convert_Pixels_విభజించు_NV_గమ్యం_UVPlanes_std(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, స్థిరరాశి శూన్య *src, పూర్ణాంకం src_pitch, శూన్య *dst, పూర్ణాంకం dst_pitch, bool తిరగేయి_UV)
{
    పూర్ణాంకం x, y;
    స్థిరరాశి పూర్ణాంకం UVwidth = (వెడల్పు + 1) / 2;
    స్థిరరాశి పూర్ణాంకం UVheight = (ఎత్తు + 1) / 2;
    స్థిరరాశి పూర్ణాంకం srcUVPitch = ((src_pitch + 1) / 2) * 2;
    స్థిరరాశి పూర్ణాంకం src_UVPitch_ఎడమ = srcUVPitch - UVwidth * 2;
    స్థిరరాశి పూర్ణాంకం dstUVPitch = ((dst_pitch + 1) / 2);
    స్థిరరాశి పూర్ణాంకం dst_UVPitch_ఎడమ = dstUVPitch - UVwidth;
    స్థిరరాశి Uint8 *srcUV;
    Uint8 *dst1, *dst2;
    Uint8 *tmp = ఖాళీ;

    // Skip the Y plane
    src = (స్థిరరాశి Uint8 *)src + ఎత్తు * src_pitch;
    dst = (Uint8 *)dst + ఎత్తు * dst_pitch;

    ఒకవేళ (src == dst) {
        // Need to make a copy of the buffer so we don't clobber it while converting
        tmp = (Uint8 *)SDL_malloc((size_t)UVheight * srcUVPitch);
        ఒకవేళ (!tmp) {
            తిరిగి false;
        }
        SDL_memcpy(tmp, src, (size_t)UVheight * srcUVPitch);
        src = tmp;
    }

    ఒకవేళ (తిరగేయి_UV) {
        dst2 = (Uint8 *)dst;
        dst1 = dst2 + UVheight * dstUVPitch;
    } లేకపోతే {
        dst1 = (Uint8 *)dst;
        dst2 = dst1 + UVheight * dstUVPitch;
    }
    srcUV = (స్థిరరాశి Uint8 *)src;

    y = UVheight;
    అయితే (y--) {
        x = UVwidth;
        అయితే (x--) {
            *dst1++ = *srcUV++;
            *dst2++ = *srcUV++;
        }
        srcUV += src_UVPitch_ఎడమ;
        dst1 += dst_UVPitch_ఎడమ;
        dst2 += dst_UVPitch_ఎడమ;
    }

    SDL_free(tmp);
    తిరిగి true;
}

స్థిర bool SDL_Convert_Pixels_మార్పిడి_NV_std(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, స్థిరరాశి శూన్య *src, పూర్ణాంకం src_pitch, శూన్య *dst, పూర్ణాంకం dst_pitch)
{
    పూర్ణాంకం x, y;
    స్థిరరాశి పూర్ణాంకం UVwidth = (వెడల్పు + 1) / 2;
    స్థిరరాశి పూర్ణాంకం UVheight = (ఎత్తు + 1) / 2;
    స్థిరరాశి పూర్ణాంకం srcUVPitch = ((src_pitch + 1) / 2) * 2;
    స్థిరరాశి పూర్ణాంకం dstUVPitch = ((dst_pitch + 1) / 2) * 2;

    // Skip the Y plane
    src = (స్థిరరాశి Uint8 *)src + ఎత్తు * src_pitch;
    dst = (Uint8 *)dst + ఎత్తు * dst_pitch;

    bool aligned = (((uintptr_t)src | (uintptr_t)dst) & 1) == 0;
    ఒకవేళ (aligned) {
        స్థిరరాశి పూర్ణాంకం src_UVPitch_ఎడమ = (srcUVPitch - UVwidth * 2) / పరిమాణం(Uint16);
        స్థిరరాశి పూర్ణాంకం dst_UVPitch_ఎడమ = (dstUVPitch - UVwidth * 2) / పరిమాణం(Uint16);
        స్థిరరాశి Uint16 *srcUV = (స్థిరరాశి Uint16 *)src;
        Uint16 *dstUV = (Uint16 *)dst;
        y = UVheight;
        అయితే (y--) {
            x = UVwidth;
            అయితే (x--) {
                *dstUV++ = SDL_Swap16(*srcUV++);
            }
            srcUV += src_UVPitch_ఎడమ;
            dstUV += dst_UVPitch_ఎడమ;
        }
    } లేకపోతే {
        స్థిరరాశి పూర్ణాంకం src_UVPitch_ఎడమ = (srcUVPitch - UVwidth * 2);
        స్థిరరాశి పూర్ణాంకం dst_UVPitch_ఎడమ = (dstUVPitch - UVwidth * 2);
        స్థిరరాశి Uint8 *srcUV = (స్థిరరాశి Uint8 *)src;
        Uint8 *dstUV = (Uint8 *)dst;
        y = UVheight;
        అయితే (y--) {
            x = UVwidth;
            అయితే (x--) {
                Uint8 u = *srcUV++;
                Uint8 v = *srcUV++;
                *dstUV++ = v;
                *dstUV++ = u;
            }
            srcUV += src_UVPitch_ఎడమ;
            dstUV += dst_UVPitch_ఎడమ;
        }
    }
    తిరిగి true;
}

స్థిర bool SDL_Convert_Pixels_Pack_UVPlanes_గమ్యం_NV(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, స్థిరరాశి శూన్య *src, పూర్ణాంకం src_pitch, శూన్య *dst, పూర్ణాంకం dst_pitch, bool తిరగేయి_UV)
{
#నిర్వచితమైతే SDL_SSE2_INTRINSICS
    ఒకవేళ (SDL_HasSSE2()) {
      తిరిగి SDL_Convert_Pixels_Pack_UVPlanes_గమ్యం_NV_SSE2(వెడల్పు, ఎత్తు, src, src_pitch, dst, dst_pitch, తిరగేయి_UV);
    }
#అయితే_ముగింపు
    తిరిగి SDL_Convert_Pixels_Pack_UVPlanes_గమ్యం_NV_std(వెడల్పు, ఎత్తు, src, src_pitch, dst, dst_pitch, తిరగేయి_UV);
}

స్థిర bool SDL_Convert_Pixels_విభజించు_NV_గమ్యం_UVPlanes(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, స్థిరరాశి శూన్య *src, పూర్ణాంకం src_pitch, శూన్య *dst, పూర్ణాంకం dst_pitch, bool తిరగేయి_UV)
{
#నిర్వచితమైతే SDL_SSE2_INTRINSICS
    ఒకవేళ (SDL_HasSSE2()) {
      తిరిగి SDL_Convert_Pixels_విభజించు_NV_గమ్యం_UVPlanes_SSE2(వెడల్పు, ఎత్తు, src, src_pitch, dst, dst_pitch, తిరగేయి_UV);
    }
#అయితే_ముగింపు
    తిరిగి SDL_Convert_Pixels_విభజించు_NV_గమ్యం_UVPlanes_std(వెడల్పు, ఎత్తు, src, src_pitch, dst, dst_pitch, తిరగేయి_UV);
}

స్థిర bool SDL_Convert_Pixels_మార్పిడి_NV(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, స్థిరరాశి శూన్య *src, పూర్ణాంకం src_pitch, శూన్య *dst, పూర్ణాంకం dst_pitch)
{
#నిర్వచితమైతే SDL_SSE2_INTRINSICS
    ఒకవేళ (SDL_HasSSE2()) {
      తిరిగి SDL_Convert_Pixels_మార్పిడి_NV_SSE2(వెడల్పు, ఎత్తు, src, src_pitch, dst, dst_pitch);
    }
#అయితే_ముగింపు
    తిరిగి SDL_Convert_Pixels_మార్పిడి_NV_std(వెడల్పు, ఎత్తు, src, src_pitch, dst, dst_pitch);
}

స్థిర bool SDL_Convert_Pixels_Planar2x2_గమ్యం_Planar2x2(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు,
                                                     SDL_PixelFormat src_format, స్థిరరాశి శూన్య *src, పూర్ణాంకం src_pitch,
                                                     SDL_PixelFormat dst_format, శూన్య *dst, పూర్ణాంకం dst_pitch)
{
    ఒకవేళ (src != dst) {
        // Copy Y plane
        పూర్ణాంకం i;
        స్థిరరాశి Uint8 *srcY = (స్థిరరాశి Uint8 *)src;
        Uint8 *dstY = (Uint8 *)dst;
        కొరకు (i = ఎత్తు; i--;) {
            SDL_memcpy(dstY, srcY, వెడల్పు);
            srcY += src_pitch;
            dstY += dst_pitch;
        }
    }

    ఎంపిక (src_format) {
    స్థితి SDL_PIXELFORMAT_YV12:
        ఎంపిక (dst_format) {
        స్థితి SDL_PIXELFORMAT_IYUV:
            తిరిగి SDL_Convert_Pixels_మార్పిడి_UVPlanes(వెడల్పు, ఎత్తు, src, src_pitch, dst, dst_pitch);
        స్థితి SDL_PIXELFORMAT_NV12:
            తిరిగి SDL_Convert_Pixels_Pack_UVPlanes_గమ్యం_NV(వెడల్పు, ఎత్తు, src, src_pitch, dst, dst_pitch, true);
        స్థితి SDL_PIXELFORMAT_NV21:
            తిరిగి SDL_Convert_Pixels_Pack_UVPlanes_గమ్యం_NV(వెడల్పు, ఎత్తు, src, src_pitch, dst, dst_pitch, false);
        అప్రమేయ:
            ఆపు;
        }
        ఆపు;
    స్థితి SDL_PIXELFORMAT_IYUV:
        ఎంపిక (dst_format) {
        స్థితి SDL_PIXELFORMAT_YV12:
            తిరిగి SDL_Convert_Pixels_మార్పిడి_UVPlanes(వెడల్పు, ఎత్తు, src, src_pitch, dst, dst_pitch);
        స్థితి SDL_PIXELFORMAT_NV12:
            తిరిగి SDL_Convert_Pixels_Pack_UVPlanes_గమ్యం_NV(వెడల్పు, ఎత్తు, src, src_pitch, dst, dst_pitch, false);
        స్థితి SDL_PIXELFORMAT_NV21:
            తిరిగి SDL_Convert_Pixels_Pack_UVPlanes_గమ్యం_NV(వెడల్పు, ఎత్తు, src, src_pitch, dst, dst_pitch, true);
        అప్రమేయ:
            ఆపు;
        }
        ఆపు;
    స్థితి SDL_PIXELFORMAT_NV12:
        ఎంపిక (dst_format) {
        స్థితి SDL_PIXELFORMAT_YV12:
            తిరిగి SDL_Convert_Pixels_విభజించు_NV_గమ్యం_UVPlanes(వెడల్పు, ఎత్తు, src, src_pitch, dst, dst_pitch, true);
        స్థితి SDL_PIXELFORMAT_IYUV:
            తిరిగి SDL_Convert_Pixels_విభజించు_NV_గమ్యం_UVPlanes(వెడల్పు, ఎత్తు, src, src_pitch, dst, dst_pitch, false);
        స్థితి SDL_PIXELFORMAT_NV21:
            తిరిగి SDL_Convert_Pixels_మార్పిడి_NV(వెడల్పు, ఎత్తు, src, src_pitch, dst, dst_pitch);
        అప్రమేయ:
            ఆపు;
        }
        ఆపు;
    స్థితి SDL_PIXELFORMAT_NV21:
        ఎంపిక (dst_format) {
        స్థితి SDL_PIXELFORMAT_YV12:
            తిరిగి SDL_Convert_Pixels_విభజించు_NV_గమ్యం_UVPlanes(వెడల్పు, ఎత్తు, src, src_pitch, dst, dst_pitch, false);
        స్థితి SDL_PIXELFORMAT_IYUV:
            తిరిగి SDL_Convert_Pixels_విభజించు_NV_గమ్యం_UVPlanes(వెడల్పు, ఎత్తు, src, src_pitch, dst, dst_pitch, true);
        స్థితి SDL_PIXELFORMAT_NV12:
            తిరిగి SDL_Convert_Pixels_మార్పిడి_NV(వెడల్పు, ఎత్తు, src, src_pitch, dst, dst_pitch);
        అప్రమేయ:
            ఆపు;
        }
        ఆపు;
    అప్రమేయ:
        ఆపు;
    }
    తిరిగి SDL_సమితి_Error("SDL_ConvertPixels_Planar2x2_to_Planar2x2: Unsupported YUV conversion: %s -> %s", SDL_GetPixelFormatName(src_format),
                        SDL_GetPixelFormatName(dst_format));
}

#నిర్వచితమైతే SDL_SSE2_INTRINSICS
#నిర్వచించు PACKED4_గమ్యం_PACKED4_అడ్డువరుస_SSE2(shuffle)                      \
    అయితే (x >= 4) {                                              \
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

స్థిర bool SDL_TARGETING("sse2") SDL_Convert_Pixels_YUY2_గమ్యం_UYVY_SSE2(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, స్థిరరాశి శూన్య *src, పూర్ణాంకం src_pitch, శూన్య *dst, పూర్ణాంకం dst_pitch)
{
    పూర్ణాంకం x, y;
    స్థిరరాశి పూర్ణాంకం YUVwidth = (వెడల్పు + 1) / 2;
    స్థిరరాశి పూర్ణాంకం src_YUVPitch_ఎడమ = (src_pitch - YUVwidth * 4);
    స్థిరరాశి పూర్ణాంకం dst_YUVPitch_ఎడమ = (dst_pitch - YUVwidth * 4);
    స్థిరరాశి Uint8 *srcYUV = (స్థిరరాశి Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = ఎత్తు;
    x = YUVwidth;
    అయితే (y--) {
        PACKED4_గమ్యం_PACKED4_అడ్డువరుస_SSE2(_MM_SHUFFLE(2, 3, 0, 1));
        అయితే (x--) {
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
        srcYUV += src_YUVPitch_ఎడమ;
        dstYUV += dst_YUVPitch_ఎడమ;
        x = YUVwidth;
    }
    తిరిగి true;
}

స్థిర bool SDL_TARGETING("sse2") SDL_Convert_Pixels_YUY2_గమ్యం_YVYU_SSE2(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, స్థిరరాశి శూన్య *src, పూర్ణాంకం src_pitch, శూన్య *dst, పూర్ణాంకం dst_pitch)
{
    పూర్ణాంకం x, y;
    స్థిరరాశి పూర్ణాంకం YUVwidth = (వెడల్పు + 1) / 2;
    స్థిరరాశి పూర్ణాంకం src_YUVPitch_ఎడమ = (src_pitch - YUVwidth * 4);
    స్థిరరాశి పూర్ణాంకం dst_YUVPitch_ఎడమ = (dst_pitch - YUVwidth * 4);
    స్థిరరాశి Uint8 *srcYUV = (స్థిరరాశి Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = ఎత్తు;
    x = YUVwidth;
    అయితే (y--) {
        PACKED4_గమ్యం_PACKED4_అడ్డువరుస_SSE2(_MM_SHUFFLE(1, 2, 3, 0));
        అయితే (x--) {
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
        srcYUV += src_YUVPitch_ఎడమ;
        dstYUV += dst_YUVPitch_ఎడమ;
        x = YUVwidth;
    }
    తిరిగి true;
}

స్థిర bool SDL_TARGETING("sse2") SDL_Convert_Pixels_UYVY_గమ్యం_YUY2_SSE2(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, స్థిరరాశి శూన్య *src, పూర్ణాంకం src_pitch, శూన్య *dst, పూర్ణాంకం dst_pitch)
{
    పూర్ణాంకం x, y;
    స్థిరరాశి పూర్ణాంకం YUVwidth = (వెడల్పు + 1) / 2;
    స్థిరరాశి పూర్ణాంకం src_YUVPitch_ఎడమ = (src_pitch - YUVwidth * 4);
    స్థిరరాశి పూర్ణాంకం dst_YUVPitch_ఎడమ = (dst_pitch - YUVwidth * 4);
    స్థిరరాశి Uint8 *srcYUV = (స్థిరరాశి Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = ఎత్తు;
    x = YUVwidth;
    అయితే (y--) {
        PACKED4_గమ్యం_PACKED4_అడ్డువరుస_SSE2(_MM_SHUFFLE(2, 3, 0, 1));
        అయితే (x--) {
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
        srcYUV += src_YUVPitch_ఎడమ;
        dstYUV += dst_YUVPitch_ఎడమ;
        x = YUVwidth;
    }
    తిరిగి true;
}

స్థిర bool SDL_TARGETING("sse2") SDL_Convert_Pixels_UYVY_గమ్యం_YVYU_SSE2(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, స్థిరరాశి శూన్య *src, పూర్ణాంకం src_pitch, శూన్య *dst, పూర్ణాంకం dst_pitch)
{
    పూర్ణాంకం x, y;
    స్థిరరాశి పూర్ణాంకం YUVwidth = (వెడల్పు + 1) / 2;
    స్థిరరాశి పూర్ణాంకం src_YUVPitch_ఎడమ = (src_pitch - YUVwidth * 4);
    స్థిరరాశి పూర్ణాంకం dst_YUVPitch_ఎడమ = (dst_pitch - YUVwidth * 4);
    స్థిరరాశి Uint8 *srcYUV = (స్థిరరాశి Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = ఎత్తు;
    x = YUVwidth;
    అయితే (y--) {
        PACKED4_గమ్యం_PACKED4_అడ్డువరుస_SSE2(_MM_SHUFFLE(0, 3, 2, 1));
        అయితే (x--) {
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
        srcYUV += src_YUVPitch_ఎడమ;
        dstYUV += dst_YUVPitch_ఎడమ;
        x = YUVwidth;
    }
    తిరిగి true;
}

స్థిర bool SDL_TARGETING("sse2") SDL_Convert_Pixels_YVYU_గమ్యం_YUY2_SSE2(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, స్థిరరాశి శూన్య *src, పూర్ణాంకం src_pitch, శూన్య *dst, పూర్ణాంకం dst_pitch)
{
    పూర్ణాంకం x, y;
    స్థిరరాశి పూర్ణాంకం YUVwidth = (వెడల్పు + 1) / 2;
    స్థిరరాశి పూర్ణాంకం src_YUVPitch_ఎడమ = (src_pitch - YUVwidth * 4);
    స్థిరరాశి పూర్ణాంకం dst_YUVPitch_ఎడమ = (dst_pitch - YUVwidth * 4);
    స్థిరరాశి Uint8 *srcYUV = (స్థిరరాశి Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = ఎత్తు;
    x = YUVwidth;
    అయితే (y--) {
        PACKED4_గమ్యం_PACKED4_అడ్డువరుస_SSE2(_MM_SHUFFLE(1, 2, 3, 0));
        అయితే (x--) {
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
        srcYUV += src_YUVPitch_ఎడమ;
        dstYUV += dst_YUVPitch_ఎడమ;
        x = YUVwidth;
    }
    తిరిగి true;
}

స్థిర bool SDL_TARGETING("sse2") SDL_Convert_Pixels_YVYU_గమ్యం_UYVY_SSE2(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, స్థిరరాశి శూన్య *src, పూర్ణాంకం src_pitch, శూన్య *dst, పూర్ణాంకం dst_pitch)
{
    పూర్ణాంకం x, y;
    స్థిరరాశి పూర్ణాంకం YUVwidth = (వెడల్పు + 1) / 2;
    స్థిరరాశి పూర్ణాంకం src_YUVPitch_ఎడమ = (src_pitch - YUVwidth * 4);
    స్థిరరాశి పూర్ణాంకం dst_YUVPitch_ఎడమ = (dst_pitch - YUVwidth * 4);
    స్థిరరాశి Uint8 *srcYUV = (స్థిరరాశి Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = ఎత్తు;
    x = YUVwidth;
    అయితే (y--) {
        PACKED4_గమ్యం_PACKED4_అడ్డువరుస_SSE2(_MM_SHUFFLE(2, 1, 0, 3));
        అయితే (x--) {
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
        srcYUV += src_YUVPitch_ఎడమ;
        dstYUV += dst_YUVPitch_ఎడమ;
        x = YUVwidth;
    }
    తిరిగి true;
}
#అయితే_ముగింపు

స్థిర bool SDL_Convert_Pixels_YUY2_గమ్యం_UYVY_std(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, స్థిరరాశి శూన్య *src, పూర్ణాంకం src_pitch, శూన్య *dst, పూర్ణాంకం dst_pitch)
{
    పూర్ణాంకం x, y;
    స్థిరరాశి పూర్ణాంకం YUVwidth = (వెడల్పు + 1) / 2;
    స్థిరరాశి పూర్ణాంకం src_YUVPitch_ఎడమ = (src_pitch - YUVwidth * 4);
    స్థిరరాశి పూర్ణాంకం dst_YUVPitch_ఎడమ = (dst_pitch - YUVwidth * 4);
    స్థిరరాశి Uint8 *srcYUV = (స్థిరరాశి Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = ఎత్తు;
    అయితే (y--) {
        x = YUVwidth;
        అయితే (x--) {
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
        srcYUV += src_YUVPitch_ఎడమ;
        dstYUV += dst_YUVPitch_ఎడమ;
    }
    తిరిగి true;
}

స్థిర bool SDL_Convert_Pixels_YUY2_గమ్యం_YVYU_std(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, స్థిరరాశి శూన్య *src, పూర్ణాంకం src_pitch, శూన్య *dst, పూర్ణాంకం dst_pitch)
{
    పూర్ణాంకం x, y;
    స్థిరరాశి పూర్ణాంకం YUVwidth = (వెడల్పు + 1) / 2;
    స్థిరరాశి పూర్ణాంకం src_YUVPitch_ఎడమ = (src_pitch - YUVwidth * 4);
    స్థిరరాశి పూర్ణాంకం dst_YUVPitch_ఎడమ = (dst_pitch - YUVwidth * 4);
    స్థిరరాశి Uint8 *srcYUV = (స్థిరరాశి Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = ఎత్తు;
    అయితే (y--) {
        x = YUVwidth;
        అయితే (x--) {
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
        srcYUV += src_YUVPitch_ఎడమ;
        dstYUV += dst_YUVPitch_ఎడమ;
    }
    తిరిగి true;
}

స్థిర bool SDL_Convert_Pixels_UYVY_గమ్యం_YUY2_std(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, స్థిరరాశి శూన్య *src, పూర్ణాంకం src_pitch, శూన్య *dst, పూర్ణాంకం dst_pitch)
{
    పూర్ణాంకం x, y;
    స్థిరరాశి పూర్ణాంకం YUVwidth = (వెడల్పు + 1) / 2;
    స్థిరరాశి పూర్ణాంకం src_YUVPitch_ఎడమ = (src_pitch - YUVwidth * 4);
    స్థిరరాశి పూర్ణాంకం dst_YUVPitch_ఎడమ = (dst_pitch - YUVwidth * 4);
    స్థిరరాశి Uint8 *srcYUV = (స్థిరరాశి Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = ఎత్తు;
    అయితే (y--) {
        x = YUVwidth;
        అయితే (x--) {
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
        srcYUV += src_YUVPitch_ఎడమ;
        dstYUV += dst_YUVPitch_ఎడమ;
    }
    తిరిగి true;
}

స్థిర bool SDL_Convert_Pixels_UYVY_గమ్యం_YVYU_std(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, స్థిరరాశి శూన్య *src, పూర్ణాంకం src_pitch, శూన్య *dst, పూర్ణాంకం dst_pitch)
{
    పూర్ణాంకం x, y;
    స్థిరరాశి పూర్ణాంకం YUVwidth = (వెడల్పు + 1) / 2;
    స్థిరరాశి పూర్ణాంకం src_YUVPitch_ఎడమ = (src_pitch - YUVwidth * 4);
    స్థిరరాశి పూర్ణాంకం dst_YUVPitch_ఎడమ = (dst_pitch - YUVwidth * 4);
    స్థిరరాశి Uint8 *srcYUV = (స్థిరరాశి Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = ఎత్తు;
    అయితే (y--) {
        x = YUVwidth;
        అయితే (x--) {
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
        srcYUV += src_YUVPitch_ఎడమ;
        dstYUV += dst_YUVPitch_ఎడమ;
    }
    తిరిగి true;
}

స్థిర bool SDL_Convert_Pixels_YVYU_గమ్యం_YUY2_std(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, స్థిరరాశి శూన్య *src, పూర్ణాంకం src_pitch, శూన్య *dst, పూర్ణాంకం dst_pitch)
{
    పూర్ణాంకం x, y;
    స్థిరరాశి పూర్ణాంకం YUVwidth = (వెడల్పు + 1) / 2;
    స్థిరరాశి పూర్ణాంకం src_YUVPitch_ఎడమ = (src_pitch - YUVwidth * 4);
    స్థిరరాశి పూర్ణాంకం dst_YUVPitch_ఎడమ = (dst_pitch - YUVwidth * 4);
    స్థిరరాశి Uint8 *srcYUV = (స్థిరరాశి Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = ఎత్తు;
    అయితే (y--) {
        x = YUVwidth;
        అయితే (x--) {
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
        srcYUV += src_YUVPitch_ఎడమ;
        dstYUV += dst_YUVPitch_ఎడమ;
    }
    తిరిగి true;
}

స్థిర bool SDL_Convert_Pixels_YVYU_గమ్యం_UYVY_std(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, స్థిరరాశి శూన్య *src, పూర్ణాంకం src_pitch, శూన్య *dst, పూర్ణాంకం dst_pitch)
{
    పూర్ణాంకం x, y;
    స్థిరరాశి పూర్ణాంకం YUVwidth = (వెడల్పు + 1) / 2;
    స్థిరరాశి పూర్ణాంకం src_YUVPitch_ఎడమ = (src_pitch - YUVwidth * 4);
    స్థిరరాశి పూర్ణాంకం dst_YUVPitch_ఎడమ = (dst_pitch - YUVwidth * 4);
    స్థిరరాశి Uint8 *srcYUV = (స్థిరరాశి Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = ఎత్తు;
    అయితే (y--) {
        x = YUVwidth;
        అయితే (x--) {
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
        srcYUV += src_YUVPitch_ఎడమ;
        dstYUV += dst_YUVPitch_ఎడమ;
    }
    తిరిగి true;
}

స్థిర bool SDL_Convert_Pixels_YUY2_గమ్యం_UYVY(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, స్థిరరాశి శూన్య *src, పూర్ణాంకం src_pitch, శూన్య *dst, పూర్ణాంకం dst_pitch)
{
#నిర్వచితమైతే SDL_SSE2_INTRINSICS
    ఒకవేళ (SDL_HasSSE2()) {
      తిరిగి SDL_Convert_Pixels_YUY2_గమ్యం_UYVY_SSE2(వెడల్పు, ఎత్తు, src, src_pitch, dst, dst_pitch);
    }
#అయితే_ముగింపు
    తిరిగి SDL_Convert_Pixels_YUY2_గమ్యం_UYVY_std(వెడల్పు, ఎత్తు, src, src_pitch, dst, dst_pitch);
}

స్థిర bool SDL_Convert_Pixels_YUY2_గమ్యం_YVYU(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, స్థిరరాశి శూన్య *src, పూర్ణాంకం src_pitch, శూన్య *dst, పూర్ణాంకం dst_pitch)
{
#నిర్వచితమైతే SDL_SSE2_INTRINSICS
    ఒకవేళ (SDL_HasSSE2()) {
      తిరిగి SDL_Convert_Pixels_YUY2_గమ్యం_YVYU_SSE2(వెడల్పు, ఎత్తు, src, src_pitch, dst, dst_pitch);
    }
#అయితే_ముగింపు
    తిరిగి SDL_Convert_Pixels_YUY2_గమ్యం_YVYU_std(వెడల్పు, ఎత్తు, src, src_pitch, dst, dst_pitch);
}

స్థిర bool SDL_Convert_Pixels_UYVY_గమ్యం_YUY2(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, స్థిరరాశి శూన్య *src, పూర్ణాంకం src_pitch, శూన్య *dst, పూర్ణాంకం dst_pitch)
{
#నిర్వచితమైతే SDL_SSE2_INTRINSICS
    ఒకవేళ (SDL_HasSSE2()) {
      తిరిగి SDL_Convert_Pixels_UYVY_గమ్యం_YUY2_SSE2(వెడల్పు, ఎత్తు, src, src_pitch, dst, dst_pitch);
    }
#అయితే_ముగింపు
    తిరిగి SDL_Convert_Pixels_UYVY_గమ్యం_YUY2_std(వెడల్పు, ఎత్తు, src, src_pitch, dst, dst_pitch);
}

స్థిర bool SDL_Convert_Pixels_UYVY_గమ్యం_YVYU(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, స్థిరరాశి శూన్య *src, పూర్ణాంకం src_pitch, శూన్య *dst, పూర్ణాంకం dst_pitch)
{
#నిర్వచితమైతే SDL_SSE2_INTRINSICS
    ఒకవేళ (SDL_HasSSE2()) {
      తిరిగి SDL_Convert_Pixels_UYVY_గమ్యం_YVYU_SSE2(వెడల్పు, ఎత్తు, src, src_pitch, dst, dst_pitch);
    }
#అయితే_ముగింపు
    తిరిగి SDL_Convert_Pixels_UYVY_గమ్యం_YVYU_std(వెడల్పు, ఎత్తు, src, src_pitch, dst, dst_pitch);
}

స్థిర bool SDL_Convert_Pixels_YVYU_గమ్యం_YUY2(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, స్థిరరాశి శూన్య *src, పూర్ణాంకం src_pitch, శూన్య *dst, పూర్ణాంకం dst_pitch)
{
#నిర్వచితమైతే SDL_SSE2_INTRINSICS
    ఒకవేళ (SDL_HasSSE2()) {
      తిరిగి SDL_Convert_Pixels_YVYU_గమ్యం_YUY2_SSE2(వెడల్పు, ఎత్తు, src, src_pitch, dst, dst_pitch);
    }
#అయితే_ముగింపు
    తిరిగి SDL_Convert_Pixels_YVYU_గమ్యం_YUY2_std(వెడల్పు, ఎత్తు, src, src_pitch, dst, dst_pitch);
}

స్థిర bool SDL_Convert_Pixels_YVYU_గమ్యం_UYVY(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, స్థిరరాశి శూన్య *src, పూర్ణాంకం src_pitch, శూన్య *dst, పూర్ణాంకం dst_pitch)
{
#నిర్వచితమైతే SDL_SSE2_INTRINSICS
    ఒకవేళ (SDL_HasSSE2()) {
      తిరిగి SDL_Convert_Pixels_YVYU_గమ్యం_UYVY_SSE2(వెడల్పు, ఎత్తు, src, src_pitch, dst, dst_pitch);
    }
#అయితే_ముగింపు
    తిరిగి SDL_Convert_Pixels_YVYU_గమ్యం_UYVY_std(వెడల్పు, ఎత్తు, src, src_pitch, dst, dst_pitch);
}

స్థిర bool SDL_Convert_Pixels_Packed4_గమ్యం_Packed4(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు,
                                                SDL_PixelFormat src_format, స్థిరరాశి శూన్య *src, పూర్ణాంకం src_pitch,
                                                SDL_PixelFormat dst_format, శూన్య *dst, పూర్ణాంకం dst_pitch)
{
    ఎంపిక (src_format) {
    స్థితి SDL_PIXELFORMAT_YUY2:
        ఎంపిక (dst_format) {
        స్థితి SDL_PIXELFORMAT_UYVY:
            తిరిగి SDL_Convert_Pixels_YUY2_గమ్యం_UYVY(వెడల్పు, ఎత్తు, src, src_pitch, dst, dst_pitch);
        స్థితి SDL_PIXELFORMAT_YVYU:
            తిరిగి SDL_Convert_Pixels_YUY2_గమ్యం_YVYU(వెడల్పు, ఎత్తు, src, src_pitch, dst, dst_pitch);
        అప్రమేయ:
            ఆపు;
        }
        ఆపు;
    స్థితి SDL_PIXELFORMAT_UYVY:
        ఎంపిక (dst_format) {
        స్థితి SDL_PIXELFORMAT_YUY2:
            తిరిగి SDL_Convert_Pixels_UYVY_గమ్యం_YUY2(వెడల్పు, ఎత్తు, src, src_pitch, dst, dst_pitch);
        స్థితి SDL_PIXELFORMAT_YVYU:
            తిరిగి SDL_Convert_Pixels_UYVY_గమ్యం_YVYU(వెడల్పు, ఎత్తు, src, src_pitch, dst, dst_pitch);
        అప్రమేయ:
            ఆపు;
        }
        ఆపు;
    స్థితి SDL_PIXELFORMAT_YVYU:
        ఎంపిక (dst_format) {
        స్థితి SDL_PIXELFORMAT_YUY2:
            తిరిగి SDL_Convert_Pixels_YVYU_గమ్యం_YUY2(వెడల్పు, ఎత్తు, src, src_pitch, dst, dst_pitch);
        స్థితి SDL_PIXELFORMAT_UYVY:
            తిరిగి SDL_Convert_Pixels_YVYU_గమ్యం_UYVY(వెడల్పు, ఎత్తు, src, src_pitch, dst, dst_pitch);
        అప్రమేయ:
            ఆపు;
        }
        ఆపు;
    అప్రమేయ:
        ఆపు;
    }
    తిరిగి SDL_సమితి_Error("SDL_ConvertPixels_Packed4_to_Packed4: Unsupported YUV conversion: %s -> %s", SDL_GetPixelFormatName(src_format),
                        SDL_GetPixelFormatName(dst_format));
}

స్థిర bool SDL_Convert_Pixels_Planar2x2_గమ్యం_Packed4(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు,
                                                   SDL_PixelFormat src_format, స్థిరరాశి శూన్య *src, పూర్ణాంకం src_pitch,
                                                   SDL_PixelFormat dst_format, శూన్య *dst, పూర్ణాంకం dst_pitch)
{
    పూర్ణాంకం x, y;
    స్థిరరాశి Uint8 *srcY1, *srcY2, *srcU, *srcV;
    Uint32 srcY_pitch, srcUV_pitch;
    Uint32 src_Y_pitch_ఎడమ, src_UV_pitch_ఎడమ, srcUV_pixel_stride;
    Uint8 *dstY1, *dstY2, *dstU1, *dstU2, *dstV1, *dstV2;
    Uint32 dstY_pitch, dstUV_pitch;
    Uint32 dst_pitch_ఎడమ;

    ఒకవేళ (src == dst) {
        తిరిగి SDL_సమితి_Error("Can't change YUV plane types in-place");
    }

    ఒకవేళ (!GetYUVPlanes(వెడల్పు, ఎత్తు, src_format, src, src_pitch,
                      &srcY1, &srcU, &srcV, &srcY_pitch, &srcUV_pitch)) {
        తిరిగి false;
    }
    srcY2 = srcY1 + srcY_pitch;
    src_Y_pitch_ఎడమ = (srcY_pitch - వెడల్పు);

    ఒకవేళ (src_format == SDL_PIXELFORMAT_NV12 || src_format == SDL_PIXELFORMAT_NV21) {
        srcUV_pixel_stride = 2;
        src_UV_pitch_ఎడమ = (srcUV_pitch - 2 * ((వెడల్పు + 1) / 2));
    } లేకపోతే {
        srcUV_pixel_stride = 1;
        src_UV_pitch_ఎడమ = (srcUV_pitch - ((వెడల్పు + 1) / 2));
    }

    ఒకవేళ (!GetYUVPlanes(వెడల్పు, ఎత్తు, dst_format, dst, dst_pitch,
                      (స్థిరరాశి Uint8 **)&dstY1, (స్థిరరాశి Uint8 **)&dstU1, (స్థిరరాశి Uint8 **)&dstV1,
                      &dstY_pitch, &dstUV_pitch)) {
        తిరిగి false;
    }
    dstY2 = dstY1 + dstY_pitch;
    dstU2 = dstU1 + dstUV_pitch;
    dstV2 = dstV1 + dstUV_pitch;
    dst_pitch_ఎడమ = (dstY_pitch - 4 * ((వెడల్పు + 1) / 2));

    // Copy 2x2 blocks of pixels at a time
    కొరకు (y = 0; y < (ఎత్తు - 1); y += 2) {
        కొరకు (x = 0; x < (వెడల్పు - 1); x += 2) {
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
        ఒకవేళ (x == (వెడల్పు - 1)) {
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

        srcY1 += src_Y_pitch_ఎడమ + srcY_pitch;
        srcY2 += src_Y_pitch_ఎడమ + srcY_pitch;
        srcU += src_UV_pitch_ఎడమ;
        srcV += src_UV_pitch_ఎడమ;
        dstY1 += dst_pitch_ఎడమ + dstY_pitch;
        dstY2 += dst_pitch_ఎడమ + dstY_pitch;
        dstU1 += dst_pitch_ఎడమ + dstUV_pitch;
        dstU2 += dst_pitch_ఎడమ + dstUV_pitch;
        dstV1 += dst_pitch_ఎడమ + dstUV_pitch;
        dstV2 += dst_pitch_ఎడమ + dstUV_pitch;
    }

    // Last row
    ఒకవేళ (y == (ఎత్తు - 1)) {
        కొరకు (x = 0; x < (వెడల్పు - 1); x += 2) {
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
        ఒకవేళ (x == (వెడల్పు - 1)) {
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
    తిరిగి true;
}

స్థిర bool SDL_Convert_Pixels_Packed4_గమ్యం_Planar2x2(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు,
                                                   SDL_PixelFormat src_format, స్థిరరాశి శూన్య *src, పూర్ణాంకం src_pitch,
                                                   SDL_PixelFormat dst_format, శూన్య *dst, పూర్ణాంకం dst_pitch)
{
    పూర్ణాంకం x, y;
    స్థిరరాశి Uint8 *srcY1, *srcY2, *srcU1, *srcU2, *srcV1, *srcV2;
    Uint32 srcY_pitch, srcUV_pitch;
    Uint32 src_pitch_ఎడమ;
    Uint8 *dstY1, *dstY2, *dstU, *dstV;
    Uint32 dstY_pitch, dstUV_pitch;
    Uint32 dst_Y_pitch_ఎడమ, dst_UV_pitch_ఎడమ, dstUV_pixel_stride;

    ఒకవేళ (src == dst) {
        తిరిగి SDL_సమితి_Error("Can't change YUV plane types in-place");
    }

    ఒకవేళ (!GetYUVPlanes(వెడల్పు, ఎత్తు, src_format, src, src_pitch,
                      &srcY1, &srcU1, &srcV1, &srcY_pitch, &srcUV_pitch)) {
        తిరిగి false;
    }
    srcY2 = srcY1 + srcY_pitch;
    srcU2 = srcU1 + srcUV_pitch;
    srcV2 = srcV1 + srcUV_pitch;
    src_pitch_ఎడమ = (srcY_pitch - 4 * ((వెడల్పు + 1) / 2));

    ఒకవేళ (!GetYUVPlanes(వెడల్పు, ఎత్తు, dst_format, dst, dst_pitch,
                      (స్థిరరాశి Uint8 **)&dstY1, (స్థిరరాశి Uint8 **)&dstU, (స్థిరరాశి Uint8 **)&dstV,
                      &dstY_pitch, &dstUV_pitch)) {
        తిరిగి false;
    }
    dstY2 = dstY1 + dstY_pitch;
    dst_Y_pitch_ఎడమ = (dstY_pitch - వెడల్పు);

    ఒకవేళ (dst_format == SDL_PIXELFORMAT_NV12 || dst_format == SDL_PIXELFORMAT_NV21) {
        dstUV_pixel_stride = 2;
        dst_UV_pitch_ఎడమ = (dstUV_pitch - 2 * ((వెడల్పు + 1) / 2));
    } లేకపోతే {
        dstUV_pixel_stride = 1;
        dst_UV_pitch_ఎడమ = (dstUV_pitch - ((వెడల్పు + 1) / 2));
    }

    // Copy 2x2 blocks of pixels at a time
    కొరకు (y = 0; y < (ఎత్తు - 1); y += 2) {
        కొరకు (x = 0; x < (వెడల్పు - 1); x += 2) {
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
        ఒకవేళ (x == (వెడల్పు - 1)) {
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

        srcY1 += src_pitch_ఎడమ + srcY_pitch;
        srcY2 += src_pitch_ఎడమ + srcY_pitch;
        srcU1 += src_pitch_ఎడమ + srcUV_pitch;
        srcU2 += src_pitch_ఎడమ + srcUV_pitch;
        srcV1 += src_pitch_ఎడమ + srcUV_pitch;
        srcV2 += src_pitch_ఎడమ + srcUV_pitch;
        dstY1 += dst_Y_pitch_ఎడమ + dstY_pitch;
        dstY2 += dst_Y_pitch_ఎడమ + dstY_pitch;
        dstU += dst_UV_pitch_ఎడమ;
        dstV += dst_UV_pitch_ఎడమ;
    }

    // Last row
    ఒకవేళ (y == (ఎత్తు - 1)) {
        కొరకు (x = 0; x < (వెడల్పు - 1); x += 2) {
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
        ఒకవేళ (x == (వెడల్పు - 1)) {
            *dstY1 = *srcY1;
            *dstU = *srcU1;
            *dstV = *srcV1;
        }
    }
    తిరిగి true;
}

#అయితే_ముగింపు // SDL_HAVE_YUV

bool SDL_Convert_Pixels_YUV_గమ్యం_YUV(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు,
                                  SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, స్థిరరాశి శూన్య *src, పూర్ణాంకం src_pitch,
                                  SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, శూన్య *dst, పూర్ణాంకం dst_pitch)
{
#నిర్వచితమైతే SDL_HAVE_YUV
    ఒకవేళ (src_colorspace != dst_colorspace) {
        తిరిగి SDL_సమితి_Error("SDL_ConvertPixels_YUV_to_YUV: colorspace conversion not supported");
    }

    ఒకవేళ (src_format == dst_format) {
        ఒకవేళ (src == dst) {
            // Nothing to do
            తిరిగి true;
        }
        తిరిగి SDL_Convert_Pixels_YUV_గమ్యం_YUV_Copy(వెడల్పు, ఎత్తు, src_format, src, src_pitch, dst, dst_pitch);
    }

    ఒకవేళ (IsPlanar2x2Format(src_format) && IsPlanar2x2Format(dst_format)) {
        తిరిగి SDL_Convert_Pixels_Planar2x2_గమ్యం_Planar2x2(వెడల్పు, ఎత్తు, src_format, src, src_pitch, dst_format, dst, dst_pitch);
    } లేకపోతే ఒకవేళ (IsPacked4Format(src_format) && IsPacked4Format(dst_format)) {
        తిరిగి SDL_Convert_Pixels_Packed4_గమ్యం_Packed4(వెడల్పు, ఎత్తు, src_format, src, src_pitch, dst_format, dst, dst_pitch);
    } లేకపోతే ఒకవేళ (IsPlanar2x2Format(src_format) && IsPacked4Format(dst_format)) {
        తిరిగి SDL_Convert_Pixels_Planar2x2_గమ్యం_Packed4(వెడల్పు, ఎత్తు, src_format, src, src_pitch, dst_format, dst, dst_pitch);
    } లేకపోతే ఒకవేళ (IsPacked4Format(src_format) && IsPlanar2x2Format(dst_format)) {
        తిరిగి SDL_Convert_Pixels_Packed4_గమ్యం_Planar2x2(వెడల్పు, ఎత్తు, src_format, src, src_pitch, dst_format, dst, dst_pitch);
    } లేకపోతే {
        తిరిగి SDL_సమితి_Error("SDL_ConvertPixels_YUV_to_YUV: Unsupported YUV conversion: %s -> %s", SDL_GetPixelFormatName(src_format),
                            SDL_GetPixelFormatName(dst_format));
    }
#లేకపోతే
    తిరిగి SDL_సమితి_Error("SDL not built with YUV support");
#అయితే_ముగింపు
}
