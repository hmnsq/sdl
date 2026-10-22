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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_HAVE_RLE

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

#ಅನ್ತರ್ಭಾವ "SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_surface_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_pixels_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_RLEaccel_c.h"

#ವ್ಯಾಖ್ಯಾನಿಸು PIXEL_COPY(ಗಮ್ಯ, from, len, bpp) \
    SDL_memcpy(ಗಮ್ಯ, from, (size_t)(len) * (bpp))

/*
 * Various colorkey blit methods, for opaque and per-surface alpha
 */

#ವ್ಯಾಖ್ಯಾನಿಸು OPAQUE_BLIT(ಗಮ್ಯ, from, ಉದ್ದಳತೆ, bpp, alpha) \
    PIXEL_COPY(ಗಮ್ಯ, from, ಉದ್ದಳತೆ, bpp)

/*
 * For 32bpp pixels on the form 0x00rrggbb:
 * If we treat the middle component separately, we can process the two
 * remaining in parallel. This is safe to do because of the gap to the left
 * of each component, so the bits from the multiplication don't collide.
 * This can be used for any RGB permutation of course.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ALPHA_BLIT32_888(ಗಮ್ಯ, from, ಉದ್ದಳತೆ, bpp, alpha)       \
    ಮಾಡು {                                                     \
        ಪೂರ್ಣಾಂಕ i;                                               \
        Uint32 *src = (Uint32 *)(from);                      \
        Uint32 *dst = (Uint32 *)(ಗಮ್ಯ);                        \
        ಗಾಗಿ (i = 0; i < (ಪೂರ್ಣಾಂಕ)(ಉದ್ದಳತೆ); i++) {                \
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
    } ಆಗ (0)

/*
 * For 16bpp pixels we can go a step further: put the middle component
 * in the high 16 bits of a 32 bit word, and process all three RGB
 * components at the same time. Since the smallest gap is here just
 * 5 bits, we have to scale alpha down to 5 bits as well.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ALPHA_BLIT16_565(ಗಮ್ಯ, from, ಉದ್ದಳತೆ, bpp, alpha) \
    ಮಾಡು {                                               \
        ಪೂರ್ಣಾಂಕ i;                                         \
        Uint16 *src = (Uint16 *)(from);                \
        Uint16 *dst = (Uint16 *)(ಗಮ್ಯ);                  \
        Uint32 ALPHA = alpha >> 3;                     \
        ಗಾಗಿ (i = 0; i < (ಪೂರ್ಣಾಂಕ)(ಉದ್ದಳತೆ); i++) {          \
            Uint32 s = *src++;                         \
            Uint32 d = *dst;                           \
            s = (s | s << 16) & 0x07e0f81f;            \
            d = (d | d << 16) & 0x07e0f81f;            \
            d += (s - d) * ALPHA >> 5;                 \
            d &= 0x07e0f81f;                           \
            *dst++ = (Uint16)(d | d >> 16);            \
        }                                              \
    } ಆಗ (0)

#ವ್ಯಾಖ್ಯಾನಿಸು ALPHA_BLIT16_555(ಗಮ್ಯ, from, ಉದ್ದಳತೆ, bpp, alpha) \
    ಮಾಡು {                                               \
        ಪೂರ್ಣಾಂಕ i;                                         \
        Uint16 *src = (Uint16 *)(from);                \
        Uint16 *dst = (Uint16 *)(ಗಮ್ಯ);                  \
        Uint32 ALPHA = alpha >> 3;                     \
        ಗಾಗಿ (i = 0; i < (ಪೂರ್ಣಾಂಕ)(ಉದ್ದಳತೆ); i++) {          \
            Uint32 s = *src++;                         \
            Uint32 d = *dst;                           \
            s = (s | s << 16) & 0x03e07c1f;            \
            d = (d | d << 16) & 0x03e07c1f;            \
            d += (s - d) * ALPHA >> 5;                 \
            d &= 0x03e07c1f;                           \
            *dst++ = (Uint16)(d | d >> 16);            \
        }                                              \
    } ಆಗ (0)

/*
 * The general slow catch-all function, for remaining depths and formats
 */
#ಆದರೆ SDL_BYTEORDER == SDL_BIG_ENDIAN
#ವ್ಯಾಖ್ಯಾನಿಸು ಗಣ_RGB24(dst, d)      \
    dst[0] = (Uint8)(d >> 16); \
    dst[1] = (Uint8)(d >> 8);  \
    dst[2] = (Uint8)(d);
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು ಗಣ_RGB24(dst, d)      \
    dst[0] = (Uint8)(d);       \
    dst[1] = (Uint8)(d >> 8);  \
    dst[2] = (Uint8)(d >> 16);
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿಸು ALPHA_BLIT_ANY(ಗಮ್ಯ, from, ಉದ್ದಳತೆ, bpp, alpha)             \
    ಮಾಡು {                                                         \
        ಪೂರ್ಣಾಂಕ i;                                                   \
        Uint8 *src = from;                                       \
        Uint8 *dst = ಗಮ್ಯ;                                         \
        ಗಾಗಿ (i = 0; i < (ಪೂರ್ಣಾಂಕ)(ಉದ್ದಳತೆ); i++) {                    \
            Uint32 s = 0, d = 0;                                 \
            ಚಿಹ್ನೆರಹಿತ rs, gs, bs, rd, gd, bd;                     \
            ಆಯ್ಕೆ (bpp) {                                       \
            ಸ್ಥಿತಿ 2:                                              \
                s = *(Uint16 *)src;                              \
                d = *(Uint16 *)dst;                              \
                ನಿಲ್ಲಿಸು;                                           \
            ಸ್ಥಿತಿ 3:                                              \
                s = GET_RGB24(src);                              \
                d = GET_RGB24(dst);                              \
                ನಿಲ್ಲಿಸು;                                           \
            ಸ್ಥಿತಿ 4:                                              \
                s = *(Uint32 *)src;                              \
                d = *(Uint32 *)dst;                              \
                ನಿಲ್ಲಿಸು;                                           \
            }                                                    \
            RGB_FROM_PIXEL(s, fmt, rs, gs, bs);                  \
            RGB_FROM_PIXEL(d, fmt, rd, gd, bd);                  \
            rd += (rs - rd) * alpha >> 8;                        \
            gd += (gs - gd) * alpha >> 8;                        \
            bd += (bs - bd) * alpha >> 8;                        \
            PIXEL_FROM_RGB(d, fmt, rd, gd, bd);                  \
            ಆಯ್ಕೆ (bpp) {                                       \
            ಸ್ಥಿತಿ 2:                                              \
                *(Uint16 *)dst = (Uint16)d;                      \
                ನಿಲ್ಲಿಸು;                                           \
            ಸ್ಥಿತಿ 3:                                              \
                ಗಣ_RGB24(dst, d);                               \
                ನಿಲ್ಲಿಸು;                                           \
            ಸ್ಥಿತಿ 4:                                              \
                *(Uint32 *)dst = d;                              \
                ನಿಲ್ಲಿಸು;                                           \
            }                                                    \
            src += bpp;                                          \
            dst += bpp;                                          \
        }                                                        \
    } ಆಗ (0)

/*
 * Special case: 50% alpha (alpha=128)
 * This is treated specially because it can be optimized very well, and
 * since it is good for many cases of semi-translucency.
 * The theory is to do all three components at the same time:
 * First zero the lowest bit of each component, which gives us room to
 * add them. Then shift right and add the sum of the lowest bits.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ALPHA_BLIT32_888_50(ಗಮ್ಯ, from, ಉದ್ದಳತೆ, bpp, alpha)                                 \
    ಮಾಡು {                                                                                  \
        ಪೂರ್ಣಾಂಕ i;                                                                            \
        Uint32 *src = (Uint32 *)(from);                                                   \
        Uint32 *dst = (Uint32 *)(ಗಮ್ಯ);                                                     \
        ಗಾಗಿ (i = 0; i < (ಪೂರ್ಣಾಂಕ)(ಉದ್ದಳತೆ); i++) {                                             \
            Uint32 s = *src++;                                                            \
            Uint32 d = *dst;                                                              \
            *dst++ = (((s & 0x00fefefe) + (d & 0x00fefefe)) >> 1) + (s & d & 0x00010101); \
        }                                                                                 \
    } ಆಗ (0)

/*
 * For 16bpp, we can actually blend two pixels in parallel, if we take
 * care to shift before we add, not after.
 */

// helper: blend a single 16 bit pixel at 50%
#ವ್ಯಾಖ್ಯಾನಿಸು BLEND16_50(dst, src, ಮುಖವಾಡ)                           \
    ಮಾಡು {                                                     \
        Uint32 s = *src++;                                   \
        Uint32 d = *dst;                                     \
        *dst++ = (Uint16)((((s & ಮುಖವಾಡ) + (d & ಮುಖವಾಡ)) >> 1) + \
                          (s & d & (~ಮುಖವಾಡ & 0xffff)));       \
    } ಆಗ (0)

// basic 16bpp blender. mask is the pixels to keep when adding.
#ವ್ಯಾಖ್ಯಾನಿಸು ALPHA_BLIT16_50(ಗಮ್ಯ, from, ಉದ್ದಳತೆ, bpp, alpha, ಮುಖವಾಡ)                                                                              \
    ಮಾಡು {                                                                                                                                 \
        ಚಿಹ್ನೆರಹಿತ n = (ಉದ್ದಳತೆ);                                                                                                           \
        Uint16 *src = (Uint16 *)(from);                                                                                                  \
        Uint16 *dst = (Uint16 *)(ಗಮ್ಯ);                                                                                                    \
        ಆದರೆ (((uintptr_t)src ^ (uintptr_t)dst) & 3) {                                                                                     \
            /* source and destination not in phase, blit one by one */                                                                   \
            ಆಗ (n--)                                                                                                                  \
                BLEND16_50(dst, src, ಮುಖವಾಡ);                                                                                              \
        } ಇಲ್ಲದಿದ್ದರೆ {                                                                                                                         \
            ಆದರೆ ((uintptr_t)src & 3) {                                                                                                    \
                /* first odd pixel */                                                                                                    \
                BLEND16_50(dst, src, ಮುಖವಾಡ);                                                                                              \
                n--;                                                                                                                     \
            }                                                                                                                            \
            ಗಾಗಿ (; n > 1; n -= 2) {                                                                                                      \
                Uint32 s = *(Uint32 *)src;                                                                                               \
                Uint32 d = *(Uint32 *)dst;                                                                                               \
                *(Uint32 *)dst = ((s & (ಮುಖವಾಡ | ಮುಖವಾಡ << 16)) >> 1) + ((d & (ಮುಖವಾಡ | ಮುಖವಾಡ << 16)) >> 1) + (s & d & (~(ಮುಖವಾಡ | ಮುಖವಾಡ << 16))); \
                src += 2;                                                                                                                \
                dst += 2;                                                                                                                \
            }                                                                                                                            \
            ಆದರೆ (n)                                                                                                                       \
                BLEND16_50(dst, src, ಮುಖವಾಡ); /* last odd pixel */                                                                         \
        }                                                                                                                                \
    } ಆಗ (0)

#ವ್ಯಾಖ್ಯಾನಿಸು ALPHA_BLIT16_565_50(ಗಮ್ಯ, from, ಉದ್ದಳತೆ, bpp, alpha) \
    ALPHA_BLIT16_50(ಗಮ್ಯ, from, ಉದ್ದಳತೆ, bpp, alpha, 0xf7deU)

#ವ್ಯಾಖ್ಯಾನಿಸು ALPHA_BLIT16_555_50(ಗಮ್ಯ, from, ಉದ್ದಳತೆ, bpp, alpha) \
    ALPHA_BLIT16_50(ಗಮ್ಯ, from, ಉದ್ದಳತೆ, bpp, alpha, 0xfbdeU)

#ವ್ಯಾಖ್ಯಾನಿಸು ಆರಿಸು_BLIT(blitter, alpha, fmt)                                                                                                              \
    ಮಾಡು {                                                                                                                                              \
        ಆದರೆ (alpha == 255) {                                                                                                                           \
            ಆಯ್ಕೆ (fmt->ಬೈಟುಗಳು_ಪ್ರತಿ_pixel) {                                                                                                             \
            ಸ್ಥಿತಿ 1:                                                                                                                                   \
                blitter(1, Uint8, OPAQUE_BLIT);                                                                                                       \
                ನಿಲ್ಲಿಸು;                                                                                                                                \
            ಸ್ಥಿತಿ 2:                                                                                                                                   \
                blitter(2, Uint8, OPAQUE_BLIT);                                                                                                       \
                ನಿಲ್ಲಿಸು;                                                                                                                                \
            ಸ್ಥಿತಿ 3:                                                                                                                                   \
                blitter(3, Uint8, OPAQUE_BLIT);                                                                                                       \
                ನಿಲ್ಲಿಸು;                                                                                                                                \
            ಸ್ಥಿತಿ 4:                                                                                                                                   \
                blitter(4, Uint16, OPAQUE_BLIT);                                                                                                      \
                ನಿಲ್ಲಿಸು;                                                                                                                                \
            }                                                                                                                                         \
        } ಇಲ್ಲದಿದ್ದರೆ {                                                                                                                                      \
            ಆಯ್ಕೆ (fmt->ಬೈಟುಗಳು_ಪ್ರತಿ_pixel) {                                                                                                             \
            ಸ್ಥಿತಿ 1:                                                                                                                                   \
                /* No 8bpp alpha blitting */                                                                                                          \
                ನಿಲ್ಲಿಸು;                                                                                                                                \
                                                                                                                                                      \
            ಸ್ಥಿತಿ 2:                                                                                                                                   \
                ಆಯ್ಕೆ (fmt->Rmask | fmt->Gmask | fmt->Bmask) {                                                                                       \
                ಸ್ಥಿತಿ 0xffff:                                                                                                                          \
                    ಆದರೆ (fmt->Gmask == 0x07e0 || fmt->Rmask == 0x07e0 || fmt->Bmask == 0x07e0) {                                                       \
                        ಆದರೆ (alpha == 128) {                                                                                                           \
                            blitter(2, Uint8, ALPHA_BLIT16_565_50);                                                                                   \
                        } ಇಲ್ಲದಿದ್ದರೆ {                                                                                                                      \
                            blitter(2, Uint8, ALPHA_BLIT16_565);                                                                                      \
                        }                                                                                                                             \
                    } ಇಲ್ಲದಿದ್ದರೆ {                                                                                                                          \
                        ಹೋಗು general16;                                                                                                               \
                    }                                                                                                                                 \
                    ನಿಲ್ಲಿಸು;                                                                                                                            \
                                                                                                                                                      \
                ಸ್ಥಿತಿ 0x7fff:                                                                                                                          \
                    ಆದರೆ (fmt->Gmask == 0x03e0 || fmt->Rmask == 0x03e0 || fmt->Bmask == 0x03e0) {                                                       \
                        ಆದರೆ (alpha == 128) {                                                                                                           \
                            blitter(2, Uint8, ALPHA_BLIT16_555_50);                                                                                   \
                        } ಇಲ್ಲದಿದ್ದರೆ {                                                                                                                      \
                            blitter(2, Uint8, ALPHA_BLIT16_555);                                                                                      \
                        }                                                                                                                             \
                        ನಿಲ್ಲಿಸು;                                                                                                                        \
                    } ಇಲ್ಲದಿದ್ದರೆ {                                                                                                                          \
                        ಹೋಗು general16;                                                                                                               \
                    }                                                                                                                                 \
                    ನಿಲ್ಲಿಸು;                                                                                                                            \
                                                                                                                                                      \
                ಪೂರ್ವನಿಯೋಜಿತ:                                                                                                                              \
                general16:                                                                                                                            \
                    blitter(2, Uint8, ALPHA_BLIT_ANY);                                                                                                \
                }                                                                                                                                     \
                ನಿಲ್ಲಿಸು;                                                                                                                                \
                                                                                                                                                      \
            ಸ್ಥಿತಿ 3:                                                                                                                                   \
                blitter(3, Uint8, ALPHA_BLIT_ANY);                                                                                                    \
                ನಿಲ್ಲಿಸು;                                                                                                                                \
                                                                                                                                                      \
            ಸ್ಥಿತಿ 4:                                                                                                                                   \
                ಆದರೆ ((fmt->Rmask | fmt->Gmask | fmt->Bmask) == 0x00ffffff && (fmt->Gmask == 0xff00 || fmt->Rmask == 0xff00 || fmt->Bmask == 0xff00)) { \
                    ಆದರೆ (alpha == 128) {                                                                                                               \
                        blitter(4, Uint16, ALPHA_BLIT32_888_50);                                                                                      \
                    } ಇಲ್ಲದಿದ್ದರೆ {                                                                                                                          \
                        blitter(4, Uint16, ALPHA_BLIT32_888);                                                                                         \
                    }                                                                                                                                 \
                } ಇಲ್ಲದಿದ್ದರೆ {                                                                                                                              \
                    blitter(4, Uint16, ALPHA_BLIT_ANY);                                                                                               \
                }                                                                                                                                     \
                ನಿಲ್ಲಿಸು;                                                                                                                                \
            }                                                                                                                                         \
        }                                                                                                                                             \
    } ಆಗ (0)

/*
 * Set a pixel value using the given format, except that the alpha value is
 * placed in the top byte. This is the format used for RLE with alpha.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು RLEPIXEL_FROM_RGBA(Pixel, fmt, r, g, b, a)   \
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
#ವ್ಯಾಖ್ಯಾನಿಸು RLECLIPBLIT(bpp, Type, do_blit)                                    \
    ಮಾಡು {                                                                   \
        ಪೂರ್ಣಾಂಕ linecount = srcrect->h;                                        \
        ಪೂರ್ಣಾಂಕ ofs = 0;                                                       \
        ಪೂರ್ಣಾಂಕ ಎಡ = srcrect->x;                                             \
        ಪೂರ್ಣಾಂಕ ಬಲ = ಎಡ + srcrect->w;                                     \
        dstbuf -= ಎಡ * bpp;                                              \
        ಗಾಗಿ (;;) {                                                         \
            ಪೂರ್ಣಾಂಕ ಸತತ;                                                       \
            ofs += *(Type *)srcbuf;                                        \
            ಸತತ = ((Type *)srcbuf)[1];                                     \
            srcbuf += 2 * ಗಾತ್ರ(Type);                                    \
            ಆದರೆ (ಸತತ) {                                                     \
                /* clip to left and right borders */                       \
                ಆದರೆ (ofs < ಬಲ) {                                         \
                    ಪೂರ್ಣಾಂಕ ಆರಂಭ = 0;                                         \
                    ಪೂರ್ಣಾಂಕ len = ಸತತ;                                         \
                    ಪೂರ್ಣಾಂಕ startcol;                                          \
                    ಆದರೆ (ಎಡ - ofs > 0) {                                  \
                        ಆರಂಭ = ಎಡ - ofs;                                \
                        len -= ಆರಂಭ;                                      \
                        ಆದರೆ (len <= 0)                                      \
                            ಹೋಗು nocopy##bpp##do_blit;                     \
                    }                                                      \
                    startcol = ofs + ಆರಂಭ;                                \
                    ಆದರೆ (len > ಬಲ - startcol)                            \
                        len = ಬಲ - startcol;                            \
                    do_blit(dstbuf + startcol * bpp, srcbuf + ಆರಂಭ * bpp, \
                            len, bpp, alpha);                              \
                }                                                          \
                nocopy##bpp##do_blit : srcbuf += ಸತತ * bpp;                \
                ofs += ಸತತ;                                                \
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!ofs) {                                             \
                ನಿಲ್ಲಿಸು;                                                     \
            }                                                              \
                                                                           \
            ಆದರೆ (ofs == w) {                                                \
                ofs = 0;                                                   \
                dstbuf += surf_dst->pitch;                                 \
                ಆದರೆ (!--linecount) {                                        \
                    ನಿಲ್ಲಿಸು;                                                 \
                }                                                          \
            }                                                              \
        }                                                                  \
    } ಆಗ (0)

ಸ್ಥಿರ ಶೂನ್ಯ RLEClipBlit(ಪೂರ್ಣಾಂಕ w, Uint8 *srcbuf, SDL_Surface *surf_dst,
                        Uint8 *dstbuf, ಸ್ಥಿರಾಂಕ SDL_Rect *srcrect, ಚಿಹ್ನೆರಹಿತ alpha)
{
    ಸ್ಥಿರಾಂಕ SDL_PixelFormatDetails *fmt = surf_dst->fmt;

    ಆರಿಸು_BLIT(RLECLIPBLIT, alpha, fmt);
}

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು RLECLIPBLIT

// blit a colorkeyed RLE surface
ಸ್ಥಿರ bool SDLCALL SDL_RLEBlit(SDL_Surface *surf_src, ಸ್ಥಿರಾಂಕ SDL_Rect *srcrect,
                                SDL_Surface *surf_dst, ಸ್ಥಿರಾಂಕ SDL_Rect *dstrect)
{
    Uint8 *dstbuf;
    Uint8 *srcbuf;
    ಪೂರ್ಣಾಂಕ x, y;
    ಪೂರ್ಣಾಂಕ w = surf_src->w;
    ಚಿಹ್ನೆರಹಿತ alpha;

    // Lock the destination if necessary
    ಆದರೆ (SDL_MUSTLOCK(surf_dst)) {
        ಆದರೆ (!SDL_ಬೀಗ_Surface(surf_dst)) {
            ಹಿಂತಿರುಗಿ false;
        }
    }

    // Set up the source and destination pointers
    x = dstrect->x;
    y = dstrect->y;
    dstbuf = (Uint8 *)surf_dst->pixels + y * surf_dst->pitch + x * surf_src->fmt->ಬೈಟುಗಳು_ಪ್ರತಿ_pixel;
    srcbuf = (Uint8 *)surf_src->map.ದತ್ತಾಂಶ + ಗಾತ್ರ(SDL_PixelFormat);

    {
        // skip lines at the top if necessary
        ಪೂರ್ಣಾಂಕ vskip = srcrect->y;
        ಪೂರ್ಣಾಂಕ ofs = 0;
        ಆದರೆ (vskip) {

#ವ್ಯಾಖ್ಯಾನಿಸು RLESKIP(bpp, Type)          \
    ಗಾಗಿ (;;) {                      \
        ಪೂರ್ಣಾಂಕ ಸತತ;                    \
        ofs += *(Type *)srcbuf;     \
        ಸತತ = ((Type *)srcbuf)[1];  \
        srcbuf += ಗಾತ್ರ(Type) * 2; \
        ಆದರೆ (ಸತತ) {                  \
            srcbuf += ಸತತ * bpp;    \
            ofs += ಸತತ;             \
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!ofs)            \
            ಹೋಗು ಮುಗಿದ;              \
        ಆದರೆ (ofs == w) {             \
            ofs = 0;                \
            ಆದರೆ (!--vskip)           \
                ನಿಲ್ಲಿಸು;              \
        }                           \
    }

            ಆಯ್ಕೆ (surf_src->fmt->ಬೈಟುಗಳು_ಪ್ರತಿ_pixel) {
            ಸ್ಥಿತಿ 1:
                RLESKIP(1, Uint8);
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ 2:
                RLESKIP(2, Uint8);
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ 3:
                RLESKIP(3, Uint8);
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ 4:
                RLESKIP(4, Uint16);
                ನಿಲ್ಲಿಸು;
            }

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು RLESKIP
        }
    }

    alpha = surf_src->map.info.a;
    // if left or right edge clipping needed, call clip blit
    ಆದರೆ (srcrect->x || srcrect->w != surf_src->w) {
        RLEClipBlit(w, srcbuf, surf_dst, dstbuf, srcrect, alpha);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಸ್ಥಿರಾಂಕ SDL_PixelFormatDetails *fmt = surf_src->fmt;

#ವ್ಯಾಖ್ಯಾನಿಸು RLEBLIT(bpp, Type, do_blit)                                   \
    ಮಾಡು {                                                              \
        ಪೂರ್ಣಾಂಕ linecount = srcrect->h;                                   \
        ಪೂರ್ಣಾಂಕ ofs = 0;                                                  \
        ಗಾಗಿ (;;) {                                                    \
            ಚಿಹ್ನೆರಹಿತ ಸತತ;                                             \
            ofs += *(Type *)srcbuf;                                   \
            ಸತತ = ((Type *)srcbuf)[1];                                \
            srcbuf += 2 * ಗಾತ್ರ(Type);                               \
            ಆದರೆ (ಸತತ) {                                                \
                do_blit(dstbuf + ofs * bpp, srcbuf, ಸತತ, bpp, alpha); \
                srcbuf += ಸತತ * bpp;                                  \
                ofs += ಸತತ;                                           \
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!ofs)                                          \
                ನಿಲ್ಲಿಸು;                                                \
            ಆದರೆ (ofs == w) {                                           \
                ofs = 0;                                              \
                dstbuf += surf_dst->pitch;                            \
                ಆದರೆ (!--linecount)                                     \
                    ನಿಲ್ಲಿಸು;                                            \
            }                                                         \
        }                                                             \
    } ಆಗ (0)

        ಆರಿಸು_BLIT(RLEBLIT, alpha, fmt);

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು RLEBLIT
    }

ಮುಗಿದ:
    // Unlock the destination if necessary
    ಆದರೆ (SDL_MUSTLOCK(surf_dst)) {
        SDL_UnlockSurface(surf_dst);
    }
    ಹಿಂತಿರುಗಿ true;
}

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು OPAQUE_BLIT

/*
 * Per-pixel blitting macros for translucent pixels:
 * These use the same techniques as the per-surface blitting macros
 */

/*
 * For 32bpp pixels, we have made sure the alpha is stored in the top
 * 8 bits, so proceed as usual
 */
#ವ್ಯಾಖ್ಯಾನಿಸು BLIT_TRANSL_888(src, dst)                        \
    ಮಾಡು {                                                 \
        Uint32 s = src;                                  \
        Uint32 d = dst;                                  \
        ಚಿಹ್ನೆರಹಿತ alpha = s >> 24;                        \
        Uint32 s1 = s & 0xff00ff;                        \
        Uint32 d1 = d & 0xff00ff;                        \
        d1 = (d1 + ((s1 - d1) * alpha >> 8)) & 0xff00ff; \
        s &= 0xff00;                                     \
        d &= 0xff00;                                     \
        d = (d + ((s - d) * alpha >> 8)) & 0xff00;       \
        dst = d1 | d | 0xff000000;                       \
    } ಆಗ (0)

/*
 * For 16bpp pixels, we have stored the 5 most significant alpha bits in
 * bits 5-10. As before, we can process all 3 RGB components at the same time.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು BLIT_TRANSL_565(src, dst)          \
    ಮಾಡು {                                   \
        Uint32 s = src;                    \
        Uint32 d = dst;                    \
        ಚಿಹ್ನೆರಹಿತ alpha = (s & 0x3e0) >> 5; \
        s &= 0x07e0f81f;                   \
        d = (d | d << 16) & 0x07e0f81f;    \
        d += (s - d) * alpha >> 5;         \
        d &= 0x07e0f81f;                   \
        dst = (Uint16)(d | d >> 16);       \
    } ಆಗ (0)

#ವ್ಯಾಖ್ಯಾನಿಸು BLIT_TRANSL_555(src, dst)          \
    ಮಾಡು {                                   \
        Uint32 s = src;                    \
        Uint32 d = dst;                    \
        ಚಿಹ್ನೆರಹಿತ alpha = (s & 0x3e0) >> 5; \
        s &= 0x03e07c1f;                   \
        d = (d | d << 16) & 0x03e07c1f;    \
        d += (s - d) * alpha >> 5;         \
        d &= 0x03e07c1f;                   \
        dst = (Uint16)(d | d >> 16);       \
    } ಆಗ (0)

// blit a pixel-alpha RLE surface clipped at the right and/or left edges
ಸ್ಥಿರ ಶೂನ್ಯ RLEAlphaClipBlit(ಪೂರ್ಣಾಂಕ w, Uint8 *srcbuf, SDL_Surface *surf_dst,
                             Uint8 *dstbuf, ಸ್ಥಿರಾಂಕ SDL_Rect *srcrect)
{
    ಸ್ಥಿರಾಂಕ SDL_PixelFormatDetails *df = surf_dst->fmt;
    /*
     * clipped blitter: Ptype is the destination pixel type,
     * Ctype the translucent count type, and do_blend the macro
     * to blend one pixel.
     */
#ವ್ಯಾಖ್ಯಾನಿಸು RLEALPHACLIPBLIT(Ptype, Ctype, do_blend)                          \
    ಮಾಡು {                                                                  \
        ಪೂರ್ಣಾಂಕ linecount = srcrect->h;                                       \
        ಪೂರ್ಣಾಂಕ ಎಡ = srcrect->x;                                            \
        ಪೂರ್ಣಾಂಕ ಬಲ = ಎಡ + srcrect->w;                                    \
        dstbuf -= ಎಡ * ಗಾತ್ರ(Ptype);                                   \
        ಮಾಡು {                                                              \
            ಪೂರ್ಣಾಂಕ ofs = 0;                                                  \
            /* blit opaque pixels on one line */                          \
            ಮಾಡು {                                                          \
                ಚಿಹ್ನೆರಹಿತ ಸತತ;                                             \
                ofs += ((Ctype *)srcbuf)[0];                              \
                ಸತತ = ((Ctype *)srcbuf)[1];                               \
                srcbuf += 2 * ಗಾತ್ರ(Ctype);                              \
                ಆದರೆ (ಸತತ) {                                                \
                    /* clip to left and right borders */                  \
                    ಪೂರ್ಣಾಂಕ cofs = ofs;                                       \
                    ಪೂರ್ಣಾಂಕ crun = ಸತತ;                                       \
                    ಆದರೆ (ಎಡ - cofs > 0) {                                \
                        crun -= ಎಡ - cofs;                              \
                        cofs = ಎಡ;                                      \
                    }                                                     \
                    ಆದರೆ (crun > ಬಲ - cofs)                              \
                        crun = ಬಲ - cofs;                              \
                    ಆದರೆ (crun > 0)                                         \
                        PIXEL_COPY(dstbuf + cofs * ಗಾತ್ರ(Ptype),         \
                                   srcbuf + (cofs - ofs) * ಗಾತ್ರ(Ptype), \
                                   (ಚಿಹ್ನೆರಹಿತ)crun, ಗಾತ್ರ(Ptype));        \
                    srcbuf += ಸತತ * ಗಾತ್ರ(Ptype);                        \
                    ofs += ಸತತ;                                           \
                } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!ofs)                                          \
                    ಹಿಂತಿರುಗಿ;                                               \
            } ಆಗ (ofs < w);                                            \
            /* skip padding if necessary */                               \
            ಸ್ಥಿರಾಂಕ size_t psize = ಗಾತ್ರ(Ptype);                           \
            ಆದರೆ (psize == 2)                                               \
                srcbuf += (uintptr_t)srcbuf & 2;                          \
            /* blit translucent pixels on the same line */                \
            ofs = 0;                                                      \
            ಮಾಡು {                                                          \
                ಚಿಹ್ನೆರಹಿತ ಸತತ;                                             \
                ofs += ((Uint16 *)srcbuf)[0];                             \
                ಸತತ = ((Uint16 *)srcbuf)[1];                              \
                srcbuf += 4;                                              \
                ಆದರೆ (ಸತತ) {                                                \
                    /* clip to left and right borders */                  \
                    ಪೂರ್ಣಾಂಕ cofs = ofs;                                       \
                    ಪೂರ್ಣಾಂಕ crun = ಸತತ;                                       \
                    ಆದರೆ (ಎಡ - cofs > 0) {                                \
                        crun -= ಎಡ - cofs;                              \
                        cofs = ಎಡ;                                      \
                    }                                                     \
                    ಆದರೆ (crun > ಬಲ - cofs)                              \
                        crun = ಬಲ - cofs;                              \
                    ಆದರೆ (crun > 0) {                                       \
                        Ptype *dst = (Ptype *)dstbuf + cofs;              \
                        Uint32 *src = (Uint32 *)srcbuf + (cofs - ofs);    \
                        ಪೂರ್ಣಾಂಕ i;                                            \
                        ಗಾಗಿ (i = 0; i < crun; i++)                        \
                            do_blend(src[i], dst[i]);                     \
                    }                                                     \
                    srcbuf += ಸತತ * 4;                                    \
                    ofs += ಸತತ;                                           \
                }                                                         \
            } ಆಗ (ofs < w);                                            \
            dstbuf += surf_dst->pitch;                                    \
        } ಆಗ (--linecount);                                            \
    } ಆಗ (0)

    ಆಯ್ಕೆ (df->ಬೈಟುಗಳು_ಪ್ರತಿ_pixel) {
    ಸ್ಥಿತಿ 2:
        ಆದರೆ (df->Gmask == 0x07e0 || df->Rmask == 0x07e0 || df->Bmask == 0x07e0) {
            RLEALPHACLIPBLIT(Uint16, Uint8, BLIT_TRANSL_565);
        } ಇಲ್ಲದಿದ್ದರೆ {
            RLEALPHACLIPBLIT(Uint16, Uint8, BLIT_TRANSL_555);
        }
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 4:
        RLEALPHACLIPBLIT(Uint32, Uint16, BLIT_TRANSL_888);
        ನಿಲ್ಲಿಸು;
    }
}

// blit a pixel-alpha RLE surface
ಸ್ಥಿರ bool SDLCALL SDL_RLEAlphaBlit(SDL_Surface *surf_src, ಸ್ಥಿರಾಂಕ SDL_Rect *srcrect,
                                     SDL_Surface *surf_dst, ಸ್ಥಿರಾಂಕ SDL_Rect *dstrect)
{
    ಪೂರ್ಣಾಂಕ x, y;
    ಪೂರ್ಣಾಂಕ w = surf_src->w;
    Uint8 *srcbuf, *dstbuf;
    ಸ್ಥಿರಾಂಕ SDL_PixelFormatDetails *df = surf_dst->fmt;

    // Lock the destination if necessary
    ಆದರೆ (SDL_MUSTLOCK(surf_dst)) {
        ಆದರೆ (!SDL_ಬೀಗ_Surface(surf_dst)) {
            ಹಿಂತಿರುಗಿ false;
        }
    }

    x = dstrect->x;
    y = dstrect->y;
    dstbuf = (Uint8 *)surf_dst->pixels + y * surf_dst->pitch + x * df->ಬೈಟುಗಳು_ಪ್ರತಿ_pixel;
    srcbuf = (Uint8 *)surf_src->map.ದತ್ತಾಂಶ + ಗಾತ್ರ(SDL_PixelFormat);

    {
        // skip lines at the top if necessary
        ಪೂರ್ಣಾಂಕ vskip = srcrect->y;
        ಆದರೆ (vskip) {
            ಪೂರ್ಣಾಂಕ ofs;
            ಆದರೆ (df->ಬೈಟುಗಳು_ಪ್ರತಿ_pixel == 2) {
                // the 16/32 interleaved format
                ಮಾಡು {
                    // skip opaque line
                    ofs = 0;
                    ಮಾಡು {
                        ಪೂರ್ಣಾಂಕ ಸತತ;
                        ofs += srcbuf[0];
                        ಸತತ = srcbuf[1];
                        srcbuf += 2;
                        ಆದರೆ (ಸತತ) {
                            srcbuf += 2 * ಸತತ;
                            ofs += ಸತತ;
                        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ofs == 0) {
                            ಹೋಗು ಮುಗಿದ;
                        }
                    } ಆಗ (ofs < w);

                    // skip padding
                    srcbuf += (uintptr_t)srcbuf & 2;

                    // skip translucent line
                    ofs = 0;
                    ಮಾಡು {
                        ಪೂರ್ಣಾಂಕ ಸತತ;
                        ofs += ((Uint16 *)srcbuf)[0];
                        ಸತತ = ((Uint16 *)srcbuf)[1];
                        srcbuf += 4 * (ಸತತ + 1);
                        ofs += ಸತತ;
                    } ಆಗ (ofs < w);
                } ಆಗ (--vskip);
            } ಇಲ್ಲದಿದ್ದರೆ {
                // the 32/32 interleaved format
                vskip <<= 1; // opaque and translucent have same format
                ಮಾಡು {
                    ofs = 0;
                    ಮಾಡು {
                        ಪೂರ್ಣಾಂಕ ಸತತ;
                        ofs += ((Uint16 *)srcbuf)[0];
                        ಸತತ = ((Uint16 *)srcbuf)[1];
                        srcbuf += 4;
                        ಆದರೆ (ಸತತ) {
                            srcbuf += 4 * ಸತತ;
                            ofs += ಸತತ;
                        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ofs == 0) {
                            ಹೋಗು ಮುಗಿದ;
                        }
                    } ಆಗ (ofs < w);
                } ಆಗ (--vskip);
            }
        }
    }

    // if left or right edge clipping needed, call clip blit
    ಆದರೆ (srcrect->x || srcrect->w != surf_src->w) {
        RLEAlphaClipBlit(w, srcbuf, surf_dst, dstbuf, srcrect);
    } ಇಲ್ಲದಿದ್ದರೆ {

        /*
         * non-clipped blitter. Ptype is the destination pixel type,
         * Ctype the translucent count type, and do_blend the
         * macro to blend one pixel.
         */
#ವ್ಯಾಖ್ಯಾನಿಸು RLEALPHABLIT(Ptype, Ctype, do_blend)                         \
    ಮಾಡು {                                                             \
        ಪೂರ್ಣಾಂಕ linecount = srcrect->h;                                  \
        ಮಾಡು {                                                         \
            ಪೂರ್ಣಾಂಕ ofs = 0;                                             \
            /* blit opaque pixels on one line */                     \
            ಮಾಡು {                                                     \
                ಚಿಹ್ನೆರಹಿತ ಸತತ;                                        \
                ofs += ((Ctype *)srcbuf)[0];                         \
                ಸತತ = ((Ctype *)srcbuf)[1];                          \
                srcbuf += 2 * ಗಾತ್ರ(Ctype);                         \
                ಆದರೆ (ಸತತ) {                                           \
                    PIXEL_COPY(dstbuf + ofs * ಗಾತ್ರ(Ptype), srcbuf, \
                               ಸತತ, ಗಾತ್ರ(Ptype));                  \
                    srcbuf += ಸತತ * ಗಾತ್ರ(Ptype);                   \
                    ofs += ಸತತ;                                      \
                } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!ofs)                                     \
                    ಹೋಗು ಮುಗಿದ;                                       \
            } ಆಗ (ofs < w);                                       \
            /* skip padding if necessary */                          \
            ಸ್ಥಿರಾಂಕ size_t psize = ಗಾತ್ರ(Ptype);                      \
            ಆದರೆ (psize == 2)                                          \
                srcbuf += (uintptr_t)srcbuf & 2;                     \
            /* blit translucent pixels on the same line */           \
            ofs = 0;                                                 \
            ಮಾಡು {                                                     \
                ಚಿಹ್ನೆರಹಿತ ಸತತ;                                        \
                ofs += ((Uint16 *)srcbuf)[0];                        \
                ಸತತ = ((Uint16 *)srcbuf)[1];                         \
                srcbuf += 4;                                         \
                ಆದರೆ (ಸತತ) {                                           \
                    Ptype *dst = (Ptype *)dstbuf + ofs;              \
                    ಚಿಹ್ನೆರಹಿತ i;                                      \
                    ಗಾಗಿ (i = 0; i < ಸತತ; i++) {                      \
                        Uint32 src = *(Uint32 *)srcbuf;              \
                        do_blend(src, *dst);                         \
                        srcbuf += 4;                                 \
                        dst++;                                       \
                    }                                                \
                    ofs += ಸತತ;                                      \
                }                                                    \
            } ಆಗ (ofs < w);                                       \
            dstbuf += surf_dst->pitch;                               \
        } ಆಗ (--linecount);                                       \
    } ಆಗ (0)

        ಆಯ್ಕೆ (df->ಬೈಟುಗಳು_ಪ್ರತಿ_pixel) {
        ಸ್ಥಿತಿ 2:
            ಆದರೆ (df->Gmask == 0x07e0 || df->Rmask == 0x07e0 || df->Bmask == 0x07e0) {
                RLEALPHABLIT(Uint16, Uint8, BLIT_TRANSL_565);
            } ಇಲ್ಲದಿದ್ದರೆ {
                RLEALPHABLIT(Uint16, Uint8, BLIT_TRANSL_555);
            }
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ 4:
            RLEALPHABLIT(Uint32, Uint16, BLIT_TRANSL_888);
            ನಿಲ್ಲಿಸು;
        }
    }

ಮುಗಿದ:
    // Unlock the destination if necessary
    ಆದರೆ (SDL_MUSTLOCK(surf_dst)) {
        SDL_UnlockSurface(surf_dst);
    }
    ಹಿಂತಿರುಗಿ true;
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
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ copy_opaque_16(ಶೂನ್ಯ *dst, ಸ್ಥಿರಾಂಕ Uint32 *src, ಪೂರ್ಣಾಂಕ n,
                          ಸ್ಥಿರಾಂಕ SDL_PixelFormatDetails *sfmt, ಸ್ಥಿರಾಂಕ SDL_PixelFormatDetails *dfmt)
{
    ಪೂರ್ಣಾಂಕ i;
    Uint16 *d = (Uint16 *)dst;
    ಗಾಗಿ (i = 0; i < n; i++) {
        ಚಿಹ್ನೆರಹಿತ r, g, b;
        RGB_FROM_PIXEL(*src, sfmt, r, g, b);
        PIXEL_FROM_RGB(*d, dfmt, r, g, b);
        src++;
        d++;
    }
    ಹಿಂತಿರುಗಿ n * 2;
}

// encode 32bpp rgb + a into 32bpp G0RAB format for blitting into 565
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ copy_transl_565(ಶೂನ್ಯ *dst, ಸ್ಥಿರಾಂಕ Uint32 *src, ಪೂರ್ಣಾಂಕ n,
                           ಸ್ಥಿರಾಂಕ SDL_PixelFormatDetails *sfmt, ಸ್ಥಿರಾಂಕ SDL_PixelFormatDetails *dfmt)
{
    ಪೂರ್ಣಾಂಕ i;
    Uint32 *d = (Uint32 *)dst;
    ಗಾಗಿ (i = 0; i < n; i++) {
        ಚಿಹ್ನೆರಹಿತ r, g, b, a;
        Uint16 pix;
        RGBA_FROM_8888(*src, sfmt, r, g, b, a);
        PIXEL_FROM_RGB(pix, dfmt, r, g, b);
        *d = ((pix & 0x7e0) << 16) | (pix & 0xf81f) | ((a << 2) & 0x7e0);
        src++;
        d++;
    }
    ಹಿಂತಿರುಗಿ n * 4;
}

// encode 32bpp rgb + a into 32bpp G0RAB format for blitting into 555
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ copy_transl_555(ಶೂನ್ಯ *dst, ಸ್ಥಿರಾಂಕ Uint32 *src, ಪೂರ್ಣಾಂಕ n,
                           ಸ್ಥಿರಾಂಕ SDL_PixelFormatDetails *sfmt, ಸ್ಥಿರಾಂಕ SDL_PixelFormatDetails *dfmt)
{
    ಪೂರ್ಣಾಂಕ i;
    Uint32 *d = (Uint32 *)dst;
    ಗಾಗಿ (i = 0; i < n; i++) {
        ಚಿಹ್ನೆರಹಿತ r, g, b, a;
        Uint16 pix;
        RGBA_FROM_8888(*src, sfmt, r, g, b, a);
        PIXEL_FROM_RGB(pix, dfmt, r, g, b);
        *d = ((pix & 0x3e0) << 16) | (pix & 0xfc1f) | ((a << 2) & 0x3e0);
        src++;
        d++;
    }
    ಹಿಂತಿರುಗಿ n * 4;
}

// encode 32bpp rgba into 32bpp rgba, keeping alpha (dual purpose)
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ copy_32(ಶೂನ್ಯ *dst, ಸ್ಥಿರಾಂಕ Uint32 *src, ಪೂರ್ಣಾಂಕ n,
                   ಸ್ಥಿರಾಂಕ SDL_PixelFormatDetails *sfmt, ಸ್ಥಿರಾಂಕ SDL_PixelFormatDetails *dfmt)
{
    ಪೂರ್ಣಾಂಕ i;
    Uint32 *d = (Uint32 *)dst;
    ಗಾಗಿ (i = 0; i < n; i++) {
        ಚಿಹ್ನೆರಹಿತ r, g, b, a;
        RGBA_FROM_8888(*src, sfmt, r, g, b, a);
        RLEPIXEL_FROM_RGBA(*d, dfmt, r, g, b, a);
        d++;
        src++;
    }
    ಹಿಂತಿರುಗಿ n * 4;
}

#ವ್ಯಾಖ್ಯಾನಿಸು ISOPAQUE(pixel, fmt) ((((pixel)&fmt->Amask) >> fmt->Ashift) == 255)

#ವ್ಯಾಖ್ಯಾನಿಸು ISTRANSL(pixel, fmt) \
    ((ಚಿಹ್ನೆರಹಿತ)((((pixel)&fmt->Amask) >> fmt->Ashift) - 1U) < 254U)

// convert surface to be quickly alpha-blittable onto dest, if possible
ಸ್ಥಿರ bool RLEAlphaSurface(SDL_Surface *surface)
{
    SDL_Surface *dest;
    ಸ್ಥಿರಾಂಕ SDL_PixelFormatDetails *df;
    ಪೂರ್ಣಾಂಕ maxsize = 0;
    ಪೂರ್ಣಾಂಕ max_opaque_ಸತತ;
    ಪೂರ್ಣಾಂಕ max_transl_ಸತತ = 65535;
    ಚಿಹ್ನೆರಹಿತ masksum;
    Uint8 *rlebuf, *dst;
    ಪೂರ್ಣಾಂಕ (*copy_opaque)(ಶೂನ್ಯ *, ಸ್ಥಿರಾಂಕ Uint32 *, ಪೂರ್ಣಾಂಕ,
                       ಸ್ಥಿರಾಂಕ SDL_PixelFormatDetails *, ಸ್ಥಿರಾಂಕ SDL_PixelFormatDetails *);
    ಪೂರ್ಣಾಂಕ (*copy_transl)(ಶೂನ್ಯ *, ಸ್ಥಿರಾಂಕ Uint32 *, ಪೂರ್ಣಾಂಕ,
                       ಸ್ಥಿರಾಂಕ SDL_PixelFormatDetails *, ಸ್ಥಿರಾಂಕ SDL_PixelFormatDetails *);

    dest = surface->map.info.dst_surface;
    ಆದರೆ (!dest) {
        ಹಿಂತಿರುಗಿ false;
    }
    df = dest->fmt;
    ಆದರೆ (surface->fmt->ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_pixel != 32) {
        ಹಿಂತಿರುಗಿ false; // only 32bpp source supported
    }

    /* find out whether the destination is one we support,
       and determine the max size of the encoded result */
    masksum = df->Rmask | df->Gmask | df->Bmask;
    ಆಯ್ಕೆ (df->ಬೈಟುಗಳು_ಪ್ರತಿ_pixel) {
    ಸ್ಥಿತಿ 2:
        // 16bpp: only support 565 and 555 formats
        ಆಯ್ಕೆ (masksum) {
        ಸ್ಥಿತಿ 0xffff:
            ಆದರೆ (df->Gmask == 0x07e0 || df->Rmask == 0x07e0 || df->Bmask == 0x07e0) {
                copy_opaque = copy_opaque_16;
                copy_transl = copy_transl_565;
            } ಇಲ್ಲದಿದ್ದರೆ {
                ಹಿಂತಿರುಗಿ false;
            }
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ 0x7fff:
            ಆದರೆ (df->Gmask == 0x03e0 || df->Rmask == 0x03e0 || df->Bmask == 0x03e0) {
                copy_opaque = copy_opaque_16;
                copy_transl = copy_transl_555;
            } ಇಲ್ಲದಿದ್ದರೆ {
                ಹಿಂತಿರುಗಿ false;
            }
            ನಿಲ್ಲಿಸು;
        ಪೂರ್ವನಿಯೋಜಿತ:
            ಹಿಂತಿರುಗಿ false;
        }
        max_opaque_ಸತತ = 255; // runs stored as bytes

        /* worst case is alternating opaque and translucent pixels,
           with room for alignment padding between lines */
        maxsize = surface->h * (2 + (4 + 2) * (surface->w + 1)) + 2;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 4:
        ಆದರೆ (masksum != 0x00ffffff) {
            ಹಿಂತಿರುಗಿ false; // requires unused high byte
        }
        copy_opaque = copy_32;
        copy_transl = copy_32;
        max_opaque_ಸತತ = 255; // runs stored as short ints

        // worst case is alternating opaque and translucent pixels
        maxsize = surface->h * 2 * 4 * (surface->w + 1) + 4;
        ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        ಹಿಂತಿರುಗಿ false; // anything else unsupported right now
    }

    maxsize += ಗಾತ್ರ(SDL_PixelFormat);
    rlebuf = (Uint8 *)SDL_malloc(maxsize);
    ಆದರೆ (!rlebuf) {
        ಹಿಂತಿರುಗಿ false;
    }
    // save the destination format so we can undo the encoding later
    *(SDL_PixelFormat *)rlebuf = dest->format;
    dst = rlebuf + ಗಾತ್ರ(SDL_PixelFormat);

    // Do the actual encoding
    {
        ಪೂರ್ಣಾಂಕ x, y;
        ಪೂರ್ಣಾಂಕ h = surface->h, w = surface->w;
        ಸ್ಥಿರಾಂಕ SDL_PixelFormatDetails *sf = surface->fmt;
        Uint32 *src = (Uint32 *)surface->pixels;
        Uint8 *lastline = dst; // end of last non-blank line

        // opaque counts are 8 or 16 bits, depending on target depth
#ವ್ಯಾಖ್ಯಾನಿಸು ಕೂಡಿಸು_OPAQUE_COUNTS(n, m)           \
    ಆದರೆ (df->ಬೈಟುಗಳು_ಪ್ರತಿ_pixel == 4) {         \
        ((Uint16 *)dst)[0] = (Uint16)n;   \
        ((Uint16 *)dst)[1] = (Uint16)m;   \
        dst += 4;                         \
    } ಇಲ್ಲದಿದ್ದರೆ {                              \
        dst[0] = (Uint8)n;                \
        dst[1] = (Uint8)m;                \
        dst += 2;                         \
    }

        // translucent counts are always 16 bit
#ವ್ಯಾಖ್ಯಾನಿಸು ಕೂಡಿಸು_TRANSL_COUNTS(n, m) \
    (((Uint16 *)dst)[0] = (Uint16)n, ((Uint16 *)dst)[1] = (Uint16)m, dst += 4)

        ಗಾಗಿ (y = 0; y < h; y++) {
            ಪೂರ್ಣಾಂಕ runstart, skipstart;
            ಪೂರ್ಣಾಂಕ blankline = 0;
            // First encode all opaque pixels of a scan line
            x = 0;
            ಮಾಡು {
                ಪೂರ್ಣಾಂಕ ಸತತ, skip, len;
                skipstart = x;
                ಆಗ (x < w && !ISOPAQUE(src[x], sf)) {
                    x++;
                }
                runstart = x;
                ಆಗ (x < w && ISOPAQUE(src[x], sf)) {
                    x++;
                }
                skip = runstart - skipstart;
                ಆದರೆ (skip == w) {
                    blankline = 1;
                }
                ಸತತ = x - runstart;
                ಆಗ (skip > max_opaque_ಸತತ) {
                    ಕೂಡಿಸು_OPAQUE_COUNTS(max_opaque_ಸತತ, 0);
                    skip -= max_opaque_ಸತತ;
                }
                len = SDL_min(ಸತತ, max_opaque_ಸತತ);
                ಕೂಡಿಸು_OPAQUE_COUNTS(skip, len);
                dst += copy_opaque(dst, src + runstart, len, sf, df);
                runstart += len;
                ಸತತ -= len;
                ಆಗ (ಸತತ) {
                    len = SDL_min(ಸತತ, max_opaque_ಸತತ);
                    ಕೂಡಿಸು_OPAQUE_COUNTS(0, len);
                    dst += copy_opaque(dst, src + runstart, len, sf, df);
                    runstart += len;
                    ಸತತ -= len;
                }
            } ಆಗ (x < w);

            // Make sure the next output address is 32-bit aligned
            dst += (uintptr_t)dst & 2;

            // Next, encode all translucent pixels of the same scan line
            x = 0;
            ಮಾಡು {
                ಪೂರ್ಣಾಂಕ ಸತತ, skip, len;
                skipstart = x;
                ಆಗ (x < w && !ISTRANSL(src[x], sf)) {
                    x++;
                }
                runstart = x;
                ಆಗ (x < w && ISTRANSL(src[x], sf)) {
                    x++;
                }
                skip = runstart - skipstart;
                blankline &= (skip == w);
                ಸತತ = x - runstart;
                ಆಗ (skip > max_transl_ಸತತ) {
                    ಕೂಡಿಸು_TRANSL_COUNTS(max_transl_ಸತತ, 0);
                    skip -= max_transl_ಸತತ;
                }
                len = SDL_min(ಸತತ, max_transl_ಸತತ);
                ಕೂಡಿಸು_TRANSL_COUNTS(skip, len);
                dst += copy_transl(dst, src + runstart, len, sf, df);
                runstart += len;
                ಸತತ -= len;
                ಆಗ (ಸತತ) {
                    len = SDL_min(ಸತತ, max_transl_ಸತತ);
                    ಕೂಡಿಸು_TRANSL_COUNTS(0, len);
                    dst += copy_transl(dst, src + runstart, len, sf, df);
                    runstart += len;
                    ಸತತ -= len;
                }
                ಆದರೆ (!blankline) {
                    lastline = dst;
                }
            } ಆಗ (x < w);

            src += surface->pitch >> 2;
        }
        dst = lastline; // back up past trailing blank lines
        ಕೂಡಿಸು_OPAQUE_COUNTS(0, 0);
    }

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು ಕೂಡಿಸು_OPAQUE_COUNTS
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು ಕೂಡಿಸು_TRANSL_COUNTS

    // reallocate the buffer to release unused memory
    {
        Uint8 *p = (Uint8 *)SDL_realloc(rlebuf, dst - rlebuf);
        ಆದರೆ (!p) {
            p = rlebuf;
        }
        surface->map.ದತ್ತಾಂಶ = p;
    }

    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ Uint32 getpix_8(ಸ್ಥಿರಾಂಕ Uint8 *srcbuf)
{
    ಹಿಂತಿರುಗಿ *srcbuf;
}

ಸ್ಥಿರ Uint32 getpix_16(ಸ್ಥಿರಾಂಕ Uint8 *srcbuf)
{
    ಹಿಂತಿರುಗಿ *(ಸ್ಥಿರಾಂಕ Uint16 *)srcbuf;
}

ಸ್ಥಿರ Uint32 getpix_24(ಸ್ಥಿರಾಂಕ Uint8 *srcbuf)
{
#ಆದರೆ SDL_BYTEORDER == SDL_LIL_ENDIAN
    ಹಿಂತಿರುಗಿ srcbuf[0] + (srcbuf[1] << 8) + (srcbuf[2] << 16);
#ಇಲ್ಲದಿದ್ದರೆ
    ಹಿಂತಿರುಗಿ (srcbuf[0] << 16) + (srcbuf[1] << 8) + srcbuf[2];
#ಆದರೆ_ಅಂತ್ಯ
}

ಸ್ಥಿರ Uint32 getpix_32(ಸ್ಥಿರಾಂಕ Uint8 *srcbuf)
{
    ಹಿಂತಿರುಗಿ *(ಸ್ಥಿರಾಂಕ Uint32 *)srcbuf;
}

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Uint32 (*getpix_func)(ಸ್ಥಿರಾಂಕ Uint8 *);

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ getpix_func getpixes[4] = {
    getpix_8, getpix_16, getpix_24, getpix_32
};

ಸ್ಥಿರ bool RLEColorkeySurface(SDL_Surface *surface)
{
    SDL_Surface *dest;
    Uint8 *rlebuf, *dst;
    ಪೂರ್ಣಾಂಕ maxn;
    ಪೂರ್ಣಾಂಕ y;
    Uint8 *srcbuf, *lastline;
    ಪೂರ್ಣಾಂಕ maxsize = 0;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ bpp = surface->fmt->ಬೈಟುಗಳು_ಪ್ರತಿ_pixel;
    getpix_func getpix;
    Uint32 ckey, rgbmask;
    ಪೂರ್ಣಾಂಕ w, h;

    dest = surface->map.info.dst_surface;
    ಆದರೆ (!dest) {
        ಹಿಂತಿರುಗಿ false;
    }

    // calculate the worst case size for the compressed surface
    ಆಯ್ಕೆ (bpp) {
    ಸ್ಥಿತಿ 1:
        /* worst case is alternating opaque and transparent pixels,
           starting with an opaque pixel */
        maxsize = surface->h * 3 * (surface->w / 2 + 1) + 2;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 2:
    ಸ್ಥಿತಿ 3:
        // worst case is solid runs, at most 255 pixels wide
        maxsize = surface->h * (2 * (surface->w / 255 + 1) + surface->w * bpp) + 2;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 4:
        // worst case is solid runs, at most 65535 pixels wide
        maxsize = surface->h * (4 * (surface->w / 65535 + 1) + surface->w * 4) + 4;
        ನಿಲ್ಲಿಸು;

    ಪೂರ್ವನಿಯೋಜಿತ:
        ಹಿಂತಿರುಗಿ false;
    }

    maxsize += ಗಾತ್ರ(SDL_PixelFormat);
    rlebuf = (Uint8 *)SDL_malloc(maxsize);
    ಆದರೆ (!rlebuf) {
        ಹಿಂತಿರುಗಿ false;
    }
    // save the destination format so we can undo the encoding later
    *(SDL_PixelFormat *)rlebuf = dest->format;

    // Set up the conversion
    srcbuf = (Uint8 *)surface->pixels;
    maxn = bpp == 4 ? 65535 : 255;
    dst = rlebuf + ಗಾತ್ರ(SDL_PixelFormat);
    rgbmask = ~surface->fmt->Amask;
    ckey = surface->map.info.colorkey & rgbmask;
    lastline = dst;
    getpix = getpixes[bpp - 1];
    w = surface->w;
    h = surface->h;

#ವ್ಯಾಖ್ಯಾನಿಸು ಕೂಡಿಸು_COUNTS(n, m)                \
    ಆದರೆ (bpp == 4) {                     \
        ((Uint16 *)dst)[0] = (Uint16)n; \
        ((Uint16 *)dst)[1] = (Uint16)m; \
        dst += 4;                       \
    } ಇಲ್ಲದಿದ್ದರೆ {                            \
        dst[0] = (Uint8)n;              \
        dst[1] = (Uint8)m;              \
        dst += 2;                       \
    }

    ಗಾಗಿ (y = 0; y < h; y++) {
        ಪೂರ್ಣಾಂಕ x = 0;
        ಪೂರ್ಣಾಂಕ blankline = 0;
        ಮಾಡು {
            ಪೂರ್ಣಾಂಕ ಸತತ, skip;
            ಪೂರ್ಣಾಂಕ len;
            ಪೂರ್ಣಾಂಕ runstart;
            ಪೂರ್ಣಾಂಕ skipstart = x;

            // find run of transparent, then opaque pixels
            ಆಗ (x < w && (getpix(srcbuf + x * bpp) & rgbmask) == ckey) {
                x++;
            }
            runstart = x;
            ಆಗ (x < w && (getpix(srcbuf + x * bpp) & rgbmask) != ckey) {
                x++;
            }
            skip = runstart - skipstart;
            ಆದರೆ (skip == w) {
                blankline = 1;
            }
            ಸತತ = x - runstart;

            // encode segment
            ಆಗ (skip > maxn) {
                ಕೂಡಿಸು_COUNTS(maxn, 0);
                skip -= maxn;
            }
            len = SDL_min(ಸತತ, maxn);
            ಕೂಡಿಸು_COUNTS(skip, len);
            SDL_memcpy(dst, srcbuf + runstart * bpp, (size_t)len * bpp);
            dst += len * bpp;
            ಸತತ -= len;
            runstart += len;
            ಆಗ (ಸತತ) {
                len = SDL_min(ಸತತ, maxn);
                ಕೂಡಿಸು_COUNTS(0, len);
                SDL_memcpy(dst, srcbuf + runstart * bpp, (size_t)len * bpp);
                dst += len * bpp;
                runstart += len;
                ಸತತ -= len;
            }
            ಆದರೆ (!blankline) {
                lastline = dst;
            }
        } ಆಗ (x < w);

        srcbuf += surface->pitch;
    }
    dst = lastline; // back up bast trailing blank lines
    ಕೂಡಿಸು_COUNTS(0, 0);

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು ಕೂಡಿಸು_COUNTS

    // reallocate the buffer to release unused memory
    {
        // If SDL_realloc returns NULL, the original block is left intact
        Uint8 *p = (Uint8 *)SDL_realloc(rlebuf, dst - rlebuf);
        ಆದರೆ (!p) {
            p = rlebuf;
        }
        surface->map.ದತ್ತಾಂಶ = p;
    }

    ಹಿಂತಿರುಗಿ true;
}

bool SDL_RLESurface(SDL_Surface *surface)
{
    ಪೂರ್ಣಾಂಕ flags;

    // Clear any previous RLE conversion
    ಆದರೆ (surface->ಆಂತರಿಕ_flags & SDL_ಆಂತರಿಕ_SURFACE_RLEACCEL) {
        SDL_UnRLESurface(surface);
    }

    // We don't support RLE encoding of bitmaps
    ಆದರೆ (SDL_BITSPERPIXEL(surface->format) < 8) {
        ಹಿಂತಿರುಗಿ false;
    }

    // Make sure the pixels are available
    ಆದರೆ (!surface->pixels) {
        ಹಿಂತಿರುಗಿ false;
    }

    flags = surface->map.info.flags;
    ಆದರೆ (flags & SDL_COPY_COLORKEY) {
        // ok
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((flags & SDL_COPY_BLEND) && SDL_ISPIXELFORMAT_ALPHA(surface->format)) {
        // ok
    } ಇಲ್ಲದಿದ್ದರೆ {
        // If we don't have colorkey or blending, nothing to do...
        ಹಿಂತಿರುಗಿ false;
    }

    // Pass on combinations not supported
    ಆದರೆ ((flags & SDL_COPY_MODULATE_COLOR) ||
        ((flags & SDL_COPY_MODULATE_ALPHA) && SDL_ISPIXELFORMAT_ALPHA(surface->format)) ||
        (flags & (SDL_COPY_BLEND_PREMULTIPLIED | SDL_COPY_ಕೂಡಿಸು | SDL_COPY_ಕೂಡಿಸು_PREMULTIPLIED | SDL_COPY_MOD | SDL_COPY_MUL)) ||
        (flags & SDL_COPY_ಹತ್ತಿರದ)) {
        ಹಿಂತಿರುಗಿ false;
    }

    // Encode and set up the blit
    ಆದರೆ (!SDL_ISPIXELFORMAT_ALPHA(surface->format) || !(flags & SDL_COPY_BLEND)) {
        ಆದರೆ (!surface->map.ತಟಸ್ಥ) {
            ಹಿಂತಿರುಗಿ false;
        }
        ಆದರೆ (!RLEColorkeySurface(surface)) {
            ಹಿಂತಿರುಗಿ false;
        }
        surface->map.blit = SDL_RLEBlit;
        surface->map.info.flags |= SDL_COPY_RLE_COLORKEY;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (!RLEAlphaSurface(surface)) {
            ಹಿಂತಿರುಗಿ false;
        }
        surface->map.blit = SDL_RLEAlphaBlit;
        surface->map.info.flags |= SDL_COPY_RLE_ALPHAKEY;
    }

    ಆದರೆ (!(surface->flags & SDL_SURFACE_PREALLOCATED)) {
        surface->saved_pixels = surface->pixels;
        surface->pixels = ಖಾಲಿ;
    }

    // The surface is now accelerated
    surface->ಆಂತರಿಕ_flags |= SDL_ಆಂತರಿಕ_SURFACE_RLEACCEL;
    SDL_Update_Surface_ಬೀಗ_Flag(surface);

    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ SDL_UnRLESurface(SDL_Surface *surface)
{
    ಆದರೆ (surface->ಆಂತರಿಕ_flags & SDL_ಆಂತರಿಕ_SURFACE_RLEACCEL) {
        surface->ಆಂತರಿಕ_flags &= ~SDL_ಆಂತರಿಕ_SURFACE_RLEACCEL;

        surface->map.info.flags &= ~(SDL_COPY_RLE_COLORKEY | SDL_COPY_RLE_ALPHAKEY);

        ಆದರೆ (!(surface->flags & SDL_SURFACE_PREALLOCATED)) {
            surface->pixels = surface->saved_pixels;
            surface->saved_pixels = ಖಾಲಿ;
        }

        SDL_free(surface->map.ದತ್ತಾಂಶ);
        surface->map.ದತ್ತಾಂಶ = ಖಾಲಿ;

        SDL_InvalidateMap(&surface->map);

        SDL_Update_Surface_ಬೀಗ_Flag(surface);
    }
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_HAVE_RLE
