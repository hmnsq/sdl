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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_HAVE_BLIT_0

#అన్తర్భావ "SDL_surface_c.h"

// Functions to blit from bitmaps to other surfaces

SDL_FORCE_INLINE శూన్య BlitBto1(SDL_BlitInfo *info, స్థిరరాశి Uint32 srcbpp)
{
    స్థిరరాశి Uint32 ముసుగు = (1 << srcbpp) - 1;
    స్థిరరాశి Uint32 align = (8 / srcbpp) - 1;

    పూర్ణాంకం c;
    పూర్ణాంకం వెడల్పు, ఎత్తు;
    Uint8 *src, *map, *dst;
    పూర్ణాంకం srcskip, dstskip;

    // Set up some basic variables
    వెడల్పు = info->dst_w;
    ఎత్తు = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = info->పట్టిక;

    వెడల్పు += info->leading_skip;

    ఒకవేళ (srcbpp == 4)
        srcskip += వెడల్పు - (వెడల్పు + 1) / 2;
    లేకపోతే ఒకవేళ (srcbpp == 2)
        srcskip += వెడల్పు - (వెడల్పు + 3) / 4;
    లేకపోతే ఒకవేళ (srcbpp == 1)
        srcskip += వెడల్పు - (వెడల్పు + 7) / 8;

    ఒకవేళ (map) {
        ఒకవేళ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            అయితే (ఎత్తు--) {
                Uint8 byte = 0, బిట్టు;
                కొరకు (c = 0; c < info->leading_skip; ++c) {
                    ఒకవేళ (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                కొరకు (; c < వెడల్పు; ++c) {
                    ఒకవేళ (!(c & align)) {
                        byte = *src++;
                    }
                    బిట్టు = (byte & ముసుగు);
                    ఒకవేళ (1) {
                        *dst = map[బిట్టు];
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } లేకపోతే {
            అయితే (ఎత్తు--) {
                Uint8 byte = 0, బిట్టు;
                కొరకు (c = 0; c < info->leading_skip; ++c) {
                    ఒకవేళ (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                కొరకు (; c < వెడల్పు; ++c) {
                    ఒకవేళ (!(c & align)) {
                        byte = *src++;
                    }
                    బిట్టు = (byte >> (8 - srcbpp)) & ముసుగు;
                    ఒకవేళ (1) {
                        *dst = map[బిట్టు];
                    }
                    dst++;
                    byte <<= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        }
    } లేకపోతే {
        ఒకవేళ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            అయితే (ఎత్తు--) {
                Uint8 byte = 0, బిట్టు;
                కొరకు (c = 0; c < info->leading_skip; ++c) {
                    ఒకవేళ (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                కొరకు (; c < వెడల్పు; ++c) {
                    ఒకవేళ (!(c & align)) {
                        byte = *src++;
                    }
                    బిట్టు = (byte & ముసుగు);
                    ఒకవేళ (1) {
                        *dst = బిట్టు;
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } లేకపోతే {
            అయితే (ఎత్తు--) {
                Uint8 byte = 0, బిట్టు;
                కొరకు (c = 0; c < info->leading_skip; ++c) {
                    ఒకవేళ (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                కొరకు (; c < వెడల్పు; ++c) {
                    ఒకవేళ (!(c & align)) {
                        byte = *src++;
                    }
                    బిట్టు = (byte >> (8 - srcbpp)) & ముసుగు;
                    ఒకవేళ (1) {
                        *dst = బిట్టు;
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

SDL_FORCE_INLINE శూన్య BlitBto2(SDL_BlitInfo *info, స్థిరరాశి Uint32 srcbpp)
{
    స్థిరరాశి Uint32 ముసుగు = (1 << srcbpp) - 1;
    స్థిరరాశి Uint32 align = (8 / srcbpp) - 1;

    పూర్ణాంకం c;
    పూర్ణాంకం వెడల్పు, ఎత్తు;
    Uint8 *src;
    Uint16 *map, *dst;
    పూర్ణాంకం srcskip, dstskip;

    // Set up some basic variables
    వెడల్పు = info->dst_w;
    ఎత్తు = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = (Uint16 *)info->dst;
    dstskip = info->dst_skip / 2;
    map = (Uint16 *)info->పట్టిక;

    వెడల్పు += info->leading_skip;

    ఒకవేళ (srcbpp == 4)
        srcskip += వెడల్పు - (వెడల్పు + 1) / 2;
    లేకపోతే ఒకవేళ (srcbpp == 2)
        srcskip += వెడల్పు - (వెడల్పు + 3) / 4;
    లేకపోతే ఒకవేళ (srcbpp == 1)
        srcskip += వెడల్పు - (వెడల్పు + 7) / 8;

    ఒకవేళ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        అయితే (ఎత్తు--) {
            Uint8 byte = 0, బిట్టు;
            కొరకు (c = 0; c < info->leading_skip; ++c) {
                ఒకవేళ (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            కొరకు (; c < వెడల్పు; ++c) {
                ఒకవేళ (!(c & align)) {
                    byte = *src++;
                }
                బిట్టు = (byte & ముసుగు);
                ఒకవేళ (1) {
                    *dst = map[బిట్టు];
                }
                byte >>= srcbpp;
                dst++;
            }
            src += srcskip;
            dst += dstskip;
        }
    } లేకపోతే {
        అయితే (ఎత్తు--) {
            Uint8 byte = 0, బిట్టు;
            కొరకు (c = 0; c < info->leading_skip; ++c) {
                ఒకవేళ (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            కొరకు (; c < వెడల్పు; ++c) {
                ఒకవేళ (!(c & align)) {
                    byte = *src++;
                }
                బిట్టు = (byte >> (8 - srcbpp)) & ముసుగు;
                ఒకవేళ (1) {
                    *dst = map[బిట్టు];
                }
                byte <<= srcbpp;
                dst++;
            }
            src += srcskip;
            dst += dstskip;
        }
    }
}

SDL_FORCE_INLINE శూన్య BlitBto3(SDL_BlitInfo *info, స్థిరరాశి Uint32 srcbpp)
{
    స్థిరరాశి Uint32 ముసుగు = (1 << srcbpp) - 1;
    స్థిరరాశి Uint32 align = (8 / srcbpp) - 1;

    పూర్ణాంకం c, o;
    పూర్ణాంకం వెడల్పు, ఎత్తు;
    Uint8 *src, *map, *dst;
    పూర్ణాంకం srcskip, dstskip;

    // Set up some basic variables
    వెడల్పు = info->dst_w;
    ఎత్తు = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = info->dst;
    dstskip = info->dst_skip;
    map = info->పట్టిక;

    వెడల్పు += info->leading_skip;

    ఒకవేళ (srcbpp == 4)
        srcskip += వెడల్పు - (వెడల్పు + 1) / 2;
    లేకపోతే ఒకవేళ (srcbpp == 2)
        srcskip += వెడల్పు - (వెడల్పు + 3) / 4;
    లేకపోతే ఒకవేళ (srcbpp == 1)
        srcskip += వెడల్పు - (వెడల్పు + 7) / 8;

    ఒకవేళ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        అయితే (ఎత్తు--) {
            Uint8 byte = 0, బిట్టు;
            కొరకు (c = 0; c < info->leading_skip; ++c) {
                ఒకవేళ (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            కొరకు (; c < వెడల్పు; ++c) {
                ఒకవేళ (!(c & align)) {
                    byte = *src++;
                }
                బిట్టు = (byte & ముసుగు);
                ఒకవేళ (1) {
                    o = బిట్టు * 4;
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
    } లేకపోతే {
        అయితే (ఎత్తు--) {
            Uint8 byte = 0, బిట్టు;
            కొరకు (c = 0; c < info->leading_skip; ++c) {
                ఒకవేళ (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            కొరకు (; c < వెడల్పు; ++c) {
                ఒకవేళ (!(c & align)) {
                    byte = *src++;
                }
                బిట్టు = (byte >> (8 - srcbpp)) & ముసుగు;
                ఒకవేళ (1) {
                    o = బిట్టు * 4;
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

SDL_FORCE_INLINE శూన్య BlitBto4(SDL_BlitInfo *info, స్థిరరాశి Uint32 srcbpp)
{
    స్థిరరాశి Uint32 ముసుగు = (1 << srcbpp) - 1;
    స్థిరరాశి Uint32 align = (8 / srcbpp) - 1;

    పూర్ణాంకం వెడల్పు, ఎత్తు;
    Uint8 *src;
    Uint32 *map, *dst;
    పూర్ణాంకం srcskip, dstskip;
    పూర్ణాంకం c;

    // Set up some basic variables
    వెడల్పు = info->dst_w;
    ఎత్తు = info->dst_h;
    src = info->src;
    srcskip = info->src_skip;
    dst = (Uint32 *)info->dst;
    dstskip = info->dst_skip / 4;
    map = (Uint32 *)info->పట్టిక;

    వెడల్పు += info->leading_skip;

    ఒకవేళ (srcbpp == 4)
        srcskip += వెడల్పు - (వెడల్పు + 1) / 2;
    లేకపోతే ఒకవేళ (srcbpp == 2)
        srcskip += వెడల్పు - (వెడల్పు + 3) / 4;
    లేకపోతే ఒకవేళ (srcbpp == 1)
        srcskip += వెడల్పు - (వెడల్పు + 7) / 8;

    ఒకవేళ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        అయితే (ఎత్తు--) {
            Uint8 byte = 0, బిట్టు;
            కొరకు (c = 0; c < info->leading_skip; ++c) {
                ఒకవేళ (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            కొరకు (; c < వెడల్పు; ++c) {
                ఒకవేళ (!(c & align)) {
                    byte = *src++;
                }
                బిట్టు = (byte & ముసుగు);
                ఒకవేళ (1) {
                    *dst = map[బిట్టు];
                }
                byte >>= srcbpp;
                dst++;
            }
            src += srcskip;
            dst += dstskip;
        }
    } లేకపోతే {
        అయితే (ఎత్తు--) {
            Uint8 byte = 0, బిట్టు;
            కొరకు (c = 0; c < info->leading_skip; ++c) {
                ఒకవేళ (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            కొరకు (; c < వెడల్పు; ++c) {
                ఒకవేళ (!(c & align)) {
                    byte = *src++;
                }
                బిట్టు = (byte >> (8 - srcbpp)) & ముసుగు;
                ఒకవేళ (1) {
                    *dst = map[బిట్టు];
                }
                byte <<= srcbpp;
                dst++;
            }
            src += srcskip;
            dst += dstskip;
        }
    }
}

SDL_FORCE_INLINE శూన్య Blit_Bto1_కీలకం(SDL_BlitInfo *info, స్థిరరాశి Uint32 srcbpp)
{
    స్థిరరాశి Uint32 ముసుగు = (1 << srcbpp) - 1;
    స్థిరరాశి Uint32 align = (8 / srcbpp) - 1;

    పూర్ణాంకం వెడల్పు = info->dst_w;
    పూర్ణాంకం ఎత్తు = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    పూర్ణాంకం srcskip = info->src_skip;
    పూర్ణాంకం dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->పట్టిక;
    పూర్ణాంకం c;

    వెడల్పు += info->leading_skip;

    ఒకవేళ (srcbpp == 4)
        srcskip += వెడల్పు - (వెడల్పు + 1) / 2;
    లేకపోతే ఒకవేళ (srcbpp == 2)
        srcskip += వెడల్పు - (వెడల్పు + 3) / 4;
    లేకపోతే ఒకవేళ (srcbpp == 1)
        srcskip += వెడల్పు - (వెడల్పు + 7) / 8;

    ఒకవేళ (palmap) {
        ఒకవేళ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            అయితే (ఎత్తు--) {
                Uint8 byte = 0, బిట్టు;
                కొరకు (c = 0; c < info->leading_skip; ++c) {
                    ఒకవేళ (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                కొరకు (; c < వెడల్పు; ++c) {
                    ఒకవేళ (!(c & align)) {
                        byte = *src++;
                    }
                    బిట్టు = (byte & ముసుగు);
                    ఒకవేళ (బిట్టు != ckey) {
                        *dst = palmap[బిట్టు];
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } లేకపోతే {
            అయితే (ఎత్తు--) {
                Uint8 byte = 0, బిట్టు;
                కొరకు (c = 0; c < info->leading_skip; ++c) {
                    ఒకవేళ (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                కొరకు (; c < వెడల్పు; ++c) {
                    ఒకవేళ (!(c & align)) {
                        byte = *src++;
                    }
                    బిట్టు = (byte >> (8 - srcbpp)) & ముసుగు;
                    ఒకవేళ (బిట్టు != ckey) {
                        *dst = palmap[బిట్టు];
                    }
                    dst++;
                    byte <<= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        }
    } లేకపోతే {
        ఒకవేళ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
            అయితే (ఎత్తు--) {
                Uint8 byte = 0, బిట్టు;
                కొరకు (c = 0; c < info->leading_skip; ++c) {
                    ఒకవేళ (!(c & align)) {
                        byte = *src++;
                    }
                    byte >>= srcbpp;
                }
                కొరకు (; c < వెడల్పు; ++c) {
                    ఒకవేళ (!(c & align)) {
                        byte = *src++;
                    }
                    బిట్టు = (byte & ముసుగు);
                    ఒకవేళ (బిట్టు != ckey) {
                        *dst = బిట్టు;
                    }
                    dst++;
                    byte >>= srcbpp;
                }
                src += srcskip;
                dst += dstskip;
            }
        } లేకపోతే {
            అయితే (ఎత్తు--) {
                Uint8 byte = 0, బిట్టు;
                కొరకు (c = 0; c < info->leading_skip; ++c) {
                    ఒకవేళ (!(c & align)) {
                        byte = *src++;
                    }
                    byte <<= srcbpp;
                }
                కొరకు (; c < వెడల్పు; ++c) {
                    ఒకవేళ (!(c & align)) {
                        byte = *src++;
                    }
                    బిట్టు = (byte >> (8 - srcbpp)) & ముసుగు;
                    ఒకవేళ (బిట్టు != ckey) {
                        *dst = బిట్టు;
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

SDL_FORCE_INLINE శూన్య Blit_Bto2_కీలకం(SDL_BlitInfo *info, స్థిరరాశి Uint32 srcbpp)
{
    స్థిరరాశి Uint32 ముసుగు = (1 << srcbpp) - 1;
    స్థిరరాశి Uint32 align = (8 / srcbpp) - 1;

    పూర్ణాంకం వెడల్పు = info->dst_w;
    పూర్ణాంకం ఎత్తు = info->dst_h;
    Uint8 *src = info->src;
    Uint16 *dstp = (Uint16 *)info->dst;
    పూర్ణాంకం srcskip = info->src_skip;
    పూర్ణాంకం dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->పట్టిక;
    పూర్ణాంకం c;

    వెడల్పు += info->leading_skip;

    ఒకవేళ (srcbpp == 4)
        srcskip += వెడల్పు - (వెడల్పు + 1) / 2;
    లేకపోతే ఒకవేళ (srcbpp == 2)
        srcskip += వెడల్పు - (వెడల్పు + 3) / 4;
    లేకపోతే ఒకవేళ (srcbpp == 1)
        srcskip += వెడల్పు - (వెడల్పు + 7) / 8;
    dstskip /= 2;

    ఒకవేళ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        అయితే (ఎత్తు--) {
            Uint8 byte = 0, బిట్టు;
            కొరకు (c = 0; c < info->leading_skip; ++c) {
                ఒకవేళ (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            కొరకు (; c < వెడల్పు; ++c) {
                ఒకవేళ (!(c & align)) {
                    byte = *src++;
                }
                బిట్టు = (byte & ముసుగు);
                ఒకవేళ (బిట్టు != ckey) {
                    *dstp = ((Uint16 *)palmap)[బిట్టు];
                }
                byte >>= srcbpp;
                dstp++;
            }
            src += srcskip;
            dstp += dstskip;
        }
    } లేకపోతే {
        అయితే (ఎత్తు--) {
            Uint8 byte = 0, బిట్టు;
            కొరకు (c = 0; c < info->leading_skip; ++c) {
                ఒకవేళ (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            కొరకు (; c < వెడల్పు; ++c) {
                ఒకవేళ (!(c & align)) {
                    byte = *src++;
                }
                బిట్టు = (byte >> (8 - srcbpp)) & ముసుగు;
                ఒకవేళ (బిట్టు != ckey) {
                    *dstp = ((Uint16 *)palmap)[బిట్టు];
                }
                byte <<= srcbpp;
                dstp++;
            }
            src += srcskip;
            dstp += dstskip;
        }
    }
}

SDL_FORCE_INLINE శూన్య Blit_Bto3_కీలకం(SDL_BlitInfo *info, స్థిరరాశి Uint32 srcbpp)
{
    స్థిరరాశి Uint32 ముసుగు = (1 << srcbpp) - 1;
    స్థిరరాశి Uint32 align = (8 / srcbpp) - 1;

    పూర్ణాంకం వెడల్పు = info->dst_w;
    పూర్ణాంకం ఎత్తు = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    పూర్ణాంకం srcskip = info->src_skip;
    పూర్ణాంకం dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->పట్టిక;
    పూర్ణాంకం c;

    వెడల్పు += info->leading_skip;

    ఒకవేళ (srcbpp == 4)
        srcskip += వెడల్పు - (వెడల్పు + 1) / 2;
    లేకపోతే ఒకవేళ (srcbpp == 2)
        srcskip += వెడల్పు - (వెడల్పు + 3) / 4;
    లేకపోతే ఒకవేళ (srcbpp == 1)
        srcskip += వెడల్పు - (వెడల్పు + 7) / 8;

    ఒకవేళ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        అయితే (ఎత్తు--) {
            Uint8 byte = 0, బిట్టు;
            కొరకు (c = 0; c < info->leading_skip; ++c) {
                ఒకవేళ (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            కొరకు (; c < వెడల్పు; ++c) {
                ఒకవేళ (!(c & align)) {
                    byte = *src++;
                }
                బిట్టు = (byte & ముసుగు);
                ఒకవేళ (బిట్టు != ckey) {
                    SDL_memcpy(dst, &palmap[బిట్టు * 4], 3);
                }
                byte >>= srcbpp;
                dst += 3;
            }
            src += srcskip;
            dst += dstskip;
        }
    } లేకపోతే {
        అయితే (ఎత్తు--) {
            Uint8 byte = 0, బిట్టు;
            కొరకు (c = 0; c < info->leading_skip; ++c) {
                ఒకవేళ (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            కొరకు (; c < వెడల్పు; ++c) {
                ఒకవేళ (!(c & align)) {
                    byte = *src++;
                }
                బిట్టు = (byte >> (8 - srcbpp)) & ముసుగు;
                ఒకవేళ (బిట్టు != ckey) {
                    SDL_memcpy(dst, &palmap[బిట్టు * 4], 3);
                }
                byte <<= srcbpp;
                dst += 3;
            }
            src += srcskip;
            dst += dstskip;
        }
    }
}

SDL_FORCE_INLINE శూన్య Blit_Bto4_కీలకం(SDL_BlitInfo *info, స్థిరరాశి Uint32 srcbpp)
{
    స్థిరరాశి Uint32 ముసుగు = (1 << srcbpp) - 1;
    స్థిరరాశి Uint32 align = (8 / srcbpp) - 1;

    పూర్ణాంకం వెడల్పు = info->dst_w;
    పూర్ణాంకం ఎత్తు = info->dst_h;
    Uint8 *src = info->src;
    Uint32 *dstp = (Uint32 *)info->dst;
    పూర్ణాంకం srcskip = info->src_skip;
    పూర్ణాంకం dstskip = info->dst_skip;
    Uint32 ckey = info->colorkey;
    Uint8 *palmap = info->పట్టిక;
    పూర్ణాంకం c;

    వెడల్పు += info->leading_skip;

    ఒకవేళ (srcbpp == 4)
        srcskip += వెడల్పు - (వెడల్పు + 1) / 2;
    లేకపోతే ఒకవేళ (srcbpp == 2)
        srcskip += వెడల్పు - (వెడల్పు + 3) / 4;
    లేకపోతే ఒకవేళ (srcbpp == 1)
        srcskip += వెడల్పు - (వెడల్పు + 7) / 8;
    dstskip /= 4;

    ఒకవేళ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        అయితే (ఎత్తు--) {
            Uint8 byte = 0, బిట్టు;
            కొరకు (c = 0; c < info->leading_skip; ++c) {
                ఒకవేళ (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            కొరకు (; c < వెడల్పు; ++c) {
                ఒకవేళ (!(c & align)) {
                    byte = *src++;
                }
                బిట్టు = (byte & ముసుగు);
                ఒకవేళ (బిట్టు != ckey) {
                    *dstp = ((Uint32 *)palmap)[బిట్టు];
                }
                byte >>= srcbpp;
                dstp++;
            }
            src += srcskip;
            dstp += dstskip;
        }
    } లేకపోతే {
        అయితే (ఎత్తు--) {
            Uint8 byte = 0, బిట్టు;
            కొరకు (c = 0; c < info->leading_skip; ++c) {
                ఒకవేళ (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            కొరకు (; c < వెడల్పు; ++c) {
                ఒకవేళ (!(c & align)) {
                    byte = *src++;
                }
                బిట్టు = (byte >> (8 - srcbpp)) & ముసుగు;
                ఒకవేళ (బిట్టు != ckey) {
                    *dstp = ((Uint32 *)palmap)[బిట్టు];
                }
                byte <<= srcbpp;
                dstp++;
            }
            src += srcskip;
            dstp += dstskip;
        }
    }
}

స్థిర శూన్య BlitBtoNAlpha(SDL_BlitInfo *info)
{
    పూర్ణాంకం వెడల్పు = info->dst_w;
    పూర్ణాంకం ఎత్తు = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    పూర్ణాంకం srcskip = info->src_skip;
    పూర్ణాంకం dstskip = info->dst_skip;
    స్థిరరాశి SDL_Color *srcpal = info->src_pal->colors;
    స్థిరరాశి SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    స్థిరరాశి SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    పూర్ణాంకం srcbpp, dstbpp;
    పూర్ణాంకం c;
    Uint32 pixelvalue, ముసుగు, align;
    గుర్తులేని sR, sG, sB;
    గుర్తులేని dR, dG, dB, dA;
    స్థిరరాశి గుర్తులేని A = info->a;

    వెడల్పు += info->leading_skip;

    srcbpp = srcfmt->బైట్లు_చొప్పున_pixel;
    dstbpp = dstfmt->బైట్లు_చొప్పున_pixel;
    ఒకవేళ (srcbpp == 4)
        srcskip += వెడల్పు - (వెడల్పు + 1) / 2;
    లేకపోతే ఒకవేళ (srcbpp == 2)
        srcskip += వెడల్పు - (వెడల్పు + 3) / 4;
    లేకపోతే ఒకవేళ (srcbpp == 1)
        srcskip += వెడల్పు - (వెడల్పు + 7) / 8;
    ముసుగు = (1 << srcbpp) - 1;
    align = (8 / srcbpp) - 1;

    ఒకవేళ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        అయితే (ఎత్తు--) {
            Uint8 byte = 0, బిట్టు;
            కొరకు (c = 0; c < info->leading_skip; ++c) {
                ఒకవేళ (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            కొరకు (; c < వెడల్పు; ++c) {
                ఒకవేళ (!(c & align)) {
                    byte = *src++;
                }
                బిట్టు = (byte & ముసుగు);
                ఒకవేళ (1) {
                    sR = srcpal[బిట్టు].r;
                    sG = srcpal[బిట్టు].g;
                    sB = srcpal[బిట్టు].b;
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
    } లేకపోతే {
        అయితే (ఎత్తు--) {
            Uint8 byte = 0, బిట్టు;
            కొరకు (c = 0; c < info->leading_skip; ++c) {
                ఒకవేళ (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            కొరకు (; c < వెడల్పు; ++c) {
                ఒకవేళ (!(c & align)) {
                    byte = *src++;
                }
                బిట్టు = (byte >> (8 - srcbpp)) & ముసుగు;
                ఒకవేళ (1) {
                    sR = srcpal[బిట్టు].r;
                    sG = srcpal[బిట్టు].g;
                    sB = srcpal[బిట్టు].b;
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

స్థిర శూన్య Blit_Bto_NAlpha_కీలకం(SDL_BlitInfo *info)
{
    పూర్ణాంకం వెడల్పు = info->dst_w;
    పూర్ణాంకం ఎత్తు = info->dst_h;
    Uint8 *src = info->src;
    Uint8 *dst = info->dst;
    పూర్ణాంకం srcskip = info->src_skip;
    పూర్ణాంకం dstskip = info->dst_skip;
    స్థిరరాశి SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    స్థిరరాశి SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    స్థిరరాశి SDL_Color *srcpal = info->src_pal->colors;
    పూర్ణాంకం srcbpp, dstbpp;
    పూర్ణాంకం c;
    Uint32 pixelvalue, ముసుగు, align;
    గుర్తులేని sR, sG, sB;
    గుర్తులేని dR, dG, dB, dA;
    స్థిరరాశి గుర్తులేని A = info->a;
    Uint32 ckey = info->colorkey;

    వెడల్పు += info->leading_skip;

    srcbpp = srcfmt->బైట్లు_చొప్పున_pixel;
    dstbpp = dstfmt->బైట్లు_చొప్పున_pixel;
    ఒకవేళ (srcbpp == 4)
        srcskip += వెడల్పు - (వెడల్పు + 1) / 2;
    లేకపోతే ఒకవేళ (srcbpp == 2)
        srcskip += వెడల్పు - (వెడల్పు + 3) / 4;
    లేకపోతే ఒకవేళ (srcbpp == 1)
        srcskip += వెడల్పు - (వెడల్పు + 7) / 8;
    ముసుగు = (1 << srcbpp) - 1;
    align = (8 / srcbpp) - 1;

    ఒకవేళ (SDL_PIXELORDER(info->src_fmt->format) == SDL_BITMAPORDER_4321) {
        అయితే (ఎత్తు--) {
            Uint8 byte = 0, బిట్టు;
            కొరకు (c = 0; c < info->leading_skip; ++c) {
                ఒకవేళ (!(c & align)) {
                    byte = *src++;
                }
                byte >>= srcbpp;
            }
            కొరకు (; c < వెడల్పు; ++c) {
                ఒకవేళ (!(c & align)) {
                    byte = *src++;
                }
                బిట్టు = (byte & ముసుగు);
                ఒకవేళ (బిట్టు != ckey) {
                    sR = srcpal[బిట్టు].r;
                    sG = srcpal[బిట్టు].g;
                    sB = srcpal[బిట్టు].b;
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
    } లేకపోతే {
        అయితే (ఎత్తు--) {
            Uint8 byte = 0, బిట్టు;
            కొరకు (c = 0; c < info->leading_skip; ++c) {
                ఒకవేళ (!(c & align)) {
                    byte = *src++;
                }
                byte <<= srcbpp;
            }
            కొరకు (; c < వెడల్పు; ++c) {
                ఒకవేళ (!(c & align)) {
                    byte = *src++;
                }
                బిట్టు = (byte >> (8 - srcbpp)) & ముసుగు;
                ఒకవేళ (బిట్టు != ckey) {
                    sR = srcpal[బిట్టు].r;
                    sG = srcpal[బిట్టు].g;
                    sB = srcpal[బిట్టు].b;
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



స్థిర శూన్య Blit1bto1(SDL_BlitInfo *info) {
    BlitBto1(info, 1);
}

స్థిర శూన్య Blit1bto2(SDL_BlitInfo *info) {
    BlitBto2(info, 1);
}

స్థిర శూన్య Blit1bto3(SDL_BlitInfo *info) {
    BlitBto3(info, 1);
}

స్థిర శూన్య Blit1bto4(SDL_BlitInfo *info) {
    BlitBto4(info, 1);
}

స్థిర స్థిరరాశి SDL_BlitFunc bitmap_blit_1b[] = {
    (SDL_BlitFunc)ఖాళీ, Blit1bto1, Blit1bto2, Blit1bto3, Blit1bto4
};

స్థిర శూన్య Blit1bto1_కీలకం(SDL_BlitInfo *info) {
    Blit_Bto1_కీలకం(info, 1);
}

స్థిర శూన్య Blit1bto2_కీలకం(SDL_BlitInfo *info) {
    Blit_Bto2_కీలకం(info, 1);
}

స్థిర శూన్య Blit1bto3_కీలకం(SDL_BlitInfo *info) {
    Blit_Bto3_కీలకం(info, 1);
}

స్థిర శూన్య Blit1bto4_కీలకం(SDL_BlitInfo *info) {
    Blit_Bto4_కీలకం(info, 1);
}

స్థిర స్థిరరాశి SDL_BlitFunc colorkey_blit_1b[] = {
    (SDL_BlitFunc)ఖాళీ, Blit1bto1_కీలకం, Blit1bto2_కీలకం, Blit1bto3_కీలకం, Blit1bto4_కీలకం
};



స్థిర శూన్య Blit2bto1(SDL_BlitInfo *info) {
    BlitBto1(info, 2);
}

స్థిర శూన్య Blit2bto2(SDL_BlitInfo *info) {
    BlitBto2(info, 2);
}

స్థిర శూన్య Blit2bto3(SDL_BlitInfo *info) {
    BlitBto3(info, 2);
}

స్థిర శూన్య Blit2bto4(SDL_BlitInfo *info) {
    BlitBto4(info, 2);
}

స్థిర స్థిరరాశి SDL_BlitFunc bitmap_blit_2b[] = {
    (SDL_BlitFunc)ఖాళీ, Blit2bto1, Blit2bto2, Blit2bto3, Blit2bto4
};

స్థిర శూన్య Blit2bto1_కీలకం(SDL_BlitInfo *info) {
    Blit_Bto1_కీలకం(info, 2);
}

స్థిర శూన్య Blit2bto2_కీలకం(SDL_BlitInfo *info) {
    Blit_Bto2_కీలకం(info, 2);
}

స్థిర శూన్య Blit2bto3_కీలకం(SDL_BlitInfo *info) {
    Blit_Bto3_కీలకం(info, 2);
}

స్థిర శూన్య Blit2bto4_కీలకం(SDL_BlitInfo *info) {
    Blit_Bto4_కీలకం(info, 2);
}

స్థిర స్థిరరాశి SDL_BlitFunc colorkey_blit_2b[] = {
    (SDL_BlitFunc)ఖాళీ, Blit2bto1_కీలకం, Blit2bto2_కీలకం, Blit2bto3_కీలకం, Blit2bto4_కీలకం
};



స్థిర శూన్య Blit4bto1(SDL_BlitInfo *info) {
    BlitBto1(info, 4);
}

స్థిర శూన్య Blit4bto2(SDL_BlitInfo *info) {
    BlitBto2(info, 4);
}

స్థిర శూన్య Blit4bto3(SDL_BlitInfo *info) {
    BlitBto3(info, 4);
}

స్థిర శూన్య Blit4bto4(SDL_BlitInfo *info) {
    BlitBto4(info, 4);
}

స్థిర స్థిరరాశి SDL_BlitFunc bitmap_blit_4b[] = {
    (SDL_BlitFunc)ఖాళీ, Blit4bto1, Blit4bto2, Blit4bto3, Blit4bto4
};

స్థిర శూన్య Blit4bto1_కీలకం(SDL_BlitInfo *info) {
    Blit_Bto1_కీలకం(info, 4);
}

స్థిర శూన్య Blit4bto2_కీలకం(SDL_BlitInfo *info) {
    Blit_Bto2_కీలకం(info, 4);
}

స్థిర శూన్య Blit4bto3_కీలకం(SDL_BlitInfo *info) {
    Blit_Bto3_కీలకం(info, 4);
}

స్థిర శూన్య Blit4bto4_కీలకం(SDL_BlitInfo *info) {
    Blit_Bto4_కీలకం(info, 4);
}

స్థిర స్థిరరాశి SDL_BlitFunc colorkey_blit_4b[] = {
    (SDL_BlitFunc)ఖాళీ, Blit4bto1_కీలకం, Blit4bto2_కీలకం, Blit4bto3_కీలకం, Blit4bto4_కీలకం
};



SDL_BlitFunc SDL_CalculateBlit0(SDL_Surface *surface)
{
    పూర్ణాంకం which;

    ఒకవేళ (SDL_BITSPERPIXEL(surface->map.info.dst_fmt->format) < 8) {
        which = 0;
    } లేకపోతే {
        which = SDL_BYTESPERPIXEL(surface->map.info.dst_fmt->format);
    }

    ఒకవేళ (SDL_PIXELTYPE(surface->format) == SDL_PIXELTYPE_INDEX1) {
        ఎంపిక (surface->map.info.flags & ~SDL_COPY_RLE_ముసుగు) {
        స్థితి 0:
            ఒకవేళ (which < SDL_arraysize(bitmap_blit_1b)) {
                తిరిగి bitmap_blit_1b[which];
            }
            ఆపు;

        స్థితి SDL_COPY_COLORKEY:
            ఒకవేళ (which < SDL_arraysize(colorkey_blit_1b)) {
                తిరిగి colorkey_blit_1b[which];
            }
            ఆపు;

        స్థితి SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            తిరిగి which >= 2 ? BlitBtoNAlpha : (SDL_BlitFunc)ఖాళీ;

        స్థితి SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            తిరిగి which >= 2 ? Blit_Bto_NAlpha_కీలకం : (SDL_BlitFunc)ఖాళీ;
        }
        తిరిగి ఖాళీ;
    }

    ఒకవేళ (SDL_PIXELTYPE(surface->format) == SDL_PIXELTYPE_INDEX2) {
        ఎంపిక (surface->map.info.flags & ~SDL_COPY_RLE_ముసుగు) {
        స్థితి 0:
            ఒకవేళ (which < SDL_arraysize(bitmap_blit_2b)) {
                తిరిగి bitmap_blit_2b[which];
            }
            ఆపు;

        స్థితి SDL_COPY_COLORKEY:
            ఒకవేళ (which < SDL_arraysize(colorkey_blit_2b)) {
                తిరిగి colorkey_blit_2b[which];
            }
            ఆపు;

        స్థితి SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            తిరిగి which >= 2 ? BlitBtoNAlpha : (SDL_BlitFunc)ఖాళీ;

        స్థితి SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            తిరిగి which >= 2 ? Blit_Bto_NAlpha_కీలకం : (SDL_BlitFunc)ఖాళీ;
        }
        తిరిగి ఖాళీ;
    }

    ఒకవేళ (SDL_PIXELTYPE(surface->format) == SDL_PIXELTYPE_INDEX4) {
        ఎంపిక (surface->map.info.flags & ~SDL_COPY_RLE_ముసుగు) {
        స్థితి 0:
            ఒకవేళ (which < SDL_arraysize(bitmap_blit_4b)) {
                తిరిగి bitmap_blit_4b[which];
            }
            ఆపు;

        స్థితి SDL_COPY_COLORKEY:
            ఒకవేళ (which < SDL_arraysize(colorkey_blit_4b)) {
                తిరిగి colorkey_blit_4b[which];
            }
            ఆపు;

        స్థితి SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            తిరిగి which >= 2 ? BlitBtoNAlpha : (SDL_BlitFunc)ఖాళీ;

        స్థితి SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
            తిరిగి which >= 2 ? Blit_Bto_NAlpha_కీలకం : (SDL_BlitFunc)ఖాళీ;
        }
        తిరిగి ఖాళీ;
    }

    తిరిగి ఖాళీ;
}

#అయితే_ముగింపు // SDL_HAVE_BLIT_0
