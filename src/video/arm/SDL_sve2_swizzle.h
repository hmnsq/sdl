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

#ఒకవేళ !defined(SD_SVE2_SWIZZLE_H) //&& (defined(__ARM_FEATURE_SVE2) && __ARM_FEATURE_SVE2)
#నిర్వచించు SD_SVE2_SWIZZLE_H

#అన్తర్భావ "SDL_sve2_extension.h"

#నిర్వచించు sdl_sve_rgb32_stride_impl(ma_sve_chn_iterator, ...)   \
    sdl_sve_stride_loop_pixel(uStride, v_తోక_Pred)             \
    {                                                         \
                                                              \
        svuint16x4_t v_ఆధారం_Low16x4 = svundef4_u16();         \
        svuint16x4_t v_ఆధారం_High16x4 = svundef4_u16();        \
                                                              \
        svuint16x4_t v_లక్ష్యం_Low16x4 = svundef4_u16();         \
        svuint16x4_t v_లక్ష్యం_High16x4 = svundef4_u16();        \
                                                              \
        svld4ub_u16(v_తోక_Pred,                                \
                    (uint8_t *)pw_ఆధారం,                      \
                    &v_ఆధారం_Low16x4,                          \
                    &v_ఆధారం_High16x4);                        \
                                                              \
        svld4ub_u16(v_తోక_Pred,                                \
                    (uint8_t *)pw_లక్ష్యం,                      \
                    &v_లక్ష్యం_Low16x4,                          \
                    &v_లక్ష్యం_High16x4);                        \
                                                              \
        /* process low half */                                \
        ma_sve_chn_iterator(v_ఆధారం_Low16x4, v_లక్ష్యం_Low16x4,   \
                            __VA_ARGS__);                     \
                                                              \
        /* process high half */                               \
        ma_sve_chn_iterator(v_ఆధారం_High16x4, v_లక్ష్యం_High16x4, \
                            __VA_ARGS__);                     \
                                                              \
        svst4ub_u16(v_తోక_Pred,                                \
                    (uint8_t *)pw_లక్ష్యం,                      \
                    v_లక్ష్యం_Low16x4,                           \
                    v_లక్ష్యం_High16x4);                         \
                                                              \
        pw_ఆధారం += sve_iteration_advance;                    \
        pw_లక్ష్యం += sve_iteration_advance;                    \
    }

#నిర్వచించు sdl_sve_rgb32_no_alpha_stride_impl(                   \
    ma_alpha_idx,                                             \
    ma_sve_chn_iterator,                                      \
    ...)                                                      \
    sdl_sve_stride_loop_pixel(uStride, v_తోక_Pred)             \
    {                                                         \
                                                              \
        svuint16x4_t v_ఆధారం_Low16x4 = svundef4_u16();         \
        svuint16x4_t v_ఆధారం_High16x4 = svundef4_u16();        \
                                                              \
        svuint16x4_t v_లక్ష్యం_Low16x4 = svundef4_u16();         \
        svuint16x4_t v_లక్ష్యం_High16x4 = svundef4_u16();        \
                                                              \
        svld4ub_u16(v_తోక_Pred,                                \
                    (uint8_t *)pw_ఆధారం,                      \
                    &v_ఆధారం_Low16x4,                          \
                    &v_ఆధారం_High16x4);                        \
                                                              \
        svld4ub_u16(v_తోక_Pred,                                \
                    (uint8_t *)pw_లక్ష్యం,                      \
                    &v_లక్ష్యం_Low16x4,                          \
                    &v_లక్ష్యం_High16x4);                        \
                                                              \
        v_ఆధారం_Low16x4 = svset4(v_ఆధారం_Low16x4,               \
                                (ma_alpha_idx),               \
                                svdup_u16(0xFF));             \
        v_ఆధారం_High16x4 = svset4(v_ఆధారం_High16x4,             \
                                 (ma_alpha_idx),              \
                                 svdup_u16(0xFF));            \
                                                              \
        /* process low half */                                \
        ma_sve_chn_iterator(v_ఆధారం_Low16x4, v_లక్ష్యం_Low16x4,   \
                            __VA_ARGS__);                     \
                                                              \
        /* process high half */                               \
        ma_sve_chn_iterator(v_ఆధారం_High16x4, v_లక్ష్యం_High16x4, \
                            __VA_ARGS__);                     \
                                                              \
        svst4ub_u16(v_తోక_Pred,                                \
                    (uint8_t *)pw_లక్ష్యం,                      \
                    v_లక్ష్యం_Low16x4,                           \
                    v_లక్ష్యం_High16x4);                         \
                                                              \
        pw_ఆధారం += sve_iteration_advance;                    \
        pw_లక్ష్యం += sve_iteration_advance;                    \
    }

#నిర్వచించు sdl_sve_rgb32_గమ్యం_rgb565_stride_impl(ma_sve_chn_iterator, ...) \
    sdl_sve_stride_loop_pixel(uStride, v_తోక_Pred)                     \
    {                                                                 \
                                                                      \
        svuint16x4_t v_ఆధారం_Low16x4 = svundef4_u16();                 \
        svuint16x4_t v_ఆధారం_High16x4 = svundef4_u16();                \
                                                                      \
        svuint16x3_t v_లక్ష్యం_Low16x3 = svundef3_u16();                 \
        svuint16x3_t v_లక్ష్యం_High16x3 = svundef3_u16();                \
                                                                      \
        svld4ub_u16(v_తోక_Pred,                                        \
                    (uint8_t *)pw_ఆధారం,                              \
                    &v_ఆధారం_Low16x4,                                  \
                    &v_ఆధారం_High16x4);                                \
                                                                      \
        svld3rgb565_u16(v_తోక_Pred,                                    \
                        phw_లక్ష్యం,                                    \
                        &v_లక్ష్యం_Low16x3,                              \
                        &v_లక్ష్యం_High16x3);                            \
                                                                      \
        ma_sve_chn_iterator(v_ఆధారం_Low16x4, v_లక్ష్యం_Low16x3,           \
                            __VA_ARGS__);                             \
                                                                      \
        ma_sve_chn_iterator(v_ఆధారం_High16x4, v_లక్ష్యం_High16x3,         \
                            __VA_ARGS__);                             \
                                                                      \
        svst3rgb565_u16(v_తోక_Pred,                                    \
                        phw_లక్ష్యం,                                    \
                        v_లక్ష్యం_Low16x3,                               \
                        v_లక్ష్యం_High16x3);                             \
                                                                      \
        pw_ఆధారం += sve_iteration_advance;                            \
        phw_లక్ష్యం += sve_iteration_advance;                           \
    }

#నిర్వచించు sdl_sve_rgb32_no_alpha_గమ్యం_rgb565_stride_impl(         \
    ma_alpha_idx,                                             \
    ma_sve_chn_iterator,                                      \
    ...)                                                      \
    sdl_sve_stride_loop_pixel(uStride, v_తోక_Pred)             \
    {                                                         \
                                                              \
        svuint16x4_t v_ఆధారం_Low16x4 = svundef4_u16();         \
        svuint16x4_t v_ఆధారం_High16x4 = svundef4_u16();        \
                                                              \
        svuint16x3_t v_లక్ష్యం_Low16x3 = svundef3_u16();         \
        svuint16x3_t v_లక్ష్యం_High16x3 = svundef3_u16();        \
                                                              \
        svld4ub_u16(v_తోక_Pred,                                \
                    (uint8_t *)pw_ఆధారం,                      \
                    &v_ఆధారం_Low16x4,                          \
                    &v_ఆధారం_High16x4);                        \
                                                              \
        v_ఆధారం_Low16x4 = svset4(v_ఆధారం_Low16x4,               \
                                (ma_alpha_idx),               \
                                svdup_u16(0xFF));             \
        v_ఆధారం_High16x4 = svset4(v_ఆధారం_High16x4,             \
                                 (ma_alpha_idx),              \
                                 svdup_u16(0xFF));            \
                                                              \
        svld3rgb565_u16(v_తోక_Pred,                            \
                        phw_లక్ష్యం,                            \
                        &v_లక్ష్యం_Low16x3,                      \
                        &v_లక్ష్యం_High16x3);                    \
                                                              \
        ma_sve_chn_iterator(v_ఆధారం_Low16x4, v_లక్ష్యం_Low16x3,   \
                            __VA_ARGS__);                     \
                                                              \
        ma_sve_chn_iterator(v_ఆధారం_High16x4, v_లక్ష్యం_High16x3, \
                            __VA_ARGS__);                     \
                                                              \
        svst3rgb565_u16(v_తోక_Pred,                            \
                        phw_లక్ష్యం,                            \
                        v_లక్ష్యం_Low16x3,                       \
                        v_లక్ష్యం_High16x3);                     \
                                                              \
        pw_ఆధారం += sve_iteration_advance;                    \
        phw_లక్ష్యం += sve_iteration_advance;                   \
    }

#నిర్వచితం_కాకపోతే sdl_sve_rgb32_blend_op_fill_alpha
#నిర్వచించు sdl_sve_rgb32_blend_op_fill_alpha(ma_alpha_chn_idx)
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే sdl_sve_rgb32_blend_op_copy_alpha
#నిర్వచించు sdl_sve_rgb32_blend_op_copy_alpha(ma_alpha_chn_idx)
#అయితే_ముగింపు

/*
 * Source: ACCC and CCCA
 */
SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
స్థిర అంతఃవరుస శూన్య sdl_sve_accc_stride_blend_గమ్యం_accc_fill_alpha(
    uint32_t *SDL_RESTRICT pw_ఆధారం,
    uint32_t *SDL_RESTRICT pw_లక్ష్యం,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn,

                              sdl_sve_rgb32_blend_op_fill_alpha(3);

    );
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
స్థిర అంతఃవరుస శూన్య sdl_sve_accc_stride_blend_గమ్యం_accc_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ఆధారం,
    uint32_t *SDL_RESTRICT pw_లక్ష్యం,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn,
                              sdl_sve_rgb32_blend_op_copy_alpha(3););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
స్థిర అంతఃవరుస శూన్య sdl_sve_ccca_stride_blend_గమ్యం_ccca_fill_alpha(
    uint32_t *SDL_RESTRICT pw_ఆధారం,
    uint32_t *SDL_RESTRICT pw_లక్ష్యం,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn,
                              sdl_sve_rgb32_blend_op_fill_alpha(0););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
స్థిర అంతఃవరుస శూన్య sdl_sve_ccca_stride_blend_గమ్యం_ccca_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ఆధారం,
    uint32_t *SDL_RESTRICT pw_లక్ష్యం,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn,

                              sdl_sve_rgb32_blend_op_copy_alpha(0);

    );
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
స్థిర అంతఃవరుస శూన్య sdl_sve_accc_blend_గమ్యం_accc_fill_alpha(
    uint8_t *SDL_RESTRICT pch_ఆధారం,
    size_t u_ఆధారం_Stride,
    uint8_t *SDL_RESTRICT pch_లక్ష్యం,
    size_t u_లక్ష్యం_Stride,
    పూర్ణాంకం n_వెడల్పు,
    పూర్ణాంకం n_ఎత్తు)
{
    అయితే (n_ఎత్తు--) {

        sdl_sve_accc_stride_blend_గమ్యం_accc_fill_alpha(
            (uint32_t *)pch_ఆధారం,
            (uint32_t *)pch_లక్ష్యం,
            n_వెడల్పు);

        pch_ఆధారం += u_ఆధారం_Stride;
        pch_లక్ష్యం += u_లక్ష్యం_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
స్థిర అంతఃవరుస శూన్య sdl_sve_accc_blend_గమ్యం_accc_copy_alpha(
    uint8_t *SDL_RESTRICT pch_ఆధారం,
    size_t u_ఆధారం_Stride,
    uint8_t *SDL_RESTRICT pch_లక్ష్యం,
    size_t u_లక్ష్యం_Stride,
    పూర్ణాంకం n_వెడల్పు,
    పూర్ణాంకం n_ఎత్తు)
{
    అయితే (n_ఎత్తు--) {

        sdl_sve_accc_stride_blend_గమ్యం_accc_copy_alpha(
            (uint32_t *)pch_ఆధారం,
            (uint32_t *)pch_లక్ష్యం,
            n_వెడల్పు);

        pch_ఆధారం += u_ఆధారం_Stride;
        pch_లక్ష్యం += u_లక్ష్యం_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
స్థిర అంతఃవరుస శూన్య sdl_sve_ccca_blend_గమ్యం_ccca_fill_alpha(
    uint8_t *SDL_RESTRICT pch_ఆధారం,
    size_t u_ఆధారం_Stride,
    uint8_t *SDL_RESTRICT pch_లక్ష్యం,
    size_t u_లక్ష్యం_Stride,
    పూర్ణాంకం n_వెడల్పు,
    పూర్ణాంకం n_ఎత్తు)
{
    అయితే (n_ఎత్తు--) {

        sdl_sve_ccca_stride_blend_గమ్యం_ccca_fill_alpha(
            (uint32_t *)pch_ఆధారం,
            (uint32_t *)pch_లక్ష్యం,
            n_వెడల్పు);

        pch_ఆధారం += u_ఆధారం_Stride;
        pch_లక్ష్యం += u_లక్ష్యం_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
స్థిర అంతఃవరుస శూన్య sdl_sve_ccca_blend_గమ్యం_ccca_copy_alpha(
    uint8_t *SDL_RESTRICT pch_ఆధారం,
    size_t u_ఆధారం_Stride,
    uint8_t *SDL_RESTRICT pch_లక్ష్యం,
    size_t u_లక్ష్యం_Stride,
    పూర్ణాంకం n_వెడల్పు,
    పూర్ణాంకం n_ఎత్తు)
{
    అయితే (n_ఎత్తు--) {

        sdl_sve_ccca_stride_blend_గమ్యం_ccca_copy_alpha(
            (uint32_t *)pch_ఆధారం,
            (uint32_t *)pch_లక్ష్యం,
            n_వెడల్పు);

        pch_ఆధారం += u_ఆధారం_Stride;
        pch_లక్ష్యం += u_లక్ష్యం_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
స్థిర అంతఃవరుస శూన్య sdl_sve_a123_stride_blend_గమ్యం_321a_fill_alpha(
    uint32_t *SDL_RESTRICT pw_ఆధారం,
    uint32_t *SDL_RESTRICT pw_లక్ష్యం,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn_src_dst_rev,
                              sdl_sve_rgb32_blend_op_fill_alpha(3);

    );
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
స్థిర అంతఃవరుస శూన్య sdl_sve_a123_stride_blend_గమ్యం_321a_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ఆధారం,
    uint32_t *SDL_RESTRICT pw_లక్ష్యం,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn_src_dst_rev,
                              sdl_sve_rgb32_blend_op_copy_alpha(3);

    );
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
స్థిర అంతఃవరుస శూన్య sdl_sve_a123_blend_గమ్యం_321a_fill_alpha(uint8_t *SDL_RESTRICT pch_ఆధారం,
                                                         size_t u_ఆధారం_Stride,
                                                         uint8_t *SDL_RESTRICT pch_లక్ష్యం,
                                                         size_t u_లక్ష్యం_Stride,
                                                         పూర్ణాంకం n_వెడల్పు,
                                                         పూర్ణాంకం n_ఎత్తు)
{
    అయితే (n_ఎత్తు--) {

        sdl_sve_a123_stride_blend_గమ్యం_321a_fill_alpha((uint32_t *)pch_ఆధారం,
                                                     (uint32_t *)pch_లక్ష్యం,
                                                     n_వెడల్పు);

        pch_ఆధారం += u_ఆధారం_Stride;
        pch_లక్ష్యం += u_లక్ష్యం_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
స్థిర అంతఃవరుస శూన్య sdl_sve_a123_blend_గమ్యం_321a_copy_alpha(uint8_t *SDL_RESTRICT pch_ఆధారం,
                                                         size_t u_ఆధారం_Stride,
                                                         uint8_t *SDL_RESTRICT pch_లక్ష్యం,
                                                         size_t u_లక్ష్యం_Stride,
                                                         పూర్ణాంకం n_వెడల్పు,
                                                         పూర్ణాంకం n_ఎత్తు)
{
    అయితే (n_ఎత్తు--) {

        sdl_sve_a123_stride_blend_గమ్యం_321a_copy_alpha((uint32_t *)pch_ఆధారం,
                                                     (uint32_t *)pch_లక్ష్యం,
                                                     n_వెడల్పు);

        pch_ఆధారం += u_ఆధారం_Stride;
        pch_లక్ష్యం += u_లక్ష్యం_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
స్థిర అంతఃవరుస శూన్య sdl_sve_123a_stride_blend_గమ్యం_a321_fill_alpha(
    uint32_t *SDL_RESTRICT pw_ఆధారం,
    uint32_t *SDL_RESTRICT pw_లక్ష్యం,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn_src_dst_rev,
                              sdl_sve_rgb32_blend_op_fill_alpha(0);

    );
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
స్థిర అంతఃవరుస శూన్య sdl_sve_123a_stride_blend_గమ్యం_a321_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ఆధారం,
    uint32_t *SDL_RESTRICT pw_లక్ష్యం,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn_src_dst_rev,
                              sdl_sve_rgb32_blend_op_copy_alpha(0);

    );
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
స్థిర అంతఃవరుస శూన్య sdl_sve_123a_blend_గమ్యం_a321_fill_alpha(uint8_t *SDL_RESTRICT pch_ఆధారం,
                                                         size_t u_ఆధారం_Stride,
                                                         uint8_t *SDL_RESTRICT pch_లక్ష్యం,
                                                         size_t u_లక్ష్యం_Stride,
                                                         పూర్ణాంకం n_వెడల్పు,
                                                         పూర్ణాంకం n_ఎత్తు)
{
    అయితే (n_ఎత్తు--) {

        sdl_sve_123a_stride_blend_గమ్యం_a321_fill_alpha((uint32_t *)pch_ఆధారం,
                                                     (uint32_t *)pch_లక్ష్యం,
                                                     n_వెడల్పు);

        pch_ఆధారం += u_ఆధారం_Stride;
        pch_లక్ష్యం += u_లక్ష్యం_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
స్థిర అంతఃవరుస శూన్య sdl_sve_123a_blend_గమ్యం_a321_copy_alpha(uint8_t *SDL_RESTRICT pch_ఆధారం,
                                                         size_t u_ఆధారం_Stride,
                                                         uint8_t *SDL_RESTRICT pch_లక్ష్యం,
                                                         size_t u_లక్ష్యం_Stride,
                                                         పూర్ణాంకం n_వెడల్పు,
                                                         పూర్ణాంకం n_ఎత్తు)
{
    అయితే (n_ఎత్తు--) {

        sdl_sve_123a_stride_blend_గమ్యం_a321_copy_alpha((uint32_t *)pch_ఆధారం,
                                                     (uint32_t *)pch_లక్ష్యం,
                                                     n_వెడల్పు);

        pch_ఆధారం += u_ఆధారం_Stride;
        pch_లక్ష్యం += u_లక్ష్యం_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
స్థిర అంతఃవరుస శూన్య sdl_sve_accc_stride_blend_గమ్యం_ccca_fill_alpha(
    uint32_t *SDL_RESTRICT pw_ఆధారం,
    uint32_t *SDL_RESTRICT pw_లక్ష్యం,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn_accc_ccca,
                              sdl_sve_rgb32_blend_op_fill_alpha(3);

    );
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
స్థిర అంతఃవరుస శూన్య sdl_sve_accc_stride_blend_గమ్యం_ccca_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ఆధారం,
    uint32_t *SDL_RESTRICT pw_లక్ష్యం,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn_accc_ccca,
                              sdl_sve_rgb32_blend_op_copy_alpha(3);

    );
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
స్థిర అంతఃవరుస శూన్య sdl_sve_accc_blend_గమ్యం_ccca_fill_alpha(uint8_t *SDL_RESTRICT pch_ఆధారం,
                                                         size_t u_ఆధారం_Stride,
                                                         uint8_t *SDL_RESTRICT pch_లక్ష్యం,
                                                         size_t u_లక్ష్యం_Stride,
                                                         పూర్ణాంకం n_వెడల్పు,
                                                         పూర్ణాంకం n_ఎత్తు)
{
    అయితే (n_ఎత్తు--) {

        sdl_sve_accc_stride_blend_గమ్యం_ccca_fill_alpha((uint32_t *)pch_ఆధారం,
                                                     (uint32_t *)pch_లక్ష్యం,
                                                     n_వెడల్పు);

        pch_ఆధారం += u_ఆధారం_Stride;
        pch_లక్ష్యం += u_లక్ష్యం_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
స్థిర అంతఃవరుస శూన్య sdl_sve_accc_blend_గమ్యం_ccca_copy_alpha(uint8_t *SDL_RESTRICT pch_ఆధారం,
                                                         size_t u_ఆధారం_Stride,
                                                         uint8_t *SDL_RESTRICT pch_లక్ష్యం,
                                                         size_t u_లక్ష్యం_Stride,
                                                         పూర్ణాంకం n_వెడల్పు,
                                                         పూర్ణాంకం n_ఎత్తు)
{
    అయితే (n_ఎత్తు--) {

        sdl_sve_accc_stride_blend_గమ్యం_ccca_copy_alpha((uint32_t *)pch_ఆధారం,
                                                     (uint32_t *)pch_లక్ష్యం,
                                                     n_వెడల్పు);

        pch_ఆధారం += u_ఆధారం_Stride;
        pch_లక్ష్యం += u_లక్ష్యం_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
స్థిర అంతఃవరుస శూన్య sdl_sve_ccca_stride_blend_గమ్యం_accc_fill_alpha(
    uint32_t *SDL_RESTRICT pw_ఆధారం,
    uint32_t *SDL_RESTRICT pw_లక్ష్యం,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn_ccca_accc,
                              sdl_sve_rgb32_blend_op_fill_alpha(0);

    );
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
స్థిర అంతఃవరుస శూన్య sdl_sve_ccca_stride_blend_గమ్యం_accc_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ఆధారం,
    uint32_t *SDL_RESTRICT pw_లక్ష్యం,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn_ccca_accc,
                              sdl_sve_rgb32_blend_op_copy_alpha(0););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
స్థిర అంతఃవరుస శూన్య sdl_sve_ccca_blend_గమ్యం_accc_fill_alpha(uint8_t *SDL_RESTRICT pch_ఆధారం,
                                                         size_t u_ఆధారం_Stride,
                                                         uint8_t *SDL_RESTRICT pch_లక్ష్యం,
                                                         size_t u_లక్ష్యం_Stride,
                                                         పూర్ణాంకం n_వెడల్పు,
                                                         పూర్ణాంకం n_ఎత్తు)
{
    అయితే (n_ఎత్తు--) {

        sdl_sve_ccca_stride_blend_గమ్యం_accc_fill_alpha((uint32_t *)pch_ఆధారం,
                                                     (uint32_t *)pch_లక్ష్యం,
                                                     n_వెడల్పు);

        pch_ఆధారం += u_ఆధారం_Stride;
        pch_లక్ష్యం += u_లక్ష్యం_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
స్థిర అంతఃవరుస శూన్య sdl_sve_ccca_blend_గమ్యం_accc_copy_alpha(uint8_t *SDL_RESTRICT pch_ఆధారం,
                                                         size_t u_ఆధారం_Stride,
                                                         uint8_t *SDL_RESTRICT pch_లక్ష్యం,
                                                         size_t u_లక్ష్యం_Stride,
                                                         పూర్ణాంకం n_వెడల్పు,
                                                         పూర్ణాంకం n_ఎత్తు)
{
    అయితే (n_ఎత్తు--) {

        sdl_sve_ccca_stride_blend_గమ్యం_accc_copy_alpha((uint32_t *)pch_ఆధారం,
                                                     (uint32_t *)pch_లక్ష్యం,
                                                     n_వెడల్పు);

        pch_ఆధారం += u_ఆధారం_Stride;
        pch_లక్ష్యం += u_లక్ష్యం_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
స్థిర అంతఃవరుస శూన్య sdl_sve_a123_stride_blend_గమ్యం_a321_fill_alpha(
    uint32_t *SDL_RESTRICT pw_ఆధారం,
    uint32_t *SDL_RESTRICT pw_లక్ష్యం,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn_a123_a321,
                              sdl_sve_rgb32_blend_op_fill_alpha(3););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
స్థిర అంతఃవరుస శూన్య sdl_sve_a123_stride_blend_గమ్యం_a321_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ఆధారం,
    uint32_t *SDL_RESTRICT pw_లక్ష్యం,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn_a123_a321,
                              sdl_sve_rgb32_blend_op_copy_alpha(3););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
స్థిర అంతఃవరుస శూన్య sdl_sve_a123_blend_గమ్యం_a321_fill_alpha(uint8_t *SDL_RESTRICT pch_ఆధారం,
                                                         size_t u_ఆధారం_Stride,
                                                         uint8_t *SDL_RESTRICT pch_లక్ష్యం,
                                                         size_t u_లక్ష్యం_Stride,
                                                         పూర్ణాంకం n_వెడల్పు,
                                                         పూర్ణాంకం n_ఎత్తు)
{
    అయితే (n_ఎత్తు--) {

        sdl_sve_a123_stride_blend_గమ్యం_a321_fill_alpha((uint32_t *)pch_ఆధారం,
                                                     (uint32_t *)pch_లక్ష్యం,
                                                     n_వెడల్పు);

        pch_ఆధారం += u_ఆధారం_Stride;
        pch_లక్ష్యం += u_లక్ష్యం_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
స్థిర అంతఃవరుస శూన్య sdl_sve_a123_blend_గమ్యం_a321_copy_alpha(uint8_t *SDL_RESTRICT pch_ఆధారం,
                                                         size_t u_ఆధారం_Stride,
                                                         uint8_t *SDL_RESTRICT pch_లక్ష్యం,
                                                         size_t u_లక్ష్యం_Stride,
                                                         పూర్ణాంకం n_వెడల్పు,
                                                         పూర్ణాంకం n_ఎత్తు)
{
    అయితే (n_ఎత్తు--) {

        sdl_sve_a123_stride_blend_గమ్యం_a321_copy_alpha((uint32_t *)pch_ఆధారం,
                                                     (uint32_t *)pch_లక్ష్యం,
                                                     n_వెడల్పు);

        pch_ఆధారం += u_ఆధారం_Stride;
        pch_లక్ష్యం += u_లక్ష్యం_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
స్థిర అంతఃవరుస శూన్య sdl_sve_123a_stride_blend_గమ్యం_321a_fill_alpha(
    uint32_t *SDL_RESTRICT pw_ఆధారం,
    uint32_t *SDL_RESTRICT pw_లక్ష్యం,
    size_t uStride)
{

    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn_123a_321a,
                              sdl_sve_rgb32_blend_op_fill_alpha(0););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
స్థిర అంతఃవరుస శూన్య sdl_sve_123a_stride_blend_గమ్యం_321a_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ఆధారం,
    uint32_t *SDL_RESTRICT pw_లక్ష్యం,
    size_t uStride)
{
    sdl_sve_rgb32_stride_impl(sdl_sve_pixel_u16x4_foreach_chn_123a_321a,
                              sdl_sve_rgb32_blend_op_copy_alpha(0););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
స్థిర అంతఃవరుస శూన్య sdl_sve_123a_blend_గమ్యం_321a_fill_alpha(uint8_t *SDL_RESTRICT pch_ఆధారం,
                                                         size_t u_ఆధారం_Stride,
                                                         uint8_t *SDL_RESTRICT pch_లక్ష్యం,
                                                         size_t u_లక్ష్యం_Stride,
                                                         పూర్ణాంకం n_వెడల్పు,
                                                         పూర్ణాంకం n_ఎత్తు)
{
    అయితే (n_ఎత్తు--) {

        sdl_sve_123a_stride_blend_గమ్యం_321a_fill_alpha((uint32_t *)pch_ఆధారం,
                                                     (uint32_t *)pch_లక్ష్యం,
                                                     n_వెడల్పు);

        pch_ఆధారం += u_ఆధారం_Stride;
        pch_లక్ష్యం += u_లక్ష్యం_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
స్థిర అంతఃవరుస శూన్య sdl_sve_123a_blend_గమ్యం_321a_copy_alpha(uint8_t *SDL_RESTRICT pch_ఆధారం,
                                                         size_t u_ఆధారం_Stride,
                                                         uint8_t *SDL_RESTRICT pch_లక్ష్యం,
                                                         size_t u_లక్ష్యం_Stride,
                                                         పూర్ణాంకం n_వెడల్పు,
                                                         పూర్ణాంకం n_ఎత్తు)
{
    అయితే (n_ఎత్తు--) {

        sdl_sve_123a_stride_blend_గమ్యం_321a_copy_alpha((uint32_t *)pch_ఆధారం,
                                                     (uint32_t *)pch_లక్ష్యం,
                                                     n_వెడల్పు);

        pch_ఆధారం += u_ఆధారం_Stride;
        pch_లక్ష్యం += u_లక్ష్యం_Stride;
    }
}

/*
 * Source: XCCC and CCCX
 */

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
స్థిర అంతఃవరుస శూన్య sdl_sve_xccc_stride_blend_గమ్యం_accc_fill_alpha(
    uint32_t *SDL_RESTRICT pw_ఆధారం,
    uint32_t *SDL_RESTRICT pw_లక్ష్యం,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(3,
                                       sdl_sve_pixel_u16x4_foreach_chn,
                                       sdl_sve_rgb32_blend_op_fill_alpha(3););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
స్థిర అంతఃవరుస శూన్య sdl_sve_xccc_stride_blend_గమ్యం_accc_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ఆధారం,
    uint32_t *SDL_RESTRICT pw_లక్ష్యం,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(3,
                                       sdl_sve_pixel_u16x4_foreach_chn,
                                       sdl_sve_rgb32_blend_op_copy_alpha(3););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
స్థిర అంతఃవరుస శూన్య sdl_sve_cccx_stride_blend_గమ్యం_ccca_fill_alpha(
    uint32_t *SDL_RESTRICT pw_ఆధారం,
    uint32_t *SDL_RESTRICT pw_లక్ష్యం,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(0,
                                       sdl_sve_pixel_u16x4_foreach_chn,
                                       sdl_sve_rgb32_blend_op_fill_alpha(0);

    );
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
స్థిర అంతఃవరుస శూన్య sdl_sve_cccx_stride_blend_గమ్యం_ccca_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ఆధారం,
    uint32_t *SDL_RESTRICT pw_లక్ష్యం,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(0,
                                       sdl_sve_pixel_u16x4_foreach_chn,
                                       sdl_sve_rgb32_blend_op_copy_alpha(0););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
స్థిర అంతఃవరుస శూన్య sdl_sve_xccc_blend_గమ్యం_accc_fill_alpha(
    uint8_t *SDL_RESTRICT pch_ఆధారం,
    size_t u_ఆధారం_Stride,
    uint8_t *SDL_RESTRICT pch_లక్ష్యం,
    size_t u_లక్ష్యం_Stride,
    పూర్ణాంకం n_వెడల్పు,
    పూర్ణాంకం n_ఎత్తు)
{
    అయితే (n_ఎత్తు--) {

        sdl_sve_xccc_stride_blend_గమ్యం_accc_fill_alpha(
            (uint32_t *)pch_ఆధారం,
            (uint32_t *)pch_లక్ష్యం,
            n_వెడల్పు);

        pch_ఆధారం += u_ఆధారం_Stride;
        pch_లక్ష్యం += u_లక్ష్యం_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
స్థిర అంతఃవరుస శూన్య sdl_sve_xccc_blend_గమ్యం_accc_copy_alpha(
    uint8_t *SDL_RESTRICT pch_ఆధారం,
    size_t u_ఆధారం_Stride,
    uint8_t *SDL_RESTRICT pch_లక్ష్యం,
    size_t u_లక్ష్యం_Stride,
    పూర్ణాంకం n_వెడల్పు,
    పూర్ణాంకం n_ఎత్తు)
{
    అయితే (n_ఎత్తు--) {

        sdl_sve_xccc_stride_blend_గమ్యం_accc_copy_alpha(
            (uint32_t *)pch_ఆధారం,
            (uint32_t *)pch_లక్ష్యం,
            n_వెడల్పు);

        pch_ఆధారం += u_ఆధారం_Stride;
        pch_లక్ష్యం += u_లక్ష్యం_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
స్థిర అంతఃవరుస శూన్య sdl_sve_cccx_blend_గమ్యం_ccca_fill_alpha(
    uint8_t *SDL_RESTRICT pch_ఆధారం,
    size_t u_ఆధారం_Stride,
    uint8_t *SDL_RESTRICT pch_లక్ష్యం,
    size_t u_లక్ష్యం_Stride,
    పూర్ణాంకం n_వెడల్పు,
    పూర్ణాంకం n_ఎత్తు)
{
    అయితే (n_ఎత్తు--) {

        sdl_sve_cccx_stride_blend_గమ్యం_ccca_fill_alpha(
            (uint32_t *)pch_ఆధారం,
            (uint32_t *)pch_లక్ష్యం,
            n_వెడల్పు);

        pch_ఆధారం += u_ఆధారం_Stride;
        pch_లక్ష్యం += u_లక్ష్యం_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
స్థిర అంతఃవరుస శూన్య sdl_sve_cccx_blend_గమ్యం_ccca_copy_alpha(
    uint8_t *SDL_RESTRICT pch_ఆధారం,
    size_t u_ఆధారం_Stride,
    uint8_t *SDL_RESTRICT pch_లక్ష్యం,
    size_t u_లక్ష్యం_Stride,
    పూర్ణాంకం n_వెడల్పు,
    పూర్ణాంకం n_ఎత్తు)
{
    అయితే (n_ఎత్తు--) {

        sdl_sve_cccx_stride_blend_గమ్యం_ccca_copy_alpha(
            (uint32_t *)pch_ఆధారం,
            (uint32_t *)pch_లక్ష్యం,
            n_వెడల్పు);

        pch_ఆధారం += u_ఆధారం_Stride;
        pch_లక్ష్యం += u_లక్ష్యం_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
స్థిర అంతఃవరుస శూన్య sdl_sve_x123_stride_blend_గమ్యం_321a_fill_alpha(
    uint32_t *SDL_RESTRICT pw_ఆధారం,
    uint32_t *SDL_RESTRICT pw_లక్ష్యం,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(3,
                                       sdl_sve_pixel_u16x4_foreach_chn_src_dst_rev,
                                       sdl_sve_rgb32_blend_op_fill_alpha(3););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
స్థిర అంతఃవరుస శూన్య sdl_sve_x123_stride_blend_గమ్యం_321a_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ఆధారం,
    uint32_t *SDL_RESTRICT pw_లక్ష్యం,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(3,
                                       sdl_sve_pixel_u16x4_foreach_chn_src_dst_rev,
                                       sdl_sve_rgb32_blend_op_copy_alpha(3););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
స్థిర అంతఃవరుస శూన్య sdl_sve_x123_blend_గమ్యం_321a_fill_alpha(uint8_t *SDL_RESTRICT pch_ఆధారం,
                                                         size_t u_ఆధారం_Stride,
                                                         uint8_t *SDL_RESTRICT pch_లక్ష్యం,
                                                         size_t u_లక్ష్యం_Stride,
                                                         పూర్ణాంకం n_వెడల్పు,
                                                         పూర్ణాంకం n_ఎత్తు)
{
    అయితే (n_ఎత్తు--) {

        sdl_sve_x123_stride_blend_గమ్యం_321a_fill_alpha((uint32_t *)pch_ఆధారం,
                                                     (uint32_t *)pch_లక్ష్యం,
                                                     n_వెడల్పు);

        pch_ఆధారం += u_ఆధారం_Stride;
        pch_లక్ష్యం += u_లక్ష్యం_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
స్థిర అంతఃవరుస శూన్య sdl_sve_x123_blend_గమ్యం_321a_copy_alpha(uint8_t *SDL_RESTRICT pch_ఆధారం,
                                                         size_t u_ఆధారం_Stride,
                                                         uint8_t *SDL_RESTRICT pch_లక్ష్యం,
                                                         size_t u_లక్ష్యం_Stride,
                                                         పూర్ణాంకం n_వెడల్పు,
                                                         పూర్ణాంకం n_ఎత్తు)
{
    అయితే (n_ఎత్తు--) {

        sdl_sve_x123_stride_blend_గమ్యం_321a_copy_alpha((uint32_t *)pch_ఆధారం,
                                                     (uint32_t *)pch_లక్ష్యం,
                                                     n_వెడల్పు);

        pch_ఆధారం += u_ఆధారం_Stride;
        pch_లక్ష్యం += u_లక్ష్యం_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
స్థిర అంతఃవరుస శూన్య sdl_sve_123x_stride_blend_గమ్యం_a321_fill_alpha(
    uint32_t *SDL_RESTRICT pw_ఆధారం,
    uint32_t *SDL_RESTRICT pw_లక్ష్యం,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(0,
                                       sdl_sve_pixel_u16x4_foreach_chn_src_dst_rev,
                                       sdl_sve_rgb32_blend_op_fill_alpha(0););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
స్థిర అంతఃవరుస శూన్య sdl_sve_123x_stride_blend_గమ్యం_a321_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ఆధారం,
    uint32_t *SDL_RESTRICT pw_లక్ష్యం,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(0,
                                       sdl_sve_pixel_u16x4_foreach_chn_src_dst_rev,
                                       sdl_sve_rgb32_blend_op_copy_alpha(0););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
స్థిర అంతఃవరుస శూన్య sdl_sve_123x_blend_గమ్యం_a321_fill_alpha(uint8_t *SDL_RESTRICT pch_ఆధారం,
                                                         size_t u_ఆధారం_Stride,
                                                         uint8_t *SDL_RESTRICT pch_లక్ష్యం,
                                                         size_t u_లక్ష్యం_Stride,
                                                         పూర్ణాంకం n_వెడల్పు,
                                                         పూర్ణాంకం n_ఎత్తు)
{
    అయితే (n_ఎత్తు--) {

        sdl_sve_123x_stride_blend_గమ్యం_a321_fill_alpha((uint32_t *)pch_ఆధారం,
                                                     (uint32_t *)pch_లక్ష్యం,
                                                     n_వెడల్పు);

        pch_ఆధారం += u_ఆధారం_Stride;
        pch_లక్ష్యం += u_లక్ష్యం_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
స్థిర అంతఃవరుస శూన్య sdl_sve_123x_blend_గమ్యం_a321_copy_alpha(uint8_t *SDL_RESTRICT pch_ఆధారం,
                                                         size_t u_ఆధారం_Stride,
                                                         uint8_t *SDL_RESTRICT pch_లక్ష్యం,
                                                         size_t u_లక్ష్యం_Stride,
                                                         పూర్ణాంకం n_వెడల్పు,
                                                         పూర్ణాంకం n_ఎత్తు)
{
    అయితే (n_ఎత్తు--) {

        sdl_sve_123x_stride_blend_గమ్యం_a321_copy_alpha((uint32_t *)pch_ఆధారం,
                                                     (uint32_t *)pch_లక్ష్యం,
                                                     n_వెడల్పు);

        pch_ఆధారం += u_ఆధారం_Stride;
        pch_లక్ష్యం += u_లక్ష్యం_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
స్థిర అంతఃవరుస శూన్య sdl_sve_xccc_stride_blend_గమ్యం_ccca_fill_alpha(
    uint32_t *SDL_RESTRICT pw_ఆధారం,
    uint32_t *SDL_RESTRICT pw_లక్ష్యం,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(3,
                                       sdl_sve_pixel_u16x4_foreach_chn_accc_ccca,
                                       sdl_sve_rgb32_blend_op_fill_alpha(3););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
స్థిర అంతఃవరుస శూన్య sdl_sve_xccc_stride_blend_గమ్యం_ccca_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ఆధారం,
    uint32_t *SDL_RESTRICT pw_లక్ష్యం,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(3,
                                       sdl_sve_pixel_u16x4_foreach_chn_accc_ccca,
                                       sdl_sve_rgb32_blend_op_copy_alpha(3););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
స్థిర అంతఃవరుస శూన్య sdl_sve_xccc_blend_గమ్యం_ccca_fill_alpha(uint8_t *SDL_RESTRICT pch_ఆధారం,
                                                         size_t u_ఆధారం_Stride,
                                                         uint8_t *SDL_RESTRICT pch_లక్ష్యం,
                                                         size_t u_లక్ష్యం_Stride,
                                                         పూర్ణాంకం n_వెడల్పు,
                                                         పూర్ణాంకం n_ఎత్తు)
{
    అయితే (n_ఎత్తు--) {

        sdl_sve_xccc_stride_blend_గమ్యం_ccca_fill_alpha((uint32_t *)pch_ఆధారం,
                                                     (uint32_t *)pch_లక్ష్యం,
                                                     n_వెడల్పు);

        pch_ఆధారం += u_ఆధారం_Stride;
        pch_లక్ష్యం += u_లక్ష్యం_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
స్థిర అంతఃవరుస శూన్య sdl_sve_xccc_blend_గమ్యం_ccca_copy_alpha(uint8_t *SDL_RESTRICT pch_ఆధారం,
                                                         size_t u_ఆధారం_Stride,
                                                         uint8_t *SDL_RESTRICT pch_లక్ష్యం,
                                                         size_t u_లక్ష్యం_Stride,
                                                         పూర్ణాంకం n_వెడల్పు,
                                                         పూర్ణాంకం n_ఎత్తు)
{
    అయితే (n_ఎత్తు--) {

        sdl_sve_xccc_stride_blend_గమ్యం_ccca_copy_alpha((uint32_t *)pch_ఆధారం,
                                                     (uint32_t *)pch_లక్ష్యం,
                                                     n_వెడల్పు);

        pch_ఆధారం += u_ఆధారం_Stride;
        pch_లక్ష్యం += u_లక్ష్యం_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
స్థిర అంతఃవరుస శూన్య sdl_sve_cccx_stride_blend_గమ్యం_accc_fill_alpha(
    uint32_t *SDL_RESTRICT pw_ఆధారం,
    uint32_t *SDL_RESTRICT pw_లక్ష్యం,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(0,
                                       sdl_sve_pixel_u16x4_foreach_chn_ccca_accc,
                                       sdl_sve_rgb32_blend_op_fill_alpha(0););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
స్థిర అంతఃవరుస శూన్య sdl_sve_cccx_stride_blend_గమ్యం_accc_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ఆధారం,
    uint32_t *SDL_RESTRICT pw_లక్ష్యం,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(0,
                                       sdl_sve_pixel_u16x4_foreach_chn_ccca_accc,
                                       sdl_sve_rgb32_blend_op_copy_alpha(0););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
స్థిర అంతఃవరుస శూన్య sdl_sve_cccx_blend_గమ్యం_accc_fill_alpha(uint8_t *SDL_RESTRICT pch_ఆధారం,
                                                         size_t u_ఆధారం_Stride,
                                                         uint8_t *SDL_RESTRICT pch_లక్ష్యం,
                                                         size_t u_లక్ష్యం_Stride,
                                                         పూర్ణాంకం n_వెడల్పు,
                                                         పూర్ణాంకం n_ఎత్తు)
{
    అయితే (n_ఎత్తు--) {

        sdl_sve_cccx_stride_blend_గమ్యం_accc_fill_alpha((uint32_t *)pch_ఆధారం,
                                                     (uint32_t *)pch_లక్ష్యం,
                                                     n_వెడల్పు);

        pch_ఆధారం += u_ఆధారం_Stride;
        pch_లక్ష్యం += u_లక్ష్యం_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
స్థిర అంతఃవరుస శూన్య sdl_sve_cccx_blend_గమ్యం_accc_copy_alpha(uint8_t *SDL_RESTRICT pch_ఆధారం,
                                                         size_t u_ఆధారం_Stride,
                                                         uint8_t *SDL_RESTRICT pch_లక్ష్యం,
                                                         size_t u_లక్ష్యం_Stride,
                                                         పూర్ణాంకం n_వెడల్పు,
                                                         పూర్ణాంకం n_ఎత్తు)
{
    అయితే (n_ఎత్తు--) {

        sdl_sve_cccx_stride_blend_గమ్యం_accc_copy_alpha((uint32_t *)pch_ఆధారం,
                                                     (uint32_t *)pch_లక్ష్యం,
                                                     n_వెడల్పు);

        pch_ఆధారం += u_ఆధారం_Stride;
        pch_లక్ష్యం += u_లక్ష్యం_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
స్థిర అంతఃవరుస శూన్య sdl_sve_x123_stride_blend_గమ్యం_a321_fill_alpha(
    uint32_t *SDL_RESTRICT pw_ఆధారం,
    uint32_t *SDL_RESTRICT pw_లక్ష్యం,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(3,
                                       sdl_sve_pixel_u16x4_foreach_chn_a123_a321,
                                       sdl_sve_rgb32_blend_op_fill_alpha(3););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
స్థిర అంతఃవరుస శూన్య sdl_sve_x123_stride_blend_గమ్యం_a321_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ఆధారం,
    uint32_t *SDL_RESTRICT pw_లక్ష్యం,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(3,
                                       sdl_sve_pixel_u16x4_foreach_chn_a123_a321,
                                       sdl_sve_rgb32_blend_op_copy_alpha(3););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
స్థిర అంతఃవరుస శూన్య sdl_sve_x123_blend_గమ్యం_a321_fill_alpha(uint8_t *SDL_RESTRICT pch_ఆధారం,
                                                         size_t u_ఆధారం_Stride,
                                                         uint8_t *SDL_RESTRICT pch_లక్ష్యం,
                                                         size_t u_లక్ష్యం_Stride,
                                                         పూర్ణాంకం n_వెడల్పు,
                                                         పూర్ణాంకం n_ఎత్తు)
{
    అయితే (n_ఎత్తు--) {

        sdl_sve_x123_stride_blend_గమ్యం_a321_fill_alpha((uint32_t *)pch_ఆధారం,
                                                     (uint32_t *)pch_లక్ష్యం,
                                                     n_వెడల్పు);

        pch_ఆధారం += u_ఆధారం_Stride;
        pch_లక్ష్యం += u_లక్ష్యం_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
స్థిర అంతఃవరుస శూన్య sdl_sve_x123_blend_గమ్యం_a321_copy_alpha(uint8_t *SDL_RESTRICT pch_ఆధారం,
                                                         size_t u_ఆధారం_Stride,
                                                         uint8_t *SDL_RESTRICT pch_లక్ష్యం,
                                                         size_t u_లక్ష్యం_Stride,
                                                         పూర్ణాంకం n_వెడల్పు,
                                                         పూర్ణాంకం n_ఎత్తు)
{
    అయితే (n_ఎత్తు--) {

        sdl_sve_x123_stride_blend_గమ్యం_a321_copy_alpha((uint32_t *)pch_ఆధారం,
                                                     (uint32_t *)pch_లక్ష్యం,
                                                     n_వెడల్పు);

        pch_ఆధారం += u_ఆధారం_Stride;
        pch_లక్ష్యం += u_లక్ష్యం_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
స్థిర అంతఃవరుస శూన్య sdl_sve_123x_stride_blend_గమ్యం_321a_fill_alpha(
    uint32_t *SDL_RESTRICT pw_ఆధారం,
    uint32_t *SDL_RESTRICT pw_లక్ష్యం,
    size_t uStride)
{

    sdl_sve_rgb32_no_alpha_stride_impl(0,
                                       sdl_sve_pixel_u16x4_foreach_chn_123a_321a,
                                       sdl_sve_rgb32_blend_op_fill_alpha(0););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
స్థిర అంతఃవరుస శూన్య sdl_sve_123x_stride_blend_గమ్యం_321a_copy_alpha(
    uint32_t *SDL_RESTRICT pw_ఆధారం,
    uint32_t *SDL_RESTRICT pw_లక్ష్యం,
    size_t uStride)
{
    sdl_sve_rgb32_no_alpha_stride_impl(0,
                                       sdl_sve_pixel_u16x4_foreach_chn_123a_321a,
                                       sdl_sve_rgb32_blend_op_copy_alpha(0););
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
స్థిర అంతఃవరుస శూన్య sdl_sve_123x_blend_గమ్యం_321a_fill_alpha(uint8_t *SDL_RESTRICT pch_ఆధారం,
                                                         size_t u_ఆధారం_Stride,
                                                         uint8_t *SDL_RESTRICT pch_లక్ష్యం,
                                                         size_t u_లక్ష్యం_Stride,
                                                         పూర్ణాంకం n_వెడల్పు,
                                                         పూర్ణాంకం n_ఎత్తు)
{
    అయితే (n_ఎత్తు--) {

        sdl_sve_123x_stride_blend_గమ్యం_321a_fill_alpha((uint32_t *)pch_ఆధారం,
                                                     (uint32_t *)pch_లక్ష్యం,
                                                     n_వెడల్పు);

        pch_ఆధారం += u_ఆధారం_Stride;
        pch_లక్ష్యం += u_లక్ష్యం_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
స్థిర అంతఃవరుస శూన్య sdl_sve_123x_blend_గమ్యం_321a_copy_alpha(uint8_t *SDL_RESTRICT pch_ఆధారం,
                                                         size_t u_ఆధారం_Stride,
                                                         uint8_t *SDL_RESTRICT pch_లక్ష్యం,
                                                         size_t u_లక్ష్యం_Stride,
                                                         పూర్ణాంకం n_వెడల్పు,
                                                         పూర్ణాంకం n_ఎత్తు)
{
    అయితే (n_ఎత్తు--) {

        sdl_sve_123x_stride_blend_గమ్యం_321a_copy_alpha((uint32_t *)pch_ఆధారం,
                                                     (uint32_t *)pch_లక్ష్యం,
                                                     n_వెడల్పు);

        pch_ఆధారం += u_ఆధారం_Stride;
        pch_లక్ష్యం += u_లక్ష్యం_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1)
స్థిర అంతఃవరుస శూన్య sdl_sve_8888_గమ్యం_8888_swizzle_dispatcher(SDL_BlitInfo *info)
{
    పూర్ణాంకం వెడల్పు = info->dst_w;
    పూర్ణాంకం ఎత్తు = info->dst_h;
    uint8_t *src = info->src;
    పూర్ణాంకం srcskip = info->src_skip;
    uint8_t *dst = info->dst;
    పూర్ణాంకం dstskip = info->dst_skip;

    స్థిరరాశి SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    స్థిరరాశి SDL_PixelFormatDetails *dstfmt = info->dst_fmt;

    // Set up some basic variables
    పూర్ణాంకం srcbpp = srcfmt->బైట్లు_చొప్పున_pixel;
    పూర్ణాంకం dstbpp = dstfmt->బైట్లు_చొప్పున_pixel;

    ప్రతిజ్ఞా((srcbpp == 4) && (dstbpp == 4));

    bool fill_alpha = (!dstfmt->Amask);

    పూర్ణాంకం srcstride = srcskip + srcbpp * వెడల్పు;
    పూర్ణాంకం dststride = dstskip + dstbpp * వెడల్పు;

    ఎంపిక (srcfmt->format) {
    స్థితి SDL_PIXELFORMAT_XRGB8888:
        ఎంపిక (dstfmt->format) {
        స్థితి SDL_PIXELFORMAT_ARGB8888:
        స్థితి SDL_PIXELFORMAT_XRGB8888:
            ఒకవేళ (fill_alpha) {
                sdl_sve_xccc_blend_గమ్యం_accc_fill_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    వెడల్పు,
                    ఎత్తు);
            } లేకపోతే {
                sdl_sve_xccc_blend_గమ్యం_accc_copy_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    వెడల్పు,
                    ఎత్తు);
            }
            ఆపు;

        స్థితి SDL_PIXELFORMAT_RGBA8888:
        స్థితి SDL_PIXELFORMAT_RGBX8888:
            ఒకవేళ (fill_alpha) {
                sdl_sve_xccc_blend_గమ్యం_ccca_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      వెడల్పు,
                                                      ఎత్తు);
            } లేకపోతే {
                sdl_sve_xccc_blend_గమ్యం_ccca_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      వెడల్పు,
                                                      ఎత్తు);
            }
            ఆపు;

        స్థితి SDL_PIXELFORMAT_ABGR8888:
        స్థితి SDL_PIXELFORMAT_XBGR8888:
            ఒకవేళ (fill_alpha) {
                sdl_sve_x123_blend_గమ్యం_a321_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      వెడల్పు,
                                                      ఎత్తు);
            } లేకపోతే {
                sdl_sve_x123_blend_గమ్యం_a321_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      వెడల్పు,
                                                      ఎత్తు);
            }
            ఆపు;

        స్థితి SDL_PIXELFORMAT_BGRA8888:
        స్థితి SDL_PIXELFORMAT_BGRX8888:
            ఒకవేళ (fill_alpha) {
                sdl_sve_x123_blend_గమ్యం_321a_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      వెడల్పు,
                                                      ఎత్తు);
            } లేకపోతే {
                sdl_sve_x123_blend_గమ్యం_321a_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      వెడల్పు,
                                                      ఎత్తు);
            }
            ఆపు;
        అప్రమేయ:
            ప్రతిజ్ఞా(false);
            ఆపు;
        }
        ఆపు;

    స్థితి SDL_PIXELFORMAT_ARGB8888:
        ఎంపిక (dstfmt->format) {
        స్థితి SDL_PIXELFORMAT_ARGB8888:
        స్థితి SDL_PIXELFORMAT_XRGB8888:
            ఒకవేళ (fill_alpha) {
                sdl_sve_accc_blend_గమ్యం_accc_fill_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    వెడల్పు,
                    ఎత్తు);
            } లేకపోతే {
                sdl_sve_accc_blend_గమ్యం_accc_copy_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    వెడల్పు,
                    ఎత్తు);
            }
            ఆపు;

        స్థితి SDL_PIXELFORMAT_RGBA8888:
        స్థితి SDL_PIXELFORMAT_RGBX8888:
            ఒకవేళ (fill_alpha) {
                sdl_sve_accc_blend_గమ్యం_ccca_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      వెడల్పు,
                                                      ఎత్తు);
            } లేకపోతే {
                sdl_sve_accc_blend_గమ్యం_ccca_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      వెడల్పు,
                                                      ఎత్తు);
            }
            ఆపు;

        స్థితి SDL_PIXELFORMAT_ABGR8888:
        స్థితి SDL_PIXELFORMAT_XBGR8888:
            ఒకవేళ (fill_alpha) {
                sdl_sve_a123_blend_గమ్యం_a321_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      వెడల్పు,
                                                      ఎత్తు);
            } లేకపోతే {
                sdl_sve_a123_blend_గమ్యం_a321_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      వెడల్పు,
                                                      ఎత్తు);
            }
            ఆపు;

        స్థితి SDL_PIXELFORMAT_BGRA8888:
        స్థితి SDL_PIXELFORMAT_BGRX8888:
            ఒకవేళ (fill_alpha) {
                sdl_sve_a123_blend_గమ్యం_321a_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      వెడల్పు,
                                                      ఎత్తు);
            } లేకపోతే {
                sdl_sve_a123_blend_గమ్యం_321a_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      వెడల్పు,
                                                      ఎత్తు);
            }
            ఆపు;
        అప్రమేయ:
            ప్రతిజ్ఞా(false);
            ఆపు;
        }
        ఆపు;

    స్థితి SDL_PIXELFORMAT_RGBX8888:
        ఎంపిక (dstfmt->format) {
        స్థితి SDL_PIXELFORMAT_ARGB8888:
        స్థితి SDL_PIXELFORMAT_XRGB8888:
            ఒకవేళ (fill_alpha) {
                sdl_sve_cccx_blend_గమ్యం_accc_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      వెడల్పు,
                                                      ఎత్తు);
            } లేకపోతే {
                sdl_sve_cccx_blend_గమ్యం_accc_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      వెడల్పు,
                                                      ఎత్తు);
            }
            ఆపు;

        స్థితి SDL_PIXELFORMAT_RGBA8888:
        స్థితి SDL_PIXELFORMAT_RGBX8888:
            ఒకవేళ (fill_alpha) {
                sdl_sve_cccx_blend_గమ్యం_ccca_fill_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    వెడల్పు,
                    ఎత్తు);
            } లేకపోతే {
                sdl_sve_cccx_blend_గమ్యం_ccca_copy_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    వెడల్పు,
                    ఎత్తు);
            }
            ఆపు;

        స్థితి SDL_PIXELFORMAT_ABGR8888:
        స్థితి SDL_PIXELFORMAT_XBGR8888:
            ఒకవేళ (fill_alpha) {
                sdl_sve_123x_blend_గమ్యం_a321_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      వెడల్పు,
                                                      ఎత్తు);
            } లేకపోతే {
                sdl_sve_123x_blend_గమ్యం_a321_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      వెడల్పు,
                                                      ఎత్తు);
            }
            ఆపు;

        స్థితి SDL_PIXELFORMAT_BGRA8888:
        స్థితి SDL_PIXELFORMAT_BGRX8888:
            ఒకవేళ (fill_alpha) {
                sdl_sve_123x_blend_గమ్యం_321a_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      వెడల్పు,
                                                      ఎత్తు);
            } లేకపోతే {
                sdl_sve_123x_blend_గమ్యం_321a_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      వెడల్పు,
                                                      ఎత్తు);
            }
            ఆపు;
        అప్రమేయ:
            ప్రతిజ్ఞా(false);
            ఆపు;
        }
        ఆపు;

    స్థితి SDL_PIXELFORMAT_RGBA8888:
        ఎంపిక (dstfmt->format) {
        స్థితి SDL_PIXELFORMAT_ARGB8888:
        స్థితి SDL_PIXELFORMAT_XRGB8888:
            ఒకవేళ (fill_alpha) {
                sdl_sve_ccca_blend_గమ్యం_accc_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      వెడల్పు,
                                                      ఎత్తు);
            } లేకపోతే {
                sdl_sve_ccca_blend_గమ్యం_accc_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      వెడల్పు,
                                                      ఎత్తు);
            }
            ఆపు;

        స్థితి SDL_PIXELFORMAT_RGBA8888:
        స్థితి SDL_PIXELFORMAT_RGBX8888:
            ఒకవేళ (fill_alpha) {
                sdl_sve_ccca_blend_గమ్యం_ccca_fill_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    వెడల్పు,
                    ఎత్తు);
            } లేకపోతే {
                sdl_sve_ccca_blend_గమ్యం_ccca_copy_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    వెడల్పు,
                    ఎత్తు);
            }
            ఆపు;

        స్థితి SDL_PIXELFORMAT_ABGR8888:
        స్థితి SDL_PIXELFORMAT_XBGR8888:
            ఒకవేళ (fill_alpha) {
                sdl_sve_123a_blend_గమ్యం_a321_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      వెడల్పు,
                                                      ఎత్తు);
            } లేకపోతే {
                sdl_sve_123a_blend_గమ్యం_a321_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      వెడల్పు,
                                                      ఎత్తు);
            }
            ఆపు;

        స్థితి SDL_PIXELFORMAT_BGRA8888:
        స్థితి SDL_PIXELFORMAT_BGRX8888:
            ఒకవేళ (fill_alpha) {
                sdl_sve_123a_blend_గమ్యం_321a_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      వెడల్పు,
                                                      ఎత్తు);
            } లేకపోతే {
                sdl_sve_123a_blend_గమ్యం_321a_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      వెడల్పు,
                                                      ఎత్తు);
            }
            ఆపు;
        అప్రమేయ:
            ప్రతిజ్ఞా(false);
            ఆపు;
        }
        ఆపు;

    స్థితి SDL_PIXELFORMAT_XBGR8888:
        ఎంపిక (dstfmt->format) {
        స్థితి SDL_PIXELFORMAT_ARGB8888:
        స్థితి SDL_PIXELFORMAT_XRGB8888:
            ఒకవేళ (fill_alpha) {
                sdl_sve_x123_blend_గమ్యం_a321_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      వెడల్పు,
                                                      ఎత్తు);
            } లేకపోతే {
                sdl_sve_x123_blend_గమ్యం_a321_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      వెడల్పు,
                                                      ఎత్తు);
            }
            ఆపు;

        స్థితి SDL_PIXELFORMAT_RGBA8888:
        స్థితి SDL_PIXELFORMAT_RGBX8888:
            ఒకవేళ (fill_alpha) {
                sdl_sve_x123_blend_గమ్యం_321a_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      వెడల్పు,
                                                      ఎత్తు);
            } లేకపోతే {
                sdl_sve_x123_blend_గమ్యం_321a_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      వెడల్పు,
                                                      ఎత్తు);
            }
            ఆపు;

        స్థితి SDL_PIXELFORMAT_ABGR8888:
        స్థితి SDL_PIXELFORMAT_XBGR8888:
            ఒకవేళ (fill_alpha) {
                sdl_sve_xccc_blend_గమ్యం_accc_fill_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    వెడల్పు,
                    ఎత్తు);
            } లేకపోతే {
                sdl_sve_xccc_blend_గమ్యం_accc_copy_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    వెడల్పు,
                    ఎత్తు);
            }
            ఆపు;

        స్థితి SDL_PIXELFORMAT_BGRA8888:
        స్థితి SDL_PIXELFORMAT_BGRX8888:
            ఒకవేళ (fill_alpha) {
                sdl_sve_xccc_blend_గమ్యం_ccca_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      వెడల్పు,
                                                      ఎత్తు);
            } లేకపోతే {
                sdl_sve_xccc_blend_గమ్యం_ccca_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      వెడల్పు,
                                                      ఎత్తు);
            }
            ఆపు;
        అప్రమేయ:
            ప్రతిజ్ఞా(false);
            ఆపు;
        }
        ఆపు;

    స్థితి SDL_PIXELFORMAT_ABGR8888:
        ఎంపిక (dstfmt->format) {
        స్థితి SDL_PIXELFORMAT_ARGB8888:
        స్థితి SDL_PIXELFORMAT_XRGB8888:
            ఒకవేళ (fill_alpha) {
                sdl_sve_a123_blend_గమ్యం_a321_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      వెడల్పు,
                                                      ఎత్తు);
            } లేకపోతే {
                sdl_sve_a123_blend_గమ్యం_a321_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      వెడల్పు,
                                                      ఎత్తు);
            }
            ఆపు;

        స్థితి SDL_PIXELFORMAT_RGBA8888:
        స్థితి SDL_PIXELFORMAT_RGBX8888:
            ఒకవేళ (fill_alpha) {
                sdl_sve_a123_blend_గమ్యం_321a_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      వెడల్పు,
                                                      ఎత్తు);
            } లేకపోతే {
                sdl_sve_a123_blend_గమ్యం_321a_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      వెడల్పు,
                                                      ఎత్తు);
            }
            ఆపు;

        స్థితి SDL_PIXELFORMAT_ABGR8888:
        స్థితి SDL_PIXELFORMAT_XBGR8888:
            ఒకవేళ (fill_alpha) {
                sdl_sve_accc_blend_గమ్యం_accc_fill_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    వెడల్పు,
                    ఎత్తు);
            } లేకపోతే {
                sdl_sve_accc_blend_గమ్యం_accc_copy_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    వెడల్పు,
                    ఎత్తు);
            }
            ఆపు;

        స్థితి SDL_PIXELFORMAT_BGRA8888:
        స్థితి SDL_PIXELFORMAT_BGRX8888:
            ఒకవేళ (fill_alpha) {
                sdl_sve_accc_blend_గమ్యం_ccca_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      వెడల్పు,
                                                      ఎత్తు);
            } లేకపోతే {
                sdl_sve_accc_blend_గమ్యం_ccca_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      వెడల్పు,
                                                      ఎత్తు);
            }
            ఆపు;
        అప్రమేయ:
            ప్రతిజ్ఞా(false);
            ఆపు;
        }
        ఆపు;

    స్థితి SDL_PIXELFORMAT_BGRX8888:
        ఎంపిక (dstfmt->format) {
        స్థితి SDL_PIXELFORMAT_ARGB8888:
        స్థితి SDL_PIXELFORMAT_XRGB8888:
            ఒకవేళ (fill_alpha) {
                sdl_sve_123x_blend_గమ్యం_a321_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      వెడల్పు,
                                                      ఎత్తు);
            } లేకపోతే {
                sdl_sve_123x_blend_గమ్యం_a321_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      వెడల్పు,
                                                      ఎత్తు);
            }
            ఆపు;

        స్థితి SDL_PIXELFORMAT_RGBA8888:
        స్థితి SDL_PIXELFORMAT_RGBX8888:
            ఒకవేళ (fill_alpha) {
                sdl_sve_123x_blend_గమ్యం_321a_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      వెడల్పు,
                                                      ఎత్తు);
            } లేకపోతే {
                sdl_sve_123x_blend_గమ్యం_321a_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      వెడల్పు,
                                                      ఎత్తు);
            }
            ఆపు;

        స్థితి SDL_PIXELFORMAT_ABGR8888:
        స్థితి SDL_PIXELFORMAT_XBGR8888:
            ఒకవేళ (fill_alpha) {
                sdl_sve_cccx_blend_గమ్యం_accc_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      వెడల్పు,
                                                      ఎత్తు);
            } లేకపోతే {
                sdl_sve_cccx_blend_గమ్యం_accc_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      వెడల్పు,
                                                      ఎత్తు);
            }
            ఆపు;

        స్థితి SDL_PIXELFORMAT_BGRA8888:
        స్థితి SDL_PIXELFORMAT_BGRX8888:
            ఒకవేళ (fill_alpha) {
                sdl_sve_cccx_blend_గమ్యం_ccca_fill_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    వెడల్పు,
                    ఎత్తు);
            } లేకపోతే {
                sdl_sve_cccx_blend_గమ్యం_ccca_copy_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    వెడల్పు,
                    ఎత్తు);
            }
            ఆపు;
        అప్రమేయ:
            ప్రతిజ్ఞా(false);
            ఆపు;
        }
        ఆపు;

    స్థితి SDL_PIXELFORMAT_BGRA8888:
        ఎంపిక (dstfmt->format) {
        స్థితి SDL_PIXELFORMAT_ARGB8888:
        స్థితి SDL_PIXELFORMAT_XRGB8888:
            ఒకవేళ (fill_alpha) {
                sdl_sve_123a_blend_గమ్యం_a321_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      వెడల్పు,
                                                      ఎత్తు);
            } లేకపోతే {
                sdl_sve_123a_blend_గమ్యం_a321_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      వెడల్పు,
                                                      ఎత్తు);
            }
            ఆపు;

        స్థితి SDL_PIXELFORMAT_RGBA8888:
        స్థితి SDL_PIXELFORMAT_RGBX8888:
            ఒకవేళ (fill_alpha) {
                sdl_sve_123a_blend_గమ్యం_321a_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      వెడల్పు,
                                                      ఎత్తు);
            } లేకపోతే {
                sdl_sve_123a_blend_గమ్యం_321a_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      వెడల్పు,
                                                      ఎత్తు);
            }
            ఆపు;

        స్థితి SDL_PIXELFORMAT_ABGR8888:
        స్థితి SDL_PIXELFORMAT_XBGR8888:
            ఒకవేళ (fill_alpha) {
                sdl_sve_ccca_blend_గమ్యం_accc_fill_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      వెడల్పు,
                                                      ఎత్తు);
            } లేకపోతే {
                sdl_sve_ccca_blend_గమ్యం_accc_copy_alpha(src,
                                                      srcstride,
                                                      dst,
                                                      dststride,
                                                      వెడల్పు,
                                                      ఎత్తు);
            }
            ఆపు;

        స్థితి SDL_PIXELFORMAT_BGRA8888:
        స్థితి SDL_PIXELFORMAT_BGRX8888:
            ఒకవేళ (fill_alpha) {
                sdl_sve_ccca_blend_గమ్యం_ccca_fill_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    వెడల్పు,
                    ఎత్తు);
            } లేకపోతే {
                sdl_sve_ccca_blend_గమ్యం_ccca_copy_alpha(
                    src,
                    srcstride,
                    dst,
                    dststride,
                    వెడల్పు,
                    ఎత్తు);
            }
            ఆపు;
        అప్రమేయ:
            ప్రతిజ్ఞా(false);
            ఆపు;
        }
        ఆపు;

    అప్రమేయ:
        ప్రతిజ్ఞా(false);
        ఆపు;
    }
}

#నిర్వచితం_కాకపోతే sdl_sve_rgb32_blend_గమ్యం_rgb565_op
#నిర్వచించు sdl_sve_rgb32_blend_గమ్యం_rgb565_op(ma_alpha_chn_idx)
#అయితే_ముగింపు

/*
 * ACCC or CCCA
 */
SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
స్థిర అంతఃవరుస శూన్య sdl_sve_argb8888_stride_blend_గమ్యం_rgb565(uint32_t *SDL_RESTRICT pw_ఆధారం,
                                                           uint16_t *SDL_RESTRICT phw_లక్ష్యం,
                                                           size_t uStride)
{
    sdl_sve_rgb32_గమ్యం_rgb565_stride_impl(
        sdl_sve_pixel_u16x4_foreach_chn_argb_rgb565,
        {
            sdl_sve_rgb32_blend_గమ్యం_rgb565_op(3);
        });
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
స్థిర అంతఃవరుస శూన్య sdl_sve_argb8888_blend_గమ్యం_rgb565(uint8_t *SDL_RESTRICT pch_ఆధారం,
                                                    size_t u_ఆధారం_Stride,
                                                    uint8_t *SDL_RESTRICT pch_లక్ష్యం,
                                                    size_t u_లక్ష్యం_Stride,
                                                    పూర్ణాంకం n_వెడల్పు,
                                                    పూర్ణాంకం n_ఎత్తు)
{
    అయితే (n_ఎత్తు--) {

        sdl_sve_argb8888_stride_blend_గమ్యం_rgb565((uint32_t *)pch_ఆధారం,
                                                (uint16_t *)pch_లక్ష్యం,
                                                n_వెడల్పు);

        pch_ఆధారం += u_ఆధారం_Stride;
        pch_లక్ష్యం += u_లక్ష్యం_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
స్థిర అంతఃవరుస శూన్య sdl_sve_rgba8888_stride_blend_గమ్యం_rgb565(uint32_t *SDL_RESTRICT pw_ఆధారం,
                                                           uint16_t *SDL_RESTRICT phw_లక్ష్యం,
                                                           size_t uStride)
{
    sdl_sve_rgb32_గమ్యం_rgb565_stride_impl(
        sdl_sve_pixel_u16x4_foreach_chn_rgba_rgb565,
        {
            sdl_sve_rgb32_blend_గమ్యం_rgb565_op(0);
        });
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
స్థిర అంతఃవరుస శూన్య sdl_sve_rgba8888_blend_గమ్యం_rgb565(uint8_t *SDL_RESTRICT pch_ఆధారం,
                                                    size_t u_ఆధారం_Stride,
                                                    uint8_t *SDL_RESTRICT pch_లక్ష్యం,
                                                    size_t u_లక్ష్యం_Stride,
                                                    పూర్ణాంకం n_వెడల్పు,
                                                    పూర్ణాంకం n_ఎత్తు)
{
    అయితే (n_ఎత్తు--) {

        sdl_sve_rgba8888_stride_blend_గమ్యం_rgb565((uint32_t *)pch_ఆధారం,
                                                (uint16_t *)pch_లక్ష్యం,
                                                n_వెడల్పు);

        pch_ఆధారం += u_ఆధారం_Stride;
        pch_లక్ష్యం += u_లక్ష్యం_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
స్థిర అంతఃవరుస శూన్య sdl_sve_bgra8888_stride_blend_గమ్యం_rgb565(uint32_t *SDL_RESTRICT pw_ఆధారం,
                                                           uint16_t *SDL_RESTRICT phw_లక్ష్యం,
                                                           size_t uStride)
{
    sdl_sve_rgb32_గమ్యం_rgb565_stride_impl(
        sdl_sve_pixel_u16x4_foreach_chn_bgra_rgb565,
        {
            sdl_sve_rgb32_blend_గమ్యం_rgb565_op(0);
        });
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
స్థిర అంతఃవరుస శూన్య sdl_sve_bgra8888_blend_గమ్యం_rgb565(uint8_t *SDL_RESTRICT pch_ఆధారం,
                                                    size_t u_ఆధారం_Stride,
                                                    uint8_t *SDL_RESTRICT pch_లక్ష్యం,
                                                    size_t u_లక్ష్యం_Stride,
                                                    పూర్ణాంకం n_వెడల్పు,
                                                    పూర్ణాంకం n_ఎత్తు)
{
    అయితే (n_ఎత్తు--) {

        sdl_sve_bgra8888_stride_blend_గమ్యం_rgb565((uint32_t *)pch_ఆధారం,
                                                (uint16_t *)pch_లక్ష్యం,
                                                n_వెడల్పు);

        pch_ఆధారం += u_ఆధారం_Stride;
        pch_లక్ష్యం += u_లక్ష్యం_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
స్థిర అంతఃవరుస శూన్య sdl_sve_abgr8888_stride_blend_గమ్యం_rgb565(uint32_t *SDL_RESTRICT pw_ఆధారం,
                                                           uint16_t *SDL_RESTRICT phw_లక్ష్యం,
                                                           size_t uStride)
{
    sdl_sve_rgb32_గమ్యం_rgb565_stride_impl(
        sdl_sve_pixel_u16x4_foreach_chn_abgr_rgb565,
        {
            sdl_sve_rgb32_blend_గమ్యం_rgb565_op(3);
        });
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
స్థిర అంతఃవరుస శూన్య sdl_sve_abgr8888_blend_గమ్యం_rgb565(uint8_t *SDL_RESTRICT pch_ఆధారం,
                                                    size_t u_ఆధారం_Stride,
                                                    uint8_t *SDL_RESTRICT pch_లక్ష్యం,
                                                    size_t u_లక్ష్యం_Stride,
                                                    పూర్ణాంకం n_వెడల్పు,
                                                    పూర్ణాంకం n_ఎత్తు)
{
    అయితే (n_ఎత్తు--) {

        sdl_sve_abgr8888_stride_blend_గమ్యం_rgb565((uint32_t *)pch_ఆధారం,
                                                (uint16_t *)pch_లక్ష్యం,
                                                n_వెడల్పు);

        pch_ఆధారం += u_ఆధారం_Stride;
        pch_లక్ష్యం += u_లక్ష్యం_Stride;
    }
}

/*
 * XCCC or CCCX
 */
SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
స్థిర అంతఃవరుస శూన్య sdl_sve_xrgb8888_stride_blend_గమ్యం_rgb565(uint32_t *SDL_RESTRICT pw_ఆధారం,
                                                           uint16_t *SDL_RESTRICT phw_లక్ష్యం,
                                                           size_t uStride)
{
    sdl_sve_rgb32_no_alpha_గమ్యం_rgb565_stride_impl(
        3,
        sdl_sve_pixel_u16x4_foreach_chn_argb_rgb565,
        {
            sdl_sve_rgb32_blend_గమ్యం_rgb565_op(3);
        });
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
స్థిర అంతఃవరుస శూన్య sdl_sve_xrgb8888_blend_గమ్యం_rgb565(uint8_t *SDL_RESTRICT pch_ఆధారం,
                                                    size_t u_ఆధారం_Stride,
                                                    uint8_t *SDL_RESTRICT pch_లక్ష్యం,
                                                    size_t u_లక్ష్యం_Stride,
                                                    పూర్ణాంకం n_వెడల్పు,
                                                    పూర్ణాంకం n_ఎత్తు)
{
    అయితే (n_ఎత్తు--) {

        sdl_sve_xrgb8888_stride_blend_గమ్యం_rgb565((uint32_t *)pch_ఆధారం,
                                                (uint16_t *)pch_లక్ష్యం,
                                                n_వెడల్పు);

        pch_ఆధారం += u_ఆధారం_Stride;
        pch_లక్ష్యం += u_లక్ష్యం_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
స్థిర అంతఃవరుస శూన్య sdl_sve_rgbx8888_stride_blend_గమ్యం_rgb565(uint32_t *SDL_RESTRICT pw_ఆధారం,
                                                           uint16_t *SDL_RESTRICT phw_లక్ష్యం,
                                                           size_t uStride)
{
    sdl_sve_rgb32_no_alpha_గమ్యం_rgb565_stride_impl(
        0,
        sdl_sve_pixel_u16x4_foreach_chn_rgba_rgb565,
        {
            sdl_sve_rgb32_blend_గమ్యం_rgb565_op(0);
        });
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
స్థిర అంతఃవరుస శూన్య sdl_sve_rgbx8888_blend_గమ్యం_rgb565(uint8_t *SDL_RESTRICT pch_ఆధారం,
                                                    size_t u_ఆధారం_Stride,
                                                    uint8_t *SDL_RESTRICT pch_లక్ష్యం,
                                                    size_t u_లక్ష్యం_Stride,
                                                    పూర్ణాంకం n_వెడల్పు,
                                                    పూర్ణాంకం n_ఎత్తు)
{
    అయితే (n_ఎత్తు--) {

        sdl_sve_rgbx8888_stride_blend_గమ్యం_rgb565((uint32_t *)pch_ఆధారం,
                                                (uint16_t *)pch_లక్ష్యం,
                                                n_వెడల్పు);

        pch_ఆధారం += u_ఆధారం_Stride;
        pch_లక్ష్యం += u_లక్ష్యం_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
స్థిర అంతఃవరుస శూన్య sdl_sve_bgrx8888_stride_blend_గమ్యం_rgb565(uint32_t *SDL_RESTRICT pw_ఆధారం,
                                                           uint16_t *SDL_RESTRICT phw_లక్ష్యం,
                                                           size_t uStride)
{
    sdl_sve_rgb32_no_alpha_గమ్యం_rgb565_stride_impl(
        0,
        sdl_sve_pixel_u16x4_foreach_chn_bgra_rgb565,
        {
            sdl_sve_rgb32_blend_గమ్యం_rgb565_op(0);
        });
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
స్థిర అంతఃవరుస శూన్య sdl_sve_bgrx8888_blend_గమ్యం_rgb565(uint8_t *SDL_RESTRICT pch_ఆధారం,
                                                    size_t u_ఆధారం_Stride,
                                                    uint8_t *SDL_RESTRICT pch_లక్ష్యం,
                                                    size_t u_లక్ష్యం_Stride,
                                                    పూర్ణాంకం n_వెడల్పు,
                                                    పూర్ణాంకం n_ఎత్తు)
{
    అయితే (n_ఎత్తు--) {

        sdl_sve_bgrx8888_stride_blend_గమ్యం_rgb565((uint32_t *)pch_ఆధారం,
                                                (uint16_t *)pch_లక్ష్యం,
                                                n_వెడల్పు);

        pch_ఆధారం += u_ఆధారం_Stride;
        pch_లక్ష్యం += u_లక్ష్యం_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 2)
స్థిర అంతఃవరుస శూన్య sdl_sve_xbgr8888_stride_blend_గమ్యం_rgb565(uint32_t *SDL_RESTRICT pw_ఆధారం,
                                                           uint16_t *SDL_RESTRICT phw_లక్ష్యం,
                                                           size_t uStride)
{
    sdl_sve_rgb32_no_alpha_గమ్యం_rgb565_stride_impl(
        3,
        sdl_sve_pixel_u16x4_foreach_chn_abgr_rgb565,
        {
            sdl_sve_rgb32_blend_గమ్యం_rgb565_op(3);
        });
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1, 3)
స్థిర అంతఃవరుస శూన్య sdl_sve_xbgr8888_blend_గమ్యం_rgb565(uint8_t *SDL_RESTRICT pch_ఆధారం,
                                                    size_t u_ఆధారం_Stride,
                                                    uint8_t *SDL_RESTRICT pch_లక్ష్యం,
                                                    size_t u_లక్ష్యం_Stride,
                                                    పూర్ణాంకం n_వెడల్పు,
                                                    పూర్ణాంకం n_ఎత్తు)
{
    అయితే (n_ఎత్తు--) {

        sdl_sve_xbgr8888_stride_blend_గమ్యం_rgb565((uint32_t *)pch_ఆధారం,
                                                (uint16_t *)pch_లక్ష్యం,
                                                n_వెడల్పు);

        pch_ఆధారం += u_ఆధారం_Stride;
        pch_లక్ష్యం += u_లక్ష్యం_Stride;
    }
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(1)
స్థిర అంతఃవరుస శూన్య sdl_sve_rgb32_గమ్యం_rgb565_swizzle_dispatcher(SDL_BlitInfo *info)
{
    పూర్ణాంకం వెడల్పు = info->dst_w;
    పూర్ణాంకం ఎత్తు = info->dst_h;
    uint8_t *src = info->src;
    పూర్ణాంకం srcskip = info->src_skip;
    uint8_t *dst = info->dst;
    పూర్ణాంకం dstskip = info->dst_skip;

    స్థిరరాశి SDL_PixelFormatDetails *srcfmt = info->src_fmt;
    స్థిరరాశి SDL_PixelFormatDetails *dstfmt = info->dst_fmt;

    // Set up some basic variables
    పూర్ణాంకం srcbpp = srcfmt->బైట్లు_చొప్పున_pixel;
    పూర్ణాంకం dstbpp = dstfmt->బైట్లు_చొప్పున_pixel;

    ప్రతిజ్ఞా(srcbpp == 4);
    ప్రతిజ్ఞా(dstbpp == 2);

    పూర్ణాంకం srcstride = srcskip + srcbpp * వెడల్పు;
    పూర్ణాంకం dststride = dstskip + dstbpp * వెడల్పు;

    ఎంపిక (srcfmt->format) {
    స్థితి SDL_PIXELFORMAT_XRGB8888:
        sdl_sve_xrgb8888_blend_గమ్యం_rgb565(src,
                                         srcstride,
                                         dst,
                                         dststride,
                                         వెడల్పు,
                                         ఎత్తు);
        ఆపు;

    స్థితి SDL_PIXELFORMAT_ARGB8888:
        sdl_sve_argb8888_blend_గమ్యం_rgb565(src,
                                         srcstride,
                                         dst,
                                         dststride,
                                         వెడల్పు,
                                         ఎత్తు);
        ఆపు;

    స్థితి SDL_PIXELFORMAT_RGBX8888:
        sdl_sve_rgbx8888_blend_గమ్యం_rgb565(src,
                                         srcstride,
                                         dst,
                                         dststride,
                                         వెడల్పు,
                                         ఎత్తు);
        ఆపు;

    స్థితి SDL_PIXELFORMAT_RGBA8888:
        sdl_sve_rgba8888_blend_గమ్యం_rgb565(src,
                                         srcstride,
                                         dst,
                                         dststride,
                                         వెడల్పు,
                                         ఎత్తు);
        ఆపు;

    స్థితి SDL_PIXELFORMAT_XBGR8888:
        sdl_sve_xbgr8888_blend_గమ్యం_rgb565(src,
                                         srcstride,
                                         dst,
                                         dststride,
                                         వెడల్పు,
                                         ఎత్తు);
        ఆపు;

    స్థితి SDL_PIXELFORMAT_ABGR8888:
        sdl_sve_abgr8888_blend_గమ్యం_rgb565(src,
                                         srcstride,
                                         dst,
                                         dststride,
                                         వెడల్పు,
                                         ఎత్తు);
        ఆపు;

    స్థితి SDL_PIXELFORMAT_BGRX8888:
        sdl_sve_bgrx8888_blend_గమ్యం_rgb565(src,
                                         srcstride,
                                         dst,
                                         dststride,
                                         వెడల్పు,
                                         ఎత్తు);
        ఆపు;

    స్థితి SDL_PIXELFORMAT_BGRA8888:
        sdl_sve_bgra8888_blend_గమ్యం_rgb565(src,
                                         srcstride,
                                         dst,
                                         dststride,
                                         వెడల్పు,
                                         ఎత్తు);
        ఆపు;

    అప్రమేయ:
        ప్రతిజ్ఞా(false);
        ఆపు;
    }
}

#అయితే_ముగింపు /* SD_SVE2_SWIZZLE_H */