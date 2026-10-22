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

#ضمن "SDL_sve2_blit_A.h"
#ضمن <assert.h>

#که_تعریف_شوی SDL_SVE2_INTRINSICS

#تعریف_لغوه sdl_sve_rgb32_blend_op_fill_alpha
#تعریف_کړه sdl_sve_rgb32_blend_op_fill_alpha(ma_alpha_chn_idx)              \
    إذا (sve_src_chn_idx == (ma_alpha_chn_idx)) {                         \
        /* fill alpha */                                                 \
        sve_موخه_u16 = svdup_u16(0xFF);                                \
    } وإلا {                                                             \
        svuint16_t v_ماسک = svget4(sve_سرچینه_u16x4, (ma_alpha_chn_idx)); \
        sve_موخه_u16 = sdl_sve_chn_blend_with_ماسک(sve_سرچینه_u16,     \
                                                     sve_موخه_u16,     \
                                                     v_ماسک);             \
    }

#تعریف_لغوه sdl_sve_rgb32_blend_op_copy_alpha
#تعریف_کړه sdl_sve_rgb32_blend_op_copy_alpha(ma_alpha_chn_idx)              \
    إذا (sve_src_chn_idx == (ma_alpha_chn_idx)) {                         \
        svuint16_t v_ماسک = svget4(sve_سرچینه_u16x4, (ma_alpha_chn_idx)); \
        sve_موخه_u16 = sdl_sve_chn_blend_with_ماسک(svdup_u16(0xFF),    \
                                                     sve_موخه_u16,     \
                                                     v_ماسک);             \
    } وإلا {                                                             \
        svuint16_t v_ماسک = svget4(sve_سرچینه_u16x4, (ma_alpha_chn_idx)); \
        sve_موخه_u16 = sdl_sve_chn_blend_with_ماسک(sve_سرچینه_u16,     \
                                                     sve_موخه_u16,     \
                                                     v_ماسک);             \
    }

#تعریف_لغوه sdl_sve_rgb32_blend_منزل_rgb565_op
#تعریف_کړه sdl_sve_rgb32_blend_منزل_rgb565_op(ma_alpha_chn_idx)                \
    افعل {                                                                  \
        svuint16_t v_ماسک = svget4(sve_سرچینه_u16x4, (ma_alpha_chn_idx));  \
        sve_موخه_u16 = sdl_sve_chn_blend_with_ماسک_fast(sve_سرچینه_u16, \
                                                          sve_موخه_u16, \
                                                          v_ماسک);         \
    } طالما (0)

#ضمن "SDL_sve2_swizzle.h"

/*-----------------------------------------------------------------------------*
 * Swizzle Blend with Alpha                                                    *
 *-----------------------------------------------------------------------------*/
SDL_TARGETING("arch=armv8-a+sve2")
فراغ Blit8888to8888PixelAlphaSwizzleSVE2(SDL_BlitInfo *info)
{
    ثابت SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    أكد(0 != srcfmt->Amask);
    (فراغ)srcfmt;

    sdl_sve_8888_منزل_8888_swizzle_dispatcher(info);
}

SDL_TARGETING("arch=armv8-a+sve2")
فراغ Blit8888to565PixelAlphaSwizzleSVE2(SDL_BlitInfo *info)
{
    sdl_sve_rgb32_منزل_rgb565_swizzle_dispatcher(info);
}

SDL_TARGETING("arch=armv8-a+sve2")
size_t SDL_Get_SVEVector_اندازه(فراغ)
{
    أرجع svlen(svundef_u8()) * 8;
}

/*-----------------------------------------------------------------------------*
 * RGB565 Blend with Surface Alpha                                             *
 *-----------------------------------------------------------------------------*/
SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_rgb565_stride_blend_with_opacity(uint16_t *SDL_RESTRICT phw_سرچینه,
                                                            uint16_t *SDL_RESTRICT phw_موخه,
                                                            size_t uStride,
                                                            uint16_t hwOpacity)
{
    sdl_sve_stride_loop_u16(uStride, v_لکۍ_Pred)
    {

        svuint16x3_t vSource16x3 =
            sdl_sve_rgb565_unpack(svld1_u16(v_لکۍ_Pred, phw_سرچینه));

        svuint16x3_t vTarget16x3 =
            sdl_sve_rgb565_unpack(svld1_u16(v_لکۍ_Pred, phw_موخه));

        sdl_sve_pixel_ccc_foreach_chn(
            vSource16x3,
            vTarget16x3,
            {
                sve_موخه_u16 = sdl_sve_chn_blend_with_opacity_fast(
                    sve_سرچینه_u16,
                    sve_موخه_u16,
                    hwOpacity);
            });

        svst1_u16(v_لکۍ_Pred, phw_موخه, sdl_sve_rgb565_pack(vTarget16x3));

        phw_سرچینه += sve_iteration_advance;
        phw_موخه += sve_iteration_advance;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_rgb565_blend_with_opacity(uint8_t *SDL_RESTRICT pch_سرچینه,
                                                     size_t u_سرچینه_Stride,
                                                     uint8_t *SDL_RESTRICT pch_موخه,
                                                     size_t u_موخه_Stride,
                                                     صحيح n_پلنوالی,
                                                     صحيح n_لوړوالی,
                                                     uint16_t hwOpacity)
{
    hwOpacity += hwOpacity == 255;
    أكد(0 == ((uintptr_t)pch_سرچینه & 0x01));
    أكد(0 == ((uintptr_t)pch_موخه & 0x01));

    طالما (n_لوړوالی--) {

        sdl_sve_rgb565_stride_blend_with_opacity((uint16_t *)pch_سرچینه,
                                                 (uint16_t *)pch_موخه,
                                                 n_پلنوالی,
                                                 hwOpacity);

        pch_سرچینه += u_سرچینه_Stride;
        pch_موخه += u_موخه_Stride;
    }
}

// fast RGB565->RGB565 blending with surface alpha
SDL_TARGETING("arch=armv8-a+sve2")
فراغ Blit565to565SurfaceAlphaSVE2(SDL_BlitInfo *info)
{
    uint16_t alpha = info->a;

    صحيح پلنوالی = info->dst_w;
    صحيح لوړوالی = info->dst_h;
    uint8_t *src = info->src;
    صحيح srcskip = info->src_skip;
    uint8_t *dst = info->dst;
    صحيح dstskip = info->dst_skip;

    ثابت SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    ثابت SDL_PixelFormatDetails *dstfmt = info->dst_fmt;

    // Set up some basic variables
    صحيح srcbpp = srcfmt->بایټونه_فی_pixel;
    صحيح dstbpp = dstfmt->بایټونه_فی_pixel;

    أكد(srcbpp == 2);
    أكد(dstbpp == 2);

    صحيح srcstride = srcskip + srcbpp * پلنوالی;
    صحيح dststride = dstskip + dstbpp * پلنوالی;

    sdl_sve_rgb565_blend_with_opacity(src,
                                      srcstride,
                                      dst,
                                      dststride,
                                      پلنوالی,
                                      لوړوالی,
                                      alpha);
}

#د_که_پای /* SDL_SVE2_INTRINSICS */