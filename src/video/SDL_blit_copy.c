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
#شامل "SDL_internal.h"

#شامل "SDL_surface_c.h"
#شامل "SDL_blit_copy.h"

#اگر_تعریف_شدہ SDL_SSE_INTRINSICS
// This assumes 16-byte aligned src and dst
ساکن SDL_INLINE خالی SDL_TARGETING("sse") SDL_memcpySSE(Uint8 *dst, ثابت Uint8 *src, صحیح len)
{
    صحیح i;

    __m128 اقدار[4];
    برائے (i = len / 64; i--;) {
        _mm_prefetch((ثابت حرف *)src, _MM_HINT_NTA);
        اقدار[0] = *(__m128 *)(src + 0);
        اقدار[1] = *(__m128 *)(src + 16);
        اقدار[2] = *(__m128 *)(src + 32);
        اقدار[3] = *(__m128 *)(src + 48);
        mm_دھارا_ps((اعشاری *)(dst + 0), اقدار[0]);
        mm_دھارا_ps((اعشاری *)(dst + 16), اقدار[1]);
        mm_دھارا_ps((اعشاری *)(dst + 32), اقدار[2]);
        mm_دھارا_ps((اعشاری *)(dst + 48), اقدار[3]);
        src += 64;
        dst += 64;
    }

    اگر (len & 63) {
        SDL_memcpy(dst, src, len & 63);
    }
}
#اگر_ختم // SDL_SSE_INTRINSICS

خالی SDL_BlitCopy(SDL_BlitInfo *info)
{
    bool overlap;
    Uint8 *src, *dst;
    صحیح w, h;
    صحیح srcskip, dstskip;

    w = info->dst_w * info->dst_fmt->بائٹیں_فی_pixel;
    h = info->dst_h;
    src = info->src;
    dst = info->dst;
    srcskip = info->src_pitch;
    dstskip = info->dst_pitch;

    // Properly handle overlapping blits
    اگر (src < dst) {
        overlap = (dst < (src + h * srcskip));
    } ورنہ {
        overlap = (src < (dst + h * dstskip));
    }
    اگر (overlap) {
        اگر (dst < src) {
            جب (h--) {
                SDL_memmove(dst, src, w);
                src += srcskip;
                dst += dstskip;
            }
        } ورنہ {
            src += ((h - 1) * srcskip);
            dst += ((h - 1) * dstskip);
            جب (h--) {
                SDL_memmove(dst, src, w);
                src -= srcskip;
                dst -= dstskip;
            }
        }
        واپس;
    }

#اگر_تعریف_شدہ SDL_SSE_INTRINSICS
    اگر (SDL_HasSSE() &&
        !((uintptr_t)src & 15) && !(srcskip & 15) &&
        !((uintptr_t)dst & 15) && !(dstskip & 15)) {
        جب (h--) {
            SDL_memcpySSE(dst, src, w);
            src += srcskip;
            dst += dstskip;
        }
        واپس;
    }
#اگر_ختم

    جب (h--) {
        SDL_memcpy(dst, src, w);
        src += srcskip;
        dst += dstskip;
    }
}
