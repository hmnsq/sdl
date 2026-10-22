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

#समावेश "SDL_sve2_blit_N.h"
#समावेश <assert.h>

#अगर_घोषित SDL_SVE2_INTRINSICS

#अघोषित sdl_sve_rgb32_blend_op_fill_alpha
#घोषणा sdl_sve_rgb32_blend_op_fill_alpha(ma_alpha_chn_idx) \
    करो {                                                    \
        अगर (sve_src_chn_idx == (ma_alpha_chn_idx)) {        \
            /* fill alpha */                                \
            sve_target_u16 = svdup_u16(0xFF);               \
        } अन्यथा {                                            \
            sve_target_u16 = sve_source_u16;                \
        }                                                   \
    } जबतक (0)

#अघोषित sdl_sve_rgb32_blend_op_copy_alpha
#घोषणा sdl_sve_rgb32_blend_op_copy_alpha(ma_alpha_chn_idx) \
    करो {                                                    \
        sve_target_u16 = sve_source_u16;                    \
    } जबतक (0)

#अघोषित sdl_sve_rgb32_blend_to_rgb565_op
#घोषणा sdl_sve_rgb32_blend_to_rgb565_op(ma_alpha_chn_idx) \
    करो {                                                   \
        sve_target_u16 = sve_source_u16;                   \
    } जबतक (0)

#समावेश "SDL_sve2_swizzle.h"

SDL_TARGETING("arch=armv8-a+sve2")
व्योम Blit8888to8888PixelSwizzleSVE2(SDL_BlitInfo *info)
{
    sdl_sve_8888_to_8888_swizzle_dispatcher(info);
}

SDL_TARGETING("arch=armv8-a+sve2")
व्योम Blit8888to565PixelSwizzleSVE2(SDL_BlitInfo *info)
{
    sdl_sve_rgb32_to_rgb565_swizzle_dispatcher(info);
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
अटल अंतरभूत व्योम sdl_sve_rgb16_stride_कुंजी(uint16_t *SDL_RESTRICT phwSource,
                                            uint16_t *SDL_RESTRICT phwTarget,
                                            माप_प्रकार uStride,
                                            uint16_t hw_कुंजी,
                                            uint16_t hw_कुंजी_Mask)
{
    sdl_sve_stride_loop_u16(uStride, v_पुच्छ_Pred)
    {
        svuint16_t vSource = svld1_u16(v_पुच्छ_Pred, phwSource);
        svuint16_t vTarget = svld1_u16(v_पुच्छ_Pred, phwTarget);

        svuint16_t vSourceMasked = svand_n_u16_m(v_पुच्छ_Pred,
                                                 vSource,
                                                 hw_कुंजी_Mask);
        vTarget = svsel_u16(svcmpeq_n_u16(v_पुच्छ_Pred, vSourceMasked, hw_कुंजी),
                            vTarget,
                            vSource);

        svst1_u16(v_पुच्छ_Pred, phwTarget, vTarget);

        phwSource += sve_iteration_advance;
        phwTarget += sve_iteration_advance;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
अटल अंतरभूत व्योम sdl_sve_rgb16_कुंजी(uint8_t *SDL_RESTRICT pchSource,
                                     माप_प्रकार uSourceStride,
                                     uint8_t *SDL_RESTRICT pchTarget,
                                     माप_प्रकार uTargetStride,
                                     पूर्णांक nWidth,
                                     पूर्णांक nHeight,
                                     uint16_t hw_कुंजी,
                                     uint16_t hw_कुंजी_Mask)
{
    निश्चित(0 == ((uintptr_t)pchSource & 0x01));
    निश्चित(0 == ((uintptr_t)pchTarget & 0x01));

    जबतक (nHeight--) {
        sdl_sve_rgb16_stride_कुंजी((uint16_t *)pchSource,
                                 (uint16_t *)pchTarget,
                                 nWidth,
                                 hw_कुंजी,
                                 hw_कुंजी_Mask);

        pchSource += uSourceStride;
        pchTarget += uTargetStride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
व्योम Blit2to2_कुंजी_SVE2(SDL_BlitInfo *info)
{
    पूर्णांक width = info->dst_w;
    पूर्णांक height = info->dst_h;
    uint8_t *src = info->src;
    पूर्णांक srcskip = info->src_skip;
    uint8_t *dst = info->dst;
    पूर्णांक dstskip = info->dst_skip;

    स्थिर SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    स्थिर SDL_PixelFormatDetails *dstfmt = info->dst_fmt;

    // Set up some basic variables
    पूर्णांक srcbpp = srcfmt->bytes_per_pixel;
    पूर्णांक dstbpp = dstfmt->bytes_per_pixel;

    निश्चित(srcbpp == 2);
    निश्चित(dstbpp == 2);

    पूर्णांक srcstride = srcskip + srcbpp * width;
    पूर्णांक dststride = dstskip + dstbpp * width;

    uint32_t ckey = info->colorkey;
    uint32_t rgbmask = ~srcfmt->Amask;
    ckey &= rgbmask;

    sdl_sve_rgb16_कुंजी(src,
                      srcstride,
                      dst,
                      dststride,
                      width,
                      height,
                      ckey,
                      rgbmask);
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
अटल अंतरभूत व्योम sdl_sve_rgb32_stride_कुंजी_copy_alpha(
    uint32_t *SDL_RESTRICT pwSource,
    uint32_t *SDL_RESTRICT pwTarget,
    माप_प्रकार uStride,
    uint32_t w_कुंजी,
    uint32_t w_कुंजी_Mask,
    uint32_t wOpacifyMask)
{
    sdl_sve_stride_loop_u32(uStride, v_पुच्छ_Pred)
    {
        svuint32_t vSource = svld1_u32(v_पुच्छ_Pred, pwSource);
        svuint32_t vTarget = svld1_u32(v_पुच्छ_Pred, pwTarget);

        /*
            uint32_t opamask = ((uint32_t)info->a) << dstfmt->Ashift;
            ...
            if ((*src32 & rgbmask) != ckey) {
                *dst32 = *src32 | opamask;
            }
        */
        svuint32_t vSourceMasked = svand_n_u32_m(v_पुच्छ_Pred,
                                                 vSource,
                                                 w_कुंजी_Mask);
        vTarget = svsel_u32(svcmpeq_n_u32(v_पुच्छ_Pred, vSourceMasked, w_कुंजी),
                            vTarget,
                            svorr_n_u32_m(v_पुच्छ_Pred, vSource, wOpacifyMask));

        svst1_u32(v_पुच्छ_Pred, pwTarget, vTarget);

        pwSource += sve_iteration_advance;
        pwTarget += sve_iteration_advance;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
अटल अंतरभूत व्योम sdl_sve_rgb32_stride_कुंजी_no_alpha(
    uint32_t *SDL_RESTRICT pwSource,
    uint32_t *SDL_RESTRICT pwTarget,
    माप_प्रकार uStride,
    uint32_t w_कुंजी,
    uint32_t w_कुंजी_Mask,
    uint32_t wActualRGBMask)
{
    sdl_sve_stride_loop_u32(uStride, v_पुच्छ_Pred)
    {
        svuint32_t vSource = svld1_u32(v_पुच्छ_Pred, pwSource);
        svuint32_t vTarget = svld1_u32(v_पुच्छ_Pred, pwTarget);

        /*
            uint32_t rgbmaskactual = srcfmt->Rmask | srcfmt->Gmask | srcfmt->Bmask;
            ...
            if ((*src32 & rgbmask) != ckey) {
                *dst32 = *src32 & rgbmaskactual;
            }
        */
        svuint32_t vSourceMasked = svand_n_u32_m(v_पुच्छ_Pred,
                                                 vSource,
                                                 w_कुंजी_Mask);
        vTarget = svsel_u32(svcmpeq_n_u32(v_पुच्छ_Pred, vSourceMasked, w_कुंजी),
                            vTarget,
                            svand_n_u32_m(v_पुच्छ_Pred, vSource, wActualRGBMask));

        svst1_u32(v_पुच्छ_Pred, pwTarget, vTarget);

        pwSource += sve_iteration_advance;
        pwTarget += sve_iteration_advance;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
अटल अंतरभूत व्योम sdl_sve_rgb32_कुंजी_copy_alpha(uint8_t *SDL_RESTRICT pchSource,
                                                माप_प्रकार uSourceStride,
                                                uint8_t *SDL_RESTRICT pchTarget,
                                                माप_प्रकार uTargetStride,
                                                पूर्णांक nWidth,
                                                पूर्णांक nHeight,
                                                uint32_t w_कुंजी,
                                                uint32_t w_कुंजी_Mask,
                                                uint32_t wOpacifyMask)
{
    निश्चित(0 == ((uintptr_t)pchSource & 0x03));
    निश्चित(0 == ((uintptr_t)pchTarget & 0x03));

    जबतक (nHeight--) {
        sdl_sve_rgb32_stride_कुंजी_copy_alpha((uint32_t *)pchSource,
                                            (uint32_t *)pchTarget,
                                            nWidth,
                                            w_कुंजी,
                                            w_कुंजी_Mask,
                                            wOpacifyMask);

        pchSource += uSourceStride;
        pchTarget += uTargetStride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
अटल अंतरभूत व्योम sdl_sve_rgb32_कुंजी_no_alpha(uint8_t *SDL_RESTRICT pchSource,
                                              माप_प्रकार uSourceStride,
                                              uint8_t *SDL_RESTRICT pchTarget,
                                              माप_प्रकार uTargetStride,
                                              पूर्णांक nWidth,
                                              पूर्णांक nHeight,
                                              uint32_t w_कुंजी,
                                              uint32_t w_कुंजी_Mask,
                                              uint32_t wActualRGBMask)
{
    निश्चित(0 == ((uintptr_t)pchSource & 0x03));
    निश्चित(0 == ((uintptr_t)pchTarget & 0x03));

    जबतक (nHeight--) {
        sdl_sve_rgb32_stride_कुंजी_no_alpha((uint32_t *)pchSource,
                                          (uint32_t *)pchTarget,
                                          nWidth,
                                          w_कुंजी,
                                          w_कुंजी_Mask,
                                          wActualRGBMask);

        pchSource += uSourceStride;
        pchTarget += uTargetStride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
व्योम Blit4to4_कुंजी_SVE2(SDL_BlitInfo *info)
{
    पूर्णांक width = info->dst_w;
    पूर्णांक height = info->dst_h;
    uint8_t *src = info->src;
    पूर्णांक srcskip = info->src_skip;
    uint8_t *dst = info->dst;
    पूर्णांक dstskip = info->dst_skip;

    स्थिर SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    स्थिर SDL_PixelFormatDetails *dstfmt = info->dst_fmt;

    // Set up some basic variables
    पूर्णांक srcbpp = srcfmt->bytes_per_pixel;
    पूर्णांक dstbpp = dstfmt->bytes_per_pixel;

    निश्चित(srcbpp == 4);
    निश्चित(dstbpp == 4);

    पूर्णांक srcstride = srcskip + srcbpp * width;
    पूर्णांक dststride = dstskip + dstbpp * width;

    uint32_t ckey = info->colorkey;
    uint32_t rgbmask = ~srcfmt->Amask;
    ckey &= rgbmask;

    अगर (dstfmt->Amask) {
        uint32_t opamask = ((uint32_t)info->a) << dstfmt->Ashift;
        /* RGBA: set alpha from info->a */
        sdl_sve_rgb32_कुंजी_copy_alpha(src,
                                     srcstride,
                                     dst,
                                     dststride,
                                     width,
                                     height,
                                     ckey,
                                     rgbmask,
                                     opamask);
    } अन्यथा {
        /* RGBA->RGB: only copy rgb and set alpha to zero */
        uint32_t rgbmaskactual = srcfmt->Rmask | srcfmt->Gmask | srcfmt->Bmask;
        sdl_sve_rgb32_कुंजी_no_alpha(src,
                                   srcstride,
                                   dst,
                                   dststride,
                                   width,
                                   height,
                                   ckey,
                                   rgbmask,
                                   rgbmaskactual);
    }
}

#पूर्ण_अगर /* SDL_SVE2_INTRINSICS */