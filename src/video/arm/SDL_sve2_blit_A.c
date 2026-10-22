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

#समावेश "SDL_sve2_blit_A.h"
#समावेश <assert.h>

#अगर_घोषित SDL_SVE2_INTRINSICS

#अघोषित sdl_sve_rgb32_blend_op_fill_alpha
#घोषणा sdl_sve_rgb32_blend_op_fill_alpha(ma_alpha_chn_idx)              \
    अगर (sve_src_chn_idx == (ma_alpha_chn_idx)) {                         \
        /* fill alpha */                                                 \
        sve_target_u16 = svdup_u16(0xFF);                                \
    } अन्यथा {                                                             \
        svuint16_t vMask = svget4(sve_source_u16x4, (ma_alpha_chn_idx)); \
        sve_target_u16 = sdl_sve_chn_blend_with_mask(sve_source_u16,     \
                                                     sve_target_u16,     \
                                                     vMask);             \
    }

#अघोषित sdl_sve_rgb32_blend_op_copy_alpha
#घोषणा sdl_sve_rgb32_blend_op_copy_alpha(ma_alpha_chn_idx)              \
    अगर (sve_src_chn_idx == (ma_alpha_chn_idx)) {                         \
        svuint16_t vMask = svget4(sve_source_u16x4, (ma_alpha_chn_idx)); \
        sve_target_u16 = sdl_sve_chn_blend_with_mask(svdup_u16(0xFF),    \
                                                     sve_target_u16,     \
                                                     vMask);             \
    } अन्यथा {                                                             \
        svuint16_t vMask = svget4(sve_source_u16x4, (ma_alpha_chn_idx)); \
        sve_target_u16 = sdl_sve_chn_blend_with_mask(sve_source_u16,     \
                                                     sve_target_u16,     \
                                                     vMask);             \
    }

#अघोषित sdl_sve_rgb32_blend_to_rgb565_op
#घोषणा sdl_sve_rgb32_blend_to_rgb565_op(ma_alpha_chn_idx)                \
    करो {                                                                  \
        svuint16_t vMask = svget4(sve_source_u16x4, (ma_alpha_chn_idx));  \
        sve_target_u16 = sdl_sve_chn_blend_with_mask_fast(sve_source_u16, \
                                                          sve_target_u16, \
                                                          vMask);         \
    } जबतक (0)

#समावेश "SDL_sve2_swizzle.h"

/*-----------------------------------------------------------------------------*
 * Swizzle Blend with Alpha                                                    *
 *-----------------------------------------------------------------------------*/
SDL_TARGETING("arch=armv8-a+sve2")
व्योम Blit8888to8888PixelAlphaSwizzleSVE2(SDL_BlitInfo *info)
{
    स्थिर SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    निश्चित(0 != srcfmt->Amask);
    (व्योम)srcfmt;

    sdl_sve_8888_to_8888_swizzle_dispatcher(info);
}

SDL_TARGETING("arch=armv8-a+sve2")
व्योम Blit8888to565PixelAlphaSwizzleSVE2(SDL_BlitInfo *info)
{
    sdl_sve_rgb32_to_rgb565_swizzle_dispatcher(info);
}

SDL_TARGETING("arch=armv8-a+sve2")
माप_प्रकार SDL_Get_SVEVector_आकार(व्योम)
{
    वापस svlen(svundef_u8()) * 8;
}

/*-----------------------------------------------------------------------------*
 * RGB565 Blend with Surface Alpha                                             *
 *-----------------------------------------------------------------------------*/
SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
अटल अंतरभूत व्योम sdl_sve_rgb565_stride_blend_with_opacity(uint16_t *SDL_RESTRICT phwSource,
                                                            uint16_t *SDL_RESTRICT phwTarget,
                                                            माप_प्रकार uStride,
                                                            uint16_t hwOpacity)
{
    sdl_sve_stride_loop_u16(uStride, v_पुच्छ_Pred)
    {

        svuint16x3_t vSource16x3 =
            sdl_sve_rgb565_unpack(svld1_u16(v_पुच्छ_Pred, phwSource));

        svuint16x3_t vTarget16x3 =
            sdl_sve_rgb565_unpack(svld1_u16(v_पुच्छ_Pred, phwTarget));

        sdl_sve_pixel_ccc_foreach_chn(
            vSource16x3,
            vTarget16x3,
            {
                sve_target_u16 = sdl_sve_chn_blend_with_opacity_fast(
                    sve_source_u16,
                    sve_target_u16,
                    hwOpacity);
            });

        svst1_u16(v_पुच्छ_Pred, phwTarget, sdl_sve_rgb565_pack(vTarget16x3));

        phwSource += sve_iteration_advance;
        phwTarget += sve_iteration_advance;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
अटल अंतरभूत व्योम sdl_sve_rgb565_blend_with_opacity(uint8_t *SDL_RESTRICT pchSource,
                                                     माप_प्रकार uSourceStride,
                                                     uint8_t *SDL_RESTRICT pchTarget,
                                                     माप_प्रकार uTargetStride,
                                                     पूर्णांक nWidth,
                                                     पूर्णांक nHeight,
                                                     uint16_t hwOpacity)
{
    hwOpacity += hwOpacity == 255;
    निश्चित(0 == ((uintptr_t)pchSource & 0x01));
    निश्चित(0 == ((uintptr_t)pchTarget & 0x01));

    जबतक (nHeight--) {

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
व्योम Blit565to565SurfaceAlphaSVE2(SDL_BlitInfo *info)
{
    uint16_t alpha = info->a;

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

    sdl_sve_rgb565_blend_with_opacity(src,
                                      srcstride,
                                      dst,
                                      dststride,
                                      width,
                                      height,
                                      alpha);
}

#पूर्ण_अगर /* SDL_SVE2_INTRINSICS */