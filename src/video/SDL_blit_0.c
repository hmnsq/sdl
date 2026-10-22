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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifdef SDL_HAVE_BLIT_0

#ଅନ୍ତର୍ଭାଵ "SDL_surface_c.h"

// Functions to blit from bitmaps to other surfaces

SDL_FORCE_INLINE ଶୂନ୍ୟ BlitBto1(SDL_BlitInfo *info, ଅଚଳ Uint32 srcbpp)
{
    ଅଚଳ Uint32 mask = (1 << srcbpp) - 1;
    ଅଚଳ Uint32 align = (8 / srcbpp) - 1;

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା c;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, height;
    Uint8 *src, *map, *dst;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = info->table;

    width += info->leading_skip;

    ଯଦି (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    ଅନ୍ୟଥା ଯଦି (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    ଅନ୍ୟଥା ଯଦି (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    ଯଦି (map) {
        ଯଦି (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            ଯେତେବେଳେ (height--) {
                Uint8 byte = 0, bit;
                ପାଇଁ (c = 0; c < info->leading_skip; ++c) {
                    ଯଦି (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                ପାଇଁ (; c < width; ++c) {
                    ଯଦି (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte & mask);
                    ଯଦି (1) {
                        *dst = map[bit];
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } ଅନ୍ୟଥା {
            ଯେତେବେଳେ (height--) {
                Uint8 byte = 0, bit;
                ପାଇଁ (c = 0; c < info->leading_skip; ++c) {
                    ଯଦି (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                ପାଇଁ (; c < width; ++c) {
                    ଯଦି (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte >> (8 - srcbpp)) & mask;
                    ଯଦି (1) {
                        *dst = map[bit];
                    }
                    dst++;
                    byte <<= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        }
    } ଅନ୍ୟଥା {
        ଯଦି (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            ଯେତେବେଳେ (height--) {
                Uint8 byte = 0, bit;
                ପାଇଁ (c = 0; c < info->leading_skip; ++c) {
                    ଯଦି (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                ପାଇଁ (; c < width; ++c) {
                    ଯଦି (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte & mask);
                    ଯଦି (1) {
                        *dst = bit;
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } ଅନ୍ୟଥା {
            ଯେତେବେଳେ (height--) {
                Uint8 byte = 0, bit;
                ପାଇଁ (c = 0; c < info->leading_skip; ++c) {
                    ଯଦି (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                ପାଇଁ (; c < width; ++c) {
                    ଯଦି (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte >> (8 - srcbpp)) & mask;
                    ଯଦି (1) {
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

SDL_FORCE_INLINE ଶୂନ୍ୟ BlitBto2(SDL_BlitInfo *info, ଅଚଳ Uint32 srcbpp)
{
    ଅଚଳ Uint32 mask = (1 << srcbpp) - 1;
    ଅଚଳ Uint32 align = (8 / srcbpp) - 1;

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା c;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, height;
    Uint8 *src;
    Uint16 *map, *dst;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = (Uint16 *)info->dst;
    dstskip = info->dst_skip / 2;
    map = (Uint16 *)info->table;

    width += info->leading_skip;

    ଯଦି (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    ଅନ୍ୟଥା ଯଦି (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    ଅନ୍ୟଥା ଯଦି (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    ଯଦି (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        ଯେତେବେଳେ (height--) {
            Uint8 byte = 0, bit;
            ପାଇଁ (c = 0; c < info->leading_skip; ++c) {
                ଯଦି (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            ପାଇଁ (; c < width; ++c) {
                ଯଦି (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                ଯଦି (1) {
                    *dst = map[bit];
                }
                byte >>= srcbpp;
                dst++;
            }
            src += srcskip;
            dst += dstskip;
        }
    } ଅନ୍ୟଥା {
        ଯେତେବେଳେ (height--) {
            Uint8 byte = 0, bit;
            ପାଇଁ (c = 0; c < info->leading_skip; ++c) {
                ଯଦି (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            ପାଇଁ (; c < width; ++c) {
                ଯଦି (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                ଯଦି (1) {
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

SDL_FORCE_INLINE ଶୂନ୍ୟ BlitBto3(SDL_BlitInfo *info, ଅଚଳ Uint32 srcbpp)
{
    ଅଚଳ Uint32 mask = (1 << srcbpp) - 1;
    ଅଚଳ Uint32 align = (8 / srcbpp) - 1;

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା c, o;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, height;
    Uint8 *src, *map, *dst;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = info->table;

    width += info->leading_skip;

    ଯଦି (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    ଅନ୍ୟଥା ଯଦି (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    ଅନ୍ୟଥା ଯଦି (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    ଯଦି (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        ଯେତେବେଳେ (height--) {
            Uint8 byte = 0, bit;
            ପାଇଁ (c = 0; c < info->leading_skip; ++c) {
                ଯଦି (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            ପାଇଁ (; c < width; ++c) {
                ଯଦି (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                ଯଦି (1) {
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
    } ଅନ୍ୟଥା {
        ଯେତେବେଳେ (height--) {
            Uint8 byte = 0, bit;
            ପାଇଁ (c = 0; c < info->leading_skip; ++c) {
                ଯଦି (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            ପାଇଁ (; c < width; ++c) {
                ଯଦି (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                ଯଦି (1) {
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

SDL_FORCE_INLINE ଶୂନ୍ୟ BlitBto4(SDL_BlitInfo *info, ଅଚଳ Uint32 srcbpp)
{
    ଅଚଳ Uint32 mask = (1 << srcbpp) - 1;
    ଅଚଳ Uint32 align = (8 / srcbpp) - 1;

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, height;
    Uint8 *src;
    Uint32 *map, *dst;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା srcskip, dstskip;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା c;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = (Uint32 *)info->dst;
    dstskip = info->dst_skip / 4;
    map = (Uint32 *)info->table;

    width += info->leading_skip;

    ଯଦି (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    ଅନ୍ୟଥା ଯଦି (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    ଅନ୍ୟଥା ଯଦି (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    ଯଦି (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        ଯେତେବେଳେ (height--) {
            Uint8 byte = 0, bit;
            ପାଇଁ (c = 0; c < info->leading_skip; ++c) {
                ଯଦି (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            ପାଇଁ (; c < width; ++c) {
                ଯଦି (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                ଯଦି (1) {
                    *dst = map[bit];
                }
                byte >>= srcbpp;
                dst++;
            }
            src += srcskip;
            dst += dstskip;
        }
    } ଅନ୍ୟଥା {
        ଯେତେବେଳେ (height--) {
            Uint8 byte = 0, bit;
            ପାଇଁ (c = 0; c < info->leading_skip; ++c) {
                ଯଦି (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            ପାଇଁ (; c < width; ++c) {
                ଯଦି (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                ଯଦି (1) {
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

SDL_FORCE_INLINE ଶୂନ୍ୟ Blit_Bto1_ଚାବି(SDL_BlitInfo *info, ଅଚଳ Uint32 srcbpp)
{
    ଅଚଳ Uint32 mask = (1 << srcbpp) - 1;
    ଅଚଳ Uint32 align = (8 / srcbpp) - 1;

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା width = info->dst_w;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା height = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା srcskip = info->src_skip;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->table;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା c;

    width += info->leading_skip;

    ଯଦି (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    ଅନ୍ୟଥା ଯଦି (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    ଅନ୍ୟଥା ଯଦି (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    ଯଦି (palmap) {
        ଯଦି (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            ଯେତେବେଳେ (height--) {
                Uint8 byte = 0, bit;
                ପାଇଁ (c = 0; c < info->leading_skip; ++c) {
                    ଯଦି (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                ପାଇଁ (; c < width; ++c) {
                    ଯଦି (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte & mask);
                    ଯଦି (bit != ckey) {
                        *dst = palmap[bit];
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } ଅନ୍ୟଥା {
            ଯେତେବେଳେ (height--) {
                Uint8 byte = 0, bit;
                ପାଇଁ (c = 0; c < info->leading_skip; ++c) {
                    ଯଦି (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                ପାଇଁ (; c < width; ++c) {
                    ଯଦି (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte >> (8 - srcbpp)) & mask;
                    ଯଦି (bit != ckey) {
                        *dst = palmap[bit];
                    }
                    dst++;
                    byte <<= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        }
    } ଅନ୍ୟଥା {
        ଯଦି (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            ଯେତେବେଳେ (height--) {
                Uint8 byte = 0, bit;
                ପାଇଁ (c = 0; c < info->leading_skip; ++c) {
                    ଯଦି (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                ପାଇଁ (; c < width; ++c) {
                    ଯଦି (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte & mask);
                    ଯଦି (bit != ckey) {
                        *dst = bit;
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } ଅନ୍ୟଥା {
            ଯେତେବେଳେ (height--) {
                Uint8 byte = 0, bit;
                ପାଇଁ (c = 0; c < info->leading_skip; ++c) {
                    ଯଦି (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                ପାଇଁ (; c < width; ++c) {
                    ଯଦି (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte >> (8 - srcbpp)) & mask;
                    ଯଦି (bit != ckey) {
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

SDL_FORCE_INLINE ଶୂନ୍ୟ Blit_Bto2_ଚାବି(SDL_BlitInfo *info, ଅଚଳ Uint32 srcbpp)
{
    ଅଚଳ Uint32 mask = (1 << srcbpp) - 1;
    ଅଚଳ Uint32 align = (8 / srcbpp) - 1;

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା width = info->dst_w;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା height = info->dst_h;
    Uint8 *src = info->src;
    Uint16 *dstp = (Uint16 *)info->dst;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା srcskip = info->src_skip;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->table;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା c;

    width += info->leading_skip;

    ଯଦି (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    ଅନ୍ୟଥା ଯଦି (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    ଅନ୍ୟଥା ଯଦି (srcbpp == 1)
        srcskip += width - (width + 7) / 8;
    dstskip /= 2;

    ଯଦି (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        ଯେତେବେଳେ (height--) {
            Uint8 byte = 0, bit;
            ପାଇଁ (c = 0; c < info->leading_skip; ++c) {
                ଯଦି (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            ପାଇଁ (; c < width; ++c) {
                ଯଦି (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                ଯଦି (bit != ckey) {
                    *dstp = ((Uint16 *)palmap)[bit];
                }
                byte >>= srcbpp;
                dstp++;
            }
            src += srcskip;
            dstp += dstskip;
        }
    } ଅନ୍ୟଥା {
        ଯେତେବେଳେ (height--) {
            Uint8 byte = 0, bit;
            ପାଇଁ (c = 0; c < info->leading_skip; ++c) {
                ଯଦି (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            ପାଇଁ (; c < width; ++c) {
                ଯଦି (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                ଯଦି (bit != ckey) {
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

SDL_FORCE_INLINE ଶୂନ୍ୟ Blit_Bto3_ଚାବି(SDL_BlitInfo *info, ଅଚଳ Uint32 srcbpp)
{
    ଅଚଳ Uint32 mask = (1 << srcbpp) - 1;
    ଅଚଳ Uint32 align = (8 / srcbpp) - 1;

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା width = info->dst_w;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା height = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା srcskip = info->src_skip;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->table;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା c;

    width += info->leading_skip;

    ଯଦି (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    ଅନ୍ୟଥା ଯଦି (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    ଅନ୍ୟଥା ଯଦି (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    ଯଦି (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        ଯେତେବେଳେ (height--) {
            Uint8 byte = 0, bit;
            ପାଇଁ (c = 0; c < info->leading_skip; ++c) {
                ଯଦି (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            ପାଇଁ (; c < width; ++c) {
                ଯଦି (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                ଯଦି (bit != ckey) {
                    SDL_memcpy(dst, &palmap[bit * 4], 3);
                }
                byte >>= srcbpp;
                dst += 3;
            }
            src += srcskip;
            dst += dstskip;
        }
    } ଅନ୍ୟଥା {
        ଯେତେବେଳେ (height--) {
            Uint8 byte = 0, bit;
            ପାଇଁ (c = 0; c < info->leading_skip; ++c) {
                ଯଦି (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            ପାଇଁ (; c < width; ++c) {
                ଯଦି (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                ଯଦି (bit != ckey) {
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

SDL_FORCE_INLINE ଶୂନ୍ୟ Blit_Bto4_ଚାବି(SDL_BlitInfo *info, ଅଚଳ Uint32 srcbpp)
{
    ଅଚଳ Uint32 mask = (1 << srcbpp) - 1;
    ଅଚଳ Uint32 align = (8 / srcbpp) - 1;

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା width = info->dst_w;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା height = info->dst_h;
    Uint8 *src = info->src;
    Uint32 *dstp = (Uint32 *)info->dst;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା srcskip = info->src_skip;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->table;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା c;

    width += info->leading_skip;

    ଯଦି (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    ଅନ୍ୟଥା ଯଦି (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    ଅନ୍ୟଥା ଯଦି (srcbpp == 1)
        srcskip += width - (width + 7) / 8;
    dstskip /= 4;

    ଯଦି (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        ଯେତେବେଳେ (height--) {
            Uint8 byte = 0, bit;
            ପାଇଁ (c = 0; c < info->leading_skip; ++c) {
                ଯଦି (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            ପାଇଁ (; c < width; ++c) {
                ଯଦି (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                ଯଦି (bit != ckey) {
                    *dstp = ((Uint32 *)palmap)[bit];
                }
                byte >>= srcbpp;
                dstp++;
            }
            src += srcskip;
            dstp += dstskip;
        }
    } ଅନ୍ୟଥା {
        ଯେତେବେଳେ (height--) {
            Uint8 byte = 0, bit;
            ପାଇଁ (c = 0; c < info->leading_skip; ++c) {
                ଯଦି (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            ପାଇଁ (; c < width; ++c) {
                ଯଦି (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                ଯଦି (bit != ckey) {
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

ସ୍ଥିର ଶୂନ୍ୟ BlitBtoNAlpha(SDL_BlitInfo *info)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା width = info->dst_w;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା height = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା srcskip = info->src_skip;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା dstskip = info->dst_skip;
    ଅଚଳ SDL_Color *srcpal = info->src_pal->colors;
    ଅଚଳ SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    ଅଚଳ SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା srcbpp, dstbpp;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା c;
    Uint32 pixelvalue, mask, align;
    unsigned sR, sG, sB;
    unsigned dR, dG, dB, dA;
    ଅଚଳ unsigned A = info->a;

    width += info->leading_skip;

    srcbpp = srcfmt->bytes_per_pixel;
    dstbpp = dstfmt->bytes_per_pixel;
    ଯଦି (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    ଅନ୍ୟଥା ଯଦି (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    ଅନ୍ୟଥା ଯଦି (srcbpp == 1)
        srcskip += width - (width + 7) / 8;
    mask = (1 << srcbpp) - 1;
    align = (8 / srcbpp) - 1;

    ଯଦି (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        ଯେତେବେଳେ (height--) {
            Uint8 byte = 0, bit;
            ପାଇଁ (c = 0; c < info->leading_skip; ++c) {
                ଯଦି (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            ପାଇଁ (; c < width; ++c) {
                ଯଦି (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                ଯଦି (1) {
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
    } ଅନ୍ୟଥା {
        ଯେତେବେଳେ (height--) {
            Uint8 byte = 0, bit;
            ପାଇଁ (c = 0; c < info->leading_skip; ++c) {
                ଯଦି (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            ପାଇଁ (; c < width; ++c) {
                ଯଦି (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                ଯଦି (1) {
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

ସ୍ଥିର ଶୂନ୍ୟ Blit_Bto_NAlpha_ଚାବି(SDL_BlitInfo *info)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା width = info->dst_w;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା height = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା srcskip = info->src_skip;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା dstskip = info->dst_skip;
    ଅଚଳ SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    ଅଚଳ SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    ଅଚଳ SDL_Color *srcpal = info->src_pal->colors;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା srcbpp, dstbpp;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା c;
    Uint32 pixelvalue, mask, align;
    unsigned sR, sG, sB;
    unsigned dR, dG, dB, dA;
    ଅଚଳ unsigned A = info->a;
    Uint32 ckey = info->colorkey;

    width += info->leading_skip;

    srcbpp = srcfmt->bytes_per_pixel;
    dstbpp = dstfmt->bytes_per_pixel;
    ଯଦି (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    ଅନ୍ୟଥା ଯଦି (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    ଅନ୍ୟଥା ଯଦି (srcbpp == 1)
        srcskip += width - (width + 7) / 8;
    mask = (1 << srcbpp) - 1;
    align = (8 / srcbpp) - 1;

    ଯଦି (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        ଯେତେବେଳେ (height--) {
            Uint8 byte = 0, bit;
            ପାଇଁ (c = 0; c < info->leading_skip; ++c) {
                ଯଦି (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            ପାଇଁ (; c < width; ++c) {
                ଯଦି (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                ଯଦି (bit != ckey) {
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
    } ଅନ୍ୟଥା {
        ଯେତେବେଳେ (height--) {
            Uint8 byte = 0, bit;
            ପାଇଁ (c = 0; c < info->leading_skip; ++c) {
                ଯଦି (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            ପାଇଁ (; c < width; ++c) {
                ଯଦି (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                ଯଦି (bit != ckey) {
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



ସ୍ଥିର ଶୂନ୍ୟ Blit1bto1(SDL_BlitInfo *info) {
    BlitBto1(info, 1);
}

ସ୍ଥିର ଶୂନ୍ୟ Blit1bto2(SDL_BlitInfo *info) {
    BlitBto2(info, 1);
}

ସ୍ଥିର ଶୂନ୍ୟ Blit1bto3(SDL_BlitInfo *info) {
    BlitBto3(info, 1);
}

ସ୍ଥିର ଶୂନ୍ୟ Blit1bto4(SDL_BlitInfo *info) {
    BlitBto4(info, 1);
}

ସ୍ଥିର ଅଚଳ SDL_BlitFunc bitmap_blit_1b[] = {
    (SDL_BlitFunc)ଖାଲି, Blit1bto1, Blit1bto2, Blit1bto3, Blit1bto4
};

ସ୍ଥିର ଶୂନ୍ୟ Blit1bto1_ଚାବି(SDL_BlitInfo *info) {
    Blit_Bto1_ଚାବି(info, 1);
}

ସ୍ଥିର ଶୂନ୍ୟ Blit1bto2_ଚାବି(SDL_BlitInfo *info) {
    Blit_Bto2_ଚାବି(info, 1);
}

ସ୍ଥିର ଶୂନ୍ୟ Blit1bto3_ଚାବି(SDL_BlitInfo *info) {
    Blit_Bto3_ଚାବି(info, 1);
}

ସ୍ଥିର ଶୂନ୍ୟ Blit1bto4_ଚାବି(SDL_BlitInfo *info) {
    Blit_Bto4_ଚାବି(info, 1);
}

ସ୍ଥିର ଅଚଳ SDL_BlitFunc colorkey_blit_1b[] = {
    (SDL_BlitFunc)ଖାଲି, Blit1bto1_ଚାବି, Blit1bto2_ଚାବି, Blit1bto3_ଚାବି, Blit1bto4_ଚାବି
};



ସ୍ଥିର ଶୂନ୍ୟ Blit2bto1(SDL_BlitInfo *info) {
    BlitBto1(info, 2);
}

ସ୍ଥିର ଶୂନ୍ୟ Blit2bto2(SDL_BlitInfo *info) {
    BlitBto2(info, 2);
}

ସ୍ଥିର ଶୂନ୍ୟ Blit2bto3(SDL_BlitInfo *info) {
    BlitBto3(info, 2);
}

ସ୍ଥିର ଶୂନ୍ୟ Blit2bto4(SDL_BlitInfo *info) {
    BlitBto4(info, 2);
}

ସ୍ଥିର ଅଚଳ SDL_BlitFunc bitmap_blit_2b[] = {
    (SDL_BlitFunc)ଖାଲି, Blit2bto1, Blit2bto2, Blit2bto3, Blit2bto4
};

ସ୍ଥିର ଶୂନ୍ୟ Blit2bto1_ଚାବି(SDL_BlitInfo *info) {
    Blit_Bto1_ଚାବି(info, 2);
}

ସ୍ଥିର ଶୂନ୍ୟ Blit2bto2_ଚାବି(SDL_BlitInfo *info) {
    Blit_Bto2_ଚାବି(info, 2);
}

ସ୍ଥିର ଶୂନ୍ୟ Blit2bto3_ଚାବି(SDL_BlitInfo *info) {
    Blit_Bto3_ଚାବି(info, 2);
}

ସ୍ଥିର ଶୂନ୍ୟ Blit2bto4_ଚାବି(SDL_BlitInfo *info) {
    Blit_Bto4_ଚାବି(info, 2);
}

ସ୍ଥିର ଅଚଳ SDL_BlitFunc colorkey_blit_2b[] = {
    (SDL_BlitFunc)ଖାଲି, Blit2bto1_ଚାବି, Blit2bto2_ଚାବି, Blit2bto3_ଚାବି, Blit2bto4_ଚାବି
};



ସ୍ଥିର ଶୂନ୍ୟ Blit4bto1(SDL_BlitInfo *info) {
    BlitBto1(info, 4);
}

ସ୍ଥିର ଶୂନ୍ୟ Blit4bto2(SDL_BlitInfo *info) {
    BlitBto2(info, 4);
}

ସ୍ଥିର ଶୂନ୍ୟ Blit4bto3(SDL_BlitInfo *info) {
    BlitBto3(info, 4);
}

ସ୍ଥିର ଶୂନ୍ୟ Blit4bto4(SDL_BlitInfo *info) {
    BlitBto4(info, 4);
}

ସ୍ଥିର ଅଚଳ SDL_BlitFunc bitmap_blit_4b[] = {
    (SDL_BlitFunc)ଖାଲି, Blit4bto1, Blit4bto2, Blit4bto3, Blit4bto4
};

ସ୍ଥିର ଶୂନ୍ୟ Blit4bto1_ଚାବି(SDL_BlitInfo *info) {
    Blit_Bto1_ଚାବି(info, 4);
}

ସ୍ଥିର ଶୂନ୍ୟ Blit4bto2_ଚାବି(SDL_BlitInfo *info) {
    Blit_Bto2_ଚାବି(info, 4);
}

ସ୍ଥିର ଶୂନ୍ୟ Blit4bto3_ଚାବି(SDL_BlitInfo *info) {
    Blit_Bto3_ଚାବି(info, 4);
}

ସ୍ଥିର ଶୂନ୍ୟ Blit4bto4_ଚାବି(SDL_BlitInfo *info) {
    Blit_Bto4_ଚାବି(info, 4);
}

ସ୍ଥିର ଅଚଳ SDL_BlitFunc colorkey_blit_4b[] = {
    (SDL_BlitFunc)ଖାଲି, Blit4bto1_ଚାବି, Blit4bto2_ଚାବି, Blit4bto3_ଚାବି, Blit4bto4_ଚାବି
};



SDL_BlitFunc SDL_CalculateBlit0(SDL_Surface *surface)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା which;

    ଯଦି (SDL_BITSPERPIXEL(surface->map.info.dst_fmt->format) < 8) {
        which = 0;
    } ଅନ୍ୟଥା {
        which = SDL_BYTESPERPIXEL(surface->map.info.dst_fmt->format);
    }

    ଯଦି (SDL_PIXELTYPE(surface->format) == SDL_PIXELTYPE_INDEX1) {
        ବାଛ (surface->map.info.flags & ~SDL_COPY_RLE_MASK) {
        ସ୍ଥିତି 0:
            ଯଦି (which < SDL_arraysize(bitmap_blit_1b)) {
                ଫେରନ୍ତୁ bitmap_blit_1b[which];
            }
            ଭାଙ୍ଗ;

        ସ୍ଥିତି SDL_COPY_COLORKEY:
            ଯଦି (which < SDL_arraysize(colorkey_blit_1b)) {
                ଫେରନ୍ତୁ colorkey_blit_1b[which];
            }
            ଭାଙ୍ଗ;

        ସ୍ଥିତି SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            ଫେରନ୍ତୁ which >= 2 ? BlitBtoNAlpha : (SDL_BlitFunc)ଖାଲି;

        ସ୍ଥିତି SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            ଫେରନ୍ତୁ which >= 2 ? Blit_Bto_NAlpha_ଚାବି : (SDL_BlitFunc)ଖାଲି;
        }
        ଫେରନ୍ତୁ ଖାଲି;
    }

    ଯଦି (SDL_PIXELTYPE(surface->format) == SDL_PIXELTYPE_INDEX2) {
        ବାଛ (surface->map.info.flags & ~SDL_COPY_RLE_MASK) {
        ସ୍ଥିତି 0:
            ଯଦି (which < SDL_arraysize(bitmap_blit_2b)) {
                ଫେରନ୍ତୁ bitmap_blit_2b[which];
            }
            ଭାଙ୍ଗ;

        ସ୍ଥିତି SDL_COPY_COLORKEY:
            ଯଦି (which < SDL_arraysize(colorkey_blit_2b)) {
                ଫେରନ୍ତୁ colorkey_blit_2b[which];
            }
            ଭାଙ୍ଗ;

        ସ୍ଥିତି SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            ଫେରନ୍ତୁ which >= 2 ? BlitBtoNAlpha : (SDL_BlitFunc)ଖାଲି;

        ସ୍ଥିତି SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            ଫେରନ୍ତୁ which >= 2 ? Blit_Bto_NAlpha_ଚାବି : (SDL_BlitFunc)ଖାଲି;
        }
        ଫେରନ୍ତୁ ଖାଲି;
    }

    ଯଦି (SDL_PIXELTYPE(surface->format) == SDL_PIXELTYPE_INDEX4) {
        ବାଛ (surface->map.info.flags & ~SDL_COPY_RLE_MASK) {
        ସ୍ଥିତି 0:
            ଯଦି (which < SDL_arraysize(bitmap_blit_4b)) {
                ଫେରନ୍ତୁ bitmap_blit_4b[which];
            }
            ଭାଙ୍ଗ;

        ସ୍ଥିତି SDL_COPY_COLORKEY:
            ଯଦି (which < SDL_arraysize(colorkey_blit_4b)) {
                ଫେରନ୍ତୁ colorkey_blit_4b[which];
            }
            ଭାଙ୍ଗ;

        ସ୍ଥିତି SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            ଫେରନ୍ତୁ which >= 2 ? BlitBtoNAlpha : (SDL_BlitFunc)ଖାଲି;

        ସ୍ଥିତି SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            ଫେରନ୍ତୁ which >= 2 ? Blit_Bto_NAlpha_ଚାବି : (SDL_BlitFunc)ଖାଲି;
        }
        ଫେରନ୍ତୁ ଖାଲି;
    }

    ଫେରନ୍ତୁ ଖାଲି;
}

#endif // SDL_HAVE_BLIT_0
