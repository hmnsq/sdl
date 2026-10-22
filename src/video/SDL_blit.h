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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_blit_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_blit_h_

// Table to do pixel byte expansion
ਬਾਹਰੀ ਅਚਲ Uint8 *SDL_expand_byte[9];
ਬਾਹਰੀ ਅਚਲ Uint16 SDL_expand_byte_10[];

// SDL blit copy flags
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_COPY_MODULATE_COLOR         0x00000001
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_COPY_MODULATE_ALPHA         0x00000002
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_COPY_MODULATE_ਨਕਾਬ		(SDL_COPY_MODULATE_COLOR | SDL_COPY_MODULATE_ALPHA)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_COPY_BLEND                  0x00000010
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_COPY_BLEND_PREMULTIPLIED    0x00000020
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_COPY_ਜੋੜੋ                    0x00000040
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_COPY_ਜੋੜੋ_PREMULTIPLIED      0x00000080
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_COPY_MOD                    0x00000100
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_COPY_MUL                    0x00000200
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_COPY_BLEND_ਨਕਾਬ		(SDL_COPY_BLEND | SDL_COPY_BLEND_PREMULTIPLIED | SDL_COPY_ਜੋੜੋ | SDL_COPY_ਜੋੜੋ_PREMULTIPLIED | SDL_COPY_MOD | SDL_COPY_MUL)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_COPY_COLORKEY               0x00000400
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_COPY_ਸਭ_ਤੋਂ_ਨੇੜੇ                0x00000800
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_COPY_RLE_DESIRED            0x00001000
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_COPY_RLE_COLORKEY           0x00002000
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_COPY_RLE_ALPHAKEY           0x00004000
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_COPY_RLE_ਨਕਾਬ               (SDL_COPY_RLE_DESIRED | SDL_COPY_RLE_COLORKEY | SDL_COPY_RLE_ALPHAKEY)

// SDL blit CPU flags
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_CPU_ANY                0x00000000
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_CPU_MMX                0x00000001
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_CPU_SSE                0x00000002
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_CPU_SSE2               0x00000004
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_CPU_ALTIVEC_PREFETCH   0x00000008
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_CPU_ALTIVEC_NOPREFETCH 0x00000010

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
    SDL_Surface *src_surface;
    Uint8 *src;
    ਪੂਰਨ src_w, src_h;
    ਪੂਰਨ src_pitch;
    ਪੂਰਨ src_skip;
    ਪੂਰਨ leading_skip;
    SDL_Surface *dst_surface;
    Uint8 *dst;
    ਪੂਰਨ dst_w, dst_h;
    ਪੂਰਨ dst_pitch;
    ਪੂਰਨ dst_skip;
    ਅਚਲ SDL_PixelFormatDetails *src_fmt;
    ਅਚਲ SDL_Palette *src_pal;
    ਅਚਲ SDL_PixelFormatDetails *dst_fmt;
    ਅਚਲ SDL_Palette *dst_pal;
    Uint8 *ਸਾਰਣੀ;
    SDL_Hash_ਸਾਰਣੀ *palette_map;
    ਪੂਰਨ flags;
    Uint32 colorkey;
    Uint8 r, g, b, a;
} SDL_BlitInfo;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (*SDL_BlitFunc)(SDL_BlitInfo *info);

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
    SDL_PixelFormat src_format;
    SDL_PixelFormat dst_format;
    ਪੂਰਨ flags;
    SDL_BlitFunc func;
} SDL_Blit_Func_ਇੰਦਰਾਜ;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ bool (SDLCALL *SDL_Blit) (ਬਣਤਰ SDL_Surface *src, ਅਚਲ SDL_Rect *srcrect, ਬਣਤਰ SDL_Surface *dst, ਅਚਲ SDL_Rect *dstrect);

// Blit mapping definition
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ SDL_BlitMap
{
    ਪੂਰਨ ਪਛਾਣ_ਤੱਤ;
    SDL_Blit blit;
    ਖਾਲੀ *ਅੰਕੜੇ;
    SDL_BlitInfo info;

    /* the version count matches the destination; mismatch indicates
       an invalid mapping */
    Uint32 dst_palette_ਸੰਸਕਰਣ;
    Uint32 src_palette_ਸੰਸਕਰਣ;
} SDL_BlitMap;

// Functions found in SDL_blit.c
ਬਾਹਰੀ bool SDL_CalculateBlit(SDL_Surface *surface, SDL_Surface *dst);

/* Functions found in SDL_blit_*.c */
ਬਾਹਰੀ SDL_BlitFunc SDL_CalculateBlit0(SDL_Surface *surface);
ਬਾਹਰੀ SDL_BlitFunc SDL_CalculateBlit1(SDL_Surface *surface);
ਬਾਹਰੀ SDL_BlitFunc SDL_CalculateBlitN(SDL_Surface *surface);
ਬਾਹਰੀ SDL_BlitFunc SDL_CalculateBlitA(SDL_Surface *surface);

/*
 * Useful macros for blitting routines
 */

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __GNUC__
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DECLARE_ALIGNED(t, v, a) t __attribute__((aligned(a))) v
#ਜਾਂਜੇ defined(_MSC_VER)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DECLARE_ALIGNED(t, v, a) __declspec(align(a)) t v
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DECLARE_ALIGNED(t, v, a) t v
#ਜੇ_ਅੰਤ

// Load pixel of the specified format from a buffer and get its R-G-B values
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RGB_FROM_PIXEL(Pixel, fmt, r, g, b)                                     \
    {                                                                           \
        r = SDL_expand_byte[fmt->Rbits][((Pixel & fmt->Rmask) >> fmt->Rshift)]; \
        g = SDL_expand_byte[fmt->Gbits][((Pixel & fmt->Gmask) >> fmt->Gshift)]; \
        b = SDL_expand_byte[fmt->Bbits][((Pixel & fmt->Bmask) >> fmt->Bshift)]; \
    }
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RGB_FROM_RGB565(Pixel, r, g, b)                   \
    {                                                     \
        r = SDL_expand_byte[5][((Pixel & 0xF800) >> 11)]; \
        g = SDL_expand_byte[6][((Pixel & 0x07E0) >> 5)];  \
        b = SDL_expand_byte[5][(Pixel & 0x001F)];         \
    }
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RGB_FROM_RGB555(Pixel, r, g, b)                   \
    {                                                     \
        r = SDL_expand_byte[5][((Pixel & 0x7C00) >> 10)]; \
        g = SDL_expand_byte[5][((Pixel & 0x03E0) >> 5)];  \
        b = SDL_expand_byte[5][(Pixel & 0x001F)];         \
    }
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RGB_FROM_XRGB8888(Pixel, r, g, b) \
    {                                   \
        r = ((Pixel & 0xFF0000) >> 16); \
        g = ((Pixel & 0xFF00) >> 8);    \
        b = (Pixel & 0xFF);             \
    }
#ਜੇ SDL_BYTEORDER == SDL_LIL_ENDIAN
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GET_RGB24(B) (B[2] << 16) | (B[1] << 8) | B[0]
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GET_RGB24(B) (B[0] << 16) | (B[1] << 8) | B[2]
#ਜੇ_ਅੰਤ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RETRIEVE_RGB_PIXEL(buf, bpp, Pixel)                \
    ਕਰੋ {                                                   \
        ਚੋਣ (bpp) {                                     \
        ਹਾਲਤ 1:                                            \
            Pixel = *((Uint8 *)(buf));                     \
            ਰੋਕੋ;                                         \
                                                           \
        ਹਾਲਤ 2:                                            \
            Pixel = *((Uint16 *)(buf));                    \
            ਰੋਕੋ;                                         \
                                                           \
        ਹਾਲਤ 3:                                            \
        {                                                  \
            Uint8 *B = (Uint8 *)(buf);                     \
            Pixel = GET_RGB24(B);                          \
        } ਰੋਕੋ;                                           \
                                                           \
        ਹਾਲਤ 4:                                            \
            Pixel = *((Uint32 *)(buf));                    \
            ਰੋਕੋ;                                         \
                                                           \
        ਮੂਲ:                                           \
            Pixel = 0; /* stop gcc complaints */           \
            ਰੋਕੋ;                                         \
        }                                                  \
    } ਜਦੋਂ (0)

#ਜੇ SDL_BYTEORDER == SDL_LIL_ENDIAN
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GET_RGB24_COMPONENT(buf, fmt, ਖਿਸਕਾਓ) *((buf) + fmt->ਖਿਸਕਾਓ / 8)
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GET_RGB24_COMPONENT(buf, fmt, ਖਿਸਕਾਓ) *((buf) + 2 - fmt->ਖਿਸਕਾਓ / 8)
#ਜੇ_ਅੰਤ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DISEMBLE_RGB(buf, bpp, fmt, Pixel, r, g, b)    \
    ਕਰੋ {                                               \
        ਚੋਣ (bpp) {                                 \
        ਹਾਲਤ 1:                                        \
            Pixel = *((Uint8 *)(buf));                 \
            RGB_FROM_PIXEL(Pixel, fmt, r, g, b);       \
            ਰੋਕੋ;                                     \
                                                       \
        ਹਾਲਤ 2:                                        \
            Pixel = *((Uint16 *)(buf));                \
            RGB_FROM_PIXEL(Pixel, fmt, r, g, b);       \
            ਰੋਕੋ;                                     \
                                                       \
        ਹਾਲਤ 3:                                        \
        {                                              \
            Pixel = 0;                                 \
            r = GET_RGB24_COMPONENT(buf, fmt, Rshift); \
            g = GET_RGB24_COMPONENT(buf, fmt, Gshift); \
            b = GET_RGB24_COMPONENT(buf, fmt, Bshift); \
        } ਰੋਕੋ;                                       \
                                                       \
        ਹਾਲਤ 4:                                        \
            Pixel = *((Uint32 *)(buf));                \
            RGB_FROM_PIXEL(Pixel, fmt, r, g, b);       \
            ਰੋਕੋ;                                     \
                                                       \
        ਮੂਲ:                                       \
            /* stop gcc complaints */                  \
            Pixel = 0;                                 \
            r = g = b = 0;                             \
            ਰੋਕੋ;                                     \
        }                                              \
    } ਜਦੋਂ (0)

// Assemble R-G-B values into a specified pixel format and store them
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PIXEL_FROM_RGB(Pixel, fmt, r, g, b)                 \
    {                                                       \
        Pixel = ((r >> (8 - fmt->Rbits)) << fmt->Rshift) |  \
                ((g >> (8 - fmt->Gbits)) << fmt->Gshift) |  \
                ((b >> (8 - fmt->Bbits)) << fmt->Bshift) |  \
                fmt->Amask;                                 \
    }
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RGB332_FROM_RGB(Pixel, r, g, b)                        \
    {                                                          \
        Pixel = (Uint8)(((r >> 5) << 5) | ((g >> 5) << 2) | (b >> 6)); \
    }
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RGB565_FROM_RGB(Pixel, r, g, b)                        \
    {                                                          \
        Pixel = (Uint16)(((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3)); \
    }
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RGB555_FROM_RGB(Pixel, r, g, b)                        \
    {                                                          \
        Pixel = (Uint16)(((r >> 3) << 10) | ((g >> 3) << 5) | (b >> 3)); \
    }
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XRGB8888_FROM_RGB(Pixel, r, g, b)   \
    {                                     \
        Pixel = (r << 16) | (g << 8) | b; \
    }
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ARGB8888_FROM_RGBA(Pixel, r, g, b, a)         \
    {                                                 \
        Pixel = (a << 24) | (r << 16) | (g << 8) | b; \
    }
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RGBA8888_FROM_RGBA(Pixel, r, g, b, a)         \
    {                                                 \
        Pixel = (r << 24) | (g << 16) | (b << 8) | a; \
    }
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ABGR8888_FROM_RGBA(Pixel, r, g, b, a)         \
    {                                                 \
        Pixel = (a << 24) | (b << 16) | (g << 8) | r; \
    }
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BGRA8888_FROM_RGBA(Pixel, r, g, b, a)         \
    {                                                 \
        Pixel = (b << 24) | (g << 16) | (r << 8) | a; \
    }
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ARGB2101010_FROM_RGBA(Pixel, r, g, b, a)       \
    {                                                  \
        r = r ? ((r << 2) | 0x3) : 0;                  \
        g = g ? ((g << 2) | 0x3) : 0;                  \
        b = b ? ((b << 2) | 0x3) : 0;                  \
        a = (a * 3) / 255;                             \
        Pixel = (a << 30) | (r << 20) | (g << 10) | b; \
    }
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ARGB2101010_FROM_RGBAFLOAT(Pixel, r, g, b, a) \
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
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ABGR2101010_FROM_RGBA(Pixel, r, g, b, a)       \
    {                                                  \
        r = r ? ((r << 2) | 0x3) : 0;                  \
        g = g ? ((g << 2) | 0x3) : 0;                  \
        b = b ? ((b << 2) | 0x3) : 0;                  \
        a = (a * 3) / 255;                             \
        Pixel = (a << 30) | (b << 20) | (g << 10) | r; \
    }
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ABGR2101010_FROM_RGBAFLOAT(Pixel, r, g, b, a) \
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
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ASSEMBLE_RGB(buf, bpp, fmt, r, g, b)           \
    {                                                  \
        ਚੋਣ (bpp) {                                 \
        ਹਾਲਤ 1:                                        \
        {                                              \
            Uint8 _pixel;                              \
                                                       \
            PIXEL_FROM_RGB(_pixel, fmt, r, g, b);      \
            *((Uint8 *)(buf)) = _pixel;                \
        } ਰੋਕੋ;                                       \
                                                       \
        ਹਾਲਤ 2:                                        \
        {                                              \
            Uint16 _pixel;                             \
                                                       \
            PIXEL_FROM_RGB(_pixel, fmt, r, g, b);      \
            *((Uint16 *)(buf)) = _pixel;               \
        } ਰੋਕੋ;                                       \
                                                       \
        ਹਾਲਤ 3:                                        \
        {                                              \
            GET_RGB24_COMPONENT(buf, fmt, Rshift) = r; \
            GET_RGB24_COMPONENT(buf, fmt, Gshift) = g; \
            GET_RGB24_COMPONENT(buf, fmt, Bshift) = b; \
        } ਰੋਕੋ;                                       \
                                                       \
        ਹਾਲਤ 4:                                        \
        {                                              \
            Uint32 _pixel;                             \
                                                       \
            PIXEL_FROM_RGB(_pixel, fmt, r, g, b);      \
            *((Uint32 *)(buf)) = _pixel;               \
        } ਰੋਕੋ;                                       \
        }                                              \
    }

// FIXME: Should we rescale alpha into 0..255 here?
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RGBA_FROM_PIXEL(Pixel, fmt, r, g, b, a)                                 \
    {                                                                           \
        r = SDL_expand_byte[fmt->Rbits][((Pixel & fmt->Rmask) >> fmt->Rshift)]; \
        g = SDL_expand_byte[fmt->Gbits][((Pixel & fmt->Gmask) >> fmt->Gshift)]; \
        b = SDL_expand_byte[fmt->Bbits][((Pixel & fmt->Bmask) >> fmt->Bshift)]; \
        a = SDL_expand_byte[fmt->Abits][((Pixel & fmt->Amask) >> fmt->Ashift)]; \
    }
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RGBA_FROM_8888(Pixel, fmt, r, g, b, a)   \
    {                                            \
        r = (Pixel & fmt->Rmask) >> fmt->Rshift; \
        g = (Pixel & fmt->Gmask) >> fmt->Gshift; \
        b = (Pixel & fmt->Bmask) >> fmt->Bshift; \
        a = (Pixel & fmt->Amask) >> fmt->Ashift; \
    }
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RGBA_FROM_RGBA8888(Pixel, r, g, b, a) \
    {                                         \
        r = (Pixel >> 24);                    \
        g = ((Pixel >> 16) & 0xFF);           \
        b = ((Pixel >> 8) & 0xFF);            \
        a = (Pixel & 0xFF);                   \
    }
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RGBA_FROM_ARGB8888(Pixel, r, g, b, a) \
    {                                         \
        r = ((Pixel >> 16) & 0xFF);           \
        g = ((Pixel >> 8) & 0xFF);            \
        b = (Pixel & 0xFF);                   \
        a = (Pixel >> 24);                    \
    }
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RGBA_FROM_ABGR8888(Pixel, r, g, b, a) \
    {                                         \
        r = (Pixel & 0xFF);                   \
        g = ((Pixel >> 8) & 0xFF);            \
        b = ((Pixel >> 16) & 0xFF);           \
        a = (Pixel >> 24);                    \
    }
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RGBA_FROM_BGRA8888(Pixel, r, g, b, a) \
    {                                         \
        r = ((Pixel >> 8) & 0xFF);            \
        g = ((Pixel >> 16) & 0xFF);           \
        b = (Pixel >> 24);                    \
        a = (Pixel & 0xFF);                   \
    }
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RGBA_FROM_ARGB2101010(Pixel, r, g, b, a) \
    {                                            \
        r = ((Pixel >> 22) & 0xFF);              \
        g = ((Pixel >> 12) & 0xFF);              \
        b = ((Pixel >> 2) & 0xFF);               \
        a = SDL_expand_byte[2][(Pixel >> 30)];   \
    }
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RGBAFLOAT_FROM_ARGB2101010(Pixel, r, g, b, a)   \
    {                                                   \
        r = (ਦਸ਼ਮਲਵ)((Pixel >> 20) & 0x3FF) / 1023.0f;   \
        g = (ਦਸ਼ਮਲਵ)((Pixel >> 10) & 0x3FF) / 1023.0f;   \
        b = (ਦਸ਼ਮਲਵ)((Pixel >> 0) & 0x3FF) / 1023.0f;    \
        a = (ਦਸ਼ਮਲਵ)(Pixel >> 30) / 3.0f;                \
    }
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RGBA_FROM_ABGR2101010(Pixel, r, g, b, a) \
    {                                            \
        r = ((Pixel >> 2) & 0xFF);               \
        g = ((Pixel >> 12) & 0xFF);              \
        b = ((Pixel >> 22) & 0xFF);              \
        a = SDL_expand_byte[2][(Pixel >> 30)];   \
    }
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RGBAFLOAT_FROM_ABGR2101010(Pixel, r, g, b, a)   \
    {                                                   \
        r = (ਦਸ਼ਮਲਵ)((Pixel >> 0) & 0x3FF) / 1023.0f;    \
        g = (ਦਸ਼ਮਲਵ)((Pixel >> 10) & 0x3FF) / 1023.0f;   \
        b = (ਦਸ਼ਮਲਵ)((Pixel >> 20) & 0x3FF) / 1023.0f;   \
        a = (ਦਸ਼ਮਲਵ)(Pixel >> 30) / 3.0f;                \
    }
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DISEMBLE_RGBA(buf, bpp, fmt, Pixel, r, g, b, a) \
    ਕਰੋ {                                                \
        ਚੋਣ (bpp) {                                  \
        ਹਾਲਤ 1:                                         \
            Pixel = *((Uint8 *)(buf));                  \
            RGBA_FROM_PIXEL(Pixel, fmt, r, g, b, a);    \
            ਰੋਕੋ;                                      \
                                                        \
        ਹਾਲਤ 2:                                         \
            Pixel = *((Uint16 *)(buf));                 \
            RGBA_FROM_PIXEL(Pixel, fmt, r, g, b, a);    \
            ਰੋਕੋ;                                      \
                                                        \
        ਹਾਲਤ 3:                                         \
        {                                               \
            Pixel = 0;                                  \
            r = GET_RGB24_COMPONENT(buf, fmt, Rshift);  \
            g = GET_RGB24_COMPONENT(buf, fmt, Gshift);  \
            b = GET_RGB24_COMPONENT(buf, fmt, Bshift);  \
            a = 0xFF;                                   \
        } ਰੋਕੋ;                                        \
                                                        \
        ਹਾਲਤ 4:                                         \
            Pixel = *((Uint32 *)(buf));                 \
            RGBA_FROM_PIXEL(Pixel, fmt, r, g, b, a);    \
            ਰੋਕੋ;                                      \
                                                        \
        ਮੂਲ:                                        \
            /* stop gcc complaints */                   \
            Pixel = 0;                                  \
            r = g = b = a = 0;                          \
            ਰੋਕੋ;                                      \
        }                                               \
    } ਜਦੋਂ (0)

// FIXME: this isn't correct, especially for Alpha (maximum != 255)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PIXEL_FROM_RGBA(Pixel, fmt, r, g, b, a)             \
    {                                                       \
        Pixel = ((r >> (8 - fmt->Rbits)) << fmt->Rshift) |  \
                ((g >> (8 - fmt->Gbits)) << fmt->Gshift) |  \
                ((b >> (8 - fmt->Bbits)) << fmt->Bshift) |  \
                ((a >> (8 - fmt->Abits)) << fmt->Ashift);   \
    }
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ASSEMBLE_RGBA(buf, bpp, fmt, r, g, b, a)       \
    {                                                  \
        ਚੋਣ (bpp) {                                 \
        ਹਾਲਤ 1:                                        \
        {                                              \
            Uint8 _pixel;                              \
                                                       \
            PIXEL_FROM_RGBA(_pixel, fmt, r, g, b, a);  \
            *((Uint8 *)(buf)) = _pixel;                \
        } ਰੋਕੋ;                                       \
                                                       \
        ਹਾਲਤ 2:                                        \
        {                                              \
            Uint16 _pixel;                             \
                                                       \
            PIXEL_FROM_RGBA(_pixel, fmt, r, g, b, a);  \
            *((Uint16 *)(buf)) = _pixel;               \
        } ਰੋਕੋ;                                       \
                                                       \
        ਹਾਲਤ 3:                                        \
        {                                              \
            GET_RGB24_COMPONENT(buf, fmt, Rshift) = r; \
            GET_RGB24_COMPONENT(buf, fmt, Gshift) = g; \
            GET_RGB24_COMPONENT(buf, fmt, Bshift) = b; \
        } ਰੋਕੋ;                                       \
                                                       \
        ਹਾਲਤ 4:                                        \
        {                                              \
            Uint32 _pixel;                             \
                                                       \
            PIXEL_FROM_RGBA(_pixel, fmt, r, g, b, a);  \
            *((Uint32 *)(buf)) = _pixel;               \
        } ਰੋਕੋ;                                       \
        }                                              \
    }

// Convert any 32-bit 4-bpp pixel to ARGB format
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PIXEL_ਮੰਜ਼ਿਲ_ARGB_PIXEL(src, srcfmt, dst)         \
    ਕਰੋ {                                              \
        Uint8 a, r, g, b;                         \
        RGBA_FROM_PIXEL(src, srcfmt, r, g, b, a); \
        dst = a << 24 | r << 16 | g << 8 | b;     \
    } ਜਦੋਂ (0)
// Blend a single color channel or alpha value
/* dC = ((sC * sA) + (dC * (255 - sA))) / 255 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ALPHA_BLEND_CHANNEL(sC, dC, sA)                  \
    ਕਰੋ {                                                 \
        Uint16 x;                                        \
        x = ((sC - dC) * sA) + ((dC << 8) - dC);         \
        x += 0x1U;                                       \
        x += x >> 8;                                     \
        dC = x >> 8;                                     \
    } ਜਦੋਂ (0)
// Perform a division by 255 after a multiplication of two 8-bit color channels
/* out = (sC * dC) / 255 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MULT_DIV_255(sC, dC, ਬਾਹਰਲਾ) \
    ਕਰੋ {                          \
        Uint16 x = sC * dC;       \
        x += 0x1U;                \
        x += x >> 8;              \
        ਬਾਹਰਲਾ = x >> 8;             \
    } ਜਦੋਂ (0)
// Blend the RGB values of two pixels with an alpha value
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ALPHA_BLEND_RGB(sR, sG, sB, A, dR, dG, dB)            \
    ਕਰੋ {                                                      \
        ALPHA_BLEND_CHANNEL(sR, dR, A);                       \
        ALPHA_BLEND_CHANNEL(sG, dG, A);                       \
        ALPHA_BLEND_CHANNEL(sB, dB, A);                       \
    } ਜਦੋਂ (0)

// Blend two 8888 pixels with the same format
/* Calculates dst = ((src * factor) + (dst * (255 - factor))) / 255 */
// FIXME: SDL_SIZE_MAX might not be an integer literal
#ਜੇ defined(SIZE_MAX) && (SIZE_MAX == 0xffffffffffffffff)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਗੁਣਕ_BLEND_8888(src, dst, ਗੁਣਕ)                        \
    ਕਰੋ {                                                           \
        Uint64 src64 = src;                                        \
        src64 = (src64 | (src64 << 24)) & 0x00FF00FF00FF00FF;      \
                                                                   \
        Uint64 dst64 = dst;                                        \
        dst64 = (dst64 | (dst64 << 24)) & 0x00FF00FF00FF00FF;      \
                                                                   \
        dst64 = ((src64 - dst64) * ਗੁਣਕ) + (dst64 << 8) - dst64; \
        dst64 += 0x0001000100010001;                               \
        dst64 += (dst64 >> 8) & 0x00FF00FF00FF00FF;                \
        dst64 &= 0xFF00FF00FF00FF00;                               \
                                                                   \
        dst = (Uint32)((dst64 >> 8) | (dst64 >> 32));              \
    } ਜਦੋਂ (0)
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਗੁਣਕ_BLEND_8888(src, dst, ਗੁਣਕ)                               \
    ਕਰੋ {                                                                  \
        Uint32 src02 = src & 0x00FF00FF;                                  \
        Uint32 dst02 = dst & 0x00FF00FF;                                  \
                                                                          \
        Uint32 src13 = (src >> 8) & 0x00FF00FF;                           \
        Uint32 dst13 = (dst >> 8) & 0x00FF00FF;                           \
                                                                          \
        Uint32 res02 = ((src02 - dst02) * ਗੁਣਕ) + (dst02 << 8) - dst02; \
        res02 += 0x00010001;                                              \
        res02 += (res02 >> 8) & 0x00FF00FF;                               \
        res02 = (res02 >> 8) & 0x00FF00FF;                                \
                                                                          \
        Uint32 res13 = ((src13 - dst13) * ਗੁਣਕ) + (dst13 << 8) - dst13; \
        res13 += 0x00010001;                                              \
        res13 += (res13 >> 8) & 0x00FF00FF;                               \
        res13 &= 0xFF00FF00;                                              \
        dst = res02 | res13;                                              \
    } ਜਦੋਂ (0)
#ਜੇ_ਅੰਤ

// Alpha blend two 8888 pixels with the same formats.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ALPHA_BLEND_8888(src, dst, fmt)            \
    ਕਰੋ {                                           \
        Uint32 srcA = (src >> fmt->Ashift) & 0xFF; \
        Uint32 tmp = src | fmt->Amask;             \
        ਗੁਣਕ_BLEND_8888(tmp, dst, srcA);         \
    } ਜਦੋਂ (0)

// Alpha blend two 8888 pixels with differing formats.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ALPHA_BLEND_SWIZZLE_8888(src, dst, srcfmt, dstfmt)                  \
    ਕਰੋ {                                                                    \
        Uint32 srcA = (src >> srcfmt->Ashift) & 0xFF;                       \
        Uint32 tmp = (((src >> srcfmt->Rshift) & 0xFF) << dstfmt->Rshift) | \
                     (((src >> srcfmt->Gshift) & 0xFF) << dstfmt->Gshift) | \
                     (((src >> srcfmt->Bshift) & 0xFF) << dstfmt->Bshift) | \
                     dstfmt->Amask;                                         \
        ਗੁਣਕ_BLEND_8888(tmp, dst, srcA);                                  \
    } ਜਦੋਂ (0)
// Blend the RGBA values of two pixels
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ALPHA_BLEND_RGBA(sR, sG, sB, sA, dR, dG, dB, dA) \
    ਕਰੋ {                                                 \
        ALPHA_BLEND_CHANNEL(sR, dR, sA);                 \
        ALPHA_BLEND_CHANNEL(sG, dG, sA);                 \
        ALPHA_BLEND_CHANNEL(sB, dB, sA);                 \
        ALPHA_BLEND_CHANNEL(255, dA, sA);                \
    } ਜਦੋਂ (0)

// This is a very useful loop for optimizing blitters
#ਜੇ defined(_MSC_VER) && (_MSC_VER == 1300)
// There's a bug in the Visual C++ 7 optimizer when compiling this code
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ USE_DUFFS_LOOP
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DUFFS_LOOP1(pixel_copy_increment, ਚੌੜਾਈ) \
    {                                            \
        ਪੂਰਨ n;                                   \
        ਲਈ (n = ਚੌੜਾਈ; n > 0; --n) {            \
            pixel_copy_increment;                \
        }                                        \
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ USE_DUFFS_LOOP

// 8-times unrolled loop
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DUFFS_LOOP8(pixel_copy_increment, ਚੌੜਾਈ) \
    {                                            \
        ਪੂਰਨ n = (ਚੌੜਾਈ + 7) / 8;                 \
        ਚੋਣ (ਚੌੜਾਈ & 7) {                     \
        ਹਾਲਤ 0:                                  \
            ਕਰੋ {                                 \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            ਹਾਲਤ 7:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            ਹਾਲਤ 6:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            ਹਾਲਤ 5:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            ਹਾਲਤ 4:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            ਹਾਲਤ 3:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            ਹਾਲਤ 2:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            ਹਾਲਤ 1:                              \
                pixel_copy_increment;            \
            } ਜਦੋਂ (--n > 0);                   \
        }                                        \
    }

// 4-times unrolled loop
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DUFFS_LOOP4(pixel_copy_increment, ਚੌੜਾਈ) \
    {                                            \
        ਪੂਰਨ n = (ਚੌੜਾਈ + 3) / 4;                 \
        ਚੋਣ (ਚੌੜਾਈ & 3) {                     \
        ਹਾਲਤ 0:                                  \
            ਕਰੋ {                                 \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            ਹਾਲਤ 3:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            ਹਾਲਤ 2:                              \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            ਹਾਲਤ 1:                              \
                pixel_copy_increment;            \
            } ਜਦੋਂ (--n > 0);                   \
        }                                        \
    }

// 2-times unrolled loop
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DUFFS_LOOP2(pixel_copy_increment, ਚੌੜਾਈ) \
    {                                            \
        ਪੂਰਨ n = (ਚੌੜਾਈ + 1) / 2;                 \
        ਚੋਣ (ਚੌੜਾਈ & 1) {                     \
        ਹਾਲਤ 0:                                  \
            ਕਰੋ {                                 \
                pixel_copy_increment;            \
                SDL_FALLTHROUGH;                 \
            ਹਾਲਤ 1:                              \
                pixel_copy_increment;            \
            } ਜਦੋਂ (--n > 0);                   \
        }                                        \
    }

// Use the 4-times version of the loop by default
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DUFFS_LOOP(pixel_copy_increment, ਚੌੜਾਈ) \
    DUFFS_LOOP4(pixel_copy_increment, ਚੌੜਾਈ)
// Use the 8-times version of the loop for simple routines
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DUFFS_LOOP_TRIVIAL(pixel_copy_increment, ਚੌੜਾਈ) \
    DUFFS_LOOP8(pixel_copy_increment, ਚੌੜਾਈ)

// Special version of Duff's device for even more optimization
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DUFFS_LOOP_124(pixel_copy_increment1,        \
                       pixel_copy_increment2,        \
                       pixel_copy_increment4, ਚੌੜਾਈ) \
    {                                                \
        ਪੂਰਨ n = ਚੌੜਾਈ;                               \
        ਜੇ (n & 1) {                                 \
            pixel_copy_increment1;                   \
            n -= 1;                                  \
        }                                            \
        ਜੇ (n & 2) {                                 \
            pixel_copy_increment2;                   \
            n -= 2;                                  \
        }                                            \
        ਜੇ (n & 4) {                                 \
            pixel_copy_increment4;                   \
            n -= 4;                                  \
        }                                            \
        ਜੇ (n) {                                     \
            n /= 8;                                  \
            ਕਰੋ {                                     \
                pixel_copy_increment4;               \
                pixel_copy_increment4;               \
            } ਜਦੋਂ (--n > 0);                       \
        }                                            \
    }

#ਨਹੀਂਤਾਂ

// Don't use Duff's device to unroll loops
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DUFFS_LOOP(pixel_copy_increment, ਚੌੜਾਈ) \
    DUFFS_LOOP1(pixel_copy_increment, ਚੌੜਾਈ)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DUFFS_LOOP_TRIVIAL(pixel_copy_increment, ਚੌੜਾਈ) \
    DUFFS_LOOP1(pixel_copy_increment, ਚੌੜਾਈ)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DUFFS_LOOP8(pixel_copy_increment, ਚੌੜਾਈ) \
    DUFFS_LOOP1(pixel_copy_increment, ਚੌੜਾਈ)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DUFFS_LOOP4(pixel_copy_increment, ਚੌੜਾਈ) \
    DUFFS_LOOP1(pixel_copy_increment, ਚੌੜਾਈ)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DUFFS_LOOP2(pixel_copy_increment, ਚੌੜਾਈ) \
    DUFFS_LOOP1(pixel_copy_increment, ਚੌੜਾਈ)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DUFFS_LOOP_124(pixel_copy_increment1,        \
                       pixel_copy_increment2,        \
                       pixel_copy_increment4, ਚੌੜਾਈ) \
    DUFFS_LOOP1(pixel_copy_increment1, ਚੌੜਾਈ)

#ਜੇ_ਅੰਤ // USE_DUFFS_LOOP

#ਜੇ defined(_MSC_VER) && (_MSC_VER >= 600)
#ਹਦਾਇਤ warning(disable : 4244) // '=': conversion from 'X' to 'Y', possible loss of data
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ // SDL_blit_h_
