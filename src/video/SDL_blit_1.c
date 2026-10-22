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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifdef SDL_HAVE_BLIT_1

#ଅନ୍ତର୍ଭାଵ "SDL_surface_c.h"
#ଅନ୍ତର୍ଭାଵ "SDL_sysvideo.h"

// Functions to blit from 8-bit surfaces to other surfaces

ସ୍ଥିର ଶୂନ୍ୟ Blit1to1(SDL_BlitInfo *info)
{
#ifndef USE_DUFFS_LOOP
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା c;
#endif
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, height;
    Uint8 *src, *map, *dst;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = info->table;

    ଯେତେବେଳେ (height--) {
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
#ଅନ୍ୟଥା
        ପାଇଁ (c = width; c; --c) {
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
#ଯଦି (SDL_BYTEORDER == SDL_LIL_ENDIAN)
#define HI 1
#define LO 0
#ଅନ୍ୟଥା // ( SDL_BYTEORDER == SDL_BIG_ENDIAN )
#define HI 0
#define LO 1
#endif
#endif
ସ୍ଥିର ଶୂନ୍ୟ Blit1to2(SDL_BlitInfo *info)
{
#ifndef USE_DUFFS_LOOP
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା c;
#endif
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, height;
    Uint8 *src, *dst;
    Uint16 *map;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = (Uint16 *)info->table;

#ifdef USE_DUFFS_LOOP
    ଯେତେବେଳେ (height--) {
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
#ଅନ୍ୟଥା
    // Memory align at 4-byte boundary, if necessary
    ଯଦି ((long)dst & 0x03) {
        // Don't do anything if width is 0
        ଯଦି (width == 0) {
            ଫେରନ୍ତୁ;
        }
        --width;

        ଯେତେବେଳେ (height--) {
            // Perform copy alignment
            *(Uint16 *)dst = map[*src++];
            dst += 2;

            // Copy in 4 pixel chunks
            ପାଇଁ (c = width / 4; c; --c) {
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
            }
            // Get any leftovers
            ବାଛ (width & 3) {
            ସ୍ଥିତି 3:
                *(Uint16 *)dst = map[*src++];
                dst += 2;
                SDL_FALLTHROUGH;
            ସ୍ଥିତି 2:
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
                ଭାଙ୍ଗ;
            ସ୍ଥିତି 1:
                *(Uint16 *)dst = map[*src++];
                dst += 2;
                ଭାଙ୍ଗ;
            }
            src += srcskip;
            dst += dstskip;
        }
    } ଅନ୍ୟଥା {
        ଯେତେବେଳେ (height--) {
            // Copy in 4 pixel chunks
            ପାଇଁ (c = width / 4; c; --c) {
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
            }
            // Get any leftovers
            ବାଛ (width & 3) {
            ସ୍ଥିତି 3:
                *(Uint16 *)dst = map[*src++];
                dst += 2;
                SDL_FALLTHROUGH;
            ସ୍ଥିତି 2:
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
                ଭାଙ୍ଗ;
            ସ୍ଥିତି 1:
                *(Uint16 *)dst = map[*src++];
                dst += 2;
                ଭାଙ୍ଗ;
            }
            src += srcskip;
            dst += dstskip;
        }
    }
#endif // USE_DUFFS_LOOP
}

ସ୍ଥିର ଶୂନ୍ୟ Blit1to3(SDL_BlitInfo *info)
{
#ifndef USE_DUFFS_LOOP
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା c;
#endif
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା o;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, height;
    Uint8 *src, *map, *dst;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = info->table;

    ଯେତେବେଳେ (height--) {
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
#ଅନ୍ୟଥା
        ପାଇଁ (c = width; c; --c) {
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

ସ୍ଥିର ଶୂନ୍ୟ Blit1to4(SDL_BlitInfo *info)
{
#ifndef USE_DUFFS_LOOP
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା c;
#endif
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, height;
    Uint8 *src;
    Uint32 *map, *dst;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = (Uint32 *)info->dst;
    dstskip = info->dst_skip / 4;
    map = (Uint32 *)info->table;

    ଯେତେବେଳେ (height--) {
#ifdef USE_DUFFS_LOOP
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
            *dst++ = map[*src++];
        , width);
        /* *INDENT-ON* */ // clang-format on
#ଅନ୍ୟଥା
        ପାଇଁ (c = width / 4; c; --c) {
            *dst++ = map[*src++];
            *dst++ = map[*src++];
            *dst++ = map[*src++];
            *dst++ = map[*src++];
        }
        ବାଛ (width & 3) {
        ସ୍ଥିତି 3:
            *dst++ = map[*src++];
            SDL_FALLTHROUGH;
        ସ୍ଥିତି 2:
            *dst++ = map[*src++];
            SDL_FALLTHROUGH;
        ସ୍ଥିତି 1:
            *dst++ = map[*src++];
        }
#endif // USE_DUFFS_LOOP
        src += srcskip;
        dst += dstskip;
    }
}

ସ୍ଥିର ଶୂନ୍ୟ Blit1to1_ଚାବି(SDL_BlitInfo *info)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା width = info->dst_w;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା height = info->dst_h;
    Uint8 *src = info->src;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା dstskip = info->dst_skip;
    Uint8 *palmap = info->table;
    Uint32 ckey = info->colorkey;

    ଯଦି (palmap) {
        ଯେତେବେଳେ (height--) {
            /* *INDENT-OFF* */ // clang-format off
            DUFFS_LOOP_TRIVIAL(
            {
                ଯଦି ( *src != ckey ) {
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
    } ଅନ୍ୟଥା {
        ଯେତେବେଳେ (height--) {
            /* *INDENT-OFF* */ // clang-format off
            DUFFS_LOOP_TRIVIAL(
            {
                ଯଦି ( *src != ckey ) {
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

ସ୍ଥିର ଶୂନ୍ୟ Blit1to2_ଚାବି(SDL_BlitInfo *info)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା width = info->dst_w;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା height = info->dst_h;
    Uint8 *src = info->src;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା srcskip = info->src_skip;
    Uint16 *dstp = (Uint16 *)info->dst;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା dstskip = info->dst_skip;
    Uint16 *palmap = (Uint16 *)info->table;
    Uint32 ckey = info->colorkey;

    // Set up some basic variables
    dstskip /= 2;

    ଯେତେବେଳେ (height--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
        {
            ଯଦି ( *src != ckey ) {
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

ସ୍ଥିର ଶୂନ୍ୟ Blit1to3_ଚାବି(SDL_BlitInfo *info)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା width = info->dst_w;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା height = info->dst_h;
    Uint8 *src = info->src;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା dstskip = info->dst_skip;
    Uint8 *palmap = info->table;
    Uint32 ckey = info->colorkey;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା o;

    ଯେତେବେଳେ (height--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP(
        {
            ଯଦି ( *src != ckey ) {
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

ସ୍ଥିର ଶୂନ୍ୟ Blit1to4_ଚାବି(SDL_BlitInfo *info)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା width = info->dst_w;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା height = info->dst_h;
    Uint8 *src = info->src;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା srcskip = info->src_skip;
    Uint32 *dstp = (Uint32 *)info->dst;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା dstskip = info->dst_skip;
    Uint32 *palmap = (Uint32 *)info->table;
    Uint32 ckey = info->colorkey;

    // Set up some basic variables
    dstskip /= 4;

    ଯେତେବେଳେ (height--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
        {
            ଯଦି ( *src != ckey ) {
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

ସ୍ଥିର ଶୂନ୍ୟ Blit1toNAlpha(SDL_BlitInfo *info)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା width = info->dst_w;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା height = info->dst_h;
    Uint8 *src = info->src;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା dstskip = info->dst_skip;
    ଅଚଳ SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    ଅଚଳ SDL_Color *srcpal = info->src_pal->colors;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା dstbpp;
    Uint32 pixelvalue;
    unsigned sR, sG, sB, sA;
    unsigned dR, dG, dB, dA;
    ଅଚଳ unsigned A = info->a;

    // Set up some basic variables
    dstbpp = dstfmt->bytes_per_pixel;

    ଯେତେବେଳେ (height--) {
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

ସ୍ଥିର ଶୂନ୍ୟ Blit1to_NAlpha_ଚାବି(SDL_BlitInfo *info)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା width = info->dst_w;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା height = info->dst_h;
    Uint8 *src = info->src;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା dstskip = info->dst_skip;
    ଅଚଳ SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    ଅଚଳ SDL_Color *srcpal = info->src_pal->colors;
    Uint32 ckey = info->colorkey;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା dstbpp;
    Uint32 pixelvalue;
    unsigned sR, sG, sB, sA;
    unsigned dR, dG, dB, dA;
    ଅଚଳ unsigned A = info->a;

    // Set up some basic variables
    dstbpp = dstfmt->bytes_per_pixel;

    ଯେତେବେଳେ (height--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP(
        {
            ଯଦି ( *src != ckey ) {
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

ସ୍ଥିର ଅଚଳ SDL_BlitFunc one_blit[] = {
    (SDL_BlitFunc)ଖାଲି, Blit1to1, Blit1to2, Blit1to3, Blit1to4
};

ସ୍ଥିର ଅଚଳ SDL_BlitFunc one_blitkey[] = {
    (SDL_BlitFunc)ଖାଲି, Blit1to1_ଚାବି, Blit1to2_ଚାବି, Blit1to3_ଚାବି, Blit1to4_ଚାବି
};

SDL_BlitFunc SDL_CalculateBlit1(SDL_Surface *surface)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା which;

    ଯଦି (SDL_BITSPERPIXEL(surface->map.info.dst_fmt->format) < 8) {
        which = 0;
    } ଅନ୍ୟଥା {
        which = SDL_BYTESPERPIXEL(surface->map.info.dst_fmt->format);
    }

    ବାଛ (surface->map.info.flags & ~SDL_COPY_RLE_MASK) {
    ସ୍ଥିତି 0:
        ଯଦି (which < SDL_arraysize(one_blit)) {
            ଫେରନ୍ତୁ one_blit[which];
        }
        ଭାଙ୍ଗ;

    ସ୍ଥିତି SDL_COPY_COLORKEY:
        ଯଦି (which < SDL_arraysize(one_blitkey)) {
            ଫେରନ୍ତୁ one_blitkey[which];
        }
        ଭାଙ୍ଗ;

    ସ୍ଥିତି SDL_COPY_COLORKEY | SDL_COPY_BLEND:  // this is not super-robust but handles a specific case we found sdl12-compat.
        ଯଦି (surface->map.info.a == 255) {
            ଯଦି (which < SDL_arraysize(one_blitkey)) {
                ଫେରନ୍ତୁ one_blitkey[which];
            }
        } ଅନ୍ୟଥା {
            ଫେରନ୍ତୁ which >= 2 ? Blit1to_NAlpha_ଚାବି : (SDL_BlitFunc)ଖାଲି;
        }
        ଭାଙ୍ଗ;

    ସ୍ଥିତି SDL_COPY_BLEND:
    ସ୍ଥିତି SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
        /* Supporting 8bpp->8bpp alpha is doable but requires lots of
           tables which consume space and takes time to precompute,
           so is better left to the user */
        ଫେରନ୍ତୁ which >= 2 ? Blit1toNAlpha : (SDL_BlitFunc)ଖାଲି;

    ସ୍ଥିତି SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
        ଫେରନ୍ତୁ which >= 2 ? Blit1to_NAlpha_ଚାବି : (SDL_BlitFunc)ଖାଲି;
    }
    ଫେରନ୍ତୁ (SDL_BlitFunc)ଖାଲି;
}

#endif // SDL_HAVE_BLIT_1
