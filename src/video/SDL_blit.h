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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_blit_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_blit_h_

// Table to do pixel byte expansion
ಬಾಹ್ಯ ಸ್ಥಿರಾಂಕ Uint8 *SDL_expand_byte[9];
ಬಾಹ್ಯ ಸ್ಥಿರಾಂಕ Uint16 SDL_expand_byte_10[];

// SDL blit copy flags
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_COPY_MODULATE_COLOR         0x00000001
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_COPY_MODULATE_ALPHA         0x00000002
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_COPY_MODULATE_ಮುಖವಾಡ		(SDL_COPY_MODULATE_COLOR | SDL_COPY_MODULATE_ALPHA)
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_COPY_BLEND                  0x00000010
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_COPY_BLEND_PREMULTIPLIED    0x00000020
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_COPY_ಕೂಡಿಸು                    0x00000040
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_COPY_ಕೂಡಿಸು_PREMULTIPLIED      0x00000080
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_COPY_MOD                    0x00000100
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_COPY_MUL                    0x00000200
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_COPY_BLEND_ಮುಖವಾಡ		(SDL_COPY_BLEND | SDL_COPY_BLEND_PREMULTIPLIED | SDL_COPY_ಕೂಡಿಸು | SDL_COPY_ಕೂಡಿಸು_PREMULTIPLIED | SDL_COPY_MOD | SDL_COPY_MUL)
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_COPY_COLORKEY               0x00000400
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_COPY_ಹತ್ತಿರದ                0x00000800
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_COPY_RLE_DESIRED            0x00001000
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_COPY_RLE_COLORKEY           0x00002000
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_COPY_RLE_ALPHAKEY           0x00004000
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_COPY_RLE_ಮುಖವಾಡ               (SDL_COPY_RLE_DESIRED | SDL_COPY_RLE_COLORKEY | SDL_COPY_RLE_ALPHAKEY)

// SDL blit CPU flags
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_CPU_ANY                0x00000000
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_CPU_MMX                0x00000001
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_CPU_SSE                0x00000002
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_CPU_SSE2               0x00000004
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_CPU_ALTIVEC_PREFETCH   0x00000008
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_CPU_ALTIVEC_NOPREFETCH 0x00000010

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
    SDL_Surface *src_surface;
    Uint8 *src;
    ಪೂರ್ಣಾಂಕ src_w, src_h;
    ಪೂರ್ಣಾಂಕ src_pitch;
    ಪೂರ್ಣಾಂಕ src_skip;
    ಪೂರ್ಣಾಂಕ leading_skip;
    SDL_Surface *dst_surface;
    Uint8 *dst;
    ಪೂರ್ಣಾಂಕ dst_w, dst_h;
    ಪೂರ್ಣಾಂಕ dst_pitch;
    ಪೂರ್ಣಾಂಕ dst_skip;
    ಸ್ಥಿರಾಂಕ SDL_PixelFormatDetails *src_fmt;
    ಸ್ಥಿರಾಂಕ SDL_Palette *src_pal;
    ಸ್ಥಿರಾಂಕ SDL_PixelFormatDetails *dst_fmt;
    ಸ್ಥಿರಾಂಕ SDL_Palette *dst_pal;
    Uint8 *ಕೋಷ್ಟಕ;
    SDL_Hash_ಕೋಷ್ಟಕ *palette_map;
    ಪೂರ್ಣಾಂಕ flags;
    Uint32 colorkey;
    Uint8 r, g, b, a;
} SDL_BlitInfo;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (*SDL_BlitFunc)(SDL_BlitInfo *info);

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
    SDL_PixelFormat src_format;
    SDL_PixelFormat dst_format;
    ಪೂರ್ಣಾಂಕ flags;
    SDL_BlitFunc func;
} SDL_Blit_Func_ನಮೂದು;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ bool (SDLCALL *SDL_Blit) (ರಚನೆ SDL_Surface *src, ಸ್ಥಿರಾಂಕ SDL_Rect *srcrect, ರಚನೆ SDL_Surface *dst, ಸ್ಥಿರಾಂಕ SDL_Rect *dstrect);

// Blit mapping definition
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ SDL_BlitMap
{
    ಪೂರ್ಣಾಂಕ ತಟಸ್ಥ;
    SDL_Blit blit;
    ಶೂನ್ಯ *ದತ್ತಾಂಶ;
    SDL_BlitInfo info;

    /* the version count matches the destination; mismatch indicates
       an invalid mapping */
    Uint32 dst_palette_ಆವೃತ್ತಿ;
    Uint32 src_palette_ಆವೃತ್ತಿ;
} SDL_BlitMap;

// Functions found in SDL_blit.c
ಬಾಹ್ಯ bool SDL_CalculateBlit(SDL_Surface *surface, SDL_Surface *dst);

/* Functions found in SDL_blit_*.c */
ಬಾಹ್ಯ SDL_BlitFunc SDL_CalculateBlit0(SDL_Surface *surface);
ಬಾಹ್ಯ SDL_BlitFunc SDL_CalculateBlit1(SDL_Surface *surface);
ಬಾಹ್ಯ SDL_BlitFunc SDL_CalculateBlitN(SDL_Surface *surface);
ಬಾಹ್ಯ SDL_BlitFunc SDL_CalculateBlitA(SDL_Surface *surface);

/*
 * Useful macros for blitting routines
 */

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __GNUC__
#ವ್ಯಾಖ್ಯಾನಿಸು DECLARE_ALIGNED(t, v, a) t __attribute__((aligned(a))) v
#ಅಥವಾಆದರೆ defined(_MSC_VER)
#ವ್ಯಾಖ್ಯಾನಿಸು DECLARE_ALIGNED(t, v, a) __declspec(align(a)) t v
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು DECLARE_ALIGNED(t, v, a) t v
#ಆದರೆ_ಅಂತ್ಯ

// Load pixel of the specified format from a buffer and get its R-G-B values
#ವ್ಯಾಖ್ಯಾನಿಸು RGB_FROM_PIXEL(Pixel, fmt, r, g, b)                                     \
    {                                                                           \
        r = SDL_expand_byte[fmt->Rbits][((Pixel & fmt->Rmask) >> fmt->Rshift)]; \
        g = SDL_expand_byte[fmt->Gbits][((Pixel & fmt->Gmask) >> fmt->Gshift)]; \
        b = SDL_expand_byte[fmt->Bbits][((Pixel & fmt->Bmask) >> fmt->Bshift)]; \
    }
#ವ್ಯಾಖ್ಯಾನಿಸು RGB_FROM_RGB565(Pixel, r, g, b)                   \
    {                                                     \
        r = SDL_expand_byte[5][((Pixel & 0xF800) >> 11)]; \
        g = SDL_expand_byte[6][((Pixel & 0x07E0) >> 5)];  \
        b = SDL_expand_byte[5][(Pixel & 0x001F)];         \
    }
#ವ್ಯಾಖ್ಯಾನಿಸು RGB_FROM_RGB555(Pixel, r, g, b)                   \
    {                                                     \
        r = SDL_expand_byte[5][((Pixel & 0x7C00) >> 10)]; \
        g = SDL_expand_byte[5][((Pixel & 0x03E0) >> 5)];  \
        b = SDL_expand_byte[5][(Pixel & 0x001F)];         \
    }
#ವ್ಯಾಖ್ಯಾನಿಸು RGB_FROM_XRGB8888(Pixel, r, g, b) \
    {                                   \
        r = ((Pixel & 0xFF0000) >> 16); \
        g = ((Pixel & 0xFF00) >> 8);    \
        b = (Pixel & 0xFF);             \
    }
#ಆದರೆ SDL_BYTEORDER == SDL_LIL_ENDIAN
#ವ್ಯಾಖ್ಯಾನಿಸು GET_RGB24(B) (B[2] << 16) | (B[1] << 8) | B[0]
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು GET_RGB24(B) (B[0] << 16) | (B[1] << 8) | B[2]
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿಸು RETRIEVE_RGB_PIXEL(buf, bpp, Pixel)                \
    ಮಾಡು {                                                   \
        ಆಯ್ಕೆ (bpp) {                                     \
        ಸ್ಥಿತಿ 1:                                            \
            Pixel = *((Uint8 *)(buf));                     \
            ನಿಲ್ಲಿಸು;                                         \
                                                           \
        ಸ್ಥಿತಿ 2:                                            \
            Pixel = *((Uint16 *)(buf));                    \
            ನಿಲ್ಲಿಸು;                                         \
                                                           \
        ಸ್ಥಿತಿ 3:                                            \
        {                                                  \
            Uint8 *B = (Uint8 *)(buf);                     \
            Pixel = GET_RGB24(B);                          \
        } ನಿಲ್ಲಿಸು;                                           \
                                                           \
        ಸ್ಥಿತಿ 4:                                            \
            Pixel = *((Uint32 *)(buf));                    \
            ನಿಲ್ಲಿಸು;                                         \
                                                           \
        ಪೂರ್ವನಿಯೋಜಿತ:                                           \
            Pixel = 0; /* stop gcc complaints */           \
            ನಿಲ್ಲಿಸು;                                         \
        }                                                  \
    } ಆಗ (0)

#ಆದರೆ SDL_BYTEORDER == SDL_LIL_ENDIAN
#ವ್ಯಾಖ್ಯಾನಿಸು GET_RGB24_COMPONENT(buf, fmt, ಸರಿಸು) *((buf) + fmt->ಸರಿಸು / 8)
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು GET_RGB24_COMPONENT(buf, fmt, ಸರಿಸು) *((buf) + 2 - fmt->ಸರಿಸು / 8)
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿಸು DISEMBLE_RGB(buf, bpp, fmt, Pixel, r, g, b)    \
    ಮಾಡು {                                               \
        ಆಯ್ಕೆ (bpp) {                                 \
        ಸ್ಥಿತಿ 1:                                        \
            Pixel = *((Uint8 *)(buf));                 \
            RGB_FROM_PIXEL(Pixel, fmt, r, g, b);       \
            ನಿಲ್ಲಿಸು;                                     \
                                                       \
        ಸ್ಥಿತಿ 2:                                        \
            Pixel = *((Uint16 *)(buf));                \
            RGB_FROM_PIXEL(Pixel, fmt, r, g, b);       \
            ನಿಲ್ಲಿಸು;                                     \
                                                       \
        ಸ್ಥಿತಿ 3:                                        \
        {                                              \
            Pixel = 0;                                 \
            r = GET_RGB24_COMPONENT(buf, fmt, Rshift); \
            g = GET_RGB24_COMPONENT(buf, fmt, Gshift); \
            b = GET_RGB24_COMPONENT(buf, fmt, Bshift); \
        } ನಿಲ್ಲಿಸು;                                       \
                                                       \
        ಸ್ಥಿತಿ 4:                                        \
            Pixel = *((Uint32 *)(buf));                \
            RGB_FROM_PIXEL(Pixel, fmt, r, g, b);       \
            ನಿಲ್ಲಿಸು;                                     \
                                                       \
        ಪೂರ್ವನಿಯೋಜಿತ:                                       \
            /* stop gcc complaints */                  \
            Pixel = 0;                                 \
            r = g = b = 0;                             \
            ನಿಲ್ಲಿಸು;                                     \
        }                                              \
    } ಆಗ (0)

// Assemble R-G-B values into a specified pixel format and store them
#ವ್ಯಾಖ್ಯಾನಿಸು PIXEL_FROM_RGB(Pixel, fmt, r, g, b)                 \
    {                                                       \
        Pixel = ((r >> (8 - fmt->Rbits)) << fmt->Rshift) |  \
                ((g >> (8 - fmt->Gbits)) << fmt->Gshift) |  \
                ((b >> (8 - fmt->Bbits)) << fmt->Bshift) |  \
                fmt->Amask;                                 \
    }
#ವ್ಯಾಖ್ಯಾನಿಸು RGB332_FROM_RGB(Pixel, r, g, b)                        \
    {                                                          \
        Pixel = (Uint8)(((r >> 5) << 5) | ((g >> 5) << 2) | (b >> 6)); \
    }
#ವ್ಯಾಖ್ಯಾನಿಸು RGB565_FROM_RGB(Pixel, r, g, b)                        \
    {                                                          \
        Pixel = (Uint16)(((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3)); \
    }
#ವ್ಯಾಖ್ಯಾನಿಸು RGB555_FROM_RGB(Pixel, r, g, b)                        \
    {                                                          \
        Pixel = (Uint16)(((r >> 3) << 10) | ((g >> 3) << 5) | (b >> 3)); \
    }
#ವ್ಯಾಖ್ಯಾನಿಸು XRGB8888_FROM_RGB(Pixel, r, g, b)   \
    {                                     \
        Pixel = (r << 16) | (g << 8) | b; \
    }
#ವ್ಯಾಖ್ಯಾನಿಸು ARGB8888_FROM_RGBA(Pixel, r, g, b, a)         \
    {                                                 \
        Pixel = (a << 24) | (r << 16) | (g << 8) | b; \
    }
#ವ್ಯಾಖ್ಯಾನಿಸು RGBA8888_FROM_RGBA(Pixel, r, g, b, a)         \
    {                                                 \
        Pixel = (r << 24) | (g << 16) | (b << 8) | a; \
    }
#ವ್ಯಾಖ್ಯಾನಿಸು ABGR8888_FROM_RGBA(Pixel, r, g, b, a)         \
    {                                                 \
        Pixel = (a << 24) | (b << 16) | (g << 8) | r; \
    }
#ವ್ಯಾಖ್ಯಾನಿಸು BGRA8888_FROM_RGBA(Pixel, r, g, b, a)         \
    {                                                 \
        Pixel = (b << 24) | (g << 16) | (r << 8) | a; \
    }
#ವ್ಯಾಖ್ಯಾನಿಸು ARGB2101010_FROM_RGBA(Pixel, r, g, b, a)       \
    {                                                  \
        r = r ? ((r << 2) | 0x3) : 0;                  \
        g = g ? ((g << 2) | 0x3) : 0;                  \
        b = b ? ((b << 2) | 0x3) : 0;                  \
        a = (a * 3) / 255;                             \
        Pixel = (a << 30) | (r << 20) | (g << 10) | b; \
    }
#ವ್ಯಾಖ್ಯಾನಿಸು ARGB2101010_FROM_RGBAFLOAT(Pixel, r, g, b, a) \
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
#ವ್ಯಾಖ್ಯಾನಿಸು ABGR2101010_FROM_RGBA(Pixel, r, g, b, a)       \
    {                                                  \
        r = r ? ((r << 2) | 0x3) : 0;                  \
        g = g ? ((g << 2) | 0x3) : 0;                  \
        b = b ? ((b << 2) | 0x3) : 0;                  \
        a = (a * 3) / 255;                             \
        Pixel = (a << 30) | (b << 20) | (g << 10) | r; \
    }
#ವ್ಯಾಖ್ಯಾನಿಸು ABGR2101010_FROM_RGBAFLOAT(Pixel, r, g, b, a) \
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
#ವ್ಯಾಖ್ಯಾನಿಸು ASSEMBLE_RGB(buf, bpp, fmt, r, g, b)           \
    {                                                  \
        ಆಯ್ಕೆ (bpp) {                                 \
        ಸ್ಥಿತಿ 1:                                        \
        {                                              \
            Uint8 _pixel;                              \
                                                       \
            PIXEL_FROM_RGB(_pixel, fmt, r, g, b);      \
            *((Uint8 *)(buf)) = _pixel;                \
        } ನಿಲ್ಲಿಸು;                                       \
                                                       \
        ಸ್ಥಿತಿ 2:                                        \
        {                                              \
            Uint16 _pixel;                             \
                                                       \
            PIXEL_FROM_RGB(_pixel, fmt, r, g, b);      \
            *((Uint16 *)(buf)) = _pixel;               \
        } ನಿಲ್ಲಿಸು;                                       \
                                                       \
        ಸ್ಥಿತಿ 3:                                        \
        {                                              \
            GET_RGB24_COMPONENT(buf, fmt, Rshift) = r; \
            GET_RGB24_COMPONENT(buf, fmt, Gshift) = g; \
            GET_RGB24_COMPONENT(buf, fmt, Bshift) = b; \
        } ನಿಲ್ಲಿಸು;                                       \
                                                       \
        ಸ್ಥಿತಿ 4:                                        \
        {                                              \
            Uint32 _pixel;                             \
                                                       \
            PIXEL_FROM_RGB(_pixel, fmt, r, g, b);      \
            *((Uint32 *)(buf)) = _pixel;               \
        } ನಿಲ್ಲಿಸು;                                       \
        }                                              \
    }

// FIXME: Should we rescale alpha into 0..255 here?
#ವ್ಯಾಖ್ಯಾನಿಸು RGBA_FROM_PIXEL(Pixel, fmt, r, g, b, a)                                 \
    {                                                                           \
        r = SDL_expand_byte[fmt->Rbits][((Pixel & fmt->Rmask) >> fmt->Rshift)]; \
        g = SDL_expand_byte[fmt->Gbits][((Pixel & fmt->Gmask) >> fmt->Gshift)]; \
        b = SDL_expand_byte[fmt->Bbits][((Pixel & fmt->Bmask) >> fmt->Bshift)]; \
        a = SDL_expand_byte[fmt->Abits][((Pixel & fmt->Amask) >> fmt->Ashift)]; \
    }
#ವ್ಯಾಖ್ಯಾನಿಸು RGBA_FROM_8888(Pixel, fmt, r, g, b, a)   \
    {                                            \
        r = (Pixel & fmt->Rmask) >> fmt->Rshift; \
        g = (Pixel & fmt->Gmask) >> fmt->Gshift; \
        b = (Pixel & fmt->Bmask) >> fmt->Bshift; \
        a = (Pixel & fmt->Amask) >> fmt->Ashift; \
    }
#ವ್ಯಾಖ್ಯಾನಿಸು RGBA_FROM_RGBA8888(Pixel, r, g, b, a) \
    {                                         \
        r = (Pixel >> 24);                    \
        g = ((Pixel >> 16) & 0xFF);           \
        b = ((Pixel >> 8) & 0xFF);            \
        a = (Pixel & 0xFF);                   \
    }
#ವ್ಯಾಖ್ಯಾನಿಸು RGBA_FROM_ARGB8888(Pixel, r, g, b, a) \
    {                                         \
        r = ((Pixel >> 16) & 0xFF);           \
        g = ((Pixel >> 8) & 0xFF);            \
        b = (Pixel & 0xFF);                   \
        a = (Pixel >> 24);                    \
    }
#ವ್ಯಾಖ್ಯಾನಿಸು RGBA_FROM_ABGR8888(Pixel, r, g, b, a) \
    {                                         \
        r = (Pixel & 0xFF);                   \
        g = ((Pixel >> 8) & 0xFF);            \
        b = ((Pixel >> 16) & 0xFF);           \
        a = (Pixel >> 24);                    \
    }
#ವ್ಯಾಖ್ಯಾನಿಸು RGBA_FROM_BGRA8888(Pixel, r, g, b, a) \
    {                                         \
        r = ((Pixel >> 8) & 0xFF);            \
        g = ((Pixel >> 16) & 0xFF);           \
        b = (Pixel >> 24);                    \
        a = (Pixel & 0xFF);                   \
    }
#ವ್ಯಾಖ್ಯಾನಿಸು RGBA_FROM_ARGB2101010(Pixel, r, g, b, a) \
    {                                            \
        r = ((Pixel >> 22) & 0xFF);              \
        g = ((Pixel >> 12) & 0xFF);              \
        b = ((Pixel >> 2) & 0xFF);               \
        a = SDL_expand_byte[2][(Pixel >> 30)];   \
    }
#ವ್ಯಾಖ್ಯಾನಿಸು RGBAFLOAT_FROM_ARGB2101010(Pixel, r, g, b, a)   \
    {                                                   \
        r = (ದಶಮಾಂಶ)((Pixel >> 20) & 0x3FF) / 1023.0f;   \
        g = (ದಶಮಾಂಶ)((Pixel >> 10) & 0x3FF) / 1023.0f;   \
        b = (ದಶಮಾಂಶ)((Pixel >> 0) & 0x3FF) / 1023.0f;    \
        a = (ದಶಮಾಂಶ)(Pixel >> 30) / 3.0f;                \
    }
#ವ್ಯಾಖ್ಯಾನಿಸು RGBA_FROM_ABGR2101010(Pixel, r, g, b, a) \
    {                                            \
        r = ((Pixel >> 2) & 0xFF);               \
        g = ((Pixel >> 12) & 0xFF);              \
        b = ((Pixel >> 22) & 0xFF);              \
        a = SDL_expand_byte[2][(Pixel >> 30)];   \
    }
#ವ್ಯಾಖ್ಯಾನಿಸು RGBAFLOAT_FROM_ABGR2101010(Pixel, r, g, b, a)   \
    {                                                   \
        r = (ದಶಮಾಂಶ)((Pixel >> 0) & 0x3FF) / 1023.0f;    \
        g = (ದಶಮಾಂಶ)((Pixel >> 10) & 0x3FF) / 1023.0f;   \
        b = (ದಶಮಾಂಶ)((Pixel >> 20) & 0x3FF) / 1023.0f;   \
        a = (ದಶಮಾಂಶ)(Pixel >> 30) / 3.0f;                \
    }
#ವ್ಯಾಖ್ಯಾನಿಸು DISEMBLE_RGBA(buf, bpp, fmt, Pixel, r, g, b, a) \
    ಮಾಡು {                                                \
        ಆಯ್ಕೆ (bpp) {                                  \
        ಸ್ಥಿತಿ 1:                                         \
            Pixel = *((Uint8 *)(buf));                  \
            RGBA_FROM_PIXEL(Pixel, fmt, r, g, b, a);    \
            ನಿಲ್ಲಿಸು;                                      \
                                                        \
        ಸ್ಥಿತಿ 2:                                         \
            Pixel = *((Uint16 *)(buf));                 \
            RGBA_FROM_PIXEL(Pixel, fmt, r, g, b, a);    \
            ನಿಲ್ಲಿಸು;                                      \
                                                        \
        ಸ್ಥಿತಿ 3:                                         \
        {                                               \
            Pixel = 0;                                  \
            r = GET_RGB24_COMPONENT(buf, fmt, Rshift);  \
            g = GET_RGB24_COMPONENT(buf, fmt, Gshift);  \
            b = GET_RGB24_COMPONENT(buf, fmt, Bshift);  \
            a = 0xFF;                                   \
        } ನಿಲ್ಲಿಸು;                                        \
                                                        \
        ಸ್ಥಿತಿ 4:                                         \
            Pixel = *((Uint32 *)(buf));                 \
            RGBA_FROM_PIXEL(Pixel, fmt, r, g, b, a);    \
            ನಿಲ್ಲಿಸು;                                      \
                                                        \
        ಪೂರ್ವನಿಯೋಜಿತ:                                        \
            /* stop gcc complaints */                   \
            Pixel = 0;                                  \
            r = g = b = a = 0;                          \
            ನಿಲ್ಲಿಸು;                                      \
        }                                               \
    } ಆಗ (0)

// FIXME: this isn't correct, especially for Alpha (maximum != 255)
#ವ್ಯಾಖ್ಯಾನಿಸು PIXEL_FROM_RGBA(Pixel, fmt, r, g, b, a)             \
    {                                                       \
        Pixel = ((r >> (8 - fmt->Rbits)) << fmt->Rshift) |  \
                ((g >> (8 - fmt->Gbits)) << fmt->Gshift) |  \
                ((b >> (8 - fmt->Bbits)) << fmt->Bshift) |  \
                ((a >> (8 - fmt->Abits)) << fmt->Ashift);   \
    }
#ವ್ಯಾಖ್ಯಾನಿಸು ASSEMBLE_RGBA(buf, bpp, fmt, r, g, b, a)       \
    {                                                  \
        ಆಯ್ಕೆ (bpp) {                                 \
        ಸ್ಥಿತಿ 1:                                        \
        {                                              \
            Uint8 _pixel;                              \
                                                       \
            PIXEL_FROM_RGBA(_pixel, fmt, r, g, b, a);  \
            *((Uint8 *)(buf)) = _pixel;                \
        } ನಿಲ್ಲಿಸು;                                       \
                                                       \
        ಸ್ಥಿತಿ 2:                                        \
        {                                              \
            Uint16 _pixel;                             \
                                                       \
            PIXEL_FROM_RGBA(_pixel, fmt, r, g, b, a);  \
            *((Uint16 *)(buf)) = _pixel;               \
        } ನಿಲ್ಲಿಸು;                                       \
                                                       \
        ಸ್ಥಿತಿ 3:                                        \
        {                                              \
            GET_RGB24_COMPONENT(buf, fmt, Rshift) = r; \
            GET_RGB24_COMPONENT(buf, fmt, Gshift) = g; \
            GET_RGB24_COMPONENT(buf, fmt, Bshift) = b; \
        } ನಿಲ್ಲಿಸು;                                       \
                                                       \
        ಸ್ಥಿತಿ 4:                                        \
        {                                              \
            Uint32 _pixel;                             \
                                                       \
            PIXEL_FROM_RGBA(_pixel, fmt, r, g, b, a);  \
            *((Uint32 *)(buf)) = _pixel;               \
        } ನಿಲ್ಲಿಸು;                                       \
        }                                              \
    }

// Convert any 32-bit 4-bpp pixel to ARGB format
#ವ್ಯಾಖ್ಯಾನಿಸು PIXEL_ಗಮ್ಯ_ARGB_PIXEL(src, srcfmt, dst)         \
    ಮಾಡು {                                              \
        Uint8 a, r, g, b;                         \
        RGBA_FROM_PIXEL(src, srcfmt, r, g, b, a); \
        dst = a << 24 | r << 16 | g << 8 | b;     \
    } ಆಗ (0)
// Blend a single color channel or alpha value
/* dC = ((sC * sA) + (dC * (255 - sA))) / 255 */
#ವ್ಯಾಖ್ಯಾನಿಸು ALPHA_BLEND_CHANNEL(sC, dC, sA)                  \
    ಮಾಡು {                                                 \
        Uint16 x;                                        \
        x = ((sC - dC) * sA) + ((dC << 8) - dC);         \
        x += 0x1U;                                       \
        x += x >> 8;                                     \
        dC = x >> 8;                                     \
    } ಆಗ (0)
// Perform a division by 255 after a multiplication of two 8-bit color channels
/* out = (sC * dC) / 255 */
#ವ್ಯಾಖ್ಯಾನಿಸು MULT_DIV_255(sC, dC, ಹೊರಹೋಗು) \
    ಮಾಡು {                          \
        Uint16 x = sC * dC;       \
        x += 0x1U;                \
        x += x >> 8;              \
        ಹೊರಹೋಗು = x >> 8;             \
    } ಆಗ (0)
// Blend the RGB values of two pixels with an alpha value
#ವ್ಯಾಖ್ಯಾನಿಸು ALPHA_BLEND_RGB(sR, sG, sB, A, dR, dG, dB)            \
    ಮಾಡು {                                                      \
        ALPHA_BLEND_CHANNEL(sR, dR, A);                       \
        ALPHA_BLEND_CHANNEL(sG, dG, A);                       \
        ALPHA_BLEND_CHANNEL(sB, dB, A);                       \
    } ಆಗ (0)

// Blend two 8888 pixels with the same format
/* Calculates dst = ((src * factor) + (dst * (255 - factor))) / 255 */
// FIXME: SDL_SIZE_MAX might not be an integer literal
#ಆದರೆ defined(SIZE_MAX) && (SIZE_MAX == 0xffffffffffffffff)
#ವ್ಯಾಖ್ಯಾನಿಸು ಗುಣಕ_BLEND_8888(src, dst, ಗುಣಕ)                        \
    ಮಾಡು {                                                           \
        Uint64 src64 = src;                                        \
        src64 = (src64 | (src64 << 24)) & 0x00FF00FF00FF00FF;      \
                                                                   \
        Uint64 dst64 = dst;                                        \
        dst64 = (dst64 | (dst64 << 24)) & 0x00FF00FF00FF00FF;      \
                                                                   \
        dst64 = ((src64 - dst64) * ಗುಣಕ) + (dst64 << 8) - dst64; \
        dst64 += 0x0001000100010001;                               \
        dst64 += (dst64 >> 8) & 0x00FF00FF00FF00FF;                \
        dst64 &= 0xFF00FF00FF00FF00;                               \
                                                                   \
        dst = (Uint32)((dst64 >> 8) | (dst64 >> 32));              \
    } ಆಗ (0)
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು ಗುಣಕ_BLEND_8888(src, dst, ಗುಣಕ)                               \
    ಮಾಡು {                                                                  \
        Uint32 src02 = src & 0x00FF00FF;                                  \
        Uint32 dst02 = dst & 0x00FF00FF;                                  \
                                                                          \
        Uint32 src13 = (src >> 8) & 0x00FF00FF;                           \
        Uint32 dst13 = (dst >> 8) & 0x00FF00FF;                           \
                                                                          \
        Uint32 res02 = ((src02 - dst02) * ಗುಣಕ) + (dst02 << 8) - dst02; \
        res02 += 0x00010001;                                              \
        res02 += (res02 >> 8) & 0x00FF00FF;                               \
        res02 = (res02 >> 8) & 0x00FF00FF;                                \
                                                                          \
        Uint32 res13 = ((src13 - dst13) * ಗುಣಕ) + (dst13 << 8) - dst13; \
        res13 += 0x00010001;                                              \
        res13 += (res13 >> 8) & 0x00FF00FF;                               \
        res13 &= 0xFF00FF00;                                              \
        dst = res02 | res13;                                              \
    } ಆಗ (0)
#ಆದರೆ_ಅಂತ್ಯ

// Alpha blend two 8888 pixels with the same formats.
#ವ್ಯಾಖ್ಯಾನಿಸು ALPHA_BLEND_8888(src, dst, fmt)            \
    ಮಾಡು {                                           \
        Uint32 srcA = (src >> fmt->Ashift) & 0xFF; \
        Uint32 tmp = src | fmt->Amask;             \
        ಗುಣಕ_BLEND_8888(tmp, dst, srcA);         \
    } ಆಗ (0)

// Alpha blend two 8888 pixels with differing formats.
#ವ್ಯಾಖ್ಯಾನಿಸು ALPHA_BLEND_SWIZZLE_8888(src, dst, srcfmt, dstfmt)                  \
    ಮಾಡು {                                                                    \
        Uint32 srcA = (src >> srcfmt->Ashift) & 0xFF;                       \
        Uint32 tmp = (((src >> srcfmt->Rshift) & 0xFF) << dstfmt->Rshift) | \
                     (((src >> srcfmt->Gshift) & 0xFF) << dstfmt->Gshift) | \
                     (((src >> srcfmt->Bshift) & 0xFF) << dstfmt->Bshift) | \
                     dstfmt->Amask;                                         \
        ಗುಣಕ_BLEND_8888(tmp, dst, srcA);                                  \
    } ಆಗ (0)
// Blend the RGBA values of two pixels
#ವ್ಯಾಖ್ಯಾನಿಸು ALPHA_BLEND_RGBA(sR, sG, sB, sA, dR, dG, dB, dA) \
    ಮಾಡು {                                                 \
        ALPHA_BLEND_CHANNEL(sR, dR, sA);                 \
        ALPHA_BLEND_CHANNEL(sG, dG, sA);                 \
        ALPHA_BLEND_CHANNEL(sB, dB, sA);                 \
        ALPHA_BLEND_CHANNEL(255, dA, sA);                \
    } ಆಗ (0)

// This is a very useful loop for optimizing blitters
#ಆದರೆ defined(_MSC_VER) && (_MSC_VER == 1300)
// There's a bug in the Visual C++ 7 optimizer when compiling this code
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು USE_DUFFS_LOOP
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿಸು DUFFS_LOOP1(pixel_copy_increment, ಅಗಲ) \
    {                                            \
        ಪೂರ್ಣಾಂಕ n;                                   \
        ಗಾಗಿ (n = ಅಗಲ; n > 0; --n) {            \
            pixel_copy_increment;                \
        }                                        \
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ USE_DUFFS_LOOP

// 8-times unrolled loop
#ವ್ಯಾಖ್ಯಾನಿಸು DUFFS_LOOP8(pixel_copy_increment, ಅಗಲ) \
    {                                            \
        ಪೂರ್ಣಾಂಕ n = (ಅಗಲ + 7) / 8;                 \
        ಆಯ್ಕೆ (ಅಗಲ & 7) {                     \
        ಸ್ಥಿತಿ 0:                                  \
            ಮಾಡು {                                 \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            ಸ್ಥಿತಿ 7:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            ಸ್ಥಿತಿ 6:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            ಸ್ಥಿತಿ 5:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            ಸ್ಥಿತಿ 4:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            ಸ್ಥಿತಿ 3:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            ಸ್ಥಿತಿ 2:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            ಸ್ಥಿತಿ 1:                              \
                pixel_copy_increment;            \
            } ಆಗ (--n > 0);                   \
        }                                        \
    }

// 4-times unrolled loop
#ವ್ಯಾಖ್ಯಾನಿಸು DUFFS_LOOP4(pixel_copy_increment, ಅಗಲ) \
    {                                            \
        ಪೂರ್ಣಾಂಕ n = (ಅಗಲ + 3) / 4;                 \
        ಆಯ್ಕೆ (ಅಗಲ & 3) {                     \
        ಸ್ಥಿತಿ 0:                                  \
            ಮಾಡು {                                 \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            ಸ್ಥಿತಿ 3:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            ಸ್ಥಿತಿ 2:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            ಸ್ಥಿತಿ 1:                              \
                pixel_copy_increment;            \
            } ಆಗ (--n > 0);                   \
        }                                        \
    }

// 2-times unrolled loop
#ವ್ಯಾಖ್ಯಾನಿಸು DUFFS_LOOP2(pixel_copy_increment, ಅಗಲ) \
    {                                            \
        ಪೂರ್ಣಾಂಕ n = (ಅಗಲ + 1) / 2;                 \
        ಆಯ್ಕೆ (ಅಗಲ & 1) {                     \
        ಸ್ಥಿತಿ 0:                                  \
            ಮಾಡು {                                 \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            ಸ್ಥಿತಿ 1:                              \
                pixel_copy_increment;            \
            } ಆಗ (--n > 0);                   \
        }                                        \
    }

// Use the 4-times version of the loop by default
#ವ್ಯಾಖ್ಯಾನಿಸು DUFFS_LOOP(pixel_copy_increment, ಅಗಲ) \
    DUFFS_LOOP4(pixel_copy_increment, ಅಗಲ)
// Use the 8-times version of the loop for simple routines
#ವ್ಯಾಖ್ಯಾನಿಸು DUFFS_LOOP_TRIVIAL(pixel_copy_increment, ಅಗಲ) \
    DUFFS_LOOP8(pixel_copy_increment, ಅಗಲ)

// Special version of Duff's device for even more optimization
#ವ್ಯಾಖ್ಯಾನಿಸು DUFFS_LOOP_124(pixel_copy_increment1,        \
                       pixel_copy_increment2,        \
                       pixel_copy_increment4, ಅಗಲ) \
    {                                                \
        ಪೂರ್ಣಾಂಕ n = ಅಗಲ;                               \
        ಆದರೆ (n & 1) {                                 \
            pixel_copy_increment1;                   \
            n -= 1;                                  \
        }                                            \
        ಆದರೆ (n & 2) {                                 \
            pixel_copy_increment2;                   \
            n -= 2;                                  \
        }                                            \
        ಆದರೆ (n & 4) {                                 \
            pixel_copy_increment4;                   \
            n -= 4;                                  \
        }                                            \
        ಆದರೆ (n) {                                     \
            n /= 8;                                  \
            ಮಾಡು {                                     \
                pixel_copy_increment4;               \
                pixel_copy_increment4;               \
            } ಆಗ (--n > 0);                       \
        }                                            \
    }

#ಇಲ್ಲದಿದ್ದರೆ

// Don't use Duff's device to unroll loops
#ವ್ಯಾಖ್ಯಾನಿಸು DUFFS_LOOP(pixel_copy_increment, ಅಗಲ) \
    DUFFS_LOOP1(pixel_copy_increment, ಅಗಲ)
#ವ್ಯಾಖ್ಯಾನಿಸು DUFFS_LOOP_TRIVIAL(pixel_copy_increment, ಅಗಲ) \
    DUFFS_LOOP1(pixel_copy_increment, ಅಗಲ)
#ವ್ಯಾಖ್ಯಾನಿಸು DUFFS_LOOP8(pixel_copy_increment, ಅಗಲ) \
    DUFFS_LOOP1(pixel_copy_increment, ಅಗಲ)
#ವ್ಯಾಖ್ಯಾನಿಸು DUFFS_LOOP4(pixel_copy_increment, ಅಗಲ) \
    DUFFS_LOOP1(pixel_copy_increment, ಅಗಲ)
#ವ್ಯಾಖ್ಯಾನಿಸು DUFFS_LOOP2(pixel_copy_increment, ಅಗಲ) \
    DUFFS_LOOP1(pixel_copy_increment, ಅಗಲ)
#ವ್ಯಾಖ್ಯಾನಿಸು DUFFS_LOOP_124(pixel_copy_increment1,        \
                       pixel_copy_increment2,        \
                       pixel_copy_increment4, ಅಗಲ) \
    DUFFS_LOOP1(pixel_copy_increment1, ಅಗಲ)

#ಆದರೆ_ಅಂತ್ಯ // USE_DUFFS_LOOP

#ಆದರೆ defined(_MSC_VER) && (_MSC_VER >= 600)
#ಸೂಚನೆ warning(disable : 4244) // '=': conversion from 'X' to 'Y', possible loss of data
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ // SDL_blit_h_
