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

#ಅನ್ತರ್ಭಾವ "SDL_surface_c.h"

#ifdef SDL_SSE_INTRINSICS
/* *INDENT-OFF* */ // clang-format off

#ಯದಿ defined(_MSC_VER) && !defined(__clang__)
#define SSE_BEGIN \
    __m128 c128; \
    c128.m128_u32[0] = color; \
    c128.m128_u32[1] = color; \
    c128.m128_u32[2] = color; \
    c128.m128_u32[3] = color
#ಅನ್ಯಥಾ
#define SSE_BEGIN \
    __m128 c128; \
    DECLARE_ALIGNED(Uint32, cccc[4], 16); \
    cccc[0] = color; \
    cccc[1] = color; \
    cccc[2] = color; \
    cccc[3] = color; \
    c128 = *(__m128 *)cccc
#endif

#define SSE_WORK \
    ಪ್ರತಿ (i = n / 64; i--;) { \
        _mm_stream_ps((ಭಿನ್ನ *)(p+0), c128); \
        _mm_stream_ps((ಭಿನ್ನ *)(p+16), c128); \
        _mm_stream_ps((ಭಿನ್ನ *)(p+32), c128); \
        _mm_stream_ps((ಭಿನ್ನ *)(p+48), c128); \
        p += 64; \
    }

#define SSE_END

#define DEFINE_SSE_FILLRECT(bpp, type) \
ಸ್ಥಿರ ಶೂನ್ಯ SDL_TARGETING("sse") SDL_FillSurfaceRect##bpp##SSE(Uint8 *pixels, ಪೂರ್ಣಾಙ್ಕ pitch, Uint32 color, ಪೂರ್ಣಾಙ್ಕ w, ಪೂರ್ಣಾಙ್ಕ h) \
{ \
    ಪೂರ್ಣಾಙ್ಕ i, n; \
    Uint8 *p = ರಿಕ್ತ; \
  \
    /* If the number of bytes per row is equal to the pitch, treat */ \
    /* all rows as one long continuous row (for better performance) */ \
    ಯದಿ ((w) * (bpp) == pitch) { \
        w = w * h; \
        h = 1; \
    } \
 \
    SSE_BEGIN; \
 \
    ಯಾವತ್ (h--) { \
        n = (w) * (bpp); \
        p = pixels; \
 \
        ಯದಿ (n > 63) { \
            ಪೂರ್ಣಾಙ್ಕ adjust = 16 - ((uintptr_t)p & 15); \
            ಯದಿ (adjust < 16) { \
                n -= adjust; \
                adjust /= (bpp); \
                ಯಾವತ್ (adjust--) { \
                    *((type *)p) = (type)color; \
                    p += (bpp); \
                } \
            } \
            SSE_WORK; \
        } \
        ಯದಿ (n & 63) { \
            ಪೂರ್ಣಾಙ್ಕ remainder = (n & 63); \
            remainder /= (bpp); \
            ಯಾವತ್ (remainder--) { \
                *((type *)p) = (type)color; \
                p += (bpp); \
            } \
        } \
        pixels += pitch; \
    } \
 \
    SSE_END; \
}

ಸ್ಥಿರ ಶೂನ್ಯ SDL_TARGETING("sse") SDL_FillSurfaceRect1SSE(Uint8 *pixels, ಪೂರ್ಣಾಙ್ಕ pitch, Uint32 color, ಪೂರ್ಣಾಙ್ಕ w, ಪೂರ್ಣಾಙ್ಕ h)
{
    ಪೂರ್ಣಾಙ್ಕ i, n;

    SSE_BEGIN;
    ಯಾವತ್ (h--) {
        Uint8 *p = pixels;
        n = w;

        ಯದಿ (n > 63) {
            ಪೂರ್ಣಾಙ್ಕ adjust = 16 - ((uintptr_t)p & 15);
            ಯದಿ (adjust) {
                n -= adjust;
                SDL_memset(p, color, adjust);
                p += adjust;
            }
            SSE_WORK;
        }
        ಯದಿ (n & 63) {
            ಪೂರ್ಣಾಙ್ಕ remainder = (n & 63);
            SDL_memset(p, color, remainder);
        }
        pixels += pitch;
    }

    SSE_END;
}
// DEFINE_SSE_FILLRECT(1, Uint8)
DEFINE_SSE_FILLRECT(2, Uint16)
DEFINE_SSE_FILLRECT(4, Uint32)

/* *INDENT-ON* */ // clang-format on
#endif            // SDL_SSE_INTRINSICS

#ifdef SDL_LSX_INTRINSICS
/* *INDENT-OFF* */ // clang-format off

#define LSX_BEGIN __m128i c128 = __lsx_vreplgr2vr_w(color);

#define LSX_WORK \
    ಪ್ರತಿ (i = n / 64; i--;) { \
        __lsx_vst(c128, p, 0); \
        __lsx_vst(c128, p, 16); \
        __lsx_vst(c128, p, 32); \
        __lsx_vst(c128, p, 48); \
        p += 64; \
    }

#define DEFINE_LSX_FILLRECT(bpp, type) \
ಸ್ಥಿರ ಶೂನ್ಯ SDL_TARGETING("lsx") SDL_FillSurfaceRect##bpp##LSX(Uint8 *pixels, ಪೂರ್ಣಾಙ್ಕ pitch, Uint32 color, ಪೂರ್ಣಾಙ್ಕ w, ಪೂರ್ಣಾಙ್ಕ h) \
{ \
    ಪೂರ್ಣಾಙ್ಕ i, n; \
    Uint8 *p = ರಿಕ್ತ; \
  \
    /* If the number of bytes per row is equal to the pitch, treat */ \
    /* all rows as one long continuous row (for better performance) */ \
    ಯದಿ ((w) * (bpp) == pitch) { \
        w = w * h; \
        h = 1; \
    } \
 \
    LSX_BEGIN; \
 \
    ಯಾವತ್ (h--) { \
        n = (w) * (bpp); \
        p = pixels; \
 \
        ಯದಿ (n > 63) { \
            ಪೂರ್ಣಾಙ್ಕ adjust = 16 - ((uintptr_t)p & 15); \
            ಯದಿ (adjust < 16) { \
                n -= adjust; \
                adjust /= (bpp); \
                ಯಾವತ್ (adjust--) { \
                    *((type *)p) = (type)color; \
                    p += (bpp); \
                } \
            } \
            LSX_WORK; \
        } \
        ಯದಿ (n & 63) { \
            ಪೂರ್ಣಾಙ್ಕ remainder = (n & 63); \
            remainder /= (bpp); \
            ಯಾವತ್ (remainder--) { \
                *((type *)p) = (type)color; \
                p += (bpp); \
            } \
        } \
        pixels += pitch; \
    } \
 \
}

DEFINE_LSX_FILLRECT(4, Uint32)

/* *INDENT-ON* */ // clang-format on
#endif // SDL_LSX_INTRINSICS

ಸ್ಥಿರ ಶೂನ್ಯ SDL_FillSurfaceRect1(Uint8 *pixels, ಪೂರ್ಣಾಙ್ಕ pitch, Uint32 color, ಪೂರ್ಣಾಙ್ಕ w, ಪೂರ್ಣಾಙ್ಕ h)
{
    ಪೂರ್ಣಾಙ್ಕ n;
    Uint8 *p = ರಿಕ್ತ;

    ಯಾವತ್ (h--) {
        n = w;
        p = pixels;

        ಯದಿ (n > 3) {
            ವಿಕಲ್ಪ ((uintptr_t)p & 3) {
            ಪಕ್ಷ 1:
                *p++ = (Uint8)color;
                --n;
                SDL_FALLTHROUGH;
            ಪಕ್ಷ 2:
                *p++ = (Uint8)color;
                --n;
                SDL_FALLTHROUGH;
            ಪಕ್ಷ 3:
                *p++ = (Uint8)color;
                --n;
            }
            SDL_memset4(p, color, (n >> 2));
        }
        ಯದಿ (n & 3) {
            p += (n & ~3);
            ವಿಕಲ್ಪ (n & 3) {
            ಪಕ್ಷ 3:
                *p++ = (Uint8)color;
                SDL_FALLTHROUGH;
            ಪಕ್ಷ 2:
                *p++ = (Uint8)color;
                SDL_FALLTHROUGH;
            ಪಕ್ಷ 1:
                *p++ = (Uint8)color;
            }
        }
        pixels += pitch;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ SDL_FillSurfaceRect2(Uint8 *pixels, ಪೂರ್ಣಾಙ್ಕ pitch, Uint32 color, ಪೂರ್ಣಾಙ್ಕ w, ಪೂರ್ಣಾಙ್ಕ h)
{
    ಪೂರ್ಣಾಙ್ಕ n;
    Uint16 *p = ರಿಕ್ತ;

    ಯಾವತ್ (h--) {
        n = w;
        p = (Uint16 *)pixels;

        ಯದಿ (n > 1) {
            ಯದಿ ((uintptr_t)p & 2) {
                *p++ = (Uint16)color;
                --n;
            }
            SDL_memset4(p, color, (n >> 1));
        }
        ಯದಿ (n & 1) {
            p[n - 1] = (Uint16)color;
        }
        pixels += pitch;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ SDL_FillSurfaceRect3(Uint8 *pixels, ಪೂರ್ಣಾಙ್ಕ pitch, Uint32 color, ಪೂರ್ಣಾಙ್ಕ w, ಪೂರ್ಣಾಙ್ಕ h)
{
#ಯದಿ SDL_BYTEORDER == SDL_LIL_ENDIAN
    Uint8 b1 = (Uint8)(color & 0xFF);
    Uint8 b2 = (Uint8)((color >> 8) & 0xFF);
    Uint8 b3 = (Uint8)((color >> 16) & 0xFF);
#ನೋಚೇದ್ಯದಿ SDL_BYTEORDER == SDL_BIG_ENDIAN
    Uint8 b1 = (Uint8)((color >> 16) & 0xFF);
    Uint8 b2 = (Uint8)((color >> 8) & 0xFF);
    Uint8 b3 = (Uint8)(color & 0xFF);
#endif
    ಪೂರ್ಣಾಙ್ಕ n;
    Uint8 *p = ರಿಕ್ತ;

    ಯಾವತ್ (h--) {
        n = w;
        p = pixels;

        ಯಾವತ್ (n--) {
            *p++ = b1;
            *p++ = b2;
            *p++ = b3;
        }
        pixels += pitch;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ SDL_FillSurfaceRect4(Uint8 *pixels, ಪೂರ್ಣಾಙ್ಕ pitch, Uint32 color, ಪೂರ್ಣಾಙ್ಕ w, ಪೂರ್ಣಾಙ್ಕ h)
{
    ಯಾವತ್ (h--) {
        SDL_memset4(pixels, color, w);
        pixels += pitch;
    }
}

/*
 * This function performs a fast fill of the given rectangle with 'color'
 */
bool SDL_FillSurfaceRect(SDL_Surface *dst, ಧ್ರುವ SDL_Rect *rect, Uint32 color)
{
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("SDL_FillSurfaceRect(): dst");
    }

    // If 'rect' == NULL, then fill the whole surface
    ಯದಿ (!rect) {
        rect = &dst->clip_rect;
        // Don't attempt to fill if the surface's clip_rect is empty
        ಯದಿ (SDL_RectEmpty(rect)) {
            ಪ್ರತ್ಯಾಗಮ true;
        }
    }

    ಪ್ರತ್ಯಾಗಮ SDL_FillSurfaceRects(dst, rect, 1, color);
}

bool SDL_FillSurfaceRects(SDL_Surface *dst, ಧ್ರುವ SDL_Rect *rects, ಪೂರ್ಣಾಙ್ಕ ಎಣಿಕೆ, Uint32 color)
{
    SDL_Rect clipped;
    Uint8 *pixels;
    ಧ್ರುವ SDL_Rect *rect;
    ಶೂನ್ಯ (*fill_function)(Uint8 * pixels, ಪೂರ್ಣಾಙ್ಕ pitch, Uint32 color, ಪೂರ್ಣಾಙ್ಕ w, ಪೂರ್ಣಾಙ್ಕ h) = ರಿಕ್ತ;
    ಪೂರ್ಣಾಙ್ಕ i;

    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("SDL_FillSurfaceRects(): dst");
    }

    CHECK_PARAM(!rects) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("SDL_FillSurfaceRects(): rects");
    }

    ಯದಿ (!dst->pixels && SDL_MUSTLOCK(dst)) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("SDL_FillSurfaceRects(): You must lock the surface");
    }

    // Nothing to do
    ಯದಿ (dst->w == 0 || dst->h == 0 || !dst->pixels) {
        ಪ್ರತ್ಯಾಗಮ true;
    }

    /* This function doesn't usually work on surfaces < 8 bpp
     * Except: support for 4bits, when filling full size.
     */
    ಯದಿ (SDL_BITSPERPIXEL(dst->format) < 8) {
        ಯದಿ (ಎಣಿಕೆ == 1) {
            ಧ್ರುವ SDL_Rect *r = &rects[0];
            ಯದಿ (r->x == 0 && r->y == 0 && r->w == dst->w && r->h == dst->h) {
                ಯದಿ (SDL_BITSPERPIXEL(dst->format) == 4) {
                    Uint8 b = (((Uint8)color << 4) | (Uint8)color);
                    SDL_memset(dst->pixels, b, (size_t)dst->h * dst->pitch);
                    ಪ್ರತ್ಯಾಗಮ true;
                }
            }
        }
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("SDL_FillSurfaceRects(): Unsupported surface format");
    }

    ಯದಿ (fill_function == ರಿಕ್ತ) {
        ವಿಕಲ್ಪ (SDL_BYTESPERPIXEL(dst->format)) {
        ಪಕ್ಷ 1:
        {
            color |= (color << 8);
            color |= (color << 16);
#ifdef SDL_SSE_INTRINSICS
            ಯದಿ (SDL_HasSSE()) {
                fill_function = SDL_FillSurfaceRect1SSE;
                ಭಙ್ಗ;
            }
#endif
            fill_function = SDL_FillSurfaceRect1;
            ಭಙ್ಗ;
        }

        ಪಕ್ಷ 2:
        {
            color |= (color << 16);
#ifdef SDL_SSE_INTRINSICS
            ಯದಿ (SDL_HasSSE()) {
                fill_function = SDL_FillSurfaceRect2SSE;
                ಭಙ್ಗ;
            }
#endif
            fill_function = SDL_FillSurfaceRect2;
            ಭಙ್ಗ;
        }

        ಪಕ್ಷ 3:
            // 24-bit RGB is a slow path, at least for now.
            {
                fill_function = SDL_FillSurfaceRect3;
                ಭಙ್ಗ;
            }

        ಪಕ್ಷ 4:
        {
#ifdef SDL_SSE_INTRINSICS
            ಯದಿ (SDL_HasSSE()) {
                fill_function = SDL_FillSurfaceRect4SSE;
                ಭಙ್ಗ;
            }
#endif
#ifdef SDL_LSX_INTRINSICS
            ಯದಿ (SDL_HasLSX()) {
                fill_function = SDL_FillSurfaceRect4LSX;
                ಭಙ್ಗ;
            }
#endif
            fill_function = SDL_FillSurfaceRect4;
            ಭಙ್ಗ;
        }

        ಸ್ವಭಾವ:
            ಪ್ರತ್ಯಾಗಮ SDL_SetError("Unsupported pixel format");
        }
    }

    ಪ್ರತಿ (i = 0; i < ಎಣಿಕೆ; ++i) {
        rect = &rects[i];
        // Perform clipping
        ಯದಿ (!SDL_GetRectIntersection(rect, &dst->clip_rect, &clipped)) {
            ಅನುವರ್ತ;
        }
        rect = &clipped;

        pixels = (Uint8 *)dst->pixels + rect->y * dst->pitch +
                 rect->x * SDL_BYTESPERPIXEL(dst->format);

        fill_function(pixels, dst->pitch, color, rect->w, rect->h);
    }

    // We're done!
    ಪ್ರತ್ಯಾಗಮ true;
}
