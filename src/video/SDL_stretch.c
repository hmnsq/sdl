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
#अन्तर्भाव "SDL_internal.h"

#अन्तर्भाव "SDL_surface_c.h"

स्थिर bool SDL_StretchSurfaceUncheckedNearest(SDL_Surface *src, अचर SDL_Rect *srcrect, SDL_Surface *dst, अचर SDL_Rect *dstrect);
स्थिर bool SDL_StretchSurfaceUncheckedLinear(SDL_Surface *src, अचर SDL_Rect *srcrect, SDL_Surface *dst, अचर SDL_Rect *dstrect);

bool SDL_StretchSurface(SDL_Surface *src, अचर SDL_Rect *srcrect, SDL_Surface *dst, अचर SDL_Rect *dstrect, SDL_ScaleMode scaleMode)
{
    bool result;
    पूर्णाङ्क src_locked;
    पूर्णाङ्क dst_locked;
    SDL_Rect full_src;
    SDL_Rect full_dst;

    CHECK_PARAM(!src) {
        फर्काऊ SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!dst) {
        फर्काऊ SDL_InvalidParamError("dst");
    }

    यदि (src->format != dst->format) {
        // Slow!
        SDL_Surface *src_tmp = SDL_ConvertSurfaceAndColorspace(src, dst->format, dst->palette, dst->colorspace, dst->props);
        यदि (!src_tmp) {
            फर्काऊ false;
        }
        result = SDL_StretchSurface(src_tmp, srcrect, dst, dstrect, scaleMode);
        SDL_DestroySurface(src_tmp);
        फर्काऊ result;
    }

    यदि (SDL_ISPIXELFORMAT_FOURCC(src->format)) {
        // Slow!
        यदि (!dstrect) {
            full_dst.x = 0;
            full_dst.y = 0;
            full_dst.w = dst->w;
            full_dst.h = dst->h;
            dstrect = &full_dst;
        }

        SDL_Surface *src_tmp = SDL_ConvertSurface(src, SDL_PIXELFORMAT_XRGB8888);
        SDL_Surface *dst_tmp = SDL_CreateSurfaceUninitialized(dstrect->w, dstrect->h, SDL_PIXELFORMAT_XRGB8888);
        यदि (src_tmp && dst_tmp) {
            result = SDL_StretchSurface(src_tmp, srcrect, dst_tmp, रिक्त, scaleMode);
            यदि (result) {
                result = SDL_ConvertPixelsAndColorspace(dstrect->w, dstrect->h,
                            dst_tmp->format, SDL_COLORSPACE_SRGB, 0,
                            dst_tmp->pixels, dst_tmp->pitch,
                            dst->format, dst->colorspace, SDL_GetSurfaceProperties(dst),
                            (Uint8 *)dst->pixels + dstrect->y * dst->pitch + dstrect->x * SDL_BYTESPERPIXEL(dst->format), dst->pitch);
            }
        } अन्यथा {
            result = false;
        }
        SDL_DestroySurface(src_tmp);
        SDL_DestroySurface(dst_tmp);
        फर्काऊ result;
    }

    विकल्प (scaleMode) {
    पक्ष SDL_SCALEMODE_NEAREST:
        रोक;
    पक्ष SDL_SCALEMODE_LINEAR:
        रोक;
    पक्ष SDL_SCALEMODE_PIXELART:
        scaleMode = SDL_SCALEMODE_NEAREST;
        रोक;
    स्वभाव:
        फर्काऊ SDL_InvalidParamError("scaleMode");
    }

    यदि (scaleMode == SDL_SCALEMODE_LINEAR) {
        यदि (SDL_BYTESPERPIXEL(src->format) != 4 || src->format == SDL_PIXELFORMAT_ARGB2101010) {
            फर्काऊ SDL_SetError("Wrong format");
        }
    }

    // Verify the blit rectangles
    यदि (srcrect) {
        यदि ((srcrect->x < 0) || (srcrect->y < 0) ||
            ((srcrect->x + srcrect->w) > src->w) ||
            ((srcrect->y + srcrect->h) > src->h)) {
            फर्काऊ SDL_SetError("Invalid source blit rectangle");
        }
    } अन्यथा {
        full_src.x = 0;
        full_src.y = 0;
        full_src.w = src->w;
        full_src.h = src->h;
        srcrect = &full_src;
    }
    यदि (dstrect) {
        यदि ((dstrect->x < 0) || (dstrect->y < 0) ||
            ((dstrect->x + dstrect->w) > dst->w) ||
            ((dstrect->y + dstrect->h) > dst->h)) {
            फर्काऊ SDL_SetError("Invalid destination blit rectangle");
        }
    } अन्यथा {
        full_dst.x = 0;
        full_dst.y = 0;
        full_dst.w = dst->w;
        full_dst.h = dst->h;
        dstrect = &full_dst;
    }

    यदि (dstrect->w <= 0 || dstrect->h <= 0) {
        फर्काऊ true;
    }

    यदि (srcrect->w > SDL_MAX_UINT16 || srcrect->h > SDL_MAX_UINT16 ||
        dstrect->w > SDL_MAX_UINT16 || dstrect->h > SDL_MAX_UINT16) {
        फर्काऊ SDL_SetError("Size too large for scaling");
    }

    // Lock the destination if it's in hardware
    dst_locked = 0;
    यदि (SDL_MUSTLOCK(dst)) {
        यदि (!SDL_LockSurface(dst)) {
            फर्काऊ SDL_SetError("Unable to lock destination surface");
        }
        dst_locked = 1;
    }
    // Lock the source if it's in hardware
    src_locked = 0;
    यदि (SDL_MUSTLOCK(src)) {
        यदि (!SDL_LockSurface(src)) {
            यदि (dst_locked) {
                SDL_UnlockSurface(dst);
            }
            फर्काऊ SDL_SetError("Unable to lock source surface");
        }
        src_locked = 1;
    }

    यदि (scaleMode == SDL_SCALEMODE_NEAREST) {
        result = SDL_StretchSurfaceUncheckedNearest(src, srcrect, dst, dstrect);
    } अन्यथा {
        result = SDL_StretchSurfaceUncheckedLinear(src, srcrect, dst, dstrect);
    }

    // We need to unlock the surfaces if they're locked
    यदि (dst_locked) {
        SDL_UnlockSurface(dst);
    }
    यदि (src_locked) {
        SDL_UnlockSurface(src);
    }

    फर्काऊ result;
}

/* bilinear interpolation precision must be < 8
   Because with SSE: add-multiply: _mm_madd_epi16 works with signed int
   so pixels 0xb1...... are negatives and false the result
   same in NEON probably */
#define PRECISION 7

#define FIXED_POINT(i) ((Uint32)(i) << 16)
#define SRC_INDEX(fp)  ((Uint32)(fp) >> 16)
#define INTEGER(fp)    ((Uint32)(fp) >> PRECISION)
#define FRAC(fp)       ((Uint32)((fp) >> (16 - PRECISION)) & ((1 << PRECISION) - 1))
#define FRAC_ZERO      0
#define FRAC_ONE       (1 << PRECISION)
#define FP_ONE         FIXED_POINT(1)

#define BILINEAR___START                                                              \
    पूर्णाङ्क i;                                                                            \
    Sint64 fp_sum_h;                                                                  \
    पूर्णाङ्क fp_step_h, बायाँ_pad_h, दायाँ_pad_h;                                           \
    Sint64 fp_sum_w;                                                                  \
    पूर्णाङ्क fp_step_w, बायाँ_pad_w, दायाँ_pad_w;                                           \
    Sint64 fp_sum_w_init;                                                             \
    पूर्णाङ्क बायाँ_pad_w_init, दायाँ_pad_w_init, dst_gap, बीच_init;                      \
    get_scaler_datas(src_h, dst_h, &fp_sum_h, &fp_step_h, &बायाँ_pad_h, &दायाँ_pad_h); \
    get_scaler_datas(src_w, dst_w, &fp_sum_w, &fp_step_w, &बायाँ_pad_w, &दायाँ_pad_w); \
    fp_sum_w_init = fp_sum_w + बायाँ_pad_w * fp_step_w;                                \
    बायाँ_pad_w_init = बायाँ_pad_w;                                                     \
    दायाँ_pad_w_init = दायाँ_pad_w;                                                   \
    dst_gap = dst_pitch - 4 * dst_w;                                                  \
    बीच_init = dst_w - बायाँ_pad_w - दायाँ_pad_w;

#define BILINEAR___HEIGHT                                              \
    पूर्णाङ्क index_h, frac_h0, frac_h1, बीच;                             \
    अचर Uint32 *src_h0, *src_h1;                                     \
    पूर्णाङ्क no_padding;                                                    \
    Uint64 incr_h0, incr_h1;                                           \
                                                                       \
    no_padding = !(i < बायाँ_pad_h || i > dst_h - 1 - दायाँ_pad_h);     \
    index_h = SRC_INDEX(fp_sum_h);                                     \
    frac_h0 = FRAC(fp_sum_h);                                          \
                                                                       \
    index_h = no_padding ? index_h : (i < बायाँ_pad_h ? 0 : src_h - 1); \
    frac_h0 = no_padding ? frac_h0 : 0;                                \
    incr_h1 = no_padding ? src_pitch : 0;                              \
    incr_h0 = (Uint64)index_h * src_pitch;                             \
                                                                       \
    src_h0 = (अचर Uint32 *)((अचर Uint8 *)src + incr_h0);           \
    src_h1 = (अचर Uint32 *)((अचर Uint8 *)src_h0 + incr_h1);        \
                                                                       \
    fp_sum_h += fp_step_h;                                             \
                                                                       \
    frac_h1 = FRAC_ONE - frac_h0;                                      \
    fp_sum_w = fp_sum_w_init;                                          \
    दायाँ_pad_w = दायाँ_pad_w_init;                                    \
    बायाँ_pad_w = बायाँ_pad_w_init;                                      \
    बीच = बीच_init;

#ifdef __clang__
// Remove inlining of this function
// Compiler crash with clang 9.0.8 / android-ndk-r21d
// Compiler crash with clang 11.0.3 / Xcode
// OK with clang 11.0.5 / android-ndk-22
// OK with clang 12.0.0 / Xcode
__attribute__((noinline))
#endif
स्थिर शून्य get_scaler_datas(पूर्णाङ्क src_nb, पूर्णाङ्क dst_nb, Sint64 *fp_start, पूर्णाङ्क *fp_step, पूर्णाङ्क *बायाँ_pad, पूर्णाङ्क *दायाँ_pad)
{

    पूर्णाङ्क step = FIXED_POINT(src_nb) / (dst_nb); // source step in fixed point
    पूर्णाङ्क x0 = FP_ONE / 2;                       // dst first pixel center at 0.5 in fixed point
    Sint64 fp_sum;
    पूर्णाङ्क i;
#यदि 0
    // scale to source coordinates
    x0 *= src_nb;
    x0 /= dst_nb; // x0 == step / 2
#अन्यथा
    // Use this code for perfect match with pixman
    Sint64 tmp[2];
    tmp[0] = (Sint64)step * (x0 >> 16);
    tmp[1] = (Sint64)step * (x0 & 0xFFFF);
    x0 = (पूर्णाङ्क)(tmp[0] + ((tmp[1] + 0x8000) >> 16)); // x0 == (step + 1) / 2
#endif
    // -= 0.5, get back the pixel origin, in source coordinates
    x0 -= FP_ONE / 2;

    *fp_start = x0;
    *fp_step = step;
    *बायाँ_pad = 0;
    *दायाँ_pad = 0;

    fp_sum = x0;
    लागि (i = 0; i < dst_nb; i++) {
        यदि (fp_sum < 0) {
            *बायाँ_pad += 1;
        } अन्यथा {
            पूर्णाङ्क index = SRC_INDEX(fp_sum);
            यदि (index > src_nb - 2) {
                *दायाँ_pad += 1;
            }
        }
        fp_sum += step;
    }
    //    SDL_Log("%d -> %d  x0=%d step=%d left_pad=%d right_pad=%d", src_nb, dst_nb, *fp_start, *fp_step, *left_pad, *right_pad);
}

प्रकारनिर्देश संरचना color_t
{
    Uint8 a;
    Uint8 b;
    Uint8 c;
    Uint8 d;
} color_t;

/* Interpolated == x0 + frac * (x1 - x0) == x0 * (1 - frac) + x1 * frac */

स्थिर SDL_INLINE शून्य INTERPOL(अचर Uint32 *src_x0, अचर Uint32 *src_x1, पूर्णाङ्क frac0, पूर्णाङ्क frac1, Uint32 *dst)
{
    अचर color_t *c0 = (अचर color_t *)src_x0;
    अचर color_t *c1 = (अचर color_t *)src_x1;
    color_t *cx = (color_t *)dst;
#यदि 0
    cx->a = c0->a + INTEGER(frac0 * (c1->a - c0->a));
    cx->b = c0->b + INTEGER(frac0 * (c1->b - c0->b));
    cx->c = c0->c + INTEGER(frac0 * (c1->c - c0->c));
    cx->d = c0->d + INTEGER(frac0 * (c1->d - c0->d));
#अन्यथा
    cx->a = (Uint8)INTEGER(frac1 * c0->a + frac0 * c1->a);
    cx->b = (Uint8)INTEGER(frac1 * c0->b + frac0 * c1->b);
    cx->c = (Uint8)INTEGER(frac1 * c0->c + frac0 * c1->c);
    cx->d = (Uint8)INTEGER(frac1 * c0->d + frac0 * c1->d);
#endif
}

स्थिर SDL_INLINE शून्य INTERPOL_BILINEAR(अचर Uint32 *s0, अचर Uint32 *s1, पूर्णाङ्क frac_w0, पूर्णाङ्क frac_h0, पूर्णाङ्क frac_h1, Uint32 *dst)
{
    Uint32 tmp[2];
    अचिन्हित पूर्णाङ्क frac_w1 = FRAC_ONE - frac_w0;

    // Vertical first, store to 'tmp'
    INTERPOL(s0, s1, frac_h0, frac_h1, tmp);
    INTERPOL(s0 + 1, s1 + 1, frac_h0, frac_h1, tmp + 1);

    // Horizontal, store to 'dst'
    INTERPOL(tmp, tmp + 1, frac_w0, frac_w1, dst);
}

स्थिर bool scale_mat(अचर Uint32 *src, पूर्णाङ्क src_w, पूर्णाङ्क src_h, पूर्णाङ्क src_pitch, Uint32 *dst, पूर्णाङ्क dst_w, पूर्णाङ्क dst_h, पूर्णाङ्क dst_pitch)
{
    BILINEAR___START

    लागि (i = 0; i < dst_h; i++) {

        BILINEAR___HEIGHT

        जबसम्म (बायाँ_pad_w--) {
            INTERPOL_BILINEAR(src_h0, src_h1, FRAC_ZERO, frac_h0, frac_h1, dst);
            dst += 1;
        }

        जबसम्म (बीच--) {
            अचर Uint32 *s_00_01;
            अचर Uint32 *s_10_11;
            पूर्णाङ्क index_w = 4 * SRC_INDEX(fp_sum_w);
            पूर्णाङ्क frac_w = FRAC(fp_sum_w);
            fp_sum_w += fp_step_w;

            /*
                        x00 ... x0_ ..... x01
                        .       .         .
                        .       x         .
                        .       .         .
                        .       .         .
                        x10 ... x1_ ..... x11
            */
            s_00_01 = (अचर Uint32 *)((अचर Uint8 *)src_h0 + index_w);
            s_10_11 = (अचर Uint32 *)((अचर Uint8 *)src_h1 + index_w);

            INTERPOL_BILINEAR(s_00_01, s_10_11, frac_w, frac_h0, frac_h1, dst);

            dst += 1;
        }

        जबसम्म (दायाँ_pad_w--) {
            पूर्णाङ्क index_w = 4 * (src_w - 2);
            अचर Uint32 *s_00_01 = (अचर Uint32 *)((अचर Uint8 *)src_h0 + index_w);
            अचर Uint32 *s_10_11 = (अचर Uint32 *)((अचर Uint8 *)src_h1 + index_w);
            INTERPOL_BILINEAR(s_00_01, s_10_11, FRAC_ONE, frac_h0, frac_h1, dst);
            dst += 1;
        }
        dst = (Uint32 *)((Uint8 *)dst + dst_gap);
    }
    फर्काऊ true;
}

#ifdef SDL_SSE2_INTRINSICS

स्थिर SDL_INLINE पूर्णाङ्क hasSSE2(शून्य)
{
    स्थिर पूर्णाङ्क val = -1;
    यदि (val != -1) {
        फर्काऊ val;
    }
    val = SDL_HasSSE2();
    फर्काऊ val;
}

स्थिर SDL_INLINE शून्य SDL_TARGETING("sse2") INTERPOL_BILINEAR_SSE(अचर Uint32 *s0, अचर Uint32 *s1, पूर्णाङ्क frac_w, __m128i v_frac_h0, __m128i v_frac_h1, Uint32 *dst, __m128i zero)
{
    __m128i x_00_01, x_10_11; /* Pixels in 4*uint8 in row */
    __m128i v_frac_w0, k0, l0, d0, e0;

    पूर्णाङ्क f, f2;
    f = frac_w;
    f2 = FRAC_ONE - frac_w;
    v_frac_w0 = _mm_set_epi16((लघु)f, (लघु)f2, (लघु)f, (लघु)f2, (लघु)f, (लघु)f2, (लघु)f, (लघु)f2);

    x_00_01 = _mm_loadl_epi64((अचर __m128i *)s0); // Load x00 and x01
    x_10_11 = _mm_loadl_epi64((अचर __m128i *)s1);

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

स्थिर bool SDL_TARGETING("sse2") scale_mat_SSE(अचर Uint32 *src, पूर्णाङ्क src_w, पूर्णाङ्क src_h, पूर्णाङ्क src_pitch, Uint32 *dst, पूर्णाङ्क dst_w, पूर्णाङ्क dst_h, पूर्णाङ्क dst_pitch)
{
    BILINEAR___START

    लागि (i = 0; i < dst_h; i++) {
        पूर्णाङ्क nb_block2;
        __m128i v_frac_h0;
        __m128i v_frac_h1;
        __m128i zero;

        BILINEAR___HEIGHT

        nb_block2 = बीच / 2;

        v_frac_h0 = _mm_set_epi16((लघु)frac_h0, (लघु)frac_h0, (लघु)frac_h0, (लघु)frac_h0, (लघु)frac_h0, (लघु)frac_h0, (लघु)frac_h0, (लघु)frac_h0);
        v_frac_h1 = _mm_set_epi16((लघु)frac_h1, (लघु)frac_h1, (लघु)frac_h1, (लघु)frac_h1, (लघु)frac_h1, (लघु)frac_h1, (लघु)frac_h1, (लघु)frac_h1);
        zero = _mm_setzero_si128();

        जबसम्म (बायाँ_pad_w--) {
            INTERPOL_BILINEAR_SSE(src_h0, src_h1, FRAC_ZERO, v_frac_h0, v_frac_h1, dst, zero);
            dst += 1;
        }

        जबसम्म (nb_block2--) {
            पूर्णाङ्क index_w_0, frac_w_0;
            पूर्णाङ्क index_w_1, frac_w_1;

            अचर Uint32 *s_00_01, *s_02_03, *s_10_11, *s_12_13;

            __m128i x_00_01, x_10_11, x_02_03, x_12_13; /* Pixels in 4*uint8 in row */
            __m128i v_frac_w0, k0, l0, d0, e0;
            __m128i v_frac_w1, k1, l1, d1, e1;

            पूर्णाङ्क f, f2;
            index_w_0 = 4 * SRC_INDEX(fp_sum_w);
            frac_w_0 = FRAC(fp_sum_w);
            fp_sum_w += fp_step_w;
            index_w_1 = 4 * SRC_INDEX(fp_sum_w);
            frac_w_1 = FRAC(fp_sum_w);
            fp_sum_w += fp_step_w;
            /*
                        x00............ x01   x02...........x03
                        .      .         .     .       .     .
                        j0     f0        j1    j2      f1    j3
                        .      .         .     .       .     .
                        .      .         .     .       .     .
                        .      .         .     .       .     .
                        x10............ x11   x12...........x13
             */
            s_00_01 = (अचर Uint32 *)((अचर Uint8 *)src_h0 + index_w_0);
            s_02_03 = (अचर Uint32 *)((अचर Uint8 *)src_h0 + index_w_1);
            s_10_11 = (अचर Uint32 *)((अचर Uint8 *)src_h1 + index_w_0);
            s_12_13 = (अचर Uint32 *)((अचर Uint8 *)src_h1 + index_w_1);

            f = frac_w_0;
            f2 = FRAC_ONE - frac_w_0;
            v_frac_w0 = _mm_set_epi16((लघु)f, (लघु)f2, (लघु)f, (लघु)f2, (लघु)f, (लघु)f2, (लघु)f, (लघु)f2);

            f = frac_w_1;
            f2 = FRAC_ONE - frac_w_1;
            v_frac_w1 = _mm_set_epi16((लघु)f, (लघु)f2, (लघु)f, (लघु)f2, (लघु)f, (लघु)f2, (लघु)f, (लघु)f2);

            x_00_01 = _mm_loadl_epi64((अचर __m128i *)s_00_01); // Load x00 and x01
            x_02_03 = _mm_loadl_epi64((अचर __m128i *)s_02_03);
            x_10_11 = _mm_loadl_epi64((अचर __m128i *)s_10_11);
            x_12_13 = _mm_loadl_epi64((अचर __m128i *)s_12_13);

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
        यदि (बीच & 0x1) {
            अचर Uint32 *s_00_01;
            अचर Uint32 *s_10_11;
            पूर्णाङ्क index_w = 4 * SRC_INDEX(fp_sum_w);
            पूर्णाङ्क frac_w = FRAC(fp_sum_w);
            fp_sum_w += fp_step_w;
            s_00_01 = (अचर Uint32 *)((अचर Uint8 *)src_h0 + index_w);
            s_10_11 = (अचर Uint32 *)((अचर Uint8 *)src_h1 + index_w);
            INTERPOL_BILINEAR_SSE(s_00_01, s_10_11, frac_w, v_frac_h0, v_frac_h1, dst, zero);
            dst += 1;
        }

        जबसम्म (दायाँ_pad_w--) {
            पूर्णाङ्क index_w = 4 * (src_w - 2);
            अचर Uint32 *s_00_01 = (अचर Uint32 *)((अचर Uint8 *)src_h0 + index_w);
            अचर Uint32 *s_10_11 = (अचर Uint32 *)((अचर Uint8 *)src_h1 + index_w);
            INTERPOL_BILINEAR_SSE(s_00_01, s_10_11, FRAC_ONE, v_frac_h0, v_frac_h1, dst, zero);
            dst += 1;
        }
        dst = (Uint32 *)((Uint8 *)dst + dst_gap);
    }
    फर्काऊ true;
}
#endif

#ifdef SDL_NEON_INTRINSICS

स्थिर SDL_INLINE पूर्णाङ्क hasNEON(शून्य)
{
    स्थिर पूर्णाङ्क val = -1;
    यदि (val != -1) {
        फर्काऊ val;
    }
    val = SDL_HasNEON();
    फर्काऊ val;
}

स्थिर SDL_INLINE शून्य INTERPOL_BILINEAR_NEON(अचर Uint32 *s0, अचर Uint32 *s1, पूर्णाङ्क frac_w, uint8x8_t v_frac_h0, uint8x8_t v_frac_h1, Uint32 *dst)
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
    l0 = vshll_n_u16(vget_तल्लो_u16(k0), PRECISION);
    l0 = vmlsl_n_u16(l0, vget_तल्लो_u16(k0), frac_w);
    l0 = vmlal_n_u16(l0, vget_माथिल्लो_u16(k0), frac_w);

    // Shift and narrow
    d0 = vcombine_u16(
        /* uint16x4_t */ vshrn_n_u32(l0, 2 * PRECISION),
        /* uint16x4_t */ vshrn_n_u32(l0, 2 * PRECISION));

    // Narrow again
    e0 = vmovn_u16(d0);

    // Store 1 pixel
    *dst = vget_lane_u32(vreinterpret_u32_u8(e0), 0);
}

स्थिर bool scale_mat_NEON(अचर Uint32 *src, पूर्णाङ्क src_w, पूर्णाङ्क src_h, पूर्णाङ्क src_pitch, Uint32 *dst, पूर्णाङ्क dst_w, पूर्णाङ्क dst_h, पूर्णाङ्क dst_pitch)
{
    BILINEAR___START

    लागि (i = 0; i < dst_h; i++) {
        पूर्णाङ्क nb_block4;
        uint8x8_t v_frac_h0, v_frac_h1;

        BILINEAR___HEIGHT

        nb_block4 = बीच / 4;

        v_frac_h0 = vmov_n_u8(frac_h0);
        v_frac_h1 = vmov_n_u8(frac_h1);

        जबसम्म (बायाँ_pad_w--) {
            INTERPOL_BILINEAR_NEON(src_h0, src_h1, FRAC_ZERO, v_frac_h0, v_frac_h1, dst);
            dst += 1;
        }

        जबसम्म (nb_block4--) {
            पूर्णाङ्क index_w_0, frac_w_0;
            पूर्णाङ्क index_w_1, frac_w_1;
            पूर्णाङ्क index_w_2, frac_w_2;
            पूर्णाङ्क index_w_3, frac_w_3;

            अचर Uint32 *s_00_01, *s_02_03, *s_04_05, *s_06_07;
            अचर Uint32 *s_10_11, *s_12_13, *s_14_15, *s_16_17;

            uint8x8_t x_00_01, x_10_11, x_02_03, x_12_13; /* Pixels in 4*uint8 in row */
            uint8x8_t x_04_05, x_14_15, x_06_07, x_16_17;

            uint16x8_t k0, k1, k2, k3;
            uint32x4_t l0, l1, l2, l3;
            uint16x8_t d0, d1;
            uint8x8_t e0, e1;
            uint32x4_t f0;

            index_w_0 = 4 * SRC_INDEX(fp_sum_w);
            frac_w_0 = FRAC(fp_sum_w);
            fp_sum_w += fp_step_w;
            index_w_1 = 4 * SRC_INDEX(fp_sum_w);
            frac_w_1 = FRAC(fp_sum_w);
            fp_sum_w += fp_step_w;
            index_w_2 = 4 * SRC_INDEX(fp_sum_w);
            frac_w_2 = FRAC(fp_sum_w);
            fp_sum_w += fp_step_w;
            index_w_3 = 4 * SRC_INDEX(fp_sum_w);
            frac_w_3 = FRAC(fp_sum_w);
            fp_sum_w += fp_step_w;

            s_00_01 = (अचर Uint32 *)((अचर Uint8 *)src_h0 + index_w_0);
            s_02_03 = (अचर Uint32 *)((अचर Uint8 *)src_h0 + index_w_1);
            s_04_05 = (अचर Uint32 *)((अचर Uint8 *)src_h0 + index_w_2);
            s_06_07 = (अचर Uint32 *)((अचर Uint8 *)src_h0 + index_w_3);
            s_10_11 = (अचर Uint32 *)((अचर Uint8 *)src_h1 + index_w_0);
            s_12_13 = (अचर Uint32 *)((अचर Uint8 *)src_h1 + index_w_1);
            s_14_15 = (अचर Uint32 *)((अचर Uint8 *)src_h1 + index_w_2);
            s_16_17 = (अचर Uint32 *)((अचर Uint8 *)src_h1 + index_w_3);

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

            l0 = vshll_n_u16(vget_तल्लो_u16(k0), PRECISION);
            l0 = vmlsl_n_u16(l0, vget_तल्लो_u16(k0), frac_w_0);
            l0 = vmlal_n_u16(l0, vget_माथिल्लो_u16(k0), frac_w_0);

            l1 = vshll_n_u16(vget_तल्लो_u16(k1), PRECISION);
            l1 = vmlsl_n_u16(l1, vget_तल्लो_u16(k1), frac_w_1);
            l1 = vmlal_n_u16(l1, vget_माथिल्लो_u16(k1), frac_w_1);

            l2 = vshll_n_u16(vget_तल्लो_u16(k2), PRECISION);
            l2 = vmlsl_n_u16(l2, vget_तल्लो_u16(k2), frac_w_2);
            l2 = vmlal_n_u16(l2, vget_माथिल्लो_u16(k2), frac_w_2);

            l3 = vshll_n_u16(vget_तल्लो_u16(k3), PRECISION);
            l3 = vmlsl_n_u16(l3, vget_तल्लो_u16(k3), frac_w_3);
            l3 = vmlal_n_u16(l3, vget_माथिल्लो_u16(k3), frac_w_3);

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

        यदि (बीच & 0x2) {
            पूर्णाङ्क index_w_0, frac_w_0;
            पूर्णाङ्क index_w_1, frac_w_1;
            अचर Uint32 *s_00_01, *s_02_03;
            अचर Uint32 *s_10_11, *s_12_13;
            uint8x8_t x_00_01, x_10_11, x_02_03, x_12_13; /* Pixels in 4*uint8 in row */
            uint16x8_t k0, k1;
            uint32x4_t l0, l1;
            uint16x8_t d0;
            uint8x8_t e0;

            index_w_0 = 4 * SRC_INDEX(fp_sum_w);
            frac_w_0 = FRAC(fp_sum_w);
            fp_sum_w += fp_step_w;
            index_w_1 = 4 * SRC_INDEX(fp_sum_w);
            frac_w_1 = FRAC(fp_sum_w);
            fp_sum_w += fp_step_w;
            /*
                        x00............ x01   x02...........x03
                        .      .         .     .       .     .
                        j0   dest0       j1    j2    dest1   j3
                        .      .         .     .       .     .
                        .      .         .     .       .     .
                        .      .         .     .       .     .
                        x10............ x11   x12...........x13
            */
            s_00_01 = (अचर Uint32 *)((अचर Uint8 *)src_h0 + index_w_0);
            s_02_03 = (अचर Uint32 *)((अचर Uint8 *)src_h0 + index_w_1);
            s_10_11 = (अचर Uint32 *)((अचर Uint8 *)src_h1 + index_w_0);
            s_12_13 = (अचर Uint32 *)((अचर Uint8 *)src_h1 + index_w_1);

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

            l0 = vshll_n_u16(vget_तल्लो_u16(k0), PRECISION);
            l0 = vmlsl_n_u16(l0, vget_तल्लो_u16(k0), frac_w_0);
            l0 = vmlal_n_u16(l0, vget_माथिल्लो_u16(k0), frac_w_0);

            l1 = vshll_n_u16(vget_तल्लो_u16(k1), PRECISION);
            l1 = vmlsl_n_u16(l1, vget_तल्लो_u16(k1), frac_w_1);
            l1 = vmlal_n_u16(l1, vget_माथिल्लो_u16(k1), frac_w_1);

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
        यदि (बीच & 0x1) {
            पूर्णाङ्क index_w = 4 * SRC_INDEX(fp_sum_w);
            पूर्णाङ्क frac_w = FRAC(fp_sum_w);
            अचर Uint32 *s_00_01 = (अचर Uint32 *)((अचर Uint8 *)src_h0 + index_w);
            अचर Uint32 *s_10_11 = (अचर Uint32 *)((अचर Uint8 *)src_h1 + index_w);
            INTERPOL_BILINEAR_NEON(s_00_01, s_10_11, frac_w, v_frac_h0, v_frac_h1, dst);
            dst += 1;
        }

        जबसम्म (दायाँ_pad_w--) {
            पूर्णाङ्क index_w = 4 * (src_w - 2);
            अचर Uint32 *s_00_01 = (अचर Uint32 *)((अचर Uint8 *)src_h0 + index_w);
            अचर Uint32 *s_10_11 = (अचर Uint32 *)((अचर Uint8 *)src_h1 + index_w);
            INTERPOL_BILINEAR_NEON(s_00_01, s_10_11, FRAC_ONE, v_frac_h0, v_frac_h1, dst);
            dst += 1;
        }

        dst = (Uint32 *)((Uint8 *)dst + dst_gap);
    }
    फर्काऊ true;
}
#endif

bool SDL_StretchSurfaceUncheckedLinear(SDL_Surface *s, अचर SDL_Rect *srcrect, SDL_Surface *d, अचर SDL_Rect *dstrect)
{
    bool result = false;
    पूर्णाङ्क src_w = srcrect->w;
    पूर्णाङ्क src_h = srcrect->h;
    पूर्णाङ्क dst_w = dstrect->w;
    पूर्णाङ्क dst_h = dstrect->h;
    पूर्णाङ्क src_pitch = s->pitch;
    पूर्णाङ्क dst_pitch = d->pitch;
    Uint32 *src = (Uint32 *)((Uint8 *)s->pixels + srcrect->x * 4 + srcrect->y * src_pitch);
    Uint32 *dst = (Uint32 *)((Uint8 *)d->pixels + dstrect->x * 4 + dstrect->y * dst_pitch);

#ifdef SDL_NEON_INTRINSICS
    यदि (!result && hasNEON()) {
        result = scale_mat_NEON(src, src_w, src_h, src_pitch, dst, dst_w, dst_h, dst_pitch);
    }
#endif

#ifdef SDL_SSE2_INTRINSICS
    यदि (!result && hasSSE2()) {
        result = scale_mat_SSE(src, src_w, src_h, src_pitch, dst, dst_w, dst_h, dst_pitch);
    }
#endif

    यदि (!result) {
        result = scale_mat(src, src_w, src_h, src_pitch, dst, dst_w, dst_h, dst_pitch);
    }

    फर्काऊ result;
}

#define SDL_SCALE_NEAREST__START          \
    पूर्णाङ्क i;                                \
    Uint64 posy, incy;                    \
    Uint64 posx, incx;                    \
    Uint64 srcy, srcx;                    \
    पूर्णाङ्क dst_gap, n;                       \
    अचर Uint32 *src_h0;                 \
    incy = ((Uint64)src_h << 16) / dst_h; \
    incx = ((Uint64)src_w << 16) / dst_w; \
    dst_gap = dst_pitch - bpp * dst_w;    \
    posy = incy / 2;

#define SDL_SCALE_NEAREST__HEIGHT                                         \
    srcy = (posy >> 16);                                                  \
    src_h0 = (अचर Uint32 *)((अचर Uint8 *)src_ptr + srcy * src_pitch); \
    posy += incy;                                                         \
    posx = incx / 2;                                                      \
    n = dst_w;

स्थिर bool scale_mat_nearest_1(अचर Uint32 *src_ptr, पूर्णाङ्क src_w, पूर्णाङ्क src_h, पूर्णाङ्क src_pitch, Uint32 *dst, पूर्णाङ्क dst_w, पूर्णाङ्क dst_h, पूर्णाङ्क dst_pitch)
{
    Uint32 bpp = 1;
    SDL_SCALE_NEAREST__START
    लागि (i = 0; i < dst_h; i++) {
        SDL_SCALE_NEAREST__HEIGHT
        जबसम्म (n--) {
            अचर Uint8 *src;
            srcx = bpp * (posx >> 16);
            posx += incx;
            src = (अचर Uint8 *)src_h0 + srcx;
            *(Uint8 *)dst = *src;
            dst = (Uint32 *)((Uint8 *)dst + bpp);
        }
        dst = (Uint32 *)((Uint8 *)dst + dst_gap);
    }
    फर्काऊ true;
}

स्थिर bool scale_mat_nearest_2(अचर Uint32 *src_ptr, पूर्णाङ्क src_w, पूर्णाङ्क src_h, पूर्णाङ्क src_pitch, Uint32 *dst, पूर्णाङ्क dst_w, पूर्णाङ्क dst_h, पूर्णाङ्क dst_pitch)
{
    Uint32 bpp = 2;
    SDL_SCALE_NEAREST__START
    लागि (i = 0; i < dst_h; i++) {
        SDL_SCALE_NEAREST__HEIGHT
        जबसम्म (n--) {
            अचर Uint16 *src;
            srcx = bpp * (posx >> 16);
            posx += incx;
            src = (अचर Uint16 *)((अचर Uint8 *)src_h0 + srcx);
            *(Uint16 *)dst = *src;
            dst = (Uint32 *)((Uint8 *)dst + bpp);
        }
        dst = (Uint32 *)((Uint8 *)dst + dst_gap);
    }
    फर्काऊ true;
}

स्थिर bool scale_mat_nearest_3(अचर Uint32 *src_ptr, पूर्णाङ्क src_w, पूर्णाङ्क src_h, पूर्णाङ्क src_pitch, Uint32 *dst, पूर्णाङ्क dst_w, पूर्णाङ्क dst_h, पूर्णाङ्क dst_pitch)
{
    Uint32 bpp = 3;
    SDL_SCALE_NEAREST__START
    लागि (i = 0; i < dst_h; i++) {
        SDL_SCALE_NEAREST__HEIGHT
        जबसम्म (n--) {
            अचर Uint8 *src;
            srcx = bpp * (posx >> 16);
            posx += incx;
            src = (अचर Uint8 *)src_h0 + srcx;
            ((Uint8 *)dst)[0] = src[0];
            ((Uint8 *)dst)[1] = src[1];
            ((Uint8 *)dst)[2] = src[2];
            dst = (Uint32 *)((Uint8 *)dst + bpp);
        }
        dst = (Uint32 *)((Uint8 *)dst + dst_gap);
    }
    फर्काऊ true;
}

स्थिर bool scale_mat_nearest_4(अचर Uint32 *src_ptr, पूर्णाङ्क src_w, पूर्णाङ्क src_h, पूर्णाङ्क src_pitch, Uint32 *dst, पूर्णाङ्क dst_w, पूर्णाङ्क dst_h, पूर्णाङ्क dst_pitch)
{
    Uint32 bpp = 4;
    SDL_SCALE_NEAREST__START
    लागि (i = 0; i < dst_h; i++) {
        SDL_SCALE_NEAREST__HEIGHT
        जबसम्म (n--) {
            अचर Uint32 *src;
            srcx = bpp * (posx >> 16);
            posx += incx;
            src = (अचर Uint32 *)((अचर Uint8 *)src_h0 + srcx);
            *dst = *src;
            dst = (Uint32 *)((Uint8 *)dst + bpp);
        }
        dst = (Uint32 *)((Uint8 *)dst + dst_gap);
    }
    फर्काऊ true;
}

bool SDL_StretchSurfaceUncheckedNearest(SDL_Surface *s, अचर SDL_Rect *srcrect, SDL_Surface *d, अचर SDL_Rect *dstrect)
{
    पूर्णाङ्क src_w = srcrect->w;
    पूर्णाङ्क src_h = srcrect->h;
    पूर्णाङ्क dst_w = dstrect->w;
    पूर्णाङ्क dst_h = dstrect->h;
    पूर्णाङ्क src_pitch = s->pitch;
    पूर्णाङ्क dst_pitch = d->pitch;
    पूर्णाङ्क bpp = SDL_BYTESPERPIXEL(d->format);

    Uint32 *src = (Uint32 *)((Uint8 *)s->pixels + srcrect->x * bpp + srcrect->y * src_pitch);
    Uint32 *dst = (Uint32 *)((Uint8 *)d->pixels + dstrect->x * bpp + dstrect->y * dst_pitch);

    यदि (bpp == 4) {
        फर्काऊ scale_mat_nearest_4(src, src_w, src_h, src_pitch, dst, dst_w, dst_h, dst_pitch);
    } अन्यथा यदि (bpp == 3) {
        फर्काऊ scale_mat_nearest_3(src, src_w, src_h, src_pitch, dst, dst_w, dst_h, dst_pitch);
    } अन्यथा यदि (bpp == 2) {
        फर्काऊ scale_mat_nearest_2(src, src_w, src_h, src_pitch, dst, dst_w, dst_h, dst_pitch);
    } अन्यथा {
        फर्काऊ scale_mat_nearest_1(src, src_w, src_h, src_pitch, dst, dst_w, dst_h, dst_pitch);
    }
}
