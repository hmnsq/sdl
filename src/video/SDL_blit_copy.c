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
#অন্তর্ভাৱ "SDL_internal.h"

#অন্তর্ভাৱ "SDL_surface_c.h"
#অন্তর্ভাৱ "SDL_blit_copy.h"

#ifdef SDL_SSE_INTRINSICS
// This assumes 16-byte aligned src and dst
স্থির SDL_INLINE শূন্য SDL_TARGETING("sse") SDL_memcpySSE(Uint8 *dst, ধ্রুৱ Uint8 *src, পূর্ণাঙ্ক len)
{
    পূর্ণাঙ্ক i;

    __m128 মানসমূহ[4];
    বাবে (i = len / 64; i--;) {
        _mm_prefetch((ধ্রুৱ ৱর্ণ *)src, _MM_HINT_NTA);
        মানসমূহ[0] = *(__m128 *)(src + 0);
        মানসমূহ[1] = *(__m128 *)(src + 16);
        মানসমূহ[2] = *(__m128 *)(src + 32);
        মানসমূহ[3] = *(__m128 *)(src + 48);
        _mm_stream_ps((ভিন্ন *)(dst + 0), মানসমূহ[0]);
        _mm_stream_ps((ভিন্ন *)(dst + 16), মানসমূহ[1]);
        _mm_stream_ps((ভিন্ন *)(dst + 32), মানসমূহ[2]);
        _mm_stream_ps((ভিন্ন *)(dst + 48), মানসমূহ[3]);
        src += 64;
        dst += 64;
    }

    যদি (len & 63) {
        SDL_memcpy(dst, src, len & 63);
    }
}
#endif // SDL_SSE_INTRINSICS

শূন্য SDL_BlitCopy(SDL_BlitInfo *info)
{
    bool overlap;
    Uint8 *src, *dst;
    পূর্ণাঙ্ক w, h;
    পূর্ণাঙ্ক srcskip, dstskip;

    w = info->dst_w * info->dst_fmt->bytes_per_pixel;
    h = info->dst_h;
    src = info->src;
    dst = info->dst;
    srcskip = info->src_pitch;
    dstskip = info->dst_pitch;

    // Properly handle overlapping blits
    যদি (src < dst) {
        overlap = (dst < (src + h * srcskip));
    } অন্যথা {
        overlap = (src < (dst + h * dstskip));
    }
    যদি (overlap) {
        যদি (dst < src) {
            যেতিয়ালৈ (h--) {
                SDL_memmove(dst, src, w);
                src += srcskip;
                dst += dstskip;
            }
        } অন্যথা {
            src += ((h - 1) * srcskip);
            dst += ((h - 1) * dstskip);
            যেতিয়ালৈ (h--) {
                SDL_memmove(dst, src, w);
                src -= srcskip;
                dst -= dstskip;
            }
        }
        ঘূৰাই;
    }

#ifdef SDL_SSE_INTRINSICS
    যদি (SDL_HasSSE() &&
        !((uintptr_t)src & 15) && !(srcskip & 15) &&
        !((uintptr_t)dst & 15) && !(dstskip & 15)) {
        যেতিয়ালৈ (h--) {
            SDL_memcpySSE(dst, src, w);
            src += srcskip;
            dst += dstskip;
        }
        ঘূৰাই;
    }
#endif

    যেতিয়ালৈ (h--) {
        SDL_memcpy(dst, src, w);
        src += srcskip;
        dst += dstskip;
    }
}
