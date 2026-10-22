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

#اگر_تعریف_شدہ SDL_SSE_INTRINSICS
/* *INDENT-OFF* */ // clang-format off

#اگر defined(_MSC_VER) && !defined(__clang__)
#تعریف_کرو SSE_BEGIN \
    __m128 c128; \
    c128.m128_u32[0] = color; \
    c128.m128_u32[1] = color; \
    c128.m128_u32[2] = color; \
    c128.m128_u32[3] = color
#ورنہ
#تعریف_کرو SSE_BEGIN \
    __m128 c128; \
    DECLARE_ALIGNED(Uint32, cccc[4], 16); \
    cccc[0] = color; \
    cccc[1] = color; \
    cccc[2] = color; \
    cccc[3] = color; \
    c128 = *(__m128 *)cccc
#اگر_ختم

#تعریف_کرو SSE_WORK \
    برائے (i = n / 64; i--;) { \
        mm_دھارا_ps((اعشاری *)(p+0), c128); \
        mm_دھارا_ps((اعشاری *)(p+16), c128); \
        mm_دھارا_ps((اعشاری *)(p+32), c128); \
        mm_دھارا_ps((اعشاری *)(p+48), c128); \
        p += 64; \
    }

#تعریف_کرو SSE_انتہا

#تعریف_کرو DEFINE_SSE_FILLRECT(bpp, type) \
ساکن خالی SDL_TARGETING("sse") SDL_FillSurfaceRect##bpp##SSE(Uint8 *pixels, صحیح pitch, Uint32 color, صحیح w, صحیح h) \
{ \
    صحیح i, n; \
    Uint8 *p = تہی; \
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
    جب (h--) { \
        n = (w) * (bpp); \
        p = pixels; \
 \
        اگر (n > 63) { \
            صحیح adjust = 16 - ((uintptr_t)p & 15); \
            اگر (adjust < 16) { \
                n -= adjust; \
                adjust /= (bpp); \
                جب (adjust--) { \
                    *((type *)p) = (type)color; \
                    p += (bpp); \
                } \
            } \
            SSE_WORK; \
        } \
        اگر (n & 63) { \
            صحیح remainder = (n & 63); \
            remainder /= (bpp); \
            جب (remainder--) { \
                *((type *)p) = (type)color; \
                p += (bpp); \
            } \
        } \
        pixels += pitch; \
    } \
 \
    SSE_انتہا; \
}

ساکن خالی SDL_TARGETING("sse") SDL_FillSurfaceRect1SSE(Uint8 *pixels, صحیح pitch, Uint32 color, صحیح w, صحیح h)
{
    صحیح i, n;

    SSE_BEGIN;
    جب (h--) {
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

    SSE_انتہا;
}
// DEFINE_SSE_FILLRECT(1, Uint8)
DEFINE_SSE_FILLRECT(2, Uint16)
DEFINE_SSE_FILLRECT(4, Uint32)

/* *INDENT-ON* */ // clang-format on
#اگر_ختم            // SDL_SSE_INTRINSICS

#اگر_تعریف_شدہ SDL_LSX_INTRINSICS
/* *INDENT-OFF* */ // clang-format off

#تعریف_کرو LSX_BEGIN __m128i c128 = __lsx_vreplgr2vr_w(color);

#تعریف_کرو LSX_WORK \
    برائے (i = n / 64; i--;) { \
        __lsx_vst(c128, p, 0); \
        __lsx_vst(c128, p, 16); \
        __lsx_vst(c128, p, 32); \
        __lsx_vst(c128, p, 48); \
        p += 64; \
    }

#تعریف_کرو DEFINE_LSX_FILLRECT(bpp, type) \
ساکن خالی SDL_TARGETING("lsx") SDL_FillSurfaceRect##bpp##LSX(Uint8 *pixels, صحیح pitch, Uint32 color, صحیح w, صحیح h) \
{ \
    صحیح i, n; \
    Uint8 *p = تہی; \
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
    جب (h--) { \
        n = (w) * (bpp); \
        p = pixels; \
 \
        اگر (n > 63) { \
            صحیح adjust = 16 - ((uintptr_t)p & 15); \
            اگر (adjust < 16) { \
                n -= adjust; \
                adjust /= (bpp); \
                جب (adjust--) { \
                    *((type *)p) = (type)color; \
                    p += (bpp); \
                } \
            } \
            LSX_WORK; \
        } \
        اگر (n & 63) { \
            صحیح remainder = (n & 63); \
            remainder /= (bpp); \
            جب (remainder--) { \
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
#اگر_ختم // SDL_LSX_INTRINSICS

ساکن خالی SDL_FillSurfaceRect1(Uint8 *pixels, صحیح pitch, Uint32 color, صحیح w, صحیح h)
{
    صحیح n;
    Uint8 *p = تہی;

    جب (h--) {
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

ساکن خالی SDL_FillSurfaceRect2(Uint8 *pixels, صحیح pitch, Uint32 color, صحیح w, صحیح h)
{
    صحیح n;
    Uint16 *p = تہی;

    جب (h--) {
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

ساکن خالی SDL_FillSurfaceRect3(Uint8 *pixels, صحیح pitch, Uint32 color, صحیح w, صحیح h)
{
#اگر SDL_BYTEORDER == SDL_LIL_ENDIAN
    Uint8 b1 = (Uint8)(color & 0xFF);
    Uint8 b2 = (Uint8)((color >> 8) & 0xFF);
    Uint8 b3 = (Uint8)((color >> 16) & 0xFF);
#وگرنہ_اگر SDL_BYTEORDER == SDL_BIG_ENDIAN
    Uint8 b1 = (Uint8)((color >> 16) & 0xFF);
    Uint8 b2 = (Uint8)((color >> 8) & 0xFF);
    Uint8 b3 = (Uint8)(color & 0xFF);
#اگر_ختم
    صحیح n;
    Uint8 *p = تہی;

    جب (h--) {
        n = w;
        p = pixels;

        جب (n--) {
            *p++ = b1;
            *p++ = b2;
            *p++ = b3;
        }
        pixels += pitch;
    }
}

ساکن خالی SDL_FillSurfaceRect4(Uint8 *pixels, صحیح pitch, Uint32 color, صحیح w, صحیح h)
{
    جب (h--) {
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
        واپس SDL_InvalidParamError("SDL_FillSurfaceRect(): dst");
    }

    // If 'rect' == NULL, then fill the whole surface
    اگر (!rect) {
        rect = &dst->clip_rect;
        // Don't attempt to fill if the surface's clip_rect is empty
        اگر (SDL_Rect_خالی_خانے(rect)) {
            واپس true;
        }
    }

    واپس SDL_FillSurfaceRects(dst, rect, 1, color);
}

bool SDL_FillSurfaceRects(SDL_Surface *dst, ثابت SDL_Rect *rects, صحیح گنتی, Uint32 color)
{
    SDL_Rect clipped;
    Uint8 *pixels;
    ثابت SDL_Rect *rect;
    خالی (*fill_function)(Uint8 * pixels, صحیح pitch, Uint32 color, صحیح w, صحیح h) = تہی;
    صحیح i;

    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        واپس SDL_InvalidParamError("SDL_FillSurfaceRects(): dst");
    }

    CHECK_PARAM(!rects) {
        واپس SDL_InvalidParamError("SDL_FillSurfaceRects(): rects");
    }

    اگر (!dst->pixels && SDL_MUSTLOCK(dst)) {
        واپس SDL_سیٹ_Error("SDL_FillSurfaceRects(): You must lock the surface");
    }

    // Nothing to do
    اگر (dst->w == 0 || dst->h == 0 || !dst->pixels) {
        واپس true;
    }

    /* This function doesn't usually work on surfaces < 8 bpp
     * Except: support for 4bits, when filling full size.
     */
    اگر (SDL_BITSPERPIXEL(dst->format) < 8) {
        اگر (گنتی == 1) {
            ثابت SDL_Rect *r = &rects[0];
            اگر (r->x == 0 && r->y == 0 && r->w == dst->w && r->h == dst->h) {
                اگر (SDL_BITSPERPIXEL(dst->format) == 4) {
                    Uint8 b = (((Uint8)color << 4) | (Uint8)color);
                    SDL_memset(dst->pixels, b, (size_t)dst->h * dst->pitch);
                    واپس true;
                }
            }
        }
        واپس SDL_سیٹ_Error("SDL_FillSurfaceRects(): Unsupported surface format");
    }

    اگر (fill_function == تہی) {
        انتخاب (SDL_BYTESPERPIXEL(dst->format)) {
        حالت 1:
        {
            color |= (color << 8);
            color |= (color << 16);
#اگر_تعریف_شدہ SDL_SSE_INTRINSICS
            اگر (SDL_HasSSE()) {
                fill_function = SDL_FillSurfaceRect1SSE;
                توڑو;
            }
#اگر_ختم
            fill_function = SDL_FillSurfaceRect1;
            توڑو;
        }

        حالت 2:
        {
            color |= (color << 16);
#اگر_تعریف_شدہ SDL_SSE_INTRINSICS
            اگر (SDL_HasSSE()) {
                fill_function = SDL_FillSurfaceRect2SSE;
                توڑو;
            }
#اگر_ختم
            fill_function = SDL_FillSurfaceRect2;
            توڑو;
        }

        حالت 3:
            // 24-bit RGB is a slow path, at least for now.
            {
                fill_function = SDL_FillSurfaceRect3;
                توڑو;
            }

        حالت 4:
        {
#اگر_تعریف_شدہ SDL_SSE_INTRINSICS
            اگر (SDL_HasSSE()) {
                fill_function = SDL_FillSurfaceRect4SSE;
                توڑو;
            }
#اگر_ختم
#اگر_تعریف_شدہ SDL_LSX_INTRINSICS
            اگر (SDL_HasLSX()) {
                fill_function = SDL_FillSurfaceRect4LSX;
                توڑو;
            }
#اگر_ختم
            fill_function = SDL_FillSurfaceRect4;
            توڑو;
        }

        طےشدہ:
            واپس SDL_سیٹ_Error("Unsupported pixel format");
        }
    }

    برائے (i = 0; i < گنتی; ++i) {
        rect = &rects[i];
        // Perform clipping
        اگر (!SDL_GetRectIntersection(rect, &dst->clip_rect, &clipped)) {
            جاری;
        }
        rect = &clipped;

        pixels = (Uint8 *)dst->pixels + rect->y * dst->pitch +
                 rect->x * SDL_BYTESPERPIXEL(dst->format);

        fill_function(pixels, dst->pitch, color, rect->w, rect->h);
    }

    // We're done!
    واپس true;
}
