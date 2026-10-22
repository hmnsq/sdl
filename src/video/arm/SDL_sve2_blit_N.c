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

#অন্তর্ভাব "SDL_sve2_blit_N.h"
#অন্তর্ভাব <assert.h>

#ifdef SDL_SVE2_INTRINSICS

#undef sdl_sve_rgb32_blend_op_fill_alpha
#define sdl_sve_rgb32_blend_op_fill_alpha(ma_alpha_chn_idx) \
    কুরু {                                                    \
        যদি (sve_src_chn_idx == (ma_alpha_chn_idx)) {        \
            /* fill alpha */                                \
            sve_target_u16 = svdup_u16(0xFF);               \
        } অন্যথা {                                            \
            sve_target_u16 = sve_source_u16;                \
        }                                                   \
    } যাবত্ (0)

#undef sdl_sve_rgb32_blend_op_copy_alpha
#define sdl_sve_rgb32_blend_op_copy_alpha(ma_alpha_chn_idx) \
    কুরু {                                                    \
        sve_target_u16 = sve_source_u16;                    \
    } যাবত্ (0)

#undef sdl_sve_rgb32_blend_to_rgb565_op
#define sdl_sve_rgb32_blend_to_rgb565_op(ma_alpha_chn_idx) \
    কুরু {                                                   \
        sve_target_u16 = sve_source_u16;                   \
    } যাবত্ (0)

#অন্তর্ভাব "SDL_sve2_swizzle.h"

SDL_TARGETING("arch=armv8-a+sve2")
শূন্য Blit8888to8888PixelSwizzleSVE2(SDL_BlitInfo *info)
{
    sdl_sve_8888_to_8888_swizzle_dispatcher(info);
}

SDL_TARGETING("arch=armv8-a+sve2")
শূন্য Blit8888to565PixelSwizzleSVE2(SDL_BlitInfo *info)
{
    sdl_sve_rgb32_to_rgb565_swizzle_dispatcher(info);
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
স্থির অন্তঃস্থ শূন্য sdl_sve_rgb16_stride_চাবি(uint16_t *SDL_RESTRICT phwSource,
                                            uint16_t *SDL_RESTRICT phwTarget,
                                            size_t uStride,
                                            uint16_t hw_চাবি,
                                            uint16_t hw_চাবি_Mask)
{
    sdl_sve_stride_loop_u16(uStride, vTailPred)
    {
        svuint16_t vSource = svld1_u16(vTailPred, phwSource);
        svuint16_t vTarget = svld1_u16(vTailPred, phwTarget);

        svuint16_t vSourceMasked = svand_n_u16_m(vTailPred,
                                                 vSource,
                                                 hw_চাবি_Mask);
        vTarget = svsel_u16(svcmpeq_n_u16(vTailPred, vSourceMasked, hw_চাবি),
                            vTarget,
                            vSource);

        svst1_u16(vTailPred, phwTarget, vTarget);

        phwSource += sve_iteration_advance;
        phwTarget += sve_iteration_advance;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
স্থির অন্তঃস্থ শূন্য sdl_sve_rgb16_চাবি(uint8_t *SDL_RESTRICT pchSource,
                                     size_t uSourceStride,
                                     uint8_t *SDL_RESTRICT pchTarget,
                                     size_t uTargetStride,
                                     পূর্ণাঙ্ক nWidth,
                                     পূর্ণাঙ্ক nHeight,
                                     uint16_t hw_চাবি,
                                     uint16_t hw_চাবি_Mask)
{
    প্রতিজ্ঞা(0 == ((uintptr_t)pchSource & 0x01));
    প্রতিজ্ঞা(0 == ((uintptr_t)pchTarget & 0x01));

    যাবত্ (nHeight--) {
        sdl_sve_rgb16_stride_চাবি((uint16_t *)pchSource,
                                 (uint16_t *)pchTarget,
                                 nWidth,
                                 hw_চাবি,
                                 hw_চাবি_Mask);

        pchSource += uSourceStride;
        pchTarget += uTargetStride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
শূন্য Blit2to2_চাবি_SVE2(SDL_BlitInfo *info)
{
    পূর্ণাঙ্ক width = info->dst_w;
    পূর্ণাঙ্ক height = info->dst_h;
    uint8_t *src = info->src;
    পূর্ণাঙ্ক srcskip = info->src_skip;
    uint8_t *dst = info->dst;
    পূর্ণাঙ্ক dstskip = info->dst_skip;

    ধ্রুব SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    ধ্রুব SDL_PixelFormatDetails *dstfmt = info->dst_fmt;

    // Set up some basic variables
    পূর্ণাঙ্ক srcbpp = srcfmt->bytes_per_pixel;
    পূর্ণাঙ্ক dstbpp = dstfmt->bytes_per_pixel;

    প্রতিজ্ঞা(srcbpp == 2);
    প্রতিজ্ঞা(dstbpp == 2);

    পূর্ণাঙ্ক srcstride = srcskip + srcbpp * width;
    পূর্ণাঙ্ক dststride = dstskip + dstbpp * width;

    uint32_t ckey = info->colorkey;
    uint32_t rgbmask = ~srcfmt->Amask;
    ckey &= rgbmask;

    sdl_sve_rgb16_চাবি(src,
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
স্থির অন্তঃস্থ শূন্য sdl_sve_rgb32_stride_চাবি_copy_alpha(
    uint32_t *SDL_RESTRICT pwSource,
    uint32_t *SDL_RESTRICT pwTarget,
    size_t uStride,
    uint32_t w_চাবি,
    uint32_t w_চাবি_Mask,
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
                                                 w_চাবি_Mask);
        vTarget = svsel_u32(svcmpeq_n_u32(vTailPred, vSourceMasked, w_চাবি),
                            vTarget,
                            svorr_n_u32_m(vTailPred, vSource, wOpacifyMask));

        svst1_u32(vTailPred, pwTarget, vTarget);

        pwSource += sve_iteration_advance;
        pwTarget += sve_iteration_advance;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
স্থির অন্তঃস্থ শূন্য sdl_sve_rgb32_stride_চাবি_no_alpha(
    uint32_t *SDL_RESTRICT pwSource,
    uint32_t *SDL_RESTRICT pwTarget,
    size_t uStride,
    uint32_t w_চাবি,
    uint32_t w_চাবি_Mask,
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
                                                 w_চাবি_Mask);
        vTarget = svsel_u32(svcmpeq_n_u32(vTailPred, vSourceMasked, w_চাবি),
                            vTarget,
                            svand_n_u32_m(vTailPred, vSource, wActualRGBMask));

        svst1_u32(vTailPred, pwTarget, vTarget);

        pwSource += sve_iteration_advance;
        pwTarget += sve_iteration_advance;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
স্থির অন্তঃস্থ শূন্য sdl_sve_rgb32_চাবি_copy_alpha(uint8_t *SDL_RESTRICT pchSource,
                                                size_t uSourceStride,
                                                uint8_t *SDL_RESTRICT pchTarget,
                                                size_t uTargetStride,
                                                পূর্ণাঙ্ক nWidth,
                                                পূর্ণাঙ্ক nHeight,
                                                uint32_t w_চাবি,
                                                uint32_t w_চাবি_Mask,
                                                uint32_t wOpacifyMask)
{
    প্রতিজ্ঞা(0 == ((uintptr_t)pchSource & 0x03));
    প্রতিজ্ঞা(0 == ((uintptr_t)pchTarget & 0x03));

    যাবত্ (nHeight--) {
        sdl_sve_rgb32_stride_চাবি_copy_alpha((uint32_t *)pchSource,
                                            (uint32_t *)pchTarget,
                                            nWidth,
                                            w_চাবি,
                                            w_চাবি_Mask,
                                            wOpacifyMask);

        pchSource += uSourceStride;
        pchTarget += uTargetStride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
স্থির অন্তঃস্থ শূন্য sdl_sve_rgb32_চাবি_no_alpha(uint8_t *SDL_RESTRICT pchSource,
                                              size_t uSourceStride,
                                              uint8_t *SDL_RESTRICT pchTarget,
                                              size_t uTargetStride,
                                              পূর্ণাঙ্ক nWidth,
                                              পূর্ণাঙ্ক nHeight,
                                              uint32_t w_চাবি,
                                              uint32_t w_চাবি_Mask,
                                              uint32_t wActualRGBMask)
{
    প্রতিজ্ঞা(0 == ((uintptr_t)pchSource & 0x03));
    প্রতিজ্ঞা(0 == ((uintptr_t)pchTarget & 0x03));

    যাবত্ (nHeight--) {
        sdl_sve_rgb32_stride_চাবি_no_alpha((uint32_t *)pchSource,
                                          (uint32_t *)pchTarget,
                                          nWidth,
                                          w_চাবি,
                                          w_চাবি_Mask,
                                          wActualRGBMask);

        pchSource += uSourceStride;
        pchTarget += uTargetStride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
শূন্য Blit4to4_চাবি_SVE2(SDL_BlitInfo *info)
{
    পূর্ণাঙ্ক width = info->dst_w;
    পূর্ণাঙ্ক height = info->dst_h;
    uint8_t *src = info->src;
    পূর্ণাঙ্ক srcskip = info->src_skip;
    uint8_t *dst = info->dst;
    পূর্ণাঙ্ক dstskip = info->dst_skip;

    ধ্রুব SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    ধ্রুব SDL_PixelFormatDetails *dstfmt = info->dst_fmt;

    // Set up some basic variables
    পূর্ণাঙ্ক srcbpp = srcfmt->bytes_per_pixel;
    পূর্ণাঙ্ক dstbpp = dstfmt->bytes_per_pixel;

    প্রতিজ্ঞা(srcbpp == 4);
    প্রতিজ্ঞা(dstbpp == 4);

    পূর্ণাঙ্ক srcstride = srcskip + srcbpp * width;
    পূর্ণাঙ্ক dststride = dstskip + dstbpp * width;

    uint32_t ckey = info->colorkey;
    uint32_t rgbmask = ~srcfmt->Amask;
    ckey &= rgbmask;

    যদি (dstfmt->Amask) {
        uint32_t opamask = ((uint32_t)info->a) << dstfmt->Ashift;
        /* RGBA: set alpha from info->a */
        sdl_sve_rgb32_চাবি_copy_alpha(src,
                                     srcstride,
                                     dst,
                                     dststride,
                                     width,
                                     height,
                                     ckey,
                                     rgbmask,
                                     opamask);
    } অন্যথা {
        /* RGBA->RGB: only copy rgb and set alpha to zero */
        uint32_t rgbmaskactual = srcfmt->Rmask | srcfmt->Gmask | srcfmt->Bmask;
        sdl_sve_rgb32_চাবি_no_alpha(src,
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