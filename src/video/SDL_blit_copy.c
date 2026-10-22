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
#ضمن "SDL_internal.h"

#ضمن "SDL_surface_c.h"
#ضمن "SDL_blit_copy.h"

#جيڪڏهن_وصف_ٿيل SDL_SSE_INTRINSICS
// This assumes 16-byte aligned src and dst
ساكن SDL_INLINE فراغ SDL_TARGETING("sse") SDL_memcpySSE(Uint8 *dst, ثابت Uint8 *src, صحيح len)
{
    صحيح i;

    __m128 قدرون[4];
    لكل (i = len / 64; i--;) {
        _mm_prefetch((ثابت حرف *)src, _MM_HINT_NTA);
        قدرون[0] = *(__m128 *)(src + 0);
        قدرون[1] = *(__m128 *)(src + 16);
        قدرون[2] = *(__m128 *)(src + 32);
        قدرون[3] = *(__m128 *)(src + 48);
        mm_وهڪرو_ps((عائم *)(dst + 0), قدرون[0]);
        mm_وهڪرو_ps((عائم *)(dst + 16), قدرون[1]);
        mm_وهڪرو_ps((عائم *)(dst + 32), قدرون[2]);
        mm_وهڪرو_ps((عائم *)(dst + 48), قدرون[3]);
        src += 64;
        dst += 64;
    }

    إذا (len & 63) {
        SDL_memcpy(dst, src, len & 63);
    }
}
#جيڪڏهن_پورو // SDL_SSE_INTRINSICS

فراغ SDL_BlitCopy(SDL_BlitInfo *info)
{
    bool overlap;
    Uint8 *src, *dst;
    صحيح w, h;
    صحيح srcskip, dstskip;

    w = info->dst_w * info->dst_fmt->بائيٽون_في_pixel;
    h = info->dst_h;
    src = info->src;
    dst = info->dst;
    srcskip = info->src_pitch;
    dstskip = info->dst_pitch;

    // Properly handle overlapping blits
    إذا (src < dst) {
        overlap = (dst < (src + h * srcskip));
    } وإلا {
        overlap = (src < (dst + h * dstskip));
    }
    إذا (overlap) {
        إذا (dst < src) {
            طالما (h--) {
                SDL_memmove(dst, src, w);
                src += srcskip;
                dst += dstskip;
            }
        } وإلا {
            src += ((h - 1) * srcskip);
            dst += ((h - 1) * dstskip);
            طالما (h--) {
                SDL_memmove(dst, src, w);
                src -= srcskip;
                dst -= dstskip;
            }
        }
        أرجع;
    }

#جيڪڏهن_وصف_ٿيل SDL_SSE_INTRINSICS
    إذا (SDL_HasSSE() &&
        !((uintptr_t)src & 15) && !(srcskip & 15) &&
        !((uintptr_t)dst & 15) && !(dstskip & 15)) {
        طالما (h--) {
            SDL_memcpySSE(dst, src, w);
            src += srcskip;
            dst += dstskip;
        }
        أرجع;
    }
#جيڪڏهن_پورو

    طالما (h--) {
        SDL_memcpy(dst, src, w);
        src += srcskip;
        dst += dstskip;
    }
}
