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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_surface_c.h"

ਸਥਿਰ bool SDL_Stretch_Surface_Unchecked_ਸਭ_ਤੋਂ_ਨੇੜੇ(SDL_Surface *src, ਅਚਲ SDL_Rect *srcrect, SDL_Surface *dst, ਅਚਲ SDL_Rect *dstrect);
ਸਥਿਰ bool SDL_Stretch_Surface_Unchecked_ਰੇਖਿਕ(SDL_Surface *src, ਅਚਲ SDL_Rect *srcrect, SDL_Surface *dst, ਅਚਲ SDL_Rect *dstrect);

bool SDL_StretchSurface(SDL_Surface *src, ਅਚਲ SDL_Rect *srcrect, SDL_Surface *dst, ਅਚਲ SDL_Rect *dstrect, SDL_Scale_ਬਹੁਲਕ scale_ਬਹੁਲਕ)
{
    bool ਨਤੀਜਾ;
    ਪੂਰਨ src_locked;
    ਪੂਰਨ dst_locked;
    SDL_Rect ਭਰਿਆ_src;
    SDL_Rect ਭਰਿਆ_dst;

    CHECK_PARAM(!src) {
        ਵਾਪਸ SDL_InvalidParamError("src");
    }
    CHECK_PARAM(!dst) {
        ਵਾਪਸ SDL_InvalidParamError("dst");
    }

    ਜੇ (src->format != dst->format) {
        // Slow!
        SDL_Surface *src_tmp = SDL_ConvertSurfaceAndColorspace(src, dst->format, dst->palette, dst->colorspace, dst->props);
        ਜੇ (!src_tmp) {
            ਵਾਪਸ false;
        }
        ਨਤੀਜਾ = SDL_StretchSurface(src_tmp, srcrect, dst, dstrect, scale_ਬਹੁਲਕ);
        SDL_DestroySurface(src_tmp);
        ਵਾਪਸ ਨਤੀਜਾ;
    }

    ਜੇ (SDL_ISPIXELFORMAT_FOURCC(src->format)) {
        // Slow!
        ਜੇ (!dstrect) {
            ਭਰਿਆ_dst.x = 0;
            ਭਰਿਆ_dst.y = 0;
            ਭਰਿਆ_dst.w = dst->w;
            ਭਰਿਆ_dst.h = dst->h;
            dstrect = &ਭਰਿਆ_dst;
        }

        SDL_Surface *src_tmp = SDL_ConvertSurface(src, SDL_PIXELFORMAT_XRGB8888);
        SDL_Surface *dst_tmp = SDL_CreateSurfaceUninitialized(dstrect->w, dstrect->h, SDL_PIXELFORMAT_XRGB8888);
        ਜੇ (src_tmp && dst_tmp) {
            ਨਤੀਜਾ = SDL_StretchSurface(src_tmp, srcrect, dst_tmp, ਨਿਰਾ, scale_ਬਹੁਲਕ);
            ਜੇ (ਨਤੀਜਾ) {
                ਨਤੀਜਾ = SDL_ConvertPixelsAndColorspace(dstrect->w, dstrect->h,
                            dst_tmp->format, SDL_COLORSPACE_SRGB, 0,
                            dst_tmp->pixels, dst_tmp->pitch,
                            dst->format, dst->colorspace, SDL_GetSurfaceProperties(dst),
                            (Uint8 *)dst->pixels + dstrect->y * dst->pitch + dstrect->x * SDL_BYTESPERPIXEL(dst->format), dst->pitch);
            }
        } ਨਹੀਂਤਾਂ {
            ਨਤੀਜਾ = false;
        }
        SDL_DestroySurface(src_tmp);
        SDL_DestroySurface(dst_tmp);
        ਵਾਪਸ ਨਤੀਜਾ;
    }

    ਚੋਣ (scale_ਬਹੁਲਕ) {
    ਹਾਲਤ SDL_SCALEMODE_ਸਭ_ਤੋਂ_ਨੇੜੇ:
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SCALEMODE_ਰੇਖਿਕ:
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SCALEMODE_PIXELART:
        scale_ਬਹੁਲਕ = SDL_SCALEMODE_ਸਭ_ਤੋਂ_ਨੇੜੇ;
        ਰੋਕੋ;
    ਮੂਲ:
        ਵਾਪਸ SDL_InvalidParamError("scaleMode");
    }

    ਜੇ (scale_ਬਹੁਲਕ == SDL_SCALEMODE_ਰੇਖਿਕ) {
        ਜੇ (SDL_BYTESPERPIXEL(src->format) != 4 || src->format == SDL_PIXELFORMAT_ARGB2101010) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("Wrong format");
        }
    }

    // Verify the blit rectangles
    ਜੇ (srcrect) {
        ਜੇ ((srcrect->x < 0) || (srcrect->y < 0) ||
            ((srcrect->x + srcrect->w) > src->w) ||
            ((srcrect->y + srcrect->h) > src->h)) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("Invalid source blit rectangle");
        }
    } ਨਹੀਂਤਾਂ {
        ਭਰਿਆ_src.x = 0;
        ਭਰਿਆ_src.y = 0;
        ਭਰਿਆ_src.w = src->w;
        ਭਰਿਆ_src.h = src->h;
        srcrect = &ਭਰਿਆ_src;
    }
    ਜੇ (dstrect) {
        ਜੇ ((dstrect->x < 0) || (dstrect->y < 0) ||
            ((dstrect->x + dstrect->w) > dst->w) ||
            ((dstrect->y + dstrect->h) > dst->h)) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("Invalid destination blit rectangle");
        }
    } ਨਹੀਂਤਾਂ {
        ਭਰਿਆ_dst.x = 0;
        ਭਰਿਆ_dst.y = 0;
        ਭਰਿਆ_dst.w = dst->w;
        ਭਰਿਆ_dst.h = dst->h;
        dstrect = &ਭਰਿਆ_dst;
    }

    ਜੇ (dstrect->w <= 0 || dstrect->h <= 0) {
        ਵਾਪਸ true;
    }

    ਜੇ (srcrect->w > SDL_MAX_UINT16 || srcrect->h > SDL_MAX_UINT16 ||
        dstrect->w > SDL_MAX_UINT16 || dstrect->h > SDL_MAX_UINT16) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Size too large for scaling");
    }

    // Lock the destination if it's in hardware
    dst_locked = 0;
    ਜੇ (SDL_MUSTLOCK(dst)) {
        ਜੇ (!SDL_ਤਾਲਾ_Surface(dst)) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("Unable to lock destination surface");
        }
        dst_locked = 1;
    }
    // Lock the source if it's in hardware
    src_locked = 0;
    ਜੇ (SDL_MUSTLOCK(src)) {
        ਜੇ (!SDL_ਤਾਲਾ_Surface(src)) {
            ਜੇ (dst_locked) {
                SDL_UnlockSurface(dst);
            }
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("Unable to lock source surface");
        }
        src_locked = 1;
    }

    ਜੇ (scale_ਬਹੁਲਕ == SDL_SCALEMODE_ਸਭ_ਤੋਂ_ਨੇੜੇ) {
        ਨਤੀਜਾ = SDL_Stretch_Surface_Unchecked_ਸਭ_ਤੋਂ_ਨੇੜੇ(src, srcrect, dst, dstrect);
    } ਨਹੀਂਤਾਂ {
        ਨਤੀਜਾ = SDL_Stretch_Surface_Unchecked_ਰੇਖਿਕ(src, srcrect, dst, dstrect);
    }

    // We need to unlock the surfaces if they're locked
    ਜੇ (dst_locked) {
        SDL_UnlockSurface(dst);
    }
    ਜੇ (src_locked) {
        SDL_UnlockSurface(src);
    }

    ਵਾਪਸ ਨਤੀਜਾ;
}

/* bilinear interpolation precision must be < 8
   Because with SSE: add-multiply: _mm_madd_epi16 works with signed int
   so pixels 0xb1...... are negatives and false the result
   same in NEON probably */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PRECISION 7

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FIXED_ਬਿੰਦੂ(i) ((Uint32)(i) << 16)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SRC_ਸੂਚਕਾਂਕ(fp)  ((Uint32)(fp) >> 16)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INTEGER(fp)    ((Uint32)(fp) >> PRECISION)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FRAC(fp)       ((Uint32)((fp) >> (16 - PRECISION)) & ((1 << PRECISION) - 1))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FRAC_ZERO      0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FRAC_ONE       (1 << PRECISION)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FP_ONE         FIXED_ਬਿੰਦੂ(1)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BILINEAR_ਸ਼ੁਰੂ                                                              \
    ਪੂਰਨ i;                                                                            \
    Sint64 fp_ਜੋੜ_h;                                                                  \
    ਪੂਰਨ fp_ਕਦਮ_h, ਖੱਬਾ_pad_h, ਸੱਜਾ_pad_h;                                           \
    Sint64 fp_ਜੋੜ_w;                                                                  \
    ਪੂਰਨ fp_ਕਦਮ_w, ਖੱਬਾ_pad_w, ਸੱਜਾ_pad_w;                                           \
    Sint64 fp_ਜੋੜ_w_init;                                                             \
    ਪੂਰਨ ਖੱਬਾ_pad_w_init, ਸੱਜਾ_pad_w_init, dst_gap, ਵਿਚਕਾਰ_init;                      \
    get_scaler_datas(src_h, dst_h, &fp_ਜੋੜ_h, &fp_ਕਦਮ_h, &ਖੱਬਾ_pad_h, &ਸੱਜਾ_pad_h); \
    get_scaler_datas(src_w, dst_w, &fp_ਜੋੜ_w, &fp_ਕਦਮ_w, &ਖੱਬਾ_pad_w, &ਸੱਜਾ_pad_w); \
    fp_ਜੋੜ_w_init = fp_ਜੋੜ_w + ਖੱਬਾ_pad_w * fp_ਕਦਮ_w;                                \
    ਖੱਬਾ_pad_w_init = ਖੱਬਾ_pad_w;                                                     \
    ਸੱਜਾ_pad_w_init = ਸੱਜਾ_pad_w;                                                   \
    dst_gap = dst_pitch - 4 * dst_w;                                                  \
    ਵਿਚਕਾਰ_init = dst_w - ਖੱਬਾ_pad_w - ਸੱਜਾ_pad_w;

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BILINEAR_ਉਚਾਈ                                              \
    ਪੂਰਨ ਸੂਚਕਾਂਕ_h, frac_h0, frac_h1, ਵਿਚਕਾਰ;                             \
    ਅਚਲ Uint32 *src_h0, *src_h1;                                     \
    ਪੂਰਨ no_padding;                                                    \
    Uint64 incr_h0, incr_h1;                                           \
                                                                       \
    no_padding = !(i < ਖੱਬਾ_pad_h || i > dst_h - 1 - ਸੱਜਾ_pad_h);     \
    ਸੂਚਕਾਂਕ_h = SRC_ਸੂਚਕਾਂਕ(fp_ਜੋੜ_h);                                     \
    frac_h0 = FRAC(fp_ਜੋੜ_h);                                          \
                                                                       \
    ਸੂਚਕਾਂਕ_h = no_padding ? ਸੂਚਕਾਂਕ_h : (i < ਖੱਬਾ_pad_h ? 0 : src_h - 1); \
    frac_h0 = no_padding ? frac_h0 : 0;                                \
    incr_h1 = no_padding ? src_pitch : 0;                              \
    incr_h0 = (Uint64)ਸੂਚਕਾਂਕ_h * src_pitch;                             \
                                                                       \
    src_h0 = (ਅਚਲ Uint32 *)((ਅਚਲ Uint8 *)src + incr_h0);           \
    src_h1 = (ਅਚਲ Uint32 *)((ਅਚਲ Uint8 *)src_h0 + incr_h1);        \
                                                                       \
    fp_ਜੋੜ_h += fp_ਕਦਮ_h;                                             \
                                                                       \
    frac_h1 = FRAC_ONE - frac_h0;                                      \
    fp_ਜੋੜ_w = fp_ਜੋੜ_w_init;                                          \
    ਸੱਜਾ_pad_w = ਸੱਜਾ_pad_w_init;                                    \
    ਖੱਬਾ_pad_w = ਖੱਬਾ_pad_w_init;                                      \
    ਵਿਚਕਾਰ = ਵਿਚਕਾਰ_init;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __clang__
// Remove inlining of this function
// Compiler crash with clang 9.0.8 / android-ndk-r21d
// Compiler crash with clang 11.0.3 / Xcode
// OK with clang 11.0.5 / android-ndk-22
// OK with clang 12.0.0 / Xcode
__attribute__((noinline))
#ਜੇ_ਅੰਤ
ਸਥਿਰ ਖਾਲੀ get_scaler_datas(ਪੂਰਨ src_nb, ਪੂਰਨ dst_nb, Sint64 *fp_ਸ਼ੁਰੂ, ਪੂਰਨ *fp_ਕਦਮ, ਪੂਰਨ *ਖੱਬਾ_pad, ਪੂਰਨ *ਸੱਜਾ_pad)
{

    ਪੂਰਨ ਕਦਮ = FIXED_ਬਿੰਦੂ(src_nb) / (dst_nb); // source step in fixed point
    ਪੂਰਨ x0 = FP_ONE / 2;                       // dst first pixel center at 0.5 in fixed point
    Sint64 fp_ਜੋੜ;
    ਪੂਰਨ i;
#ਜੇ 0
    // scale to source coordinates
    x0 *= src_nb;
    x0 /= dst_nb; // x0 == step / 2
#ਨਹੀਂਤਾਂ
    // Use this code for perfect match with pixman
    Sint64 tmp[2];
    tmp[0] = (Sint64)ਕਦਮ * (x0 >> 16);
    tmp[1] = (Sint64)ਕਦਮ * (x0 & 0xFFFF);
    x0 = (ਪੂਰਨ)(tmp[0] + ((tmp[1] + 0x8000) >> 16)); // x0 == (step + 1) / 2
#ਜੇ_ਅੰਤ
    // -= 0.5, get back the pixel origin, in source coordinates
    x0 -= FP_ONE / 2;

    *fp_ਸ਼ੁਰੂ = x0;
    *fp_ਕਦਮ = ਕਦਮ;
    *ਖੱਬਾ_pad = 0;
    *ਸੱਜਾ_pad = 0;

    fp_ਜੋੜ = x0;
    ਲਈ (i = 0; i < dst_nb; i++) {
        ਜੇ (fp_ਜੋੜ < 0) {
            *ਖੱਬਾ_pad += 1;
        } ਨਹੀਂਤਾਂ {
            ਪੂਰਨ ਸੂਚਕਾਂਕ = SRC_ਸੂਚਕਾਂਕ(fp_ਜੋੜ);
            ਜੇ (ਸੂਚਕਾਂਕ > src_nb - 2) {
                *ਸੱਜਾ_pad += 1;
            }
        }
        fp_ਜੋੜ += ਕਦਮ;
    }
    //    SDL_Log("%d -> %d  x0=%d step=%d left_pad=%d right_pad=%d", src_nb, dst_nb, *fp_start, *fp_step, *left_pad, *right_pad);
}

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ color_t
{
    Uint8 a;
    Uint8 b;
    Uint8 c;
    Uint8 d;
} color_t;

/* Interpolated == x0 + frac * (x1 - x0) == x0 * (1 - frac) + x1 * frac */

ਸਥਿਰ SDL_INLINE ਖਾਲੀ INTERPOL(ਅਚਲ Uint32 *src_x0, ਅਚਲ Uint32 *src_x1, ਪੂਰਨ frac0, ਪੂਰਨ frac1, Uint32 *dst)
{
    ਅਚਲ color_t *c0 = (ਅਚਲ color_t *)src_x0;
    ਅਚਲ color_t *c1 = (ਅਚਲ color_t *)src_x1;
    color_t *cx = (color_t *)dst;
#ਜੇ 0
    cx->a = c0->a + INTEGER(frac0 * (c1->a - c0->a));
    cx->b = c0->b + INTEGER(frac0 * (c1->b - c0->b));
    cx->c = c0->c + INTEGER(frac0 * (c1->c - c0->c));
    cx->d = c0->d + INTEGER(frac0 * (c1->d - c0->d));
#ਨਹੀਂਤਾਂ
    cx->a = (Uint8)INTEGER(frac1 * c0->a + frac0 * c1->a);
    cx->b = (Uint8)INTEGER(frac1 * c0->b + frac0 * c1->b);
    cx->c = (Uint8)INTEGER(frac1 * c0->c + frac0 * c1->c);
    cx->d = (Uint8)INTEGER(frac1 * c0->d + frac0 * c1->d);
#ਜੇ_ਅੰਤ
}

ਸਥਿਰ SDL_INLINE ਖਾਲੀ INTERPOL_BILINEAR(ਅਚਲ Uint32 *s0, ਅਚਲ Uint32 *s1, ਪੂਰਨ frac_w0, ਪੂਰਨ frac_h0, ਪੂਰਨ frac_h1, Uint32 *dst)
{
    Uint32 tmp[2];
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ frac_w1 = FRAC_ONE - frac_w0;

    // Vertical first, store to 'tmp'
    INTERPOL(s0, s1, frac_h0, frac_h1, tmp);
    INTERPOL(s0 + 1, s1 + 1, frac_h0, frac_h1, tmp + 1);

    // Horizontal, store to 'dst'
    INTERPOL(tmp, tmp + 1, frac_w0, frac_w1, dst);
}

ਸਥਿਰ bool scale_mat(ਅਚਲ Uint32 *src, ਪੂਰਨ src_w, ਪੂਰਨ src_h, ਪੂਰਨ src_pitch, Uint32 *dst, ਪੂਰਨ dst_w, ਪੂਰਨ dst_h, ਪੂਰਨ dst_pitch)
{
    BILINEAR_ਸ਼ੁਰੂ

    ਲਈ (i = 0; i < dst_h; i++) {

        BILINEAR_ਉਚਾਈ

        ਜਦੋਂ (ਖੱਬਾ_pad_w--) {
            INTERPOL_BILINEAR(src_h0, src_h1, FRAC_ZERO, frac_h0, frac_h1, dst);
            dst += 1;
        }

        ਜਦੋਂ (ਵਿਚਕਾਰ--) {
            ਅਚਲ Uint32 *s_00_01;
            ਅਚਲ Uint32 *s_10_11;
            ਪੂਰਨ ਸੂਚਕਾਂਕ_w = 4 * SRC_ਸੂਚਕਾਂਕ(fp_ਜੋੜ_w);
            ਪੂਰਨ frac_w = FRAC(fp_ਜੋੜ_w);
            fp_ਜੋੜ_w += fp_ਕਦਮ_w;

            /*
                        x00 ... x0_ ..... x01
                        .       .         .
                        .       x         .
                        .       .         .
                        .       .         .
                        x10 ... x1_ ..... x11
            */
            s_00_01 = (ਅਚਲ Uint32 *)((ਅਚਲ Uint8 *)src_h0 + ਸੂਚਕਾਂਕ_w);
            s_10_11 = (ਅਚਲ Uint32 *)((ਅਚਲ Uint8 *)src_h1 + ਸੂਚਕਾਂਕ_w);

            INTERPOL_BILINEAR(s_00_01, s_10_11, frac_w, frac_h0, frac_h1, dst);

            dst += 1;
        }

        ਜਦੋਂ (ਸੱਜਾ_pad_w--) {
            ਪੂਰਨ ਸੂਚਕਾਂਕ_w = 4 * (src_w - 2);
            ਅਚਲ Uint32 *s_00_01 = (ਅਚਲ Uint32 *)((ਅਚਲ Uint8 *)src_h0 + ਸੂਚਕਾਂਕ_w);
            ਅਚਲ Uint32 *s_10_11 = (ਅਚਲ Uint32 *)((ਅਚਲ Uint8 *)src_h1 + ਸੂਚਕਾਂਕ_w);
            INTERPOL_BILINEAR(s_00_01, s_10_11, FRAC_ONE, frac_h0, frac_h1, dst);
            dst += 1;
        }
        dst = (Uint32 *)((Uint8 *)dst + dst_gap);
    }
    ਵਾਪਸ true;
}

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_SSE2_INTRINSICS

ਸਥਿਰ SDL_INLINE ਪੂਰਨ hasSSE2(ਖਾਲੀ)
{
    ਸਥਿਰ ਪੂਰਨ val = -1;
    ਜੇ (val != -1) {
        ਵਾਪਸ val;
    }
    val = SDL_HasSSE2();
    ਵਾਪਸ val;
}

ਸਥਿਰ SDL_INLINE ਖਾਲੀ SDL_TARGETING("sse2") INTERPOL_BILINEAR_SSE(ਅਚਲ Uint32 *s0, ਅਚਲ Uint32 *s1, ਪੂਰਨ frac_w, __m128i v_frac_h0, __m128i v_frac_h1, Uint32 *dst, __m128i zero)
{
    __m128i x_00_01, x_10_11; /* Pixels in 4*uint8 in row */
    __m128i v_frac_w0, k0, l0, d0, e0;

    ਪੂਰਨ f, f2;
    f = frac_w;
    f2 = FRAC_ONE - frac_w;
    v_frac_w0 = mm_ਸੈੱਟ_epi16((ਛੋਟਾ)f, (ਛੋਟਾ)f2, (ਛੋਟਾ)f, (ਛੋਟਾ)f2, (ਛੋਟਾ)f, (ਛੋਟਾ)f2, (ਛੋਟਾ)f, (ਛੋਟਾ)f2);

    x_00_01 = _mm_loadl_epi64((ਅਚਲ __m128i *)s0); // Load x00 and x01
    x_10_11 = _mm_loadl_epi64((ਅਚਲ __m128i *)s1);

    /* Interpolated == x0 + frac * (x1 - x0) == x0 * (1 - frac) + x1 * frac */

    // Interpolation vertical
    k0 = _mm_mullo_epi16(_mm_unpacklo_epi8(x_00_01, zero), v_frac_h1);
    l0 = _mm_mullo_epi16(_mm_unpacklo_epi8(x_10_11, zero), v_frac_h0);
    k0 = mm_ਜੋੜੋ_epi16(k0, l0);

    // For perfect match, clear the factionnal part eventually.
    /*
    k0 = _mm_srli_epi16(k0, PRECISION);
    k0 = _mm_slli_epi16(k0, PRECISION);
    */

    // Interpolation horizontal
    l0 = _mm_unpacklo_epi64(/*ਅਣਵਰਤਿਆ*/ l0, k0);
    k0 = _mm_madd_epi16(_mm_unpackhi_epi16(l0, k0), v_frac_w0);

    // Store 1 pixel
    d0 = _mm_srli_epi32(k0, PRECISION * 2);
    e0 = _mm_packs_epi32(d0, d0);
    e0 = _mm_packus_epi16(e0, e0);
    *dst = _mm_cvtsi128_si32(e0);
}

ਸਥਿਰ bool SDL_TARGETING("sse2") scale_mat_SSE(ਅਚਲ Uint32 *src, ਪੂਰਨ src_w, ਪੂਰਨ src_h, ਪੂਰਨ src_pitch, Uint32 *dst, ਪੂਰਨ dst_w, ਪੂਰਨ dst_h, ਪੂਰਨ dst_pitch)
{
    BILINEAR_ਸ਼ੁਰੂ

    ਲਈ (i = 0; i < dst_h; i++) {
        ਪੂਰਨ nb_block2;
        __m128i v_frac_h0;
        __m128i v_frac_h1;
        __m128i zero;

        BILINEAR_ਉਚਾਈ

        nb_block2 = ਵਿਚਕਾਰ / 2;

        v_frac_h0 = mm_ਸੈੱਟ_epi16((ਛੋਟਾ)frac_h0, (ਛੋਟਾ)frac_h0, (ਛੋਟਾ)frac_h0, (ਛੋਟਾ)frac_h0, (ਛੋਟਾ)frac_h0, (ਛੋਟਾ)frac_h0, (ਛੋਟਾ)frac_h0, (ਛੋਟਾ)frac_h0);
        v_frac_h1 = mm_ਸੈੱਟ_epi16((ਛੋਟਾ)frac_h1, (ਛੋਟਾ)frac_h1, (ਛੋਟਾ)frac_h1, (ਛੋਟਾ)frac_h1, (ਛੋਟਾ)frac_h1, (ਛੋਟਾ)frac_h1, (ਛੋਟਾ)frac_h1, (ਛੋਟਾ)frac_h1);
        zero = _mm_setzero_si128();

        ਜਦੋਂ (ਖੱਬਾ_pad_w--) {
            INTERPOL_BILINEAR_SSE(src_h0, src_h1, FRAC_ZERO, v_frac_h0, v_frac_h1, dst, zero);
            dst += 1;
        }

        ਜਦੋਂ (nb_block2--) {
            ਪੂਰਨ ਸੂਚਕਾਂਕ_w_0, frac_w_0;
            ਪੂਰਨ ਸੂਚਕਾਂਕ_w_1, frac_w_1;

            ਅਚਲ Uint32 *s_00_01, *s_02_03, *s_10_11, *s_12_13;

            __m128i x_00_01, x_10_11, x_02_03, x_12_13; /* Pixels in 4*uint8 in row */
            __m128i v_frac_w0, k0, l0, d0, e0;
            __m128i v_frac_w1, k1, l1, d1, e1;

            ਪੂਰਨ f, f2;
            ਸੂਚਕਾਂਕ_w_0 = 4 * SRC_ਸੂਚਕਾਂਕ(fp_ਜੋੜ_w);
            frac_w_0 = FRAC(fp_ਜੋੜ_w);
            fp_ਜੋੜ_w += fp_ਕਦਮ_w;
            ਸੂਚਕਾਂਕ_w_1 = 4 * SRC_ਸੂਚਕਾਂਕ(fp_ਜੋੜ_w);
            frac_w_1 = FRAC(fp_ਜੋੜ_w);
            fp_ਜੋੜ_w += fp_ਕਦਮ_w;
            /*
                        x00............ x01   x02...........x03
                        .      .         .     .       .     .
                        j0     f0        j1    j2      f1    j3
                        .      .         .     .       .     .
                        .      .         .     .       .     .
                        .      .         .     .       .     .
                        x10............ x11   x12...........x13
             */
            s_00_01 = (ਅਚਲ Uint32 *)((ਅਚਲ Uint8 *)src_h0 + ਸੂਚਕਾਂਕ_w_0);
            s_02_03 = (ਅਚਲ Uint32 *)((ਅਚਲ Uint8 *)src_h0 + ਸੂਚਕਾਂਕ_w_1);
            s_10_11 = (ਅਚਲ Uint32 *)((ਅਚਲ Uint8 *)src_h1 + ਸੂਚਕਾਂਕ_w_0);
            s_12_13 = (ਅਚਲ Uint32 *)((ਅਚਲ Uint8 *)src_h1 + ਸੂਚਕਾਂਕ_w_1);

            f = frac_w_0;
            f2 = FRAC_ONE - frac_w_0;
            v_frac_w0 = mm_ਸੈੱਟ_epi16((ਛੋਟਾ)f, (ਛੋਟਾ)f2, (ਛੋਟਾ)f, (ਛੋਟਾ)f2, (ਛੋਟਾ)f, (ਛੋਟਾ)f2, (ਛੋਟਾ)f, (ਛੋਟਾ)f2);

            f = frac_w_1;
            f2 = FRAC_ONE - frac_w_1;
            v_frac_w1 = mm_ਸੈੱਟ_epi16((ਛੋਟਾ)f, (ਛੋਟਾ)f2, (ਛੋਟਾ)f, (ਛੋਟਾ)f2, (ਛੋਟਾ)f, (ਛੋਟਾ)f2, (ਛੋਟਾ)f, (ਛੋਟਾ)f2);

            x_00_01 = _mm_loadl_epi64((ਅਚਲ __m128i *)s_00_01); // Load x00 and x01
            x_02_03 = _mm_loadl_epi64((ਅਚਲ __m128i *)s_02_03);
            x_10_11 = _mm_loadl_epi64((ਅਚਲ __m128i *)s_10_11);
            x_12_13 = _mm_loadl_epi64((ਅਚਲ __m128i *)s_12_13);

            // Interpolation vertical
            k0 = _mm_mullo_epi16(_mm_unpacklo_epi8(x_00_01, zero), v_frac_h1);
            l0 = _mm_mullo_epi16(_mm_unpacklo_epi8(x_10_11, zero), v_frac_h0);
            k0 = mm_ਜੋੜੋ_epi16(k0, l0);
            k1 = _mm_mullo_epi16(_mm_unpacklo_epi8(x_02_03, zero), v_frac_h1);
            l1 = _mm_mullo_epi16(_mm_unpacklo_epi8(x_12_13, zero), v_frac_h0);
            k1 = mm_ਜੋੜੋ_epi16(k1, l1);

            // Interpolation horizontal
            l0 = _mm_unpacklo_epi64(/*ਅਣਵਰਤਿਆ*/ l0, k0);
            k0 = _mm_madd_epi16(_mm_unpackhi_epi16(l0, k0), v_frac_w0);
            l1 = _mm_unpacklo_epi64(/*ਅਣਵਰਤਿਆ*/ l1, k1);
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
        ਜੇ (ਵਿਚਕਾਰ & 0x1) {
            ਅਚਲ Uint32 *s_00_01;
            ਅਚਲ Uint32 *s_10_11;
            ਪੂਰਨ ਸੂਚਕਾਂਕ_w = 4 * SRC_ਸੂਚਕਾਂਕ(fp_ਜੋੜ_w);
            ਪੂਰਨ frac_w = FRAC(fp_ਜੋੜ_w);
            fp_ਜੋੜ_w += fp_ਕਦਮ_w;
            s_00_01 = (ਅਚਲ Uint32 *)((ਅਚਲ Uint8 *)src_h0 + ਸੂਚਕਾਂਕ_w);
            s_10_11 = (ਅਚਲ Uint32 *)((ਅਚਲ Uint8 *)src_h1 + ਸੂਚਕਾਂਕ_w);
            INTERPOL_BILINEAR_SSE(s_00_01, s_10_11, frac_w, v_frac_h0, v_frac_h1, dst, zero);
            dst += 1;
        }

        ਜਦੋਂ (ਸੱਜਾ_pad_w--) {
            ਪੂਰਨ ਸੂਚਕਾਂਕ_w = 4 * (src_w - 2);
            ਅਚਲ Uint32 *s_00_01 = (ਅਚਲ Uint32 *)((ਅਚਲ Uint8 *)src_h0 + ਸੂਚਕਾਂਕ_w);
            ਅਚਲ Uint32 *s_10_11 = (ਅਚਲ Uint32 *)((ਅਚਲ Uint8 *)src_h1 + ਸੂਚਕਾਂਕ_w);
            INTERPOL_BILINEAR_SSE(s_00_01, s_10_11, FRAC_ONE, v_frac_h0, v_frac_h1, dst, zero);
            dst += 1;
        }
        dst = (Uint32 *)((Uint8 *)dst + dst_gap);
    }
    ਵਾਪਸ true;
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_NEON_INTRINSICS

ਸਥਿਰ SDL_INLINE ਪੂਰਨ hasNEON(ਖਾਲੀ)
{
    ਸਥਿਰ ਪੂਰਨ val = -1;
    ਜੇ (val != -1) {
        ਵਾਪਸ val;
    }
    val = SDL_HasNEON();
    ਵਾਪਸ val;
}

ਸਥਿਰ SDL_INLINE ਖਾਲੀ INTERPOL_BILINEAR_NEON(ਅਚਲ Uint32 *s0, ਅਚਲ Uint32 *s1, ਪੂਰਨ frac_w, uint8x8_t v_frac_h0, uint8x8_t v_frac_h1, Uint32 *dst)
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
    l0 = vshll_n_u16(vget_ਨੀਵਾਂ_u16(k0), PRECISION);
    l0 = vmlsl_n_u16(l0, vget_ਨੀਵਾਂ_u16(k0), frac_w);
    l0 = vmlal_n_u16(l0, vget_ਉੱਚਾ_u16(k0), frac_w);

    // Shift and narrow
    d0 = vcombine_u16(
        /* uint16x4_t */ vshrn_n_u32(l0, 2 * PRECISION),
        /* uint16x4_t */ vshrn_n_u32(l0, 2 * PRECISION));

    // Narrow again
    e0 = vmovn_u16(d0);

    // Store 1 pixel
    *dst = vget_lane_u32(vreinterpret_u32_u8(e0), 0);
}

ਸਥਿਰ bool scale_mat_NEON(ਅਚਲ Uint32 *src, ਪੂਰਨ src_w, ਪੂਰਨ src_h, ਪੂਰਨ src_pitch, Uint32 *dst, ਪੂਰਨ dst_w, ਪੂਰਨ dst_h, ਪੂਰਨ dst_pitch)
{
    BILINEAR_ਸ਼ੁਰੂ

    ਲਈ (i = 0; i < dst_h; i++) {
        ਪੂਰਨ nb_block4;
        uint8x8_t v_frac_h0, v_frac_h1;

        BILINEAR_ਉਚਾਈ

        nb_block4 = ਵਿਚਕਾਰ / 4;

        v_frac_h0 = vmov_n_u8(frac_h0);
        v_frac_h1 = vmov_n_u8(frac_h1);

        ਜਦੋਂ (ਖੱਬਾ_pad_w--) {
            INTERPOL_BILINEAR_NEON(src_h0, src_h1, FRAC_ZERO, v_frac_h0, v_frac_h1, dst);
            dst += 1;
        }

        ਜਦੋਂ (nb_block4--) {
            ਪੂਰਨ ਸੂਚਕਾਂਕ_w_0, frac_w_0;
            ਪੂਰਨ ਸੂਚਕਾਂਕ_w_1, frac_w_1;
            ਪੂਰਨ ਸੂਚਕਾਂਕ_w_2, frac_w_2;
            ਪੂਰਨ ਸੂਚਕਾਂਕ_w_3, frac_w_3;

            ਅਚਲ Uint32 *s_00_01, *s_02_03, *s_04_05, *s_06_07;
            ਅਚਲ Uint32 *s_10_11, *s_12_13, *s_14_15, *s_16_17;

            uint8x8_t x_00_01, x_10_11, x_02_03, x_12_13; /* Pixels in 4*uint8 in row */
            uint8x8_t x_04_05, x_14_15, x_06_07, x_16_17;

            uint16x8_t k0, k1, k2, k3;
            uint32x4_t l0, l1, l2, l3;
            uint16x8_t d0, d1;
            uint8x8_t e0, e1;
            uint32x4_t f0;

            ਸੂਚਕਾਂਕ_w_0 = 4 * SRC_ਸੂਚਕਾਂਕ(fp_ਜੋੜ_w);
            frac_w_0 = FRAC(fp_ਜੋੜ_w);
            fp_ਜੋੜ_w += fp_ਕਦਮ_w;
            ਸੂਚਕਾਂਕ_w_1 = 4 * SRC_ਸੂਚਕਾਂਕ(fp_ਜੋੜ_w);
            frac_w_1 = FRAC(fp_ਜੋੜ_w);
            fp_ਜੋੜ_w += fp_ਕਦਮ_w;
            ਸੂਚਕਾਂਕ_w_2 = 4 * SRC_ਸੂਚਕਾਂਕ(fp_ਜੋੜ_w);
            frac_w_2 = FRAC(fp_ਜੋੜ_w);
            fp_ਜੋੜ_w += fp_ਕਦਮ_w;
            ਸੂਚਕਾਂਕ_w_3 = 4 * SRC_ਸੂਚਕਾਂਕ(fp_ਜੋੜ_w);
            frac_w_3 = FRAC(fp_ਜੋੜ_w);
            fp_ਜੋੜ_w += fp_ਕਦਮ_w;

            s_00_01 = (ਅਚਲ Uint32 *)((ਅਚਲ Uint8 *)src_h0 + ਸੂਚਕਾਂਕ_w_0);
            s_02_03 = (ਅਚਲ Uint32 *)((ਅਚਲ Uint8 *)src_h0 + ਸੂਚਕਾਂਕ_w_1);
            s_04_05 = (ਅਚਲ Uint32 *)((ਅਚਲ Uint8 *)src_h0 + ਸੂਚਕਾਂਕ_w_2);
            s_06_07 = (ਅਚਲ Uint32 *)((ਅਚਲ Uint8 *)src_h0 + ਸੂਚਕਾਂਕ_w_3);
            s_10_11 = (ਅਚਲ Uint32 *)((ਅਚਲ Uint8 *)src_h1 + ਸੂਚਕਾਂਕ_w_0);
            s_12_13 = (ਅਚਲ Uint32 *)((ਅਚਲ Uint8 *)src_h1 + ਸੂਚਕਾਂਕ_w_1);
            s_14_15 = (ਅਚਲ Uint32 *)((ਅਚਲ Uint8 *)src_h1 + ਸੂਚਕਾਂਕ_w_2);
            s_16_17 = (ਅਚਲ Uint32 *)((ਅਚਲ Uint8 *)src_h1 + ਸੂਚਕਾਂਕ_w_3);

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

            l0 = vshll_n_u16(vget_ਨੀਵਾਂ_u16(k0), PRECISION);
            l0 = vmlsl_n_u16(l0, vget_ਨੀਵਾਂ_u16(k0), frac_w_0);
            l0 = vmlal_n_u16(l0, vget_ਉੱਚਾ_u16(k0), frac_w_0);

            l1 = vshll_n_u16(vget_ਨੀਵਾਂ_u16(k1), PRECISION);
            l1 = vmlsl_n_u16(l1, vget_ਨੀਵਾਂ_u16(k1), frac_w_1);
            l1 = vmlal_n_u16(l1, vget_ਉੱਚਾ_u16(k1), frac_w_1);

            l2 = vshll_n_u16(vget_ਨੀਵਾਂ_u16(k2), PRECISION);
            l2 = vmlsl_n_u16(l2, vget_ਨੀਵਾਂ_u16(k2), frac_w_2);
            l2 = vmlal_n_u16(l2, vget_ਉੱਚਾ_u16(k2), frac_w_2);

            l3 = vshll_n_u16(vget_ਨੀਵਾਂ_u16(k3), PRECISION);
            l3 = vmlsl_n_u16(l3, vget_ਨੀਵਾਂ_u16(k3), frac_w_3);
            l3 = vmlal_n_u16(l3, vget_ਉੱਚਾ_u16(k3), frac_w_3);

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

        ਜੇ (ਵਿਚਕਾਰ & 0x2) {
            ਪੂਰਨ ਸੂਚਕਾਂਕ_w_0, frac_w_0;
            ਪੂਰਨ ਸੂਚਕਾਂਕ_w_1, frac_w_1;
            ਅਚਲ Uint32 *s_00_01, *s_02_03;
            ਅਚਲ Uint32 *s_10_11, *s_12_13;
            uint8x8_t x_00_01, x_10_11, x_02_03, x_12_13; /* Pixels in 4*uint8 in row */
            uint16x8_t k0, k1;
            uint32x4_t l0, l1;
            uint16x8_t d0;
            uint8x8_t e0;

            ਸੂਚਕਾਂਕ_w_0 = 4 * SRC_ਸੂਚਕਾਂਕ(fp_ਜੋੜ_w);
            frac_w_0 = FRAC(fp_ਜੋੜ_w);
            fp_ਜੋੜ_w += fp_ਕਦਮ_w;
            ਸੂਚਕਾਂਕ_w_1 = 4 * SRC_ਸੂਚਕਾਂਕ(fp_ਜੋੜ_w);
            frac_w_1 = FRAC(fp_ਜੋੜ_w);
            fp_ਜੋੜ_w += fp_ਕਦਮ_w;
            /*
                        x00............ x01   x02...........x03
                        .      .         .     .       .     .
                        j0   dest0       j1    j2    dest1   j3
                        .      .         .     .       .     .
                        .      .         .     .       .     .
                        .      .         .     .       .     .
                        x10............ x11   x12...........x13
            */
            s_00_01 = (ਅਚਲ Uint32 *)((ਅਚਲ Uint8 *)src_h0 + ਸੂਚਕਾਂਕ_w_0);
            s_02_03 = (ਅਚਲ Uint32 *)((ਅਚਲ Uint8 *)src_h0 + ਸੂਚਕਾਂਕ_w_1);
            s_10_11 = (ਅਚਲ Uint32 *)((ਅਚਲ Uint8 *)src_h1 + ਸੂਚਕਾਂਕ_w_0);
            s_12_13 = (ਅਚਲ Uint32 *)((ਅਚਲ Uint8 *)src_h1 + ਸੂਚਕਾਂਕ_w_1);

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

            l0 = vshll_n_u16(vget_ਨੀਵਾਂ_u16(k0), PRECISION);
            l0 = vmlsl_n_u16(l0, vget_ਨੀਵਾਂ_u16(k0), frac_w_0);
            l0 = vmlal_n_u16(l0, vget_ਉੱਚਾ_u16(k0), frac_w_0);

            l1 = vshll_n_u16(vget_ਨੀਵਾਂ_u16(k1), PRECISION);
            l1 = vmlsl_n_u16(l1, vget_ਨੀਵਾਂ_u16(k1), frac_w_1);
            l1 = vmlal_n_u16(l1, vget_ਉੱਚਾ_u16(k1), frac_w_1);

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
        ਜੇ (ਵਿਚਕਾਰ & 0x1) {
            ਪੂਰਨ ਸੂਚਕਾਂਕ_w = 4 * SRC_ਸੂਚਕਾਂਕ(fp_ਜੋੜ_w);
            ਪੂਰਨ frac_w = FRAC(fp_ਜੋੜ_w);
            ਅਚਲ Uint32 *s_00_01 = (ਅਚਲ Uint32 *)((ਅਚਲ Uint8 *)src_h0 + ਸੂਚਕਾਂਕ_w);
            ਅਚਲ Uint32 *s_10_11 = (ਅਚਲ Uint32 *)((ਅਚਲ Uint8 *)src_h1 + ਸੂਚਕਾਂਕ_w);
            INTERPOL_BILINEAR_NEON(s_00_01, s_10_11, frac_w, v_frac_h0, v_frac_h1, dst);
            dst += 1;
        }

        ਜਦੋਂ (ਸੱਜਾ_pad_w--) {
            ਪੂਰਨ ਸੂਚਕਾਂਕ_w = 4 * (src_w - 2);
            ਅਚਲ Uint32 *s_00_01 = (ਅਚਲ Uint32 *)((ਅਚਲ Uint8 *)src_h0 + ਸੂਚਕਾਂਕ_w);
            ਅਚਲ Uint32 *s_10_11 = (ਅਚਲ Uint32 *)((ਅਚਲ Uint8 *)src_h1 + ਸੂਚਕਾਂਕ_w);
            INTERPOL_BILINEAR_NEON(s_00_01, s_10_11, FRAC_ONE, v_frac_h0, v_frac_h1, dst);
            dst += 1;
        }

        dst = (Uint32 *)((Uint8 *)dst + dst_gap);
    }
    ਵਾਪਸ true;
}
#ਜੇ_ਅੰਤ

bool SDL_Stretch_Surface_Unchecked_ਰੇਖਿਕ(SDL_Surface *s, ਅਚਲ SDL_Rect *srcrect, SDL_Surface *d, ਅਚਲ SDL_Rect *dstrect)
{
    bool ਨਤੀਜਾ = false;
    ਪੂਰਨ src_w = srcrect->w;
    ਪੂਰਨ src_h = srcrect->h;
    ਪੂਰਨ dst_w = dstrect->w;
    ਪੂਰਨ dst_h = dstrect->h;
    ਪੂਰਨ src_pitch = s->pitch;
    ਪੂਰਨ dst_pitch = d->pitch;
    Uint32 *src = (Uint32 *)((Uint8 *)s->pixels + srcrect->x * 4 + srcrect->y * src_pitch);
    Uint32 *dst = (Uint32 *)((Uint8 *)d->pixels + dstrect->x * 4 + dstrect->y * dst_pitch);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_NEON_INTRINSICS
    ਜੇ (!ਨਤੀਜਾ && hasNEON()) {
        ਨਤੀਜਾ = scale_mat_NEON(src, src_w, src_h, src_pitch, dst, dst_w, dst_h, dst_pitch);
    }
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_SSE2_INTRINSICS
    ਜੇ (!ਨਤੀਜਾ && hasSSE2()) {
        ਨਤੀਜਾ = scale_mat_SSE(src, src_w, src_h, src_pitch, dst, dst_w, dst_h, dst_pitch);
    }
#ਜੇ_ਅੰਤ

    ਜੇ (!ਨਤੀਜਾ) {
        ਨਤੀਜਾ = scale_mat(src, src_w, src_h, src_pitch, dst, dst_w, dst_h, dst_pitch);
    }

    ਵਾਪਸ ਨਤੀਜਾ;
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_SCALE_ਸਭ_ਤੋਂ_ਨੇੜੇ_ਸ਼ੁਰੂ          \
    ਪੂਰਨ i;                                \
    Uint64 posy, incy;                    \
    Uint64 posx, incx;                    \
    Uint64 srcy, srcx;                    \
    ਪੂਰਨ dst_gap, n;                       \
    ਅਚਲ Uint32 *src_h0;                 \
    incy = ((Uint64)src_h << 16) / dst_h; \
    incx = ((Uint64)src_w << 16) / dst_w; \
    dst_gap = dst_pitch - bpp * dst_w;    \
    posy = incy / 2;

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_SCALE_ਸਭ_ਤੋਂ_ਨੇੜੇ_ਉਚਾਈ                                         \
    srcy = (posy >> 16);                                                  \
    src_h0 = (ਅਚਲ Uint32 *)((ਅਚਲ Uint8 *)src_ptr + srcy * src_pitch); \
    posy += incy;                                                         \
    posx = incx / 2;                                                      \
    n = dst_w;

ਸਥਿਰ bool scale_mat_ਸਭ_ਤੋਂ_ਨੇੜੇ_1(ਅਚਲ Uint32 *src_ptr, ਪੂਰਨ src_w, ਪੂਰਨ src_h, ਪੂਰਨ src_pitch, Uint32 *dst, ਪੂਰਨ dst_w, ਪੂਰਨ dst_h, ਪੂਰਨ dst_pitch)
{
    Uint32 bpp = 1;
    SDL_SCALE_ਸਭ_ਤੋਂ_ਨੇੜੇ_ਸ਼ੁਰੂ
    ਲਈ (i = 0; i < dst_h; i++) {
        SDL_SCALE_ਸਭ_ਤੋਂ_ਨੇੜੇ_ਉਚਾਈ
        ਜਦੋਂ (n--) {
            ਅਚਲ Uint8 *src;
            srcx = bpp * (posx >> 16);
            posx += incx;
            src = (ਅਚਲ Uint8 *)src_h0 + srcx;
            *(Uint8 *)dst = *src;
            dst = (Uint32 *)((Uint8 *)dst + bpp);
        }
        dst = (Uint32 *)((Uint8 *)dst + dst_gap);
    }
    ਵਾਪਸ true;
}

ਸਥਿਰ bool scale_mat_ਸਭ_ਤੋਂ_ਨੇੜੇ_2(ਅਚਲ Uint32 *src_ptr, ਪੂਰਨ src_w, ਪੂਰਨ src_h, ਪੂਰਨ src_pitch, Uint32 *dst, ਪੂਰਨ dst_w, ਪੂਰਨ dst_h, ਪੂਰਨ dst_pitch)
{
    Uint32 bpp = 2;
    SDL_SCALE_ਸਭ_ਤੋਂ_ਨੇੜੇ_ਸ਼ੁਰੂ
    ਲਈ (i = 0; i < dst_h; i++) {
        SDL_SCALE_ਸਭ_ਤੋਂ_ਨੇੜੇ_ਉਚਾਈ
        ਜਦੋਂ (n--) {
            ਅਚਲ Uint16 *src;
            srcx = bpp * (posx >> 16);
            posx += incx;
            src = (ਅਚਲ Uint16 *)((ਅਚਲ Uint8 *)src_h0 + srcx);
            *(Uint16 *)dst = *src;
            dst = (Uint32 *)((Uint8 *)dst + bpp);
        }
        dst = (Uint32 *)((Uint8 *)dst + dst_gap);
    }
    ਵਾਪਸ true;
}

ਸਥਿਰ bool scale_mat_ਸਭ_ਤੋਂ_ਨੇੜੇ_3(ਅਚਲ Uint32 *src_ptr, ਪੂਰਨ src_w, ਪੂਰਨ src_h, ਪੂਰਨ src_pitch, Uint32 *dst, ਪੂਰਨ dst_w, ਪੂਰਨ dst_h, ਪੂਰਨ dst_pitch)
{
    Uint32 bpp = 3;
    SDL_SCALE_ਸਭ_ਤੋਂ_ਨੇੜੇ_ਸ਼ੁਰੂ
    ਲਈ (i = 0; i < dst_h; i++) {
        SDL_SCALE_ਸਭ_ਤੋਂ_ਨੇੜੇ_ਉਚਾਈ
        ਜਦੋਂ (n--) {
            ਅਚਲ Uint8 *src;
            srcx = bpp * (posx >> 16);
            posx += incx;
            src = (ਅਚਲ Uint8 *)src_h0 + srcx;
            ((Uint8 *)dst)[0] = src[0];
            ((Uint8 *)dst)[1] = src[1];
            ((Uint8 *)dst)[2] = src[2];
            dst = (Uint32 *)((Uint8 *)dst + bpp);
        }
        dst = (Uint32 *)((Uint8 *)dst + dst_gap);
    }
    ਵਾਪਸ true;
}

ਸਥਿਰ bool scale_mat_ਸਭ_ਤੋਂ_ਨੇੜੇ_4(ਅਚਲ Uint32 *src_ptr, ਪੂਰਨ src_w, ਪੂਰਨ src_h, ਪੂਰਨ src_pitch, Uint32 *dst, ਪੂਰਨ dst_w, ਪੂਰਨ dst_h, ਪੂਰਨ dst_pitch)
{
    Uint32 bpp = 4;
    SDL_SCALE_ਸਭ_ਤੋਂ_ਨੇੜੇ_ਸ਼ੁਰੂ
    ਲਈ (i = 0; i < dst_h; i++) {
        SDL_SCALE_ਸਭ_ਤੋਂ_ਨੇੜੇ_ਉਚਾਈ
        ਜਦੋਂ (n--) {
            ਅਚਲ Uint32 *src;
            srcx = bpp * (posx >> 16);
            posx += incx;
            src = (ਅਚਲ Uint32 *)((ਅਚਲ Uint8 *)src_h0 + srcx);
            *dst = *src;
            dst = (Uint32 *)((Uint8 *)dst + bpp);
        }
        dst = (Uint32 *)((Uint8 *)dst + dst_gap);
    }
    ਵਾਪਸ true;
}

bool SDL_Stretch_Surface_Unchecked_ਸਭ_ਤੋਂ_ਨੇੜੇ(SDL_Surface *s, ਅਚਲ SDL_Rect *srcrect, SDL_Surface *d, ਅਚਲ SDL_Rect *dstrect)
{
    ਪੂਰਨ src_w = srcrect->w;
    ਪੂਰਨ src_h = srcrect->h;
    ਪੂਰਨ dst_w = dstrect->w;
    ਪੂਰਨ dst_h = dstrect->h;
    ਪੂਰਨ src_pitch = s->pitch;
    ਪੂਰਨ dst_pitch = d->pitch;
    ਪੂਰਨ bpp = SDL_BYTESPERPIXEL(d->format);

    Uint32 *src = (Uint32 *)((Uint8 *)s->pixels + srcrect->x * bpp + srcrect->y * src_pitch);
    Uint32 *dst = (Uint32 *)((Uint8 *)d->pixels + dstrect->x * bpp + dstrect->y * dst_pitch);

    ਜੇ (bpp == 4) {
        ਵਾਪਸ scale_mat_ਸਭ_ਤੋਂ_ਨੇੜੇ_4(src, src_w, src_h, src_pitch, dst, dst_w, dst_h, dst_pitch);
    } ਨਹੀਂਤਾਂ ਜੇ (bpp == 3) {
        ਵਾਪਸ scale_mat_ਸਭ_ਤੋਂ_ਨੇੜੇ_3(src, src_w, src_h, src_pitch, dst, dst_w, dst_h, dst_pitch);
    } ਨਹੀਂਤਾਂ ਜੇ (bpp == 2) {
        ਵਾਪਸ scale_mat_ਸਭ_ਤੋਂ_ਨੇੜੇ_2(src, src_w, src_h, src_pitch, dst, dst_w, dst_h, dst_pitch);
    } ਨਹੀਂਤਾਂ {
        ਵਾਪਸ scale_mat_ਸਭ_ਤੋਂ_ਨੇੜੇ_1(src, src_w, src_h, src_pitch, dst, dst_w, dst_h, dst_pitch);
    }
}
