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

#جے_تعریف_شدہ SDL_SVE2_INTRINSICS

#تعریف_رد sdl_sve_rgb32_blend_op_fill_alpha
#تعریف_کرو sdl_sve_rgb32_blend_op_fill_alpha(ma_alpha_chn_idx) \
    افعل {                                                    \
        إذا (sve_src_chn_idx == (ma_alpha_chn_idx)) {        \
            /* fill alpha */                                \
            sve_نشانہ_u16 = svdup_u16(0xFF);               \
        } وإلا {                                            \
            sve_نشانہ_u16 = sve_سروت_u16;                \
        }                                                   \
    } طالما (0)

#تعریف_رد sdl_sve_rgb32_blend_op_copy_alpha
#تعریف_کرو sdl_sve_rgb32_blend_op_copy_alpha(ma_alpha_chn_idx) \
    افعل {                                                    \
        sve_نشانہ_u16 = sve_سروت_u16;                    \
    } طالما (0)

#تعریف_رد sdl_sve_rgb32_blend_منزل_rgb565_op
#تعریف_کرو sdl_sve_rgb32_blend_منزل_rgb565_op(ma_alpha_chn_idx) \
    افعل {                                                   \
        sve_نشانہ_u16 = sve_سروت_u16;                   \
    } طالما (0)

#ضمن "SDL_sve2_swizzle.h"

SDL_TARGETING("arch=armv8-a+sve2")
فراغ Blit8888to8888PixelSwizzleSVE2(SDL_BlitInfo *info)
{
    sdl_sve_8888_منزل_8888_swizzle_dispatcher(info);
}

SDL_TARGETING("arch=armv8-a+sve2")
فراغ Blit8888to565PixelSwizzleSVE2(SDL_BlitInfo *info)
{
    sdl_sve_rgb32_منزل_rgb565_swizzle_dispatcher(info);
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_rgb16_stride_کلید(uint16_t *SDL_RESTRICT phw_سروت,
                                            uint16_t *SDL_RESTRICT phw_نشانہ,
                                            size_t uStride,
                                            uint16_t hw_کلید,
                                            uint16_t hw_کلید_نقاب)
{
    sdl_sve_stride_loop_u16(uStride, v_پوچھ_Pred)
    {
        svuint16_t v_سروت = svld1_u16(v_پوچھ_Pred, phw_سروت);
        svuint16_t v_نشانہ = svld1_u16(v_پوچھ_Pred, phw_نشانہ);

        svuint16_t v_سروت_Masked = svand_n_u16_m(v_پوچھ_Pred,
                                                 v_سروت,
                                                 hw_کلید_نقاب);
        v_نشانہ = svsel_u16(svcmpeq_n_u16(v_پوچھ_Pred, v_سروت_Masked, hw_کلید),
                            v_نشانہ,
                            v_سروت);

        svst1_u16(v_پوچھ_Pred, phw_نشانہ, v_نشانہ);

        phw_سروت += sve_iteration_advance;
        phw_نشانہ += sve_iteration_advance;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_rgb16_کلید(uint8_t *SDL_RESTRICT pch_سروت,
                                     size_t u_سروت_Stride,
                                     uint8_t *SDL_RESTRICT pch_نشانہ,
                                     size_t u_نشانہ_Stride,
                                     صحيح n_چوڑائی,
                                     صحيح n_اچائی,
                                     uint16_t hw_کلید,
                                     uint16_t hw_کلید_نقاب)
{
    أكد(0 == ((uintptr_t)pch_سروت & 0x01));
    أكد(0 == ((uintptr_t)pch_نشانہ & 0x01));

    طالما (n_اچائی--) {
        sdl_sve_rgb16_stride_کلید((uint16_t *)pch_سروت,
                                 (uint16_t *)pch_نشانہ,
                                 n_چوڑائی,
                                 hw_کلید,
                                 hw_کلید_نقاب);

        pch_سروت += u_سروت_Stride;
        pch_نشانہ += u_نشانہ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
فراغ Blit2to2_کلید_SVE2(SDL_BlitInfo *info)
{
    صحيح چوڑائی = info->dst_w;
    صحيح اچائی = info->dst_h;
    uint8_t *src = info->src;
    صحيح srcskip = info->src_skip;
    uint8_t *dst = info->dst;
    صحيح dstskip = info->dst_skip;

    ثابت SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    ثابت SDL_PixelFormatDetails *dstfmt = info->dst_fmt;

    // Set up some basic variables
    صحيح srcbpp = srcfmt->بائٹاں_فی_pixel;
    صحيح dstbpp = dstfmt->بائٹاں_فی_pixel;

    أكد(srcbpp == 2);
    أكد(dstbpp == 2);

    صحيح srcstride = srcskip + srcbpp * چوڑائی;
    صحيح dststride = dstskip + dstbpp * چوڑائی;

    uint32_t ckey = info->colorkey;
    uint32_t rgbmask = ~srcfmt->Amask;
    ckey &= rgbmask;

    sdl_sve_rgb16_کلید(src,
                      srcstride,
                      dst,
                      dststride,
                      چوڑائی,
                      اچائی,
                      ckey,
                      rgbmask);
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_rgb32_stride_کلید_copy_alpha(
    uint32_t *SDL_RESTRICT pw_سروت,
    uint32_t *SDL_RESTRICT pw_نشانہ,
    size_t uStride,
    uint32_t w_کلید,
    uint32_t w_کلید_نقاب,
    uint32_t w_Opacify_نقاب)
{
    sdl_sve_stride_loop_u32(uStride, v_پوچھ_Pred)
    {
        svuint32_t v_سروت = svld1_u32(v_پوچھ_Pred, pw_سروت);
        svuint32_t v_نشانہ = svld1_u32(v_پوچھ_Pred, pw_نشانہ);

        /*
            uint32_t opamask = ((uint32_t)info->a) << dstfmt->Ashift;
            ...
            if ((*src32 & rgbmask) != ckey) {
                *dst32 = *src32 | opamask;
            }
        */
        svuint32_t v_سروت_Masked = svand_n_u32_m(v_پوچھ_Pred,
                                                 v_سروت,
                                                 w_کلید_نقاب);
        v_نشانہ = svsel_u32(svcmpeq_n_u32(v_پوچھ_Pred, v_سروت_Masked, w_کلید),
                            v_نشانہ,
                            svorr_n_u32_m(v_پوچھ_Pred, v_سروت, w_Opacify_نقاب));

        svst1_u32(v_پوچھ_Pred, pw_نشانہ, v_نشانہ);

        pw_سروت += sve_iteration_advance;
        pw_نشانہ += sve_iteration_advance;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_rgb32_stride_کلید_no_alpha(
    uint32_t *SDL_RESTRICT pw_سروت,
    uint32_t *SDL_RESTRICT pw_نشانہ,
    size_t uStride,
    uint32_t w_کلید,
    uint32_t w_کلید_نقاب,
    uint32_t wActualRGBMask)
{
    sdl_sve_stride_loop_u32(uStride, v_پوچھ_Pred)
    {
        svuint32_t v_سروت = svld1_u32(v_پوچھ_Pred, pw_سروت);
        svuint32_t v_نشانہ = svld1_u32(v_پوچھ_Pred, pw_نشانہ);

        /*
            uint32_t rgbmaskactual = srcfmt->Rmask | srcfmt->Gmask | srcfmt->Bmask;
            ...
            if ((*src32 & rgbmask) != ckey) {
                *dst32 = *src32 & rgbmaskactual;
            }
        */
        svuint32_t v_سروت_Masked = svand_n_u32_m(v_پوچھ_Pred,
                                                 v_سروت,
                                                 w_کلید_نقاب);
        v_نشانہ = svsel_u32(svcmpeq_n_u32(v_پوچھ_Pred, v_سروت_Masked, w_کلید),
                            v_نشانہ,
                            svand_n_u32_m(v_پوچھ_Pred, v_سروت, wActualRGBMask));

        svst1_u32(v_پوچھ_Pred, pw_نشانہ, v_نشانہ);

        pw_سروت += sve_iteration_advance;
        pw_نشانہ += sve_iteration_advance;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_rgb32_کلید_copy_alpha(uint8_t *SDL_RESTRICT pch_سروت,
                                                size_t u_سروت_Stride,
                                                uint8_t *SDL_RESTRICT pch_نشانہ,
                                                size_t u_نشانہ_Stride,
                                                صحيح n_چوڑائی,
                                                صحيح n_اچائی,
                                                uint32_t w_کلید,
                                                uint32_t w_کلید_نقاب,
                                                uint32_t w_Opacify_نقاب)
{
    أكد(0 == ((uintptr_t)pch_سروت & 0x03));
    أكد(0 == ((uintptr_t)pch_نشانہ & 0x03));

    طالما (n_اچائی--) {
        sdl_sve_rgb32_stride_کلید_copy_alpha((uint32_t *)pch_سروت,
                                            (uint32_t *)pch_نشانہ,
                                            n_چوڑائی,
                                            w_کلید,
                                            w_کلید_نقاب,
                                            w_Opacify_نقاب);

        pch_سروت += u_سروت_Stride;
        pch_نشانہ += u_نشانہ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_rgb32_کلید_no_alpha(uint8_t *SDL_RESTRICT pch_سروت,
                                              size_t u_سروت_Stride,
                                              uint8_t *SDL_RESTRICT pch_نشانہ,
                                              size_t u_نشانہ_Stride,
                                              صحيح n_چوڑائی,
                                              صحيح n_اچائی,
                                              uint32_t w_کلید,
                                              uint32_t w_کلید_نقاب,
                                              uint32_t wActualRGBMask)
{
    أكد(0 == ((uintptr_t)pch_سروت & 0x03));
    أكد(0 == ((uintptr_t)pch_نشانہ & 0x03));

    طالما (n_اچائی--) {
        sdl_sve_rgb32_stride_کلید_no_alpha((uint32_t *)pch_سروت,
                                          (uint32_t *)pch_نشانہ,
                                          n_چوڑائی,
                                          w_کلید,
                                          w_کلید_نقاب,
                                          wActualRGBMask);

        pch_سروت += u_سروت_Stride;
        pch_نشانہ += u_نشانہ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
فراغ Blit4to4_کلید_SVE2(SDL_BlitInfo *info)
{
    صحيح چوڑائی = info->dst_w;
    صحيح اچائی = info->dst_h;
    uint8_t *src = info->src;
    صحيح srcskip = info->src_skip;
    uint8_t *dst = info->dst;
    صحيح dstskip = info->dst_skip;

    ثابت SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    ثابت SDL_PixelFormatDetails *dstfmt = info->dst_fmt;

    // Set up some basic variables
    صحيح srcbpp = srcfmt->بائٹاں_فی_pixel;
    صحيح dstbpp = dstfmt->بائٹاں_فی_pixel;

    أكد(srcbpp == 4);
    أكد(dstbpp == 4);

    صحيح srcstride = srcskip + srcbpp * چوڑائی;
    صحيح dststride = dstskip + dstbpp * چوڑائی;

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
                                     چوڑائی,
                                     اچائی,
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
                                   چوڑائی,
                                   اچائی,
                                   ckey,
                                   rgbmask,
                                   rgbmaskactual);
    }
}

#جے_انت /* SDL_SVE2_INTRINSICS */