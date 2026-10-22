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

#شامل "SDL_sve2_blit_N.h"
#شامل <assert.h>

#اگر_تعریف_شدہ SDL_SVE2_INTRINSICS

#تعریف_منسوخ sdl_sve_rgb32_blend_op_fill_alpha
#تعریف_کرو sdl_sve_rgb32_blend_op_fill_alpha(ma_alpha_chn_idx) \
    کرو {                                                    \
        اگر (sve_src_chn_idx == (ma_alpha_chn_idx)) {        \
            /* fill alpha */                                \
            sve_ہدف_u16 = svdup_u16(0xFF);               \
        } ورنہ {                                            \
            sve_ہدف_u16 = sve_ماخذ_u16;                \
        }                                                   \
    } جب (0)

#تعریف_منسوخ sdl_sve_rgb32_blend_op_copy_alpha
#تعریف_کرو sdl_sve_rgb32_blend_op_copy_alpha(ma_alpha_chn_idx) \
    کرو {                                                    \
        sve_ہدف_u16 = sve_ماخذ_u16;                    \
    } جب (0)

#تعریف_منسوخ sdl_sve_rgb32_blend_مقصد_rgb565_op
#تعریف_کرو sdl_sve_rgb32_blend_مقصد_rgb565_op(ma_alpha_chn_idx) \
    کرو {                                                   \
        sve_ہدف_u16 = sve_ماخذ_u16;                   \
    } جب (0)

#شامل "SDL_sve2_swizzle.h"

SDL_TARGETING("arch=armv8-a+sve2")
خالی Blit8888to8888PixelSwizzleSVE2(SDL_BlitInfo *info)
{
    sdl_sve_8888_مقصد_8888_swizzle_dispatcher(info);
}

SDL_TARGETING("arch=armv8-a+sve2")
خالی Blit8888to565PixelSwizzleSVE2(SDL_BlitInfo *info)
{
    sdl_sve_rgb32_مقصد_rgb565_swizzle_dispatcher(info);
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساکن اندرونی خالی sdl_sve_rgb16_stride_کلید(uint16_t *SDL_RESTRICT phw_ماخذ,
                                            uint16_t *SDL_RESTRICT phw_ہدف,
                                            size_t uStride,
                                            uint16_t hw_کلید,
                                            uint16_t hw_کلید_نقاب)
{
    sdl_sve_stride_loop_u16(uStride, v_دم_Pred)
    {
        svuint16_t v_ماخذ = svld1_u16(v_دم_Pred, phw_ماخذ);
        svuint16_t v_ہدف = svld1_u16(v_دم_Pred, phw_ہدف);

        svuint16_t v_ماخذ_Masked = svand_n_u16_m(v_دم_Pred,
                                                 v_ماخذ,
                                                 hw_کلید_نقاب);
        v_ہدف = svsel_u16(svcmpeq_n_u16(v_دم_Pred, v_ماخذ_Masked, hw_کلید),
                            v_ہدف,
                            v_ماخذ);

        svst1_u16(v_دم_Pred, phw_ہدف, v_ہدف);

        phw_ماخذ += sve_iteration_advance;
        phw_ہدف += sve_iteration_advance;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساکن اندرونی خالی sdl_sve_rgb16_کلید(uint8_t *SDL_RESTRICT pch_ماخذ,
                                     size_t u_ماخذ_Stride,
                                     uint8_t *SDL_RESTRICT pch_ہدف,
                                     size_t u_ہدف_Stride,
                                     صحیح n_چوڑائی,
                                     صحیح n_اونچائی,
                                     uint16_t hw_کلید,
                                     uint16_t hw_کلید_نقاب)
{
    أكد(0 == ((uintptr_t)pch_ماخذ & 0x01));
    أكد(0 == ((uintptr_t)pch_ہدف & 0x01));

    جب (n_اونچائی--) {
        sdl_sve_rgb16_stride_کلید((uint16_t *)pch_ماخذ,
                                 (uint16_t *)pch_ہدف,
                                 n_چوڑائی,
                                 hw_کلید,
                                 hw_کلید_نقاب);

        pch_ماخذ += u_ماخذ_Stride;
        pch_ہدف += u_ہدف_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
خالی Blit2to2_کلید_SVE2(SDL_BlitInfo *info)
{
    صحیح چوڑائی = info->dst_w;
    صحیح اونچائی = info->dst_h;
    uint8_t *src = info->src;
    صحیح srcskip = info->src_skip;
    uint8_t *dst = info->dst;
    صحیح dstskip = info->dst_skip;

    ثابت SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    ثابت SDL_PixelFormatDetails *dstfmt = info->dst_fmt;

    // Set up some basic variables
    صحیح srcbpp = srcfmt->بائٹیں_فی_pixel;
    صحیح dstbpp = dstfmt->بائٹیں_فی_pixel;

    أكد(srcbpp == 2);
    أكد(dstbpp == 2);

    صحیح srcstride = srcskip + srcbpp * چوڑائی;
    صحیح dststride = dstskip + dstbpp * چوڑائی;

    uint32_t ckey = info->colorkey;
    uint32_t rgbmask = ~srcfmt->Amask;
    ckey &= rgbmask;

    sdl_sve_rgb16_کلید(src,
                      srcstride,
                      dst,
                      dststride,
                      چوڑائی,
                      اونچائی,
                      ckey,
                      rgbmask);
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساکن اندرونی خالی sdl_sve_rgb32_stride_کلید_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ماخذ,
    uint32_t *SDL_RESTRICT pw_ہدف,
    size_t uStride,
    uint32_t w_کلید,
    uint32_t w_کلید_نقاب,
    uint32_t w_Opacify_نقاب)
{
    sdl_sve_stride_loop_u32(uStride, v_دم_Pred)
    {
        svuint32_t v_ماخذ = svld1_u32(v_دم_Pred, pw_ماخذ);
        svuint32_t v_ہدف = svld1_u32(v_دم_Pred, pw_ہدف);

        /*
            uint32_t opamask = ((uint32_t)info->a) << dstfmt->Ashift;
            ...
            if ((*src32 & rgbmask) != ckey) {
                *dst32 = *src32 | opamask;
            }
        */
        svuint32_t v_ماخذ_Masked = svand_n_u32_m(v_دم_Pred,
                                                 v_ماخذ,
                                                 w_کلید_نقاب);
        v_ہدف = svsel_u32(svcmpeq_n_u32(v_دم_Pred, v_ماخذ_Masked, w_کلید),
                            v_ہدف,
                            svorr_n_u32_m(v_دم_Pred, v_ماخذ, w_Opacify_نقاب));

        svst1_u32(v_دم_Pred, pw_ہدف, v_ہدف);

        pw_ماخذ += sve_iteration_advance;
        pw_ہدف += sve_iteration_advance;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساکن اندرونی خالی sdl_sve_rgb32_stride_کلید_no_alpha(
    uint32_t *SDL_RESTRICT pw_ماخذ,
    uint32_t *SDL_RESTRICT pw_ہدف,
    size_t uStride,
    uint32_t w_کلید,
    uint32_t w_کلید_نقاب,
    uint32_t wActualRGBMask)
{
    sdl_sve_stride_loop_u32(uStride, v_دم_Pred)
    {
        svuint32_t v_ماخذ = svld1_u32(v_دم_Pred, pw_ماخذ);
        svuint32_t v_ہدف = svld1_u32(v_دم_Pred, pw_ہدف);

        /*
            uint32_t rgbmaskactual = srcfmt->Rmask | srcfmt->Gmask | srcfmt->Bmask;
            ...
            if ((*src32 & rgbmask) != ckey) {
                *dst32 = *src32 & rgbmaskactual;
            }
        */
        svuint32_t v_ماخذ_Masked = svand_n_u32_m(v_دم_Pred,
                                                 v_ماخذ,
                                                 w_کلید_نقاب);
        v_ہدف = svsel_u32(svcmpeq_n_u32(v_دم_Pred, v_ماخذ_Masked, w_کلید),
                            v_ہدف,
                            svand_n_u32_m(v_دم_Pred, v_ماخذ, wActualRGBMask));

        svst1_u32(v_دم_Pred, pw_ہدف, v_ہدف);

        pw_ماخذ += sve_iteration_advance;
        pw_ہدف += sve_iteration_advance;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساکن اندرونی خالی sdl_sve_rgb32_کلید_copy_alpha(uint8_t *SDL_RESTRICT pch_ماخذ,
                                                size_t u_ماخذ_Stride,
                                                uint8_t *SDL_RESTRICT pch_ہدف,
                                                size_t u_ہدف_Stride,
                                                صحیح n_چوڑائی,
                                                صحیح n_اونچائی,
                                                uint32_t w_کلید,
                                                uint32_t w_کلید_نقاب,
                                                uint32_t w_Opacify_نقاب)
{
    أكد(0 == ((uintptr_t)pch_ماخذ & 0x03));
    أكد(0 == ((uintptr_t)pch_ہدف & 0x03));

    جب (n_اونچائی--) {
        sdl_sve_rgb32_stride_کلید_copy_alpha((uint32_t *)pch_ماخذ,
                                            (uint32_t *)pch_ہدف,
                                            n_چوڑائی,
                                            w_کلید,
                                            w_کلید_نقاب,
                                            w_Opacify_نقاب);

        pch_ماخذ += u_ماخذ_Stride;
        pch_ہدف += u_ہدف_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساکن اندرونی خالی sdl_sve_rgb32_کلید_no_alpha(uint8_t *SDL_RESTRICT pch_ماخذ,
                                              size_t u_ماخذ_Stride,
                                              uint8_t *SDL_RESTRICT pch_ہدف,
                                              size_t u_ہدف_Stride,
                                              صحیح n_چوڑائی,
                                              صحیح n_اونچائی,
                                              uint32_t w_کلید,
                                              uint32_t w_کلید_نقاب,
                                              uint32_t wActualRGBMask)
{
    أكد(0 == ((uintptr_t)pch_ماخذ & 0x03));
    أكد(0 == ((uintptr_t)pch_ہدف & 0x03));

    جب (n_اونچائی--) {
        sdl_sve_rgb32_stride_کلید_no_alpha((uint32_t *)pch_ماخذ,
                                          (uint32_t *)pch_ہدف,
                                          n_چوڑائی,
                                          w_کلید,
                                          w_کلید_نقاب,
                                          wActualRGBMask);

        pch_ماخذ += u_ماخذ_Stride;
        pch_ہدف += u_ہدف_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
خالی Blit4to4_کلید_SVE2(SDL_BlitInfo *info)
{
    صحیح چوڑائی = info->dst_w;
    صحیح اونچائی = info->dst_h;
    uint8_t *src = info->src;
    صحیح srcskip = info->src_skip;
    uint8_t *dst = info->dst;
    صحیح dstskip = info->dst_skip;

    ثابت SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    ثابت SDL_PixelFormatDetails *dstfmt = info->dst_fmt;

    // Set up some basic variables
    صحیح srcbpp = srcfmt->بائٹیں_فی_pixel;
    صحیح dstbpp = dstfmt->بائٹیں_فی_pixel;

    أكد(srcbpp == 4);
    أكد(dstbpp == 4);

    صحیح srcstride = srcskip + srcbpp * چوڑائی;
    صحیح dststride = dstskip + dstbpp * چوڑائی;

    uint32_t ckey = info->colorkey;
    uint32_t rgbmask = ~srcfmt->Amask;
    ckey &= rgbmask;

    اگر (dstfmt->Amask) {
        uint32_t opamask = ((uint32_t)info->a) << dstfmt->Ashift;
        /* RGBA: set alpha from info->a */
        sdl_sve_rgb32_کلید_copy_alpha(src,
                                     srcstride,
                                     dst,
                                     dststride,
                                     چوڑائی,
                                     اونچائی,
                                     ckey,
                                     rgbmask,
                                     opamask);
    } ورنہ {
        /* RGBA->RGB: only copy rgb and set alpha to zero */
        uint32_t rgbmaskactual = srcfmt->Rmask | srcfmt->Gmask | srcfmt->Bmask;
        sdl_sve_rgb32_کلید_no_alpha(src,
                                   srcstride,
                                   dst,
                                   dststride,
                                   چوڑائی,
                                   اونچائی,
                                   ckey,
                                   rgbmask,
                                   rgbmaskactual);
    }
}

#اگر_ختم /* SDL_SVE2_INTRINSICS */