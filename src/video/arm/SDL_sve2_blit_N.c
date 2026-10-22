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

#అన్తర్భావ "SDL_sve2_blit_N.h"
#అన్తర్భావ <assert.h>

#నిర్వచితమైతే SDL_SVE2_INTRINSICS

#నిర్వచనం_రద్దు sdl_sve_rgb32_blend_op_fill_alpha
#నిర్వచించు sdl_sve_rgb32_blend_op_fill_alpha(ma_alpha_chn_idx) \
    చేయి {                                                    \
        ఒకవేళ (sve_src_chn_idx == (ma_alpha_chn_idx)) {        \
            /* fill alpha */                                \
            sve_లక్ష్యం_u16 = svdup_u16(0xFF);               \
        } లేకపోతే {                                            \
            sve_లక్ష్యం_u16 = sve_ఆధారం_u16;                \
        }                                                   \
    } అయితే (0)

#నిర్వచనం_రద్దు sdl_sve_rgb32_blend_op_copy_alpha
#నిర్వచించు sdl_sve_rgb32_blend_op_copy_alpha(ma_alpha_chn_idx) \
    చేయి {                                                    \
        sve_లక్ష్యం_u16 = sve_ఆధారం_u16;                    \
    } అయితే (0)

#నిర్వచనం_రద్దు sdl_sve_rgb32_blend_గమ్యం_rgb565_op
#నిర్వచించు sdl_sve_rgb32_blend_గమ్యం_rgb565_op(ma_alpha_chn_idx) \
    చేయి {                                                   \
        sve_లక్ష్యం_u16 = sve_ఆధారం_u16;                   \
    } అయితే (0)

#అన్తర్భావ "SDL_sve2_swizzle.h"

SDL_TARGETING("arch=armv8-a+sve2")
శూన్య Blit8888to8888PixelSwizzleSVE2(SDL_BlitInfo *info)
{
    sdl_sve_8888_గమ్యం_8888_swizzle_dispatcher(info);
}

SDL_TARGETING("arch=armv8-a+sve2")
శూన్య Blit8888to565PixelSwizzleSVE2(SDL_BlitInfo *info)
{
    sdl_sve_rgb32_గమ్యం_rgb565_swizzle_dispatcher(info);
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
స్థిర అంతఃవరుస శూన్య sdl_sve_rgb16_stride_కీలకం(uint16_t *SDL_RESTRICT phw_ఆధారం,
                                            uint16_t *SDL_RESTRICT phw_లక్ష్యం,
                                            size_t uStride,
                                            uint16_t hw_కీలకం,
                                            uint16_t hw_కీలకం_ముసుగు)
{
    sdl_sve_stride_loop_u16(uStride, v_తోక_Pred)
    {
        svuint16_t v_ఆధారం = svld1_u16(v_తోక_Pred, phw_ఆధారం);
        svuint16_t v_లక్ష్యం = svld1_u16(v_తోక_Pred, phw_లక్ష్యం);

        svuint16_t v_ఆధారం_Masked = svand_n_u16_m(v_తోక_Pred,
                                                 v_ఆధారం,
                                                 hw_కీలకం_ముసుగు);
        v_లక్ష్యం = svsel_u16(svcmpeq_n_u16(v_తోక_Pred, v_ఆధారం_Masked, hw_కీలకం),
                            v_లక్ష్యం,
                            v_ఆధారం);

        svst1_u16(v_తోక_Pred, phw_లక్ష్యం, v_లక్ష్యం);

        phw_ఆధారం += sve_iteration_advance;
        phw_లక్ష్యం += sve_iteration_advance;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
స్థిర అంతఃవరుస శూన్య sdl_sve_rgb16_కీలకం(uint8_t *SDL_RESTRICT pch_ఆధారం,
                                     size_t u_ఆధారం_Stride,
                                     uint8_t *SDL_RESTRICT pch_లక్ష్యం,
                                     size_t u_లక్ష్యం_Stride,
                                     పూర్ణాంకం n_వెడల్పు,
                                     పూర్ణాంకం n_ఎత్తు,
                                     uint16_t hw_కీలకం,
                                     uint16_t hw_కీలకం_ముసుగు)
{
    ప్రతిజ్ఞా(0 == ((uintptr_t)pch_ఆధారం & 0x01));
    ప్రతిజ్ఞా(0 == ((uintptr_t)pch_లక్ష్యం & 0x01));

    అయితే (n_ఎత్తు--) {
        sdl_sve_rgb16_stride_కీలకం((uint16_t *)pch_ఆధారం,
                                 (uint16_t *)pch_లక్ష్యం,
                                 n_వెడల్పు,
                                 hw_కీలకం,
                                 hw_కీలకం_ముసుగు);

        pch_ఆధారం += u_ఆధారం_Stride;
        pch_లక్ష్యం += u_లక్ష్యం_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
శూన్య Blit2to2_కీలకం_SVE2(SDL_BlitInfo *info)
{
    పూర్ణాంకం వెడల్పు = info->dst_w;
    పూర్ణాంకం ఎత్తు = info->dst_h;
    uint8_t *src = info->src;
    పూర్ణాంకం srcskip = info->src_skip;
    uint8_t *dst = info->dst;
    పూర్ణాంకం dstskip = info->dst_skip;

    స్థిరరాశి SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    స్థిరరాశి SDL_PixelFormatDetails *dstfmt = info->dst_fmt;

    // Set up some basic variables
    పూర్ణాంకం srcbpp = srcfmt->బైట్లు_చొప్పున_pixel;
    పూర్ణాంకం dstbpp = dstfmt->బైట్లు_చొప్పున_pixel;

    ప్రతిజ్ఞా(srcbpp == 2);
    ప్రతిజ్ఞా(dstbpp == 2);

    పూర్ణాంకం srcstride = srcskip + srcbpp * వెడల్పు;
    పూర్ణాంకం dststride = dstskip + dstbpp * వెడల్పు;

    uint32_t ckey = info->colorkey;
    uint32_t rgbmask = ~srcfmt->Amask;
    ckey &= rgbmask;

    sdl_sve_rgb16_కీలకం(src,
                      srcstride,
                      dst,
                      dststride,
                      వెడల్పు,
                      ఎత్తు,
                      ckey,
                      rgbmask);
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
స్థిర అంతఃవరుస శూన్య sdl_sve_rgb32_stride_కీలకం_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ఆధారం,
    uint32_t *SDL_RESTRICT pw_లక్ష్యం,
    size_t uStride,
    uint32_t w_కీలకం,
    uint32_t w_కీలకం_ముసుగు,
    uint32_t w_Opacify_ముసుగు)
{
    sdl_sve_stride_loop_u32(uStride, v_తోక_Pred)
    {
        svuint32_t v_ఆధారం = svld1_u32(v_తోక_Pred, pw_ఆధారం);
        svuint32_t v_లక్ష్యం = svld1_u32(v_తోక_Pred, pw_లక్ష్యం);

        /*
            uint32_t opamask = ((uint32_t)info->a) << dstfmt->Ashift;
            ...
            if ((*src32 & rgbmask) != ckey) {
                *dst32 = *src32 | opamask;
            }
        */
        svuint32_t v_ఆధారం_Masked = svand_n_u32_m(v_తోక_Pred,
                                                 v_ఆధారం,
                                                 w_కీలకం_ముసుగు);
        v_లక్ష్యం = svsel_u32(svcmpeq_n_u32(v_తోక_Pred, v_ఆధారం_Masked, w_కీలకం),
                            v_లక్ష్యం,
                            svorr_n_u32_m(v_తోక_Pred, v_ఆధారం, w_Opacify_ముసుగు));

        svst1_u32(v_తోక_Pred, pw_లక్ష్యం, v_లక్ష్యం);

        pw_ఆధారం += sve_iteration_advance;
        pw_లక్ష్యం += sve_iteration_advance;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
స్థిర అంతఃవరుస శూన్య sdl_sve_rgb32_stride_కీలకం_no_alpha(
    uint32_t *SDL_RESTRICT pw_ఆధారం,
    uint32_t *SDL_RESTRICT pw_లక్ష్యం,
    size_t uStride,
    uint32_t w_కీలకం,
    uint32_t w_కీలకం_ముసుగు,
    uint32_t wActualRGBMask)
{
    sdl_sve_stride_loop_u32(uStride, v_తోక_Pred)
    {
        svuint32_t v_ఆధారం = svld1_u32(v_తోక_Pred, pw_ఆధారం);
        svuint32_t v_లక్ష్యం = svld1_u32(v_తోక_Pred, pw_లక్ష్యం);

        /*
            uint32_t rgbmaskactual = srcfmt->Rmask | srcfmt->Gmask | srcfmt->Bmask;
            ...
            if ((*src32 & rgbmask) != ckey) {
                *dst32 = *src32 & rgbmaskactual;
            }
        */
        svuint32_t v_ఆధారం_Masked = svand_n_u32_m(v_తోక_Pred,
                                                 v_ఆధారం,
                                                 w_కీలకం_ముసుగు);
        v_లక్ష్యం = svsel_u32(svcmpeq_n_u32(v_తోక_Pred, v_ఆధారం_Masked, w_కీలకం),
                            v_లక్ష్యం,
                            svand_n_u32_m(v_తోక_Pred, v_ఆధారం, wActualRGBMask));

        svst1_u32(v_తోక_Pred, pw_లక్ష్యం, v_లక్ష్యం);

        pw_ఆధారం += sve_iteration_advance;
        pw_లక్ష్యం += sve_iteration_advance;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
స్థిర అంతఃవరుస శూన్య sdl_sve_rgb32_కీలకం_copy_alpha(uint8_t *SDL_RESTRICT pch_ఆధారం,
                                                size_t u_ఆధారం_Stride,
                                                uint8_t *SDL_RESTRICT pch_లక్ష్యం,
                                                size_t u_లక్ష్యం_Stride,
                                                పూర్ణాంకం n_వెడల్పు,
                                                పూర్ణాంకం n_ఎత్తు,
                                                uint32_t w_కీలకం,
                                                uint32_t w_కీలకం_ముసుగు,
                                                uint32_t w_Opacify_ముసుగు)
{
    ప్రతిజ్ఞా(0 == ((uintptr_t)pch_ఆధారం & 0x03));
    ప్రతిజ్ఞా(0 == ((uintptr_t)pch_లక్ష్యం & 0x03));

    అయితే (n_ఎత్తు--) {
        sdl_sve_rgb32_stride_కీలకం_copy_alpha((uint32_t *)pch_ఆధారం,
                                            (uint32_t *)pch_లక్ష్యం,
                                            n_వెడల్పు,
                                            w_కీలకం,
                                            w_కీలకం_ముసుగు,
                                            w_Opacify_ముసుగు);

        pch_ఆధారం += u_ఆధారం_Stride;
        pch_లక్ష్యం += u_లక్ష్యం_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
స్థిర అంతఃవరుస శూన్య sdl_sve_rgb32_కీలకం_no_alpha(uint8_t *SDL_RESTRICT pch_ఆధారం,
                                              size_t u_ఆధారం_Stride,
                                              uint8_t *SDL_RESTRICT pch_లక్ష్యం,
                                              size_t u_లక్ష్యం_Stride,
                                              పూర్ణాంకం n_వెడల్పు,
                                              పూర్ణాంకం n_ఎత్తు,
                                              uint32_t w_కీలకం,
                                              uint32_t w_కీలకం_ముసుగు,
                                              uint32_t wActualRGBMask)
{
    ప్రతిజ్ఞా(0 == ((uintptr_t)pch_ఆధారం & 0x03));
    ప్రతిజ్ఞా(0 == ((uintptr_t)pch_లక్ష్యం & 0x03));

    అయితే (n_ఎత్తు--) {
        sdl_sve_rgb32_stride_కీలకం_no_alpha((uint32_t *)pch_ఆధారం,
                                          (uint32_t *)pch_లక్ష్యం,
                                          n_వెడల్పు,
                                          w_కీలకం,
                                          w_కీలకం_ముసుగు,
                                          wActualRGBMask);

        pch_ఆధారం += u_ఆధారం_Stride;
        pch_లక్ష్యం += u_లక్ష్యం_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
శూన్య Blit4to4_కీలకం_SVE2(SDL_BlitInfo *info)
{
    పూర్ణాంకం వెడల్పు = info->dst_w;
    పూర్ణాంకం ఎత్తు = info->dst_h;
    uint8_t *src = info->src;
    పూర్ణాంకం srcskip = info->src_skip;
    uint8_t *dst = info->dst;
    పూర్ణాంకం dstskip = info->dst_skip;

    స్థిరరాశి SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    స్థిరరాశి SDL_PixelFormatDetails *dstfmt = info->dst_fmt;

    // Set up some basic variables
    పూర్ణాంకం srcbpp = srcfmt->బైట్లు_చొప్పున_pixel;
    పూర్ణాంకం dstbpp = dstfmt->బైట్లు_చొప్పున_pixel;

    ప్రతిజ్ఞా(srcbpp == 4);
    ప్రతిజ్ఞా(dstbpp == 4);

    పూర్ణాంకం srcstride = srcskip + srcbpp * వెడల్పు;
    పూర్ణాంకం dststride = dstskip + dstbpp * వెడల్పు;

    uint32_t ckey = info->colorkey;
    uint32_t rgbmask = ~srcfmt->Amask;
    ckey &= rgbmask;

    ఒకవేళ (dstfmt->Amask) {
        uint32_t opamask = ((uint32_t)info->a) << dstfmt->Ashift;
        /* RGBA: set alpha from info->a */
        sdl_sve_rgb32_కీలకం_copy_alpha(src,
                                     srcstride,
                                     dst,
                                     dststride,
                                     వెడల్పు,
                                     ఎత్తు,
                                     ckey,
                                     rgbmask,
                                     opamask);
    } లేకపోతే {
        /* RGBA->RGB: only copy rgb and set alpha to zero */
        uint32_t rgbmaskactual = srcfmt->Rmask | srcfmt->Gmask | srcfmt->Bmask;
        sdl_sve_rgb32_కీలకం_no_alpha(src,
                                   srcstride,
                                   dst,
                                   dststride,
                                   వెడల్పు,
                                   ఎత్తు,
                                   ckey,
                                   rgbmask,
                                   rgbmaskactual);
    }
}

#అయితే_ముగింపు /* SDL_SVE2_INTRINSICS */