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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_SSE_INTRINSICS
// This assumes 16-byte aligned src and dst
ಸ್ಥಿರ SDL_INLINE ಶೂನ್ಯ SDL_TARGETING("sse") SDL_memcpySSE(Uint8 *dst, ಸ್ಥಿರಾಂಕ Uint8 *src, ಪೂರ್ಣಾಂಕ len)
{
    ಪೂರ್ಣಾಂಕ i;

    __m128 ಮೌಲ್ಯಗಳು[4];
    ಗಾಗಿ (i = len / 64; i--;) {
        _mm_prefetch((ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *)src, _MM_HINT_NTA);
        ಮೌಲ್ಯಗಳು[0] = *(__m128 *)(src + 0);
        ಮೌಲ್ಯಗಳು[1] = *(__m128 *)(src + 16);
        ಮೌಲ್ಯಗಳು[2] = *(__m128 *)(src + 32);
        ಮೌಲ್ಯಗಳು[3] = *(__m128 *)(src + 48);
        mm_ಹರಿವು_ps((ದಶಮಾಂಶ *)(dst + 0), ಮೌಲ್ಯಗಳು[0]);
        mm_ಹರಿವು_ps((ದಶಮಾಂಶ *)(dst + 16), ಮೌಲ್ಯಗಳು[1]);
        mm_ಹರಿವು_ps((ದಶಮಾಂಶ *)(dst + 32), ಮೌಲ್ಯಗಳು[2]);
        mm_ಹರಿವು_ps((ದಶಮಾಂಶ *)(dst + 48), ಮೌಲ್ಯಗಳು[3]);
        src += 64;
        dst += 64;
    }

    ಆದರೆ (len & 63) {
        SDL_memcpy(dst, src, len & 63);
    }
}
#ಆದರೆ_ಅಂತ್ಯ // SDL_SSE_INTRINSICS

ಶೂನ್ಯ SDL_BlitCopy(SDL_BlitInfo *info)
{
    bool overlap;
    Uint8 *src, *dst;
    ಪೂರ್ಣಾಂಕ w, h;
    ಪೂರ್ಣಾಂಕ srcskip, dstskip;

    w = info->dst_w * info->dst_fmt->ಬೈಟುಗಳು_ಪ್ರತಿ_pixel;
    h = info->dst_h;
    src = info->src;
    dst = info->dst;
    srcskip = info->src_pitch;
    dstskip = info->dst_pitch;

    // Properly handle overlapping blits
    ಆದರೆ (src < dst) {
        overlap = (dst < (src + h * srcskip));
    } ಇಲ್ಲದಿದ್ದರೆ {
        overlap = (src < (dst + h * dstskip));
    }
    ಆದರೆ (overlap) {
        ಆದರೆ (dst < src) {
            ಆಗ (h--) {
                SDL_memmove(dst, src, w);
                src += srcskip;
                dst += dstskip;
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            src += ((h - 1) * srcskip);
            dst += ((h - 1) * dstskip);
            ಆಗ (h--) {
                SDL_memmove(dst, src, w);
                src -= srcskip;
                dst -= dstskip;
            }
        }
        ಹಿಂತಿರುಗಿ;
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_SSE_INTRINSICS
    ಆದರೆ (SDL_HasSSE() &&
        !((uintptr_t)src & 15) && !(srcskip & 15) &&
        !((uintptr_t)dst & 15) && !(dstskip & 15)) {
        ಆಗ (h--) {
            SDL_memcpySSE(dst, src, w);
            src += srcskip;
            dst += dstskip;
        }
        ಹಿಂತಿರುಗಿ;
    }
#ಆದರೆ_ಅಂತ್ಯ

    ಆಗ (h--) {
        SDL_memcpy(dst, src, w);
        src += srcskip;
        dst += dstskip;
    }
}
