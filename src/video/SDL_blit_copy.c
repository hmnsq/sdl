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

#అన్తర్భావ "SDL_surface_c.h"
#అన్తర్భావ "SDL_blit_copy.h"

#నిర్వచితమైతే SDL_SSE_INTRINSICS
// This assumes 16-byte aligned src and dst
స్థిర SDL_INLINE శూన్య SDL_TARGETING("sse") SDL_memcpySSE(Uint8 *dst, స్థిరరాశి Uint8 *src, పూర్ణాంకం len)
{
    పూర్ణాంకం i;

    __m128 విలువలు[4];
    కొరకు (i = len / 64; i--;) {
        _mm_prefetch((స్థిరరాశి అక్షరం *)src, _MM_HINT_NTA);
        విలువలు[0] = *(__m128 *)(src + 0);
        విలువలు[1] = *(__m128 *)(src + 16);
        విలువలు[2] = *(__m128 *)(src + 32);
        విలువలు[3] = *(__m128 *)(src + 48);
        mm_ప్రవాహం_ps((దశాంశం *)(dst + 0), విలువలు[0]);
        mm_ప్రవాహం_ps((దశాంశం *)(dst + 16), విలువలు[1]);
        mm_ప్రవాహం_ps((దశాంశం *)(dst + 32), విలువలు[2]);
        mm_ప్రవాహం_ps((దశాంశం *)(dst + 48), విలువలు[3]);
        src += 64;
        dst += 64;
    }

    ఒకవేళ (len & 63) {
        SDL_memcpy(dst, src, len & 63);
    }
}
#అయితే_ముగింపు // SDL_SSE_INTRINSICS

శూన్య SDL_BlitCopy(SDL_BlitInfo *info)
{
    bool overlap;
    Uint8 *src, *dst;
    పూర్ణాంకం w, h;
    పూర్ణాంకం srcskip, dstskip;

    w = info->dst_w * info->dst_fmt->బైట్లు_చొప్పున_pixel;
    h = info->dst_h;
    src = info->src;
    dst = info->dst;
    srcskip = info->src_pitch;
    dstskip = info->dst_pitch;

    // Properly handle overlapping blits
    ఒకవేళ (src < dst) {
        overlap = (dst < (src + h * srcskip));
    } లేకపోతే {
        overlap = (src < (dst + h * dstskip));
    }
    ఒకవేళ (overlap) {
        ఒకవేళ (dst < src) {
            అయితే (h--) {
                SDL_memmove(dst, src, w);
                src += srcskip;
                dst += dstskip;
            }
        } లేకపోతే {
            src += ((h - 1) * srcskip);
            dst += ((h - 1) * dstskip);
            అయితే (h--) {
                SDL_memmove(dst, src, w);
                src -= srcskip;
                dst -= dstskip;
            }
        }
        తిరిగి;
    }

#నిర్వచితమైతే SDL_SSE_INTRINSICS
    ఒకవేళ (SDL_HasSSE() &&
        !((uintptr_t)src & 15) && !(srcskip & 15) &&
        !((uintptr_t)dst & 15) && !(dstskip & 15)) {
        అయితే (h--) {
            SDL_memcpySSE(dst, src, w);
            src += srcskip;
            dst += dstskip;
        }
        తిరిగి;
    }
#అయితే_ముగింపు

    అయితే (h--) {
        SDL_memcpy(dst, src, w);
        src += srcskip;
        dst += dstskip;
    }
}
