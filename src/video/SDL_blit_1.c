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

#ifdef SDL_HAVE_BLIT_1

#ಅನ್ತರ್ಭಾವ "SDL_surface_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_sysvideo.h"

// Functions to blit from 8-bit surfaces to other surfaces

ಸ್ಥಿರ ಶೂನ್ಯ Blit1to1(SDL_BlitInfo *info)
{
#ifndef USE_DUFFS_LOOP
    ಪೂರ್ಣಾಙ್ಕ c;
#endif
    ಪೂರ್ಣಾಙ್ಕ width, height;
    Uint8 *src, *map, *dst;
    ಪೂರ್ಣಾಙ್ಕ srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = info->table;

    ಯಾವತ್ (height--) {
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
#ಅನ್ಯಥಾ
        ಪ್ರತಿ (c = width; c; --c) {
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
#ಯದಿ (SDL_BYTEORDER == SDL_LIL_ENDIAN)
#define HI 1
#define LO 0
#ಅನ್ಯಥಾ // ( SDL_BYTEORDER == SDL_BIG_ENDIAN )
#define HI 0
#define LO 1
#endif
#endif
ಸ್ಥಿರ ಶೂನ್ಯ Blit1to2(SDL_BlitInfo *info)
{
#ifndef USE_DUFFS_LOOP
    ಪೂರ್ಣಾಙ್ಕ c;
#endif
    ಪೂರ್ಣಾಙ್ಕ width, height;
    Uint8 *src, *dst;
    Uint16 *map;
    ಪೂರ್ಣಾಙ್ಕ srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = (Uint16 *)info->table;

#ifdef USE_DUFFS_LOOP
    ಯಾವತ್ (height--) {
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
#ಅನ್ಯಥಾ
    // Memory align at 4-byte boundary, if necessary
    ಯದಿ ((long)dst & 0x03) {
        // Don't do anything if width is 0
        ಯದಿ (width == 0) {
            ಪ್ರತ್ಯಾಗಮ;
        }
        --width;

        ಯಾವತ್ (height--) {
            // Perform copy alignment
            *(Uint16 *)dst = map[*src++];
            dst += 2;

            // Copy in 4 pixel chunks
            ಪ್ರತಿ (c = width / 4; c; --c) {
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
            }
            // Get any leftovers
            ವಿಕಲ್ಪ (width & 3) {
            ಪಕ್ಷ 3:
                *(Uint16 *)dst = map[*src++];
                dst += 2;
                SDL_FALLTHROUGH;
            ಪಕ್ಷ 2:
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
                ಭಙ್ಗ;
            ಪಕ್ಷ 1:
                *(Uint16 *)dst = map[*src++];
                dst += 2;
                ಭಙ್ಗ;
            }
            src += srcskip;
            dst += dstskip;
        }
    } ಅನ್ಯಥಾ {
        ಯಾವತ್ (height--) {
            // Copy in 4 pixel chunks
            ಪ್ರತಿ (c = width / 4; c; --c) {
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
            }
            // Get any leftovers
            ವಿಕಲ್ಪ (width & 3) {
            ಪಕ್ಷ 3:
                *(Uint16 *)dst = map[*src++];
                dst += 2;
                SDL_FALLTHROUGH;
            ಪಕ್ಷ 2:
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
                ಭಙ್ಗ;
            ಪಕ್ಷ 1:
                *(Uint16 *)dst = map[*src++];
                dst += 2;
                ಭಙ್ಗ;
            }
            src += srcskip;
            dst += dstskip;
        }
    }
#endif // USE_DUFFS_LOOP
}

ಸ್ಥಿರ ಶೂನ್ಯ Blit1to3(SDL_BlitInfo *info)
{
#ifndef USE_DUFFS_LOOP
    ಪೂರ್ಣಾಙ್ಕ c;
#endif
    ಪೂರ್ಣಾಙ್ಕ o;
    ಪೂರ್ಣಾಙ್ಕ width, height;
    Uint8 *src, *map, *dst;
    ಪೂರ್ಣಾಙ್ಕ srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = info->table;

    ಯಾವತ್ (height--) {
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
#ಅನ್ಯಥಾ
        ಪ್ರತಿ (c = width; c; --c) {
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

ಸ್ಥಿರ ಶೂನ್ಯ Blit1to4(SDL_BlitInfo *info)
{
#ifndef USE_DUFFS_LOOP
    ಪೂರ್ಣಾಙ್ಕ c;
#endif
    ಪೂರ್ಣಾಙ್ಕ width, height;
    Uint8 *src;
    Uint32 *map, *dst;
    ಪೂರ್ಣಾಙ್ಕ srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = (Uint32 *)info->dst;
    dstskip = info->dst_skip / 4;
    map = (Uint32 *)info->table;

    ಯಾವತ್ (height--) {
#ifdef USE_DUFFS_LOOP
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
            *dst++ = map[*src++];
        , width);
        /* *INDENT-ON* */ // clang-format on
#ಅನ್ಯಥಾ
        ಪ್ರತಿ (c = width / 4; c; --c) {
            *dst++ = map[*src++];
            *dst++ = map[*src++];
            *dst++ = map[*src++];
            *dst++ = map[*src++];
        }
        ವಿಕಲ್ಪ (width & 3) {
        ಪಕ್ಷ 3:
            *dst++ = map[*src++];
            SDL_FALLTHROUGH;
        ಪಕ್ಷ 2:
            *dst++ = map[*src++];
            SDL_FALLTHROUGH;
        ಪಕ್ಷ 1:
            *dst++ = map[*src++];
        }
#endif // USE_DUFFS_LOOP
        src += srcskip;
        dst += dstskip;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Blit1to1_ಕೀಲಿ(SDL_BlitInfo *info)
{
    ಪೂರ್ಣಾಙ್ಕ width = info->dst_w;
    ಪೂರ್ಣಾಙ್ಕ height = info->dst_h;
    Uint8 *src = info->src;
    ಪೂರ್ಣಾಙ್ಕ srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    ಪೂರ್ಣಾಙ್ಕ dstskip = info->dst_skip;
    Uint8 *palmap = info->table;
    Uint32 ckey = info->colorkey;

    ಯದಿ (palmap) {
        ಯಾವತ್ (height--) {
            /* *INDENT-OFF* */ // clang-format off
            DUFFS_LOOP_TRIVIAL(
            {
                ಯದಿ ( *src != ckey ) {
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
    } ಅನ್ಯಥಾ {
        ಯಾವತ್ (height--) {
            /* *INDENT-OFF* */ // clang-format off
            DUFFS_LOOP_TRIVIAL(
            {
                ಯದಿ ( *src != ckey ) {
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

ಸ್ಥಿರ ಶೂನ್ಯ Blit1to2_ಕೀಲಿ(SDL_BlitInfo *info)
{
    ಪೂರ್ಣಾಙ್ಕ width = info->dst_w;
    ಪೂರ್ಣಾಙ್ಕ height = info->dst_h;
    Uint8 *src = info->src;
    ಪೂರ್ಣಾಙ್ಕ srcskip = info->src_skip;
    Uint16 *dstp = (Uint16 *)info->dst;
    ಪೂರ್ಣಾಙ್ಕ dstskip = info->dst_skip;
    Uint16 *palmap = (Uint16 *)info->table;
    Uint32 ckey = info->colorkey;

    // Set up some basic variables
    dstskip /= 2;

    ಯಾವತ್ (height--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
        {
            ಯದಿ ( *src != ckey ) {
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

ಸ್ಥಿರ ಶೂನ್ಯ Blit1to3_ಕೀಲಿ(SDL_BlitInfo *info)
{
    ಪೂರ್ಣಾಙ್ಕ width = info->dst_w;
    ಪೂರ್ಣಾಙ್ಕ height = info->dst_h;
    Uint8 *src = info->src;
    ಪೂರ್ಣಾಙ್ಕ srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    ಪೂರ್ಣಾಙ್ಕ dstskip = info->dst_skip;
    Uint8 *palmap = info->table;
    Uint32 ckey = info->colorkey;
    ಪೂರ್ಣಾಙ್ಕ o;

    ಯಾವತ್ (height--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP(
        {
            ಯದಿ ( *src != ckey ) {
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

ಸ್ಥಿರ ಶೂನ್ಯ Blit1to4_ಕೀಲಿ(SDL_BlitInfo *info)
{
    ಪೂರ್ಣಾಙ್ಕ width = info->dst_w;
    ಪೂರ್ಣಾಙ್ಕ height = info->dst_h;
    Uint8 *src = info->src;
    ಪೂರ್ಣಾಙ್ಕ srcskip = info->src_skip;
    Uint32 *dstp = (Uint32 *)info->dst;
    ಪೂರ್ಣಾಙ್ಕ dstskip = info->dst_skip;
    Uint32 *palmap = (Uint32 *)info->table;
    Uint32 ckey = info->colorkey;

    // Set up some basic variables
    dstskip /= 4;

    ಯಾವತ್ (height--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
        {
            ಯದಿ ( *src != ckey ) {
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

ಸ್ಥಿರ ಶೂನ್ಯ Blit1toNAlpha(SDL_BlitInfo *info)
{
    ಪೂರ್ಣಾಙ್ಕ width = info->dst_w;
    ಪೂರ್ಣಾಙ್ಕ height = info->dst_h;
    Uint8 *src = info->src;
    ಪೂರ್ಣಾಙ್ಕ srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    ಪೂರ್ಣಾಙ್ಕ dstskip = info->dst_skip;
    ಧ್ರುವ SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    ಧ್ರುವ SDL_Color *srcpal = info->src_pal->colors;
    ಪೂರ್ಣಾಙ್ಕ dstbpp;
    Uint32 pixelvalue;
    unsigned sR, sG, sB, sA;
    unsigned dR, dG, dB, dA;
    ಧ್ರುವ unsigned A = info->a;

    // Set up some basic variables
    dstbpp = dstfmt->bytes_per_pixel;

    ಯಾವತ್ (height--) {
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

ಸ್ಥಿರ ಶೂನ್ಯ Blit1to_NAlpha_ಕೀಲಿ(SDL_BlitInfo *info)
{
    ಪೂರ್ಣಾಙ್ಕ width = info->dst_w;
    ಪೂರ್ಣಾಙ್ಕ height = info->dst_h;
    Uint8 *src = info->src;
    ಪೂರ್ಣಾಙ್ಕ srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    ಪೂರ್ಣಾಙ್ಕ dstskip = info->dst_skip;
    ಧ್ರುವ SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    ಧ್ರುವ SDL_Color *srcpal = info->src_pal->colors;
    Uint32 ckey = info->colorkey;
    ಪೂರ್ಣಾಙ್ಕ dstbpp;
    Uint32 pixelvalue;
    unsigned sR, sG, sB, sA;
    unsigned dR, dG, dB, dA;
    ಧ್ರುವ unsigned A = info->a;

    // Set up some basic variables
    dstbpp = dstfmt->bytes_per_pixel;

    ಯಾವತ್ (height--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP(
        {
            ಯದಿ ( *src != ckey ) {
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

ಸ್ಥಿರ ಧ್ರುವ SDL_BlitFunc one_blit[] = {
    (SDL_BlitFunc)ರಿಕ್ತ, Blit1to1, Blit1to2, Blit1to3, Blit1to4
};

ಸ್ಥಿರ ಧ್ರುವ SDL_BlitFunc one_blitkey[] = {
    (SDL_BlitFunc)ರಿಕ್ತ, Blit1to1_ಕೀಲಿ, Blit1to2_ಕೀಲಿ, Blit1to3_ಕೀಲಿ, Blit1to4_ಕೀಲಿ
};

SDL_BlitFunc SDL_CalculateBlit1(SDL_Surface *surface)
{
    ಪೂರ್ಣಾಙ್ಕ which;

    ಯದಿ (SDL_BITSPERPIXEL(surface->map.info.dst_fmt->format) < 8) {
        which = 0;
    } ಅನ್ಯಥಾ {
        which = SDL_BYTESPERPIXEL(surface->map.info.dst_fmt->format);
    }

    ವಿಕಲ್ಪ (surface->map.info.flags & ~SDL_COPY_RLE_MASK) {
    ಪಕ್ಷ 0:
        ಯದಿ (which < SDL_arraysize(one_blit)) {
            ಪ್ರತ್ಯಾಗಮ one_blit[which];
        }
        ಭಙ್ಗ;

    ಪಕ್ಷ SDL_COPY_COLORKEY:
        ಯದಿ (which < SDL_arraysize(one_blitkey)) {
            ಪ್ರತ್ಯಾಗಮ one_blitkey[which];
        }
        ಭಙ್ಗ;

    ಪಕ್ಷ SDL_COPY_COLORKEY | SDL_COPY_BLEND:  // this is not super-robust but handles a specific case we found sdl12-compat.
        ಯದಿ (surface->map.info.a == 255) {
            ಯದಿ (which < SDL_arraysize(one_blitkey)) {
                ಪ್ರತ್ಯಾಗಮ one_blitkey[which];
            }
        } ಅನ್ಯಥಾ {
            ಪ್ರತ್ಯಾಗಮ which >= 2 ? Blit1to_NAlpha_ಕೀಲಿ : (SDL_BlitFunc)ರಿಕ್ತ;
        }
        ಭಙ್ಗ;

    ಪಕ್ಷ SDL_COPY_BLEND:
    ಪಕ್ಷ SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
        /* Supporting 8bpp->8bpp alpha is doable but requires lots of
           tables which consume space and takes time to precompute,
           so is better left to the user */
        ಪ್ರತ್ಯಾಗಮ which >= 2 ? Blit1toNAlpha : (SDL_BlitFunc)ರಿಕ್ತ;

    ಪಕ್ಷ SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
        ಪ್ರತ್ಯಾಗಮ which >= 2 ? Blit1to_NAlpha_ಕೀಲಿ : (SDL_BlitFunc)ರಿಕ್ತ;
    }
    ಪ್ರತ್ಯಾಗಮ (SDL_BlitFunc)ರಿಕ್ತ;
}

#endif // SDL_HAVE_BLIT_1
