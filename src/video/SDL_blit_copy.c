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

#અન્તર્ભાવ "SDL_surface_c.h"
#અન્તર્ભાવ "SDL_blit_copy.h"

#ifdef SDL_SSE_INTRINSICS
// This assumes 16-byte aligned src and dst
સ્થિર SDL_INLINE શૂન્ય SDL_TARGETING("sse") SDL_memcpySSE(Uint8 *dst, અચલ Uint8 *src, પૂર્ણાંક len)
{
    પૂર્ણાંક i;

    __m128 કિંમતો[4];
    માટે (i = len / 64; i--;) {
        _mm_prefetch((અચલ અક્ષર *)src, _MM_HINT_NTA);
        કિંમતો[0] = *(__m128 *)(src + 0);
        કિંમતો[1] = *(__m128 *)(src + 16);
        કિંમતો[2] = *(__m128 *)(src + 32);
        કિંમતો[3] = *(__m128 *)(src + 48);
        _mm_stream_ps((દશાંશ *)(dst + 0), કિંમતો[0]);
        _mm_stream_ps((દશાંશ *)(dst + 16), કિંમતો[1]);
        _mm_stream_ps((દશાંશ *)(dst + 32), કિંમતો[2]);
        _mm_stream_ps((દશાંશ *)(dst + 48), કિંમતો[3]);
        src += 64;
        dst += 64;
    }

    જો (len & 63) {
        SDL_memcpy(dst, src, len & 63);
    }
}
#endif // SDL_SSE_INTRINSICS

શૂન્ય SDL_BlitCopy(SDL_BlitInfo *info)
{
    bool overlap;
    Uint8 *src, *dst;
    પૂર્ણાંક w, h;
    પૂર્ણાંક srcskip, dstskip;

    w = info->dst_w * info->dst_fmt->bytes_per_pixel;
    h = info->dst_h;
    src = info->src;
    dst = info->dst;
    srcskip = info->src_pitch;
    dstskip = info->dst_pitch;

    // Properly handle overlapping blits
    જો (src < dst) {
        overlap = (dst < (src + h * srcskip));
    } નહીંતર {
        overlap = (src < (dst + h * dstskip));
    }
    જો (overlap) {
        જો (dst < src) {
            જ્યારે (h--) {
                SDL_memmove(dst, src, w);
                src += srcskip;
                dst += dstskip;
            }
        } નહીંતર {
            src += ((h - 1) * srcskip);
            dst += ((h - 1) * dstskip);
            જ્યારે (h--) {
                SDL_memmove(dst, src, w);
                src -= srcskip;
                dst -= dstskip;
            }
        }
        પાછા;
    }

#ifdef SDL_SSE_INTRINSICS
    જો (SDL_HasSSE() &&
        !((uintptr_t)src & 15) && !(srcskip & 15) &&
        !((uintptr_t)dst & 15) && !(dstskip & 15)) {
        જ્યારે (h--) {
            SDL_memcpySSE(dst, src, w);
            src += srcskip;
            dst += dstskip;
        }
        પાછા;
    }
#endif

    જ્યારે (h--) {
        SDL_memcpy(dst, src, w);
        src += srcskip;
        dst += dstskip;
    }
}
