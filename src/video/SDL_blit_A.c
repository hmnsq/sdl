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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_HAVE_BLIT_A

#అన్తర్భావ "SDL_pixels_c.h"
#అన్తర్భావ "SDL_surface_c.h"

#నిర్వచితమైతే SDL_SVE2_INTRINSICS
#అన్తర్భావ "./arm/SDL_sve2_blit_A.h"
#అయితే_ముగింపు

// Functions to perform alpha blended blitting

// N->1 blending with per-surface alpha
స్థిర శూన్య BlitNto1SurfaceAlpha(SDL_BlitInfo *info)
{
    పూర్ణాంకం వెడల్పు = info->dst_w;
    పూర్ణాంకం ఎత్తు = info->dst_h;
    Uint8 *src = info->src;
    పూర్ణాంకం srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    పూర్ణాంకం dstskip = info->dst_skip;
    Uint8 *palmap = info->పట్టిక;
    స్థిరరాశి SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    స్థిరరాశి SDL_Color *dstpal = info->dst_pal->colors;
    పూర్ణాంకం srcbpp = srcfmt->బైట్లు_చొప్పున_pixel;
    Uint32 Pixel;
    గుర్తులేని sR, sG, sB;
    గుర్తులేని dR, dG, dB;
    స్థిరరాశి గుర్తులేని A = info->a;

    అయితే (ఎత్తు--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP(
        {
        DISEMBLE_RGB(src, srcbpp, srcfmt, Pixel, sR, sG, sB);
        dR = dstpal[*dst].r;
        dG = dstpal[*dst].g;
        dB = dstpal[*dst].b;
        ALPHA_BLEND_RGB(sR, sG, sB, A, dR, dG, dB);
        dR &= 0xff;
        dG &= 0xff;
        dB &= 0xff;
        // Pack RGB into 8bit pixel
        ఒకవేళ ( palmap == ఖాళీ ) {
            *dst = (Uint8)(((dR>>5)<<(3+2))|((dG>>5)<<(2))|((dB>>6)<<(0)));
        } లేకపోతే {
            *dst = palmap[((dR>>5)<<(3+2))|((dG>>5)<<(2))|((dB>>6)<<(0))];
        }
        dst++;
        src += srcbpp;
        },
        వెడల్పు);
        /* *INDENT-ON* */ // clang-format on
        src += srcskip;
        dst += dstskip;
    }
}

// N->1 blending with pixel alpha
స్థిర శూన్య BlitNto1PixelAlpha(SDL_BlitInfo *info)
{
    పూర్ణాంకం వెడల్పు = info->dst_w;
    పూర్ణాంకం ఎత్తు = info->dst_h;
    Uint8 *src = info->src;
    పూర్ణాంకం srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    పూర్ణాంకం dstskip = info->dst_skip;
    Uint8 *palmap = info->పట్టిక;
    స్థిరరాశి SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    స్థిరరాశి SDL_Color *dstpal = info->dst_pal->colors;
    పూర్ణాంకం srcbpp = srcfmt->బైట్లు_చొప్పున_pixel;
    Uint32 Pixel;
    గుర్తులేని sR, sG, sB, sA;
    గుర్తులేని dR, dG, dB;

    అయితే (ఎత్తు--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP(
        {
        DISEMBLE_RGBA(src,srcbpp,srcfmt,Pixel,sR,sG,sB,sA);
        dR = dstpal[*dst].r;
        dG = dstpal[*dst].g;
        dB = dstpal[*dst].b;
        ALPHA_BLEND_RGB(sR, sG, sB, sA, dR, dG, dB);
        dR &= 0xff;
        dG &= 0xff;
        dB &= 0xff;
        // Pack RGB into 8bit pixel
        ఒకవేళ ( palmap == ఖాళీ ) {
            *dst = (Uint8)(((dR>>5)<<(3+2))|((dG>>5)<<(2))|((dB>>6)<<(0)));
        } లేకపోతే {
            *dst = palmap[((dR>>5)<<(3+2))|((dG>>5)<<(2))|((dB>>6)<<(0))];
        }
        dst++;
        src += srcbpp;
        },
        వెడల్పు);
        /* *INDENT-ON* */ // clang-format on
        src += srcskip;
        dst += dstskip;
    }
}

// colorkeyed N->1 blending with per-surface alpha
స్థిర శూన్య Blit_Nto1_Surface_Alpha_కీలకం(SDL_BlitInfo *info)
{
    పూర్ణాంకం వెడల్పు = info->dst_w;
    పూర్ణాంకం ఎత్తు = info->dst_h;
    Uint8 *src = info->src;
    పూర్ణాంకం srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    పూర్ణాంకం dstskip = info->dst_skip;
    Uint8 *palmap = info->పట్టిక;
    స్థిరరాశి SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    స్థిరరాశి SDL_Color *dstpal = info->dst_pal->colors;
    పూర్ణాంకం srcbpp = srcfmt->బైట్లు_చొప్పున_pixel;
    Uint32 ckey = info->colorkey;
    Uint32 Pixel;
    గుర్తులేని sR, sG, sB;
    గుర్తులేని dR, dG, dB;
    స్థిరరాశి గుర్తులేని A = info->a;

    అయితే (ఎత్తు--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP(
        {
        DISEMBLE_RGB(src, srcbpp, srcfmt, Pixel, sR, sG, sB);
        ఒకవేళ ( Pixel != ckey ) {
            dR = dstpal[*dst].r;
            dG = dstpal[*dst].g;
            dB = dstpal[*dst].b;
            ALPHA_BLEND_RGB(sR, sG, sB, A, dR, dG, dB);
            dR &= 0xff;
            dG &= 0xff;
            dB &= 0xff;
            // Pack RGB into 8bit pixel
            ఒకవేళ ( palmap == ఖాళీ ) {
                *dst = (Uint8)(((dR>>5)<<(3+2))|((dG>>5)<<(2))|((dB>>6)<<(0)));
            } లేకపోతే {
                *dst = palmap[((dR>>5)<<(3+2))|((dG>>5)<<(2))|((dB>>6)<<(0))];
            }
        }
        dst++;
        src += srcbpp;
        },
        వెడల్పు);
        /* *INDENT-ON* */ // clang-format on
        src += srcskip;
        dst += dstskip;
    }
}

#నిర్వచితమైతే SDL_SSE2_INTRINSICS

స్థిర శూన్య SDL_TARGETING("sse2") Blit888to888SurfaceAlphaSSE2(SDL_BlitInfo *info)
{
    పూర్ణాంకం వెడల్పు = info->dst_w;
    పూర్ణాంకం ఎత్తు = info->dst_h;
    Uint8 *src = info->src;
    పూర్ణాంకం srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    పూర్ణాంకం dstskip = info->dst_skip;
    Uint8 alpha = info->a;

    స్థిరరాశి __m128i alpha_fill_ముసుగు = _mm_set1_epi32((పూర్ణాంకం)0xff000000);
    స్థిరరాశి __m128i srcA = _mm_set1_epi16(alpha);

    అయితే (ఎత్తు--) {
        పూర్ణాంకం i = 0;

        కొరకు (; i + 4 <= వెడల్పు; i += 4) {
            // Load 4 src pixels
            __m128i src128 = _mm_loadu_si128((__m128i *)src);

            // Load 4 dst pixels
            __m128i dst128 = _mm_loadu_si128((__m128i *)dst);

            __m128i src_lo = _mm_unpacklo_epi8(src128, _mm_setzero_si128());
            __m128i src_hi = _mm_unpackhi_epi8(src128, _mm_setzero_si128());

            __m128i dst_lo = _mm_unpacklo_epi8(dst128, _mm_setzero_si128());
            __m128i dst_hi = _mm_unpackhi_epi8(dst128, _mm_setzero_si128());

            // dst = ((src - dst) * srcA) + ((dst << 8) - dst)
            dst_lo = mm_కూడు_epi16(_mm_mullo_epi16(_mm_sub_epi16(src_lo, dst_lo), srcA),
                                      _mm_sub_epi16(_mm_slli_epi16(dst_lo, 8), dst_lo));
            dst_hi = mm_కూడు_epi16(_mm_mullo_epi16(_mm_sub_epi16(src_hi, dst_hi), srcA),
                                      _mm_sub_epi16(_mm_slli_epi16(dst_hi, 8), dst_hi));

            // dst += 0x1U (use 0x80 to round instead of floor)
            dst_lo = mm_కూడు_epi16(dst_lo, _mm_set1_epi16(1));
            dst_hi = mm_కూడు_epi16(dst_hi, _mm_set1_epi16(1));

            // dst = (dst + (dst >> 8)) >> 8
            dst_lo = _mm_srli_epi16(mm_కూడు_epi16(dst_lo, _mm_srli_epi16(dst_lo, 8)), 8);
            dst_hi = _mm_srli_epi16(mm_కూడు_epi16(dst_hi, _mm_srli_epi16(dst_hi, 8)), 8);

            dst128 = _mm_packus_epi16(dst_lo, dst_hi);

            // Set the alpha channels of dst to 255
            dst128 = _mm_or_si128(dst128, alpha_fill_ముసుగు);

            _mm_storeu_si128((__m128i *)dst, dst128);

            src += 16;
            dst += 16;
        }

        కొరకు (; i < వెడల్పు; ++i) {
            Uint32 src32 = *(Uint32 *)src;
            Uint32 dst32 = *(Uint32 *)dst;

            గుణకం_BLEND_8888(src32, dst32, alpha);

            *dst = dst32 | 0xff000000;

            src += 4;
            dst += 4;
        }

        src += srcskip;
        dst += dstskip;
    }
}

#అయితే_ముగింపు

#నిర్వచితమైతే SDL_LSX_INTRINSICS

స్థిర శూన్య SDL_TARGETING("lsx") Blit8888to8888PixelAlphaSwizzleLSX(SDL_BlitInfo *info)
{
    పూర్ణాంకం వెడల్పు = info->dst_w;
    పూర్ణాంకం ఎత్తు = info->dst_h;
    Uint8 *src = info->src;
    పూర్ణాంకం srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    పూర్ణాంకం dstskip = info->dst_skip;
    స్థిరరాశి SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    స్థిరరాశి SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    bool fill_alpha = !dstfmt->Amask;
    Uint32 dstAmask, dstAshift;
    స్థిరరాశి Uint8 offsets[] = {0, 0, 0, 0, 4, 4, 4, 4, 8, 8, 8, 8, 12, 12, 12, 12};

    SDL_Get8888_Alpha_ముసుగు_And_జరుపు(dstfmt, &dstAmask, &dstAshift);

    స్థిరరాశి __m128i const_0xff00 = __lsx_vreplgr2vr_h(0xff00);
    స్థిరరాశి __m128i const_128 = __lsx_vreplgr2vr_b((Uint8)128);
    స్థిరరాశి __m128i const_32641 = __lsx_vreplgr2vr_h(32641);
    స్థిరరాశి __m128i const_257 = __lsx_vreplgr2vr_h(257);

    // The byte offsets for the start of each pixel
    స్థిరరాశి __m128i ముసుగు_offsets = __lsx_vld(offsets, 0);

    స్థిరరాశి __m128i convert_ముసుగు = __lsx_vadd_w(
        __lsx_vreplgr2vr_w(
            ((srcfmt->Rshift >> 3) << dstfmt->Rshift) |
            ((srcfmt->Gshift >> 3) << dstfmt->Gshift) |
            ((srcfmt->Bshift >> 3) << dstfmt->Bshift)),
        ముసుగు_offsets);

    స్థిరరాశి __m128i alpha_splat_ముసుగు = __lsx_vadd_b(__lsx_vreplgr2vr_b(srcfmt->Ashift >> 3), ముసుగు_offsets);
    స్థిరరాశి __m128i alpha_fill_ముసుగు = __lsx_vreplgr2vr_w((పూర్ణాంకం)dstAmask);

    అయితే (ఎత్తు--) {
        పూర్ణాంకం i = 0;

        కొరకు (; i + 4 <= వెడల్పు; i += 4) {
            __m128i src128 = __lsx_vld(src, 0);
            __m128i dst128 = __lsx_vld(dst, 0);

            __m128i srcA = __lsx_vshuf_b(src128, src128, alpha_splat_ముసుగు);
            src128 = __lsx_vshuf_b(src128, src128, convert_ముసుగు);

            src128 = __lsx_vor_v(src128, alpha_fill_ముసుగు);

            __m128i srca_lo = __lsx_vilvl_b(srcA, srcA);
            __m128i srca_hi = __lsx_vilvh_b(srcA, srcA);

            srca_lo = __lsx_vxor_v(srca_lo, const_0xff00);
            srca_hi = __lsx_vxor_v(srca_hi, const_0xff00);

            src128 = __lsx_vsub_b(src128, const_128);
            dst128 = __lsx_vsub_b(dst128, const_128);

            __m128i tmp = __lsx_vilvl_b(dst128, src128);
            __m128i dst_lo = __lsx_vsadd_h(__lsx_vmulwev_h_bu_b(srca_lo, tmp), __lsx_vmulwod_h_bu_b(srca_lo, tmp));
            tmp = __lsx_vilvh_b(dst128, src128);
            __m128i dst_hi = __lsx_vsadd_h(__lsx_vmulwev_h_bu_b(srca_hi, tmp), __lsx_vmulwod_h_bu_b(srca_hi, tmp));

            dst_lo = __lsx_vadd_h(dst_lo, const_32641);
            dst_hi = __lsx_vadd_h(dst_hi, const_32641);

            dst_lo = __lsx_vmuh_hu(dst_lo, const_257);
            dst_hi = __lsx_vmuh_hu(dst_hi, const_257);

            dst128 = __lsx_vssrarni_bu_h(dst_hi, dst_lo, 0);
            ఒకవేళ (fill_alpha) {
                dst128 = __lsx_vor_v(dst128, alpha_fill_ముసుగు);
            }
            __lsx_vst(dst128, dst, 0);

            src += 16;
            dst += 16;
        }

        కొరకు (; i < వెడల్పు; ++i) {
            Uint32 src32 = *(Uint32 *)src;
            Uint32 dst32 = *(Uint32 *)dst;
            ALPHA_BLEND_SWIZZLE_8888(src32, dst32, srcfmt, dstfmt);
            ఒకవేళ (fill_alpha) {
                dst32 |= dstAmask;
            }
            *(Uint32 *)dst = dst32;
            src += 4;
            dst += 4;
        }

        src += srcskip;
        dst += dstskip;
    }
}

#అయితే_ముగింపు

// fast RGB888->(A)RGB888 blending with surface alpha=128 special case
స్థిర శూన్య BlitRGBtoRGBSurfaceAlpha128(SDL_BlitInfo *info)
{
    పూర్ణాంకం వెడల్పు = info->dst_w;
    పూర్ణాంకం ఎత్తు = info->dst_h;
    Uint32 *srcp = (Uint32 *)info->src;
    పూర్ణాంకం srcskip = info->src_skip >> 2;
    Uint32 *dstp = (Uint32 *)info->dst;
    పూర్ణాంకం dstskip = info->dst_skip >> 2;

    అయితే (ఎత్తు--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP({
            Uint32 s = *srcp++;
            Uint32 d = *dstp;
            *dstp++ = ((((s & 0x00fefefe) + (d & 0x00fefefe)) >> 1)
                   + (s & d & 0x00010101)) | 0xff000000;
        }, వెడల్పు);
        /* *INDENT-ON* */ // clang-format on
        srcp += srcskip;
        dstp += dstskip;
    }
}

// fast RGB888->(A)RGB888 blending with surface alpha
స్థిర శూన్య BlitRGBtoRGBSurfaceAlpha(SDL_BlitInfo *info)
{
    గుర్తులేని alpha = info->a;
    ఒకవేళ (alpha == 128) {
        BlitRGBtoRGBSurfaceAlpha128(info);
    } లేకపోతే {
        పూర్ణాంకం వెడల్పు = info->dst_w;
        పూర్ణాంకం ఎత్తు = info->dst_h;
        Uint32 *srcp = (Uint32 *)info->src;
        పూర్ణాంకం srcskip = info->src_skip >> 2;
        Uint32 *dstp = (Uint32 *)info->dst;
        పూర్ణాంకం dstskip = info->dst_skip >> 2;
        Uint32 s;
        Uint32 d;

        అయితే (ఎత్తు--) {
            /* *INDENT-OFF* */ // clang-format off
            DUFFS_LOOP({
                s = *srcp;
                d = *dstp;

                గుణకం_BLEND_8888(s, d, alpha);

                *dstp = d | 0xff000000;
                ++srcp;
                ++dstp;
            }, వెడల్పు);
            /* *INDENT-ON* */ // clang-format on
            srcp += srcskip;
            dstp += dstskip;
        }
    }
}

// 16bpp special case for per-surface alpha=50%: blend 2 pixels in parallel

// blend a single 16 bit pixel at 50%
#నిర్వచించు BLEND16_50(d, s, ముసుగు) \
    ((((s & ముసుగు) + (d & ముసుగు)) >> 1) + (s & d & (~ముసుగు & 0xffff)))

// blend two 16 bit pixels at 50%
#నిర్వచించు BLEND2x16_50(d, s, ముసుగు) \
    (((s & (ముసుగు | ముసుగు << 16)) >> 1) + ((d & (ముసుగు | ముసుగు << 16)) >> 1) + (s & d & (~(ముసుగు | ముసుగు << 16))))

స్థిర శూన్య Blit16to16SurfaceAlpha128(SDL_BlitInfo *info, Uint16 ముసుగు)
{
    పూర్ణాంకం వెడల్పు = info->dst_w;
    పూర్ణాంకం ఎత్తు = info->dst_h;
    Uint16 *srcp = (Uint16 *)info->src;
    పూర్ణాంకం srcskip = info->src_skip >> 1;
    Uint16 *dstp = (Uint16 *)info->dst;
    పూర్ణాంకం dstskip = info->dst_skip >> 1;

    అయితే (ఎత్తు--) {
        ఒకవేళ (((uintptr_t)srcp ^ (uintptr_t)dstp) & 2) {
            /*
             * Source and destination not aligned, pipeline it.
             * This is mostly a win for big blits but no loss for
             * small ones
             */
            Uint32 prev_sw;
            పూర్ణాంకం w = వెడల్పు;

            // handle odd destination
            ఒకవేళ ((uintptr_t)dstp & 2) {
                Uint16 d = *dstp, s = *srcp;
                *dstp = BLEND16_50(d, s, ముసుగు);
                dstp++;
                srcp++;
                w--;
            }
            srcp++; // srcp is now 32-bit aligned

            // bootstrap pipeline with first halfword
            prev_sw = ((Uint32 *)srcp)[-1];

            అయితే (w > 1) {
                Uint32 sw, dw, s;
                sw = *(Uint32 *)srcp;
                dw = *(Uint32 *)dstp;
#ఒకవేళ SDL_BYTEORDER == SDL_BIG_ENDIAN
                s = (prev_sw << 16) + (sw >> 16);
#లేకపోతే
                s = (prev_sw >> 16) + (sw << 16);
#అయితే_ముగింపు
                prev_sw = sw;
                *(Uint32 *)dstp = BLEND2x16_50(dw, s, ముసుగు);
                dstp += 2;
                srcp += 2;
                w -= 2;
            }

            // final pixel if any
            ఒకవేళ (w) {
                Uint16 d = *dstp, s;
#ఒకవేళ SDL_BYTEORDER == SDL_BIG_ENDIAN
                s = (Uint16)prev_sw;
#లేకపోతే
                s = (Uint16)(prev_sw >> 16);
#అయితే_ముగింపు
                *dstp = BLEND16_50(d, s, ముసుగు);
                srcp++;
                dstp++;
            }
            srcp += srcskip - 1;
            dstp += dstskip;
        } లేకపోతే {
            // source and destination are aligned
            పూర్ణాంకం w = వెడల్పు;

            // first odd pixel?
            ఒకవేళ ((uintptr_t)srcp & 2) {
                Uint16 d = *dstp, s = *srcp;
                *dstp = BLEND16_50(d, s, ముసుగు);
                srcp++;
                dstp++;
                w--;
            }
            // srcp and dstp are now 32-bit aligned

            అయితే (w > 1) {
                Uint32 sw = *(Uint32 *)srcp;
                Uint32 dw = *(Uint32 *)dstp;
                *(Uint32 *)dstp = BLEND2x16_50(dw, sw, ముసుగు);
                srcp += 2;
                dstp += 2;
                w -= 2;
            }

            // last odd pixel?
            ఒకవేళ (w) {
                Uint16 d = *dstp, s = *srcp;
                *dstp = BLEND16_50(d, s, ముసుగు);
                srcp++;
                dstp++;
            }
            srcp += srcskip;
            dstp += dstskip;
        }
    }
}

#నిర్వచితమైతే SDL_MMX_INTRINSICS

// fast RGB565->RGB565 blending with surface alpha
స్థిర శూన్య SDL_TARGETING("mmx") Blit565to565SurfaceAlphaMMX(SDL_BlitInfo *info)
{
    గుర్తులేని alpha = info->a;
    ఒకవేళ (alpha == 128) {
        Blit16to16SurfaceAlpha128(info, 0xf7de);
    } లేకపోతే {
        పూర్ణాంకం వెడల్పు = info->dst_w;
        పూర్ణాంకం ఎత్తు = info->dst_h;
        Uint16 *srcp = (Uint16 *)info->src;
        పూర్ణాంకం srcskip = info->src_skip >> 1;
        Uint16 *dstp = (Uint16 *)info->dst;
        పూర్ణాంకం dstskip = info->dst_skip >> 1;
        Uint32 s, d;

#నిర్వచితమైతే USE_DUFFS_LOOP
        __m64 src1, dst1, src2, dst2, gmask, bmask, mm_res, mm_alpha;

        alpha &= ~(1 + 2 + 4);             // cut alpha to get the exact same behaviour
        mm_alpha = mm_సమితి_pi32(0, alpha); // 0000000A -> mm_alpha
        alpha >>= 3;                       // downscale alpha to 5 bits

        mm_alpha = _mm_unpacklo_pi16(mm_alpha, mm_alpha); // 00000A0A -> mm_alpha
        mm_alpha = _mm_unpacklo_pi32(mm_alpha, mm_alpha); // 0A0A0A0A -> mm_alpha
        /* position alpha to allow for mullo and mulhi on diff channels
           to reduce the number of operations */
        mm_alpha = _mm_slli_si64(mm_alpha, 3);

        // Setup the 565 color channel masks
        gmask = mm_సమితి_pi32(0x07E007E0, 0x07E007E0); // MASKGREEN -> gmask
        bmask = mm_సమితి_pi32(0x001F001F, 0x001F001F); // MASKBLUE -> bmask
#అయితే_ముగింపు

        అయితే (ఎత్తు--) {
            /* *INDENT-OFF* */ // clang-format off
            DUFFS_LOOP_124(
            {
                s = *srcp++;
                d = *dstp;
                /*
                 * shift out the middle component (green) to
                 * the high 16 bits, and process all three RGB
                 * components at the same time.
                 */
                s = (s | s << 16) & 0x07e0f81f;
                d = (d | d << 16) & 0x07e0f81f;
                d += (s - d) * alpha >> 5;
                d &= 0x07e0f81f;
                *dstp++ = (Uint16)(d | d >> 16);
            },{
                s = *srcp++;
                d = *dstp;
                /*
                 * shift out the middle component (green) to
                 * the high 16 bits, and process all three RGB
                 * components at the same time.
                 */
                s = (s | s << 16) & 0x07e0f81f;
                d = (d | d << 16) & 0x07e0f81f;
                d += (s - d) * alpha >> 5;
                d &= 0x07e0f81f;
                *dstp++ = (Uint16)(d | d >> 16);
                s = *srcp++;
                d = *dstp;
                /*
                 * shift out the middle component (green) to
                 * the high 16 bits, and process all three RGB
                 * components at the same time.
                 */
                s = (s | s << 16) & 0x07e0f81f;
                d = (d | d << 16) & 0x07e0f81f;
                d += (s - d) * alpha >> 5;
                d &= 0x07e0f81f;
                *dstp++ = (Uint16)(d | d >> 16);
            },{
                src1 = *(__m64 *)srcp; // 4 src pixels -> src1
                dst1 = *(__m64 *)dstp; // 4 dst pixels -> dst1

                // red
                src2 = src1;
                src2 = _mm_srli_pi16(src2, 11); // src2 >> 11 -> src2 [000r 000r 000r 000r]

                dst2 = dst1;
                dst2 = _mm_srli_pi16(dst2, 11); // dst2 >> 11 -> dst2 [000r 000r 000r 000r]

                // blend
                src2 = _mm_sub_pi16(src2, dst2);// src - dst -> src2
                src2 = _mm_mullo_pi16(src2, mm_alpha); /* src2 * alpha -> src2 */
                src2 = _mm_srli_pi16(src2, 11); // src2 >> 11 -> src2
                dst2 = mm_కూడు_pi16(src2, dst2); // src2 + dst2 -> dst2
                dst2 = _mm_slli_pi16(dst2, 11); // dst2 << 11 -> dst2

                mm_res = dst2; // RED -> mm_res

                // green -- process the bits in place
                src2 = src1;
                src2 = _mm_and_si64(src2, gmask); // src & MASKGREEN -> src2

                dst2 = dst1;
                dst2 = _mm_and_si64(dst2, gmask); // dst & MASKGREEN -> dst2

                // blend
                src2 = _mm_sub_pi16(src2, dst2);// src - dst -> src2
                src2 = _mm_mulhi_pi16(src2, mm_alpha); /* src2 * alpha -> src2 */
                src2 = _mm_slli_pi16(src2, 5); // src2 << 5 -> src2
                dst2 = mm_కూడు_pi16(src2, dst2); // src2 + dst2 -> dst2

                mm_res = _mm_or_si64(mm_res, dst2); // RED | GREEN -> mm_res

                // blue
                src2 = src1;
                src2 = _mm_and_si64(src2, bmask); // src & MASKBLUE -> src2[000b 000b 000b 000b]

                dst2 = dst1;
                dst2 = _mm_and_si64(dst2, bmask); // dst & MASKBLUE -> dst2[000b 000b 000b 000b]

                // blend
                src2 = _mm_sub_pi16(src2, dst2);// src - dst -> src2
                src2 = _mm_mullo_pi16(src2, mm_alpha); /* src2 * alpha -> src2 */
                src2 = _mm_srli_pi16(src2, 11); // src2 >> 11 -> src2
                dst2 = mm_కూడు_pi16(src2, dst2); // src2 + dst2 -> dst2
                dst2 = _mm_and_si64(dst2, bmask); // dst2 & MASKBLUE -> dst2

                mm_res = _mm_or_si64(mm_res, dst2); // RED | GREEN | BLUE -> mm_res

                *(__m64 *)dstp = mm_res; // mm_res -> 4 dst pixels

                srcp += 4;
                dstp += 4;
            }, వెడల్పు);
            /* *INDENT-ON* */ // clang-format on
            srcp += srcskip;
            dstp += dstskip;
        }
        mm_ఖాళీలు();
    }
}

// fast RGB555->RGB555 blending with surface alpha
స్థిర శూన్య SDL_TARGETING("mmx") Blit555to555SurfaceAlphaMMX(SDL_BlitInfo *info)
{
    గుర్తులేని alpha = info->a;
    ఒకవేళ (alpha == 128) {
        Blit16to16SurfaceAlpha128(info, 0xfbde);
    } లేకపోతే {
        పూర్ణాంకం వెడల్పు = info->dst_w;
        పూర్ణాంకం ఎత్తు = info->dst_h;
        Uint16 *srcp = (Uint16 *)info->src;
        పూర్ణాంకం srcskip = info->src_skip >> 1;
        Uint16 *dstp = (Uint16 *)info->dst;
        పూర్ణాంకం dstskip = info->dst_skip >> 1;
        Uint32 s, d;

#నిర్వచితమైతే USE_DUFFS_LOOP
        __m64 src1, dst1, src2, dst2, rmask, gmask, bmask, mm_res, mm_alpha;

        alpha &= ~(1 + 2 + 4);             // cut alpha to get the exact same behaviour
        mm_alpha = mm_సమితి_pi32(0, alpha); // 0000000A -> mm_alpha
        alpha >>= 3;                       // downscale alpha to 5 bits

        mm_alpha = _mm_unpacklo_pi16(mm_alpha, mm_alpha); // 00000A0A -> mm_alpha
        mm_alpha = _mm_unpacklo_pi32(mm_alpha, mm_alpha); // 0A0A0A0A -> mm_alpha
        /* position alpha to allow for mullo and mulhi on diff channels
           to reduce the number of operations */
        mm_alpha = _mm_slli_si64(mm_alpha, 3);

        // Setup the 555 color channel masks
        rmask = mm_సమితి_pi32(0x7C007C00, 0x7C007C00); // MASKRED -> rmask
        gmask = mm_సమితి_pi32(0x03E003E0, 0x03E003E0); // MASKGREEN -> gmask
        bmask = mm_సమితి_pi32(0x001F001F, 0x001F001F); // MASKBLUE -> bmask
#అయితే_ముగింపు
        అయితే (ఎత్తు--) {
            /* *INDENT-OFF* */ // clang-format off
            DUFFS_LOOP_124(
            {
                s = *srcp++;
                d = *dstp;
                /*
                 * shift out the middle component (green) to
                 * the high 16 bits, and process all three RGB
                 * components at the same time.
                 */
                s = (s | s << 16) & 0x03e07c1f;
                d = (d | d << 16) & 0x03e07c1f;
                d += (s - d) * alpha >> 5;
                d &= 0x03e07c1f;
                *dstp++ = (Uint16)(d | d >> 16);
            },{
                s = *srcp++;
                d = *dstp;
                /*
                 * shift out the middle component (green) to
                 * the high 16 bits, and process all three RGB
                 * components at the same time.
                 */
                s = (s | s << 16) & 0x03e07c1f;
                d = (d | d << 16) & 0x03e07c1f;
                d += (s - d) * alpha >> 5;
                d &= 0x03e07c1f;
                *dstp++ = (Uint16)(d | d >> 16);
                    s = *srcp++;
                d = *dstp;
                /*
                 * shift out the middle component (green) to
                 * the high 16 bits, and process all three RGB
                 * components at the same time.
                 */
                s = (s | s << 16) & 0x03e07c1f;
                d = (d | d << 16) & 0x03e07c1f;
                d += (s - d) * alpha >> 5;
                d &= 0x03e07c1f;
                *dstp++ = (Uint16)(d | d >> 16);
            },{
                src1 = *(__m64 *)srcp; // 4 src pixels -> src1
                dst1 = *(__m64 *)dstp; // 4 dst pixels -> dst1

                // red -- process the bits in place
                src2 = src1;
                src2 = _mm_and_si64(src2, rmask); // src & MASKRED -> src2

                dst2 = dst1;
                dst2 = _mm_and_si64(dst2, rmask); // dst & MASKRED -> dst2

                // blend
                src2 = _mm_sub_pi16(src2, dst2);// src - dst -> src2
                src2 = _mm_mulhi_pi16(src2, mm_alpha); /* src2 * alpha -> src2 */
                src2 = _mm_slli_pi16(src2, 5); // src2 << 5 -> src2
                dst2 = mm_కూడు_pi16(src2, dst2); // src2 + dst2 -> dst2
                dst2 = _mm_and_si64(dst2, rmask); // dst2 & MASKRED -> dst2

                mm_res = dst2; // RED -> mm_res

                // green -- process the bits in place
                src2 = src1;
                src2 = _mm_and_si64(src2, gmask); // src & MASKGREEN -> src2

                dst2 = dst1;
                dst2 = _mm_and_si64(dst2, gmask); // dst & MASKGREEN -> dst2

                // blend
                src2 = _mm_sub_pi16(src2, dst2);// src - dst -> src2
                src2 = _mm_mulhi_pi16(src2, mm_alpha); /* src2 * alpha -> src2 */
                src2 = _mm_slli_pi16(src2, 5); // src2 << 5 -> src2
                dst2 = mm_కూడు_pi16(src2, dst2); // src2 + dst2 -> dst2

                mm_res = _mm_or_si64(mm_res, dst2); // RED | GREEN -> mm_res

                // blue
                src2 = src1; // src -> src2
                src2 = _mm_and_si64(src2, bmask); // src & MASKBLUE -> src2[000b 000b 000b 000b]

                dst2 = dst1; // dst -> dst2
                dst2 = _mm_and_si64(dst2, bmask); // dst & MASKBLUE -> dst2[000b 000b 000b 000b]

                // blend
                src2 = _mm_sub_pi16(src2, dst2);// src - dst -> src2
                src2 = _mm_mullo_pi16(src2, mm_alpha); /* src2 * alpha -> src2 */
                src2 = _mm_srli_pi16(src2, 11); // src2 >> 11 -> src2
                dst2 = mm_కూడు_pi16(src2, dst2); // src2 + dst2 -> dst2
                dst2 = _mm_and_si64(dst2, bmask); // dst2 & MASKBLUE -> dst2

                mm_res = _mm_or_si64(mm_res, dst2); // RED | GREEN | BLUE -> mm_res

                *(__m64 *)dstp = mm_res; // mm_res -> 4 dst pixels

                srcp += 4;
                dstp += 4;
            }, వెడల్పు);
            /* *INDENT-ON* */ // clang-format on
            srcp += srcskip;
            dstp += dstskip;
        }
        mm_ఖాళీలు();
    }
}

#అయితే_ముగింపు // SDL_MMX_INTRINSICS

// fast RGB565->RGB565 blending with surface alpha
స్థిర శూన్య Blit565to565SurfaceAlpha(SDL_BlitInfo *info)
{
    గుర్తులేని alpha = info->a;
    ఒకవేళ (alpha == 128) {
        Blit16to16SurfaceAlpha128(info, 0xf7de);
    } లేకపోతే {
        పూర్ణాంకం వెడల్పు = info->dst_w;
        పూర్ణాంకం ఎత్తు = info->dst_h;
        Uint16 *srcp = (Uint16 *)info->src;
        పూర్ణాంకం srcskip = info->src_skip >> 1;
        Uint16 *dstp = (Uint16 *)info->dst;
        పూర్ణాంకం dstskip = info->dst_skip >> 1;
        alpha >>= 3; // downscale alpha to 5 bits

        అయితే (ఎత్తు--) {
            /* *INDENT-OFF* */ // clang-format off
            DUFFS_LOOP({
                Uint32 s = *srcp++;
                Uint32 d = *dstp;
                /*
                 * shift out the middle component (green) to
                 * the high 16 bits, and process all three RGB
                 * components at the same time.
                 */
                s = (s | s << 16) & 0x07e0f81f;
                d = (d | d << 16) & 0x07e0f81f;
                d += (s - d) * alpha >> 5;
                d &= 0x07e0f81f;
                *dstp++ = (Uint16)(d | d >> 16);
            }, వెడల్పు);
            /* *INDENT-ON* */ // clang-format on
            srcp += srcskip;
            dstp += dstskip;
        }
    }
}

// fast RGB555->RGB555 blending with surface alpha
స్థిర శూన్య Blit555to555SurfaceAlpha(SDL_BlitInfo *info)
{
    గుర్తులేని alpha = info->a; // downscale alpha to 5 bits
    ఒకవేళ (alpha == 128) {
        Blit16to16SurfaceAlpha128(info, 0xfbde);
    } లేకపోతే {
        పూర్ణాంకం వెడల్పు = info->dst_w;
        పూర్ణాంకం ఎత్తు = info->dst_h;
        Uint16 *srcp = (Uint16 *)info->src;
        పూర్ణాంకం srcskip = info->src_skip >> 1;
        Uint16 *dstp = (Uint16 *)info->dst;
        పూర్ణాంకం dstskip = info->dst_skip >> 1;
        alpha >>= 3; // downscale alpha to 5 bits

        అయితే (ఎత్తు--) {
            /* *INDENT-OFF* */ // clang-format off
            DUFFS_LOOP({
                Uint32 s = *srcp++;
                Uint32 d = *dstp;
                /*
                 * shift out the middle component (green) to
                 * the high 16 bits, and process all three RGB
                 * components at the same time.
                 */
                s = (s | s << 16) & 0x03e07c1f;
                d = (d | d << 16) & 0x03e07c1f;
                d += (s - d) * alpha >> 5;
                d &= 0x03e07c1f;
                *dstp++ = (Uint16)(d | d >> 16);
            }, వెడల్పు);
            /* *INDENT-ON* */ // clang-format on
            srcp += srcskip;
            dstp += dstskip;
        }
    }
}

// fast ARGB8888->RGB565 blending with pixel alpha
స్థిర శూన్య BlitARGBto565PixelAlpha(SDL_BlitInfo *info)
{
    పూర్ణాంకం వెడల్పు = info->dst_w;
    పూర్ణాంకం ఎత్తు = info->dst_h;
    Uint32 *srcp = (Uint32 *)info->src;
    పూర్ణాంకం srcskip = info->src_skip >> 2;
    Uint16 *dstp = (Uint16 *)info->dst;
    పూర్ణాంకం dstskip = info->dst_skip >> 1;

    అయితే (ఎత్తు--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP({
        Uint32 s = *srcp;
        గుర్తులేని alpha = s >> 27; // downscale alpha to 5 bits
        /* Here we special-case opaque alpha since the
           compositioning used (>>8 instead of /255) doesn't handle
           it correctly. */
        ఒకవేళ (alpha) {
          ఒకవేళ (alpha == (SDL_ALPHA_OPAQUE >> 3)) {
            *dstp = (Uint16)((s >> 8 & 0xf800) + (s >> 5 & 0x7e0) + (s >> 3  & 0x1f));
          } లేకపోతే {
            Uint32 d = *dstp;
            /*
             * convert source and destination to G0RAB65565
             * and blend all components at the same time
             */
            s = ((s & 0xfc00) << 11) + (s >> 8 & 0xf800) + (s >> 3 & 0x1f);
            d = (d | d << 16) & 0x07e0f81f;
            d += (s - d) * alpha >> 5;
            d &= 0x07e0f81f;
            *dstp = (Uint16)(d | d >> 16);
          }
        }
        srcp++;
        dstp++;
        }, వెడల్పు);
        /* *INDENT-ON* */ // clang-format on
        srcp += srcskip;
        dstp += dstskip;
    }
}

// fast ARGB8888->RGB555 blending with pixel alpha
స్థిర శూన్య BlitARGBto555PixelAlpha(SDL_BlitInfo *info)
{
    పూర్ణాంకం వెడల్పు = info->dst_w;
    పూర్ణాంకం ఎత్తు = info->dst_h;
    Uint32 *srcp = (Uint32 *)info->src;
    పూర్ణాంకం srcskip = info->src_skip >> 2;
    Uint16 *dstp = (Uint16 *)info->dst;
    పూర్ణాంకం dstskip = info->dst_skip >> 1;

    అయితే (ఎత్తు--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP({
        గుర్తులేని alpha;
        Uint32 s = *srcp;
        alpha = s >> 27; // downscale alpha to 5 bits
        /* Here we special-case opaque alpha since the
           compositioning used (>>8 instead of /255) doesn't handle
           it correctly. */
        ఒకవేళ (alpha) {
          ఒకవేళ (alpha == (SDL_ALPHA_OPAQUE >> 3)) {
            *dstp = (Uint16)((s >> 9 & 0x7c00) + (s >> 6 & 0x3e0) + (s >> 3  & 0x1f));
          } లేకపోతే {
            Uint32 d = *dstp;
            /*
             * convert source and destination to G0RAB55555
             * and blend all components at the same time
             */
            s = ((s & 0xf800) << 10) + (s >> 9 & 0x7c00) + (s >> 3 & 0x1f);
            d = (d | d << 16) & 0x03e07c1f;
            d += (s - d) * alpha >> 5;
            d &= 0x03e07c1f;
            *dstp = (Uint16)(d | d >> 16);
          }
        }
        srcp++;
        dstp++;
        }, వెడల్పు);
        /* *INDENT-ON* */ // clang-format on
        srcp += srcskip;
        dstp += dstskip;
    }
}

// General (slow) N->N blending with per-surface alpha
స్థిర శూన్య BlitNtoNSurfaceAlpha(SDL_BlitInfo *info)
{
    పూర్ణాంకం వెడల్పు = info->dst_w;
    పూర్ణాంకం ఎత్తు = info->dst_h;
    Uint8 *src = info->src;
    పూర్ణాంకం srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    పూర్ణాంకం dstskip = info->dst_skip;
    స్థిరరాశి SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    స్థిరరాశి SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    పూర్ణాంకం srcbpp = srcfmt->బైట్లు_చొప్పున_pixel;
    పూర్ణాంకం dstbpp = dstfmt->బైట్లు_చొప్పున_pixel;
    Uint32 Pixel;
    గుర్తులేని sR, sG, sB;
    గుర్తులేని dR, dG, dB, dA;
    స్థిరరాశి గుర్తులేని sA = info->a;

    ఒకవేళ (sA) {
        అయితే (ఎత్తు--) {
            /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP(
        {
        DISEMBLE_RGB(src, srcbpp, srcfmt, Pixel, sR, sG, sB);
        DISEMBLE_RGBA(dst, dstbpp, dstfmt, Pixel, dR, dG, dB, dA);
        ALPHA_BLEND_RGBA(sR, sG, sB, sA, dR, dG, dB, dA);
        ASSEMBLE_RGBA(dst, dstbpp, dstfmt, dR, dG, dB, dA);
        src += srcbpp;
        dst += dstbpp;
        },
        వెడల్పు);
        /* *INDENT-ON* */ // clang-format on
            src += srcskip;
            dst += dstskip;
        }
    }
}

// General (slow) colorkeyed N->N blending with per-surface alpha
స్థిర శూన్య Blit_Nto_NSurface_Alpha_కీలకం(SDL_BlitInfo *info)
{
    పూర్ణాంకం వెడల్పు = info->dst_w;
    పూర్ణాంకం ఎత్తు = info->dst_h;
    Uint8 *src = info->src;
    పూర్ణాంకం srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    పూర్ణాంకం dstskip = info->dst_skip;
    స్థిరరాశి SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    స్థిరరాశి SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    Uint32 ckey = info->colorkey;
    పూర్ణాంకం srcbpp = srcfmt->బైట్లు_చొప్పున_pixel;
    పూర్ణాంకం dstbpp = dstfmt->బైట్లు_చొప్పున_pixel;
    Uint32 Pixel;
    గుర్తులేని sR, sG, sB;
    గుర్తులేని dR, dG, dB, dA;
    స్థిరరాశి గుర్తులేని sA = info->a;

    అయితే (ఎత్తు--) {
        /* *INDENT-OFF* */ // clang-format off
        DUFFS_LOOP(
        {
        RETRIEVE_RGB_PIXEL(src, srcbpp, Pixel);
        ఒకవేళ (sA && Pixel != ckey) {
            RGB_FROM_PIXEL(Pixel, srcfmt, sR, sG, sB);
            DISEMBLE_RGBA(dst, dstbpp, dstfmt, Pixel, dR, dG, dB, dA);
            ALPHA_BLEND_RGBA(sR, sG, sB, sA, dR, dG, dB, dA);
            ASSEMBLE_RGBA(dst, dstbpp, dstfmt, dR, dG, dB, dA);
        }
        src += srcbpp;
        dst += dstbpp;
        },
        వెడల్పు);
        /* *INDENT-ON* */ // clang-format on
        src += srcskip;
        dst += dstskip;
    }
}

// Fast 32-bit RGBA->RGBA blending with pixel alpha
స్థిర శూన్య Blit8888to8888PixelAlpha(SDL_BlitInfo *info)
{
    పూర్ణాంకం వెడల్పు = info->dst_w;
    పూర్ణాంకం ఎత్తు = info->dst_h;
    Uint8 *src = info->src;
    పూర్ణాంకం srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    పూర్ణాంకం dstskip = info->dst_skip;
    స్థిరరాశి SDL_PixelFormatDetails *srcfmt = info->src_fmt;

    అయితే (ఎత్తు--) {
        పూర్ణాంకం i = 0;

        కొరకు (; i < వెడల్పు; ++i) {
            Uint32 src32 = *(Uint32 *)src;
            Uint32 dst32 = *(Uint32 *)dst;
            ALPHA_BLEND_8888(src32, dst32, srcfmt);
            *(Uint32 *)dst = dst32;
            src += 4;
            dst += 4;
        }

        src += srcskip;
        dst += dstskip;
    }
}

// Fast 32-bit RGBA->RGB(A) blending with pixel alpha and src swizzling
స్థిర శూన్య Blit8888to8888PixelAlphaSwizzle(SDL_BlitInfo *info)
{
    పూర్ణాంకం వెడల్పు = info->dst_w;
    పూర్ణాంకం ఎత్తు = info->dst_h;
    Uint8 *src = info->src;
    పూర్ణాంకం srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    పూర్ణాంకం dstskip = info->dst_skip;
    స్థిరరాశి SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    స్థిరరాశి SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    bool fill_alpha = !dstfmt->Amask;
    Uint32 dstAmask, dstAshift;

    SDL_Get8888_Alpha_ముసుగు_And_జరుపు(dstfmt, &dstAmask, &dstAshift);

    అయితే (ఎత్తు--) {
        పూర్ణాంకం i = 0;

        కొరకు (; i < వెడల్పు; ++i) {
            Uint32 src32 = *(Uint32 *)src;
            Uint32 dst32 = *(Uint32 *)dst;
            ALPHA_BLEND_SWIZZLE_8888(src32, dst32, srcfmt, dstfmt);
            ఒకవేళ (fill_alpha) {
                dst32 |= dstAmask;
            }
            *(Uint32 *)dst = dst32;
            src += 4;
            dst += 4;
        }

        src += srcskip;
        dst += dstskip;
    }
}

#నిర్వచితమైతే SDL_SSE4_1_INTRINSICS

స్థిర శూన్య SDL_TARGETING("sse4.1") Blit8888to8888PixelAlphaSwizzleSSE41(SDL_BlitInfo *info)
{
    పూర్ణాంకం వెడల్పు = info->dst_w;
    పూర్ణాంకం ఎత్తు = info->dst_h;
    Uint8 *src = info->src;
    పూర్ణాంకం srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    పూర్ణాంకం dstskip = info->dst_skip;
    స్థిరరాశి SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    స్థిరరాశి SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    bool fill_alpha = !dstfmt->Amask;
    Uint32 dstAmask, dstAshift;

    SDL_Get8888_Alpha_ముసుగు_And_జరుపు(dstfmt, &dstAmask, &dstAshift);

    // The byte offsets for the start of each pixel
    స్థిరరాశి __m128i ముసుగు_offsets = mm_సమితి_epi8(
        12, 12, 12, 12, 8, 8, 8, 8, 4, 4, 4, 4, 0, 0, 0, 0);

    స్థిరరాశి __m128i convert_ముసుగు = mm_కూడు_epi32(
        _mm_set1_epi32(
            ((srcfmt->Rshift >> 3) << dstfmt->Rshift) |
            ((srcfmt->Gshift >> 3) << dstfmt->Gshift) |
            ((srcfmt->Bshift >> 3) << dstfmt->Bshift)),
        ముసుగు_offsets);

    స్థిరరాశి __m128i alpha_splat_ముసుగు = mm_కూడు_epi8(_mm_set1_epi8(srcfmt->Ashift >> 3), ముసుగు_offsets);
    స్థిరరాశి __m128i alpha_fill_ముసుగు = _mm_set1_epi32((పూర్ణాంకం)dstAmask);

    అయితే (ఎత్తు--) {
        పూర్ణాంకం i = 0;

        కొరకు (; i + 4 <= వెడల్పు; i += 4) {
            // Load 4 src pixels
            __m128i src128 = _mm_loadu_si128((__m128i *)src);

            // Load 4 dst pixels
            __m128i dst128 = _mm_loadu_si128((__m128i *)dst);

            // Extract the alpha from each pixel and splat it into all the channels
            __m128i srcA = _mm_shuffle_epi8(src128, alpha_splat_ముసుగు);

            // Convert to dst format
            src128 = _mm_shuffle_epi8(src128, convert_ముసుగు);

            // Set the alpha channels of src to 255
            src128 = _mm_or_si128(src128, alpha_fill_ముసుగు);

            // Duplicate each 8-bit alpha value into both bytes of 16-bit lanes
            __m128i srca_lo = _mm_unpacklo_epi8(srcA, srcA);
            __m128i srca_hi = _mm_unpackhi_epi8(srcA, srcA);

            // Calculate 255-srcA in every second 8-bit lane (255-srcA = srcA^0xff)
            srca_lo = _mm_xor_si128(srca_lo, _mm_set1_epi16(0xff00));
            srca_hi = _mm_xor_si128(srca_hi, _mm_set1_epi16(0xff00));

            // maddubs expects second argument to be signed, so subtract 128
            src128 = _mm_sub_epi8(src128, _mm_set1_epi8((Uint8)128));
            dst128 = _mm_sub_epi8(dst128, _mm_set1_epi8((Uint8)128));

            // dst = srcA*(src-128) + (255-srcA)*(dst-128) = srcA*src + (255-srcA)*dst - 128*255
            __m128i dst_lo = _mm_maddubs_epi16(srca_lo, _mm_unpacklo_epi8(src128, dst128));
            __m128i dst_hi = _mm_maddubs_epi16(srca_hi, _mm_unpackhi_epi8(src128, dst128));

            // dst += 0x1U (use 0x80 to round instead of floor) + 128*255 (to fix maddubs result)
            dst_lo = mm_కూడు_epi16(dst_lo, _mm_set1_epi16(1 + 128 * 255));
            dst_hi = mm_కూడు_epi16(dst_hi, _mm_set1_epi16(1 + 128 * 255));

            // dst = (dst + (dst >> 8)) >> 8 = (dst * 257) >> 16
            dst_lo = _mm_mulhi_epu16(dst_lo, _mm_set1_epi16(257));
            dst_hi = _mm_mulhi_epu16(dst_hi, _mm_set1_epi16(257));

            // Blend the pixels together and save the result
            dst128 = _mm_packus_epi16(dst_lo, dst_hi);
            ఒకవేళ (fill_alpha) {
                dst128 = _mm_or_si128(dst128, alpha_fill_ముసుగు);
            }
            _mm_storeu_si128((__m128i *)dst, dst128);

            src += 16;
            dst += 16;
        }

        కొరకు (; i < వెడల్పు; ++i) {
            Uint32 src32 = *(Uint32 *)src;
            Uint32 dst32 = *(Uint32 *)dst;
            ALPHA_BLEND_SWIZZLE_8888(src32, dst32, srcfmt, dstfmt);
            ఒకవేళ (fill_alpha) {
                dst32 |= dstAmask;
            }
            *(Uint32 *)dst = dst32;
            src += 4;
            dst += 4;
        }

        src += srcskip;
        dst += dstskip;
    }
}

#అయితే_ముగింపు

#నిర్వచితమైతే SDL_AVX2_INTRINSICS

స్థిర శూన్య SDL_TARGETING("avx2") Blit8888to8888PixelAlphaSwizzleAVX2(SDL_BlitInfo *info)
{
    పూర్ణాంకం వెడల్పు = info->dst_w;
    పూర్ణాంకం ఎత్తు = info->dst_h;
    Uint8 *src = info->src;
    పూర్ణాంకం srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    పూర్ణాంకం dstskip = info->dst_skip;
    స్థిరరాశి SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    స్థిరరాశి SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    bool fill_alpha = !dstfmt->Amask;
    Uint32 dstAmask, dstAshift;

    SDL_Get8888_Alpha_ముసుగు_And_జరుపు(dstfmt, &dstAmask, &dstAshift);

    // The byte offsets for the start of each pixel
    స్థిరరాశి __m256i ముసుగు_offsets = mm256_సమితి_epi8(
        28, 28, 28, 28, 24, 24, 24, 24, 20, 20, 20, 20, 16, 16, 16, 16, 12, 12, 12, 12, 8, 8, 8, 8, 4, 4, 4, 4, 0, 0, 0, 0);

    స్థిరరాశి __m256i convert_ముసుగు = mm256_కూడు_epi32(
        _mm256_set1_epi32(
            ((srcfmt->Rshift >> 3) << dstfmt->Rshift) |
            ((srcfmt->Gshift >> 3) << dstfmt->Gshift) |
            ((srcfmt->Bshift >> 3) << dstfmt->Bshift)),
        ముసుగు_offsets);

    స్థిరరాశి __m256i alpha_splat_ముసుగు = mm256_కూడు_epi8(_mm256_set1_epi8(srcfmt->Ashift >> 3), ముసుగు_offsets);
    స్థిరరాశి __m256i alpha_fill_ముసుగు = _mm256_set1_epi32((పూర్ణాంకం)dstAmask);

    అయితే (ఎత్తు--) {
        పూర్ణాంకం i = 0;

        కొరకు (; i + 8 <= వెడల్పు; i += 8) {
            // Load 8 src pixels
            __m256i src256 = _mm256_loadu_si256((__m256i *)src);

            // Load 8 dst pixels
            __m256i dst256 = _mm256_loadu_si256((__m256i *)dst);

            // Extract the alpha from each pixel and splat it into all the channels
            __m256i srcA = _mm256_shuffle_epi8(src256, alpha_splat_ముసుగు);

            // Convert to dst format
            src256 = _mm256_shuffle_epi8(src256, convert_ముసుగు);

            // Set the alpha channels of src to 255
            src256 = _mm256_or_si256(src256, alpha_fill_ముసుగు);

            // Duplicate each 8-bit alpha value into both bytes of 16-bit lanes
            __m256i alpha_lo = _mm256_unpacklo_epi8(srcA, srcA);
            __m256i alpha_hi = _mm256_unpackhi_epi8(srcA, srcA);

            // Calculate 255-srcA in every second 8-bit lane (255-srcA = srcA^0xff)
            alpha_lo = _mm256_xor_si256(alpha_lo, _mm256_set1_epi16(0xff00));
            alpha_hi = _mm256_xor_si256(alpha_hi, _mm256_set1_epi16(0xff00));

            // maddubs expects second argument to be signed, so subtract 128
            src256 = _mm256_sub_epi8(src256, _mm256_set1_epi8((Uint8)128));
            dst256 = _mm256_sub_epi8(dst256, _mm256_set1_epi8((Uint8)128));

            // dst = srcA*(src-128) + (255-srcA)*(dst-128) = srcA*src + (255-srcA)*dst - 128*255
            __m256i dst_lo = _mm256_maddubs_epi16(alpha_lo, _mm256_unpacklo_epi8(src256, dst256));
            __m256i dst_hi = _mm256_maddubs_epi16(alpha_hi, _mm256_unpackhi_epi8(src256, dst256));

            // dst += 0x1U (use 0x80 to round instead of floor) + 128*255 (to fix maddubs result)
            dst_lo = mm256_కూడు_epi16(dst_lo, _mm256_set1_epi16(1 + 128 * 255));
            dst_hi = mm256_కూడు_epi16(dst_hi, _mm256_set1_epi16(1 + 128 * 255));

            // dst = (dst + (dst >> 8)) >> 8 = (dst * 257) >> 16
            dst_lo = _mm256_mulhi_epu16(dst_lo, _mm256_set1_epi16(257));
            dst_hi = _mm256_mulhi_epu16(dst_hi, _mm256_set1_epi16(257));

            // Blend the pixels together and save the result
            dst256 = _mm256_packus_epi16(dst_lo, dst_hi);
            ఒకవేళ (fill_alpha) {
                dst256 = _mm256_or_si256(dst256, alpha_fill_ముసుగు);
            }
            _mm256_storeu_si256((__m256i *)dst, dst256);

            src += 32;
            dst += 32;
        }

        కొరకు (; i < వెడల్పు; ++i) {
            Uint32 src32 = *(Uint32 *)src;
            Uint32 dst32 = *(Uint32 *)dst;
            ALPHA_BLEND_SWIZZLE_8888(src32, dst32, srcfmt, dstfmt);
            ఒకవేళ (fill_alpha) {
                dst32 |= dstAmask;
            }
            *(Uint32 *)dst = dst32;
            src += 4;
            dst += 4;
        }

        src += srcskip;
        dst += dstskip;
    }
}

#అయితే_ముగింపు

#ఒకవేళ defined(SDL_NEON_INTRINSICS) && (__ARM_ARCH >= 8) && (defined(__aarch64__) || defined(_M_ARM64))

స్థిర శూన్య Blit8888to8888PixelAlphaSwizzleNEON(SDL_BlitInfo *info)
{
    పూర్ణాంకం వెడల్పు = info->dst_w;
    పూర్ణాంకం ఎత్తు = info->dst_h;
    Uint8 *src = info->src;
    పూర్ణాంకం srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    పూర్ణాంకం dstskip = info->dst_skip;
    స్థిరరాశి SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    స్థిరరాశి SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    bool fill_alpha = !dstfmt->Amask;
    Uint32 dstAmask, dstAshift;

    SDL_Get8888_Alpha_ముసుగు_And_జరుపు(dstfmt, &dstAmask, &dstAshift);

    // The byte offsets for the start of each pixel
    స్థిరరాశి uint8x16_t ముసుగు_offsets = vreinterpretq_u8_u64(vcombine_u64(
        vcreate_u64(0x0404040400000000), vcreate_u64(0x0c0c0c0c08080808)));

    స్థిరరాశి uint8x16_t convert_ముసుగు = vreinterpretq_u8_u32(vaddq_u32(
        vreinterpretq_u32_u8(ముసుగు_offsets),
        vdupq_n_u32(
            ((srcfmt->Rshift >> 3) << dstfmt->Rshift) |
            ((srcfmt->Gshift >> 3) << dstfmt->Gshift) |
            ((srcfmt->Bshift >> 3) << dstfmt->Bshift))));

    స్థిరరాశి uint8x16_t alpha_splat_ముసుగు = vaddq_u8(vdupq_n_u8(srcfmt->Ashift >> 3), ముసుగు_offsets);
    స్థిరరాశి uint8x16_t alpha_fill_ముసుగు = vreinterpretq_u8_u32(vdupq_n_u32(dstAmask));

    అయితే (ఎత్తు--) {
        పూర్ణాంకం i = 0;

        కొరకు (; i + 4 <= వెడల్పు; i += 4) {
            // Load 4 src pixels
            uint8x16_t src128 = vld1q_u8(src);

            // Load 4 dst pixels
            uint8x16_t dst128 = vld1q_u8(dst);

            // Extract the alpha from each pixel and splat it into all the channels
            uint8x16_t srcA = vqtbl1q_u8(src128, alpha_splat_ముసుగు);

            // Convert to dst format
            src128 = vqtbl1q_u8(src128, convert_ముసుగు);

            // Set the alpha channels of src to 255
            src128 = vorrq_u8(src128, alpha_fill_ముసుగు);

            // 255 - srcA = ~srcA
            uint8x16_t srcInvA = vmvnq_u8(srcA);

            // Result initialized with 1, this is for truncated divide later
            uint16x8_t res_lo = vdupq_n_u16(1);
            uint16x8_t res_hi = vdupq_n_u16(1);

            // res = alpha * src + (255 - alpha) * dst
            res_lo = vmlal_u8(res_lo, vget_దిగువ_u8(srcA),    vget_దిగువ_u8(src128));
            res_lo = vmlal_u8(res_lo, vget_దిగువ_u8(srcInvA), vget_దిగువ_u8(dst128));
            res_hi = vmlal_ఎగువ_u8(res_hi, srcA,    src128);
            res_hi = vmlal_ఎగువ_u8(res_hi, srcInvA, dst128);

            // Now result has +1 already added for truncated division
            // dst = (res + (res >> 8)) >> 8
            uint8x8_t తాత్కాలిక;
            తాత్కాలిక   = vaddhn_u16(res_lo, vshrq_n_u16(res_lo, 8));
            dst128 = vaddhn_ఎగువ_u16(తాత్కాలిక, res_hi, vshrq_n_u16(res_hi, 8));

            // For rounded division remove the constant 1 and change first two vmlal_u8 to vmull_u8
            // Then replace two previous lines with following code:
            // temp   = vraddhn_u16(res_lo, vrshrq_n_u16(res_lo, 8));
            // dst128 = vraddhn_high_u16(temp, res_hi, vrshrq_n_u16(res_hi, 8));

            ఒకవేళ (fill_alpha) {
                dst128 = vorrq_u8(dst128, alpha_fill_ముసుగు);
            }

            // Save the result
            vst1q_u8(dst, dst128);

            src += 16;
            dst += 16;
        }

        // Process 1 pixel per iteration, max 3 iterations, same calculations as above
        కొరకు (; i < వెడల్పు; ++i) {
            // Top 32-bits will be not used in src32 & dst32
            uint8x8_t src32 = vreinterpret_u8_u32(vld1_dup_u32((Uint32 *)src));
            uint8x8_t dst32 = vreinterpret_u8_u32(vld1_dup_u32((Uint32 *)dst));

            uint8x8_t srcA = vtbl1_u8(src32, vget_దిగువ_u8(alpha_splat_ముసుగు));
            src32 = vtbl1_u8(src32, vget_దిగువ_u8(convert_ముసుగు));
            src32 = vorr_u8(src32, vget_దిగువ_u8(alpha_fill_ముసుగు));
            uint8x8_t srcInvA = vmvn_u8(srcA);

            uint16x8_t res = vdupq_n_u16(1);
            res = vmlal_u8(res, srcA,    src32);
            res = vmlal_u8(res, srcInvA, dst32);

            dst32 = vaddhn_u16(res, vshrq_n_u16(res, 8));

            ఒకవేళ (fill_alpha) {
                dst32 = vorr_u8(dst32, vget_దిగువ_u8(alpha_fill_ముసుగు));
            }

            // Save the result, only low 32-bits
            vst1_lane_u32((Uint32 *)dst, vreinterpret_u32_u8(dst32), 0);

            src += 4;
            dst += 4;
        }

        src += srcskip;
        dst += dstskip;
    }
}

#అయితే_ముగింపు

// General (slow) N->N blending with pixel alpha
స్థిర శూన్య BlitNtoNPixelAlpha(SDL_BlitInfo *info)
{
    పూర్ణాంకం వెడల్పు = info->dst_w;
    పూర్ణాంకం ఎత్తు = info->dst_h;
    Uint8 *src = info->src;
    పూర్ణాంకం srcskip = info->src_skip;
    Uint8 *dst = info->dst;
    పూర్ణాంకం dstskip = info->dst_skip;
    స్థిరరాశి SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    స్థిరరాశి SDL_PixelFormatDetails *dstfmt = info->dst_fmt;
    పూర్ణాంకం srcbpp;
    పూర్ణాంకం dstbpp;
    Uint32 Pixel;
    గుర్తులేని sR, sG, sB, sA;
    గుర్తులేని dR, dG, dB, dA;

    // Set up some basic variables
    srcbpp = srcfmt->బైట్లు_చొప్పున_pixel;
    dstbpp = dstfmt->బైట్లు_చొప్పున_pixel;

    అయితే (ఎత్తు--) {
        DUFFS_LOOP(
        {
        DISEMBLE_RGBA(src, srcbpp, srcfmt, Pixel, sR, sG, sB, sA);
        ఒకవేళ (sA) {
            DISEMBLE_RGBA(dst, dstbpp, dstfmt, Pixel, dR, dG, dB, dA);
            ALPHA_BLEND_RGBA(sR, sG, sB, sA, dR, dG, dB, dA);
            ASSEMBLE_RGBA(dst, dstbpp, dstfmt, dR, dG, dB, dA);
        }
        src += srcbpp;
        dst += dstbpp;
        },
        వెడల్పు);
        /* *INDENT-ON* */ // clang-format on
        src += srcskip;
        dst += dstskip;
    }
}

SDL_BlitFunc SDL_CalculateBlitA(SDL_Surface *surface)
{
    స్థిరరాశి SDL_PixelFormatDetails *sf = surface->fmt;
    స్థిరరాశి SDL_PixelFormatDetails *df = surface->map.info.dst_fmt;

    ఎంపిక (surface->map.info.flags & ~SDL_COPY_RLE_ముసుగు) {
    స్థితి SDL_COPY_BLEND:
        // Per-pixel alpha blits
        ఎంపిక (df->బైట్లు_చొప్పున_pixel) {
        స్థితి 1:
            ఒకవేళ (surface->map.info.dst_pal) {
                తిరిగి BlitNto1PixelAlpha;
            } లేకపోతే {
                // RGB332 has no palette !
                తిరిగి BlitNtoNPixelAlpha;
            }

        స్థితి 2:
#నిర్వచితమైతే SDL_SVE2_INTRINSICS
            ఒకవేళ (SDL_HasSVE2()) {
                ఒకవేళ (sf->బైట్లు_చొప్పున_pixel == 4 &&
                    df->బైట్లు_చొప్పున_pixel == 2 &&
                    df->Rmask == 0x0000F800 &&
                    df->Gmask == 0x000007E0 &&
                    df->Bmask == 0x0000001F) {
                    తిరిగి Blit8888to565PixelAlphaSwizzleSVE2;
                }
            }
#అయితే_ముగింపు
            ఒకవేళ (sf->బైట్లు_చొప్పున_pixel == 4 && sf->Amask == 0xff000000 && sf->Gmask == 0xff00 && ((sf->Rmask == 0xff && df->Rmask == 0x1f) || (sf->Bmask == 0xff && df->Bmask == 0x1f))) {
                ఒకవేళ (df->Gmask == 0x7e0) {
                    తిరిగి BlitARGBto565PixelAlpha;
                } లేకపోతే ఒకవేళ (df->Gmask == 0x3e0 && !df->Amask) {
                    తిరిగి BlitARGBto555PixelAlpha;
                }
            }
            తిరిగి BlitNtoNPixelAlpha;

        స్థితి 4:
            ఒకవేళ (SDL_PIXELLAYOUT(sf->format) == SDL_PACKEDLAYOUT_8888 && sf->Amask &&
                SDL_PIXELLAYOUT(df->format) == SDL_PACKEDLAYOUT_8888) {
#నిర్వచితమైతే SDL_AVX2_INTRINSICS
                ఒకవేళ (SDL_HasAVX2()) {
                    తిరిగి Blit8888to8888PixelAlphaSwizzleAVX2;
                }
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_SSE4_1_INTRINSICS
                ఒకవేళ (SDL_HasSSE41()) {
                    తిరిగి Blit8888to8888PixelAlphaSwizzleSSE41;
                }
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_LSX_INTRINSICS
                ఒకవేళ (SDL_HasLSX()) {
                    తిరిగి Blit8888to8888PixelAlphaSwizzleLSX;
                }
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_SVE2_INTRINSICS
                ఒకవేళ (SDL_HasSVE2() 
            /* NEON is faster than SVE2 when vector size is 128bit */
            #ఒకవేళ defined(SDL_NEON_INTRINSICS)
                && (SDL_Get_SVEVector_కొలత() > 128 || !SDL_HasNEON())
            #అయితే_ముగింపు
                ) {
                    // To prevent "unused function" compiler warnings/errors
                    (శూన్య)Blit8888to8888PixelAlpha;
                    (శూన్య)Blit8888to8888PixelAlphaSwizzle;
                    తిరిగి Blit8888to8888PixelAlphaSwizzleSVE2;
                }
#అయితే_ముగింపు
#ఒకవేళ defined(SDL_NEON_INTRINSICS) && (__ARM_ARCH >= 8) && (defined(__aarch64__) || defined(_M_ARM64))
                ఒకవేళ (SDL_HasNEON()) {
                    తిరిగి Blit8888to8888PixelAlphaSwizzleNEON;
                }
#అయితే_ముగింపు
                ఒకవేళ (sf->format == df->format) {
                    తిరిగి Blit8888to8888PixelAlpha;
                } లేకపోతే {
                    తిరిగి Blit8888to8888PixelAlphaSwizzle;
                }
            }
            తిరిగి BlitNtoNPixelAlpha;

        స్థితి 3:
        అప్రమేయ:
            ఆపు;
        }
        తిరిగి BlitNtoNPixelAlpha;

    స్థితి SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
        ఒకవేళ (sf->Amask == 0) {
            // Per-surface alpha blits
            ఎంపిక (df->బైట్లు_చొప్పున_pixel) {
            స్థితి 1:
                ఒకవేళ (surface->map.info.dst_pal) {
                    తిరిగి BlitNto1SurfaceAlpha;
                } లేకపోతే {
                    // RGB332 has no palette !
                    తిరిగి BlitNtoNSurfaceAlpha;
                }

            స్థితి 2:
                ఒకవేళ (surface->map.తటస్థం) {
                    ఒకవేళ (df->Gmask == 0x7e0) {
#నిర్వచితమైతే SDL_MMX_INTRINSICS
                        ఒకవేళ (SDL_HasMMX()) {
                            తిరిగి Blit565to565SurfaceAlphaMMX;
                        } లేకపోతే
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_SVE2_INTRINSICS
                        ఒకవేళ (SDL_HasSVE2()) {
                            తిరిగి Blit565to565SurfaceAlphaSVE2;
                        } లేకపోతే 
#అయితే_ముగింపు
                        {
                            తిరిగి Blit565to565SurfaceAlpha;
                        }
                    } లేకపోతే ఒకవేళ (df->Gmask == 0x3e0) {
#నిర్వచితమైతే SDL_MMX_INTRINSICS
                        ఒకవేళ (SDL_HasMMX()) {
                            తిరిగి Blit555to555SurfaceAlphaMMX;
                        } లేకపోతే
#అయితే_ముగింపు
                        {
                            తిరిగి Blit555to555SurfaceAlpha;
                        }
                    }
                }
                తిరిగి BlitNtoNSurfaceAlpha;

            స్థితి 4:
                ఒకవేళ (sf->Rmask == df->Rmask && sf->Gmask == df->Gmask && sf->Bmask == df->Bmask && sf->బైట్లు_చొప్పున_pixel == 4) {
#నిర్వచితమైతే SDL_SSE2_INTRINSICS
                    ఒకవేళ (sf->Rshift % 8 == 0 && sf->Gshift % 8 == 0 && sf->Bshift % 8 == 0 && SDL_HasSSE2()) {
                        తిరిగి Blit888to888SurfaceAlphaSSE2;
                    }
#అయితే_ముగింపు
                    ఒకవేళ ((sf->Rmask | sf->Gmask | sf->Bmask) == 0xffffff) {
                        తిరిగి BlitRGBtoRGBSurfaceAlpha;
                    }
                }
                తిరిగి BlitNtoNSurfaceAlpha;

            స్థితి 3:
            అప్రమేయ:
                తిరిగి BlitNtoNSurfaceAlpha;
            }
        }
        ఆపు;

    స్థితి SDL_COPY_COLORKEY | SDL_COPY_MODULATE_ALPHA | SDL_COPY_BLEND:
        ఒకవేళ (sf->Amask == 0) {
            ఒకవేళ (df->బైట్లు_చొప్పున_pixel == 1) {

                ఒకవేళ (surface->map.info.dst_pal) {
                    తిరిగి Blit_Nto1_Surface_Alpha_కీలకం;
                } లేకపోతే {
                    // RGB332 has no palette !
                    తిరిగి Blit_Nto_NSurface_Alpha_కీలకం;
                }
            } లేకపోతే {
                తిరిగి Blit_Nto_NSurface_Alpha_కీలకం;
            }
        }
        ఆపు;
    }

    తిరిగి ఖాళీ;
}

#అయితే_ముగింపు // SDL_HAVE_BLIT_A

