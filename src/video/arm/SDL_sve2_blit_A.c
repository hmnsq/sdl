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

#अन्तर्भाव "SDL_sve2_blit_A.h"
#अन्तर्भाव <assert.h>

#यदि_परिभाषितम् SDL_SVE2_INTRINSICS

#अपरिभाषय sdl_sve_rgb32_blend_op_fill_alpha
#परिभाषय sdl_sve_rgb32_blend_op_fill_alpha(ma_alpha_chn_idx)              \
    यदि (sve_src_chn_idx == (ma_alpha_chn_idx)) {                         \
        /* fill alpha */                                                 \
        sve_target_u16 = svdup_u16(0xFF);                                \
    } अन्यथा {                                                             \
        svuint16_t v_आवरणम् = svget4(sve_source_u16x4, (ma_alpha_chn_idx)); \
        sve_target_u16 = sdl_sve_chn_blend_with_आवरणम्(sve_source_u16,     \
                                                     sve_target_u16,     \
                                                     v_आवरणम्);             \
    }

#अपरिभाषय sdl_sve_rgb32_blend_op_copy_alpha
#परिभाषय sdl_sve_rgb32_blend_op_copy_alpha(ma_alpha_chn_idx)              \
    यदि (sve_src_chn_idx == (ma_alpha_chn_idx)) {                         \
        svuint16_t v_आवरणम् = svget4(sve_source_u16x4, (ma_alpha_chn_idx)); \
        sve_target_u16 = sdl_sve_chn_blend_with_आवरणम्(svdup_u16(0xFF),    \
                                                     sve_target_u16,     \
                                                     v_आवरणम्);             \
    } अन्यथा {                                                             \
        svuint16_t v_आवरणम् = svget4(sve_source_u16x4, (ma_alpha_chn_idx)); \
        sve_target_u16 = sdl_sve_chn_blend_with_आवरणम्(sve_source_u16,     \
                                                     sve_target_u16,     \
                                                     v_आवरणम्);             \
    }

#अपरिभाषय sdl_sve_rgb32_blend_गन्तव्यम्_rgb565_op
#परिभाषय sdl_sve_rgb32_blend_गन्तव्यम्_rgb565_op(ma_alpha_chn_idx)                \
    कुरु {                                                                  \
        svuint16_t v_आवरणम् = svget4(sve_source_u16x4, (ma_alpha_chn_idx));  \
        sve_target_u16 = sdl_sve_chn_blend_with_आवरणम्_fast(sve_source_u16, \
                                                          sve_target_u16, \
                                                          v_आवरणम्);         \
    } यावत् (0)

#अन्तर्भाव "SDL_sve2_swizzle.h"

/*-----------------------------------------------------------------------------*
 * Swizzle Blend with Alpha                                                    *
 *-----------------------------------------------------------------------------*/
SDL_TARGETING("arch=armv8-a+sve2")
शून्य Blit8888to8888PixelAlphaSwizzleSVE2(SDL_BlitInfo *info)
{
    ध्रुव SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    प्रतिज्ञा(0 != srcfmt->Amask);
    (शून्य)srcfmt;

    sdl_sve_8888_गन्तव्यम्_8888_swizzle_dispatcher(info);
}

SDL_TARGETING("arch=armv8-a+sve2")
शून्य Blit8888to565PixelAlphaSwizzleSVE2(SDL_BlitInfo *info)
{
    sdl_sve_rgb32_गन्तव्यम्_rgb565_swizzle_dispatcher(info);
}

SDL_TARGETING("arch=armv8-a+sve2")
size_t SDL_Get_SVEVector_आकार(शून्य)
{
    प्रत्यागम svlen(svundef_u8()) * 8;
}

/*-----------------------------------------------------------------------------*
 * RGB565 Blend with Surface Alpha                                             *
 *-----------------------------------------------------------------------------*/
SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
स्थिर अन्तःस्थ शून्य sdl_sve_rgb565_stride_blend_with_opacity(uint16_t *SDL_RESTRICT phwSource,
                                                            uint16_t *SDL_RESTRICT phwTarget,
                                                            size_t uStride,
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
स्थिर अन्तःस्थ शून्य sdl_sve_rgb565_blend_with_opacity(uint8_t *SDL_RESTRICT pchSource,
                                                     size_t uSourceStride,
                                                     uint8_t *SDL_RESTRICT pchTarget,
                                                     size_t uTargetStride,
                                                     पूर्णाङ्क n_विस्तारः,
                                                     पूर्णाङ्क nHeight,
                                                     uint16_t hwOpacity)
{
    hwOpacity += hwOpacity == 255;
    प्रतिज्ञा(0 == ((uintptr_t)pchSource & 0x01));
    प्रतिज्ञा(0 == ((uintptr_t)pchTarget & 0x01));

    यावत् (nHeight--) {

        sdl_sve_rgb565_stride_blend_with_opacity((uint16_t *)pchSource,
                                                 (uint16_t *)pchTarget,
                                                 n_विस्तारः,
                                                 hwOpacity);

        pchSource += uSourceStride;
        pchTarget += uTargetStride;
    }
}

// fast RGB565->RGB565 blending with surface alpha
SDL_TARGETING("arch=armv8-a+sve2")
शून्य Blit565to565SurfaceAlphaSVE2(SDL_BlitInfo *info)
{
    uint16_t alpha = info->a;

    पूर्णाङ्क विस्तारः = info->dst_w;
    पूर्णाङ्क height = info->dst_h;
    uint8_t *src = info->src;
    पूर्णाङ्क srcskip = info->src_skip;
    uint8_t *dst = info->dst;
    पूर्णाङ्क dstskip = info->dst_skip;

    ध्रुव SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    ध्रुव SDL_PixelFormatDetails *dstfmt = info->dst_fmt;

    // Set up some basic variables
    पूर्णाङ्क srcbpp = srcfmt->अष्टकानि_प्रत्येकम्_pixel;
    पूर्णाङ्क dstbpp = dstfmt->अष्टकानि_प्रत्येकम्_pixel;

    प्रतिज्ञा(srcbpp == 2);
    प्रतिज्ञा(dstbpp == 2);

    पूर्णाङ्क srcstride = srcskip + srcbpp * विस्तारः;
    पूर्णाङ्क dststride = dstskip + dstbpp * विस्तारः;

    sdl_sve_rgb565_blend_with_opacity(src,
                                      srcstride,
                                      dst,
                                      dststride,
                                      विस्तारः,
                                      height,
                                      alpha);
}

#यदि_अन्तः /* SDL_SVE2_INTRINSICS */