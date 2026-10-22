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

#अन्तर्भाव "SDL_surface_c.h"
#अन्तर्भाव "SDL_blit_copy.h"

#ifdef SDL_SSE_INTRINSICS
// This assumes 16-byte aligned src and dst
स्थिर SDL_INLINE शून्य SDL_TARGETING("sse") SDL_memcpySSE(Uint8 *dst, ध्रुव Uint8 *src, पूर्णाङ्क len)
{
    पूर्णाङ्क i;

    __m128 मानानि[4];
    प्रति (i = len / 64; i--;) {
        _mm_prefetch((ध्रुव वर्ण *)src, _MM_HINT_NTA);
        मानानि[0] = *(__m128 *)(src + 0);
        मानानि[1] = *(__m128 *)(src + 16);
        मानानि[2] = *(__m128 *)(src + 32);
        मानानि[3] = *(__m128 *)(src + 48);
        _mm_stream_ps((भिन्न *)(dst + 0), मानानि[0]);
        _mm_stream_ps((भिन्न *)(dst + 16), मानानि[1]);
        _mm_stream_ps((भिन्न *)(dst + 32), मानानि[2]);
        _mm_stream_ps((भिन्न *)(dst + 48), मानानि[3]);
        src += 64;
        dst += 64;
    }

    जइ (len & 63) {
        SDL_memcpy(dst, src, len & 63);
    }
}
#endif // SDL_SSE_INTRINSICS

शून्य SDL_BlitCopy(SDL_BlitInfo *info)
{
    bool overlap;
    Uint8 *src, *dst;
    पूर्णाङ्क w, h;
    पूर्णाङ्क srcskip, dstskip;

    w = info->dst_w * info->dst_fmt->bytes_per_pixel;
    h = info->dst_h;
    src = info->src;
    dst = info->dst;
    srcskip = info->src_pitch;
    dstskip = info->dst_pitch;

    // Properly handle overlapping blits
    जइ (src < dst) {
        overlap = (dst < (src + h * srcskip));
    } अण्णहा {
        overlap = (src < (dst + h * dstskip));
    }
    जइ (overlap) {
        जइ (dst < src) {
            जाव (h--) {
                SDL_memmove(dst, src, w);
                src += srcskip;
                dst += dstskip;
            }
        } अण्णहा {
            src += ((h - 1) * srcskip);
            dst += ((h - 1) * dstskip);
            जाव (h--) {
                SDL_memmove(dst, src, w);
                src -= srcskip;
                dst -= dstskip;
            }
        }
        प्रत्यागम;
    }

#ifdef SDL_SSE_INTRINSICS
    जइ (SDL_HasSSE() &&
        !((uintptr_t)src & 15) && !(srcskip & 15) &&
        !((uintptr_t)dst & 15) && !(dstskip & 15)) {
        जाव (h--) {
            SDL_memcpySSE(dst, src, w);
            src += srcskip;
            dst += dstskip;
        }
        प्रत्यागम;
    }
#endif

    जाव (h--) {
        SDL_memcpy(dst, src, w);
        src += srcskip;
        dst += dstskip;
    }
}
