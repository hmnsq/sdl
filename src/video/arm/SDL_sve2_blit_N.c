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

#که_تعریف_شوی SDL_SVE2_INTRINSICS

#تعریف_لغوه sdl_sve_rgb32_blend_op_fill_alpha
#تعریف_کړه sdl_sve_rgb32_blend_op_fill_alpha(ma_alpha_chn_idx) \
    افعل {                                                    \
        إذا (sve_src_chn_idx == (ma_alpha_chn_idx)) {        \
            /* fill alpha */                                \
            sve_موخه_u16 = svdup_u16(0xFF);               \
        } وإلا {                                            \
            sve_موخه_u16 = sve_سرچینه_u16;                \
        }                                                   \
    } طالما (0)

#تعریف_لغوه sdl_sve_rgb32_blend_op_copy_alpha
#تعریف_کړه sdl_sve_rgb32_blend_op_copy_alpha(ma_alpha_chn_idx) \
    افعل {                                                    \
        sve_موخه_u16 = sve_سرچینه_u16;                    \
    } طالما (0)

#تعریف_لغوه sdl_sve_rgb32_blend_منزل_rgb565_op
#تعریف_کړه sdl_sve_rgb32_blend_منزل_rgb565_op(ma_alpha_chn_idx) \
    افعل {                                                   \
        sve_موخه_u16 = sve_سرچینه_u16;                   \
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
ساكن مضمن فراغ sdl_sve_rgb16_stride_کلی(uint16_t *SDL_RESTRICT phw_سرچینه,
                                            uint16_t *SDL_RESTRICT phw_موخه,
                                            size_t uStride,
                                            uint16_t hw_کلی,
                                            uint16_t hw_کلی_ماسک)
{
    sdl_sve_stride_loop_u16(uStride, v_لکۍ_Pred)
    {
        svuint16_t v_سرچینه = svld1_u16(v_لکۍ_Pred, phw_سرچینه);
        svuint16_t v_موخه = svld1_u16(v_لکۍ_Pred, phw_موخه);

        svuint16_t v_سرچینه_Masked = svand_n_u16_m(v_لکۍ_Pred,
                                                 v_سرچینه,
                                                 hw_کلی_ماسک);
        v_موخه = svsel_u16(svcmpeq_n_u16(v_لکۍ_Pred, v_سرچینه_Masked, hw_کلی),
                            v_موخه,
                            v_سرچینه);

        svst1_u16(v_لکۍ_Pred, phw_موخه, v_موخه);

        phw_سرچینه += sve_iteration_advance;
        phw_موخه += sve_iteration_advance;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_rgb16_کلی(uint8_t *SDL_RESTRICT pch_سرچینه,
                                     size_t u_سرچینه_Stride,
                                     uint8_t *SDL_RESTRICT pch_موخه,
                                     size_t u_موخه_Stride,
                                     صحيح n_پلنوالی,
                                     صحيح n_لوړوالی,
                                     uint16_t hw_کلی,
                                     uint16_t hw_کلی_ماسک)
{
    أكد(0 == ((uintptr_t)pch_سرچینه & 0x01));
    أكد(0 == ((uintptr_t)pch_موخه & 0x01));

    طالما (n_لوړوالی--) {
        sdl_sve_rgb16_stride_کلی((uint16_t *)pch_سرچینه,
                                 (uint16_t *)pch_موخه,
                                 n_پلنوالی,
                                 hw_کلی,
                                 hw_کلی_ماسک);

        pch_سرچینه += u_سرچینه_Stride;
        pch_موخه += u_موخه_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
فراغ Blit2to2_کلی_SVE2(SDL_BlitInfo *info)
{
    صحيح پلنوالی = info->dst_w;
    صحيح لوړوالی = info->dst_h;
    uint8_t *src = info->src;
    صحيح srcskip = info->src_skip;
    uint8_t *dst = info->dst;
    صحيح dstskip = info->dst_skip;

    ثابت SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    ثابت SDL_PixelFormatDetails *dstfmt = info->dst_fmt;

    // Set up some basic variables
    صحيح srcbpp = srcfmt->بایټونه_فی_pixel;
    صحيح dstbpp = dstfmt->بایټونه_فی_pixel;

    أكد(srcbpp == 2);
    أكد(dstbpp == 2);

    صحيح srcstride = srcskip + srcbpp * پلنوالی;
    صحيح dststride = dstskip + dstbpp * پلنوالی;

    uint32_t ckey = info->colorkey;
    uint32_t rgbmask = ~srcfmt->Amask;
    ckey &= rgbmask;

    sdl_sve_rgb16_کلی(src,
                      srcstride,
                      dst,
                      dststride,
                      پلنوالی,
                      لوړوالی,
                      ckey,
                      rgbmask);
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_rgb32_stride_کلی_copy_alpha(
    uint32_t *SDL_RESTRICT pw_سرچینه,
    uint32_t *SDL_RESTRICT pw_موخه,
    size_t uStride,
    uint32_t w_کلی,
    uint32_t w_کلی_ماسک,
    uint32_t w_Opacify_ماسک)
{
    sdl_sve_stride_loop_u32(uStride, v_لکۍ_Pred)
    {
        svuint32_t v_سرچینه = svld1_u32(v_لکۍ_Pred, pw_سرچینه);
        svuint32_t v_موخه = svld1_u32(v_لکۍ_Pred, pw_موخه);

        /*
            uint32_t opamask = ((uint32_t)info->a) << dstfmt->Ashift;
            ...
            if ((*src32 & rgbmask) != ckey) {
                *dst32 = *src32 | opamask;
            }
        */
        svuint32_t v_سرچینه_Masked = svand_n_u32_m(v_لکۍ_Pred,
                                                 v_سرچینه,
                                                 w_کلی_ماسک);
        v_موخه = svsel_u32(svcmpeq_n_u32(v_لکۍ_Pred, v_سرچینه_Masked, w_کلی),
                            v_موخه,
                            svorr_n_u32_m(v_لکۍ_Pred, v_سرچینه, w_Opacify_ماسک));

        svst1_u32(v_لکۍ_Pred, pw_موخه, v_موخه);

        pw_سرچینه += sve_iteration_advance;
        pw_موخه += sve_iteration_advance;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_rgb32_stride_کلی_no_alpha(
    uint32_t *SDL_RESTRICT pw_سرچینه,
    uint32_t *SDL_RESTRICT pw_موخه,
    size_t uStride,
    uint32_t w_کلی,
    uint32_t w_کلی_ماسک,
    uint32_t wActualRGBMask)
{
    sdl_sve_stride_loop_u32(uStride, v_لکۍ_Pred)
    {
        svuint32_t v_سرچینه = svld1_u32(v_لکۍ_Pred, pw_سرچینه);
        svuint32_t v_موخه = svld1_u32(v_لکۍ_Pred, pw_موخه);

        /*
            uint32_t rgbmaskactual = srcfmt->Rmask | srcfmt->Gmask | srcfmt->Bmask;
            ...
            if ((*src32 & rgbmask) != ckey) {
                *dst32 = *src32 & rgbmaskactual;
            }
        */
        svuint32_t v_سرچینه_Masked = svand_n_u32_m(v_لکۍ_Pred,
                                                 v_سرچینه,
                                                 w_کلی_ماسک);
        v_موخه = svsel_u32(svcmpeq_n_u32(v_لکۍ_Pred, v_سرچینه_Masked, w_کلی),
                            v_موخه,
                            svand_n_u32_m(v_لکۍ_Pred, v_سرچینه, wActualRGBMask));

        svst1_u32(v_لکۍ_Pred, pw_موخه, v_موخه);

        pw_سرچینه += sve_iteration_advance;
        pw_موخه += sve_iteration_advance;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_rgb32_کلی_copy_alpha(uint8_t *SDL_RESTRICT pch_سرچینه,
                                                size_t u_سرچینه_Stride,
                                                uint8_t *SDL_RESTRICT pch_موخه,
                                                size_t u_موخه_Stride,
                                                صحيح n_پلنوالی,
                                                صحيح n_لوړوالی,
                                                uint32_t w_کلی,
                                                uint32_t w_کلی_ماسک,
                                                uint32_t w_Opacify_ماسک)
{
    أكد(0 == ((uintptr_t)pch_سرچینه & 0x03));
    أكد(0 == ((uintptr_t)pch_موخه & 0x03));

    طالما (n_لوړوالی--) {
        sdl_sve_rgb32_stride_کلی_copy_alpha((uint32_t *)pch_سرچینه,
                                            (uint32_t *)pch_موخه,
                                            n_پلنوالی,
                                            w_کلی,
                                            w_کلی_ماسک,
                                            w_Opacify_ماسک);

        pch_سرچینه += u_سرچینه_Stride;
        pch_موخه += u_موخه_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_rgb32_کلی_no_alpha(uint8_t *SDL_RESTRICT pch_سرچینه,
                                              size_t u_سرچینه_Stride,
                                              uint8_t *SDL_RESTRICT pch_موخه,
                                              size_t u_موخه_Stride,
                                              صحيح n_پلنوالی,
                                              صحيح n_لوړوالی,
                                              uint32_t w_کلی,
                                              uint32_t w_کلی_ماسک,
                                              uint32_t wActualRGBMask)
{
    أكد(0 == ((uintptr_t)pch_سرچینه & 0x03));
    أكد(0 == ((uintptr_t)pch_موخه & 0x03));

    طالما (n_لوړوالی--) {
        sdl_sve_rgb32_stride_کلی_no_alpha((uint32_t *)pch_سرچینه,
                                          (uint32_t *)pch_موخه,
                                          n_پلنوالی,
                                          w_کلی,
                                          w_کلی_ماسک,
                                          wActualRGBMask);

        pch_سرچینه += u_سرچینه_Stride;
        pch_موخه += u_موخه_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
فراغ Blit4to4_کلی_SVE2(SDL_BlitInfo *info)
{
    صحيح پلنوالی = info->dst_w;
    صحيح لوړوالی = info->dst_h;
    uint8_t *src = info->src;
    صحيح srcskip = info->src_skip;
    uint8_t *dst = info->dst;
    صحيح dstskip = info->dst_skip;

    ثابت SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    ثابت SDL_PixelFormatDetails *dstfmt = info->dst_fmt;

    // Set up some basic variables
    صحيح srcbpp = srcfmt->بایټونه_فی_pixel;
    صحيح dstbpp = dstfmt->بایټونه_فی_pixel;

    أكد(srcbpp == 4);
    أكد(dstbpp == 4);

    صحيح srcstride = srcskip + srcbpp * پلنوالی;
    صحيح dststride = dstskip + dstbpp * پلنوالی;

    uint32_t ckey = info->colorkey;
    uint32_t rgbmask = ~srcfmt->Amask;
    ckey &= rgbmask;

    إذا (dstfmt->Amask) {
        uint32_t opamask = ((uint32_t)info->a) << dstfmt->Ashift;
        /* RGBA: set alpha from info->a */
        sdl_sve_rgb32_کلی_copy_alpha(src,
                                     srcstride,
                                     dst,
                                     dststride,
                                     پلنوالی,
                                     لوړوالی,
                                     ckey,
                                     rgbmask,
                                     opamask);
    } وإلا {
        /* RGBA->RGB: only copy rgb and set alpha to zero */
        uint32_t rgbmaskactual = srcfmt->Rmask | srcfmt->Gmask | srcfmt->Bmask;
        sdl_sve_rgb32_کلی_no_alpha(src,
                                   srcstride,
                                   dst,
                                   dststride,
                                   پلنوالی,
                                   لوړوالی,
                                   ckey,
                                   rgbmask,
                                   rgbmaskactual);
    }
}

#د_که_پای /* SDL_SVE2_INTRINSICS */