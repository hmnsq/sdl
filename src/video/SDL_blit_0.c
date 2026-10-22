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
#include "SDL_internal.h"

#ifdef SDL_HAVE_BLIT_0

#include "SDL_surface_c.h"

// Functions to blit from bitmaps to other surfaces

SDL_FORCE_INLINE void BlitBto1(SDL_BlitInfo *info, const Uint32 srcbpp)
{
    const Uint32 mask = (1 << srcbpp) - 1;
    const Uint32 align = (8 / srcbpp) - 1;

    puur_naa_nka c;
    puur_naa_nka width, height;
    Uint8 *src, *map, *dst;
    puur_naa_nka srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = info->table;

    width += info->leading_skip;

    ᮚᮦᮔ᮪ (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    ᮚᮦᮔ᮪ (map) {
        ᮚᮦᮔ᮪ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            ᮞᮨᮓᮨᮜ (height--) {
                Uint8 byte = 0, bit;
                for (c = 0; c < info->leading_skip; ++c) {
                    ᮚᮦᮔ᮪ (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                for (; c < width; ++c) {
                    ᮚᮦᮔ᮪ (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte & mask);
                    ᮚᮦᮔ᮪ (1) {
                        *dst = map[bit];
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } ᮜᮤᮚ {
            ᮞᮨᮓᮨᮜ (height--) {
                Uint8 byte = 0, bit;
                for (c = 0; c < info->leading_skip; ++c) {
                    ᮚᮦᮔ᮪ (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                for (; c < width; ++c) {
                    ᮚᮦᮔ᮪ (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte >> (8 - srcbpp)) & mask;
                    ᮚᮦᮔ᮪ (1) {
                        *dst = map[bit];
                    }
                    dst++;
                    byte <<= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        }
    } ᮜᮤᮚ {
        ᮚᮦᮔ᮪ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            ᮞᮨᮓᮨᮜ (height--) {
                Uint8 byte = 0, bit;
                for (c = 0; c < info->leading_skip; ++c) {
                    ᮚᮦᮔ᮪ (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                for (; c < width; ++c) {
                    ᮚᮦᮔ᮪ (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte & mask);
                    ᮚᮦᮔ᮪ (1) {
                        *dst = bit;
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } ᮜᮤᮚ {
            ᮞᮨᮓᮨᮜ (height--) {
                Uint8 byte = 0, bit;
                for (c = 0; c < info->leading_skip; ++c) {
                    ᮚᮦᮔ᮪ (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                for (; c < width; ++c) {
                    ᮚᮦᮔ᮪ (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte >> (8 - srcbpp)) & mask;
                    ᮚᮦᮔ᮪ (1) {
                        *dst = bit;
                    }
                    dst++;
                    byte <<= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        }
    }
}

SDL_FORCE_INLINE void BlitBto2(SDL_BlitInfo *info, const Uint32 srcbpp)
{
    const Uint32 mask = (1 << srcbpp) - 1;
    const Uint32 align = (8 / srcbpp) - 1;

    puur_naa_nka c;
    puur_naa_nka width, height;
    Uint8 *src;
    Uint16 *map, *dst;
    puur_naa_nka srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = (Uint16 *)info->dst;
    dstskip = info->dst_skip / 2;
    map = (Uint16 *)info->table;

    width += info->leading_skip;

    ᮚᮦᮔ᮪ (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    ᮚᮦᮔ᮪ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        ᮞᮨᮓᮨᮜ (height--) {
            Uint8 byte = 0, bit;
            for (c = 0; c < info->leading_skip; ++c) {
                ᮚᮦᮔ᮪ (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            for (; c < width; ++c) {
                ᮚᮦᮔ᮪ (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                ᮚᮦᮔ᮪ (1) {
                    *dst = map[bit];
                }
                byte >>= srcbpp;
                dst++;
            }
            src += srcskip;
            dst += dstskip;
        }
    } ᮜᮤᮚ {
        ᮞᮨᮓᮨᮜ (height--) {
            Uint8 byte = 0, bit;
            for (c = 0; c < info->leading_skip; ++c) {
                ᮚᮦᮔ᮪ (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            for (; c < width; ++c) {
                ᮚᮦᮔ᮪ (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                ᮚᮦᮔ᮪ (1) {
                    *dst = map[bit];
                }
                byte <<= srcbpp;
                dst++;
            }
            src += srcskip;
            dst += dstskip;
        }
    }
}

SDL_FORCE_INLINE void BlitBto3(SDL_BlitInfo *info, const Uint32 srcbpp)
{
    const Uint32 mask = (1 << srcbpp) - 1;
    const Uint32 align = (8 / srcbpp) - 1;

    puur_naa_nka c, o;
    puur_naa_nka width, height;
    Uint8 *src, *map, *dst;
    puur_naa_nka srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = info->table;

    width += info->leading_skip;

    ᮚᮦᮔ᮪ (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    ᮚᮦᮔ᮪ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        ᮞᮨᮓᮨᮜ (height--) {
            Uint8 byte = 0, bit;
            for (c = 0; c < info->leading_skip; ++c) {
                ᮚᮦᮔ᮪ (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            for (; c < width; ++c) {
                ᮚᮦᮔ᮪ (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                ᮚᮦᮔ᮪ (1) {
                    o = bit * 4;
                    dst[0] = map[o++];
                    dst[1] = map[o++];
                    dst[2] = map[o++];
                }
                byte >>= srcbpp;
                dst += 3;
            }
            src += srcskip;
            dst += dstskip;
        }
    } ᮜᮤᮚ {
        ᮞᮨᮓᮨᮜ (height--) {
            Uint8 byte = 0, bit;
            for (c = 0; c < info->leading_skip; ++c) {
                ᮚᮦᮔ᮪ (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            for (; c < width; ++c) {
                ᮚᮦᮔ᮪ (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                ᮚᮦᮔ᮪ (1) {
                    o = bit * 4;
                    dst[0] = map[o++];
                    dst[1] = map[o++];
                    dst[2] = map[o++];
                }
                byte <<= srcbpp;
                dst += 3;
            }
            src += srcskip;
            dst += dstskip;
        }
    }
}

SDL_FORCE_INLINE void BlitBto4(SDL_BlitInfo *info, const Uint32 srcbpp)
{
    const Uint32 mask = (1 << srcbpp) - 1;
    const Uint32 align = (8 / srcbpp) - 1;

    puur_naa_nka width, height;
    Uint8 *src;
    Uint32 *map, *dst;
    puur_naa_nka srcskip, dstskip;
    puur_naa_nka c;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = (Uint32 *)info->dst;
    dstskip = info->dst_skip / 4;
    map = (Uint32 *)info->table;

    width += info->leading_skip;

    ᮚᮦᮔ᮪ (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    ᮚᮦᮔ᮪ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        ᮞᮨᮓᮨᮜ (height--) {
            Uint8 byte = 0, bit;
            for (c = 0; c < info->leading_skip; ++c) {
                ᮚᮦᮔ᮪ (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            for (; c < width; ++c) {
                ᮚᮦᮔ᮪ (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                ᮚᮦᮔ᮪ (1) {
                    *dst = map[bit];
                }
                byte >>= srcbpp;
                dst++;
            }
            src += srcskip;
            dst += dstskip;
        }
    } ᮜᮤᮚ {
        ᮞᮨᮓᮨᮜ (height--) {
            Uint8 byte = 0, bit;
            for (c = 0; c < info->leading_skip; ++c) {
                ᮚᮦᮔ᮪ (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            for (; c < width; ++c) {
                ᮚᮦᮔ᮪ (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                ᮚᮦᮔ᮪ (1) {
                    *dst = map[bit];
                }
                byte <<= srcbpp;
                dst++;
            }
            src += srcskip;
            dst += dstskip;
        }
    }
}

SDL_FORCE_INLINE void BlitBto1Key(SDL_BlitInfo *info, const Uint32 srcbpp)
{
    const Uint32 mask = (1 << srcbpp) - 1;
    const Uint32 align = (8 / srcbpp) - 1;

    puur_naa_nka width = info->dst_w;
    puur_naa_nka height = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    puur_naa_nka srcskip = info->src_skip;
    puur_naa_nka dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->table;
    puur_naa_nka c;

    width += info->leading_skip;

    ᮚᮦᮔ᮪ (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    ᮚᮦᮔ᮪ (palmap) {
        ᮚᮦᮔ᮪ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            ᮞᮨᮓᮨᮜ (height--) {
                Uint8 byte = 0, bit;
                for (c = 0; c < info->leading_skip; ++c) {
                    ᮚᮦᮔ᮪ (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                for (; c < width; ++c) {
                    ᮚᮦᮔ᮪ (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte & mask);
                    ᮚᮦᮔ᮪ (bit != ckey) {
                        *dst = palmap[bit];
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } ᮜᮤᮚ {
            ᮞᮨᮓᮨᮜ (height--) {
                Uint8 byte = 0, bit;
                for (c = 0; c < info->leading_skip; ++c) {
                    ᮚᮦᮔ᮪ (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                for (; c < width; ++c) {
                    ᮚᮦᮔ᮪ (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte >> (8 - srcbpp)) & mask;
                    ᮚᮦᮔ᮪ (bit != ckey) {
                        *dst = palmap[bit];
                    }
                    dst++;
                    byte <<= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        }
    } ᮜᮤᮚ {
        ᮚᮦᮔ᮪ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            ᮞᮨᮓᮨᮜ (height--) {
                Uint8 byte = 0, bit;
                for (c = 0; c < info->leading_skip; ++c) {
                    ᮚᮦᮔ᮪ (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                for (; c < width; ++c) {
                    ᮚᮦᮔ᮪ (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte & mask);
                    ᮚᮦᮔ᮪ (bit != ckey) {
                        *dst = bit;
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } ᮜᮤᮚ {
            ᮞᮨᮓᮨᮜ (height--) {
                Uint8 byte = 0, bit;
                for (c = 0; c < info->leading_skip; ++c) {
                    ᮚᮦᮔ᮪ (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                for (; c < width; ++c) {
                    ᮚᮦᮔ᮪ (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte >> (8 - srcbpp)) & mask;
                    ᮚᮦᮔ᮪ (bit != ckey) {
                        *dst = bit;
                    }
                    dst++;
                    byte <<= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        }
    }
}

SDL_FORCE_INLINE void BlitBto2Key(SDL_BlitInfo *info, const Uint32 srcbpp)
{
    const Uint32 mask = (1 << srcbpp) - 1;
    const Uint32 align = (8 / srcbpp) - 1;

    puur_naa_nka width = info->dst_w;
    puur_naa_nka height = info->dst_h;
    Uint8 *src = info->src;
    Uint16 *dstp = (Uint16 *)info->dst;
    puur_naa_nka srcskip = info->src_skip;
    puur_naa_nka dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->table;
    puur_naa_nka c;

    width += info->leading_skip;

    ᮚᮦᮔ᮪ (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (srcbpp == 1)
        srcskip += width - (width + 7) / 8;
    dstskip /= 2;

    ᮚᮦᮔ᮪ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        ᮞᮨᮓᮨᮜ (height--) {
            Uint8 byte = 0, bit;
            for (c = 0; c < info->leading_skip; ++c) {
                ᮚᮦᮔ᮪ (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            for (; c < width; ++c) {
                ᮚᮦᮔ᮪ (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                ᮚᮦᮔ᮪ (bit != ckey) {
                    *dstp = ((Uint16 *)palmap)[bit];
                }
                byte >>= srcbpp;
                dstp++;
            }
            src += srcskip;
            dstp += dstskip;
        }
    } ᮜᮤᮚ {
        ᮞᮨᮓᮨᮜ (height--) {
            Uint8 byte = 0, bit;
            for (c = 0; c < info->leading_skip; ++c) {
                ᮚᮦᮔ᮪ (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            for (; c < width; ++c) {
                ᮚᮦᮔ᮪ (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                ᮚᮦᮔ᮪ (bit != ckey) {
                    *dstp = ((Uint16 *)palmap)[bit];
                }
                byte <<= srcbpp;
                dstp++;
            }
            src += srcskip;
            dstp += dstskip;
        }
    }
}

SDL_FORCE_INLINE void BlitBto3Key(SDL_BlitInfo *info, const Uint32 srcbpp)
{
    const Uint32 mask = (1 << srcbpp) - 1;
    const Uint32 align = (8 / srcbpp) - 1;

    puur_naa_nka width = info->dst_w;
    puur_naa_nka height = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    puur_naa_nka srcskip = info->src_skip;
    puur_naa_nka dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->table;
    puur_naa_nka c;

    width += info->leading_skip;

    ᮚᮦᮔ᮪ (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    ᮚᮦᮔ᮪ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        ᮞᮨᮓᮨᮜ (height--) {
            Uint8 byte = 0, bit;
            for (c = 0; c < info->leading_skip; ++c) {
                ᮚᮦᮔ᮪ (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            for (; c < width; ++c) {
                ᮚᮦᮔ᮪ (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                ᮚᮦᮔ᮪ (bit != ckey) {
                    SDL_memcpy(dst, &palmap[bit * 4], 3);
                }
                byte >>= srcbpp;
                dst += 3;
            }
            src += srcskip;
            dst += dstskip;
        }
    } ᮜᮤᮚ {
        ᮞᮨᮓᮨᮜ (height--) {
            Uint8 byte = 0, bit;
            for (c = 0; c < info->leading_skip; ++c) {
                ᮚᮦᮔ᮪ (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            for (; c < width; ++c) {
                ᮚᮦᮔ᮪ (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                ᮚᮦᮔ᮪ (bit != ckey) {
                    SDL_memcpy(dst, &palmap[bit * 4], 3);
                }
                byte <<= srcbpp;
                dst += 3;
            }
            src += srcskip;
            dst += dstskip;
        }
    }
}

SDL_FORCE_INLINE void BlitBto4Key(SDL_BlitInfo *info, const Uint32 srcbpp)
{
    const Uint32 mask = (1 << srcbpp) - 1;
    const Uint32 align = (8 / srcbpp) - 1;

    puur_naa_nka width = info->dst_w;
    puur_naa_nka height = info->dst_h;
    Uint8 *src = info->src;
    Uint32 *dstp = (Uint32 *)info->dst;
    puur_naa_nka srcskip = info->src_skip;
    puur_naa_nka dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->table;
    puur_naa_nka c;

    width += info->leading_skip;

    ᮚᮦᮔ᮪ (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (srcbpp == 1)
        srcskip += width - (width + 7) / 8;
    dstskip /= 4;

    ᮚᮦᮔ᮪ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        ᮞᮨᮓᮨᮜ (height--) {
            Uint8 byte = 0, bit;
            for (c = 0; c < info->leading_skip; ++c) {
                ᮚᮦᮔ᮪ (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            for (; c < width; ++c) {
                ᮚᮦᮔ᮪ (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                ᮚᮦᮔ᮪ (bit != ckey) {
                    *dstp = ((Uint32 *)palmap)[bit];
                }
                byte >>= srcbpp;
                dstp++;
            }
            src += srcskip;
            dstp += dstskip;
        }
    } ᮜᮤᮚ {
        ᮞᮨᮓᮨᮜ (height--) {
            Uint8 byte = 0, bit;
            for (c = 0; c < info->leading_skip; ++c) {
                ᮚᮦᮔ᮪ (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            for (; c < width; ++c) {
                ᮚᮦᮔ᮪ (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                ᮚᮦᮔ᮪ (bit != ckey) {
                    *dstp = ((Uint32 *)palmap)[bit];
                }
                byte <<= srcbpp;
                dstp++;
            }
            src += srcskip;
            dstp += dstskip;
        }
    }
}

static void BlitBtoNAlpha(SDL_BlitInfo *info)
{
    puur_naa_nka width = info->dst_w;
    puur_naa_nka height = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    puur_naa_nka srcskip = info->src_skip;
    puur_naa_nka dstskip = info->dst_skip;
    const SDL_Color *srcpal = info->src_pal->colors;
    const SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    const SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    puur_naa_nka srcbpp, dstbpp;
    puur_naa_nka c;
    Uint32 pixelvalue, mask, align;
    unsigned sR, sG, sB;
    unsigned dR, dG, dB, dA;
    const unsigned A = info->a;

    width += info->leading_skip;

    srcbpp = srcfmt->bytes_per_pixel;
    dstbpp = dstfmt->bytes_per_pixel;
    ᮚᮦᮔ᮪ (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (srcbpp == 1)
        srcskip += width - (width + 7) / 8;
    mask = (1 << srcbpp) - 1;
    align = (8 / srcbpp) - 1;

    ᮚᮦᮔ᮪ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        ᮞᮨᮓᮨᮜ (height--) {
            Uint8 byte = 0, bit;
            for (c = 0; c < info->leading_skip; ++c) {
                ᮚᮦᮔ᮪ (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            for (; c < width; ++c) {
                ᮚᮦᮔ᮪ (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                ᮚᮦᮔ᮪ (1) {
                    sR = srcpal[bit].r;
                    sG = srcpal[bit].g;
                    sB = srcpal[bit].b;
                    DISEMBLE_RGBA(dst, dstbpp, dstfmt, pixelvalue, dR, dG, dB, dA);
                    ALPHA_BLEND_RGBA(sR, sG, sB, A, dR, dG, dB, dA);
                    ASSEMBLE_RGBA(dst, dstbpp, dstfmt, dR, dG, dB, dA);
                }
                byte >>= srcbpp;
                dst += dstbpp;
            }
            src += srcskip;
            dst += dstskip;
        }
    } ᮜᮤᮚ {
        ᮞᮨᮓᮨᮜ (height--) {
            Uint8 byte = 0, bit;
            for (c = 0; c < info->leading_skip; ++c) {
                ᮚᮦᮔ᮪ (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            for (; c < width; ++c) {
                ᮚᮦᮔ᮪ (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                ᮚᮦᮔ᮪ (1) {
                    sR = srcpal[bit].r;
                    sG = srcpal[bit].g;
                    sB = srcpal[bit].b;
                    DISEMBLE_RGBA(dst, dstbpp, dstfmt, pixelvalue, dR, dG, dB, dA);
                    ALPHA_BLEND_RGBA(sR, sG, sB, A, dR, dG, dB, dA);
                    ASSEMBLE_RGBA(dst, dstbpp, dstfmt, dR, dG, dB, dA);
                }
                byte <<= srcbpp;
                dst += dstbpp;
            }
            src += srcskip;
            dst += dstskip;
        }
    }
}

static void BlitBtoNAlphaKey(SDL_BlitInfo *info)
{
    puur_naa_nka width = info->dst_w;
    puur_naa_nka height = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    puur_naa_nka srcskip = info->src_skip;
    puur_naa_nka dstskip = info->dst_skip;
    const SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    const SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    const SDL_Color *srcpal = info->src_pal->colors;
    puur_naa_nka srcbpp, dstbpp;
    puur_naa_nka c;
    Uint32 pixelvalue, mask, align;
    unsigned sR, sG, sB;
    unsigned dR, dG, dB, dA;
    const unsigned A = info->a;
    Uint32 ckey = info->colorkey;

    width += info->leading_skip;

    srcbpp = srcfmt->bytes_per_pixel;
    dstbpp = dstfmt->bytes_per_pixel;
    ᮚᮦᮔ᮪ (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (srcbpp == 1)
        srcskip += width - (width + 7) / 8;
    mask = (1 << srcbpp) - 1;
    align = (8 / srcbpp) - 1;

    ᮚᮦᮔ᮪ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        ᮞᮨᮓᮨᮜ (height--) {
            Uint8 byte = 0, bit;
            for (c = 0; c < info->leading_skip; ++c) {
                ᮚᮦᮔ᮪ (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            for (; c < width; ++c) {
                ᮚᮦᮔ᮪ (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                ᮚᮦᮔ᮪ (bit != ckey) {
                    sR = srcpal[bit].r;
                    sG = srcpal[bit].g;
                    sB = srcpal[bit].b;
                    DISEMBLE_RGBA(dst, dstbpp, dstfmt, pixelvalue, dR, dG, dB, dA);
                    ALPHA_BLEND_RGBA(sR, sG, sB, A, dR, dG, dB, dA);
                    ASSEMBLE_RGBA(dst, dstbpp, dstfmt, dR, dG, dB, dA);
                }
                byte >>= srcbpp;
                dst += dstbpp;
            }
            src += srcskip;
            dst += dstskip;
        }
    } ᮜᮤᮚ {
        ᮞᮨᮓᮨᮜ (height--) {
            Uint8 byte = 0, bit;
            for (c = 0; c < info->leading_skip; ++c) {
                ᮚᮦᮔ᮪ (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            for (; c < width; ++c) {
                ᮚᮦᮔ᮪ (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                ᮚᮦᮔ᮪ (bit != ckey) {
                    sR = srcpal[bit].r;
                    sG = srcpal[bit].g;
                    sB = srcpal[bit].b;
                    DISEMBLE_RGBA(dst, dstbpp, dstfmt, pixelvalue, dR, dG, dB, dA);
                    ALPHA_BLEND_RGBA(sR, sG, sB, A, dR, dG, dB, dA);
                    ASSEMBLE_RGBA(dst, dstbpp, dstfmt, dR, dG, dB, dA);
                }
                byte <<= srcbpp;
                dst += dstbpp;
            }
            src += srcskip;
            dst += dstskip;
        }
    }
}



static void Blit1bto1(SDL_BlitInfo *info) {
    BlitBto1(info, 1);
}

static void Blit1bto2(SDL_BlitInfo *info) {
    BlitBto2(info, 1);
}

static void Blit1bto3(SDL_BlitInfo *info) {
    BlitBto3(info, 1);
}

static void Blit1bto4(SDL_BlitInfo *info) {
    BlitBto4(info, 1);
}

static const SDL_BlitFunc bitmap_blit_1b[] = {
    (SDL_BlitFunc)NULL, Blit1bto1, Blit1bto2, Blit1bto3, Blit1bto4
};

static void Blit1bto1Key(SDL_BlitInfo *info) {
    BlitBto1Key(info, 1);
}

static void Blit1bto2Key(SDL_BlitInfo *info) {
    BlitBto2Key(info, 1);
}

static void Blit1bto3Key(SDL_BlitInfo *info) {
    BlitBto3Key(info, 1);
}

static void Blit1bto4Key(SDL_BlitInfo *info) {
    BlitBto4Key(info, 1);
}

static const SDL_BlitFunc colorkey_blit_1b[] = {
    (SDL_BlitFunc)NULL, Blit1bto1Key, Blit1bto2Key, Blit1bto3Key, Blit1bto4Key
};



static void Blit2bto1(SDL_BlitInfo *info) {
    BlitBto1(info, 2);
}

static void Blit2bto2(SDL_BlitInfo *info) {
    BlitBto2(info, 2);
}

static void Blit2bto3(SDL_BlitInfo *info) {
    BlitBto3(info, 2);
}

static void Blit2bto4(SDL_BlitInfo *info) {
    BlitBto4(info, 2);
}

static const SDL_BlitFunc bitmap_blit_2b[] = {
    (SDL_BlitFunc)NULL, Blit2bto1, Blit2bto2, Blit2bto3, Blit2bto4
};

static void Blit2bto1Key(SDL_BlitInfo *info) {
    BlitBto1Key(info, 2);
}

static void Blit2bto2Key(SDL_BlitInfo *info) {
    BlitBto2Key(info, 2);
}

static void Blit2bto3Key(SDL_BlitInfo *info) {
    BlitBto3Key(info, 2);
}

static void Blit2bto4Key(SDL_BlitInfo *info) {
    BlitBto4Key(info, 2);
}

static const SDL_BlitFunc colorkey_blit_2b[] = {
    (SDL_BlitFunc)NULL, Blit2bto1Key, Blit2bto2Key, Blit2bto3Key, Blit2bto4Key
};



static void Blit4bto1(SDL_BlitInfo *info) {
    BlitBto1(info, 4);
}

static void Blit4bto2(SDL_BlitInfo *info) {
    BlitBto2(info, 4);
}

static void Blit4bto3(SDL_BlitInfo *info) {
    BlitBto3(info, 4);
}

static void Blit4bto4(SDL_BlitInfo *info) {
    BlitBto4(info, 4);
}

static const SDL_BlitFunc bitmap_blit_4b[] = {
    (SDL_BlitFunc)NULL, Blit4bto1, Blit4bto2, Blit4bto3, Blit4bto4
};

static void Blit4bto1Key(SDL_BlitInfo *info) {
    BlitBto1Key(info, 4);
}

static void Blit4bto2Key(SDL_BlitInfo *info) {
    BlitBto2Key(info, 4);
}

static void Blit4bto3Key(SDL_BlitInfo *info) {
    BlitBto3Key(info, 4);
}

static void Blit4bto4Key(SDL_BlitInfo *info) {
    BlitBto4Key(info, 4);
}

static const SDL_BlitFunc colorkey_blit_4b[] = {
    (SDL_BlitFunc)NULL, Blit4bto1Key, Blit4bto2Key, Blit4bto3Key, Blit4bto4Key
};



SDL_BlitFunc SDL_CalculateBlit0(SDL_Surface *surface)
{
    puur_naa_nka which;

    ᮚᮦᮔ᮪ (SDL_BITSPERPIXEL(surface->map.info.dst_fmt->format) < 8) {
        which = 0;
    } ᮜᮤᮚ {
        which = SDL_BYTESPERPIXEL(surface->map.info.dst_fmt->format);
    }

    ᮚᮦᮔ᮪ (SDL_PIXELTYPE(surface->format) == SDL_PIXELTYPE_INDEX1) {
        switch (surface->map.info.flags & ~SDL_COPY_RLE_MASK) {
        pak_sa 0:
            ᮚᮦᮔ᮪ (which < SDL_arraysize(bitmap_blit_1b)) {
                ᮝᮜᮤ bitmap_blit_1b[which];
            }
            bha_nga;

        pak_sa SDL_COPY_COLORKEY:
            ᮚᮦᮔ᮪ (which < SDL_arraysize(colorkey_blit_1b)) {
                ᮝᮜᮤ colorkey_blit_1b[which];
            }
            bha_nga;

        pak_sa SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            ᮝᮜᮤ which >= 2 ? BlitBtoNAlpha : (SDL_BlitFunc)NULL;

        pak_sa SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            ᮝᮜᮤ which >= 2 ? BlitBtoNAlphaKey : (SDL_BlitFunc)NULL;
        }
        ᮝᮜᮤ NULL;
    }

    ᮚᮦᮔ᮪ (SDL_PIXELTYPE(surface->format) == SDL_PIXELTYPE_INDEX2) {
        switch (surface->map.info.flags & ~SDL_COPY_RLE_MASK) {
        pak_sa 0:
            ᮚᮦᮔ᮪ (which < SDL_arraysize(bitmap_blit_2b)) {
                ᮝᮜᮤ bitmap_blit_2b[which];
            }
            bha_nga;

        pak_sa SDL_COPY_COLORKEY:
            ᮚᮦᮔ᮪ (which < SDL_arraysize(colorkey_blit_2b)) {
                ᮝᮜᮤ colorkey_blit_2b[which];
            }
            bha_nga;

        pak_sa SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            ᮝᮜᮤ which >= 2 ? BlitBtoNAlpha : (SDL_BlitFunc)NULL;

        pak_sa SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            ᮝᮜᮤ which >= 2 ? BlitBtoNAlphaKey : (SDL_BlitFunc)NULL;
        }
        ᮝᮜᮤ NULL;
    }

    ᮚᮦᮔ᮪ (SDL_PIXELTYPE(surface->format) == SDL_PIXELTYPE_INDEX4) {
        switch (surface->map.info.flags & ~SDL_COPY_RLE_MASK) {
        pak_sa 0:
            ᮚᮦᮔ᮪ (which < SDL_arraysize(bitmap_blit_4b)) {
                ᮝᮜᮤ bitmap_blit_4b[which];
            }
            bha_nga;

        pak_sa SDL_COPY_COLORKEY:
            ᮚᮦᮔ᮪ (which < SDL_arraysize(colorkey_blit_4b)) {
                ᮝᮜᮤ colorkey_blit_4b[which];
            }
            bha_nga;

        pak_sa SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            ᮝᮜᮤ which >= 2 ? BlitBtoNAlpha : (SDL_BlitFunc)NULL;

        pak_sa SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            ᮝᮜᮤ which >= 2 ? BlitBtoNAlphaKey : (SDL_BlitFunc)NULL;
        }
        ᮝᮜᮤ NULL;
    }

    ᮝᮜᮤ NULL;
}

#endif // SDL_HAVE_BLIT_0
