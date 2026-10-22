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

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_pixels_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_yuv_c.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "yuv2rgb/yuv_rgb.h"


ਸਥਿਰ bool IsPlanar1x1Format(SDL_PixelFormat format)
{
    ਵਾਪਸ format == SDL_PIXELFORMAT_I444 || format == SDL_PIXELFORMAT_I4FL;
}

ਸਥਿਰ bool IsPlanar2x2Format(SDL_PixelFormat format)
{
    ਵਾਪਸ format == SDL_PIXELFORMAT_YV12 ||
           format == SDL_PIXELFORMAT_IYUV ||
           format == SDL_PIXELFORMAT_NV12 ||
           format == SDL_PIXELFORMAT_NV21 ||
           format == SDL_PIXELFORMAT_P010 ||
           format == SDL_PIXELFORMAT_I0FL;
}

ਸਥਿਰ bool IsPacked4Format(Uint32 format)
{
    ਵਾਪਸ format == SDL_PIXELFORMAT_YUY2 || format == SDL_PIXELFORMAT_UYVY || format == SDL_PIXELFORMAT_YVYU;
}

/*
 * Calculate YUV size and pitch. Check for overflow.
 * Output 'pitch' that can be used with SDL_ConvertPixels()
 */
bool SDL_CalculateYUVSize(SDL_PixelFormat format, ਪੂਰਨ w, ਪੂਰਨ h, size_t *ਮਾਪ, size_t *pitch)
{
    ਪੂਰਨ sz_plane = 0, sz_plane_chroma = 0, sz_plane_packed = 0;

    ਜੇ (IsPlanar1x1Format(format)) {
        /* sz_plane == w * h * bpp; */
        size_t s1;
        ਜੇ (!SDL_ਮਾਪ_mul_check_ਉਛਾਲ(w, h, &s1)) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("width * height would overflow");
        }
        ਜੇ (!SDL_ਮਾਪ_mul_check_ਉਛਾਲ(s1, SDL_BYTESPERPIXEL(format), &s1)) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("width * height * bpp would overflow");
        }
        sz_plane = (ਪੂਰਨ)s1;
        sz_plane_chroma = sz_plane;
    } ਨਹੀਂਤਾਂ ਜੇ (IsPlanar2x2Format(format)) {
        {
            /* sz_plane == w * h * bpp; */
            size_t s1;
            ਜੇ (!SDL_ਮਾਪ_mul_check_ਉਛਾਲ(w, h, &s1)) {
                ਵਾਪਸ SDL_ਸੈੱਟ_Error("width * height would overflow");
            }
            ਜੇ (!SDL_ਮਾਪ_mul_check_ਉਛਾਲ(s1, SDL_BYTESPERPIXEL(format), &s1)) {
                ਵਾਪਸ SDL_ਸੈੱਟ_Error("width * height * bpp would overflow");
            }
            sz_plane = (ਪੂਰਨ)s1;
        }

        {
            /* sz_plane_chroma == ((w + 1) / 2) * ((h + 1) / 2) * bpp; */
            size_t s1, s2, s3;
            ਜੇ (!SDL_ਮਾਪ_ਜੋੜੋ_check_ਉਛਾਲ(w, 1, &s1)) {
                ਵਾਪਸ SDL_ਸੈੱਟ_Error("width + 1 would overflow");
            }
            s1 = s1 / 2;
            ਜੇ (!SDL_ਮਾਪ_ਜੋੜੋ_check_ਉਛਾਲ(h, 1, &s2)) {
                ਵਾਪਸ SDL_ਸੈੱਟ_Error("height + 1 would overflow");
            }
            s2 = s2 / 2;
            ਜੇ (!SDL_ਮਾਪ_mul_check_ਉਛਾਲ(s1, s2, &s3)) {
                ਵਾਪਸ SDL_ਸੈੱਟ_Error("width * height would overflow");
            }
            ਜੇ (!SDL_ਮਾਪ_mul_check_ਉਛਾਲ(s3, SDL_BYTESPERPIXEL(format), &s3)) {
                ਵਾਪਸ SDL_ਸੈੱਟ_Error("width * height * bpp would overflow");
            }
            sz_plane_chroma = (ਪੂਰਨ)s3;
        }
    } ਨਹੀਂਤਾਂ ਜੇ (IsPacked4Format(format)) {
        /* sz_plane_packed == ((w + 1) / 2) * h; */
        size_t s1, s2;
        ਜੇ (!SDL_ਮਾਪ_ਜੋੜੋ_check_ਉਛਾਲ(w, 1, &s1)) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("width + 1 would overflow");
        }
        s1 = s1 / 2;
        ਜੇ (!SDL_ਮਾਪ_mul_check_ਉਛਾਲ(s1, h, &s2)) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("width * height would overflow");
        }
        sz_plane_packed = (ਪੂਰਨ) s2;
    } ਨਹੀਂਤਾਂ {
        ਵਾਪਸ SDL_Unsupported();
    }

    ਚੋਣ (format) {
    ਹਾਲਤ SDL_PIXELFORMAT_YV12: /**< Planar mode: Y + V + U  (3 planes) */
    ਹਾਲਤ SDL_PIXELFORMAT_IYUV: /**< Planar mode: Y + U + V  (3 planes) */
    ਹਾਲਤ SDL_PIXELFORMAT_I444: /**< Planar mode: Y + U + V  (3 planes) */
    ਹਾਲਤ SDL_PIXELFORMAT_I0FL: /**< Planar mode: Y + U + V  (3 planes) */
    ਹਾਲਤ SDL_PIXELFORMAT_I4FL: /**< Planar mode: Y + U + V  (3 planes) */

        ਜੇ (pitch) {
            *pitch = w * SDL_BYTESPERPIXEL(format);
        }

        ਜੇ (ਮਾਪ) {
            // dst_size == sz_plane + sz_plane_chroma + sz_plane_chroma;
            size_t s1, s2;
            ਜੇ (!SDL_ਮਾਪ_ਜੋੜੋ_check_ਉਛਾਲ(sz_plane, sz_plane_chroma, &s1)) {
                ਵਾਪਸ SDL_ਸੈੱਟ_Error("Y + U would overflow");
            }
            ਜੇ (!SDL_ਮਾਪ_ਜੋੜੋ_check_ਉਛਾਲ(s1, sz_plane_chroma, &s2)) {
                ਵਾਪਸ SDL_ਸੈੱਟ_Error("Y + U + V would overflow");
            }
            *ਮਾਪ = (ਪੂਰਨ)s2;
        }
        ਰੋਕੋ;

    ਹਾਲਤ SDL_PIXELFORMAT_YUY2: /**< Packed mode: Y0+U0+Y1+V0 (1 plane) */
    ਹਾਲਤ SDL_PIXELFORMAT_UYVY: /**< Packed mode: U0+Y0+V0+Y1 (1 plane) */
    ਹਾਲਤ SDL_PIXELFORMAT_YVYU: /**< Packed mode: Y0+V0+Y1+U0 (1 plane) */

        ਜੇ (pitch) {
            /* pitch == ((w + 1) / 2) * 4; */
           size_t p1, p2;
           ਜੇ (!SDL_ਮਾਪ_ਜੋੜੋ_check_ਉਛਾਲ(w, 1, &p1)) {
               ਵਾਪਸ SDL_ਸੈੱਟ_Error("width + 1 would overflow");
           }
           p1 = p1 / 2;
           ਜੇ (!SDL_ਮਾਪ_mul_check_ਉਛਾਲ(p1, 4, &p2)) {
               ਵਾਪਸ SDL_ਸੈੱਟ_Error("width * 4 would overflow");
           }
           *pitch = p2;
        }

        ਜੇ (ਮਾਪ) {
            /* dst_size == 4 * sz_plane_packed; */
            size_t s1;
            ਜੇ (!SDL_ਮਾਪ_mul_check_ਉਛਾਲ(sz_plane_packed, 4, &s1)) {
                ਵਾਪਸ SDL_ਸੈੱਟ_Error("plane * 4 would overflow");
            }
            *ਮਾਪ = (ਪੂਰਨ) s1;
        }
        ਰੋਕੋ;

    ਹਾਲਤ SDL_PIXELFORMAT_NV12: /**< Planar mode: Y + U/V interleaved  (2 planes) */
    ਹਾਲਤ SDL_PIXELFORMAT_NV21: /**< Planar mode: Y + V/U interleaved  (2 planes) */
    ਹਾਲਤ SDL_PIXELFORMAT_P010: /**< Planar mode: Y + U/V interleaved, 10 bit  (2 planes) */
        ਜੇ (pitch) {
            *pitch = w * SDL_BYTESPERPIXEL(format);
        }

        ਜੇ (ਮਾਪ) {
            // dst_size == sz_plane + sz_plane_chroma + sz_plane_chroma;
            size_t s1, s2;
            ਜੇ (!SDL_ਮਾਪ_ਜੋੜੋ_check_ਉਛਾਲ(sz_plane, sz_plane_chroma, &s1)) {
                ਵਾਪਸ SDL_ਸੈੱਟ_Error("Y + U would overflow");
            }
            ਜੇ (!SDL_ਮਾਪ_ਜੋੜੋ_check_ਉਛਾਲ(s1, sz_plane_chroma, &s2)) {
                ਵਾਪਸ SDL_ਸੈੱਟ_Error("Y + U + V would overflow");
            }
            *ਮਾਪ = (ਪੂਰਨ) s2;
        }
        ਰੋਕੋ;

    ਮੂਲ:
        ਵਾਪਸ SDL_Unsupported();
    }

    ਵਾਪਸ true;
}

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_HAVE_YUV

ਸਥਿਰ bool GetYUVConversionType(SDL_Colorspace colorspace, ਪੂਰਨ w, ਪੂਰਨ h, ਪੂਰਨ ਬਿੱਟ_ਪ੍ਰਤੀ_pixel, YCbCrType *yuv_type)
{
    ਜੇ (SDL_ISCOLORSPACE_ਮੈਟ੍ਰਿਕਸ_BT601(colorspace)) {
        ਜੇ (SDL_ISCOLORSPACE_LIMITED_RANGE(colorspace)) {
            *yuv_type = YCBCR_601_LIMITED;
        } ਨਹੀਂਤਾਂ {
            *yuv_type = YCBCR_601_ਭਰਿਆ;
        }
        ਵਾਪਸ true;
    }

    ਜੇ (SDL_ISCOLORSPACE_ਮੈਟ੍ਰਿਕਸ_BT709(colorspace)) {
        ਜੇ (SDL_ISCOLORSPACE_LIMITED_RANGE(colorspace)) {
            *yuv_type = YCBCR_709_LIMITED;
        } ਨਹੀਂਤਾਂ {
            *yuv_type = YCBCR_709_ਭਰਿਆ;
        }
        ਵਾਪਸ true;
    }

    ਜੇ (SDL_ISCOLORSPACE_ਮੈਟ੍ਰਿਕਸ_BT2020_NCL(colorspace)) {
        ਜੇ (SDL_ISCOLORSPACE_ਭਰਿਆ_RANGE(colorspace)) {
            *yuv_type = YCBCR_2020_NCL_ਭਰਿਆ;
            ਵਾਪਸ true;
        }
    }

    ਜੇ (SDL_COLORSPACEMATRIX(colorspace) == SDL_ਮੈਟ੍ਰਿਕਸ_COEFFICIENTS_UNSPECIFIED) {
        ਚੋਣ (ਬਿੱਟ_ਪ੍ਰਤੀ_pixel) {
        ਹਾਲਤ 8:
            ਜੇ (h <= YUV_SD_ਹੱਦ) {
                ਜੇ (SDL_ISCOLORSPACE_LIMITED_RANGE(colorspace)) {
                    *yuv_type = YCBCR_601_LIMITED;
                } ਨਹੀਂਤਾਂ {
                    *yuv_type = YCBCR_601_ਭਰਿਆ;
                }
            } ਨਹੀਂਤਾਂ {
                ਜੇ (SDL_ISCOLORSPACE_LIMITED_RANGE(colorspace)) {
                    *yuv_type = YCBCR_709_LIMITED;
                } ਨਹੀਂਤਾਂ {
                    *yuv_type = YCBCR_709_ਭਰਿਆ;
                }
            }
			ਵਾਪਸ true;
        ਹਾਲਤ 10:
        ਹਾਲਤ 16:
            ਜੇ (SDL_ISCOLORSPACE_ਭਰਿਆ_RANGE(colorspace)) {
                *yuv_type = YCBCR_2020_NCL_ਭਰਿਆ;
                ਵਾਪਸ true;
            }
            ਰੋਕੋ;
        ਮੂਲ:
            ਰੋਕੋ;
        }
    }

    ਵਾਪਸ SDL_ਸੈੱਟ_Error("Unsupported YUV colorspace");
}

ਸਥਿਰ bool GetYUVPlanes(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, SDL_PixelFormat format, ਅਚਲ ਖਾਲੀ *yuv, ਪੂਰਨ yuv_pitch,
                         ਅਚਲ Uint8 **y, ਅਚਲ Uint8 **u, ਅਚਲ Uint8 **v, Uint32 *y_stride, Uint32 *uv_stride)
{
    ਅਚਲ Uint8 *planes[3] = { ਨਿਰਾ, ਨਿਰਾ, ਨਿਰਾ };
    ਪੂਰਨ pitches[3] = { 0, 0, 0 };
    ਪੂਰਨ uv_ਚੌੜਾਈ;

    ਚੋਣ (format) {
    ਹਾਲਤ SDL_PIXELFORMAT_YV12:
    ਹਾਲਤ SDL_PIXELFORMAT_IYUV:
    ਹਾਲਤ SDL_PIXELFORMAT_I0FL:
        pitches[0] = yuv_pitch;
        pitches[1] = ((pitches[0] / SDL_BYTESPERPIXEL(format) + 1) / 2) * SDL_BYTESPERPIXEL(format);
        pitches[2] = pitches[1];
        planes[0] = (ਅਚਲ Uint8 *)yuv;
        planes[1] = planes[0] + pitches[0] * ਉਚਾਈ;
        planes[2] = planes[1] + pitches[1] * ((ਉਚਾਈ + 1) / 2);
        ਰੋਕੋ;
    ਹਾਲਤ SDL_PIXELFORMAT_YUY2:
    ਹਾਲਤ SDL_PIXELFORMAT_UYVY:
    ਹਾਲਤ SDL_PIXELFORMAT_YVYU:
        pitches[0] = yuv_pitch;
        planes[0] = (ਅਚਲ Uint8 *)yuv;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_PIXELFORMAT_NV12:
    ਹਾਲਤ SDL_PIXELFORMAT_NV21:
        pitches[0] = yuv_pitch;
        pitches[1] = 2 * ((pitches[0] + 1) / 2);
        planes[0] = (ਅਚਲ Uint8 *)yuv;
        planes[1] = planes[0] + pitches[0] * ਉਚਾਈ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_PIXELFORMAT_P010:
        pitches[0] = yuv_pitch;
        uv_ਚੌੜਾਈ = ((ਚੌੜਾਈ + 1) / 2) * 2;
        pitches[1] = SDL_max(pitches[0], (ਪੂਰਨ)(uv_ਚੌੜਾਈ * ਆਕਾਰ(Uint16)));
        planes[0] = (ਅਚਲ Uint8 *)yuv;
        planes[1] = planes[0] + pitches[0] * ਉਚਾਈ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_PIXELFORMAT_I444:
    ਹਾਲਤ SDL_PIXELFORMAT_I4FL:
        pitches[0] = yuv_pitch;
        pitches[1] = pitches[0];
        pitches[2] = pitches[1];
        planes[0] = (ਅਚਲ Uint8 *)yuv;
        planes[1] = planes[0] + pitches[0] * ਉਚਾਈ;
        planes[2] = planes[1] + pitches[1] * ਉਚਾਈ;
        ਰੋਕੋ;
    ਮੂਲ:
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("GetYUVPlanes(): Unsupported YUV format: %s", SDL_GetPixelFormatName(format));
    }

    ਚੋਣ (format) {
    ਹਾਲਤ SDL_PIXELFORMAT_YV12:
        *y = planes[0];
        *y_stride = pitches[0];
        *v = planes[1];
        *u = planes[2];
        *uv_stride = pitches[1];
        ਰੋਕੋ;
    ਹਾਲਤ SDL_PIXELFORMAT_IYUV:
    ਹਾਲਤ SDL_PIXELFORMAT_I444:
    ਹਾਲਤ SDL_PIXELFORMAT_I0FL:
    ਹਾਲਤ SDL_PIXELFORMAT_I4FL:
        *y = planes[0];
        *y_stride = pitches[0];
        *v = planes[2];
        *u = planes[1];
        *uv_stride = pitches[1];
        ਰੋਕੋ;
    ਹਾਲਤ SDL_PIXELFORMAT_YUY2:
        *y = planes[0];
        *y_stride = pitches[0];
        *v = *y + 3;
        *u = *y + 1;
        *uv_stride = pitches[0];
        ਰੋਕੋ;
    ਹਾਲਤ SDL_PIXELFORMAT_UYVY:
        *y = planes[0] + 1;
        *y_stride = pitches[0];
        *v = *y + 1;
        *u = *y - 1;
        *uv_stride = pitches[0];
        ਰੋਕੋ;
    ਹਾਲਤ SDL_PIXELFORMAT_YVYU:
        *y = planes[0];
        *y_stride = pitches[0];
        *v = *y + 1;
        *u = *y + 3;
        *uv_stride = pitches[0];
        ਰੋਕੋ;
    ਹਾਲਤ SDL_PIXELFORMAT_NV12:
        *y = planes[0];
        *y_stride = pitches[0];
        *u = planes[1];
        *v = *u + 1;
        *uv_stride = pitches[1];
        ਰੋਕੋ;
    ਹਾਲਤ SDL_PIXELFORMAT_NV21:
        *y = planes[0];
        *y_stride = pitches[0];
        *v = planes[1];
        *u = *v + 1;
        *uv_stride = pitches[1];
        ਰੋਕੋ;
    ਹਾਲਤ SDL_PIXELFORMAT_P010:
        *y = planes[0];
        *y_stride = pitches[0];
        *u = planes[1];
        *v = *u + ਆਕਾਰ(Uint16);
        *uv_stride = pitches[1];
        ਰੋਕੋ;
    ਮੂਲ:
        // Should have caught this above
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("GetYUVPlanes[2]: Unsupported YUV format: %s", SDL_GetPixelFormatName(format));
    }
    ਵਾਪਸ true;
}

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_SSE2_INTRINSICS
ਸਥਿਰ bool SDL_TARGETING("sse2") yuv_rgb_sse(
    SDL_PixelFormat src_format, SDL_PixelFormat dst_format,
    Uint32 ਚੌੜਾਈ, Uint32 ਉਚਾਈ,
    ਅਚਲ Uint8 *y, ਅਚਲ Uint8 *u, ਅਚਲ Uint8 *v, Uint32 y_stride, Uint32 uv_stride,
    Uint8 *rgb, Uint32 rgb_stride,
    YCbCrType yuv_type)
{
    ਜੇ (!SDL_HasSSE2()) {
        ਵਾਪਸ false;
    }

    ਜੇ (src_format == SDL_PIXELFORMAT_YV12 ||
        src_format == SDL_PIXELFORMAT_IYUV) {

        ਚੋਣ (dst_format) {
        ਹਾਲਤ SDL_PIXELFORMAT_RGB565:
            yuv420_rgb565_sseu(ਚੌੜਾਈ, ਉਚਾਈ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ਵਾਪਸ true;
        ਹਾਲਤ SDL_PIXELFORMAT_RGB24:
            yuv420_rgb24_sseu(ਚੌੜਾਈ, ਉਚਾਈ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ਵਾਪਸ true;
        ਹਾਲਤ SDL_PIXELFORMAT_RGBX8888:
        ਹਾਲਤ SDL_PIXELFORMAT_RGBA8888:
            yuv420_rgba_sseu(ਚੌੜਾਈ, ਉਚਾਈ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ਵਾਪਸ true;
        ਹਾਲਤ SDL_PIXELFORMAT_BGRX8888:
        ਹਾਲਤ SDL_PIXELFORMAT_BGRA8888:
            yuv420_bgra_sseu(ਚੌੜਾਈ, ਉਚਾਈ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ਵਾਪਸ true;
        ਹਾਲਤ SDL_PIXELFORMAT_XRGB8888:
        ਹਾਲਤ SDL_PIXELFORMAT_ARGB8888:
            yuv420_argb_sseu(ਚੌੜਾਈ, ਉਚਾਈ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ਵਾਪਸ true;
        ਹਾਲਤ SDL_PIXELFORMAT_XBGR8888:
        ਹਾਲਤ SDL_PIXELFORMAT_ABGR8888:
            yuv420_abgr_sseu(ਚੌੜਾਈ, ਉਚਾਈ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ਵਾਪਸ true;
        ਮੂਲ:
            ਰੋਕੋ;
        }
    }

    ਜੇ (src_format == SDL_PIXELFORMAT_YUY2 ||
        src_format == SDL_PIXELFORMAT_UYVY ||
        src_format == SDL_PIXELFORMAT_YVYU) {

        ਚੋਣ (dst_format) {
        ਹਾਲਤ SDL_PIXELFORMAT_RGB565:
            yuv422_rgb565_sseu(ਚੌੜਾਈ, ਉਚਾਈ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ਵਾਪਸ true;
        ਹਾਲਤ SDL_PIXELFORMAT_RGB24:
            yuv422_rgb24_sseu(ਚੌੜਾਈ, ਉਚਾਈ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ਵਾਪਸ true;
        ਹਾਲਤ SDL_PIXELFORMAT_RGBX8888:
        ਹਾਲਤ SDL_PIXELFORMAT_RGBA8888:
            yuv422_rgba_sseu(ਚੌੜਾਈ, ਉਚਾਈ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ਵਾਪਸ true;
        ਹਾਲਤ SDL_PIXELFORMAT_BGRX8888:
        ਹਾਲਤ SDL_PIXELFORMAT_BGRA8888:
            yuv422_bgra_sseu(ਚੌੜਾਈ, ਉਚਾਈ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ਵਾਪਸ true;
        ਹਾਲਤ SDL_PIXELFORMAT_XRGB8888:
        ਹਾਲਤ SDL_PIXELFORMAT_ARGB8888:
            yuv422_argb_sseu(ਚੌੜਾਈ, ਉਚਾਈ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ਵਾਪਸ true;
        ਹਾਲਤ SDL_PIXELFORMAT_XBGR8888:
        ਹਾਲਤ SDL_PIXELFORMAT_ABGR8888:
            yuv422_abgr_sseu(ਚੌੜਾਈ, ਉਚਾਈ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ਵਾਪਸ true;
        ਮੂਲ:
            ਰੋਕੋ;
        }
    }

    ਜੇ (src_format == SDL_PIXELFORMAT_NV12 ||
        src_format == SDL_PIXELFORMAT_NV21) {

        ਚੋਣ (dst_format) {
        ਹਾਲਤ SDL_PIXELFORMAT_RGB565:
            yuvnv12_rgb565_sseu(ਚੌੜਾਈ, ਉਚਾਈ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ਵਾਪਸ true;
        ਹਾਲਤ SDL_PIXELFORMAT_RGB24:
            yuvnv12_rgb24_sseu(ਚੌੜਾਈ, ਉਚਾਈ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ਵਾਪਸ true;
        ਹਾਲਤ SDL_PIXELFORMAT_RGBX8888:
        ਹਾਲਤ SDL_PIXELFORMAT_RGBA8888:
            yuvnv12_rgba_sseu(ਚੌੜਾਈ, ਉਚਾਈ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ਵਾਪਸ true;
        ਹਾਲਤ SDL_PIXELFORMAT_BGRX8888:
        ਹਾਲਤ SDL_PIXELFORMAT_BGRA8888:
            yuvnv12_bgra_sseu(ਚੌੜਾਈ, ਉਚਾਈ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ਵਾਪਸ true;
        ਹਾਲਤ SDL_PIXELFORMAT_XRGB8888:
        ਹਾਲਤ SDL_PIXELFORMAT_ARGB8888:
            yuvnv12_argb_sseu(ਚੌੜਾਈ, ਉਚਾਈ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ਵਾਪਸ true;
        ਹਾਲਤ SDL_PIXELFORMAT_XBGR8888:
        ਹਾਲਤ SDL_PIXELFORMAT_ABGR8888:
            yuvnv12_abgr_sseu(ਚੌੜਾਈ, ਉਚਾਈ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ਵਾਪਸ true;
        ਮੂਲ:
            ਰੋਕੋ;
        }
    }
    ਵਾਪਸ false;
}
#ਨਹੀਂਤਾਂ
ਸਥਿਰ bool yuv_rgb_sse(
    SDL_PixelFormat src_format, SDL_PixelFormat dst_format,
    Uint32 ਚੌੜਾਈ, Uint32 ਉਚਾਈ,
    ਅਚਲ Uint8 *y, ਅਚਲ Uint8 *u, ਅਚਲ Uint8 *v, Uint32 y_stride, Uint32 uv_stride,
    Uint8 *rgb, Uint32 rgb_stride,
    YCbCrType yuv_type)
{
    ਵਾਪਸ false;
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_LSX_INTRINSICS
ਸਥਿਰ bool yuv_rgb_lsx(
    SDL_PixelFormat src_format, SDL_PixelFormat dst_format,
    Uint32 ਚੌੜਾਈ, Uint32 ਉਚਾਈ,
    ਅਚਲ Uint8 *y, ਅਚਲ Uint8 *u, ਅਚਲ Uint8 *v, Uint32 y_stride, Uint32 uv_stride,
    Uint8 *rgb, Uint32 rgb_stride,
    YCbCrType yuv_type)
{
    ਜੇ (!SDL_HasLSX()) {
        ਵਾਪਸ false;
    }
    ਜੇ (src_format == SDL_PIXELFORMAT_YV12 ||
        src_format == SDL_PIXELFORMAT_IYUV) {

        ਚੋਣ (dst_format) {
        ਹਾਲਤ SDL_PIXELFORMAT_RGB24:
            yuv420_rgb24_lsx(ਚੌੜਾਈ, ਉਚਾਈ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ਵਾਪਸ true;
        ਹਾਲਤ SDL_PIXELFORMAT_RGBX8888:
        ਹਾਲਤ SDL_PIXELFORMAT_RGBA8888:
            yuv420_rgba_lsx(ਚੌੜਾਈ, ਉਚਾਈ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ਵਾਪਸ true;
        ਹਾਲਤ SDL_PIXELFORMAT_BGRX8888:
        ਹਾਲਤ SDL_PIXELFORMAT_BGRA8888:
            yuv420_bgra_lsx(ਚੌੜਾਈ, ਉਚਾਈ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ਵਾਪਸ true;
        ਹਾਲਤ SDL_PIXELFORMAT_XRGB8888:
        ਹਾਲਤ SDL_PIXELFORMAT_ARGB8888:
            yuv420_argb_lsx(ਚੌੜਾਈ, ਉਚਾਈ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ਵਾਪਸ true;
        ਹਾਲਤ SDL_PIXELFORMAT_XBGR8888:
        ਹਾਲਤ SDL_PIXELFORMAT_ABGR8888:
            yuv420_abgr_lsx(ਚੌੜਾਈ, ਉਚਾਈ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ਵਾਪਸ true;
        ਮੂਲ:
            ਰੋਕੋ;
        }
    }
    ਵਾਪਸ false;
}
#ਨਹੀਂਤਾਂ
ਸਥਿਰ bool yuv_rgb_lsx(
    SDL_PixelFormat src_format, SDL_PixelFormat dst_format,
    Uint32 ਚੌੜਾਈ, Uint32 ਉਚਾਈ,
    ਅਚਲ Uint8 *y, ਅਚਲ Uint8 *u, ਅਚਲ Uint8 *v, Uint32 y_stride, Uint32 uv_stride,
    Uint8 *rgb, Uint32 rgb_stride,
    YCbCrType yuv_type)
{
    ਵਾਪਸ false;
}
#ਜੇ_ਅੰਤ

ਸਥਿਰ bool yuv_rgb_std(
    SDL_PixelFormat src_format, SDL_PixelFormat dst_format,
    Uint32 ਚੌੜਾਈ, Uint32 ਉਚਾਈ,
    ਅਚਲ Uint8 *y, ਅਚਲ Uint8 *u, ਅਚਲ Uint8 *v, Uint32 y_stride, Uint32 uv_stride,
    Uint8 *rgb, Uint32 rgb_stride,
    YCbCrType yuv_type)
{
    ਜੇ (src_format == SDL_PIXELFORMAT_YV12 ||
        src_format == SDL_PIXELFORMAT_IYUV) {

        ਚੋਣ (dst_format) {
        ਹਾਲਤ SDL_PIXELFORMAT_RGB565:
            yuv420_rgb565_std(ਚੌੜਾਈ, ਉਚਾਈ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ਵਾਪਸ true;
        ਹਾਲਤ SDL_PIXELFORMAT_RGB24:
            yuv420_rgb24_std(ਚੌੜਾਈ, ਉਚਾਈ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ਵਾਪਸ true;
        ਹਾਲਤ SDL_PIXELFORMAT_RGBX8888:
        ਹਾਲਤ SDL_PIXELFORMAT_RGBA8888:
            yuv420_rgba_std(ਚੌੜਾਈ, ਉਚਾਈ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ਵਾਪਸ true;
        ਹਾਲਤ SDL_PIXELFORMAT_BGRX8888:
        ਹਾਲਤ SDL_PIXELFORMAT_BGRA8888:
            yuv420_bgra_std(ਚੌੜਾਈ, ਉਚਾਈ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ਵਾਪਸ true;
        ਹਾਲਤ SDL_PIXELFORMAT_XRGB8888:
        ਹਾਲਤ SDL_PIXELFORMAT_ARGB8888:
            yuv420_argb_std(ਚੌੜਾਈ, ਉਚਾਈ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ਵਾਪਸ true;
        ਹਾਲਤ SDL_PIXELFORMAT_XBGR8888:
        ਹਾਲਤ SDL_PIXELFORMAT_ABGR8888:
            yuv420_abgr_std(ਚੌੜਾਈ, ਉਚਾਈ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ਵਾਪਸ true;
        ਮੂਲ:
            ਰੋਕੋ;
        }
    }

    ਜੇ (src_format == SDL_PIXELFORMAT_I444) {

        ਚੋਣ (dst_format) {
        ਹਾਲਤ SDL_PIXELFORMAT_RGBX8888:
        ਹਾਲਤ SDL_PIXELFORMAT_RGBA8888:
            yuv444_rgba_std(ਚੌੜਾਈ, ਉਚਾਈ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ਵਾਪਸ true;
        ਹਾਲਤ SDL_PIXELFORMAT_BGRX8888:
        ਹਾਲਤ SDL_PIXELFORMAT_BGRA8888:
            yuv444_bgra_std(ਚੌੜਾਈ, ਉਚਾਈ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ਵਾਪਸ true;
        ਹਾਲਤ SDL_PIXELFORMAT_XRGB8888:
        ਹਾਲਤ SDL_PIXELFORMAT_ARGB8888:
            yuv444_argb_std(ਚੌੜਾਈ, ਉਚਾਈ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ਵਾਪਸ true;
        ਹਾਲਤ SDL_PIXELFORMAT_XBGR8888:
        ਹਾਲਤ SDL_PIXELFORMAT_ABGR8888:
            yuv444_abgr_std(ਚੌੜਾਈ, ਉਚਾਈ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ਵਾਪਸ true;
        ਮੂਲ:
            ਰੋਕੋ;
        }
    }

    ਜੇ (src_format == SDL_PIXELFORMAT_YUY2 ||
        src_format == SDL_PIXELFORMAT_UYVY ||
        src_format == SDL_PIXELFORMAT_YVYU) {

        ਚੋਣ (dst_format) {
        ਹਾਲਤ SDL_PIXELFORMAT_RGB565:
            yuv422_rgb565_std(ਚੌੜਾਈ, ਉਚਾਈ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ਵਾਪਸ true;
        ਹਾਲਤ SDL_PIXELFORMAT_RGB24:
            yuv422_rgb24_std(ਚੌੜਾਈ, ਉਚਾਈ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ਵਾਪਸ true;
        ਹਾਲਤ SDL_PIXELFORMAT_RGBX8888:
        ਹਾਲਤ SDL_PIXELFORMAT_RGBA8888:
            yuv422_rgba_std(ਚੌੜਾਈ, ਉਚਾਈ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ਵਾਪਸ true;
        ਹਾਲਤ SDL_PIXELFORMAT_BGRX8888:
        ਹਾਲਤ SDL_PIXELFORMAT_BGRA8888:
            yuv422_bgra_std(ਚੌੜਾਈ, ਉਚਾਈ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ਵਾਪਸ true;
        ਹਾਲਤ SDL_PIXELFORMAT_XRGB8888:
        ਹਾਲਤ SDL_PIXELFORMAT_ARGB8888:
            yuv422_argb_std(ਚੌੜਾਈ, ਉਚਾਈ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ਵਾਪਸ true;
        ਹਾਲਤ SDL_PIXELFORMAT_XBGR8888:
        ਹਾਲਤ SDL_PIXELFORMAT_ABGR8888:
            yuv422_abgr_std(ਚੌੜਾਈ, ਉਚਾਈ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ਵਾਪਸ true;
        ਮੂਲ:
            ਰੋਕੋ;
        }
    }

    ਜੇ (src_format == SDL_PIXELFORMAT_NV12 ||
        src_format == SDL_PIXELFORMAT_NV21) {

        ਚੋਣ (dst_format) {
        ਹਾਲਤ SDL_PIXELFORMAT_RGB565:
            yuvnv12_rgb565_std(ਚੌੜਾਈ, ਉਚਾਈ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ਵਾਪਸ true;
        ਹਾਲਤ SDL_PIXELFORMAT_RGB24:
            yuvnv12_rgb24_std(ਚੌੜਾਈ, ਉਚਾਈ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ਵਾਪਸ true;
        ਹਾਲਤ SDL_PIXELFORMAT_RGBX8888:
        ਹਾਲਤ SDL_PIXELFORMAT_RGBA8888:
            yuvnv12_rgba_std(ਚੌੜਾਈ, ਉਚਾਈ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ਵਾਪਸ true;
        ਹਾਲਤ SDL_PIXELFORMAT_BGRX8888:
        ਹਾਲਤ SDL_PIXELFORMAT_BGRA8888:
            yuvnv12_bgra_std(ਚੌੜਾਈ, ਉਚਾਈ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ਵਾਪਸ true;
        ਹਾਲਤ SDL_PIXELFORMAT_XRGB8888:
        ਹਾਲਤ SDL_PIXELFORMAT_ARGB8888:
            yuvnv12_argb_std(ਚੌੜਾਈ, ਉਚਾਈ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ਵਾਪਸ true;
        ਹਾਲਤ SDL_PIXELFORMAT_XBGR8888:
        ਹਾਲਤ SDL_PIXELFORMAT_ABGR8888:
            yuvnv12_abgr_std(ਚੌੜਾਈ, ਉਚਾਈ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ਵਾਪਸ true;
        ਮੂਲ:
            ਰੋਕੋ;
        }
    }

    ਜੇ (src_format == SDL_PIXELFORMAT_P010) {
        ਚੋਣ (dst_format) {
        ਹਾਲਤ SDL_PIXELFORMAT_XBGR2101010:
            yuvp010_xbgr2101010_std(ਚੌੜਾਈ, ਉਚਾਈ, (ਅਚਲ uint16_t *)y, (ਅਚਲ uint16_t *)u, (ਅਚਲ uint16_t *)v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ਵਾਪਸ true;
        ਮੂਲ:
            ਰੋਕੋ;
        }
    }

    ਜੇ (src_format == SDL_PIXELFORMAT_I0FL) {
        ਚੋਣ (dst_format) {
        ਹਾਲਤ SDL_PIXELFORMAT_RGB48:
            yuvi0fl_rgb48_std(ਚੌੜਾਈ, ਉਚਾਈ, (ਅਚਲ uint16_t *)y, (ਅਚਲ uint16_t *)u, (ਅਚਲ uint16_t *)v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ਵਾਪਸ true;
        ਮੂਲ:
            ਰੋਕੋ;
        }
    }

    ਜੇ (src_format == SDL_PIXELFORMAT_I4FL) {
        ਚੋਣ (dst_format) {
        ਹਾਲਤ SDL_PIXELFORMAT_RGB48:
            yuvi4fl_rgb48_std(ਚੌੜਾਈ, ਉਚਾਈ, (ਅਚਲ uint16_t *)y, (ਅਚਲ uint16_t *)u, (ਅਚਲ uint16_t *)v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ਵਾਪਸ true;
        ਮੂਲ:
            ਰੋਕੋ;
        }
    }
    ਵਾਪਸ false;
}

bool SDL_Convert_Pixels_YUV_ਮੰਜ਼ਿਲ_RGB(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ,
                                  SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ਅਚਲ ਖਾਲੀ *src, ਪੂਰਨ src_pitch,
                                  SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, ਖਾਲੀ *dst, ਪੂਰਨ dst_pitch)
{
    ਅਚਲ Uint8 *y = ਨਿਰਾ;
    ਅਚਲ Uint8 *u = ਨਿਰਾ;
    ਅਚਲ Uint8 *v = ਨਿਰਾ;
    Uint32 y_stride = 0;
    Uint32 uv_stride = 0;
    YCbCrType yuv_type = YCBCR_601_LIMITED;

    ਜੇ (!GetYUVPlanes(ਚੌੜਾਈ, ਉਚਾਈ, src_format, src, src_pitch, &y, &u, &v, &y_stride, &uv_stride)) {
        ਵਾਪਸ false;
    }

    ਜੇ (!GetYUVConversionType(src_colorspace, ਚੌੜਾਈ, ਉਚਾਈ, 8, &yuv_type)) {
        ਵਾਪਸ false;
    }

    ਜੇ (yuv_rgb_sse(src_format, dst_format, ਚੌੜਾਈ, ਉਚਾਈ, y, u, v, y_stride, uv_stride, (Uint8 *)dst, dst_pitch, yuv_type)) {
        ਵਾਪਸ true;
    }

    ਜੇ (yuv_rgb_lsx(src_format, dst_format, ਚੌੜਾਈ, ਉਚਾਈ, y, u, v, y_stride, uv_stride, (Uint8 *)dst, dst_pitch, yuv_type)) {
        ਵਾਪਸ true;
    }

    ਜੇ (yuv_rgb_std(src_format, dst_format, ਚੌੜਾਈ, ਉਚਾਈ, y, u, v, y_stride, uv_stride, (Uint8 *)dst, dst_pitch, yuv_type)) {
        ਵਾਪਸ true;
    }

    // No fast path for the RGB format, instead convert using an intermediate buffer
    ਜੇ (src_format == SDL_PIXELFORMAT_P010 && dst_format != SDL_PIXELFORMAT_XBGR2101010) {
        bool ਨਤੀਜਾ;
        ਖਾਲੀ *tmp;
        ਪੂਰਨ tmp_pitch = (ਚੌੜਾਈ * ਆਕਾਰ(Uint32));

        tmp = SDL_malloc((size_t)tmp_pitch * ਉਚਾਈ);
        ਜੇ (!tmp) {
            ਵਾਪਸ false;
        }

        // convert src/src_format to tmp/XBGR2101010
        ਨਤੀਜਾ = SDL_Convert_Pixels_YUV_ਮੰਜ਼ਿਲ_RGB(ਚੌੜਾਈ, ਉਚਾਈ, src_format, src_colorspace, src_properties, src, src_pitch, SDL_PIXELFORMAT_XBGR2101010, src_colorspace, src_properties, tmp, tmp_pitch);
        ਜੇ (!ਨਤੀਜਾ) {
            SDL_free(tmp);
            ਵਾਪਸ false;
        }

        // convert tmp/XBGR2101010 to dst/RGB
        ਨਤੀਜਾ = SDL_ConvertPixelsAndColorspace(ਚੌੜਾਈ, ਉਚਾਈ, SDL_PIXELFORMAT_XBGR2101010, src_colorspace, src_properties, tmp, tmp_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
        SDL_free(tmp);
        ਵਾਪਸ ਨਤੀਜਾ;
    }

    ਜੇ ((src_format == SDL_PIXELFORMAT_I0FL || src_format == SDL_PIXELFORMAT_I4FL) && dst_format != SDL_PIXELFORMAT_RGB48) {
        bool ਨਤੀਜਾ;
        ਖਾਲੀ *tmp;
        ਪੂਰਨ tmp_pitch = (ਚੌੜਾਈ * 3 * ਆਕਾਰ(Uint16));

        tmp = SDL_malloc((size_t)tmp_pitch * ਉਚਾਈ);
        ਜੇ (!tmp) {
            ਵਾਪਸ false;
        }

        // convert src/src_format to tmp/RGB48
        ਨਤੀਜਾ = SDL_Convert_Pixels_YUV_ਮੰਜ਼ਿਲ_RGB(ਚੌੜਾਈ, ਉਚਾਈ, src_format, src_colorspace, src_properties, src, src_pitch, SDL_PIXELFORMAT_RGB48, src_colorspace, src_properties, tmp, tmp_pitch);
        ਜੇ (!ਨਤੀਜਾ) {
            SDL_free(tmp);
            ਵਾਪਸ false;
        }

        // convert tmp/RGB48 to dst/RGB
        ਨਤੀਜਾ = SDL_ConvertPixelsAndColorspace(ਚੌੜਾਈ, ਉਚਾਈ, SDL_PIXELFORMAT_RGB48, src_colorspace, src_properties, tmp, tmp_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
        SDL_free(tmp);
        ਵਾਪਸ ਨਤੀਜਾ;
    }

    ਜੇ (dst_format != SDL_PIXELFORMAT_ARGB8888) {
        bool ਨਤੀਜਾ;
        ਖਾਲੀ *tmp;
        ਪੂਰਨ tmp_pitch = (ਚੌੜਾਈ * ਆਕਾਰ(Uint32));

        tmp = SDL_malloc((size_t)tmp_pitch * ਉਚਾਈ);
        ਜੇ (!tmp) {
            ਵਾਪਸ false;
        }

        // convert src/src_format to tmp/ARGB8888
        ਨਤੀਜਾ = SDL_Convert_Pixels_YUV_ਮੰਜ਼ਿਲ_RGB(ਚੌੜਾਈ, ਉਚਾਈ, src_format, src_colorspace, src_properties, src, src_pitch, SDL_PIXELFORMAT_ARGB8888, SDL_COLORSPACE_SRGB, 0, tmp, tmp_pitch);
        ਜੇ (!ਨਤੀਜਾ) {
            SDL_free(tmp);
            ਵਾਪਸ false;
        }

        // convert tmp/ARGB8888 to dst/RGB
        ਨਤੀਜਾ = SDL_ConvertPixelsAndColorspace(ਚੌੜਾਈ, ਉਚਾਈ, SDL_PIXELFORMAT_ARGB8888, SDL_COLORSPACE_SRGB, 0, tmp, tmp_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
        SDL_free(tmp);
        ਵਾਪਸ ਨਤੀਜਾ;
    }

    ਵਾਪਸ SDL_ਸੈੱਟ_Error("Unsupported YUV conversion");
}

ਬਣਤਰ RGB2YUVFactors
{
    ਪੂਰਨ y_ਵਿੱਥ;
    ਦਸ਼ਮਲਵ y[3]; // Rfactor, Gfactor, Bfactor
    ਦਸ਼ਮਲਵ u[3]; // Rfactor, Gfactor, Bfactor
    ਦਸ਼ਮਲਵ v[3]; // Rfactor, Gfactor, Bfactor
};

ਸਥਿਰ ਬਣਤਰ RGB2YUVFactors RGB2YUVFactorTables[] = {
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

ਸਥਿਰ bool SDL_Convert_Pixels_XRGB8888_ਮੰਜ਼ਿਲ_YUV(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, ਅਚਲ ਖਾਲੀ *src, ਪੂਰਨ src_pitch, SDL_PixelFormat dst_format, ਖਾਲੀ *dst, ਪੂਰਨ dst_pitch, YCbCrType yuv_type)
{
    ਅਚਲ ਪੂਰਨ src_pitch_x_2 = src_pitch * 2;
    ਅਚਲ ਪੂਰਨ ਉਚਾਈ_half = ਉਚਾਈ / 2;
    ਅਚਲ ਪੂਰਨ ਉਚਾਈ_remainder = (ਉਚਾਈ & 0x1);
    ਅਚਲ ਪੂਰਨ ਚੌੜਾਈ_half = ਚੌੜਾਈ / 2;
    ਅਚਲ ਪੂਰਨ ਚੌੜਾਈ_remainder = (ਚੌੜਾਈ & 0x1);
    ਪੂਰਨ i, j;

    ਅਚਲ ਬਣਤਰ RGB2YUVFactors *cvt = &RGB2YUVFactorTables[yuv_type];

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAKE_Y(r, g, b) (Uint8)SDL_clamp(((ਪੂਰਨ)(cvt->y[0] * (r) + cvt->y[1] * (g) + cvt->y[2] * (b) + 0.5f) + cvt->y_ਵਿੱਥ), 0, 255)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAKE_U(r, g, b) (Uint8)SDL_clamp(((ਪੂਰਨ)(cvt->u[0] * (r) + cvt->u[1] * (g) + cvt->u[2] * (b) + 0.5f) + 128), 0, 255)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAKE_V(r, g, b) (Uint8)SDL_clamp(((ਪੂਰਨ)(cvt->v[0] * (r) + cvt->v[1] * (g) + cvt->v[2] * (b) + 0.5f) + 128), 0, 255)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ READ_2x2_PIXELS                                                                                     \
    ਅਚਲ Uint32 p1 = ((ਅਚਲ Uint32 *)curr_ਪੰਕਤੀ)[2 * i];                                                    \
    ਅਚਲ Uint32 p2 = ((ਅਚਲ Uint32 *)curr_ਪੰਕਤੀ)[2 * i + 1];                                                \
    ਅਚਲ Uint32 p3 = ((ਅਚਲ Uint32 *)ਅਗਲਾ_ਪੰਕਤੀ)[2 * i];                                                    \
    ਅਚਲ Uint32 p4 = ((ਅਚਲ Uint32 *)ਅਗਲਾ_ਪੰਕਤੀ)[2 * i + 1];                                                \
    ਅਚਲ Uint32 r = ((p1 & 0x00ff0000) + (p2 & 0x00ff0000) + (p3 & 0x00ff0000) + (p4 & 0x00ff0000)) >> 18; \
    ਅਚਲ Uint32 g = ((p1 & 0x0000ff00) + (p2 & 0x0000ff00) + (p3 & 0x0000ff00) + (p4 & 0x0000ff00)) >> 10; \
    ਅਚਲ Uint32 b = ((p1 & 0x000000ff) + (p2 & 0x000000ff) + (p3 & 0x000000ff) + (p4 & 0x000000ff)) >> 2

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ READ_2x1_PIXELS                                             \
    ਅਚਲ Uint32 p1 = ((ਅਚਲ Uint32 *)curr_ਪੰਕਤੀ)[2 * i];            \
    ਅਚਲ Uint32 p2 = ((ਅਚਲ Uint32 *)ਅਗਲਾ_ਪੰਕਤੀ)[2 * i];            \
    ਅਚਲ Uint32 r = ((p1 & 0x00ff0000) + (p2 & 0x00ff0000)) >> 17; \
    ਅਚਲ Uint32 g = ((p1 & 0x0000ff00) + (p2 & 0x0000ff00)) >> 9;  \
    ਅਚਲ Uint32 b = ((p1 & 0x000000ff) + (p2 & 0x000000ff)) >> 1

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ READ_1x2_PIXELS                                             \
    ਅਚਲ Uint32 p1 = ((ਅਚਲ Uint32 *)curr_ਪੰਕਤੀ)[2 * i];            \
    ਅਚਲ Uint32 p2 = ((ਅਚਲ Uint32 *)curr_ਪੰਕਤੀ)[2 * i + 1];        \
    ਅਚਲ Uint32 r = ((p1 & 0x00ff0000) + (p2 & 0x00ff0000)) >> 17; \
    ਅਚਲ Uint32 g = ((p1 & 0x0000ff00) + (p2 & 0x0000ff00)) >> 9;  \
    ਅਚਲ Uint32 b = ((p1 & 0x000000ff) + (p2 & 0x000000ff)) >> 1

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ READ_1x1_PIXEL                                  \
    ਅਚਲ Uint32 p = ((ਅਚਲ Uint32 *)curr_ਪੰਕਤੀ)[2 * i]; \
    ਅਚਲ Uint32 r = (p & 0x00ff0000) >> 16;            \
    ਅਚਲ Uint32 g = (p & 0x0000ff00) >> 8;             \
    ਅਚਲ Uint32 b = (p & 0x000000ff)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ READ_TWO_RGB_PIXELS                                  \
    ਅਚਲ Uint32 p = ((ਅਚਲ Uint32 *)curr_ਪੰਕਤੀ)[2 * i];      \
    ਅਚਲ Uint32 r = (p & 0x00ff0000) >> 16;                 \
    ਅਚਲ Uint32 g = (p & 0x0000ff00) >> 8;                  \
    ਅਚਲ Uint32 b = (p & 0x000000ff);                       \
    ਅਚਲ Uint32 p1 = ((ਅਚਲ Uint32 *)curr_ਪੰਕਤੀ)[2 * i + 1]; \
    ਅਚਲ Uint32 r1 = (p1 & 0x00ff0000) >> 16;               \
    ਅਚਲ Uint32 g1 = (p1 & 0x0000ff00) >> 8;                \
    ਅਚਲ Uint32 b1 = (p1 & 0x000000ff);                     \
    ਅਚਲ Uint32 R = (r + r1) / 2;                           \
    ਅਚਲ Uint32 G = (g + g1) / 2;                           \
    ਅਚਲ Uint32 B = (b + b1) / 2

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ READ_ONE_RGB_PIXEL READ_1x1_PIXEL

    ਚੋਣ (dst_format) {
    ਹਾਲਤ SDL_PIXELFORMAT_YV12:
    ਹਾਲਤ SDL_PIXELFORMAT_IYUV:
    ਹਾਲਤ SDL_PIXELFORMAT_I444:
    ਹਾਲਤ SDL_PIXELFORMAT_NV12:
    ਹਾਲਤ SDL_PIXELFORMAT_NV21:
    {
        ਅਚਲ Uint8 *curr_ਪੰਕਤੀ, *ਅਗਲਾ_ਪੰਕਤੀ;

        Uint8 *plane_y;
        Uint8 *plane_u;
        Uint8 *plane_v;
        Uint8 *plane_interleaved_uv;
        Uint32 y_stride, uv_stride, y_skip, uv_skip;

        ਜੇ (!GetYUVPlanes(ਚੌੜਾਈ, ਉਚਾਈ, dst_format, dst, dst_pitch,
                          (ਅਚਲ Uint8 **)&plane_y, (ਅਚਲ Uint8 **)&plane_u, (ਅਚਲ Uint8 **)&plane_v,
                          &y_stride, &uv_stride)) {
            ਵਾਪਸ false;
        }

        plane_interleaved_uv = (plane_y + ਉਚਾਈ * y_stride);
        y_skip = (y_stride - ਚੌੜਾਈ);

        curr_ਪੰਕਤੀ = (ਅਚਲ Uint8 *)src;

        // Write Y plane
        ਲਈ (j = 0; j < ਉਚਾਈ; j++) {
            ਲਈ (i = 0; i < ਚੌੜਾਈ; i++) {
                ਅਚਲ Uint32 p1 = ((ਅਚਲ Uint32 *)curr_ਪੰਕਤੀ)[i];
                ਅਚਲ Uint32 r = (p1 & 0x00ff0000) >> 16;
                ਅਚਲ Uint32 g = (p1 & 0x0000ff00) >> 8;
                ਅਚਲ Uint32 b = (p1 & 0x000000ff);
                *plane_y++ = MAKE_Y(r, g, b);
            }
            plane_y += y_skip;
            curr_ਪੰਕਤੀ += src_pitch;
        }

        curr_ਪੰਕਤੀ = (ਅਚਲ Uint8 *)src;
        ਅਗਲਾ_ਪੰਕਤੀ = (ਅਚਲ Uint8 *)src;
        ਅਗਲਾ_ਪੰਕਤੀ += src_pitch;

        ਜੇ (dst_format == SDL_PIXELFORMAT_YV12 || dst_format == SDL_PIXELFORMAT_IYUV) {
            // Write UV planes, not interleaved
            uv_skip = (uv_stride - (ਚੌੜਾਈ + 1) / 2);
            ਲਈ (j = 0; j < ਉਚਾਈ_half; j++) {
                ਲਈ (i = 0; i < ਚੌੜਾਈ_half; i++) {
                    READ_2x2_PIXELS;
                    *plane_u++ = MAKE_U(r, g, b);
                    *plane_v++ = MAKE_V(r, g, b);
                }
                ਜੇ (ਚੌੜਾਈ_remainder) {
                    READ_2x1_PIXELS;
                    *plane_u++ = MAKE_U(r, g, b);
                    *plane_v++ = MAKE_V(r, g, b);
                }
                plane_u += uv_skip;
                plane_v += uv_skip;
                curr_ਪੰਕਤੀ += src_pitch_x_2;
                ਅਗਲਾ_ਪੰਕਤੀ += src_pitch_x_2;
            }
            ਜੇ (ਉਚਾਈ_remainder) {
                ਲਈ (i = 0; i < ਚੌੜਾਈ_half; i++) {
                    READ_1x2_PIXELS;
                    *plane_u++ = MAKE_U(r, g, b);
                    *plane_v++ = MAKE_V(r, g, b);
                }
                ਜੇ (ਚੌੜਾਈ_remainder) {
                    READ_1x1_PIXEL;
                    *plane_u++ = MAKE_U(r, g, b);
                    *plane_v++ = MAKE_V(r, g, b);
                }
                plane_u += uv_skip;
                plane_v += uv_skip;
            }
        } ਨਹੀਂਤਾਂ ਜੇ (dst_format == SDL_PIXELFORMAT_I444) {
            // Write UV planes, not interleaved
            uv_skip = (uv_stride - ਚੌੜਾਈ);
            ਲਈ (j = 0; j < ਉਚਾਈ; j++) {
                ਲਈ (i = 0; i < ਚੌੜਾਈ; i++) {
                    ਅਚਲ Uint32 p1 = ((ਅਚਲ Uint32 *)curr_ਪੰਕਤੀ)[i];
                    ਅਚਲ Uint32 r = (p1 & 0x00ff0000) >> 16;
                    ਅਚਲ Uint32 g = (p1 & 0x0000ff00) >> 8;
                    ਅਚਲ Uint32 b = (p1 & 0x000000ff);
                    *plane_u++ = MAKE_U(r, g, b);
                    *plane_v++ = MAKE_V(r, g, b);
                }
                plane_u += uv_skip;
                plane_v += uv_skip;
                curr_ਪੰਕਤੀ += src_pitch;
            }
        } ਨਹੀਂਤਾਂ ਜੇ (dst_format == SDL_PIXELFORMAT_NV12) {
            uv_skip = (uv_stride - ((ਚੌੜਾਈ + 1) / 2) * 2);
            ਲਈ (j = 0; j < ਉਚਾਈ_half; j++) {
                ਲਈ (i = 0; i < ਚੌੜਾਈ_half; i++) {
                    READ_2x2_PIXELS;
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                }
                ਜੇ (ਚੌੜਾਈ_remainder) {
                    READ_2x1_PIXELS;
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                }
                plane_interleaved_uv += uv_skip;
                curr_ਪੰਕਤੀ += src_pitch_x_2;
                ਅਗਲਾ_ਪੰਕਤੀ += src_pitch_x_2;
            }
            ਜੇ (ਉਚਾਈ_remainder) {
                ਲਈ (i = 0; i < ਚੌੜਾਈ_half; i++) {
                    READ_1x2_PIXELS;
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                }
                ਜੇ (ਚੌੜਾਈ_remainder) {
                    READ_1x1_PIXEL;
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                }
            }
        } ਨਹੀਂਤਾਂ /* dst_format == SDL_PIXELFORMAT_NV21 */ {
            uv_skip = (uv_stride - ((ਚੌੜਾਈ + 1) / 2) * 2);
            ਲਈ (j = 0; j < ਉਚਾਈ_half; j++) {
                ਲਈ (i = 0; i < ਚੌੜਾਈ_half; i++) {
                    READ_2x2_PIXELS;
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                }
                ਜੇ (ਚੌੜਾਈ_remainder) {
                    READ_2x1_PIXELS;
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                }
                plane_interleaved_uv += uv_skip;
                curr_ਪੰਕਤੀ += src_pitch_x_2;
                ਅਗਲਾ_ਪੰਕਤੀ += src_pitch_x_2;
            }
            ਜੇ (ਉਚਾਈ_remainder) {
                ਲਈ (i = 0; i < ਚੌੜਾਈ_half; i++) {
                    READ_1x2_PIXELS;
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                }
                ਜੇ (ਚੌੜਾਈ_remainder) {
                    READ_1x1_PIXEL;
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                }
            }
        }
    } ਰੋਕੋ;

    ਹਾਲਤ SDL_PIXELFORMAT_YUY2:
    ਹਾਲਤ SDL_PIXELFORMAT_UYVY:
    ਹਾਲਤ SDL_PIXELFORMAT_YVYU:
    {
        ਅਚਲ Uint8 *curr_ਪੰਕਤੀ = (ਅਚਲ Uint8 *)src;
        Uint8 *plane = (Uint8 *)dst;
        ਅਚਲ ਪੂਰਨ ਪੰਕਤੀ_ਮਾਪ = (4 * ((ਚੌੜਾਈ + 1) / 2));
        ਪੂਰਨ plane_skip;

        ਜੇ (dst_pitch < ਪੰਕਤੀ_ਮਾਪ) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("Destination pitch is too small, expected at least %d", ਪੰਕਤੀ_ਮਾਪ);
        }
        plane_skip = (dst_pitch - ਪੰਕਤੀ_ਮਾਪ);

        // Write YUV plane, packed
        ਜੇ (dst_format == SDL_PIXELFORMAT_YUY2) {
            ਲਈ (j = 0; j < ਉਚਾਈ; j++) {
                ਲਈ (i = 0; i < ਚੌੜਾਈ_half; i++) {
                    READ_TWO_RGB_PIXELS;
                    // Y U Y1 V
                    *plane++ = MAKE_Y(r, g, b);
                    *plane++ = MAKE_U(R, G, B);
                    *plane++ = MAKE_Y(r1, g1, b1);
                    *plane++ = MAKE_V(R, G, B);
                }
                ਜੇ (ਚੌੜਾਈ_remainder) {
                    READ_ONE_RGB_PIXEL;
                    // Y U Y V
                    *plane++ = MAKE_Y(r, g, b);
                    *plane++ = MAKE_U(r, g, b);
                    *plane++ = MAKE_Y(r, g, b);
                    *plane++ = MAKE_V(r, g, b);
                }
                plane += plane_skip;
                curr_ਪੰਕਤੀ += src_pitch;
            }
        } ਨਹੀਂਤਾਂ ਜੇ (dst_format == SDL_PIXELFORMAT_UYVY) {
            ਲਈ (j = 0; j < ਉਚਾਈ; j++) {
                ਲਈ (i = 0; i < ਚੌੜਾਈ_half; i++) {
                    READ_TWO_RGB_PIXELS;
                    // U Y V Y1
                    *plane++ = MAKE_U(R, G, B);
                    *plane++ = MAKE_Y(r, g, b);
                    *plane++ = MAKE_V(R, G, B);
                    *plane++ = MAKE_Y(r1, g1, b1);
                }
                ਜੇ (ਚੌੜਾਈ_remainder) {
                    READ_ONE_RGB_PIXEL;
                    // U Y V Y
                    *plane++ = MAKE_U(r, g, b);
                    *plane++ = MAKE_Y(r, g, b);
                    *plane++ = MAKE_V(r, g, b);
                    *plane++ = MAKE_Y(r, g, b);
                }
                plane += plane_skip;
                curr_ਪੰਕਤੀ += src_pitch;
            }
        } ਨਹੀਂਤਾਂ ਜੇ (dst_format == SDL_PIXELFORMAT_YVYU) {
            ਲਈ (j = 0; j < ਉਚਾਈ; j++) {
                ਲਈ (i = 0; i < ਚੌੜਾਈ_half; i++) {
                    READ_TWO_RGB_PIXELS;
                    // Y V Y1 U
                    *plane++ = MAKE_Y(r, g, b);
                    *plane++ = MAKE_V(R, G, B);
                    *plane++ = MAKE_Y(r1, g1, b1);
                    *plane++ = MAKE_U(R, G, B);
                }
                ਜੇ (ਚੌੜਾਈ_remainder) {
                    READ_ONE_RGB_PIXEL;
                    // Y V Y U
                    *plane++ = MAKE_Y(r, g, b);
                    *plane++ = MAKE_V(r, g, b);
                    *plane++ = MAKE_Y(r, g, b);
                    *plane++ = MAKE_U(r, g, b);
                }
                plane += plane_skip;
                curr_ਪੰਕਤੀ += src_pitch;
            }
        }
    } ਰੋਕੋ;

    ਮੂਲ:
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Unsupported YUV destination format: %s", SDL_GetPixelFormatName(dst_format));
    }
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ MAKE_Y
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ MAKE_U
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ MAKE_V
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ READ_2x2_PIXELS
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ READ_2x1_PIXELS
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ READ_1x2_PIXELS
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ READ_1x1_PIXEL
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ READ_TWO_RGB_PIXELS
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ READ_ONE_RGB_PIXEL
    ਵਾਪਸ true;
}

ਸਥਿਰ bool SDL_Convert_Pixels_XBGR2101010_ਮੰਜ਼ਿਲ_P010(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, ਅਚਲ ਖਾਲੀ *src, ਪੂਰਨ src_pitch, SDL_PixelFormat dst_format, ਖਾਲੀ *dst, ਪੂਰਨ dst_pitch, YCbCrType yuv_type)
{
    ਅਚਲ ਪੂਰਨ src_pitch_x_2 = src_pitch * 2;
    ਅਚਲ ਪੂਰਨ ਉਚਾਈ_half = ਉਚਾਈ / 2;
    ਅਚਲ ਪੂਰਨ ਉਚਾਈ_remainder = (ਉਚਾਈ & 0x1);
    ਅਚਲ ਪੂਰਨ ਚੌੜਾਈ_half = ਚੌੜਾਈ / 2;
    ਅਚਲ ਪੂਰਨ ਚੌੜਾਈ_remainder = (ਚੌੜਾਈ & 0x1);
    ਪੂਰਨ i, j;

    ਅਚਲ ਬਣਤਰ RGB2YUVFactors *cvt = &RGB2YUVFactorTables[yuv_type];

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAKE_Y(r, g, b) (Uint16)(((ਪੂਰਨ)(cvt->y[0] * (r) + cvt->y[1] * (g) + cvt->y[2] * (b) + 0.5f) + cvt->y_ਵਿੱਥ) << 6)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAKE_U(r, g, b) (Uint16)(((ਪੂਰਨ)(cvt->u[0] * (r) + cvt->u[1] * (g) + cvt->u[2] * (b) + 0.5f) + 512) << 6)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAKE_V(r, g, b) (Uint16)(((ਪੂਰਨ)(cvt->v[0] * (r) + cvt->v[1] * (g) + cvt->v[2] * (b) + 0.5f) + 512) << 6)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ READ_2x2_PIXELS                                                                                     \
    ਅਚਲ Uint32 p1 = ((ਅਚਲ Uint32 *)curr_ਪੰਕਤੀ)[2 * i];                                                    \
    ਅਚਲ Uint32 p2 = ((ਅਚਲ Uint32 *)curr_ਪੰਕਤੀ)[2 * i + 1];                                                \
    ਅਚਲ Uint32 p3 = ((ਅਚਲ Uint32 *)ਅਗਲਾ_ਪੰਕਤੀ)[2 * i];                                                    \
    ਅਚਲ Uint32 p4 = ((ਅਚਲ Uint32 *)ਅਗਲਾ_ਪੰਕਤੀ)[2 * i + 1];                                                \
    ਅਚਲ Uint32 r = ((p1 & 0x000003ff) + (p2 & 0x000003ff) + (p3 & 0x000003ff) + (p4 & 0x000003ff)) >> 2;  \
    ਅਚਲ Uint32 g = ((p1 & 0x000ffc00) + (p2 & 0x000ffc00) + (p3 & 0x000ffc00) + (p4 & 0x000ffc00)) >> 12; \
    ਅਚਲ Uint32 b = ((p1 & 0x3ff00000) + (p2 & 0x3ff00000) + (p3 & 0x3ff00000) + (p4 & 0x3ff00000)) >> 22

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ READ_2x1_PIXELS                                             \
    ਅਚਲ Uint32 p1 = ((ਅਚਲ Uint32 *)curr_ਪੰਕਤੀ)[2 * i];            \
    ਅਚਲ Uint32 p2 = ((ਅਚਲ Uint32 *)ਅਗਲਾ_ਪੰਕਤੀ)[2 * i];            \
    ਅਚਲ Uint32 r = ((p1 & 0x000003ff) + (p2 & 0x000003ff)) >> 1;  \
    ਅਚਲ Uint32 g = ((p1 & 0x000ffc00) + (p2 & 0x000ffc00)) >> 11; \
    ਅਚਲ Uint32 b = ((p1 & 0x3ff00000) + (p2 & 0x3ff00000)) >> 21

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ READ_1x2_PIXELS                                             \
    ਅਚਲ Uint32 p1 = ((ਅਚਲ Uint32 *)curr_ਪੰਕਤੀ)[2 * i];            \
    ਅਚਲ Uint32 p2 = ((ਅਚਲ Uint32 *)curr_ਪੰਕਤੀ)[2 * i + 1];        \
    ਅਚਲ Uint32 r = ((p1 & 0x000003ff) + (p2 & 0x000003ff)) >> 1;  \
    ਅਚਲ Uint32 g = ((p1 & 0x000ffc00) + (p2 & 0x000ffc00)) >> 11; \
    ਅਚਲ Uint32 b = ((p1 & 0x3ff00000) + (p2 & 0x3ff00000)) >> 21

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ READ_1x1_PIXEL                                  \
    ਅਚਲ Uint32 p = ((ਅਚਲ Uint32 *)curr_ਪੰਕਤੀ)[2 * i]; \
    ਅਚਲ Uint32 r = (p & 0x000003ff);                  \
    ਅਚਲ Uint32 g = (p & 0x000ffc00) >> 10;            \
    ਅਚਲ Uint32 b = (p & 0x3ff00000) >> 20

    ਅਚਲ Uint8 *curr_ਪੰਕਤੀ, *ਅਗਲਾ_ਪੰਕਤੀ;

    Uint16 *plane_y;
    Uint16 *plane_u;
    Uint16 *plane_v;
    Uint16 *plane_interleaved_uv;
    Uint32 y_stride, uv_stride, y_skip, uv_skip;

    ਜੇ (!GetYUVPlanes(ਚੌੜਾਈ, ਉਚਾਈ, dst_format, dst, dst_pitch,
                      (ਅਚਲ Uint8 **)&plane_y, (ਅਚਲ Uint8 **)&plane_u, (ਅਚਲ Uint8 **)&plane_v,
                      &y_stride, &uv_stride)) {
        ਵਾਪਸ false;
    }

    y_stride /= ਆਕਾਰ(Uint16);
    uv_stride /= ਆਕਾਰ(Uint16);

    plane_interleaved_uv = (plane_y + ਉਚਾਈ * y_stride);
    y_skip = (y_stride - ਚੌੜਾਈ);

    curr_ਪੰਕਤੀ = (ਅਚਲ Uint8 *)src;

    // Write Y plane
    ਲਈ (j = 0; j < ਉਚਾਈ; j++) {
        ਲਈ (i = 0; i < ਚੌੜਾਈ; i++) {
            ਅਚਲ Uint32 p1 = ((ਅਚਲ Uint32 *)curr_ਪੰਕਤੀ)[i];
            ਅਚਲ Uint32 r = (p1 >>  0) & 0x03ff;
            ਅਚਲ Uint32 g = (p1 >> 10) & 0x03ff;
            ਅਚਲ Uint32 b = (p1 >> 20) & 0x03ff;
            *plane_y++ = MAKE_Y(r, g, b);
        }
        plane_y += y_skip;
        curr_ਪੰਕਤੀ += src_pitch;
    }

    curr_ਪੰਕਤੀ = (ਅਚਲ Uint8 *)src;
    ਅਗਲਾ_ਪੰਕਤੀ = (ਅਚਲ Uint8 *)src;
    ਅਗਲਾ_ਪੰਕਤੀ += src_pitch;

    uv_skip = (uv_stride - ((ਚੌੜਾਈ + 1) / 2) * 2);
    ਲਈ (j = 0; j < ਉਚਾਈ_half; j++) {
        ਲਈ (i = 0; i < ਚੌੜਾਈ_half; i++) {
            READ_2x2_PIXELS;
            *plane_interleaved_uv++ = MAKE_U(r, g, b);
            *plane_interleaved_uv++ = MAKE_V(r, g, b);
        }
        ਜੇ (ਚੌੜਾਈ_remainder) {
            READ_2x1_PIXELS;
            *plane_interleaved_uv++ = MAKE_U(r, g, b);
            *plane_interleaved_uv++ = MAKE_V(r, g, b);
        }
        plane_interleaved_uv += uv_skip;
        curr_ਪੰਕਤੀ += src_pitch_x_2;
        ਅਗਲਾ_ਪੰਕਤੀ += src_pitch_x_2;
    }
    ਜੇ (ਉਚਾਈ_remainder) {
        ਲਈ (i = 0; i < ਚੌੜਾਈ_half; i++) {
            READ_1x2_PIXELS;
            *plane_interleaved_uv++ = MAKE_U(r, g, b);
            *plane_interleaved_uv++ = MAKE_V(r, g, b);
        }
        ਜੇ (ਚੌੜਾਈ_remainder) {
            READ_1x1_PIXEL;
            *plane_interleaved_uv++ = MAKE_U(r, g, b);
            *plane_interleaved_uv++ = MAKE_V(r, g, b);
        }
    }

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ MAKE_Y
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ MAKE_U
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ MAKE_V
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ READ_2x2_PIXELS
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ READ_2x1_PIXELS
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ READ_1x2_PIXELS
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ READ_1x1_PIXEL
    ਵਾਪਸ true;
}

bool SDL_Convert_Pixels_RGB_ਮੰਜ਼ਿਲ_YUV(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ,
                                  SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ਅਚਲ ਖਾਲੀ *src, ਪੂਰਨ src_pitch,
                                  SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, ਖਾਲੀ *dst, ਪੂਰਨ dst_pitch)
{
    YCbCrType yuv_type = YCBCR_601_LIMITED;

    ਜੇ (!GetYUVConversionType(dst_colorspace, ਚੌੜਾਈ, ਉਚਾਈ, 8, &yuv_type)) {
        ਵਾਪਸ false;
    }

#ਜੇ 0 // Doesn't handle odd widths
    // RGB24 to FOURCC
    ਜੇ (src_format == SDL_PIXELFORMAT_RGB24) {
        Uint8 *y;
        Uint8 *u;
        Uint8 *v;
        Uint32 y_stride;
        Uint32 uv_stride;

        ਜੇ (GetYUVPlanes(ਚੌੜਾਈ, ਉਚਾਈ, dst_format, dst, dst_pitch, (ਅਚਲ Uint8 **)&y, (ਅਚਲ Uint8 **)&u, (ਅਚਲ Uint8 **)&v, &y_stride, &uv_stride) < 0) {
            ਵਾਪਸ false;
        }

        rgb24_yuv420_std(ਚੌੜਾਈ, ਉਚਾਈ, src, src_pitch, y, u, v, y_stride, uv_stride, yuv_type);
        ਵਾਪਸ true;
    }
#ਜੇ_ਅੰਤ

    // ARGB8888 to FOURCC
    ਜੇ (src_format == SDL_PIXELFORMAT_ARGB8888 || src_format == SDL_PIXELFORMAT_XRGB8888) {
        ਵਾਪਸ SDL_Convert_Pixels_XRGB8888_ਮੰਜ਼ਿਲ_YUV(ਚੌੜਾਈ, ਉਚਾਈ, src, src_pitch, dst_format, dst, dst_pitch, yuv_type);
    }

    ਜੇ (dst_format == SDL_PIXELFORMAT_P010) {
        ਜੇ (src_format == SDL_PIXELFORMAT_XBGR2101010) {
            ਵਾਪਸ SDL_Convert_Pixels_XBGR2101010_ਮੰਜ਼ਿਲ_P010(ਚੌੜਾਈ, ਉਚਾਈ, src, src_pitch, dst_format, dst, dst_pitch, yuv_type);
        }

        // We currently only support converting from XBGR2101010 to P010
        bool ਨਤੀਜਾ;
        ਖਾਲੀ *tmp;
        ਪੂਰਨ tmp_pitch = (ਚੌੜਾਈ * ਆਕਾਰ(Uint32));

        tmp = SDL_malloc((size_t)tmp_pitch * ਉਚਾਈ);
        ਜੇ (!tmp) {
            ਵਾਪਸ false;
        }

        // convert src/src_format to tmp/XBGR2101010
        ਨਤੀਜਾ = SDL_ConvertPixelsAndColorspace(ਚੌੜਾਈ, ਉਚਾਈ, src_format, src_colorspace, src_properties, src, src_pitch, SDL_PIXELFORMAT_XBGR2101010, dst_colorspace, dst_properties, tmp, tmp_pitch);
        ਜੇ (!ਨਤੀਜਾ) {
            SDL_free(tmp);
            ਵਾਪਸ false;
        }

        // convert tmp/XBGR2101010 to dst/P010
        ਨਤੀਜਾ = SDL_Convert_Pixels_XBGR2101010_ਮੰਜ਼ਿਲ_P010(ਚੌੜਾਈ, ਉਚਾਈ, tmp, tmp_pitch, dst_format, dst, dst_pitch, yuv_type);
        SDL_free(tmp);
        ਵਾਪਸ ਨਤੀਜਾ;
    }

    // not ARGB8888 to FOURCC : need an intermediate conversion
    {
        bool ਨਤੀਜਾ;
        ਖਾਲੀ *tmp;
        ਪੂਰਨ tmp_pitch = (ਚੌੜਾਈ * ਆਕਾਰ(Uint32));

        tmp = SDL_malloc((size_t)tmp_pitch * ਉਚਾਈ);
        ਜੇ (!tmp) {
            ਵਾਪਸ false;
        }

        // convert src/src_format to tmp/XRGB8888
        ਨਤੀਜਾ = SDL_ConvertPixelsAndColorspace(ਚੌੜਾਈ, ਉਚਾਈ, src_format, src_colorspace, src_properties, src, src_pitch, SDL_PIXELFORMAT_XRGB8888, SDL_COLORSPACE_SRGB, 0, tmp, tmp_pitch);
        ਜੇ (!ਨਤੀਜਾ) {
            SDL_free(tmp);
            ਵਾਪਸ false;
        }

        // convert tmp/XRGB8888 to dst/FOURCC
        ਨਤੀਜਾ = SDL_Convert_Pixels_XRGB8888_ਮੰਜ਼ਿਲ_YUV(ਚੌੜਾਈ, ਉਚਾਈ, tmp, tmp_pitch, dst_format, dst, dst_pitch, yuv_type);
        SDL_free(tmp);
        ਵਾਪਸ ਨਤੀਜਾ;
    }
}

ਸਥਿਰ bool SDL_Convert_Pixels_YUV_ਮੰਜ਼ਿਲ_YUV_Copy(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, SDL_PixelFormat format, ਅਚਲ ਖਾਲੀ *src, ਪੂਰਨ src_pitch, ਖਾਲੀ *dst, ਪੂਰਨ dst_pitch)
{
    ਪੂਰਨ i;

    ਜੇ (IsPlanar1x1Format(format)) {
        // YUV planes
        ਅਚਲ size_t ਲੰਮਾਈ = ਚੌੜਾਈ * SDL_BYTESPERPIXEL(format);
        ਲਈ (i = ਉਚਾਈ * 3; i--;) {
            SDL_memcpy(dst, src, ਲੰਮਾਈ);
            src = (ਅਚਲ Uint8 *)src + src_pitch;
            dst = (Uint8 *)dst + dst_pitch;
        }
        ਵਾਪਸ true;
    }

    ਜੇ (IsPlanar2x2Format(format)) {
        ਅਚਲ ਪੂਰਨ bpp = SDL_BYTESPERPIXEL(format);

        // Y plane
        ਅਚਲ size_t ਲੰਮਾਈ = ਚੌੜਾਈ * bpp;
        ਲਈ (i = ਉਚਾਈ; i--;) {
            SDL_memcpy(dst, src, ਲੰਮਾਈ);
            src = (ਅਚਲ Uint8 *)src + src_pitch;
            dst = (Uint8 *)dst + dst_pitch;
        }

        ਜੇ (format == SDL_PIXELFORMAT_YV12 ||
            format == SDL_PIXELFORMAT_IYUV ||
            format == SDL_PIXELFORMAT_I0FL) {
            // U and V planes are a quarter the size of the Y plane, rounded up
            ਚੌੜਾਈ = ((ਚੌੜਾਈ + 1) / 2) * bpp;
            ਉਚਾਈ = (ਉਚਾਈ + 1) / 2;
            src_pitch = ((src_pitch / bpp + 1) / 2) * bpp;
            dst_pitch = ((dst_pitch / bpp + 1) / 2) * bpp;
            ਲਈ (i = ਉਚਾਈ * 2; i--;) {
                SDL_memcpy(dst, src, ਚੌੜਾਈ);
                src = (ਅਚਲ Uint8 *)src + src_pitch;
                dst = (Uint8 *)dst + dst_pitch;
            }
        } ਨਹੀਂਤਾਂ ਜੇ (format == SDL_PIXELFORMAT_NV12 ||
                   format == SDL_PIXELFORMAT_NV21 ||
                   format == SDL_PIXELFORMAT_P010) {
            // U/V plane is half the height of the Y plane, rounded up, with packed CrCb
            ਚੌੜਾਈ = ((ਚੌੜਾਈ + 1) / 2) * 2 * bpp;
            ਉਚਾਈ = (ਉਚਾਈ + 1) / 2;
            src_pitch = ((src_pitch / bpp + 1) / 2) * 2 * bpp;
            dst_pitch = ((dst_pitch / bpp + 1) / 2) * 2 * bpp;
            ਲਈ (i = ਉਚਾਈ; i--;) {
                SDL_memcpy(dst, src, ਚੌੜਾਈ);
                src = (ਅਚਲ Uint8 *)src + src_pitch;
                dst = (Uint8 *)dst + dst_pitch;
            }
        }
        ਵਾਪਸ true;
    }

    ਜੇ (IsPacked4Format(format)) {
        // Packed planes
        ਚੌੜਾਈ = 4 * ((ਚੌੜਾਈ + 1) / 2);
        ਲਈ (i = ਉਚਾਈ; i--;) {
            SDL_memcpy(dst, src, ਚੌੜਾਈ);
            src = (ਅਚਲ Uint8 *)src + src_pitch;
            dst = (Uint8 *)dst + dst_pitch;
        }
        ਵਾਪਸ true;
    }

    ਵਾਪਸ SDL_ਸੈੱਟ_Error("SDL_ConvertPixels_YUV_to_YUV_Copy: Unsupported YUV format: %s", SDL_GetPixelFormatName(format));
}

ਸਥਿਰ bool SDL_Convert_Pixels_ਅਦਲਾ_ਬਦਲੀ_UVPlanes(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, ਅਚਲ ਖਾਲੀ *src, ਪੂਰਨ src_pitch, ਖਾਲੀ *dst, ਪੂਰਨ dst_pitch)
{
    ਪੂਰਨ y;
    ਅਚਲ ਪੂਰਨ UVwidth = (ਚੌੜਾਈ + 1) / 2;
    ਅਚਲ ਪੂਰਨ UVheight = (ਉਚਾਈ + 1) / 2;

    // Skip the Y plane
    src = (ਅਚਲ Uint8 *)src + ਉਚਾਈ * src_pitch;
    dst = (Uint8 *)dst + ਉਚਾਈ * dst_pitch;

    ਜੇ (src == dst) {
        ਪੂਰਨ UVpitch = (dst_pitch + 1) / 2;
        Uint8 *tmp;
        Uint8 *row1 = (Uint8 *)dst;
        Uint8 *row2 = row1 + UVheight * UVpitch;

        // Allocate a temporary row for the swap
        tmp = (Uint8 *)SDL_malloc(UVwidth);
        ਜੇ (!tmp) {
            ਵਾਪਸ false;
        }
        ਲਈ (y = 0; y < UVheight; ++y) {
            SDL_memcpy(tmp, row1, UVwidth);
            SDL_memcpy(row1, row2, UVwidth);
            SDL_memcpy(row2, tmp, UVwidth);
            row1 += UVpitch;
            row2 += UVpitch;
        }
        SDL_free(tmp);
    } ਨਹੀਂਤਾਂ {
        ਅਚਲ Uint8 *srcUV;
        Uint8 *dstUV;
        ਪੂਰਨ srcUVPitch = ((src_pitch + 1) / 2);
        ਪੂਰਨ dstUVPitch = ((dst_pitch + 1) / 2);

        // Copy the first plane
        srcUV = (ਅਚਲ Uint8 *)src;
        dstUV = (Uint8 *)dst + UVheight * dstUVPitch;
        ਲਈ (y = 0; y < UVheight; ++y) {
            SDL_memcpy(dstUV, srcUV, UVwidth);
            srcUV += srcUVPitch;
            dstUV += dstUVPitch;
        }

        // Copy the second plane
        dstUV = (Uint8 *)dst;
        ਲਈ (y = 0; y < UVheight; ++y) {
            SDL_memcpy(dstUV, srcUV, UVwidth);
            srcUV += srcUVPitch;
            dstUV += dstUVPitch;
        }
    }
    ਵਾਪਸ true;
}

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_SSE2_INTRINSICS
ਸਥਿਰ bool SDL_TARGETING("sse2") SDL_Convert_Pixels_Pack_UVPlanes_ਮੰਜ਼ਿਲ_NV_SSE2(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, ਅਚਲ ਖਾਲੀ *src, ਪੂਰਨ src_pitch, ਖਾਲੀ *dst, ਪੂਰਨ dst_pitch, bool ਉਲਟ_UV)
{
    ਪੂਰਨ x, y;
    ਅਚਲ ਪੂਰਨ UVwidth = (ਚੌੜਾਈ + 1) / 2;
    ਅਚਲ ਪੂਰਨ UVheight = (ਉਚਾਈ + 1) / 2;
    ਅਚਲ ਪੂਰਨ srcUVPitch = ((src_pitch + 1) / 2);
    ਅਚਲ ਪੂਰਨ src_UVPitch_ਖੱਬਾ = srcUVPitch - UVwidth;
    ਅਚਲ ਪੂਰਨ dstUVPitch = ((dst_pitch + 1) / 2) * 2;
    ਅਚਲ ਪੂਰਨ dst_UVPitch_ਖੱਬਾ = dstUVPitch - UVwidth * 2;
    ਅਚਲ Uint8 *src1, *src2;
    Uint8 *dstUV;
    Uint8 *tmp = ਨਿਰਾ;

    // Skip the Y plane
    src = (ਅਚਲ Uint8 *)src + ਉਚਾਈ * src_pitch;
    dst = (Uint8 *)dst + ਉਚਾਈ * dst_pitch;

    ਜੇ (src == dst) {
        // Need to make a copy of the buffer so we don't clobber it while converting
        tmp = (Uint8 *)SDL_malloc((size_t)2 * UVheight * srcUVPitch);
        ਜੇ (tmp == ਨਿਰਾ) {
            ਵਾਪਸ false;
        }
        SDL_memcpy(tmp, src, (size_t)2 * UVheight * srcUVPitch);
        src = tmp;
    }

    ਜੇ (ਉਲਟ_UV) {
        src2 = (ਅਚਲ Uint8 *)src;
        src1 = src2 + UVheight * srcUVPitch;
    } ਨਹੀਂਤਾਂ {
        src1 = (ਅਚਲ Uint8 *)src;
        src2 = src1 + UVheight * srcUVPitch;
    }
    dstUV = (Uint8 *)dst;

    y = UVheight;
    ਜਦੋਂ (y--) {
        x = UVwidth;
        ਜਦੋਂ (x >= 16) {
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
        ਜਦੋਂ (x--) {
            *dstUV++ = *src1++;
            *dstUV++ = *src2++;
        }
        src1 += src_UVPitch_ਖੱਬਾ;
        src2 += src_UVPitch_ਖੱਬਾ;
        dstUV += dst_UVPitch_ਖੱਬਾ;
    }

    ਜੇ (tmp) {
        SDL_free(tmp);
    }
    ਵਾਪਸ true;
}

ਸਥਿਰ bool SDL_TARGETING("sse2") SDL_Convert_Pixels_ਵੰਡੋ_NV_ਮੰਜ਼ਿਲ_UVPlanes_SSE2(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, ਅਚਲ ਖਾਲੀ *src, ਪੂਰਨ src_pitch, ਖਾਲੀ *dst, ਪੂਰਨ dst_pitch, bool ਉਲਟ_UV)
{
    ਪੂਰਨ x, y;
    ਅਚਲ ਪੂਰਨ UVwidth = (ਚੌੜਾਈ + 1) / 2;
    ਅਚਲ ਪੂਰਨ UVheight = (ਉਚਾਈ + 1) / 2;
    ਅਚਲ ਪੂਰਨ srcUVPitch = ((src_pitch + 1) / 2) * 2;
    ਅਚਲ ਪੂਰਨ src_UVPitch_ਖੱਬਾ = srcUVPitch - UVwidth * 2;
    ਅਚਲ ਪੂਰਨ dstUVPitch = ((dst_pitch + 1) / 2);
    ਅਚਲ ਪੂਰਨ dst_UVPitch_ਖੱਬਾ = dstUVPitch - UVwidth;
    ਅਚਲ Uint8 *srcUV;
    Uint8 *dst1, *dst2;
    Uint8 *tmp = ਨਿਰਾ;

    // Skip the Y plane
    src = (ਅਚਲ Uint8 *)src + ਉਚਾਈ * src_pitch;
    dst = (Uint8 *)dst + ਉਚਾਈ * dst_pitch;

    ਜੇ (src == dst) {
        // Need to make a copy of the buffer so we don't clobber it while converting
        tmp = (Uint8 *)SDL_malloc((size_t)UVheight * srcUVPitch);
        ਜੇ (tmp == ਨਿਰਾ) {
            ਵਾਪਸ false;
        }
        SDL_memcpy(tmp, src, (size_t)UVheight * srcUVPitch);
        src = tmp;
    }

    ਜੇ (ਉਲਟ_UV) {
        dst2 = (Uint8 *)dst;
        dst1 = dst2 + UVheight * dstUVPitch;
    } ਨਹੀਂਤਾਂ {
        dst1 = (Uint8 *)dst;
        dst2 = dst1 + UVheight * dstUVPitch;
    }
    srcUV = (ਅਚਲ Uint8 *)src;

    y = UVheight;
    ਜਦੋਂ (y--) {
        __m128i ਨਕਾਬ = _mm_set1_epi16(0x00FF);
        x = UVwidth;
        ਜਦੋਂ (x >= 16) {
            __m128i uv1 = _mm_loadu_si128((__m128i *)srcUV);
            __m128i uv2 = _mm_loadu_si128((__m128i *)(srcUV + 16));
            __m128i u1 = _mm_and_si128(uv1, ਨਕਾਬ);
            __m128i u2 = _mm_and_si128(uv2, ਨਕਾਬ);
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
        ਜਦੋਂ (x--) {
            *dst1++ = *srcUV++;
            *dst2++ = *srcUV++;
        }
        srcUV += src_UVPitch_ਖੱਬਾ;
        dst1 += dst_UVPitch_ਖੱਬਾ;
        dst2 += dst_UVPitch_ਖੱਬਾ;
    }

    ਜੇ (tmp) {
        SDL_free(tmp);
    }
    ਵਾਪਸ true;
}

ਸਥਿਰ bool SDL_TARGETING("sse2") SDL_Convert_Pixels_ਅਦਲਾ_ਬਦਲੀ_NV_SSE2(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, ਅਚਲ ਖਾਲੀ *src, ਪੂਰਨ src_pitch, ਖਾਲੀ *dst, ਪੂਰਨ dst_pitch)
{
    ਪੂਰਨ x, y;
    ਅਚਲ ਪੂਰਨ UVwidth = (ਚੌੜਾਈ + 1) / 2;
    ਅਚਲ ਪੂਰਨ UVheight = (ਉਚਾਈ + 1) / 2;
    ਅਚਲ ਪੂਰਨ srcUVPitch = ((src_pitch + 1) / 2) * 2;
    ਅਚਲ ਪੂਰਨ src_UVPitch_ਖੱਬਾ = (srcUVPitch - UVwidth * 2) / ਆਕਾਰ(Uint16);
    ਅਚਲ ਪੂਰਨ dstUVPitch = ((dst_pitch + 1) / 2) * 2;
    ਅਚਲ ਪੂਰਨ dst_UVPitch_ਖੱਬਾ = (dstUVPitch - UVwidth * 2) / ਆਕਾਰ(Uint16);
    ਅਚਲ Uint16 *srcUV;
    Uint16 *dstUV;

    // Skip the Y plane
    src = (ਅਚਲ Uint8 *)src + ਉਚਾਈ * src_pitch;
    dst = (Uint8 *)dst + ਉਚਾਈ * dst_pitch;

    srcUV = (ਅਚਲ Uint16 *)src;
    dstUV = (Uint16 *)dst;
    y = UVheight;
    ਜਦੋਂ (y--) {
        x = UVwidth;
        ਜਦੋਂ (x >= 8) {
            __m128i uv = _mm_loadu_si128((__m128i *)srcUV);
            __m128i v = _mm_slli_epi16(uv, 8);
            __m128i u = _mm_srli_epi16(uv, 8);
            __m128i vu = _mm_or_si128(v, u);
            _mm_storeu_si128((__m128i *)dstUV, vu);
            srcUV += 8;
            dstUV += 8;
            x -= 8;
        }
        ਜੇ (x > 0) {
            ਅਚਲ Uint8 *srcUV8 = (ਅਚਲ Uint8 *)srcUV;
            Uint8 *dstUV8 = (Uint8 *)dstUV;
            srcUV += x;
            dstUV += x;
            ਜਦੋਂ (x--) {
                Uint8 u = *srcUV8++;
                Uint8 v = *srcUV8++;
                *dstUV8++ = v;
                *dstUV8++ = u;
            }
        }
        srcUV += src_UVPitch_ਖੱਬਾ;
        dstUV += dst_UVPitch_ਖੱਬਾ;
    }
    ਵਾਪਸ true;
}
#ਜੇ_ਅੰਤ

ਸਥਿਰ bool SDL_Convert_Pixels_Pack_UVPlanes_ਮੰਜ਼ਿਲ_NV_std(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, ਅਚਲ ਖਾਲੀ *src, ਪੂਰਨ src_pitch, ਖਾਲੀ *dst, ਪੂਰਨ dst_pitch, bool ਉਲਟ_UV)
{
    ਪੂਰਨ x, y;
    ਅਚਲ ਪੂਰਨ UVwidth = (ਚੌੜਾਈ + 1) / 2;
    ਅਚਲ ਪੂਰਨ UVheight = (ਉਚਾਈ + 1) / 2;
    ਅਚਲ ਪੂਰਨ srcUVPitch = ((src_pitch + 1) / 2);
    ਅਚਲ ਪੂਰਨ src_UVPitch_ਖੱਬਾ = srcUVPitch - UVwidth;
    ਅਚਲ ਪੂਰਨ dstUVPitch = ((dst_pitch + 1) / 2) * 2;
    ਅਚਲ ਪੂਰਨ dst_UVPitch_ਖੱਬਾ = dstUVPitch - UVwidth * 2;
    ਅਚਲ Uint8 *src1, *src2;
    Uint8 *dstUV;
    Uint8 *tmp = ਨਿਰਾ;

    // Skip the Y plane
    src = (ਅਚਲ Uint8 *)src + ਉਚਾਈ * src_pitch;
    dst = (Uint8 *)dst + ਉਚਾਈ * dst_pitch;

    ਜੇ (src == dst) {
        // Need to make a copy of the buffer so we don't clobber it while converting
        tmp = (Uint8 *)SDL_malloc((size_t)2 * UVheight * srcUVPitch);
        ਜੇ (!tmp) {
            ਵਾਪਸ false;
        }
        SDL_memcpy(tmp, src, (size_t)2 * UVheight * srcUVPitch);
        src = tmp;
    }

    ਜੇ (ਉਲਟ_UV) {
        src2 = (ਅਚਲ Uint8 *)src;
        src1 = src2 + UVheight * srcUVPitch;
    } ਨਹੀਂਤਾਂ {
        src1 = (ਅਚਲ Uint8 *)src;
        src2 = src1 + UVheight * srcUVPitch;
    }
    dstUV = (Uint8 *)dst;

    y = UVheight;
    ਜਦੋਂ (y--) {
        x = UVwidth;
        ਜਦੋਂ (x--) {
            *dstUV++ = *src1++;
            *dstUV++ = *src2++;
        }
        src1 += src_UVPitch_ਖੱਬਾ;
        src2 += src_UVPitch_ਖੱਬਾ;
        dstUV += dst_UVPitch_ਖੱਬਾ;
    }

    SDL_free(tmp);
    ਵਾਪਸ true;
}

ਸਥਿਰ bool SDL_Convert_Pixels_ਵੰਡੋ_NV_ਮੰਜ਼ਿਲ_UVPlanes_std(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, ਅਚਲ ਖਾਲੀ *src, ਪੂਰਨ src_pitch, ਖਾਲੀ *dst, ਪੂਰਨ dst_pitch, bool ਉਲਟ_UV)
{
    ਪੂਰਨ x, y;
    ਅਚਲ ਪੂਰਨ UVwidth = (ਚੌੜਾਈ + 1) / 2;
    ਅਚਲ ਪੂਰਨ UVheight = (ਉਚਾਈ + 1) / 2;
    ਅਚਲ ਪੂਰਨ srcUVPitch = ((src_pitch + 1) / 2) * 2;
    ਅਚਲ ਪੂਰਨ src_UVPitch_ਖੱਬਾ = srcUVPitch - UVwidth * 2;
    ਅਚਲ ਪੂਰਨ dstUVPitch = ((dst_pitch + 1) / 2);
    ਅਚਲ ਪੂਰਨ dst_UVPitch_ਖੱਬਾ = dstUVPitch - UVwidth;
    ਅਚਲ Uint8 *srcUV;
    Uint8 *dst1, *dst2;
    Uint8 *tmp = ਨਿਰਾ;

    // Skip the Y plane
    src = (ਅਚਲ Uint8 *)src + ਉਚਾਈ * src_pitch;
    dst = (Uint8 *)dst + ਉਚਾਈ * dst_pitch;

    ਜੇ (src == dst) {
        // Need to make a copy of the buffer so we don't clobber it while converting
        tmp = (Uint8 *)SDL_malloc((size_t)UVheight * srcUVPitch);
        ਜੇ (!tmp) {
            ਵਾਪਸ false;
        }
        SDL_memcpy(tmp, src, (size_t)UVheight * srcUVPitch);
        src = tmp;
    }

    ਜੇ (ਉਲਟ_UV) {
        dst2 = (Uint8 *)dst;
        dst1 = dst2 + UVheight * dstUVPitch;
    } ਨਹੀਂਤਾਂ {
        dst1 = (Uint8 *)dst;
        dst2 = dst1 + UVheight * dstUVPitch;
    }
    srcUV = (ਅਚਲ Uint8 *)src;

    y = UVheight;
    ਜਦੋਂ (y--) {
        x = UVwidth;
        ਜਦੋਂ (x--) {
            *dst1++ = *srcUV++;
            *dst2++ = *srcUV++;
        }
        srcUV += src_UVPitch_ਖੱਬਾ;
        dst1 += dst_UVPitch_ਖੱਬਾ;
        dst2 += dst_UVPitch_ਖੱਬਾ;
    }

    SDL_free(tmp);
    ਵਾਪਸ true;
}

ਸਥਿਰ bool SDL_Convert_Pixels_ਅਦਲਾ_ਬਦਲੀ_NV_std(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, ਅਚਲ ਖਾਲੀ *src, ਪੂਰਨ src_pitch, ਖਾਲੀ *dst, ਪੂਰਨ dst_pitch)
{
    ਪੂਰਨ x, y;
    ਅਚਲ ਪੂਰਨ UVwidth = (ਚੌੜਾਈ + 1) / 2;
    ਅਚਲ ਪੂਰਨ UVheight = (ਉਚਾਈ + 1) / 2;
    ਅਚਲ ਪੂਰਨ srcUVPitch = ((src_pitch + 1) / 2) * 2;
    ਅਚਲ ਪੂਰਨ dstUVPitch = ((dst_pitch + 1) / 2) * 2;

    // Skip the Y plane
    src = (ਅਚਲ Uint8 *)src + ਉਚਾਈ * src_pitch;
    dst = (Uint8 *)dst + ਉਚਾਈ * dst_pitch;

    bool aligned = (((uintptr_t)src | (uintptr_t)dst) & 1) == 0;
    ਜੇ (aligned) {
        ਅਚਲ ਪੂਰਨ src_UVPitch_ਖੱਬਾ = (srcUVPitch - UVwidth * 2) / ਆਕਾਰ(Uint16);
        ਅਚਲ ਪੂਰਨ dst_UVPitch_ਖੱਬਾ = (dstUVPitch - UVwidth * 2) / ਆਕਾਰ(Uint16);
        ਅਚਲ Uint16 *srcUV = (ਅਚਲ Uint16 *)src;
        Uint16 *dstUV = (Uint16 *)dst;
        y = UVheight;
        ਜਦੋਂ (y--) {
            x = UVwidth;
            ਜਦੋਂ (x--) {
                *dstUV++ = SDL_Swap16(*srcUV++);
            }
            srcUV += src_UVPitch_ਖੱਬਾ;
            dstUV += dst_UVPitch_ਖੱਬਾ;
        }
    } ਨਹੀਂਤਾਂ {
        ਅਚਲ ਪੂਰਨ src_UVPitch_ਖੱਬਾ = (srcUVPitch - UVwidth * 2);
        ਅਚਲ ਪੂਰਨ dst_UVPitch_ਖੱਬਾ = (dstUVPitch - UVwidth * 2);
        ਅਚਲ Uint8 *srcUV = (ਅਚਲ Uint8 *)src;
        Uint8 *dstUV = (Uint8 *)dst;
        y = UVheight;
        ਜਦੋਂ (y--) {
            x = UVwidth;
            ਜਦੋਂ (x--) {
                Uint8 u = *srcUV++;
                Uint8 v = *srcUV++;
                *dstUV++ = v;
                *dstUV++ = u;
            }
            srcUV += src_UVPitch_ਖੱਬਾ;
            dstUV += dst_UVPitch_ਖੱਬਾ;
        }
    }
    ਵਾਪਸ true;
}

ਸਥਿਰ bool SDL_Convert_Pixels_Pack_UVPlanes_ਮੰਜ਼ਿਲ_NV(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, ਅਚਲ ਖਾਲੀ *src, ਪੂਰਨ src_pitch, ਖਾਲੀ *dst, ਪੂਰਨ dst_pitch, bool ਉਲਟ_UV)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_SSE2_INTRINSICS
    ਜੇ (SDL_HasSSE2()) {
      ਵਾਪਸ SDL_Convert_Pixels_Pack_UVPlanes_ਮੰਜ਼ਿਲ_NV_SSE2(ਚੌੜਾਈ, ਉਚਾਈ, src, src_pitch, dst, dst_pitch, ਉਲਟ_UV);
    }
#ਜੇ_ਅੰਤ
    ਵਾਪਸ SDL_Convert_Pixels_Pack_UVPlanes_ਮੰਜ਼ਿਲ_NV_std(ਚੌੜਾਈ, ਉਚਾਈ, src, src_pitch, dst, dst_pitch, ਉਲਟ_UV);
}

ਸਥਿਰ bool SDL_Convert_Pixels_ਵੰਡੋ_NV_ਮੰਜ਼ਿਲ_UVPlanes(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, ਅਚਲ ਖਾਲੀ *src, ਪੂਰਨ src_pitch, ਖਾਲੀ *dst, ਪੂਰਨ dst_pitch, bool ਉਲਟ_UV)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_SSE2_INTRINSICS
    ਜੇ (SDL_HasSSE2()) {
      ਵਾਪਸ SDL_Convert_Pixels_ਵੰਡੋ_NV_ਮੰਜ਼ਿਲ_UVPlanes_SSE2(ਚੌੜਾਈ, ਉਚਾਈ, src, src_pitch, dst, dst_pitch, ਉਲਟ_UV);
    }
#ਜੇ_ਅੰਤ
    ਵਾਪਸ SDL_Convert_Pixels_ਵੰਡੋ_NV_ਮੰਜ਼ਿਲ_UVPlanes_std(ਚੌੜਾਈ, ਉਚਾਈ, src, src_pitch, dst, dst_pitch, ਉਲਟ_UV);
}

ਸਥਿਰ bool SDL_Convert_Pixels_ਅਦਲਾ_ਬਦਲੀ_NV(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, ਅਚਲ ਖਾਲੀ *src, ਪੂਰਨ src_pitch, ਖਾਲੀ *dst, ਪੂਰਨ dst_pitch)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_SSE2_INTRINSICS
    ਜੇ (SDL_HasSSE2()) {
      ਵਾਪਸ SDL_Convert_Pixels_ਅਦਲਾ_ਬਦਲੀ_NV_SSE2(ਚੌੜਾਈ, ਉਚਾਈ, src, src_pitch, dst, dst_pitch);
    }
#ਜੇ_ਅੰਤ
    ਵਾਪਸ SDL_Convert_Pixels_ਅਦਲਾ_ਬਦਲੀ_NV_std(ਚੌੜਾਈ, ਉਚਾਈ, src, src_pitch, dst, dst_pitch);
}

ਸਥਿਰ bool SDL_Convert_Pixels_Planar2x2_ਮੰਜ਼ਿਲ_Planar2x2(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ,
                                                     SDL_PixelFormat src_format, ਅਚਲ ਖਾਲੀ *src, ਪੂਰਨ src_pitch,
                                                     SDL_PixelFormat dst_format, ਖਾਲੀ *dst, ਪੂਰਨ dst_pitch)
{
    ਜੇ (src != dst) {
        // Copy Y plane
        ਪੂਰਨ i;
        ਅਚਲ Uint8 *srcY = (ਅਚਲ Uint8 *)src;
        Uint8 *dstY = (Uint8 *)dst;
        ਲਈ (i = ਉਚਾਈ; i--;) {
            SDL_memcpy(dstY, srcY, ਚੌੜਾਈ);
            srcY += src_pitch;
            dstY += dst_pitch;
        }
    }

    ਚੋਣ (src_format) {
    ਹਾਲਤ SDL_PIXELFORMAT_YV12:
        ਚੋਣ (dst_format) {
        ਹਾਲਤ SDL_PIXELFORMAT_IYUV:
            ਵਾਪਸ SDL_Convert_Pixels_ਅਦਲਾ_ਬਦਲੀ_UVPlanes(ਚੌੜਾਈ, ਉਚਾਈ, src, src_pitch, dst, dst_pitch);
        ਹਾਲਤ SDL_PIXELFORMAT_NV12:
            ਵਾਪਸ SDL_Convert_Pixels_Pack_UVPlanes_ਮੰਜ਼ਿਲ_NV(ਚੌੜਾਈ, ਉਚਾਈ, src, src_pitch, dst, dst_pitch, true);
        ਹਾਲਤ SDL_PIXELFORMAT_NV21:
            ਵਾਪਸ SDL_Convert_Pixels_Pack_UVPlanes_ਮੰਜ਼ਿਲ_NV(ਚੌੜਾਈ, ਉਚਾਈ, src, src_pitch, dst, dst_pitch, false);
        ਮੂਲ:
            ਰੋਕੋ;
        }
        ਰੋਕੋ;
    ਹਾਲਤ SDL_PIXELFORMAT_IYUV:
        ਚੋਣ (dst_format) {
        ਹਾਲਤ SDL_PIXELFORMAT_YV12:
            ਵਾਪਸ SDL_Convert_Pixels_ਅਦਲਾ_ਬਦਲੀ_UVPlanes(ਚੌੜਾਈ, ਉਚਾਈ, src, src_pitch, dst, dst_pitch);
        ਹਾਲਤ SDL_PIXELFORMAT_NV12:
            ਵਾਪਸ SDL_Convert_Pixels_Pack_UVPlanes_ਮੰਜ਼ਿਲ_NV(ਚੌੜਾਈ, ਉਚਾਈ, src, src_pitch, dst, dst_pitch, false);
        ਹਾਲਤ SDL_PIXELFORMAT_NV21:
            ਵਾਪਸ SDL_Convert_Pixels_Pack_UVPlanes_ਮੰਜ਼ਿਲ_NV(ਚੌੜਾਈ, ਉਚਾਈ, src, src_pitch, dst, dst_pitch, true);
        ਮੂਲ:
            ਰੋਕੋ;
        }
        ਰੋਕੋ;
    ਹਾਲਤ SDL_PIXELFORMAT_NV12:
        ਚੋਣ (dst_format) {
        ਹਾਲਤ SDL_PIXELFORMAT_YV12:
            ਵਾਪਸ SDL_Convert_Pixels_ਵੰਡੋ_NV_ਮੰਜ਼ਿਲ_UVPlanes(ਚੌੜਾਈ, ਉਚਾਈ, src, src_pitch, dst, dst_pitch, true);
        ਹਾਲਤ SDL_PIXELFORMAT_IYUV:
            ਵਾਪਸ SDL_Convert_Pixels_ਵੰਡੋ_NV_ਮੰਜ਼ਿਲ_UVPlanes(ਚੌੜਾਈ, ਉਚਾਈ, src, src_pitch, dst, dst_pitch, false);
        ਹਾਲਤ SDL_PIXELFORMAT_NV21:
            ਵਾਪਸ SDL_Convert_Pixels_ਅਦਲਾ_ਬਦਲੀ_NV(ਚੌੜਾਈ, ਉਚਾਈ, src, src_pitch, dst, dst_pitch);
        ਮੂਲ:
            ਰੋਕੋ;
        }
        ਰੋਕੋ;
    ਹਾਲਤ SDL_PIXELFORMAT_NV21:
        ਚੋਣ (dst_format) {
        ਹਾਲਤ SDL_PIXELFORMAT_YV12:
            ਵਾਪਸ SDL_Convert_Pixels_ਵੰਡੋ_NV_ਮੰਜ਼ਿਲ_UVPlanes(ਚੌੜਾਈ, ਉਚਾਈ, src, src_pitch, dst, dst_pitch, false);
        ਹਾਲਤ SDL_PIXELFORMAT_IYUV:
            ਵਾਪਸ SDL_Convert_Pixels_ਵੰਡੋ_NV_ਮੰਜ਼ਿਲ_UVPlanes(ਚੌੜਾਈ, ਉਚਾਈ, src, src_pitch, dst, dst_pitch, true);
        ਹਾਲਤ SDL_PIXELFORMAT_NV12:
            ਵਾਪਸ SDL_Convert_Pixels_ਅਦਲਾ_ਬਦਲੀ_NV(ਚੌੜਾਈ, ਉਚਾਈ, src, src_pitch, dst, dst_pitch);
        ਮੂਲ:
            ਰੋਕੋ;
        }
        ਰੋਕੋ;
    ਮੂਲ:
        ਰੋਕੋ;
    }
    ਵਾਪਸ SDL_ਸੈੱਟ_Error("SDL_ConvertPixels_Planar2x2_to_Planar2x2: Unsupported YUV conversion: %s -> %s", SDL_GetPixelFormatName(src_format),
                        SDL_GetPixelFormatName(dst_format));
}

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_SSE2_INTRINSICS
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PACKED4_ਮੰਜ਼ਿਲ_PACKED4_ਪੰਕਤੀ_SSE2(shuffle)                      \
    ਜਦੋਂ (x >= 4) {                                              \
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

ਸਥਿਰ bool SDL_TARGETING("sse2") SDL_Convert_Pixels_YUY2_ਮੰਜ਼ਿਲ_UYVY_SSE2(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, ਅਚਲ ਖਾਲੀ *src, ਪੂਰਨ src_pitch, ਖਾਲੀ *dst, ਪੂਰਨ dst_pitch)
{
    ਪੂਰਨ x, y;
    ਅਚਲ ਪੂਰਨ YUVwidth = (ਚੌੜਾਈ + 1) / 2;
    ਅਚਲ ਪੂਰਨ src_YUVPitch_ਖੱਬਾ = (src_pitch - YUVwidth * 4);
    ਅਚਲ ਪੂਰਨ dst_YUVPitch_ਖੱਬਾ = (dst_pitch - YUVwidth * 4);
    ਅਚਲ Uint8 *srcYUV = (ਅਚਲ Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = ਉਚਾਈ;
    x = YUVwidth;
    ਜਦੋਂ (y--) {
        PACKED4_ਮੰਜ਼ਿਲ_PACKED4_ਪੰਕਤੀ_SSE2(_MM_SHUFFLE(2, 3, 0, 1));
        ਜਦੋਂ (x--) {
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
        srcYUV += src_YUVPitch_ਖੱਬਾ;
        dstYUV += dst_YUVPitch_ਖੱਬਾ;
        x = YUVwidth;
    }
    ਵਾਪਸ true;
}

ਸਥਿਰ bool SDL_TARGETING("sse2") SDL_Convert_Pixels_YUY2_ਮੰਜ਼ਿਲ_YVYU_SSE2(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, ਅਚਲ ਖਾਲੀ *src, ਪੂਰਨ src_pitch, ਖਾਲੀ *dst, ਪੂਰਨ dst_pitch)
{
    ਪੂਰਨ x, y;
    ਅਚਲ ਪੂਰਨ YUVwidth = (ਚੌੜਾਈ + 1) / 2;
    ਅਚਲ ਪੂਰਨ src_YUVPitch_ਖੱਬਾ = (src_pitch - YUVwidth * 4);
    ਅਚਲ ਪੂਰਨ dst_YUVPitch_ਖੱਬਾ = (dst_pitch - YUVwidth * 4);
    ਅਚਲ Uint8 *srcYUV = (ਅਚਲ Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = ਉਚਾਈ;
    x = YUVwidth;
    ਜਦੋਂ (y--) {
        PACKED4_ਮੰਜ਼ਿਲ_PACKED4_ਪੰਕਤੀ_SSE2(_MM_SHUFFLE(1, 2, 3, 0));
        ਜਦੋਂ (x--) {
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
        srcYUV += src_YUVPitch_ਖੱਬਾ;
        dstYUV += dst_YUVPitch_ਖੱਬਾ;
        x = YUVwidth;
    }
    ਵਾਪਸ true;
}

ਸਥਿਰ bool SDL_TARGETING("sse2") SDL_Convert_Pixels_UYVY_ਮੰਜ਼ਿਲ_YUY2_SSE2(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, ਅਚਲ ਖਾਲੀ *src, ਪੂਰਨ src_pitch, ਖਾਲੀ *dst, ਪੂਰਨ dst_pitch)
{
    ਪੂਰਨ x, y;
    ਅਚਲ ਪੂਰਨ YUVwidth = (ਚੌੜਾਈ + 1) / 2;
    ਅਚਲ ਪੂਰਨ src_YUVPitch_ਖੱਬਾ = (src_pitch - YUVwidth * 4);
    ਅਚਲ ਪੂਰਨ dst_YUVPitch_ਖੱਬਾ = (dst_pitch - YUVwidth * 4);
    ਅਚਲ Uint8 *srcYUV = (ਅਚਲ Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = ਉਚਾਈ;
    x = YUVwidth;
    ਜਦੋਂ (y--) {
        PACKED4_ਮੰਜ਼ਿਲ_PACKED4_ਪੰਕਤੀ_SSE2(_MM_SHUFFLE(2, 3, 0, 1));
        ਜਦੋਂ (x--) {
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
        srcYUV += src_YUVPitch_ਖੱਬਾ;
        dstYUV += dst_YUVPitch_ਖੱਬਾ;
        x = YUVwidth;
    }
    ਵਾਪਸ true;
}

ਸਥਿਰ bool SDL_TARGETING("sse2") SDL_Convert_Pixels_UYVY_ਮੰਜ਼ਿਲ_YVYU_SSE2(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, ਅਚਲ ਖਾਲੀ *src, ਪੂਰਨ src_pitch, ਖਾਲੀ *dst, ਪੂਰਨ dst_pitch)
{
    ਪੂਰਨ x, y;
    ਅਚਲ ਪੂਰਨ YUVwidth = (ਚੌੜਾਈ + 1) / 2;
    ਅਚਲ ਪੂਰਨ src_YUVPitch_ਖੱਬਾ = (src_pitch - YUVwidth * 4);
    ਅਚਲ ਪੂਰਨ dst_YUVPitch_ਖੱਬਾ = (dst_pitch - YUVwidth * 4);
    ਅਚਲ Uint8 *srcYUV = (ਅਚਲ Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = ਉਚਾਈ;
    x = YUVwidth;
    ਜਦੋਂ (y--) {
        PACKED4_ਮੰਜ਼ਿਲ_PACKED4_ਪੰਕਤੀ_SSE2(_MM_SHUFFLE(0, 3, 2, 1));
        ਜਦੋਂ (x--) {
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
        srcYUV += src_YUVPitch_ਖੱਬਾ;
        dstYUV += dst_YUVPitch_ਖੱਬਾ;
        x = YUVwidth;
    }
    ਵਾਪਸ true;
}

ਸਥਿਰ bool SDL_TARGETING("sse2") SDL_Convert_Pixels_YVYU_ਮੰਜ਼ਿਲ_YUY2_SSE2(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, ਅਚਲ ਖਾਲੀ *src, ਪੂਰਨ src_pitch, ਖਾਲੀ *dst, ਪੂਰਨ dst_pitch)
{
    ਪੂਰਨ x, y;
    ਅਚਲ ਪੂਰਨ YUVwidth = (ਚੌੜਾਈ + 1) / 2;
    ਅਚਲ ਪੂਰਨ src_YUVPitch_ਖੱਬਾ = (src_pitch - YUVwidth * 4);
    ਅਚਲ ਪੂਰਨ dst_YUVPitch_ਖੱਬਾ = (dst_pitch - YUVwidth * 4);
    ਅਚਲ Uint8 *srcYUV = (ਅਚਲ Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = ਉਚਾਈ;
    x = YUVwidth;
    ਜਦੋਂ (y--) {
        PACKED4_ਮੰਜ਼ਿਲ_PACKED4_ਪੰਕਤੀ_SSE2(_MM_SHUFFLE(1, 2, 3, 0));
        ਜਦੋਂ (x--) {
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
        srcYUV += src_YUVPitch_ਖੱਬਾ;
        dstYUV += dst_YUVPitch_ਖੱਬਾ;
        x = YUVwidth;
    }
    ਵਾਪਸ true;
}

ਸਥਿਰ bool SDL_TARGETING("sse2") SDL_Convert_Pixels_YVYU_ਮੰਜ਼ਿਲ_UYVY_SSE2(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, ਅਚਲ ਖਾਲੀ *src, ਪੂਰਨ src_pitch, ਖਾਲੀ *dst, ਪੂਰਨ dst_pitch)
{
    ਪੂਰਨ x, y;
    ਅਚਲ ਪੂਰਨ YUVwidth = (ਚੌੜਾਈ + 1) / 2;
    ਅਚਲ ਪੂਰਨ src_YUVPitch_ਖੱਬਾ = (src_pitch - YUVwidth * 4);
    ਅਚਲ ਪੂਰਨ dst_YUVPitch_ਖੱਬਾ = (dst_pitch - YUVwidth * 4);
    ਅਚਲ Uint8 *srcYUV = (ਅਚਲ Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = ਉਚਾਈ;
    x = YUVwidth;
    ਜਦੋਂ (y--) {
        PACKED4_ਮੰਜ਼ਿਲ_PACKED4_ਪੰਕਤੀ_SSE2(_MM_SHUFFLE(2, 1, 0, 3));
        ਜਦੋਂ (x--) {
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
        srcYUV += src_YUVPitch_ਖੱਬਾ;
        dstYUV += dst_YUVPitch_ਖੱਬਾ;
        x = YUVwidth;
    }
    ਵਾਪਸ true;
}
#ਜੇ_ਅੰਤ

ਸਥਿਰ bool SDL_Convert_Pixels_YUY2_ਮੰਜ਼ਿਲ_UYVY_std(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, ਅਚਲ ਖਾਲੀ *src, ਪੂਰਨ src_pitch, ਖਾਲੀ *dst, ਪੂਰਨ dst_pitch)
{
    ਪੂਰਨ x, y;
    ਅਚਲ ਪੂਰਨ YUVwidth = (ਚੌੜਾਈ + 1) / 2;
    ਅਚਲ ਪੂਰਨ src_YUVPitch_ਖੱਬਾ = (src_pitch - YUVwidth * 4);
    ਅਚਲ ਪੂਰਨ dst_YUVPitch_ਖੱਬਾ = (dst_pitch - YUVwidth * 4);
    ਅਚਲ Uint8 *srcYUV = (ਅਚਲ Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = ਉਚਾਈ;
    ਜਦੋਂ (y--) {
        x = YUVwidth;
        ਜਦੋਂ (x--) {
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
        srcYUV += src_YUVPitch_ਖੱਬਾ;
        dstYUV += dst_YUVPitch_ਖੱਬਾ;
    }
    ਵਾਪਸ true;
}

ਸਥਿਰ bool SDL_Convert_Pixels_YUY2_ਮੰਜ਼ਿਲ_YVYU_std(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, ਅਚਲ ਖਾਲੀ *src, ਪੂਰਨ src_pitch, ਖਾਲੀ *dst, ਪੂਰਨ dst_pitch)
{
    ਪੂਰਨ x, y;
    ਅਚਲ ਪੂਰਨ YUVwidth = (ਚੌੜਾਈ + 1) / 2;
    ਅਚਲ ਪੂਰਨ src_YUVPitch_ਖੱਬਾ = (src_pitch - YUVwidth * 4);
    ਅਚਲ ਪੂਰਨ dst_YUVPitch_ਖੱਬਾ = (dst_pitch - YUVwidth * 4);
    ਅਚਲ Uint8 *srcYUV = (ਅਚਲ Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = ਉਚਾਈ;
    ਜਦੋਂ (y--) {
        x = YUVwidth;
        ਜਦੋਂ (x--) {
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
        srcYUV += src_YUVPitch_ਖੱਬਾ;
        dstYUV += dst_YUVPitch_ਖੱਬਾ;
    }
    ਵਾਪਸ true;
}

ਸਥਿਰ bool SDL_Convert_Pixels_UYVY_ਮੰਜ਼ਿਲ_YUY2_std(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, ਅਚਲ ਖਾਲੀ *src, ਪੂਰਨ src_pitch, ਖਾਲੀ *dst, ਪੂਰਨ dst_pitch)
{
    ਪੂਰਨ x, y;
    ਅਚਲ ਪੂਰਨ YUVwidth = (ਚੌੜਾਈ + 1) / 2;
    ਅਚਲ ਪੂਰਨ src_YUVPitch_ਖੱਬਾ = (src_pitch - YUVwidth * 4);
    ਅਚਲ ਪੂਰਨ dst_YUVPitch_ਖੱਬਾ = (dst_pitch - YUVwidth * 4);
    ਅਚਲ Uint8 *srcYUV = (ਅਚਲ Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = ਉਚਾਈ;
    ਜਦੋਂ (y--) {
        x = YUVwidth;
        ਜਦੋਂ (x--) {
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
        srcYUV += src_YUVPitch_ਖੱਬਾ;
        dstYUV += dst_YUVPitch_ਖੱਬਾ;
    }
    ਵਾਪਸ true;
}

ਸਥਿਰ bool SDL_Convert_Pixels_UYVY_ਮੰਜ਼ਿਲ_YVYU_std(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, ਅਚਲ ਖਾਲੀ *src, ਪੂਰਨ src_pitch, ਖਾਲੀ *dst, ਪੂਰਨ dst_pitch)
{
    ਪੂਰਨ x, y;
    ਅਚਲ ਪੂਰਨ YUVwidth = (ਚੌੜਾਈ + 1) / 2;
    ਅਚਲ ਪੂਰਨ src_YUVPitch_ਖੱਬਾ = (src_pitch - YUVwidth * 4);
    ਅਚਲ ਪੂਰਨ dst_YUVPitch_ਖੱਬਾ = (dst_pitch - YUVwidth * 4);
    ਅਚਲ Uint8 *srcYUV = (ਅਚਲ Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = ਉਚਾਈ;
    ਜਦੋਂ (y--) {
        x = YUVwidth;
        ਜਦੋਂ (x--) {
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
        srcYUV += src_YUVPitch_ਖੱਬਾ;
        dstYUV += dst_YUVPitch_ਖੱਬਾ;
    }
    ਵਾਪਸ true;
}

ਸਥਿਰ bool SDL_Convert_Pixels_YVYU_ਮੰਜ਼ਿਲ_YUY2_std(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, ਅਚਲ ਖਾਲੀ *src, ਪੂਰਨ src_pitch, ਖਾਲੀ *dst, ਪੂਰਨ dst_pitch)
{
    ਪੂਰਨ x, y;
    ਅਚਲ ਪੂਰਨ YUVwidth = (ਚੌੜਾਈ + 1) / 2;
    ਅਚਲ ਪੂਰਨ src_YUVPitch_ਖੱਬਾ = (src_pitch - YUVwidth * 4);
    ਅਚਲ ਪੂਰਨ dst_YUVPitch_ਖੱਬਾ = (dst_pitch - YUVwidth * 4);
    ਅਚਲ Uint8 *srcYUV = (ਅਚਲ Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = ਉਚਾਈ;
    ਜਦੋਂ (y--) {
        x = YUVwidth;
        ਜਦੋਂ (x--) {
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
        srcYUV += src_YUVPitch_ਖੱਬਾ;
        dstYUV += dst_YUVPitch_ਖੱਬਾ;
    }
    ਵਾਪਸ true;
}

ਸਥਿਰ bool SDL_Convert_Pixels_YVYU_ਮੰਜ਼ਿਲ_UYVY_std(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, ਅਚਲ ਖਾਲੀ *src, ਪੂਰਨ src_pitch, ਖਾਲੀ *dst, ਪੂਰਨ dst_pitch)
{
    ਪੂਰਨ x, y;
    ਅਚਲ ਪੂਰਨ YUVwidth = (ਚੌੜਾਈ + 1) / 2;
    ਅਚਲ ਪੂਰਨ src_YUVPitch_ਖੱਬਾ = (src_pitch - YUVwidth * 4);
    ਅਚਲ ਪੂਰਨ dst_YUVPitch_ਖੱਬਾ = (dst_pitch - YUVwidth * 4);
    ਅਚਲ Uint8 *srcYUV = (ਅਚਲ Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = ਉਚਾਈ;
    ਜਦੋਂ (y--) {
        x = YUVwidth;
        ਜਦੋਂ (x--) {
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
        srcYUV += src_YUVPitch_ਖੱਬਾ;
        dstYUV += dst_YUVPitch_ਖੱਬਾ;
    }
    ਵਾਪਸ true;
}

ਸਥਿਰ bool SDL_Convert_Pixels_YUY2_ਮੰਜ਼ਿਲ_UYVY(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, ਅਚਲ ਖਾਲੀ *src, ਪੂਰਨ src_pitch, ਖਾਲੀ *dst, ਪੂਰਨ dst_pitch)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_SSE2_INTRINSICS
    ਜੇ (SDL_HasSSE2()) {
      ਵਾਪਸ SDL_Convert_Pixels_YUY2_ਮੰਜ਼ਿਲ_UYVY_SSE2(ਚੌੜਾਈ, ਉਚਾਈ, src, src_pitch, dst, dst_pitch);
    }
#ਜੇ_ਅੰਤ
    ਵਾਪਸ SDL_Convert_Pixels_YUY2_ਮੰਜ਼ਿਲ_UYVY_std(ਚੌੜਾਈ, ਉਚਾਈ, src, src_pitch, dst, dst_pitch);
}

ਸਥਿਰ bool SDL_Convert_Pixels_YUY2_ਮੰਜ਼ਿਲ_YVYU(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, ਅਚਲ ਖਾਲੀ *src, ਪੂਰਨ src_pitch, ਖਾਲੀ *dst, ਪੂਰਨ dst_pitch)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_SSE2_INTRINSICS
    ਜੇ (SDL_HasSSE2()) {
      ਵਾਪਸ SDL_Convert_Pixels_YUY2_ਮੰਜ਼ਿਲ_YVYU_SSE2(ਚੌੜਾਈ, ਉਚਾਈ, src, src_pitch, dst, dst_pitch);
    }
#ਜੇ_ਅੰਤ
    ਵਾਪਸ SDL_Convert_Pixels_YUY2_ਮੰਜ਼ਿਲ_YVYU_std(ਚੌੜਾਈ, ਉਚਾਈ, src, src_pitch, dst, dst_pitch);
}

ਸਥਿਰ bool SDL_Convert_Pixels_UYVY_ਮੰਜ਼ਿਲ_YUY2(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, ਅਚਲ ਖਾਲੀ *src, ਪੂਰਨ src_pitch, ਖਾਲੀ *dst, ਪੂਰਨ dst_pitch)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_SSE2_INTRINSICS
    ਜੇ (SDL_HasSSE2()) {
      ਵਾਪਸ SDL_Convert_Pixels_UYVY_ਮੰਜ਼ਿਲ_YUY2_SSE2(ਚੌੜਾਈ, ਉਚਾਈ, src, src_pitch, dst, dst_pitch);
    }
#ਜੇ_ਅੰਤ
    ਵਾਪਸ SDL_Convert_Pixels_UYVY_ਮੰਜ਼ਿਲ_YUY2_std(ਚੌੜਾਈ, ਉਚਾਈ, src, src_pitch, dst, dst_pitch);
}

ਸਥਿਰ bool SDL_Convert_Pixels_UYVY_ਮੰਜ਼ਿਲ_YVYU(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, ਅਚਲ ਖਾਲੀ *src, ਪੂਰਨ src_pitch, ਖਾਲੀ *dst, ਪੂਰਨ dst_pitch)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_SSE2_INTRINSICS
    ਜੇ (SDL_HasSSE2()) {
      ਵਾਪਸ SDL_Convert_Pixels_UYVY_ਮੰਜ਼ਿਲ_YVYU_SSE2(ਚੌੜਾਈ, ਉਚਾਈ, src, src_pitch, dst, dst_pitch);
    }
#ਜੇ_ਅੰਤ
    ਵਾਪਸ SDL_Convert_Pixels_UYVY_ਮੰਜ਼ਿਲ_YVYU_std(ਚੌੜਾਈ, ਉਚਾਈ, src, src_pitch, dst, dst_pitch);
}

ਸਥਿਰ bool SDL_Convert_Pixels_YVYU_ਮੰਜ਼ਿਲ_YUY2(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, ਅਚਲ ਖਾਲੀ *src, ਪੂਰਨ src_pitch, ਖਾਲੀ *dst, ਪੂਰਨ dst_pitch)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_SSE2_INTRINSICS
    ਜੇ (SDL_HasSSE2()) {
      ਵਾਪਸ SDL_Convert_Pixels_YVYU_ਮੰਜ਼ਿਲ_YUY2_SSE2(ਚੌੜਾਈ, ਉਚਾਈ, src, src_pitch, dst, dst_pitch);
    }
#ਜੇ_ਅੰਤ
    ਵਾਪਸ SDL_Convert_Pixels_YVYU_ਮੰਜ਼ਿਲ_YUY2_std(ਚੌੜਾਈ, ਉਚਾਈ, src, src_pitch, dst, dst_pitch);
}

ਸਥਿਰ bool SDL_Convert_Pixels_YVYU_ਮੰਜ਼ਿਲ_UYVY(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, ਅਚਲ ਖਾਲੀ *src, ਪੂਰਨ src_pitch, ਖਾਲੀ *dst, ਪੂਰਨ dst_pitch)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_SSE2_INTRINSICS
    ਜੇ (SDL_HasSSE2()) {
      ਵਾਪਸ SDL_Convert_Pixels_YVYU_ਮੰਜ਼ਿਲ_UYVY_SSE2(ਚੌੜਾਈ, ਉਚਾਈ, src, src_pitch, dst, dst_pitch);
    }
#ਜੇ_ਅੰਤ
    ਵਾਪਸ SDL_Convert_Pixels_YVYU_ਮੰਜ਼ਿਲ_UYVY_std(ਚੌੜਾਈ, ਉਚਾਈ, src, src_pitch, dst, dst_pitch);
}

ਸਥਿਰ bool SDL_Convert_Pixels_Packed4_ਮੰਜ਼ਿਲ_Packed4(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ,
                                                SDL_PixelFormat src_format, ਅਚਲ ਖਾਲੀ *src, ਪੂਰਨ src_pitch,
                                                SDL_PixelFormat dst_format, ਖਾਲੀ *dst, ਪੂਰਨ dst_pitch)
{
    ਚੋਣ (src_format) {
    ਹਾਲਤ SDL_PIXELFORMAT_YUY2:
        ਚੋਣ (dst_format) {
        ਹਾਲਤ SDL_PIXELFORMAT_UYVY:
            ਵਾਪਸ SDL_Convert_Pixels_YUY2_ਮੰਜ਼ਿਲ_UYVY(ਚੌੜਾਈ, ਉਚਾਈ, src, src_pitch, dst, dst_pitch);
        ਹਾਲਤ SDL_PIXELFORMAT_YVYU:
            ਵਾਪਸ SDL_Convert_Pixels_YUY2_ਮੰਜ਼ਿਲ_YVYU(ਚੌੜਾਈ, ਉਚਾਈ, src, src_pitch, dst, dst_pitch);
        ਮੂਲ:
            ਰੋਕੋ;
        }
        ਰੋਕੋ;
    ਹਾਲਤ SDL_PIXELFORMAT_UYVY:
        ਚੋਣ (dst_format) {
        ਹਾਲਤ SDL_PIXELFORMAT_YUY2:
            ਵਾਪਸ SDL_Convert_Pixels_UYVY_ਮੰਜ਼ਿਲ_YUY2(ਚੌੜਾਈ, ਉਚਾਈ, src, src_pitch, dst, dst_pitch);
        ਹਾਲਤ SDL_PIXELFORMAT_YVYU:
            ਵਾਪਸ SDL_Convert_Pixels_UYVY_ਮੰਜ਼ਿਲ_YVYU(ਚੌੜਾਈ, ਉਚਾਈ, src, src_pitch, dst, dst_pitch);
        ਮੂਲ:
            ਰੋਕੋ;
        }
        ਰੋਕੋ;
    ਹਾਲਤ SDL_PIXELFORMAT_YVYU:
        ਚੋਣ (dst_format) {
        ਹਾਲਤ SDL_PIXELFORMAT_YUY2:
            ਵਾਪਸ SDL_Convert_Pixels_YVYU_ਮੰਜ਼ਿਲ_YUY2(ਚੌੜਾਈ, ਉਚਾਈ, src, src_pitch, dst, dst_pitch);
        ਹਾਲਤ SDL_PIXELFORMAT_UYVY:
            ਵਾਪਸ SDL_Convert_Pixels_YVYU_ਮੰਜ਼ਿਲ_UYVY(ਚੌੜਾਈ, ਉਚਾਈ, src, src_pitch, dst, dst_pitch);
        ਮੂਲ:
            ਰੋਕੋ;
        }
        ਰੋਕੋ;
    ਮੂਲ:
        ਰੋਕੋ;
    }
    ਵਾਪਸ SDL_ਸੈੱਟ_Error("SDL_ConvertPixels_Packed4_to_Packed4: Unsupported YUV conversion: %s -> %s", SDL_GetPixelFormatName(src_format),
                        SDL_GetPixelFormatName(dst_format));
}

ਸਥਿਰ bool SDL_Convert_Pixels_Planar2x2_ਮੰਜ਼ਿਲ_Packed4(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ,
                                                   SDL_PixelFormat src_format, ਅਚਲ ਖਾਲੀ *src, ਪੂਰਨ src_pitch,
                                                   SDL_PixelFormat dst_format, ਖਾਲੀ *dst, ਪੂਰਨ dst_pitch)
{
    ਪੂਰਨ x, y;
    ਅਚਲ Uint8 *srcY1, *srcY2, *srcU, *srcV;
    Uint32 srcY_pitch, srcUV_pitch;
    Uint32 src_Y_pitch_ਖੱਬਾ, src_UV_pitch_ਖੱਬਾ, srcUV_pixel_stride;
    Uint8 *dstY1, *dstY2, *dstU1, *dstU2, *dstV1, *dstV2;
    Uint32 dstY_pitch, dstUV_pitch;
    Uint32 dst_pitch_ਖੱਬਾ;

    ਜੇ (src == dst) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Can't change YUV plane types in-place");
    }

    ਜੇ (!GetYUVPlanes(ਚੌੜਾਈ, ਉਚਾਈ, src_format, src, src_pitch,
                      &srcY1, &srcU, &srcV, &srcY_pitch, &srcUV_pitch)) {
        ਵਾਪਸ false;
    }
    srcY2 = srcY1 + srcY_pitch;
    src_Y_pitch_ਖੱਬਾ = (srcY_pitch - ਚੌੜਾਈ);

    ਜੇ (src_format == SDL_PIXELFORMAT_NV12 || src_format == SDL_PIXELFORMAT_NV21) {
        srcUV_pixel_stride = 2;
        src_UV_pitch_ਖੱਬਾ = (srcUV_pitch - 2 * ((ਚੌੜਾਈ + 1) / 2));
    } ਨਹੀਂਤਾਂ {
        srcUV_pixel_stride = 1;
        src_UV_pitch_ਖੱਬਾ = (srcUV_pitch - ((ਚੌੜਾਈ + 1) / 2));
    }

    ਜੇ (!GetYUVPlanes(ਚੌੜਾਈ, ਉਚਾਈ, dst_format, dst, dst_pitch,
                      (ਅਚਲ Uint8 **)&dstY1, (ਅਚਲ Uint8 **)&dstU1, (ਅਚਲ Uint8 **)&dstV1,
                      &dstY_pitch, &dstUV_pitch)) {
        ਵਾਪਸ false;
    }
    dstY2 = dstY1 + dstY_pitch;
    dstU2 = dstU1 + dstUV_pitch;
    dstV2 = dstV1 + dstUV_pitch;
    dst_pitch_ਖੱਬਾ = (dstY_pitch - 4 * ((ਚੌੜਾਈ + 1) / 2));

    // Copy 2x2 blocks of pixels at a time
    ਲਈ (y = 0; y < (ਉਚਾਈ - 1); y += 2) {
        ਲਈ (x = 0; x < (ਚੌੜਾਈ - 1); x += 2) {
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
        ਜੇ (x == (ਚੌੜਾਈ - 1)) {
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

        srcY1 += src_Y_pitch_ਖੱਬਾ + srcY_pitch;
        srcY2 += src_Y_pitch_ਖੱਬਾ + srcY_pitch;
        srcU += src_UV_pitch_ਖੱਬਾ;
        srcV += src_UV_pitch_ਖੱਬਾ;
        dstY1 += dst_pitch_ਖੱਬਾ + dstY_pitch;
        dstY2 += dst_pitch_ਖੱਬਾ + dstY_pitch;
        dstU1 += dst_pitch_ਖੱਬਾ + dstUV_pitch;
        dstU2 += dst_pitch_ਖੱਬਾ + dstUV_pitch;
        dstV1 += dst_pitch_ਖੱਬਾ + dstUV_pitch;
        dstV2 += dst_pitch_ਖੱਬਾ + dstUV_pitch;
    }

    // Last row
    ਜੇ (y == (ਉਚਾਈ - 1)) {
        ਲਈ (x = 0; x < (ਚੌੜਾਈ - 1); x += 2) {
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
        ਜੇ (x == (ਚੌੜਾਈ - 1)) {
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
    ਵਾਪਸ true;
}

ਸਥਿਰ bool SDL_Convert_Pixels_Packed4_ਮੰਜ਼ਿਲ_Planar2x2(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ,
                                                   SDL_PixelFormat src_format, ਅਚਲ ਖਾਲੀ *src, ਪੂਰਨ src_pitch,
                                                   SDL_PixelFormat dst_format, ਖਾਲੀ *dst, ਪੂਰਨ dst_pitch)
{
    ਪੂਰਨ x, y;
    ਅਚਲ Uint8 *srcY1, *srcY2, *srcU1, *srcU2, *srcV1, *srcV2;
    Uint32 srcY_pitch, srcUV_pitch;
    Uint32 src_pitch_ਖੱਬਾ;
    Uint8 *dstY1, *dstY2, *dstU, *dstV;
    Uint32 dstY_pitch, dstUV_pitch;
    Uint32 dst_Y_pitch_ਖੱਬਾ, dst_UV_pitch_ਖੱਬਾ, dstUV_pixel_stride;

    ਜੇ (src == dst) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Can't change YUV plane types in-place");
    }

    ਜੇ (!GetYUVPlanes(ਚੌੜਾਈ, ਉਚਾਈ, src_format, src, src_pitch,
                      &srcY1, &srcU1, &srcV1, &srcY_pitch, &srcUV_pitch)) {
        ਵਾਪਸ false;
    }
    srcY2 = srcY1 + srcY_pitch;
    srcU2 = srcU1 + srcUV_pitch;
    srcV2 = srcV1 + srcUV_pitch;
    src_pitch_ਖੱਬਾ = (srcY_pitch - 4 * ((ਚੌੜਾਈ + 1) / 2));

    ਜੇ (!GetYUVPlanes(ਚੌੜਾਈ, ਉਚਾਈ, dst_format, dst, dst_pitch,
                      (ਅਚਲ Uint8 **)&dstY1, (ਅਚਲ Uint8 **)&dstU, (ਅਚਲ Uint8 **)&dstV,
                      &dstY_pitch, &dstUV_pitch)) {
        ਵਾਪਸ false;
    }
    dstY2 = dstY1 + dstY_pitch;
    dst_Y_pitch_ਖੱਬਾ = (dstY_pitch - ਚੌੜਾਈ);

    ਜੇ (dst_format == SDL_PIXELFORMAT_NV12 || dst_format == SDL_PIXELFORMAT_NV21) {
        dstUV_pixel_stride = 2;
        dst_UV_pitch_ਖੱਬਾ = (dstUV_pitch - 2 * ((ਚੌੜਾਈ + 1) / 2));
    } ਨਹੀਂਤਾਂ {
        dstUV_pixel_stride = 1;
        dst_UV_pitch_ਖੱਬਾ = (dstUV_pitch - ((ਚੌੜਾਈ + 1) / 2));
    }

    // Copy 2x2 blocks of pixels at a time
    ਲਈ (y = 0; y < (ਉਚਾਈ - 1); y += 2) {
        ਲਈ (x = 0; x < (ਚੌੜਾਈ - 1); x += 2) {
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
        ਜੇ (x == (ਚੌੜਾਈ - 1)) {
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

        srcY1 += src_pitch_ਖੱਬਾ + srcY_pitch;
        srcY2 += src_pitch_ਖੱਬਾ + srcY_pitch;
        srcU1 += src_pitch_ਖੱਬਾ + srcUV_pitch;
        srcU2 += src_pitch_ਖੱਬਾ + srcUV_pitch;
        srcV1 += src_pitch_ਖੱਬਾ + srcUV_pitch;
        srcV2 += src_pitch_ਖੱਬਾ + srcUV_pitch;
        dstY1 += dst_Y_pitch_ਖੱਬਾ + dstY_pitch;
        dstY2 += dst_Y_pitch_ਖੱਬਾ + dstY_pitch;
        dstU += dst_UV_pitch_ਖੱਬਾ;
        dstV += dst_UV_pitch_ਖੱਬਾ;
    }

    // Last row
    ਜੇ (y == (ਉਚਾਈ - 1)) {
        ਲਈ (x = 0; x < (ਚੌੜਾਈ - 1); x += 2) {
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
        ਜੇ (x == (ਚੌੜਾਈ - 1)) {
            *dstY1 = *srcY1;
            *dstU = *srcU1;
            *dstV = *srcV1;
        }
    }
    ਵਾਪਸ true;
}

#ਜੇ_ਅੰਤ // SDL_HAVE_YUV

bool SDL_Convert_Pixels_YUV_ਮੰਜ਼ਿਲ_YUV(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ,
                                  SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ਅਚਲ ਖਾਲੀ *src, ਪੂਰਨ src_pitch,
                                  SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, ਖਾਲੀ *dst, ਪੂਰਨ dst_pitch)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_HAVE_YUV
    ਜੇ (src_colorspace != dst_colorspace) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("SDL_ConvertPixels_YUV_to_YUV: colorspace conversion not supported");
    }

    ਜੇ (src_format == dst_format) {
        ਜੇ (src == dst) {
            // Nothing to do
            ਵਾਪਸ true;
        }
        ਵਾਪਸ SDL_Convert_Pixels_YUV_ਮੰਜ਼ਿਲ_YUV_Copy(ਚੌੜਾਈ, ਉਚਾਈ, src_format, src, src_pitch, dst, dst_pitch);
    }

    ਜੇ (IsPlanar2x2Format(src_format) && IsPlanar2x2Format(dst_format)) {
        ਵਾਪਸ SDL_Convert_Pixels_Planar2x2_ਮੰਜ਼ਿਲ_Planar2x2(ਚੌੜਾਈ, ਉਚਾਈ, src_format, src, src_pitch, dst_format, dst, dst_pitch);
    } ਨਹੀਂਤਾਂ ਜੇ (IsPacked4Format(src_format) && IsPacked4Format(dst_format)) {
        ਵਾਪਸ SDL_Convert_Pixels_Packed4_ਮੰਜ਼ਿਲ_Packed4(ਚੌੜਾਈ, ਉਚਾਈ, src_format, src, src_pitch, dst_format, dst, dst_pitch);
    } ਨਹੀਂਤਾਂ ਜੇ (IsPlanar2x2Format(src_format) && IsPacked4Format(dst_format)) {
        ਵਾਪਸ SDL_Convert_Pixels_Planar2x2_ਮੰਜ਼ਿਲ_Packed4(ਚੌੜਾਈ, ਉਚਾਈ, src_format, src, src_pitch, dst_format, dst, dst_pitch);
    } ਨਹੀਂਤਾਂ ਜੇ (IsPacked4Format(src_format) && IsPlanar2x2Format(dst_format)) {
        ਵਾਪਸ SDL_Convert_Pixels_Packed4_ਮੰਜ਼ਿਲ_Planar2x2(ਚੌੜਾਈ, ਉਚਾਈ, src_format, src, src_pitch, dst_format, dst, dst_pitch);
    } ਨਹੀਂਤਾਂ {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("SDL_ConvertPixels_YUV_to_YUV: Unsupported YUV conversion: %s -> %s", SDL_GetPixelFormatName(src_format),
                            SDL_GetPixelFormatName(dst_format));
    }
#ਨਹੀਂਤਾਂ
    ਵਾਪਸ SDL_ਸੈੱਟ_Error("SDL not built with YUV support");
#ਜੇ_ਅੰਤ
}
