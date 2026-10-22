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
#അന്തര്ഭാവ "SDL_internal.h"

#ifdef SDL_HAVE_BLIT_1

#അന്തര്ഭാവ "SDL_surface_c.h"
#അന്തര്ഭാവ "SDL_sysvideo.h"

// Functions to blit from 8-bit surfaces to other surfaces

സ്ഥിതം ശൂന്യം Blit1to1(SDL_BlitInfo *info)
{
#ifndef USE_DUFFS_LOOP
    പൂർണ്ണസംഖ്യ c;
#endif
    പൂർണ്ണസംഖ്യ width, height;
    Uint8 *src, *map, *dst;
    പൂർണ്ണസംഖ്യ srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = info->table;

    ആകുമ്പോൾ (height--) {
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
#അല്ലെങ്കിൽ
        വേണ്ടി (c = width; c; --c) {
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
#എങ്കിൽ (SDL_BYTEORDER == SDL_LIL_ENDIAN)
#define HI 1
#define LO 0
#അല്ലെങ്കിൽ // ( SDL_BYTEORDER == SDL_BIG_ENDIAN )
#define HI 0
#define LO 1
#endif
#endif
സ്ഥിതം ശൂന്യം Blit1to2(SDL_BlitInfo *info)
{
#ifndef USE_DUFFS_LOOP
    പൂർണ്ണസംഖ്യ c;
#endif
    പൂർണ്ണസംഖ്യ width, height;
    Uint8 *src, *dst;
    Uint16 *map;
    പൂർണ്ണസംഖ്യ srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = (Uint16 *)info->table;

#ifdef USE_DUFFS_LOOP
    ആകുമ്പോൾ (height--) {
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
#അല്ലെങ്കിൽ
    // Memory align at 4-byte boundary, if necessary
    എങ്കിൽ ((long)dst & 0x03) {
        // Don't do anything if width is 0
        എങ്കിൽ (width == 0) {
            തിരികെ;
        }
        --width;

        ആകുമ്പോൾ (height--) {
            // Perform copy alignment
            *(Uint16 *)dst = map[*src++];
            dst += 2;

            // Copy in 4 pixel chunks
            വേണ്ടി (c = width / 4; c; --c) {
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
            }
            // Get any leftovers
            തിരഞ്ഞെടുപ്പ് (width & 3) {
            അവസ്ഥ 3:
                *(Uint16 *)dst = map[*src++];
                dst += 2;
                SDL_FALLTHROUGH;
            അവസ്ഥ 2:
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
                നിർത്തുക;
            അവസ്ഥ 1:
                *(Uint16 *)dst = map[*src++];
                dst += 2;
                നിർത്തുക;
            }
            src += srcskip;
            dst += dstskip;
        }
    } അല്ലെങ്കിൽ {
        ആകുമ്പോൾ (height--) {
            // Copy in 4 pixel chunks
            വേണ്ടി (c = width / 4; c; --c) {
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
            }
            // Get any leftovers
            തിരഞ്ഞെടുപ്പ് (width & 3) {
            അവസ്ഥ 3:
                *(Uint16 *)dst = map[*src++];
                dst += 2;
                SDL_FALLTHROUGH;
            അവസ്ഥ 2:
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
                നിർത്തുക;
            അവസ്ഥ 1:
                *(Uint16 *)dst = map[*src++];
                dst += 2;
                നിർത്തുക;
            }
            src += srcskip;
            dst += dstskip;
        }
    }
#endif // USE_DUFFS_LOOP
}

സ്ഥിതം ശൂന്യം Blit1to3(SDL_BlitInfo *info)
{
#ifndef USE_DUFFS_LOOP
    പൂർണ്ണസംഖ്യ c;
#endif
    പൂർണ്ണസംഖ്യ o;
    പൂർണ്ണസംഖ്യ width, height;
    Uint8 *src, *map, *dst;
    പൂർണ്ണസംഖ്യ srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = info->table;

    ആകുമ്പോൾ (height--) {
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
#അല്ലെങ്കിൽ
        വേണ്ടി (c = width; c; --c) {
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

സ്ഥിതം ശൂന്യം Blit1to4(SDL_BlitInfo *info)
{
#ifndef USE_DUFFS_LOOP
    പൂർണ്ണസംഖ്യ c;
#endif
    പൂർണ്ണസംഖ്യ width, height;
    Uint8 *src;
    Uint32 *map, *dst;
    പൂർണ്ണസംഖ്യ srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = (Uint32 *)info->dst;
    dstskip = info->dst_skip / 4;
    map = (Uint32 *)info->table;

    ആകുമ്പോൾ (height--) {
#ifdef USE_DUFFS_LOOP
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
            *dst++ = map[*src++];
        , width);
        /* *INDENT-ON* */ // clang-format on
#അല്ലെങ്കിൽ
        വേണ്ടി (c = width / 4; c; --c) {
            *dst++ = map[*src++];
            *dst++ = map[*src++];
            *dst++ = map[*src++];
            *dst++ = map[*src++];
        }
        തിരഞ്ഞെടുപ്പ് (width & 3) {
        അവസ്ഥ 3:
            *dst++ = map[*src++];
            SDL_FALLTHROUGH;
        അവസ്ഥ 2:
            *dst++ = map[*src++];
            SDL_FALLTHROUGH;
        അവസ്ഥ 1:
            *dst++ = map[*src++];
        }
#endif // USE_DUFFS_LOOP
        src += srcskip;
        dst += dstskip;
    }
}

സ്ഥിതം ശൂന്യം Blit1to1_താക്കോൽ(SDL_BlitInfo *info)
{
    പൂർണ്ണസംഖ്യ width = info->dst_w;
    പൂർണ്ണസംഖ്യ height = info->dst_h;
    Uint8 *src = info->src;
    പൂർണ്ണസംഖ്യ srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    പൂർണ്ണസംഖ്യ dstskip = info->dst_skip;
    Uint8 *palmap = info->table;
    Uint32 ckey = info->colorkey;

    എങ്കിൽ (palmap) {
        ആകുമ്പോൾ (height--) {
            /* *INDENT-OFF* */ // clang-format off
            DUFFS_LOOP_TRIVIAL(
            {
                എങ്കിൽ ( *src != ckey ) {
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
    } അല്ലെങ്കിൽ {
        ആകുമ്പോൾ (height--) {
            /* *INDENT-OFF* */ // clang-format off
            DUFFS_LOOP_TRIVIAL(
            {
                എങ്കിൽ ( *src != ckey ) {
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

സ്ഥിതം ശൂന്യം Blit1to2_താക്കോൽ(SDL_BlitInfo *info)
{
    പൂർണ്ണസംഖ്യ width = info->dst_w;
    പൂർണ്ണസംഖ്യ height = info->dst_h;
    Uint8 *src = info->src;
    പൂർണ്ണസംഖ്യ srcskip = info->src_skip;
    Uint16 *dstp = (Uint16 *)info->dst;
    പൂർണ്ണസംഖ്യ dstskip = info->dst_skip;
    Uint16 *palmap = (Uint16 *)info->table;
    Uint32 ckey = info->colorkey;

    // Set up some basic variables
    dstskip /= 2;

    ആകുമ്പോൾ (height--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
        {
            എങ്കിൽ ( *src != ckey ) {
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

സ്ഥിതം ശൂന്യം Blit1to3_താക്കോൽ(SDL_BlitInfo *info)
{
    പൂർണ്ണസംഖ്യ width = info->dst_w;
    പൂർണ്ണസംഖ്യ height = info->dst_h;
    Uint8 *src = info->src;
    പൂർണ്ണസംഖ്യ srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    പൂർണ്ണസംഖ്യ dstskip = info->dst_skip;
    Uint8 *palmap = info->table;
    Uint32 ckey = info->colorkey;
    പൂർണ്ണസംഖ്യ o;

    ആകുമ്പോൾ (height--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP(
        {
            എങ്കിൽ ( *src != ckey ) {
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

സ്ഥിതം ശൂന്യം Blit1to4_താക്കോൽ(SDL_BlitInfo *info)
{
    പൂർണ്ണസംഖ്യ width = info->dst_w;
    പൂർണ്ണസംഖ്യ height = info->dst_h;
    Uint8 *src = info->src;
    പൂർണ്ണസംഖ്യ srcskip = info->src_skip;
    Uint32 *dstp = (Uint32 *)info->dst;
    പൂർണ്ണസംഖ്യ dstskip = info->dst_skip;
    Uint32 *palmap = (Uint32 *)info->table;
    Uint32 ckey = info->colorkey;

    // Set up some basic variables
    dstskip /= 4;

    ആകുമ്പോൾ (height--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
        {
            എങ്കിൽ ( *src != ckey ) {
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

സ്ഥിതം ശൂന്യം Blit1toNAlpha(SDL_BlitInfo *info)
{
    പൂർണ്ണസംഖ്യ width = info->dst_w;
    പൂർണ്ണസംഖ്യ height = info->dst_h;
    Uint8 *src = info->src;
    പൂർണ്ണസംഖ്യ srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    പൂർണ്ണസംഖ്യ dstskip = info->dst_skip;
    സ്ഥിരം SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    സ്ഥിരം SDL_Color *srcpal = info->src_pal->colors;
    പൂർണ്ണസംഖ്യ dstbpp;
    Uint32 pixelvalue;
    unsigned sR, sG, sB, sA;
    unsigned dR, dG, dB, dA;
    സ്ഥിരം unsigned A = info->a;

    // Set up some basic variables
    dstbpp = dstfmt->bytes_per_pixel;

    ആകുമ്പോൾ (height--) {
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

സ്ഥിതം ശൂന്യം Blit1to_NAlpha_താക്കോൽ(SDL_BlitInfo *info)
{
    പൂർണ്ണസംഖ്യ width = info->dst_w;
    പൂർണ്ണസംഖ്യ height = info->dst_h;
    Uint8 *src = info->src;
    പൂർണ്ണസംഖ്യ srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    പൂർണ്ണസംഖ്യ dstskip = info->dst_skip;
    സ്ഥിരം SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    സ്ഥിരം SDL_Color *srcpal = info->src_pal->colors;
    Uint32 ckey = info->colorkey;
    പൂർണ്ണസംഖ്യ dstbpp;
    Uint32 pixelvalue;
    unsigned sR, sG, sB, sA;
    unsigned dR, dG, dB, dA;
    സ്ഥിരം unsigned A = info->a;

    // Set up some basic variables
    dstbpp = dstfmt->bytes_per_pixel;

    ആകുമ്പോൾ (height--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP(
        {
            എങ്കിൽ ( *src != ckey ) {
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

സ്ഥിതം സ്ഥിരം SDL_BlitFunc one_blit[] = {
    (SDL_BlitFunc)ശൂന്യ, Blit1to1, Blit1to2, Blit1to3, Blit1to4
};

സ്ഥിതം സ്ഥിരം SDL_BlitFunc one_blitkey[] = {
    (SDL_BlitFunc)ശൂന്യ, Blit1to1_താക്കോൽ, Blit1to2_താക്കോൽ, Blit1to3_താക്കോൽ, Blit1to4_താക്കോൽ
};

SDL_BlitFunc SDL_CalculateBlit1(SDL_Surface *surface)
{
    പൂർണ്ണസംഖ്യ which;

    എങ്കിൽ (SDL_BITSPERPIXEL(surface->map.info.dst_fmt->format) < 8) {
        which = 0;
    } അല്ലെങ്കിൽ {
        which = SDL_BYTESPERPIXEL(surface->map.info.dst_fmt->format);
    }

    തിരഞ്ഞെടുപ്പ് (surface->map.info.flags & ~SDL_COPY_RLE_MASK) {
    അവസ്ഥ 0:
        എങ്കിൽ (which < SDL_arraysize(one_blit)) {
            തിരികെ one_blit[which];
        }
        നിർത്തുക;

    അവസ്ഥ SDL_COPY_COLORKEY:
        എങ്കിൽ (which < SDL_arraysize(one_blitkey)) {
            തിരികെ one_blitkey[which];
        }
        നിർത്തുക;

    അവസ്ഥ SDL_COPY_COLORKEY | SDL_COPY_BLEND:  // this is not super-robust but handles a specific case we found sdl12-compat.
        എങ്കിൽ (surface->map.info.a == 255) {
            എങ്കിൽ (which < SDL_arraysize(one_blitkey)) {
                തിരികെ one_blitkey[which];
            }
        } അല്ലെങ്കിൽ {
            തിരികെ which >= 2 ? Blit1to_NAlpha_താക്കോൽ : (SDL_BlitFunc)ശൂന്യ;
        }
        നിർത്തുക;

    അവസ്ഥ SDL_COPY_BLEND:
    അവസ്ഥ SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
        /* Supporting 8bpp->8bpp alpha is doable but requires lots of
           tables which consume space and takes time to precompute,
           so is better left to the user */
        തിരികെ which >= 2 ? Blit1toNAlpha : (SDL_BlitFunc)ശൂന്യ;

    അവസ്ഥ SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
        തിരികെ which >= 2 ? Blit1to_NAlpha_താക്കോൽ : (SDL_BlitFunc)ശൂന്യ;
    }
    തിരികെ (SDL_BlitFunc)ശൂന്യ;
}

#endif // SDL_HAVE_BLIT_1
