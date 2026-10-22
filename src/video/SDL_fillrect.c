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
#அந்தர்பாவ "SDL_internal.h"

#அந்தர்பாவ "SDL_surface_c.h"

#ifdef SDL_SSE_INTRINSICS
/* *INDENT-OFF* */ // clang-format off

#எனில் defined(_MSC_VER) && !defined(__clang__)
#define SSE_BEGIN \
    __m128 c128; \
    c128.m128_u32[0] = color; \
    c128.m128_u32[1] = color; \
    c128.m128_u32[2] = color; \
    c128.m128_u32[3] = color
#இல்லையெனில்
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
    க்கு (i = n / 64; i--;) { \
        _mm_stream_ps((தசம *)(p+0), c128); \
        _mm_stream_ps((தசம *)(p+16), c128); \
        _mm_stream_ps((தசம *)(p+32), c128); \
        _mm_stream_ps((தசம *)(p+48), c128); \
        p += 64; \
    }

#define SSE_END

#define DEFINE_SSE_FILLRECT(bpp, type) \
நிலையான வெறுமை SDL_TARGETING("sse") SDL_FillSurfaceRect##bpp##SSE(Uint8 *pixels, முழு pitch, Uint32 color, முழு w, முழு h) \
{ \
    முழு i, n; \
    Uint8 *p = வெற்று; \
  \
    /* If the number of bytes per row is equal to the pitch, treat */ \
    /* all rows as one long continuous row (for better performance) */ \
    எனில் ((w) * (bpp) == pitch) { \
        w = w * h; \
        h = 1; \
    } \
 \
    SSE_BEGIN; \
 \
    போது (h--) { \
        n = (w) * (bpp); \
        p = pixels; \
 \
        எனில் (n > 63) { \
            முழு adjust = 16 - ((uintptr_t)p & 15); \
            எனில் (adjust < 16) { \
                n -= adjust; \
                adjust /= (bpp); \
                போது (adjust--) { \
                    *((type *)p) = (type)color; \
                    p += (bpp); \
                } \
            } \
            SSE_WORK; \
        } \
        எனில் (n & 63) { \
            முழு remainder = (n & 63); \
            remainder /= (bpp); \
            போது (remainder--) { \
                *((type *)p) = (type)color; \
                p += (bpp); \
            } \
        } \
        pixels += pitch; \
    } \
 \
    SSE_END; \
}

நிலையான வெறுமை SDL_TARGETING("sse") SDL_FillSurfaceRect1SSE(Uint8 *pixels, முழு pitch, Uint32 color, முழு w, முழு h)
{
    முழு i, n;

    SSE_BEGIN;
    போது (h--) {
        Uint8 *p = pixels;
        n = w;

        எனில் (n > 63) {
            முழு adjust = 16 - ((uintptr_t)p & 15);
            எனில் (adjust) {
                n -= adjust;
                SDL_memset(p, color, adjust);
                p += adjust;
            }
            SSE_WORK;
        }
        எனில் (n & 63) {
            முழு remainder = (n & 63);
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
    க்கு (i = n / 64; i--;) { \
        __lsx_vst(c128, p, 0); \
        __lsx_vst(c128, p, 16); \
        __lsx_vst(c128, p, 32); \
        __lsx_vst(c128, p, 48); \
        p += 64; \
    }

#define DEFINE_LSX_FILLRECT(bpp, type) \
நிலையான வெறுமை SDL_TARGETING("lsx") SDL_FillSurfaceRect##bpp##LSX(Uint8 *pixels, முழு pitch, Uint32 color, முழு w, முழு h) \
{ \
    முழு i, n; \
    Uint8 *p = வெற்று; \
  \
    /* If the number of bytes per row is equal to the pitch, treat */ \
    /* all rows as one long continuous row (for better performance) */ \
    எனில் ((w) * (bpp) == pitch) { \
        w = w * h; \
        h = 1; \
    } \
 \
    LSX_BEGIN; \
 \
    போது (h--) { \
        n = (w) * (bpp); \
        p = pixels; \
 \
        எனில் (n > 63) { \
            முழு adjust = 16 - ((uintptr_t)p & 15); \
            எனில் (adjust < 16) { \
                n -= adjust; \
                adjust /= (bpp); \
                போது (adjust--) { \
                    *((type *)p) = (type)color; \
                    p += (bpp); \
                } \
            } \
            LSX_WORK; \
        } \
        எனில் (n & 63) { \
            முழு remainder = (n & 63); \
            remainder /= (bpp); \
            போது (remainder--) { \
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

நிலையான வெறுமை SDL_FillSurfaceRect1(Uint8 *pixels, முழு pitch, Uint32 color, முழு w, முழு h)
{
    முழு n;
    Uint8 *p = வெற்று;

    போது (h--) {
        n = w;
        p = pixels;

        எனில் (n > 3) {
            தேர்வு ((uintptr_t)p & 3) {
            நிலை 1:
                *p++ = (Uint8)color;
                --n;
                SDL_FALLTHROUGH;
            நிலை 2:
                *p++ = (Uint8)color;
                --n;
                SDL_FALLTHROUGH;
            நிலை 3:
                *p++ = (Uint8)color;
                --n;
            }
            SDL_memset4(p, color, (n >> 2));
        }
        எனில் (n & 3) {
            p += (n & ~3);
            தேர்வு (n & 3) {
            நிலை 3:
                *p++ = (Uint8)color;
                SDL_FALLTHROUGH;
            நிலை 2:
                *p++ = (Uint8)color;
                SDL_FALLTHROUGH;
            நிலை 1:
                *p++ = (Uint8)color;
            }
        }
        pixels += pitch;
    }
}

நிலையான வெறுமை SDL_FillSurfaceRect2(Uint8 *pixels, முழு pitch, Uint32 color, முழு w, முழு h)
{
    முழு n;
    Uint16 *p = வெற்று;

    போது (h--) {
        n = w;
        p = (Uint16 *)pixels;

        எனில் (n > 1) {
            எனில் ((uintptr_t)p & 2) {
                *p++ = (Uint16)color;
                --n;
            }
            SDL_memset4(p, color, (n >> 1));
        }
        எனில் (n & 1) {
            p[n - 1] = (Uint16)color;
        }
        pixels += pitch;
    }
}

நிலையான வெறுமை SDL_FillSurfaceRect3(Uint8 *pixels, முழு pitch, Uint32 color, முழு w, முழு h)
{
#எனில் SDL_BYTEORDER == SDL_LIL_ENDIAN
    Uint8 b1 = (Uint8)(color & 0xFF);
    Uint8 b2 = (Uint8)((color >> 8) & 0xFF);
    Uint8 b3 = (Uint8)((color >> 16) & 0xFF);
#அல்லதெனில் SDL_BYTEORDER == SDL_BIG_ENDIAN
    Uint8 b1 = (Uint8)((color >> 16) & 0xFF);
    Uint8 b2 = (Uint8)((color >> 8) & 0xFF);
    Uint8 b3 = (Uint8)(color & 0xFF);
#endif
    முழு n;
    Uint8 *p = வெற்று;

    போது (h--) {
        n = w;
        p = pixels;

        போது (n--) {
            *p++ = b1;
            *p++ = b2;
            *p++ = b3;
        }
        pixels += pitch;
    }
}

நிலையான வெறுமை SDL_FillSurfaceRect4(Uint8 *pixels, முழு pitch, Uint32 color, முழு w, முழு h)
{
    போது (h--) {
        SDL_memset4(pixels, color, w);
        pixels += pitch;
    }
}

/*
 * This function performs a fast fill of the given rectangle with 'color'
 */
bool SDL_FillSurfaceRect(SDL_Surface *dst, மாறிலி SDL_Rect *rect, Uint32 color)
{
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        திரும்பு SDL_InvalidParamError("SDL_FillSurfaceRect(): dst");
    }

    // If 'rect' == NULL, then fill the whole surface
    எனில் (!rect) {
        rect = &dst->clip_rect;
        // Don't attempt to fill if the surface's clip_rect is empty
        எனில் (SDL_RectEmpty(rect)) {
            திரும்பு true;
        }
    }

    திரும்பு SDL_FillSurfaceRects(dst, rect, 1, color);
}

bool SDL_FillSurfaceRects(SDL_Surface *dst, மாறிலி SDL_Rect *rects, முழு மொத்தம், Uint32 color)
{
    SDL_Rect clipped;
    Uint8 *pixels;
    மாறிலி SDL_Rect *rect;
    வெறுமை (*fill_function)(Uint8 * pixels, முழு pitch, Uint32 color, முழு w, முழு h) = வெற்று;
    முழு i;

    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        திரும்பு SDL_InvalidParamError("SDL_FillSurfaceRects(): dst");
    }

    CHECK_PARAM(!rects) {
        திரும்பு SDL_InvalidParamError("SDL_FillSurfaceRects(): rects");
    }

    எனில் (!dst->pixels && SDL_MUSTLOCK(dst)) {
        திரும்பு SDL_SetError("SDL_FillSurfaceRects(): You must lock the surface");
    }

    // Nothing to do
    எனில் (dst->w == 0 || dst->h == 0 || !dst->pixels) {
        திரும்பு true;
    }

    /* This function doesn't usually work on surfaces < 8 bpp
     * Except: support for 4bits, when filling full size.
     */
    எனில் (SDL_BITSPERPIXEL(dst->format) < 8) {
        எனில் (மொத்தம் == 1) {
            மாறிலி SDL_Rect *r = &rects[0];
            எனில் (r->x == 0 && r->y == 0 && r->w == dst->w && r->h == dst->h) {
                எனில் (SDL_BITSPERPIXEL(dst->format) == 4) {
                    Uint8 b = (((Uint8)color << 4) | (Uint8)color);
                    SDL_memset(dst->pixels, b, (size_t)dst->h * dst->pitch);
                    திரும்பு true;
                }
            }
        }
        திரும்பு SDL_SetError("SDL_FillSurfaceRects(): Unsupported surface format");
    }

    எனில் (fill_function == வெற்று) {
        தேர்வு (SDL_BYTESPERPIXEL(dst->format)) {
        நிலை 1:
        {
            color |= (color << 8);
            color |= (color << 16);
#ifdef SDL_SSE_INTRINSICS
            எனில் (SDL_HasSSE()) {
                fill_function = SDL_FillSurfaceRect1SSE;
                நிறுத்து;
            }
#endif
            fill_function = SDL_FillSurfaceRect1;
            நிறுத்து;
        }

        நிலை 2:
        {
            color |= (color << 16);
#ifdef SDL_SSE_INTRINSICS
            எனில் (SDL_HasSSE()) {
                fill_function = SDL_FillSurfaceRect2SSE;
                நிறுத்து;
            }
#endif
            fill_function = SDL_FillSurfaceRect2;
            நிறுத்து;
        }

        நிலை 3:
            // 24-bit RGB is a slow path, at least for now.
            {
                fill_function = SDL_FillSurfaceRect3;
                நிறுத்து;
            }

        நிலை 4:
        {
#ifdef SDL_SSE_INTRINSICS
            எனில் (SDL_HasSSE()) {
                fill_function = SDL_FillSurfaceRect4SSE;
                நிறுத்து;
            }
#endif
#ifdef SDL_LSX_INTRINSICS
            எனில் (SDL_HasLSX()) {
                fill_function = SDL_FillSurfaceRect4LSX;
                நிறுத்து;
            }
#endif
            fill_function = SDL_FillSurfaceRect4;
            நிறுத்து;
        }

        இயல்பு:
            திரும்பு SDL_SetError("Unsupported pixel format");
        }
    }

    க்கு (i = 0; i < மொத்தம்; ++i) {
        rect = &rects[i];
        // Perform clipping
        எனில் (!SDL_GetRectIntersection(rect, &dst->clip_rect, &clipped)) {
            தொடர்;
        }
        rect = &clipped;

        pixels = (Uint8 *)dst->pixels + rect->y * dst->pitch +
                 rect->x * SDL_BYTESPERPIXEL(dst->format);

        fill_function(pixels, dst->pitch, color, rect->w, rect->h);
    }

    // We're done!
    திரும்பு true;
}
