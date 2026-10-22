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

#నిర్వచితమైతే SDL_HAVE_RLE

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

#అన్తర్భావ "SDL_sysvideo.h"
#అన్తర్భావ "SDL_surface_c.h"
#అన్తర్భావ "SDL_pixels_c.h"
#అన్తర్భావ "SDL_RLEaccel_c.h"

#నిర్వచించు PIXEL_COPY(గమ్యం, from, len, bpp) \
    SDL_memcpy(గమ్యం, from, (size_t)(len) * (bpp))

/*
 * Various colorkey blit methods, for opaque and per-surface alpha
 */

#నిర్వచించు OPAQUE_BLIT(గమ్యం, from, నిడివి, bpp, alpha) \
    PIXEL_COPY(గమ్యం, from, నిడివి, bpp)

/*
 * For 32bpp pixels on the form 0x00rrggbb:
 * If we treat the middle component separately, we can process the two
 * remaining in parallel. This is safe to do because of the gap to the left
 * of each component, so the bits from the multiplication don't collide.
 * This can be used for any RGB permutation of course.
 */
#నిర్వచించు ALPHA_BLIT32_888(గమ్యం, from, నిడివి, bpp, alpha)       \
    చేయి {                                                     \
        పూర్ణాంకం i;                                               \
        Uint32 *src = (Uint32 *)(from);                      \
        Uint32 *dst = (Uint32 *)(గమ్యం);                        \
        కొరకు (i = 0; i < (పూర్ణాంకం)(నిడివి); i++) {                \
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
    } అయితే (0)

/*
 * For 16bpp pixels we can go a step further: put the middle component
 * in the high 16 bits of a 32 bit word, and process all three RGB
 * components at the same time. Since the smallest gap is here just
 * 5 bits, we have to scale alpha down to 5 bits as well.
 */
#నిర్వచించు ALPHA_BLIT16_565(గమ్యం, from, నిడివి, bpp, alpha) \
    చేయి {                                               \
        పూర్ణాంకం i;                                         \
        Uint16 *src = (Uint16 *)(from);                \
        Uint16 *dst = (Uint16 *)(గమ్యం);                  \
        Uint32 ALPHA = alpha >> 3;                     \
        కొరకు (i = 0; i < (పూర్ణాంకం)(నిడివి); i++) {          \
            Uint32 s = *src++;                         \
            Uint32 d = *dst;                           \
            s = (s | s << 16) & 0x07e0f81f;            \
            d = (d | d << 16) & 0x07e0f81f;            \
            d += (s - d) * ALPHA >> 5;                 \
            d &= 0x07e0f81f;                           \
            *dst++ = (Uint16)(d | d >> 16);            \
        }                                              \
    } అయితే (0)

#నిర్వచించు ALPHA_BLIT16_555(గమ్యం, from, నిడివి, bpp, alpha) \
    చేయి {                                               \
        పూర్ణాంకం i;                                         \
        Uint16 *src = (Uint16 *)(from);                \
        Uint16 *dst = (Uint16 *)(గమ్యం);                  \
        Uint32 ALPHA = alpha >> 3;                     \
        కొరకు (i = 0; i < (పూర్ణాంకం)(నిడివి); i++) {          \
            Uint32 s = *src++;                         \
            Uint32 d = *dst;                           \
            s = (s | s << 16) & 0x03e07c1f;            \
            d = (d | d << 16) & 0x03e07c1f;            \
            d += (s - d) * ALPHA >> 5;                 \
            d &= 0x03e07c1f;                           \
            *dst++ = (Uint16)(d | d >> 16);            \
        }                                              \
    } అయితే (0)

/*
 * The general slow catch-all function, for remaining depths and formats
 */
#ఒకవేళ SDL_BYTEORDER == SDL_BIG_ENDIAN
#నిర్వచించు సమితి_RGB24(dst, d)      \
    dst[0] = (Uint8)(d >> 16); \
    dst[1] = (Uint8)(d >> 8);  \
    dst[2] = (Uint8)(d);
#లేకపోతే
#నిర్వచించు సమితి_RGB24(dst, d)      \
    dst[0] = (Uint8)(d);       \
    dst[1] = (Uint8)(d >> 8);  \
    dst[2] = (Uint8)(d >> 16);
#అయితే_ముగింపు
#నిర్వచించు ALPHA_BLIT_ANY(గమ్యం, from, నిడివి, bpp, alpha)             \
    చేయి {                                                         \
        పూర్ణాంకం i;                                                   \
        Uint8 *src = from;                                       \
        Uint8 *dst = గమ్యం;                                         \
        కొరకు (i = 0; i < (పూర్ణాంకం)(నిడివి); i++) {                    \
            Uint32 s = 0, d = 0;                                 \
            గుర్తులేని rs, gs, bs, rd, gd, bd;                     \
            ఎంపిక (bpp) {                                       \
            స్థితి 2:                                              \
                s = *(Uint16 *)src;                              \
                d = *(Uint16 *)dst;                              \
                ఆపు;                                           \
            స్థితి 3:                                              \
                s = GET_RGB24(src);                              \
                d = GET_RGB24(dst);                              \
                ఆపు;                                           \
            స్థితి 4:                                              \
                s = *(Uint32 *)src;                              \
                d = *(Uint32 *)dst;                              \
                ఆపు;                                           \
            }                                                    \
            RGB_FROM_PIXEL(s, fmt, rs, gs, bs);                  \
            RGB_FROM_PIXEL(d, fmt, rd, gd, bd);                  \
            rd += (rs - rd) * alpha >> 8;                        \
            gd += (gs - gd) * alpha >> 8;                        \
            bd += (bs - bd) * alpha >> 8;                        \
            PIXEL_FROM_RGB(d, fmt, rd, gd, bd);                  \
            ఎంపిక (bpp) {                                       \
            స్థితి 2:                                              \
                *(Uint16 *)dst = (Uint16)d;                      \
                ఆపు;                                           \
            స్థితి 3:                                              \
                సమితి_RGB24(dst, d);                               \
                ఆపు;                                           \
            స్థితి 4:                                              \
                *(Uint32 *)dst = d;                              \
                ఆపు;                                           \
            }                                                    \
            src += bpp;                                          \
            dst += bpp;                                          \
        }                                                        \
    } అయితే (0)

/*
 * Special case: 50% alpha (alpha=128)
 * This is treated specially because it can be optimized very well, and
 * since it is good for many cases of semi-translucency.
 * The theory is to do all three components at the same time:
 * First zero the lowest bit of each component, which gives us room to
 * add them. Then shift right and add the sum of the lowest bits.
 */
#నిర్వచించు ALPHA_BLIT32_888_50(గమ్యం, from, నిడివి, bpp, alpha)                                 \
    చేయి {                                                                                  \
        పూర్ణాంకం i;                                                                            \
        Uint32 *src = (Uint32 *)(from);                                                   \
        Uint32 *dst = (Uint32 *)(గమ్యం);                                                     \
        కొరకు (i = 0; i < (పూర్ణాంకం)(నిడివి); i++) {                                             \
            Uint32 s = *src++;                                                            \
            Uint32 d = *dst;                                                              \
            *dst++ = (((s & 0x00fefefe) + (d & 0x00fefefe)) >> 1) + (s & d & 0x00010101); \
        }                                                                                 \
    } అయితే (0)

/*
 * For 16bpp, we can actually blend two pixels in parallel, if we take
 * care to shift before we add, not after.
 */

// helper: blend a single 16 bit pixel at 50%
#నిర్వచించు BLEND16_50(dst, src, ముసుగు)                           \
    చేయి {                                                     \
        Uint32 s = *src++;                                   \
        Uint32 d = *dst;                                     \
        *dst++ = (Uint16)((((s & ముసుగు) + (d & ముసుగు)) >> 1) + \
                          (s & d & (~ముసుగు & 0xffff)));       \
    } అయితే (0)

// basic 16bpp blender. mask is the pixels to keep when adding.
#నిర్వచించు ALPHA_BLIT16_50(గమ్యం, from, నిడివి, bpp, alpha, ముసుగు)                                                                              \
    చేయి {                                                                                                                                 \
        గుర్తులేని n = (నిడివి);                                                                                                           \
        Uint16 *src = (Uint16 *)(from);                                                                                                  \
        Uint16 *dst = (Uint16 *)(గమ్యం);                                                                                                    \
        ఒకవేళ (((uintptr_t)src ^ (uintptr_t)dst) & 3) {                                                                                     \
            /* source and destination not in phase, blit one by one */                                                                   \
            అయితే (n--)                                                                                                                  \
                BLEND16_50(dst, src, ముసుగు);                                                                                              \
        } లేకపోతే {                                                                                                                         \
            ఒకవేళ ((uintptr_t)src & 3) {                                                                                                    \
                /* first odd pixel */                                                                                                    \
                BLEND16_50(dst, src, ముసుగు);                                                                                              \
                n--;                                                                                                                     \
            }                                                                                                                            \
            కొరకు (; n > 1; n -= 2) {                                                                                                      \
                Uint32 s = *(Uint32 *)src;                                                                                               \
                Uint32 d = *(Uint32 *)dst;                                                                                               \
                *(Uint32 *)dst = ((s & (ముసుగు | ముసుగు << 16)) >> 1) + ((d & (ముసుగు | ముసుగు << 16)) >> 1) + (s & d & (~(ముసుగు | ముసుగు << 16))); \
                src += 2;                                                                                                                \
                dst += 2;                                                                                                                \
            }                                                                                                                            \
            ఒకవేళ (n)                                                                                                                       \
                BLEND16_50(dst, src, ముసుగు); /* last odd pixel */                                                                         \
        }                                                                                                                                \
    } అయితే (0)

#నిర్వచించు ALPHA_BLIT16_565_50(గమ్యం, from, నిడివి, bpp, alpha) \
    ALPHA_BLIT16_50(గమ్యం, from, నిడివి, bpp, alpha, 0xf7deU)

#నిర్వచించు ALPHA_BLIT16_555_50(గమ్యం, from, నిడివి, bpp, alpha) \
    ALPHA_BLIT16_50(గమ్యం, from, నిడివి, bpp, alpha, 0xfbdeU)

#నిర్వచించు ఎంచుకో_BLIT(blitter, alpha, fmt)                                                                                                              \
    చేయి {                                                                                                                                              \
        ఒకవేళ (alpha == 255) {                                                                                                                           \
            ఎంపిక (fmt->బైట్లు_చొప్పున_pixel) {                                                                                                             \
            స్థితి 1:                                                                                                                                   \
                blitter(1, Uint8, OPAQUE_BLIT);                                                                                                       \
                ఆపు;                                                                                                                                \
            స్థితి 2:                                                                                                                                   \
                blitter(2, Uint8, OPAQUE_BLIT);                                                                                                       \
                ఆపు;                                                                                                                                \
            స్థితి 3:                                                                                                                                   \
                blitter(3, Uint8, OPAQUE_BLIT);                                                                                                       \
                ఆపు;                                                                                                                                \
            స్థితి 4:                                                                                                                                   \
                blitter(4, Uint16, OPAQUE_BLIT);                                                                                                      \
                ఆపు;                                                                                                                                \
            }                                                                                                                                         \
        } లేకపోతే {                                                                                                                                      \
            ఎంపిక (fmt->బైట్లు_చొప్పున_pixel) {                                                                                                             \
            స్థితి 1:                                                                                                                                   \
                /* No 8bpp alpha blitting */                                                                                                          \
                ఆపు;                                                                                                                                \
                                                                                                                                                      \
            స్థితి 2:                                                                                                                                   \
                ఎంపిక (fmt->Rmask | fmt->Gmask | fmt->Bmask) {                                                                                       \
                స్థితి 0xffff:                                                                                                                          \
                    ఒకవేళ (fmt->Gmask == 0x07e0 || fmt->Rmask == 0x07e0 || fmt->Bmask == 0x07e0) {                                                       \
                        ఒకవేళ (alpha == 128) {                                                                                                           \
                            blitter(2, Uint8, ALPHA_BLIT16_565_50);                                                                                   \
                        } లేకపోతే {                                                                                                                      \
                            blitter(2, Uint8, ALPHA_BLIT16_565);                                                                                      \
                        }                                                                                                                             \
                    } లేకపోతే {                                                                                                                          \
                        వెళ్ళు general16;                                                                                                               \
                    }                                                                                                                                 \
                    ఆపు;                                                                                                                            \
                                                                                                                                                      \
                స్థితి 0x7fff:                                                                                                                          \
                    ఒకవేళ (fmt->Gmask == 0x03e0 || fmt->Rmask == 0x03e0 || fmt->Bmask == 0x03e0) {                                                       \
                        ఒకవేళ (alpha == 128) {                                                                                                           \
                            blitter(2, Uint8, ALPHA_BLIT16_555_50);                                                                                   \
                        } లేకపోతే {                                                                                                                      \
                            blitter(2, Uint8, ALPHA_BLIT16_555);                                                                                      \
                        }                                                                                                                             \
                        ఆపు;                                                                                                                        \
                    } లేకపోతే {                                                                                                                          \
                        వెళ్ళు general16;                                                                                                               \
                    }                                                                                                                                 \
                    ఆపు;                                                                                                                            \
                                                                                                                                                      \
                అప్రమేయ:                                                                                                                              \
                general16:                                                                                                                            \
                    blitter(2, Uint8, ALPHA_BLIT_ANY);                                                                                                \
                }                                                                                                                                     \
                ఆపు;                                                                                                                                \
                                                                                                                                                      \
            స్థితి 3:                                                                                                                                   \
                blitter(3, Uint8, ALPHA_BLIT_ANY);                                                                                                    \
                ఆపు;                                                                                                                                \
                                                                                                                                                      \
            స్థితి 4:                                                                                                                                   \
                ఒకవేళ ((fmt->Rmask | fmt->Gmask | fmt->Bmask) == 0x00ffffff && (fmt->Gmask == 0xff00 || fmt->Rmask == 0xff00 || fmt->Bmask == 0xff00)) { \
                    ఒకవేళ (alpha == 128) {                                                                                                               \
                        blitter(4, Uint16, ALPHA_BLIT32_888_50);                                                                                      \
                    } లేకపోతే {                                                                                                                          \
                        blitter(4, Uint16, ALPHA_BLIT32_888);                                                                                         \
                    }                                                                                                                                 \
                } లేకపోతే {                                                                                                                              \
                    blitter(4, Uint16, ALPHA_BLIT_ANY);                                                                                               \
                }                                                                                                                                     \
                ఆపు;                                                                                                                                \
            }                                                                                                                                         \
        }                                                                                                                                             \
    } అయితే (0)

/*
 * Set a pixel value using the given format, except that the alpha value is
 * placed in the top byte. This is the format used for RLE with alpha.
 */
#నిర్వచించు RLEPIXEL_FROM_RGBA(Pixel, fmt, r, g, b, a)   \
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
#నిర్వచించు RLECLIPBLIT(bpp, Type, do_blit)                                    \
    చేయి {                                                                   \
        పూర్ణాంకం linecount = srcrect->h;                                        \
        పూర్ణాంకం ofs = 0;                                                       \
        పూర్ణాంకం ఎడమ = srcrect->x;                                             \
        పూర్ణాంకం కుడి = ఎడమ + srcrect->w;                                     \
        dstbuf -= ఎడమ * bpp;                                              \
        కొరకు (;;) {                                                         \
            పూర్ణాంకం నిరంతరం;                                                       \
            ofs += *(Type *)srcbuf;                                        \
            నిరంతరం = ((Type *)srcbuf)[1];                                     \
            srcbuf += 2 * పరిమాణం(Type);                                    \
            ఒకవేళ (నిరంతరం) {                                                     \
                /* clip to left and right borders */                       \
                ఒకవేళ (ofs < కుడి) {                                         \
                    పూర్ణాంకం ప్రారంభం = 0;                                         \
                    పూర్ణాంకం len = నిరంతరం;                                         \
                    పూర్ణాంకం startcol;                                          \
                    ఒకవేళ (ఎడమ - ofs > 0) {                                  \
                        ప్రారంభం = ఎడమ - ofs;                                \
                        len -= ప్రారంభం;                                      \
                        ఒకవేళ (len <= 0)                                      \
                            వెళ్ళు nocopy##bpp##do_blit;                     \
                    }                                                      \
                    startcol = ofs + ప్రారంభం;                                \
                    ఒకవేళ (len > కుడి - startcol)                            \
                        len = కుడి - startcol;                            \
                    do_blit(dstbuf + startcol * bpp, srcbuf + ప్రారంభం * bpp, \
                            len, bpp, alpha);                              \
                }                                                          \
                nocopy##bpp##do_blit : srcbuf += నిరంతరం * bpp;                \
                ofs += నిరంతరం;                                                \
            } లేకపోతే ఒకవేళ (!ofs) {                                             \
                ఆపు;                                                     \
            }                                                              \
                                                                           \
            ఒకవేళ (ofs == w) {                                                \
                ofs = 0;                                                   \
                dstbuf += surf_dst->pitch;                                 \
                ఒకవేళ (!--linecount) {                                        \
                    ఆపు;                                                 \
                }                                                          \
            }                                                              \
        }                                                                  \
    } అయితే (0)

స్థిర శూన్య RLEClipBlit(పూర్ణాంకం w, Uint8 *srcbuf, SDL_Surface *surf_dst,
                        Uint8 *dstbuf, స్థిరరాశి SDL_Rect *srcrect, గుర్తులేని alpha)
{
    స్థిరరాశి SDL_PixelFormatDetails *fmt = surf_dst->fmt;

    ఎంచుకో_BLIT(RLECLIPBLIT, alpha, fmt);
}

#నిర్వచనం_రద్దు RLECLIPBLIT

// blit a colorkeyed RLE surface
స్థిర bool SDLCALL SDL_RLEBlit(SDL_Surface *surf_src, స్థిరరాశి SDL_Rect *srcrect,
                                SDL_Surface *surf_dst, స్థిరరాశి SDL_Rect *dstrect)
{
    Uint8 *dstbuf;
    Uint8 *srcbuf;
    పూర్ణాంకం x, y;
    పూర్ణాంకం w = surf_src->w;
    గుర్తులేని alpha;

    // Lock the destination if necessary
    ఒకవేళ (SDL_MUSTLOCK(surf_dst)) {
        ఒకవేళ (!SDL_తాళం_Surface(surf_dst)) {
            తిరిగి false;
        }
    }

    // Set up the source and destination pointers
    x = dstrect->x;
    y = dstrect->y;
    dstbuf = (Uint8 *)surf_dst->pixels + y * surf_dst->pitch + x * surf_src->fmt->బైట్లు_చొప్పున_pixel;
    srcbuf = (Uint8 *)surf_src->map.దత్తాంశం + పరిమాణం(SDL_PixelFormat);

    {
        // skip lines at the top if necessary
        పూర్ణాంకం vskip = srcrect->y;
        పూర్ణాంకం ofs = 0;
        ఒకవేళ (vskip) {

#నిర్వచించు RLESKIP(bpp, Type)          \
    కొరకు (;;) {                      \
        పూర్ణాంకం నిరంతరం;                    \
        ofs += *(Type *)srcbuf;     \
        నిరంతరం = ((Type *)srcbuf)[1];  \
        srcbuf += పరిమాణం(Type) * 2; \
        ఒకవేళ (నిరంతరం) {                  \
            srcbuf += నిరంతరం * bpp;    \
            ofs += నిరంతరం;             \
        } లేకపోతే ఒకవేళ (!ofs)            \
            వెళ్ళు పూర్తి;              \
        ఒకవేళ (ofs == w) {             \
            ofs = 0;                \
            ఒకవేళ (!--vskip)           \
                ఆపు;              \
        }                           \
    }

            ఎంపిక (surf_src->fmt->బైట్లు_చొప్పున_pixel) {
            స్థితి 1:
                RLESKIP(1, Uint8);
                ఆపు;
            స్థితి 2:
                RLESKIP(2, Uint8);
                ఆపు;
            స్థితి 3:
                RLESKIP(3, Uint8);
                ఆపు;
            స్థితి 4:
                RLESKIP(4, Uint16);
                ఆపు;
            }

#నిర్వచనం_రద్దు RLESKIP
        }
    }

    alpha = surf_src->map.info.a;
    // if left or right edge clipping needed, call clip blit
    ఒకవేళ (srcrect->x || srcrect->w != surf_src->w) {
        RLEClipBlit(w, srcbuf, surf_dst, dstbuf, srcrect, alpha);
    } లేకపోతే {
        స్థిరరాశి SDL_PixelFormatDetails *fmt = surf_src->fmt;

#నిర్వచించు RLEBLIT(bpp, Type, do_blit)                                   \
    చేయి {                                                              \
        పూర్ణాంకం linecount = srcrect->h;                                   \
        పూర్ణాంకం ofs = 0;                                                  \
        కొరకు (;;) {                                                    \
            గుర్తులేని నిరంతరం;                                             \
            ofs += *(Type *)srcbuf;                                   \
            నిరంతరం = ((Type *)srcbuf)[1];                                \
            srcbuf += 2 * పరిమాణం(Type);                               \
            ఒకవేళ (నిరంతరం) {                                                \
                do_blit(dstbuf + ofs * bpp, srcbuf, నిరంతరం, bpp, alpha); \
                srcbuf += నిరంతరం * bpp;                                  \
                ofs += నిరంతరం;                                           \
            } లేకపోతే ఒకవేళ (!ofs)                                          \
                ఆపు;                                                \
            ఒకవేళ (ofs == w) {                                           \
                ofs = 0;                                              \
                dstbuf += surf_dst->pitch;                            \
                ఒకవేళ (!--linecount)                                     \
                    ఆపు;                                            \
            }                                                         \
        }                                                             \
    } అయితే (0)

        ఎంచుకో_BLIT(RLEBLIT, alpha, fmt);

#నిర్వచనం_రద్దు RLEBLIT
    }

పూర్తి:
    // Unlock the destination if necessary
    ఒకవేళ (SDL_MUSTLOCK(surf_dst)) {
        SDL_UnlockSurface(surf_dst);
    }
    తిరిగి true;
}

#నిర్వచనం_రద్దు OPAQUE_BLIT

/*
 * Per-pixel blitting macros for translucent pixels:
 * These use the same techniques as the per-surface blitting macros
 */

/*
 * For 32bpp pixels, we have made sure the alpha is stored in the top
 * 8 bits, so proceed as usual
 */
#నిర్వచించు BLIT_TRANSL_888(src, dst)                        \
    చేయి {                                                 \
        Uint32 s = src;                                  \
        Uint32 d = dst;                                  \
        గుర్తులేని alpha = s >> 24;                        \
        Uint32 s1 = s & 0xff00ff;                        \
        Uint32 d1 = d & 0xff00ff;                        \
        d1 = (d1 + ((s1 - d1) * alpha >> 8)) & 0xff00ff; \
        s &= 0xff00;                                     \
        d &= 0xff00;                                     \
        d = (d + ((s - d) * alpha >> 8)) & 0xff00;       \
        dst = d1 | d | 0xff000000;                       \
    } అయితే (0)

/*
 * For 16bpp pixels, we have stored the 5 most significant alpha bits in
 * bits 5-10. As before, we can process all 3 RGB components at the same time.
 */
#నిర్వచించు BLIT_TRANSL_565(src, dst)          \
    చేయి {                                   \
        Uint32 s = src;                    \
        Uint32 d = dst;                    \
        గుర్తులేని alpha = (s & 0x3e0) >> 5; \
        s &= 0x07e0f81f;                   \
        d = (d | d << 16) & 0x07e0f81f;    \
        d += (s - d) * alpha >> 5;         \
        d &= 0x07e0f81f;                   \
        dst = (Uint16)(d | d >> 16);       \
    } అయితే (0)

#నిర్వచించు BLIT_TRANSL_555(src, dst)          \
    చేయి {                                   \
        Uint32 s = src;                    \
        Uint32 d = dst;                    \
        గుర్తులేని alpha = (s & 0x3e0) >> 5; \
        s &= 0x03e07c1f;                   \
        d = (d | d << 16) & 0x03e07c1f;    \
        d += (s - d) * alpha >> 5;         \
        d &= 0x03e07c1f;                   \
        dst = (Uint16)(d | d >> 16);       \
    } అయితే (0)

// blit a pixel-alpha RLE surface clipped at the right and/or left edges
స్థిర శూన్య RLEAlphaClipBlit(పూర్ణాంకం w, Uint8 *srcbuf, SDL_Surface *surf_dst,
                             Uint8 *dstbuf, స్థిరరాశి SDL_Rect *srcrect)
{
    స్థిరరాశి SDL_PixelFormatDetails *df = surf_dst->fmt;
    /*
     * clipped blitter: Ptype is the destination pixel type,
     * Ctype the translucent count type, and do_blend the macro
     * to blend one pixel.
     */
#నిర్వచించు RLEALPHACLIPBLIT(Ptype, Ctype, do_blend)                          \
    చేయి {                                                                  \
        పూర్ణాంకం linecount = srcrect->h;                                       \
        పూర్ణాంకం ఎడమ = srcrect->x;                                            \
        పూర్ణాంకం కుడి = ఎడమ + srcrect->w;                                    \
        dstbuf -= ఎడమ * పరిమాణం(Ptype);                                   \
        చేయి {                                                              \
            పూర్ణాంకం ofs = 0;                                                  \
            /* blit opaque pixels on one line */                          \
            చేయి {                                                          \
                గుర్తులేని నిరంతరం;                                             \
                ofs += ((Ctype *)srcbuf)[0];                              \
                నిరంతరం = ((Ctype *)srcbuf)[1];                               \
                srcbuf += 2 * పరిమాణం(Ctype);                              \
                ఒకవేళ (నిరంతరం) {                                                \
                    /* clip to left and right borders */                  \
                    పూర్ణాంకం cofs = ofs;                                       \
                    పూర్ణాంకం crun = నిరంతరం;                                       \
                    ఒకవేళ (ఎడమ - cofs > 0) {                                \
                        crun -= ఎడమ - cofs;                              \
                        cofs = ఎడమ;                                      \
                    }                                                     \
                    ఒకవేళ (crun > కుడి - cofs)                              \
                        crun = కుడి - cofs;                              \
                    ఒకవేళ (crun > 0)                                         \
                        PIXEL_COPY(dstbuf + cofs * పరిమాణం(Ptype),         \
                                   srcbuf + (cofs - ofs) * పరిమాణం(Ptype), \
                                   (గుర్తులేని)crun, పరిమాణం(Ptype));        \
                    srcbuf += నిరంతరం * పరిమాణం(Ptype);                        \
                    ofs += నిరంతరం;                                           \
                } లేకపోతే ఒకవేళ (!ofs)                                          \
                    తిరిగి;                                               \
            } అయితే (ofs < w);                                            \
            /* skip padding if necessary */                               \
            స్థిరరాశి size_t psize = పరిమాణం(Ptype);                           \
            ఒకవేళ (psize == 2)                                               \
                srcbuf += (uintptr_t)srcbuf & 2;                          \
            /* blit translucent pixels on the same line */                \
            ofs = 0;                                                      \
            చేయి {                                                          \
                గుర్తులేని నిరంతరం;                                             \
                ofs += ((Uint16 *)srcbuf)[0];                             \
                నిరంతరం = ((Uint16 *)srcbuf)[1];                              \
                srcbuf += 4;                                              \
                ఒకవేళ (నిరంతరం) {                                                \
                    /* clip to left and right borders */                  \
                    పూర్ణాంకం cofs = ofs;                                       \
                    పూర్ణాంకం crun = నిరంతరం;                                       \
                    ఒకవేళ (ఎడమ - cofs > 0) {                                \
                        crun -= ఎడమ - cofs;                              \
                        cofs = ఎడమ;                                      \
                    }                                                     \
                    ఒకవేళ (crun > కుడి - cofs)                              \
                        crun = కుడి - cofs;                              \
                    ఒకవేళ (crun > 0) {                                       \
                        Ptype *dst = (Ptype *)dstbuf + cofs;              \
                        Uint32 *src = (Uint32 *)srcbuf + (cofs - ofs);    \
                        పూర్ణాంకం i;                                            \
                        కొరకు (i = 0; i < crun; i++)                        \
                            do_blend(src[i], dst[i]);                     \
                    }                                                     \
                    srcbuf += నిరంతరం * 4;                                    \
                    ofs += నిరంతరం;                                           \
                }                                                         \
            } అయితే (ofs < w);                                            \
            dstbuf += surf_dst->pitch;                                    \
        } అయితే (--linecount);                                            \
    } అయితే (0)

    ఎంపిక (df->బైట్లు_చొప్పున_pixel) {
    స్థితి 2:
        ఒకవేళ (df->Gmask == 0x07e0 || df->Rmask == 0x07e0 || df->Bmask == 0x07e0) {
            RLEALPHACLIPBLIT(Uint16, Uint8, BLIT_TRANSL_565);
        } లేకపోతే {
            RLEALPHACLIPBLIT(Uint16, Uint8, BLIT_TRANSL_555);
        }
        ఆపు;
    స్థితి 4:
        RLEALPHACLIPBLIT(Uint32, Uint16, BLIT_TRANSL_888);
        ఆపు;
    }
}

// blit a pixel-alpha RLE surface
స్థిర bool SDLCALL SDL_RLEAlphaBlit(SDL_Surface *surf_src, స్థిరరాశి SDL_Rect *srcrect,
                                     SDL_Surface *surf_dst, స్థిరరాశి SDL_Rect *dstrect)
{
    పూర్ణాంకం x, y;
    పూర్ణాంకం w = surf_src->w;
    Uint8 *srcbuf, *dstbuf;
    స్థిరరాశి SDL_PixelFormatDetails *df = surf_dst->fmt;

    // Lock the destination if necessary
    ఒకవేళ (SDL_MUSTLOCK(surf_dst)) {
        ఒకవేళ (!SDL_తాళం_Surface(surf_dst)) {
            తిరిగి false;
        }
    }

    x = dstrect->x;
    y = dstrect->y;
    dstbuf = (Uint8 *)surf_dst->pixels + y * surf_dst->pitch + x * df->బైట్లు_చొప్పున_pixel;
    srcbuf = (Uint8 *)surf_src->map.దత్తాంశం + పరిమాణం(SDL_PixelFormat);

    {
        // skip lines at the top if necessary
        పూర్ణాంకం vskip = srcrect->y;
        ఒకవేళ (vskip) {
            పూర్ణాంకం ofs;
            ఒకవేళ (df->బైట్లు_చొప్పున_pixel == 2) {
                // the 16/32 interleaved format
                చేయి {
                    // skip opaque line
                    ofs = 0;
                    చేయి {
                        పూర్ణాంకం నిరంతరం;
                        ofs += srcbuf[0];
                        నిరంతరం = srcbuf[1];
                        srcbuf += 2;
                        ఒకవేళ (నిరంతరం) {
                            srcbuf += 2 * నిరంతరం;
                            ofs += నిరంతరం;
                        } లేకపోతే ఒకవేళ (ofs == 0) {
                            వెళ్ళు పూర్తి;
                        }
                    } అయితే (ofs < w);

                    // skip padding
                    srcbuf += (uintptr_t)srcbuf & 2;

                    // skip translucent line
                    ofs = 0;
                    చేయి {
                        పూర్ణాంకం నిరంతరం;
                        ofs += ((Uint16 *)srcbuf)[0];
                        నిరంతరం = ((Uint16 *)srcbuf)[1];
                        srcbuf += 4 * (నిరంతరం + 1);
                        ofs += నిరంతరం;
                    } అయితే (ofs < w);
                } అయితే (--vskip);
            } లేకపోతే {
                // the 32/32 interleaved format
                vskip <<= 1; // opaque and translucent have same format
                చేయి {
                    ofs = 0;
                    చేయి {
                        పూర్ణాంకం నిరంతరం;
                        ofs += ((Uint16 *)srcbuf)[0];
                        నిరంతరం = ((Uint16 *)srcbuf)[1];
                        srcbuf += 4;
                        ఒకవేళ (నిరంతరం) {
                            srcbuf += 4 * నిరంతరం;
                            ofs += నిరంతరం;
                        } లేకపోతే ఒకవేళ (ofs == 0) {
                            వెళ్ళు పూర్తి;
                        }
                    } అయితే (ofs < w);
                } అయితే (--vskip);
            }
        }
    }

    // if left or right edge clipping needed, call clip blit
    ఒకవేళ (srcrect->x || srcrect->w != surf_src->w) {
        RLEAlphaClipBlit(w, srcbuf, surf_dst, dstbuf, srcrect);
    } లేకపోతే {

        /*
         * non-clipped blitter. Ptype is the destination pixel type,
         * Ctype the translucent count type, and do_blend the
         * macro to blend one pixel.
         */
#నిర్వచించు RLEALPHABLIT(Ptype, Ctype, do_blend)                         \
    చేయి {                                                             \
        పూర్ణాంకం linecount = srcrect->h;                                  \
        చేయి {                                                         \
            పూర్ణాంకం ofs = 0;                                             \
            /* blit opaque pixels on one line */                     \
            చేయి {                                                     \
                గుర్తులేని నిరంతరం;                                        \
                ofs += ((Ctype *)srcbuf)[0];                         \
                నిరంతరం = ((Ctype *)srcbuf)[1];                          \
                srcbuf += 2 * పరిమాణం(Ctype);                         \
                ఒకవేళ (నిరంతరం) {                                           \
                    PIXEL_COPY(dstbuf + ofs * పరిమాణం(Ptype), srcbuf, \
                               నిరంతరం, పరిమాణం(Ptype));                  \
                    srcbuf += నిరంతరం * పరిమాణం(Ptype);                   \
                    ofs += నిరంతరం;                                      \
                } లేకపోతే ఒకవేళ (!ofs)                                     \
                    వెళ్ళు పూర్తి;                                       \
            } అయితే (ofs < w);                                       \
            /* skip padding if necessary */                          \
            స్థిరరాశి size_t psize = పరిమాణం(Ptype);                      \
            ఒకవేళ (psize == 2)                                          \
                srcbuf += (uintptr_t)srcbuf & 2;                     \
            /* blit translucent pixels on the same line */           \
            ofs = 0;                                                 \
            చేయి {                                                     \
                గుర్తులేని నిరంతరం;                                        \
                ofs += ((Uint16 *)srcbuf)[0];                        \
                నిరంతరం = ((Uint16 *)srcbuf)[1];                         \
                srcbuf += 4;                                         \
                ఒకవేళ (నిరంతరం) {                                           \
                    Ptype *dst = (Ptype *)dstbuf + ofs;              \
                    గుర్తులేని i;                                      \
                    కొరకు (i = 0; i < నిరంతరం; i++) {                      \
                        Uint32 src = *(Uint32 *)srcbuf;              \
                        do_blend(src, *dst);                         \
                        srcbuf += 4;                                 \
                        dst++;                                       \
                    }                                                \
                    ofs += నిరంతరం;                                      \
                }                                                    \
            } అయితే (ofs < w);                                       \
            dstbuf += surf_dst->pitch;                               \
        } అయితే (--linecount);                                       \
    } అయితే (0)

        ఎంపిక (df->బైట్లు_చొప్పున_pixel) {
        స్థితి 2:
            ఒకవేళ (df->Gmask == 0x07e0 || df->Rmask == 0x07e0 || df->Bmask == 0x07e0) {
                RLEALPHABLIT(Uint16, Uint8, BLIT_TRANSL_565);
            } లేకపోతే {
                RLEALPHABLIT(Uint16, Uint8, BLIT_TRANSL_555);
            }
            ఆపు;
        స్థితి 4:
            RLEALPHABLIT(Uint32, Uint16, BLIT_TRANSL_888);
            ఆపు;
        }
    }

పూర్తి:
    // Unlock the destination if necessary
    ఒకవేళ (SDL_MUSTLOCK(surf_dst)) {
        SDL_UnlockSurface(surf_dst);
    }
    తిరిగి true;
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
స్థిర పూర్ణాంకం copy_opaque_16(శూన్య *dst, స్థిరరాశి Uint32 *src, పూర్ణాంకం n,
                          స్థిరరాశి SDL_PixelFormatDetails *sfmt, స్థిరరాశి SDL_PixelFormatDetails *dfmt)
{
    పూర్ణాంకం i;
    Uint16 *d = (Uint16 *)dst;
    కొరకు (i = 0; i < n; i++) {
        గుర్తులేని r, g, b;
        RGB_FROM_PIXEL(*src, sfmt, r, g, b);
        PIXEL_FROM_RGB(*d, dfmt, r, g, b);
        src++;
        d++;
    }
    తిరిగి n * 2;
}

// encode 32bpp rgb + a into 32bpp G0RAB format for blitting into 565
స్థిర పూర్ణాంకం copy_transl_565(శూన్య *dst, స్థిరరాశి Uint32 *src, పూర్ణాంకం n,
                           స్థిరరాశి SDL_PixelFormatDetails *sfmt, స్థిరరాశి SDL_PixelFormatDetails *dfmt)
{
    పూర్ణాంకం i;
    Uint32 *d = (Uint32 *)dst;
    కొరకు (i = 0; i < n; i++) {
        గుర్తులేని r, g, b, a;
        Uint16 pix;
        RGBA_FROM_8888(*src, sfmt, r, g, b, a);
        PIXEL_FROM_RGB(pix, dfmt, r, g, b);
        *d = ((pix & 0x7e0) << 16) | (pix & 0xf81f) | ((a << 2) & 0x7e0);
        src++;
        d++;
    }
    తిరిగి n * 4;
}

// encode 32bpp rgb + a into 32bpp G0RAB format for blitting into 555
స్థిర పూర్ణాంకం copy_transl_555(శూన్య *dst, స్థిరరాశి Uint32 *src, పూర్ణాంకం n,
                           స్థిరరాశి SDL_PixelFormatDetails *sfmt, స్థిరరాశి SDL_PixelFormatDetails *dfmt)
{
    పూర్ణాంకం i;
    Uint32 *d = (Uint32 *)dst;
    కొరకు (i = 0; i < n; i++) {
        గుర్తులేని r, g, b, a;
        Uint16 pix;
        RGBA_FROM_8888(*src, sfmt, r, g, b, a);
        PIXEL_FROM_RGB(pix, dfmt, r, g, b);
        *d = ((pix & 0x3e0) << 16) | (pix & 0xfc1f) | ((a << 2) & 0x3e0);
        src++;
        d++;
    }
    తిరిగి n * 4;
}

// encode 32bpp rgba into 32bpp rgba, keeping alpha (dual purpose)
స్థిర పూర్ణాంకం copy_32(శూన్య *dst, స్థిరరాశి Uint32 *src, పూర్ణాంకం n,
                   స్థిరరాశి SDL_PixelFormatDetails *sfmt, స్థిరరాశి SDL_PixelFormatDetails *dfmt)
{
    పూర్ణాంకం i;
    Uint32 *d = (Uint32 *)dst;
    కొరకు (i = 0; i < n; i++) {
        గుర్తులేని r, g, b, a;
        RGBA_FROM_8888(*src, sfmt, r, g, b, a);
        RLEPIXEL_FROM_RGBA(*d, dfmt, r, g, b, a);
        d++;
        src++;
    }
    తిరిగి n * 4;
}

#నిర్వచించు ISOPAQUE(pixel, fmt) ((((pixel)&fmt->Amask) >> fmt->Ashift) == 255)

#నిర్వచించు ISTRANSL(pixel, fmt) \
    ((గుర్తులేని)((((pixel)&fmt->Amask) >> fmt->Ashift) - 1U) < 254U)

// convert surface to be quickly alpha-blittable onto dest, if possible
స్థిర bool RLEAlphaSurface(SDL_Surface *surface)
{
    SDL_Surface *dest;
    స్థిరరాశి SDL_PixelFormatDetails *df;
    పూర్ణాంకం maxsize = 0;
    పూర్ణాంకం max_opaque_నిరంతరం;
    పూర్ణాంకం max_transl_నిరంతరం = 65535;
    గుర్తులేని masksum;
    Uint8 *rlebuf, *dst;
    పూర్ణాంకం (*copy_opaque)(శూన్య *, స్థిరరాశి Uint32 *, పూర్ణాంకం,
                       స్థిరరాశి SDL_PixelFormatDetails *, స్థిరరాశి SDL_PixelFormatDetails *);
    పూర్ణాంకం (*copy_transl)(శూన్య *, స్థిరరాశి Uint32 *, పూర్ణాంకం,
                       స్థిరరాశి SDL_PixelFormatDetails *, స్థిరరాశి SDL_PixelFormatDetails *);

    dest = surface->map.info.dst_surface;
    ఒకవేళ (!dest) {
        తిరిగి false;
    }
    df = dest->fmt;
    ఒకవేళ (surface->fmt->బిట్లు_చొప్పున_pixel != 32) {
        తిరిగి false; // only 32bpp source supported
    }

    /* find out whether the destination is one we support,
       and determine the max size of the encoded result */
    masksum = df->Rmask | df->Gmask | df->Bmask;
    ఎంపిక (df->బైట్లు_చొప్పున_pixel) {
    స్థితి 2:
        // 16bpp: only support 565 and 555 formats
        ఎంపిక (masksum) {
        స్థితి 0xffff:
            ఒకవేళ (df->Gmask == 0x07e0 || df->Rmask == 0x07e0 || df->Bmask == 0x07e0) {
                copy_opaque = copy_opaque_16;
                copy_transl = copy_transl_565;
            } లేకపోతే {
                తిరిగి false;
            }
            ఆపు;
        స్థితి 0x7fff:
            ఒకవేళ (df->Gmask == 0x03e0 || df->Rmask == 0x03e0 || df->Bmask == 0x03e0) {
                copy_opaque = copy_opaque_16;
                copy_transl = copy_transl_555;
            } లేకపోతే {
                తిరిగి false;
            }
            ఆపు;
        అప్రమేయ:
            తిరిగి false;
        }
        max_opaque_నిరంతరం = 255; // runs stored as bytes

        /* worst case is alternating opaque and translucent pixels,
           with room for alignment padding between lines */
        maxsize = surface->h * (2 + (4 + 2) * (surface->w + 1)) + 2;
        ఆపు;
    స్థితి 4:
        ఒకవేళ (masksum != 0x00ffffff) {
            తిరిగి false; // requires unused high byte
        }
        copy_opaque = copy_32;
        copy_transl = copy_32;
        max_opaque_నిరంతరం = 255; // runs stored as short ints

        // worst case is alternating opaque and translucent pixels
        maxsize = surface->h * 2 * 4 * (surface->w + 1) + 4;
        ఆపు;
    అప్రమేయ:
        తిరిగి false; // anything else unsupported right now
    }

    maxsize += పరిమాణం(SDL_PixelFormat);
    rlebuf = (Uint8 *)SDL_malloc(maxsize);
    ఒకవేళ (!rlebuf) {
        తిరిగి false;
    }
    // save the destination format so we can undo the encoding later
    *(SDL_PixelFormat *)rlebuf = dest->format;
    dst = rlebuf + పరిమాణం(SDL_PixelFormat);

    // Do the actual encoding
    {
        పూర్ణాంకం x, y;
        పూర్ణాంకం h = surface->h, w = surface->w;
        స్థిరరాశి SDL_PixelFormatDetails *sf = surface->fmt;
        Uint32 *src = (Uint32 *)surface->pixels;
        Uint8 *lastline = dst; // end of last non-blank line

        // opaque counts are 8 or 16 bits, depending on target depth
#నిర్వచించు కూడు_OPAQUE_COUNTS(n, m)           \
    ఒకవేళ (df->బైట్లు_చొప్పున_pixel == 4) {         \
        ((Uint16 *)dst)[0] = (Uint16)n;   \
        ((Uint16 *)dst)[1] = (Uint16)m;   \
        dst += 4;                         \
    } లేకపోతే {                              \
        dst[0] = (Uint8)n;                \
        dst[1] = (Uint8)m;                \
        dst += 2;                         \
    }

        // translucent counts are always 16 bit
#నిర్వచించు కూడు_TRANSL_COUNTS(n, m) \
    (((Uint16 *)dst)[0] = (Uint16)n, ((Uint16 *)dst)[1] = (Uint16)m, dst += 4)

        కొరకు (y = 0; y < h; y++) {
            పూర్ణాంకం runstart, skipstart;
            పూర్ణాంకం blankline = 0;
            // First encode all opaque pixels of a scan line
            x = 0;
            చేయి {
                పూర్ణాంకం నిరంతరం, skip, len;
                skipstart = x;
                అయితే (x < w && !ISOPAQUE(src[x], sf)) {
                    x++;
                }
                runstart = x;
                అయితే (x < w && ISOPAQUE(src[x], sf)) {
                    x++;
                }
                skip = runstart - skipstart;
                ఒకవేళ (skip == w) {
                    blankline = 1;
                }
                నిరంతరం = x - runstart;
                అయితే (skip > max_opaque_నిరంతరం) {
                    కూడు_OPAQUE_COUNTS(max_opaque_నిరంతరం, 0);
                    skip -= max_opaque_నిరంతరం;
                }
                len = SDL_min(నిరంతరం, max_opaque_నిరంతరం);
                కూడు_OPAQUE_COUNTS(skip, len);
                dst += copy_opaque(dst, src + runstart, len, sf, df);
                runstart += len;
                నిరంతరం -= len;
                అయితే (నిరంతరం) {
                    len = SDL_min(నిరంతరం, max_opaque_నిరంతరం);
                    కూడు_OPAQUE_COUNTS(0, len);
                    dst += copy_opaque(dst, src + runstart, len, sf, df);
                    runstart += len;
                    నిరంతరం -= len;
                }
            } అయితే (x < w);

            // Make sure the next output address is 32-bit aligned
            dst += (uintptr_t)dst & 2;

            // Next, encode all translucent pixels of the same scan line
            x = 0;
            చేయి {
                పూర్ణాంకం నిరంతరం, skip, len;
                skipstart = x;
                అయితే (x < w && !ISTRANSL(src[x], sf)) {
                    x++;
                }
                runstart = x;
                అయితే (x < w && ISTRANSL(src[x], sf)) {
                    x++;
                }
                skip = runstart - skipstart;
                blankline &= (skip == w);
                నిరంతరం = x - runstart;
                అయితే (skip > max_transl_నిరంతరం) {
                    కూడు_TRANSL_COUNTS(max_transl_నిరంతరం, 0);
                    skip -= max_transl_నిరంతరం;
                }
                len = SDL_min(నిరంతరం, max_transl_నిరంతరం);
                కూడు_TRANSL_COUNTS(skip, len);
                dst += copy_transl(dst, src + runstart, len, sf, df);
                runstart += len;
                నిరంతరం -= len;
                అయితే (నిరంతరం) {
                    len = SDL_min(నిరంతరం, max_transl_నిరంతరం);
                    కూడు_TRANSL_COUNTS(0, len);
                    dst += copy_transl(dst, src + runstart, len, sf, df);
                    runstart += len;
                    నిరంతరం -= len;
                }
                ఒకవేళ (!blankline) {
                    lastline = dst;
                }
            } అయితే (x < w);

            src += surface->pitch >> 2;
        }
        dst = lastline; // back up past trailing blank lines
        కూడు_OPAQUE_COUNTS(0, 0);
    }

#నిర్వచనం_రద్దు కూడు_OPAQUE_COUNTS
#నిర్వచనం_రద్దు కూడు_TRANSL_COUNTS

    // reallocate the buffer to release unused memory
    {
        Uint8 *p = (Uint8 *)SDL_realloc(rlebuf, dst - rlebuf);
        ఒకవేళ (!p) {
            p = rlebuf;
        }
        surface->map.దత్తాంశం = p;
    }

    తిరిగి true;
}

స్థిర Uint32 getpix_8(స్థిరరాశి Uint8 *srcbuf)
{
    తిరిగి *srcbuf;
}

స్థిర Uint32 getpix_16(స్థిరరాశి Uint8 *srcbuf)
{
    తిరిగి *(స్థిరరాశి Uint16 *)srcbuf;
}

స్థిర Uint32 getpix_24(స్థిరరాశి Uint8 *srcbuf)
{
#ఒకవేళ SDL_BYTEORDER == SDL_LIL_ENDIAN
    తిరిగి srcbuf[0] + (srcbuf[1] << 8) + (srcbuf[2] << 16);
#లేకపోతే
    తిరిగి (srcbuf[0] << 16) + (srcbuf[1] << 8) + srcbuf[2];
#అయితే_ముగింపు
}

స్థిర Uint32 getpix_32(స్థిరరాశి Uint8 *srcbuf)
{
    తిరిగి *(స్థిరరాశి Uint32 *)srcbuf;
}

రకనిర్వచనం Uint32 (*getpix_func)(స్థిరరాశి Uint8 *);

స్థిర స్థిరరాశి getpix_func getpixes[4] = {
    getpix_8, getpix_16, getpix_24, getpix_32
};

స్థిర bool RLEColorkeySurface(SDL_Surface *surface)
{
    SDL_Surface *dest;
    Uint8 *rlebuf, *dst;
    పూర్ణాంకం maxn;
    పూర్ణాంకం y;
    Uint8 *srcbuf, *lastline;
    పూర్ణాంకం maxsize = 0;
    స్థిరరాశి పూర్ణాంకం bpp = surface->fmt->బైట్లు_చొప్పున_pixel;
    getpix_func getpix;
    Uint32 ckey, rgbmask;
    పూర్ణాంకం w, h;

    dest = surface->map.info.dst_surface;
    ఒకవేళ (!dest) {
        తిరిగి false;
    }

    // calculate the worst case size for the compressed surface
    ఎంపిక (bpp) {
    స్థితి 1:
        /* worst case is alternating opaque and transparent pixels,
           starting with an opaque pixel */
        maxsize = surface->h * 3 * (surface->w / 2 + 1) + 2;
        ఆపు;
    స్థితి 2:
    స్థితి 3:
        // worst case is solid runs, at most 255 pixels wide
        maxsize = surface->h * (2 * (surface->w / 255 + 1) + surface->w * bpp) + 2;
        ఆపు;
    స్థితి 4:
        // worst case is solid runs, at most 65535 pixels wide
        maxsize = surface->h * (4 * (surface->w / 65535 + 1) + surface->w * 4) + 4;
        ఆపు;

    అప్రమేయ:
        తిరిగి false;
    }

    maxsize += పరిమాణం(SDL_PixelFormat);
    rlebuf = (Uint8 *)SDL_malloc(maxsize);
    ఒకవేళ (!rlebuf) {
        తిరిగి false;
    }
    // save the destination format so we can undo the encoding later
    *(SDL_PixelFormat *)rlebuf = dest->format;

    // Set up the conversion
    srcbuf = (Uint8 *)surface->pixels;
    maxn = bpp == 4 ? 65535 : 255;
    dst = rlebuf + పరిమాణం(SDL_PixelFormat);
    rgbmask = ~surface->fmt->Amask;
    ckey = surface->map.info.colorkey & rgbmask;
    lastline = dst;
    getpix = getpixes[bpp - 1];
    w = surface->w;
    h = surface->h;

#నిర్వచించు కూడు_COUNTS(n, m)                \
    ఒకవేళ (bpp == 4) {                     \
        ((Uint16 *)dst)[0] = (Uint16)n; \
        ((Uint16 *)dst)[1] = (Uint16)m; \
        dst += 4;                       \
    } లేకపోతే {                            \
        dst[0] = (Uint8)n;              \
        dst[1] = (Uint8)m;              \
        dst += 2;                       \
    }

    కొరకు (y = 0; y < h; y++) {
        పూర్ణాంకం x = 0;
        పూర్ణాంకం blankline = 0;
        చేయి {
            పూర్ణాంకం నిరంతరం, skip;
            పూర్ణాంకం len;
            పూర్ణాంకం runstart;
            పూర్ణాంకం skipstart = x;

            // find run of transparent, then opaque pixels
            అయితే (x < w && (getpix(srcbuf + x * bpp) & rgbmask) == ckey) {
                x++;
            }
            runstart = x;
            అయితే (x < w && (getpix(srcbuf + x * bpp) & rgbmask) != ckey) {
                x++;
            }
            skip = runstart - skipstart;
            ఒకవేళ (skip == w) {
                blankline = 1;
            }
            నిరంతరం = x - runstart;

            // encode segment
            అయితే (skip > maxn) {
                కూడు_COUNTS(maxn, 0);
                skip -= maxn;
            }
            len = SDL_min(నిరంతరం, maxn);
            కూడు_COUNTS(skip, len);
            SDL_memcpy(dst, srcbuf + runstart * bpp, (size_t)len * bpp);
            dst += len * bpp;
            నిరంతరం -= len;
            runstart += len;
            అయితే (నిరంతరం) {
                len = SDL_min(నిరంతరం, maxn);
                కూడు_COUNTS(0, len);
                SDL_memcpy(dst, srcbuf + runstart * bpp, (size_t)len * bpp);
                dst += len * bpp;
                runstart += len;
                నిరంతరం -= len;
            }
            ఒకవేళ (!blankline) {
                lastline = dst;
            }
        } అయితే (x < w);

        srcbuf += surface->pitch;
    }
    dst = lastline; // back up bast trailing blank lines
    కూడు_COUNTS(0, 0);

#నిర్వచనం_రద్దు కూడు_COUNTS

    // reallocate the buffer to release unused memory
    {
        // If SDL_realloc returns NULL, the original block is left intact
        Uint8 *p = (Uint8 *)SDL_realloc(rlebuf, dst - rlebuf);
        ఒకవేళ (!p) {
            p = rlebuf;
        }
        surface->map.దత్తాంశం = p;
    }

    తిరిగి true;
}

bool SDL_RLESurface(SDL_Surface *surface)
{
    పూర్ణాంకం flags;

    // Clear any previous RLE conversion
    ఒకవేళ (surface->అంతర్గత_flags & SDL_అంతర్గత_SURFACE_RLEACCEL) {
        SDL_UnRLESurface(surface);
    }

    // We don't support RLE encoding of bitmaps
    ఒకవేళ (SDL_BITSPERPIXEL(surface->format) < 8) {
        తిరిగి false;
    }

    // Make sure the pixels are available
    ఒకవేళ (!surface->pixels) {
        తిరిగి false;
    }

    flags = surface->map.info.flags;
    ఒకవేళ (flags & SDL_COPY_COLORKEY) {
        // ok
    } లేకపోతే ఒకవేళ ((flags & SDL_COPY_BLEND) && SDL_ISPIXELFORMAT_ALPHA(surface->format)) {
        // ok
    } లేకపోతే {
        // If we don't have colorkey or blending, nothing to do...
        తిరిగి false;
    }

    // Pass on combinations not supported
    ఒకవేళ ((flags & SDL_COPY_MODULATE_COLOR) ||
        ((flags & SDL_COPY_MODULATE_ALPHA) && SDL_ISPIXELFORMAT_ALPHA(surface->format)) ||
        (flags & (SDL_COPY_BLEND_PREMULTIPLIED | SDL_COPY_కూడు | SDL_COPY_కూడు_PREMULTIPLIED | SDL_COPY_MOD | SDL_COPY_MUL)) ||
        (flags & SDL_COPY_సమీప)) {
        తిరిగి false;
    }

    // Encode and set up the blit
    ఒకవేళ (!SDL_ISPIXELFORMAT_ALPHA(surface->format) || !(flags & SDL_COPY_BLEND)) {
        ఒకవేళ (!surface->map.తటస్థం) {
            తిరిగి false;
        }
        ఒకవేళ (!RLEColorkeySurface(surface)) {
            తిరిగి false;
        }
        surface->map.blit = SDL_RLEBlit;
        surface->map.info.flags |= SDL_COPY_RLE_COLORKEY;
    } లేకపోతే {
        ఒకవేళ (!RLEAlphaSurface(surface)) {
            తిరిగి false;
        }
        surface->map.blit = SDL_RLEAlphaBlit;
        surface->map.info.flags |= SDL_COPY_RLE_ALPHAKEY;
    }

    ఒకవేళ (!(surface->flags & SDL_SURFACE_PREALLOCATED)) {
        surface->saved_pixels = surface->pixels;
        surface->pixels = ఖాళీ;
    }

    // The surface is now accelerated
    surface->అంతర్గత_flags |= SDL_అంతర్గత_SURFACE_RLEACCEL;
    SDL_Update_Surface_తాళం_Flag(surface);

    తిరిగి true;
}

శూన్య SDL_UnRLESurface(SDL_Surface *surface)
{
    ఒకవేళ (surface->అంతర్గత_flags & SDL_అంతర్గత_SURFACE_RLEACCEL) {
        surface->అంతర్గత_flags &= ~SDL_అంతర్గత_SURFACE_RLEACCEL;

        surface->map.info.flags &= ~(SDL_COPY_RLE_COLORKEY | SDL_COPY_RLE_ALPHAKEY);

        ఒకవేళ (!(surface->flags & SDL_SURFACE_PREALLOCATED)) {
            surface->pixels = surface->saved_pixels;
            surface->saved_pixels = ఖాళీ;
        }

        SDL_free(surface->map.దత్తాంశం);
        surface->map.దత్తాంశం = ఖాళీ;

        SDL_InvalidateMap(&surface->map);

        SDL_Update_Surface_తాళం_Flag(surface);
    }
}

#అయితే_ముగింపు // SDL_HAVE_RLE
