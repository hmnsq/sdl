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
#شامل "SDL_internal.h"

#شامل "SDL_surface_c.h"

#ifdef SDL_SSE_INTRINSICS
/* *INDENT-OFF* */ // clang-format off

#اگر defined(_MSC_VER) && !defined(__clang__)
#define SSE_BEGIN \
    __m128 c128; \
    c128.m128_u32[0] = color; \
    c128.m128_u32[1] = color; \
    c128.m128_u32[2] = color; \
    c128.m128_u32[3] = color
#وگرنه
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
    برای (i = n / 64; i--;) { \
        _mm_stream_ps((اعشاری *)(p+0), c128); \
        _mm_stream_ps((اعشاری *)(p+16), c128); \
        _mm_stream_ps((اعشاری *)(p+32), c128); \
        _mm_stream_ps((اعشاری *)(p+48), c128); \
        p += 64; \
    }

#define SSE_END

#define DEFINE_SSE_FILLRECT(bpp, type) \
ایستا تهی SDL_TARGETING("sse") SDL_FillSurfaceRect##bpp##SSE(Uint8 *pixels, صحیح pitch, Uint32 color, صحیح w, صحیح h) \
{ \
    صحیح i, n; \
    Uint8 *p = پوچ; \
  \
    /* If the number of bytes per row is equal to the pitch, treat */ \
    /* all rows as one long continuous row (for better performance) */ \
    اگر ((w) * (bpp) == pitch) { \
        w = w * h; \
        h = 1; \
    } \
 \
    SSE_BEGIN; \
 \
    وقتی (h--) { \
        n = (w) * (bpp); \
        p = pixels; \
 \
        اگر (n > 63) { \
            صحیح adjust = 16 - ((uintptr_t)p & 15); \
            اگر (adjust < 16) { \
                n -= adjust; \
                adjust /= (bpp); \
                وقتی (adjust--) { \
                    *((type *)p) = (type)color; \
                    p += (bpp); \
                } \
            } \
            SSE_WORK; \
        } \
        اگر (n & 63) { \
            صحیح remainder = (n & 63); \
            remainder /= (bpp); \
            وقتی (remainder--) { \
                *((type *)p) = (type)color; \
                p += (bpp); \
            } \
        } \
        pixels += pitch; \
    } \
 \
    SSE_END; \
}

ایستا تهی SDL_TARGETING("sse") SDL_FillSurfaceRect1SSE(Uint8 *pixels, صحیح pitch, Uint32 color, صحیح w, صحیح h)
{
    صحیح i, n;

    SSE_BEGIN;
    وقتی (h--) {
        Uint8 *p = pixels;
        n = w;

        اگر (n > 63) {
            صحیح adjust = 16 - ((uintptr_t)p & 15);
            اگر (adjust) {
                n -= adjust;
                SDL_memset(p, color, adjust);
                p += adjust;
            }
            SSE_WORK;
        }
        اگر (n & 63) {
            صحیح remainder = (n & 63);
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
    برای (i = n / 64; i--;) { \
        __lsx_vst(c128, p, 0); \
        __lsx_vst(c128, p, 16); \
        __lsx_vst(c128, p, 32); \
        __lsx_vst(c128, p, 48); \
        p += 64; \
    }

#define DEFINE_LSX_FILLRECT(bpp, type) \
ایستا تهی SDL_TARGETING("lsx") SDL_FillSurfaceRect##bpp##LSX(Uint8 *pixels, صحیح pitch, Uint32 color, صحیح w, صحیح h) \
{ \
    صحیح i, n; \
    Uint8 *p = پوچ; \
  \
    /* If the number of bytes per row is equal to the pitch, treat */ \
    /* all rows as one long continuous row (for better performance) */ \
    اگر ((w) * (bpp) == pitch) { \
        w = w * h; \
        h = 1; \
    } \
 \
    LSX_BEGIN; \
 \
    وقتی (h--) { \
        n = (w) * (bpp); \
        p = pixels; \
 \
        اگر (n > 63) { \
            صحیح adjust = 16 - ((uintptr_t)p & 15); \
            اگر (adjust < 16) { \
                n -= adjust; \
                adjust /= (bpp); \
                وقتی (adjust--) { \
                    *((type *)p) = (type)color; \
                    p += (bpp); \
                } \
            } \
            LSX_WORK; \
        } \
        اگر (n & 63) { \
            صحیح remainder = (n & 63); \
            remainder /= (bpp); \
            وقتی (remainder--) { \
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

ایستا تهی SDL_FillSurfaceRect1(Uint8 *pixels, صحیح pitch, Uint32 color, صحیح w, صحیح h)
{
    صحیح n;
    Uint8 *p = پوچ;

    وقتی (h--) {
        n = w;
        p = pixels;

        اگر (n > 3) {
            انتخاب ((uintptr_t)p & 3) {
            حالت 1:
                *p++ = (Uint8)color;
                --n;
                SDL_FALLTHROUGH;
            حالت 2:
                *p++ = (Uint8)color;
                --n;
                SDL_FALLTHROUGH;
            حالت 3:
                *p++ = (Uint8)color;
                --n;
            }
            SDL_memset4(p, color, (n >> 2));
        }
        اگر (n & 3) {
            p += (n & ~3);
            انتخاب (n & 3) {
            حالت 3:
                *p++ = (Uint8)color;
                SDL_FALLTHROUGH;
            حالت 2:
                *p++ = (Uint8)color;
                SDL_FALLTHROUGH;
            حالت 1:
                *p++ = (Uint8)color;
            }
        }
        pixels += pitch;
    }
}

ایستا تهی SDL_FillSurfaceRect2(Uint8 *pixels, صحیح pitch, Uint32 color, صحیح w, صحیح h)
{
    صحیح n;
    Uint16 *p = پوچ;

    وقتی (h--) {
        n = w;
        p = (Uint16 *)pixels;

        اگر (n > 1) {
            اگر ((uintptr_t)p & 2) {
                *p++ = (Uint16)color;
                --n;
            }
            SDL_memset4(p, color, (n >> 1));
        }
        اگر (n & 1) {
            p[n - 1] = (Uint16)color;
        }
        pixels += pitch;
    }
}

ایستا تهی SDL_FillSurfaceRect3(Uint8 *pixels, صحیح pitch, Uint32 color, صحیح w, صحیح h)
{
#اگر SDL_BYTEORDER == SDL_LIL_ENDIAN
    Uint8 b1 = (Uint8)(color & 0xFF);
    Uint8 b2 = (Uint8)((color >> 8) & 0xFF);
    Uint8 b3 = (Uint8)((color >> 16) & 0xFF);
#وگرنهاگر SDL_BYTEORDER == SDL_BIG_ENDIAN
    Uint8 b1 = (Uint8)((color >> 16) & 0xFF);
    Uint8 b2 = (Uint8)((color >> 8) & 0xFF);
    Uint8 b3 = (Uint8)(color & 0xFF);
#endif
    صحیح n;
    Uint8 *p = پوچ;

    وقتی (h--) {
        n = w;
        p = pixels;

        وقتی (n--) {
            *p++ = b1;
            *p++ = b2;
            *p++ = b3;
        }
        pixels += pitch;
    }
}

ایستا تهی SDL_FillSurfaceRect4(Uint8 *pixels, صحیح pitch, Uint32 color, صحیح w, صحیح h)
{
    وقتی (h--) {
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
        بازگشت SDL_InvalidParamError("SDL_FillSurfaceRect(): dst");
    }

    // If 'rect' == NULL, then fill the whole surface
    اگر (!rect) {
        rect = &dst->clip_rect;
        // Don't attempt to fill if the surface's clip_rect is empty
        اگر (SDL_RectEmpty(rect)) {
            بازگشت true;
        }
    }

    بازگشت SDL_FillSurfaceRects(dst, rect, 1, color);
}

bool SDL_FillSurfaceRects(SDL_Surface *dst, ثابت SDL_Rect *rects, صحیح شمار, Uint32 color)
{
    SDL_Rect clipped;
    Uint8 *pixels;
    ثابت SDL_Rect *rect;
    تهی (*fill_function)(Uint8 * pixels, صحیح pitch, Uint32 color, صحیح w, صحیح h) = پوچ;
    صحیح i;

    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        بازگشت SDL_InvalidParamError("SDL_FillSurfaceRects(): dst");
    }

    CHECK_PARAM(!rects) {
        بازگشت SDL_InvalidParamError("SDL_FillSurfaceRects(): rects");
    }

    اگر (!dst->pixels && SDL_MUSTLOCK(dst)) {
        بازگشت SDL_SetError("SDL_FillSurfaceRects(): You must lock the surface");
    }

    // Nothing to do
    اگر (dst->w == 0 || dst->h == 0 || !dst->pixels) {
        بازگشت true;
    }

    /* This function doesn't usually work on surfaces < 8 bpp
     * Except: support for 4bits, when filling full size.
     */
    اگر (SDL_BITSPERPIXEL(dst->format) < 8) {
        اگر (شمار == 1) {
            ثابت SDL_Rect *r = &rects[0];
            اگر (r->x == 0 && r->y == 0 && r->w == dst->w && r->h == dst->h) {
                اگر (SDL_BITSPERPIXEL(dst->format) == 4) {
                    Uint8 b = (((Uint8)color << 4) | (Uint8)color);
                    SDL_memset(dst->pixels, b, (size_t)dst->h * dst->pitch);
                    بازگشت true;
                }
            }
        }
        بازگشت SDL_SetError("SDL_FillSurfaceRects(): Unsupported surface format");
    }

    اگر (fill_function == پوچ) {
        انتخاب (SDL_BYTESPERPIXEL(dst->format)) {
        حالت 1:
        {
            color |= (color << 8);
            color |= (color << 16);
#ifdef SDL_SSE_INTRINSICS
            اگر (SDL_HasSSE()) {
                fill_function = SDL_FillSurfaceRect1SSE;
                بشکن;
            }
#endif
            fill_function = SDL_FillSurfaceRect1;
            بشکن;
        }

        حالت 2:
        {
            color |= (color << 16);
#ifdef SDL_SSE_INTRINSICS
            اگر (SDL_HasSSE()) {
                fill_function = SDL_FillSurfaceRect2SSE;
                بشکن;
            }
#endif
            fill_function = SDL_FillSurfaceRect2;
            بشکن;
        }

        حالت 3:
            // 24-bit RGB is a slow path, at least for now.
            {
                fill_function = SDL_FillSurfaceRect3;
                بشکن;
            }

        حالت 4:
        {
#ifdef SDL_SSE_INTRINSICS
            اگر (SDL_HasSSE()) {
                fill_function = SDL_FillSurfaceRect4SSE;
                بشکن;
            }
#endif
#ifdef SDL_LSX_INTRINSICS
            اگر (SDL_HasLSX()) {
                fill_function = SDL_FillSurfaceRect4LSX;
                بشکن;
            }
#endif
            fill_function = SDL_FillSurfaceRect4;
            بشکن;
        }

        پیشفرض:
            بازگشت SDL_SetError("Unsupported pixel format");
        }
    }

    برای (i = 0; i < شمار; ++i) {
        rect = &rects[i];
        // Perform clipping
        اگر (!SDL_GetRectIntersection(rect, &dst->clip_rect, &clipped)) {
            ادامه;
        }
        rect = &clipped;

        pixels = (Uint8 *)dst->pixels + rect->y * dst->pitch +
                 rect->x * SDL_BYTESPERPIXEL(dst->format);

        fill_function(pixels, dst->pitch, color, rect->w, rect->h);
    }

    // We're done!
    بازگشت true;
}
