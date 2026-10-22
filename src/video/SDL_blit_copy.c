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
#include "SDL_internal.h"

#include "SDL_surface_c.h"
#include "SDL_blit_copy.h"

#ifdef SDL_SSE_INTRINSICS
// This assumes 16-byte aligned src and dst
static SDL_INLINE void SDL_TARGETING("sse") SDL_memcpySSE(Uint8 *dst, const Uint8 *src, 정수 len)
{
    정수 i;

    __m128 values[4];
    위해 (i = len / 64; i--;) {
        _mm_prefetch((const char *)src, _MM_HINT_NTA);
        values[0] = *(__m128 *)(src + 0);
        values[1] = *(__m128 *)(src + 16);
        values[2] = *(__m128 *)(src + 32);
        values[3] = *(__m128 *)(src + 48);
        _mm_stream_ps((float *)(dst + 0), values[0]);
        _mm_stream_ps((float *)(dst + 16), values[1]);
        _mm_stream_ps((float *)(dst + 32), values[2]);
        _mm_stream_ps((float *)(dst + 48), values[3]);
        src += 64;
        dst += 64;
    }

    만약 (len & 63) {
        SDL_memcpy(dst, src, len & 63);
    }
}
#endif // SDL_SSE_INTRINSICS

void SDL_BlitCopy(SDL_BlitInfo *info)
{
    bool overlap;
    Uint8 *src, *dst;
    정수 w, h;
    정수 srcskip, dstskip;

    w = info->dst_w * info->dst_fmt->bytes_per_pixel;
    h = info->dst_h;
    src = info->src;
    dst = info->dst;
    srcskip = info->src_pitch;
    dstskip = info->dst_pitch;

    // Properly handle overlapping blits
    만약 (src < dst) {
        overlap = (dst < (src + h * srcskip));
    } 아니면 {
        overlap = (src < (dst + h * dstskip));
    }
    만약 (overlap) {
        만약 (dst < src) {
            동안 (h--) {
                SDL_memmove(dst, src, w);
                src += srcskip;
                dst += dstskip;
            }
        } 아니면 {
            src += ((h - 1) * srcskip);
            dst += ((h - 1) * dstskip);
            동안 (h--) {
                SDL_memmove(dst, src, w);
                src -= srcskip;
                dst -= dstskip;
            }
        }
        반환;
    }

#ifdef SDL_SSE_INTRINSICS
    만약 (SDL_HasSSE() &&
        !((uintptr_t)src & 15) && !(srcskip & 15) &&
        !((uintptr_t)dst & 15) && !(dstskip & 15)) {
        동안 (h--) {
            SDL_memcpySSE(dst, src, w);
            src += srcskip;
            dst += dstskip;
        }
        반환;
    }
#endif

    동안 (h--) {
        SDL_memcpy(dst, src, w);
        src += srcskip;
        dst += dstskip;
    }
}
