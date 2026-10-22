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

SDL_FORCE_INLINE शून्य BlitBto1(SDL_BlitInfo *info, ध्रुव Uint32 srcbpp)
{
    ध्रुव Uint32 mask = (1 << srcbpp) - 1;
    ध्रुव Uint32 align = (8 / srcbpp) - 1;

    पूर्णाङ्क c;
    पूर्णाङ्क width, height;
    Uint8 *src, *map, *dst;
    पूर्णाङ्क srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = info->table;

    width += info->leading_skip;

    यदि (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    अन्यथा यदि (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    अन्यथा यदि (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    यदि (map) {
        यदि (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            यावत् (height--) {
                Uint8 byte = 0, bit;
                प्रति (c = 0; c < info->leading_skip; ++c) {
                    यदि (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                प्रति (; c < width; ++c) {
                    यदि (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte & mask);
                    यदि (1) {
                        *dst = map[bit];
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } अन्यथा {
            यावत् (height--) {
                Uint8 byte = 0, bit;
                प्रति (c = 0; c < info->leading_skip; ++c) {
                    यदि (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                प्रति (; c < width; ++c) {
                    यदि (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte >> (8 - srcbpp)) & mask;
                    यदि (1) {
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
        यदि (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            यावत् (height--) {
                Uint8 byte = 0, bit;
                प्रति (c = 0; c < info->leading_skip; ++c) {
                    यदि (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                प्रति (; c < width; ++c) {
                    यदि (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte & mask);
                    यदि (1) {
                        *dst = bit;
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } अन्यथा {
            यावत् (height--) {
                Uint8 byte = 0, bit;
                प्रति (c = 0; c < info->leading_skip; ++c) {
                    यदि (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                प्रति (; c < width; ++c) {
                    यदि (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte >> (8 - srcbpp)) & mask;
                    यदि (1) {
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

SDL_FORCE_INLINE शून्य BlitBto2(SDL_BlitInfo *info, ध्रुव Uint32 srcbpp)
{
    ध्रुव Uint32 mask = (1 << srcbpp) - 1;
    ध्रुव Uint32 align = (8 / srcbpp) - 1;

    पूर्णाङ्क c;
    पूर्णाङ्क width, height;
    Uint8 *src;
    Uint16 *map, *dst;
    पूर्णाङ्क srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = (Uint16 *)info->dst;
    dstskip = info->dst_skip / 2;
    map = (Uint16 *)info->table;

    width += info->leading_skip;

    यदि (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    अन्यथा यदि (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    अन्यथा यदि (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    यदि (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        यावत् (height--) {
            Uint8 byte = 0, bit;
            प्रति (c = 0; c < info->leading_skip; ++c) {
                यदि (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            प्रति (; c < width; ++c) {
                यदि (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                यदि (1) {
                    *dst = map[bit];
                }
                byte >>= srcbpp;
                dst++;
            }
            src += srcskip;
            dst += dstskip;
        }
    } अन्यथा {
        यावत् (height--) {
            Uint8 byte = 0, bit;
            प्रति (c = 0; c < info->leading_skip; ++c) {
                यदि (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            प्रति (; c < width; ++c) {
                यदि (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                यदि (1) {
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

SDL_FORCE_INLINE शून्य BlitBto3(SDL_BlitInfo *info, ध्रुव Uint32 srcbpp)
{
    ध्रुव Uint32 mask = (1 << srcbpp) - 1;
    ध्रुव Uint32 align = (8 / srcbpp) - 1;

    पूर्णाङ्क c, o;
    पूर्णाङ्क width, height;
    Uint8 *src, *map, *dst;
    पूर्णाङ्क srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = info->table;

    width += info->leading_skip;

    यदि (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    अन्यथा यदि (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    अन्यथा यदि (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    यदि (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        यावत् (height--) {
            Uint8 byte = 0, bit;
            प्रति (c = 0; c < info->leading_skip; ++c) {
                यदि (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            प्रति (; c < width; ++c) {
                यदि (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                यदि (1) {
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
        यावत् (height--) {
            Uint8 byte = 0, bit;
            प्रति (c = 0; c < info->leading_skip; ++c) {
                यदि (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            प्रति (; c < width; ++c) {
                यदि (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                यदि (1) {
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

SDL_FORCE_INLINE शून्य BlitBto4(SDL_BlitInfo *info, ध्रुव Uint32 srcbpp)
{
    ध्रुव Uint32 mask = (1 << srcbpp) - 1;
    ध्रुव Uint32 align = (8 / srcbpp) - 1;

    पूर्णाङ्क width, height;
    Uint8 *src;
    Uint32 *map, *dst;
    पूर्णाङ्क srcskip, dstskip;
    पूर्णाङ्क c;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = (Uint32 *)info->dst;
    dstskip = info->dst_skip / 4;
    map = (Uint32 *)info->table;

    width += info->leading_skip;

    यदि (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    अन्यथा यदि (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    अन्यथा यदि (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    यदि (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        यावत् (height--) {
            Uint8 byte = 0, bit;
            प्रति (c = 0; c < info->leading_skip; ++c) {
                यदि (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            प्रति (; c < width; ++c) {
                यदि (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                यदि (1) {
                    *dst = map[bit];
                }
                byte >>= srcbpp;
                dst++;
            }
            src += srcskip;
            dst += dstskip;
        }
    } अन्यथा {
        यावत् (height--) {
            Uint8 byte = 0, bit;
            प्रति (c = 0; c < info->leading_skip; ++c) {
                यदि (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            प्रति (; c < width; ++c) {
                यदि (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                यदि (1) {
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

SDL_FORCE_INLINE शून्य Blit_Bto1_कुंजी(SDL_BlitInfo *info, ध्रुव Uint32 srcbpp)
{
    ध्रुव Uint32 mask = (1 << srcbpp) - 1;
    ध्रुव Uint32 align = (8 / srcbpp) - 1;

    पूर्णाङ्क width = info->dst_w;
    पूर्णाङ्क height = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    पूर्णाङ्क srcskip = info->src_skip;
    पूर्णाङ्क dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->table;
    पूर्णाङ्क c;

    width += info->leading_skip;

    यदि (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    अन्यथा यदि (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    अन्यथा यदि (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    यदि (palmap) {
        यदि (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            यावत् (height--) {
                Uint8 byte = 0, bit;
                प्रति (c = 0; c < info->leading_skip; ++c) {
                    यदि (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                प्रति (; c < width; ++c) {
                    यदि (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte & mask);
                    यदि (bit != ckey) {
                        *dst = palmap[bit];
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } अन्यथा {
            यावत् (height--) {
                Uint8 byte = 0, bit;
                प्रति (c = 0; c < info->leading_skip; ++c) {
                    यदि (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                प्रति (; c < width; ++c) {
                    यदि (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte >> (8 - srcbpp)) & mask;
                    यदि (bit != ckey) {
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
        यदि (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            यावत् (height--) {
                Uint8 byte = 0, bit;
                प्रति (c = 0; c < info->leading_skip; ++c) {
                    यदि (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                प्रति (; c < width; ++c) {
                    यदि (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte & mask);
                    यदि (bit != ckey) {
                        *dst = bit;
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } अन्यथा {
            यावत् (height--) {
                Uint8 byte = 0, bit;
                प्रति (c = 0; c < info->leading_skip; ++c) {
                    यदि (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                प्रति (; c < width; ++c) {
                    यदि (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte >> (8 - srcbpp)) & mask;
                    यदि (bit != ckey) {
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

SDL_FORCE_INLINE शून्य Blit_Bto2_कुंजी(SDL_BlitInfo *info, ध्रुव Uint32 srcbpp)
{
    ध्रुव Uint32 mask = (1 << srcbpp) - 1;
    ध्रुव Uint32 align = (8 / srcbpp) - 1;

    पूर्णाङ्क width = info->dst_w;
    पूर्णाङ्क height = info->dst_h;
    Uint8 *src = info->src;
    Uint16 *dstp = (Uint16 *)info->dst;
    पूर्णाङ्क srcskip = info->src_skip;
    पूर्णाङ्क dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->table;
    पूर्णाङ्क c;

    width += info->leading_skip;

    यदि (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    अन्यथा यदि (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    अन्यथा यदि (srcbpp == 1)
        srcskip += width - (width + 7) / 8;
    dstskip /= 2;

    यदि (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        यावत् (height--) {
            Uint8 byte = 0, bit;
            प्रति (c = 0; c < info->leading_skip; ++c) {
                यदि (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            प्रति (; c < width; ++c) {
                यदि (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                यदि (bit != ckey) {
                    *dstp = ((Uint16 *)palmap)[bit];
                }
                byte >>= srcbpp;
                dstp++;
            }
            src += srcskip;
            dstp += dstskip;
        }
    } अन्यथा {
        यावत् (height--) {
            Uint8 byte = 0, bit;
            प्रति (c = 0; c < info->leading_skip; ++c) {
                यदि (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            प्रति (; c < width; ++c) {
                यदि (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                यदि (bit != ckey) {
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

SDL_FORCE_INLINE शून्य Blit_Bto3_कुंजी(SDL_BlitInfo *info, ध्रुव Uint32 srcbpp)
{
    ध्रुव Uint32 mask = (1 << srcbpp) - 1;
    ध्रुव Uint32 align = (8 / srcbpp) - 1;

    पूर्णाङ्क width = info->dst_w;
    पूर्णाङ्क height = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    पूर्णाङ्क srcskip = info->src_skip;
    पूर्णाङ्क dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->table;
    पूर्णाङ्क c;

    width += info->leading_skip;

    यदि (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    अन्यथा यदि (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    अन्यथा यदि (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    यदि (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        यावत् (height--) {
            Uint8 byte = 0, bit;
            प्रति (c = 0; c < info->leading_skip; ++c) {
                यदि (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            प्रति (; c < width; ++c) {
                यदि (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                यदि (bit != ckey) {
                    SDL_memcpy(dst, &palmap[bit * 4], 3);
                }
                byte >>= srcbpp;
                dst += 3;
            }
            src += srcskip;
            dst += dstskip;
        }
    } अन्यथा {
        यावत् (height--) {
            Uint8 byte = 0, bit;
            प्रति (c = 0; c < info->leading_skip; ++c) {
                यदि (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            प्रति (; c < width; ++c) {
                यदि (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                यदि (bit != ckey) {
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

SDL_FORCE_INLINE शून्य Blit_Bto4_कुंजी(SDL_BlitInfo *info, ध्रुव Uint32 srcbpp)
{
    ध्रुव Uint32 mask = (1 << srcbpp) - 1;
    ध्रुव Uint32 align = (8 / srcbpp) - 1;

    पूर्णाङ्क width = info->dst_w;
    पूर्णाङ्क height = info->dst_h;
    Uint8 *src = info->src;
    Uint32 *dstp = (Uint32 *)info->dst;
    पूर्णाङ्क srcskip = info->src_skip;
    पूर्णाङ्क dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->table;
    पूर्णाङ्क c;

    width += info->leading_skip;

    यदि (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    अन्यथा यदि (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    अन्यथा यदि (srcbpp == 1)
        srcskip += width - (width + 7) / 8;
    dstskip /= 4;

    यदि (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        यावत् (height--) {
            Uint8 byte = 0, bit;
            प्रति (c = 0; c < info->leading_skip; ++c) {
                यदि (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            प्रति (; c < width; ++c) {
                यदि (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                यदि (bit != ckey) {
                    *dstp = ((Uint32 *)palmap)[bit];
                }
                byte >>= srcbpp;
                dstp++;
            }
            src += srcskip;
            dstp += dstskip;
        }
    } अन्यथा {
        यावत् (height--) {
            Uint8 byte = 0, bit;
            प्रति (c = 0; c < info->leading_skip; ++c) {
                यदि (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            प्रति (; c < width; ++c) {
                यदि (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                यदि (bit != ckey) {
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
    पूर्णाङ्क width = info->dst_w;
    पूर्णाङ्क height = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    पूर्णाङ्क srcskip = info->src_skip;
    पूर्णाङ्क dstskip = info->dst_skip;
    ध्रुव SDL_Color *srcpal = info->src_pal->colors;
    ध्रुव SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    ध्रुव SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    पूर्णाङ्क srcbpp, dstbpp;
    पूर्णाङ्क c;
    Uint32 pixelvalue, mask, align;
    अचिन्हित sR, sG, sB;
    अचिन्हित dR, dG, dB, dA;
    ध्रुव अचिन्हित A = info->a;

    width += info->leading_skip;

    srcbpp = srcfmt->bytes_per_pixel;
    dstbpp = dstfmt->bytes_per_pixel;
    यदि (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    अन्यथा यदि (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    अन्यथा यदि (srcbpp == 1)
        srcskip += width - (width + 7) / 8;
    mask = (1 << srcbpp) - 1;
    align = (8 / srcbpp) - 1;

    यदि (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        यावत् (height--) {
            Uint8 byte = 0, bit;
            प्रति (c = 0; c < info->leading_skip; ++c) {
                यदि (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            प्रति (; c < width; ++c) {
                यदि (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                यदि (1) {
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
        यावत् (height--) {
            Uint8 byte = 0, bit;
            प्रति (c = 0; c < info->leading_skip; ++c) {
                यदि (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            प्रति (; c < width; ++c) {
                यदि (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                यदि (1) {
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

स्थिर शून्य Blit_Bto_NAlpha_कुंजी(SDL_BlitInfo *info)
{
    पूर्णाङ्क width = info->dst_w;
    पूर्णाङ्क height = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    पूर्णाङ्क srcskip = info->src_skip;
    पूर्णाङ्क dstskip = info->dst_skip;
    ध्रुव SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    ध्रुव SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    ध्रुव SDL_Color *srcpal = info->src_pal->colors;
    पूर्णाङ्क srcbpp, dstbpp;
    पूर्णाङ्क c;
    Uint32 pixelvalue, mask, align;
    अचिन्हित sR, sG, sB;
    अचिन्हित dR, dG, dB, dA;
    ध्रुव अचिन्हित A = info->a;
    Uint32 ckey = info->colorkey;

    width += info->leading_skip;

    srcbpp = srcfmt->bytes_per_pixel;
    dstbpp = dstfmt->bytes_per_pixel;
    यदि (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    अन्यथा यदि (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    अन्यथा यदि (srcbpp == 1)
        srcskip += width - (width + 7) / 8;
    mask = (1 << srcbpp) - 1;
    align = (8 / srcbpp) - 1;

    यदि (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        यावत् (height--) {
            Uint8 byte = 0, bit;
            प्रति (c = 0; c < info->leading_skip; ++c) {
                यदि (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            प्रति (; c < width; ++c) {
                यदि (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                यदि (bit != ckey) {
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
        यावत् (height--) {
            Uint8 byte = 0, bit;
            प्रति (c = 0; c < info->leading_skip; ++c) {
                यदि (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            प्रति (; c < width; ++c) {
                यदि (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                यदि (bit != ckey) {
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

स्थिर ध्रुव SDL_BlitFunc bitmap_blit_1b[] = {
    (SDL_BlitFunc)रिक्त, Blit1bto1, Blit1bto2, Blit1bto3, Blit1bto4
};

स्थिर शून्य Blit1bto1_कुंजी(SDL_BlitInfo *info) {
    Blit_Bto1_कुंजी(info, 1);
}

स्थिर शून्य Blit1bto2_कुंजी(SDL_BlitInfo *info) {
    Blit_Bto2_कुंजी(info, 1);
}

स्थिर शून्य Blit1bto3_कुंजी(SDL_BlitInfo *info) {
    Blit_Bto3_कुंजी(info, 1);
}

स्थिर शून्य Blit1bto4_कुंजी(SDL_BlitInfo *info) {
    Blit_Bto4_कुंजी(info, 1);
}

स्थिर ध्रुव SDL_BlitFunc colorkey_blit_1b[] = {
    (SDL_BlitFunc)रिक्त, Blit1bto1_कुंजी, Blit1bto2_कुंजी, Blit1bto3_कुंजी, Blit1bto4_कुंजी
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

स्थिर ध्रुव SDL_BlitFunc bitmap_blit_2b[] = {
    (SDL_BlitFunc)रिक्त, Blit2bto1, Blit2bto2, Blit2bto3, Blit2bto4
};

स्थिर शून्य Blit2bto1_कुंजी(SDL_BlitInfo *info) {
    Blit_Bto1_कुंजी(info, 2);
}

स्थिर शून्य Blit2bto2_कुंजी(SDL_BlitInfo *info) {
    Blit_Bto2_कुंजी(info, 2);
}

स्थिर शून्य Blit2bto3_कुंजी(SDL_BlitInfo *info) {
    Blit_Bto3_कुंजी(info, 2);
}

स्थिर शून्य Blit2bto4_कुंजी(SDL_BlitInfo *info) {
    Blit_Bto4_कुंजी(info, 2);
}

स्थिर ध्रुव SDL_BlitFunc colorkey_blit_2b[] = {
    (SDL_BlitFunc)रिक्त, Blit2bto1_कुंजी, Blit2bto2_कुंजी, Blit2bto3_कुंजी, Blit2bto4_कुंजी
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

स्थिर ध्रुव SDL_BlitFunc bitmap_blit_4b[] = {
    (SDL_BlitFunc)रिक्त, Blit4bto1, Blit4bto2, Blit4bto3, Blit4bto4
};

स्थिर शून्य Blit4bto1_कुंजी(SDL_BlitInfo *info) {
    Blit_Bto1_कुंजी(info, 4);
}

स्थिर शून्य Blit4bto2_कुंजी(SDL_BlitInfo *info) {
    Blit_Bto2_कुंजी(info, 4);
}

स्थिर शून्य Blit4bto3_कुंजी(SDL_BlitInfo *info) {
    Blit_Bto3_कुंजी(info, 4);
}

स्थिर शून्य Blit4bto4_कुंजी(SDL_BlitInfo *info) {
    Blit_Bto4_कुंजी(info, 4);
}

स्थिर ध्रुव SDL_BlitFunc colorkey_blit_4b[] = {
    (SDL_BlitFunc)रिक्त, Blit4bto1_कुंजी, Blit4bto2_कुंजी, Blit4bto3_कुंजी, Blit4bto4_कुंजी
};



SDL_BlitFunc SDL_CalculateBlit0(SDL_Surface *surface)
{
    पूर्णाङ्क which;

    यदि (SDL_BITSPERPIXEL(surface->map.info.dst_fmt->format) < 8) {
        which = 0;
    } अन्यथा {
        which = SDL_BYTESPERPIXEL(surface->map.info.dst_fmt->format);
    }

    यदि (SDL_PIXELTYPE(surface->format) == SDL_PIXELTYPE_INDEX1) {
        विकल्प (surface->map.info.flags & ~SDL_COPY_RLE_MASK) {
        पक्ष 0:
            यदि (which < SDL_arraysize(bitmap_blit_1b)) {
                प्रत्यागम bitmap_blit_1b[which];
            }
            भङ्ग;

        पक्ष SDL_COPY_COLORKEY:
            यदि (which < SDL_arraysize(colorkey_blit_1b)) {
                प्रत्यागम colorkey_blit_1b[which];
            }
            भङ्ग;

        पक्ष SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            प्रत्यागम which >= 2 ? BlitBtoNAlpha : (SDL_BlitFunc)रिक्त;

        पक्ष SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            प्रत्यागम which >= 2 ? Blit_Bto_NAlpha_कुंजी : (SDL_BlitFunc)रिक्त;
        }
        प्रत्यागम रिक्त;
    }

    यदि (SDL_PIXELTYPE(surface->format) == SDL_PIXELTYPE_INDEX2) {
        विकल्प (surface->map.info.flags & ~SDL_COPY_RLE_MASK) {
        पक्ष 0:
            यदि (which < SDL_arraysize(bitmap_blit_2b)) {
                प्रत्यागम bitmap_blit_2b[which];
            }
            भङ्ग;

        पक्ष SDL_COPY_COLORKEY:
            यदि (which < SDL_arraysize(colorkey_blit_2b)) {
                प्रत्यागम colorkey_blit_2b[which];
            }
            भङ्ग;

        पक्ष SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            प्रत्यागम which >= 2 ? BlitBtoNAlpha : (SDL_BlitFunc)रिक्त;

        पक्ष SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            प्रत्यागम which >= 2 ? Blit_Bto_NAlpha_कुंजी : (SDL_BlitFunc)रिक्त;
        }
        प्रत्यागम रिक्त;
    }

    यदि (SDL_PIXELTYPE(surface->format) == SDL_PIXELTYPE_INDEX4) {
        विकल्प (surface->map.info.flags & ~SDL_COPY_RLE_MASK) {
        पक्ष 0:
            यदि (which < SDL_arraysize(bitmap_blit_4b)) {
                प्रत्यागम bitmap_blit_4b[which];
            }
            भङ्ग;

        पक्ष SDL_COPY_COLORKEY:
            यदि (which < SDL_arraysize(colorkey_blit_4b)) {
                प्रत्यागम colorkey_blit_4b[which];
            }
            भङ्ग;

        पक्ष SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            प्रत्यागम which >= 2 ? BlitBtoNAlpha : (SDL_BlitFunc)रिक्त;

        पक्ष SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            प्रत्यागम which >= 2 ? Blit_Bto_NAlpha_कुंजी : (SDL_BlitFunc)रिक्त;
        }
        प्रत्यागम रिक्त;
    }

    प्रत्यागम रिक्त;
}

#endif // SDL_HAVE_BLIT_0
