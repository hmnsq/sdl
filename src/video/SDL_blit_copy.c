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
#அந்தர்பாவ "SDL_internal.h"

#அந்தர்பாவ "SDL_surface_c.h"
#அந்தர்பாவ "SDL_blit_copy.h"

#ifdef SDL_SSE_INTRINSICS
// This assumes 16-byte aligned src and dst
நிலையான SDL_INLINE வெறுமை SDL_TARGETING("sse") SDL_memcpySSE(Uint8 *dst, மாறிலி Uint8 *src, முழு len)
{
    முழு i;

    __m128 மதிப்புகள்[4];
    க்கு (i = len / 64; i--;) {
        _mm_prefetch((மாறிலி எழுத்து *)src, _MM_HINT_NTA);
        மதிப்புகள்[0] = *(__m128 *)(src + 0);
        மதிப்புகள்[1] = *(__m128 *)(src + 16);
        மதிப்புகள்[2] = *(__m128 *)(src + 32);
        மதிப்புகள்[3] = *(__m128 *)(src + 48);
        _mm_stream_ps((தசம *)(dst + 0), மதிப்புகள்[0]);
        _mm_stream_ps((தசம *)(dst + 16), மதிப்புகள்[1]);
        _mm_stream_ps((தசம *)(dst + 32), மதிப்புகள்[2]);
        _mm_stream_ps((தசம *)(dst + 48), மதிப்புகள்[3]);
        src += 64;
        dst += 64;
    }

    எனில் (len & 63) {
        SDL_memcpy(dst, src, len & 63);
    }
}
#endif // SDL_SSE_INTRINSICS

வெறுமை SDL_BlitCopy(SDL_BlitInfo *info)
{
    bool overlap;
    Uint8 *src, *dst;
    முழு w, h;
    முழு srcskip, dstskip;

    w = info->dst_w * info->dst_fmt->bytes_per_pixel;
    h = info->dst_h;
    src = info->src;
    dst = info->dst;
    srcskip = info->src_pitch;
    dstskip = info->dst_pitch;

    // Properly handle overlapping blits
    எனில் (src < dst) {
        overlap = (dst < (src + h * srcskip));
    } இல்லையெனில் {
        overlap = (src < (dst + h * dstskip));
    }
    எனில் (overlap) {
        எனில் (dst < src) {
            போது (h--) {
                SDL_memmove(dst, src, w);
                src += srcskip;
                dst += dstskip;
            }
        } இல்லையெனில் {
            src += ((h - 1) * srcskip);
            dst += ((h - 1) * dstskip);
            போது (h--) {
                SDL_memmove(dst, src, w);
                src -= srcskip;
                dst -= dstskip;
            }
        }
        திரும்பு;
    }

#ifdef SDL_SSE_INTRINSICS
    எனில் (SDL_HasSSE() &&
        !((uintptr_t)src & 15) && !(srcskip & 15) &&
        !((uintptr_t)dst & 15) && !(dstskip & 15)) {
        போது (h--) {
            SDL_memcpySSE(dst, src, w);
            src += srcskip;
            dst += dstskip;
        }
        திரும்பு;
    }
#endif

    போது (h--) {
        SDL_memcpy(dst, src, w);
        src += srcskip;
        dst += dstskip;
    }
}
