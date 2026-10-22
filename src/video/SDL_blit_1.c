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
#અન્તર્ભાવ "SDL_internal.h"

#ifdef SDL_HAVE_BLIT_1

#અન્તર્ભાવ "SDL_surface_c.h"
#અન્તર્ભાવ "SDL_sysvideo.h"

// Functions to blit from 8-bit surfaces to other surfaces

સ્થિર શૂન્ય Blit1to1(SDL_BlitInfo *info)
{
#ifndef USE_DUFFS_LOOP
    પૂર્ણાંક c;
#endif
    પૂર્ણાંક width, height;
    Uint8 *src, *map, *dst;
    પૂર્ણાંક srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = info->table;

    જ્યારે (height--) {
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
#નહીંતર
        માટે (c = width; c; --c) {
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
#જો (SDL_BYTEORDER == SDL_LIL_ENDIAN)
#define HI 1
#define LO 0
#નહીંતર // ( SDL_BYTEORDER == SDL_BIG_ENDIAN )
#define HI 0
#define LO 1
#endif
#endif
સ્થિર શૂન્ય Blit1to2(SDL_BlitInfo *info)
{
#ifndef USE_DUFFS_LOOP
    પૂર્ણાંક c;
#endif
    પૂર્ણાંક width, height;
    Uint8 *src, *dst;
    Uint16 *map;
    પૂર્ણાંક srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = (Uint16 *)info->table;

#ifdef USE_DUFFS_LOOP
    જ્યારે (height--) {
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
#નહીંતર
    // Memory align at 4-byte boundary, if necessary
    જો ((long)dst & 0x03) {
        // Don't do anything if width is 0
        જો (width == 0) {
            પાછા;
        }
        --width;

        જ્યારે (height--) {
            // Perform copy alignment
            *(Uint16 *)dst = map[*src++];
            dst += 2;

            // Copy in 4 pixel chunks
            માટે (c = width / 4; c; --c) {
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
            }
            // Get any leftovers
            પસંદગી (width & 3) {
            સ્થિતિ 3:
                *(Uint16 *)dst = map[*src++];
                dst += 2;
                SDL_FALLTHROUGH;
            સ્થિતિ 2:
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
                તોડો;
            સ્થિતિ 1:
                *(Uint16 *)dst = map[*src++];
                dst += 2;
                તોડો;
            }
            src += srcskip;
            dst += dstskip;
        }
    } નહીંતર {
        જ્યારે (height--) {
            // Copy in 4 pixel chunks
            માટે (c = width / 4; c; --c) {
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
            }
            // Get any leftovers
            પસંદગી (width & 3) {
            સ્થિતિ 3:
                *(Uint16 *)dst = map[*src++];
                dst += 2;
                SDL_FALLTHROUGH;
            સ્થિતિ 2:
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
                તોડો;
            સ્થિતિ 1:
                *(Uint16 *)dst = map[*src++];
                dst += 2;
                તોડો;
            }
            src += srcskip;
            dst += dstskip;
        }
    }
#endif // USE_DUFFS_LOOP
}

સ્થિર શૂન્ય Blit1to3(SDL_BlitInfo *info)
{
#ifndef USE_DUFFS_LOOP
    પૂર્ણાંક c;
#endif
    પૂર્ણાંક o;
    પૂર્ણાંક width, height;
    Uint8 *src, *map, *dst;
    પૂર્ણાંક srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = info->table;

    જ્યારે (height--) {
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
#નહીંતર
        માટે (c = width; c; --c) {
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

સ્થિર શૂન્ય Blit1to4(SDL_BlitInfo *info)
{
#ifndef USE_DUFFS_LOOP
    પૂર્ણાંક c;
#endif
    પૂર્ણાંક width, height;
    Uint8 *src;
    Uint32 *map, *dst;
    પૂર્ણાંક srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = (Uint32 *)info->dst;
    dstskip = info->dst_skip / 4;
    map = (Uint32 *)info->table;

    જ્યારે (height--) {
#ifdef USE_DUFFS_LOOP
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
            *dst++ = map[*src++];
        , width);
        /* *INDENT-ON* */ // clang-format on
#નહીંતર
        માટે (c = width / 4; c; --c) {
            *dst++ = map[*src++];
            *dst++ = map[*src++];
            *dst++ = map[*src++];
            *dst++ = map[*src++];
        }
        પસંદગી (width & 3) {
        સ્થિતિ 3:
            *dst++ = map[*src++];
            SDL_FALLTHROUGH;
        સ્થિતિ 2:
            *dst++ = map[*src++];
            SDL_FALLTHROUGH;
        સ્થિતિ 1:
            *dst++ = map[*src++];
        }
#endif // USE_DUFFS_LOOP
        src += srcskip;
        dst += dstskip;
    }
}

સ્થિર શૂન્ય Blit1to1_ચાવી(SDL_BlitInfo *info)
{
    પૂર્ણાંક width = info->dst_w;
    પૂર્ણાંક height = info->dst_h;
    Uint8 *src = info->src;
    પૂર્ણાંક srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    પૂર્ણાંક dstskip = info->dst_skip;
    Uint8 *palmap = info->table;
    Uint32 ckey = info->colorkey;

    જો (palmap) {
        જ્યારે (height--) {
            /* *INDENT-OFF* */ // clang-format off
            DUFFS_LOOP_TRIVIAL(
            {
                જો ( *src != ckey ) {
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
    } નહીંતર {
        જ્યારે (height--) {
            /* *INDENT-OFF* */ // clang-format off
            DUFFS_LOOP_TRIVIAL(
            {
                જો ( *src != ckey ) {
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

સ્થિર શૂન્ય Blit1to2_ચાવી(SDL_BlitInfo *info)
{
    પૂર્ણાંક width = info->dst_w;
    પૂર્ણાંક height = info->dst_h;
    Uint8 *src = info->src;
    પૂર્ણાંક srcskip = info->src_skip;
    Uint16 *dstp = (Uint16 *)info->dst;
    પૂર્ણાંક dstskip = info->dst_skip;
    Uint16 *palmap = (Uint16 *)info->table;
    Uint32 ckey = info->colorkey;

    // Set up some basic variables
    dstskip /= 2;

    જ્યારે (height--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
        {
            જો ( *src != ckey ) {
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

સ્થિર શૂન્ય Blit1to3_ચાવી(SDL_BlitInfo *info)
{
    પૂર્ણાંક width = info->dst_w;
    પૂર્ણાંક height = info->dst_h;
    Uint8 *src = info->src;
    પૂર્ણાંક srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    પૂર્ણાંક dstskip = info->dst_skip;
    Uint8 *palmap = info->table;
    Uint32 ckey = info->colorkey;
    પૂર્ણાંક o;

    જ્યારે (height--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP(
        {
            જો ( *src != ckey ) {
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

સ્થિર શૂન્ય Blit1to4_ચાવી(SDL_BlitInfo *info)
{
    પૂર્ણાંક width = info->dst_w;
    પૂર્ણાંક height = info->dst_h;
    Uint8 *src = info->src;
    પૂર્ણાંક srcskip = info->src_skip;
    Uint32 *dstp = (Uint32 *)info->dst;
    પૂર્ણાંક dstskip = info->dst_skip;
    Uint32 *palmap = (Uint32 *)info->table;
    Uint32 ckey = info->colorkey;

    // Set up some basic variables
    dstskip /= 4;

    જ્યારે (height--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
        {
            જો ( *src != ckey ) {
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

સ્થિર શૂન્ય Blit1toNAlpha(SDL_BlitInfo *info)
{
    પૂર્ણાંક width = info->dst_w;
    પૂર્ણાંક height = info->dst_h;
    Uint8 *src = info->src;
    પૂર્ણાંક srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    પૂર્ણાંક dstskip = info->dst_skip;
    અચલ SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    અચલ SDL_Color *srcpal = info->src_pal->colors;
    પૂર્ણાંક dstbpp;
    Uint32 pixelvalue;
    unsigned sR, sG, sB, sA;
    unsigned dR, dG, dB, dA;
    અચલ unsigned A = info->a;

    // Set up some basic variables
    dstbpp = dstfmt->bytes_per_pixel;

    જ્યારે (height--) {
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

સ્થિર શૂન્ય Blit1to_NAlpha_ચાવી(SDL_BlitInfo *info)
{
    પૂર્ણાંક width = info->dst_w;
    પૂર્ણાંક height = info->dst_h;
    Uint8 *src = info->src;
    પૂર્ણાંક srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    પૂર્ણાંક dstskip = info->dst_skip;
    અચલ SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    અચલ SDL_Color *srcpal = info->src_pal->colors;
    Uint32 ckey = info->colorkey;
    પૂર્ણાંક dstbpp;
    Uint32 pixelvalue;
    unsigned sR, sG, sB, sA;
    unsigned dR, dG, dB, dA;
    અચલ unsigned A = info->a;

    // Set up some basic variables
    dstbpp = dstfmt->bytes_per_pixel;

    જ્યારે (height--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP(
        {
            જો ( *src != ckey ) {
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

સ્થિર અચલ SDL_BlitFunc one_blit[] = {
    (SDL_BlitFunc)ખાલી, Blit1to1, Blit1to2, Blit1to3, Blit1to4
};

સ્થિર અચલ SDL_BlitFunc one_blitkey[] = {
    (SDL_BlitFunc)ખાલી, Blit1to1_ચાવી, Blit1to2_ચાવી, Blit1to3_ચાવી, Blit1to4_ચાવી
};

SDL_BlitFunc SDL_CalculateBlit1(SDL_Surface *surface)
{
    પૂર્ણાંક which;

    જો (SDL_BITSPERPIXEL(surface->map.info.dst_fmt->format) < 8) {
        which = 0;
    } નહીંતર {
        which = SDL_BYTESPERPIXEL(surface->map.info.dst_fmt->format);
    }

    પસંદગી (surface->map.info.flags & ~SDL_COPY_RLE_MASK) {
    સ્થિતિ 0:
        જો (which < SDL_arraysize(one_blit)) {
            પાછા one_blit[which];
        }
        તોડો;

    સ્થિતિ SDL_COPY_COLORKEY:
        જો (which < SDL_arraysize(one_blitkey)) {
            પાછા one_blitkey[which];
        }
        તોડો;

    સ્થિતિ SDL_COPY_COLORKEY | SDL_COPY_BLEND:  // this is not super-robust but handles a specific case we found sdl12-compat.
        જો (surface->map.info.a == 255) {
            જો (which < SDL_arraysize(one_blitkey)) {
                પાછા one_blitkey[which];
            }
        } નહીંતર {
            પાછા which >= 2 ? Blit1to_NAlpha_ચાવી : (SDL_BlitFunc)ખાલી;
        }
        તોડો;

    સ્થિતિ SDL_COPY_BLEND:
    સ્થિતિ SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
        /* Supporting 8bpp->8bpp alpha is doable but requires lots of
           tables which consume space and takes time to precompute,
           so is better left to the user */
        પાછા which >= 2 ? Blit1toNAlpha : (SDL_BlitFunc)ખાલી;

    સ્થિતિ SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
        પાછા which >= 2 ? Blit1to_NAlpha_ચાવી : (SDL_BlitFunc)ખાલી;
    }
    પાછા (SDL_BlitFunc)ખાલી;
}

#endif // SDL_HAVE_BLIT_1
