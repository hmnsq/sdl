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
#অন্তর্ভাব "SDL_internal.h"

#অন্তর্ভাব "SDL_surface_c.h"

#ifdef SDL_SSE_INTRINSICS
/* *INDENT-OFF* */ // clang-format off

#যদি defined(_MSC_VER) && !defined(__clang__)
#define SSE_BEGIN \
    __m128 c128; \
    c128.m128_u32[0] = color; \
    c128.m128_u32[1] = color; \
    c128.m128_u32[2] = color; \
    c128.m128_u32[3] = color
#অন্যথা
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
    প্রতি (i = n / 64; i--;) { \
        _mm_stream_ps((ভিন্ন *)(p+0), c128); \
        _mm_stream_ps((ভিন্ন *)(p+16), c128); \
        _mm_stream_ps((ভিন্ন *)(p+32), c128); \
        _mm_stream_ps((ভিন্ন *)(p+48), c128); \
        p += 64; \
    }

#define SSE_END

#define DEFINE_SSE_FILLRECT(bpp, type) \
স্থির শূন্য SDL_TARGETING("sse") SDL_FillSurfaceRect##bpp##SSE(Uint8 *pixels, পূর্ণাঙ্ক pitch, Uint32 color, পূর্ণাঙ্ক w, পূর্ণাঙ্ক h) \
{ \
    পূর্ণাঙ্ক i, n; \
    Uint8 *p = রিক্ত; \
  \
    /* If the number of bytes per row is equal to the pitch, treat */ \
    /* all rows as one long continuous row (for better performance) */ \
    যদি ((w) * (bpp) == pitch) { \
        w = w * h; \
        h = 1; \
    } \
 \
    SSE_BEGIN; \
 \
    যাবত্ (h--) { \
        n = (w) * (bpp); \
        p = pixels; \
 \
        যদি (n > 63) { \
            পূর্ণাঙ্ক adjust = 16 - ((uintptr_t)p & 15); \
            যদি (adjust < 16) { \
                n -= adjust; \
                adjust /= (bpp); \
                যাবত্ (adjust--) { \
                    *((type *)p) = (type)color; \
                    p += (bpp); \
                } \
            } \
            SSE_WORK; \
        } \
        যদি (n & 63) { \
            পূর্ণাঙ্ক remainder = (n & 63); \
            remainder /= (bpp); \
            যাবত্ (remainder--) { \
                *((type *)p) = (type)color; \
                p += (bpp); \
            } \
        } \
        pixels += pitch; \
    } \
 \
    SSE_END; \
}

স্থির শূন্য SDL_TARGETING("sse") SDL_FillSurfaceRect1SSE(Uint8 *pixels, পূর্ণাঙ্ক pitch, Uint32 color, পূর্ণাঙ্ক w, পূর্ণাঙ্ক h)
{
    পূর্ণাঙ্ক i, n;

    SSE_BEGIN;
    যাবত্ (h--) {
        Uint8 *p = pixels;
        n = w;

        যদি (n > 63) {
            পূর্ণাঙ্ক adjust = 16 - ((uintptr_t)p & 15);
            যদি (adjust) {
                n -= adjust;
                SDL_memset(p, color, adjust);
                p += adjust;
            }
            SSE_WORK;
        }
        যদি (n & 63) {
            পূর্ণাঙ্ক remainder = (n & 63);
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
    প্রতি (i = n / 64; i--;) { \
        __lsx_vst(c128, p, 0); \
        __lsx_vst(c128, p, 16); \
        __lsx_vst(c128, p, 32); \
        __lsx_vst(c128, p, 48); \
        p += 64; \
    }

#define DEFINE_LSX_FILLRECT(bpp, type) \
স্থির শূন্য SDL_TARGETING("lsx") SDL_FillSurfaceRect##bpp##LSX(Uint8 *pixels, পূর্ণাঙ্ক pitch, Uint32 color, পূর্ণাঙ্ক w, পূর্ণাঙ্ক h) \
{ \
    পূর্ণাঙ্ক i, n; \
    Uint8 *p = রিক্ত; \
  \
    /* If the number of bytes per row is equal to the pitch, treat */ \
    /* all rows as one long continuous row (for better performance) */ \
    যদি ((w) * (bpp) == pitch) { \
        w = w * h; \
        h = 1; \
    } \
 \
    LSX_BEGIN; \
 \
    যাবত্ (h--) { \
        n = (w) * (bpp); \
        p = pixels; \
 \
        যদি (n > 63) { \
            পূর্ণাঙ্ক adjust = 16 - ((uintptr_t)p & 15); \
            যদি (adjust < 16) { \
                n -= adjust; \
                adjust /= (bpp); \
                যাবত্ (adjust--) { \
                    *((type *)p) = (type)color; \
                    p += (bpp); \
                } \
            } \
            LSX_WORK; \
        } \
        যদি (n & 63) { \
            পূর্ণাঙ্ক remainder = (n & 63); \
            remainder /= (bpp); \
            যাবত্ (remainder--) { \
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

স্থির শূন্য SDL_FillSurfaceRect1(Uint8 *pixels, পূর্ণাঙ্ক pitch, Uint32 color, পূর্ণাঙ্ক w, পূর্ণাঙ্ক h)
{
    পূর্ণাঙ্ক n;
    Uint8 *p = রিক্ত;

    যাবত্ (h--) {
        n = w;
        p = pixels;

        যদি (n > 3) {
            বিকল্প ((uintptr_t)p & 3) {
            পক্ষ 1:
                *p++ = (Uint8)color;
                --n;
                SDL_FALLTHROUGH;
            পক্ষ 2:
                *p++ = (Uint8)color;
                --n;
                SDL_FALLTHROUGH;
            পক্ষ 3:
                *p++ = (Uint8)color;
                --n;
            }
            SDL_memset4(p, color, (n >> 2));
        }
        যদি (n & 3) {
            p += (n & ~3);
            বিকল্প (n & 3) {
            পক্ষ 3:
                *p++ = (Uint8)color;
                SDL_FALLTHROUGH;
            পক্ষ 2:
                *p++ = (Uint8)color;
                SDL_FALLTHROUGH;
            পক্ষ 1:
                *p++ = (Uint8)color;
            }
        }
        pixels += pitch;
    }
}

স্থির শূন্য SDL_FillSurfaceRect2(Uint8 *pixels, পূর্ণাঙ্ক pitch, Uint32 color, পূর্ণাঙ্ক w, পূর্ণাঙ্ক h)
{
    পূর্ণাঙ্ক n;
    Uint16 *p = রিক্ত;

    যাবত্ (h--) {
        n = w;
        p = (Uint16 *)pixels;

        যদি (n > 1) {
            যদি ((uintptr_t)p & 2) {
                *p++ = (Uint16)color;
                --n;
            }
            SDL_memset4(p, color, (n >> 1));
        }
        যদি (n & 1) {
            p[n - 1] = (Uint16)color;
        }
        pixels += pitch;
    }
}

স্থির শূন্য SDL_FillSurfaceRect3(Uint8 *pixels, পূর্ণাঙ্ক pitch, Uint32 color, পূর্ণাঙ্ক w, পূর্ণাঙ্ক h)
{
#যদি SDL_BYTEORDER == SDL_LIL_ENDIAN
    Uint8 b1 = (Uint8)(color & 0xFF);
    Uint8 b2 = (Uint8)((color >> 8) & 0xFF);
    Uint8 b3 = (Uint8)((color >> 16) & 0xFF);
#নোচেদ্যদি SDL_BYTEORDER == SDL_BIG_ENDIAN
    Uint8 b1 = (Uint8)((color >> 16) & 0xFF);
    Uint8 b2 = (Uint8)((color >> 8) & 0xFF);
    Uint8 b3 = (Uint8)(color & 0xFF);
#endif
    পূর্ণাঙ্ক n;
    Uint8 *p = রিক্ত;

    যাবত্ (h--) {
        n = w;
        p = pixels;

        যাবত্ (n--) {
            *p++ = b1;
            *p++ = b2;
            *p++ = b3;
        }
        pixels += pitch;
    }
}

স্থির শূন্য SDL_FillSurfaceRect4(Uint8 *pixels, পূর্ণাঙ্ক pitch, Uint32 color, পূর্ণাঙ্ক w, পূর্ণাঙ্ক h)
{
    যাবত্ (h--) {
        SDL_memset4(pixels, color, w);
        pixels += pitch;
    }
}

/*
 * This function performs a fast fill of the given rectangle with 'color'
 */
bool SDL_FillSurfaceRect(SDL_Surface *dst, ধ্রুব SDL_Rect *rect, Uint32 color)
{
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        প্রত্যাগম SDL_InvalidParamError("SDL_FillSurfaceRect(): dst");
    }

    // If 'rect' == NULL, then fill the whole surface
    যদি (!rect) {
        rect = &dst->clip_rect;
        // Don't attempt to fill if the surface's clip_rect is empty
        যদি (SDL_RectEmpty(rect)) {
            প্রত্যাগম true;
        }
    }

    প্রত্যাগম SDL_FillSurfaceRects(dst, rect, 1, color);
}

bool SDL_FillSurfaceRects(SDL_Surface *dst, ধ্রুব SDL_Rect *rects, পূর্ণাঙ্ক গুনতি, Uint32 color)
{
    SDL_Rect clipped;
    Uint8 *pixels;
    ধ্রুব SDL_Rect *rect;
    শূন্য (*fill_function)(Uint8 * pixels, পূর্ণাঙ্ক pitch, Uint32 color, পূর্ণাঙ্ক w, পূর্ণাঙ্ক h) = রিক্ত;
    পূর্ণাঙ্ক i;

    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        প্রত্যাগম SDL_InvalidParamError("SDL_FillSurfaceRects(): dst");
    }

    CHECK_PARAM(!rects) {
        প্রত্যাগম SDL_InvalidParamError("SDL_FillSurfaceRects(): rects");
    }

    যদি (!dst->pixels && SDL_MUSTLOCK(dst)) {
        প্রত্যাগম SDL_SetError("SDL_FillSurfaceRects(): You must lock the surface");
    }

    // Nothing to do
    যদি (dst->w == 0 || dst->h == 0 || !dst->pixels) {
        প্রত্যাগম true;
    }

    /* This function doesn't usually work on surfaces < 8 bpp
     * Except: support for 4bits, when filling full size.
     */
    যদি (SDL_BITSPERPIXEL(dst->format) < 8) {
        যদি (গুনতি == 1) {
            ধ্রুব SDL_Rect *r = &rects[0];
            যদি (r->x == 0 && r->y == 0 && r->w == dst->w && r->h == dst->h) {
                যদি (SDL_BITSPERPIXEL(dst->format) == 4) {
                    Uint8 b = (((Uint8)color << 4) | (Uint8)color);
                    SDL_memset(dst->pixels, b, (size_t)dst->h * dst->pitch);
                    প্রত্যাগম true;
                }
            }
        }
        প্রত্যাগম SDL_SetError("SDL_FillSurfaceRects(): Unsupported surface format");
    }

    যদি (fill_function == রিক্ত) {
        বিকল্প (SDL_BYTESPERPIXEL(dst->format)) {
        পক্ষ 1:
        {
            color |= (color << 8);
            color |= (color << 16);
#ifdef SDL_SSE_INTRINSICS
            যদি (SDL_HasSSE()) {
                fill_function = SDL_FillSurfaceRect1SSE;
                ভঙ্গ;
            }
#endif
            fill_function = SDL_FillSurfaceRect1;
            ভঙ্গ;
        }

        পক্ষ 2:
        {
            color |= (color << 16);
#ifdef SDL_SSE_INTRINSICS
            যদি (SDL_HasSSE()) {
                fill_function = SDL_FillSurfaceRect2SSE;
                ভঙ্গ;
            }
#endif
            fill_function = SDL_FillSurfaceRect2;
            ভঙ্গ;
        }

        পক্ষ 3:
            // 24-bit RGB is a slow path, at least for now.
            {
                fill_function = SDL_FillSurfaceRect3;
                ভঙ্গ;
            }

        পক্ষ 4:
        {
#ifdef SDL_SSE_INTRINSICS
            যদি (SDL_HasSSE()) {
                fill_function = SDL_FillSurfaceRect4SSE;
                ভঙ্গ;
            }
#endif
#ifdef SDL_LSX_INTRINSICS
            যদি (SDL_HasLSX()) {
                fill_function = SDL_FillSurfaceRect4LSX;
                ভঙ্গ;
            }
#endif
            fill_function = SDL_FillSurfaceRect4;
            ভঙ্গ;
        }

        স্বভাব:
            প্রত্যাগম SDL_SetError("Unsupported pixel format");
        }
    }

    প্রতি (i = 0; i < গুনতি; ++i) {
        rect = &rects[i];
        // Perform clipping
        যদি (!SDL_GetRectIntersection(rect, &dst->clip_rect, &clipped)) {
            অনুবর্ত;
        }
        rect = &clipped;

        pixels = (Uint8 *)dst->pixels + rect->y * dst->pitch +
                 rect->x * SDL_BYTESPERPIXEL(dst->format);

        fill_function(pixels, dst->pitch, color, rect->w, rect->h);
    }

    // We're done!
    প্রত্যাগম true;
}
