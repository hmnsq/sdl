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

#ifdef SDL_HAVE_BLIT_0

#ضمن "SDL_surface_c.h"

// Functions to blit from bitmaps to other surfaces

SDL_FORCE_INLINE فراغ BlitBto1(SDL_BlitInfo *info, ثابت Uint32 srcbpp)
{
    ثابت Uint32 mask = (1 << srcbpp) - 1;
    ثابت Uint32 align = (8 / srcbpp) - 1;

    صحيح c;
    صحيح width, height;
    Uint8 *src, *map, *dst;
    صحيح srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = info->table;

    width += info->leading_skip;

    إذا (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    وإلا إذا (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    وإلا إذا (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    إذا (map) {
        إذا (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            طالما (height--) {
                Uint8 byte = 0, bit;
                لكل (c = 0; c < info->leading_skip; ++c) {
                    إذا (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                لكل (; c < width; ++c) {
                    إذا (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte & mask);
                    إذا (1) {
                        *dst = map[bit];
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } وإلا {
            طالما (height--) {
                Uint8 byte = 0, bit;
                لكل (c = 0; c < info->leading_skip; ++c) {
                    إذا (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                لكل (; c < width; ++c) {
                    إذا (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte >> (8 - srcbpp)) & mask;
                    إذا (1) {
                        *dst = map[bit];
                    }
                    dst++;
                    byte <<= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        }
    } وإلا {
        إذا (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            طالما (height--) {
                Uint8 byte = 0, bit;
                لكل (c = 0; c < info->leading_skip; ++c) {
                    إذا (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                لكل (; c < width; ++c) {
                    إذا (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte & mask);
                    إذا (1) {
                        *dst = bit;
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } وإلا {
            طالما (height--) {
                Uint8 byte = 0, bit;
                لكل (c = 0; c < info->leading_skip; ++c) {
                    إذا (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                لكل (; c < width; ++c) {
                    إذا (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte >> (8 - srcbpp)) & mask;
                    إذا (1) {
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

SDL_FORCE_INLINE فراغ BlitBto2(SDL_BlitInfo *info, ثابت Uint32 srcbpp)
{
    ثابت Uint32 mask = (1 << srcbpp) - 1;
    ثابت Uint32 align = (8 / srcbpp) - 1;

    صحيح c;
    صحيح width, height;
    Uint8 *src;
    Uint16 *map, *dst;
    صحيح srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = (Uint16 *)info->dst;
    dstskip = info->dst_skip / 2;
    map = (Uint16 *)info->table;

    width += info->leading_skip;

    إذا (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    وإلا إذا (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    وإلا إذا (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    إذا (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        طالما (height--) {
            Uint8 byte = 0, bit;
            لكل (c = 0; c < info->leading_skip; ++c) {
                إذا (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            لكل (; c < width; ++c) {
                إذا (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                إذا (1) {
                    *dst = map[bit];
                }
                byte >>= srcbpp;
                dst++;
            }
            src += srcskip;
            dst += dstskip;
        }
    } وإلا {
        طالما (height--) {
            Uint8 byte = 0, bit;
            لكل (c = 0; c < info->leading_skip; ++c) {
                إذا (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            لكل (; c < width; ++c) {
                إذا (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                إذا (1) {
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

SDL_FORCE_INLINE فراغ BlitBto3(SDL_BlitInfo *info, ثابت Uint32 srcbpp)
{
    ثابت Uint32 mask = (1 << srcbpp) - 1;
    ثابت Uint32 align = (8 / srcbpp) - 1;

    صحيح c, o;
    صحيح width, height;
    Uint8 *src, *map, *dst;
    صحيح srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = info->table;

    width += info->leading_skip;

    إذا (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    وإلا إذا (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    وإلا إذا (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    إذا (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        طالما (height--) {
            Uint8 byte = 0, bit;
            لكل (c = 0; c < info->leading_skip; ++c) {
                إذا (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            لكل (; c < width; ++c) {
                إذا (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                إذا (1) {
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
    } وإلا {
        طالما (height--) {
            Uint8 byte = 0, bit;
            لكل (c = 0; c < info->leading_skip; ++c) {
                إذا (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            لكل (; c < width; ++c) {
                إذا (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                إذا (1) {
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

SDL_FORCE_INLINE فراغ BlitBto4(SDL_BlitInfo *info, ثابت Uint32 srcbpp)
{
    ثابت Uint32 mask = (1 << srcbpp) - 1;
    ثابت Uint32 align = (8 / srcbpp) - 1;

    صحيح width, height;
    Uint8 *src;
    Uint32 *map, *dst;
    صحيح srcskip, dstskip;
    صحيح c;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = (Uint32 *)info->dst;
    dstskip = info->dst_skip / 4;
    map = (Uint32 *)info->table;

    width += info->leading_skip;

    إذا (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    وإلا إذا (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    وإلا إذا (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    إذا (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        طالما (height--) {
            Uint8 byte = 0, bit;
            لكل (c = 0; c < info->leading_skip; ++c) {
                إذا (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            لكل (; c < width; ++c) {
                إذا (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                إذا (1) {
                    *dst = map[bit];
                }
                byte >>= srcbpp;
                dst++;
            }
            src += srcskip;
            dst += dstskip;
        }
    } وإلا {
        طالما (height--) {
            Uint8 byte = 0, bit;
            لكل (c = 0; c < info->leading_skip; ++c) {
                إذا (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            لكل (; c < width; ++c) {
                إذا (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                إذا (1) {
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

SDL_FORCE_INLINE فراغ Blit_Bto1_ئاچقۇچ(SDL_BlitInfo *info, ثابت Uint32 srcbpp)
{
    ثابت Uint32 mask = (1 << srcbpp) - 1;
    ثابت Uint32 align = (8 / srcbpp) - 1;

    صحيح width = info->dst_w;
    صحيح height = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    صحيح srcskip = info->src_skip;
    صحيح dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->table;
    صحيح c;

    width += info->leading_skip;

    إذا (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    وإلا إذا (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    وإلا إذا (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    إذا (palmap) {
        إذا (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            طالما (height--) {
                Uint8 byte = 0, bit;
                لكل (c = 0; c < info->leading_skip; ++c) {
                    إذا (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                لكل (; c < width; ++c) {
                    إذا (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte & mask);
                    إذا (bit != ckey) {
                        *dst = palmap[bit];
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } وإلا {
            طالما (height--) {
                Uint8 byte = 0, bit;
                لكل (c = 0; c < info->leading_skip; ++c) {
                    إذا (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                لكل (; c < width; ++c) {
                    إذا (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte >> (8 - srcbpp)) & mask;
                    إذا (bit != ckey) {
                        *dst = palmap[bit];
                    }
                    dst++;
                    byte <<= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        }
    } وإلا {
        إذا (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            طالما (height--) {
                Uint8 byte = 0, bit;
                لكل (c = 0; c < info->leading_skip; ++c) {
                    إذا (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                لكل (; c < width; ++c) {
                    إذا (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte & mask);
                    إذا (bit != ckey) {
                        *dst = bit;
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } وإلا {
            طالما (height--) {
                Uint8 byte = 0, bit;
                لكل (c = 0; c < info->leading_skip; ++c) {
                    إذا (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                لكل (; c < width; ++c) {
                    إذا (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte >> (8 - srcbpp)) & mask;
                    إذا (bit != ckey) {
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

SDL_FORCE_INLINE فراغ Blit_Bto2_ئاچقۇچ(SDL_BlitInfo *info, ثابت Uint32 srcbpp)
{
    ثابت Uint32 mask = (1 << srcbpp) - 1;
    ثابت Uint32 align = (8 / srcbpp) - 1;

    صحيح width = info->dst_w;
    صحيح height = info->dst_h;
    Uint8 *src = info->src;
    Uint16 *dstp = (Uint16 *)info->dst;
    صحيح srcskip = info->src_skip;
    صحيح dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->table;
    صحيح c;

    width += info->leading_skip;

    إذا (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    وإلا إذا (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    وإلا إذا (srcbpp == 1)
        srcskip += width - (width + 7) / 8;
    dstskip /= 2;

    إذا (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        طالما (height--) {
            Uint8 byte = 0, bit;
            لكل (c = 0; c < info->leading_skip; ++c) {
                إذا (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            لكل (; c < width; ++c) {
                إذا (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                إذا (bit != ckey) {
                    *dstp = ((Uint16 *)palmap)[bit];
                }
                byte >>= srcbpp;
                dstp++;
            }
            src += srcskip;
            dstp += dstskip;
        }
    } وإلا {
        طالما (height--) {
            Uint8 byte = 0, bit;
            لكل (c = 0; c < info->leading_skip; ++c) {
                إذا (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            لكل (; c < width; ++c) {
                إذا (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                إذا (bit != ckey) {
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

SDL_FORCE_INLINE فراغ Blit_Bto3_ئاچقۇچ(SDL_BlitInfo *info, ثابت Uint32 srcbpp)
{
    ثابت Uint32 mask = (1 << srcbpp) - 1;
    ثابت Uint32 align = (8 / srcbpp) - 1;

    صحيح width = info->dst_w;
    صحيح height = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    صحيح srcskip = info->src_skip;
    صحيح dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->table;
    صحيح c;

    width += info->leading_skip;

    إذا (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    وإلا إذا (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    وإلا إذا (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    إذا (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        طالما (height--) {
            Uint8 byte = 0, bit;
            لكل (c = 0; c < info->leading_skip; ++c) {
                إذا (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            لكل (; c < width; ++c) {
                إذا (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                إذا (bit != ckey) {
                    SDL_memcpy(dst, &palmap[bit * 4], 3);
                }
                byte >>= srcbpp;
                dst += 3;
            }
            src += srcskip;
            dst += dstskip;
        }
    } وإلا {
        طالما (height--) {
            Uint8 byte = 0, bit;
            لكل (c = 0; c < info->leading_skip; ++c) {
                إذا (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            لكل (; c < width; ++c) {
                إذا (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                إذا (bit != ckey) {
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

SDL_FORCE_INLINE فراغ Blit_Bto4_ئاچقۇچ(SDL_BlitInfo *info, ثابت Uint32 srcbpp)
{
    ثابت Uint32 mask = (1 << srcbpp) - 1;
    ثابت Uint32 align = (8 / srcbpp) - 1;

    صحيح width = info->dst_w;
    صحيح height = info->dst_h;
    Uint8 *src = info->src;
    Uint32 *dstp = (Uint32 *)info->dst;
    صحيح srcskip = info->src_skip;
    صحيح dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->table;
    صحيح c;

    width += info->leading_skip;

    إذا (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    وإلا إذا (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    وإلا إذا (srcbpp == 1)
        srcskip += width - (width + 7) / 8;
    dstskip /= 4;

    إذا (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        طالما (height--) {
            Uint8 byte = 0, bit;
            لكل (c = 0; c < info->leading_skip; ++c) {
                إذا (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            لكل (; c < width; ++c) {
                إذا (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                إذا (bit != ckey) {
                    *dstp = ((Uint32 *)palmap)[bit];
                }
                byte >>= srcbpp;
                dstp++;
            }
            src += srcskip;
            dstp += dstskip;
        }
    } وإلا {
        طالما (height--) {
            Uint8 byte = 0, bit;
            لكل (c = 0; c < info->leading_skip; ++c) {
                إذا (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            لكل (; c < width; ++c) {
                إذا (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                إذا (bit != ckey) {
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

ساكن فراغ BlitBtoNAlpha(SDL_BlitInfo *info)
{
    صحيح width = info->dst_w;
    صحيح height = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    صحيح srcskip = info->src_skip;
    صحيح dstskip = info->dst_skip;
    ثابت SDL_Color *srcpal = info->src_pal->colors;
    ثابت SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    ثابت SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    صحيح srcbpp, dstbpp;
    صحيح c;
    Uint32 pixelvalue, mask, align;
    unsigned sR, sG, sB;
    unsigned dR, dG, dB, dA;
    ثابت unsigned A = info->a;

    width += info->leading_skip;

    srcbpp = srcfmt->bytes_per_pixel;
    dstbpp = dstfmt->bytes_per_pixel;
    إذا (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    وإلا إذا (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    وإلا إذا (srcbpp == 1)
        srcskip += width - (width + 7) / 8;
    mask = (1 << srcbpp) - 1;
    align = (8 / srcbpp) - 1;

    إذا (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        طالما (height--) {
            Uint8 byte = 0, bit;
            لكل (c = 0; c < info->leading_skip; ++c) {
                إذا (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            لكل (; c < width; ++c) {
                إذا (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                إذا (1) {
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
    } وإلا {
        طالما (height--) {
            Uint8 byte = 0, bit;
            لكل (c = 0; c < info->leading_skip; ++c) {
                إذا (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            لكل (; c < width; ++c) {
                إذا (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                إذا (1) {
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

ساكن فراغ Blit_Bto_NAlpha_ئاچقۇچ(SDL_BlitInfo *info)
{
    صحيح width = info->dst_w;
    صحيح height = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    صحيح srcskip = info->src_skip;
    صحيح dstskip = info->dst_skip;
    ثابت SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    ثابت SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    ثابت SDL_Color *srcpal = info->src_pal->colors;
    صحيح srcbpp, dstbpp;
    صحيح c;
    Uint32 pixelvalue, mask, align;
    unsigned sR, sG, sB;
    unsigned dR, dG, dB, dA;
    ثابت unsigned A = info->a;
    Uint32 ckey = info->colorkey;

    width += info->leading_skip;

    srcbpp = srcfmt->bytes_per_pixel;
    dstbpp = dstfmt->bytes_per_pixel;
    إذا (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    وإلا إذا (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    وإلا إذا (srcbpp == 1)
        srcskip += width - (width + 7) / 8;
    mask = (1 << srcbpp) - 1;
    align = (8 / srcbpp) - 1;

    إذا (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        طالما (height--) {
            Uint8 byte = 0, bit;
            لكل (c = 0; c < info->leading_skip; ++c) {
                إذا (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            لكل (; c < width; ++c) {
                إذا (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                إذا (bit != ckey) {
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
    } وإلا {
        طالما (height--) {
            Uint8 byte = 0, bit;
            لكل (c = 0; c < info->leading_skip; ++c) {
                إذا (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            لكل (; c < width; ++c) {
                إذا (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                إذا (bit != ckey) {
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



ساكن فراغ Blit1bto1(SDL_BlitInfo *info) {
    BlitBto1(info, 1);
}

ساكن فراغ Blit1bto2(SDL_BlitInfo *info) {
    BlitBto2(info, 1);
}

ساكن فراغ Blit1bto3(SDL_BlitInfo *info) {
    BlitBto3(info, 1);
}

ساكن فراغ Blit1bto4(SDL_BlitInfo *info) {
    BlitBto4(info, 1);
}

ساكن ثابت SDL_BlitFunc bitmap_blit_1b[] = {
    (SDL_BlitFunc)عدم, Blit1bto1, Blit1bto2, Blit1bto3, Blit1bto4
};

ساكن فراغ Blit1bto1_ئاچقۇچ(SDL_BlitInfo *info) {
    Blit_Bto1_ئاچقۇچ(info, 1);
}

ساكن فراغ Blit1bto2_ئاچقۇچ(SDL_BlitInfo *info) {
    Blit_Bto2_ئاچقۇچ(info, 1);
}

ساكن فراغ Blit1bto3_ئاچقۇچ(SDL_BlitInfo *info) {
    Blit_Bto3_ئاچقۇچ(info, 1);
}

ساكن فراغ Blit1bto4_ئاچقۇچ(SDL_BlitInfo *info) {
    Blit_Bto4_ئاچقۇچ(info, 1);
}

ساكن ثابت SDL_BlitFunc colorkey_blit_1b[] = {
    (SDL_BlitFunc)عدم, Blit1bto1_ئاچقۇچ, Blit1bto2_ئاچقۇچ, Blit1bto3_ئاچقۇچ, Blit1bto4_ئاچقۇچ
};



ساكن فراغ Blit2bto1(SDL_BlitInfo *info) {
    BlitBto1(info, 2);
}

ساكن فراغ Blit2bto2(SDL_BlitInfo *info) {
    BlitBto2(info, 2);
}

ساكن فراغ Blit2bto3(SDL_BlitInfo *info) {
    BlitBto3(info, 2);
}

ساكن فراغ Blit2bto4(SDL_BlitInfo *info) {
    BlitBto4(info, 2);
}

ساكن ثابت SDL_BlitFunc bitmap_blit_2b[] = {
    (SDL_BlitFunc)عدم, Blit2bto1, Blit2bto2, Blit2bto3, Blit2bto4
};

ساكن فراغ Blit2bto1_ئاچقۇچ(SDL_BlitInfo *info) {
    Blit_Bto1_ئاچقۇچ(info, 2);
}

ساكن فراغ Blit2bto2_ئاچقۇچ(SDL_BlitInfo *info) {
    Blit_Bto2_ئاچقۇچ(info, 2);
}

ساكن فراغ Blit2bto3_ئاچقۇچ(SDL_BlitInfo *info) {
    Blit_Bto3_ئاچقۇچ(info, 2);
}

ساكن فراغ Blit2bto4_ئاچقۇچ(SDL_BlitInfo *info) {
    Blit_Bto4_ئاچقۇچ(info, 2);
}

ساكن ثابت SDL_BlitFunc colorkey_blit_2b[] = {
    (SDL_BlitFunc)عدم, Blit2bto1_ئاچقۇچ, Blit2bto2_ئاچقۇچ, Blit2bto3_ئاچقۇچ, Blit2bto4_ئاچقۇچ
};



ساكن فراغ Blit4bto1(SDL_BlitInfo *info) {
    BlitBto1(info, 4);
}

ساكن فراغ Blit4bto2(SDL_BlitInfo *info) {
    BlitBto2(info, 4);
}

ساكن فراغ Blit4bto3(SDL_BlitInfo *info) {
    BlitBto3(info, 4);
}

ساكن فراغ Blit4bto4(SDL_BlitInfo *info) {
    BlitBto4(info, 4);
}

ساكن ثابت SDL_BlitFunc bitmap_blit_4b[] = {
    (SDL_BlitFunc)عدم, Blit4bto1, Blit4bto2, Blit4bto3, Blit4bto4
};

ساكن فراغ Blit4bto1_ئاچقۇچ(SDL_BlitInfo *info) {
    Blit_Bto1_ئاچقۇچ(info, 4);
}

ساكن فراغ Blit4bto2_ئاچقۇچ(SDL_BlitInfo *info) {
    Blit_Bto2_ئاچقۇچ(info, 4);
}

ساكن فراغ Blit4bto3_ئاچقۇچ(SDL_BlitInfo *info) {
    Blit_Bto3_ئاچقۇچ(info, 4);
}

ساكن فراغ Blit4bto4_ئاچقۇچ(SDL_BlitInfo *info) {
    Blit_Bto4_ئاچقۇچ(info, 4);
}

ساكن ثابت SDL_BlitFunc colorkey_blit_4b[] = {
    (SDL_BlitFunc)عدم, Blit4bto1_ئاچقۇچ, Blit4bto2_ئاچقۇچ, Blit4bto3_ئاچقۇچ, Blit4bto4_ئاچقۇچ
};



SDL_BlitFunc SDL_CalculateBlit0(SDL_Surface *surface)
{
    صحيح which;

    إذا (SDL_BITSPERPIXEL(surface->map.info.dst_fmt->format) < 8) {
        which = 0;
    } وإلا {
        which = SDL_BYTESPERPIXEL(surface->map.info.dst_fmt->format);
    }

    إذا (SDL_PIXELTYPE(surface->format) == SDL_PIXELTYPE_INDEX1) {
        بدل (surface->map.info.flags & ~SDL_COPY_RLE_MASK) {
        حالة 0:
            إذا (which < SDL_arraysize(bitmap_blit_1b)) {
                أرجع bitmap_blit_1b[which];
            }
            اكسر;

        حالة SDL_COPY_COLORKEY:
            إذا (which < SDL_arraysize(colorkey_blit_1b)) {
                أرجع colorkey_blit_1b[which];
            }
            اكسر;

        حالة SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            أرجع which >= 2 ? BlitBtoNAlpha : (SDL_BlitFunc)عدم;

        حالة SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            أرجع which >= 2 ? Blit_Bto_NAlpha_ئاچقۇچ : (SDL_BlitFunc)عدم;
        }
        أرجع عدم;
    }

    إذا (SDL_PIXELTYPE(surface->format) == SDL_PIXELTYPE_INDEX2) {
        بدل (surface->map.info.flags & ~SDL_COPY_RLE_MASK) {
        حالة 0:
            إذا (which < SDL_arraysize(bitmap_blit_2b)) {
                أرجع bitmap_blit_2b[which];
            }
            اكسر;

        حالة SDL_COPY_COLORKEY:
            إذا (which < SDL_arraysize(colorkey_blit_2b)) {
                أرجع colorkey_blit_2b[which];
            }
            اكسر;

        حالة SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            أرجع which >= 2 ? BlitBtoNAlpha : (SDL_BlitFunc)عدم;

        حالة SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            أرجع which >= 2 ? Blit_Bto_NAlpha_ئاچقۇچ : (SDL_BlitFunc)عدم;
        }
        أرجع عدم;
    }

    إذا (SDL_PIXELTYPE(surface->format) == SDL_PIXELTYPE_INDEX4) {
        بدل (surface->map.info.flags & ~SDL_COPY_RLE_MASK) {
        حالة 0:
            إذا (which < SDL_arraysize(bitmap_blit_4b)) {
                أرجع bitmap_blit_4b[which];
            }
            اكسر;

        حالة SDL_COPY_COLORKEY:
            إذا (which < SDL_arraysize(colorkey_blit_4b)) {
                أرجع colorkey_blit_4b[which];
            }
            اكسر;

        حالة SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            أرجع which >= 2 ? BlitBtoNAlpha : (SDL_BlitFunc)عدم;

        حالة SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            أرجع which >= 2 ? Blit_Bto_NAlpha_ئاچقۇچ : (SDL_BlitFunc)عدم;
        }
        أرجع عدم;
    }

    أرجع عدم;
}

#endif // SDL_HAVE_BLIT_0
