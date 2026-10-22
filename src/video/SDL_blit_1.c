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
#अन्तर्भाव "SDL_internal.h"

#ifdef SDL_HAVE_BLIT_1

#अन्तर्भाव "SDL_surface_c.h"
#अन्तर्भाव "SDL_sysvideo.h"

// Functions to blit from 8-bit surfaces to other surfaces

स्थिर शून्य Blit1to1(SDL_BlitInfo *info)
{
#ifndef USE_DUFFS_LOOP
    पूर्णांक c;
#endif
    पूर्णांक width, height;
    Uint8 *src, *map, *dst;
    पूर्णांक srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = info->table;

    पर्यंत (height--) {
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
#अन्यथा
        साठी (c = width; c; --c) {
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
#जर (SDL_BYTEORDER == SDL_LIL_ENDIAN)
#define HI 1
#define LO 0
#अन्यथा // ( SDL_BYTEORDER == SDL_BIG_ENDIAN )
#define HI 0
#define LO 1
#endif
#endif
स्थिर शून्य Blit1to2(SDL_BlitInfo *info)
{
#ifndef USE_DUFFS_LOOP
    पूर्णांक c;
#endif
    पूर्णांक width, height;
    Uint8 *src, *dst;
    Uint16 *map;
    पूर्णांक srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = (Uint16 *)info->table;

#ifdef USE_DUFFS_LOOP
    पर्यंत (height--) {
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
#अन्यथा
    // Memory align at 4-byte boundary, if necessary
    जर ((दीर्घ)dst & 0x03) {
        // Don't do anything if width is 0
        जर (width == 0) {
            परत;
        }
        --width;

        पर्यंत (height--) {
            // Perform copy alignment
            *(Uint16 *)dst = map[*src++];
            dst += 2;

            // Copy in 4 pixel chunks
            साठी (c = width / 4; c; --c) {
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
            }
            // Get any leftovers
            निवड (width & 3) {
            स्थिती 3:
                *(Uint16 *)dst = map[*src++];
                dst += 2;
                SDL_FALLTHROUGH;
            स्थिती 2:
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
                थांबा;
            स्थिती 1:
                *(Uint16 *)dst = map[*src++];
                dst += 2;
                थांबा;
            }
            src += srcskip;
            dst += dstskip;
        }
    } अन्यथा {
        पर्यंत (height--) {
            // Copy in 4 pixel chunks
            साठी (c = width / 4; c; --c) {
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
            }
            // Get any leftovers
            निवड (width & 3) {
            स्थिती 3:
                *(Uint16 *)dst = map[*src++];
                dst += 2;
                SDL_FALLTHROUGH;
            स्थिती 2:
                *(Uint32 *)dst = (map[src[HI]] << 16) | (map[src[LO]]);
                src += 2;
                dst += 4;
                थांबा;
            स्थिती 1:
                *(Uint16 *)dst = map[*src++];
                dst += 2;
                थांबा;
            }
            src += srcskip;
            dst += dstskip;
        }
    }
#endif // USE_DUFFS_LOOP
}

स्थिर शून्य Blit1to3(SDL_BlitInfo *info)
{
#ifndef USE_DUFFS_LOOP
    पूर्णांक c;
#endif
    पूर्णांक o;
    पूर्णांक width, height;
    Uint8 *src, *map, *dst;
    पूर्णांक srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = info->table;

    पर्यंत (height--) {
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
#अन्यथा
        साठी (c = width; c; --c) {
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

स्थिर शून्य Blit1to4(SDL_BlitInfo *info)
{
#ifndef USE_DUFFS_LOOP
    पूर्णांक c;
#endif
    पूर्णांक width, height;
    Uint8 *src;
    Uint32 *map, *dst;
    पूर्णांक srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = (Uint32 *)info->dst;
    dstskip = info->dst_skip / 4;
    map = (Uint32 *)info->table;

    पर्यंत (height--) {
#ifdef USE_DUFFS_LOOP
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
            *dst++ = map[*src++];
        , width);
        /* *INDENT-ON* */ // clang-format on
#अन्यथा
        साठी (c = width / 4; c; --c) {
            *dst++ = map[*src++];
            *dst++ = map[*src++];
            *dst++ = map[*src++];
            *dst++ = map[*src++];
        }
        निवड (width & 3) {
        स्थिती 3:
            *dst++ = map[*src++];
            SDL_FALLTHROUGH;
        स्थिती 2:
            *dst++ = map[*src++];
            SDL_FALLTHROUGH;
        स्थिती 1:
            *dst++ = map[*src++];
        }
#endif // USE_DUFFS_LOOP
        src += srcskip;
        dst += dstskip;
    }
}

स्थिर शून्य Blit1to1_किल्ली(SDL_BlitInfo *info)
{
    पूर्णांक width = info->dst_w;
    पूर्णांक height = info->dst_h;
    Uint8 *src = info->src;
    पूर्णांक srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    पूर्णांक dstskip = info->dst_skip;
    Uint8 *palmap = info->table;
    Uint32 ckey = info->colorkey;

    जर (palmap) {
        पर्यंत (height--) {
            /* *INDENT-OFF* */ // clang-format off
            DUFFS_LOOP_TRIVIAL(
            {
                जर ( *src != ckey ) {
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
    } अन्यथा {
        पर्यंत (height--) {
            /* *INDENT-OFF* */ // clang-format off
            DUFFS_LOOP_TRIVIAL(
            {
                जर ( *src != ckey ) {
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

स्थिर शून्य Blit1to2_किल्ली(SDL_BlitInfo *info)
{
    पूर्णांक width = info->dst_w;
    पूर्णांक height = info->dst_h;
    Uint8 *src = info->src;
    पूर्णांक srcskip = info->src_skip;
    Uint16 *dstp = (Uint16 *)info->dst;
    पूर्णांक dstskip = info->dst_skip;
    Uint16 *palmap = (Uint16 *)info->table;
    Uint32 ckey = info->colorkey;

    // Set up some basic variables
    dstskip /= 2;

    पर्यंत (height--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
        {
            जर ( *src != ckey ) {
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

स्थिर शून्य Blit1to3_किल्ली(SDL_BlitInfo *info)
{
    पूर्णांक width = info->dst_w;
    पूर्णांक height = info->dst_h;
    Uint8 *src = info->src;
    पूर्णांक srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    पूर्णांक dstskip = info->dst_skip;
    Uint8 *palmap = info->table;
    Uint32 ckey = info->colorkey;
    पूर्णांक o;

    पर्यंत (height--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP(
        {
            जर ( *src != ckey ) {
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

स्थिर शून्य Blit1to4_किल्ली(SDL_BlitInfo *info)
{
    पूर्णांक width = info->dst_w;
    पूर्णांक height = info->dst_h;
    Uint8 *src = info->src;
    पूर्णांक srcskip = info->src_skip;
    Uint32 *dstp = (Uint32 *)info->dst;
    पूर्णांक dstskip = info->dst_skip;
    Uint32 *palmap = (Uint32 *)info->table;
    Uint32 ckey = info->colorkey;

    // Set up some basic variables
    dstskip /= 4;

    पर्यंत (height--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP_TRIVIAL(
        {
            जर ( *src != ckey ) {
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

स्थिर शून्य Blit1toNAlpha(SDL_BlitInfo *info)
{
    पूर्णांक width = info->dst_w;
    पूर्णांक height = info->dst_h;
    Uint8 *src = info->src;
    पूर्णांक srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    पूर्णांक dstskip = info->dst_skip;
    स्थिरांक SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    स्थिरांक SDL_Color *srcpal = info->src_pal->colors;
    पूर्णांक dstbpp;
    Uint32 pixelvalue;
    अचिन्हित sR, sG, sB, sA;
    अचिन्हित dR, dG, dB, dA;
    स्थिरांक अचिन्हित A = info->a;

    // Set up some basic variables
    dstbpp = dstfmt->bytes_per_pixel;

    पर्यंत (height--) {
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

स्थिर शून्य Blit1to_NAlpha_किल्ली(SDL_BlitInfo *info)
{
    पूर्णांक width = info->dst_w;
    पूर्णांक height = info->dst_h;
    Uint8 *src = info->src;
    पूर्णांक srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    पूर्णांक dstskip = info->dst_skip;
    स्थिरांक SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    स्थिरांक SDL_Color *srcpal = info->src_pal->colors;
    Uint32 ckey = info->colorkey;
    पूर्णांक dstbpp;
    Uint32 pixelvalue;
    अचिन्हित sR, sG, sB, sA;
    अचिन्हित dR, dG, dB, dA;
    स्थिरांक अचिन्हित A = info->a;

    // Set up some basic variables
    dstbpp = dstfmt->bytes_per_pixel;

    पर्यंत (height--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP(
        {
            जर ( *src != ckey ) {
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

स्थिर स्थिरांक SDL_BlitFunc one_blit[] = {
    (SDL_BlitFunc)रिक्त, Blit1to1, Blit1to2, Blit1to3, Blit1to4
};

स्थिर स्थिरांक SDL_BlitFunc one_blitkey[] = {
    (SDL_BlitFunc)रिक्त, Blit1to1_किल्ली, Blit1to2_किल्ली, Blit1to3_किल्ली, Blit1to4_किल्ली
};

SDL_BlitFunc SDL_CalculateBlit1(SDL_Surface *surface)
{
    पूर्णांक which;

    जर (SDL_BITSPERPIXEL(surface->map.info.dst_fmt->format) < 8) {
        which = 0;
    } अन्यथा {
        which = SDL_BYTESPERPIXEL(surface->map.info.dst_fmt->format);
    }

    निवड (surface->map.info.flags & ~SDL_COPY_RLE_MASK) {
    स्थिती 0:
        जर (which < SDL_arraysize(one_blit)) {
            परत one_blit[which];
        }
        थांबा;

    स्थिती SDL_COPY_COLORKEY:
        जर (which < SDL_arraysize(one_blitkey)) {
            परत one_blitkey[which];
        }
        थांबा;

    स्थिती SDL_COPY_COLORKEY | SDL_COPY_BLEND:  // this is not super-robust but handles a specific case we found sdl12-compat.
        जर (surface->map.info.a == 255) {
            जर (which < SDL_arraysize(one_blitkey)) {
                परत one_blitkey[which];
            }
        } अन्यथा {
            परत which >= 2 ? Blit1to_NAlpha_किल्ली : (SDL_BlitFunc)रिक्त;
        }
        थांबा;

    स्थिती SDL_COPY_BLEND:
    स्थिती SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
        /* Supporting 8bpp->8bpp alpha is doable but requires lots of
           tables which consume space and takes time to precompute,
           so is better left to the user */
        परत which >= 2 ? Blit1toNAlpha : (SDL_BlitFunc)रिक्त;

    स्थिती SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
        परत which >= 2 ? Blit1to_NAlpha_किल्ली : (SDL_BlitFunc)रिक्त;
    }
    परत (SDL_BlitFunc)रिक्त;
}

#endif // SDL_HAVE_BLIT_1
