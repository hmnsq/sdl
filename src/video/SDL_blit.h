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

#अगर_अघोषित SDL_blit_h_
#घोषणा SDL_blit_h_

// Table to do pixel byte expansion
बाह्य स्थिर Uint8 *SDL_expand_byte[9];
बाह्य स्थिर Uint16 SDL_expand_byte_10[];

// SDL blit copy flags
#घोषणा SDL_COPY_MODULATE_COLOR         0x00000001
#घोषणा SDL_COPY_MODULATE_ALPHA         0x00000002
#घोषणा SDL_COPY_MODULATE_MASK		(SDL_COPY_MODULATE_COLOR | SDL_COPY_MODULATE_ALPHA)
#घोषणा SDL_COPY_BLEND                  0x00000010
#घोषणा SDL_COPY_BLEND_PREMULTIPLIED    0x00000020
#घोषणा SDL_COPY_ADD                    0x00000040
#घोषणा SDL_COPY_ADD_PREMULTIPLIED      0x00000080
#घोषणा SDL_COPY_MOD                    0x00000100
#घोषणा SDL_COPY_MUL                    0x00000200
#घोषणा SDL_COPY_BLEND_MASK		(SDL_COPY_BLEND | SDL_COPY_BLEND_PREMULTIPLIED | SDL_COPY_ADD | SDL_COPY_ADD_PREMULTIPLIED | SDL_COPY_MOD | SDL_COPY_MUL)
#घोषणा SDL_COPY_COLORKEY               0x00000400
#घोषणा SDL_COPY_NEAREST                0x00000800
#घोषणा SDL_COPY_RLE_DESIRED            0x00001000
#घोषणा SDL_COPY_RLE_COLORKEY           0x00002000
#घोषणा SDL_COPY_RLE_ALPHAKEY           0x00004000
#घोषणा SDL_COPY_RLE_MASK               (SDL_COPY_RLE_DESIRED | SDL_COPY_RLE_COLORKEY | SDL_COPY_RLE_ALPHAKEY)

// SDL blit CPU flags
#घोषणा SDL_CPU_ANY                0x00000000
#घोषणा SDL_CPU_MMX                0x00000001
#घोषणा SDL_CPU_SSE                0x00000002
#घोषणा SDL_CPU_SSE2               0x00000004
#घोषणा SDL_CPU_ALTIVEC_PREFETCH   0x00000008
#घोषणा SDL_CPU_ALTIVEC_NOPREFETCH 0x00000010

प्रकार काष्ठा
{
    SDL_Surface *src_surface;
    Uint8 *src;
    पूर्णांक src_w, src_h;
    पूर्णांक src_pitch;
    पूर्णांक src_skip;
    पूर्णांक leading_skip;
    SDL_Surface *dst_surface;
    Uint8 *dst;
    पूर्णांक dst_w, dst_h;
    पूर्णांक dst_pitch;
    पूर्णांक dst_skip;
    स्थिर SDL_PixelFormatDetails *src_fmt;
    स्थिर SDL_Palette *src_pal;
    स्थिर SDL_PixelFormatDetails *dst_fmt;
    स्थिर SDL_Palette *dst_pal;
    Uint8 *table;
    SDL_HashTable *palette_map;
    पूर्णांक flags;
    Uint32 colorkey;
    Uint8 r, g, b, a;
} SDL_BlitInfo;

प्रकार व्योम (*SDL_BlitFunc)(SDL_BlitInfo *info);

प्रकार काष्ठा
{
    SDL_PixelFormat src_format;
    SDL_PixelFormat dst_format;
    पूर्णांक flags;
    SDL_BlitFunc func;
} SDL_BlitFuncEntry;

प्रकार bool (SDLCALL *SDL_Blit) (काष्ठा SDL_Surface *src, स्थिर SDL_Rect *srcrect, काष्ठा SDL_Surface *dst, स्थिर SDL_Rect *dstrect);

// Blit mapping definition
प्रकार काष्ठा SDL_BlitMap
{
    पूर्णांक identity;
    SDL_Blit blit;
    व्योम *तथ्य;
    SDL_BlitInfo info;

    /* the version count matches the destination; mismatch indicates
       an invalid mapping */
    Uint32 dst_palette_version;
    Uint32 src_palette_version;
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

#अगर_घोषित __GNUC__
#घोषणा DECLARE_ALIGNED(t, v, a) t __attribute__((aligned(a))) v
#या_अगर defined(_MSC_VER)
#घोषणा DECLARE_ALIGNED(t, v, a) __declspec(align(a)) t v
#अन्यथा
#घोषणा DECLARE_ALIGNED(t, v, a) t v
#पूर्ण_अगर

// Load pixel of the specified format from a buffer and get its R-G-B values
#घोषणा RGB_FROM_PIXEL(Pixel, fmt, r, g, b)                                     \
    {                                                                           \
        r = SDL_expand_byte[fmt->Rbits][((Pixel & fmt->Rmask) >> fmt->Rshift)]; \
        g = SDL_expand_byte[fmt->Gbits][((Pixel & fmt->Gmask) >> fmt->Gshift)]; \
        b = SDL_expand_byte[fmt->Bbits][((Pixel & fmt->Bmask) >> fmt->Bshift)]; \
    }
#घोषणा RGB_FROM_RGB565(Pixel, r, g, b)                   \
    {                                                     \
        r = SDL_expand_byte[5][((Pixel & 0xF800) >> 11)]; \
        g = SDL_expand_byte[6][((Pixel & 0x07E0) >> 5)];  \
        b = SDL_expand_byte[5][(Pixel & 0x001F)];         \
    }
#घोषणा RGB_FROM_RGB555(Pixel, r, g, b)                   \
    {                                                     \
        r = SDL_expand_byte[5][((Pixel & 0x7C00) >> 10)]; \
        g = SDL_expand_byte[5][((Pixel & 0x03E0) >> 5)];  \
        b = SDL_expand_byte[5][(Pixel & 0x001F)];         \
    }
#घोषणा RGB_FROM_XRGB8888(Pixel, r, g, b) \
    {                                   \
        r = ((Pixel & 0xFF0000) >> 16); \
        g = ((Pixel & 0xFF00) >> 8);    \
        b = (Pixel & 0xFF);             \
    }
#अगर SDL_BYTEORDER == SDL_LIL_ENDIAN
#घोषणा GET_RGB24(B) (B[2] << 16) | (B[1] << 8) | B[0]
#अन्यथा
#घोषणा GET_RGB24(B) (B[0] << 16) | (B[1] << 8) | B[2]
#पूर्ण_अगर
#घोषणा RETRIEVE_RGB_PIXEL(buf, bpp, Pixel)                \
    करो {                                                   \
        चयन (bpp) {                                     \
        हाल 1:                                            \
            Pixel = *((Uint8 *)(buf));                     \
            अवरोध;                                         \
                                                           \
        हाल 2:                                            \
            Pixel = *((Uint16 *)(buf));                    \
            अवरोध;                                         \
                                                           \
        हाल 3:                                            \
        {                                                  \
            Uint8 *B = (Uint8 *)(buf);                     \
            Pixel = GET_RGB24(B);                          \
        } अवरोध;                                           \
                                                           \
        हाल 4:                                            \
            Pixel = *((Uint32 *)(buf));                    \
            अवरोध;                                         \
                                                           \
        शेष:                                           \
            Pixel = 0; /* stop gcc complaints */           \
            अवरोध;                                         \
        }                                                  \
    } जबतक (0)

#अगर SDL_BYTEORDER == SDL_LIL_ENDIAN
#घोषणा GET_RGB24_COMPONENT(buf, fmt, shift) *((buf) + fmt->shift / 8)
#अन्यथा
#घोषणा GET_RGB24_COMPONENT(buf, fmt, shift) *((buf) + 2 - fmt->shift / 8)
#पूर्ण_अगर
#घोषणा DISEMBLE_RGB(buf, bpp, fmt, Pixel, r, g, b)    \
    करो {                                               \
        चयन (bpp) {                                 \
        हाल 1:                                        \
            Pixel = *((Uint8 *)(buf));                 \
            RGB_FROM_PIXEL(Pixel, fmt, r, g, b);       \
            अवरोध;                                     \
                                                       \
        हाल 2:                                        \
            Pixel = *((Uint16 *)(buf));                \
            RGB_FROM_PIXEL(Pixel, fmt, r, g, b);       \
            अवरोध;                                     \
                                                       \
        हाल 3:                                        \
        {                                              \
            Pixel = 0;                                 \
            r = GET_RGB24_COMPONENT(buf, fmt, Rshift); \
            g = GET_RGB24_COMPONENT(buf, fmt, Gshift); \
            b = GET_RGB24_COMPONENT(buf, fmt, Bshift); \
        } अवरोध;                                       \
                                                       \
        हाल 4:                                        \
            Pixel = *((Uint32 *)(buf));                \
            RGB_FROM_PIXEL(Pixel, fmt, r, g, b);       \
            अवरोध;                                     \
                                                       \
        शेष:                                       \
            /* stop gcc complaints */                  \
            Pixel = 0;                                 \
            r = g = b = 0;                             \
            अवरोध;                                     \
        }                                              \
    } जबतक (0)

// Assemble R-G-B values into a specified pixel format and store them
#घोषणा PIXEL_FROM_RGB(Pixel, fmt, r, g, b)                 \
    {                                                       \
        Pixel = ((r >> (8 - fmt->Rbits)) << fmt->Rshift) |  \
                ((g >> (8 - fmt->Gbits)) << fmt->Gshift) |  \
                ((b >> (8 - fmt->Bbits)) << fmt->Bshift) |  \
                fmt->Amask;                                 \
    }
#घोषणा RGB332_FROM_RGB(Pixel, r, g, b)                        \
    {                                                          \
        Pixel = (Uint8)(((r >> 5) << 5) | ((g >> 5) << 2) | (b >> 6)); \
    }
#घोषणा RGB565_FROM_RGB(Pixel, r, g, b)                        \
    {                                                          \
        Pixel = (Uint16)(((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3)); \
    }
#घोषणा RGB555_FROM_RGB(Pixel, r, g, b)                        \
    {                                                          \
        Pixel = (Uint16)(((r >> 3) << 10) | ((g >> 3) << 5) | (b >> 3)); \
    }
#घोषणा XRGB8888_FROM_RGB(Pixel, r, g, b)   \
    {                                     \
        Pixel = (r << 16) | (g << 8) | b; \
    }
#घोषणा ARGB8888_FROM_RGBA(Pixel, r, g, b, a)         \
    {                                                 \
        Pixel = (a << 24) | (r << 16) | (g << 8) | b; \
    }
#घोषणा RGBA8888_FROM_RGBA(Pixel, r, g, b, a)         \
    {                                                 \
        Pixel = (r << 24) | (g << 16) | (b << 8) | a; \
    }
#घोषणा ABGR8888_FROM_RGBA(Pixel, r, g, b, a)         \
    {                                                 \
        Pixel = (a << 24) | (b << 16) | (g << 8) | r; \
    }
#घोषणा BGRA8888_FROM_RGBA(Pixel, r, g, b, a)         \
    {                                                 \
        Pixel = (b << 24) | (g << 16) | (r << 8) | a; \
    }
#घोषणा ARGB2101010_FROM_RGBA(Pixel, r, g, b, a)       \
    {                                                  \
        r = r ? ((r << 2) | 0x3) : 0;                  \
        g = g ? ((g << 2) | 0x3) : 0;                  \
        b = b ? ((b << 2) | 0x3) : 0;                  \
        a = (a * 3) / 255;                             \
        Pixel = (a << 30) | (r << 20) | (g << 10) | b; \
    }
#घोषणा ARGB2101010_FROM_RGBAFLOAT(Pixel, r, g, b, a) \
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
#घोषणा ABGR2101010_FROM_RGBA(Pixel, r, g, b, a)       \
    {                                                  \
        r = r ? ((r << 2) | 0x3) : 0;                  \
        g = g ? ((g << 2) | 0x3) : 0;                  \
        b = b ? ((b << 2) | 0x3) : 0;                  \
        a = (a * 3) / 255;                             \
        Pixel = (a << 30) | (b << 20) | (g << 10) | r; \
    }
#घोषणा ABGR2101010_FROM_RGBAFLOAT(Pixel, r, g, b, a) \
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
#घोषणा ASSEMBLE_RGB(buf, bpp, fmt, r, g, b)           \
    {                                                  \
        चयन (bpp) {                                 \
        हाल 1:                                        \
        {                                              \
            Uint8 _pixel;                              \
                                                       \
            PIXEL_FROM_RGB(_pixel, fmt, r, g, b);      \
            *((Uint8 *)(buf)) = _pixel;                \
        } अवरोध;                                       \
                                                       \
        हाल 2:                                        \
        {                                              \
            Uint16 _pixel;                             \
                                                       \
            PIXEL_FROM_RGB(_pixel, fmt, r, g, b);      \
            *((Uint16 *)(buf)) = _pixel;               \
        } अवरोध;                                       \
                                                       \
        हाल 3:                                        \
        {                                              \
            GET_RGB24_COMPONENT(buf, fmt, Rshift) = r; \
            GET_RGB24_COMPONENT(buf, fmt, Gshift) = g; \
            GET_RGB24_COMPONENT(buf, fmt, Bshift) = b; \
        } अवरोध;                                       \
                                                       \
        हाल 4:                                        \
        {                                              \
            Uint32 _pixel;                             \
                                                       \
            PIXEL_FROM_RGB(_pixel, fmt, r, g, b);      \
            *((Uint32 *)(buf)) = _pixel;               \
        } अवरोध;                                       \
        }                                              \
    }

// FIXME: Should we rescale alpha into 0..255 here?
#घोषणा RGBA_FROM_PIXEL(Pixel, fmt, r, g, b, a)                                 \
    {                                                                           \
        r = SDL_expand_byte[fmt->Rbits][((Pixel & fmt->Rmask) >> fmt->Rshift)]; \
        g = SDL_expand_byte[fmt->Gbits][((Pixel & fmt->Gmask) >> fmt->Gshift)]; \
        b = SDL_expand_byte[fmt->Bbits][((Pixel & fmt->Bmask) >> fmt->Bshift)]; \
        a = SDL_expand_byte[fmt->Abits][((Pixel & fmt->Amask) >> fmt->Ashift)]; \
    }
#घोषणा RGBA_FROM_8888(Pixel, fmt, r, g, b, a)   \
    {                                            \
        r = (Pixel & fmt->Rmask) >> fmt->Rshift; \
        g = (Pixel & fmt->Gmask) >> fmt->Gshift; \
        b = (Pixel & fmt->Bmask) >> fmt->Bshift; \
        a = (Pixel & fmt->Amask) >> fmt->Ashift; \
    }
#घोषणा RGBA_FROM_RGBA8888(Pixel, r, g, b, a) \
    {                                         \
        r = (Pixel >> 24);                    \
        g = ((Pixel >> 16) & 0xFF);           \
        b = ((Pixel >> 8) & 0xFF);            \
        a = (Pixel & 0xFF);                   \
    }
#घोषणा RGBA_FROM_ARGB8888(Pixel, r, g, b, a) \
    {                                         \
        r = ((Pixel >> 16) & 0xFF);           \
        g = ((Pixel >> 8) & 0xFF);            \
        b = (Pixel & 0xFF);                   \
        a = (Pixel >> 24);                    \
    }
#घोषणा RGBA_FROM_ABGR8888(Pixel, r, g, b, a) \
    {                                         \
        r = (Pixel & 0xFF);                   \
        g = ((Pixel >> 8) & 0xFF);            \
        b = ((Pixel >> 16) & 0xFF);           \
        a = (Pixel >> 24);                    \
    }
#घोषणा RGBA_FROM_BGRA8888(Pixel, r, g, b, a) \
    {                                         \
        r = ((Pixel >> 8) & 0xFF);            \
        g = ((Pixel >> 16) & 0xFF);           \
        b = (Pixel >> 24);                    \
        a = (Pixel & 0xFF);                   \
    }
#घोषणा RGBA_FROM_ARGB2101010(Pixel, r, g, b, a) \
    {                                            \
        r = ((Pixel >> 22) & 0xFF);              \
        g = ((Pixel >> 12) & 0xFF);              \
        b = ((Pixel >> 2) & 0xFF);               \
        a = SDL_expand_byte[2][(Pixel >> 30)];   \
    }
#घोषणा RGBAFLOAT_FROM_ARGB2101010(Pixel, r, g, b, a)   \
    {                                                   \
        r = (भग्न)((Pixel >> 20) & 0x3FF) / 1023.0f;   \
        g = (भग्न)((Pixel >> 10) & 0x3FF) / 1023.0f;   \
        b = (भग्न)((Pixel >> 0) & 0x3FF) / 1023.0f;    \
        a = (भग्न)(Pixel >> 30) / 3.0f;                \
    }
#घोषणा RGBA_FROM_ABGR2101010(Pixel, r, g, b, a) \
    {                                            \
        r = ((Pixel >> 2) & 0xFF);               \
        g = ((Pixel >> 12) & 0xFF);              \
        b = ((Pixel >> 22) & 0xFF);              \
        a = SDL_expand_byte[2][(Pixel >> 30)];   \
    }
#घोषणा RGBAFLOAT_FROM_ABGR2101010(Pixel, r, g, b, a)   \
    {                                                   \
        r = (भग्न)((Pixel >> 0) & 0x3FF) / 1023.0f;    \
        g = (भग्न)((Pixel >> 10) & 0x3FF) / 1023.0f;   \
        b = (भग्न)((Pixel >> 20) & 0x3FF) / 1023.0f;   \
        a = (भग्न)(Pixel >> 30) / 3.0f;                \
    }
#घोषणा DISEMBLE_RGBA(buf, bpp, fmt, Pixel, r, g, b, a) \
    करो {                                                \
        चयन (bpp) {                                  \
        हाल 1:                                         \
            Pixel = *((Uint8 *)(buf));                  \
            RGBA_FROM_PIXEL(Pixel, fmt, r, g, b, a);    \
            अवरोध;                                      \
                                                        \
        हाल 2:                                         \
            Pixel = *((Uint16 *)(buf));                 \
            RGBA_FROM_PIXEL(Pixel, fmt, r, g, b, a);    \
            अवरोध;                                      \
                                                        \
        हाल 3:                                         \
        {                                               \
            Pixel = 0;                                  \
            r = GET_RGB24_COMPONENT(buf, fmt, Rshift);  \
            g = GET_RGB24_COMPONENT(buf, fmt, Gshift);  \
            b = GET_RGB24_COMPONENT(buf, fmt, Bshift);  \
            a = 0xFF;                                   \
        } अवरोध;                                        \
                                                        \
        हाल 4:                                         \
            Pixel = *((Uint32 *)(buf));                 \
            RGBA_FROM_PIXEL(Pixel, fmt, r, g, b, a);    \
            अवरोध;                                      \
                                                        \
        शेष:                                        \
            /* stop gcc complaints */                   \
            Pixel = 0;                                  \
            r = g = b = a = 0;                          \
            अवरोध;                                      \
        }                                               \
    } जबतक (0)

// FIXME: this isn't correct, especially for Alpha (maximum != 255)
#घोषणा PIXEL_FROM_RGBA(Pixel, fmt, r, g, b, a)             \
    {                                                       \
        Pixel = ((r >> (8 - fmt->Rbits)) << fmt->Rshift) |  \
                ((g >> (8 - fmt->Gbits)) << fmt->Gshift) |  \
                ((b >> (8 - fmt->Bbits)) << fmt->Bshift) |  \
                ((a >> (8 - fmt->Abits)) << fmt->Ashift);   \
    }
#घोषणा ASSEMBLE_RGBA(buf, bpp, fmt, r, g, b, a)       \
    {                                                  \
        चयन (bpp) {                                 \
        हाल 1:                                        \
        {                                              \
            Uint8 _pixel;                              \
                                                       \
            PIXEL_FROM_RGBA(_pixel, fmt, r, g, b, a);  \
            *((Uint8 *)(buf)) = _pixel;                \
        } अवरोध;                                       \
                                                       \
        हाल 2:                                        \
        {                                              \
            Uint16 _pixel;                             \
                                                       \
            PIXEL_FROM_RGBA(_pixel, fmt, r, g, b, a);  \
            *((Uint16 *)(buf)) = _pixel;               \
        } अवरोध;                                       \
                                                       \
        हाल 3:                                        \
        {                                              \
            GET_RGB24_COMPONENT(buf, fmt, Rshift) = r; \
            GET_RGB24_COMPONENT(buf, fmt, Gshift) = g; \
            GET_RGB24_COMPONENT(buf, fmt, Bshift) = b; \
        } अवरोध;                                       \
                                                       \
        हाल 4:                                        \
        {                                              \
            Uint32 _pixel;                             \
                                                       \
            PIXEL_FROM_RGBA(_pixel, fmt, r, g, b, a);  \
            *((Uint32 *)(buf)) = _pixel;               \
        } अवरोध;                                       \
        }                                              \
    }

// Convert any 32-bit 4-bpp pixel to ARGB format
#घोषणा PIXEL_TO_ARGB_PIXEL(src, srcfmt, dst)         \
    करो {                                              \
        Uint8 a, r, g, b;                         \
        RGBA_FROM_PIXEL(src, srcfmt, r, g, b, a); \
        dst = a << 24 | r << 16 | g << 8 | b;     \
    } जबतक (0)
// Blend a single color channel or alpha value
/* dC = ((sC * sA) + (dC * (255 - sA))) / 255 */
#घोषणा ALPHA_BLEND_CHANNEL(sC, dC, sA)                  \
    करो {                                                 \
        Uint16 x;                                        \
        x = ((sC - dC) * sA) + ((dC << 8) - dC);         \
        x += 0x1U;                                       \
        x += x >> 8;                                     \
        dC = x >> 8;                                     \
    } जबतक (0)
// Perform a division by 255 after a multiplication of two 8-bit color channels
/* out = (sC * dC) / 255 */
#घोषणा MULT_DIV_255(sC, dC, out) \
    करो {                          \
        Uint16 x = sC * dC;       \
        x += 0x1U;                \
        x += x >> 8;              \
        out = x >> 8;             \
    } जबतक (0)
// Blend the RGB values of two pixels with an alpha value
#घोषणा ALPHA_BLEND_RGB(sR, sG, sB, A, dR, dG, dB)            \
    करो {                                                      \
        ALPHA_BLEND_CHANNEL(sR, dR, A);                       \
        ALPHA_BLEND_CHANNEL(sG, dG, A);                       \
        ALPHA_BLEND_CHANNEL(sB, dB, A);                       \
    } जबतक (0)

// Blend two 8888 pixels with the same format
/* Calculates dst = ((src * factor) + (dst * (255 - factor))) / 255 */
// FIXME: SDL_SIZE_MAX might not be an integer literal
#अगर defined(SIZE_MAX) && (SIZE_MAX == 0xffffffffffffffff)
#घोषणा FACTOR_BLEND_8888(src, dst, factor)                        \
    करो {                                                           \
        Uint64 src64 = src;                                        \
        src64 = (src64 | (src64 << 24)) & 0x00FF00FF00FF00FF;      \
                                                                   \
        Uint64 dst64 = dst;                                        \
        dst64 = (dst64 | (dst64 << 24)) & 0x00FF00FF00FF00FF;      \
                                                                   \
        dst64 = ((src64 - dst64) * factor) + (dst64 << 8) - dst64; \
        dst64 += 0x0001000100010001;                               \
        dst64 += (dst64 >> 8) & 0x00FF00FF00FF00FF;                \
        dst64 &= 0xFF00FF00FF00FF00;                               \
                                                                   \
        dst = (Uint32)((dst64 >> 8) | (dst64 >> 32));              \
    } जबतक (0)
#अन्यथा
#घोषणा FACTOR_BLEND_8888(src, dst, factor)                               \
    करो {                                                                  \
        Uint32 src02 = src & 0x00FF00FF;                                  \
        Uint32 dst02 = dst & 0x00FF00FF;                                  \
                                                                          \
        Uint32 src13 = (src >> 8) & 0x00FF00FF;                           \
        Uint32 dst13 = (dst >> 8) & 0x00FF00FF;                           \
                                                                          \
        Uint32 res02 = ((src02 - dst02) * factor) + (dst02 << 8) - dst02; \
        res02 += 0x00010001;                                              \
        res02 += (res02 >> 8) & 0x00FF00FF;                               \
        res02 = (res02 >> 8) & 0x00FF00FF;                                \
                                                                          \
        Uint32 res13 = ((src13 - dst13) * factor) + (dst13 << 8) - dst13; \
        res13 += 0x00010001;                                              \
        res13 += (res13 >> 8) & 0x00FF00FF;                               \
        res13 &= 0xFF00FF00;                                              \
        dst = res02 | res13;                                              \
    } जबतक (0)
#पूर्ण_अगर

// Alpha blend two 8888 pixels with the same formats.
#घोषणा ALPHA_BLEND_8888(src, dst, fmt)            \
    करो {                                           \
        Uint32 srcA = (src >> fmt->Ashift) & 0xFF; \
        Uint32 tmp = src | fmt->Amask;             \
        FACTOR_BLEND_8888(tmp, dst, srcA);         \
    } जबतक (0)

// Alpha blend two 8888 pixels with differing formats.
#घोषणा ALPHA_BLEND_SWIZZLE_8888(src, dst, srcfmt, dstfmt)                  \
    करो {                                                                    \
        Uint32 srcA = (src >> srcfmt->Ashift) & 0xFF;                       \
        Uint32 tmp = (((src >> srcfmt->Rshift) & 0xFF) << dstfmt->Rshift) | \
                     (((src >> srcfmt->Gshift) & 0xFF) << dstfmt->Gshift) | \
                     (((src >> srcfmt->Bshift) & 0xFF) << dstfmt->Bshift) | \
                     dstfmt->Amask;                                         \
        FACTOR_BLEND_8888(tmp, dst, srcA);                                  \
    } जबतक (0)
// Blend the RGBA values of two pixels
#घोषणा ALPHA_BLEND_RGBA(sR, sG, sB, sA, dR, dG, dB, dA) \
    करो {                                                 \
        ALPHA_BLEND_CHANNEL(sR, dR, sA);                 \
        ALPHA_BLEND_CHANNEL(sG, dG, sA);                 \
        ALPHA_BLEND_CHANNEL(sB, dB, sA);                 \
        ALPHA_BLEND_CHANNEL(255, dA, sA);                \
    } जबतक (0)

// This is a very useful loop for optimizing blitters
#अगर defined(_MSC_VER) && (_MSC_VER == 1300)
// There's a bug in the Visual C++ 7 optimizer when compiling this code
#अन्यथा
#घोषणा USE_DUFFS_LOOP
#पूर्ण_अगर

#घोषणा DUFFS_LOOP1(pixel_copy_increment, width) \
    {                                            \
        पूर्णांक n;                                   \
        क्रम (n = width; n > 0; --n) {            \
            pixel_copy_increment;                \
        }                                        \
    }

#अगर_घोषित USE_DUFFS_LOOP

// 8-times unrolled loop
#घोषणा DUFFS_LOOP8(pixel_copy_increment, width) \
    {                                            \
        पूर्णांक n = (width + 7) / 8;                 \
        चयन (width & 7) {                     \
        हाल 0:                                  \
            करो {                                 \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            हाल 7:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            हाल 6:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            हाल 5:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            हाल 4:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            हाल 3:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            हाल 2:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            हाल 1:                              \
                pixel_copy_increment;            \
            } जबतक (--n > 0);                   \
        }                                        \
    }

// 4-times unrolled loop
#घोषणा DUFFS_LOOP4(pixel_copy_increment, width) \
    {                                            \
        पूर्णांक n = (width + 3) / 4;                 \
        चयन (width & 3) {                     \
        हाल 0:                                  \
            करो {                                 \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            हाल 3:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            हाल 2:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            हाल 1:                              \
                pixel_copy_increment;            \
            } जबतक (--n > 0);                   \
        }                                        \
    }

// 2-times unrolled loop
#घोषणा DUFFS_LOOP2(pixel_copy_increment, width) \
    {                                            \
        पूर्णांक n = (width + 1) / 2;                 \
        चयन (width & 1) {                     \
        हाल 0:                                  \
            करो {                                 \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            हाल 1:                              \
                pixel_copy_increment;            \
            } जबतक (--n > 0);                   \
        }                                        \
    }

// Use the 4-times version of the loop by default
#घोषणा DUFFS_LOOP(pixel_copy_increment, width) \
    DUFFS_LOOP4(pixel_copy_increment, width)
// Use the 8-times version of the loop for simple routines
#घोषणा DUFFS_LOOP_TRIVIAL(pixel_copy_increment, width) \
    DUFFS_LOOP8(pixel_copy_increment, width)

// Special version of Duff's device for even more optimization
#घोषणा DUFFS_LOOP_124(pixel_copy_increment1,        \
                       pixel_copy_increment2,        \
                       pixel_copy_increment4, width) \
    {                                                \
        पूर्णांक n = width;                               \
        अगर (n & 1) {                                 \
            pixel_copy_increment1;                   \
            n -= 1;                                  \
        }                                            \
        अगर (n & 2) {                                 \
            pixel_copy_increment2;                   \
            n -= 2;                                  \
        }                                            \
        अगर (n & 4) {                                 \
            pixel_copy_increment4;                   \
            n -= 4;                                  \
        }                                            \
        अगर (n) {                                     \
            n /= 8;                                  \
            करो {                                     \
                pixel_copy_increment4;               \
                pixel_copy_increment4;               \
            } जबतक (--n > 0);                       \
        }                                            \
    }

#अन्यथा

// Don't use Duff's device to unroll loops
#घोषणा DUFFS_LOOP(pixel_copy_increment, width) \
    DUFFS_LOOP1(pixel_copy_increment, width)
#घोषणा DUFFS_LOOP_TRIVIAL(pixel_copy_increment, width) \
    DUFFS_LOOP1(pixel_copy_increment, width)
#घोषणा DUFFS_LOOP8(pixel_copy_increment, width) \
    DUFFS_LOOP1(pixel_copy_increment, width)
#घोषणा DUFFS_LOOP4(pixel_copy_increment, width) \
    DUFFS_LOOP1(pixel_copy_increment, width)
#घोषणा DUFFS_LOOP2(pixel_copy_increment, width) \
    DUFFS_LOOP1(pixel_copy_increment, width)
#घोषणा DUFFS_LOOP_124(pixel_copy_increment1,        \
                       pixel_copy_increment2,        \
                       pixel_copy_increment4, width) \
    DUFFS_LOOP1(pixel_copy_increment1, width)

#पूर्ण_अगर // USE_DUFFS_LOOP

#अगर defined(_MSC_VER) && (_MSC_VER >= 600)
#आशय warning(disable : 4244) // '=': conversion from 'X' to 'Y', possible loss of data
#पूर्ण_अगर

#पूर्ण_अगर // SDL_blit_h_
