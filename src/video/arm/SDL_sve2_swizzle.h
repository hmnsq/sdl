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

#ಆದರೆ !defined(SD_SVE2_SWIZZLE_H) //&& (defined(__ARM_FEATURE_SVE2) && __ARM_FEATURE_SVE2)
#ವ್ಯಾಖ್ಯಾನಿಸು SD_SVE2_SWIZZLE_H

#ಅನ್ತರ್ಭಾವ "SDL_sve2_extension.h"

#ವ್ಯಾಖ್ಯಾನಿಸು sdl_sve_rgb32_stride_impl(ma_sve_chn_iterator, ...)   \
    sdl_sve_stride_loop_pixel(uStride, v_ಬಾಲ_Pred)             \
    {                                                         \
                                                              \
        svuint16x4_t v_ಮೂಲ_Low16x4 = svundef4_u16();         \
        svuint16x4_t v_ಮೂಲ_High16x4 = svundef4_u16();        \
                                                              \
        svuint16x4_t v_ಗುರಿ_Low16x4 = svundef4_u16();         \
        svuint16x4_t v_ಗುರಿ_High16x4 = svundef4_u16();        \
                                                              \
        svld4ub_u16(v_ಬಾಲ_Pred,                                \
                    (uint8_t *)pw_ಮೂಲ,                      \
                    &v_ಮೂಲ_Low16x4,                          \
                    &v_ಮೂಲ_High16x4);                        \
                                                              \
        svld4ub_u16(v_ಬಾಲ_Pred,                                \
                    (uint8_t *)pw_ಗುರಿ,                      \
                    &v_ಗುರಿ_Low16x4,                          \
                    &v_ಗುರಿ_High16x4);                        \
                                                              \
        /* process low half */                                \
        ma_sve_chn_iterator(v_ಮೂಲ_Low16x4, v_ಗುರಿ_Low16x4,   \
                            __VA_ARGS__);                     \
                                                              \
        /* process high half */                               \
        ma_sve_chn_iterator(v_ಮೂಲ_High16x4, v_ಗುರಿ_High16x4, \
                            __VA_ARGS__);                     \
                                                              \
        svst4ub_u16(v_ಬಾಲ_Pred,                                \
                    (uint8_t *)pw_ಗುರಿ,                      \
                    v_ಗುರಿ_Low16x4,                           \
                    v_ಗುರಿ_High16x4);                         \
                                                              \
        pw_ಮೂಲ += sve_iteration_advance;                    \
        pw_ಗುರಿ += sve_iteration_advance;                    \
    }

#ವ್ಯಾಖ್ಯಾನಿಸು sdl_sve_rgb32_no_alpha_stride_impl(                   \
    ma_alpha_idx,                                             \
    ma_sve_chn_iterator,                                      \
    ...)                                                      \
    sdl_sve_stride_loop_pixel(uStride, v_ಬಾಲ_Pred)             \
    {                                                         \
                                                              \
        svuint16x4_t v_ಮೂಲ_Low16x4 = svundef4_u16();         \
        svuint16x4_t v_ಮೂಲ_High16x4 = svundef4_u16();        \
                                                              \
        svuint16x4_t v_ಗುರಿ_Low16x4 = svundef4_u16();         \
        svuint16x4_t v_ಗುರಿ_High16x4 = svundef4_u16();        \
                                                              \
        svld4ub_u16(v_ಬಾಲ_Pred,                                \
                    (uint8_t *)pw_ಮೂಲ,                      \
                    &v_ಮೂಲ_Low16x4,                          \
                    &v_ಮೂಲ_High16x4);                        \
                                                              \
        svld4ub_u16(v_ಬಾಲ_Pred,                                \
                    (uint8_t *)pw_ಗುರಿ,                      \
                    &v_ಗುರಿ_Low16x4,                          \
                    &v_ಗುರಿ_High16x4);                        \
                                                              \
        v_ಮೂಲ_Low16x4 = svset4(v_ಮೂಲ_Low16x4,               \
                                (ma_alpha_idx),               \
                                svdup_u16(0xFF));             \
        v_ಮೂಲ_High16x4 = svset4(v_ಮೂಲ_High16x4,             \
                                 (ma_alpha_idx),              \
                                 svdup_u16(0xFF));            \
                                                              \
        /* process low half */                                \
        ma_sve_chn_iterator(v_ಮೂಲ_Low16x4, v_ಗುರಿ_Low16x4,   \
                            __VA_ARGS__);                     \
                                                              \
        /* process high half */                               \
        ma_sve_chn_iterator(v_ಮೂಲ_High16x4, v_ಗುರಿ_High16x4, \
                            __VA_ARGS__);                     \
                                                              \
        svst4ub_u16(v_ಬಾಲ_Pred,                                \
                    (uint8_t *)pw_ಗುರಿ,                      \
                    v_ಗುರಿ_Low16x4,                           \
                    v_ಗುರಿ_High16x4);                         \
                                                              \
        pw_ಮೂಲ += sve_iteration_advance;                    \
        pw_ಗುರಿ += sve_iteration_advance;                    \
    }

#ವ್ಯಾಖ್ಯಾನಿಸು sdl_sve_rgb32_ಗಮ್ಯ_rgb565_stride_impl(ma_sve_chn_iterator, ...) \
    sdl_sve_stride_loop_pixel(uStride, v_ಬಾಲ_Pred)                     \
    {                                                                 \
                                                                      \
        svuint16x4_t v_ಮೂಲ_Low16x4 = svundef4_u16();                 \
        svuint16x4_t v_ಮೂಲ_High16x4 = svundef4_u16();                \
                                                                      \
        svuint16x3_t v_ಗುರಿ_Low16x3 = svundef3_u16();                 \
        svuint16x3_t v_ಗುರಿ_High16x3 = svundef3_u16();                \
                                                                      \
        svld4ub_u16(v_ಬಾಲ_Pred,                                        \
                    (uint8_t *)pw_ಮೂಲ,                              \
                    &v_ಮೂಲ_Low16x4,                                  \
                    &v_ಮೂಲ_High16x4);                                \
                                                                      \
        svld3rgb565_u16(v_ಬಾಲ_Pred,                                    \
                        phw_ಗುರಿ,                                    \
                        &v_ಗುರಿ_Low16x3,                              \
                        &v_ಗುರಿ_High16x3);                            \
                                                                      \
        ma_sve_chn_iterator(v_ಮೂಲ_Low16x4, v_ಗುರಿ_Low16x3,           \
                            __VA_ARGS__);                             \
                                                                      \
        ma_sve_chn_iterator(v_ಮೂಲ_High16x4, v_ಗುರಿ_High16x3,         \
                            __VA_ARGS__);                             \
                                                                      \
        svst3rgb565_u16(v_ಬಾಲ_Pred,                                    \
                        phw_ಗುರಿ,                                    \
                        v_ಗುರಿ_Low16x3,                               \
                        v_ಗುರಿ_High16x3);                             \
                                                                      \
        pw_ಮೂಲ += sve_iteration_advance;                            \
        phw_ಗುರಿ += sve_iteration_advance;                           \
    }

#ವ್ಯಾಖ್ಯಾನಿಸು sdl_sve_rgb32_no_alpha_ಗಮ್ಯ_rgb565_stride_impl(         \
    ma_alpha_idx,                                             \
    ma_sve_chn_iterator,                                      \
    ...)                                                      \
    sdl_sve_stride_loop_pixel(uStride, v_ಬಾಲ_Pred)             \
    {                                                         \
                                                              \
        svuint16x4_t v_ಮೂಲ_Low16x4 = svundef4_u16();         \
        svuint16x4_t v_ಮೂಲ_High16x4 = svundef4_u16();        \
                                                              \
        svuint16x3_t v_ಗುರಿ_Low16x3 = svundef3_u16();         \
        svuint16x3_t v_ಗುರಿ_High16x3 = svundef3_u16();        \
                                                              \
        svld4ub_u16(v_ಬಾಲ_Pred,                                \
                    (uint8_t *)pw_ಮೂಲ,                      \
                    &v_ಮೂಲ_Low16x4,                          \
                    &v_ಮೂಲ_High16x4);                        \
                                                              \
        v_ಮೂಲ_Low16x4 = svset4(v_ಮೂಲ_Low16x4,               \
                                (ma_alpha_idx),               \
                                svdup_u16(0xFF));             \
        v_ಮೂಲ_High16x4 = svset4(v_ಮೂಲ_High16x4,             \
                                 (ma_alpha_idx),              \
                                 svdup_u16(0xFF));            \
                                                              \
        svld3rgb565_u16(v_ಬಾಲ_Pred,                            \
                        phw_ಗುರಿ,                            \
                        &v_ಗುರಿ_Low16x3,                      \
                        &v_ಗುರಿ_High16x3);                    \
                                                              \
        ma_sve_chn_iterator(v_ಮೂಲ_Low16x4, v_ಗುರಿ_Low16x3,   \
                            __VA_ARGS__);                     \
                                                              \
        ma_sve_chn_iterator(v_ಮೂಲ_High16x4, v_ಗುರಿ_High16x3, \
                            __VA_ARGS__);                     \
                                                              \
        svst3rgb565_u16(v_ಬಾಲ_Pred,                            \
                        phw_ಗುರಿ,                            \
                        v_ಗುರಿ_Low16x3,                       \
                        v_ಗುರಿ_High16x3);                     \
                                                              \
        pw_ಮೂಲ += sve_iteration_advance;                    \
        phw_ಗುರಿ += sve_iteration_advance;                   \
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ sdl_sve_rgb32_blend_op_fill_alpha
#ವ್ಯಾಖ್ಯಾನಿಸು sdl_sve_rgb32_blend_op_fill_alpha(ma_alpha_chn_idx)
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ sdl_sve_rgb32_blend_op_copy_alpha
#ವ್ಯಾಖ್ಯಾನಿಸು sdl_sve_rgb32_blend_op_copy_alpha(ma_alpha_chn_idx)
#ಆದರೆ_ಅಂತ್ಯ

/*
 * Source: ACCC and CCCA
 */
SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_accc_stride_blend_ಗಮ್ಯ_accc_fill_alpha(
    uint32_t *SDL_RESTRICT pw_ಮೂಲ,
    uint32_t *SDL_RESTRICT pw_ಗುರಿ,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn,

                              sdl_sve_rgb32_blend_op_fill_alpha(3);

    );
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_accc_stride_blend_ಗಮ್ಯ_accc_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ಮೂಲ,
    uint32_t *SDL_RESTRICT pw_ಗುರಿ,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn,
                              sdl_sve_rgb32_blend_op_copy_alpha(3););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_ccca_stride_blend_ಗಮ್ಯ_ccca_fill_alpha(
    uint32_t *SDL_RESTRICT pw_ಮೂಲ,
    uint32_t *SDL_RESTRICT pw_ಗುರಿ,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn,
                              sdl_sve_rgb32_blend_op_fill_alpha(0););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_ccca_stride_blend_ಗಮ್ಯ_ccca_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ಮೂಲ,
    uint32_t *SDL_RESTRICT pw_ಗುರಿ,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn,

                              sdl_sve_rgb32_blend_op_copy_alpha(0);

    );
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_accc_blend_ಗಮ್ಯ_accc_fill_alpha(
    uint8_t *SDL_RESTRICT pch_ಮೂಲ,
    size_t u_ಮೂಲ_Stride,
    uint8_t *SDL_RESTRICT pch_ಗುರಿ,
    size_t u_ಗುರಿ_Stride,
    ಪೂರ್ಣಾಂಕ n_ಅಗಲ,
    ಪೂರ್ಣಾಂಕ n_ಎತ್ತರ)
{
    ಆಗ (n_ಎತ್ತರ--) {

        sdl_sve_accc_stride_blend_ಗಮ್ಯ_accc_fill_alpha(
            (uint32_t *)pch_ಮೂಲ,
            (uint32_t *)pch_ಗುರಿ,
            n_ಅಗಲ);

        pch_ಮೂಲ += u_ಮೂಲ_Stride;
        pch_ಗುರಿ += u_ಗುರಿ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_accc_blend_ಗಮ್ಯ_accc_copy_alpha(
    uint8_t *SDL_RESTRICT pch_ಮೂಲ,
    size_t u_ಮೂಲ_Stride,
    uint8_t *SDL_RESTRICT pch_ಗುರಿ,
    size_t u_ಗುರಿ_Stride,
    ಪೂರ್ಣಾಂಕ n_ಅಗಲ,
    ಪೂರ್ಣಾಂಕ n_ಎತ್ತರ)
{
    ಆಗ (n_ಎತ್ತರ--) {

        sdl_sve_accc_stride_blend_ಗಮ್ಯ_accc_copy_alpha(
            (uint32_t *)pch_ಮೂಲ,
            (uint32_t *)pch_ಗುರಿ,
            n_ಅಗಲ);

        pch_ಮೂಲ += u_ಮೂಲ_Stride;
        pch_ಗುರಿ += u_ಗುರಿ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_ccca_blend_ಗಮ್ಯ_ccca_fill_alpha(
    uint8_t *SDL_RESTRICT pch_ಮೂಲ,
    size_t u_ಮೂಲ_Stride,
    uint8_t *SDL_RESTRICT pch_ಗುರಿ,
    size_t u_ಗುರಿ_Stride,
    ಪೂರ್ಣಾಂಕ n_ಅಗಲ,
    ಪೂರ್ಣಾಂಕ n_ಎತ್ತರ)
{
    ಆಗ (n_ಎತ್ತರ--) {

        sdl_sve_ccca_stride_blend_ಗಮ್ಯ_ccca_fill_alpha(
            (uint32_t *)pch_ಮೂಲ,
            (uint32_t *)pch_ಗುರಿ,
            n_ಅಗಲ);

        pch_ಮೂಲ += u_ಮೂಲ_Stride;
        pch_ಗುರಿ += u_ಗುರಿ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_ccca_blend_ಗಮ್ಯ_ccca_copy_alpha(
    uint8_t *SDL_RESTRICT pch_ಮೂಲ,
    size_t u_ಮೂಲ_Stride,
    uint8_t *SDL_RESTRICT pch_ಗುರಿ,
    size_t u_ಗುರಿ_Stride,
    ಪೂರ್ಣಾಂಕ n_ಅಗಲ,
    ಪೂರ್ಣಾಂಕ n_ಎತ್ತರ)
{
    ಆಗ (n_ಎತ್ತರ--) {

        sdl_sve_ccca_stride_blend_ಗಮ್ಯ_ccca_copy_alpha(
            (uint32_t *)pch_ಮೂಲ,
            (uint32_t *)pch_ಗುರಿ,
            n_ಅಗಲ);

        pch_ಮೂಲ += u_ಮೂಲ_Stride;
        pch_ಗುರಿ += u_ಗುರಿ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_a123_stride_blend_ಗಮ್ಯ_321a_fill_alpha(
    uint32_t *SDL_RESTRICT pw_ಮೂಲ,
    uint32_t *SDL_RESTRICT pw_ಗುರಿ,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn_src_dst_rev,
                              sdl_sve_rgb32_blend_op_fill_alpha(3);

    );
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_a123_stride_blend_ಗಮ್ಯ_321a_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ಮೂಲ,
    uint32_t *SDL_RESTRICT pw_ಗುರಿ,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn_src_dst_rev,
                              sdl_sve_rgb32_blend_op_copy_alpha(3);

    );
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_a123_blend_ಗಮ್ಯ_321a_fill_alpha(uint8_t *SDL_RESTRICT pch_ಮೂಲ,
                                                         size_t u_ಮೂಲ_Stride,
                                                         uint8_t *SDL_RESTRICT pch_ಗುರಿ,
                                                         size_t u_ಗುರಿ_Stride,
                                                         ಪೂರ್ಣಾಂಕ n_ಅಗಲ,
                                                         ಪೂರ್ಣಾಂಕ n_ಎತ್ತರ)
{
    ಆಗ (n_ಎತ್ತರ--) {

        sdl_sve_a123_stride_blend_ಗಮ್ಯ_321a_fill_alpha((uint32_t *)pch_ಮೂಲ,
                                                     (uint32_t *)pch_ಗುರಿ,
                                                     n_ಅಗಲ);

        pch_ಮೂಲ += u_ಮೂಲ_Stride;
        pch_ಗುರಿ += u_ಗುರಿ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_a123_blend_ಗಮ್ಯ_321a_copy_alpha(uint8_t *SDL_RESTRICT pch_ಮೂಲ,
                                                         size_t u_ಮೂಲ_Stride,
                                                         uint8_t *SDL_RESTRICT pch_ಗುರಿ,
                                                         size_t u_ಗುರಿ_Stride,
                                                         ಪೂರ್ಣಾಂಕ n_ಅಗಲ,
                                                         ಪೂರ್ಣಾಂಕ n_ಎತ್ತರ)
{
    ಆಗ (n_ಎತ್ತರ--) {

        sdl_sve_a123_stride_blend_ಗಮ್ಯ_321a_copy_alpha((uint32_t *)pch_ಮೂಲ,
                                                     (uint32_t *)pch_ಗುರಿ,
                                                     n_ಅಗಲ);

        pch_ಮೂಲ += u_ಮೂಲ_Stride;
        pch_ಗುರಿ += u_ಗುರಿ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_123a_stride_blend_ಗಮ್ಯ_a321_fill_alpha(
    uint32_t *SDL_RESTRICT pw_ಮೂಲ,
    uint32_t *SDL_RESTRICT pw_ಗುರಿ,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn_src_dst_rev,
                              sdl_sve_rgb32_blend_op_fill_alpha(0);

    );
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_123a_stride_blend_ಗಮ್ಯ_a321_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ಮೂಲ,
    uint32_t *SDL_RESTRICT pw_ಗುರಿ,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn_src_dst_rev,
                              sdl_sve_rgb32_blend_op_copy_alpha(0);

    );
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_123a_blend_ಗಮ್ಯ_a321_fill_alpha(uint8_t *SDL_RESTRICT pch_ಮೂಲ,
                                                         size_t u_ಮೂಲ_Stride,
                                                         uint8_t *SDL_RESTRICT pch_ಗುರಿ,
                                                         size_t u_ಗುರಿ_Stride,
                                                         ಪೂರ್ಣಾಂಕ n_ಅಗಲ,
                                                         ಪೂರ್ಣಾಂಕ n_ಎತ್ತರ)
{
    ಆಗ (n_ಎತ್ತರ--) {

        sdl_sve_123a_stride_blend_ಗಮ್ಯ_a321_fill_alpha((uint32_t *)pch_ಮೂಲ,
                                                     (uint32_t *)pch_ಗುರಿ,
                                                     n_ಅಗಲ);

        pch_ಮೂಲ += u_ಮೂಲ_Stride;
        pch_ಗುರಿ += u_ಗುರಿ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_123a_blend_ಗಮ್ಯ_a321_copy_alpha(uint8_t *SDL_RESTRICT pch_ಮೂಲ,
                                                         size_t u_ಮೂಲ_Stride,
                                                         uint8_t *SDL_RESTRICT pch_ಗುರಿ,
                                                         size_t u_ಗುರಿ_Stride,
                                                         ಪೂರ್ಣಾಂಕ n_ಅಗಲ,
                                                         ಪೂರ್ಣಾಂಕ n_ಎತ್ತರ)
{
    ಆಗ (n_ಎತ್ತರ--) {

        sdl_sve_123a_stride_blend_ಗಮ್ಯ_a321_copy_alpha((uint32_t *)pch_ಮೂಲ,
                                                     (uint32_t *)pch_ಗುರಿ,
                                                     n_ಅಗಲ);

        pch_ಮೂಲ += u_ಮೂಲ_Stride;
        pch_ಗುರಿ += u_ಗುರಿ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_accc_stride_blend_ಗಮ್ಯ_ccca_fill_alpha(
    uint32_t *SDL_RESTRICT pw_ಮೂಲ,
    uint32_t *SDL_RESTRICT pw_ಗುರಿ,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn_accc_ccca,
                              sdl_sve_rgb32_blend_op_fill_alpha(3);

    );
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_accc_stride_blend_ಗಮ್ಯ_ccca_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ಮೂಲ,
    uint32_t *SDL_RESTRICT pw_ಗುರಿ,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn_accc_ccca,
                              sdl_sve_rgb32_blend_op_copy_alpha(3);

    );
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_accc_blend_ಗಮ್ಯ_ccca_fill_alpha(uint8_t *SDL_RESTRICT pch_ಮೂಲ,
                                                         size_t u_ಮೂಲ_Stride,
                                                         uint8_t *SDL_RESTRICT pch_ಗುರಿ,
                                                         size_t u_ಗುರಿ_Stride,
                                                         ಪೂರ್ಣಾಂಕ n_ಅಗಲ,
                                                         ಪೂರ್ಣಾಂಕ n_ಎತ್ತರ)
{
    ಆಗ (n_ಎತ್ತರ--) {

        sdl_sve_accc_stride_blend_ಗಮ್ಯ_ccca_fill_alpha((uint32_t *)pch_ಮೂಲ,
                                                     (uint32_t *)pch_ಗುರಿ,
                                                     n_ಅಗಲ);

        pch_ಮೂಲ += u_ಮೂಲ_Stride;
        pch_ಗುರಿ += u_ಗುರಿ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_accc_blend_ಗಮ್ಯ_ccca_copy_alpha(uint8_t *SDL_RESTRICT pch_ಮೂಲ,
                                                         size_t u_ಮೂಲ_Stride,
                                                         uint8_t *SDL_RESTRICT pch_ಗುರಿ,
                                                         size_t u_ಗುರಿ_Stride,
                                                         ಪೂರ್ಣಾಂಕ n_ಅಗಲ,
                                                         ಪೂರ್ಣಾಂಕ n_ಎತ್ತರ)
{
    ಆಗ (n_ಎತ್ತರ--) {

        sdl_sve_accc_stride_blend_ಗಮ್ಯ_ccca_copy_alpha((uint32_t *)pch_ಮೂಲ,
                                                     (uint32_t *)pch_ಗುರಿ,
                                                     n_ಅಗಲ);

        pch_ಮೂಲ += u_ಮೂಲ_Stride;
        pch_ಗುರಿ += u_ಗುರಿ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_ccca_stride_blend_ಗಮ್ಯ_accc_fill_alpha(
    uint32_t *SDL_RESTRICT pw_ಮೂಲ,
    uint32_t *SDL_RESTRICT pw_ಗುರಿ,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn_ccca_accc,
                              sdl_sve_rgb32_blend_op_fill_alpha(0);

    );
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_ccca_stride_blend_ಗಮ್ಯ_accc_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ಮೂಲ,
    uint32_t *SDL_RESTRICT pw_ಗುರಿ,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn_ccca_accc,
                              sdl_sve_rgb32_blend_op_copy_alpha(0););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_ccca_blend_ಗಮ್ಯ_accc_fill_alpha(uint8_t *SDL_RESTRICT pch_ಮೂಲ,
                                                         size_t u_ಮೂಲ_Stride,
                                                         uint8_t *SDL_RESTRICT pch_ಗುರಿ,
                                                         size_t u_ಗುರಿ_Stride,
                                                         ಪೂರ್ಣಾಂಕ n_ಅಗಲ,
                                                         ಪೂರ್ಣಾಂಕ n_ಎತ್ತರ)
{
    ಆಗ (n_ಎತ್ತರ--) {

        sdl_sve_ccca_stride_blend_ಗಮ್ಯ_accc_fill_alpha((uint32_t *)pch_ಮೂಲ,
                                                     (uint32_t *)pch_ಗುರಿ,
                                                     n_ಅಗಲ);

        pch_ಮೂಲ += u_ಮೂಲ_Stride;
        pch_ಗುರಿ += u_ಗುರಿ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_ccca_blend_ಗಮ್ಯ_accc_copy_alpha(uint8_t *SDL_RESTRICT pch_ಮೂಲ,
                                                         size_t u_ಮೂಲ_Stride,
                                                         uint8_t *SDL_RESTRICT pch_ಗುರಿ,
                                                         size_t u_ಗುರಿ_Stride,
                                                         ಪೂರ್ಣಾಂಕ n_ಅಗಲ,
                                                         ಪೂರ್ಣಾಂಕ n_ಎತ್ತರ)
{
    ಆಗ (n_ಎತ್ತರ--) {

        sdl_sve_ccca_stride_blend_ಗಮ್ಯ_accc_copy_alpha((uint32_t *)pch_ಮೂಲ,
                                                     (uint32_t *)pch_ಗುರಿ,
                                                     n_ಅಗಲ);

        pch_ಮೂಲ += u_ಮೂಲ_Stride;
        pch_ಗುರಿ += u_ಗುರಿ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_a123_stride_blend_ಗಮ್ಯ_a321_fill_alpha(
    uint32_t *SDL_RESTRICT pw_ಮೂಲ,
    uint32_t *SDL_RESTRICT pw_ಗುರಿ,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn_a123_a321,
                              sdl_sve_rgb32_blend_op_fill_alpha(3););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_a123_stride_blend_ಗಮ್ಯ_a321_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ಮೂಲ,
    uint32_t *SDL_RESTRICT pw_ಗುರಿ,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn_a123_a321,
                              sdl_sve_rgb32_blend_op_copy_alpha(3););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_a123_blend_ಗಮ್ಯ_a321_fill_alpha(uint8_t *SDL_RESTRICT pch_ಮೂಲ,
                                                         size_t u_ಮೂಲ_Stride,
                                                         uint8_t *SDL_RESTRICT pch_ಗುರಿ,
                                                         size_t u_ಗುರಿ_Stride,
                                                         ಪೂರ್ಣಾಂಕ n_ಅಗಲ,
                                                         ಪೂರ್ಣಾಂಕ n_ಎತ್ತರ)
{
    ಆಗ (n_ಎತ್ತರ--) {

        sdl_sve_a123_stride_blend_ಗಮ್ಯ_a321_fill_alpha((uint32_t *)pch_ಮೂಲ,
                                                     (uint32_t *)pch_ಗುರಿ,
                                                     n_ಅಗಲ);

        pch_ಮೂಲ += u_ಮೂಲ_Stride;
        pch_ಗುರಿ += u_ಗುರಿ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_a123_blend_ಗಮ್ಯ_a321_copy_alpha(uint8_t *SDL_RESTRICT pch_ಮೂಲ,
                                                         size_t u_ಮೂಲ_Stride,
                                                         uint8_t *SDL_RESTRICT pch_ಗುರಿ,
                                                         size_t u_ಗುರಿ_Stride,
                                                         ಪೂರ್ಣಾಂಕ n_ಅಗಲ,
                                                         ಪೂರ್ಣಾಂಕ n_ಎತ್ತರ)
{
    ಆಗ (n_ಎತ್ತರ--) {

        sdl_sve_a123_stride_blend_ಗಮ್ಯ_a321_copy_alpha((uint32_t *)pch_ಮೂಲ,
                                                     (uint32_t *)pch_ಗುರಿ,
                                                     n_ಅಗಲ);

        pch_ಮೂಲ += u_ಮೂಲ_Stride;
        pch_ಗುರಿ += u_ಗುರಿ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_123a_stride_blend_ಗಮ್ಯ_321a_fill_alpha(
    uint32_t *SDL_RESTRICT pw_ಮೂಲ,
    uint32_t *SDL_RESTRICT pw_ಗುರಿ,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn_123a_321a,
                              sdl_sve_rgb32_blend_op_fill_alpha(0););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_123a_stride_blend_ಗಮ್ಯ_321a_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ಮೂಲ,
    uint32_t *SDL_RESTRICT pw_ಗುರಿ,
    size_t uStride)
{
    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn_123a_321a,
                              sdl_sve_rgb32_blend_op_copy_alpha(0););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_123a_blend_ಗಮ್ಯ_321a_fill_alpha(uint8_t *SDL_RESTRICT pch_ಮೂಲ,
                                                         size_t u_ಮೂಲ_Stride,
                                                         uint8_t *SDL_RESTRICT pch_ಗುರಿ,
                                                         size_t u_ಗುರಿ_Stride,
                                                         ಪೂರ್ಣಾಂಕ n_ಅಗಲ,
                                                         ಪೂರ್ಣಾಂಕ n_ಎತ್ತರ)
{
    ಆಗ (n_ಎತ್ತರ--) {

        sdl_sve_123a_stride_blend_ಗಮ್ಯ_321a_fill_alpha((uint32_t *)pch_ಮೂಲ,
                                                     (uint32_t *)pch_ಗುರಿ,
                                                     n_ಅಗಲ);

        pch_ಮೂಲ += u_ಮೂಲ_Stride;
        pch_ಗುರಿ += u_ಗುರಿ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_123a_blend_ಗಮ್ಯ_321a_copy_alpha(uint8_t *SDL_RESTRICT pch_ಮೂಲ,
                                                         size_t u_ಮೂಲ_Stride,
                                                         uint8_t *SDL_RESTRICT pch_ಗುರಿ,
                                                         size_t u_ಗುರಿ_Stride,
                                                         ಪೂರ್ಣಾಂಕ n_ಅಗಲ,
                                                         ಪೂರ್ಣಾಂಕ n_ಎತ್ತರ)
{
    ಆಗ (n_ಎತ್ತರ--) {

        sdl_sve_123a_stride_blend_ಗಮ್ಯ_321a_copy_alpha((uint32_t *)pch_ಮೂಲ,
                                                     (uint32_t *)pch_ಗುರಿ,
                                                     n_ಅಗಲ);

        pch_ಮೂಲ += u_ಮೂಲ_Stride;
        pch_ಗುರಿ += u_ಗುರಿ_Stride;
    }
}

/*
 * Source: XCCC and CCCX
 */

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_xccc_stride_blend_ಗಮ್ಯ_accc_fill_alpha(
    uint32_t *SDL_RESTRICT pw_ಮೂಲ,
    uint32_t *SDL_RESTRICT pw_ಗುರಿ,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(3,
                                       sdl_sve_pixel_u16x4_foreach_chn,
                                       sdl_sve_rgb32_blend_op_fill_alpha(3););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_xccc_stride_blend_ಗಮ್ಯ_accc_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ಮೂಲ,
    uint32_t *SDL_RESTRICT pw_ಗುರಿ,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(3,
                                       sdl_sve_pixel_u16x4_foreach_chn,
                                       sdl_sve_rgb32_blend_op_copy_alpha(3););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_cccx_stride_blend_ಗಮ್ಯ_ccca_fill_alpha(
    uint32_t *SDL_RESTRICT pw_ಮೂಲ,
    uint32_t *SDL_RESTRICT pw_ಗುರಿ,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(0,
                                       sdl_sve_pixel_u16x4_foreach_chn,
                                       sdl_sve_rgb32_blend_op_fill_alpha(0);

    );
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_cccx_stride_blend_ಗಮ್ಯ_ccca_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ಮೂಲ,
    uint32_t *SDL_RESTRICT pw_ಗುರಿ,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(0,
                                       sdl_sve_pixel_u16x4_foreach_chn,
                                       sdl_sve_rgb32_blend_op_copy_alpha(0););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_xccc_blend_ಗಮ್ಯ_accc_fill_alpha(
    uint8_t *SDL_RESTRICT pch_ಮೂಲ,
    size_t u_ಮೂಲ_Stride,
    uint8_t *SDL_RESTRICT pch_ಗುರಿ,
    size_t u_ಗುರಿ_Stride,
    ಪೂರ್ಣಾಂಕ n_ಅಗಲ,
    ಪೂರ್ಣಾಂಕ n_ಎತ್ತರ)
{
    ಆಗ (n_ಎತ್ತರ--) {

        sdl_sve_xccc_stride_blend_ಗಮ್ಯ_accc_fill_alpha(
            (uint32_t *)pch_ಮೂಲ,
            (uint32_t *)pch_ಗುರಿ,
            n_ಅಗಲ);

        pch_ಮೂಲ += u_ಮೂಲ_Stride;
        pch_ಗುರಿ += u_ಗುರಿ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_xccc_blend_ಗಮ್ಯ_accc_copy_alpha(
    uint8_t *SDL_RESTRICT pch_ಮೂಲ,
    size_t u_ಮೂಲ_Stride,
    uint8_t *SDL_RESTRICT pch_ಗುರಿ,
    size_t u_ಗುರಿ_Stride,
    ಪೂರ್ಣಾಂಕ n_ಅಗಲ,
    ಪೂರ್ಣಾಂಕ n_ಎತ್ತರ)
{
    ಆಗ (n_ಎತ್ತರ--) {

        sdl_sve_xccc_stride_blend_ಗಮ್ಯ_accc_copy_alpha(
            (uint32_t *)pch_ಮೂಲ,
            (uint32_t *)pch_ಗುರಿ,
            n_ಅಗಲ);

        pch_ಮೂಲ += u_ಮೂಲ_Stride;
        pch_ಗುರಿ += u_ಗುರಿ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_cccx_blend_ಗಮ್ಯ_ccca_fill_alpha(
    uint8_t *SDL_RESTRICT pch_ಮೂಲ,
    size_t u_ಮೂಲ_Stride,
    uint8_t *SDL_RESTRICT pch_ಗುರಿ,
    size_t u_ಗುರಿ_Stride,
    ಪೂರ್ಣಾಂಕ n_ಅಗಲ,
    ಪೂರ್ಣಾಂಕ n_ಎತ್ತರ)
{
    ಆಗ (n_ಎತ್ತರ--) {

        sdl_sve_cccx_stride_blend_ಗಮ್ಯ_ccca_fill_alpha(
            (uint32_t *)pch_ಮೂಲ,
            (uint32_t *)pch_ಗುರಿ,
            n_ಅಗಲ);

        pch_ಮೂಲ += u_ಮೂಲ_Stride;
        pch_ಗುರಿ += u_ಗುರಿ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_cccx_blend_ಗಮ್ಯ_ccca_copy_alpha(
    uint8_t *SDL_RESTRICT pch_ಮೂಲ,
    size_t u_ಮೂಲ_Stride,
    uint8_t *SDL_RESTRICT pch_ಗುರಿ,
    size_t u_ಗುರಿ_Stride,
    ಪೂರ್ಣಾಂಕ n_ಅಗಲ,
    ಪೂರ್ಣಾಂಕ n_ಎತ್ತರ)
{
    ಆಗ (n_ಎತ್ತರ--) {

        sdl_sve_cccx_stride_blend_ಗಮ್ಯ_ccca_copy_alpha(
            (uint32_t *)pch_ಮೂಲ,
            (uint32_t *)pch_ಗುರಿ,
            n_ಅಗಲ);

        pch_ಮೂಲ += u_ಮೂಲ_Stride;
        pch_ಗುರಿ += u_ಗುರಿ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_x123_stride_blend_ಗಮ್ಯ_321a_fill_alpha(
    uint32_t *SDL_RESTRICT pw_ಮೂಲ,
    uint32_t *SDL_RESTRICT pw_ಗುರಿ,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(3,
                                       sdl_sve_pixel_u16x4_foreach_chn_src_dst_rev,
                                       sdl_sve_rgb32_blend_op_fill_alpha(3););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_x123_stride_blend_ಗಮ್ಯ_321a_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ಮೂಲ,
    uint32_t *SDL_RESTRICT pw_ಗುರಿ,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(3,
                                       sdl_sve_pixel_u16x4_foreach_chn_src_dst_rev,
                                       sdl_sve_rgb32_blend_op_copy_alpha(3););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_x123_blend_ಗಮ್ಯ_321a_fill_alpha(uint8_t *SDL_RESTRICT pch_ಮೂಲ,
                                                         size_t u_ಮೂಲ_Stride,
                                                         uint8_t *SDL_RESTRICT pch_ಗುರಿ,
                                                         size_t u_ಗುರಿ_Stride,
                                                         ಪೂರ್ಣಾಂಕ n_ಅಗಲ,
                                                         ಪೂರ್ಣಾಂಕ n_ಎತ್ತರ)
{
    ಆಗ (n_ಎತ್ತರ--) {

        sdl_sve_x123_stride_blend_ಗಮ್ಯ_321a_fill_alpha((uint32_t *)pch_ಮೂಲ,
                                                     (uint32_t *)pch_ಗುರಿ,
                                                     n_ಅಗಲ);

        pch_ಮೂಲ += u_ಮೂಲ_Stride;
        pch_ಗುರಿ += u_ಗುರಿ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_x123_blend_ಗಮ್ಯ_321a_copy_alpha(uint8_t *SDL_RESTRICT pch_ಮೂಲ,
                                                         size_t u_ಮೂಲ_Stride,
                                                         uint8_t *SDL_RESTRICT pch_ಗುರಿ,
                                                         size_t u_ಗುರಿ_Stride,
                                                         ಪೂರ್ಣಾಂಕ n_ಅಗಲ,
                                                         ಪೂರ್ಣಾಂಕ n_ಎತ್ತರ)
{
    ಆಗ (n_ಎತ್ತರ--) {

        sdl_sve_x123_stride_blend_ಗಮ್ಯ_321a_copy_alpha((uint32_t *)pch_ಮೂಲ,
                                                     (uint32_t *)pch_ಗುರಿ,
                                                     n_ಅಗಲ);

        pch_ಮೂಲ += u_ಮೂಲ_Stride;
        pch_ಗುರಿ += u_ಗುರಿ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_123x_stride_blend_ಗಮ್ಯ_a321_fill_alpha(
    uint32_t *SDL_RESTRICT pw_ಮೂಲ,
    uint32_t *SDL_RESTRICT pw_ಗುರಿ,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(0,
                                       sdl_sve_pixel_u16x4_foreach_chn_src_dst_rev,
                                       sdl_sve_rgb32_blend_op_fill_alpha(0););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_123x_stride_blend_ಗಮ್ಯ_a321_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ಮೂಲ,
    uint32_t *SDL_RESTRICT pw_ಗುರಿ,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(0,
                                       sdl_sve_pixel_u16x4_foreach_chn_src_dst_rev,
                                       sdl_sve_rgb32_blend_op_copy_alpha(0););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_123x_blend_ಗಮ್ಯ_a321_fill_alpha(uint8_t *SDL_RESTRICT pch_ಮೂಲ,
                                                         size_t u_ಮೂಲ_Stride,
                                                         uint8_t *SDL_RESTRICT pch_ಗುರಿ,
                                                         size_t u_ಗುರಿ_Stride,
                                                         ಪೂರ್ಣಾಂಕ n_ಅಗಲ,
                                                         ಪೂರ್ಣಾಂಕ n_ಎತ್ತರ)
{
    ಆಗ (n_ಎತ್ತರ--) {

        sdl_sve_123x_stride_blend_ಗಮ್ಯ_a321_fill_alpha((uint32_t *)pch_ಮೂಲ,
                                                     (uint32_t *)pch_ಗುರಿ,
                                                     n_ಅಗಲ);

        pch_ಮೂಲ += u_ಮೂಲ_Stride;
        pch_ಗುರಿ += u_ಗುರಿ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_123x_blend_ಗಮ್ಯ_a321_copy_alpha(uint8_t *SDL_RESTRICT pch_ಮೂಲ,
                                                         size_t u_ಮೂಲ_Stride,
                                                         uint8_t *SDL_RESTRICT pch_ಗುರಿ,
                                                         size_t u_ಗುರಿ_Stride,
                                                         ಪೂರ್ಣಾಂಕ n_ಅಗಲ,
                                                         ಪೂರ್ಣಾಂಕ n_ಎತ್ತರ)
{
    ಆಗ (n_ಎತ್ತರ--) {

        sdl_sve_123x_stride_blend_ಗಮ್ಯ_a321_copy_alpha((uint32_t *)pch_ಮೂಲ,
                                                     (uint32_t *)pch_ಗುರಿ,
                                                     n_ಅಗಲ);

        pch_ಮೂಲ += u_ಮೂಲ_Stride;
        pch_ಗುರಿ += u_ಗುರಿ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_xccc_stride_blend_ಗಮ್ಯ_ccca_fill_alpha(
    uint32_t *SDL_RESTRICT pw_ಮೂಲ,
    uint32_t *SDL_RESTRICT pw_ಗುರಿ,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(3,
                                       sdl_sve_pixel_u16x4_foreach_chn_accc_ccca,
                                       sdl_sve_rgb32_blend_op_fill_alpha(3););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_xccc_stride_blend_ಗಮ್ಯ_ccca_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ಮೂಲ,
    uint32_t *SDL_RESTRICT pw_ಗುರಿ,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(3,
                                       sdl_sve_pixel_u16x4_foreach_chn_accc_ccca,
                                       sdl_sve_rgb32_blend_op_copy_alpha(3););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_xccc_blend_ಗಮ್ಯ_ccca_fill_alpha(uint8_t *SDL_RESTRICT pch_ಮೂಲ,
                                                         size_t u_ಮೂಲ_Stride,
                                                         uint8_t *SDL_RESTRICT pch_ಗುರಿ,
                                                         size_t u_ಗುರಿ_Stride,
                                                         ಪೂರ್ಣಾಂಕ n_ಅಗಲ,
                                                         ಪೂರ್ಣಾಂಕ n_ಎತ್ತರ)
{
    ಆಗ (n_ಎತ್ತರ--) {

        sdl_sve_xccc_stride_blend_ಗಮ್ಯ_ccca_fill_alpha((uint32_t *)pch_ಮೂಲ,
                                                     (uint32_t *)pch_ಗುರಿ,
                                                     n_ಅಗಲ);

        pch_ಮೂಲ += u_ಮೂಲ_Stride;
        pch_ಗುರಿ += u_ಗುರಿ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_xccc_blend_ಗಮ್ಯ_ccca_copy_alpha(uint8_t *SDL_RESTRICT pch_ಮೂಲ,
                                                         size_t u_ಮೂಲ_Stride,
                                                         uint8_t *SDL_RESTRICT pch_ಗುರಿ,
                                                         size_t u_ಗುರಿ_Stride,
                                                         ಪೂರ್ಣಾಂಕ n_ಅಗಲ,
                                                         ಪೂರ್ಣಾಂಕ n_ಎತ್ತರ)
{
    ಆಗ (n_ಎತ್ತರ--) {

        sdl_sve_xccc_stride_blend_ಗಮ್ಯ_ccca_copy_alpha((uint32_t *)pch_ಮೂಲ,
                                                     (uint32_t *)pch_ಗುರಿ,
                                                     n_ಅಗಲ);

        pch_ಮೂಲ += u_ಮೂಲ_Stride;
        pch_ಗುರಿ += u_ಗುರಿ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_cccx_stride_blend_ಗಮ್ಯ_accc_fill_alpha(
    uint32_t *SDL_RESTRICT pw_ಮೂಲ,
    uint32_t *SDL_RESTRICT pw_ಗುರಿ,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(0,
                                       sdl_sve_pixel_u16x4_foreach_chn_ccca_accc,
                                       sdl_sve_rgb32_blend_op_fill_alpha(0););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_cccx_stride_blend_ಗಮ್ಯ_accc_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ಮೂಲ,
    uint32_t *SDL_RESTRICT pw_ಗುರಿ,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(0,
                                       sdl_sve_pixel_u16x4_foreach_chn_ccca_accc,
                                       sdl_sve_rgb32_blend_op_copy_alpha(0););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_cccx_blend_ಗಮ್ಯ_accc_fill_alpha(uint8_t *SDL_RESTRICT pch_ಮೂಲ,
                                                         size_t u_ಮೂಲ_Stride,
                                                         uint8_t *SDL_RESTRICT pch_ಗುರಿ,
                                                         size_t u_ಗುರಿ_Stride,
                                                         ಪೂರ್ಣಾಂಕ n_ಅಗಲ,
                                                         ಪೂರ್ಣಾಂಕ n_ಎತ್ತರ)
{
    ಆಗ (n_ಎತ್ತರ--) {

        sdl_sve_cccx_stride_blend_ಗಮ್ಯ_accc_fill_alpha((uint32_t *)pch_ಮೂಲ,
                                                     (uint32_t *)pch_ಗುರಿ,
                                                     n_ಅಗಲ);

        pch_ಮೂಲ += u_ಮೂಲ_Stride;
        pch_ಗುರಿ += u_ಗುರಿ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_cccx_blend_ಗಮ್ಯ_accc_copy_alpha(uint8_t *SDL_RESTRICT pch_ಮೂಲ,
                                                         size_t u_ಮೂಲ_Stride,
                                                         uint8_t *SDL_RESTRICT pch_ಗುರಿ,
                                                         size_t u_ಗುರಿ_Stride,
                                                         ಪೂರ್ಣಾಂಕ n_ಅಗಲ,
                                                         ಪೂರ್ಣಾಂಕ n_ಎತ್ತರ)
{
    ಆಗ (n_ಎತ್ತರ--) {

        sdl_sve_cccx_stride_blend_ಗಮ್ಯ_accc_copy_alpha((uint32_t *)pch_ಮೂಲ,
                                                     (uint32_t *)pch_ಗುರಿ,
                                                     n_ಅಗಲ);

        pch_ಮೂಲ += u_ಮೂಲ_Stride;
        pch_ಗುರಿ += u_ಗುರಿ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_x123_stride_blend_ಗಮ್ಯ_a321_fill_alpha(
    uint32_t *SDL_RESTRICT pw_ಮೂಲ,
    uint32_t *SDL_RESTRICT pw_ಗುರಿ,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(3,
                                       sdl_sve_pixel_u16x4_foreach_chn_a123_a321,
                                       sdl_sve_rgb32_blend_op_fill_alpha(3););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_x123_stride_blend_ಗಮ್ಯ_a321_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ಮೂಲ,
    uint32_t *SDL_RESTRICT pw_ಗುರಿ,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(3,
                                       sdl_sve_pixel_u16x4_foreach_chn_a123_a321,
                                       sdl_sve_rgb32_blend_op_copy_alpha(3););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_x123_blend_ಗಮ್ಯ_a321_fill_alpha(uint8_t *SDL_RESTRICT pch_ಮೂಲ,
                                                         size_t u_ಮೂಲ_Stride,
                                                         uint8_t *SDL_RESTRICT pch_ಗುರಿ,
                                                         size_t u_ಗುರಿ_Stride,
                                                         ಪೂರ್ಣಾಂಕ n_ಅಗಲ,
                                                         ಪೂರ್ಣಾಂಕ n_ಎತ್ತರ)
{
    ಆಗ (n_ಎತ್ತರ--) {

        sdl_sve_x123_stride_blend_ಗಮ್ಯ_a321_fill_alpha((uint32_t *)pch_ಮೂಲ,
                                                     (uint32_t *)pch_ಗುರಿ,
                                                     n_ಅಗಲ);

        pch_ಮೂಲ += u_ಮೂಲ_Stride;
        pch_ಗುರಿ += u_ಗುರಿ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_x123_blend_ಗಮ್ಯ_a321_copy_alpha(uint8_t *SDL_RESTRICT pch_ಮೂಲ,
                                                         size_t u_ಮೂಲ_Stride,
                                                         uint8_t *SDL_RESTRICT pch_ಗುರಿ,
                                                         size_t u_ಗುರಿ_Stride,
                                                         ಪೂರ್ಣಾಂಕ n_ಅಗಲ,
                                                         ಪೂರ್ಣಾಂಕ n_ಎತ್ತರ)
{
    ಆಗ (n_ಎತ್ತರ--) {

        sdl_sve_x123_stride_blend_ಗಮ್ಯ_a321_copy_alpha((uint32_t *)pch_ಮೂಲ,
                                                     (uint32_t *)pch_ಗುರಿ,
                                                     n_ಅಗಲ);

        pch_ಮೂಲ += u_ಮೂಲ_Stride;
        pch_ಗುರಿ += u_ಗುರಿ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_123x_stride_blend_ಗಮ್ಯ_321a_fill_alpha(
    uint32_t *SDL_RESTRICT pw_ಮೂಲ,
    uint32_t *SDL_RESTRICT pw_ಗುರಿ,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(0,
                                       sdl_sve_pixel_u16x4_foreach_chn_123a_321a,
                                       sdl_sve_rgb32_blend_op_fill_alpha(0););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_123x_stride_blend_ಗಮ್ಯ_321a_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ಮೂಲ,
    uint32_t *SDL_RESTRICT pw_ಗುರಿ,
    size_t uStride)
{
    sdl_sve_rgb32_no_alpha_stride_impl(0,
                                       sdl_sve_pixel_u16x4_foreach_chn_123a_321a,
                                       sdl_sve_rgb32_blend_op_copy_alpha(0););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_123x_blend_ಗಮ್ಯ_321a_fill_alpha(uint8_t *SDL_RESTRICT pch_ಮೂಲ,
                                                         size_t u_ಮೂಲ_Stride,
                                                         uint8_t *SDL_RESTRICT pch_ಗುರಿ,
                                                         size_t u_ಗುರಿ_Stride,
                                                         ಪೂರ್ಣಾಂಕ n_ಅಗಲ,
                                                         ಪೂರ್ಣಾಂಕ n_ಎತ್ತರ)
{
    ಆಗ (n_ಎತ್ತರ--) {

        sdl_sve_123x_stride_blend_ಗಮ್ಯ_321a_fill_alpha((uint32_t *)pch_ಮೂಲ,
                                                     (uint32_t *)pch_ಗುರಿ,
                                                     n_ಅಗಲ);

        pch_ಮೂಲ += u_ಮೂಲ_Stride;
        pch_ಗುರಿ += u_ಗುರಿ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_123x_blend_ಗಮ್ಯ_321a_copy_alpha(uint8_t *SDL_RESTRICT pch_ಮೂಲ,
                                                         size_t u_ಮೂಲ_Stride,
                                                         uint8_t *SDL_RESTRICT pch_ಗುರಿ,
                                                         size_t u_ಗುರಿ_Stride,
                                                         ಪೂರ್ಣಾಂಕ n_ಅಗಲ,
                                                         ಪೂರ್ಣಾಂಕ n_ಎತ್ತರ)
{
    ಆಗ (n_ಎತ್ತರ--) {

        sdl_sve_123x_stride_blend_ಗಮ್ಯ_321a_copy_alpha((uint32_t *)pch_ಮೂಲ,
                                                     (uint32_t *)pch_ಗುರಿ,
                                                     n_ಅಗಲ);

        pch_ಮೂಲ += u_ಮೂಲ_Stride;
        pch_ಗುರಿ += u_ಗುರಿ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_8888_ಗಮ್ಯ_8888_swizzle_dispatcher(SDL_BlitInfo *info)
{
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

    ಪ್ರತಿಜ್ಞಾ((srcbpp == 4) && (dstbpp == 4));

    bool fill_alpha = (!dstfmt->Amask);

    ಪೂರ್ಣಾಂಕ srcstride = srcskip + srcbpp * ಅಗಲ;
    ಪೂರ್ಣಾಂಕ dststride = dstskip + dstbpp * ಅಗಲ;

    ಆಯ್ಕೆ (srcfmt->format) {
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_XRGB8888:
        ಆಯ್ಕೆ (dstfmt->format) {
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_ARGB8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_XRGB8888:
            ಆದರೆ (fill_alpha) {
                sdl_sve_xccc_blend_ಗಮ್ಯ_accc_fill_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    ಅಗಲ,
                    ಎತ್ತರ);
            } ಇಲ್ಲದಿದ್ದರೆ {
                sdl_sve_xccc_blend_ಗಮ್ಯ_accc_copy_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    ಅಗಲ,
                    ಎತ್ತರ);
            }
            ನಿಲ್ಲಿಸು;

        ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGBA8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGBX8888:
            ಆದರೆ (fill_alpha) {
                sdl_sve_xccc_blend_ಗಮ್ಯ_ccca_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      ಅಗಲ,
                                                      ಎತ್ತರ);
            } ಇಲ್ಲದಿದ್ದರೆ {
                sdl_sve_xccc_blend_ಗಮ್ಯ_ccca_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      ಅಗಲ,
                                                      ಎತ್ತರ);
            }
            ನಿಲ್ಲಿಸು;

        ಸ್ಥಿತಿ SDL_PIXELFORMAT_ABGR8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_XBGR8888:
            ಆದರೆ (fill_alpha) {
                sdl_sve_x123_blend_ಗಮ್ಯ_a321_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      ಅಗಲ,
                                                      ಎತ್ತರ);
            } ಇಲ್ಲದಿದ್ದರೆ {
                sdl_sve_x123_blend_ಗಮ್ಯ_a321_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      ಅಗಲ,
                                                      ಎತ್ತರ);
            }
            ನಿಲ್ಲಿಸು;

        ಸ್ಥಿತಿ SDL_PIXELFORMAT_BGRA8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_BGRX8888:
            ಆದರೆ (fill_alpha) {
                sdl_sve_x123_blend_ಗಮ್ಯ_321a_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      ಅಗಲ,
                                                      ಎತ್ತರ);
            } ಇಲ್ಲದಿದ್ದರೆ {
                sdl_sve_x123_blend_ಗಮ್ಯ_321a_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      ಅಗಲ,
                                                      ಎತ್ತರ);
            }
            ನಿಲ್ಲಿಸು;
        ಪೂರ್ವನಿಯೋಜಿತ:
            ಪ್ರತಿಜ್ಞಾ(false);
            ನಿಲ್ಲಿಸು;
        }
        ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ SDL_PIXELFORMAT_ARGB8888:
        ಆಯ್ಕೆ (dstfmt->format) {
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_ARGB8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_XRGB8888:
            ಆದರೆ (fill_alpha) {
                sdl_sve_accc_blend_ಗಮ್ಯ_accc_fill_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    ಅಗಲ,
                    ಎತ್ತರ);
            } ಇಲ್ಲದಿದ್ದರೆ {
                sdl_sve_accc_blend_ಗಮ್ಯ_accc_copy_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    ಅಗಲ,
                    ಎತ್ತರ);
            }
            ನಿಲ್ಲಿಸು;

        ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGBA8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGBX8888:
            ಆದರೆ (fill_alpha) {
                sdl_sve_accc_blend_ಗಮ್ಯ_ccca_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      ಅಗಲ,
                                                      ಎತ್ತರ);
            } ಇಲ್ಲದಿದ್ದರೆ {
                sdl_sve_accc_blend_ಗಮ್ಯ_ccca_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      ಅಗಲ,
                                                      ಎತ್ತರ);
            }
            ನಿಲ್ಲಿಸು;

        ಸ್ಥಿತಿ SDL_PIXELFORMAT_ABGR8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_XBGR8888:
            ಆದರೆ (fill_alpha) {
                sdl_sve_a123_blend_ಗಮ್ಯ_a321_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      ಅಗಲ,
                                                      ಎತ್ತರ);
            } ಇಲ್ಲದಿದ್ದರೆ {
                sdl_sve_a123_blend_ಗಮ್ಯ_a321_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      ಅಗಲ,
                                                      ಎತ್ತರ);
            }
            ನಿಲ್ಲಿಸು;

        ಸ್ಥಿತಿ SDL_PIXELFORMAT_BGRA8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_BGRX8888:
            ಆದರೆ (fill_alpha) {
                sdl_sve_a123_blend_ಗಮ್ಯ_321a_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      ಅಗಲ,
                                                      ಎತ್ತರ);
            } ಇಲ್ಲದಿದ್ದರೆ {
                sdl_sve_a123_blend_ಗಮ್ಯ_321a_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      ಅಗಲ,
                                                      ಎತ್ತರ);
            }
            ನಿಲ್ಲಿಸು;
        ಪೂರ್ವನಿಯೋಜಿತ:
            ಪ್ರತಿಜ್ಞಾ(false);
            ನಿಲ್ಲಿಸು;
        }
        ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGBX8888:
        ಆಯ್ಕೆ (dstfmt->format) {
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_ARGB8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_XRGB8888:
            ಆದರೆ (fill_alpha) {
                sdl_sve_cccx_blend_ಗಮ್ಯ_accc_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      ಅಗಲ,
                                                      ಎತ್ತರ);
            } ಇಲ್ಲದಿದ್ದರೆ {
                sdl_sve_cccx_blend_ಗಮ್ಯ_accc_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      ಅಗಲ,
                                                      ಎತ್ತರ);
            }
            ನಿಲ್ಲಿಸು;

        ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGBA8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGBX8888:
            ಆದರೆ (fill_alpha) {
                sdl_sve_cccx_blend_ಗಮ್ಯ_ccca_fill_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    ಅಗಲ,
                    ಎತ್ತರ);
            } ಇಲ್ಲದಿದ್ದರೆ {
                sdl_sve_cccx_blend_ಗಮ್ಯ_ccca_copy_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    ಅಗಲ,
                    ಎತ್ತರ);
            }
            ನಿಲ್ಲಿಸು;

        ಸ್ಥಿತಿ SDL_PIXELFORMAT_ABGR8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_XBGR8888:
            ಆದರೆ (fill_alpha) {
                sdl_sve_123x_blend_ಗಮ್ಯ_a321_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      ಅಗಲ,
                                                      ಎತ್ತರ);
            } ಇಲ್ಲದಿದ್ದರೆ {
                sdl_sve_123x_blend_ಗಮ್ಯ_a321_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      ಅಗಲ,
                                                      ಎತ್ತರ);
            }
            ನಿಲ್ಲಿಸು;

        ಸ್ಥಿತಿ SDL_PIXELFORMAT_BGRA8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_BGRX8888:
            ಆದರೆ (fill_alpha) {
                sdl_sve_123x_blend_ಗಮ್ಯ_321a_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      ಅಗಲ,
                                                      ಎತ್ತರ);
            } ಇಲ್ಲದಿದ್ದರೆ {
                sdl_sve_123x_blend_ಗಮ್ಯ_321a_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      ಅಗಲ,
                                                      ಎತ್ತರ);
            }
            ನಿಲ್ಲಿಸು;
        ಪೂರ್ವನಿಯೋಜಿತ:
            ಪ್ರತಿಜ್ಞಾ(false);
            ನಿಲ್ಲಿಸು;
        }
        ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGBA8888:
        ಆಯ್ಕೆ (dstfmt->format) {
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_ARGB8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_XRGB8888:
            ಆದರೆ (fill_alpha) {
                sdl_sve_ccca_blend_ಗಮ್ಯ_accc_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      ಅಗಲ,
                                                      ಎತ್ತರ);
            } ಇಲ್ಲದಿದ್ದರೆ {
                sdl_sve_ccca_blend_ಗಮ್ಯ_accc_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      ಅಗಲ,
                                                      ಎತ್ತರ);
            }
            ನಿಲ್ಲಿಸು;

        ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGBA8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGBX8888:
            ಆದರೆ (fill_alpha) {
                sdl_sve_ccca_blend_ಗಮ್ಯ_ccca_fill_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    ಅಗಲ,
                    ಎತ್ತರ);
            } ಇಲ್ಲದಿದ್ದರೆ {
                sdl_sve_ccca_blend_ಗಮ್ಯ_ccca_copy_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    ಅಗಲ,
                    ಎತ್ತರ);
            }
            ನಿಲ್ಲಿಸು;

        ಸ್ಥಿತಿ SDL_PIXELFORMAT_ABGR8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_XBGR8888:
            ಆದರೆ (fill_alpha) {
                sdl_sve_123a_blend_ಗಮ್ಯ_a321_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      ಅಗಲ,
                                                      ಎತ್ತರ);
            } ಇಲ್ಲದಿದ್ದರೆ {
                sdl_sve_123a_blend_ಗಮ್ಯ_a321_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      ಅಗಲ,
                                                      ಎತ್ತರ);
            }
            ನಿಲ್ಲಿಸು;

        ಸ್ಥಿತಿ SDL_PIXELFORMAT_BGRA8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_BGRX8888:
            ಆದರೆ (fill_alpha) {
                sdl_sve_123a_blend_ಗಮ್ಯ_321a_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      ಅಗಲ,
                                                      ಎತ್ತರ);
            } ಇಲ್ಲದಿದ್ದರೆ {
                sdl_sve_123a_blend_ಗಮ್ಯ_321a_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      ಅಗಲ,
                                                      ಎತ್ತರ);
            }
            ನಿಲ್ಲಿಸು;
        ಪೂರ್ವನಿಯೋಜಿತ:
            ಪ್ರತಿಜ್ಞಾ(false);
            ನಿಲ್ಲಿಸು;
        }
        ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ SDL_PIXELFORMAT_XBGR8888:
        ಆಯ್ಕೆ (dstfmt->format) {
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_ARGB8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_XRGB8888:
            ಆದರೆ (fill_alpha) {
                sdl_sve_x123_blend_ಗಮ್ಯ_a321_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      ಅಗಲ,
                                                      ಎತ್ತರ);
            } ಇಲ್ಲದಿದ್ದರೆ {
                sdl_sve_x123_blend_ಗಮ್ಯ_a321_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      ಅಗಲ,
                                                      ಎತ್ತರ);
            }
            ನಿಲ್ಲಿಸು;

        ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGBA8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGBX8888:
            ಆದರೆ (fill_alpha) {
                sdl_sve_x123_blend_ಗಮ್ಯ_321a_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      ಅಗಲ,
                                                      ಎತ್ತರ);
            } ಇಲ್ಲದಿದ್ದರೆ {
                sdl_sve_x123_blend_ಗಮ್ಯ_321a_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      ಅಗಲ,
                                                      ಎತ್ತರ);
            }
            ನಿಲ್ಲಿಸು;

        ಸ್ಥಿತಿ SDL_PIXELFORMAT_ABGR8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_XBGR8888:
            ಆದರೆ (fill_alpha) {
                sdl_sve_xccc_blend_ಗಮ್ಯ_accc_fill_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    ಅಗಲ,
                    ಎತ್ತರ);
            } ಇಲ್ಲದಿದ್ದರೆ {
                sdl_sve_xccc_blend_ಗಮ್ಯ_accc_copy_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    ಅಗಲ,
                    ಎತ್ತರ);
            }
            ನಿಲ್ಲಿಸು;

        ಸ್ಥಿತಿ SDL_PIXELFORMAT_BGRA8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_BGRX8888:
            ಆದರೆ (fill_alpha) {
                sdl_sve_xccc_blend_ಗಮ್ಯ_ccca_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      ಅಗಲ,
                                                      ಎತ್ತರ);
            } ಇಲ್ಲದಿದ್ದರೆ {
                sdl_sve_xccc_blend_ಗಮ್ಯ_ccca_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      ಅಗಲ,
                                                      ಎತ್ತರ);
            }
            ನಿಲ್ಲಿಸು;
        ಪೂರ್ವನಿಯೋಜಿತ:
            ಪ್ರತಿಜ್ಞಾ(false);
            ನಿಲ್ಲಿಸು;
        }
        ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ SDL_PIXELFORMAT_ABGR8888:
        ಆಯ್ಕೆ (dstfmt->format) {
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_ARGB8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_XRGB8888:
            ಆದರೆ (fill_alpha) {
                sdl_sve_a123_blend_ಗಮ್ಯ_a321_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      ಅಗಲ,
                                                      ಎತ್ತರ);
            } ಇಲ್ಲದಿದ್ದರೆ {
                sdl_sve_a123_blend_ಗಮ್ಯ_a321_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      ಅಗಲ,
                                                      ಎತ್ತರ);
            }
            ನಿಲ್ಲಿಸು;

        ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGBA8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGBX8888:
            ಆದರೆ (fill_alpha) {
                sdl_sve_a123_blend_ಗಮ್ಯ_321a_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      ಅಗಲ,
                                                      ಎತ್ತರ);
            } ಇಲ್ಲದಿದ್ದರೆ {
                sdl_sve_a123_blend_ಗಮ್ಯ_321a_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      ಅಗಲ,
                                                      ಎತ್ತರ);
            }
            ನಿಲ್ಲಿಸು;

        ಸ್ಥಿತಿ SDL_PIXELFORMAT_ABGR8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_XBGR8888:
            ಆದರೆ (fill_alpha) {
                sdl_sve_accc_blend_ಗಮ್ಯ_accc_fill_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    ಅಗಲ,
                    ಎತ್ತರ);
            } ಇಲ್ಲದಿದ್ದರೆ {
                sdl_sve_accc_blend_ಗಮ್ಯ_accc_copy_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    ಅಗಲ,
                    ಎತ್ತರ);
            }
            ನಿಲ್ಲಿಸು;

        ಸ್ಥಿತಿ SDL_PIXELFORMAT_BGRA8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_BGRX8888:
            ಆದರೆ (fill_alpha) {
                sdl_sve_accc_blend_ಗಮ್ಯ_ccca_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      ಅಗಲ,
                                                      ಎತ್ತರ);
            } ಇಲ್ಲದಿದ್ದರೆ {
                sdl_sve_accc_blend_ಗಮ್ಯ_ccca_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      ಅಗಲ,
                                                      ಎತ್ತರ);
            }
            ನಿಲ್ಲಿಸು;
        ಪೂರ್ವನಿಯೋಜಿತ:
            ಪ್ರತಿಜ್ಞಾ(false);
            ನಿಲ್ಲಿಸು;
        }
        ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ SDL_PIXELFORMAT_BGRX8888:
        ಆಯ್ಕೆ (dstfmt->format) {
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_ARGB8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_XRGB8888:
            ಆದರೆ (fill_alpha) {
                sdl_sve_123x_blend_ಗಮ್ಯ_a321_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      ಅಗಲ,
                                                      ಎತ್ತರ);
            } ಇಲ್ಲದಿದ್ದರೆ {
                sdl_sve_123x_blend_ಗಮ್ಯ_a321_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      ಅಗಲ,
                                                      ಎತ್ತರ);
            }
            ನಿಲ್ಲಿಸು;

        ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGBA8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGBX8888:
            ಆದರೆ (fill_alpha) {
                sdl_sve_123x_blend_ಗಮ್ಯ_321a_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      ಅಗಲ,
                                                      ಎತ್ತರ);
            } ಇಲ್ಲದಿದ್ದರೆ {
                sdl_sve_123x_blend_ಗಮ್ಯ_321a_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      ಅಗಲ,
                                                      ಎತ್ತರ);
            }
            ನಿಲ್ಲಿಸು;

        ಸ್ಥಿತಿ SDL_PIXELFORMAT_ABGR8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_XBGR8888:
            ಆದರೆ (fill_alpha) {
                sdl_sve_cccx_blend_ಗಮ್ಯ_accc_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      ಅಗಲ,
                                                      ಎತ್ತರ);
            } ಇಲ್ಲದಿದ್ದರೆ {
                sdl_sve_cccx_blend_ಗಮ್ಯ_accc_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      ಅಗಲ,
                                                      ಎತ್ತರ);
            }
            ನಿಲ್ಲಿಸು;

        ಸ್ಥಿತಿ SDL_PIXELFORMAT_BGRA8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_BGRX8888:
            ಆದರೆ (fill_alpha) {
                sdl_sve_cccx_blend_ಗಮ್ಯ_ccca_fill_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    ಅಗಲ,
                    ಎತ್ತರ);
            } ಇಲ್ಲದಿದ್ದರೆ {
                sdl_sve_cccx_blend_ಗಮ್ಯ_ccca_copy_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    ಅಗಲ,
                    ಎತ್ತರ);
            }
            ನಿಲ್ಲಿಸು;
        ಪೂರ್ವನಿಯೋಜಿತ:
            ಪ್ರತಿಜ್ಞಾ(false);
            ನಿಲ್ಲಿಸು;
        }
        ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ SDL_PIXELFORMAT_BGRA8888:
        ಆಯ್ಕೆ (dstfmt->format) {
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_ARGB8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_XRGB8888:
            ಆದರೆ (fill_alpha) {
                sdl_sve_123a_blend_ಗಮ್ಯ_a321_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      ಅಗಲ,
                                                      ಎತ್ತರ);
            } ಇಲ್ಲದಿದ್ದರೆ {
                sdl_sve_123a_blend_ಗಮ್ಯ_a321_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      ಅಗಲ,
                                                      ಎತ್ತರ);
            }
            ನಿಲ್ಲಿಸು;

        ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGBA8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGBX8888:
            ಆದರೆ (fill_alpha) {
                sdl_sve_123a_blend_ಗಮ್ಯ_321a_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      ಅಗಲ,
                                                      ಎತ್ತರ);
            } ಇಲ್ಲದಿದ್ದರೆ {
                sdl_sve_123a_blend_ಗಮ್ಯ_321a_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      ಅಗಲ,
                                                      ಎತ್ತರ);
            }
            ನಿಲ್ಲಿಸು;

        ಸ್ಥಿತಿ SDL_PIXELFORMAT_ABGR8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_XBGR8888:
            ಆದರೆ (fill_alpha) {
                sdl_sve_ccca_blend_ಗಮ್ಯ_accc_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      ಅಗಲ,
                                                      ಎತ್ತರ);
            } ಇಲ್ಲದಿದ್ದರೆ {
                sdl_sve_ccca_blend_ಗಮ್ಯ_accc_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      ಅಗಲ,
                                                      ಎತ್ತರ);
            }
            ನಿಲ್ಲಿಸು;

        ಸ್ಥಿತಿ SDL_PIXELFORMAT_BGRA8888:
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_BGRX8888:
            ಆದರೆ (fill_alpha) {
                sdl_sve_ccca_blend_ಗಮ್ಯ_ccca_fill_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    ಅಗಲ,
                    ಎತ್ತರ);
            } ಇಲ್ಲದಿದ್ದರೆ {
                sdl_sve_ccca_blend_ಗಮ್ಯ_ccca_copy_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    ಅಗಲ,
                    ಎತ್ತರ);
            }
            ನಿಲ್ಲಿಸು;
        ಪೂರ್ವನಿಯೋಜಿತ:
            ಪ್ರತಿಜ್ಞಾ(false);
            ನಿಲ್ಲಿಸು;
        }
        ನಿಲ್ಲಿಸು;

    ಪೂರ್ವನಿಯೋಜಿತ:
        ಪ್ರತಿಜ್ಞಾ(false);
        ನಿಲ್ಲಿಸು;
    }
}

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ sdl_sve_rgb32_blend_ಗಮ್ಯ_rgb565_op
#ವ್ಯಾಖ್ಯಾನಿಸು sdl_sve_rgb32_blend_ಗಮ್ಯ_rgb565_op(ma_alpha_chn_idx)
#ಆದರೆ_ಅಂತ್ಯ

/*
 * ACCC or CCCA
 */
SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_argb8888_stride_blend_ಗಮ್ಯ_rgb565(uint32_t *SDL_RESTRICT pw_ಮೂಲ,
                                                           uint16_t *SDL_RESTRICT phw_ಗುರಿ,
                                                           size_t uStride)
{
    sdl_sve_rgb32_ಗಮ್ಯ_rgb565_stride_impl(
        sdl_sve_pixel_u16x4_foreach_chn_argb_rgb565,
        {
            sdl_sve_rgb32_blend_ಗಮ್ಯ_rgb565_op(3);
        });
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_argb8888_blend_ಗಮ್ಯ_rgb565(uint8_t *SDL_RESTRICT pch_ಮೂಲ,
                                                    size_t u_ಮೂಲ_Stride,
                                                    uint8_t *SDL_RESTRICT pch_ಗುರಿ,
                                                    size_t u_ಗುರಿ_Stride,
                                                    ಪೂರ್ಣಾಂಕ n_ಅಗಲ,
                                                    ಪೂರ್ಣಾಂಕ n_ಎತ್ತರ)
{
    ಆಗ (n_ಎತ್ತರ--) {

        sdl_sve_argb8888_stride_blend_ಗಮ್ಯ_rgb565((uint32_t *)pch_ಮೂಲ,
                                                (uint16_t *)pch_ಗುರಿ,
                                                n_ಅಗಲ);

        pch_ಮೂಲ += u_ಮೂಲ_Stride;
        pch_ಗುರಿ += u_ಗುರಿ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_rgba8888_stride_blend_ಗಮ್ಯ_rgb565(uint32_t *SDL_RESTRICT pw_ಮೂಲ,
                                                           uint16_t *SDL_RESTRICT phw_ಗುರಿ,
                                                           size_t uStride)
{
    sdl_sve_rgb32_ಗಮ್ಯ_rgb565_stride_impl(
        sdl_sve_pixel_u16x4_foreach_chn_rgba_rgb565,
        {
            sdl_sve_rgb32_blend_ಗಮ್ಯ_rgb565_op(0);
        });
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_rgba8888_blend_ಗಮ್ಯ_rgb565(uint8_t *SDL_RESTRICT pch_ಮೂಲ,
                                                    size_t u_ಮೂಲ_Stride,
                                                    uint8_t *SDL_RESTRICT pch_ಗುರಿ,
                                                    size_t u_ಗುರಿ_Stride,
                                                    ಪೂರ್ಣಾಂಕ n_ಅಗಲ,
                                                    ಪೂರ್ಣಾಂಕ n_ಎತ್ತರ)
{
    ಆಗ (n_ಎತ್ತರ--) {

        sdl_sve_rgba8888_stride_blend_ಗಮ್ಯ_rgb565((uint32_t *)pch_ಮೂಲ,
                                                (uint16_t *)pch_ಗುರಿ,
                                                n_ಅಗಲ);

        pch_ಮೂಲ += u_ಮೂಲ_Stride;
        pch_ಗುರಿ += u_ಗುರಿ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_bgra8888_stride_blend_ಗಮ್ಯ_rgb565(uint32_t *SDL_RESTRICT pw_ಮೂಲ,
                                                           uint16_t *SDL_RESTRICT phw_ಗುರಿ,
                                                           size_t uStride)
{
    sdl_sve_rgb32_ಗಮ್ಯ_rgb565_stride_impl(
        sdl_sve_pixel_u16x4_foreach_chn_bgra_rgb565,
        {
            sdl_sve_rgb32_blend_ಗಮ್ಯ_rgb565_op(0);
        });
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_bgra8888_blend_ಗಮ್ಯ_rgb565(uint8_t *SDL_RESTRICT pch_ಮೂಲ,
                                                    size_t u_ಮೂಲ_Stride,
                                                    uint8_t *SDL_RESTRICT pch_ಗುರಿ,
                                                    size_t u_ಗುರಿ_Stride,
                                                    ಪೂರ್ಣಾಂಕ n_ಅಗಲ,
                                                    ಪೂರ್ಣಾಂಕ n_ಎತ್ತರ)
{
    ಆಗ (n_ಎತ್ತರ--) {

        sdl_sve_bgra8888_stride_blend_ಗಮ್ಯ_rgb565((uint32_t *)pch_ಮೂಲ,
                                                (uint16_t *)pch_ಗುರಿ,
                                                n_ಅಗಲ);

        pch_ಮೂಲ += u_ಮೂಲ_Stride;
        pch_ಗುರಿ += u_ಗುರಿ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_abgr8888_stride_blend_ಗಮ್ಯ_rgb565(uint32_t *SDL_RESTRICT pw_ಮೂಲ,
                                                           uint16_t *SDL_RESTRICT phw_ಗುರಿ,
                                                           size_t uStride)
{
    sdl_sve_rgb32_ಗಮ್ಯ_rgb565_stride_impl(
        sdl_sve_pixel_u16x4_foreach_chn_abgr_rgb565,
        {
            sdl_sve_rgb32_blend_ಗಮ್ಯ_rgb565_op(3);
        });
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_abgr8888_blend_ಗಮ್ಯ_rgb565(uint8_t *SDL_RESTRICT pch_ಮೂಲ,
                                                    size_t u_ಮೂಲ_Stride,
                                                    uint8_t *SDL_RESTRICT pch_ಗುರಿ,
                                                    size_t u_ಗುರಿ_Stride,
                                                    ಪೂರ್ಣಾಂಕ n_ಅಗಲ,
                                                    ಪೂರ್ಣಾಂಕ n_ಎತ್ತರ)
{
    ಆಗ (n_ಎತ್ತರ--) {

        sdl_sve_abgr8888_stride_blend_ಗಮ್ಯ_rgb565((uint32_t *)pch_ಮೂಲ,
                                                (uint16_t *)pch_ಗುರಿ,
                                                n_ಅಗಲ);

        pch_ಮೂಲ += u_ಮೂಲ_Stride;
        pch_ಗುರಿ += u_ಗುರಿ_Stride;
    }
}

/*
 * XCCC or CCCX
 */
SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_xrgb8888_stride_blend_ಗಮ್ಯ_rgb565(uint32_t *SDL_RESTRICT pw_ಮೂಲ,
                                                           uint16_t *SDL_RESTRICT phw_ಗುರಿ,
                                                           size_t uStride)
{
    sdl_sve_rgb32_no_alpha_ಗಮ್ಯ_rgb565_stride_impl(
        3,
        sdl_sve_pixel_u16x4_foreach_chn_argb_rgb565,
        {
            sdl_sve_rgb32_blend_ಗಮ್ಯ_rgb565_op(3);
        });
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_xrgb8888_blend_ಗಮ್ಯ_rgb565(uint8_t *SDL_RESTRICT pch_ಮೂಲ,
                                                    size_t u_ಮೂಲ_Stride,
                                                    uint8_t *SDL_RESTRICT pch_ಗುರಿ,
                                                    size_t u_ಗುರಿ_Stride,
                                                    ಪೂರ್ಣಾಂಕ n_ಅಗಲ,
                                                    ಪೂರ್ಣಾಂಕ n_ಎತ್ತರ)
{
    ಆಗ (n_ಎತ್ತರ--) {

        sdl_sve_xrgb8888_stride_blend_ಗಮ್ಯ_rgb565((uint32_t *)pch_ಮೂಲ,
                                                (uint16_t *)pch_ಗುರಿ,
                                                n_ಅಗಲ);

        pch_ಮೂಲ += u_ಮೂಲ_Stride;
        pch_ಗುರಿ += u_ಗುರಿ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_rgbx8888_stride_blend_ಗಮ್ಯ_rgb565(uint32_t *SDL_RESTRICT pw_ಮೂಲ,
                                                           uint16_t *SDL_RESTRICT phw_ಗುರಿ,
                                                           size_t uStride)
{
    sdl_sve_rgb32_no_alpha_ಗಮ್ಯ_rgb565_stride_impl(
        0,
        sdl_sve_pixel_u16x4_foreach_chn_rgba_rgb565,
        {
            sdl_sve_rgb32_blend_ಗಮ್ಯ_rgb565_op(0);
        });
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_rgbx8888_blend_ಗಮ್ಯ_rgb565(uint8_t *SDL_RESTRICT pch_ಮೂಲ,
                                                    size_t u_ಮೂಲ_Stride,
                                                    uint8_t *SDL_RESTRICT pch_ಗುರಿ,
                                                    size_t u_ಗುರಿ_Stride,
                                                    ಪೂರ್ಣಾಂಕ n_ಅಗಲ,
                                                    ಪೂರ್ಣಾಂಕ n_ಎತ್ತರ)
{
    ಆಗ (n_ಎತ್ತರ--) {

        sdl_sve_rgbx8888_stride_blend_ಗಮ್ಯ_rgb565((uint32_t *)pch_ಮೂಲ,
                                                (uint16_t *)pch_ಗುರಿ,
                                                n_ಅಗಲ);

        pch_ಮೂಲ += u_ಮೂಲ_Stride;
        pch_ಗುರಿ += u_ಗುರಿ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_bgrx8888_stride_blend_ಗಮ್ಯ_rgb565(uint32_t *SDL_RESTRICT pw_ಮೂಲ,
                                                           uint16_t *SDL_RESTRICT phw_ಗುರಿ,
                                                           size_t uStride)
{
    sdl_sve_rgb32_no_alpha_ಗಮ್ಯ_rgb565_stride_impl(
        0,
        sdl_sve_pixel_u16x4_foreach_chn_bgra_rgb565,
        {
            sdl_sve_rgb32_blend_ಗಮ್ಯ_rgb565_op(0);
        });
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_bgrx8888_blend_ಗಮ್ಯ_rgb565(uint8_t *SDL_RESTRICT pch_ಮೂಲ,
                                                    size_t u_ಮೂಲ_Stride,
                                                    uint8_t *SDL_RESTRICT pch_ಗುರಿ,
                                                    size_t u_ಗುರಿ_Stride,
                                                    ಪೂರ್ಣಾಂಕ n_ಅಗಲ,
                                                    ಪೂರ್ಣಾಂಕ n_ಎತ್ತರ)
{
    ಆಗ (n_ಎತ್ತರ--) {

        sdl_sve_bgrx8888_stride_blend_ಗಮ್ಯ_rgb565((uint32_t *)pch_ಮೂಲ,
                                                (uint16_t *)pch_ಗುರಿ,
                                                n_ಅಗಲ);

        pch_ಮೂಲ += u_ಮೂಲ_Stride;
        pch_ಗುರಿ += u_ಗುರಿ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_xbgr8888_stride_blend_ಗಮ್ಯ_rgb565(uint32_t *SDL_RESTRICT pw_ಮೂಲ,
                                                           uint16_t *SDL_RESTRICT phw_ಗುರಿ,
                                                           size_t uStride)
{
    sdl_sve_rgb32_no_alpha_ಗಮ್ಯ_rgb565_stride_impl(
        3,
        sdl_sve_pixel_u16x4_foreach_chn_abgr_rgb565,
        {
            sdl_sve_rgb32_blend_ಗಮ್ಯ_rgb565_op(3);
        });
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_xbgr8888_blend_ಗಮ್ಯ_rgb565(uint8_t *SDL_RESTRICT pch_ಮೂಲ,
                                                    size_t u_ಮೂಲ_Stride,
                                                    uint8_t *SDL_RESTRICT pch_ಗುರಿ,
                                                    size_t u_ಗುರಿ_Stride,
                                                    ಪೂರ್ಣಾಂಕ n_ಅಗಲ,
                                                    ಪೂರ್ಣಾಂಕ n_ಎತ್ತರ)
{
    ಆಗ (n_ಎತ್ತರ--) {

        sdl_sve_xbgr8888_stride_blend_ಗಮ್ಯ_rgb565((uint32_t *)pch_ಮೂಲ,
                                                (uint16_t *)pch_ಗುರಿ,
                                                n_ಅಗಲ);

        pch_ಮೂಲ += u_ಮೂಲ_Stride;
        pch_ಗುರಿ += u_ಗುರಿ_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ sdl_sve_rgb32_ಗಮ್ಯ_rgb565_swizzle_dispatcher(SDL_BlitInfo *info)
{
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

    ಪ್ರತಿಜ್ಞಾ(srcbpp == 4);
    ಪ್ರತಿಜ್ಞಾ(dstbpp == 2);

    ಪೂರ್ಣಾಂಕ srcstride = srcskip + srcbpp * ಅಗಲ;
    ಪೂರ್ಣಾಂಕ dststride = dstskip + dstbpp * ಅಗಲ;

    ಆಯ್ಕೆ (srcfmt->format) {
    ಸ್ಥಿತಿ SDL_PIXELFORMAT_XRGB8888:
        sdl_sve_xrgb8888_blend_ಗಮ್ಯ_rgb565(src,
                                         srcstride,
                                         dst,
                                         dststride,
                                         ಅಗಲ,
                                         ಎತ್ತರ);
        ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ SDL_PIXELFORMAT_ARGB8888:
        sdl_sve_argb8888_blend_ಗಮ್ಯ_rgb565(src,
                                         srcstride,
                                         dst,
                                         dststride,
                                         ಅಗಲ,
                                         ಎತ್ತರ);
        ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGBX8888:
        sdl_sve_rgbx8888_blend_ಗಮ್ಯ_rgb565(src,
                                         srcstride,
                                         dst,
                                         dststride,
                                         ಅಗಲ,
                                         ಎತ್ತರ);
        ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ SDL_PIXELFORMAT_RGBA8888:
        sdl_sve_rgba8888_blend_ಗಮ್ಯ_rgb565(src,
                                         srcstride,
                                         dst,
                                         dststride,
                                         ಅಗಲ,
                                         ಎತ್ತರ);
        ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ SDL_PIXELFORMAT_XBGR8888:
        sdl_sve_xbgr8888_blend_ಗಮ್ಯ_rgb565(src,
                                         srcstride,
                                         dst,
                                         dststride,
                                         ಅಗಲ,
                                         ಎತ್ತರ);
        ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ SDL_PIXELFORMAT_ABGR8888:
        sdl_sve_abgr8888_blend_ಗಮ್ಯ_rgb565(src,
                                         srcstride,
                                         dst,
                                         dststride,
                                         ಅಗಲ,
                                         ಎತ್ತರ);
        ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ SDL_PIXELFORMAT_BGRX8888:
        sdl_sve_bgrx8888_blend_ಗಮ್ಯ_rgb565(src,
                                         srcstride,
                                         dst,
                                         dststride,
                                         ಅಗಲ,
                                         ಎತ್ತರ);
        ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ SDL_PIXELFORMAT_BGRA8888:
        sdl_sve_bgra8888_blend_ಗಮ್ಯ_rgb565(src,
                                         srcstride,
                                         dst,
                                         dststride,
                                         ಅಗಲ,
                                         ಎತ್ತರ);
        ನಿಲ್ಲಿಸು;

    ಪೂರ್ವನಿಯೋಜಿತ:
        ಪ್ರತಿಜ್ಞಾ(false);
        ನಿಲ್ಲಿಸು;
    }
}

#ಆದರೆ_ಅಂತ್ಯ /* SD_SVE2_SWIZZLE_H */