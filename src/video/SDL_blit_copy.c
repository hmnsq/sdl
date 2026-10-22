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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_surface_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_blit_copy.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_SSE_INTRINSICS
// This assumes 16-byte aligned src and dst
ਸਥਿਰ SDL_INLINE ਖਾਲੀ SDL_TARGETING("sse") SDL_memcpySSE(Uint8 *dst, ਅਚਲ Uint8 *src, ਪੂਰਨ len)
{
    ਪੂਰਨ i;

    __m128 ਮੁੱਲਾਂ[4];
    ਲਈ (i = len / 64; i--;) {
        _mm_prefetch((ਅਚਲ ਅੱਖਰ *)src, _MM_HINT_NTA);
        ਮੁੱਲਾਂ[0] = *(__m128 *)(src + 0);
        ਮੁੱਲਾਂ[1] = *(__m128 *)(src + 16);
        ਮੁੱਲਾਂ[2] = *(__m128 *)(src + 32);
        ਮੁੱਲਾਂ[3] = *(__m128 *)(src + 48);
        mm_ਧਾਰਾ_ps((ਦਸ਼ਮਲਵ *)(dst + 0), ਮੁੱਲਾਂ[0]);
        mm_ਧਾਰਾ_ps((ਦਸ਼ਮਲਵ *)(dst + 16), ਮੁੱਲਾਂ[1]);
        mm_ਧਾਰਾ_ps((ਦਸ਼ਮਲਵ *)(dst + 32), ਮੁੱਲਾਂ[2]);
        mm_ਧਾਰਾ_ps((ਦਸ਼ਮਲਵ *)(dst + 48), ਮੁੱਲਾਂ[3]);
        src += 64;
        dst += 64;
    }

    ਜੇ (len & 63) {
        SDL_memcpy(dst, src, len & 63);
    }
}
#ਜੇ_ਅੰਤ // SDL_SSE_INTRINSICS

ਖਾਲੀ SDL_BlitCopy(SDL_BlitInfo *info)
{
    bool overlap;
    Uint8 *src, *dst;
    ਪੂਰਨ w, h;
    ਪੂਰਨ srcskip, dstskip;

    w = info->dst_w * info->dst_fmt->ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel;
    h = info->dst_h;
    src = info->src;
    dst = info->dst;
    srcskip = info->src_pitch;
    dstskip = info->dst_pitch;

    // Properly handle overlapping blits
    ਜੇ (src < dst) {
        overlap = (dst < (src + h * srcskip));
    } ਨਹੀਂਤਾਂ {
        overlap = (src < (dst + h * dstskip));
    }
    ਜੇ (overlap) {
        ਜੇ (dst < src) {
            ਜਦੋਂ (h--) {
                SDL_memmove(dst, src, w);
                src += srcskip;
                dst += dstskip;
            }
        } ਨਹੀਂਤਾਂ {
            src += ((h - 1) * srcskip);
            dst += ((h - 1) * dstskip);
            ਜਦੋਂ (h--) {
                SDL_memmove(dst, src, w);
                src -= srcskip;
                dst -= dstskip;
            }
        }
        ਵਾਪਸ;
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_SSE_INTRINSICS
    ਜੇ (SDL_HasSSE() &&
        !((uintptr_t)src & 15) && !(srcskip & 15) &&
        !((uintptr_t)dst & 15) && !(dstskip & 15)) {
        ਜਦੋਂ (h--) {
            SDL_memcpySSE(dst, src, w);
            src += srcskip;
            dst += dstskip;
        }
        ਵਾਪਸ;
    }
#ਜੇ_ਅੰਤ

    ਜਦੋਂ (h--) {
        SDL_memcpy(dst, src, w);
        src += srcskip;
        dst += dstskip;
    }
}
