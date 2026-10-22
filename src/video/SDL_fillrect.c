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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ଅନ୍ତର୍ଭାଵ "SDL_surface_c.h"

#ifdef SDL_SSE_INTRINSICS
/* *INDENT-OFF* */ // clang-format off

#ଯଦି defined(_MSC_VER) && !defined(__clang__)
#define SSE_BEGIN \
    __m128 c128; \
    c128.m128_u32[0] = color; \
    c128.m128_u32[1] = color; \
    c128.m128_u32[2] = color; \
    c128.m128_u32[3] = color
#ଅନ୍ୟଥା
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
    ପାଇଁ (i = n / 64; i--;) { \
        _mm_stream_ps((ଦଶମିକ *)(p+0), c128); \
        _mm_stream_ps((ଦଶମିକ *)(p+16), c128); \
        _mm_stream_ps((ଦଶମିକ *)(p+32), c128); \
        _mm_stream_ps((ଦଶମିକ *)(p+48), c128); \
        p += 64; \
    }

#define SSE_END

#define DEFINE_SSE_FILLRECT(bpp, type) \
ସ୍ଥିର ଶୂନ୍ୟ SDL_TARGETING("sse") SDL_FillSurfaceRect##bpp##SSE(Uint8 *pixels, ପୂର୍ଣ୍ଣସଂଖ୍ୟା pitch, Uint32 color, ପୂର୍ଣ୍ଣସଂଖ୍ୟା w, ପୂର୍ଣ୍ଣସଂଖ୍ୟା h) \
{ \
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, n; \
    Uint8 *p = ଖାଲି; \
  \
    /* If the number of bytes per row is equal to the pitch, treat */ \
    /* all rows as one long continuous row (for better performance) */ \
    ଯଦି ((w) * (bpp) == pitch) { \
        w = w * h; \
        h = 1; \
    } \
 \
    SSE_BEGIN; \
 \
    ଯେତେବେଳେ (h--) { \
        n = (w) * (bpp); \
        p = pixels; \
 \
        ଯଦି (n > 63) { \
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା adjust = 16 - ((uintptr_t)p & 15); \
            ଯଦି (adjust < 16) { \
                n -= adjust; \
                adjust /= (bpp); \
                ଯେତେବେଳେ (adjust--) { \
                    *((type *)p) = (type)color; \
                    p += (bpp); \
                } \
            } \
            SSE_WORK; \
        } \
        ଯଦି (n & 63) { \
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା remainder = (n & 63); \
            remainder /= (bpp); \
            ଯେତେବେଳେ (remainder--) { \
                *((type *)p) = (type)color; \
                p += (bpp); \
            } \
        } \
        pixels += pitch; \
    } \
 \
    SSE_END; \
}

ସ୍ଥିର ଶୂନ୍ୟ SDL_TARGETING("sse") SDL_FillSurfaceRect1SSE(Uint8 *pixels, ପୂର୍ଣ୍ଣସଂଖ୍ୟା pitch, Uint32 color, ପୂର୍ଣ୍ଣସଂଖ୍ୟା w, ପୂର୍ଣ୍ଣସଂଖ୍ୟା h)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, n;

    SSE_BEGIN;
    ଯେତେବେଳେ (h--) {
        Uint8 *p = pixels;
        n = w;

        ଯଦି (n > 63) {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା adjust = 16 - ((uintptr_t)p & 15);
            ଯଦି (adjust) {
                n -= adjust;
                SDL_memset(p, color, adjust);
                p += adjust;
            }
            SSE_WORK;
        }
        ଯଦି (n & 63) {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା remainder = (n & 63);
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
    ପାଇଁ (i = n / 64; i--;) { \
        __lsx_vst(c128, p, 0); \
        __lsx_vst(c128, p, 16); \
        __lsx_vst(c128, p, 32); \
        __lsx_vst(c128, p, 48); \
        p += 64; \
    }

#define DEFINE_LSX_FILLRECT(bpp, type) \
ସ୍ଥିର ଶୂନ୍ୟ SDL_TARGETING("lsx") SDL_FillSurfaceRect##bpp##LSX(Uint8 *pixels, ପୂର୍ଣ୍ଣସଂଖ୍ୟା pitch, Uint32 color, ପୂର୍ଣ୍ଣସଂଖ୍ୟା w, ପୂର୍ଣ୍ଣସଂଖ୍ୟା h) \
{ \
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, n; \
    Uint8 *p = ଖାଲି; \
  \
    /* If the number of bytes per row is equal to the pitch, treat */ \
    /* all rows as one long continuous row (for better performance) */ \
    ଯଦି ((w) * (bpp) == pitch) { \
        w = w * h; \
        h = 1; \
    } \
 \
    LSX_BEGIN; \
 \
    ଯେତେବେଳେ (h--) { \
        n = (w) * (bpp); \
        p = pixels; \
 \
        ଯଦି (n > 63) { \
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା adjust = 16 - ((uintptr_t)p & 15); \
            ଯଦି (adjust < 16) { \
                n -= adjust; \
                adjust /= (bpp); \
                ଯେତେବେଳେ (adjust--) { \
                    *((type *)p) = (type)color; \
                    p += (bpp); \
                } \
            } \
            LSX_WORK; \
        } \
        ଯଦି (n & 63) { \
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା remainder = (n & 63); \
            remainder /= (bpp); \
            ଯେତେବେଳେ (remainder--) { \
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

ସ୍ଥିର ଶୂନ୍ୟ SDL_FillSurfaceRect1(Uint8 *pixels, ପୂର୍ଣ୍ଣସଂଖ୍ୟା pitch, Uint32 color, ପୂର୍ଣ୍ଣସଂଖ୍ୟା w, ପୂର୍ଣ୍ଣସଂଖ୍ୟା h)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା n;
    Uint8 *p = ଖାଲି;

    ଯେତେବେଳେ (h--) {
        n = w;
        p = pixels;

        ଯଦି (n > 3) {
            ବାଛ ((uintptr_t)p & 3) {
            ସ୍ଥିତି 1:
                *p++ = (Uint8)color;
                --n;
                SDL_FALLTHROUGH;
            ସ୍ଥିତି 2:
                *p++ = (Uint8)color;
                --n;
                SDL_FALLTHROUGH;
            ସ୍ଥିତି 3:
                *p++ = (Uint8)color;
                --n;
            }
            SDL_memset4(p, color, (n >> 2));
        }
        ଯଦି (n & 3) {
            p += (n & ~3);
            ବାଛ (n & 3) {
            ସ୍ଥିତି 3:
                *p++ = (Uint8)color;
                SDL_FALLTHROUGH;
            ସ୍ଥିତି 2:
                *p++ = (Uint8)color;
                SDL_FALLTHROUGH;
            ସ୍ଥିତି 1:
                *p++ = (Uint8)color;
            }
        }
        pixels += pitch;
    }
}

ସ୍ଥିର ଶୂନ୍ୟ SDL_FillSurfaceRect2(Uint8 *pixels, ପୂର୍ଣ୍ଣସଂଖ୍ୟା pitch, Uint32 color, ପୂର୍ଣ୍ଣସଂଖ୍ୟା w, ପୂର୍ଣ୍ଣସଂଖ୍ୟା h)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା n;
    Uint16 *p = ଖାଲି;

    ଯେତେବେଳେ (h--) {
        n = w;
        p = (Uint16 *)pixels;

        ଯଦି (n > 1) {
            ଯଦି ((uintptr_t)p & 2) {
                *p++ = (Uint16)color;
                --n;
            }
            SDL_memset4(p, color, (n >> 1));
        }
        ଯଦି (n & 1) {
            p[n - 1] = (Uint16)color;
        }
        pixels += pitch;
    }
}

ସ୍ଥିର ଶୂନ୍ୟ SDL_FillSurfaceRect3(Uint8 *pixels, ପୂର୍ଣ୍ଣସଂଖ୍ୟା pitch, Uint32 color, ପୂର୍ଣ୍ଣସଂଖ୍ୟା w, ପୂର୍ଣ୍ଣସଂଖ୍ୟା h)
{
#ଯଦି SDL_BYTEORDER == SDL_LIL_ENDIAN
    Uint8 b1 = (Uint8)(color & 0xFF);
    Uint8 b2 = (Uint8)((color >> 8) & 0xFF);
    Uint8 b3 = (Uint8)((color >> 16) & 0xFF);
#ନଚେତଯଦି SDL_BYTEORDER == SDL_BIG_ENDIAN
    Uint8 b1 = (Uint8)((color >> 16) & 0xFF);
    Uint8 b2 = (Uint8)((color >> 8) & 0xFF);
    Uint8 b3 = (Uint8)(color & 0xFF);
#endif
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା n;
    Uint8 *p = ଖାଲି;

    ଯେତେବେଳେ (h--) {
        n = w;
        p = pixels;

        ଯେତେବେଳେ (n--) {
            *p++ = b1;
            *p++ = b2;
            *p++ = b3;
        }
        pixels += pitch;
    }
}

ସ୍ଥିର ଶୂନ୍ୟ SDL_FillSurfaceRect4(Uint8 *pixels, ପୂର୍ଣ୍ଣସଂଖ୍ୟା pitch, Uint32 color, ପୂର୍ଣ୍ଣସଂଖ୍ୟା w, ପୂର୍ଣ୍ଣସଂଖ୍ୟା h)
{
    ଯେତେବେଳେ (h--) {
        SDL_memset4(pixels, color, w);
        pixels += pitch;
    }
}

/*
 * This function performs a fast fill of the given rectangle with 'color'
 */
bool SDL_FillSurfaceRect(SDL_Surface *dst, ଅଚଳ SDL_Rect *rect, Uint32 color)
{
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        ଫେରନ୍ତୁ SDL_InvalidParamError("SDL_FillSurfaceRect(): dst");
    }

    // If 'rect' == NULL, then fill the whole surface
    ଯଦି (!rect) {
        rect = &dst->clip_rect;
        // Don't attempt to fill if the surface's clip_rect is empty
        ଯଦି (SDL_RectEmpty(rect)) {
            ଫେରନ୍ତୁ true;
        }
    }

    ଫେରନ୍ତୁ SDL_FillSurfaceRects(dst, rect, 1, color);
}

bool SDL_FillSurfaceRects(SDL_Surface *dst, ଅଚଳ SDL_Rect *rects, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଗଣନା_2, Uint32 color)
{
    SDL_Rect clipped;
    Uint8 *pixels;
    ଅଚଳ SDL_Rect *rect;
    ଶୂନ୍ୟ (*fill_function)(Uint8 * pixels, ପୂର୍ଣ୍ଣସଂଖ୍ୟା pitch, Uint32 color, ପୂର୍ଣ୍ଣସଂଖ୍ୟା w, ପୂର୍ଣ୍ଣସଂଖ୍ୟା h) = ଖାଲି;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        ଫେରନ୍ତୁ SDL_InvalidParamError("SDL_FillSurfaceRects(): dst");
    }

    CHECK_PARAM(!rects) {
        ଫେରନ୍ତୁ SDL_InvalidParamError("SDL_FillSurfaceRects(): rects");
    }

    ଯଦି (!dst->pixels && SDL_MUSTLOCK(dst)) {
        ଫେରନ୍ତୁ SDL_SetError("SDL_FillSurfaceRects(): You must lock the surface");
    }

    // Nothing to do
    ଯଦି (dst->w == 0 || dst->h == 0 || !dst->pixels) {
        ଫେରନ୍ତୁ true;
    }

    /* This function doesn't usually work on surfaces < 8 bpp
     * Except: support for 4bits, when filling full size.
     */
    ଯଦି (SDL_BITSPERPIXEL(dst->format) < 8) {
        ଯଦି (ଗଣନା_2 == 1) {
            ଅଚଳ SDL_Rect *r = &rects[0];
            ଯଦି (r->x == 0 && r->y == 0 && r->w == dst->w && r->h == dst->h) {
                ଯଦି (SDL_BITSPERPIXEL(dst->format) == 4) {
                    Uint8 b = (((Uint8)color << 4) | (Uint8)color);
                    SDL_memset(dst->pixels, b, (size_t)dst->h * dst->pitch);
                    ଫେରନ୍ତୁ true;
                }
            }
        }
        ଫେରନ୍ତୁ SDL_SetError("SDL_FillSurfaceRects(): Unsupported surface format");
    }

    ଯଦି (fill_function == ଖାଲି) {
        ବାଛ (SDL_BYTESPERPIXEL(dst->format)) {
        ସ୍ଥିତି 1:
        {
            color |= (color << 8);
            color |= (color << 16);
#ifdef SDL_SSE_INTRINSICS
            ଯଦି (SDL_HasSSE()) {
                fill_function = SDL_FillSurfaceRect1SSE;
                ଭାଙ୍ଗ;
            }
#endif
            fill_function = SDL_FillSurfaceRect1;
            ଭାଙ୍ଗ;
        }

        ସ୍ଥିତି 2:
        {
            color |= (color << 16);
#ifdef SDL_SSE_INTRINSICS
            ଯଦି (SDL_HasSSE()) {
                fill_function = SDL_FillSurfaceRect2SSE;
                ଭାଙ୍ଗ;
            }
#endif
            fill_function = SDL_FillSurfaceRect2;
            ଭାଙ୍ଗ;
        }

        ସ୍ଥିତି 3:
            // 24-bit RGB is a slow path, at least for now.
            {
                fill_function = SDL_FillSurfaceRect3;
                ଭାଙ୍ଗ;
            }

        ସ୍ଥିତି 4:
        {
#ifdef SDL_SSE_INTRINSICS
            ଯଦି (SDL_HasSSE()) {
                fill_function = SDL_FillSurfaceRect4SSE;
                ଭାଙ୍ଗ;
            }
#endif
#ifdef SDL_LSX_INTRINSICS
            ଯଦି (SDL_HasLSX()) {
                fill_function = SDL_FillSurfaceRect4LSX;
                ଭାଙ୍ଗ;
            }
#endif
            fill_function = SDL_FillSurfaceRect4;
            ଭାଙ୍ଗ;
        }

        ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
            ଫେରନ୍ତୁ SDL_SetError("Unsupported pixel format");
        }
    }

    ପାଇଁ (i = 0; i < ଗଣନା_2; ++i) {
        rect = &rects[i];
        // Perform clipping
        ଯଦି (!SDL_GetRectIntersection(rect, &dst->clip_rect, &clipped)) {
            ଜାରି;
        }
        rect = &clipped;

        pixels = (Uint8 *)dst->pixels + rect->y * dst->pitch +
                 rect->x * SDL_BYTESPERPIXEL(dst->format);

        fill_function(pixels, dst->pitch, color, rect->w, rect->h);
    }

    // We're done!
    ଫେରନ୍ତୁ true;
}
