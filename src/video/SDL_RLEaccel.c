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
#அந்தர்பாவ "SDL_internal.h"

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

#அந்தர்பாவ "SDL_sysvideo.h"
#அந்தர்பாவ "SDL_surface_c.h"
#அந்தர்பாவ "SDL_pixels_c.h"
#அந்தர்பாவ "SDL_RLEaccel_c.h"

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
    செய் {                                                     \
        முழு i;                                               \
        Uint32 *src = (Uint32 *)(from);                      \
        Uint32 *dst = (Uint32 *)(to);                        \
        க்கு (i = 0; i < (முழு)(length); i++) {                \
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
    } போது (0)

/*
 * For 16bpp pixels we can go a step further: put the middle component
 * in the high 16 bits of a 32 bit word, and process all three RGB
 * components at the same time. Since the smallest gap is here just
 * 5 bits, we have to scale alpha down to 5 bits as well.
 */
#define ALPHA_BLIT16_565(to, from, length, bpp, alpha) \
    செய் {                                               \
        முழு i;                                         \
        Uint16 *src = (Uint16 *)(from);                \
        Uint16 *dst = (Uint16 *)(to);                  \
        Uint32 ALPHA = alpha >> 3;                     \
        க்கு (i = 0; i < (முழு)(length); i++) {          \
            Uint32 s = *src++;                         \
            Uint32 d = *dst;                           \
            s = (s | s << 16) & 0x07e0f81f;            \
            d = (d | d << 16) & 0x07e0f81f;            \
            d += (s - d) * ALPHA >> 5;                 \
            d &= 0x07e0f81f;                           \
            *dst++ = (Uint16)(d | d >> 16);            \
        }                                              \
    } போது (0)

#define ALPHA_BLIT16_555(to, from, length, bpp, alpha) \
    செய் {                                               \
        முழு i;                                         \
        Uint16 *src = (Uint16 *)(from);                \
        Uint16 *dst = (Uint16 *)(to);                  \
        Uint32 ALPHA = alpha >> 3;                     \
        க்கு (i = 0; i < (முழு)(length); i++) {          \
            Uint32 s = *src++;                         \
            Uint32 d = *dst;                           \
            s = (s | s << 16) & 0x03e07c1f;            \
            d = (d | d << 16) & 0x03e07c1f;            \
            d += (s - d) * ALPHA >> 5;                 \
            d &= 0x03e07c1f;                           \
            *dst++ = (Uint16)(d | d >> 16);            \
        }                                              \
    } போது (0)

/*
 * The general slow catch-all function, for remaining depths and formats
 */
#எனில் SDL_BYTEORDER == SDL_BIG_ENDIAN
#define SET_RGB24(dst, d)      \
    dst[0] = (Uint8)(d >> 16); \
    dst[1] = (Uint8)(d >> 8);  \
    dst[2] = (Uint8)(d);
#இல்லையெனில்
#define SET_RGB24(dst, d)      \
    dst[0] = (Uint8)(d);       \
    dst[1] = (Uint8)(d >> 8);  \
    dst[2] = (Uint8)(d >> 16);
#endif
#define ALPHA_BLIT_ANY(to, from, length, bpp, alpha)             \
    செய் {                                                         \
        முழு i;                                                   \
        Uint8 *src = from;                                       \
        Uint8 *dst = to;                                         \
        க்கு (i = 0; i < (முழு)(length); i++) {                    \
            Uint32 s = 0, d = 0;                                 \
            unsigned rs, gs, bs, rd, gd, bd;                     \
            தேர்வு (bpp) {                                       \
            நிலை 2:                                              \
                s = *(Uint16 *)src;                              \
                d = *(Uint16 *)dst;                              \
                நிறுத்து;                                           \
            நிலை 3:                                              \
                s = GET_RGB24(src);                              \
                d = GET_RGB24(dst);                              \
                நிறுத்து;                                           \
            நிலை 4:                                              \
                s = *(Uint32 *)src;                              \
                d = *(Uint32 *)dst;                              \
                நிறுத்து;                                           \
            }                                                    \
            RGB_FROM_PIXEL(s, fmt, rs, gs, bs);                  \
            RGB_FROM_PIXEL(d, fmt, rd, gd, bd);                  \
            rd += (rs - rd) * alpha >> 8;                        \
            gd += (gs - gd) * alpha >> 8;                        \
            bd += (bs - bd) * alpha >> 8;                        \
            PIXEL_FROM_RGB(d, fmt, rd, gd, bd);                  \
            தேர்வு (bpp) {                                       \
            நிலை 2:                                              \
                *(Uint16 *)dst = (Uint16)d;                      \
                நிறுத்து;                                           \
            நிலை 3:                                              \
                SET_RGB24(dst, d);                               \
                நிறுத்து;                                           \
            நிலை 4:                                              \
                *(Uint32 *)dst = d;                              \
                நிறுத்து;                                           \
            }                                                    \
            src += bpp;                                          \
            dst += bpp;                                          \
        }                                                        \
    } போது (0)

/*
 * Special case: 50% alpha (alpha=128)
 * This is treated specially because it can be optimized very well, and
 * since it is good for many cases of semi-translucency.
 * The theory is to do all three components at the same time:
 * First zero the lowest bit of each component, which gives us room to
 * add them. Then shift right and add the sum of the lowest bits.
 */
#define ALPHA_BLIT32_888_50(to, from, length, bpp, alpha)                                 \
    செய் {                                                                                  \
        முழு i;                                                                            \
        Uint32 *src = (Uint32 *)(from);                                                   \
        Uint32 *dst = (Uint32 *)(to);                                                     \
        க்கு (i = 0; i < (முழு)(length); i++) {                                             \
            Uint32 s = *src++;                                                            \
            Uint32 d = *dst;                                                              \
            *dst++ = (((s & 0x00fefefe) + (d & 0x00fefefe)) >> 1) + (s & d & 0x00010101); \
        }                                                                                 \
    } போது (0)

/*
 * For 16bpp, we can actually blend two pixels in parallel, if we take
 * care to shift before we add, not after.
 */

// helper: blend a single 16 bit pixel at 50%
#define BLEND16_50(dst, src, mask)                           \
    செய் {                                                     \
        Uint32 s = *src++;                                   \
        Uint32 d = *dst;                                     \
        *dst++ = (Uint16)((((s & mask) + (d & mask)) >> 1) + \
                          (s & d & (~mask & 0xffff)));       \
    } போது (0)

// basic 16bpp blender. mask is the pixels to keep when adding.
#define ALPHA_BLIT16_50(to, from, length, bpp, alpha, mask)                                                                              \
    செய் {                                                                                                                                 \
        unsigned n = (length);                                                                                                           \
        Uint16 *src = (Uint16 *)(from);                                                                                                  \
        Uint16 *dst = (Uint16 *)(to);                                                                                                    \
        எனில் (((uintptr_t)src ^ (uintptr_t)dst) & 3) {                                                                                     \
            /* source and destination not in phase, blit one by one */                                                                   \
            போது (n--)                                                                                                                  \
                BLEND16_50(dst, src, mask);                                                                                              \
        } இல்லையெனில் {                                                                                                                         \
            எனில் ((uintptr_t)src & 3) {                                                                                                    \
                /* first odd pixel */                                                                                                    \
                BLEND16_50(dst, src, mask);                                                                                              \
                n--;                                                                                                                     \
            }                                                                                                                            \
            க்கு (; n > 1; n -= 2) {                                                                                                      \
                Uint32 s = *(Uint32 *)src;                                                                                               \
                Uint32 d = *(Uint32 *)dst;                                                                                               \
                *(Uint32 *)dst = ((s & (mask | mask << 16)) >> 1) + ((d & (mask | mask << 16)) >> 1) + (s & d & (~(mask | mask << 16))); \
                src += 2;                                                                                                                \
                dst += 2;                                                                                                                \
            }                                                                                                                            \
            எனில் (n)                                                                                                                       \
                BLEND16_50(dst, src, mask); /* last odd pixel */                                                                         \
        }                                                                                                                                \
    } போது (0)

#define ALPHA_BLIT16_565_50(to, from, length, bpp, alpha) \
    ALPHA_BLIT16_50(to, from, length, bpp, alpha, 0xf7deU)

#define ALPHA_BLIT16_555_50(to, from, length, bpp, alpha) \
    ALPHA_BLIT16_50(to, from, length, bpp, alpha, 0xfbdeU)

#define CHOOSE_BLIT(blitter, alpha, fmt)                                                                                                              \
    செய் {                                                                                                                                              \
        எனில் (alpha == 255) {                                                                                                                           \
            தேர்வு (fmt->bytes_per_pixel) {                                                                                                             \
            நிலை 1:                                                                                                                                   \
                blitter(1, Uint8, OPAQUE_BLIT);                                                                                                       \
                நிறுத்து;                                                                                                                                \
            நிலை 2:                                                                                                                                   \
                blitter(2, Uint8, OPAQUE_BLIT);                                                                                                       \
                நிறுத்து;                                                                                                                                \
            நிலை 3:                                                                                                                                   \
                blitter(3, Uint8, OPAQUE_BLIT);                                                                                                       \
                நிறுத்து;                                                                                                                                \
            நிலை 4:                                                                                                                                   \
                blitter(4, Uint16, OPAQUE_BLIT);                                                                                                      \
                நிறுத்து;                                                                                                                                \
            }                                                                                                                                         \
        } இல்லையெனில் {                                                                                                                                      \
            தேர்வு (fmt->bytes_per_pixel) {                                                                                                             \
            நிலை 1:                                                                                                                                   \
                /* No 8bpp alpha blitting */                                                                                                          \
                நிறுத்து;                                                                                                                                \
                                                                                                                                                      \
            நிலை 2:                                                                                                                                   \
                தேர்வு (fmt->Rmask | fmt->Gmask | fmt->Bmask) {                                                                                       \
                நிலை 0xffff:                                                                                                                          \
                    எனில் (fmt->Gmask == 0x07e0 || fmt->Rmask == 0x07e0 || fmt->Bmask == 0x07e0) {                                                       \
                        எனில் (alpha == 128) {                                                                                                           \
                            blitter(2, Uint8, ALPHA_BLIT16_565_50);                                                                                   \
                        } இல்லையெனில் {                                                                                                                      \
                            blitter(2, Uint8, ALPHA_BLIT16_565);                                                                                      \
                        }                                                                                                                             \
                    } இல்லையெனில் {                                                                                                                          \
                        செல் general16;                                                                                                               \
                    }                                                                                                                                 \
                    நிறுத்து;                                                                                                                            \
                                                                                                                                                      \
                நிலை 0x7fff:                                                                                                                          \
                    எனில் (fmt->Gmask == 0x03e0 || fmt->Rmask == 0x03e0 || fmt->Bmask == 0x03e0) {                                                       \
                        எனில் (alpha == 128) {                                                                                                           \
                            blitter(2, Uint8, ALPHA_BLIT16_555_50);                                                                                   \
                        } இல்லையெனில் {                                                                                                                      \
                            blitter(2, Uint8, ALPHA_BLIT16_555);                                                                                      \
                        }                                                                                                                             \
                        நிறுத்து;                                                                                                                        \
                    } இல்லையெனில் {                                                                                                                          \
                        செல் general16;                                                                                                               \
                    }                                                                                                                                 \
                    நிறுத்து;                                                                                                                            \
                                                                                                                                                      \
                இயல்பு:                                                                                                                              \
                general16:                                                                                                                            \
                    blitter(2, Uint8, ALPHA_BLIT_ANY);                                                                                                \
                }                                                                                                                                     \
                நிறுத்து;                                                                                                                                \
                                                                                                                                                      \
            நிலை 3:                                                                                                                                   \
                blitter(3, Uint8, ALPHA_BLIT_ANY);                                                                                                    \
                நிறுத்து;                                                                                                                                \
                                                                                                                                                      \
            நிலை 4:                                                                                                                                   \
                எனில் ((fmt->Rmask | fmt->Gmask | fmt->Bmask) == 0x00ffffff && (fmt->Gmask == 0xff00 || fmt->Rmask == 0xff00 || fmt->Bmask == 0xff00)) { \
                    எனில் (alpha == 128) {                                                                                                               \
                        blitter(4, Uint16, ALPHA_BLIT32_888_50);                                                                                      \
                    } இல்லையெனில் {                                                                                                                          \
                        blitter(4, Uint16, ALPHA_BLIT32_888);                                                                                         \
                    }                                                                                                                                 \
                } இல்லையெனில் {                                                                                                                              \
                    blitter(4, Uint16, ALPHA_BLIT_ANY);                                                                                               \
                }                                                                                                                                     \
                நிறுத்து;                                                                                                                                \
            }                                                                                                                                         \
        }                                                                                                                                             \
    } போது (0)

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
    செய் {                                                                   \
        முழு linecount = srcrect->h;                                        \
        முழு ofs = 0;                                                       \
        முழு இடது = srcrect->x;                                             \
        முழு வலது = இடது + srcrect->w;                                     \
        dstbuf -= இடது * bpp;                                              \
        க்கு (;;) {                                                         \
            முழு run;                                                       \
            ofs += *(Type *)srcbuf;                                        \
            run = ((Type *)srcbuf)[1];                                     \
            srcbuf += 2 * அளவு(Type);                                    \
            எனில் (run) {                                                     \
                /* clip to left and right borders */                       \
                எனில் (ofs < வலது) {                                         \
                    முழு start = 0;                                         \
                    முழு len = run;                                         \
                    முழு startcol;                                          \
                    எனில் (இடது - ofs > 0) {                                  \
                        start = இடது - ofs;                                \
                        len -= start;                                      \
                        எனில் (len <= 0)                                      \
                            செல் nocopy##bpp##do_blit;                     \
                    }                                                      \
                    startcol = ofs + start;                                \
                    எனில் (len > வலது - startcol)                            \
                        len = வலது - startcol;                            \
                    do_blit(dstbuf + startcol * bpp, srcbuf + start * bpp, \
                            len, bpp, alpha);                              \
                }                                                          \
                nocopy##bpp##do_blit : srcbuf += run * bpp;                \
                ofs += run;                                                \
            } இல்லையெனில் எனில் (!ofs) {                                             \
                நிறுத்து;                                                     \
            }                                                              \
                                                                           \
            எனில் (ofs == w) {                                                \
                ofs = 0;                                                   \
                dstbuf += surf_dst->pitch;                                 \
                எனில் (!--linecount) {                                        \
                    நிறுத்து;                                                 \
                }                                                          \
            }                                                              \
        }                                                                  \
    } போது (0)

நிலையான வெறுமை RLEClipBlit(முழு w, Uint8 *srcbuf, SDL_Surface *surf_dst,
                        Uint8 *dstbuf, மாறிலி SDL_Rect *srcrect, unsigned alpha)
{
    மாறிலி SDL_PixelFormatDetails *fmt = surf_dst->fmt;

    CHOOSE_BLIT(RLECLIPBLIT, alpha, fmt);
}

#undef RLECLIPBLIT

// blit a colorkeyed RLE surface
நிலையான bool SDLCALL SDL_RLEBlit(SDL_Surface *surf_src, மாறிலி SDL_Rect *srcrect,
                                SDL_Surface *surf_dst, மாறிலி SDL_Rect *dstrect)
{
    Uint8 *dstbuf;
    Uint8 *srcbuf;
    முழு x, y;
    முழு w = surf_src->w;
    unsigned alpha;

    // Lock the destination if necessary
    எனில் (SDL_MUSTLOCK(surf_dst)) {
        எனில் (!SDL_LockSurface(surf_dst)) {
            திரும்பு false;
        }
    }

    // Set up the source and destination pointers
    x = dstrect->x;
    y = dstrect->y;
    dstbuf = (Uint8 *)surf_dst->pixels + y * surf_dst->pitch + x * surf_src->fmt->bytes_per_pixel;
    srcbuf = (Uint8 *)surf_src->map.data + அளவு(SDL_PixelFormat);

    {
        // skip lines at the top if necessary
        முழு vskip = srcrect->y;
        முழு ofs = 0;
        எனில் (vskip) {

#define RLESKIP(bpp, Type)          \
    க்கு (;;) {                      \
        முழு run;                    \
        ofs += *(Type *)srcbuf;     \
        run = ((Type *)srcbuf)[1];  \
        srcbuf += அளவு(Type) * 2; \
        எனில் (run) {                  \
            srcbuf += run * bpp;    \
            ofs += run;             \
        } இல்லையெனில் எனில் (!ofs)            \
            செல் done;              \
        எனில் (ofs == w) {             \
            ofs = 0;                \
            எனில் (!--vskip)           \
                நிறுத்து;              \
        }                           \
    }

            தேர்வு (surf_src->fmt->bytes_per_pixel) {
            நிலை 1:
                RLESKIP(1, Uint8);
                நிறுத்து;
            நிலை 2:
                RLESKIP(2, Uint8);
                நிறுத்து;
            நிலை 3:
                RLESKIP(3, Uint8);
                நிறுத்து;
            நிலை 4:
                RLESKIP(4, Uint16);
                நிறுத்து;
            }

#undef RLESKIP
        }
    }

    alpha = surf_src->map.info.a;
    // if left or right edge clipping needed, call clip blit
    எனில் (srcrect->x || srcrect->w != surf_src->w) {
        RLEClipBlit(w, srcbuf, surf_dst, dstbuf, srcrect, alpha);
    } இல்லையெனில் {
        மாறிலி SDL_PixelFormatDetails *fmt = surf_src->fmt;

#define RLEBLIT(bpp, Type, do_blit)                                   \
    செய் {                                                              \
        முழு linecount = srcrect->h;                                   \
        முழு ofs = 0;                                                  \
        க்கு (;;) {                                                    \
            unsigned run;                                             \
            ofs += *(Type *)srcbuf;                                   \
            run = ((Type *)srcbuf)[1];                                \
            srcbuf += 2 * அளவு(Type);                               \
            எனில் (run) {                                                \
                do_blit(dstbuf + ofs * bpp, srcbuf, run, bpp, alpha); \
                srcbuf += run * bpp;                                  \
                ofs += run;                                           \
            } இல்லையெனில் எனில் (!ofs)                                          \
                நிறுத்து;                                                \
            எனில் (ofs == w) {                                           \
                ofs = 0;                                              \
                dstbuf += surf_dst->pitch;                            \
                எனில் (!--linecount)                                     \
                    நிறுத்து;                                            \
            }                                                         \
        }                                                             \
    } போது (0)

        CHOOSE_BLIT(RLEBLIT, alpha, fmt);

#undef RLEBLIT
    }

done:
    // Unlock the destination if necessary
    எனில் (SDL_MUSTLOCK(surf_dst)) {
        SDL_UnlockSurface(surf_dst);
    }
    திரும்பு true;
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
    செய் {                                                 \
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
    } போது (0)

/*
 * For 16bpp pixels, we have stored the 5 most significant alpha bits in
 * bits 5-10. As before, we can process all 3 RGB components at the same time.
 */
#define BLIT_TRANSL_565(src, dst)          \
    செய் {                                   \
        Uint32 s = src;                    \
        Uint32 d = dst;                    \
        unsigned alpha = (s & 0x3e0) >> 5; \
        s &= 0x07e0f81f;                   \
        d = (d | d << 16) & 0x07e0f81f;    \
        d += (s - d) * alpha >> 5;         \
        d &= 0x07e0f81f;                   \
        dst = (Uint16)(d | d >> 16);       \
    } போது (0)

#define BLIT_TRANSL_555(src, dst)          \
    செய் {                                   \
        Uint32 s = src;                    \
        Uint32 d = dst;                    \
        unsigned alpha = (s & 0x3e0) >> 5; \
        s &= 0x03e07c1f;                   \
        d = (d | d << 16) & 0x03e07c1f;    \
        d += (s - d) * alpha >> 5;         \
        d &= 0x03e07c1f;                   \
        dst = (Uint16)(d | d >> 16);       \
    } போது (0)

// blit a pixel-alpha RLE surface clipped at the right and/or left edges
நிலையான வெறுமை RLEAlphaClipBlit(முழு w, Uint8 *srcbuf, SDL_Surface *surf_dst,
                             Uint8 *dstbuf, மாறிலி SDL_Rect *srcrect)
{
    மாறிலி SDL_PixelFormatDetails *df = surf_dst->fmt;
    /*
     * clipped blitter: Ptype is the destination pixel type,
     * Ctype the translucent count type, and do_blend the macro
     * to blend one pixel.
     */
#define RLEALPHACLIPBLIT(Ptype, Ctype, do_blend)                          \
    செய் {                                                                  \
        முழு linecount = srcrect->h;                                       \
        முழு இடது = srcrect->x;                                            \
        முழு வலது = இடது + srcrect->w;                                    \
        dstbuf -= இடது * அளவு(Ptype);                                   \
        செய் {                                                              \
            முழு ofs = 0;                                                  \
            /* blit opaque pixels on one line */                          \
            செய் {                                                          \
                unsigned run;                                             \
                ofs += ((Ctype *)srcbuf)[0];                              \
                run = ((Ctype *)srcbuf)[1];                               \
                srcbuf += 2 * அளவு(Ctype);                              \
                எனில் (run) {                                                \
                    /* clip to left and right borders */                  \
                    முழு cofs = ofs;                                       \
                    முழு crun = run;                                       \
                    எனில் (இடது - cofs > 0) {                                \
                        crun -= இடது - cofs;                              \
                        cofs = இடது;                                      \
                    }                                                     \
                    எனில் (crun > வலது - cofs)                              \
                        crun = வலது - cofs;                              \
                    எனில் (crun > 0)                                         \
                        PIXEL_COPY(dstbuf + cofs * அளவு(Ptype),         \
                                   srcbuf + (cofs - ofs) * அளவு(Ptype), \
                                   (unsigned)crun, அளவு(Ptype));        \
                    srcbuf += run * அளவு(Ptype);                        \
                    ofs += run;                                           \
                } இல்லையெனில் எனில் (!ofs)                                          \
                    திரும்பு;                                               \
            } போது (ofs < w);                                            \
            /* skip padding if necessary */                               \
            மாறிலி size_t psize = அளவு(Ptype);                           \
            எனில் (psize == 2)                                               \
                srcbuf += (uintptr_t)srcbuf & 2;                          \
            /* blit translucent pixels on the same line */                \
            ofs = 0;                                                      \
            செய் {                                                          \
                unsigned run;                                             \
                ofs += ((Uint16 *)srcbuf)[0];                             \
                run = ((Uint16 *)srcbuf)[1];                              \
                srcbuf += 4;                                              \
                எனில் (run) {                                                \
                    /* clip to left and right borders */                  \
                    முழு cofs = ofs;                                       \
                    முழு crun = run;                                       \
                    எனில் (இடது - cofs > 0) {                                \
                        crun -= இடது - cofs;                              \
                        cofs = இடது;                                      \
                    }                                                     \
                    எனில் (crun > வலது - cofs)                              \
                        crun = வலது - cofs;                              \
                    எனில் (crun > 0) {                                       \
                        Ptype *dst = (Ptype *)dstbuf + cofs;              \
                        Uint32 *src = (Uint32 *)srcbuf + (cofs - ofs);    \
                        முழு i;                                            \
                        க்கு (i = 0; i < crun; i++)                        \
                            do_blend(src[i], dst[i]);                     \
                    }                                                     \
                    srcbuf += run * 4;                                    \
                    ofs += run;                                           \
                }                                                         \
            } போது (ofs < w);                                            \
            dstbuf += surf_dst->pitch;                                    \
        } போது (--linecount);                                            \
    } போது (0)

    தேர்வு (df->bytes_per_pixel) {
    நிலை 2:
        எனில் (df->Gmask == 0x07e0 || df->Rmask == 0x07e0 || df->Bmask == 0x07e0) {
            RLEALPHACLIPBLIT(Uint16, Uint8, BLIT_TRANSL_565);
        } இல்லையெனில் {
            RLEALPHACLIPBLIT(Uint16, Uint8, BLIT_TRANSL_555);
        }
        நிறுத்து;
    நிலை 4:
        RLEALPHACLIPBLIT(Uint32, Uint16, BLIT_TRANSL_888);
        நிறுத்து;
    }
}

// blit a pixel-alpha RLE surface
நிலையான bool SDLCALL SDL_RLEAlphaBlit(SDL_Surface *surf_src, மாறிலி SDL_Rect *srcrect,
                                     SDL_Surface *surf_dst, மாறிலி SDL_Rect *dstrect)
{
    முழு x, y;
    முழு w = surf_src->w;
    Uint8 *srcbuf, *dstbuf;
    மாறிலி SDL_PixelFormatDetails *df = surf_dst->fmt;

    // Lock the destination if necessary
    எனில் (SDL_MUSTLOCK(surf_dst)) {
        எனில் (!SDL_LockSurface(surf_dst)) {
            திரும்பு false;
        }
    }

    x = dstrect->x;
    y = dstrect->y;
    dstbuf = (Uint8 *)surf_dst->pixels + y * surf_dst->pitch + x * df->bytes_per_pixel;
    srcbuf = (Uint8 *)surf_src->map.data + அளவு(SDL_PixelFormat);

    {
        // skip lines at the top if necessary
        முழு vskip = srcrect->y;
        எனில் (vskip) {
            முழு ofs;
            எனில் (df->bytes_per_pixel == 2) {
                // the 16/32 interleaved format
                செய் {
                    // skip opaque line
                    ofs = 0;
                    செய் {
                        முழு run;
                        ofs += srcbuf[0];
                        run = srcbuf[1];
                        srcbuf += 2;
                        எனில் (run) {
                            srcbuf += 2 * run;
                            ofs += run;
                        } இல்லையெனில் எனில் (ofs == 0) {
                            செல் done;
                        }
                    } போது (ofs < w);

                    // skip padding
                    srcbuf += (uintptr_t)srcbuf & 2;

                    // skip translucent line
                    ofs = 0;
                    செய் {
                        முழு run;
                        ofs += ((Uint16 *)srcbuf)[0];
                        run = ((Uint16 *)srcbuf)[1];
                        srcbuf += 4 * (run + 1);
                        ofs += run;
                    } போது (ofs < w);
                } போது (--vskip);
            } இல்லையெனில் {
                // the 32/32 interleaved format
                vskip <<= 1; // opaque and translucent have same format
                செய் {
                    ofs = 0;
                    செய் {
                        முழு run;
                        ofs += ((Uint16 *)srcbuf)[0];
                        run = ((Uint16 *)srcbuf)[1];
                        srcbuf += 4;
                        எனில் (run) {
                            srcbuf += 4 * run;
                            ofs += run;
                        } இல்லையெனில் எனில் (ofs == 0) {
                            செல் done;
                        }
                    } போது (ofs < w);
                } போது (--vskip);
            }
        }
    }

    // if left or right edge clipping needed, call clip blit
    எனில் (srcrect->x || srcrect->w != surf_src->w) {
        RLEAlphaClipBlit(w, srcbuf, surf_dst, dstbuf, srcrect);
    } இல்லையெனில் {

        /*
         * non-clipped blitter. Ptype is the destination pixel type,
         * Ctype the translucent count type, and do_blend the
         * macro to blend one pixel.
         */
#define RLEALPHABLIT(Ptype, Ctype, do_blend)                         \
    செய் {                                                             \
        முழு linecount = srcrect->h;                                  \
        செய் {                                                         \
            முழு ofs = 0;                                             \
            /* blit opaque pixels on one line */                     \
            செய் {                                                     \
                unsigned run;                                        \
                ofs += ((Ctype *)srcbuf)[0];                         \
                run = ((Ctype *)srcbuf)[1];                          \
                srcbuf += 2 * அளவு(Ctype);                         \
                எனில் (run) {                                           \
                    PIXEL_COPY(dstbuf + ofs * அளவு(Ptype), srcbuf, \
                               run, அளவு(Ptype));                  \
                    srcbuf += run * அளவு(Ptype);                   \
                    ofs += run;                                      \
                } இல்லையெனில் எனில் (!ofs)                                     \
                    செல் done;                                       \
            } போது (ofs < w);                                       \
            /* skip padding if necessary */                          \
            மாறிலி size_t psize = அளவு(Ptype);                      \
            எனில் (psize == 2)                                          \
                srcbuf += (uintptr_t)srcbuf & 2;                     \
            /* blit translucent pixels on the same line */           \
            ofs = 0;                                                 \
            செய் {                                                     \
                unsigned run;                                        \
                ofs += ((Uint16 *)srcbuf)[0];                        \
                run = ((Uint16 *)srcbuf)[1];                         \
                srcbuf += 4;                                         \
                எனில் (run) {                                           \
                    Ptype *dst = (Ptype *)dstbuf + ofs;              \
                    unsigned i;                                      \
                    க்கு (i = 0; i < run; i++) {                      \
                        Uint32 src = *(Uint32 *)srcbuf;              \
                        do_blend(src, *dst);                         \
                        srcbuf += 4;                                 \
                        dst++;                                       \
                    }                                                \
                    ofs += run;                                      \
                }                                                    \
            } போது (ofs < w);                                       \
            dstbuf += surf_dst->pitch;                               \
        } போது (--linecount);                                       \
    } போது (0)

        தேர்வு (df->bytes_per_pixel) {
        நிலை 2:
            எனில் (df->Gmask == 0x07e0 || df->Rmask == 0x07e0 || df->Bmask == 0x07e0) {
                RLEALPHABLIT(Uint16, Uint8, BLIT_TRANSL_565);
            } இல்லையெனில் {
                RLEALPHABLIT(Uint16, Uint8, BLIT_TRANSL_555);
            }
            நிறுத்து;
        நிலை 4:
            RLEALPHABLIT(Uint32, Uint16, BLIT_TRANSL_888);
            நிறுத்து;
        }
    }

done:
    // Unlock the destination if necessary
    எனில் (SDL_MUSTLOCK(surf_dst)) {
        SDL_UnlockSurface(surf_dst);
    }
    திரும்பு true;
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
நிலையான முழு copy_opaque_16(வெறுமை *dst, மாறிலி Uint32 *src, முழு n,
                          மாறிலி SDL_PixelFormatDetails *sfmt, மாறிலி SDL_PixelFormatDetails *dfmt)
{
    முழு i;
    Uint16 *d = (Uint16 *)dst;
    க்கு (i = 0; i < n; i++) {
        unsigned r, g, b;
        RGB_FROM_PIXEL(*src, sfmt, r, g, b);
        PIXEL_FROM_RGB(*d, dfmt, r, g, b);
        src++;
        d++;
    }
    திரும்பு n * 2;
}

// encode 32bpp rgb + a into 32bpp G0RAB format for blitting into 565
நிலையான முழு copy_transl_565(வெறுமை *dst, மாறிலி Uint32 *src, முழு n,
                           மாறிலி SDL_PixelFormatDetails *sfmt, மாறிலி SDL_PixelFormatDetails *dfmt)
{
    முழு i;
    Uint32 *d = (Uint32 *)dst;
    க்கு (i = 0; i < n; i++) {
        unsigned r, g, b, a;
        Uint16 pix;
        RGBA_FROM_8888(*src, sfmt, r, g, b, a);
        PIXEL_FROM_RGB(pix, dfmt, r, g, b);
        *d = ((pix & 0x7e0) << 16) | (pix & 0xf81f) | ((a << 2) & 0x7e0);
        src++;
        d++;
    }
    திரும்பு n * 4;
}

// encode 32bpp rgb + a into 32bpp G0RAB format for blitting into 555
நிலையான முழு copy_transl_555(வெறுமை *dst, மாறிலி Uint32 *src, முழு n,
                           மாறிலி SDL_PixelFormatDetails *sfmt, மாறிலி SDL_PixelFormatDetails *dfmt)
{
    முழு i;
    Uint32 *d = (Uint32 *)dst;
    க்கு (i = 0; i < n; i++) {
        unsigned r, g, b, a;
        Uint16 pix;
        RGBA_FROM_8888(*src, sfmt, r, g, b, a);
        PIXEL_FROM_RGB(pix, dfmt, r, g, b);
        *d = ((pix & 0x3e0) << 16) | (pix & 0xfc1f) | ((a << 2) & 0x3e0);
        src++;
        d++;
    }
    திரும்பு n * 4;
}

// encode 32bpp rgba into 32bpp rgba, keeping alpha (dual purpose)
நிலையான முழு copy_32(வெறுமை *dst, மாறிலி Uint32 *src, முழு n,
                   மாறிலி SDL_PixelFormatDetails *sfmt, மாறிலி SDL_PixelFormatDetails *dfmt)
{
    முழு i;
    Uint32 *d = (Uint32 *)dst;
    க்கு (i = 0; i < n; i++) {
        unsigned r, g, b, a;
        RGBA_FROM_8888(*src, sfmt, r, g, b, a);
        RLEPIXEL_FROM_RGBA(*d, dfmt, r, g, b, a);
        d++;
        src++;
    }
    திரும்பு n * 4;
}

#define ISOPAQUE(pixel, fmt) ((((pixel)&fmt->Amask) >> fmt->Ashift) == 255)

#define ISTRANSL(pixel, fmt) \
    ((unsigned)((((pixel)&fmt->Amask) >> fmt->Ashift) - 1U) < 254U)

// convert surface to be quickly alpha-blittable onto dest, if possible
நிலையான bool RLEAlphaSurface(SDL_Surface *surface)
{
    SDL_Surface *dest;
    மாறிலி SDL_PixelFormatDetails *df;
    முழு maxsize = 0;
    முழு max_opaque_run;
    முழு max_transl_run = 65535;
    unsigned masksum;
    Uint8 *rlebuf, *dst;
    முழு (*copy_opaque)(வெறுமை *, மாறிலி Uint32 *, முழு,
                       மாறிலி SDL_PixelFormatDetails *, மாறிலி SDL_PixelFormatDetails *);
    முழு (*copy_transl)(வெறுமை *, மாறிலி Uint32 *, முழு,
                       மாறிலி SDL_PixelFormatDetails *, மாறிலி SDL_PixelFormatDetails *);

    dest = surface->map.info.dst_surface;
    எனில் (!dest) {
        திரும்பு false;
    }
    df = dest->fmt;
    எனில் (surface->fmt->bits_per_pixel != 32) {
        திரும்பு false; // only 32bpp source supported
    }

    /* find out whether the destination is one we support,
       and determine the max size of the encoded result */
    masksum = df->Rmask | df->Gmask | df->Bmask;
    தேர்வு (df->bytes_per_pixel) {
    நிலை 2:
        // 16bpp: only support 565 and 555 formats
        தேர்வு (masksum) {
        நிலை 0xffff:
            எனில் (df->Gmask == 0x07e0 || df->Rmask == 0x07e0 || df->Bmask == 0x07e0) {
                copy_opaque = copy_opaque_16;
                copy_transl = copy_transl_565;
            } இல்லையெனில் {
                திரும்பு false;
            }
            நிறுத்து;
        நிலை 0x7fff:
            எனில் (df->Gmask == 0x03e0 || df->Rmask == 0x03e0 || df->Bmask == 0x03e0) {
                copy_opaque = copy_opaque_16;
                copy_transl = copy_transl_555;
            } இல்லையெனில் {
                திரும்பு false;
            }
            நிறுத்து;
        இயல்பு:
            திரும்பு false;
        }
        max_opaque_run = 255; // runs stored as bytes

        /* worst case is alternating opaque and translucent pixels,
           with room for alignment padding between lines */
        maxsize = surface->h * (2 + (4 + 2) * (surface->w + 1)) + 2;
        நிறுத்து;
    நிலை 4:
        எனில் (masksum != 0x00ffffff) {
            திரும்பு false; // requires unused high byte
        }
        copy_opaque = copy_32;
        copy_transl = copy_32;
        max_opaque_run = 255; // runs stored as short ints

        // worst case is alternating opaque and translucent pixels
        maxsize = surface->h * 2 * 4 * (surface->w + 1) + 4;
        நிறுத்து;
    இயல்பு:
        திரும்பு false; // anything else unsupported right now
    }

    maxsize += அளவு(SDL_PixelFormat);
    rlebuf = (Uint8 *)SDL_malloc(maxsize);
    எனில் (!rlebuf) {
        திரும்பு false;
    }
    // save the destination format so we can undo the encoding later
    *(SDL_PixelFormat *)rlebuf = dest->format;
    dst = rlebuf + அளவு(SDL_PixelFormat);

    // Do the actual encoding
    {
        முழு x, y;
        முழு h = surface->h, w = surface->w;
        மாறிலி SDL_PixelFormatDetails *sf = surface->fmt;
        Uint32 *src = (Uint32 *)surface->pixels;
        Uint8 *lastline = dst; // end of last non-blank line

        // opaque counts are 8 or 16 bits, depending on target depth
#define ADD_OPAQUE_COUNTS(n, m)           \
    எனில் (df->bytes_per_pixel == 4) {         \
        ((Uint16 *)dst)[0] = (Uint16)n;   \
        ((Uint16 *)dst)[1] = (Uint16)m;   \
        dst += 4;                         \
    } இல்லையெனில் {                              \
        dst[0] = (Uint8)n;                \
        dst[1] = (Uint8)m;                \
        dst += 2;                         \
    }

        // translucent counts are always 16 bit
#define ADD_TRANSL_COUNTS(n, m) \
    (((Uint16 *)dst)[0] = (Uint16)n, ((Uint16 *)dst)[1] = (Uint16)m, dst += 4)

        க்கு (y = 0; y < h; y++) {
            முழு runstart, skipstart;
            முழு blankline = 0;
            // First encode all opaque pixels of a scan line
            x = 0;
            செய் {
                முழு run, skip, len;
                skipstart = x;
                போது (x < w && !ISOPAQUE(src[x], sf)) {
                    x++;
                }
                runstart = x;
                போது (x < w && ISOPAQUE(src[x], sf)) {
                    x++;
                }
                skip = runstart - skipstart;
                எனில் (skip == w) {
                    blankline = 1;
                }
                run = x - runstart;
                போது (skip > max_opaque_run) {
                    ADD_OPAQUE_COUNTS(max_opaque_run, 0);
                    skip -= max_opaque_run;
                }
                len = SDL_min(run, max_opaque_run);
                ADD_OPAQUE_COUNTS(skip, len);
                dst += copy_opaque(dst, src + runstart, len, sf, df);
                runstart += len;
                run -= len;
                போது (run) {
                    len = SDL_min(run, max_opaque_run);
                    ADD_OPAQUE_COUNTS(0, len);
                    dst += copy_opaque(dst, src + runstart, len, sf, df);
                    runstart += len;
                    run -= len;
                }
            } போது (x < w);

            // Make sure the next output address is 32-bit aligned
            dst += (uintptr_t)dst & 2;

            // Next, encode all translucent pixels of the same scan line
            x = 0;
            செய் {
                முழு run, skip, len;
                skipstart = x;
                போது (x < w && !ISTRANSL(src[x], sf)) {
                    x++;
                }
                runstart = x;
                போது (x < w && ISTRANSL(src[x], sf)) {
                    x++;
                }
                skip = runstart - skipstart;
                blankline &= (skip == w);
                run = x - runstart;
                போது (skip > max_transl_run) {
                    ADD_TRANSL_COUNTS(max_transl_run, 0);
                    skip -= max_transl_run;
                }
                len = SDL_min(run, max_transl_run);
                ADD_TRANSL_COUNTS(skip, len);
                dst += copy_transl(dst, src + runstart, len, sf, df);
                runstart += len;
                run -= len;
                போது (run) {
                    len = SDL_min(run, max_transl_run);
                    ADD_TRANSL_COUNTS(0, len);
                    dst += copy_transl(dst, src + runstart, len, sf, df);
                    runstart += len;
                    run -= len;
                }
                எனில் (!blankline) {
                    lastline = dst;
                }
            } போது (x < w);

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
        எனில் (!p) {
            p = rlebuf;
        }
        surface->map.data = p;
    }

    திரும்பு true;
}

நிலையான Uint32 getpix_8(மாறிலி Uint8 *srcbuf)
{
    திரும்பு *srcbuf;
}

நிலையான Uint32 getpix_16(மாறிலி Uint8 *srcbuf)
{
    திரும்பு *(மாறிலி Uint16 *)srcbuf;
}

நிலையான Uint32 getpix_24(மாறிலி Uint8 *srcbuf)
{
#எனில் SDL_BYTEORDER == SDL_LIL_ENDIAN
    திரும்பு srcbuf[0] + (srcbuf[1] << 8) + (srcbuf[2] << 16);
#இல்லையெனில்
    திரும்பு (srcbuf[0] << 16) + (srcbuf[1] << 8) + srcbuf[2];
#endif
}

நிலையான Uint32 getpix_32(மாறிலி Uint8 *srcbuf)
{
    திரும்பு *(மாறிலி Uint32 *)srcbuf;
}

வகைவரை Uint32 (*getpix_func)(மாறிலி Uint8 *);

நிலையான மாறிலி getpix_func getpixes[4] = {
    getpix_8, getpix_16, getpix_24, getpix_32
};

நிலையான bool RLEColorkeySurface(SDL_Surface *surface)
{
    SDL_Surface *dest;
    Uint8 *rlebuf, *dst;
    முழு maxn;
    முழு y;
    Uint8 *srcbuf, *lastline;
    முழு maxsize = 0;
    மாறிலி முழு bpp = surface->fmt->bytes_per_pixel;
    getpix_func getpix;
    Uint32 ckey, rgbmask;
    முழு w, h;

    dest = surface->map.info.dst_surface;
    எனில் (!dest) {
        திரும்பு false;
    }

    // calculate the worst case size for the compressed surface
    தேர்வு (bpp) {
    நிலை 1:
        /* worst case is alternating opaque and transparent pixels,
           starting with an opaque pixel */
        maxsize = surface->h * 3 * (surface->w / 2 + 1) + 2;
        நிறுத்து;
    நிலை 2:
    நிலை 3:
        // worst case is solid runs, at most 255 pixels wide
        maxsize = surface->h * (2 * (surface->w / 255 + 1) + surface->w * bpp) + 2;
        நிறுத்து;
    நிலை 4:
        // worst case is solid runs, at most 65535 pixels wide
        maxsize = surface->h * (4 * (surface->w / 65535 + 1) + surface->w * 4) + 4;
        நிறுத்து;

    இயல்பு:
        திரும்பு false;
    }

    maxsize += அளவு(SDL_PixelFormat);
    rlebuf = (Uint8 *)SDL_malloc(maxsize);
    எனில் (!rlebuf) {
        திரும்பு false;
    }
    // save the destination format so we can undo the encoding later
    *(SDL_PixelFormat *)rlebuf = dest->format;

    // Set up the conversion
    srcbuf = (Uint8 *)surface->pixels;
    maxn = bpp == 4 ? 65535 : 255;
    dst = rlebuf + அளவு(SDL_PixelFormat);
    rgbmask = ~surface->fmt->Amask;
    ckey = surface->map.info.colorkey & rgbmask;
    lastline = dst;
    getpix = getpixes[bpp - 1];
    w = surface->w;
    h = surface->h;

#define ADD_COUNTS(n, m)                \
    எனில் (bpp == 4) {                     \
        ((Uint16 *)dst)[0] = (Uint16)n; \
        ((Uint16 *)dst)[1] = (Uint16)m; \
        dst += 4;                       \
    } இல்லையெனில் {                            \
        dst[0] = (Uint8)n;              \
        dst[1] = (Uint8)m;              \
        dst += 2;                       \
    }

    க்கு (y = 0; y < h; y++) {
        முழு x = 0;
        முழு blankline = 0;
        செய் {
            முழு run, skip;
            முழு len;
            முழு runstart;
            முழு skipstart = x;

            // find run of transparent, then opaque pixels
            போது (x < w && (getpix(srcbuf + x * bpp) & rgbmask) == ckey) {
                x++;
            }
            runstart = x;
            போது (x < w && (getpix(srcbuf + x * bpp) & rgbmask) != ckey) {
                x++;
            }
            skip = runstart - skipstart;
            எனில் (skip == w) {
                blankline = 1;
            }
            run = x - runstart;

            // encode segment
            போது (skip > maxn) {
                ADD_COUNTS(maxn, 0);
                skip -= maxn;
            }
            len = SDL_min(run, maxn);
            ADD_COUNTS(skip, len);
            SDL_memcpy(dst, srcbuf + runstart * bpp, (size_t)len * bpp);
            dst += len * bpp;
            run -= len;
            runstart += len;
            போது (run) {
                len = SDL_min(run, maxn);
                ADD_COUNTS(0, len);
                SDL_memcpy(dst, srcbuf + runstart * bpp, (size_t)len * bpp);
                dst += len * bpp;
                runstart += len;
                run -= len;
            }
            எனில் (!blankline) {
                lastline = dst;
            }
        } போது (x < w);

        srcbuf += surface->pitch;
    }
    dst = lastline; // back up bast trailing blank lines
    ADD_COUNTS(0, 0);

#undef ADD_COUNTS

    // reallocate the buffer to release unused memory
    {
        // If SDL_realloc returns NULL, the original block is left intact
        Uint8 *p = (Uint8 *)SDL_realloc(rlebuf, dst - rlebuf);
        எனில் (!p) {
            p = rlebuf;
        }
        surface->map.data = p;
    }

    திரும்பு true;
}

bool SDL_RLESurface(SDL_Surface *surface)
{
    முழு flags;

    // Clear any previous RLE conversion
    எனில் (surface->internal_flags & SDL_INTERNAL_SURFACE_RLEACCEL) {
        SDL_UnRLESurface(surface);
    }

    // We don't support RLE encoding of bitmaps
    எனில் (SDL_BITSPERPIXEL(surface->format) < 8) {
        திரும்பு false;
    }

    // Make sure the pixels are available
    எனில் (!surface->pixels) {
        திரும்பு false;
    }

    flags = surface->map.info.flags;
    எனில் (flags & SDL_COPY_COLORKEY) {
        // ok
    } இல்லையெனில் எனில் ((flags & SDL_COPY_BLEND) && SDL_ISPIXELFORMAT_ALPHA(surface->format)) {
        // ok
    } இல்லையெனில் {
        // If we don't have colorkey or blending, nothing to do...
        திரும்பு false;
    }

    // Pass on combinations not supported
    எனில் ((flags & SDL_COPY_MODULATE_COLOR) ||
        ((flags & SDL_COPY_MODULATE_ALPHA) && SDL_ISPIXELFORMAT_ALPHA(surface->format)) ||
        (flags & (SDL_COPY_BLEND_PREMULTIPLIED | SDL_COPY_ADD | SDL_COPY_ADD_PREMULTIPLIED | SDL_COPY_MOD | SDL_COPY_MUL)) ||
        (flags & SDL_COPY_NEAREST)) {
        திரும்பு false;
    }

    // Encode and set up the blit
    எனில் (!SDL_ISPIXELFORMAT_ALPHA(surface->format) || !(flags & SDL_COPY_BLEND)) {
        எனில் (!surface->map.identity) {
            திரும்பு false;
        }
        எனில் (!RLEColorkeySurface(surface)) {
            திரும்பு false;
        }
        surface->map.blit = SDL_RLEBlit;
        surface->map.info.flags |= SDL_COPY_RLE_COLORKEY;
    } இல்லையெனில் {
        எனில் (!RLEAlphaSurface(surface)) {
            திரும்பு false;
        }
        surface->map.blit = SDL_RLEAlphaBlit;
        surface->map.info.flags |= SDL_COPY_RLE_ALPHAKEY;
    }

    எனில் (!(surface->flags & SDL_SURFACE_PREALLOCATED)) {
        surface->saved_pixels = surface->pixels;
        surface->pixels = வெற்று;
    }

    // The surface is now accelerated
    surface->internal_flags |= SDL_INTERNAL_SURFACE_RLEACCEL;
    SDL_UpdateSurfaceLockFlag(surface);

    திரும்பு true;
}

வெறுமை SDL_UnRLESurface(SDL_Surface *surface)
{
    எனில் (surface->internal_flags & SDL_INTERNAL_SURFACE_RLEACCEL) {
        surface->internal_flags &= ~SDL_INTERNAL_SURFACE_RLEACCEL;

        surface->map.info.flags &= ~(SDL_COPY_RLE_COLORKEY | SDL_COPY_RLE_ALPHAKEY);

        எனில் (!(surface->flags & SDL_SURFACE_PREALLOCATED)) {
            surface->pixels = surface->saved_pixels;
            surface->saved_pixels = வெற்று;
        }

        SDL_free(surface->map.data);
        surface->map.data = வெற்று;

        SDL_InvalidateMap(&surface->map);

        SDL_UpdateSurfaceLockFlag(surface);
    }
}

#endif // SDL_HAVE_RLE
