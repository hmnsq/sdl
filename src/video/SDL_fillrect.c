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
#અન્તર્ભાવ "SDL_internal.h"

#અન્તર્ભાવ "SDL_surface_c.h"

#ifdef SDL_SSE_INTRINSICS
/* *INDENT-OFF* */ // clang-format off

#જો defined(_MSC_VER) && !defined(__clang__)
#define SSE_BEGIN \
    __m128 c128; \
    c128.m128_u32[0] = color; \
    c128.m128_u32[1] = color; \
    c128.m128_u32[2] = color; \
    c128.m128_u32[3] = color
#નહીંતર
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
    માટે (i = n / 64; i--;) { \
        _mm_stream_ps((દશાંશ *)(p+0), c128); \
        _mm_stream_ps((દશાંશ *)(p+16), c128); \
        _mm_stream_ps((દશાંશ *)(p+32), c128); \
        _mm_stream_ps((દશાંશ *)(p+48), c128); \
        p += 64; \
    }

#define SSE_END

#define DEFINE_SSE_FILLRECT(bpp, type) \
સ્થિર શૂન્ય SDL_TARGETING("sse") SDL_FillSurfaceRect##bpp##SSE(Uint8 *pixels, પૂર્ણાંક pitch, Uint32 color, પૂર્ણાંક w, પૂર્ણાંક h) \
{ \
    પૂર્ણાંક i, n; \
    Uint8 *p = ખાલી; \
  \
    /* If the number of bytes per row is equal to the pitch, treat */ \
    /* all rows as one long continuous row (for better performance) */ \
    જો ((w) * (bpp) == pitch) { \
        w = w * h; \
        h = 1; \
    } \
 \
    SSE_BEGIN; \
 \
    જ્યારે (h--) { \
        n = (w) * (bpp); \
        p = pixels; \
 \
        જો (n > 63) { \
            પૂર્ણાંક adjust = 16 - ((uintptr_t)p & 15); \
            જો (adjust < 16) { \
                n -= adjust; \
                adjust /= (bpp); \
                જ્યારે (adjust--) { \
                    *((type *)p) = (type)color; \
                    p += (bpp); \
                } \
            } \
            SSE_WORK; \
        } \
        જો (n & 63) { \
            પૂર્ણાંક remainder = (n & 63); \
            remainder /= (bpp); \
            જ્યારે (remainder--) { \
                *((type *)p) = (type)color; \
                p += (bpp); \
            } \
        } \
        pixels += pitch; \
    } \
 \
    SSE_END; \
}

સ્થિર શૂન્ય SDL_TARGETING("sse") SDL_FillSurfaceRect1SSE(Uint8 *pixels, પૂર્ણાંક pitch, Uint32 color, પૂર્ણાંક w, પૂર્ણાંક h)
{
    પૂર્ણાંક i, n;

    SSE_BEGIN;
    જ્યારે (h--) {
        Uint8 *p = pixels;
        n = w;

        જો (n > 63) {
            પૂર્ણાંક adjust = 16 - ((uintptr_t)p & 15);
            જો (adjust) {
                n -= adjust;
                SDL_memset(p, color, adjust);
                p += adjust;
            }
            SSE_WORK;
        }
        જો (n & 63) {
            પૂર્ણાંક remainder = (n & 63);
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
    માટે (i = n / 64; i--;) { \
        __lsx_vst(c128, p, 0); \
        __lsx_vst(c128, p, 16); \
        __lsx_vst(c128, p, 32); \
        __lsx_vst(c128, p, 48); \
        p += 64; \
    }

#define DEFINE_LSX_FILLRECT(bpp, type) \
સ્થિર શૂન્ય SDL_TARGETING("lsx") SDL_FillSurfaceRect##bpp##LSX(Uint8 *pixels, પૂર્ણાંક pitch, Uint32 color, પૂર્ણાંક w, પૂર્ણાંક h) \
{ \
    પૂર્ણાંક i, n; \
    Uint8 *p = ખાલી; \
  \
    /* If the number of bytes per row is equal to the pitch, treat */ \
    /* all rows as one long continuous row (for better performance) */ \
    જો ((w) * (bpp) == pitch) { \
        w = w * h; \
        h = 1; \
    } \
 \
    LSX_BEGIN; \
 \
    જ્યારે (h--) { \
        n = (w) * (bpp); \
        p = pixels; \
 \
        જો (n > 63) { \
            પૂર્ણાંક adjust = 16 - ((uintptr_t)p & 15); \
            જો (adjust < 16) { \
                n -= adjust; \
                adjust /= (bpp); \
                જ્યારે (adjust--) { \
                    *((type *)p) = (type)color; \
                    p += (bpp); \
                } \
            } \
            LSX_WORK; \
        } \
        જો (n & 63) { \
            પૂર્ણાંક remainder = (n & 63); \
            remainder /= (bpp); \
            જ્યારે (remainder--) { \
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

સ્થિર શૂન્ય SDL_FillSurfaceRect1(Uint8 *pixels, પૂર્ણાંક pitch, Uint32 color, પૂર્ણાંક w, પૂર્ણાંક h)
{
    પૂર્ણાંક n;
    Uint8 *p = ખાલી;

    જ્યારે (h--) {
        n = w;
        p = pixels;

        જો (n > 3) {
            પસંદગી ((uintptr_t)p & 3) {
            સ્થિતિ 1:
                *p++ = (Uint8)color;
                --n;
                SDL_FALLTHROUGH;
            સ્થિતિ 2:
                *p++ = (Uint8)color;
                --n;
                SDL_FALLTHROUGH;
            સ્થિતિ 3:
                *p++ = (Uint8)color;
                --n;
            }
            SDL_memset4(p, color, (n >> 2));
        }
        જો (n & 3) {
            p += (n & ~3);
            પસંદગી (n & 3) {
            સ્થિતિ 3:
                *p++ = (Uint8)color;
                SDL_FALLTHROUGH;
            સ્થિતિ 2:
                *p++ = (Uint8)color;
                SDL_FALLTHROUGH;
            સ્થિતિ 1:
                *p++ = (Uint8)color;
            }
        }
        pixels += pitch;
    }
}

સ્થિર શૂન્ય SDL_FillSurfaceRect2(Uint8 *pixels, પૂર્ણાંક pitch, Uint32 color, પૂર્ણાંક w, પૂર્ણાંક h)
{
    પૂર્ણાંક n;
    Uint16 *p = ખાલી;

    જ્યારે (h--) {
        n = w;
        p = (Uint16 *)pixels;

        જો (n > 1) {
            જો ((uintptr_t)p & 2) {
                *p++ = (Uint16)color;
                --n;
            }
            SDL_memset4(p, color, (n >> 1));
        }
        જો (n & 1) {
            p[n - 1] = (Uint16)color;
        }
        pixels += pitch;
    }
}

સ્થિર શૂન્ય SDL_FillSurfaceRect3(Uint8 *pixels, પૂર્ણાંક pitch, Uint32 color, પૂર્ણાંક w, પૂર્ણાંક h)
{
#જો SDL_BYTEORDER == SDL_LIL_ENDIAN
    Uint8 b1 = (Uint8)(color & 0xFF);
    Uint8 b2 = (Uint8)((color >> 8) & 0xFF);
    Uint8 b3 = (Uint8)((color >> 16) & 0xFF);
#અથવાજો SDL_BYTEORDER == SDL_BIG_ENDIAN
    Uint8 b1 = (Uint8)((color >> 16) & 0xFF);
    Uint8 b2 = (Uint8)((color >> 8) & 0xFF);
    Uint8 b3 = (Uint8)(color & 0xFF);
#endif
    પૂર્ણાંક n;
    Uint8 *p = ખાલી;

    જ્યારે (h--) {
        n = w;
        p = pixels;

        જ્યારે (n--) {
            *p++ = b1;
            *p++ = b2;
            *p++ = b3;
        }
        pixels += pitch;
    }
}

સ્થિર શૂન્ય SDL_FillSurfaceRect4(Uint8 *pixels, પૂર્ણાંક pitch, Uint32 color, પૂર્ણાંક w, પૂર્ણાંક h)
{
    જ્યારે (h--) {
        SDL_memset4(pixels, color, w);
        pixels += pitch;
    }
}

/*
 * This function performs a fast fill of the given rectangle with 'color'
 */
bool SDL_FillSurfaceRect(SDL_Surface *dst, અચલ SDL_Rect *rect, Uint32 color)
{
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        પાછા SDL_InvalidParamError("SDL_FillSurfaceRect(): dst");
    }

    // If 'rect' == NULL, then fill the whole surface
    જો (!rect) {
        rect = &dst->clip_rect;
        // Don't attempt to fill if the surface's clip_rect is empty
        જો (SDL_RectEmpty(rect)) {
            પાછા true;
        }
    }

    પાછા SDL_FillSurfaceRects(dst, rect, 1, color);
}

bool SDL_FillSurfaceRects(SDL_Surface *dst, અચલ SDL_Rect *rects, પૂર્ણાંક ગણતરી, Uint32 color)
{
    SDL_Rect clipped;
    Uint8 *pixels;
    અચલ SDL_Rect *rect;
    શૂન્ય (*fill_function)(Uint8 * pixels, પૂર્ણાંક pitch, Uint32 color, પૂર્ણાંક w, પૂર્ણાંક h) = ખાલી;
    પૂર્ણાંક i;

    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        પાછા SDL_InvalidParamError("SDL_FillSurfaceRects(): dst");
    }

    CHECK_PARAM(!rects) {
        પાછા SDL_InvalidParamError("SDL_FillSurfaceRects(): rects");
    }

    જો (!dst->pixels && SDL_MUSTLOCK(dst)) {
        પાછા SDL_SetError("SDL_FillSurfaceRects(): You must lock the surface");
    }

    // Nothing to do
    જો (dst->w == 0 || dst->h == 0 || !dst->pixels) {
        પાછા true;
    }

    /* This function doesn't usually work on surfaces < 8 bpp
     * Except: support for 4bits, when filling full size.
     */
    જો (SDL_BITSPERPIXEL(dst->format) < 8) {
        જો (ગણતરી == 1) {
            અચલ SDL_Rect *r = &rects[0];
            જો (r->x == 0 && r->y == 0 && r->w == dst->w && r->h == dst->h) {
                જો (SDL_BITSPERPIXEL(dst->format) == 4) {
                    Uint8 b = (((Uint8)color << 4) | (Uint8)color);
                    SDL_memset(dst->pixels, b, (size_t)dst->h * dst->pitch);
                    પાછા true;
                }
            }
        }
        પાછા SDL_SetError("SDL_FillSurfaceRects(): Unsupported surface format");
    }

    જો (fill_function == ખાલી) {
        પસંદગી (SDL_BYTESPERPIXEL(dst->format)) {
        સ્થિતિ 1:
        {
            color |= (color << 8);
            color |= (color << 16);
#ifdef SDL_SSE_INTRINSICS
            જો (SDL_HasSSE()) {
                fill_function = SDL_FillSurfaceRect1SSE;
                તોડો;
            }
#endif
            fill_function = SDL_FillSurfaceRect1;
            તોડો;
        }

        સ્થિતિ 2:
        {
            color |= (color << 16);
#ifdef SDL_SSE_INTRINSICS
            જો (SDL_HasSSE()) {
                fill_function = SDL_FillSurfaceRect2SSE;
                તોડો;
            }
#endif
            fill_function = SDL_FillSurfaceRect2;
            તોડો;
        }

        સ્થિતિ 3:
            // 24-bit RGB is a slow path, at least for now.
            {
                fill_function = SDL_FillSurfaceRect3;
                તોડો;
            }

        સ્થિતિ 4:
        {
#ifdef SDL_SSE_INTRINSICS
            જો (SDL_HasSSE()) {
                fill_function = SDL_FillSurfaceRect4SSE;
                તોડો;
            }
#endif
#ifdef SDL_LSX_INTRINSICS
            જો (SDL_HasLSX()) {
                fill_function = SDL_FillSurfaceRect4LSX;
                તોડો;
            }
#endif
            fill_function = SDL_FillSurfaceRect4;
            તોડો;
        }

        મૂળભૂત:
            પાછા SDL_SetError("Unsupported pixel format");
        }
    }

    માટે (i = 0; i < ગણતરી; ++i) {
        rect = &rects[i];
        // Perform clipping
        જો (!SDL_GetRectIntersection(rect, &dst->clip_rect, &clipped)) {
            ચાલુ;
        }
        rect = &clipped;

        pixels = (Uint8 *)dst->pixels + rect->y * dst->pitch +
                 rect->x * SDL_BYTESPERPIXEL(dst->format);

        fill_function(pixels, dst->pitch, color, rect->w, rect->h);
    }

    // We're done!
    પાછા true;
}
