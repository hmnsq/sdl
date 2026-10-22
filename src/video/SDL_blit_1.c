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
#ضمن "SDL_internal.h"

#اگر_تعریف_شده SDL_HAVE_BLIT_1

#ضمن "SDL_surface_c.h"
#ضمن "SDL_sysvideo.h"

// Functions to blit from 8-bit surfaces to other surfaces

ساكن فراغ Blit1to1(SDL_BlitInfo *info)
{
#اگر_تعریف_نشده USE_DUFFS_LOOP
    صحيح c;
#پایان_اگر
    صحيح عرض, ارتفاع;
    Uint8 *src, *map, *dst;
    صحيح srcskip, dstskip;

    // Set up some basic variables
    عرض = info->dst_w;
    ارتفاع = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = info->جدول;

    طالما (ارتفاع--) {
#اگر_تعریف_شده USE_DUFFS_LOOP
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
            {
              *dst = map[*src];
            }
            dst++;
            src++;
        , عرض);
        /* *INDENT-ON* */ // clang-format on
#وإلا
        لكل (c = عرض; c; --c) {
            *dst = map[*src];
            dst++;
            src++;
        }
#پایان_اگر
        src += srcskip;
        dst += dstskip;
    }
}

// This is now endian dependent
#اگر_تعریف_نشده USE_DUFFS_LOOP
#إذا (SDL_BYTEORDER == SDL_LIL_ENDIAN)
#تعریف_کن HI 1
#تعریف_کن LO 0
#وإلا // ( SDL_BYTEORDER == SDL_BIG_ENDIAN )
#تعریف_کن HI 0
#تعریف_کن LO 1
#پایان_اگر
#پایان_اگر
ساكن فراغ Blit1to2(SDL_BlitInfo *info)
{
#اگر_تعریف_نشده USE_DUFFS_LOOP
    صحيح c;
#پایان_اگر
    صحيح عرض, ارتفاع;
    Uint8 *src, *dst;
    Uint16 *map;
    صحيح srcskip, dstskip;

    // Set up some basic variables
    عرض = info->dst_w;
    ارتفاع = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = (Uint16 *)info->جدول;

#اگر_تعریف_شده USE_DUFFS_LOOP
    طالما (ارتفاع--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
        {
            *(Uint16 *)dst = map[*src++];
            dst += 2;
        },
        عرض);
        /* *INDENT-ON* */ // clang-format on
        src += srcskip;
        dst += dstskip;
    }
#وإلا
    // Memory align at 4-byte boundary, if necessary
    إذا ((دراز)dst & 0x03) {
        // Don't do anything if width is 0
        إذا (عرض == 0) {
            أرجع;
        }
        --عرض;

        طالما (ارتفاع--) {
            // Perform copy alignment
            *(Uint16 *)dst = map[*src++];
            dst += 2;

            // Copy in 4 pixel chunks
            لكل (c = عرض / 4; c; --c) {
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
            }
            // Get any leftovers
            بدل (عرض & 3) {
            حالة 3:
                *(Uint16 *)dst = map[*src++];
                dst += 2;
                SDL_FALLTHROUGH;
            حالة 2:
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
                اكسر;
            حالة 1:
                *(Uint16 *)dst = map[*src++];
                dst += 2;
                اكسر;
            }
            src += srcskip;
            dst += dstskip;
        }
    } وإلا {
        طالما (ارتفاع--) {
            // Copy in 4 pixel chunks
            لكل (c = عرض / 4; c; --c) {
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
            }
            // Get any leftovers
            بدل (عرض & 3) {
            حالة 3:
                *(Uint16 *)dst = map[*src++];
                dst += 2;
                SDL_FALLTHROUGH;
            حالة 2:
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
                اكسر;
            حالة 1:
                *(Uint16 *)dst = map[*src++];
                dst += 2;
                اكسر;
            }
            src += srcskip;
            dst += dstskip;
        }
    }
#پایان_اگر // USE_DUFFS_LOOP
}

ساكن فراغ Blit1to3(SDL_BlitInfo *info)
{
#اگر_تعریف_نشده USE_DUFFS_LOOP
    صحيح c;
#پایان_اگر
    صحيح o;
    صحيح عرض, ارتفاع;
    Uint8 *src, *map, *dst;
    صحيح srcskip, dstskip;

    // Set up some basic variables
    عرض = info->dst_w;
    ارتفاع = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = info->جدول;

    طالما (ارتفاع--) {
#اگر_تعریف_شده USE_DUFFS_LOOP
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
        , عرض);
        /* *INDENT-ON* */ // clang-format on
#وإلا
        لكل (c = عرض; c; --c) {
            o = *src * 4;
            dst[0] = map[o++];
            dst[1] = map[o++];
            dst[2] = map[o++];
            src++;
            dst += 3;
        }
#پایان_اگر // USE_DUFFS_LOOP
        src += srcskip;
        dst += dstskip;
    }
}

ساكن فراغ Blit1to4(SDL_BlitInfo *info)
{
#اگر_تعریف_نشده USE_DUFFS_LOOP
    صحيح c;
#پایان_اگر
    صحيح عرض, ارتفاع;
    Uint8 *src;
    Uint32 *map, *dst;
    صحيح srcskip, dstskip;

    // Set up some basic variables
    عرض = info->dst_w;
    ارتفاع = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = (Uint32 *)info->dst;
    dstskip = info->dst_skip / 4;
    map = (Uint32 *)info->جدول;

    طالما (ارتفاع--) {
#اگر_تعریف_شده USE_DUFFS_LOOP
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
            *dst++ = map[*src++];
        , عرض);
        /* *INDENT-ON* */ // clang-format on
#وإلا
        لكل (c = عرض / 4; c; --c) {
            *dst++ = map[*src++];
            *dst++ = map[*src++];
            *dst++ = map[*src++];
            *dst++ = map[*src++];
        }
        بدل (عرض & 3) {
        حالة 3:
            *dst++ = map[*src++];
            SDL_FALLTHROUGH;
        حالة 2:
            *dst++ = map[*src++];
            SDL_FALLTHROUGH;
        حالة 1:
            *dst++ = map[*src++];
        }
#پایان_اگر // USE_DUFFS_LOOP
        src += srcskip;
        dst += dstskip;
    }
}

ساكن فراغ Blit1to1_کلید(SDL_BlitInfo *info)
{
    صحيح عرض = info->dst_w;
    صحيح ارتفاع = info->dst_h;
    Uint8 *src = info->src;
    صحيح srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    صحيح dstskip = info->dst_skip;
    Uint8 *palmap = info->جدول;
    Uint32 ckey = info->colorkey;

    إذا (palmap) {
        طالما (ارتفاع--) {
            /* *INDENT-OFF* */ // clang-format off
            DUFFS_LOOP_TRIVIAL(
            {
                إذا ( *src != ckey ) {
                  *dst = palmap[*src];
                }
                dst++;
                src++;
            },
            عرض);
            /* *INDENT-ON* */ // clang-format on
            src += srcskip;
            dst += dstskip;
        }
    } وإلا {
        طالما (ارتفاع--) {
            /* *INDENT-OFF* */ // clang-format off
            DUFFS_LOOP_TRIVIAL(
            {
                إذا ( *src != ckey ) {
                  *dst = *src;
                }
                dst++;
                src++;
            },
            عرض);
            /* *INDENT-ON* */ // clang-format on
            src += srcskip;
            dst += dstskip;
        }
    }
}

ساكن فراغ Blit1to2_کلید(SDL_BlitInfo *info)
{
    صحيح عرض = info->dst_w;
    صحيح ارتفاع = info->dst_h;
    Uint8 *src = info->src;
    صحيح srcskip = info->src_skip;
    Uint16 *dstp = (Uint16 *)info->dst;
    صحيح dstskip = info->dst_skip;
    Uint16 *palmap = (Uint16 *)info->جدول;
    Uint32 ckey = info->colorkey;

    // Set up some basic variables
    dstskip /= 2;

    طالما (ارتفاع--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
        {
            إذا ( *src != ckey ) {
                *dstp=palmap[*src];
            }
            src++;
            dstp++;
        },
        عرض);
        /* *INDENT-ON* */ // clang-format on
        src += srcskip;
        dstp += dstskip;
    }
}

ساكن فراغ Blit1to3_کلید(SDL_BlitInfo *info)
{
    صحيح عرض = info->dst_w;
    صحيح ارتفاع = info->dst_h;
    Uint8 *src = info->src;
    صحيح srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    صحيح dstskip = info->dst_skip;
    Uint8 *palmap = info->جدول;
    Uint32 ckey = info->colorkey;
    صحيح o;

    طالما (ارتفاع--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP(
        {
            إذا ( *src != ckey ) {
                o = *src * 4;
                dst[0] = palmap[o++];
                dst[1] = palmap[o++];
                dst[2] = palmap[o++];
            }
            src++;
            dst += 3;
        },
        عرض);
        /* *INDENT-ON* */ // clang-format on
        src += srcskip;
        dst += dstskip;
    }
}

ساكن فراغ Blit1to4_کلید(SDL_BlitInfo *info)
{
    صحيح عرض = info->dst_w;
    صحيح ارتفاع = info->dst_h;
    Uint8 *src = info->src;
    صحيح srcskip = info->src_skip;
    Uint32 *dstp = (Uint32 *)info->dst;
    صحيح dstskip = info->dst_skip;
    Uint32 *palmap = (Uint32 *)info->جدول;
    Uint32 ckey = info->colorkey;

    // Set up some basic variables
    dstskip /= 4;

    طالما (ارتفاع--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
        {
            إذا ( *src != ckey ) {
                *dstp = palmap[*src];
            }
            src++;
            dstp++;
        },
        عرض);
        /* *INDENT-ON* */ // clang-format on
        src += srcskip;
        dstp += dstskip;
    }
}

ساكن فراغ Blit1toNAlpha(SDL_BlitInfo *info)
{
    صحيح عرض = info->dst_w;
    صحيح ارتفاع = info->dst_h;
    Uint8 *src = info->src;
    صحيح srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    صحيح dstskip = info->dst_skip;
    ثابت SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    ثابت SDL_Color *srcpal = info->src_pal->colors;
    صحيح dstbpp;
    Uint32 pixelvalue;
    بیعلامت sR, sG, sB, sA;
    بیعلامت dR, dG, dB, dA;
    ثابت بیعلامت A = info->a;

    // Set up some basic variables
    dstbpp = dstfmt->بایتها_در_هر_pixel;

    طالما (ارتفاع--) {
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
        عرض);
        /* *INDENT-ON* */ // clang-format on
        src += srcskip;
        dst += dstskip;
    }
}

ساكن فراغ Blit1to_NAlpha_کلید(SDL_BlitInfo *info)
{
    صحيح عرض = info->dst_w;
    صحيح ارتفاع = info->dst_h;
    Uint8 *src = info->src;
    صحيح srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    صحيح dstskip = info->dst_skip;
    ثابت SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    ثابت SDL_Color *srcpal = info->src_pal->colors;
    Uint32 ckey = info->colorkey;
    صحيح dstbpp;
    Uint32 pixelvalue;
    بیعلامت sR, sG, sB, sA;
    بیعلامت dR, dG, dB, dA;
    ثابت بیعلامت A = info->a;

    // Set up some basic variables
    dstbpp = dstfmt->بایتها_در_هر_pixel;

    طالما (ارتفاع--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP(
        {
            إذا ( *src != ckey ) {
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
        عرض);
        /* *INDENT-ON* */ // clang-format on
        src += srcskip;
        dst += dstskip;
    }
}

ساكن ثابت SDL_BlitFunc one_blit[] = {
    (SDL_BlitFunc)عدم, Blit1to1, Blit1to2, Blit1to3, Blit1to4
};

ساكن ثابت SDL_BlitFunc one_blitkey[] = {
    (SDL_BlitFunc)عدم, Blit1to1_کلید, Blit1to2_کلید, Blit1to3_کلید, Blit1to4_کلید
};

SDL_BlitFunc SDL_CalculateBlit1(SDL_Surface *surface)
{
    صحيح which;

    إذا (SDL_BITSPERPIXEL(surface->map.info.dst_fmt->format) < 8) {
        which = 0;
    } وإلا {
        which = SDL_BYTESPERPIXEL(surface->map.info.dst_fmt->format);
    }

    بدل (surface->map.info.flags & ~SDL_COPY_RLE_ماسک) {
    حالة 0:
        إذا (which < SDL_arraysize(one_blit)) {
            أرجع one_blit[which];
        }
        اكسر;

    حالة SDL_COPY_COLORKEY:
        إذا (which < SDL_arraysize(one_blitkey)) {
            أرجع one_blitkey[which];
        }
        اكسر;

    حالة SDL_COPY_COLORKEY | SDL_COPY_BLEND:  // this is not super-robust but handles a specific case we found sdl12-compat.
        إذا (surface->map.info.a == 255) {
            إذا (which < SDL_arraysize(one_blitkey)) {
                أرجع one_blitkey[which];
            }
        } وإلا {
            أرجع which >= 2 ? Blit1to_NAlpha_کلید : (SDL_BlitFunc)عدم;
        }
        اكسر;

    حالة SDL_COPY_BLEND:
    حالة SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
        /* Supporting 8bpp->8bpp alpha is doable but requires lots of
           tables which consume space and takes time to precompute,
           so is better left to the user */
        أرجع which >= 2 ? Blit1toNAlpha : (SDL_BlitFunc)عدم;

    حالة SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
        أرجع which >= 2 ? Blit1to_NAlpha_کلید : (SDL_BlitFunc)عدم;
    }
    أرجع (SDL_BlitFunc)عدم;
}

#پایان_اگر // SDL_HAVE_BLIT_1
