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

#جيڪڏهن_وصف_ٿيل SDL_SVE2_INTRINSICS

#وصف_رد sdl_sve_rgb32_blend_op_fill_alpha
#وصف_ڪريو sdl_sve_rgb32_blend_op_fill_alpha(ma_alpha_chn_idx) \
    افعل {                                                    \
        إذا (sve_src_chn_idx == (ma_alpha_chn_idx)) {        \
            /* fill alpha */                                \
            sve_هدف_u16 = svdup_u16(0xFF);               \
        } وإلا {                                            \
            sve_هدف_u16 = sve_ذريعو_u16;                \
        }                                                   \
    } طالما (0)

#وصف_رد sdl_sve_rgb32_blend_op_copy_alpha
#وصف_ڪريو sdl_sve_rgb32_blend_op_copy_alpha(ma_alpha_chn_idx) \
    افعل {                                                    \
        sve_هدف_u16 = sve_ذريعو_u16;                    \
    } طالما (0)

#وصف_رد sdl_sve_rgb32_blend_منزل_rgb565_op
#وصف_ڪريو sdl_sve_rgb32_blend_منزل_rgb565_op(ma_alpha_chn_idx) \
    افعل {                                                   \
        sve_هدف_u16 = sve_ذريعو_u16;                   \
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
ساكن مضمن فراغ sdl_sve_rgb16_stride_ڪنجي(uint16_t *SDL_RESTRICT phw_ذريعو,
                                            uint16_t *SDL_RESTRICT phw_هدف,
                                            size_t uStride,
                                            uint16_t hw_ڪنجي,
                                            uint16_t hw_ڪنجي_نقاب)
{
    sdl_sve_stride_loop_u16(uStride, v_پڇ_Pred)
    {
        svuint16_t v_ذريعو = svld1_u16(v_پڇ_Pred, phw_ذريعو);
        svuint16_t v_هدف = svld1_u16(v_پڇ_Pred, phw_هدف);

        svuint16_t v_ذريعو_Masked = svand_n_u16_m(v_پڇ_Pred,
                                                 v_ذريعو,
                                                 hw_ڪنجي_نقاب);
        v_هدف = svsel_u16(svcmpeq_n_u16(v_پڇ_Pred, v_ذريعو_Masked, hw_ڪنجي),
                            v_هدف,
                            v_ذريعو);

        svst1_u16(v_پڇ_Pred, phw_هدف, v_هدف);

        phw_ذريعو += sve_iteration_advance;
        phw_هدف += sve_iteration_advance;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_rgb16_ڪنجي(uint8_t *SDL_RESTRICT pch_ذريعو,
                                     size_t u_ذريعو_Stride,
                                     uint8_t *SDL_RESTRICT pch_هدف,
                                     size_t u_هدف_Stride,
                                     صحيح n_ويڪر,
                                     صحيح n_اوچائي,
                                     uint16_t hw_ڪنجي,
                                     uint16_t hw_ڪنجي_نقاب)
{
    أكد(0 == ((uintptr_t)pch_ذريعو & 0x01));
    أكد(0 == ((uintptr_t)pch_هدف & 0x01));

    طالما (n_اوچائي--) {
        sdl_sve_rgb16_stride_ڪنجي((uint16_t *)pch_ذريعو,
                                 (uint16_t *)pch_هدف,
                                 n_ويڪر,
                                 hw_ڪنجي,
                                 hw_ڪنجي_نقاب);

        pch_ذريعو += u_ذريعو_Stride;
        pch_هدف += u_هدف_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
فراغ Blit2to2_ڪنجي_SVE2(SDL_BlitInfo *info)
{
    صحيح ويڪر = info->dst_w;
    صحيح اوچائي = info->dst_h;
    uint8_t *src = info->src;
    صحيح srcskip = info->src_skip;
    uint8_t *dst = info->dst;
    صحيح dstskip = info->dst_skip;

    ثابت SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    ثابت SDL_PixelFormatDetails *dstfmt = info->dst_fmt;

    // Set up some basic variables
    صحيح srcbpp = srcfmt->بائيٽون_في_pixel;
    صحيح dstbpp = dstfmt->بائيٽون_في_pixel;

    أكد(srcbpp == 2);
    أكد(dstbpp == 2);

    صحيح srcstride = srcskip + srcbpp * ويڪر;
    صحيح dststride = dstskip + dstbpp * ويڪر;

    uint32_t ckey = info->colorkey;
    uint32_t rgbmask = ~srcfmt->Amask;
    ckey &= rgbmask;

    sdl_sve_rgb16_ڪنجي(src,
                      srcstride,
                      dst,
                      dststride,
                      ويڪر,
                      اوچائي,
                      ckey,
                      rgbmask);
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_rgb32_stride_ڪنجي_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ذريعو,
    uint32_t *SDL_RESTRICT pw_هدف,
    size_t uStride,
    uint32_t w_ڪنجي,
    uint32_t w_ڪنجي_نقاب,
    uint32_t w_Opacify_نقاب)
{
    sdl_sve_stride_loop_u32(uStride, v_پڇ_Pred)
    {
        svuint32_t v_ذريعو = svld1_u32(v_پڇ_Pred, pw_ذريعو);
        svuint32_t v_هدف = svld1_u32(v_پڇ_Pred, pw_هدف);

        /*
            uint32_t opamask = ((uint32_t)info->a) << dstfmt->Ashift;
            ...
            if ((*src32 & rgbmask) != ckey) {
                *dst32 = *src32 | opamask;
            }
        */
        svuint32_t v_ذريعو_Masked = svand_n_u32_m(v_پڇ_Pred,
                                                 v_ذريعو,
                                                 w_ڪنجي_نقاب);
        v_هدف = svsel_u32(svcmpeq_n_u32(v_پڇ_Pred, v_ذريعو_Masked, w_ڪنجي),
                            v_هدف,
                            svorr_n_u32_m(v_پڇ_Pred, v_ذريعو, w_Opacify_نقاب));

        svst1_u32(v_پڇ_Pred, pw_هدف, v_هدف);

        pw_ذريعو += sve_iteration_advance;
        pw_هدف += sve_iteration_advance;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_rgb32_stride_ڪنجي_no_alpha(
    uint32_t *SDL_RESTRICT pw_ذريعو,
    uint32_t *SDL_RESTRICT pw_هدف,
    size_t uStride,
    uint32_t w_ڪنجي,
    uint32_t w_ڪنجي_نقاب,
    uint32_t wActualRGBMask)
{
    sdl_sve_stride_loop_u32(uStride, v_پڇ_Pred)
    {
        svuint32_t v_ذريعو = svld1_u32(v_پڇ_Pred, pw_ذريعو);
        svuint32_t v_هدف = svld1_u32(v_پڇ_Pred, pw_هدف);

        /*
            uint32_t rgbmaskactual = srcfmt->Rmask | srcfmt->Gmask | srcfmt->Bmask;
            ...
            if ((*src32 & rgbmask) != ckey) {
                *dst32 = *src32 & rgbmaskactual;
            }
        */
        svuint32_t v_ذريعو_Masked = svand_n_u32_m(v_پڇ_Pred,
                                                 v_ذريعو,
                                                 w_ڪنجي_نقاب);
        v_هدف = svsel_u32(svcmpeq_n_u32(v_پڇ_Pred, v_ذريعو_Masked, w_ڪنجي),
                            v_هدف,
                            svand_n_u32_m(v_پڇ_Pred, v_ذريعو, wActualRGBMask));

        svst1_u32(v_پڇ_Pred, pw_هدف, v_هدف);

        pw_ذريعو += sve_iteration_advance;
        pw_هدف += sve_iteration_advance;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_rgb32_ڪنجي_copy_alpha(uint8_t *SDL_RESTRICT pch_ذريعو,
                                                size_t u_ذريعو_Stride,
                                                uint8_t *SDL_RESTRICT pch_هدف,
                                                size_t u_هدف_Stride,
                                                صحيح n_ويڪر,
                                                صحيح n_اوچائي,
                                                uint32_t w_ڪنجي,
                                                uint32_t w_ڪنجي_نقاب,
                                                uint32_t w_Opacify_نقاب)
{
    أكد(0 == ((uintptr_t)pch_ذريعو & 0x03));
    أكد(0 == ((uintptr_t)pch_هدف & 0x03));

    طالما (n_اوچائي--) {
        sdl_sve_rgb32_stride_ڪنجي_copy_alpha((uint32_t *)pch_ذريعو,
                                            (uint32_t *)pch_هدف,
                                            n_ويڪر,
                                            w_ڪنجي,
                                            w_ڪنجي_نقاب,
                                            w_Opacify_نقاب);

        pch_ذريعو += u_ذريعو_Stride;
        pch_هدف += u_هدف_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_rgb32_ڪنجي_no_alpha(uint8_t *SDL_RESTRICT pch_ذريعو,
                                              size_t u_ذريعو_Stride,
                                              uint8_t *SDL_RESTRICT pch_هدف,
                                              size_t u_هدف_Stride,
                                              صحيح n_ويڪر,
                                              صحيح n_اوچائي,
                                              uint32_t w_ڪنجي,
                                              uint32_t w_ڪنجي_نقاب,
                                              uint32_t wActualRGBMask)
{
    أكد(0 == ((uintptr_t)pch_ذريعو & 0x03));
    أكد(0 == ((uintptr_t)pch_هدف & 0x03));

    طالما (n_اوچائي--) {
        sdl_sve_rgb32_stride_ڪنجي_no_alpha((uint32_t *)pch_ذريعو,
                                          (uint32_t *)pch_هدف,
                                          n_ويڪر,
                                          w_ڪنجي,
                                          w_ڪنجي_نقاب,
                                          wActualRGBMask);

        pch_ذريعو += u_ذريعو_Stride;
        pch_هدف += u_هدف_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
فراغ Blit4to4_ڪنجي_SVE2(SDL_BlitInfo *info)
{
    صحيح ويڪر = info->dst_w;
    صحيح اوچائي = info->dst_h;
    uint8_t *src = info->src;
    صحيح srcskip = info->src_skip;
    uint8_t *dst = info->dst;
    صحيح dstskip = info->dst_skip;

    ثابت SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    ثابت SDL_PixelFormatDetails *dstfmt = info->dst_fmt;

    // Set up some basic variables
    صحيح srcbpp = srcfmt->بائيٽون_في_pixel;
    صحيح dstbpp = dstfmt->بائيٽون_في_pixel;

    أكد(srcbpp == 4);
    أكد(dstbpp == 4);

    صحيح srcstride = srcskip + srcbpp * ويڪر;
    صحيح dststride = dstskip + dstbpp * ويڪر;

    uint32_t ckey = info->colorkey;
    uint32_t rgbmask = ~srcfmt->Amask;
    ckey &= rgbmask;

    إذا (dstfmt->Amask) {
        uint32_t opamask = ((uint32_t)info->a) << dstfmt->Ashift;
        /* RGBA: set alpha from info->a */
        sdl_sve_rgb32_ڪنجي_copy_alpha(src,
                                     srcstride,
                                     dst,
                                     dststride,
                                     ويڪر,
                                     اوچائي,
                                     ckey,
                                     rgbmask,
                                     opamask);
    } وإلا {
        /* RGBA->RGB: only copy rgb and set alpha to zero */
        uint32_t rgbmaskactual = srcfmt->Rmask | srcfmt->Gmask | srcfmt->Bmask;
        sdl_sve_rgb32_ڪنجي_no_alpha(src,
                                   srcstride,
                                   dst,
                                   dststride,
                                   ويڪر,
                                   اوچائي,
                                   ckey,
                                   rgbmask,
                                   rgbmaskactual);
    }
}

#جيڪڏهن_پورو /* SDL_SVE2_INTRINSICS */