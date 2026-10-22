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

#ఒకవేళ !defined(SDL_SVE2_EXTENSION_H) //&& (defined(__ARM_FEATURE_SVE2) && __ARM_FEATURE_SVE2)
#నిర్వచించు SDL_SVE2_EXTENSION_H

#అన్తర్భావ "SDL_sve2_util.h"

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
#నిర్వచితమైతే SDL_PLATFORM_ANDROID
#నిర్వచితం_కాకపోతే __ARM_FEATURE_SVE
#నిర్వచించు __ARM_FEATURE_SVE 1
#అయితే_ముగింపు
#అయితే_ముగింపు
#అన్తర్భావ <arm_sve.h>
#అన్తర్భావ <stdint.h>

/*!
 * \brief a wrapper for __attribute__((nonnull))
 */
#నిర్వచితం_కాకపోతే ARM_NONNULL
#నిర్వచించు ARM_NONNULL(...) __attribute__((nonnull(__VA_ARGS__)))
#అయితే_ముగింపు

#నిర్వచించు svlenu8()  svcntb_pat(SV_ALL)
#నిర్వచించు svlenu16() (svcntb_pat(SV_ALL) / పరిమాణం(uint16_t))
#నిర్వచించు svlenu32() (svcntb_pat(SV_ALL) / పరిమాణం(uint32_t))
#నిర్వచించు svlenu64() (svcntb_pat(SV_ALL) / పరిమాణం(uint64_t))

#నిర్వచించు svlens8()  svlenu8()
#నిర్వచించు svlens16() svlenu16()
#నిర్వచించు svlens32() svlenu32()
#నిర్వచించు svlens64() svlenu64()

#నిర్వచించు sdl_sve_stride_loop_pixel(ma_stride_కొలత, ma_pred_name)          \
    కొరకు (svbool_t ma_pred_name, *p_తాత్కాలిక = &ma_pred_name;                  \
         p_తాత్కాలిక != ఖాళీ;                                                  \
         p_తాత్కాలిక = ఖాళీ)                                                   \
        కొరకు (size_t SVE_సురక్షిత_NAME(n) = 0,                                \
                    sve_iteration_advance = svlenu8();                   \
             ({                                                          \
                 ma_pred_name = svwhilelt_b8((int32_t)SVE_సురక్షిత_NAME(n),  \
                                             (int32_t)(ma_stride_కొలత)); \
                 SVE_సురక్షిత_NAME(n) < (ma_stride_కొలత);                    \
             });                                                         \
             SVE_సురక్షిత_NAME(n) += sve_iteration_advance)

#నిర్వచించు sdl_sve_stride_loop_u8 sdl_sve_stride_loop_pixel

#నిర్వచించు sdl_sve_stride_loop_u16(ma_stride_కొలత, ma_pred_name)             \
    కొరకు (svbool_t ma_pred_name, *p_తాత్కాలిక = &ma_pred_name;                   \
         p_తాత్కాలిక != ఖాళీ;                                                   \
         p_తాత్కాలిక = ఖాళీ)                                                    \
        కొరకు (size_t SVE_సురక్షిత_NAME(n) = 0,                                 \
                    sve_iteration_advance = svlenu16();                   \
             ({                                                           \
                 ma_pred_name = svwhilelt_b16((int32_t)SVE_సురక్షిత_NAME(n),  \
                                              (int32_t)(ma_stride_కొలత)); \
                 SVE_సురక్షిత_NAME(n) < (ma_stride_కొలత);                     \
             });                                                          \
             SVE_సురక్షిత_NAME(n) += sve_iteration_advance)

#నిర్వచించు sdl_sve_stride_loop_u32(ma_stride_కొలత, ma_pred_name)             \
    కొరకు (svbool_t ma_pred_name, *p_తాత్కాలిక = &ma_pred_name;                   \
         p_తాత్కాలిక != ఖాళీ;                                                   \
         p_తాత్కాలిక = ఖాళీ)                                                    \
        కొరకు (size_t SVE_సురక్షిత_NAME(n) = 0,                                 \
                    sve_iteration_advance = svlenu32();                   \
             ({                                                           \
                 ma_pred_name = svwhilelt_b16((int32_t)SVE_సురక్షిత_NAME(n),  \
                                              (int32_t)(ma_stride_కొలత)); \
                 SVE_సురక్షిత_NAME(n) < (ma_stride_కొలత);                     \
             });                                                          \
             SVE_సురక్షిత_NAME(n) += sve_iteration_advance)

#నిర్వచించు sdl_sve_pixel_ccc_foreach_chn(ma_ఆధారం_u16x3,                    \
                                      ma_లక్ష్యం_u16x3,                    \
                                      ...)                                \
    చేయి {                                                                  \
        svuint16x3_t sve_ఆధారం_u16x3 = ma_ఆధారం_u16x3;                  \
        (శూన్య)sve_ఆధారం_u16x3;                                           \
        చేయి {                                                              \
            స్థిరరాశి uint8_t sve_src_chn_idx = 0;                            \
            (శూన్య)sve_src_chn_idx;                                        \
            svuint16_t sve_ఆధారం_u16 = svget3((ma_ఆధారం_u16x3), 0);     \
            svuint16_t sve_లక్ష్యం_u16 = svget3((ma_లక్ష్యం_u16x3), 0);     \
            (శూన్య)sve_ఆధారం_u16;                                         \
            (శూన్య)sve_లక్ష్యం_u16;                                         \
            __VA_ARGS__                                                   \
            ma_లక్ష్యం_u16x3 = svset3(ma_లక్ష్యం_u16x3, 0, sve_లక్ష్యం_u16); \
        } అయితే (0);                                                      \
        చేయి {                                                              \
            స్థిరరాశి uint8_t sve_src_chn_idx = 1;                            \
            (శూన్య)sve_src_chn_idx;                                        \
            svuint16_t sve_ఆధారం_u16 = svget3((ma_ఆధారం_u16x3), 1);     \
            svuint16_t sve_లక్ష్యం_u16 = svget3((ma_లక్ష్యం_u16x3), 1);     \
            (శూన్య)sve_ఆధారం_u16;                                         \
            (శూన్య)sve_లక్ష్యం_u16;                                         \
            __VA_ARGS__                                                   \
            ma_లక్ష్యం_u16x3 = svset3(ma_లక్ష్యం_u16x3, 1, sve_లక్ష్యం_u16); \
        } అయితే (0);                                                      \
        చేయి {                                                              \
            స్థిరరాశి uint8_t sve_src_chn_idx = 2;                            \
            (శూన్య)sve_src_chn_idx;                                        \
            svuint16_t sve_ఆధారం_u16 = svget3((ma_ఆధారం_u16x3), 2);     \
            svuint16_t sve_లక్ష్యం_u16 = svget3((ma_లక్ష్యం_u16x3), 2);     \
            (శూన్య)sve_ఆధారం_u16;                                         \
            (శూన్య)sve_లక్ష్యం_u16;                                         \
            __VA_ARGS__                                                   \
            ma_లక్ష్యం_u16x3 = svset3(ma_లక్ష్యం_u16x3, 2, sve_లక్ష్యం_u16); \
        } అయితే (0);                                                      \
    } అయితే (0)

#నిర్వచించు sdl_sve_pixel_accc_foreach_chn012(ma_ఆధారం_u16x4,                \
                                          ma_లక్ష్యం_u16x4,                \
                                          ...)                            \
    చేయి {                                                                  \
        svuint16x4_t sve_ఆధారం_u16x4 = ma_ఆధారం_u16x4;                  \
        (శూన్య)sve_ఆధారం_u16x4;                                           \
        చేయి {                                                              \
            స్థిరరాశి uint8_t sve_src_chn_idx = 0;                            \
            (శూన్య)sve_src_chn_idx;                                        \
            svuint16_t sve_ఆధారం_u16 = svget4((ma_ఆధారం_u16x4), 0);     \
            svuint16_t sve_లక్ష్యం_u16 = svget4((ma_లక్ష్యం_u16x4), 0);     \
            (శూన్య)sve_ఆధారం_u16;                                         \
            (శూన్య)sve_లక్ష్యం_u16;                                         \
            __VA_ARGS__                                                   \
            ma_లక్ష్యం_u16x4 = svset4(ma_లక్ష్యం_u16x4, 0, sve_లక్ష్యం_u16); \
        } అయితే (0);                                                      \
        చేయి {                                                              \
            స్థిరరాశి uint8_t sve_src_chn_idx = 1;                            \
            (శూన్య)sve_src_chn_idx;                                        \
            svuint16_t sve_ఆధారం_u16 = svget4((ma_ఆధారం_u16x4), 1);     \
            svuint16_t sve_లక్ష్యం_u16 = svget4((ma_లక్ష్యం_u16x4), 1);     \
            (శూన్య)sve_ఆధారం_u16;                                         \
            (శూన్య)sve_లక్ష్యం_u16;                                         \
            __VA_ARGS__                                                   \
            ma_లక్ష్యం_u16x4 = svset4(ma_లక్ష్యం_u16x4, 1, sve_లక్ష్యం_u16); \
        } అయితే (0);                                                      \
        చేయి {                                                              \
            స్థిరరాశి uint8_t sve_src_chn_idx = 2;                            \
            (శూన్య)sve_src_chn_idx;                                        \
            svuint16_t sve_ఆధారం_u16 = svget4((ma_ఆధారం_u16x4), 2);     \
            svuint16_t sve_లక్ష్యం_u16 = svget4((ma_లక్ష్యం_u16x4), 2);     \
            (శూన్య)sve_ఆధారం_u16;                                         \
            (శూన్య)sve_లక్ష్యం_u16;                                         \
            __VA_ARGS__                                                   \
            ma_లక్ష్యం_u16x4 = svset4(ma_లక్ష్యం_u16x4, 2, sve_లక్ష్యం_u16); \
        } అయితే (0);                                                      \
    } అయితే (0)

#నిర్వచించు sdl_sve_pixel_accc_foreach_chn(ma_ఆధారం_u16x4,                   \
                                       ma_లక్ష్యం_u16x4,                   \
                                       ...)                               \
    చేయి {                                                                  \
        svuint16x4_t sve_ఆధారం_u16x4 = ma_ఆధారం_u16x4;                  \
        (శూన్య)sve_ఆధారం_u16x4;                                           \
        చేయి {                                                              \
            స్థిరరాశి uint8_t sve_src_chn_idx = 0;                            \
            (శూన్య)sve_src_chn_idx;                                        \
            (శూన్య)sve_dst_chn_idx;                                        \
            svuint16_t sve_ఆధారం_u16 = svget4((ma_ఆధారం_u16x4), 0);     \
            svuint16_t sve_లక్ష్యం_u16 = svget4((ma_లక్ష్యం_u16x4), 0);     \
            (శూన్య)sve_ఆధారం_u16;                                         \
            (శూన్య)sve_లక్ష్యం_u16;                                         \
            __VA_ARGS__                                                   \
            ma_లక్ష్యం_u16x4 = svset4(ma_లక్ష్యం_u16x4, 0, sve_లక్ష్యం_u16); \
        } అయితే (0);                                                      \
        చేయి {                                                              \
            స్థిరరాశి uint8_t sve_src_chn_idx = 1;                            \
            (శూన్య)sve_src_chn_idx;                                        \
            (శూన్య)sve_dst_chn_idx;                                        \
            svuint16_t sve_ఆధారం_u16 = svget4((ma_ఆధారం_u16x4), 1);     \
            svuint16_t sve_లక్ష్యం_u16 = svget4((ma_లక్ష్యం_u16x4), 1);     \
            (శూన్య)sve_ఆధారం_u16;                                         \
            (శూన్య)sve_లక్ష్యం_u16;                                         \
            __VA_ARGS__                                                   \
            ma_లక్ష్యం_u16x4 = svset4(ma_లక్ష్యం_u16x4, 1, sve_లక్ష్యం_u16); \
        } అయితే (0);                                                      \
        చేయి {                                                              \
            స్థిరరాశి uint8_t sve_src_chn_idx = 2;                            \
            (శూన్య)sve_src_chn_idx;                                        \
            (శూన్య)sve_dst_chn_idx;                                        \
            svuint16_t sve_ఆధారం_u16 = svget4((ma_ఆధారం_u16x4), 2);     \
            svuint16_t sve_లక్ష్యం_u16 = svget4((ma_లక్ష్యం_u16x4), 2);     \
            (శూన్య)sve_ఆధారం_u16;                                         \
            (శూన్య)sve_లక్ష్యం_u16;                                         \
            __VA_ARGS__                                                   \
            ma_లక్ష్యం_u16x4 = svset4(ma_లక్ష్యం_u16x4, 2, sve_లక్ష్యం_u16); \
        } అయితే (0);                                                      \
        చేయి {                                                              \
            స్థిరరాశి uint8_t sve_src_chn_idx = 3;                            \
            (శూన్య)sve_src_chn_idx;                                        \
            (శూన్య)sve_dst_chn_idx;                                        \
            svuint16_t sve_ఆధారం_u16 = svget4((ma_ఆధారం_u16x4), 3);     \
            svuint16_t sve_లక్ష్యం_u16 = svget4((ma_లక్ష్యం_u16x4), 3);     \
            (శూన్య)sve_ఆధారం_u16;                                         \
            (శూన్య)sve_లక్ష్యం_u16;                                         \
            __VA_ARGS__                                                   \
            ma_లక్ష్యం_u16x4 = svset4(ma_లక్ష్యం_u16x4, 3, sve_లక్ష్యం_u16); \
        } అయితే (0);                                                      \
    } అయితే (0)

#నిర్వచించు sdl_sve_pixel_u16x4_foreach_chn(ma_ఆధారం_u16x4,                  \
                                        ma_లక్ష్యం_u16x4,                  \
                                        ...)                              \
    చేయి {                                                                  \
        svuint16x4_t sve_ఆధారం_u16x4 = ma_ఆధారం_u16x4;                  \
        (శూన్య)sve_ఆధారం_u16x4;                                           \
        చేయి {                                                              \
            స్థిరరాశి uint8_t sve_src_chn_idx = 0;                            \
            (శూన్య)sve_src_chn_idx;                                        \
            svuint16_t sve_ఆధారం_u16 = svget4((ma_ఆధారం_u16x4), 0);     \
            svuint16_t sve_లక్ష్యం_u16 = svget4((ma_లక్ష్యం_u16x4), 0);     \
            (శూన్య)sve_ఆధారం_u16;                                         \
            (శూన్య)sve_లక్ష్యం_u16;                                         \
            __VA_ARGS__                                                   \
            ma_లక్ష్యం_u16x4 = svset4(ma_లక్ష్యం_u16x4, 0, sve_లక్ష్యం_u16); \
        } అయితే (0);                                                      \
        చేయి {                                                              \
            స్థిరరాశి uint8_t sve_src_chn_idx = 1;                            \
            (శూన్య)sve_src_chn_idx;                                        \
            svuint16_t sve_ఆధారం_u16 = svget4((ma_ఆధారం_u16x4), 1);     \
            svuint16_t sve_లక్ష్యం_u16 = svget4((ma_లక్ష్యం_u16x4), 1);     \
            (శూన్య)sve_ఆధారం_u16;                                         \
            (శూన్య)sve_లక్ష్యం_u16;                                         \
            __VA_ARGS__                                                   \
            ma_లక్ష్యం_u16x4 = svset4(ma_లక్ష్యం_u16x4, 1, sve_లక్ష్యం_u16); \
        } అయితే (0);                                                      \
        చేయి {                                                              \
            స్థిరరాశి uint8_t sve_src_chn_idx = 2;                            \
            (శూన్య)sve_src_chn_idx;                                        \
            svuint16_t sve_ఆధారం_u16 = svget4((ma_ఆధారం_u16x4), 2);     \
            svuint16_t sve_లక్ష్యం_u16 = svget4((ma_లక్ష్యం_u16x4), 2);     \
            (శూన్య)sve_ఆధారం_u16;                                         \
            (శూన్య)sve_లక్ష్యం_u16;                                         \
            __VA_ARGS__                                                   \
            ma_లక్ష్యం_u16x4 = svset4(ma_లక్ష్యం_u16x4, 2, sve_లక్ష్యం_u16); \
        } అయితే (0);                                                      \
        చేయి {                                                              \
            స్థిరరాశి uint8_t sve_src_chn_idx = 3;                            \
            (శూన్య)sve_src_chn_idx;                                        \
            svuint16_t sve_ఆధారం_u16 = svget4((ma_ఆధారం_u16x4), 3);     \
            svuint16_t sve_లక్ష్యం_u16 = svget4((ma_లక్ష్యం_u16x4), 3);     \
            (శూన్య)sve_ఆధారం_u16;                                         \
            (శూన్య)sve_లక్ష్యం_u16;                                         \
            __VA_ARGS__                                                   \
            ma_లక్ష్యం_u16x4 = svset4(ma_లక్ష్యం_u16x4, 3, sve_లక్ష్యం_u16); \
        } అయితే (0);                                                      \
    } అయితే (0)

#నిర్వచించు sdl_sve_pixel_u16x4_foreach_chn_src_dst_rev(ma_ఆధారం_u16x4,      \
                                                    ma_లక్ష్యం_u16x4,      \
                                                    ...)                  \
    చేయి {                                                                  \
        svuint16x4_t sve_ఆధారం_u16x4 = ma_ఆధారం_u16x4;                  \
        (శూన్య)sve_ఆధారం_u16x4;                                           \
        చేయి {                                                              \
            స్థిరరాశి uint8_t sve_src_chn_idx = 0;                            \
            స్థిరరాశి uint8_t sve_dst_chn_idx = 3;                            \
            (శూన్య)sve_src_chn_idx;                                        \
            (శూన్య)sve_dst_chn_idx;                                        \
            svuint16_t sve_ఆధారం_u16 = svget4((ma_ఆధారం_u16x4), 0);     \
            svuint16_t sve_లక్ష్యం_u16 = svget4((ma_లక్ష్యం_u16x4), 3);     \
            (శూన్య)sve_ఆధారం_u16;                                         \
            (శూన్య)sve_లక్ష్యం_u16;                                         \
            __VA_ARGS__                                                   \
            ma_లక్ష్యం_u16x4 = svset4(ma_లక్ష్యం_u16x4, 3, sve_లక్ష్యం_u16); \
        } అయితే (0);                                                      \
        చేయి {                                                              \
            స్థిరరాశి uint8_t sve_src_chn_idx = 1;                            \
            స్థిరరాశి uint8_t sve_dst_chn_idx = 2;                            \
            (శూన్య)sve_src_chn_idx;                                        \
            (శూన్య)sve_dst_chn_idx;                                        \
            svuint16_t sve_ఆధారం_u16 = svget4((ma_ఆధారం_u16x4), 1);     \
            svuint16_t sve_లక్ష్యం_u16 = svget4((ma_లక్ష్యం_u16x4), 2);     \
            (శూన్య)sve_ఆధారం_u16;                                         \
            (శూన్య)sve_లక్ష్యం_u16;                                         \
            __VA_ARGS__                                                   \
            ma_లక్ష్యం_u16x4 = svset4(ma_లక్ష్యం_u16x4, 2, sve_లక్ష్యం_u16); \
        } అయితే (0);                                                      \
        చేయి {                                                              \
            స్థిరరాశి uint8_t sve_src_chn_idx = 2;                            \
            స్థిరరాశి uint8_t sve_dst_chn_idx = 1;                            \
            (శూన్య)sve_src_chn_idx;                                        \
            (శూన్య)sve_dst_chn_idx;                                        \
            svuint16_t sve_ఆధారం_u16 = svget4((ma_ఆధారం_u16x4), 2);     \
            svuint16_t sve_లక్ష్యం_u16 = svget4((ma_లక్ష్యం_u16x4), 1);     \
            (శూన్య)sve_ఆధారం_u16;                                         \
            (శూన్య)sve_లక్ష్యం_u16;                                         \
            __VA_ARGS__                                                   \
            ma_లక్ష్యం_u16x4 = svset4(ma_లక్ష్యం_u16x4, 1, sve_లక్ష్యం_u16); \
        } అయితే (0);                                                      \
        చేయి {                                                              \
            స్థిరరాశి uint8_t sve_src_chn_idx = 3;                            \
            స్థిరరాశి uint8_t sve_dst_chn_idx = 0;                            \
            (శూన్య)sve_src_chn_idx;                                        \
            (శూన్య)sve_dst_chn_idx;                                        \
            svuint16_t sve_ఆధారం_u16 = svget4((ma_ఆధారం_u16x4), 3);     \
            svuint16_t sve_లక్ష్యం_u16 = svget4((ma_లక్ష్యం_u16x4), 0);     \
            (శూన్య)sve_ఆధారం_u16;                                         \
            (శూన్య)sve_లక్ష్యం_u16;                                         \
            __VA_ARGS__                                                   \
            ma_లక్ష్యం_u16x4 = svset4(ma_లక్ష్యం_u16x4, 0, sve_లక్ష్యం_u16); \
        } అయితే (0);                                                      \
    } అయితే (0)

#నిర్వచించు sdl_sve_pixel_u16x4_foreach_chn_accc_ccca(ma_ఆధారం_u16x4,        \
                                                  ma_లక్ష్యం_u16x4,        \
                                                  ...)                    \
    చేయి {                                                                  \
        svuint16x4_t sve_ఆధారం_u16x4 = ma_ఆధారం_u16x4;                  \
        (శూన్య)sve_ఆధారం_u16x4;                                           \
        చేయి {                                                              \
            స్థిరరాశి uint8_t sve_src_chn_idx = 0;                            \
            స్థిరరాశి uint8_t sve_dst_chn_idx = 1;                            \
            (శూన్య)sve_src_chn_idx;                                        \
            (శూన్య)sve_dst_chn_idx;                                        \
            svuint16_t sve_ఆధారం_u16 = svget4((ma_ఆధారం_u16x4), 0);     \
            svuint16_t sve_లక్ష్యం_u16 = svget4((ma_లక్ష్యం_u16x4), 1);     \
            (శూన్య)sve_ఆధారం_u16;                                         \
            (శూన్య)sve_లక్ష్యం_u16;                                         \
            __VA_ARGS__                                                   \
            ma_లక్ష్యం_u16x4 = svset4(ma_లక్ష్యం_u16x4, 1, sve_లక్ష్యం_u16); \
        } అయితే (0);                                                      \
        చేయి {                                                              \
            స్థిరరాశి uint8_t sve_src_chn_idx = 1;                            \
            స్థిరరాశి uint8_t sve_dst_chn_idx = 2;                            \
            (శూన్య)sve_src_chn_idx;                                        \
            (శూన్య)sve_dst_chn_idx;                                        \
            svuint16_t sve_ఆధారం_u16 = svget4((ma_ఆధారం_u16x4), 1);     \
            svuint16_t sve_లక్ష్యం_u16 = svget4((ma_లక్ష్యం_u16x4), 2);     \
            (శూన్య)sve_ఆధారం_u16;                                         \
            (శూన్య)sve_లక్ష్యం_u16;                                         \
            __VA_ARGS__                                                   \
            ma_లక్ష్యం_u16x4 = svset4(ma_లక్ష్యం_u16x4, 2, sve_లక్ష్యం_u16); \
        } అయితే (0);                                                      \
        చేయి {                                                              \
            స్థిరరాశి uint8_t sve_src_chn_idx = 2;                            \
            స్థిరరాశి uint8_t sve_dst_chn_idx = 3;                            \
            (శూన్య)sve_src_chn_idx;                                        \
            (శూన్య)sve_dst_chn_idx;                                        \
            svuint16_t sve_ఆధారం_u16 = svget4((ma_ఆధారం_u16x4), 2);     \
            svuint16_t sve_లక్ష్యం_u16 = svget4((ma_లక్ష్యం_u16x4), 3);     \
            (శూన్య)sve_ఆధారం_u16;                                         \
            (శూన్య)sve_లక్ష్యం_u16;                                         \
            __VA_ARGS__                                                   \
            ma_లక్ష్యం_u16x4 = svset4(ma_లక్ష్యం_u16x4, 3, sve_లక్ష్యం_u16); \
        } అయితే (0);                                                      \
        చేయి {                                                              \
            స్థిరరాశి uint8_t sve_src_chn_idx = 3;                            \
            స్థిరరాశి uint8_t sve_dst_chn_idx = 0;                            \
            (శూన్య)sve_src_chn_idx;                                        \
            (శూన్య)sve_dst_chn_idx;                                        \
            svuint16_t sve_ఆధారం_u16 = svget4((ma_ఆధారం_u16x4), 3);     \
            svuint16_t sve_లక్ష్యం_u16 = svget4((ma_లక్ష్యం_u16x4), 0);     \
            (శూన్య)sve_ఆధారం_u16;                                         \
            (శూన్య)sve_లక్ష్యం_u16;                                         \
            __VA_ARGS__                                                   \
            ma_లక్ష్యం_u16x4 = svset4(ma_లక్ష్యం_u16x4, 0, sve_లక్ష్యం_u16); \
        } అయితే (0);                                                      \
    } అయితే (0)

#నిర్వచించు sdl_sve_pixel_u16x4_foreach_chn_ccca_accc(ma_ఆధారం_u16x4,        \
                                                  ma_లక్ష్యం_u16x4,        \
                                                  ...)                    \
    చేయి {                                                                  \
        svuint16x4_t sve_ఆధారం_u16x4 = ma_ఆధారం_u16x4;                  \
        (శూన్య)sve_ఆధారం_u16x4;                                           \
        చేయి {                                                              \
            స్థిరరాశి uint8_t sve_src_chn_idx = 1;                            \
            స్థిరరాశి uint8_t sve_dst_chn_idx = 0;                            \
            (శూన్య)sve_src_chn_idx;                                        \
            (శూన్య)sve_dst_chn_idx;                                        \
            svuint16_t sve_ఆధారం_u16 = svget4((ma_ఆధారం_u16x4), 1);     \
            svuint16_t sve_లక్ష్యం_u16 = svget4((ma_లక్ష్యం_u16x4), 0);     \
            (శూన్య)sve_ఆధారం_u16;                                         \
            (శూన్య)sve_లక్ష్యం_u16;                                         \
            __VA_ARGS__                                                   \
            ma_లక్ష్యం_u16x4 = svset4(ma_లక్ష్యం_u16x4, 0, sve_లక్ష్యం_u16); \
        } అయితే (0);                                                      \
        చేయి {                                                              \
            స్థిరరాశి uint8_t sve_src_chn_idx = 2;                            \
            స్థిరరాశి uint8_t sve_dst_chn_idx = 1;                            \
            (శూన్య)sve_src_chn_idx;                                        \
            (శూన్య)sve_dst_chn_idx;                                        \
            svuint16_t sve_ఆధారం_u16 = svget4((ma_ఆధారం_u16x4), 2);     \
            svuint16_t sve_లక్ష్యం_u16 = svget4((ma_లక్ష్యం_u16x4), 1);     \
            (శూన్య)sve_ఆధారం_u16;                                         \
            (శూన్య)sve_లక్ష్యం_u16;                                         \
            __VA_ARGS__                                                   \
            ma_లక్ష్యం_u16x4 = svset4(ma_లక్ష్యం_u16x4, 1, sve_లక్ష్యం_u16); \
        } అయితే (0);                                                      \
        చేయి {                                                              \
            స్థిరరాశి uint8_t sve_src_chn_idx = 3;                            \
            స్థిరరాశి uint8_t sve_dst_chn_idx = 2;                            \
            (శూన్య)sve_src_chn_idx;                                        \
            (శూన్య)sve_dst_chn_idx;                                        \
            svuint16_t sve_ఆధారం_u16 = svget4((ma_ఆధారం_u16x4), 3);     \
            svuint16_t sve_లక్ష్యం_u16 = svget4((ma_లక్ష్యం_u16x4), 2);     \
            (శూన్య)sve_ఆధారం_u16;                                         \
            (శూన్య)sve_లక్ష్యం_u16;                                         \
            __VA_ARGS__                                                   \
            ma_లక్ష్యం_u16x4 = svset4(ma_లక్ష్యం_u16x4, 2, sve_లక్ష్యం_u16); \
        } అయితే (0);                                                      \
        చేయి {                                                              \
            స్థిరరాశి uint8_t sve_src_chn_idx = 0;                            \
            స్థిరరాశి uint8_t sve_dst_chn_idx = 3;                            \
            (శూన్య)sve_src_chn_idx;                                        \
            (శూన్య)sve_dst_chn_idx;                                        \
            svuint16_t sve_ఆధారం_u16 = svget4((ma_ఆధారం_u16x4), 0);     \
            svuint16_t sve_లక్ష్యం_u16 = svget4((ma_లక్ష్యం_u16x4), 3);     \
            (శూన్య)sve_ఆధారం_u16;                                         \
            (శూన్య)sve_లక్ష్యం_u16;                                         \
            __VA_ARGS__                                                   \
            ma_లక్ష్యం_u16x4 = svset4(ma_లక్ష్యం_u16x4, 3, sve_లక్ష్యం_u16); \
        } అయితే (0);                                                      \
    } అయితే (0)

#నిర్వచించు sdl_sve_pixel_u16x4_foreach_chn_a123_a321(ma_ఆధారం_u16x4,        \
                                                  ma_లక్ష్యం_u16x4,        \
                                                  ...)                    \
    చేయి {                                                                  \
        svuint16x4_t sve_ఆధారం_u16x4 = ma_ఆధారం_u16x4;                  \
        (శూన్య)sve_ఆధారం_u16x4;                                           \
        చేయి {                                                              \
            స్థిరరాశి uint8_t sve_src_chn_idx = 0;                            \
            స్థిరరాశి uint8_t sve_dst_chn_idx = 2;                            \
            (శూన్య)sve_src_chn_idx;                                        \
            (శూన్య)sve_dst_chn_idx;                                        \
            svuint16_t sve_ఆధారం_u16 = svget4((ma_ఆధారం_u16x4), 0);     \
            svuint16_t sve_లక్ష్యం_u16 = svget4((ma_లక్ష్యం_u16x4), 2);     \
            (శూన్య)sve_ఆధారం_u16;                                         \
            (శూన్య)sve_లక్ష్యం_u16;                                         \
            __VA_ARGS__                                                   \
            ma_లక్ష్యం_u16x4 = svset4(ma_లక్ష్యం_u16x4, 2, sve_లక్ష్యం_u16); \
        } అయితే (0);                                                      \
        చేయి {                                                              \
            స్థిరరాశి uint8_t sve_src_chn_idx = 1;                            \
            స్థిరరాశి uint8_t sve_dst_chn_idx = 1;                            \
            (శూన్య)sve_src_chn_idx;                                        \
            (శూన్య)sve_dst_chn_idx;                                        \
            svuint16_t sve_ఆధారం_u16 = svget4((ma_ఆధారం_u16x4), 1);     \
            svuint16_t sve_లక్ష్యం_u16 = svget4((ma_లక్ష్యం_u16x4), 1);     \
            (శూన్య)sve_ఆధారం_u16;                                         \
            (శూన్య)sve_లక్ష్యం_u16;                                         \
            __VA_ARGS__                                                   \
            ma_లక్ష్యం_u16x4 = svset4(ma_లక్ష్యం_u16x4, 1, sve_లక్ష్యం_u16); \
        } అయితే (0);                                                      \
        చేయి {                                                              \
            స్థిరరాశి uint8_t sve_src_chn_idx = 2;                            \
            స్థిరరాశి uint8_t sve_dst_chn_idx = 0;                            \
            (శూన్య)sve_src_chn_idx;                                        \
            (శూన్య)sve_dst_chn_idx;                                        \
            svuint16_t sve_ఆధారం_u16 = svget4((ma_ఆధారం_u16x4), 2);     \
            svuint16_t sve_లక్ష్యం_u16 = svget4((ma_లక్ష్యం_u16x4), 0);     \
            (శూన్య)sve_ఆధారం_u16;                                         \
            (శూన్య)sve_లక్ష్యం_u16;                                         \
            __VA_ARGS__                                                   \
            ma_లక్ష్యం_u16x4 = svset4(ma_లక్ష్యం_u16x4, 0, sve_లక్ష్యం_u16); \
        } అయితే (0);                                                      \
        చేయి {                                                              \
            స్థిరరాశి uint8_t sve_src_chn_idx = 3;                            \
            స్థిరరాశి uint8_t sve_dst_chn_idx = 3;                            \
            (శూన్య)sve_src_chn_idx;                                        \
            (శూన్య)sve_dst_chn_idx;                                        \
            svuint16_t sve_ఆధారం_u16 = svget4((ma_ఆధారం_u16x4), 3);     \
            svuint16_t sve_లక్ష్యం_u16 = svget4((ma_లక్ష్యం_u16x4), 3);     \
            (శూన్య)sve_ఆధారం_u16;                                         \
            (శూన్య)sve_లక్ష్యం_u16;                                         \
            __VA_ARGS__                                                   \
            ma_లక్ష్యం_u16x4 = svset4(ma_లక్ష్యం_u16x4, 3, sve_లక్ష్యం_u16); \
        } అయితే (0);                                                      \
    } అయితే (0)

#నిర్వచించు sdl_sve_pixel_u16x4_foreach_chn_123a_321a(ma_ఆధారం_u16x4,        \
                                                  ma_లక్ష్యం_u16x4,        \
                                                  ...)                    \
    చేయి {                                                                  \
        svuint16x4_t sve_ఆధారం_u16x4 = ma_ఆధారం_u16x4;                  \
        (శూన్య)sve_ఆధారం_u16x4;                                           \
        చేయి {                                                              \
            స్థిరరాశి uint8_t sve_src_chn_idx = 0;                            \
            స్థిరరాశి uint8_t sve_dst_chn_idx = 0;                            \
            (శూన్య)sve_src_chn_idx;                                        \
            (శూన్య)sve_dst_chn_idx;                                        \
            svuint16_t sve_ఆధారం_u16 = svget4((ma_ఆధారం_u16x4), 0);     \
            svuint16_t sve_లక్ష్యం_u16 = svget4((ma_లక్ష్యం_u16x4), 0);     \
            (శూన్య)sve_ఆధారం_u16;                                         \
            (శూన్య)sve_లక్ష్యం_u16;                                         \
            __VA_ARGS__                                                   \
            ma_లక్ష్యం_u16x4 = svset4(ma_లక్ష్యం_u16x4, 0, sve_లక్ష్యం_u16); \
        } అయితే (0);                                                      \
        చేయి {                                                              \
            స్థిరరాశి uint8_t sve_src_chn_idx = 1;                            \
            స్థిరరాశి uint8_t sve_dst_chn_idx = 3;                            \
            (శూన్య)sve_src_chn_idx;                                        \
            (శూన్య)sve_dst_chn_idx;                                        \
            svuint16_t sve_ఆధారం_u16 = svget4((ma_ఆధారం_u16x4), 1);     \
            svuint16_t sve_లక్ష్యం_u16 = svget4((ma_లక్ష్యం_u16x4), 3);     \
            (శూన్య)sve_ఆధారం_u16;                                         \
            (శూన్య)sve_లక్ష్యం_u16;                                         \
            __VA_ARGS__                                                   \
            ma_లక్ష్యం_u16x4 = svset4(ma_లక్ష్యం_u16x4, 3, sve_లక్ష్యం_u16); \
        } అయితే (0);                                                      \
        చేయి {                                                              \
            స్థిరరాశి uint8_t sve_src_chn_idx = 2;                            \
            స్థిరరాశి uint8_t sve_dst_chn_idx = 2;                            \
            (శూన్య)sve_src_chn_idx;                                        \
            (శూన్య)sve_dst_chn_idx;                                        \
            svuint16_t sve_ఆధారం_u16 = svget4((ma_ఆధారం_u16x4), 2);     \
            svuint16_t sve_లక్ష్యం_u16 = svget4((ma_లక్ష్యం_u16x4), 2);     \
            (శూన్య)sve_ఆధారం_u16;                                         \
            (శూన్య)sve_లక్ష్యం_u16;                                         \
            __VA_ARGS__                                                   \
            ma_లక్ష్యం_u16x4 = svset4(ma_లక్ష్యం_u16x4, 2, sve_లక్ష్యం_u16); \
        } అయితే (0);                                                      \
        చేయి {                                                              \
            స్థిరరాశి uint8_t sve_src_chn_idx = 3;                            \
            స్థిరరాశి uint8_t sve_dst_chn_idx = 1;                            \
            (శూన్య)sve_src_chn_idx;                                        \
            (శూన్య)sve_dst_chn_idx;                                        \
            svuint16_t sve_ఆధారం_u16 = svget4((ma_ఆధారం_u16x4), 3);     \
            svuint16_t sve_లక్ష్యం_u16 = svget4((ma_లక్ష్యం_u16x4), 1);     \
            (శూన్య)sve_ఆధారం_u16;                                         \
            (శూన్య)sve_లక్ష్యం_u16;                                         \
            __VA_ARGS__                                                   \
            ma_లక్ష్యం_u16x4 = svset4(ma_లక్ష్యం_u16x4, 1, sve_లక్ష్యం_u16); \
        } అయితే (0);                                                      \
    } అయితే (0)

#నిర్వచించు sdl_sve_pixel_u16x4_foreach_chn_argb_rgb565(ma_ఆధారం_u16x4,      \
                                                    ma_లక్ష్యం_u16x3,      \
                                                    ...)                  \
    చేయి {                                                                  \
        svuint16x4_t sve_ఆధారం_u16x4 = ma_ఆధారం_u16x4;                  \
        (శూన్య)sve_ఆధారం_u16x4;                                           \
        చేయి {                                                              \
            స్థిరరాశి uint8_t sve_src_chn_idx = 0;                            \
            స్థిరరాశి uint8_t sve_dst_chn_idx = 0;                            \
            (శూన్య)sve_src_chn_idx;                                        \
            (శూన్య)sve_dst_chn_idx;                                        \
            svuint16_t sve_ఆధారం_u16 = svget4((ma_ఆధారం_u16x4), 0);     \
            svuint16_t sve_లక్ష్యం_u16 = svget3((ma_లక్ష్యం_u16x3), 0);     \
            (శూన్య)sve_ఆధారం_u16;                                         \
            (శూన్య)sve_లక్ష్యం_u16;                                         \
            __VA_ARGS__                                                   \
            ma_లక్ష్యం_u16x3 = svset3(ma_లక్ష్యం_u16x3, 0, sve_లక్ష్యం_u16); \
        } అయితే (0);                                                      \
        చేయి {                                                              \
            స్థిరరాశి uint8_t sve_src_chn_idx = 1;                            \
            స్థిరరాశి uint8_t sve_dst_chn_idx = 1;                            \
            (శూన్య)sve_src_chn_idx;                                        \
            (శూన్య)sve_dst_chn_idx;                                        \
            svuint16_t sve_ఆధారం_u16 = svget4((ma_ఆధారం_u16x4), 1);     \
            svuint16_t sve_లక్ష్యం_u16 = svget3((ma_లక్ష్యం_u16x3), 1);     \
            (శూన్య)sve_ఆధారం_u16;                                         \
            (శూన్య)sve_లక్ష్యం_u16;                                         \
            __VA_ARGS__                                                   \
            ma_లక్ష్యం_u16x3 = svset3(ma_లక్ష్యం_u16x3, 1, sve_లక్ష్యం_u16); \
        } అయితే (0);                                                      \
        చేయి {                                                              \
            స్థిరరాశి uint8_t sve_src_chn_idx = 2;                            \
            స్థిరరాశి uint8_t sve_dst_chn_idx = 2;                            \
            (శూన్య)sve_src_chn_idx;                                        \
            (శూన్య)sve_dst_chn_idx;                                        \
            svuint16_t sve_ఆధారం_u16 = svget4((ma_ఆధారం_u16x4), 2);     \
            svuint16_t sve_లక్ష్యం_u16 = svget3((ma_లక్ష్యం_u16x3), 2);     \
            (శూన్య)sve_ఆధారం_u16;                                         \
            (శూన్య)sve_లక్ష్యం_u16;                                         \
            __VA_ARGS__                                                   \
            ma_లక్ష్యం_u16x3 = svset3(ma_లక్ష్యం_u16x3, 2, sve_లక్ష్యం_u16); \
        } అయితే (0);                                                      \
    } అయితే (0)

#నిర్వచించు sdl_sve_pixel_u16x4_foreach_chn_rgba_rgb565(ma_ఆధారం_u16x4,      \
                                                    ma_లక్ష్యం_u16x3,      \
                                                    ...)                  \
    చేయి {                                                                  \
        svuint16x4_t sve_ఆధారం_u16x4 = ma_ఆధారం_u16x4;                  \
        (శూన్య)sve_ఆధారం_u16x4;                                           \
        చేయి {                                                              \
            స్థిరరాశి uint8_t sve_src_chn_idx = 1;                            \
            స్థిరరాశి uint8_t sve_dst_chn_idx = 0;                            \
            (శూన్య)sve_src_chn_idx;                                        \
            (శూన్య)sve_dst_chn_idx;                                        \
            svuint16_t sve_ఆధారం_u16 = svget4((ma_ఆధారం_u16x4), 1);     \
            svuint16_t sve_లక్ష్యం_u16 = svget3((ma_లక్ష్యం_u16x3), 0);     \
            (శూన్య)sve_ఆధారం_u16;                                         \
            (శూన్య)sve_లక్ష్యం_u16;                                         \
            __VA_ARGS__                                                   \
            ma_లక్ష్యం_u16x3 = svset3(ma_లక్ష్యం_u16x3, 0, sve_లక్ష్యం_u16); \
        } అయితే (0);                                                      \
        చేయి {                                                              \
            స్థిరరాశి uint8_t sve_src_chn_idx = 2;                            \
            స్థిరరాశి uint8_t sve_dst_chn_idx = 1;                            \
            (శూన్య)sve_src_chn_idx;                                        \
            (శూన్య)sve_dst_chn_idx;                                        \
            svuint16_t sve_ఆధారం_u16 = svget4((ma_ఆధారం_u16x4), 2);     \
            svuint16_t sve_లక్ష్యం_u16 = svget3((ma_లక్ష్యం_u16x3), 1);     \
            (శూన్య)sve_ఆధారం_u16;                                         \
            (శూన్య)sve_లక్ష్యం_u16;                                         \
            __VA_ARGS__                                                   \
            ma_లక్ష్యం_u16x3 = svset3(ma_లక్ష్యం_u16x3, 1, sve_లక్ష్యం_u16); \
        } అయితే (0);                                                      \
        చేయి {                                                              \
            స్థిరరాశి uint8_t sve_src_chn_idx = 3;                            \
            స్థిరరాశి uint8_t sve_dst_chn_idx = 2;                            \
            (శూన్య)sve_src_chn_idx;                                        \
            (శూన్య)sve_dst_chn_idx;                                        \
            svuint16_t sve_ఆధారం_u16 = svget4((ma_ఆధారం_u16x4), 3);     \
            svuint16_t sve_లక్ష్యం_u16 = svget3((ma_లక్ష్యం_u16x3), 2);     \
            (శూన్య)sve_ఆధారం_u16;                                         \
            (శూన్య)sve_లక్ష్యం_u16;                                         \
            __VA_ARGS__                                                   \
            ma_లక్ష్యం_u16x3 = svset3(ma_లక్ష్యం_u16x3, 2, sve_లక్ష్యం_u16); \
        } అయితే (0);                                                      \
    } అయితే (0)

#నిర్వచించు sdl_sve_pixel_u16x4_foreach_chn_bgra_rgb565(ma_ఆధారం_u16x4,      \
                                                    ma_లక్ష్యం_u16x3,      \
                                                    ...)                  \
    చేయి {                                                                  \
        svuint16x4_t sve_ఆధారం_u16x4 = ma_ఆధారం_u16x4;                  \
        (శూన్య)sve_ఆధారం_u16x4;                                           \
        చేయి {                                                              \
            స్థిరరాశి uint8_t sve_src_chn_idx = 3;                            \
            స్థిరరాశి uint8_t sve_dst_chn_idx = 0;                            \
            (శూన్య)sve_src_chn_idx;                                        \
            (శూన్య)sve_dst_chn_idx;                                        \
            svuint16_t sve_ఆధారం_u16 = svget4((ma_ఆధారం_u16x4), 3);     \
            svuint16_t sve_లక్ష్యం_u16 = svget3((ma_లక్ష్యం_u16x3), 0);     \
            (శూన్య)sve_ఆధారం_u16;                                         \
            (శూన్య)sve_లక్ష్యం_u16;                                         \
            __VA_ARGS__                                                   \
            ma_లక్ష్యం_u16x3 = svset3(ma_లక్ష్యం_u16x3, 0, sve_లక్ష్యం_u16); \
        } అయితే (0);                                                      \
        చేయి {                                                              \
            స్థిరరాశి uint8_t sve_src_chn_idx = 2;                            \
            స్థిరరాశి uint8_t sve_dst_chn_idx = 1;                            \
            (శూన్య)sve_src_chn_idx;                                        \
            (శూన్య)sve_dst_chn_idx;                                        \
            svuint16_t sve_ఆధారం_u16 = svget4((ma_ఆధారం_u16x4), 2);     \
            svuint16_t sve_లక్ష్యం_u16 = svget3((ma_లక్ష్యం_u16x3), 1);     \
            (శూన్య)sve_ఆధారం_u16;                                         \
            (శూన్య)sve_లక్ష్యం_u16;                                         \
            __VA_ARGS__                                                   \
            ma_లక్ష్యం_u16x3 = svset3(ma_లక్ష్యం_u16x3, 1, sve_లక్ష్యం_u16); \
        } అయితే (0);                                                      \
        చేయి {                                                              \
            స్థిరరాశి uint8_t sve_src_chn_idx = 1;                            \
            స్థిరరాశి uint8_t sve_dst_chn_idx = 2;                            \
            (శూన్య)sve_src_chn_idx;                                        \
            (శూన్య)sve_dst_chn_idx;                                        \
            svuint16_t sve_ఆధారం_u16 = svget4((ma_ఆధారం_u16x4), 1);     \
            svuint16_t sve_లక్ష్యం_u16 = svget3((ma_లక్ష్యం_u16x3), 2);     \
            (శూన్య)sve_ఆధారం_u16;                                         \
            (శూన్య)sve_లక్ష్యం_u16;                                         \
            __VA_ARGS__                                                   \
            ma_లక్ష్యం_u16x3 = svset3(ma_లక్ష్యం_u16x3, 2, sve_లక్ష్యం_u16); \
        } అయితే (0);                                                      \
    } అయితే (0)

#నిర్వచించు sdl_sve_pixel_u16x4_foreach_chn_abgr_rgb565(ma_ఆధారం_u16x4,      \
                                                    ma_లక్ష్యం_u16x3,      \
                                                    ...)                  \
    చేయి {                                                                  \
        svuint16x4_t sve_ఆధారం_u16x4 = ma_ఆధారం_u16x4;                  \
        (శూన్య)sve_ఆధారం_u16x4;                                           \
        చేయి {                                                              \
            స్థిరరాశి uint8_t sve_src_chn_idx = 2;                            \
            స్థిరరాశి uint8_t sve_dst_chn_idx = 0;                            \
            (శూన్య)sve_src_chn_idx;                                        \
            (శూన్య)sve_dst_chn_idx;                                        \
            svuint16_t sve_ఆధారం_u16 = svget4((ma_ఆధారం_u16x4), 2);     \
            svuint16_t sve_లక్ష్యం_u16 = svget3((ma_లక్ష్యం_u16x3), 0);     \
            (శూన్య)sve_ఆధారం_u16;                                         \
            (శూన్య)sve_లక్ష్యం_u16;                                         \
            __VA_ARGS__                                                   \
            ma_లక్ష్యం_u16x3 = svset3(ma_లక్ష్యం_u16x3, 0, sve_లక్ష్యం_u16); \
        } అయితే (0);                                                      \
        చేయి {                                                              \
            స్థిరరాశి uint8_t sve_src_chn_idx = 1;                            \
            స్థిరరాశి uint8_t sve_dst_chn_idx = 1;                            \
            (శూన్య)sve_src_chn_idx;                                        \
            (శూన్య)sve_dst_chn_idx;                                        \
            svuint16_t sve_ఆధారం_u16 = svget4((ma_ఆధారం_u16x4), 1);     \
            svuint16_t sve_లక్ష్యం_u16 = svget3((ma_లక్ష్యం_u16x3), 1);     \
            (శూన్య)sve_ఆధారం_u16;                                         \
            (శూన్య)sve_లక్ష్యం_u16;                                         \
            __VA_ARGS__                                                   \
            ma_లక్ష్యం_u16x3 = svset3(ma_లక్ష్యం_u16x3, 1, sve_లక్ష్యం_u16); \
        } అయితే (0);                                                      \
        చేయి {                                                              \
            స్థిరరాశి uint8_t sve_src_chn_idx = 0;                            \
            స్థిరరాశి uint8_t sve_dst_chn_idx = 2;                            \
            (శూన్య)sve_src_chn_idx;                                        \
            (శూన్య)sve_dst_chn_idx;                                        \
            svuint16_t sve_ఆధారం_u16 = svget4((ma_ఆధారం_u16x4), 0);     \
            svuint16_t sve_లక్ష్యం_u16 = svget3((ma_లక్ష్యం_u16x3), 2);     \
            (శూన్య)sve_ఆధారం_u16;                                         \
            (శూన్య)sve_లక్ష్యం_u16;                                         \
            __VA_ARGS__                                                   \
            ma_లక్ష్యం_u16x3 = svset3(ma_లక్ష్యం_u16x3, 2, sve_లక్ష్యం_u16); \
        } అయితే (0);                                                      \
    } అయితే (0)

SDL_TARGETING("arch=armv8-a+sve2")
స్థిర అంతఃవరుస svuint16x3_t sdl_sve_rgb565_unpack(svuint16_t vPixels)
{
    svuint16_t vBlue = svand_n_u16_m(svptrue_b16(), vPixels, 0x1F);
    svuint16_t vGreen = svand_n_u16_m(svptrue_b16(), vPixels, (0x3F << 5));
    svuint16_t vRed = svand_n_u16_m(svptrue_b16(), vPixels, (0x1F << 11));

    తిరిగి svcreate3_u16(svlsl_n_u16_m(svptrue_b16(), vBlue, 3),
                         svlsr_n_u16_m(svptrue_b16(), vGreen, 3),
                         svlsr_n_u16_m(svptrue_b16(), vRed, 8));
}

SDL_TARGETING("arch=armv8-a+sve2")
స్థిర అంతఃవరుస svuint16_t sdl_sve_rgb565_pack(svuint16x3_t vRGB16x3)
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
    తిరిగి svorr_u16_m(svptrue_b16(), vPixel, vBlue);

    // return  (svget3_u16(vRGB16x3, 0) >> 3)
    //     |   ((svget3_u16(vRGB16x3, 1) & (0x3F << 2)) << 3)
    //     |   ((svget3_u16(vRGB16x3, 2) & (0x1F << 3)) << 8);
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(2, 3, 4)
స్థిర అంతఃవరుస శూన్య svld3rgb565_u16(svbool_t vPredu8,
                                   uint16_t *phw_ఆధారం,
                                   svuint16x3_t *pv_దిగువ,
                                   svuint16x3_t *pv_ఎగువ)
{
    svuint8x2_t vInput8x2 = svld2_u8(vPredu8, (uint8_t *)phw_ఆధారం);

    svuint16_t v_దిగువ_Byte_దిగువ_Half = svunpklo_u16(svget2_u8(vInput8x2, 0));
    svuint16_t v_దిగువ_Byte_ఎగువ_Half = svunpkhi_u16(svget2_u8(vInput8x2, 0));

    svuint16_t v_ఎగువ_Byte_దిగువ_Half = svunpklo_u16(svget2_u8(vInput8x2, 1));
    svuint16_t v_ఎగువ_Byte_ఎగువ_Half = svunpkhi_u16(svget2_u8(vInput8x2, 1));

    //*pvLow = sdl_sve_rgb565_unpack  (   vLowByteLowHalf
    //                                |   (vHighByteLowHalf << 8));
    *pv_దిగువ = sdl_sve_rgb565_unpack(
        svorr_u16_m(svptrue_b16(),
                    v_దిగువ_Byte_దిగువ_Half,
                    //(vHighByteLowHalf << 8)
                    svlsl_n_u16_m(svptrue_b16(), v_ఎగువ_Byte_దిగువ_Half, 8)));

    //*pvHigh = sdl_sve_rgb565_unpack (   vLowByteHighHalf
    //                                |   (vHighByteHighHalf << 8));
    *pv_ఎగువ = sdl_sve_rgb565_unpack(
        svorr_u16_m(svptrue_b16(),
                    v_దిగువ_Byte_ఎగువ_Half,
                    //(vHighByteHighHalf << 8)
                    svlsl_n_u16_m(svptrue_b16(), v_ఎగువ_Byte_ఎగువ_Half, 8)));
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(2)
స్థిర అంతఃవరుస శూన్య svst3rgb565_u16(svbool_t vPredu8,
                                   uint16_t *phw_లక్ష్యం,
                                   svuint16x3_t v_దిగువ,
                                   svuint16x3_t v_ఎగువ)
{
    svuint16_t v_దిగువ_Byte_దిగువ_Half = svundef_u16();
    svuint16_t v_ఎగువ_Byte_దిగువ_Half = svundef_u16();

    /* pack low half pixels */
    చేయి {
        svuint16_t vPixel = sdl_sve_rgb565_pack(v_దిగువ);

        // vLowByteLowHalf = vPixel & 0xFF;
        v_దిగువ_Byte_దిగువ_Half = svand_n_u16_m(svptrue_b16(), vPixel, 0xFF);

        // vHighByteLowHalf = vPixel >> 8;
        v_ఎగువ_Byte_దిగువ_Half = svlsr_n_u16_m(svptrue_b16(), vPixel, 8);
    } అయితే (0);

    svuint16_t v_దిగువ_Byte_ఎగువ_Half = svundef_u16();
    svuint16_t v_ఎగువ_Byte_ఎగువ_Half = svundef_u16();

    /* pack high half pixels */
    చేయి {
        svuint16_t vPixel = sdl_sve_rgb565_pack(v_ఎగువ);

        // vLowByteHighHalf = vPixel & 0xFF;
        v_దిగువ_Byte_ఎగువ_Half = svand_n_u16_m(svptrue_b16(), vPixel, 0xFF);

        // vHighByteHighHalf = vPixel >> 8;
        v_ఎగువ_Byte_ఎగువ_Half = svlsr_n_u16_m(svptrue_b16(), vPixel, 8);
    } అయితే (0);

    /* save rgb565 pixels */
    svuint8_t v_దిగువ_Byte = svuzp1_u8(svreinterpret_u8(v_దిగువ_Byte_దిగువ_Half),
                                   svreinterpret_u8(v_దిగువ_Byte_ఎగువ_Half));

    svuint8_t v_ఎగువ_Byte = svuzp1_u8(svreinterpret_u8(v_ఎగువ_Byte_దిగువ_Half),
                                    svreinterpret_u8(v_ఎగువ_Byte_ఎగువ_Half));

    svst2_u8(vPredu8, (uint8_t *)phw_లక్ష్యం, svcreate2_u8(v_దిగువ_Byte, v_ఎగువ_Byte));
}

#ఒకవేళ defined(__GNUC__) && !defined(__clang__)
#నిర్వచించు svld4ub_u16(ma_pred,                                                                                         \
                    ma_src_ptr,                                                                                      \
                    ma_svuint16x4_దిగువ_ptr,                                                                           \
                    ma_svuint16x4_ఎగువ_ptr)                                                                          \
    చేయి {                                                                                                             \
        svuint8x4_t vInput8x4 = svld4_u8((ma_pred), (ma_src_ptr));                                                   \
                                                                                                                     \
        *(ma_svuint16x4_దిగువ_ptr) = svset4_u16(*(ma_svuint16x4_దిగువ_ptr), 0, svunpklo_u16(svget4_u8(vInput8x4, 0)));   \
        *(ma_svuint16x4_దిగువ_ptr) = svset4_u16(*(ma_svuint16x4_దిగువ_ptr), 1, svunpklo_u16(svget4_u8(vInput8x4, 1)));   \
        *(ma_svuint16x4_దిగువ_ptr) = svset4_u16(*(ma_svuint16x4_దిగువ_ptr), 2, svunpklo_u16(svget4_u8(vInput8x4, 2)));   \
        *(ma_svuint16x4_దిగువ_ptr) = svset4_u16(*(ma_svuint16x4_దిగువ_ptr), 3, svunpklo_u16(svget4_u8(vInput8x4, 3)));   \
                                                                                                                     \
        *(ma_svuint16x4_ఎగువ_ptr) = svset4_u16(*(ma_svuint16x4_ఎగువ_ptr), 0, svunpkhi_u16(svget4_u8(vInput8x4, 0))); \
        *(ma_svuint16x4_ఎగువ_ptr) = svset4_u16(*(ma_svuint16x4_ఎగువ_ptr), 1, svunpkhi_u16(svget4_u8(vInput8x4, 1))); \
        *(ma_svuint16x4_ఎగువ_ptr) = svset4_u16(*(ma_svuint16x4_ఎగువ_ptr), 2, svunpkhi_u16(svget4_u8(vInput8x4, 2))); \
        *(ma_svuint16x4_ఎగువ_ptr) = svset4_u16(*(ma_svuint16x4_ఎగువ_ptr), 3, svunpkhi_u16(svget4_u8(vInput8x4, 3))); \
    } అయితే (0)

#నిర్వచించు svst4ub_u16(ma_pred,                                                                 \
                    ma_dst_ptr,                                                              \
                    ma_svuint16x4_దిగువ,                                                       \
                    ma_svuint16x4_ఎగువ)                                                      \
    చేయి {                                                                                     \
        svuint8_t vCH0u8 = svuzp1_u8(svreinterpret_u8(svget4_u16((ma_svuint16x4_దిగువ), 0)),   \
                                     svreinterpret_u8(svget4_u16((ma_svuint16x4_ఎగువ), 0))); \
                                                                                             \
        svuint8_t vCH1u8 = svuzp1_u8(svreinterpret_u8(svget4_u16((ma_svuint16x4_దిగువ), 1)),   \
                                     svreinterpret_u8(svget4_u16((ma_svuint16x4_ఎగువ), 1))); \
                                                                                             \
        svuint8_t vCH2u8 = svuzp1_u8(svreinterpret_u8(svget4_u16((ma_svuint16x4_దిగువ), 2)),   \
                                     svreinterpret_u8(svget4_u16((ma_svuint16x4_ఎగువ), 2))); \
                                                                                             \
        svuint8_t vCH3u8 = svuzp1_u8(svreinterpret_u8(svget4_u16((ma_svuint16x4_దిగువ), 3)),   \
                                     svreinterpret_u8(svget4_u16((ma_svuint16x4_ఎగువ), 3))); \
                                                                                             \
        svst4_u8((ma_pred), (ma_dst_ptr), svcreate4_u8(vCH0u8, vCH1u8, vCH2u8, vCH3u8));     \
    } అయితే (0)
#లేకపోతే
SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(2, 3, 4)
స్థిర అంతఃవరుస శూన్య svld4ub_u16(svbool_t vPredu8,
                               uint8_t *pch_ఆధారం,
                               svuint16x4_t *pv_దిగువ,
                               svuint16x4_t *pv_ఎగువ)
{
    svuint8x4_t vInput8x4 = svld4_u8(vPredu8, pch_ఆధారం);

    *pv_దిగువ = svset4_u16(*pv_దిగువ, 0, svunpklo_u16(svget4_u8(vInput8x4, 0)));
    *pv_దిగువ = svset4_u16(*pv_దిగువ, 1, svunpklo_u16(svget4_u8(vInput8x4, 1)));
    *pv_దిగువ = svset4_u16(*pv_దిగువ, 2, svunpklo_u16(svget4_u8(vInput8x4, 2)));
    *pv_దిగువ = svset4_u16(*pv_దిగువ, 3, svunpklo_u16(svget4_u8(vInput8x4, 3)));

    *pv_ఎగువ = svset4_u16(*pv_ఎగువ, 0, svunpkhi_u16(svget4_u8(vInput8x4, 0)));
    *pv_ఎగువ = svset4_u16(*pv_ఎగువ, 1, svunpkhi_u16(svget4_u8(vInput8x4, 1)));
    *pv_ఎగువ = svset4_u16(*pv_ఎగువ, 2, svunpkhi_u16(svget4_u8(vInput8x4, 2)));
    *pv_ఎగువ = svset4_u16(*pv_ఎగువ, 3, svunpkhi_u16(svget4_u8(vInput8x4, 3)));
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(2)
స్థిర అంతఃవరుస శూన్య svst4ub_u16(svbool_t vPredu8,
                               uint8_t *pch_లక్ష్యం,
                               svuint16x4_t v_దిగువ,
                               svuint16x4_t v_ఎగువ)
{

    svuint8_t vCH0u8 = svuzp1_u8(svreinterpret_u8(svget4_u16(v_దిగువ, 0)),
                                 svreinterpret_u8(svget4_u16(v_ఎగువ, 0)));

    svuint8_t vCH1u8 = svuzp1_u8(svreinterpret_u8(svget4_u16(v_దిగువ, 1)),
                                 svreinterpret_u8(svget4_u16(v_ఎగువ, 1)));

    svuint8_t vCH2u8 = svuzp1_u8(svreinterpret_u8(svget4_u16(v_దిగువ, 2)),
                                 svreinterpret_u8(svget4_u16(v_ఎగువ, 2)));

    svuint8_t vCH3u8 = svuzp1_u8(svreinterpret_u8(svget4_u16(v_దిగువ, 3)),
                                 svreinterpret_u8(svget4_u16(v_ఎగువ, 3)));

    svst4_u8(vPredu8, pch_లక్ష్యం, svcreate4_u8(vCH0u8, vCH1u8, vCH2u8, vCH3u8));
}
#అయితే_ముగింపు

/*! \note the Element range of vMask is [0, 0xFF]
 */
SDL_TARGETING("arch=armv8-a+sve2")
స్థిర అంతఃవరుస svuint16_t sdl_sve_chn_blend_with_ముసుగు(svuint16_t v_ఆధారం,
                                                     svuint16_t v_లక్ష్యం,
                                                     svuint16_t v_ముసుగు)
{
    // vTarget = vSource * vMask + vTarget * (255 - vMask);
    svuint16_t vTemp0 = svdup_u16(1);
    vTemp0 = svmla_u16_m(svptrue_b16(), vTemp0, v_ఆధారం, v_ముసుగు);
    vTemp0 = svmla_u16_m(svptrue_b16(),
                         vTemp0,
                         v_లక్ష్యం,
                         svsub_u16_m(svptrue_b16(),
                                     svdup_u16(255),
                                     v_ముసుగు));

    /* x += x >> 8 */
    తిరిగి svreinterpret_u16_u8(
        svaddhnb_u16(vTemp0,
                     svlsr_n_u16_m(svptrue_b16(),
                                   vTemp0,
                                   8)));
}
/*! \note the Element range of vMask is [0, 0xFF]
 */
SDL_TARGETING("arch=armv8-a+sve2")
స్థిర అంతఃవరుస svuint16_t sdl_sve_chn_blend_with_ముసుగు_fast(svuint16_t v_ఆధారం,
                                                          svuint16_t v_లక్ష్యం,
                                                          svuint16_t v_ముసుగు)
{
    // vTarget = vSource * vMask + vTarget * (255 - vMask);
    svuint16_t vTemp0 = svmul_u16_m(svptrue_b16(), v_ఆధారం, v_ముసుగు);
    vTemp0 = svmla_u16_m(svptrue_b16(),
                         vTemp0,
                         v_లక్ష్యం,
                         svsub_u16_m(svptrue_b16(),
                                     svdup_u16(255),
                                     v_ముసుగు));

    తిరిగి svlsr_n_u16_m(svptrue_b16(), vTemp0, 8); // vTarget >> 8;
}

/*! \note the hwOpacity range [0, 0x100]
 */
SDL_TARGETING("arch=armv8-a+sve2")
స్థిర అంతఃవరుస svuint16_t sdl_sve_chn_blend_with_opacity(svuint16_t v_ఆధారం,
                                                        svuint16_t v_లక్ష్యం,
                                                        uint16_t hwOpacity)
{
    // svuint16_t vOpacity = svdup_u16(hwOpacity);
    // vTarget = vSource * vOpacity + vTarget * (256 - vOpacity);

    svuint16_t vTemp0 = svmul_n_u16_m(svptrue_b16(), v_ఆధారం, hwOpacity);
    svuint16_t vTemp1 = svmul_n_u16_m(svptrue_b16(),
                                      v_లక్ష్యం,
                                      256 - hwOpacity);
    v_లక్ష్యం = svadd_u16_m(svptrue_b16(), vTemp0, vTemp1);

    తిరిగి svlsr_n_u16_m(svptrue_b16(), v_లక్ష్యం, 8); // vTarget >> 8;
}

/*! \note the hwOpacity range [0, 0x100]
 */
SDL_TARGETING("arch=armv8-a+sve2")
స్థిర అంతఃవరుస svuint16_t sdl_sve_chn_blend_with_opacity_fast(svuint16_t v_ఆధారం,
                                                             svuint16_t v_లక్ష్యం,
                                                             uint16_t hwOpacity)
{
    // vTarget = vSource * vMask + vTarget * (255 - vMask);
    svuint16_t vTemp0 = svmul_n_u16_m(svptrue_b16(), v_ఆధారం, hwOpacity);
    vTemp0 = svmla_n_u16_m(svptrue_b16(),
                           vTemp0,
                           v_లక్ష్యం,
                           256 - hwOpacity);

    తిరిగి svlsr_n_u16_m(svptrue_b16(), vTemp0, 8); // vTarget >> 8;
}

/*! \note the Element range of vMask is [0, 0xFF]
 *  \note the hwOpacity range [0, 0x100]
 */
SDL_TARGETING("arch=armv8-a+sve2")
స్థిర అంతఃవరుస svuint16_t sdl_sve_chn_blend_with_ముసుగు_and_opacity(svuint16_t v_ఆధారం,
                                                                 svuint16_t v_లక్ష్యం,
                                                                 svuint16_t v_ముసుగు,
                                                                 uint16_t hwOpacity)
{
    v_ముసుగు = svsel(svcmpeq_n_u16(svptrue_b16(), v_ముసుగు, 255),
                  svdup_u16(hwOpacity),
                  //(vMask * hwOpacity) >> 8,
                  svlsr_n_u16_m(svptrue_b16(),
                                svmul_n_u16_m(svptrue_b16(), v_ముసుగు, hwOpacity),
                                8));

    // vTarget = vSource * vMask + vTarget * (256 - vMask);
    svuint16_t vTemp0 = svmul_u16_m(svptrue_b16(), v_ఆధారం, v_ముసుగు);
    svuint16_t vTemp1 = svmul_u16_m(svptrue_b16(),
                                    v_లక్ష్యం,
                                    svsub_u16_m(svptrue_b16(),
                                                svdup_u16(256),
                                                v_ముసుగు));
    v_లక్ష్యం = svadd_u16_m(svptrue_b16(), vTemp0, vTemp1);

    తిరిగి svlsr_n_u16_m(svptrue_b16(), v_లక్ష్యం, 8); // vTarget >> 8;
}

/*! \note the Element range of vMask0/1 is [0, 0xFF]
 */
SDL_TARGETING("arch=armv8-a+sve2")
స్థిర అంతఃవరుస svuint16_t sdl_sve_chn_blend_with_masks(svuint16_t v_ఆధారం,
                                                      svuint16_t v_లక్ష్యం,
                                                      svuint16_t vMask0,
                                                      svuint16_t vMask1)
{
    vMask1 = svadd_u16_m(svcmpeq_n_u16(svptrue_b16(), vMask1, 255),
                         vMask1,
                         svdup_u16(1));

    svuint16_t v_ముసుగు =
        svsel(svcmpge_n_u16(svptrue_b16(), vMask0, 255),
              vMask1,
              //(vMask0 * vMask1) >> 8,
              svlsr_n_u16_m(svptrue_b16(),
                            svmul_u16_m(svptrue_b16(), vMask0, vMask1),
                            8));

    // vTarget = vSource * vMask + vTarget * (256 - vMask);
    svuint16_t vTemp0 = svmul_u16_m(svptrue_b16(), v_ఆధారం, v_ముసుగు);
    svuint16_t vTemp1 = svmul_u16_m(svptrue_b16(),
                                    v_లక్ష్యం,
                                    svsub_u16_m(svptrue_b16(),
                                                svdup_u16(256),
                                                v_ముసుగు));
    v_లక్ష్యం = svadd_u16_m(svptrue_b16(), vTemp0, vTemp1);

    తిరిగి svlsr_n_u16_m(svptrue_b16(), v_లక్ష్యం, 8); // vTarget >> 8;
}

/*! \note the Element range of vMask0/1 is [0, 0xFF]
 *  \note the hwOpacity range [0, 0x100]
 */
SDL_TARGETING("arch=armv8-a+sve2")
స్థిర అంతఃవరుస svuint16_t sdl_sve_chn_blend_with_masks_and_opacity(
    svuint16_t v_ఆధారం,
    svuint16_t v_లక్ష్యం,
    svuint16_t vMask0,
    svuint16_t vMask1,
    uint16_t hwOpacity)
{
    vMask0 = svadd_u16_m(svcmpeq_n_u16(svptrue_b16(), vMask0, 255),
                         vMask0,
                         svdup_u16(1));

    svuint16_t v_ముసుగు =
        svsel(svcmpge_n_u16(svptrue_b16(), vMask1, 255), /* >= 255 */
              vMask0,
              //(vMask0 * vMask1) >> 8
              svlsr_n_u16_m(svptrue_b16(),
                            svmul_u16_m(svptrue_b16(), vMask0, vMask1),
                            8));

    v_ముసుగు =
        svsel(svcmpge_n_u16(svptrue_b16(), v_ముసుగు, 255),
              svdup_u16(hwOpacity),
              //(vMask * hwOpacity) >> 8,
              svlsr_n_u16_m(svptrue_b16(),
                            svmul_n_u16_m(svptrue_b16(), v_ముసుగు, hwOpacity),
                            8));

    // vTarget = vSource * vMask + vTarget * (256 - vMask);
    svuint16_t vTemp0 = svmul_u16_m(svptrue_b16(), v_ఆధారం, v_ముసుగు);
    svuint16_t vTemp1 = svmul_u16_m(svptrue_b16(),
                                    v_లక్ష్యం,
                                    svsub_u16_m(svptrue_b16(),
                                                svdup_u16(256),
                                                v_ముసుగు));
    v_లక్ష్యం = svadd_u16_m(svptrue_b16(), vTemp0, vTemp1);

    తిరిగి svlsr_n_u16_m(svptrue_b16(), v_లక్ష్యం, 8); // vTarget >> 8;
}

/*! \note the Element range of vMask0/1 is [0, 0xFF]
 */
SDL_TARGETING("arch=armv8-a+sve2")
స్థిర అంతఃవరుస svuint16_t sdl_sve_chn_blend_with_3masks(svuint16_t v_ఆధారం,
                                                       svuint16_t v_లక్ష్యం,
                                                       svuint16_t vMask0,
                                                       svuint16_t vMask1,
                                                       svuint16_t vMask2)
{
    vMask0 = svadd_u16_m(svcmpeq_n_u16(svptrue_b16(), vMask0, 255),
                         vMask0,
                         svdup_u16(1));

    svuint16_t v_ముసుగు =
        svsel(svcmpge_n_u16(svptrue_b16(), vMask1, 255),
              vMask0,
              //(vMask0 * vMask1) >> 8
              svlsr_n_u16_m(svptrue_b16(),
                            svmul_u16_m(svptrue_b16(), vMask0, vMask1),
                            8));

    v_ముసుగు =
        svsel(svcmpge_n_u16(svptrue_b16(), vMask2, 255),
              v_ముసుగు,
              //(vMask * vMask2) >> 8
              svlsr_n_u16_m(svptrue_b16(),
                            svmul_u16_m(svptrue_b16(), v_ముసుగు, vMask2),
                            8));

    // vTarget = vSource * vMask + vTarget * (256 - vMask);
    svuint16_t vTemp0 = svmul_u16_m(svptrue_b16(), v_ఆధారం, v_ముసుగు);
    svuint16_t vTemp1 = svmul_u16_m(svptrue_b16(),
                                    v_లక్ష్యం,
                                    svsub_u16_m(svptrue_b16(),
                                                svdup_u16(256),
                                                v_ముసుగు));
    v_లక్ష్యం = svadd_u16_m(svptrue_b16(), vTemp0, vTemp1);

    తిరిగి svlsr_n_u16_m(svptrue_b16(), v_లక్ష్యం, 8); // vTarget >> 8;
}

/*! \note the Element range of vMask0/1 is [0, 0xFF]
 *  \note the hwOpacity range [0, 0x100]
 */
SDL_TARGETING("arch=armv8-a+sve2")
స్థిర అంతఃవరుస svuint16_t sdl_sve_chn_blend_with_3masks_and_opacity(
    svuint16_t v_ఆధారం,
    svuint16_t v_లక్ష్యం,
    svuint16_t vMask0,
    svuint16_t vMask1,
    svuint16_t vMask2,
    uint16_t hwOpacity)
{
    vMask0 = svadd_u16_m(svcmpeq_n_u16(svptrue_b16(), vMask0, 255),
                         vMask0,
                         svdup_u16(1));

    svuint16_t v_ముసుగు =
        svsel(svcmpge_n_u16(svptrue_b16(), vMask1, 255),
              vMask0,
              //(vMask0 * vMask1) >> 8
              svlsr_n_u16_m(svptrue_b16(),
                            svmul_u16_m(svptrue_b16(), vMask0, vMask1),
                            8));

    v_ముసుగు =
        svsel(svcmpge_n_u16(svptrue_b16(), vMask2, 255),
              v_ముసుగు,
              svlsr_n_u16_m(svptrue_b16(),
                            svmul_u16_m(svptrue_b16(), v_ముసుగు, vMask2),
                            8));
    //(vMask * vMask2) >> 8);

    v_ముసుగు =
        svsel(svcmpge_n_u16(svptrue_b16(), v_ముసుగు, 255),
              svdup_u16(hwOpacity),
              //(vMask * hwOpacity) >> 8
              svlsr_n_u16_m(svptrue_b16(),
                            svmul_n_u16_m(svptrue_b16(), v_ముసుగు, hwOpacity),
                            8));

    // vTarget = vSource * vMask + vTarget * (256 - vMask);
    svuint16_t vTemp0 = svmul_u16_m(svptrue_b16(), v_ఆధారం, v_ముసుగు);
    svuint16_t vTemp1 = svmul_u16_m(svptrue_b16(),
                                    v_లక్ష్యం,
                                    svsub_u16_m(svptrue_b16(),
                                                svdup_u16(256),
                                                v_ముసుగు));
    v_లక్ష్యం = svadd_u16_m(svptrue_b16(), vTemp0, vTemp1);

    తిరిగి svlsr_n_u16_m(svptrue_b16(), v_లక్ష్యం, 8); // vTarget >> 8;
}

#అయితే_ముగింపు /* SDL_SVE2_EXTENSION_H */