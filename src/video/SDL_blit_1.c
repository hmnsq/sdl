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

#ifdef SDL_HAVE_BLIT_1

#அந்தர்பாவ "SDL_surface_c.h"
#அந்தர்பாவ "SDL_sysvideo.h"

// Functions to blit from 8-bit surfaces to other surfaces

நிலையான வெறுமை Blit1to1(SDL_BlitInfo *info)
{
#ifndef USE_DUFFS_LOOP
    முழு c;
#endif
    முழு width, height;
    Uint8 *src, *map, *dst;
    முழு srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = info->table;

    போது (height--) {
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
#இல்லையெனில்
        க்கு (c = width; c; --c) {
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
#எனில் (SDL_BYTEORDER == SDL_LIL_ENDIAN)
#define HI 1
#define LO 0
#இல்லையெனில் // ( SDL_BYTEORDER == SDL_BIG_ENDIAN )
#define HI 0
#define LO 1
#endif
#endif
நிலையான வெறுமை Blit1to2(SDL_BlitInfo *info)
{
#ifndef USE_DUFFS_LOOP
    முழு c;
#endif
    முழு width, height;
    Uint8 *src, *dst;
    Uint16 *map;
    முழு srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = (Uint16 *)info->table;

#ifdef USE_DUFFS_LOOP
    போது (height--) {
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
#இல்லையெனில்
    // Memory align at 4-byte boundary, if necessary
    எனில் ((long)dst & 0x03) {
        // Don't do anything if width is 0
        எனில் (width == 0) {
            திரும்பு;
        }
        --width;

        போது (height--) {
            // Perform copy alignment
            *(Uint16 *)dst = map[*src++];
            dst += 2;

            // Copy in 4 pixel chunks
            க்கு (c = width / 4; c; --c) {
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
            }
            // Get any leftovers
            தேர்வு (width & 3) {
            நிலை 3:
                *(Uint16 *)dst = map[*src++];
                dst += 2;
                SDL_FALLTHROUGH;
            நிலை 2:
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
                நிறுத்து;
            நிலை 1:
                *(Uint16 *)dst = map[*src++];
                dst += 2;
                நிறுத்து;
            }
            src += srcskip;
            dst += dstskip;
        }
    } இல்லையெனில் {
        போது (height--) {
            // Copy in 4 pixel chunks
            க்கு (c = width / 4; c; --c) {
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
            }
            // Get any leftovers
            தேர்வு (width & 3) {
            நிலை 3:
                *(Uint16 *)dst = map[*src++];
                dst += 2;
                SDL_FALLTHROUGH;
            நிலை 2:
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
                நிறுத்து;
            நிலை 1:
                *(Uint16 *)dst = map[*src++];
                dst += 2;
                நிறுத்து;
            }
            src += srcskip;
            dst += dstskip;
        }
    }
#endif // USE_DUFFS_LOOP
}

நிலையான வெறுமை Blit1to3(SDL_BlitInfo *info)
{
#ifndef USE_DUFFS_LOOP
    முழு c;
#endif
    முழு o;
    முழு width, height;
    Uint8 *src, *map, *dst;
    முழு srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = info->table;

    போது (height--) {
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
#இல்லையெனில்
        க்கு (c = width; c; --c) {
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

நிலையான வெறுமை Blit1to4(SDL_BlitInfo *info)
{
#ifndef USE_DUFFS_LOOP
    முழு c;
#endif
    முழு width, height;
    Uint8 *src;
    Uint32 *map, *dst;
    முழு srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = (Uint32 *)info->dst;
    dstskip = info->dst_skip / 4;
    map = (Uint32 *)info->table;

    போது (height--) {
#ifdef USE_DUFFS_LOOP
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
            *dst++ = map[*src++];
        , width);
        /* *INDENT-ON* */ // clang-format on
#இல்லையெனில்
        க்கு (c = width / 4; c; --c) {
            *dst++ = map[*src++];
            *dst++ = map[*src++];
            *dst++ = map[*src++];
            *dst++ = map[*src++];
        }
        தேர்வு (width & 3) {
        நிலை 3:
            *dst++ = map[*src++];
            SDL_FALLTHROUGH;
        நிலை 2:
            *dst++ = map[*src++];
            SDL_FALLTHROUGH;
        நிலை 1:
            *dst++ = map[*src++];
        }
#endif // USE_DUFFS_LOOP
        src += srcskip;
        dst += dstskip;
    }
}

நிலையான வெறுமை Blit1to1_சாவி(SDL_BlitInfo *info)
{
    முழு width = info->dst_w;
    முழு height = info->dst_h;
    Uint8 *src = info->src;
    முழு srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    முழு dstskip = info->dst_skip;
    Uint8 *palmap = info->table;
    Uint32 ckey = info->colorkey;

    எனில் (palmap) {
        போது (height--) {
            /* *INDENT-OFF* */ // clang-format off
            DUFFS_LOOP_TRIVIAL(
            {
                எனில் ( *src != ckey ) {
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
    } இல்லையெனில் {
        போது (height--) {
            /* *INDENT-OFF* */ // clang-format off
            DUFFS_LOOP_TRIVIAL(
            {
                எனில் ( *src != ckey ) {
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

நிலையான வெறுமை Blit1to2_சாவி(SDL_BlitInfo *info)
{
    முழு width = info->dst_w;
    முழு height = info->dst_h;
    Uint8 *src = info->src;
    முழு srcskip = info->src_skip;
    Uint16 *dstp = (Uint16 *)info->dst;
    முழு dstskip = info->dst_skip;
    Uint16 *palmap = (Uint16 *)info->table;
    Uint32 ckey = info->colorkey;

    // Set up some basic variables
    dstskip /= 2;

    போது (height--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
        {
            எனில் ( *src != ckey ) {
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

நிலையான வெறுமை Blit1to3_சாவி(SDL_BlitInfo *info)
{
    முழு width = info->dst_w;
    முழு height = info->dst_h;
    Uint8 *src = info->src;
    முழு srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    முழு dstskip = info->dst_skip;
    Uint8 *palmap = info->table;
    Uint32 ckey = info->colorkey;
    முழு o;

    போது (height--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP(
        {
            எனில் ( *src != ckey ) {
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

நிலையான வெறுமை Blit1to4_சாவி(SDL_BlitInfo *info)
{
    முழு width = info->dst_w;
    முழு height = info->dst_h;
    Uint8 *src = info->src;
    முழு srcskip = info->src_skip;
    Uint32 *dstp = (Uint32 *)info->dst;
    முழு dstskip = info->dst_skip;
    Uint32 *palmap = (Uint32 *)info->table;
    Uint32 ckey = info->colorkey;

    // Set up some basic variables
    dstskip /= 4;

    போது (height--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
        {
            எனில் ( *src != ckey ) {
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

நிலையான வெறுமை Blit1toNAlpha(SDL_BlitInfo *info)
{
    முழு width = info->dst_w;
    முழு height = info->dst_h;
    Uint8 *src = info->src;
    முழு srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    முழு dstskip = info->dst_skip;
    மாறிலி SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    மாறிலி SDL_Color *srcpal = info->src_pal->colors;
    முழு dstbpp;
    Uint32 pixelvalue;
    unsigned sR, sG, sB, sA;
    unsigned dR, dG, dB, dA;
    மாறிலி unsigned A = info->a;

    // Set up some basic variables
    dstbpp = dstfmt->bytes_per_pixel;

    போது (height--) {
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

நிலையான வெறுமை Blit1to_NAlpha_சாவி(SDL_BlitInfo *info)
{
    முழு width = info->dst_w;
    முழு height = info->dst_h;
    Uint8 *src = info->src;
    முழு srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    முழு dstskip = info->dst_skip;
    மாறிலி SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    மாறிலி SDL_Color *srcpal = info->src_pal->colors;
    Uint32 ckey = info->colorkey;
    முழு dstbpp;
    Uint32 pixelvalue;
    unsigned sR, sG, sB, sA;
    unsigned dR, dG, dB, dA;
    மாறிலி unsigned A = info->a;

    // Set up some basic variables
    dstbpp = dstfmt->bytes_per_pixel;

    போது (height--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP(
        {
            எனில் ( *src != ckey ) {
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

நிலையான மாறிலி SDL_BlitFunc one_blit[] = {
    (SDL_BlitFunc)வெற்று, Blit1to1, Blit1to2, Blit1to3, Blit1to4
};

நிலையான மாறிலி SDL_BlitFunc one_blitkey[] = {
    (SDL_BlitFunc)வெற்று, Blit1to1_சாவி, Blit1to2_சாவி, Blit1to3_சாவி, Blit1to4_சாவி
};

SDL_BlitFunc SDL_CalculateBlit1(SDL_Surface *surface)
{
    முழு which;

    எனில் (SDL_BITSPERPIXEL(surface->map.info.dst_fmt->format) < 8) {
        which = 0;
    } இல்லையெனில் {
        which = SDL_BYTESPERPIXEL(surface->map.info.dst_fmt->format);
    }

    தேர்வு (surface->map.info.flags & ~SDL_COPY_RLE_MASK) {
    நிலை 0:
        எனில் (which < SDL_arraysize(one_blit)) {
            திரும்பு one_blit[which];
        }
        நிறுத்து;

    நிலை SDL_COPY_COLORKEY:
        எனில் (which < SDL_arraysize(one_blitkey)) {
            திரும்பு one_blitkey[which];
        }
        நிறுத்து;

    நிலை SDL_COPY_COLORKEY | SDL_COPY_BLEND:  // this is not super-robust but handles a specific case we found sdl12-compat.
        எனில் (surface->map.info.a == 255) {
            எனில் (which < SDL_arraysize(one_blitkey)) {
                திரும்பு one_blitkey[which];
            }
        } இல்லையெனில் {
            திரும்பு which >= 2 ? Blit1to_NAlpha_சாவி : (SDL_BlitFunc)வெற்று;
        }
        நிறுத்து;

    நிலை SDL_COPY_BLEND:
    நிலை SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
        /* Supporting 8bpp->8bpp alpha is doable but requires lots of
           tables which consume space and takes time to precompute,
           so is better left to the user */
        திரும்பு which >= 2 ? Blit1toNAlpha : (SDL_BlitFunc)வெற்று;

    நிலை SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
        திரும்பு which >= 2 ? Blit1to_NAlpha_சாவி : (SDL_BlitFunc)வெற்று;
    }
    திரும்பு (SDL_BlitFunc)வெற்று;
}

#endif // SDL_HAVE_BLIT_1
