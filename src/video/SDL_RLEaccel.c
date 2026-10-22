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

#اگر_تعریف_شدہ SDL_HAVE_RLE

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

#شامل "SDL_sysvideo.h"
#شامل "SDL_surface_c.h"
#شامل "SDL_pixels_c.h"
#شامل "SDL_RLEaccel_c.h"

#تعریف_کرو PIXEL_COPY(مقصد, from, len, bpp) \
    SDL_memcpy(مقصد, from, (size_t)(len) * (bpp))

/*
 * Various colorkey blit methods, for opaque and per-surface alpha
 */

#تعریف_کرو OPAQUE_BLIT(مقصد, from, لمبائی, bpp, alpha) \
    PIXEL_COPY(مقصد, from, لمبائی, bpp)

/*
 * For 32bpp pixels on the form 0x00rrggbb:
 * If we treat the middle component separately, we can process the two
 * remaining in parallel. This is safe to do because of the gap to the left
 * of each component, so the bits from the multiplication don't collide.
 * This can be used for any RGB permutation of course.
 */
#تعریف_کرو ALPHA_BLIT32_888(مقصد, from, لمبائی, bpp, alpha)       \
    کرو {                                                     \
        صحیح i;                                               \
        Uint32 *src = (Uint32 *)(from);                      \
        Uint32 *dst = (Uint32 *)(مقصد);                        \
        برائے (i = 0; i < (صحیح)(لمبائی); i++) {                \
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
    } جب (0)

/*
 * For 16bpp pixels we can go a step further: put the middle component
 * in the high 16 bits of a 32 bit word, and process all three RGB
 * components at the same time. Since the smallest gap is here just
 * 5 bits, we have to scale alpha down to 5 bits as well.
 */
#تعریف_کرو ALPHA_BLIT16_565(مقصد, from, لمبائی, bpp, alpha) \
    کرو {                                               \
        صحیح i;                                         \
        Uint16 *src = (Uint16 *)(from);                \
        Uint16 *dst = (Uint16 *)(مقصد);                  \
        Uint32 ALPHA = alpha >> 3;                     \
        برائے (i = 0; i < (صحیح)(لمبائی); i++) {          \
            Uint32 s = *src++;                         \
            Uint32 d = *dst;                           \
            s = (s | s << 16) & 0x07e0f81f;            \
            d = (d | d << 16) & 0x07e0f81f;            \
            d += (s - d) * ALPHA >> 5;                 \
            d &= 0x07e0f81f;                           \
            *dst++ = (Uint16)(d | d >> 16);            \
        }                                              \
    } جب (0)

#تعریف_کرو ALPHA_BLIT16_555(مقصد, from, لمبائی, bpp, alpha) \
    کرو {                                               \
        صحیح i;                                         \
        Uint16 *src = (Uint16 *)(from);                \
        Uint16 *dst = (Uint16 *)(مقصد);                  \
        Uint32 ALPHA = alpha >> 3;                     \
        برائے (i = 0; i < (صحیح)(لمبائی); i++) {          \
            Uint32 s = *src++;                         \
            Uint32 d = *dst;                           \
            s = (s | s << 16) & 0x03e07c1f;            \
            d = (d | d << 16) & 0x03e07c1f;            \
            d += (s - d) * ALPHA >> 5;                 \
            d &= 0x03e07c1f;                           \
            *dst++ = (Uint16)(d | d >> 16);            \
        }                                              \
    } جب (0)

/*
 * The general slow catch-all function, for remaining depths and formats
 */
#اگر SDL_BYTEORDER == SDL_BIG_ENDIAN
#تعریف_کرو سیٹ_RGB24(dst, d)      \
    dst[0] = (Uint8)(d >> 16); \
    dst[1] = (Uint8)(d >> 8);  \
    dst[2] = (Uint8)(d);
#ورنہ
#تعریف_کرو سیٹ_RGB24(dst, d)      \
    dst[0] = (Uint8)(d);       \
    dst[1] = (Uint8)(d >> 8);  \
    dst[2] = (Uint8)(d >> 16);
#اگر_ختم
#تعریف_کرو ALPHA_BLIT_ANY(مقصد, from, لمبائی, bpp, alpha)             \
    کرو {                                                         \
        صحیح i;                                                   \
        Uint8 *src = from;                                       \
        Uint8 *dst = مقصد;                                         \
        برائے (i = 0; i < (صحیح)(لمبائی); i++) {                    \
            Uint32 s = 0, d = 0;                                 \
            غیرعلامتی rs, gs, bs, rd, gd, bd;                     \
            انتخاب (bpp) {                                       \
            حالت 2:                                              \
                s = *(Uint16 *)src;                              \
                d = *(Uint16 *)dst;                              \
                توڑو;                                           \
            حالت 3:                                              \
                s = GET_RGB24(src);                              \
                d = GET_RGB24(dst);                              \
                توڑو;                                           \
            حالت 4:                                              \
                s = *(Uint32 *)src;                              \
                d = *(Uint32 *)dst;                              \
                توڑو;                                           \
            }                                                    \
            RGB_FROM_PIXEL(s, fmt, rs, gs, bs);                  \
            RGB_FROM_PIXEL(d, fmt, rd, gd, bd);                  \
            rd += (rs - rd) * alpha >> 8;                        \
            gd += (gs - gd) * alpha >> 8;                        \
            bd += (bs - bd) * alpha >> 8;                        \
            PIXEL_FROM_RGB(d, fmt, rd, gd, bd);                  \
            انتخاب (bpp) {                                       \
            حالت 2:                                              \
                *(Uint16 *)dst = (Uint16)d;                      \
                توڑو;                                           \
            حالت 3:                                              \
                سیٹ_RGB24(dst, d);                               \
                توڑو;                                           \
            حالت 4:                                              \
                *(Uint32 *)dst = d;                              \
                توڑو;                                           \
            }                                                    \
            src += bpp;                                          \
            dst += bpp;                                          \
        }                                                        \
    } جب (0)

/*
 * Special case: 50% alpha (alpha=128)
 * This is treated specially because it can be optimized very well, and
 * since it is good for many cases of semi-translucency.
 * The theory is to do all three components at the same time:
 * First zero the lowest bit of each component, which gives us room to
 * add them. Then shift right and add the sum of the lowest bits.
 */
#تعریف_کرو ALPHA_BLIT32_888_50(مقصد, from, لمبائی, bpp, alpha)                                 \
    کرو {                                                                                  \
        صحیح i;                                                                            \
        Uint32 *src = (Uint32 *)(from);                                                   \
        Uint32 *dst = (Uint32 *)(مقصد);                                                     \
        برائے (i = 0; i < (صحیح)(لمبائی); i++) {                                             \
            Uint32 s = *src++;                                                            \
            Uint32 d = *dst;                                                              \
            *dst++ = (((s & 0x00fefefe) + (d & 0x00fefefe)) >> 1) + (s & d & 0x00010101); \
        }                                                                                 \
    } جب (0)

/*
 * For 16bpp, we can actually blend two pixels in parallel, if we take
 * care to shift before we add, not after.
 */

// helper: blend a single 16 bit pixel at 50%
#تعریف_کرو BLEND16_50(dst, src, نقاب)                           \
    کرو {                                                     \
        Uint32 s = *src++;                                   \
        Uint32 d = *dst;                                     \
        *dst++ = (Uint16)((((s & نقاب) + (d & نقاب)) >> 1) + \
                          (s & d & (~نقاب & 0xffff)));       \
    } جب (0)

// basic 16bpp blender. mask is the pixels to keep when adding.
#تعریف_کرو ALPHA_BLIT16_50(مقصد, from, لمبائی, bpp, alpha, نقاب)                                                                              \
    کرو {                                                                                                                                 \
        غیرعلامتی n = (لمبائی);                                                                                                           \
        Uint16 *src = (Uint16 *)(from);                                                                                                  \
        Uint16 *dst = (Uint16 *)(مقصد);                                                                                                    \
        اگر (((uintptr_t)src ^ (uintptr_t)dst) & 3) {                                                                                     \
            /* source and destination not in phase, blit one by one */                                                                   \
            جب (n--)                                                                                                                  \
                BLEND16_50(dst, src, نقاب);                                                                                              \
        } ورنہ {                                                                                                                         \
            اگر ((uintptr_t)src & 3) {                                                                                                    \
                /* first odd pixel */                                                                                                    \
                BLEND16_50(dst, src, نقاب);                                                                                              \
                n--;                                                                                                                     \
            }                                                                                                                            \
            برائے (; n > 1; n -= 2) {                                                                                                      \
                Uint32 s = *(Uint32 *)src;                                                                                               \
                Uint32 d = *(Uint32 *)dst;                                                                                               \
                *(Uint32 *)dst = ((s & (نقاب | نقاب << 16)) >> 1) + ((d & (نقاب | نقاب << 16)) >> 1) + (s & d & (~(نقاب | نقاب << 16))); \
                src += 2;                                                                                                                \
                dst += 2;                                                                                                                \
            }                                                                                                                            \
            اگر (n)                                                                                                                       \
                BLEND16_50(dst, src, نقاب); /* last odd pixel */                                                                         \
        }                                                                                                                                \
    } جب (0)

#تعریف_کرو ALPHA_BLIT16_565_50(مقصد, from, لمبائی, bpp, alpha) \
    ALPHA_BLIT16_50(مقصد, from, لمبائی, bpp, alpha, 0xf7deU)

#تعریف_کرو ALPHA_BLIT16_555_50(مقصد, from, لمبائی, bpp, alpha) \
    ALPHA_BLIT16_50(مقصد, from, لمبائی, bpp, alpha, 0xfbdeU)

#تعریف_کرو انتخاب_BLIT(blitter, alpha, fmt)                                                                                                              \
    کرو {                                                                                                                                              \
        اگر (alpha == 255) {                                                                                                                           \
            انتخاب (fmt->بائٹیں_فی_pixel) {                                                                                                             \
            حالت 1:                                                                                                                                   \
                blitter(1, Uint8, OPAQUE_BLIT);                                                                                                       \
                توڑو;                                                                                                                                \
            حالت 2:                                                                                                                                   \
                blitter(2, Uint8, OPAQUE_BLIT);                                                                                                       \
                توڑو;                                                                                                                                \
            حالت 3:                                                                                                                                   \
                blitter(3, Uint8, OPAQUE_BLIT);                                                                                                       \
                توڑو;                                                                                                                                \
            حالت 4:                                                                                                                                   \
                blitter(4, Uint16, OPAQUE_BLIT);                                                                                                      \
                توڑو;                                                                                                                                \
            }                                                                                                                                         \
        } ورنہ {                                                                                                                                      \
            انتخاب (fmt->بائٹیں_فی_pixel) {                                                                                                             \
            حالت 1:                                                                                                                                   \
                /* No 8bpp alpha blitting */                                                                                                          \
                توڑو;                                                                                                                                \
                                                                                                                                                      \
            حالت 2:                                                                                                                                   \
                انتخاب (fmt->Rmask | fmt->Gmask | fmt->Bmask) {                                                                                       \
                حالت 0xffff:                                                                                                                          \
                    اگر (fmt->Gmask == 0x07e0 || fmt->Rmask == 0x07e0 || fmt->Bmask == 0x07e0) {                                                       \
                        اگر (alpha == 128) {                                                                                                           \
                            blitter(2, Uint8, ALPHA_BLIT16_565_50);                                                                                   \
                        } ورنہ {                                                                                                                      \
                            blitter(2, Uint8, ALPHA_BLIT16_565);                                                                                      \
                        }                                                                                                                             \
                    } ورنہ {                                                                                                                          \
                        جاؤ general16;                                                                                                               \
                    }                                                                                                                                 \
                    توڑو;                                                                                                                            \
                                                                                                                                                      \
                حالت 0x7fff:                                                                                                                          \
                    اگر (fmt->Gmask == 0x03e0 || fmt->Rmask == 0x03e0 || fmt->Bmask == 0x03e0) {                                                       \
                        اگر (alpha == 128) {                                                                                                           \
                            blitter(2, Uint8, ALPHA_BLIT16_555_50);                                                                                   \
                        } ورنہ {                                                                                                                      \
                            blitter(2, Uint8, ALPHA_BLIT16_555);                                                                                      \
                        }                                                                                                                             \
                        توڑو;                                                                                                                        \
                    } ورنہ {                                                                                                                          \
                        جاؤ general16;                                                                                                               \
                    }                                                                                                                                 \
                    توڑو;                                                                                                                            \
                                                                                                                                                      \
                طےشدہ:                                                                                                                              \
                general16:                                                                                                                            \
                    blitter(2, Uint8, ALPHA_BLIT_ANY);                                                                                                \
                }                                                                                                                                     \
                توڑو;                                                                                                                                \
                                                                                                                                                      \
            حالت 3:                                                                                                                                   \
                blitter(3, Uint8, ALPHA_BLIT_ANY);                                                                                                    \
                توڑو;                                                                                                                                \
                                                                                                                                                      \
            حالت 4:                                                                                                                                   \
                اگر ((fmt->Rmask | fmt->Gmask | fmt->Bmask) == 0x00ffffff && (fmt->Gmask == 0xff00 || fmt->Rmask == 0xff00 || fmt->Bmask == 0xff00)) { \
                    اگر (alpha == 128) {                                                                                                               \
                        blitter(4, Uint16, ALPHA_BLIT32_888_50);                                                                                      \
                    } ورنہ {                                                                                                                          \
                        blitter(4, Uint16, ALPHA_BLIT32_888);                                                                                         \
                    }                                                                                                                                 \
                } ورنہ {                                                                                                                              \
                    blitter(4, Uint16, ALPHA_BLIT_ANY);                                                                                               \
                }                                                                                                                                     \
                توڑو;                                                                                                                                \
            }                                                                                                                                         \
        }                                                                                                                                             \
    } جب (0)

/*
 * Set a pixel value using the given format, except that the alpha value is
 * placed in the top byte. This is the format used for RLE with alpha.
 */
#تعریف_کرو RLEPIXEL_FROM_RGBA(Pixel, fmt, r, g, b, a)   \
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
#تعریف_کرو RLECLIPBLIT(bpp, Type, do_blit)                                    \
    کرو {                                                                   \
        صحیح linecount = srcrect->h;                                        \
        صحیح ofs = 0;                                                       \
        صحیح بایاں = srcrect->x;                                             \
        صحیح دایاں = بایاں + srcrect->w;                                     \
        dstbuf -= بایاں * bpp;                                              \
        برائے (;;) {                                                         \
            صحیح تسلسل;                                                       \
            ofs += *(Type *)srcbuf;                                        \
            تسلسل = ((Type *)srcbuf)[1];                                     \
            srcbuf += 2 * حجم(Type);                                    \
            اگر (تسلسل) {                                                     \
                /* clip to left and right borders */                       \
                اگر (ofs < دایاں) {                                         \
                    صحیح آغاز = 0;                                         \
                    صحیح len = تسلسل;                                         \
                    صحیح startcol;                                          \
                    اگر (بایاں - ofs > 0) {                                  \
                        آغاز = بایاں - ofs;                                \
                        len -= آغاز;                                      \
                        اگر (len <= 0)                                      \
                            جاؤ nocopy##bpp##do_blit;                     \
                    }                                                      \
                    startcol = ofs + آغاز;                                \
                    اگر (len > دایاں - startcol)                            \
                        len = دایاں - startcol;                            \
                    do_blit(dstbuf + startcol * bpp, srcbuf + آغاز * bpp, \
                            len, bpp, alpha);                              \
                }                                                          \
                nocopy##bpp##do_blit : srcbuf += تسلسل * bpp;                \
                ofs += تسلسل;                                                \
            } ورنہ اگر (!ofs) {                                             \
                توڑو;                                                     \
            }                                                              \
                                                                           \
            اگر (ofs == w) {                                                \
                ofs = 0;                                                   \
                dstbuf += surf_dst->pitch;                                 \
                اگر (!--linecount) {                                        \
                    توڑو;                                                 \
                }                                                          \
            }                                                              \
        }                                                                  \
    } جب (0)

ساکن خالی RLEClipBlit(صحیح w, Uint8 *srcbuf, SDL_Surface *surf_dst,
                        Uint8 *dstbuf, ثابت SDL_Rect *srcrect, غیرعلامتی alpha)
{
    ثابت SDL_PixelFormatDetails *fmt = surf_dst->fmt;

    انتخاب_BLIT(RLECLIPBLIT, alpha, fmt);
}

#تعریف_منسوخ RLECLIPBLIT

// blit a colorkeyed RLE surface
ساکن bool SDLCALL SDL_RLEBlit(SDL_Surface *surf_src, ثابت SDL_Rect *srcrect,
                                SDL_Surface *surf_dst, ثابت SDL_Rect *dstrect)
{
    Uint8 *dstbuf;
    Uint8 *srcbuf;
    صحیح x, y;
    صحیح w = surf_src->w;
    غیرعلامتی alpha;

    // Lock the destination if necessary
    اگر (SDL_MUSTLOCK(surf_dst)) {
        اگر (!SDL_تالا_Surface(surf_dst)) {
            واپس false;
        }
    }

    // Set up the source and destination pointers
    x = dstrect->x;
    y = dstrect->y;
    dstbuf = (Uint8 *)surf_dst->pixels + y * surf_dst->pitch + x * surf_src->fmt->بائٹیں_فی_pixel;
    srcbuf = (Uint8 *)surf_src->map.ڈیٹا + حجم(SDL_PixelFormat);

    {
        // skip lines at the top if necessary
        صحیح vskip = srcrect->y;
        صحیح ofs = 0;
        اگر (vskip) {

#تعریف_کرو RLESKIP(bpp, Type)          \
    برائے (;;) {                      \
        صحیح تسلسل;                    \
        ofs += *(Type *)srcbuf;     \
        تسلسل = ((Type *)srcbuf)[1];  \
        srcbuf += حجم(Type) * 2; \
        اگر (تسلسل) {                  \
            srcbuf += تسلسل * bpp;    \
            ofs += تسلسل;             \
        } ورنہ اگر (!ofs)            \
            جاؤ مکمل;              \
        اگر (ofs == w) {             \
            ofs = 0;                \
            اگر (!--vskip)           \
                توڑو;              \
        }                           \
    }

            انتخاب (surf_src->fmt->بائٹیں_فی_pixel) {
            حالت 1:
                RLESKIP(1, Uint8);
                توڑو;
            حالت 2:
                RLESKIP(2, Uint8);
                توڑو;
            حالت 3:
                RLESKIP(3, Uint8);
                توڑو;
            حالت 4:
                RLESKIP(4, Uint16);
                توڑو;
            }

#تعریف_منسوخ RLESKIP
        }
    }

    alpha = surf_src->map.info.a;
    // if left or right edge clipping needed, call clip blit
    اگر (srcrect->x || srcrect->w != surf_src->w) {
        RLEClipBlit(w, srcbuf, surf_dst, dstbuf, srcrect, alpha);
    } ورنہ {
        ثابت SDL_PixelFormatDetails *fmt = surf_src->fmt;

#تعریف_کرو RLEBLIT(bpp, Type, do_blit)                                   \
    کرو {                                                              \
        صحیح linecount = srcrect->h;                                   \
        صحیح ofs = 0;                                                  \
        برائے (;;) {                                                    \
            غیرعلامتی تسلسل;                                             \
            ofs += *(Type *)srcbuf;                                   \
            تسلسل = ((Type *)srcbuf)[1];                                \
            srcbuf += 2 * حجم(Type);                               \
            اگر (تسلسل) {                                                \
                do_blit(dstbuf + ofs * bpp, srcbuf, تسلسل, bpp, alpha); \
                srcbuf += تسلسل * bpp;                                  \
                ofs += تسلسل;                                           \
            } ورنہ اگر (!ofs)                                          \
                توڑو;                                                \
            اگر (ofs == w) {                                           \
                ofs = 0;                                              \
                dstbuf += surf_dst->pitch;                            \
                اگر (!--linecount)                                     \
                    توڑو;                                            \
            }                                                         \
        }                                                             \
    } جب (0)

        انتخاب_BLIT(RLEBLIT, alpha, fmt);

#تعریف_منسوخ RLEBLIT
    }

مکمل:
    // Unlock the destination if necessary
    اگر (SDL_MUSTLOCK(surf_dst)) {
        SDL_UnlockSurface(surf_dst);
    }
    واپس true;
}

#تعریف_منسوخ OPAQUE_BLIT

/*
 * Per-pixel blitting macros for translucent pixels:
 * These use the same techniques as the per-surface blitting macros
 */

/*
 * For 32bpp pixels, we have made sure the alpha is stored in the top
 * 8 bits, so proceed as usual
 */
#تعریف_کرو BLIT_TRANSL_888(src, dst)                        \
    کرو {                                                 \
        Uint32 s = src;                                  \
        Uint32 d = dst;                                  \
        غیرعلامتی alpha = s >> 24;                        \
        Uint32 s1 = s & 0xff00ff;                        \
        Uint32 d1 = d & 0xff00ff;                        \
        d1 = (d1 + ((s1 - d1) * alpha >> 8)) & 0xff00ff; \
        s &= 0xff00;                                     \
        d &= 0xff00;                                     \
        d = (d + ((s - d) * alpha >> 8)) & 0xff00;       \
        dst = d1 | d | 0xff000000;                       \
    } جب (0)

/*
 * For 16bpp pixels, we have stored the 5 most significant alpha bits in
 * bits 5-10. As before, we can process all 3 RGB components at the same time.
 */
#تعریف_کرو BLIT_TRANSL_565(src, dst)          \
    کرو {                                   \
        Uint32 s = src;                    \
        Uint32 d = dst;                    \
        غیرعلامتی alpha = (s & 0x3e0) >> 5; \
        s &= 0x07e0f81f;                   \
        d = (d | d << 16) & 0x07e0f81f;    \
        d += (s - d) * alpha >> 5;         \
        d &= 0x07e0f81f;                   \
        dst = (Uint16)(d | d >> 16);       \
    } جب (0)

#تعریف_کرو BLIT_TRANSL_555(src, dst)          \
    کرو {                                   \
        Uint32 s = src;                    \
        Uint32 d = dst;                    \
        غیرعلامتی alpha = (s & 0x3e0) >> 5; \
        s &= 0x03e07c1f;                   \
        d = (d | d << 16) & 0x03e07c1f;    \
        d += (s - d) * alpha >> 5;         \
        d &= 0x03e07c1f;                   \
        dst = (Uint16)(d | d >> 16);       \
    } جب (0)

// blit a pixel-alpha RLE surface clipped at the right and/or left edges
ساکن خالی RLEAlphaClipBlit(صحیح w, Uint8 *srcbuf, SDL_Surface *surf_dst,
                             Uint8 *dstbuf, ثابت SDL_Rect *srcrect)
{
    ثابت SDL_PixelFormatDetails *df = surf_dst->fmt;
    /*
     * clipped blitter: Ptype is the destination pixel type,
     * Ctype the translucent count type, and do_blend the macro
     * to blend one pixel.
     */
#تعریف_کرو RLEALPHACLIPBLIT(Ptype, Ctype, do_blend)                          \
    کرو {                                                                  \
        صحیح linecount = srcrect->h;                                       \
        صحیح بایاں = srcrect->x;                                            \
        صحیح دایاں = بایاں + srcrect->w;                                    \
        dstbuf -= بایاں * حجم(Ptype);                                   \
        کرو {                                                              \
            صحیح ofs = 0;                                                  \
            /* blit opaque pixels on one line */                          \
            کرو {                                                          \
                غیرعلامتی تسلسل;                                             \
                ofs += ((Ctype *)srcbuf)[0];                              \
                تسلسل = ((Ctype *)srcbuf)[1];                               \
                srcbuf += 2 * حجم(Ctype);                              \
                اگر (تسلسل) {                                                \
                    /* clip to left and right borders */                  \
                    صحیح cofs = ofs;                                       \
                    صحیح crun = تسلسل;                                       \
                    اگر (بایاں - cofs > 0) {                                \
                        crun -= بایاں - cofs;                              \
                        cofs = بایاں;                                      \
                    }                                                     \
                    اگر (crun > دایاں - cofs)                              \
                        crun = دایاں - cofs;                              \
                    اگر (crun > 0)                                         \
                        PIXEL_COPY(dstbuf + cofs * حجم(Ptype),         \
                                   srcbuf + (cofs - ofs) * حجم(Ptype), \
                                   (غیرعلامتی)crun, حجم(Ptype));        \
                    srcbuf += تسلسل * حجم(Ptype);                        \
                    ofs += تسلسل;                                           \
                } ورنہ اگر (!ofs)                                          \
                    واپس;                                               \
            } جب (ofs < w);                                            \
            /* skip padding if necessary */                               \
            ثابت size_t psize = حجم(Ptype);                           \
            اگر (psize == 2)                                               \
                srcbuf += (uintptr_t)srcbuf & 2;                          \
            /* blit translucent pixels on the same line */                \
            ofs = 0;                                                      \
            کرو {                                                          \
                غیرعلامتی تسلسل;                                             \
                ofs += ((Uint16 *)srcbuf)[0];                             \
                تسلسل = ((Uint16 *)srcbuf)[1];                              \
                srcbuf += 4;                                              \
                اگر (تسلسل) {                                                \
                    /* clip to left and right borders */                  \
                    صحیح cofs = ofs;                                       \
                    صحیح crun = تسلسل;                                       \
                    اگر (بایاں - cofs > 0) {                                \
                        crun -= بایاں - cofs;                              \
                        cofs = بایاں;                                      \
                    }                                                     \
                    اگر (crun > دایاں - cofs)                              \
                        crun = دایاں - cofs;                              \
                    اگر (crun > 0) {                                       \
                        Ptype *dst = (Ptype *)dstbuf + cofs;              \
                        Uint32 *src = (Uint32 *)srcbuf + (cofs - ofs);    \
                        صحیح i;                                            \
                        برائے (i = 0; i < crun; i++)                        \
                            do_blend(src[i], dst[i]);                     \
                    }                                                     \
                    srcbuf += تسلسل * 4;                                    \
                    ofs += تسلسل;                                           \
                }                                                         \
            } جب (ofs < w);                                            \
            dstbuf += surf_dst->pitch;                                    \
        } جب (--linecount);                                            \
    } جب (0)

    انتخاب (df->بائٹیں_فی_pixel) {
    حالت 2:
        اگر (df->Gmask == 0x07e0 || df->Rmask == 0x07e0 || df->Bmask == 0x07e0) {
            RLEALPHACLIPBLIT(Uint16, Uint8, BLIT_TRANSL_565);
        } ورنہ {
            RLEALPHACLIPBLIT(Uint16, Uint8, BLIT_TRANSL_555);
        }
        توڑو;
    حالت 4:
        RLEALPHACLIPBLIT(Uint32, Uint16, BLIT_TRANSL_888);
        توڑو;
    }
}

// blit a pixel-alpha RLE surface
ساکن bool SDLCALL SDL_RLEAlphaBlit(SDL_Surface *surf_src, ثابت SDL_Rect *srcrect,
                                     SDL_Surface *surf_dst, ثابت SDL_Rect *dstrect)
{
    صحیح x, y;
    صحیح w = surf_src->w;
    Uint8 *srcbuf, *dstbuf;
    ثابت SDL_PixelFormatDetails *df = surf_dst->fmt;

    // Lock the destination if necessary
    اگر (SDL_MUSTLOCK(surf_dst)) {
        اگر (!SDL_تالا_Surface(surf_dst)) {
            واپس false;
        }
    }

    x = dstrect->x;
    y = dstrect->y;
    dstbuf = (Uint8 *)surf_dst->pixels + y * surf_dst->pitch + x * df->بائٹیں_فی_pixel;
    srcbuf = (Uint8 *)surf_src->map.ڈیٹا + حجم(SDL_PixelFormat);

    {
        // skip lines at the top if necessary
        صحیح vskip = srcrect->y;
        اگر (vskip) {
            صحیح ofs;
            اگر (df->بائٹیں_فی_pixel == 2) {
                // the 16/32 interleaved format
                کرو {
                    // skip opaque line
                    ofs = 0;
                    کرو {
                        صحیح تسلسل;
                        ofs += srcbuf[0];
                        تسلسل = srcbuf[1];
                        srcbuf += 2;
                        اگر (تسلسل) {
                            srcbuf += 2 * تسلسل;
                            ofs += تسلسل;
                        } ورنہ اگر (ofs == 0) {
                            جاؤ مکمل;
                        }
                    } جب (ofs < w);

                    // skip padding
                    srcbuf += (uintptr_t)srcbuf & 2;

                    // skip translucent line
                    ofs = 0;
                    کرو {
                        صحیح تسلسل;
                        ofs += ((Uint16 *)srcbuf)[0];
                        تسلسل = ((Uint16 *)srcbuf)[1];
                        srcbuf += 4 * (تسلسل + 1);
                        ofs += تسلسل;
                    } جب (ofs < w);
                } جب (--vskip);
            } ورنہ {
                // the 32/32 interleaved format
                vskip <<= 1; // opaque and translucent have same format
                کرو {
                    ofs = 0;
                    کرو {
                        صحیح تسلسل;
                        ofs += ((Uint16 *)srcbuf)[0];
                        تسلسل = ((Uint16 *)srcbuf)[1];
                        srcbuf += 4;
                        اگر (تسلسل) {
                            srcbuf += 4 * تسلسل;
                            ofs += تسلسل;
                        } ورنہ اگر (ofs == 0) {
                            جاؤ مکمل;
                        }
                    } جب (ofs < w);
                } جب (--vskip);
            }
        }
    }

    // if left or right edge clipping needed, call clip blit
    اگر (srcrect->x || srcrect->w != surf_src->w) {
        RLEAlphaClipBlit(w, srcbuf, surf_dst, dstbuf, srcrect);
    } ورنہ {

        /*
         * non-clipped blitter. Ptype is the destination pixel type,
         * Ctype the translucent count type, and do_blend the
         * macro to blend one pixel.
         */
#تعریف_کرو RLEALPHABLIT(Ptype, Ctype, do_blend)                         \
    کرو {                                                             \
        صحیح linecount = srcrect->h;                                  \
        کرو {                                                         \
            صحیح ofs = 0;                                             \
            /* blit opaque pixels on one line */                     \
            کرو {                                                     \
                غیرعلامتی تسلسل;                                        \
                ofs += ((Ctype *)srcbuf)[0];                         \
                تسلسل = ((Ctype *)srcbuf)[1];                          \
                srcbuf += 2 * حجم(Ctype);                         \
                اگر (تسلسل) {                                           \
                    PIXEL_COPY(dstbuf + ofs * حجم(Ptype), srcbuf, \
                               تسلسل, حجم(Ptype));                  \
                    srcbuf += تسلسل * حجم(Ptype);                   \
                    ofs += تسلسل;                                      \
                } ورنہ اگر (!ofs)                                     \
                    جاؤ مکمل;                                       \
            } جب (ofs < w);                                       \
            /* skip padding if necessary */                          \
            ثابت size_t psize = حجم(Ptype);                      \
            اگر (psize == 2)                                          \
                srcbuf += (uintptr_t)srcbuf & 2;                     \
            /* blit translucent pixels on the same line */           \
            ofs = 0;                                                 \
            کرو {                                                     \
                غیرعلامتی تسلسل;                                        \
                ofs += ((Uint16 *)srcbuf)[0];                        \
                تسلسل = ((Uint16 *)srcbuf)[1];                         \
                srcbuf += 4;                                         \
                اگر (تسلسل) {                                           \
                    Ptype *dst = (Ptype *)dstbuf + ofs;              \
                    غیرعلامتی i;                                      \
                    برائے (i = 0; i < تسلسل; i++) {                      \
                        Uint32 src = *(Uint32 *)srcbuf;              \
                        do_blend(src, *dst);                         \
                        srcbuf += 4;                                 \
                        dst++;                                       \
                    }                                                \
                    ofs += تسلسل;                                      \
                }                                                    \
            } جب (ofs < w);                                       \
            dstbuf += surf_dst->pitch;                               \
        } جب (--linecount);                                       \
    } جب (0)

        انتخاب (df->بائٹیں_فی_pixel) {
        حالت 2:
            اگر (df->Gmask == 0x07e0 || df->Rmask == 0x07e0 || df->Bmask == 0x07e0) {
                RLEALPHABLIT(Uint16, Uint8, BLIT_TRANSL_565);
            } ورنہ {
                RLEALPHABLIT(Uint16, Uint8, BLIT_TRANSL_555);
            }
            توڑو;
        حالت 4:
            RLEALPHABLIT(Uint32, Uint16, BLIT_TRANSL_888);
            توڑو;
        }
    }

مکمل:
    // Unlock the destination if necessary
    اگر (SDL_MUSTLOCK(surf_dst)) {
        SDL_UnlockSurface(surf_dst);
    }
    واپس true;
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
ساکن صحیح copy_opaque_16(خالی *dst, ثابت Uint32 *src, صحیح n,
                          ثابت SDL_PixelFormatDetails *sfmt, ثابت SDL_PixelFormatDetails *dfmt)
{
    صحیح i;
    Uint16 *d = (Uint16 *)dst;
    برائے (i = 0; i < n; i++) {
        غیرعلامتی r, g, b;
        RGB_FROM_PIXEL(*src, sfmt, r, g, b);
        PIXEL_FROM_RGB(*d, dfmt, r, g, b);
        src++;
        d++;
    }
    واپس n * 2;
}

// encode 32bpp rgb + a into 32bpp G0RAB format for blitting into 565
ساکن صحیح copy_transl_565(خالی *dst, ثابت Uint32 *src, صحیح n,
                           ثابت SDL_PixelFormatDetails *sfmt, ثابت SDL_PixelFormatDetails *dfmt)
{
    صحیح i;
    Uint32 *d = (Uint32 *)dst;
    برائے (i = 0; i < n; i++) {
        غیرعلامتی r, g, b, a;
        Uint16 pix;
        RGBA_FROM_8888(*src, sfmt, r, g, b, a);
        PIXEL_FROM_RGB(pix, dfmt, r, g, b);
        *d = ((pix & 0x7e0) << 16) | (pix & 0xf81f) | ((a << 2) & 0x7e0);
        src++;
        d++;
    }
    واپس n * 4;
}

// encode 32bpp rgb + a into 32bpp G0RAB format for blitting into 555
ساکن صحیح copy_transl_555(خالی *dst, ثابت Uint32 *src, صحیح n,
                           ثابت SDL_PixelFormatDetails *sfmt, ثابت SDL_PixelFormatDetails *dfmt)
{
    صحیح i;
    Uint32 *d = (Uint32 *)dst;
    برائے (i = 0; i < n; i++) {
        غیرعلامتی r, g, b, a;
        Uint16 pix;
        RGBA_FROM_8888(*src, sfmt, r, g, b, a);
        PIXEL_FROM_RGB(pix, dfmt, r, g, b);
        *d = ((pix & 0x3e0) << 16) | (pix & 0xfc1f) | ((a << 2) & 0x3e0);
        src++;
        d++;
    }
    واپس n * 4;
}

// encode 32bpp rgba into 32bpp rgba, keeping alpha (dual purpose)
ساکن صحیح copy_32(خالی *dst, ثابت Uint32 *src, صحیح n,
                   ثابت SDL_PixelFormatDetails *sfmt, ثابت SDL_PixelFormatDetails *dfmt)
{
    صحیح i;
    Uint32 *d = (Uint32 *)dst;
    برائے (i = 0; i < n; i++) {
        غیرعلامتی r, g, b, a;
        RGBA_FROM_8888(*src, sfmt, r, g, b, a);
        RLEPIXEL_FROM_RGBA(*d, dfmt, r, g, b, a);
        d++;
        src++;
    }
    واپس n * 4;
}

#تعریف_کرو ISOPAQUE(pixel, fmt) ((((pixel)&fmt->Amask) >> fmt->Ashift) == 255)

#تعریف_کرو ISTRANSL(pixel, fmt) \
    ((غیرعلامتی)((((pixel)&fmt->Amask) >> fmt->Ashift) - 1U) < 254U)

// convert surface to be quickly alpha-blittable onto dest, if possible
ساکن bool RLEAlphaSurface(SDL_Surface *surface)
{
    SDL_Surface *dest;
    ثابت SDL_PixelFormatDetails *df;
    صحیح maxsize = 0;
    صحیح max_opaque_تسلسل;
    صحیح max_transl_تسلسل = 65535;
    غیرعلامتی masksum;
    Uint8 *rlebuf, *dst;
    صحیح (*copy_opaque)(خالی *, ثابت Uint32 *, صحیح,
                       ثابت SDL_PixelFormatDetails *, ثابت SDL_PixelFormatDetails *);
    صحیح (*copy_transl)(خالی *, ثابت Uint32 *, صحیح,
                       ثابت SDL_PixelFormatDetails *, ثابت SDL_PixelFormatDetails *);

    dest = surface->map.info.dst_surface;
    اگر (!dest) {
        واپس false;
    }
    df = dest->fmt;
    اگر (surface->fmt->بٹ_فی_pixel != 32) {
        واپس false; // only 32bpp source supported
    }

    /* find out whether the destination is one we support,
       and determine the max size of the encoded result */
    masksum = df->Rmask | df->Gmask | df->Bmask;
    انتخاب (df->بائٹیں_فی_pixel) {
    حالت 2:
        // 16bpp: only support 565 and 555 formats
        انتخاب (masksum) {
        حالت 0xffff:
            اگر (df->Gmask == 0x07e0 || df->Rmask == 0x07e0 || df->Bmask == 0x07e0) {
                copy_opaque = copy_opaque_16;
                copy_transl = copy_transl_565;
            } ورنہ {
                واپس false;
            }
            توڑو;
        حالت 0x7fff:
            اگر (df->Gmask == 0x03e0 || df->Rmask == 0x03e0 || df->Bmask == 0x03e0) {
                copy_opaque = copy_opaque_16;
                copy_transl = copy_transl_555;
            } ورنہ {
                واپس false;
            }
            توڑو;
        طےشدہ:
            واپس false;
        }
        max_opaque_تسلسل = 255; // runs stored as bytes

        /* worst case is alternating opaque and translucent pixels,
           with room for alignment padding between lines */
        maxsize = surface->h * (2 + (4 + 2) * (surface->w + 1)) + 2;
        توڑو;
    حالت 4:
        اگر (masksum != 0x00ffffff) {
            واپس false; // requires unused high byte
        }
        copy_opaque = copy_32;
        copy_transl = copy_32;
        max_opaque_تسلسل = 255; // runs stored as short ints

        // worst case is alternating opaque and translucent pixels
        maxsize = surface->h * 2 * 4 * (surface->w + 1) + 4;
        توڑو;
    طےشدہ:
        واپس false; // anything else unsupported right now
    }

    maxsize += حجم(SDL_PixelFormat);
    rlebuf = (Uint8 *)SDL_malloc(maxsize);
    اگر (!rlebuf) {
        واپس false;
    }
    // save the destination format so we can undo the encoding later
    *(SDL_PixelFormat *)rlebuf = dest->format;
    dst = rlebuf + حجم(SDL_PixelFormat);

    // Do the actual encoding
    {
        صحیح x, y;
        صحیح h = surface->h, w = surface->w;
        ثابت SDL_PixelFormatDetails *sf = surface->fmt;
        Uint32 *src = (Uint32 *)surface->pixels;
        Uint8 *lastline = dst; // end of last non-blank line

        // opaque counts are 8 or 16 bits, depending on target depth
#تعریف_کرو جوڑو_OPAQUE_COUNTS(n, m)           \
    اگر (df->بائٹیں_فی_pixel == 4) {         \
        ((Uint16 *)dst)[0] = (Uint16)n;   \
        ((Uint16 *)dst)[1] = (Uint16)m;   \
        dst += 4;                         \
    } ورنہ {                              \
        dst[0] = (Uint8)n;                \
        dst[1] = (Uint8)m;                \
        dst += 2;                         \
    }

        // translucent counts are always 16 bit
#تعریف_کرو جوڑو_TRANSL_COUNTS(n, m) \
    (((Uint16 *)dst)[0] = (Uint16)n, ((Uint16 *)dst)[1] = (Uint16)m, dst += 4)

        برائے (y = 0; y < h; y++) {
            صحیح runstart, skipstart;
            صحیح blankline = 0;
            // First encode all opaque pixels of a scan line
            x = 0;
            کرو {
                صحیح تسلسل, skip, len;
                skipstart = x;
                جب (x < w && !ISOPAQUE(src[x], sf)) {
                    x++;
                }
                runstart = x;
                جب (x < w && ISOPAQUE(src[x], sf)) {
                    x++;
                }
                skip = runstart - skipstart;
                اگر (skip == w) {
                    blankline = 1;
                }
                تسلسل = x - runstart;
                جب (skip > max_opaque_تسلسل) {
                    جوڑو_OPAQUE_COUNTS(max_opaque_تسلسل, 0);
                    skip -= max_opaque_تسلسل;
                }
                len = SDL_min(تسلسل, max_opaque_تسلسل);
                جوڑو_OPAQUE_COUNTS(skip, len);
                dst += copy_opaque(dst, src + runstart, len, sf, df);
                runstart += len;
                تسلسل -= len;
                جب (تسلسل) {
                    len = SDL_min(تسلسل, max_opaque_تسلسل);
                    جوڑو_OPAQUE_COUNTS(0, len);
                    dst += copy_opaque(dst, src + runstart, len, sf, df);
                    runstart += len;
                    تسلسل -= len;
                }
            } جب (x < w);

            // Make sure the next output address is 32-bit aligned
            dst += (uintptr_t)dst & 2;

            // Next, encode all translucent pixels of the same scan line
            x = 0;
            کرو {
                صحیح تسلسل, skip, len;
                skipstart = x;
                جب (x < w && !ISTRANSL(src[x], sf)) {
                    x++;
                }
                runstart = x;
                جب (x < w && ISTRANSL(src[x], sf)) {
                    x++;
                }
                skip = runstart - skipstart;
                blankline &= (skip == w);
                تسلسل = x - runstart;
                جب (skip > max_transl_تسلسل) {
                    جوڑو_TRANSL_COUNTS(max_transl_تسلسل, 0);
                    skip -= max_transl_تسلسل;
                }
                len = SDL_min(تسلسل, max_transl_تسلسل);
                جوڑو_TRANSL_COUNTS(skip, len);
                dst += copy_transl(dst, src + runstart, len, sf, df);
                runstart += len;
                تسلسل -= len;
                جب (تسلسل) {
                    len = SDL_min(تسلسل, max_transl_تسلسل);
                    جوڑو_TRANSL_COUNTS(0, len);
                    dst += copy_transl(dst, src + runstart, len, sf, df);
                    runstart += len;
                    تسلسل -= len;
                }
                اگر (!blankline) {
                    lastline = dst;
                }
            } جب (x < w);

            src += surface->pitch >> 2;
        }
        dst = lastline; // back up past trailing blank lines
        جوڑو_OPAQUE_COUNTS(0, 0);
    }

#تعریف_منسوخ جوڑو_OPAQUE_COUNTS
#تعریف_منسوخ جوڑو_TRANSL_COUNTS

    // reallocate the buffer to release unused memory
    {
        Uint8 *p = (Uint8 *)SDL_realloc(rlebuf, dst - rlebuf);
        اگر (!p) {
            p = rlebuf;
        }
        surface->map.ڈیٹا = p;
    }

    واپس true;
}

ساکن Uint32 getpix_8(ثابت Uint8 *srcbuf)
{
    واپس *srcbuf;
}

ساکن Uint32 getpix_16(ثابت Uint8 *srcbuf)
{
    واپس *(ثابت Uint16 *)srcbuf;
}

ساکن Uint32 getpix_24(ثابت Uint8 *srcbuf)
{
#اگر SDL_BYTEORDER == SDL_LIL_ENDIAN
    واپس srcbuf[0] + (srcbuf[1] << 8) + (srcbuf[2] << 16);
#ورنہ
    واپس (srcbuf[0] << 16) + (srcbuf[1] << 8) + srcbuf[2];
#اگر_ختم
}

ساکن Uint32 getpix_32(ثابت Uint8 *srcbuf)
{
    واپس *(ثابت Uint32 *)srcbuf;
}

قسمتعریف Uint32 (*getpix_func)(ثابت Uint8 *);

ساکن ثابت getpix_func getpixes[4] = {
    getpix_8, getpix_16, getpix_24, getpix_32
};

ساکن bool RLEColorkeySurface(SDL_Surface *surface)
{
    SDL_Surface *dest;
    Uint8 *rlebuf, *dst;
    صحیح maxn;
    صحیح y;
    Uint8 *srcbuf, *lastline;
    صحیح maxsize = 0;
    ثابت صحیح bpp = surface->fmt->بائٹیں_فی_pixel;
    getpix_func getpix;
    Uint32 ckey, rgbmask;
    صحیح w, h;

    dest = surface->map.info.dst_surface;
    اگر (!dest) {
        واپس false;
    }

    // calculate the worst case size for the compressed surface
    انتخاب (bpp) {
    حالت 1:
        /* worst case is alternating opaque and transparent pixels,
           starting with an opaque pixel */
        maxsize = surface->h * 3 * (surface->w / 2 + 1) + 2;
        توڑو;
    حالت 2:
    حالت 3:
        // worst case is solid runs, at most 255 pixels wide
        maxsize = surface->h * (2 * (surface->w / 255 + 1) + surface->w * bpp) + 2;
        توڑو;
    حالت 4:
        // worst case is solid runs, at most 65535 pixels wide
        maxsize = surface->h * (4 * (surface->w / 65535 + 1) + surface->w * 4) + 4;
        توڑو;

    طےشدہ:
        واپس false;
    }

    maxsize += حجم(SDL_PixelFormat);
    rlebuf = (Uint8 *)SDL_malloc(maxsize);
    اگر (!rlebuf) {
        واپس false;
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

#تعریف_کرو جوڑو_COUNTS(n, m)                \
    اگر (bpp == 4) {                     \
        ((Uint16 *)dst)[0] = (Uint16)n; \
        ((Uint16 *)dst)[1] = (Uint16)m; \
        dst += 4;                       \
    } ورنہ {                            \
        dst[0] = (Uint8)n;              \
        dst[1] = (Uint8)m;              \
        dst += 2;                       \
    }

    برائے (y = 0; y < h; y++) {
        صحیح x = 0;
        صحیح blankline = 0;
        کرو {
            صحیح تسلسل, skip;
            صحیح len;
            صحیح runstart;
            صحیح skipstart = x;

            // find run of transparent, then opaque pixels
            جب (x < w && (getpix(srcbuf + x * bpp) & rgbmask) == ckey) {
                x++;
            }
            runstart = x;
            جب (x < w && (getpix(srcbuf + x * bpp) & rgbmask) != ckey) {
                x++;
            }
            skip = runstart - skipstart;
            اگر (skip == w) {
                blankline = 1;
            }
            تسلسل = x - runstart;

            // encode segment
            جب (skip > maxn) {
                جوڑو_COUNTS(maxn, 0);
                skip -= maxn;
            }
            len = SDL_min(تسلسل, maxn);
            جوڑو_COUNTS(skip, len);
            SDL_memcpy(dst, srcbuf + runstart * bpp, (size_t)len * bpp);
            dst += len * bpp;
            تسلسل -= len;
            runstart += len;
            جب (تسلسل) {
                len = SDL_min(تسلسل, maxn);
                جوڑو_COUNTS(0, len);
                SDL_memcpy(dst, srcbuf + runstart * bpp, (size_t)len * bpp);
                dst += len * bpp;
                runstart += len;
                تسلسل -= len;
            }
            اگر (!blankline) {
                lastline = dst;
            }
        } جب (x < w);

        srcbuf += surface->pitch;
    }
    dst = lastline; // back up bast trailing blank lines
    جوڑو_COUNTS(0, 0);

#تعریف_منسوخ جوڑو_COUNTS

    // reallocate the buffer to release unused memory
    {
        // If SDL_realloc returns NULL, the original block is left intact
        Uint8 *p = (Uint8 *)SDL_realloc(rlebuf, dst - rlebuf);
        اگر (!p) {
            p = rlebuf;
        }
        surface->map.ڈیٹا = p;
    }

    واپس true;
}

bool SDL_RLESurface(SDL_Surface *surface)
{
    صحیح flags;

    // Clear any previous RLE conversion
    اگر (surface->اندرونی_flags & SDL_اندرونی_SURFACE_RLEACCEL) {
        SDL_UnRLESurface(surface);
    }

    // We don't support RLE encoding of bitmaps
    اگر (SDL_BITSPERPIXEL(surface->format) < 8) {
        واپس false;
    }

    // Make sure the pixels are available
    اگر (!surface->pixels) {
        واپس false;
    }

    flags = surface->map.info.flags;
    اگر (flags & SDL_COPY_COLORKEY) {
        // ok
    } ورنہ اگر ((flags & SDL_COPY_BLEND) && SDL_ISPIXELFORMAT_ALPHA(surface->format)) {
        // ok
    } ورنہ {
        // If we don't have colorkey or blending, nothing to do...
        واپس false;
    }

    // Pass on combinations not supported
    اگر ((flags & SDL_COPY_MODULATE_COLOR) ||
        ((flags & SDL_COPY_MODULATE_ALPHA) && SDL_ISPIXELFORMAT_ALPHA(surface->format)) ||
        (flags & (SDL_COPY_BLEND_PREMULTIPLIED | SDL_COPY_جوڑو | SDL_COPY_جوڑو_PREMULTIPLIED | SDL_COPY_MOD | SDL_COPY_MUL)) ||
        (flags & SDL_COPY_قریب_ترین)) {
        واپس false;
    }

    // Encode and set up the blit
    اگر (!SDL_ISPIXELFORMAT_ALPHA(surface->format) || !(flags & SDL_COPY_BLEND)) {
        اگر (!surface->map.شناختی_عنصر) {
            واپس false;
        }
        اگر (!RLEColorkeySurface(surface)) {
            واپس false;
        }
        surface->map.blit = SDL_RLEBlit;
        surface->map.info.flags |= SDL_COPY_RLE_COLORKEY;
    } ورنہ {
        اگر (!RLEAlphaSurface(surface)) {
            واپس false;
        }
        surface->map.blit = SDL_RLEAlphaBlit;
        surface->map.info.flags |= SDL_COPY_RLE_ALPHAKEY;
    }

    اگر (!(surface->flags & SDL_SURFACE_PREALLOCATED)) {
        surface->saved_pixels = surface->pixels;
        surface->pixels = تہی;
    }

    // The surface is now accelerated
    surface->اندرونی_flags |= SDL_اندرونی_SURFACE_RLEACCEL;
    SDL_Update_Surface_تالا_Flag(surface);

    واپس true;
}

خالی SDL_UnRLESurface(SDL_Surface *surface)
{
    اگر (surface->اندرونی_flags & SDL_اندرونی_SURFACE_RLEACCEL) {
        surface->اندرونی_flags &= ~SDL_اندرونی_SURFACE_RLEACCEL;

        surface->map.info.flags &= ~(SDL_COPY_RLE_COLORKEY | SDL_COPY_RLE_ALPHAKEY);

        اگر (!(surface->flags & SDL_SURFACE_PREALLOCATED)) {
            surface->pixels = surface->saved_pixels;
            surface->saved_pixels = تہی;
        }

        SDL_free(surface->map.ڈیٹا);
        surface->map.ڈیٹا = تہی;

        SDL_InvalidateMap(&surface->map);

        SDL_Update_Surface_تالا_Flag(surface);
    }
}

#اگر_ختم // SDL_HAVE_RLE
