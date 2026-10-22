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

#ضمن "SDL_sve2_blit_N.h"
#ضمن <assert.h>

#اگر_تعریف_شده SDL_SVE2_INTRINSICS

#لغو_تعریف sdl_sve_rgb32_blend_op_fill_alpha
#تعریف_کن sdl_sve_rgb32_blend_op_fill_alpha(ma_alpha_chn_idx) \
    افعل {                                                    \
        إذا (sve_src_chn_idx == (ma_alpha_chn_idx)) {        \
            /* fill alpha */                                \
            sve_هدف_u16 = svdup_u16(0xFF);               \
        } وإلا {                                            \
            sve_هدف_u16 = sve_منبع_u16;                \
        }                                                   \
    } طالما (0)

#لغو_تعریف sdl_sve_rgb32_blend_op_copy_alpha
#تعریف_کن sdl_sve_rgb32_blend_op_copy_alpha(ma_alpha_chn_idx) \
    افعل {                                                    \
        sve_هدف_u16 = sve_منبع_u16;                    \
    } طالما (0)

#لغو_تعریف sdl_sve_rgb32_blend_مقصد_rgb565_op
#تعریف_کن sdl_sve_rgb32_blend_مقصد_rgb565_op(ma_alpha_chn_idx) \
    افعل {                                                   \
        sve_هدف_u16 = sve_منبع_u16;                   \
    } طالما (0)

#ضمن "SDL_sve2_swizzle.h"

SDL_TARGETING("arch=armv8-a+sve2")
فراغ Blit8888to8888PixelSwizzleSVE2(SDL_BlitInfo *info)
{
    sdl_sve_8888_مقصد_8888_swizzle_dispatcher(info);
}

SDL_TARGETING("arch=armv8-a+sve2")
فراغ Blit8888to565PixelSwizzleSVE2(SDL_BlitInfo *info)
{
    sdl_sve_rgb32_مقصد_rgb565_swizzle_dispatcher(info);
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_rgb16_stride_کلید(uint16_t *SDL_RESTRICT phw_منبع,
                                            uint16_t *SDL_RESTRICT phw_هدف,
                                            size_t uStride,
                                            uint16_t hw_کلید,
                                            uint16_t hw_کلید_ماسک)
{
    sdl_sve_stride_loop_u16(uStride, v_دم_Pred)
    {
        svuint16_t v_منبع = svld1_u16(v_دم_Pred, phw_منبع);
        svuint16_t v_هدف = svld1_u16(v_دم_Pred, phw_هدف);

        svuint16_t v_منبع_Masked = svand_n_u16_m(v_دم_Pred,
                                                 v_منبع,
                                                 hw_کلید_ماسک);
        v_هدف = svsel_u16(svcmpeq_n_u16(v_دم_Pred, v_منبع_Masked, hw_کلید),
                            v_هدف,
                            v_منبع);

        svst1_u16(v_دم_Pred, phw_هدف, v_هدف);

        phw_منبع += sve_iteration_advance;
        phw_هدف += sve_iteration_advance;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_rgb16_کلید(uint8_t *SDL_RESTRICT pch_منبع,
                                     size_t u_منبع_Stride,
                                     uint8_t *SDL_RESTRICT pch_هدف,
                                     size_t u_هدف_Stride,
                                     صحيح n_عرض,
                                     صحيح n_ارتفاع,
                                     uint16_t hw_کلید,
                                     uint16_t hw_کلید_ماسک)
{
    أكد(0 == ((uintptr_t)pch_منبع & 0x01));
    أكد(0 == ((uintptr_t)pch_هدف & 0x01));

    طالما (n_ارتفاع--) {
        sdl_sve_rgb16_stride_کلید((uint16_t *)pch_منبع,
                                 (uint16_t *)pch_هدف,
                                 n_عرض,
                                 hw_کلید,
                                 hw_کلید_ماسک);

        pch_منبع += u_منبع_Stride;
        pch_هدف += u_هدف_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
فراغ Blit2to2_کلید_SVE2(SDL_BlitInfo *info)
{
    صحيح عرض = info->dst_w;
    صحيح ارتفاع = info->dst_h;
    uint8_t *src = info->src;
    صحيح srcskip = info->src_skip;
    uint8_t *dst = info->dst;
    صحيح dstskip = info->dst_skip;

    ثابت SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    ثابت SDL_PixelFormatDetails *dstfmt = info->dst_fmt;

    // Set up some basic variables
    صحيح srcbpp = srcfmt->بایتها_در_هر_pixel;
    صحيح dstbpp = dstfmt->بایتها_در_هر_pixel;

    أكد(srcbpp == 2);
    أكد(dstbpp == 2);

    صحيح srcstride = srcskip + srcbpp * عرض;
    صحيح dststride = dstskip + dstbpp * عرض;

    uint32_t ckey = info->colorkey;
    uint32_t rgbmask = ~srcfmt->Amask;
    ckey &= rgbmask;

    sdl_sve_rgb16_کلید(src,
                      srcstride,
                      dst,
                      dststride,
                      عرض,
                      ارتفاع,
                      ckey,
                      rgbmask);
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_rgb32_stride_کلید_copy_alpha(
    uint32_t *SDL_RESTRICT pw_منبع,
    uint32_t *SDL_RESTRICT pw_هدف,
    size_t uStride,
    uint32_t w_کلید,
    uint32_t w_کلید_ماسک,
    uint32_t w_Opacify_ماسک)
{
    sdl_sve_stride_loop_u32(uStride, v_دم_Pred)
    {
        svuint32_t v_منبع = svld1_u32(v_دم_Pred, pw_منبع);
        svuint32_t v_هدف = svld1_u32(v_دم_Pred, pw_هدف);

        /*
            uint32_t opamask = ((uint32_t)info->a) << dstfmt->Ashift;
            ...
            if ((*src32 & rgbmask) != ckey) {
                *dst32 = *src32 | opamask;
            }
        */
        svuint32_t v_منبع_Masked = svand_n_u32_m(v_دم_Pred,
                                                 v_منبع,
                                                 w_کلید_ماسک);
        v_هدف = svsel_u32(svcmpeq_n_u32(v_دم_Pred, v_منبع_Masked, w_کلید),
                            v_هدف,
                            svorr_n_u32_m(v_دم_Pred, v_منبع, w_Opacify_ماسک));

        svst1_u32(v_دم_Pred, pw_هدف, v_هدف);

        pw_منبع += sve_iteration_advance;
        pw_هدف += sve_iteration_advance;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_rgb32_stride_کلید_no_alpha(
    uint32_t *SDL_RESTRICT pw_منبع,
    uint32_t *SDL_RESTRICT pw_هدف,
    size_t uStride,
    uint32_t w_کلید,
    uint32_t w_کلید_ماسک,
    uint32_t wActualRGBMask)
{
    sdl_sve_stride_loop_u32(uStride, v_دم_Pred)
    {
        svuint32_t v_منبع = svld1_u32(v_دم_Pred, pw_منبع);
        svuint32_t v_هدف = svld1_u32(v_دم_Pred, pw_هدف);

        /*
            uint32_t rgbmaskactual = srcfmt->Rmask | srcfmt->Gmask | srcfmt->Bmask;
            ...
            if ((*src32 & rgbmask) != ckey) {
                *dst32 = *src32 & rgbmaskactual;
            }
        */
        svuint32_t v_منبع_Masked = svand_n_u32_m(v_دم_Pred,
                                                 v_منبع,
                                                 w_کلید_ماسک);
        v_هدف = svsel_u32(svcmpeq_n_u32(v_دم_Pred, v_منبع_Masked, w_کلید),
                            v_هدف,
                            svand_n_u32_m(v_دم_Pred, v_منبع, wActualRGBMask));

        svst1_u32(v_دم_Pred, pw_هدف, v_هدف);

        pw_منبع += sve_iteration_advance;
        pw_هدف += sve_iteration_advance;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_rgb32_کلید_copy_alpha(uint8_t *SDL_RESTRICT pch_منبع,
                                                size_t u_منبع_Stride,
                                                uint8_t *SDL_RESTRICT pch_هدف,
                                                size_t u_هدف_Stride,
                                                صحيح n_عرض,
                                                صحيح n_ارتفاع,
                                                uint32_t w_کلید,
                                                uint32_t w_کلید_ماسک,
                                                uint32_t w_Opacify_ماسک)
{
    أكد(0 == ((uintptr_t)pch_منبع & 0x03));
    أكد(0 == ((uintptr_t)pch_هدف & 0x03));

    طالما (n_ارتفاع--) {
        sdl_sve_rgb32_stride_کلید_copy_alpha((uint32_t *)pch_منبع,
                                            (uint32_t *)pch_هدف,
                                            n_عرض,
                                            w_کلید,
                                            w_کلید_ماسک,
                                            w_Opacify_ماسک);

        pch_منبع += u_منبع_Stride;
        pch_هدف += u_هدف_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_rgb32_کلید_no_alpha(uint8_t *SDL_RESTRICT pch_منبع,
                                              size_t u_منبع_Stride,
                                              uint8_t *SDL_RESTRICT pch_هدف,
                                              size_t u_هدف_Stride,
                                              صحيح n_عرض,
                                              صحيح n_ارتفاع,
                                              uint32_t w_کلید,
                                              uint32_t w_کلید_ماسک,
                                              uint32_t wActualRGBMask)
{
    أكد(0 == ((uintptr_t)pch_منبع & 0x03));
    أكد(0 == ((uintptr_t)pch_هدف & 0x03));

    طالما (n_ارتفاع--) {
        sdl_sve_rgb32_stride_کلید_no_alpha((uint32_t *)pch_منبع,
                                          (uint32_t *)pch_هدف,
                                          n_عرض,
                                          w_کلید,
                                          w_کلید_ماسک,
                                          wActualRGBMask);

        pch_منبع += u_منبع_Stride;
        pch_هدف += u_هدف_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
فراغ Blit4to4_کلید_SVE2(SDL_BlitInfo *info)
{
    صحيح عرض = info->dst_w;
    صحيح ارتفاع = info->dst_h;
    uint8_t *src = info->src;
    صحيح srcskip = info->src_skip;
    uint8_t *dst = info->dst;
    صحيح dstskip = info->dst_skip;

    ثابت SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    ثابت SDL_PixelFormatDetails *dstfmt = info->dst_fmt;

    // Set up some basic variables
    صحيح srcbpp = srcfmt->بایتها_در_هر_pixel;
    صحيح dstbpp = dstfmt->بایتها_در_هر_pixel;

    أكد(srcbpp == 4);
    أكد(dstbpp == 4);

    صحيح srcstride = srcskip + srcbpp * عرض;
    صحيح dststride = dstskip + dstbpp * عرض;

    uint32_t ckey = info->colorkey;
    uint32_t rgbmask = ~srcfmt->Amask;
    ckey &= rgbmask;

    إذا (dstfmt->Amask) {
        uint32_t opamask = ((uint32_t)info->a) << dstfmt->Ashift;
        /* RGBA: set alpha from info->a */
        sdl_sve_rgb32_کلید_copy_alpha(src,
                                     srcstride,
                                     dst,
                                     dststride,
                                     عرض,
                                     ارتفاع,
                                     ckey,
                                     rgbmask,
                                     opamask);
    } وإلا {
        /* RGBA->RGB: only copy rgb and set alpha to zero */
        uint32_t rgbmaskactual = srcfmt->Rmask | srcfmt->Gmask | srcfmt->Bmask;
        sdl_sve_rgb32_کلید_no_alpha(src,
                                   srcstride,
                                   dst,
                                   dststride,
                                   عرض,
                                   ارتفاع,
                                   ckey,
                                   rgbmask,
                                   rgbmaskactual);
    }
}

#پایان_اگر /* SDL_SVE2_INTRINSICS */