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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_HAVE_BLIT_1

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_surface_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_sysvideo.h"

// Functions to blit from 8-bit surfaces to other surfaces

ਸਥਿਰ ਖਾਲੀ Blit1to1(SDL_BlitInfo *info)
{
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ USE_DUFFS_LOOP
    ਪੂਰਨ c;
#ਜੇ_ਅੰਤ
    ਪੂਰਨ ਚੌੜਾਈ, ਉਚਾਈ;
    Uint8 *src, *map, *dst;
    ਪੂਰਨ srcskip, dstskip;

    // Set up some basic variables
    ਚੌੜਾਈ = info->dst_w;
    ਉਚਾਈ = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = info->ਸਾਰਣੀ;

    ਜਦੋਂ (ਉਚਾਈ--) {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ USE_DUFFS_LOOP
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
            {
              *dst = map[*src];
            }
            dst++;
            src++;
        , ਚੌੜਾਈ);
        /* *INDENT-ON* */ // clang-format on
#ਨਹੀਂਤਾਂ
        ਲਈ (c = ਚੌੜਾਈ; c; --c) {
            *dst = map[*src];
            dst++;
            src++;
        }
#ਜੇ_ਅੰਤ
        src += srcskip;
        dst += dstskip;
    }
}

// This is now endian dependent
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ USE_DUFFS_LOOP
#ਜੇ (SDL_BYTEORDER == SDL_LIL_ENDIAN)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HI 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LO 0
#ਨਹੀਂਤਾਂ // ( SDL_BYTEORDER == SDL_BIG_ENDIAN )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HI 0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LO 1
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ
ਸਥਿਰ ਖਾਲੀ Blit1to2(SDL_BlitInfo *info)
{
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ USE_DUFFS_LOOP
    ਪੂਰਨ c;
#ਜੇ_ਅੰਤ
    ਪੂਰਨ ਚੌੜਾਈ, ਉਚਾਈ;
    Uint8 *src, *dst;
    Uint16 *map;
    ਪੂਰਨ srcskip, dstskip;

    // Set up some basic variables
    ਚੌੜਾਈ = info->dst_w;
    ਉਚਾਈ = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = (Uint16 *)info->ਸਾਰਣੀ;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ USE_DUFFS_LOOP
    ਜਦੋਂ (ਉਚਾਈ--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
        {
            *(Uint16 *)dst = map[*src++];
            dst += 2;
        },
        ਚੌੜਾਈ);
        /* *INDENT-ON* */ // clang-format on
        src += srcskip;
        dst += dstskip;
    }
#ਨਹੀਂਤਾਂ
    // Memory align at 4-byte boundary, if necessary
    ਜੇ ((ਲੰਮਾ)dst & 0x03) {
        // Don't do anything if width is 0
        ਜੇ (ਚੌੜਾਈ == 0) {
            ਵਾਪਸ;
        }
        --ਚੌੜਾਈ;

        ਜਦੋਂ (ਉਚਾਈ--) {
            // Perform copy alignment
            *(Uint16 *)dst = map[*src++];
            dst += 2;

            // Copy in 4 pixel chunks
            ਲਈ (c = ਚੌੜਾਈ / 4; c; --c) {
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
            }
            // Get any leftovers
            ਚੋਣ (ਚੌੜਾਈ & 3) {
            ਹਾਲਤ 3:
                *(Uint16 *)dst = map[*src++];
                dst += 2;
                SDL_FALLTHROUGH;
            ਹਾਲਤ 2:
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
                ਰੋਕੋ;
            ਹਾਲਤ 1:
                *(Uint16 *)dst = map[*src++];
                dst += 2;
                ਰੋਕੋ;
            }
            src += srcskip;
            dst += dstskip;
        }
    } ਨਹੀਂਤਾਂ {
        ਜਦੋਂ (ਉਚਾਈ--) {
            // Copy in 4 pixel chunks
            ਲਈ (c = ਚੌੜਾਈ / 4; c; --c) {
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
            }
            // Get any leftovers
            ਚੋਣ (ਚੌੜਾਈ & 3) {
            ਹਾਲਤ 3:
                *(Uint16 *)dst = map[*src++];
                dst += 2;
                SDL_FALLTHROUGH;
            ਹਾਲਤ 2:
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
                ਰੋਕੋ;
            ਹਾਲਤ 1:
                *(Uint16 *)dst = map[*src++];
                dst += 2;
                ਰੋਕੋ;
            }
            src += srcskip;
            dst += dstskip;
        }
    }
#ਜੇ_ਅੰਤ // USE_DUFFS_LOOP
}

ਸਥਿਰ ਖਾਲੀ Blit1to3(SDL_BlitInfo *info)
{
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ USE_DUFFS_LOOP
    ਪੂਰਨ c;
#ਜੇ_ਅੰਤ
    ਪੂਰਨ o;
    ਪੂਰਨ ਚੌੜਾਈ, ਉਚਾਈ;
    Uint8 *src, *map, *dst;
    ਪੂਰਨ srcskip, dstskip;

    // Set up some basic variables
    ਚੌੜਾਈ = info->dst_w;
    ਉਚਾਈ = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = info->ਸਾਰਣੀ;

    ਜਦੋਂ (ਉਚਾਈ--) {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ USE_DUFFS_LOOP
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
        , ਚੌੜਾਈ);
        /* *INDENT-ON* */ // clang-format on
#ਨਹੀਂਤਾਂ
        ਲਈ (c = ਚੌੜਾਈ; c; --c) {
            o = *src * 4;
            dst[0] = map[o++];
            dst[1] = map[o++];
            dst[2] = map[o++];
            src++;
            dst += 3;
        }
#ਜੇ_ਅੰਤ // USE_DUFFS_LOOP
        src += srcskip;
        dst += dstskip;
    }
}

ਸਥਿਰ ਖਾਲੀ Blit1to4(SDL_BlitInfo *info)
{
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ USE_DUFFS_LOOP
    ਪੂਰਨ c;
#ਜੇ_ਅੰਤ
    ਪੂਰਨ ਚੌੜਾਈ, ਉਚਾਈ;
    Uint8 *src;
    Uint32 *map, *dst;
    ਪੂਰਨ srcskip, dstskip;

    // Set up some basic variables
    ਚੌੜਾਈ = info->dst_w;
    ਉਚਾਈ = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = (Uint32 *)info->dst;
    dstskip = info->dst_skip / 4;
    map = (Uint32 *)info->ਸਾਰਣੀ;

    ਜਦੋਂ (ਉਚਾਈ--) {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ USE_DUFFS_LOOP
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
            *dst++ = map[*src++];
        , ਚੌੜਾਈ);
        /* *INDENT-ON* */ // clang-format on
#ਨਹੀਂਤਾਂ
        ਲਈ (c = ਚੌੜਾਈ / 4; c; --c) {
            *dst++ = map[*src++];
            *dst++ = map[*src++];
            *dst++ = map[*src++];
            *dst++ = map[*src++];
        }
        ਚੋਣ (ਚੌੜਾਈ & 3) {
        ਹਾਲਤ 3:
            *dst++ = map[*src++];
            SDL_FALLTHROUGH;
        ਹਾਲਤ 2:
            *dst++ = map[*src++];
            SDL_FALLTHROUGH;
        ਹਾਲਤ 1:
            *dst++ = map[*src++];
        }
#ਜੇ_ਅੰਤ // USE_DUFFS_LOOP
        src += srcskip;
        dst += dstskip;
    }
}

ਸਥਿਰ ਖਾਲੀ Blit1to1_ਕੁੰਜੀ(SDL_BlitInfo *info)
{
    ਪੂਰਨ ਚੌੜਾਈ = info->dst_w;
    ਪੂਰਨ ਉਚਾਈ = info->dst_h;
    Uint8 *src = info->src;
    ਪੂਰਨ srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    ਪੂਰਨ dstskip = info->dst_skip;
    Uint8 *palmap = info->ਸਾਰਣੀ;
    Uint32 ckey = info->colorkey;

    ਜੇ (palmap) {
        ਜਦੋਂ (ਉਚਾਈ--) {
            /* *INDENT-OFF* */ // clang-format off
            DUFFS_LOOP_TRIVIAL(
            {
                ਜੇ ( *src != ckey ) {
                  *dst = palmap[*src];
                }
                dst++;
                src++;
            },
            ਚੌੜਾਈ);
            /* *INDENT-ON* */ // clang-format on
            src += srcskip;
            dst += dstskip;
        }
    } ਨਹੀਂਤਾਂ {
        ਜਦੋਂ (ਉਚਾਈ--) {
            /* *INDENT-OFF* */ // clang-format off
            DUFFS_LOOP_TRIVIAL(
            {
                ਜੇ ( *src != ckey ) {
                  *dst = *src;
                }
                dst++;
                src++;
            },
            ਚੌੜਾਈ);
            /* *INDENT-ON* */ // clang-format on
            src += srcskip;
            dst += dstskip;
        }
    }
}

ਸਥਿਰ ਖਾਲੀ Blit1to2_ਕੁੰਜੀ(SDL_BlitInfo *info)
{
    ਪੂਰਨ ਚੌੜਾਈ = info->dst_w;
    ਪੂਰਨ ਉਚਾਈ = info->dst_h;
    Uint8 *src = info->src;
    ਪੂਰਨ srcskip = info->src_skip;
    Uint16 *dstp = (Uint16 *)info->dst;
    ਪੂਰਨ dstskip = info->dst_skip;
    Uint16 *palmap = (Uint16 *)info->ਸਾਰਣੀ;
    Uint32 ckey = info->colorkey;

    // Set up some basic variables
    dstskip /= 2;

    ਜਦੋਂ (ਉਚਾਈ--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
        {
            ਜੇ ( *src != ckey ) {
                *dstp=palmap[*src];
            }
            src++;
            dstp++;
        },
        ਚੌੜਾਈ);
        /* *INDENT-ON* */ // clang-format on
        src += srcskip;
        dstp += dstskip;
    }
}

ਸਥਿਰ ਖਾਲੀ Blit1to3_ਕੁੰਜੀ(SDL_BlitInfo *info)
{
    ਪੂਰਨ ਚੌੜਾਈ = info->dst_w;
    ਪੂਰਨ ਉਚਾਈ = info->dst_h;
    Uint8 *src = info->src;
    ਪੂਰਨ srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    ਪੂਰਨ dstskip = info->dst_skip;
    Uint8 *palmap = info->ਸਾਰਣੀ;
    Uint32 ckey = info->colorkey;
    ਪੂਰਨ o;

    ਜਦੋਂ (ਉਚਾਈ--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP(
        {
            ਜੇ ( *src != ckey ) {
                o = *src * 4;
                dst[0] = palmap[o++];
                dst[1] = palmap[o++];
                dst[2] = palmap[o++];
            }
            src++;
            dst += 3;
        },
        ਚੌੜਾਈ);
        /* *INDENT-ON* */ // clang-format on
        src += srcskip;
        dst += dstskip;
    }
}

ਸਥਿਰ ਖਾਲੀ Blit1to4_ਕੁੰਜੀ(SDL_BlitInfo *info)
{
    ਪੂਰਨ ਚੌੜਾਈ = info->dst_w;
    ਪੂਰਨ ਉਚਾਈ = info->dst_h;
    Uint8 *src = info->src;
    ਪੂਰਨ srcskip = info->src_skip;
    Uint32 *dstp = (Uint32 *)info->dst;
    ਪੂਰਨ dstskip = info->dst_skip;
    Uint32 *palmap = (Uint32 *)info->ਸਾਰਣੀ;
    Uint32 ckey = info->colorkey;

    // Set up some basic variables
    dstskip /= 4;

    ਜਦੋਂ (ਉਚਾਈ--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
        {
            ਜੇ ( *src != ckey ) {
                *dstp = palmap[*src];
            }
            src++;
            dstp++;
        },
        ਚੌੜਾਈ);
        /* *INDENT-ON* */ // clang-format on
        src += srcskip;
        dstp += dstskip;
    }
}

ਸਥਿਰ ਖਾਲੀ Blit1toNAlpha(SDL_BlitInfo *info)
{
    ਪੂਰਨ ਚੌੜਾਈ = info->dst_w;
    ਪੂਰਨ ਉਚਾਈ = info->dst_h;
    Uint8 *src = info->src;
    ਪੂਰਨ srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    ਪੂਰਨ dstskip = info->dst_skip;
    ਅਚਲ SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    ਅਚਲ SDL_Color *srcpal = info->src_pal->colors;
    ਪੂਰਨ dstbpp;
    Uint32 pixelvalue;
    ਬਿਨਾਨਿਸ਼ਾਨੀ sR, sG, sB, sA;
    ਬਿਨਾਨਿਸ਼ਾਨੀ dR, dG, dB, dA;
    ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ A = info->a;

    // Set up some basic variables
    dstbpp = dstfmt->ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel;

    ਜਦੋਂ (ਉਚਾਈ--) {
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
        ਚੌੜਾਈ);
        /* *INDENT-ON* */ // clang-format on
        src += srcskip;
        dst += dstskip;
    }
}

ਸਥਿਰ ਖਾਲੀ Blit1to_NAlpha_ਕੁੰਜੀ(SDL_BlitInfo *info)
{
    ਪੂਰਨ ਚੌੜਾਈ = info->dst_w;
    ਪੂਰਨ ਉਚਾਈ = info->dst_h;
    Uint8 *src = info->src;
    ਪੂਰਨ srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    ਪੂਰਨ dstskip = info->dst_skip;
    ਅਚਲ SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    ਅਚਲ SDL_Color *srcpal = info->src_pal->colors;
    Uint32 ckey = info->colorkey;
    ਪੂਰਨ dstbpp;
    Uint32 pixelvalue;
    ਬਿਨਾਨਿਸ਼ਾਨੀ sR, sG, sB, sA;
    ਬਿਨਾਨਿਸ਼ਾਨੀ dR, dG, dB, dA;
    ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ A = info->a;

    // Set up some basic variables
    dstbpp = dstfmt->ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel;

    ਜਦੋਂ (ਉਚਾਈ--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP(
        {
            ਜੇ ( *src != ckey ) {
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
        ਚੌੜਾਈ);
        /* *INDENT-ON* */ // clang-format on
        src += srcskip;
        dst += dstskip;
    }
}

ਸਥਿਰ ਅਚਲ SDL_BlitFunc one_blit[] = {
    (SDL_BlitFunc)ਨਿਰਾ, Blit1to1, Blit1to2, Blit1to3, Blit1to4
};

ਸਥਿਰ ਅਚਲ SDL_BlitFunc one_blitkey[] = {
    (SDL_BlitFunc)ਨਿਰਾ, Blit1to1_ਕੁੰਜੀ, Blit1to2_ਕੁੰਜੀ, Blit1to3_ਕੁੰਜੀ, Blit1to4_ਕੁੰਜੀ
};

SDL_BlitFunc SDL_CalculateBlit1(SDL_Surface *surface)
{
    ਪੂਰਨ which;

    ਜੇ (SDL_BITSPERPIXEL(surface->map.info.dst_fmt->format) < 8) {
        which = 0;
    } ਨਹੀਂਤਾਂ {
        which = SDL_BYTESPERPIXEL(surface->map.info.dst_fmt->format);
    }

    ਚੋਣ (surface->map.info.flags & ~SDL_COPY_RLE_ਨਕਾਬ) {
    ਹਾਲਤ 0:
        ਜੇ (which < SDL_arraysize(one_blit)) {
            ਵਾਪਸ one_blit[which];
        }
        ਰੋਕੋ;

    ਹਾਲਤ SDL_COPY_COLORKEY:
        ਜੇ (which < SDL_arraysize(one_blitkey)) {
            ਵਾਪਸ one_blitkey[which];
        }
        ਰੋਕੋ;

    ਹਾਲਤ SDL_COPY_COLORKEY | SDL_COPY_BLEND:  // this is not super-robust but handles a specific case we found sdl12-compat.
        ਜੇ (surface->map.info.a == 255) {
            ਜੇ (which < SDL_arraysize(one_blitkey)) {
                ਵਾਪਸ one_blitkey[which];
            }
        } ਨਹੀਂਤਾਂ {
            ਵਾਪਸ which >= 2 ? Blit1to_NAlpha_ਕੁੰਜੀ : (SDL_BlitFunc)ਨਿਰਾ;
        }
        ਰੋਕੋ;

    ਹਾਲਤ SDL_COPY_BLEND:
    ਹਾਲਤ SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
        /* Supporting 8bpp->8bpp alpha is doable but requires lots of
           tables which consume space and takes time to precompute,
           so is better left to the user */
        ਵਾਪਸ which >= 2 ? Blit1toNAlpha : (SDL_BlitFunc)ਨਿਰਾ;

    ਹਾਲਤ SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
        ਵਾਪਸ which >= 2 ? Blit1to_NAlpha_ਕੁੰਜੀ : (SDL_BlitFunc)ਨਿਰਾ;
    }
    ਵਾਪਸ (SDL_BlitFunc)ਨਿਰਾ;
}

#ਜੇ_ਅੰਤ // SDL_HAVE_BLIT_1
