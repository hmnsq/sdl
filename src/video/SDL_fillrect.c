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
#अन्तर्भाव "SDL_internal.h"

#अन्तर्भाव "SDL_surface_c.h"

#ifdef SDL_SSE_INTRINSICS
/* *INDENT-OFF* */ // clang-format off

#यदि defined(_MSC_VER) && !defined(__clang__)
#define SSE_BEGIN \
    __m128 c128; \
    c128.m128_u32[0] = color; \
    c128.m128_u32[1] = color; \
    c128.m128_u32[2] = color; \
    c128.m128_u32[3] = color
#अन्यथा
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
    प्रति (i = n / 64; i--;) { \
        _mm_stream_ps((भिन्न *)(p+0), c128); \
        _mm_stream_ps((भिन्न *)(p+16), c128); \
        _mm_stream_ps((भिन्न *)(p+32), c128); \
        _mm_stream_ps((भिन्न *)(p+48), c128); \
        p += 64; \
    }

#define SSE_END

#define DEFINE_SSE_FILLRECT(bpp, type) \
स्थिर शून्य SDL_TARGETING("sse") SDL_FillSurfaceRect##bpp##SSE(Uint8 *pixels, पूर्णाङ्क pitch, Uint32 color, पूर्णाङ्क w, पूर्णाङ्क h) \
{ \
    पूर्णाङ्क i, n; \
    Uint8 *p = रिक्त; \
  \
    /* If the number of bytes per row is equal to the pitch, treat */ \
    /* all rows as one long continuous row (for better performance) */ \
    यदि ((w) * (bpp) == pitch) { \
        w = w * h; \
        h = 1; \
    } \
 \
    SSE_BEGIN; \
 \
    यावत् (h--) { \
        n = (w) * (bpp); \
        p = pixels; \
 \
        यदि (n > 63) { \
            पूर्णाङ्क adjust = 16 - ((uintptr_t)p & 15); \
            यदि (adjust < 16) { \
                n -= adjust; \
                adjust /= (bpp); \
                यावत् (adjust--) { \
                    *((type *)p) = (type)color; \
                    p += (bpp); \
                } \
            } \
            SSE_WORK; \
        } \
        यदि (n & 63) { \
            पूर्णाङ्क remainder = (n & 63); \
            remainder /= (bpp); \
            यावत् (remainder--) { \
                *((type *)p) = (type)color; \
                p += (bpp); \
            } \
        } \
        pixels += pitch; \
    } \
 \
    SSE_END; \
}

स्थिर शून्य SDL_TARGETING("sse") SDL_FillSurfaceRect1SSE(Uint8 *pixels, पूर्णाङ्क pitch, Uint32 color, पूर्णाङ्क w, पूर्णाङ्क h)
{
    पूर्णाङ्क i, n;

    SSE_BEGIN;
    यावत् (h--) {
        Uint8 *p = pixels;
        n = w;

        यदि (n > 63) {
            पूर्णाङ्क adjust = 16 - ((uintptr_t)p & 15);
            यदि (adjust) {
                n -= adjust;
                SDL_memset(p, color, adjust);
                p += adjust;
            }
            SSE_WORK;
        }
        यदि (n & 63) {
            पूर्णाङ्क remainder = (n & 63);
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
    प्रति (i = n / 64; i--;) { \
        __lsx_vst(c128, p, 0); \
        __lsx_vst(c128, p, 16); \
        __lsx_vst(c128, p, 32); \
        __lsx_vst(c128, p, 48); \
        p += 64; \
    }

#define DEFINE_LSX_FILLRECT(bpp, type) \
स्थिर शून्य SDL_TARGETING("lsx") SDL_FillSurfaceRect##bpp##LSX(Uint8 *pixels, पूर्णाङ्क pitch, Uint32 color, पूर्णाङ्क w, पूर्णाङ्क h) \
{ \
    पूर्णाङ्क i, n; \
    Uint8 *p = रिक्त; \
  \
    /* If the number of bytes per row is equal to the pitch, treat */ \
    /* all rows as one long continuous row (for better performance) */ \
    यदि ((w) * (bpp) == pitch) { \
        w = w * h; \
        h = 1; \
    } \
 \
    LSX_BEGIN; \
 \
    यावत् (h--) { \
        n = (w) * (bpp); \
        p = pixels; \
 \
        यदि (n > 63) { \
            पूर्णाङ्क adjust = 16 - ((uintptr_t)p & 15); \
            यदि (adjust < 16) { \
                n -= adjust; \
                adjust /= (bpp); \
                यावत् (adjust--) { \
                    *((type *)p) = (type)color; \
                    p += (bpp); \
                } \
            } \
            LSX_WORK; \
        } \
        यदि (n & 63) { \
            पूर्णाङ्क remainder = (n & 63); \
            remainder /= (bpp); \
            यावत् (remainder--) { \
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

स्थिर शून्य SDL_FillSurfaceRect1(Uint8 *pixels, पूर्णाङ्क pitch, Uint32 color, पूर्णाङ्क w, पूर्णाङ्क h)
{
    पूर्णाङ्क n;
    Uint8 *p = रिक्त;

    यावत् (h--) {
        n = w;
        p = pixels;

        यदि (n > 3) {
            विकल्प ((uintptr_t)p & 3) {
            पक्ष 1:
                *p++ = (Uint8)color;
                --n;
                SDL_FALLTHROUGH;
            पक्ष 2:
                *p++ = (Uint8)color;
                --n;
                SDL_FALLTHROUGH;
            पक्ष 3:
                *p++ = (Uint8)color;
                --n;
            }
            SDL_memset4(p, color, (n >> 2));
        }
        यदि (n & 3) {
            p += (n & ~3);
            विकल्प (n & 3) {
            पक्ष 3:
                *p++ = (Uint8)color;
                SDL_FALLTHROUGH;
            पक्ष 2:
                *p++ = (Uint8)color;
                SDL_FALLTHROUGH;
            पक्ष 1:
                *p++ = (Uint8)color;
            }
        }
        pixels += pitch;
    }
}

स्थिर शून्य SDL_FillSurfaceRect2(Uint8 *pixels, पूर्णाङ्क pitch, Uint32 color, पूर्णाङ्क w, पूर्णाङ्क h)
{
    पूर्णाङ्क n;
    Uint16 *p = रिक्त;

    यावत् (h--) {
        n = w;
        p = (Uint16 *)pixels;

        यदि (n > 1) {
            यदि ((uintptr_t)p & 2) {
                *p++ = (Uint16)color;
                --n;
            }
            SDL_memset4(p, color, (n >> 1));
        }
        यदि (n & 1) {
            p[n - 1] = (Uint16)color;
        }
        pixels += pitch;
    }
}

स्थिर शून्य SDL_FillSurfaceRect3(Uint8 *pixels, पूर्णाङ्क pitch, Uint32 color, पूर्णाङ्क w, पूर्णाङ्क h)
{
#यदि SDL_BYTEORDER == SDL_LIL_ENDIAN
    Uint8 b1 = (Uint8)(color & 0xFF);
    Uint8 b2 = (Uint8)((color >> 8) & 0xFF);
    Uint8 b3 = (Uint8)((color >> 16) & 0xFF);
#नोचेद्यदि SDL_BYTEORDER == SDL_BIG_ENDIAN
    Uint8 b1 = (Uint8)((color >> 16) & 0xFF);
    Uint8 b2 = (Uint8)((color >> 8) & 0xFF);
    Uint8 b3 = (Uint8)(color & 0xFF);
#endif
    पूर्णाङ्क n;
    Uint8 *p = रिक्त;

    यावत् (h--) {
        n = w;
        p = pixels;

        यावत् (n--) {
            *p++ = b1;
            *p++ = b2;
            *p++ = b3;
        }
        pixels += pitch;
    }
}

स्थिर शून्य SDL_FillSurfaceRect4(Uint8 *pixels, पूर्णाङ्क pitch, Uint32 color, पूर्णाङ्क w, पूर्णाङ्क h)
{
    यावत् (h--) {
        SDL_memset4(pixels, color, w);
        pixels += pitch;
    }
}

/*
 * This function performs a fast fill of the given rectangle with 'color'
 */
bool SDL_FillSurfaceRect(SDL_Surface *dst, ध्रुव SDL_Rect *rect, Uint32 color)
{
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        प्रत्यागम SDL_InvalidParamError("SDL_FillSurfaceRect(): dst");
    }

    // If 'rect' == NULL, then fill the whole surface
    यदि (!rect) {
        rect = &dst->clip_rect;
        // Don't attempt to fill if the surface's clip_rect is empty
        यदि (SDL_RectEmpty(rect)) {
            प्रत्यागम true;
        }
    }

    प्रत्यागम SDL_FillSurfaceRects(dst, rect, 1, color);
}

bool SDL_FillSurfaceRects(SDL_Surface *dst, ध्रुव SDL_Rect *rects, पूर्णाङ्क गिनती, Uint32 color)
{
    SDL_Rect clipped;
    Uint8 *pixels;
    ध्रुव SDL_Rect *rect;
    शून्य (*fill_function)(Uint8 * pixels, पूर्णाङ्क pitch, Uint32 color, पूर्णाङ्क w, पूर्णाङ्क h) = रिक्त;
    पूर्णाङ्क i;

    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        प्रत्यागम SDL_InvalidParamError("SDL_FillSurfaceRects(): dst");
    }

    CHECK_PARAM(!rects) {
        प्रत्यागम SDL_InvalidParamError("SDL_FillSurfaceRects(): rects");
    }

    यदि (!dst->pixels && SDL_MUSTLOCK(dst)) {
        प्रत्यागम SDL_SetError("SDL_FillSurfaceRects(): You must lock the surface");
    }

    // Nothing to do
    यदि (dst->w == 0 || dst->h == 0 || !dst->pixels) {
        प्रत्यागम true;
    }

    /* This function doesn't usually work on surfaces < 8 bpp
     * Except: support for 4bits, when filling full size.
     */
    यदि (SDL_BITSPERPIXEL(dst->format) < 8) {
        यदि (गिनती == 1) {
            ध्रुव SDL_Rect *r = &rects[0];
            यदि (r->x == 0 && r->y == 0 && r->w == dst->w && r->h == dst->h) {
                यदि (SDL_BITSPERPIXEL(dst->format) == 4) {
                    Uint8 b = (((Uint8)color << 4) | (Uint8)color);
                    SDL_memset(dst->pixels, b, (size_t)dst->h * dst->pitch);
                    प्रत्यागम true;
                }
            }
        }
        प्रत्यागम SDL_SetError("SDL_FillSurfaceRects(): Unsupported surface format");
    }

    यदि (fill_function == रिक्त) {
        विकल्प (SDL_BYTESPERPIXEL(dst->format)) {
        पक्ष 1:
        {
            color |= (color << 8);
            color |= (color << 16);
#ifdef SDL_SSE_INTRINSICS
            यदि (SDL_HasSSE()) {
                fill_function = SDL_FillSurfaceRect1SSE;
                भङ्ग;
            }
#endif
            fill_function = SDL_FillSurfaceRect1;
            भङ्ग;
        }

        पक्ष 2:
        {
            color |= (color << 16);
#ifdef SDL_SSE_INTRINSICS
            यदि (SDL_HasSSE()) {
                fill_function = SDL_FillSurfaceRect2SSE;
                भङ्ग;
            }
#endif
            fill_function = SDL_FillSurfaceRect2;
            भङ्ग;
        }

        पक्ष 3:
            // 24-bit RGB is a slow path, at least for now.
            {
                fill_function = SDL_FillSurfaceRect3;
                भङ्ग;
            }

        पक्ष 4:
        {
#ifdef SDL_SSE_INTRINSICS
            यदि (SDL_HasSSE()) {
                fill_function = SDL_FillSurfaceRect4SSE;
                भङ्ग;
            }
#endif
#ifdef SDL_LSX_INTRINSICS
            यदि (SDL_HasLSX()) {
                fill_function = SDL_FillSurfaceRect4LSX;
                भङ्ग;
            }
#endif
            fill_function = SDL_FillSurfaceRect4;
            भङ्ग;
        }

        स्वभाव:
            प्रत्यागम SDL_SetError("Unsupported pixel format");
        }
    }

    प्रति (i = 0; i < गिनती; ++i) {
        rect = &rects[i];
        // Perform clipping
        यदि (!SDL_GetRectIntersection(rect, &dst->clip_rect, &clipped)) {
            अनुवर्त;
        }
        rect = &clipped;

        pixels = (Uint8 *)dst->pixels + rect->y * dst->pitch +
                 rect->x * SDL_BYTESPERPIXEL(dst->format);

        fill_function(pixels, dst->pitch, color, rect->w, rect->h);
    }

    // We're done!
    प्रत्यागम true;
}
