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
#অন্তর্ভাৱ "SDL_internal.h"

#ifdef SDL_HAVE_BLIT_0

#অন্তর্ভাৱ "SDL_surface_c.h"

// Functions to blit from bitmaps to other surfaces

SDL_FORCE_INLINE শূন্য BlitBto1(SDL_BlitInfo *info, ধ্রুৱ Uint32 srcbpp)
{
    ধ্রুৱ Uint32 mask = (1 << srcbpp) - 1;
    ধ্রুৱ Uint32 align = (8 / srcbpp) - 1;

    পূর্ণাঙ্ক c;
    পূর্ণাঙ্ক width, height;
    Uint8 *src, *map, *dst;
    পূর্ণাঙ্ক srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = info->table;

    width += info->leading_skip;

    যদি (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    অন্যথা যদি (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    অন্যথা যদি (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    যদি (map) {
        যদি (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            যেতিয়ালৈ (height--) {
                Uint8 byte = 0, bit;
                বাবে (c = 0; c < info->leading_skip; ++c) {
                    যদি (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                বাবে (; c < width; ++c) {
                    যদি (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte & mask);
                    যদি (1) {
                        *dst = map[bit];
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } অন্যথা {
            যেতিয়ালৈ (height--) {
                Uint8 byte = 0, bit;
                বাবে (c = 0; c < info->leading_skip; ++c) {
                    যদি (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                বাবে (; c < width; ++c) {
                    যদি (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte >> (8 - srcbpp)) & mask;
                    যদি (1) {
                        *dst = map[bit];
                    }
                    dst++;
                    byte <<= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        }
    } অন্যথা {
        যদি (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            যেতিয়ালৈ (height--) {
                Uint8 byte = 0, bit;
                বাবে (c = 0; c < info->leading_skip; ++c) {
                    যদি (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                বাবে (; c < width; ++c) {
                    যদি (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte & mask);
                    যদি (1) {
                        *dst = bit;
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } অন্যথা {
            যেতিয়ালৈ (height--) {
                Uint8 byte = 0, bit;
                বাবে (c = 0; c < info->leading_skip; ++c) {
                    যদি (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                বাবে (; c < width; ++c) {
                    যদি (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte >> (8 - srcbpp)) & mask;
                    যদি (1) {
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

SDL_FORCE_INLINE শূন্য BlitBto2(SDL_BlitInfo *info, ধ্রুৱ Uint32 srcbpp)
{
    ধ্রুৱ Uint32 mask = (1 << srcbpp) - 1;
    ধ্রুৱ Uint32 align = (8 / srcbpp) - 1;

    পূর্ণাঙ্ক c;
    পূর্ণাঙ্ক width, height;
    Uint8 *src;
    Uint16 *map, *dst;
    পূর্ণাঙ্ক srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = (Uint16 *)info->dst;
    dstskip = info->dst_skip / 2;
    map = (Uint16 *)info->table;

    width += info->leading_skip;

    যদি (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    অন্যথা যদি (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    অন্যথা যদি (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    যদি (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        যেতিয়ালৈ (height--) {
            Uint8 byte = 0, bit;
            বাবে (c = 0; c < info->leading_skip; ++c) {
                যদি (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            বাবে (; c < width; ++c) {
                যদি (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                যদি (1) {
                    *dst = map[bit];
                }
                byte >>= srcbpp;
                dst++;
            }
            src += srcskip;
            dst += dstskip;
        }
    } অন্যথা {
        যেতিয়ালৈ (height--) {
            Uint8 byte = 0, bit;
            বাবে (c = 0; c < info->leading_skip; ++c) {
                যদি (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            বাবে (; c < width; ++c) {
                যদি (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                যদি (1) {
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

SDL_FORCE_INLINE শূন্য BlitBto3(SDL_BlitInfo *info, ধ্রুৱ Uint32 srcbpp)
{
    ধ্রুৱ Uint32 mask = (1 << srcbpp) - 1;
    ধ্রুৱ Uint32 align = (8 / srcbpp) - 1;

    পূর্ণাঙ্ক c, o;
    পূর্ণাঙ্ক width, height;
    Uint8 *src, *map, *dst;
    পূর্ণাঙ্ক srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = info->table;

    width += info->leading_skip;

    যদি (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    অন্যথা যদি (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    অন্যথা যদি (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    যদি (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        যেতিয়ালৈ (height--) {
            Uint8 byte = 0, bit;
            বাবে (c = 0; c < info->leading_skip; ++c) {
                যদি (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            বাবে (; c < width; ++c) {
                যদি (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                যদি (1) {
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
    } অন্যথা {
        যেতিয়ালৈ (height--) {
            Uint8 byte = 0, bit;
            বাবে (c = 0; c < info->leading_skip; ++c) {
                যদি (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            বাবে (; c < width; ++c) {
                যদি (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                যদি (1) {
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

SDL_FORCE_INLINE শূন্য BlitBto4(SDL_BlitInfo *info, ধ্রুৱ Uint32 srcbpp)
{
    ধ্রুৱ Uint32 mask = (1 << srcbpp) - 1;
    ধ্রুৱ Uint32 align = (8 / srcbpp) - 1;

    পূর্ণাঙ্ক width, height;
    Uint8 *src;
    Uint32 *map, *dst;
    পূর্ণাঙ্ক srcskip, dstskip;
    পূর্ণাঙ্ক c;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = (Uint32 *)info->dst;
    dstskip = info->dst_skip / 4;
    map = (Uint32 *)info->table;

    width += info->leading_skip;

    যদি (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    অন্যথা যদি (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    অন্যথা যদি (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    যদি (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        যেতিয়ালৈ (height--) {
            Uint8 byte = 0, bit;
            বাবে (c = 0; c < info->leading_skip; ++c) {
                যদি (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            বাবে (; c < width; ++c) {
                যদি (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                যদি (1) {
                    *dst = map[bit];
                }
                byte >>= srcbpp;
                dst++;
            }
            src += srcskip;
            dst += dstskip;
        }
    } অন্যথা {
        যেতিয়ালৈ (height--) {
            Uint8 byte = 0, bit;
            বাবে (c = 0; c < info->leading_skip; ++c) {
                যদি (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            বাবে (; c < width; ++c) {
                যদি (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                যদি (1) {
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

SDL_FORCE_INLINE শূন্য Blit_Bto1_চাবি(SDL_BlitInfo *info, ধ্রুৱ Uint32 srcbpp)
{
    ধ্রুৱ Uint32 mask = (1 << srcbpp) - 1;
    ধ্রুৱ Uint32 align = (8 / srcbpp) - 1;

    পূর্ণাঙ্ক width = info->dst_w;
    পূর্ণাঙ্ক height = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    পূর্ণাঙ্ক srcskip = info->src_skip;
    পূর্ণাঙ্ক dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->table;
    পূর্ণাঙ্ক c;

    width += info->leading_skip;

    যদি (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    অন্যথা যদি (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    অন্যথা যদি (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    যদি (palmap) {
        যদি (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            যেতিয়ালৈ (height--) {
                Uint8 byte = 0, bit;
                বাবে (c = 0; c < info->leading_skip; ++c) {
                    যদি (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                বাবে (; c < width; ++c) {
                    যদি (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte & mask);
                    যদি (bit != ckey) {
                        *dst = palmap[bit];
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } অন্যথা {
            যেতিয়ালৈ (height--) {
                Uint8 byte = 0, bit;
                বাবে (c = 0; c < info->leading_skip; ++c) {
                    যদি (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                বাবে (; c < width; ++c) {
                    যদি (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte >> (8 - srcbpp)) & mask;
                    যদি (bit != ckey) {
                        *dst = palmap[bit];
                    }
                    dst++;
                    byte <<= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        }
    } অন্যথা {
        যদি (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            যেতিয়ালৈ (height--) {
                Uint8 byte = 0, bit;
                বাবে (c = 0; c < info->leading_skip; ++c) {
                    যদি (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                বাবে (; c < width; ++c) {
                    যদি (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte & mask);
                    যদি (bit != ckey) {
                        *dst = bit;
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } অন্যথা {
            যেতিয়ালৈ (height--) {
                Uint8 byte = 0, bit;
                বাবে (c = 0; c < info->leading_skip; ++c) {
                    যদি (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                বাবে (; c < width; ++c) {
                    যদি (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte >> (8 - srcbpp)) & mask;
                    যদি (bit != ckey) {
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

SDL_FORCE_INLINE শূন্য Blit_Bto2_চাবি(SDL_BlitInfo *info, ধ্রুৱ Uint32 srcbpp)
{
    ধ্রুৱ Uint32 mask = (1 << srcbpp) - 1;
    ধ্রুৱ Uint32 align = (8 / srcbpp) - 1;

    পূর্ণাঙ্ক width = info->dst_w;
    পূর্ণাঙ্ক height = info->dst_h;
    Uint8 *src = info->src;
    Uint16 *dstp = (Uint16 *)info->dst;
    পূর্ণাঙ্ক srcskip = info->src_skip;
    পূর্ণাঙ্ক dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->table;
    পূর্ণাঙ্ক c;

    width += info->leading_skip;

    যদি (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    অন্যথা যদি (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    অন্যথা যদি (srcbpp == 1)
        srcskip += width - (width + 7) / 8;
    dstskip /= 2;

    যদি (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        যেতিয়ালৈ (height--) {
            Uint8 byte = 0, bit;
            বাবে (c = 0; c < info->leading_skip; ++c) {
                যদি (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            বাবে (; c < width; ++c) {
                যদি (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                যদি (bit != ckey) {
                    *dstp = ((Uint16 *)palmap)[bit];
                }
                byte >>= srcbpp;
                dstp++;
            }
            src += srcskip;
            dstp += dstskip;
        }
    } অন্যথা {
        যেতিয়ালৈ (height--) {
            Uint8 byte = 0, bit;
            বাবে (c = 0; c < info->leading_skip; ++c) {
                যদি (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            বাবে (; c < width; ++c) {
                যদি (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                যদি (bit != ckey) {
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

SDL_FORCE_INLINE শূন্য Blit_Bto3_চাবি(SDL_BlitInfo *info, ধ্রুৱ Uint32 srcbpp)
{
    ধ্রুৱ Uint32 mask = (1 << srcbpp) - 1;
    ধ্রুৱ Uint32 align = (8 / srcbpp) - 1;

    পূর্ণাঙ্ক width = info->dst_w;
    পূর্ণাঙ্ক height = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    পূর্ণাঙ্ক srcskip = info->src_skip;
    পূর্ণাঙ্ক dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->table;
    পূর্ণাঙ্ক c;

    width += info->leading_skip;

    যদি (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    অন্যথা যদি (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    অন্যথা যদি (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    যদি (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        যেতিয়ালৈ (height--) {
            Uint8 byte = 0, bit;
            বাবে (c = 0; c < info->leading_skip; ++c) {
                যদি (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            বাবে (; c < width; ++c) {
                যদি (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                যদি (bit != ckey) {
                    SDL_memcpy(dst, &palmap[bit * 4], 3);
                }
                byte >>= srcbpp;
                dst += 3;
            }
            src += srcskip;
            dst += dstskip;
        }
    } অন্যথা {
        যেতিয়ালৈ (height--) {
            Uint8 byte = 0, bit;
            বাবে (c = 0; c < info->leading_skip; ++c) {
                যদি (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            বাবে (; c < width; ++c) {
                যদি (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                যদি (bit != ckey) {
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

SDL_FORCE_INLINE শূন্য Blit_Bto4_চাবি(SDL_BlitInfo *info, ধ্রুৱ Uint32 srcbpp)
{
    ধ্রুৱ Uint32 mask = (1 << srcbpp) - 1;
    ধ্রুৱ Uint32 align = (8 / srcbpp) - 1;

    পূর্ণাঙ্ক width = info->dst_w;
    পূর্ণাঙ্ক height = info->dst_h;
    Uint8 *src = info->src;
    Uint32 *dstp = (Uint32 *)info->dst;
    পূর্ণাঙ্ক srcskip = info->src_skip;
    পূর্ণাঙ্ক dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->table;
    পূর্ণাঙ্ক c;

    width += info->leading_skip;

    যদি (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    অন্যথা যদি (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    অন্যথা যদি (srcbpp == 1)
        srcskip += width - (width + 7) / 8;
    dstskip /= 4;

    যদি (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        যেতিয়ালৈ (height--) {
            Uint8 byte = 0, bit;
            বাবে (c = 0; c < info->leading_skip; ++c) {
                যদি (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            বাবে (; c < width; ++c) {
                যদি (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                যদি (bit != ckey) {
                    *dstp = ((Uint32 *)palmap)[bit];
                }
                byte >>= srcbpp;
                dstp++;
            }
            src += srcskip;
            dstp += dstskip;
        }
    } অন্যথা {
        যেতিয়ালৈ (height--) {
            Uint8 byte = 0, bit;
            বাবে (c = 0; c < info->leading_skip; ++c) {
                যদি (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            বাবে (; c < width; ++c) {
                যদি (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                যদি (bit != ckey) {
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

স্থির শূন্য BlitBtoNAlpha(SDL_BlitInfo *info)
{
    পূর্ণাঙ্ক width = info->dst_w;
    পূর্ণাঙ্ক height = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    পূর্ণাঙ্ক srcskip = info->src_skip;
    পূর্ণাঙ্ক dstskip = info->dst_skip;
    ধ্রুৱ SDL_Color *srcpal = info->src_pal->colors;
    ধ্রুৱ SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    ধ্রুৱ SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    পূর্ণাঙ্ক srcbpp, dstbpp;
    পূর্ণাঙ্ক c;
    Uint32 pixelvalue, mask, align;
    unsigned sR, sG, sB;
    unsigned dR, dG, dB, dA;
    ধ্রুৱ unsigned A = info->a;

    width += info->leading_skip;

    srcbpp = srcfmt->bytes_per_pixel;
    dstbpp = dstfmt->bytes_per_pixel;
    যদি (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    অন্যথা যদি (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    অন্যথা যদি (srcbpp == 1)
        srcskip += width - (width + 7) / 8;
    mask = (1 << srcbpp) - 1;
    align = (8 / srcbpp) - 1;

    যদি (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        যেতিয়ালৈ (height--) {
            Uint8 byte = 0, bit;
            বাবে (c = 0; c < info->leading_skip; ++c) {
                যদি (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            বাবে (; c < width; ++c) {
                যদি (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                যদি (1) {
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
    } অন্যথা {
        যেতিয়ালৈ (height--) {
            Uint8 byte = 0, bit;
            বাবে (c = 0; c < info->leading_skip; ++c) {
                যদি (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            বাবে (; c < width; ++c) {
                যদি (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                যদি (1) {
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

স্থির শূন্য Blit_Bto_NAlpha_চাবি(SDL_BlitInfo *info)
{
    পূর্ণাঙ্ক width = info->dst_w;
    পূর্ণাঙ্ক height = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    পূর্ণাঙ্ক srcskip = info->src_skip;
    পূর্ণাঙ্ক dstskip = info->dst_skip;
    ধ্রুৱ SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    ধ্রুৱ SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    ধ্রুৱ SDL_Color *srcpal = info->src_pal->colors;
    পূর্ণাঙ্ক srcbpp, dstbpp;
    পূর্ণাঙ্ক c;
    Uint32 pixelvalue, mask, align;
    unsigned sR, sG, sB;
    unsigned dR, dG, dB, dA;
    ধ্রুৱ unsigned A = info->a;
    Uint32 ckey = info->colorkey;

    width += info->leading_skip;

    srcbpp = srcfmt->bytes_per_pixel;
    dstbpp = dstfmt->bytes_per_pixel;
    যদি (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    অন্যথা যদি (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    অন্যথা যদি (srcbpp == 1)
        srcskip += width - (width + 7) / 8;
    mask = (1 << srcbpp) - 1;
    align = (8 / srcbpp) - 1;

    যদি (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        যেতিয়ালৈ (height--) {
            Uint8 byte = 0, bit;
            বাবে (c = 0; c < info->leading_skip; ++c) {
                যদি (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            বাবে (; c < width; ++c) {
                যদি (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                যদি (bit != ckey) {
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
    } অন্যথা {
        যেতিয়ালৈ (height--) {
            Uint8 byte = 0, bit;
            বাবে (c = 0; c < info->leading_skip; ++c) {
                যদি (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            বাবে (; c < width; ++c) {
                যদি (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                যদি (bit != ckey) {
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



স্থির শূন্য Blit1bto1(SDL_BlitInfo *info) {
    BlitBto1(info, 1);
}

স্থির শূন্য Blit1bto2(SDL_BlitInfo *info) {
    BlitBto2(info, 1);
}

স্থির শূন্য Blit1bto3(SDL_BlitInfo *info) {
    BlitBto3(info, 1);
}

স্থির শূন্য Blit1bto4(SDL_BlitInfo *info) {
    BlitBto4(info, 1);
}

স্থির ধ্রুৱ SDL_BlitFunc bitmap_blit_1b[] = {
    (SDL_BlitFunc)রিক্ত, Blit1bto1, Blit1bto2, Blit1bto3, Blit1bto4
};

স্থির শূন্য Blit1bto1_চাবি(SDL_BlitInfo *info) {
    Blit_Bto1_চাবি(info, 1);
}

স্থির শূন্য Blit1bto2_চাবি(SDL_BlitInfo *info) {
    Blit_Bto2_চাবি(info, 1);
}

স্থির শূন্য Blit1bto3_চাবি(SDL_BlitInfo *info) {
    Blit_Bto3_চাবি(info, 1);
}

স্থির শূন্য Blit1bto4_চাবি(SDL_BlitInfo *info) {
    Blit_Bto4_চাবি(info, 1);
}

স্থির ধ্রুৱ SDL_BlitFunc colorkey_blit_1b[] = {
    (SDL_BlitFunc)রিক্ত, Blit1bto1_চাবি, Blit1bto2_চাবি, Blit1bto3_চাবি, Blit1bto4_চাবি
};



স্থির শূন্য Blit2bto1(SDL_BlitInfo *info) {
    BlitBto1(info, 2);
}

স্থির শূন্য Blit2bto2(SDL_BlitInfo *info) {
    BlitBto2(info, 2);
}

স্থির শূন্য Blit2bto3(SDL_BlitInfo *info) {
    BlitBto3(info, 2);
}

স্থির শূন্য Blit2bto4(SDL_BlitInfo *info) {
    BlitBto4(info, 2);
}

স্থির ধ্রুৱ SDL_BlitFunc bitmap_blit_2b[] = {
    (SDL_BlitFunc)রিক্ত, Blit2bto1, Blit2bto2, Blit2bto3, Blit2bto4
};

স্থির শূন্য Blit2bto1_চাবি(SDL_BlitInfo *info) {
    Blit_Bto1_চাবি(info, 2);
}

স্থির শূন্য Blit2bto2_চাবি(SDL_BlitInfo *info) {
    Blit_Bto2_চাবি(info, 2);
}

স্থির শূন্য Blit2bto3_চাবি(SDL_BlitInfo *info) {
    Blit_Bto3_চাবি(info, 2);
}

স্থির শূন্য Blit2bto4_চাবি(SDL_BlitInfo *info) {
    Blit_Bto4_চাবি(info, 2);
}

স্থির ধ্রুৱ SDL_BlitFunc colorkey_blit_2b[] = {
    (SDL_BlitFunc)রিক্ত, Blit2bto1_চাবি, Blit2bto2_চাবি, Blit2bto3_চাবি, Blit2bto4_চাবি
};



স্থির শূন্য Blit4bto1(SDL_BlitInfo *info) {
    BlitBto1(info, 4);
}

স্থির শূন্য Blit4bto2(SDL_BlitInfo *info) {
    BlitBto2(info, 4);
}

স্থির শূন্য Blit4bto3(SDL_BlitInfo *info) {
    BlitBto3(info, 4);
}

স্থির শূন্য Blit4bto4(SDL_BlitInfo *info) {
    BlitBto4(info, 4);
}

স্থির ধ্রুৱ SDL_BlitFunc bitmap_blit_4b[] = {
    (SDL_BlitFunc)রিক্ত, Blit4bto1, Blit4bto2, Blit4bto3, Blit4bto4
};

স্থির শূন্য Blit4bto1_চাবি(SDL_BlitInfo *info) {
    Blit_Bto1_চাবি(info, 4);
}

স্থির শূন্য Blit4bto2_চাবি(SDL_BlitInfo *info) {
    Blit_Bto2_চাবি(info, 4);
}

স্থির শূন্য Blit4bto3_চাবি(SDL_BlitInfo *info) {
    Blit_Bto3_চাবি(info, 4);
}

স্থির শূন্য Blit4bto4_চাবি(SDL_BlitInfo *info) {
    Blit_Bto4_চাবি(info, 4);
}

স্থির ধ্রুৱ SDL_BlitFunc colorkey_blit_4b[] = {
    (SDL_BlitFunc)রিক্ত, Blit4bto1_চাবি, Blit4bto2_চাবি, Blit4bto3_চাবি, Blit4bto4_চাবি
};



SDL_BlitFunc SDL_CalculateBlit0(SDL_Surface *surface)
{
    পূর্ণাঙ্ক which;

    যদি (SDL_BITSPERPIXEL(surface->map.info.dst_fmt->format) < 8) {
        which = 0;
    } অন্যথা {
        which = SDL_BYTESPERPIXEL(surface->map.info.dst_fmt->format);
    }

    যদি (SDL_PIXELTYPE(surface->format) == SDL_PIXELTYPE_INDEX1) {
        ৱিকল্প (surface->map.info.flags & ~SDL_COPY_RLE_MASK) {
        পক্ষ 0:
            যদি (which < SDL_arraysize(bitmap_blit_1b)) {
                ঘূৰাই bitmap_blit_1b[which];
            }
            ভঙ্গ;

        পক্ষ SDL_COPY_COLORKEY:
            যদি (which < SDL_arraysize(colorkey_blit_1b)) {
                ঘূৰাই colorkey_blit_1b[which];
            }
            ভঙ্গ;

        পক্ষ SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            ঘূৰাই which >= 2 ? BlitBtoNAlpha : (SDL_BlitFunc)রিক্ত;

        পক্ষ SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            ঘূৰাই which >= 2 ? Blit_Bto_NAlpha_চাবি : (SDL_BlitFunc)রিক্ত;
        }
        ঘূৰাই রিক্ত;
    }

    যদি (SDL_PIXELTYPE(surface->format) == SDL_PIXELTYPE_INDEX2) {
        ৱিকল্প (surface->map.info.flags & ~SDL_COPY_RLE_MASK) {
        পক্ষ 0:
            যদি (which < SDL_arraysize(bitmap_blit_2b)) {
                ঘূৰাই bitmap_blit_2b[which];
            }
            ভঙ্গ;

        পক্ষ SDL_COPY_COLORKEY:
            যদি (which < SDL_arraysize(colorkey_blit_2b)) {
                ঘূৰাই colorkey_blit_2b[which];
            }
            ভঙ্গ;

        পক্ষ SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            ঘূৰাই which >= 2 ? BlitBtoNAlpha : (SDL_BlitFunc)রিক্ত;

        পক্ষ SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            ঘূৰাই which >= 2 ? Blit_Bto_NAlpha_চাবি : (SDL_BlitFunc)রিক্ত;
        }
        ঘূৰাই রিক্ত;
    }

    যদি (SDL_PIXELTYPE(surface->format) == SDL_PIXELTYPE_INDEX4) {
        ৱিকল্প (surface->map.info.flags & ~SDL_COPY_RLE_MASK) {
        পক্ষ 0:
            যদি (which < SDL_arraysize(bitmap_blit_4b)) {
                ঘূৰাই bitmap_blit_4b[which];
            }
            ভঙ্গ;

        পক্ষ SDL_COPY_COLORKEY:
            যদি (which < SDL_arraysize(colorkey_blit_4b)) {
                ঘূৰাই colorkey_blit_4b[which];
            }
            ভঙ্গ;

        পক্ষ SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            ঘূৰাই which >= 2 ? BlitBtoNAlpha : (SDL_BlitFunc)রিক্ত;

        পক্ষ SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            ঘূৰাই which >= 2 ? Blit_Bto_NAlpha_চাবি : (SDL_BlitFunc)রিক্ত;
        }
        ঘূৰাই রিক্ত;
    }

    ঘূৰাই রিক্ত;
}

#endif // SDL_HAVE_BLIT_0
