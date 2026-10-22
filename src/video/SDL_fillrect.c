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
#ضمن "SDL_internal.h"

#ضمن "SDL_surface_c.h"

#ifdef SDL_SSE_INTRINSICS
/* *INDENT-OFF* */ // clang-format off

#𐤀𐤌 defined(_MSC_VER) && !defined(__clang__)
#define SSE_BEGIN \
    __m128 c128; \
    c128.m128_u32[0] = color; \
    c128.m128_u32[1] = color; \
    c128.m128_u32[2] = color; \
    c128.m128_u32[3] = color
#وإلا
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
    لكل (i = n / 64; i--;) { \
        _mm_stream_ps((عائم *)(p+0), c128); \
        _mm_stream_ps((عائم *)(p+16), c128); \
        _mm_stream_ps((عائم *)(p+32), c128); \
        _mm_stream_ps((عائم *)(p+48), c128); \
        p += 64; \
    }

#define SSE_END

#define DEFINE_SSE_FILLRECT(bpp, type) \
ساكن فراغ SDL_TARGETING("sse") SDL_FillSurfaceRect##bpp##SSE(Uint8 *pixels, صحيح pitch, Uint32 color, صحيح w, صحيح h) \
{ \
    صحيح i, n; \
    Uint8 *p = عدم; \
  \
    /* If the number of bytes per row is equal to the pitch, treat */ \
    /* all rows as one long continuous row (for better performance) */ \
    𐤀𐤌 ((w) * (bpp) == pitch) { \
        w = w * h; \
        h = 1; \
    } \
 \
    SSE_BEGIN; \
 \
    طالما (h--) { \
        n = (w) * (bpp); \
        p = pixels; \
 \
        𐤀𐤌 (n > 63) { \
            صحيح adjust = 16 - ((uintptr_t)p & 15); \
            𐤀𐤌 (adjust < 16) { \
                n -= adjust; \
                adjust /= (bpp); \
                طالما (adjust--) { \
                    *((type *)p) = (type)color; \
                    p += (bpp); \
                } \
            } \
            SSE_WORK; \
        } \
        𐤀𐤌 (n & 63) { \
            صحيح remainder = (n & 63); \
            remainder /= (bpp); \
            طالما (remainder--) { \
                *((type *)p) = (type)color; \
                p += (bpp); \
            } \
        } \
        pixels += pitch; \
    } \
 \
    SSE_END; \
}

ساكن فراغ SDL_TARGETING("sse") SDL_FillSurfaceRect1SSE(Uint8 *pixels, صحيح pitch, Uint32 color, صحيح w, صحيح h)
{
    صحيح i, n;

    SSE_BEGIN;
    طالما (h--) {
        Uint8 *p = pixels;
        n = w;

        𐤀𐤌 (n > 63) {
            صحيح adjust = 16 - ((uintptr_t)p & 15);
            𐤀𐤌 (adjust) {
                n -= adjust;
                SDL_memset(p, color, adjust);
                p += adjust;
            }
            SSE_WORK;
        }
        𐤀𐤌 (n & 63) {
            صحيح remainder = (n & 63);
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
    لكل (i = n / 64; i--;) { \
        __lsx_vst(c128, p, 0); \
        __lsx_vst(c128, p, 16); \
        __lsx_vst(c128, p, 32); \
        __lsx_vst(c128, p, 48); \
        p += 64; \
    }

#define DEFINE_LSX_FILLRECT(bpp, type) \
ساكن فراغ SDL_TARGETING("lsx") SDL_FillSurfaceRect##bpp##LSX(Uint8 *pixels, صحيح pitch, Uint32 color, صحيح w, صحيح h) \
{ \
    صحيح i, n; \
    Uint8 *p = عدم; \
  \
    /* If the number of bytes per row is equal to the pitch, treat */ \
    /* all rows as one long continuous row (for better performance) */ \
    𐤀𐤌 ((w) * (bpp) == pitch) { \
        w = w * h; \
        h = 1; \
    } \
 \
    LSX_BEGIN; \
 \
    طالما (h--) { \
        n = (w) * (bpp); \
        p = pixels; \
 \
        𐤀𐤌 (n > 63) { \
            صحيح adjust = 16 - ((uintptr_t)p & 15); \
            𐤀𐤌 (adjust < 16) { \
                n -= adjust; \
                adjust /= (bpp); \
                طالما (adjust--) { \
                    *((type *)p) = (type)color; \
                    p += (bpp); \
                } \
            } \
            LSX_WORK; \
        } \
        𐤀𐤌 (n & 63) { \
            صحيح remainder = (n & 63); \
            remainder /= (bpp); \
            طالما (remainder--) { \
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

ساكن فراغ SDL_FillSurfaceRect1(Uint8 *pixels, صحيح pitch, Uint32 color, صحيح w, صحيح h)
{
    صحيح n;
    Uint8 *p = عدم;

    طالما (h--) {
        n = w;
        p = pixels;

        𐤀𐤌 (n > 3) {
            بدل ((uintptr_t)p & 3) {
            حالة 1:
                *p++ = (Uint8)color;
                --n;
                SDL_FALLTHROUGH;
            حالة 2:
                *p++ = (Uint8)color;
                --n;
                SDL_FALLTHROUGH;
            حالة 3:
                *p++ = (Uint8)color;
                --n;
            }
            SDL_memset4(p, color, (n >> 2));
        }
        𐤀𐤌 (n & 3) {
            p += (n & ~3);
            بدل (n & 3) {
            حالة 3:
                *p++ = (Uint8)color;
                SDL_FALLTHROUGH;
            حالة 2:
                *p++ = (Uint8)color;
                SDL_FALLTHROUGH;
            حالة 1:
                *p++ = (Uint8)color;
            }
        }
        pixels += pitch;
    }
}

ساكن فراغ SDL_FillSurfaceRect2(Uint8 *pixels, صحيح pitch, Uint32 color, صحيح w, صحيح h)
{
    صحيح n;
    Uint16 *p = عدم;

    طالما (h--) {
        n = w;
        p = (Uint16 *)pixels;

        𐤀𐤌 (n > 1) {
            𐤀𐤌 ((uintptr_t)p & 2) {
                *p++ = (Uint16)color;
                --n;
            }
            SDL_memset4(p, color, (n >> 1));
        }
        𐤀𐤌 (n & 1) {
            p[n - 1] = (Uint16)color;
        }
        pixels += pitch;
    }
}

ساكن فراغ SDL_FillSurfaceRect3(Uint8 *pixels, صحيح pitch, Uint32 color, صحيح w, صحيح h)
{
#𐤀𐤌 SDL_BYTEORDER == SDL_LIL_ENDIAN
    Uint8 b1 = (Uint8)(color & 0xFF);
    Uint8 b2 = (Uint8)((color >> 8) & 0xFF);
    Uint8 b3 = (Uint8)((color >> 16) & 0xFF);
#وإلاإذا SDL_BYTEORDER == SDL_BIG_ENDIAN
    Uint8 b1 = (Uint8)((color >> 16) & 0xFF);
    Uint8 b2 = (Uint8)((color >> 8) & 0xFF);
    Uint8 b3 = (Uint8)(color & 0xFF);
#endif
    صحيح n;
    Uint8 *p = عدم;

    طالما (h--) {
        n = w;
        p = pixels;

        طالما (n--) {
            *p++ = b1;
            *p++ = b2;
            *p++ = b3;
        }
        pixels += pitch;
    }
}

ساكن فراغ SDL_FillSurfaceRect4(Uint8 *pixels, صحيح pitch, Uint32 color, صحيح w, صحيح h)
{
    طالما (h--) {
        SDL_memset4(pixels, color, w);
        pixels += pitch;
    }
}

/*
 * This function performs a fast fill of the given rectangle with 'color'
 */
bool SDL_FillSurfaceRect(SDL_Surface *dst, ثابت SDL_Rect *rect, Uint32 color)
{
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        أرجع SDL_InvalidParamError("SDL_FillSurfaceRect(): dst");
    }

    // If 'rect' == NULL, then fill the whole surface
    𐤀𐤌 (!rect) {
        rect = &dst->clip_rect;
        // Don't attempt to fill if the surface's clip_rect is empty
        𐤀𐤌 (SDL_RectEmpty(rect)) {
            أرجع true;
        }
    }

    أرجع SDL_FillSurfaceRects(dst, rect, 1, color);
}

bool SDL_FillSurfaceRects(SDL_Surface *dst, ثابت SDL_Rect *rects, صحيح count, Uint32 color)
{
    SDL_Rect clipped;
    Uint8 *pixels;
    ثابت SDL_Rect *rect;
    فراغ (*fill_function)(Uint8 * pixels, صحيح pitch, Uint32 color, صحيح w, صحيح h) = عدم;
    صحيح i;

    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        أرجع SDL_InvalidParamError("SDL_FillSurfaceRects(): dst");
    }

    CHECK_PARAM(!rects) {
        أرجع SDL_InvalidParamError("SDL_FillSurfaceRects(): rects");
    }

    𐤀𐤌 (!dst->pixels && SDL_MUSTLOCK(dst)) {
        أرجع SDL_SetError("SDL_FillSurfaceRects(): You must lock the surface");
    }

    // Nothing to do
    𐤀𐤌 (dst->w == 0 || dst->h == 0 || !dst->pixels) {
        أرجع true;
    }

    /* This function doesn't usually work on surfaces < 8 bpp
     * Except: support for 4bits, when filling full size.
     */
    𐤀𐤌 (SDL_BITSPERPIXEL(dst->format) < 8) {
        𐤀𐤌 (count == 1) {
            ثابت SDL_Rect *r = &rects[0];
            𐤀𐤌 (r->x == 0 && r->y == 0 && r->w == dst->w && r->h == dst->h) {
                𐤀𐤌 (SDL_BITSPERPIXEL(dst->format) == 4) {
                    Uint8 b = (((Uint8)color << 4) | (Uint8)color);
                    SDL_memset(dst->pixels, b, (size_t)dst->h * dst->pitch);
                    أرجع true;
                }
            }
        }
        أرجع SDL_SetError("SDL_FillSurfaceRects(): Unsupported surface format");
    }

    𐤀𐤌 (fill_function == عدم) {
        بدل (SDL_BYTESPERPIXEL(dst->format)) {
        حالة 1:
        {
            color |= (color << 8);
            color |= (color << 16);
#ifdef SDL_SSE_INTRINSICS
            𐤀𐤌 (SDL_HasSSE()) {
                fill_function = SDL_FillSurfaceRect1SSE;
                اكسر;
            }
#endif
            fill_function = SDL_FillSurfaceRect1;
            اكسر;
        }

        حالة 2:
        {
            color |= (color << 16);
#ifdef SDL_SSE_INTRINSICS
            𐤀𐤌 (SDL_HasSSE()) {
                fill_function = SDL_FillSurfaceRect2SSE;
                اكسر;
            }
#endif
            fill_function = SDL_FillSurfaceRect2;
            اكسر;
        }

        حالة 3:
            // 24-bit RGB is a slow path, at least for now.
            {
                fill_function = SDL_FillSurfaceRect3;
                اكسر;
            }

        حالة 4:
        {
#ifdef SDL_SSE_INTRINSICS
            𐤀𐤌 (SDL_HasSSE()) {
                fill_function = SDL_FillSurfaceRect4SSE;
                اكسر;
            }
#endif
#ifdef SDL_LSX_INTRINSICS
            𐤀𐤌 (SDL_HasLSX()) {
                fill_function = SDL_FillSurfaceRect4LSX;
                اكسر;
            }
#endif
            fill_function = SDL_FillSurfaceRect4;
            اكسر;
        }

        افتراضي:
            أرجع SDL_SetError("Unsupported pixel format");
        }
    }

    لكل (i = 0; i < count; ++i) {
        rect = &rects[i];
        // Perform clipping
        𐤀𐤌 (!SDL_GetRectIntersection(rect, &dst->clip_rect, &clipped)) {
            استمر;
        }
        rect = &clipped;

        pixels = (Uint8 *)dst->pixels + rect->y * dst->pitch +
                 rect->x * SDL_BYTESPERPIXEL(dst->format);

        fill_function(pixels, dst->pitch, color, rect->w, rect->h);
    }

    // We're done!
    أرجع true;
}
