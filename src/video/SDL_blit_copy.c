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
#അന്തര്ഭാവ "SDL_internal.h"

#അന്തര്ഭാവ "SDL_surface_c.h"
#അന്തര്ഭാവ "SDL_blit_copy.h"

#ifdef SDL_SSE_INTRINSICS
// This assumes 16-byte aligned src and dst
സ്ഥിതം SDL_INLINE ശൂന്യം SDL_TARGETING("sse") SDL_memcpySSE(Uint8 *dst, സ്ഥിരം Uint8 *src, പൂർണ്ണസംഖ്യ len)
{
    പൂർണ്ണസംഖ്യ i;

    __m128 മൂല്യങ്ങൾ[4];
    വേണ്ടി (i = len / 64; i--;) {
        _mm_prefetch((സ്ഥിരം അക്ഷരം *)src, _MM_HINT_NTA);
        മൂല്യങ്ങൾ[0] = *(__m128 *)(src + 0);
        മൂല്യങ്ങൾ[1] = *(__m128 *)(src + 16);
        മൂല്യങ്ങൾ[2] = *(__m128 *)(src + 32);
        മൂല്യങ്ങൾ[3] = *(__m128 *)(src + 48);
        _mm_stream_ps((ദശാംശം *)(dst + 0), മൂല്യങ്ങൾ[0]);
        _mm_stream_ps((ദശാംശം *)(dst + 16), മൂല്യങ്ങൾ[1]);
        _mm_stream_ps((ദശാംശം *)(dst + 32), മൂല്യങ്ങൾ[2]);
        _mm_stream_ps((ദശാംശം *)(dst + 48), മൂല്യങ്ങൾ[3]);
        src += 64;
        dst += 64;
    }

    എങ്കിൽ (len & 63) {
        SDL_memcpy(dst, src, len & 63);
    }
}
#endif // SDL_SSE_INTRINSICS

ശൂന്യം SDL_BlitCopy(SDL_BlitInfo *info)
{
    bool overlap;
    Uint8 *src, *dst;
    പൂർണ്ണസംഖ്യ w, h;
    പൂർണ്ണസംഖ്യ srcskip, dstskip;

    w = info->dst_w * info->dst_fmt->bytes_per_pixel;
    h = info->dst_h;
    src = info->src;
    dst = info->dst;
    srcskip = info->src_pitch;
    dstskip = info->dst_pitch;

    // Properly handle overlapping blits
    എങ്കിൽ (src < dst) {
        overlap = (dst < (src + h * srcskip));
    } അല്ലെങ്കിൽ {
        overlap = (src < (dst + h * dstskip));
    }
    എങ്കിൽ (overlap) {
        എങ്കിൽ (dst < src) {
            ആകുമ്പോൾ (h--) {
                SDL_memmove(dst, src, w);
                src += srcskip;
                dst += dstskip;
            }
        } അല്ലെങ്കിൽ {
            src += ((h - 1) * srcskip);
            dst += ((h - 1) * dstskip);
            ആകുമ്പോൾ (h--) {
                SDL_memmove(dst, src, w);
                src -= srcskip;
                dst -= dstskip;
            }
        }
        തിരികെ;
    }

#ifdef SDL_SSE_INTRINSICS
    എങ്കിൽ (SDL_HasSSE() &&
        !((uintptr_t)src & 15) && !(srcskip & 15) &&
        !((uintptr_t)dst & 15) && !(dstskip & 15)) {
        ആകുമ്പോൾ (h--) {
            SDL_memcpySSE(dst, src, w);
            src += srcskip;
            dst += dstskip;
        }
        തിരികെ;
    }
#endif

    ആകുമ്പോൾ (h--) {
        SDL_memcpy(dst, src, w);
        src += srcskip;
        dst += dstskip;
    }
}
