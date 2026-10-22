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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ଅନ୍ତର୍ଭାଵ "SDL_surface_c.h"
#ଅନ୍ତର୍ଭାଵ "SDL_blit_copy.h"

#ifdef SDL_SSE_INTRINSICS
// This assumes 16-byte aligned src and dst
ସ୍ଥିର SDL_INLINE ଶୂନ୍ୟ SDL_TARGETING("sse") SDL_memcpySSE(Uint8 *dst, ଅଚଳ Uint8 *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା len)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    __m128 ମୂଲ୍ୟଗୁଡ଼ିକ[4];
    ପାଇଁ (i = len / 64; i--;) {
        _mm_prefetch((ଅଚଳ ଅକ୍ଷର *)src, _MM_HINT_NTA);
        ମୂଲ୍ୟଗୁଡ଼ିକ[0] = *(__m128 *)(src + 0);
        ମୂଲ୍ୟଗୁଡ଼ିକ[1] = *(__m128 *)(src + 16);
        ମୂଲ୍ୟଗୁଡ଼ିକ[2] = *(__m128 *)(src + 32);
        ମୂଲ୍ୟଗୁଡ଼ିକ[3] = *(__m128 *)(src + 48);
        _mm_stream_ps((ଦଶମିକ *)(dst + 0), ମୂଲ୍ୟଗୁଡ଼ିକ[0]);
        _mm_stream_ps((ଦଶମିକ *)(dst + 16), ମୂଲ୍ୟଗୁଡ଼ିକ[1]);
        _mm_stream_ps((ଦଶମିକ *)(dst + 32), ମୂଲ୍ୟଗୁଡ଼ିକ[2]);
        _mm_stream_ps((ଦଶମିକ *)(dst + 48), ମୂଲ୍ୟଗୁଡ଼ିକ[3]);
        src += 64;
        dst += 64;
    }

    ଯଦି (len & 63) {
        SDL_memcpy(dst, src, len & 63);
    }
}
#endif // SDL_SSE_INTRINSICS

ଶୂନ୍ୟ SDL_BlitCopy(SDL_BlitInfo *info)
{
    bool overlap;
    Uint8 *src, *dst;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା w, h;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା srcskip, dstskip;

    w = info->dst_w * info->dst_fmt->bytes_per_pixel;
    h = info->dst_h;
    src = info->src;
    dst = info->dst;
    srcskip = info->src_pitch;
    dstskip = info->dst_pitch;

    // Properly handle overlapping blits
    ଯଦି (src < dst) {
        overlap = (dst < (src + h * srcskip));
    } ଅନ୍ୟଥା {
        overlap = (src < (dst + h * dstskip));
    }
    ଯଦି (overlap) {
        ଯଦି (dst < src) {
            ଯେତେବେଳେ (h--) {
                SDL_memmove(dst, src, w);
                src += srcskip;
                dst += dstskip;
            }
        } ଅନ୍ୟଥା {
            src += ((h - 1) * srcskip);
            dst += ((h - 1) * dstskip);
            ଯେତେବେଳେ (h--) {
                SDL_memmove(dst, src, w);
                src -= srcskip;
                dst -= dstskip;
            }
        }
        ଫେରନ୍ତୁ;
    }

#ifdef SDL_SSE_INTRINSICS
    ଯଦି (SDL_HasSSE() &&
        !((uintptr_t)src & 15) && !(srcskip & 15) &&
        !((uintptr_t)dst & 15) && !(dstskip & 15)) {
        ଯେତେବେଳେ (h--) {
            SDL_memcpySSE(dst, src, w);
            src += srcskip;
            dst += dstskip;
        }
        ଫେରନ୍ତୁ;
    }
#endif

    ଯେତେବେଳେ (h--) {
        SDL_memcpy(dst, src, w);
        src += srcskip;
        dst += dstskip;
    }
}
