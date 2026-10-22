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

#અન્તર્ભાવ "SDL_sve2_blit_A.h"
#અન્તર્ભાવ <assert.h>

#ifdef SDL_SVE2_INTRINSICS

#undef sdl_sve_rgb32_blend_op_fill_alpha
#define sdl_sve_rgb32_blend_op_fill_alpha(ma_alpha_chn_idx)              \
    જો (sve_src_chn_idx == (ma_alpha_chn_idx)) {                         \
        /* fill alpha */                                                 \
        sve_target_u16 = svdup_u16(0xFF);                                \
    } નહીંતર {                                                             \
        svuint16_t vMask = svget4(sve_source_u16x4, (ma_alpha_chn_idx)); \
        sve_target_u16 = sdl_sve_chn_blend_with_mask(sve_source_u16,     \
                                                     sve_target_u16,     \
                                                     vMask);             \
    }

#undef sdl_sve_rgb32_blend_op_copy_alpha
#define sdl_sve_rgb32_blend_op_copy_alpha(ma_alpha_chn_idx)              \
    જો (sve_src_chn_idx == (ma_alpha_chn_idx)) {                         \
        svuint16_t vMask = svget4(sve_source_u16x4, (ma_alpha_chn_idx)); \
        sve_target_u16 = sdl_sve_chn_blend_with_mask(svdup_u16(0xFF),    \
                                                     sve_target_u16,     \
                                                     vMask);             \
    } નહીંતર {                                                             \
        svuint16_t vMask = svget4(sve_source_u16x4, (ma_alpha_chn_idx)); \
        sve_target_u16 = sdl_sve_chn_blend_with_mask(sve_source_u16,     \
                                                     sve_target_u16,     \
                                                     vMask);             \
    }

#undef sdl_sve_rgb32_blend_to_rgb565_op
#define sdl_sve_rgb32_blend_to_rgb565_op(ma_alpha_chn_idx)                \
    કરો {                                                                  \
        svuint16_t vMask = svget4(sve_source_u16x4, (ma_alpha_chn_idx));  \
        sve_target_u16 = sdl_sve_chn_blend_with_mask_fast(sve_source_u16, \
                                                          sve_target_u16, \
                                                          vMask);         \
    } જ્યારે (0)

#અન્તર્ભાવ "SDL_sve2_swizzle.h"

/*-----------------------------------------------------------------------------*
 * Swizzle Blend with Alpha                                                    *
 *-----------------------------------------------------------------------------*/
SDL_TARGETING("arch=armv8-a+sve2")
શૂન્ય Blit8888to8888PixelAlphaSwizzleSVE2(SDL_BlitInfo *info)
{
    અચલ SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    પ્રતિજ્ઞા(0 != srcfmt->Amask);
    (શૂન્ય)srcfmt;

    sdl_sve_8888_to_8888_swizzle_dispatcher(info);
}

SDL_TARGETING("arch=armv8-a+sve2")
શૂન્ય Blit8888to565PixelAlphaSwizzleSVE2(SDL_BlitInfo *info)
{
    sdl_sve_rgb32_to_rgb565_swizzle_dispatcher(info);
}

SDL_TARGETING("arch=armv8-a+sve2")
size_t SDL_GetSVEVectorSize(શૂન્ય)
{
    પાછા svlen(svundef_u8()) * 8;
}

/*-----------------------------------------------------------------------------*
 * RGB565 Blend with Surface Alpha                                             *
 *-----------------------------------------------------------------------------*/
SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
સ્થિર અંતઃરેખ શૂન્ય sdl_sve_rgb565_stride_blend_with_opacity(uint16_t *SDL_RESTRICT phwSource,
                                                            uint16_t *SDL_RESTRICT phwTarget,
                                                            size_t uStride,
                                                            uint16_t hwOpacity)
{
    sdl_sve_stride_loop_u16(uStride, vTailPred)
    {

        svuint16x3_t vSource16x3 =
            sdl_sve_rgb565_unpack(svld1_u16(vTailPred, phwSource));

        svuint16x3_t vTarget16x3 =
            sdl_sve_rgb565_unpack(svld1_u16(vTailPred, phwTarget));

        sdl_sve_pixel_ccc_foreach_chn(
            vSource16x3,
            vTarget16x3,
            {
                sve_target_u16 = sdl_sve_chn_blend_with_opacity_fast(
                    sve_source_u16,
                    sve_target_u16,
                    hwOpacity);
            });

        svst1_u16(vTailPred, phwTarget, sdl_sve_rgb565_pack(vTarget16x3));

        phwSource += sve_iteration_advance;
        phwTarget += sve_iteration_advance;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
સ્થિર અંતઃરેખ શૂન્ય sdl_sve_rgb565_blend_with_opacity(uint8_t *SDL_RESTRICT pchSource,
                                                     size_t uSourceStride,
                                                     uint8_t *SDL_RESTRICT pchTarget,
                                                     size_t uTargetStride,
                                                     પૂર્ણાંક nWidth,
                                                     પૂર્ણાંક nHeight,
                                                     uint16_t hwOpacity)
{
    hwOpacity += hwOpacity == 255;
    પ્રતિજ્ઞા(0 == ((uintptr_t)pchSource & 0x01));
    પ્રતિજ્ઞા(0 == ((uintptr_t)pchTarget & 0x01));

    જ્યારે (nHeight--) {

        sdl_sve_rgb565_stride_blend_with_opacity((uint16_t *)pchSource,
                                                 (uint16_t *)pchTarget,
                                                 nWidth,
                                                 hwOpacity);

        pchSource += uSourceStride;
        pchTarget += uTargetStride;
    }
}

// fast RGB565->RGB565 blending with surface alpha
SDL_TARGETING("arch=armv8-a+sve2")
શૂન્ય Blit565to565SurfaceAlphaSVE2(SDL_BlitInfo *info)
{
    uint16_t alpha = info->a;

    પૂર્ણાંક width = info->dst_w;
    પૂર્ણાંક height = info->dst_h;
    uint8_t *src = info->src;
    પૂર્ણાંક srcskip = info->src_skip;
    uint8_t *dst = info->dst;
    પૂર્ણાંક dstskip = info->dst_skip;

    અચલ SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    અચલ SDL_PixelFormatDetails *dstfmt = info->dst_fmt;

    // Set up some basic variables
    પૂર્ણાંક srcbpp = srcfmt->bytes_per_pixel;
    પૂર્ણાંક dstbpp = dstfmt->bytes_per_pixel;

    પ્રતિજ્ઞા(srcbpp == 2);
    પ્રતિજ્ઞા(dstbpp == 2);

    પૂર્ણાંક srcstride = srcskip + srcbpp * width;
    પૂર્ણાંક dststride = dstskip + dstbpp * width;

    sdl_sve_rgb565_blend_with_opacity(src,
                                      srcstride,
                                      dst,
                                      dststride,
                                      width,
                                      height,
                                      alpha);
}

#endif /* SDL_SVE2_INTRINSICS */