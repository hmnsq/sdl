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
#समावेश "SDL_internal.h"

#समावेश "SDL_surface_c.h"
#समावेश "SDL_blit_copy.h"

#अगर_घोषित SDL_SSE_INTRINSICS
// This assumes 16-byte aligned src and dst
अटल SDL_INLINE व्योम SDL_TARGETING("sse") SDL_memcpySSE(Uint8 *dst, स्थिर Uint8 *src, पूर्णांक len)
{
    पूर्णांक i;

    __m128 मूल्यावली[4];
    क्रम (i = len / 64; i--;) {
        _mm_prefetch((स्थिर अक्षर *)src, _MM_HINT_NTA);
        मूल्यावली[0] = *(__m128 *)(src + 0);
        मूल्यावली[1] = *(__m128 *)(src + 16);
        मूल्यावली[2] = *(__m128 *)(src + 32);
        मूल्यावली[3] = *(__m128 *)(src + 48);
        _mm_stream_ps((भग्न *)(dst + 0), मूल्यावली[0]);
        _mm_stream_ps((भग्न *)(dst + 16), मूल्यावली[1]);
        _mm_stream_ps((भग्न *)(dst + 32), मूल्यावली[2]);
        _mm_stream_ps((भग्न *)(dst + 48), मूल्यावली[3]);
        src += 64;
        dst += 64;
    }

    अगर (len & 63) {
        SDL_memcpy(dst, src, len & 63);
    }
}
#पूर्ण_अगर // SDL_SSE_INTRINSICS

व्योम SDL_BlitCopy(SDL_BlitInfo *info)
{
    bool overlap;
    Uint8 *src, *dst;
    पूर्णांक w, h;
    पूर्णांक srcskip, dstskip;

    w = info->dst_w * info->dst_fmt->bytes_per_pixel;
    h = info->dst_h;
    src = info->src;
    dst = info->dst;
    srcskip = info->src_pitch;
    dstskip = info->dst_pitch;

    // Properly handle overlapping blits
    अगर (src < dst) {
        overlap = (dst < (src + h * srcskip));
    } अन्यथा {
        overlap = (src < (dst + h * dstskip));
    }
    अगर (overlap) {
        अगर (dst < src) {
            जबतक (h--) {
                SDL_memmove(dst, src, w);
                src += srcskip;
                dst += dstskip;
            }
        } अन्यथा {
            src += ((h - 1) * srcskip);
            dst += ((h - 1) * dstskip);
            जबतक (h--) {
                SDL_memmove(dst, src, w);
                src -= srcskip;
                dst -= dstskip;
            }
        }
        वापस;
    }

#अगर_घोषित SDL_SSE_INTRINSICS
    अगर (SDL_HasSSE() &&
        !((uintptr_t)src & 15) && !(srcskip & 15) &&
        !((uintptr_t)dst & 15) && !(dstskip & 15)) {
        जबतक (h--) {
            SDL_memcpySSE(dst, src, w);
            src += srcskip;
            dst += dstskip;
        }
        वापस;
    }
#पूर्ण_अगर

    जबतक (h--) {
        SDL_memcpy(dst, src, w);
        src += srcskip;
        dst += dstskip;
    }
}
