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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ಅನ್ತರ್ಭಾವ "SDL_surface_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_blit_copy.h"

#ifdef SDL_SSE_INTRINSICS
// This assumes 16-byte aligned src and dst
ಸ್ಥಿರ SDL_INLINE ಶೂನ್ಯ SDL_TARGETING("sse") SDL_memcpySSE(Uint8 *dst, ಧ್ರುವ Uint8 *src, ಪೂರ್ಣಾಙ್ಕ len)
{
    ಪೂರ್ಣಾಙ್ಕ i;

    __m128 ಮೌಲ್ಯಗಳು[4];
    ಪ್ರತಿ (i = len / 64; i--;) {
        _mm_prefetch((ಧ್ರುವ ವರ್ಣ *)src, _MM_HINT_NTA);
        ಮೌಲ್ಯಗಳು[0] = *(__m128 *)(src + 0);
        ಮೌಲ್ಯಗಳು[1] = *(__m128 *)(src + 16);
        ಮೌಲ್ಯಗಳು[2] = *(__m128 *)(src + 32);
        ಮೌಲ್ಯಗಳು[3] = *(__m128 *)(src + 48);
        _mm_stream_ps((ಭಿನ್ನ *)(dst + 0), ಮೌಲ್ಯಗಳು[0]);
        _mm_stream_ps((ಭಿನ್ನ *)(dst + 16), ಮೌಲ್ಯಗಳು[1]);
        _mm_stream_ps((ಭಿನ್ನ *)(dst + 32), ಮೌಲ್ಯಗಳು[2]);
        _mm_stream_ps((ಭಿನ್ನ *)(dst + 48), ಮೌಲ್ಯಗಳು[3]);
        src += 64;
        dst += 64;
    }

    ಯದಿ (len & 63) {
        SDL_memcpy(dst, src, len & 63);
    }
}
#endif // SDL_SSE_INTRINSICS

ಶೂನ್ಯ SDL_BlitCopy(SDL_BlitInfo *info)
{
    bool overlap;
    Uint8 *src, *dst;
    ಪೂರ್ಣಾಙ್ಕ w, h;
    ಪೂರ್ಣಾಙ್ಕ srcskip, dstskip;

    w = info->dst_w * info->dst_fmt->bytes_per_pixel;
    h = info->dst_h;
    src = info->src;
    dst = info->dst;
    srcskip = info->src_pitch;
    dstskip = info->dst_pitch;

    // Properly handle overlapping blits
    ಯದಿ (src < dst) {
        overlap = (dst < (src + h * srcskip));
    } ಅನ್ಯಥಾ {
        overlap = (src < (dst + h * dstskip));
    }
    ಯದಿ (overlap) {
        ಯದಿ (dst < src) {
            ಯಾವತ್ (h--) {
                SDL_memmove(dst, src, w);
                src += srcskip;
                dst += dstskip;
            }
        } ಅನ್ಯಥಾ {
            src += ((h - 1) * srcskip);
            dst += ((h - 1) * dstskip);
            ಯಾವತ್ (h--) {
                SDL_memmove(dst, src, w);
                src -= srcskip;
                dst -= dstskip;
            }
        }
        ಪ್ರತ್ಯಾಗಮ;
    }

#ifdef SDL_SSE_INTRINSICS
    ಯದಿ (SDL_HasSSE() &&
        !((uintptr_t)src & 15) && !(srcskip & 15) &&
        !((uintptr_t)dst & 15) && !(dstskip & 15)) {
        ಯಾವತ್ (h--) {
            SDL_memcpySSE(dst, src, w);
            src += srcskip;
            dst += dstskip;
        }
        ಪ್ರತ್ಯಾಗಮ;
    }
#endif

    ಯಾವತ್ (h--) {
        SDL_memcpy(dst, src, w);
        src += srcskip;
        dst += dstskip;
    }
}
