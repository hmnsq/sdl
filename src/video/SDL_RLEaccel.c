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

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_HAVE_RLE

/*
 * RLE encoding for software colorkey and alpha-channel acceleration
 *
 * Original version by Sam Lantinga
 *
 * Mattias Engdegård (Yorick): Rewrite. New encoding format, encoder and
 * decoder. Added per-surface alpha blitter. Added per-pixel alpha
 * format, encoder and blitter.
 *
 * Many thanks to Xark and johns for hints, benchmarks and useful comments
 * leading to this code.
 *
 * Welcome to Macro Mayhem.
 */

/*
 * The encoding translates the image data to a stream of segments of the form
 *
 * <skip> <run> <data>
 *
 * where <skip> is the number of transparent pixels to skip,
 *       <run>  is the number of opaque pixels to blit,
 * and   <data> are the pixels themselves.
 *
 * This basic structure is used both for colorkeyed surfaces, used for simple
 * binary transparency and for per-surface alpha blending, and for surfaces
 * with per-pixel alpha. The details differ, however:
 *
 * Encoding of colorkeyed surfaces:
 *
 *   Encoded pixels always have the same format as the target surface.
 *   <skip> and <run> are unsigned 8 bit integers, except for 32 bit depth
 *   where they are 16 bit. This makes the pixel data aligned at all times.
 *   Segments never wrap around from one scan line to the next.
 *
 *   The end of the sequence is marked by a zero <skip>,<run> pair at the *
 *   beginning of a line.
 *
 * Encoding of surfaces with per-pixel alpha:
 *
 *   The sequence begins with an SDL_PixelFormat value describing the target
 *   pixel format, to provide reliable un-encoding.
 *
 *   Each scan line is encoded twice: First all completely opaque pixels,
 *   encoded in the target format as described above, and then all
 *   partially transparent (translucent) pixels (where 1 <= alpha <= 254),
 *   in the following 32-bit format:
 *
 *   For 32-bit targets, each pixel has the target RGB format but with
 *   the alpha value occupying the highest 8 bits. The <skip> and <run>
 *   counts are 16 bit.
 *
 *   For 16-bit targets, each pixel has the target RGB format, but with
 *   the middle component (usually green) shifted 16 steps to the left,
 *   and the hole filled with the 5 most significant bits of the alpha value.
 *   i.e. if the target has the format         rrrrrggggggbbbbb,
 *   the encoded pixel will be 00000gggggg00000rrrrr0aaaaabbbbb.
 *   The <skip> and <run> counts are 8 bit for the opaque lines, 16 bit
 *   for the translucent lines. Two padding bytes may be inserted
 *   before each translucent line to keep them 32-bit aligned.
 *
 *   The end of the sequence is marked by a zero <skip>,<run> pair at the
 *   beginning of an opaque line.
 */

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_sysvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_surface_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_pixels_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_RLEaccel_c.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PIXEL_COPY(ਮੰਜ਼ਿਲ, from, len, bpp) \
    SDL_memcpy(ਮੰਜ਼ਿਲ, from, (size_t)(len) * (bpp))

/*
 * Various colorkey blit methods, for opaque and per-surface alpha
 */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OPAQUE_BLIT(ਮੰਜ਼ਿਲ, from, ਲੰਮਾਈ, bpp, alpha) \
    PIXEL_COPY(ਮੰਜ਼ਿਲ, from, ਲੰਮਾਈ, bpp)

/*
 * For 32bpp pixels on the form 0x00rrggbb:
 * If we treat the middle component separately, we can process the two
 * remaining in parallel. This is safe to do because of the gap to the left
 * of each component, so the bits from the multiplication don't collide.
 * This can be used for any RGB permutation of course.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ALPHA_BLIT32_888(ਮੰਜ਼ਿਲ, from, ਲੰਮਾਈ, bpp, alpha)       \
    ਕਰੋ {                                                     \
        ਪੂਰਨ i;                                               \
        Uint32 *src = (Uint32 *)(from);                      \
        Uint32 *dst = (Uint32 *)(ਮੰਜ਼ਿਲ);                        \
        ਲਈ (i = 0; i < (ਪੂਰਨ)(ਲੰਮਾਈ); i++) {                \
            Uint32 s = *src++;                               \
            Uint32 d = *dst;                                 \
            Uint32 s1 = s & 0xff00ff;                        \
            Uint32 d1 = d & 0xff00ff;                        \
            d1 = (d1 + ((s1 - d1) * alpha >> 8)) & 0xff00ff; \
            s &= 0xff00;                                     \
            d &= 0xff00;                                     \
            d = (d + ((s - d) * alpha >> 8)) & 0xff00;       \
            *dst++ = d1 | d;                                 \
        }                                                    \
    } ਜਦੋਂ (0)

/*
 * For 16bpp pixels we can go a step further: put the middle component
 * in the high 16 bits of a 32 bit word, and process all three RGB
 * components at the same time. Since the smallest gap is here just
 * 5 bits, we have to scale alpha down to 5 bits as well.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ALPHA_BLIT16_565(ਮੰਜ਼ਿਲ, from, ਲੰਮਾਈ, bpp, alpha) \
    ਕਰੋ {                                               \
        ਪੂਰਨ i;                                         \
        Uint16 *src = (Uint16 *)(from);                \
        Uint16 *dst = (Uint16 *)(ਮੰਜ਼ਿਲ);                  \
        Uint32 ALPHA = alpha >> 3;                     \
        ਲਈ (i = 0; i < (ਪੂਰਨ)(ਲੰਮਾਈ); i++) {          \
            Uint32 s = *src++;                         \
            Uint32 d = *dst;                           \
            s = (s | s << 16) & 0x07e0f81f;            \
            d = (d | d << 16) & 0x07e0f81f;            \
            d += (s - d) * ALPHA >> 5;                 \
            d &= 0x07e0f81f;                           \
            *dst++ = (Uint16)(d | d >> 16);            \
        }                                              \
    } ਜਦੋਂ (0)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ALPHA_BLIT16_555(ਮੰਜ਼ਿਲ, from, ਲੰਮਾਈ, bpp, alpha) \
    ਕਰੋ {                                               \
        ਪੂਰਨ i;                                         \
        Uint16 *src = (Uint16 *)(from);                \
        Uint16 *dst = (Uint16 *)(ਮੰਜ਼ਿਲ);                  \
        Uint32 ALPHA = alpha >> 3;                     \
        ਲਈ (i = 0; i < (ਪੂਰਨ)(ਲੰਮਾਈ); i++) {          \
            Uint32 s = *src++;                         \
            Uint32 d = *dst;                           \
            s = (s | s << 16) & 0x03e07c1f;            \
            d = (d | d << 16) & 0x03e07c1f;            \
            d += (s - d) * ALPHA >> 5;                 \
            d &= 0x03e07c1f;                           \
            *dst++ = (Uint16)(d | d >> 16);            \
        }                                              \
    } ਜਦੋਂ (0)

/*
 * The general slow catch-all function, for remaining depths and formats
 */
#ਜੇ SDL_BYTEORDER == SDL_BIG_ENDIAN
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਸੈੱਟ_RGB24(dst, d)      \
    dst[0] = (Uint8)(d >> 16); \
    dst[1] = (Uint8)(d >> 8);  \
    dst[2] = (Uint8)(d);
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਸੈੱਟ_RGB24(dst, d)      \
    dst[0] = (Uint8)(d);       \
    dst[1] = (Uint8)(d >> 8);  \
    dst[2] = (Uint8)(d >> 16);
#ਜੇ_ਅੰਤ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ALPHA_BLIT_ANY(ਮੰਜ਼ਿਲ, from, ਲੰਮਾਈ, bpp, alpha)             \
    ਕਰੋ {                                                         \
        ਪੂਰਨ i;                                                   \
        Uint8 *src = from;                                       \
        Uint8 *dst = ਮੰਜ਼ਿਲ;                                         \
        ਲਈ (i = 0; i < (ਪੂਰਨ)(ਲੰਮਾਈ); i++) {                    \
            Uint32 s = 0, d = 0;                                 \
            ਬਿਨਾਨਿਸ਼ਾਨੀ rs, gs, bs, rd, gd, bd;                     \
            ਚੋਣ (bpp) {                                       \
            ਹਾਲਤ 2:                                              \
                s = *(Uint16 *)src;                              \
                d = *(Uint16 *)dst;                              \
                ਰੋਕੋ;                                           \
            ਹਾਲਤ 3:                                              \
                s = GET_RGB24(src);                              \
                d = GET_RGB24(dst);                              \
                ਰੋਕੋ;                                           \
            ਹਾਲਤ 4:                                              \
                s = *(Uint32 *)src;                              \
                d = *(Uint32 *)dst;                              \
                ਰੋਕੋ;                                           \
            }                                                    \
            RGB_FROM_PIXEL(s, fmt, rs, gs, bs);                  \
            RGB_FROM_PIXEL(d, fmt, rd, gd, bd);                  \
            rd += (rs - rd) * alpha >> 8;                        \
            gd += (gs - gd) * alpha >> 8;                        \
            bd += (bs - bd) * alpha >> 8;                        \
            PIXEL_FROM_RGB(d, fmt, rd, gd, bd);                  \
            ਚੋਣ (bpp) {                                       \
            ਹਾਲਤ 2:                                              \
                *(Uint16 *)dst = (Uint16)d;                      \
                ਰੋਕੋ;                                           \
            ਹਾਲਤ 3:                                              \
                ਸੈੱਟ_RGB24(dst, d);                               \
                ਰੋਕੋ;                                           \
            ਹਾਲਤ 4:                                              \
                *(Uint32 *)dst = d;                              \
                ਰੋਕੋ;                                           \
            }                                                    \
            src += bpp;                                          \
            dst += bpp;                                          \
        }                                                        \
    } ਜਦੋਂ (0)

/*
 * Special case: 50% alpha (alpha=128)
 * This is treated specially because it can be optimized very well, and
 * since it is good for many cases of semi-translucency.
 * The theory is to do all three components at the same time:
 * First zero the lowest bit of each component, which gives us room to
 * add them. Then shift right and add the sum of the lowest bits.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ALPHA_BLIT32_888_50(ਮੰਜ਼ਿਲ, from, ਲੰਮਾਈ, bpp, alpha)                                 \
    ਕਰੋ {                                                                                  \
        ਪੂਰਨ i;                                                                            \
        Uint32 *src = (Uint32 *)(from);                                                   \
        Uint32 *dst = (Uint32 *)(ਮੰਜ਼ਿਲ);                                                     \
        ਲਈ (i = 0; i < (ਪੂਰਨ)(ਲੰਮਾਈ); i++) {                                             \
            Uint32 s = *src++;                                                            \
            Uint32 d = *dst;                                                              \
            *dst++ = (((s & 0x00fefefe) + (d & 0x00fefefe)) >> 1) + (s & d & 0x00010101); \
        }                                                                                 \
    } ਜਦੋਂ (0)

/*
 * For 16bpp, we can actually blend two pixels in parallel, if we take
 * care to shift before we add, not after.
 */

// helper: blend a single 16 bit pixel at 50%
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BLEND16_50(dst, src, ਨਕਾਬ)                           \
    ਕਰੋ {                                                     \
        Uint32 s = *src++;                                   \
        Uint32 d = *dst;                                     \
        *dst++ = (Uint16)((((s & ਨਕਾਬ) + (d & ਨਕਾਬ)) >> 1) + \
                          (s & d & (~ਨਕਾਬ & 0xffff)));       \
    } ਜਦੋਂ (0)

// basic 16bpp blender. mask is the pixels to keep when adding.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ALPHA_BLIT16_50(ਮੰਜ਼ਿਲ, from, ਲੰਮਾਈ, bpp, alpha, ਨਕਾਬ)                                                                              \
    ਕਰੋ {                                                                                                                                 \
        ਬਿਨਾਨਿਸ਼ਾਨੀ n = (ਲੰਮਾਈ);                                                                                                           \
        Uint16 *src = (Uint16 *)(from);                                                                                                  \
        Uint16 *dst = (Uint16 *)(ਮੰਜ਼ਿਲ);                                                                                                    \
        ਜੇ (((uintptr_t)src ^ (uintptr_t)dst) & 3) {                                                                                     \
            /* source and destination not in phase, blit one by one */                                                                   \
            ਜਦੋਂ (n--)                                                                                                                  \
                BLEND16_50(dst, src, ਨਕਾਬ);                                                                                              \
        } ਨਹੀਂਤਾਂ {                                                                                                                         \
            ਜੇ ((uintptr_t)src & 3) {                                                                                                    \
                /* first odd pixel */                                                                                                    \
                BLEND16_50(dst, src, ਨਕਾਬ);                                                                                              \
                n--;                                                                                                                     \
            }                                                                                                                            \
            ਲਈ (; n > 1; n -= 2) {                                                                                                      \
                Uint32 s = *(Uint32 *)src;                                                                                               \
                Uint32 d = *(Uint32 *)dst;                                                                                               \
                *(Uint32 *)dst = ((s & (ਨਕਾਬ | ਨਕਾਬ << 16)) >> 1) + ((d & (ਨਕਾਬ | ਨਕਾਬ << 16)) >> 1) + (s & d & (~(ਨਕਾਬ | ਨਕਾਬ << 16))); \
                src += 2;                                                                                                                \
                dst += 2;                                                                                                                \
            }                                                                                                                            \
            ਜੇ (n)                                                                                                                       \
                BLEND16_50(dst, src, ਨਕਾਬ); /* last odd pixel */                                                                         \
        }                                                                                                                                \
    } ਜਦੋਂ (0)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ALPHA_BLIT16_565_50(ਮੰਜ਼ਿਲ, from, ਲੰਮਾਈ, bpp, alpha) \
    ALPHA_BLIT16_50(ਮੰਜ਼ਿਲ, from, ਲੰਮਾਈ, bpp, alpha, 0xf7deU)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ALPHA_BLIT16_555_50(ਮੰਜ਼ਿਲ, from, ਲੰਮਾਈ, bpp, alpha) \
    ALPHA_BLIT16_50(ਮੰਜ਼ਿਲ, from, ਲੰਮਾਈ, bpp, alpha, 0xfbdeU)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਚੁਣੋ_BLIT(blitter, alpha, fmt)                                                                                                              \
    ਕਰੋ {                                                                                                                                              \
        ਜੇ (alpha == 255) {                                                                                                                           \
            ਚੋਣ (fmt->ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel) {                                                                                                             \
            ਹਾਲਤ 1:                                                                                                                                   \
                blitter(1, Uint8, OPAQUE_BLIT);                                                                                                       \
                ਰੋਕੋ;                                                                                                                                \
            ਹਾਲਤ 2:                                                                                                                                   \
                blitter(2, Uint8, OPAQUE_BLIT);                                                                                                       \
                ਰੋਕੋ;                                                                                                                                \
            ਹਾਲਤ 3:                                                                                                                                   \
                blitter(3, Uint8, OPAQUE_BLIT);                                                                                                       \
                ਰੋਕੋ;                                                                                                                                \
            ਹਾਲਤ 4:                                                                                                                                   \
                blitter(4, Uint16, OPAQUE_BLIT);                                                                                                      \
                ਰੋਕੋ;                                                                                                                                \
            }                                                                                                                                         \
        } ਨਹੀਂਤਾਂ {                                                                                                                                      \
            ਚੋਣ (fmt->ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel) {                                                                                                             \
            ਹਾਲਤ 1:                                                                                                                                   \
                /* No 8bpp alpha blitting */                                                                                                          \
                ਰੋਕੋ;                                                                                                                                \
                                                                                                                                                      \
            ਹਾਲਤ 2:                                                                                                                                   \
                ਚੋਣ (fmt->Rmask | fmt->Gmask | fmt->Bmask) {                                                                                       \
                ਹਾਲਤ 0xffff:                                                                                                                          \
                    ਜੇ (fmt->Gmask == 0x07e0 || fmt->Rmask == 0x07e0 || fmt->Bmask == 0x07e0) {                                                       \
                        ਜੇ (alpha == 128) {                                                                                                           \
                            blitter(2, Uint8, ALPHA_BLIT16_565_50);                                                                                   \
                        } ਨਹੀਂਤਾਂ {                                                                                                                      \
                            blitter(2, Uint8, ALPHA_BLIT16_565);                                                                                      \
                        }                                                                                                                             \
                    } ਨਹੀਂਤਾਂ {                                                                                                                          \
                        ਜਾਓ general16;                                                                                                               \
                    }                                                                                                                                 \
                    ਰੋਕੋ;                                                                                                                            \
                                                                                                                                                      \
                ਹਾਲਤ 0x7fff:                                                                                                                          \
                    ਜੇ (fmt->Gmask == 0x03e0 || fmt->Rmask == 0x03e0 || fmt->Bmask == 0x03e0) {                                                       \
                        ਜੇ (alpha == 128) {                                                                                                           \
                            blitter(2, Uint8, ALPHA_BLIT16_555_50);                                                                                   \
                        } ਨਹੀਂਤਾਂ {                                                                                                                      \
                            blitter(2, Uint8, ALPHA_BLIT16_555);                                                                                      \
                        }                                                                                                                             \
                        ਰੋਕੋ;                                                                                                                        \
                    } ਨਹੀਂਤਾਂ {                                                                                                                          \
                        ਜਾਓ general16;                                                                                                               \
                    }                                                                                                                                 \
                    ਰੋਕੋ;                                                                                                                            \
                                                                                                                                                      \
                ਮੂਲ:                                                                                                                              \
                general16:                                                                                                                            \
                    blitter(2, Uint8, ALPHA_BLIT_ANY);                                                                                                \
                }                                                                                                                                     \
                ਰੋਕੋ;                                                                                                                                \
                                                                                                                                                      \
            ਹਾਲਤ 3:                                                                                                                                   \
                blitter(3, Uint8, ALPHA_BLIT_ANY);                                                                                                    \
                ਰੋਕੋ;                                                                                                                                \
                                                                                                                                                      \
            ਹਾਲਤ 4:                                                                                                                                   \
                ਜੇ ((fmt->Rmask | fmt->Gmask | fmt->Bmask) == 0x00ffffff && (fmt->Gmask == 0xff00 || fmt->Rmask == 0xff00 || fmt->Bmask == 0xff00)) { \
                    ਜੇ (alpha == 128) {                                                                                                               \
                        blitter(4, Uint16, ALPHA_BLIT32_888_50);                                                                                      \
                    } ਨਹੀਂਤਾਂ {                                                                                                                          \
                        blitter(4, Uint16, ALPHA_BLIT32_888);                                                                                         \
                    }                                                                                                                                 \
                } ਨਹੀਂਤਾਂ {                                                                                                                              \
                    blitter(4, Uint16, ALPHA_BLIT_ANY);                                                                                               \
                }                                                                                                                                     \
                ਰੋਕੋ;                                                                                                                                \
            }                                                                                                                                         \
        }                                                                                                                                             \
    } ਜਦੋਂ (0)

/*
 * Set a pixel value using the given format, except that the alpha value is
 * placed in the top byte. This is the format used for RLE with alpha.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RLEPIXEL_FROM_RGBA(Pixel, fmt, r, g, b, a)   \
    {                                                \
        Pixel = ((r >> (8 - fmt->Rbits)) << fmt->Rshift) | \
                ((g >> (8 - fmt->Gbits)) << fmt->Gshift) | \
                ((b >> (8 - fmt->Bbits)) << fmt->Bshift) | \
                (a << 24);                           \
    }

/*
 * This takes care of the case when the surface is clipped on the left and/or
 * right. Top clipping has already been taken care of.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RLECLIPBLIT(bpp, Type, do_blit)                                    \
    ਕਰੋ {                                                                   \
        ਪੂਰਨ linecount = srcrect->h;                                        \
        ਪੂਰਨ ofs = 0;                                                       \
        ਪੂਰਨ ਖੱਬਾ = srcrect->x;                                             \
        ਪੂਰਨ ਸੱਜਾ = ਖੱਬਾ + srcrect->w;                                     \
        dstbuf -= ਖੱਬਾ * bpp;                                              \
        ਲਈ (;;) {                                                         \
            ਪੂਰਨ ਲੜੀਵਾਰ;                                                       \
            ofs += *(Type *)srcbuf;                                        \
            ਲੜੀਵਾਰ = ((Type *)srcbuf)[1];                                     \
            srcbuf += 2 * ਆਕਾਰ(Type);                                    \
            ਜੇ (ਲੜੀਵਾਰ) {                                                     \
                /* clip to left and right borders */                       \
                ਜੇ (ofs < ਸੱਜਾ) {                                         \
                    ਪੂਰਨ ਸ਼ੁਰੂ = 0;                                         \
                    ਪੂਰਨ len = ਲੜੀਵਾਰ;                                         \
                    ਪੂਰਨ startcol;                                          \
                    ਜੇ (ਖੱਬਾ - ofs > 0) {                                  \
                        ਸ਼ੁਰੂ = ਖੱਬਾ - ofs;                                \
                        len -= ਸ਼ੁਰੂ;                                      \
                        ਜੇ (len <= 0)                                      \
                            ਜਾਓ nocopy##bpp##do_blit;                     \
                    }                                                      \
                    startcol = ofs + ਸ਼ੁਰੂ;                                \
                    ਜੇ (len > ਸੱਜਾ - startcol)                            \
                        len = ਸੱਜਾ - startcol;                            \
                    do_blit(dstbuf + startcol * bpp, srcbuf + ਸ਼ੁਰੂ * bpp, \
                            len, bpp, alpha);                              \
                }                                                          \
                nocopy##bpp##do_blit : srcbuf += ਲੜੀਵਾਰ * bpp;                \
                ofs += ਲੜੀਵਾਰ;                                                \
            } ਨਹੀਂਤਾਂ ਜੇ (!ofs) {                                             \
                ਰੋਕੋ;                                                     \
            }                                                              \
                                                                           \
            ਜੇ (ofs == w) {                                                \
                ofs = 0;                                                   \
                dstbuf += surf_dst->pitch;                                 \
                ਜੇ (!--linecount) {                                        \
                    ਰੋਕੋ;                                                 \
                }                                                          \
            }                                                              \
        }                                                                  \
    } ਜਦੋਂ (0)

ਸਥਿਰ ਖਾਲੀ RLEClipBlit(ਪੂਰਨ w, Uint8 *srcbuf, SDL_Surface *surf_dst,
                        Uint8 *dstbuf, ਅਚਲ SDL_Rect *srcrect, ਬਿਨਾਨਿਸ਼ਾਨੀ alpha)
{
    ਅਚਲ SDL_PixelFormatDetails *fmt = surf_dst->fmt;

    ਚੁਣੋ_BLIT(RLECLIPBLIT, alpha, fmt);
}

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ RLECLIPBLIT

// blit a colorkeyed RLE surface
ਸਥਿਰ bool SDLCALL SDL_RLEBlit(SDL_Surface *surf_src, ਅਚਲ SDL_Rect *srcrect,
                                SDL_Surface *surf_dst, ਅਚਲ SDL_Rect *dstrect)
{
    Uint8 *dstbuf;
    Uint8 *srcbuf;
    ਪੂਰਨ x, y;
    ਪੂਰਨ w = surf_src->w;
    ਬਿਨਾਨਿਸ਼ਾਨੀ alpha;

    // Lock the destination if necessary
    ਜੇ (SDL_MUSTLOCK(surf_dst)) {
        ਜੇ (!SDL_ਤਾਲਾ_Surface(surf_dst)) {
            ਵਾਪਸ false;
        }
    }

    // Set up the source and destination pointers
    x = dstrect->x;
    y = dstrect->y;
    dstbuf = (Uint8 *)surf_dst->pixels + y * surf_dst->pitch + x * surf_src->fmt->ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel;
    srcbuf = (Uint8 *)surf_src->map.ਅੰਕੜੇ + ਆਕਾਰ(SDL_PixelFormat);

    {
        // skip lines at the top if necessary
        ਪੂਰਨ vskip = srcrect->y;
        ਪੂਰਨ ofs = 0;
        ਜੇ (vskip) {

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RLESKIP(bpp, Type)          \
    ਲਈ (;;) {                      \
        ਪੂਰਨ ਲੜੀਵਾਰ;                    \
        ofs += *(Type *)srcbuf;     \
        ਲੜੀਵਾਰ = ((Type *)srcbuf)[1];  \
        srcbuf += ਆਕਾਰ(Type) * 2; \
        ਜੇ (ਲੜੀਵਾਰ) {                  \
            srcbuf += ਲੜੀਵਾਰ * bpp;    \
            ofs += ਲੜੀਵਾਰ;             \
        } ਨਹੀਂਤਾਂ ਜੇ (!ofs)            \
            ਜਾਓ ਪੂਰਾ;              \
        ਜੇ (ofs == w) {             \
            ofs = 0;                \
            ਜੇ (!--vskip)           \
                ਰੋਕੋ;              \
        }                           \
    }

            ਚੋਣ (surf_src->fmt->ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel) {
            ਹਾਲਤ 1:
                RLESKIP(1, Uint8);
                ਰੋਕੋ;
            ਹਾਲਤ 2:
                RLESKIP(2, Uint8);
                ਰੋਕੋ;
            ਹਾਲਤ 3:
                RLESKIP(3, Uint8);
                ਰੋਕੋ;
            ਹਾਲਤ 4:
                RLESKIP(4, Uint16);
                ਰੋਕੋ;
            }

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ RLESKIP
        }
    }

    alpha = surf_src->map.info.a;
    // if left or right edge clipping needed, call clip blit
    ਜੇ (srcrect->x || srcrect->w != surf_src->w) {
        RLEClipBlit(w, srcbuf, surf_dst, dstbuf, srcrect, alpha);
    } ਨਹੀਂਤਾਂ {
        ਅਚਲ SDL_PixelFormatDetails *fmt = surf_src->fmt;

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RLEBLIT(bpp, Type, do_blit)                                   \
    ਕਰੋ {                                                              \
        ਪੂਰਨ linecount = srcrect->h;                                   \
        ਪੂਰਨ ofs = 0;                                                  \
        ਲਈ (;;) {                                                    \
            ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੜੀਵਾਰ;                                             \
            ofs += *(Type *)srcbuf;                                   \
            ਲੜੀਵਾਰ = ((Type *)srcbuf)[1];                                \
            srcbuf += 2 * ਆਕਾਰ(Type);                               \
            ਜੇ (ਲੜੀਵਾਰ) {                                                \
                do_blit(dstbuf + ofs * bpp, srcbuf, ਲੜੀਵਾਰ, bpp, alpha); \
                srcbuf += ਲੜੀਵਾਰ * bpp;                                  \
                ofs += ਲੜੀਵਾਰ;                                           \
            } ਨਹੀਂਤਾਂ ਜੇ (!ofs)                                          \
                ਰੋਕੋ;                                                \
            ਜੇ (ofs == w) {                                           \
                ofs = 0;                                              \
                dstbuf += surf_dst->pitch;                            \
                ਜੇ (!--linecount)                                     \
                    ਰੋਕੋ;                                            \
            }                                                         \
        }                                                             \
    } ਜਦੋਂ (0)

        ਚੁਣੋ_BLIT(RLEBLIT, alpha, fmt);

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ RLEBLIT
    }

ਪੂਰਾ:
    // Unlock the destination if necessary
    ਜੇ (SDL_MUSTLOCK(surf_dst)) {
        SDL_UnlockSurface(surf_dst);
    }
    ਵਾਪਸ true;
}

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ OPAQUE_BLIT

/*
 * Per-pixel blitting macros for translucent pixels:
 * These use the same techniques as the per-surface blitting macros
 */

/*
 * For 32bpp pixels, we have made sure the alpha is stored in the top
 * 8 bits, so proceed as usual
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BLIT_TRANSL_888(src, dst)                        \
    ਕਰੋ {                                                 \
        Uint32 s = src;                                  \
        Uint32 d = dst;                                  \
        ਬਿਨਾਨਿਸ਼ਾਨੀ alpha = s >> 24;                        \
        Uint32 s1 = s & 0xff00ff;                        \
        Uint32 d1 = d & 0xff00ff;                        \
        d1 = (d1 + ((s1 - d1) * alpha >> 8)) & 0xff00ff; \
        s &= 0xff00;                                     \
        d &= 0xff00;                                     \
        d = (d + ((s - d) * alpha >> 8)) & 0xff00;       \
        dst = d1 | d | 0xff000000;                       \
    } ਜਦੋਂ (0)

/*
 * For 16bpp pixels, we have stored the 5 most significant alpha bits in
 * bits 5-10. As before, we can process all 3 RGB components at the same time.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BLIT_TRANSL_565(src, dst)          \
    ਕਰੋ {                                   \
        Uint32 s = src;                    \
        Uint32 d = dst;                    \
        ਬਿਨਾਨਿਸ਼ਾਨੀ alpha = (s & 0x3e0) >> 5; \
        s &= 0x07e0f81f;                   \
        d = (d | d << 16) & 0x07e0f81f;    \
        d += (s - d) * alpha >> 5;         \
        d &= 0x07e0f81f;                   \
        dst = (Uint16)(d | d >> 16);       \
    } ਜਦੋਂ (0)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BLIT_TRANSL_555(src, dst)          \
    ਕਰੋ {                                   \
        Uint32 s = src;                    \
        Uint32 d = dst;                    \
        ਬਿਨਾਨਿਸ਼ਾਨੀ alpha = (s & 0x3e0) >> 5; \
        s &= 0x03e07c1f;                   \
        d = (d | d << 16) & 0x03e07c1f;    \
        d += (s - d) * alpha >> 5;         \
        d &= 0x03e07c1f;                   \
        dst = (Uint16)(d | d >> 16);       \
    } ਜਦੋਂ (0)

// blit a pixel-alpha RLE surface clipped at the right and/or left edges
ਸਥਿਰ ਖਾਲੀ RLEAlphaClipBlit(ਪੂਰਨ w, Uint8 *srcbuf, SDL_Surface *surf_dst,
                             Uint8 *dstbuf, ਅਚਲ SDL_Rect *srcrect)
{
    ਅਚਲ SDL_PixelFormatDetails *df = surf_dst->fmt;
    /*
     * clipped blitter: Ptype is the destination pixel type,
     * Ctype the translucent count type, and do_blend the macro
     * to blend one pixel.
     */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RLEALPHACLIPBLIT(Ptype, Ctype, do_blend)                          \
    ਕਰੋ {                                                                  \
        ਪੂਰਨ linecount = srcrect->h;                                       \
        ਪੂਰਨ ਖੱਬਾ = srcrect->x;                                            \
        ਪੂਰਨ ਸੱਜਾ = ਖੱਬਾ + srcrect->w;                                    \
        dstbuf -= ਖੱਬਾ * ਆਕਾਰ(Ptype);                                   \
        ਕਰੋ {                                                              \
            ਪੂਰਨ ofs = 0;                                                  \
            /* blit opaque pixels on one line */                          \
            ਕਰੋ {                                                          \
                ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੜੀਵਾਰ;                                             \
                ofs += ((Ctype *)srcbuf)[0];                              \
                ਲੜੀਵਾਰ = ((Ctype *)srcbuf)[1];                               \
                srcbuf += 2 * ਆਕਾਰ(Ctype);                              \
                ਜੇ (ਲੜੀਵਾਰ) {                                                \
                    /* clip to left and right borders */                  \
                    ਪੂਰਨ cofs = ofs;                                       \
                    ਪੂਰਨ crun = ਲੜੀਵਾਰ;                                       \
                    ਜੇ (ਖੱਬਾ - cofs > 0) {                                \
                        crun -= ਖੱਬਾ - cofs;                              \
                        cofs = ਖੱਬਾ;                                      \
                    }                                                     \
                    ਜੇ (crun > ਸੱਜਾ - cofs)                              \
                        crun = ਸੱਜਾ - cofs;                              \
                    ਜੇ (crun > 0)                                         \
                        PIXEL_COPY(dstbuf + cofs * ਆਕਾਰ(Ptype),         \
                                   srcbuf + (cofs - ofs) * ਆਕਾਰ(Ptype), \
                                   (ਬਿਨਾਨਿਸ਼ਾਨੀ)crun, ਆਕਾਰ(Ptype));        \
                    srcbuf += ਲੜੀਵਾਰ * ਆਕਾਰ(Ptype);                        \
                    ofs += ਲੜੀਵਾਰ;                                           \
                } ਨਹੀਂਤਾਂ ਜੇ (!ofs)                                          \
                    ਵਾਪਸ;                                               \
            } ਜਦੋਂ (ofs < w);                                            \
            /* skip padding if necessary */                               \
            ਅਚਲ size_t psize = ਆਕਾਰ(Ptype);                           \
            ਜੇ (psize == 2)                                               \
                srcbuf += (uintptr_t)srcbuf & 2;                          \
            /* blit translucent pixels on the same line */                \
            ofs = 0;                                                      \
            ਕਰੋ {                                                          \
                ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੜੀਵਾਰ;                                             \
                ofs += ((Uint16 *)srcbuf)[0];                             \
                ਲੜੀਵਾਰ = ((Uint16 *)srcbuf)[1];                              \
                srcbuf += 4;                                              \
                ਜੇ (ਲੜੀਵਾਰ) {                                                \
                    /* clip to left and right borders */                  \
                    ਪੂਰਨ cofs = ofs;                                       \
                    ਪੂਰਨ crun = ਲੜੀਵਾਰ;                                       \
                    ਜੇ (ਖੱਬਾ - cofs > 0) {                                \
                        crun -= ਖੱਬਾ - cofs;                              \
                        cofs = ਖੱਬਾ;                                      \
                    }                                                     \
                    ਜੇ (crun > ਸੱਜਾ - cofs)                              \
                        crun = ਸੱਜਾ - cofs;                              \
                    ਜੇ (crun > 0) {                                       \
                        Ptype *dst = (Ptype *)dstbuf + cofs;              \
                        Uint32 *src = (Uint32 *)srcbuf + (cofs - ofs);    \
                        ਪੂਰਨ i;                                            \
                        ਲਈ (i = 0; i < crun; i++)                        \
                            do_blend(src[i], dst[i]);                     \
                    }                                                     \
                    srcbuf += ਲੜੀਵਾਰ * 4;                                    \
                    ofs += ਲੜੀਵਾਰ;                                           \
                }                                                         \
            } ਜਦੋਂ (ofs < w);                                            \
            dstbuf += surf_dst->pitch;                                    \
        } ਜਦੋਂ (--linecount);                                            \
    } ਜਦੋਂ (0)

    ਚੋਣ (df->ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel) {
    ਹਾਲਤ 2:
        ਜੇ (df->Gmask == 0x07e0 || df->Rmask == 0x07e0 || df->Bmask == 0x07e0) {
            RLEALPHACLIPBLIT(Uint16, Uint8, BLIT_TRANSL_565);
        } ਨਹੀਂਤਾਂ {
            RLEALPHACLIPBLIT(Uint16, Uint8, BLIT_TRANSL_555);
        }
        ਰੋਕੋ;
    ਹਾਲਤ 4:
        RLEALPHACLIPBLIT(Uint32, Uint16, BLIT_TRANSL_888);
        ਰੋਕੋ;
    }
}

// blit a pixel-alpha RLE surface
ਸਥਿਰ bool SDLCALL SDL_RLEAlphaBlit(SDL_Surface *surf_src, ਅਚਲ SDL_Rect *srcrect,
                                     SDL_Surface *surf_dst, ਅਚਲ SDL_Rect *dstrect)
{
    ਪੂਰਨ x, y;
    ਪੂਰਨ w = surf_src->w;
    Uint8 *srcbuf, *dstbuf;
    ਅਚਲ SDL_PixelFormatDetails *df = surf_dst->fmt;

    // Lock the destination if necessary
    ਜੇ (SDL_MUSTLOCK(surf_dst)) {
        ਜੇ (!SDL_ਤਾਲਾ_Surface(surf_dst)) {
            ਵਾਪਸ false;
        }
    }

    x = dstrect->x;
    y = dstrect->y;
    dstbuf = (Uint8 *)surf_dst->pixels + y * surf_dst->pitch + x * df->ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel;
    srcbuf = (Uint8 *)surf_src->map.ਅੰਕੜੇ + ਆਕਾਰ(SDL_PixelFormat);

    {
        // skip lines at the top if necessary
        ਪੂਰਨ vskip = srcrect->y;
        ਜੇ (vskip) {
            ਪੂਰਨ ofs;
            ਜੇ (df->ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel == 2) {
                // the 16/32 interleaved format
                ਕਰੋ {
                    // skip opaque line
                    ofs = 0;
                    ਕਰੋ {
                        ਪੂਰਨ ਲੜੀਵਾਰ;
                        ofs += srcbuf[0];
                        ਲੜੀਵਾਰ = srcbuf[1];
                        srcbuf += 2;
                        ਜੇ (ਲੜੀਵਾਰ) {
                            srcbuf += 2 * ਲੜੀਵਾਰ;
                            ofs += ਲੜੀਵਾਰ;
                        } ਨਹੀਂਤਾਂ ਜੇ (ofs == 0) {
                            ਜਾਓ ਪੂਰਾ;
                        }
                    } ਜਦੋਂ (ofs < w);

                    // skip padding
                    srcbuf += (uintptr_t)srcbuf & 2;

                    // skip translucent line
                    ofs = 0;
                    ਕਰੋ {
                        ਪੂਰਨ ਲੜੀਵਾਰ;
                        ofs += ((Uint16 *)srcbuf)[0];
                        ਲੜੀਵਾਰ = ((Uint16 *)srcbuf)[1];
                        srcbuf += 4 * (ਲੜੀਵਾਰ + 1);
                        ofs += ਲੜੀਵਾਰ;
                    } ਜਦੋਂ (ofs < w);
                } ਜਦੋਂ (--vskip);
            } ਨਹੀਂਤਾਂ {
                // the 32/32 interleaved format
                vskip <<= 1; // opaque and translucent have same format
                ਕਰੋ {
                    ofs = 0;
                    ਕਰੋ {
                        ਪੂਰਨ ਲੜੀਵਾਰ;
                        ofs += ((Uint16 *)srcbuf)[0];
                        ਲੜੀਵਾਰ = ((Uint16 *)srcbuf)[1];
                        srcbuf += 4;
                        ਜੇ (ਲੜੀਵਾਰ) {
                            srcbuf += 4 * ਲੜੀਵਾਰ;
                            ofs += ਲੜੀਵਾਰ;
                        } ਨਹੀਂਤਾਂ ਜੇ (ofs == 0) {
                            ਜਾਓ ਪੂਰਾ;
                        }
                    } ਜਦੋਂ (ofs < w);
                } ਜਦੋਂ (--vskip);
            }
        }
    }

    // if left or right edge clipping needed, call clip blit
    ਜੇ (srcrect->x || srcrect->w != surf_src->w) {
        RLEAlphaClipBlit(w, srcbuf, surf_dst, dstbuf, srcrect);
    } ਨਹੀਂਤਾਂ {

        /*
         * non-clipped blitter. Ptype is the destination pixel type,
         * Ctype the translucent count type, and do_blend the
         * macro to blend one pixel.
         */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RLEALPHABLIT(Ptype, Ctype, do_blend)                         \
    ਕਰੋ {                                                             \
        ਪੂਰਨ linecount = srcrect->h;                                  \
        ਕਰੋ {                                                         \
            ਪੂਰਨ ofs = 0;                                             \
            /* blit opaque pixels on one line */                     \
            ਕਰੋ {                                                     \
                ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੜੀਵਾਰ;                                        \
                ofs += ((Ctype *)srcbuf)[0];                         \
                ਲੜੀਵਾਰ = ((Ctype *)srcbuf)[1];                          \
                srcbuf += 2 * ਆਕਾਰ(Ctype);                         \
                ਜੇ (ਲੜੀਵਾਰ) {                                           \
                    PIXEL_COPY(dstbuf + ofs * ਆਕਾਰ(Ptype), srcbuf, \
                               ਲੜੀਵਾਰ, ਆਕਾਰ(Ptype));                  \
                    srcbuf += ਲੜੀਵਾਰ * ਆਕਾਰ(Ptype);                   \
                    ofs += ਲੜੀਵਾਰ;                                      \
                } ਨਹੀਂਤਾਂ ਜੇ (!ofs)                                     \
                    ਜਾਓ ਪੂਰਾ;                                       \
            } ਜਦੋਂ (ofs < w);                                       \
            /* skip padding if necessary */                          \
            ਅਚਲ size_t psize = ਆਕਾਰ(Ptype);                      \
            ਜੇ (psize == 2)                                          \
                srcbuf += (uintptr_t)srcbuf & 2;                     \
            /* blit translucent pixels on the same line */           \
            ofs = 0;                                                 \
            ਕਰੋ {                                                     \
                ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੜੀਵਾਰ;                                        \
                ofs += ((Uint16 *)srcbuf)[0];                        \
                ਲੜੀਵਾਰ = ((Uint16 *)srcbuf)[1];                         \
                srcbuf += 4;                                         \
                ਜੇ (ਲੜੀਵਾਰ) {                                           \
                    Ptype *dst = (Ptype *)dstbuf + ofs;              \
                    ਬਿਨਾਨਿਸ਼ਾਨੀ i;                                      \
                    ਲਈ (i = 0; i < ਲੜੀਵਾਰ; i++) {                      \
                        Uint32 src = *(Uint32 *)srcbuf;              \
                        do_blend(src, *dst);                         \
                        srcbuf += 4;                                 \
                        dst++;                                       \
                    }                                                \
                    ofs += ਲੜੀਵਾਰ;                                      \
                }                                                    \
            } ਜਦੋਂ (ofs < w);                                       \
            dstbuf += surf_dst->pitch;                               \
        } ਜਦੋਂ (--linecount);                                       \
    } ਜਦੋਂ (0)

        ਚੋਣ (df->ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel) {
        ਹਾਲਤ 2:
            ਜੇ (df->Gmask == 0x07e0 || df->Rmask == 0x07e0 || df->Bmask == 0x07e0) {
                RLEALPHABLIT(Uint16, Uint8, BLIT_TRANSL_565);
            } ਨਹੀਂਤਾਂ {
                RLEALPHABLIT(Uint16, Uint8, BLIT_TRANSL_555);
            }
            ਰੋਕੋ;
        ਹਾਲਤ 4:
            RLEALPHABLIT(Uint32, Uint16, BLIT_TRANSL_888);
            ਰੋਕੋ;
        }
    }

ਪੂਰਾ:
    // Unlock the destination if necessary
    ਜੇ (SDL_MUSTLOCK(surf_dst)) {
        SDL_UnlockSurface(surf_dst);
    }
    ਵਾਪਸ true;
}

/*
 * Auxiliary functions:
 * The encoding functions take 32bpp rgb + a, and
 * return the number of bytes copied to the destination.
 * The decoding functions copy to 32bpp rgb + a, and
 * return the number of bytes copied from the source.
 * These are only used in the encoder and un-RLE code and are therefore not
 * highly optimised.
 */

// encode 32bpp rgb + a into 16bpp rgb, losing alpha
ਸਥਿਰ ਪੂਰਨ copy_opaque_16(ਖਾਲੀ *dst, ਅਚਲ Uint32 *src, ਪੂਰਨ n,
                          ਅਚਲ SDL_PixelFormatDetails *sfmt, ਅਚਲ SDL_PixelFormatDetails *dfmt)
{
    ਪੂਰਨ i;
    Uint16 *d = (Uint16 *)dst;
    ਲਈ (i = 0; i < n; i++) {
        ਬਿਨਾਨਿਸ਼ਾਨੀ r, g, b;
        RGB_FROM_PIXEL(*src, sfmt, r, g, b);
        PIXEL_FROM_RGB(*d, dfmt, r, g, b);
        src++;
        d++;
    }
    ਵਾਪਸ n * 2;
}

// encode 32bpp rgb + a into 32bpp G0RAB format for blitting into 565
ਸਥਿਰ ਪੂਰਨ copy_transl_565(ਖਾਲੀ *dst, ਅਚਲ Uint32 *src, ਪੂਰਨ n,
                           ਅਚਲ SDL_PixelFormatDetails *sfmt, ਅਚਲ SDL_PixelFormatDetails *dfmt)
{
    ਪੂਰਨ i;
    Uint32 *d = (Uint32 *)dst;
    ਲਈ (i = 0; i < n; i++) {
        ਬਿਨਾਨਿਸ਼ਾਨੀ r, g, b, a;
        Uint16 pix;
        RGBA_FROM_8888(*src, sfmt, r, g, b, a);
        PIXEL_FROM_RGB(pix, dfmt, r, g, b);
        *d = ((pix & 0x7e0) << 16) | (pix & 0xf81f) | ((a << 2) & 0x7e0);
        src++;
        d++;
    }
    ਵਾਪਸ n * 4;
}

// encode 32bpp rgb + a into 32bpp G0RAB format for blitting into 555
ਸਥਿਰ ਪੂਰਨ copy_transl_555(ਖਾਲੀ *dst, ਅਚਲ Uint32 *src, ਪੂਰਨ n,
                           ਅਚਲ SDL_PixelFormatDetails *sfmt, ਅਚਲ SDL_PixelFormatDetails *dfmt)
{
    ਪੂਰਨ i;
    Uint32 *d = (Uint32 *)dst;
    ਲਈ (i = 0; i < n; i++) {
        ਬਿਨਾਨਿਸ਼ਾਨੀ r, g, b, a;
        Uint16 pix;
        RGBA_FROM_8888(*src, sfmt, r, g, b, a);
        PIXEL_FROM_RGB(pix, dfmt, r, g, b);
        *d = ((pix & 0x3e0) << 16) | (pix & 0xfc1f) | ((a << 2) & 0x3e0);
        src++;
        d++;
    }
    ਵਾਪਸ n * 4;
}

// encode 32bpp rgba into 32bpp rgba, keeping alpha (dual purpose)
ਸਥਿਰ ਪੂਰਨ copy_32(ਖਾਲੀ *dst, ਅਚਲ Uint32 *src, ਪੂਰਨ n,
                   ਅਚਲ SDL_PixelFormatDetails *sfmt, ਅਚਲ SDL_PixelFormatDetails *dfmt)
{
    ਪੂਰਨ i;
    Uint32 *d = (Uint32 *)dst;
    ਲਈ (i = 0; i < n; i++) {
        ਬਿਨਾਨਿਸ਼ਾਨੀ r, g, b, a;
        RGBA_FROM_8888(*src, sfmt, r, g, b, a);
        RLEPIXEL_FROM_RGBA(*d, dfmt, r, g, b, a);
        d++;
        src++;
    }
    ਵਾਪਸ n * 4;
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ISOPAQUE(pixel, fmt) ((((pixel)&fmt->Amask) >> fmt->Ashift) == 255)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ISTRANSL(pixel, fmt) \
    ((ਬਿਨਾਨਿਸ਼ਾਨੀ)((((pixel)&fmt->Amask) >> fmt->Ashift) - 1U) < 254U)

// convert surface to be quickly alpha-blittable onto dest, if possible
ਸਥਿਰ bool RLEAlphaSurface(SDL_Surface *surface)
{
    SDL_Surface *dest;
    ਅਚਲ SDL_PixelFormatDetails *df;
    ਪੂਰਨ maxsize = 0;
    ਪੂਰਨ max_opaque_ਲੜੀਵਾਰ;
    ਪੂਰਨ max_transl_ਲੜੀਵਾਰ = 65535;
    ਬਿਨਾਨਿਸ਼ਾਨੀ masksum;
    Uint8 *rlebuf, *dst;
    ਪੂਰਨ (*copy_opaque)(ਖਾਲੀ *, ਅਚਲ Uint32 *, ਪੂਰਨ,
                       ਅਚਲ SDL_PixelFormatDetails *, ਅਚਲ SDL_PixelFormatDetails *);
    ਪੂਰਨ (*copy_transl)(ਖਾਲੀ *, ਅਚਲ Uint32 *, ਪੂਰਨ,
                       ਅਚਲ SDL_PixelFormatDetails *, ਅਚਲ SDL_PixelFormatDetails *);

    dest = surface->map.info.dst_surface;
    ਜੇ (!dest) {
        ਵਾਪਸ false;
    }
    df = dest->fmt;
    ਜੇ (surface->fmt->ਬਿੱਟ_ਪ੍ਰਤੀ_pixel != 32) {
        ਵਾਪਸ false; // only 32bpp source supported
    }

    /* find out whether the destination is one we support,
       and determine the max size of the encoded result */
    masksum = df->Rmask | df->Gmask | df->Bmask;
    ਚੋਣ (df->ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel) {
    ਹਾਲਤ 2:
        // 16bpp: only support 565 and 555 formats
        ਚੋਣ (masksum) {
        ਹਾਲਤ 0xffff:
            ਜੇ (df->Gmask == 0x07e0 || df->Rmask == 0x07e0 || df->Bmask == 0x07e0) {
                copy_opaque = copy_opaque_16;
                copy_transl = copy_transl_565;
            } ਨਹੀਂਤਾਂ {
                ਵਾਪਸ false;
            }
            ਰੋਕੋ;
        ਹਾਲਤ 0x7fff:
            ਜੇ (df->Gmask == 0x03e0 || df->Rmask == 0x03e0 || df->Bmask == 0x03e0) {
                copy_opaque = copy_opaque_16;
                copy_transl = copy_transl_555;
            } ਨਹੀਂਤਾਂ {
                ਵਾਪਸ false;
            }
            ਰੋਕੋ;
        ਮੂਲ:
            ਵਾਪਸ false;
        }
        max_opaque_ਲੜੀਵਾਰ = 255; // runs stored as bytes

        /* worst case is alternating opaque and translucent pixels,
           with room for alignment padding between lines */
        maxsize = surface->h * (2 + (4 + 2) * (surface->w + 1)) + 2;
        ਰੋਕੋ;
    ਹਾਲਤ 4:
        ਜੇ (masksum != 0x00ffffff) {
            ਵਾਪਸ false; // requires unused high byte
        }
        copy_opaque = copy_32;
        copy_transl = copy_32;
        max_opaque_ਲੜੀਵਾਰ = 255; // runs stored as short ints

        // worst case is alternating opaque and translucent pixels
        maxsize = surface->h * 2 * 4 * (surface->w + 1) + 4;
        ਰੋਕੋ;
    ਮੂਲ:
        ਵਾਪਸ false; // anything else unsupported right now
    }

    maxsize += ਆਕਾਰ(SDL_PixelFormat);
    rlebuf = (Uint8 *)SDL_malloc(maxsize);
    ਜੇ (!rlebuf) {
        ਵਾਪਸ false;
    }
    // save the destination format so we can undo the encoding later
    *(SDL_PixelFormat *)rlebuf = dest->format;
    dst = rlebuf + ਆਕਾਰ(SDL_PixelFormat);

    // Do the actual encoding
    {
        ਪੂਰਨ x, y;
        ਪੂਰਨ h = surface->h, w = surface->w;
        ਅਚਲ SDL_PixelFormatDetails *sf = surface->fmt;
        Uint32 *src = (Uint32 *)surface->pixels;
        Uint8 *lastline = dst; // end of last non-blank line

        // opaque counts are 8 or 16 bits, depending on target depth
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਜੋੜੋ_OPAQUE_COUNTS(n, m)           \
    ਜੇ (df->ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel == 4) {         \
        ((Uint16 *)dst)[0] = (Uint16)n;   \
        ((Uint16 *)dst)[1] = (Uint16)m;   \
        dst += 4;                         \
    } ਨਹੀਂਤਾਂ {                              \
        dst[0] = (Uint8)n;                \
        dst[1] = (Uint8)m;                \
        dst += 2;                         \
    }

        // translucent counts are always 16 bit
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਜੋੜੋ_TRANSL_COUNTS(n, m) \
    (((Uint16 *)dst)[0] = (Uint16)n, ((Uint16 *)dst)[1] = (Uint16)m, dst += 4)

        ਲਈ (y = 0; y < h; y++) {
            ਪੂਰਨ runstart, skipstart;
            ਪੂਰਨ blankline = 0;
            // First encode all opaque pixels of a scan line
            x = 0;
            ਕਰੋ {
                ਪੂਰਨ ਲੜੀਵਾਰ, skip, len;
                skipstart = x;
                ਜਦੋਂ (x < w && !ISOPAQUE(src[x], sf)) {
                    x++;
                }
                runstart = x;
                ਜਦੋਂ (x < w && ISOPAQUE(src[x], sf)) {
                    x++;
                }
                skip = runstart - skipstart;
                ਜੇ (skip == w) {
                    blankline = 1;
                }
                ਲੜੀਵਾਰ = x - runstart;
                ਜਦੋਂ (skip > max_opaque_ਲੜੀਵਾਰ) {
                    ਜੋੜੋ_OPAQUE_COUNTS(max_opaque_ਲੜੀਵਾਰ, 0);
                    skip -= max_opaque_ਲੜੀਵਾਰ;
                }
                len = SDL_min(ਲੜੀਵਾਰ, max_opaque_ਲੜੀਵਾਰ);
                ਜੋੜੋ_OPAQUE_COUNTS(skip, len);
                dst += copy_opaque(dst, src + runstart, len, sf, df);
                runstart += len;
                ਲੜੀਵਾਰ -= len;
                ਜਦੋਂ (ਲੜੀਵਾਰ) {
                    len = SDL_min(ਲੜੀਵਾਰ, max_opaque_ਲੜੀਵਾਰ);
                    ਜੋੜੋ_OPAQUE_COUNTS(0, len);
                    dst += copy_opaque(dst, src + runstart, len, sf, df);
                    runstart += len;
                    ਲੜੀਵਾਰ -= len;
                }
            } ਜਦੋਂ (x < w);

            // Make sure the next output address is 32-bit aligned
            dst += (uintptr_t)dst & 2;

            // Next, encode all translucent pixels of the same scan line
            x = 0;
            ਕਰੋ {
                ਪੂਰਨ ਲੜੀਵਾਰ, skip, len;
                skipstart = x;
                ਜਦੋਂ (x < w && !ISTRANSL(src[x], sf)) {
                    x++;
                }
                runstart = x;
                ਜਦੋਂ (x < w && ISTRANSL(src[x], sf)) {
                    x++;
                }
                skip = runstart - skipstart;
                blankline &= (skip == w);
                ਲੜੀਵਾਰ = x - runstart;
                ਜਦੋਂ (skip > max_transl_ਲੜੀਵਾਰ) {
                    ਜੋੜੋ_TRANSL_COUNTS(max_transl_ਲੜੀਵਾਰ, 0);
                    skip -= max_transl_ਲੜੀਵਾਰ;
                }
                len = SDL_min(ਲੜੀਵਾਰ, max_transl_ਲੜੀਵਾਰ);
                ਜੋੜੋ_TRANSL_COUNTS(skip, len);
                dst += copy_transl(dst, src + runstart, len, sf, df);
                runstart += len;
                ਲੜੀਵਾਰ -= len;
                ਜਦੋਂ (ਲੜੀਵਾਰ) {
                    len = SDL_min(ਲੜੀਵਾਰ, max_transl_ਲੜੀਵਾਰ);
                    ਜੋੜੋ_TRANSL_COUNTS(0, len);
                    dst += copy_transl(dst, src + runstart, len, sf, df);
                    runstart += len;
                    ਲੜੀਵਾਰ -= len;
                }
                ਜੇ (!blankline) {
                    lastline = dst;
                }
            } ਜਦੋਂ (x < w);

            src += surface->pitch >> 2;
        }
        dst = lastline; // back up past trailing blank lines
        ਜੋੜੋ_OPAQUE_COUNTS(0, 0);
    }

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ ਜੋੜੋ_OPAQUE_COUNTS
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ ਜੋੜੋ_TRANSL_COUNTS

    // reallocate the buffer to release unused memory
    {
        Uint8 *p = (Uint8 *)SDL_realloc(rlebuf, dst - rlebuf);
        ਜੇ (!p) {
            p = rlebuf;
        }
        surface->map.ਅੰਕੜੇ = p;
    }

    ਵਾਪਸ true;
}

ਸਥਿਰ Uint32 getpix_8(ਅਚਲ Uint8 *srcbuf)
{
    ਵਾਪਸ *srcbuf;
}

ਸਥਿਰ Uint32 getpix_16(ਅਚਲ Uint8 *srcbuf)
{
    ਵਾਪਸ *(ਅਚਲ Uint16 *)srcbuf;
}

ਸਥਿਰ Uint32 getpix_24(ਅਚਲ Uint8 *srcbuf)
{
#ਜੇ SDL_BYTEORDER == SDL_LIL_ENDIAN
    ਵਾਪਸ srcbuf[0] + (srcbuf[1] << 8) + (srcbuf[2] << 16);
#ਨਹੀਂਤਾਂ
    ਵਾਪਸ (srcbuf[0] << 16) + (srcbuf[1] << 8) + srcbuf[2];
#ਜੇ_ਅੰਤ
}

ਸਥਿਰ Uint32 getpix_32(ਅਚਲ Uint8 *srcbuf)
{
    ਵਾਪਸ *(ਅਚਲ Uint32 *)srcbuf;
}

ਕਿਸਮਪਰਿਭਾਸ਼ਾ Uint32 (*getpix_func)(ਅਚਲ Uint8 *);

ਸਥਿਰ ਅਚਲ getpix_func getpixes[4] = {
    getpix_8, getpix_16, getpix_24, getpix_32
};

ਸਥਿਰ bool RLEColorkeySurface(SDL_Surface *surface)
{
    SDL_Surface *dest;
    Uint8 *rlebuf, *dst;
    ਪੂਰਨ maxn;
    ਪੂਰਨ y;
    Uint8 *srcbuf, *lastline;
    ਪੂਰਨ maxsize = 0;
    ਅਚਲ ਪੂਰਨ bpp = surface->fmt->ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel;
    getpix_func getpix;
    Uint32 ckey, rgbmask;
    ਪੂਰਨ w, h;

    dest = surface->map.info.dst_surface;
    ਜੇ (!dest) {
        ਵਾਪਸ false;
    }

    // calculate the worst case size for the compressed surface
    ਚੋਣ (bpp) {
    ਹਾਲਤ 1:
        /* worst case is alternating opaque and transparent pixels,
           starting with an opaque pixel */
        maxsize = surface->h * 3 * (surface->w / 2 + 1) + 2;
        ਰੋਕੋ;
    ਹਾਲਤ 2:
    ਹਾਲਤ 3:
        // worst case is solid runs, at most 255 pixels wide
        maxsize = surface->h * (2 * (surface->w / 255 + 1) + surface->w * bpp) + 2;
        ਰੋਕੋ;
    ਹਾਲਤ 4:
        // worst case is solid runs, at most 65535 pixels wide
        maxsize = surface->h * (4 * (surface->w / 65535 + 1) + surface->w * 4) + 4;
        ਰੋਕੋ;

    ਮੂਲ:
        ਵਾਪਸ false;
    }

    maxsize += ਆਕਾਰ(SDL_PixelFormat);
    rlebuf = (Uint8 *)SDL_malloc(maxsize);
    ਜੇ (!rlebuf) {
        ਵਾਪਸ false;
    }
    // save the destination format so we can undo the encoding later
    *(SDL_PixelFormat *)rlebuf = dest->format;

    // Set up the conversion
    srcbuf = (Uint8 *)surface->pixels;
    maxn = bpp == 4 ? 65535 : 255;
    dst = rlebuf + ਆਕਾਰ(SDL_PixelFormat);
    rgbmask = ~surface->fmt->Amask;
    ckey = surface->map.info.colorkey & rgbmask;
    lastline = dst;
    getpix = getpixes[bpp - 1];
    w = surface->w;
    h = surface->h;

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਜੋੜੋ_COUNTS(n, m)                \
    ਜੇ (bpp == 4) {                     \
        ((Uint16 *)dst)[0] = (Uint16)n; \
        ((Uint16 *)dst)[1] = (Uint16)m; \
        dst += 4;                       \
    } ਨਹੀਂਤਾਂ {                            \
        dst[0] = (Uint8)n;              \
        dst[1] = (Uint8)m;              \
        dst += 2;                       \
    }

    ਲਈ (y = 0; y < h; y++) {
        ਪੂਰਨ x = 0;
        ਪੂਰਨ blankline = 0;
        ਕਰੋ {
            ਪੂਰਨ ਲੜੀਵਾਰ, skip;
            ਪੂਰਨ len;
            ਪੂਰਨ runstart;
            ਪੂਰਨ skipstart = x;

            // find run of transparent, then opaque pixels
            ਜਦੋਂ (x < w && (getpix(srcbuf + x * bpp) & rgbmask) == ckey) {
                x++;
            }
            runstart = x;
            ਜਦੋਂ (x < w && (getpix(srcbuf + x * bpp) & rgbmask) != ckey) {
                x++;
            }
            skip = runstart - skipstart;
            ਜੇ (skip == w) {
                blankline = 1;
            }
            ਲੜੀਵਾਰ = x - runstart;

            // encode segment
            ਜਦੋਂ (skip > maxn) {
                ਜੋੜੋ_COUNTS(maxn, 0);
                skip -= maxn;
            }
            len = SDL_min(ਲੜੀਵਾਰ, maxn);
            ਜੋੜੋ_COUNTS(skip, len);
            SDL_memcpy(dst, srcbuf + runstart * bpp, (size_t)len * bpp);
            dst += len * bpp;
            ਲੜੀਵਾਰ -= len;
            runstart += len;
            ਜਦੋਂ (ਲੜੀਵਾਰ) {
                len = SDL_min(ਲੜੀਵਾਰ, maxn);
                ਜੋੜੋ_COUNTS(0, len);
                SDL_memcpy(dst, srcbuf + runstart * bpp, (size_t)len * bpp);
                dst += len * bpp;
                runstart += len;
                ਲੜੀਵਾਰ -= len;
            }
            ਜੇ (!blankline) {
                lastline = dst;
            }
        } ਜਦੋਂ (x < w);

        srcbuf += surface->pitch;
    }
    dst = lastline; // back up bast trailing blank lines
    ਜੋੜੋ_COUNTS(0, 0);

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ ਜੋੜੋ_COUNTS

    // reallocate the buffer to release unused memory
    {
        // If SDL_realloc returns NULL, the original block is left intact
        Uint8 *p = (Uint8 *)SDL_realloc(rlebuf, dst - rlebuf);
        ਜੇ (!p) {
            p = rlebuf;
        }
        surface->map.ਅੰਕੜੇ = p;
    }

    ਵਾਪਸ true;
}

bool SDL_RLESurface(SDL_Surface *surface)
{
    ਪੂਰਨ flags;

    // Clear any previous RLE conversion
    ਜੇ (surface->ਅੰਦਰੂਨੀ_flags & SDL_ਅੰਦਰੂਨੀ_SURFACE_RLEACCEL) {
        SDL_UnRLESurface(surface);
    }

    // We don't support RLE encoding of bitmaps
    ਜੇ (SDL_BITSPERPIXEL(surface->format) < 8) {
        ਵਾਪਸ false;
    }

    // Make sure the pixels are available
    ਜੇ (!surface->pixels) {
        ਵਾਪਸ false;
    }

    flags = surface->map.info.flags;
    ਜੇ (flags & SDL_COPY_COLORKEY) {
        // ok
    } ਨਹੀਂਤਾਂ ਜੇ ((flags & SDL_COPY_BLEND) && SDL_ISPIXELFORMAT_ALPHA(surface->format)) {
        // ok
    } ਨਹੀਂਤਾਂ {
        // If we don't have colorkey or blending, nothing to do...
        ਵਾਪਸ false;
    }

    // Pass on combinations not supported
    ਜੇ ((flags & SDL_COPY_MODULATE_COLOR) ||
        ((flags & SDL_COPY_MODULATE_ALPHA) && SDL_ISPIXELFORMAT_ALPHA(surface->format)) ||
        (flags & (SDL_COPY_BLEND_PREMULTIPLIED | SDL_COPY_ਜੋੜੋ | SDL_COPY_ਜੋੜੋ_PREMULTIPLIED | SDL_COPY_MOD | SDL_COPY_MUL)) ||
        (flags & SDL_COPY_ਸਭ_ਤੋਂ_ਨੇੜੇ)) {
        ਵਾਪਸ false;
    }

    // Encode and set up the blit
    ਜੇ (!SDL_ISPIXELFORMAT_ALPHA(surface->format) || !(flags & SDL_COPY_BLEND)) {
        ਜੇ (!surface->map.ਪਛਾਣ_ਤੱਤ) {
            ਵਾਪਸ false;
        }
        ਜੇ (!RLEColorkeySurface(surface)) {
            ਵਾਪਸ false;
        }
        surface->map.blit = SDL_RLEBlit;
        surface->map.info.flags |= SDL_COPY_RLE_COLORKEY;
    } ਨਹੀਂਤਾਂ {
        ਜੇ (!RLEAlphaSurface(surface)) {
            ਵਾਪਸ false;
        }
        surface->map.blit = SDL_RLEAlphaBlit;
        surface->map.info.flags |= SDL_COPY_RLE_ALPHAKEY;
    }

    ਜੇ (!(surface->flags & SDL_SURFACE_PREALLOCATED)) {
        surface->saved_pixels = surface->pixels;
        surface->pixels = ਨਿਰਾ;
    }

    // The surface is now accelerated
    surface->ਅੰਦਰੂਨੀ_flags |= SDL_ਅੰਦਰੂਨੀ_SURFACE_RLEACCEL;
    SDL_Update_Surface_ਤਾਲਾ_Flag(surface);

    ਵਾਪਸ true;
}

ਖਾਲੀ SDL_UnRLESurface(SDL_Surface *surface)
{
    ਜੇ (surface->ਅੰਦਰੂਨੀ_flags & SDL_ਅੰਦਰੂਨੀ_SURFACE_RLEACCEL) {
        surface->ਅੰਦਰੂਨੀ_flags &= ~SDL_ਅੰਦਰੂਨੀ_SURFACE_RLEACCEL;

        surface->map.info.flags &= ~(SDL_COPY_RLE_COLORKEY | SDL_COPY_RLE_ALPHAKEY);

        ਜੇ (!(surface->flags & SDL_SURFACE_PREALLOCATED)) {
            surface->pixels = surface->saved_pixels;
            surface->saved_pixels = ਨਿਰਾ;
        }

        SDL_free(surface->map.ਅੰਕੜੇ);
        surface->map.ਅੰਕੜੇ = ਨਿਰਾ;

        SDL_InvalidateMap(&surface->map);

        SDL_Update_Surface_ਤਾਲਾ_Flag(surface);
    }
}

#ਜੇ_ਅੰਤ // SDL_HAVE_RLE
