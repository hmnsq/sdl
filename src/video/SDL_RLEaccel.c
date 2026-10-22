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

#ifdef SDL_HAVE_RLE

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

#ضمن "SDL_sysvideo.h"
#ضمن "SDL_surface_c.h"
#ضمن "SDL_pixels_c.h"
#ضمن "SDL_RLEaccel_c.h"

#define PIXEL_COPY(to, from, len, bpp) \
    SDL_memcpy(to, from, (size_t)(len) * (bpp))

/*
 * Various colorkey blit methods, for opaque and per-surface alpha
 */

#define OPAQUE_BLIT(to, from, length, bpp, alpha) \
    PIXEL_COPY(to, from, length, bpp)

/*
 * For 32bpp pixels on the form 0x00rrggbb:
 * If we treat the middle component separately, we can process the two
 * remaining in parallel. This is safe to do because of the gap to the left
 * of each component, so the bits from the multiplication don't collide.
 * This can be used for any RGB permutation of course.
 */
#define ALPHA_BLIT32_888(to, from, length, bpp, alpha)       \
    ܥܒܕ {                                                     \
        صحيح i;                                               \
        Uint32 *src = (Uint32 *)(from);                      \
        Uint32 *dst = (Uint32 *)(to);                        \
        لكل (i = 0; i < (صحيح)(length); i++) {                \
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
    } ܟܡܐ (0)

/*
 * For 16bpp pixels we can go a step further: put the middle component
 * in the high 16 bits of a 32 bit word, and process all three RGB
 * components at the same time. Since the smallest gap is here just
 * 5 bits, we have to scale alpha down to 5 bits as well.
 */
#define ALPHA_BLIT16_565(to, from, length, bpp, alpha) \
    ܥܒܕ {                                               \
        صحيح i;                                         \
        Uint16 *src = (Uint16 *)(from);                \
        Uint16 *dst = (Uint16 *)(to);                  \
        Uint32 ALPHA = alpha >> 3;                     \
        لكل (i = 0; i < (صحيح)(length); i++) {          \
            Uint32 s = *src++;                         \
            Uint32 d = *dst;                           \
            s = (s | s << 16) & 0x07e0f81f;            \
            d = (d | d << 16) & 0x07e0f81f;            \
            d += (s - d) * ALPHA >> 5;                 \
            d &= 0x07e0f81f;                           \
            *dst++ = (Uint16)(d | d >> 16);            \
        }                                              \
    } ܟܡܐ (0)

#define ALPHA_BLIT16_555(to, from, length, bpp, alpha) \
    ܥܒܕ {                                               \
        صحيح i;                                         \
        Uint16 *src = (Uint16 *)(from);                \
        Uint16 *dst = (Uint16 *)(to);                  \
        Uint32 ALPHA = alpha >> 3;                     \
        لكل (i = 0; i < (صحيح)(length); i++) {          \
            Uint32 s = *src++;                         \
            Uint32 d = *dst;                           \
            s = (s | s << 16) & 0x03e07c1f;            \
            d = (d | d << 16) & 0x03e07c1f;            \
            d += (s - d) * ALPHA >> 5;                 \
            d &= 0x03e07c1f;                           \
            *dst++ = (Uint16)(d | d >> 16);            \
        }                                              \
    } ܟܡܐ (0)

/*
 * The general slow catch-all function, for remaining depths and formats
 */
#ܐܢ SDL_BYTEORDER == SDL_BIG_ENDIAN
#define SET_RGB24(dst, d)      \
    dst[0] = (Uint8)(d >> 16); \
    dst[1] = (Uint8)(d >> 8);  \
    dst[2] = (Uint8)(d);
#ܐܚܪܢܐ
#define SET_RGB24(dst, d)      \
    dst[0] = (Uint8)(d);       \
    dst[1] = (Uint8)(d >> 8);  \
    dst[2] = (Uint8)(d >> 16);
#endif
#define ALPHA_BLIT_ANY(to, from, length, bpp, alpha)             \
    ܥܒܕ {                                                         \
        صحيح i;                                                   \
        Uint8 *src = from;                                       \
        Uint8 *dst = to;                                         \
        لكل (i = 0; i < (صحيح)(length); i++) {                    \
            Uint32 s = 0, d = 0;                                 \
            unsigned rs, gs, bs, rd, gd, bd;                     \
            بدل (bpp) {                                       \
            حالة 2:                                              \
                s = *(Uint16 *)src;                              \
                d = *(Uint16 *)dst;                              \
                اكسر;                                           \
            حالة 3:                                              \
                s = GET_RGB24(src);                              \
                d = GET_RGB24(dst);                              \
                اكسر;                                           \
            حالة 4:                                              \
                s = *(Uint32 *)src;                              \
                d = *(Uint32 *)dst;                              \
                اكسر;                                           \
            }                                                    \
            RGB_FROM_PIXEL(s, fmt, rs, gs, bs);                  \
            RGB_FROM_PIXEL(d, fmt, rd, gd, bd);                  \
            rd += (rs - rd) * alpha >> 8;                        \
            gd += (gs - gd) * alpha >> 8;                        \
            bd += (bs - bd) * alpha >> 8;                        \
            PIXEL_FROM_RGB(d, fmt, rd, gd, bd);                  \
            بدل (bpp) {                                       \
            حالة 2:                                              \
                *(Uint16 *)dst = (Uint16)d;                      \
                اكسر;                                           \
            حالة 3:                                              \
                SET_RGB24(dst, d);                               \
                اكسر;                                           \
            حالة 4:                                              \
                *(Uint32 *)dst = d;                              \
                اكسر;                                           \
            }                                                    \
            src += bpp;                                          \
            dst += bpp;                                          \
        }                                                        \
    } ܟܡܐ (0)

/*
 * Special case: 50% alpha (alpha=128)
 * This is treated specially because it can be optimized very well, and
 * since it is good for many cases of semi-translucency.
 * The theory is to do all three components at the same time:
 * First zero the lowest bit of each component, which gives us room to
 * add them. Then shift right and add the sum of the lowest bits.
 */
#define ALPHA_BLIT32_888_50(to, from, length, bpp, alpha)                                 \
    ܥܒܕ {                                                                                  \
        صحيح i;                                                                            \
        Uint32 *src = (Uint32 *)(from);                                                   \
        Uint32 *dst = (Uint32 *)(to);                                                     \
        لكل (i = 0; i < (صحيح)(length); i++) {                                             \
            Uint32 s = *src++;                                                            \
            Uint32 d = *dst;                                                              \
            *dst++ = (((s & 0x00fefefe) + (d & 0x00fefefe)) >> 1) + (s & d & 0x00010101); \
        }                                                                                 \
    } ܟܡܐ (0)

/*
 * For 16bpp, we can actually blend two pixels in parallel, if we take
 * care to shift before we add, not after.
 */

// helper: blend a single 16 bit pixel at 50%
#define BLEND16_50(dst, src, mask)                           \
    ܥܒܕ {                                                     \
        Uint32 s = *src++;                                   \
        Uint32 d = *dst;                                     \
        *dst++ = (Uint16)((((s & mask) + (d & mask)) >> 1) + \
                          (s & d & (~mask & 0xffff)));       \
    } ܟܡܐ (0)

// basic 16bpp blender. mask is the pixels to keep when adding.
#define ALPHA_BLIT16_50(to, from, length, bpp, alpha, mask)                                                                              \
    ܥܒܕ {                                                                                                                                 \
        unsigned n = (length);                                                                                                           \
        Uint16 *src = (Uint16 *)(from);                                                                                                  \
        Uint16 *dst = (Uint16 *)(to);                                                                                                    \
        ܐܢ (((uintptr_t)src ^ (uintptr_t)dst) & 3) {                                                                                     \
            /* source and destination not in phase, blit one by one */                                                                   \
            ܟܡܐ (n--)                                                                                                                  \
                BLEND16_50(dst, src, mask);                                                                                              \
        } ܐܚܪܢܐ {                                                                                                                         \
            ܐܢ ((uintptr_t)src & 3) {                                                                                                    \
                /* first odd pixel */                                                                                                    \
                BLEND16_50(dst, src, mask);                                                                                              \
                n--;                                                                                                                     \
            }                                                                                                                            \
            لكل (; n > 1; n -= 2) {                                                                                                      \
                Uint32 s = *(Uint32 *)src;                                                                                               \
                Uint32 d = *(Uint32 *)dst;                                                                                               \
                *(Uint32 *)dst = ((s & (mask | mask << 16)) >> 1) + ((d & (mask | mask << 16)) >> 1) + (s & d & (~(mask | mask << 16))); \
                src += 2;                                                                                                                \
                dst += 2;                                                                                                                \
            }                                                                                                                            \
            ܐܢ (n)                                                                                                                       \
                BLEND16_50(dst, src, mask); /* last odd pixel */                                                                         \
        }                                                                                                                                \
    } ܟܡܐ (0)

#define ALPHA_BLIT16_565_50(to, from, length, bpp, alpha) \
    ALPHA_BLIT16_50(to, from, length, bpp, alpha, 0xf7deU)

#define ALPHA_BLIT16_555_50(to, from, length, bpp, alpha) \
    ALPHA_BLIT16_50(to, from, length, bpp, alpha, 0xfbdeU)

#define CHOOSE_BLIT(blitter, alpha, fmt)                                                                                                              \
    ܥܒܕ {                                                                                                                                              \
        ܐܢ (alpha == 255) {                                                                                                                           \
            بدل (fmt->bytes_per_pixel) {                                                                                                             \
            حالة 1:                                                                                                                                   \
                blitter(1, Uint8, OPAQUE_BLIT);                                                                                                       \
                اكسر;                                                                                                                                \
            حالة 2:                                                                                                                                   \
                blitter(2, Uint8, OPAQUE_BLIT);                                                                                                       \
                اكسر;                                                                                                                                \
            حالة 3:                                                                                                                                   \
                blitter(3, Uint8, OPAQUE_BLIT);                                                                                                       \
                اكسر;                                                                                                                                \
            حالة 4:                                                                                                                                   \
                blitter(4, Uint16, OPAQUE_BLIT);                                                                                                      \
                اكسر;                                                                                                                                \
            }                                                                                                                                         \
        } ܐܚܪܢܐ {                                                                                                                                      \
            بدل (fmt->bytes_per_pixel) {                                                                                                             \
            حالة 1:                                                                                                                                   \
                /* No 8bpp alpha blitting */                                                                                                          \
                اكسر;                                                                                                                                \
                                                                                                                                                      \
            حالة 2:                                                                                                                                   \
                بدل (fmt->Rmask | fmt->Gmask | fmt->Bmask) {                                                                                       \
                حالة 0xffff:                                                                                                                          \
                    ܐܢ (fmt->Gmask == 0x07e0 || fmt->Rmask == 0x07e0 || fmt->Bmask == 0x07e0) {                                                       \
                        ܐܢ (alpha == 128) {                                                                                                           \
                            blitter(2, Uint8, ALPHA_BLIT16_565_50);                                                                                   \
                        } ܐܚܪܢܐ {                                                                                                                      \
                            blitter(2, Uint8, ALPHA_BLIT16_565);                                                                                      \
                        }                                                                                                                             \
                    } ܐܚܪܢܐ {                                                                                                                          \
                        اذهب general16;                                                                                                               \
                    }                                                                                                                                 \
                    اكسر;                                                                                                                            \
                                                                                                                                                      \
                حالة 0x7fff:                                                                                                                          \
                    ܐܢ (fmt->Gmask == 0x03e0 || fmt->Rmask == 0x03e0 || fmt->Bmask == 0x03e0) {                                                       \
                        ܐܢ (alpha == 128) {                                                                                                           \
                            blitter(2, Uint8, ALPHA_BLIT16_555_50);                                                                                   \
                        } ܐܚܪܢܐ {                                                                                                                      \
                            blitter(2, Uint8, ALPHA_BLIT16_555);                                                                                      \
                        }                                                                                                                             \
                        اكسر;                                                                                                                        \
                    } ܐܚܪܢܐ {                                                                                                                          \
                        اذهب general16;                                                                                                               \
                    }                                                                                                                                 \
                    اكسر;                                                                                                                            \
                                                                                                                                                      \
                افتراضي:                                                                                                                              \
                general16:                                                                                                                            \
                    blitter(2, Uint8, ALPHA_BLIT_ANY);                                                                                                \
                }                                                                                                                                     \
                اكسر;                                                                                                                                \
                                                                                                                                                      \
            حالة 3:                                                                                                                                   \
                blitter(3, Uint8, ALPHA_BLIT_ANY);                                                                                                    \
                اكسر;                                                                                                                                \
                                                                                                                                                      \
            حالة 4:                                                                                                                                   \
                ܐܢ ((fmt->Rmask | fmt->Gmask | fmt->Bmask) == 0x00ffffff && (fmt->Gmask == 0xff00 || fmt->Rmask == 0xff00 || fmt->Bmask == 0xff00)) { \
                    ܐܢ (alpha == 128) {                                                                                                               \
                        blitter(4, Uint16, ALPHA_BLIT32_888_50);                                                                                      \
                    } ܐܚܪܢܐ {                                                                                                                          \
                        blitter(4, Uint16, ALPHA_BLIT32_888);                                                                                         \
                    }                                                                                                                                 \
                } ܐܚܪܢܐ {                                                                                                                              \
                    blitter(4, Uint16, ALPHA_BLIT_ANY);                                                                                               \
                }                                                                                                                                     \
                اكسر;                                                                                                                                \
            }                                                                                                                                         \
        }                                                                                                                                             \
    } ܟܡܐ (0)

/*
 * Set a pixel value using the given format, except that the alpha value is
 * placed in the top byte. This is the format used for RLE with alpha.
 */
#define RLEPIXEL_FROM_RGBA(Pixel, fmt, r, g, b, a)   \
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
#define RLECLIPBLIT(bpp, Type, do_blit)                                    \
    ܥܒܕ {                                                                   \
        صحيح linecount = srcrect->h;                                        \
        صحيح ofs = 0;                                                       \
        صحيح left = srcrect->x;                                             \
        صحيح right = left + srcrect->w;                                     \
        dstbuf -= left * bpp;                                              \
        لكل (;;) {                                                         \
            صحيح run;                                                       \
            ofs += *(Type *)srcbuf;                                        \
            run = ((Type *)srcbuf)[1];                                     \
            srcbuf += 2 * حجم(Type);                                    \
            ܐܢ (run) {                                                     \
                /* clip to left and right borders */                       \
                ܐܢ (ofs < right) {                                         \
                    صحيح start = 0;                                         \
                    صحيح len = run;                                         \
                    صحيح startcol;                                          \
                    ܐܢ (left - ofs > 0) {                                  \
                        start = left - ofs;                                \
                        len -= start;                                      \
                        ܐܢ (len <= 0)                                      \
                            اذهب nocopy##bpp##do_blit;                     \
                    }                                                      \
                    startcol = ofs + start;                                \
                    ܐܢ (len > right - startcol)                            \
                        len = right - startcol;                            \
                    do_blit(dstbuf + startcol * bpp, srcbuf + start * bpp, \
                            len, bpp, alpha);                              \
                }                                                          \
                nocopy##bpp##do_blit : srcbuf += run * bpp;                \
                ofs += run;                                                \
            } ܐܚܪܢܐ ܐܢ (!ofs) {                                             \
                اكسر;                                                     \
            }                                                              \
                                                                           \
            ܐܢ (ofs == w) {                                                \
                ofs = 0;                                                   \
                dstbuf += surf_dst->pitch;                                 \
                ܐܢ (!--linecount) {                                        \
                    اكسر;                                                 \
                }                                                          \
            }                                                              \
        }                                                                  \
    } ܟܡܐ (0)

ساكن فراغ RLEClipBlit(صحيح w, Uint8 *srcbuf, SDL_Surface *surf_dst,
                        Uint8 *dstbuf, ثابت SDL_Rect *srcrect, unsigned alpha)
{
    ثابت SDL_PixelFormatDetails *fmt = surf_dst->fmt;

    CHOOSE_BLIT(RLECLIPBLIT, alpha, fmt);
}

#undef RLECLIPBLIT

// blit a colorkeyed RLE surface
ساكن bool SDLCALL SDL_RLEBlit(SDL_Surface *surf_src, ثابت SDL_Rect *srcrect,
                                SDL_Surface *surf_dst, ثابت SDL_Rect *dstrect)
{
    Uint8 *dstbuf;
    Uint8 *srcbuf;
    صحيح x, y;
    صحيح w = surf_src->w;
    unsigned alpha;

    // Lock the destination if necessary
    ܐܢ (SDL_MUSTLOCK(surf_dst)) {
        ܐܢ (!SDL_LockSurface(surf_dst)) {
            ܦܢܐ false;
        }
    }

    // Set up the source and destination pointers
    x = dstrect->x;
    y = dstrect->y;
    dstbuf = (Uint8 *)surf_dst->pixels + y * surf_dst->pitch + x * surf_src->fmt->bytes_per_pixel;
    srcbuf = (Uint8 *)surf_src->map.data + حجم(SDL_PixelFormat);

    {
        // skip lines at the top if necessary
        صحيح vskip = srcrect->y;
        صحيح ofs = 0;
        ܐܢ (vskip) {

#define RLESKIP(bpp, Type)          \
    لكل (;;) {                      \
        صحيح run;                    \
        ofs += *(Type *)srcbuf;     \
        run = ((Type *)srcbuf)[1];  \
        srcbuf += حجم(Type) * 2; \
        ܐܢ (run) {                  \
            srcbuf += run * bpp;    \
            ofs += run;             \
        } ܐܚܪܢܐ ܐܢ (!ofs)            \
            اذهب done;              \
        ܐܢ (ofs == w) {             \
            ofs = 0;                \
            ܐܢ (!--vskip)           \
                اكسر;              \
        }                           \
    }

            بدل (surf_src->fmt->bytes_per_pixel) {
            حالة 1:
                RLESKIP(1, Uint8);
                اكسر;
            حالة 2:
                RLESKIP(2, Uint8);
                اكسر;
            حالة 3:
                RLESKIP(3, Uint8);
                اكسر;
            حالة 4:
                RLESKIP(4, Uint16);
                اكسر;
            }

#undef RLESKIP
        }
    }

    alpha = surf_src->map.info.a;
    // if left or right edge clipping needed, call clip blit
    ܐܢ (srcrect->x || srcrect->w != surf_src->w) {
        RLEClipBlit(w, srcbuf, surf_dst, dstbuf, srcrect, alpha);
    } ܐܚܪܢܐ {
        ثابت SDL_PixelFormatDetails *fmt = surf_src->fmt;

#define RLEBLIT(bpp, Type, do_blit)                                   \
    ܥܒܕ {                                                              \
        صحيح linecount = srcrect->h;                                   \
        صحيح ofs = 0;                                                  \
        لكل (;;) {                                                    \
            unsigned run;                                             \
            ofs += *(Type *)srcbuf;                                   \
            run = ((Type *)srcbuf)[1];                                \
            srcbuf += 2 * حجم(Type);                               \
            ܐܢ (run) {                                                \
                do_blit(dstbuf + ofs * bpp, srcbuf, run, bpp, alpha); \
                srcbuf += run * bpp;                                  \
                ofs += run;                                           \
            } ܐܚܪܢܐ ܐܢ (!ofs)                                          \
                اكسر;                                                \
            ܐܢ (ofs == w) {                                           \
                ofs = 0;                                              \
                dstbuf += surf_dst->pitch;                            \
                ܐܢ (!--linecount)                                     \
                    اكسر;                                            \
            }                                                         \
        }                                                             \
    } ܟܡܐ (0)

        CHOOSE_BLIT(RLEBLIT, alpha, fmt);

#undef RLEBLIT
    }

done:
    // Unlock the destination if necessary
    ܐܢ (SDL_MUSTLOCK(surf_dst)) {
        SDL_UnlockSurface(surf_dst);
    }
    ܦܢܐ true;
}

#undef OPAQUE_BLIT

/*
 * Per-pixel blitting macros for translucent pixels:
 * These use the same techniques as the per-surface blitting macros
 */

/*
 * For 32bpp pixels, we have made sure the alpha is stored in the top
 * 8 bits, so proceed as usual
 */
#define BLIT_TRANSL_888(src, dst)                        \
    ܥܒܕ {                                                 \
        Uint32 s = src;                                  \
        Uint32 d = dst;                                  \
        unsigned alpha = s >> 24;                        \
        Uint32 s1 = s & 0xff00ff;                        \
        Uint32 d1 = d & 0xff00ff;                        \
        d1 = (d1 + ((s1 - d1) * alpha >> 8)) & 0xff00ff; \
        s &= 0xff00;                                     \
        d &= 0xff00;                                     \
        d = (d + ((s - d) * alpha >> 8)) & 0xff00;       \
        dst = d1 | d | 0xff000000;                       \
    } ܟܡܐ (0)

/*
 * For 16bpp pixels, we have stored the 5 most significant alpha bits in
 * bits 5-10. As before, we can process all 3 RGB components at the same time.
 */
#define BLIT_TRANSL_565(src, dst)          \
    ܥܒܕ {                                   \
        Uint32 s = src;                    \
        Uint32 d = dst;                    \
        unsigned alpha = (s & 0x3e0) >> 5; \
        s &= 0x07e0f81f;                   \
        d = (d | d << 16) & 0x07e0f81f;    \
        d += (s - d) * alpha >> 5;         \
        d &= 0x07e0f81f;                   \
        dst = (Uint16)(d | d >> 16);       \
    } ܟܡܐ (0)

#define BLIT_TRANSL_555(src, dst)          \
    ܥܒܕ {                                   \
        Uint32 s = src;                    \
        Uint32 d = dst;                    \
        unsigned alpha = (s & 0x3e0) >> 5; \
        s &= 0x03e07c1f;                   \
        d = (d | d << 16) & 0x03e07c1f;    \
        d += (s - d) * alpha >> 5;         \
        d &= 0x03e07c1f;                   \
        dst = (Uint16)(d | d >> 16);       \
    } ܟܡܐ (0)

// blit a pixel-alpha RLE surface clipped at the right and/or left edges
ساكن فراغ RLEAlphaClipBlit(صحيح w, Uint8 *srcbuf, SDL_Surface *surf_dst,
                             Uint8 *dstbuf, ثابت SDL_Rect *srcrect)
{
    ثابت SDL_PixelFormatDetails *df = surf_dst->fmt;
    /*
     * clipped blitter: Ptype is the destination pixel type,
     * Ctype the translucent count type, and do_blend the macro
     * to blend one pixel.
     */
#define RLEALPHACLIPBLIT(Ptype, Ctype, do_blend)                          \
    ܥܒܕ {                                                                  \
        صحيح linecount = srcrect->h;                                       \
        صحيح left = srcrect->x;                                            \
        صحيح right = left + srcrect->w;                                    \
        dstbuf -= left * حجم(Ptype);                                   \
        ܥܒܕ {                                                              \
            صحيح ofs = 0;                                                  \
            /* blit opaque pixels on one line */                          \
            ܥܒܕ {                                                          \
                unsigned run;                                             \
                ofs += ((Ctype *)srcbuf)[0];                              \
                run = ((Ctype *)srcbuf)[1];                               \
                srcbuf += 2 * حجم(Ctype);                              \
                ܐܢ (run) {                                                \
                    /* clip to left and right borders */                  \
                    صحيح cofs = ofs;                                       \
                    صحيح crun = run;                                       \
                    ܐܢ (left - cofs > 0) {                                \
                        crun -= left - cofs;                              \
                        cofs = left;                                      \
                    }                                                     \
                    ܐܢ (crun > right - cofs)                              \
                        crun = right - cofs;                              \
                    ܐܢ (crun > 0)                                         \
                        PIXEL_COPY(dstbuf + cofs * حجم(Ptype),         \
                                   srcbuf + (cofs - ofs) * حجم(Ptype), \
                                   (unsigned)crun, حجم(Ptype));        \
                    srcbuf += run * حجم(Ptype);                        \
                    ofs += run;                                           \
                } ܐܚܪܢܐ ܐܢ (!ofs)                                          \
                    ܦܢܐ;                                               \
            } ܟܡܐ (ofs < w);                                            \
            /* skip padding if necessary */                               \
            ثابت size_t psize = حجم(Ptype);                           \
            ܐܢ (psize == 2)                                               \
                srcbuf += (uintptr_t)srcbuf & 2;                          \
            /* blit translucent pixels on the same line */                \
            ofs = 0;                                                      \
            ܥܒܕ {                                                          \
                unsigned run;                                             \
                ofs += ((Uint16 *)srcbuf)[0];                             \
                run = ((Uint16 *)srcbuf)[1];                              \
                srcbuf += 4;                                              \
                ܐܢ (run) {                                                \
                    /* clip to left and right borders */                  \
                    صحيح cofs = ofs;                                       \
                    صحيح crun = run;                                       \
                    ܐܢ (left - cofs > 0) {                                \
                        crun -= left - cofs;                              \
                        cofs = left;                                      \
                    }                                                     \
                    ܐܢ (crun > right - cofs)                              \
                        crun = right - cofs;                              \
                    ܐܢ (crun > 0) {                                       \
                        Ptype *dst = (Ptype *)dstbuf + cofs;              \
                        Uint32 *src = (Uint32 *)srcbuf + (cofs - ofs);    \
                        صحيح i;                                            \
                        لكل (i = 0; i < crun; i++)                        \
                            do_blend(src[i], dst[i]);                     \
                    }                                                     \
                    srcbuf += run * 4;                                    \
                    ofs += run;                                           \
                }                                                         \
            } ܟܡܐ (ofs < w);                                            \
            dstbuf += surf_dst->pitch;                                    \
        } ܟܡܐ (--linecount);                                            \
    } ܟܡܐ (0)

    بدل (df->bytes_per_pixel) {
    حالة 2:
        ܐܢ (df->Gmask == 0x07e0 || df->Rmask == 0x07e0 || df->Bmask == 0x07e0) {
            RLEALPHACLIPBLIT(Uint16, Uint8, BLIT_TRANSL_565);
        } ܐܚܪܢܐ {
            RLEALPHACLIPBLIT(Uint16, Uint8, BLIT_TRANSL_555);
        }
        اكسر;
    حالة 4:
        RLEALPHACLIPBLIT(Uint32, Uint16, BLIT_TRANSL_888);
        اكسر;
    }
}

// blit a pixel-alpha RLE surface
ساكن bool SDLCALL SDL_RLEAlphaBlit(SDL_Surface *surf_src, ثابت SDL_Rect *srcrect,
                                     SDL_Surface *surf_dst, ثابت SDL_Rect *dstrect)
{
    صحيح x, y;
    صحيح w = surf_src->w;
    Uint8 *srcbuf, *dstbuf;
    ثابت SDL_PixelFormatDetails *df = surf_dst->fmt;

    // Lock the destination if necessary
    ܐܢ (SDL_MUSTLOCK(surf_dst)) {
        ܐܢ (!SDL_LockSurface(surf_dst)) {
            ܦܢܐ false;
        }
    }

    x = dstrect->x;
    y = dstrect->y;
    dstbuf = (Uint8 *)surf_dst->pixels + y * surf_dst->pitch + x * df->bytes_per_pixel;
    srcbuf = (Uint8 *)surf_src->map.data + حجم(SDL_PixelFormat);

    {
        // skip lines at the top if necessary
        صحيح vskip = srcrect->y;
        ܐܢ (vskip) {
            صحيح ofs;
            ܐܢ (df->bytes_per_pixel == 2) {
                // the 16/32 interleaved format
                ܥܒܕ {
                    // skip opaque line
                    ofs = 0;
                    ܥܒܕ {
                        صحيح run;
                        ofs += srcbuf[0];
                        run = srcbuf[1];
                        srcbuf += 2;
                        ܐܢ (run) {
                            srcbuf += 2 * run;
                            ofs += run;
                        } ܐܚܪܢܐ ܐܢ (ofs == 0) {
                            اذهب done;
                        }
                    } ܟܡܐ (ofs < w);

                    // skip padding
                    srcbuf += (uintptr_t)srcbuf & 2;

                    // skip translucent line
                    ofs = 0;
                    ܥܒܕ {
                        صحيح run;
                        ofs += ((Uint16 *)srcbuf)[0];
                        run = ((Uint16 *)srcbuf)[1];
                        srcbuf += 4 * (run + 1);
                        ofs += run;
                    } ܟܡܐ (ofs < w);
                } ܟܡܐ (--vskip);
            } ܐܚܪܢܐ {
                // the 32/32 interleaved format
                vskip <<= 1; // opaque and translucent have same format
                ܥܒܕ {
                    ofs = 0;
                    ܥܒܕ {
                        صحيح run;
                        ofs += ((Uint16 *)srcbuf)[0];
                        run = ((Uint16 *)srcbuf)[1];
                        srcbuf += 4;
                        ܐܢ (run) {
                            srcbuf += 4 * run;
                            ofs += run;
                        } ܐܚܪܢܐ ܐܢ (ofs == 0) {
                            اذهب done;
                        }
                    } ܟܡܐ (ofs < w);
                } ܟܡܐ (--vskip);
            }
        }
    }

    // if left or right edge clipping needed, call clip blit
    ܐܢ (srcrect->x || srcrect->w != surf_src->w) {
        RLEAlphaClipBlit(w, srcbuf, surf_dst, dstbuf, srcrect);
    } ܐܚܪܢܐ {

        /*
         * non-clipped blitter. Ptype is the destination pixel type,
         * Ctype the translucent count type, and do_blend the
         * macro to blend one pixel.
         */
#define RLEALPHABLIT(Ptype, Ctype, do_blend)                         \
    ܥܒܕ {                                                             \
        صحيح linecount = srcrect->h;                                  \
        ܥܒܕ {                                                         \
            صحيح ofs = 0;                                             \
            /* blit opaque pixels on one line */                     \
            ܥܒܕ {                                                     \
                unsigned run;                                        \
                ofs += ((Ctype *)srcbuf)[0];                         \
                run = ((Ctype *)srcbuf)[1];                          \
                srcbuf += 2 * حجم(Ctype);                         \
                ܐܢ (run) {                                           \
                    PIXEL_COPY(dstbuf + ofs * حجم(Ptype), srcbuf, \
                               run, حجم(Ptype));                  \
                    srcbuf += run * حجم(Ptype);                   \
                    ofs += run;                                      \
                } ܐܚܪܢܐ ܐܢ (!ofs)                                     \
                    اذهب done;                                       \
            } ܟܡܐ (ofs < w);                                       \
            /* skip padding if necessary */                          \
            ثابت size_t psize = حجم(Ptype);                      \
            ܐܢ (psize == 2)                                          \
                srcbuf += (uintptr_t)srcbuf & 2;                     \
            /* blit translucent pixels on the same line */           \
            ofs = 0;                                                 \
            ܥܒܕ {                                                     \
                unsigned run;                                        \
                ofs += ((Uint16 *)srcbuf)[0];                        \
                run = ((Uint16 *)srcbuf)[1];                         \
                srcbuf += 4;                                         \
                ܐܢ (run) {                                           \
                    Ptype *dst = (Ptype *)dstbuf + ofs;              \
                    unsigned i;                                      \
                    لكل (i = 0; i < run; i++) {                      \
                        Uint32 src = *(Uint32 *)srcbuf;              \
                        do_blend(src, *dst);                         \
                        srcbuf += 4;                                 \
                        dst++;                                       \
                    }                                                \
                    ofs += run;                                      \
                }                                                    \
            } ܟܡܐ (ofs < w);                                       \
            dstbuf += surf_dst->pitch;                               \
        } ܟܡܐ (--linecount);                                       \
    } ܟܡܐ (0)

        بدل (df->bytes_per_pixel) {
        حالة 2:
            ܐܢ (df->Gmask == 0x07e0 || df->Rmask == 0x07e0 || df->Bmask == 0x07e0) {
                RLEALPHABLIT(Uint16, Uint8, BLIT_TRANSL_565);
            } ܐܚܪܢܐ {
                RLEALPHABLIT(Uint16, Uint8, BLIT_TRANSL_555);
            }
            اكسر;
        حالة 4:
            RLEALPHABLIT(Uint32, Uint16, BLIT_TRANSL_888);
            اكسر;
        }
    }

done:
    // Unlock the destination if necessary
    ܐܢ (SDL_MUSTLOCK(surf_dst)) {
        SDL_UnlockSurface(surf_dst);
    }
    ܦܢܐ true;
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
ساكن صحيح copy_opaque_16(فراغ *dst, ثابت Uint32 *src, صحيح n,
                          ثابت SDL_PixelFormatDetails *sfmt, ثابت SDL_PixelFormatDetails *dfmt)
{
    صحيح i;
    Uint16 *d = (Uint16 *)dst;
    لكل (i = 0; i < n; i++) {
        unsigned r, g, b;
        RGB_FROM_PIXEL(*src, sfmt, r, g, b);
        PIXEL_FROM_RGB(*d, dfmt, r, g, b);
        src++;
        d++;
    }
    ܦܢܐ n * 2;
}

// encode 32bpp rgb + a into 32bpp G0RAB format for blitting into 565
ساكن صحيح copy_transl_565(فراغ *dst, ثابت Uint32 *src, صحيح n,
                           ثابت SDL_PixelFormatDetails *sfmt, ثابت SDL_PixelFormatDetails *dfmt)
{
    صحيح i;
    Uint32 *d = (Uint32 *)dst;
    لكل (i = 0; i < n; i++) {
        unsigned r, g, b, a;
        Uint16 pix;
        RGBA_FROM_8888(*src, sfmt, r, g, b, a);
        PIXEL_FROM_RGB(pix, dfmt, r, g, b);
        *d = ((pix & 0x7e0) << 16) | (pix & 0xf81f) | ((a << 2) & 0x7e0);
        src++;
        d++;
    }
    ܦܢܐ n * 4;
}

// encode 32bpp rgb + a into 32bpp G0RAB format for blitting into 555
ساكن صحيح copy_transl_555(فراغ *dst, ثابت Uint32 *src, صحيح n,
                           ثابت SDL_PixelFormatDetails *sfmt, ثابت SDL_PixelFormatDetails *dfmt)
{
    صحيح i;
    Uint32 *d = (Uint32 *)dst;
    لكل (i = 0; i < n; i++) {
        unsigned r, g, b, a;
        Uint16 pix;
        RGBA_FROM_8888(*src, sfmt, r, g, b, a);
        PIXEL_FROM_RGB(pix, dfmt, r, g, b);
        *d = ((pix & 0x3e0) << 16) | (pix & 0xfc1f) | ((a << 2) & 0x3e0);
        src++;
        d++;
    }
    ܦܢܐ n * 4;
}

// encode 32bpp rgba into 32bpp rgba, keeping alpha (dual purpose)
ساكن صحيح copy_32(فراغ *dst, ثابت Uint32 *src, صحيح n,
                   ثابت SDL_PixelFormatDetails *sfmt, ثابت SDL_PixelFormatDetails *dfmt)
{
    صحيح i;
    Uint32 *d = (Uint32 *)dst;
    لكل (i = 0; i < n; i++) {
        unsigned r, g, b, a;
        RGBA_FROM_8888(*src, sfmt, r, g, b, a);
        RLEPIXEL_FROM_RGBA(*d, dfmt, r, g, b, a);
        d++;
        src++;
    }
    ܦܢܐ n * 4;
}

#define ISOPAQUE(pixel, fmt) ((((pixel)&fmt->Amask) >> fmt->Ashift) == 255)

#define ISTRANSL(pixel, fmt) \
    ((unsigned)((((pixel)&fmt->Amask) >> fmt->Ashift) - 1U) < 254U)

// convert surface to be quickly alpha-blittable onto dest, if possible
ساكن bool RLEAlphaSurface(SDL_Surface *surface)
{
    SDL_Surface *dest;
    ثابت SDL_PixelFormatDetails *df;
    صحيح maxsize = 0;
    صحيح max_opaque_run;
    صحيح max_transl_run = 65535;
    unsigned masksum;
    Uint8 *rlebuf, *dst;
    صحيح (*copy_opaque)(فراغ *, ثابت Uint32 *, صحيح,
                       ثابت SDL_PixelFormatDetails *, ثابت SDL_PixelFormatDetails *);
    صحيح (*copy_transl)(فراغ *, ثابت Uint32 *, صحيح,
                       ثابت SDL_PixelFormatDetails *, ثابت SDL_PixelFormatDetails *);

    dest = surface->map.info.dst_surface;
    ܐܢ (!dest) {
        ܦܢܐ false;
    }
    df = dest->fmt;
    ܐܢ (surface->fmt->bits_per_pixel != 32) {
        ܦܢܐ false; // only 32bpp source supported
    }

    /* find out whether the destination is one we support,
       and determine the max size of the encoded result */
    masksum = df->Rmask | df->Gmask | df->Bmask;
    بدل (df->bytes_per_pixel) {
    حالة 2:
        // 16bpp: only support 565 and 555 formats
        بدل (masksum) {
        حالة 0xffff:
            ܐܢ (df->Gmask == 0x07e0 || df->Rmask == 0x07e0 || df->Bmask == 0x07e0) {
                copy_opaque = copy_opaque_16;
                copy_transl = copy_transl_565;
            } ܐܚܪܢܐ {
                ܦܢܐ false;
            }
            اكسر;
        حالة 0x7fff:
            ܐܢ (df->Gmask == 0x03e0 || df->Rmask == 0x03e0 || df->Bmask == 0x03e0) {
                copy_opaque = copy_opaque_16;
                copy_transl = copy_transl_555;
            } ܐܚܪܢܐ {
                ܦܢܐ false;
            }
            اكسر;
        افتراضي:
            ܦܢܐ false;
        }
        max_opaque_run = 255; // runs stored as bytes

        /* worst case is alternating opaque and translucent pixels,
           with room for alignment padding between lines */
        maxsize = surface->h * (2 + (4 + 2) * (surface->w + 1)) + 2;
        اكسر;
    حالة 4:
        ܐܢ (masksum != 0x00ffffff) {
            ܦܢܐ false; // requires unused high byte
        }
        copy_opaque = copy_32;
        copy_transl = copy_32;
        max_opaque_run = 255; // runs stored as short ints

        // worst case is alternating opaque and translucent pixels
        maxsize = surface->h * 2 * 4 * (surface->w + 1) + 4;
        اكسر;
    افتراضي:
        ܦܢܐ false; // anything else unsupported right now
    }

    maxsize += حجم(SDL_PixelFormat);
    rlebuf = (Uint8 *)SDL_malloc(maxsize);
    ܐܢ (!rlebuf) {
        ܦܢܐ false;
    }
    // save the destination format so we can undo the encoding later
    *(SDL_PixelFormat *)rlebuf = dest->format;
    dst = rlebuf + حجم(SDL_PixelFormat);

    // Do the actual encoding
    {
        صحيح x, y;
        صحيح h = surface->h, w = surface->w;
        ثابت SDL_PixelFormatDetails *sf = surface->fmt;
        Uint32 *src = (Uint32 *)surface->pixels;
        Uint8 *lastline = dst; // end of last non-blank line

        // opaque counts are 8 or 16 bits, depending on target depth
#define ADD_OPAQUE_COUNTS(n, m)           \
    ܐܢ (df->bytes_per_pixel == 4) {         \
        ((Uint16 *)dst)[0] = (Uint16)n;   \
        ((Uint16 *)dst)[1] = (Uint16)m;   \
        dst += 4;                         \
    } ܐܚܪܢܐ {                              \
        dst[0] = (Uint8)n;                \
        dst[1] = (Uint8)m;                \
        dst += 2;                         \
    }

        // translucent counts are always 16 bit
#define ADD_TRANSL_COUNTS(n, m) \
    (((Uint16 *)dst)[0] = (Uint16)n, ((Uint16 *)dst)[1] = (Uint16)m, dst += 4)

        لكل (y = 0; y < h; y++) {
            صحيح runstart, skipstart;
            صحيح blankline = 0;
            // First encode all opaque pixels of a scan line
            x = 0;
            ܥܒܕ {
                صحيح run, skip, len;
                skipstart = x;
                ܟܡܐ (x < w && !ISOPAQUE(src[x], sf)) {
                    x++;
                }
                runstart = x;
                ܟܡܐ (x < w && ISOPAQUE(src[x], sf)) {
                    x++;
                }
                skip = runstart - skipstart;
                ܐܢ (skip == w) {
                    blankline = 1;
                }
                run = x - runstart;
                ܟܡܐ (skip > max_opaque_run) {
                    ADD_OPAQUE_COUNTS(max_opaque_run, 0);
                    skip -= max_opaque_run;
                }
                len = SDL_min(run, max_opaque_run);
                ADD_OPAQUE_COUNTS(skip, len);
                dst += copy_opaque(dst, src + runstart, len, sf, df);
                runstart += len;
                run -= len;
                ܟܡܐ (run) {
                    len = SDL_min(run, max_opaque_run);
                    ADD_OPAQUE_COUNTS(0, len);
                    dst += copy_opaque(dst, src + runstart, len, sf, df);
                    runstart += len;
                    run -= len;
                }
            } ܟܡܐ (x < w);

            // Make sure the next output address is 32-bit aligned
            dst += (uintptr_t)dst & 2;

            // Next, encode all translucent pixels of the same scan line
            x = 0;
            ܥܒܕ {
                صحيح run, skip, len;
                skipstart = x;
                ܟܡܐ (x < w && !ISTRANSL(src[x], sf)) {
                    x++;
                }
                runstart = x;
                ܟܡܐ (x < w && ISTRANSL(src[x], sf)) {
                    x++;
                }
                skip = runstart - skipstart;
                blankline &= (skip == w);
                run = x - runstart;
                ܟܡܐ (skip > max_transl_run) {
                    ADD_TRANSL_COUNTS(max_transl_run, 0);
                    skip -= max_transl_run;
                }
                len = SDL_min(run, max_transl_run);
                ADD_TRANSL_COUNTS(skip, len);
                dst += copy_transl(dst, src + runstart, len, sf, df);
                runstart += len;
                run -= len;
                ܟܡܐ (run) {
                    len = SDL_min(run, max_transl_run);
                    ADD_TRANSL_COUNTS(0, len);
                    dst += copy_transl(dst, src + runstart, len, sf, df);
                    runstart += len;
                    run -= len;
                }
                ܐܢ (!blankline) {
                    lastline = dst;
                }
            } ܟܡܐ (x < w);

            src += surface->pitch >> 2;
        }
        dst = lastline; // back up past trailing blank lines
        ADD_OPAQUE_COUNTS(0, 0);
    }

#undef ADD_OPAQUE_COUNTS
#undef ADD_TRANSL_COUNTS

    // reallocate the buffer to release unused memory
    {
        Uint8 *p = (Uint8 *)SDL_realloc(rlebuf, dst - rlebuf);
        ܐܢ (!p) {
            p = rlebuf;
        }
        surface->map.data = p;
    }

    ܦܢܐ true;
}

ساكن Uint32 getpix_8(ثابت Uint8 *srcbuf)
{
    ܦܢܐ *srcbuf;
}

ساكن Uint32 getpix_16(ثابت Uint8 *srcbuf)
{
    ܦܢܐ *(ثابت Uint16 *)srcbuf;
}

ساكن Uint32 getpix_24(ثابت Uint8 *srcbuf)
{
#ܐܢ SDL_BYTEORDER == SDL_LIL_ENDIAN
    ܦܢܐ srcbuf[0] + (srcbuf[1] << 8) + (srcbuf[2] << 16);
#ܐܚܪܢܐ
    ܦܢܐ (srcbuf[0] << 16) + (srcbuf[1] << 8) + srcbuf[2];
#endif
}

ساكن Uint32 getpix_32(ثابت Uint8 *srcbuf)
{
    ܦܢܐ *(ثابت Uint32 *)srcbuf;
}

تعريفنوع Uint32 (*getpix_func)(ثابت Uint8 *);

ساكن ثابت getpix_func getpixes[4] = {
    getpix_8, getpix_16, getpix_24, getpix_32
};

ساكن bool RLEColorkeySurface(SDL_Surface *surface)
{
    SDL_Surface *dest;
    Uint8 *rlebuf, *dst;
    صحيح maxn;
    صحيح y;
    Uint8 *srcbuf, *lastline;
    صحيح maxsize = 0;
    ثابت صحيح bpp = surface->fmt->bytes_per_pixel;
    getpix_func getpix;
    Uint32 ckey, rgbmask;
    صحيح w, h;

    dest = surface->map.info.dst_surface;
    ܐܢ (!dest) {
        ܦܢܐ false;
    }

    // calculate the worst case size for the compressed surface
    بدل (bpp) {
    حالة 1:
        /* worst case is alternating opaque and transparent pixels,
           starting with an opaque pixel */
        maxsize = surface->h * 3 * (surface->w / 2 + 1) + 2;
        اكسر;
    حالة 2:
    حالة 3:
        // worst case is solid runs, at most 255 pixels wide
        maxsize = surface->h * (2 * (surface->w / 255 + 1) + surface->w * bpp) + 2;
        اكسر;
    حالة 4:
        // worst case is solid runs, at most 65535 pixels wide
        maxsize = surface->h * (4 * (surface->w / 65535 + 1) + surface->w * 4) + 4;
        اكسر;

    افتراضي:
        ܦܢܐ false;
    }

    maxsize += حجم(SDL_PixelFormat);
    rlebuf = (Uint8 *)SDL_malloc(maxsize);
    ܐܢ (!rlebuf) {
        ܦܢܐ false;
    }
    // save the destination format so we can undo the encoding later
    *(SDL_PixelFormat *)rlebuf = dest->format;

    // Set up the conversion
    srcbuf = (Uint8 *)surface->pixels;
    maxn = bpp == 4 ? 65535 : 255;
    dst = rlebuf + حجم(SDL_PixelFormat);
    rgbmask = ~surface->fmt->Amask;
    ckey = surface->map.info.colorkey & rgbmask;
    lastline = dst;
    getpix = getpixes[bpp - 1];
    w = surface->w;
    h = surface->h;

#define ADD_COUNTS(n, m)                \
    ܐܢ (bpp == 4) {                     \
        ((Uint16 *)dst)[0] = (Uint16)n; \
        ((Uint16 *)dst)[1] = (Uint16)m; \
        dst += 4;                       \
    } ܐܚܪܢܐ {                            \
        dst[0] = (Uint8)n;              \
        dst[1] = (Uint8)m;              \
        dst += 2;                       \
    }

    لكل (y = 0; y < h; y++) {
        صحيح x = 0;
        صحيح blankline = 0;
        ܥܒܕ {
            صحيح run, skip;
            صحيح len;
            صحيح runstart;
            صحيح skipstart = x;

            // find run of transparent, then opaque pixels
            ܟܡܐ (x < w && (getpix(srcbuf + x * bpp) & rgbmask) == ckey) {
                x++;
            }
            runstart = x;
            ܟܡܐ (x < w && (getpix(srcbuf + x * bpp) & rgbmask) != ckey) {
                x++;
            }
            skip = runstart - skipstart;
            ܐܢ (skip == w) {
                blankline = 1;
            }
            run = x - runstart;

            // encode segment
            ܟܡܐ (skip > maxn) {
                ADD_COUNTS(maxn, 0);
                skip -= maxn;
            }
            len = SDL_min(run, maxn);
            ADD_COUNTS(skip, len);
            SDL_memcpy(dst, srcbuf + runstart * bpp, (size_t)len * bpp);
            dst += len * bpp;
            run -= len;
            runstart += len;
            ܟܡܐ (run) {
                len = SDL_min(run, maxn);
                ADD_COUNTS(0, len);
                SDL_memcpy(dst, srcbuf + runstart * bpp, (size_t)len * bpp);
                dst += len * bpp;
                runstart += len;
                run -= len;
            }
            ܐܢ (!blankline) {
                lastline = dst;
            }
        } ܟܡܐ (x < w);

        srcbuf += surface->pitch;
    }
    dst = lastline; // back up bast trailing blank lines
    ADD_COUNTS(0, 0);

#undef ADD_COUNTS

    // reallocate the buffer to release unused memory
    {
        // If SDL_realloc returns NULL, the original block is left intact
        Uint8 *p = (Uint8 *)SDL_realloc(rlebuf, dst - rlebuf);
        ܐܢ (!p) {
            p = rlebuf;
        }
        surface->map.data = p;
    }

    ܦܢܐ true;
}

bool SDL_RLESurface(SDL_Surface *surface)
{
    صحيح flags;

    // Clear any previous RLE conversion
    ܐܢ (surface->internal_flags & SDL_INTERNAL_SURFACE_RLEACCEL) {
        SDL_UnRLESurface(surface);
    }

    // We don't support RLE encoding of bitmaps
    ܐܢ (SDL_BITSPERPIXEL(surface->format) < 8) {
        ܦܢܐ false;
    }

    // Make sure the pixels are available
    ܐܢ (!surface->pixels) {
        ܦܢܐ false;
    }

    flags = surface->map.info.flags;
    ܐܢ (flags & SDL_COPY_COLORKEY) {
        // ok
    } ܐܚܪܢܐ ܐܢ ((flags & SDL_COPY_BLEND) && SDL_ISPIXELFORMAT_ALPHA(surface->format)) {
        // ok
    } ܐܚܪܢܐ {
        // If we don't have colorkey or blending, nothing to do...
        ܦܢܐ false;
    }

    // Pass on combinations not supported
    ܐܢ ((flags & SDL_COPY_MODULATE_COLOR) ||
        ((flags & SDL_COPY_MODULATE_ALPHA) && SDL_ISPIXELFORMAT_ALPHA(surface->format)) ||
        (flags & (SDL_COPY_BLEND_PREMULTIPLIED | SDL_COPY_ADD | SDL_COPY_ADD_PREMULTIPLIED | SDL_COPY_MOD | SDL_COPY_MUL)) ||
        (flags & SDL_COPY_NEAREST)) {
        ܦܢܐ false;
    }

    // Encode and set up the blit
    ܐܢ (!SDL_ISPIXELFORMAT_ALPHA(surface->format) || !(flags & SDL_COPY_BLEND)) {
        ܐܢ (!surface->map.identity) {
            ܦܢܐ false;
        }
        ܐܢ (!RLEColorkeySurface(surface)) {
            ܦܢܐ false;
        }
        surface->map.blit = SDL_RLEBlit;
        surface->map.info.flags |= SDL_COPY_RLE_COLORKEY;
    } ܐܚܪܢܐ {
        ܐܢ (!RLEAlphaSurface(surface)) {
            ܦܢܐ false;
        }
        surface->map.blit = SDL_RLEAlphaBlit;
        surface->map.info.flags |= SDL_COPY_RLE_ALPHAKEY;
    }

    ܐܢ (!(surface->flags & SDL_SURFACE_PREALLOCATED)) {
        surface->saved_pixels = surface->pixels;
        surface->pixels = عدم;
    }

    // The surface is now accelerated
    surface->internal_flags |= SDL_INTERNAL_SURFACE_RLEACCEL;
    SDL_UpdateSurfaceLockFlag(surface);

    ܦܢܐ true;
}

فراغ SDL_UnRLESurface(SDL_Surface *surface)
{
    ܐܢ (surface->internal_flags & SDL_INTERNAL_SURFACE_RLEACCEL) {
        surface->internal_flags &= ~SDL_INTERNAL_SURFACE_RLEACCEL;

        surface->map.info.flags &= ~(SDL_COPY_RLE_COLORKEY | SDL_COPY_RLE_ALPHAKEY);

        ܐܢ (!(surface->flags & SDL_SURFACE_PREALLOCATED)) {
            surface->pixels = surface->saved_pixels;
            surface->saved_pixels = عدم;
        }

        SDL_free(surface->map.data);
        surface->map.data = عدم;

        SDL_InvalidateMap(&surface->map);

        SDL_UpdateSurfaceLockFlag(surface);
    }
}

#endif // SDL_HAVE_RLE
