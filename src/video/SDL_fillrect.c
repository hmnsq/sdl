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
#అన్తర్భావ "SDL_internal.h"

#అన్తర్భావ "SDL_surface_c.h"

#నిర్వచితమైతే SDL_SSE_INTRINSICS
/* *INDENT-OFF* */ // clang-format off

#ఒకవేళ defined(_MSC_VER) && !defined(__clang__)
#నిర్వచించు SSE_BEGIN \
    __m128 c128; \
    c128.m128_u32[0] = color; \
    c128.m128_u32[1] = color; \
    c128.m128_u32[2] = color; \
    c128.m128_u32[3] = color
#లేకపోతే
#నిర్వచించు SSE_BEGIN \
    __m128 c128; \
    DECLARE_ALIGNED(Uint32, cccc[4], 16); \
    cccc[0] = color; \
    cccc[1] = color; \
    cccc[2] = color; \
    cccc[3] = color; \
    c128 = *(__m128 *)cccc
#అయితే_ముగింపు

#నిర్వచించు SSE_WORK \
    కొరకు (i = n / 64; i--;) { \
        mm_ప్రవాహం_ps((దశాంశం *)(p+0), c128); \
        mm_ప్రవాహం_ps((దశాంశం *)(p+16), c128); \
        mm_ప్రవాహం_ps((దశాంశం *)(p+32), c128); \
        mm_ప్రవాహం_ps((దశాంశం *)(p+48), c128); \
        p += 64; \
    }

#నిర్వచించు SSE_చివర

#నిర్వచించు DEFINE_SSE_FILLRECT(bpp, type) \
స్థిర శూన్య SDL_TARGETING("sse") SDL_FillSurfaceRect##bpp##SSE(Uint8 *pixels, పూర్ణాంకం pitch, Uint32 color, పూర్ణాంకం w, పూర్ణాంకం h) \
{ \
    పూర్ణాంకం i, n; \
    Uint8 *p = ఖాళీ; \
  \
    /* If the number of bytes per row is equal to the pitch, treat */ \
    /* all rows as one long continuous row (for better performance) */ \
    ఒకవేళ ((w) * (bpp) == pitch) { \
        w = w * h; \
        h = 1; \
    } \
 \
    SSE_BEGIN; \
 \
    అయితే (h--) { \
        n = (w) * (bpp); \
        p = pixels; \
 \
        ఒకవేళ (n > 63) { \
            పూర్ణాంకం adjust = 16 - ((uintptr_t)p & 15); \
            ఒకవేళ (adjust < 16) { \
                n -= adjust; \
                adjust /= (bpp); \
                అయితే (adjust--) { \
                    *((type *)p) = (type)color; \
                    p += (bpp); \
                } \
            } \
            SSE_WORK; \
        } \
        ఒకవేళ (n & 63) { \
            పూర్ణాంకం remainder = (n & 63); \
            remainder /= (bpp); \
            అయితే (remainder--) { \
                *((type *)p) = (type)color; \
                p += (bpp); \
            } \
        } \
        pixels += pitch; \
    } \
 \
    SSE_చివర; \
}

స్థిర శూన్య SDL_TARGETING("sse") SDL_FillSurfaceRect1SSE(Uint8 *pixels, పూర్ణాంకం pitch, Uint32 color, పూర్ణాంకం w, పూర్ణాంకం h)
{
    పూర్ణాంకం i, n;

    SSE_BEGIN;
    అయితే (h--) {
        Uint8 *p = pixels;
        n = w;

        ఒకవేళ (n > 63) {
            పూర్ణాంకం adjust = 16 - ((uintptr_t)p & 15);
            ఒకవేళ (adjust) {
                n -= adjust;
                SDL_memset(p, color, adjust);
                p += adjust;
            }
            SSE_WORK;
        }
        ఒకవేళ (n & 63) {
            పూర్ణాంకం remainder = (n & 63);
            SDL_memset(p, color, remainder);
        }
        pixels += pitch;
    }

    SSE_చివర;
}
// DEFINE_SSE_FILLRECT(1, Uint8)
DEFINE_SSE_FILLRECT(2, Uint16)
DEFINE_SSE_FILLRECT(4, Uint32)

/* *INDENT-ON* */ // clang-format on
#అయితే_ముగింపు            // SDL_SSE_INTRINSICS

#నిర్వచితమైతే SDL_LSX_INTRINSICS
/* *INDENT-OFF* */ // clang-format off

#నిర్వచించు LSX_BEGIN __m128i c128 = __lsx_vreplgr2vr_w(color);

#నిర్వచించు LSX_WORK \
    కొరకు (i = n / 64; i--;) { \
        __lsx_vst(c128, p, 0); \
        __lsx_vst(c128, p, 16); \
        __lsx_vst(c128, p, 32); \
        __lsx_vst(c128, p, 48); \
        p += 64; \
    }

#నిర్వచించు DEFINE_LSX_FILLRECT(bpp, type) \
స్థిర శూన్య SDL_TARGETING("lsx") SDL_FillSurfaceRect##bpp##LSX(Uint8 *pixels, పూర్ణాంకం pitch, Uint32 color, పూర్ణాంకం w, పూర్ణాంకం h) \
{ \
    పూర్ణాంకం i, n; \
    Uint8 *p = ఖాళీ; \
  \
    /* If the number of bytes per row is equal to the pitch, treat */ \
    /* all rows as one long continuous row (for better performance) */ \
    ఒకవేళ ((w) * (bpp) == pitch) { \
        w = w * h; \
        h = 1; \
    } \
 \
    LSX_BEGIN; \
 \
    అయితే (h--) { \
        n = (w) * (bpp); \
        p = pixels; \
 \
        ఒకవేళ (n > 63) { \
            పూర్ణాంకం adjust = 16 - ((uintptr_t)p & 15); \
            ఒకవేళ (adjust < 16) { \
                n -= adjust; \
                adjust /= (bpp); \
                అయితే (adjust--) { \
                    *((type *)p) = (type)color; \
                    p += (bpp); \
                } \
            } \
            LSX_WORK; \
        } \
        ఒకవేళ (n & 63) { \
            పూర్ణాంకం remainder = (n & 63); \
            remainder /= (bpp); \
            అయితే (remainder--) { \
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
#అయితే_ముగింపు // SDL_LSX_INTRINSICS

స్థిర శూన్య SDL_FillSurfaceRect1(Uint8 *pixels, పూర్ణాంకం pitch, Uint32 color, పూర్ణాంకం w, పూర్ణాంకం h)
{
    పూర్ణాంకం n;
    Uint8 *p = ఖాళీ;

    అయితే (h--) {
        n = w;
        p = pixels;

        ఒకవేళ (n > 3) {
            ఎంపిక ((uintptr_t)p & 3) {
            స్థితి 1:
                *p++ = (Uint8)color;
                --n;
                SDL_FALLTHROUGH;
            స్థితి 2:
                *p++ = (Uint8)color;
                --n;
                SDL_FALLTHROUGH;
            స్థితి 3:
                *p++ = (Uint8)color;
                --n;
            }
            SDL_memset4(p, color, (n >> 2));
        }
        ఒకవేళ (n & 3) {
            p += (n & ~3);
            ఎంపిక (n & 3) {
            స్థితి 3:
                *p++ = (Uint8)color;
                SDL_FALLTHROUGH;
            స్థితి 2:
                *p++ = (Uint8)color;
                SDL_FALLTHROUGH;
            స్థితి 1:
                *p++ = (Uint8)color;
            }
        }
        pixels += pitch;
    }
}

స్థిర శూన్య SDL_FillSurfaceRect2(Uint8 *pixels, పూర్ణాంకం pitch, Uint32 color, పూర్ణాంకం w, పూర్ణాంకం h)
{
    పూర్ణాంకం n;
    Uint16 *p = ఖాళీ;

    అయితే (h--) {
        n = w;
        p = (Uint16 *)pixels;

        ఒకవేళ (n > 1) {
            ఒకవేళ ((uintptr_t)p & 2) {
                *p++ = (Uint16)color;
                --n;
            }
            SDL_memset4(p, color, (n >> 1));
        }
        ఒకవేళ (n & 1) {
            p[n - 1] = (Uint16)color;
        }
        pixels += pitch;
    }
}

స్థిర శూన్య SDL_FillSurfaceRect3(Uint8 *pixels, పూర్ణాంకం pitch, Uint32 color, పూర్ణాంకం w, పూర్ణాంకం h)
{
#ఒకవేళ SDL_BYTEORDER == SDL_LIL_ENDIAN
    Uint8 b1 = (Uint8)(color & 0xFF);
    Uint8 b2 = (Uint8)((color >> 8) & 0xFF);
    Uint8 b3 = (Uint8)((color >> 16) & 0xFF);
#లేదావేళ SDL_BYTEORDER == SDL_BIG_ENDIAN
    Uint8 b1 = (Uint8)((color >> 16) & 0xFF);
    Uint8 b2 = (Uint8)((color >> 8) & 0xFF);
    Uint8 b3 = (Uint8)(color & 0xFF);
#అయితే_ముగింపు
    పూర్ణాంకం n;
    Uint8 *p = ఖాళీ;

    అయితే (h--) {
        n = w;
        p = pixels;

        అయితే (n--) {
            *p++ = b1;
            *p++ = b2;
            *p++ = b3;
        }
        pixels += pitch;
    }
}

స్థిర శూన్య SDL_FillSurfaceRect4(Uint8 *pixels, పూర్ణాంకం pitch, Uint32 color, పూర్ణాంకం w, పూర్ణాంకం h)
{
    అయితే (h--) {
        SDL_memset4(pixels, color, w);
        pixels += pitch;
    }
}

/*
 * This function performs a fast fill of the given rectangle with 'color'
 */
bool SDL_FillSurfaceRect(SDL_Surface *dst, స్థిరరాశి SDL_Rect *rect, Uint32 color)
{
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        తిరిగి SDL_InvalidParamError("SDL_FillSurfaceRect(): dst");
    }

    // If 'rect' == NULL, then fill the whole surface
    ఒకవేళ (!rect) {
        rect = &dst->clip_rect;
        // Don't attempt to fill if the surface's clip_rect is empty
        ఒకవేళ (SDL_Rect_ఖాళీలు(rect)) {
            తిరిగి true;
        }
    }

    తిరిగి SDL_FillSurfaceRects(dst, rect, 1, color);
}

bool SDL_FillSurfaceRects(SDL_Surface *dst, స్థిరరాశి SDL_Rect *rects, పూర్ణాంకం లెక్క, Uint32 color)
{
    SDL_Rect clipped;
    Uint8 *pixels;
    స్థిరరాశి SDL_Rect *rect;
    శూన్య (*fill_function)(Uint8 * pixels, పూర్ణాంకం pitch, Uint32 color, పూర్ణాంకం w, పూర్ణాంకం h) = ఖాళీ;
    పూర్ణాంకం i;

    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        తిరిగి SDL_InvalidParamError("SDL_FillSurfaceRects(): dst");
    }

    CHECK_PARAM(!rects) {
        తిరిగి SDL_InvalidParamError("SDL_FillSurfaceRects(): rects");
    }

    ఒకవేళ (!dst->pixels && SDL_MUSTLOCK(dst)) {
        తిరిగి SDL_సమితి_Error("SDL_FillSurfaceRects(): You must lock the surface");
    }

    // Nothing to do
    ఒకవేళ (dst->w == 0 || dst->h == 0 || !dst->pixels) {
        తిరిగి true;
    }

    /* This function doesn't usually work on surfaces < 8 bpp
     * Except: support for 4bits, when filling full size.
     */
    ఒకవేళ (SDL_BITSPERPIXEL(dst->format) < 8) {
        ఒకవేళ (లెక్క == 1) {
            స్థిరరాశి SDL_Rect *r = &rects[0];
            ఒకవేళ (r->x == 0 && r->y == 0 && r->w == dst->w && r->h == dst->h) {
                ఒకవేళ (SDL_BITSPERPIXEL(dst->format) == 4) {
                    Uint8 b = (((Uint8)color << 4) | (Uint8)color);
                    SDL_memset(dst->pixels, b, (size_t)dst->h * dst->pitch);
                    తిరిగి true;
                }
            }
        }
        తిరిగి SDL_సమితి_Error("SDL_FillSurfaceRects(): Unsupported surface format");
    }

    ఒకవేళ (fill_function == ఖాళీ) {
        ఎంపిక (SDL_BYTESPERPIXEL(dst->format)) {
        స్థితి 1:
        {
            color |= (color << 8);
            color |= (color << 16);
#నిర్వచితమైతే SDL_SSE_INTRINSICS
            ఒకవేళ (SDL_HasSSE()) {
                fill_function = SDL_FillSurfaceRect1SSE;
                ఆపు;
            }
#అయితే_ముగింపు
            fill_function = SDL_FillSurfaceRect1;
            ఆపు;
        }

        స్థితి 2:
        {
            color |= (color << 16);
#నిర్వచితమైతే SDL_SSE_INTRINSICS
            ఒకవేళ (SDL_HasSSE()) {
                fill_function = SDL_FillSurfaceRect2SSE;
                ఆపు;
            }
#అయితే_ముగింపు
            fill_function = SDL_FillSurfaceRect2;
            ఆపు;
        }

        స్థితి 3:
            // 24-bit RGB is a slow path, at least for now.
            {
                fill_function = SDL_FillSurfaceRect3;
                ఆపు;
            }

        స్థితి 4:
        {
#నిర్వచితమైతే SDL_SSE_INTRINSICS
            ఒకవేళ (SDL_HasSSE()) {
                fill_function = SDL_FillSurfaceRect4SSE;
                ఆపు;
            }
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_LSX_INTRINSICS
            ఒకవేళ (SDL_HasLSX()) {
                fill_function = SDL_FillSurfaceRect4LSX;
                ఆపు;
            }
#అయితే_ముగింపు
            fill_function = SDL_FillSurfaceRect4;
            ఆపు;
        }

        అప్రమేయ:
            తిరిగి SDL_సమితి_Error("Unsupported pixel format");
        }
    }

    కొరకు (i = 0; i < లెక్క; ++i) {
        rect = &rects[i];
        // Perform clipping
        ఒకవేళ (!SDL_GetRectIntersection(rect, &dst->clip_rect, &clipped)) {
            కొనసాగు;
        }
        rect = &clipped;

        pixels = (Uint8 *)dst->pixels + rect->y * dst->pitch +
                 rect->x * SDL_BYTESPERPIXEL(dst->format);

        fill_function(pixels, dst->pitch, color, rect->w, rect->h);
    }

    // We're done!
    తిరిగి true;
}
