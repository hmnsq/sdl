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

ಸ್ಥಿರ bool SDL_Stretch_Surface_Unchecked_ಹತ್ತಿರದ(SDL_Surface *src, ಸ್ಥಿರಾಂಕ SDL_Rect *srcrect, SDL_Surface *dst, ಸ್ಥಿರಾಂಕ SDL_Rect *dstrect);
ಸ್ಥಿರ bool SDL_Stretch_Surface_Unchecked_ರೇಖೀಯ(SDL_Surface *src, ಸ್ಥಿರಾಂಕ SDL_Rect *srcrect, SDL_Surface *dst, ಸ್ಥಿರಾಂಕ SDL_Rect *dstrect);

bool SDL_StretchSurface(SDL_Surface *src, ಸ್ಥಿರಾಂಕ SDL_Rect *srcrect, SDL_Surface *dst, ಸ್ಥಿರಾಂಕ SDL_Rect *dstrect, SDL_Scale_ಬಹುಲಕ scale_ಬಹುಲಕ)
{
    bool ಫಲಿತಾಂಶ;
    ಪೂರ್ಣಾಂಕ src_locked;
    ಪೂರ್ಣಾಂಕ dst_locked;
    SDL_Rect ತುಂಬಿದ_src;
    SDL_Rect ತುಂಬಿದ_dst;

    CHECK_PARAM(!src) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!dst) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("dst");
    }

    ಆದರೆ (src->format != dst->format) {
        // Slow!
        SDL_Surface *src_tmp = SDL_ConvertSurfaceAndColorspace(src, dst->format, dst->palette, dst->colorspace, dst->props);
        ಆದರೆ (!src_tmp) {
            ಹಿಂತಿರುಗಿ false;
        }
        ಫಲಿತಾಂಶ = SDL_StretchSurface(src_tmp, srcrect, dst, dstrect, scale_ಬಹುಲಕ);
        SDL_DestroySurface(src_tmp);
        ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
    }

    ಆದರೆ (SDL_ISPIXELFORMAT_FOURCC(src->format)) {
        // Slow!
        ಆದರೆ (!dstrect) {
            ತುಂಬಿದ_dst.x = 0;
            ತುಂಬಿದ_dst.y = 0;
            ತುಂಬಿದ_dst.w = dst->w;
            ತುಂಬಿದ_dst.h = dst->h;
            dstrect = &ತುಂಬಿದ_dst;
        }

        SDL_Surface *src_tmp = SDL_ConvertSurface(src, SDL_PIXELFORMAT_XRGB8888);
        SDL_Surface *dst_tmp = SDL_CreateSurfaceUninitialized(dstrect->w, dstrect->h, SDL_PIXELFORMAT_XRGB8888);
        ಆದರೆ (src_tmp && dst_tmp) {
            ಫಲಿತಾಂಶ = SDL_StretchSurface(src_tmp, srcrect, dst_tmp, ಖಾಲಿ, scale_ಬಹುಲಕ);
            ಆದರೆ (ಫಲಿತಾಂಶ) {
                ಫಲಿತಾಂಶ = SDL_ConvertPixelsAndColorspace(dstrect->w, dstrect->h,
                            dst_tmp->format, SDL_COLORSPACE_SRGB, 0,
                            dst_tmp->pixels, dst_tmp->pitch,
                            dst->format, dst->colorspace, SDL_GetSurfaceProperties(dst),
                            (Uint8 *)dst->pixels + dstrect->y * dst->pitch + dstrect->x * SDL_BYTESPERPIXEL(dst->format), dst->pitch);
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಫಲಿತಾಂಶ = false;
        }
        SDL_DestroySurface(src_tmp);
        SDL_DestroySurface(dst_tmp);
        ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
    }

    ಆಯ್ಕೆ (scale_ಬಹುಲಕ) {
    ಸ್ಥಿತಿ SDL_SCALEMODE_ಹತ್ತಿರದ:
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SCALEMODE_ರೇಖೀಯ:
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SCALEMODE_PIXELART:
        scale_ಬಹುಲಕ = SDL_SCALEMODE_ಹತ್ತಿರದ;
        ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("scaleMode");
    }

    ಆದರೆ (scale_ಬಹುಲಕ == SDL_SCALEMODE_ರೇಖೀಯ) {
        ಆದರೆ (SDL_BYTESPERPIXEL(src->format) != 4 || src->format == SDL_PIXELFORMAT_ARGB2101010) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Wrong format");
        }
    }

    // Verify the blit rectangles
    ಆದರೆ (srcrect) {
        ಆದರೆ ((srcrect->x < 0) || (srcrect->y < 0) ||
            ((srcrect->x + srcrect->w) > src->w) ||
            ((srcrect->y + srcrect->h) > src->h)) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Invalid source blit rectangle");
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ತುಂಬಿದ_src.x = 0;
        ತುಂಬಿದ_src.y = 0;
        ತುಂಬಿದ_src.w = src->w;
        ತುಂಬಿದ_src.h = src->h;
        srcrect = &ತುಂಬಿದ_src;
    }
    ಆದರೆ (dstrect) {
        ಆದರೆ ((dstrect->x < 0) || (dstrect->y < 0) ||
            ((dstrect->x + dstrect->w) > dst->w) ||
            ((dstrect->y + dstrect->h) > dst->h)) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Invalid destination blit rectangle");
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ತುಂಬಿದ_dst.x = 0;
        ತುಂಬಿದ_dst.y = 0;
        ತುಂಬಿದ_dst.w = dst->w;
        ತುಂಬಿದ_dst.h = dst->h;
        dstrect = &ತುಂಬಿದ_dst;
    }

    ಆದರೆ (dstrect->w <= 0 || dstrect->h <= 0) {
        ಹಿಂತಿರುಗಿ true;
    }

    ಆದರೆ (srcrect->w > SDL_MAX_UINT16 || srcrect->h > SDL_MAX_UINT16 ||
        dstrect->w > SDL_MAX_UINT16 || dstrect->h > SDL_MAX_UINT16) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Size too large for scaling");
    }

    // Lock the destination if it's in hardware
    dst_locked = 0;
    ಆದರೆ (SDL_MUSTLOCK(dst)) {
        ಆದರೆ (!SDL_ಬೀಗ_Surface(dst)) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Unable to lock destination surface");
        }
        dst_locked = 1;
    }
    // Lock the source if it's in hardware
    src_locked = 0;
    ಆದರೆ (SDL_MUSTLOCK(src)) {
        ಆದರೆ (!SDL_ಬೀಗ_Surface(src)) {
            ಆದರೆ (dst_locked) {
                SDL_UnlockSurface(dst);
            }
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Unable to lock source surface");
        }
        src_locked = 1;
    }

    ಆದರೆ (scale_ಬಹುಲಕ == SDL_SCALEMODE_ಹತ್ತಿರದ) {
        ಫಲಿತಾಂಶ = SDL_Stretch_Surface_Unchecked_ಹತ್ತಿರದ(src, srcrect, dst, dstrect);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಫಲಿತಾಂಶ = SDL_Stretch_Surface_Unchecked_ರೇಖೀಯ(src, srcrect, dst, dstrect);
    }

    // We need to unlock the surfaces if they're locked
    ಆದರೆ (dst_locked) {
        SDL_UnlockSurface(dst);
    }
    ಆದರೆ (src_locked) {
        SDL_UnlockSurface(src);
    }

    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

/* bilinear interpolation precision must be < 8
   Because with SSE: add-multiply: _mm_madd_epi16 works with signed int
   so pixels 0xb1...... are negatives and false the result
   same in NEON probably */
#ವ್ಯಾಖ್ಯಾನಿಸು PRECISION 7

#ವ್ಯಾಖ್ಯಾನಿಸು FIXED_ಬಿಂದು(i) ((Uint32)(i) << 16)
#ವ್ಯಾಖ್ಯಾನಿಸು SRC_ಸೂಚ್ಯಂಕ(fp)  ((Uint32)(fp) >> 16)
#ವ್ಯಾಖ್ಯಾನಿಸು INTEGER(fp)    ((Uint32)(fp) >> PRECISION)
#ವ್ಯಾಖ್ಯಾನಿಸು FRAC(fp)       ((Uint32)((fp) >> (16 - PRECISION)) & ((1 << PRECISION) - 1))
#ವ್ಯಾಖ್ಯಾನಿಸು FRAC_ZERO      0
#ವ್ಯಾಖ್ಯಾನಿಸು FRAC_ONE       (1 << PRECISION)
#ವ್ಯಾಖ್ಯಾನಿಸು FP_ONE         FIXED_ಬಿಂದು(1)

#ವ್ಯಾಖ್ಯಾನಿಸು BILINEAR_ಆರಂಭ                                                              \
    ಪೂರ್ಣಾಂಕ i;                                                                            \
    Sint64 fp_ಮೊತ್ತ_h;                                                                  \
    ಪೂರ್ಣಾಂಕ fp_ಹೆಜ್ಜೆ_h, ಎಡ_pad_h, ಬಲ_pad_h;                                           \
    Sint64 fp_ಮೊತ್ತ_w;                                                                  \
    ಪೂರ್ಣಾಂಕ fp_ಹೆಜ್ಜೆ_w, ಎಡ_pad_w, ಬಲ_pad_w;                                           \
    Sint64 fp_ಮೊತ್ತ_w_init;                                                             \
    ಪೂರ್ಣಾಂಕ ಎಡ_pad_w_init, ಬಲ_pad_w_init, dst_gap, ಮಧ್ಯ_init;                      \
    get_scaler_datas(src_h, dst_h, &fp_ಮೊತ್ತ_h, &fp_ಹೆಜ್ಜೆ_h, &ಎಡ_pad_h, &ಬಲ_pad_h); \
    get_scaler_datas(src_w, dst_w, &fp_ಮೊತ್ತ_w, &fp_ಹೆಜ್ಜೆ_w, &ಎಡ_pad_w, &ಬಲ_pad_w); \
    fp_ಮೊತ್ತ_w_init = fp_ಮೊತ್ತ_w + ಎಡ_pad_w * fp_ಹೆಜ್ಜೆ_w;                                \
    ಎಡ_pad_w_init = ಎಡ_pad_w;                                                     \
    ಬಲ_pad_w_init = ಬಲ_pad_w;                                                   \
    dst_gap = dst_pitch - 4 * dst_w;                                                  \
    ಮಧ್ಯ_init = dst_w - ಎಡ_pad_w - ಬಲ_pad_w;

#ವ್ಯಾಖ್ಯಾನಿಸು BILINEAR_ಎತ್ತರ                                              \
    ಪೂರ್ಣಾಂಕ ಸೂಚ್ಯಂಕ_h, frac_h0, frac_h1, ಮಧ್ಯ;                             \
    ಸ್ಥಿರಾಂಕ Uint32 *src_h0, *src_h1;                                     \
    ಪೂರ್ಣಾಂಕ no_padding;                                                    \
    Uint64 incr_h0, incr_h1;                                           \
                                                                       \
    no_padding = !(i < ಎಡ_pad_h || i > dst_h - 1 - ಬಲ_pad_h);     \
    ಸೂಚ್ಯಂಕ_h = SRC_ಸೂಚ್ಯಂಕ(fp_ಮೊತ್ತ_h);                                     \
    frac_h0 = FRAC(fp_ಮೊತ್ತ_h);                                          \
                                                                       \
    ಸೂಚ್ಯಂಕ_h = no_padding ? ಸೂಚ್ಯಂಕ_h : (i < ಎಡ_pad_h ? 0 : src_h - 1); \
    frac_h0 = no_padding ? frac_h0 : 0;                                \
    incr_h1 = no_padding ? src_pitch : 0;                              \
    incr_h0 = (Uint64)ಸೂಚ್ಯಂಕ_h * src_pitch;                             \
                                                                       \
    src_h0 = (ಸ್ಥಿರಾಂಕ Uint32 *)((ಸ್ಥಿರಾಂಕ Uint8 *)src + incr_h0);           \
    src_h1 = (ಸ್ಥಿರಾಂಕ Uint32 *)((ಸ್ಥಿರಾಂಕ Uint8 *)src_h0 + incr_h1);        \
                                                                       \
    fp_ಮೊತ್ತ_h += fp_ಹೆಜ್ಜೆ_h;                                             \
                                                                       \
    frac_h1 = FRAC_ONE - frac_h0;                                      \
    fp_ಮೊತ್ತ_w = fp_ಮೊತ್ತ_w_init;                                          \
    ಬಲ_pad_w = ಬಲ_pad_w_init;                                    \
    ಎಡ_pad_w = ಎಡ_pad_w_init;                                      \
    ಮಧ್ಯ = ಮಧ್ಯ_init;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __clang__
// Remove inlining of this function
// Compiler crash with clang 9.0.8 / android-ndk-r21d
// Compiler crash with clang 11.0.3 / Xcode
// OK with clang 11.0.5 / android-ndk-22
// OK with clang 12.0.0 / Xcode
__attribute__((noinline))
#ಆದರೆ_ಅಂತ್ಯ
ಸ್ಥಿರ ಶೂನ್ಯ get_scaler_datas(ಪೂರ್ಣಾಂಕ src_nb, ಪೂರ್ಣಾಂಕ dst_nb, Sint64 *fp_ಆರಂಭ, ಪೂರ್ಣಾಂಕ *fp_ಹೆಜ್ಜೆ, ಪೂರ್ಣಾಂಕ *ಎಡ_pad, ಪೂರ್ಣಾಂಕ *ಬಲ_pad)
{

    ಪೂರ್ಣಾಂಕ ಹೆಜ್ಜೆ = FIXED_ಬಿಂದು(src_nb) / (dst_nb); // source step in fixed point
    ಪೂರ್ಣಾಂಕ x0 = FP_ONE / 2;                       // dst first pixel center at 0.5 in fixed point
    Sint64 fp_ಮೊತ್ತ;
    ಪೂರ್ಣಾಂಕ i;
#ಆದರೆ 0
    // scale to source coordinates
    x0 *= src_nb;
    x0 /= dst_nb; // x0 == step / 2
#ಇಲ್ಲದಿದ್ದರೆ
    // Use this code for perfect match with pixman
    Sint64 tmp[2];
    tmp[0] = (Sint64)ಹೆಜ್ಜೆ * (x0 >> 16);
    tmp[1] = (Sint64)ಹೆಜ್ಜೆ * (x0 & 0xFFFF);
    x0 = (ಪೂರ್ಣಾಂಕ)(tmp[0] + ((tmp[1] + 0x8000) >> 16)); // x0 == (step + 1) / 2
#ಆದರೆ_ಅಂತ್ಯ
    // -= 0.5, get back the pixel origin, in source coordinates
    x0 -= FP_ONE / 2;

    *fp_ಆರಂಭ = x0;
    *fp_ಹೆಜ್ಜೆ = ಹೆಜ್ಜೆ;
    *ಎಡ_pad = 0;
    *ಬಲ_pad = 0;

    fp_ಮೊತ್ತ = x0;
    ಗಾಗಿ (i = 0; i < dst_nb; i++) {
        ಆದರೆ (fp_ಮೊತ್ತ < 0) {
            *ಎಡ_pad += 1;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಪೂರ್ಣಾಂಕ ಸೂಚ್ಯಂಕ = SRC_ಸೂಚ್ಯಂಕ(fp_ಮೊತ್ತ);
            ಆದರೆ (ಸೂಚ್ಯಂಕ > src_nb - 2) {
                *ಬಲ_pad += 1;
            }
        }
        fp_ಮೊತ್ತ += ಹೆಜ್ಜೆ;
    }
    //    SDL_Log("%d -> %d  x0=%d step=%d left_pad=%d right_pad=%d", src_nb, dst_nb, *fp_start, *fp_step, *left_pad, *right_pad);
}

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ color_t
{
    Uint8 a;
    Uint8 b;
    Uint8 c;
    Uint8 d;
} color_t;

/* Interpolated == x0 + frac * (x1 - x0) == x0 * (1 - frac) + x1 * frac */

ಸ್ಥಿರ SDL_INLINE ಶೂನ್ಯ INTERPOL(ಸ್ಥಿರಾಂಕ Uint32 *src_x0, ಸ್ಥಿರಾಂಕ Uint32 *src_x1, ಪೂರ್ಣಾಂಕ frac0, ಪೂರ್ಣಾಂಕ frac1, Uint32 *dst)
{
    ಸ್ಥಿರಾಂಕ color_t *c0 = (ಸ್ಥಿರಾಂಕ color_t *)src_x0;
    ಸ್ಥಿರಾಂಕ color_t *c1 = (ಸ್ಥಿರಾಂಕ color_t *)src_x1;
    color_t *cx = (color_t *)dst;
#ಆದರೆ 0
    cx->a = c0->a + INTEGER(frac0 * (c1->a - c0->a));
    cx->b = c0->b + INTEGER(frac0 * (c1->b - c0->b));
    cx->c = c0->c + INTEGER(frac0 * (c1->c - c0->c));
    cx->d = c0->d + INTEGER(frac0 * (c1->d - c0->d));
#ಇಲ್ಲದಿದ್ದರೆ
    cx->a = (Uint8)INTEGER(frac1 * c0->a + frac0 * c1->a);
    cx->b = (Uint8)INTEGER(frac1 * c0->b + frac0 * c1->b);
    cx->c = (Uint8)INTEGER(frac1 * c0->c + frac0 * c1->c);
    cx->d = (Uint8)INTEGER(frac1 * c0->d + frac0 * c1->d);
#ಆದರೆ_ಅಂತ್ಯ
}

ಸ್ಥಿರ SDL_INLINE ಶೂನ್ಯ INTERPOL_BILINEAR(ಸ್ಥಿರಾಂಕ Uint32 *s0, ಸ್ಥಿರಾಂಕ Uint32 *s1, ಪೂರ್ಣಾಂಕ frac_w0, ಪೂರ್ಣಾಂಕ frac_h0, ಪೂರ್ಣಾಂಕ frac_h1, Uint32 *dst)
{
    Uint32 tmp[2];
    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ frac_w1 = FRAC_ONE - frac_w0;

    // Vertical first, store to 'tmp'
    INTERPOL(s0, s1, frac_h0, frac_h1, tmp);
    INTERPOL(s0 + 1, s1 + 1, frac_h0, frac_h1, tmp + 1);

    // Horizontal, store to 'dst'
    INTERPOL(tmp, tmp + 1, frac_w0, frac_w1, dst);
}

ಸ್ಥಿರ bool scale_mat(ಸ್ಥಿರಾಂಕ Uint32 *src, ಪೂರ್ಣಾಂಕ src_w, ಪೂರ್ಣಾಂಕ src_h, ಪೂರ್ಣಾಂಕ src_pitch, Uint32 *dst, ಪೂರ್ಣಾಂಕ dst_w, ಪೂರ್ಣಾಂಕ dst_h, ಪೂರ್ಣಾಂಕ dst_pitch)
{
    BILINEAR_ಆರಂಭ

    ಗಾಗಿ (i = 0; i < dst_h; i++) {

        BILINEAR_ಎತ್ತರ

        ಆಗ (ಎಡ_pad_w--) {
            INTERPOL_BILINEAR(src_h0, src_h1, FRAC_ZERO, frac_h0, frac_h1, dst);
            dst += 1;
        }

        ಆಗ (ಮಧ್ಯ--) {
            ಸ್ಥಿರಾಂಕ Uint32 *s_00_01;
            ಸ್ಥಿರಾಂಕ Uint32 *s_10_11;
            ಪೂರ್ಣಾಂಕ ಸೂಚ್ಯಂಕ_w = 4 * SRC_ಸೂಚ್ಯಂಕ(fp_ಮೊತ್ತ_w);
            ಪೂರ್ಣಾಂಕ frac_w = FRAC(fp_ಮೊತ್ತ_w);
            fp_ಮೊತ್ತ_w += fp_ಹೆಜ್ಜೆ_w;

            /*
                        x00 ... x0_ ..... x01
                        .       .         .
                        .       x         .
                        .       .         .
                        .       .         .
                        x10 ... x1_ ..... x11
            */
            s_00_01 = (ಸ್ಥಿರಾಂಕ Uint32 *)((ಸ್ಥಿರಾಂಕ Uint8 *)src_h0 + ಸೂಚ್ಯಂಕ_w);
            s_10_11 = (ಸ್ಥಿರಾಂಕ Uint32 *)((ಸ್ಥಿರಾಂಕ Uint8 *)src_h1 + ಸೂಚ್ಯಂಕ_w);

            INTERPOL_BILINEAR(s_00_01, s_10_11, frac_w, frac_h0, frac_h1, dst);

            dst += 1;
        }

        ಆಗ (ಬಲ_pad_w--) {
            ಪೂರ್ಣಾಂಕ ಸೂಚ್ಯಂಕ_w = 4 * (src_w - 2);
            ಸ್ಥಿರಾಂಕ Uint32 *s_00_01 = (ಸ್ಥಿರಾಂಕ Uint32 *)((ಸ್ಥಿರಾಂಕ Uint8 *)src_h0 + ಸೂಚ್ಯಂಕ_w);
            ಸ್ಥಿರಾಂಕ Uint32 *s_10_11 = (ಸ್ಥಿರಾಂಕ Uint32 *)((ಸ್ಥಿರಾಂಕ Uint8 *)src_h1 + ಸೂಚ್ಯಂಕ_w);
            INTERPOL_BILINEAR(s_00_01, s_10_11, FRAC_ONE, frac_h0, frac_h1, dst);
            dst += 1;
        }
        dst = (Uint32 *)((Uint8 *)dst + dst_gap);
    }
    ಹಿಂತಿರುಗಿ true;
}

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_SSE2_INTRINSICS

ಸ್ಥಿರ SDL_INLINE ಪೂರ್ಣಾಂಕ hasSSE2(ಶೂನ್ಯ)
{
    ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ val = -1;
    ಆದರೆ (val != -1) {
        ಹಿಂತಿರುಗಿ val;
    }
    val = SDL_HasSSE2();
    ಹಿಂತಿರುಗಿ val;
}

ಸ್ಥಿರ SDL_INLINE ಶೂನ್ಯ SDL_TARGETING("sse2") INTERPOL_BILINEAR_SSE(ಸ್ಥಿರಾಂಕ Uint32 *s0, ಸ್ಥಿರಾಂಕ Uint32 *s1, ಪೂರ್ಣಾಂಕ frac_w, __m128i v_frac_h0, __m128i v_frac_h1, Uint32 *dst, __m128i zero)
{
    __m128i x_00_01, x_10_11; /* Pixels in 4*uint8 in row */
    __m128i v_frac_w0, k0, l0, d0, e0;

    ಪೂರ್ಣಾಂಕ f, f2;
    f = frac_w;
    f2 = FRAC_ONE - frac_w;
    v_frac_w0 = mm_ಗಣ_epi16((ಗಿಡ್ಡ)f, (ಗಿಡ್ಡ)f2, (ಗಿಡ್ಡ)f, (ಗಿಡ್ಡ)f2, (ಗಿಡ್ಡ)f, (ಗಿಡ್ಡ)f2, (ಗಿಡ್ಡ)f, (ಗಿಡ್ಡ)f2);

    x_00_01 = _mm_loadl_epi64((ಸ್ಥಿರಾಂಕ __m128i *)s0); // Load x00 and x01
    x_10_11 = _mm_loadl_epi64((ಸ್ಥಿರಾಂಕ __m128i *)s1);

    /* Interpolated == x0 + frac * (x1 - x0) == x0 * (1 - frac) + x1 * frac */

    // Interpolation vertical
    k0 = _mm_mullo_epi16(_mm_unpacklo_epi8(x_00_01, zero), v_frac_h1);
    l0 = _mm_mullo_epi16(_mm_unpacklo_epi8(x_10_11, zero), v_frac_h0);
    k0 = mm_ಕೂಡಿಸು_epi16(k0, l0);

    // For perfect match, clear the factionnal part eventually.
    /*
    k0 = _mm_srli_epi16(k0, PRECISION);
    k0 = _mm_slli_epi16(k0, PRECISION);
    */

    // Interpolation horizontal
    l0 = _mm_unpacklo_epi64(/*ಬಳಸದ*/ l0, k0);
    k0 = _mm_madd_epi16(_mm_unpackhi_epi16(l0, k0), v_frac_w0);

    // Store 1 pixel
    d0 = _mm_srli_epi32(k0, PRECISION * 2);
    e0 = _mm_packs_epi32(d0, d0);
    e0 = _mm_packus_epi16(e0, e0);
    *dst = _mm_cvtsi128_si32(e0);
}

ಸ್ಥಿರ bool SDL_TARGETING("sse2") scale_mat_SSE(ಸ್ಥಿರಾಂಕ Uint32 *src, ಪೂರ್ಣಾಂಕ src_w, ಪೂರ್ಣಾಂಕ src_h, ಪೂರ್ಣಾಂಕ src_pitch, Uint32 *dst, ಪೂರ್ಣಾಂಕ dst_w, ಪೂರ್ಣಾಂಕ dst_h, ಪೂರ್ಣಾಂಕ dst_pitch)
{
    BILINEAR_ಆರಂಭ

    ಗಾಗಿ (i = 0; i < dst_h; i++) {
        ಪೂರ್ಣಾಂಕ nb_block2;
        __m128i v_frac_h0;
        __m128i v_frac_h1;
        __m128i zero;

        BILINEAR_ಎತ್ತರ

        nb_block2 = ಮಧ್ಯ / 2;

        v_frac_h0 = mm_ಗಣ_epi16((ಗಿಡ್ಡ)frac_h0, (ಗಿಡ್ಡ)frac_h0, (ಗಿಡ್ಡ)frac_h0, (ಗಿಡ್ಡ)frac_h0, (ಗಿಡ್ಡ)frac_h0, (ಗಿಡ್ಡ)frac_h0, (ಗಿಡ್ಡ)frac_h0, (ಗಿಡ್ಡ)frac_h0);
        v_frac_h1 = mm_ಗಣ_epi16((ಗಿಡ್ಡ)frac_h1, (ಗಿಡ್ಡ)frac_h1, (ಗಿಡ್ಡ)frac_h1, (ಗಿಡ್ಡ)frac_h1, (ಗಿಡ್ಡ)frac_h1, (ಗಿಡ್ಡ)frac_h1, (ಗಿಡ್ಡ)frac_h1, (ಗಿಡ್ಡ)frac_h1);
        zero = _mm_setzero_si128();

        ಆಗ (ಎಡ_pad_w--) {
            INTERPOL_BILINEAR_SSE(src_h0, src_h1, FRAC_ZERO, v_frac_h0, v_frac_h1, dst, zero);
            dst += 1;
        }

        ಆಗ (nb_block2--) {
            ಪೂರ್ಣಾಂಕ ಸೂಚ್ಯಂಕ_w_0, frac_w_0;
            ಪೂರ್ಣಾಂಕ ಸೂಚ್ಯಂಕ_w_1, frac_w_1;

            ಸ್ಥಿರಾಂಕ Uint32 *s_00_01, *s_02_03, *s_10_11, *s_12_13;

            __m128i x_00_01, x_10_11, x_02_03, x_12_13; /* Pixels in 4*uint8 in row */
            __m128i v_frac_w0, k0, l0, d0, e0;
            __m128i v_frac_w1, k1, l1, d1, e1;

            ಪೂರ್ಣಾಂಕ f, f2;
            ಸೂಚ್ಯಂಕ_w_0 = 4 * SRC_ಸೂಚ್ಯಂಕ(fp_ಮೊತ್ತ_w);
            frac_w_0 = FRAC(fp_ಮೊತ್ತ_w);
            fp_ಮೊತ್ತ_w += fp_ಹೆಜ್ಜೆ_w;
            ಸೂಚ್ಯಂಕ_w_1 = 4 * SRC_ಸೂಚ್ಯಂಕ(fp_ಮೊತ್ತ_w);
            frac_w_1 = FRAC(fp_ಮೊತ್ತ_w);
            fp_ಮೊತ್ತ_w += fp_ಹೆಜ್ಜೆ_w;
            /*
                        x00............ x01   x02...........x03
                        .      .         .     .       .     .
                        j0     f0        j1    j2      f1    j3
                        .      .         .     .       .     .
                        .      .         .     .       .     .
                        .      .         .     .       .     .
                        x10............ x11   x12...........x13
             */
            s_00_01 = (ಸ್ಥಿರಾಂಕ Uint32 *)((ಸ್ಥಿರಾಂಕ Uint8 *)src_h0 + ಸೂಚ್ಯಂಕ_w_0);
            s_02_03 = (ಸ್ಥಿರಾಂಕ Uint32 *)((ಸ್ಥಿರಾಂಕ Uint8 *)src_h0 + ಸೂಚ್ಯಂಕ_w_1);
            s_10_11 = (ಸ್ಥಿರಾಂಕ Uint32 *)((ಸ್ಥಿರಾಂಕ Uint8 *)src_h1 + ಸೂಚ್ಯಂಕ_w_0);
            s_12_13 = (ಸ್ಥಿರಾಂಕ Uint32 *)((ಸ್ಥಿರಾಂಕ Uint8 *)src_h1 + ಸೂಚ್ಯಂಕ_w_1);

            f = frac_w_0;
            f2 = FRAC_ONE - frac_w_0;
            v_frac_w0 = mm_ಗಣ_epi16((ಗಿಡ್ಡ)f, (ಗಿಡ್ಡ)f2, (ಗಿಡ್ಡ)f, (ಗಿಡ್ಡ)f2, (ಗಿಡ್ಡ)f, (ಗಿಡ್ಡ)f2, (ಗಿಡ್ಡ)f, (ಗಿಡ್ಡ)f2);

            f = frac_w_1;
            f2 = FRAC_ONE - frac_w_1;
            v_frac_w1 = mm_ಗಣ_epi16((ಗಿಡ್ಡ)f, (ಗಿಡ್ಡ)f2, (ಗಿಡ್ಡ)f, (ಗಿಡ್ಡ)f2, (ಗಿಡ್ಡ)f, (ಗಿಡ್ಡ)f2, (ಗಿಡ್ಡ)f, (ಗಿಡ್ಡ)f2);

            x_00_01 = _mm_loadl_epi64((ಸ್ಥಿರಾಂಕ __m128i *)s_00_01); // Load x00 and x01
            x_02_03 = _mm_loadl_epi64((ಸ್ಥಿರಾಂಕ __m128i *)s_02_03);
            x_10_11 = _mm_loadl_epi64((ಸ್ಥಿರಾಂಕ __m128i *)s_10_11);
            x_12_13 = _mm_loadl_epi64((ಸ್ಥಿರಾಂಕ __m128i *)s_12_13);

            // Interpolation vertical
            k0 = _mm_mullo_epi16(_mm_unpacklo_epi8(x_00_01, zero), v_frac_h1);
            l0 = _mm_mullo_epi16(_mm_unpacklo_epi8(x_10_11, zero), v_frac_h0);
            k0 = mm_ಕೂಡಿಸು_epi16(k0, l0);
            k1 = _mm_mullo_epi16(_mm_unpacklo_epi8(x_02_03, zero), v_frac_h1);
            l1 = _mm_mullo_epi16(_mm_unpacklo_epi8(x_12_13, zero), v_frac_h0);
            k1 = mm_ಕೂಡಿಸು_epi16(k1, l1);

            // Interpolation horizontal
            l0 = _mm_unpacklo_epi64(/*ಬಳಸದ*/ l0, k0);
            k0 = _mm_madd_epi16(_mm_unpackhi_epi16(l0, k0), v_frac_w0);
            l1 = _mm_unpacklo_epi64(/*ಬಳಸದ*/ l1, k1);
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
        ಆದರೆ (ಮಧ್ಯ & 0x1) {
            ಸ್ಥಿರಾಂಕ Uint32 *s_00_01;
            ಸ್ಥಿರಾಂಕ Uint32 *s_10_11;
            ಪೂರ್ಣಾಂಕ ಸೂಚ್ಯಂಕ_w = 4 * SRC_ಸೂಚ್ಯಂಕ(fp_ಮೊತ್ತ_w);
            ಪೂರ್ಣಾಂಕ frac_w = FRAC(fp_ಮೊತ್ತ_w);
            fp_ಮೊತ್ತ_w += fp_ಹೆಜ್ಜೆ_w;
            s_00_01 = (ಸ್ಥಿರಾಂಕ Uint32 *)((ಸ್ಥಿರಾಂಕ Uint8 *)src_h0 + ಸೂಚ್ಯಂಕ_w);
            s_10_11 = (ಸ್ಥಿರಾಂಕ Uint32 *)((ಸ್ಥಿರಾಂಕ Uint8 *)src_h1 + ಸೂಚ್ಯಂಕ_w);
            INTERPOL_BILINEAR_SSE(s_00_01, s_10_11, frac_w, v_frac_h0, v_frac_h1, dst, zero);
            dst += 1;
        }

        ಆಗ (ಬಲ_pad_w--) {
            ಪೂರ್ಣಾಂಕ ಸೂಚ್ಯಂಕ_w = 4 * (src_w - 2);
            ಸ್ಥಿರಾಂಕ Uint32 *s_00_01 = (ಸ್ಥಿರಾಂಕ Uint32 *)((ಸ್ಥಿರಾಂಕ Uint8 *)src_h0 + ಸೂಚ್ಯಂಕ_w);
            ಸ್ಥಿರಾಂಕ Uint32 *s_10_11 = (ಸ್ಥಿರಾಂಕ Uint32 *)((ಸ್ಥಿರಾಂಕ Uint8 *)src_h1 + ಸೂಚ್ಯಂಕ_w);
            INTERPOL_BILINEAR_SSE(s_00_01, s_10_11, FRAC_ONE, v_frac_h0, v_frac_h1, dst, zero);
            dst += 1;
        }
        dst = (Uint32 *)((Uint8 *)dst + dst_gap);
    }
    ಹಿಂತಿರುಗಿ true;
}
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_NEON_INTRINSICS

ಸ್ಥಿರ SDL_INLINE ಪೂರ್ಣಾಂಕ hasNEON(ಶೂನ್ಯ)
{
    ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ val = -1;
    ಆದರೆ (val != -1) {
        ಹಿಂತಿರುಗಿ val;
    }
    val = SDL_HasNEON();
    ಹಿಂತಿರುಗಿ val;
}

ಸ್ಥಿರ SDL_INLINE ಶೂನ್ಯ INTERPOL_BILINEAR_NEON(ಸ್ಥಿರಾಂಕ Uint32 *s0, ಸ್ಥಿರಾಂಕ Uint32 *s1, ಪೂರ್ಣಾಂಕ frac_w, uint8x8_t v_frac_h0, uint8x8_t v_frac_h1, Uint32 *dst)
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
    l0 = vshll_n_u16(vget_ಕೆಳಗಿನ_u16(k0), PRECISION);
    l0 = vmlsl_n_u16(l0, vget_ಕೆಳಗಿನ_u16(k0), frac_w);
    l0 = vmlal_n_u16(l0, vget_ಮೇಲಿನ_u16(k0), frac_w);

    // Shift and narrow
    d0 = vcombine_u16(
        /* uint16x4_t */ vshrn_n_u32(l0, 2 * PRECISION),
        /* uint16x4_t */ vshrn_n_u32(l0, 2 * PRECISION));

    // Narrow again
    e0 = vmovn_u16(d0);

    // Store 1 pixel
    *dst = vget_lane_u32(vreinterpret_u32_u8(e0), 0);
}

ಸ್ಥಿರ bool scale_mat_NEON(ಸ್ಥಿರಾಂಕ Uint32 *src, ಪೂರ್ಣಾಂಕ src_w, ಪೂರ್ಣಾಂಕ src_h, ಪೂರ್ಣಾಂಕ src_pitch, Uint32 *dst, ಪೂರ್ಣಾಂಕ dst_w, ಪೂರ್ಣಾಂಕ dst_h, ಪೂರ್ಣಾಂಕ dst_pitch)
{
    BILINEAR_ಆರಂಭ

    ಗಾಗಿ (i = 0; i < dst_h; i++) {
        ಪೂರ್ಣಾಂಕ nb_block4;
        uint8x8_t v_frac_h0, v_frac_h1;

        BILINEAR_ಎತ್ತರ

        nb_block4 = ಮಧ್ಯ / 4;

        v_frac_h0 = vmov_n_u8(frac_h0);
        v_frac_h1 = vmov_n_u8(frac_h1);

        ಆಗ (ಎಡ_pad_w--) {
            INTERPOL_BILINEAR_NEON(src_h0, src_h1, FRAC_ZERO, v_frac_h0, v_frac_h1, dst);
            dst += 1;
        }

        ಆಗ (nb_block4--) {
            ಪೂರ್ಣಾಂಕ ಸೂಚ್ಯಂಕ_w_0, frac_w_0;
            ಪೂರ್ಣಾಂಕ ಸೂಚ್ಯಂಕ_w_1, frac_w_1;
            ಪೂರ್ಣಾಂಕ ಸೂಚ್ಯಂಕ_w_2, frac_w_2;
            ಪೂರ್ಣಾಂಕ ಸೂಚ್ಯಂಕ_w_3, frac_w_3;

            ಸ್ಥಿರಾಂಕ Uint32 *s_00_01, *s_02_03, *s_04_05, *s_06_07;
            ಸ್ಥಿರಾಂಕ Uint32 *s_10_11, *s_12_13, *s_14_15, *s_16_17;

            uint8x8_t x_00_01, x_10_11, x_02_03, x_12_13; /* Pixels in 4*uint8 in row */
            uint8x8_t x_04_05, x_14_15, x_06_07, x_16_17;

            uint16x8_t k0, k1, k2, k3;
            uint32x4_t l0, l1, l2, l3;
            uint16x8_t d0, d1;
            uint8x8_t e0, e1;
            uint32x4_t f0;

            ಸೂಚ್ಯಂಕ_w_0 = 4 * SRC_ಸೂಚ್ಯಂಕ(fp_ಮೊತ್ತ_w);
            frac_w_0 = FRAC(fp_ಮೊತ್ತ_w);
            fp_ಮೊತ್ತ_w += fp_ಹೆಜ್ಜೆ_w;
            ಸೂಚ್ಯಂಕ_w_1 = 4 * SRC_ಸೂಚ್ಯಂಕ(fp_ಮೊತ್ತ_w);
            frac_w_1 = FRAC(fp_ಮೊತ್ತ_w);
            fp_ಮೊತ್ತ_w += fp_ಹೆಜ್ಜೆ_w;
            ಸೂಚ್ಯಂಕ_w_2 = 4 * SRC_ಸೂಚ್ಯಂಕ(fp_ಮೊತ್ತ_w);
            frac_w_2 = FRAC(fp_ಮೊತ್ತ_w);
            fp_ಮೊತ್ತ_w += fp_ಹೆಜ್ಜೆ_w;
            ಸೂಚ್ಯಂಕ_w_3 = 4 * SRC_ಸೂಚ್ಯಂಕ(fp_ಮೊತ್ತ_w);
            frac_w_3 = FRAC(fp_ಮೊತ್ತ_w);
            fp_ಮೊತ್ತ_w += fp_ಹೆಜ್ಜೆ_w;

            s_00_01 = (ಸ್ಥಿರಾಂಕ Uint32 *)((ಸ್ಥಿರಾಂಕ Uint8 *)src_h0 + ಸೂಚ್ಯಂಕ_w_0);
            s_02_03 = (ಸ್ಥಿರಾಂಕ Uint32 *)((ಸ್ಥಿರಾಂಕ Uint8 *)src_h0 + ಸೂಚ್ಯಂಕ_w_1);
            s_04_05 = (ಸ್ಥಿರಾಂಕ Uint32 *)((ಸ್ಥಿರಾಂಕ Uint8 *)src_h0 + ಸೂಚ್ಯಂಕ_w_2);
            s_06_07 = (ಸ್ಥಿರಾಂಕ Uint32 *)((ಸ್ಥಿರಾಂಕ Uint8 *)src_h0 + ಸೂಚ್ಯಂಕ_w_3);
            s_10_11 = (ಸ್ಥಿರಾಂಕ Uint32 *)((ಸ್ಥಿರಾಂಕ Uint8 *)src_h1 + ಸೂಚ್ಯಂಕ_w_0);
            s_12_13 = (ಸ್ಥಿರಾಂಕ Uint32 *)((ಸ್ಥಿರಾಂಕ Uint8 *)src_h1 + ಸೂಚ್ಯಂಕ_w_1);
            s_14_15 = (ಸ್ಥಿರಾಂಕ Uint32 *)((ಸ್ಥಿರಾಂಕ Uint8 *)src_h1 + ಸೂಚ್ಯಂಕ_w_2);
            s_16_17 = (ಸ್ಥಿರಾಂಕ Uint32 *)((ಸ್ಥಿರಾಂಕ Uint8 *)src_h1 + ಸೂಚ್ಯಂಕ_w_3);

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

            l0 = vshll_n_u16(vget_ಕೆಳಗಿನ_u16(k0), PRECISION);
            l0 = vmlsl_n_u16(l0, vget_ಕೆಳಗಿನ_u16(k0), frac_w_0);
            l0 = vmlal_n_u16(l0, vget_ಮೇಲಿನ_u16(k0), frac_w_0);

            l1 = vshll_n_u16(vget_ಕೆಳಗಿನ_u16(k1), PRECISION);
            l1 = vmlsl_n_u16(l1, vget_ಕೆಳಗಿನ_u16(k1), frac_w_1);
            l1 = vmlal_n_u16(l1, vget_ಮೇಲಿನ_u16(k1), frac_w_1);

            l2 = vshll_n_u16(vget_ಕೆಳಗಿನ_u16(k2), PRECISION);
            l2 = vmlsl_n_u16(l2, vget_ಕೆಳಗಿನ_u16(k2), frac_w_2);
            l2 = vmlal_n_u16(l2, vget_ಮೇಲಿನ_u16(k2), frac_w_2);

            l3 = vshll_n_u16(vget_ಕೆಳಗಿನ_u16(k3), PRECISION);
            l3 = vmlsl_n_u16(l3, vget_ಕೆಳಗಿನ_u16(k3), frac_w_3);
            l3 = vmlal_n_u16(l3, vget_ಮೇಲಿನ_u16(k3), frac_w_3);

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

        ಆದರೆ (ಮಧ್ಯ & 0x2) {
            ಪೂರ್ಣಾಂಕ ಸೂಚ್ಯಂಕ_w_0, frac_w_0;
            ಪೂರ್ಣಾಂಕ ಸೂಚ್ಯಂಕ_w_1, frac_w_1;
            ಸ್ಥಿರಾಂಕ Uint32 *s_00_01, *s_02_03;
            ಸ್ಥಿರಾಂಕ Uint32 *s_10_11, *s_12_13;
            uint8x8_t x_00_01, x_10_11, x_02_03, x_12_13; /* Pixels in 4*uint8 in row */
            uint16x8_t k0, k1;
            uint32x4_t l0, l1;
            uint16x8_t d0;
            uint8x8_t e0;

            ಸೂಚ್ಯಂಕ_w_0 = 4 * SRC_ಸೂಚ್ಯಂಕ(fp_ಮೊತ್ತ_w);
            frac_w_0 = FRAC(fp_ಮೊತ್ತ_w);
            fp_ಮೊತ್ತ_w += fp_ಹೆಜ್ಜೆ_w;
            ಸೂಚ್ಯಂಕ_w_1 = 4 * SRC_ಸೂಚ್ಯಂಕ(fp_ಮೊತ್ತ_w);
            frac_w_1 = FRAC(fp_ಮೊತ್ತ_w);
            fp_ಮೊತ್ತ_w += fp_ಹೆಜ್ಜೆ_w;
            /*
                        x00............ x01   x02...........x03
                        .      .         .     .       .     .
                        j0   dest0       j1    j2    dest1   j3
                        .      .         .     .       .     .
                        .      .         .     .       .     .
                        .      .         .     .       .     .
                        x10............ x11   x12...........x13
            */
            s_00_01 = (ಸ್ಥಿರಾಂಕ Uint32 *)((ಸ್ಥಿರಾಂಕ Uint8 *)src_h0 + ಸೂಚ್ಯಂಕ_w_0);
            s_02_03 = (ಸ್ಥಿರಾಂಕ Uint32 *)((ಸ್ಥಿರಾಂಕ Uint8 *)src_h0 + ಸೂಚ್ಯಂಕ_w_1);
            s_10_11 = (ಸ್ಥಿರಾಂಕ Uint32 *)((ಸ್ಥಿರಾಂಕ Uint8 *)src_h1 + ಸೂಚ್ಯಂಕ_w_0);
            s_12_13 = (ಸ್ಥಿರಾಂಕ Uint32 *)((ಸ್ಥಿರಾಂಕ Uint8 *)src_h1 + ಸೂಚ್ಯಂಕ_w_1);

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

            l0 = vshll_n_u16(vget_ಕೆಳಗಿನ_u16(k0), PRECISION);
            l0 = vmlsl_n_u16(l0, vget_ಕೆಳಗಿನ_u16(k0), frac_w_0);
            l0 = vmlal_n_u16(l0, vget_ಮೇಲಿನ_u16(k0), frac_w_0);

            l1 = vshll_n_u16(vget_ಕೆಳಗಿನ_u16(k1), PRECISION);
            l1 = vmlsl_n_u16(l1, vget_ಕೆಳಗಿನ_u16(k1), frac_w_1);
            l1 = vmlal_n_u16(l1, vget_ಮೇಲಿನ_u16(k1), frac_w_1);

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
        ಆದರೆ (ಮಧ್ಯ & 0x1) {
            ಪೂರ್ಣಾಂಕ ಸೂಚ್ಯಂಕ_w = 4 * SRC_ಸೂಚ್ಯಂಕ(fp_ಮೊತ್ತ_w);
            ಪೂರ್ಣಾಂಕ frac_w = FRAC(fp_ಮೊತ್ತ_w);
            ಸ್ಥಿರಾಂಕ Uint32 *s_00_01 = (ಸ್ಥಿರಾಂಕ Uint32 *)((ಸ್ಥಿರಾಂಕ Uint8 *)src_h0 + ಸೂಚ್ಯಂಕ_w);
            ಸ್ಥಿರಾಂಕ Uint32 *s_10_11 = (ಸ್ಥಿರಾಂಕ Uint32 *)((ಸ್ಥಿರಾಂಕ Uint8 *)src_h1 + ಸೂಚ್ಯಂಕ_w);
            INTERPOL_BILINEAR_NEON(s_00_01, s_10_11, frac_w, v_frac_h0, v_frac_h1, dst);
            dst += 1;
        }

        ಆಗ (ಬಲ_pad_w--) {
            ಪೂರ್ಣಾಂಕ ಸೂಚ್ಯಂಕ_w = 4 * (src_w - 2);
            ಸ್ಥಿರಾಂಕ Uint32 *s_00_01 = (ಸ್ಥಿರಾಂಕ Uint32 *)((ಸ್ಥಿರಾಂಕ Uint8 *)src_h0 + ಸೂಚ್ಯಂಕ_w);
            ಸ್ಥಿರಾಂಕ Uint32 *s_10_11 = (ಸ್ಥಿರಾಂಕ Uint32 *)((ಸ್ಥಿರಾಂಕ Uint8 *)src_h1 + ಸೂಚ್ಯಂಕ_w);
            INTERPOL_BILINEAR_NEON(s_00_01, s_10_11, FRAC_ONE, v_frac_h0, v_frac_h1, dst);
            dst += 1;
        }

        dst = (Uint32 *)((Uint8 *)dst + dst_gap);
    }
    ಹಿಂತಿರುಗಿ true;
}
#ಆದರೆ_ಅಂತ್ಯ

bool SDL_Stretch_Surface_Unchecked_ರೇಖೀಯ(SDL_Surface *s, ಸ್ಥಿರಾಂಕ SDL_Rect *srcrect, SDL_Surface *d, ಸ್ಥಿರಾಂಕ SDL_Rect *dstrect)
{
    bool ಫಲಿತಾಂಶ = false;
    ಪೂರ್ಣಾಂಕ src_w = srcrect->w;
    ಪೂರ್ಣಾಂಕ src_h = srcrect->h;
    ಪೂರ್ಣಾಂಕ dst_w = dstrect->w;
    ಪೂರ್ಣಾಂಕ dst_h = dstrect->h;
    ಪೂರ್ಣಾಂಕ src_pitch = s->pitch;
    ಪೂರ್ಣಾಂಕ dst_pitch = d->pitch;
    Uint32 *src = (Uint32 *)((Uint8 *)s->pixels + srcrect->x * 4 + srcrect->y * src_pitch);
    Uint32 *dst = (Uint32 *)((Uint8 *)d->pixels + dstrect->x * 4 + dstrect->y * dst_pitch);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_NEON_INTRINSICS
    ಆದರೆ (!ಫಲಿತಾಂಶ && hasNEON()) {
        ಫಲಿತಾಂಶ = scale_mat_NEON(src, src_w, src_h, src_pitch, dst, dst_w, dst_h, dst_pitch);
    }
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_SSE2_INTRINSICS
    ಆದರೆ (!ಫಲಿತಾಂಶ && hasSSE2()) {
        ಫಲಿತಾಂಶ = scale_mat_SSE(src, src_w, src_h, src_pitch, dst, dst_w, dst_h, dst_pitch);
    }
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (!ಫಲಿತಾಂಶ) {
        ಫಲಿತಾಂಶ = scale_mat(src, src_w, src_h, src_pitch, dst, dst_w, dst_h, dst_pitch);
    }

    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

#ವ್ಯಾಖ್ಯಾನಿಸು SDL_SCALE_ಹತ್ತಿರದ_ಆರಂಭ          \
    ಪೂರ್ಣಾಂಕ i;                                \
    Uint64 posy, incy;                    \
    Uint64 posx, incx;                    \
    Uint64 srcy, srcx;                    \
    ಪೂರ್ಣಾಂಕ dst_gap, n;                       \
    ಸ್ಥಿರಾಂಕ Uint32 *src_h0;                 \
    incy = ((Uint64)src_h << 16) / dst_h; \
    incx = ((Uint64)src_w << 16) / dst_w; \
    dst_gap = dst_pitch - bpp * dst_w;    \
    posy = incy / 2;

#ವ್ಯಾಖ್ಯಾನಿಸು SDL_SCALE_ಹತ್ತಿರದ_ಎತ್ತರ                                         \
    srcy = (posy >> 16);                                                  \
    src_h0 = (ಸ್ಥಿರಾಂಕ Uint32 *)((ಸ್ಥಿರಾಂಕ Uint8 *)src_ptr + srcy * src_pitch); \
    posy += incy;                                                         \
    posx = incx / 2;                                                      \
    n = dst_w;

ಸ್ಥಿರ bool scale_mat_ಹತ್ತಿರದ_1(ಸ್ಥಿರಾಂಕ Uint32 *src_ptr, ಪೂರ್ಣಾಂಕ src_w, ಪೂರ್ಣಾಂಕ src_h, ಪೂರ್ಣಾಂಕ src_pitch, Uint32 *dst, ಪೂರ್ಣಾಂಕ dst_w, ಪೂರ್ಣಾಂಕ dst_h, ಪೂರ್ಣಾಂಕ dst_pitch)
{
    Uint32 bpp = 1;
    SDL_SCALE_ಹತ್ತಿರದ_ಆರಂಭ
    ಗಾಗಿ (i = 0; i < dst_h; i++) {
        SDL_SCALE_ಹತ್ತಿರದ_ಎತ್ತರ
        ಆಗ (n--) {
            ಸ್ಥಿರಾಂಕ Uint8 *src;
            srcx = bpp * (posx >> 16);
            posx += incx;
            src = (ಸ್ಥಿರಾಂಕ Uint8 *)src_h0 + srcx;
            *(Uint8 *)dst = *src;
            dst = (Uint32 *)((Uint8 *)dst + bpp);
        }
        dst = (Uint32 *)((Uint8 *)dst + dst_gap);
    }
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool scale_mat_ಹತ್ತಿರದ_2(ಸ್ಥಿರಾಂಕ Uint32 *src_ptr, ಪೂರ್ಣಾಂಕ src_w, ಪೂರ್ಣಾಂಕ src_h, ಪೂರ್ಣಾಂಕ src_pitch, Uint32 *dst, ಪೂರ್ಣಾಂಕ dst_w, ಪೂರ್ಣಾಂಕ dst_h, ಪೂರ್ಣಾಂಕ dst_pitch)
{
    Uint32 bpp = 2;
    SDL_SCALE_ಹತ್ತಿರದ_ಆರಂಭ
    ಗಾಗಿ (i = 0; i < dst_h; i++) {
        SDL_SCALE_ಹತ್ತಿರದ_ಎತ್ತರ
        ಆಗ (n--) {
            ಸ್ಥಿರಾಂಕ Uint16 *src;
            srcx = bpp * (posx >> 16);
            posx += incx;
            src = (ಸ್ಥಿರಾಂಕ Uint16 *)((ಸ್ಥಿರಾಂಕ Uint8 *)src_h0 + srcx);
            *(Uint16 *)dst = *src;
            dst = (Uint32 *)((Uint8 *)dst + bpp);
        }
        dst = (Uint32 *)((Uint8 *)dst + dst_gap);
    }
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool scale_mat_ಹತ್ತಿರದ_3(ಸ್ಥಿರಾಂಕ Uint32 *src_ptr, ಪೂರ್ಣಾಂಕ src_w, ಪೂರ್ಣಾಂಕ src_h, ಪೂರ್ಣಾಂಕ src_pitch, Uint32 *dst, ಪೂರ್ಣಾಂಕ dst_w, ಪೂರ್ಣಾಂಕ dst_h, ಪೂರ್ಣಾಂಕ dst_pitch)
{
    Uint32 bpp = 3;
    SDL_SCALE_ಹತ್ತಿರದ_ಆರಂಭ
    ಗಾಗಿ (i = 0; i < dst_h; i++) {
        SDL_SCALE_ಹತ್ತಿರದ_ಎತ್ತರ
        ಆಗ (n--) {
            ಸ್ಥಿರಾಂಕ Uint8 *src;
            srcx = bpp * (posx >> 16);
            posx += incx;
            src = (ಸ್ಥಿರಾಂಕ Uint8 *)src_h0 + srcx;
            ((Uint8 *)dst)[0] = src[0];
            ((Uint8 *)dst)[1] = src[1];
            ((Uint8 *)dst)[2] = src[2];
            dst = (Uint32 *)((Uint8 *)dst + bpp);
        }
        dst = (Uint32 *)((Uint8 *)dst + dst_gap);
    }
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool scale_mat_ಹತ್ತಿರದ_4(ಸ್ಥಿರಾಂಕ Uint32 *src_ptr, ಪೂರ್ಣಾಂಕ src_w, ಪೂರ್ಣಾಂಕ src_h, ಪೂರ್ಣಾಂಕ src_pitch, Uint32 *dst, ಪೂರ್ಣಾಂಕ dst_w, ಪೂರ್ಣಾಂಕ dst_h, ಪೂರ್ಣಾಂಕ dst_pitch)
{
    Uint32 bpp = 4;
    SDL_SCALE_ಹತ್ತಿರದ_ಆರಂಭ
    ಗಾಗಿ (i = 0; i < dst_h; i++) {
        SDL_SCALE_ಹತ್ತಿರದ_ಎತ್ತರ
        ಆಗ (n--) {
            ಸ್ಥಿರಾಂಕ Uint32 *src;
            srcx = bpp * (posx >> 16);
            posx += incx;
            src = (ಸ್ಥಿರಾಂಕ Uint32 *)((ಸ್ಥಿರಾಂಕ Uint8 *)src_h0 + srcx);
            *dst = *src;
            dst = (Uint32 *)((Uint8 *)dst + bpp);
        }
        dst = (Uint32 *)((Uint8 *)dst + dst_gap);
    }
    ಹಿಂತಿರುಗಿ true;
}

bool SDL_Stretch_Surface_Unchecked_ಹತ್ತಿರದ(SDL_Surface *s, ಸ್ಥಿರಾಂಕ SDL_Rect *srcrect, SDL_Surface *d, ಸ್ಥಿರಾಂಕ SDL_Rect *dstrect)
{
    ಪೂರ್ಣಾಂಕ src_w = srcrect->w;
    ಪೂರ್ಣಾಂಕ src_h = srcrect->h;
    ಪೂರ್ಣಾಂಕ dst_w = dstrect->w;
    ಪೂರ್ಣಾಂಕ dst_h = dstrect->h;
    ಪೂರ್ಣಾಂಕ src_pitch = s->pitch;
    ಪೂರ್ಣಾಂಕ dst_pitch = d->pitch;
    ಪೂರ್ಣಾಂಕ bpp = SDL_BYTESPERPIXEL(d->format);

    Uint32 *src = (Uint32 *)((Uint8 *)s->pixels + srcrect->x * bpp + srcrect->y * src_pitch);
    Uint32 *dst = (Uint32 *)((Uint8 *)d->pixels + dstrect->x * bpp + dstrect->y * dst_pitch);

    ಆದರೆ (bpp == 4) {
        ಹಿಂತಿರುಗಿ scale_mat_ಹತ್ತಿರದ_4(src, src_w, src_h, src_pitch, dst, dst_w, dst_h, dst_pitch);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (bpp == 3) {
        ಹಿಂತಿರುಗಿ scale_mat_ಹತ್ತಿರದ_3(src, src_w, src_h, src_pitch, dst, dst_w, dst_h, dst_pitch);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (bpp == 2) {
        ಹಿಂತಿರುಗಿ scale_mat_ಹತ್ತಿರದ_2(src, src_w, src_h, src_pitch, dst, dst_w, dst_h, dst_pitch);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ scale_mat_ಹತ್ತಿರದ_1(src, src_w, src_h, src_pitch, dst, dst_w, dst_h, dst_pitch);
    }
}
