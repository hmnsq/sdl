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
#অন্তর্ভাব "SDL_internal.h"

#অন্তর্ভাব "SDL_surface_c.h"

স্থির bool SDL_StretchSurfaceUncheckedNearest(SDL_Surface *src, ধ্রুবক SDL_Rect *srcrect, SDL_Surface *dst, ধ্রুবক SDL_Rect *dstrect);
স্থির bool SDL_StretchSurfaceUncheckedLinear(SDL_Surface *src, ধ্রুবক SDL_Rect *srcrect, SDL_Surface *dst, ধ্রুবক SDL_Rect *dstrect);

bool SDL_StretchSurface(SDL_Surface *src, ধ্রুবক SDL_Rect *srcrect, SDL_Surface *dst, ধ্রুবক SDL_Rect *dstrect, SDL_ScaleMode scaleMode)
{
    bool ফলাফল;
    পূর্ণসংখ্যা src_locked;
    পূর্ণসংখ্যা dst_locked;
    SDL_Rect full_src;
    SDL_Rect full_dst;

    CHECK_PARAM(!src) {
        ফেরত SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!dst) {
        ফেরত SDL_InvalidParamError("dst");
    }

    যদি (src->format != dst->format) {
        // Slow!
        SDL_Surface *src_tmp = SDL_ConvertSurfaceAndColorspace(src, dst->format, dst->palette, dst->colorspace, dst->props);
        যদি (!src_tmp) {
            ফেরত false;
        }
        ফলাফল = SDL_StretchSurface(src_tmp, srcrect, dst, dstrect, scaleMode);
        SDL_DestroySurface(src_tmp);
        ফেরত ফলাফল;
    }

    যদি (SDL_ISPIXELFORMAT_FOURCC(src->format)) {
        // Slow!
        যদি (!dstrect) {
            full_dst.x = 0;
            full_dst.y = 0;
            full_dst.w = dst->w;
            full_dst.h = dst->h;
            dstrect = &full_dst;
        }

        SDL_Surface *src_tmp = SDL_ConvertSurface(src, SDL_PIXELFORMAT_XRGB8888);
        SDL_Surface *dst_tmp = SDL_CreateSurfaceUninitialized(dstrect->w, dstrect->h, SDL_PIXELFORMAT_XRGB8888);
        যদি (src_tmp && dst_tmp) {
            ফলাফল = SDL_StretchSurface(src_tmp, srcrect, dst_tmp, ফাঁকা, scaleMode);
            যদি (ফলাফল) {
                ফলাফল = SDL_ConvertPixelsAndColorspace(dstrect->w, dstrect->h,
                            dst_tmp->format, SDL_COLORSPACE_SRGB, 0,
                            dst_tmp->pixels, dst_tmp->pitch,
                            dst->format, dst->colorspace, SDL_GetSurfaceProperties(dst),
                            (Uint8 *)dst->pixels + dstrect->y * dst->pitch + dstrect->x * SDL_BYTESPERPIXEL(dst->format), dst->pitch);
            }
        } অন্যথা {
            ফলাফল = false;
        }
        SDL_DestroySurface(src_tmp);
        SDL_DestroySurface(dst_tmp);
        ফেরত ফলাফল;
    }

    নির্বাচন (scaleMode) {
    ক্ষেত্র SDL_SCALEMODE_NEAREST:
        বিরতি;
    ক্ষেত্র SDL_SCALEMODE_LINEAR:
        বিরতি;
    ক্ষেত্র SDL_SCALEMODE_PIXELART:
        scaleMode = SDL_SCALEMODE_NEAREST;
        বিরতি;
    পূর্বনির্ধারিত:
        ফেরত SDL_InvalidParamError("scaleMode");
    }

    যদি (scaleMode == SDL_SCALEMODE_LINEAR) {
        যদি (SDL_BYTESPERPIXEL(src->format) != 4 || src->format == SDL_PIXELFORMAT_ARGB2101010) {
            ফেরত SDL_SetError("Wrong format");
        }
    }

    // Verify the blit rectangles
    যদি (srcrect) {
        যদি ((srcrect->x < 0) || (srcrect->y < 0) ||
            ((srcrect->x + srcrect->w) > src->w) ||
            ((srcrect->y + srcrect->h) > src->h)) {
            ফেরত SDL_SetError("Invalid source blit rectangle");
        }
    } অন্যথা {
        full_src.x = 0;
        full_src.y = 0;
        full_src.w = src->w;
        full_src.h = src->h;
        srcrect = &full_src;
    }
    যদি (dstrect) {
        যদি ((dstrect->x < 0) || (dstrect->y < 0) ||
            ((dstrect->x + dstrect->w) > dst->w) ||
            ((dstrect->y + dstrect->h) > dst->h)) {
            ফেরত SDL_SetError("Invalid destination blit rectangle");
        }
    } অন্যথা {
        full_dst.x = 0;
        full_dst.y = 0;
        full_dst.w = dst->w;
        full_dst.h = dst->h;
        dstrect = &full_dst;
    }

    যদি (dstrect->w <= 0 || dstrect->h <= 0) {
        ফেরত true;
    }

    যদি (srcrect->w > SDL_MAX_UINT16 || srcrect->h > SDL_MAX_UINT16 ||
        dstrect->w > SDL_MAX_UINT16 || dstrect->h > SDL_MAX_UINT16) {
        ফেরত SDL_SetError("Size too large for scaling");
    }

    // Lock the destination if it's in hardware
    dst_locked = 0;
    যদি (SDL_MUSTLOCK(dst)) {
        যদি (!SDL_LockSurface(dst)) {
            ফেরত SDL_SetError("Unable to lock destination surface");
        }
        dst_locked = 1;
    }
    // Lock the source if it's in hardware
    src_locked = 0;
    যদি (SDL_MUSTLOCK(src)) {
        যদি (!SDL_LockSurface(src)) {
            যদি (dst_locked) {
                SDL_UnlockSurface(dst);
            }
            ফেরত SDL_SetError("Unable to lock source surface");
        }
        src_locked = 1;
    }

    যদি (scaleMode == SDL_SCALEMODE_NEAREST) {
        ফলাফল = SDL_StretchSurfaceUncheckedNearest(src, srcrect, dst, dstrect);
    } অন্যথা {
        ফলাফল = SDL_StretchSurfaceUncheckedLinear(src, srcrect, dst, dstrect);
    }

    // We need to unlock the surfaces if they're locked
    যদি (dst_locked) {
        SDL_UnlockSurface(dst);
    }
    যদি (src_locked) {
        SDL_UnlockSurface(src);
    }

    ফেরত ফলাফল;
}

/* bilinear interpolation precision must be < 8
   Because with SSE: add-multiply: _mm_madd_epi16 works with signed int
   so pixels 0xb1...... are negatives and false the result
   same in NEON probably */
#define PRECISION 7

#define FIXED_POINT(i) ((Uint32)(i) << 16)
#define SRC_সূচক(fp)  ((Uint32)(fp) >> 16)
#define INTEGER(fp)    ((Uint32)(fp) >> PRECISION)
#define FRAC(fp)       ((Uint32)((fp) >> (16 - PRECISION)) & ((1 << PRECISION) - 1))
#define FRAC_ZERO      0
#define FRAC_ONE       (1 << PRECISION)
#define FP_ONE         FIXED_POINT(1)

#define BILINEAR___START                                                              \
    পূর্ণসংখ্যা i;                                                                            \
    Sint64 fp_যোগ_h;                                                                  \
    পূর্ণসংখ্যা fp_step_h, বাম_pad_h, ডান_pad_h;                                           \
    Sint64 fp_যোগ_w;                                                                  \
    পূর্ণসংখ্যা fp_step_w, বাম_pad_w, ডান_pad_w;                                           \
    Sint64 fp_যোগ_w_init;                                                             \
    পূর্ণসংখ্যা বাম_pad_w_init, ডান_pad_w_init, dst_gap, মধ্য_init;                      \
    get_scaler_datas(src_h, dst_h, &fp_যোগ_h, &fp_step_h, &বাম_pad_h, &ডান_pad_h); \
    get_scaler_datas(src_w, dst_w, &fp_যোগ_w, &fp_step_w, &বাম_pad_w, &ডান_pad_w); \
    fp_যোগ_w_init = fp_যোগ_w + বাম_pad_w * fp_step_w;                                \
    বাম_pad_w_init = বাম_pad_w;                                                     \
    ডান_pad_w_init = ডান_pad_w;                                                   \
    dst_gap = dst_pitch - 4 * dst_w;                                                  \
    মধ্য_init = dst_w - বাম_pad_w - ডান_pad_w;

#define BILINEAR___HEIGHT                                              \
    পূর্ণসংখ্যা সূচক_h, frac_h0, frac_h1, মধ্য;                             \
    ধ্রুবক Uint32 *src_h0, *src_h1;                                     \
    পূর্ণসংখ্যা no_padding;                                                    \
    Uint64 incr_h0, incr_h1;                                           \
                                                                       \
    no_padding = !(i < বাম_pad_h || i > dst_h - 1 - ডান_pad_h);     \
    সূচক_h = SRC_সূচক(fp_যোগ_h);                                     \
    frac_h0 = FRAC(fp_যোগ_h);                                          \
                                                                       \
    সূচক_h = no_padding ? সূচক_h : (i < বাম_pad_h ? 0 : src_h - 1); \
    frac_h0 = no_padding ? frac_h0 : 0;                                \
    incr_h1 = no_padding ? src_pitch : 0;                              \
    incr_h0 = (Uint64)সূচক_h * src_pitch;                             \
                                                                       \
    src_h0 = (ধ্রুবক Uint32 *)((ধ্রুবক Uint8 *)src + incr_h0);           \
    src_h1 = (ধ্রুবক Uint32 *)((ধ্রুবক Uint8 *)src_h0 + incr_h1);        \
                                                                       \
    fp_যোগ_h += fp_step_h;                                             \
                                                                       \
    frac_h1 = FRAC_ONE - frac_h0;                                      \
    fp_যোগ_w = fp_যোগ_w_init;                                          \
    ডান_pad_w = ডান_pad_w_init;                                    \
    বাম_pad_w = বাম_pad_w_init;                                      \
    মধ্য = মধ্য_init;

#ifdef __clang__
// Remove inlining of this function
// Compiler crash with clang 9.0.8 / android-ndk-r21d
// Compiler crash with clang 11.0.3 / Xcode
// OK with clang 11.0.5 / android-ndk-22
// OK with clang 12.0.0 / Xcode
__attribute__((noinline))
#endif
স্থির শূন্য get_scaler_datas(পূর্ণসংখ্যা src_nb, পূর্ণসংখ্যা dst_nb, Sint64 *fp_start, পূর্ণসংখ্যা *fp_step, পূর্ণসংখ্যা *বাম_pad, পূর্ণসংখ্যা *ডান_pad)
{

    পূর্ণসংখ্যা step = FIXED_POINT(src_nb) / (dst_nb); // source step in fixed point
    পূর্ণসংখ্যা x0 = FP_ONE / 2;                       // dst first pixel center at 0.5 in fixed point
    Sint64 fp_যোগ;
    পূর্ণসংখ্যা i;
#যদি 0
    // scale to source coordinates
    x0 *= src_nb;
    x0 /= dst_nb; // x0 == step / 2
#অন্যথা
    // Use this code for perfect match with pixman
    Sint64 tmp[2];
    tmp[0] = (Sint64)step * (x0 >> 16);
    tmp[1] = (Sint64)step * (x0 & 0xFFFF);
    x0 = (পূর্ণসংখ্যা)(tmp[0] + ((tmp[1] + 0x8000) >> 16)); // x0 == (step + 1) / 2
#endif
    // -= 0.5, get back the pixel origin, in source coordinates
    x0 -= FP_ONE / 2;

    *fp_start = x0;
    *fp_step = step;
    *বাম_pad = 0;
    *ডান_pad = 0;

    fp_যোগ = x0;
    জন্য (i = 0; i < dst_nb; i++) {
        যদি (fp_যোগ < 0) {
            *বাম_pad += 1;
        } অন্যথা {
            পূর্ণসংখ্যা সূচক = SRC_সূচক(fp_যোগ);
            যদি (সূচক > src_nb - 2) {
                *ডান_pad += 1;
            }
        }
        fp_যোগ += step;
    }
    //    SDL_Log("%d -> %d  x0=%d step=%d left_pad=%d right_pad=%d", src_nb, dst_nb, *fp_start, *fp_step, *left_pad, *right_pad);
}

প্রকারলেখ কাঠামো color_t
{
    Uint8 a;
    Uint8 b;
    Uint8 c;
    Uint8 d;
} color_t;

/* Interpolated == x0 + frac * (x1 - x0) == x0 * (1 - frac) + x1 * frac */

স্থির SDL_INLINE শূন্য INTERPOL(ধ্রুবক Uint32 *src_x0, ধ্রুবক Uint32 *src_x1, পূর্ণসংখ্যা frac0, পূর্ণসংখ্যা frac1, Uint32 *dst)
{
    ধ্রুবক color_t *c0 = (ধ্রুবক color_t *)src_x0;
    ধ্রুবক color_t *c1 = (ধ্রুবক color_t *)src_x1;
    color_t *cx = (color_t *)dst;
#যদি 0
    cx->a = c0->a + INTEGER(frac0 * (c1->a - c0->a));
    cx->b = c0->b + INTEGER(frac0 * (c1->b - c0->b));
    cx->c = c0->c + INTEGER(frac0 * (c1->c - c0->c));
    cx->d = c0->d + INTEGER(frac0 * (c1->d - c0->d));
#অন্যথা
    cx->a = (Uint8)INTEGER(frac1 * c0->a + frac0 * c1->a);
    cx->b = (Uint8)INTEGER(frac1 * c0->b + frac0 * c1->b);
    cx->c = (Uint8)INTEGER(frac1 * c0->c + frac0 * c1->c);
    cx->d = (Uint8)INTEGER(frac1 * c0->d + frac0 * c1->d);
#endif
}

স্থির SDL_INLINE শূন্য INTERPOL_BILINEAR(ধ্রুবক Uint32 *s0, ধ্রুবক Uint32 *s1, পূর্ণসংখ্যা frac_w0, পূর্ণসংখ্যা frac_h0, পূর্ণসংখ্যা frac_h1, Uint32 *dst)
{
    Uint32 tmp[2];
    unsigned পূর্ণসংখ্যা frac_w1 = FRAC_ONE - frac_w0;

    // Vertical first, store to 'tmp'
    INTERPOL(s0, s1, frac_h0, frac_h1, tmp);
    INTERPOL(s0 + 1, s1 + 1, frac_h0, frac_h1, tmp + 1);

    // Horizontal, store to 'dst'
    INTERPOL(tmp, tmp + 1, frac_w0, frac_w1, dst);
}

স্থির bool scale_mat(ধ্রুবক Uint32 *src, পূর্ণসংখ্যা src_w, পূর্ণসংখ্যা src_h, পূর্ণসংখ্যা src_pitch, Uint32 *dst, পূর্ণসংখ্যা dst_w, পূর্ণসংখ্যা dst_h, পূর্ণসংখ্যা dst_pitch)
{
    BILINEAR___START

    জন্য (i = 0; i < dst_h; i++) {

        BILINEAR___HEIGHT

        যখন (বাম_pad_w--) {
            INTERPOL_BILINEAR(src_h0, src_h1, FRAC_ZERO, frac_h0, frac_h1, dst);
            dst += 1;
        }

        যখন (মধ্য--) {
            ধ্রুবক Uint32 *s_00_01;
            ধ্রুবক Uint32 *s_10_11;
            পূর্ণসংখ্যা সূচক_w = 4 * SRC_সূচক(fp_যোগ_w);
            পূর্ণসংখ্যা frac_w = FRAC(fp_যোগ_w);
            fp_যোগ_w += fp_step_w;

            /*
                        x00 ... x0_ ..... x01
                        .       .         .
                        .       x         .
                        .       .         .
                        .       .         .
                        x10 ... x1_ ..... x11
            */
            s_00_01 = (ধ্রুবক Uint32 *)((ধ্রুবক Uint8 *)src_h0 + সূচক_w);
            s_10_11 = (ধ্রুবক Uint32 *)((ধ্রুবক Uint8 *)src_h1 + সূচক_w);

            INTERPOL_BILINEAR(s_00_01, s_10_11, frac_w, frac_h0, frac_h1, dst);

            dst += 1;
        }

        যখন (ডান_pad_w--) {
            পূর্ণসংখ্যা সূচক_w = 4 * (src_w - 2);
            ধ্রুবক Uint32 *s_00_01 = (ধ্রুবক Uint32 *)((ধ্রুবক Uint8 *)src_h0 + সূচক_w);
            ধ্রুবক Uint32 *s_10_11 = (ধ্রুবক Uint32 *)((ধ্রুবক Uint8 *)src_h1 + সূচক_w);
            INTERPOL_BILINEAR(s_00_01, s_10_11, FRAC_ONE, frac_h0, frac_h1, dst);
            dst += 1;
        }
        dst = (Uint32 *)((Uint8 *)dst + dst_gap);
    }
    ফেরত true;
}

#ifdef SDL_SSE2_INTRINSICS

স্থির SDL_INLINE পূর্ণসংখ্যা hasSSE2(শূন্য)
{
    স্থির পূর্ণসংখ্যা val = -1;
    যদি (val != -1) {
        ফেরত val;
    }
    val = SDL_HasSSE2();
    ফেরত val;
}

স্থির SDL_INLINE শূন্য SDL_TARGETING("sse2") INTERPOL_BILINEAR_SSE(ধ্রুবক Uint32 *s0, ধ্রুবক Uint32 *s1, পূর্ণসংখ্যা frac_w, __m128i v_frac_h0, __m128i v_frac_h1, Uint32 *dst, __m128i zero)
{
    __m128i x_00_01, x_10_11; /* Pixels in 4*uint8 in row */
    __m128i v_frac_w0, k0, l0, d0, e0;

    পূর্ণসংখ্যা f, f2;
    f = frac_w;
    f2 = FRAC_ONE - frac_w;
    v_frac_w0 = _mm_set_epi16((short)f, (short)f2, (short)f, (short)f2, (short)f, (short)f2, (short)f, (short)f2);

    x_00_01 = _mm_loadl_epi64((ধ্রুবক __m128i *)s0); // Load x00 and x01
    x_10_11 = _mm_loadl_epi64((ধ্রুবক __m128i *)s1);

    /* Interpolated == x0 + frac * (x1 - x0) == x0 * (1 - frac) + x1 * frac */

    // Interpolation vertical
    k0 = _mm_mullo_epi16(_mm_unpacklo_epi8(x_00_01, zero), v_frac_h1);
    l0 = _mm_mullo_epi16(_mm_unpacklo_epi8(x_10_11, zero), v_frac_h0);
    k0 = _mm_add_epi16(k0, l0);

    // For perfect match, clear the factionnal part eventually.
    /*
    k0 = _mm_srli_epi16(k0, PRECISION);
    k0 = _mm_slli_epi16(k0, PRECISION);
    */

    // Interpolation horizontal
    l0 = _mm_unpacklo_epi64(/* unused */ l0, k0);
    k0 = _mm_madd_epi16(_mm_unpackhi_epi16(l0, k0), v_frac_w0);

    // Store 1 pixel
    d0 = _mm_srli_epi32(k0, PRECISION * 2);
    e0 = _mm_packs_epi32(d0, d0);
    e0 = _mm_packus_epi16(e0, e0);
    *dst = _mm_cvtsi128_si32(e0);
}

স্থির bool SDL_TARGETING("sse2") scale_mat_SSE(ধ্রুবক Uint32 *src, পূর্ণসংখ্যা src_w, পূর্ণসংখ্যা src_h, পূর্ণসংখ্যা src_pitch, Uint32 *dst, পূর্ণসংখ্যা dst_w, পূর্ণসংখ্যা dst_h, পূর্ণসংখ্যা dst_pitch)
{
    BILINEAR___START

    জন্য (i = 0; i < dst_h; i++) {
        পূর্ণসংখ্যা nb_block2;
        __m128i v_frac_h0;
        __m128i v_frac_h1;
        __m128i zero;

        BILINEAR___HEIGHT

        nb_block2 = মধ্য / 2;

        v_frac_h0 = _mm_set_epi16((short)frac_h0, (short)frac_h0, (short)frac_h0, (short)frac_h0, (short)frac_h0, (short)frac_h0, (short)frac_h0, (short)frac_h0);
        v_frac_h1 = _mm_set_epi16((short)frac_h1, (short)frac_h1, (short)frac_h1, (short)frac_h1, (short)frac_h1, (short)frac_h1, (short)frac_h1, (short)frac_h1);
        zero = _mm_setzero_si128();

        যখন (বাম_pad_w--) {
            INTERPOL_BILINEAR_SSE(src_h0, src_h1, FRAC_ZERO, v_frac_h0, v_frac_h1, dst, zero);
            dst += 1;
        }

        যখন (nb_block2--) {
            পূর্ণসংখ্যা সূচক_w_0, frac_w_0;
            পূর্ণসংখ্যা সূচক_w_1, frac_w_1;

            ধ্রুবক Uint32 *s_00_01, *s_02_03, *s_10_11, *s_12_13;

            __m128i x_00_01, x_10_11, x_02_03, x_12_13; /* Pixels in 4*uint8 in row */
            __m128i v_frac_w0, k0, l0, d0, e0;
            __m128i v_frac_w1, k1, l1, d1, e1;

            পূর্ণসংখ্যা f, f2;
            সূচক_w_0 = 4 * SRC_সূচক(fp_যোগ_w);
            frac_w_0 = FRAC(fp_যোগ_w);
            fp_যোগ_w += fp_step_w;
            সূচক_w_1 = 4 * SRC_সূচক(fp_যোগ_w);
            frac_w_1 = FRAC(fp_যোগ_w);
            fp_যোগ_w += fp_step_w;
            /*
                        x00............ x01   x02...........x03
                        .      .         .     .       .     .
                        j0     f0        j1    j2      f1    j3
                        .      .         .     .       .     .
                        .      .         .     .       .     .
                        .      .         .     .       .     .
                        x10............ x11   x12...........x13
             */
            s_00_01 = (ধ্রুবক Uint32 *)((ধ্রুবক Uint8 *)src_h0 + সূচক_w_0);
            s_02_03 = (ধ্রুবক Uint32 *)((ধ্রুবক Uint8 *)src_h0 + সূচক_w_1);
            s_10_11 = (ধ্রুবক Uint32 *)((ধ্রুবক Uint8 *)src_h1 + সূচক_w_0);
            s_12_13 = (ধ্রুবক Uint32 *)((ধ্রুবক Uint8 *)src_h1 + সূচক_w_1);

            f = frac_w_0;
            f2 = FRAC_ONE - frac_w_0;
            v_frac_w0 = _mm_set_epi16((short)f, (short)f2, (short)f, (short)f2, (short)f, (short)f2, (short)f, (short)f2);

            f = frac_w_1;
            f2 = FRAC_ONE - frac_w_1;
            v_frac_w1 = _mm_set_epi16((short)f, (short)f2, (short)f, (short)f2, (short)f, (short)f2, (short)f, (short)f2);

            x_00_01 = _mm_loadl_epi64((ধ্রুবক __m128i *)s_00_01); // Load x00 and x01
            x_02_03 = _mm_loadl_epi64((ধ্রুবক __m128i *)s_02_03);
            x_10_11 = _mm_loadl_epi64((ধ্রুবক __m128i *)s_10_11);
            x_12_13 = _mm_loadl_epi64((ধ্রুবক __m128i *)s_12_13);

            // Interpolation vertical
            k0 = _mm_mullo_epi16(_mm_unpacklo_epi8(x_00_01, zero), v_frac_h1);
            l0 = _mm_mullo_epi16(_mm_unpacklo_epi8(x_10_11, zero), v_frac_h0);
            k0 = _mm_add_epi16(k0, l0);
            k1 = _mm_mullo_epi16(_mm_unpacklo_epi8(x_02_03, zero), v_frac_h1);
            l1 = _mm_mullo_epi16(_mm_unpacklo_epi8(x_12_13, zero), v_frac_h0);
            k1 = _mm_add_epi16(k1, l1);

            // Interpolation horizontal
            l0 = _mm_unpacklo_epi64(/* unused */ l0, k0);
            k0 = _mm_madd_epi16(_mm_unpackhi_epi16(l0, k0), v_frac_w0);
            l1 = _mm_unpacklo_epi64(/* unused */ l1, k1);
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
        যদি (মধ্য & 0x1) {
            ধ্রুবক Uint32 *s_00_01;
            ধ্রুবক Uint32 *s_10_11;
            পূর্ণসংখ্যা সূচক_w = 4 * SRC_সূচক(fp_যোগ_w);
            পূর্ণসংখ্যা frac_w = FRAC(fp_যোগ_w);
            fp_যোগ_w += fp_step_w;
            s_00_01 = (ধ্রুবক Uint32 *)((ধ্রুবক Uint8 *)src_h0 + সূচক_w);
            s_10_11 = (ধ্রুবক Uint32 *)((ধ্রুবক Uint8 *)src_h1 + সূচক_w);
            INTERPOL_BILINEAR_SSE(s_00_01, s_10_11, frac_w, v_frac_h0, v_frac_h1, dst, zero);
            dst += 1;
        }

        যখন (ডান_pad_w--) {
            পূর্ণসংখ্যা সূচক_w = 4 * (src_w - 2);
            ধ্রুবক Uint32 *s_00_01 = (ধ্রুবক Uint32 *)((ধ্রুবক Uint8 *)src_h0 + সূচক_w);
            ধ্রুবক Uint32 *s_10_11 = (ধ্রুবক Uint32 *)((ধ্রুবক Uint8 *)src_h1 + সূচক_w);
            INTERPOL_BILINEAR_SSE(s_00_01, s_10_11, FRAC_ONE, v_frac_h0, v_frac_h1, dst, zero);
            dst += 1;
        }
        dst = (Uint32 *)((Uint8 *)dst + dst_gap);
    }
    ফেরত true;
}
#endif

#ifdef SDL_NEON_INTRINSICS

স্থির SDL_INLINE পূর্ণসংখ্যা hasNEON(শূন্য)
{
    স্থির পূর্ণসংখ্যা val = -1;
    যদি (val != -1) {
        ফেরত val;
    }
    val = SDL_HasNEON();
    ফেরত val;
}

স্থির SDL_INLINE শূন্য INTERPOL_BILINEAR_NEON(ধ্রুবক Uint32 *s0, ধ্রুবক Uint32 *s1, পূর্ণসংখ্যা frac_w, uint8x8_t v_frac_h0, uint8x8_t v_frac_h1, Uint32 *dst)
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
    l0 = vshll_n_u16(vget_নিচের_u16(k0), PRECISION);
    l0 = vmlsl_n_u16(l0, vget_নিচের_u16(k0), frac_w);
    l0 = vmlal_n_u16(l0, vget_উপরের_u16(k0), frac_w);

    // Shift and narrow
    d0 = vcombine_u16(
        /* uint16x4_t */ vshrn_n_u32(l0, 2 * PRECISION),
        /* uint16x4_t */ vshrn_n_u32(l0, 2 * PRECISION));

    // Narrow again
    e0 = vmovn_u16(d0);

    // Store 1 pixel
    *dst = vget_lane_u32(vreinterpret_u32_u8(e0), 0);
}

স্থির bool scale_mat_NEON(ধ্রুবক Uint32 *src, পূর্ণসংখ্যা src_w, পূর্ণসংখ্যা src_h, পূর্ণসংখ্যা src_pitch, Uint32 *dst, পূর্ণসংখ্যা dst_w, পূর্ণসংখ্যা dst_h, পূর্ণসংখ্যা dst_pitch)
{
    BILINEAR___START

    জন্য (i = 0; i < dst_h; i++) {
        পূর্ণসংখ্যা nb_block4;
        uint8x8_t v_frac_h0, v_frac_h1;

        BILINEAR___HEIGHT

        nb_block4 = মধ্য / 4;

        v_frac_h0 = vmov_n_u8(frac_h0);
        v_frac_h1 = vmov_n_u8(frac_h1);

        যখন (বাম_pad_w--) {
            INTERPOL_BILINEAR_NEON(src_h0, src_h1, FRAC_ZERO, v_frac_h0, v_frac_h1, dst);
            dst += 1;
        }

        যখন (nb_block4--) {
            পূর্ণসংখ্যা সূচক_w_0, frac_w_0;
            পূর্ণসংখ্যা সূচক_w_1, frac_w_1;
            পূর্ণসংখ্যা সূচক_w_2, frac_w_2;
            পূর্ণসংখ্যা সূচক_w_3, frac_w_3;

            ধ্রুবক Uint32 *s_00_01, *s_02_03, *s_04_05, *s_06_07;
            ধ্রুবক Uint32 *s_10_11, *s_12_13, *s_14_15, *s_16_17;

            uint8x8_t x_00_01, x_10_11, x_02_03, x_12_13; /* Pixels in 4*uint8 in row */
            uint8x8_t x_04_05, x_14_15, x_06_07, x_16_17;

            uint16x8_t k0, k1, k2, k3;
            uint32x4_t l0, l1, l2, l3;
            uint16x8_t d0, d1;
            uint8x8_t e0, e1;
            uint32x4_t f0;

            সূচক_w_0 = 4 * SRC_সূচক(fp_যোগ_w);
            frac_w_0 = FRAC(fp_যোগ_w);
            fp_যোগ_w += fp_step_w;
            সূচক_w_1 = 4 * SRC_সূচক(fp_যোগ_w);
            frac_w_1 = FRAC(fp_যোগ_w);
            fp_যোগ_w += fp_step_w;
            সূচক_w_2 = 4 * SRC_সূচক(fp_যোগ_w);
            frac_w_2 = FRAC(fp_যোগ_w);
            fp_যোগ_w += fp_step_w;
            সূচক_w_3 = 4 * SRC_সূচক(fp_যোগ_w);
            frac_w_3 = FRAC(fp_যোগ_w);
            fp_যোগ_w += fp_step_w;

            s_00_01 = (ধ্রুবক Uint32 *)((ধ্রুবক Uint8 *)src_h0 + সূচক_w_0);
            s_02_03 = (ধ্রুবক Uint32 *)((ধ্রুবক Uint8 *)src_h0 + সূচক_w_1);
            s_04_05 = (ধ্রুবক Uint32 *)((ধ্রুবক Uint8 *)src_h0 + সূচক_w_2);
            s_06_07 = (ধ্রুবক Uint32 *)((ধ্রুবক Uint8 *)src_h0 + সূচক_w_3);
            s_10_11 = (ধ্রুবক Uint32 *)((ধ্রুবক Uint8 *)src_h1 + সূচক_w_0);
            s_12_13 = (ধ্রুবক Uint32 *)((ধ্রুবক Uint8 *)src_h1 + সূচক_w_1);
            s_14_15 = (ধ্রুবক Uint32 *)((ধ্রুবক Uint8 *)src_h1 + সূচক_w_2);
            s_16_17 = (ধ্রুবক Uint32 *)((ধ্রুবক Uint8 *)src_h1 + সূচক_w_3);

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

            l0 = vshll_n_u16(vget_নিচের_u16(k0), PRECISION);
            l0 = vmlsl_n_u16(l0, vget_নিচের_u16(k0), frac_w_0);
            l0 = vmlal_n_u16(l0, vget_উপরের_u16(k0), frac_w_0);

            l1 = vshll_n_u16(vget_নিচের_u16(k1), PRECISION);
            l1 = vmlsl_n_u16(l1, vget_নিচের_u16(k1), frac_w_1);
            l1 = vmlal_n_u16(l1, vget_উপরের_u16(k1), frac_w_1);

            l2 = vshll_n_u16(vget_নিচের_u16(k2), PRECISION);
            l2 = vmlsl_n_u16(l2, vget_নিচের_u16(k2), frac_w_2);
            l2 = vmlal_n_u16(l2, vget_উপরের_u16(k2), frac_w_2);

            l3 = vshll_n_u16(vget_নিচের_u16(k3), PRECISION);
            l3 = vmlsl_n_u16(l3, vget_নিচের_u16(k3), frac_w_3);
            l3 = vmlal_n_u16(l3, vget_উপরের_u16(k3), frac_w_3);

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

        যদি (মধ্য & 0x2) {
            পূর্ণসংখ্যা সূচক_w_0, frac_w_0;
            পূর্ণসংখ্যা সূচক_w_1, frac_w_1;
            ধ্রুবক Uint32 *s_00_01, *s_02_03;
            ধ্রুবক Uint32 *s_10_11, *s_12_13;
            uint8x8_t x_00_01, x_10_11, x_02_03, x_12_13; /* Pixels in 4*uint8 in row */
            uint16x8_t k0, k1;
            uint32x4_t l0, l1;
            uint16x8_t d0;
            uint8x8_t e0;

            সূচক_w_0 = 4 * SRC_সূচক(fp_যোগ_w);
            frac_w_0 = FRAC(fp_যোগ_w);
            fp_যোগ_w += fp_step_w;
            সূচক_w_1 = 4 * SRC_সূচক(fp_যোগ_w);
            frac_w_1 = FRAC(fp_যোগ_w);
            fp_যোগ_w += fp_step_w;
            /*
                        x00............ x01   x02...........x03
                        .      .         .     .       .     .
                        j0   dest0       j1    j2    dest1   j3
                        .      .         .     .       .     .
                        .      .         .     .       .     .
                        .      .         .     .       .     .
                        x10............ x11   x12...........x13
            */
            s_00_01 = (ধ্রুবক Uint32 *)((ধ্রুবক Uint8 *)src_h0 + সূচক_w_0);
            s_02_03 = (ধ্রুবক Uint32 *)((ধ্রুবক Uint8 *)src_h0 + সূচক_w_1);
            s_10_11 = (ধ্রুবক Uint32 *)((ধ্রুবক Uint8 *)src_h1 + সূচক_w_0);
            s_12_13 = (ধ্রুবক Uint32 *)((ধ্রুবক Uint8 *)src_h1 + সূচক_w_1);

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

            l0 = vshll_n_u16(vget_নিচের_u16(k0), PRECISION);
            l0 = vmlsl_n_u16(l0, vget_নিচের_u16(k0), frac_w_0);
            l0 = vmlal_n_u16(l0, vget_উপরের_u16(k0), frac_w_0);

            l1 = vshll_n_u16(vget_নিচের_u16(k1), PRECISION);
            l1 = vmlsl_n_u16(l1, vget_নিচের_u16(k1), frac_w_1);
            l1 = vmlal_n_u16(l1, vget_উপরের_u16(k1), frac_w_1);

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
        যদি (মধ্য & 0x1) {
            পূর্ণসংখ্যা সূচক_w = 4 * SRC_সূচক(fp_যোগ_w);
            পূর্ণসংখ্যা frac_w = FRAC(fp_যোগ_w);
            ধ্রুবক Uint32 *s_00_01 = (ধ্রুবক Uint32 *)((ধ্রুবক Uint8 *)src_h0 + সূচক_w);
            ধ্রুবক Uint32 *s_10_11 = (ধ্রুবক Uint32 *)((ধ্রুবক Uint8 *)src_h1 + সূচক_w);
            INTERPOL_BILINEAR_NEON(s_00_01, s_10_11, frac_w, v_frac_h0, v_frac_h1, dst);
            dst += 1;
        }

        যখন (ডান_pad_w--) {
            পূর্ণসংখ্যা সূচক_w = 4 * (src_w - 2);
            ধ্রুবক Uint32 *s_00_01 = (ধ্রুবক Uint32 *)((ধ্রুবক Uint8 *)src_h0 + সূচক_w);
            ধ্রুবক Uint32 *s_10_11 = (ধ্রুবক Uint32 *)((ধ্রুবক Uint8 *)src_h1 + সূচক_w);
            INTERPOL_BILINEAR_NEON(s_00_01, s_10_11, FRAC_ONE, v_frac_h0, v_frac_h1, dst);
            dst += 1;
        }

        dst = (Uint32 *)((Uint8 *)dst + dst_gap);
    }
    ফেরত true;
}
#endif

bool SDL_StretchSurfaceUncheckedLinear(SDL_Surface *s, ধ্রুবক SDL_Rect *srcrect, SDL_Surface *d, ধ্রুবক SDL_Rect *dstrect)
{
    bool ফলাফল = false;
    পূর্ণসংখ্যা src_w = srcrect->w;
    পূর্ণসংখ্যা src_h = srcrect->h;
    পূর্ণসংখ্যা dst_w = dstrect->w;
    পূর্ণসংখ্যা dst_h = dstrect->h;
    পূর্ণসংখ্যা src_pitch = s->pitch;
    পূর্ণসংখ্যা dst_pitch = d->pitch;
    Uint32 *src = (Uint32 *)((Uint8 *)s->pixels + srcrect->x * 4 + srcrect->y * src_pitch);
    Uint32 *dst = (Uint32 *)((Uint8 *)d->pixels + dstrect->x * 4 + dstrect->y * dst_pitch);

#ifdef SDL_NEON_INTRINSICS
    যদি (!ফলাফল && hasNEON()) {
        ফলাফল = scale_mat_NEON(src, src_w, src_h, src_pitch, dst, dst_w, dst_h, dst_pitch);
    }
#endif

#ifdef SDL_SSE2_INTRINSICS
    যদি (!ফলাফল && hasSSE2()) {
        ফলাফল = scale_mat_SSE(src, src_w, src_h, src_pitch, dst, dst_w, dst_h, dst_pitch);
    }
#endif

    যদি (!ফলাফল) {
        ফলাফল = scale_mat(src, src_w, src_h, src_pitch, dst, dst_w, dst_h, dst_pitch);
    }

    ফেরত ফলাফল;
}

#define SDL_SCALE_NEAREST__START          \
    পূর্ণসংখ্যা i;                                \
    Uint64 posy, incy;                    \
    Uint64 posx, incx;                    \
    Uint64 srcy, srcx;                    \
    পূর্ণসংখ্যা dst_gap, n;                       \
    ধ্রুবক Uint32 *src_h0;                 \
    incy = ((Uint64)src_h << 16) / dst_h; \
    incx = ((Uint64)src_w << 16) / dst_w; \
    dst_gap = dst_pitch - bpp * dst_w;    \
    posy = incy / 2;

#define SDL_SCALE_NEAREST__HEIGHT                                         \
    srcy = (posy >> 16);                                                  \
    src_h0 = (ধ্রুবক Uint32 *)((ধ্রুবক Uint8 *)src_ptr + srcy * src_pitch); \
    posy += incy;                                                         \
    posx = incx / 2;                                                      \
    n = dst_w;

স্থির bool scale_mat_nearest_1(ধ্রুবক Uint32 *src_ptr, পূর্ণসংখ্যা src_w, পূর্ণসংখ্যা src_h, পূর্ণসংখ্যা src_pitch, Uint32 *dst, পূর্ণসংখ্যা dst_w, পূর্ণসংখ্যা dst_h, পূর্ণসংখ্যা dst_pitch)
{
    Uint32 bpp = 1;
    SDL_SCALE_NEAREST__START
    জন্য (i = 0; i < dst_h; i++) {
        SDL_SCALE_NEAREST__HEIGHT
        যখন (n--) {
            ধ্রুবক Uint8 *src;
            srcx = bpp * (posx >> 16);
            posx += incx;
            src = (ধ্রুবক Uint8 *)src_h0 + srcx;
            *(Uint8 *)dst = *src;
            dst = (Uint32 *)((Uint8 *)dst + bpp);
        }
        dst = (Uint32 *)((Uint8 *)dst + dst_gap);
    }
    ফেরত true;
}

স্থির bool scale_mat_nearest_2(ধ্রুবক Uint32 *src_ptr, পূর্ণসংখ্যা src_w, পূর্ণসংখ্যা src_h, পূর্ণসংখ্যা src_pitch, Uint32 *dst, পূর্ণসংখ্যা dst_w, পূর্ণসংখ্যা dst_h, পূর্ণসংখ্যা dst_pitch)
{
    Uint32 bpp = 2;
    SDL_SCALE_NEAREST__START
    জন্য (i = 0; i < dst_h; i++) {
        SDL_SCALE_NEAREST__HEIGHT
        যখন (n--) {
            ধ্রুবক Uint16 *src;
            srcx = bpp * (posx >> 16);
            posx += incx;
            src = (ধ্রুবক Uint16 *)((ধ্রুবক Uint8 *)src_h0 + srcx);
            *(Uint16 *)dst = *src;
            dst = (Uint32 *)((Uint8 *)dst + bpp);
        }
        dst = (Uint32 *)((Uint8 *)dst + dst_gap);
    }
    ফেরত true;
}

স্থির bool scale_mat_nearest_3(ধ্রুবক Uint32 *src_ptr, পূর্ণসংখ্যা src_w, পূর্ণসংখ্যা src_h, পূর্ণসংখ্যা src_pitch, Uint32 *dst, পূর্ণসংখ্যা dst_w, পূর্ণসংখ্যা dst_h, পূর্ণসংখ্যা dst_pitch)
{
    Uint32 bpp = 3;
    SDL_SCALE_NEAREST__START
    জন্য (i = 0; i < dst_h; i++) {
        SDL_SCALE_NEAREST__HEIGHT
        যখন (n--) {
            ধ্রুবক Uint8 *src;
            srcx = bpp * (posx >> 16);
            posx += incx;
            src = (ধ্রুবক Uint8 *)src_h0 + srcx;
            ((Uint8 *)dst)[0] = src[0];
            ((Uint8 *)dst)[1] = src[1];
            ((Uint8 *)dst)[2] = src[2];
            dst = (Uint32 *)((Uint8 *)dst + bpp);
        }
        dst = (Uint32 *)((Uint8 *)dst + dst_gap);
    }
    ফেরত true;
}

স্থির bool scale_mat_nearest_4(ধ্রুবক Uint32 *src_ptr, পূর্ণসংখ্যা src_w, পূর্ণসংখ্যা src_h, পূর্ণসংখ্যা src_pitch, Uint32 *dst, পূর্ণসংখ্যা dst_w, পূর্ণসংখ্যা dst_h, পূর্ণসংখ্যা dst_pitch)
{
    Uint32 bpp = 4;
    SDL_SCALE_NEAREST__START
    জন্য (i = 0; i < dst_h; i++) {
        SDL_SCALE_NEAREST__HEIGHT
        যখন (n--) {
            ধ্রুবক Uint32 *src;
            srcx = bpp * (posx >> 16);
            posx += incx;
            src = (ধ্রুবক Uint32 *)((ধ্রুবক Uint8 *)src_h0 + srcx);
            *dst = *src;
            dst = (Uint32 *)((Uint8 *)dst + bpp);
        }
        dst = (Uint32 *)((Uint8 *)dst + dst_gap);
    }
    ফেরত true;
}

bool SDL_StretchSurfaceUncheckedNearest(SDL_Surface *s, ধ্রুবক SDL_Rect *srcrect, SDL_Surface *d, ধ্রুবক SDL_Rect *dstrect)
{
    পূর্ণসংখ্যা src_w = srcrect->w;
    পূর্ণসংখ্যা src_h = srcrect->h;
    পূর্ণসংখ্যা dst_w = dstrect->w;
    পূর্ণসংখ্যা dst_h = dstrect->h;
    পূর্ণসংখ্যা src_pitch = s->pitch;
    পূর্ণসংখ্যা dst_pitch = d->pitch;
    পূর্ণসংখ্যা bpp = SDL_BYTESPERPIXEL(d->format);

    Uint32 *src = (Uint32 *)((Uint8 *)s->pixels + srcrect->x * bpp + srcrect->y * src_pitch);
    Uint32 *dst = (Uint32 *)((Uint8 *)d->pixels + dstrect->x * bpp + dstrect->y * dst_pitch);

    যদি (bpp == 4) {
        ফেরত scale_mat_nearest_4(src, src_w, src_h, src_pitch, dst, dst_w, dst_h, dst_pitch);
    } অন্যথা যদি (bpp == 3) {
        ফেরত scale_mat_nearest_3(src, src_w, src_h, src_pitch, dst, dst_w, dst_h, dst_pitch);
    } অন্যথা যদি (bpp == 2) {
        ফেরত scale_mat_nearest_2(src, src_w, src_h, src_pitch, dst, dst_w, dst_h, dst_pitch);
    } অন্যথা {
        ফেরত scale_mat_nearest_1(src, src_w, src_h, src_pitch, dst, dst_w, dst_h, dst_pitch);
    }
}
