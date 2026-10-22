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

#ಅನ್ತರ್ಭಾವ "SDL_sve2_blit_N.h"
#ಅನ್ತರ್ಭಾವ <assert.h>

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_SVE2_INTRINSICS

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು sdl_sve_rgb32_blend_op_fill_alpha
#ವ್ಯಾಖ್ಯಾನಿಸು sdl_sve_rgb32_blend_op_fill_alpha(ma_alpha_chn_idx) \
    ಮಾಡು {                                                    \
        ಆದರೆ (sve_src_chn_idx == (ma_alpha_chn_idx)) {        \
            /* fill alpha */                                \
            sve_ಗುರಿ_u16 = svdup_u16(0xFF);               \
        } ಇಲ್ಲದಿದ್ದರೆ {                                            \
            sve_ಗುರಿ_u16 = sve_ಮೂಲ_u16;                \
        }                                                   \
    } ಆಗ (0)

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು sdl_sve_rgb32_blend_op_copy_alpha
#ವ್ಯಾಖ್ಯಾನಿಸು sdl_sve_rgb32_blend_op_copy_alpha(ma_alpha_chn_idx) \
    ಮಾಡು {                                                    \
        sve_ಗುರಿ_u16 = sve_ಮೂಲ_u16;                    \
    } ಆಗ (0)

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು sdl_sve_rgb32_blend_ಗಮ್ಯ_rgb565_op
#ವ್ಯಾಖ್ಯಾನಿಸು sdl_sve_rgb32_blend_ಗಮ್ಯ_rgb565_op(ma_alpha_chn_idx) \
    ಮಾಡು {                                                   \
        sve_ಗುರಿ_u16 = sve_ಮೂಲ_u16;                   \
    } ಆಗ (0)

#ಅನ್ತರ್ಭಾವ "SDL_sve2_swizzle.h"

SDL_TARGETING("arch=armv8-a+sve2")
ಶೂನ್ಯ Blit8888to8888PixelSwizzleSVE2(SDL_BlitInfo *info)
{
    sdl_sve_8888_ಗಮ್ಯ_8888_swizzle_dispatcher(info);
}

SDL_TARGETING("arch=armv8-a+sve2")
ಶೂನ್ಯ Blit8888to565PixelSwizzleSVE2(SDL_BlitInfo *info)
{
    sdl_sve_rgb32_ಗಮ್ಯ_rgb565_swizzle_dispatcher(info);
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_rgb16_stride_ಕೀಲಿ(uint16_t *SDL_RESTRICT phw_ಮೂಲ,
                                            uint16_t *SDL_RESTRICT phw_ಗುರಿ,
                                            size_t uStride,
                                            uint16_t hw_ಕೀಲಿ,
                                            uint16_t hw_ಕೀಲಿ_ಮುಖವಾಡ)
{
    sdl_sve_stride_loop_u16(uStride, v_ಬಾಲ_Pred)
    {
        svuint16_t v_ಮೂಲ = svld1_u16(v_ಬಾಲ_Pred, phw_ಮೂಲ);
        svuint16_t v_ಗುರಿ = svld1_u16(v_ಬಾಲ_Pred, phw_ಗುರಿ);

        svuint16_t v_ಮೂಲ_Masked = svand_n_u16_m(v_ಬಾಲ_Pred,
                                                 v_ಮೂಲ,
                                                 hw_ಕೀಲಿ_ಮುಖವಾಡ);
        v_ಗುರಿ = svsel_u16(svcmpeq_n_u16(v_ಬಾಲ_Pred, v_ಮೂಲ_Masked, hw_ಕೀಲಿ),
                            v_ಗುರಿ,
                            v_ಮೂಲ);

        svst1_u16(v_ಬಾಲ_Pred, phw_ಗುರಿ, v_ಗುರಿ);

        phw_ಮೂಲ += sve_iteration_advance;
        phw_ಗುರಿ += sve_iteration_advance;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_rgb16_ಕೀಲಿ(uint8_t *SDL_RESTRICT pch_ಮೂಲ,
                                     size_t u_ಮೂಲ_Stride,
                                     uint8_t *SDL_RESTRICT pch_ಗುರಿ,
                                     size_t u_ಗುರಿ_Stride,
                                     ಪೂರ್ಣಾಂಕ n_ಅಗಲ,
                                     ಪೂರ್ಣಾಂಕ n_ಎತ್ತರ,
                                     uint16_t hw_ಕೀಲಿ,
                                     uint16_t hw_ಕೀಲಿ_ಮುಖವಾಡ)
{
    ಪ್ರತಿಜ್ಞಾ(0 == ((uintptr_t)pch_ಮೂಲ & 0x01));
    ಪ್ರತಿಜ್ಞಾ(0 == ((uintptr_t)pch_ಗುರಿ & 0x01));

    ಆಗ (n_ಎತ್ತರ--) {
        sdl_sve_rgb16_stride_ಕೀಲಿ((uint16_t *)pch_ಮೂಲ,
                                 (uint16_t *)pch_ಗುರಿ,
                                 n_ಅಗಲ,
                                 hw_ಕೀಲಿ,
                                 hw_ಕೀಲಿ_ಮುಖವಾಡ);

        pch_ಮೂಲ += u_ಮೂಲ_Stride;
        pch_ಗುರಿ += u_ಗುರಿ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ಶೂನ್ಯ Blit2to2_ಕೀಲಿ_SVE2(SDL_BlitInfo *info)
{
    ಪೂರ್ಣಾಂಕ ಅಗಲ = info->dst_w;
    ಪೂರ್ಣಾಂಕ ಎತ್ತರ = info->dst_h;
    uint8_t *src = info->src;
    ಪೂರ್ಣಾಂಕ srcskip = info->src_skip;
    uint8_t *dst = info->dst;
    ಪೂರ್ಣಾಂಕ dstskip = info->dst_skip;

    ಸ್ಥಿರಾಂಕ SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    ಸ್ಥಿರಾಂಕ SDL_PixelFormatDetails *dstfmt = info->dst_fmt;

    // Set up some basic variables
    ಪೂರ್ಣಾಂಕ srcbpp = srcfmt->ಬೈಟುಗಳು_ಪ್ರತಿ_pixel;
    ಪೂರ್ಣಾಂಕ dstbpp = dstfmt->ಬೈಟುಗಳು_ಪ್ರತಿ_pixel;

    ಪ್ರತಿಜ್ಞಾ(srcbpp == 2);
    ಪ್ರತಿಜ್ಞಾ(dstbpp == 2);

    ಪೂರ್ಣಾಂಕ srcstride = srcskip + srcbpp * ಅಗಲ;
    ಪೂರ್ಣಾಂಕ dststride = dstskip + dstbpp * ಅಗಲ;

    uint32_t ckey = info->colorkey;
    uint32_t rgbmask = ~srcfmt->Amask;
    ckey &= rgbmask;

    sdl_sve_rgb16_ಕೀಲಿ(src,
                      srcstride,
                      dst,
                      dststride,
                      ಅಗಲ,
                      ಎತ್ತರ,
                      ckey,
                      rgbmask);
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_rgb32_stride_ಕೀಲಿ_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ಮೂಲ,
    uint32_t *SDL_RESTRICT pw_ಗುರಿ,
    size_t uStride,
    uint32_t w_ಕೀಲಿ,
    uint32_t w_ಕೀಲಿ_ಮುಖವಾಡ,
    uint32_t w_Opacify_ಮುಖವಾಡ)
{
    sdl_sve_stride_loop_u32(uStride, v_ಬಾಲ_Pred)
    {
        svuint32_t v_ಮೂಲ = svld1_u32(v_ಬಾಲ_Pred, pw_ಮೂಲ);
        svuint32_t v_ಗುರಿ = svld1_u32(v_ಬಾಲ_Pred, pw_ಗುರಿ);

        /*
            uint32_t opamask = ((uint32_t)info->a) << dstfmt->Ashift;
            ...
            if ((*src32 & rgbmask) != ckey) {
                *dst32 = *src32 | opamask;
            }
        */
        svuint32_t v_ಮೂಲ_Masked = svand_n_u32_m(v_ಬಾಲ_Pred,
                                                 v_ಮೂಲ,
                                                 w_ಕೀಲಿ_ಮುಖವಾಡ);
        v_ಗುರಿ = svsel_u32(svcmpeq_n_u32(v_ಬಾಲ_Pred, v_ಮೂಲ_Masked, w_ಕೀಲಿ),
                            v_ಗುರಿ,
                            svorr_n_u32_m(v_ಬಾಲ_Pred, v_ಮೂಲ, w_Opacify_ಮುಖವಾಡ));

        svst1_u32(v_ಬಾಲ_Pred, pw_ಗುರಿ, v_ಗುರಿ);

        pw_ಮೂಲ += sve_iteration_advance;
        pw_ಗುರಿ += sve_iteration_advance;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_rgb32_stride_ಕೀಲಿ_no_alpha(
    uint32_t *SDL_RESTRICT pw_ಮೂಲ,
    uint32_t *SDL_RESTRICT pw_ಗುರಿ,
    size_t uStride,
    uint32_t w_ಕೀಲಿ,
    uint32_t w_ಕೀಲಿ_ಮುಖವಾಡ,
    uint32_t wActualRGBMask)
{
    sdl_sve_stride_loop_u32(uStride, v_ಬಾಲ_Pred)
    {
        svuint32_t v_ಮೂಲ = svld1_u32(v_ಬಾಲ_Pred, pw_ಮೂಲ);
        svuint32_t v_ಗುರಿ = svld1_u32(v_ಬಾಲ_Pred, pw_ಗುರಿ);

        /*
            uint32_t rgbmaskactual = srcfmt->Rmask | srcfmt->Gmask | srcfmt->Bmask;
            ...
            if ((*src32 & rgbmask) != ckey) {
                *dst32 = *src32 & rgbmaskactual;
            }
        */
        svuint32_t v_ಮೂಲ_Masked = svand_n_u32_m(v_ಬಾಲ_Pred,
                                                 v_ಮೂಲ,
                                                 w_ಕೀಲಿ_ಮುಖವಾಡ);
        v_ಗುರಿ = svsel_u32(svcmpeq_n_u32(v_ಬಾಲ_Pred, v_ಮೂಲ_Masked, w_ಕೀಲಿ),
                            v_ಗುರಿ,
                            svand_n_u32_m(v_ಬಾಲ_Pred, v_ಮೂಲ, wActualRGBMask));

        svst1_u32(v_ಬಾಲ_Pred, pw_ಗುರಿ, v_ಗುರಿ);

        pw_ಮೂಲ += sve_iteration_advance;
        pw_ಗುರಿ += sve_iteration_advance;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_rgb32_ಕೀಲಿ_copy_alpha(uint8_t *SDL_RESTRICT pch_ಮೂಲ,
                                                size_t u_ಮೂಲ_Stride,
                                                uint8_t *SDL_RESTRICT pch_ಗುರಿ,
                                                size_t u_ಗುರಿ_Stride,
                                                ಪೂರ್ಣಾಂಕ n_ಅಗಲ,
                                                ಪೂರ್ಣಾಂಕ n_ಎತ್ತರ,
                                                uint32_t w_ಕೀಲಿ,
                                                uint32_t w_ಕೀಲಿ_ಮುಖವಾಡ,
                                                uint32_t w_Opacify_ಮುಖವಾಡ)
{
    ಪ್ರತಿಜ್ಞಾ(0 == ((uintptr_t)pch_ಮೂಲ & 0x03));
    ಪ್ರತಿಜ್ಞಾ(0 == ((uintptr_t)pch_ಗುರಿ & 0x03));

    ಆಗ (n_ಎತ್ತರ--) {
        sdl_sve_rgb32_stride_ಕೀಲಿ_copy_alpha((uint32_t *)pch_ಮೂಲ,
                                            (uint32_t *)pch_ಗುರಿ,
                                            n_ಅಗಲ,
                                            w_ಕೀಲಿ,
                                            w_ಕೀಲಿ_ಮುಖವಾಡ,
                                            w_Opacify_ಮುಖವಾಡ);

        pch_ಮೂಲ += u_ಮೂಲ_Stride;
        pch_ಗುರಿ += u_ಗುರಿ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_rgb32_ಕೀಲಿ_no_alpha(uint8_t *SDL_RESTRICT pch_ಮೂಲ,
                                              size_t u_ಮೂಲ_Stride,
                                              uint8_t *SDL_RESTRICT pch_ಗುರಿ,
                                              size_t u_ಗುರಿ_Stride,
                                              ಪೂರ್ಣಾಂಕ n_ಅಗಲ,
                                              ಪೂರ್ಣಾಂಕ n_ಎತ್ತರ,
                                              uint32_t w_ಕೀಲಿ,
                                              uint32_t w_ಕೀಲಿ_ಮುಖವಾಡ,
                                              uint32_t wActualRGBMask)
{
    ಪ್ರತಿಜ್ಞಾ(0 == ((uintptr_t)pch_ಮೂಲ & 0x03));
    ಪ್ರತಿಜ್ಞಾ(0 == ((uintptr_t)pch_ಗುರಿ & 0x03));

    ಆಗ (n_ಎತ್ತರ--) {
        sdl_sve_rgb32_stride_ಕೀಲಿ_no_alpha((uint32_t *)pch_ಮೂಲ,
                                          (uint32_t *)pch_ಗುರಿ,
                                          n_ಅಗಲ,
                                          w_ಕೀಲಿ,
                                          w_ಕೀಲಿ_ಮುಖವಾಡ,
                                          wActualRGBMask);

        pch_ಮೂಲ += u_ಮೂಲ_Stride;
        pch_ಗುರಿ += u_ಗುರಿ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ಶೂನ್ಯ Blit4to4_ಕೀಲಿ_SVE2(SDL_BlitInfo *info)
{
    ಪೂರ್ಣಾಂಕ ಅಗಲ = info->dst_w;
    ಪೂರ್ಣಾಂಕ ಎತ್ತರ = info->dst_h;
    uint8_t *src = info->src;
    ಪೂರ್ಣಾಂಕ srcskip = info->src_skip;
    uint8_t *dst = info->dst;
    ಪೂರ್ಣಾಂಕ dstskip = info->dst_skip;

    ಸ್ಥಿರಾಂಕ SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    ಸ್ಥಿರಾಂಕ SDL_PixelFormatDetails *dstfmt = info->dst_fmt;

    // Set up some basic variables
    ಪೂರ್ಣಾಂಕ srcbpp = srcfmt->ಬೈಟುಗಳು_ಪ್ರತಿ_pixel;
    ಪೂರ್ಣಾಂಕ dstbpp = dstfmt->ಬೈಟುಗಳು_ಪ್ರತಿ_pixel;

    ಪ್ರತಿಜ್ಞಾ(srcbpp == 4);
    ಪ್ರತಿಜ್ಞಾ(dstbpp == 4);

    ಪೂರ್ಣಾಂಕ srcstride = srcskip + srcbpp * ಅಗಲ;
    ಪೂರ್ಣಾಂಕ dststride = dstskip + dstbpp * ಅಗಲ;

    uint32_t ckey = info->colorkey;
    uint32_t rgbmask = ~srcfmt->Amask;
    ckey &= rgbmask;

    ಆದರೆ (dstfmt->Amask) {
        uint32_t opamask = ((uint32_t)info->a) << dstfmt->Ashift;
        /* RGBA: set alpha from info->a */
        sdl_sve_rgb32_ಕೀಲಿ_copy_alpha(src,
                                     srcstride,
                                     dst,
                                     dststride,
                                     ಅಗಲ,
                                     ಎತ್ತರ,
                                     ckey,
                                     rgbmask,
                                     opamask);
    } ಇಲ್ಲದಿದ್ದರೆ {
        /* RGBA->RGB: only copy rgb and set alpha to zero */
        uint32_t rgbmaskactual = srcfmt->Rmask | srcfmt->Gmask | srcfmt->Bmask;
        sdl_sve_rgb32_ಕೀಲಿ_no_alpha(src,
                                   srcstride,
                                   dst,
                                   dststride,
                                   ಅಗಲ,
                                   ಎತ್ತರ,
                                   ckey,
                                   rgbmask,
                                   rgbmaskactual);
    }
}

#ಆದರೆ_ಅಂತ್ಯ /* SDL_SVE2_INTRINSICS */