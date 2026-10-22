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
#ضمن "SDL_internal.h"

#اگر_تعریف_نشده SDL_blit_h_
#تعریف_کن SDL_blit_h_

// Table to do pixel byte expansion
خارجي ثابت Uint8 *SDL_expand_byte[9];
خارجي ثابت Uint16 SDL_expand_byte_10[];

// SDL blit copy flags
#تعریف_کن SDL_COPY_MODULATE_COLOR         0x00000001
#تعریف_کن SDL_COPY_MODULATE_ALPHA         0x00000002
#تعریف_کن SDL_COPY_MODULATE_ماسک		(SDL_COPY_MODULATE_COLOR | SDL_COPY_MODULATE_ALPHA)
#تعریف_کن SDL_COPY_BLEND                  0x00000010
#تعریف_کن SDL_COPY_BLEND_PREMULTIPLIED    0x00000020
#تعریف_کن SDL_COPY_جمع_کن                    0x00000040
#تعریف_کن SDL_COPY_جمع_کن_PREMULTIPLIED      0x00000080
#تعریف_کن SDL_COPY_MOD                    0x00000100
#تعریف_کن SDL_COPY_MUL                    0x00000200
#تعریف_کن SDL_COPY_BLEND_ماسک		(SDL_COPY_BLEND | SDL_COPY_BLEND_PREMULTIPLIED | SDL_COPY_جمع_کن | SDL_COPY_جمع_کن_PREMULTIPLIED | SDL_COPY_MOD | SDL_COPY_MUL)
#تعریف_کن SDL_COPY_COLORKEY               0x00000400
#تعریف_کن SDL_COPY_نزدیکترین                0x00000800
#تعریف_کن SDL_COPY_RLE_DESIRED            0x00001000
#تعریف_کن SDL_COPY_RLE_COLORKEY           0x00002000
#تعریف_کن SDL_COPY_RLE_ALPHAKEY           0x00004000
#تعریف_کن SDL_COPY_RLE_ماسک               (SDL_COPY_RLE_DESIRED | SDL_COPY_RLE_COLORKEY | SDL_COPY_RLE_ALPHAKEY)

// SDL blit CPU flags
#تعریف_کن SDL_CPU_ANY                0x00000000
#تعریف_کن SDL_CPU_MMX                0x00000001
#تعریف_کن SDL_CPU_SSE                0x00000002
#تعریف_کن SDL_CPU_SSE2               0x00000004
#تعریف_کن SDL_CPU_ALTIVEC_PREFETCH   0x00000008
#تعریف_کن SDL_CPU_ALTIVEC_NOPREFETCH 0x00000010

تعريفنوع بنية
{
    SDL_Surface *src_surface;
    Uint8 *src;
    صحيح src_w, src_h;
    صحيح src_pitch;
    صحيح src_skip;
    صحيح leading_skip;
    SDL_Surface *dst_surface;
    Uint8 *dst;
    صحيح dst_w, dst_h;
    صحيح dst_pitch;
    صحيح dst_skip;
    ثابت SDL_PixelFormatDetails *src_fmt;
    ثابت SDL_Palette *src_pal;
    ثابت SDL_PixelFormatDetails *dst_fmt;
    ثابت SDL_Palette *dst_pal;
    Uint8 *جدول;
    SDL_Hash_جدول *palette_map;
    صحيح flags;
    Uint32 colorkey;
    Uint8 r, g, b, a;
} SDL_BlitInfo;

تعريفنوع فراغ (*SDL_BlitFunc)(SDL_BlitInfo *info);

تعريفنوع بنية
{
    SDL_PixelFormat src_format;
    SDL_PixelFormat dst_format;
    صحيح flags;
    SDL_BlitFunc func;
} SDL_Blit_Func_مدخل;

تعريفنوع bool (SDLCALL *SDL_Blit) (بنية SDL_Surface *src, ثابت SDL_Rect *srcrect, بنية SDL_Surface *dst, ثابت SDL_Rect *dstrect);

// Blit mapping definition
تعريفنوع بنية SDL_BlitMap
{
    صحيح عنصر_خنثی;
    SDL_Blit blit;
    فراغ *داده;
    SDL_BlitInfo info;

    /* the version count matches the destination; mismatch indicates
       an invalid mapping */
    Uint32 dst_palette_نسخه;
    Uint32 src_palette_نسخه;
} SDL_BlitMap;

// Functions found in SDL_blit.c
خارجي bool SDL_CalculateBlit(SDL_Surface *surface, SDL_Surface *dst);

/* Functions found in SDL_blit_*.c */
خارجي SDL_BlitFunc SDL_CalculateBlit0(SDL_Surface *surface);
خارجي SDL_BlitFunc SDL_CalculateBlit1(SDL_Surface *surface);
خارجي SDL_BlitFunc SDL_CalculateBlitN(SDL_Surface *surface);
خارجي SDL_BlitFunc SDL_CalculateBlitA(SDL_Surface *surface);

/*
 * Useful macros for blitting routines
 */

#اگر_تعریف_شده __GNUC__
#تعریف_کن DECLARE_ALIGNED(t, v, a) t __attribute__((aligned(a))) v
#وإلاإذا defined(_MSC_VER)
#تعریف_کن DECLARE_ALIGNED(t, v, a) __declspec(align(a)) t v
#وإلا
#تعریف_کن DECLARE_ALIGNED(t, v, a) t v
#پایان_اگر

// Load pixel of the specified format from a buffer and get its R-G-B values
#تعریف_کن RGB_FROM_PIXEL(Pixel, fmt, r, g, b)                                     \
    {                                                                           \
        r = SDL_expand_byte[fmt->Rbits][((Pixel & fmt->Rmask) >> fmt->Rshift)]; \
        g = SDL_expand_byte[fmt->Gbits][((Pixel & fmt->Gmask) >> fmt->Gshift)]; \
        b = SDL_expand_byte[fmt->Bbits][((Pixel & fmt->Bmask) >> fmt->Bshift)]; \
    }
#تعریف_کن RGB_FROM_RGB565(Pixel, r, g, b)                   \
    {                                                     \
        r = SDL_expand_byte[5][((Pixel & 0xF800) >> 11)]; \
        g = SDL_expand_byte[6][((Pixel & 0x07E0) >> 5)];  \
        b = SDL_expand_byte[5][(Pixel & 0x001F)];         \
    }
#تعریف_کن RGB_FROM_RGB555(Pixel, r, g, b)                   \
    {                                                     \
        r = SDL_expand_byte[5][((Pixel & 0x7C00) >> 10)]; \
        g = SDL_expand_byte[5][((Pixel & 0x03E0) >> 5)];  \
        b = SDL_expand_byte[5][(Pixel & 0x001F)];         \
    }
#تعریف_کن RGB_FROM_XRGB8888(Pixel, r, g, b) \
    {                                   \
        r = ((Pixel & 0xFF0000) >> 16); \
        g = ((Pixel & 0xFF00) >> 8);    \
        b = (Pixel & 0xFF);             \
    }
#إذا SDL_BYTEORDER == SDL_LIL_ENDIAN
#تعریف_کن GET_RGB24(B) (B[2] << 16) | (B[1] << 8) | B[0]
#وإلا
#تعریف_کن GET_RGB24(B) (B[0] << 16) | (B[1] << 8) | B[2]
#پایان_اگر
#تعریف_کن RETRIEVE_RGB_PIXEL(buf, bpp, Pixel)                \
    افعل {                                                   \
        بدل (bpp) {                                     \
        حالة 1:                                            \
            Pixel = *((Uint8 *)(buf));                     \
            اكسر;                                         \
                                                           \
        حالة 2:                                            \
            Pixel = *((Uint16 *)(buf));                    \
            اكسر;                                         \
                                                           \
        حالة 3:                                            \
        {                                                  \
            Uint8 *B = (Uint8 *)(buf);                     \
            Pixel = GET_RGB24(B);                          \
        } اكسر;                                           \
                                                           \
        حالة 4:                                            \
            Pixel = *((Uint32 *)(buf));                    \
            اكسر;                                         \
                                                           \
        افتراضي:                                           \
            Pixel = 0; /* stop gcc complaints */           \
            اكسر;                                         \
        }                                                  \
    } طالما (0)

#إذا SDL_BYTEORDER == SDL_LIL_ENDIAN
#تعریف_کن GET_RGB24_COMPONENT(buf, fmt, لغزش) *((buf) + fmt->لغزش / 8)
#وإلا
#تعریف_کن GET_RGB24_COMPONENT(buf, fmt, لغزش) *((buf) + 2 - fmt->لغزش / 8)
#پایان_اگر
#تعریف_کن DISEMBLE_RGB(buf, bpp, fmt, Pixel, r, g, b)    \
    افعل {                                               \
        بدل (bpp) {                                 \
        حالة 1:                                        \
            Pixel = *((Uint8 *)(buf));                 \
            RGB_FROM_PIXEL(Pixel, fmt, r, g, b);       \
            اكسر;                                     \
                                                       \
        حالة 2:                                        \
            Pixel = *((Uint16 *)(buf));                \
            RGB_FROM_PIXEL(Pixel, fmt, r, g, b);       \
            اكسر;                                     \
                                                       \
        حالة 3:                                        \
        {                                              \
            Pixel = 0;                                 \
            r = GET_RGB24_COMPONENT(buf, fmt, Rshift); \
            g = GET_RGB24_COMPONENT(buf, fmt, Gshift); \
            b = GET_RGB24_COMPONENT(buf, fmt, Bshift); \
        } اكسر;                                       \
                                                       \
        حالة 4:                                        \
            Pixel = *((Uint32 *)(buf));                \
            RGB_FROM_PIXEL(Pixel, fmt, r, g, b);       \
            اكسر;                                     \
                                                       \
        افتراضي:                                       \
            /* stop gcc complaints */                  \
            Pixel = 0;                                 \
            r = g = b = 0;                             \
            اكسر;                                     \
        }                                              \
    } طالما (0)

// Assemble R-G-B values into a specified pixel format and store them
#تعریف_کن PIXEL_FROM_RGB(Pixel, fmt, r, g, b)                 \
    {                                                       \
        Pixel = ((r >> (8 - fmt->Rbits)) << fmt->Rshift) |  \
                ((g >> (8 - fmt->Gbits)) << fmt->Gshift) |  \
                ((b >> (8 - fmt->Bbits)) << fmt->Bshift) |  \
                fmt->Amask;                                 \
    }
#تعریف_کن RGB332_FROM_RGB(Pixel, r, g, b)                        \
    {                                                          \
        Pixel = (Uint8)(((r >> 5) << 5) | ((g >> 5) << 2) | (b >> 6)); \
    }
#تعریف_کن RGB565_FROM_RGB(Pixel, r, g, b)                        \
    {                                                          \
        Pixel = (Uint16)(((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3)); \
    }
#تعریف_کن RGB555_FROM_RGB(Pixel, r, g, b)                        \
    {                                                          \
        Pixel = (Uint16)(((r >> 3) << 10) | ((g >> 3) << 5) | (b >> 3)); \
    }
#تعریف_کن XRGB8888_FROM_RGB(Pixel, r, g, b)   \
    {                                     \
        Pixel = (r << 16) | (g << 8) | b; \
    }
#تعریف_کن ARGB8888_FROM_RGBA(Pixel, r, g, b, a)         \
    {                                                 \
        Pixel = (a << 24) | (r << 16) | (g << 8) | b; \
    }
#تعریف_کن RGBA8888_FROM_RGBA(Pixel, r, g, b, a)         \
    {                                                 \
        Pixel = (r << 24) | (g << 16) | (b << 8) | a; \
    }
#تعریف_کن ABGR8888_FROM_RGBA(Pixel, r, g, b, a)         \
    {                                                 \
        Pixel = (a << 24) | (b << 16) | (g << 8) | r; \
    }
#تعریف_کن BGRA8888_FROM_RGBA(Pixel, r, g, b, a)         \
    {                                                 \
        Pixel = (b << 24) | (g << 16) | (r << 8) | a; \
    }
#تعریف_کن ARGB2101010_FROM_RGBA(Pixel, r, g, b, a)       \
    {                                                  \
        r = r ? ((r << 2) | 0x3) : 0;                  \
        g = g ? ((g << 2) | 0x3) : 0;                  \
        b = b ? ((b << 2) | 0x3) : 0;                  \
        a = (a * 3) / 255;                             \
        Pixel = (a << 30) | (r << 20) | (g << 10) | b; \
    }
#تعریف_کن ARGB2101010_FROM_RGBAFLOAT(Pixel, r, g, b, a) \
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
#تعریف_کن ABGR2101010_FROM_RGBA(Pixel, r, g, b, a)       \
    {                                                  \
        r = r ? ((r << 2) | 0x3) : 0;                  \
        g = g ? ((g << 2) | 0x3) : 0;                  \
        b = b ? ((b << 2) | 0x3) : 0;                  \
        a = (a * 3) / 255;                             \
        Pixel = (a << 30) | (b << 20) | (g << 10) | r; \
    }
#تعریف_کن ABGR2101010_FROM_RGBAFLOAT(Pixel, r, g, b, a) \
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
#تعریف_کن ASSEMBLE_RGB(buf, bpp, fmt, r, g, b)           \
    {                                                  \
        بدل (bpp) {                                 \
        حالة 1:                                        \
        {                                              \
            Uint8 _pixel;                              \
                                                       \
            PIXEL_FROM_RGB(_pixel, fmt, r, g, b);      \
            *((Uint8 *)(buf)) = _pixel;                \
        } اكسر;                                       \
                                                       \
        حالة 2:                                        \
        {                                              \
            Uint16 _pixel;                             \
                                                       \
            PIXEL_FROM_RGB(_pixel, fmt, r, g, b);      \
            *((Uint16 *)(buf)) = _pixel;               \
        } اكسر;                                       \
                                                       \
        حالة 3:                                        \
        {                                              \
            GET_RGB24_COMPONENT(buf, fmt, Rshift) = r; \
            GET_RGB24_COMPONENT(buf, fmt, Gshift) = g; \
            GET_RGB24_COMPONENT(buf, fmt, Bshift) = b; \
        } اكسر;                                       \
                                                       \
        حالة 4:                                        \
        {                                              \
            Uint32 _pixel;                             \
                                                       \
            PIXEL_FROM_RGB(_pixel, fmt, r, g, b);      \
            *((Uint32 *)(buf)) = _pixel;               \
        } اكسر;                                       \
        }                                              \
    }

// FIXME: Should we rescale alpha into 0..255 here?
#تعریف_کن RGBA_FROM_PIXEL(Pixel, fmt, r, g, b, a)                                 \
    {                                                                           \
        r = SDL_expand_byte[fmt->Rbits][((Pixel & fmt->Rmask) >> fmt->Rshift)]; \
        g = SDL_expand_byte[fmt->Gbits][((Pixel & fmt->Gmask) >> fmt->Gshift)]; \
        b = SDL_expand_byte[fmt->Bbits][((Pixel & fmt->Bmask) >> fmt->Bshift)]; \
        a = SDL_expand_byte[fmt->Abits][((Pixel & fmt->Amask) >> fmt->Ashift)]; \
    }
#تعریف_کن RGBA_FROM_8888(Pixel, fmt, r, g, b, a)   \
    {                                            \
        r = (Pixel & fmt->Rmask) >> fmt->Rshift; \
        g = (Pixel & fmt->Gmask) >> fmt->Gshift; \
        b = (Pixel & fmt->Bmask) >> fmt->Bshift; \
        a = (Pixel & fmt->Amask) >> fmt->Ashift; \
    }
#تعریف_کن RGBA_FROM_RGBA8888(Pixel, r, g, b, a) \
    {                                         \
        r = (Pixel >> 24);                    \
        g = ((Pixel >> 16) & 0xFF);           \
        b = ((Pixel >> 8) & 0xFF);            \
        a = (Pixel & 0xFF);                   \
    }
#تعریف_کن RGBA_FROM_ARGB8888(Pixel, r, g, b, a) \
    {                                         \
        r = ((Pixel >> 16) & 0xFF);           \
        g = ((Pixel >> 8) & 0xFF);            \
        b = (Pixel & 0xFF);                   \
        a = (Pixel >> 24);                    \
    }
#تعریف_کن RGBA_FROM_ABGR8888(Pixel, r, g, b, a) \
    {                                         \
        r = (Pixel & 0xFF);                   \
        g = ((Pixel >> 8) & 0xFF);            \
        b = ((Pixel >> 16) & 0xFF);           \
        a = (Pixel >> 24);                    \
    }
#تعریف_کن RGBA_FROM_BGRA8888(Pixel, r, g, b, a) \
    {                                         \
        r = ((Pixel >> 8) & 0xFF);            \
        g = ((Pixel >> 16) & 0xFF);           \
        b = (Pixel >> 24);                    \
        a = (Pixel & 0xFF);                   \
    }
#تعریف_کن RGBA_FROM_ARGB2101010(Pixel, r, g, b, a) \
    {                                            \
        r = ((Pixel >> 22) & 0xFF);              \
        g = ((Pixel >> 12) & 0xFF);              \
        b = ((Pixel >> 2) & 0xFF);               \
        a = SDL_expand_byte[2][(Pixel >> 30)];   \
    }
#تعریف_کن RGBAFLOAT_FROM_ARGB2101010(Pixel, r, g, b, a)   \
    {                                                   \
        r = (عائم)((Pixel >> 20) & 0x3FF) / 1023.0f;   \
        g = (عائم)((Pixel >> 10) & 0x3FF) / 1023.0f;   \
        b = (عائم)((Pixel >> 0) & 0x3FF) / 1023.0f;    \
        a = (عائم)(Pixel >> 30) / 3.0f;                \
    }
#تعریف_کن RGBA_FROM_ABGR2101010(Pixel, r, g, b, a) \
    {                                            \
        r = ((Pixel >> 2) & 0xFF);               \
        g = ((Pixel >> 12) & 0xFF);              \
        b = ((Pixel >> 22) & 0xFF);              \
        a = SDL_expand_byte[2][(Pixel >> 30)];   \
    }
#تعریف_کن RGBAFLOAT_FROM_ABGR2101010(Pixel, r, g, b, a)   \
    {                                                   \
        r = (عائم)((Pixel >> 0) & 0x3FF) / 1023.0f;    \
        g = (عائم)((Pixel >> 10) & 0x3FF) / 1023.0f;   \
        b = (عائم)((Pixel >> 20) & 0x3FF) / 1023.0f;   \
        a = (عائم)(Pixel >> 30) / 3.0f;                \
    }
#تعریف_کن DISEMBLE_RGBA(buf, bpp, fmt, Pixel, r, g, b, a) \
    افعل {                                                \
        بدل (bpp) {                                  \
        حالة 1:                                         \
            Pixel = *((Uint8 *)(buf));                  \
            RGBA_FROM_PIXEL(Pixel, fmt, r, g, b, a);    \
            اكسر;                                      \
                                                        \
        حالة 2:                                         \
            Pixel = *((Uint16 *)(buf));                 \
            RGBA_FROM_PIXEL(Pixel, fmt, r, g, b, a);    \
            اكسر;                                      \
                                                        \
        حالة 3:                                         \
        {                                               \
            Pixel = 0;                                  \
            r = GET_RGB24_COMPONENT(buf, fmt, Rshift);  \
            g = GET_RGB24_COMPONENT(buf, fmt, Gshift);  \
            b = GET_RGB24_COMPONENT(buf, fmt, Bshift);  \
            a = 0xFF;                                   \
        } اكسر;                                        \
                                                        \
        حالة 4:                                         \
            Pixel = *((Uint32 *)(buf));                 \
            RGBA_FROM_PIXEL(Pixel, fmt, r, g, b, a);    \
            اكسر;                                      \
                                                        \
        افتراضي:                                        \
            /* stop gcc complaints */                   \
            Pixel = 0;                                  \
            r = g = b = a = 0;                          \
            اكسر;                                      \
        }                                               \
    } طالما (0)

// FIXME: this isn't correct, especially for Alpha (maximum != 255)
#تعریف_کن PIXEL_FROM_RGBA(Pixel, fmt, r, g, b, a)             \
    {                                                       \
        Pixel = ((r >> (8 - fmt->Rbits)) << fmt->Rshift) |  \
                ((g >> (8 - fmt->Gbits)) << fmt->Gshift) |  \
                ((b >> (8 - fmt->Bbits)) << fmt->Bshift) |  \
                ((a >> (8 - fmt->Abits)) << fmt->Ashift);   \
    }
#تعریف_کن ASSEMBLE_RGBA(buf, bpp, fmt, r, g, b, a)       \
    {                                                  \
        بدل (bpp) {                                 \
        حالة 1:                                        \
        {                                              \
            Uint8 _pixel;                              \
                                                       \
            PIXEL_FROM_RGBA(_pixel, fmt, r, g, b, a);  \
            *((Uint8 *)(buf)) = _pixel;                \
        } اكسر;                                       \
                                                       \
        حالة 2:                                        \
        {                                              \
            Uint16 _pixel;                             \
                                                       \
            PIXEL_FROM_RGBA(_pixel, fmt, r, g, b, a);  \
            *((Uint16 *)(buf)) = _pixel;               \
        } اكسر;                                       \
                                                       \
        حالة 3:                                        \
        {                                              \
            GET_RGB24_COMPONENT(buf, fmt, Rshift) = r; \
            GET_RGB24_COMPONENT(buf, fmt, Gshift) = g; \
            GET_RGB24_COMPONENT(buf, fmt, Bshift) = b; \
        } اكسر;                                       \
                                                       \
        حالة 4:                                        \
        {                                              \
            Uint32 _pixel;                             \
                                                       \
            PIXEL_FROM_RGBA(_pixel, fmt, r, g, b, a);  \
            *((Uint32 *)(buf)) = _pixel;               \
        } اكسر;                                       \
        }                                              \
    }

// Convert any 32-bit 4-bpp pixel to ARGB format
#تعریف_کن PIXEL_مقصد_ARGB_PIXEL(src, srcfmt, dst)         \
    افعل {                                              \
        Uint8 a, r, g, b;                         \
        RGBA_FROM_PIXEL(src, srcfmt, r, g, b, a); \
        dst = a << 24 | r << 16 | g << 8 | b;     \
    } طالما (0)
// Blend a single color channel or alpha value
/* dC = ((sC * sA) + (dC * (255 - sA))) / 255 */
#تعریف_کن ALPHA_BLEND_CHANNEL(sC, dC, sA)                  \
    افعل {                                                 \
        Uint16 x;                                        \
        x = ((sC - dC) * sA) + ((dC << 8) - dC);         \
        x += 0x1U;                                       \
        x += x >> 8;                                     \
        dC = x >> 8;                                     \
    } طالما (0)
// Perform a division by 255 after a multiplication of two 8-bit color channels
/* out = (sC * dC) / 255 */
#تعریف_کن MULT_DIV_255(sC, dC, بیرون) \
    افعل {                          \
        Uint16 x = sC * dC;       \
        x += 0x1U;                \
        x += x >> 8;              \
        بیرون = x >> 8;             \
    } طالما (0)
// Blend the RGB values of two pixels with an alpha value
#تعریف_کن ALPHA_BLEND_RGB(sR, sG, sB, A, dR, dG, dB)            \
    افعل {                                                      \
        ALPHA_BLEND_CHANNEL(sR, dR, A);                       \
        ALPHA_BLEND_CHANNEL(sG, dG, A);                       \
        ALPHA_BLEND_CHANNEL(sB, dB, A);                       \
    } طالما (0)

// Blend two 8888 pixels with the same format
/* Calculates dst = ((src * factor) + (dst * (255 - factor))) / 255 */
// FIXME: SDL_SIZE_MAX might not be an integer literal
#إذا defined(SIZE_MAX) && (SIZE_MAX == 0xffffffffffffffff)
#تعریف_کن ضریب_BLEND_8888(src, dst, ضریب)                        \
    افعل {                                                           \
        Uint64 src64 = src;                                        \
        src64 = (src64 | (src64 << 24)) & 0x00FF00FF00FF00FF;      \
                                                                   \
        Uint64 dst64 = dst;                                        \
        dst64 = (dst64 | (dst64 << 24)) & 0x00FF00FF00FF00FF;      \
                                                                   \
        dst64 = ((src64 - dst64) * ضریب) + (dst64 << 8) - dst64; \
        dst64 += 0x0001000100010001;                               \
        dst64 += (dst64 >> 8) & 0x00FF00FF00FF00FF;                \
        dst64 &= 0xFF00FF00FF00FF00;                               \
                                                                   \
        dst = (Uint32)((dst64 >> 8) | (dst64 >> 32));              \
    } طالما (0)
#وإلا
#تعریف_کن ضریب_BLEND_8888(src, dst, ضریب)                               \
    افعل {                                                                  \
        Uint32 src02 = src & 0x00FF00FF;                                  \
        Uint32 dst02 = dst & 0x00FF00FF;                                  \
                                                                          \
        Uint32 src13 = (src >> 8) & 0x00FF00FF;                           \
        Uint32 dst13 = (dst >> 8) & 0x00FF00FF;                           \
                                                                          \
        Uint32 res02 = ((src02 - dst02) * ضریب) + (dst02 << 8) - dst02; \
        res02 += 0x00010001;                                              \
        res02 += (res02 >> 8) & 0x00FF00FF;                               \
        res02 = (res02 >> 8) & 0x00FF00FF;                                \
                                                                          \
        Uint32 res13 = ((src13 - dst13) * ضریب) + (dst13 << 8) - dst13; \
        res13 += 0x00010001;                                              \
        res13 += (res13 >> 8) & 0x00FF00FF;                               \
        res13 &= 0xFF00FF00;                                              \
        dst = res02 | res13;                                              \
    } طالما (0)
#پایان_اگر

// Alpha blend two 8888 pixels with the same formats.
#تعریف_کن ALPHA_BLEND_8888(src, dst, fmt)            \
    افعل {                                           \
        Uint32 srcA = (src >> fmt->Ashift) & 0xFF; \
        Uint32 tmp = src | fmt->Amask;             \
        ضریب_BLEND_8888(tmp, dst, srcA);         \
    } طالما (0)

// Alpha blend two 8888 pixels with differing formats.
#تعریف_کن ALPHA_BLEND_SWIZZLE_8888(src, dst, srcfmt, dstfmt)                  \
    افعل {                                                                    \
        Uint32 srcA = (src >> srcfmt->Ashift) & 0xFF;                       \
        Uint32 tmp = (((src >> srcfmt->Rshift) & 0xFF) << dstfmt->Rshift) | \
                     (((src >> srcfmt->Gshift) & 0xFF) << dstfmt->Gshift) | \
                     (((src >> srcfmt->Bshift) & 0xFF) << dstfmt->Bshift) | \
                     dstfmt->Amask;                                         \
        ضریب_BLEND_8888(tmp, dst, srcA);                                  \
    } طالما (0)
// Blend the RGBA values of two pixels
#تعریف_کن ALPHA_BLEND_RGBA(sR, sG, sB, sA, dR, dG, dB, dA) \
    افعل {                                                 \
        ALPHA_BLEND_CHANNEL(sR, dR, sA);                 \
        ALPHA_BLEND_CHANNEL(sG, dG, sA);                 \
        ALPHA_BLEND_CHANNEL(sB, dB, sA);                 \
        ALPHA_BLEND_CHANNEL(255, dA, sA);                \
    } طالما (0)

// This is a very useful loop for optimizing blitters
#إذا defined(_MSC_VER) && (_MSC_VER == 1300)
// There's a bug in the Visual C++ 7 optimizer when compiling this code
#وإلا
#تعریف_کن USE_DUFFS_LOOP
#پایان_اگر

#تعریف_کن DUFFS_LOOP1(pixel_copy_increment, عرض) \
    {                                            \
        صحيح n;                                   \
        لكل (n = عرض; n > 0; --n) {            \
            pixel_copy_increment;                \
        }                                        \
    }

#اگر_تعریف_شده USE_DUFFS_LOOP

// 8-times unrolled loop
#تعریف_کن DUFFS_LOOP8(pixel_copy_increment, عرض) \
    {                                            \
        صحيح n = (عرض + 7) / 8;                 \
        بدل (عرض & 7) {                     \
        حالة 0:                                  \
            افعل {                                 \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            حالة 7:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            حالة 6:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            حالة 5:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            حالة 4:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            حالة 3:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            حالة 2:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            حالة 1:                              \
                pixel_copy_increment;            \
            } طالما (--n > 0);                   \
        }                                        \
    }

// 4-times unrolled loop
#تعریف_کن DUFFS_LOOP4(pixel_copy_increment, عرض) \
    {                                            \
        صحيح n = (عرض + 3) / 4;                 \
        بدل (عرض & 3) {                     \
        حالة 0:                                  \
            افعل {                                 \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            حالة 3:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            حالة 2:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            حالة 1:                              \
                pixel_copy_increment;            \
            } طالما (--n > 0);                   \
        }                                        \
    }

// 2-times unrolled loop
#تعریف_کن DUFFS_LOOP2(pixel_copy_increment, عرض) \
    {                                            \
        صحيح n = (عرض + 1) / 2;                 \
        بدل (عرض & 1) {                     \
        حالة 0:                                  \
            افعل {                                 \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            حالة 1:                              \
                pixel_copy_increment;            \
            } طالما (--n > 0);                   \
        }                                        \
    }

// Use the 4-times version of the loop by default
#تعریف_کن DUFFS_LOOP(pixel_copy_increment, عرض) \
    DUFFS_LOOP4(pixel_copy_increment, عرض)
// Use the 8-times version of the loop for simple routines
#تعریف_کن DUFFS_LOOP_TRIVIAL(pixel_copy_increment, عرض) \
    DUFFS_LOOP8(pixel_copy_increment, عرض)

// Special version of Duff's device for even more optimization
#تعریف_کن DUFFS_LOOP_124(pixel_copy_increment1,        \
                       pixel_copy_increment2,        \
                       pixel_copy_increment4, عرض) \
    {                                                \
        صحيح n = عرض;                               \
        إذا (n & 1) {                                 \
            pixel_copy_increment1;                   \
            n -= 1;                                  \
        }                                            \
        إذا (n & 2) {                                 \
            pixel_copy_increment2;                   \
            n -= 2;                                  \
        }                                            \
        إذا (n & 4) {                                 \
            pixel_copy_increment4;                   \
            n -= 4;                                  \
        }                                            \
        إذا (n) {                                     \
            n /= 8;                                  \
            افعل {                                     \
                pixel_copy_increment4;               \
                pixel_copy_increment4;               \
            } طالما (--n > 0);                       \
        }                                            \
    }

#وإلا

// Don't use Duff's device to unroll loops
#تعریف_کن DUFFS_LOOP(pixel_copy_increment, عرض) \
    DUFFS_LOOP1(pixel_copy_increment, عرض)
#تعریف_کن DUFFS_LOOP_TRIVIAL(pixel_copy_increment, عرض) \
    DUFFS_LOOP1(pixel_copy_increment, عرض)
#تعریف_کن DUFFS_LOOP8(pixel_copy_increment, عرض) \
    DUFFS_LOOP1(pixel_copy_increment, عرض)
#تعریف_کن DUFFS_LOOP4(pixel_copy_increment, عرض) \
    DUFFS_LOOP1(pixel_copy_increment, عرض)
#تعریف_کن DUFFS_LOOP2(pixel_copy_increment, عرض) \
    DUFFS_LOOP1(pixel_copy_increment, عرض)
#تعریف_کن DUFFS_LOOP_124(pixel_copy_increment1,        \
                       pixel_copy_increment2,        \
                       pixel_copy_increment4, عرض) \
    DUFFS_LOOP1(pixel_copy_increment1, عرض)

#پایان_اگر // USE_DUFFS_LOOP

#إذا defined(_MSC_VER) && (_MSC_VER >= 600)
#رهنمود warning(disable : 4244) // '=': conversion from 'X' to 'Y', possible loss of data
#پایان_اگر

#پایان_اگر // SDL_blit_h_
