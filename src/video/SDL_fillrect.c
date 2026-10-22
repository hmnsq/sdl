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
#അന്തര്ഭാവ "SDL_internal.h"

#അന്തര്ഭാവ "SDL_surface_c.h"

#ifdef SDL_SSE_INTRINSICS
/* *INDENT-OFF* */ // clang-format off

#എങ്കിൽ defined(_MSC_VER) && !defined(__clang__)
#define SSE_BEGIN \
    __m128 c128; \
    c128.m128_u32[0] = color; \
    c128.m128_u32[1] = color; \
    c128.m128_u32[2] = color; \
    c128.m128_u32[3] = color
#അല്ലെങ്കിൽ
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
    വേണ്ടി (i = n / 64; i--;) { \
        _mm_stream_ps((ദശാംശം *)(p+0), c128); \
        _mm_stream_ps((ദശാംശം *)(p+16), c128); \
        _mm_stream_ps((ദശാംശം *)(p+32), c128); \
        _mm_stream_ps((ദശാംശം *)(p+48), c128); \
        p += 64; \
    }

#define SSE_END

#define DEFINE_SSE_FILLRECT(bpp, type) \
സ്ഥിതം ശൂന്യം SDL_TARGETING("sse") SDL_FillSurfaceRect##bpp##SSE(Uint8 *pixels, പൂർണ്ണസംഖ്യ pitch, Uint32 color, പൂർണ്ണസംഖ്യ w, പൂർണ്ണസംഖ്യ h) \
{ \
    പൂർണ്ണസംഖ്യ i, n; \
    Uint8 *p = ശൂന്യ; \
  \
    /* If the number of bytes per row is equal to the pitch, treat */ \
    /* all rows as one long continuous row (for better performance) */ \
    എങ്കിൽ ((w) * (bpp) == pitch) { \
        w = w * h; \
        h = 1; \
    } \
 \
    SSE_BEGIN; \
 \
    ആകുമ്പോൾ (h--) { \
        n = (w) * (bpp); \
        p = pixels; \
 \
        എങ്കിൽ (n > 63) { \
            പൂർണ്ണസംഖ്യ adjust = 16 - ((uintptr_t)p & 15); \
            എങ്കിൽ (adjust < 16) { \
                n -= adjust; \
                adjust /= (bpp); \
                ആകുമ്പോൾ (adjust--) { \
                    *((type *)p) = (type)color; \
                    p += (bpp); \
                } \
            } \
            SSE_WORK; \
        } \
        എങ്കിൽ (n & 63) { \
            പൂർണ്ണസംഖ്യ remainder = (n & 63); \
            remainder /= (bpp); \
            ആകുമ്പോൾ (remainder--) { \
                *((type *)p) = (type)color; \
                p += (bpp); \
            } \
        } \
        pixels += pitch; \
    } \
 \
    SSE_END; \
}

സ്ഥിതം ശൂന്യം SDL_TARGETING("sse") SDL_FillSurfaceRect1SSE(Uint8 *pixels, പൂർണ്ണസംഖ്യ pitch, Uint32 color, പൂർണ്ണസംഖ്യ w, പൂർണ്ണസംഖ്യ h)
{
    പൂർണ്ണസംഖ്യ i, n;

    SSE_BEGIN;
    ആകുമ്പോൾ (h--) {
        Uint8 *p = pixels;
        n = w;

        എങ്കിൽ (n > 63) {
            പൂർണ്ണസംഖ്യ adjust = 16 - ((uintptr_t)p & 15);
            എങ്കിൽ (adjust) {
                n -= adjust;
                SDL_memset(p, color, adjust);
                p += adjust;
            }
            SSE_WORK;
        }
        എങ്കിൽ (n & 63) {
            പൂർണ്ണസംഖ്യ remainder = (n & 63);
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
    വേണ്ടി (i = n / 64; i--;) { \
        __lsx_vst(c128, p, 0); \
        __lsx_vst(c128, p, 16); \
        __lsx_vst(c128, p, 32); \
        __lsx_vst(c128, p, 48); \
        p += 64; \
    }

#define DEFINE_LSX_FILLRECT(bpp, type) \
സ്ഥിതം ശൂന്യം SDL_TARGETING("lsx") SDL_FillSurfaceRect##bpp##LSX(Uint8 *pixels, പൂർണ്ണസംഖ്യ pitch, Uint32 color, പൂർണ്ണസംഖ്യ w, പൂർണ്ണസംഖ്യ h) \
{ \
    പൂർണ്ണസംഖ്യ i, n; \
    Uint8 *p = ശൂന്യ; \
  \
    /* If the number of bytes per row is equal to the pitch, treat */ \
    /* all rows as one long continuous row (for better performance) */ \
    എങ്കിൽ ((w) * (bpp) == pitch) { \
        w = w * h; \
        h = 1; \
    } \
 \
    LSX_BEGIN; \
 \
    ആകുമ്പോൾ (h--) { \
        n = (w) * (bpp); \
        p = pixels; \
 \
        എങ്കിൽ (n > 63) { \
            പൂർണ്ണസംഖ്യ adjust = 16 - ((uintptr_t)p & 15); \
            എങ്കിൽ (adjust < 16) { \
                n -= adjust; \
                adjust /= (bpp); \
                ആകുമ്പോൾ (adjust--) { \
                    *((type *)p) = (type)color; \
                    p += (bpp); \
                } \
            } \
            LSX_WORK; \
        } \
        എങ്കിൽ (n & 63) { \
            പൂർണ്ണസംഖ്യ remainder = (n & 63); \
            remainder /= (bpp); \
            ആകുമ്പോൾ (remainder--) { \
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

സ്ഥിതം ശൂന്യം SDL_FillSurfaceRect1(Uint8 *pixels, പൂർണ്ണസംഖ്യ pitch, Uint32 color, പൂർണ്ണസംഖ്യ w, പൂർണ്ണസംഖ്യ h)
{
    പൂർണ്ണസംഖ്യ n;
    Uint8 *p = ശൂന്യ;

    ആകുമ്പോൾ (h--) {
        n = w;
        p = pixels;

        എങ്കിൽ (n > 3) {
            തിരഞ്ഞെടുപ്പ് ((uintptr_t)p & 3) {
            അവസ്ഥ 1:
                *p++ = (Uint8)color;
                --n;
                SDL_FALLTHROUGH;
            അവസ്ഥ 2:
                *p++ = (Uint8)color;
                --n;
                SDL_FALLTHROUGH;
            അവസ്ഥ 3:
                *p++ = (Uint8)color;
                --n;
            }
            SDL_memset4(p, color, (n >> 2));
        }
        എങ്കിൽ (n & 3) {
            p += (n & ~3);
            തിരഞ്ഞെടുപ്പ് (n & 3) {
            അവസ്ഥ 3:
                *p++ = (Uint8)color;
                SDL_FALLTHROUGH;
            അവസ്ഥ 2:
                *p++ = (Uint8)color;
                SDL_FALLTHROUGH;
            അവസ്ഥ 1:
                *p++ = (Uint8)color;
            }
        }
        pixels += pitch;
    }
}

സ്ഥിതം ശൂന്യം SDL_FillSurfaceRect2(Uint8 *pixels, പൂർണ്ണസംഖ്യ pitch, Uint32 color, പൂർണ്ണസംഖ്യ w, പൂർണ്ണസംഖ്യ h)
{
    പൂർണ്ണസംഖ്യ n;
    Uint16 *p = ശൂന്യ;

    ആകുമ്പോൾ (h--) {
        n = w;
        p = (Uint16 *)pixels;

        എങ്കിൽ (n > 1) {
            എങ്കിൽ ((uintptr_t)p & 2) {
                *p++ = (Uint16)color;
                --n;
            }
            SDL_memset4(p, color, (n >> 1));
        }
        എങ്കിൽ (n & 1) {
            p[n - 1] = (Uint16)color;
        }
        pixels += pitch;
    }
}

സ്ഥിതം ശൂന്യം SDL_FillSurfaceRect3(Uint8 *pixels, പൂർണ്ണസംഖ്യ pitch, Uint32 color, പൂർണ്ണസംഖ്യ w, പൂർണ്ണസംഖ്യ h)
{
#എങ്കിൽ SDL_BYTEORDER == SDL_LIL_ENDIAN
    Uint8 b1 = (Uint8)(color & 0xFF);
    Uint8 b2 = (Uint8)((color >> 8) & 0xFF);
    Uint8 b3 = (Uint8)((color >> 16) & 0xFF);
#അല്ലെങ്കിലെങ്കിൽ SDL_BYTEORDER == SDL_BIG_ENDIAN
    Uint8 b1 = (Uint8)((color >> 16) & 0xFF);
    Uint8 b2 = (Uint8)((color >> 8) & 0xFF);
    Uint8 b3 = (Uint8)(color & 0xFF);
#endif
    പൂർണ്ണസംഖ്യ n;
    Uint8 *p = ശൂന്യ;

    ആകുമ്പോൾ (h--) {
        n = w;
        p = pixels;

        ആകുമ്പോൾ (n--) {
            *p++ = b1;
            *p++ = b2;
            *p++ = b3;
        }
        pixels += pitch;
    }
}

സ്ഥിതം ശൂന്യം SDL_FillSurfaceRect4(Uint8 *pixels, പൂർണ്ണസംഖ്യ pitch, Uint32 color, പൂർണ്ണസംഖ്യ w, പൂർണ്ണസംഖ്യ h)
{
    ആകുമ്പോൾ (h--) {
        SDL_memset4(pixels, color, w);
        pixels += pitch;
    }
}

/*
 * This function performs a fast fill of the given rectangle with 'color'
 */
bool SDL_FillSurfaceRect(SDL_Surface *dst, സ്ഥിരം SDL_Rect *rect, Uint32 color)
{
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        തിരികെ SDL_InvalidParamError("SDL_FillSurfaceRect(): dst");
    }

    // If 'rect' == NULL, then fill the whole surface
    എങ്കിൽ (!rect) {
        rect = &dst->clip_rect;
        // Don't attempt to fill if the surface's clip_rect is empty
        എങ്കിൽ (SDL_RectEmpty(rect)) {
            തിരികെ true;
        }
    }

    തിരികെ SDL_FillSurfaceRects(dst, rect, 1, color);
}

bool SDL_FillSurfaceRects(SDL_Surface *dst, സ്ഥിരം SDL_Rect *rects, പൂർണ്ണസംഖ്യ എണ്ണം, Uint32 color)
{
    SDL_Rect clipped;
    Uint8 *pixels;
    സ്ഥിരം SDL_Rect *rect;
    ശൂന്യം (*fill_function)(Uint8 * pixels, പൂർണ്ണസംഖ്യ pitch, Uint32 color, പൂർണ്ണസംഖ്യ w, പൂർണ്ണസംഖ്യ h) = ശൂന്യ;
    പൂർണ്ണസംഖ്യ i;

    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        തിരികെ SDL_InvalidParamError("SDL_FillSurfaceRects(): dst");
    }

    CHECK_PARAM(!rects) {
        തിരികെ SDL_InvalidParamError("SDL_FillSurfaceRects(): rects");
    }

    എങ്കിൽ (!dst->pixels && SDL_MUSTLOCK(dst)) {
        തിരികെ SDL_SetError("SDL_FillSurfaceRects(): You must lock the surface");
    }

    // Nothing to do
    എങ്കിൽ (dst->w == 0 || dst->h == 0 || !dst->pixels) {
        തിരികെ true;
    }

    /* This function doesn't usually work on surfaces < 8 bpp
     * Except: support for 4bits, when filling full size.
     */
    എങ്കിൽ (SDL_BITSPERPIXEL(dst->format) < 8) {
        എങ്കിൽ (എണ്ണം == 1) {
            സ്ഥിരം SDL_Rect *r = &rects[0];
            എങ്കിൽ (r->x == 0 && r->y == 0 && r->w == dst->w && r->h == dst->h) {
                എങ്കിൽ (SDL_BITSPERPIXEL(dst->format) == 4) {
                    Uint8 b = (((Uint8)color << 4) | (Uint8)color);
                    SDL_memset(dst->pixels, b, (size_t)dst->h * dst->pitch);
                    തിരികെ true;
                }
            }
        }
        തിരികെ SDL_SetError("SDL_FillSurfaceRects(): Unsupported surface format");
    }

    എങ്കിൽ (fill_function == ശൂന്യ) {
        തിരഞ്ഞെടുപ്പ് (SDL_BYTESPERPIXEL(dst->format)) {
        അവസ്ഥ 1:
        {
            color |= (color << 8);
            color |= (color << 16);
#ifdef SDL_SSE_INTRINSICS
            എങ്കിൽ (SDL_HasSSE()) {
                fill_function = SDL_FillSurfaceRect1SSE;
                നിർത്തുക;
            }
#endif
            fill_function = SDL_FillSurfaceRect1;
            നിർത്തുക;
        }

        അവസ്ഥ 2:
        {
            color |= (color << 16);
#ifdef SDL_SSE_INTRINSICS
            എങ്കിൽ (SDL_HasSSE()) {
                fill_function = SDL_FillSurfaceRect2SSE;
                നിർത്തുക;
            }
#endif
            fill_function = SDL_FillSurfaceRect2;
            നിർത്തുക;
        }

        അവസ്ഥ 3:
            // 24-bit RGB is a slow path, at least for now.
            {
                fill_function = SDL_FillSurfaceRect3;
                നിർത്തുക;
            }

        അവസ്ഥ 4:
        {
#ifdef SDL_SSE_INTRINSICS
            എങ്കിൽ (SDL_HasSSE()) {
                fill_function = SDL_FillSurfaceRect4SSE;
                നിർത്തുക;
            }
#endif
#ifdef SDL_LSX_INTRINSICS
            എങ്കിൽ (SDL_HasLSX()) {
                fill_function = SDL_FillSurfaceRect4LSX;
                നിർത്തുക;
            }
#endif
            fill_function = SDL_FillSurfaceRect4;
            നിർത്തുക;
        }

        സ്ഥിരസ്ഥിതി:
            തിരികെ SDL_SetError("Unsupported pixel format");
        }
    }

    വേണ്ടി (i = 0; i < എണ്ണം; ++i) {
        rect = &rects[i];
        // Perform clipping
        എങ്കിൽ (!SDL_GetRectIntersection(rect, &dst->clip_rect, &clipped)) {
            തുടരുക;
        }
        rect = &clipped;

        pixels = (Uint8 *)dst->pixels + rect->y * dst->pitch +
                 rect->x * SDL_BYTESPERPIXEL(dst->format);

        fill_function(pixels, dst->pitch, color, rect->w, rect->h);
    }

    // We're done!
    തിരികെ true;
}
