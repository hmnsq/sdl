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

#నిర్వచితం_కాకపోతే SDL_blit_h_
#నిర్వచించు SDL_blit_h_

// Table to do pixel byte expansion
బాహ్య స్థిరరాశి Uint8 *SDL_expand_byte[9];
బాహ్య స్థిరరాశి Uint16 SDL_expand_byte_10[];

// SDL blit copy flags
#నిర్వచించు SDL_COPY_MODULATE_COLOR         0x00000001
#నిర్వచించు SDL_COPY_MODULATE_ALPHA         0x00000002
#నిర్వచించు SDL_COPY_MODULATE_ముసుగు		(SDL_COPY_MODULATE_COLOR | SDL_COPY_MODULATE_ALPHA)
#నిర్వచించు SDL_COPY_BLEND                  0x00000010
#నిర్వచించు SDL_COPY_BLEND_PREMULTIPLIED    0x00000020
#నిర్వచించు SDL_COPY_కూడు                    0x00000040
#నిర్వచించు SDL_COPY_కూడు_PREMULTIPLIED      0x00000080
#నిర్వచించు SDL_COPY_MOD                    0x00000100
#నిర్వచించు SDL_COPY_MUL                    0x00000200
#నిర్వచించు SDL_COPY_BLEND_ముసుగు		(SDL_COPY_BLEND | SDL_COPY_BLEND_PREMULTIPLIED | SDL_COPY_కూడు | SDL_COPY_కూడు_PREMULTIPLIED | SDL_COPY_MOD | SDL_COPY_MUL)
#నిర్వచించు SDL_COPY_COLORKEY               0x00000400
#నిర్వచించు SDL_COPY_సమీప                0x00000800
#నిర్వచించు SDL_COPY_RLE_DESIRED            0x00001000
#నిర్వచించు SDL_COPY_RLE_COLORKEY           0x00002000
#నిర్వచించు SDL_COPY_RLE_ALPHAKEY           0x00004000
#నిర్వచించు SDL_COPY_RLE_ముసుగు               (SDL_COPY_RLE_DESIRED | SDL_COPY_RLE_COLORKEY | SDL_COPY_RLE_ALPHAKEY)

// SDL blit CPU flags
#నిర్వచించు SDL_CPU_ANY                0x00000000
#నిర్వచించు SDL_CPU_MMX                0x00000001
#నిర్వచించు SDL_CPU_SSE                0x00000002
#నిర్వచించు SDL_CPU_SSE2               0x00000004
#నిర్వచించు SDL_CPU_ALTIVEC_PREFETCH   0x00000008
#నిర్వచించు SDL_CPU_ALTIVEC_NOPREFETCH 0x00000010

రకనిర్వచనం నిర్మాణం
{
    SDL_Surface *src_surface;
    Uint8 *src;
    పూర్ణాంకం src_w, src_h;
    పూర్ణాంకం src_pitch;
    పూర్ణాంకం src_skip;
    పూర్ణాంకం leading_skip;
    SDL_Surface *dst_surface;
    Uint8 *dst;
    పూర్ణాంకం dst_w, dst_h;
    పూర్ణాంకం dst_pitch;
    పూర్ణాంకం dst_skip;
    స్థిరరాశి SDL_PixelFormatDetails *src_fmt;
    స్థిరరాశి SDL_Palette *src_pal;
    స్థిరరాశి SDL_PixelFormatDetails *dst_fmt;
    స్థిరరాశి SDL_Palette *dst_pal;
    Uint8 *పట్టిక;
    SDL_Hash_పట్టిక *palette_map;
    పూర్ణాంకం flags;
    Uint32 colorkey;
    Uint8 r, g, b, a;
} SDL_BlitInfo;

రకనిర్వచనం శూన్య (*SDL_BlitFunc)(SDL_BlitInfo *info);

రకనిర్వచనం నిర్మాణం
{
    SDL_PixelFormat src_format;
    SDL_PixelFormat dst_format;
    పూర్ణాంకం flags;
    SDL_BlitFunc func;
} SDL_Blit_Func_నమోదు;

రకనిర్వచనం bool (SDLCALL *SDL_Blit) (నిర్మాణం SDL_Surface *src, స్థిరరాశి SDL_Rect *srcrect, నిర్మాణం SDL_Surface *dst, స్థిరరాశి SDL_Rect *dstrect);

// Blit mapping definition
రకనిర్వచనం నిర్మాణం SDL_BlitMap
{
    పూర్ణాంకం తటస్థం;
    SDL_Blit blit;
    శూన్య *దత్తాంశం;
    SDL_BlitInfo info;

    /* the version count matches the destination; mismatch indicates
       an invalid mapping */
    Uint32 dst_palette_సంస్కరణ;
    Uint32 src_palette_సంస్కరణ;
} SDL_BlitMap;

// Functions found in SDL_blit.c
బాహ్య bool SDL_CalculateBlit(SDL_Surface *surface, SDL_Surface *dst);

/* Functions found in SDL_blit_*.c */
బాహ్య SDL_BlitFunc SDL_CalculateBlit0(SDL_Surface *surface);
బాహ్య SDL_BlitFunc SDL_CalculateBlit1(SDL_Surface *surface);
బాహ్య SDL_BlitFunc SDL_CalculateBlitN(SDL_Surface *surface);
బాహ్య SDL_BlitFunc SDL_CalculateBlitA(SDL_Surface *surface);

/*
 * Useful macros for blitting routines
 */

#నిర్వచితమైతే __GNUC__
#నిర్వచించు DECLARE_ALIGNED(t, v, a) t __attribute__((aligned(a))) v
#లేదావేళ defined(_MSC_VER)
#నిర్వచించు DECLARE_ALIGNED(t, v, a) __declspec(align(a)) t v
#లేకపోతే
#నిర్వచించు DECLARE_ALIGNED(t, v, a) t v
#అయితే_ముగింపు

// Load pixel of the specified format from a buffer and get its R-G-B values
#నిర్వచించు RGB_FROM_PIXEL(Pixel, fmt, r, g, b)                                     \
    {                                                                           \
        r = SDL_expand_byte[fmt->Rbits][((Pixel & fmt->Rmask) >> fmt->Rshift)]; \
        g = SDL_expand_byte[fmt->Gbits][((Pixel & fmt->Gmask) >> fmt->Gshift)]; \
        b = SDL_expand_byte[fmt->Bbits][((Pixel & fmt->Bmask) >> fmt->Bshift)]; \
    }
#నిర్వచించు RGB_FROM_RGB565(Pixel, r, g, b)                   \
    {                                                     \
        r = SDL_expand_byte[5][((Pixel & 0xF800) >> 11)]; \
        g = SDL_expand_byte[6][((Pixel & 0x07E0) >> 5)];  \
        b = SDL_expand_byte[5][(Pixel & 0x001F)];         \
    }
#నిర్వచించు RGB_FROM_RGB555(Pixel, r, g, b)                   \
    {                                                     \
        r = SDL_expand_byte[5][((Pixel & 0x7C00) >> 10)]; \
        g = SDL_expand_byte[5][((Pixel & 0x03E0) >> 5)];  \
        b = SDL_expand_byte[5][(Pixel & 0x001F)];         \
    }
#నిర్వచించు RGB_FROM_XRGB8888(Pixel, r, g, b) \
    {                                   \
        r = ((Pixel & 0xFF0000) >> 16); \
        g = ((Pixel & 0xFF00) >> 8);    \
        b = (Pixel & 0xFF);             \
    }
#ఒకవేళ SDL_BYTEORDER == SDL_LIL_ENDIAN
#నిర్వచించు GET_RGB24(B) (B[2] << 16) | (B[1] << 8) | B[0]
#లేకపోతే
#నిర్వచించు GET_RGB24(B) (B[0] << 16) | (B[1] << 8) | B[2]
#అయితే_ముగింపు
#నిర్వచించు RETRIEVE_RGB_PIXEL(buf, bpp, Pixel)                \
    చేయి {                                                   \
        ఎంపిక (bpp) {                                     \
        స్థితి 1:                                            \
            Pixel = *((Uint8 *)(buf));                     \
            ఆపు;                                         \
                                                           \
        స్థితి 2:                                            \
            Pixel = *((Uint16 *)(buf));                    \
            ఆపు;                                         \
                                                           \
        స్థితి 3:                                            \
        {                                                  \
            Uint8 *B = (Uint8 *)(buf);                     \
            Pixel = GET_RGB24(B);                          \
        } ఆపు;                                           \
                                                           \
        స్థితి 4:                                            \
            Pixel = *((Uint32 *)(buf));                    \
            ఆపు;                                         \
                                                           \
        అప్రమేయ:                                           \
            Pixel = 0; /* stop gcc complaints */           \
            ఆపు;                                         \
        }                                                  \
    } అయితే (0)

#ఒకవేళ SDL_BYTEORDER == SDL_LIL_ENDIAN
#నిర్వచించు GET_RGB24_COMPONENT(buf, fmt, జరుపు) *((buf) + fmt->జరుపు / 8)
#లేకపోతే
#నిర్వచించు GET_RGB24_COMPONENT(buf, fmt, జరుపు) *((buf) + 2 - fmt->జరుపు / 8)
#అయితే_ముగింపు
#నిర్వచించు DISEMBLE_RGB(buf, bpp, fmt, Pixel, r, g, b)    \
    చేయి {                                               \
        ఎంపిక (bpp) {                                 \
        స్థితి 1:                                        \
            Pixel = *((Uint8 *)(buf));                 \
            RGB_FROM_PIXEL(Pixel, fmt, r, g, b);       \
            ఆపు;                                     \
                                                       \
        స్థితి 2:                                        \
            Pixel = *((Uint16 *)(buf));                \
            RGB_FROM_PIXEL(Pixel, fmt, r, g, b);       \
            ఆపు;                                     \
                                                       \
        స్థితి 3:                                        \
        {                                              \
            Pixel = 0;                                 \
            r = GET_RGB24_COMPONENT(buf, fmt, Rshift); \
            g = GET_RGB24_COMPONENT(buf, fmt, Gshift); \
            b = GET_RGB24_COMPONENT(buf, fmt, Bshift); \
        } ఆపు;                                       \
                                                       \
        స్థితి 4:                                        \
            Pixel = *((Uint32 *)(buf));                \
            RGB_FROM_PIXEL(Pixel, fmt, r, g, b);       \
            ఆపు;                                     \
                                                       \
        అప్రమేయ:                                       \
            /* stop gcc complaints */                  \
            Pixel = 0;                                 \
            r = g = b = 0;                             \
            ఆపు;                                     \
        }                                              \
    } అయితే (0)

// Assemble R-G-B values into a specified pixel format and store them
#నిర్వచించు PIXEL_FROM_RGB(Pixel, fmt, r, g, b)                 \
    {                                                       \
        Pixel = ((r >> (8 - fmt->Rbits)) << fmt->Rshift) |  \
                ((g >> (8 - fmt->Gbits)) << fmt->Gshift) |  \
                ((b >> (8 - fmt->Bbits)) << fmt->Bshift) |  \
                fmt->Amask;                                 \
    }
#నిర్వచించు RGB332_FROM_RGB(Pixel, r, g, b)                        \
    {                                                          \
        Pixel = (Uint8)(((r >> 5) << 5) | ((g >> 5) << 2) | (b >> 6)); \
    }
#నిర్వచించు RGB565_FROM_RGB(Pixel, r, g, b)                        \
    {                                                          \
        Pixel = (Uint16)(((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3)); \
    }
#నిర్వచించు RGB555_FROM_RGB(Pixel, r, g, b)                        \
    {                                                          \
        Pixel = (Uint16)(((r >> 3) << 10) | ((g >> 3) << 5) | (b >> 3)); \
    }
#నిర్వచించు XRGB8888_FROM_RGB(Pixel, r, g, b)   \
    {                                     \
        Pixel = (r << 16) | (g << 8) | b; \
    }
#నిర్వచించు ARGB8888_FROM_RGBA(Pixel, r, g, b, a)         \
    {                                                 \
        Pixel = (a << 24) | (r << 16) | (g << 8) | b; \
    }
#నిర్వచించు RGBA8888_FROM_RGBA(Pixel, r, g, b, a)         \
    {                                                 \
        Pixel = (r << 24) | (g << 16) | (b << 8) | a; \
    }
#నిర్వచించు ABGR8888_FROM_RGBA(Pixel, r, g, b, a)         \
    {                                                 \
        Pixel = (a << 24) | (b << 16) | (g << 8) | r; \
    }
#నిర్వచించు BGRA8888_FROM_RGBA(Pixel, r, g, b, a)         \
    {                                                 \
        Pixel = (b << 24) | (g << 16) | (r << 8) | a; \
    }
#నిర్వచించు ARGB2101010_FROM_RGBA(Pixel, r, g, b, a)       \
    {                                                  \
        r = r ? ((r << 2) | 0x3) : 0;                  \
        g = g ? ((g << 2) | 0x3) : 0;                  \
        b = b ? ((b << 2) | 0x3) : 0;                  \
        a = (a * 3) / 255;                             \
        Pixel = (a << 30) | (r << 20) | (g << 10) | b; \
    }
#నిర్వచించు ARGB2101010_FROM_RGBAFLOAT(Pixel, r, g, b, a) \
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
#నిర్వచించు ABGR2101010_FROM_RGBA(Pixel, r, g, b, a)       \
    {                                                  \
        r = r ? ((r << 2) | 0x3) : 0;                  \
        g = g ? ((g << 2) | 0x3) : 0;                  \
        b = b ? ((b << 2) | 0x3) : 0;                  \
        a = (a * 3) / 255;                             \
        Pixel = (a << 30) | (b << 20) | (g << 10) | r; \
    }
#నిర్వచించు ABGR2101010_FROM_RGBAFLOAT(Pixel, r, g, b, a) \
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
#నిర్వచించు ASSEMBLE_RGB(buf, bpp, fmt, r, g, b)           \
    {                                                  \
        ఎంపిక (bpp) {                                 \
        స్థితి 1:                                        \
        {                                              \
            Uint8 _pixel;                              \
                                                       \
            PIXEL_FROM_RGB(_pixel, fmt, r, g, b);      \
            *((Uint8 *)(buf)) = _pixel;                \
        } ఆపు;                                       \
                                                       \
        స్థితి 2:                                        \
        {                                              \
            Uint16 _pixel;                             \
                                                       \
            PIXEL_FROM_RGB(_pixel, fmt, r, g, b);      \
            *((Uint16 *)(buf)) = _pixel;               \
        } ఆపు;                                       \
                                                       \
        స్థితి 3:                                        \
        {                                              \
            GET_RGB24_COMPONENT(buf, fmt, Rshift) = r; \
            GET_RGB24_COMPONENT(buf, fmt, Gshift) = g; \
            GET_RGB24_COMPONENT(buf, fmt, Bshift) = b; \
        } ఆపు;                                       \
                                                       \
        స్థితి 4:                                        \
        {                                              \
            Uint32 _pixel;                             \
                                                       \
            PIXEL_FROM_RGB(_pixel, fmt, r, g, b);      \
            *((Uint32 *)(buf)) = _pixel;               \
        } ఆపు;                                       \
        }                                              \
    }

// FIXME: Should we rescale alpha into 0..255 here?
#నిర్వచించు RGBA_FROM_PIXEL(Pixel, fmt, r, g, b, a)                                 \
    {                                                                           \
        r = SDL_expand_byte[fmt->Rbits][((Pixel & fmt->Rmask) >> fmt->Rshift)]; \
        g = SDL_expand_byte[fmt->Gbits][((Pixel & fmt->Gmask) >> fmt->Gshift)]; \
        b = SDL_expand_byte[fmt->Bbits][((Pixel & fmt->Bmask) >> fmt->Bshift)]; \
        a = SDL_expand_byte[fmt->Abits][((Pixel & fmt->Amask) >> fmt->Ashift)]; \
    }
#నిర్వచించు RGBA_FROM_8888(Pixel, fmt, r, g, b, a)   \
    {                                            \
        r = (Pixel & fmt->Rmask) >> fmt->Rshift; \
        g = (Pixel & fmt->Gmask) >> fmt->Gshift; \
        b = (Pixel & fmt->Bmask) >> fmt->Bshift; \
        a = (Pixel & fmt->Amask) >> fmt->Ashift; \
    }
#నిర్వచించు RGBA_FROM_RGBA8888(Pixel, r, g, b, a) \
    {                                         \
        r = (Pixel >> 24);                    \
        g = ((Pixel >> 16) & 0xFF);           \
        b = ((Pixel >> 8) & 0xFF);            \
        a = (Pixel & 0xFF);                   \
    }
#నిర్వచించు RGBA_FROM_ARGB8888(Pixel, r, g, b, a) \
    {                                         \
        r = ((Pixel >> 16) & 0xFF);           \
        g = ((Pixel >> 8) & 0xFF);            \
        b = (Pixel & 0xFF);                   \
        a = (Pixel >> 24);                    \
    }
#నిర్వచించు RGBA_FROM_ABGR8888(Pixel, r, g, b, a) \
    {                                         \
        r = (Pixel & 0xFF);                   \
        g = ((Pixel >> 8) & 0xFF);            \
        b = ((Pixel >> 16) & 0xFF);           \
        a = (Pixel >> 24);                    \
    }
#నిర్వచించు RGBA_FROM_BGRA8888(Pixel, r, g, b, a) \
    {                                         \
        r = ((Pixel >> 8) & 0xFF);            \
        g = ((Pixel >> 16) & 0xFF);           \
        b = (Pixel >> 24);                    \
        a = (Pixel & 0xFF);                   \
    }
#నిర్వచించు RGBA_FROM_ARGB2101010(Pixel, r, g, b, a) \
    {                                            \
        r = ((Pixel >> 22) & 0xFF);              \
        g = ((Pixel >> 12) & 0xFF);              \
        b = ((Pixel >> 2) & 0xFF);               \
        a = SDL_expand_byte[2][(Pixel >> 30)];   \
    }
#నిర్వచించు RGBAFLOAT_FROM_ARGB2101010(Pixel, r, g, b, a)   \
    {                                                   \
        r = (దశాంశం)((Pixel >> 20) & 0x3FF) / 1023.0f;   \
        g = (దశాంశం)((Pixel >> 10) & 0x3FF) / 1023.0f;   \
        b = (దశాంశం)((Pixel >> 0) & 0x3FF) / 1023.0f;    \
        a = (దశాంశం)(Pixel >> 30) / 3.0f;                \
    }
#నిర్వచించు RGBA_FROM_ABGR2101010(Pixel, r, g, b, a) \
    {                                            \
        r = ((Pixel >> 2) & 0xFF);               \
        g = ((Pixel >> 12) & 0xFF);              \
        b = ((Pixel >> 22) & 0xFF);              \
        a = SDL_expand_byte[2][(Pixel >> 30)];   \
    }
#నిర్వచించు RGBAFLOAT_FROM_ABGR2101010(Pixel, r, g, b, a)   \
    {                                                   \
        r = (దశాంశం)((Pixel >> 0) & 0x3FF) / 1023.0f;    \
        g = (దశాంశం)((Pixel >> 10) & 0x3FF) / 1023.0f;   \
        b = (దశాంశం)((Pixel >> 20) & 0x3FF) / 1023.0f;   \
        a = (దశాంశం)(Pixel >> 30) / 3.0f;                \
    }
#నిర్వచించు DISEMBLE_RGBA(buf, bpp, fmt, Pixel, r, g, b, a) \
    చేయి {                                                \
        ఎంపిక (bpp) {                                  \
        స్థితి 1:                                         \
            Pixel = *((Uint8 *)(buf));                  \
            RGBA_FROM_PIXEL(Pixel, fmt, r, g, b, a);    \
            ఆపు;                                      \
                                                        \
        స్థితి 2:                                         \
            Pixel = *((Uint16 *)(buf));                 \
            RGBA_FROM_PIXEL(Pixel, fmt, r, g, b, a);    \
            ఆపు;                                      \
                                                        \
        స్థితి 3:                                         \
        {                                               \
            Pixel = 0;                                  \
            r = GET_RGB24_COMPONENT(buf, fmt, Rshift);  \
            g = GET_RGB24_COMPONENT(buf, fmt, Gshift);  \
            b = GET_RGB24_COMPONENT(buf, fmt, Bshift);  \
            a = 0xFF;                                   \
        } ఆపు;                                        \
                                                        \
        స్థితి 4:                                         \
            Pixel = *((Uint32 *)(buf));                 \
            RGBA_FROM_PIXEL(Pixel, fmt, r, g, b, a);    \
            ఆపు;                                      \
                                                        \
        అప్రమేయ:                                        \
            /* stop gcc complaints */                   \
            Pixel = 0;                                  \
            r = g = b = a = 0;                          \
            ఆపు;                                      \
        }                                               \
    } అయితే (0)

// FIXME: this isn't correct, especially for Alpha (maximum != 255)
#నిర్వచించు PIXEL_FROM_RGBA(Pixel, fmt, r, g, b, a)             \
    {                                                       \
        Pixel = ((r >> (8 - fmt->Rbits)) << fmt->Rshift) |  \
                ((g >> (8 - fmt->Gbits)) << fmt->Gshift) |  \
                ((b >> (8 - fmt->Bbits)) << fmt->Bshift) |  \
                ((a >> (8 - fmt->Abits)) << fmt->Ashift);   \
    }
#నిర్వచించు ASSEMBLE_RGBA(buf, bpp, fmt, r, g, b, a)       \
    {                                                  \
        ఎంపిక (bpp) {                                 \
        స్థితి 1:                                        \
        {                                              \
            Uint8 _pixel;                              \
                                                       \
            PIXEL_FROM_RGBA(_pixel, fmt, r, g, b, a);  \
            *((Uint8 *)(buf)) = _pixel;                \
        } ఆపు;                                       \
                                                       \
        స్థితి 2:                                        \
        {                                              \
            Uint16 _pixel;                             \
                                                       \
            PIXEL_FROM_RGBA(_pixel, fmt, r, g, b, a);  \
            *((Uint16 *)(buf)) = _pixel;               \
        } ఆపు;                                       \
                                                       \
        స్థితి 3:                                        \
        {                                              \
            GET_RGB24_COMPONENT(buf, fmt, Rshift) = r; \
            GET_RGB24_COMPONENT(buf, fmt, Gshift) = g; \
            GET_RGB24_COMPONENT(buf, fmt, Bshift) = b; \
        } ఆపు;                                       \
                                                       \
        స్థితి 4:                                        \
        {                                              \
            Uint32 _pixel;                             \
                                                       \
            PIXEL_FROM_RGBA(_pixel, fmt, r, g, b, a);  \
            *((Uint32 *)(buf)) = _pixel;               \
        } ఆపు;                                       \
        }                                              \
    }

// Convert any 32-bit 4-bpp pixel to ARGB format
#నిర్వచించు PIXEL_గమ్యం_ARGB_PIXEL(src, srcfmt, dst)         \
    చేయి {                                              \
        Uint8 a, r, g, b;                         \
        RGBA_FROM_PIXEL(src, srcfmt, r, g, b, a); \
        dst = a << 24 | r << 16 | g << 8 | b;     \
    } అయితే (0)
// Blend a single color channel or alpha value
/* dC = ((sC * sA) + (dC * (255 - sA))) / 255 */
#నిర్వచించు ALPHA_BLEND_CHANNEL(sC, dC, sA)                  \
    చేయి {                                                 \
        Uint16 x;                                        \
        x = ((sC - dC) * sA) + ((dC << 8) - dC);         \
        x += 0x1U;                                       \
        x += x >> 8;                                     \
        dC = x >> 8;                                     \
    } అయితే (0)
// Perform a division by 255 after a multiplication of two 8-bit color channels
/* out = (sC * dC) / 255 */
#నిర్వచించు MULT_DIV_255(sC, dC, బహిర్గతం) \
    చేయి {                          \
        Uint16 x = sC * dC;       \
        x += 0x1U;                \
        x += x >> 8;              \
        బహిర్గతం = x >> 8;             \
    } అయితే (0)
// Blend the RGB values of two pixels with an alpha value
#నిర్వచించు ALPHA_BLEND_RGB(sR, sG, sB, A, dR, dG, dB)            \
    చేయి {                                                      \
        ALPHA_BLEND_CHANNEL(sR, dR, A);                       \
        ALPHA_BLEND_CHANNEL(sG, dG, A);                       \
        ALPHA_BLEND_CHANNEL(sB, dB, A);                       \
    } అయితే (0)

// Blend two 8888 pixels with the same format
/* Calculates dst = ((src * factor) + (dst * (255 - factor))) / 255 */
// FIXME: SDL_SIZE_MAX might not be an integer literal
#ఒకవేళ defined(SIZE_MAX) && (SIZE_MAX == 0xffffffffffffffff)
#నిర్వచించు గుణకం_BLEND_8888(src, dst, గుణకం)                        \
    చేయి {                                                           \
        Uint64 src64 = src;                                        \
        src64 = (src64 | (src64 << 24)) & 0x00FF00FF00FF00FF;      \
                                                                   \
        Uint64 dst64 = dst;                                        \
        dst64 = (dst64 | (dst64 << 24)) & 0x00FF00FF00FF00FF;      \
                                                                   \
        dst64 = ((src64 - dst64) * గుణకం) + (dst64 << 8) - dst64; \
        dst64 += 0x0001000100010001;                               \
        dst64 += (dst64 >> 8) & 0x00FF00FF00FF00FF;                \
        dst64 &= 0xFF00FF00FF00FF00;                               \
                                                                   \
        dst = (Uint32)((dst64 >> 8) | (dst64 >> 32));              \
    } అయితే (0)
#లేకపోతే
#నిర్వచించు గుణకం_BLEND_8888(src, dst, గుణకం)                               \
    చేయి {                                                                  \
        Uint32 src02 = src & 0x00FF00FF;                                  \
        Uint32 dst02 = dst & 0x00FF00FF;                                  \
                                                                          \
        Uint32 src13 = (src >> 8) & 0x00FF00FF;                           \
        Uint32 dst13 = (dst >> 8) & 0x00FF00FF;                           \
                                                                          \
        Uint32 res02 = ((src02 - dst02) * గుణకం) + (dst02 << 8) - dst02; \
        res02 += 0x00010001;                                              \
        res02 += (res02 >> 8) & 0x00FF00FF;                               \
        res02 = (res02 >> 8) & 0x00FF00FF;                                \
                                                                          \
        Uint32 res13 = ((src13 - dst13) * గుణకం) + (dst13 << 8) - dst13; \
        res13 += 0x00010001;                                              \
        res13 += (res13 >> 8) & 0x00FF00FF;                               \
        res13 &= 0xFF00FF00;                                              \
        dst = res02 | res13;                                              \
    } అయితే (0)
#అయితే_ముగింపు

// Alpha blend two 8888 pixels with the same formats.
#నిర్వచించు ALPHA_BLEND_8888(src, dst, fmt)            \
    చేయి {                                           \
        Uint32 srcA = (src >> fmt->Ashift) & 0xFF; \
        Uint32 tmp = src | fmt->Amask;             \
        గుణకం_BLEND_8888(tmp, dst, srcA);         \
    } అయితే (0)

// Alpha blend two 8888 pixels with differing formats.
#నిర్వచించు ALPHA_BLEND_SWIZZLE_8888(src, dst, srcfmt, dstfmt)                  \
    చేయి {                                                                    \
        Uint32 srcA = (src >> srcfmt->Ashift) & 0xFF;                       \
        Uint32 tmp = (((src >> srcfmt->Rshift) & 0xFF) << dstfmt->Rshift) | \
                     (((src >> srcfmt->Gshift) & 0xFF) << dstfmt->Gshift) | \
                     (((src >> srcfmt->Bshift) & 0xFF) << dstfmt->Bshift) | \
                     dstfmt->Amask;                                         \
        గుణకం_BLEND_8888(tmp, dst, srcA);                                  \
    } అయితే (0)
// Blend the RGBA values of two pixels
#నిర్వచించు ALPHA_BLEND_RGBA(sR, sG, sB, sA, dR, dG, dB, dA) \
    చేయి {                                                 \
        ALPHA_BLEND_CHANNEL(sR, dR, sA);                 \
        ALPHA_BLEND_CHANNEL(sG, dG, sA);                 \
        ALPHA_BLEND_CHANNEL(sB, dB, sA);                 \
        ALPHA_BLEND_CHANNEL(255, dA, sA);                \
    } అయితే (0)

// This is a very useful loop for optimizing blitters
#ఒకవేళ defined(_MSC_VER) && (_MSC_VER == 1300)
// There's a bug in the Visual C++ 7 optimizer when compiling this code
#లేకపోతే
#నిర్వచించు USE_DUFFS_LOOP
#అయితే_ముగింపు

#నిర్వచించు DUFFS_LOOP1(pixel_copy_increment, వెడల్పు) \
    {                                            \
        పూర్ణాంకం n;                                   \
        కొరకు (n = వెడల్పు; n > 0; --n) {            \
            pixel_copy_increment;                \
        }                                        \
    }

#నిర్వచితమైతే USE_DUFFS_LOOP

// 8-times unrolled loop
#నిర్వచించు DUFFS_LOOP8(pixel_copy_increment, వెడల్పు) \
    {                                            \
        పూర్ణాంకం n = (వెడల్పు + 7) / 8;                 \
        ఎంపిక (వెడల్పు & 7) {                     \
        స్థితి 0:                                  \
            చేయి {                                 \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            స్థితి 7:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            స్థితి 6:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            స్థితి 5:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            స్థితి 4:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            స్థితి 3:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            స్థితి 2:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            స్థితి 1:                              \
                pixel_copy_increment;            \
            } అయితే (--n > 0);                   \
        }                                        \
    }

// 4-times unrolled loop
#నిర్వచించు DUFFS_LOOP4(pixel_copy_increment, వెడల్పు) \
    {                                            \
        పూర్ణాంకం n = (వెడల్పు + 3) / 4;                 \
        ఎంపిక (వెడల్పు & 3) {                     \
        స్థితి 0:                                  \
            చేయి {                                 \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            స్థితి 3:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            స్థితి 2:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            స్థితి 1:                              \
                pixel_copy_increment;            \
            } అయితే (--n > 0);                   \
        }                                        \
    }

// 2-times unrolled loop
#నిర్వచించు DUFFS_LOOP2(pixel_copy_increment, వెడల్పు) \
    {                                            \
        పూర్ణాంకం n = (వెడల్పు + 1) / 2;                 \
        ఎంపిక (వెడల్పు & 1) {                     \
        స్థితి 0:                                  \
            చేయి {                                 \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            స్థితి 1:                              \
                pixel_copy_increment;            \
            } అయితే (--n > 0);                   \
        }                                        \
    }

// Use the 4-times version of the loop by default
#నిర్వచించు DUFFS_LOOP(pixel_copy_increment, వెడల్పు) \
    DUFFS_LOOP4(pixel_copy_increment, వెడల్పు)
// Use the 8-times version of the loop for simple routines
#నిర్వచించు DUFFS_LOOP_TRIVIAL(pixel_copy_increment, వెడల్పు) \
    DUFFS_LOOP8(pixel_copy_increment, వెడల్పు)

// Special version of Duff's device for even more optimization
#నిర్వచించు DUFFS_LOOP_124(pixel_copy_increment1,        \
                       pixel_copy_increment2,        \
                       pixel_copy_increment4, వెడల్పు) \
    {                                                \
        పూర్ణాంకం n = వెడల్పు;                               \
        ఒకవేళ (n & 1) {                                 \
            pixel_copy_increment1;                   \
            n -= 1;                                  \
        }                                            \
        ఒకవేళ (n & 2) {                                 \
            pixel_copy_increment2;                   \
            n -= 2;                                  \
        }                                            \
        ఒకవేళ (n & 4) {                                 \
            pixel_copy_increment4;                   \
            n -= 4;                                  \
        }                                            \
        ఒకవేళ (n) {                                     \
            n /= 8;                                  \
            చేయి {                                     \
                pixel_copy_increment4;               \
                pixel_copy_increment4;               \
            } అయితే (--n > 0);                       \
        }                                            \
    }

#లేకపోతే

// Don't use Duff's device to unroll loops
#నిర్వచించు DUFFS_LOOP(pixel_copy_increment, వెడల్పు) \
    DUFFS_LOOP1(pixel_copy_increment, వెడల్పు)
#నిర్వచించు DUFFS_LOOP_TRIVIAL(pixel_copy_increment, వెడల్పు) \
    DUFFS_LOOP1(pixel_copy_increment, వెడల్పు)
#నిర్వచించు DUFFS_LOOP8(pixel_copy_increment, వెడల్పు) \
    DUFFS_LOOP1(pixel_copy_increment, వెడల్పు)
#నిర్వచించు DUFFS_LOOP4(pixel_copy_increment, వెడల్పు) \
    DUFFS_LOOP1(pixel_copy_increment, వెడల్పు)
#నిర్వచించు DUFFS_LOOP2(pixel_copy_increment, వెడల్పు) \
    DUFFS_LOOP1(pixel_copy_increment, వెడల్పు)
#నిర్వచించు DUFFS_LOOP_124(pixel_copy_increment1,        \
                       pixel_copy_increment2,        \
                       pixel_copy_increment4, వెడల్పు) \
    DUFFS_LOOP1(pixel_copy_increment1, వెడల్పు)

#అయితే_ముగింపు // USE_DUFFS_LOOP

#ఒకవేళ defined(_MSC_VER) && (_MSC_VER >= 600)
#సూచన warning(disable : 4244) // '=': conversion from 'X' to 'Y', possible loss of data
#అయితే_ముగింపు

#అయితే_ముగింపు // SDL_blit_h_
