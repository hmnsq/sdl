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

#ifdef SDL_HAVE_BLIT_0

#अन्तर्भाव "SDL_surface_c.h"

// Functions to blit from bitmaps to other surfaces

SDL_FORCE_INLINE शून्य BlitBto1(SDL_BlitInfo *info, स्थिरांक Uint32 srcbpp)
{
    स्थिरांक Uint32 mask = (1 << srcbpp) - 1;
    स्थिरांक Uint32 align = (8 / srcbpp) - 1;

    पूर्णांक c;
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

    width += info->leading_skip;

    जर (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    अन्यथा जर (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    अन्यथा जर (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    जर (map) {
        जर (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            पर्यंत (height--) {
                Uint8 byte = 0, bit;
                साठी (c = 0; c < info->leading_skip; ++c) {
                    जर (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                साठी (; c < width; ++c) {
                    जर (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte & mask);
                    जर (1) {
                        *dst = map[bit];
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } अन्यथा {
            पर्यंत (height--) {
                Uint8 byte = 0, bit;
                साठी (c = 0; c < info->leading_skip; ++c) {
                    जर (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                साठी (; c < width; ++c) {
                    जर (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte >> (8 - srcbpp)) & mask;
                    जर (1) {
                        *dst = map[bit];
                    }
                    dst++;
                    byte <<= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        }
    } अन्यथा {
        जर (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            पर्यंत (height--) {
                Uint8 byte = 0, bit;
                साठी (c = 0; c < info->leading_skip; ++c) {
                    जर (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                साठी (; c < width; ++c) {
                    जर (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte & mask);
                    जर (1) {
                        *dst = bit;
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } अन्यथा {
            पर्यंत (height--) {
                Uint8 byte = 0, bit;
                साठी (c = 0; c < info->leading_skip; ++c) {
                    जर (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                साठी (; c < width; ++c) {
                    जर (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte >> (8 - srcbpp)) & mask;
                    जर (1) {
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

SDL_FORCE_INLINE शून्य BlitBto2(SDL_BlitInfo *info, स्थिरांक Uint32 srcbpp)
{
    स्थिरांक Uint32 mask = (1 << srcbpp) - 1;
    स्थिरांक Uint32 align = (8 / srcbpp) - 1;

    पूर्णांक c;
    पूर्णांक width, height;
    Uint8 *src;
    Uint16 *map, *dst;
    पूर्णांक srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = (Uint16 *)info->dst;
    dstskip = info->dst_skip / 2;
    map = (Uint16 *)info->table;

    width += info->leading_skip;

    जर (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    अन्यथा जर (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    अन्यथा जर (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    जर (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        पर्यंत (height--) {
            Uint8 byte = 0, bit;
            साठी (c = 0; c < info->leading_skip; ++c) {
                जर (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            साठी (; c < width; ++c) {
                जर (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                जर (1) {
                    *dst = map[bit];
                }
                byte >>= srcbpp;
                dst++;
            }
            src += srcskip;
            dst += dstskip;
        }
    } अन्यथा {
        पर्यंत (height--) {
            Uint8 byte = 0, bit;
            साठी (c = 0; c < info->leading_skip; ++c) {
                जर (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            साठी (; c < width; ++c) {
                जर (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                जर (1) {
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

SDL_FORCE_INLINE शून्य BlitBto3(SDL_BlitInfo *info, स्थिरांक Uint32 srcbpp)
{
    स्थिरांक Uint32 mask = (1 << srcbpp) - 1;
    स्थिरांक Uint32 align = (8 / srcbpp) - 1;

    पूर्णांक c, o;
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

    width += info->leading_skip;

    जर (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    अन्यथा जर (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    अन्यथा जर (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    जर (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        पर्यंत (height--) {
            Uint8 byte = 0, bit;
            साठी (c = 0; c < info->leading_skip; ++c) {
                जर (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            साठी (; c < width; ++c) {
                जर (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                जर (1) {
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
    } अन्यथा {
        पर्यंत (height--) {
            Uint8 byte = 0, bit;
            साठी (c = 0; c < info->leading_skip; ++c) {
                जर (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            साठी (; c < width; ++c) {
                जर (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                जर (1) {
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

SDL_FORCE_INLINE शून्य BlitBto4(SDL_BlitInfo *info, स्थिरांक Uint32 srcbpp)
{
    स्थिरांक Uint32 mask = (1 << srcbpp) - 1;
    स्थिरांक Uint32 align = (8 / srcbpp) - 1;

    पूर्णांक width, height;
    Uint8 *src;
    Uint32 *map, *dst;
    पूर्णांक srcskip, dstskip;
    पूर्णांक c;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = (Uint32 *)info->dst;
    dstskip = info->dst_skip / 4;
    map = (Uint32 *)info->table;

    width += info->leading_skip;

    जर (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    अन्यथा जर (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    अन्यथा जर (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    जर (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        पर्यंत (height--) {
            Uint8 byte = 0, bit;
            साठी (c = 0; c < info->leading_skip; ++c) {
                जर (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            साठी (; c < width; ++c) {
                जर (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                जर (1) {
                    *dst = map[bit];
                }
                byte >>= srcbpp;
                dst++;
            }
            src += srcskip;
            dst += dstskip;
        }
    } अन्यथा {
        पर्यंत (height--) {
            Uint8 byte = 0, bit;
            साठी (c = 0; c < info->leading_skip; ++c) {
                जर (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            साठी (; c < width; ++c) {
                जर (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                जर (1) {
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

SDL_FORCE_INLINE शून्य Blit_Bto1_किल्ली(SDL_BlitInfo *info, स्थिरांक Uint32 srcbpp)
{
    स्थिरांक Uint32 mask = (1 << srcbpp) - 1;
    स्थिरांक Uint32 align = (8 / srcbpp) - 1;

    पूर्णांक width = info->dst_w;
    पूर्णांक height = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    पूर्णांक srcskip = info->src_skip;
    पूर्णांक dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->table;
    पूर्णांक c;

    width += info->leading_skip;

    जर (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    अन्यथा जर (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    अन्यथा जर (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    जर (palmap) {
        जर (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            पर्यंत (height--) {
                Uint8 byte = 0, bit;
                साठी (c = 0; c < info->leading_skip; ++c) {
                    जर (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                साठी (; c < width; ++c) {
                    जर (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte & mask);
                    जर (bit != ckey) {
                        *dst = palmap[bit];
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } अन्यथा {
            पर्यंत (height--) {
                Uint8 byte = 0, bit;
                साठी (c = 0; c < info->leading_skip; ++c) {
                    जर (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                साठी (; c < width; ++c) {
                    जर (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte >> (8 - srcbpp)) & mask;
                    जर (bit != ckey) {
                        *dst = palmap[bit];
                    }
                    dst++;
                    byte <<= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        }
    } अन्यथा {
        जर (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            पर्यंत (height--) {
                Uint8 byte = 0, bit;
                साठी (c = 0; c < info->leading_skip; ++c) {
                    जर (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                साठी (; c < width; ++c) {
                    जर (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte & mask);
                    जर (bit != ckey) {
                        *dst = bit;
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } अन्यथा {
            पर्यंत (height--) {
                Uint8 byte = 0, bit;
                साठी (c = 0; c < info->leading_skip; ++c) {
                    जर (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                साठी (; c < width; ++c) {
                    जर (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte >> (8 - srcbpp)) & mask;
                    जर (bit != ckey) {
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

SDL_FORCE_INLINE शून्य Blit_Bto2_किल्ली(SDL_BlitInfo *info, स्थिरांक Uint32 srcbpp)
{
    स्थिरांक Uint32 mask = (1 << srcbpp) - 1;
    स्थिरांक Uint32 align = (8 / srcbpp) - 1;

    पूर्णांक width = info->dst_w;
    पूर्णांक height = info->dst_h;
    Uint8 *src = info->src;
    Uint16 *dstp = (Uint16 *)info->dst;
    पूर्णांक srcskip = info->src_skip;
    पूर्णांक dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->table;
    पूर्णांक c;

    width += info->leading_skip;

    जर (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    अन्यथा जर (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    अन्यथा जर (srcbpp == 1)
        srcskip += width - (width + 7) / 8;
    dstskip /= 2;

    जर (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        पर्यंत (height--) {
            Uint8 byte = 0, bit;
            साठी (c = 0; c < info->leading_skip; ++c) {
                जर (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            साठी (; c < width; ++c) {
                जर (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                जर (bit != ckey) {
                    *dstp = ((Uint16 *)palmap)[bit];
                }
                byte >>= srcbpp;
                dstp++;
            }
            src += srcskip;
            dstp += dstskip;
        }
    } अन्यथा {
        पर्यंत (height--) {
            Uint8 byte = 0, bit;
            साठी (c = 0; c < info->leading_skip; ++c) {
                जर (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            साठी (; c < width; ++c) {
                जर (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                जर (bit != ckey) {
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

SDL_FORCE_INLINE शून्य Blit_Bto3_किल्ली(SDL_BlitInfo *info, स्थिरांक Uint32 srcbpp)
{
    स्थिरांक Uint32 mask = (1 << srcbpp) - 1;
    स्थिरांक Uint32 align = (8 / srcbpp) - 1;

    पूर्णांक width = info->dst_w;
    पूर्णांक height = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    पूर्णांक srcskip = info->src_skip;
    पूर्णांक dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->table;
    पूर्णांक c;

    width += info->leading_skip;

    जर (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    अन्यथा जर (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    अन्यथा जर (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    जर (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        पर्यंत (height--) {
            Uint8 byte = 0, bit;
            साठी (c = 0; c < info->leading_skip; ++c) {
                जर (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            साठी (; c < width; ++c) {
                जर (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                जर (bit != ckey) {
                    SDL_memcpy(dst, &palmap[bit * 4], 3);
                }
                byte >>= srcbpp;
                dst += 3;
            }
            src += srcskip;
            dst += dstskip;
        }
    } अन्यथा {
        पर्यंत (height--) {
            Uint8 byte = 0, bit;
            साठी (c = 0; c < info->leading_skip; ++c) {
                जर (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            साठी (; c < width; ++c) {
                जर (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                जर (bit != ckey) {
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

SDL_FORCE_INLINE शून्य Blit_Bto4_किल्ली(SDL_BlitInfo *info, स्थिरांक Uint32 srcbpp)
{
    स्थिरांक Uint32 mask = (1 << srcbpp) - 1;
    स्थिरांक Uint32 align = (8 / srcbpp) - 1;

    पूर्णांक width = info->dst_w;
    पूर्णांक height = info->dst_h;
    Uint8 *src = info->src;
    Uint32 *dstp = (Uint32 *)info->dst;
    पूर्णांक srcskip = info->src_skip;
    पूर्णांक dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->table;
    पूर्णांक c;

    width += info->leading_skip;

    जर (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    अन्यथा जर (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    अन्यथा जर (srcbpp == 1)
        srcskip += width - (width + 7) / 8;
    dstskip /= 4;

    जर (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        पर्यंत (height--) {
            Uint8 byte = 0, bit;
            साठी (c = 0; c < info->leading_skip; ++c) {
                जर (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            साठी (; c < width; ++c) {
                जर (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                जर (bit != ckey) {
                    *dstp = ((Uint32 *)palmap)[bit];
                }
                byte >>= srcbpp;
                dstp++;
            }
            src += srcskip;
            dstp += dstskip;
        }
    } अन्यथा {
        पर्यंत (height--) {
            Uint8 byte = 0, bit;
            साठी (c = 0; c < info->leading_skip; ++c) {
                जर (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            साठी (; c < width; ++c) {
                जर (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                जर (bit != ckey) {
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

स्थिर शून्य BlitBtoNAlpha(SDL_BlitInfo *info)
{
    पूर्णांक width = info->dst_w;
    पूर्णांक height = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    पूर्णांक srcskip = info->src_skip;
    पूर्णांक dstskip = info->dst_skip;
    स्थिरांक SDL_Color *srcpal = info->src_pal->colors;
    स्थिरांक SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    स्थिरांक SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    पूर्णांक srcbpp, dstbpp;
    पूर्णांक c;
    Uint32 pixelvalue, mask, align;
    अचिन्हित sR, sG, sB;
    अचिन्हित dR, dG, dB, dA;
    स्थिरांक अचिन्हित A = info->a;

    width += info->leading_skip;

    srcbpp = srcfmt->bytes_per_pixel;
    dstbpp = dstfmt->bytes_per_pixel;
    जर (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    अन्यथा जर (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    अन्यथा जर (srcbpp == 1)
        srcskip += width - (width + 7) / 8;
    mask = (1 << srcbpp) - 1;
    align = (8 / srcbpp) - 1;

    जर (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        पर्यंत (height--) {
            Uint8 byte = 0, bit;
            साठी (c = 0; c < info->leading_skip; ++c) {
                जर (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            साठी (; c < width; ++c) {
                जर (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                जर (1) {
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
    } अन्यथा {
        पर्यंत (height--) {
            Uint8 byte = 0, bit;
            साठी (c = 0; c < info->leading_skip; ++c) {
                जर (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            साठी (; c < width; ++c) {
                जर (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                जर (1) {
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

स्थिर शून्य Blit_Bto_NAlpha_किल्ली(SDL_BlitInfo *info)
{
    पूर्णांक width = info->dst_w;
    पूर्णांक height = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    पूर्णांक srcskip = info->src_skip;
    पूर्णांक dstskip = info->dst_skip;
    स्थिरांक SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    स्थिरांक SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    स्थिरांक SDL_Color *srcpal = info->src_pal->colors;
    पूर्णांक srcbpp, dstbpp;
    पूर्णांक c;
    Uint32 pixelvalue, mask, align;
    अचिन्हित sR, sG, sB;
    अचिन्हित dR, dG, dB, dA;
    स्थिरांक अचिन्हित A = info->a;
    Uint32 ckey = info->colorkey;

    width += info->leading_skip;

    srcbpp = srcfmt->bytes_per_pixel;
    dstbpp = dstfmt->bytes_per_pixel;
    जर (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    अन्यथा जर (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    अन्यथा जर (srcbpp == 1)
        srcskip += width - (width + 7) / 8;
    mask = (1 << srcbpp) - 1;
    align = (8 / srcbpp) - 1;

    जर (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        पर्यंत (height--) {
            Uint8 byte = 0, bit;
            साठी (c = 0; c < info->leading_skip; ++c) {
                जर (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            साठी (; c < width; ++c) {
                जर (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                जर (bit != ckey) {
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
    } अन्यथा {
        पर्यंत (height--) {
            Uint8 byte = 0, bit;
            साठी (c = 0; c < info->leading_skip; ++c) {
                जर (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            साठी (; c < width; ++c) {
                जर (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                जर (bit != ckey) {
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



स्थिर शून्य Blit1bto1(SDL_BlitInfo *info) {
    BlitBto1(info, 1);
}

स्थिर शून्य Blit1bto2(SDL_BlitInfo *info) {
    BlitBto2(info, 1);
}

स्थिर शून्य Blit1bto3(SDL_BlitInfo *info) {
    BlitBto3(info, 1);
}

स्थिर शून्य Blit1bto4(SDL_BlitInfo *info) {
    BlitBto4(info, 1);
}

स्थिर स्थिरांक SDL_BlitFunc bitmap_blit_1b[] = {
    (SDL_BlitFunc)रिक्त, Blit1bto1, Blit1bto2, Blit1bto3, Blit1bto4
};

स्थिर शून्य Blit1bto1_किल्ली(SDL_BlitInfo *info) {
    Blit_Bto1_किल्ली(info, 1);
}

स्थिर शून्य Blit1bto2_किल्ली(SDL_BlitInfo *info) {
    Blit_Bto2_किल्ली(info, 1);
}

स्थिर शून्य Blit1bto3_किल्ली(SDL_BlitInfo *info) {
    Blit_Bto3_किल्ली(info, 1);
}

स्थिर शून्य Blit1bto4_किल्ली(SDL_BlitInfo *info) {
    Blit_Bto4_किल्ली(info, 1);
}

स्थिर स्थिरांक SDL_BlitFunc colorkey_blit_1b[] = {
    (SDL_BlitFunc)रिक्त, Blit1bto1_किल्ली, Blit1bto2_किल्ली, Blit1bto3_किल्ली, Blit1bto4_किल्ली
};



स्थिर शून्य Blit2bto1(SDL_BlitInfo *info) {
    BlitBto1(info, 2);
}

स्थिर शून्य Blit2bto2(SDL_BlitInfo *info) {
    BlitBto2(info, 2);
}

स्थिर शून्य Blit2bto3(SDL_BlitInfo *info) {
    BlitBto3(info, 2);
}

स्थिर शून्य Blit2bto4(SDL_BlitInfo *info) {
    BlitBto4(info, 2);
}

स्थिर स्थिरांक SDL_BlitFunc bitmap_blit_2b[] = {
    (SDL_BlitFunc)रिक्त, Blit2bto1, Blit2bto2, Blit2bto3, Blit2bto4
};

स्थिर शून्य Blit2bto1_किल्ली(SDL_BlitInfo *info) {
    Blit_Bto1_किल्ली(info, 2);
}

स्थिर शून्य Blit2bto2_किल्ली(SDL_BlitInfo *info) {
    Blit_Bto2_किल्ली(info, 2);
}

स्थिर शून्य Blit2bto3_किल्ली(SDL_BlitInfo *info) {
    Blit_Bto3_किल्ली(info, 2);
}

स्थिर शून्य Blit2bto4_किल्ली(SDL_BlitInfo *info) {
    Blit_Bto4_किल्ली(info, 2);
}

स्थिर स्थिरांक SDL_BlitFunc colorkey_blit_2b[] = {
    (SDL_BlitFunc)रिक्त, Blit2bto1_किल्ली, Blit2bto2_किल्ली, Blit2bto3_किल्ली, Blit2bto4_किल्ली
};



स्थिर शून्य Blit4bto1(SDL_BlitInfo *info) {
    BlitBto1(info, 4);
}

स्थिर शून्य Blit4bto2(SDL_BlitInfo *info) {
    BlitBto2(info, 4);
}

स्थिर शून्य Blit4bto3(SDL_BlitInfo *info) {
    BlitBto3(info, 4);
}

स्थिर शून्य Blit4bto4(SDL_BlitInfo *info) {
    BlitBto4(info, 4);
}

स्थिर स्थिरांक SDL_BlitFunc bitmap_blit_4b[] = {
    (SDL_BlitFunc)रिक्त, Blit4bto1, Blit4bto2, Blit4bto3, Blit4bto4
};

स्थिर शून्य Blit4bto1_किल्ली(SDL_BlitInfo *info) {
    Blit_Bto1_किल्ली(info, 4);
}

स्थिर शून्य Blit4bto2_किल्ली(SDL_BlitInfo *info) {
    Blit_Bto2_किल्ली(info, 4);
}

स्थिर शून्य Blit4bto3_किल्ली(SDL_BlitInfo *info) {
    Blit_Bto3_किल्ली(info, 4);
}

स्थिर शून्य Blit4bto4_किल्ली(SDL_BlitInfo *info) {
    Blit_Bto4_किल्ली(info, 4);
}

स्थिर स्थिरांक SDL_BlitFunc colorkey_blit_4b[] = {
    (SDL_BlitFunc)रिक्त, Blit4bto1_किल्ली, Blit4bto2_किल्ली, Blit4bto3_किल्ली, Blit4bto4_किल्ली
};



SDL_BlitFunc SDL_CalculateBlit0(SDL_Surface *surface)
{
    पूर्णांक which;

    जर (SDL_BITSPERPIXEL(surface->map.info.dst_fmt->format) < 8) {
        which = 0;
    } अन्यथा {
        which = SDL_BYTESPERPIXEL(surface->map.info.dst_fmt->format);
    }

    जर (SDL_PIXELTYPE(surface->format) == SDL_PIXELTYPE_INDEX1) {
        निवड (surface->map.info.flags & ~SDL_COPY_RLE_MASK) {
        स्थिती 0:
            जर (which < SDL_arraysize(bitmap_blit_1b)) {
                परत bitmap_blit_1b[which];
            }
            थांबा;

        स्थिती SDL_COPY_COLORKEY:
            जर (which < SDL_arraysize(colorkey_blit_1b)) {
                परत colorkey_blit_1b[which];
            }
            थांबा;

        स्थिती SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            परत which >= 2 ? BlitBtoNAlpha : (SDL_BlitFunc)रिक्त;

        स्थिती SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            परत which >= 2 ? Blit_Bto_NAlpha_किल्ली : (SDL_BlitFunc)रिक्त;
        }
        परत रिक्त;
    }

    जर (SDL_PIXELTYPE(surface->format) == SDL_PIXELTYPE_INDEX2) {
        निवड (surface->map.info.flags & ~SDL_COPY_RLE_MASK) {
        स्थिती 0:
            जर (which < SDL_arraysize(bitmap_blit_2b)) {
                परत bitmap_blit_2b[which];
            }
            थांबा;

        स्थिती SDL_COPY_COLORKEY:
            जर (which < SDL_arraysize(colorkey_blit_2b)) {
                परत colorkey_blit_2b[which];
            }
            थांबा;

        स्थिती SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            परत which >= 2 ? BlitBtoNAlpha : (SDL_BlitFunc)रिक्त;

        स्थिती SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            परत which >= 2 ? Blit_Bto_NAlpha_किल्ली : (SDL_BlitFunc)रिक्त;
        }
        परत रिक्त;
    }

    जर (SDL_PIXELTYPE(surface->format) == SDL_PIXELTYPE_INDEX4) {
        निवड (surface->map.info.flags & ~SDL_COPY_RLE_MASK) {
        स्थिती 0:
            जर (which < SDL_arraysize(bitmap_blit_4b)) {
                परत bitmap_blit_4b[which];
            }
            थांबा;

        स्थिती SDL_COPY_COLORKEY:
            जर (which < SDL_arraysize(colorkey_blit_4b)) {
                परत colorkey_blit_4b[which];
            }
            थांबा;

        स्थिती SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            परत which >= 2 ? BlitBtoNAlpha : (SDL_BlitFunc)रिक्त;

        स्थिती SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            परत which >= 2 ? Blit_Bto_NAlpha_किल्ली : (SDL_BlitFunc)रिक्त;
        }
        परत रिक्त;
    }

    परत रिक्त;
}

#endif // SDL_HAVE_BLIT_0
