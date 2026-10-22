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

#यदि_अपरिभाषितम् SDL_blit_h_
#परिभाषय SDL_blit_h_

// Table to do pixel byte expansion
बाह्य ध्रुव Uint8 *SDL_expand_byte[9];
बाह्य ध्रुव Uint16 SDL_expand_byte_10[];

// SDL blit copy flags
#परिभाषय SDL_COPY_MODULATE_COLOR         0x00000001
#परिभाषय SDL_COPY_MODULATE_ALPHA         0x00000002
#परिभाषय SDL_COPY_MODULATE_आवरणम्		(SDL_COPY_MODULATE_COLOR | SDL_COPY_MODULATE_ALPHA)
#परिभाषय SDL_COPY_BLEND                  0x00000010
#परिभाषय SDL_COPY_BLEND_PREMULTIPLIED    0x00000020
#परिभाषय SDL_COPY_सङ्कलय                    0x00000040
#परिभाषय SDL_COPY_सङ्कलय_PREMULTIPLIED      0x00000080
#परिभाषय SDL_COPY_MOD                    0x00000100
#परिभाषय SDL_COPY_MUL                    0x00000200
#परिभाषय SDL_COPY_BLEND_आवरणम्		(SDL_COPY_BLEND | SDL_COPY_BLEND_PREMULTIPLIED | SDL_COPY_सङ्कलय | SDL_COPY_सङ्कलय_PREMULTIPLIED | SDL_COPY_MOD | SDL_COPY_MUL)
#परिभाषय SDL_COPY_COLORKEY               0x00000400
#परिभाषय SDL_COPY_निकटतमः                0x00000800
#परिभाषय SDL_COPY_RLE_DESIRED            0x00001000
#परिभाषय SDL_COPY_RLE_COLORKEY           0x00002000
#परिभाषय SDL_COPY_RLE_ALPHAKEY           0x00004000
#परिभाषय SDL_COPY_RLE_आवरणम्               (SDL_COPY_RLE_DESIRED | SDL_COPY_RLE_COLORKEY | SDL_COPY_RLE_ALPHAKEY)

// SDL blit CPU flags
#परिभाषय SDL_CPU_ANY                0x00000000
#परिभाषय SDL_CPU_MMX                0x00000001
#परिभाषय SDL_CPU_SSE                0x00000002
#परिभाषय SDL_CPU_SSE2               0x00000004
#परिभाषय SDL_CPU_ALTIVEC_PREFETCH   0x00000008
#परिभाषय SDL_CPU_ALTIVEC_NOPREFETCH 0x00000010

प्रकारनिर्देश संरचना
{
    SDL_Surface *src_surface;
    Uint8 *src;
    पूर्णाङ्क src_w, src_h;
    पूर्णाङ्क src_pitch;
    पूर्णाङ्क src_skip;
    पूर्णाङ्क leading_skip;
    SDL_Surface *dst_surface;
    Uint8 *dst;
    पूर्णाङ्क dst_w, dst_h;
    पूर्णाङ्क dst_pitch;
    पूर्णाङ्क dst_skip;
    ध्रुव SDL_PixelFormatDetails *src_fmt;
    ध्रुव SDL_Palette *src_pal;
    ध्रुव SDL_PixelFormatDetails *dst_fmt;
    ध्रुव SDL_Palette *dst_pal;
    Uint8 *सारणी;
    SDL_Hash_सारणी *palette_map;
    पूर्णाङ्क flags;
    Uint32 colorkey;
    Uint8 r, g, b, a;
} SDL_BlitInfo;

प्रकारनिर्देश शून्य (*SDL_BlitFunc)(SDL_BlitInfo *info);

प्रकारनिर्देश संरचना
{
    SDL_PixelFormat src_format;
    SDL_PixelFormat dst_format;
    पूर्णाङ्क flags;
    SDL_BlitFunc func;
} SDL_Blit_Func_प्रविष्टिः;

प्रकारनिर्देश bool (SDLCALL *SDL_Blit) (संरचना SDL_Surface *src, ध्रुव SDL_Rect *srcrect, संरचना SDL_Surface *dst, ध्रुव SDL_Rect *dstrect);

// Blit mapping definition
प्रकारनिर्देश संरचना SDL_BlitMap
{
    पूर्णाङ्क तटस्थः;
    SDL_Blit blit;
    शून्य *दत्त;
    SDL_BlitInfo info;

    /* the version count matches the destination; mismatch indicates
       an invalid mapping */
    Uint32 dst_palette_संस्करणम्;
    Uint32 src_palette_संस्करणम्;
} SDL_BlitMap;

// Functions found in SDL_blit.c
बाह्य bool SDL_CalculateBlit(SDL_Surface *surface, SDL_Surface *dst);

/* Functions found in SDL_blit_*.c */
बाह्य SDL_BlitFunc SDL_CalculateBlit0(SDL_Surface *surface);
बाह्य SDL_BlitFunc SDL_CalculateBlit1(SDL_Surface *surface);
बाह्य SDL_BlitFunc SDL_CalculateBlitN(SDL_Surface *surface);
बाह्य SDL_BlitFunc SDL_CalculateBlitA(SDL_Surface *surface);

/*
 * Useful macros for blitting routines
 */

#यदि_परिभाषितम् __GNUC__
#परिभाषय DECLARE_ALIGNED(t, v, a) t __attribute__((aligned(a))) v
#नोचेद्यदि defined(_MSC_VER)
#परिभाषय DECLARE_ALIGNED(t, v, a) __declspec(align(a)) t v
#अन्यथा
#परिभाषय DECLARE_ALIGNED(t, v, a) t v
#यदि_अन्तः

// Load pixel of the specified format from a buffer and get its R-G-B values
#परिभाषय RGB_FROM_PIXEL(Pixel, fmt, r, g, b)                                     \
    {                                                                           \
        r = SDL_expand_byte[fmt->Rbits][((Pixel & fmt->Rmask) >> fmt->Rshift)]; \
        g = SDL_expand_byte[fmt->Gbits][((Pixel & fmt->Gmask) >> fmt->Gshift)]; \
        b = SDL_expand_byte[fmt->Bbits][((Pixel & fmt->Bmask) >> fmt->Bshift)]; \
    }
#परिभाषय RGB_FROM_RGB565(Pixel, r, g, b)                   \
    {                                                     \
        r = SDL_expand_byte[5][((Pixel & 0xF800) >> 11)]; \
        g = SDL_expand_byte[6][((Pixel & 0x07E0) >> 5)];  \
        b = SDL_expand_byte[5][(Pixel & 0x001F)];         \
    }
#परिभाषय RGB_FROM_RGB555(Pixel, r, g, b)                   \
    {                                                     \
        r = SDL_expand_byte[5][((Pixel & 0x7C00) >> 10)]; \
        g = SDL_expand_byte[5][((Pixel & 0x03E0) >> 5)];  \
        b = SDL_expand_byte[5][(Pixel & 0x001F)];         \
    }
#परिभाषय RGB_FROM_XRGB8888(Pixel, r, g, b) \
    {                                   \
        r = ((Pixel & 0xFF0000) >> 16); \
        g = ((Pixel & 0xFF00) >> 8);    \
        b = (Pixel & 0xFF);             \
    }
#यदि SDL_BYTEORDER == SDL_LIL_ENDIAN
#परिभाषय GET_RGB24(B) (B[2] << 16) | (B[1] << 8) | B[0]
#अन्यथा
#परिभाषय GET_RGB24(B) (B[0] << 16) | (B[1] << 8) | B[2]
#यदि_अन्तः
#परिभाषय RETRIEVE_RGB_PIXEL(buf, bpp, Pixel)                \
    कुरु {                                                   \
        विकल्प (bpp) {                                     \
        पक्ष 1:                                            \
            Pixel = *((Uint8 *)(buf));                     \
            भङ्ग;                                         \
                                                           \
        पक्ष 2:                                            \
            Pixel = *((Uint16 *)(buf));                    \
            भङ्ग;                                         \
                                                           \
        पक्ष 3:                                            \
        {                                                  \
            Uint8 *B = (Uint8 *)(buf);                     \
            Pixel = GET_RGB24(B);                          \
        } भङ्ग;                                           \
                                                           \
        पक्ष 4:                                            \
            Pixel = *((Uint32 *)(buf));                    \
            भङ्ग;                                         \
                                                           \
        स्वभाव:                                           \
            Pixel = 0; /* stop gcc complaints */           \
            भङ्ग;                                         \
        }                                                  \
    } यावत् (0)

#यदि SDL_BYTEORDER == SDL_LIL_ENDIAN
#परिभाषय GET_RGB24_COMPONENT(buf, fmt, सरणम्) *((buf) + fmt->सरणम् / 8)
#अन्यथा
#परिभाषय GET_RGB24_COMPONENT(buf, fmt, सरणम्) *((buf) + 2 - fmt->सरणम् / 8)
#यदि_अन्तः
#परिभाषय DISEMBLE_RGB(buf, bpp, fmt, Pixel, r, g, b)    \
    कुरु {                                               \
        विकल्प (bpp) {                                 \
        पक्ष 1:                                        \
            Pixel = *((Uint8 *)(buf));                 \
            RGB_FROM_PIXEL(Pixel, fmt, r, g, b);       \
            भङ्ग;                                     \
                                                       \
        पक्ष 2:                                        \
            Pixel = *((Uint16 *)(buf));                \
            RGB_FROM_PIXEL(Pixel, fmt, r, g, b);       \
            भङ्ग;                                     \
                                                       \
        पक्ष 3:                                        \
        {                                              \
            Pixel = 0;                                 \
            r = GET_RGB24_COMPONENT(buf, fmt, Rshift); \
            g = GET_RGB24_COMPONENT(buf, fmt, Gshift); \
            b = GET_RGB24_COMPONENT(buf, fmt, Bshift); \
        } भङ्ग;                                       \
                                                       \
        पक्ष 4:                                        \
            Pixel = *((Uint32 *)(buf));                \
            RGB_FROM_PIXEL(Pixel, fmt, r, g, b);       \
            भङ्ग;                                     \
                                                       \
        स्वभाव:                                       \
            /* stop gcc complaints */                  \
            Pixel = 0;                                 \
            r = g = b = 0;                             \
            भङ्ग;                                     \
        }                                              \
    } यावत् (0)

// Assemble R-G-B values into a specified pixel format and store them
#परिभाषय PIXEL_FROM_RGB(Pixel, fmt, r, g, b)                 \
    {                                                       \
        Pixel = ((r >> (8 - fmt->Rbits)) << fmt->Rshift) |  \
                ((g >> (8 - fmt->Gbits)) << fmt->Gshift) |  \
                ((b >> (8 - fmt->Bbits)) << fmt->Bshift) |  \
                fmt->Amask;                                 \
    }
#परिभाषय RGB332_FROM_RGB(Pixel, r, g, b)                        \
    {                                                          \
        Pixel = (Uint8)(((r >> 5) << 5) | ((g >> 5) << 2) | (b >> 6)); \
    }
#परिभाषय RGB565_FROM_RGB(Pixel, r, g, b)                        \
    {                                                          \
        Pixel = (Uint16)(((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3)); \
    }
#परिभाषय RGB555_FROM_RGB(Pixel, r, g, b)                        \
    {                                                          \
        Pixel = (Uint16)(((r >> 3) << 10) | ((g >> 3) << 5) | (b >> 3)); \
    }
#परिभाषय XRGB8888_FROM_RGB(Pixel, r, g, b)   \
    {                                     \
        Pixel = (r << 16) | (g << 8) | b; \
    }
#परिभाषय ARGB8888_FROM_RGBA(Pixel, r, g, b, a)         \
    {                                                 \
        Pixel = (a << 24) | (r << 16) | (g << 8) | b; \
    }
#परिभाषय RGBA8888_FROM_RGBA(Pixel, r, g, b, a)         \
    {                                                 \
        Pixel = (r << 24) | (g << 16) | (b << 8) | a; \
    }
#परिभाषय ABGR8888_FROM_RGBA(Pixel, r, g, b, a)         \
    {                                                 \
        Pixel = (a << 24) | (b << 16) | (g << 8) | r; \
    }
#परिभाषय BGRA8888_FROM_RGBA(Pixel, r, g, b, a)         \
    {                                                 \
        Pixel = (b << 24) | (g << 16) | (r << 8) | a; \
    }
#परिभाषय ARGB2101010_FROM_RGBA(Pixel, r, g, b, a)       \
    {                                                  \
        r = r ? ((r << 2) | 0x3) : 0;                  \
        g = g ? ((g << 2) | 0x3) : 0;                  \
        b = b ? ((b << 2) | 0x3) : 0;                  \
        a = (a * 3) / 255;                             \
        Pixel = (a << 30) | (r << 20) | (g << 10) | b; \
    }
#परिभाषय ARGB2101010_FROM_RGBAFLOAT(Pixel, r, g, b, a) \
    {                                                 \
        r = SDL_clamp(r, 0.0f, 1.0f) * 1023.0f;       \
        g = SDL_clamp(g, 0.0f, 1.0f) * 1023.0f;       \
        b = SDL_clamp(b, 0.0f, 1.0f) * 1023.0f;       \
        a = SDL_clamp(a, 0.0f, 1.0f) * 3.0f;          \
        Pixel = (((Uint32)SDL_roundf(a)) << 30) |     \
                (((Uint32)SDL_roundf(r)) << 20) |     \
                (((Uint32)SDL_roundf(g)) << 10) |     \
                (Uint32)SDL_roundf(b);                \
    }
#परिभाषय ABGR2101010_FROM_RGBA(Pixel, r, g, b, a)       \
    {                                                  \
        r = r ? ((r << 2) | 0x3) : 0;                  \
        g = g ? ((g << 2) | 0x3) : 0;                  \
        b = b ? ((b << 2) | 0x3) : 0;                  \
        a = (a * 3) / 255;                             \
        Pixel = (a << 30) | (b << 20) | (g << 10) | r; \
    }
#परिभाषय ABGR2101010_FROM_RGBAFLOAT(Pixel, r, g, b, a) \
    {                                                 \
        r = SDL_clamp(r, 0.0f, 1.0f) * 1023.0f;       \
        g = SDL_clamp(g, 0.0f, 1.0f) * 1023.0f;       \
        b = SDL_clamp(b, 0.0f, 1.0f) * 1023.0f;       \
        a = SDL_clamp(a, 0.0f, 1.0f) * 3.0f;          \
        Pixel = (((Uint32)SDL_roundf(a)) << 30) |     \
                (((Uint32)SDL_roundf(b)) << 20) |     \
                (((Uint32)SDL_roundf(g)) << 10) |     \
                (Uint32)SDL_roundf(r);                \
    }
#परिभाषय ASSEMBLE_RGB(buf, bpp, fmt, r, g, b)           \
    {                                                  \
        विकल्प (bpp) {                                 \
        पक्ष 1:                                        \
        {                                              \
            Uint8 _pixel;                              \
                                                       \
            PIXEL_FROM_RGB(_pixel, fmt, r, g, b);      \
            *((Uint8 *)(buf)) = _pixel;                \
        } भङ्ग;                                       \
                                                       \
        पक्ष 2:                                        \
        {                                              \
            Uint16 _pixel;                             \
                                                       \
            PIXEL_FROM_RGB(_pixel, fmt, r, g, b);      \
            *((Uint16 *)(buf)) = _pixel;               \
        } भङ्ग;                                       \
                                                       \
        पक्ष 3:                                        \
        {                                              \
            GET_RGB24_COMPONENT(buf, fmt, Rshift) = r; \
            GET_RGB24_COMPONENT(buf, fmt, Gshift) = g; \
            GET_RGB24_COMPONENT(buf, fmt, Bshift) = b; \
        } भङ्ग;                                       \
                                                       \
        पक्ष 4:                                        \
        {                                              \
            Uint32 _pixel;                             \
                                                       \
            PIXEL_FROM_RGB(_pixel, fmt, r, g, b);      \
            *((Uint32 *)(buf)) = _pixel;               \
        } भङ्ग;                                       \
        }                                              \
    }

// FIXME: Should we rescale alpha into 0..255 here?
#परिभाषय RGBA_FROM_PIXEL(Pixel, fmt, r, g, b, a)                                 \
    {                                                                           \
        r = SDL_expand_byte[fmt->Rbits][((Pixel & fmt->Rmask) >> fmt->Rshift)]; \
        g = SDL_expand_byte[fmt->Gbits][((Pixel & fmt->Gmask) >> fmt->Gshift)]; \
        b = SDL_expand_byte[fmt->Bbits][((Pixel & fmt->Bmask) >> fmt->Bshift)]; \
        a = SDL_expand_byte[fmt->Abits][((Pixel & fmt->Amask) >> fmt->Ashift)]; \
    }
#परिभाषय RGBA_FROM_8888(Pixel, fmt, r, g, b, a)   \
    {                                            \
        r = (Pixel & fmt->Rmask) >> fmt->Rshift; \
        g = (Pixel & fmt->Gmask) >> fmt->Gshift; \
        b = (Pixel & fmt->Bmask) >> fmt->Bshift; \
        a = (Pixel & fmt->Amask) >> fmt->Ashift; \
    }
#परिभाषय RGBA_FROM_RGBA8888(Pixel, r, g, b, a) \
    {                                         \
        r = (Pixel >> 24);                    \
        g = ((Pixel >> 16) & 0xFF);           \
        b = ((Pixel >> 8) & 0xFF);            \
        a = (Pixel & 0xFF);                   \
    }
#परिभाषय RGBA_FROM_ARGB8888(Pixel, r, g, b, a) \
    {                                         \
        r = ((Pixel >> 16) & 0xFF);           \
        g = ((Pixel >> 8) & 0xFF);            \
        b = (Pixel & 0xFF);                   \
        a = (Pixel >> 24);                    \
    }
#परिभाषय RGBA_FROM_ABGR8888(Pixel, r, g, b, a) \
    {                                         \
        r = (Pixel & 0xFF);                   \
        g = ((Pixel >> 8) & 0xFF);            \
        b = ((Pixel >> 16) & 0xFF);           \
        a = (Pixel >> 24);                    \
    }
#परिभाषय RGBA_FROM_BGRA8888(Pixel, r, g, b, a) \
    {                                         \
        r = ((Pixel >> 8) & 0xFF);            \
        g = ((Pixel >> 16) & 0xFF);           \
        b = (Pixel >> 24);                    \
        a = (Pixel & 0xFF);                   \
    }
#परिभाषय RGBA_FROM_ARGB2101010(Pixel, r, g, b, a) \
    {                                            \
        r = ((Pixel >> 22) & 0xFF);              \
        g = ((Pixel >> 12) & 0xFF);              \
        b = ((Pixel >> 2) & 0xFF);               \
        a = SDL_expand_byte[2][(Pixel >> 30)];   \
    }
#परिभाषय RGBAFLOAT_FROM_ARGB2101010(Pixel, r, g, b, a)   \
    {                                                   \
        r = (भिन्न)((Pixel >> 20) & 0x3FF) / 1023.0f;   \
        g = (भिन्न)((Pixel >> 10) & 0x3FF) / 1023.0f;   \
        b = (भिन्न)((Pixel >> 0) & 0x3FF) / 1023.0f;    \
        a = (भिन्न)(Pixel >> 30) / 3.0f;                \
    }
#परिभाषय RGBA_FROM_ABGR2101010(Pixel, r, g, b, a) \
    {                                            \
        r = ((Pixel >> 2) & 0xFF);               \
        g = ((Pixel >> 12) & 0xFF);              \
        b = ((Pixel >> 22) & 0xFF);              \
        a = SDL_expand_byte[2][(Pixel >> 30)];   \
    }
#परिभाषय RGBAFLOAT_FROM_ABGR2101010(Pixel, r, g, b, a)   \
    {                                                   \
        r = (भिन्न)((Pixel >> 0) & 0x3FF) / 1023.0f;    \
        g = (भिन्न)((Pixel >> 10) & 0x3FF) / 1023.0f;   \
        b = (भिन्न)((Pixel >> 20) & 0x3FF) / 1023.0f;   \
        a = (भिन्न)(Pixel >> 30) / 3.0f;                \
    }
#परिभाषय DISEMBLE_RGBA(buf, bpp, fmt, Pixel, r, g, b, a) \
    कुरु {                                                \
        विकल्प (bpp) {                                  \
        पक्ष 1:                                         \
            Pixel = *((Uint8 *)(buf));                  \
            RGBA_FROM_PIXEL(Pixel, fmt, r, g, b, a);    \
            भङ्ग;                                      \
                                                        \
        पक्ष 2:                                         \
            Pixel = *((Uint16 *)(buf));                 \
            RGBA_FROM_PIXEL(Pixel, fmt, r, g, b, a);    \
            भङ्ग;                                      \
                                                        \
        पक्ष 3:                                         \
        {                                               \
            Pixel = 0;                                  \
            r = GET_RGB24_COMPONENT(buf, fmt, Rshift);  \
            g = GET_RGB24_COMPONENT(buf, fmt, Gshift);  \
            b = GET_RGB24_COMPONENT(buf, fmt, Bshift);  \
            a = 0xFF;                                   \
        } भङ्ग;                                        \
                                                        \
        पक्ष 4:                                         \
            Pixel = *((Uint32 *)(buf));                 \
            RGBA_FROM_PIXEL(Pixel, fmt, r, g, b, a);    \
            भङ्ग;                                      \
                                                        \
        स्वभाव:                                        \
            /* stop gcc complaints */                   \
            Pixel = 0;                                  \
            r = g = b = a = 0;                          \
            भङ्ग;                                      \
        }                                               \
    } यावत् (0)

// FIXME: this isn't correct, especially for Alpha (maximum != 255)
#परिभाषय PIXEL_FROM_RGBA(Pixel, fmt, r, g, b, a)             \
    {                                                       \
        Pixel = ((r >> (8 - fmt->Rbits)) << fmt->Rshift) |  \
                ((g >> (8 - fmt->Gbits)) << fmt->Gshift) |  \
                ((b >> (8 - fmt->Bbits)) << fmt->Bshift) |  \
                ((a >> (8 - fmt->Abits)) << fmt->Ashift);   \
    }
#परिभाषय ASSEMBLE_RGBA(buf, bpp, fmt, r, g, b, a)       \
    {                                                  \
        विकल्प (bpp) {                                 \
        पक्ष 1:                                        \
        {                                              \
            Uint8 _pixel;                              \
                                                       \
            PIXEL_FROM_RGBA(_pixel, fmt, r, g, b, a);  \
            *((Uint8 *)(buf)) = _pixel;                \
        } भङ्ग;                                       \
                                                       \
        पक्ष 2:                                        \
        {                                              \
            Uint16 _pixel;                             \
                                                       \
            PIXEL_FROM_RGBA(_pixel, fmt, r, g, b, a);  \
            *((Uint16 *)(buf)) = _pixel;               \
        } भङ्ग;                                       \
                                                       \
        पक्ष 3:                                        \
        {                                              \
            GET_RGB24_COMPONENT(buf, fmt, Rshift) = r; \
            GET_RGB24_COMPONENT(buf, fmt, Gshift) = g; \
            GET_RGB24_COMPONENT(buf, fmt, Bshift) = b; \
        } भङ्ग;                                       \
                                                       \
        पक्ष 4:                                        \
        {                                              \
            Uint32 _pixel;                             \
                                                       \
            PIXEL_FROM_RGBA(_pixel, fmt, r, g, b, a);  \
            *((Uint32 *)(buf)) = _pixel;               \
        } भङ्ग;                                       \
        }                                              \
    }

// Convert any 32-bit 4-bpp pixel to ARGB format
#परिभाषय PIXEL_गन्तव्यम्_ARGB_PIXEL(src, srcfmt, dst)         \
    कुरु {                                              \
        Uint8 a, r, g, b;                         \
        RGBA_FROM_PIXEL(src, srcfmt, r, g, b, a); \
        dst = a << 24 | r << 16 | g << 8 | b;     \
    } यावत् (0)
// Blend a single color channel or alpha value
/* dC = ((sC * sA) + (dC * (255 - sA))) / 255 */
#परिभाषय ALPHA_BLEND_CHANNEL(sC, dC, sA)                  \
    कुरु {                                                 \
        Uint16 x;                                        \
        x = ((sC - dC) * sA) + ((dC << 8) - dC);         \
        x += 0x1U;                                       \
        x += x >> 8;                                     \
        dC = x >> 8;                                     \
    } यावत् (0)
// Perform a division by 255 after a multiplication of two 8-bit color channels
/* out = (sC * dC) / 255 */
#परिभाषय MULT_DIV_255(sC, dC, बहिर्गमनम्) \
    कुरु {                          \
        Uint16 x = sC * dC;       \
        x += 0x1U;                \
        x += x >> 8;              \
        बहिर्गमनम् = x >> 8;             \
    } यावत् (0)
// Blend the RGB values of two pixels with an alpha value
#परिभाषय ALPHA_BLEND_RGB(sR, sG, sB, A, dR, dG, dB)            \
    कुरु {                                                      \
        ALPHA_BLEND_CHANNEL(sR, dR, A);                       \
        ALPHA_BLEND_CHANNEL(sG, dG, A);                       \
        ALPHA_BLEND_CHANNEL(sB, dB, A);                       \
    } यावत् (0)

// Blend two 8888 pixels with the same format
/* Calculates dst = ((src * factor) + (dst * (255 - factor))) / 255 */
// FIXME: SDL_SIZE_MAX might not be an integer literal
#यदि defined(SIZE_MAX) && (SIZE_MAX == 0xffffffffffffffff)
#परिभाषय गुणकः_BLEND_8888(src, dst, गुणकः)                        \
    कुरु {                                                           \
        Uint64 src64 = src;                                        \
        src64 = (src64 | (src64 << 24)) & 0x00FF00FF00FF00FF;      \
                                                                   \
        Uint64 dst64 = dst;                                        \
        dst64 = (dst64 | (dst64 << 24)) & 0x00FF00FF00FF00FF;      \
                                                                   \
        dst64 = ((src64 - dst64) * गुणकः) + (dst64 << 8) - dst64; \
        dst64 += 0x0001000100010001;                               \
        dst64 += (dst64 >> 8) & 0x00FF00FF00FF00FF;                \
        dst64 &= 0xFF00FF00FF00FF00;                               \
                                                                   \
        dst = (Uint32)((dst64 >> 8) | (dst64 >> 32));              \
    } यावत् (0)
#अन्यथा
#परिभाषय गुणकः_BLEND_8888(src, dst, गुणकः)                               \
    कुरु {                                                                  \
        Uint32 src02 = src & 0x00FF00FF;                                  \
        Uint32 dst02 = dst & 0x00FF00FF;                                  \
                                                                          \
        Uint32 src13 = (src >> 8) & 0x00FF00FF;                           \
        Uint32 dst13 = (dst >> 8) & 0x00FF00FF;                           \
                                                                          \
        Uint32 res02 = ((src02 - dst02) * गुणकः) + (dst02 << 8) - dst02; \
        res02 += 0x00010001;                                              \
        res02 += (res02 >> 8) & 0x00FF00FF;                               \
        res02 = (res02 >> 8) & 0x00FF00FF;                                \
                                                                          \
        Uint32 res13 = ((src13 - dst13) * गुणकः) + (dst13 << 8) - dst13; \
        res13 += 0x00010001;                                              \
        res13 += (res13 >> 8) & 0x00FF00FF;                               \
        res13 &= 0xFF00FF00;                                              \
        dst = res02 | res13;                                              \
    } यावत् (0)
#यदि_अन्तः

// Alpha blend two 8888 pixels with the same formats.
#परिभाषय ALPHA_BLEND_8888(src, dst, fmt)            \
    कुरु {                                           \
        Uint32 srcA = (src >> fmt->Ashift) & 0xFF; \
        Uint32 tmp = src | fmt->Amask;             \
        गुणकः_BLEND_8888(tmp, dst, srcA);         \
    } यावत् (0)

// Alpha blend two 8888 pixels with differing formats.
#परिभाषय ALPHA_BLEND_SWIZZLE_8888(src, dst, srcfmt, dstfmt)                  \
    कुरु {                                                                    \
        Uint32 srcA = (src >> srcfmt->Ashift) & 0xFF;                       \
        Uint32 tmp = (((src >> srcfmt->Rshift) & 0xFF) << dstfmt->Rshift) | \
                     (((src >> srcfmt->Gshift) & 0xFF) << dstfmt->Gshift) | \
                     (((src >> srcfmt->Bshift) & 0xFF) << dstfmt->Bshift) | \
                     dstfmt->Amask;                                         \
        गुणकः_BLEND_8888(tmp, dst, srcA);                                  \
    } यावत् (0)
// Blend the RGBA values of two pixels
#परिभाषय ALPHA_BLEND_RGBA(sR, sG, sB, sA, dR, dG, dB, dA) \
    कुरु {                                                 \
        ALPHA_BLEND_CHANNEL(sR, dR, sA);                 \
        ALPHA_BLEND_CHANNEL(sG, dG, sA);                 \
        ALPHA_BLEND_CHANNEL(sB, dB, sA);                 \
        ALPHA_BLEND_CHANNEL(255, dA, sA);                \
    } यावत् (0)

// This is a very useful loop for optimizing blitters
#यदि defined(_MSC_VER) && (_MSC_VER == 1300)
// There's a bug in the Visual C++ 7 optimizer when compiling this code
#अन्यथा
#परिभाषय USE_DUFFS_LOOP
#यदि_अन्तः

#परिभाषय DUFFS_LOOP1(pixel_copy_increment, विस्तारः) \
    {                                            \
        पूर्णाङ्क n;                                   \
        प्रति (n = विस्तारः; n > 0; --n) {            \
            pixel_copy_increment;                \
        }                                        \
    }

#यदि_परिभाषितम् USE_DUFFS_LOOP

// 8-times unrolled loop
#परिभाषय DUFFS_LOOP8(pixel_copy_increment, विस्तारः) \
    {                                            \
        पूर्णाङ्क n = (विस्तारः + 7) / 8;                 \
        विकल्प (विस्तारः & 7) {                     \
        पक्ष 0:                                  \
            कुरु {                                 \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            पक्ष 7:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            पक्ष 6:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            पक्ष 5:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            पक्ष 4:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            पक्ष 3:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            पक्ष 2:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            पक्ष 1:                              \
                pixel_copy_increment;            \
            } यावत् (--n > 0);                   \
        }                                        \
    }

// 4-times unrolled loop
#परिभाषय DUFFS_LOOP4(pixel_copy_increment, विस्तारः) \
    {                                            \
        पूर्णाङ्क n = (विस्तारः + 3) / 4;                 \
        विकल्प (विस्तारः & 3) {                     \
        पक्ष 0:                                  \
            कुरु {                                 \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            पक्ष 3:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            पक्ष 2:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            पक्ष 1:                              \
                pixel_copy_increment;            \
            } यावत् (--n > 0);                   \
        }                                        \
    }

// 2-times unrolled loop
#परिभाषय DUFFS_LOOP2(pixel_copy_increment, विस्तारः) \
    {                                            \
        पूर्णाङ्क n = (विस्तारः + 1) / 2;                 \
        विकल्प (विस्तारः & 1) {                     \
        पक्ष 0:                                  \
            कुरु {                                 \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            पक्ष 1:                              \
                pixel_copy_increment;            \
            } यावत् (--n > 0);                   \
        }                                        \
    }

// Use the 4-times version of the loop by default
#परिभाषय DUFFS_LOOP(pixel_copy_increment, विस्तारः) \
    DUFFS_LOOP4(pixel_copy_increment, विस्तारः)
// Use the 8-times version of the loop for simple routines
#परिभाषय DUFFS_LOOP_TRIVIAL(pixel_copy_increment, विस्तारः) \
    DUFFS_LOOP8(pixel_copy_increment, विस्तारः)

// Special version of Duff's device for even more optimization
#परिभाषय DUFFS_LOOP_124(pixel_copy_increment1,        \
                       pixel_copy_increment2,        \
                       pixel_copy_increment4, विस्तारः) \
    {                                                \
        पूर्णाङ्क n = विस्तारः;                               \
        यदि (n & 1) {                                 \
            pixel_copy_increment1;                   \
            n -= 1;                                  \
        }                                            \
        यदि (n & 2) {                                 \
            pixel_copy_increment2;                   \
            n -= 2;                                  \
        }                                            \
        यदि (n & 4) {                                 \
            pixel_copy_increment4;                   \
            n -= 4;                                  \
        }                                            \
        यदि (n) {                                     \
            n /= 8;                                  \
            कुरु {                                     \
                pixel_copy_increment4;               \
                pixel_copy_increment4;               \
            } यावत् (--n > 0);                       \
        }                                            \
    }

#अन्यथा

// Don't use Duff's device to unroll loops
#परिभाषय DUFFS_LOOP(pixel_copy_increment, विस्तारः) \
    DUFFS_LOOP1(pixel_copy_increment, विस्तारः)
#परिभाषय DUFFS_LOOP_TRIVIAL(pixel_copy_increment, विस्तारः) \
    DUFFS_LOOP1(pixel_copy_increment, विस्तारः)
#परिभाषय DUFFS_LOOP8(pixel_copy_increment, विस्तारः) \
    DUFFS_LOOP1(pixel_copy_increment, विस्तारः)
#परिभाषय DUFFS_LOOP4(pixel_copy_increment, विस्तारः) \
    DUFFS_LOOP1(pixel_copy_increment, विस्तारः)
#परिभाषय DUFFS_LOOP2(pixel_copy_increment, विस्तारः) \
    DUFFS_LOOP1(pixel_copy_increment, विस्तारः)
#परिभाषय DUFFS_LOOP_124(pixel_copy_increment1,        \
                       pixel_copy_increment2,        \
                       pixel_copy_increment4, विस्तारः) \
    DUFFS_LOOP1(pixel_copy_increment1, विस्तारः)

#यदि_अन्तः // USE_DUFFS_LOOP

#यदि defined(_MSC_VER) && (_MSC_VER >= 600)
#निर्देशः warning(disable : 4244) // '=': conversion from 'X' to 'Y', possible loss of data
#यदि_अन्तः

#यदि_अन्तः // SDL_blit_h_
