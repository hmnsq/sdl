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

/*
 * IMPORTANT: Please do NOT include this header file directly or indirectly
 *            outside the src/video/arm folder.
 *
 */

#اگر !defined(SD_SVE2_SWIZZLE_H) //&& (defined(__ARM_FEATURE_SVE2) && __ARM_FEATURE_SVE2)
#تعریف_کرو SD_SVE2_SWIZZLE_H

#شامل "SDL_sve2_extension.h"

#تعریف_کرو sdl_sve_rgb32_stride_impl(ma_sve_chn_iterator, ...)   \
    sdl_sve_stride_loop_pixel(uStride, v_دم_Pred)             \
    {                                                         \
                                                              \
        svuint16x4_t v_ماخذ_Low16x4 = svundef4_u16();         \
        svuint16x4_t v_ماخذ_High16x4 = svundef4_u16();        \
                                                              \
        svuint16x4_t v_ہدف_Low16x4 = svundef4_u16();         \
        svuint16x4_t v_ہدف_High16x4 = svundef4_u16();        \
                                                              \
        svld4ub_u16(v_دم_Pred,                                \
                    (uint8_t *)pw_ماخذ,                      \
                    &v_ماخذ_Low16x4,                          \
                    &v_ماخذ_High16x4);                        \
                                                              \
        svld4ub_u16(v_دم_Pred,                                \
                    (uint8_t *)pw_ہدف,                      \
                    &v_ہدف_Low16x4,                          \
                    &v_ہدف_High16x4);                        \
                                                              \
        /* process low half */                                \
        ma_sve_chn_iterator(v_ماخذ_Low16x4, v_ہدف_Low16x4,   \
                            __VA_ARGS__);                     \
                                                              \
        /* process high half */                               \
        ma_sve_chn_iterator(v_ماخذ_High16x4, v_ہدف_High16x4, \
                            __VA_ARGS__);                     \
                                                              \
        svst4ub_u16(v_دم_Pred,                                \
                    (uint8_t *)pw_ہدف,                      \
                    v_ہدف_Low16x4,                           \
                    v_ہدف_High16x4);                         \
                                                              \
        pw_ماخذ += sve_iteration_advance;                    \
        pw_ہدف += sve_iteration_advance;                    \
    }

#تعریف_کرو sdl_sve_rgb32_no_alpha_stride_impl(                   \
    ma_alpha_idx,                                             \
    ma_sve_chn_iterator,                                      \
    ...)                                                      \
    sdl_sve_stride_loop_pixel(uStride, v_دم_Pred)             \
    {                                                         \
                                                              \
        svuint16x4_t v_ماخذ_Low16x4 = svundef4_u16();         \
        svuint16x4_t v_ماخذ_High16x4 = svundef4_u16();        \
                                                              \
        svuint16x4_t v_ہدف_Low16x4 = svundef4_u16();         \
        svuint16x4_t v_ہدف_High16x4 = svundef4_u16();        \
                                                              \
        svld4ub_u16(v_دم_Pred,                                \
                    (uint8_t *)pw_ماخذ,                      \
                    &v_ماخذ_Low16x4,                          \
                    &v_ماخذ_High16x4);                        \
                                                              \
        svld4ub_u16(v_دم_Pred,                                \
                    (uint8_t *)pw_ہدف,                      \
                    &v_ہدف_Low16x4,                          \
                    &v_ہدف_High16x4);                        \
                                                              \
        v_ماخذ_Low16x4 = svset4(v_ماخذ_Low16x4,               \
                                (ma_alpha_idx),               \
                                svdup_u16(0xFF));             \
        v_ماخذ_High16x4 = svset4(v_ماخذ_High16x4,             \
                                 (ma_alpha_idx),              \
                                 svdup_u16(0xFF));            \
                                                              \
        /* process low half */                                \
        ma_sve_chn_iterator(v_ماخذ_Low16x4, v_ہدف_Low16x4,   \
                            __VA_ARGS__);                     \
                                                              \
        /* process high half */                               \
        ma_sve_chn_iterator(v_ماخذ_High16x4, v_ہدف_High16x4, \
                            __VA_ARGS__);                     \
                                                              \
        svst4ub_u16(v_دم_Pred,                                \
                    (uint8_t *)pw_ہدف,                      \
                    v_ہدف_Low16x4,                           \
                    v_ہدف_High16x4);                         \
                                                              \
        pw_ماخذ += sve_iteration_advance;                    \
        pw_ہدف += sve_iteration_advance;                    \
    }

#تعریف_کرو sdl_sve_rgb32_مقصد_rgb565_stride_impl(ma_sve_chn_iterator, ...) \
    sdl_sve_stride_loop_pixel(uStride, v_دم_Pred)                     \
    {                                                                 \
                                                                      \
        svuint16x4_t v_ماخذ_Low16x4 = svundef4_u16();                 \
        svuint16x4_t v_ماخذ_High16x4 = svundef4_u16();                \
                                                                      \
        svuint16x3_t v_ہدف_Low16x3 = svundef3_u16();                 \
        svuint16x3_t v_ہدف_High16x3 = svundef3_u16();                \
                                                                      \
        svld4ub_u16(v_دم_Pred,                                        \
                    (uint8_t *)pw_ماخذ,                              \
                    &v_ماخذ_Low16x4,                                  \
                    &v_ماخذ_High16x4);                                \
                                                                      \
        svld3rgb565_u16(v_دم_Pred,                                    \
                        phw_ہدف,                                    \
                        &v_ہدف_Low16x3,                              \
                        &v_ہدف_High16x3);                            \
                                                                      \
        ma_sve_chn_iterator(v_ماخذ_Low16x4, v_ہدف_Low16x3,           \
                            __VA_ARGS__);                             \
                                                                      \
        ma_sve_chn_iterator(v_ماخذ_High16x4, v_ہدف_High16x3,         \
                            __VA_ARGS__);                             \
                                                                      \
        svst3rgb565_u16(v_دم_Pred,                                    \
                        phw_ہدف,                                    \
                        v_ہدف_Low16x3,                               \
                        v_ہدف_High16x3);                             \
                                                                      \
        pw_ماخذ += sve_iteration_advance;                            \
        phw_ہدف += sve_iteration_advance;                           \
    }

#تعریف_کرو sdl_sve_rgb32_no_alpha_مقصد_rgb565_stride_impl(         \
    ma_alpha_idx,                                             \
    ma_sve_chn_iterator,                                      \
    ...)                                                      \
    sdl_sve_stride_loop_pixel(uStride, v_دم_Pred)             \
    {                                                         \
                                                              \
        svuint16x4_t v_ماخذ_Low16x4 = svundef4_u16();         \
        svuint16x4_t v_ماخذ_High16x4 = svundef4_u16();        \
                                                              \
        svuint16x3_t v_ہدف_Low16x3 = svundef3_u16();         \
        svuint16x3_t v_ہدف_High16x3 = svundef3_u16();        \
                                                              \
        svld4ub_u16(v_دم_Pred,                                \
                    (uint8_t *)pw_ماخذ,                      \
                    &v_ماخذ_Low16x4,                          \
                    &v_ماخذ_High16x4);                        \
                                                              \
        v_ماخذ_Low16x4 = svset4(v_ماخذ_Low16x4,               \
                                (ma_alpha_idx),               \
                                svdup_u16(0xFF));             \
        v_ماخذ_High16x4 = svset4(v_ماخذ_High16x4,             \
                                 (ma_alpha_idx),              \
                                 svdup_u16(0xFF));            \
                                                              \
        svld3rgb565_u16(v_دم_Pred,                            \
                        phw_ہدف,                            \
                        &v_ہدف_Low16x3,                      \
                        &v_ہدف_High16x3);                    \
                                                              \
        ma_sve_chn_iterator(v_ماخذ_Low16x4, v_ہدف_Low16x3,   \
                            __VA_ARGS__);                     \
                                                              \
        ma_sve_chn_iterator(v_ماخذ_High16x4, v_ہدف_High16x3, \
                            __VA_ARGS__);                     \
                                                              \
        svst3rgb565_u16(v_دم_Pred,                            \
                        phw_ہدف,                            \
                        v_ہدف_Low16x3,                       \
                        v_ہدف_High16x3);                     \
                                                              \
        pw_ماخذ += sve_iteration_advance;                    \
        phw_ہدف += sve_iteration_advance;                   \
    }

#اگر_غیر_تعریف_شدہ sdl_sve_rgb32_blend_op_fill_alpha
#تعریف_کرو sdl_sve_rgb32_blend_op_fill_alpha(ma_alpha_chn_idx)
#اگر_ختم

#اگر_غیر_تعریف_شدہ sdl_sve_rgb32_blend_op_copy_alpha
#تعریف_کرو sdl_sve_rgb32_blend_op_copy_alpha(ma_alpha_chn_idx)
#اگر_ختم

/*
 * Source: ACCC and CCCA
 */
SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساکن اندرونی خالی sdl_sve_accc_stride_blend_مقصد_accc_fill_alpha(
    uint32_t *SDL_RESTRICT pw_ماخذ,
    uint32_t *SDL_RESTRICT pw_ہدف,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn,

                              sdl_sve_rgb32_blend_op_fill_alpha(3);

    );
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساکن اندرونی خالی sdl_sve_accc_stride_blend_مقصد_accc_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ماخذ,
    uint32_t *SDL_RESTRICT pw_ہدف,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn,
                              sdl_sve_rgb32_blend_op_copy_alpha(3););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساکن اندرونی خالی sdl_sve_ccca_stride_blend_مقصد_ccca_fill_alpha(
    uint32_t *SDL_RESTRICT pw_ماخذ,
    uint32_t *SDL_RESTRICT pw_ہدف,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn,
                              sdl_sve_rgb32_blend_op_fill_alpha(0););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساکن اندرونی خالی sdl_sve_ccca_stride_blend_مقصد_ccca_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ماخذ,
    uint32_t *SDL_RESTRICT pw_ہدف,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn,

                              sdl_sve_rgb32_blend_op_copy_alpha(0);

    );
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساکن اندرونی خالی sdl_sve_accc_blend_مقصد_accc_fill_alpha(
    uint8_t *SDL_RESTRICT pch_ماخذ,
    size_t u_ماخذ_Stride,
    uint8_t *SDL_RESTRICT pch_ہدف,
    size_t u_ہدف_Stride,
    صحیح n_چوڑائی,
    صحیح n_اونچائی)
{
    جب (n_اونچائی--) {

        sdl_sve_accc_stride_blend_مقصد_accc_fill_alpha(
            (uint32_t *)pch_ماخذ,
            (uint32_t *)pch_ہدف,
            n_چوڑائی);

        pch_ماخذ += u_ماخذ_Stride;
        pch_ہدف += u_ہدف_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساکن اندرونی خالی sdl_sve_accc_blend_مقصد_accc_copy_alpha(
    uint8_t *SDL_RESTRICT pch_ماخذ,
    size_t u_ماخذ_Stride,
    uint8_t *SDL_RESTRICT pch_ہدف,
    size_t u_ہدف_Stride,
    صحیح n_چوڑائی,
    صحیح n_اونچائی)
{
    جب (n_اونچائی--) {

        sdl_sve_accc_stride_blend_مقصد_accc_copy_alpha(
            (uint32_t *)pch_ماخذ,
            (uint32_t *)pch_ہدف,
            n_چوڑائی);

        pch_ماخذ += u_ماخذ_Stride;
        pch_ہدف += u_ہدف_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساکن اندرونی خالی sdl_sve_ccca_blend_مقصد_ccca_fill_alpha(
    uint8_t *SDL_RESTRICT pch_ماخذ,
    size_t u_ماخذ_Stride,
    uint8_t *SDL_RESTRICT pch_ہدف,
    size_t u_ہدف_Stride,
    صحیح n_چوڑائی,
    صحیح n_اونچائی)
{
    جب (n_اونچائی--) {

        sdl_sve_ccca_stride_blend_مقصد_ccca_fill_alpha(
            (uint32_t *)pch_ماخذ,
            (uint32_t *)pch_ہدف,
            n_چوڑائی);

        pch_ماخذ += u_ماخذ_Stride;
        pch_ہدف += u_ہدف_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساکن اندرونی خالی sdl_sve_ccca_blend_مقصد_ccca_copy_alpha(
    uint8_t *SDL_RESTRICT pch_ماخذ,
    size_t u_ماخذ_Stride,
    uint8_t *SDL_RESTRICT pch_ہدف,
    size_t u_ہدف_Stride,
    صحیح n_چوڑائی,
    صحیح n_اونچائی)
{
    جب (n_اونچائی--) {

        sdl_sve_ccca_stride_blend_مقصد_ccca_copy_alpha(
            (uint32_t *)pch_ماخذ,
            (uint32_t *)pch_ہدف,
            n_چوڑائی);

        pch_ماخذ += u_ماخذ_Stride;
        pch_ہدف += u_ہدف_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساکن اندرونی خالی sdl_sve_a123_stride_blend_مقصد_321a_fill_alpha(
    uint32_t *SDL_RESTRICT pw_ماخذ,
    uint32_t *SDL_RESTRICT pw_ہدف,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn_src_dst_rev,
                              sdl_sve_rgb32_blend_op_fill_alpha(3);

    );
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساکن اندرونی خالی sdl_sve_a123_stride_blend_مقصد_321a_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ماخذ,
    uint32_t *SDL_RESTRICT pw_ہدف,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn_src_dst_rev,
                              sdl_sve_rgb32_blend_op_copy_alpha(3);

    );
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساکن اندرونی خالی sdl_sve_a123_blend_مقصد_321a_fill_alpha(uint8_t *SDL_RESTRICT pch_ماخذ,
                                                         size_t u_ماخذ_Stride,
                                                         uint8_t *SDL_RESTRICT pch_ہدف,
                                                         size_t u_ہدف_Stride,
                                                         صحیح n_چوڑائی,
                                                         صحیح n_اونچائی)
{
    جب (n_اونچائی--) {

        sdl_sve_a123_stride_blend_مقصد_321a_fill_alpha((uint32_t *)pch_ماخذ,
                                                     (uint32_t *)pch_ہدف,
                                                     n_چوڑائی);

        pch_ماخذ += u_ماخذ_Stride;
        pch_ہدف += u_ہدف_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساکن اندرونی خالی sdl_sve_a123_blend_مقصد_321a_copy_alpha(uint8_t *SDL_RESTRICT pch_ماخذ,
                                                         size_t u_ماخذ_Stride,
                                                         uint8_t *SDL_RESTRICT pch_ہدف,
                                                         size_t u_ہدف_Stride,
                                                         صحیح n_چوڑائی,
                                                         صحیح n_اونچائی)
{
    جب (n_اونچائی--) {

        sdl_sve_a123_stride_blend_مقصد_321a_copy_alpha((uint32_t *)pch_ماخذ,
                                                     (uint32_t *)pch_ہدف,
                                                     n_چوڑائی);

        pch_ماخذ += u_ماخذ_Stride;
        pch_ہدف += u_ہدف_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساکن اندرونی خالی sdl_sve_123a_stride_blend_مقصد_a321_fill_alpha(
    uint32_t *SDL_RESTRICT pw_ماخذ,
    uint32_t *SDL_RESTRICT pw_ہدف,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn_src_dst_rev,
                              sdl_sve_rgb32_blend_op_fill_alpha(0);

    );
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساکن اندرونی خالی sdl_sve_123a_stride_blend_مقصد_a321_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ماخذ,
    uint32_t *SDL_RESTRICT pw_ہدف,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn_src_dst_rev,
                              sdl_sve_rgb32_blend_op_copy_alpha(0);

    );
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساکن اندرونی خالی sdl_sve_123a_blend_مقصد_a321_fill_alpha(uint8_t *SDL_RESTRICT pch_ماخذ,
                                                         size_t u_ماخذ_Stride,
                                                         uint8_t *SDL_RESTRICT pch_ہدف,
                                                         size_t u_ہدف_Stride,
                                                         صحیح n_چوڑائی,
                                                         صحیح n_اونچائی)
{
    جب (n_اونچائی--) {

        sdl_sve_123a_stride_blend_مقصد_a321_fill_alpha((uint32_t *)pch_ماخذ,
                                                     (uint32_t *)pch_ہدف,
                                                     n_چوڑائی);

        pch_ماخذ += u_ماخذ_Stride;
        pch_ہدف += u_ہدف_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساکن اندرونی خالی sdl_sve_123a_blend_مقصد_a321_copy_alpha(uint8_t *SDL_RESTRICT pch_ماخذ,
                                                         size_t u_ماخذ_Stride,
                                                         uint8_t *SDL_RESTRICT pch_ہدف,
                                                         size_t u_ہدف_Stride,
                                                         صحیح n_چوڑائی,
                                                         صحیح n_اونچائی)
{
    جب (n_اونچائی--) {

        sdl_sve_123a_stride_blend_مقصد_a321_copy_alpha((uint32_t *)pch_ماخذ,
                                                     (uint32_t *)pch_ہدف,
                                                     n_چوڑائی);

        pch_ماخذ += u_ماخذ_Stride;
        pch_ہدف += u_ہدف_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساکن اندرونی خالی sdl_sve_accc_stride_blend_مقصد_ccca_fill_alpha(
    uint32_t *SDL_RESTRICT pw_ماخذ,
    uint32_t *SDL_RESTRICT pw_ہدف,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn_accc_ccca,
                              sdl_sve_rgb32_blend_op_fill_alpha(3);

    );
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساکن اندرونی خالی sdl_sve_accc_stride_blend_مقصد_ccca_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ماخذ,
    uint32_t *SDL_RESTRICT pw_ہدف,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn_accc_ccca,
                              sdl_sve_rgb32_blend_op_copy_alpha(3);

    );
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساکن اندرونی خالی sdl_sve_accc_blend_مقصد_ccca_fill_alpha(uint8_t *SDL_RESTRICT pch_ماخذ,
                                                         size_t u_ماخذ_Stride,
                                                         uint8_t *SDL_RESTRICT pch_ہدف,
                                                         size_t u_ہدف_Stride,
                                                         صحیح n_چوڑائی,
                                                         صحیح n_اونچائی)
{
    جب (n_اونچائی--) {

        sdl_sve_accc_stride_blend_مقصد_ccca_fill_alpha((uint32_t *)pch_ماخذ,
                                                     (uint32_t *)pch_ہدف,
                                                     n_چوڑائی);

        pch_ماخذ += u_ماخذ_Stride;
        pch_ہدف += u_ہدف_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساکن اندرونی خالی sdl_sve_accc_blend_مقصد_ccca_copy_alpha(uint8_t *SDL_RESTRICT pch_ماخذ,
                                                         size_t u_ماخذ_Stride,
                                                         uint8_t *SDL_RESTRICT pch_ہدف,
                                                         size_t u_ہدف_Stride,
                                                         صحیح n_چوڑائی,
                                                         صحیح n_اونچائی)
{
    جب (n_اونچائی--) {

        sdl_sve_accc_stride_blend_مقصد_ccca_copy_alpha((uint32_t *)pch_ماخذ,
                                                     (uint32_t *)pch_ہدف,
                                                     n_چوڑائی);

        pch_ماخذ += u_ماخذ_Stride;
        pch_ہدف += u_ہدف_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساکن اندرونی خالی sdl_sve_ccca_stride_blend_مقصد_accc_fill_alpha(
    uint32_t *SDL_RESTRICT pw_ماخذ,
    uint32_t *SDL_RESTRICT pw_ہدف,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn_ccca_accc,
                              sdl_sve_rgb32_blend_op_fill_alpha(0);

    );
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساکن اندرونی خالی sdl_sve_ccca_stride_blend_مقصد_accc_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ماخذ,
    uint32_t *SDL_RESTRICT pw_ہدف,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn_ccca_accc,
                              sdl_sve_rgb32_blend_op_copy_alpha(0););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساکن اندرونی خالی sdl_sve_ccca_blend_مقصد_accc_fill_alpha(uint8_t *SDL_RESTRICT pch_ماخذ,
                                                         size_t u_ماخذ_Stride,
                                                         uint8_t *SDL_RESTRICT pch_ہدف,
                                                         size_t u_ہدف_Stride,
                                                         صحیح n_چوڑائی,
                                                         صحیح n_اونچائی)
{
    جب (n_اونچائی--) {

        sdl_sve_ccca_stride_blend_مقصد_accc_fill_alpha((uint32_t *)pch_ماخذ,
                                                     (uint32_t *)pch_ہدف,
                                                     n_چوڑائی);

        pch_ماخذ += u_ماخذ_Stride;
        pch_ہدف += u_ہدف_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساکن اندرونی خالی sdl_sve_ccca_blend_مقصد_accc_copy_alpha(uint8_t *SDL_RESTRICT pch_ماخذ,
                                                         size_t u_ماخذ_Stride,
                                                         uint8_t *SDL_RESTRICT pch_ہدف,
                                                         size_t u_ہدف_Stride,
                                                         صحیح n_چوڑائی,
                                                         صحیح n_اونچائی)
{
    جب (n_اونچائی--) {

        sdl_sve_ccca_stride_blend_مقصد_accc_copy_alpha((uint32_t *)pch_ماخذ,
                                                     (uint32_t *)pch_ہدف,
                                                     n_چوڑائی);

        pch_ماخذ += u_ماخذ_Stride;
        pch_ہدف += u_ہدف_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساکن اندرونی خالی sdl_sve_a123_stride_blend_مقصد_a321_fill_alpha(
    uint32_t *SDL_RESTRICT pw_ماخذ,
    uint32_t *SDL_RESTRICT pw_ہدف,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn_a123_a321,
                              sdl_sve_rgb32_blend_op_fill_alpha(3););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساکن اندرونی خالی sdl_sve_a123_stride_blend_مقصد_a321_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ماخذ,
    uint32_t *SDL_RESTRICT pw_ہدف,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn_a123_a321,
                              sdl_sve_rgb32_blend_op_copy_alpha(3););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساکن اندرونی خالی sdl_sve_a123_blend_مقصد_a321_fill_alpha(uint8_t *SDL_RESTRICT pch_ماخذ,
                                                         size_t u_ماخذ_Stride,
                                                         uint8_t *SDL_RESTRICT pch_ہدف,
                                                         size_t u_ہدف_Stride,
                                                         صحیح n_چوڑائی,
                                                         صحیح n_اونچائی)
{
    جب (n_اونچائی--) {

        sdl_sve_a123_stride_blend_مقصد_a321_fill_alpha((uint32_t *)pch_ماخذ,
                                                     (uint32_t *)pch_ہدف,
                                                     n_چوڑائی);

        pch_ماخذ += u_ماخذ_Stride;
        pch_ہدف += u_ہدف_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساکن اندرونی خالی sdl_sve_a123_blend_مقصد_a321_copy_alpha(uint8_t *SDL_RESTRICT pch_ماخذ,
                                                         size_t u_ماخذ_Stride,
                                                         uint8_t *SDL_RESTRICT pch_ہدف,
                                                         size_t u_ہدف_Stride,
                                                         صحیح n_چوڑائی,
                                                         صحیح n_اونچائی)
{
    جب (n_اونچائی--) {

        sdl_sve_a123_stride_blend_مقصد_a321_copy_alpha((uint32_t *)pch_ماخذ,
                                                     (uint32_t *)pch_ہدف,
                                                     n_چوڑائی);

        pch_ماخذ += u_ماخذ_Stride;
        pch_ہدف += u_ہدف_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساکن اندرونی خالی sdl_sve_123a_stride_blend_مقصد_321a_fill_alpha(
    uint32_t *SDL_RESTRICT pw_ماخذ,
    uint32_t *SDL_RESTRICT pw_ہدف,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn_123a_321a,
                              sdl_sve_rgb32_blend_op_fill_alpha(0););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساکن اندرونی خالی sdl_sve_123a_stride_blend_مقصد_321a_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ماخذ,
    uint32_t *SDL_RESTRICT pw_ہدف,
    size_t uStride)
{
    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn_123a_321a,
                              sdl_sve_rgb32_blend_op_copy_alpha(0););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساکن اندرونی خالی sdl_sve_123a_blend_مقصد_321a_fill_alpha(uint8_t *SDL_RESTRICT pch_ماخذ,
                                                         size_t u_ماخذ_Stride,
                                                         uint8_t *SDL_RESTRICT pch_ہدف,
                                                         size_t u_ہدف_Stride,
                                                         صحیح n_چوڑائی,
                                                         صحیح n_اونچائی)
{
    جب (n_اونچائی--) {

        sdl_sve_123a_stride_blend_مقصد_321a_fill_alpha((uint32_t *)pch_ماخذ,
                                                     (uint32_t *)pch_ہدف,
                                                     n_چوڑائی);

        pch_ماخذ += u_ماخذ_Stride;
        pch_ہدف += u_ہدف_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساکن اندرونی خالی sdl_sve_123a_blend_مقصد_321a_copy_alpha(uint8_t *SDL_RESTRICT pch_ماخذ,
                                                         size_t u_ماخذ_Stride,
                                                         uint8_t *SDL_RESTRICT pch_ہدف,
                                                         size_t u_ہدف_Stride,
                                                         صحیح n_چوڑائی,
                                                         صحیح n_اونچائی)
{
    جب (n_اونچائی--) {

        sdl_sve_123a_stride_blend_مقصد_321a_copy_alpha((uint32_t *)pch_ماخذ,
                                                     (uint32_t *)pch_ہدف,
                                                     n_چوڑائی);

        pch_ماخذ += u_ماخذ_Stride;
        pch_ہدف += u_ہدف_Stride;
    }
}

/*
 * Source: XCCC and CCCX
 */

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساکن اندرونی خالی sdl_sve_xccc_stride_blend_مقصد_accc_fill_alpha(
    uint32_t *SDL_RESTRICT pw_ماخذ,
    uint32_t *SDL_RESTRICT pw_ہدف,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(3,
                                       sdl_sve_pixel_u16x4_foreach_chn,
                                       sdl_sve_rgb32_blend_op_fill_alpha(3););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساکن اندرونی خالی sdl_sve_xccc_stride_blend_مقصد_accc_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ماخذ,
    uint32_t *SDL_RESTRICT pw_ہدف,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(3,
                                       sdl_sve_pixel_u16x4_foreach_chn,
                                       sdl_sve_rgb32_blend_op_copy_alpha(3););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساکن اندرونی خالی sdl_sve_cccx_stride_blend_مقصد_ccca_fill_alpha(
    uint32_t *SDL_RESTRICT pw_ماخذ,
    uint32_t *SDL_RESTRICT pw_ہدف,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(0,
                                       sdl_sve_pixel_u16x4_foreach_chn,
                                       sdl_sve_rgb32_blend_op_fill_alpha(0);

    );
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساکن اندرونی خالی sdl_sve_cccx_stride_blend_مقصد_ccca_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ماخذ,
    uint32_t *SDL_RESTRICT pw_ہدف,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(0,
                                       sdl_sve_pixel_u16x4_foreach_chn,
                                       sdl_sve_rgb32_blend_op_copy_alpha(0););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساکن اندرونی خالی sdl_sve_xccc_blend_مقصد_accc_fill_alpha(
    uint8_t *SDL_RESTRICT pch_ماخذ,
    size_t u_ماخذ_Stride,
    uint8_t *SDL_RESTRICT pch_ہدف,
    size_t u_ہدف_Stride,
    صحیح n_چوڑائی,
    صحیح n_اونچائی)
{
    جب (n_اونچائی--) {

        sdl_sve_xccc_stride_blend_مقصد_accc_fill_alpha(
            (uint32_t *)pch_ماخذ,
            (uint32_t *)pch_ہدف,
            n_چوڑائی);

        pch_ماخذ += u_ماخذ_Stride;
        pch_ہدف += u_ہدف_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساکن اندرونی خالی sdl_sve_xccc_blend_مقصد_accc_copy_alpha(
    uint8_t *SDL_RESTRICT pch_ماخذ,
    size_t u_ماخذ_Stride,
    uint8_t *SDL_RESTRICT pch_ہدف,
    size_t u_ہدف_Stride,
    صحیح n_چوڑائی,
    صحیح n_اونچائی)
{
    جب (n_اونچائی--) {

        sdl_sve_xccc_stride_blend_مقصد_accc_copy_alpha(
            (uint32_t *)pch_ماخذ,
            (uint32_t *)pch_ہدف,
            n_چوڑائی);

        pch_ماخذ += u_ماخذ_Stride;
        pch_ہدف += u_ہدف_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساکن اندرونی خالی sdl_sve_cccx_blend_مقصد_ccca_fill_alpha(
    uint8_t *SDL_RESTRICT pch_ماخذ,
    size_t u_ماخذ_Stride,
    uint8_t *SDL_RESTRICT pch_ہدف,
    size_t u_ہدف_Stride,
    صحیح n_چوڑائی,
    صحیح n_اونچائی)
{
    جب (n_اونچائی--) {

        sdl_sve_cccx_stride_blend_مقصد_ccca_fill_alpha(
            (uint32_t *)pch_ماخذ,
            (uint32_t *)pch_ہدف,
            n_چوڑائی);

        pch_ماخذ += u_ماخذ_Stride;
        pch_ہدف += u_ہدف_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساکن اندرونی خالی sdl_sve_cccx_blend_مقصد_ccca_copy_alpha(
    uint8_t *SDL_RESTRICT pch_ماخذ,
    size_t u_ماخذ_Stride,
    uint8_t *SDL_RESTRICT pch_ہدف,
    size_t u_ہدف_Stride,
    صحیح n_چوڑائی,
    صحیح n_اونچائی)
{
    جب (n_اونچائی--) {

        sdl_sve_cccx_stride_blend_مقصد_ccca_copy_alpha(
            (uint32_t *)pch_ماخذ,
            (uint32_t *)pch_ہدف,
            n_چوڑائی);

        pch_ماخذ += u_ماخذ_Stride;
        pch_ہدف += u_ہدف_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساکن اندرونی خالی sdl_sve_x123_stride_blend_مقصد_321a_fill_alpha(
    uint32_t *SDL_RESTRICT pw_ماخذ,
    uint32_t *SDL_RESTRICT pw_ہدف,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(3,
                                       sdl_sve_pixel_u16x4_foreach_chn_src_dst_rev,
                                       sdl_sve_rgb32_blend_op_fill_alpha(3););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساکن اندرونی خالی sdl_sve_x123_stride_blend_مقصد_321a_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ماخذ,
    uint32_t *SDL_RESTRICT pw_ہدف,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(3,
                                       sdl_sve_pixel_u16x4_foreach_chn_src_dst_rev,
                                       sdl_sve_rgb32_blend_op_copy_alpha(3););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساکن اندرونی خالی sdl_sve_x123_blend_مقصد_321a_fill_alpha(uint8_t *SDL_RESTRICT pch_ماخذ,
                                                         size_t u_ماخذ_Stride,
                                                         uint8_t *SDL_RESTRICT pch_ہدف,
                                                         size_t u_ہدف_Stride,
                                                         صحیح n_چوڑائی,
                                                         صحیح n_اونچائی)
{
    جب (n_اونچائی--) {

        sdl_sve_x123_stride_blend_مقصد_321a_fill_alpha((uint32_t *)pch_ماخذ,
                                                     (uint32_t *)pch_ہدف,
                                                     n_چوڑائی);

        pch_ماخذ += u_ماخذ_Stride;
        pch_ہدف += u_ہدف_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساکن اندرونی خالی sdl_sve_x123_blend_مقصد_321a_copy_alpha(uint8_t *SDL_RESTRICT pch_ماخذ,
                                                         size_t u_ماخذ_Stride,
                                                         uint8_t *SDL_RESTRICT pch_ہدف,
                                                         size_t u_ہدف_Stride,
                                                         صحیح n_چوڑائی,
                                                         صحیح n_اونچائی)
{
    جب (n_اونچائی--) {

        sdl_sve_x123_stride_blend_مقصد_321a_copy_alpha((uint32_t *)pch_ماخذ,
                                                     (uint32_t *)pch_ہدف,
                                                     n_چوڑائی);

        pch_ماخذ += u_ماخذ_Stride;
        pch_ہدف += u_ہدف_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساکن اندرونی خالی sdl_sve_123x_stride_blend_مقصد_a321_fill_alpha(
    uint32_t *SDL_RESTRICT pw_ماخذ,
    uint32_t *SDL_RESTRICT pw_ہدف,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(0,
                                       sdl_sve_pixel_u16x4_foreach_chn_src_dst_rev,
                                       sdl_sve_rgb32_blend_op_fill_alpha(0););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساکن اندرونی خالی sdl_sve_123x_stride_blend_مقصد_a321_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ماخذ,
    uint32_t *SDL_RESTRICT pw_ہدف,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(0,
                                       sdl_sve_pixel_u16x4_foreach_chn_src_dst_rev,
                                       sdl_sve_rgb32_blend_op_copy_alpha(0););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساکن اندرونی خالی sdl_sve_123x_blend_مقصد_a321_fill_alpha(uint8_t *SDL_RESTRICT pch_ماخذ,
                                                         size_t u_ماخذ_Stride,
                                                         uint8_t *SDL_RESTRICT pch_ہدف,
                                                         size_t u_ہدف_Stride,
                                                         صحیح n_چوڑائی,
                                                         صحیح n_اونچائی)
{
    جب (n_اونچائی--) {

        sdl_sve_123x_stride_blend_مقصد_a321_fill_alpha((uint32_t *)pch_ماخذ,
                                                     (uint32_t *)pch_ہدف,
                                                     n_چوڑائی);

        pch_ماخذ += u_ماخذ_Stride;
        pch_ہدف += u_ہدف_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساکن اندرونی خالی sdl_sve_123x_blend_مقصد_a321_copy_alpha(uint8_t *SDL_RESTRICT pch_ماخذ,
                                                         size_t u_ماخذ_Stride,
                                                         uint8_t *SDL_RESTRICT pch_ہدف,
                                                         size_t u_ہدف_Stride,
                                                         صحیح n_چوڑائی,
                                                         صحیح n_اونچائی)
{
    جب (n_اونچائی--) {

        sdl_sve_123x_stride_blend_مقصد_a321_copy_alpha((uint32_t *)pch_ماخذ,
                                                     (uint32_t *)pch_ہدف,
                                                     n_چوڑائی);

        pch_ماخذ += u_ماخذ_Stride;
        pch_ہدف += u_ہدف_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساکن اندرونی خالی sdl_sve_xccc_stride_blend_مقصد_ccca_fill_alpha(
    uint32_t *SDL_RESTRICT pw_ماخذ,
    uint32_t *SDL_RESTRICT pw_ہدف,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(3,
                                       sdl_sve_pixel_u16x4_foreach_chn_accc_ccca,
                                       sdl_sve_rgb32_blend_op_fill_alpha(3););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساکن اندرونی خالی sdl_sve_xccc_stride_blend_مقصد_ccca_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ماخذ,
    uint32_t *SDL_RESTRICT pw_ہدف,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(3,
                                       sdl_sve_pixel_u16x4_foreach_chn_accc_ccca,
                                       sdl_sve_rgb32_blend_op_copy_alpha(3););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساکن اندرونی خالی sdl_sve_xccc_blend_مقصد_ccca_fill_alpha(uint8_t *SDL_RESTRICT pch_ماخذ,
                                                         size_t u_ماخذ_Stride,
                                                         uint8_t *SDL_RESTRICT pch_ہدف,
                                                         size_t u_ہدف_Stride,
                                                         صحیح n_چوڑائی,
                                                         صحیح n_اونچائی)
{
    جب (n_اونچائی--) {

        sdl_sve_xccc_stride_blend_مقصد_ccca_fill_alpha((uint32_t *)pch_ماخذ,
                                                     (uint32_t *)pch_ہدف,
                                                     n_چوڑائی);

        pch_ماخذ += u_ماخذ_Stride;
        pch_ہدف += u_ہدف_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساکن اندرونی خالی sdl_sve_xccc_blend_مقصد_ccca_copy_alpha(uint8_t *SDL_RESTRICT pch_ماخذ,
                                                         size_t u_ماخذ_Stride,
                                                         uint8_t *SDL_RESTRICT pch_ہدف,
                                                         size_t u_ہدف_Stride,
                                                         صحیح n_چوڑائی,
                                                         صحیح n_اونچائی)
{
    جب (n_اونچائی--) {

        sdl_sve_xccc_stride_blend_مقصد_ccca_copy_alpha((uint32_t *)pch_ماخذ,
                                                     (uint32_t *)pch_ہدف,
                                                     n_چوڑائی);

        pch_ماخذ += u_ماخذ_Stride;
        pch_ہدف += u_ہدف_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساکن اندرونی خالی sdl_sve_cccx_stride_blend_مقصد_accc_fill_alpha(
    uint32_t *SDL_RESTRICT pw_ماخذ,
    uint32_t *SDL_RESTRICT pw_ہدف,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(0,
                                       sdl_sve_pixel_u16x4_foreach_chn_ccca_accc,
                                       sdl_sve_rgb32_blend_op_fill_alpha(0););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساکن اندرونی خالی sdl_sve_cccx_stride_blend_مقصد_accc_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ماخذ,
    uint32_t *SDL_RESTRICT pw_ہدف,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(0,
                                       sdl_sve_pixel_u16x4_foreach_chn_ccca_accc,
                                       sdl_sve_rgb32_blend_op_copy_alpha(0););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساکن اندرونی خالی sdl_sve_cccx_blend_مقصد_accc_fill_alpha(uint8_t *SDL_RESTRICT pch_ماخذ,
                                                         size_t u_ماخذ_Stride,
                                                         uint8_t *SDL_RESTRICT pch_ہدف,
                                                         size_t u_ہدف_Stride,
                                                         صحیح n_چوڑائی,
                                                         صحیح n_اونچائی)
{
    جب (n_اونچائی--) {

        sdl_sve_cccx_stride_blend_مقصد_accc_fill_alpha((uint32_t *)pch_ماخذ,
                                                     (uint32_t *)pch_ہدف,
                                                     n_چوڑائی);

        pch_ماخذ += u_ماخذ_Stride;
        pch_ہدف += u_ہدف_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساکن اندرونی خالی sdl_sve_cccx_blend_مقصد_accc_copy_alpha(uint8_t *SDL_RESTRICT pch_ماخذ,
                                                         size_t u_ماخذ_Stride,
                                                         uint8_t *SDL_RESTRICT pch_ہدف,
                                                         size_t u_ہدف_Stride,
                                                         صحیح n_چوڑائی,
                                                         صحیح n_اونچائی)
{
    جب (n_اونچائی--) {

        sdl_sve_cccx_stride_blend_مقصد_accc_copy_alpha((uint32_t *)pch_ماخذ,
                                                     (uint32_t *)pch_ہدف,
                                                     n_چوڑائی);

        pch_ماخذ += u_ماخذ_Stride;
        pch_ہدف += u_ہدف_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساکن اندرونی خالی sdl_sve_x123_stride_blend_مقصد_a321_fill_alpha(
    uint32_t *SDL_RESTRICT pw_ماخذ,
    uint32_t *SDL_RESTRICT pw_ہدف,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(3,
                                       sdl_sve_pixel_u16x4_foreach_chn_a123_a321,
                                       sdl_sve_rgb32_blend_op_fill_alpha(3););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساکن اندرونی خالی sdl_sve_x123_stride_blend_مقصد_a321_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ماخذ,
    uint32_t *SDL_RESTRICT pw_ہدف,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(3,
                                       sdl_sve_pixel_u16x4_foreach_chn_a123_a321,
                                       sdl_sve_rgb32_blend_op_copy_alpha(3););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساکن اندرونی خالی sdl_sve_x123_blend_مقصد_a321_fill_alpha(uint8_t *SDL_RESTRICT pch_ماخذ,
                                                         size_t u_ماخذ_Stride,
                                                         uint8_t *SDL_RESTRICT pch_ہدف,
                                                         size_t u_ہدف_Stride,
                                                         صحیح n_چوڑائی,
                                                         صحیح n_اونچائی)
{
    جب (n_اونچائی--) {

        sdl_sve_x123_stride_blend_مقصد_a321_fill_alpha((uint32_t *)pch_ماخذ,
                                                     (uint32_t *)pch_ہدف,
                                                     n_چوڑائی);

        pch_ماخذ += u_ماخذ_Stride;
        pch_ہدف += u_ہدف_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساکن اندرونی خالی sdl_sve_x123_blend_مقصد_a321_copy_alpha(uint8_t *SDL_RESTRICT pch_ماخذ,
                                                         size_t u_ماخذ_Stride,
                                                         uint8_t *SDL_RESTRICT pch_ہدف,
                                                         size_t u_ہدف_Stride,
                                                         صحیح n_چوڑائی,
                                                         صحیح n_اونچائی)
{
    جب (n_اونچائی--) {

        sdl_sve_x123_stride_blend_مقصد_a321_copy_alpha((uint32_t *)pch_ماخذ,
                                                     (uint32_t *)pch_ہدف,
                                                     n_چوڑائی);

        pch_ماخذ += u_ماخذ_Stride;
        pch_ہدف += u_ہدف_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساکن اندرونی خالی sdl_sve_123x_stride_blend_مقصد_321a_fill_alpha(
    uint32_t *SDL_RESTRICT pw_ماخذ,
    uint32_t *SDL_RESTRICT pw_ہدف,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(0,
                                       sdl_sve_pixel_u16x4_foreach_chn_123a_321a,
                                       sdl_sve_rgb32_blend_op_fill_alpha(0););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساکن اندرونی خالی sdl_sve_123x_stride_blend_مقصد_321a_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ماخذ,
    uint32_t *SDL_RESTRICT pw_ہدف,
    size_t uStride)
{
    sdl_sve_rgb32_no_alpha_stride_impl(0,
                                       sdl_sve_pixel_u16x4_foreach_chn_123a_321a,
                                       sdl_sve_rgb32_blend_op_copy_alpha(0););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساکن اندرونی خالی sdl_sve_123x_blend_مقصد_321a_fill_alpha(uint8_t *SDL_RESTRICT pch_ماخذ,
                                                         size_t u_ماخذ_Stride,
                                                         uint8_t *SDL_RESTRICT pch_ہدف,
                                                         size_t u_ہدف_Stride,
                                                         صحیح n_چوڑائی,
                                                         صحیح n_اونچائی)
{
    جب (n_اونچائی--) {

        sdl_sve_123x_stride_blend_مقصد_321a_fill_alpha((uint32_t *)pch_ماخذ,
                                                     (uint32_t *)pch_ہدف,
                                                     n_چوڑائی);

        pch_ماخذ += u_ماخذ_Stride;
        pch_ہدف += u_ہدف_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساکن اندرونی خالی sdl_sve_123x_blend_مقصد_321a_copy_alpha(uint8_t *SDL_RESTRICT pch_ماخذ,
                                                         size_t u_ماخذ_Stride,
                                                         uint8_t *SDL_RESTRICT pch_ہدف,
                                                         size_t u_ہدف_Stride,
                                                         صحیح n_چوڑائی,
                                                         صحیح n_اونچائی)
{
    جب (n_اونچائی--) {

        sdl_sve_123x_stride_blend_مقصد_321a_copy_alpha((uint32_t *)pch_ماخذ,
                                                     (uint32_t *)pch_ہدف,
                                                     n_چوڑائی);

        pch_ماخذ += u_ماخذ_Stride;
        pch_ہدف += u_ہدف_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1)
ساکن اندرونی خالی sdl_sve_8888_مقصد_8888_swizzle_dispatcher(SDL_BlitInfo *info)
{
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

    أكد((srcbpp == 4) && (dstbpp == 4));

    bool fill_alpha = (!dstfmt->Amask);

    صحیح srcstride = srcskip + srcbpp * چوڑائی;
    صحیح dststride = dstskip + dstbpp * چوڑائی;

    انتخاب (srcfmt->format) {
    حالت SDL_PIXELFORMAT_XRGB8888:
        انتخاب (dstfmt->format) {
        حالت SDL_PIXELFORMAT_ARGB8888:
        حالت SDL_PIXELFORMAT_XRGB8888:
            اگر (fill_alpha) {
                sdl_sve_xccc_blend_مقصد_accc_fill_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    چوڑائی,
                    اونچائی);
            } ورنہ {
                sdl_sve_xccc_blend_مقصد_accc_copy_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    چوڑائی,
                    اونچائی);
            }
            توڑو;

        حالت SDL_PIXELFORMAT_RGBA8888:
        حالت SDL_PIXELFORMAT_RGBX8888:
            اگر (fill_alpha) {
                sdl_sve_xccc_blend_مقصد_ccca_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اونچائی);
            } ورنہ {
                sdl_sve_xccc_blend_مقصد_ccca_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اونچائی);
            }
            توڑو;

        حالت SDL_PIXELFORMAT_ABGR8888:
        حالت SDL_PIXELFORMAT_XBGR8888:
            اگر (fill_alpha) {
                sdl_sve_x123_blend_مقصد_a321_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اونچائی);
            } ورنہ {
                sdl_sve_x123_blend_مقصد_a321_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اونچائی);
            }
            توڑو;

        حالت SDL_PIXELFORMAT_BGRA8888:
        حالت SDL_PIXELFORMAT_BGRX8888:
            اگر (fill_alpha) {
                sdl_sve_x123_blend_مقصد_321a_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اونچائی);
            } ورنہ {
                sdl_sve_x123_blend_مقصد_321a_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اونچائی);
            }
            توڑو;
        طےشدہ:
            أكد(false);
            توڑو;
        }
        توڑو;

    حالت SDL_PIXELFORMAT_ARGB8888:
        انتخاب (dstfmt->format) {
        حالت SDL_PIXELFORMAT_ARGB8888:
        حالت SDL_PIXELFORMAT_XRGB8888:
            اگر (fill_alpha) {
                sdl_sve_accc_blend_مقصد_accc_fill_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    چوڑائی,
                    اونچائی);
            } ورنہ {
                sdl_sve_accc_blend_مقصد_accc_copy_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    چوڑائی,
                    اونچائی);
            }
            توڑو;

        حالت SDL_PIXELFORMAT_RGBA8888:
        حالت SDL_PIXELFORMAT_RGBX8888:
            اگر (fill_alpha) {
                sdl_sve_accc_blend_مقصد_ccca_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اونچائی);
            } ورنہ {
                sdl_sve_accc_blend_مقصد_ccca_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اونچائی);
            }
            توڑو;

        حالت SDL_PIXELFORMAT_ABGR8888:
        حالت SDL_PIXELFORMAT_XBGR8888:
            اگر (fill_alpha) {
                sdl_sve_a123_blend_مقصد_a321_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اونچائی);
            } ورنہ {
                sdl_sve_a123_blend_مقصد_a321_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اونچائی);
            }
            توڑو;

        حالت SDL_PIXELFORMAT_BGRA8888:
        حالت SDL_PIXELFORMAT_BGRX8888:
            اگر (fill_alpha) {
                sdl_sve_a123_blend_مقصد_321a_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اونچائی);
            } ورنہ {
                sdl_sve_a123_blend_مقصد_321a_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اونچائی);
            }
            توڑو;
        طےشدہ:
            أكد(false);
            توڑو;
        }
        توڑو;

    حالت SDL_PIXELFORMAT_RGBX8888:
        انتخاب (dstfmt->format) {
        حالت SDL_PIXELFORMAT_ARGB8888:
        حالت SDL_PIXELFORMAT_XRGB8888:
            اگر (fill_alpha) {
                sdl_sve_cccx_blend_مقصد_accc_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اونچائی);
            } ورنہ {
                sdl_sve_cccx_blend_مقصد_accc_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اونچائی);
            }
            توڑو;

        حالت SDL_PIXELFORMAT_RGBA8888:
        حالت SDL_PIXELFORMAT_RGBX8888:
            اگر (fill_alpha) {
                sdl_sve_cccx_blend_مقصد_ccca_fill_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    چوڑائی,
                    اونچائی);
            } ورنہ {
                sdl_sve_cccx_blend_مقصد_ccca_copy_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    چوڑائی,
                    اونچائی);
            }
            توڑو;

        حالت SDL_PIXELFORMAT_ABGR8888:
        حالت SDL_PIXELFORMAT_XBGR8888:
            اگر (fill_alpha) {
                sdl_sve_123x_blend_مقصد_a321_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اونچائی);
            } ورنہ {
                sdl_sve_123x_blend_مقصد_a321_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اونچائی);
            }
            توڑو;

        حالت SDL_PIXELFORMAT_BGRA8888:
        حالت SDL_PIXELFORMAT_BGRX8888:
            اگر (fill_alpha) {
                sdl_sve_123x_blend_مقصد_321a_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اونچائی);
            } ورنہ {
                sdl_sve_123x_blend_مقصد_321a_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اونچائی);
            }
            توڑو;
        طےشدہ:
            أكد(false);
            توڑو;
        }
        توڑو;

    حالت SDL_PIXELFORMAT_RGBA8888:
        انتخاب (dstfmt->format) {
        حالت SDL_PIXELFORMAT_ARGB8888:
        حالت SDL_PIXELFORMAT_XRGB8888:
            اگر (fill_alpha) {
                sdl_sve_ccca_blend_مقصد_accc_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اونچائی);
            } ورنہ {
                sdl_sve_ccca_blend_مقصد_accc_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اونچائی);
            }
            توڑو;

        حالت SDL_PIXELFORMAT_RGBA8888:
        حالت SDL_PIXELFORMAT_RGBX8888:
            اگر (fill_alpha) {
                sdl_sve_ccca_blend_مقصد_ccca_fill_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    چوڑائی,
                    اونچائی);
            } ورنہ {
                sdl_sve_ccca_blend_مقصد_ccca_copy_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    چوڑائی,
                    اونچائی);
            }
            توڑو;

        حالت SDL_PIXELFORMAT_ABGR8888:
        حالت SDL_PIXELFORMAT_XBGR8888:
            اگر (fill_alpha) {
                sdl_sve_123a_blend_مقصد_a321_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اونچائی);
            } ورنہ {
                sdl_sve_123a_blend_مقصد_a321_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اونچائی);
            }
            توڑو;

        حالت SDL_PIXELFORMAT_BGRA8888:
        حالت SDL_PIXELFORMAT_BGRX8888:
            اگر (fill_alpha) {
                sdl_sve_123a_blend_مقصد_321a_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اونچائی);
            } ورنہ {
                sdl_sve_123a_blend_مقصد_321a_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اونچائی);
            }
            توڑو;
        طےشدہ:
            أكد(false);
            توڑو;
        }
        توڑو;

    حالت SDL_PIXELFORMAT_XBGR8888:
        انتخاب (dstfmt->format) {
        حالت SDL_PIXELFORMAT_ARGB8888:
        حالت SDL_PIXELFORMAT_XRGB8888:
            اگر (fill_alpha) {
                sdl_sve_x123_blend_مقصد_a321_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اونچائی);
            } ورنہ {
                sdl_sve_x123_blend_مقصد_a321_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اونچائی);
            }
            توڑو;

        حالت SDL_PIXELFORMAT_RGBA8888:
        حالت SDL_PIXELFORMAT_RGBX8888:
            اگر (fill_alpha) {
                sdl_sve_x123_blend_مقصد_321a_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اونچائی);
            } ورنہ {
                sdl_sve_x123_blend_مقصد_321a_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اونچائی);
            }
            توڑو;

        حالت SDL_PIXELFORMAT_ABGR8888:
        حالت SDL_PIXELFORMAT_XBGR8888:
            اگر (fill_alpha) {
                sdl_sve_xccc_blend_مقصد_accc_fill_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    چوڑائی,
                    اونچائی);
            } ورنہ {
                sdl_sve_xccc_blend_مقصد_accc_copy_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    چوڑائی,
                    اونچائی);
            }
            توڑو;

        حالت SDL_PIXELFORMAT_BGRA8888:
        حالت SDL_PIXELFORMAT_BGRX8888:
            اگر (fill_alpha) {
                sdl_sve_xccc_blend_مقصد_ccca_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اونچائی);
            } ورنہ {
                sdl_sve_xccc_blend_مقصد_ccca_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اونچائی);
            }
            توڑو;
        طےشدہ:
            أكد(false);
            توڑو;
        }
        توڑو;

    حالت SDL_PIXELFORMAT_ABGR8888:
        انتخاب (dstfmt->format) {
        حالت SDL_PIXELFORMAT_ARGB8888:
        حالت SDL_PIXELFORMAT_XRGB8888:
            اگر (fill_alpha) {
                sdl_sve_a123_blend_مقصد_a321_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اونچائی);
            } ورنہ {
                sdl_sve_a123_blend_مقصد_a321_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اونچائی);
            }
            توڑو;

        حالت SDL_PIXELFORMAT_RGBA8888:
        حالت SDL_PIXELFORMAT_RGBX8888:
            اگر (fill_alpha) {
                sdl_sve_a123_blend_مقصد_321a_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اونچائی);
            } ورنہ {
                sdl_sve_a123_blend_مقصد_321a_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اونچائی);
            }
            توڑو;

        حالت SDL_PIXELFORMAT_ABGR8888:
        حالت SDL_PIXELFORMAT_XBGR8888:
            اگر (fill_alpha) {
                sdl_sve_accc_blend_مقصد_accc_fill_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    چوڑائی,
                    اونچائی);
            } ورنہ {
                sdl_sve_accc_blend_مقصد_accc_copy_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    چوڑائی,
                    اونچائی);
            }
            توڑو;

        حالت SDL_PIXELFORMAT_BGRA8888:
        حالت SDL_PIXELFORMAT_BGRX8888:
            اگر (fill_alpha) {
                sdl_sve_accc_blend_مقصد_ccca_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اونچائی);
            } ورنہ {
                sdl_sve_accc_blend_مقصد_ccca_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اونچائی);
            }
            توڑو;
        طےشدہ:
            أكد(false);
            توڑو;
        }
        توڑو;

    حالت SDL_PIXELFORMAT_BGRX8888:
        انتخاب (dstfmt->format) {
        حالت SDL_PIXELFORMAT_ARGB8888:
        حالت SDL_PIXELFORMAT_XRGB8888:
            اگر (fill_alpha) {
                sdl_sve_123x_blend_مقصد_a321_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اونچائی);
            } ورنہ {
                sdl_sve_123x_blend_مقصد_a321_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اونچائی);
            }
            توڑو;

        حالت SDL_PIXELFORMAT_RGBA8888:
        حالت SDL_PIXELFORMAT_RGBX8888:
            اگر (fill_alpha) {
                sdl_sve_123x_blend_مقصد_321a_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اونچائی);
            } ورنہ {
                sdl_sve_123x_blend_مقصد_321a_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اونچائی);
            }
            توڑو;

        حالت SDL_PIXELFORMAT_ABGR8888:
        حالت SDL_PIXELFORMAT_XBGR8888:
            اگر (fill_alpha) {
                sdl_sve_cccx_blend_مقصد_accc_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اونچائی);
            } ورنہ {
                sdl_sve_cccx_blend_مقصد_accc_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اونچائی);
            }
            توڑو;

        حالت SDL_PIXELFORMAT_BGRA8888:
        حالت SDL_PIXELFORMAT_BGRX8888:
            اگر (fill_alpha) {
                sdl_sve_cccx_blend_مقصد_ccca_fill_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    چوڑائی,
                    اونچائی);
            } ورنہ {
                sdl_sve_cccx_blend_مقصد_ccca_copy_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    چوڑائی,
                    اونچائی);
            }
            توڑو;
        طےشدہ:
            أكد(false);
            توڑو;
        }
        توڑو;

    حالت SDL_PIXELFORMAT_BGRA8888:
        انتخاب (dstfmt->format) {
        حالت SDL_PIXELFORMAT_ARGB8888:
        حالت SDL_PIXELFORMAT_XRGB8888:
            اگر (fill_alpha) {
                sdl_sve_123a_blend_مقصد_a321_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اونچائی);
            } ورنہ {
                sdl_sve_123a_blend_مقصد_a321_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اونچائی);
            }
            توڑو;

        حالت SDL_PIXELFORMAT_RGBA8888:
        حالت SDL_PIXELFORMAT_RGBX8888:
            اگر (fill_alpha) {
                sdl_sve_123a_blend_مقصد_321a_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اونچائی);
            } ورنہ {
                sdl_sve_123a_blend_مقصد_321a_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اونچائی);
            }
            توڑو;

        حالت SDL_PIXELFORMAT_ABGR8888:
        حالت SDL_PIXELFORMAT_XBGR8888:
            اگر (fill_alpha) {
                sdl_sve_ccca_blend_مقصد_accc_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اونچائی);
            } ورنہ {
                sdl_sve_ccca_blend_مقصد_accc_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اونچائی);
            }
            توڑو;

        حالت SDL_PIXELFORMAT_BGRA8888:
        حالت SDL_PIXELFORMAT_BGRX8888:
            اگر (fill_alpha) {
                sdl_sve_ccca_blend_مقصد_ccca_fill_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    چوڑائی,
                    اونچائی);
            } ورنہ {
                sdl_sve_ccca_blend_مقصد_ccca_copy_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    چوڑائی,
                    اونچائی);
            }
            توڑو;
        طےشدہ:
            أكد(false);
            توڑو;
        }
        توڑو;

    طےشدہ:
        أكد(false);
        توڑو;
    }
}

#اگر_غیر_تعریف_شدہ sdl_sve_rgb32_blend_مقصد_rgb565_op
#تعریف_کرو sdl_sve_rgb32_blend_مقصد_rgb565_op(ma_alpha_chn_idx)
#اگر_ختم

/*
 * ACCC or CCCA
 */
SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساکن اندرونی خالی sdl_sve_argb8888_stride_blend_مقصد_rgb565(uint32_t *SDL_RESTRICT pw_ماخذ,
                                                           uint16_t *SDL_RESTRICT phw_ہدف,
                                                           size_t uStride)
{
    sdl_sve_rgb32_مقصد_rgb565_stride_impl(
        sdl_sve_pixel_u16x4_foreach_chn_argb_rgb565,
        {
            sdl_sve_rgb32_blend_مقصد_rgb565_op(3);
        });
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساکن اندرونی خالی sdl_sve_argb8888_blend_مقصد_rgb565(uint8_t *SDL_RESTRICT pch_ماخذ,
                                                    size_t u_ماخذ_Stride,
                                                    uint8_t *SDL_RESTRICT pch_ہدف,
                                                    size_t u_ہدف_Stride,
                                                    صحیح n_چوڑائی,
                                                    صحیح n_اونچائی)
{
    جب (n_اونچائی--) {

        sdl_sve_argb8888_stride_blend_مقصد_rgb565((uint32_t *)pch_ماخذ,
                                                (uint16_t *)pch_ہدف,
                                                n_چوڑائی);

        pch_ماخذ += u_ماخذ_Stride;
        pch_ہدف += u_ہدف_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساکن اندرونی خالی sdl_sve_rgba8888_stride_blend_مقصد_rgb565(uint32_t *SDL_RESTRICT pw_ماخذ,
                                                           uint16_t *SDL_RESTRICT phw_ہدف,
                                                           size_t uStride)
{
    sdl_sve_rgb32_مقصد_rgb565_stride_impl(
        sdl_sve_pixel_u16x4_foreach_chn_rgba_rgb565,
        {
            sdl_sve_rgb32_blend_مقصد_rgb565_op(0);
        });
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساکن اندرونی خالی sdl_sve_rgba8888_blend_مقصد_rgb565(uint8_t *SDL_RESTRICT pch_ماخذ,
                                                    size_t u_ماخذ_Stride,
                                                    uint8_t *SDL_RESTRICT pch_ہدف,
                                                    size_t u_ہدف_Stride,
                                                    صحیح n_چوڑائی,
                                                    صحیح n_اونچائی)
{
    جب (n_اونچائی--) {

        sdl_sve_rgba8888_stride_blend_مقصد_rgb565((uint32_t *)pch_ماخذ,
                                                (uint16_t *)pch_ہدف,
                                                n_چوڑائی);

        pch_ماخذ += u_ماخذ_Stride;
        pch_ہدف += u_ہدف_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساکن اندرونی خالی sdl_sve_bgra8888_stride_blend_مقصد_rgb565(uint32_t *SDL_RESTRICT pw_ماخذ,
                                                           uint16_t *SDL_RESTRICT phw_ہدف,
                                                           size_t uStride)
{
    sdl_sve_rgb32_مقصد_rgb565_stride_impl(
        sdl_sve_pixel_u16x4_foreach_chn_bgra_rgb565,
        {
            sdl_sve_rgb32_blend_مقصد_rgb565_op(0);
        });
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساکن اندرونی خالی sdl_sve_bgra8888_blend_مقصد_rgb565(uint8_t *SDL_RESTRICT pch_ماخذ,
                                                    size_t u_ماخذ_Stride,
                                                    uint8_t *SDL_RESTRICT pch_ہدف,
                                                    size_t u_ہدف_Stride,
                                                    صحیح n_چوڑائی,
                                                    صحیح n_اونچائی)
{
    جب (n_اونچائی--) {

        sdl_sve_bgra8888_stride_blend_مقصد_rgb565((uint32_t *)pch_ماخذ,
                                                (uint16_t *)pch_ہدف,
                                                n_چوڑائی);

        pch_ماخذ += u_ماخذ_Stride;
        pch_ہدف += u_ہدف_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساکن اندرونی خالی sdl_sve_abgr8888_stride_blend_مقصد_rgb565(uint32_t *SDL_RESTRICT pw_ماخذ,
                                                           uint16_t *SDL_RESTRICT phw_ہدف,
                                                           size_t uStride)
{
    sdl_sve_rgb32_مقصد_rgb565_stride_impl(
        sdl_sve_pixel_u16x4_foreach_chn_abgr_rgb565,
        {
            sdl_sve_rgb32_blend_مقصد_rgb565_op(3);
        });
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساکن اندرونی خالی sdl_sve_abgr8888_blend_مقصد_rgb565(uint8_t *SDL_RESTRICT pch_ماخذ,
                                                    size_t u_ماخذ_Stride,
                                                    uint8_t *SDL_RESTRICT pch_ہدف,
                                                    size_t u_ہدف_Stride,
                                                    صحیح n_چوڑائی,
                                                    صحیح n_اونچائی)
{
    جب (n_اونچائی--) {

        sdl_sve_abgr8888_stride_blend_مقصد_rgb565((uint32_t *)pch_ماخذ,
                                                (uint16_t *)pch_ہدف,
                                                n_چوڑائی);

        pch_ماخذ += u_ماخذ_Stride;
        pch_ہدف += u_ہدف_Stride;
    }
}

/*
 * XCCC or CCCX
 */
SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساکن اندرونی خالی sdl_sve_xrgb8888_stride_blend_مقصد_rgb565(uint32_t *SDL_RESTRICT pw_ماخذ,
                                                           uint16_t *SDL_RESTRICT phw_ہدف,
                                                           size_t uStride)
{
    sdl_sve_rgb32_no_alpha_مقصد_rgb565_stride_impl(
        3,
        sdl_sve_pixel_u16x4_foreach_chn_argb_rgb565,
        {
            sdl_sve_rgb32_blend_مقصد_rgb565_op(3);
        });
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساکن اندرونی خالی sdl_sve_xrgb8888_blend_مقصد_rgb565(uint8_t *SDL_RESTRICT pch_ماخذ,
                                                    size_t u_ماخذ_Stride,
                                                    uint8_t *SDL_RESTRICT pch_ہدف,
                                                    size_t u_ہدف_Stride,
                                                    صحیح n_چوڑائی,
                                                    صحیح n_اونچائی)
{
    جب (n_اونچائی--) {

        sdl_sve_xrgb8888_stride_blend_مقصد_rgb565((uint32_t *)pch_ماخذ,
                                                (uint16_t *)pch_ہدف,
                                                n_چوڑائی);

        pch_ماخذ += u_ماخذ_Stride;
        pch_ہدف += u_ہدف_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساکن اندرونی خالی sdl_sve_rgbx8888_stride_blend_مقصد_rgb565(uint32_t *SDL_RESTRICT pw_ماخذ,
                                                           uint16_t *SDL_RESTRICT phw_ہدف,
                                                           size_t uStride)
{
    sdl_sve_rgb32_no_alpha_مقصد_rgb565_stride_impl(
        0,
        sdl_sve_pixel_u16x4_foreach_chn_rgba_rgb565,
        {
            sdl_sve_rgb32_blend_مقصد_rgb565_op(0);
        });
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساکن اندرونی خالی sdl_sve_rgbx8888_blend_مقصد_rgb565(uint8_t *SDL_RESTRICT pch_ماخذ,
                                                    size_t u_ماخذ_Stride,
                                                    uint8_t *SDL_RESTRICT pch_ہدف,
                                                    size_t u_ہدف_Stride,
                                                    صحیح n_چوڑائی,
                                                    صحیح n_اونچائی)
{
    جب (n_اونچائی--) {

        sdl_sve_rgbx8888_stride_blend_مقصد_rgb565((uint32_t *)pch_ماخذ,
                                                (uint16_t *)pch_ہدف,
                                                n_چوڑائی);

        pch_ماخذ += u_ماخذ_Stride;
        pch_ہدف += u_ہدف_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساکن اندرونی خالی sdl_sve_bgrx8888_stride_blend_مقصد_rgb565(uint32_t *SDL_RESTRICT pw_ماخذ,
                                                           uint16_t *SDL_RESTRICT phw_ہدف,
                                                           size_t uStride)
{
    sdl_sve_rgb32_no_alpha_مقصد_rgb565_stride_impl(
        0,
        sdl_sve_pixel_u16x4_foreach_chn_bgra_rgb565,
        {
            sdl_sve_rgb32_blend_مقصد_rgb565_op(0);
        });
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساکن اندرونی خالی sdl_sve_bgrx8888_blend_مقصد_rgb565(uint8_t *SDL_RESTRICT pch_ماخذ,
                                                    size_t u_ماخذ_Stride,
                                                    uint8_t *SDL_RESTRICT pch_ہدف,
                                                    size_t u_ہدف_Stride,
                                                    صحیح n_چوڑائی,
                                                    صحیح n_اونچائی)
{
    جب (n_اونچائی--) {

        sdl_sve_bgrx8888_stride_blend_مقصد_rgb565((uint32_t *)pch_ماخذ,
                                                (uint16_t *)pch_ہدف,
                                                n_چوڑائی);

        pch_ماخذ += u_ماخذ_Stride;
        pch_ہدف += u_ہدف_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساکن اندرونی خالی sdl_sve_xbgr8888_stride_blend_مقصد_rgb565(uint32_t *SDL_RESTRICT pw_ماخذ,
                                                           uint16_t *SDL_RESTRICT phw_ہدف,
                                                           size_t uStride)
{
    sdl_sve_rgb32_no_alpha_مقصد_rgb565_stride_impl(
        3,
        sdl_sve_pixel_u16x4_foreach_chn_abgr_rgb565,
        {
            sdl_sve_rgb32_blend_مقصد_rgb565_op(3);
        });
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساکن اندرونی خالی sdl_sve_xbgr8888_blend_مقصد_rgb565(uint8_t *SDL_RESTRICT pch_ماخذ,
                                                    size_t u_ماخذ_Stride,
                                                    uint8_t *SDL_RESTRICT pch_ہدف,
                                                    size_t u_ہدف_Stride,
                                                    صحیح n_چوڑائی,
                                                    صحیح n_اونچائی)
{
    جب (n_اونچائی--) {

        sdl_sve_xbgr8888_stride_blend_مقصد_rgb565((uint32_t *)pch_ماخذ,
                                                (uint16_t *)pch_ہدف,
                                                n_چوڑائی);

        pch_ماخذ += u_ماخذ_Stride;
        pch_ہدف += u_ہدف_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1)
ساکن اندرونی خالی sdl_sve_rgb32_مقصد_rgb565_swizzle_dispatcher(SDL_BlitInfo *info)
{
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

    أكد(srcbpp == 4);
    أكد(dstbpp == 2);

    صحیح srcstride = srcskip + srcbpp * چوڑائی;
    صحیح dststride = dstskip + dstbpp * چوڑائی;

    انتخاب (srcfmt->format) {
    حالت SDL_PIXELFORMAT_XRGB8888:
        sdl_sve_xrgb8888_blend_مقصد_rgb565(src,
                                         srcstride,
                                         dst,
                                         dststride,
                                         چوڑائی,
                                         اونچائی);
        توڑو;

    حالت SDL_PIXELFORMAT_ARGB8888:
        sdl_sve_argb8888_blend_مقصد_rgb565(src,
                                         srcstride,
                                         dst,
                                         dststride,
                                         چوڑائی,
                                         اونچائی);
        توڑو;

    حالت SDL_PIXELFORMAT_RGBX8888:
        sdl_sve_rgbx8888_blend_مقصد_rgb565(src,
                                         srcstride,
                                         dst,
                                         dststride,
                                         چوڑائی,
                                         اونچائی);
        توڑو;

    حالت SDL_PIXELFORMAT_RGBA8888:
        sdl_sve_rgba8888_blend_مقصد_rgb565(src,
                                         srcstride,
                                         dst,
                                         dststride,
                                         چوڑائی,
                                         اونچائی);
        توڑو;

    حالت SDL_PIXELFORMAT_XBGR8888:
        sdl_sve_xbgr8888_blend_مقصد_rgb565(src,
                                         srcstride,
                                         dst,
                                         dststride,
                                         چوڑائی,
                                         اونچائی);
        توڑو;

    حالت SDL_PIXELFORMAT_ABGR8888:
        sdl_sve_abgr8888_blend_مقصد_rgb565(src,
                                         srcstride,
                                         dst,
                                         dststride,
                                         چوڑائی,
                                         اونچائی);
        توڑو;

    حالت SDL_PIXELFORMAT_BGRX8888:
        sdl_sve_bgrx8888_blend_مقصد_rgb565(src,
                                         srcstride,
                                         dst,
                                         dststride,
                                         چوڑائی,
                                         اونچائی);
        توڑو;

    حالت SDL_PIXELFORMAT_BGRA8888:
        sdl_sve_bgra8888_blend_مقصد_rgb565(src,
                                         srcstride,
                                         dst,
                                         dststride,
                                         چوڑائی,
                                         اونچائی);
        توڑو;

    طےشدہ:
        أكد(false);
        توڑو;
    }
}

#اگر_ختم /* SD_SVE2_SWIZZLE_H */