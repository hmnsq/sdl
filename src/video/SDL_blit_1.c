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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_HAVE_BLIT_1

#అన్తర్భావ "SDL_surface_c.h"
#అన్తర్భావ "SDL_sysvideo.h"

// Functions to blit from 8-bit surfaces to other surfaces

స్థిర శూన్య Blit1to1(SDL_BlitInfo *info)
{
#నిర్వచితం_కాకపోతే USE_DUFFS_LOOP
    పూర్ణాంకం c;
#అయితే_ముగింపు
    పూర్ణాంకం వెడల్పు, ఎత్తు;
    Uint8 *src, *map, *dst;
    పూర్ణాంకం srcskip, dstskip;

    // Set up some basic variables
    వెడల్పు = info->dst_w;
    ఎత్తు = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = info->పట్టిక;

    అయితే (ఎత్తు--) {
#నిర్వచితమైతే USE_DUFFS_LOOP
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
            {
              *dst = map[*src];
            }
            dst++;
            src++;
        , వెడల్పు);
        /* *INDENT-ON* */ // clang-format on
#లేకపోతే
        కొరకు (c = వెడల్పు; c; --c) {
            *dst = map[*src];
            dst++;
            src++;
        }
#అయితే_ముగింపు
        src += srcskip;
        dst += dstskip;
    }
}

// This is now endian dependent
#నిర్వచితం_కాకపోతే USE_DUFFS_LOOP
#ఒకవేళ (SDL_BYTEORDER == SDL_LIL_ENDIAN)
#నిర్వచించు HI 1
#నిర్వచించు LO 0
#లేకపోతే // ( SDL_BYTEORDER == SDL_BIG_ENDIAN )
#నిర్వచించు HI 0
#నిర్వచించు LO 1
#అయితే_ముగింపు
#అయితే_ముగింపు
స్థిర శూన్య Blit1to2(SDL_BlitInfo *info)
{
#నిర్వచితం_కాకపోతే USE_DUFFS_LOOP
    పూర్ణాంకం c;
#అయితే_ముగింపు
    పూర్ణాంకం వెడల్పు, ఎత్తు;
    Uint8 *src, *dst;
    Uint16 *map;
    పూర్ణాంకం srcskip, dstskip;

    // Set up some basic variables
    వెడల్పు = info->dst_w;
    ఎత్తు = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = (Uint16 *)info->పట్టిక;

#నిర్వచితమైతే USE_DUFFS_LOOP
    అయితే (ఎత్తు--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
        {
            *(Uint16 *)dst = map[*src++];
            dst += 2;
        },
        వెడల్పు);
        /* *INDENT-ON* */ // clang-format on
        src += srcskip;
        dst += dstskip;
    }
#లేకపోతే
    // Memory align at 4-byte boundary, if necessary
    ఒకవేళ ((దీర్ఘ)dst & 0x03) {
        // Don't do anything if width is 0
        ఒకవేళ (వెడల్పు == 0) {
            తిరిగి;
        }
        --వెడల్పు;

        అయితే (ఎత్తు--) {
            // Perform copy alignment
            *(Uint16 *)dst = map[*src++];
            dst += 2;

            // Copy in 4 pixel chunks
            కొరకు (c = వెడల్పు / 4; c; --c) {
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
            }
            // Get any leftovers
            ఎంపిక (వెడల్పు & 3) {
            స్థితి 3:
                *(Uint16 *)dst = map[*src++];
                dst += 2;
                SDL_FALLTHROUGH;
            స్థితి 2:
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
                ఆపు;
            స్థితి 1:
                *(Uint16 *)dst = map[*src++];
                dst += 2;
                ఆపు;
            }
            src += srcskip;
            dst += dstskip;
        }
    } లేకపోతే {
        అయితే (ఎత్తు--) {
            // Copy in 4 pixel chunks
            కొరకు (c = వెడల్పు / 4; c; --c) {
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
            }
            // Get any leftovers
            ఎంపిక (వెడల్పు & 3) {
            స్థితి 3:
                *(Uint16 *)dst = map[*src++];
                dst += 2;
                SDL_FALLTHROUGH;
            స్థితి 2:
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
                ఆపు;
            స్థితి 1:
                *(Uint16 *)dst = map[*src++];
                dst += 2;
                ఆపు;
            }
            src += srcskip;
            dst += dstskip;
        }
    }
#అయితే_ముగింపు // USE_DUFFS_LOOP
}

స్థిర శూన్య Blit1to3(SDL_BlitInfo *info)
{
#నిర్వచితం_కాకపోతే USE_DUFFS_LOOP
    పూర్ణాంకం c;
#అయితే_ముగింపు
    పూర్ణాంకం o;
    పూర్ణాంకం వెడల్పు, ఎత్తు;
    Uint8 *src, *map, *dst;
    పూర్ణాంకం srcskip, dstskip;

    // Set up some basic variables
    వెడల్పు = info->dst_w;
    ఎత్తు = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = info->పట్టిక;

    అయితే (ఎత్తు--) {
#నిర్వచితమైతే USE_DUFFS_LOOP
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
        , వెడల్పు);
        /* *INDENT-ON* */ // clang-format on
#లేకపోతే
        కొరకు (c = వెడల్పు; c; --c) {
            o = *src * 4;
            dst[0] = map[o++];
            dst[1] = map[o++];
            dst[2] = map[o++];
            src++;
            dst += 3;
        }
#అయితే_ముగింపు // USE_DUFFS_LOOP
        src += srcskip;
        dst += dstskip;
    }
}

స్థిర శూన్య Blit1to4(SDL_BlitInfo *info)
{
#నిర్వచితం_కాకపోతే USE_DUFFS_LOOP
    పూర్ణాంకం c;
#అయితే_ముగింపు
    పూర్ణాంకం వెడల్పు, ఎత్తు;
    Uint8 *src;
    Uint32 *map, *dst;
    పూర్ణాంకం srcskip, dstskip;

    // Set up some basic variables
    వెడల్పు = info->dst_w;
    ఎత్తు = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = (Uint32 *)info->dst;
    dstskip = info->dst_skip / 4;
    map = (Uint32 *)info->పట్టిక;

    అయితే (ఎత్తు--) {
#నిర్వచితమైతే USE_DUFFS_LOOP
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
            *dst++ = map[*src++];
        , వెడల్పు);
        /* *INDENT-ON* */ // clang-format on
#లేకపోతే
        కొరకు (c = వెడల్పు / 4; c; --c) {
            *dst++ = map[*src++];
            *dst++ = map[*src++];
            *dst++ = map[*src++];
            *dst++ = map[*src++];
        }
        ఎంపిక (వెడల్పు & 3) {
        స్థితి 3:
            *dst++ = map[*src++];
            SDL_FALLTHROUGH;
        స్థితి 2:
            *dst++ = map[*src++];
            SDL_FALLTHROUGH;
        స్థితి 1:
            *dst++ = map[*src++];
        }
#అయితే_ముగింపు // USE_DUFFS_LOOP
        src += srcskip;
        dst += dstskip;
    }
}

స్థిర శూన్య Blit1to1_కీలకం(SDL_BlitInfo *info)
{
    పూర్ణాంకం వెడల్పు = info->dst_w;
    పూర్ణాంకం ఎత్తు = info->dst_h;
    Uint8 *src = info->src;
    పూర్ణాంకం srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    పూర్ణాంకం dstskip = info->dst_skip;
    Uint8 *palmap = info->పట్టిక;
    Uint32 ckey = info->colorkey;

    ఒకవేళ (palmap) {
        అయితే (ఎత్తు--) {
            /* *INDENT-OFF* */ // clang-format off
            DUFFS_LOOP_TRIVIAL(
            {
                ఒకవేళ ( *src != ckey ) {
                  *dst = palmap[*src];
                }
                dst++;
                src++;
            },
            వెడల్పు);
            /* *INDENT-ON* */ // clang-format on
            src += srcskip;
            dst += dstskip;
        }
    } లేకపోతే {
        అయితే (ఎత్తు--) {
            /* *INDENT-OFF* */ // clang-format off
            DUFFS_LOOP_TRIVIAL(
            {
                ఒకవేళ ( *src != ckey ) {
                  *dst = *src;
                }
                dst++;
                src++;
            },
            వెడల్పు);
            /* *INDENT-ON* */ // clang-format on
            src += srcskip;
            dst += dstskip;
        }
    }
}

స్థిర శూన్య Blit1to2_కీలకం(SDL_BlitInfo *info)
{
    పూర్ణాంకం వెడల్పు = info->dst_w;
    పూర్ణాంకం ఎత్తు = info->dst_h;
    Uint8 *src = info->src;
    పూర్ణాంకం srcskip = info->src_skip;
    Uint16 *dstp = (Uint16 *)info->dst;
    పూర్ణాంకం dstskip = info->dst_skip;
    Uint16 *palmap = (Uint16 *)info->పట్టిక;
    Uint32 ckey = info->colorkey;

    // Set up some basic variables
    dstskip /= 2;

    అయితే (ఎత్తు--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
        {
            ఒకవేళ ( *src != ckey ) {
                *dstp=palmap[*src];
            }
            src++;
            dstp++;
        },
        వెడల్పు);
        /* *INDENT-ON* */ // clang-format on
        src += srcskip;
        dstp += dstskip;
    }
}

స్థిర శూన్య Blit1to3_కీలకం(SDL_BlitInfo *info)
{
    పూర్ణాంకం వెడల్పు = info->dst_w;
    పూర్ణాంకం ఎత్తు = info->dst_h;
    Uint8 *src = info->src;
    పూర్ణాంకం srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    పూర్ణాంకం dstskip = info->dst_skip;
    Uint8 *palmap = info->పట్టిక;
    Uint32 ckey = info->colorkey;
    పూర్ణాంకం o;

    అయితే (ఎత్తు--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP(
        {
            ఒకవేళ ( *src != ckey ) {
                o = *src * 4;
                dst[0] = palmap[o++];
                dst[1] = palmap[o++];
                dst[2] = palmap[o++];
            }
            src++;
            dst += 3;
        },
        వెడల్పు);
        /* *INDENT-ON* */ // clang-format on
        src += srcskip;
        dst += dstskip;
    }
}

స్థిర శూన్య Blit1to4_కీలకం(SDL_BlitInfo *info)
{
    పూర్ణాంకం వెడల్పు = info->dst_w;
    పూర్ణాంకం ఎత్తు = info->dst_h;
    Uint8 *src = info->src;
    పూర్ణాంకం srcskip = info->src_skip;
    Uint32 *dstp = (Uint32 *)info->dst;
    పూర్ణాంకం dstskip = info->dst_skip;
    Uint32 *palmap = (Uint32 *)info->పట్టిక;
    Uint32 ckey = info->colorkey;

    // Set up some basic variables
    dstskip /= 4;

    అయితే (ఎత్తు--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
        {
            ఒకవేళ ( *src != ckey ) {
                *dstp = palmap[*src];
            }
            src++;
            dstp++;
        },
        వెడల్పు);
        /* *INDENT-ON* */ // clang-format on
        src += srcskip;
        dstp += dstskip;
    }
}

స్థిర శూన్య Blit1toNAlpha(SDL_BlitInfo *info)
{
    పూర్ణాంకం వెడల్పు = info->dst_w;
    పూర్ణాంకం ఎత్తు = info->dst_h;
    Uint8 *src = info->src;
    పూర్ణాంకం srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    పూర్ణాంకం dstskip = info->dst_skip;
    స్థిరరాశి SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    స్థిరరాశి SDL_Color *srcpal = info->src_pal->colors;
    పూర్ణాంకం dstbpp;
    Uint32 pixelvalue;
    గుర్తులేని sR, sG, sB, sA;
    గుర్తులేని dR, dG, dB, dA;
    స్థిరరాశి గుర్తులేని A = info->a;

    // Set up some basic variables
    dstbpp = dstfmt->బైట్లు_చొప్పున_pixel;

    అయితే (ఎత్తు--) {
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
        వెడల్పు);
        /* *INDENT-ON* */ // clang-format on
        src += srcskip;
        dst += dstskip;
    }
}

స్థిర శూన్య Blit1to_NAlpha_కీలకం(SDL_BlitInfo *info)
{
    పూర్ణాంకం వెడల్పు = info->dst_w;
    పూర్ణాంకం ఎత్తు = info->dst_h;
    Uint8 *src = info->src;
    పూర్ణాంకం srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    పూర్ణాంకం dstskip = info->dst_skip;
    స్థిరరాశి SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    స్థిరరాశి SDL_Color *srcpal = info->src_pal->colors;
    Uint32 ckey = info->colorkey;
    పూర్ణాంకం dstbpp;
    Uint32 pixelvalue;
    గుర్తులేని sR, sG, sB, sA;
    గుర్తులేని dR, dG, dB, dA;
    స్థిరరాశి గుర్తులేని A = info->a;

    // Set up some basic variables
    dstbpp = dstfmt->బైట్లు_చొప్పున_pixel;

    అయితే (ఎత్తు--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP(
        {
            ఒకవేళ ( *src != ckey ) {
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
        వెడల్పు);
        /* *INDENT-ON* */ // clang-format on
        src += srcskip;
        dst += dstskip;
    }
}

స్థిర స్థిరరాశి SDL_BlitFunc one_blit[] = {
    (SDL_BlitFunc)ఖాళీ, Blit1to1, Blit1to2, Blit1to3, Blit1to4
};

స్థిర స్థిరరాశి SDL_BlitFunc one_blitkey[] = {
    (SDL_BlitFunc)ఖాళీ, Blit1to1_కీలకం, Blit1to2_కీలకం, Blit1to3_కీలకం, Blit1to4_కీలకం
};

SDL_BlitFunc SDL_CalculateBlit1(SDL_Surface *surface)
{
    పూర్ణాంకం which;

    ఒకవేళ (SDL_BITSPERPIXEL(surface->map.info.dst_fmt->format) < 8) {
        which = 0;
    } లేకపోతే {
        which = SDL_BYTESPERPIXEL(surface->map.info.dst_fmt->format);
    }

    ఎంపిక (surface->map.info.flags & ~SDL_COPY_RLE_ముసుగు) {
    స్థితి 0:
        ఒకవేళ (which < SDL_arraysize(one_blit)) {
            తిరిగి one_blit[which];
        }
        ఆపు;

    స్థితి SDL_COPY_COLORKEY:
        ఒకవేళ (which < SDL_arraysize(one_blitkey)) {
            తిరిగి one_blitkey[which];
        }
        ఆపు;

    స్థితి SDL_COPY_COLORKEY | SDL_COPY_BLEND:  // this is not super-robust but handles a specific case we found sdl12-compat.
        ఒకవేళ (surface->map.info.a == 255) {
            ఒకవేళ (which < SDL_arraysize(one_blitkey)) {
                తిరిగి one_blitkey[which];
            }
        } లేకపోతే {
            తిరిగి which >= 2 ? Blit1to_NAlpha_కీలకం : (SDL_BlitFunc)ఖాళీ;
        }
        ఆపు;

    స్థితి SDL_COPY_BLEND:
    స్థితి SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
        /* Supporting 8bpp->8bpp alpha is doable but requires lots of
           tables which consume space and takes time to precompute,
           so is better left to the user */
        తిరిగి which >= 2 ? Blit1toNAlpha : (SDL_BlitFunc)ఖాళీ;

    స్థితి SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
        తిరిగి which >= 2 ? Blit1to_NAlpha_కీలకం : (SDL_BlitFunc)ఖాళీ;
    }
    తిరిగి (SDL_BlitFunc)ఖాళీ;
}

#అయితే_ముగింపు // SDL_HAVE_BLIT_1
