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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_HAVE_BLIT_0

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_surface_c.h"

// Functions to blit from bitmaps to other surfaces

SDL_FORCE_INLINE ਖਾਲੀ BlitBto1(SDL_BlitInfo *info, ਅਚਲ Uint32 srcbpp)
{
    ਅਚਲ Uint32 ਨਕਾਬ = (1 << srcbpp) - 1;
    ਅਚਲ Uint32 align = (8 / srcbpp) - 1;

    ਪੂਰਨ c;
    ਪੂਰਨ ਚੌੜਾਈ, ਉਚਾਈ;
    Uint8 *src, *map, *dst;
    ਪੂਰਨ srcskip, dstskip;

    // Set up some basic variables
    ਚੌੜਾਈ = info->dst_w;
    ਉਚਾਈ = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = info->ਸਾਰਣੀ;

    ਚੌੜਾਈ += info->leading_skip;

    ਜੇ (srcbpp == 4)
        srcskip += ਚੌੜਾਈ - (ਚੌੜਾਈ + 1) / 2;
    ਨਹੀਂਤਾਂ ਜੇ (srcbpp == 2)
        srcskip += ਚੌੜਾਈ - (ਚੌੜਾਈ + 3) / 4;
    ਨਹੀਂਤਾਂ ਜੇ (srcbpp == 1)
        srcskip += ਚੌੜਾਈ - (ਚੌੜਾਈ + 7) / 8;

    ਜੇ (map) {
        ਜੇ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            ਜਦੋਂ (ਉਚਾਈ--) {
                Uint8 byte = 0, ਦੋਆਧਾਰੀ_ਅੰਕ;
                ਲਈ (c = 0; c < info->leading_skip; ++c) {
                    ਜੇ (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                ਲਈ (; c < ਚੌੜਾਈ; ++c) {
                    ਜੇ (!(c & align)) {
                        byte = *src++;
                    }
                    ਦੋਆਧਾਰੀ_ਅੰਕ = (byte & ਨਕਾਬ);
                    ਜੇ (1) {
                        *dst = map[ਦੋਆਧਾਰੀ_ਅੰਕ];
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } ਨਹੀਂਤਾਂ {
            ਜਦੋਂ (ਉਚਾਈ--) {
                Uint8 byte = 0, ਦੋਆਧਾਰੀ_ਅੰਕ;
                ਲਈ (c = 0; c < info->leading_skip; ++c) {
                    ਜੇ (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                ਲਈ (; c < ਚੌੜਾਈ; ++c) {
                    ਜੇ (!(c & align)) {
                        byte = *src++;
                    }
                    ਦੋਆਧਾਰੀ_ਅੰਕ = (byte >> (8 - srcbpp)) & ਨਕਾਬ;
                    ਜੇ (1) {
                        *dst = map[ਦੋਆਧਾਰੀ_ਅੰਕ];
                    }
                    dst++;
                    byte <<= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        }
    } ਨਹੀਂਤਾਂ {
        ਜੇ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            ਜਦੋਂ (ਉਚਾਈ--) {
                Uint8 byte = 0, ਦੋਆਧਾਰੀ_ਅੰਕ;
                ਲਈ (c = 0; c < info->leading_skip; ++c) {
                    ਜੇ (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                ਲਈ (; c < ਚੌੜਾਈ; ++c) {
                    ਜੇ (!(c & align)) {
                        byte = *src++;
                    }
                    ਦੋਆਧਾਰੀ_ਅੰਕ = (byte & ਨਕਾਬ);
                    ਜੇ (1) {
                        *dst = ਦੋਆਧਾਰੀ_ਅੰਕ;
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } ਨਹੀਂਤਾਂ {
            ਜਦੋਂ (ਉਚਾਈ--) {
                Uint8 byte = 0, ਦੋਆਧਾਰੀ_ਅੰਕ;
                ਲਈ (c = 0; c < info->leading_skip; ++c) {
                    ਜੇ (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                ਲਈ (; c < ਚੌੜਾਈ; ++c) {
                    ਜੇ (!(c & align)) {
                        byte = *src++;
                    }
                    ਦੋਆਧਾਰੀ_ਅੰਕ = (byte >> (8 - srcbpp)) & ਨਕਾਬ;
                    ਜੇ (1) {
                        *dst = ਦੋਆਧਾਰੀ_ਅੰਕ;
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

SDL_FORCE_INLINE ਖਾਲੀ BlitBto2(SDL_BlitInfo *info, ਅਚਲ Uint32 srcbpp)
{
    ਅਚਲ Uint32 ਨਕਾਬ = (1 << srcbpp) - 1;
    ਅਚਲ Uint32 align = (8 / srcbpp) - 1;

    ਪੂਰਨ c;
    ਪੂਰਨ ਚੌੜਾਈ, ਉਚਾਈ;
    Uint8 *src;
    Uint16 *map, *dst;
    ਪੂਰਨ srcskip, dstskip;

    // Set up some basic variables
    ਚੌੜਾਈ = info->dst_w;
    ਉਚਾਈ = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = (Uint16 *)info->dst;
    dstskip = info->dst_skip / 2;
    map = (Uint16 *)info->ਸਾਰਣੀ;

    ਚੌੜਾਈ += info->leading_skip;

    ਜੇ (srcbpp == 4)
        srcskip += ਚੌੜਾਈ - (ਚੌੜਾਈ + 1) / 2;
    ਨਹੀਂਤਾਂ ਜੇ (srcbpp == 2)
        srcskip += ਚੌੜਾਈ - (ਚੌੜਾਈ + 3) / 4;
    ਨਹੀਂਤਾਂ ਜੇ (srcbpp == 1)
        srcskip += ਚੌੜਾਈ - (ਚੌੜਾਈ + 7) / 8;

    ਜੇ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        ਜਦੋਂ (ਉਚਾਈ--) {
            Uint8 byte = 0, ਦੋਆਧਾਰੀ_ਅੰਕ;
            ਲਈ (c = 0; c < info->leading_skip; ++c) {
                ਜੇ (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            ਲਈ (; c < ਚੌੜਾਈ; ++c) {
                ਜੇ (!(c & align)) {
                    byte = *src++;
                }
                ਦੋਆਧਾਰੀ_ਅੰਕ = (byte & ਨਕਾਬ);
                ਜੇ (1) {
                    *dst = map[ਦੋਆਧਾਰੀ_ਅੰਕ];
                }
                byte >>= srcbpp;
                dst++;
            }
            src += srcskip;
            dst += dstskip;
        }
    } ਨਹੀਂਤਾਂ {
        ਜਦੋਂ (ਉਚਾਈ--) {
            Uint8 byte = 0, ਦੋਆਧਾਰੀ_ਅੰਕ;
            ਲਈ (c = 0; c < info->leading_skip; ++c) {
                ਜੇ (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            ਲਈ (; c < ਚੌੜਾਈ; ++c) {
                ਜੇ (!(c & align)) {
                    byte = *src++;
                }
                ਦੋਆਧਾਰੀ_ਅੰਕ = (byte >> (8 - srcbpp)) & ਨਕਾਬ;
                ਜੇ (1) {
                    *dst = map[ਦੋਆਧਾਰੀ_ਅੰਕ];
                }
                byte <<= srcbpp;
                dst++;
            }
            src += srcskip;
            dst += dstskip;
        }
    }
}

SDL_FORCE_INLINE ਖਾਲੀ BlitBto3(SDL_BlitInfo *info, ਅਚਲ Uint32 srcbpp)
{
    ਅਚਲ Uint32 ਨਕਾਬ = (1 << srcbpp) - 1;
    ਅਚਲ Uint32 align = (8 / srcbpp) - 1;

    ਪੂਰਨ c, o;
    ਪੂਰਨ ਚੌੜਾਈ, ਉਚਾਈ;
    Uint8 *src, *map, *dst;
    ਪੂਰਨ srcskip, dstskip;

    // Set up some basic variables
    ਚੌੜਾਈ = info->dst_w;
    ਉਚਾਈ = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = info->ਸਾਰਣੀ;

    ਚੌੜਾਈ += info->leading_skip;

    ਜੇ (srcbpp == 4)
        srcskip += ਚੌੜਾਈ - (ਚੌੜਾਈ + 1) / 2;
    ਨਹੀਂਤਾਂ ਜੇ (srcbpp == 2)
        srcskip += ਚੌੜਾਈ - (ਚੌੜਾਈ + 3) / 4;
    ਨਹੀਂਤਾਂ ਜੇ (srcbpp == 1)
        srcskip += ਚੌੜਾਈ - (ਚੌੜਾਈ + 7) / 8;

    ਜੇ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        ਜਦੋਂ (ਉਚਾਈ--) {
            Uint8 byte = 0, ਦੋਆਧਾਰੀ_ਅੰਕ;
            ਲਈ (c = 0; c < info->leading_skip; ++c) {
                ਜੇ (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            ਲਈ (; c < ਚੌੜਾਈ; ++c) {
                ਜੇ (!(c & align)) {
                    byte = *src++;
                }
                ਦੋਆਧਾਰੀ_ਅੰਕ = (byte & ਨਕਾਬ);
                ਜੇ (1) {
                    o = ਦੋਆਧਾਰੀ_ਅੰਕ * 4;
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
    } ਨਹੀਂਤਾਂ {
        ਜਦੋਂ (ਉਚਾਈ--) {
            Uint8 byte = 0, ਦੋਆਧਾਰੀ_ਅੰਕ;
            ਲਈ (c = 0; c < info->leading_skip; ++c) {
                ਜੇ (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            ਲਈ (; c < ਚੌੜਾਈ; ++c) {
                ਜੇ (!(c & align)) {
                    byte = *src++;
                }
                ਦੋਆਧਾਰੀ_ਅੰਕ = (byte >> (8 - srcbpp)) & ਨਕਾਬ;
                ਜੇ (1) {
                    o = ਦੋਆਧਾਰੀ_ਅੰਕ * 4;
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

SDL_FORCE_INLINE ਖਾਲੀ BlitBto4(SDL_BlitInfo *info, ਅਚਲ Uint32 srcbpp)
{
    ਅਚਲ Uint32 ਨਕਾਬ = (1 << srcbpp) - 1;
    ਅਚਲ Uint32 align = (8 / srcbpp) - 1;

    ਪੂਰਨ ਚੌੜਾਈ, ਉਚਾਈ;
    Uint8 *src;
    Uint32 *map, *dst;
    ਪੂਰਨ srcskip, dstskip;
    ਪੂਰਨ c;

    // Set up some basic variables
    ਚੌੜਾਈ = info->dst_w;
    ਉਚਾਈ = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = (Uint32 *)info->dst;
    dstskip = info->dst_skip / 4;
    map = (Uint32 *)info->ਸਾਰਣੀ;

    ਚੌੜਾਈ += info->leading_skip;

    ਜੇ (srcbpp == 4)
        srcskip += ਚੌੜਾਈ - (ਚੌੜਾਈ + 1) / 2;
    ਨਹੀਂਤਾਂ ਜੇ (srcbpp == 2)
        srcskip += ਚੌੜਾਈ - (ਚੌੜਾਈ + 3) / 4;
    ਨਹੀਂਤਾਂ ਜੇ (srcbpp == 1)
        srcskip += ਚੌੜਾਈ - (ਚੌੜਾਈ + 7) / 8;

    ਜੇ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        ਜਦੋਂ (ਉਚਾਈ--) {
            Uint8 byte = 0, ਦੋਆਧਾਰੀ_ਅੰਕ;
            ਲਈ (c = 0; c < info->leading_skip; ++c) {
                ਜੇ (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            ਲਈ (; c < ਚੌੜਾਈ; ++c) {
                ਜੇ (!(c & align)) {
                    byte = *src++;
                }
                ਦੋਆਧਾਰੀ_ਅੰਕ = (byte & ਨਕਾਬ);
                ਜੇ (1) {
                    *dst = map[ਦੋਆਧਾਰੀ_ਅੰਕ];
                }
                byte >>= srcbpp;
                dst++;
            }
            src += srcskip;
            dst += dstskip;
        }
    } ਨਹੀਂਤਾਂ {
        ਜਦੋਂ (ਉਚਾਈ--) {
            Uint8 byte = 0, ਦੋਆਧਾਰੀ_ਅੰਕ;
            ਲਈ (c = 0; c < info->leading_skip; ++c) {
                ਜੇ (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            ਲਈ (; c < ਚੌੜਾਈ; ++c) {
                ਜੇ (!(c & align)) {
                    byte = *src++;
                }
                ਦੋਆਧਾਰੀ_ਅੰਕ = (byte >> (8 - srcbpp)) & ਨਕਾਬ;
                ਜੇ (1) {
                    *dst = map[ਦੋਆਧਾਰੀ_ਅੰਕ];
                }
                byte <<= srcbpp;
                dst++;
            }
            src += srcskip;
            dst += dstskip;
        }
    }
}

SDL_FORCE_INLINE ਖਾਲੀ Blit_Bto1_ਕੁੰਜੀ(SDL_BlitInfo *info, ਅਚਲ Uint32 srcbpp)
{
    ਅਚਲ Uint32 ਨਕਾਬ = (1 << srcbpp) - 1;
    ਅਚਲ Uint32 align = (8 / srcbpp) - 1;

    ਪੂਰਨ ਚੌੜਾਈ = info->dst_w;
    ਪੂਰਨ ਉਚਾਈ = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    ਪੂਰਨ srcskip = info->src_skip;
    ਪੂਰਨ dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->ਸਾਰਣੀ;
    ਪੂਰਨ c;

    ਚੌੜਾਈ += info->leading_skip;

    ਜੇ (srcbpp == 4)
        srcskip += ਚੌੜਾਈ - (ਚੌੜਾਈ + 1) / 2;
    ਨਹੀਂਤਾਂ ਜੇ (srcbpp == 2)
        srcskip += ਚੌੜਾਈ - (ਚੌੜਾਈ + 3) / 4;
    ਨਹੀਂਤਾਂ ਜੇ (srcbpp == 1)
        srcskip += ਚੌੜਾਈ - (ਚੌੜਾਈ + 7) / 8;

    ਜੇ (palmap) {
        ਜੇ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            ਜਦੋਂ (ਉਚਾਈ--) {
                Uint8 byte = 0, ਦੋਆਧਾਰੀ_ਅੰਕ;
                ਲਈ (c = 0; c < info->leading_skip; ++c) {
                    ਜੇ (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                ਲਈ (; c < ਚੌੜਾਈ; ++c) {
                    ਜੇ (!(c & align)) {
                        byte = *src++;
                    }
                    ਦੋਆਧਾਰੀ_ਅੰਕ = (byte & ਨਕਾਬ);
                    ਜੇ (ਦੋਆਧਾਰੀ_ਅੰਕ != ckey) {
                        *dst = palmap[ਦੋਆਧਾਰੀ_ਅੰਕ];
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } ਨਹੀਂਤਾਂ {
            ਜਦੋਂ (ਉਚਾਈ--) {
                Uint8 byte = 0, ਦੋਆਧਾਰੀ_ਅੰਕ;
                ਲਈ (c = 0; c < info->leading_skip; ++c) {
                    ਜੇ (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                ਲਈ (; c < ਚੌੜਾਈ; ++c) {
                    ਜੇ (!(c & align)) {
                        byte = *src++;
                    }
                    ਦੋਆਧਾਰੀ_ਅੰਕ = (byte >> (8 - srcbpp)) & ਨਕਾਬ;
                    ਜੇ (ਦੋਆਧਾਰੀ_ਅੰਕ != ckey) {
                        *dst = palmap[ਦੋਆਧਾਰੀ_ਅੰਕ];
                    }
                    dst++;
                    byte <<= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        }
    } ਨਹੀਂਤਾਂ {
        ਜੇ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            ਜਦੋਂ (ਉਚਾਈ--) {
                Uint8 byte = 0, ਦੋਆਧਾਰੀ_ਅੰਕ;
                ਲਈ (c = 0; c < info->leading_skip; ++c) {
                    ਜੇ (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                ਲਈ (; c < ਚੌੜਾਈ; ++c) {
                    ਜੇ (!(c & align)) {
                        byte = *src++;
                    }
                    ਦੋਆਧਾਰੀ_ਅੰਕ = (byte & ਨਕਾਬ);
                    ਜੇ (ਦੋਆਧਾਰੀ_ਅੰਕ != ckey) {
                        *dst = ਦੋਆਧਾਰੀ_ਅੰਕ;
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } ਨਹੀਂਤਾਂ {
            ਜਦੋਂ (ਉਚਾਈ--) {
                Uint8 byte = 0, ਦੋਆਧਾਰੀ_ਅੰਕ;
                ਲਈ (c = 0; c < info->leading_skip; ++c) {
                    ਜੇ (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                ਲਈ (; c < ਚੌੜਾਈ; ++c) {
                    ਜੇ (!(c & align)) {
                        byte = *src++;
                    }
                    ਦੋਆਧਾਰੀ_ਅੰਕ = (byte >> (8 - srcbpp)) & ਨਕਾਬ;
                    ਜੇ (ਦੋਆਧਾਰੀ_ਅੰਕ != ckey) {
                        *dst = ਦੋਆਧਾਰੀ_ਅੰਕ;
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

SDL_FORCE_INLINE ਖਾਲੀ Blit_Bto2_ਕੁੰਜੀ(SDL_BlitInfo *info, ਅਚਲ Uint32 srcbpp)
{
    ਅਚਲ Uint32 ਨਕਾਬ = (1 << srcbpp) - 1;
    ਅਚਲ Uint32 align = (8 / srcbpp) - 1;

    ਪੂਰਨ ਚੌੜਾਈ = info->dst_w;
    ਪੂਰਨ ਉਚਾਈ = info->dst_h;
    Uint8 *src = info->src;
    Uint16 *dstp = (Uint16 *)info->dst;
    ਪੂਰਨ srcskip = info->src_skip;
    ਪੂਰਨ dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->ਸਾਰਣੀ;
    ਪੂਰਨ c;

    ਚੌੜਾਈ += info->leading_skip;

    ਜੇ (srcbpp == 4)
        srcskip += ਚੌੜਾਈ - (ਚੌੜਾਈ + 1) / 2;
    ਨਹੀਂਤਾਂ ਜੇ (srcbpp == 2)
        srcskip += ਚੌੜਾਈ - (ਚੌੜਾਈ + 3) / 4;
    ਨਹੀਂਤਾਂ ਜੇ (srcbpp == 1)
        srcskip += ਚੌੜਾਈ - (ਚੌੜਾਈ + 7) / 8;
    dstskip /= 2;

    ਜੇ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        ਜਦੋਂ (ਉਚਾਈ--) {
            Uint8 byte = 0, ਦੋਆਧਾਰੀ_ਅੰਕ;
            ਲਈ (c = 0; c < info->leading_skip; ++c) {
                ਜੇ (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            ਲਈ (; c < ਚੌੜਾਈ; ++c) {
                ਜੇ (!(c & align)) {
                    byte = *src++;
                }
                ਦੋਆਧਾਰੀ_ਅੰਕ = (byte & ਨਕਾਬ);
                ਜੇ (ਦੋਆਧਾਰੀ_ਅੰਕ != ckey) {
                    *dstp = ((Uint16 *)palmap)[ਦੋਆਧਾਰੀ_ਅੰਕ];
                }
                byte >>= srcbpp;
                dstp++;
            }
            src += srcskip;
            dstp += dstskip;
        }
    } ਨਹੀਂਤਾਂ {
        ਜਦੋਂ (ਉਚਾਈ--) {
            Uint8 byte = 0, ਦੋਆਧਾਰੀ_ਅੰਕ;
            ਲਈ (c = 0; c < info->leading_skip; ++c) {
                ਜੇ (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            ਲਈ (; c < ਚੌੜਾਈ; ++c) {
                ਜੇ (!(c & align)) {
                    byte = *src++;
                }
                ਦੋਆਧਾਰੀ_ਅੰਕ = (byte >> (8 - srcbpp)) & ਨਕਾਬ;
                ਜੇ (ਦੋਆਧਾਰੀ_ਅੰਕ != ckey) {
                    *dstp = ((Uint16 *)palmap)[ਦੋਆਧਾਰੀ_ਅੰਕ];
                }
                byte <<= srcbpp;
                dstp++;
            }
            src += srcskip;
            dstp += dstskip;
        }
    }
}

SDL_FORCE_INLINE ਖਾਲੀ Blit_Bto3_ਕੁੰਜੀ(SDL_BlitInfo *info, ਅਚਲ Uint32 srcbpp)
{
    ਅਚਲ Uint32 ਨਕਾਬ = (1 << srcbpp) - 1;
    ਅਚਲ Uint32 align = (8 / srcbpp) - 1;

    ਪੂਰਨ ਚੌੜਾਈ = info->dst_w;
    ਪੂਰਨ ਉਚਾਈ = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    ਪੂਰਨ srcskip = info->src_skip;
    ਪੂਰਨ dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->ਸਾਰਣੀ;
    ਪੂਰਨ c;

    ਚੌੜਾਈ += info->leading_skip;

    ਜੇ (srcbpp == 4)
        srcskip += ਚੌੜਾਈ - (ਚੌੜਾਈ + 1) / 2;
    ਨਹੀਂਤਾਂ ਜੇ (srcbpp == 2)
        srcskip += ਚੌੜਾਈ - (ਚੌੜਾਈ + 3) / 4;
    ਨਹੀਂਤਾਂ ਜੇ (srcbpp == 1)
        srcskip += ਚੌੜਾਈ - (ਚੌੜਾਈ + 7) / 8;

    ਜੇ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        ਜਦੋਂ (ਉਚਾਈ--) {
            Uint8 byte = 0, ਦੋਆਧਾਰੀ_ਅੰਕ;
            ਲਈ (c = 0; c < info->leading_skip; ++c) {
                ਜੇ (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            ਲਈ (; c < ਚੌੜਾਈ; ++c) {
                ਜੇ (!(c & align)) {
                    byte = *src++;
                }
                ਦੋਆਧਾਰੀ_ਅੰਕ = (byte & ਨਕਾਬ);
                ਜੇ (ਦੋਆਧਾਰੀ_ਅੰਕ != ckey) {
                    SDL_memcpy(dst, &palmap[ਦੋਆਧਾਰੀ_ਅੰਕ * 4], 3);
                }
                byte >>= srcbpp;
                dst += 3;
            }
            src += srcskip;
            dst += dstskip;
        }
    } ਨਹੀਂਤਾਂ {
        ਜਦੋਂ (ਉਚਾਈ--) {
            Uint8 byte = 0, ਦੋਆਧਾਰੀ_ਅੰਕ;
            ਲਈ (c = 0; c < info->leading_skip; ++c) {
                ਜੇ (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            ਲਈ (; c < ਚੌੜਾਈ; ++c) {
                ਜੇ (!(c & align)) {
                    byte = *src++;
                }
                ਦੋਆਧਾਰੀ_ਅੰਕ = (byte >> (8 - srcbpp)) & ਨਕਾਬ;
                ਜੇ (ਦੋਆਧਾਰੀ_ਅੰਕ != ckey) {
                    SDL_memcpy(dst, &palmap[ਦੋਆਧਾਰੀ_ਅੰਕ * 4], 3);
                }
                byte <<= srcbpp;
                dst += 3;
            }
            src += srcskip;
            dst += dstskip;
        }
    }
}

SDL_FORCE_INLINE ਖਾਲੀ Blit_Bto4_ਕੁੰਜੀ(SDL_BlitInfo *info, ਅਚਲ Uint32 srcbpp)
{
    ਅਚਲ Uint32 ਨਕਾਬ = (1 << srcbpp) - 1;
    ਅਚਲ Uint32 align = (8 / srcbpp) - 1;

    ਪੂਰਨ ਚੌੜਾਈ = info->dst_w;
    ਪੂਰਨ ਉਚਾਈ = info->dst_h;
    Uint8 *src = info->src;
    Uint32 *dstp = (Uint32 *)info->dst;
    ਪੂਰਨ srcskip = info->src_skip;
    ਪੂਰਨ dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->ਸਾਰਣੀ;
    ਪੂਰਨ c;

    ਚੌੜਾਈ += info->leading_skip;

    ਜੇ (srcbpp == 4)
        srcskip += ਚੌੜਾਈ - (ਚੌੜਾਈ + 1) / 2;
    ਨਹੀਂਤਾਂ ਜੇ (srcbpp == 2)
        srcskip += ਚੌੜਾਈ - (ਚੌੜਾਈ + 3) / 4;
    ਨਹੀਂਤਾਂ ਜੇ (srcbpp == 1)
        srcskip += ਚੌੜਾਈ - (ਚੌੜਾਈ + 7) / 8;
    dstskip /= 4;

    ਜੇ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        ਜਦੋਂ (ਉਚਾਈ--) {
            Uint8 byte = 0, ਦੋਆਧਾਰੀ_ਅੰਕ;
            ਲਈ (c = 0; c < info->leading_skip; ++c) {
                ਜੇ (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            ਲਈ (; c < ਚੌੜਾਈ; ++c) {
                ਜੇ (!(c & align)) {
                    byte = *src++;
                }
                ਦੋਆਧਾਰੀ_ਅੰਕ = (byte & ਨਕਾਬ);
                ਜੇ (ਦੋਆਧਾਰੀ_ਅੰਕ != ckey) {
                    *dstp = ((Uint32 *)palmap)[ਦੋਆਧਾਰੀ_ਅੰਕ];
                }
                byte >>= srcbpp;
                dstp++;
            }
            src += srcskip;
            dstp += dstskip;
        }
    } ਨਹੀਂਤਾਂ {
        ਜਦੋਂ (ਉਚਾਈ--) {
            Uint8 byte = 0, ਦੋਆਧਾਰੀ_ਅੰਕ;
            ਲਈ (c = 0; c < info->leading_skip; ++c) {
                ਜੇ (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            ਲਈ (; c < ਚੌੜਾਈ; ++c) {
                ਜੇ (!(c & align)) {
                    byte = *src++;
                }
                ਦੋਆਧਾਰੀ_ਅੰਕ = (byte >> (8 - srcbpp)) & ਨਕਾਬ;
                ਜੇ (ਦੋਆਧਾਰੀ_ਅੰਕ != ckey) {
                    *dstp = ((Uint32 *)palmap)[ਦੋਆਧਾਰੀ_ਅੰਕ];
                }
                byte <<= srcbpp;
                dstp++;
            }
            src += srcskip;
            dstp += dstskip;
        }
    }
}

ਸਥਿਰ ਖਾਲੀ BlitBtoNAlpha(SDL_BlitInfo *info)
{
    ਪੂਰਨ ਚੌੜਾਈ = info->dst_w;
    ਪੂਰਨ ਉਚਾਈ = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    ਪੂਰਨ srcskip = info->src_skip;
    ਪੂਰਨ dstskip = info->dst_skip;
    ਅਚਲ SDL_Color *srcpal = info->src_pal->colors;
    ਅਚਲ SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    ਅਚਲ SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    ਪੂਰਨ srcbpp, dstbpp;
    ਪੂਰਨ c;
    Uint32 pixelvalue, ਨਕਾਬ, align;
    ਬਿਨਾਨਿਸ਼ਾਨੀ sR, sG, sB;
    ਬਿਨਾਨਿਸ਼ਾਨੀ dR, dG, dB, dA;
    ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ A = info->a;

    ਚੌੜਾਈ += info->leading_skip;

    srcbpp = srcfmt->ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel;
    dstbpp = dstfmt->ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel;
    ਜੇ (srcbpp == 4)
        srcskip += ਚੌੜਾਈ - (ਚੌੜਾਈ + 1) / 2;
    ਨਹੀਂਤਾਂ ਜੇ (srcbpp == 2)
        srcskip += ਚੌੜਾਈ - (ਚੌੜਾਈ + 3) / 4;
    ਨਹੀਂਤਾਂ ਜੇ (srcbpp == 1)
        srcskip += ਚੌੜਾਈ - (ਚੌੜਾਈ + 7) / 8;
    ਨਕਾਬ = (1 << srcbpp) - 1;
    align = (8 / srcbpp) - 1;

    ਜੇ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        ਜਦੋਂ (ਉਚਾਈ--) {
            Uint8 byte = 0, ਦੋਆਧਾਰੀ_ਅੰਕ;
            ਲਈ (c = 0; c < info->leading_skip; ++c) {
                ਜੇ (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            ਲਈ (; c < ਚੌੜਾਈ; ++c) {
                ਜੇ (!(c & align)) {
                    byte = *src++;
                }
                ਦੋਆਧਾਰੀ_ਅੰਕ = (byte & ਨਕਾਬ);
                ਜੇ (1) {
                    sR = srcpal[ਦੋਆਧਾਰੀ_ਅੰਕ].r;
                    sG = srcpal[ਦੋਆਧਾਰੀ_ਅੰਕ].g;
                    sB = srcpal[ਦੋਆਧਾਰੀ_ਅੰਕ].b;
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
    } ਨਹੀਂਤਾਂ {
        ਜਦੋਂ (ਉਚਾਈ--) {
            Uint8 byte = 0, ਦੋਆਧਾਰੀ_ਅੰਕ;
            ਲਈ (c = 0; c < info->leading_skip; ++c) {
                ਜੇ (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            ਲਈ (; c < ਚੌੜਾਈ; ++c) {
                ਜੇ (!(c & align)) {
                    byte = *src++;
                }
                ਦੋਆਧਾਰੀ_ਅੰਕ = (byte >> (8 - srcbpp)) & ਨਕਾਬ;
                ਜੇ (1) {
                    sR = srcpal[ਦੋਆਧਾਰੀ_ਅੰਕ].r;
                    sG = srcpal[ਦੋਆਧਾਰੀ_ਅੰਕ].g;
                    sB = srcpal[ਦੋਆਧਾਰੀ_ਅੰਕ].b;
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

ਸਥਿਰ ਖਾਲੀ Blit_Bto_NAlpha_ਕੁੰਜੀ(SDL_BlitInfo *info)
{
    ਪੂਰਨ ਚੌੜਾਈ = info->dst_w;
    ਪੂਰਨ ਉਚਾਈ = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    ਪੂਰਨ srcskip = info->src_skip;
    ਪੂਰਨ dstskip = info->dst_skip;
    ਅਚਲ SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    ਅਚਲ SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    ਅਚਲ SDL_Color *srcpal = info->src_pal->colors;
    ਪੂਰਨ srcbpp, dstbpp;
    ਪੂਰਨ c;
    Uint32 pixelvalue, ਨਕਾਬ, align;
    ਬਿਨਾਨਿਸ਼ਾਨੀ sR, sG, sB;
    ਬਿਨਾਨਿਸ਼ਾਨੀ dR, dG, dB, dA;
    ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ A = info->a;
    Uint32 ckey = info->colorkey;

    ਚੌੜਾਈ += info->leading_skip;

    srcbpp = srcfmt->ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel;
    dstbpp = dstfmt->ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel;
    ਜੇ (srcbpp == 4)
        srcskip += ਚੌੜਾਈ - (ਚੌੜਾਈ + 1) / 2;
    ਨਹੀਂਤਾਂ ਜੇ (srcbpp == 2)
        srcskip += ਚੌੜਾਈ - (ਚੌੜਾਈ + 3) / 4;
    ਨਹੀਂਤਾਂ ਜੇ (srcbpp == 1)
        srcskip += ਚੌੜਾਈ - (ਚੌੜਾਈ + 7) / 8;
    ਨਕਾਬ = (1 << srcbpp) - 1;
    align = (8 / srcbpp) - 1;

    ਜੇ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        ਜਦੋਂ (ਉਚਾਈ--) {
            Uint8 byte = 0, ਦੋਆਧਾਰੀ_ਅੰਕ;
            ਲਈ (c = 0; c < info->leading_skip; ++c) {
                ਜੇ (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            ਲਈ (; c < ਚੌੜਾਈ; ++c) {
                ਜੇ (!(c & align)) {
                    byte = *src++;
                }
                ਦੋਆਧਾਰੀ_ਅੰਕ = (byte & ਨਕਾਬ);
                ਜੇ (ਦੋਆਧਾਰੀ_ਅੰਕ != ckey) {
                    sR = srcpal[ਦੋਆਧਾਰੀ_ਅੰਕ].r;
                    sG = srcpal[ਦੋਆਧਾਰੀ_ਅੰਕ].g;
                    sB = srcpal[ਦੋਆਧਾਰੀ_ਅੰਕ].b;
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
    } ਨਹੀਂਤਾਂ {
        ਜਦੋਂ (ਉਚਾਈ--) {
            Uint8 byte = 0, ਦੋਆਧਾਰੀ_ਅੰਕ;
            ਲਈ (c = 0; c < info->leading_skip; ++c) {
                ਜੇ (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            ਲਈ (; c < ਚੌੜਾਈ; ++c) {
                ਜੇ (!(c & align)) {
                    byte = *src++;
                }
                ਦੋਆਧਾਰੀ_ਅੰਕ = (byte >> (8 - srcbpp)) & ਨਕਾਬ;
                ਜੇ (ਦੋਆਧਾਰੀ_ਅੰਕ != ckey) {
                    sR = srcpal[ਦੋਆਧਾਰੀ_ਅੰਕ].r;
                    sG = srcpal[ਦੋਆਧਾਰੀ_ਅੰਕ].g;
                    sB = srcpal[ਦੋਆਧਾਰੀ_ਅੰਕ].b;
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



ਸਥਿਰ ਖਾਲੀ Blit1bto1(SDL_BlitInfo *info) {
    BlitBto1(info, 1);
}

ਸਥਿਰ ਖਾਲੀ Blit1bto2(SDL_BlitInfo *info) {
    BlitBto2(info, 1);
}

ਸਥਿਰ ਖਾਲੀ Blit1bto3(SDL_BlitInfo *info) {
    BlitBto3(info, 1);
}

ਸਥਿਰ ਖਾਲੀ Blit1bto4(SDL_BlitInfo *info) {
    BlitBto4(info, 1);
}

ਸਥਿਰ ਅਚਲ SDL_BlitFunc bitmap_blit_1b[] = {
    (SDL_BlitFunc)ਨਿਰਾ, Blit1bto1, Blit1bto2, Blit1bto3, Blit1bto4
};

ਸਥਿਰ ਖਾਲੀ Blit1bto1_ਕੁੰਜੀ(SDL_BlitInfo *info) {
    Blit_Bto1_ਕੁੰਜੀ(info, 1);
}

ਸਥਿਰ ਖਾਲੀ Blit1bto2_ਕੁੰਜੀ(SDL_BlitInfo *info) {
    Blit_Bto2_ਕੁੰਜੀ(info, 1);
}

ਸਥਿਰ ਖਾਲੀ Blit1bto3_ਕੁੰਜੀ(SDL_BlitInfo *info) {
    Blit_Bto3_ਕੁੰਜੀ(info, 1);
}

ਸਥਿਰ ਖਾਲੀ Blit1bto4_ਕੁੰਜੀ(SDL_BlitInfo *info) {
    Blit_Bto4_ਕੁੰਜੀ(info, 1);
}

ਸਥਿਰ ਅਚਲ SDL_BlitFunc colorkey_blit_1b[] = {
    (SDL_BlitFunc)ਨਿਰਾ, Blit1bto1_ਕੁੰਜੀ, Blit1bto2_ਕੁੰਜੀ, Blit1bto3_ਕੁੰਜੀ, Blit1bto4_ਕੁੰਜੀ
};



ਸਥਿਰ ਖਾਲੀ Blit2bto1(SDL_BlitInfo *info) {
    BlitBto1(info, 2);
}

ਸਥਿਰ ਖਾਲੀ Blit2bto2(SDL_BlitInfo *info) {
    BlitBto2(info, 2);
}

ਸਥਿਰ ਖਾਲੀ Blit2bto3(SDL_BlitInfo *info) {
    BlitBto3(info, 2);
}

ਸਥਿਰ ਖਾਲੀ Blit2bto4(SDL_BlitInfo *info) {
    BlitBto4(info, 2);
}

ਸਥਿਰ ਅਚਲ SDL_BlitFunc bitmap_blit_2b[] = {
    (SDL_BlitFunc)ਨਿਰਾ, Blit2bto1, Blit2bto2, Blit2bto3, Blit2bto4
};

ਸਥਿਰ ਖਾਲੀ Blit2bto1_ਕੁੰਜੀ(SDL_BlitInfo *info) {
    Blit_Bto1_ਕੁੰਜੀ(info, 2);
}

ਸਥਿਰ ਖਾਲੀ Blit2bto2_ਕੁੰਜੀ(SDL_BlitInfo *info) {
    Blit_Bto2_ਕੁੰਜੀ(info, 2);
}

ਸਥਿਰ ਖਾਲੀ Blit2bto3_ਕੁੰਜੀ(SDL_BlitInfo *info) {
    Blit_Bto3_ਕੁੰਜੀ(info, 2);
}

ਸਥਿਰ ਖਾਲੀ Blit2bto4_ਕੁੰਜੀ(SDL_BlitInfo *info) {
    Blit_Bto4_ਕੁੰਜੀ(info, 2);
}

ਸਥਿਰ ਅਚਲ SDL_BlitFunc colorkey_blit_2b[] = {
    (SDL_BlitFunc)ਨਿਰਾ, Blit2bto1_ਕੁੰਜੀ, Blit2bto2_ਕੁੰਜੀ, Blit2bto3_ਕੁੰਜੀ, Blit2bto4_ਕੁੰਜੀ
};



ਸਥਿਰ ਖਾਲੀ Blit4bto1(SDL_BlitInfo *info) {
    BlitBto1(info, 4);
}

ਸਥਿਰ ਖਾਲੀ Blit4bto2(SDL_BlitInfo *info) {
    BlitBto2(info, 4);
}

ਸਥਿਰ ਖਾਲੀ Blit4bto3(SDL_BlitInfo *info) {
    BlitBto3(info, 4);
}

ਸਥਿਰ ਖਾਲੀ Blit4bto4(SDL_BlitInfo *info) {
    BlitBto4(info, 4);
}

ਸਥਿਰ ਅਚਲ SDL_BlitFunc bitmap_blit_4b[] = {
    (SDL_BlitFunc)ਨਿਰਾ, Blit4bto1, Blit4bto2, Blit4bto3, Blit4bto4
};

ਸਥਿਰ ਖਾਲੀ Blit4bto1_ਕੁੰਜੀ(SDL_BlitInfo *info) {
    Blit_Bto1_ਕੁੰਜੀ(info, 4);
}

ਸਥਿਰ ਖਾਲੀ Blit4bto2_ਕੁੰਜੀ(SDL_BlitInfo *info) {
    Blit_Bto2_ਕੁੰਜੀ(info, 4);
}

ਸਥਿਰ ਖਾਲੀ Blit4bto3_ਕੁੰਜੀ(SDL_BlitInfo *info) {
    Blit_Bto3_ਕੁੰਜੀ(info, 4);
}

ਸਥਿਰ ਖਾਲੀ Blit4bto4_ਕੁੰਜੀ(SDL_BlitInfo *info) {
    Blit_Bto4_ਕੁੰਜੀ(info, 4);
}

ਸਥਿਰ ਅਚਲ SDL_BlitFunc colorkey_blit_4b[] = {
    (SDL_BlitFunc)ਨਿਰਾ, Blit4bto1_ਕੁੰਜੀ, Blit4bto2_ਕੁੰਜੀ, Blit4bto3_ਕੁੰਜੀ, Blit4bto4_ਕੁੰਜੀ
};



SDL_BlitFunc SDL_CalculateBlit0(SDL_Surface *surface)
{
    ਪੂਰਨ which;

    ਜੇ (SDL_BITSPERPIXEL(surface->map.info.dst_fmt->format) < 8) {
        which = 0;
    } ਨਹੀਂਤਾਂ {
        which = SDL_BYTESPERPIXEL(surface->map.info.dst_fmt->format);
    }

    ਜੇ (SDL_PIXELTYPE(surface->format) == SDL_PIXELTYPE_INDEX1) {
        ਚੋਣ (surface->map.info.flags & ~SDL_COPY_RLE_ਨਕਾਬ) {
        ਹਾਲਤ 0:
            ਜੇ (which < SDL_arraysize(bitmap_blit_1b)) {
                ਵਾਪਸ bitmap_blit_1b[which];
            }
            ਰੋਕੋ;

        ਹਾਲਤ SDL_COPY_COLORKEY:
            ਜੇ (which < SDL_arraysize(colorkey_blit_1b)) {
                ਵਾਪਸ colorkey_blit_1b[which];
            }
            ਰੋਕੋ;

        ਹਾਲਤ SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            ਵਾਪਸ which >= 2 ? BlitBtoNAlpha : (SDL_BlitFunc)ਨਿਰਾ;

        ਹਾਲਤ SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            ਵਾਪਸ which >= 2 ? Blit_Bto_NAlpha_ਕੁੰਜੀ : (SDL_BlitFunc)ਨਿਰਾ;
        }
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਜੇ (SDL_PIXELTYPE(surface->format) == SDL_PIXELTYPE_INDEX2) {
        ਚੋਣ (surface->map.info.flags & ~SDL_COPY_RLE_ਨਕਾਬ) {
        ਹਾਲਤ 0:
            ਜੇ (which < SDL_arraysize(bitmap_blit_2b)) {
                ਵਾਪਸ bitmap_blit_2b[which];
            }
            ਰੋਕੋ;

        ਹਾਲਤ SDL_COPY_COLORKEY:
            ਜੇ (which < SDL_arraysize(colorkey_blit_2b)) {
                ਵਾਪਸ colorkey_blit_2b[which];
            }
            ਰੋਕੋ;

        ਹਾਲਤ SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            ਵਾਪਸ which >= 2 ? BlitBtoNAlpha : (SDL_BlitFunc)ਨਿਰਾ;

        ਹਾਲਤ SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            ਵਾਪਸ which >= 2 ? Blit_Bto_NAlpha_ਕੁੰਜੀ : (SDL_BlitFunc)ਨਿਰਾ;
        }
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਜੇ (SDL_PIXELTYPE(surface->format) == SDL_PIXELTYPE_INDEX4) {
        ਚੋਣ (surface->map.info.flags & ~SDL_COPY_RLE_ਨਕਾਬ) {
        ਹਾਲਤ 0:
            ਜੇ (which < SDL_arraysize(bitmap_blit_4b)) {
                ਵਾਪਸ bitmap_blit_4b[which];
            }
            ਰੋਕੋ;

        ਹਾਲਤ SDL_COPY_COLORKEY:
            ਜੇ (which < SDL_arraysize(colorkey_blit_4b)) {
                ਵਾਪਸ colorkey_blit_4b[which];
            }
            ਰੋਕੋ;

        ਹਾਲਤ SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            ਵਾਪਸ which >= 2 ? BlitBtoNAlpha : (SDL_BlitFunc)ਨਿਰਾ;

        ਹਾਲਤ SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            ਵਾਪਸ which >= 2 ? Blit_Bto_NAlpha_ਕੁੰਜੀ : (SDL_BlitFunc)ਨਿਰਾ;
        }
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਵਾਪਸ ਨਿਰਾ;
}

#ਜੇ_ਅੰਤ // SDL_HAVE_BLIT_0
