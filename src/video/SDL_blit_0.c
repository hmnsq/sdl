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

#ifdef SDL_HAVE_BLIT_0

#شامل "SDL_surface_c.h"

// Functions to blit from bitmaps to other surfaces

SDL_FORCE_INLINE تهی BlitBto1(SDL_BlitInfo *info, ثابت Uint32 srcbpp)
{
    ثابت Uint32 mask = (1 << srcbpp) - 1;
    ثابت Uint32 align = (8 / srcbpp) - 1;

    صحیح c;
    صحیح width, height;
    Uint8 *src, *map, *dst;
    صحیح srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = info->table;

    width += info->leading_skip;

    اگر (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    وگرنه اگر (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    وگرنه اگر (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    اگر (map) {
        اگر (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            وقتی (height--) {
                Uint8 byte = 0, bit;
                برای (c = 0; c < info->leading_skip; ++c) {
                    اگر (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                برای (; c < width; ++c) {
                    اگر (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte & mask);
                    اگر (1) {
                        *dst = map[bit];
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } وگرنه {
            وقتی (height--) {
                Uint8 byte = 0, bit;
                برای (c = 0; c < info->leading_skip; ++c) {
                    اگر (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                برای (; c < width; ++c) {
                    اگر (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte >> (8 - srcbpp)) & mask;
                    اگر (1) {
                        *dst = map[bit];
                    }
                    dst++;
                    byte <<= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        }
    } وگرنه {
        اگر (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            وقتی (height--) {
                Uint8 byte = 0, bit;
                برای (c = 0; c < info->leading_skip; ++c) {
                    اگر (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                برای (; c < width; ++c) {
                    اگر (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte & mask);
                    اگر (1) {
                        *dst = bit;
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } وگرنه {
            وقتی (height--) {
                Uint8 byte = 0, bit;
                برای (c = 0; c < info->leading_skip; ++c) {
                    اگر (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                برای (; c < width; ++c) {
                    اگر (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte >> (8 - srcbpp)) & mask;
                    اگر (1) {
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

SDL_FORCE_INLINE تهی BlitBto2(SDL_BlitInfo *info, ثابت Uint32 srcbpp)
{
    ثابت Uint32 mask = (1 << srcbpp) - 1;
    ثابت Uint32 align = (8 / srcbpp) - 1;

    صحیح c;
    صحیح width, height;
    Uint8 *src;
    Uint16 *map, *dst;
    صحیح srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = (Uint16 *)info->dst;
    dstskip = info->dst_skip / 2;
    map = (Uint16 *)info->table;

    width += info->leading_skip;

    اگر (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    وگرنه اگر (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    وگرنه اگر (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    اگر (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        وقتی (height--) {
            Uint8 byte = 0, bit;
            برای (c = 0; c < info->leading_skip; ++c) {
                اگر (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            برای (; c < width; ++c) {
                اگر (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                اگر (1) {
                    *dst = map[bit];
                }
                byte >>= srcbpp;
                dst++;
            }
            src += srcskip;
            dst += dstskip;
        }
    } وگرنه {
        وقتی (height--) {
            Uint8 byte = 0, bit;
            برای (c = 0; c < info->leading_skip; ++c) {
                اگر (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            برای (; c < width; ++c) {
                اگر (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                اگر (1) {
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

SDL_FORCE_INLINE تهی BlitBto3(SDL_BlitInfo *info, ثابت Uint32 srcbpp)
{
    ثابت Uint32 mask = (1 << srcbpp) - 1;
    ثابت Uint32 align = (8 / srcbpp) - 1;

    صحیح c, o;
    صحیح width, height;
    Uint8 *src, *map, *dst;
    صحیح srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = info->table;

    width += info->leading_skip;

    اگر (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    وگرنه اگر (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    وگرنه اگر (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    اگر (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        وقتی (height--) {
            Uint8 byte = 0, bit;
            برای (c = 0; c < info->leading_skip; ++c) {
                اگر (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            برای (; c < width; ++c) {
                اگر (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                اگر (1) {
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
    } وگرنه {
        وقتی (height--) {
            Uint8 byte = 0, bit;
            برای (c = 0; c < info->leading_skip; ++c) {
                اگر (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            برای (; c < width; ++c) {
                اگر (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                اگر (1) {
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

SDL_FORCE_INLINE تهی BlitBto4(SDL_BlitInfo *info, ثابت Uint32 srcbpp)
{
    ثابت Uint32 mask = (1 << srcbpp) - 1;
    ثابت Uint32 align = (8 / srcbpp) - 1;

    صحیح width, height;
    Uint8 *src;
    Uint32 *map, *dst;
    صحیح srcskip, dstskip;
    صحیح c;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = (Uint32 *)info->dst;
    dstskip = info->dst_skip / 4;
    map = (Uint32 *)info->table;

    width += info->leading_skip;

    اگر (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    وگرنه اگر (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    وگرنه اگر (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    اگر (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        وقتی (height--) {
            Uint8 byte = 0, bit;
            برای (c = 0; c < info->leading_skip; ++c) {
                اگر (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            برای (; c < width; ++c) {
                اگر (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                اگر (1) {
                    *dst = map[bit];
                }
                byte >>= srcbpp;
                dst++;
            }
            src += srcskip;
            dst += dstskip;
        }
    } وگرنه {
        وقتی (height--) {
            Uint8 byte = 0, bit;
            برای (c = 0; c < info->leading_skip; ++c) {
                اگر (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            برای (; c < width; ++c) {
                اگر (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                اگر (1) {
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

SDL_FORCE_INLINE تهی Blit_Bto1_کلید(SDL_BlitInfo *info, ثابت Uint32 srcbpp)
{
    ثابت Uint32 mask = (1 << srcbpp) - 1;
    ثابت Uint32 align = (8 / srcbpp) - 1;

    صحیح width = info->dst_w;
    صحیح height = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    صحیح srcskip = info->src_skip;
    صحیح dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->table;
    صحیح c;

    width += info->leading_skip;

    اگر (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    وگرنه اگر (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    وگرنه اگر (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    اگر (palmap) {
        اگر (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            وقتی (height--) {
                Uint8 byte = 0, bit;
                برای (c = 0; c < info->leading_skip; ++c) {
                    اگر (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                برای (; c < width; ++c) {
                    اگر (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte & mask);
                    اگر (bit != ckey) {
                        *dst = palmap[bit];
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } وگرنه {
            وقتی (height--) {
                Uint8 byte = 0, bit;
                برای (c = 0; c < info->leading_skip; ++c) {
                    اگر (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                برای (; c < width; ++c) {
                    اگر (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte >> (8 - srcbpp)) & mask;
                    اگر (bit != ckey) {
                        *dst = palmap[bit];
                    }
                    dst++;
                    byte <<= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        }
    } وگرنه {
        اگر (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            وقتی (height--) {
                Uint8 byte = 0, bit;
                برای (c = 0; c < info->leading_skip; ++c) {
                    اگر (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                برای (; c < width; ++c) {
                    اگر (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte & mask);
                    اگر (bit != ckey) {
                        *dst = bit;
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } وگرنه {
            وقتی (height--) {
                Uint8 byte = 0, bit;
                برای (c = 0; c < info->leading_skip; ++c) {
                    اگر (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                برای (; c < width; ++c) {
                    اگر (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte >> (8 - srcbpp)) & mask;
                    اگر (bit != ckey) {
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

SDL_FORCE_INLINE تهی Blit_Bto2_کلید(SDL_BlitInfo *info, ثابت Uint32 srcbpp)
{
    ثابت Uint32 mask = (1 << srcbpp) - 1;
    ثابت Uint32 align = (8 / srcbpp) - 1;

    صحیح width = info->dst_w;
    صحیح height = info->dst_h;
    Uint8 *src = info->src;
    Uint16 *dstp = (Uint16 *)info->dst;
    صحیح srcskip = info->src_skip;
    صحیح dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->table;
    صحیح c;

    width += info->leading_skip;

    اگر (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    وگرنه اگر (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    وگرنه اگر (srcbpp == 1)
        srcskip += width - (width + 7) / 8;
    dstskip /= 2;

    اگر (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        وقتی (height--) {
            Uint8 byte = 0, bit;
            برای (c = 0; c < info->leading_skip; ++c) {
                اگر (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            برای (; c < width; ++c) {
                اگر (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                اگر (bit != ckey) {
                    *dstp = ((Uint16 *)palmap)[bit];
                }
                byte >>= srcbpp;
                dstp++;
            }
            src += srcskip;
            dstp += dstskip;
        }
    } وگرنه {
        وقتی (height--) {
            Uint8 byte = 0, bit;
            برای (c = 0; c < info->leading_skip; ++c) {
                اگر (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            برای (; c < width; ++c) {
                اگر (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                اگر (bit != ckey) {
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

SDL_FORCE_INLINE تهی Blit_Bto3_کلید(SDL_BlitInfo *info, ثابت Uint32 srcbpp)
{
    ثابت Uint32 mask = (1 << srcbpp) - 1;
    ثابت Uint32 align = (8 / srcbpp) - 1;

    صحیح width = info->dst_w;
    صحیح height = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    صحیح srcskip = info->src_skip;
    صحیح dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->table;
    صحیح c;

    width += info->leading_skip;

    اگر (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    وگرنه اگر (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    وگرنه اگر (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    اگر (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        وقتی (height--) {
            Uint8 byte = 0, bit;
            برای (c = 0; c < info->leading_skip; ++c) {
                اگر (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            برای (; c < width; ++c) {
                اگر (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                اگر (bit != ckey) {
                    SDL_memcpy(dst, &palmap[bit * 4], 3);
                }
                byte >>= srcbpp;
                dst += 3;
            }
            src += srcskip;
            dst += dstskip;
        }
    } وگرنه {
        وقتی (height--) {
            Uint8 byte = 0, bit;
            برای (c = 0; c < info->leading_skip; ++c) {
                اگر (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            برای (; c < width; ++c) {
                اگر (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                اگر (bit != ckey) {
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

SDL_FORCE_INLINE تهی Blit_Bto4_کلید(SDL_BlitInfo *info, ثابت Uint32 srcbpp)
{
    ثابت Uint32 mask = (1 << srcbpp) - 1;
    ثابت Uint32 align = (8 / srcbpp) - 1;

    صحیح width = info->dst_w;
    صحیح height = info->dst_h;
    Uint8 *src = info->src;
    Uint32 *dstp = (Uint32 *)info->dst;
    صحیح srcskip = info->src_skip;
    صحیح dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->table;
    صحیح c;

    width += info->leading_skip;

    اگر (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    وگرنه اگر (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    وگرنه اگر (srcbpp == 1)
        srcskip += width - (width + 7) / 8;
    dstskip /= 4;

    اگر (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        وقتی (height--) {
            Uint8 byte = 0, bit;
            برای (c = 0; c < info->leading_skip; ++c) {
                اگر (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            برای (; c < width; ++c) {
                اگر (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                اگر (bit != ckey) {
                    *dstp = ((Uint32 *)palmap)[bit];
                }
                byte >>= srcbpp;
                dstp++;
            }
            src += srcskip;
            dstp += dstskip;
        }
    } وگرنه {
        وقتی (height--) {
            Uint8 byte = 0, bit;
            برای (c = 0; c < info->leading_skip; ++c) {
                اگر (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            برای (; c < width; ++c) {
                اگر (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                اگر (bit != ckey) {
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

ایستا تهی BlitBtoNAlpha(SDL_BlitInfo *info)
{
    صحیح width = info->dst_w;
    صحیح height = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    صحیح srcskip = info->src_skip;
    صحیح dstskip = info->dst_skip;
    ثابت SDL_Color *srcpal = info->src_pal->colors;
    ثابت SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    ثابت SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    صحیح srcbpp, dstbpp;
    صحیح c;
    Uint32 pixelvalue, mask, align;
    unsigned sR, sG, sB;
    unsigned dR, dG, dB, dA;
    ثابت unsigned A = info->a;

    width += info->leading_skip;

    srcbpp = srcfmt->bytes_per_pixel;
    dstbpp = dstfmt->bytes_per_pixel;
    اگر (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    وگرنه اگر (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    وگرنه اگر (srcbpp == 1)
        srcskip += width - (width + 7) / 8;
    mask = (1 << srcbpp) - 1;
    align = (8 / srcbpp) - 1;

    اگر (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        وقتی (height--) {
            Uint8 byte = 0, bit;
            برای (c = 0; c < info->leading_skip; ++c) {
                اگر (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            برای (; c < width; ++c) {
                اگر (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                اگر (1) {
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
    } وگرنه {
        وقتی (height--) {
            Uint8 byte = 0, bit;
            برای (c = 0; c < info->leading_skip; ++c) {
                اگر (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            برای (; c < width; ++c) {
                اگر (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                اگر (1) {
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

ایستا تهی Blit_Bto_NAlpha_کلید(SDL_BlitInfo *info)
{
    صحیح width = info->dst_w;
    صحیح height = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    صحیح srcskip = info->src_skip;
    صحیح dstskip = info->dst_skip;
    ثابت SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    ثابت SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    ثابت SDL_Color *srcpal = info->src_pal->colors;
    صحیح srcbpp, dstbpp;
    صحیح c;
    Uint32 pixelvalue, mask, align;
    unsigned sR, sG, sB;
    unsigned dR, dG, dB, dA;
    ثابت unsigned A = info->a;
    Uint32 ckey = info->colorkey;

    width += info->leading_skip;

    srcbpp = srcfmt->bytes_per_pixel;
    dstbpp = dstfmt->bytes_per_pixel;
    اگر (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    وگرنه اگر (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    وگرنه اگر (srcbpp == 1)
        srcskip += width - (width + 7) / 8;
    mask = (1 << srcbpp) - 1;
    align = (8 / srcbpp) - 1;

    اگر (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        وقتی (height--) {
            Uint8 byte = 0, bit;
            برای (c = 0; c < info->leading_skip; ++c) {
                اگر (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            برای (; c < width; ++c) {
                اگر (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                اگر (bit != ckey) {
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
    } وگرنه {
        وقتی (height--) {
            Uint8 byte = 0, bit;
            برای (c = 0; c < info->leading_skip; ++c) {
                اگر (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            برای (; c < width; ++c) {
                اگر (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                اگر (bit != ckey) {
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



ایستا تهی Blit1bto1(SDL_BlitInfo *info) {
    BlitBto1(info, 1);
}

ایستا تهی Blit1bto2(SDL_BlitInfo *info) {
    BlitBto2(info, 1);
}

ایستا تهی Blit1bto3(SDL_BlitInfo *info) {
    BlitBto3(info, 1);
}

ایستا تهی Blit1bto4(SDL_BlitInfo *info) {
    BlitBto4(info, 1);
}

ایستا ثابت SDL_BlitFunc bitmap_blit_1b[] = {
    (SDL_BlitFunc)پوچ, Blit1bto1, Blit1bto2, Blit1bto3, Blit1bto4
};

ایستا تهی Blit1bto1_کلید(SDL_BlitInfo *info) {
    Blit_Bto1_کلید(info, 1);
}

ایستا تهی Blit1bto2_کلید(SDL_BlitInfo *info) {
    Blit_Bto2_کلید(info, 1);
}

ایستا تهی Blit1bto3_کلید(SDL_BlitInfo *info) {
    Blit_Bto3_کلید(info, 1);
}

ایستا تهی Blit1bto4_کلید(SDL_BlitInfo *info) {
    Blit_Bto4_کلید(info, 1);
}

ایستا ثابت SDL_BlitFunc colorkey_blit_1b[] = {
    (SDL_BlitFunc)پوچ, Blit1bto1_کلید, Blit1bto2_کلید, Blit1bto3_کلید, Blit1bto4_کلید
};



ایستا تهی Blit2bto1(SDL_BlitInfo *info) {
    BlitBto1(info, 2);
}

ایستا تهی Blit2bto2(SDL_BlitInfo *info) {
    BlitBto2(info, 2);
}

ایستا تهی Blit2bto3(SDL_BlitInfo *info) {
    BlitBto3(info, 2);
}

ایستا تهی Blit2bto4(SDL_BlitInfo *info) {
    BlitBto4(info, 2);
}

ایستا ثابت SDL_BlitFunc bitmap_blit_2b[] = {
    (SDL_BlitFunc)پوچ, Blit2bto1, Blit2bto2, Blit2bto3, Blit2bto4
};

ایستا تهی Blit2bto1_کلید(SDL_BlitInfo *info) {
    Blit_Bto1_کلید(info, 2);
}

ایستا تهی Blit2bto2_کلید(SDL_BlitInfo *info) {
    Blit_Bto2_کلید(info, 2);
}

ایستا تهی Blit2bto3_کلید(SDL_BlitInfo *info) {
    Blit_Bto3_کلید(info, 2);
}

ایستا تهی Blit2bto4_کلید(SDL_BlitInfo *info) {
    Blit_Bto4_کلید(info, 2);
}

ایستا ثابت SDL_BlitFunc colorkey_blit_2b[] = {
    (SDL_BlitFunc)پوچ, Blit2bto1_کلید, Blit2bto2_کلید, Blit2bto3_کلید, Blit2bto4_کلید
};



ایستا تهی Blit4bto1(SDL_BlitInfo *info) {
    BlitBto1(info, 4);
}

ایستا تهی Blit4bto2(SDL_BlitInfo *info) {
    BlitBto2(info, 4);
}

ایستا تهی Blit4bto3(SDL_BlitInfo *info) {
    BlitBto3(info, 4);
}

ایستا تهی Blit4bto4(SDL_BlitInfo *info) {
    BlitBto4(info, 4);
}

ایستا ثابت SDL_BlitFunc bitmap_blit_4b[] = {
    (SDL_BlitFunc)پوچ, Blit4bto1, Blit4bto2, Blit4bto3, Blit4bto4
};

ایستا تهی Blit4bto1_کلید(SDL_BlitInfo *info) {
    Blit_Bto1_کلید(info, 4);
}

ایستا تهی Blit4bto2_کلید(SDL_BlitInfo *info) {
    Blit_Bto2_کلید(info, 4);
}

ایستا تهی Blit4bto3_کلید(SDL_BlitInfo *info) {
    Blit_Bto3_کلید(info, 4);
}

ایستا تهی Blit4bto4_کلید(SDL_BlitInfo *info) {
    Blit_Bto4_کلید(info, 4);
}

ایستا ثابت SDL_BlitFunc colorkey_blit_4b[] = {
    (SDL_BlitFunc)پوچ, Blit4bto1_کلید, Blit4bto2_کلید, Blit4bto3_کلید, Blit4bto4_کلید
};



SDL_BlitFunc SDL_CalculateBlit0(SDL_Surface *surface)
{
    صحیح which;

    اگر (SDL_BITSPERPIXEL(surface->map.info.dst_fmt->format) < 8) {
        which = 0;
    } وگرنه {
        which = SDL_BYTESPERPIXEL(surface->map.info.dst_fmt->format);
    }

    اگر (SDL_PIXELTYPE(surface->format) == SDL_PIXELTYPE_INDEX1) {
        انتخاب (surface->map.info.flags & ~SDL_COPY_RLE_MASK) {
        حالت 0:
            اگر (which < SDL_arraysize(bitmap_blit_1b)) {
                بازگشت bitmap_blit_1b[which];
            }
            بشکن;

        حالت SDL_COPY_COLORKEY:
            اگر (which < SDL_arraysize(colorkey_blit_1b)) {
                بازگشت colorkey_blit_1b[which];
            }
            بشکن;

        حالت SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            بازگشت which >= 2 ? BlitBtoNAlpha : (SDL_BlitFunc)پوچ;

        حالت SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            بازگشت which >= 2 ? Blit_Bto_NAlpha_کلید : (SDL_BlitFunc)پوچ;
        }
        بازگشت پوچ;
    }

    اگر (SDL_PIXELTYPE(surface->format) == SDL_PIXELTYPE_INDEX2) {
        انتخاب (surface->map.info.flags & ~SDL_COPY_RLE_MASK) {
        حالت 0:
            اگر (which < SDL_arraysize(bitmap_blit_2b)) {
                بازگشت bitmap_blit_2b[which];
            }
            بشکن;

        حالت SDL_COPY_COLORKEY:
            اگر (which < SDL_arraysize(colorkey_blit_2b)) {
                بازگشت colorkey_blit_2b[which];
            }
            بشکن;

        حالت SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            بازگشت which >= 2 ? BlitBtoNAlpha : (SDL_BlitFunc)پوچ;

        حالت SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            بازگشت which >= 2 ? Blit_Bto_NAlpha_کلید : (SDL_BlitFunc)پوچ;
        }
        بازگشت پوچ;
    }

    اگر (SDL_PIXELTYPE(surface->format) == SDL_PIXELTYPE_INDEX4) {
        انتخاب (surface->map.info.flags & ~SDL_COPY_RLE_MASK) {
        حالت 0:
            اگر (which < SDL_arraysize(bitmap_blit_4b)) {
                بازگشت bitmap_blit_4b[which];
            }
            بشکن;

        حالت SDL_COPY_COLORKEY:
            اگر (which < SDL_arraysize(colorkey_blit_4b)) {
                بازگشت colorkey_blit_4b[which];
            }
            بشکن;

        حالت SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            بازگشت which >= 2 ? BlitBtoNAlpha : (SDL_BlitFunc)پوچ;

        حالت SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            بازگشت which >= 2 ? Blit_Bto_NAlpha_کلید : (SDL_BlitFunc)پوچ;
        }
        بازگشت پوچ;
    }

    بازگشت پوچ;
}

#endif // SDL_HAVE_BLIT_0
