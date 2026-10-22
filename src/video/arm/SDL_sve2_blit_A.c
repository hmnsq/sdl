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

#ಅನ್ತರ್ಭಾವ "SDL_sve2_blit_A.h"
#ಅನ್ತರ್ಭಾವ <assert.h>

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_SVE2_INTRINSICS

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು sdl_sve_rgb32_blend_op_fill_alpha
#ವ್ಯಾಖ್ಯಾನಿಸು sdl_sve_rgb32_blend_op_fill_alpha(ma_alpha_chn_idx)              \
    ಆದರೆ (sve_src_chn_idx == (ma_alpha_chn_idx)) {                         \
        /* fill alpha */                                                 \
        sve_ಗುರಿ_u16 = svdup_u16(0xFF);                                \
    } ಇಲ್ಲದಿದ್ದರೆ {                                                             \
        svuint16_t v_ಮುಖವಾಡ = svget4(sve_ಮೂಲ_u16x4, (ma_alpha_chn_idx)); \
        sve_ಗುರಿ_u16 = sdl_sve_chn_blend_with_ಮುಖವಾಡ(sve_ಮೂಲ_u16,     \
                                                     sve_ಗುರಿ_u16,     \
                                                     v_ಮುಖವಾಡ);             \
    }

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು sdl_sve_rgb32_blend_op_copy_alpha
#ವ್ಯಾಖ್ಯಾನಿಸು sdl_sve_rgb32_blend_op_copy_alpha(ma_alpha_chn_idx)              \
    ಆದರೆ (sve_src_chn_idx == (ma_alpha_chn_idx)) {                         \
        svuint16_t v_ಮುಖವಾಡ = svget4(sve_ಮೂಲ_u16x4, (ma_alpha_chn_idx)); \
        sve_ಗುರಿ_u16 = sdl_sve_chn_blend_with_ಮುಖವಾಡ(svdup_u16(0xFF),    \
                                                     sve_ಗುರಿ_u16,     \
                                                     v_ಮುಖವಾಡ);             \
    } ಇಲ್ಲದಿದ್ದರೆ {                                                             \
        svuint16_t v_ಮುಖವಾಡ = svget4(sve_ಮೂಲ_u16x4, (ma_alpha_chn_idx)); \
        sve_ಗುರಿ_u16 = sdl_sve_chn_blend_with_ಮುಖವಾಡ(sve_ಮೂಲ_u16,     \
                                                     sve_ಗುರಿ_u16,     \
                                                     v_ಮುಖವಾಡ);             \
    }

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು sdl_sve_rgb32_blend_ಗಮ್ಯ_rgb565_op
#ವ್ಯಾಖ್ಯಾನಿಸು sdl_sve_rgb32_blend_ಗಮ್ಯ_rgb565_op(ma_alpha_chn_idx)                \
    ಮಾಡು {                                                                  \
        svuint16_t v_ಮುಖವಾಡ = svget4(sve_ಮೂಲ_u16x4, (ma_alpha_chn_idx));  \
        sve_ಗುರಿ_u16 = sdl_sve_chn_blend_with_ಮುಖವಾಡ_fast(sve_ಮೂಲ_u16, \
                                                          sve_ಗುರಿ_u16, \
                                                          v_ಮುಖವಾಡ);         \
    } ಆಗ (0)

#ಅನ್ತರ್ಭಾವ "SDL_sve2_swizzle.h"

/*-----------------------------------------------------------------------------*
 * Swizzle Blend with Alpha                                                    *
 *-----------------------------------------------------------------------------*/
SDL_TARGETING("arch=armv8-a+sve2")
ಶೂನ್ಯ Blit8888to8888PixelAlphaSwizzleSVE2(SDL_BlitInfo *info)
{
    ಸ್ಥಿರಾಂಕ SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    ಪ್ರತಿಜ್ಞಾ(0 != srcfmt->Amask);
    (ಶೂನ್ಯ)srcfmt;

    sdl_sve_8888_ಗಮ್ಯ_8888_swizzle_dispatcher(info);
}

SDL_TARGETING("arch=armv8-a+sve2")
ಶೂನ್ಯ Blit8888to565PixelAlphaSwizzleSVE2(SDL_BlitInfo *info)
{
    sdl_sve_rgb32_ಗಮ್ಯ_rgb565_swizzle_dispatcher(info);
}

SDL_TARGETING("arch=armv8-a+sve2")
size_t SDL_Get_SVEVector_ಗಾತ್ರ(ಶೂನ್ಯ)
{
    ಹಿಂತಿರುಗಿ svlen(svundef_u8()) * 8;
}

/*-----------------------------------------------------------------------------*
 * RGB565 Blend with Surface Alpha                                             *
 *-----------------------------------------------------------------------------*/
SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_rgb565_stride_blend_with_opacity(uint16_t *SDL_RESTRICT phw_ಮೂಲ,
                                                            uint16_t *SDL_RESTRICT phw_ಗುರಿ,
                                                            size_t uStride,
                                                            uint16_t hwOpacity)
{
    sdl_sve_stride_loop_u16(uStride, v_ಬಾಲ_Pred)
    {

        svuint16x3_t vSource16x3 =
            sdl_sve_rgb565_unpack(svld1_u16(v_ಬಾಲ_Pred, phw_ಮೂಲ));

        svuint16x3_t vTarget16x3 =
            sdl_sve_rgb565_unpack(svld1_u16(v_ಬಾಲ_Pred, phw_ಗುರಿ));

        sdl_sve_pixel_ccc_foreach_chn(
            vSource16x3,
            vTarget16x3,
            {
                sve_ಗುರಿ_u16 = sdl_sve_chn_blend_with_opacity_fast(
                    sve_ಮೂಲ_u16,
                    sve_ಗುರಿ_u16,
                    hwOpacity);
            });

        svst1_u16(v_ಬಾಲ_Pred, phw_ಗುರಿ, sdl_sve_rgb565_pack(vTarget16x3));

        phw_ಮೂಲ += sve_iteration_advance;
        phw_ಗುರಿ += sve_iteration_advance;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_rgb565_blend_with_opacity(uint8_t *SDL_RESTRICT pch_ಮೂಲ,
                                                     size_t u_ಮೂಲ_Stride,
                                                     uint8_t *SDL_RESTRICT pch_ಗುರಿ,
                                                     size_t u_ಗುರಿ_Stride,
                                                     ಪೂರ್ಣಾಂಕ n_ಅಗಲ,
                                                     ಪೂರ್ಣಾಂಕ n_ಎತ್ತರ,
                                                     uint16_t hwOpacity)
{
    hwOpacity += hwOpacity == 255;
    ಪ್ರತಿಜ್ಞಾ(0 == ((uintptr_t)pch_ಮೂಲ & 0x01));
    ಪ್ರತಿಜ್ಞಾ(0 == ((uintptr_t)pch_ಗುರಿ & 0x01));

    ಆಗ (n_ಎತ್ತರ--) {

        sdl_sve_rgb565_stride_blend_with_opacity((uint16_t *)pch_ಮೂಲ,
                                                 (uint16_t *)pch_ಗುರಿ,
                                                 n_ಅಗಲ,
                                                 hwOpacity);

        pch_ಮೂಲ += u_ಮೂಲ_Stride;
        pch_ಗುರಿ += u_ಗುರಿ_Stride;
    }
}

// fast RGB565->RGB565 blending with surface alpha
SDL_TARGETING("arch=armv8-a+sve2")
ಶೂನ್ಯ Blit565to565SurfaceAlphaSVE2(SDL_BlitInfo *info)
{
    uint16_t alpha = info->a;

    ಪೂರ್ಣಾಂಕ ಅಗಲ = info->dst_w;
    ಪೂರ್ಣಾಂಕ ಎತ್ತರ = info->dst_h;
    uint8_t *src = info->src;
    ಪೂರ್ಣಾಂಕ srcskip = info->src_skip;
    uint8_t *dst = info->dst;
    ಪೂರ್ಣಾಂಕ dstskip = info->dst_skip;

    ಸ್ಥಿರಾಂಕ SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    ಸ್ಥಿರಾಂಕ SDL_PixelFormatDetails *dstfmt = info->dst_fmt;

    // Set up some basic variables
    ಪೂರ್ಣಾಂಕ srcbpp = srcfmt->ಬೈಟುಗಳು_ಪ್ರತಿ_pixel;
    ಪೂರ್ಣಾಂಕ dstbpp = dstfmt->ಬೈಟುಗಳು_ಪ್ರತಿ_pixel;

    ಪ್ರತಿಜ್ಞಾ(srcbpp == 2);
    ಪ್ರತಿಜ್ಞಾ(dstbpp == 2);

    ಪೂರ್ಣಾಂಕ srcstride = srcskip + srcbpp * ಅಗಲ;
    ಪೂರ್ಣಾಂಕ dststride = dstskip + dstbpp * ಅಗಲ;

    sdl_sve_rgb565_blend_with_opacity(src,
                                      srcstride,
                                      dst,
                                      dststride,
                                      ಅಗಲ,
                                      ಎತ್ತರ,
                                      alpha);
}

#ಆದರೆ_ಅಂತ್ಯ /* SDL_SVE2_INTRINSICS */