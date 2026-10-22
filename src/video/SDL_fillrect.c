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

#include "SDL_surface_c.h"

#ifdef SDL_SSE_INTRINSICS
/* *INDENT-OFF* */ // clang-format off

#ប្រសិនបើ defined(_MSC_VER) && !defined(__clang__)
#define SSE_BEGIN \
    __m128 c128; \
    c128.m128_u32[0] = color; \
    c128.m128_u32[1] = color; \
    c128.m128_u32[2] = color; \
    c128.m128_u32[3] = color
#បើមិនដូច្នេះ
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
    សម្រាប់ (i = n / 64; i--;) { \
        _mm_stream_ps((float *)(p+0), c128); \
        _mm_stream_ps((float *)(p+16), c128); \
        _mm_stream_ps((float *)(p+32), c128); \
        _mm_stream_ps((float *)(p+48), c128); \
        p += 64; \
    }

#define SSE_END

#define DEFINE_SSE_FILLRECT(bpp, type) \
static void SDL_TARGETING("sse") SDL_FillSurfaceRect##bpp##SSE(Uint8 *pixels, ចំនួនគត់ pitch, Uint32 color, ចំនួនគត់ w, ចំនួនគត់ h) \
{ \
    ចំនួនគត់ i, n; \
    Uint8 *p = NULL; \
  \
    /* If the number of bytes per row is equal to the pitch, treat */ \
    /* all rows as one long continuous row (for better performance) */ \
    ប្រសិនបើ ((w) * (bpp) == pitch) { \
        w = w * h; \
        h = 1; \
    } \
 \
    SSE_BEGIN; \
 \
    ខណៈពេល (h--) { \
        n = (w) * (bpp); \
        p = pixels; \
 \
        ប្រសិនបើ (n > 63) { \
            ចំនួនគត់ adjust = 16 - ((uintptr_t)p & 15); \
            ប្រសិនបើ (adjust < 16) { \
                n -= adjust; \
                adjust /= (bpp); \
                ខណៈពេល (adjust--) { \
                    *((type *)p) = (type)color; \
                    p += (bpp); \
                } \
            } \
            SSE_WORK; \
        } \
        ប្រសិនបើ (n & 63) { \
            ចំនួនគត់ remainder = (n & 63); \
            remainder /= (bpp); \
            ខណៈពេល (remainder--) { \
                *((type *)p) = (type)color; \
                p += (bpp); \
            } \
        } \
        pixels += pitch; \
    } \
 \
    SSE_END; \
}

static void SDL_TARGETING("sse") SDL_FillSurfaceRect1SSE(Uint8 *pixels, ចំនួនគត់ pitch, Uint32 color, ចំនួនគត់ w, ចំនួនគត់ h)
{
    ចំនួនគត់ i, n;

    SSE_BEGIN;
    ខណៈពេល (h--) {
        Uint8 *p = pixels;
        n = w;

        ប្រសិនបើ (n > 63) {
            ចំនួនគត់ adjust = 16 - ((uintptr_t)p & 15);
            ប្រសិនបើ (adjust) {
                n -= adjust;
                SDL_memset(p, color, adjust);
                p += adjust;
            }
            SSE_WORK;
        }
        ប្រសិនបើ (n & 63) {
            ចំនួនគត់ remainder = (n & 63);
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
    សម្រាប់ (i = n / 64; i--;) { \
        __lsx_vst(c128, p, 0); \
        __lsx_vst(c128, p, 16); \
        __lsx_vst(c128, p, 32); \
        __lsx_vst(c128, p, 48); \
        p += 64; \
    }

#define DEFINE_LSX_FILLRECT(bpp, type) \
static void SDL_TARGETING("lsx") SDL_FillSurfaceRect##bpp##LSX(Uint8 *pixels, ចំនួនគត់ pitch, Uint32 color, ចំនួនគត់ w, ចំនួនគត់ h) \
{ \
    ចំនួនគត់ i, n; \
    Uint8 *p = NULL; \
  \
    /* If the number of bytes per row is equal to the pitch, treat */ \
    /* all rows as one long continuous row (for better performance) */ \
    ប្រសិនបើ ((w) * (bpp) == pitch) { \
        w = w * h; \
        h = 1; \
    } \
 \
    LSX_BEGIN; \
 \
    ខណៈពេល (h--) { \
        n = (w) * (bpp); \
        p = pixels; \
 \
        ប្រសិនបើ (n > 63) { \
            ចំនួនគត់ adjust = 16 - ((uintptr_t)p & 15); \
            ប្រសិនបើ (adjust < 16) { \
                n -= adjust; \
                adjust /= (bpp); \
                ខណៈពេល (adjust--) { \
                    *((type *)p) = (type)color; \
                    p += (bpp); \
                } \
            } \
            LSX_WORK; \
        } \
        ប្រសិនបើ (n & 63) { \
            ចំនួនគត់ remainder = (n & 63); \
            remainder /= (bpp); \
            ខណៈពេល (remainder--) { \
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

static void SDL_FillSurfaceRect1(Uint8 *pixels, ចំនួនគត់ pitch, Uint32 color, ចំនួនគត់ w, ចំនួនគត់ h)
{
    ចំនួនគត់ n;
    Uint8 *p = NULL;

    ខណៈពេល (h--) {
        n = w;
        p = pixels;

        ប្រសិនបើ (n > 3) {
            switch ((uintptr_t)p & 3) {
            pak_sa 1:
                *p++ = (Uint8)color;
                --n;
                SDL_FALLTHROUGH;
            pak_sa 2:
                *p++ = (Uint8)color;
                --n;
                SDL_FALLTHROUGH;
            pak_sa 3:
                *p++ = (Uint8)color;
                --n;
            }
            SDL_memset4(p, color, (n >> 2));
        }
        ប្រសិនបើ (n & 3) {
            p += (n & ~3);
            switch (n & 3) {
            pak_sa 3:
                *p++ = (Uint8)color;
                SDL_FALLTHROUGH;
            pak_sa 2:
                *p++ = (Uint8)color;
                SDL_FALLTHROUGH;
            pak_sa 1:
                *p++ = (Uint8)color;
            }
        }
        pixels += pitch;
    }
}

static void SDL_FillSurfaceRect2(Uint8 *pixels, ចំនួនគត់ pitch, Uint32 color, ចំនួនគត់ w, ចំនួនគត់ h)
{
    ចំនួនគត់ n;
    Uint16 *p = NULL;

    ខណៈពេល (h--) {
        n = w;
        p = (Uint16 *)pixels;

        ប្រសិនបើ (n > 1) {
            ប្រសិនបើ ((uintptr_t)p & 2) {
                *p++ = (Uint16)color;
                --n;
            }
            SDL_memset4(p, color, (n >> 1));
        }
        ប្រសិនបើ (n & 1) {
            p[n - 1] = (Uint16)color;
        }
        pixels += pitch;
    }
}

static void SDL_FillSurfaceRect3(Uint8 *pixels, ចំនួនគត់ pitch, Uint32 color, ចំនួនគត់ w, ចំនួនគត់ h)
{
#ប្រសិនបើ SDL_BYTEORDER == SDL_LIL_ENDIAN
    Uint8 b1 = (Uint8)(color & 0xFF);
    Uint8 b2 = (Uint8)((color >> 8) & 0xFF);
    Uint8 b3 = (Uint8)((color >> 16) & 0xFF);
#elif SDL_BYTEORDER == SDL_BIG_ENDIAN
    Uint8 b1 = (Uint8)((color >> 16) & 0xFF);
    Uint8 b2 = (Uint8)((color >> 8) & 0xFF);
    Uint8 b3 = (Uint8)(color & 0xFF);
#endif
    ចំនួនគត់ n;
    Uint8 *p = NULL;

    ខណៈពេល (h--) {
        n = w;
        p = pixels;

        ខណៈពេល (n--) {
            *p++ = b1;
            *p++ = b2;
            *p++ = b3;
        }
        pixels += pitch;
    }
}

static void SDL_FillSurfaceRect4(Uint8 *pixels, ចំនួនគត់ pitch, Uint32 color, ចំនួនគត់ w, ចំនួនគត់ h)
{
    ខណៈពេល (h--) {
        SDL_memset4(pixels, color, w);
        pixels += pitch;
    }
}

/*
 * This function performs a fast fill of the given rectangle with 'color'
 */
bool SDL_FillSurfaceRect(SDL_Surface *dst, const SDL_Rect *rect, Uint32 color)
{
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        ត្រឡប់ SDL_InvalidParamError("SDL_FillSurfaceRect(): dst");
    }

    // If 'rect' == NULL, then fill the whole surface
    ប្រសិនបើ (!rect) {
        rect = &dst->clip_rect;
        // Don't attempt to fill if the surface's clip_rect is empty
        ប្រសិនបើ (SDL_RectEmpty(rect)) {
            ត្រឡប់ true;
        }
    }

    ត្រឡប់ SDL_FillSurfaceRects(dst, rect, 1, color);
}

bool SDL_FillSurfaceRects(SDL_Surface *dst, const SDL_Rect *rects, ចំនួនគត់ count, Uint32 color)
{
    SDL_Rect clipped;
    Uint8 *pixels;
    const SDL_Rect *rect;
    void (*fill_function)(Uint8 * pixels, ចំនួនគត់ pitch, Uint32 color, ចំនួនគត់ w, ចំនួនគត់ h) = NULL;
    ចំនួនគត់ i;

    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        ត្រឡប់ SDL_InvalidParamError("SDL_FillSurfaceRects(): dst");
    }

    CHECK_PARAM(!rects) {
        ត្រឡប់ SDL_InvalidParamError("SDL_FillSurfaceRects(): rects");
    }

    ប្រសិនបើ (!dst->pixels && SDL_MUSTLOCK(dst)) {
        ត្រឡប់ SDL_SetError("SDL_FillSurfaceRects(): You must lock the surface");
    }

    // Nothing to do
    ប្រសិនបើ (dst->w == 0 || dst->h == 0 || !dst->pixels) {
        ត្រឡប់ true;
    }

    /* This function doesn't usually work on surfaces < 8 bpp
     * Except: support for 4bits, when filling full size.
     */
    ប្រសិនបើ (SDL_BITSPERPIXEL(dst->format) < 8) {
        ប្រសិនបើ (count == 1) {
            const SDL_Rect *r = &rects[0];
            ប្រសិនបើ (r->x == 0 && r->y == 0 && r->w == dst->w && r->h == dst->h) {
                ប្រសិនបើ (SDL_BITSPERPIXEL(dst->format) == 4) {
                    Uint8 b = (((Uint8)color << 4) | (Uint8)color);
                    SDL_memset(dst->pixels, b, (size_t)dst->h * dst->pitch);
                    ត្រឡប់ true;
                }
            }
        }
        ត្រឡប់ SDL_SetError("SDL_FillSurfaceRects(): Unsupported surface format");
    }

    ប្រសិនបើ (fill_function == NULL) {
        switch (SDL_BYTESPERPIXEL(dst->format)) {
        pak_sa 1:
        {
            color |= (color << 8);
            color |= (color << 16);
#ifdef SDL_SSE_INTRINSICS
            ប្រសិនបើ (SDL_HasSSE()) {
                fill_function = SDL_FillSurfaceRect1SSE;
                bha_nga;
            }
#endif
            fill_function = SDL_FillSurfaceRect1;
            bha_nga;
        }

        pak_sa 2:
        {
            color |= (color << 16);
#ifdef SDL_SSE_INTRINSICS
            ប្រសិនបើ (SDL_HasSSE()) {
                fill_function = SDL_FillSurfaceRect2SSE;
                bha_nga;
            }
#endif
            fill_function = SDL_FillSurfaceRect2;
            bha_nga;
        }

        pak_sa 3:
            // 24-bit RGB is a slow path, at least for now.
            {
                fill_function = SDL_FillSurfaceRect3;
                bha_nga;
            }

        pak_sa 4:
        {
#ifdef SDL_SSE_INTRINSICS
            ប្រសិនបើ (SDL_HasSSE()) {
                fill_function = SDL_FillSurfaceRect4SSE;
                bha_nga;
            }
#endif
#ifdef SDL_LSX_INTRINSICS
            ប្រសិនបើ (SDL_HasLSX()) {
                fill_function = SDL_FillSurfaceRect4LSX;
                bha_nga;
            }
#endif
            fill_function = SDL_FillSurfaceRect4;
            bha_nga;
        }

        default:
            ត្រឡប់ SDL_SetError("Unsupported pixel format");
        }
    }

    សម្រាប់ (i = 0; i < count; ++i) {
        rect = &rects[i];
        // Perform clipping
        ប្រសិនបើ (!SDL_GetRectIntersection(rect, &dst->clip_rect, &clipped)) {
            continue;
        }
        rect = &clipped;

        pixels = (Uint8 *)dst->pixels + rect->y * dst->pitch +
                 rect->x * SDL_BYTESPERPIXEL(dst->format);

        fill_function(pixels, dst->pitch, color, rect->w, rect->h);
    }

    // We're done!
    ត្រឡប់ true;
}
