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

#ifdef SDL_HAVE_BLIT_0

#അന്തര്ഭാവ "SDL_surface_c.h"

// Functions to blit from bitmaps to other surfaces

SDL_FORCE_INLINE ശൂന്യം BlitBto1(SDL_BlitInfo *info, സ്ഥിരം Uint32 srcbpp)
{
    സ്ഥിരം Uint32 mask = (1 << srcbpp) - 1;
    സ്ഥിരം Uint32 align = (8 / srcbpp) - 1;

    പൂർണ്ണസംഖ്യ c;
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

    width += info->leading_skip;

    എങ്കിൽ (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    അല്ലെങ്കിൽ എങ്കിൽ (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    അല്ലെങ്കിൽ എങ്കിൽ (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    എങ്കിൽ (map) {
        എങ്കിൽ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            ആകുമ്പോൾ (height--) {
                Uint8 byte = 0, bit;
                വേണ്ടി (c = 0; c < info->leading_skip; ++c) {
                    എങ്കിൽ (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                വേണ്ടി (; c < width; ++c) {
                    എങ്കിൽ (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte & mask);
                    എങ്കിൽ (1) {
                        *dst = map[bit];
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } അല്ലെങ്കിൽ {
            ആകുമ്പോൾ (height--) {
                Uint8 byte = 0, bit;
                വേണ്ടി (c = 0; c < info->leading_skip; ++c) {
                    എങ്കിൽ (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                വേണ്ടി (; c < width; ++c) {
                    എങ്കിൽ (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte >> (8 - srcbpp)) & mask;
                    എങ്കിൽ (1) {
                        *dst = map[bit];
                    }
                    dst++;
                    byte <<= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        }
    } അല്ലെങ്കിൽ {
        എങ്കിൽ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            ആകുമ്പോൾ (height--) {
                Uint8 byte = 0, bit;
                വേണ്ടി (c = 0; c < info->leading_skip; ++c) {
                    എങ്കിൽ (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                വേണ്ടി (; c < width; ++c) {
                    എങ്കിൽ (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte & mask);
                    എങ്കിൽ (1) {
                        *dst = bit;
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } അല്ലെങ്കിൽ {
            ആകുമ്പോൾ (height--) {
                Uint8 byte = 0, bit;
                വേണ്ടി (c = 0; c < info->leading_skip; ++c) {
                    എങ്കിൽ (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                വേണ്ടി (; c < width; ++c) {
                    എങ്കിൽ (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte >> (8 - srcbpp)) & mask;
                    എങ്കിൽ (1) {
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

SDL_FORCE_INLINE ശൂന്യം BlitBto2(SDL_BlitInfo *info, സ്ഥിരം Uint32 srcbpp)
{
    സ്ഥിരം Uint32 mask = (1 << srcbpp) - 1;
    സ്ഥിരം Uint32 align = (8 / srcbpp) - 1;

    പൂർണ്ണസംഖ്യ c;
    പൂർണ്ണസംഖ്യ width, height;
    Uint8 *src;
    Uint16 *map, *dst;
    പൂർണ്ണസംഖ്യ srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = (Uint16 *)info->dst;
    dstskip = info->dst_skip / 2;
    map = (Uint16 *)info->table;

    width += info->leading_skip;

    എങ്കിൽ (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    അല്ലെങ്കിൽ എങ്കിൽ (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    അല്ലെങ്കിൽ എങ്കിൽ (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    എങ്കിൽ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        ആകുമ്പോൾ (height--) {
            Uint8 byte = 0, bit;
            വേണ്ടി (c = 0; c < info->leading_skip; ++c) {
                എങ്കിൽ (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            വേണ്ടി (; c < width; ++c) {
                എങ്കിൽ (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                എങ്കിൽ (1) {
                    *dst = map[bit];
                }
                byte >>= srcbpp;
                dst++;
            }
            src += srcskip;
            dst += dstskip;
        }
    } അല്ലെങ്കിൽ {
        ആകുമ്പോൾ (height--) {
            Uint8 byte = 0, bit;
            വേണ്ടി (c = 0; c < info->leading_skip; ++c) {
                എങ്കിൽ (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            വേണ്ടി (; c < width; ++c) {
                എങ്കിൽ (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                എങ്കിൽ (1) {
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

SDL_FORCE_INLINE ശൂന്യം BlitBto3(SDL_BlitInfo *info, സ്ഥിരം Uint32 srcbpp)
{
    സ്ഥിരം Uint32 mask = (1 << srcbpp) - 1;
    സ്ഥിരം Uint32 align = (8 / srcbpp) - 1;

    പൂർണ്ണസംഖ്യ c, o;
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

    width += info->leading_skip;

    എങ്കിൽ (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    അല്ലെങ്കിൽ എങ്കിൽ (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    അല്ലെങ്കിൽ എങ്കിൽ (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    എങ്കിൽ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        ആകുമ്പോൾ (height--) {
            Uint8 byte = 0, bit;
            വേണ്ടി (c = 0; c < info->leading_skip; ++c) {
                എങ്കിൽ (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            വേണ്ടി (; c < width; ++c) {
                എങ്കിൽ (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                എങ്കിൽ (1) {
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
    } അല്ലെങ്കിൽ {
        ആകുമ്പോൾ (height--) {
            Uint8 byte = 0, bit;
            വേണ്ടി (c = 0; c < info->leading_skip; ++c) {
                എങ്കിൽ (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            വേണ്ടി (; c < width; ++c) {
                എങ്കിൽ (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                എങ്കിൽ (1) {
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

SDL_FORCE_INLINE ശൂന്യം BlitBto4(SDL_BlitInfo *info, സ്ഥിരം Uint32 srcbpp)
{
    സ്ഥിരം Uint32 mask = (1 << srcbpp) - 1;
    സ്ഥിരം Uint32 align = (8 / srcbpp) - 1;

    പൂർണ്ണസംഖ്യ width, height;
    Uint8 *src;
    Uint32 *map, *dst;
    പൂർണ്ണസംഖ്യ srcskip, dstskip;
    പൂർണ്ണസംഖ്യ c;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = (Uint32 *)info->dst;
    dstskip = info->dst_skip / 4;
    map = (Uint32 *)info->table;

    width += info->leading_skip;

    എങ്കിൽ (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    അല്ലെങ്കിൽ എങ്കിൽ (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    അല്ലെങ്കിൽ എങ്കിൽ (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    എങ്കിൽ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        ആകുമ്പോൾ (height--) {
            Uint8 byte = 0, bit;
            വേണ്ടി (c = 0; c < info->leading_skip; ++c) {
                എങ്കിൽ (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            വേണ്ടി (; c < width; ++c) {
                എങ്കിൽ (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                എങ്കിൽ (1) {
                    *dst = map[bit];
                }
                byte >>= srcbpp;
                dst++;
            }
            src += srcskip;
            dst += dstskip;
        }
    } അല്ലെങ്കിൽ {
        ആകുമ്പോൾ (height--) {
            Uint8 byte = 0, bit;
            വേണ്ടി (c = 0; c < info->leading_skip; ++c) {
                എങ്കിൽ (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            വേണ്ടി (; c < width; ++c) {
                എങ്കിൽ (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                എങ്കിൽ (1) {
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

SDL_FORCE_INLINE ശൂന്യം Blit_Bto1_താക്കോൽ(SDL_BlitInfo *info, സ്ഥിരം Uint32 srcbpp)
{
    സ്ഥിരം Uint32 mask = (1 << srcbpp) - 1;
    സ്ഥിരം Uint32 align = (8 / srcbpp) - 1;

    പൂർണ്ണസംഖ്യ width = info->dst_w;
    പൂർണ്ണസംഖ്യ height = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    പൂർണ്ണസംഖ്യ srcskip = info->src_skip;
    പൂർണ്ണസംഖ്യ dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->table;
    പൂർണ്ണസംഖ്യ c;

    width += info->leading_skip;

    എങ്കിൽ (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    അല്ലെങ്കിൽ എങ്കിൽ (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    അല്ലെങ്കിൽ എങ്കിൽ (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    എങ്കിൽ (palmap) {
        എങ്കിൽ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            ആകുമ്പോൾ (height--) {
                Uint8 byte = 0, bit;
                വേണ്ടി (c = 0; c < info->leading_skip; ++c) {
                    എങ്കിൽ (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                വേണ്ടി (; c < width; ++c) {
                    എങ്കിൽ (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte & mask);
                    എങ്കിൽ (bit != ckey) {
                        *dst = palmap[bit];
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } അല്ലെങ്കിൽ {
            ആകുമ്പോൾ (height--) {
                Uint8 byte = 0, bit;
                വേണ്ടി (c = 0; c < info->leading_skip; ++c) {
                    എങ്കിൽ (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                വേണ്ടി (; c < width; ++c) {
                    എങ്കിൽ (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte >> (8 - srcbpp)) & mask;
                    എങ്കിൽ (bit != ckey) {
                        *dst = palmap[bit];
                    }
                    dst++;
                    byte <<= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        }
    } അല്ലെങ്കിൽ {
        എങ്കിൽ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            ആകുമ്പോൾ (height--) {
                Uint8 byte = 0, bit;
                വേണ്ടി (c = 0; c < info->leading_skip; ++c) {
                    എങ്കിൽ (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                വേണ്ടി (; c < width; ++c) {
                    എങ്കിൽ (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte & mask);
                    എങ്കിൽ (bit != ckey) {
                        *dst = bit;
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } അല്ലെങ്കിൽ {
            ആകുമ്പോൾ (height--) {
                Uint8 byte = 0, bit;
                വേണ്ടി (c = 0; c < info->leading_skip; ++c) {
                    എങ്കിൽ (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                വേണ്ടി (; c < width; ++c) {
                    എങ്കിൽ (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte >> (8 - srcbpp)) & mask;
                    എങ്കിൽ (bit != ckey) {
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

SDL_FORCE_INLINE ശൂന്യം Blit_Bto2_താക്കോൽ(SDL_BlitInfo *info, സ്ഥിരം Uint32 srcbpp)
{
    സ്ഥിരം Uint32 mask = (1 << srcbpp) - 1;
    സ്ഥിരം Uint32 align = (8 / srcbpp) - 1;

    പൂർണ്ണസംഖ്യ width = info->dst_w;
    പൂർണ്ണസംഖ്യ height = info->dst_h;
    Uint8 *src = info->src;
    Uint16 *dstp = (Uint16 *)info->dst;
    പൂർണ്ണസംഖ്യ srcskip = info->src_skip;
    പൂർണ്ണസംഖ്യ dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->table;
    പൂർണ്ണസംഖ്യ c;

    width += info->leading_skip;

    എങ്കിൽ (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    അല്ലെങ്കിൽ എങ്കിൽ (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    അല്ലെങ്കിൽ എങ്കിൽ (srcbpp == 1)
        srcskip += width - (width + 7) / 8;
    dstskip /= 2;

    എങ്കിൽ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        ആകുമ്പോൾ (height--) {
            Uint8 byte = 0, bit;
            വേണ്ടി (c = 0; c < info->leading_skip; ++c) {
                എങ്കിൽ (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            വേണ്ടി (; c < width; ++c) {
                എങ്കിൽ (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                എങ്കിൽ (bit != ckey) {
                    *dstp = ((Uint16 *)palmap)[bit];
                }
                byte >>= srcbpp;
                dstp++;
            }
            src += srcskip;
            dstp += dstskip;
        }
    } അല്ലെങ്കിൽ {
        ആകുമ്പോൾ (height--) {
            Uint8 byte = 0, bit;
            വേണ്ടി (c = 0; c < info->leading_skip; ++c) {
                എങ്കിൽ (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            വേണ്ടി (; c < width; ++c) {
                എങ്കിൽ (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                എങ്കിൽ (bit != ckey) {
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

SDL_FORCE_INLINE ശൂന്യം Blit_Bto3_താക്കോൽ(SDL_BlitInfo *info, സ്ഥിരം Uint32 srcbpp)
{
    സ്ഥിരം Uint32 mask = (1 << srcbpp) - 1;
    സ്ഥിരം Uint32 align = (8 / srcbpp) - 1;

    പൂർണ്ണസംഖ്യ width = info->dst_w;
    പൂർണ്ണസംഖ്യ height = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    പൂർണ്ണസംഖ്യ srcskip = info->src_skip;
    പൂർണ്ണസംഖ്യ dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->table;
    പൂർണ്ണസംഖ്യ c;

    width += info->leading_skip;

    എങ്കിൽ (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    അല്ലെങ്കിൽ എങ്കിൽ (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    അല്ലെങ്കിൽ എങ്കിൽ (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    എങ്കിൽ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        ആകുമ്പോൾ (height--) {
            Uint8 byte = 0, bit;
            വേണ്ടി (c = 0; c < info->leading_skip; ++c) {
                എങ്കിൽ (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            വേണ്ടി (; c < width; ++c) {
                എങ്കിൽ (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                എങ്കിൽ (bit != ckey) {
                    SDL_memcpy(dst, &palmap[bit * 4], 3);
                }
                byte >>= srcbpp;
                dst += 3;
            }
            src += srcskip;
            dst += dstskip;
        }
    } അല്ലെങ്കിൽ {
        ആകുമ്പോൾ (height--) {
            Uint8 byte = 0, bit;
            വേണ്ടി (c = 0; c < info->leading_skip; ++c) {
                എങ്കിൽ (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            വേണ്ടി (; c < width; ++c) {
                എങ്കിൽ (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                എങ്കിൽ (bit != ckey) {
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

SDL_FORCE_INLINE ശൂന്യം Blit_Bto4_താക്കോൽ(SDL_BlitInfo *info, സ്ഥിരം Uint32 srcbpp)
{
    സ്ഥിരം Uint32 mask = (1 << srcbpp) - 1;
    സ്ഥിരം Uint32 align = (8 / srcbpp) - 1;

    പൂർണ്ണസംഖ്യ width = info->dst_w;
    പൂർണ്ണസംഖ്യ height = info->dst_h;
    Uint8 *src = info->src;
    Uint32 *dstp = (Uint32 *)info->dst;
    പൂർണ്ണസംഖ്യ srcskip = info->src_skip;
    പൂർണ്ണസംഖ്യ dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->table;
    പൂർണ്ണസംഖ്യ c;

    width += info->leading_skip;

    എങ്കിൽ (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    അല്ലെങ്കിൽ എങ്കിൽ (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    അല്ലെങ്കിൽ എങ്കിൽ (srcbpp == 1)
        srcskip += width - (width + 7) / 8;
    dstskip /= 4;

    എങ്കിൽ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        ആകുമ്പോൾ (height--) {
            Uint8 byte = 0, bit;
            വേണ്ടി (c = 0; c < info->leading_skip; ++c) {
                എങ്കിൽ (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            വേണ്ടി (; c < width; ++c) {
                എങ്കിൽ (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                എങ്കിൽ (bit != ckey) {
                    *dstp = ((Uint32 *)palmap)[bit];
                }
                byte >>= srcbpp;
                dstp++;
            }
            src += srcskip;
            dstp += dstskip;
        }
    } അല്ലെങ്കിൽ {
        ആകുമ്പോൾ (height--) {
            Uint8 byte = 0, bit;
            വേണ്ടി (c = 0; c < info->leading_skip; ++c) {
                എങ്കിൽ (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            വേണ്ടി (; c < width; ++c) {
                എങ്കിൽ (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                എങ്കിൽ (bit != ckey) {
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

സ്ഥിതം ശൂന്യം BlitBtoNAlpha(SDL_BlitInfo *info)
{
    പൂർണ്ണസംഖ്യ width = info->dst_w;
    പൂർണ്ണസംഖ്യ height = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    പൂർണ്ണസംഖ്യ srcskip = info->src_skip;
    പൂർണ്ണസംഖ്യ dstskip = info->dst_skip;
    സ്ഥിരം SDL_Color *srcpal = info->src_pal->colors;
    സ്ഥിരം SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    സ്ഥിരം SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    പൂർണ്ണസംഖ്യ srcbpp, dstbpp;
    പൂർണ്ണസംഖ്യ c;
    Uint32 pixelvalue, mask, align;
    unsigned sR, sG, sB;
    unsigned dR, dG, dB, dA;
    സ്ഥിരം unsigned A = info->a;

    width += info->leading_skip;

    srcbpp = srcfmt->bytes_per_pixel;
    dstbpp = dstfmt->bytes_per_pixel;
    എങ്കിൽ (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    അല്ലെങ്കിൽ എങ്കിൽ (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    അല്ലെങ്കിൽ എങ്കിൽ (srcbpp == 1)
        srcskip += width - (width + 7) / 8;
    mask = (1 << srcbpp) - 1;
    align = (8 / srcbpp) - 1;

    എങ്കിൽ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        ആകുമ്പോൾ (height--) {
            Uint8 byte = 0, bit;
            വേണ്ടി (c = 0; c < info->leading_skip; ++c) {
                എങ്കിൽ (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            വേണ്ടി (; c < width; ++c) {
                എങ്കിൽ (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                എങ്കിൽ (1) {
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
    } അല്ലെങ്കിൽ {
        ആകുമ്പോൾ (height--) {
            Uint8 byte = 0, bit;
            വേണ്ടി (c = 0; c < info->leading_skip; ++c) {
                എങ്കിൽ (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            വേണ്ടി (; c < width; ++c) {
                എങ്കിൽ (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                എങ്കിൽ (1) {
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

സ്ഥിതം ശൂന്യം Blit_Bto_NAlpha_താക്കോൽ(SDL_BlitInfo *info)
{
    പൂർണ്ണസംഖ്യ width = info->dst_w;
    പൂർണ്ണസംഖ്യ height = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    പൂർണ്ണസംഖ്യ srcskip = info->src_skip;
    പൂർണ്ണസംഖ്യ dstskip = info->dst_skip;
    സ്ഥിരം SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    സ്ഥിരം SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    സ്ഥിരം SDL_Color *srcpal = info->src_pal->colors;
    പൂർണ്ണസംഖ്യ srcbpp, dstbpp;
    പൂർണ്ണസംഖ്യ c;
    Uint32 pixelvalue, mask, align;
    unsigned sR, sG, sB;
    unsigned dR, dG, dB, dA;
    സ്ഥിരം unsigned A = info->a;
    Uint32 ckey = info->colorkey;

    width += info->leading_skip;

    srcbpp = srcfmt->bytes_per_pixel;
    dstbpp = dstfmt->bytes_per_pixel;
    എങ്കിൽ (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    അല്ലെങ്കിൽ എങ്കിൽ (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    അല്ലെങ്കിൽ എങ്കിൽ (srcbpp == 1)
        srcskip += width - (width + 7) / 8;
    mask = (1 << srcbpp) - 1;
    align = (8 / srcbpp) - 1;

    എങ്കിൽ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        ആകുമ്പോൾ (height--) {
            Uint8 byte = 0, bit;
            വേണ്ടി (c = 0; c < info->leading_skip; ++c) {
                എങ്കിൽ (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            വേണ്ടി (; c < width; ++c) {
                എങ്കിൽ (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                എങ്കിൽ (bit != ckey) {
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
    } അല്ലെങ്കിൽ {
        ആകുമ്പോൾ (height--) {
            Uint8 byte = 0, bit;
            വേണ്ടി (c = 0; c < info->leading_skip; ++c) {
                എങ്കിൽ (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            വേണ്ടി (; c < width; ++c) {
                എങ്കിൽ (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                എങ്കിൽ (bit != ckey) {
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



സ്ഥിതം ശൂന്യം Blit1bto1(SDL_BlitInfo *info) {
    BlitBto1(info, 1);
}

സ്ഥിതം ശൂന്യം Blit1bto2(SDL_BlitInfo *info) {
    BlitBto2(info, 1);
}

സ്ഥിതം ശൂന്യം Blit1bto3(SDL_BlitInfo *info) {
    BlitBto3(info, 1);
}

സ്ഥിതം ശൂന്യം Blit1bto4(SDL_BlitInfo *info) {
    BlitBto4(info, 1);
}

സ്ഥിതം സ്ഥിരം SDL_BlitFunc bitmap_blit_1b[] = {
    (SDL_BlitFunc)ശൂന്യ, Blit1bto1, Blit1bto2, Blit1bto3, Blit1bto4
};

സ്ഥിതം ശൂന്യം Blit1bto1_താക്കോൽ(SDL_BlitInfo *info) {
    Blit_Bto1_താക്കോൽ(info, 1);
}

സ്ഥിതം ശൂന്യം Blit1bto2_താക്കോൽ(SDL_BlitInfo *info) {
    Blit_Bto2_താക്കോൽ(info, 1);
}

സ്ഥിതം ശൂന്യം Blit1bto3_താക്കോൽ(SDL_BlitInfo *info) {
    Blit_Bto3_താക്കോൽ(info, 1);
}

സ്ഥിതം ശൂന്യം Blit1bto4_താക്കോൽ(SDL_BlitInfo *info) {
    Blit_Bto4_താക്കോൽ(info, 1);
}

സ്ഥിതം സ്ഥിരം SDL_BlitFunc colorkey_blit_1b[] = {
    (SDL_BlitFunc)ശൂന്യ, Blit1bto1_താക്കോൽ, Blit1bto2_താക്കോൽ, Blit1bto3_താക്കോൽ, Blit1bto4_താക്കോൽ
};



സ്ഥിതം ശൂന്യം Blit2bto1(SDL_BlitInfo *info) {
    BlitBto1(info, 2);
}

സ്ഥിതം ശൂന്യം Blit2bto2(SDL_BlitInfo *info) {
    BlitBto2(info, 2);
}

സ്ഥിതം ശൂന്യം Blit2bto3(SDL_BlitInfo *info) {
    BlitBto3(info, 2);
}

സ്ഥിതം ശൂന്യം Blit2bto4(SDL_BlitInfo *info) {
    BlitBto4(info, 2);
}

സ്ഥിതം സ്ഥിരം SDL_BlitFunc bitmap_blit_2b[] = {
    (SDL_BlitFunc)ശൂന്യ, Blit2bto1, Blit2bto2, Blit2bto3, Blit2bto4
};

സ്ഥിതം ശൂന്യം Blit2bto1_താക്കോൽ(SDL_BlitInfo *info) {
    Blit_Bto1_താക്കോൽ(info, 2);
}

സ്ഥിതം ശൂന്യം Blit2bto2_താക്കോൽ(SDL_BlitInfo *info) {
    Blit_Bto2_താക്കോൽ(info, 2);
}

സ്ഥിതം ശൂന്യം Blit2bto3_താക്കോൽ(SDL_BlitInfo *info) {
    Blit_Bto3_താക്കോൽ(info, 2);
}

സ്ഥിതം ശൂന്യം Blit2bto4_താക്കോൽ(SDL_BlitInfo *info) {
    Blit_Bto4_താക്കോൽ(info, 2);
}

സ്ഥിതം സ്ഥിരം SDL_BlitFunc colorkey_blit_2b[] = {
    (SDL_BlitFunc)ശൂന്യ, Blit2bto1_താക്കോൽ, Blit2bto2_താക്കോൽ, Blit2bto3_താക്കോൽ, Blit2bto4_താക്കോൽ
};



സ്ഥിതം ശൂന്യം Blit4bto1(SDL_BlitInfo *info) {
    BlitBto1(info, 4);
}

സ്ഥിതം ശൂന്യം Blit4bto2(SDL_BlitInfo *info) {
    BlitBto2(info, 4);
}

സ്ഥിതം ശൂന്യം Blit4bto3(SDL_BlitInfo *info) {
    BlitBto3(info, 4);
}

സ്ഥിതം ശൂന്യം Blit4bto4(SDL_BlitInfo *info) {
    BlitBto4(info, 4);
}

സ്ഥിതം സ്ഥിരം SDL_BlitFunc bitmap_blit_4b[] = {
    (SDL_BlitFunc)ശൂന്യ, Blit4bto1, Blit4bto2, Blit4bto3, Blit4bto4
};

സ്ഥിതം ശൂന്യം Blit4bto1_താക്കോൽ(SDL_BlitInfo *info) {
    Blit_Bto1_താക്കോൽ(info, 4);
}

സ്ഥിതം ശൂന്യം Blit4bto2_താക്കോൽ(SDL_BlitInfo *info) {
    Blit_Bto2_താക്കോൽ(info, 4);
}

സ്ഥിതം ശൂന്യം Blit4bto3_താക്കോൽ(SDL_BlitInfo *info) {
    Blit_Bto3_താക്കോൽ(info, 4);
}

സ്ഥിതം ശൂന്യം Blit4bto4_താക്കോൽ(SDL_BlitInfo *info) {
    Blit_Bto4_താക്കോൽ(info, 4);
}

സ്ഥിതം സ്ഥിരം SDL_BlitFunc colorkey_blit_4b[] = {
    (SDL_BlitFunc)ശൂന്യ, Blit4bto1_താക്കോൽ, Blit4bto2_താക്കോൽ, Blit4bto3_താക്കോൽ, Blit4bto4_താക്കോൽ
};



SDL_BlitFunc SDL_CalculateBlit0(SDL_Surface *surface)
{
    പൂർണ്ണസംഖ്യ which;

    എങ്കിൽ (SDL_BITSPERPIXEL(surface->map.info.dst_fmt->format) < 8) {
        which = 0;
    } അല്ലെങ്കിൽ {
        which = SDL_BYTESPERPIXEL(surface->map.info.dst_fmt->format);
    }

    എങ്കിൽ (SDL_PIXELTYPE(surface->format) == SDL_PIXELTYPE_INDEX1) {
        തിരഞ്ഞെടുപ്പ് (surface->map.info.flags & ~SDL_COPY_RLE_MASK) {
        അവസ്ഥ 0:
            എങ്കിൽ (which < SDL_arraysize(bitmap_blit_1b)) {
                തിരികെ bitmap_blit_1b[which];
            }
            നിർത്തുക;

        അവസ്ഥ SDL_COPY_COLORKEY:
            എങ്കിൽ (which < SDL_arraysize(colorkey_blit_1b)) {
                തിരികെ colorkey_blit_1b[which];
            }
            നിർത്തുക;

        അവസ്ഥ SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            തിരികെ which >= 2 ? BlitBtoNAlpha : (SDL_BlitFunc)ശൂന്യ;

        അവസ്ഥ SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            തിരികെ which >= 2 ? Blit_Bto_NAlpha_താക്കോൽ : (SDL_BlitFunc)ശൂന്യ;
        }
        തിരികെ ശൂന്യ;
    }

    എങ്കിൽ (SDL_PIXELTYPE(surface->format) == SDL_PIXELTYPE_INDEX2) {
        തിരഞ്ഞെടുപ്പ് (surface->map.info.flags & ~SDL_COPY_RLE_MASK) {
        അവസ്ഥ 0:
            എങ്കിൽ (which < SDL_arraysize(bitmap_blit_2b)) {
                തിരികെ bitmap_blit_2b[which];
            }
            നിർത്തുക;

        അവസ്ഥ SDL_COPY_COLORKEY:
            എങ്കിൽ (which < SDL_arraysize(colorkey_blit_2b)) {
                തിരികെ colorkey_blit_2b[which];
            }
            നിർത്തുക;

        അവസ്ഥ SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            തിരികെ which >= 2 ? BlitBtoNAlpha : (SDL_BlitFunc)ശൂന്യ;

        അവസ്ഥ SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            തിരികെ which >= 2 ? Blit_Bto_NAlpha_താക്കോൽ : (SDL_BlitFunc)ശൂന്യ;
        }
        തിരികെ ശൂന്യ;
    }

    എങ്കിൽ (SDL_PIXELTYPE(surface->format) == SDL_PIXELTYPE_INDEX4) {
        തിരഞ്ഞെടുപ്പ് (surface->map.info.flags & ~SDL_COPY_RLE_MASK) {
        അവസ്ഥ 0:
            എങ്കിൽ (which < SDL_arraysize(bitmap_blit_4b)) {
                തിരികെ bitmap_blit_4b[which];
            }
            നിർത്തുക;

        അവസ്ഥ SDL_COPY_COLORKEY:
            എങ്കിൽ (which < SDL_arraysize(colorkey_blit_4b)) {
                തിരികെ colorkey_blit_4b[which];
            }
            നിർത്തുക;

        അവസ്ഥ SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            തിരികെ which >= 2 ? BlitBtoNAlpha : (SDL_BlitFunc)ശൂന്യ;

        അവസ്ഥ SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            തിരികെ which >= 2 ? Blit_Bto_NAlpha_താക്കോൽ : (SDL_BlitFunc)ശൂന്യ;
        }
        തിരികെ ശൂന്യ;
    }

    തിരികെ ശൂന്യ;
}

#endif // SDL_HAVE_BLIT_0
