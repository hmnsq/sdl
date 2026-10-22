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

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_surface_c.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_SSE_INTRINSICS
/* *INDENT-OFF* */ // clang-format off

#ਜੇ defined(_MSC_VER) && !defined(__clang__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SSE_BEGIN \
    __m128 c128; \
    c128.m128_u32[0] = color; \
    c128.m128_u32[1] = color; \
    c128.m128_u32[2] = color; \
    c128.m128_u32[3] = color
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SSE_BEGIN \
    __m128 c128; \
    DECLARE_ALIGNED(Uint32, cccc[4], 16); \
    cccc[0] = color; \
    cccc[1] = color; \
    cccc[2] = color; \
    cccc[3] = color; \
    c128 = *(__m128 *)cccc
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SSE_WORK \
    ਲਈ (i = n / 64; i--;) { \
        mm_ਧਾਰਾ_ps((ਦਸ਼ਮਲਵ *)(p+0), c128); \
        mm_ਧਾਰਾ_ps((ਦਸ਼ਮਲਵ *)(p+16), c128); \
        mm_ਧਾਰਾ_ps((ਦਸ਼ਮਲਵ *)(p+32), c128); \
        mm_ਧਾਰਾ_ps((ਦਸ਼ਮਲਵ *)(p+48), c128); \
        p += 64; \
    }

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SSE_ਸਿਰਾ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFINE_SSE_FILLRECT(bpp, type) \
ਸਥਿਰ ਖਾਲੀ SDL_TARGETING("sse") SDL_FillSurfaceRect##bpp##SSE(Uint8 *pixels, ਪੂਰਨ pitch, Uint32 color, ਪੂਰਨ w, ਪੂਰਨ h) \
{ \
    ਪੂਰਨ i, n; \
    Uint8 *p = ਨਿਰਾ; \
  \
    /* If the number of bytes per row is equal to the pitch, treat */ \
    /* all rows as one long continuous row (for better performance) */ \
    ਜੇ ((w) * (bpp) == pitch) { \
        w = w * h; \
        h = 1; \
    } \
 \
    SSE_BEGIN; \
 \
    ਜਦੋਂ (h--) { \
        n = (w) * (bpp); \
        p = pixels; \
 \
        ਜੇ (n > 63) { \
            ਪੂਰਨ adjust = 16 - ((uintptr_t)p & 15); \
            ਜੇ (adjust < 16) { \
                n -= adjust; \
                adjust /= (bpp); \
                ਜਦੋਂ (adjust--) { \
                    *((type *)p) = (type)color; \
                    p += (bpp); \
                } \
            } \
            SSE_WORK; \
        } \
        ਜੇ (n & 63) { \
            ਪੂਰਨ remainder = (n & 63); \
            remainder /= (bpp); \
            ਜਦੋਂ (remainder--) { \
                *((type *)p) = (type)color; \
                p += (bpp); \
            } \
        } \
        pixels += pitch; \
    } \
 \
    SSE_ਸਿਰਾ; \
}

ਸਥਿਰ ਖਾਲੀ SDL_TARGETING("sse") SDL_FillSurfaceRect1SSE(Uint8 *pixels, ਪੂਰਨ pitch, Uint32 color, ਪੂਰਨ w, ਪੂਰਨ h)
{
    ਪੂਰਨ i, n;

    SSE_BEGIN;
    ਜਦੋਂ (h--) {
        Uint8 *p = pixels;
        n = w;

        ਜੇ (n > 63) {
            ਪੂਰਨ adjust = 16 - ((uintptr_t)p & 15);
            ਜੇ (adjust) {
                n -= adjust;
                SDL_memset(p, color, adjust);
                p += adjust;
            }
            SSE_WORK;
        }
        ਜੇ (n & 63) {
            ਪੂਰਨ remainder = (n & 63);
            SDL_memset(p, color, remainder);
        }
        pixels += pitch;
    }

    SSE_ਸਿਰਾ;
}
// DEFINE_SSE_FILLRECT(1, Uint8)
DEFINE_SSE_FILLRECT(2, Uint16)
DEFINE_SSE_FILLRECT(4, Uint32)

/* *INDENT-ON* */ // clang-format on
#ਜੇ_ਅੰਤ            // SDL_SSE_INTRINSICS

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_LSX_INTRINSICS
/* *INDENT-OFF* */ // clang-format off

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LSX_BEGIN __m128i c128 = __lsx_vreplgr2vr_w(color);

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LSX_WORK \
    ਲਈ (i = n / 64; i--;) { \
        __lsx_vst(c128, p, 0); \
        __lsx_vst(c128, p, 16); \
        __lsx_vst(c128, p, 32); \
        __lsx_vst(c128, p, 48); \
        p += 64; \
    }

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFINE_LSX_FILLRECT(bpp, type) \
ਸਥਿਰ ਖਾਲੀ SDL_TARGETING("lsx") SDL_FillSurfaceRect##bpp##LSX(Uint8 *pixels, ਪੂਰਨ pitch, Uint32 color, ਪੂਰਨ w, ਪੂਰਨ h) \
{ \
    ਪੂਰਨ i, n; \
    Uint8 *p = ਨਿਰਾ; \
  \
    /* If the number of bytes per row is equal to the pitch, treat */ \
    /* all rows as one long continuous row (for better performance) */ \
    ਜੇ ((w) * (bpp) == pitch) { \
        w = w * h; \
        h = 1; \
    } \
 \
    LSX_BEGIN; \
 \
    ਜਦੋਂ (h--) { \
        n = (w) * (bpp); \
        p = pixels; \
 \
        ਜੇ (n > 63) { \
            ਪੂਰਨ adjust = 16 - ((uintptr_t)p & 15); \
            ਜੇ (adjust < 16) { \
                n -= adjust; \
                adjust /= (bpp); \
                ਜਦੋਂ (adjust--) { \
                    *((type *)p) = (type)color; \
                    p += (bpp); \
                } \
            } \
            LSX_WORK; \
        } \
        ਜੇ (n & 63) { \
            ਪੂਰਨ remainder = (n & 63); \
            remainder /= (bpp); \
            ਜਦੋਂ (remainder--) { \
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
#ਜੇ_ਅੰਤ // SDL_LSX_INTRINSICS

ਸਥਿਰ ਖਾਲੀ SDL_FillSurfaceRect1(Uint8 *pixels, ਪੂਰਨ pitch, Uint32 color, ਪੂਰਨ w, ਪੂਰਨ h)
{
    ਪੂਰਨ n;
    Uint8 *p = ਨਿਰਾ;

    ਜਦੋਂ (h--) {
        n = w;
        p = pixels;

        ਜੇ (n > 3) {
            ਚੋਣ ((uintptr_t)p & 3) {
            ਹਾਲਤ 1:
                *p++ = (Uint8)color;
                --n;
                SDL_FALLTHROUGH;
            ਹਾਲਤ 2:
                *p++ = (Uint8)color;
                --n;
                SDL_FALLTHROUGH;
            ਹਾਲਤ 3:
                *p++ = (Uint8)color;
                --n;
            }
            SDL_memset4(p, color, (n >> 2));
        }
        ਜੇ (n & 3) {
            p += (n & ~3);
            ਚੋਣ (n & 3) {
            ਹਾਲਤ 3:
                *p++ = (Uint8)color;
                SDL_FALLTHROUGH;
            ਹਾਲਤ 2:
                *p++ = (Uint8)color;
                SDL_FALLTHROUGH;
            ਹਾਲਤ 1:
                *p++ = (Uint8)color;
            }
        }
        pixels += pitch;
    }
}

ਸਥਿਰ ਖਾਲੀ SDL_FillSurfaceRect2(Uint8 *pixels, ਪੂਰਨ pitch, Uint32 color, ਪੂਰਨ w, ਪੂਰਨ h)
{
    ਪੂਰਨ n;
    Uint16 *p = ਨਿਰਾ;

    ਜਦੋਂ (h--) {
        n = w;
        p = (Uint16 *)pixels;

        ਜੇ (n > 1) {
            ਜੇ ((uintptr_t)p & 2) {
                *p++ = (Uint16)color;
                --n;
            }
            SDL_memset4(p, color, (n >> 1));
        }
        ਜੇ (n & 1) {
            p[n - 1] = (Uint16)color;
        }
        pixels += pitch;
    }
}

ਸਥਿਰ ਖਾਲੀ SDL_FillSurfaceRect3(Uint8 *pixels, ਪੂਰਨ pitch, Uint32 color, ਪੂਰਨ w, ਪੂਰਨ h)
{
#ਜੇ SDL_BYTEORDER == SDL_LIL_ENDIAN
    Uint8 b1 = (Uint8)(color & 0xFF);
    Uint8 b2 = (Uint8)((color >> 8) & 0xFF);
    Uint8 b3 = (Uint8)((color >> 16) & 0xFF);
#ਜਾਂਜੇ SDL_BYTEORDER == SDL_BIG_ENDIAN
    Uint8 b1 = (Uint8)((color >> 16) & 0xFF);
    Uint8 b2 = (Uint8)((color >> 8) & 0xFF);
    Uint8 b3 = (Uint8)(color & 0xFF);
#ਜੇ_ਅੰਤ
    ਪੂਰਨ n;
    Uint8 *p = ਨਿਰਾ;

    ਜਦੋਂ (h--) {
        n = w;
        p = pixels;

        ਜਦੋਂ (n--) {
            *p++ = b1;
            *p++ = b2;
            *p++ = b3;
        }
        pixels += pitch;
    }
}

ਸਥਿਰ ਖਾਲੀ SDL_FillSurfaceRect4(Uint8 *pixels, ਪੂਰਨ pitch, Uint32 color, ਪੂਰਨ w, ਪੂਰਨ h)
{
    ਜਦੋਂ (h--) {
        SDL_memset4(pixels, color, w);
        pixels += pitch;
    }
}

/*
 * This function performs a fast fill of the given rectangle with 'color'
 */
bool SDL_FillSurfaceRect(SDL_Surface *dst, ਅਚਲ SDL_Rect *rect, Uint32 color)
{
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        ਵਾਪਸ SDL_InvalidParamError("SDL_FillSurfaceRect(): dst");
    }

    // If 'rect' == NULL, then fill the whole surface
    ਜੇ (!rect) {
        rect = &dst->clip_rect;
        // Don't attempt to fill if the surface's clip_rect is empty
        ਜੇ (SDL_Rect_ਖਾਲੀ_ਥਾਵਾਂ(rect)) {
            ਵਾਪਸ true;
        }
    }

    ਵਾਪਸ SDL_FillSurfaceRects(dst, rect, 1, color);
}

bool SDL_FillSurfaceRects(SDL_Surface *dst, ਅਚਲ SDL_Rect *rects, ਪੂਰਨ ਗਿਣਤੀ_2, Uint32 color)
{
    SDL_Rect clipped;
    Uint8 *pixels;
    ਅਚਲ SDL_Rect *rect;
    ਖਾਲੀ (*fill_function)(Uint8 * pixels, ਪੂਰਨ pitch, Uint32 color, ਪੂਰਨ w, ਪੂਰਨ h) = ਨਿਰਾ;
    ਪੂਰਨ i;

    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        ਵਾਪਸ SDL_InvalidParamError("SDL_FillSurfaceRects(): dst");
    }

    CHECK_PARAM(!rects) {
        ਵਾਪਸ SDL_InvalidParamError("SDL_FillSurfaceRects(): rects");
    }

    ਜੇ (!dst->pixels && SDL_MUSTLOCK(dst)) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("SDL_FillSurfaceRects(): You must lock the surface");
    }

    // Nothing to do
    ਜੇ (dst->w == 0 || dst->h == 0 || !dst->pixels) {
        ਵਾਪਸ true;
    }

    /* This function doesn't usually work on surfaces < 8 bpp
     * Except: support for 4bits, when filling full size.
     */
    ਜੇ (SDL_BITSPERPIXEL(dst->format) < 8) {
        ਜੇ (ਗਿਣਤੀ_2 == 1) {
            ਅਚਲ SDL_Rect *r = &rects[0];
            ਜੇ (r->x == 0 && r->y == 0 && r->w == dst->w && r->h == dst->h) {
                ਜੇ (SDL_BITSPERPIXEL(dst->format) == 4) {
                    Uint8 b = (((Uint8)color << 4) | (Uint8)color);
                    SDL_memset(dst->pixels, b, (size_t)dst->h * dst->pitch);
                    ਵਾਪਸ true;
                }
            }
        }
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("SDL_FillSurfaceRects(): Unsupported surface format");
    }

    ਜੇ (fill_function == ਨਿਰਾ) {
        ਚੋਣ (SDL_BYTESPERPIXEL(dst->format)) {
        ਹਾਲਤ 1:
        {
            color |= (color << 8);
            color |= (color << 16);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_SSE_INTRINSICS
            ਜੇ (SDL_HasSSE()) {
                fill_function = SDL_FillSurfaceRect1SSE;
                ਰੋਕੋ;
            }
#ਜੇ_ਅੰਤ
            fill_function = SDL_FillSurfaceRect1;
            ਰੋਕੋ;
        }

        ਹਾਲਤ 2:
        {
            color |= (color << 16);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_SSE_INTRINSICS
            ਜੇ (SDL_HasSSE()) {
                fill_function = SDL_FillSurfaceRect2SSE;
                ਰੋਕੋ;
            }
#ਜੇ_ਅੰਤ
            fill_function = SDL_FillSurfaceRect2;
            ਰੋਕੋ;
        }

        ਹਾਲਤ 3:
            // 24-bit RGB is a slow path, at least for now.
            {
                fill_function = SDL_FillSurfaceRect3;
                ਰੋਕੋ;
            }

        ਹਾਲਤ 4:
        {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_SSE_INTRINSICS
            ਜੇ (SDL_HasSSE()) {
                fill_function = SDL_FillSurfaceRect4SSE;
                ਰੋਕੋ;
            }
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_LSX_INTRINSICS
            ਜੇ (SDL_HasLSX()) {
                fill_function = SDL_FillSurfaceRect4LSX;
                ਰੋਕੋ;
            }
#ਜੇ_ਅੰਤ
            fill_function = SDL_FillSurfaceRect4;
            ਰੋਕੋ;
        }

        ਮੂਲ:
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("Unsupported pixel format");
        }
    }

    ਲਈ (i = 0; i < ਗਿਣਤੀ_2; ++i) {
        rect = &rects[i];
        // Perform clipping
        ਜੇ (!SDL_GetRectIntersection(rect, &dst->clip_rect, &clipped)) {
            ਜਾਰੀ;
        }
        rect = &clipped;

        pixels = (Uint8 *)dst->pixels + rect->y * dst->pitch +
                 rect->x * SDL_BYTESPERPIXEL(dst->format);

        fill_function(pixels, dst->pitch, color, rect->w, rect->h);
    }

    // We're done!
    ਵਾਪਸ true;
}
