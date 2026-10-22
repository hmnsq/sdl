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

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_sve2_blit_N.h"
#ਅਨ੍ਤਰ੍ਭਾਵ <assert.h>

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_SVE2_INTRINSICS

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ sdl_sve_rgb32_blend_op_fill_alpha
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ sdl_sve_rgb32_blend_op_fill_alpha(ma_alpha_chn_idx) \
    ਕਰੋ {                                                    \
        ਜੇ (sve_src_chn_idx == (ma_alpha_chn_idx)) {        \
            /* fill alpha */                                \
            sve_ਨਿਸ਼ਾਨਾ_u16 = svdup_u16(0xFF);               \
        } ਨਹੀਂਤਾਂ {                                            \
            sve_ਨਿਸ਼ਾਨਾ_u16 = sve_ਸਰੋਤ_u16;                \
        }                                                   \
    } ਜਦੋਂ (0)

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ sdl_sve_rgb32_blend_op_copy_alpha
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ sdl_sve_rgb32_blend_op_copy_alpha(ma_alpha_chn_idx) \
    ਕਰੋ {                                                    \
        sve_ਨਿਸ਼ਾਨਾ_u16 = sve_ਸਰੋਤ_u16;                    \
    } ਜਦੋਂ (0)

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ sdl_sve_rgb32_blend_ਮੰਜ਼ਿਲ_rgb565_op
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ sdl_sve_rgb32_blend_ਮੰਜ਼ਿਲ_rgb565_op(ma_alpha_chn_idx) \
    ਕਰੋ {                                                   \
        sve_ਨਿਸ਼ਾਨਾ_u16 = sve_ਸਰੋਤ_u16;                   \
    } ਜਦੋਂ (0)

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_sve2_swizzle.h"

SDL_TARGETING("arch=armv8-a+sve2")
ਖਾਲੀ Blit8888to8888PixelSwizzleSVE2(SDL_BlitInfo *info)
{
    sdl_sve_8888_ਮੰਜ਼ਿਲ_8888_swizzle_dispatcher(info);
}

SDL_TARGETING("arch=armv8-a+sve2")
ਖਾਲੀ Blit8888to565PixelSwizzleSVE2(SDL_BlitInfo *info)
{
    sdl_sve_rgb32_ਮੰਜ਼ਿਲ_rgb565_swizzle_dispatcher(info);
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ sdl_sve_rgb16_stride_ਕੁੰਜੀ(uint16_t *SDL_RESTRICT phw_ਸਰੋਤ,
                                            uint16_t *SDL_RESTRICT phw_ਨਿਸ਼ਾਨਾ,
                                            size_t uStride,
                                            uint16_t hw_ਕੁੰਜੀ,
                                            uint16_t hw_ਕੁੰਜੀ_ਨਕਾਬ)
{
    sdl_sve_stride_loop_u16(uStride, v_ਪੂਛ_Pred)
    {
        svuint16_t v_ਸਰੋਤ = svld1_u16(v_ਪੂਛ_Pred, phw_ਸਰੋਤ);
        svuint16_t v_ਨਿਸ਼ਾਨਾ = svld1_u16(v_ਪੂਛ_Pred, phw_ਨਿਸ਼ਾਨਾ);

        svuint16_t v_ਸਰੋਤ_Masked = svand_n_u16_m(v_ਪੂਛ_Pred,
                                                 v_ਸਰੋਤ,
                                                 hw_ਕੁੰਜੀ_ਨਕਾਬ);
        v_ਨਿਸ਼ਾਨਾ = svsel_u16(svcmpeq_n_u16(v_ਪੂਛ_Pred, v_ਸਰੋਤ_Masked, hw_ਕੁੰਜੀ),
                            v_ਨਿਸ਼ਾਨਾ,
                            v_ਸਰੋਤ);

        svst1_u16(v_ਪੂਛ_Pred, phw_ਨਿਸ਼ਾਨਾ, v_ਨਿਸ਼ਾਨਾ);

        phw_ਸਰੋਤ += sve_iteration_advance;
        phw_ਨਿਸ਼ਾਨਾ += sve_iteration_advance;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ sdl_sve_rgb16_ਕੁੰਜੀ(uint8_t *SDL_RESTRICT pch_ਸਰੋਤ,
                                     size_t u_ਸਰੋਤ_Stride,
                                     uint8_t *SDL_RESTRICT pch_ਨਿਸ਼ਾਨਾ,
                                     size_t u_ਨਿਸ਼ਾਨਾ_Stride,
                                     ਪੂਰਨ n_ਚੌੜਾਈ,
                                     ਪੂਰਨ n_ਉਚਾਈ,
                                     uint16_t hw_ਕੁੰਜੀ,
                                     uint16_t hw_ਕੁੰਜੀ_ਨਕਾਬ)
{
    ਪ੍ਰਤਿਜ੍ਞਾ(0 == ((uintptr_t)pch_ਸਰੋਤ & 0x01));
    ਪ੍ਰਤਿਜ੍ਞਾ(0 == ((uintptr_t)pch_ਨਿਸ਼ਾਨਾ & 0x01));

    ਜਦੋਂ (n_ਉਚਾਈ--) {
        sdl_sve_rgb16_stride_ਕੁੰਜੀ((uint16_t *)pch_ਸਰੋਤ,
                                 (uint16_t *)pch_ਨਿਸ਼ਾਨਾ,
                                 n_ਚੌੜਾਈ,
                                 hw_ਕੁੰਜੀ,
                                 hw_ਕੁੰਜੀ_ਨਕਾਬ);

        pch_ਸਰੋਤ += u_ਸਰੋਤ_Stride;
        pch_ਨਿਸ਼ਾਨਾ += u_ਨਿਸ਼ਾਨਾ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ਖਾਲੀ Blit2to2_ਕੁੰਜੀ_SVE2(SDL_BlitInfo *info)
{
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

    uint32_t ckey = info->colorkey;
    uint32_t rgbmask = ~srcfmt->Amask;
    ckey &= rgbmask;

    sdl_sve_rgb16_ਕੁੰਜੀ(src,
                      srcstride,
                      dst,
                      dststride,
                      ਚੌੜਾਈ,
                      ਉਚਾਈ,
                      ckey,
                      rgbmask);
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ sdl_sve_rgb32_stride_ਕੁੰਜੀ_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ਸਰੋਤ,
    uint32_t *SDL_RESTRICT pw_ਨਿਸ਼ਾਨਾ,
    size_t uStride,
    uint32_t w_ਕੁੰਜੀ,
    uint32_t w_ਕੁੰਜੀ_ਨਕਾਬ,
    uint32_t w_Opacify_ਨਕਾਬ)
{
    sdl_sve_stride_loop_u32(uStride, v_ਪੂਛ_Pred)
    {
        svuint32_t v_ਸਰੋਤ = svld1_u32(v_ਪੂਛ_Pred, pw_ਸਰੋਤ);
        svuint32_t v_ਨਿਸ਼ਾਨਾ = svld1_u32(v_ਪੂਛ_Pred, pw_ਨਿਸ਼ਾਨਾ);

        /*
            uint32_t opamask = ((uint32_t)info->a) << dstfmt->Ashift;
            ...
            if ((*src32 & rgbmask) != ckey) {
                *dst32 = *src32 | opamask;
            }
        */
        svuint32_t v_ਸਰੋਤ_Masked = svand_n_u32_m(v_ਪੂਛ_Pred,
                                                 v_ਸਰੋਤ,
                                                 w_ਕੁੰਜੀ_ਨਕਾਬ);
        v_ਨਿਸ਼ਾਨਾ = svsel_u32(svcmpeq_n_u32(v_ਪੂਛ_Pred, v_ਸਰੋਤ_Masked, w_ਕੁੰਜੀ),
                            v_ਨਿਸ਼ਾਨਾ,
                            svorr_n_u32_m(v_ਪੂਛ_Pred, v_ਸਰੋਤ, w_Opacify_ਨਕਾਬ));

        svst1_u32(v_ਪੂਛ_Pred, pw_ਨਿਸ਼ਾਨਾ, v_ਨਿਸ਼ਾਨਾ);

        pw_ਸਰੋਤ += sve_iteration_advance;
        pw_ਨਿਸ਼ਾਨਾ += sve_iteration_advance;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ sdl_sve_rgb32_stride_ਕੁੰਜੀ_no_alpha(
    uint32_t *SDL_RESTRICT pw_ਸਰੋਤ,
    uint32_t *SDL_RESTRICT pw_ਨਿਸ਼ਾਨਾ,
    size_t uStride,
    uint32_t w_ਕੁੰਜੀ,
    uint32_t w_ਕੁੰਜੀ_ਨਕਾਬ,
    uint32_t wActualRGBMask)
{
    sdl_sve_stride_loop_u32(uStride, v_ਪੂਛ_Pred)
    {
        svuint32_t v_ਸਰੋਤ = svld1_u32(v_ਪੂਛ_Pred, pw_ਸਰੋਤ);
        svuint32_t v_ਨਿਸ਼ਾਨਾ = svld1_u32(v_ਪੂਛ_Pred, pw_ਨਿਸ਼ਾਨਾ);

        /*
            uint32_t rgbmaskactual = srcfmt->Rmask | srcfmt->Gmask | srcfmt->Bmask;
            ...
            if ((*src32 & rgbmask) != ckey) {
                *dst32 = *src32 & rgbmaskactual;
            }
        */
        svuint32_t v_ਸਰੋਤ_Masked = svand_n_u32_m(v_ਪੂਛ_Pred,
                                                 v_ਸਰੋਤ,
                                                 w_ਕੁੰਜੀ_ਨਕਾਬ);
        v_ਨਿਸ਼ਾਨਾ = svsel_u32(svcmpeq_n_u32(v_ਪੂਛ_Pred, v_ਸਰੋਤ_Masked, w_ਕੁੰਜੀ),
                            v_ਨਿਸ਼ਾਨਾ,
                            svand_n_u32_m(v_ਪੂਛ_Pred, v_ਸਰੋਤ, wActualRGBMask));

        svst1_u32(v_ਪੂਛ_Pred, pw_ਨਿਸ਼ਾਨਾ, v_ਨਿਸ਼ਾਨਾ);

        pw_ਸਰੋਤ += sve_iteration_advance;
        pw_ਨਿਸ਼ਾਨਾ += sve_iteration_advance;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ sdl_sve_rgb32_ਕੁੰਜੀ_copy_alpha(uint8_t *SDL_RESTRICT pch_ਸਰੋਤ,
                                                size_t u_ਸਰੋਤ_Stride,
                                                uint8_t *SDL_RESTRICT pch_ਨਿਸ਼ਾਨਾ,
                                                size_t u_ਨਿਸ਼ਾਨਾ_Stride,
                                                ਪੂਰਨ n_ਚੌੜਾਈ,
                                                ਪੂਰਨ n_ਉਚਾਈ,
                                                uint32_t w_ਕੁੰਜੀ,
                                                uint32_t w_ਕੁੰਜੀ_ਨਕਾਬ,
                                                uint32_t w_Opacify_ਨਕਾਬ)
{
    ਪ੍ਰਤਿਜ੍ਞਾ(0 == ((uintptr_t)pch_ਸਰੋਤ & 0x03));
    ਪ੍ਰਤਿਜ੍ਞਾ(0 == ((uintptr_t)pch_ਨਿਸ਼ਾਨਾ & 0x03));

    ਜਦੋਂ (n_ਉਚਾਈ--) {
        sdl_sve_rgb32_stride_ਕੁੰਜੀ_copy_alpha((uint32_t *)pch_ਸਰੋਤ,
                                            (uint32_t *)pch_ਨਿਸ਼ਾਨਾ,
                                            n_ਚੌੜਾਈ,
                                            w_ਕੁੰਜੀ,
                                            w_ਕੁੰਜੀ_ਨਕਾਬ,
                                            w_Opacify_ਨਕਾਬ);

        pch_ਸਰੋਤ += u_ਸਰੋਤ_Stride;
        pch_ਨਿਸ਼ਾਨਾ += u_ਨਿਸ਼ਾਨਾ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ sdl_sve_rgb32_ਕੁੰਜੀ_no_alpha(uint8_t *SDL_RESTRICT pch_ਸਰੋਤ,
                                              size_t u_ਸਰੋਤ_Stride,
                                              uint8_t *SDL_RESTRICT pch_ਨਿਸ਼ਾਨਾ,
                                              size_t u_ਨਿਸ਼ਾਨਾ_Stride,
                                              ਪੂਰਨ n_ਚੌੜਾਈ,
                                              ਪੂਰਨ n_ਉਚਾਈ,
                                              uint32_t w_ਕੁੰਜੀ,
                                              uint32_t w_ਕੁੰਜੀ_ਨਕਾਬ,
                                              uint32_t wActualRGBMask)
{
    ਪ੍ਰਤਿਜ੍ਞਾ(0 == ((uintptr_t)pch_ਸਰੋਤ & 0x03));
    ਪ੍ਰਤਿਜ੍ਞਾ(0 == ((uintptr_t)pch_ਨਿਸ਼ਾਨਾ & 0x03));

    ਜਦੋਂ (n_ਉਚਾਈ--) {
        sdl_sve_rgb32_stride_ਕੁੰਜੀ_no_alpha((uint32_t *)pch_ਸਰੋਤ,
                                          (uint32_t *)pch_ਨਿਸ਼ਾਨਾ,
                                          n_ਚੌੜਾਈ,
                                          w_ਕੁੰਜੀ,
                                          w_ਕੁੰਜੀ_ਨਕਾਬ,
                                          wActualRGBMask);

        pch_ਸਰੋਤ += u_ਸਰੋਤ_Stride;
        pch_ਨਿਸ਼ਾਨਾ += u_ਨਿਸ਼ਾਨਾ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ਖਾਲੀ Blit4to4_ਕੁੰਜੀ_SVE2(SDL_BlitInfo *info)
{
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

    ਪ੍ਰਤਿਜ੍ਞਾ(srcbpp == 4);
    ਪ੍ਰਤਿਜ੍ਞਾ(dstbpp == 4);

    ਪੂਰਨ srcstride = srcskip + srcbpp * ਚੌੜਾਈ;
    ਪੂਰਨ dststride = dstskip + dstbpp * ਚੌੜਾਈ;

    uint32_t ckey = info->colorkey;
    uint32_t rgbmask = ~srcfmt->Amask;
    ckey &= rgbmask;

    ਜੇ (dstfmt->Amask) {
        uint32_t opamask = ((uint32_t)info->a) << dstfmt->Ashift;
        /* RGBA: set alpha from info->a */
        sdl_sve_rgb32_ਕੁੰਜੀ_copy_alpha(src,
                                     srcstride,
                                     dst,
                                     dststride,
                                     ਚੌੜਾਈ,
                                     ਉਚਾਈ,
                                     ckey,
                                     rgbmask,
                                     opamask);
    } ਨਹੀਂਤਾਂ {
        /* RGBA->RGB: only copy rgb and set alpha to zero */
        uint32_t rgbmaskactual = srcfmt->Rmask | srcfmt->Gmask | srcfmt->Bmask;
        sdl_sve_rgb32_ਕੁੰਜੀ_no_alpha(src,
                                   srcstride,
                                   dst,
                                   dststride,
                                   ਚੌੜਾਈ,
                                   ਉਚਾਈ,
                                   ckey,
                                   rgbmask,
                                   rgbmaskactual);
    }
}

#ਜੇ_ਅੰਤ /* SDL_SVE2_INTRINSICS */