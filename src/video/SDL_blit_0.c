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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_HAVE_BLIT_0

#ಅನ್ತರ್ಭಾವ "SDL_surface_c.h"

// Functions to blit from bitmaps to other surfaces

SDL_FORCE_INLINE ಶೂನ್ಯ BlitBto1(SDL_BlitInfo *info, ಸ್ಥಿರಾಂಕ Uint32 srcbpp)
{
    ಸ್ಥಿರಾಂಕ Uint32 ಮುಖವಾಡ = (1 << srcbpp) - 1;
    ಸ್ಥಿರಾಂಕ Uint32 align = (8 / srcbpp) - 1;

    ಪೂರ್ಣಾಂಕ c;
    ಪೂರ್ಣಾಂಕ ಅಗಲ, ಎತ್ತರ;
    Uint8 *src, *map, *dst;
    ಪೂರ್ಣಾಂಕ srcskip, dstskip;

    // Set up some basic variables
    ಅಗಲ = info->dst_w;
    ಎತ್ತರ = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = info->ಕೋಷ್ಟಕ;

    ಅಗಲ += info->leading_skip;

    ಆದರೆ (srcbpp == 4)
        srcskip += ಅಗಲ - (ಅಗಲ + 1) / 2;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (srcbpp == 2)
        srcskip += ಅಗಲ - (ಅಗಲ + 3) / 4;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (srcbpp == 1)
        srcskip += ಅಗಲ - (ಅಗಲ + 7) / 8;

    ಆದರೆ (map) {
        ಆದರೆ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            ಆಗ (ಎತ್ತರ--) {
                Uint8 byte = 0, ಬಿಟ್;
                ಗಾಗಿ (c = 0; c < info->leading_skip; ++c) {
                    ಆದರೆ (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                ಗಾಗಿ (; c < ಅಗಲ; ++c) {
                    ಆದರೆ (!(c & align)) {
                        byte = *src++;
                    }
                    ಬಿಟ್ = (byte & ಮುಖವಾಡ);
                    ಆದರೆ (1) {
                        *dst = map[ಬಿಟ್];
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಆಗ (ಎತ್ತರ--) {
                Uint8 byte = 0, ಬಿಟ್;
                ಗಾಗಿ (c = 0; c < info->leading_skip; ++c) {
                    ಆದರೆ (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                ಗಾಗಿ (; c < ಅಗಲ; ++c) {
                    ಆದರೆ (!(c & align)) {
                        byte = *src++;
                    }
                    ಬಿಟ್ = (byte >> (8 - srcbpp)) & ಮುಖವಾಡ;
                    ಆದರೆ (1) {
                        *dst = map[ಬಿಟ್];
                    }
                    dst++;
                    byte <<= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            ಆಗ (ಎತ್ತರ--) {
                Uint8 byte = 0, ಬಿಟ್;
                ಗಾಗಿ (c = 0; c < info->leading_skip; ++c) {
                    ಆದರೆ (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                ಗಾಗಿ (; c < ಅಗಲ; ++c) {
                    ಆದರೆ (!(c & align)) {
                        byte = *src++;
                    }
                    ಬಿಟ್ = (byte & ಮುಖವಾಡ);
                    ಆದರೆ (1) {
                        *dst = ಬಿಟ್;
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಆಗ (ಎತ್ತರ--) {
                Uint8 byte = 0, ಬಿಟ್;
                ಗಾಗಿ (c = 0; c < info->leading_skip; ++c) {
                    ಆದರೆ (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                ಗಾಗಿ (; c < ಅಗಲ; ++c) {
                    ಆದರೆ (!(c & align)) {
                        byte = *src++;
                    }
                    ಬಿಟ್ = (byte >> (8 - srcbpp)) & ಮುಖವಾಡ;
                    ಆದರೆ (1) {
                        *dst = ಬಿಟ್;
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

SDL_FORCE_INLINE ಶೂನ್ಯ BlitBto2(SDL_BlitInfo *info, ಸ್ಥಿರಾಂಕ Uint32 srcbpp)
{
    ಸ್ಥಿರಾಂಕ Uint32 ಮುಖವಾಡ = (1 << srcbpp) - 1;
    ಸ್ಥಿರಾಂಕ Uint32 align = (8 / srcbpp) - 1;

    ಪೂರ್ಣಾಂಕ c;
    ಪೂರ್ಣಾಂಕ ಅಗಲ, ಎತ್ತರ;
    Uint8 *src;
    Uint16 *map, *dst;
    ಪೂರ್ಣಾಂಕ srcskip, dstskip;

    // Set up some basic variables
    ಅಗಲ = info->dst_w;
    ಎತ್ತರ = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = (Uint16 *)info->dst;
    dstskip = info->dst_skip / 2;
    map = (Uint16 *)info->ಕೋಷ್ಟಕ;

    ಅಗಲ += info->leading_skip;

    ಆದರೆ (srcbpp == 4)
        srcskip += ಅಗಲ - (ಅಗಲ + 1) / 2;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (srcbpp == 2)
        srcskip += ಅಗಲ - (ಅಗಲ + 3) / 4;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (srcbpp == 1)
        srcskip += ಅಗಲ - (ಅಗಲ + 7) / 8;

    ಆದರೆ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        ಆಗ (ಎತ್ತರ--) {
            Uint8 byte = 0, ಬಿಟ್;
            ಗಾಗಿ (c = 0; c < info->leading_skip; ++c) {
                ಆದರೆ (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            ಗಾಗಿ (; c < ಅಗಲ; ++c) {
                ಆದರೆ (!(c & align)) {
                    byte = *src++;
                }
                ಬಿಟ್ = (byte & ಮುಖವಾಡ);
                ಆದರೆ (1) {
                    *dst = map[ಬಿಟ್];
                }
                byte >>= srcbpp;
                dst++;
            }
            src += srcskip;
            dst += dstskip;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆಗ (ಎತ್ತರ--) {
            Uint8 byte = 0, ಬಿಟ್;
            ಗಾಗಿ (c = 0; c < info->leading_skip; ++c) {
                ಆದರೆ (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            ಗಾಗಿ (; c < ಅಗಲ; ++c) {
                ಆದರೆ (!(c & align)) {
                    byte = *src++;
                }
                ಬಿಟ್ = (byte >> (8 - srcbpp)) & ಮುಖವಾಡ;
                ಆದರೆ (1) {
                    *dst = map[ಬಿಟ್];
                }
                byte <<= srcbpp;
                dst++;
            }
            src += srcskip;
            dst += dstskip;
        }
    }
}

SDL_FORCE_INLINE ಶೂನ್ಯ BlitBto3(SDL_BlitInfo *info, ಸ್ಥಿರಾಂಕ Uint32 srcbpp)
{
    ಸ್ಥಿರಾಂಕ Uint32 ಮುಖವಾಡ = (1 << srcbpp) - 1;
    ಸ್ಥಿರಾಂಕ Uint32 align = (8 / srcbpp) - 1;

    ಪೂರ್ಣಾಂಕ c, o;
    ಪೂರ್ಣಾಂಕ ಅಗಲ, ಎತ್ತರ;
    Uint8 *src, *map, *dst;
    ಪೂರ್ಣಾಂಕ srcskip, dstskip;

    // Set up some basic variables
    ಅಗಲ = info->dst_w;
    ಎತ್ತರ = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = info->ಕೋಷ್ಟಕ;

    ಅಗಲ += info->leading_skip;

    ಆದರೆ (srcbpp == 4)
        srcskip += ಅಗಲ - (ಅಗಲ + 1) / 2;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (srcbpp == 2)
        srcskip += ಅಗಲ - (ಅಗಲ + 3) / 4;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (srcbpp == 1)
        srcskip += ಅಗಲ - (ಅಗಲ + 7) / 8;

    ಆದರೆ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        ಆಗ (ಎತ್ತರ--) {
            Uint8 byte = 0, ಬಿಟ್;
            ಗಾಗಿ (c = 0; c < info->leading_skip; ++c) {
                ಆದರೆ (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            ಗಾಗಿ (; c < ಅಗಲ; ++c) {
                ಆದರೆ (!(c & align)) {
                    byte = *src++;
                }
                ಬಿಟ್ = (byte & ಮುಖವಾಡ);
                ಆದರೆ (1) {
                    o = ಬಿಟ್ * 4;
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
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆಗ (ಎತ್ತರ--) {
            Uint8 byte = 0, ಬಿಟ್;
            ಗಾಗಿ (c = 0; c < info->leading_skip; ++c) {
                ಆದರೆ (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            ಗಾಗಿ (; c < ಅಗಲ; ++c) {
                ಆದರೆ (!(c & align)) {
                    byte = *src++;
                }
                ಬಿಟ್ = (byte >> (8 - srcbpp)) & ಮುಖವಾಡ;
                ಆದರೆ (1) {
                    o = ಬಿಟ್ * 4;
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

SDL_FORCE_INLINE ಶೂನ್ಯ BlitBto4(SDL_BlitInfo *info, ಸ್ಥಿರಾಂಕ Uint32 srcbpp)
{
    ಸ್ಥಿರಾಂಕ Uint32 ಮುಖವಾಡ = (1 << srcbpp) - 1;
    ಸ್ಥಿರಾಂಕ Uint32 align = (8 / srcbpp) - 1;

    ಪೂರ್ಣಾಂಕ ಅಗಲ, ಎತ್ತರ;
    Uint8 *src;
    Uint32 *map, *dst;
    ಪೂರ್ಣಾಂಕ srcskip, dstskip;
    ಪೂರ್ಣಾಂಕ c;

    // Set up some basic variables
    ಅಗಲ = info->dst_w;
    ಎತ್ತರ = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = (Uint32 *)info->dst;
    dstskip = info->dst_skip / 4;
    map = (Uint32 *)info->ಕೋಷ್ಟಕ;

    ಅಗಲ += info->leading_skip;

    ಆದರೆ (srcbpp == 4)
        srcskip += ಅಗಲ - (ಅಗಲ + 1) / 2;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (srcbpp == 2)
        srcskip += ಅಗಲ - (ಅಗಲ + 3) / 4;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (srcbpp == 1)
        srcskip += ಅಗಲ - (ಅಗಲ + 7) / 8;

    ಆದರೆ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        ಆಗ (ಎತ್ತರ--) {
            Uint8 byte = 0, ಬಿಟ್;
            ಗಾಗಿ (c = 0; c < info->leading_skip; ++c) {
                ಆದರೆ (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            ಗಾಗಿ (; c < ಅಗಲ; ++c) {
                ಆದರೆ (!(c & align)) {
                    byte = *src++;
                }
                ಬಿಟ್ = (byte & ಮುಖವಾಡ);
                ಆದರೆ (1) {
                    *dst = map[ಬಿಟ್];
                }
                byte >>= srcbpp;
                dst++;
            }
            src += srcskip;
            dst += dstskip;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆಗ (ಎತ್ತರ--) {
            Uint8 byte = 0, ಬಿಟ್;
            ಗಾಗಿ (c = 0; c < info->leading_skip; ++c) {
                ಆದರೆ (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            ಗಾಗಿ (; c < ಅಗಲ; ++c) {
                ಆದರೆ (!(c & align)) {
                    byte = *src++;
                }
                ಬಿಟ್ = (byte >> (8 - srcbpp)) & ಮುಖವಾಡ;
                ಆದರೆ (1) {
                    *dst = map[ಬಿಟ್];
                }
                byte <<= srcbpp;
                dst++;
            }
            src += srcskip;
            dst += dstskip;
        }
    }
}

SDL_FORCE_INLINE ಶೂನ್ಯ Blit_Bto1_ಕೀಲಿ(SDL_BlitInfo *info, ಸ್ಥಿರಾಂಕ Uint32 srcbpp)
{
    ಸ್ಥಿರಾಂಕ Uint32 ಮುಖವಾಡ = (1 << srcbpp) - 1;
    ಸ್ಥಿರಾಂಕ Uint32 align = (8 / srcbpp) - 1;

    ಪೂರ್ಣಾಂಕ ಅಗಲ = info->dst_w;
    ಪೂರ್ಣಾಂಕ ಎತ್ತರ = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    ಪೂರ್ಣಾಂಕ srcskip = info->src_skip;
    ಪೂರ್ಣಾಂಕ dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->ಕೋಷ್ಟಕ;
    ಪೂರ್ಣಾಂಕ c;

    ಅಗಲ += info->leading_skip;

    ಆದರೆ (srcbpp == 4)
        srcskip += ಅಗಲ - (ಅಗಲ + 1) / 2;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (srcbpp == 2)
        srcskip += ಅಗಲ - (ಅಗಲ + 3) / 4;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (srcbpp == 1)
        srcskip += ಅಗಲ - (ಅಗಲ + 7) / 8;

    ಆದರೆ (palmap) {
        ಆದರೆ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            ಆಗ (ಎತ್ತರ--) {
                Uint8 byte = 0, ಬಿಟ್;
                ಗಾಗಿ (c = 0; c < info->leading_skip; ++c) {
                    ಆದರೆ (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                ಗಾಗಿ (; c < ಅಗಲ; ++c) {
                    ಆದರೆ (!(c & align)) {
                        byte = *src++;
                    }
                    ಬಿಟ್ = (byte & ಮುಖವಾಡ);
                    ಆದರೆ (ಬಿಟ್ != ckey) {
                        *dst = palmap[ಬಿಟ್];
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಆಗ (ಎತ್ತರ--) {
                Uint8 byte = 0, ಬಿಟ್;
                ಗಾಗಿ (c = 0; c < info->leading_skip; ++c) {
                    ಆದರೆ (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                ಗಾಗಿ (; c < ಅಗಲ; ++c) {
                    ಆದರೆ (!(c & align)) {
                        byte = *src++;
                    }
                    ಬಿಟ್ = (byte >> (8 - srcbpp)) & ಮುಖವಾಡ;
                    ಆದರೆ (ಬಿಟ್ != ckey) {
                        *dst = palmap[ಬಿಟ್];
                    }
                    dst++;
                    byte <<= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            ಆಗ (ಎತ್ತರ--) {
                Uint8 byte = 0, ಬಿಟ್;
                ಗಾಗಿ (c = 0; c < info->leading_skip; ++c) {
                    ಆದರೆ (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                ಗಾಗಿ (; c < ಅಗಲ; ++c) {
                    ಆದರೆ (!(c & align)) {
                        byte = *src++;
                    }
                    ಬಿಟ್ = (byte & ಮುಖವಾಡ);
                    ಆದರೆ (ಬಿಟ್ != ckey) {
                        *dst = ಬಿಟ್;
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಆಗ (ಎತ್ತರ--) {
                Uint8 byte = 0, ಬಿಟ್;
                ಗಾಗಿ (c = 0; c < info->leading_skip; ++c) {
                    ಆದರೆ (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                ಗಾಗಿ (; c < ಅಗಲ; ++c) {
                    ಆದರೆ (!(c & align)) {
                        byte = *src++;
                    }
                    ಬಿಟ್ = (byte >> (8 - srcbpp)) & ಮುಖವಾಡ;
                    ಆದರೆ (ಬಿಟ್ != ckey) {
                        *dst = ಬಿಟ್;
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

SDL_FORCE_INLINE ಶೂನ್ಯ Blit_Bto2_ಕೀಲಿ(SDL_BlitInfo *info, ಸ್ಥಿರಾಂಕ Uint32 srcbpp)
{
    ಸ್ಥಿರಾಂಕ Uint32 ಮುಖವಾಡ = (1 << srcbpp) - 1;
    ಸ್ಥಿರಾಂಕ Uint32 align = (8 / srcbpp) - 1;

    ಪೂರ್ಣಾಂಕ ಅಗಲ = info->dst_w;
    ಪೂರ್ಣಾಂಕ ಎತ್ತರ = info->dst_h;
    Uint8 *src = info->src;
    Uint16 *dstp = (Uint16 *)info->dst;
    ಪೂರ್ಣಾಂಕ srcskip = info->src_skip;
    ಪೂರ್ಣಾಂಕ dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->ಕೋಷ್ಟಕ;
    ಪೂರ್ಣಾಂಕ c;

    ಅಗಲ += info->leading_skip;

    ಆದರೆ (srcbpp == 4)
        srcskip += ಅಗಲ - (ಅಗಲ + 1) / 2;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (srcbpp == 2)
        srcskip += ಅಗಲ - (ಅಗಲ + 3) / 4;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (srcbpp == 1)
        srcskip += ಅಗಲ - (ಅಗಲ + 7) / 8;
    dstskip /= 2;

    ಆದರೆ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        ಆಗ (ಎತ್ತರ--) {
            Uint8 byte = 0, ಬಿಟ್;
            ಗಾಗಿ (c = 0; c < info->leading_skip; ++c) {
                ಆದರೆ (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            ಗಾಗಿ (; c < ಅಗಲ; ++c) {
                ಆದರೆ (!(c & align)) {
                    byte = *src++;
                }
                ಬಿಟ್ = (byte & ಮುಖವಾಡ);
                ಆದರೆ (ಬಿಟ್ != ckey) {
                    *dstp = ((Uint16 *)palmap)[ಬಿಟ್];
                }
                byte >>= srcbpp;
                dstp++;
            }
            src += srcskip;
            dstp += dstskip;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆಗ (ಎತ್ತರ--) {
            Uint8 byte = 0, ಬಿಟ್;
            ಗಾಗಿ (c = 0; c < info->leading_skip; ++c) {
                ಆದರೆ (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            ಗಾಗಿ (; c < ಅಗಲ; ++c) {
                ಆದರೆ (!(c & align)) {
                    byte = *src++;
                }
                ಬಿಟ್ = (byte >> (8 - srcbpp)) & ಮುಖವಾಡ;
                ಆದರೆ (ಬಿಟ್ != ckey) {
                    *dstp = ((Uint16 *)palmap)[ಬಿಟ್];
                }
                byte <<= srcbpp;
                dstp++;
            }
            src += srcskip;
            dstp += dstskip;
        }
    }
}

SDL_FORCE_INLINE ಶೂನ್ಯ Blit_Bto3_ಕೀಲಿ(SDL_BlitInfo *info, ಸ್ಥಿರಾಂಕ Uint32 srcbpp)
{
    ಸ್ಥಿರಾಂಕ Uint32 ಮುಖವಾಡ = (1 << srcbpp) - 1;
    ಸ್ಥಿರಾಂಕ Uint32 align = (8 / srcbpp) - 1;

    ಪೂರ್ಣಾಂಕ ಅಗಲ = info->dst_w;
    ಪೂರ್ಣಾಂಕ ಎತ್ತರ = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    ಪೂರ್ಣಾಂಕ srcskip = info->src_skip;
    ಪೂರ್ಣಾಂಕ dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->ಕೋಷ್ಟಕ;
    ಪೂರ್ಣಾಂಕ c;

    ಅಗಲ += info->leading_skip;

    ಆದರೆ (srcbpp == 4)
        srcskip += ಅಗಲ - (ಅಗಲ + 1) / 2;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (srcbpp == 2)
        srcskip += ಅಗಲ - (ಅಗಲ + 3) / 4;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (srcbpp == 1)
        srcskip += ಅಗಲ - (ಅಗಲ + 7) / 8;

    ಆದರೆ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        ಆಗ (ಎತ್ತರ--) {
            Uint8 byte = 0, ಬಿಟ್;
            ಗಾಗಿ (c = 0; c < info->leading_skip; ++c) {
                ಆದರೆ (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            ಗಾಗಿ (; c < ಅಗಲ; ++c) {
                ಆದರೆ (!(c & align)) {
                    byte = *src++;
                }
                ಬಿಟ್ = (byte & ಮುಖವಾಡ);
                ಆದರೆ (ಬಿಟ್ != ckey) {
                    SDL_memcpy(dst, &palmap[ಬಿಟ್ * 4], 3);
                }
                byte >>= srcbpp;
                dst += 3;
            }
            src += srcskip;
            dst += dstskip;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆಗ (ಎತ್ತರ--) {
            Uint8 byte = 0, ಬಿಟ್;
            ಗಾಗಿ (c = 0; c < info->leading_skip; ++c) {
                ಆದರೆ (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            ಗಾಗಿ (; c < ಅಗಲ; ++c) {
                ಆದರೆ (!(c & align)) {
                    byte = *src++;
                }
                ಬಿಟ್ = (byte >> (8 - srcbpp)) & ಮುಖವಾಡ;
                ಆದರೆ (ಬಿಟ್ != ckey) {
                    SDL_memcpy(dst, &palmap[ಬಿಟ್ * 4], 3);
                }
                byte <<= srcbpp;
                dst += 3;
            }
            src += srcskip;
            dst += dstskip;
        }
    }
}

SDL_FORCE_INLINE ಶೂನ್ಯ Blit_Bto4_ಕೀಲಿ(SDL_BlitInfo *info, ಸ್ಥಿರಾಂಕ Uint32 srcbpp)
{
    ಸ್ಥಿರಾಂಕ Uint32 ಮುಖವಾಡ = (1 << srcbpp) - 1;
    ಸ್ಥಿರಾಂಕ Uint32 align = (8 / srcbpp) - 1;

    ಪೂರ್ಣಾಂಕ ಅಗಲ = info->dst_w;
    ಪೂರ್ಣಾಂಕ ಎತ್ತರ = info->dst_h;
    Uint8 *src = info->src;
    Uint32 *dstp = (Uint32 *)info->dst;
    ಪೂರ್ಣಾಂಕ srcskip = info->src_skip;
    ಪೂರ್ಣಾಂಕ dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->ಕೋಷ್ಟಕ;
    ಪೂರ್ಣಾಂಕ c;

    ಅಗಲ += info->leading_skip;

    ಆದರೆ (srcbpp == 4)
        srcskip += ಅಗಲ - (ಅಗಲ + 1) / 2;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (srcbpp == 2)
        srcskip += ಅಗಲ - (ಅಗಲ + 3) / 4;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (srcbpp == 1)
        srcskip += ಅಗಲ - (ಅಗಲ + 7) / 8;
    dstskip /= 4;

    ಆದರೆ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        ಆಗ (ಎತ್ತರ--) {
            Uint8 byte = 0, ಬಿಟ್;
            ಗಾಗಿ (c = 0; c < info->leading_skip; ++c) {
                ಆದರೆ (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            ಗಾಗಿ (; c < ಅಗಲ; ++c) {
                ಆದರೆ (!(c & align)) {
                    byte = *src++;
                }
                ಬಿಟ್ = (byte & ಮುಖವಾಡ);
                ಆದರೆ (ಬಿಟ್ != ckey) {
                    *dstp = ((Uint32 *)palmap)[ಬಿಟ್];
                }
                byte >>= srcbpp;
                dstp++;
            }
            src += srcskip;
            dstp += dstskip;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆಗ (ಎತ್ತರ--) {
            Uint8 byte = 0, ಬಿಟ್;
            ಗಾಗಿ (c = 0; c < info->leading_skip; ++c) {
                ಆದರೆ (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            ಗಾಗಿ (; c < ಅಗಲ; ++c) {
                ಆದರೆ (!(c & align)) {
                    byte = *src++;
                }
                ಬಿಟ್ = (byte >> (8 - srcbpp)) & ಮುಖವಾಡ;
                ಆದರೆ (ಬಿಟ್ != ckey) {
                    *dstp = ((Uint32 *)palmap)[ಬಿಟ್];
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
    ಪೂರ್ಣಾಂಕ ಅಗಲ = info->dst_w;
    ಪೂರ್ಣಾಂಕ ಎತ್ತರ = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    ಪೂರ್ಣಾಂಕ srcskip = info->src_skip;
    ಪೂರ್ಣಾಂಕ dstskip = info->dst_skip;
    ಸ್ಥಿರಾಂಕ SDL_Color *srcpal = info->src_pal->colors;
    ಸ್ಥಿರಾಂಕ SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    ಸ್ಥಿರಾಂಕ SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    ಪೂರ್ಣಾಂಕ srcbpp, dstbpp;
    ಪೂರ್ಣಾಂಕ c;
    Uint32 pixelvalue, ಮುಖವಾಡ, align;
    ಚಿಹ್ನೆರಹಿತ sR, sG, sB;
    ಚಿಹ್ನೆರಹಿತ dR, dG, dB, dA;
    ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ A = info->a;

    ಅಗಲ += info->leading_skip;

    srcbpp = srcfmt->ಬೈಟುಗಳು_ಪ್ರತಿ_pixel;
    dstbpp = dstfmt->ಬೈಟುಗಳು_ಪ್ರತಿ_pixel;
    ಆದರೆ (srcbpp == 4)
        srcskip += ಅಗಲ - (ಅಗಲ + 1) / 2;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (srcbpp == 2)
        srcskip += ಅಗಲ - (ಅಗಲ + 3) / 4;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (srcbpp == 1)
        srcskip += ಅಗಲ - (ಅಗಲ + 7) / 8;
    ಮುಖವಾಡ = (1 << srcbpp) - 1;
    align = (8 / srcbpp) - 1;

    ಆದರೆ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        ಆಗ (ಎತ್ತರ--) {
            Uint8 byte = 0, ಬಿಟ್;
            ಗಾಗಿ (c = 0; c < info->leading_skip; ++c) {
                ಆದರೆ (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            ಗಾಗಿ (; c < ಅಗಲ; ++c) {
                ಆದರೆ (!(c & align)) {
                    byte = *src++;
                }
                ಬಿಟ್ = (byte & ಮುಖವಾಡ);
                ಆದರೆ (1) {
                    sR = srcpal[ಬಿಟ್].r;
                    sG = srcpal[ಬಿಟ್].g;
                    sB = srcpal[ಬಿಟ್].b;
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
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆಗ (ಎತ್ತರ--) {
            Uint8 byte = 0, ಬಿಟ್;
            ಗಾಗಿ (c = 0; c < info->leading_skip; ++c) {
                ಆದರೆ (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            ಗಾಗಿ (; c < ಅಗಲ; ++c) {
                ಆದರೆ (!(c & align)) {
                    byte = *src++;
                }
                ಬಿಟ್ = (byte >> (8 - srcbpp)) & ಮುಖವಾಡ;
                ಆದರೆ (1) {
                    sR = srcpal[ಬಿಟ್].r;
                    sG = srcpal[ಬಿಟ್].g;
                    sB = srcpal[ಬಿಟ್].b;
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
    ಪೂರ್ಣಾಂಕ ಅಗಲ = info->dst_w;
    ಪೂರ್ಣಾಂಕ ಎತ್ತರ = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    ಪೂರ್ಣಾಂಕ srcskip = info->src_skip;
    ಪೂರ್ಣಾಂಕ dstskip = info->dst_skip;
    ಸ್ಥಿರಾಂಕ SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    ಸ್ಥಿರಾಂಕ SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    ಸ್ಥಿರಾಂಕ SDL_Color *srcpal = info->src_pal->colors;
    ಪೂರ್ಣಾಂಕ srcbpp, dstbpp;
    ಪೂರ್ಣಾಂಕ c;
    Uint32 pixelvalue, ಮುಖವಾಡ, align;
    ಚಿಹ್ನೆರಹಿತ sR, sG, sB;
    ಚಿಹ್ನೆರಹಿತ dR, dG, dB, dA;
    ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ A = info->a;
    Uint32 ckey = info->colorkey;

    ಅಗಲ += info->leading_skip;

    srcbpp = srcfmt->ಬೈಟುಗಳು_ಪ್ರತಿ_pixel;
    dstbpp = dstfmt->ಬೈಟುಗಳು_ಪ್ರತಿ_pixel;
    ಆದರೆ (srcbpp == 4)
        srcskip += ಅಗಲ - (ಅಗಲ + 1) / 2;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (srcbpp == 2)
        srcskip += ಅಗಲ - (ಅಗಲ + 3) / 4;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (srcbpp == 1)
        srcskip += ಅಗಲ - (ಅಗಲ + 7) / 8;
    ಮುಖವಾಡ = (1 << srcbpp) - 1;
    align = (8 / srcbpp) - 1;

    ಆದರೆ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        ಆಗ (ಎತ್ತರ--) {
            Uint8 byte = 0, ಬಿಟ್;
            ಗಾಗಿ (c = 0; c < info->leading_skip; ++c) {
                ಆದರೆ (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            ಗಾಗಿ (; c < ಅಗಲ; ++c) {
                ಆದರೆ (!(c & align)) {
                    byte = *src++;
                }
                ಬಿಟ್ = (byte & ಮುಖವಾಡ);
                ಆದರೆ (ಬಿಟ್ != ckey) {
                    sR = srcpal[ಬಿಟ್].r;
                    sG = srcpal[ಬಿಟ್].g;
                    sB = srcpal[ಬಿಟ್].b;
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
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆಗ (ಎತ್ತರ--) {
            Uint8 byte = 0, ಬಿಟ್;
            ಗಾಗಿ (c = 0; c < info->leading_skip; ++c) {
                ಆದರೆ (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            ಗಾಗಿ (; c < ಅಗಲ; ++c) {
                ಆದರೆ (!(c & align)) {
                    byte = *src++;
                }
                ಬಿಟ್ = (byte >> (8 - srcbpp)) & ಮುಖವಾಡ;
                ಆದರೆ (ಬಿಟ್ != ckey) {
                    sR = srcpal[ಬಿಟ್].r;
                    sG = srcpal[ಬಿಟ್].g;
                    sB = srcpal[ಬಿಟ್].b;
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

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ SDL_BlitFunc bitmap_blit_1b[] = {
    (SDL_BlitFunc)ಖಾಲಿ, Blit1bto1, Blit1bto2, Blit1bto3, Blit1bto4
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

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ SDL_BlitFunc colorkey_blit_1b[] = {
    (SDL_BlitFunc)ಖಾಲಿ, Blit1bto1_ಕೀಲಿ, Blit1bto2_ಕೀಲಿ, Blit1bto3_ಕೀಲಿ, Blit1bto4_ಕೀಲಿ
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

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ SDL_BlitFunc bitmap_blit_2b[] = {
    (SDL_BlitFunc)ಖಾಲಿ, Blit2bto1, Blit2bto2, Blit2bto3, Blit2bto4
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

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ SDL_BlitFunc colorkey_blit_2b[] = {
    (SDL_BlitFunc)ಖಾಲಿ, Blit2bto1_ಕೀಲಿ, Blit2bto2_ಕೀಲಿ, Blit2bto3_ಕೀಲಿ, Blit2bto4_ಕೀಲಿ
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

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ SDL_BlitFunc bitmap_blit_4b[] = {
    (SDL_BlitFunc)ಖಾಲಿ, Blit4bto1, Blit4bto2, Blit4bto3, Blit4bto4
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

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ SDL_BlitFunc colorkey_blit_4b[] = {
    (SDL_BlitFunc)ಖಾಲಿ, Blit4bto1_ಕೀಲಿ, Blit4bto2_ಕೀಲಿ, Blit4bto3_ಕೀಲಿ, Blit4bto4_ಕೀಲಿ
};



SDL_BlitFunc SDL_CalculateBlit0(SDL_Surface *surface)
{
    ಪೂರ್ಣಾಂಕ which;

    ಆದರೆ (SDL_BITSPERPIXEL(surface->map.info.dst_fmt->format) < 8) {
        which = 0;
    } ಇಲ್ಲದಿದ್ದರೆ {
        which = SDL_BYTESPERPIXEL(surface->map.info.dst_fmt->format);
    }

    ಆದರೆ (SDL_PIXELTYPE(surface->format) == SDL_PIXELTYPE_INDEX1) {
        ಆಯ್ಕೆ (surface->map.info.flags & ~SDL_COPY_RLE_ಮುಖವಾಡ) {
        ಸ್ಥಿತಿ 0:
            ಆದರೆ (which < SDL_arraysize(bitmap_blit_1b)) {
                ಹಿಂತಿರುಗಿ bitmap_blit_1b[which];
            }
            ನಿಲ್ಲಿಸು;

        ಸ್ಥಿತಿ SDL_COPY_COLORKEY:
            ಆದರೆ (which < SDL_arraysize(colorkey_blit_1b)) {
                ಹಿಂತಿರುಗಿ colorkey_blit_1b[which];
            }
            ನಿಲ್ಲಿಸು;

        ಸ್ಥಿತಿ SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            ಹಿಂತಿರುಗಿ which >= 2 ? BlitBtoNAlpha : (SDL_BlitFunc)ಖಾಲಿ;

        ಸ್ಥಿತಿ SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            ಹಿಂತಿರುಗಿ which >= 2 ? Blit_Bto_NAlpha_ಕೀಲಿ : (SDL_BlitFunc)ಖಾಲಿ;
        }
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಆದರೆ (SDL_PIXELTYPE(surface->format) == SDL_PIXELTYPE_INDEX2) {
        ಆಯ್ಕೆ (surface->map.info.flags & ~SDL_COPY_RLE_ಮುಖವಾಡ) {
        ಸ್ಥಿತಿ 0:
            ಆದರೆ (which < SDL_arraysize(bitmap_blit_2b)) {
                ಹಿಂತಿರುಗಿ bitmap_blit_2b[which];
            }
            ನಿಲ್ಲಿಸು;

        ಸ್ಥಿತಿ SDL_COPY_COLORKEY:
            ಆದರೆ (which < SDL_arraysize(colorkey_blit_2b)) {
                ಹಿಂತಿರುಗಿ colorkey_blit_2b[which];
            }
            ನಿಲ್ಲಿಸು;

        ಸ್ಥಿತಿ SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            ಹಿಂತಿರುಗಿ which >= 2 ? BlitBtoNAlpha : (SDL_BlitFunc)ಖಾಲಿ;

        ಸ್ಥಿತಿ SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            ಹಿಂತಿರುಗಿ which >= 2 ? Blit_Bto_NAlpha_ಕೀಲಿ : (SDL_BlitFunc)ಖಾಲಿ;
        }
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಆದರೆ (SDL_PIXELTYPE(surface->format) == SDL_PIXELTYPE_INDEX4) {
        ಆಯ್ಕೆ (surface->map.info.flags & ~SDL_COPY_RLE_ಮುಖವಾಡ) {
        ಸ್ಥಿತಿ 0:
            ಆದರೆ (which < SDL_arraysize(bitmap_blit_4b)) {
                ಹಿಂತಿರುಗಿ bitmap_blit_4b[which];
            }
            ನಿಲ್ಲಿಸು;

        ಸ್ಥಿತಿ SDL_COPY_COLORKEY:
            ಆದರೆ (which < SDL_arraysize(colorkey_blit_4b)) {
                ಹಿಂತಿರುಗಿ colorkey_blit_4b[which];
            }
            ನಿಲ್ಲಿಸು;

        ಸ್ಥಿತಿ SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            ಹಿಂತಿರುಗಿ which >= 2 ? BlitBtoNAlpha : (SDL_BlitFunc)ಖಾಲಿ;

        ಸ್ಥಿತಿ SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            ಹಿಂತಿರುಗಿ which >= 2 ? Blit_Bto_NAlpha_ಕೀಲಿ : (SDL_BlitFunc)ಖಾಲಿ;
        }
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_HAVE_BLIT_0
