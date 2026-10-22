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

#ଅନ୍ତର୍ଭାଵ "SDL_sve2_blit_N.h"
#ଅନ୍ତର୍ଭାଵ <assert.h>

#ifdef SDL_SVE2_INTRINSICS

#undef sdl_sve_rgb32_blend_op_fill_alpha
#define sdl_sve_rgb32_blend_op_fill_alpha(ma_alpha_chn_idx) \
    କର {                                                    \
        ଯଦି (sve_src_chn_idx == (ma_alpha_chn_idx)) {        \
            /* fill alpha */                                \
            sve_target_u16 = svdup_u16(0xFF);               \
        } ଅନ୍ୟଥା {                                            \
            sve_target_u16 = sve_source_u16;                \
        }                                                   \
    } ଯେତେବେଳେ (0)

#undef sdl_sve_rgb32_blend_op_copy_alpha
#define sdl_sve_rgb32_blend_op_copy_alpha(ma_alpha_chn_idx) \
    କର {                                                    \
        sve_target_u16 = sve_source_u16;                    \
    } ଯେତେବେଳେ (0)

#undef sdl_sve_rgb32_blend_to_rgb565_op
#define sdl_sve_rgb32_blend_to_rgb565_op(ma_alpha_chn_idx) \
    କର {                                                   \
        sve_target_u16 = sve_source_u16;                   \
    } ଯେତେବେଳେ (0)

#ଅନ୍ତର୍ଭାଵ "SDL_sve2_swizzle.h"

SDL_TARGETING("arch=armv8-a+sve2")
ଶୂନ୍ୟ Blit8888to8888PixelSwizzleSVE2(SDL_BlitInfo *info)
{
    sdl_sve_8888_to_8888_swizzle_dispatcher(info);
}

SDL_TARGETING("arch=armv8-a+sve2")
ଶୂନ୍ୟ Blit8888to565PixelSwizzleSVE2(SDL_BlitInfo *info)
{
    sdl_sve_rgb32_to_rgb565_swizzle_dispatcher(info);
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ସ୍ଥିର ଧାଡ଼ିଭିତରେ ଶୂନ୍ୟ sdl_sve_rgb16_stride_ଚାବି(uint16_t *SDL_RESTRICT phwSource,
                                            uint16_t *SDL_RESTRICT phwTarget,
                                            size_t uStride,
                                            uint16_t hw_ଚାବି,
                                            uint16_t hw_ଚାବି_Mask)
{
    sdl_sve_stride_loop_u16(uStride, vTailPred)
    {
        svuint16_t vSource = svld1_u16(vTailPred, phwSource);
        svuint16_t vTarget = svld1_u16(vTailPred, phwTarget);

        svuint16_t vSourceMasked = svand_n_u16_m(vTailPred,
                                                 vSource,
                                                 hw_ଚାବି_Mask);
        vTarget = svsel_u16(svcmpeq_n_u16(vTailPred, vSourceMasked, hw_ଚାବି),
                            vTarget,
                            vSource);

        svst1_u16(vTailPred, phwTarget, vTarget);

        phwSource += sve_iteration_advance;
        phwTarget += sve_iteration_advance;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ସ୍ଥିର ଧାଡ଼ିଭିତରେ ଶୂନ୍ୟ sdl_sve_rgb16_ଚାବି(uint8_t *SDL_RESTRICT pchSource,
                                     size_t uSourceStride,
                                     uint8_t *SDL_RESTRICT pchTarget,
                                     size_t uTargetStride,
                                     ପୂର୍ଣ୍ଣସଂଖ୍ୟା nWidth,
                                     ପୂର୍ଣ୍ଣସଂଖ୍ୟା nHeight,
                                     uint16_t hw_ଚାବି,
                                     uint16_t hw_ଚାବି_Mask)
{
    ପ୍ରତିଜ୍ଞା(0 == ((uintptr_t)pchSource & 0x01));
    ପ୍ରତିଜ୍ଞା(0 == ((uintptr_t)pchTarget & 0x01));

    ଯେତେବେଳେ (nHeight--) {
        sdl_sve_rgb16_stride_ଚାବି((uint16_t *)pchSource,
                                 (uint16_t *)pchTarget,
                                 nWidth,
                                 hw_ଚାବି,
                                 hw_ଚାବି_Mask);

        pchSource += uSourceStride;
        pchTarget += uTargetStride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ଶୂନ୍ୟ Blit2to2_ଚାବି_SVE2(SDL_BlitInfo *info)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା width = info->dst_w;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା height = info->dst_h;
    uint8_t *src = info->src;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା srcskip = info->src_skip;
    uint8_t *dst = info->dst;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା dstskip = info->dst_skip;

    ଅଚଳ SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    ଅଚଳ SDL_PixelFormatDetails *dstfmt = info->dst_fmt;

    // Set up some basic variables
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା srcbpp = srcfmt->bytes_per_pixel;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା dstbpp = dstfmt->bytes_per_pixel;

    ପ୍ରତିଜ୍ଞା(srcbpp == 2);
    ପ୍ରତିଜ୍ଞା(dstbpp == 2);

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା srcstride = srcskip + srcbpp * width;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା dststride = dstskip + dstbpp * width;

    uint32_t ckey = info->colorkey;
    uint32_t rgbmask = ~srcfmt->Amask;
    ckey &= rgbmask;

    sdl_sve_rgb16_ଚାବି(src,
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
ସ୍ଥିର ଧାଡ଼ିଭିତରେ ଶୂନ୍ୟ sdl_sve_rgb32_stride_ଚାବି_copy_alpha(
    uint32_t *SDL_RESTRICT pwSource,
    uint32_t *SDL_RESTRICT pwTarget,
    size_t uStride,
    uint32_t w_ଚାବି,
    uint32_t w_ଚାବି_Mask,
    uint32_t wOpacifyMask)
{
    sdl_sve_stride_loop_u32(uStride, vTailPred)
    {
        svuint32_t vSource = svld1_u32(vTailPred, pwSource);
        svuint32_t vTarget = svld1_u32(vTailPred, pwTarget);

        /*
            uint32_t opamask = ((uint32_t)info->a) << dstfmt->Ashift;
            ...
            if ((*src32 & rgbmask) != ckey) {
                *dst32 = *src32 | opamask;
            }
        */
        svuint32_t vSourceMasked = svand_n_u32_m(vTailPred,
                                                 vSource,
                                                 w_ଚାବି_Mask);
        vTarget = svsel_u32(svcmpeq_n_u32(vTailPred, vSourceMasked, w_ଚାବି),
                            vTarget,
                            svorr_n_u32_m(vTailPred, vSource, wOpacifyMask));

        svst1_u32(vTailPred, pwTarget, vTarget);

        pwSource += sve_iteration_advance;
        pwTarget += sve_iteration_advance;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ସ୍ଥିର ଧାଡ଼ିଭିତରେ ଶୂନ୍ୟ sdl_sve_rgb32_stride_ଚାବି_no_alpha(
    uint32_t *SDL_RESTRICT pwSource,
    uint32_t *SDL_RESTRICT pwTarget,
    size_t uStride,
    uint32_t w_ଚାବି,
    uint32_t w_ଚାବି_Mask,
    uint32_t wActualRGBMask)
{
    sdl_sve_stride_loop_u32(uStride, vTailPred)
    {
        svuint32_t vSource = svld1_u32(vTailPred, pwSource);
        svuint32_t vTarget = svld1_u32(vTailPred, pwTarget);

        /*
            uint32_t rgbmaskactual = srcfmt->Rmask | srcfmt->Gmask | srcfmt->Bmask;
            ...
            if ((*src32 & rgbmask) != ckey) {
                *dst32 = *src32 & rgbmaskactual;
            }
        */
        svuint32_t vSourceMasked = svand_n_u32_m(vTailPred,
                                                 vSource,
                                                 w_ଚାବି_Mask);
        vTarget = svsel_u32(svcmpeq_n_u32(vTailPred, vSourceMasked, w_ଚାବି),
                            vTarget,
                            svand_n_u32_m(vTailPred, vSource, wActualRGBMask));

        svst1_u32(vTailPred, pwTarget, vTarget);

        pwSource += sve_iteration_advance;
        pwTarget += sve_iteration_advance;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ସ୍ଥିର ଧାଡ଼ିଭିତରେ ଶୂନ୍ୟ sdl_sve_rgb32_ଚାବି_copy_alpha(uint8_t *SDL_RESTRICT pchSource,
                                                size_t uSourceStride,
                                                uint8_t *SDL_RESTRICT pchTarget,
                                                size_t uTargetStride,
                                                ପୂର୍ଣ୍ଣସଂଖ୍ୟା nWidth,
                                                ପୂର୍ଣ୍ଣସଂଖ୍ୟା nHeight,
                                                uint32_t w_ଚାବି,
                                                uint32_t w_ଚାବି_Mask,
                                                uint32_t wOpacifyMask)
{
    ପ୍ରତିଜ୍ଞା(0 == ((uintptr_t)pchSource & 0x03));
    ପ୍ରତିଜ୍ଞା(0 == ((uintptr_t)pchTarget & 0x03));

    ଯେତେବେଳେ (nHeight--) {
        sdl_sve_rgb32_stride_ଚାବି_copy_alpha((uint32_t *)pchSource,
                                            (uint32_t *)pchTarget,
                                            nWidth,
                                            w_ଚାବି,
                                            w_ଚାବି_Mask,
                                            wOpacifyMask);

        pchSource += uSourceStride;
        pchTarget += uTargetStride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ସ୍ଥିର ଧାଡ଼ିଭିତରେ ଶୂନ୍ୟ sdl_sve_rgb32_ଚାବି_no_alpha(uint8_t *SDL_RESTRICT pchSource,
                                              size_t uSourceStride,
                                              uint8_t *SDL_RESTRICT pchTarget,
                                              size_t uTargetStride,
                                              ପୂର୍ଣ୍ଣସଂଖ୍ୟା nWidth,
                                              ପୂର୍ଣ୍ଣସଂଖ୍ୟା nHeight,
                                              uint32_t w_ଚାବି,
                                              uint32_t w_ଚାବି_Mask,
                                              uint32_t wActualRGBMask)
{
    ପ୍ରତିଜ୍ଞା(0 == ((uintptr_t)pchSource & 0x03));
    ପ୍ରତିଜ୍ଞା(0 == ((uintptr_t)pchTarget & 0x03));

    ଯେତେବେଳେ (nHeight--) {
        sdl_sve_rgb32_stride_ଚାବି_no_alpha((uint32_t *)pchSource,
                                          (uint32_t *)pchTarget,
                                          nWidth,
                                          w_ଚାବି,
                                          w_ଚାବି_Mask,
                                          wActualRGBMask);

        pchSource += uSourceStride;
        pchTarget += uTargetStride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ଶୂନ୍ୟ Blit4to4_ଚାବି_SVE2(SDL_BlitInfo *info)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା width = info->dst_w;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା height = info->dst_h;
    uint8_t *src = info->src;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା srcskip = info->src_skip;
    uint8_t *dst = info->dst;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା dstskip = info->dst_skip;

    ଅଚଳ SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    ଅଚଳ SDL_PixelFormatDetails *dstfmt = info->dst_fmt;

    // Set up some basic variables
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା srcbpp = srcfmt->bytes_per_pixel;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା dstbpp = dstfmt->bytes_per_pixel;

    ପ୍ରତିଜ୍ଞା(srcbpp == 4);
    ପ୍ରତିଜ୍ଞା(dstbpp == 4);

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା srcstride = srcskip + srcbpp * width;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା dststride = dstskip + dstbpp * width;

    uint32_t ckey = info->colorkey;
    uint32_t rgbmask = ~srcfmt->Amask;
    ckey &= rgbmask;

    ଯଦି (dstfmt->Amask) {
        uint32_t opamask = ((uint32_t)info->a) << dstfmt->Ashift;
        /* RGBA: set alpha from info->a */
        sdl_sve_rgb32_ଚାବି_copy_alpha(src,
                                     srcstride,
                                     dst,
                                     dststride,
                                     width,
                                     height,
                                     ckey,
                                     rgbmask,
                                     opamask);
    } ଅନ୍ୟଥା {
        /* RGBA->RGB: only copy rgb and set alpha to zero */
        uint32_t rgbmaskactual = srcfmt->Rmask | srcfmt->Gmask | srcfmt->Bmask;
        sdl_sve_rgb32_ଚାବି_no_alpha(src,
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

#endif /* SDL_SVE2_INTRINSICS */