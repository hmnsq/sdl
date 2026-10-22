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
    ಹಿಂತಿರುಗಿ format == SDL_PIXELFORMAT_I444 || format == SDL_PIXELFORMAT_I4FL;
}

ಸ್ಥಿರ bool IsPlanar2x2Format(SDL_PixelFormat format)
{
    ಹಿಂತಿರುಗಿ format == SDL_PIXELFORMAT_YV12 ||
           format == SDL_PIXELFORMAT_IYUV ||
           format == SDL_PIXELFORMAT_NV12 ||
           format == SDL_PIXELFORMAT_NV21 ||
           format == SDL_PIXELFORMAT_P010 ||
           format == SDL_PIXELFORMAT_I0FL;
}

ಸ್ಥಿರ bool IsPacked4Format(Uint32 format)
{
    ಹಿಂತಿರುಗಿ format == SDL_PIXELFORMAT_YUY2 || format == SDL_PIXELFORMAT_UYVY || format == SDL_PIXELFORMAT_YVYU;
}

/*
 * Calculate YUV size and pitch. Check for overflow.
 * Output 'pitch' that can be used with SDL_ConvertPixels()
 */
bool SDL_CalculateYUVSize(SDL_PixelFormat format, ಪೂರ್ಣಾಂಕ w, ಪೂರ್ಣಾಂಕ h, size_t *ಗಾತ್ರ_2, size_t *pitch)
{
    ಪೂರ್ಣಾಂಕ sz_plane = 0, sz_plane_chroma = 0, sz_plane_packed = 0;

    ಆದರೆ (IsPlanar1x1Format(format)) {
        /* sz_plane == w * h * bpp; */
        size_t s1;
        ಆದರೆ (!SDL_ಗಾತ್ರ_mul_check_ಅತಿಪ್ರವಾಹ(w, h, &s1)) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("width * height would overflow");
        }
        ಆದರೆ (!SDL_ಗಾತ್ರ_mul_check_ಅತಿಪ್ರವಾಹ(s1, SDL_BYTESPERPIXEL(format), &s1)) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("width * height * bpp would overflow");
        }
        sz_plane = (ಪೂರ್ಣಾಂಕ)s1;
        sz_plane_chroma = sz_plane;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (IsPlanar2x2Format(format)) {
        {
            /* sz_plane == w * h * bpp; */
            size_t s1;
            ಆದರೆ (!SDL_ಗಾತ್ರ_mul_check_ಅತಿಪ್ರವಾಹ(w, h, &s1)) {
                ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("width * height would overflow");
            }
            ಆದರೆ (!SDL_ಗಾತ್ರ_mul_check_ಅತಿಪ್ರವಾಹ(s1, SDL_BYTESPERPIXEL(format), &s1)) {
                ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("width * height * bpp would overflow");
            }
            sz_plane = (ಪೂರ್ಣಾಂಕ)s1;
        }

        {
            /* sz_plane_chroma == ((w + 1) / 2) * ((h + 1) / 2) * bpp; */
            size_t s1, s2, s3;
            ಆದರೆ (!SDL_ಗಾತ್ರ_ಕೂಡಿಸು_check_ಅತಿಪ್ರವಾಹ(w, 1, &s1)) {
                ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("width + 1 would overflow");
            }
            s1 = s1 / 2;
            ಆದರೆ (!SDL_ಗಾತ್ರ_ಕೂಡಿಸು_check_ಅತಿಪ್ರವಾಹ(h, 1, &s2)) {
                ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("height + 1 would overflow");
            }
            s2 = s2 / 2;
            ಆದರೆ (!SDL_ಗಾತ್ರ_mul_check_ಅತಿಪ್ರವಾಹ(s1, s2, &s3)) {
                ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("width * height would overflow");
            }
            ಆದರೆ (!SDL_ಗಾತ್ರ_mul_check_ಅತಿಪ್ರವಾಹ(s3, SDL_BYTESPERPIXEL(format), &s3)) {
                ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("width * height * bpp would overflow");
            }
            sz_plane_chroma = (ಪೂರ್ಣಾಂಕ)s3;
        }
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (IsPacked4Format(format)) {
        /* sz_plane_packed == ((w + 1) / 2) * h; */
        size_t s1, s2;
        ಆದರೆ (!SDL_ಗಾತ್ರ_ಕೂಡಿಸು_check_ಅತಿಪ್ರವಾಹ(w, 1, &s1)) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("width + 1 would overflow");
        }
        s1 = s1 / 2;
        ಆದರೆ (!SDL_ಗಾತ್ರ_mul_check_ಅತಿಪ್ರವಾಹ(s1, h, &s2)) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("width * height would overflow");
        }
        sz_plane_packed = (ಪೂರ್ಣಾಂಕ) s2;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ SDL_Unsupported();
    }

    ಆಯ್ಕೆ (format) {
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_YV12: /**< Planar mode: Y + V + U  (3 planes) */
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_IYUV: /**< Planar mode: Y + U + V  (3 planes) */
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_I444: /**< Planar mode: Y + U + V  (3 planes) */
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_I0FL: /**< Planar mode: Y + U + V  (3 planes) */
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_I4FL: /**< Planar mode: Y + U + V  (3 planes) */

        ಆದರೆ (pitch) {
            *pitch = w * SDL_BYTESPERPIXEL(format);
        }

        ಆದರೆ (ಗಾತ್ರ_2) {
            // dst_size == sz_plane + sz_plane_chroma + sz_plane_chroma;
            size_t s1, s2;
            ಆದರೆ (!SDL_ಗಾತ್ರ_ಕೂಡಿಸು_check_ಅತಿಪ್ರವಾಹ(sz_plane, sz_plane_chroma, &s1)) {
                ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Y + U would overflow");
            }
            ಆದರೆ (!SDL_ಗಾತ್ರ_ಕೂಡಿಸು_check_ಅತಿಪ್ರವಾಹ(s1, sz_plane_chroma, &s2)) {
                ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Y + U + V would overflow");
            }
            *ಗಾತ್ರ_2 = (ಪೂರ್ಣಾಂಕ)s2;
        }
        ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ SDL_PIXELFORMAT_YUY2: /**< Packed mode: Y0+U0+Y1+V0 (1 plane) */
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_UYVY: /**< Packed mode: U0+Y0+V0+Y1 (1 plane) */
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_YVYU: /**< Packed mode: Y0+V0+Y1+U0 (1 plane) */

        ಆದರೆ (pitch) {
            /* pitch == ((w + 1) / 2) * 4; */
           size_t p1, p2;
           ಆದರೆ (!SDL_ಗಾತ್ರ_ಕೂಡಿಸು_check_ಅತಿಪ್ರವಾಹ(w, 1, &p1)) {
               ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("width + 1 would overflow");
           }
           p1 = p1 / 2;
           ಆದರೆ (!SDL_ಗಾತ್ರ_mul_check_ಅತಿಪ್ರವಾಹ(p1, 4, &p2)) {
               ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("width * 4 would overflow");
           }
           *pitch = p2;
        }

        ಆದರೆ (ಗಾತ್ರ_2) {
            /* dst_size == 4 * sz_plane_packed; */
            size_t s1;
            ಆದರೆ (!SDL_ಗಾತ್ರ_mul_check_ಅತಿಪ್ರವಾಹ(sz_plane_packed, 4, &s1)) {
                ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("plane * 4 would overflow");
            }
            *ಗಾತ್ರ_2 = (ಪೂರ್ಣಾಂಕ) s1;
        }
        ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ SDL_PIXELFORMAT_NV12: /**< Planar mode: Y + U/V interleaved  (2 planes) */
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_NV21: /**< Planar mode: Y + V/U interleaved  (2 planes) */
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_P010: /**< Planar mode: Y + U/V interleaved, 10 bit  (2 planes) */
        ಆದರೆ (pitch) {
            *pitch = w * SDL_BYTESPERPIXEL(format);
        }

        ಆದರೆ (ಗಾತ್ರ_2) {
            // dst_size == sz_plane + sz_plane_chroma + sz_plane_chroma;
            size_t s1, s2;
            ಆದರೆ (!SDL_ಗಾತ್ರ_ಕೂಡಿಸು_check_ಅತಿಪ್ರವಾಹ(sz_plane, sz_plane_chroma, &s1)) {
                ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Y + U would overflow");
            }
            ಆದರೆ (!SDL_ಗಾತ್ರ_ಕೂಡಿಸು_check_ಅತಿಪ್ರವಾಹ(s1, sz_plane_chroma, &s2)) {
                ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Y + U + V would overflow");
            }
            *ಗಾತ್ರ_2 = (ಪೂರ್ಣಾಂಕ) s2;
        }
        ನಿಲ್ಲಿಸು;

    ಪೂರ್ವನಿಯೋಜಿತ:
        ಹಿಂತಿರುಗಿ SDL_Unsupported();
    }

    ಹಿಂತಿರುಗಿ true;
}

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_HAVE_YUV

ಸ್ಥಿರ bool GetYUVConversionType(SDL_Colorspace colorspace, ಪೂರ್ಣಾಂಕ w, ಪೂರ್ಣಾಂಕ h, ಪೂರ್ಣಾಂಕ ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_pixel, YCbCrType *yuv_type)
{
    ಆದರೆ (SDL_ISCOLORSPACE_ಮಾತೃಕೆ_BT601(colorspace)) {
        ಆದರೆ (SDL_ISCOLORSPACE_LIMITED_RANGE(colorspace)) {
            *yuv_type = YCBCR_601_LIMITED;
        } ಇಲ್ಲದಿದ್ದರೆ {
            *yuv_type = YCBCR_601_ತುಂಬಿದ;
        }
        ಹಿಂತಿರುಗಿ true;
    }

    ಆದರೆ (SDL_ISCOLORSPACE_ಮಾತೃಕೆ_BT709(colorspace)) {
        ಆದರೆ (SDL_ISCOLORSPACE_LIMITED_RANGE(colorspace)) {
            *yuv_type = YCBCR_709_LIMITED;
        } ಇಲ್ಲದಿದ್ದರೆ {
            *yuv_type = YCBCR_709_ತುಂಬಿದ;
        }
        ಹಿಂತಿರುಗಿ true;
    }

    ಆದರೆ (SDL_ISCOLORSPACE_ಮಾತೃಕೆ_BT2020_NCL(colorspace)) {
        ಆದರೆ (SDL_ISCOLORSPACE_ತುಂಬಿದ_RANGE(colorspace)) {
            *yuv_type = YCBCR_2020_NCL_ತುಂಬಿದ;
            ಹಿಂತಿರುಗಿ true;
        }
    }

    ಆದರೆ (SDL_COLORSPACEMATRIX(colorspace) == SDL_ಮಾತೃಕೆ_COEFFICIENTS_UNSPECIFIED) {
        ಆಯ್ಕೆ (ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_pixel) {
        ಸ್ಥಿತಿ 8:
            ಆದರೆ (h <= YUV_SD_ಮಿತಿ) {
                ಆದರೆ (SDL_ISCOLORSPACE_LIMITED_RANGE(colorspace)) {
                    *yuv_type = YCBCR_601_LIMITED;
                } ಇಲ್ಲದಿದ್ದರೆ {
                    *yuv_type = YCBCR_601_ತುಂಬಿದ;
                }
            } ಇಲ್ಲದಿದ್ದರೆ {
                ಆದರೆ (SDL_ISCOLORSPACE_LIMITED_RANGE(colorspace)) {
                    *yuv_type = YCBCR_709_LIMITED;
                } ಇಲ್ಲದಿದ್ದರೆ {
                    *yuv_type = YCBCR_709_ತುಂಬಿದ;
                }
            }
			ಹಿಂತಿರುಗಿ true;
        ಸ್ಥಿತಿ 10:
        ಸ್ಥಿತಿ 16:
            ಆದರೆ (SDL_ISCOLORSPACE_ತುಂಬಿದ_RANGE(colorspace)) {
                *yuv_type = YCBCR_2020_NCL_ತುಂಬಿದ;
                ಹಿಂತಿರುಗಿ true;
            }
            ನಿಲ್ಲಿಸು;
        ಪೂರ್ವನಿಯೋಜಿತ:
            ನಿಲ್ಲಿಸು;
        }
    }

    ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Unsupported YUV colorspace");
}

ಸ್ಥಿರ bool GetYUVPlanes(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, SDL_PixelFormat format, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *yuv, ಪೂರ್ಣಾಂಕ yuv_pitch,
                         ಸ್ಥಿರಾಂಕ Uint8 **y, ಸ್ಥಿರಾಂಕ Uint8 **u, ಸ್ಥಿರಾಂಕ Uint8 **v, Uint32 *y_stride, Uint32 *uv_stride)
{
    ಸ್ಥಿರಾಂಕ Uint8 *planes[3] = { ಖಾಲಿ, ಖಾಲಿ, ಖಾಲಿ };
    ಪೂರ್ಣಾಂಕ pitches[3] = { 0, 0, 0 };
    ಪೂರ್ಣಾಂಕ uv_ಅಗಲ;

    ಆಯ್ಕೆ (format) {
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_YV12:
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_IYUV:
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_I0FL:
        pitches[0] = yuv_pitch;
        pitches[1] = ((pitches[0] / SDL_BYTESPERPIXEL(format) + 1) / 2) * SDL_BYTESPERPIXEL(format);
        pitches[2] = pitches[1];
        planes[0] = (ಸ್ಥಿರಾಂಕ Uint8 *)yuv;
        planes[1] = planes[0] + pitches[0] * ಎತ್ತರ;
        planes[2] = planes[1] + pitches[1] * ((ಎತ್ತರ + 1) / 2);
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_YUY2:
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_UYVY:
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_YVYU:
        pitches[0] = yuv_pitch;
        planes[0] = (ಸ್ಥಿರಾಂಕ Uint8 *)yuv;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_NV12:
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_NV21:
        pitches[0] = yuv_pitch;
        pitches[1] = 2 * ((pitches[0] + 1) / 2);
        planes[0] = (ಸ್ಥಿರಾಂಕ Uint8 *)yuv;
        planes[1] = planes[0] + pitches[0] * ಎತ್ತರ;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_P010:
        pitches[0] = yuv_pitch;
        uv_ಅಗಲ = ((ಅಗಲ + 1) / 2) * 2;
        pitches[1] = SDL_max(pitches[0], (ಪೂರ್ಣಾಂಕ)(uv_ಅಗಲ * ಗಾತ್ರ(Uint16)));
        planes[0] = (ಸ್ಥಿರಾಂಕ Uint8 *)yuv;
        planes[1] = planes[0] + pitches[0] * ಎತ್ತರ;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_I444:
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_I4FL:
        pitches[0] = yuv_pitch;
        pitches[1] = pitches[0];
        pitches[2] = pitches[1];
        planes[0] = (ಸ್ಥಿರಾಂಕ Uint8 *)yuv;
        planes[1] = planes[0] + pitches[0] * ಎತ್ತರ;
        planes[2] = planes[1] + pitches[1] * ಎತ್ತರ;
        ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("GetYUVPlanes(): Unsupported YUV format: %s", SDL_GetPixelFormatName(format));
    }

    ಆಯ್ಕೆ (format) {
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_YV12:
        *y = planes[0];
        *y_stride = pitches[0];
        *v = planes[1];
        *u = planes[2];
        *uv_stride = pitches[1];
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_IYUV:
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_I444:
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_I0FL:
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_I4FL:
        *y = planes[0];
        *y_stride = pitches[0];
        *v = planes[2];
        *u = planes[1];
        *uv_stride = pitches[1];
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_YUY2:
        *y = planes[0];
        *y_stride = pitches[0];
        *v = *y + 3;
        *u = *y + 1;
        *uv_stride = pitches[0];
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_UYVY:
        *y = planes[0] + 1;
        *y_stride = pitches[0];
        *v = *y + 1;
        *u = *y - 1;
        *uv_stride = pitches[0];
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_YVYU:
        *y = planes[0];
        *y_stride = pitches[0];
        *v = *y + 1;
        *u = *y + 3;
        *uv_stride = pitches[0];
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_NV12:
        *y = planes[0];
        *y_stride = pitches[0];
        *u = planes[1];
        *v = *u + 1;
        *uv_stride = pitches[1];
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_NV21:
        *y = planes[0];
        *y_stride = pitches[0];
        *v = planes[1];
        *u = *v + 1;
        *uv_stride = pitches[1];
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_P010:
        *y = planes[0];
        *y_stride = pitches[0];
        *u = planes[1];
        *v = *u + ಗಾತ್ರ(Uint16);
        *uv_stride = pitches[1];
        ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        // Should have caught this above
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("GetYUVPlanes[2]: Unsupported YUV format: %s", SDL_GetPixelFormatName(format));
    }
    ಹಿಂತಿರುಗಿ true;
}

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_SSE2_INTRINSICS
ಸ್ಥಿರ bool SDL_TARGETING("sse2") yuv_rgb_sse(
    SDL_PixelFormat src_format, SDL_PixelFormat dst_format,
    Uint32 ಅಗಲ, Uint32 ಎತ್ತರ,
    ಸ್ಥಿರಾಂಕ Uint8 *y, ಸ್ಥಿರಾಂಕ Uint8 *u, ಸ್ಥಿರಾಂಕ Uint8 *v, Uint32 y_stride, Uint32 uv_stride,
    Uint8 *rgb, Uint32 rgb_stride,
    YCbCrType yuv_type)
{
    ಆದರೆ (!SDL_HasSSE2()) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಆದರೆ (src_format == SDL_PIXELFORMAT_YV12 ||
        src_format == SDL_PIXELFORMAT_IYUV) {

        ಆಯ್ಕೆ (dst_format) {
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGB565:
            yuv420_rgb565_sseu(ಅಗಲ, ಎತ್ತರ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಹಿಂತಿರುಗಿ true;
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGB24:
            yuv420_rgb24_sseu(ಅಗಲ, ಎತ್ತರ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಹಿಂತಿರುಗಿ true;
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGBX8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGBA8888:
            yuv420_rgba_sseu(ಅಗಲ, ಎತ್ತರ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಹಿಂತಿರುಗಿ true;
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_BGRX8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_BGRA8888:
            yuv420_bgra_sseu(ಅಗಲ, ಎತ್ತರ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಹಿಂತಿರುಗಿ true;
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_XRGB8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_ARGB8888:
            yuv420_argb_sseu(ಅಗಲ, ಎತ್ತರ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಹಿಂತಿರುಗಿ true;
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_XBGR8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_ABGR8888:
            yuv420_abgr_sseu(ಅಗಲ, ಎತ್ತರ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಹಿಂತಿರುಗಿ true;
        ಪೂರ್ವನಿಯೋಜಿತ:
            ನಿಲ್ಲಿಸು;
        }
    }

    ಆದರೆ (src_format == SDL_PIXELFORMAT_YUY2 ||
        src_format == SDL_PIXELFORMAT_UYVY ||
        src_format == SDL_PIXELFORMAT_YVYU) {

        ಆಯ್ಕೆ (dst_format) {
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGB565:
            yuv422_rgb565_sseu(ಅಗಲ, ಎತ್ತರ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಹಿಂತಿರುಗಿ true;
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGB24:
            yuv422_rgb24_sseu(ಅಗಲ, ಎತ್ತರ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಹಿಂತಿರುಗಿ true;
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGBX8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGBA8888:
            yuv422_rgba_sseu(ಅಗಲ, ಎತ್ತರ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಹಿಂತಿರುಗಿ true;
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_BGRX8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_BGRA8888:
            yuv422_bgra_sseu(ಅಗಲ, ಎತ್ತರ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಹಿಂತಿರುಗಿ true;
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_XRGB8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_ARGB8888:
            yuv422_argb_sseu(ಅಗಲ, ಎತ್ತರ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಹಿಂತಿರುಗಿ true;
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_XBGR8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_ABGR8888:
            yuv422_abgr_sseu(ಅಗಲ, ಎತ್ತರ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಹಿಂತಿರುಗಿ true;
        ಪೂರ್ವನಿಯೋಜಿತ:
            ನಿಲ್ಲಿಸು;
        }
    }

    ಆದರೆ (src_format == SDL_PIXELFORMAT_NV12 ||
        src_format == SDL_PIXELFORMAT_NV21) {

        ಆಯ್ಕೆ (dst_format) {
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGB565:
            yuvnv12_rgb565_sseu(ಅಗಲ, ಎತ್ತರ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಹಿಂತಿರುಗಿ true;
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGB24:
            yuvnv12_rgb24_sseu(ಅಗಲ, ಎತ್ತರ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಹಿಂತಿರುಗಿ true;
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGBX8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGBA8888:
            yuvnv12_rgba_sseu(ಅಗಲ, ಎತ್ತರ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಹಿಂತಿರುಗಿ true;
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_BGRX8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_BGRA8888:
            yuvnv12_bgra_sseu(ಅಗಲ, ಎತ್ತರ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಹಿಂತಿರುಗಿ true;
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_XRGB8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_ARGB8888:
            yuvnv12_argb_sseu(ಅಗಲ, ಎತ್ತರ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಹಿಂತಿರುಗಿ true;
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_XBGR8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_ABGR8888:
            yuvnv12_abgr_sseu(ಅಗಲ, ಎತ್ತರ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಹಿಂತಿರುಗಿ true;
        ಪೂರ್ವನಿಯೋಜಿತ:
            ನಿಲ್ಲಿಸು;
        }
    }
    ಹಿಂತಿರುಗಿ false;
}
#ಇಲ್ಲದಿದ್ದರೆ
ಸ್ಥಿರ bool yuv_rgb_sse(
    SDL_PixelFormat src_format, SDL_PixelFormat dst_format,
    Uint32 ಅಗಲ, Uint32 ಎತ್ತರ,
    ಸ್ಥಿರಾಂಕ Uint8 *y, ಸ್ಥಿರಾಂಕ Uint8 *u, ಸ್ಥಿರಾಂಕ Uint8 *v, Uint32 y_stride, Uint32 uv_stride,
    Uint8 *rgb, Uint32 rgb_stride,
    YCbCrType yuv_type)
{
    ಹಿಂತಿರುಗಿ false;
}
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_LSX_INTRINSICS
ಸ್ಥಿರ bool yuv_rgb_lsx(
    SDL_PixelFormat src_format, SDL_PixelFormat dst_format,
    Uint32 ಅಗಲ, Uint32 ಎತ್ತರ,
    ಸ್ಥಿರಾಂಕ Uint8 *y, ಸ್ಥಿರಾಂಕ Uint8 *u, ಸ್ಥಿರಾಂಕ Uint8 *v, Uint32 y_stride, Uint32 uv_stride,
    Uint8 *rgb, Uint32 rgb_stride,
    YCbCrType yuv_type)
{
    ಆದರೆ (!SDL_HasLSX()) {
        ಹಿಂತಿರುಗಿ false;
    }
    ಆದರೆ (src_format == SDL_PIXELFORMAT_YV12 ||
        src_format == SDL_PIXELFORMAT_IYUV) {

        ಆಯ್ಕೆ (dst_format) {
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGB24:
            yuv420_rgb24_lsx(ಅಗಲ, ಎತ್ತರ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಹಿಂತಿರುಗಿ true;
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGBX8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGBA8888:
            yuv420_rgba_lsx(ಅಗಲ, ಎತ್ತರ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಹಿಂತಿರುಗಿ true;
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_BGRX8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_BGRA8888:
            yuv420_bgra_lsx(ಅಗಲ, ಎತ್ತರ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಹಿಂತಿರುಗಿ true;
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_XRGB8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_ARGB8888:
            yuv420_argb_lsx(ಅಗಲ, ಎತ್ತರ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಹಿಂತಿರುಗಿ true;
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_XBGR8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_ABGR8888:
            yuv420_abgr_lsx(ಅಗಲ, ಎತ್ತರ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಹಿಂತಿರುಗಿ true;
        ಪೂರ್ವನಿಯೋಜಿತ:
            ನಿಲ್ಲಿಸು;
        }
    }
    ಹಿಂತಿರುಗಿ false;
}
#ಇಲ್ಲದಿದ್ದರೆ
ಸ್ಥಿರ bool yuv_rgb_lsx(
    SDL_PixelFormat src_format, SDL_PixelFormat dst_format,
    Uint32 ಅಗಲ, Uint32 ಎತ್ತರ,
    ಸ್ಥಿರಾಂಕ Uint8 *y, ಸ್ಥಿರಾಂಕ Uint8 *u, ಸ್ಥಿರಾಂಕ Uint8 *v, Uint32 y_stride, Uint32 uv_stride,
    Uint8 *rgb, Uint32 rgb_stride,
    YCbCrType yuv_type)
{
    ಹಿಂತಿರುಗಿ false;
}
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ bool yuv_rgb_std(
    SDL_PixelFormat src_format, SDL_PixelFormat dst_format,
    Uint32 ಅಗಲ, Uint32 ಎತ್ತರ,
    ಸ್ಥಿರಾಂಕ Uint8 *y, ಸ್ಥಿರಾಂಕ Uint8 *u, ಸ್ಥಿರಾಂಕ Uint8 *v, Uint32 y_stride, Uint32 uv_stride,
    Uint8 *rgb, Uint32 rgb_stride,
    YCbCrType yuv_type)
{
    ಆದರೆ (src_format == SDL_PIXELFORMAT_YV12 ||
        src_format == SDL_PIXELFORMAT_IYUV) {

        ಆಯ್ಕೆ (dst_format) {
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGB565:
            yuv420_rgb565_std(ಅಗಲ, ಎತ್ತರ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಹಿಂತಿರುಗಿ true;
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGB24:
            yuv420_rgb24_std(ಅಗಲ, ಎತ್ತರ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಹಿಂತಿರುಗಿ true;
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGBX8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGBA8888:
            yuv420_rgba_std(ಅಗಲ, ಎತ್ತರ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಹಿಂತಿರುಗಿ true;
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_BGRX8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_BGRA8888:
            yuv420_bgra_std(ಅಗಲ, ಎತ್ತರ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಹಿಂತಿರುಗಿ true;
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_XRGB8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_ARGB8888:
            yuv420_argb_std(ಅಗಲ, ಎತ್ತರ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಹಿಂತಿರುಗಿ true;
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_XBGR8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_ABGR8888:
            yuv420_abgr_std(ಅಗಲ, ಎತ್ತರ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಹಿಂತಿರುಗಿ true;
        ಪೂರ್ವನಿಯೋಜಿತ:
            ನಿಲ್ಲಿಸು;
        }
    }

    ಆದರೆ (src_format == SDL_PIXELFORMAT_I444) {

        ಆಯ್ಕೆ (dst_format) {
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGBX8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGBA8888:
            yuv444_rgba_std(ಅಗಲ, ಎತ್ತರ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಹಿಂತಿರುಗಿ true;
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_BGRX8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_BGRA8888:
            yuv444_bgra_std(ಅಗಲ, ಎತ್ತರ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಹಿಂತಿರುಗಿ true;
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_XRGB8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_ARGB8888:
            yuv444_argb_std(ಅಗಲ, ಎತ್ತರ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಹಿಂತಿರುಗಿ true;
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_XBGR8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_ABGR8888:
            yuv444_abgr_std(ಅಗಲ, ಎತ್ತರ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಹಿಂತಿರುಗಿ true;
        ಪೂರ್ವನಿಯೋಜಿತ:
            ನಿಲ್ಲಿಸು;
        }
    }

    ಆದರೆ (src_format == SDL_PIXELFORMAT_YUY2 ||
        src_format == SDL_PIXELFORMAT_UYVY ||
        src_format == SDL_PIXELFORMAT_YVYU) {

        ಆಯ್ಕೆ (dst_format) {
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGB565:
            yuv422_rgb565_std(ಅಗಲ, ಎತ್ತರ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಹಿಂತಿರುಗಿ true;
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGB24:
            yuv422_rgb24_std(ಅಗಲ, ಎತ್ತರ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಹಿಂತಿರುಗಿ true;
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGBX8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGBA8888:
            yuv422_rgba_std(ಅಗಲ, ಎತ್ತರ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಹಿಂತಿರುಗಿ true;
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_BGRX8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_BGRA8888:
            yuv422_bgra_std(ಅಗಲ, ಎತ್ತರ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಹಿಂತಿರುಗಿ true;
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_XRGB8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_ARGB8888:
            yuv422_argb_std(ಅಗಲ, ಎತ್ತರ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಹಿಂತಿರುಗಿ true;
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_XBGR8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_ABGR8888:
            yuv422_abgr_std(ಅಗಲ, ಎತ್ತರ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಹಿಂತಿರುಗಿ true;
        ಪೂರ್ವನಿಯೋಜಿತ:
            ನಿಲ್ಲಿಸು;
        }
    }

    ಆದರೆ (src_format == SDL_PIXELFORMAT_NV12 ||
        src_format == SDL_PIXELFORMAT_NV21) {

        ಆಯ್ಕೆ (dst_format) {
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGB565:
            yuvnv12_rgb565_std(ಅಗಲ, ಎತ್ತರ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಹಿಂತಿರುಗಿ true;
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGB24:
            yuvnv12_rgb24_std(ಅಗಲ, ಎತ್ತರ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಹಿಂತಿರುಗಿ true;
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGBX8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGBA8888:
            yuvnv12_rgba_std(ಅಗಲ, ಎತ್ತರ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಹಿಂತಿರುಗಿ true;
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_BGRX8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_BGRA8888:
            yuvnv12_bgra_std(ಅಗಲ, ಎತ್ತರ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಹಿಂತಿರುಗಿ true;
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_XRGB8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_ARGB8888:
            yuvnv12_argb_std(ಅಗಲ, ಎತ್ತರ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಹಿಂತಿರುಗಿ true;
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_XBGR8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_ABGR8888:
            yuvnv12_abgr_std(ಅಗಲ, ಎತ್ತರ, y, u, v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಹಿಂತಿರುಗಿ true;
        ಪೂರ್ವನಿಯೋಜಿತ:
            ನಿಲ್ಲಿಸು;
        }
    }

    ಆದರೆ (src_format == SDL_PIXELFORMAT_P010) {
        ಆಯ್ಕೆ (dst_format) {
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_XBGR2101010:
            yuvp010_xbgr2101010_std(ಅಗಲ, ಎತ್ತರ, (ಸ್ಥಿರಾಂಕ uint16_t *)y, (ಸ್ಥಿರಾಂಕ uint16_t *)u, (ಸ್ಥಿರಾಂಕ uint16_t *)v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಹಿಂತಿರುಗಿ true;
        ಪೂರ್ವನಿಯೋಜಿತ:
            ನಿಲ್ಲಿಸು;
        }
    }

    ಆದರೆ (src_format == SDL_PIXELFORMAT_I0FL) {
        ಆಯ್ಕೆ (dst_format) {
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGB48:
            yuvi0fl_rgb48_std(ಅಗಲ, ಎತ್ತರ, (ಸ್ಥಿರಾಂಕ uint16_t *)y, (ಸ್ಥಿರಾಂಕ uint16_t *)u, (ಸ್ಥಿರಾಂಕ uint16_t *)v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಹಿಂತಿರುಗಿ true;
        ಪೂರ್ವನಿಯೋಜಿತ:
            ನಿಲ್ಲಿಸು;
        }
    }

    ಆದರೆ (src_format == SDL_PIXELFORMAT_I4FL) {
        ಆಯ್ಕೆ (dst_format) {
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGB48:
            yuvi4fl_rgb48_std(ಅಗಲ, ಎತ್ತರ, (ಸ್ಥಿರಾಂಕ uint16_t *)y, (ಸ್ಥಿರಾಂಕ uint16_t *)u, (ಸ್ಥಿರಾಂಕ uint16_t *)v, y_stride, uv_stride, rgb, rgb_stride, yuv_type);
            ಹಿಂತಿರುಗಿ true;
        ಪೂರ್ವನಿಯೋಜಿತ:
            ನಿಲ್ಲಿಸು;
        }
    }
    ಹಿಂತಿರುಗಿ false;
}

bool SDL_Convert_Pixels_YUV_ಗಮ್ಯ_RGB(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ,
                                  SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಂಕ src_pitch,
                                  SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಂಕ dst_pitch)
{
    ಸ್ಥಿರಾಂಕ Uint8 *y = ಖಾಲಿ;
    ಸ್ಥಿರಾಂಕ Uint8 *u = ಖಾಲಿ;
    ಸ್ಥಿರಾಂಕ Uint8 *v = ಖಾಲಿ;
    Uint32 y_stride = 0;
    Uint32 uv_stride = 0;
    YCbCrType yuv_type = YCBCR_601_LIMITED;

    ಆದರೆ (!GetYUVPlanes(ಅಗಲ, ಎತ್ತರ, src_format, src, src_pitch, &y, &u, &v, &y_stride, &uv_stride)) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಆದರೆ (!GetYUVConversionType(src_colorspace, ಅಗಲ, ಎತ್ತರ, 8, &yuv_type)) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಆದರೆ (yuv_rgb_sse(src_format, dst_format, ಅಗಲ, ಎತ್ತರ, y, u, v, y_stride, uv_stride, (Uint8 *)dst, dst_pitch, yuv_type)) {
        ಹಿಂತಿರುಗಿ true;
    }

    ಆದರೆ (yuv_rgb_lsx(src_format, dst_format, ಅಗಲ, ಎತ್ತರ, y, u, v, y_stride, uv_stride, (Uint8 *)dst, dst_pitch, yuv_type)) {
        ಹಿಂತಿರುಗಿ true;
    }

    ಆದರೆ (yuv_rgb_std(src_format, dst_format, ಅಗಲ, ಎತ್ತರ, y, u, v, y_stride, uv_stride, (Uint8 *)dst, dst_pitch, yuv_type)) {
        ಹಿಂತಿರುಗಿ true;
    }

    // No fast path for the RGB format, instead convert using an intermediate buffer
    ಆದರೆ (src_format == SDL_PIXELFORMAT_P010 && dst_format != SDL_PIXELFORMAT_XBGR2101010) {
        bool ಫಲಿತಾಂಶ;
        ಶೂನ್ಯ *tmp;
        ಪೂರ್ಣಾಂಕ tmp_pitch = (ಅಗಲ * ಗಾತ್ರ(Uint32));

        tmp = SDL_malloc((size_t)tmp_pitch * ಎತ್ತರ);
        ಆದರೆ (!tmp) {
            ಹಿಂತಿರುಗಿ false;
        }

        // convert src/src_format to tmp/XBGR2101010
        ಫಲಿತಾಂಶ = SDL_Convert_Pixels_YUV_ಗಮ್ಯ_RGB(ಅಗಲ, ಎತ್ತರ, src_format, src_colorspace, src_properties, src, src_pitch, SDL_PIXELFORMAT_XBGR2101010, src_colorspace, src_properties, tmp, tmp_pitch);
        ಆದರೆ (!ಫಲಿತಾಂಶ) {
            SDL_free(tmp);
            ಹಿಂತಿರುಗಿ false;
        }

        // convert tmp/XBGR2101010 to dst/RGB
        ಫಲಿತಾಂಶ = SDL_ConvertPixelsAndColorspace(ಅಗಲ, ಎತ್ತರ, SDL_PIXELFORMAT_XBGR2101010, src_colorspace, src_properties, tmp, tmp_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
        SDL_free(tmp);
        ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
    }

    ಆದರೆ ((src_format == SDL_PIXELFORMAT_I0FL || src_format == SDL_PIXELFORMAT_I4FL) && dst_format != SDL_PIXELFORMAT_RGB48) {
        bool ಫಲಿತಾಂಶ;
        ಶೂನ್ಯ *tmp;
        ಪೂರ್ಣಾಂಕ tmp_pitch = (ಅಗಲ * 3 * ಗಾತ್ರ(Uint16));

        tmp = SDL_malloc((size_t)tmp_pitch * ಎತ್ತರ);
        ಆದರೆ (!tmp) {
            ಹಿಂತಿರುಗಿ false;
        }

        // convert src/src_format to tmp/RGB48
        ಫಲಿತಾಂಶ = SDL_Convert_Pixels_YUV_ಗಮ್ಯ_RGB(ಅಗಲ, ಎತ್ತರ, src_format, src_colorspace, src_properties, src, src_pitch, SDL_PIXELFORMAT_RGB48, src_colorspace, src_properties, tmp, tmp_pitch);
        ಆದರೆ (!ಫಲಿತಾಂಶ) {
            SDL_free(tmp);
            ಹಿಂತಿರುಗಿ false;
        }

        // convert tmp/RGB48 to dst/RGB
        ಫಲಿತಾಂಶ = SDL_ConvertPixelsAndColorspace(ಅಗಲ, ಎತ್ತರ, SDL_PIXELFORMAT_RGB48, src_colorspace, src_properties, tmp, tmp_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
        SDL_free(tmp);
        ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
    }

    ಆದರೆ (dst_format != SDL_PIXELFORMAT_ARGB8888) {
        bool ಫಲಿತಾಂಶ;
        ಶೂನ್ಯ *tmp;
        ಪೂರ್ಣಾಂಕ tmp_pitch = (ಅಗಲ * ಗಾತ್ರ(Uint32));

        tmp = SDL_malloc((size_t)tmp_pitch * ಎತ್ತರ);
        ಆದರೆ (!tmp) {
            ಹಿಂತಿರುಗಿ false;
        }

        // convert src/src_format to tmp/ARGB8888
        ಫಲಿತಾಂಶ = SDL_Convert_Pixels_YUV_ಗಮ್ಯ_RGB(ಅಗಲ, ಎತ್ತರ, src_format, src_colorspace, src_properties, src, src_pitch, SDL_PIXELFORMAT_ARGB8888, SDL_COLORSPACE_SRGB, 0, tmp, tmp_pitch);
        ಆದರೆ (!ಫಲಿತಾಂಶ) {
            SDL_free(tmp);
            ಹಿಂತಿರುಗಿ false;
        }

        // convert tmp/ARGB8888 to dst/RGB
        ಫಲಿತಾಂಶ = SDL_ConvertPixelsAndColorspace(ಅಗಲ, ಎತ್ತರ, SDL_PIXELFORMAT_ARGB8888, SDL_COLORSPACE_SRGB, 0, tmp, tmp_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
        SDL_free(tmp);
        ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
    }

    ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Unsupported YUV conversion");
}

ರಚನೆ RGB2YUVFactors
{
    ಪೂರ್ಣಾಂಕ y_ಸ್ಥಾನಾಂತರ;
    ದಶಮಾಂಶ y[3]; // Rfactor, Gfactor, Bfactor
    ದಶಮಾಂಶ u[3]; // Rfactor, Gfactor, Bfactor
    ದಶಮಾಂಶ v[3]; // Rfactor, Gfactor, Bfactor
};

ಸ್ಥಿರ ರಚನೆ RGB2YUVFactors RGB2YUVFactorTables[] = {
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

ಸ್ಥಿರ bool SDL_Convert_Pixels_XRGB8888_ಗಮ್ಯ_YUV(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಂಕ src_pitch, SDL_PixelFormat dst_format, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಂಕ dst_pitch, YCbCrType yuv_type)
{
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ src_pitch_x_2 = src_pitch * 2;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ ಎತ್ತರ_half = ಎತ್ತರ / 2;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ ಎತ್ತರ_remainder = (ಎತ್ತರ & 0x1);
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ ಅಗಲ_half = ಅಗಲ / 2;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ ಅಗಲ_remainder = (ಅಗಲ & 0x1);
    ಪೂರ್ಣಾಂಕ i, j;

    ಸ್ಥಿರಾಂಕ ರಚನೆ RGB2YUVFactors *cvt = &RGB2YUVFactorTables[yuv_type];

#ವ್ಯಾಖ್ಯಾನಿಸು MAKE_Y(r, g, b) (Uint8)SDL_clamp(((ಪೂರ್ಣಾಂಕ)(cvt->y[0] * (r) + cvt->y[1] * (g) + cvt->y[2] * (b) + 0.5f) + cvt->y_ಸ್ಥಾನಾಂತರ), 0, 255)
#ವ್ಯಾಖ್ಯಾನಿಸು MAKE_U(r, g, b) (Uint8)SDL_clamp(((ಪೂರ್ಣಾಂಕ)(cvt->u[0] * (r) + cvt->u[1] * (g) + cvt->u[2] * (b) + 0.5f) + 128), 0, 255)
#ವ್ಯಾಖ್ಯಾನಿಸು MAKE_V(r, g, b) (Uint8)SDL_clamp(((ಪೂರ್ಣಾಂಕ)(cvt->v[0] * (r) + cvt->v[1] * (g) + cvt->v[2] * (b) + 0.5f) + 128), 0, 255)

#ವ್ಯಾಖ್ಯಾನಿಸು READ_2x2_PIXELS                                                                                     \
    ಸ್ಥಿರಾಂಕ Uint32 p1 = ((ಸ್ಥಿರಾಂಕ Uint32 *)curr_ಅಡ್ಡಸಾಲು)[2 * i];                                                    \
    ಸ್ಥಿರಾಂಕ Uint32 p2 = ((ಸ್ಥಿರಾಂಕ Uint32 *)curr_ಅಡ್ಡಸಾಲು)[2 * i + 1];                                                \
    ಸ್ಥಿರಾಂಕ Uint32 p3 = ((ಸ್ಥಿರಾಂಕ Uint32 *)ಮುಂದಿನ_ಅಡ್ಡಸಾಲು)[2 * i];                                                    \
    ಸ್ಥಿರಾಂಕ Uint32 p4 = ((ಸ್ಥಿರಾಂಕ Uint32 *)ಮುಂದಿನ_ಅಡ್ಡಸಾಲು)[2 * i + 1];                                                \
    ಸ್ಥಿರಾಂಕ Uint32 r = ((p1 & 0x00ff0000) + (p2 & 0x00ff0000) + (p3 & 0x00ff0000) + (p4 & 0x00ff0000)) >> 18; \
    ಸ್ಥಿರಾಂಕ Uint32 g = ((p1 & 0x0000ff00) + (p2 & 0x0000ff00) + (p3 & 0x0000ff00) + (p4 & 0x0000ff00)) >> 10; \
    ಸ್ಥಿರಾಂಕ Uint32 b = ((p1 & 0x000000ff) + (p2 & 0x000000ff) + (p3 & 0x000000ff) + (p4 & 0x000000ff)) >> 2

#ವ್ಯಾಖ್ಯಾನಿಸು READ_2x1_PIXELS                                             \
    ಸ್ಥಿರಾಂಕ Uint32 p1 = ((ಸ್ಥಿರಾಂಕ Uint32 *)curr_ಅಡ್ಡಸಾಲು)[2 * i];            \
    ಸ್ಥಿರಾಂಕ Uint32 p2 = ((ಸ್ಥಿರಾಂಕ Uint32 *)ಮುಂದಿನ_ಅಡ್ಡಸಾಲು)[2 * i];            \
    ಸ್ಥಿರಾಂಕ Uint32 r = ((p1 & 0x00ff0000) + (p2 & 0x00ff0000)) >> 17; \
    ಸ್ಥಿರಾಂಕ Uint32 g = ((p1 & 0x0000ff00) + (p2 & 0x0000ff00)) >> 9;  \
    ಸ್ಥಿರಾಂಕ Uint32 b = ((p1 & 0x000000ff) + (p2 & 0x000000ff)) >> 1

#ವ್ಯಾಖ್ಯಾನಿಸು READ_1x2_PIXELS                                             \
    ಸ್ಥಿರಾಂಕ Uint32 p1 = ((ಸ್ಥಿರಾಂಕ Uint32 *)curr_ಅಡ್ಡಸಾಲು)[2 * i];            \
    ಸ್ಥಿರಾಂಕ Uint32 p2 = ((ಸ್ಥಿರಾಂಕ Uint32 *)curr_ಅಡ್ಡಸಾಲು)[2 * i + 1];        \
    ಸ್ಥಿರಾಂಕ Uint32 r = ((p1 & 0x00ff0000) + (p2 & 0x00ff0000)) >> 17; \
    ಸ್ಥಿರಾಂಕ Uint32 g = ((p1 & 0x0000ff00) + (p2 & 0x0000ff00)) >> 9;  \
    ಸ್ಥಿರಾಂಕ Uint32 b = ((p1 & 0x000000ff) + (p2 & 0x000000ff)) >> 1

#ವ್ಯಾಖ್ಯಾನಿಸು READ_1x1_PIXEL                                  \
    ಸ್ಥಿರಾಂಕ Uint32 p = ((ಸ್ಥಿರಾಂಕ Uint32 *)curr_ಅಡ್ಡಸಾಲು)[2 * i]; \
    ಸ್ಥಿರಾಂಕ Uint32 r = (p & 0x00ff0000) >> 16;            \
    ಸ್ಥಿರಾಂಕ Uint32 g = (p & 0x0000ff00) >> 8;             \
    ಸ್ಥಿರಾಂಕ Uint32 b = (p & 0x000000ff)

#ವ್ಯಾಖ್ಯಾನಿಸು READ_TWO_RGB_PIXELS                                  \
    ಸ್ಥಿರಾಂಕ Uint32 p = ((ಸ್ಥಿರಾಂಕ Uint32 *)curr_ಅಡ್ಡಸಾಲು)[2 * i];      \
    ಸ್ಥಿರಾಂಕ Uint32 r = (p & 0x00ff0000) >> 16;                 \
    ಸ್ಥಿರಾಂಕ Uint32 g = (p & 0x0000ff00) >> 8;                  \
    ಸ್ಥಿರಾಂಕ Uint32 b = (p & 0x000000ff);                       \
    ಸ್ಥಿರಾಂಕ Uint32 p1 = ((ಸ್ಥಿರಾಂಕ Uint32 *)curr_ಅಡ್ಡಸಾಲು)[2 * i + 1]; \
    ಸ್ಥಿರಾಂಕ Uint32 r1 = (p1 & 0x00ff0000) >> 16;               \
    ಸ್ಥಿರಾಂಕ Uint32 g1 = (p1 & 0x0000ff00) >> 8;                \
    ಸ್ಥಿರಾಂಕ Uint32 b1 = (p1 & 0x000000ff);                     \
    ಸ್ಥಿರಾಂಕ Uint32 R = (r + r1) / 2;                           \
    ಸ್ಥಿರಾಂಕ Uint32 G = (g + g1) / 2;                           \
    ಸ್ಥಿರಾಂಕ Uint32 B = (b + b1) / 2

#ವ್ಯಾಖ್ಯಾನಿಸು READ_ONE_RGB_PIXEL READ_1x1_PIXEL

    ಆಯ್ಕೆ (dst_format) {
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_YV12:
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_IYUV:
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_I444:
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_NV12:
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_NV21:
    {
        ಸ್ಥಿರಾಂಕ Uint8 *curr_ಅಡ್ಡಸಾಲು, *ಮುಂದಿನ_ಅಡ್ಡಸಾಲು;

        Uint8 *plane_y;
        Uint8 *plane_u;
        Uint8 *plane_v;
        Uint8 *plane_interleaved_uv;
        Uint32 y_stride, uv_stride, y_skip, uv_skip;

        ಆದರೆ (!GetYUVPlanes(ಅಗಲ, ಎತ್ತರ, dst_format, dst, dst_pitch,
                          (ಸ್ಥಿರಾಂಕ Uint8 **)&plane_y, (ಸ್ಥಿರಾಂಕ Uint8 **)&plane_u, (ಸ್ಥಿರಾಂಕ Uint8 **)&plane_v,
                          &y_stride, &uv_stride)) {
            ಹಿಂತಿರುಗಿ false;
        }

        plane_interleaved_uv = (plane_y + ಎತ್ತರ * y_stride);
        y_skip = (y_stride - ಅಗಲ);

        curr_ಅಡ್ಡಸಾಲು = (ಸ್ಥಿರಾಂಕ Uint8 *)src;

        // Write Y plane
        ಗಾಗಿ (j = 0; j < ಎತ್ತರ; j++) {
            ಗಾಗಿ (i = 0; i < ಅಗಲ; i++) {
                ಸ್ಥಿರಾಂಕ Uint32 p1 = ((ಸ್ಥಿರಾಂಕ Uint32 *)curr_ಅಡ್ಡಸಾಲು)[i];
                ಸ್ಥಿರಾಂಕ Uint32 r = (p1 & 0x00ff0000) >> 16;
                ಸ್ಥಿರಾಂಕ Uint32 g = (p1 & 0x0000ff00) >> 8;
                ಸ್ಥಿರಾಂಕ Uint32 b = (p1 & 0x000000ff);
                *plane_y++ = MAKE_Y(r, g, b);
            }
            plane_y += y_skip;
            curr_ಅಡ್ಡಸಾಲು += src_pitch;
        }

        curr_ಅಡ್ಡಸಾಲು = (ಸ್ಥಿರಾಂಕ Uint8 *)src;
        ಮುಂದಿನ_ಅಡ್ಡಸಾಲು = (ಸ್ಥಿರಾಂಕ Uint8 *)src;
        ಮುಂದಿನ_ಅಡ್ಡಸಾಲು += src_pitch;

        ಆದರೆ (dst_format == SDL_PIXELFORMAT_YV12 || dst_format == SDL_PIXELFORMAT_IYUV) {
            // Write UV planes, not interleaved
            uv_skip = (uv_stride - (ಅಗಲ + 1) / 2);
            ಗಾಗಿ (j = 0; j < ಎತ್ತರ_half; j++) {
                ಗಾಗಿ (i = 0; i < ಅಗಲ_half; i++) {
                    READ_2x2_PIXELS;
                    *plane_u++ = MAKE_U(r, g, b);
                    *plane_v++ = MAKE_V(r, g, b);
                }
                ಆದರೆ (ಅಗಲ_remainder) {
                    READ_2x1_PIXELS;
                    *plane_u++ = MAKE_U(r, g, b);
                    *plane_v++ = MAKE_V(r, g, b);
                }
                plane_u += uv_skip;
                plane_v += uv_skip;
                curr_ಅಡ್ಡಸಾಲು += src_pitch_x_2;
                ಮುಂದಿನ_ಅಡ್ಡಸಾಲು += src_pitch_x_2;
            }
            ಆದರೆ (ಎತ್ತರ_remainder) {
                ಗಾಗಿ (i = 0; i < ಅಗಲ_half; i++) {
                    READ_1x2_PIXELS;
                    *plane_u++ = MAKE_U(r, g, b);
                    *plane_v++ = MAKE_V(r, g, b);
                }
                ಆದರೆ (ಅಗಲ_remainder) {
                    READ_1x1_PIXEL;
                    *plane_u++ = MAKE_U(r, g, b);
                    *plane_v++ = MAKE_V(r, g, b);
                }
                plane_u += uv_skip;
                plane_v += uv_skip;
            }
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (dst_format == SDL_PIXELFORMAT_I444) {
            // Write UV planes, not interleaved
            uv_skip = (uv_stride - ಅಗಲ);
            ಗಾಗಿ (j = 0; j < ಎತ್ತರ; j++) {
                ಗಾಗಿ (i = 0; i < ಅಗಲ; i++) {
                    ಸ್ಥಿರಾಂಕ Uint32 p1 = ((ಸ್ಥಿರಾಂಕ Uint32 *)curr_ಅಡ್ಡಸಾಲು)[i];
                    ಸ್ಥಿರಾಂಕ Uint32 r = (p1 & 0x00ff0000) >> 16;
                    ಸ್ಥಿರಾಂಕ Uint32 g = (p1 & 0x0000ff00) >> 8;
                    ಸ್ಥಿರಾಂಕ Uint32 b = (p1 & 0x000000ff);
                    *plane_u++ = MAKE_U(r, g, b);
                    *plane_v++ = MAKE_V(r, g, b);
                }
                plane_u += uv_skip;
                plane_v += uv_skip;
                curr_ಅಡ್ಡಸಾಲು += src_pitch;
            }
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (dst_format == SDL_PIXELFORMAT_NV12) {
            uv_skip = (uv_stride - ((ಅಗಲ + 1) / 2) * 2);
            ಗಾಗಿ (j = 0; j < ಎತ್ತರ_half; j++) {
                ಗಾಗಿ (i = 0; i < ಅಗಲ_half; i++) {
                    READ_2x2_PIXELS;
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                }
                ಆದರೆ (ಅಗಲ_remainder) {
                    READ_2x1_PIXELS;
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                }
                plane_interleaved_uv += uv_skip;
                curr_ಅಡ್ಡಸಾಲು += src_pitch_x_2;
                ಮುಂದಿನ_ಅಡ್ಡಸಾಲು += src_pitch_x_2;
            }
            ಆದರೆ (ಎತ್ತರ_remainder) {
                ಗಾಗಿ (i = 0; i < ಅಗಲ_half; i++) {
                    READ_1x2_PIXELS;
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                }
                ಆದರೆ (ಅಗಲ_remainder) {
                    READ_1x1_PIXEL;
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                }
            }
        } ಇಲ್ಲದಿದ್ದರೆ /* dst_format == SDL_PIXELFORMAT_NV21 */ {
            uv_skip = (uv_stride - ((ಅಗಲ + 1) / 2) * 2);
            ಗಾಗಿ (j = 0; j < ಎತ್ತರ_half; j++) {
                ಗಾಗಿ (i = 0; i < ಅಗಲ_half; i++) {
                    READ_2x2_PIXELS;
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                }
                ಆದರೆ (ಅಗಲ_remainder) {
                    READ_2x1_PIXELS;
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                }
                plane_interleaved_uv += uv_skip;
                curr_ಅಡ್ಡಸಾಲು += src_pitch_x_2;
                ಮುಂದಿನ_ಅಡ್ಡಸಾಲು += src_pitch_x_2;
            }
            ಆದರೆ (ಎತ್ತರ_remainder) {
                ಗಾಗಿ (i = 0; i < ಅಗಲ_half; i++) {
                    READ_1x2_PIXELS;
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                }
                ಆದರೆ (ಅಗಲ_remainder) {
                    READ_1x1_PIXEL;
                    *plane_interleaved_uv++ = MAKE_V(r, g, b);
                    *plane_interleaved_uv++ = MAKE_U(r, g, b);
                }
            }
        }
    } ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ SDL_PIXELFORMAT_YUY2:
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_UYVY:
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_YVYU:
    {
        ಸ್ಥಿರಾಂಕ Uint8 *curr_ಅಡ್ಡಸಾಲು = (ಸ್ಥಿರಾಂಕ Uint8 *)src;
        Uint8 *plane = (Uint8 *)dst;
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ ಅಡ್ಡಸಾಲು_ಗಾತ್ರ = (4 * ((ಅಗಲ + 1) / 2));
        ಪೂರ್ಣಾಂಕ plane_skip;

        ಆದರೆ (dst_pitch < ಅಡ್ಡಸಾಲು_ಗಾತ್ರ) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Destination pitch is too small, expected at least %d", ಅಡ್ಡಸಾಲು_ಗಾತ್ರ);
        }
        plane_skip = (dst_pitch - ಅಡ್ಡಸಾಲು_ಗಾತ್ರ);

        // Write YUV plane, packed
        ಆದರೆ (dst_format == SDL_PIXELFORMAT_YUY2) {
            ಗಾಗಿ (j = 0; j < ಎತ್ತರ; j++) {
                ಗಾಗಿ (i = 0; i < ಅಗಲ_half; i++) {
                    READ_TWO_RGB_PIXELS;
                    // Y U Y1 V
                    *plane++ = MAKE_Y(r, g, b);
                    *plane++ = MAKE_U(R, G, B);
                    *plane++ = MAKE_Y(r1, g1, b1);
                    *plane++ = MAKE_V(R, G, B);
                }
                ಆದರೆ (ಅಗಲ_remainder) {
                    READ_ONE_RGB_PIXEL;
                    // Y U Y V
                    *plane++ = MAKE_Y(r, g, b);
                    *plane++ = MAKE_U(r, g, b);
                    *plane++ = MAKE_Y(r, g, b);
                    *plane++ = MAKE_V(r, g, b);
                }
                plane += plane_skip;
                curr_ಅಡ್ಡಸಾಲು += src_pitch;
            }
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (dst_format == SDL_PIXELFORMAT_UYVY) {
            ಗಾಗಿ (j = 0; j < ಎತ್ತರ; j++) {
                ಗಾಗಿ (i = 0; i < ಅಗಲ_half; i++) {
                    READ_TWO_RGB_PIXELS;
                    // U Y V Y1
                    *plane++ = MAKE_U(R, G, B);
                    *plane++ = MAKE_Y(r, g, b);
                    *plane++ = MAKE_V(R, G, B);
                    *plane++ = MAKE_Y(r1, g1, b1);
                }
                ಆದರೆ (ಅಗಲ_remainder) {
                    READ_ONE_RGB_PIXEL;
                    // U Y V Y
                    *plane++ = MAKE_U(r, g, b);
                    *plane++ = MAKE_Y(r, g, b);
                    *plane++ = MAKE_V(r, g, b);
                    *plane++ = MAKE_Y(r, g, b);
                }
                plane += plane_skip;
                curr_ಅಡ್ಡಸಾಲು += src_pitch;
            }
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (dst_format == SDL_PIXELFORMAT_YVYU) {
            ಗಾಗಿ (j = 0; j < ಎತ್ತರ; j++) {
                ಗಾಗಿ (i = 0; i < ಅಗಲ_half; i++) {
                    READ_TWO_RGB_PIXELS;
                    // Y V Y1 U
                    *plane++ = MAKE_Y(r, g, b);
                    *plane++ = MAKE_V(R, G, B);
                    *plane++ = MAKE_Y(r1, g1, b1);
                    *plane++ = MAKE_U(R, G, B);
                }
                ಆದರೆ (ಅಗಲ_remainder) {
                    READ_ONE_RGB_PIXEL;
                    // Y V Y U
                    *plane++ = MAKE_Y(r, g, b);
                    *plane++ = MAKE_V(r, g, b);
                    *plane++ = MAKE_Y(r, g, b);
                    *plane++ = MAKE_U(r, g, b);
                }
                plane += plane_skip;
                curr_ಅಡ್ಡಸಾಲು += src_pitch;
            }
        }
    } ನಿಲ್ಲಿಸು;

    ಪೂರ್ವನಿಯೋಜಿತ:
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Unsupported YUV destination format: %s", SDL_GetPixelFormatName(dst_format));
    }
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು MAKE_Y
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು MAKE_U
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು MAKE_V
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು READ_2x2_PIXELS
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು READ_2x1_PIXELS
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು READ_1x2_PIXELS
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು READ_1x1_PIXEL
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು READ_TWO_RGB_PIXELS
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು READ_ONE_RGB_PIXEL
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool SDL_Convert_Pixels_XBGR2101010_ಗಮ್ಯ_P010(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಂಕ src_pitch, SDL_PixelFormat dst_format, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಂಕ dst_pitch, YCbCrType yuv_type)
{
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ src_pitch_x_2 = src_pitch * 2;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ ಎತ್ತರ_half = ಎತ್ತರ / 2;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ ಎತ್ತರ_remainder = (ಎತ್ತರ & 0x1);
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ ಅಗಲ_half = ಅಗಲ / 2;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ ಅಗಲ_remainder = (ಅಗಲ & 0x1);
    ಪೂರ್ಣಾಂಕ i, j;

    ಸ್ಥಿರಾಂಕ ರಚನೆ RGB2YUVFactors *cvt = &RGB2YUVFactorTables[yuv_type];

#ವ್ಯಾಖ್ಯಾನಿಸು MAKE_Y(r, g, b) (Uint16)(((ಪೂರ್ಣಾಂಕ)(cvt->y[0] * (r) + cvt->y[1] * (g) + cvt->y[2] * (b) + 0.5f) + cvt->y_ಸ್ಥಾನಾಂತರ) << 6)
#ವ್ಯಾಖ್ಯಾನಿಸು MAKE_U(r, g, b) (Uint16)(((ಪೂರ್ಣಾಂಕ)(cvt->u[0] * (r) + cvt->u[1] * (g) + cvt->u[2] * (b) + 0.5f) + 512) << 6)
#ವ್ಯಾಖ್ಯಾನಿಸು MAKE_V(r, g, b) (Uint16)(((ಪೂರ್ಣಾಂಕ)(cvt->v[0] * (r) + cvt->v[1] * (g) + cvt->v[2] * (b) + 0.5f) + 512) << 6)

#ವ್ಯಾಖ್ಯಾನಿಸು READ_2x2_PIXELS                                                                                     \
    ಸ್ಥಿರಾಂಕ Uint32 p1 = ((ಸ್ಥಿರಾಂಕ Uint32 *)curr_ಅಡ್ಡಸಾಲು)[2 * i];                                                    \
    ಸ್ಥಿರಾಂಕ Uint32 p2 = ((ಸ್ಥಿರಾಂಕ Uint32 *)curr_ಅಡ್ಡಸಾಲು)[2 * i + 1];                                                \
    ಸ್ಥಿರಾಂಕ Uint32 p3 = ((ಸ್ಥಿರಾಂಕ Uint32 *)ಮುಂದಿನ_ಅಡ್ಡಸಾಲು)[2 * i];                                                    \
    ಸ್ಥಿರಾಂಕ Uint32 p4 = ((ಸ್ಥಿರಾಂಕ Uint32 *)ಮುಂದಿನ_ಅಡ್ಡಸಾಲು)[2 * i + 1];                                                \
    ಸ್ಥಿರಾಂಕ Uint32 r = ((p1 & 0x000003ff) + (p2 & 0x000003ff) + (p3 & 0x000003ff) + (p4 & 0x000003ff)) >> 2;  \
    ಸ್ಥಿರಾಂಕ Uint32 g = ((p1 & 0x000ffc00) + (p2 & 0x000ffc00) + (p3 & 0x000ffc00) + (p4 & 0x000ffc00)) >> 12; \
    ಸ್ಥಿರಾಂಕ Uint32 b = ((p1 & 0x3ff00000) + (p2 & 0x3ff00000) + (p3 & 0x3ff00000) + (p4 & 0x3ff00000)) >> 22

#ವ್ಯಾಖ್ಯಾನಿಸು READ_2x1_PIXELS                                             \
    ಸ್ಥಿರಾಂಕ Uint32 p1 = ((ಸ್ಥಿರಾಂಕ Uint32 *)curr_ಅಡ್ಡಸಾಲು)[2 * i];            \
    ಸ್ಥಿರಾಂಕ Uint32 p2 = ((ಸ್ಥಿರಾಂಕ Uint32 *)ಮುಂದಿನ_ಅಡ್ಡಸಾಲು)[2 * i];            \
    ಸ್ಥಿರಾಂಕ Uint32 r = ((p1 & 0x000003ff) + (p2 & 0x000003ff)) >> 1;  \
    ಸ್ಥಿರಾಂಕ Uint32 g = ((p1 & 0x000ffc00) + (p2 & 0x000ffc00)) >> 11; \
    ಸ್ಥಿರಾಂಕ Uint32 b = ((p1 & 0x3ff00000) + (p2 & 0x3ff00000)) >> 21

#ವ್ಯಾಖ್ಯಾನಿಸು READ_1x2_PIXELS                                             \
    ಸ್ಥಿರಾಂಕ Uint32 p1 = ((ಸ್ಥಿರಾಂಕ Uint32 *)curr_ಅಡ್ಡಸಾಲು)[2 * i];            \
    ಸ್ಥಿರಾಂಕ Uint32 p2 = ((ಸ್ಥಿರಾಂಕ Uint32 *)curr_ಅಡ್ಡಸಾಲು)[2 * i + 1];        \
    ಸ್ಥಿರಾಂಕ Uint32 r = ((p1 & 0x000003ff) + (p2 & 0x000003ff)) >> 1;  \
    ಸ್ಥಿರಾಂಕ Uint32 g = ((p1 & 0x000ffc00) + (p2 & 0x000ffc00)) >> 11; \
    ಸ್ಥಿರಾಂಕ Uint32 b = ((p1 & 0x3ff00000) + (p2 & 0x3ff00000)) >> 21

#ವ್ಯಾಖ್ಯಾನಿಸು READ_1x1_PIXEL                                  \
    ಸ್ಥಿರಾಂಕ Uint32 p = ((ಸ್ಥಿರಾಂಕ Uint32 *)curr_ಅಡ್ಡಸಾಲು)[2 * i]; \
    ಸ್ಥಿರಾಂಕ Uint32 r = (p & 0x000003ff);                  \
    ಸ್ಥಿರಾಂಕ Uint32 g = (p & 0x000ffc00) >> 10;            \
    ಸ್ಥಿರಾಂಕ Uint32 b = (p & 0x3ff00000) >> 20

    ಸ್ಥಿರಾಂಕ Uint8 *curr_ಅಡ್ಡಸಾಲು, *ಮುಂದಿನ_ಅಡ್ಡಸಾಲು;

    Uint16 *plane_y;
    Uint16 *plane_u;
    Uint16 *plane_v;
    Uint16 *plane_interleaved_uv;
    Uint32 y_stride, uv_stride, y_skip, uv_skip;

    ಆದರೆ (!GetYUVPlanes(ಅಗಲ, ಎತ್ತರ, dst_format, dst, dst_pitch,
                      (ಸ್ಥಿರಾಂಕ Uint8 **)&plane_y, (ಸ್ಥಿರಾಂಕ Uint8 **)&plane_u, (ಸ್ಥಿರಾಂಕ Uint8 **)&plane_v,
                      &y_stride, &uv_stride)) {
        ಹಿಂತಿರುಗಿ false;
    }

    y_stride /= ಗಾತ್ರ(Uint16);
    uv_stride /= ಗಾತ್ರ(Uint16);

    plane_interleaved_uv = (plane_y + ಎತ್ತರ * y_stride);
    y_skip = (y_stride - ಅಗಲ);

    curr_ಅಡ್ಡಸಾಲು = (ಸ್ಥಿರಾಂಕ Uint8 *)src;

    // Write Y plane
    ಗಾಗಿ (j = 0; j < ಎತ್ತರ; j++) {
        ಗಾಗಿ (i = 0; i < ಅಗಲ; i++) {
            ಸ್ಥಿರಾಂಕ Uint32 p1 = ((ಸ್ಥಿರಾಂಕ Uint32 *)curr_ಅಡ್ಡಸಾಲು)[i];
            ಸ್ಥಿರಾಂಕ Uint32 r = (p1 >>  0) & 0x03ff;
            ಸ್ಥಿರಾಂಕ Uint32 g = (p1 >> 10) & 0x03ff;
            ಸ್ಥಿರಾಂಕ Uint32 b = (p1 >> 20) & 0x03ff;
            *plane_y++ = MAKE_Y(r, g, b);
        }
        plane_y += y_skip;
        curr_ಅಡ್ಡಸಾಲು += src_pitch;
    }

    curr_ಅಡ್ಡಸಾಲು = (ಸ್ಥಿರಾಂಕ Uint8 *)src;
    ಮುಂದಿನ_ಅಡ್ಡಸಾಲು = (ಸ್ಥಿರಾಂಕ Uint8 *)src;
    ಮುಂದಿನ_ಅಡ್ಡಸಾಲು += src_pitch;

    uv_skip = (uv_stride - ((ಅಗಲ + 1) / 2) * 2);
    ಗಾಗಿ (j = 0; j < ಎತ್ತರ_half; j++) {
        ಗಾಗಿ (i = 0; i < ಅಗಲ_half; i++) {
            READ_2x2_PIXELS;
            *plane_interleaved_uv++ = MAKE_U(r, g, b);
            *plane_interleaved_uv++ = MAKE_V(r, g, b);
        }
        ಆದರೆ (ಅಗಲ_remainder) {
            READ_2x1_PIXELS;
            *plane_interleaved_uv++ = MAKE_U(r, g, b);
            *plane_interleaved_uv++ = MAKE_V(r, g, b);
        }
        plane_interleaved_uv += uv_skip;
        curr_ಅಡ್ಡಸಾಲು += src_pitch_x_2;
        ಮುಂದಿನ_ಅಡ್ಡಸಾಲು += src_pitch_x_2;
    }
    ಆದರೆ (ಎತ್ತರ_remainder) {
        ಗಾಗಿ (i = 0; i < ಅಗಲ_half; i++) {
            READ_1x2_PIXELS;
            *plane_interleaved_uv++ = MAKE_U(r, g, b);
            *plane_interleaved_uv++ = MAKE_V(r, g, b);
        }
        ಆದರೆ (ಅಗಲ_remainder) {
            READ_1x1_PIXEL;
            *plane_interleaved_uv++ = MAKE_U(r, g, b);
            *plane_interleaved_uv++ = MAKE_V(r, g, b);
        }
    }

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು MAKE_Y
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು MAKE_U
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು MAKE_V
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು READ_2x2_PIXELS
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು READ_2x1_PIXELS
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು READ_1x2_PIXELS
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು READ_1x1_PIXEL
    ಹಿಂತಿರುಗಿ true;
}

bool SDL_Convert_Pixels_RGB_ಗಮ್ಯ_YUV(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ,
                                  SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಂಕ src_pitch,
                                  SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಂಕ dst_pitch)
{
    YCbCrType yuv_type = YCBCR_601_LIMITED;

    ಆದರೆ (!GetYUVConversionType(dst_colorspace, ಅಗಲ, ಎತ್ತರ, 8, &yuv_type)) {
        ಹಿಂತಿರುಗಿ false;
    }

#ಆದರೆ 0 // Doesn't handle odd widths
    // RGB24 to FOURCC
    ಆದರೆ (src_format == SDL_PIXELFORMAT_RGB24) {
        Uint8 *y;
        Uint8 *u;
        Uint8 *v;
        Uint32 y_stride;
        Uint32 uv_stride;

        ಆದರೆ (GetYUVPlanes(ಅಗಲ, ಎತ್ತರ, dst_format, dst, dst_pitch, (ಸ್ಥಿರಾಂಕ Uint8 **)&y, (ಸ್ಥಿರಾಂಕ Uint8 **)&u, (ಸ್ಥಿರಾಂಕ Uint8 **)&v, &y_stride, &uv_stride) < 0) {
            ಹಿಂತಿರುಗಿ false;
        }

        rgb24_yuv420_std(ಅಗಲ, ಎತ್ತರ, src, src_pitch, y, u, v, y_stride, uv_stride, yuv_type);
        ಹಿಂತಿರುಗಿ true;
    }
#ಆದರೆ_ಅಂತ್ಯ

    // ARGB8888 to FOURCC
    ಆದರೆ (src_format == SDL_PIXELFORMAT_ARGB8888 || src_format == SDL_PIXELFORMAT_XRGB8888) {
        ಹಿಂತಿರುಗಿ SDL_Convert_Pixels_XRGB8888_ಗಮ್ಯ_YUV(ಅಗಲ, ಎತ್ತರ, src, src_pitch, dst_format, dst, dst_pitch, yuv_type);
    }

    ಆದರೆ (dst_format == SDL_PIXELFORMAT_P010) {
        ಆದರೆ (src_format == SDL_PIXELFORMAT_XBGR2101010) {
            ಹಿಂತಿರುಗಿ SDL_Convert_Pixels_XBGR2101010_ಗಮ್ಯ_P010(ಅಗಲ, ಎತ್ತರ, src, src_pitch, dst_format, dst, dst_pitch, yuv_type);
        }

        // We currently only support converting from XBGR2101010 to P010
        bool ಫಲಿತಾಂಶ;
        ಶೂನ್ಯ *tmp;
        ಪೂರ್ಣಾಂಕ tmp_pitch = (ಅಗಲ * ಗಾತ್ರ(Uint32));

        tmp = SDL_malloc((size_t)tmp_pitch * ಎತ್ತರ);
        ಆದರೆ (!tmp) {
            ಹಿಂತಿರುಗಿ false;
        }

        // convert src/src_format to tmp/XBGR2101010
        ಫಲಿತಾಂಶ = SDL_ConvertPixelsAndColorspace(ಅಗಲ, ಎತ್ತರ, src_format, src_colorspace, src_properties, src, src_pitch, SDL_PIXELFORMAT_XBGR2101010, dst_colorspace, dst_properties, tmp, tmp_pitch);
        ಆದರೆ (!ಫಲಿತಾಂಶ) {
            SDL_free(tmp);
            ಹಿಂತಿರುಗಿ false;
        }

        // convert tmp/XBGR2101010 to dst/P010
        ಫಲಿತಾಂಶ = SDL_Convert_Pixels_XBGR2101010_ಗಮ್ಯ_P010(ಅಗಲ, ಎತ್ತರ, tmp, tmp_pitch, dst_format, dst, dst_pitch, yuv_type);
        SDL_free(tmp);
        ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
    }

    // not ARGB8888 to FOURCC : need an intermediate conversion
    {
        bool ಫಲಿತಾಂಶ;
        ಶೂನ್ಯ *tmp;
        ಪೂರ್ಣಾಂಕ tmp_pitch = (ಅಗಲ * ಗಾತ್ರ(Uint32));

        tmp = SDL_malloc((size_t)tmp_pitch * ಎತ್ತರ);
        ಆದರೆ (!tmp) {
            ಹಿಂತಿರುಗಿ false;
        }

        // convert src/src_format to tmp/XRGB8888
        ಫಲಿತಾಂಶ = SDL_ConvertPixelsAndColorspace(ಅಗಲ, ಎತ್ತರ, src_format, src_colorspace, src_properties, src, src_pitch, SDL_PIXELFORMAT_XRGB8888, SDL_COLORSPACE_SRGB, 0, tmp, tmp_pitch);
        ಆದರೆ (!ಫಲಿತಾಂಶ) {
            SDL_free(tmp);
            ಹಿಂತಿರುಗಿ false;
        }

        // convert tmp/XRGB8888 to dst/FOURCC
        ಫಲಿತಾಂಶ = SDL_Convert_Pixels_XRGB8888_ಗಮ್ಯ_YUV(ಅಗಲ, ಎತ್ತರ, tmp, tmp_pitch, dst_format, dst, dst_pitch, yuv_type);
        SDL_free(tmp);
        ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
    }
}

ಸ್ಥಿರ bool SDL_Convert_Pixels_YUV_ಗಮ್ಯ_YUV_Copy(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, SDL_PixelFormat format, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಂಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಂಕ dst_pitch)
{
    ಪೂರ್ಣಾಂಕ i;

    ಆದರೆ (IsPlanar1x1Format(format)) {
        // YUV planes
        ಸ್ಥಿರಾಂಕ size_t ಉದ್ದಳತೆ = ಅಗಲ * SDL_BYTESPERPIXEL(format);
        ಗಾಗಿ (i = ಎತ್ತರ * 3; i--;) {
            SDL_memcpy(dst, src, ಉದ್ದಳತೆ);
            src = (ಸ್ಥಿರಾಂಕ Uint8 *)src + src_pitch;
            dst = (Uint8 *)dst + dst_pitch;
        }
        ಹಿಂತಿರುಗಿ true;
    }

    ಆದರೆ (IsPlanar2x2Format(format)) {
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ bpp = SDL_BYTESPERPIXEL(format);

        // Y plane
        ಸ್ಥಿರಾಂಕ size_t ಉದ್ದಳತೆ = ಅಗಲ * bpp;
        ಗಾಗಿ (i = ಎತ್ತರ; i--;) {
            SDL_memcpy(dst, src, ಉದ್ದಳತೆ);
            src = (ಸ್ಥಿರಾಂಕ Uint8 *)src + src_pitch;
            dst = (Uint8 *)dst + dst_pitch;
        }

        ಆದರೆ (format == SDL_PIXELFORMAT_YV12 ||
            format == SDL_PIXELFORMAT_IYUV ||
            format == SDL_PIXELFORMAT_I0FL) {
            // U and V planes are a quarter the size of the Y plane, rounded up
            ಅಗಲ = ((ಅಗಲ + 1) / 2) * bpp;
            ಎತ್ತರ = (ಎತ್ತರ + 1) / 2;
            src_pitch = ((src_pitch / bpp + 1) / 2) * bpp;
            dst_pitch = ((dst_pitch / bpp + 1) / 2) * bpp;
            ಗಾಗಿ (i = ಎತ್ತರ * 2; i--;) {
                SDL_memcpy(dst, src, ಅಗಲ);
                src = (ಸ್ಥಿರಾಂಕ Uint8 *)src + src_pitch;
                dst = (Uint8 *)dst + dst_pitch;
            }
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (format == SDL_PIXELFORMAT_NV12 ||
                   format == SDL_PIXELFORMAT_NV21 ||
                   format == SDL_PIXELFORMAT_P010) {
            // U/V plane is half the height of the Y plane, rounded up, with packed CrCb
            ಅಗಲ = ((ಅಗಲ + 1) / 2) * 2 * bpp;
            ಎತ್ತರ = (ಎತ್ತರ + 1) / 2;
            src_pitch = ((src_pitch / bpp + 1) / 2) * 2 * bpp;
            dst_pitch = ((dst_pitch / bpp + 1) / 2) * 2 * bpp;
            ಗಾಗಿ (i = ಎತ್ತರ; i--;) {
                SDL_memcpy(dst, src, ಅಗಲ);
                src = (ಸ್ಥಿರಾಂಕ Uint8 *)src + src_pitch;
                dst = (Uint8 *)dst + dst_pitch;
            }
        }
        ಹಿಂತಿರುಗಿ true;
    }

    ಆದರೆ (IsPacked4Format(format)) {
        // Packed planes
        ಅಗಲ = 4 * ((ಅಗಲ + 1) / 2);
        ಗಾಗಿ (i = ಎತ್ತರ; i--;) {
            SDL_memcpy(dst, src, ಅಗಲ);
            src = (ಸ್ಥಿರಾಂಕ Uint8 *)src + src_pitch;
            dst = (Uint8 *)dst + dst_pitch;
        }
        ಹಿಂತಿರುಗಿ true;
    }

    ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("SDL_ConvertPixels_YUV_to_YUV_Copy: Unsupported YUV format: %s", SDL_GetPixelFormatName(format));
}

ಸ್ಥಿರ bool SDL_Convert_Pixels_ಅದಲುಬದಲು_UVPlanes(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಂಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಂಕ dst_pitch)
{
    ಪೂರ್ಣಾಂಕ y;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ UVwidth = (ಅಗಲ + 1) / 2;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ UVheight = (ಎತ್ತರ + 1) / 2;

    // Skip the Y plane
    src = (ಸ್ಥಿರಾಂಕ Uint8 *)src + ಎತ್ತರ * src_pitch;
    dst = (Uint8 *)dst + ಎತ್ತರ * dst_pitch;

    ಆದರೆ (src == dst) {
        ಪೂರ್ಣಾಂಕ UVpitch = (dst_pitch + 1) / 2;
        Uint8 *tmp;
        Uint8 *row1 = (Uint8 *)dst;
        Uint8 *row2 = row1 + UVheight * UVpitch;

        // Allocate a temporary row for the swap
        tmp = (Uint8 *)SDL_malloc(UVwidth);
        ಆದರೆ (!tmp) {
            ಹಿಂತಿರುಗಿ false;
        }
        ಗಾಗಿ (y = 0; y < UVheight; ++y) {
            SDL_memcpy(tmp, row1, UVwidth);
            SDL_memcpy(row1, row2, UVwidth);
            SDL_memcpy(row2, tmp, UVwidth);
            row1 += UVpitch;
            row2 += UVpitch;
        }
        SDL_free(tmp);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಸ್ಥಿರಾಂಕ Uint8 *srcUV;
        Uint8 *dstUV;
        ಪೂರ್ಣಾಂಕ srcUVPitch = ((src_pitch + 1) / 2);
        ಪೂರ್ಣಾಂಕ dstUVPitch = ((dst_pitch + 1) / 2);

        // Copy the first plane
        srcUV = (ಸ್ಥಿರಾಂಕ Uint8 *)src;
        dstUV = (Uint8 *)dst + UVheight * dstUVPitch;
        ಗಾಗಿ (y = 0; y < UVheight; ++y) {
            SDL_memcpy(dstUV, srcUV, UVwidth);
            srcUV += srcUVPitch;
            dstUV += dstUVPitch;
        }

        // Copy the second plane
        dstUV = (Uint8 *)dst;
        ಗಾಗಿ (y = 0; y < UVheight; ++y) {
            SDL_memcpy(dstUV, srcUV, UVwidth);
            srcUV += srcUVPitch;
            dstUV += dstUVPitch;
        }
    }
    ಹಿಂತಿರುಗಿ true;
}

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_SSE2_INTRINSICS
ಸ್ಥಿರ bool SDL_TARGETING("sse2") SDL_Convert_Pixels_Pack_UVPlanes_ಗಮ್ಯ_NV_SSE2(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಂಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಂಕ dst_pitch, bool ಹಿಮ್ಮುಖ_UV)
{
    ಪೂರ್ಣಾಂಕ x, y;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ UVwidth = (ಅಗಲ + 1) / 2;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ UVheight = (ಎತ್ತರ + 1) / 2;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ srcUVPitch = ((src_pitch + 1) / 2);
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ src_UVPitch_ಎಡ = srcUVPitch - UVwidth;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ dstUVPitch = ((dst_pitch + 1) / 2) * 2;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ dst_UVPitch_ಎಡ = dstUVPitch - UVwidth * 2;
    ಸ್ಥಿರಾಂಕ Uint8 *src1, *src2;
    Uint8 *dstUV;
    Uint8 *tmp = ಖಾಲಿ;

    // Skip the Y plane
    src = (ಸ್ಥಿರಾಂಕ Uint8 *)src + ಎತ್ತರ * src_pitch;
    dst = (Uint8 *)dst + ಎತ್ತರ * dst_pitch;

    ಆದರೆ (src == dst) {
        // Need to make a copy of the buffer so we don't clobber it while converting
        tmp = (Uint8 *)SDL_malloc((size_t)2 * UVheight * srcUVPitch);
        ಆದರೆ (tmp == ಖಾಲಿ) {
            ಹಿಂತಿರುಗಿ false;
        }
        SDL_memcpy(tmp, src, (size_t)2 * UVheight * srcUVPitch);
        src = tmp;
    }

    ಆದರೆ (ಹಿಮ್ಮುಖ_UV) {
        src2 = (ಸ್ಥಿರಾಂಕ Uint8 *)src;
        src1 = src2 + UVheight * srcUVPitch;
    } ಇಲ್ಲದಿದ್ದರೆ {
        src1 = (ಸ್ಥಿರಾಂಕ Uint8 *)src;
        src2 = src1 + UVheight * srcUVPitch;
    }
    dstUV = (Uint8 *)dst;

    y = UVheight;
    ಆಗ (y--) {
        x = UVwidth;
        ಆಗ (x >= 16) {
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
        ಆಗ (x--) {
            *dstUV++ = *src1++;
            *dstUV++ = *src2++;
        }
        src1 += src_UVPitch_ಎಡ;
        src2 += src_UVPitch_ಎಡ;
        dstUV += dst_UVPitch_ಎಡ;
    }

    ಆದರೆ (tmp) {
        SDL_free(tmp);
    }
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool SDL_TARGETING("sse2") SDL_Convert_Pixels_ವಿಭಜಿಸು_NV_ಗಮ್ಯ_UVPlanes_SSE2(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಂಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಂಕ dst_pitch, bool ಹಿಮ್ಮುಖ_UV)
{
    ಪೂರ್ಣಾಂಕ x, y;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ UVwidth = (ಅಗಲ + 1) / 2;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ UVheight = (ಎತ್ತರ + 1) / 2;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ srcUVPitch = ((src_pitch + 1) / 2) * 2;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ src_UVPitch_ಎಡ = srcUVPitch - UVwidth * 2;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ dstUVPitch = ((dst_pitch + 1) / 2);
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ dst_UVPitch_ಎಡ = dstUVPitch - UVwidth;
    ಸ್ಥಿರಾಂಕ Uint8 *srcUV;
    Uint8 *dst1, *dst2;
    Uint8 *tmp = ಖಾಲಿ;

    // Skip the Y plane
    src = (ಸ್ಥಿರಾಂಕ Uint8 *)src + ಎತ್ತರ * src_pitch;
    dst = (Uint8 *)dst + ಎತ್ತರ * dst_pitch;

    ಆದರೆ (src == dst) {
        // Need to make a copy of the buffer so we don't clobber it while converting
        tmp = (Uint8 *)SDL_malloc((size_t)UVheight * srcUVPitch);
        ಆದರೆ (tmp == ಖಾಲಿ) {
            ಹಿಂತಿರುಗಿ false;
        }
        SDL_memcpy(tmp, src, (size_t)UVheight * srcUVPitch);
        src = tmp;
    }

    ಆದರೆ (ಹಿಮ್ಮುಖ_UV) {
        dst2 = (Uint8 *)dst;
        dst1 = dst2 + UVheight * dstUVPitch;
    } ಇಲ್ಲದಿದ್ದರೆ {
        dst1 = (Uint8 *)dst;
        dst2 = dst1 + UVheight * dstUVPitch;
    }
    srcUV = (ಸ್ಥಿರಾಂಕ Uint8 *)src;

    y = UVheight;
    ಆಗ (y--) {
        __m128i ಮುಖವಾಡ = _mm_set1_epi16(0x00FF);
        x = UVwidth;
        ಆಗ (x >= 16) {
            __m128i uv1 = _mm_loadu_si128((__m128i *)srcUV);
            __m128i uv2 = _mm_loadu_si128((__m128i *)(srcUV + 16));
            __m128i u1 = _mm_and_si128(uv1, ಮುಖವಾಡ);
            __m128i u2 = _mm_and_si128(uv2, ಮುಖವಾಡ);
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
        ಆಗ (x--) {
            *dst1++ = *srcUV++;
            *dst2++ = *srcUV++;
        }
        srcUV += src_UVPitch_ಎಡ;
        dst1 += dst_UVPitch_ಎಡ;
        dst2 += dst_UVPitch_ಎಡ;
    }

    ಆದರೆ (tmp) {
        SDL_free(tmp);
    }
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool SDL_TARGETING("sse2") SDL_Convert_Pixels_ಅದಲುಬದಲು_NV_SSE2(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಂಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಂಕ dst_pitch)
{
    ಪೂರ್ಣಾಂಕ x, y;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ UVwidth = (ಅಗಲ + 1) / 2;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ UVheight = (ಎತ್ತರ + 1) / 2;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ srcUVPitch = ((src_pitch + 1) / 2) * 2;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ src_UVPitch_ಎಡ = (srcUVPitch - UVwidth * 2) / ಗಾತ್ರ(Uint16);
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ dstUVPitch = ((dst_pitch + 1) / 2) * 2;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ dst_UVPitch_ಎಡ = (dstUVPitch - UVwidth * 2) / ಗಾತ್ರ(Uint16);
    ಸ್ಥಿರಾಂಕ Uint16 *srcUV;
    Uint16 *dstUV;

    // Skip the Y plane
    src = (ಸ್ಥಿರಾಂಕ Uint8 *)src + ಎತ್ತರ * src_pitch;
    dst = (Uint8 *)dst + ಎತ್ತರ * dst_pitch;

    srcUV = (ಸ್ಥಿರಾಂಕ Uint16 *)src;
    dstUV = (Uint16 *)dst;
    y = UVheight;
    ಆಗ (y--) {
        x = UVwidth;
        ಆಗ (x >= 8) {
            __m128i uv = _mm_loadu_si128((__m128i *)srcUV);
            __m128i v = _mm_slli_epi16(uv, 8);
            __m128i u = _mm_srli_epi16(uv, 8);
            __m128i vu = _mm_or_si128(v, u);
            _mm_storeu_si128((__m128i *)dstUV, vu);
            srcUV += 8;
            dstUV += 8;
            x -= 8;
        }
        ಆದರೆ (x > 0) {
            ಸ್ಥಿರಾಂಕ Uint8 *srcUV8 = (ಸ್ಥಿರಾಂಕ Uint8 *)srcUV;
            Uint8 *dstUV8 = (Uint8 *)dstUV;
            srcUV += x;
            dstUV += x;
            ಆಗ (x--) {
                Uint8 u = *srcUV8++;
                Uint8 v = *srcUV8++;
                *dstUV8++ = v;
                *dstUV8++ = u;
            }
        }
        srcUV += src_UVPitch_ಎಡ;
        dstUV += dst_UVPitch_ಎಡ;
    }
    ಹಿಂತಿರುಗಿ true;
}
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ bool SDL_Convert_Pixels_Pack_UVPlanes_ಗಮ್ಯ_NV_std(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಂಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಂಕ dst_pitch, bool ಹಿಮ್ಮುಖ_UV)
{
    ಪೂರ್ಣಾಂಕ x, y;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ UVwidth = (ಅಗಲ + 1) / 2;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ UVheight = (ಎತ್ತರ + 1) / 2;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ srcUVPitch = ((src_pitch + 1) / 2);
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ src_UVPitch_ಎಡ = srcUVPitch - UVwidth;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ dstUVPitch = ((dst_pitch + 1) / 2) * 2;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ dst_UVPitch_ಎಡ = dstUVPitch - UVwidth * 2;
    ಸ್ಥಿರಾಂಕ Uint8 *src1, *src2;
    Uint8 *dstUV;
    Uint8 *tmp = ಖಾಲಿ;

    // Skip the Y plane
    src = (ಸ್ಥಿರಾಂಕ Uint8 *)src + ಎತ್ತರ * src_pitch;
    dst = (Uint8 *)dst + ಎತ್ತರ * dst_pitch;

    ಆದರೆ (src == dst) {
        // Need to make a copy of the buffer so we don't clobber it while converting
        tmp = (Uint8 *)SDL_malloc((size_t)2 * UVheight * srcUVPitch);
        ಆದರೆ (!tmp) {
            ಹಿಂತಿರುಗಿ false;
        }
        SDL_memcpy(tmp, src, (size_t)2 * UVheight * srcUVPitch);
        src = tmp;
    }

    ಆದರೆ (ಹಿಮ್ಮುಖ_UV) {
        src2 = (ಸ್ಥಿರಾಂಕ Uint8 *)src;
        src1 = src2 + UVheight * srcUVPitch;
    } ಇಲ್ಲದಿದ್ದರೆ {
        src1 = (ಸ್ಥಿರಾಂಕ Uint8 *)src;
        src2 = src1 + UVheight * srcUVPitch;
    }
    dstUV = (Uint8 *)dst;

    y = UVheight;
    ಆಗ (y--) {
        x = UVwidth;
        ಆಗ (x--) {
            *dstUV++ = *src1++;
            *dstUV++ = *src2++;
        }
        src1 += src_UVPitch_ಎಡ;
        src2 += src_UVPitch_ಎಡ;
        dstUV += dst_UVPitch_ಎಡ;
    }

    SDL_free(tmp);
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool SDL_Convert_Pixels_ವಿಭಜಿಸು_NV_ಗಮ್ಯ_UVPlanes_std(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಂಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಂಕ dst_pitch, bool ಹಿಮ್ಮುಖ_UV)
{
    ಪೂರ್ಣಾಂಕ x, y;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ UVwidth = (ಅಗಲ + 1) / 2;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ UVheight = (ಎತ್ತರ + 1) / 2;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ srcUVPitch = ((src_pitch + 1) / 2) * 2;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ src_UVPitch_ಎಡ = srcUVPitch - UVwidth * 2;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ dstUVPitch = ((dst_pitch + 1) / 2);
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ dst_UVPitch_ಎಡ = dstUVPitch - UVwidth;
    ಸ್ಥಿರಾಂಕ Uint8 *srcUV;
    Uint8 *dst1, *dst2;
    Uint8 *tmp = ಖಾಲಿ;

    // Skip the Y plane
    src = (ಸ್ಥಿರಾಂಕ Uint8 *)src + ಎತ್ತರ * src_pitch;
    dst = (Uint8 *)dst + ಎತ್ತರ * dst_pitch;

    ಆದರೆ (src == dst) {
        // Need to make a copy of the buffer so we don't clobber it while converting
        tmp = (Uint8 *)SDL_malloc((size_t)UVheight * srcUVPitch);
        ಆದರೆ (!tmp) {
            ಹಿಂತಿರುಗಿ false;
        }
        SDL_memcpy(tmp, src, (size_t)UVheight * srcUVPitch);
        src = tmp;
    }

    ಆದರೆ (ಹಿಮ್ಮುಖ_UV) {
        dst2 = (Uint8 *)dst;
        dst1 = dst2 + UVheight * dstUVPitch;
    } ಇಲ್ಲದಿದ್ದರೆ {
        dst1 = (Uint8 *)dst;
        dst2 = dst1 + UVheight * dstUVPitch;
    }
    srcUV = (ಸ್ಥಿರಾಂಕ Uint8 *)src;

    y = UVheight;
    ಆಗ (y--) {
        x = UVwidth;
        ಆಗ (x--) {
            *dst1++ = *srcUV++;
            *dst2++ = *srcUV++;
        }
        srcUV += src_UVPitch_ಎಡ;
        dst1 += dst_UVPitch_ಎಡ;
        dst2 += dst_UVPitch_ಎಡ;
    }

    SDL_free(tmp);
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool SDL_Convert_Pixels_ಅದಲುಬದಲು_NV_std(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಂಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಂಕ dst_pitch)
{
    ಪೂರ್ಣಾಂಕ x, y;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ UVwidth = (ಅಗಲ + 1) / 2;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ UVheight = (ಎತ್ತರ + 1) / 2;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ srcUVPitch = ((src_pitch + 1) / 2) * 2;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ dstUVPitch = ((dst_pitch + 1) / 2) * 2;

    // Skip the Y plane
    src = (ಸ್ಥಿರಾಂಕ Uint8 *)src + ಎತ್ತರ * src_pitch;
    dst = (Uint8 *)dst + ಎತ್ತರ * dst_pitch;

    bool aligned = (((uintptr_t)src | (uintptr_t)dst) & 1) == 0;
    ಆದರೆ (aligned) {
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ src_UVPitch_ಎಡ = (srcUVPitch - UVwidth * 2) / ಗಾತ್ರ(Uint16);
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ dst_UVPitch_ಎಡ = (dstUVPitch - UVwidth * 2) / ಗಾತ್ರ(Uint16);
        ಸ್ಥಿರಾಂಕ Uint16 *srcUV = (ಸ್ಥಿರಾಂಕ Uint16 *)src;
        Uint16 *dstUV = (Uint16 *)dst;
        y = UVheight;
        ಆಗ (y--) {
            x = UVwidth;
            ಆಗ (x--) {
                *dstUV++ = SDL_Swap16(*srcUV++);
            }
            srcUV += src_UVPitch_ಎಡ;
            dstUV += dst_UVPitch_ಎಡ;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ src_UVPitch_ಎಡ = (srcUVPitch - UVwidth * 2);
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ dst_UVPitch_ಎಡ = (dstUVPitch - UVwidth * 2);
        ಸ್ಥಿರಾಂಕ Uint8 *srcUV = (ಸ್ಥಿರಾಂಕ Uint8 *)src;
        Uint8 *dstUV = (Uint8 *)dst;
        y = UVheight;
        ಆಗ (y--) {
            x = UVwidth;
            ಆಗ (x--) {
                Uint8 u = *srcUV++;
                Uint8 v = *srcUV++;
                *dstUV++ = v;
                *dstUV++ = u;
            }
            srcUV += src_UVPitch_ಎಡ;
            dstUV += dst_UVPitch_ಎಡ;
        }
    }
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool SDL_Convert_Pixels_Pack_UVPlanes_ಗಮ್ಯ_NV(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಂಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಂಕ dst_pitch, bool ಹಿಮ್ಮುಖ_UV)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_SSE2_INTRINSICS
    ಆದರೆ (SDL_HasSSE2()) {
      ಹಿಂತಿರುಗಿ SDL_Convert_Pixels_Pack_UVPlanes_ಗಮ್ಯ_NV_SSE2(ಅಗಲ, ಎತ್ತರ, src, src_pitch, dst, dst_pitch, ಹಿಮ್ಮುಖ_UV);
    }
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ SDL_Convert_Pixels_Pack_UVPlanes_ಗಮ್ಯ_NV_std(ಅಗಲ, ಎತ್ತರ, src, src_pitch, dst, dst_pitch, ಹಿಮ್ಮುಖ_UV);
}

ಸ್ಥಿರ bool SDL_Convert_Pixels_ವಿಭಜಿಸು_NV_ಗಮ್ಯ_UVPlanes(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಂಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಂಕ dst_pitch, bool ಹಿಮ್ಮುಖ_UV)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_SSE2_INTRINSICS
    ಆದರೆ (SDL_HasSSE2()) {
      ಹಿಂತಿರುಗಿ SDL_Convert_Pixels_ವಿಭಜಿಸು_NV_ಗಮ್ಯ_UVPlanes_SSE2(ಅಗಲ, ಎತ್ತರ, src, src_pitch, dst, dst_pitch, ಹಿಮ್ಮುಖ_UV);
    }
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ SDL_Convert_Pixels_ವಿಭಜಿಸು_NV_ಗಮ್ಯ_UVPlanes_std(ಅಗಲ, ಎತ್ತರ, src, src_pitch, dst, dst_pitch, ಹಿಮ್ಮುಖ_UV);
}

ಸ್ಥಿರ bool SDL_Convert_Pixels_ಅದಲುಬದಲು_NV(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಂಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಂಕ dst_pitch)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_SSE2_INTRINSICS
    ಆದರೆ (SDL_HasSSE2()) {
      ಹಿಂತಿರುಗಿ SDL_Convert_Pixels_ಅದಲುಬದಲು_NV_SSE2(ಅಗಲ, ಎತ್ತರ, src, src_pitch, dst, dst_pitch);
    }
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ SDL_Convert_Pixels_ಅದಲುಬದಲು_NV_std(ಅಗಲ, ಎತ್ತರ, src, src_pitch, dst, dst_pitch);
}

ಸ್ಥಿರ bool SDL_Convert_Pixels_Planar2x2_ಗಮ್ಯ_Planar2x2(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ,
                                                     SDL_PixelFormat src_format, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಂಕ src_pitch,
                                                     SDL_PixelFormat dst_format, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಂಕ dst_pitch)
{
    ಆದರೆ (src != dst) {
        // Copy Y plane
        ಪೂರ್ಣಾಂಕ i;
        ಸ್ಥಿರಾಂಕ Uint8 *srcY = (ಸ್ಥಿರಾಂಕ Uint8 *)src;
        Uint8 *dstY = (Uint8 *)dst;
        ಗಾಗಿ (i = ಎತ್ತರ; i--;) {
            SDL_memcpy(dstY, srcY, ಅಗಲ);
            srcY += src_pitch;
            dstY += dst_pitch;
        }
    }

    ಆಯ್ಕೆ (src_format) {
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_YV12:
        ಆಯ್ಕೆ (dst_format) {
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_IYUV:
            ಹಿಂತಿರುಗಿ SDL_Convert_Pixels_ಅದಲುಬದಲು_UVPlanes(ಅಗಲ, ಎತ್ತರ, src, src_pitch, dst, dst_pitch);
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_NV12:
            ಹಿಂತಿರುಗಿ SDL_Convert_Pixels_Pack_UVPlanes_ಗಮ್ಯ_NV(ಅಗಲ, ಎತ್ತರ, src, src_pitch, dst, dst_pitch, true);
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_NV21:
            ಹಿಂತಿರುಗಿ SDL_Convert_Pixels_Pack_UVPlanes_ಗಮ್ಯ_NV(ಅಗಲ, ಎತ್ತರ, src, src_pitch, dst, dst_pitch, false);
        ಪೂರ್ವನಿಯೋಜಿತ:
            ನಿಲ್ಲಿಸು;
        }
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_IYUV:
        ಆಯ್ಕೆ (dst_format) {
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_YV12:
            ಹಿಂತಿರುಗಿ SDL_Convert_Pixels_ಅದಲುಬದಲು_UVPlanes(ಅಗಲ, ಎತ್ತರ, src, src_pitch, dst, dst_pitch);
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_NV12:
            ಹಿಂತಿರುಗಿ SDL_Convert_Pixels_Pack_UVPlanes_ಗಮ್ಯ_NV(ಅಗಲ, ಎತ್ತರ, src, src_pitch, dst, dst_pitch, false);
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_NV21:
            ಹಿಂತಿರುಗಿ SDL_Convert_Pixels_Pack_UVPlanes_ಗಮ್ಯ_NV(ಅಗಲ, ಎತ್ತರ, src, src_pitch, dst, dst_pitch, true);
        ಪೂರ್ವನಿಯೋಜಿತ:
            ನಿಲ್ಲಿಸು;
        }
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_NV12:
        ಆಯ್ಕೆ (dst_format) {
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_YV12:
            ಹಿಂತಿರುಗಿ SDL_Convert_Pixels_ವಿಭಜಿಸು_NV_ಗಮ್ಯ_UVPlanes(ಅಗಲ, ಎತ್ತರ, src, src_pitch, dst, dst_pitch, true);
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_IYUV:
            ಹಿಂತಿರುಗಿ SDL_Convert_Pixels_ವಿಭಜಿಸು_NV_ಗಮ್ಯ_UVPlanes(ಅಗಲ, ಎತ್ತರ, src, src_pitch, dst, dst_pitch, false);
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_NV21:
            ಹಿಂತಿರುಗಿ SDL_Convert_Pixels_ಅದಲುಬದಲು_NV(ಅಗಲ, ಎತ್ತರ, src, src_pitch, dst, dst_pitch);
        ಪೂರ್ವನಿಯೋಜಿತ:
            ನಿಲ್ಲಿಸು;
        }
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_NV21:
        ಆಯ್ಕೆ (dst_format) {
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_YV12:
            ಹಿಂತಿರುಗಿ SDL_Convert_Pixels_ವಿಭಜಿಸು_NV_ಗಮ್ಯ_UVPlanes(ಅಗಲ, ಎತ್ತರ, src, src_pitch, dst, dst_pitch, false);
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_IYUV:
            ಹಿಂತಿರುಗಿ SDL_Convert_Pixels_ವಿಭಜಿಸು_NV_ಗಮ್ಯ_UVPlanes(ಅಗಲ, ಎತ್ತರ, src, src_pitch, dst, dst_pitch, true);
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_NV12:
            ಹಿಂತಿರುಗಿ SDL_Convert_Pixels_ಅದಲುಬದಲು_NV(ಅಗಲ, ಎತ್ತರ, src, src_pitch, dst, dst_pitch);
        ಪೂರ್ವನಿಯೋಜಿತ:
            ನಿಲ್ಲಿಸು;
        }
        ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        ನಿಲ್ಲಿಸು;
    }
    ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("SDL_ConvertPixels_Planar2x2_to_Planar2x2: Unsupported YUV conversion: %s -> %s", SDL_GetPixelFormatName(src_format),
                        SDL_GetPixelFormatName(dst_format));
}

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_SSE2_INTRINSICS
#ವ್ಯಾಖ್ಯಾನಿಸು PACKED4_ಗಮ್ಯ_PACKED4_ಅಡ್ಡಸಾಲು_SSE2(shuffle)                      \
    ಆಗ (x >= 4) {                                              \
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

ಸ್ಥಿರ bool SDL_TARGETING("sse2") SDL_Convert_Pixels_YUY2_ಗಮ್ಯ_UYVY_SSE2(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಂಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಂಕ dst_pitch)
{
    ಪೂರ್ಣಾಂಕ x, y;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ YUVwidth = (ಅಗಲ + 1) / 2;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ src_YUVPitch_ಎಡ = (src_pitch - YUVwidth * 4);
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ dst_YUVPitch_ಎಡ = (dst_pitch - YUVwidth * 4);
    ಸ್ಥಿರಾಂಕ Uint8 *srcYUV = (ಸ್ಥಿರಾಂಕ Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = ಎತ್ತರ;
    x = YUVwidth;
    ಆಗ (y--) {
        PACKED4_ಗಮ್ಯ_PACKED4_ಅಡ್ಡಸಾಲು_SSE2(_MM_SHUFFLE(2, 3, 0, 1));
        ಆಗ (x--) {
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
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool SDL_TARGETING("sse2") SDL_Convert_Pixels_YUY2_ಗಮ್ಯ_YVYU_SSE2(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಂಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಂಕ dst_pitch)
{
    ಪೂರ್ಣಾಂಕ x, y;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ YUVwidth = (ಅಗಲ + 1) / 2;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ src_YUVPitch_ಎಡ = (src_pitch - YUVwidth * 4);
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ dst_YUVPitch_ಎಡ = (dst_pitch - YUVwidth * 4);
    ಸ್ಥಿರಾಂಕ Uint8 *srcYUV = (ಸ್ಥಿರಾಂಕ Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = ಎತ್ತರ;
    x = YUVwidth;
    ಆಗ (y--) {
        PACKED4_ಗಮ್ಯ_PACKED4_ಅಡ್ಡಸಾಲು_SSE2(_MM_SHUFFLE(1, 2, 3, 0));
        ಆಗ (x--) {
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
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool SDL_TARGETING("sse2") SDL_Convert_Pixels_UYVY_ಗಮ್ಯ_YUY2_SSE2(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಂಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಂಕ dst_pitch)
{
    ಪೂರ್ಣಾಂಕ x, y;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ YUVwidth = (ಅಗಲ + 1) / 2;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ src_YUVPitch_ಎಡ = (src_pitch - YUVwidth * 4);
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ dst_YUVPitch_ಎಡ = (dst_pitch - YUVwidth * 4);
    ಸ್ಥಿರಾಂಕ Uint8 *srcYUV = (ಸ್ಥಿರಾಂಕ Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = ಎತ್ತರ;
    x = YUVwidth;
    ಆಗ (y--) {
        PACKED4_ಗಮ್ಯ_PACKED4_ಅಡ್ಡಸಾಲು_SSE2(_MM_SHUFFLE(2, 3, 0, 1));
        ಆಗ (x--) {
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
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool SDL_TARGETING("sse2") SDL_Convert_Pixels_UYVY_ಗಮ್ಯ_YVYU_SSE2(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಂಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಂಕ dst_pitch)
{
    ಪೂರ್ಣಾಂಕ x, y;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ YUVwidth = (ಅಗಲ + 1) / 2;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ src_YUVPitch_ಎಡ = (src_pitch - YUVwidth * 4);
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ dst_YUVPitch_ಎಡ = (dst_pitch - YUVwidth * 4);
    ಸ್ಥಿರಾಂಕ Uint8 *srcYUV = (ಸ್ಥಿರಾಂಕ Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = ಎತ್ತರ;
    x = YUVwidth;
    ಆಗ (y--) {
        PACKED4_ಗಮ್ಯ_PACKED4_ಅಡ್ಡಸಾಲು_SSE2(_MM_SHUFFLE(0, 3, 2, 1));
        ಆಗ (x--) {
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
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool SDL_TARGETING("sse2") SDL_Convert_Pixels_YVYU_ಗಮ್ಯ_YUY2_SSE2(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಂಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಂಕ dst_pitch)
{
    ಪೂರ್ಣಾಂಕ x, y;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ YUVwidth = (ಅಗಲ + 1) / 2;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ src_YUVPitch_ಎಡ = (src_pitch - YUVwidth * 4);
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ dst_YUVPitch_ಎಡ = (dst_pitch - YUVwidth * 4);
    ಸ್ಥಿರಾಂಕ Uint8 *srcYUV = (ಸ್ಥಿರಾಂಕ Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = ಎತ್ತರ;
    x = YUVwidth;
    ಆಗ (y--) {
        PACKED4_ಗಮ್ಯ_PACKED4_ಅಡ್ಡಸಾಲು_SSE2(_MM_SHUFFLE(1, 2, 3, 0));
        ಆಗ (x--) {
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
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool SDL_TARGETING("sse2") SDL_Convert_Pixels_YVYU_ಗಮ್ಯ_UYVY_SSE2(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಂಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಂಕ dst_pitch)
{
    ಪೂರ್ಣಾಂಕ x, y;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ YUVwidth = (ಅಗಲ + 1) / 2;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ src_YUVPitch_ಎಡ = (src_pitch - YUVwidth * 4);
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ dst_YUVPitch_ಎಡ = (dst_pitch - YUVwidth * 4);
    ಸ್ಥಿರಾಂಕ Uint8 *srcYUV = (ಸ್ಥಿರಾಂಕ Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = ಎತ್ತರ;
    x = YUVwidth;
    ಆಗ (y--) {
        PACKED4_ಗಮ್ಯ_PACKED4_ಅಡ್ಡಸಾಲು_SSE2(_MM_SHUFFLE(2, 1, 0, 3));
        ಆಗ (x--) {
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
    ಹಿಂತಿರುಗಿ true;
}
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ bool SDL_Convert_Pixels_YUY2_ಗಮ್ಯ_UYVY_std(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಂಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಂಕ dst_pitch)
{
    ಪೂರ್ಣಾಂಕ x, y;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ YUVwidth = (ಅಗಲ + 1) / 2;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ src_YUVPitch_ಎಡ = (src_pitch - YUVwidth * 4);
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ dst_YUVPitch_ಎಡ = (dst_pitch - YUVwidth * 4);
    ಸ್ಥಿರಾಂಕ Uint8 *srcYUV = (ಸ್ಥಿರಾಂಕ Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = ಎತ್ತರ;
    ಆಗ (y--) {
        x = YUVwidth;
        ಆಗ (x--) {
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
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool SDL_Convert_Pixels_YUY2_ಗಮ್ಯ_YVYU_std(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಂಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಂಕ dst_pitch)
{
    ಪೂರ್ಣಾಂಕ x, y;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ YUVwidth = (ಅಗಲ + 1) / 2;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ src_YUVPitch_ಎಡ = (src_pitch - YUVwidth * 4);
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ dst_YUVPitch_ಎಡ = (dst_pitch - YUVwidth * 4);
    ಸ್ಥಿರಾಂಕ Uint8 *srcYUV = (ಸ್ಥಿರಾಂಕ Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = ಎತ್ತರ;
    ಆಗ (y--) {
        x = YUVwidth;
        ಆಗ (x--) {
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
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool SDL_Convert_Pixels_UYVY_ಗಮ್ಯ_YUY2_std(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಂಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಂಕ dst_pitch)
{
    ಪೂರ್ಣಾಂಕ x, y;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ YUVwidth = (ಅಗಲ + 1) / 2;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ src_YUVPitch_ಎಡ = (src_pitch - YUVwidth * 4);
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ dst_YUVPitch_ಎಡ = (dst_pitch - YUVwidth * 4);
    ಸ್ಥಿರಾಂಕ Uint8 *srcYUV = (ಸ್ಥಿರಾಂಕ Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = ಎತ್ತರ;
    ಆಗ (y--) {
        x = YUVwidth;
        ಆಗ (x--) {
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
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool SDL_Convert_Pixels_UYVY_ಗಮ್ಯ_YVYU_std(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಂಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಂಕ dst_pitch)
{
    ಪೂರ್ಣಾಂಕ x, y;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ YUVwidth = (ಅಗಲ + 1) / 2;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ src_YUVPitch_ಎಡ = (src_pitch - YUVwidth * 4);
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ dst_YUVPitch_ಎಡ = (dst_pitch - YUVwidth * 4);
    ಸ್ಥಿರಾಂಕ Uint8 *srcYUV = (ಸ್ಥಿರಾಂಕ Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = ಎತ್ತರ;
    ಆಗ (y--) {
        x = YUVwidth;
        ಆಗ (x--) {
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
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool SDL_Convert_Pixels_YVYU_ಗಮ್ಯ_YUY2_std(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಂಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಂಕ dst_pitch)
{
    ಪೂರ್ಣಾಂಕ x, y;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ YUVwidth = (ಅಗಲ + 1) / 2;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ src_YUVPitch_ಎಡ = (src_pitch - YUVwidth * 4);
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ dst_YUVPitch_ಎಡ = (dst_pitch - YUVwidth * 4);
    ಸ್ಥಿರಾಂಕ Uint8 *srcYUV = (ಸ್ಥಿರಾಂಕ Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = ಎತ್ತರ;
    ಆಗ (y--) {
        x = YUVwidth;
        ಆಗ (x--) {
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
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool SDL_Convert_Pixels_YVYU_ಗಮ್ಯ_UYVY_std(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಂಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಂಕ dst_pitch)
{
    ಪೂರ್ಣಾಂಕ x, y;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ YUVwidth = (ಅಗಲ + 1) / 2;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ src_YUVPitch_ಎಡ = (src_pitch - YUVwidth * 4);
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ dst_YUVPitch_ಎಡ = (dst_pitch - YUVwidth * 4);
    ಸ್ಥಿರಾಂಕ Uint8 *srcYUV = (ಸ್ಥಿರಾಂಕ Uint8 *)src;
    Uint8 *dstYUV = (Uint8 *)dst;

    y = ಎತ್ತರ;
    ಆಗ (y--) {
        x = YUVwidth;
        ಆಗ (x--) {
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
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool SDL_Convert_Pixels_YUY2_ಗಮ್ಯ_UYVY(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಂಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಂಕ dst_pitch)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_SSE2_INTRINSICS
    ಆದರೆ (SDL_HasSSE2()) {
      ಹಿಂತಿರುಗಿ SDL_Convert_Pixels_YUY2_ಗಮ್ಯ_UYVY_SSE2(ಅಗಲ, ಎತ್ತರ, src, src_pitch, dst, dst_pitch);
    }
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ SDL_Convert_Pixels_YUY2_ಗಮ್ಯ_UYVY_std(ಅಗಲ, ಎತ್ತರ, src, src_pitch, dst, dst_pitch);
}

ಸ್ಥಿರ bool SDL_Convert_Pixels_YUY2_ಗಮ್ಯ_YVYU(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಂಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಂಕ dst_pitch)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_SSE2_INTRINSICS
    ಆದರೆ (SDL_HasSSE2()) {
      ಹಿಂತಿರುಗಿ SDL_Convert_Pixels_YUY2_ಗಮ್ಯ_YVYU_SSE2(ಅಗಲ, ಎತ್ತರ, src, src_pitch, dst, dst_pitch);
    }
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ SDL_Convert_Pixels_YUY2_ಗಮ್ಯ_YVYU_std(ಅಗಲ, ಎತ್ತರ, src, src_pitch, dst, dst_pitch);
}

ಸ್ಥಿರ bool SDL_Convert_Pixels_UYVY_ಗಮ್ಯ_YUY2(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಂಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಂಕ dst_pitch)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_SSE2_INTRINSICS
    ಆದರೆ (SDL_HasSSE2()) {
      ಹಿಂತಿರುಗಿ SDL_Convert_Pixels_UYVY_ಗಮ್ಯ_YUY2_SSE2(ಅಗಲ, ಎತ್ತರ, src, src_pitch, dst, dst_pitch);
    }
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ SDL_Convert_Pixels_UYVY_ಗಮ್ಯ_YUY2_std(ಅಗಲ, ಎತ್ತರ, src, src_pitch, dst, dst_pitch);
}

ಸ್ಥಿರ bool SDL_Convert_Pixels_UYVY_ಗಮ್ಯ_YVYU(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಂಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಂಕ dst_pitch)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_SSE2_INTRINSICS
    ಆದರೆ (SDL_HasSSE2()) {
      ಹಿಂತಿರುಗಿ SDL_Convert_Pixels_UYVY_ಗಮ್ಯ_YVYU_SSE2(ಅಗಲ, ಎತ್ತರ, src, src_pitch, dst, dst_pitch);
    }
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ SDL_Convert_Pixels_UYVY_ಗಮ್ಯ_YVYU_std(ಅಗಲ, ಎತ್ತರ, src, src_pitch, dst, dst_pitch);
}

ಸ್ಥಿರ bool SDL_Convert_Pixels_YVYU_ಗಮ್ಯ_YUY2(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಂಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಂಕ dst_pitch)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_SSE2_INTRINSICS
    ಆದರೆ (SDL_HasSSE2()) {
      ಹಿಂತಿರುಗಿ SDL_Convert_Pixels_YVYU_ಗಮ್ಯ_YUY2_SSE2(ಅಗಲ, ಎತ್ತರ, src, src_pitch, dst, dst_pitch);
    }
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ SDL_Convert_Pixels_YVYU_ಗಮ್ಯ_YUY2_std(ಅಗಲ, ಎತ್ತರ, src, src_pitch, dst, dst_pitch);
}

ಸ್ಥಿರ bool SDL_Convert_Pixels_YVYU_ಗಮ್ಯ_UYVY(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಂಕ src_pitch, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಂಕ dst_pitch)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_SSE2_INTRINSICS
    ಆದರೆ (SDL_HasSSE2()) {
      ಹಿಂತಿರುಗಿ SDL_Convert_Pixels_YVYU_ಗಮ್ಯ_UYVY_SSE2(ಅಗಲ, ಎತ್ತರ, src, src_pitch, dst, dst_pitch);
    }
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ SDL_Convert_Pixels_YVYU_ಗಮ್ಯ_UYVY_std(ಅಗಲ, ಎತ್ತರ, src, src_pitch, dst, dst_pitch);
}

ಸ್ಥಿರ bool SDL_Convert_Pixels_Packed4_ಗಮ್ಯ_Packed4(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ,
                                                SDL_PixelFormat src_format, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಂಕ src_pitch,
                                                SDL_PixelFormat dst_format, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಂಕ dst_pitch)
{
    ಆಯ್ಕೆ (src_format) {
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_YUY2:
        ಆಯ್ಕೆ (dst_format) {
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_UYVY:
            ಹಿಂತಿರುಗಿ SDL_Convert_Pixels_YUY2_ಗಮ್ಯ_UYVY(ಅಗಲ, ಎತ್ತರ, src, src_pitch, dst, dst_pitch);
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_YVYU:
            ಹಿಂತಿರುಗಿ SDL_Convert_Pixels_YUY2_ಗಮ್ಯ_YVYU(ಅಗಲ, ಎತ್ತರ, src, src_pitch, dst, dst_pitch);
        ಪೂರ್ವನಿಯೋಜಿತ:
            ನಿಲ್ಲಿಸು;
        }
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_UYVY:
        ಆಯ್ಕೆ (dst_format) {
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_YUY2:
            ಹಿಂತಿರುಗಿ SDL_Convert_Pixels_UYVY_ಗಮ್ಯ_YUY2(ಅಗಲ, ಎತ್ತರ, src, src_pitch, dst, dst_pitch);
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_YVYU:
            ಹಿಂತಿರುಗಿ SDL_Convert_Pixels_UYVY_ಗಮ್ಯ_YVYU(ಅಗಲ, ಎತ್ತರ, src, src_pitch, dst, dst_pitch);
        ಪೂರ್ವನಿಯೋಜಿತ:
            ನಿಲ್ಲಿಸು;
        }
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_YVYU:
        ಆಯ್ಕೆ (dst_format) {
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_YUY2:
            ಹಿಂತಿರುಗಿ SDL_Convert_Pixels_YVYU_ಗಮ್ಯ_YUY2(ಅಗಲ, ಎತ್ತರ, src, src_pitch, dst, dst_pitch);
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_UYVY:
            ಹಿಂತಿರುಗಿ SDL_Convert_Pixels_YVYU_ಗಮ್ಯ_UYVY(ಅಗಲ, ಎತ್ತರ, src, src_pitch, dst, dst_pitch);
        ಪೂರ್ವನಿಯೋಜಿತ:
            ನಿಲ್ಲಿಸು;
        }
        ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        ನಿಲ್ಲಿಸು;
    }
    ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("SDL_ConvertPixels_Packed4_to_Packed4: Unsupported YUV conversion: %s -> %s", SDL_GetPixelFormatName(src_format),
                        SDL_GetPixelFormatName(dst_format));
}

ಸ್ಥಿರ bool SDL_Convert_Pixels_Planar2x2_ಗಮ್ಯ_Packed4(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ,
                                                   SDL_PixelFormat src_format, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಂಕ src_pitch,
                                                   SDL_PixelFormat dst_format, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಂಕ dst_pitch)
{
    ಪೂರ್ಣಾಂಕ x, y;
    ಸ್ಥಿರಾಂಕ Uint8 *srcY1, *srcY2, *srcU, *srcV;
    Uint32 srcY_pitch, srcUV_pitch;
    Uint32 src_Y_pitch_ಎಡ, src_UV_pitch_ಎಡ, srcUV_pixel_stride;
    Uint8 *dstY1, *dstY2, *dstU1, *dstU2, *dstV1, *dstV2;
    Uint32 dstY_pitch, dstUV_pitch;
    Uint32 dst_pitch_ಎಡ;

    ಆದರೆ (src == dst) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Can't change YUV plane types in-place");
    }

    ಆದರೆ (!GetYUVPlanes(ಅಗಲ, ಎತ್ತರ, src_format, src, src_pitch,
                      &srcY1, &srcU, &srcV, &srcY_pitch, &srcUV_pitch)) {
        ಹಿಂತಿರುಗಿ false;
    }
    srcY2 = srcY1 + srcY_pitch;
    src_Y_pitch_ಎಡ = (srcY_pitch - ಅಗಲ);

    ಆದರೆ (src_format == SDL_PIXELFORMAT_NV12 || src_format == SDL_PIXELFORMAT_NV21) {
        srcUV_pixel_stride = 2;
        src_UV_pitch_ಎಡ = (srcUV_pitch - 2 * ((ಅಗಲ + 1) / 2));
    } ಇಲ್ಲದಿದ್ದರೆ {
        srcUV_pixel_stride = 1;
        src_UV_pitch_ಎಡ = (srcUV_pitch - ((ಅಗಲ + 1) / 2));
    }

    ಆದರೆ (!GetYUVPlanes(ಅಗಲ, ಎತ್ತರ, dst_format, dst, dst_pitch,
                      (ಸ್ಥಿರಾಂಕ Uint8 **)&dstY1, (ಸ್ಥಿರಾಂಕ Uint8 **)&dstU1, (ಸ್ಥಿರಾಂಕ Uint8 **)&dstV1,
                      &dstY_pitch, &dstUV_pitch)) {
        ಹಿಂತಿರುಗಿ false;
    }
    dstY2 = dstY1 + dstY_pitch;
    dstU2 = dstU1 + dstUV_pitch;
    dstV2 = dstV1 + dstUV_pitch;
    dst_pitch_ಎಡ = (dstY_pitch - 4 * ((ಅಗಲ + 1) / 2));

    // Copy 2x2 blocks of pixels at a time
    ಗಾಗಿ (y = 0; y < (ಎತ್ತರ - 1); y += 2) {
        ಗಾಗಿ (x = 0; x < (ಅಗಲ - 1); x += 2) {
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
        ಆದರೆ (x == (ಅಗಲ - 1)) {
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
    ಆದರೆ (y == (ಎತ್ತರ - 1)) {
        ಗಾಗಿ (x = 0; x < (ಅಗಲ - 1); x += 2) {
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
        ಆದರೆ (x == (ಅಗಲ - 1)) {
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
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool SDL_Convert_Pixels_Packed4_ಗಮ್ಯ_Planar2x2(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ,
                                                   SDL_PixelFormat src_format, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಂಕ src_pitch,
                                                   SDL_PixelFormat dst_format, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಂಕ dst_pitch)
{
    ಪೂರ್ಣಾಂಕ x, y;
    ಸ್ಥಿರಾಂಕ Uint8 *srcY1, *srcY2, *srcU1, *srcU2, *srcV1, *srcV2;
    Uint32 srcY_pitch, srcUV_pitch;
    Uint32 src_pitch_ಎಡ;
    Uint8 *dstY1, *dstY2, *dstU, *dstV;
    Uint32 dstY_pitch, dstUV_pitch;
    Uint32 dst_Y_pitch_ಎಡ, dst_UV_pitch_ಎಡ, dstUV_pixel_stride;

    ಆದರೆ (src == dst) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Can't change YUV plane types in-place");
    }

    ಆದರೆ (!GetYUVPlanes(ಅಗಲ, ಎತ್ತರ, src_format, src, src_pitch,
                      &srcY1, &srcU1, &srcV1, &srcY_pitch, &srcUV_pitch)) {
        ಹಿಂತಿರುಗಿ false;
    }
    srcY2 = srcY1 + srcY_pitch;
    srcU2 = srcU1 + srcUV_pitch;
    srcV2 = srcV1 + srcUV_pitch;
    src_pitch_ಎಡ = (srcY_pitch - 4 * ((ಅಗಲ + 1) / 2));

    ಆದರೆ (!GetYUVPlanes(ಅಗಲ, ಎತ್ತರ, dst_format, dst, dst_pitch,
                      (ಸ್ಥಿರಾಂಕ Uint8 **)&dstY1, (ಸ್ಥಿರಾಂಕ Uint8 **)&dstU, (ಸ್ಥಿರಾಂಕ Uint8 **)&dstV,
                      &dstY_pitch, &dstUV_pitch)) {
        ಹಿಂತಿರುಗಿ false;
    }
    dstY2 = dstY1 + dstY_pitch;
    dst_Y_pitch_ಎಡ = (dstY_pitch - ಅಗಲ);

    ಆದರೆ (dst_format == SDL_PIXELFORMAT_NV12 || dst_format == SDL_PIXELFORMAT_NV21) {
        dstUV_pixel_stride = 2;
        dst_UV_pitch_ಎಡ = (dstUV_pitch - 2 * ((ಅಗಲ + 1) / 2));
    } ಇಲ್ಲದಿದ್ದರೆ {
        dstUV_pixel_stride = 1;
        dst_UV_pitch_ಎಡ = (dstUV_pitch - ((ಅಗಲ + 1) / 2));
    }

    // Copy 2x2 blocks of pixels at a time
    ಗಾಗಿ (y = 0; y < (ಎತ್ತರ - 1); y += 2) {
        ಗಾಗಿ (x = 0; x < (ಅಗಲ - 1); x += 2) {
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
        ಆದರೆ (x == (ಅಗಲ - 1)) {
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
    ಆದರೆ (y == (ಎತ್ತರ - 1)) {
        ಗಾಗಿ (x = 0; x < (ಅಗಲ - 1); x += 2) {
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
        ಆದರೆ (x == (ಅಗಲ - 1)) {
            *dstY1 = *srcY1;
            *dstU = *srcU1;
            *dstV = *srcV1;
        }
    }
    ಹಿಂತಿರುಗಿ true;
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_HAVE_YUV

bool SDL_Convert_Pixels_YUV_ಗಮ್ಯ_YUV(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ,
                                  SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಂಕ src_pitch,
                                  SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಂಕ dst_pitch)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_HAVE_YUV
    ಆದರೆ (src_colorspace != dst_colorspace) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("SDL_ConvertPixels_YUV_to_YUV: colorspace conversion not supported");
    }

    ಆದರೆ (src_format == dst_format) {
        ಆದರೆ (src == dst) {
            // Nothing to do
            ಹಿಂತಿರುಗಿ true;
        }
        ಹಿಂತಿರುಗಿ SDL_Convert_Pixels_YUV_ಗಮ್ಯ_YUV_Copy(ಅಗಲ, ಎತ್ತರ, src_format, src, src_pitch, dst, dst_pitch);
    }

    ಆದರೆ (IsPlanar2x2Format(src_format) && IsPlanar2x2Format(dst_format)) {
        ಹಿಂತಿರುಗಿ SDL_Convert_Pixels_Planar2x2_ಗಮ್ಯ_Planar2x2(ಅಗಲ, ಎತ್ತರ, src_format, src, src_pitch, dst_format, dst, dst_pitch);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (IsPacked4Format(src_format) && IsPacked4Format(dst_format)) {
        ಹಿಂತಿರುಗಿ SDL_Convert_Pixels_Packed4_ಗಮ್ಯ_Packed4(ಅಗಲ, ಎತ್ತರ, src_format, src, src_pitch, dst_format, dst, dst_pitch);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (IsPlanar2x2Format(src_format) && IsPacked4Format(dst_format)) {
        ಹಿಂತಿರುಗಿ SDL_Convert_Pixels_Planar2x2_ಗಮ್ಯ_Packed4(ಅಗಲ, ಎತ್ತರ, src_format, src, src_pitch, dst_format, dst, dst_pitch);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (IsPacked4Format(src_format) && IsPlanar2x2Format(dst_format)) {
        ಹಿಂತಿರುಗಿ SDL_Convert_Pixels_Packed4_ಗಮ್ಯ_Planar2x2(ಅಗಲ, ಎತ್ತರ, src_format, src, src_pitch, dst_format, dst, dst_pitch);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("SDL_ConvertPixels_YUV_to_YUV: Unsupported YUV conversion: %s -> %s", SDL_GetPixelFormatName(src_format),
                            SDL_GetPixelFormatName(dst_format));
    }
#ಇಲ್ಲದಿದ್ದರೆ
    ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("SDL not built with YUV support");
#ಆದರೆ_ಅಂತ್ಯ
}
