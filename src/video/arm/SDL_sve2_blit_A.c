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

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_sve2_blit_A.h"
#ਅਨ੍ਤਰ੍ਭਾਵ <assert.h>

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_SVE2_INTRINSICS

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ sdl_sve_rgb32_blend_op_fill_alpha
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ sdl_sve_rgb32_blend_op_fill_alpha(ma_alpha_chn_idx)              \
    ਜੇ (sve_src_chn_idx == (ma_alpha_chn_idx)) {                         \
        /* fill alpha */                                                 \
        sve_ਨਿਸ਼ਾਨਾ_u16 = svdup_u16(0xFF);                                \
    } ਨਹੀਂਤਾਂ {                                                             \
        svuint16_t v_ਨਕਾਬ = svget4(sve_ਸਰੋਤ_u16x4, (ma_alpha_chn_idx)); \
        sve_ਨਿਸ਼ਾਨਾ_u16 = sdl_sve_chn_blend_with_ਨਕਾਬ(sve_ਸਰੋਤ_u16,     \
                                                     sve_ਨਿਸ਼ਾਨਾ_u16,     \
                                                     v_ਨਕਾਬ);             \
    }

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ sdl_sve_rgb32_blend_op_copy_alpha
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ sdl_sve_rgb32_blend_op_copy_alpha(ma_alpha_chn_idx)              \
    ਜੇ (sve_src_chn_idx == (ma_alpha_chn_idx)) {                         \
        svuint16_t v_ਨਕਾਬ = svget4(sve_ਸਰੋਤ_u16x4, (ma_alpha_chn_idx)); \
        sve_ਨਿਸ਼ਾਨਾ_u16 = sdl_sve_chn_blend_with_ਨਕਾਬ(svdup_u16(0xFF),    \
                                                     sve_ਨਿਸ਼ਾਨਾ_u16,     \
                                                     v_ਨਕਾਬ);             \
    } ਨਹੀਂਤਾਂ {                                                             \
        svuint16_t v_ਨਕਾਬ = svget4(sve_ਸਰੋਤ_u16x4, (ma_alpha_chn_idx)); \
        sve_ਨਿਸ਼ਾਨਾ_u16 = sdl_sve_chn_blend_with_ਨਕਾਬ(sve_ਸਰੋਤ_u16,     \
                                                     sve_ਨਿਸ਼ਾਨਾ_u16,     \
                                                     v_ਨਕਾਬ);             \
    }

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ sdl_sve_rgb32_blend_ਮੰਜ਼ਿਲ_rgb565_op
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ sdl_sve_rgb32_blend_ਮੰਜ਼ਿਲ_rgb565_op(ma_alpha_chn_idx)                \
    ਕਰੋ {                                                                  \
        svuint16_t v_ਨਕਾਬ = svget4(sve_ਸਰੋਤ_u16x4, (ma_alpha_chn_idx));  \
        sve_ਨਿਸ਼ਾਨਾ_u16 = sdl_sve_chn_blend_with_ਨਕਾਬ_fast(sve_ਸਰੋਤ_u16, \
                                                          sve_ਨਿਸ਼ਾਨਾ_u16, \
                                                          v_ਨਕਾਬ);         \
    } ਜਦੋਂ (0)

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_sve2_swizzle.h"

/*-----------------------------------------------------------------------------*
 * Swizzle Blend with Alpha                                                    *
 *-----------------------------------------------------------------------------*/
SDL_TARGETING("arch=armv8-a+sve2")
ਖਾਲੀ Blit8888to8888PixelAlphaSwizzleSVE2(SDL_BlitInfo *info)
{
    ਅਚਲ SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    ਪ੍ਰਤਿਜ੍ਞਾ(0 != srcfmt->Amask);
    (ਖਾਲੀ)srcfmt;

    sdl_sve_8888_ਮੰਜ਼ਿਲ_8888_swizzle_dispatcher(info);
}

SDL_TARGETING("arch=armv8-a+sve2")
ਖਾਲੀ Blit8888to565PixelAlphaSwizzleSVE2(SDL_BlitInfo *info)
{
    sdl_sve_rgb32_ਮੰਜ਼ਿਲ_rgb565_swizzle_dispatcher(info);
}

SDL_TARGETING("arch=armv8-a+sve2")
size_t SDL_Get_SVEVector_ਮਾਪ(ਖਾਲੀ)
{
    ਵਾਪਸ svlen(svundef_u8()) * 8;
}

/*-----------------------------------------------------------------------------*
 * RGB565 Blend with Surface Alpha                                             *
 *-----------------------------------------------------------------------------*/
SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ sdl_sve_rgb565_stride_blend_with_opacity(uint16_t *SDL_RESTRICT phw_ਸਰੋਤ,
                                                            uint16_t *SDL_RESTRICT phw_ਨਿਸ਼ਾਨਾ,
                                                            size_t uStride,
                                                            uint16_t hwOpacity)
{
    sdl_sve_stride_loop_u16(uStride, v_ਪੂਛ_Pred)
    {

        svuint16x3_t vSource16x3 =
            sdl_sve_rgb565_unpack(svld1_u16(v_ਪੂਛ_Pred, phw_ਸਰੋਤ));

        svuint16x3_t vTarget16x3 =
            sdl_sve_rgb565_unpack(svld1_u16(v_ਪੂਛ_Pred, phw_ਨਿਸ਼ਾਨਾ));

        sdl_sve_pixel_ccc_foreach_chn(
            vSource16x3,
            vTarget16x3,
            {
                sve_ਨਿਸ਼ਾਨਾ_u16 = sdl_sve_chn_blend_with_opacity_fast(
                    sve_ਸਰੋਤ_u16,
                    sve_ਨਿਸ਼ਾਨਾ_u16,
                    hwOpacity);
            });

        svst1_u16(v_ਪੂਛ_Pred, phw_ਨਿਸ਼ਾਨਾ, sdl_sve_rgb565_pack(vTarget16x3));

        phw_ਸਰੋਤ += sve_iteration_advance;
        phw_ਨਿਸ਼ਾਨਾ += sve_iteration_advance;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ sdl_sve_rgb565_blend_with_opacity(uint8_t *SDL_RESTRICT pch_ਸਰੋਤ,
                                                     size_t u_ਸਰੋਤ_Stride,
                                                     uint8_t *SDL_RESTRICT pch_ਨਿਸ਼ਾਨਾ,
                                                     size_t u_ਨਿਸ਼ਾਨਾ_Stride,
                                                     ਪੂਰਨ n_ਚੌੜਾਈ,
                                                     ਪੂਰਨ n_ਉਚਾਈ,
                                                     uint16_t hwOpacity)
{
    hwOpacity += hwOpacity == 255;
    ਪ੍ਰਤਿਜ੍ਞਾ(0 == ((uintptr_t)pch_ਸਰੋਤ & 0x01));
    ਪ੍ਰਤਿਜ੍ਞਾ(0 == ((uintptr_t)pch_ਨਿਸ਼ਾਨਾ & 0x01));

    ਜਦੋਂ (n_ਉਚਾਈ--) {

        sdl_sve_rgb565_stride_blend_with_opacity((uint16_t *)pch_ਸਰੋਤ,
                                                 (uint16_t *)pch_ਨਿਸ਼ਾਨਾ,
                                                 n_ਚੌੜਾਈ,
                                                 hwOpacity);

        pch_ਸਰੋਤ += u_ਸਰੋਤ_Stride;
        pch_ਨਿਸ਼ਾਨਾ += u_ਨਿਸ਼ਾਨਾ_Stride;
    }
}

// fast RGB565->RGB565 blending with surface alpha
SDL_TARGETING("arch=armv8-a+sve2")
ਖਾਲੀ Blit565to565SurfaceAlphaSVE2(SDL_BlitInfo *info)
{
    uint16_t alpha = info->a;

    ਪੂਰਨ ਚੌੜਾਈ = info->dst_w;
    ਪੂਰਨ ਉਚਾਈ = info->dst_h;
    uint8_t *src = info->src;
    ਪੂਰਨ srcskip = info->src_skip;
    uint8_t *dst = info->dst;
    ਪੂਰਨ dstskip = info->dst_skip;

    ਅਚਲ SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    ਅਚਲ SDL_PixelFormatDetails *dstfmt = info->dst_fmt;

    // Set up some basic variables
    ਪੂਰਨ srcbpp = srcfmt->ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel;
    ਪੂਰਨ dstbpp = dstfmt->ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel;

    ਪ੍ਰਤਿਜ੍ਞਾ(srcbpp == 2);
    ਪ੍ਰਤਿਜ੍ਞਾ(dstbpp == 2);

    ਪੂਰਨ srcstride = srcskip + srcbpp * ਚੌੜਾਈ;
    ਪੂਰਨ dststride = dstskip + dstbpp * ਚੌੜਾਈ;

    sdl_sve_rgb565_blend_with_opacity(src,
                                      srcstride,
                                      dst,
                                      dststride,
                                      ਚੌੜਾਈ,
                                      ਉਚਾਈ,
                                      alpha);
}

#ਜੇ_ਅੰਤ /* SDL_SVE2_INTRINSICS */