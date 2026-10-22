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

#ifdef SDL_HAVE_BLIT_0

#ಅನ್ತರ್ಭಾವ "SDL_surface_c.h"

// Functions to blit from bitmaps to other surfaces

SDL_FORCE_INLINE ಶೂನ್ಯ BlitBto1(SDL_BlitInfo *info, ಧ್ರುವ Uint32 srcbpp)
{
    ಧ್ರುವ Uint32 mask = (1 << srcbpp) - 1;
    ಧ್ರುವ Uint32 align = (8 / srcbpp) - 1;

    ಪೂರ್ಣಾಙ್ಕ c;
    ಪೂರ್ಣಾಙ್ಕ width, height;
    Uint8 *src, *map, *dst;
    ಪೂರ್ಣಾಙ್ಕ srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = info->table;

    width += info->leading_skip;

    ಯದಿ (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    ಅನ್ಯಥಾ ಯದಿ (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    ಅನ್ಯಥಾ ಯದಿ (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    ಯದಿ (map) {
        ಯದಿ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            ಯಾವತ್ (height--) {
                Uint8 byte = 0, bit;
                ಪ್ರತಿ (c = 0; c < info->leading_skip; ++c) {
                    ಯದಿ (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                ಪ್ರತಿ (; c < width; ++c) {
                    ಯದಿ (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte & mask);
                    ಯದಿ (1) {
                        *dst = map[bit];
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } ಅನ್ಯಥಾ {
            ಯಾವತ್ (height--) {
                Uint8 byte = 0, bit;
                ಪ್ರತಿ (c = 0; c < info->leading_skip; ++c) {
                    ಯದಿ (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                ಪ್ರತಿ (; c < width; ++c) {
                    ಯದಿ (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte >> (8 - srcbpp)) & mask;
                    ಯದಿ (1) {
                        *dst = map[bit];
                    }
                    dst++;
                    byte <<= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        }
    } ಅನ್ಯಥಾ {
        ಯದಿ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            ಯಾವತ್ (height--) {
                Uint8 byte = 0, bit;
                ಪ್ರತಿ (c = 0; c < info->leading_skip; ++c) {
                    ಯದಿ (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                ಪ್ರತಿ (; c < width; ++c) {
                    ಯದಿ (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte & mask);
                    ಯದಿ (1) {
                        *dst = bit;
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } ಅನ್ಯಥಾ {
            ಯಾವತ್ (height--) {
                Uint8 byte = 0, bit;
                ಪ್ರತಿ (c = 0; c < info->leading_skip; ++c) {
                    ಯದಿ (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                ಪ್ರತಿ (; c < width; ++c) {
                    ಯದಿ (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte >> (8 - srcbpp)) & mask;
                    ಯದಿ (1) {
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

SDL_FORCE_INLINE ಶೂನ್ಯ BlitBto2(SDL_BlitInfo *info, ಧ್ರುವ Uint32 srcbpp)
{
    ಧ್ರುವ Uint32 mask = (1 << srcbpp) - 1;
    ಧ್ರುವ Uint32 align = (8 / srcbpp) - 1;

    ಪೂರ್ಣಾಙ್ಕ c;
    ಪೂರ್ಣಾಙ್ಕ width, height;
    Uint8 *src;
    Uint16 *map, *dst;
    ಪೂರ್ಣಾಙ್ಕ srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = (Uint16 *)info->dst;
    dstskip = info->dst_skip / 2;
    map = (Uint16 *)info->table;

    width += info->leading_skip;

    ಯದಿ (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    ಅನ್ಯಥಾ ಯದಿ (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    ಅನ್ಯಥಾ ಯದಿ (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    ಯದಿ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        ಯಾವತ್ (height--) {
            Uint8 byte = 0, bit;
            ಪ್ರತಿ (c = 0; c < info->leading_skip; ++c) {
                ಯದಿ (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            ಪ್ರತಿ (; c < width; ++c) {
                ಯದಿ (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                ಯದಿ (1) {
                    *dst = map[bit];
                }
                byte >>= srcbpp;
                dst++;
            }
            src += srcskip;
            dst += dstskip;
        }
    } ಅನ್ಯಥಾ {
        ಯಾವತ್ (height--) {
            Uint8 byte = 0, bit;
            ಪ್ರತಿ (c = 0; c < info->leading_skip; ++c) {
                ಯದಿ (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            ಪ್ರತಿ (; c < width; ++c) {
                ಯದಿ (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                ಯದಿ (1) {
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

SDL_FORCE_INLINE ಶೂನ್ಯ BlitBto3(SDL_BlitInfo *info, ಧ್ರುವ Uint32 srcbpp)
{
    ಧ್ರುವ Uint32 mask = (1 << srcbpp) - 1;
    ಧ್ರುವ Uint32 align = (8 / srcbpp) - 1;

    ಪೂರ್ಣಾಙ್ಕ c, o;
    ಪೂರ್ಣಾಙ್ಕ width, height;
    Uint8 *src, *map, *dst;
    ಪೂರ್ಣಾಙ್ಕ srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = info->table;

    width += info->leading_skip;

    ಯದಿ (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    ಅನ್ಯಥಾ ಯದಿ (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    ಅನ್ಯಥಾ ಯದಿ (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    ಯದಿ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        ಯಾವತ್ (height--) {
            Uint8 byte = 0, bit;
            ಪ್ರತಿ (c = 0; c < info->leading_skip; ++c) {
                ಯದಿ (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            ಪ್ರತಿ (; c < width; ++c) {
                ಯದಿ (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                ಯದಿ (1) {
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
    } ಅನ್ಯಥಾ {
        ಯಾವತ್ (height--) {
            Uint8 byte = 0, bit;
            ಪ್ರತಿ (c = 0; c < info->leading_skip; ++c) {
                ಯದಿ (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            ಪ್ರತಿ (; c < width; ++c) {
                ಯದಿ (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                ಯದಿ (1) {
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

SDL_FORCE_INLINE ಶೂನ್ಯ BlitBto4(SDL_BlitInfo *info, ಧ್ರುವ Uint32 srcbpp)
{
    ಧ್ರುವ Uint32 mask = (1 << srcbpp) - 1;
    ಧ್ರುವ Uint32 align = (8 / srcbpp) - 1;

    ಪೂರ್ಣಾಙ್ಕ width, height;
    Uint8 *src;
    Uint32 *map, *dst;
    ಪೂರ್ಣಾಙ್ಕ srcskip, dstskip;
    ಪೂರ್ಣಾಙ್ಕ c;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = (Uint32 *)info->dst;
    dstskip = info->dst_skip / 4;
    map = (Uint32 *)info->table;

    width += info->leading_skip;

    ಯದಿ (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    ಅನ್ಯಥಾ ಯದಿ (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    ಅನ್ಯಥಾ ಯದಿ (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    ಯದಿ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        ಯಾವತ್ (height--) {
            Uint8 byte = 0, bit;
            ಪ್ರತಿ (c = 0; c < info->leading_skip; ++c) {
                ಯದಿ (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            ಪ್ರತಿ (; c < width; ++c) {
                ಯದಿ (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                ಯದಿ (1) {
                    *dst = map[bit];
                }
                byte >>= srcbpp;
                dst++;
            }
            src += srcskip;
            dst += dstskip;
        }
    } ಅನ್ಯಥಾ {
        ಯಾವತ್ (height--) {
            Uint8 byte = 0, bit;
            ಪ್ರತಿ (c = 0; c < info->leading_skip; ++c) {
                ಯದಿ (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            ಪ್ರತಿ (; c < width; ++c) {
                ಯದಿ (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                ಯದಿ (1) {
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

SDL_FORCE_INLINE ಶೂನ್ಯ Blit_Bto1_ಕೀಲಿ(SDL_BlitInfo *info, ಧ್ರುವ Uint32 srcbpp)
{
    ಧ್ರುವ Uint32 mask = (1 << srcbpp) - 1;
    ಧ್ರುವ Uint32 align = (8 / srcbpp) - 1;

    ಪೂರ್ಣಾಙ್ಕ width = info->dst_w;
    ಪೂರ್ಣಾಙ್ಕ height = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    ಪೂರ್ಣಾಙ್ಕ srcskip = info->src_skip;
    ಪೂರ್ಣಾಙ್ಕ dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->table;
    ಪೂರ್ಣಾಙ್ಕ c;

    width += info->leading_skip;

    ಯದಿ (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    ಅನ್ಯಥಾ ಯದಿ (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    ಅನ್ಯಥಾ ಯದಿ (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    ಯದಿ (palmap) {
        ಯದಿ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            ಯಾವತ್ (height--) {
                Uint8 byte = 0, bit;
                ಪ್ರತಿ (c = 0; c < info->leading_skip; ++c) {
                    ಯದಿ (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                ಪ್ರತಿ (; c < width; ++c) {
                    ಯದಿ (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte & mask);
                    ಯದಿ (bit != ckey) {
                        *dst = palmap[bit];
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } ಅನ್ಯಥಾ {
            ಯಾವತ್ (height--) {
                Uint8 byte = 0, bit;
                ಪ್ರತಿ (c = 0; c < info->leading_skip; ++c) {
                    ಯದಿ (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                ಪ್ರತಿ (; c < width; ++c) {
                    ಯದಿ (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte >> (8 - srcbpp)) & mask;
                    ಯದಿ (bit != ckey) {
                        *dst = palmap[bit];
                    }
                    dst++;
                    byte <<= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        }
    } ಅನ್ಯಥಾ {
        ಯದಿ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            ಯಾವತ್ (height--) {
                Uint8 byte = 0, bit;
                ಪ್ರತಿ (c = 0; c < info->leading_skip; ++c) {
                    ಯದಿ (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                ಪ್ರತಿ (; c < width; ++c) {
                    ಯದಿ (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte & mask);
                    ಯದಿ (bit != ckey) {
                        *dst = bit;
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } ಅನ್ಯಥಾ {
            ಯಾವತ್ (height--) {
                Uint8 byte = 0, bit;
                ಪ್ರತಿ (c = 0; c < info->leading_skip; ++c) {
                    ಯದಿ (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                ಪ್ರತಿ (; c < width; ++c) {
                    ಯದಿ (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte >> (8 - srcbpp)) & mask;
                    ಯದಿ (bit != ckey) {
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

SDL_FORCE_INLINE ಶೂನ್ಯ Blit_Bto2_ಕೀಲಿ(SDL_BlitInfo *info, ಧ್ರುವ Uint32 srcbpp)
{
    ಧ್ರುವ Uint32 mask = (1 << srcbpp) - 1;
    ಧ್ರುವ Uint32 align = (8 / srcbpp) - 1;

    ಪೂರ್ಣಾಙ್ಕ width = info->dst_w;
    ಪೂರ್ಣಾಙ್ಕ height = info->dst_h;
    Uint8 *src = info->src;
    Uint16 *dstp = (Uint16 *)info->dst;
    ಪೂರ್ಣಾಙ್ಕ srcskip = info->src_skip;
    ಪೂರ್ಣಾಙ್ಕ dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->table;
    ಪೂರ್ಣಾಙ್ಕ c;

    width += info->leading_skip;

    ಯದಿ (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    ಅನ್ಯಥಾ ಯದಿ (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    ಅನ್ಯಥಾ ಯದಿ (srcbpp == 1)
        srcskip += width - (width + 7) / 8;
    dstskip /= 2;

    ಯದಿ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        ಯಾವತ್ (height--) {
            Uint8 byte = 0, bit;
            ಪ್ರತಿ (c = 0; c < info->leading_skip; ++c) {
                ಯದಿ (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            ಪ್ರತಿ (; c < width; ++c) {
                ಯದಿ (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                ಯದಿ (bit != ckey) {
                    *dstp = ((Uint16 *)palmap)[bit];
                }
                byte >>= srcbpp;
                dstp++;
            }
            src += srcskip;
            dstp += dstskip;
        }
    } ಅನ್ಯಥಾ {
        ಯಾವತ್ (height--) {
            Uint8 byte = 0, bit;
            ಪ್ರತಿ (c = 0; c < info->leading_skip; ++c) {
                ಯದಿ (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            ಪ್ರತಿ (; c < width; ++c) {
                ಯದಿ (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                ಯದಿ (bit != ckey) {
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

SDL_FORCE_INLINE ಶೂನ್ಯ Blit_Bto3_ಕೀಲಿ(SDL_BlitInfo *info, ಧ್ರುವ Uint32 srcbpp)
{
    ಧ್ರುವ Uint32 mask = (1 << srcbpp) - 1;
    ಧ್ರುವ Uint32 align = (8 / srcbpp) - 1;

    ಪೂರ್ಣಾಙ್ಕ width = info->dst_w;
    ಪೂರ್ಣಾಙ್ಕ height = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    ಪೂರ್ಣಾಙ್ಕ srcskip = info->src_skip;
    ಪೂರ್ಣಾಙ್ಕ dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->table;
    ಪೂರ್ಣಾಙ್ಕ c;

    width += info->leading_skip;

    ಯದಿ (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    ಅನ್ಯಥಾ ಯದಿ (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    ಅನ್ಯಥಾ ಯದಿ (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    ಯದಿ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        ಯಾವತ್ (height--) {
            Uint8 byte = 0, bit;
            ಪ್ರತಿ (c = 0; c < info->leading_skip; ++c) {
                ಯದಿ (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            ಪ್ರತಿ (; c < width; ++c) {
                ಯದಿ (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                ಯದಿ (bit != ckey) {
                    SDL_memcpy(dst, &palmap[bit * 4], 3);
                }
                byte >>= srcbpp;
                dst += 3;
            }
            src += srcskip;
            dst += dstskip;
        }
    } ಅನ್ಯಥಾ {
        ಯಾವತ್ (height--) {
            Uint8 byte = 0, bit;
            ಪ್ರತಿ (c = 0; c < info->leading_skip; ++c) {
                ಯದಿ (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            ಪ್ರತಿ (; c < width; ++c) {
                ಯದಿ (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                ಯದಿ (bit != ckey) {
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

SDL_FORCE_INLINE ಶೂನ್ಯ Blit_Bto4_ಕೀಲಿ(SDL_BlitInfo *info, ಧ್ರುವ Uint32 srcbpp)
{
    ಧ್ರುವ Uint32 mask = (1 << srcbpp) - 1;
    ಧ್ರುವ Uint32 align = (8 / srcbpp) - 1;

    ಪೂರ್ಣಾಙ್ಕ width = info->dst_w;
    ಪೂರ್ಣಾಙ್ಕ height = info->dst_h;
    Uint8 *src = info->src;
    Uint32 *dstp = (Uint32 *)info->dst;
    ಪೂರ್ಣಾಙ್ಕ srcskip = info->src_skip;
    ಪೂರ್ಣಾಙ್ಕ dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->table;
    ಪೂರ್ಣಾಙ್ಕ c;

    width += info->leading_skip;

    ಯದಿ (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    ಅನ್ಯಥಾ ಯದಿ (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    ಅನ್ಯಥಾ ಯದಿ (srcbpp == 1)
        srcskip += width - (width + 7) / 8;
    dstskip /= 4;

    ಯದಿ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        ಯಾವತ್ (height--) {
            Uint8 byte = 0, bit;
            ಪ್ರತಿ (c = 0; c < info->leading_skip; ++c) {
                ಯದಿ (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            ಪ್ರತಿ (; c < width; ++c) {
                ಯದಿ (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                ಯದಿ (bit != ckey) {
                    *dstp = ((Uint32 *)palmap)[bit];
                }
                byte >>= srcbpp;
                dstp++;
            }
            src += srcskip;
            dstp += dstskip;
        }
    } ಅನ್ಯಥಾ {
        ಯಾವತ್ (height--) {
            Uint8 byte = 0, bit;
            ಪ್ರತಿ (c = 0; c < info->leading_skip; ++c) {
                ಯದಿ (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            ಪ್ರತಿ (; c < width; ++c) {
                ಯದಿ (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                ಯದಿ (bit != ckey) {
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

ಸ್ಥಿರ ಶೂನ್ಯ BlitBtoNAlpha(SDL_BlitInfo *info)
{
    ಪೂರ್ಣಾಙ್ಕ width = info->dst_w;
    ಪೂರ್ಣಾಙ್ಕ height = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    ಪೂರ್ಣಾಙ್ಕ srcskip = info->src_skip;
    ಪೂರ್ಣಾಙ್ಕ dstskip = info->dst_skip;
    ಧ್ರುವ SDL_Color *srcpal = info->src_pal->colors;
    ಧ್ರುವ SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    ಧ್ರುವ SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    ಪೂರ್ಣಾಙ್ಕ srcbpp, dstbpp;
    ಪೂರ್ಣಾಙ್ಕ c;
    Uint32 pixelvalue, mask, align;
    unsigned sR, sG, sB;
    unsigned dR, dG, dB, dA;
    ಧ್ರುವ unsigned A = info->a;

    width += info->leading_skip;

    srcbpp = srcfmt->bytes_per_pixel;
    dstbpp = dstfmt->bytes_per_pixel;
    ಯದಿ (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    ಅನ್ಯಥಾ ಯದಿ (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    ಅನ್ಯಥಾ ಯದಿ (srcbpp == 1)
        srcskip += width - (width + 7) / 8;
    mask = (1 << srcbpp) - 1;
    align = (8 / srcbpp) - 1;

    ಯದಿ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        ಯಾವತ್ (height--) {
            Uint8 byte = 0, bit;
            ಪ್ರತಿ (c = 0; c < info->leading_skip; ++c) {
                ಯದಿ (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            ಪ್ರತಿ (; c < width; ++c) {
                ಯದಿ (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                ಯದಿ (1) {
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
    } ಅನ್ಯಥಾ {
        ಯಾವತ್ (height--) {
            Uint8 byte = 0, bit;
            ಪ್ರತಿ (c = 0; c < info->leading_skip; ++c) {
                ಯದಿ (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            ಪ್ರತಿ (; c < width; ++c) {
                ಯದಿ (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                ಯದಿ (1) {
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

ಸ್ಥಿರ ಶೂನ್ಯ Blit_Bto_NAlpha_ಕೀಲಿ(SDL_BlitInfo *info)
{
    ಪೂರ್ಣಾಙ್ಕ width = info->dst_w;
    ಪೂರ್ಣಾಙ್ಕ height = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    ಪೂರ್ಣಾಙ್ಕ srcskip = info->src_skip;
    ಪೂರ್ಣಾಙ್ಕ dstskip = info->dst_skip;
    ಧ್ರುವ SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    ಧ್ರುವ SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    ಧ್ರುವ SDL_Color *srcpal = info->src_pal->colors;
    ಪೂರ್ಣಾಙ್ಕ srcbpp, dstbpp;
    ಪೂರ್ಣಾಙ್ಕ c;
    Uint32 pixelvalue, mask, align;
    unsigned sR, sG, sB;
    unsigned dR, dG, dB, dA;
    ಧ್ರುವ unsigned A = info->a;
    Uint32 ckey = info->colorkey;

    width += info->leading_skip;

    srcbpp = srcfmt->bytes_per_pixel;
    dstbpp = dstfmt->bytes_per_pixel;
    ಯದಿ (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    ಅನ್ಯಥಾ ಯದಿ (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    ಅನ್ಯಥಾ ಯದಿ (srcbpp == 1)
        srcskip += width - (width + 7) / 8;
    mask = (1 << srcbpp) - 1;
    align = (8 / srcbpp) - 1;

    ಯದಿ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        ಯಾವತ್ (height--) {
            Uint8 byte = 0, bit;
            ಪ್ರತಿ (c = 0; c < info->leading_skip; ++c) {
                ಯದಿ (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            ಪ್ರತಿ (; c < width; ++c) {
                ಯದಿ (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                ಯದಿ (bit != ckey) {
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
    } ಅನ್ಯಥಾ {
        ಯಾವತ್ (height--) {
            Uint8 byte = 0, bit;
            ಪ್ರತಿ (c = 0; c < info->leading_skip; ++c) {
                ಯದಿ (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            ಪ್ರತಿ (; c < width; ++c) {
                ಯದಿ (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                ಯದಿ (bit != ckey) {
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



ಸ್ಥಿರ ಶೂನ್ಯ Blit1bto1(SDL_BlitInfo *info) {
    BlitBto1(info, 1);
}

ಸ್ಥಿರ ಶೂನ್ಯ Blit1bto2(SDL_BlitInfo *info) {
    BlitBto2(info, 1);
}

ಸ್ಥಿರ ಶೂನ್ಯ Blit1bto3(SDL_BlitInfo *info) {
    BlitBto3(info, 1);
}

ಸ್ಥಿರ ಶೂನ್ಯ Blit1bto4(SDL_BlitInfo *info) {
    BlitBto4(info, 1);
}

ಸ್ಥಿರ ಧ್ರುವ SDL_BlitFunc bitmap_blit_1b[] = {
    (SDL_BlitFunc)ರಿಕ್ತ, Blit1bto1, Blit1bto2, Blit1bto3, Blit1bto4
};

ಸ್ಥಿರ ಶೂನ್ಯ Blit1bto1_ಕೀಲಿ(SDL_BlitInfo *info) {
    Blit_Bto1_ಕೀಲಿ(info, 1);
}

ಸ್ಥಿರ ಶೂನ್ಯ Blit1bto2_ಕೀಲಿ(SDL_BlitInfo *info) {
    Blit_Bto2_ಕೀಲಿ(info, 1);
}

ಸ್ಥಿರ ಶೂನ್ಯ Blit1bto3_ಕೀಲಿ(SDL_BlitInfo *info) {
    Blit_Bto3_ಕೀಲಿ(info, 1);
}

ಸ್ಥಿರ ಶೂನ್ಯ Blit1bto4_ಕೀಲಿ(SDL_BlitInfo *info) {
    Blit_Bto4_ಕೀಲಿ(info, 1);
}

ಸ್ಥಿರ ಧ್ರುವ SDL_BlitFunc colorkey_blit_1b[] = {
    (SDL_BlitFunc)ರಿಕ್ತ, Blit1bto1_ಕೀಲಿ, Blit1bto2_ಕೀಲಿ, Blit1bto3_ಕೀಲಿ, Blit1bto4_ಕೀಲಿ
};



ಸ್ಥಿರ ಶೂನ್ಯ Blit2bto1(SDL_BlitInfo *info) {
    BlitBto1(info, 2);
}

ಸ್ಥಿರ ಶೂನ್ಯ Blit2bto2(SDL_BlitInfo *info) {
    BlitBto2(info, 2);
}

ಸ್ಥಿರ ಶೂನ್ಯ Blit2bto3(SDL_BlitInfo *info) {
    BlitBto3(info, 2);
}

ಸ್ಥಿರ ಶೂನ್ಯ Blit2bto4(SDL_BlitInfo *info) {
    BlitBto4(info, 2);
}

ಸ್ಥಿರ ಧ್ರುವ SDL_BlitFunc bitmap_blit_2b[] = {
    (SDL_BlitFunc)ರಿಕ್ತ, Blit2bto1, Blit2bto2, Blit2bto3, Blit2bto4
};

ಸ್ಥಿರ ಶೂನ್ಯ Blit2bto1_ಕೀಲಿ(SDL_BlitInfo *info) {
    Blit_Bto1_ಕೀಲಿ(info, 2);
}

ಸ್ಥಿರ ಶೂನ್ಯ Blit2bto2_ಕೀಲಿ(SDL_BlitInfo *info) {
    Blit_Bto2_ಕೀಲಿ(info, 2);
}

ಸ್ಥಿರ ಶೂನ್ಯ Blit2bto3_ಕೀಲಿ(SDL_BlitInfo *info) {
    Blit_Bto3_ಕೀಲಿ(info, 2);
}

ಸ್ಥಿರ ಶೂನ್ಯ Blit2bto4_ಕೀಲಿ(SDL_BlitInfo *info) {
    Blit_Bto4_ಕೀಲಿ(info, 2);
}

ಸ್ಥಿರ ಧ್ರುವ SDL_BlitFunc colorkey_blit_2b[] = {
    (SDL_BlitFunc)ರಿಕ್ತ, Blit2bto1_ಕೀಲಿ, Blit2bto2_ಕೀಲಿ, Blit2bto3_ಕೀಲಿ, Blit2bto4_ಕೀಲಿ
};



ಸ್ಥಿರ ಶೂನ್ಯ Blit4bto1(SDL_BlitInfo *info) {
    BlitBto1(info, 4);
}

ಸ್ಥಿರ ಶೂನ್ಯ Blit4bto2(SDL_BlitInfo *info) {
    BlitBto2(info, 4);
}

ಸ್ಥಿರ ಶೂನ್ಯ Blit4bto3(SDL_BlitInfo *info) {
    BlitBto3(info, 4);
}

ಸ್ಥಿರ ಶೂನ್ಯ Blit4bto4(SDL_BlitInfo *info) {
    BlitBto4(info, 4);
}

ಸ್ಥಿರ ಧ್ರುವ SDL_BlitFunc bitmap_blit_4b[] = {
    (SDL_BlitFunc)ರಿಕ್ತ, Blit4bto1, Blit4bto2, Blit4bto3, Blit4bto4
};

ಸ್ಥಿರ ಶೂನ್ಯ Blit4bto1_ಕೀಲಿ(SDL_BlitInfo *info) {
    Blit_Bto1_ಕೀಲಿ(info, 4);
}

ಸ್ಥಿರ ಶೂನ್ಯ Blit4bto2_ಕೀಲಿ(SDL_BlitInfo *info) {
    Blit_Bto2_ಕೀಲಿ(info, 4);
}

ಸ್ಥಿರ ಶೂನ್ಯ Blit4bto3_ಕೀಲಿ(SDL_BlitInfo *info) {
    Blit_Bto3_ಕೀಲಿ(info, 4);
}

ಸ್ಥಿರ ಶೂನ್ಯ Blit4bto4_ಕೀಲಿ(SDL_BlitInfo *info) {
    Blit_Bto4_ಕೀಲಿ(info, 4);
}

ಸ್ಥಿರ ಧ್ರುವ SDL_BlitFunc colorkey_blit_4b[] = {
    (SDL_BlitFunc)ರಿಕ್ತ, Blit4bto1_ಕೀಲಿ, Blit4bto2_ಕೀಲಿ, Blit4bto3_ಕೀಲಿ, Blit4bto4_ಕೀಲಿ
};



SDL_BlitFunc SDL_CalculateBlit0(SDL_Surface *surface)
{
    ಪೂರ್ಣಾಙ್ಕ which;

    ಯದಿ (SDL_BITSPERPIXEL(surface->map.info.dst_fmt->format) < 8) {
        which = 0;
    } ಅನ್ಯಥಾ {
        which = SDL_BYTESPERPIXEL(surface->map.info.dst_fmt->format);
    }

    ಯದಿ (SDL_PIXELTYPE(surface->format) == SDL_PIXELTYPE_INDEX1) {
        ವಿಕಲ್ಪ (surface->map.info.flags & ~SDL_COPY_RLE_MASK) {
        ಪಕ್ಷ 0:
            ಯದಿ (which < SDL_arraysize(bitmap_blit_1b)) {
                ಪ್ರತ್ಯಾಗಮ bitmap_blit_1b[which];
            }
            ಭಙ್ಗ;

        ಪಕ್ಷ SDL_COPY_COLORKEY:
            ಯದಿ (which < SDL_arraysize(colorkey_blit_1b)) {
                ಪ್ರತ್ಯಾಗಮ colorkey_blit_1b[which];
            }
            ಭಙ್ಗ;

        ಪಕ್ಷ SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            ಪ್ರತ್ಯಾಗಮ which >= 2 ? BlitBtoNAlpha : (SDL_BlitFunc)ರಿಕ್ತ;

        ಪಕ್ಷ SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            ಪ್ರತ್ಯಾಗಮ which >= 2 ? Blit_Bto_NAlpha_ಕೀಲಿ : (SDL_BlitFunc)ರಿಕ್ತ;
        }
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    ಯದಿ (SDL_PIXELTYPE(surface->format) == SDL_PIXELTYPE_INDEX2) {
        ವಿಕಲ್ಪ (surface->map.info.flags & ~SDL_COPY_RLE_MASK) {
        ಪಕ್ಷ 0:
            ಯದಿ (which < SDL_arraysize(bitmap_blit_2b)) {
                ಪ್ರತ್ಯಾಗಮ bitmap_blit_2b[which];
            }
            ಭಙ್ಗ;

        ಪಕ್ಷ SDL_COPY_COLORKEY:
            ಯದಿ (which < SDL_arraysize(colorkey_blit_2b)) {
                ಪ್ರತ್ಯಾಗಮ colorkey_blit_2b[which];
            }
            ಭಙ್ಗ;

        ಪಕ್ಷ SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            ಪ್ರತ್ಯಾಗಮ which >= 2 ? BlitBtoNAlpha : (SDL_BlitFunc)ರಿಕ್ತ;

        ಪಕ್ಷ SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            ಪ್ರತ್ಯಾಗಮ which >= 2 ? Blit_Bto_NAlpha_ಕೀಲಿ : (SDL_BlitFunc)ರಿಕ್ತ;
        }
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    ಯದಿ (SDL_PIXELTYPE(surface->format) == SDL_PIXELTYPE_INDEX4) {
        ವಿಕಲ್ಪ (surface->map.info.flags & ~SDL_COPY_RLE_MASK) {
        ಪಕ್ಷ 0:
            ಯದಿ (which < SDL_arraysize(bitmap_blit_4b)) {
                ಪ್ರತ್ಯಾಗಮ bitmap_blit_4b[which];
            }
            ಭಙ್ಗ;

        ಪಕ್ಷ SDL_COPY_COLORKEY:
            ಯದಿ (which < SDL_arraysize(colorkey_blit_4b)) {
                ಪ್ರತ್ಯಾಗಮ colorkey_blit_4b[which];
            }
            ಭಙ್ಗ;

        ಪಕ್ಷ SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            ಪ್ರತ್ಯಾಗಮ which >= 2 ? BlitBtoNAlpha : (SDL_BlitFunc)ರಿಕ್ತ;

        ಪಕ್ಷ SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            ಪ್ರತ್ಯಾಗಮ which >= 2 ? Blit_Bto_NAlpha_ಕೀಲಿ : (SDL_BlitFunc)ರಿಕ್ತ;
        }
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

#endif // SDL_HAVE_BLIT_0
