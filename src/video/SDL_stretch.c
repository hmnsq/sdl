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

#అన్తర్భావ "SDL_surface_c.h"

స్థిర bool SDL_Stretch_Surface_Unchecked_సమీప(SDL_Surface *src, స్థిరరాశి SDL_Rect *srcrect, SDL_Surface *dst, స్థిరరాశి SDL_Rect *dstrect);
స్థిర bool SDL_Stretch_Surface_Unchecked_రేఖీయ(SDL_Surface *src, స్థిరరాశి SDL_Rect *srcrect, SDL_Surface *dst, స్థిరరాశి SDL_Rect *dstrect);

bool SDL_StretchSurface(SDL_Surface *src, స్థిరరాశి SDL_Rect *srcrect, SDL_Surface *dst, స్థిరరాశి SDL_Rect *dstrect, SDL_Scale_బహుళకం scale_బహుళకం)
{
    bool ఫలితం;
    పూర్ణాంకం src_locked;
    పూర్ణాంకం dst_locked;
    SDL_Rect నిండిన_src;
    SDL_Rect నిండిన_dst;

    CHECK_PARAM(!src) {
        తిరిగి SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!dst) {
        తిరిగి SDL_InvalidParamError("dst");
    }

    ఒకవేళ (src->format != dst->format) {
        // Slow!
        SDL_Surface *src_tmp = SDL_ConvertSurfaceAndColorspace(src, dst->format, dst->palette, dst->colorspace, dst->props);
        ఒకవేళ (!src_tmp) {
            తిరిగి false;
        }
        ఫలితం = SDL_StretchSurface(src_tmp, srcrect, dst, dstrect, scale_బహుళకం);
        SDL_DestroySurface(src_tmp);
        తిరిగి ఫలితం;
    }

    ఒకవేళ (SDL_ISPIXELFORMAT_FOURCC(src->format)) {
        // Slow!
        ఒకవేళ (!dstrect) {
            నిండిన_dst.x = 0;
            నిండిన_dst.y = 0;
            నిండిన_dst.w = dst->w;
            నిండిన_dst.h = dst->h;
            dstrect = &నిండిన_dst;
        }

        SDL_Surface *src_tmp = SDL_ConvertSurface(src, SDL_PIXELFORMAT_XRGB8888);
        SDL_Surface *dst_tmp = SDL_CreateSurfaceUninitialized(dstrect->w, dstrect->h, SDL_PIXELFORMAT_XRGB8888);
        ఒకవేళ (src_tmp && dst_tmp) {
            ఫలితం = SDL_StretchSurface(src_tmp, srcrect, dst_tmp, ఖాళీ, scale_బహుళకం);
            ఒకవేళ (ఫలితం) {
                ఫలితం = SDL_ConvertPixelsAndColorspace(dstrect->w, dstrect->h,
                            dst_tmp->format, SDL_COLORSPACE_SRGB, 0,
                            dst_tmp->pixels, dst_tmp->pitch,
                            dst->format, dst->colorspace, SDL_GetSurfaceProperties(dst),
                            (Uint8 *)dst->pixels + dstrect->y * dst->pitch + dstrect->x * SDL_BYTESPERPIXEL(dst->format), dst->pitch);
            }
        } లేకపోతే {
            ఫలితం = false;
        }
        SDL_DestroySurface(src_tmp);
        SDL_DestroySurface(dst_tmp);
        తిరిగి ఫలితం;
    }

    ఎంపిక (scale_బహుళకం) {
    స్థితి SDL_SCALEMODE_సమీప:
        ఆపు;
    స్థితి SDL_SCALEMODE_రేఖీయ:
        ఆపు;
    స్థితి SDL_SCALEMODE_PIXELART:
        scale_బహుళకం = SDL_SCALEMODE_సమీప;
        ఆపు;
    అప్రమేయ:
        తిరిగి SDL_InvalidParamError("scaleMode");
    }

    ఒకవేళ (scale_బహుళకం == SDL_SCALEMODE_రేఖీయ) {
        ఒకవేళ (SDL_BYTESPERPIXEL(src->format) != 4 || src->format == SDL_PIXELFORMAT_ARGB2101010) {
            తిరిగి SDL_సమితి_Error("Wrong format");
        }
    }

    // Verify the blit rectangles
    ఒకవేళ (srcrect) {
        ఒకవేళ ((srcrect->x < 0) || (srcrect->y < 0) ||
            ((srcrect->x + srcrect->w) > src->w) ||
            ((srcrect->y + srcrect->h) > src->h)) {
            తిరిగి SDL_సమితి_Error("Invalid source blit rectangle");
        }
    } లేకపోతే {
        నిండిన_src.x = 0;
        నిండిన_src.y = 0;
        నిండిన_src.w = src->w;
        నిండిన_src.h = src->h;
        srcrect = &నిండిన_src;
    }
    ఒకవేళ (dstrect) {
        ఒకవేళ ((dstrect->x < 0) || (dstrect->y < 0) ||
            ((dstrect->x + dstrect->w) > dst->w) ||
            ((dstrect->y + dstrect->h) > dst->h)) {
            తిరిగి SDL_సమితి_Error("Invalid destination blit rectangle");
        }
    } లేకపోతే {
        నిండిన_dst.x = 0;
        నిండిన_dst.y = 0;
        నిండిన_dst.w = dst->w;
        నిండిన_dst.h = dst->h;
        dstrect = &నిండిన_dst;
    }

    ఒకవేళ (dstrect->w <= 0 || dstrect->h <= 0) {
        తిరిగి true;
    }

    ఒకవేళ (srcrect->w > SDL_MAX_UINT16 || srcrect->h > SDL_MAX_UINT16 ||
        dstrect->w > SDL_MAX_UINT16 || dstrect->h > SDL_MAX_UINT16) {
        తిరిగి SDL_సమితి_Error("Size too large for scaling");
    }

    // Lock the destination if it's in hardware
    dst_locked = 0;
    ఒకవేళ (SDL_MUSTLOCK(dst)) {
        ఒకవేళ (!SDL_తాళం_Surface(dst)) {
            తిరిగి SDL_సమితి_Error("Unable to lock destination surface");
        }
        dst_locked = 1;
    }
    // Lock the source if it's in hardware
    src_locked = 0;
    ఒకవేళ (SDL_MUSTLOCK(src)) {
        ఒకవేళ (!SDL_తాళం_Surface(src)) {
            ఒకవేళ (dst_locked) {
                SDL_UnlockSurface(dst);
            }
            తిరిగి SDL_సమితి_Error("Unable to lock source surface");
        }
        src_locked = 1;
    }

    ఒకవేళ (scale_బహుళకం == SDL_SCALEMODE_సమీప) {
        ఫలితం = SDL_Stretch_Surface_Unchecked_సమీప(src, srcrect, dst, dstrect);
    } లేకపోతే {
        ఫలితం = SDL_Stretch_Surface_Unchecked_రేఖీయ(src, srcrect, dst, dstrect);
    }

    // We need to unlock the surfaces if they're locked
    ఒకవేళ (dst_locked) {
        SDL_UnlockSurface(dst);
    }
    ఒకవేళ (src_locked) {
        SDL_UnlockSurface(src);
    }

    తిరిగి ఫలితం;
}

/* bilinear interpolation precision must be < 8
   Because with SSE: add-multiply: _mm_madd_epi16 works with signed int
   so pixels 0xb1...... are negatives and false the result
   same in NEON probably */
#నిర్వచించు PRECISION 7

#నిర్వచించు FIXED_బిందువు(i) ((Uint32)(i) << 16)
#నిర్వచించు SRC_సూచీ(fp)  ((Uint32)(fp) >> 16)
#నిర్వచించు INTEGER(fp)    ((Uint32)(fp) >> PRECISION)
#నిర్వచించు FRAC(fp)       ((Uint32)((fp) >> (16 - PRECISION)) & ((1 << PRECISION) - 1))
#నిర్వచించు FRAC_ZERO      0
#నిర్వచించు FRAC_ONE       (1 << PRECISION)
#నిర్వచించు FP_ONE         FIXED_బిందువు(1)

#నిర్వచించు BILINEAR_ప్రారంభం                                                              \
    పూర్ణాంకం i;                                                                            \
    Sint64 fp_కూడిక_h;                                                                  \
    పూర్ణాంకం fp_అడుగు_h, ఎడమ_pad_h, కుడి_pad_h;                                           \
    Sint64 fp_కూడిక_w;                                                                  \
    పూర్ణాంకం fp_అడుగు_w, ఎడమ_pad_w, కుడి_pad_w;                                           \
    Sint64 fp_కూడిక_w_init;                                                             \
    పూర్ణాంకం ఎడమ_pad_w_init, కుడి_pad_w_init, dst_gap, మధ్య_init;                      \
    get_scaler_datas(src_h, dst_h, &fp_కూడిక_h, &fp_అడుగు_h, &ఎడమ_pad_h, &కుడి_pad_h); \
    get_scaler_datas(src_w, dst_w, &fp_కూడిక_w, &fp_అడుగు_w, &ఎడమ_pad_w, &కుడి_pad_w); \
    fp_కూడిక_w_init = fp_కూడిక_w + ఎడమ_pad_w * fp_అడుగు_w;                                \
    ఎడమ_pad_w_init = ఎడమ_pad_w;                                                     \
    కుడి_pad_w_init = కుడి_pad_w;                                                   \
    dst_gap = dst_pitch - 4 * dst_w;                                                  \
    మధ్య_init = dst_w - ఎడమ_pad_w - కుడి_pad_w;

#నిర్వచించు BILINEAR_ఎత్తు                                              \
    పూర్ణాంకం సూచీ_h, frac_h0, frac_h1, మధ్య;                             \
    స్థిరరాశి Uint32 *src_h0, *src_h1;                                     \
    పూర్ణాంకం no_padding;                                                    \
    Uint64 incr_h0, incr_h1;                                           \
                                                                       \
    no_padding = !(i < ఎడమ_pad_h || i > dst_h - 1 - కుడి_pad_h);     \
    సూచీ_h = SRC_సూచీ(fp_కూడిక_h);                                     \
    frac_h0 = FRAC(fp_కూడిక_h);                                          \
                                                                       \
    సూచీ_h = no_padding ? సూచీ_h : (i < ఎడమ_pad_h ? 0 : src_h - 1); \
    frac_h0 = no_padding ? frac_h0 : 0;                                \
    incr_h1 = no_padding ? src_pitch : 0;                              \
    incr_h0 = (Uint64)సూచీ_h * src_pitch;                             \
                                                                       \
    src_h0 = (స్థిరరాశి Uint32 *)((స్థిరరాశి Uint8 *)src + incr_h0);           \
    src_h1 = (స్థిరరాశి Uint32 *)((స్థిరరాశి Uint8 *)src_h0 + incr_h1);        \
                                                                       \
    fp_కూడిక_h += fp_అడుగు_h;                                             \
                                                                       \
    frac_h1 = FRAC_ONE - frac_h0;                                      \
    fp_కూడిక_w = fp_కూడిక_w_init;                                          \
    కుడి_pad_w = కుడి_pad_w_init;                                    \
    ఎడమ_pad_w = ఎడమ_pad_w_init;                                      \
    మధ్య = మధ్య_init;

#నిర్వచితమైతే __clang__
// Remove inlining of this function
// Compiler crash with clang 9.0.8 / android-ndk-r21d
// Compiler crash with clang 11.0.3 / Xcode
// OK with clang 11.0.5 / android-ndk-22
// OK with clang 12.0.0 / Xcode
__attribute__((noinline))
#అయితే_ముగింపు
స్థిర శూన్య get_scaler_datas(పూర్ణాంకం src_nb, పూర్ణాంకం dst_nb, Sint64 *fp_ప్రారంభం, పూర్ణాంకం *fp_అడుగు, పూర్ణాంకం *ఎడమ_pad, పూర్ణాంకం *కుడి_pad)
{

    పూర్ణాంకం అడుగు = FIXED_బిందువు(src_nb) / (dst_nb); // source step in fixed point
    పూర్ణాంకం x0 = FP_ONE / 2;                       // dst first pixel center at 0.5 in fixed point
    Sint64 fp_కూడిక;
    పూర్ణాంకం i;
#ఒకవేళ 0
    // scale to source coordinates
    x0 *= src_nb;
    x0 /= dst_nb; // x0 == step / 2
#లేకపోతే
    // Use this code for perfect match with pixman
    Sint64 tmp[2];
    tmp[0] = (Sint64)అడుగు * (x0 >> 16);
    tmp[1] = (Sint64)అడుగు * (x0 & 0xFFFF);
    x0 = (పూర్ణాంకం)(tmp[0] + ((tmp[1] + 0x8000) >> 16)); // x0 == (step + 1) / 2
#అయితే_ముగింపు
    // -= 0.5, get back the pixel origin, in source coordinates
    x0 -= FP_ONE / 2;

    *fp_ప్రారంభం = x0;
    *fp_అడుగు = అడుగు;
    *ఎడమ_pad = 0;
    *కుడి_pad = 0;

    fp_కూడిక = x0;
    కొరకు (i = 0; i < dst_nb; i++) {
        ఒకవేళ (fp_కూడిక < 0) {
            *ఎడమ_pad += 1;
        } లేకపోతే {
            పూర్ణాంకం సూచీ = SRC_సూచీ(fp_కూడిక);
            ఒకవేళ (సూచీ > src_nb - 2) {
                *కుడి_pad += 1;
            }
        }
        fp_కూడిక += అడుగు;
    }
    //    SDL_Log("%d -> %d  x0=%d step=%d left_pad=%d right_pad=%d", src_nb, dst_nb, *fp_start, *fp_step, *left_pad, *right_pad);
}

రకనిర్వచనం నిర్మాణం color_t
{
    Uint8 a;
    Uint8 b;
    Uint8 c;
    Uint8 d;
} color_t;

/* Interpolated == x0 + frac * (x1 - x0) == x0 * (1 - frac) + x1 * frac */

స్థిర SDL_INLINE శూన్య INTERPOL(స్థిరరాశి Uint32 *src_x0, స్థిరరాశి Uint32 *src_x1, పూర్ణాంకం frac0, పూర్ణాంకం frac1, Uint32 *dst)
{
    స్థిరరాశి color_t *c0 = (స్థిరరాశి color_t *)src_x0;
    స్థిరరాశి color_t *c1 = (స్థిరరాశి color_t *)src_x1;
    color_t *cx = (color_t *)dst;
#ఒకవేళ 0
    cx->a = c0->a + INTEGER(frac0 * (c1->a - c0->a));
    cx->b = c0->b + INTEGER(frac0 * (c1->b - c0->b));
    cx->c = c0->c + INTEGER(frac0 * (c1->c - c0->c));
    cx->d = c0->d + INTEGER(frac0 * (c1->d - c0->d));
#లేకపోతే
    cx->a = (Uint8)INTEGER(frac1 * c0->a + frac0 * c1->a);
    cx->b = (Uint8)INTEGER(frac1 * c0->b + frac0 * c1->b);
    cx->c = (Uint8)INTEGER(frac1 * c0->c + frac0 * c1->c);
    cx->d = (Uint8)INTEGER(frac1 * c0->d + frac0 * c1->d);
#అయితే_ముగింపు
}

స్థిర SDL_INLINE శూన్య INTERPOL_BILINEAR(స్థిరరాశి Uint32 *s0, స్థిరరాశి Uint32 *s1, పూర్ణాంకం frac_w0, పూర్ణాంకం frac_h0, పూర్ణాంకం frac_h1, Uint32 *dst)
{
    Uint32 tmp[2];
    గుర్తులేని పూర్ణాంకం frac_w1 = FRAC_ONE - frac_w0;

    // Vertical first, store to 'tmp'
    INTERPOL(s0, s1, frac_h0, frac_h1, tmp);
    INTERPOL(s0 + 1, s1 + 1, frac_h0, frac_h1, tmp + 1);

    // Horizontal, store to 'dst'
    INTERPOL(tmp, tmp + 1, frac_w0, frac_w1, dst);
}

స్థిర bool scale_mat(స్థిరరాశి Uint32 *src, పూర్ణాంకం src_w, పూర్ణాంకం src_h, పూర్ణాంకం src_pitch, Uint32 *dst, పూర్ణాంకం dst_w, పూర్ణాంకం dst_h, పూర్ణాంకం dst_pitch)
{
    BILINEAR_ప్రారంభం

    కొరకు (i = 0; i < dst_h; i++) {

        BILINEAR_ఎత్తు

        అయితే (ఎడమ_pad_w--) {
            INTERPOL_BILINEAR(src_h0, src_h1, FRAC_ZERO, frac_h0, frac_h1, dst);
            dst += 1;
        }

        అయితే (మధ్య--) {
            స్థిరరాశి Uint32 *s_00_01;
            స్థిరరాశి Uint32 *s_10_11;
            పూర్ణాంకం సూచీ_w = 4 * SRC_సూచీ(fp_కూడిక_w);
            పూర్ణాంకం frac_w = FRAC(fp_కూడిక_w);
            fp_కూడిక_w += fp_అడుగు_w;

            /*
                        x00 ... x0_ ..... x01
                        .       .         .
                        .       x         .
                        .       .         .
                        .       .         .
                        x10 ... x1_ ..... x11
            */
            s_00_01 = (స్థిరరాశి Uint32 *)((స్థిరరాశి Uint8 *)src_h0 + సూచీ_w);
            s_10_11 = (స్థిరరాశి Uint32 *)((స్థిరరాశి Uint8 *)src_h1 + సూచీ_w);

            INTERPOL_BILINEAR(s_00_01, s_10_11, frac_w, frac_h0, frac_h1, dst);

            dst += 1;
        }

        అయితే (కుడి_pad_w--) {
            పూర్ణాంకం సూచీ_w = 4 * (src_w - 2);
            స్థిరరాశి Uint32 *s_00_01 = (స్థిరరాశి Uint32 *)((స్థిరరాశి Uint8 *)src_h0 + సూచీ_w);
            స్థిరరాశి Uint32 *s_10_11 = (స్థిరరాశి Uint32 *)((స్థిరరాశి Uint8 *)src_h1 + సూచీ_w);
            INTERPOL_BILINEAR(s_00_01, s_10_11, FRAC_ONE, frac_h0, frac_h1, dst);
            dst += 1;
        }
        dst = (Uint32 *)((Uint8 *)dst + dst_gap);
    }
    తిరిగి true;
}

#నిర్వచితమైతే SDL_SSE2_INTRINSICS

స్థిర SDL_INLINE పూర్ణాంకం hasSSE2(శూన్య)
{
    స్థిర పూర్ణాంకం val = -1;
    ఒకవేళ (val != -1) {
        తిరిగి val;
    }
    val = SDL_HasSSE2();
    తిరిగి val;
}

స్థిర SDL_INLINE శూన్య SDL_TARGETING("sse2") INTERPOL_BILINEAR_SSE(స్థిరరాశి Uint32 *s0, స్థిరరాశి Uint32 *s1, పూర్ణాంకం frac_w, __m128i v_frac_h0, __m128i v_frac_h1, Uint32 *dst, __m128i zero)
{
    __m128i x_00_01, x_10_11; /* Pixels in 4*uint8 in row */
    __m128i v_frac_w0, k0, l0, d0, e0;

    పూర్ణాంకం f, f2;
    f = frac_w;
    f2 = FRAC_ONE - frac_w;
    v_frac_w0 = mm_సమితి_epi16((పొట్టి)f, (పొట్టి)f2, (పొట్టి)f, (పొట్టి)f2, (పొట్టి)f, (పొట్టి)f2, (పొట్టి)f, (పొట్టి)f2);

    x_00_01 = _mm_loadl_epi64((స్థిరరాశి __m128i *)s0); // Load x00 and x01
    x_10_11 = _mm_loadl_epi64((స్థిరరాశి __m128i *)s1);

    /* Interpolated == x0 + frac * (x1 - x0) == x0 * (1 - frac) + x1 * frac */

    // Interpolation vertical
    k0 = _mm_mullo_epi16(_mm_unpacklo_epi8(x_00_01, zero), v_frac_h1);
    l0 = _mm_mullo_epi16(_mm_unpacklo_epi8(x_10_11, zero), v_frac_h0);
    k0 = mm_కూడు_epi16(k0, l0);

    // For perfect match, clear the factionnal part eventually.
    /*
    k0 = _mm_srli_epi16(k0, PRECISION);
    k0 = _mm_slli_epi16(k0, PRECISION);
    */

    // Interpolation horizontal
    l0 = _mm_unpacklo_epi64(/*వాడని*/ l0, k0);
    k0 = _mm_madd_epi16(_mm_unpackhi_epi16(l0, k0), v_frac_w0);

    // Store 1 pixel
    d0 = _mm_srli_epi32(k0, PRECISION * 2);
    e0 = _mm_packs_epi32(d0, d0);
    e0 = _mm_packus_epi16(e0, e0);
    *dst = _mm_cvtsi128_si32(e0);
}

స్థిర bool SDL_TARGETING("sse2") scale_mat_SSE(స్థిరరాశి Uint32 *src, పూర్ణాంకం src_w, పూర్ణాంకం src_h, పూర్ణాంకం src_pitch, Uint32 *dst, పూర్ణాంకం dst_w, పూర్ణాంకం dst_h, పూర్ణాంకం dst_pitch)
{
    BILINEAR_ప్రారంభం

    కొరకు (i = 0; i < dst_h; i++) {
        పూర్ణాంకం nb_block2;
        __m128i v_frac_h0;
        __m128i v_frac_h1;
        __m128i zero;

        BILINEAR_ఎత్తు

        nb_block2 = మధ్య / 2;

        v_frac_h0 = mm_సమితి_epi16((పొట్టి)frac_h0, (పొట్టి)frac_h0, (పొట్టి)frac_h0, (పొట్టి)frac_h0, (పొట్టి)frac_h0, (పొట్టి)frac_h0, (పొట్టి)frac_h0, (పొట్టి)frac_h0);
        v_frac_h1 = mm_సమితి_epi16((పొట్టి)frac_h1, (పొట్టి)frac_h1, (పొట్టి)frac_h1, (పొట్టి)frac_h1, (పొట్టి)frac_h1, (పొట్టి)frac_h1, (పొట్టి)frac_h1, (పొట్టి)frac_h1);
        zero = _mm_setzero_si128();

        అయితే (ఎడమ_pad_w--) {
            INTERPOL_BILINEAR_SSE(src_h0, src_h1, FRAC_ZERO, v_frac_h0, v_frac_h1, dst, zero);
            dst += 1;
        }

        అయితే (nb_block2--) {
            పూర్ణాంకం సూచీ_w_0, frac_w_0;
            పూర్ణాంకం సూచీ_w_1, frac_w_1;

            స్థిరరాశి Uint32 *s_00_01, *s_02_03, *s_10_11, *s_12_13;

            __m128i x_00_01, x_10_11, x_02_03, x_12_13; /* Pixels in 4*uint8 in row */
            __m128i v_frac_w0, k0, l0, d0, e0;
            __m128i v_frac_w1, k1, l1, d1, e1;

            పూర్ణాంకం f, f2;
            సూచీ_w_0 = 4 * SRC_సూచీ(fp_కూడిక_w);
            frac_w_0 = FRAC(fp_కూడిక_w);
            fp_కూడిక_w += fp_అడుగు_w;
            సూచీ_w_1 = 4 * SRC_సూచీ(fp_కూడిక_w);
            frac_w_1 = FRAC(fp_కూడిక_w);
            fp_కూడిక_w += fp_అడుగు_w;
            /*
                        x00............ x01   x02...........x03
                        .      .         .     .       .     .
                        j0     f0        j1    j2      f1    j3
                        .      .         .     .       .     .
                        .      .         .     .       .     .
                        .      .         .     .       .     .
                        x10............ x11   x12...........x13
             */
            s_00_01 = (స్థిరరాశి Uint32 *)((స్థిరరాశి Uint8 *)src_h0 + సూచీ_w_0);
            s_02_03 = (స్థిరరాశి Uint32 *)((స్థిరరాశి Uint8 *)src_h0 + సూచీ_w_1);
            s_10_11 = (స్థిరరాశి Uint32 *)((స్థిరరాశి Uint8 *)src_h1 + సూచీ_w_0);
            s_12_13 = (స్థిరరాశి Uint32 *)((స్థిరరాశి Uint8 *)src_h1 + సూచీ_w_1);

            f = frac_w_0;
            f2 = FRAC_ONE - frac_w_0;
            v_frac_w0 = mm_సమితి_epi16((పొట్టి)f, (పొట్టి)f2, (పొట్టి)f, (పొట్టి)f2, (పొట్టి)f, (పొట్టి)f2, (పొట్టి)f, (పొట్టి)f2);

            f = frac_w_1;
            f2 = FRAC_ONE - frac_w_1;
            v_frac_w1 = mm_సమితి_epi16((పొట్టి)f, (పొట్టి)f2, (పొట్టి)f, (పొట్టి)f2, (పొట్టి)f, (పొట్టి)f2, (పొట్టి)f, (పొట్టి)f2);

            x_00_01 = _mm_loadl_epi64((స్థిరరాశి __m128i *)s_00_01); // Load x00 and x01
            x_02_03 = _mm_loadl_epi64((స్థిరరాశి __m128i *)s_02_03);
            x_10_11 = _mm_loadl_epi64((స్థిరరాశి __m128i *)s_10_11);
            x_12_13 = _mm_loadl_epi64((స్థిరరాశి __m128i *)s_12_13);

            // Interpolation vertical
            k0 = _mm_mullo_epi16(_mm_unpacklo_epi8(x_00_01, zero), v_frac_h1);
            l0 = _mm_mullo_epi16(_mm_unpacklo_epi8(x_10_11, zero), v_frac_h0);
            k0 = mm_కూడు_epi16(k0, l0);
            k1 = _mm_mullo_epi16(_mm_unpacklo_epi8(x_02_03, zero), v_frac_h1);
            l1 = _mm_mullo_epi16(_mm_unpacklo_epi8(x_12_13, zero), v_frac_h0);
            k1 = mm_కూడు_epi16(k1, l1);

            // Interpolation horizontal
            l0 = _mm_unpacklo_epi64(/*వాడని*/ l0, k0);
            k0 = _mm_madd_epi16(_mm_unpackhi_epi16(l0, k0), v_frac_w0);
            l1 = _mm_unpacklo_epi64(/*వాడని*/ l1, k1);
            k1 = _mm_madd_epi16(_mm_unpackhi_epi16(l1, k1), v_frac_w1);

            // Store 1 pixel
            d0 = _mm_srli_epi32(k0, PRECISION * 2);
            e0 = _mm_packs_epi32(d0, d0);
            e0 = _mm_packus_epi16(e0, e0);
            *dst++ = _mm_cvtsi128_si32(e0);

            // Store 1 pixel
            d1 = _mm_srli_epi32(k1, PRECISION * 2);
            e1 = _mm_packs_epi32(d1, d1);
            e1 = _mm_packus_epi16(e1, e1);
            *dst++ = _mm_cvtsi128_si32(e1);
        }

        // Last point
        ఒకవేళ (మధ్య & 0x1) {
            స్థిరరాశి Uint32 *s_00_01;
            స్థిరరాశి Uint32 *s_10_11;
            పూర్ణాంకం సూచీ_w = 4 * SRC_సూచీ(fp_కూడిక_w);
            పూర్ణాంకం frac_w = FRAC(fp_కూడిక_w);
            fp_కూడిక_w += fp_అడుగు_w;
            s_00_01 = (స్థిరరాశి Uint32 *)((స్థిరరాశి Uint8 *)src_h0 + సూచీ_w);
            s_10_11 = (స్థిరరాశి Uint32 *)((స్థిరరాశి Uint8 *)src_h1 + సూచీ_w);
            INTERPOL_BILINEAR_SSE(s_00_01, s_10_11, frac_w, v_frac_h0, v_frac_h1, dst, zero);
            dst += 1;
        }

        అయితే (కుడి_pad_w--) {
            పూర్ణాంకం సూచీ_w = 4 * (src_w - 2);
            స్థిరరాశి Uint32 *s_00_01 = (స్థిరరాశి Uint32 *)((స్థిరరాశి Uint8 *)src_h0 + సూచీ_w);
            స్థిరరాశి Uint32 *s_10_11 = (స్థిరరాశి Uint32 *)((స్థిరరాశి Uint8 *)src_h1 + సూచీ_w);
            INTERPOL_BILINEAR_SSE(s_00_01, s_10_11, FRAC_ONE, v_frac_h0, v_frac_h1, dst, zero);
            dst += 1;
        }
        dst = (Uint32 *)((Uint8 *)dst + dst_gap);
    }
    తిరిగి true;
}
#అయితే_ముగింపు

#నిర్వచితమైతే SDL_NEON_INTRINSICS

స్థిర SDL_INLINE పూర్ణాంకం hasNEON(శూన్య)
{
    స్థిర పూర్ణాంకం val = -1;
    ఒకవేళ (val != -1) {
        తిరిగి val;
    }
    val = SDL_HasNEON();
    తిరిగి val;
}

స్థిర SDL_INLINE శూన్య INTERPOL_BILINEAR_NEON(స్థిరరాశి Uint32 *s0, స్థిరరాశి Uint32 *s1, పూర్ణాంకం frac_w, uint8x8_t v_frac_h0, uint8x8_t v_frac_h1, Uint32 *dst)
{
    uint8x8_t x_00_01, x_10_11; /* Pixels in 4*uint8 in row */
    uint16x8_t k0;
    uint32x4_t l0;
    uint16x8_t d0;
    uint8x8_t e0;

    x_00_01 = vreinterpret_u8_u32(vld1_u32(s0)); // Load 2 pixels
    x_10_11 = vreinterpret_u8_u32(vld1_u32(s1));

    /* Interpolated == x0 + frac * (x1 - x0) == x0 * (1 - frac) + x1 * frac */
    k0 = vmull_u8(x_00_01, v_frac_h1);     /* k0 := x0 * (1 - frac)    */
    k0 = vmlal_u8(k0, x_10_11, v_frac_h0); /* k0 += x1 * frac          */

    // k0 now contains 2 interpolated pixels { j0, j1 }
    l0 = vshll_n_u16(vget_దిగువ_u16(k0), PRECISION);
    l0 = vmlsl_n_u16(l0, vget_దిగువ_u16(k0), frac_w);
    l0 = vmlal_n_u16(l0, vget_ఎగువ_u16(k0), frac_w);

    // Shift and narrow
    d0 = vcombine_u16(
        /* uint16x4_t */ vshrn_n_u32(l0, 2 * PRECISION),
        /* uint16x4_t */ vshrn_n_u32(l0, 2 * PRECISION));

    // Narrow again
    e0 = vmovn_u16(d0);

    // Store 1 pixel
    *dst = vget_lane_u32(vreinterpret_u32_u8(e0), 0);
}

స్థిర bool scale_mat_NEON(స్థిరరాశి Uint32 *src, పూర్ణాంకం src_w, పూర్ణాంకం src_h, పూర్ణాంకం src_pitch, Uint32 *dst, పూర్ణాంకం dst_w, పూర్ణాంకం dst_h, పూర్ణాంకం dst_pitch)
{
    BILINEAR_ప్రారంభం

    కొరకు (i = 0; i < dst_h; i++) {
        పూర్ణాంకం nb_block4;
        uint8x8_t v_frac_h0, v_frac_h1;

        BILINEAR_ఎత్తు

        nb_block4 = మధ్య / 4;

        v_frac_h0 = vmov_n_u8(frac_h0);
        v_frac_h1 = vmov_n_u8(frac_h1);

        అయితే (ఎడమ_pad_w--) {
            INTERPOL_BILINEAR_NEON(src_h0, src_h1, FRAC_ZERO, v_frac_h0, v_frac_h1, dst);
            dst += 1;
        }

        అయితే (nb_block4--) {
            పూర్ణాంకం సూచీ_w_0, frac_w_0;
            పూర్ణాంకం సూచీ_w_1, frac_w_1;
            పూర్ణాంకం సూచీ_w_2, frac_w_2;
            పూర్ణాంకం సూచీ_w_3, frac_w_3;

            స్థిరరాశి Uint32 *s_00_01, *s_02_03, *s_04_05, *s_06_07;
            స్థిరరాశి Uint32 *s_10_11, *s_12_13, *s_14_15, *s_16_17;

            uint8x8_t x_00_01, x_10_11, x_02_03, x_12_13; /* Pixels in 4*uint8 in row */
            uint8x8_t x_04_05, x_14_15, x_06_07, x_16_17;

            uint16x8_t k0, k1, k2, k3;
            uint32x4_t l0, l1, l2, l3;
            uint16x8_t d0, d1;
            uint8x8_t e0, e1;
            uint32x4_t f0;

            సూచీ_w_0 = 4 * SRC_సూచీ(fp_కూడిక_w);
            frac_w_0 = FRAC(fp_కూడిక_w);
            fp_కూడిక_w += fp_అడుగు_w;
            సూచీ_w_1 = 4 * SRC_సూచీ(fp_కూడిక_w);
            frac_w_1 = FRAC(fp_కూడిక_w);
            fp_కూడిక_w += fp_అడుగు_w;
            సూచీ_w_2 = 4 * SRC_సూచీ(fp_కూడిక_w);
            frac_w_2 = FRAC(fp_కూడిక_w);
            fp_కూడిక_w += fp_అడుగు_w;
            సూచీ_w_3 = 4 * SRC_సూచీ(fp_కూడిక_w);
            frac_w_3 = FRAC(fp_కూడిక_w);
            fp_కూడిక_w += fp_అడుగు_w;

            s_00_01 = (స్థిరరాశి Uint32 *)((స్థిరరాశి Uint8 *)src_h0 + సూచీ_w_0);
            s_02_03 = (స్థిరరాశి Uint32 *)((స్థిరరాశి Uint8 *)src_h0 + సూచీ_w_1);
            s_04_05 = (స్థిరరాశి Uint32 *)((స్థిరరాశి Uint8 *)src_h0 + సూచీ_w_2);
            s_06_07 = (స్థిరరాశి Uint32 *)((స్థిరరాశి Uint8 *)src_h0 + సూచీ_w_3);
            s_10_11 = (స్థిరరాశి Uint32 *)((స్థిరరాశి Uint8 *)src_h1 + సూచీ_w_0);
            s_12_13 = (స్థిరరాశి Uint32 *)((స్థిరరాశి Uint8 *)src_h1 + సూచీ_w_1);
            s_14_15 = (స్థిరరాశి Uint32 *)((స్థిరరాశి Uint8 *)src_h1 + సూచీ_w_2);
            s_16_17 = (స్థిరరాశి Uint32 *)((స్థిరరాశి Uint8 *)src_h1 + సూచీ_w_3);

            // Interpolation vertical
            x_00_01 = vreinterpret_u8_u32(vld1_u32(s_00_01)); // Load 2 pixels
            x_02_03 = vreinterpret_u8_u32(vld1_u32(s_02_03));
            x_04_05 = vreinterpret_u8_u32(vld1_u32(s_04_05));
            x_06_07 = vreinterpret_u8_u32(vld1_u32(s_06_07));
            x_10_11 = vreinterpret_u8_u32(vld1_u32(s_10_11));
            x_12_13 = vreinterpret_u8_u32(vld1_u32(s_12_13));
            x_14_15 = vreinterpret_u8_u32(vld1_u32(s_14_15));
            x_16_17 = vreinterpret_u8_u32(vld1_u32(s_16_17));

            /* Interpolated == x0 + frac * (x1 - x0) == x0 * (1 - frac) + x1 * frac */
            k0 = vmull_u8(x_00_01, v_frac_h1);     /* k0 := x0 * (1 - frac)    */
            k0 = vmlal_u8(k0, x_10_11, v_frac_h0); /* k0 += x1 * frac          */

            k1 = vmull_u8(x_02_03, v_frac_h1);
            k1 = vmlal_u8(k1, x_12_13, v_frac_h0);

            k2 = vmull_u8(x_04_05, v_frac_h1);
            k2 = vmlal_u8(k2, x_14_15, v_frac_h0);

            k3 = vmull_u8(x_06_07, v_frac_h1);
            k3 = vmlal_u8(k3, x_16_17, v_frac_h0);

            // k0 now contains 2 interpolated pixels { j0, j1 }
            // k1 now contains 2 interpolated pixels { j2, j3 }
            // k2 now contains 2 interpolated pixels { j4, j5 }
            // k3 now contains 2 interpolated pixels { j6, j7 }

            l0 = vshll_n_u16(vget_దిగువ_u16(k0), PRECISION);
            l0 = vmlsl_n_u16(l0, vget_దిగువ_u16(k0), frac_w_0);
            l0 = vmlal_n_u16(l0, vget_ఎగువ_u16(k0), frac_w_0);

            l1 = vshll_n_u16(vget_దిగువ_u16(k1), PRECISION);
            l1 = vmlsl_n_u16(l1, vget_దిగువ_u16(k1), frac_w_1);
            l1 = vmlal_n_u16(l1, vget_ఎగువ_u16(k1), frac_w_1);

            l2 = vshll_n_u16(vget_దిగువ_u16(k2), PRECISION);
            l2 = vmlsl_n_u16(l2, vget_దిగువ_u16(k2), frac_w_2);
            l2 = vmlal_n_u16(l2, vget_ఎగువ_u16(k2), frac_w_2);

            l3 = vshll_n_u16(vget_దిగువ_u16(k3), PRECISION);
            l3 = vmlsl_n_u16(l3, vget_దిగువ_u16(k3), frac_w_3);
            l3 = vmlal_n_u16(l3, vget_ఎగువ_u16(k3), frac_w_3);

            // shift and narrow
            d0 = vcombine_u16(
                /* uint16x4_t */ vshrn_n_u32(l0, 2 * PRECISION),
                /* uint16x4_t */ vshrn_n_u32(l1, 2 * PRECISION));
            // narrow again
            e0 = vmovn_u16(d0);

            // Shift and narrow
            d1 = vcombine_u16(
                /* uint16x4_t */ vshrn_n_u32(l2, 2 * PRECISION),
                /* uint16x4_t */ vshrn_n_u32(l3, 2 * PRECISION));
            // Narrow again
            e1 = vmovn_u16(d1);

            f0 = vcombine_u32(vreinterpret_u32_u8(e0), vreinterpret_u32_u8(e1));
            // Store 4 pixels
            vst1q_u32(dst, f0);

            dst += 4;
        }

        ఒకవేళ (మధ్య & 0x2) {
            పూర్ణాంకం సూచీ_w_0, frac_w_0;
            పూర్ణాంకం సూచీ_w_1, frac_w_1;
            స్థిరరాశి Uint32 *s_00_01, *s_02_03;
            స్థిరరాశి Uint32 *s_10_11, *s_12_13;
            uint8x8_t x_00_01, x_10_11, x_02_03, x_12_13; /* Pixels in 4*uint8 in row */
            uint16x8_t k0, k1;
            uint32x4_t l0, l1;
            uint16x8_t d0;
            uint8x8_t e0;

            సూచీ_w_0 = 4 * SRC_సూచీ(fp_కూడిక_w);
            frac_w_0 = FRAC(fp_కూడిక_w);
            fp_కూడిక_w += fp_అడుగు_w;
            సూచీ_w_1 = 4 * SRC_సూచీ(fp_కూడిక_w);
            frac_w_1 = FRAC(fp_కూడిక_w);
            fp_కూడిక_w += fp_అడుగు_w;
            /*
                        x00............ x01   x02...........x03
                        .      .         .     .       .     .
                        j0   dest0       j1    j2    dest1   j3
                        .      .         .     .       .     .
                        .      .         .     .       .     .
                        .      .         .     .       .     .
                        x10............ x11   x12...........x13
            */
            s_00_01 = (స్థిరరాశి Uint32 *)((స్థిరరాశి Uint8 *)src_h0 + సూచీ_w_0);
            s_02_03 = (స్థిరరాశి Uint32 *)((స్థిరరాశి Uint8 *)src_h0 + సూచీ_w_1);
            s_10_11 = (స్థిరరాశి Uint32 *)((స్థిరరాశి Uint8 *)src_h1 + సూచీ_w_0);
            s_12_13 = (స్థిరరాశి Uint32 *)((స్థిరరాశి Uint8 *)src_h1 + సూచీ_w_1);

            // Interpolation vertical
            x_00_01 = vreinterpret_u8_u32(vld1_u32(s_00_01)); // Load 2 pixels
            x_02_03 = vreinterpret_u8_u32(vld1_u32(s_02_03));
            x_10_11 = vreinterpret_u8_u32(vld1_u32(s_10_11));
            x_12_13 = vreinterpret_u8_u32(vld1_u32(s_12_13));

            /* Interpolated == x0 + frac * (x1 - x0) == x0 * (1 - frac) + x1 * frac */
            k0 = vmull_u8(x_00_01, v_frac_h1);     /* k0 := x0 * (1 - frac)    */
            k0 = vmlal_u8(k0, x_10_11, v_frac_h0); /* k0 += x1 * frac          */

            k1 = vmull_u8(x_02_03, v_frac_h1);
            k1 = vmlal_u8(k1, x_12_13, v_frac_h0);

            // k0 now contains 2 interpolated pixels { j0, j1 }
            // k1 now contains 2 interpolated pixels { j2, j3 }

            l0 = vshll_n_u16(vget_దిగువ_u16(k0), PRECISION);
            l0 = vmlsl_n_u16(l0, vget_దిగువ_u16(k0), frac_w_0);
            l0 = vmlal_n_u16(l0, vget_ఎగువ_u16(k0), frac_w_0);

            l1 = vshll_n_u16(vget_దిగువ_u16(k1), PRECISION);
            l1 = vmlsl_n_u16(l1, vget_దిగువ_u16(k1), frac_w_1);
            l1 = vmlal_n_u16(l1, vget_ఎగువ_u16(k1), frac_w_1);

            // Shift and narrow

            d0 = vcombine_u16(
                /* uint16x4_t */ vshrn_n_u32(l0, 2 * PRECISION),
                /* uint16x4_t */ vshrn_n_u32(l1, 2 * PRECISION));

            // Narrow again
            e0 = vmovn_u16(d0);

            // Store 2 pixels
            vst1_u32(dst, vreinterpret_u32_u8(e0));
            dst += 2;
        }

        // Last point
        ఒకవేళ (మధ్య & 0x1) {
            పూర్ణాంకం సూచీ_w = 4 * SRC_సూచీ(fp_కూడిక_w);
            పూర్ణాంకం frac_w = FRAC(fp_కూడిక_w);
            స్థిరరాశి Uint32 *s_00_01 = (స్థిరరాశి Uint32 *)((స్థిరరాశి Uint8 *)src_h0 + సూచీ_w);
            స్థిరరాశి Uint32 *s_10_11 = (స్థిరరాశి Uint32 *)((స్థిరరాశి Uint8 *)src_h1 + సూచీ_w);
            INTERPOL_BILINEAR_NEON(s_00_01, s_10_11, frac_w, v_frac_h0, v_frac_h1, dst);
            dst += 1;
        }

        అయితే (కుడి_pad_w--) {
            పూర్ణాంకం సూచీ_w = 4 * (src_w - 2);
            స్థిరరాశి Uint32 *s_00_01 = (స్థిరరాశి Uint32 *)((స్థిరరాశి Uint8 *)src_h0 + సూచీ_w);
            స్థిరరాశి Uint32 *s_10_11 = (స్థిరరాశి Uint32 *)((స్థిరరాశి Uint8 *)src_h1 + సూచీ_w);
            INTERPOL_BILINEAR_NEON(s_00_01, s_10_11, FRAC_ONE, v_frac_h0, v_frac_h1, dst);
            dst += 1;
        }

        dst = (Uint32 *)((Uint8 *)dst + dst_gap);
    }
    తిరిగి true;
}
#అయితే_ముగింపు

bool SDL_Stretch_Surface_Unchecked_రేఖీయ(SDL_Surface *s, స్థిరరాశి SDL_Rect *srcrect, SDL_Surface *d, స్థిరరాశి SDL_Rect *dstrect)
{
    bool ఫలితం = false;
    పూర్ణాంకం src_w = srcrect->w;
    పూర్ణాంకం src_h = srcrect->h;
    పూర్ణాంకం dst_w = dstrect->w;
    పూర్ణాంకం dst_h = dstrect->h;
    పూర్ణాంకం src_pitch = s->pitch;
    పూర్ణాంకం dst_pitch = d->pitch;
    Uint32 *src = (Uint32 *)((Uint8 *)s->pixels + srcrect->x * 4 + srcrect->y * src_pitch);
    Uint32 *dst = (Uint32 *)((Uint8 *)d->pixels + dstrect->x * 4 + dstrect->y * dst_pitch);

#నిర్వచితమైతే SDL_NEON_INTRINSICS
    ఒకవేళ (!ఫలితం && hasNEON()) {
        ఫలితం = scale_mat_NEON(src, src_w, src_h, src_pitch, dst, dst_w, dst_h, dst_pitch);
    }
#అయితే_ముగింపు

#నిర్వచితమైతే SDL_SSE2_INTRINSICS
    ఒకవేళ (!ఫలితం && hasSSE2()) {
        ఫలితం = scale_mat_SSE(src, src_w, src_h, src_pitch, dst, dst_w, dst_h, dst_pitch);
    }
#అయితే_ముగింపు

    ఒకవేళ (!ఫలితం) {
        ఫలితం = scale_mat(src, src_w, src_h, src_pitch, dst, dst_w, dst_h, dst_pitch);
    }

    తిరిగి ఫలితం;
}

#నిర్వచించు SDL_SCALE_సమీప_ప్రారంభం          \
    పూర్ణాంకం i;                                \
    Uint64 posy, incy;                    \
    Uint64 posx, incx;                    \
    Uint64 srcy, srcx;                    \
    పూర్ణాంకం dst_gap, n;                       \
    స్థిరరాశి Uint32 *src_h0;                 \
    incy = ((Uint64)src_h << 16) / dst_h; \
    incx = ((Uint64)src_w << 16) / dst_w; \
    dst_gap = dst_pitch - bpp * dst_w;    \
    posy = incy / 2;

#నిర్వచించు SDL_SCALE_సమీప_ఎత్తు                                         \
    srcy = (posy >> 16);                                                  \
    src_h0 = (స్థిరరాశి Uint32 *)((స్థిరరాశి Uint8 *)src_ptr + srcy * src_pitch); \
    posy += incy;                                                         \
    posx = incx / 2;                                                      \
    n = dst_w;

స్థిర bool scale_mat_సమీప_1(స్థిరరాశి Uint32 *src_ptr, పూర్ణాంకం src_w, పూర్ణాంకం src_h, పూర్ణాంకం src_pitch, Uint32 *dst, పూర్ణాంకం dst_w, పూర్ణాంకం dst_h, పూర్ణాంకం dst_pitch)
{
    Uint32 bpp = 1;
    SDL_SCALE_సమీప_ప్రారంభం
    కొరకు (i = 0; i < dst_h; i++) {
        SDL_SCALE_సమీప_ఎత్తు
        అయితే (n--) {
            స్థిరరాశి Uint8 *src;
            srcx = bpp * (posx >> 16);
            posx += incx;
            src = (స్థిరరాశి Uint8 *)src_h0 + srcx;
            *(Uint8 *)dst = *src;
            dst = (Uint32 *)((Uint8 *)dst + bpp);
        }
        dst = (Uint32 *)((Uint8 *)dst + dst_gap);
    }
    తిరిగి true;
}

స్థిర bool scale_mat_సమీప_2(స్థిరరాశి Uint32 *src_ptr, పూర్ణాంకం src_w, పూర్ణాంకం src_h, పూర్ణాంకం src_pitch, Uint32 *dst, పూర్ణాంకం dst_w, పూర్ణాంకం dst_h, పూర్ణాంకం dst_pitch)
{
    Uint32 bpp = 2;
    SDL_SCALE_సమీప_ప్రారంభం
    కొరకు (i = 0; i < dst_h; i++) {
        SDL_SCALE_సమీప_ఎత్తు
        అయితే (n--) {
            స్థిరరాశి Uint16 *src;
            srcx = bpp * (posx >> 16);
            posx += incx;
            src = (స్థిరరాశి Uint16 *)((స్థిరరాశి Uint8 *)src_h0 + srcx);
            *(Uint16 *)dst = *src;
            dst = (Uint32 *)((Uint8 *)dst + bpp);
        }
        dst = (Uint32 *)((Uint8 *)dst + dst_gap);
    }
    తిరిగి true;
}

స్థిర bool scale_mat_సమీప_3(స్థిరరాశి Uint32 *src_ptr, పూర్ణాంకం src_w, పూర్ణాంకం src_h, పూర్ణాంకం src_pitch, Uint32 *dst, పూర్ణాంకం dst_w, పూర్ణాంకం dst_h, పూర్ణాంకం dst_pitch)
{
    Uint32 bpp = 3;
    SDL_SCALE_సమీప_ప్రారంభం
    కొరకు (i = 0; i < dst_h; i++) {
        SDL_SCALE_సమీప_ఎత్తు
        అయితే (n--) {
            స్థిరరాశి Uint8 *src;
            srcx = bpp * (posx >> 16);
            posx += incx;
            src = (స్థిరరాశి Uint8 *)src_h0 + srcx;
            ((Uint8 *)dst)[0] = src[0];
            ((Uint8 *)dst)[1] = src[1];
            ((Uint8 *)dst)[2] = src[2];
            dst = (Uint32 *)((Uint8 *)dst + bpp);
        }
        dst = (Uint32 *)((Uint8 *)dst + dst_gap);
    }
    తిరిగి true;
}

స్థిర bool scale_mat_సమీప_4(స్థిరరాశి Uint32 *src_ptr, పూర్ణాంకం src_w, పూర్ణాంకం src_h, పూర్ణాంకం src_pitch, Uint32 *dst, పూర్ణాంకం dst_w, పూర్ణాంకం dst_h, పూర్ణాంకం dst_pitch)
{
    Uint32 bpp = 4;
    SDL_SCALE_సమీప_ప్రారంభం
    కొరకు (i = 0; i < dst_h; i++) {
        SDL_SCALE_సమీప_ఎత్తు
        అయితే (n--) {
            స్థిరరాశి Uint32 *src;
            srcx = bpp * (posx >> 16);
            posx += incx;
            src = (స్థిరరాశి Uint32 *)((స్థిరరాశి Uint8 *)src_h0 + srcx);
            *dst = *src;
            dst = (Uint32 *)((Uint8 *)dst + bpp);
        }
        dst = (Uint32 *)((Uint8 *)dst + dst_gap);
    }
    తిరిగి true;
}

bool SDL_Stretch_Surface_Unchecked_సమీప(SDL_Surface *s, స్థిరరాశి SDL_Rect *srcrect, SDL_Surface *d, స్థిరరాశి SDL_Rect *dstrect)
{
    పూర్ణాంకం src_w = srcrect->w;
    పూర్ణాంకం src_h = srcrect->h;
    పూర్ణాంకం dst_w = dstrect->w;
    పూర్ణాంకం dst_h = dstrect->h;
    పూర్ణాంకం src_pitch = s->pitch;
    పూర్ణాంకం dst_pitch = d->pitch;
    పూర్ణాంకం bpp = SDL_BYTESPERPIXEL(d->format);

    Uint32 *src = (Uint32 *)((Uint8 *)s->pixels + srcrect->x * bpp + srcrect->y * src_pitch);
    Uint32 *dst = (Uint32 *)((Uint8 *)d->pixels + dstrect->x * bpp + dstrect->y * dst_pitch);

    ఒకవేళ (bpp == 4) {
        తిరిగి scale_mat_సమీప_4(src, src_w, src_h, src_pitch, dst, dst_w, dst_h, dst_pitch);
    } లేకపోతే ఒకవేళ (bpp == 3) {
        తిరిగి scale_mat_సమీప_3(src, src_w, src_h, src_pitch, dst, dst_w, dst_h, dst_pitch);
    } లేకపోతే ఒకవేళ (bpp == 2) {
        తిరిగి scale_mat_సమీప_2(src, src_w, src_h, src_pitch, dst, dst_w, dst_h, dst_pitch);
    } లేకపోతే {
        తిరిగి scale_mat_సమీప_1(src, src_w, src_h, src_pitch, dst, dst_w, dst_h, dst_pitch);
    }
}
