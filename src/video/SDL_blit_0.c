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
#அந்தர்பாவ "SDL_internal.h"

#ifdef SDL_HAVE_BLIT_0

#அந்தர்பாவ "SDL_surface_c.h"

// Functions to blit from bitmaps to other surfaces

SDL_FORCE_INLINE வெறுமை BlitBto1(SDL_BlitInfo *info, மாறிலி Uint32 srcbpp)
{
    மாறிலி Uint32 mask = (1 << srcbpp) - 1;
    மாறிலி Uint32 align = (8 / srcbpp) - 1;

    முழு c;
    முழு width, height;
    Uint8 *src, *map, *dst;
    முழு srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = info->table;

    width += info->leading_skip;

    எனில் (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    இல்லையெனில் எனில் (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    இல்லையெனில் எனில் (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    எனில் (map) {
        எனில் (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            போது (height--) {
                Uint8 byte = 0, bit;
                க்கு (c = 0; c < info->leading_skip; ++c) {
                    எனில் (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                க்கு (; c < width; ++c) {
                    எனில் (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte & mask);
                    எனில் (1) {
                        *dst = map[bit];
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } இல்லையெனில் {
            போது (height--) {
                Uint8 byte = 0, bit;
                க்கு (c = 0; c < info->leading_skip; ++c) {
                    எனில் (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                க்கு (; c < width; ++c) {
                    எனில் (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte >> (8 - srcbpp)) & mask;
                    எனில் (1) {
                        *dst = map[bit];
                    }
                    dst++;
                    byte <<= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        }
    } இல்லையெனில் {
        எனில் (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            போது (height--) {
                Uint8 byte = 0, bit;
                க்கு (c = 0; c < info->leading_skip; ++c) {
                    எனில் (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                க்கு (; c < width; ++c) {
                    எனில் (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte & mask);
                    எனில் (1) {
                        *dst = bit;
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } இல்லையெனில் {
            போது (height--) {
                Uint8 byte = 0, bit;
                க்கு (c = 0; c < info->leading_skip; ++c) {
                    எனில் (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                க்கு (; c < width; ++c) {
                    எனில் (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte >> (8 - srcbpp)) & mask;
                    எனில் (1) {
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

SDL_FORCE_INLINE வெறுமை BlitBto2(SDL_BlitInfo *info, மாறிலி Uint32 srcbpp)
{
    மாறிலி Uint32 mask = (1 << srcbpp) - 1;
    மாறிலி Uint32 align = (8 / srcbpp) - 1;

    முழு c;
    முழு width, height;
    Uint8 *src;
    Uint16 *map, *dst;
    முழு srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = (Uint16 *)info->dst;
    dstskip = info->dst_skip / 2;
    map = (Uint16 *)info->table;

    width += info->leading_skip;

    எனில் (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    இல்லையெனில் எனில் (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    இல்லையெனில் எனில் (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    எனில் (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        போது (height--) {
            Uint8 byte = 0, bit;
            க்கு (c = 0; c < info->leading_skip; ++c) {
                எனில் (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            க்கு (; c < width; ++c) {
                எனில் (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                எனில் (1) {
                    *dst = map[bit];
                }
                byte >>= srcbpp;
                dst++;
            }
            src += srcskip;
            dst += dstskip;
        }
    } இல்லையெனில் {
        போது (height--) {
            Uint8 byte = 0, bit;
            க்கு (c = 0; c < info->leading_skip; ++c) {
                எனில் (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            க்கு (; c < width; ++c) {
                எனில் (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                எனில் (1) {
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

SDL_FORCE_INLINE வெறுமை BlitBto3(SDL_BlitInfo *info, மாறிலி Uint32 srcbpp)
{
    மாறிலி Uint32 mask = (1 << srcbpp) - 1;
    மாறிலி Uint32 align = (8 / srcbpp) - 1;

    முழு c, o;
    முழு width, height;
    Uint8 *src, *map, *dst;
    முழு srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = info->table;

    width += info->leading_skip;

    எனில் (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    இல்லையெனில் எனில் (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    இல்லையெனில் எனில் (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    எனில் (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        போது (height--) {
            Uint8 byte = 0, bit;
            க்கு (c = 0; c < info->leading_skip; ++c) {
                எனில் (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            க்கு (; c < width; ++c) {
                எனில் (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                எனில் (1) {
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
    } இல்லையெனில் {
        போது (height--) {
            Uint8 byte = 0, bit;
            க்கு (c = 0; c < info->leading_skip; ++c) {
                எனில் (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            க்கு (; c < width; ++c) {
                எனில் (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                எனில் (1) {
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

SDL_FORCE_INLINE வெறுமை BlitBto4(SDL_BlitInfo *info, மாறிலி Uint32 srcbpp)
{
    மாறிலி Uint32 mask = (1 << srcbpp) - 1;
    மாறிலி Uint32 align = (8 / srcbpp) - 1;

    முழு width, height;
    Uint8 *src;
    Uint32 *map, *dst;
    முழு srcskip, dstskip;
    முழு c;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = (Uint32 *)info->dst;
    dstskip = info->dst_skip / 4;
    map = (Uint32 *)info->table;

    width += info->leading_skip;

    எனில் (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    இல்லையெனில் எனில் (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    இல்லையெனில் எனில் (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    எனில் (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        போது (height--) {
            Uint8 byte = 0, bit;
            க்கு (c = 0; c < info->leading_skip; ++c) {
                எனில் (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            க்கு (; c < width; ++c) {
                எனில் (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                எனில் (1) {
                    *dst = map[bit];
                }
                byte >>= srcbpp;
                dst++;
            }
            src += srcskip;
            dst += dstskip;
        }
    } இல்லையெனில் {
        போது (height--) {
            Uint8 byte = 0, bit;
            க்கு (c = 0; c < info->leading_skip; ++c) {
                எனில் (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            க்கு (; c < width; ++c) {
                எனில் (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                எனில் (1) {
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

SDL_FORCE_INLINE வெறுமை Blit_Bto1_சாவி(SDL_BlitInfo *info, மாறிலி Uint32 srcbpp)
{
    மாறிலி Uint32 mask = (1 << srcbpp) - 1;
    மாறிலி Uint32 align = (8 / srcbpp) - 1;

    முழு width = info->dst_w;
    முழு height = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    முழு srcskip = info->src_skip;
    முழு dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->table;
    முழு c;

    width += info->leading_skip;

    எனில் (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    இல்லையெனில் எனில் (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    இல்லையெனில் எனில் (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    எனில் (palmap) {
        எனில் (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            போது (height--) {
                Uint8 byte = 0, bit;
                க்கு (c = 0; c < info->leading_skip; ++c) {
                    எனில் (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                க்கு (; c < width; ++c) {
                    எனில் (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte & mask);
                    எனில் (bit != ckey) {
                        *dst = palmap[bit];
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } இல்லையெனில் {
            போது (height--) {
                Uint8 byte = 0, bit;
                க்கு (c = 0; c < info->leading_skip; ++c) {
                    எனில் (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                க்கு (; c < width; ++c) {
                    எனில் (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte >> (8 - srcbpp)) & mask;
                    எனில் (bit != ckey) {
                        *dst = palmap[bit];
                    }
                    dst++;
                    byte <<= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        }
    } இல்லையெனில் {
        எனில் (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            போது (height--) {
                Uint8 byte = 0, bit;
                க்கு (c = 0; c < info->leading_skip; ++c) {
                    எனில் (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                க்கு (; c < width; ++c) {
                    எனில் (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte & mask);
                    எனில் (bit != ckey) {
                        *dst = bit;
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } இல்லையெனில் {
            போது (height--) {
                Uint8 byte = 0, bit;
                க்கு (c = 0; c < info->leading_skip; ++c) {
                    எனில் (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                க்கு (; c < width; ++c) {
                    எனில் (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte >> (8 - srcbpp)) & mask;
                    எனில் (bit != ckey) {
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

SDL_FORCE_INLINE வெறுமை Blit_Bto2_சாவி(SDL_BlitInfo *info, மாறிலி Uint32 srcbpp)
{
    மாறிலி Uint32 mask = (1 << srcbpp) - 1;
    மாறிலி Uint32 align = (8 / srcbpp) - 1;

    முழு width = info->dst_w;
    முழு height = info->dst_h;
    Uint8 *src = info->src;
    Uint16 *dstp = (Uint16 *)info->dst;
    முழு srcskip = info->src_skip;
    முழு dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->table;
    முழு c;

    width += info->leading_skip;

    எனில் (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    இல்லையெனில் எனில் (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    இல்லையெனில் எனில் (srcbpp == 1)
        srcskip += width - (width + 7) / 8;
    dstskip /= 2;

    எனில் (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        போது (height--) {
            Uint8 byte = 0, bit;
            க்கு (c = 0; c < info->leading_skip; ++c) {
                எனில் (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            க்கு (; c < width; ++c) {
                எனில் (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                எனில் (bit != ckey) {
                    *dstp = ((Uint16 *)palmap)[bit];
                }
                byte >>= srcbpp;
                dstp++;
            }
            src += srcskip;
            dstp += dstskip;
        }
    } இல்லையெனில் {
        போது (height--) {
            Uint8 byte = 0, bit;
            க்கு (c = 0; c < info->leading_skip; ++c) {
                எனில் (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            க்கு (; c < width; ++c) {
                எனில் (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                எனில் (bit != ckey) {
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

SDL_FORCE_INLINE வெறுமை Blit_Bto3_சாவி(SDL_BlitInfo *info, மாறிலி Uint32 srcbpp)
{
    மாறிலி Uint32 mask = (1 << srcbpp) - 1;
    மாறிலி Uint32 align = (8 / srcbpp) - 1;

    முழு width = info->dst_w;
    முழு height = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    முழு srcskip = info->src_skip;
    முழு dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->table;
    முழு c;

    width += info->leading_skip;

    எனில் (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    இல்லையெனில் எனில் (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    இல்லையெனில் எனில் (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    எனில் (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        போது (height--) {
            Uint8 byte = 0, bit;
            க்கு (c = 0; c < info->leading_skip; ++c) {
                எனில் (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            க்கு (; c < width; ++c) {
                எனில் (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                எனில் (bit != ckey) {
                    SDL_memcpy(dst, &palmap[bit * 4], 3);
                }
                byte >>= srcbpp;
                dst += 3;
            }
            src += srcskip;
            dst += dstskip;
        }
    } இல்லையெனில் {
        போது (height--) {
            Uint8 byte = 0, bit;
            க்கு (c = 0; c < info->leading_skip; ++c) {
                எனில் (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            க்கு (; c < width; ++c) {
                எனில் (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                எனில் (bit != ckey) {
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

SDL_FORCE_INLINE வெறுமை Blit_Bto4_சாவி(SDL_BlitInfo *info, மாறிலி Uint32 srcbpp)
{
    மாறிலி Uint32 mask = (1 << srcbpp) - 1;
    மாறிலி Uint32 align = (8 / srcbpp) - 1;

    முழு width = info->dst_w;
    முழு height = info->dst_h;
    Uint8 *src = info->src;
    Uint32 *dstp = (Uint32 *)info->dst;
    முழு srcskip = info->src_skip;
    முழு dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->table;
    முழு c;

    width += info->leading_skip;

    எனில் (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    இல்லையெனில் எனில் (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    இல்லையெனில் எனில் (srcbpp == 1)
        srcskip += width - (width + 7) / 8;
    dstskip /= 4;

    எனில் (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        போது (height--) {
            Uint8 byte = 0, bit;
            க்கு (c = 0; c < info->leading_skip; ++c) {
                எனில் (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            க்கு (; c < width; ++c) {
                எனில் (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                எனில் (bit != ckey) {
                    *dstp = ((Uint32 *)palmap)[bit];
                }
                byte >>= srcbpp;
                dstp++;
            }
            src += srcskip;
            dstp += dstskip;
        }
    } இல்லையெனில் {
        போது (height--) {
            Uint8 byte = 0, bit;
            க்கு (c = 0; c < info->leading_skip; ++c) {
                எனில் (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            க்கு (; c < width; ++c) {
                எனில் (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                எனில் (bit != ckey) {
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

நிலையான வெறுமை BlitBtoNAlpha(SDL_BlitInfo *info)
{
    முழு width = info->dst_w;
    முழு height = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    முழு srcskip = info->src_skip;
    முழு dstskip = info->dst_skip;
    மாறிலி SDL_Color *srcpal = info->src_pal->colors;
    மாறிலி SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    மாறிலி SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    முழு srcbpp, dstbpp;
    முழு c;
    Uint32 pixelvalue, mask, align;
    unsigned sR, sG, sB;
    unsigned dR, dG, dB, dA;
    மாறிலி unsigned A = info->a;

    width += info->leading_skip;

    srcbpp = srcfmt->bytes_per_pixel;
    dstbpp = dstfmt->bytes_per_pixel;
    எனில் (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    இல்லையெனில் எனில் (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    இல்லையெனில் எனில் (srcbpp == 1)
        srcskip += width - (width + 7) / 8;
    mask = (1 << srcbpp) - 1;
    align = (8 / srcbpp) - 1;

    எனில் (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        போது (height--) {
            Uint8 byte = 0, bit;
            க்கு (c = 0; c < info->leading_skip; ++c) {
                எனில் (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            க்கு (; c < width; ++c) {
                எனில் (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                எனில் (1) {
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
    } இல்லையெனில் {
        போது (height--) {
            Uint8 byte = 0, bit;
            க்கு (c = 0; c < info->leading_skip; ++c) {
                எனில் (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            க்கு (; c < width; ++c) {
                எனில் (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                எனில் (1) {
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

நிலையான வெறுமை Blit_Bto_NAlpha_சாவி(SDL_BlitInfo *info)
{
    முழு width = info->dst_w;
    முழு height = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    முழு srcskip = info->src_skip;
    முழு dstskip = info->dst_skip;
    மாறிலி SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    மாறிலி SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    மாறிலி SDL_Color *srcpal = info->src_pal->colors;
    முழு srcbpp, dstbpp;
    முழு c;
    Uint32 pixelvalue, mask, align;
    unsigned sR, sG, sB;
    unsigned dR, dG, dB, dA;
    மாறிலி unsigned A = info->a;
    Uint32 ckey = info->colorkey;

    width += info->leading_skip;

    srcbpp = srcfmt->bytes_per_pixel;
    dstbpp = dstfmt->bytes_per_pixel;
    எனில் (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    இல்லையெனில் எனில் (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    இல்லையெனில் எனில் (srcbpp == 1)
        srcskip += width - (width + 7) / 8;
    mask = (1 << srcbpp) - 1;
    align = (8 / srcbpp) - 1;

    எனில் (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        போது (height--) {
            Uint8 byte = 0, bit;
            க்கு (c = 0; c < info->leading_skip; ++c) {
                எனில் (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            க்கு (; c < width; ++c) {
                எனில் (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                எனில் (bit != ckey) {
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
    } இல்லையெனில் {
        போது (height--) {
            Uint8 byte = 0, bit;
            க்கு (c = 0; c < info->leading_skip; ++c) {
                எனில் (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            க்கு (; c < width; ++c) {
                எனில் (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                எனில் (bit != ckey) {
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



நிலையான வெறுமை Blit1bto1(SDL_BlitInfo *info) {
    BlitBto1(info, 1);
}

நிலையான வெறுமை Blit1bto2(SDL_BlitInfo *info) {
    BlitBto2(info, 1);
}

நிலையான வெறுமை Blit1bto3(SDL_BlitInfo *info) {
    BlitBto3(info, 1);
}

நிலையான வெறுமை Blit1bto4(SDL_BlitInfo *info) {
    BlitBto4(info, 1);
}

நிலையான மாறிலி SDL_BlitFunc bitmap_blit_1b[] = {
    (SDL_BlitFunc)வெற்று, Blit1bto1, Blit1bto2, Blit1bto3, Blit1bto4
};

நிலையான வெறுமை Blit1bto1_சாவி(SDL_BlitInfo *info) {
    Blit_Bto1_சாவி(info, 1);
}

நிலையான வெறுமை Blit1bto2_சாவி(SDL_BlitInfo *info) {
    Blit_Bto2_சாவி(info, 1);
}

நிலையான வெறுமை Blit1bto3_சாவி(SDL_BlitInfo *info) {
    Blit_Bto3_சாவி(info, 1);
}

நிலையான வெறுமை Blit1bto4_சாவி(SDL_BlitInfo *info) {
    Blit_Bto4_சாவி(info, 1);
}

நிலையான மாறிலி SDL_BlitFunc colorkey_blit_1b[] = {
    (SDL_BlitFunc)வெற்று, Blit1bto1_சாவி, Blit1bto2_சாவி, Blit1bto3_சாவி, Blit1bto4_சாவி
};



நிலையான வெறுமை Blit2bto1(SDL_BlitInfo *info) {
    BlitBto1(info, 2);
}

நிலையான வெறுமை Blit2bto2(SDL_BlitInfo *info) {
    BlitBto2(info, 2);
}

நிலையான வெறுமை Blit2bto3(SDL_BlitInfo *info) {
    BlitBto3(info, 2);
}

நிலையான வெறுமை Blit2bto4(SDL_BlitInfo *info) {
    BlitBto4(info, 2);
}

நிலையான மாறிலி SDL_BlitFunc bitmap_blit_2b[] = {
    (SDL_BlitFunc)வெற்று, Blit2bto1, Blit2bto2, Blit2bto3, Blit2bto4
};

நிலையான வெறுமை Blit2bto1_சாவி(SDL_BlitInfo *info) {
    Blit_Bto1_சாவி(info, 2);
}

நிலையான வெறுமை Blit2bto2_சாவி(SDL_BlitInfo *info) {
    Blit_Bto2_சாவி(info, 2);
}

நிலையான வெறுமை Blit2bto3_சாவி(SDL_BlitInfo *info) {
    Blit_Bto3_சாவி(info, 2);
}

நிலையான வெறுமை Blit2bto4_சாவி(SDL_BlitInfo *info) {
    Blit_Bto4_சாவி(info, 2);
}

நிலையான மாறிலி SDL_BlitFunc colorkey_blit_2b[] = {
    (SDL_BlitFunc)வெற்று, Blit2bto1_சாவி, Blit2bto2_சாவி, Blit2bto3_சாவி, Blit2bto4_சாவி
};



நிலையான வெறுமை Blit4bto1(SDL_BlitInfo *info) {
    BlitBto1(info, 4);
}

நிலையான வெறுமை Blit4bto2(SDL_BlitInfo *info) {
    BlitBto2(info, 4);
}

நிலையான வெறுமை Blit4bto3(SDL_BlitInfo *info) {
    BlitBto3(info, 4);
}

நிலையான வெறுமை Blit4bto4(SDL_BlitInfo *info) {
    BlitBto4(info, 4);
}

நிலையான மாறிலி SDL_BlitFunc bitmap_blit_4b[] = {
    (SDL_BlitFunc)வெற்று, Blit4bto1, Blit4bto2, Blit4bto3, Blit4bto4
};

நிலையான வெறுமை Blit4bto1_சாவி(SDL_BlitInfo *info) {
    Blit_Bto1_சாவி(info, 4);
}

நிலையான வெறுமை Blit4bto2_சாவி(SDL_BlitInfo *info) {
    Blit_Bto2_சாவி(info, 4);
}

நிலையான வெறுமை Blit4bto3_சாவி(SDL_BlitInfo *info) {
    Blit_Bto3_சாவி(info, 4);
}

நிலையான வெறுமை Blit4bto4_சாவி(SDL_BlitInfo *info) {
    Blit_Bto4_சாவி(info, 4);
}

நிலையான மாறிலி SDL_BlitFunc colorkey_blit_4b[] = {
    (SDL_BlitFunc)வெற்று, Blit4bto1_சாவி, Blit4bto2_சாவி, Blit4bto3_சாவி, Blit4bto4_சாவி
};



SDL_BlitFunc SDL_CalculateBlit0(SDL_Surface *surface)
{
    முழு which;

    எனில் (SDL_BITSPERPIXEL(surface->map.info.dst_fmt->format) < 8) {
        which = 0;
    } இல்லையெனில் {
        which = SDL_BYTESPERPIXEL(surface->map.info.dst_fmt->format);
    }

    எனில் (SDL_PIXELTYPE(surface->format) == SDL_PIXELTYPE_INDEX1) {
        தேர்வு (surface->map.info.flags & ~SDL_COPY_RLE_MASK) {
        நிலை 0:
            எனில் (which < SDL_arraysize(bitmap_blit_1b)) {
                திரும்பு bitmap_blit_1b[which];
            }
            நிறுத்து;

        நிலை SDL_COPY_COLORKEY:
            எனில் (which < SDL_arraysize(colorkey_blit_1b)) {
                திரும்பு colorkey_blit_1b[which];
            }
            நிறுத்து;

        நிலை SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            திரும்பு which >= 2 ? BlitBtoNAlpha : (SDL_BlitFunc)வெற்று;

        நிலை SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            திரும்பு which >= 2 ? Blit_Bto_NAlpha_சாவி : (SDL_BlitFunc)வெற்று;
        }
        திரும்பு வெற்று;
    }

    எனில் (SDL_PIXELTYPE(surface->format) == SDL_PIXELTYPE_INDEX2) {
        தேர்வு (surface->map.info.flags & ~SDL_COPY_RLE_MASK) {
        நிலை 0:
            எனில் (which < SDL_arraysize(bitmap_blit_2b)) {
                திரும்பு bitmap_blit_2b[which];
            }
            நிறுத்து;

        நிலை SDL_COPY_COLORKEY:
            எனில் (which < SDL_arraysize(colorkey_blit_2b)) {
                திரும்பு colorkey_blit_2b[which];
            }
            நிறுத்து;

        நிலை SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            திரும்பு which >= 2 ? BlitBtoNAlpha : (SDL_BlitFunc)வெற்று;

        நிலை SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            திரும்பு which >= 2 ? Blit_Bto_NAlpha_சாவி : (SDL_BlitFunc)வெற்று;
        }
        திரும்பு வெற்று;
    }

    எனில் (SDL_PIXELTYPE(surface->format) == SDL_PIXELTYPE_INDEX4) {
        தேர்வு (surface->map.info.flags & ~SDL_COPY_RLE_MASK) {
        நிலை 0:
            எனில் (which < SDL_arraysize(bitmap_blit_4b)) {
                திரும்பு bitmap_blit_4b[which];
            }
            நிறுத்து;

        நிலை SDL_COPY_COLORKEY:
            எனில் (which < SDL_arraysize(colorkey_blit_4b)) {
                திரும்பு colorkey_blit_4b[which];
            }
            நிறுத்து;

        நிலை SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            திரும்பு which >= 2 ? BlitBtoNAlpha : (SDL_BlitFunc)வெற்று;

        நிலை SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            திரும்பு which >= 2 ? Blit_Bto_NAlpha_சாவி : (SDL_BlitFunc)வெற்று;
        }
        திரும்பு வெற்று;
    }

    திரும்பு வெற்று;
}

#endif // SDL_HAVE_BLIT_0
