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
#অন্তর্ভাব "SDL_internal.h"

#ifdef SDL_HAVE_BLIT_1

#অন্তর্ভাব "SDL_surface_c.h"
#অন্তর্ভাব "SDL_sysvideo.h"

// Functions to blit from 8-bit surfaces to other surfaces

স্থির শূন্য Blit1to1(SDL_BlitInfo *info)
{
#ifndef USE_DUFFS_LOOP
    পূর্ণসংখ্যা c;
#endif
    পূর্ণসংখ্যা width, height;
    Uint8 *src, *map, *dst;
    পূর্ণসংখ্যা srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = info->table;

    যখন (height--) {
#ifdef USE_DUFFS_LOOP
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
            {
              *dst = map[*src];
            }
            dst++;
            src++;
        , width);
        /* *INDENT-ON* */ // clang-format on
#অন্যথা
        জন্য (c = width; c; --c) {
            *dst = map[*src];
            dst++;
            src++;
        }
#endif
        src += srcskip;
        dst += dstskip;
    }
}

// This is now endian dependent
#ifndef USE_DUFFS_LOOP
#যদি (SDL_BYTEORDER == SDL_LIL_ENDIAN)
#define HI 1
#define LO 0
#অন্যথা // ( SDL_BYTEORDER == SDL_BIG_ENDIAN )
#define HI 0
#define LO 1
#endif
#endif
স্থির শূন্য Blit1to2(SDL_BlitInfo *info)
{
#ifndef USE_DUFFS_LOOP
    পূর্ণসংখ্যা c;
#endif
    পূর্ণসংখ্যা width, height;
    Uint8 *src, *dst;
    Uint16 *map;
    পূর্ণসংখ্যা srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = (Uint16 *)info->table;

#ifdef USE_DUFFS_LOOP
    যখন (height--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
        {
            *(Uint16 *)dst = map[*src++];
            dst += 2;
        },
        width);
        /* *INDENT-ON* */ // clang-format on
        src += srcskip;
        dst += dstskip;
    }
#অন্যথা
    // Memory align at 4-byte boundary, if necessary
    যদি ((long)dst & 0x03) {
        // Don't do anything if width is 0
        যদি (width == 0) {
            ফেরত;
        }
        --width;

        যখন (height--) {
            // Perform copy alignment
            *(Uint16 *)dst = map[*src++];
            dst += 2;

            // Copy in 4 pixel chunks
            জন্য (c = width / 4; c; --c) {
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
            }
            // Get any leftovers
            নির্বাচন (width & 3) {
            ক্ষেত্র 3:
                *(Uint16 *)dst = map[*src++];
                dst += 2;
                SDL_FALLTHROUGH;
            ক্ষেত্র 2:
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
                বিরতি;
            ক্ষেত্র 1:
                *(Uint16 *)dst = map[*src++];
                dst += 2;
                বিরতি;
            }
            src += srcskip;
            dst += dstskip;
        }
    } অন্যথা {
        যখন (height--) {
            // Copy in 4 pixel chunks
            জন্য (c = width / 4; c; --c) {
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
            }
            // Get any leftovers
            নির্বাচন (width & 3) {
            ক্ষেত্র 3:
                *(Uint16 *)dst = map[*src++];
                dst += 2;
                SDL_FALLTHROUGH;
            ক্ষেত্র 2:
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
                বিরতি;
            ক্ষেত্র 1:
                *(Uint16 *)dst = map[*src++];
                dst += 2;
                বিরতি;
            }
            src += srcskip;
            dst += dstskip;
        }
    }
#endif // USE_DUFFS_LOOP
}

স্থির শূন্য Blit1to3(SDL_BlitInfo *info)
{
#ifndef USE_DUFFS_LOOP
    পূর্ণসংখ্যা c;
#endif
    পূর্ণসংখ্যা o;
    পূর্ণসংখ্যা width, height;
    Uint8 *src, *map, *dst;
    পূর্ণসংখ্যা srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = info->table;

    যখন (height--) {
#ifdef USE_DUFFS_LOOP
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP(
            {
                o = *src * 4;
                dst[0] = map[o++];
                dst[1] = map[o++];
                dst[2] = map[o++];
            }
            src++;
            dst += 3;
        , width);
        /* *INDENT-ON* */ // clang-format on
#অন্যথা
        জন্য (c = width; c; --c) {
            o = *src * 4;
            dst[0] = map[o++];
            dst[1] = map[o++];
            dst[2] = map[o++];
            src++;
            dst += 3;
        }
#endif // USE_DUFFS_LOOP
        src += srcskip;
        dst += dstskip;
    }
}

স্থির শূন্য Blit1to4(SDL_BlitInfo *info)
{
#ifndef USE_DUFFS_LOOP
    পূর্ণসংখ্যা c;
#endif
    পূর্ণসংখ্যা width, height;
    Uint8 *src;
    Uint32 *map, *dst;
    পূর্ণসংখ্যা srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = (Uint32 *)info->dst;
    dstskip = info->dst_skip / 4;
    map = (Uint32 *)info->table;

    যখন (height--) {
#ifdef USE_DUFFS_LOOP
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
            *dst++ = map[*src++];
        , width);
        /* *INDENT-ON* */ // clang-format on
#অন্যথা
        জন্য (c = width / 4; c; --c) {
            *dst++ = map[*src++];
            *dst++ = map[*src++];
            *dst++ = map[*src++];
            *dst++ = map[*src++];
        }
        নির্বাচন (width & 3) {
        ক্ষেত্র 3:
            *dst++ = map[*src++];
            SDL_FALLTHROUGH;
        ক্ষেত্র 2:
            *dst++ = map[*src++];
            SDL_FALLTHROUGH;
        ক্ষেত্র 1:
            *dst++ = map[*src++];
        }
#endif // USE_DUFFS_LOOP
        src += srcskip;
        dst += dstskip;
    }
}

স্থির শূন্য Blit1to1_চাবি(SDL_BlitInfo *info)
{
    পূর্ণসংখ্যা width = info->dst_w;
    পূর্ণসংখ্যা height = info->dst_h;
    Uint8 *src = info->src;
    পূর্ণসংখ্যা srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    পূর্ণসংখ্যা dstskip = info->dst_skip;
    Uint8 *palmap = info->table;
    Uint32 ckey = info->colorkey;

    যদি (palmap) {
        যখন (height--) {
            /* *INDENT-OFF* */ // clang-format off
            DUFFS_LOOP_TRIVIAL(
            {
                যদি ( *src != ckey ) {
                  *dst = palmap[*src];
                }
                dst++;
                src++;
            },
            width);
            /* *INDENT-ON* */ // clang-format on
            src += srcskip;
            dst += dstskip;
        }
    } অন্যথা {
        যখন (height--) {
            /* *INDENT-OFF* */ // clang-format off
            DUFFS_LOOP_TRIVIAL(
            {
                যদি ( *src != ckey ) {
                  *dst = *src;
                }
                dst++;
                src++;
            },
            width);
            /* *INDENT-ON* */ // clang-format on
            src += srcskip;
            dst += dstskip;
        }
    }
}

স্থির শূন্য Blit1to2_চাবি(SDL_BlitInfo *info)
{
    পূর্ণসংখ্যা width = info->dst_w;
    পূর্ণসংখ্যা height = info->dst_h;
    Uint8 *src = info->src;
    পূর্ণসংখ্যা srcskip = info->src_skip;
    Uint16 *dstp = (Uint16 *)info->dst;
    পূর্ণসংখ্যা dstskip = info->dst_skip;
    Uint16 *palmap = (Uint16 *)info->table;
    Uint32 ckey = info->colorkey;

    // Set up some basic variables
    dstskip /= 2;

    যখন (height--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
        {
            যদি ( *src != ckey ) {
                *dstp=palmap[*src];
            }
            src++;
            dstp++;
        },
        width);
        /* *INDENT-ON* */ // clang-format on
        src += srcskip;
        dstp += dstskip;
    }
}

স্থির শূন্য Blit1to3_চাবি(SDL_BlitInfo *info)
{
    পূর্ণসংখ্যা width = info->dst_w;
    পূর্ণসংখ্যা height = info->dst_h;
    Uint8 *src = info->src;
    পূর্ণসংখ্যা srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    পূর্ণসংখ্যা dstskip = info->dst_skip;
    Uint8 *palmap = info->table;
    Uint32 ckey = info->colorkey;
    পূর্ণসংখ্যা o;

    যখন (height--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP(
        {
            যদি ( *src != ckey ) {
                o = *src * 4;
                dst[0] = palmap[o++];
                dst[1] = palmap[o++];
                dst[2] = palmap[o++];
            }
            src++;
            dst += 3;
        },
        width);
        /* *INDENT-ON* */ // clang-format on
        src += srcskip;
        dst += dstskip;
    }
}

স্থির শূন্য Blit1to4_চাবি(SDL_BlitInfo *info)
{
    পূর্ণসংখ্যা width = info->dst_w;
    পূর্ণসংখ্যা height = info->dst_h;
    Uint8 *src = info->src;
    পূর্ণসংখ্যা srcskip = info->src_skip;
    Uint32 *dstp = (Uint32 *)info->dst;
    পূর্ণসংখ্যা dstskip = info->dst_skip;
    Uint32 *palmap = (Uint32 *)info->table;
    Uint32 ckey = info->colorkey;

    // Set up some basic variables
    dstskip /= 4;

    যখন (height--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
        {
            যদি ( *src != ckey ) {
                *dstp = palmap[*src];
            }
            src++;
            dstp++;
        },
        width);
        /* *INDENT-ON* */ // clang-format on
        src += srcskip;
        dstp += dstskip;
    }
}

স্থির শূন্য Blit1toNAlpha(SDL_BlitInfo *info)
{
    পূর্ণসংখ্যা width = info->dst_w;
    পূর্ণসংখ্যা height = info->dst_h;
    Uint8 *src = info->src;
    পূর্ণসংখ্যা srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    পূর্ণসংখ্যা dstskip = info->dst_skip;
    ধ্রুবক SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    ধ্রুবক SDL_Color *srcpal = info->src_pal->colors;
    পূর্ণসংখ্যা dstbpp;
    Uint32 pixelvalue;
    unsigned sR, sG, sB, sA;
    unsigned dR, dG, dB, dA;
    ধ্রুবক unsigned A = info->a;

    // Set up some basic variables
    dstbpp = dstfmt->bytes_per_pixel;

    যখন (height--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP(
        {
            sR = srcpal[*src].r;
            sG = srcpal[*src].g;
            sB = srcpal[*src].b;
            sA = (srcpal[*src].a * A) / 255;
            DISEMBLE_RGBA(dst, dstbpp, dstfmt, pixelvalue, dR, dG, dB, dA);
            ALPHA_BLEND_RGBA(sR, sG, sB, sA, dR, dG, dB, dA);
            ASSEMBLE_RGBA(dst, dstbpp, dstfmt, dR, dG, dB, dA);
            src++;
            dst += dstbpp;
        },
        width);
        /* *INDENT-ON* */ // clang-format on
        src += srcskip;
        dst += dstskip;
    }
}

স্থির শূন্য Blit1to_NAlpha_চাবি(SDL_BlitInfo *info)
{
    পূর্ণসংখ্যা width = info->dst_w;
    পূর্ণসংখ্যা height = info->dst_h;
    Uint8 *src = info->src;
    পূর্ণসংখ্যা srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    পূর্ণসংখ্যা dstskip = info->dst_skip;
    ধ্রুবক SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    ধ্রুবক SDL_Color *srcpal = info->src_pal->colors;
    Uint32 ckey = info->colorkey;
    পূর্ণসংখ্যা dstbpp;
    Uint32 pixelvalue;
    unsigned sR, sG, sB, sA;
    unsigned dR, dG, dB, dA;
    ধ্রুবক unsigned A = info->a;

    // Set up some basic variables
    dstbpp = dstfmt->bytes_per_pixel;

    যখন (height--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP(
        {
            যদি ( *src != ckey ) {
                sR = srcpal[*src].r;
                sG = srcpal[*src].g;
                sB = srcpal[*src].b;
                sA = (srcpal[*src].a * A) / 255;
                DISEMBLE_RGBA(dst, dstbpp, dstfmt, pixelvalue, dR, dG, dB, dA);
                ALPHA_BLEND_RGBA(sR, sG, sB, sA, dR, dG, dB, dA);
                ASSEMBLE_RGBA(dst, dstbpp, dstfmt, dR, dG, dB, dA);
            }
            src++;
            dst += dstbpp;
        },
        width);
        /* *INDENT-ON* */ // clang-format on
        src += srcskip;
        dst += dstskip;
    }
}

স্থির ধ্রুবক SDL_BlitFunc one_blit[] = {
    (SDL_BlitFunc)ফাঁকা, Blit1to1, Blit1to2, Blit1to3, Blit1to4
};

স্থির ধ্রুবক SDL_BlitFunc one_blitkey[] = {
    (SDL_BlitFunc)ফাঁকা, Blit1to1_চাবি, Blit1to2_চাবি, Blit1to3_চাবি, Blit1to4_চাবি
};

SDL_BlitFunc SDL_CalculateBlit1(SDL_Surface *surface)
{
    পূর্ণসংখ্যা which;

    যদি (SDL_BITSPERPIXEL(surface->map.info.dst_fmt->format) < 8) {
        which = 0;
    } অন্যথা {
        which = SDL_BYTESPERPIXEL(surface->map.info.dst_fmt->format);
    }

    নির্বাচন (surface->map.info.flags & ~SDL_COPY_RLE_MASK) {
    ক্ষেত্র 0:
        যদি (which < SDL_arraysize(one_blit)) {
            ফেরত one_blit[which];
        }
        বিরতি;

    ক্ষেত্র SDL_COPY_COLORKEY:
        যদি (which < SDL_arraysize(one_blitkey)) {
            ফেরত one_blitkey[which];
        }
        বিরতি;

    ক্ষেত্র SDL_COPY_COLORKEY | SDL_COPY_BLEND:  // this is not super-robust but handles a specific case we found sdl12-compat.
        যদি (surface->map.info.a == 255) {
            যদি (which < SDL_arraysize(one_blitkey)) {
                ফেরত one_blitkey[which];
            }
        } অন্যথা {
            ফেরত which >= 2 ? Blit1to_NAlpha_চাবি : (SDL_BlitFunc)ফাঁকা;
        }
        বিরতি;

    ক্ষেত্র SDL_COPY_BLEND:
    ক্ষেত্র SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
        /* Supporting 8bpp->8bpp alpha is doable but requires lots of
           tables which consume space and takes time to precompute,
           so is better left to the user */
        ফেরত which >= 2 ? Blit1toNAlpha : (SDL_BlitFunc)ফাঁকা;

    ক্ষেত্র SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
        ফেরত which >= 2 ? Blit1to_NAlpha_চাবি : (SDL_BlitFunc)ফাঁকা;
    }
    ফেরত (SDL_BlitFunc)ফাঁকা;
}

#endif // SDL_HAVE_BLIT_1
