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
#समावेश "SDL_internal.h"

#समावेश "SDL_surface_c.h"

#अगर_घोषित SDL_SSE_INTRINSICS
/* *INDENT-OFF* */ // clang-format off

#अगर defined(_MSC_VER) && !defined(__clang__)
#घोषणा SSE_BEGIN \
    __m128 c128; \
    c128.m128_u32[0] = color; \
    c128.m128_u32[1] = color; \
    c128.m128_u32[2] = color; \
    c128.m128_u32[3] = color
#अन्यथा
#घोषणा SSE_BEGIN \
    __m128 c128; \
    DECLARE_ALIGNED(Uint32, cccc[4], 16); \
    cccc[0] = color; \
    cccc[1] = color; \
    cccc[2] = color; \
    cccc[3] = color; \
    c128 = *(__m128 *)cccc
#पूर्ण_अगर

#घोषणा SSE_WORK \
    क्रम (i = n / 64; i--;) { \
        _mm_stream_ps((भग्न *)(p+0), c128); \
        _mm_stream_ps((भग्न *)(p+16), c128); \
        _mm_stream_ps((भग्न *)(p+32), c128); \
        _mm_stream_ps((भग्न *)(p+48), c128); \
        p += 64; \
    }

#घोषणा SSE_END

#घोषणा DEFINE_SSE_FILLRECT(bpp, type) \
अटल व्योम SDL_TARGETING("sse") SDL_FillSurfaceRect##bpp##SSE(Uint8 *pixels, पूर्णांक pitch, Uint32 color, पूर्णांक w, पूर्णांक h) \
{ \
    पूर्णांक i, n; \
    Uint8 *p = शून्य; \
  \
    /* If the number of bytes per row is equal to the pitch, treat */ \
    /* all rows as one long continuous row (for better performance) */ \
    अगर ((w) * (bpp) == pitch) { \
        w = w * h; \
        h = 1; \
    } \
 \
    SSE_BEGIN; \
 \
    जबतक (h--) { \
        n = (w) * (bpp); \
        p = pixels; \
 \
        अगर (n > 63) { \
            पूर्णांक adjust = 16 - ((uintptr_t)p & 15); \
            अगर (adjust < 16) { \
                n -= adjust; \
                adjust /= (bpp); \
                जबतक (adjust--) { \
                    *((type *)p) = (type)color; \
                    p += (bpp); \
                } \
            } \
            SSE_WORK; \
        } \
        अगर (n & 63) { \
            पूर्णांक remainder = (n & 63); \
            remainder /= (bpp); \
            जबतक (remainder--) { \
                *((type *)p) = (type)color; \
                p += (bpp); \
            } \
        } \
        pixels += pitch; \
    } \
 \
    SSE_END; \
}

अटल व्योम SDL_TARGETING("sse") SDL_FillSurfaceRect1SSE(Uint8 *pixels, पूर्णांक pitch, Uint32 color, पूर्णांक w, पूर्णांक h)
{
    पूर्णांक i, n;

    SSE_BEGIN;
    जबतक (h--) {
        Uint8 *p = pixels;
        n = w;

        अगर (n > 63) {
            पूर्णांक adjust = 16 - ((uintptr_t)p & 15);
            अगर (adjust) {
                n -= adjust;
                SDL_memset(p, color, adjust);
                p += adjust;
            }
            SSE_WORK;
        }
        अगर (n & 63) {
            पूर्णांक remainder = (n & 63);
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
#पूर्ण_अगर            // SDL_SSE_INTRINSICS

#अगर_घोषित SDL_LSX_INTRINSICS
/* *INDENT-OFF* */ // clang-format off

#घोषणा LSX_BEGIN __m128i c128 = __lsx_vreplgr2vr_w(color);

#घोषणा LSX_WORK \
    क्रम (i = n / 64; i--;) { \
        __lsx_vst(c128, p, 0); \
        __lsx_vst(c128, p, 16); \
        __lsx_vst(c128, p, 32); \
        __lsx_vst(c128, p, 48); \
        p += 64; \
    }

#घोषणा DEFINE_LSX_FILLRECT(bpp, type) \
अटल व्योम SDL_TARGETING("lsx") SDL_FillSurfaceRect##bpp##LSX(Uint8 *pixels, पूर्णांक pitch, Uint32 color, पूर्णांक w, पूर्णांक h) \
{ \
    पूर्णांक i, n; \
    Uint8 *p = शून्य; \
  \
    /* If the number of bytes per row is equal to the pitch, treat */ \
    /* all rows as one long continuous row (for better performance) */ \
    अगर ((w) * (bpp) == pitch) { \
        w = w * h; \
        h = 1; \
    } \
 \
    LSX_BEGIN; \
 \
    जबतक (h--) { \
        n = (w) * (bpp); \
        p = pixels; \
 \
        अगर (n > 63) { \
            पूर्णांक adjust = 16 - ((uintptr_t)p & 15); \
            अगर (adjust < 16) { \
                n -= adjust; \
                adjust /= (bpp); \
                जबतक (adjust--) { \
                    *((type *)p) = (type)color; \
                    p += (bpp); \
                } \
            } \
            LSX_WORK; \
        } \
        अगर (n & 63) { \
            पूर्णांक remainder = (n & 63); \
            remainder /= (bpp); \
            जबतक (remainder--) { \
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
#पूर्ण_अगर // SDL_LSX_INTRINSICS

अटल व्योम SDL_FillSurfaceRect1(Uint8 *pixels, पूर्णांक pitch, Uint32 color, पूर्णांक w, पूर्णांक h)
{
    पूर्णांक n;
    Uint8 *p = शून्य;

    जबतक (h--) {
        n = w;
        p = pixels;

        अगर (n > 3) {
            चयन ((uintptr_t)p & 3) {
            हाल 1:
                *p++ = (Uint8)color;
                --n;
                SDL_FALLTHROUGH;
            हाल 2:
                *p++ = (Uint8)color;
                --n;
                SDL_FALLTHROUGH;
            हाल 3:
                *p++ = (Uint8)color;
                --n;
            }
            SDL_memset4(p, color, (n >> 2));
        }
        अगर (n & 3) {
            p += (n & ~3);
            चयन (n & 3) {
            हाल 3:
                *p++ = (Uint8)color;
                SDL_FALLTHROUGH;
            हाल 2:
                *p++ = (Uint8)color;
                SDL_FALLTHROUGH;
            हाल 1:
                *p++ = (Uint8)color;
            }
        }
        pixels += pitch;
    }
}

अटल व्योम SDL_FillSurfaceRect2(Uint8 *pixels, पूर्णांक pitch, Uint32 color, पूर्णांक w, पूर्णांक h)
{
    पूर्णांक n;
    Uint16 *p = शून्य;

    जबतक (h--) {
        n = w;
        p = (Uint16 *)pixels;

        अगर (n > 1) {
            अगर ((uintptr_t)p & 2) {
                *p++ = (Uint16)color;
                --n;
            }
            SDL_memset4(p, color, (n >> 1));
        }
        अगर (n & 1) {
            p[n - 1] = (Uint16)color;
        }
        pixels += pitch;
    }
}

अटल व्योम SDL_FillSurfaceRect3(Uint8 *pixels, पूर्णांक pitch, Uint32 color, पूर्णांक w, पूर्णांक h)
{
#अगर SDL_BYTEORDER == SDL_LIL_ENDIAN
    Uint8 b1 = (Uint8)(color & 0xFF);
    Uint8 b2 = (Uint8)((color >> 8) & 0xFF);
    Uint8 b3 = (Uint8)((color >> 16) & 0xFF);
#या_अगर SDL_BYTEORDER == SDL_BIG_ENDIAN
    Uint8 b1 = (Uint8)((color >> 16) & 0xFF);
    Uint8 b2 = (Uint8)((color >> 8) & 0xFF);
    Uint8 b3 = (Uint8)(color & 0xFF);
#पूर्ण_अगर
    पूर्णांक n;
    Uint8 *p = शून्य;

    जबतक (h--) {
        n = w;
        p = pixels;

        जबतक (n--) {
            *p++ = b1;
            *p++ = b2;
            *p++ = b3;
        }
        pixels += pitch;
    }
}

अटल व्योम SDL_FillSurfaceRect4(Uint8 *pixels, पूर्णांक pitch, Uint32 color, पूर्णांक w, पूर्णांक h)
{
    जबतक (h--) {
        SDL_memset4(pixels, color, w);
        pixels += pitch;
    }
}

/*
 * This function performs a fast fill of the given rectangle with 'color'
 */
bool SDL_FillSurfaceRect(SDL_Surface *dst, स्थिर SDL_Rect *rect, Uint32 color)
{
    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        वापस SDL_InvalidParamError("SDL_FillSurfaceRect(): dst");
    }

    // If 'rect' == NULL, then fill the whole surface
    अगर (!rect) {
        rect = &dst->clip_rect;
        // Don't attempt to fill if the surface's clip_rect is empty
        अगर (SDL_RectEmpty(rect)) {
            वापस true;
        }
    }

    वापस SDL_FillSurfaceRects(dst, rect, 1, color);
}

bool SDL_FillSurfaceRects(SDL_Surface *dst, स्थिर SDL_Rect *rects, पूर्णांक गिनती, Uint32 color)
{
    SDL_Rect clipped;
    Uint8 *pixels;
    स्थिर SDL_Rect *rect;
    व्योम (*fill_function)(Uint8 * pixels, पूर्णांक pitch, Uint32 color, पूर्णांक w, पूर्णांक h) = शून्य;
    पूर्णांक i;

    CHECK_PARAM(!SDL_SurfaceValid(dst)) {
        वापस SDL_InvalidParamError("SDL_FillSurfaceRects(): dst");
    }

    CHECK_PARAM(!rects) {
        वापस SDL_InvalidParamError("SDL_FillSurfaceRects(): rects");
    }

    अगर (!dst->pixels && SDL_MUSTLOCK(dst)) {
        वापस SDL_SetError("SDL_FillSurfaceRects(): You must lock the surface");
    }

    // Nothing to do
    अगर (dst->w == 0 || dst->h == 0 || !dst->pixels) {
        वापस true;
    }

    /* This function doesn't usually work on surfaces < 8 bpp
     * Except: support for 4bits, when filling full size.
     */
    अगर (SDL_BITSPERPIXEL(dst->format) < 8) {
        अगर (गिनती == 1) {
            स्थिर SDL_Rect *r = &rects[0];
            अगर (r->x == 0 && r->y == 0 && r->w == dst->w && r->h == dst->h) {
                अगर (SDL_BITSPERPIXEL(dst->format) == 4) {
                    Uint8 b = (((Uint8)color << 4) | (Uint8)color);
                    SDL_memset(dst->pixels, b, (माप_प्रकार)dst->h * dst->pitch);
                    वापस true;
                }
            }
        }
        वापस SDL_SetError("SDL_FillSurfaceRects(): Unsupported surface format");
    }

    अगर (fill_function == शून्य) {
        चयन (SDL_BYTESPERPIXEL(dst->format)) {
        हाल 1:
        {
            color |= (color << 8);
            color |= (color << 16);
#अगर_घोषित SDL_SSE_INTRINSICS
            अगर (SDL_HasSSE()) {
                fill_function = SDL_FillSurfaceRect1SSE;
                अवरोध;
            }
#पूर्ण_अगर
            fill_function = SDL_FillSurfaceRect1;
            अवरोध;
        }

        हाल 2:
        {
            color |= (color << 16);
#अगर_घोषित SDL_SSE_INTRINSICS
            अगर (SDL_HasSSE()) {
                fill_function = SDL_FillSurfaceRect2SSE;
                अवरोध;
            }
#पूर्ण_अगर
            fill_function = SDL_FillSurfaceRect2;
            अवरोध;
        }

        हाल 3:
            // 24-bit RGB is a slow path, at least for now.
            {
                fill_function = SDL_FillSurfaceRect3;
                अवरोध;
            }

        हाल 4:
        {
#अगर_घोषित SDL_SSE_INTRINSICS
            अगर (SDL_HasSSE()) {
                fill_function = SDL_FillSurfaceRect4SSE;
                अवरोध;
            }
#पूर्ण_अगर
#अगर_घोषित SDL_LSX_INTRINSICS
            अगर (SDL_HasLSX()) {
                fill_function = SDL_FillSurfaceRect4LSX;
                अवरोध;
            }
#पूर्ण_अगर
            fill_function = SDL_FillSurfaceRect4;
            अवरोध;
        }

        शेष:
            वापस SDL_SetError("Unsupported pixel format");
        }
    }

    क्रम (i = 0; i < गिनती; ++i) {
        rect = &rects[i];
        // Perform clipping
        अगर (!SDL_GetRectIntersection(rect, &dst->clip_rect, &clipped)) {
            जारी;
        }
        rect = &clipped;

        pixels = (Uint8 *)dst->pixels + rect->y * dst->pitch +
                 rect->x * SDL_BYTESPERPIXEL(dst->format);

        fill_function(pixels, dst->pitch, color, rect->w, rect->h);
    }

    // We're done!
    वापस true;
}
