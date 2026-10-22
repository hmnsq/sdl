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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_SSE_INTRINSICS
/* *INDENT-OFF* */ // clang-format off

#ಆದರೆ defined(_MSC_VER) && !defined(__clang__)
#ವ್ಯಾಖ್ಯಾನಿಸು SSE_BEGIN \
    __m128 c128; \
    c128.m128_u32[0] = color; \
    c128.m128_u32[1] = color; \
    c128.m128_u32[2] = color; \
    c128.m128_u32[3] = color
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು SSE_BEGIN \
    __m128 c128; \
    DECLARE_ALIGNED(Uint32, cccc[4], 16); \
    cccc[0] = color; \
    cccc[1] = color; \
    cccc[2] = color; \
    cccc[3] = color; \
    c128 = *(__m128 *)cccc
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿಸು SSE_WORK \
    ಗಾಗಿ (i = n / 64; i--;) { \
        mm_ಹರಿವು_ps((ದಶಮಾಂಶ *)(p+0), c128); \
        mm_ಹರಿವು_ps((ದಶಮಾಂಶ *)(p+16), c128); \
        mm_ಹರಿವು_ps((ದಶಮಾಂಶ *)(p+32), c128); \
        mm_ಹರಿವು_ps((ದಶಮಾಂಶ *)(p+48), c128); \
        p += 64; \
    }

#ವ್ಯಾಖ್ಯಾನಿಸು SSE_ಕೊನೆ

#ವ್ಯಾಖ್ಯಾನಿಸು DEFINE_SSE_FILLRECT(bpp, type) \
ಸ್ಥಿರ ಶೂನ್ಯ SDL_TARGETING("sse") SDL_FillSurfaceRect##bpp##SSE(Uint8 *pixels, ಪೂರ್ಣಾಂಕ pitch, Uint32 color, ಪೂರ್ಣಾಂಕ w, ಪೂರ್ಣಾಂಕ h) \
{ \
    ಪೂರ್ಣಾಂಕ i, n; \
    Uint8 *p = ಖಾಲಿ; \
  \
    /* If the number of bytes per row is equal to the pitch, treat */ \
    /* all rows as one long continuous row (for better performance) */ \
    ಆದರೆ ((w) * (bpp) == pitch) { \
        w = w * h; \
        h = 1; \
    } \
 \
    SSE_BEGIN; \
 \
    ಆಗ (h--) { \
        n = (w) * (bpp); \
        p = pixels; \
 \
        ಆದರೆ (n > 63) { \
            ಪೂರ್ಣಾಂಕ adjust = 16 - ((uintptr_t)p & 15); \
            ಆದರೆ (adjust < 16) { \
                n -= adjust; \
                adjust /= (bpp); \
                ಆಗ (adjust--) { \
                    *((type *)p) = (type)color; \
                    p += (bpp); \
                } \
            } \
            SSE_WORK; \
        } \
        ಆದರೆ (n & 63) { \
            ಪೂರ್ಣಾಂಕ remainder = (n & 63); \
            remainder /= (bpp); \
            ಆಗ (remainder--) { \
                *((type *)p) = (type)color; \
                p += (bpp); \
            } \
        } \
        pixels += pitch; \
    } \
 \
    SSE_ಕೊನೆ; \
}

ಸ್ಥಿರ ಶೂನ್ಯ SDL_TARGETING("sse") SDL_FillSurfaceRect1SSE(Uint8 *pixels, ಪೂರ್ಣಾಂಕ pitch, Uint32 color, ಪೂರ್ಣಾಂಕ w, ಪೂರ್ಣಾಂಕ h)
{
    ಪೂರ್ಣಾಂಕ i, n;

    SSE_BEGIN;
    ಆಗ (h--) {
        Uint8 *p = pixels;
        n = w;

        ಆದರೆ (n > 63) {
            ಪೂರ್ಣಾಂಕ adjust = 16 - ((uintptr_t)p & 15);
            ಆದರೆ (adjust) {
                n -= adjust;
                SDL_memset(p, color, adjust);
                p += adjust;
            }
            SSE_WORK;
        }
        ಆದರೆ (n & 63) {
            ಪೂರ್ಣಾಂಕ remainder = (n & 63);
            SDL_memset(p, color, remainder);
        }
        pixels += pitch;
    }

    SSE_ಕೊನೆ;
}
// DEFINE_SSE_FILLRECT(1, Uint8)
DEFINE_SSE_FILLRECT(2, Uint16)
DEFINE_SSE_FILLRECT(4, Uint32)

/* *INDENT-ON* */ // clang-format on
#ಆದರೆ_ಅಂತ್ಯ            // SDL_SSE_INTRINSICS

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_LSX_INTRINSICS
/* *INDENT-OFF* */ // clang-format off

#ವ್ಯಾಖ್ಯಾನಿಸು LSX_BEGIN __m128i c128 = __lsx_vreplgr2vr_w(color);

#ವ್ಯಾಖ್ಯಾನಿಸು LSX_WORK \
    ಗಾಗಿ (i = n / 64; i--;) { \
        __lsx_vst(c128, p, 0); \
        __lsx_vst(c128, p, 16); \
        __lsx_vst(c128, p, 32); \
        __lsx_vst(c128, p, 48); \
        p += 64; \
    }

#ವ್ಯಾಖ್ಯಾನಿಸು DEFINE_LSX_FILLRECT(bpp, type) \
ಸ್ಥಿರ ಶೂನ್ಯ SDL_TARGETING("lsx") SDL_FillSurfaceRect##bpp##LSX(Uint8 *pixels, ಪೂರ್ಣಾಂಕ pitch, Uint32 color, ಪೂರ್ಣಾಂಕ w, ಪೂರ್ಣಾಂಕ h) \
{ \
    ಪೂರ್ಣಾಂಕ i, n; \
    Uint8 *p = ಖಾಲಿ; \
  \
    /* If the number of bytes per row is equal to the pitch, treat */ \
    /* all rows as one long continuous row (for better performance) */ \
    ಆದರೆ ((w) * (bpp) == pitch) { \
        w = w * h; \
        h = 1; \
    } \
 \
    LSX_BEGIN; \
 \
    ಆಗ (h--) { \
        n = (w) * (bpp); \
        p = pixels; \
 \
        ಆದರೆ (n > 63) { \
            ಪೂರ್ಣಾಂಕ adjust = 16 - ((uintptr_t)p & 15); \
            ಆದರೆ (adjust < 16) { \
                n -= adjust; \
                adjust /= (bpp); \
                ಆಗ (adjust--) { \
                    *((type *)p) = (type)color; \
                    p += (bpp); \
                } \
            } \
            LSX_WORK; \
        } \
        ಆದರೆ (n & 63) { \
            ಪೂರ್ಣಾಂಕ remainder = (n & 63); \
            remainder /= (bpp); \
            ಆಗ (remainder--) { \
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
#ಆದರೆ_ಅಂತ್ಯ // SDL_LSX_INTRINSICS

ಸ್ಥಿರ ಶೂನ್ಯ SDL_FillSurfaceRect1(Uint8 *pixels, ಪೂರ್ಣಾಂಕ pitch, Uint32 color, ಪೂರ್ಣಾಂಕ w, ಪೂರ್ಣಾಂಕ h)
{
    ಪೂರ್ಣಾಂಕ n;
    Uint8 *p = ಖಾಲಿ;

    ಆಗ (h--) {
        n = w;
        p = pixels;

        ಆದರೆ (n > 3) {
            ಆಯ್ಕೆ ((uintptr_t)p & 3) {
            ಸ್ಥಿತಿ 1:
                *p++ = (Uint8)color;
                --n;
                SDL_FALLTHROUGH;
            ಸ್ಥಿತಿ 2:
                *p++ = (Uint8)color;
                --n;
                SDL_FALLTHROUGH;
            ಸ್ಥಿತಿ 3:
                *p++ = (Uint8)color;
                --n;
            }
            SDL_memset4(p, color, (n >> 2));
        }
        ಆದರೆ (n & 3) {
            p += (n & ~3);
            ಆಯ್ಕೆ (n & 3) {
            ಸ್ಥಿತಿ 3:
                *p++ = (Uint8)color;
                SDL_FALLTHROUGH;
            ಸ್ಥಿತಿ 2:
                *p++ = (Uint8)color;
                SDL_FALLTHROUGH;
            ಸ್ಥಿತಿ 1:
                *p++ = (Uint8)color;
            }
        }
        pixels += pitch;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ SDL_FillSurfaceRect2(Uint8 *pixels, ಪೂರ್ಣಾಂಕ pitch, Uint32 color, ಪೂರ್ಣಾಂಕ w, ಪೂರ್ಣಾಂಕ h)
{
    ಪೂರ್ಣಾಂಕ n;
    Uint16 *p = ಖಾಲಿ;

    ಆಗ (h--) {
        n = w;
        p = (Uint16 *)pixels;

        ಆದರೆ (n > 1) {
            ಆದರೆ ((uintptr_t)p & 2) {
                *p++ = (Uint16)color;
                --n;
            }
            SDL_memset4(p, color, (n >> 1));
        }
        ಆದರೆ (n & 1) {
            p[n - 1] = (Uint16)color;
        }
        pixels += pitch;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ SDL_FillSurfaceRect3(Uint8 *pixels, ಪೂರ್ಣಾಂಕ pitch, Uint32 color, ಪೂರ್ಣಾಂಕ w, ಪೂರ್ಣಾಂಕ h)
{
#ಆದರೆ SDL_BYTEORDER == SDL_LIL_ENDIAN
    Uint8 b1 = (Uint8)(color & 0xFF);
    Uint8 b2 = (Uint8)((color >> 8) & 0xFF);
    Uint8 b3 = (Uint8)((color >> 16) & 0xFF);
#ಅಥವಾಆದರೆ SDL_BYTEORDER == SDL_BIG_ENDIAN
    Uint8 b1 = (Uint8)((color >> 16) & 0xFF);
    Uint8 b2 = (Uint8)((color >> 8) & 0xFF);
    Uint8 b3 = (Uint8)(color & 0xFF);
#ಆದರೆ_ಅಂತ್ಯ
    ಪೂರ್ಣಾಂಕ n;
    Uint8 *p = ಖಾಲಿ;

    ಆಗ (h--) {
        n = w;
        p = pixels;

        ಆಗ (n--) {
            *p++ = b1;
            *p++ = b2;
            *p++ = b3;
        }
        pixels += pitch;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ SDL_FillSurfaceRect4(Uint8 *pixels, ಪೂರ್ಣಾಂಕ pitch, Uint32 color, ಪೂರ್ಣಾಂಕ w, ಪೂರ್ಣಾಂಕ h)
{
    ಆಗ (h--) {
        SDL_memset4(pixels, color, w);
        pixels += pitch;
    }
}

/*
 * This function performs a fast fill of the given rectangle with 'color'
 */
bool SDL_FillSurfaceRect(SDL_Surface *dst, ಸ್ಥಿರಾಂಕ SDL_Rect *rect, Uint32 color)
{
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("SDL_FillSurfaceRect(): dst");
    }

    // If 'rect' == NULL, then fill the whole surface
    ಆದರೆ (!rect) {
        rect = &dst->clip_rect;
        // Don't attempt to fill if the surface's clip_rect is empty
        ಆದರೆ (SDL_Rect_ಖಾಲಿಗಳು(rect)) {
            ಹಿಂತಿರುಗಿ true;
        }
    }

    ಹಿಂತಿರುಗಿ SDL_FillSurfaceRects(dst, rect, 1, color);
}

bool SDL_FillSurfaceRects(SDL_Surface *dst, ಸ್ಥಿರಾಂಕ SDL_Rect *rects, ಪೂರ್ಣಾಂಕ ಎಣಿಕೆ_2, Uint32 color)
{
    SDL_Rect clipped;
    Uint8 *pixels;
    ಸ್ಥಿರಾಂಕ SDL_Rect *rect;
    ಶೂನ್ಯ (*fill_function)(Uint8 * pixels, ಪೂರ್ಣಾಂಕ pitch, Uint32 color, ಪೂರ್ಣಾಂಕ w, ಪೂರ್ಣಾಂಕ h) = ಖಾಲಿ;
    ಪೂರ್ಣಾಂಕ i;

    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("SDL_FillSurfaceRects(): dst");
    }

    CHECK_PARAM(!rects) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("SDL_FillSurfaceRects(): rects");
    }

    ಆದರೆ (!dst->pixels && SDL_MUSTLOCK(dst)) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("SDL_FillSurfaceRects(): You must lock the surface");
    }

    // Nothing to do
    ಆದರೆ (dst->w == 0 || dst->h == 0 || !dst->pixels) {
        ಹಿಂತಿರುಗಿ true;
    }

    /* This function doesn't usually work on surfaces < 8 bpp
     * Except: support for 4bits, when filling full size.
     */
    ಆದರೆ (SDL_BITSPERPIXEL(dst->format) < 8) {
        ಆದರೆ (ಎಣಿಕೆ_2 == 1) {
            ಸ್ಥಿರಾಂಕ SDL_Rect *r = &rects[0];
            ಆದರೆ (r->x == 0 && r->y == 0 && r->w == dst->w && r->h == dst->h) {
                ಆದರೆ (SDL_BITSPERPIXEL(dst->format) == 4) {
                    Uint8 b = (((Uint8)color << 4) | (Uint8)color);
                    SDL_memset(dst->pixels, b, (size_t)dst->h * dst->pitch);
                    ಹಿಂತಿರುಗಿ true;
                }
            }
        }
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("SDL_FillSurfaceRects(): Unsupported surface format");
    }

    ಆದರೆ (fill_function == ಖಾಲಿ) {
        ಆಯ್ಕೆ (SDL_BYTESPERPIXEL(dst->format)) {
        ಸ್ಥಿತಿ 1:
        {
            color |= (color << 8);
            color |= (color << 16);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_SSE_INTRINSICS
            ಆದರೆ (SDL_HasSSE()) {
                fill_function = SDL_FillSurfaceRect1SSE;
                ನಿಲ್ಲಿಸು;
            }
#ಆದರೆ_ಅಂತ್ಯ
            fill_function = SDL_FillSurfaceRect1;
            ನಿಲ್ಲಿಸು;
        }

        ಸ್ಥಿತಿ 2:
        {
            color |= (color << 16);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_SSE_INTRINSICS
            ಆದರೆ (SDL_HasSSE()) {
                fill_function = SDL_FillSurfaceRect2SSE;
                ನಿಲ್ಲಿಸು;
            }
#ಆದರೆ_ಅಂತ್ಯ
            fill_function = SDL_FillSurfaceRect2;
            ನಿಲ್ಲಿಸು;
        }

        ಸ್ಥಿತಿ 3:
            // 24-bit RGB is a slow path, at least for now.
            {
                fill_function = SDL_FillSurfaceRect3;
                ನಿಲ್ಲಿಸು;
            }

        ಸ್ಥಿತಿ 4:
        {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_SSE_INTRINSICS
            ಆದರೆ (SDL_HasSSE()) {
                fill_function = SDL_FillSurfaceRect4SSE;
                ನಿಲ್ಲಿಸು;
            }
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_LSX_INTRINSICS
            ಆದರೆ (SDL_HasLSX()) {
                fill_function = SDL_FillSurfaceRect4LSX;
                ನಿಲ್ಲಿಸು;
            }
#ಆದರೆ_ಅಂತ್ಯ
            fill_function = SDL_FillSurfaceRect4;
            ನಿಲ್ಲಿಸು;
        }

        ಪೂರ್ವನಿಯೋಜಿತ:
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Unsupported pixel format");
        }
    }

    ಗಾಗಿ (i = 0; i < ಎಣಿಕೆ_2; ++i) {
        rect = &rects[i];
        // Perform clipping
        ಆದರೆ (!SDL_GetRectIntersection(rect, &dst->clip_rect, &clipped)) {
            ಮುಂದುವರಿ;
        }
        rect = &clipped;

        pixels = (Uint8 *)dst->pixels + rect->y * dst->pitch +
                 rect->x * SDL_BYTESPERPIXEL(dst->format);

        fill_function(pixels, dst->pitch, color, rect->w, rect->h);
    }

    // We're done!
    ಹಿಂತಿರುಗಿ true;
}
