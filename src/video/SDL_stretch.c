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

स्थिर bool SDL_Stretch_Surface_Unchecked_निकटतमः(SDL_Surface *src, ध्रुव SDL_Rect *srcrect, SDL_Surface *dst, ध्रुव SDL_Rect *dstrect);
स्थिर bool SDL_Stretch_Surface_Unchecked_रैखिकम्(SDL_Surface *src, ध्रुव SDL_Rect *srcrect, SDL_Surface *dst, ध्रुव SDL_Rect *dstrect);

bool SDL_StretchSurface(SDL_Surface *src, ध्रुव SDL_Rect *srcrect, SDL_Surface *dst, ध्रुव SDL_Rect *dstrect, SDL_Scale_बहुलकम् scale_बहुलकम्)
{
    bool परिणाम;
    पूर्णाङ्क src_locked;
    पूर्णाङ्क dst_locked;
    SDL_Rect पूर्णम्_src;
    SDL_Rect पूर्णम्_dst;

    CHECK_PARAM(!src) {
        प्रत्यागम SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!dst) {
        प्रत्यागम SDL_InvalidParamError("dst");
    }

    यदि (src->format != dst->format) {
        // Slow!
        SDL_Surface *src_tmp = SDL_ConvertSurfaceAndColorspace(src, dst->format, dst->palette, dst->colorspace, dst->props);
        यदि (!src_tmp) {
            प्रत्यागम false;
        }
        परिणाम = SDL_StretchSurface(src_tmp, srcrect, dst, dstrect, scale_बहुलकम्);
        SDL_DestroySurface(src_tmp);
        प्रत्यागम परिणाम;
    }

    यदि (SDL_ISPIXELFORMAT_FOURCC(src->format)) {
        // Slow!
        यदि (!dstrect) {
            पूर्णम्_dst.x = 0;
            पूर्णम्_dst.y = 0;
            पूर्णम्_dst.w = dst->w;
            पूर्णम्_dst.h = dst->h;
            dstrect = &पूर्णम्_dst;
        }

        SDL_Surface *src_tmp = SDL_ConvertSurface(src, SDL_PIXELFORMAT_XRGB8888);
        SDL_Surface *dst_tmp = SDL_CreateSurfaceUninitialized(dstrect->w, dstrect->h, SDL_PIXELFORMAT_XRGB8888);
        यदि (src_tmp && dst_tmp) {
            परिणाम = SDL_StretchSurface(src_tmp, srcrect, dst_tmp, रिक्त, scale_बहुलकम्);
            यदि (परिणाम) {
                परिणाम = SDL_ConvertPixelsAndColorspace(dstrect->w, dstrect->h,
                            dst_tmp->format, SDL_COLORSPACE_SRGB, 0,
                            dst_tmp->pixels, dst_tmp->pitch,
                            dst->format, dst->colorspace, SDL_GetSurfaceProperties(dst),
                            (Uint8 *)dst->pixels + dstrect->y * dst->pitch + dstrect->x * SDL_BYTESPERPIXEL(dst->format), dst->pitch);
            }
        } अन्यथा {
            परिणाम = false;
        }
        SDL_DestroySurface(src_tmp);
        SDL_DestroySurface(dst_tmp);
        प्रत्यागम परिणाम;
    }

    विकल्प (scale_बहुलकम्) {
    पक्ष SDL_SCALEMODE_निकटतमः:
        भङ्ग;
    पक्ष SDL_SCALEMODE_रैखिकम्:
        भङ्ग;
    पक्ष SDL_SCALEMODE_PIXELART:
        scale_बहुलकम् = SDL_SCALEMODE_निकटतमः;
        भङ्ग;
    स्वभाव:
        प्रत्यागम SDL_InvalidParamError("scaleMode");
    }

    यदि (scale_बहुलकम् == SDL_SCALEMODE_रैखिकम्) {
        यदि (SDL_BYTESPERPIXEL(src->format) != 4 || src->format == SDL_PIXELFORMAT_ARGB2101010) {
            प्रत्यागम SDL_समुच्चयः_Error("Wrong format");
        }
    }

    // Verify the blit rectangles
    यदि (srcrect) {
        यदि ((srcrect->x < 0) || (srcrect->y < 0) ||
            ((srcrect->x + srcrect->w) > src->w) ||
            ((srcrect->y + srcrect->h) > src->h)) {
            प्रत्यागम SDL_समुच्चयः_Error("Invalid source blit rectangle");
        }
    } अन्यथा {
        पूर्णम्_src.x = 0;
        पूर्णम्_src.y = 0;
        पूर्णम्_src.w = src->w;
        पूर्णम्_src.h = src->h;
        srcrect = &पूर्णम्_src;
    }
    यदि (dstrect) {
        यदि ((dstrect->x < 0) || (dstrect->y < 0) ||
            ((dstrect->x + dstrect->w) > dst->w) ||
            ((dstrect->y + dstrect->h) > dst->h)) {
            प्रत्यागम SDL_समुच्चयः_Error("Invalid destination blit rectangle");
        }
    } अन्यथा {
        पूर्णम्_dst.x = 0;
        पूर्णम्_dst.y = 0;
        पूर्णम्_dst.w = dst->w;
        पूर्णम्_dst.h = dst->h;
        dstrect = &पूर्णम्_dst;
    }

    यदि (dstrect->w <= 0 || dstrect->h <= 0) {
        प्रत्यागम true;
    }

    यदि (srcrect->w > SDL_MAX_UINT16 || srcrect->h > SDL_MAX_UINT16 ||
        dstrect->w > SDL_MAX_UINT16 || dstrect->h > SDL_MAX_UINT16) {
        प्रत्यागम SDL_समुच्चयः_Error("Size too large for scaling");
    }

    // Lock the destination if it's in hardware
    dst_locked = 0;
    यदि (SDL_MUSTLOCK(dst)) {
        यदि (!SDL_तालकम्_Surface(dst)) {
            प्रत्यागम SDL_समुच्चयः_Error("Unable to lock destination surface");
        }
        dst_locked = 1;
    }
    // Lock the source if it's in hardware
    src_locked = 0;
    यदि (SDL_MUSTLOCK(src)) {
        यदि (!SDL_तालकम्_Surface(src)) {
            यदि (dst_locked) {
                SDL_UnlockSurface(dst);
            }
            प्रत्यागम SDL_समुच्चयः_Error("Unable to lock source surface");
        }
        src_locked = 1;
    }

    यदि (scale_बहुलकम् == SDL_SCALEMODE_निकटतमः) {
        परिणाम = SDL_Stretch_Surface_Unchecked_निकटतमः(src, srcrect, dst, dstrect);
    } अन्यथा {
        परिणाम = SDL_Stretch_Surface_Unchecked_रैखिकम्(src, srcrect, dst, dstrect);
    }

    // We need to unlock the surfaces if they're locked
    यदि (dst_locked) {
        SDL_UnlockSurface(dst);
    }
    यदि (src_locked) {
        SDL_UnlockSurface(src);
    }

    प्रत्यागम परिणाम;
}

/* bilinear interpolation precision must be < 8
   Because with SSE: add-multiply: _mm_madd_epi16 works with signed int
   so pixels 0xb1...... are negatives and false the result
   same in NEON probably */
#परिभाषय PRECISION 7

#परिभाषय FIXED_POINT(i) ((Uint32)(i) << 16)
#परिभाषय SRC_सूचकांक(fp)  ((Uint32)(fp) >> 16)
#परिभाषय INTEGER(fp)    ((Uint32)(fp) >> PRECISION)
#परिभाषय FRAC(fp)       ((Uint32)((fp) >> (16 - PRECISION)) & ((1 << PRECISION) - 1))
#परिभाषय FRAC_ZERO      0
#परिभाषय FRAC_ONE       (1 << PRECISION)
#परिभाषय FP_ONE         FIXED_POINT(1)

#परिभाषय BILINEAR___START                                                              \
    पूर्णाङ्क i;                                                                            \
    Sint64 fp_योग_h;                                                                  \
    पूर्णाङ्क fp_चरणः_h, वामः_pad_h, दक्षिणः_pad_h;                                           \
    Sint64 fp_योग_w;                                                                  \
    पूर्णाङ्क fp_चरणः_w, वामः_pad_w, दक्षिणः_pad_w;                                           \
    Sint64 fp_योग_w_init;                                                             \
    पूर्णाङ्क वामः_pad_w_init, दक्षिणः_pad_w_init, dst_gap, मध्यः_init;                      \
    get_scaler_datas(src_h, dst_h, &fp_योग_h, &fp_चरणः_h, &वामः_pad_h, &दक्षिणः_pad_h); \
    get_scaler_datas(src_w, dst_w, &fp_योग_w, &fp_चरणः_w, &वामः_pad_w, &दक्षिणः_pad_w); \
    fp_योग_w_init = fp_योग_w + वामः_pad_w * fp_चरणः_w;                                \
    वामः_pad_w_init = वामः_pad_w;                                                     \
    दक्षिणः_pad_w_init = दक्षिणः_pad_w;                                                   \
    dst_gap = dst_pitch - 4 * dst_w;                                                  \
    मध्यः_init = dst_w - वामः_pad_w - दक्षिणः_pad_w;

#परिभाषय BILINEAR___HEIGHT                                              \
    पूर्णाङ्क सूचकांक_h, frac_h0, frac_h1, मध्यः;                             \
    ध्रुव Uint32 *src_h0, *src_h1;                                     \
    पूर्णाङ्क no_padding;                                                    \
    Uint64 incr_h0, incr_h1;                                           \
                                                                       \
    no_padding = !(i < वामः_pad_h || i > dst_h - 1 - दक्षिणः_pad_h);     \
    सूचकांक_h = SRC_सूचकांक(fp_योग_h);                                     \
    frac_h0 = FRAC(fp_योग_h);                                          \
                                                                       \
    सूचकांक_h = no_padding ? सूचकांक_h : (i < वामः_pad_h ? 0 : src_h - 1); \
    frac_h0 = no_padding ? frac_h0 : 0;                                \
    incr_h1 = no_padding ? src_pitch : 0;                              \
    incr_h0 = (Uint64)सूचकांक_h * src_pitch;                             \
                                                                       \
    src_h0 = (ध्रुव Uint32 *)((ध्रुव Uint8 *)src + incr_h0);           \
    src_h1 = (ध्रुव Uint32 *)((ध्रुव Uint8 *)src_h0 + incr_h1);        \
                                                                       \
    fp_योग_h += fp_चरणः_h;                                             \
                                                                       \
    frac_h1 = FRAC_ONE - frac_h0;                                      \
    fp_योग_w = fp_योग_w_init;                                          \
    दक्षिणः_pad_w = दक्षिणः_pad_w_init;                                    \
    वामः_pad_w = वामः_pad_w_init;                                      \
    मध्यः = मध्यः_init;

#यदि_परिभाषितम् __clang__
// Remove inlining of this function
// Compiler crash with clang 9.0.8 / android-ndk-r21d
// Compiler crash with clang 11.0.3 / Xcode
// OK with clang 11.0.5 / android-ndk-22
// OK with clang 12.0.0 / Xcode
__attribute__((noinline))
#यदि_अन्तः
स्थिर शून्य get_scaler_datas(पूर्णाङ्क src_nb, पूर्णाङ्क dst_nb, Sint64 *fp_start, पूर्णाङ्क *fp_चरणः, पूर्णाङ्क *वामः_pad, पूर्णाङ्क *दक्षिणः_pad)
{

    पूर्णाङ्क चरणः = FIXED_POINT(src_nb) / (dst_nb); // source step in fixed point
    पूर्णाङ्क x0 = FP_ONE / 2;                       // dst first pixel center at 0.5 in fixed point
    Sint64 fp_योग;
    पूर्णाङ्क i;
#यदि 0
    // scale to source coordinates
    x0 *= src_nb;
    x0 /= dst_nb; // x0 == step / 2
#अन्यथा
    // Use this code for perfect match with pixman
    Sint64 tmp[2];
    tmp[0] = (Sint64)चरणः * (x0 >> 16);
    tmp[1] = (Sint64)चरणः * (x0 & 0xFFFF);
    x0 = (पूर्णाङ्क)(tmp[0] + ((tmp[1] + 0x8000) >> 16)); // x0 == (step + 1) / 2
#यदि_अन्तः
    // -= 0.5, get back the pixel origin, in source coordinates
    x0 -= FP_ONE / 2;

    *fp_start = x0;
    *fp_चरणः = चरणः;
    *वामः_pad = 0;
    *दक्षिणः_pad = 0;

    fp_योग = x0;
    प्रति (i = 0; i < dst_nb; i++) {
        यदि (fp_योग < 0) {
            *वामः_pad += 1;
        } अन्यथा {
            पूर्णाङ्क सूचकांक = SRC_सूचकांक(fp_योग);
            यदि (सूचकांक > src_nb - 2) {
                *दक्षिणः_pad += 1;
            }
        }
        fp_योग += चरणः;
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

स्थिर SDL_INLINE शून्य INTERPOL(ध्रुव Uint32 *src_x0, ध्रुव Uint32 *src_x1, पूर्णाङ्क frac0, पूर्णाङ्क frac1, Uint32 *dst)
{
    ध्रुव color_t *c0 = (ध्रुव color_t *)src_x0;
    ध्रुव color_t *c1 = (ध्रुव color_t *)src_x1;
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
#यदि_अन्तः
}

स्थिर SDL_INLINE शून्य INTERPOL_BILINEAR(ध्रुव Uint32 *s0, ध्रुव Uint32 *s1, पूर्णाङ्क frac_w0, पूर्णाङ्क frac_h0, पूर्णाङ्क frac_h1, Uint32 *dst)
{
    Uint32 tmp[2];
    अचिह्नित पूर्णाङ्क frac_w1 = FRAC_ONE - frac_w0;

    // Vertical first, store to 'tmp'
    INTERPOL(s0, s1, frac_h0, frac_h1, tmp);
    INTERPOL(s0 + 1, s1 + 1, frac_h0, frac_h1, tmp + 1);

    // Horizontal, store to 'dst'
    INTERPOL(tmp, tmp + 1, frac_w0, frac_w1, dst);
}

स्थिर bool scale_mat(ध्रुव Uint32 *src, पूर्णाङ्क src_w, पूर्णाङ्क src_h, पूर्णाङ्क src_pitch, Uint32 *dst, पूर्णाङ्क dst_w, पूर्णाङ्क dst_h, पूर्णाङ्क dst_pitch)
{
    BILINEAR___START

    प्रति (i = 0; i < dst_h; i++) {

        BILINEAR___HEIGHT

        यावत् (वामः_pad_w--) {
            INTERPOL_BILINEAR(src_h0, src_h1, FRAC_ZERO, frac_h0, frac_h1, dst);
            dst += 1;
        }

        यावत् (मध्यः--) {
            ध्रुव Uint32 *s_00_01;
            ध्रुव Uint32 *s_10_11;
            पूर्णाङ्क सूचकांक_w = 4 * SRC_सूचकांक(fp_योग_w);
            पूर्णाङ्क frac_w = FRAC(fp_योग_w);
            fp_योग_w += fp_चरणः_w;

            /*
                        x00 ... x0_ ..... x01
                        .       .         .
                        .       x         .
                        .       .         .
                        .       .         .
                        x10 ... x1_ ..... x11
            */
            s_00_01 = (ध्रुव Uint32 *)((ध्रुव Uint8 *)src_h0 + सूचकांक_w);
            s_10_11 = (ध्रुव Uint32 *)((ध्रुव Uint8 *)src_h1 + सूचकांक_w);

            INTERPOL_BILINEAR(s_00_01, s_10_11, frac_w, frac_h0, frac_h1, dst);

            dst += 1;
        }

        यावत् (दक्षिणः_pad_w--) {
            पूर्णाङ्क सूचकांक_w = 4 * (src_w - 2);
            ध्रुव Uint32 *s_00_01 = (ध्रुव Uint32 *)((ध्रुव Uint8 *)src_h0 + सूचकांक_w);
            ध्रुव Uint32 *s_10_11 = (ध्रुव Uint32 *)((ध्रुव Uint8 *)src_h1 + सूचकांक_w);
            INTERPOL_BILINEAR(s_00_01, s_10_11, FRAC_ONE, frac_h0, frac_h1, dst);
            dst += 1;
        }
        dst = (Uint32 *)((Uint8 *)dst + dst_gap);
    }
    प्रत्यागम true;
}

#यदि_परिभाषितम् SDL_SSE2_INTRINSICS

स्थिर SDL_INLINE पूर्णाङ्क hasSSE2(शून्य)
{
    स्थिर पूर्णाङ्क val = -1;
    यदि (val != -1) {
        प्रत्यागम val;
    }
    val = SDL_HasSSE2();
    प्रत्यागम val;
}

स्थिर SDL_INLINE शून्य SDL_TARGETING("sse2") INTERPOL_BILINEAR_SSE(ध्रुव Uint32 *s0, ध्रुव Uint32 *s1, पूर्णाङ्क frac_w, __m128i v_frac_h0, __m128i v_frac_h1, Uint32 *dst, __m128i zero)
{
    __m128i x_00_01, x_10_11; /* Pixels in 4*uint8 in row */
    __m128i v_frac_w0, k0, l0, d0, e0;

    पूर्णाङ्क f, f2;
    f = frac_w;
    f2 = FRAC_ONE - frac_w;
    v_frac_w0 = mm_समुच्चयः_epi16((ह्रस्व)f, (ह्रस्व)f2, (ह्रस्व)f, (ह्रस्व)f2, (ह्रस्व)f, (ह्रस्व)f2, (ह्रस्व)f, (ह्रस्व)f2);

    x_00_01 = _mm_loadl_epi64((ध्रुव __m128i *)s0); // Load x00 and x01
    x_10_11 = _mm_loadl_epi64((ध्रुव __m128i *)s1);

    /* Interpolated == x0 + frac * (x1 - x0) == x0 * (1 - frac) + x1 * frac */

    // Interpolation vertical
    k0 = _mm_mullo_epi16(_mm_unpacklo_epi8(x_00_01, zero), v_frac_h1);
    l0 = _mm_mullo_epi16(_mm_unpacklo_epi8(x_10_11, zero), v_frac_h0);
    k0 = mm_सङ्कलय_epi16(k0, l0);

    // For perfect match, clear the factionnal part eventually.
    /*
    k0 = _mm_srli_epi16(k0, PRECISION);
    k0 = _mm_slli_epi16(k0, PRECISION);
    */

    // Interpolation horizontal
    l0 = _mm_unpacklo_epi64(/*अप्रयुक्तम्*/ l0, k0);
    k0 = _mm_madd_epi16(_mm_unpackhi_epi16(l0, k0), v_frac_w0);

    // Store 1 pixel
    d0 = _mm_srli_epi32(k0, PRECISION * 2);
    e0 = _mm_packs_epi32(d0, d0);
    e0 = _mm_packus_epi16(e0, e0);
    *dst = _mm_cvtsi128_si32(e0);
}

स्थिर bool SDL_TARGETING("sse2") scale_mat_SSE(ध्रुव Uint32 *src, पूर्णाङ्क src_w, पूर्णाङ्क src_h, पूर्णाङ्क src_pitch, Uint32 *dst, पूर्णाङ्क dst_w, पूर्णाङ्क dst_h, पूर्णाङ्क dst_pitch)
{
    BILINEAR___START

    प्रति (i = 0; i < dst_h; i++) {
        पूर्णाङ्क nb_block2;
        __m128i v_frac_h0;
        __m128i v_frac_h1;
        __m128i zero;

        BILINEAR___HEIGHT

        nb_block2 = मध्यः / 2;

        v_frac_h0 = mm_समुच्चयः_epi16((ह्रस्व)frac_h0, (ह्रस्व)frac_h0, (ह्रस्व)frac_h0, (ह्रस्व)frac_h0, (ह्रस्व)frac_h0, (ह्रस्व)frac_h0, (ह्रस्व)frac_h0, (ह्रस्व)frac_h0);
        v_frac_h1 = mm_समुच्चयः_epi16((ह्रस्व)frac_h1, (ह्रस्व)frac_h1, (ह्रस्व)frac_h1, (ह्रस्व)frac_h1, (ह्रस्व)frac_h1, (ह्रस्व)frac_h1, (ह्रस्व)frac_h1, (ह्रस्व)frac_h1);
        zero = _mm_setzero_si128();

        यावत् (वामः_pad_w--) {
            INTERPOL_BILINEAR_SSE(src_h0, src_h1, FRAC_ZERO, v_frac_h0, v_frac_h1, dst, zero);
            dst += 1;
        }

        यावत् (nb_block2--) {
            पूर्णाङ्क सूचकांक_w_0, frac_w_0;
            पूर्णाङ्क सूचकांक_w_1, frac_w_1;

            ध्रुव Uint32 *s_00_01, *s_02_03, *s_10_11, *s_12_13;

            __m128i x_00_01, x_10_11, x_02_03, x_12_13; /* Pixels in 4*uint8 in row */
            __m128i v_frac_w0, k0, l0, d0, e0;
            __m128i v_frac_w1, k1, l1, d1, e1;

            पूर्णाङ्क f, f2;
            सूचकांक_w_0 = 4 * SRC_सूचकांक(fp_योग_w);
            frac_w_0 = FRAC(fp_योग_w);
            fp_योग_w += fp_चरणः_w;
            सूचकांक_w_1 = 4 * SRC_सूचकांक(fp_योग_w);
            frac_w_1 = FRAC(fp_योग_w);
            fp_योग_w += fp_चरणः_w;
            /*
                        x00............ x01   x02...........x03
                        .      .         .     .       .     .
                        j0     f0        j1    j2      f1    j3
                        .      .         .     .       .     .
                        .      .         .     .       .     .
                        .      .         .     .       .     .
                        x10............ x11   x12...........x13
             */
            s_00_01 = (ध्रुव Uint32 *)((ध्रुव Uint8 *)src_h0 + सूचकांक_w_0);
            s_02_03 = (ध्रुव Uint32 *)((ध्रुव Uint8 *)src_h0 + सूचकांक_w_1);
            s_10_11 = (ध्रुव Uint32 *)((ध्रुव Uint8 *)src_h1 + सूचकांक_w_0);
            s_12_13 = (ध्रुव Uint32 *)((ध्रुव Uint8 *)src_h1 + सूचकांक_w_1);

            f = frac_w_0;
            f2 = FRAC_ONE - frac_w_0;
            v_frac_w0 = mm_समुच्चयः_epi16((ह्रस्व)f, (ह्रस्व)f2, (ह्रस्व)f, (ह्रस्व)f2, (ह्रस्व)f, (ह्रस्व)f2, (ह्रस्व)f, (ह्रस्व)f2);

            f = frac_w_1;
            f2 = FRAC_ONE - frac_w_1;
            v_frac_w1 = mm_समुच्चयः_epi16((ह्रस्व)f, (ह्रस्व)f2, (ह्रस्व)f, (ह्रस्व)f2, (ह्रस्व)f, (ह्रस्व)f2, (ह्रस्व)f, (ह्रस्व)f2);

            x_00_01 = _mm_loadl_epi64((ध्रुव __m128i *)s_00_01); // Load x00 and x01
            x_02_03 = _mm_loadl_epi64((ध्रुव __m128i *)s_02_03);
            x_10_11 = _mm_loadl_epi64((ध्रुव __m128i *)s_10_11);
            x_12_13 = _mm_loadl_epi64((ध्रुव __m128i *)s_12_13);

            // Interpolation vertical
            k0 = _mm_mullo_epi16(_mm_unpacklo_epi8(x_00_01, zero), v_frac_h1);
            l0 = _mm_mullo_epi16(_mm_unpacklo_epi8(x_10_11, zero), v_frac_h0);
            k0 = mm_सङ्कलय_epi16(k0, l0);
            k1 = _mm_mullo_epi16(_mm_unpacklo_epi8(x_02_03, zero), v_frac_h1);
            l1 = _mm_mullo_epi16(_mm_unpacklo_epi8(x_12_13, zero), v_frac_h0);
            k1 = mm_सङ्कलय_epi16(k1, l1);

            // Interpolation horizontal
            l0 = _mm_unpacklo_epi64(/*अप्रयुक्तम्*/ l0, k0);
            k0 = _mm_madd_epi16(_mm_unpackhi_epi16(l0, k0), v_frac_w0);
            l1 = _mm_unpacklo_epi64(/*अप्रयुक्तम्*/ l1, k1);
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
        यदि (मध्यः & 0x1) {
            ध्रुव Uint32 *s_00_01;
            ध्रुव Uint32 *s_10_11;
            पूर्णाङ्क सूचकांक_w = 4 * SRC_सूचकांक(fp_योग_w);
            पूर्णाङ्क frac_w = FRAC(fp_योग_w);
            fp_योग_w += fp_चरणः_w;
            s_00_01 = (ध्रुव Uint32 *)((ध्रुव Uint8 *)src_h0 + सूचकांक_w);
            s_10_11 = (ध्रुव Uint32 *)((ध्रुव Uint8 *)src_h1 + सूचकांक_w);
            INTERPOL_BILINEAR_SSE(s_00_01, s_10_11, frac_w, v_frac_h0, v_frac_h1, dst, zero);
            dst += 1;
        }

        यावत् (दक्षिणः_pad_w--) {
            पूर्णाङ्क सूचकांक_w = 4 * (src_w - 2);
            ध्रुव Uint32 *s_00_01 = (ध्रुव Uint32 *)((ध्रुव Uint8 *)src_h0 + सूचकांक_w);
            ध्रुव Uint32 *s_10_11 = (ध्रुव Uint32 *)((ध्रुव Uint8 *)src_h1 + सूचकांक_w);
            INTERPOL_BILINEAR_SSE(s_00_01, s_10_11, FRAC_ONE, v_frac_h0, v_frac_h1, dst, zero);
            dst += 1;
        }
        dst = (Uint32 *)((Uint8 *)dst + dst_gap);
    }
    प्रत्यागम true;
}
#यदि_अन्तः

#यदि_परिभाषितम् SDL_NEON_INTRINSICS

स्थिर SDL_INLINE पूर्णाङ्क hasNEON(शून्य)
{
    स्थिर पूर्णाङ्क val = -1;
    यदि (val != -1) {
        प्रत्यागम val;
    }
    val = SDL_HasNEON();
    प्रत्यागम val;
}

स्थिर SDL_INLINE शून्य INTERPOL_BILINEAR_NEON(ध्रुव Uint32 *s0, ध्रुव Uint32 *s1, पूर्णाङ्क frac_w, uint8x8_t v_frac_h0, uint8x8_t v_frac_h1, Uint32 *dst)
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
    l0 = vshll_n_u16(vget_नीचः_u16(k0), PRECISION);
    l0 = vmlsl_n_u16(l0, vget_नीचः_u16(k0), frac_w);
    l0 = vmlal_n_u16(l0, vget_उच्चः_u16(k0), frac_w);

    // Shift and narrow
    d0 = vcombine_u16(
        /* uint16x4_t */ vshrn_n_u32(l0, 2 * PRECISION),
        /* uint16x4_t */ vshrn_n_u32(l0, 2 * PRECISION));

    // Narrow again
    e0 = vmovn_u16(d0);

    // Store 1 pixel
    *dst = vget_lane_u32(vreinterpret_u32_u8(e0), 0);
}

स्थिर bool scale_mat_NEON(ध्रुव Uint32 *src, पूर्णाङ्क src_w, पूर्णाङ्क src_h, पूर्णाङ्क src_pitch, Uint32 *dst, पूर्णाङ्क dst_w, पूर्णाङ्क dst_h, पूर्णाङ्क dst_pitch)
{
    BILINEAR___START

    प्रति (i = 0; i < dst_h; i++) {
        पूर्णाङ्क nb_block4;
        uint8x8_t v_frac_h0, v_frac_h1;

        BILINEAR___HEIGHT

        nb_block4 = मध्यः / 4;

        v_frac_h0 = vmov_n_u8(frac_h0);
        v_frac_h1 = vmov_n_u8(frac_h1);

        यावत् (वामः_pad_w--) {
            INTERPOL_BILINEAR_NEON(src_h0, src_h1, FRAC_ZERO, v_frac_h0, v_frac_h1, dst);
            dst += 1;
        }

        यावत् (nb_block4--) {
            पूर्णाङ्क सूचकांक_w_0, frac_w_0;
            पूर्णाङ्क सूचकांक_w_1, frac_w_1;
            पूर्णाङ्क सूचकांक_w_2, frac_w_2;
            पूर्णाङ्क सूचकांक_w_3, frac_w_3;

            ध्रुव Uint32 *s_00_01, *s_02_03, *s_04_05, *s_06_07;
            ध्रुव Uint32 *s_10_11, *s_12_13, *s_14_15, *s_16_17;

            uint8x8_t x_00_01, x_10_11, x_02_03, x_12_13; /* Pixels in 4*uint8 in row */
            uint8x8_t x_04_05, x_14_15, x_06_07, x_16_17;

            uint16x8_t k0, k1, k2, k3;
            uint32x4_t l0, l1, l2, l3;
            uint16x8_t d0, d1;
            uint8x8_t e0, e1;
            uint32x4_t f0;

            सूचकांक_w_0 = 4 * SRC_सूचकांक(fp_योग_w);
            frac_w_0 = FRAC(fp_योग_w);
            fp_योग_w += fp_चरणः_w;
            सूचकांक_w_1 = 4 * SRC_सूचकांक(fp_योग_w);
            frac_w_1 = FRAC(fp_योग_w);
            fp_योग_w += fp_चरणः_w;
            सूचकांक_w_2 = 4 * SRC_सूचकांक(fp_योग_w);
            frac_w_2 = FRAC(fp_योग_w);
            fp_योग_w += fp_चरणः_w;
            सूचकांक_w_3 = 4 * SRC_सूचकांक(fp_योग_w);
            frac_w_3 = FRAC(fp_योग_w);
            fp_योग_w += fp_चरणः_w;

            s_00_01 = (ध्रुव Uint32 *)((ध्रुव Uint8 *)src_h0 + सूचकांक_w_0);
            s_02_03 = (ध्रुव Uint32 *)((ध्रुव Uint8 *)src_h0 + सूचकांक_w_1);
            s_04_05 = (ध्रुव Uint32 *)((ध्रुव Uint8 *)src_h0 + सूचकांक_w_2);
            s_06_07 = (ध्रुव Uint32 *)((ध्रुव Uint8 *)src_h0 + सूचकांक_w_3);
            s_10_11 = (ध्रुव Uint32 *)((ध्रुव Uint8 *)src_h1 + सूचकांक_w_0);
            s_12_13 = (ध्रुव Uint32 *)((ध्रुव Uint8 *)src_h1 + सूचकांक_w_1);
            s_14_15 = (ध्रुव Uint32 *)((ध्रुव Uint8 *)src_h1 + सूचकांक_w_2);
            s_16_17 = (ध्रुव Uint32 *)((ध्रुव Uint8 *)src_h1 + सूचकांक_w_3);

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

            l0 = vshll_n_u16(vget_नीचः_u16(k0), PRECISION);
            l0 = vmlsl_n_u16(l0, vget_नीचः_u16(k0), frac_w_0);
            l0 = vmlal_n_u16(l0, vget_उच्चः_u16(k0), frac_w_0);

            l1 = vshll_n_u16(vget_नीचः_u16(k1), PRECISION);
            l1 = vmlsl_n_u16(l1, vget_नीचः_u16(k1), frac_w_1);
            l1 = vmlal_n_u16(l1, vget_उच्चः_u16(k1), frac_w_1);

            l2 = vshll_n_u16(vget_नीचः_u16(k2), PRECISION);
            l2 = vmlsl_n_u16(l2, vget_नीचः_u16(k2), frac_w_2);
            l2 = vmlal_n_u16(l2, vget_उच्चः_u16(k2), frac_w_2);

            l3 = vshll_n_u16(vget_नीचः_u16(k3), PRECISION);
            l3 = vmlsl_n_u16(l3, vget_नीचः_u16(k3), frac_w_3);
            l3 = vmlal_n_u16(l3, vget_उच्चः_u16(k3), frac_w_3);

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

        यदि (मध्यः & 0x2) {
            पूर्णाङ्क सूचकांक_w_0, frac_w_0;
            पूर्णाङ्क सूचकांक_w_1, frac_w_1;
            ध्रुव Uint32 *s_00_01, *s_02_03;
            ध्रुव Uint32 *s_10_11, *s_12_13;
            uint8x8_t x_00_01, x_10_11, x_02_03, x_12_13; /* Pixels in 4*uint8 in row */
            uint16x8_t k0, k1;
            uint32x4_t l0, l1;
            uint16x8_t d0;
            uint8x8_t e0;

            सूचकांक_w_0 = 4 * SRC_सूचकांक(fp_योग_w);
            frac_w_0 = FRAC(fp_योग_w);
            fp_योग_w += fp_चरणः_w;
            सूचकांक_w_1 = 4 * SRC_सूचकांक(fp_योग_w);
            frac_w_1 = FRAC(fp_योग_w);
            fp_योग_w += fp_चरणः_w;
            /*
                        x00............ x01   x02...........x03
                        .      .         .     .       .     .
                        j0   dest0       j1    j2    dest1   j3
                        .      .         .     .       .     .
                        .      .         .     .       .     .
                        .      .         .     .       .     .
                        x10............ x11   x12...........x13
            */
            s_00_01 = (ध्रुव Uint32 *)((ध्रुव Uint8 *)src_h0 + सूचकांक_w_0);
            s_02_03 = (ध्रुव Uint32 *)((ध्रुव Uint8 *)src_h0 + सूचकांक_w_1);
            s_10_11 = (ध्रुव Uint32 *)((ध्रुव Uint8 *)src_h1 + सूचकांक_w_0);
            s_12_13 = (ध्रुव Uint32 *)((ध्रुव Uint8 *)src_h1 + सूचकांक_w_1);

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

            l0 = vshll_n_u16(vget_नीचः_u16(k0), PRECISION);
            l0 = vmlsl_n_u16(l0, vget_नीचः_u16(k0), frac_w_0);
            l0 = vmlal_n_u16(l0, vget_उच्चः_u16(k0), frac_w_0);

            l1 = vshll_n_u16(vget_नीचः_u16(k1), PRECISION);
            l1 = vmlsl_n_u16(l1, vget_नीचः_u16(k1), frac_w_1);
            l1 = vmlal_n_u16(l1, vget_उच्चः_u16(k1), frac_w_1);

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
        यदि (मध्यः & 0x1) {
            पूर्णाङ्क सूचकांक_w = 4 * SRC_सूचकांक(fp_योग_w);
            पूर्णाङ्क frac_w = FRAC(fp_योग_w);
            ध्रुव Uint32 *s_00_01 = (ध्रुव Uint32 *)((ध्रुव Uint8 *)src_h0 + सूचकांक_w);
            ध्रुव Uint32 *s_10_11 = (ध्रुव Uint32 *)((ध्रुव Uint8 *)src_h1 + सूचकांक_w);
            INTERPOL_BILINEAR_NEON(s_00_01, s_10_11, frac_w, v_frac_h0, v_frac_h1, dst);
            dst += 1;
        }

        यावत् (दक्षिणः_pad_w--) {
            पूर्णाङ्क सूचकांक_w = 4 * (src_w - 2);
            ध्रुव Uint32 *s_00_01 = (ध्रुव Uint32 *)((ध्रुव Uint8 *)src_h0 + सूचकांक_w);
            ध्रुव Uint32 *s_10_11 = (ध्रुव Uint32 *)((ध्रुव Uint8 *)src_h1 + सूचकांक_w);
            INTERPOL_BILINEAR_NEON(s_00_01, s_10_11, FRAC_ONE, v_frac_h0, v_frac_h1, dst);
            dst += 1;
        }

        dst = (Uint32 *)((Uint8 *)dst + dst_gap);
    }
    प्रत्यागम true;
}
#यदि_अन्तः

bool SDL_Stretch_Surface_Unchecked_रैखिकम्(SDL_Surface *s, ध्रुव SDL_Rect *srcrect, SDL_Surface *d, ध्रुव SDL_Rect *dstrect)
{
    bool परिणाम = false;
    पूर्णाङ्क src_w = srcrect->w;
    पूर्णाङ्क src_h = srcrect->h;
    पूर्णाङ्क dst_w = dstrect->w;
    पूर्णाङ्क dst_h = dstrect->h;
    पूर्णाङ्क src_pitch = s->pitch;
    पूर्णाङ्क dst_pitch = d->pitch;
    Uint32 *src = (Uint32 *)((Uint8 *)s->pixels + srcrect->x * 4 + srcrect->y * src_pitch);
    Uint32 *dst = (Uint32 *)((Uint8 *)d->pixels + dstrect->x * 4 + dstrect->y * dst_pitch);

#यदि_परिभाषितम् SDL_NEON_INTRINSICS
    यदि (!परिणाम && hasNEON()) {
        परिणाम = scale_mat_NEON(src, src_w, src_h, src_pitch, dst, dst_w, dst_h, dst_pitch);
    }
#यदि_अन्तः

#यदि_परिभाषितम् SDL_SSE2_INTRINSICS
    यदि (!परिणाम && hasSSE2()) {
        परिणाम = scale_mat_SSE(src, src_w, src_h, src_pitch, dst, dst_w, dst_h, dst_pitch);
    }
#यदि_अन्तः

    यदि (!परिणाम) {
        परिणाम = scale_mat(src, src_w, src_h, src_pitch, dst, dst_w, dst_h, dst_pitch);
    }

    प्रत्यागम परिणाम;
}

#परिभाषय SDL_SCALE_निकटतमः_START          \
    पूर्णाङ्क i;                                \
    Uint64 posy, incy;                    \
    Uint64 posx, incx;                    \
    Uint64 srcy, srcx;                    \
    पूर्णाङ्क dst_gap, n;                       \
    ध्रुव Uint32 *src_h0;                 \
    incy = ((Uint64)src_h << 16) / dst_h; \
    incx = ((Uint64)src_w << 16) / dst_w; \
    dst_gap = dst_pitch - bpp * dst_w;    \
    posy = incy / 2;

#परिभाषय SDL_SCALE_निकटतमः_HEIGHT                                         \
    srcy = (posy >> 16);                                                  \
    src_h0 = (ध्रुव Uint32 *)((ध्रुव Uint8 *)src_ptr + srcy * src_pitch); \
    posy += incy;                                                         \
    posx = incx / 2;                                                      \
    n = dst_w;

स्थिर bool scale_mat_निकटतमः_1(ध्रुव Uint32 *src_ptr, पूर्णाङ्क src_w, पूर्णाङ्क src_h, पूर्णाङ्क src_pitch, Uint32 *dst, पूर्णाङ्क dst_w, पूर्णाङ्क dst_h, पूर्णाङ्क dst_pitch)
{
    Uint32 bpp = 1;
    SDL_SCALE_निकटतमः_START
    प्रति (i = 0; i < dst_h; i++) {
        SDL_SCALE_निकटतमः_HEIGHT
        यावत् (n--) {
            ध्रुव Uint8 *src;
            srcx = bpp * (posx >> 16);
            posx += incx;
            src = (ध्रुव Uint8 *)src_h0 + srcx;
            *(Uint8 *)dst = *src;
            dst = (Uint32 *)((Uint8 *)dst + bpp);
        }
        dst = (Uint32 *)((Uint8 *)dst + dst_gap);
    }
    प्रत्यागम true;
}

स्थिर bool scale_mat_निकटतमः_2(ध्रुव Uint32 *src_ptr, पूर्णाङ्क src_w, पूर्णाङ्क src_h, पूर्णाङ्क src_pitch, Uint32 *dst, पूर्णाङ्क dst_w, पूर्णाङ्क dst_h, पूर्णाङ्क dst_pitch)
{
    Uint32 bpp = 2;
    SDL_SCALE_निकटतमः_START
    प्रति (i = 0; i < dst_h; i++) {
        SDL_SCALE_निकटतमः_HEIGHT
        यावत् (n--) {
            ध्रुव Uint16 *src;
            srcx = bpp * (posx >> 16);
            posx += incx;
            src = (ध्रुव Uint16 *)((ध्रुव Uint8 *)src_h0 + srcx);
            *(Uint16 *)dst = *src;
            dst = (Uint32 *)((Uint8 *)dst + bpp);
        }
        dst = (Uint32 *)((Uint8 *)dst + dst_gap);
    }
    प्रत्यागम true;
}

स्थिर bool scale_mat_निकटतमः_3(ध्रुव Uint32 *src_ptr, पूर्णाङ्क src_w, पूर्णाङ्क src_h, पूर्णाङ्क src_pitch, Uint32 *dst, पूर्णाङ्क dst_w, पूर्णाङ्क dst_h, पूर्णाङ्क dst_pitch)
{
    Uint32 bpp = 3;
    SDL_SCALE_निकटतमः_START
    प्रति (i = 0; i < dst_h; i++) {
        SDL_SCALE_निकटतमः_HEIGHT
        यावत् (n--) {
            ध्रुव Uint8 *src;
            srcx = bpp * (posx >> 16);
            posx += incx;
            src = (ध्रुव Uint8 *)src_h0 + srcx;
            ((Uint8 *)dst)[0] = src[0];
            ((Uint8 *)dst)[1] = src[1];
            ((Uint8 *)dst)[2] = src[2];
            dst = (Uint32 *)((Uint8 *)dst + bpp);
        }
        dst = (Uint32 *)((Uint8 *)dst + dst_gap);
    }
    प्रत्यागम true;
}

स्थिर bool scale_mat_निकटतमः_4(ध्रुव Uint32 *src_ptr, पूर्णाङ्क src_w, पूर्णाङ्क src_h, पूर्णाङ्क src_pitch, Uint32 *dst, पूर्णाङ्क dst_w, पूर्णाङ्क dst_h, पूर्णाङ्क dst_pitch)
{
    Uint32 bpp = 4;
    SDL_SCALE_निकटतमः_START
    प्रति (i = 0; i < dst_h; i++) {
        SDL_SCALE_निकटतमः_HEIGHT
        यावत् (n--) {
            ध्रुव Uint32 *src;
            srcx = bpp * (posx >> 16);
            posx += incx;
            src = (ध्रुव Uint32 *)((ध्रुव Uint8 *)src_h0 + srcx);
            *dst = *src;
            dst = (Uint32 *)((Uint8 *)dst + bpp);
        }
        dst = (Uint32 *)((Uint8 *)dst + dst_gap);
    }
    प्रत्यागम true;
}

bool SDL_Stretch_Surface_Unchecked_निकटतमः(SDL_Surface *s, ध्रुव SDL_Rect *srcrect, SDL_Surface *d, ध्रुव SDL_Rect *dstrect)
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
        प्रत्यागम scale_mat_निकटतमः_4(src, src_w, src_h, src_pitch, dst, dst_w, dst_h, dst_pitch);
    } अन्यथा यदि (bpp == 3) {
        प्रत्यागम scale_mat_निकटतमः_3(src, src_w, src_h, src_pitch, dst, dst_w, dst_h, dst_pitch);
    } अन्यथा यदि (bpp == 2) {
        प्रत्यागम scale_mat_निकटतमः_2(src, src_w, src_h, src_pitch, dst, dst_w, dst_h, dst_pitch);
    } अन्यथा {
        प्रत्यागम scale_mat_निकटतमः_1(src, src_w, src_h, src_pitch, dst, dst_w, dst_h, dst_pitch);
    }
}
