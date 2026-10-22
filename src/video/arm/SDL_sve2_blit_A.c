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

#అన్తర్భావ "SDL_sve2_blit_A.h"
#అన్తర్భావ <assert.h>

#నిర్వచితమైతే SDL_SVE2_INTRINSICS

#నిర్వచనం_రద్దు sdl_sve_rgb32_blend_op_fill_alpha
#నిర్వచించు sdl_sve_rgb32_blend_op_fill_alpha(ma_alpha_chn_idx)              \
    ఒకవేళ (sve_src_chn_idx == (ma_alpha_chn_idx)) {                         \
        /* fill alpha */                                                 \
        sve_లక్ష్యం_u16 = svdup_u16(0xFF);                                \
    } లేకపోతే {                                                             \
        svuint16_t v_ముసుగు = svget4(sve_ఆధారం_u16x4, (ma_alpha_chn_idx)); \
        sve_లక్ష్యం_u16 = sdl_sve_chn_blend_with_ముసుగు(sve_ఆధారం_u16,     \
                                                     sve_లక్ష్యం_u16,     \
                                                     v_ముసుగు);             \
    }

#నిర్వచనం_రద్దు sdl_sve_rgb32_blend_op_copy_alpha
#నిర్వచించు sdl_sve_rgb32_blend_op_copy_alpha(ma_alpha_chn_idx)              \
    ఒకవేళ (sve_src_chn_idx == (ma_alpha_chn_idx)) {                         \
        svuint16_t v_ముసుగు = svget4(sve_ఆధారం_u16x4, (ma_alpha_chn_idx)); \
        sve_లక్ష్యం_u16 = sdl_sve_chn_blend_with_ముసుగు(svdup_u16(0xFF),    \
                                                     sve_లక్ష్యం_u16,     \
                                                     v_ముసుగు);             \
    } లేకపోతే {                                                             \
        svuint16_t v_ముసుగు = svget4(sve_ఆధారం_u16x4, (ma_alpha_chn_idx)); \
        sve_లక్ష్యం_u16 = sdl_sve_chn_blend_with_ముసుగు(sve_ఆధారం_u16,     \
                                                     sve_లక్ష్యం_u16,     \
                                                     v_ముసుగు);             \
    }

#నిర్వచనం_రద్దు sdl_sve_rgb32_blend_గమ్యం_rgb565_op
#నిర్వచించు sdl_sve_rgb32_blend_గమ్యం_rgb565_op(ma_alpha_chn_idx)                \
    చేయి {                                                                  \
        svuint16_t v_ముసుగు = svget4(sve_ఆధారం_u16x4, (ma_alpha_chn_idx));  \
        sve_లక్ష్యం_u16 = sdl_sve_chn_blend_with_ముసుగు_fast(sve_ఆధారం_u16, \
                                                          sve_లక్ష్యం_u16, \
                                                          v_ముసుగు);         \
    } అయితే (0)

#అన్తర్భావ "SDL_sve2_swizzle.h"

/*-----------------------------------------------------------------------------*
 * Swizzle Blend with Alpha                                                    *
 *-----------------------------------------------------------------------------*/
SDL_TARGETING("arch=armv8-a+sve2")
శూన్య Blit8888to8888PixelAlphaSwizzleSVE2(SDL_BlitInfo *info)
{
    స్థిరరాశి SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    ప్రతిజ్ఞా(0 != srcfmt->Amask);
    (శూన్య)srcfmt;

    sdl_sve_8888_గమ్యం_8888_swizzle_dispatcher(info);
}

SDL_TARGETING("arch=armv8-a+sve2")
శూన్య Blit8888to565PixelAlphaSwizzleSVE2(SDL_BlitInfo *info)
{
    sdl_sve_rgb32_గమ్యం_rgb565_swizzle_dispatcher(info);
}

SDL_TARGETING("arch=armv8-a+sve2")
size_t SDL_Get_SVEVector_కొలత(శూన్య)
{
    తిరిగి svlen(svundef_u8()) * 8;
}

/*-----------------------------------------------------------------------------*
 * RGB565 Blend with Surface Alpha                                             *
 *-----------------------------------------------------------------------------*/
SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
స్థిర అంతఃవరుస శూన్య sdl_sve_rgb565_stride_blend_with_opacity(uint16_t *SDL_RESTRICT phw_ఆధారం,
                                                            uint16_t *SDL_RESTRICT phw_లక్ష్యం,
                                                            size_t uStride,
                                                            uint16_t hwOpacity)
{
    sdl_sve_stride_loop_u16(uStride, v_తోక_Pred)
    {

        svuint16x3_t vSource16x3 =
            sdl_sve_rgb565_unpack(svld1_u16(v_తోక_Pred, phw_ఆధారం));

        svuint16x3_t vTarget16x3 =
            sdl_sve_rgb565_unpack(svld1_u16(v_తోక_Pred, phw_లక్ష్యం));

        sdl_sve_pixel_ccc_foreach_chn(
            vSource16x3,
            vTarget16x3,
            {
                sve_లక్ష్యం_u16 = sdl_sve_chn_blend_with_opacity_fast(
                    sve_ఆధారం_u16,
                    sve_లక్ష్యం_u16,
                    hwOpacity);
            });

        svst1_u16(v_తోక_Pred, phw_లక్ష్యం, sdl_sve_rgb565_pack(vTarget16x3));

        phw_ఆధారం += sve_iteration_advance;
        phw_లక్ష్యం += sve_iteration_advance;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
స్థిర అంతఃవరుస శూన్య sdl_sve_rgb565_blend_with_opacity(uint8_t *SDL_RESTRICT pch_ఆధారం,
                                                     size_t u_ఆధారం_Stride,
                                                     uint8_t *SDL_RESTRICT pch_లక్ష్యం,
                                                     size_t u_లక్ష్యం_Stride,
                                                     పూర్ణాంకం n_వెడల్పు,
                                                     పూర్ణాంకం n_ఎత్తు,
                                                     uint16_t hwOpacity)
{
    hwOpacity += hwOpacity == 255;
    ప్రతిజ్ఞా(0 == ((uintptr_t)pch_ఆధారం & 0x01));
    ప్రతిజ్ఞా(0 == ((uintptr_t)pch_లక్ష్యం & 0x01));

    అయితే (n_ఎత్తు--) {

        sdl_sve_rgb565_stride_blend_with_opacity((uint16_t *)pch_ఆధారం,
                                                 (uint16_t *)pch_లక్ష్యం,
                                                 n_వెడల్పు,
                                                 hwOpacity);

        pch_ఆధారం += u_ఆధారం_Stride;
        pch_లక్ష్యం += u_లక్ష్యం_Stride;
    }
}

// fast RGB565->RGB565 blending with surface alpha
SDL_TARGETING("arch=armv8-a+sve2")
శూన్య Blit565to565SurfaceAlphaSVE2(SDL_BlitInfo *info)
{
    uint16_t alpha = info->a;

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

    sdl_sve_rgb565_blend_with_opacity(src,
                                      srcstride,
                                      dst,
                                      dststride,
                                      వెడల్పు,
                                      ఎత్తు,
                                      alpha);
}

#అయితే_ముగింపు /* SDL_SVE2_INTRINSICS */