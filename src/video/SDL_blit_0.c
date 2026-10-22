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
#અન્તર્ભાવ "SDL_internal.h"

#ifdef SDL_HAVE_BLIT_0

#અન્તર્ભાવ "SDL_surface_c.h"

// Functions to blit from bitmaps to other surfaces

SDL_FORCE_INLINE શૂન્ય BlitBto1(SDL_BlitInfo *info, અચલ Uint32 srcbpp)
{
    અચલ Uint32 mask = (1 << srcbpp) - 1;
    અચલ Uint32 align = (8 / srcbpp) - 1;

    પૂર્ણાંક c;
    પૂર્ણાંક width, height;
    Uint8 *src, *map, *dst;
    પૂર્ણાંક srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = info->table;

    width += info->leading_skip;

    જો (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    નહીંતર જો (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    નહીંતર જો (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    જો (map) {
        જો (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            જ્યારે (height--) {
                Uint8 byte = 0, bit;
                માટે (c = 0; c < info->leading_skip; ++c) {
                    જો (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                માટે (; c < width; ++c) {
                    જો (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte & mask);
                    જો (1) {
                        *dst = map[bit];
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } નહીંતર {
            જ્યારે (height--) {
                Uint8 byte = 0, bit;
                માટે (c = 0; c < info->leading_skip; ++c) {
                    જો (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                માટે (; c < width; ++c) {
                    જો (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte >> (8 - srcbpp)) & mask;
                    જો (1) {
                        *dst = map[bit];
                    }
                    dst++;
                    byte <<= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        }
    } નહીંતર {
        જો (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            જ્યારે (height--) {
                Uint8 byte = 0, bit;
                માટે (c = 0; c < info->leading_skip; ++c) {
                    જો (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                માટે (; c < width; ++c) {
                    જો (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte & mask);
                    જો (1) {
                        *dst = bit;
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } નહીંતર {
            જ્યારે (height--) {
                Uint8 byte = 0, bit;
                માટે (c = 0; c < info->leading_skip; ++c) {
                    જો (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                માટે (; c < width; ++c) {
                    જો (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte >> (8 - srcbpp)) & mask;
                    જો (1) {
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

SDL_FORCE_INLINE શૂન્ય BlitBto2(SDL_BlitInfo *info, અચલ Uint32 srcbpp)
{
    અચલ Uint32 mask = (1 << srcbpp) - 1;
    અચલ Uint32 align = (8 / srcbpp) - 1;

    પૂર્ણાંક c;
    પૂર્ણાંક width, height;
    Uint8 *src;
    Uint16 *map, *dst;
    પૂર્ણાંક srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = (Uint16 *)info->dst;
    dstskip = info->dst_skip / 2;
    map = (Uint16 *)info->table;

    width += info->leading_skip;

    જો (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    નહીંતર જો (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    નહીંતર જો (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    જો (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        જ્યારે (height--) {
            Uint8 byte = 0, bit;
            માટે (c = 0; c < info->leading_skip; ++c) {
                જો (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            માટે (; c < width; ++c) {
                જો (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                જો (1) {
                    *dst = map[bit];
                }
                byte >>= srcbpp;
                dst++;
            }
            src += srcskip;
            dst += dstskip;
        }
    } નહીંતર {
        જ્યારે (height--) {
            Uint8 byte = 0, bit;
            માટે (c = 0; c < info->leading_skip; ++c) {
                જો (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            માટે (; c < width; ++c) {
                જો (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                જો (1) {
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

SDL_FORCE_INLINE શૂન્ય BlitBto3(SDL_BlitInfo *info, અચલ Uint32 srcbpp)
{
    અચલ Uint32 mask = (1 << srcbpp) - 1;
    અચલ Uint32 align = (8 / srcbpp) - 1;

    પૂર્ણાંક c, o;
    પૂર્ણાંક width, height;
    Uint8 *src, *map, *dst;
    પૂર્ણાંક srcskip, dstskip;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = info->table;

    width += info->leading_skip;

    જો (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    નહીંતર જો (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    નહીંતર જો (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    જો (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        જ્યારે (height--) {
            Uint8 byte = 0, bit;
            માટે (c = 0; c < info->leading_skip; ++c) {
                જો (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            માટે (; c < width; ++c) {
                જો (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                જો (1) {
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
    } નહીંતર {
        જ્યારે (height--) {
            Uint8 byte = 0, bit;
            માટે (c = 0; c < info->leading_skip; ++c) {
                જો (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            માટે (; c < width; ++c) {
                જો (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                જો (1) {
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

SDL_FORCE_INLINE શૂન્ય BlitBto4(SDL_BlitInfo *info, અચલ Uint32 srcbpp)
{
    અચલ Uint32 mask = (1 << srcbpp) - 1;
    અચલ Uint32 align = (8 / srcbpp) - 1;

    પૂર્ણાંક width, height;
    Uint8 *src;
    Uint32 *map, *dst;
    પૂર્ણાંક srcskip, dstskip;
    પૂર્ણાંક c;

    // Set up some basic variables
    width = info->dst_w;
    height = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = (Uint32 *)info->dst;
    dstskip = info->dst_skip / 4;
    map = (Uint32 *)info->table;

    width += info->leading_skip;

    જો (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    નહીંતર જો (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    નહીંતર જો (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    જો (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        જ્યારે (height--) {
            Uint8 byte = 0, bit;
            માટે (c = 0; c < info->leading_skip; ++c) {
                જો (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            માટે (; c < width; ++c) {
                જો (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                જો (1) {
                    *dst = map[bit];
                }
                byte >>= srcbpp;
                dst++;
            }
            src += srcskip;
            dst += dstskip;
        }
    } નહીંતર {
        જ્યારે (height--) {
            Uint8 byte = 0, bit;
            માટે (c = 0; c < info->leading_skip; ++c) {
                જો (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            માટે (; c < width; ++c) {
                જો (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                જો (1) {
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

SDL_FORCE_INLINE શૂન્ય Blit_Bto1_ચાવી(SDL_BlitInfo *info, અચલ Uint32 srcbpp)
{
    અચલ Uint32 mask = (1 << srcbpp) - 1;
    અચલ Uint32 align = (8 / srcbpp) - 1;

    પૂર્ણાંક width = info->dst_w;
    પૂર્ણાંક height = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    પૂર્ણાંક srcskip = info->src_skip;
    પૂર્ણાંક dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->table;
    પૂર્ણાંક c;

    width += info->leading_skip;

    જો (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    નહીંતર જો (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    નહીંતર જો (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    જો (palmap) {
        જો (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            જ્યારે (height--) {
                Uint8 byte = 0, bit;
                માટે (c = 0; c < info->leading_skip; ++c) {
                    જો (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                માટે (; c < width; ++c) {
                    જો (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte & mask);
                    જો (bit != ckey) {
                        *dst = palmap[bit];
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } નહીંતર {
            જ્યારે (height--) {
                Uint8 byte = 0, bit;
                માટે (c = 0; c < info->leading_skip; ++c) {
                    જો (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                માટે (; c < width; ++c) {
                    જો (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte >> (8 - srcbpp)) & mask;
                    જો (bit != ckey) {
                        *dst = palmap[bit];
                    }
                    dst++;
                    byte <<= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        }
    } નહીંતર {
        જો (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            જ્યારે (height--) {
                Uint8 byte = 0, bit;
                માટે (c = 0; c < info->leading_skip; ++c) {
                    જો (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                માટે (; c < width; ++c) {
                    જો (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte & mask);
                    જો (bit != ckey) {
                        *dst = bit;
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } નહીંતર {
            જ્યારે (height--) {
                Uint8 byte = 0, bit;
                માટે (c = 0; c < info->leading_skip; ++c) {
                    જો (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                માટે (; c < width; ++c) {
                    જો (!(c & align)) {
                        byte = *src++;
                    }
                    bit = (byte >> (8 - srcbpp)) & mask;
                    જો (bit != ckey) {
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

SDL_FORCE_INLINE શૂન્ય Blit_Bto2_ચાવી(SDL_BlitInfo *info, અચલ Uint32 srcbpp)
{
    અચલ Uint32 mask = (1 << srcbpp) - 1;
    અચલ Uint32 align = (8 / srcbpp) - 1;

    પૂર્ણાંક width = info->dst_w;
    પૂર્ણાંક height = info->dst_h;
    Uint8 *src = info->src;
    Uint16 *dstp = (Uint16 *)info->dst;
    પૂર્ણાંક srcskip = info->src_skip;
    પૂર્ણાંક dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->table;
    પૂર્ણાંક c;

    width += info->leading_skip;

    જો (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    નહીંતર જો (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    નહીંતર જો (srcbpp == 1)
        srcskip += width - (width + 7) / 8;
    dstskip /= 2;

    જો (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        જ્યારે (height--) {
            Uint8 byte = 0, bit;
            માટે (c = 0; c < info->leading_skip; ++c) {
                જો (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            માટે (; c < width; ++c) {
                જો (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                જો (bit != ckey) {
                    *dstp = ((Uint16 *)palmap)[bit];
                }
                byte >>= srcbpp;
                dstp++;
            }
            src += srcskip;
            dstp += dstskip;
        }
    } નહીંતર {
        જ્યારે (height--) {
            Uint8 byte = 0, bit;
            માટે (c = 0; c < info->leading_skip; ++c) {
                જો (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            માટે (; c < width; ++c) {
                જો (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                જો (bit != ckey) {
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

SDL_FORCE_INLINE શૂન્ય Blit_Bto3_ચાવી(SDL_BlitInfo *info, અચલ Uint32 srcbpp)
{
    અચલ Uint32 mask = (1 << srcbpp) - 1;
    અચલ Uint32 align = (8 / srcbpp) - 1;

    પૂર્ણાંક width = info->dst_w;
    પૂર્ણાંક height = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    પૂર્ણાંક srcskip = info->src_skip;
    પૂર્ણાંક dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->table;
    પૂર્ણાંક c;

    width += info->leading_skip;

    જો (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    નહીંતર જો (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    નહીંતર જો (srcbpp == 1)
        srcskip += width - (width + 7) / 8;

    જો (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        જ્યારે (height--) {
            Uint8 byte = 0, bit;
            માટે (c = 0; c < info->leading_skip; ++c) {
                જો (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            માટે (; c < width; ++c) {
                જો (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                જો (bit != ckey) {
                    SDL_memcpy(dst, &palmap[bit * 4], 3);
                }
                byte >>= srcbpp;
                dst += 3;
            }
            src += srcskip;
            dst += dstskip;
        }
    } નહીંતર {
        જ્યારે (height--) {
            Uint8 byte = 0, bit;
            માટે (c = 0; c < info->leading_skip; ++c) {
                જો (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            માટે (; c < width; ++c) {
                જો (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                જો (bit != ckey) {
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

SDL_FORCE_INLINE શૂન્ય Blit_Bto4_ચાવી(SDL_BlitInfo *info, અચલ Uint32 srcbpp)
{
    અચલ Uint32 mask = (1 << srcbpp) - 1;
    અચલ Uint32 align = (8 / srcbpp) - 1;

    પૂર્ણાંક width = info->dst_w;
    પૂર્ણાંક height = info->dst_h;
    Uint8 *src = info->src;
    Uint32 *dstp = (Uint32 *)info->dst;
    પૂર્ણાંક srcskip = info->src_skip;
    પૂર્ણાંક dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->table;
    પૂર્ણાંક c;

    width += info->leading_skip;

    જો (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    નહીંતર જો (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    નહીંતર જો (srcbpp == 1)
        srcskip += width - (width + 7) / 8;
    dstskip /= 4;

    જો (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        જ્યારે (height--) {
            Uint8 byte = 0, bit;
            માટે (c = 0; c < info->leading_skip; ++c) {
                જો (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            માટે (; c < width; ++c) {
                જો (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                જો (bit != ckey) {
                    *dstp = ((Uint32 *)palmap)[bit];
                }
                byte >>= srcbpp;
                dstp++;
            }
            src += srcskip;
            dstp += dstskip;
        }
    } નહીંતર {
        જ્યારે (height--) {
            Uint8 byte = 0, bit;
            માટે (c = 0; c < info->leading_skip; ++c) {
                જો (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            માટે (; c < width; ++c) {
                જો (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                જો (bit != ckey) {
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

સ્થિર શૂન્ય BlitBtoNAlpha(SDL_BlitInfo *info)
{
    પૂર્ણાંક width = info->dst_w;
    પૂર્ણાંક height = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    પૂર્ણાંક srcskip = info->src_skip;
    પૂર્ણાંક dstskip = info->dst_skip;
    અચલ SDL_Color *srcpal = info->src_pal->colors;
    અચલ SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    અચલ SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    પૂર્ણાંક srcbpp, dstbpp;
    પૂર્ણાંક c;
    Uint32 pixelvalue, mask, align;
    unsigned sR, sG, sB;
    unsigned dR, dG, dB, dA;
    અચલ unsigned A = info->a;

    width += info->leading_skip;

    srcbpp = srcfmt->bytes_per_pixel;
    dstbpp = dstfmt->bytes_per_pixel;
    જો (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    નહીંતર જો (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    નહીંતર જો (srcbpp == 1)
        srcskip += width - (width + 7) / 8;
    mask = (1 << srcbpp) - 1;
    align = (8 / srcbpp) - 1;

    જો (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        જ્યારે (height--) {
            Uint8 byte = 0, bit;
            માટે (c = 0; c < info->leading_skip; ++c) {
                જો (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            માટે (; c < width; ++c) {
                જો (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                જો (1) {
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
    } નહીંતર {
        જ્યારે (height--) {
            Uint8 byte = 0, bit;
            માટે (c = 0; c < info->leading_skip; ++c) {
                જો (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            માટે (; c < width; ++c) {
                જો (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                જો (1) {
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

સ્થિર શૂન્ય Blit_Bto_NAlpha_ચાવી(SDL_BlitInfo *info)
{
    પૂર્ણાંક width = info->dst_w;
    પૂર્ણાંક height = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    પૂર્ણાંક srcskip = info->src_skip;
    પૂર્ણાંક dstskip = info->dst_skip;
    અચલ SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    અચલ SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    અચલ SDL_Color *srcpal = info->src_pal->colors;
    પૂર્ણાંક srcbpp, dstbpp;
    પૂર્ણાંક c;
    Uint32 pixelvalue, mask, align;
    unsigned sR, sG, sB;
    unsigned dR, dG, dB, dA;
    અચલ unsigned A = info->a;
    Uint32 ckey = info->colorkey;

    width += info->leading_skip;

    srcbpp = srcfmt->bytes_per_pixel;
    dstbpp = dstfmt->bytes_per_pixel;
    જો (srcbpp == 4)
        srcskip += width - (width + 1) / 2;
    નહીંતર જો (srcbpp == 2)
        srcskip += width - (width + 3) / 4;
    નહીંતર જો (srcbpp == 1)
        srcskip += width - (width + 7) / 8;
    mask = (1 << srcbpp) - 1;
    align = (8 / srcbpp) - 1;

    જો (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        જ્યારે (height--) {
            Uint8 byte = 0, bit;
            માટે (c = 0; c < info->leading_skip; ++c) {
                જો (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            માટે (; c < width; ++c) {
                જો (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte & mask);
                જો (bit != ckey) {
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
    } નહીંતર {
        જ્યારે (height--) {
            Uint8 byte = 0, bit;
            માટે (c = 0; c < info->leading_skip; ++c) {
                જો (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            માટે (; c < width; ++c) {
                જો (!(c & align)) {
                    byte = *src++;
                }
                bit = (byte >> (8 - srcbpp)) & mask;
                જો (bit != ckey) {
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



સ્થિર શૂન્ય Blit1bto1(SDL_BlitInfo *info) {
    BlitBto1(info, 1);
}

સ્થિર શૂન્ય Blit1bto2(SDL_BlitInfo *info) {
    BlitBto2(info, 1);
}

સ્થિર શૂન્ય Blit1bto3(SDL_BlitInfo *info) {
    BlitBto3(info, 1);
}

સ્થિર શૂન્ય Blit1bto4(SDL_BlitInfo *info) {
    BlitBto4(info, 1);
}

સ્થિર અચલ SDL_BlitFunc bitmap_blit_1b[] = {
    (SDL_BlitFunc)ખાલી, Blit1bto1, Blit1bto2, Blit1bto3, Blit1bto4
};

સ્થિર શૂન્ય Blit1bto1_ચાવી(SDL_BlitInfo *info) {
    Blit_Bto1_ચાવી(info, 1);
}

સ્થિર શૂન્ય Blit1bto2_ચાવી(SDL_BlitInfo *info) {
    Blit_Bto2_ચાવી(info, 1);
}

સ્થિર શૂન્ય Blit1bto3_ચાવી(SDL_BlitInfo *info) {
    Blit_Bto3_ચાવી(info, 1);
}

સ્થિર શૂન્ય Blit1bto4_ચાવી(SDL_BlitInfo *info) {
    Blit_Bto4_ચાવી(info, 1);
}

સ્થિર અચલ SDL_BlitFunc colorkey_blit_1b[] = {
    (SDL_BlitFunc)ખાલી, Blit1bto1_ચાવી, Blit1bto2_ચાવી, Blit1bto3_ચાવી, Blit1bto4_ચાવી
};



સ્થિર શૂન્ય Blit2bto1(SDL_BlitInfo *info) {
    BlitBto1(info, 2);
}

સ્થિર શૂન્ય Blit2bto2(SDL_BlitInfo *info) {
    BlitBto2(info, 2);
}

સ્થિર શૂન્ય Blit2bto3(SDL_BlitInfo *info) {
    BlitBto3(info, 2);
}

સ્થિર શૂન્ય Blit2bto4(SDL_BlitInfo *info) {
    BlitBto4(info, 2);
}

સ્થિર અચલ SDL_BlitFunc bitmap_blit_2b[] = {
    (SDL_BlitFunc)ખાલી, Blit2bto1, Blit2bto2, Blit2bto3, Blit2bto4
};

સ્થિર શૂન્ય Blit2bto1_ચાવી(SDL_BlitInfo *info) {
    Blit_Bto1_ચાવી(info, 2);
}

સ્થિર શૂન્ય Blit2bto2_ચાવી(SDL_BlitInfo *info) {
    Blit_Bto2_ચાવી(info, 2);
}

સ્થિર શૂન્ય Blit2bto3_ચાવી(SDL_BlitInfo *info) {
    Blit_Bto3_ચાવી(info, 2);
}

સ્થિર શૂન્ય Blit2bto4_ચાવી(SDL_BlitInfo *info) {
    Blit_Bto4_ચાવી(info, 2);
}

સ્થિર અચલ SDL_BlitFunc colorkey_blit_2b[] = {
    (SDL_BlitFunc)ખાલી, Blit2bto1_ચાવી, Blit2bto2_ચાવી, Blit2bto3_ચાવી, Blit2bto4_ચાવી
};



સ્થિર શૂન્ય Blit4bto1(SDL_BlitInfo *info) {
    BlitBto1(info, 4);
}

સ્થિર શૂન્ય Blit4bto2(SDL_BlitInfo *info) {
    BlitBto2(info, 4);
}

સ્થિર શૂન્ય Blit4bto3(SDL_BlitInfo *info) {
    BlitBto3(info, 4);
}

સ્થિર શૂન્ય Blit4bto4(SDL_BlitInfo *info) {
    BlitBto4(info, 4);
}

સ્થિર અચલ SDL_BlitFunc bitmap_blit_4b[] = {
    (SDL_BlitFunc)ખાલી, Blit4bto1, Blit4bto2, Blit4bto3, Blit4bto4
};

સ્થિર શૂન્ય Blit4bto1_ચાવી(SDL_BlitInfo *info) {
    Blit_Bto1_ચાવી(info, 4);
}

સ્થિર શૂન્ય Blit4bto2_ચાવી(SDL_BlitInfo *info) {
    Blit_Bto2_ચાવી(info, 4);
}

સ્થિર શૂન્ય Blit4bto3_ચાવી(SDL_BlitInfo *info) {
    Blit_Bto3_ચાવી(info, 4);
}

સ્થિર શૂન્ય Blit4bto4_ચાવી(SDL_BlitInfo *info) {
    Blit_Bto4_ચાવી(info, 4);
}

સ્થિર અચલ SDL_BlitFunc colorkey_blit_4b[] = {
    (SDL_BlitFunc)ખાલી, Blit4bto1_ચાવી, Blit4bto2_ચાવી, Blit4bto3_ચાવી, Blit4bto4_ચાવી
};



SDL_BlitFunc SDL_CalculateBlit0(SDL_Surface *surface)
{
    પૂર્ણાંક which;

    જો (SDL_BITSPERPIXEL(surface->map.info.dst_fmt->format) < 8) {
        which = 0;
    } નહીંતર {
        which = SDL_BYTESPERPIXEL(surface->map.info.dst_fmt->format);
    }

    જો (SDL_PIXELTYPE(surface->format) == SDL_PIXELTYPE_INDEX1) {
        પસંદગી (surface->map.info.flags & ~SDL_COPY_RLE_MASK) {
        સ્થિતિ 0:
            જો (which < SDL_arraysize(bitmap_blit_1b)) {
                પાછા bitmap_blit_1b[which];
            }
            તોડો;

        સ્થિતિ SDL_COPY_COLORKEY:
            જો (which < SDL_arraysize(colorkey_blit_1b)) {
                પાછા colorkey_blit_1b[which];
            }
            તોડો;

        સ્થિતિ SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            પાછા which >= 2 ? BlitBtoNAlpha : (SDL_BlitFunc)ખાલી;

        સ્થિતિ SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            પાછા which >= 2 ? Blit_Bto_NAlpha_ચાવી : (SDL_BlitFunc)ખાલી;
        }
        પાછા ખાલી;
    }

    જો (SDL_PIXELTYPE(surface->format) == SDL_PIXELTYPE_INDEX2) {
        પસંદગી (surface->map.info.flags & ~SDL_COPY_RLE_MASK) {
        સ્થિતિ 0:
            જો (which < SDL_arraysize(bitmap_blit_2b)) {
                પાછા bitmap_blit_2b[which];
            }
            તોડો;

        સ્થિતિ SDL_COPY_COLORKEY:
            જો (which < SDL_arraysize(colorkey_blit_2b)) {
                પાછા colorkey_blit_2b[which];
            }
            તોડો;

        સ્થિતિ SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            પાછા which >= 2 ? BlitBtoNAlpha : (SDL_BlitFunc)ખાલી;

        સ્થિતિ SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            પાછા which >= 2 ? Blit_Bto_NAlpha_ચાવી : (SDL_BlitFunc)ખાલી;
        }
        પાછા ખાલી;
    }

    જો (SDL_PIXELTYPE(surface->format) == SDL_PIXELTYPE_INDEX4) {
        પસંદગી (surface->map.info.flags & ~SDL_COPY_RLE_MASK) {
        સ્થિતિ 0:
            જો (which < SDL_arraysize(bitmap_blit_4b)) {
                પાછા bitmap_blit_4b[which];
            }
            તોડો;

        સ્થિતિ SDL_COPY_COLORKEY:
            જો (which < SDL_arraysize(colorkey_blit_4b)) {
                પાછા colorkey_blit_4b[which];
            }
            તોડો;

        સ્થિતિ SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            પાછા which >= 2 ? BlitBtoNAlpha : (SDL_BlitFunc)ખાલી;

        સ્થિતિ SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            પાછા which >= 2 ? Blit_Bto_NAlpha_ચાવી : (SDL_BlitFunc)ખાલી;
        }
        પાછા ખાલી;
    }

    પાછા ખાલી;
}

#endif // SDL_HAVE_BLIT_0
