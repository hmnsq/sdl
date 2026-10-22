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

ساکن bool SDL_Stretch_Surface_Unchecked_قریب_ترین(SDL_Surface *src, ثابت SDL_Rect *srcrect, SDL_Surface *dst, ثابت SDL_Rect *dstrect);
ساکن bool SDL_Stretch_Surface_Unchecked_خطی(SDL_Surface *src, ثابت SDL_Rect *srcrect, SDL_Surface *dst, ثابت SDL_Rect *dstrect);

bool SDL_StretchSurface(SDL_Surface *src, ثابت SDL_Rect *srcrect, SDL_Surface *dst, ثابت SDL_Rect *dstrect, SDL_Scale_منوال scale_منوال)
{
    bool نتیجہ;
    صحیح src_locked;
    صحیح dst_locked;
    SDL_Rect بھرا_src;
    SDL_Rect بھرا_dst;

    CHECK_PARAM(!src) {
        واپس SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!dst) {
        واپس SDL_InvalidParamError("dst");
    }

    اگر (src->format != dst->format) {
        // Slow!
        SDL_Surface *src_tmp = SDL_ConvertSurfaceAndColorspace(src, dst->format, dst->palette, dst->colorspace, dst->props);
        اگر (!src_tmp) {
            واپس false;
        }
        نتیجہ = SDL_StretchSurface(src_tmp, srcrect, dst, dstrect, scale_منوال);
        SDL_DestroySurface(src_tmp);
        واپس نتیجہ;
    }

    اگر (SDL_ISPIXELFORMAT_FOURCC(src->format)) {
        // Slow!
        اگر (!dstrect) {
            بھرا_dst.x = 0;
            بھرا_dst.y = 0;
            بھرا_dst.w = dst->w;
            بھرا_dst.h = dst->h;
            dstrect = &بھرا_dst;
        }

        SDL_Surface *src_tmp = SDL_ConvertSurface(src, SDL_PIXELFORMAT_XRGB8888);
        SDL_Surface *dst_tmp = SDL_CreateSurfaceUninitialized(dstrect->w, dstrect->h, SDL_PIXELFORMAT_XRGB8888);
        اگر (src_tmp && dst_tmp) {
            نتیجہ = SDL_StretchSurface(src_tmp, srcrect, dst_tmp, تہی, scale_منوال);
            اگر (نتیجہ) {
                نتیجہ = SDL_ConvertPixelsAndColorspace(dstrect->w, dstrect->h,
                            dst_tmp->format, SDL_COLORSPACE_SRGB, 0,
                            dst_tmp->pixels, dst_tmp->pitch,
                            dst->format, dst->colorspace, SDL_GetSurfaceProperties(dst),
                            (Uint8 *)dst->pixels + dstrect->y * dst->pitch + dstrect->x * SDL_BYTESPERPIXEL(dst->format), dst->pitch);
            }
        } ورنہ {
            نتیجہ = false;
        }
        SDL_DestroySurface(src_tmp);
        SDL_DestroySurface(dst_tmp);
        واپس نتیجہ;
    }

    انتخاب (scale_منوال) {
    حالت SDL_SCALEMODE_قریب_ترین:
        توڑو;
    حالت SDL_SCALEMODE_خطی:
        توڑو;
    حالت SDL_SCALEMODE_PIXELART:
        scale_منوال = SDL_SCALEMODE_قریب_ترین;
        توڑو;
    طےشدہ:
        واپس SDL_InvalidParamError("scaleMode");
    }

    اگر (scale_منوال == SDL_SCALEMODE_خطی) {
        اگر (SDL_BYTESPERPIXEL(src->format) != 4 || src->format == SDL_PIXELFORMAT_ARGB2101010) {
            واپس SDL_سیٹ_Error("Wrong format");
        }
    }

    // Verify the blit rectangles
    اگر (srcrect) {
        اگر ((srcrect->x < 0) || (srcrect->y < 0) ||
            ((srcrect->x + srcrect->w) > src->w) ||
            ((srcrect->y + srcrect->h) > src->h)) {
            واپس SDL_سیٹ_Error("Invalid source blit rectangle");
        }
    } ورنہ {
        بھرا_src.x = 0;
        بھرا_src.y = 0;
        بھرا_src.w = src->w;
        بھرا_src.h = src->h;
        srcrect = &بھرا_src;
    }
    اگر (dstrect) {
        اگر ((dstrect->x < 0) || (dstrect->y < 0) ||
            ((dstrect->x + dstrect->w) > dst->w) ||
            ((dstrect->y + dstrect->h) > dst->h)) {
            واپس SDL_سیٹ_Error("Invalid destination blit rectangle");
        }
    } ورنہ {
        بھرا_dst.x = 0;
        بھرا_dst.y = 0;
        بھرا_dst.w = dst->w;
        بھرا_dst.h = dst->h;
        dstrect = &بھرا_dst;
    }

    اگر (dstrect->w <= 0 || dstrect->h <= 0) {
        واپس true;
    }

    اگر (srcrect->w > SDL_MAX_UINT16 || srcrect->h > SDL_MAX_UINT16 ||
        dstrect->w > SDL_MAX_UINT16 || dstrect->h > SDL_MAX_UINT16) {
        واپس SDL_سیٹ_Error("Size too large for scaling");
    }

    // Lock the destination if it's in hardware
    dst_locked = 0;
    اگر (SDL_MUSTLOCK(dst)) {
        اگر (!SDL_تالا_Surface(dst)) {
            واپس SDL_سیٹ_Error("Unable to lock destination surface");
        }
        dst_locked = 1;
    }
    // Lock the source if it's in hardware
    src_locked = 0;
    اگر (SDL_MUSTLOCK(src)) {
        اگر (!SDL_تالا_Surface(src)) {
            اگر (dst_locked) {
                SDL_UnlockSurface(dst);
            }
            واپس SDL_سیٹ_Error("Unable to lock source surface");
        }
        src_locked = 1;
    }

    اگر (scale_منوال == SDL_SCALEMODE_قریب_ترین) {
        نتیجہ = SDL_Stretch_Surface_Unchecked_قریب_ترین(src, srcrect, dst, dstrect);
    } ورنہ {
        نتیجہ = SDL_Stretch_Surface_Unchecked_خطی(src, srcrect, dst, dstrect);
    }

    // We need to unlock the surfaces if they're locked
    اگر (dst_locked) {
        SDL_UnlockSurface(dst);
    }
    اگر (src_locked) {
        SDL_UnlockSurface(src);
    }

    واپس نتیجہ;
}

/* bilinear interpolation precision must be < 8
   Because with SSE: add-multiply: _mm_madd_epi16 works with signed int
   so pixels 0xb1...... are negatives and false the result
   same in NEON probably */
#تعریف_کرو PRECISION 7

#تعریف_کرو FIXED_نقطہ(i) ((Uint32)(i) << 16)
#تعریف_کرو SRC_اشاریہ(fp)  ((Uint32)(fp) >> 16)
#تعریف_کرو INTEGER(fp)    ((Uint32)(fp) >> PRECISION)
#تعریف_کرو FRAC(fp)       ((Uint32)((fp) >> (16 - PRECISION)) & ((1 << PRECISION) - 1))
#تعریف_کرو FRAC_ZERO      0
#تعریف_کرو FRAC_ONE       (1 << PRECISION)
#تعریف_کرو FP_ONE         FIXED_نقطہ(1)

#تعریف_کرو BILINEAR_آغاز                                                              \
    صحیح i;                                                                            \
    Sint64 fp_مجموع_h;                                                                  \
    صحیح fp_قدم_h, بایاں_pad_h, دایاں_pad_h;                                           \
    Sint64 fp_مجموع_w;                                                                  \
    صحیح fp_قدم_w, بایاں_pad_w, دایاں_pad_w;                                           \
    Sint64 fp_مجموع_w_init;                                                             \
    صحیح بایاں_pad_w_init, دایاں_pad_w_init, dst_gap, درمیان_init;                      \
    get_scaler_datas(src_h, dst_h, &fp_مجموع_h, &fp_قدم_h, &بایاں_pad_h, &دایاں_pad_h); \
    get_scaler_datas(src_w, dst_w, &fp_مجموع_w, &fp_قدم_w, &بایاں_pad_w, &دایاں_pad_w); \
    fp_مجموع_w_init = fp_مجموع_w + بایاں_pad_w * fp_قدم_w;                                \
    بایاں_pad_w_init = بایاں_pad_w;                                                     \
    دایاں_pad_w_init = دایاں_pad_w;                                                   \
    dst_gap = dst_pitch - 4 * dst_w;                                                  \
    درمیان_init = dst_w - بایاں_pad_w - دایاں_pad_w;

#تعریف_کرو BILINEAR_اونچائی                                              \
    صحیح اشاریہ_h, frac_h0, frac_h1, درمیان;                             \
    ثابت Uint32 *src_h0, *src_h1;                                     \
    صحیح no_padding;                                                    \
    Uint64 incr_h0, incr_h1;                                           \
                                                                       \
    no_padding = !(i < بایاں_pad_h || i > dst_h - 1 - دایاں_pad_h);     \
    اشاریہ_h = SRC_اشاریہ(fp_مجموع_h);                                     \
    frac_h0 = FRAC(fp_مجموع_h);                                          \
                                                                       \
    اشاریہ_h = no_padding ? اشاریہ_h : (i < بایاں_pad_h ? 0 : src_h - 1); \
    frac_h0 = no_padding ? frac_h0 : 0;                                \
    incr_h1 = no_padding ? src_pitch : 0;                              \
    incr_h0 = (Uint64)اشاریہ_h * src_pitch;                             \
                                                                       \
    src_h0 = (ثابت Uint32 *)((ثابت Uint8 *)src + incr_h0);           \
    src_h1 = (ثابت Uint32 *)((ثابت Uint8 *)src_h0 + incr_h1);        \
                                                                       \
    fp_مجموع_h += fp_قدم_h;                                             \
                                                                       \
    frac_h1 = FRAC_ONE - frac_h0;                                      \
    fp_مجموع_w = fp_مجموع_w_init;                                          \
    دایاں_pad_w = دایاں_pad_w_init;                                    \
    بایاں_pad_w = بایاں_pad_w_init;                                      \
    درمیان = درمیان_init;

#اگر_تعریف_شدہ __clang__
// Remove inlining of this function
// Compiler crash with clang 9.0.8 / android-ndk-r21d
// Compiler crash with clang 11.0.3 / Xcode
// OK with clang 11.0.5 / android-ndk-22
// OK with clang 12.0.0 / Xcode
__attribute__((noinline))
#اگر_ختم
ساکن خالی get_scaler_datas(صحیح src_nb, صحیح dst_nb, Sint64 *fp_آغاز, صحیح *fp_قدم, صحیح *بایاں_pad, صحیح *دایاں_pad)
{

    صحیح قدم = FIXED_نقطہ(src_nb) / (dst_nb); // source step in fixed point
    صحیح x0 = FP_ONE / 2;                       // dst first pixel center at 0.5 in fixed point
    Sint64 fp_مجموع;
    صحیح i;
#اگر 0
    // scale to source coordinates
    x0 *= src_nb;
    x0 /= dst_nb; // x0 == step / 2
#ورنہ
    // Use this code for perfect match with pixman
    Sint64 tmp[2];
    tmp[0] = (Sint64)قدم * (x0 >> 16);
    tmp[1] = (Sint64)قدم * (x0 & 0xFFFF);
    x0 = (صحیح)(tmp[0] + ((tmp[1] + 0x8000) >> 16)); // x0 == (step + 1) / 2
#اگر_ختم
    // -= 0.5, get back the pixel origin, in source coordinates
    x0 -= FP_ONE / 2;

    *fp_آغاز = x0;
    *fp_قدم = قدم;
    *بایاں_pad = 0;
    *دایاں_pad = 0;

    fp_مجموع = x0;
    برائے (i = 0; i < dst_nb; i++) {
        اگر (fp_مجموع < 0) {
            *بایاں_pad += 1;
        } ورنہ {
            صحیح اشاریہ = SRC_اشاریہ(fp_مجموع);
            اگر (اشاریہ > src_nb - 2) {
                *دایاں_pad += 1;
            }
        }
        fp_مجموع += قدم;
    }
    //    SDL_Log("%d -> %d  x0=%d step=%d left_pad=%d right_pad=%d", src_nb, dst_nb, *fp_start, *fp_step, *left_pad, *right_pad);
}

قسمتعریف ساخت color_t
{
    Uint8 a;
    Uint8 b;
    Uint8 c;
    Uint8 d;
} color_t;

/* Interpolated == x0 + frac * (x1 - x0) == x0 * (1 - frac) + x1 * frac */

ساکن SDL_INLINE خالی INTERPOL(ثابت Uint32 *src_x0, ثابت Uint32 *src_x1, صحیح frac0, صحیح frac1, Uint32 *dst)
{
    ثابت color_t *c0 = (ثابت color_t *)src_x0;
    ثابت color_t *c1 = (ثابت color_t *)src_x1;
    color_t *cx = (color_t *)dst;
#اگر 0
    cx->a = c0->a + INTEGER(frac0 * (c1->a - c0->a));
    cx->b = c0->b + INTEGER(frac0 * (c1->b - c0->b));
    cx->c = c0->c + INTEGER(frac0 * (c1->c - c0->c));
    cx->d = c0->d + INTEGER(frac0 * (c1->d - c0->d));
#ورنہ
    cx->a = (Uint8)INTEGER(frac1 * c0->a + frac0 * c1->a);
    cx->b = (Uint8)INTEGER(frac1 * c0->b + frac0 * c1->b);
    cx->c = (Uint8)INTEGER(frac1 * c0->c + frac0 * c1->c);
    cx->d = (Uint8)INTEGER(frac1 * c0->d + frac0 * c1->d);
#اگر_ختم
}

ساکن SDL_INLINE خالی INTERPOL_BILINEAR(ثابت Uint32 *s0, ثابت Uint32 *s1, صحیح frac_w0, صحیح frac_h0, صحیح frac_h1, Uint32 *dst)
{
    Uint32 tmp[2];
    غیرعلامتی صحیح frac_w1 = FRAC_ONE - frac_w0;

    // Vertical first, store to 'tmp'
    INTERPOL(s0, s1, frac_h0, frac_h1, tmp);
    INTERPOL(s0 + 1, s1 + 1, frac_h0, frac_h1, tmp + 1);

    // Horizontal, store to 'dst'
    INTERPOL(tmp, tmp + 1, frac_w0, frac_w1, dst);
}

ساکن bool scale_mat(ثابت Uint32 *src, صحیح src_w, صحیح src_h, صحیح src_pitch, Uint32 *dst, صحیح dst_w, صحیح dst_h, صحیح dst_pitch)
{
    BILINEAR_آغاز

    برائے (i = 0; i < dst_h; i++) {

        BILINEAR_اونچائی

        جب (بایاں_pad_w--) {
            INTERPOL_BILINEAR(src_h0, src_h1, FRAC_ZERO, frac_h0, frac_h1, dst);
            dst += 1;
        }

        جب (درمیان--) {
            ثابت Uint32 *s_00_01;
            ثابت Uint32 *s_10_11;
            صحیح اشاریہ_w = 4 * SRC_اشاریہ(fp_مجموع_w);
            صحیح frac_w = FRAC(fp_مجموع_w);
            fp_مجموع_w += fp_قدم_w;

            /*
                        x00 ... x0_ ..... x01
                        .       .         .
                        .       x         .
                        .       .         .
                        .       .         .
                        x10 ... x1_ ..... x11
            */
            s_00_01 = (ثابت Uint32 *)((ثابت Uint8 *)src_h0 + اشاریہ_w);
            s_10_11 = (ثابت Uint32 *)((ثابت Uint8 *)src_h1 + اشاریہ_w);

            INTERPOL_BILINEAR(s_00_01, s_10_11, frac_w, frac_h0, frac_h1, dst);

            dst += 1;
        }

        جب (دایاں_pad_w--) {
            صحیح اشاریہ_w = 4 * (src_w - 2);
            ثابت Uint32 *s_00_01 = (ثابت Uint32 *)((ثابت Uint8 *)src_h0 + اشاریہ_w);
            ثابت Uint32 *s_10_11 = (ثابت Uint32 *)((ثابت Uint8 *)src_h1 + اشاریہ_w);
            INTERPOL_BILINEAR(s_00_01, s_10_11, FRAC_ONE, frac_h0, frac_h1, dst);
            dst += 1;
        }
        dst = (Uint32 *)((Uint8 *)dst + dst_gap);
    }
    واپس true;
}

#اگر_تعریف_شدہ SDL_SSE2_INTRINSICS

ساکن SDL_INLINE صحیح hasSSE2(خالی)
{
    ساکن صحیح val = -1;
    اگر (val != -1) {
        واپس val;
    }
    val = SDL_HasSSE2();
    واپس val;
}

ساکن SDL_INLINE خالی SDL_TARGETING("sse2") INTERPOL_BILINEAR_SSE(ثابت Uint32 *s0, ثابت Uint32 *s1, صحیح frac_w, __m128i v_frac_h0, __m128i v_frac_h1, Uint32 *dst, __m128i zero)
{
    __m128i x_00_01, x_10_11; /* Pixels in 4*uint8 in row */
    __m128i v_frac_w0, k0, l0, d0, e0;

    صحیح f, f2;
    f = frac_w;
    f2 = FRAC_ONE - frac_w;
    v_frac_w0 = mm_سیٹ_epi16((مختصر)f, (مختصر)f2, (مختصر)f, (مختصر)f2, (مختصر)f, (مختصر)f2, (مختصر)f, (مختصر)f2);

    x_00_01 = _mm_loadl_epi64((ثابت __m128i *)s0); // Load x00 and x01
    x_10_11 = _mm_loadl_epi64((ثابت __m128i *)s1);

    /* Interpolated == x0 + frac * (x1 - x0) == x0 * (1 - frac) + x1 * frac */

    // Interpolation vertical
    k0 = _mm_mullo_epi16(_mm_unpacklo_epi8(x_00_01, zero), v_frac_h1);
    l0 = _mm_mullo_epi16(_mm_unpacklo_epi8(x_10_11, zero), v_frac_h0);
    k0 = mm_جوڑو_epi16(k0, l0);

    // For perfect match, clear the factionnal part eventually.
    /*
    k0 = _mm_srli_epi16(k0, PRECISION);
    k0 = _mm_slli_epi16(k0, PRECISION);
    */

    // Interpolation horizontal
    l0 = _mm_unpacklo_epi64(/*غیر_مستعمل*/ l0, k0);
    k0 = _mm_madd_epi16(_mm_unpackhi_epi16(l0, k0), v_frac_w0);

    // Store 1 pixel
    d0 = _mm_srli_epi32(k0, PRECISION * 2);
    e0 = _mm_packs_epi32(d0, d0);
    e0 = _mm_packus_epi16(e0, e0);
    *dst = _mm_cvtsi128_si32(e0);
}

ساکن bool SDL_TARGETING("sse2") scale_mat_SSE(ثابت Uint32 *src, صحیح src_w, صحیح src_h, صحیح src_pitch, Uint32 *dst, صحیح dst_w, صحیح dst_h, صحیح dst_pitch)
{
    BILINEAR_آغاز

    برائے (i = 0; i < dst_h; i++) {
        صحیح nb_block2;
        __m128i v_frac_h0;
        __m128i v_frac_h1;
        __m128i zero;

        BILINEAR_اونچائی

        nb_block2 = درمیان / 2;

        v_frac_h0 = mm_سیٹ_epi16((مختصر)frac_h0, (مختصر)frac_h0, (مختصر)frac_h0, (مختصر)frac_h0, (مختصر)frac_h0, (مختصر)frac_h0, (مختصر)frac_h0, (مختصر)frac_h0);
        v_frac_h1 = mm_سیٹ_epi16((مختصر)frac_h1, (مختصر)frac_h1, (مختصر)frac_h1, (مختصر)frac_h1, (مختصر)frac_h1, (مختصر)frac_h1, (مختصر)frac_h1, (مختصر)frac_h1);
        zero = _mm_setzero_si128();

        جب (بایاں_pad_w--) {
            INTERPOL_BILINEAR_SSE(src_h0, src_h1, FRAC_ZERO, v_frac_h0, v_frac_h1, dst, zero);
            dst += 1;
        }

        جب (nb_block2--) {
            صحیح اشاریہ_w_0, frac_w_0;
            صحیح اشاریہ_w_1, frac_w_1;

            ثابت Uint32 *s_00_01, *s_02_03, *s_10_11, *s_12_13;

            __m128i x_00_01, x_10_11, x_02_03, x_12_13; /* Pixels in 4*uint8 in row */
            __m128i v_frac_w0, k0, l0, d0, e0;
            __m128i v_frac_w1, k1, l1, d1, e1;

            صحیح f, f2;
            اشاریہ_w_0 = 4 * SRC_اشاریہ(fp_مجموع_w);
            frac_w_0 = FRAC(fp_مجموع_w);
            fp_مجموع_w += fp_قدم_w;
            اشاریہ_w_1 = 4 * SRC_اشاریہ(fp_مجموع_w);
            frac_w_1 = FRAC(fp_مجموع_w);
            fp_مجموع_w += fp_قدم_w;
            /*
                        x00............ x01   x02...........x03
                        .      .         .     .       .     .
                        j0     f0        j1    j2      f1    j3
                        .      .         .     .       .     .
                        .      .         .     .       .     .
                        .      .         .     .       .     .
                        x10............ x11   x12...........x13
             */
            s_00_01 = (ثابت Uint32 *)((ثابت Uint8 *)src_h0 + اشاریہ_w_0);
            s_02_03 = (ثابت Uint32 *)((ثابت Uint8 *)src_h0 + اشاریہ_w_1);
            s_10_11 = (ثابت Uint32 *)((ثابت Uint8 *)src_h1 + اشاریہ_w_0);
            s_12_13 = (ثابت Uint32 *)((ثابت Uint8 *)src_h1 + اشاریہ_w_1);

            f = frac_w_0;
            f2 = FRAC_ONE - frac_w_0;
            v_frac_w0 = mm_سیٹ_epi16((مختصر)f, (مختصر)f2, (مختصر)f, (مختصر)f2, (مختصر)f, (مختصر)f2, (مختصر)f, (مختصر)f2);

            f = frac_w_1;
            f2 = FRAC_ONE - frac_w_1;
            v_frac_w1 = mm_سیٹ_epi16((مختصر)f, (مختصر)f2, (مختصر)f, (مختصر)f2, (مختصر)f, (مختصر)f2, (مختصر)f, (مختصر)f2);

            x_00_01 = _mm_loadl_epi64((ثابت __m128i *)s_00_01); // Load x00 and x01
            x_02_03 = _mm_loadl_epi64((ثابت __m128i *)s_02_03);
            x_10_11 = _mm_loadl_epi64((ثابت __m128i *)s_10_11);
            x_12_13 = _mm_loadl_epi64((ثابت __m128i *)s_12_13);

            // Interpolation vertical
            k0 = _mm_mullo_epi16(_mm_unpacklo_epi8(x_00_01, zero), v_frac_h1);
            l0 = _mm_mullo_epi16(_mm_unpacklo_epi8(x_10_11, zero), v_frac_h0);
            k0 = mm_جوڑو_epi16(k0, l0);
            k1 = _mm_mullo_epi16(_mm_unpacklo_epi8(x_02_03, zero), v_frac_h1);
            l1 = _mm_mullo_epi16(_mm_unpacklo_epi8(x_12_13, zero), v_frac_h0);
            k1 = mm_جوڑو_epi16(k1, l1);

            // Interpolation horizontal
            l0 = _mm_unpacklo_epi64(/*غیر_مستعمل*/ l0, k0);
            k0 = _mm_madd_epi16(_mm_unpackhi_epi16(l0, k0), v_frac_w0);
            l1 = _mm_unpacklo_epi64(/*غیر_مستعمل*/ l1, k1);
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
        اگر (درمیان & 0x1) {
            ثابت Uint32 *s_00_01;
            ثابت Uint32 *s_10_11;
            صحیح اشاریہ_w = 4 * SRC_اشاریہ(fp_مجموع_w);
            صحیح frac_w = FRAC(fp_مجموع_w);
            fp_مجموع_w += fp_قدم_w;
            s_00_01 = (ثابت Uint32 *)((ثابت Uint8 *)src_h0 + اشاریہ_w);
            s_10_11 = (ثابت Uint32 *)((ثابت Uint8 *)src_h1 + اشاریہ_w);
            INTERPOL_BILINEAR_SSE(s_00_01, s_10_11, frac_w, v_frac_h0, v_frac_h1, dst, zero);
            dst += 1;
        }

        جب (دایاں_pad_w--) {
            صحیح اشاریہ_w = 4 * (src_w - 2);
            ثابت Uint32 *s_00_01 = (ثابت Uint32 *)((ثابت Uint8 *)src_h0 + اشاریہ_w);
            ثابت Uint32 *s_10_11 = (ثابت Uint32 *)((ثابت Uint8 *)src_h1 + اشاریہ_w);
            INTERPOL_BILINEAR_SSE(s_00_01, s_10_11, FRAC_ONE, v_frac_h0, v_frac_h1, dst, zero);
            dst += 1;
        }
        dst = (Uint32 *)((Uint8 *)dst + dst_gap);
    }
    واپس true;
}
#اگر_ختم

#اگر_تعریف_شدہ SDL_NEON_INTRINSICS

ساکن SDL_INLINE صحیح hasNEON(خالی)
{
    ساکن صحیح val = -1;
    اگر (val != -1) {
        واپس val;
    }
    val = SDL_HasNEON();
    واپس val;
}

ساکن SDL_INLINE خالی INTERPOL_BILINEAR_NEON(ثابت Uint32 *s0, ثابت Uint32 *s1, صحیح frac_w, uint8x8_t v_frac_h0, uint8x8_t v_frac_h1, Uint32 *dst)
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
    l0 = vshll_n_u16(vget_کم_u16(k0), PRECISION);
    l0 = vmlsl_n_u16(l0, vget_کم_u16(k0), frac_w);
    l0 = vmlal_n_u16(l0, vget_بلند_u16(k0), frac_w);

    // Shift and narrow
    d0 = vcombine_u16(
        /* uint16x4_t */ vshrn_n_u32(l0, 2 * PRECISION),
        /* uint16x4_t */ vshrn_n_u32(l0, 2 * PRECISION));

    // Narrow again
    e0 = vmovn_u16(d0);

    // Store 1 pixel
    *dst = vget_lane_u32(vreinterpret_u32_u8(e0), 0);
}

ساکن bool scale_mat_NEON(ثابت Uint32 *src, صحیح src_w, صحیح src_h, صحیح src_pitch, Uint32 *dst, صحیح dst_w, صحیح dst_h, صحیح dst_pitch)
{
    BILINEAR_آغاز

    برائے (i = 0; i < dst_h; i++) {
        صحیح nb_block4;
        uint8x8_t v_frac_h0, v_frac_h1;

        BILINEAR_اونچائی

        nb_block4 = درمیان / 4;

        v_frac_h0 = vmov_n_u8(frac_h0);
        v_frac_h1 = vmov_n_u8(frac_h1);

        جب (بایاں_pad_w--) {
            INTERPOL_BILINEAR_NEON(src_h0, src_h1, FRAC_ZERO, v_frac_h0, v_frac_h1, dst);
            dst += 1;
        }

        جب (nb_block4--) {
            صحیح اشاریہ_w_0, frac_w_0;
            صحیح اشاریہ_w_1, frac_w_1;
            صحیح اشاریہ_w_2, frac_w_2;
            صحیح اشاریہ_w_3, frac_w_3;

            ثابت Uint32 *s_00_01, *s_02_03, *s_04_05, *s_06_07;
            ثابت Uint32 *s_10_11, *s_12_13, *s_14_15, *s_16_17;

            uint8x8_t x_00_01, x_10_11, x_02_03, x_12_13; /* Pixels in 4*uint8 in row */
            uint8x8_t x_04_05, x_14_15, x_06_07, x_16_17;

            uint16x8_t k0, k1, k2, k3;
            uint32x4_t l0, l1, l2, l3;
            uint16x8_t d0, d1;
            uint8x8_t e0, e1;
            uint32x4_t f0;

            اشاریہ_w_0 = 4 * SRC_اشاریہ(fp_مجموع_w);
            frac_w_0 = FRAC(fp_مجموع_w);
            fp_مجموع_w += fp_قدم_w;
            اشاریہ_w_1 = 4 * SRC_اشاریہ(fp_مجموع_w);
            frac_w_1 = FRAC(fp_مجموع_w);
            fp_مجموع_w += fp_قدم_w;
            اشاریہ_w_2 = 4 * SRC_اشاریہ(fp_مجموع_w);
            frac_w_2 = FRAC(fp_مجموع_w);
            fp_مجموع_w += fp_قدم_w;
            اشاریہ_w_3 = 4 * SRC_اشاریہ(fp_مجموع_w);
            frac_w_3 = FRAC(fp_مجموع_w);
            fp_مجموع_w += fp_قدم_w;

            s_00_01 = (ثابت Uint32 *)((ثابت Uint8 *)src_h0 + اشاریہ_w_0);
            s_02_03 = (ثابت Uint32 *)((ثابت Uint8 *)src_h0 + اشاریہ_w_1);
            s_04_05 = (ثابت Uint32 *)((ثابت Uint8 *)src_h0 + اشاریہ_w_2);
            s_06_07 = (ثابت Uint32 *)((ثابت Uint8 *)src_h0 + اشاریہ_w_3);
            s_10_11 = (ثابت Uint32 *)((ثابت Uint8 *)src_h1 + اشاریہ_w_0);
            s_12_13 = (ثابت Uint32 *)((ثابت Uint8 *)src_h1 + اشاریہ_w_1);
            s_14_15 = (ثابت Uint32 *)((ثابت Uint8 *)src_h1 + اشاریہ_w_2);
            s_16_17 = (ثابت Uint32 *)((ثابت Uint8 *)src_h1 + اشاریہ_w_3);

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

            l0 = vshll_n_u16(vget_کم_u16(k0), PRECISION);
            l0 = vmlsl_n_u16(l0, vget_کم_u16(k0), frac_w_0);
            l0 = vmlal_n_u16(l0, vget_بلند_u16(k0), frac_w_0);

            l1 = vshll_n_u16(vget_کم_u16(k1), PRECISION);
            l1 = vmlsl_n_u16(l1, vget_کم_u16(k1), frac_w_1);
            l1 = vmlal_n_u16(l1, vget_بلند_u16(k1), frac_w_1);

            l2 = vshll_n_u16(vget_کم_u16(k2), PRECISION);
            l2 = vmlsl_n_u16(l2, vget_کم_u16(k2), frac_w_2);
            l2 = vmlal_n_u16(l2, vget_بلند_u16(k2), frac_w_2);

            l3 = vshll_n_u16(vget_کم_u16(k3), PRECISION);
            l3 = vmlsl_n_u16(l3, vget_کم_u16(k3), frac_w_3);
            l3 = vmlal_n_u16(l3, vget_بلند_u16(k3), frac_w_3);

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

        اگر (درمیان & 0x2) {
            صحیح اشاریہ_w_0, frac_w_0;
            صحیح اشاریہ_w_1, frac_w_1;
            ثابت Uint32 *s_00_01, *s_02_03;
            ثابت Uint32 *s_10_11, *s_12_13;
            uint8x8_t x_00_01, x_10_11, x_02_03, x_12_13; /* Pixels in 4*uint8 in row */
            uint16x8_t k0, k1;
            uint32x4_t l0, l1;
            uint16x8_t d0;
            uint8x8_t e0;

            اشاریہ_w_0 = 4 * SRC_اشاریہ(fp_مجموع_w);
            frac_w_0 = FRAC(fp_مجموع_w);
            fp_مجموع_w += fp_قدم_w;
            اشاریہ_w_1 = 4 * SRC_اشاریہ(fp_مجموع_w);
            frac_w_1 = FRAC(fp_مجموع_w);
            fp_مجموع_w += fp_قدم_w;
            /*
                        x00............ x01   x02...........x03
                        .      .         .     .       .     .
                        j0   dest0       j1    j2    dest1   j3
                        .      .         .     .       .     .
                        .      .         .     .       .     .
                        .      .         .     .       .     .
                        x10............ x11   x12...........x13
            */
            s_00_01 = (ثابت Uint32 *)((ثابت Uint8 *)src_h0 + اشاریہ_w_0);
            s_02_03 = (ثابت Uint32 *)((ثابت Uint8 *)src_h0 + اشاریہ_w_1);
            s_10_11 = (ثابت Uint32 *)((ثابت Uint8 *)src_h1 + اشاریہ_w_0);
            s_12_13 = (ثابت Uint32 *)((ثابت Uint8 *)src_h1 + اشاریہ_w_1);

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

            l0 = vshll_n_u16(vget_کم_u16(k0), PRECISION);
            l0 = vmlsl_n_u16(l0, vget_کم_u16(k0), frac_w_0);
            l0 = vmlal_n_u16(l0, vget_بلند_u16(k0), frac_w_0);

            l1 = vshll_n_u16(vget_کم_u16(k1), PRECISION);
            l1 = vmlsl_n_u16(l1, vget_کم_u16(k1), frac_w_1);
            l1 = vmlal_n_u16(l1, vget_بلند_u16(k1), frac_w_1);

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
        اگر (درمیان & 0x1) {
            صحیح اشاریہ_w = 4 * SRC_اشاریہ(fp_مجموع_w);
            صحیح frac_w = FRAC(fp_مجموع_w);
            ثابت Uint32 *s_00_01 = (ثابت Uint32 *)((ثابت Uint8 *)src_h0 + اشاریہ_w);
            ثابت Uint32 *s_10_11 = (ثابت Uint32 *)((ثابت Uint8 *)src_h1 + اشاریہ_w);
            INTERPOL_BILINEAR_NEON(s_00_01, s_10_11, frac_w, v_frac_h0, v_frac_h1, dst);
            dst += 1;
        }

        جب (دایاں_pad_w--) {
            صحیح اشاریہ_w = 4 * (src_w - 2);
            ثابت Uint32 *s_00_01 = (ثابت Uint32 *)((ثابت Uint8 *)src_h0 + اشاریہ_w);
            ثابت Uint32 *s_10_11 = (ثابت Uint32 *)((ثابت Uint8 *)src_h1 + اشاریہ_w);
            INTERPOL_BILINEAR_NEON(s_00_01, s_10_11, FRAC_ONE, v_frac_h0, v_frac_h1, dst);
            dst += 1;
        }

        dst = (Uint32 *)((Uint8 *)dst + dst_gap);
    }
    واپس true;
}
#اگر_ختم

bool SDL_Stretch_Surface_Unchecked_خطی(SDL_Surface *s, ثابت SDL_Rect *srcrect, SDL_Surface *d, ثابت SDL_Rect *dstrect)
{
    bool نتیجہ = false;
    صحیح src_w = srcrect->w;
    صحیح src_h = srcrect->h;
    صحیح dst_w = dstrect->w;
    صحیح dst_h = dstrect->h;
    صحیح src_pitch = s->pitch;
    صحیح dst_pitch = d->pitch;
    Uint32 *src = (Uint32 *)((Uint8 *)s->pixels + srcrect->x * 4 + srcrect->y * src_pitch);
    Uint32 *dst = (Uint32 *)((Uint8 *)d->pixels + dstrect->x * 4 + dstrect->y * dst_pitch);

#اگر_تعریف_شدہ SDL_NEON_INTRINSICS
    اگر (!نتیجہ && hasNEON()) {
        نتیجہ = scale_mat_NEON(src, src_w, src_h, src_pitch, dst, dst_w, dst_h, dst_pitch);
    }
#اگر_ختم

#اگر_تعریف_شدہ SDL_SSE2_INTRINSICS
    اگر (!نتیجہ && hasSSE2()) {
        نتیجہ = scale_mat_SSE(src, src_w, src_h, src_pitch, dst, dst_w, dst_h, dst_pitch);
    }
#اگر_ختم

    اگر (!نتیجہ) {
        نتیجہ = scale_mat(src, src_w, src_h, src_pitch, dst, dst_w, dst_h, dst_pitch);
    }

    واپس نتیجہ;
}

#تعریف_کرو SDL_SCALE_قریب_ترین_آغاز          \
    صحیح i;                                \
    Uint64 posy, incy;                    \
    Uint64 posx, incx;                    \
    Uint64 srcy, srcx;                    \
    صحیح dst_gap, n;                       \
    ثابت Uint32 *src_h0;                 \
    incy = ((Uint64)src_h << 16) / dst_h; \
    incx = ((Uint64)src_w << 16) / dst_w; \
    dst_gap = dst_pitch - bpp * dst_w;    \
    posy = incy / 2;

#تعریف_کرو SDL_SCALE_قریب_ترین_اونچائی                                         \
    srcy = (posy >> 16);                                                  \
    src_h0 = (ثابت Uint32 *)((ثابت Uint8 *)src_ptr + srcy * src_pitch); \
    posy += incy;                                                         \
    posx = incx / 2;                                                      \
    n = dst_w;

ساکن bool scale_mat_قریب_ترین_1(ثابت Uint32 *src_ptr, صحیح src_w, صحیح src_h, صحیح src_pitch, Uint32 *dst, صحیح dst_w, صحیح dst_h, صحیح dst_pitch)
{
    Uint32 bpp = 1;
    SDL_SCALE_قریب_ترین_آغاز
    برائے (i = 0; i < dst_h; i++) {
        SDL_SCALE_قریب_ترین_اونچائی
        جب (n--) {
            ثابت Uint8 *src;
            srcx = bpp * (posx >> 16);
            posx += incx;
            src = (ثابت Uint8 *)src_h0 + srcx;
            *(Uint8 *)dst = *src;
            dst = (Uint32 *)((Uint8 *)dst + bpp);
        }
        dst = (Uint32 *)((Uint8 *)dst + dst_gap);
    }
    واپس true;
}

ساکن bool scale_mat_قریب_ترین_2(ثابت Uint32 *src_ptr, صحیح src_w, صحیح src_h, صحیح src_pitch, Uint32 *dst, صحیح dst_w, صحیح dst_h, صحیح dst_pitch)
{
    Uint32 bpp = 2;
    SDL_SCALE_قریب_ترین_آغاز
    برائے (i = 0; i < dst_h; i++) {
        SDL_SCALE_قریب_ترین_اونچائی
        جب (n--) {
            ثابت Uint16 *src;
            srcx = bpp * (posx >> 16);
            posx += incx;
            src = (ثابت Uint16 *)((ثابت Uint8 *)src_h0 + srcx);
            *(Uint16 *)dst = *src;
            dst = (Uint32 *)((Uint8 *)dst + bpp);
        }
        dst = (Uint32 *)((Uint8 *)dst + dst_gap);
    }
    واپس true;
}

ساکن bool scale_mat_قریب_ترین_3(ثابت Uint32 *src_ptr, صحیح src_w, صحیح src_h, صحیح src_pitch, Uint32 *dst, صحیح dst_w, صحیح dst_h, صحیح dst_pitch)
{
    Uint32 bpp = 3;
    SDL_SCALE_قریب_ترین_آغاز
    برائے (i = 0; i < dst_h; i++) {
        SDL_SCALE_قریب_ترین_اونچائی
        جب (n--) {
            ثابت Uint8 *src;
            srcx = bpp * (posx >> 16);
            posx += incx;
            src = (ثابت Uint8 *)src_h0 + srcx;
            ((Uint8 *)dst)[0] = src[0];
            ((Uint8 *)dst)[1] = src[1];
            ((Uint8 *)dst)[2] = src[2];
            dst = (Uint32 *)((Uint8 *)dst + bpp);
        }
        dst = (Uint32 *)((Uint8 *)dst + dst_gap);
    }
    واپس true;
}

ساکن bool scale_mat_قریب_ترین_4(ثابت Uint32 *src_ptr, صحیح src_w, صحیح src_h, صحیح src_pitch, Uint32 *dst, صحیح dst_w, صحیح dst_h, صحیح dst_pitch)
{
    Uint32 bpp = 4;
    SDL_SCALE_قریب_ترین_آغاز
    برائے (i = 0; i < dst_h; i++) {
        SDL_SCALE_قریب_ترین_اونچائی
        جب (n--) {
            ثابت Uint32 *src;
            srcx = bpp * (posx >> 16);
            posx += incx;
            src = (ثابت Uint32 *)((ثابت Uint8 *)src_h0 + srcx);
            *dst = *src;
            dst = (Uint32 *)((Uint8 *)dst + bpp);
        }
        dst = (Uint32 *)((Uint8 *)dst + dst_gap);
    }
    واپس true;
}

bool SDL_Stretch_Surface_Unchecked_قریب_ترین(SDL_Surface *s, ثابت SDL_Rect *srcrect, SDL_Surface *d, ثابت SDL_Rect *dstrect)
{
    صحیح src_w = srcrect->w;
    صحیح src_h = srcrect->h;
    صحیح dst_w = dstrect->w;
    صحیح dst_h = dstrect->h;
    صحیح src_pitch = s->pitch;
    صحیح dst_pitch = d->pitch;
    صحیح bpp = SDL_BYTESPERPIXEL(d->format);

    Uint32 *src = (Uint32 *)((Uint8 *)s->pixels + srcrect->x * bpp + srcrect->y * src_pitch);
    Uint32 *dst = (Uint32 *)((Uint8 *)d->pixels + dstrect->x * bpp + dstrect->y * dst_pitch);

    اگر (bpp == 4) {
        واپس scale_mat_قریب_ترین_4(src, src_w, src_h, src_pitch, dst, dst_w, dst_h, dst_pitch);
    } ورنہ اگر (bpp == 3) {
        واپس scale_mat_قریب_ترین_3(src, src_w, src_h, src_pitch, dst, dst_w, dst_h, dst_pitch);
    } ورنہ اگر (bpp == 2) {
        واپس scale_mat_قریب_ترین_2(src, src_w, src_h, src_pitch, dst, dst_w, dst_h, dst_pitch);
    } ورنہ {
        واپس scale_mat_قریب_ترین_1(src, src_w, src_h, src_pitch, dst, dst_w, dst_h, dst_pitch);
    }
}
