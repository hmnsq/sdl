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

#यदि !defined(SDL_SVE2_EXTENSION_H) //&& (defined(__ARM_FEATURE_SVE2) && __ARM_FEATURE_SVE2)
#define SDL_SVE2_EXTENSION_H

#अन्तर्भाव "SDL_sve2_util.h"

/*
 * NOTE: Some Android builds didn't attach '-march=armv8-a+sve2' to
 *       SDL_sve2_*.c and hence the macro __ARM_FEATURE_SVE is not
 *       defined by the compiler. This might not be a problem as the
 *       SDL_TARGETING("arch=armv8-a+sve2") enables the feature for
 *       individual functions, until some version of compilers
 *       provides arm_sve.h raising errors then __ARM_FEATURE_SVE
 *       is not defined. Although it should be avoided, as a
 *       workaround, we have to define the __ARM_FEATURE_SVE here as
 *       an ugly hack.
 */
#ifdef SDL_PLATFORM_ANDROID
#ifndef __ARM_FEATURE_SVE
#define __ARM_FEATURE_SVE 1
#endif
#endif
#अन्तर्भाव <arm_sve.h>
#अन्तर्भाव <stdint.h>

/*!
 * \brief a wrapper for __attribute__((nonnull))
 */
#ifndef ARM_NONNULL
#define ARM_NONNULL(...) __attribute__((nonnull(__VA_ARGS__)))
#endif

#define svlenu8()  svcntb_pat(SV_ALL)
#define svlenu16() (svcntb_pat(SV_ALL) / परिमाण(uint16_t))
#define svlenu32() (svcntb_pat(SV_ALL) / परिमाण(uint32_t))
#define svlenu64() (svcntb_pat(SV_ALL) / परिमाण(uint64_t))

#define svlens8()  svlenu8()
#define svlens16() svlenu16()
#define svlens32() svlenu32()
#define svlens64() svlenu64()

#define sdl_sve_stride_loop_pixel(ma_stride_size, ma_pred_name)          \
    लागि (svbool_t ma_pred_name, *pTemp = &ma_pred_name;                  \
         pTemp != रिक्त;                                                  \
         pTemp = रिक्त)                                                   \
        लागि (माप_प्रकार SVE_SAFE_NAME(n) = 0,                                \
                    sve_iteration_advance = svlenu8();                   \
             ({                                                          \
                 ma_pred_name = svwhilelt_b8((int32_t)SVE_SAFE_NAME(n),  \
                                             (int32_t)(ma_stride_size)); \
                 SVE_SAFE_NAME(n) < (ma_stride_size);                    \
             });                                                         \
             SVE_SAFE_NAME(n) += sve_iteration_advance)

#define sdl_sve_stride_loop_u8 sdl_sve_stride_loop_pixel

#define sdl_sve_stride_loop_u16(ma_stride_size, ma_pred_name)             \
    लागि (svbool_t ma_pred_name, *pTemp = &ma_pred_name;                   \
         pTemp != रिक्त;                                                   \
         pTemp = रिक्त)                                                    \
        लागि (माप_प्रकार SVE_SAFE_NAME(n) = 0,                                 \
                    sve_iteration_advance = svlenu16();                   \
             ({                                                           \
                 ma_pred_name = svwhilelt_b16((int32_t)SVE_SAFE_NAME(n),  \
                                              (int32_t)(ma_stride_size)); \
                 SVE_SAFE_NAME(n) < (ma_stride_size);                     \
             });                                                          \
             SVE_SAFE_NAME(n) += sve_iteration_advance)

#define sdl_sve_stride_loop_u32(ma_stride_size, ma_pred_name)             \
    लागि (svbool_t ma_pred_name, *pTemp = &ma_pred_name;                   \
         pTemp != रिक्त;                                                   \
         pTemp = रिक्त)                                                    \
        लागि (माप_प्रकार SVE_SAFE_NAME(n) = 0,                                 \
                    sve_iteration_advance = svlenu32();                   \
             ({                                                           \
                 ma_pred_name = svwhilelt_b16((int32_t)SVE_SAFE_NAME(n),  \
                                              (int32_t)(ma_stride_size)); \
                 SVE_SAFE_NAME(n) < (ma_stride_size);                     \
             });                                                          \
             SVE_SAFE_NAME(n) += sve_iteration_advance)

#define sdl_sve_pixel_ccc_foreach_chn(ma_source_u16x3,                    \
                                      ma_target_u16x3,                    \
                                      ...)                                \
    गर {                                                                  \
        svuint16x3_t sve_source_u16x3 = ma_source_u16x3;                  \
        (शून्य)sve_source_u16x3;                                           \
        गर {                                                              \
            अचर uint8_t sve_src_chn_idx = 0;                            \
            (शून्य)sve_src_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget3((ma_source_u16x3), 0);     \
            svuint16_t sve_target_u16 = svget3((ma_target_u16x3), 0);     \
            (शून्य)sve_source_u16;                                         \
            (शून्य)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x3 = svset3(ma_target_u16x3, 0, sve_target_u16); \
        } जबसम्म (0);                                                      \
        गर {                                                              \
            अचर uint8_t sve_src_chn_idx = 1;                            \
            (शून्य)sve_src_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget3((ma_source_u16x3), 1);     \
            svuint16_t sve_target_u16 = svget3((ma_target_u16x3), 1);     \
            (शून्य)sve_source_u16;                                         \
            (शून्य)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x3 = svset3(ma_target_u16x3, 1, sve_target_u16); \
        } जबसम्म (0);                                                      \
        गर {                                                              \
            अचर uint8_t sve_src_chn_idx = 2;                            \
            (शून्य)sve_src_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget3((ma_source_u16x3), 2);     \
            svuint16_t sve_target_u16 = svget3((ma_target_u16x3), 2);     \
            (शून्य)sve_source_u16;                                         \
            (शून्य)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x3 = svset3(ma_target_u16x3, 2, sve_target_u16); \
        } जबसम्म (0);                                                      \
    } जबसम्म (0)

#define sdl_sve_pixel_accc_foreach_chn012(ma_source_u16x4,                \
                                          ma_target_u16x4,                \
                                          ...)                            \
    गर {                                                                  \
        svuint16x4_t sve_source_u16x4 = ma_source_u16x4;                  \
        (शून्य)sve_source_u16x4;                                           \
        गर {                                                              \
            अचर uint8_t sve_src_chn_idx = 0;                            \
            (शून्य)sve_src_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 0);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 0);     \
            (शून्य)sve_source_u16;                                         \
            (शून्य)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 0, sve_target_u16); \
        } जबसम्म (0);                                                      \
        गर {                                                              \
            अचर uint8_t sve_src_chn_idx = 1;                            \
            (शून्य)sve_src_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 1);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 1);     \
            (शून्य)sve_source_u16;                                         \
            (शून्य)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 1, sve_target_u16); \
        } जबसम्म (0);                                                      \
        गर {                                                              \
            अचर uint8_t sve_src_chn_idx = 2;                            \
            (शून्य)sve_src_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 2);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 2);     \
            (शून्य)sve_source_u16;                                         \
            (शून्य)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 2, sve_target_u16); \
        } जबसम्म (0);                                                      \
    } जबसम्म (0)

#define sdl_sve_pixel_accc_foreach_chn(ma_source_u16x4,                   \
                                       ma_target_u16x4,                   \
                                       ...)                               \
    गर {                                                                  \
        svuint16x4_t sve_source_u16x4 = ma_source_u16x4;                  \
        (शून्य)sve_source_u16x4;                                           \
        गर {                                                              \
            अचर uint8_t sve_src_chn_idx = 0;                            \
            (शून्य)sve_src_chn_idx;                                        \
            (शून्य)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 0);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 0);     \
            (शून्य)sve_source_u16;                                         \
            (शून्य)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 0, sve_target_u16); \
        } जबसम्म (0);                                                      \
        गर {                                                              \
            अचर uint8_t sve_src_chn_idx = 1;                            \
            (शून्य)sve_src_chn_idx;                                        \
            (शून्य)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 1);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 1);     \
            (शून्य)sve_source_u16;                                         \
            (शून्य)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 1, sve_target_u16); \
        } जबसम्म (0);                                                      \
        गर {                                                              \
            अचर uint8_t sve_src_chn_idx = 2;                            \
            (शून्य)sve_src_chn_idx;                                        \
            (शून्य)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 2);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 2);     \
            (शून्य)sve_source_u16;                                         \
            (शून्य)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 2, sve_target_u16); \
        } जबसम्म (0);                                                      \
        गर {                                                              \
            अचर uint8_t sve_src_chn_idx = 3;                            \
            (शून्य)sve_src_chn_idx;                                        \
            (शून्य)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 3);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 3);     \
            (शून्य)sve_source_u16;                                         \
            (शून्य)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 3, sve_target_u16); \
        } जबसम्म (0);                                                      \
    } जबसम्म (0)

#define sdl_sve_pixel_u16x4_foreach_chn(ma_source_u16x4,                  \
                                        ma_target_u16x4,                  \
                                        ...)                              \
    गर {                                                                  \
        svuint16x4_t sve_source_u16x4 = ma_source_u16x4;                  \
        (शून्य)sve_source_u16x4;                                           \
        गर {                                                              \
            अचर uint8_t sve_src_chn_idx = 0;                            \
            (शून्य)sve_src_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 0);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 0);     \
            (शून्य)sve_source_u16;                                         \
            (शून्य)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 0, sve_target_u16); \
        } जबसम्म (0);                                                      \
        गर {                                                              \
            अचर uint8_t sve_src_chn_idx = 1;                            \
            (शून्य)sve_src_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 1);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 1);     \
            (शून्य)sve_source_u16;                                         \
            (शून्य)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 1, sve_target_u16); \
        } जबसम्म (0);                                                      \
        गर {                                                              \
            अचर uint8_t sve_src_chn_idx = 2;                            \
            (शून्य)sve_src_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 2);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 2);     \
            (शून्य)sve_source_u16;                                         \
            (शून्य)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 2, sve_target_u16); \
        } जबसम्म (0);                                                      \
        गर {                                                              \
            अचर uint8_t sve_src_chn_idx = 3;                            \
            (शून्य)sve_src_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 3);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 3);     \
            (शून्य)sve_source_u16;                                         \
            (शून्य)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 3, sve_target_u16); \
        } जबसम्म (0);                                                      \
    } जबसम्म (0)

#define sdl_sve_pixel_u16x4_foreach_chn_src_dst_rev(ma_source_u16x4,      \
                                                    ma_target_u16x4,      \
                                                    ...)                  \
    गर {                                                                  \
        svuint16x4_t sve_source_u16x4 = ma_source_u16x4;                  \
        (शून्य)sve_source_u16x4;                                           \
        गर {                                                              \
            अचर uint8_t sve_src_chn_idx = 0;                            \
            अचर uint8_t sve_dst_chn_idx = 3;                            \
            (शून्य)sve_src_chn_idx;                                        \
            (शून्य)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 0);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 3);     \
            (शून्य)sve_source_u16;                                         \
            (शून्य)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 3, sve_target_u16); \
        } जबसम्म (0);                                                      \
        गर {                                                              \
            अचर uint8_t sve_src_chn_idx = 1;                            \
            अचर uint8_t sve_dst_chn_idx = 2;                            \
            (शून्य)sve_src_chn_idx;                                        \
            (शून्य)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 1);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 2);     \
            (शून्य)sve_source_u16;                                         \
            (शून्य)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 2, sve_target_u16); \
        } जबसम्म (0);                                                      \
        गर {                                                              \
            अचर uint8_t sve_src_chn_idx = 2;                            \
            अचर uint8_t sve_dst_chn_idx = 1;                            \
            (शून्य)sve_src_chn_idx;                                        \
            (शून्य)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 2);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 1);     \
            (शून्य)sve_source_u16;                                         \
            (शून्य)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 1, sve_target_u16); \
        } जबसम्म (0);                                                      \
        गर {                                                              \
            अचर uint8_t sve_src_chn_idx = 3;                            \
            अचर uint8_t sve_dst_chn_idx = 0;                            \
            (शून्य)sve_src_chn_idx;                                        \
            (शून्य)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 3);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 0);     \
            (शून्य)sve_source_u16;                                         \
            (शून्य)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 0, sve_target_u16); \
        } जबसम्म (0);                                                      \
    } जबसम्म (0)

#define sdl_sve_pixel_u16x4_foreach_chn_accc_ccca(ma_source_u16x4,        \
                                                  ma_target_u16x4,        \
                                                  ...)                    \
    गर {                                                                  \
        svuint16x4_t sve_source_u16x4 = ma_source_u16x4;                  \
        (शून्य)sve_source_u16x4;                                           \
        गर {                                                              \
            अचर uint8_t sve_src_chn_idx = 0;                            \
            अचर uint8_t sve_dst_chn_idx = 1;                            \
            (शून्य)sve_src_chn_idx;                                        \
            (शून्य)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 0);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 1);     \
            (शून्य)sve_source_u16;                                         \
            (शून्य)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 1, sve_target_u16); \
        } जबसम्म (0);                                                      \
        गर {                                                              \
            अचर uint8_t sve_src_chn_idx = 1;                            \
            अचर uint8_t sve_dst_chn_idx = 2;                            \
            (शून्य)sve_src_chn_idx;                                        \
            (शून्य)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 1);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 2);     \
            (शून्य)sve_source_u16;                                         \
            (शून्य)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 2, sve_target_u16); \
        } जबसम्म (0);                                                      \
        गर {                                                              \
            अचर uint8_t sve_src_chn_idx = 2;                            \
            अचर uint8_t sve_dst_chn_idx = 3;                            \
            (शून्य)sve_src_chn_idx;                                        \
            (शून्य)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 2);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 3);     \
            (शून्य)sve_source_u16;                                         \
            (शून्य)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 3, sve_target_u16); \
        } जबसम्म (0);                                                      \
        गर {                                                              \
            अचर uint8_t sve_src_chn_idx = 3;                            \
            अचर uint8_t sve_dst_chn_idx = 0;                            \
            (शून्य)sve_src_chn_idx;                                        \
            (शून्य)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 3);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 0);     \
            (शून्य)sve_source_u16;                                         \
            (शून्य)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 0, sve_target_u16); \
        } जबसम्म (0);                                                      \
    } जबसम्म (0)

#define sdl_sve_pixel_u16x4_foreach_chn_ccca_accc(ma_source_u16x4,        \
                                                  ma_target_u16x4,        \
                                                  ...)                    \
    गर {                                                                  \
        svuint16x4_t sve_source_u16x4 = ma_source_u16x4;                  \
        (शून्य)sve_source_u16x4;                                           \
        गर {                                                              \
            अचर uint8_t sve_src_chn_idx = 1;                            \
            अचर uint8_t sve_dst_chn_idx = 0;                            \
            (शून्य)sve_src_chn_idx;                                        \
            (शून्य)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 1);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 0);     \
            (शून्य)sve_source_u16;                                         \
            (शून्य)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 0, sve_target_u16); \
        } जबसम्म (0);                                                      \
        गर {                                                              \
            अचर uint8_t sve_src_chn_idx = 2;                            \
            अचर uint8_t sve_dst_chn_idx = 1;                            \
            (शून्य)sve_src_chn_idx;                                        \
            (शून्य)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 2);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 1);     \
            (शून्य)sve_source_u16;                                         \
            (शून्य)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 1, sve_target_u16); \
        } जबसम्म (0);                                                      \
        गर {                                                              \
            अचर uint8_t sve_src_chn_idx = 3;                            \
            अचर uint8_t sve_dst_chn_idx = 2;                            \
            (शून्य)sve_src_chn_idx;                                        \
            (शून्य)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 3);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 2);     \
            (शून्य)sve_source_u16;                                         \
            (शून्य)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 2, sve_target_u16); \
        } जबसम्म (0);                                                      \
        गर {                                                              \
            अचर uint8_t sve_src_chn_idx = 0;                            \
            अचर uint8_t sve_dst_chn_idx = 3;                            \
            (शून्य)sve_src_chn_idx;                                        \
            (शून्य)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 0);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 3);     \
            (शून्य)sve_source_u16;                                         \
            (शून्य)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 3, sve_target_u16); \
        } जबसम्म (0);                                                      \
    } जबसम्म (0)

#define sdl_sve_pixel_u16x4_foreach_chn_a123_a321(ma_source_u16x4,        \
                                                  ma_target_u16x4,        \
                                                  ...)                    \
    गर {                                                                  \
        svuint16x4_t sve_source_u16x4 = ma_source_u16x4;                  \
        (शून्य)sve_source_u16x4;                                           \
        गर {                                                              \
            अचर uint8_t sve_src_chn_idx = 0;                            \
            अचर uint8_t sve_dst_chn_idx = 2;                            \
            (शून्य)sve_src_chn_idx;                                        \
            (शून्य)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 0);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 2);     \
            (शून्य)sve_source_u16;                                         \
            (शून्य)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 2, sve_target_u16); \
        } जबसम्म (0);                                                      \
        गर {                                                              \
            अचर uint8_t sve_src_chn_idx = 1;                            \
            अचर uint8_t sve_dst_chn_idx = 1;                            \
            (शून्य)sve_src_chn_idx;                                        \
            (शून्य)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 1);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 1);     \
            (शून्य)sve_source_u16;                                         \
            (शून्य)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 1, sve_target_u16); \
        } जबसम्म (0);                                                      \
        गर {                                                              \
            अचर uint8_t sve_src_chn_idx = 2;                            \
            अचर uint8_t sve_dst_chn_idx = 0;                            \
            (शून्य)sve_src_chn_idx;                                        \
            (शून्य)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 2);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 0);     \
            (शून्य)sve_source_u16;                                         \
            (शून्य)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 0, sve_target_u16); \
        } जबसम्म (0);                                                      \
        गर {                                                              \
            अचर uint8_t sve_src_chn_idx = 3;                            \
            अचर uint8_t sve_dst_chn_idx = 3;                            \
            (शून्य)sve_src_chn_idx;                                        \
            (शून्य)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 3);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 3);     \
            (शून्य)sve_source_u16;                                         \
            (शून्य)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 3, sve_target_u16); \
        } जबसम्म (0);                                                      \
    } जबसम्म (0)

#define sdl_sve_pixel_u16x4_foreach_chn_123a_321a(ma_source_u16x4,        \
                                                  ma_target_u16x4,        \
                                                  ...)                    \
    गर {                                                                  \
        svuint16x4_t sve_source_u16x4 = ma_source_u16x4;                  \
        (शून्य)sve_source_u16x4;                                           \
        गर {                                                              \
            अचर uint8_t sve_src_chn_idx = 0;                            \
            अचर uint8_t sve_dst_chn_idx = 0;                            \
            (शून्य)sve_src_chn_idx;                                        \
            (शून्य)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 0);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 0);     \
            (शून्य)sve_source_u16;                                         \
            (शून्य)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 0, sve_target_u16); \
        } जबसम्म (0);                                                      \
        गर {                                                              \
            अचर uint8_t sve_src_chn_idx = 1;                            \
            अचर uint8_t sve_dst_chn_idx = 3;                            \
            (शून्य)sve_src_chn_idx;                                        \
            (शून्य)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 1);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 3);     \
            (शून्य)sve_source_u16;                                         \
            (शून्य)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 3, sve_target_u16); \
        } जबसम्म (0);                                                      \
        गर {                                                              \
            अचर uint8_t sve_src_chn_idx = 2;                            \
            अचर uint8_t sve_dst_chn_idx = 2;                            \
            (शून्य)sve_src_chn_idx;                                        \
            (शून्य)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 2);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 2);     \
            (शून्य)sve_source_u16;                                         \
            (शून्य)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 2, sve_target_u16); \
        } जबसम्म (0);                                                      \
        गर {                                                              \
            अचर uint8_t sve_src_chn_idx = 3;                            \
            अचर uint8_t sve_dst_chn_idx = 1;                            \
            (शून्य)sve_src_chn_idx;                                        \
            (शून्य)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 3);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 1);     \
            (शून्य)sve_source_u16;                                         \
            (शून्य)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 1, sve_target_u16); \
        } जबसम्म (0);                                                      \
    } जबसम्म (0)

#define sdl_sve_pixel_u16x4_foreach_chn_argb_rgb565(ma_source_u16x4,      \
                                                    ma_target_u16x3,      \
                                                    ...)                  \
    गर {                                                                  \
        svuint16x4_t sve_source_u16x4 = ma_source_u16x4;                  \
        (शून्य)sve_source_u16x4;                                           \
        गर {                                                              \
            अचर uint8_t sve_src_chn_idx = 0;                            \
            अचर uint8_t sve_dst_chn_idx = 0;                            \
            (शून्य)sve_src_chn_idx;                                        \
            (शून्य)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 0);     \
            svuint16_t sve_target_u16 = svget3((ma_target_u16x3), 0);     \
            (शून्य)sve_source_u16;                                         \
            (शून्य)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x3 = svset3(ma_target_u16x3, 0, sve_target_u16); \
        } जबसम्म (0);                                                      \
        गर {                                                              \
            अचर uint8_t sve_src_chn_idx = 1;                            \
            अचर uint8_t sve_dst_chn_idx = 1;                            \
            (शून्य)sve_src_chn_idx;                                        \
            (शून्य)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 1);     \
            svuint16_t sve_target_u16 = svget3((ma_target_u16x3), 1);     \
            (शून्य)sve_source_u16;                                         \
            (शून्य)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x3 = svset3(ma_target_u16x3, 1, sve_target_u16); \
        } जबसम्म (0);                                                      \
        गर {                                                              \
            अचर uint8_t sve_src_chn_idx = 2;                            \
            अचर uint8_t sve_dst_chn_idx = 2;                            \
            (शून्य)sve_src_chn_idx;                                        \
            (शून्य)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 2);     \
            svuint16_t sve_target_u16 = svget3((ma_target_u16x3), 2);     \
            (शून्य)sve_source_u16;                                         \
            (शून्य)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x3 = svset3(ma_target_u16x3, 2, sve_target_u16); \
        } जबसम्म (0);                                                      \
    } जबसम्म (0)

#define sdl_sve_pixel_u16x4_foreach_chn_rgba_rgb565(ma_source_u16x4,      \
                                                    ma_target_u16x3,      \
                                                    ...)                  \
    गर {                                                                  \
        svuint16x4_t sve_source_u16x4 = ma_source_u16x4;                  \
        (शून्य)sve_source_u16x4;                                           \
        गर {                                                              \
            अचर uint8_t sve_src_chn_idx = 1;                            \
            अचर uint8_t sve_dst_chn_idx = 0;                            \
            (शून्य)sve_src_chn_idx;                                        \
            (शून्य)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 1);     \
            svuint16_t sve_target_u16 = svget3((ma_target_u16x3), 0);     \
            (शून्य)sve_source_u16;                                         \
            (शून्य)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x3 = svset3(ma_target_u16x3, 0, sve_target_u16); \
        } जबसम्म (0);                                                      \
        गर {                                                              \
            अचर uint8_t sve_src_chn_idx = 2;                            \
            अचर uint8_t sve_dst_chn_idx = 1;                            \
            (शून्य)sve_src_chn_idx;                                        \
            (शून्य)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 2);     \
            svuint16_t sve_target_u16 = svget3((ma_target_u16x3), 1);     \
            (शून्य)sve_source_u16;                                         \
            (शून्य)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x3 = svset3(ma_target_u16x3, 1, sve_target_u16); \
        } जबसम्म (0);                                                      \
        गर {                                                              \
            अचर uint8_t sve_src_chn_idx = 3;                            \
            अचर uint8_t sve_dst_chn_idx = 2;                            \
            (शून्य)sve_src_chn_idx;                                        \
            (शून्य)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 3);     \
            svuint16_t sve_target_u16 = svget3((ma_target_u16x3), 2);     \
            (शून्य)sve_source_u16;                                         \
            (शून्य)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x3 = svset3(ma_target_u16x3, 2, sve_target_u16); \
        } जबसम्म (0);                                                      \
    } जबसम्म (0)

#define sdl_sve_pixel_u16x4_foreach_chn_bgra_rgb565(ma_source_u16x4,      \
                                                    ma_target_u16x3,      \
                                                    ...)                  \
    गर {                                                                  \
        svuint16x4_t sve_source_u16x4 = ma_source_u16x4;                  \
        (शून्य)sve_source_u16x4;                                           \
        गर {                                                              \
            अचर uint8_t sve_src_chn_idx = 3;                            \
            अचर uint8_t sve_dst_chn_idx = 0;                            \
            (शून्य)sve_src_chn_idx;                                        \
            (शून्य)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 3);     \
            svuint16_t sve_target_u16 = svget3((ma_target_u16x3), 0);     \
            (शून्य)sve_source_u16;                                         \
            (शून्य)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x3 = svset3(ma_target_u16x3, 0, sve_target_u16); \
        } जबसम्म (0);                                                      \
        गर {                                                              \
            अचर uint8_t sve_src_chn_idx = 2;                            \
            अचर uint8_t sve_dst_chn_idx = 1;                            \
            (शून्य)sve_src_chn_idx;                                        \
            (शून्य)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 2);     \
            svuint16_t sve_target_u16 = svget3((ma_target_u16x3), 1);     \
            (शून्य)sve_source_u16;                                         \
            (शून्य)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x3 = svset3(ma_target_u16x3, 1, sve_target_u16); \
        } जबसम्म (0);                                                      \
        गर {                                                              \
            अचर uint8_t sve_src_chn_idx = 1;                            \
            अचर uint8_t sve_dst_chn_idx = 2;                            \
            (शून्य)sve_src_chn_idx;                                        \
            (शून्य)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 1);     \
            svuint16_t sve_target_u16 = svget3((ma_target_u16x3), 2);     \
            (शून्य)sve_source_u16;                                         \
            (शून्य)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x3 = svset3(ma_target_u16x3, 2, sve_target_u16); \
        } जबसम्म (0);                                                      \
    } जबसम्म (0)

#define sdl_sve_pixel_u16x4_foreach_chn_abgr_rgb565(ma_source_u16x4,      \
                                                    ma_target_u16x3,      \
                                                    ...)                  \
    गर {                                                                  \
        svuint16x4_t sve_source_u16x4 = ma_source_u16x4;                  \
        (शून्य)sve_source_u16x4;                                           \
        गर {                                                              \
            अचर uint8_t sve_src_chn_idx = 2;                            \
            अचर uint8_t sve_dst_chn_idx = 0;                            \
            (शून्य)sve_src_chn_idx;                                        \
            (शून्य)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 2);     \
            svuint16_t sve_target_u16 = svget3((ma_target_u16x3), 0);     \
            (शून्य)sve_source_u16;                                         \
            (शून्य)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x3 = svset3(ma_target_u16x3, 0, sve_target_u16); \
        } जबसम्म (0);                                                      \
        गर {                                                              \
            अचर uint8_t sve_src_chn_idx = 1;                            \
            अचर uint8_t sve_dst_chn_idx = 1;                            \
            (शून्य)sve_src_chn_idx;                                        \
            (शून्य)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 1);     \
            svuint16_t sve_target_u16 = svget3((ma_target_u16x3), 1);     \
            (शून्य)sve_source_u16;                                         \
            (शून्य)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x3 = svset3(ma_target_u16x3, 1, sve_target_u16); \
        } जबसम्म (0);                                                      \
        गर {                                                              \
            अचर uint8_t sve_src_chn_idx = 0;                            \
            अचर uint8_t sve_dst_chn_idx = 2;                            \
            (शून्य)sve_src_chn_idx;                                        \
            (शून्य)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 0);     \
            svuint16_t sve_target_u16 = svget3((ma_target_u16x3), 2);     \
            (शून्य)sve_source_u16;                                         \
            (शून्य)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x3 = svset3(ma_target_u16x3, 2, sve_target_u16); \
        } जबसम्म (0);                                                      \
    } जबसम्म (0)

SDL_TARGETING("arch=armv8-a+sve2")
स्थिर अन्तःस्थ svuint16x3_t sdl_sve_rgb565_unpack(svuint16_t vPixels)
{
    svuint16_t vBlue = svand_n_u16_m(svptrue_b16(), vPixels, 0x1F);
    svuint16_t vGreen = svand_n_u16_m(svptrue_b16(), vPixels, (0x3F << 5));
    svuint16_t vRed = svand_n_u16_m(svptrue_b16(), vPixels, (0x1F << 11));

    फर्काऊ svcreate3_u16(svlsl_n_u16_m(svptrue_b16(), vBlue, 3),
                         svlsr_n_u16_m(svptrue_b16(), vGreen, 3),
                         svlsr_n_u16_m(svptrue_b16(), vRed, 8));
}

SDL_TARGETING("arch=armv8-a+sve2")
स्थिर अन्तःस्थ svuint16_t sdl_sve_rgb565_pack(svuint16x3_t vRGB16x3)
{
    svuint16_t vRed = svlsr_n_u16_m(svptrue_b16(), svget3_u16(vRGB16x3, 0), 3);
    svuint16_t vGreen = svlsl_n_u16_m(svptrue_b16(),
                                      svand_n_u16_m(svptrue_b16(),
                                                    svget3_u16(vRGB16x3, 1),
                                                    (0x3F << 2)),
                                      3);
    svuint16_t vBlue = svlsl_n_u16_m(svptrue_b16(),
                                     svand_n_u16_m(svptrue_b16(),
                                                   svget3_u16(vRGB16x3, 2),
                                                   (0x1F << 3)),
                                     8);

    svuint16_t vPixel = svorr_u16_m(svptrue_b16(), vRed, vGreen);
    फर्काऊ svorr_u16_m(svptrue_b16(), vPixel, vBlue);

    // return  (svget3_u16(vRGB16x3, 0) >> 3)
    //     |   ((svget3_u16(vRGB16x3, 1) & (0x3F << 2)) << 3)
    //     |   ((svget3_u16(vRGB16x3, 2) & (0x1F << 3)) << 8);
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(2, 3, 4)
स्थिर अन्तःस्थ शून्य svld3rgb565_u16(svbool_t vPredu8,
                                   uint16_t *phwSource,
                                   svuint16x3_t *pv_तल्लो,
                                   svuint16x3_t *pv_माथिल्लो)
{
    svuint8x2_t vInput8x2 = svld2_u8(vPredu8, (uint8_t *)phwSource);

    svuint16_t v_तल्लो_Byte_तल्लो_Half = svunpklo_u16(svget2_u8(vInput8x2, 0));
    svuint16_t v_तल्लो_Byte_माथिल्लो_Half = svunpkhi_u16(svget2_u8(vInput8x2, 0));

    svuint16_t v_माथिल्लो_Byte_तल्लो_Half = svunpklo_u16(svget2_u8(vInput8x2, 1));
    svuint16_t v_माथिल्लो_Byte_माथिल्लो_Half = svunpkhi_u16(svget2_u8(vInput8x2, 1));

    //*pvLow = sdl_sve_rgb565_unpack  (   vLowByteLowHalf
    //                                |   (vHighByteLowHalf << 8));
    *pv_तल्लो = sdl_sve_rgb565_unpack(
        svorr_u16_m(svptrue_b16(),
                    v_तल्लो_Byte_तल्लो_Half,
                    //(vHighByteLowHalf << 8)
                    svlsl_n_u16_m(svptrue_b16(), v_माथिल्लो_Byte_तल्लो_Half, 8)));

    //*pvHigh = sdl_sve_rgb565_unpack (   vLowByteHighHalf
    //                                |   (vHighByteHighHalf << 8));
    *pv_माथिल्लो = sdl_sve_rgb565_unpack(
        svorr_u16_m(svptrue_b16(),
                    v_तल्लो_Byte_माथिल्लो_Half,
                    //(vHighByteHighHalf << 8)
                    svlsl_n_u16_m(svptrue_b16(), v_माथिल्लो_Byte_माथिल्लो_Half, 8)));
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(2)
स्थिर अन्तःस्थ शून्य svst3rgb565_u16(svbool_t vPredu8,
                                   uint16_t *phwTarget,
                                   svuint16x3_t v_तल्लो,
                                   svuint16x3_t v_माथिल्लो)
{
    svuint16_t v_तल्लो_Byte_तल्लो_Half = svundef_u16();
    svuint16_t v_माथिल्लो_Byte_तल्लो_Half = svundef_u16();

    /* pack low half pixels */
    गर {
        svuint16_t vPixel = sdl_sve_rgb565_pack(v_तल्लो);

        // vLowByteLowHalf = vPixel & 0xFF;
        v_तल्लो_Byte_तल्लो_Half = svand_n_u16_m(svptrue_b16(), vPixel, 0xFF);

        // vHighByteLowHalf = vPixel >> 8;
        v_माथिल्लो_Byte_तल्लो_Half = svlsr_n_u16_m(svptrue_b16(), vPixel, 8);
    } जबसम्म (0);

    svuint16_t v_तल्लो_Byte_माथिल्लो_Half = svundef_u16();
    svuint16_t v_माथिल्लो_Byte_माथिल्लो_Half = svundef_u16();

    /* pack high half pixels */
    गर {
        svuint16_t vPixel = sdl_sve_rgb565_pack(v_माथिल्लो);

        // vLowByteHighHalf = vPixel & 0xFF;
        v_तल्लो_Byte_माथिल्लो_Half = svand_n_u16_m(svptrue_b16(), vPixel, 0xFF);

        // vHighByteHighHalf = vPixel >> 8;
        v_माथिल्लो_Byte_माथिल्लो_Half = svlsr_n_u16_m(svptrue_b16(), vPixel, 8);
    } जबसम्म (0);

    /* save rgb565 pixels */
    svuint8_t v_तल्लो_Byte = svuzp1_u8(svreinterpret_u8(v_तल्लो_Byte_तल्लो_Half),
                                   svreinterpret_u8(v_तल्लो_Byte_माथिल्लो_Half));

    svuint8_t v_माथिल्लो_Byte = svuzp1_u8(svreinterpret_u8(v_माथिल्लो_Byte_तल्लो_Half),
                                    svreinterpret_u8(v_माथिल्लो_Byte_माथिल्लो_Half));

    svst2_u8(vPredu8, (uint8_t *)phwTarget, svcreate2_u8(v_तल्लो_Byte, v_माथिल्लो_Byte));
}

#यदि defined(__GNUC__) && !defined(__clang__)
#define svld4ub_u16(ma_pred,                                                                                         \
                    ma_src_ptr,                                                                                      \
                    ma_svuint16x4_तल्लो_ptr,                                                                           \
                    ma_svuint16x4_माथिल्लो_ptr)                                                                          \
    गर {                                                                                                             \
        svuint8x4_t vInput8x4 = svld4_u8((ma_pred), (ma_src_ptr));                                                   \
                                                                                                                     \
        *(ma_svuint16x4_तल्लो_ptr) = svset4_u16(*(ma_svuint16x4_तल्लो_ptr), 0, svunpklo_u16(svget4_u8(vInput8x4, 0)));   \
        *(ma_svuint16x4_तल्लो_ptr) = svset4_u16(*(ma_svuint16x4_तल्लो_ptr), 1, svunpklo_u16(svget4_u8(vInput8x4, 1)));   \
        *(ma_svuint16x4_तल्लो_ptr) = svset4_u16(*(ma_svuint16x4_तल्लो_ptr), 2, svunpklo_u16(svget4_u8(vInput8x4, 2)));   \
        *(ma_svuint16x4_तल्लो_ptr) = svset4_u16(*(ma_svuint16x4_तल्लो_ptr), 3, svunpklo_u16(svget4_u8(vInput8x4, 3)));   \
                                                                                                                     \
        *(ma_svuint16x4_माथिल्लो_ptr) = svset4_u16(*(ma_svuint16x4_माथिल्लो_ptr), 0, svunpkhi_u16(svget4_u8(vInput8x4, 0))); \
        *(ma_svuint16x4_माथिल्लो_ptr) = svset4_u16(*(ma_svuint16x4_माथिल्लो_ptr), 1, svunpkhi_u16(svget4_u8(vInput8x4, 1))); \
        *(ma_svuint16x4_माथिल्लो_ptr) = svset4_u16(*(ma_svuint16x4_माथिल्लो_ptr), 2, svunpkhi_u16(svget4_u8(vInput8x4, 2))); \
        *(ma_svuint16x4_माथिल्लो_ptr) = svset4_u16(*(ma_svuint16x4_माथिल्लो_ptr), 3, svunpkhi_u16(svget4_u8(vInput8x4, 3))); \
    } जबसम्म (0)

#define svst4ub_u16(ma_pred,                                                                 \
                    ma_dst_ptr,                                                              \
                    ma_svuint16x4_तल्लो,                                                       \
                    ma_svuint16x4_माथिल्लो)                                                      \
    गर {                                                                                     \
        svuint8_t vCH0u8 = svuzp1_u8(svreinterpret_u8(svget4_u16((ma_svuint16x4_तल्लो), 0)),   \
                                     svreinterpret_u8(svget4_u16((ma_svuint16x4_माथिल्लो), 0))); \
                                                                                             \
        svuint8_t vCH1u8 = svuzp1_u8(svreinterpret_u8(svget4_u16((ma_svuint16x4_तल्लो), 1)),   \
                                     svreinterpret_u8(svget4_u16((ma_svuint16x4_माथिल्लो), 1))); \
                                                                                             \
        svuint8_t vCH2u8 = svuzp1_u8(svreinterpret_u8(svget4_u16((ma_svuint16x4_तल्लो), 2)),   \
                                     svreinterpret_u8(svget4_u16((ma_svuint16x4_माथिल्लो), 2))); \
                                                                                             \
        svuint8_t vCH3u8 = svuzp1_u8(svreinterpret_u8(svget4_u16((ma_svuint16x4_तल्लो), 3)),   \
                                     svreinterpret_u8(svget4_u16((ma_svuint16x4_माथिल्लो), 3))); \
                                                                                             \
        svst4_u8((ma_pred), (ma_dst_ptr), svcreate4_u8(vCH0u8, vCH1u8, vCH2u8, vCH3u8));     \
    } जबसम्म (0)
#अन्यथा
SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(2, 3, 4)
स्थिर अन्तःस्थ शून्य svld4ub_u16(svbool_t vPredu8,
                               uint8_t *pchSource,
                               svuint16x4_t *pv_तल्लो,
                               svuint16x4_t *pv_माथिल्लो)
{
    svuint8x4_t vInput8x4 = svld4_u8(vPredu8, pchSource);

    *pv_तल्लो = svset4_u16(*pv_तल्लो, 0, svunpklo_u16(svget4_u8(vInput8x4, 0)));
    *pv_तल्लो = svset4_u16(*pv_तल्लो, 1, svunpklo_u16(svget4_u8(vInput8x4, 1)));
    *pv_तल्लो = svset4_u16(*pv_तल्लो, 2, svunpklo_u16(svget4_u8(vInput8x4, 2)));
    *pv_तल्लो = svset4_u16(*pv_तल्लो, 3, svunpklo_u16(svget4_u8(vInput8x4, 3)));

    *pv_माथिल्लो = svset4_u16(*pv_माथिल्लो, 0, svunpkhi_u16(svget4_u8(vInput8x4, 0)));
    *pv_माथिल्लो = svset4_u16(*pv_माथिल्लो, 1, svunpkhi_u16(svget4_u8(vInput8x4, 1)));
    *pv_माथिल्लो = svset4_u16(*pv_माथिल्लो, 2, svunpkhi_u16(svget4_u8(vInput8x4, 2)));
    *pv_माथिल्लो = svset4_u16(*pv_माथिल्लो, 3, svunpkhi_u16(svget4_u8(vInput8x4, 3)));
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(2)
स्थिर अन्तःस्थ शून्य svst4ub_u16(svbool_t vPredu8,
                               uint8_t *pchTarget,
                               svuint16x4_t v_तल्लो,
                               svuint16x4_t v_माथिल्लो)
{

    svuint8_t vCH0u8 = svuzp1_u8(svreinterpret_u8(svget4_u16(v_तल्लो, 0)),
                                 svreinterpret_u8(svget4_u16(v_माथिल्लो, 0)));

    svuint8_t vCH1u8 = svuzp1_u8(svreinterpret_u8(svget4_u16(v_तल्लो, 1)),
                                 svreinterpret_u8(svget4_u16(v_माथिल्लो, 1)));

    svuint8_t vCH2u8 = svuzp1_u8(svreinterpret_u8(svget4_u16(v_तल्लो, 2)),
                                 svreinterpret_u8(svget4_u16(v_माथिल्लो, 2)));

    svuint8_t vCH3u8 = svuzp1_u8(svreinterpret_u8(svget4_u16(v_तल्लो, 3)),
                                 svreinterpret_u8(svget4_u16(v_माथिल्लो, 3)));

    svst4_u8(vPredu8, pchTarget, svcreate4_u8(vCH0u8, vCH1u8, vCH2u8, vCH3u8));
}
#endif

/*! \note the Element range of vMask is [0, 0xFF]
 */
SDL_TARGETING("arch=armv8-a+sve2")
स्थिर अन्तःस्थ svuint16_t sdl_sve_chn_blend_with_mask(svuint16_t vSource,
                                                     svuint16_t vTarget,
                                                     svuint16_t vMask)
{
    // vTarget = vSource * vMask + vTarget * (255 - vMask);
    svuint16_t vTemp0 = svdup_u16(1);
    vTemp0 = svmla_u16_m(svptrue_b16(), vTemp0, vSource, vMask);
    vTemp0 = svmla_u16_m(svptrue_b16(),
                         vTemp0,
                         vTarget,
                         svsub_u16_m(svptrue_b16(),
                                     svdup_u16(255),
                                     vMask));

    /* x += x >> 8 */
    फर्काऊ svreinterpret_u16_u8(
        svaddhnb_u16(vTemp0,
                     svlsr_n_u16_m(svptrue_b16(),
                                   vTemp0,
                                   8)));
}
/*! \note the Element range of vMask is [0, 0xFF]
 */
SDL_TARGETING("arch=armv8-a+sve2")
स्थिर अन्तःस्थ svuint16_t sdl_sve_chn_blend_with_mask_fast(svuint16_t vSource,
                                                          svuint16_t vTarget,
                                                          svuint16_t vMask)
{
    // vTarget = vSource * vMask + vTarget * (255 - vMask);
    svuint16_t vTemp0 = svmul_u16_m(svptrue_b16(), vSource, vMask);
    vTemp0 = svmla_u16_m(svptrue_b16(),
                         vTemp0,
                         vTarget,
                         svsub_u16_m(svptrue_b16(),
                                     svdup_u16(255),
                                     vMask));

    फर्काऊ svlsr_n_u16_m(svptrue_b16(), vTemp0, 8); // vTarget >> 8;
}

/*! \note the hwOpacity range [0, 0x100]
 */
SDL_TARGETING("arch=armv8-a+sve2")
स्थिर अन्तःस्थ svuint16_t sdl_sve_chn_blend_with_opacity(svuint16_t vSource,
                                                        svuint16_t vTarget,
                                                        uint16_t hwOpacity)
{
    // svuint16_t vOpacity = svdup_u16(hwOpacity);
    // vTarget = vSource * vOpacity + vTarget * (256 - vOpacity);

    svuint16_t vTemp0 = svmul_n_u16_m(svptrue_b16(), vSource, hwOpacity);
    svuint16_t vTemp1 = svmul_n_u16_m(svptrue_b16(),
                                      vTarget,
                                      256 - hwOpacity);
    vTarget = svadd_u16_m(svptrue_b16(), vTemp0, vTemp1);

    फर्काऊ svlsr_n_u16_m(svptrue_b16(), vTarget, 8); // vTarget >> 8;
}

/*! \note the hwOpacity range [0, 0x100]
 */
SDL_TARGETING("arch=armv8-a+sve2")
स्थिर अन्तःस्थ svuint16_t sdl_sve_chn_blend_with_opacity_fast(svuint16_t vSource,
                                                             svuint16_t vTarget,
                                                             uint16_t hwOpacity)
{
    // vTarget = vSource * vMask + vTarget * (255 - vMask);
    svuint16_t vTemp0 = svmul_n_u16_m(svptrue_b16(), vSource, hwOpacity);
    vTemp0 = svmla_n_u16_m(svptrue_b16(),
                           vTemp0,
                           vTarget,
                           256 - hwOpacity);

    फर्काऊ svlsr_n_u16_m(svptrue_b16(), vTemp0, 8); // vTarget >> 8;
}

/*! \note the Element range of vMask is [0, 0xFF]
 *  \note the hwOpacity range [0, 0x100]
 */
SDL_TARGETING("arch=armv8-a+sve2")
स्थिर अन्तःस्थ svuint16_t sdl_sve_chn_blend_with_mask_and_opacity(svuint16_t vSource,
                                                                 svuint16_t vTarget,
                                                                 svuint16_t vMask,
                                                                 uint16_t hwOpacity)
{
    vMask = svsel(svcmpeq_n_u16(svptrue_b16(), vMask, 255),
                  svdup_u16(hwOpacity),
                  //(vMask * hwOpacity) >> 8,
                  svlsr_n_u16_m(svptrue_b16(),
                                svmul_n_u16_m(svptrue_b16(), vMask, hwOpacity),
                                8));

    // vTarget = vSource * vMask + vTarget * (256 - vMask);
    svuint16_t vTemp0 = svmul_u16_m(svptrue_b16(), vSource, vMask);
    svuint16_t vTemp1 = svmul_u16_m(svptrue_b16(),
                                    vTarget,
                                    svsub_u16_m(svptrue_b16(),
                                                svdup_u16(256),
                                                vMask));
    vTarget = svadd_u16_m(svptrue_b16(), vTemp0, vTemp1);

    फर्काऊ svlsr_n_u16_m(svptrue_b16(), vTarget, 8); // vTarget >> 8;
}

/*! \note the Element range of vMask0/1 is [0, 0xFF]
 */
SDL_TARGETING("arch=armv8-a+sve2")
स्थिर अन्तःस्थ svuint16_t sdl_sve_chn_blend_with_masks(svuint16_t vSource,
                                                      svuint16_t vTarget,
                                                      svuint16_t vMask0,
                                                      svuint16_t vMask1)
{
    vMask1 = svadd_u16_m(svcmpeq_n_u16(svptrue_b16(), vMask1, 255),
                         vMask1,
                         svdup_u16(1));

    svuint16_t vMask =
        svsel(svcmpge_n_u16(svptrue_b16(), vMask0, 255),
              vMask1,
              //(vMask0 * vMask1) >> 8,
              svlsr_n_u16_m(svptrue_b16(),
                            svmul_u16_m(svptrue_b16(), vMask0, vMask1),
                            8));

    // vTarget = vSource * vMask + vTarget * (256 - vMask);
    svuint16_t vTemp0 = svmul_u16_m(svptrue_b16(), vSource, vMask);
    svuint16_t vTemp1 = svmul_u16_m(svptrue_b16(),
                                    vTarget,
                                    svsub_u16_m(svptrue_b16(),
                                                svdup_u16(256),
                                                vMask));
    vTarget = svadd_u16_m(svptrue_b16(), vTemp0, vTemp1);

    फर्काऊ svlsr_n_u16_m(svptrue_b16(), vTarget, 8); // vTarget >> 8;
}

/*! \note the Element range of vMask0/1 is [0, 0xFF]
 *  \note the hwOpacity range [0, 0x100]
 */
SDL_TARGETING("arch=armv8-a+sve2")
स्थिर अन्तःस्थ svuint16_t sdl_sve_chn_blend_with_masks_and_opacity(
    svuint16_t vSource,
    svuint16_t vTarget,
    svuint16_t vMask0,
    svuint16_t vMask1,
    uint16_t hwOpacity)
{
    vMask0 = svadd_u16_m(svcmpeq_n_u16(svptrue_b16(), vMask0, 255),
                         vMask0,
                         svdup_u16(1));

    svuint16_t vMask =
        svsel(svcmpge_n_u16(svptrue_b16(), vMask1, 255), /* >= 255 */
              vMask0,
              //(vMask0 * vMask1) >> 8
              svlsr_n_u16_m(svptrue_b16(),
                            svmul_u16_m(svptrue_b16(), vMask0, vMask1),
                            8));

    vMask =
        svsel(svcmpge_n_u16(svptrue_b16(), vMask, 255),
              svdup_u16(hwOpacity),
              //(vMask * hwOpacity) >> 8,
              svlsr_n_u16_m(svptrue_b16(),
                            svmul_n_u16_m(svptrue_b16(), vMask, hwOpacity),
                            8));

    // vTarget = vSource * vMask + vTarget * (256 - vMask);
    svuint16_t vTemp0 = svmul_u16_m(svptrue_b16(), vSource, vMask);
    svuint16_t vTemp1 = svmul_u16_m(svptrue_b16(),
                                    vTarget,
                                    svsub_u16_m(svptrue_b16(),
                                                svdup_u16(256),
                                                vMask));
    vTarget = svadd_u16_m(svptrue_b16(), vTemp0, vTemp1);

    फर्काऊ svlsr_n_u16_m(svptrue_b16(), vTarget, 8); // vTarget >> 8;
}

/*! \note the Element range of vMask0/1 is [0, 0xFF]
 */
SDL_TARGETING("arch=armv8-a+sve2")
स्थिर अन्तःस्थ svuint16_t sdl_sve_chn_blend_with_3masks(svuint16_t vSource,
                                                       svuint16_t vTarget,
                                                       svuint16_t vMask0,
                                                       svuint16_t vMask1,
                                                       svuint16_t vMask2)
{
    vMask0 = svadd_u16_m(svcmpeq_n_u16(svptrue_b16(), vMask0, 255),
                         vMask0,
                         svdup_u16(1));

    svuint16_t vMask =
        svsel(svcmpge_n_u16(svptrue_b16(), vMask1, 255),
              vMask0,
              //(vMask0 * vMask1) >> 8
              svlsr_n_u16_m(svptrue_b16(),
                            svmul_u16_m(svptrue_b16(), vMask0, vMask1),
                            8));

    vMask =
        svsel(svcmpge_n_u16(svptrue_b16(), vMask2, 255),
              vMask,
              //(vMask * vMask2) >> 8
              svlsr_n_u16_m(svptrue_b16(),
                            svmul_u16_m(svptrue_b16(), vMask, vMask2),
                            8));

    // vTarget = vSource * vMask + vTarget * (256 - vMask);
    svuint16_t vTemp0 = svmul_u16_m(svptrue_b16(), vSource, vMask);
    svuint16_t vTemp1 = svmul_u16_m(svptrue_b16(),
                                    vTarget,
                                    svsub_u16_m(svptrue_b16(),
                                                svdup_u16(256),
                                                vMask));
    vTarget = svadd_u16_m(svptrue_b16(), vTemp0, vTemp1);

    फर्काऊ svlsr_n_u16_m(svptrue_b16(), vTarget, 8); // vTarget >> 8;
}

/*! \note the Element range of vMask0/1 is [0, 0xFF]
 *  \note the hwOpacity range [0, 0x100]
 */
SDL_TARGETING("arch=armv8-a+sve2")
स्थिर अन्तःस्थ svuint16_t sdl_sve_chn_blend_with_3masks_and_opacity(
    svuint16_t vSource,
    svuint16_t vTarget,
    svuint16_t vMask0,
    svuint16_t vMask1,
    svuint16_t vMask2,
    uint16_t hwOpacity)
{
    vMask0 = svadd_u16_m(svcmpeq_n_u16(svptrue_b16(), vMask0, 255),
                         vMask0,
                         svdup_u16(1));

    svuint16_t vMask =
        svsel(svcmpge_n_u16(svptrue_b16(), vMask1, 255),
              vMask0,
              //(vMask0 * vMask1) >> 8
              svlsr_n_u16_m(svptrue_b16(),
                            svmul_u16_m(svptrue_b16(), vMask0, vMask1),
                            8));

    vMask =
        svsel(svcmpge_n_u16(svptrue_b16(), vMask2, 255),
              vMask,
              svlsr_n_u16_m(svptrue_b16(),
                            svmul_u16_m(svptrue_b16(), vMask, vMask2),
                            8));
    //(vMask * vMask2) >> 8);

    vMask =
        svsel(svcmpge_n_u16(svptrue_b16(), vMask, 255),
              svdup_u16(hwOpacity),
              //(vMask * hwOpacity) >> 8
              svlsr_n_u16_m(svptrue_b16(),
                            svmul_n_u16_m(svptrue_b16(), vMask, hwOpacity),
                            8));

    // vTarget = vSource * vMask + vTarget * (256 - vMask);
    svuint16_t vTemp0 = svmul_u16_m(svptrue_b16(), vSource, vMask);
    svuint16_t vTemp1 = svmul_u16_m(svptrue_b16(),
                                    vTarget,
                                    svsub_u16_m(svptrue_b16(),
                                                svdup_u16(256),
                                                vMask));
    vTarget = svadd_u16_m(svptrue_b16(), vTemp0, vTemp1);

    फर्काऊ svlsr_n_u16_m(svptrue_b16(), vTarget, 8); // vTarget >> 8;
}

#endif /* SDL_SVE2_EXTENSION_H */