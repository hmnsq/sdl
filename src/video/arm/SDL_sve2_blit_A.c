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

#شامل "SDL_sve2_blit_A.h"
#شامل <assert.h>

#اگر_تعریف_شدہ SDL_SVE2_INTRINSICS

#تعریف_منسوخ sdl_sve_rgb32_blend_op_fill_alpha
#تعریف_کرو sdl_sve_rgb32_blend_op_fill_alpha(ma_alpha_chn_idx)              \
    اگر (sve_src_chn_idx == (ma_alpha_chn_idx)) {                         \
        /* fill alpha */                                                 \
        sve_ہدف_u16 = svdup_u16(0xFF);                                \
    } ورنہ {                                                             \
        svuint16_t v_نقاب = svget4(sve_ماخذ_u16x4, (ma_alpha_chn_idx)); \
        sve_ہدف_u16 = sdl_sve_chn_blend_with_نقاب(sve_ماخذ_u16,     \
                                                     sve_ہدف_u16,     \
                                                     v_نقاب);             \
    }

#تعریف_منسوخ sdl_sve_rgb32_blend_op_copy_alpha
#تعریف_کرو sdl_sve_rgb32_blend_op_copy_alpha(ma_alpha_chn_idx)              \
    اگر (sve_src_chn_idx == (ma_alpha_chn_idx)) {                         \
        svuint16_t v_نقاب = svget4(sve_ماخذ_u16x4, (ma_alpha_chn_idx)); \
        sve_ہدف_u16 = sdl_sve_chn_blend_with_نقاب(svdup_u16(0xFF),    \
                                                     sve_ہدف_u16,     \
                                                     v_نقاب);             \
    } ورنہ {                                                             \
        svuint16_t v_نقاب = svget4(sve_ماخذ_u16x4, (ma_alpha_chn_idx)); \
        sve_ہدف_u16 = sdl_sve_chn_blend_with_نقاب(sve_ماخذ_u16,     \
                                                     sve_ہدف_u16,     \
                                                     v_نقاب);             \
    }

#تعریف_منسوخ sdl_sve_rgb32_blend_مقصد_rgb565_op
#تعریف_کرو sdl_sve_rgb32_blend_مقصد_rgb565_op(ma_alpha_chn_idx)                \
    کرو {                                                                  \
        svuint16_t v_نقاب = svget4(sve_ماخذ_u16x4, (ma_alpha_chn_idx));  \
        sve_ہدف_u16 = sdl_sve_chn_blend_with_نقاب_fast(sve_ماخذ_u16, \
                                                          sve_ہدف_u16, \
                                                          v_نقاب);         \
    } جب (0)

#شامل "SDL_sve2_swizzle.h"

/*-----------------------------------------------------------------------------*
 * Swizzle Blend with Alpha                                                    *
 *-----------------------------------------------------------------------------*/
SDL_TARGETING("arch=armv8-a+sve2")
خالی Blit8888to8888PixelAlphaSwizzleSVE2(SDL_BlitInfo *info)
{
    ثابت SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    أكد(0 != srcfmt->Amask);
    (خالی)srcfmt;

    sdl_sve_8888_مقصد_8888_swizzle_dispatcher(info);
}

SDL_TARGETING("arch=armv8-a+sve2")
خالی Blit8888to565PixelAlphaSwizzleSVE2(SDL_BlitInfo *info)
{
    sdl_sve_rgb32_مقصد_rgb565_swizzle_dispatcher(info);
}

SDL_TARGETING("arch=armv8-a+sve2")
size_t SDL_Get_SVEVector_سائز(خالی)
{
    واپس svlen(svundef_u8()) * 8;
}

/*-----------------------------------------------------------------------------*
 * RGB565 Blend with Surface Alpha                                             *
 *-----------------------------------------------------------------------------*/
SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساکن اندرونی خالی sdl_sve_rgb565_stride_blend_with_opacity(uint16_t *SDL_RESTRICT phw_ماخذ,
                                                            uint16_t *SDL_RESTRICT phw_ہدف,
                                                            size_t uStride,
                                                            uint16_t hwOpacity)
{
    sdl_sve_stride_loop_u16(uStride, v_دم_Pred)
    {

        svuint16x3_t vSource16x3 =
            sdl_sve_rgb565_unpack(svld1_u16(v_دم_Pred, phw_ماخذ));

        svuint16x3_t vTarget16x3 =
            sdl_sve_rgb565_unpack(svld1_u16(v_دم_Pred, phw_ہدف));

        sdl_sve_pixel_ccc_foreach_chn(
            vSource16x3,
            vTarget16x3,
            {
                sve_ہدف_u16 = sdl_sve_chn_blend_with_opacity_fast(
                    sve_ماخذ_u16,
                    sve_ہدف_u16,
                    hwOpacity);
            });

        svst1_u16(v_دم_Pred, phw_ہدف, sdl_sve_rgb565_pack(vTarget16x3));

        phw_ماخذ += sve_iteration_advance;
        phw_ہدف += sve_iteration_advance;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساکن اندرونی خالی sdl_sve_rgb565_blend_with_opacity(uint8_t *SDL_RESTRICT pch_ماخذ,
                                                     size_t u_ماخذ_Stride,
                                                     uint8_t *SDL_RESTRICT pch_ہدف,
                                                     size_t u_ہدف_Stride,
                                                     صحیح n_چوڑائی,
                                                     صحیح n_اونچائی,
                                                     uint16_t hwOpacity)
{
    hwOpacity += hwOpacity == 255;
    أكد(0 == ((uintptr_t)pch_ماخذ & 0x01));
    أكد(0 == ((uintptr_t)pch_ہدف & 0x01));

    جب (n_اونچائی--) {

        sdl_sve_rgb565_stride_blend_with_opacity((uint16_t *)pch_ماخذ,
                                                 (uint16_t *)pch_ہدف,
                                                 n_چوڑائی,
                                                 hwOpacity);

        pch_ماخذ += u_ماخذ_Stride;
        pch_ہدف += u_ہدف_Stride;
    }
}

// fast RGB565->RGB565 blending with surface alpha
SDL_TARGETING("arch=armv8-a+sve2")
خالی Blit565to565SurfaceAlphaSVE2(SDL_BlitInfo *info)
{
    uint16_t alpha = info->a;

    صحیح چوڑائی = info->dst_w;
    صحیح اونچائی = info->dst_h;
    uint8_t *src = info->src;
    صحیح srcskip = info->src_skip;
    uint8_t *dst = info->dst;
    صحیح dstskip = info->dst_skip;

    ثابت SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    ثابت SDL_PixelFormatDetails *dstfmt = info->dst_fmt;

    // Set up some basic variables
    صحیح srcbpp = srcfmt->بائٹیں_فی_pixel;
    صحیح dstbpp = dstfmt->بائٹیں_فی_pixel;

    أكد(srcbpp == 2);
    أكد(dstbpp == 2);

    صحیح srcstride = srcskip + srcbpp * چوڑائی;
    صحیح dststride = dstskip + dstbpp * چوڑائی;

    sdl_sve_rgb565_blend_with_opacity(src,
                                      srcstride,
                                      dst,
                                      dststride,
                                      چوڑائی,
                                      اونچائی,
                                      alpha);
}

#اگر_ختم /* SDL_SVE2_INTRINSICS */