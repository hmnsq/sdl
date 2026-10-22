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

#که_تعریف_شوی SDL_HAVE_BLIT_1

#ضمن "SDL_surface_c.h"
#ضمن "SDL_sysvideo.h"

// Functions to blit from 8-bit surfaces to other surfaces

ساكن فراغ Blit1to1(SDL_BlitInfo *info)
{
#که_نه_تعریف_شوی USE_DUFFS_LOOP
    صحيح c;
#د_که_پای
    صحيح پلنوالی, لوړوالی;
    Uint8 *src, *map, *dst;
    صحيح srcskip, dstskip;

    // Set up some basic variables
    پلنوالی = info->dst_w;
    لوړوالی = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = info->جدول;

    طالما (لوړوالی--) {
#که_تعریف_شوی USE_DUFFS_LOOP
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
            {
              *dst = map[*src];
            }
            dst++;
            src++;
        , پلنوالی);
        /* *INDENT-ON* */ // clang-format on
#وإلا
        لكل (c = پلنوالی; c; --c) {
            *dst = map[*src];
            dst++;
            src++;
        }
#د_که_پای
        src += srcskip;
        dst += dstskip;
    }
}

// This is now endian dependent
#که_نه_تعریف_شوی USE_DUFFS_LOOP
#إذا (SDL_BYTEORDER == SDL_LIL_ENDIAN)
#تعریف_کړه HI 1
#تعریف_کړه LO 0
#وإلا // ( SDL_BYTEORDER == SDL_BIG_ENDIAN )
#تعریف_کړه HI 0
#تعریف_کړه LO 1
#د_که_پای
#د_که_پای
ساكن فراغ Blit1to2(SDL_BlitInfo *info)
{
#که_نه_تعریف_شوی USE_DUFFS_LOOP
    صحيح c;
#د_که_پای
    صحيح پلنوالی, لوړوالی;
    Uint8 *src, *dst;
    Uint16 *map;
    صحيح srcskip, dstskip;

    // Set up some basic variables
    پلنوالی = info->dst_w;
    لوړوالی = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = (Uint16 *)info->جدول;

#که_تعریف_شوی USE_DUFFS_LOOP
    طالما (لوړوالی--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
        {
            *(Uint16 *)dst = map[*src++];
            dst += 2;
        },
        پلنوالی);
        /* *INDENT-ON* */ // clang-format on
        src += srcskip;
        dst += dstskip;
    }
#وإلا
    // Memory align at 4-byte boundary, if necessary
    إذا ((اوږد)dst & 0x03) {
        // Don't do anything if width is 0
        إذا (پلنوالی == 0) {
            أرجع;
        }
        --پلنوالی;

        طالما (لوړوالی--) {
            // Perform copy alignment
            *(Uint16 *)dst = map[*src++];
            dst += 2;

            // Copy in 4 pixel chunks
            لكل (c = پلنوالی / 4; c; --c) {
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
            }
            // Get any leftovers
            بدل (پلنوالی & 3) {
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
        طالما (لوړوالی--) {
            // Copy in 4 pixel chunks
            لكل (c = پلنوالی / 4; c; --c) {
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
            }
            // Get any leftovers
            بدل (پلنوالی & 3) {
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
#د_که_پای // USE_DUFFS_LOOP
}

ساكن فراغ Blit1to3(SDL_BlitInfo *info)
{
#که_نه_تعریف_شوی USE_DUFFS_LOOP
    صحيح c;
#د_که_پای
    صحيح o;
    صحيح پلنوالی, لوړوالی;
    Uint8 *src, *map, *dst;
    صحيح srcskip, dstskip;

    // Set up some basic variables
    پلنوالی = info->dst_w;
    لوړوالی = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = info->جدول;

    طالما (لوړوالی--) {
#که_تعریف_شوی USE_DUFFS_LOOP
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
        , پلنوالی);
        /* *INDENT-ON* */ // clang-format on
#وإلا
        لكل (c = پلنوالی; c; --c) {
            o = *src * 4;
            dst[0] = map[o++];
            dst[1] = map[o++];
            dst[2] = map[o++];
            src++;
            dst += 3;
        }
#د_که_پای // USE_DUFFS_LOOP
        src += srcskip;
        dst += dstskip;
    }
}

ساكن فراغ Blit1to4(SDL_BlitInfo *info)
{
#که_نه_تعریف_شوی USE_DUFFS_LOOP
    صحيح c;
#د_که_پای
    صحيح پلنوالی, لوړوالی;
    Uint8 *src;
    Uint32 *map, *dst;
    صحيح srcskip, dstskip;

    // Set up some basic variables
    پلنوالی = info->dst_w;
    لوړوالی = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = (Uint32 *)info->dst;
    dstskip = info->dst_skip / 4;
    map = (Uint32 *)info->جدول;

    طالما (لوړوالی--) {
#که_تعریف_شوی USE_DUFFS_LOOP
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
            *dst++ = map[*src++];
        , پلنوالی);
        /* *INDENT-ON* */ // clang-format on
#وإلا
        لكل (c = پلنوالی / 4; c; --c) {
            *dst++ = map[*src++];
            *dst++ = map[*src++];
            *dst++ = map[*src++];
            *dst++ = map[*src++];
        }
        بدل (پلنوالی & 3) {
        حالة 3:
            *dst++ = map[*src++];
            SDL_FALLTHROUGH;
        حالة 2:
            *dst++ = map[*src++];
            SDL_FALLTHROUGH;
        حالة 1:
            *dst++ = map[*src++];
        }
#د_که_پای // USE_DUFFS_LOOP
        src += srcskip;
        dst += dstskip;
    }
}

ساكن فراغ Blit1to1_کلی(SDL_BlitInfo *info)
{
    صحيح پلنوالی = info->dst_w;
    صحيح لوړوالی = info->dst_h;
    Uint8 *src = info->src;
    صحيح srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    صحيح dstskip = info->dst_skip;
    Uint8 *palmap = info->جدول;
    Uint32 ckey = info->colorkey;

    إذا (palmap) {
        طالما (لوړوالی--) {
            /* *INDENT-OFF* */ // clang-format off
            DUFFS_LOOP_TRIVIAL(
            {
                إذا ( *src != ckey ) {
                  *dst = palmap[*src];
                }
                dst++;
                src++;
            },
            پلنوالی);
            /* *INDENT-ON* */ // clang-format on
            src += srcskip;
            dst += dstskip;
        }
    } وإلا {
        طالما (لوړوالی--) {
            /* *INDENT-OFF* */ // clang-format off
            DUFFS_LOOP_TRIVIAL(
            {
                إذا ( *src != ckey ) {
                  *dst = *src;
                }
                dst++;
                src++;
            },
            پلنوالی);
            /* *INDENT-ON* */ // clang-format on
            src += srcskip;
            dst += dstskip;
        }
    }
}

ساكن فراغ Blit1to2_کلی(SDL_BlitInfo *info)
{
    صحيح پلنوالی = info->dst_w;
    صحيح لوړوالی = info->dst_h;
    Uint8 *src = info->src;
    صحيح srcskip = info->src_skip;
    Uint16 *dstp = (Uint16 *)info->dst;
    صحيح dstskip = info->dst_skip;
    Uint16 *palmap = (Uint16 *)info->جدول;
    Uint32 ckey = info->colorkey;

    // Set up some basic variables
    dstskip /= 2;

    طالما (لوړوالی--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
        {
            إذا ( *src != ckey ) {
                *dstp=palmap[*src];
            }
            src++;
            dstp++;
        },
        پلنوالی);
        /* *INDENT-ON* */ // clang-format on
        src += srcskip;
        dstp += dstskip;
    }
}

ساكن فراغ Blit1to3_کلی(SDL_BlitInfo *info)
{
    صحيح پلنوالی = info->dst_w;
    صحيح لوړوالی = info->dst_h;
    Uint8 *src = info->src;
    صحيح srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    صحيح dstskip = info->dst_skip;
    Uint8 *palmap = info->جدول;
    Uint32 ckey = info->colorkey;
    صحيح o;

    طالما (لوړوالی--) {
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
        پلنوالی);
        /* *INDENT-ON* */ // clang-format on
        src += srcskip;
        dst += dstskip;
    }
}

ساكن فراغ Blit1to4_کلی(SDL_BlitInfo *info)
{
    صحيح پلنوالی = info->dst_w;
    صحيح لوړوالی = info->dst_h;
    Uint8 *src = info->src;
    صحيح srcskip = info->src_skip;
    Uint32 *dstp = (Uint32 *)info->dst;
    صحيح dstskip = info->dst_skip;
    Uint32 *palmap = (Uint32 *)info->جدول;
    Uint32 ckey = info->colorkey;

    // Set up some basic variables
    dstskip /= 4;

    طالما (لوړوالی--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
        {
            إذا ( *src != ckey ) {
                *dstp = palmap[*src];
            }
            src++;
            dstp++;
        },
        پلنوالی);
        /* *INDENT-ON* */ // clang-format on
        src += srcskip;
        dstp += dstskip;
    }
}

ساكن فراغ Blit1toNAlpha(SDL_BlitInfo *info)
{
    صحيح پلنوالی = info->dst_w;
    صحيح لوړوالی = info->dst_h;
    Uint8 *src = info->src;
    صحيح srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    صحيح dstskip = info->dst_skip;
    ثابت SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    ثابت SDL_Color *srcpal = info->src_pal->colors;
    صحيح dstbpp;
    Uint32 pixelvalue;
    بینښه sR, sG, sB, sA;
    بینښه dR, dG, dB, dA;
    ثابت بینښه A = info->a;

    // Set up some basic variables
    dstbpp = dstfmt->بایټونه_فی_pixel;

    طالما (لوړوالی--) {
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
        پلنوالی);
        /* *INDENT-ON* */ // clang-format on
        src += srcskip;
        dst += dstskip;
    }
}

ساكن فراغ Blit1to_NAlpha_کلی(SDL_BlitInfo *info)
{
    صحيح پلنوالی = info->dst_w;
    صحيح لوړوالی = info->dst_h;
    Uint8 *src = info->src;
    صحيح srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    صحيح dstskip = info->dst_skip;
    ثابت SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    ثابت SDL_Color *srcpal = info->src_pal->colors;
    Uint32 ckey = info->colorkey;
    صحيح dstbpp;
    Uint32 pixelvalue;
    بینښه sR, sG, sB, sA;
    بینښه dR, dG, dB, dA;
    ثابت بینښه A = info->a;

    // Set up some basic variables
    dstbpp = dstfmt->بایټونه_فی_pixel;

    طالما (لوړوالی--) {
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
        پلنوالی);
        /* *INDENT-ON* */ // clang-format on
        src += srcskip;
        dst += dstskip;
    }
}

ساكن ثابت SDL_BlitFunc one_blit[] = {
    (SDL_BlitFunc)عدم, Blit1to1, Blit1to2, Blit1to3, Blit1to4
};

ساكن ثابت SDL_BlitFunc one_blitkey[] = {
    (SDL_BlitFunc)عدم, Blit1to1_کلی, Blit1to2_کلی, Blit1to3_کلی, Blit1to4_کلی
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
            أرجع which >= 2 ? Blit1to_NAlpha_کلی : (SDL_BlitFunc)عدم;
        }
        اكسر;

    حالة SDL_COPY_BLEND:
    حالة SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
        /* Supporting 8bpp->8bpp alpha is doable but requires lots of
           tables which consume space and takes time to precompute,
           so is better left to the user */
        أرجع which >= 2 ? Blit1toNAlpha : (SDL_BlitFunc)عدم;

    حالة SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
        أرجع which >= 2 ? Blit1to_NAlpha_کلی : (SDL_BlitFunc)عدم;
    }
    أرجع (SDL_BlitFunc)عدم;
}

#د_که_پای // SDL_HAVE_BLIT_1
