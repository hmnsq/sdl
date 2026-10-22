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

#اگر_تعریف_شدہ SDL_HAVE_BLIT_1

#شامل "SDL_surface_c.h"
#شامل "SDL_sysvideo.h"

// Functions to blit from 8-bit surfaces to other surfaces

ساکن خالی Blit1to1(SDL_BlitInfo *info)
{
#اگر_غیر_تعریف_شدہ USE_DUFFS_LOOP
    صحیح c;
#اگر_ختم
    صحیح چوڑائی, اونچائی;
    Uint8 *src, *map, *dst;
    صحیح srcskip, dstskip;

    // Set up some basic variables
    چوڑائی = info->dst_w;
    اونچائی = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = info->جدول;

    جب (اونچائی--) {
#اگر_تعریف_شدہ USE_DUFFS_LOOP
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
            {
              *dst = map[*src];
            }
            dst++;
            src++;
        , چوڑائی);
        /* *INDENT-ON* */ // clang-format on
#ورنہ
        برائے (c = چوڑائی; c; --c) {
            *dst = map[*src];
            dst++;
            src++;
        }
#اگر_ختم
        src += srcskip;
        dst += dstskip;
    }
}

// This is now endian dependent
#اگر_غیر_تعریف_شدہ USE_DUFFS_LOOP
#اگر (SDL_BYTEORDER == SDL_LIL_ENDIAN)
#تعریف_کرو HI 1
#تعریف_کرو LO 0
#ورنہ // ( SDL_BYTEORDER == SDL_BIG_ENDIAN )
#تعریف_کرو HI 0
#تعریف_کرو LO 1
#اگر_ختم
#اگر_ختم
ساکن خالی Blit1to2(SDL_BlitInfo *info)
{
#اگر_غیر_تعریف_شدہ USE_DUFFS_LOOP
    صحیح c;
#اگر_ختم
    صحیح چوڑائی, اونچائی;
    Uint8 *src, *dst;
    Uint16 *map;
    صحیح srcskip, dstskip;

    // Set up some basic variables
    چوڑائی = info->dst_w;
    اونچائی = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = (Uint16 *)info->جدول;

#اگر_تعریف_شدہ USE_DUFFS_LOOP
    جب (اونچائی--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
        {
            *(Uint16 *)dst = map[*src++];
            dst += 2;
        },
        چوڑائی);
        /* *INDENT-ON* */ // clang-format on
        src += srcskip;
        dst += dstskip;
    }
#ورنہ
    // Memory align at 4-byte boundary, if necessary
    اگر ((طویل)dst & 0x03) {
        // Don't do anything if width is 0
        اگر (چوڑائی == 0) {
            واپس;
        }
        --چوڑائی;

        جب (اونچائی--) {
            // Perform copy alignment
            *(Uint16 *)dst = map[*src++];
            dst += 2;

            // Copy in 4 pixel chunks
            برائے (c = چوڑائی / 4; c; --c) {
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
            }
            // Get any leftovers
            انتخاب (چوڑائی & 3) {
            حالت 3:
                *(Uint16 *)dst = map[*src++];
                dst += 2;
                SDL_FALLTHROUGH;
            حالت 2:
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
                توڑو;
            حالت 1:
                *(Uint16 *)dst = map[*src++];
                dst += 2;
                توڑو;
            }
            src += srcskip;
            dst += dstskip;
        }
    } ورنہ {
        جب (اونچائی--) {
            // Copy in 4 pixel chunks
            برائے (c = چوڑائی / 4; c; --c) {
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
            }
            // Get any leftovers
            انتخاب (چوڑائی & 3) {
            حالت 3:
                *(Uint16 *)dst = map[*src++];
                dst += 2;
                SDL_FALLTHROUGH;
            حالت 2:
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
                توڑو;
            حالت 1:
                *(Uint16 *)dst = map[*src++];
                dst += 2;
                توڑو;
            }
            src += srcskip;
            dst += dstskip;
        }
    }
#اگر_ختم // USE_DUFFS_LOOP
}

ساکن خالی Blit1to3(SDL_BlitInfo *info)
{
#اگر_غیر_تعریف_شدہ USE_DUFFS_LOOP
    صحیح c;
#اگر_ختم
    صحیح o;
    صحیح چوڑائی, اونچائی;
    Uint8 *src, *map, *dst;
    صحیح srcskip, dstskip;

    // Set up some basic variables
    چوڑائی = info->dst_w;
    اونچائی = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = info->جدول;

    جب (اونچائی--) {
#اگر_تعریف_شدہ USE_DUFFS_LOOP
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
        , چوڑائی);
        /* *INDENT-ON* */ // clang-format on
#ورنہ
        برائے (c = چوڑائی; c; --c) {
            o = *src * 4;
            dst[0] = map[o++];
            dst[1] = map[o++];
            dst[2] = map[o++];
            src++;
            dst += 3;
        }
#اگر_ختم // USE_DUFFS_LOOP
        src += srcskip;
        dst += dstskip;
    }
}

ساکن خالی Blit1to4(SDL_BlitInfo *info)
{
#اگر_غیر_تعریف_شدہ USE_DUFFS_LOOP
    صحیح c;
#اگر_ختم
    صحیح چوڑائی, اونچائی;
    Uint8 *src;
    Uint32 *map, *dst;
    صحیح srcskip, dstskip;

    // Set up some basic variables
    چوڑائی = info->dst_w;
    اونچائی = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = (Uint32 *)info->dst;
    dstskip = info->dst_skip / 4;
    map = (Uint32 *)info->جدول;

    جب (اونچائی--) {
#اگر_تعریف_شدہ USE_DUFFS_LOOP
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
            *dst++ = map[*src++];
        , چوڑائی);
        /* *INDENT-ON* */ // clang-format on
#ورنہ
        برائے (c = چوڑائی / 4; c; --c) {
            *dst++ = map[*src++];
            *dst++ = map[*src++];
            *dst++ = map[*src++];
            *dst++ = map[*src++];
        }
        انتخاب (چوڑائی & 3) {
        حالت 3:
            *dst++ = map[*src++];
            SDL_FALLTHROUGH;
        حالت 2:
            *dst++ = map[*src++];
            SDL_FALLTHROUGH;
        حالت 1:
            *dst++ = map[*src++];
        }
#اگر_ختم // USE_DUFFS_LOOP
        src += srcskip;
        dst += dstskip;
    }
}

ساکن خالی Blit1to1_کلید(SDL_BlitInfo *info)
{
    صحیح چوڑائی = info->dst_w;
    صحیح اونچائی = info->dst_h;
    Uint8 *src = info->src;
    صحیح srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    صحیح dstskip = info->dst_skip;
    Uint8 *palmap = info->جدول;
    Uint32 ckey = info->colorkey;

    اگر (palmap) {
        جب (اونچائی--) {
            /* *INDENT-OFF* */ // clang-format off
            DUFFS_LOOP_TRIVIAL(
            {
                اگر ( *src != ckey ) {
                  *dst = palmap[*src];
                }
                dst++;
                src++;
            },
            چوڑائی);
            /* *INDENT-ON* */ // clang-format on
            src += srcskip;
            dst += dstskip;
        }
    } ورنہ {
        جب (اونچائی--) {
            /* *INDENT-OFF* */ // clang-format off
            DUFFS_LOOP_TRIVIAL(
            {
                اگر ( *src != ckey ) {
                  *dst = *src;
                }
                dst++;
                src++;
            },
            چوڑائی);
            /* *INDENT-ON* */ // clang-format on
            src += srcskip;
            dst += dstskip;
        }
    }
}

ساکن خالی Blit1to2_کلید(SDL_BlitInfo *info)
{
    صحیح چوڑائی = info->dst_w;
    صحیح اونچائی = info->dst_h;
    Uint8 *src = info->src;
    صحیح srcskip = info->src_skip;
    Uint16 *dstp = (Uint16 *)info->dst;
    صحیح dstskip = info->dst_skip;
    Uint16 *palmap = (Uint16 *)info->جدول;
    Uint32 ckey = info->colorkey;

    // Set up some basic variables
    dstskip /= 2;

    جب (اونچائی--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
        {
            اگر ( *src != ckey ) {
                *dstp=palmap[*src];
            }
            src++;
            dstp++;
        },
        چوڑائی);
        /* *INDENT-ON* */ // clang-format on
        src += srcskip;
        dstp += dstskip;
    }
}

ساکن خالی Blit1to3_کلید(SDL_BlitInfo *info)
{
    صحیح چوڑائی = info->dst_w;
    صحیح اونچائی = info->dst_h;
    Uint8 *src = info->src;
    صحیح srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    صحیح dstskip = info->dst_skip;
    Uint8 *palmap = info->جدول;
    Uint32 ckey = info->colorkey;
    صحیح o;

    جب (اونچائی--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP(
        {
            اگر ( *src != ckey ) {
                o = *src * 4;
                dst[0] = palmap[o++];
                dst[1] = palmap[o++];
                dst[2] = palmap[o++];
            }
            src++;
            dst += 3;
        },
        چوڑائی);
        /* *INDENT-ON* */ // clang-format on
        src += srcskip;
        dst += dstskip;
    }
}

ساکن خالی Blit1to4_کلید(SDL_BlitInfo *info)
{
    صحیح چوڑائی = info->dst_w;
    صحیح اونچائی = info->dst_h;
    Uint8 *src = info->src;
    صحیح srcskip = info->src_skip;
    Uint32 *dstp = (Uint32 *)info->dst;
    صحیح dstskip = info->dst_skip;
    Uint32 *palmap = (Uint32 *)info->جدول;
    Uint32 ckey = info->colorkey;

    // Set up some basic variables
    dstskip /= 4;

    جب (اونچائی--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
        {
            اگر ( *src != ckey ) {
                *dstp = palmap[*src];
            }
            src++;
            dstp++;
        },
        چوڑائی);
        /* *INDENT-ON* */ // clang-format on
        src += srcskip;
        dstp += dstskip;
    }
}

ساکن خالی Blit1toNAlpha(SDL_BlitInfo *info)
{
    صحیح چوڑائی = info->dst_w;
    صحیح اونچائی = info->dst_h;
    Uint8 *src = info->src;
    صحیح srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    صحیح dstskip = info->dst_skip;
    ثابت SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    ثابت SDL_Color *srcpal = info->src_pal->colors;
    صحیح dstbpp;
    Uint32 pixelvalue;
    غیرعلامتی sR, sG, sB, sA;
    غیرعلامتی dR, dG, dB, dA;
    ثابت غیرعلامتی A = info->a;

    // Set up some basic variables
    dstbpp = dstfmt->بائٹیں_فی_pixel;

    جب (اونچائی--) {
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
        چوڑائی);
        /* *INDENT-ON* */ // clang-format on
        src += srcskip;
        dst += dstskip;
    }
}

ساکن خالی Blit1to_NAlpha_کلید(SDL_BlitInfo *info)
{
    صحیح چوڑائی = info->dst_w;
    صحیح اونچائی = info->dst_h;
    Uint8 *src = info->src;
    صحیح srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    صحیح dstskip = info->dst_skip;
    ثابت SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    ثابت SDL_Color *srcpal = info->src_pal->colors;
    Uint32 ckey = info->colorkey;
    صحیح dstbpp;
    Uint32 pixelvalue;
    غیرعلامتی sR, sG, sB, sA;
    غیرعلامتی dR, dG, dB, dA;
    ثابت غیرعلامتی A = info->a;

    // Set up some basic variables
    dstbpp = dstfmt->بائٹیں_فی_pixel;

    جب (اونچائی--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP(
        {
            اگر ( *src != ckey ) {
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
        چوڑائی);
        /* *INDENT-ON* */ // clang-format on
        src += srcskip;
        dst += dstskip;
    }
}

ساکن ثابت SDL_BlitFunc one_blit[] = {
    (SDL_BlitFunc)تہی, Blit1to1, Blit1to2, Blit1to3, Blit1to4
};

ساکن ثابت SDL_BlitFunc one_blitkey[] = {
    (SDL_BlitFunc)تہی, Blit1to1_کلید, Blit1to2_کلید, Blit1to3_کلید, Blit1to4_کلید
};

SDL_BlitFunc SDL_CalculateBlit1(SDL_Surface *surface)
{
    صحیح which;

    اگر (SDL_BITSPERPIXEL(surface->map.info.dst_fmt->format) < 8) {
        which = 0;
    } ورنہ {
        which = SDL_BYTESPERPIXEL(surface->map.info.dst_fmt->format);
    }

    انتخاب (surface->map.info.flags & ~SDL_COPY_RLE_نقاب) {
    حالت 0:
        اگر (which < SDL_arraysize(one_blit)) {
            واپس one_blit[which];
        }
        توڑو;

    حالت SDL_COPY_COLORKEY:
        اگر (which < SDL_arraysize(one_blitkey)) {
            واپس one_blitkey[which];
        }
        توڑو;

    حالت SDL_COPY_COLORKEY | SDL_COPY_BLEND:  // this is not super-robust but handles a specific case we found sdl12-compat.
        اگر (surface->map.info.a == 255) {
            اگر (which < SDL_arraysize(one_blitkey)) {
                واپس one_blitkey[which];
            }
        } ورنہ {
            واپس which >= 2 ? Blit1to_NAlpha_کلید : (SDL_BlitFunc)تہی;
        }
        توڑو;

    حالت SDL_COPY_BLEND:
    حالت SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
        /* Supporting 8bpp->8bpp alpha is doable but requires lots of
           tables which consume space and takes time to precompute,
           so is better left to the user */
        واپس which >= 2 ? Blit1toNAlpha : (SDL_BlitFunc)تہی;

    حالت SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
        واپس which >= 2 ? Blit1to_NAlpha_کلید : (SDL_BlitFunc)تہی;
    }
    واپس (SDL_BlitFunc)تہی;
}

#اگر_ختم // SDL_HAVE_BLIT_1
