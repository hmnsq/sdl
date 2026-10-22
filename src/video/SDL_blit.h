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

#اگر_غیر_تعریف_شدہ SDL_blit_h_
#تعریف_کرو SDL_blit_h_

// Table to do pixel byte expansion
خارجی ثابت Uint8 *SDL_expand_byte[9];
خارجی ثابت Uint16 SDL_expand_byte_10[];

// SDL blit copy flags
#تعریف_کرو SDL_COPY_MODULATE_COLOR         0x00000001
#تعریف_کرو SDL_COPY_MODULATE_ALPHA         0x00000002
#تعریف_کرو SDL_COPY_MODULATE_نقاب		(SDL_COPY_MODULATE_COLOR | SDL_COPY_MODULATE_ALPHA)
#تعریف_کرو SDL_COPY_BLEND                  0x00000010
#تعریف_کرو SDL_COPY_BLEND_PREMULTIPLIED    0x00000020
#تعریف_کرو SDL_COPY_جوڑو                    0x00000040
#تعریف_کرو SDL_COPY_جوڑو_PREMULTIPLIED      0x00000080
#تعریف_کرو SDL_COPY_MOD                    0x00000100
#تعریف_کرو SDL_COPY_MUL                    0x00000200
#تعریف_کرو SDL_COPY_BLEND_نقاب		(SDL_COPY_BLEND | SDL_COPY_BLEND_PREMULTIPLIED | SDL_COPY_جوڑو | SDL_COPY_جوڑو_PREMULTIPLIED | SDL_COPY_MOD | SDL_COPY_MUL)
#تعریف_کرو SDL_COPY_COLORKEY               0x00000400
#تعریف_کرو SDL_COPY_قریب_ترین                0x00000800
#تعریف_کرو SDL_COPY_RLE_DESIRED            0x00001000
#تعریف_کرو SDL_COPY_RLE_COLORKEY           0x00002000
#تعریف_کرو SDL_COPY_RLE_ALPHAKEY           0x00004000
#تعریف_کرو SDL_COPY_RLE_نقاب               (SDL_COPY_RLE_DESIRED | SDL_COPY_RLE_COLORKEY | SDL_COPY_RLE_ALPHAKEY)

// SDL blit CPU flags
#تعریف_کرو SDL_CPU_ANY                0x00000000
#تعریف_کرو SDL_CPU_MMX                0x00000001
#تعریف_کرو SDL_CPU_SSE                0x00000002
#تعریف_کرو SDL_CPU_SSE2               0x00000004
#تعریف_کرو SDL_CPU_ALTIVEC_PREFETCH   0x00000008
#تعریف_کرو SDL_CPU_ALTIVEC_NOPREFETCH 0x00000010

قسمتعریف ساخت
{
    SDL_Surface *src_surface;
    Uint8 *src;
    صحیح src_w, src_h;
    صحیح src_pitch;
    صحیح src_skip;
    صحیح leading_skip;
    SDL_Surface *dst_surface;
    Uint8 *dst;
    صحیح dst_w, dst_h;
    صحیح dst_pitch;
    صحیح dst_skip;
    ثابت SDL_PixelFormatDetails *src_fmt;
    ثابت SDL_Palette *src_pal;
    ثابت SDL_PixelFormatDetails *dst_fmt;
    ثابت SDL_Palette *dst_pal;
    Uint8 *جدول;
    SDL_Hash_جدول *palette_map;
    صحیح flags;
    Uint32 colorkey;
    Uint8 r, g, b, a;
} SDL_BlitInfo;

قسمتعریف خالی (*SDL_BlitFunc)(SDL_BlitInfo *info);

قسمتعریف ساخت
{
    SDL_PixelFormat src_format;
    SDL_PixelFormat dst_format;
    صحیح flags;
    SDL_BlitFunc func;
} SDL_Blit_Func_اندراج;

قسمتعریف bool (SDLCALL *SDL_Blit) (ساخت SDL_Surface *src, ثابت SDL_Rect *srcrect, ساخت SDL_Surface *dst, ثابت SDL_Rect *dstrect);

// Blit mapping definition
قسمتعریف ساخت SDL_BlitMap
{
    صحیح شناختی_عنصر;
    SDL_Blit blit;
    خالی *ڈیٹا;
    SDL_BlitInfo info;

    /* the version count matches the destination; mismatch indicates
       an invalid mapping */
    Uint32 dst_palette_نسخہ;
    Uint32 src_palette_نسخہ;
} SDL_BlitMap;

// Functions found in SDL_blit.c
خارجی bool SDL_CalculateBlit(SDL_Surface *surface, SDL_Surface *dst);

/* Functions found in SDL_blit_*.c */
خارجی SDL_BlitFunc SDL_CalculateBlit0(SDL_Surface *surface);
خارجی SDL_BlitFunc SDL_CalculateBlit1(SDL_Surface *surface);
خارجی SDL_BlitFunc SDL_CalculateBlitN(SDL_Surface *surface);
خارجی SDL_BlitFunc SDL_CalculateBlitA(SDL_Surface *surface);

/*
 * Useful macros for blitting routines
 */

#اگر_تعریف_شدہ __GNUC__
#تعریف_کرو DECLARE_ALIGNED(t, v, a) t __attribute__((aligned(a))) v
#وگرنہ_اگر defined(_MSC_VER)
#تعریف_کرو DECLARE_ALIGNED(t, v, a) __declspec(align(a)) t v
#ورنہ
#تعریف_کرو DECLARE_ALIGNED(t, v, a) t v
#اگر_ختم

// Load pixel of the specified format from a buffer and get its R-G-B values
#تعریف_کرو RGB_FROM_PIXEL(Pixel, fmt, r, g, b)                                     \
    {                                                                           \
        r = SDL_expand_byte[fmt->Rbits][((Pixel & fmt->Rmask) >> fmt->Rshift)]; \
        g = SDL_expand_byte[fmt->Gbits][((Pixel & fmt->Gmask) >> fmt->Gshift)]; \
        b = SDL_expand_byte[fmt->Bbits][((Pixel & fmt->Bmask) >> fmt->Bshift)]; \
    }
#تعریف_کرو RGB_FROM_RGB565(Pixel, r, g, b)                   \
    {                                                     \
        r = SDL_expand_byte[5][((Pixel & 0xF800) >> 11)]; \
        g = SDL_expand_byte[6][((Pixel & 0x07E0) >> 5)];  \
        b = SDL_expand_byte[5][(Pixel & 0x001F)];         \
    }
#تعریف_کرو RGB_FROM_RGB555(Pixel, r, g, b)                   \
    {                                                     \
        r = SDL_expand_byte[5][((Pixel & 0x7C00) >> 10)]; \
        g = SDL_expand_byte[5][((Pixel & 0x03E0) >> 5)];  \
        b = SDL_expand_byte[5][(Pixel & 0x001F)];         \
    }
#تعریف_کرو RGB_FROM_XRGB8888(Pixel, r, g, b) \
    {                                   \
        r = ((Pixel & 0xFF0000) >> 16); \
        g = ((Pixel & 0xFF00) >> 8);    \
        b = (Pixel & 0xFF);             \
    }
#اگر SDL_BYTEORDER == SDL_LIL_ENDIAN
#تعریف_کرو GET_RGB24(B) (B[2] << 16) | (B[1] << 8) | B[0]
#ورنہ
#تعریف_کرو GET_RGB24(B) (B[0] << 16) | (B[1] << 8) | B[2]
#اگر_ختم
#تعریف_کرو RETRIEVE_RGB_PIXEL(buf, bpp, Pixel)                \
    کرو {                                                   \
        انتخاب (bpp) {                                     \
        حالت 1:                                            \
            Pixel = *((Uint8 *)(buf));                     \
            توڑو;                                         \
                                                           \
        حالت 2:                                            \
            Pixel = *((Uint16 *)(buf));                    \
            توڑو;                                         \
                                                           \
        حالت 3:                                            \
        {                                                  \
            Uint8 *B = (Uint8 *)(buf);                     \
            Pixel = GET_RGB24(B);                          \
        } توڑو;                                           \
                                                           \
        حالت 4:                                            \
            Pixel = *((Uint32 *)(buf));                    \
            توڑو;                                         \
                                                           \
        طےشدہ:                                           \
            Pixel = 0; /* stop gcc complaints */           \
            توڑو;                                         \
        }                                                  \
    } جب (0)

#اگر SDL_BYTEORDER == SDL_LIL_ENDIAN
#تعریف_کرو GET_RGB24_COMPONENT(buf, fmt, سرکاؤ) *((buf) + fmt->سرکاؤ / 8)
#ورنہ
#تعریف_کرو GET_RGB24_COMPONENT(buf, fmt, سرکاؤ) *((buf) + 2 - fmt->سرکاؤ / 8)
#اگر_ختم
#تعریف_کرو DISEMBLE_RGB(buf, bpp, fmt, Pixel, r, g, b)    \
    کرو {                                               \
        انتخاب (bpp) {                                 \
        حالت 1:                                        \
            Pixel = *((Uint8 *)(buf));                 \
            RGB_FROM_PIXEL(Pixel, fmt, r, g, b);       \
            توڑو;                                     \
                                                       \
        حالت 2:                                        \
            Pixel = *((Uint16 *)(buf));                \
            RGB_FROM_PIXEL(Pixel, fmt, r, g, b);       \
            توڑو;                                     \
                                                       \
        حالت 3:                                        \
        {                                              \
            Pixel = 0;                                 \
            r = GET_RGB24_COMPONENT(buf, fmt, Rshift); \
            g = GET_RGB24_COMPONENT(buf, fmt, Gshift); \
            b = GET_RGB24_COMPONENT(buf, fmt, Bshift); \
        } توڑو;                                       \
                                                       \
        حالت 4:                                        \
            Pixel = *((Uint32 *)(buf));                \
            RGB_FROM_PIXEL(Pixel, fmt, r, g, b);       \
            توڑو;                                     \
                                                       \
        طےشدہ:                                       \
            /* stop gcc complaints */                  \
            Pixel = 0;                                 \
            r = g = b = 0;                             \
            توڑو;                                     \
        }                                              \
    } جب (0)

// Assemble R-G-B values into a specified pixel format and store them
#تعریف_کرو PIXEL_FROM_RGB(Pixel, fmt, r, g, b)                 \
    {                                                       \
        Pixel = ((r >> (8 - fmt->Rbits)) << fmt->Rshift) |  \
                ((g >> (8 - fmt->Gbits)) << fmt->Gshift) |  \
                ((b >> (8 - fmt->Bbits)) << fmt->Bshift) |  \
                fmt->Amask;                                 \
    }
#تعریف_کرو RGB332_FROM_RGB(Pixel, r, g, b)                        \
    {                                                          \
        Pixel = (Uint8)(((r >> 5) << 5) | ((g >> 5) << 2) | (b >> 6)); \
    }
#تعریف_کرو RGB565_FROM_RGB(Pixel, r, g, b)                        \
    {                                                          \
        Pixel = (Uint16)(((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3)); \
    }
#تعریف_کرو RGB555_FROM_RGB(Pixel, r, g, b)                        \
    {                                                          \
        Pixel = (Uint16)(((r >> 3) << 10) | ((g >> 3) << 5) | (b >> 3)); \
    }
#تعریف_کرو XRGB8888_FROM_RGB(Pixel, r, g, b)   \
    {                                     \
        Pixel = (r << 16) | (g << 8) | b; \
    }
#تعریف_کرو ARGB8888_FROM_RGBA(Pixel, r, g, b, a)         \
    {                                                 \
        Pixel = (a << 24) | (r << 16) | (g << 8) | b; \
    }
#تعریف_کرو RGBA8888_FROM_RGBA(Pixel, r, g, b, a)         \
    {                                                 \
        Pixel = (r << 24) | (g << 16) | (b << 8) | a; \
    }
#تعریف_کرو ABGR8888_FROM_RGBA(Pixel, r, g, b, a)         \
    {                                                 \
        Pixel = (a << 24) | (b << 16) | (g << 8) | r; \
    }
#تعریف_کرو BGRA8888_FROM_RGBA(Pixel, r, g, b, a)         \
    {                                                 \
        Pixel = (b << 24) | (g << 16) | (r << 8) | a; \
    }
#تعریف_کرو ARGB2101010_FROM_RGBA(Pixel, r, g, b, a)       \
    {                                                  \
        r = r ? ((r << 2) | 0x3) : 0;                  \
        g = g ? ((g << 2) | 0x3) : 0;                  \
        b = b ? ((b << 2) | 0x3) : 0;                  \
        a = (a * 3) / 255;                             \
        Pixel = (a << 30) | (r << 20) | (g << 10) | b; \
    }
#تعریف_کرو ARGB2101010_FROM_RGBAFLOAT(Pixel, r, g, b, a) \
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
#تعریف_کرو ABGR2101010_FROM_RGBA(Pixel, r, g, b, a)       \
    {                                                  \
        r = r ? ((r << 2) | 0x3) : 0;                  \
        g = g ? ((g << 2) | 0x3) : 0;                  \
        b = b ? ((b << 2) | 0x3) : 0;                  \
        a = (a * 3) / 255;                             \
        Pixel = (a << 30) | (b << 20) | (g << 10) | r; \
    }
#تعریف_کرو ABGR2101010_FROM_RGBAFLOAT(Pixel, r, g, b, a) \
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
#تعریف_کرو ASSEMBLE_RGB(buf, bpp, fmt, r, g, b)           \
    {                                                  \
        انتخاب (bpp) {                                 \
        حالت 1:                                        \
        {                                              \
            Uint8 _pixel;                              \
                                                       \
            PIXEL_FROM_RGB(_pixel, fmt, r, g, b);      \
            *((Uint8 *)(buf)) = _pixel;                \
        } توڑو;                                       \
                                                       \
        حالت 2:                                        \
        {                                              \
            Uint16 _pixel;                             \
                                                       \
            PIXEL_FROM_RGB(_pixel, fmt, r, g, b);      \
            *((Uint16 *)(buf)) = _pixel;               \
        } توڑو;                                       \
                                                       \
        حالت 3:                                        \
        {                                              \
            GET_RGB24_COMPONENT(buf, fmt, Rshift) = r; \
            GET_RGB24_COMPONENT(buf, fmt, Gshift) = g; \
            GET_RGB24_COMPONENT(buf, fmt, Bshift) = b; \
        } توڑو;                                       \
                                                       \
        حالت 4:                                        \
        {                                              \
            Uint32 _pixel;                             \
                                                       \
            PIXEL_FROM_RGB(_pixel, fmt, r, g, b);      \
            *((Uint32 *)(buf)) = _pixel;               \
        } توڑو;                                       \
        }                                              \
    }

// FIXME: Should we rescale alpha into 0..255 here?
#تعریف_کرو RGBA_FROM_PIXEL(Pixel, fmt, r, g, b, a)                                 \
    {                                                                           \
        r = SDL_expand_byte[fmt->Rbits][((Pixel & fmt->Rmask) >> fmt->Rshift)]; \
        g = SDL_expand_byte[fmt->Gbits][((Pixel & fmt->Gmask) >> fmt->Gshift)]; \
        b = SDL_expand_byte[fmt->Bbits][((Pixel & fmt->Bmask) >> fmt->Bshift)]; \
        a = SDL_expand_byte[fmt->Abits][((Pixel & fmt->Amask) >> fmt->Ashift)]; \
    }
#تعریف_کرو RGBA_FROM_8888(Pixel, fmt, r, g, b, a)   \
    {                                            \
        r = (Pixel & fmt->Rmask) >> fmt->Rshift; \
        g = (Pixel & fmt->Gmask) >> fmt->Gshift; \
        b = (Pixel & fmt->Bmask) >> fmt->Bshift; \
        a = (Pixel & fmt->Amask) >> fmt->Ashift; \
    }
#تعریف_کرو RGBA_FROM_RGBA8888(Pixel, r, g, b, a) \
    {                                         \
        r = (Pixel >> 24);                    \
        g = ((Pixel >> 16) & 0xFF);           \
        b = ((Pixel >> 8) & 0xFF);            \
        a = (Pixel & 0xFF);                   \
    }
#تعریف_کرو RGBA_FROM_ARGB8888(Pixel, r, g, b, a) \
    {                                         \
        r = ((Pixel >> 16) & 0xFF);           \
        g = ((Pixel >> 8) & 0xFF);            \
        b = (Pixel & 0xFF);                   \
        a = (Pixel >> 24);                    \
    }
#تعریف_کرو RGBA_FROM_ABGR8888(Pixel, r, g, b, a) \
    {                                         \
        r = (Pixel & 0xFF);                   \
        g = ((Pixel >> 8) & 0xFF);            \
        b = ((Pixel >> 16) & 0xFF);           \
        a = (Pixel >> 24);                    \
    }
#تعریف_کرو RGBA_FROM_BGRA8888(Pixel, r, g, b, a) \
    {                                         \
        r = ((Pixel >> 8) & 0xFF);            \
        g = ((Pixel >> 16) & 0xFF);           \
        b = (Pixel >> 24);                    \
        a = (Pixel & 0xFF);                   \
    }
#تعریف_کرو RGBA_FROM_ARGB2101010(Pixel, r, g, b, a) \
    {                                            \
        r = ((Pixel >> 22) & 0xFF);              \
        g = ((Pixel >> 12) & 0xFF);              \
        b = ((Pixel >> 2) & 0xFF);               \
        a = SDL_expand_byte[2][(Pixel >> 30)];   \
    }
#تعریف_کرو RGBAFLOAT_FROM_ARGB2101010(Pixel, r, g, b, a)   \
    {                                                   \
        r = (اعشاری)((Pixel >> 20) & 0x3FF) / 1023.0f;   \
        g = (اعشاری)((Pixel >> 10) & 0x3FF) / 1023.0f;   \
        b = (اعشاری)((Pixel >> 0) & 0x3FF) / 1023.0f;    \
        a = (اعشاری)(Pixel >> 30) / 3.0f;                \
    }
#تعریف_کرو RGBA_FROM_ABGR2101010(Pixel, r, g, b, a) \
    {                                            \
        r = ((Pixel >> 2) & 0xFF);               \
        g = ((Pixel >> 12) & 0xFF);              \
        b = ((Pixel >> 22) & 0xFF);              \
        a = SDL_expand_byte[2][(Pixel >> 30)];   \
    }
#تعریف_کرو RGBAFLOAT_FROM_ABGR2101010(Pixel, r, g, b, a)   \
    {                                                   \
        r = (اعشاری)((Pixel >> 0) & 0x3FF) / 1023.0f;    \
        g = (اعشاری)((Pixel >> 10) & 0x3FF) / 1023.0f;   \
        b = (اعشاری)((Pixel >> 20) & 0x3FF) / 1023.0f;   \
        a = (اعشاری)(Pixel >> 30) / 3.0f;                \
    }
#تعریف_کرو DISEMBLE_RGBA(buf, bpp, fmt, Pixel, r, g, b, a) \
    کرو {                                                \
        انتخاب (bpp) {                                  \
        حالت 1:                                         \
            Pixel = *((Uint8 *)(buf));                  \
            RGBA_FROM_PIXEL(Pixel, fmt, r, g, b, a);    \
            توڑو;                                      \
                                                        \
        حالت 2:                                         \
            Pixel = *((Uint16 *)(buf));                 \
            RGBA_FROM_PIXEL(Pixel, fmt, r, g, b, a);    \
            توڑو;                                      \
                                                        \
        حالت 3:                                         \
        {                                               \
            Pixel = 0;                                  \
            r = GET_RGB24_COMPONENT(buf, fmt, Rshift);  \
            g = GET_RGB24_COMPONENT(buf, fmt, Gshift);  \
            b = GET_RGB24_COMPONENT(buf, fmt, Bshift);  \
            a = 0xFF;                                   \
        } توڑو;                                        \
                                                        \
        حالت 4:                                         \
            Pixel = *((Uint32 *)(buf));                 \
            RGBA_FROM_PIXEL(Pixel, fmt, r, g, b, a);    \
            توڑو;                                      \
                                                        \
        طےشدہ:                                        \
            /* stop gcc complaints */                   \
            Pixel = 0;                                  \
            r = g = b = a = 0;                          \
            توڑو;                                      \
        }                                               \
    } جب (0)

// FIXME: this isn't correct, especially for Alpha (maximum != 255)
#تعریف_کرو PIXEL_FROM_RGBA(Pixel, fmt, r, g, b, a)             \
    {                                                       \
        Pixel = ((r >> (8 - fmt->Rbits)) << fmt->Rshift) |  \
                ((g >> (8 - fmt->Gbits)) << fmt->Gshift) |  \
                ((b >> (8 - fmt->Bbits)) << fmt->Bshift) |  \
                ((a >> (8 - fmt->Abits)) << fmt->Ashift);   \
    }
#تعریف_کرو ASSEMBLE_RGBA(buf, bpp, fmt, r, g, b, a)       \
    {                                                  \
        انتخاب (bpp) {                                 \
        حالت 1:                                        \
        {                                              \
            Uint8 _pixel;                              \
                                                       \
            PIXEL_FROM_RGBA(_pixel, fmt, r, g, b, a);  \
            *((Uint8 *)(buf)) = _pixel;                \
        } توڑو;                                       \
                                                       \
        حالت 2:                                        \
        {                                              \
            Uint16 _pixel;                             \
                                                       \
            PIXEL_FROM_RGBA(_pixel, fmt, r, g, b, a);  \
            *((Uint16 *)(buf)) = _pixel;               \
        } توڑو;                                       \
                                                       \
        حالت 3:                                        \
        {                                              \
            GET_RGB24_COMPONENT(buf, fmt, Rshift) = r; \
            GET_RGB24_COMPONENT(buf, fmt, Gshift) = g; \
            GET_RGB24_COMPONENT(buf, fmt, Bshift) = b; \
        } توڑو;                                       \
                                                       \
        حالت 4:                                        \
        {                                              \
            Uint32 _pixel;                             \
                                                       \
            PIXEL_FROM_RGBA(_pixel, fmt, r, g, b, a);  \
            *((Uint32 *)(buf)) = _pixel;               \
        } توڑو;                                       \
        }                                              \
    }

// Convert any 32-bit 4-bpp pixel to ARGB format
#تعریف_کرو PIXEL_مقصد_ARGB_PIXEL(src, srcfmt, dst)         \
    کرو {                                              \
        Uint8 a, r, g, b;                         \
        RGBA_FROM_PIXEL(src, srcfmt, r, g, b, a); \
        dst = a << 24 | r << 16 | g << 8 | b;     \
    } جب (0)
// Blend a single color channel or alpha value
/* dC = ((sC * sA) + (dC * (255 - sA))) / 255 */
#تعریف_کرو ALPHA_BLEND_CHANNEL(sC, dC, sA)                  \
    کرو {                                                 \
        Uint16 x;                                        \
        x = ((sC - dC) * sA) + ((dC << 8) - dC);         \
        x += 0x1U;                                       \
        x += x >> 8;                                     \
        dC = x >> 8;                                     \
    } جب (0)
// Perform a division by 255 after a multiplication of two 8-bit color channels
/* out = (sC * dC) / 255 */
#تعریف_کرو MULT_DIV_255(sC, dC, برآمد) \
    کرو {                          \
        Uint16 x = sC * dC;       \
        x += 0x1U;                \
        x += x >> 8;              \
        برآمد = x >> 8;             \
    } جب (0)
// Blend the RGB values of two pixels with an alpha value
#تعریف_کرو ALPHA_BLEND_RGB(sR, sG, sB, A, dR, dG, dB)            \
    کرو {                                                      \
        ALPHA_BLEND_CHANNEL(sR, dR, A);                       \
        ALPHA_BLEND_CHANNEL(sG, dG, A);                       \
        ALPHA_BLEND_CHANNEL(sB, dB, A);                       \
    } جب (0)

// Blend two 8888 pixels with the same format
/* Calculates dst = ((src * factor) + (dst * (255 - factor))) / 255 */
// FIXME: SDL_SIZE_MAX might not be an integer literal
#اگر defined(SIZE_MAX) && (SIZE_MAX == 0xffffffffffffffff)
#تعریف_کرو ضربی_عدد_BLEND_8888(src, dst, ضربی_عدد)                        \
    کرو {                                                           \
        Uint64 src64 = src;                                        \
        src64 = (src64 | (src64 << 24)) & 0x00FF00FF00FF00FF;      \
                                                                   \
        Uint64 dst64 = dst;                                        \
        dst64 = (dst64 | (dst64 << 24)) & 0x00FF00FF00FF00FF;      \
                                                                   \
        dst64 = ((src64 - dst64) * ضربی_عدد) + (dst64 << 8) - dst64; \
        dst64 += 0x0001000100010001;                               \
        dst64 += (dst64 >> 8) & 0x00FF00FF00FF00FF;                \
        dst64 &= 0xFF00FF00FF00FF00;                               \
                                                                   \
        dst = (Uint32)((dst64 >> 8) | (dst64 >> 32));              \
    } جب (0)
#ورنہ
#تعریف_کرو ضربی_عدد_BLEND_8888(src, dst, ضربی_عدد)                               \
    کرو {                                                                  \
        Uint32 src02 = src & 0x00FF00FF;                                  \
        Uint32 dst02 = dst & 0x00FF00FF;                                  \
                                                                          \
        Uint32 src13 = (src >> 8) & 0x00FF00FF;                           \
        Uint32 dst13 = (dst >> 8) & 0x00FF00FF;                           \
                                                                          \
        Uint32 res02 = ((src02 - dst02) * ضربی_عدد) + (dst02 << 8) - dst02; \
        res02 += 0x00010001;                                              \
        res02 += (res02 >> 8) & 0x00FF00FF;                               \
        res02 = (res02 >> 8) & 0x00FF00FF;                                \
                                                                          \
        Uint32 res13 = ((src13 - dst13) * ضربی_عدد) + (dst13 << 8) - dst13; \
        res13 += 0x00010001;                                              \
        res13 += (res13 >> 8) & 0x00FF00FF;                               \
        res13 &= 0xFF00FF00;                                              \
        dst = res02 | res13;                                              \
    } جب (0)
#اگر_ختم

// Alpha blend two 8888 pixels with the same formats.
#تعریف_کرو ALPHA_BLEND_8888(src, dst, fmt)            \
    کرو {                                           \
        Uint32 srcA = (src >> fmt->Ashift) & 0xFF; \
        Uint32 tmp = src | fmt->Amask;             \
        ضربی_عدد_BLEND_8888(tmp, dst, srcA);         \
    } جب (0)

// Alpha blend two 8888 pixels with differing formats.
#تعریف_کرو ALPHA_BLEND_SWIZZLE_8888(src, dst, srcfmt, dstfmt)                  \
    کرو {                                                                    \
        Uint32 srcA = (src >> srcfmt->Ashift) & 0xFF;                       \
        Uint32 tmp = (((src >> srcfmt->Rshift) & 0xFF) << dstfmt->Rshift) | \
                     (((src >> srcfmt->Gshift) & 0xFF) << dstfmt->Gshift) | \
                     (((src >> srcfmt->Bshift) & 0xFF) << dstfmt->Bshift) | \
                     dstfmt->Amask;                                         \
        ضربی_عدد_BLEND_8888(tmp, dst, srcA);                                  \
    } جب (0)
// Blend the RGBA values of two pixels
#تعریف_کرو ALPHA_BLEND_RGBA(sR, sG, sB, sA, dR, dG, dB, dA) \
    کرو {                                                 \
        ALPHA_BLEND_CHANNEL(sR, dR, sA);                 \
        ALPHA_BLEND_CHANNEL(sG, dG, sA);                 \
        ALPHA_BLEND_CHANNEL(sB, dB, sA);                 \
        ALPHA_BLEND_CHANNEL(255, dA, sA);                \
    } جب (0)

// This is a very useful loop for optimizing blitters
#اگر defined(_MSC_VER) && (_MSC_VER == 1300)
// There's a bug in the Visual C++ 7 optimizer when compiling this code
#ورنہ
#تعریف_کرو USE_DUFFS_LOOP
#اگر_ختم

#تعریف_کرو DUFFS_LOOP1(pixel_copy_increment, چوڑائی) \
    {                                            \
        صحیح n;                                   \
        برائے (n = چوڑائی; n > 0; --n) {            \
            pixel_copy_increment;                \
        }                                        \
    }

#اگر_تعریف_شدہ USE_DUFFS_LOOP

// 8-times unrolled loop
#تعریف_کرو DUFFS_LOOP8(pixel_copy_increment, چوڑائی) \
    {                                            \
        صحیح n = (چوڑائی + 7) / 8;                 \
        انتخاب (چوڑائی & 7) {                     \
        حالت 0:                                  \
            کرو {                                 \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            حالت 7:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            حالت 6:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            حالت 5:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            حالت 4:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            حالت 3:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            حالت 2:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            حالت 1:                              \
                pixel_copy_increment;            \
            } جب (--n > 0);                   \
        }                                        \
    }

// 4-times unrolled loop
#تعریف_کرو DUFFS_LOOP4(pixel_copy_increment, چوڑائی) \
    {                                            \
        صحیح n = (چوڑائی + 3) / 4;                 \
        انتخاب (چوڑائی & 3) {                     \
        حالت 0:                                  \
            کرو {                                 \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            حالت 3:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            حالت 2:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            حالت 1:                              \
                pixel_copy_increment;            \
            } جب (--n > 0);                   \
        }                                        \
    }

// 2-times unrolled loop
#تعریف_کرو DUFFS_LOOP2(pixel_copy_increment, چوڑائی) \
    {                                            \
        صحیح n = (چوڑائی + 1) / 2;                 \
        انتخاب (چوڑائی & 1) {                     \
        حالت 0:                                  \
            کرو {                                 \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            حالت 1:                              \
                pixel_copy_increment;            \
            } جب (--n > 0);                   \
        }                                        \
    }

// Use the 4-times version of the loop by default
#تعریف_کرو DUFFS_LOOP(pixel_copy_increment, چوڑائی) \
    DUFFS_LOOP4(pixel_copy_increment, چوڑائی)
// Use the 8-times version of the loop for simple routines
#تعریف_کرو DUFFS_LOOP_TRIVIAL(pixel_copy_increment, چوڑائی) \
    DUFFS_LOOP8(pixel_copy_increment, چوڑائی)

// Special version of Duff's device for even more optimization
#تعریف_کرو DUFFS_LOOP_124(pixel_copy_increment1,        \
                       pixel_copy_increment2,        \
                       pixel_copy_increment4, چوڑائی) \
    {                                                \
        صحیح n = چوڑائی;                               \
        اگر (n & 1) {                                 \
            pixel_copy_increment1;                   \
            n -= 1;                                  \
        }                                            \
        اگر (n & 2) {                                 \
            pixel_copy_increment2;                   \
            n -= 2;                                  \
        }                                            \
        اگر (n & 4) {                                 \
            pixel_copy_increment4;                   \
            n -= 4;                                  \
        }                                            \
        اگر (n) {                                     \
            n /= 8;                                  \
            کرو {                                     \
                pixel_copy_increment4;               \
                pixel_copy_increment4;               \
            } جب (--n > 0);                       \
        }                                            \
    }

#ورنہ

// Don't use Duff's device to unroll loops
#تعریف_کرو DUFFS_LOOP(pixel_copy_increment, چوڑائی) \
    DUFFS_LOOP1(pixel_copy_increment, چوڑائی)
#تعریف_کرو DUFFS_LOOP_TRIVIAL(pixel_copy_increment, چوڑائی) \
    DUFFS_LOOP1(pixel_copy_increment, چوڑائی)
#تعریف_کرو DUFFS_LOOP8(pixel_copy_increment, چوڑائی) \
    DUFFS_LOOP1(pixel_copy_increment, چوڑائی)
#تعریف_کرو DUFFS_LOOP4(pixel_copy_increment, چوڑائی) \
    DUFFS_LOOP1(pixel_copy_increment, چوڑائی)
#تعریف_کرو DUFFS_LOOP2(pixel_copy_increment, چوڑائی) \
    DUFFS_LOOP1(pixel_copy_increment, چوڑائی)
#تعریف_کرو DUFFS_LOOP_124(pixel_copy_increment1,        \
                       pixel_copy_increment2,        \
                       pixel_copy_increment4, چوڑائی) \
    DUFFS_LOOP1(pixel_copy_increment1, چوڑائی)

#اگر_ختم // USE_DUFFS_LOOP

#اگر defined(_MSC_VER) && (_MSC_VER >= 600)
#ہدایت warning(disable : 4244) // '=': conversion from 'X' to 'Y', possible loss of data
#اگر_ختم

#اگر_ختم // SDL_blit_h_
