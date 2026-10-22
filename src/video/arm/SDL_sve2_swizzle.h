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

#إذا !defined(SD_SVE2_SWIZZLE_H) //&& (defined(__ARM_FEATURE_SVE2) && __ARM_FEATURE_SVE2)
#تعریف_کرو SD_SVE2_SWIZZLE_H

#ضمن "SDL_sve2_extension.h"

#تعریف_کرو sdl_sve_rgb32_stride_impl(ma_sve_chn_iterator, ...)   \
    sdl_sve_stride_loop_pixel(uStride, v_پوچھ_Pred)             \
    {                                                         \
                                                              \
        svuint16x4_t v_سروت_Low16x4 = svundef4_u16();         \
        svuint16x4_t v_سروت_High16x4 = svundef4_u16();        \
                                                              \
        svuint16x4_t v_نشانہ_Low16x4 = svundef4_u16();         \
        svuint16x4_t v_نشانہ_High16x4 = svundef4_u16();        \
                                                              \
        svld4ub_u16(v_پوچھ_Pred,                                \
                    (uint8_t *)pw_سروت,                      \
                    &v_سروت_Low16x4,                          \
                    &v_سروت_High16x4);                        \
                                                              \
        svld4ub_u16(v_پوچھ_Pred,                                \
                    (uint8_t *)pw_نشانہ,                      \
                    &v_نشانہ_Low16x4,                          \
                    &v_نشانہ_High16x4);                        \
                                                              \
        /* process low half */                                \
        ma_sve_chn_iterator(v_سروت_Low16x4, v_نشانہ_Low16x4,   \
                            __VA_ARGS__);                     \
                                                              \
        /* process high half */                               \
        ma_sve_chn_iterator(v_سروت_High16x4, v_نشانہ_High16x4, \
                            __VA_ARGS__);                     \
                                                              \
        svst4ub_u16(v_پوچھ_Pred,                                \
                    (uint8_t *)pw_نشانہ,                      \
                    v_نشانہ_Low16x4,                           \
                    v_نشانہ_High16x4);                         \
                                                              \
        pw_سروت += sve_iteration_advance;                    \
        pw_نشانہ += sve_iteration_advance;                    \
    }

#تعریف_کرو sdl_sve_rgb32_no_alpha_stride_impl(                   \
    ma_alpha_idx,                                             \
    ma_sve_chn_iterator,                                      \
    ...)                                                      \
    sdl_sve_stride_loop_pixel(uStride, v_پوچھ_Pred)             \
    {                                                         \
                                                              \
        svuint16x4_t v_سروت_Low16x4 = svundef4_u16();         \
        svuint16x4_t v_سروت_High16x4 = svundef4_u16();        \
                                                              \
        svuint16x4_t v_نشانہ_Low16x4 = svundef4_u16();         \
        svuint16x4_t v_نشانہ_High16x4 = svundef4_u16();        \
                                                              \
        svld4ub_u16(v_پوچھ_Pred,                                \
                    (uint8_t *)pw_سروت,                      \
                    &v_سروت_Low16x4,                          \
                    &v_سروت_High16x4);                        \
                                                              \
        svld4ub_u16(v_پوچھ_Pred,                                \
                    (uint8_t *)pw_نشانہ,                      \
                    &v_نشانہ_Low16x4,                          \
                    &v_نشانہ_High16x4);                        \
                                                              \
        v_سروت_Low16x4 = svset4(v_سروت_Low16x4,               \
                                (ma_alpha_idx),               \
                                svdup_u16(0xFF));             \
        v_سروت_High16x4 = svset4(v_سروت_High16x4,             \
                                 (ma_alpha_idx),              \
                                 svdup_u16(0xFF));            \
                                                              \
        /* process low half */                                \
        ma_sve_chn_iterator(v_سروت_Low16x4, v_نشانہ_Low16x4,   \
                            __VA_ARGS__);                     \
                                                              \
        /* process high half */                               \
        ma_sve_chn_iterator(v_سروت_High16x4, v_نشانہ_High16x4, \
                            __VA_ARGS__);                     \
                                                              \
        svst4ub_u16(v_پوچھ_Pred,                                \
                    (uint8_t *)pw_نشانہ,                      \
                    v_نشانہ_Low16x4,                           \
                    v_نشانہ_High16x4);                         \
                                                              \
        pw_سروت += sve_iteration_advance;                    \
        pw_نشانہ += sve_iteration_advance;                    \
    }

#تعریف_کرو sdl_sve_rgb32_منزل_rgb565_stride_impl(ma_sve_chn_iterator, ...) \
    sdl_sve_stride_loop_pixel(uStride, v_پوچھ_Pred)                     \
    {                                                                 \
                                                                      \
        svuint16x4_t v_سروت_Low16x4 = svundef4_u16();                 \
        svuint16x4_t v_سروت_High16x4 = svundef4_u16();                \
                                                                      \
        svuint16x3_t v_نشانہ_Low16x3 = svundef3_u16();                 \
        svuint16x3_t v_نشانہ_High16x3 = svundef3_u16();                \
                                                                      \
        svld4ub_u16(v_پوچھ_Pred,                                        \
                    (uint8_t *)pw_سروت,                              \
                    &v_سروت_Low16x4,                                  \
                    &v_سروت_High16x4);                                \
                                                                      \
        svld3rgb565_u16(v_پوچھ_Pred,                                    \
                        phw_نشانہ,                                    \
                        &v_نشانہ_Low16x3,                              \
                        &v_نشانہ_High16x3);                            \
                                                                      \
        ma_sve_chn_iterator(v_سروت_Low16x4, v_نشانہ_Low16x3,           \
                            __VA_ARGS__);                             \
                                                                      \
        ma_sve_chn_iterator(v_سروت_High16x4, v_نشانہ_High16x3,         \
                            __VA_ARGS__);                             \
                                                                      \
        svst3rgb565_u16(v_پوچھ_Pred,                                    \
                        phw_نشانہ,                                    \
                        v_نشانہ_Low16x3,                               \
                        v_نشانہ_High16x3);                             \
                                                                      \
        pw_سروت += sve_iteration_advance;                            \
        phw_نشانہ += sve_iteration_advance;                           \
    }

#تعریف_کرو sdl_sve_rgb32_no_alpha_منزل_rgb565_stride_impl(         \
    ma_alpha_idx,                                             \
    ma_sve_chn_iterator,                                      \
    ...)                                                      \
    sdl_sve_stride_loop_pixel(uStride, v_پوچھ_Pred)             \
    {                                                         \
                                                              \
        svuint16x4_t v_سروت_Low16x4 = svundef4_u16();         \
        svuint16x4_t v_سروت_High16x4 = svundef4_u16();        \
                                                              \
        svuint16x3_t v_نشانہ_Low16x3 = svundef3_u16();         \
        svuint16x3_t v_نشانہ_High16x3 = svundef3_u16();        \
                                                              \
        svld4ub_u16(v_پوچھ_Pred,                                \
                    (uint8_t *)pw_سروت,                      \
                    &v_سروت_Low16x4,                          \
                    &v_سروت_High16x4);                        \
                                                              \
        v_سروت_Low16x4 = svset4(v_سروت_Low16x4,               \
                                (ma_alpha_idx),               \
                                svdup_u16(0xFF));             \
        v_سروت_High16x4 = svset4(v_سروت_High16x4,             \
                                 (ma_alpha_idx),              \
                                 svdup_u16(0xFF));            \
                                                              \
        svld3rgb565_u16(v_پوچھ_Pred,                            \
                        phw_نشانہ,                            \
                        &v_نشانہ_Low16x3,                      \
                        &v_نشانہ_High16x3);                    \
                                                              \
        ma_sve_chn_iterator(v_سروت_Low16x4, v_نشانہ_Low16x3,   \
                            __VA_ARGS__);                     \
                                                              \
        ma_sve_chn_iterator(v_سروت_High16x4, v_نشانہ_High16x3, \
                            __VA_ARGS__);                     \
                                                              \
        svst3rgb565_u16(v_پوچھ_Pred,                            \
                        phw_نشانہ,                            \
                        v_نشانہ_Low16x3,                       \
                        v_نشانہ_High16x3);                     \
                                                              \
        pw_سروت += sve_iteration_advance;                    \
        phw_نشانہ += sve_iteration_advance;                   \
    }

#جے_بنا_تعریف sdl_sve_rgb32_blend_op_fill_alpha
#تعریف_کرو sdl_sve_rgb32_blend_op_fill_alpha(ma_alpha_chn_idx)
#جے_انت

#جے_بنا_تعریف sdl_sve_rgb32_blend_op_copy_alpha
#تعریف_کرو sdl_sve_rgb32_blend_op_copy_alpha(ma_alpha_chn_idx)
#جے_انت

/*
 * Source: ACCC and CCCA
 */
SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_accc_stride_blend_منزل_accc_fill_alpha(
    uint32_t *SDL_RESTRICT pw_سروت,
    uint32_t *SDL_RESTRICT pw_نشانہ,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn,

                              sdl_sve_rgb32_blend_op_fill_alpha(3);

    );
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_accc_stride_blend_منزل_accc_copy_alpha(
    uint32_t *SDL_RESTRICT pw_سروت,
    uint32_t *SDL_RESTRICT pw_نشانہ,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn,
                              sdl_sve_rgb32_blend_op_copy_alpha(3););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_ccca_stride_blend_منزل_ccca_fill_alpha(
    uint32_t *SDL_RESTRICT pw_سروت,
    uint32_t *SDL_RESTRICT pw_نشانہ,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn,
                              sdl_sve_rgb32_blend_op_fill_alpha(0););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_ccca_stride_blend_منزل_ccca_copy_alpha(
    uint32_t *SDL_RESTRICT pw_سروت,
    uint32_t *SDL_RESTRICT pw_نشانہ,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn,

                              sdl_sve_rgb32_blend_op_copy_alpha(0);

    );
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_accc_blend_منزل_accc_fill_alpha(
    uint8_t *SDL_RESTRICT pch_سروت,
    size_t u_سروت_Stride,
    uint8_t *SDL_RESTRICT pch_نشانہ,
    size_t u_نشانہ_Stride,
    صحيح n_چوڑائی,
    صحيح n_اچائی)
{
    طالما (n_اچائی--) {

        sdl_sve_accc_stride_blend_منزل_accc_fill_alpha(
            (uint32_t *)pch_سروت,
            (uint32_t *)pch_نشانہ,
            n_چوڑائی);

        pch_سروت += u_سروت_Stride;
        pch_نشانہ += u_نشانہ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_accc_blend_منزل_accc_copy_alpha(
    uint8_t *SDL_RESTRICT pch_سروت,
    size_t u_سروت_Stride,
    uint8_t *SDL_RESTRICT pch_نشانہ,
    size_t u_نشانہ_Stride,
    صحيح n_چوڑائی,
    صحيح n_اچائی)
{
    طالما (n_اچائی--) {

        sdl_sve_accc_stride_blend_منزل_accc_copy_alpha(
            (uint32_t *)pch_سروت,
            (uint32_t *)pch_نشانہ,
            n_چوڑائی);

        pch_سروت += u_سروت_Stride;
        pch_نشانہ += u_نشانہ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_ccca_blend_منزل_ccca_fill_alpha(
    uint8_t *SDL_RESTRICT pch_سروت,
    size_t u_سروت_Stride,
    uint8_t *SDL_RESTRICT pch_نشانہ,
    size_t u_نشانہ_Stride,
    صحيح n_چوڑائی,
    صحيح n_اچائی)
{
    طالما (n_اچائی--) {

        sdl_sve_ccca_stride_blend_منزل_ccca_fill_alpha(
            (uint32_t *)pch_سروت,
            (uint32_t *)pch_نشانہ,
            n_چوڑائی);

        pch_سروت += u_سروت_Stride;
        pch_نشانہ += u_نشانہ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_ccca_blend_منزل_ccca_copy_alpha(
    uint8_t *SDL_RESTRICT pch_سروت,
    size_t u_سروت_Stride,
    uint8_t *SDL_RESTRICT pch_نشانہ,
    size_t u_نشانہ_Stride,
    صحيح n_چوڑائی,
    صحيح n_اچائی)
{
    طالما (n_اچائی--) {

        sdl_sve_ccca_stride_blend_منزل_ccca_copy_alpha(
            (uint32_t *)pch_سروت,
            (uint32_t *)pch_نشانہ,
            n_چوڑائی);

        pch_سروت += u_سروت_Stride;
        pch_نشانہ += u_نشانہ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_a123_stride_blend_منزل_321a_fill_alpha(
    uint32_t *SDL_RESTRICT pw_سروت,
    uint32_t *SDL_RESTRICT pw_نشانہ,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn_src_dst_rev,
                              sdl_sve_rgb32_blend_op_fill_alpha(3);

    );
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_a123_stride_blend_منزل_321a_copy_alpha(
    uint32_t *SDL_RESTRICT pw_سروت,
    uint32_t *SDL_RESTRICT pw_نشانہ,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn_src_dst_rev,
                              sdl_sve_rgb32_blend_op_copy_alpha(3);

    );
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_a123_blend_منزل_321a_fill_alpha(uint8_t *SDL_RESTRICT pch_سروت,
                                                         size_t u_سروت_Stride,
                                                         uint8_t *SDL_RESTRICT pch_نشانہ,
                                                         size_t u_نشانہ_Stride,
                                                         صحيح n_چوڑائی,
                                                         صحيح n_اچائی)
{
    طالما (n_اچائی--) {

        sdl_sve_a123_stride_blend_منزل_321a_fill_alpha((uint32_t *)pch_سروت,
                                                     (uint32_t *)pch_نشانہ,
                                                     n_چوڑائی);

        pch_سروت += u_سروت_Stride;
        pch_نشانہ += u_نشانہ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_a123_blend_منزل_321a_copy_alpha(uint8_t *SDL_RESTRICT pch_سروت,
                                                         size_t u_سروت_Stride,
                                                         uint8_t *SDL_RESTRICT pch_نشانہ,
                                                         size_t u_نشانہ_Stride,
                                                         صحيح n_چوڑائی,
                                                         صحيح n_اچائی)
{
    طالما (n_اچائی--) {

        sdl_sve_a123_stride_blend_منزل_321a_copy_alpha((uint32_t *)pch_سروت,
                                                     (uint32_t *)pch_نشانہ,
                                                     n_چوڑائی);

        pch_سروت += u_سروت_Stride;
        pch_نشانہ += u_نشانہ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_123a_stride_blend_منزل_a321_fill_alpha(
    uint32_t *SDL_RESTRICT pw_سروت,
    uint32_t *SDL_RESTRICT pw_نشانہ,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn_src_dst_rev,
                              sdl_sve_rgb32_blend_op_fill_alpha(0);

    );
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_123a_stride_blend_منزل_a321_copy_alpha(
    uint32_t *SDL_RESTRICT pw_سروت,
    uint32_t *SDL_RESTRICT pw_نشانہ,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn_src_dst_rev,
                              sdl_sve_rgb32_blend_op_copy_alpha(0);

    );
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_123a_blend_منزل_a321_fill_alpha(uint8_t *SDL_RESTRICT pch_سروت,
                                                         size_t u_سروت_Stride,
                                                         uint8_t *SDL_RESTRICT pch_نشانہ,
                                                         size_t u_نشانہ_Stride,
                                                         صحيح n_چوڑائی,
                                                         صحيح n_اچائی)
{
    طالما (n_اچائی--) {

        sdl_sve_123a_stride_blend_منزل_a321_fill_alpha((uint32_t *)pch_سروت,
                                                     (uint32_t *)pch_نشانہ,
                                                     n_چوڑائی);

        pch_سروت += u_سروت_Stride;
        pch_نشانہ += u_نشانہ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_123a_blend_منزل_a321_copy_alpha(uint8_t *SDL_RESTRICT pch_سروت,
                                                         size_t u_سروت_Stride,
                                                         uint8_t *SDL_RESTRICT pch_نشانہ,
                                                         size_t u_نشانہ_Stride,
                                                         صحيح n_چوڑائی,
                                                         صحيح n_اچائی)
{
    طالما (n_اچائی--) {

        sdl_sve_123a_stride_blend_منزل_a321_copy_alpha((uint32_t *)pch_سروت,
                                                     (uint32_t *)pch_نشانہ,
                                                     n_چوڑائی);

        pch_سروت += u_سروت_Stride;
        pch_نشانہ += u_نشانہ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_accc_stride_blend_منزل_ccca_fill_alpha(
    uint32_t *SDL_RESTRICT pw_سروت,
    uint32_t *SDL_RESTRICT pw_نشانہ,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn_accc_ccca,
                              sdl_sve_rgb32_blend_op_fill_alpha(3);

    );
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_accc_stride_blend_منزل_ccca_copy_alpha(
    uint32_t *SDL_RESTRICT pw_سروت,
    uint32_t *SDL_RESTRICT pw_نشانہ,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn_accc_ccca,
                              sdl_sve_rgb32_blend_op_copy_alpha(3);

    );
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_accc_blend_منزل_ccca_fill_alpha(uint8_t *SDL_RESTRICT pch_سروت,
                                                         size_t u_سروت_Stride,
                                                         uint8_t *SDL_RESTRICT pch_نشانہ,
                                                         size_t u_نشانہ_Stride,
                                                         صحيح n_چوڑائی,
                                                         صحيح n_اچائی)
{
    طالما (n_اچائی--) {

        sdl_sve_accc_stride_blend_منزل_ccca_fill_alpha((uint32_t *)pch_سروت,
                                                     (uint32_t *)pch_نشانہ,
                                                     n_چوڑائی);

        pch_سروت += u_سروت_Stride;
        pch_نشانہ += u_نشانہ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_accc_blend_منزل_ccca_copy_alpha(uint8_t *SDL_RESTRICT pch_سروت,
                                                         size_t u_سروت_Stride,
                                                         uint8_t *SDL_RESTRICT pch_نشانہ,
                                                         size_t u_نشانہ_Stride,
                                                         صحيح n_چوڑائی,
                                                         صحيح n_اچائی)
{
    طالما (n_اچائی--) {

        sdl_sve_accc_stride_blend_منزل_ccca_copy_alpha((uint32_t *)pch_سروت,
                                                     (uint32_t *)pch_نشانہ,
                                                     n_چوڑائی);

        pch_سروت += u_سروت_Stride;
        pch_نشانہ += u_نشانہ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_ccca_stride_blend_منزل_accc_fill_alpha(
    uint32_t *SDL_RESTRICT pw_سروت,
    uint32_t *SDL_RESTRICT pw_نشانہ,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn_ccca_accc,
                              sdl_sve_rgb32_blend_op_fill_alpha(0);

    );
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_ccca_stride_blend_منزل_accc_copy_alpha(
    uint32_t *SDL_RESTRICT pw_سروت,
    uint32_t *SDL_RESTRICT pw_نشانہ,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn_ccca_accc,
                              sdl_sve_rgb32_blend_op_copy_alpha(0););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_ccca_blend_منزل_accc_fill_alpha(uint8_t *SDL_RESTRICT pch_سروت,
                                                         size_t u_سروت_Stride,
                                                         uint8_t *SDL_RESTRICT pch_نشانہ,
                                                         size_t u_نشانہ_Stride,
                                                         صحيح n_چوڑائی,
                                                         صحيح n_اچائی)
{
    طالما (n_اچائی--) {

        sdl_sve_ccca_stride_blend_منزل_accc_fill_alpha((uint32_t *)pch_سروت,
                                                     (uint32_t *)pch_نشانہ,
                                                     n_چوڑائی);

        pch_سروت += u_سروت_Stride;
        pch_نشانہ += u_نشانہ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_ccca_blend_منزل_accc_copy_alpha(uint8_t *SDL_RESTRICT pch_سروت,
                                                         size_t u_سروت_Stride,
                                                         uint8_t *SDL_RESTRICT pch_نشانہ,
                                                         size_t u_نشانہ_Stride,
                                                         صحيح n_چوڑائی,
                                                         صحيح n_اچائی)
{
    طالما (n_اچائی--) {

        sdl_sve_ccca_stride_blend_منزل_accc_copy_alpha((uint32_t *)pch_سروت,
                                                     (uint32_t *)pch_نشانہ,
                                                     n_چوڑائی);

        pch_سروت += u_سروت_Stride;
        pch_نشانہ += u_نشانہ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_a123_stride_blend_منزل_a321_fill_alpha(
    uint32_t *SDL_RESTRICT pw_سروت,
    uint32_t *SDL_RESTRICT pw_نشانہ,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn_a123_a321,
                              sdl_sve_rgb32_blend_op_fill_alpha(3););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_a123_stride_blend_منزل_a321_copy_alpha(
    uint32_t *SDL_RESTRICT pw_سروت,
    uint32_t *SDL_RESTRICT pw_نشانہ,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn_a123_a321,
                              sdl_sve_rgb32_blend_op_copy_alpha(3););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_a123_blend_منزل_a321_fill_alpha(uint8_t *SDL_RESTRICT pch_سروت,
                                                         size_t u_سروت_Stride,
                                                         uint8_t *SDL_RESTRICT pch_نشانہ,
                                                         size_t u_نشانہ_Stride,
                                                         صحيح n_چوڑائی,
                                                         صحيح n_اچائی)
{
    طالما (n_اچائی--) {

        sdl_sve_a123_stride_blend_منزل_a321_fill_alpha((uint32_t *)pch_سروت,
                                                     (uint32_t *)pch_نشانہ,
                                                     n_چوڑائی);

        pch_سروت += u_سروت_Stride;
        pch_نشانہ += u_نشانہ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_a123_blend_منزل_a321_copy_alpha(uint8_t *SDL_RESTRICT pch_سروت,
                                                         size_t u_سروت_Stride,
                                                         uint8_t *SDL_RESTRICT pch_نشانہ,
                                                         size_t u_نشانہ_Stride,
                                                         صحيح n_چوڑائی,
                                                         صحيح n_اچائی)
{
    طالما (n_اچائی--) {

        sdl_sve_a123_stride_blend_منزل_a321_copy_alpha((uint32_t *)pch_سروت,
                                                     (uint32_t *)pch_نشانہ,
                                                     n_چوڑائی);

        pch_سروت += u_سروت_Stride;
        pch_نشانہ += u_نشانہ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_123a_stride_blend_منزل_321a_fill_alpha(
    uint32_t *SDL_RESTRICT pw_سروت,
    uint32_t *SDL_RESTRICT pw_نشانہ,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn_123a_321a,
                              sdl_sve_rgb32_blend_op_fill_alpha(0););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_123a_stride_blend_منزل_321a_copy_alpha(
    uint32_t *SDL_RESTRICT pw_سروت,
    uint32_t *SDL_RESTRICT pw_نشانہ,
    size_t uStride)
{
    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn_123a_321a,
                              sdl_sve_rgb32_blend_op_copy_alpha(0););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_123a_blend_منزل_321a_fill_alpha(uint8_t *SDL_RESTRICT pch_سروت,
                                                         size_t u_سروت_Stride,
                                                         uint8_t *SDL_RESTRICT pch_نشانہ,
                                                         size_t u_نشانہ_Stride,
                                                         صحيح n_چوڑائی,
                                                         صحيح n_اچائی)
{
    طالما (n_اچائی--) {

        sdl_sve_123a_stride_blend_منزل_321a_fill_alpha((uint32_t *)pch_سروت,
                                                     (uint32_t *)pch_نشانہ,
                                                     n_چوڑائی);

        pch_سروت += u_سروت_Stride;
        pch_نشانہ += u_نشانہ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_123a_blend_منزل_321a_copy_alpha(uint8_t *SDL_RESTRICT pch_سروت,
                                                         size_t u_سروت_Stride,
                                                         uint8_t *SDL_RESTRICT pch_نشانہ,
                                                         size_t u_نشانہ_Stride,
                                                         صحيح n_چوڑائی,
                                                         صحيح n_اچائی)
{
    طالما (n_اچائی--) {

        sdl_sve_123a_stride_blend_منزل_321a_copy_alpha((uint32_t *)pch_سروت,
                                                     (uint32_t *)pch_نشانہ,
                                                     n_چوڑائی);

        pch_سروت += u_سروت_Stride;
        pch_نشانہ += u_نشانہ_Stride;
    }
}

/*
 * Source: XCCC and CCCX
 */

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_xccc_stride_blend_منزل_accc_fill_alpha(
    uint32_t *SDL_RESTRICT pw_سروت,
    uint32_t *SDL_RESTRICT pw_نشانہ,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(3,
                                       sdl_sve_pixel_u16x4_foreach_chn,
                                       sdl_sve_rgb32_blend_op_fill_alpha(3););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_xccc_stride_blend_منزل_accc_copy_alpha(
    uint32_t *SDL_RESTRICT pw_سروت,
    uint32_t *SDL_RESTRICT pw_نشانہ,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(3,
                                       sdl_sve_pixel_u16x4_foreach_chn,
                                       sdl_sve_rgb32_blend_op_copy_alpha(3););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_cccx_stride_blend_منزل_ccca_fill_alpha(
    uint32_t *SDL_RESTRICT pw_سروت,
    uint32_t *SDL_RESTRICT pw_نشانہ,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(0,
                                       sdl_sve_pixel_u16x4_foreach_chn,
                                       sdl_sve_rgb32_blend_op_fill_alpha(0);

    );
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_cccx_stride_blend_منزل_ccca_copy_alpha(
    uint32_t *SDL_RESTRICT pw_سروت,
    uint32_t *SDL_RESTRICT pw_نشانہ,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(0,
                                       sdl_sve_pixel_u16x4_foreach_chn,
                                       sdl_sve_rgb32_blend_op_copy_alpha(0););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_xccc_blend_منزل_accc_fill_alpha(
    uint8_t *SDL_RESTRICT pch_سروت,
    size_t u_سروت_Stride,
    uint8_t *SDL_RESTRICT pch_نشانہ,
    size_t u_نشانہ_Stride,
    صحيح n_چوڑائی,
    صحيح n_اچائی)
{
    طالما (n_اچائی--) {

        sdl_sve_xccc_stride_blend_منزل_accc_fill_alpha(
            (uint32_t *)pch_سروت,
            (uint32_t *)pch_نشانہ,
            n_چوڑائی);

        pch_سروت += u_سروت_Stride;
        pch_نشانہ += u_نشانہ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_xccc_blend_منزل_accc_copy_alpha(
    uint8_t *SDL_RESTRICT pch_سروت,
    size_t u_سروت_Stride,
    uint8_t *SDL_RESTRICT pch_نشانہ,
    size_t u_نشانہ_Stride,
    صحيح n_چوڑائی,
    صحيح n_اچائی)
{
    طالما (n_اچائی--) {

        sdl_sve_xccc_stride_blend_منزل_accc_copy_alpha(
            (uint32_t *)pch_سروت,
            (uint32_t *)pch_نشانہ,
            n_چوڑائی);

        pch_سروت += u_سروت_Stride;
        pch_نشانہ += u_نشانہ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_cccx_blend_منزل_ccca_fill_alpha(
    uint8_t *SDL_RESTRICT pch_سروت,
    size_t u_سروت_Stride,
    uint8_t *SDL_RESTRICT pch_نشانہ,
    size_t u_نشانہ_Stride,
    صحيح n_چوڑائی,
    صحيح n_اچائی)
{
    طالما (n_اچائی--) {

        sdl_sve_cccx_stride_blend_منزل_ccca_fill_alpha(
            (uint32_t *)pch_سروت,
            (uint32_t *)pch_نشانہ,
            n_چوڑائی);

        pch_سروت += u_سروت_Stride;
        pch_نشانہ += u_نشانہ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_cccx_blend_منزل_ccca_copy_alpha(
    uint8_t *SDL_RESTRICT pch_سروت,
    size_t u_سروت_Stride,
    uint8_t *SDL_RESTRICT pch_نشانہ,
    size_t u_نشانہ_Stride,
    صحيح n_چوڑائی,
    صحيح n_اچائی)
{
    طالما (n_اچائی--) {

        sdl_sve_cccx_stride_blend_منزل_ccca_copy_alpha(
            (uint32_t *)pch_سروت,
            (uint32_t *)pch_نشانہ,
            n_چوڑائی);

        pch_سروت += u_سروت_Stride;
        pch_نشانہ += u_نشانہ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_x123_stride_blend_منزل_321a_fill_alpha(
    uint32_t *SDL_RESTRICT pw_سروت,
    uint32_t *SDL_RESTRICT pw_نشانہ,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(3,
                                       sdl_sve_pixel_u16x4_foreach_chn_src_dst_rev,
                                       sdl_sve_rgb32_blend_op_fill_alpha(3););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_x123_stride_blend_منزل_321a_copy_alpha(
    uint32_t *SDL_RESTRICT pw_سروت,
    uint32_t *SDL_RESTRICT pw_نشانہ,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(3,
                                       sdl_sve_pixel_u16x4_foreach_chn_src_dst_rev,
                                       sdl_sve_rgb32_blend_op_copy_alpha(3););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_x123_blend_منزل_321a_fill_alpha(uint8_t *SDL_RESTRICT pch_سروت,
                                                         size_t u_سروت_Stride,
                                                         uint8_t *SDL_RESTRICT pch_نشانہ,
                                                         size_t u_نشانہ_Stride,
                                                         صحيح n_چوڑائی,
                                                         صحيح n_اچائی)
{
    طالما (n_اچائی--) {

        sdl_sve_x123_stride_blend_منزل_321a_fill_alpha((uint32_t *)pch_سروت,
                                                     (uint32_t *)pch_نشانہ,
                                                     n_چوڑائی);

        pch_سروت += u_سروت_Stride;
        pch_نشانہ += u_نشانہ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_x123_blend_منزل_321a_copy_alpha(uint8_t *SDL_RESTRICT pch_سروت,
                                                         size_t u_سروت_Stride,
                                                         uint8_t *SDL_RESTRICT pch_نشانہ,
                                                         size_t u_نشانہ_Stride,
                                                         صحيح n_چوڑائی,
                                                         صحيح n_اچائی)
{
    طالما (n_اچائی--) {

        sdl_sve_x123_stride_blend_منزل_321a_copy_alpha((uint32_t *)pch_سروت,
                                                     (uint32_t *)pch_نشانہ,
                                                     n_چوڑائی);

        pch_سروت += u_سروت_Stride;
        pch_نشانہ += u_نشانہ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_123x_stride_blend_منزل_a321_fill_alpha(
    uint32_t *SDL_RESTRICT pw_سروت,
    uint32_t *SDL_RESTRICT pw_نشانہ,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(0,
                                       sdl_sve_pixel_u16x4_foreach_chn_src_dst_rev,
                                       sdl_sve_rgb32_blend_op_fill_alpha(0););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_123x_stride_blend_منزل_a321_copy_alpha(
    uint32_t *SDL_RESTRICT pw_سروت,
    uint32_t *SDL_RESTRICT pw_نشانہ,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(0,
                                       sdl_sve_pixel_u16x4_foreach_chn_src_dst_rev,
                                       sdl_sve_rgb32_blend_op_copy_alpha(0););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_123x_blend_منزل_a321_fill_alpha(uint8_t *SDL_RESTRICT pch_سروت,
                                                         size_t u_سروت_Stride,
                                                         uint8_t *SDL_RESTRICT pch_نشانہ,
                                                         size_t u_نشانہ_Stride,
                                                         صحيح n_چوڑائی,
                                                         صحيح n_اچائی)
{
    طالما (n_اچائی--) {

        sdl_sve_123x_stride_blend_منزل_a321_fill_alpha((uint32_t *)pch_سروت,
                                                     (uint32_t *)pch_نشانہ,
                                                     n_چوڑائی);

        pch_سروت += u_سروت_Stride;
        pch_نشانہ += u_نشانہ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_123x_blend_منزل_a321_copy_alpha(uint8_t *SDL_RESTRICT pch_سروت,
                                                         size_t u_سروت_Stride,
                                                         uint8_t *SDL_RESTRICT pch_نشانہ,
                                                         size_t u_نشانہ_Stride,
                                                         صحيح n_چوڑائی,
                                                         صحيح n_اچائی)
{
    طالما (n_اچائی--) {

        sdl_sve_123x_stride_blend_منزل_a321_copy_alpha((uint32_t *)pch_سروت,
                                                     (uint32_t *)pch_نشانہ,
                                                     n_چوڑائی);

        pch_سروت += u_سروت_Stride;
        pch_نشانہ += u_نشانہ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_xccc_stride_blend_منزل_ccca_fill_alpha(
    uint32_t *SDL_RESTRICT pw_سروت,
    uint32_t *SDL_RESTRICT pw_نشانہ,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(3,
                                       sdl_sve_pixel_u16x4_foreach_chn_accc_ccca,
                                       sdl_sve_rgb32_blend_op_fill_alpha(3););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_xccc_stride_blend_منزل_ccca_copy_alpha(
    uint32_t *SDL_RESTRICT pw_سروت,
    uint32_t *SDL_RESTRICT pw_نشانہ,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(3,
                                       sdl_sve_pixel_u16x4_foreach_chn_accc_ccca,
                                       sdl_sve_rgb32_blend_op_copy_alpha(3););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_xccc_blend_منزل_ccca_fill_alpha(uint8_t *SDL_RESTRICT pch_سروت,
                                                         size_t u_سروت_Stride,
                                                         uint8_t *SDL_RESTRICT pch_نشانہ,
                                                         size_t u_نشانہ_Stride,
                                                         صحيح n_چوڑائی,
                                                         صحيح n_اچائی)
{
    طالما (n_اچائی--) {

        sdl_sve_xccc_stride_blend_منزل_ccca_fill_alpha((uint32_t *)pch_سروت,
                                                     (uint32_t *)pch_نشانہ,
                                                     n_چوڑائی);

        pch_سروت += u_سروت_Stride;
        pch_نشانہ += u_نشانہ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_xccc_blend_منزل_ccca_copy_alpha(uint8_t *SDL_RESTRICT pch_سروت,
                                                         size_t u_سروت_Stride,
                                                         uint8_t *SDL_RESTRICT pch_نشانہ,
                                                         size_t u_نشانہ_Stride,
                                                         صحيح n_چوڑائی,
                                                         صحيح n_اچائی)
{
    طالما (n_اچائی--) {

        sdl_sve_xccc_stride_blend_منزل_ccca_copy_alpha((uint32_t *)pch_سروت,
                                                     (uint32_t *)pch_نشانہ,
                                                     n_چوڑائی);

        pch_سروت += u_سروت_Stride;
        pch_نشانہ += u_نشانہ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_cccx_stride_blend_منزل_accc_fill_alpha(
    uint32_t *SDL_RESTRICT pw_سروت,
    uint32_t *SDL_RESTRICT pw_نشانہ,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(0,
                                       sdl_sve_pixel_u16x4_foreach_chn_ccca_accc,
                                       sdl_sve_rgb32_blend_op_fill_alpha(0););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_cccx_stride_blend_منزل_accc_copy_alpha(
    uint32_t *SDL_RESTRICT pw_سروت,
    uint32_t *SDL_RESTRICT pw_نشانہ,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(0,
                                       sdl_sve_pixel_u16x4_foreach_chn_ccca_accc,
                                       sdl_sve_rgb32_blend_op_copy_alpha(0););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_cccx_blend_منزل_accc_fill_alpha(uint8_t *SDL_RESTRICT pch_سروت,
                                                         size_t u_سروت_Stride,
                                                         uint8_t *SDL_RESTRICT pch_نشانہ,
                                                         size_t u_نشانہ_Stride,
                                                         صحيح n_چوڑائی,
                                                         صحيح n_اچائی)
{
    طالما (n_اچائی--) {

        sdl_sve_cccx_stride_blend_منزل_accc_fill_alpha((uint32_t *)pch_سروت,
                                                     (uint32_t *)pch_نشانہ,
                                                     n_چوڑائی);

        pch_سروت += u_سروت_Stride;
        pch_نشانہ += u_نشانہ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_cccx_blend_منزل_accc_copy_alpha(uint8_t *SDL_RESTRICT pch_سروت,
                                                         size_t u_سروت_Stride,
                                                         uint8_t *SDL_RESTRICT pch_نشانہ,
                                                         size_t u_نشانہ_Stride,
                                                         صحيح n_چوڑائی,
                                                         صحيح n_اچائی)
{
    طالما (n_اچائی--) {

        sdl_sve_cccx_stride_blend_منزل_accc_copy_alpha((uint32_t *)pch_سروت,
                                                     (uint32_t *)pch_نشانہ,
                                                     n_چوڑائی);

        pch_سروت += u_سروت_Stride;
        pch_نشانہ += u_نشانہ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_x123_stride_blend_منزل_a321_fill_alpha(
    uint32_t *SDL_RESTRICT pw_سروت,
    uint32_t *SDL_RESTRICT pw_نشانہ,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(3,
                                       sdl_sve_pixel_u16x4_foreach_chn_a123_a321,
                                       sdl_sve_rgb32_blend_op_fill_alpha(3););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_x123_stride_blend_منزل_a321_copy_alpha(
    uint32_t *SDL_RESTRICT pw_سروت,
    uint32_t *SDL_RESTRICT pw_نشانہ,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(3,
                                       sdl_sve_pixel_u16x4_foreach_chn_a123_a321,
                                       sdl_sve_rgb32_blend_op_copy_alpha(3););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_x123_blend_منزل_a321_fill_alpha(uint8_t *SDL_RESTRICT pch_سروت,
                                                         size_t u_سروت_Stride,
                                                         uint8_t *SDL_RESTRICT pch_نشانہ,
                                                         size_t u_نشانہ_Stride,
                                                         صحيح n_چوڑائی,
                                                         صحيح n_اچائی)
{
    طالما (n_اچائی--) {

        sdl_sve_x123_stride_blend_منزل_a321_fill_alpha((uint32_t *)pch_سروت,
                                                     (uint32_t *)pch_نشانہ,
                                                     n_چوڑائی);

        pch_سروت += u_سروت_Stride;
        pch_نشانہ += u_نشانہ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_x123_blend_منزل_a321_copy_alpha(uint8_t *SDL_RESTRICT pch_سروت,
                                                         size_t u_سروت_Stride,
                                                         uint8_t *SDL_RESTRICT pch_نشانہ,
                                                         size_t u_نشانہ_Stride,
                                                         صحيح n_چوڑائی,
                                                         صحيح n_اچائی)
{
    طالما (n_اچائی--) {

        sdl_sve_x123_stride_blend_منزل_a321_copy_alpha((uint32_t *)pch_سروت,
                                                     (uint32_t *)pch_نشانہ,
                                                     n_چوڑائی);

        pch_سروت += u_سروت_Stride;
        pch_نشانہ += u_نشانہ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_123x_stride_blend_منزل_321a_fill_alpha(
    uint32_t *SDL_RESTRICT pw_سروت,
    uint32_t *SDL_RESTRICT pw_نشانہ,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(0,
                                       sdl_sve_pixel_u16x4_foreach_chn_123a_321a,
                                       sdl_sve_rgb32_blend_op_fill_alpha(0););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_123x_stride_blend_منزل_321a_copy_alpha(
    uint32_t *SDL_RESTRICT pw_سروت,
    uint32_t *SDL_RESTRICT pw_نشانہ,
    size_t uStride)
{
    sdl_sve_rgb32_no_alpha_stride_impl(0,
                                       sdl_sve_pixel_u16x4_foreach_chn_123a_321a,
                                       sdl_sve_rgb32_blend_op_copy_alpha(0););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_123x_blend_منزل_321a_fill_alpha(uint8_t *SDL_RESTRICT pch_سروت,
                                                         size_t u_سروت_Stride,
                                                         uint8_t *SDL_RESTRICT pch_نشانہ,
                                                         size_t u_نشانہ_Stride,
                                                         صحيح n_چوڑائی,
                                                         صحيح n_اچائی)
{
    طالما (n_اچائی--) {

        sdl_sve_123x_stride_blend_منزل_321a_fill_alpha((uint32_t *)pch_سروت,
                                                     (uint32_t *)pch_نشانہ,
                                                     n_چوڑائی);

        pch_سروت += u_سروت_Stride;
        pch_نشانہ += u_نشانہ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_123x_blend_منزل_321a_copy_alpha(uint8_t *SDL_RESTRICT pch_سروت,
                                                         size_t u_سروت_Stride,
                                                         uint8_t *SDL_RESTRICT pch_نشانہ,
                                                         size_t u_نشانہ_Stride,
                                                         صحيح n_چوڑائی,
                                                         صحيح n_اچائی)
{
    طالما (n_اچائی--) {

        sdl_sve_123x_stride_blend_منزل_321a_copy_alpha((uint32_t *)pch_سروت,
                                                     (uint32_t *)pch_نشانہ,
                                                     n_چوڑائی);

        pch_سروت += u_سروت_Stride;
        pch_نشانہ += u_نشانہ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1)
ساكن مضمن فراغ sdl_sve_8888_منزل_8888_swizzle_dispatcher(SDL_BlitInfo *info)
{
    صحيح چوڑائی = info->dst_w;
    صحيح اچائی = info->dst_h;
    uint8_t *src = info->src;
    صحيح srcskip = info->src_skip;
    uint8_t *dst = info->dst;
    صحيح dstskip = info->dst_skip;

    ثابت SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    ثابت SDL_PixelFormatDetails *dstfmt = info->dst_fmt;

    // Set up some basic variables
    صحيح srcbpp = srcfmt->بائٹاں_فی_pixel;
    صحيح dstbpp = dstfmt->بائٹاں_فی_pixel;

    أكد((srcbpp == 4) && (dstbpp == 4));

    bool fill_alpha = (!dstfmt->Amask);

    صحيح srcstride = srcskip + srcbpp * چوڑائی;
    صحيح dststride = dstskip + dstbpp * چوڑائی;

    بدل (srcfmt->format) {
    حالة SDL_PIXELFORMAT_XRGB8888:
        بدل (dstfmt->format) {
        حالة SDL_PIXELFORMAT_ARGB8888:
        حالة SDL_PIXELFORMAT_XRGB8888:
            إذا (fill_alpha) {
                sdl_sve_xccc_blend_منزل_accc_fill_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    چوڑائی,
                    اچائی);
            } وإلا {
                sdl_sve_xccc_blend_منزل_accc_copy_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    چوڑائی,
                    اچائی);
            }
            اكسر;

        حالة SDL_PIXELFORMAT_RGBA8888:
        حالة SDL_PIXELFORMAT_RGBX8888:
            إذا (fill_alpha) {
                sdl_sve_xccc_blend_منزل_ccca_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اچائی);
            } وإلا {
                sdl_sve_xccc_blend_منزل_ccca_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اچائی);
            }
            اكسر;

        حالة SDL_PIXELFORMAT_ABGR8888:
        حالة SDL_PIXELFORMAT_XBGR8888:
            إذا (fill_alpha) {
                sdl_sve_x123_blend_منزل_a321_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اچائی);
            } وإلا {
                sdl_sve_x123_blend_منزل_a321_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اچائی);
            }
            اكسر;

        حالة SDL_PIXELFORMAT_BGRA8888:
        حالة SDL_PIXELFORMAT_BGRX8888:
            إذا (fill_alpha) {
                sdl_sve_x123_blend_منزل_321a_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اچائی);
            } وإلا {
                sdl_sve_x123_blend_منزل_321a_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اچائی);
            }
            اكسر;
        افتراضي:
            أكد(false);
            اكسر;
        }
        اكسر;

    حالة SDL_PIXELFORMAT_ARGB8888:
        بدل (dstfmt->format) {
        حالة SDL_PIXELFORMAT_ARGB8888:
        حالة SDL_PIXELFORMAT_XRGB8888:
            إذا (fill_alpha) {
                sdl_sve_accc_blend_منزل_accc_fill_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    چوڑائی,
                    اچائی);
            } وإلا {
                sdl_sve_accc_blend_منزل_accc_copy_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    چوڑائی,
                    اچائی);
            }
            اكسر;

        حالة SDL_PIXELFORMAT_RGBA8888:
        حالة SDL_PIXELFORMAT_RGBX8888:
            إذا (fill_alpha) {
                sdl_sve_accc_blend_منزل_ccca_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اچائی);
            } وإلا {
                sdl_sve_accc_blend_منزل_ccca_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اچائی);
            }
            اكسر;

        حالة SDL_PIXELFORMAT_ABGR8888:
        حالة SDL_PIXELFORMAT_XBGR8888:
            إذا (fill_alpha) {
                sdl_sve_a123_blend_منزل_a321_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اچائی);
            } وإلا {
                sdl_sve_a123_blend_منزل_a321_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اچائی);
            }
            اكسر;

        حالة SDL_PIXELFORMAT_BGRA8888:
        حالة SDL_PIXELFORMAT_BGRX8888:
            إذا (fill_alpha) {
                sdl_sve_a123_blend_منزل_321a_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اچائی);
            } وإلا {
                sdl_sve_a123_blend_منزل_321a_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اچائی);
            }
            اكسر;
        افتراضي:
            أكد(false);
            اكسر;
        }
        اكسر;

    حالة SDL_PIXELFORMAT_RGBX8888:
        بدل (dstfmt->format) {
        حالة SDL_PIXELFORMAT_ARGB8888:
        حالة SDL_PIXELFORMAT_XRGB8888:
            إذا (fill_alpha) {
                sdl_sve_cccx_blend_منزل_accc_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اچائی);
            } وإلا {
                sdl_sve_cccx_blend_منزل_accc_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اچائی);
            }
            اكسر;

        حالة SDL_PIXELFORMAT_RGBA8888:
        حالة SDL_PIXELFORMAT_RGBX8888:
            إذا (fill_alpha) {
                sdl_sve_cccx_blend_منزل_ccca_fill_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    چوڑائی,
                    اچائی);
            } وإلا {
                sdl_sve_cccx_blend_منزل_ccca_copy_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    چوڑائی,
                    اچائی);
            }
            اكسر;

        حالة SDL_PIXELFORMAT_ABGR8888:
        حالة SDL_PIXELFORMAT_XBGR8888:
            إذا (fill_alpha) {
                sdl_sve_123x_blend_منزل_a321_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اچائی);
            } وإلا {
                sdl_sve_123x_blend_منزل_a321_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اچائی);
            }
            اكسر;

        حالة SDL_PIXELFORMAT_BGRA8888:
        حالة SDL_PIXELFORMAT_BGRX8888:
            إذا (fill_alpha) {
                sdl_sve_123x_blend_منزل_321a_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اچائی);
            } وإلا {
                sdl_sve_123x_blend_منزل_321a_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اچائی);
            }
            اكسر;
        افتراضي:
            أكد(false);
            اكسر;
        }
        اكسر;

    حالة SDL_PIXELFORMAT_RGBA8888:
        بدل (dstfmt->format) {
        حالة SDL_PIXELFORMAT_ARGB8888:
        حالة SDL_PIXELFORMAT_XRGB8888:
            إذا (fill_alpha) {
                sdl_sve_ccca_blend_منزل_accc_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اچائی);
            } وإلا {
                sdl_sve_ccca_blend_منزل_accc_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اچائی);
            }
            اكسر;

        حالة SDL_PIXELFORMAT_RGBA8888:
        حالة SDL_PIXELFORMAT_RGBX8888:
            إذا (fill_alpha) {
                sdl_sve_ccca_blend_منزل_ccca_fill_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    چوڑائی,
                    اچائی);
            } وإلا {
                sdl_sve_ccca_blend_منزل_ccca_copy_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    چوڑائی,
                    اچائی);
            }
            اكسر;

        حالة SDL_PIXELFORMAT_ABGR8888:
        حالة SDL_PIXELFORMAT_XBGR8888:
            إذا (fill_alpha) {
                sdl_sve_123a_blend_منزل_a321_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اچائی);
            } وإلا {
                sdl_sve_123a_blend_منزل_a321_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اچائی);
            }
            اكسر;

        حالة SDL_PIXELFORMAT_BGRA8888:
        حالة SDL_PIXELFORMAT_BGRX8888:
            إذا (fill_alpha) {
                sdl_sve_123a_blend_منزل_321a_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اچائی);
            } وإلا {
                sdl_sve_123a_blend_منزل_321a_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اچائی);
            }
            اكسر;
        افتراضي:
            أكد(false);
            اكسر;
        }
        اكسر;

    حالة SDL_PIXELFORMAT_XBGR8888:
        بدل (dstfmt->format) {
        حالة SDL_PIXELFORMAT_ARGB8888:
        حالة SDL_PIXELFORMAT_XRGB8888:
            إذا (fill_alpha) {
                sdl_sve_x123_blend_منزل_a321_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اچائی);
            } وإلا {
                sdl_sve_x123_blend_منزل_a321_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اچائی);
            }
            اكسر;

        حالة SDL_PIXELFORMAT_RGBA8888:
        حالة SDL_PIXELFORMAT_RGBX8888:
            إذا (fill_alpha) {
                sdl_sve_x123_blend_منزل_321a_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اچائی);
            } وإلا {
                sdl_sve_x123_blend_منزل_321a_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اچائی);
            }
            اكسر;

        حالة SDL_PIXELFORMAT_ABGR8888:
        حالة SDL_PIXELFORMAT_XBGR8888:
            إذا (fill_alpha) {
                sdl_sve_xccc_blend_منزل_accc_fill_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    چوڑائی,
                    اچائی);
            } وإلا {
                sdl_sve_xccc_blend_منزل_accc_copy_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    چوڑائی,
                    اچائی);
            }
            اكسر;

        حالة SDL_PIXELFORMAT_BGRA8888:
        حالة SDL_PIXELFORMAT_BGRX8888:
            إذا (fill_alpha) {
                sdl_sve_xccc_blend_منزل_ccca_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اچائی);
            } وإلا {
                sdl_sve_xccc_blend_منزل_ccca_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اچائی);
            }
            اكسر;
        افتراضي:
            أكد(false);
            اكسر;
        }
        اكسر;

    حالة SDL_PIXELFORMAT_ABGR8888:
        بدل (dstfmt->format) {
        حالة SDL_PIXELFORMAT_ARGB8888:
        حالة SDL_PIXELFORMAT_XRGB8888:
            إذا (fill_alpha) {
                sdl_sve_a123_blend_منزل_a321_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اچائی);
            } وإلا {
                sdl_sve_a123_blend_منزل_a321_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اچائی);
            }
            اكسر;

        حالة SDL_PIXELFORMAT_RGBA8888:
        حالة SDL_PIXELFORMAT_RGBX8888:
            إذا (fill_alpha) {
                sdl_sve_a123_blend_منزل_321a_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اچائی);
            } وإلا {
                sdl_sve_a123_blend_منزل_321a_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اچائی);
            }
            اكسر;

        حالة SDL_PIXELFORMAT_ABGR8888:
        حالة SDL_PIXELFORMAT_XBGR8888:
            إذا (fill_alpha) {
                sdl_sve_accc_blend_منزل_accc_fill_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    چوڑائی,
                    اچائی);
            } وإلا {
                sdl_sve_accc_blend_منزل_accc_copy_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    چوڑائی,
                    اچائی);
            }
            اكسر;

        حالة SDL_PIXELFORMAT_BGRA8888:
        حالة SDL_PIXELFORMAT_BGRX8888:
            إذا (fill_alpha) {
                sdl_sve_accc_blend_منزل_ccca_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اچائی);
            } وإلا {
                sdl_sve_accc_blend_منزل_ccca_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اچائی);
            }
            اكسر;
        افتراضي:
            أكد(false);
            اكسر;
        }
        اكسر;

    حالة SDL_PIXELFORMAT_BGRX8888:
        بدل (dstfmt->format) {
        حالة SDL_PIXELFORMAT_ARGB8888:
        حالة SDL_PIXELFORMAT_XRGB8888:
            إذا (fill_alpha) {
                sdl_sve_123x_blend_منزل_a321_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اچائی);
            } وإلا {
                sdl_sve_123x_blend_منزل_a321_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اچائی);
            }
            اكسر;

        حالة SDL_PIXELFORMAT_RGBA8888:
        حالة SDL_PIXELFORMAT_RGBX8888:
            إذا (fill_alpha) {
                sdl_sve_123x_blend_منزل_321a_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اچائی);
            } وإلا {
                sdl_sve_123x_blend_منزل_321a_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اچائی);
            }
            اكسر;

        حالة SDL_PIXELFORMAT_ABGR8888:
        حالة SDL_PIXELFORMAT_XBGR8888:
            إذا (fill_alpha) {
                sdl_sve_cccx_blend_منزل_accc_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اچائی);
            } وإلا {
                sdl_sve_cccx_blend_منزل_accc_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اچائی);
            }
            اكسر;

        حالة SDL_PIXELFORMAT_BGRA8888:
        حالة SDL_PIXELFORMAT_BGRX8888:
            إذا (fill_alpha) {
                sdl_sve_cccx_blend_منزل_ccca_fill_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    چوڑائی,
                    اچائی);
            } وإلا {
                sdl_sve_cccx_blend_منزل_ccca_copy_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    چوڑائی,
                    اچائی);
            }
            اكسر;
        افتراضي:
            أكد(false);
            اكسر;
        }
        اكسر;

    حالة SDL_PIXELFORMAT_BGRA8888:
        بدل (dstfmt->format) {
        حالة SDL_PIXELFORMAT_ARGB8888:
        حالة SDL_PIXELFORMAT_XRGB8888:
            إذا (fill_alpha) {
                sdl_sve_123a_blend_منزل_a321_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اچائی);
            } وإلا {
                sdl_sve_123a_blend_منزل_a321_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اچائی);
            }
            اكسر;

        حالة SDL_PIXELFORMAT_RGBA8888:
        حالة SDL_PIXELFORMAT_RGBX8888:
            إذا (fill_alpha) {
                sdl_sve_123a_blend_منزل_321a_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اچائی);
            } وإلا {
                sdl_sve_123a_blend_منزل_321a_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اچائی);
            }
            اكسر;

        حالة SDL_PIXELFORMAT_ABGR8888:
        حالة SDL_PIXELFORMAT_XBGR8888:
            إذا (fill_alpha) {
                sdl_sve_ccca_blend_منزل_accc_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اچائی);
            } وإلا {
                sdl_sve_ccca_blend_منزل_accc_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      چوڑائی,
                                                      اچائی);
            }
            اكسر;

        حالة SDL_PIXELFORMAT_BGRA8888:
        حالة SDL_PIXELFORMAT_BGRX8888:
            إذا (fill_alpha) {
                sdl_sve_ccca_blend_منزل_ccca_fill_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    چوڑائی,
                    اچائی);
            } وإلا {
                sdl_sve_ccca_blend_منزل_ccca_copy_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    چوڑائی,
                    اچائی);
            }
            اكسر;
        افتراضي:
            أكد(false);
            اكسر;
        }
        اكسر;

    افتراضي:
        أكد(false);
        اكسر;
    }
}

#جے_بنا_تعریف sdl_sve_rgb32_blend_منزل_rgb565_op
#تعریف_کرو sdl_sve_rgb32_blend_منزل_rgb565_op(ma_alpha_chn_idx)
#جے_انت

/*
 * ACCC or CCCA
 */
SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_argb8888_stride_blend_منزل_rgb565(uint32_t *SDL_RESTRICT pw_سروت,
                                                           uint16_t *SDL_RESTRICT phw_نشانہ,
                                                           size_t uStride)
{
    sdl_sve_rgb32_منزل_rgb565_stride_impl(
        sdl_sve_pixel_u16x4_foreach_chn_argb_rgb565,
        {
            sdl_sve_rgb32_blend_منزل_rgb565_op(3);
        });
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_argb8888_blend_منزل_rgb565(uint8_t *SDL_RESTRICT pch_سروت,
                                                    size_t u_سروت_Stride,
                                                    uint8_t *SDL_RESTRICT pch_نشانہ,
                                                    size_t u_نشانہ_Stride,
                                                    صحيح n_چوڑائی,
                                                    صحيح n_اچائی)
{
    طالما (n_اچائی--) {

        sdl_sve_argb8888_stride_blend_منزل_rgb565((uint32_t *)pch_سروت,
                                                (uint16_t *)pch_نشانہ,
                                                n_چوڑائی);

        pch_سروت += u_سروت_Stride;
        pch_نشانہ += u_نشانہ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_rgba8888_stride_blend_منزل_rgb565(uint32_t *SDL_RESTRICT pw_سروت,
                                                           uint16_t *SDL_RESTRICT phw_نشانہ,
                                                           size_t uStride)
{
    sdl_sve_rgb32_منزل_rgb565_stride_impl(
        sdl_sve_pixel_u16x4_foreach_chn_rgba_rgb565,
        {
            sdl_sve_rgb32_blend_منزل_rgb565_op(0);
        });
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_rgba8888_blend_منزل_rgb565(uint8_t *SDL_RESTRICT pch_سروت,
                                                    size_t u_سروت_Stride,
                                                    uint8_t *SDL_RESTRICT pch_نشانہ,
                                                    size_t u_نشانہ_Stride,
                                                    صحيح n_چوڑائی,
                                                    صحيح n_اچائی)
{
    طالما (n_اچائی--) {

        sdl_sve_rgba8888_stride_blend_منزل_rgb565((uint32_t *)pch_سروت,
                                                (uint16_t *)pch_نشانہ,
                                                n_چوڑائی);

        pch_سروت += u_سروت_Stride;
        pch_نشانہ += u_نشانہ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_bgra8888_stride_blend_منزل_rgb565(uint32_t *SDL_RESTRICT pw_سروت,
                                                           uint16_t *SDL_RESTRICT phw_نشانہ,
                                                           size_t uStride)
{
    sdl_sve_rgb32_منزل_rgb565_stride_impl(
        sdl_sve_pixel_u16x4_foreach_chn_bgra_rgb565,
        {
            sdl_sve_rgb32_blend_منزل_rgb565_op(0);
        });
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_bgra8888_blend_منزل_rgb565(uint8_t *SDL_RESTRICT pch_سروت,
                                                    size_t u_سروت_Stride,
                                                    uint8_t *SDL_RESTRICT pch_نشانہ,
                                                    size_t u_نشانہ_Stride,
                                                    صحيح n_چوڑائی,
                                                    صحيح n_اچائی)
{
    طالما (n_اچائی--) {

        sdl_sve_bgra8888_stride_blend_منزل_rgb565((uint32_t *)pch_سروت,
                                                (uint16_t *)pch_نشانہ,
                                                n_چوڑائی);

        pch_سروت += u_سروت_Stride;
        pch_نشانہ += u_نشانہ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_abgr8888_stride_blend_منزل_rgb565(uint32_t *SDL_RESTRICT pw_سروت,
                                                           uint16_t *SDL_RESTRICT phw_نشانہ,
                                                           size_t uStride)
{
    sdl_sve_rgb32_منزل_rgb565_stride_impl(
        sdl_sve_pixel_u16x4_foreach_chn_abgr_rgb565,
        {
            sdl_sve_rgb32_blend_منزل_rgb565_op(3);
        });
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_abgr8888_blend_منزل_rgb565(uint8_t *SDL_RESTRICT pch_سروت,
                                                    size_t u_سروت_Stride,
                                                    uint8_t *SDL_RESTRICT pch_نشانہ,
                                                    size_t u_نشانہ_Stride,
                                                    صحيح n_چوڑائی,
                                                    صحيح n_اچائی)
{
    طالما (n_اچائی--) {

        sdl_sve_abgr8888_stride_blend_منزل_rgb565((uint32_t *)pch_سروت,
                                                (uint16_t *)pch_نشانہ,
                                                n_چوڑائی);

        pch_سروت += u_سروت_Stride;
        pch_نشانہ += u_نشانہ_Stride;
    }
}

/*
 * XCCC or CCCX
 */
SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_xrgb8888_stride_blend_منزل_rgb565(uint32_t *SDL_RESTRICT pw_سروت,
                                                           uint16_t *SDL_RESTRICT phw_نشانہ,
                                                           size_t uStride)
{
    sdl_sve_rgb32_no_alpha_منزل_rgb565_stride_impl(
        3,
        sdl_sve_pixel_u16x4_foreach_chn_argb_rgb565,
        {
            sdl_sve_rgb32_blend_منزل_rgb565_op(3);
        });
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_xrgb8888_blend_منزل_rgb565(uint8_t *SDL_RESTRICT pch_سروت,
                                                    size_t u_سروت_Stride,
                                                    uint8_t *SDL_RESTRICT pch_نشانہ,
                                                    size_t u_نشانہ_Stride,
                                                    صحيح n_چوڑائی,
                                                    صحيح n_اچائی)
{
    طالما (n_اچائی--) {

        sdl_sve_xrgb8888_stride_blend_منزل_rgb565((uint32_t *)pch_سروت,
                                                (uint16_t *)pch_نشانہ,
                                                n_چوڑائی);

        pch_سروت += u_سروت_Stride;
        pch_نشانہ += u_نشانہ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_rgbx8888_stride_blend_منزل_rgb565(uint32_t *SDL_RESTRICT pw_سروت,
                                                           uint16_t *SDL_RESTRICT phw_نشانہ,
                                                           size_t uStride)
{
    sdl_sve_rgb32_no_alpha_منزل_rgb565_stride_impl(
        0,
        sdl_sve_pixel_u16x4_foreach_chn_rgba_rgb565,
        {
            sdl_sve_rgb32_blend_منزل_rgb565_op(0);
        });
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_rgbx8888_blend_منزل_rgb565(uint8_t *SDL_RESTRICT pch_سروت,
                                                    size_t u_سروت_Stride,
                                                    uint8_t *SDL_RESTRICT pch_نشانہ,
                                                    size_t u_نشانہ_Stride,
                                                    صحيح n_چوڑائی,
                                                    صحيح n_اچائی)
{
    طالما (n_اچائی--) {

        sdl_sve_rgbx8888_stride_blend_منزل_rgb565((uint32_t *)pch_سروت,
                                                (uint16_t *)pch_نشانہ,
                                                n_چوڑائی);

        pch_سروت += u_سروت_Stride;
        pch_نشانہ += u_نشانہ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_bgrx8888_stride_blend_منزل_rgb565(uint32_t *SDL_RESTRICT pw_سروت,
                                                           uint16_t *SDL_RESTRICT phw_نشانہ,
                                                           size_t uStride)
{
    sdl_sve_rgb32_no_alpha_منزل_rgb565_stride_impl(
        0,
        sdl_sve_pixel_u16x4_foreach_chn_bgra_rgb565,
        {
            sdl_sve_rgb32_blend_منزل_rgb565_op(0);
        });
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_bgrx8888_blend_منزل_rgb565(uint8_t *SDL_RESTRICT pch_سروت,
                                                    size_t u_سروت_Stride,
                                                    uint8_t *SDL_RESTRICT pch_نشانہ,
                                                    size_t u_نشانہ_Stride,
                                                    صحيح n_چوڑائی,
                                                    صحيح n_اچائی)
{
    طالما (n_اچائی--) {

        sdl_sve_bgrx8888_stride_blend_منزل_rgb565((uint32_t *)pch_سروت,
                                                (uint16_t *)pch_نشانہ,
                                                n_چوڑائی);

        pch_سروت += u_سروت_Stride;
        pch_نشانہ += u_نشانہ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ساكن مضمن فراغ sdl_sve_xbgr8888_stride_blend_منزل_rgb565(uint32_t *SDL_RESTRICT pw_سروت,
                                                           uint16_t *SDL_RESTRICT phw_نشانہ,
                                                           size_t uStride)
{
    sdl_sve_rgb32_no_alpha_منزل_rgb565_stride_impl(
        3,
        sdl_sve_pixel_u16x4_foreach_chn_abgr_rgb565,
        {
            sdl_sve_rgb32_blend_منزل_rgb565_op(3);
        });
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ساكن مضمن فراغ sdl_sve_xbgr8888_blend_منزل_rgb565(uint8_t *SDL_RESTRICT pch_سروت,
                                                    size_t u_سروت_Stride,
                                                    uint8_t *SDL_RESTRICT pch_نشانہ,
                                                    size_t u_نشانہ_Stride,
                                                    صحيح n_چوڑائی,
                                                    صحيح n_اچائی)
{
    طالما (n_اچائی--) {

        sdl_sve_xbgr8888_stride_blend_منزل_rgb565((uint32_t *)pch_سروت,
                                                (uint16_t *)pch_نشانہ,
                                                n_چوڑائی);

        pch_سروت += u_سروت_Stride;
        pch_نشانہ += u_نشانہ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1)
ساكن مضمن فراغ sdl_sve_rgb32_منزل_rgb565_swizzle_dispatcher(SDL_BlitInfo *info)
{
    صحيح چوڑائی = info->dst_w;
    صحيح اچائی = info->dst_h;
    uint8_t *src = info->src;
    صحيح srcskip = info->src_skip;
    uint8_t *dst = info->dst;
    صحيح dstskip = info->dst_skip;

    ثابت SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    ثابت SDL_PixelFormatDetails *dstfmt = info->dst_fmt;

    // Set up some basic variables
    صحيح srcbpp = srcfmt->بائٹاں_فی_pixel;
    صحيح dstbpp = dstfmt->بائٹاں_فی_pixel;

    أكد(srcbpp == 4);
    أكد(dstbpp == 2);

    صحيح srcstride = srcskip + srcbpp * چوڑائی;
    صحيح dststride = dstskip + dstbpp * چوڑائی;

    بدل (srcfmt->format) {
    حالة SDL_PIXELFORMAT_XRGB8888:
        sdl_sve_xrgb8888_blend_منزل_rgb565(src,
                                         srcstride,
                                         dst,
                                         dststride,
                                         چوڑائی,
                                         اچائی);
        اكسر;

    حالة SDL_PIXELFORMAT_ARGB8888:
        sdl_sve_argb8888_blend_منزل_rgb565(src,
                                         srcstride,
                                         dst,
                                         dststride,
                                         چوڑائی,
                                         اچائی);
        اكسر;

    حالة SDL_PIXELFORMAT_RGBX8888:
        sdl_sve_rgbx8888_blend_منزل_rgb565(src,
                                         srcstride,
                                         dst,
                                         dststride,
                                         چوڑائی,
                                         اچائی);
        اكسر;

    حالة SDL_PIXELFORMAT_RGBA8888:
        sdl_sve_rgba8888_blend_منزل_rgb565(src,
                                         srcstride,
                                         dst,
                                         dststride,
                                         چوڑائی,
                                         اچائی);
        اكسر;

    حالة SDL_PIXELFORMAT_XBGR8888:
        sdl_sve_xbgr8888_blend_منزل_rgb565(src,
                                         srcstride,
                                         dst,
                                         dststride,
                                         چوڑائی,
                                         اچائی);
        اكسر;

    حالة SDL_PIXELFORMAT_ABGR8888:
        sdl_sve_abgr8888_blend_منزل_rgb565(src,
                                         srcstride,
                                         dst,
                                         dststride,
                                         چوڑائی,
                                         اچائی);
        اكسر;

    حالة SDL_PIXELFORMAT_BGRX8888:
        sdl_sve_bgrx8888_blend_منزل_rgb565(src,
                                         srcstride,
                                         dst,
                                         dststride,
                                         چوڑائی,
                                         اچائی);
        اكسر;

    حالة SDL_PIXELFORMAT_BGRA8888:
        sdl_sve_bgra8888_blend_منزل_rgb565(src,
                                         srcstride,
                                         dst,
                                         dststride,
                                         چوڑائی,
                                         اچائی);
        اكسر;

    افتراضي:
        أكد(false);
        اكسر;
    }
}

#جے_انت /* SD_SVE2_SWIZZLE_H */