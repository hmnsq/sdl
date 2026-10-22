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

#यदि_परिभाषितम् SDL_HAVE_RLE

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

#अन्तर्भाव "SDL_sysvideo.h"
#अन्तर्भाव "SDL_surface_c.h"
#अन्तर्भाव "SDL_pixels_c.h"
#अन्तर्भाव "SDL_RLEaccel_c.h"

#परिभाषय PIXEL_COPY(गन्तव्यम्, from, len, bpp) \
    SDL_memcpy(गन्तव्यम्, from, (size_t)(len) * (bpp))

/*
 * Various colorkey blit methods, for opaque and per-surface alpha
 */

#परिभाषय OPAQUE_BLIT(गन्तव्यम्, from, दीर्घता, bpp, alpha) \
    PIXEL_COPY(गन्तव्यम्, from, दीर्घता, bpp)

/*
 * For 32bpp pixels on the form 0x00rrggbb:
 * If we treat the middle component separately, we can process the two
 * remaining in parallel. This is safe to do because of the gap to the left
 * of each component, so the bits from the multiplication don't collide.
 * This can be used for any RGB permutation of course.
 */
#परिभाषय ALPHA_BLIT32_888(गन्तव्यम्, from, दीर्घता, bpp, alpha)       \
    कुरु {                                                     \
        पूर्णाङ्क i;                                               \
        Uint32 *src = (Uint32 *)(from);                      \
        Uint32 *dst = (Uint32 *)(गन्तव्यम्);                        \
        प्रति (i = 0; i < (पूर्णाङ्क)(दीर्घता); i++) {                \
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
    } यावत् (0)

/*
 * For 16bpp pixels we can go a step further: put the middle component
 * in the high 16 bits of a 32 bit word, and process all three RGB
 * components at the same time. Since the smallest gap is here just
 * 5 bits, we have to scale alpha down to 5 bits as well.
 */
#परिभाषय ALPHA_BLIT16_565(गन्तव्यम्, from, दीर्घता, bpp, alpha) \
    कुरु {                                               \
        पूर्णाङ्क i;                                         \
        Uint16 *src = (Uint16 *)(from);                \
        Uint16 *dst = (Uint16 *)(गन्तव्यम्);                  \
        Uint32 ALPHA = alpha >> 3;                     \
        प्रति (i = 0; i < (पूर्णाङ्क)(दीर्घता); i++) {          \
            Uint32 s = *src++;                         \
            Uint32 d = *dst;                           \
            s = (s | s << 16) & 0x07e0f81f;            \
            d = (d | d << 16) & 0x07e0f81f;            \
            d += (s - d) * ALPHA >> 5;                 \
            d &= 0x07e0f81f;                           \
            *dst++ = (Uint16)(d | d >> 16);            \
        }                                              \
    } यावत् (0)

#परिभाषय ALPHA_BLIT16_555(गन्तव्यम्, from, दीर्घता, bpp, alpha) \
    कुरु {                                               \
        पूर्णाङ्क i;                                         \
        Uint16 *src = (Uint16 *)(from);                \
        Uint16 *dst = (Uint16 *)(गन्तव्यम्);                  \
        Uint32 ALPHA = alpha >> 3;                     \
        प्रति (i = 0; i < (पूर्णाङ्क)(दीर्घता); i++) {          \
            Uint32 s = *src++;                         \
            Uint32 d = *dst;                           \
            s = (s | s << 16) & 0x03e07c1f;            \
            d = (d | d << 16) & 0x03e07c1f;            \
            d += (s - d) * ALPHA >> 5;                 \
            d &= 0x03e07c1f;                           \
            *dst++ = (Uint16)(d | d >> 16);            \
        }                                              \
    } यावत् (0)

/*
 * The general slow catch-all function, for remaining depths and formats
 */
#यदि SDL_BYTEORDER == SDL_BIG_ENDIAN
#परिभाषय समुच्चयः_RGB24(dst, d)      \
    dst[0] = (Uint8)(d >> 16); \
    dst[1] = (Uint8)(d >> 8);  \
    dst[2] = (Uint8)(d);
#अन्यथा
#परिभाषय समुच्चयः_RGB24(dst, d)      \
    dst[0] = (Uint8)(d);       \
    dst[1] = (Uint8)(d >> 8);  \
    dst[2] = (Uint8)(d >> 16);
#यदि_अन्तः
#परिभाषय ALPHA_BLIT_ANY(गन्तव्यम्, from, दीर्घता, bpp, alpha)             \
    कुरु {                                                         \
        पूर्णाङ्क i;                                                   \
        Uint8 *src = from;                                       \
        Uint8 *dst = गन्तव्यम्;                                         \
        प्रति (i = 0; i < (पूर्णाङ्क)(दीर्घता); i++) {                    \
            Uint32 s = 0, d = 0;                                 \
            अचिह्नित rs, gs, bs, rd, gd, bd;                     \
            विकल्प (bpp) {                                       \
            पक्ष 2:                                              \
                s = *(Uint16 *)src;                              \
                d = *(Uint16 *)dst;                              \
                भङ्ग;                                           \
            पक्ष 3:                                              \
                s = GET_RGB24(src);                              \
                d = GET_RGB24(dst);                              \
                भङ्ग;                                           \
            पक्ष 4:                                              \
                s = *(Uint32 *)src;                              \
                d = *(Uint32 *)dst;                              \
                भङ्ग;                                           \
            }                                                    \
            RGB_FROM_PIXEL(s, fmt, rs, gs, bs);                  \
            RGB_FROM_PIXEL(d, fmt, rd, gd, bd);                  \
            rd += (rs - rd) * alpha >> 8;                        \
            gd += (gs - gd) * alpha >> 8;                        \
            bd += (bs - bd) * alpha >> 8;                        \
            PIXEL_FROM_RGB(d, fmt, rd, gd, bd);                  \
            विकल्प (bpp) {                                       \
            पक्ष 2:                                              \
                *(Uint16 *)dst = (Uint16)d;                      \
                भङ्ग;                                           \
            पक्ष 3:                                              \
                समुच्चयः_RGB24(dst, d);                               \
                भङ्ग;                                           \
            पक्ष 4:                                              \
                *(Uint32 *)dst = d;                              \
                भङ्ग;                                           \
            }                                                    \
            src += bpp;                                          \
            dst += bpp;                                          \
        }                                                        \
    } यावत् (0)

/*
 * Special case: 50% alpha (alpha=128)
 * This is treated specially because it can be optimized very well, and
 * since it is good for many cases of semi-translucency.
 * The theory is to do all three components at the same time:
 * First zero the lowest bit of each component, which gives us room to
 * add them. Then shift right and add the sum of the lowest bits.
 */
#परिभाषय ALPHA_BLIT32_888_50(गन्तव्यम्, from, दीर्घता, bpp, alpha)                                 \
    कुरु {                                                                                  \
        पूर्णाङ्क i;                                                                            \
        Uint32 *src = (Uint32 *)(from);                                                   \
        Uint32 *dst = (Uint32 *)(गन्तव्यम्);                                                     \
        प्रति (i = 0; i < (पूर्णाङ्क)(दीर्घता); i++) {                                             \
            Uint32 s = *src++;                                                            \
            Uint32 d = *dst;                                                              \
            *dst++ = (((s & 0x00fefefe) + (d & 0x00fefefe)) >> 1) + (s & d & 0x00010101); \
        }                                                                                 \
    } यावत् (0)

/*
 * For 16bpp, we can actually blend two pixels in parallel, if we take
 * care to shift before we add, not after.
 */

// helper: blend a single 16 bit pixel at 50%
#परिभाषय BLEND16_50(dst, src, आवरणम्)                           \
    कुरु {                                                     \
        Uint32 s = *src++;                                   \
        Uint32 d = *dst;                                     \
        *dst++ = (Uint16)((((s & आवरणम्) + (d & आवरणम्)) >> 1) + \
                          (s & d & (~आवरणम् & 0xffff)));       \
    } यावत् (0)

// basic 16bpp blender. mask is the pixels to keep when adding.
#परिभाषय ALPHA_BLIT16_50(गन्तव्यम्, from, दीर्घता, bpp, alpha, आवरणम्)                                                                              \
    कुरु {                                                                                                                                 \
        अचिह्नित n = (दीर्घता);                                                                                                           \
        Uint16 *src = (Uint16 *)(from);                                                                                                  \
        Uint16 *dst = (Uint16 *)(गन्तव्यम्);                                                                                                    \
        यदि (((uintptr_t)src ^ (uintptr_t)dst) & 3) {                                                                                     \
            /* source and destination not in phase, blit one by one */                                                                   \
            यावत् (n--)                                                                                                                  \
                BLEND16_50(dst, src, आवरणम्);                                                                                              \
        } अन्यथा {                                                                                                                         \
            यदि ((uintptr_t)src & 3) {                                                                                                    \
                /* first odd pixel */                                                                                                    \
                BLEND16_50(dst, src, आवरणम्);                                                                                              \
                n--;                                                                                                                     \
            }                                                                                                                            \
            प्रति (; n > 1; n -= 2) {                                                                                                      \
                Uint32 s = *(Uint32 *)src;                                                                                               \
                Uint32 d = *(Uint32 *)dst;                                                                                               \
                *(Uint32 *)dst = ((s & (आवरणम् | आवरणम् << 16)) >> 1) + ((d & (आवरणम् | आवरणम् << 16)) >> 1) + (s & d & (~(आवरणम् | आवरणम् << 16))); \
                src += 2;                                                                                                                \
                dst += 2;                                                                                                                \
            }                                                                                                                            \
            यदि (n)                                                                                                                       \
                BLEND16_50(dst, src, आवरणम्); /* last odd pixel */                                                                         \
        }                                                                                                                                \
    } यावत् (0)

#परिभाषय ALPHA_BLIT16_565_50(गन्तव्यम्, from, दीर्घता, bpp, alpha) \
    ALPHA_BLIT16_50(गन्तव्यम्, from, दीर्घता, bpp, alpha, 0xf7deU)

#परिभाषय ALPHA_BLIT16_555_50(गन्तव्यम्, from, दीर्घता, bpp, alpha) \
    ALPHA_BLIT16_50(गन्तव्यम्, from, दीर्घता, bpp, alpha, 0xfbdeU)

#परिभाषय वृणु_BLIT(blitter, alpha, fmt)                                                                                                              \
    कुरु {                                                                                                                                              \
        यदि (alpha == 255) {                                                                                                                           \
            विकल्प (fmt->अष्टकानि_प्रत्येकम्_pixel) {                                                                                                             \
            पक्ष 1:                                                                                                                                   \
                blitter(1, Uint8, OPAQUE_BLIT);                                                                                                       \
                भङ्ग;                                                                                                                                \
            पक्ष 2:                                                                                                                                   \
                blitter(2, Uint8, OPAQUE_BLIT);                                                                                                       \
                भङ्ग;                                                                                                                                \
            पक्ष 3:                                                                                                                                   \
                blitter(3, Uint8, OPAQUE_BLIT);                                                                                                       \
                भङ्ग;                                                                                                                                \
            पक्ष 4:                                                                                                                                   \
                blitter(4, Uint16, OPAQUE_BLIT);                                                                                                      \
                भङ्ग;                                                                                                                                \
            }                                                                                                                                         \
        } अन्यथा {                                                                                                                                      \
            विकल्प (fmt->अष्टकानि_प्रत्येकम्_pixel) {                                                                                                             \
            पक्ष 1:                                                                                                                                   \
                /* No 8bpp alpha blitting */                                                                                                          \
                भङ्ग;                                                                                                                                \
                                                                                                                                                      \
            पक्ष 2:                                                                                                                                   \
                विकल्प (fmt->Rmask | fmt->Gmask | fmt->Bmask) {                                                                                       \
                पक्ष 0xffff:                                                                                                                          \
                    यदि (fmt->Gmask == 0x07e0 || fmt->Rmask == 0x07e0 || fmt->Bmask == 0x07e0) {                                                       \
                        यदि (alpha == 128) {                                                                                                           \
                            blitter(2, Uint8, ALPHA_BLIT16_565_50);                                                                                   \
                        } अन्यथा {                                                                                                                      \
                            blitter(2, Uint8, ALPHA_BLIT16_565);                                                                                      \
                        }                                                                                                                             \
                    } अन्यथा {                                                                                                                          \
                        गच्छ general16;                                                                                                               \
                    }                                                                                                                                 \
                    भङ्ग;                                                                                                                            \
                                                                                                                                                      \
                पक्ष 0x7fff:                                                                                                                          \
                    यदि (fmt->Gmask == 0x03e0 || fmt->Rmask == 0x03e0 || fmt->Bmask == 0x03e0) {                                                       \
                        यदि (alpha == 128) {                                                                                                           \
                            blitter(2, Uint8, ALPHA_BLIT16_555_50);                                                                                   \
                        } अन्यथा {                                                                                                                      \
                            blitter(2, Uint8, ALPHA_BLIT16_555);                                                                                      \
                        }                                                                                                                             \
                        भङ्ग;                                                                                                                        \
                    } अन्यथा {                                                                                                                          \
                        गच्छ general16;                                                                                                               \
                    }                                                                                                                                 \
                    भङ्ग;                                                                                                                            \
                                                                                                                                                      \
                स्वभाव:                                                                                                                              \
                general16:                                                                                                                            \
                    blitter(2, Uint8, ALPHA_BLIT_ANY);                                                                                                \
                }                                                                                                                                     \
                भङ्ग;                                                                                                                                \
                                                                                                                                                      \
            पक्ष 3:                                                                                                                                   \
                blitter(3, Uint8, ALPHA_BLIT_ANY);                                                                                                    \
                भङ्ग;                                                                                                                                \
                                                                                                                                                      \
            पक्ष 4:                                                                                                                                   \
                यदि ((fmt->Rmask | fmt->Gmask | fmt->Bmask) == 0x00ffffff && (fmt->Gmask == 0xff00 || fmt->Rmask == 0xff00 || fmt->Bmask == 0xff00)) { \
                    यदि (alpha == 128) {                                                                                                               \
                        blitter(4, Uint16, ALPHA_BLIT32_888_50);                                                                                      \
                    } अन्यथा {                                                                                                                          \
                        blitter(4, Uint16, ALPHA_BLIT32_888);                                                                                         \
                    }                                                                                                                                 \
                } अन्यथा {                                                                                                                              \
                    blitter(4, Uint16, ALPHA_BLIT_ANY);                                                                                               \
                }                                                                                                                                     \
                भङ्ग;                                                                                                                                \
            }                                                                                                                                         \
        }                                                                                                                                             \
    } यावत् (0)

/*
 * Set a pixel value using the given format, except that the alpha value is
 * placed in the top byte. This is the format used for RLE with alpha.
 */
#परिभाषय RLEPIXEL_FROM_RGBA(Pixel, fmt, r, g, b, a)   \
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
#परिभाषय RLECLIPBLIT(bpp, Type, do_blit)                                    \
    कुरु {                                                                   \
        पूर्णाङ्क linecount = srcrect->h;                                        \
        पूर्णाङ्क ofs = 0;                                                       \
        पूर्णाङ्क वामः = srcrect->x;                                             \
        पूर्णाङ्क दक्षिणः = वामः + srcrect->w;                                     \
        dstbuf -= वामः * bpp;                                              \
        प्रति (;;) {                                                         \
            पूर्णाङ्क सततम्;                                                       \
            ofs += *(Type *)srcbuf;                                        \
            सततम् = ((Type *)srcbuf)[1];                                     \
            srcbuf += 2 * परिमाण(Type);                                    \
            यदि (सततम्) {                                                     \
                /* clip to left and right borders */                       \
                यदि (ofs < दक्षिणः) {                                         \
                    पूर्णाङ्क start = 0;                                         \
                    पूर्णाङ्क len = सततम्;                                         \
                    पूर्णाङ्क startcol;                                          \
                    यदि (वामः - ofs > 0) {                                  \
                        start = वामः - ofs;                                \
                        len -= start;                                      \
                        यदि (len <= 0)                                      \
                            गच्छ nocopy##bpp##do_blit;                     \
                    }                                                      \
                    startcol = ofs + start;                                \
                    यदि (len > दक्षिणः - startcol)                            \
                        len = दक्षिणः - startcol;                            \
                    do_blit(dstbuf + startcol * bpp, srcbuf + start * bpp, \
                            len, bpp, alpha);                              \
                }                                                          \
                nocopy##bpp##do_blit : srcbuf += सततम् * bpp;                \
                ofs += सततम्;                                                \
            } अन्यथा यदि (!ofs) {                                             \
                भङ्ग;                                                     \
            }                                                              \
                                                                           \
            यदि (ofs == w) {                                                \
                ofs = 0;                                                   \
                dstbuf += surf_dst->pitch;                                 \
                यदि (!--linecount) {                                        \
                    भङ्ग;                                                 \
                }                                                          \
            }                                                              \
        }                                                                  \
    } यावत् (0)

स्थिर शून्य RLEClipBlit(पूर्णाङ्क w, Uint8 *srcbuf, SDL_Surface *surf_dst,
                        Uint8 *dstbuf, ध्रुव SDL_Rect *srcrect, अचिह्नित alpha)
{
    ध्रुव SDL_PixelFormatDetails *fmt = surf_dst->fmt;

    वृणु_BLIT(RLECLIPBLIT, alpha, fmt);
}

#अपरिभाषय RLECLIPBLIT

// blit a colorkeyed RLE surface
स्थिर bool SDLCALL SDL_RLEBlit(SDL_Surface *surf_src, ध्रुव SDL_Rect *srcrect,
                                SDL_Surface *surf_dst, ध्रुव SDL_Rect *dstrect)
{
    Uint8 *dstbuf;
    Uint8 *srcbuf;
    पूर्णाङ्क x, y;
    पूर्णाङ्क w = surf_src->w;
    अचिह्नित alpha;

    // Lock the destination if necessary
    यदि (SDL_MUSTLOCK(surf_dst)) {
        यदि (!SDL_तालकम्_Surface(surf_dst)) {
            प्रत्यागम false;
        }
    }

    // Set up the source and destination pointers
    x = dstrect->x;
    y = dstrect->y;
    dstbuf = (Uint8 *)surf_dst->pixels + y * surf_dst->pitch + x * surf_src->fmt->अष्टकानि_प्रत्येकम्_pixel;
    srcbuf = (Uint8 *)surf_src->map.दत्त + परिमाण(SDL_PixelFormat);

    {
        // skip lines at the top if necessary
        पूर्णाङ्क vskip = srcrect->y;
        पूर्णाङ्क ofs = 0;
        यदि (vskip) {

#परिभाषय RLESKIP(bpp, Type)          \
    प्रति (;;) {                      \
        पूर्णाङ्क सततम्;                    \
        ofs += *(Type *)srcbuf;     \
        सततम् = ((Type *)srcbuf)[1];  \
        srcbuf += परिमाण(Type) * 2; \
        यदि (सततम्) {                  \
            srcbuf += सततम् * bpp;    \
            ofs += सततम्;             \
        } अन्यथा यदि (!ofs)            \
            गच्छ समाप्तम्;              \
        यदि (ofs == w) {             \
            ofs = 0;                \
            यदि (!--vskip)           \
                भङ्ग;              \
        }                           \
    }

            विकल्प (surf_src->fmt->अष्टकानि_प्रत्येकम्_pixel) {
            पक्ष 1:
                RLESKIP(1, Uint8);
                भङ्ग;
            पक्ष 2:
                RLESKIP(2, Uint8);
                भङ्ग;
            पक्ष 3:
                RLESKIP(3, Uint8);
                भङ्ग;
            पक्ष 4:
                RLESKIP(4, Uint16);
                भङ्ग;
            }

#अपरिभाषय RLESKIP
        }
    }

    alpha = surf_src->map.info.a;
    // if left or right edge clipping needed, call clip blit
    यदि (srcrect->x || srcrect->w != surf_src->w) {
        RLEClipBlit(w, srcbuf, surf_dst, dstbuf, srcrect, alpha);
    } अन्यथा {
        ध्रुव SDL_PixelFormatDetails *fmt = surf_src->fmt;

#परिभाषय RLEBLIT(bpp, Type, do_blit)                                   \
    कुरु {                                                              \
        पूर्णाङ्क linecount = srcrect->h;                                   \
        पूर्णाङ्क ofs = 0;                                                  \
        प्रति (;;) {                                                    \
            अचिह्नित सततम्;                                             \
            ofs += *(Type *)srcbuf;                                   \
            सततम् = ((Type *)srcbuf)[1];                                \
            srcbuf += 2 * परिमाण(Type);                               \
            यदि (सततम्) {                                                \
                do_blit(dstbuf + ofs * bpp, srcbuf, सततम्, bpp, alpha); \
                srcbuf += सततम् * bpp;                                  \
                ofs += सततम्;                                           \
            } अन्यथा यदि (!ofs)                                          \
                भङ्ग;                                                \
            यदि (ofs == w) {                                           \
                ofs = 0;                                              \
                dstbuf += surf_dst->pitch;                            \
                यदि (!--linecount)                                     \
                    भङ्ग;                                            \
            }                                                         \
        }                                                             \
    } यावत् (0)

        वृणु_BLIT(RLEBLIT, alpha, fmt);

#अपरिभाषय RLEBLIT
    }

समाप्तम्:
    // Unlock the destination if necessary
    यदि (SDL_MUSTLOCK(surf_dst)) {
        SDL_UnlockSurface(surf_dst);
    }
    प्रत्यागम true;
}

#अपरिभाषय OPAQUE_BLIT

/*
 * Per-pixel blitting macros for translucent pixels:
 * These use the same techniques as the per-surface blitting macros
 */

/*
 * For 32bpp pixels, we have made sure the alpha is stored in the top
 * 8 bits, so proceed as usual
 */
#परिभाषय BLIT_TRANSL_888(src, dst)                        \
    कुरु {                                                 \
        Uint32 s = src;                                  \
        Uint32 d = dst;                                  \
        अचिह्नित alpha = s >> 24;                        \
        Uint32 s1 = s & 0xff00ff;                        \
        Uint32 d1 = d & 0xff00ff;                        \
        d1 = (d1 + ((s1 - d1) * alpha >> 8)) & 0xff00ff; \
        s &= 0xff00;                                     \
        d &= 0xff00;                                     \
        d = (d + ((s - d) * alpha >> 8)) & 0xff00;       \
        dst = d1 | d | 0xff000000;                       \
    } यावत् (0)

/*
 * For 16bpp pixels, we have stored the 5 most significant alpha bits in
 * bits 5-10. As before, we can process all 3 RGB components at the same time.
 */
#परिभाषय BLIT_TRANSL_565(src, dst)          \
    कुरु {                                   \
        Uint32 s = src;                    \
        Uint32 d = dst;                    \
        अचिह्नित alpha = (s & 0x3e0) >> 5; \
        s &= 0x07e0f81f;                   \
        d = (d | d << 16) & 0x07e0f81f;    \
        d += (s - d) * alpha >> 5;         \
        d &= 0x07e0f81f;                   \
        dst = (Uint16)(d | d >> 16);       \
    } यावत् (0)

#परिभाषय BLIT_TRANSL_555(src, dst)          \
    कुरु {                                   \
        Uint32 s = src;                    \
        Uint32 d = dst;                    \
        अचिह्नित alpha = (s & 0x3e0) >> 5; \
        s &= 0x03e07c1f;                   \
        d = (d | d << 16) & 0x03e07c1f;    \
        d += (s - d) * alpha >> 5;         \
        d &= 0x03e07c1f;                   \
        dst = (Uint16)(d | d >> 16);       \
    } यावत् (0)

// blit a pixel-alpha RLE surface clipped at the right and/or left edges
स्थिर शून्य RLEAlphaClipBlit(पूर्णाङ्क w, Uint8 *srcbuf, SDL_Surface *surf_dst,
                             Uint8 *dstbuf, ध्रुव SDL_Rect *srcrect)
{
    ध्रुव SDL_PixelFormatDetails *df = surf_dst->fmt;
    /*
     * clipped blitter: Ptype is the destination pixel type,
     * Ctype the translucent count type, and do_blend the macro
     * to blend one pixel.
     */
#परिभाषय RLEALPHACLIPBLIT(Ptype, Ctype, do_blend)                          \
    कुरु {                                                                  \
        पूर्णाङ्क linecount = srcrect->h;                                       \
        पूर्णाङ्क वामः = srcrect->x;                                            \
        पूर्णाङ्क दक्षिणः = वामः + srcrect->w;                                    \
        dstbuf -= वामः * परिमाण(Ptype);                                   \
        कुरु {                                                              \
            पूर्णाङ्क ofs = 0;                                                  \
            /* blit opaque pixels on one line */                          \
            कुरु {                                                          \
                अचिह्नित सततम्;                                             \
                ofs += ((Ctype *)srcbuf)[0];                              \
                सततम् = ((Ctype *)srcbuf)[1];                               \
                srcbuf += 2 * परिमाण(Ctype);                              \
                यदि (सततम्) {                                                \
                    /* clip to left and right borders */                  \
                    पूर्णाङ्क cofs = ofs;                                       \
                    पूर्णाङ्क crun = सततम्;                                       \
                    यदि (वामः - cofs > 0) {                                \
                        crun -= वामः - cofs;                              \
                        cofs = वामः;                                      \
                    }                                                     \
                    यदि (crun > दक्षिणः - cofs)                              \
                        crun = दक्षिणः - cofs;                              \
                    यदि (crun > 0)                                         \
                        PIXEL_COPY(dstbuf + cofs * परिमाण(Ptype),         \
                                   srcbuf + (cofs - ofs) * परिमाण(Ptype), \
                                   (अचिह्नित)crun, परिमाण(Ptype));        \
                    srcbuf += सततम् * परिमाण(Ptype);                        \
                    ofs += सततम्;                                           \
                } अन्यथा यदि (!ofs)                                          \
                    प्रत्यागम;                                               \
            } यावत् (ofs < w);                                            \
            /* skip padding if necessary */                               \
            ध्रुव size_t psize = परिमाण(Ptype);                           \
            यदि (psize == 2)                                               \
                srcbuf += (uintptr_t)srcbuf & 2;                          \
            /* blit translucent pixels on the same line */                \
            ofs = 0;                                                      \
            कुरु {                                                          \
                अचिह्नित सततम्;                                             \
                ofs += ((Uint16 *)srcbuf)[0];                             \
                सततम् = ((Uint16 *)srcbuf)[1];                              \
                srcbuf += 4;                                              \
                यदि (सततम्) {                                                \
                    /* clip to left and right borders */                  \
                    पूर्णाङ्क cofs = ofs;                                       \
                    पूर्णाङ्क crun = सततम्;                                       \
                    यदि (वामः - cofs > 0) {                                \
                        crun -= वामः - cofs;                              \
                        cofs = वामः;                                      \
                    }                                                     \
                    यदि (crun > दक्षिणः - cofs)                              \
                        crun = दक्षिणः - cofs;                              \
                    यदि (crun > 0) {                                       \
                        Ptype *dst = (Ptype *)dstbuf + cofs;              \
                        Uint32 *src = (Uint32 *)srcbuf + (cofs - ofs);    \
                        पूर्णाङ्क i;                                            \
                        प्रति (i = 0; i < crun; i++)                        \
                            do_blend(src[i], dst[i]);                     \
                    }                                                     \
                    srcbuf += सततम् * 4;                                    \
                    ofs += सततम्;                                           \
                }                                                         \
            } यावत् (ofs < w);                                            \
            dstbuf += surf_dst->pitch;                                    \
        } यावत् (--linecount);                                            \
    } यावत् (0)

    विकल्प (df->अष्टकानि_प्रत्येकम्_pixel) {
    पक्ष 2:
        यदि (df->Gmask == 0x07e0 || df->Rmask == 0x07e0 || df->Bmask == 0x07e0) {
            RLEALPHACLIPBLIT(Uint16, Uint8, BLIT_TRANSL_565);
        } अन्यथा {
            RLEALPHACLIPBLIT(Uint16, Uint8, BLIT_TRANSL_555);
        }
        भङ्ग;
    पक्ष 4:
        RLEALPHACLIPBLIT(Uint32, Uint16, BLIT_TRANSL_888);
        भङ्ग;
    }
}

// blit a pixel-alpha RLE surface
स्थिर bool SDLCALL SDL_RLEAlphaBlit(SDL_Surface *surf_src, ध्रुव SDL_Rect *srcrect,
                                     SDL_Surface *surf_dst, ध्रुव SDL_Rect *dstrect)
{
    पूर्णाङ्क x, y;
    पूर्णाङ्क w = surf_src->w;
    Uint8 *srcbuf, *dstbuf;
    ध्रुव SDL_PixelFormatDetails *df = surf_dst->fmt;

    // Lock the destination if necessary
    यदि (SDL_MUSTLOCK(surf_dst)) {
        यदि (!SDL_तालकम्_Surface(surf_dst)) {
            प्रत्यागम false;
        }
    }

    x = dstrect->x;
    y = dstrect->y;
    dstbuf = (Uint8 *)surf_dst->pixels + y * surf_dst->pitch + x * df->अष्टकानि_प्रत्येकम्_pixel;
    srcbuf = (Uint8 *)surf_src->map.दत्त + परिमाण(SDL_PixelFormat);

    {
        // skip lines at the top if necessary
        पूर्णाङ्क vskip = srcrect->y;
        यदि (vskip) {
            पूर्णाङ्क ofs;
            यदि (df->अष्टकानि_प्रत्येकम्_pixel == 2) {
                // the 16/32 interleaved format
                कुरु {
                    // skip opaque line
                    ofs = 0;
                    कुरु {
                        पूर्णाङ्क सततम्;
                        ofs += srcbuf[0];
                        सततम् = srcbuf[1];
                        srcbuf += 2;
                        यदि (सततम्) {
                            srcbuf += 2 * सततम्;
                            ofs += सततम्;
                        } अन्यथा यदि (ofs == 0) {
                            गच्छ समाप्तम्;
                        }
                    } यावत् (ofs < w);

                    // skip padding
                    srcbuf += (uintptr_t)srcbuf & 2;

                    // skip translucent line
                    ofs = 0;
                    कुरु {
                        पूर्णाङ्क सततम्;
                        ofs += ((Uint16 *)srcbuf)[0];
                        सततम् = ((Uint16 *)srcbuf)[1];
                        srcbuf += 4 * (सततम् + 1);
                        ofs += सततम्;
                    } यावत् (ofs < w);
                } यावत् (--vskip);
            } अन्यथा {
                // the 32/32 interleaved format
                vskip <<= 1; // opaque and translucent have same format
                कुरु {
                    ofs = 0;
                    कुरु {
                        पूर्णाङ्क सततम्;
                        ofs += ((Uint16 *)srcbuf)[0];
                        सततम् = ((Uint16 *)srcbuf)[1];
                        srcbuf += 4;
                        यदि (सततम्) {
                            srcbuf += 4 * सततम्;
                            ofs += सततम्;
                        } अन्यथा यदि (ofs == 0) {
                            गच्छ समाप्तम्;
                        }
                    } यावत् (ofs < w);
                } यावत् (--vskip);
            }
        }
    }

    // if left or right edge clipping needed, call clip blit
    यदि (srcrect->x || srcrect->w != surf_src->w) {
        RLEAlphaClipBlit(w, srcbuf, surf_dst, dstbuf, srcrect);
    } अन्यथा {

        /*
         * non-clipped blitter. Ptype is the destination pixel type,
         * Ctype the translucent count type, and do_blend the
         * macro to blend one pixel.
         */
#परिभाषय RLEALPHABLIT(Ptype, Ctype, do_blend)                         \
    कुरु {                                                             \
        पूर्णाङ्क linecount = srcrect->h;                                  \
        कुरु {                                                         \
            पूर्णाङ्क ofs = 0;                                             \
            /* blit opaque pixels on one line */                     \
            कुरु {                                                     \
                अचिह्नित सततम्;                                        \
                ofs += ((Ctype *)srcbuf)[0];                         \
                सततम् = ((Ctype *)srcbuf)[1];                          \
                srcbuf += 2 * परिमाण(Ctype);                         \
                यदि (सततम्) {                                           \
                    PIXEL_COPY(dstbuf + ofs * परिमाण(Ptype), srcbuf, \
                               सततम्, परिमाण(Ptype));                  \
                    srcbuf += सततम् * परिमाण(Ptype);                   \
                    ofs += सततम्;                                      \
                } अन्यथा यदि (!ofs)                                     \
                    गच्छ समाप्तम्;                                       \
            } यावत् (ofs < w);                                       \
            /* skip padding if necessary */                          \
            ध्रुव size_t psize = परिमाण(Ptype);                      \
            यदि (psize == 2)                                          \
                srcbuf += (uintptr_t)srcbuf & 2;                     \
            /* blit translucent pixels on the same line */           \
            ofs = 0;                                                 \
            कुरु {                                                     \
                अचिह्नित सततम्;                                        \
                ofs += ((Uint16 *)srcbuf)[0];                        \
                सततम् = ((Uint16 *)srcbuf)[1];                         \
                srcbuf += 4;                                         \
                यदि (सततम्) {                                           \
                    Ptype *dst = (Ptype *)dstbuf + ofs;              \
                    अचिह्नित i;                                      \
                    प्रति (i = 0; i < सततम्; i++) {                      \
                        Uint32 src = *(Uint32 *)srcbuf;              \
                        do_blend(src, *dst);                         \
                        srcbuf += 4;                                 \
                        dst++;                                       \
                    }                                                \
                    ofs += सततम्;                                      \
                }                                                    \
            } यावत् (ofs < w);                                       \
            dstbuf += surf_dst->pitch;                               \
        } यावत् (--linecount);                                       \
    } यावत् (0)

        विकल्प (df->अष्टकानि_प्रत्येकम्_pixel) {
        पक्ष 2:
            यदि (df->Gmask == 0x07e0 || df->Rmask == 0x07e0 || df->Bmask == 0x07e0) {
                RLEALPHABLIT(Uint16, Uint8, BLIT_TRANSL_565);
            } अन्यथा {
                RLEALPHABLIT(Uint16, Uint8, BLIT_TRANSL_555);
            }
            भङ्ग;
        पक्ष 4:
            RLEALPHABLIT(Uint32, Uint16, BLIT_TRANSL_888);
            भङ्ग;
        }
    }

समाप्तम्:
    // Unlock the destination if necessary
    यदि (SDL_MUSTLOCK(surf_dst)) {
        SDL_UnlockSurface(surf_dst);
    }
    प्रत्यागम true;
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
स्थिर पूर्णाङ्क copy_opaque_16(शून्य *dst, ध्रुव Uint32 *src, पूर्णाङ्क n,
                          ध्रुव SDL_PixelFormatDetails *sfmt, ध्रुव SDL_PixelFormatDetails *dfmt)
{
    पूर्णाङ्क i;
    Uint16 *d = (Uint16 *)dst;
    प्रति (i = 0; i < n; i++) {
        अचिह्नित r, g, b;
        RGB_FROM_PIXEL(*src, sfmt, r, g, b);
        PIXEL_FROM_RGB(*d, dfmt, r, g, b);
        src++;
        d++;
    }
    प्रत्यागम n * 2;
}

// encode 32bpp rgb + a into 32bpp G0RAB format for blitting into 565
स्थिर पूर्णाङ्क copy_transl_565(शून्य *dst, ध्रुव Uint32 *src, पूर्णाङ्क n,
                           ध्रुव SDL_PixelFormatDetails *sfmt, ध्रुव SDL_PixelFormatDetails *dfmt)
{
    पूर्णाङ्क i;
    Uint32 *d = (Uint32 *)dst;
    प्रति (i = 0; i < n; i++) {
        अचिह्नित r, g, b, a;
        Uint16 pix;
        RGBA_FROM_8888(*src, sfmt, r, g, b, a);
        PIXEL_FROM_RGB(pix, dfmt, r, g, b);
        *d = ((pix & 0x7e0) << 16) | (pix & 0xf81f) | ((a << 2) & 0x7e0);
        src++;
        d++;
    }
    प्रत्यागम n * 4;
}

// encode 32bpp rgb + a into 32bpp G0RAB format for blitting into 555
स्थिर पूर्णाङ्क copy_transl_555(शून्य *dst, ध्रुव Uint32 *src, पूर्णाङ्क n,
                           ध्रुव SDL_PixelFormatDetails *sfmt, ध्रुव SDL_PixelFormatDetails *dfmt)
{
    पूर्णाङ्क i;
    Uint32 *d = (Uint32 *)dst;
    प्रति (i = 0; i < n; i++) {
        अचिह्नित r, g, b, a;
        Uint16 pix;
        RGBA_FROM_8888(*src, sfmt, r, g, b, a);
        PIXEL_FROM_RGB(pix, dfmt, r, g, b);
        *d = ((pix & 0x3e0) << 16) | (pix & 0xfc1f) | ((a << 2) & 0x3e0);
        src++;
        d++;
    }
    प्रत्यागम n * 4;
}

// encode 32bpp rgba into 32bpp rgba, keeping alpha (dual purpose)
स्थिर पूर्णाङ्क copy_32(शून्य *dst, ध्रुव Uint32 *src, पूर्णाङ्क n,
                   ध्रुव SDL_PixelFormatDetails *sfmt, ध्रुव SDL_PixelFormatDetails *dfmt)
{
    पूर्णाङ्क i;
    Uint32 *d = (Uint32 *)dst;
    प्रति (i = 0; i < n; i++) {
        अचिह्नित r, g, b, a;
        RGBA_FROM_8888(*src, sfmt, r, g, b, a);
        RLEPIXEL_FROM_RGBA(*d, dfmt, r, g, b, a);
        d++;
        src++;
    }
    प्रत्यागम n * 4;
}

#परिभाषय ISOPAQUE(pixel, fmt) ((((pixel)&fmt->Amask) >> fmt->Ashift) == 255)

#परिभाषय ISTRANSL(pixel, fmt) \
    ((अचिह्नित)((((pixel)&fmt->Amask) >> fmt->Ashift) - 1U) < 254U)

// convert surface to be quickly alpha-blittable onto dest, if possible
स्थिर bool RLEAlphaSurface(SDL_Surface *surface)
{
    SDL_Surface *dest;
    ध्रुव SDL_PixelFormatDetails *df;
    पूर्णाङ्क maxsize = 0;
    पूर्णाङ्क max_opaque_सततम्;
    पूर्णाङ्क max_transl_सततम् = 65535;
    अचिह्नित masksum;
    Uint8 *rlebuf, *dst;
    पूर्णाङ्क (*copy_opaque)(शून्य *, ध्रुव Uint32 *, पूर्णाङ्क,
                       ध्रुव SDL_PixelFormatDetails *, ध्रुव SDL_PixelFormatDetails *);
    पूर्णाङ्क (*copy_transl)(शून्य *, ध्रुव Uint32 *, पूर्णाङ्क,
                       ध्रुव SDL_PixelFormatDetails *, ध्रुव SDL_PixelFormatDetails *);

    dest = surface->map.info.dst_surface;
    यदि (!dest) {
        प्रत्यागम false;
    }
    df = dest->fmt;
    यदि (surface->fmt->द्वयङ्काः_प्रत्येकम्_pixel != 32) {
        प्रत्यागम false; // only 32bpp source supported
    }

    /* find out whether the destination is one we support,
       and determine the max size of the encoded result */
    masksum = df->Rmask | df->Gmask | df->Bmask;
    विकल्प (df->अष्टकानि_प्रत्येकम्_pixel) {
    पक्ष 2:
        // 16bpp: only support 565 and 555 formats
        विकल्प (masksum) {
        पक्ष 0xffff:
            यदि (df->Gmask == 0x07e0 || df->Rmask == 0x07e0 || df->Bmask == 0x07e0) {
                copy_opaque = copy_opaque_16;
                copy_transl = copy_transl_565;
            } अन्यथा {
                प्रत्यागम false;
            }
            भङ्ग;
        पक्ष 0x7fff:
            यदि (df->Gmask == 0x03e0 || df->Rmask == 0x03e0 || df->Bmask == 0x03e0) {
                copy_opaque = copy_opaque_16;
                copy_transl = copy_transl_555;
            } अन्यथा {
                प्रत्यागम false;
            }
            भङ्ग;
        स्वभाव:
            प्रत्यागम false;
        }
        max_opaque_सततम् = 255; // runs stored as bytes

        /* worst case is alternating opaque and translucent pixels,
           with room for alignment padding between lines */
        maxsize = surface->h * (2 + (4 + 2) * (surface->w + 1)) + 2;
        भङ्ग;
    पक्ष 4:
        यदि (masksum != 0x00ffffff) {
            प्रत्यागम false; // requires unused high byte
        }
        copy_opaque = copy_32;
        copy_transl = copy_32;
        max_opaque_सततम् = 255; // runs stored as short ints

        // worst case is alternating opaque and translucent pixels
        maxsize = surface->h * 2 * 4 * (surface->w + 1) + 4;
        भङ्ग;
    स्वभाव:
        प्रत्यागम false; // anything else unsupported right now
    }

    maxsize += परिमाण(SDL_PixelFormat);
    rlebuf = (Uint8 *)SDL_malloc(maxsize);
    यदि (!rlebuf) {
        प्रत्यागम false;
    }
    // save the destination format so we can undo the encoding later
    *(SDL_PixelFormat *)rlebuf = dest->format;
    dst = rlebuf + परिमाण(SDL_PixelFormat);

    // Do the actual encoding
    {
        पूर्णाङ्क x, y;
        पूर्णाङ्क h = surface->h, w = surface->w;
        ध्रुव SDL_PixelFormatDetails *sf = surface->fmt;
        Uint32 *src = (Uint32 *)surface->pixels;
        Uint8 *lastline = dst; // end of last non-blank line

        // opaque counts are 8 or 16 bits, depending on target depth
#परिभाषय सङ्कलय_OPAQUE_COUNTS(n, m)           \
    यदि (df->अष्टकानि_प्रत्येकम्_pixel == 4) {         \
        ((Uint16 *)dst)[0] = (Uint16)n;   \
        ((Uint16 *)dst)[1] = (Uint16)m;   \
        dst += 4;                         \
    } अन्यथा {                              \
        dst[0] = (Uint8)n;                \
        dst[1] = (Uint8)m;                \
        dst += 2;                         \
    }

        // translucent counts are always 16 bit
#परिभाषय सङ्कलय_TRANSL_COUNTS(n, m) \
    (((Uint16 *)dst)[0] = (Uint16)n, ((Uint16 *)dst)[1] = (Uint16)m, dst += 4)

        प्रति (y = 0; y < h; y++) {
            पूर्णाङ्क runstart, skipstart;
            पूर्णाङ्क blankline = 0;
            // First encode all opaque pixels of a scan line
            x = 0;
            कुरु {
                पूर्णाङ्क सततम्, skip, len;
                skipstart = x;
                यावत् (x < w && !ISOPAQUE(src[x], sf)) {
                    x++;
                }
                runstart = x;
                यावत् (x < w && ISOPAQUE(src[x], sf)) {
                    x++;
                }
                skip = runstart - skipstart;
                यदि (skip == w) {
                    blankline = 1;
                }
                सततम् = x - runstart;
                यावत् (skip > max_opaque_सततम्) {
                    सङ्कलय_OPAQUE_COUNTS(max_opaque_सततम्, 0);
                    skip -= max_opaque_सततम्;
                }
                len = SDL_min(सततम्, max_opaque_सततम्);
                सङ्कलय_OPAQUE_COUNTS(skip, len);
                dst += copy_opaque(dst, src + runstart, len, sf, df);
                runstart += len;
                सततम् -= len;
                यावत् (सततम्) {
                    len = SDL_min(सततम्, max_opaque_सततम्);
                    सङ्कलय_OPAQUE_COUNTS(0, len);
                    dst += copy_opaque(dst, src + runstart, len, sf, df);
                    runstart += len;
                    सततम् -= len;
                }
            } यावत् (x < w);

            // Make sure the next output address is 32-bit aligned
            dst += (uintptr_t)dst & 2;

            // Next, encode all translucent pixels of the same scan line
            x = 0;
            कुरु {
                पूर्णाङ्क सततम्, skip, len;
                skipstart = x;
                यावत् (x < w && !ISTRANSL(src[x], sf)) {
                    x++;
                }
                runstart = x;
                यावत् (x < w && ISTRANSL(src[x], sf)) {
                    x++;
                }
                skip = runstart - skipstart;
                blankline &= (skip == w);
                सततम् = x - runstart;
                यावत् (skip > max_transl_सततम्) {
                    सङ्कलय_TRANSL_COUNTS(max_transl_सततम्, 0);
                    skip -= max_transl_सततम्;
                }
                len = SDL_min(सततम्, max_transl_सततम्);
                सङ्कलय_TRANSL_COUNTS(skip, len);
                dst += copy_transl(dst, src + runstart, len, sf, df);
                runstart += len;
                सततम् -= len;
                यावत् (सततम्) {
                    len = SDL_min(सततम्, max_transl_सततम्);
                    सङ्कलय_TRANSL_COUNTS(0, len);
                    dst += copy_transl(dst, src + runstart, len, sf, df);
                    runstart += len;
                    सततम् -= len;
                }
                यदि (!blankline) {
                    lastline = dst;
                }
            } यावत् (x < w);

            src += surface->pitch >> 2;
        }
        dst = lastline; // back up past trailing blank lines
        सङ्कलय_OPAQUE_COUNTS(0, 0);
    }

#अपरिभाषय सङ्कलय_OPAQUE_COUNTS
#अपरिभाषय सङ्कलय_TRANSL_COUNTS

    // reallocate the buffer to release unused memory
    {
        Uint8 *p = (Uint8 *)SDL_realloc(rlebuf, dst - rlebuf);
        यदि (!p) {
            p = rlebuf;
        }
        surface->map.दत्त = p;
    }

    प्रत्यागम true;
}

स्थिर Uint32 getpix_8(ध्रुव Uint8 *srcbuf)
{
    प्रत्यागम *srcbuf;
}

स्थिर Uint32 getpix_16(ध्रुव Uint8 *srcbuf)
{
    प्रत्यागम *(ध्रुव Uint16 *)srcbuf;
}

स्थिर Uint32 getpix_24(ध्रुव Uint8 *srcbuf)
{
#यदि SDL_BYTEORDER == SDL_LIL_ENDIAN
    प्रत्यागम srcbuf[0] + (srcbuf[1] << 8) + (srcbuf[2] << 16);
#अन्यथा
    प्रत्यागम (srcbuf[0] << 16) + (srcbuf[1] << 8) + srcbuf[2];
#यदि_अन्तः
}

स्थिर Uint32 getpix_32(ध्रुव Uint8 *srcbuf)
{
    प्रत्यागम *(ध्रुव Uint32 *)srcbuf;
}

प्रकारनिर्देश Uint32 (*getpix_func)(ध्रुव Uint8 *);

स्थिर ध्रुव getpix_func getpixes[4] = {
    getpix_8, getpix_16, getpix_24, getpix_32
};

स्थिर bool RLEColorkeySurface(SDL_Surface *surface)
{
    SDL_Surface *dest;
    Uint8 *rlebuf, *dst;
    पूर्णाङ्क maxn;
    पूर्णाङ्क y;
    Uint8 *srcbuf, *lastline;
    पूर्णाङ्क maxsize = 0;
    ध्रुव पूर्णाङ्क bpp = surface->fmt->अष्टकानि_प्रत्येकम्_pixel;
    getpix_func getpix;
    Uint32 ckey, rgbmask;
    पूर्णाङ्क w, h;

    dest = surface->map.info.dst_surface;
    यदि (!dest) {
        प्रत्यागम false;
    }

    // calculate the worst case size for the compressed surface
    विकल्प (bpp) {
    पक्ष 1:
        /* worst case is alternating opaque and transparent pixels,
           starting with an opaque pixel */
        maxsize = surface->h * 3 * (surface->w / 2 + 1) + 2;
        भङ्ग;
    पक्ष 2:
    पक्ष 3:
        // worst case is solid runs, at most 255 pixels wide
        maxsize = surface->h * (2 * (surface->w / 255 + 1) + surface->w * bpp) + 2;
        भङ्ग;
    पक्ष 4:
        // worst case is solid runs, at most 65535 pixels wide
        maxsize = surface->h * (4 * (surface->w / 65535 + 1) + surface->w * 4) + 4;
        भङ्ग;

    स्वभाव:
        प्रत्यागम false;
    }

    maxsize += परिमाण(SDL_PixelFormat);
    rlebuf = (Uint8 *)SDL_malloc(maxsize);
    यदि (!rlebuf) {
        प्रत्यागम false;
    }
    // save the destination format so we can undo the encoding later
    *(SDL_PixelFormat *)rlebuf = dest->format;

    // Set up the conversion
    srcbuf = (Uint8 *)surface->pixels;
    maxn = bpp == 4 ? 65535 : 255;
    dst = rlebuf + परिमाण(SDL_PixelFormat);
    rgbmask = ~surface->fmt->Amask;
    ckey = surface->map.info.colorkey & rgbmask;
    lastline = dst;
    getpix = getpixes[bpp - 1];
    w = surface->w;
    h = surface->h;

#परिभाषय सङ्कलय_COUNTS(n, m)                \
    यदि (bpp == 4) {                     \
        ((Uint16 *)dst)[0] = (Uint16)n; \
        ((Uint16 *)dst)[1] = (Uint16)m; \
        dst += 4;                       \
    } अन्यथा {                            \
        dst[0] = (Uint8)n;              \
        dst[1] = (Uint8)m;              \
        dst += 2;                       \
    }

    प्रति (y = 0; y < h; y++) {
        पूर्णाङ्क x = 0;
        पूर्णाङ्क blankline = 0;
        कुरु {
            पूर्णाङ्क सततम्, skip;
            पूर्णाङ्क len;
            पूर्णाङ्क runstart;
            पूर्णाङ्क skipstart = x;

            // find run of transparent, then opaque pixels
            यावत् (x < w && (getpix(srcbuf + x * bpp) & rgbmask) == ckey) {
                x++;
            }
            runstart = x;
            यावत् (x < w && (getpix(srcbuf + x * bpp) & rgbmask) != ckey) {
                x++;
            }
            skip = runstart - skipstart;
            यदि (skip == w) {
                blankline = 1;
            }
            सततम् = x - runstart;

            // encode segment
            यावत् (skip > maxn) {
                सङ्कलय_COUNTS(maxn, 0);
                skip -= maxn;
            }
            len = SDL_min(सततम्, maxn);
            सङ्कलय_COUNTS(skip, len);
            SDL_memcpy(dst, srcbuf + runstart * bpp, (size_t)len * bpp);
            dst += len * bpp;
            सततम् -= len;
            runstart += len;
            यावत् (सततम्) {
                len = SDL_min(सततम्, maxn);
                सङ्कलय_COUNTS(0, len);
                SDL_memcpy(dst, srcbuf + runstart * bpp, (size_t)len * bpp);
                dst += len * bpp;
                runstart += len;
                सततम् -= len;
            }
            यदि (!blankline) {
                lastline = dst;
            }
        } यावत् (x < w);

        srcbuf += surface->pitch;
    }
    dst = lastline; // back up bast trailing blank lines
    सङ्कलय_COUNTS(0, 0);

#अपरिभाषय सङ्कलय_COUNTS

    // reallocate the buffer to release unused memory
    {
        // If SDL_realloc returns NULL, the original block is left intact
        Uint8 *p = (Uint8 *)SDL_realloc(rlebuf, dst - rlebuf);
        यदि (!p) {
            p = rlebuf;
        }
        surface->map.दत्त = p;
    }

    प्रत्यागम true;
}

bool SDL_RLESurface(SDL_Surface *surface)
{
    पूर्णाङ्क flags;

    // Clear any previous RLE conversion
    यदि (surface->आन्तरिकम्_flags & SDL_आन्तरिकम्_SURFACE_RLEACCEL) {
        SDL_UnRLESurface(surface);
    }

    // We don't support RLE encoding of bitmaps
    यदि (SDL_BITSPERPIXEL(surface->format) < 8) {
        प्रत्यागम false;
    }

    // Make sure the pixels are available
    यदि (!surface->pixels) {
        प्रत्यागम false;
    }

    flags = surface->map.info.flags;
    यदि (flags & SDL_COPY_COLORKEY) {
        // ok
    } अन्यथा यदि ((flags & SDL_COPY_BLEND) && SDL_ISPIXELFORMAT_ALPHA(surface->format)) {
        // ok
    } अन्यथा {
        // If we don't have colorkey or blending, nothing to do...
        प्रत्यागम false;
    }

    // Pass on combinations not supported
    यदि ((flags & SDL_COPY_MODULATE_COLOR) ||
        ((flags & SDL_COPY_MODULATE_ALPHA) && SDL_ISPIXELFORMAT_ALPHA(surface->format)) ||
        (flags & (SDL_COPY_BLEND_PREMULTIPLIED | SDL_COPY_सङ्कलय | SDL_COPY_सङ्कलय_PREMULTIPLIED | SDL_COPY_MOD | SDL_COPY_MUL)) ||
        (flags & SDL_COPY_निकटतमः)) {
        प्रत्यागम false;
    }

    // Encode and set up the blit
    यदि (!SDL_ISPIXELFORMAT_ALPHA(surface->format) || !(flags & SDL_COPY_BLEND)) {
        यदि (!surface->map.तटस्थः) {
            प्रत्यागम false;
        }
        यदि (!RLEColorkeySurface(surface)) {
            प्रत्यागम false;
        }
        surface->map.blit = SDL_RLEBlit;
        surface->map.info.flags |= SDL_COPY_RLE_COLORKEY;
    } अन्यथा {
        यदि (!RLEAlphaSurface(surface)) {
            प्रत्यागम false;
        }
        surface->map.blit = SDL_RLEAlphaBlit;
        surface->map.info.flags |= SDL_COPY_RLE_ALPHAKEY;
    }

    यदि (!(surface->flags & SDL_SURFACE_PREALLOCATED)) {
        surface->saved_pixels = surface->pixels;
        surface->pixels = रिक्त;
    }

    // The surface is now accelerated
    surface->आन्तरिकम्_flags |= SDL_आन्तरिकम्_SURFACE_RLEACCEL;
    SDL_Update_Surface_तालकम्_Flag(surface);

    प्रत्यागम true;
}

शून्य SDL_UnRLESurface(SDL_Surface *surface)
{
    यदि (surface->आन्तरिकम्_flags & SDL_आन्तरिकम्_SURFACE_RLEACCEL) {
        surface->आन्तरिकम्_flags &= ~SDL_आन्तरिकम्_SURFACE_RLEACCEL;

        surface->map.info.flags &= ~(SDL_COPY_RLE_COLORKEY | SDL_COPY_RLE_ALPHAKEY);

        यदि (!(surface->flags & SDL_SURFACE_PREALLOCATED)) {
            surface->pixels = surface->saved_pixels;
            surface->saved_pixels = रिक्त;
        }

        SDL_free(surface->map.दत्त);
        surface->map.दत्त = रिक्त;

        SDL_InvalidateMap(&surface->map);

        SDL_Update_Surface_तालकम्_Flag(surface);
    }
}

#यदि_अन्तः // SDL_HAVE_RLE
