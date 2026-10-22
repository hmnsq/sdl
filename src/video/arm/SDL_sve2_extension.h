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

#اگر !defined(SDL_SVE2_EXTENSION_H) //&& (defined(__ARM_FEATURE_SVE2) && __ARM_FEATURE_SVE2)
#تعریف_کرو SDL_SVE2_EXTENSION_H

#شامل "SDL_sve2_util.h"

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
#اگر_تعریف_شدہ SDL_PLATFORM_ANDROID
#اگر_غیر_تعریف_شدہ __ARM_FEATURE_SVE
#تعریف_کرو __ARM_FEATURE_SVE 1
#اگر_ختم
#اگر_ختم
#شامل <arm_sve.h>
#شامل <stdint.h>

/*!
 * \brief a wrapper for __attribute__((nonnull))
 */
#اگر_غیر_تعریف_شدہ ARM_NONNULL
#تعریف_کرو ARM_NONNULL(...) __attribute__((nonnull(__VA_ARGS__)))
#اگر_ختم

#تعریف_کرو svlenu8()  svcntb_pat(SV_ALL)
#تعریف_کرو svlenu16() (svcntb_pat(SV_ALL) / حجم(uint16_t))
#تعریف_کرو svlenu32() (svcntb_pat(SV_ALL) / حجم(uint32_t))
#تعریف_کرو svlenu64() (svcntb_pat(SV_ALL) / حجم(uint64_t))

#تعریف_کرو svlens8()  svlenu8()
#تعریف_کرو svlens16() svlenu16()
#تعریف_کرو svlens32() svlenu32()
#تعریف_کرو svlens64() svlenu64()

#تعریف_کرو sdl_sve_stride_loop_pixel(ma_stride_سائز, ma_pred_name)          \
    برائے (svbool_t ma_pred_name, *p_عارضی = &ma_pred_name;                  \
         p_عارضی != تہی;                                                  \
         p_عارضی = تہی)                                                   \
        برائے (size_t SVE_محفوظ_NAME(n) = 0,                                \
                    sve_iteration_advance = svlenu8();                   \
             ({                                                          \
                 ma_pred_name = svwhilelt_b8((int32_t)SVE_محفوظ_NAME(n),  \
                                             (int32_t)(ma_stride_سائز)); \
                 SVE_محفوظ_NAME(n) < (ma_stride_سائز);                    \
             });                                                         \
             SVE_محفوظ_NAME(n) += sve_iteration_advance)

#تعریف_کرو sdl_sve_stride_loop_u8 sdl_sve_stride_loop_pixel

#تعریف_کرو sdl_sve_stride_loop_u16(ma_stride_سائز, ma_pred_name)             \
    برائے (svbool_t ma_pred_name, *p_عارضی = &ma_pred_name;                   \
         p_عارضی != تہی;                                                   \
         p_عارضی = تہی)                                                    \
        برائے (size_t SVE_محفوظ_NAME(n) = 0,                                 \
                    sve_iteration_advance = svlenu16();                   \
             ({                                                           \
                 ma_pred_name = svwhilelt_b16((int32_t)SVE_محفوظ_NAME(n),  \
                                              (int32_t)(ma_stride_سائز)); \
                 SVE_محفوظ_NAME(n) < (ma_stride_سائز);                     \
             });                                                          \
             SVE_محفوظ_NAME(n) += sve_iteration_advance)

#تعریف_کرو sdl_sve_stride_loop_u32(ma_stride_سائز, ma_pred_name)             \
    برائے (svbool_t ma_pred_name, *p_عارضی = &ma_pred_name;                   \
         p_عارضی != تہی;                                                   \
         p_عارضی = تہی)                                                    \
        برائے (size_t SVE_محفوظ_NAME(n) = 0,                                 \
                    sve_iteration_advance = svlenu32();                   \
             ({                                                           \
                 ma_pred_name = svwhilelt_b16((int32_t)SVE_محفوظ_NAME(n),  \
                                              (int32_t)(ma_stride_سائز)); \
                 SVE_محفوظ_NAME(n) < (ma_stride_سائز);                     \
             });                                                          \
             SVE_محفوظ_NAME(n) += sve_iteration_advance)

#تعریف_کرو sdl_sve_pixel_ccc_foreach_chn(ma_ماخذ_u16x3,                    \
                                      ma_ہدف_u16x3,                    \
                                      ...)                                \
    کرو {                                                                  \
        svuint16x3_t sve_ماخذ_u16x3 = ma_ماخذ_u16x3;                  \
        (خالی)sve_ماخذ_u16x3;                                           \
        کرو {                                                              \
            ثابت uint8_t sve_src_chn_idx = 0;                            \
            (خالی)sve_src_chn_idx;                                        \
            svuint16_t sve_ماخذ_u16 = svget3((ma_ماخذ_u16x3), 0);     \
            svuint16_t sve_ہدف_u16 = svget3((ma_ہدف_u16x3), 0);     \
            (خالی)sve_ماخذ_u16;                                         \
            (خالی)sve_ہدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ہدف_u16x3 = svset3(ma_ہدف_u16x3, 0, sve_ہدف_u16); \
        } جب (0);                                                      \
        کرو {                                                              \
            ثابت uint8_t sve_src_chn_idx = 1;                            \
            (خالی)sve_src_chn_idx;                                        \
            svuint16_t sve_ماخذ_u16 = svget3((ma_ماخذ_u16x3), 1);     \
            svuint16_t sve_ہدف_u16 = svget3((ma_ہدف_u16x3), 1);     \
            (خالی)sve_ماخذ_u16;                                         \
            (خالی)sve_ہدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ہدف_u16x3 = svset3(ma_ہدف_u16x3, 1, sve_ہدف_u16); \
        } جب (0);                                                      \
        کرو {                                                              \
            ثابت uint8_t sve_src_chn_idx = 2;                            \
            (خالی)sve_src_chn_idx;                                        \
            svuint16_t sve_ماخذ_u16 = svget3((ma_ماخذ_u16x3), 2);     \
            svuint16_t sve_ہدف_u16 = svget3((ma_ہدف_u16x3), 2);     \
            (خالی)sve_ماخذ_u16;                                         \
            (خالی)sve_ہدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ہدف_u16x3 = svset3(ma_ہدف_u16x3, 2, sve_ہدف_u16); \
        } جب (0);                                                      \
    } جب (0)

#تعریف_کرو sdl_sve_pixel_accc_foreach_chn012(ma_ماخذ_u16x4,                \
                                          ma_ہدف_u16x4,                \
                                          ...)                            \
    کرو {                                                                  \
        svuint16x4_t sve_ماخذ_u16x4 = ma_ماخذ_u16x4;                  \
        (خالی)sve_ماخذ_u16x4;                                           \
        کرو {                                                              \
            ثابت uint8_t sve_src_chn_idx = 0;                            \
            (خالی)sve_src_chn_idx;                                        \
            svuint16_t sve_ماخذ_u16 = svget4((ma_ماخذ_u16x4), 0);     \
            svuint16_t sve_ہدف_u16 = svget4((ma_ہدف_u16x4), 0);     \
            (خالی)sve_ماخذ_u16;                                         \
            (خالی)sve_ہدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ہدف_u16x4 = svset4(ma_ہدف_u16x4, 0, sve_ہدف_u16); \
        } جب (0);                                                      \
        کرو {                                                              \
            ثابت uint8_t sve_src_chn_idx = 1;                            \
            (خالی)sve_src_chn_idx;                                        \
            svuint16_t sve_ماخذ_u16 = svget4((ma_ماخذ_u16x4), 1);     \
            svuint16_t sve_ہدف_u16 = svget4((ma_ہدف_u16x4), 1);     \
            (خالی)sve_ماخذ_u16;                                         \
            (خالی)sve_ہدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ہدف_u16x4 = svset4(ma_ہدف_u16x4, 1, sve_ہدف_u16); \
        } جب (0);                                                      \
        کرو {                                                              \
            ثابت uint8_t sve_src_chn_idx = 2;                            \
            (خالی)sve_src_chn_idx;                                        \
            svuint16_t sve_ماخذ_u16 = svget4((ma_ماخذ_u16x4), 2);     \
            svuint16_t sve_ہدف_u16 = svget4((ma_ہدف_u16x4), 2);     \
            (خالی)sve_ماخذ_u16;                                         \
            (خالی)sve_ہدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ہدف_u16x4 = svset4(ma_ہدف_u16x4, 2, sve_ہدف_u16); \
        } جب (0);                                                      \
    } جب (0)

#تعریف_کرو sdl_sve_pixel_accc_foreach_chn(ma_ماخذ_u16x4,                   \
                                       ma_ہدف_u16x4,                   \
                                       ...)                               \
    کرو {                                                                  \
        svuint16x4_t sve_ماخذ_u16x4 = ma_ماخذ_u16x4;                  \
        (خالی)sve_ماخذ_u16x4;                                           \
        کرو {                                                              \
            ثابت uint8_t sve_src_chn_idx = 0;                            \
            (خالی)sve_src_chn_idx;                                        \
            (خالی)sve_dst_chn_idx;                                        \
            svuint16_t sve_ماخذ_u16 = svget4((ma_ماخذ_u16x4), 0);     \
            svuint16_t sve_ہدف_u16 = svget4((ma_ہدف_u16x4), 0);     \
            (خالی)sve_ماخذ_u16;                                         \
            (خالی)sve_ہدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ہدف_u16x4 = svset4(ma_ہدف_u16x4, 0, sve_ہدف_u16); \
        } جب (0);                                                      \
        کرو {                                                              \
            ثابت uint8_t sve_src_chn_idx = 1;                            \
            (خالی)sve_src_chn_idx;                                        \
            (خالی)sve_dst_chn_idx;                                        \
            svuint16_t sve_ماخذ_u16 = svget4((ma_ماخذ_u16x4), 1);     \
            svuint16_t sve_ہدف_u16 = svget4((ma_ہدف_u16x4), 1);     \
            (خالی)sve_ماخذ_u16;                                         \
            (خالی)sve_ہدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ہدف_u16x4 = svset4(ma_ہدف_u16x4, 1, sve_ہدف_u16); \
        } جب (0);                                                      \
        کرو {                                                              \
            ثابت uint8_t sve_src_chn_idx = 2;                            \
            (خالی)sve_src_chn_idx;                                        \
            (خالی)sve_dst_chn_idx;                                        \
            svuint16_t sve_ماخذ_u16 = svget4((ma_ماخذ_u16x4), 2);     \
            svuint16_t sve_ہدف_u16 = svget4((ma_ہدف_u16x4), 2);     \
            (خالی)sve_ماخذ_u16;                                         \
            (خالی)sve_ہدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ہدف_u16x4 = svset4(ma_ہدف_u16x4, 2, sve_ہدف_u16); \
        } جب (0);                                                      \
        کرو {                                                              \
            ثابت uint8_t sve_src_chn_idx = 3;                            \
            (خالی)sve_src_chn_idx;                                        \
            (خالی)sve_dst_chn_idx;                                        \
            svuint16_t sve_ماخذ_u16 = svget4((ma_ماخذ_u16x4), 3);     \
            svuint16_t sve_ہدف_u16 = svget4((ma_ہدف_u16x4), 3);     \
            (خالی)sve_ماخذ_u16;                                         \
            (خالی)sve_ہدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ہدف_u16x4 = svset4(ma_ہدف_u16x4, 3, sve_ہدف_u16); \
        } جب (0);                                                      \
    } جب (0)

#تعریف_کرو sdl_sve_pixel_u16x4_foreach_chn(ma_ماخذ_u16x4,                  \
                                        ma_ہدف_u16x4,                  \
                                        ...)                              \
    کرو {                                                                  \
        svuint16x4_t sve_ماخذ_u16x4 = ma_ماخذ_u16x4;                  \
        (خالی)sve_ماخذ_u16x4;                                           \
        کرو {                                                              \
            ثابت uint8_t sve_src_chn_idx = 0;                            \
            (خالی)sve_src_chn_idx;                                        \
            svuint16_t sve_ماخذ_u16 = svget4((ma_ماخذ_u16x4), 0);     \
            svuint16_t sve_ہدف_u16 = svget4((ma_ہدف_u16x4), 0);     \
            (خالی)sve_ماخذ_u16;                                         \
            (خالی)sve_ہدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ہدف_u16x4 = svset4(ma_ہدف_u16x4, 0, sve_ہدف_u16); \
        } جب (0);                                                      \
        کرو {                                                              \
            ثابت uint8_t sve_src_chn_idx = 1;                            \
            (خالی)sve_src_chn_idx;                                        \
            svuint16_t sve_ماخذ_u16 = svget4((ma_ماخذ_u16x4), 1);     \
            svuint16_t sve_ہدف_u16 = svget4((ma_ہدف_u16x4), 1);     \
            (خالی)sve_ماخذ_u16;                                         \
            (خالی)sve_ہدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ہدف_u16x4 = svset4(ma_ہدف_u16x4, 1, sve_ہدف_u16); \
        } جب (0);                                                      \
        کرو {                                                              \
            ثابت uint8_t sve_src_chn_idx = 2;                            \
            (خالی)sve_src_chn_idx;                                        \
            svuint16_t sve_ماخذ_u16 = svget4((ma_ماخذ_u16x4), 2);     \
            svuint16_t sve_ہدف_u16 = svget4((ma_ہدف_u16x4), 2);     \
            (خالی)sve_ماخذ_u16;                                         \
            (خالی)sve_ہدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ہدف_u16x4 = svset4(ma_ہدف_u16x4, 2, sve_ہدف_u16); \
        } جب (0);                                                      \
        کرو {                                                              \
            ثابت uint8_t sve_src_chn_idx = 3;                            \
            (خالی)sve_src_chn_idx;                                        \
            svuint16_t sve_ماخذ_u16 = svget4((ma_ماخذ_u16x4), 3);     \
            svuint16_t sve_ہدف_u16 = svget4((ma_ہدف_u16x4), 3);     \
            (خالی)sve_ماخذ_u16;                                         \
            (خالی)sve_ہدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ہدف_u16x4 = svset4(ma_ہدف_u16x4, 3, sve_ہدف_u16); \
        } جب (0);                                                      \
    } جب (0)

#تعریف_کرو sdl_sve_pixel_u16x4_foreach_chn_src_dst_rev(ma_ماخذ_u16x4,      \
                                                    ma_ہدف_u16x4,      \
                                                    ...)                  \
    کرو {                                                                  \
        svuint16x4_t sve_ماخذ_u16x4 = ma_ماخذ_u16x4;                  \
        (خالی)sve_ماخذ_u16x4;                                           \
        کرو {                                                              \
            ثابت uint8_t sve_src_chn_idx = 0;                            \
            ثابت uint8_t sve_dst_chn_idx = 3;                            \
            (خالی)sve_src_chn_idx;                                        \
            (خالی)sve_dst_chn_idx;                                        \
            svuint16_t sve_ماخذ_u16 = svget4((ma_ماخذ_u16x4), 0);     \
            svuint16_t sve_ہدف_u16 = svget4((ma_ہدف_u16x4), 3);     \
            (خالی)sve_ماخذ_u16;                                         \
            (خالی)sve_ہدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ہدف_u16x4 = svset4(ma_ہدف_u16x4, 3, sve_ہدف_u16); \
        } جب (0);                                                      \
        کرو {                                                              \
            ثابت uint8_t sve_src_chn_idx = 1;                            \
            ثابت uint8_t sve_dst_chn_idx = 2;                            \
            (خالی)sve_src_chn_idx;                                        \
            (خالی)sve_dst_chn_idx;                                        \
            svuint16_t sve_ماخذ_u16 = svget4((ma_ماخذ_u16x4), 1);     \
            svuint16_t sve_ہدف_u16 = svget4((ma_ہدف_u16x4), 2);     \
            (خالی)sve_ماخذ_u16;                                         \
            (خالی)sve_ہدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ہدف_u16x4 = svset4(ma_ہدف_u16x4, 2, sve_ہدف_u16); \
        } جب (0);                                                      \
        کرو {                                                              \
            ثابت uint8_t sve_src_chn_idx = 2;                            \
            ثابت uint8_t sve_dst_chn_idx = 1;                            \
            (خالی)sve_src_chn_idx;                                        \
            (خالی)sve_dst_chn_idx;                                        \
            svuint16_t sve_ماخذ_u16 = svget4((ma_ماخذ_u16x4), 2);     \
            svuint16_t sve_ہدف_u16 = svget4((ma_ہدف_u16x4), 1);     \
            (خالی)sve_ماخذ_u16;                                         \
            (خالی)sve_ہدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ہدف_u16x4 = svset4(ma_ہدف_u16x4, 1, sve_ہدف_u16); \
        } جب (0);                                                      \
        کرو {                                                              \
            ثابت uint8_t sve_src_chn_idx = 3;                            \
            ثابت uint8_t sve_dst_chn_idx = 0;                            \
            (خالی)sve_src_chn_idx;                                        \
            (خالی)sve_dst_chn_idx;                                        \
            svuint16_t sve_ماخذ_u16 = svget4((ma_ماخذ_u16x4), 3);     \
            svuint16_t sve_ہدف_u16 = svget4((ma_ہدف_u16x4), 0);     \
            (خالی)sve_ماخذ_u16;                                         \
            (خالی)sve_ہدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ہدف_u16x4 = svset4(ma_ہدف_u16x4, 0, sve_ہدف_u16); \
        } جب (0);                                                      \
    } جب (0)

#تعریف_کرو sdl_sve_pixel_u16x4_foreach_chn_accc_ccca(ma_ماخذ_u16x4,        \
                                                  ma_ہدف_u16x4,        \
                                                  ...)                    \
    کرو {                                                                  \
        svuint16x4_t sve_ماخذ_u16x4 = ma_ماخذ_u16x4;                  \
        (خالی)sve_ماخذ_u16x4;                                           \
        کرو {                                                              \
            ثابت uint8_t sve_src_chn_idx = 0;                            \
            ثابت uint8_t sve_dst_chn_idx = 1;                            \
            (خالی)sve_src_chn_idx;                                        \
            (خالی)sve_dst_chn_idx;                                        \
            svuint16_t sve_ماخذ_u16 = svget4((ma_ماخذ_u16x4), 0);     \
            svuint16_t sve_ہدف_u16 = svget4((ma_ہدف_u16x4), 1);     \
            (خالی)sve_ماخذ_u16;                                         \
            (خالی)sve_ہدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ہدف_u16x4 = svset4(ma_ہدف_u16x4, 1, sve_ہدف_u16); \
        } جب (0);                                                      \
        کرو {                                                              \
            ثابت uint8_t sve_src_chn_idx = 1;                            \
            ثابت uint8_t sve_dst_chn_idx = 2;                            \
            (خالی)sve_src_chn_idx;                                        \
            (خالی)sve_dst_chn_idx;                                        \
            svuint16_t sve_ماخذ_u16 = svget4((ma_ماخذ_u16x4), 1);     \
            svuint16_t sve_ہدف_u16 = svget4((ma_ہدف_u16x4), 2);     \
            (خالی)sve_ماخذ_u16;                                         \
            (خالی)sve_ہدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ہدف_u16x4 = svset4(ma_ہدف_u16x4, 2, sve_ہدف_u16); \
        } جب (0);                                                      \
        کرو {                                                              \
            ثابت uint8_t sve_src_chn_idx = 2;                            \
            ثابت uint8_t sve_dst_chn_idx = 3;                            \
            (خالی)sve_src_chn_idx;                                        \
            (خالی)sve_dst_chn_idx;                                        \
            svuint16_t sve_ماخذ_u16 = svget4((ma_ماخذ_u16x4), 2);     \
            svuint16_t sve_ہدف_u16 = svget4((ma_ہدف_u16x4), 3);     \
            (خالی)sve_ماخذ_u16;                                         \
            (خالی)sve_ہدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ہدف_u16x4 = svset4(ma_ہدف_u16x4, 3, sve_ہدف_u16); \
        } جب (0);                                                      \
        کرو {                                                              \
            ثابت uint8_t sve_src_chn_idx = 3;                            \
            ثابت uint8_t sve_dst_chn_idx = 0;                            \
            (خالی)sve_src_chn_idx;                                        \
            (خالی)sve_dst_chn_idx;                                        \
            svuint16_t sve_ماخذ_u16 = svget4((ma_ماخذ_u16x4), 3);     \
            svuint16_t sve_ہدف_u16 = svget4((ma_ہدف_u16x4), 0);     \
            (خالی)sve_ماخذ_u16;                                         \
            (خالی)sve_ہدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ہدف_u16x4 = svset4(ma_ہدف_u16x4, 0, sve_ہدف_u16); \
        } جب (0);                                                      \
    } جب (0)

#تعریف_کرو sdl_sve_pixel_u16x4_foreach_chn_ccca_accc(ma_ماخذ_u16x4,        \
                                                  ma_ہدف_u16x4,        \
                                                  ...)                    \
    کرو {                                                                  \
        svuint16x4_t sve_ماخذ_u16x4 = ma_ماخذ_u16x4;                  \
        (خالی)sve_ماخذ_u16x4;                                           \
        کرو {                                                              \
            ثابت uint8_t sve_src_chn_idx = 1;                            \
            ثابت uint8_t sve_dst_chn_idx = 0;                            \
            (خالی)sve_src_chn_idx;                                        \
            (خالی)sve_dst_chn_idx;                                        \
            svuint16_t sve_ماخذ_u16 = svget4((ma_ماخذ_u16x4), 1);     \
            svuint16_t sve_ہدف_u16 = svget4((ma_ہدف_u16x4), 0);     \
            (خالی)sve_ماخذ_u16;                                         \
            (خالی)sve_ہدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ہدف_u16x4 = svset4(ma_ہدف_u16x4, 0, sve_ہدف_u16); \
        } جب (0);                                                      \
        کرو {                                                              \
            ثابت uint8_t sve_src_chn_idx = 2;                            \
            ثابت uint8_t sve_dst_chn_idx = 1;                            \
            (خالی)sve_src_chn_idx;                                        \
            (خالی)sve_dst_chn_idx;                                        \
            svuint16_t sve_ماخذ_u16 = svget4((ma_ماخذ_u16x4), 2);     \
            svuint16_t sve_ہدف_u16 = svget4((ma_ہدف_u16x4), 1);     \
            (خالی)sve_ماخذ_u16;                                         \
            (خالی)sve_ہدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ہدف_u16x4 = svset4(ma_ہدف_u16x4, 1, sve_ہدف_u16); \
        } جب (0);                                                      \
        کرو {                                                              \
            ثابت uint8_t sve_src_chn_idx = 3;                            \
            ثابت uint8_t sve_dst_chn_idx = 2;                            \
            (خالی)sve_src_chn_idx;                                        \
            (خالی)sve_dst_chn_idx;                                        \
            svuint16_t sve_ماخذ_u16 = svget4((ma_ماخذ_u16x4), 3);     \
            svuint16_t sve_ہدف_u16 = svget4((ma_ہدف_u16x4), 2);     \
            (خالی)sve_ماخذ_u16;                                         \
            (خالی)sve_ہدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ہدف_u16x4 = svset4(ma_ہدف_u16x4, 2, sve_ہدف_u16); \
        } جب (0);                                                      \
        کرو {                                                              \
            ثابت uint8_t sve_src_chn_idx = 0;                            \
            ثابت uint8_t sve_dst_chn_idx = 3;                            \
            (خالی)sve_src_chn_idx;                                        \
            (خالی)sve_dst_chn_idx;                                        \
            svuint16_t sve_ماخذ_u16 = svget4((ma_ماخذ_u16x4), 0);     \
            svuint16_t sve_ہدف_u16 = svget4((ma_ہدف_u16x4), 3);     \
            (خالی)sve_ماخذ_u16;                                         \
            (خالی)sve_ہدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ہدف_u16x4 = svset4(ma_ہدف_u16x4, 3, sve_ہدف_u16); \
        } جب (0);                                                      \
    } جب (0)

#تعریف_کرو sdl_sve_pixel_u16x4_foreach_chn_a123_a321(ma_ماخذ_u16x4,        \
                                                  ma_ہدف_u16x4,        \
                                                  ...)                    \
    کرو {                                                                  \
        svuint16x4_t sve_ماخذ_u16x4 = ma_ماخذ_u16x4;                  \
        (خالی)sve_ماخذ_u16x4;                                           \
        کرو {                                                              \
            ثابت uint8_t sve_src_chn_idx = 0;                            \
            ثابت uint8_t sve_dst_chn_idx = 2;                            \
            (خالی)sve_src_chn_idx;                                        \
            (خالی)sve_dst_chn_idx;                                        \
            svuint16_t sve_ماخذ_u16 = svget4((ma_ماخذ_u16x4), 0);     \
            svuint16_t sve_ہدف_u16 = svget4((ma_ہدف_u16x4), 2);     \
            (خالی)sve_ماخذ_u16;                                         \
            (خالی)sve_ہدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ہدف_u16x4 = svset4(ma_ہدف_u16x4, 2, sve_ہدف_u16); \
        } جب (0);                                                      \
        کرو {                                                              \
            ثابت uint8_t sve_src_chn_idx = 1;                            \
            ثابت uint8_t sve_dst_chn_idx = 1;                            \
            (خالی)sve_src_chn_idx;                                        \
            (خالی)sve_dst_chn_idx;                                        \
            svuint16_t sve_ماخذ_u16 = svget4((ma_ماخذ_u16x4), 1);     \
            svuint16_t sve_ہدف_u16 = svget4((ma_ہدف_u16x4), 1);     \
            (خالی)sve_ماخذ_u16;                                         \
            (خالی)sve_ہدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ہدف_u16x4 = svset4(ma_ہدف_u16x4, 1, sve_ہدف_u16); \
        } جب (0);                                                      \
        کرو {                                                              \
            ثابت uint8_t sve_src_chn_idx = 2;                            \
            ثابت uint8_t sve_dst_chn_idx = 0;                            \
            (خالی)sve_src_chn_idx;                                        \
            (خالی)sve_dst_chn_idx;                                        \
            svuint16_t sve_ماخذ_u16 = svget4((ma_ماخذ_u16x4), 2);     \
            svuint16_t sve_ہدف_u16 = svget4((ma_ہدف_u16x4), 0);     \
            (خالی)sve_ماخذ_u16;                                         \
            (خالی)sve_ہدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ہدف_u16x4 = svset4(ma_ہدف_u16x4, 0, sve_ہدف_u16); \
        } جب (0);                                                      \
        کرو {                                                              \
            ثابت uint8_t sve_src_chn_idx = 3;                            \
            ثابت uint8_t sve_dst_chn_idx = 3;                            \
            (خالی)sve_src_chn_idx;                                        \
            (خالی)sve_dst_chn_idx;                                        \
            svuint16_t sve_ماخذ_u16 = svget4((ma_ماخذ_u16x4), 3);     \
            svuint16_t sve_ہدف_u16 = svget4((ma_ہدف_u16x4), 3);     \
            (خالی)sve_ماخذ_u16;                                         \
            (خالی)sve_ہدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ہدف_u16x4 = svset4(ma_ہدف_u16x4, 3, sve_ہدف_u16); \
        } جب (0);                                                      \
    } جب (0)

#تعریف_کرو sdl_sve_pixel_u16x4_foreach_chn_123a_321a(ma_ماخذ_u16x4,        \
                                                  ma_ہدف_u16x4,        \
                                                  ...)                    \
    کرو {                                                                  \
        svuint16x4_t sve_ماخذ_u16x4 = ma_ماخذ_u16x4;                  \
        (خالی)sve_ماخذ_u16x4;                                           \
        کرو {                                                              \
            ثابت uint8_t sve_src_chn_idx = 0;                            \
            ثابت uint8_t sve_dst_chn_idx = 0;                            \
            (خالی)sve_src_chn_idx;                                        \
            (خالی)sve_dst_chn_idx;                                        \
            svuint16_t sve_ماخذ_u16 = svget4((ma_ماخذ_u16x4), 0);     \
            svuint16_t sve_ہدف_u16 = svget4((ma_ہدف_u16x4), 0);     \
            (خالی)sve_ماخذ_u16;                                         \
            (خالی)sve_ہدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ہدف_u16x4 = svset4(ma_ہدف_u16x4, 0, sve_ہدف_u16); \
        } جب (0);                                                      \
        کرو {                                                              \
            ثابت uint8_t sve_src_chn_idx = 1;                            \
            ثابت uint8_t sve_dst_chn_idx = 3;                            \
            (خالی)sve_src_chn_idx;                                        \
            (خالی)sve_dst_chn_idx;                                        \
            svuint16_t sve_ماخذ_u16 = svget4((ma_ماخذ_u16x4), 1);     \
            svuint16_t sve_ہدف_u16 = svget4((ma_ہدف_u16x4), 3);     \
            (خالی)sve_ماخذ_u16;                                         \
            (خالی)sve_ہدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ہدف_u16x4 = svset4(ma_ہدف_u16x4, 3, sve_ہدف_u16); \
        } جب (0);                                                      \
        کرو {                                                              \
            ثابت uint8_t sve_src_chn_idx = 2;                            \
            ثابت uint8_t sve_dst_chn_idx = 2;                            \
            (خالی)sve_src_chn_idx;                                        \
            (خالی)sve_dst_chn_idx;                                        \
            svuint16_t sve_ماخذ_u16 = svget4((ma_ماخذ_u16x4), 2);     \
            svuint16_t sve_ہدف_u16 = svget4((ma_ہدف_u16x4), 2);     \
            (خالی)sve_ماخذ_u16;                                         \
            (خالی)sve_ہدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ہدف_u16x4 = svset4(ma_ہدف_u16x4, 2, sve_ہدف_u16); \
        } جب (0);                                                      \
        کرو {                                                              \
            ثابت uint8_t sve_src_chn_idx = 3;                            \
            ثابت uint8_t sve_dst_chn_idx = 1;                            \
            (خالی)sve_src_chn_idx;                                        \
            (خالی)sve_dst_chn_idx;                                        \
            svuint16_t sve_ماخذ_u16 = svget4((ma_ماخذ_u16x4), 3);     \
            svuint16_t sve_ہدف_u16 = svget4((ma_ہدف_u16x4), 1);     \
            (خالی)sve_ماخذ_u16;                                         \
            (خالی)sve_ہدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ہدف_u16x4 = svset4(ma_ہدف_u16x4, 1, sve_ہدف_u16); \
        } جب (0);                                                      \
    } جب (0)

#تعریف_کرو sdl_sve_pixel_u16x4_foreach_chn_argb_rgb565(ma_ماخذ_u16x4,      \
                                                    ma_ہدف_u16x3,      \
                                                    ...)                  \
    کرو {                                                                  \
        svuint16x4_t sve_ماخذ_u16x4 = ma_ماخذ_u16x4;                  \
        (خالی)sve_ماخذ_u16x4;                                           \
        کرو {                                                              \
            ثابت uint8_t sve_src_chn_idx = 0;                            \
            ثابت uint8_t sve_dst_chn_idx = 0;                            \
            (خالی)sve_src_chn_idx;                                        \
            (خالی)sve_dst_chn_idx;                                        \
            svuint16_t sve_ماخذ_u16 = svget4((ma_ماخذ_u16x4), 0);     \
            svuint16_t sve_ہدف_u16 = svget3((ma_ہدف_u16x3), 0);     \
            (خالی)sve_ماخذ_u16;                                         \
            (خالی)sve_ہدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ہدف_u16x3 = svset3(ma_ہدف_u16x3, 0, sve_ہدف_u16); \
        } جب (0);                                                      \
        کرو {                                                              \
            ثابت uint8_t sve_src_chn_idx = 1;                            \
            ثابت uint8_t sve_dst_chn_idx = 1;                            \
            (خالی)sve_src_chn_idx;                                        \
            (خالی)sve_dst_chn_idx;                                        \
            svuint16_t sve_ماخذ_u16 = svget4((ma_ماخذ_u16x4), 1);     \
            svuint16_t sve_ہدف_u16 = svget3((ma_ہدف_u16x3), 1);     \
            (خالی)sve_ماخذ_u16;                                         \
            (خالی)sve_ہدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ہدف_u16x3 = svset3(ma_ہدف_u16x3, 1, sve_ہدف_u16); \
        } جب (0);                                                      \
        کرو {                                                              \
            ثابت uint8_t sve_src_chn_idx = 2;                            \
            ثابت uint8_t sve_dst_chn_idx = 2;                            \
            (خالی)sve_src_chn_idx;                                        \
            (خالی)sve_dst_chn_idx;                                        \
            svuint16_t sve_ماخذ_u16 = svget4((ma_ماخذ_u16x4), 2);     \
            svuint16_t sve_ہدف_u16 = svget3((ma_ہدف_u16x3), 2);     \
            (خالی)sve_ماخذ_u16;                                         \
            (خالی)sve_ہدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ہدف_u16x3 = svset3(ma_ہدف_u16x3, 2, sve_ہدف_u16); \
        } جب (0);                                                      \
    } جب (0)

#تعریف_کرو sdl_sve_pixel_u16x4_foreach_chn_rgba_rgb565(ma_ماخذ_u16x4,      \
                                                    ma_ہدف_u16x3,      \
                                                    ...)                  \
    کرو {                                                                  \
        svuint16x4_t sve_ماخذ_u16x4 = ma_ماخذ_u16x4;                  \
        (خالی)sve_ماخذ_u16x4;                                           \
        کرو {                                                              \
            ثابت uint8_t sve_src_chn_idx = 1;                            \
            ثابت uint8_t sve_dst_chn_idx = 0;                            \
            (خالی)sve_src_chn_idx;                                        \
            (خالی)sve_dst_chn_idx;                                        \
            svuint16_t sve_ماخذ_u16 = svget4((ma_ماخذ_u16x4), 1);     \
            svuint16_t sve_ہدف_u16 = svget3((ma_ہدف_u16x3), 0);     \
            (خالی)sve_ماخذ_u16;                                         \
            (خالی)sve_ہدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ہدف_u16x3 = svset3(ma_ہدف_u16x3, 0, sve_ہدف_u16); \
        } جب (0);                                                      \
        کرو {                                                              \
            ثابت uint8_t sve_src_chn_idx = 2;                            \
            ثابت uint8_t sve_dst_chn_idx = 1;                            \
            (خالی)sve_src_chn_idx;                                        \
            (خالی)sve_dst_chn_idx;                                        \
            svuint16_t sve_ماخذ_u16 = svget4((ma_ماخذ_u16x4), 2);     \
            svuint16_t sve_ہدف_u16 = svget3((ma_ہدف_u16x3), 1);     \
            (خالی)sve_ماخذ_u16;                                         \
            (خالی)sve_ہدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ہدف_u16x3 = svset3(ma_ہدف_u16x3, 1, sve_ہدف_u16); \
        } جب (0);                                                      \
        کرو {                                                              \
            ثابت uint8_t sve_src_chn_idx = 3;                            \
            ثابت uint8_t sve_dst_chn_idx = 2;                            \
            (خالی)sve_src_chn_idx;                                        \
            (خالی)sve_dst_chn_idx;                                        \
            svuint16_t sve_ماخذ_u16 = svget4((ma_ماخذ_u16x4), 3);     \
            svuint16_t sve_ہدف_u16 = svget3((ma_ہدف_u16x3), 2);     \
            (خالی)sve_ماخذ_u16;                                         \
            (خالی)sve_ہدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ہدف_u16x3 = svset3(ma_ہدف_u16x3, 2, sve_ہدف_u16); \
        } جب (0);                                                      \
    } جب (0)

#تعریف_کرو sdl_sve_pixel_u16x4_foreach_chn_bgra_rgb565(ma_ماخذ_u16x4,      \
                                                    ma_ہدف_u16x3,      \
                                                    ...)                  \
    کرو {                                                                  \
        svuint16x4_t sve_ماخذ_u16x4 = ma_ماخذ_u16x4;                  \
        (خالی)sve_ماخذ_u16x4;                                           \
        کرو {                                                              \
            ثابت uint8_t sve_src_chn_idx = 3;                            \
            ثابت uint8_t sve_dst_chn_idx = 0;                            \
            (خالی)sve_src_chn_idx;                                        \
            (خالی)sve_dst_chn_idx;                                        \
            svuint16_t sve_ماخذ_u16 = svget4((ma_ماخذ_u16x4), 3);     \
            svuint16_t sve_ہدف_u16 = svget3((ma_ہدف_u16x3), 0);     \
            (خالی)sve_ماخذ_u16;                                         \
            (خالی)sve_ہدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ہدف_u16x3 = svset3(ma_ہدف_u16x3, 0, sve_ہدف_u16); \
        } جب (0);                                                      \
        کرو {                                                              \
            ثابت uint8_t sve_src_chn_idx = 2;                            \
            ثابت uint8_t sve_dst_chn_idx = 1;                            \
            (خالی)sve_src_chn_idx;                                        \
            (خالی)sve_dst_chn_idx;                                        \
            svuint16_t sve_ماخذ_u16 = svget4((ma_ماخذ_u16x4), 2);     \
            svuint16_t sve_ہدف_u16 = svget3((ma_ہدف_u16x3), 1);     \
            (خالی)sve_ماخذ_u16;                                         \
            (خالی)sve_ہدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ہدف_u16x3 = svset3(ma_ہدف_u16x3, 1, sve_ہدف_u16); \
        } جب (0);                                                      \
        کرو {                                                              \
            ثابت uint8_t sve_src_chn_idx = 1;                            \
            ثابت uint8_t sve_dst_chn_idx = 2;                            \
            (خالی)sve_src_chn_idx;                                        \
            (خالی)sve_dst_chn_idx;                                        \
            svuint16_t sve_ماخذ_u16 = svget4((ma_ماخذ_u16x4), 1);     \
            svuint16_t sve_ہدف_u16 = svget3((ma_ہدف_u16x3), 2);     \
            (خالی)sve_ماخذ_u16;                                         \
            (خالی)sve_ہدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ہدف_u16x3 = svset3(ma_ہدف_u16x3, 2, sve_ہدف_u16); \
        } جب (0);                                                      \
    } جب (0)

#تعریف_کرو sdl_sve_pixel_u16x4_foreach_chn_abgr_rgb565(ma_ماخذ_u16x4,      \
                                                    ma_ہدف_u16x3,      \
                                                    ...)                  \
    کرو {                                                                  \
        svuint16x4_t sve_ماخذ_u16x4 = ma_ماخذ_u16x4;                  \
        (خالی)sve_ماخذ_u16x4;                                           \
        کرو {                                                              \
            ثابت uint8_t sve_src_chn_idx = 2;                            \
            ثابت uint8_t sve_dst_chn_idx = 0;                            \
            (خالی)sve_src_chn_idx;                                        \
            (خالی)sve_dst_chn_idx;                                        \
            svuint16_t sve_ماخذ_u16 = svget4((ma_ماخذ_u16x4), 2);     \
            svuint16_t sve_ہدف_u16 = svget3((ma_ہدف_u16x3), 0);     \
            (خالی)sve_ماخذ_u16;                                         \
            (خالی)sve_ہدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ہدف_u16x3 = svset3(ma_ہدف_u16x3, 0, sve_ہدف_u16); \
        } جب (0);                                                      \
        کرو {                                                              \
            ثابت uint8_t sve_src_chn_idx = 1;                            \
            ثابت uint8_t sve_dst_chn_idx = 1;                            \
            (خالی)sve_src_chn_idx;                                        \
            (خالی)sve_dst_chn_idx;                                        \
            svuint16_t sve_ماخذ_u16 = svget4((ma_ماخذ_u16x4), 1);     \
            svuint16_t sve_ہدف_u16 = svget3((ma_ہدف_u16x3), 1);     \
            (خالی)sve_ماخذ_u16;                                         \
            (خالی)sve_ہدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ہدف_u16x3 = svset3(ma_ہدف_u16x3, 1, sve_ہدف_u16); \
        } جب (0);                                                      \
        کرو {                                                              \
            ثابت uint8_t sve_src_chn_idx = 0;                            \
            ثابت uint8_t sve_dst_chn_idx = 2;                            \
            (خالی)sve_src_chn_idx;                                        \
            (خالی)sve_dst_chn_idx;                                        \
            svuint16_t sve_ماخذ_u16 = svget4((ma_ماخذ_u16x4), 0);     \
            svuint16_t sve_ہدف_u16 = svget3((ma_ہدف_u16x3), 2);     \
            (خالی)sve_ماخذ_u16;                                         \
            (خالی)sve_ہدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ہدف_u16x3 = svset3(ma_ہدف_u16x3, 2, sve_ہدف_u16); \
        } جب (0);                                                      \
    } جب (0)

SDL_TARGETING("arch=armv8-a+sve2")
ساکن اندرونی svuint16x3_t sdl_sve_rgb565_unpack(svuint16_t vPixels)
{
    svuint16_t vBlue = svand_n_u16_m(svptrue_b16(), vPixels, 0x1F);
    svuint16_t vGreen = svand_n_u16_m(svptrue_b16(), vPixels, (0x3F << 5));
    svuint16_t vRed = svand_n_u16_m(svptrue_b16(), vPixels, (0x1F << 11));

    واپس svcreate3_u16(svlsl_n_u16_m(svptrue_b16(), vBlue, 3),
                         svlsr_n_u16_m(svptrue_b16(), vGreen, 3),
                         svlsr_n_u16_m(svptrue_b16(), vRed, 8));
}

SDL_TARGETING("arch=armv8-a+sve2")
ساکن اندرونی svuint16_t sdl_sve_rgb565_pack(svuint16x3_t vRGB16x3)
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
    واپس svorr_u16_m(svptrue_b16(), vPixel, vBlue);

    // return  (svget3_u16(vRGB16x3, 0) >> 3)
    //     |   ((svget3_u16(vRGB16x3, 1) & (0x3F << 2)) << 3)
    //     |   ((svget3_u16(vRGB16x3, 2) & (0x1F << 3)) << 8);
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(2, 3, 4)
ساکن اندرونی خالی svld3rgb565_u16(svbool_t vPredu8,
                                   uint16_t *phw_ماخذ,
                                   svuint16x3_t *pv_کم,
                                   svuint16x3_t *pv_بلند)
{
    svuint8x2_t vInput8x2 = svld2_u8(vPredu8, (uint8_t *)phw_ماخذ);

    svuint16_t v_کم_Byte_کم_Half = svunpklo_u16(svget2_u8(vInput8x2, 0));
    svuint16_t v_کم_Byte_بلند_Half = svunpkhi_u16(svget2_u8(vInput8x2, 0));

    svuint16_t v_بلند_Byte_کم_Half = svunpklo_u16(svget2_u8(vInput8x2, 1));
    svuint16_t v_بلند_Byte_بلند_Half = svunpkhi_u16(svget2_u8(vInput8x2, 1));

    //*pvLow = sdl_sve_rgb565_unpack  (   vLowByteLowHalf
    //                                |   (vHighByteLowHalf << 8));
    *pv_کم = sdl_sve_rgb565_unpack(
        svorr_u16_m(svptrue_b16(),
                    v_کم_Byte_کم_Half,
                    //(vHighByteLowHalf << 8)
                    svlsl_n_u16_m(svptrue_b16(), v_بلند_Byte_کم_Half, 8)));

    //*pvHigh = sdl_sve_rgb565_unpack (   vLowByteHighHalf
    //                                |   (vHighByteHighHalf << 8));
    *pv_بلند = sdl_sve_rgb565_unpack(
        svorr_u16_m(svptrue_b16(),
                    v_کم_Byte_بلند_Half,
                    //(vHighByteHighHalf << 8)
                    svlsl_n_u16_m(svptrue_b16(), v_بلند_Byte_بلند_Half, 8)));
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(2)
ساکن اندرونی خالی svst3rgb565_u16(svbool_t vPredu8,
                                   uint16_t *phw_ہدف,
                                   svuint16x3_t v_کم,
                                   svuint16x3_t v_بلند)
{
    svuint16_t v_کم_Byte_کم_Half = svundef_u16();
    svuint16_t v_بلند_Byte_کم_Half = svundef_u16();

    /* pack low half pixels */
    کرو {
        svuint16_t vPixel = sdl_sve_rgb565_pack(v_کم);

        // vLowByteLowHalf = vPixel & 0xFF;
        v_کم_Byte_کم_Half = svand_n_u16_m(svptrue_b16(), vPixel, 0xFF);

        // vHighByteLowHalf = vPixel >> 8;
        v_بلند_Byte_کم_Half = svlsr_n_u16_m(svptrue_b16(), vPixel, 8);
    } جب (0);

    svuint16_t v_کم_Byte_بلند_Half = svundef_u16();
    svuint16_t v_بلند_Byte_بلند_Half = svundef_u16();

    /* pack high half pixels */
    کرو {
        svuint16_t vPixel = sdl_sve_rgb565_pack(v_بلند);

        // vLowByteHighHalf = vPixel & 0xFF;
        v_کم_Byte_بلند_Half = svand_n_u16_m(svptrue_b16(), vPixel, 0xFF);

        // vHighByteHighHalf = vPixel >> 8;
        v_بلند_Byte_بلند_Half = svlsr_n_u16_m(svptrue_b16(), vPixel, 8);
    } جب (0);

    /* save rgb565 pixels */
    svuint8_t v_کم_Byte = svuzp1_u8(svreinterpret_u8(v_کم_Byte_کم_Half),
                                   svreinterpret_u8(v_کم_Byte_بلند_Half));

    svuint8_t v_بلند_Byte = svuzp1_u8(svreinterpret_u8(v_بلند_Byte_کم_Half),
                                    svreinterpret_u8(v_بلند_Byte_بلند_Half));

    svst2_u8(vPredu8, (uint8_t *)phw_ہدف, svcreate2_u8(v_کم_Byte, v_بلند_Byte));
}

#اگر defined(__GNUC__) && !defined(__clang__)
#تعریف_کرو svld4ub_u16(ma_pred,                                                                                         \
                    ma_src_ptr,                                                                                      \
                    ma_svuint16x4_کم_ptr,                                                                           \
                    ma_svuint16x4_بلند_ptr)                                                                          \
    کرو {                                                                                                             \
        svuint8x4_t vInput8x4 = svld4_u8((ma_pred), (ma_src_ptr));                                                   \
                                                                                                                     \
        *(ma_svuint16x4_کم_ptr) = svset4_u16(*(ma_svuint16x4_کم_ptr), 0, svunpklo_u16(svget4_u8(vInput8x4, 0)));   \
        *(ma_svuint16x4_کم_ptr) = svset4_u16(*(ma_svuint16x4_کم_ptr), 1, svunpklo_u16(svget4_u8(vInput8x4, 1)));   \
        *(ma_svuint16x4_کم_ptr) = svset4_u16(*(ma_svuint16x4_کم_ptr), 2, svunpklo_u16(svget4_u8(vInput8x4, 2)));   \
        *(ma_svuint16x4_کم_ptr) = svset4_u16(*(ma_svuint16x4_کم_ptr), 3, svunpklo_u16(svget4_u8(vInput8x4, 3)));   \
                                                                                                                     \
        *(ma_svuint16x4_بلند_ptr) = svset4_u16(*(ma_svuint16x4_بلند_ptr), 0, svunpkhi_u16(svget4_u8(vInput8x4, 0))); \
        *(ma_svuint16x4_بلند_ptr) = svset4_u16(*(ma_svuint16x4_بلند_ptr), 1, svunpkhi_u16(svget4_u8(vInput8x4, 1))); \
        *(ma_svuint16x4_بلند_ptr) = svset4_u16(*(ma_svuint16x4_بلند_ptr), 2, svunpkhi_u16(svget4_u8(vInput8x4, 2))); \
        *(ma_svuint16x4_بلند_ptr) = svset4_u16(*(ma_svuint16x4_بلند_ptr), 3, svunpkhi_u16(svget4_u8(vInput8x4, 3))); \
    } جب (0)

#تعریف_کرو svst4ub_u16(ma_pred,                                                                 \
                    ma_dst_ptr,                                                              \
                    ma_svuint16x4_کم,                                                       \
                    ma_svuint16x4_بلند)                                                      \
    کرو {                                                                                     \
        svuint8_t vCH0u8 = svuzp1_u8(svreinterpret_u8(svget4_u16((ma_svuint16x4_کم), 0)),   \
                                     svreinterpret_u8(svget4_u16((ma_svuint16x4_بلند), 0))); \
                                                                                             \
        svuint8_t vCH1u8 = svuzp1_u8(svreinterpret_u8(svget4_u16((ma_svuint16x4_کم), 1)),   \
                                     svreinterpret_u8(svget4_u16((ma_svuint16x4_بلند), 1))); \
                                                                                             \
        svuint8_t vCH2u8 = svuzp1_u8(svreinterpret_u8(svget4_u16((ma_svuint16x4_کم), 2)),   \
                                     svreinterpret_u8(svget4_u16((ma_svuint16x4_بلند), 2))); \
                                                                                             \
        svuint8_t vCH3u8 = svuzp1_u8(svreinterpret_u8(svget4_u16((ma_svuint16x4_کم), 3)),   \
                                     svreinterpret_u8(svget4_u16((ma_svuint16x4_بلند), 3))); \
                                                                                             \
        svst4_u8((ma_pred), (ma_dst_ptr), svcreate4_u8(vCH0u8, vCH1u8, vCH2u8, vCH3u8));     \
    } جب (0)
#ورنہ
SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(2, 3, 4)
ساکن اندرونی خالی svld4ub_u16(svbool_t vPredu8,
                               uint8_t *pch_ماخذ,
                               svuint16x4_t *pv_کم,
                               svuint16x4_t *pv_بلند)
{
    svuint8x4_t vInput8x4 = svld4_u8(vPredu8, pch_ماخذ);

    *pv_کم = svset4_u16(*pv_کم, 0, svunpklo_u16(svget4_u8(vInput8x4, 0)));
    *pv_کم = svset4_u16(*pv_کم, 1, svunpklo_u16(svget4_u8(vInput8x4, 1)));
    *pv_کم = svset4_u16(*pv_کم, 2, svunpklo_u16(svget4_u8(vInput8x4, 2)));
    *pv_کم = svset4_u16(*pv_کم, 3, svunpklo_u16(svget4_u8(vInput8x4, 3)));

    *pv_بلند = svset4_u16(*pv_بلند, 0, svunpkhi_u16(svget4_u8(vInput8x4, 0)));
    *pv_بلند = svset4_u16(*pv_بلند, 1, svunpkhi_u16(svget4_u8(vInput8x4, 1)));
    *pv_بلند = svset4_u16(*pv_بلند, 2, svunpkhi_u16(svget4_u8(vInput8x4, 2)));
    *pv_بلند = svset4_u16(*pv_بلند, 3, svunpkhi_u16(svget4_u8(vInput8x4, 3)));
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(2)
ساکن اندرونی خالی svst4ub_u16(svbool_t vPredu8,
                               uint8_t *pch_ہدف,
                               svuint16x4_t v_کم,
                               svuint16x4_t v_بلند)
{

    svuint8_t vCH0u8 = svuzp1_u8(svreinterpret_u8(svget4_u16(v_کم, 0)),
                                 svreinterpret_u8(svget4_u16(v_بلند, 0)));

    svuint8_t vCH1u8 = svuzp1_u8(svreinterpret_u8(svget4_u16(v_کم, 1)),
                                 svreinterpret_u8(svget4_u16(v_بلند, 1)));

    svuint8_t vCH2u8 = svuzp1_u8(svreinterpret_u8(svget4_u16(v_کم, 2)),
                                 svreinterpret_u8(svget4_u16(v_بلند, 2)));

    svuint8_t vCH3u8 = svuzp1_u8(svreinterpret_u8(svget4_u16(v_کم, 3)),
                                 svreinterpret_u8(svget4_u16(v_بلند, 3)));

    svst4_u8(vPredu8, pch_ہدف, svcreate4_u8(vCH0u8, vCH1u8, vCH2u8, vCH3u8));
}
#اگر_ختم

/*! \note the Element range of vMask is [0, 0xFF]
 */
SDL_TARGETING("arch=armv8-a+sve2")
ساکن اندرونی svuint16_t sdl_sve_chn_blend_with_نقاب(svuint16_t v_ماخذ,
                                                     svuint16_t v_ہدف,
                                                     svuint16_t v_نقاب)
{
    // vTarget = vSource * vMask + vTarget * (255 - vMask);
    svuint16_t vTemp0 = svdup_u16(1);
    vTemp0 = svmla_u16_m(svptrue_b16(), vTemp0, v_ماخذ, v_نقاب);
    vTemp0 = svmla_u16_m(svptrue_b16(),
                         vTemp0,
                         v_ہدف,
                         svsub_u16_m(svptrue_b16(),
                                     svdup_u16(255),
                                     v_نقاب));

    /* x += x >> 8 */
    واپس svreinterpret_u16_u8(
        svaddhnb_u16(vTemp0,
                     svlsr_n_u16_m(svptrue_b16(),
                                   vTemp0,
                                   8)));
}
/*! \note the Element range of vMask is [0, 0xFF]
 */
SDL_TARGETING("arch=armv8-a+sve2")
ساکن اندرونی svuint16_t sdl_sve_chn_blend_with_نقاب_fast(svuint16_t v_ماخذ,
                                                          svuint16_t v_ہدف,
                                                          svuint16_t v_نقاب)
{
    // vTarget = vSource * vMask + vTarget * (255 - vMask);
    svuint16_t vTemp0 = svmul_u16_m(svptrue_b16(), v_ماخذ, v_نقاب);
    vTemp0 = svmla_u16_m(svptrue_b16(),
                         vTemp0,
                         v_ہدف,
                         svsub_u16_m(svptrue_b16(),
                                     svdup_u16(255),
                                     v_نقاب));

    واپس svlsr_n_u16_m(svptrue_b16(), vTemp0, 8); // vTarget >> 8;
}

/*! \note the hwOpacity range [0, 0x100]
 */
SDL_TARGETING("arch=armv8-a+sve2")
ساکن اندرونی svuint16_t sdl_sve_chn_blend_with_opacity(svuint16_t v_ماخذ,
                                                        svuint16_t v_ہدف,
                                                        uint16_t hwOpacity)
{
    // svuint16_t vOpacity = svdup_u16(hwOpacity);
    // vTarget = vSource * vOpacity + vTarget * (256 - vOpacity);

    svuint16_t vTemp0 = svmul_n_u16_m(svptrue_b16(), v_ماخذ, hwOpacity);
    svuint16_t vTemp1 = svmul_n_u16_m(svptrue_b16(),
                                      v_ہدف,
                                      256 - hwOpacity);
    v_ہدف = svadd_u16_m(svptrue_b16(), vTemp0, vTemp1);

    واپس svlsr_n_u16_m(svptrue_b16(), v_ہدف, 8); // vTarget >> 8;
}

/*! \note the hwOpacity range [0, 0x100]
 */
SDL_TARGETING("arch=armv8-a+sve2")
ساکن اندرونی svuint16_t sdl_sve_chn_blend_with_opacity_fast(svuint16_t v_ماخذ,
                                                             svuint16_t v_ہدف,
                                                             uint16_t hwOpacity)
{
    // vTarget = vSource * vMask + vTarget * (255 - vMask);
    svuint16_t vTemp0 = svmul_n_u16_m(svptrue_b16(), v_ماخذ, hwOpacity);
    vTemp0 = svmla_n_u16_m(svptrue_b16(),
                           vTemp0,
                           v_ہدف,
                           256 - hwOpacity);

    واپس svlsr_n_u16_m(svptrue_b16(), vTemp0, 8); // vTarget >> 8;
}

/*! \note the Element range of vMask is [0, 0xFF]
 *  \note the hwOpacity range [0, 0x100]
 */
SDL_TARGETING("arch=armv8-a+sve2")
ساکن اندرونی svuint16_t sdl_sve_chn_blend_with_نقاب_and_opacity(svuint16_t v_ماخذ,
                                                                 svuint16_t v_ہدف,
                                                                 svuint16_t v_نقاب,
                                                                 uint16_t hwOpacity)
{
    v_نقاب = svsel(svcmpeq_n_u16(svptrue_b16(), v_نقاب, 255),
                  svdup_u16(hwOpacity),
                  //(vMask * hwOpacity) >> 8,
                  svlsr_n_u16_m(svptrue_b16(),
                                svmul_n_u16_m(svptrue_b16(), v_نقاب, hwOpacity),
                                8));

    // vTarget = vSource * vMask + vTarget * (256 - vMask);
    svuint16_t vTemp0 = svmul_u16_m(svptrue_b16(), v_ماخذ, v_نقاب);
    svuint16_t vTemp1 = svmul_u16_m(svptrue_b16(),
                                    v_ہدف,
                                    svsub_u16_m(svptrue_b16(),
                                                svdup_u16(256),
                                                v_نقاب));
    v_ہدف = svadd_u16_m(svptrue_b16(), vTemp0, vTemp1);

    واپس svlsr_n_u16_m(svptrue_b16(), v_ہدف, 8); // vTarget >> 8;
}

/*! \note the Element range of vMask0/1 is [0, 0xFF]
 */
SDL_TARGETING("arch=armv8-a+sve2")
ساکن اندرونی svuint16_t sdl_sve_chn_blend_with_masks(svuint16_t v_ماخذ,
                                                      svuint16_t v_ہدف,
                                                      svuint16_t vMask0,
                                                      svuint16_t vMask1)
{
    vMask1 = svadd_u16_m(svcmpeq_n_u16(svptrue_b16(), vMask1, 255),
                         vMask1,
                         svdup_u16(1));

    svuint16_t v_نقاب =
        svsel(svcmpge_n_u16(svptrue_b16(), vMask0, 255),
              vMask1,
              //(vMask0 * vMask1) >> 8,
              svlsr_n_u16_m(svptrue_b16(),
                            svmul_u16_m(svptrue_b16(), vMask0, vMask1),
                            8));

    // vTarget = vSource * vMask + vTarget * (256 - vMask);
    svuint16_t vTemp0 = svmul_u16_m(svptrue_b16(), v_ماخذ, v_نقاب);
    svuint16_t vTemp1 = svmul_u16_m(svptrue_b16(),
                                    v_ہدف,
                                    svsub_u16_m(svptrue_b16(),
                                                svdup_u16(256),
                                                v_نقاب));
    v_ہدف = svadd_u16_m(svptrue_b16(), vTemp0, vTemp1);

    واپس svlsr_n_u16_m(svptrue_b16(), v_ہدف, 8); // vTarget >> 8;
}

/*! \note the Element range of vMask0/1 is [0, 0xFF]
 *  \note the hwOpacity range [0, 0x100]
 */
SDL_TARGETING("arch=armv8-a+sve2")
ساکن اندرونی svuint16_t sdl_sve_chn_blend_with_masks_and_opacity(
    svuint16_t v_ماخذ,
    svuint16_t v_ہدف,
    svuint16_t vMask0,
    svuint16_t vMask1,
    uint16_t hwOpacity)
{
    vMask0 = svadd_u16_m(svcmpeq_n_u16(svptrue_b16(), vMask0, 255),
                         vMask0,
                         svdup_u16(1));

    svuint16_t v_نقاب =
        svsel(svcmpge_n_u16(svptrue_b16(), vMask1, 255), /* >= 255 */
              vMask0,
              //(vMask0 * vMask1) >> 8
              svlsr_n_u16_m(svptrue_b16(),
                            svmul_u16_m(svptrue_b16(), vMask0, vMask1),
                            8));

    v_نقاب =
        svsel(svcmpge_n_u16(svptrue_b16(), v_نقاب, 255),
              svdup_u16(hwOpacity),
              //(vMask * hwOpacity) >> 8,
              svlsr_n_u16_m(svptrue_b16(),
                            svmul_n_u16_m(svptrue_b16(), v_نقاب, hwOpacity),
                            8));

    // vTarget = vSource * vMask + vTarget * (256 - vMask);
    svuint16_t vTemp0 = svmul_u16_m(svptrue_b16(), v_ماخذ, v_نقاب);
    svuint16_t vTemp1 = svmul_u16_m(svptrue_b16(),
                                    v_ہدف,
                                    svsub_u16_m(svptrue_b16(),
                                                svdup_u16(256),
                                                v_نقاب));
    v_ہدف = svadd_u16_m(svptrue_b16(), vTemp0, vTemp1);

    واپس svlsr_n_u16_m(svptrue_b16(), v_ہدف, 8); // vTarget >> 8;
}

/*! \note the Element range of vMask0/1 is [0, 0xFF]
 */
SDL_TARGETING("arch=armv8-a+sve2")
ساکن اندرونی svuint16_t sdl_sve_chn_blend_with_3masks(svuint16_t v_ماخذ,
                                                       svuint16_t v_ہدف,
                                                       svuint16_t vMask0,
                                                       svuint16_t vMask1,
                                                       svuint16_t vMask2)
{
    vMask0 = svadd_u16_m(svcmpeq_n_u16(svptrue_b16(), vMask0, 255),
                         vMask0,
                         svdup_u16(1));

    svuint16_t v_نقاب =
        svsel(svcmpge_n_u16(svptrue_b16(), vMask1, 255),
              vMask0,
              //(vMask0 * vMask1) >> 8
              svlsr_n_u16_m(svptrue_b16(),
                            svmul_u16_m(svptrue_b16(), vMask0, vMask1),
                            8));

    v_نقاب =
        svsel(svcmpge_n_u16(svptrue_b16(), vMask2, 255),
              v_نقاب,
              //(vMask * vMask2) >> 8
              svlsr_n_u16_m(svptrue_b16(),
                            svmul_u16_m(svptrue_b16(), v_نقاب, vMask2),
                            8));

    // vTarget = vSource * vMask + vTarget * (256 - vMask);
    svuint16_t vTemp0 = svmul_u16_m(svptrue_b16(), v_ماخذ, v_نقاب);
    svuint16_t vTemp1 = svmul_u16_m(svptrue_b16(),
                                    v_ہدف,
                                    svsub_u16_m(svptrue_b16(),
                                                svdup_u16(256),
                                                v_نقاب));
    v_ہدف = svadd_u16_m(svptrue_b16(), vTemp0, vTemp1);

    واپس svlsr_n_u16_m(svptrue_b16(), v_ہدف, 8); // vTarget >> 8;
}

/*! \note the Element range of vMask0/1 is [0, 0xFF]
 *  \note the hwOpacity range [0, 0x100]
 */
SDL_TARGETING("arch=armv8-a+sve2")
ساکن اندرونی svuint16_t sdl_sve_chn_blend_with_3masks_and_opacity(
    svuint16_t v_ماخذ,
    svuint16_t v_ہدف,
    svuint16_t vMask0,
    svuint16_t vMask1,
    svuint16_t vMask2,
    uint16_t hwOpacity)
{
    vMask0 = svadd_u16_m(svcmpeq_n_u16(svptrue_b16(), vMask0, 255),
                         vMask0,
                         svdup_u16(1));

    svuint16_t v_نقاب =
        svsel(svcmpge_n_u16(svptrue_b16(), vMask1, 255),
              vMask0,
              //(vMask0 * vMask1) >> 8
              svlsr_n_u16_m(svptrue_b16(),
                            svmul_u16_m(svptrue_b16(), vMask0, vMask1),
                            8));

    v_نقاب =
        svsel(svcmpge_n_u16(svptrue_b16(), vMask2, 255),
              v_نقاب,
              svlsr_n_u16_m(svptrue_b16(),
                            svmul_u16_m(svptrue_b16(), v_نقاب, vMask2),
                            8));
    //(vMask * vMask2) >> 8);

    v_نقاب =
        svsel(svcmpge_n_u16(svptrue_b16(), v_نقاب, 255),
              svdup_u16(hwOpacity),
              //(vMask * hwOpacity) >> 8
              svlsr_n_u16_m(svptrue_b16(),
                            svmul_n_u16_m(svptrue_b16(), v_نقاب, hwOpacity),
                            8));

    // vTarget = vSource * vMask + vTarget * (256 - vMask);
    svuint16_t vTemp0 = svmul_u16_m(svptrue_b16(), v_ماخذ, v_نقاب);
    svuint16_t vTemp1 = svmul_u16_m(svptrue_b16(),
                                    v_ہدف,
                                    svsub_u16_m(svptrue_b16(),
                                                svdup_u16(256),
                                                v_نقاب));
    v_ہدف = svadd_u16_m(svptrue_b16(), vTemp0, vTemp1);

    واپس svlsr_n_u16_m(svptrue_b16(), v_ہدف, 8); // vTarget >> 8;
}

#اگر_ختم /* SDL_SVE2_EXTENSION_H */