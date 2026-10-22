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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_HAVE_BLIT_1

#ಅನ್ತರ್ಭಾವ "SDL_surface_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_sysvideo.h"

// Functions to blit from 8-bit surfaces to other surfaces

ಸ್ಥಿರ ಶೂನ್ಯ Blit1to1(SDL_BlitInfo *info)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ USE_DUFFS_LOOP
    ಪೂರ್ಣಾಂಕ c;
#ಆದರೆ_ಅಂತ್ಯ
    ಪೂರ್ಣಾಂಕ ಅಗಲ, ಎತ್ತರ;
    Uint8 *src, *map, *dst;
    ಪೂರ್ಣಾಂಕ srcskip, dstskip;

    // Set up some basic variables
    ಅಗಲ = info->dst_w;
    ಎತ್ತರ = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = info->ಕೋಷ್ಟಕ;

    ಆಗ (ಎತ್ತರ--) {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ USE_DUFFS_LOOP
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
            {
              *dst = map[*src];
            }
            dst++;
            src++;
        , ಅಗಲ);
        /* *INDENT-ON* */ // clang-format on
#ಇಲ್ಲದಿದ್ದರೆ
        ಗಾಗಿ (c = ಅಗಲ; c; --c) {
            *dst = map[*src];
            dst++;
            src++;
        }
#ಆದರೆ_ಅಂತ್ಯ
        src += srcskip;
        dst += dstskip;
    }
}

// This is now endian dependent
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ USE_DUFFS_LOOP
#ಆದರೆ (SDL_BYTEORDER == SDL_LIL_ENDIAN)
#ವ್ಯಾಖ್ಯಾನಿಸು HI 1
#ವ್ಯಾಖ್ಯಾನಿಸು LO 0
#ಇಲ್ಲದಿದ್ದರೆ // ( SDL_BYTEORDER == SDL_BIG_ENDIAN )
#ವ್ಯಾಖ್ಯಾನಿಸು HI 0
#ವ್ಯಾಖ್ಯಾನಿಸು LO 1
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ
ಸ್ಥಿರ ಶೂನ್ಯ Blit1to2(SDL_BlitInfo *info)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ USE_DUFFS_LOOP
    ಪೂರ್ಣಾಂಕ c;
#ಆದರೆ_ಅಂತ್ಯ
    ಪೂರ್ಣಾಂಕ ಅಗಲ, ಎತ್ತರ;
    Uint8 *src, *dst;
    Uint16 *map;
    ಪೂರ್ಣಾಂಕ srcskip, dstskip;

    // Set up some basic variables
    ಅಗಲ = info->dst_w;
    ಎತ್ತರ = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = (Uint16 *)info->ಕೋಷ್ಟಕ;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ USE_DUFFS_LOOP
    ಆಗ (ಎತ್ತರ--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
        {
            *(Uint16 *)dst = map[*src++];
            dst += 2;
        },
        ಅಗಲ);
        /* *INDENT-ON* */ // clang-format on
        src += srcskip;
        dst += dstskip;
    }
#ಇಲ್ಲದಿದ್ದರೆ
    // Memory align at 4-byte boundary, if necessary
    ಆದರೆ ((ದೀರ್ಘ)dst & 0x03) {
        // Don't do anything if width is 0
        ಆದರೆ (ಅಗಲ == 0) {
            ಹಿಂತಿರುಗಿ;
        }
        --ಅಗಲ;

        ಆಗ (ಎತ್ತರ--) {
            // Perform copy alignment
            *(Uint16 *)dst = map[*src++];
            dst += 2;

            // Copy in 4 pixel chunks
            ಗಾಗಿ (c = ಅಗಲ / 4; c; --c) {
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
            }
            // Get any leftovers
            ಆಯ್ಕೆ (ಅಗಲ & 3) {
            ಸ್ಥಿತಿ 3:
                *(Uint16 *)dst = map[*src++];
                dst += 2;
                SDL_FALLTHROUGH;
            ಸ್ಥಿತಿ 2:
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ 1:
                *(Uint16 *)dst = map[*src++];
                dst += 2;
                ನಿಲ್ಲಿಸು;
            }
            src += srcskip;
            dst += dstskip;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆಗ (ಎತ್ತರ--) {
            // Copy in 4 pixel chunks
            ಗಾಗಿ (c = ಅಗಲ / 4; c; --c) {
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
            }
            // Get any leftovers
            ಆಯ್ಕೆ (ಅಗಲ & 3) {
            ಸ್ಥಿತಿ 3:
                *(Uint16 *)dst = map[*src++];
                dst += 2;
                SDL_FALLTHROUGH;
            ಸ್ಥಿತಿ 2:
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ 1:
                *(Uint16 *)dst = map[*src++];
                dst += 2;
                ನಿಲ್ಲಿಸು;
            }
            src += srcskip;
            dst += dstskip;
        }
    }
#ಆದರೆ_ಅಂತ್ಯ // USE_DUFFS_LOOP
}

ಸ್ಥಿರ ಶೂನ್ಯ Blit1to3(SDL_BlitInfo *info)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ USE_DUFFS_LOOP
    ಪೂರ್ಣಾಂಕ c;
#ಆದರೆ_ಅಂತ್ಯ
    ಪೂರ್ಣಾಂಕ o;
    ಪೂರ್ಣಾಂಕ ಅಗಲ, ಎತ್ತರ;
    Uint8 *src, *map, *dst;
    ಪೂರ್ಣಾಂಕ srcskip, dstskip;

    // Set up some basic variables
    ಅಗಲ = info->dst_w;
    ಎತ್ತರ = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = info->ಕೋಷ್ಟಕ;

    ಆಗ (ಎತ್ತರ--) {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ USE_DUFFS_LOOP
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
        , ಅಗಲ);
        /* *INDENT-ON* */ // clang-format on
#ಇಲ್ಲದಿದ್ದರೆ
        ಗಾಗಿ (c = ಅಗಲ; c; --c) {
            o = *src * 4;
            dst[0] = map[o++];
            dst[1] = map[o++];
            dst[2] = map[o++];
            src++;
            dst += 3;
        }
#ಆದರೆ_ಅಂತ್ಯ // USE_DUFFS_LOOP
        src += srcskip;
        dst += dstskip;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Blit1to4(SDL_BlitInfo *info)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ USE_DUFFS_LOOP
    ಪೂರ್ಣಾಂಕ c;
#ಆದರೆ_ಅಂತ್ಯ
    ಪೂರ್ಣಾಂಕ ಅಗಲ, ಎತ್ತರ;
    Uint8 *src;
    Uint32 *map, *dst;
    ಪೂರ್ಣಾಂಕ srcskip, dstskip;

    // Set up some basic variables
    ಅಗಲ = info->dst_w;
    ಎತ್ತರ = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = (Uint32 *)info->dst;
    dstskip = info->dst_skip / 4;
    map = (Uint32 *)info->ಕೋಷ್ಟಕ;

    ಆಗ (ಎತ್ತರ--) {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ USE_DUFFS_LOOP
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
            *dst++ = map[*src++];
        , ಅಗಲ);
        /* *INDENT-ON* */ // clang-format on
#ಇಲ್ಲದಿದ್ದರೆ
        ಗಾಗಿ (c = ಅಗಲ / 4; c; --c) {
            *dst++ = map[*src++];
            *dst++ = map[*src++];
            *dst++ = map[*src++];
            *dst++ = map[*src++];
        }
        ಆಯ್ಕೆ (ಅಗಲ & 3) {
        ಸ್ಥಿತಿ 3:
            *dst++ = map[*src++];
            SDL_FALLTHROUGH;
        ಸ್ಥಿತಿ 2:
            *dst++ = map[*src++];
            SDL_FALLTHROUGH;
        ಸ್ಥಿತಿ 1:
            *dst++ = map[*src++];
        }
#ಆದರೆ_ಅಂತ್ಯ // USE_DUFFS_LOOP
        src += srcskip;
        dst += dstskip;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Blit1to1_ಕೀಲಿ(SDL_BlitInfo *info)
{
    ಪೂರ್ಣಾಂಕ ಅಗಲ = info->dst_w;
    ಪೂರ್ಣಾಂಕ ಎತ್ತರ = info->dst_h;
    Uint8 *src = info->src;
    ಪೂರ್ಣಾಂಕ srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    ಪೂರ್ಣಾಂಕ dstskip = info->dst_skip;
    Uint8 *palmap = info->ಕೋಷ್ಟಕ;
    Uint32 ckey = info->colorkey;

    ಆದರೆ (palmap) {
        ಆಗ (ಎತ್ತರ--) {
            /* *INDENT-OFF* */ // clang-format off
            DUFFS_LOOP_TRIVIAL(
            {
                ಆದರೆ ( *src != ckey ) {
                  *dst = palmap[*src];
                }
                dst++;
                src++;
            },
            ಅಗಲ);
            /* *INDENT-ON* */ // clang-format on
            src += srcskip;
            dst += dstskip;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆಗ (ಎತ್ತರ--) {
            /* *INDENT-OFF* */ // clang-format off
            DUFFS_LOOP_TRIVIAL(
            {
                ಆದರೆ ( *src != ckey ) {
                  *dst = *src;
                }
                dst++;
                src++;
            },
            ಅಗಲ);
            /* *INDENT-ON* */ // clang-format on
            src += srcskip;
            dst += dstskip;
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Blit1to2_ಕೀಲಿ(SDL_BlitInfo *info)
{
    ಪೂರ್ಣಾಂಕ ಅಗಲ = info->dst_w;
    ಪೂರ್ಣಾಂಕ ಎತ್ತರ = info->dst_h;
    Uint8 *src = info->src;
    ಪೂರ್ಣಾಂಕ srcskip = info->src_skip;
    Uint16 *dstp = (Uint16 *)info->dst;
    ಪೂರ್ಣಾಂಕ dstskip = info->dst_skip;
    Uint16 *palmap = (Uint16 *)info->ಕೋಷ್ಟಕ;
    Uint32 ckey = info->colorkey;

    // Set up some basic variables
    dstskip /= 2;

    ಆಗ (ಎತ್ತರ--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
        {
            ಆದರೆ ( *src != ckey ) {
                *dstp=palmap[*src];
            }
            src++;
            dstp++;
        },
        ಅಗಲ);
        /* *INDENT-ON* */ // clang-format on
        src += srcskip;
        dstp += dstskip;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Blit1to3_ಕೀಲಿ(SDL_BlitInfo *info)
{
    ಪೂರ್ಣಾಂಕ ಅಗಲ = info->dst_w;
    ಪೂರ್ಣಾಂಕ ಎತ್ತರ = info->dst_h;
    Uint8 *src = info->src;
    ಪೂರ್ಣಾಂಕ srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    ಪೂರ್ಣಾಂಕ dstskip = info->dst_skip;
    Uint8 *palmap = info->ಕೋಷ್ಟಕ;
    Uint32 ckey = info->colorkey;
    ಪೂರ್ಣಾಂಕ o;

    ಆಗ (ಎತ್ತರ--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP(
        {
            ಆದರೆ ( *src != ckey ) {
                o = *src * 4;
                dst[0] = palmap[o++];
                dst[1] = palmap[o++];
                dst[2] = palmap[o++];
            }
            src++;
            dst += 3;
        },
        ಅಗಲ);
        /* *INDENT-ON* */ // clang-format on
        src += srcskip;
        dst += dstskip;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Blit1to4_ಕೀಲಿ(SDL_BlitInfo *info)
{
    ಪೂರ್ಣಾಂಕ ಅಗಲ = info->dst_w;
    ಪೂರ್ಣಾಂಕ ಎತ್ತರ = info->dst_h;
    Uint8 *src = info->src;
    ಪೂರ್ಣಾಂಕ srcskip = info->src_skip;
    Uint32 *dstp = (Uint32 *)info->dst;
    ಪೂರ್ಣಾಂಕ dstskip = info->dst_skip;
    Uint32 *palmap = (Uint32 *)info->ಕೋಷ್ಟಕ;
    Uint32 ckey = info->colorkey;

    // Set up some basic variables
    dstskip /= 4;

    ಆಗ (ಎತ್ತರ--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
        {
            ಆದರೆ ( *src != ckey ) {
                *dstp = palmap[*src];
            }
            src++;
            dstp++;
        },
        ಅಗಲ);
        /* *INDENT-ON* */ // clang-format on
        src += srcskip;
        dstp += dstskip;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Blit1toNAlpha(SDL_BlitInfo *info)
{
    ಪೂರ್ಣಾಂಕ ಅಗಲ = info->dst_w;
    ಪೂರ್ಣಾಂಕ ಎತ್ತರ = info->dst_h;
    Uint8 *src = info->src;
    ಪೂರ್ಣಾಂಕ srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    ಪೂರ್ಣಾಂಕ dstskip = info->dst_skip;
    ಸ್ಥಿರಾಂಕ SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    ಸ್ಥಿರಾಂಕ SDL_Color *srcpal = info->src_pal->colors;
    ಪೂರ್ಣಾಂಕ dstbpp;
    Uint32 pixelvalue;
    ಚಿಹ್ನೆರಹಿತ sR, sG, sB, sA;
    ಚಿಹ್ನೆರಹಿತ dR, dG, dB, dA;
    ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ A = info->a;

    // Set up some basic variables
    dstbpp = dstfmt->ಬೈಟುಗಳು_ಪ್ರತಿ_pixel;

    ಆಗ (ಎತ್ತರ--) {
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
        ಅಗಲ);
        /* *INDENT-ON* */ // clang-format on
        src += srcskip;
        dst += dstskip;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Blit1to_NAlpha_ಕೀಲಿ(SDL_BlitInfo *info)
{
    ಪೂರ್ಣಾಂಕ ಅಗಲ = info->dst_w;
    ಪೂರ್ಣಾಂಕ ಎತ್ತರ = info->dst_h;
    Uint8 *src = info->src;
    ಪೂರ್ಣಾಂಕ srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    ಪೂರ್ಣಾಂಕ dstskip = info->dst_skip;
    ಸ್ಥಿರಾಂಕ SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    ಸ್ಥಿರಾಂಕ SDL_Color *srcpal = info->src_pal->colors;
    Uint32 ckey = info->colorkey;
    ಪೂರ್ಣಾಂಕ dstbpp;
    Uint32 pixelvalue;
    ಚಿಹ್ನೆರಹಿತ sR, sG, sB, sA;
    ಚಿಹ್ನೆರಹಿತ dR, dG, dB, dA;
    ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ A = info->a;

    // Set up some basic variables
    dstbpp = dstfmt->ಬೈಟುಗಳು_ಪ್ರತಿ_pixel;

    ಆಗ (ಎತ್ತರ--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP(
        {
            ಆದರೆ ( *src != ckey ) {
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
        ಅಗಲ);
        /* *INDENT-ON* */ // clang-format on
        src += srcskip;
        dst += dstskip;
    }
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ SDL_BlitFunc one_blit[] = {
    (SDL_BlitFunc)ಖಾಲಿ, Blit1to1, Blit1to2, Blit1to3, Blit1to4
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ SDL_BlitFunc one_blitkey[] = {
    (SDL_BlitFunc)ಖಾಲಿ, Blit1to1_ಕೀಲಿ, Blit1to2_ಕೀಲಿ, Blit1to3_ಕೀಲಿ, Blit1to4_ಕೀಲಿ
};

SDL_BlitFunc SDL_CalculateBlit1(SDL_Surface *surface)
{
    ಪೂರ್ಣಾಂಕ which;

    ಆದರೆ (SDL_BITSPERPIXEL(surface->map.info.dst_fmt->format) < 8) {
        which = 0;
    } ಇಲ್ಲದಿದ್ದರೆ {
        which = SDL_BYTESPERPIXEL(surface->map.info.dst_fmt->format);
    }

    ಆಯ್ಕೆ (surface->map.info.flags & ~SDL_COPY_RLE_ಮುಖವಾಡ) {
    ಸ್ಥಿತಿ 0:
        ಆದರೆ (which < SDL_arraysize(one_blit)) {
            ಹಿಂತಿರುಗಿ one_blit[which];
        }
        ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ SDL_COPY_COLORKEY:
        ಆದರೆ (which < SDL_arraysize(one_blitkey)) {
            ಹಿಂತಿರುಗಿ one_blitkey[which];
        }
        ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ SDL_COPY_COLORKEY | SDL_COPY_BLEND:  // this is not super-robust but handles a specific case we found sdl12-compat.
        ಆದರೆ (surface->map.info.a == 255) {
            ಆದರೆ (which < SDL_arraysize(one_blitkey)) {
                ಹಿಂತಿರುಗಿ one_blitkey[which];
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಹಿಂತಿರುಗಿ which >= 2 ? Blit1to_NAlpha_ಕೀಲಿ : (SDL_BlitFunc)ಖಾಲಿ;
        }
        ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ SDL_COPY_BLEND:
    ಸ್ಥಿತಿ SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
        /* Supporting 8bpp->8bpp alpha is doable but requires lots of
           tables which consume space and takes time to precompute,
           so is better left to the user */
        ಹಿಂತಿರುಗಿ which >= 2 ? Blit1toNAlpha : (SDL_BlitFunc)ಖಾಲಿ;

    ಸ್ಥಿತಿ SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
        ಹಿಂತಿರುಗಿ which >= 2 ? Blit1to_NAlpha_ಕೀಲಿ : (SDL_BlitFunc)ಖಾಲಿ;
    }
    ಹಿಂತಿರುಗಿ (SDL_BlitFunc)ಖಾಲಿ;
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_HAVE_BLIT_1
