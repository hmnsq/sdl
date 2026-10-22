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

#ಆದರೆ !defined(SDL_SVE2_EXTENSION_H) //&& (defined(__ARM_FEATURE_SVE2) && __ARM_FEATURE_SVE2)
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_SVE2_EXTENSION_H

#ಅನ್ತರ್ಭಾವ "SDL_sve2_util.h"

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
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_PLATFORM_ANDROID
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ __ARM_FEATURE_SVE
#ವ್ಯಾಖ್ಯಾನಿಸು __ARM_FEATURE_SVE 1
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ
#ಅನ್ತರ್ಭಾವ <arm_sve.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>

/*!
 * \brief a wrapper for __attribute__((nonnull))
 */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ ARM_NONNULL
#ವ್ಯಾಖ್ಯಾನಿಸು ARM_NONNULL(...) __attribute__((nonnull(__VA_ARGS__)))
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿಸು svlenu8()  svcntb_pat(SV_ALL)
#ವ್ಯಾಖ್ಯಾನಿಸು svlenu16() (svcntb_pat(SV_ALL) / ಗಾತ್ರ(uint16_t))
#ವ್ಯಾಖ್ಯಾನಿಸು svlenu32() (svcntb_pat(SV_ALL) / ಗಾತ್ರ(uint32_t))
#ವ್ಯಾಖ್ಯಾನಿಸು svlenu64() (svcntb_pat(SV_ALL) / ಗಾತ್ರ(uint64_t))

#ವ್ಯಾಖ್ಯಾನಿಸು svlens8()  svlenu8()
#ವ್ಯಾಖ್ಯಾನಿಸು svlens16() svlenu16()
#ವ್ಯಾಖ್ಯಾನಿಸು svlens32() svlenu32()
#ವ್ಯಾಖ್ಯಾನಿಸು svlens64() svlenu64()

#ವ್ಯಾಖ್ಯಾನಿಸು sdl_sve_stride_loop_pixel(ma_stride_ಗಾತ್ರ, ma_pred_name)          \
    ಗಾಗಿ (svbool_t ma_pred_name, *p_ತಾತ್ಕಾಲಿಕ = &ma_pred_name;                  \
         p_ತಾತ್ಕಾಲಿಕ != ಖಾಲಿ;                                                  \
         p_ತಾತ್ಕಾಲಿಕ = ಖಾಲಿ)                                                   \
        ಗಾಗಿ (size_t SVE_ಸುರಕ್ಷಿತ_NAME(n) = 0,                                \
                    sve_iteration_advance = svlenu8();                   \
             ({                                                          \
                 ma_pred_name = svwhilelt_b8((int32_t)SVE_ಸುರಕ್ಷಿತ_NAME(n),  \
                                             (int32_t)(ma_stride_ಗಾತ್ರ)); \
                 SVE_ಸುರಕ್ಷಿತ_NAME(n) < (ma_stride_ಗಾತ್ರ);                    \
             });                                                         \
             SVE_ಸುರಕ್ಷಿತ_NAME(n) += sve_iteration_advance)

#ವ್ಯಾಖ್ಯಾನಿಸು sdl_sve_stride_loop_u8 sdl_sve_stride_loop_pixel

#ವ್ಯಾಖ್ಯಾನಿಸು sdl_sve_stride_loop_u16(ma_stride_ಗಾತ್ರ, ma_pred_name)             \
    ಗಾಗಿ (svbool_t ma_pred_name, *p_ತಾತ್ಕಾಲಿಕ = &ma_pred_name;                   \
         p_ತಾತ್ಕಾಲಿಕ != ಖಾಲಿ;                                                   \
         p_ತಾತ್ಕಾಲಿಕ = ಖಾಲಿ)                                                    \
        ಗಾಗಿ (size_t SVE_ಸುರಕ್ಷಿತ_NAME(n) = 0,                                 \
                    sve_iteration_advance = svlenu16();                   \
             ({                                                           \
                 ma_pred_name = svwhilelt_b16((int32_t)SVE_ಸುರಕ್ಷಿತ_NAME(n),  \
                                              (int32_t)(ma_stride_ಗಾತ್ರ)); \
                 SVE_ಸುರಕ್ಷಿತ_NAME(n) < (ma_stride_ಗಾತ್ರ);                     \
             });                                                          \
             SVE_ಸುರಕ್ಷಿತ_NAME(n) += sve_iteration_advance)

#ವ್ಯಾಖ್ಯಾನಿಸು sdl_sve_stride_loop_u32(ma_stride_ಗಾತ್ರ, ma_pred_name)             \
    ಗಾಗಿ (svbool_t ma_pred_name, *p_ತಾತ್ಕಾಲಿಕ = &ma_pred_name;                   \
         p_ತಾತ್ಕಾಲಿಕ != ಖಾಲಿ;                                                   \
         p_ತಾತ್ಕಾಲಿಕ = ಖಾಲಿ)                                                    \
        ಗಾಗಿ (size_t SVE_ಸುರಕ್ಷಿತ_NAME(n) = 0,                                 \
                    sve_iteration_advance = svlenu32();                   \
             ({                                                           \
                 ma_pred_name = svwhilelt_b16((int32_t)SVE_ಸುರಕ್ಷಿತ_NAME(n),  \
                                              (int32_t)(ma_stride_ಗಾತ್ರ)); \
                 SVE_ಸುರಕ್ಷಿತ_NAME(n) < (ma_stride_ಗಾತ್ರ);                     \
             });                                                          \
             SVE_ಸುರಕ್ಷಿತ_NAME(n) += sve_iteration_advance)

#ವ್ಯಾಖ್ಯಾನಿಸು sdl_sve_pixel_ccc_foreach_chn(ma_ಮೂಲ_u16x3,                    \
                                      ma_ಗುರಿ_u16x3,                    \
                                      ...)                                \
    ಮಾಡು {                                                                  \
        svuint16x3_t sve_ಮೂಲ_u16x3 = ma_ಮೂಲ_u16x3;                  \
        (ಶೂನ್ಯ)sve_ಮೂಲ_u16x3;                                           \
        ಮಾಡು {                                                              \
            ಸ್ಥಿರಾಂಕ uint8_t sve_src_chn_idx = 0;                            \
            (ಶೂನ್ಯ)sve_src_chn_idx;                                        \
            svuint16_t sve_ಮೂಲ_u16 = svget3((ma_ಮೂಲ_u16x3), 0);     \
            svuint16_t sve_ಗುರಿ_u16 = svget3((ma_ಗುರಿ_u16x3), 0);     \
            (ಶೂನ್ಯ)sve_ಮೂಲ_u16;                                         \
            (ಶೂನ್ಯ)sve_ಗುರಿ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ಗುರಿ_u16x3 = svset3(ma_ಗುರಿ_u16x3, 0, sve_ಗುರಿ_u16); \
        } ಆಗ (0);                                                      \
        ಮಾಡು {                                                              \
            ಸ್ಥಿರಾಂಕ uint8_t sve_src_chn_idx = 1;                            \
            (ಶೂನ್ಯ)sve_src_chn_idx;                                        \
            svuint16_t sve_ಮೂಲ_u16 = svget3((ma_ಮೂಲ_u16x3), 1);     \
            svuint16_t sve_ಗುರಿ_u16 = svget3((ma_ಗುರಿ_u16x3), 1);     \
            (ಶೂನ್ಯ)sve_ಮೂಲ_u16;                                         \
            (ಶೂನ್ಯ)sve_ಗುರಿ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ಗುರಿ_u16x3 = svset3(ma_ಗುರಿ_u16x3, 1, sve_ಗುರಿ_u16); \
        } ಆಗ (0);                                                      \
        ಮಾಡು {                                                              \
            ಸ್ಥಿರಾಂಕ uint8_t sve_src_chn_idx = 2;                            \
            (ಶೂನ್ಯ)sve_src_chn_idx;                                        \
            svuint16_t sve_ಮೂಲ_u16 = svget3((ma_ಮೂಲ_u16x3), 2);     \
            svuint16_t sve_ಗುರಿ_u16 = svget3((ma_ಗುರಿ_u16x3), 2);     \
            (ಶೂನ್ಯ)sve_ಮೂಲ_u16;                                         \
            (ಶೂನ್ಯ)sve_ಗುರಿ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ಗುರಿ_u16x3 = svset3(ma_ಗುರಿ_u16x3, 2, sve_ಗುರಿ_u16); \
        } ಆಗ (0);                                                      \
    } ಆಗ (0)

#ವ್ಯಾಖ್ಯಾನಿಸು sdl_sve_pixel_accc_foreach_chn012(ma_ಮೂಲ_u16x4,                \
                                          ma_ಗುರಿ_u16x4,                \
                                          ...)                            \
    ಮಾಡು {                                                                  \
        svuint16x4_t sve_ಮೂಲ_u16x4 = ma_ಮೂಲ_u16x4;                  \
        (ಶೂನ್ಯ)sve_ಮೂಲ_u16x4;                                           \
        ಮಾಡು {                                                              \
            ಸ್ಥಿರಾಂಕ uint8_t sve_src_chn_idx = 0;                            \
            (ಶೂನ್ಯ)sve_src_chn_idx;                                        \
            svuint16_t sve_ಮೂಲ_u16 = svget4((ma_ಮೂಲ_u16x4), 0);     \
            svuint16_t sve_ಗುರಿ_u16 = svget4((ma_ಗುರಿ_u16x4), 0);     \
            (ಶೂನ್ಯ)sve_ಮೂಲ_u16;                                         \
            (ಶೂನ್ಯ)sve_ಗುರಿ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ಗುರಿ_u16x4 = svset4(ma_ಗುರಿ_u16x4, 0, sve_ಗುರಿ_u16); \
        } ಆಗ (0);                                                      \
        ಮಾಡು {                                                              \
            ಸ್ಥಿರಾಂಕ uint8_t sve_src_chn_idx = 1;                            \
            (ಶೂನ್ಯ)sve_src_chn_idx;                                        \
            svuint16_t sve_ಮೂಲ_u16 = svget4((ma_ಮೂಲ_u16x4), 1);     \
            svuint16_t sve_ಗುರಿ_u16 = svget4((ma_ಗುರಿ_u16x4), 1);     \
            (ಶೂನ್ಯ)sve_ಮೂಲ_u16;                                         \
            (ಶೂನ್ಯ)sve_ಗುರಿ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ಗುರಿ_u16x4 = svset4(ma_ಗುರಿ_u16x4, 1, sve_ಗುರಿ_u16); \
        } ಆಗ (0);                                                      \
        ಮಾಡು {                                                              \
            ಸ್ಥಿರಾಂಕ uint8_t sve_src_chn_idx = 2;                            \
            (ಶೂನ್ಯ)sve_src_chn_idx;                                        \
            svuint16_t sve_ಮೂಲ_u16 = svget4((ma_ಮೂಲ_u16x4), 2);     \
            svuint16_t sve_ಗುರಿ_u16 = svget4((ma_ಗುರಿ_u16x4), 2);     \
            (ಶೂನ್ಯ)sve_ಮೂಲ_u16;                                         \
            (ಶೂನ್ಯ)sve_ಗುರಿ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ಗುರಿ_u16x4 = svset4(ma_ಗುರಿ_u16x4, 2, sve_ಗುರಿ_u16); \
        } ಆಗ (0);                                                      \
    } ಆಗ (0)

#ವ್ಯಾಖ್ಯಾನಿಸು sdl_sve_pixel_accc_foreach_chn(ma_ಮೂಲ_u16x4,                   \
                                       ma_ಗುರಿ_u16x4,                   \
                                       ...)                               \
    ಮಾಡು {                                                                  \
        svuint16x4_t sve_ಮೂಲ_u16x4 = ma_ಮೂಲ_u16x4;                  \
        (ಶೂನ್ಯ)sve_ಮೂಲ_u16x4;                                           \
        ಮಾಡು {                                                              \
            ಸ್ಥಿರಾಂಕ uint8_t sve_src_chn_idx = 0;                            \
            (ಶೂನ್ಯ)sve_src_chn_idx;                                        \
            (ಶೂನ್ಯ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ಮೂಲ_u16 = svget4((ma_ಮೂಲ_u16x4), 0);     \
            svuint16_t sve_ಗುರಿ_u16 = svget4((ma_ಗುರಿ_u16x4), 0);     \
            (ಶೂನ್ಯ)sve_ಮೂಲ_u16;                                         \
            (ಶೂನ್ಯ)sve_ಗುರಿ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ಗುರಿ_u16x4 = svset4(ma_ಗುರಿ_u16x4, 0, sve_ಗುರಿ_u16); \
        } ಆಗ (0);                                                      \
        ಮಾಡು {                                                              \
            ಸ್ಥಿರಾಂಕ uint8_t sve_src_chn_idx = 1;                            \
            (ಶೂನ್ಯ)sve_src_chn_idx;                                        \
            (ಶೂನ್ಯ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ಮೂಲ_u16 = svget4((ma_ಮೂಲ_u16x4), 1);     \
            svuint16_t sve_ಗುರಿ_u16 = svget4((ma_ಗುರಿ_u16x4), 1);     \
            (ಶೂನ್ಯ)sve_ಮೂಲ_u16;                                         \
            (ಶೂನ್ಯ)sve_ಗುರಿ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ಗುರಿ_u16x4 = svset4(ma_ಗುರಿ_u16x4, 1, sve_ಗುರಿ_u16); \
        } ಆಗ (0);                                                      \
        ಮಾಡು {                                                              \
            ಸ್ಥಿರಾಂಕ uint8_t sve_src_chn_idx = 2;                            \
            (ಶೂನ್ಯ)sve_src_chn_idx;                                        \
            (ಶೂನ್ಯ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ಮೂಲ_u16 = svget4((ma_ಮೂಲ_u16x4), 2);     \
            svuint16_t sve_ಗುರಿ_u16 = svget4((ma_ಗುರಿ_u16x4), 2);     \
            (ಶೂನ್ಯ)sve_ಮೂಲ_u16;                                         \
            (ಶೂನ್ಯ)sve_ಗುರಿ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ಗುರಿ_u16x4 = svset4(ma_ಗುರಿ_u16x4, 2, sve_ಗುರಿ_u16); \
        } ಆಗ (0);                                                      \
        ಮಾಡು {                                                              \
            ಸ್ಥಿರಾಂಕ uint8_t sve_src_chn_idx = 3;                            \
            (ಶೂನ್ಯ)sve_src_chn_idx;                                        \
            (ಶೂನ್ಯ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ಮೂಲ_u16 = svget4((ma_ಮೂಲ_u16x4), 3);     \
            svuint16_t sve_ಗುರಿ_u16 = svget4((ma_ಗುರಿ_u16x4), 3);     \
            (ಶೂನ್ಯ)sve_ಮೂಲ_u16;                                         \
            (ಶೂನ್ಯ)sve_ಗುರಿ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ಗುರಿ_u16x4 = svset4(ma_ಗುರಿ_u16x4, 3, sve_ಗುರಿ_u16); \
        } ಆಗ (0);                                                      \
    } ಆಗ (0)

#ವ್ಯಾಖ್ಯಾನಿಸು sdl_sve_pixel_u16x4_foreach_chn(ma_ಮೂಲ_u16x4,                  \
                                        ma_ಗುರಿ_u16x4,                  \
                                        ...)                              \
    ಮಾಡು {                                                                  \
        svuint16x4_t sve_ಮೂಲ_u16x4 = ma_ಮೂಲ_u16x4;                  \
        (ಶೂನ್ಯ)sve_ಮೂಲ_u16x4;                                           \
        ಮಾಡು {                                                              \
            ಸ್ಥಿರಾಂಕ uint8_t sve_src_chn_idx = 0;                            \
            (ಶೂನ್ಯ)sve_src_chn_idx;                                        \
            svuint16_t sve_ಮೂಲ_u16 = svget4((ma_ಮೂಲ_u16x4), 0);     \
            svuint16_t sve_ಗುರಿ_u16 = svget4((ma_ಗುರಿ_u16x4), 0);     \
            (ಶೂನ್ಯ)sve_ಮೂಲ_u16;                                         \
            (ಶೂನ್ಯ)sve_ಗುರಿ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ಗುರಿ_u16x4 = svset4(ma_ಗುರಿ_u16x4, 0, sve_ಗುರಿ_u16); \
        } ಆಗ (0);                                                      \
        ಮಾಡು {                                                              \
            ಸ್ಥಿರಾಂಕ uint8_t sve_src_chn_idx = 1;                            \
            (ಶೂನ್ಯ)sve_src_chn_idx;                                        \
            svuint16_t sve_ಮೂಲ_u16 = svget4((ma_ಮೂಲ_u16x4), 1);     \
            svuint16_t sve_ಗುರಿ_u16 = svget4((ma_ಗುರಿ_u16x4), 1);     \
            (ಶೂನ್ಯ)sve_ಮೂಲ_u16;                                         \
            (ಶೂನ್ಯ)sve_ಗುರಿ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ಗುರಿ_u16x4 = svset4(ma_ಗುರಿ_u16x4, 1, sve_ಗುರಿ_u16); \
        } ಆಗ (0);                                                      \
        ಮಾಡು {                                                              \
            ಸ್ಥಿರಾಂಕ uint8_t sve_src_chn_idx = 2;                            \
            (ಶೂನ್ಯ)sve_src_chn_idx;                                        \
            svuint16_t sve_ಮೂಲ_u16 = svget4((ma_ಮೂಲ_u16x4), 2);     \
            svuint16_t sve_ಗುರಿ_u16 = svget4((ma_ಗುರಿ_u16x4), 2);     \
            (ಶೂನ್ಯ)sve_ಮೂಲ_u16;                                         \
            (ಶೂನ್ಯ)sve_ಗುರಿ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ಗುರಿ_u16x4 = svset4(ma_ಗುರಿ_u16x4, 2, sve_ಗುರಿ_u16); \
        } ಆಗ (0);                                                      \
        ಮಾಡು {                                                              \
            ಸ್ಥಿರಾಂಕ uint8_t sve_src_chn_idx = 3;                            \
            (ಶೂನ್ಯ)sve_src_chn_idx;                                        \
            svuint16_t sve_ಮೂಲ_u16 = svget4((ma_ಮೂಲ_u16x4), 3);     \
            svuint16_t sve_ಗುರಿ_u16 = svget4((ma_ಗುರಿ_u16x4), 3);     \
            (ಶೂನ್ಯ)sve_ಮೂಲ_u16;                                         \
            (ಶೂನ್ಯ)sve_ಗುರಿ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ಗುರಿ_u16x4 = svset4(ma_ಗುರಿ_u16x4, 3, sve_ಗುರಿ_u16); \
        } ಆಗ (0);                                                      \
    } ಆಗ (0)

#ವ್ಯಾಖ್ಯಾನಿಸು sdl_sve_pixel_u16x4_foreach_chn_src_dst_rev(ma_ಮೂಲ_u16x4,      \
                                                    ma_ಗುರಿ_u16x4,      \
                                                    ...)                  \
    ಮಾಡು {                                                                  \
        svuint16x4_t sve_ಮೂಲ_u16x4 = ma_ಮೂಲ_u16x4;                  \
        (ಶೂನ್ಯ)sve_ಮೂಲ_u16x4;                                           \
        ಮಾಡು {                                                              \
            ಸ್ಥಿರಾಂಕ uint8_t sve_src_chn_idx = 0;                            \
            ಸ್ಥಿರಾಂಕ uint8_t sve_dst_chn_idx = 3;                            \
            (ಶೂನ್ಯ)sve_src_chn_idx;                                        \
            (ಶೂನ್ಯ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ಮೂಲ_u16 = svget4((ma_ಮೂಲ_u16x4), 0);     \
            svuint16_t sve_ಗುರಿ_u16 = svget4((ma_ಗುರಿ_u16x4), 3);     \
            (ಶೂನ್ಯ)sve_ಮೂಲ_u16;                                         \
            (ಶೂನ್ಯ)sve_ಗುರಿ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ಗುರಿ_u16x4 = svset4(ma_ಗುರಿ_u16x4, 3, sve_ಗುರಿ_u16); \
        } ಆಗ (0);                                                      \
        ಮಾಡು {                                                              \
            ಸ್ಥಿರಾಂಕ uint8_t sve_src_chn_idx = 1;                            \
            ಸ್ಥಿರಾಂಕ uint8_t sve_dst_chn_idx = 2;                            \
            (ಶೂನ್ಯ)sve_src_chn_idx;                                        \
            (ಶೂನ್ಯ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ಮೂಲ_u16 = svget4((ma_ಮೂಲ_u16x4), 1);     \
            svuint16_t sve_ಗುರಿ_u16 = svget4((ma_ಗುರಿ_u16x4), 2);     \
            (ಶೂನ್ಯ)sve_ಮೂಲ_u16;                                         \
            (ಶೂನ್ಯ)sve_ಗುರಿ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ಗುರಿ_u16x4 = svset4(ma_ಗುರಿ_u16x4, 2, sve_ಗುರಿ_u16); \
        } ಆಗ (0);                                                      \
        ಮಾಡು {                                                              \
            ಸ್ಥಿರಾಂಕ uint8_t sve_src_chn_idx = 2;                            \
            ಸ್ಥಿರಾಂಕ uint8_t sve_dst_chn_idx = 1;                            \
            (ಶೂನ್ಯ)sve_src_chn_idx;                                        \
            (ಶೂನ್ಯ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ಮೂಲ_u16 = svget4((ma_ಮೂಲ_u16x4), 2);     \
            svuint16_t sve_ಗುರಿ_u16 = svget4((ma_ಗುರಿ_u16x4), 1);     \
            (ಶೂನ್ಯ)sve_ಮೂಲ_u16;                                         \
            (ಶೂನ್ಯ)sve_ಗುರಿ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ಗುರಿ_u16x4 = svset4(ma_ಗುರಿ_u16x4, 1, sve_ಗುರಿ_u16); \
        } ಆಗ (0);                                                      \
        ಮಾಡು {                                                              \
            ಸ್ಥಿರಾಂಕ uint8_t sve_src_chn_idx = 3;                            \
            ಸ್ಥಿರಾಂಕ uint8_t sve_dst_chn_idx = 0;                            \
            (ಶೂನ್ಯ)sve_src_chn_idx;                                        \
            (ಶೂನ್ಯ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ಮೂಲ_u16 = svget4((ma_ಮೂಲ_u16x4), 3);     \
            svuint16_t sve_ಗುರಿ_u16 = svget4((ma_ಗುರಿ_u16x4), 0);     \
            (ಶೂನ್ಯ)sve_ಮೂಲ_u16;                                         \
            (ಶೂನ್ಯ)sve_ಗುರಿ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ಗುರಿ_u16x4 = svset4(ma_ಗುರಿ_u16x4, 0, sve_ಗುರಿ_u16); \
        } ಆಗ (0);                                                      \
    } ಆಗ (0)

#ವ್ಯಾಖ್ಯಾನಿಸು sdl_sve_pixel_u16x4_foreach_chn_accc_ccca(ma_ಮೂಲ_u16x4,        \
                                                  ma_ಗುರಿ_u16x4,        \
                                                  ...)                    \
    ಮಾಡು {                                                                  \
        svuint16x4_t sve_ಮೂಲ_u16x4 = ma_ಮೂಲ_u16x4;                  \
        (ಶೂನ್ಯ)sve_ಮೂಲ_u16x4;                                           \
        ಮಾಡು {                                                              \
            ಸ್ಥಿರಾಂಕ uint8_t sve_src_chn_idx = 0;                            \
            ಸ್ಥಿರಾಂಕ uint8_t sve_dst_chn_idx = 1;                            \
            (ಶೂನ್ಯ)sve_src_chn_idx;                                        \
            (ಶೂನ್ಯ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ಮೂಲ_u16 = svget4((ma_ಮೂಲ_u16x4), 0);     \
            svuint16_t sve_ಗುರಿ_u16 = svget4((ma_ಗುರಿ_u16x4), 1);     \
            (ಶೂನ್ಯ)sve_ಮೂಲ_u16;                                         \
            (ಶೂನ್ಯ)sve_ಗುರಿ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ಗುರಿ_u16x4 = svset4(ma_ಗುರಿ_u16x4, 1, sve_ಗುರಿ_u16); \
        } ಆಗ (0);                                                      \
        ಮಾಡು {                                                              \
            ಸ್ಥಿರಾಂಕ uint8_t sve_src_chn_idx = 1;                            \
            ಸ್ಥಿರಾಂಕ uint8_t sve_dst_chn_idx = 2;                            \
            (ಶೂನ್ಯ)sve_src_chn_idx;                                        \
            (ಶೂನ್ಯ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ಮೂಲ_u16 = svget4((ma_ಮೂಲ_u16x4), 1);     \
            svuint16_t sve_ಗುರಿ_u16 = svget4((ma_ಗುರಿ_u16x4), 2);     \
            (ಶೂನ್ಯ)sve_ಮೂಲ_u16;                                         \
            (ಶೂನ್ಯ)sve_ಗುರಿ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ಗುರಿ_u16x4 = svset4(ma_ಗುರಿ_u16x4, 2, sve_ಗುರಿ_u16); \
        } ಆಗ (0);                                                      \
        ಮಾಡು {                                                              \
            ಸ್ಥಿರಾಂಕ uint8_t sve_src_chn_idx = 2;                            \
            ಸ್ಥಿರಾಂಕ uint8_t sve_dst_chn_idx = 3;                            \
            (ಶೂನ್ಯ)sve_src_chn_idx;                                        \
            (ಶೂನ್ಯ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ಮೂಲ_u16 = svget4((ma_ಮೂಲ_u16x4), 2);     \
            svuint16_t sve_ಗುರಿ_u16 = svget4((ma_ಗುರಿ_u16x4), 3);     \
            (ಶೂನ್ಯ)sve_ಮೂಲ_u16;                                         \
            (ಶೂನ್ಯ)sve_ಗುರಿ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ಗುರಿ_u16x4 = svset4(ma_ಗುರಿ_u16x4, 3, sve_ಗುರಿ_u16); \
        } ಆಗ (0);                                                      \
        ಮಾಡು {                                                              \
            ಸ್ಥಿರಾಂಕ uint8_t sve_src_chn_idx = 3;                            \
            ಸ್ಥಿರಾಂಕ uint8_t sve_dst_chn_idx = 0;                            \
            (ಶೂನ್ಯ)sve_src_chn_idx;                                        \
            (ಶೂನ್ಯ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ಮೂಲ_u16 = svget4((ma_ಮೂಲ_u16x4), 3);     \
            svuint16_t sve_ಗುರಿ_u16 = svget4((ma_ಗುರಿ_u16x4), 0);     \
            (ಶೂನ್ಯ)sve_ಮೂಲ_u16;                                         \
            (ಶೂನ್ಯ)sve_ಗುರಿ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ಗುರಿ_u16x4 = svset4(ma_ಗುರಿ_u16x4, 0, sve_ಗುರಿ_u16); \
        } ಆಗ (0);                                                      \
    } ಆಗ (0)

#ವ್ಯಾಖ್ಯಾನಿಸು sdl_sve_pixel_u16x4_foreach_chn_ccca_accc(ma_ಮೂಲ_u16x4,        \
                                                  ma_ಗುರಿ_u16x4,        \
                                                  ...)                    \
    ಮಾಡು {                                                                  \
        svuint16x4_t sve_ಮೂಲ_u16x4 = ma_ಮೂಲ_u16x4;                  \
        (ಶೂನ್ಯ)sve_ಮೂಲ_u16x4;                                           \
        ಮಾಡು {                                                              \
            ಸ್ಥಿರಾಂಕ uint8_t sve_src_chn_idx = 1;                            \
            ಸ್ಥಿರಾಂಕ uint8_t sve_dst_chn_idx = 0;                            \
            (ಶೂನ್ಯ)sve_src_chn_idx;                                        \
            (ಶೂನ್ಯ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ಮೂಲ_u16 = svget4((ma_ಮೂಲ_u16x4), 1);     \
            svuint16_t sve_ಗುರಿ_u16 = svget4((ma_ಗುರಿ_u16x4), 0);     \
            (ಶೂನ್ಯ)sve_ಮೂಲ_u16;                                         \
            (ಶೂನ್ಯ)sve_ಗುರಿ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ಗುರಿ_u16x4 = svset4(ma_ಗುರಿ_u16x4, 0, sve_ಗುರಿ_u16); \
        } ಆಗ (0);                                                      \
        ಮಾಡು {                                                              \
            ಸ್ಥಿರಾಂಕ uint8_t sve_src_chn_idx = 2;                            \
            ಸ್ಥಿರಾಂಕ uint8_t sve_dst_chn_idx = 1;                            \
            (ಶೂನ್ಯ)sve_src_chn_idx;                                        \
            (ಶೂನ್ಯ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ಮೂಲ_u16 = svget4((ma_ಮೂಲ_u16x4), 2);     \
            svuint16_t sve_ಗುರಿ_u16 = svget4((ma_ಗುರಿ_u16x4), 1);     \
            (ಶೂನ್ಯ)sve_ಮೂಲ_u16;                                         \
            (ಶೂನ್ಯ)sve_ಗುರಿ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ಗುರಿ_u16x4 = svset4(ma_ಗುರಿ_u16x4, 1, sve_ಗುರಿ_u16); \
        } ಆಗ (0);                                                      \
        ಮಾಡು {                                                              \
            ಸ್ಥಿರಾಂಕ uint8_t sve_src_chn_idx = 3;                            \
            ಸ್ಥಿರಾಂಕ uint8_t sve_dst_chn_idx = 2;                            \
            (ಶೂನ್ಯ)sve_src_chn_idx;                                        \
            (ಶೂನ್ಯ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ಮೂಲ_u16 = svget4((ma_ಮೂಲ_u16x4), 3);     \
            svuint16_t sve_ಗುರಿ_u16 = svget4((ma_ಗುರಿ_u16x4), 2);     \
            (ಶೂನ್ಯ)sve_ಮೂಲ_u16;                                         \
            (ಶೂನ್ಯ)sve_ಗುರಿ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ಗುರಿ_u16x4 = svset4(ma_ಗುರಿ_u16x4, 2, sve_ಗುರಿ_u16); \
        } ಆಗ (0);                                                      \
        ಮಾಡು {                                                              \
            ಸ್ಥಿರಾಂಕ uint8_t sve_src_chn_idx = 0;                            \
            ಸ್ಥಿರಾಂಕ uint8_t sve_dst_chn_idx = 3;                            \
            (ಶೂನ್ಯ)sve_src_chn_idx;                                        \
            (ಶೂನ್ಯ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ಮೂಲ_u16 = svget4((ma_ಮೂಲ_u16x4), 0);     \
            svuint16_t sve_ಗುರಿ_u16 = svget4((ma_ಗುರಿ_u16x4), 3);     \
            (ಶೂನ್ಯ)sve_ಮೂಲ_u16;                                         \
            (ಶೂನ್ಯ)sve_ಗುರಿ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ಗುರಿ_u16x4 = svset4(ma_ಗುರಿ_u16x4, 3, sve_ಗುರಿ_u16); \
        } ಆಗ (0);                                                      \
    } ಆಗ (0)

#ವ್ಯಾಖ್ಯಾನಿಸು sdl_sve_pixel_u16x4_foreach_chn_a123_a321(ma_ಮೂಲ_u16x4,        \
                                                  ma_ಗುರಿ_u16x4,        \
                                                  ...)                    \
    ಮಾಡು {                                                                  \
        svuint16x4_t sve_ಮೂಲ_u16x4 = ma_ಮೂಲ_u16x4;                  \
        (ಶೂನ್ಯ)sve_ಮೂಲ_u16x4;                                           \
        ಮಾಡು {                                                              \
            ಸ್ಥಿರಾಂಕ uint8_t sve_src_chn_idx = 0;                            \
            ಸ್ಥಿರಾಂಕ uint8_t sve_dst_chn_idx = 2;                            \
            (ಶೂನ್ಯ)sve_src_chn_idx;                                        \
            (ಶೂನ್ಯ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ಮೂಲ_u16 = svget4((ma_ಮೂಲ_u16x4), 0);     \
            svuint16_t sve_ಗುರಿ_u16 = svget4((ma_ಗುರಿ_u16x4), 2);     \
            (ಶೂನ್ಯ)sve_ಮೂಲ_u16;                                         \
            (ಶೂನ್ಯ)sve_ಗುರಿ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ಗುರಿ_u16x4 = svset4(ma_ಗುರಿ_u16x4, 2, sve_ಗುರಿ_u16); \
        } ಆಗ (0);                                                      \
        ಮಾಡು {                                                              \
            ಸ್ಥಿರಾಂಕ uint8_t sve_src_chn_idx = 1;                            \
            ಸ್ಥಿರಾಂಕ uint8_t sve_dst_chn_idx = 1;                            \
            (ಶೂನ್ಯ)sve_src_chn_idx;                                        \
            (ಶೂನ್ಯ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ಮೂಲ_u16 = svget4((ma_ಮೂಲ_u16x4), 1);     \
            svuint16_t sve_ಗುರಿ_u16 = svget4((ma_ಗುರಿ_u16x4), 1);     \
            (ಶೂನ್ಯ)sve_ಮೂಲ_u16;                                         \
            (ಶೂನ್ಯ)sve_ಗುರಿ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ಗುರಿ_u16x4 = svset4(ma_ಗುರಿ_u16x4, 1, sve_ಗುರಿ_u16); \
        } ಆಗ (0);                                                      \
        ಮಾಡು {                                                              \
            ಸ್ಥಿರಾಂಕ uint8_t sve_src_chn_idx = 2;                            \
            ಸ್ಥಿರಾಂಕ uint8_t sve_dst_chn_idx = 0;                            \
            (ಶೂನ್ಯ)sve_src_chn_idx;                                        \
            (ಶೂನ್ಯ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ಮೂಲ_u16 = svget4((ma_ಮೂಲ_u16x4), 2);     \
            svuint16_t sve_ಗುರಿ_u16 = svget4((ma_ಗುರಿ_u16x4), 0);     \
            (ಶೂನ್ಯ)sve_ಮೂಲ_u16;                                         \
            (ಶೂನ್ಯ)sve_ಗುರಿ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ಗುರಿ_u16x4 = svset4(ma_ಗುರಿ_u16x4, 0, sve_ಗುರಿ_u16); \
        } ಆಗ (0);                                                      \
        ಮಾಡು {                                                              \
            ಸ್ಥಿರಾಂಕ uint8_t sve_src_chn_idx = 3;                            \
            ಸ್ಥಿರಾಂಕ uint8_t sve_dst_chn_idx = 3;                            \
            (ಶೂನ್ಯ)sve_src_chn_idx;                                        \
            (ಶೂನ್ಯ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ಮೂಲ_u16 = svget4((ma_ಮೂಲ_u16x4), 3);     \
            svuint16_t sve_ಗುರಿ_u16 = svget4((ma_ಗುರಿ_u16x4), 3);     \
            (ಶೂನ್ಯ)sve_ಮೂಲ_u16;                                         \
            (ಶೂನ್ಯ)sve_ಗುರಿ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ಗುರಿ_u16x4 = svset4(ma_ಗುರಿ_u16x4, 3, sve_ಗುರಿ_u16); \
        } ಆಗ (0);                                                      \
    } ಆಗ (0)

#ವ್ಯಾಖ್ಯಾನಿಸು sdl_sve_pixel_u16x4_foreach_chn_123a_321a(ma_ಮೂಲ_u16x4,        \
                                                  ma_ಗುರಿ_u16x4,        \
                                                  ...)                    \
    ಮಾಡು {                                                                  \
        svuint16x4_t sve_ಮೂಲ_u16x4 = ma_ಮೂಲ_u16x4;                  \
        (ಶೂನ್ಯ)sve_ಮೂಲ_u16x4;                                           \
        ಮಾಡು {                                                              \
            ಸ್ಥಿರಾಂಕ uint8_t sve_src_chn_idx = 0;                            \
            ಸ್ಥಿರಾಂಕ uint8_t sve_dst_chn_idx = 0;                            \
            (ಶೂನ್ಯ)sve_src_chn_idx;                                        \
            (ಶೂನ್ಯ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ಮೂಲ_u16 = svget4((ma_ಮೂಲ_u16x4), 0);     \
            svuint16_t sve_ಗುರಿ_u16 = svget4((ma_ಗುರಿ_u16x4), 0);     \
            (ಶೂನ್ಯ)sve_ಮೂಲ_u16;                                         \
            (ಶೂನ್ಯ)sve_ಗುರಿ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ಗುರಿ_u16x4 = svset4(ma_ಗುರಿ_u16x4, 0, sve_ಗುರಿ_u16); \
        } ಆಗ (0);                                                      \
        ಮಾಡು {                                                              \
            ಸ್ಥಿರಾಂಕ uint8_t sve_src_chn_idx = 1;                            \
            ಸ್ಥಿರಾಂಕ uint8_t sve_dst_chn_idx = 3;                            \
            (ಶೂನ್ಯ)sve_src_chn_idx;                                        \
            (ಶೂನ್ಯ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ಮೂಲ_u16 = svget4((ma_ಮೂಲ_u16x4), 1);     \
            svuint16_t sve_ಗುರಿ_u16 = svget4((ma_ಗುರಿ_u16x4), 3);     \
            (ಶೂನ್ಯ)sve_ಮೂಲ_u16;                                         \
            (ಶೂನ್ಯ)sve_ಗುರಿ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ಗುರಿ_u16x4 = svset4(ma_ಗುರಿ_u16x4, 3, sve_ಗುರಿ_u16); \
        } ಆಗ (0);                                                      \
        ಮಾಡು {                                                              \
            ಸ್ಥಿರಾಂಕ uint8_t sve_src_chn_idx = 2;                            \
            ಸ್ಥಿರಾಂಕ uint8_t sve_dst_chn_idx = 2;                            \
            (ಶೂನ್ಯ)sve_src_chn_idx;                                        \
            (ಶೂನ್ಯ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ಮೂಲ_u16 = svget4((ma_ಮೂಲ_u16x4), 2);     \
            svuint16_t sve_ಗುರಿ_u16 = svget4((ma_ಗುರಿ_u16x4), 2);     \
            (ಶೂನ್ಯ)sve_ಮೂಲ_u16;                                         \
            (ಶೂನ್ಯ)sve_ಗುರಿ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ಗುರಿ_u16x4 = svset4(ma_ಗುರಿ_u16x4, 2, sve_ಗುರಿ_u16); \
        } ಆಗ (0);                                                      \
        ಮಾಡು {                                                              \
            ಸ್ಥಿರಾಂಕ uint8_t sve_src_chn_idx = 3;                            \
            ಸ್ಥಿರಾಂಕ uint8_t sve_dst_chn_idx = 1;                            \
            (ಶೂನ್ಯ)sve_src_chn_idx;                                        \
            (ಶೂನ್ಯ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ಮೂಲ_u16 = svget4((ma_ಮೂಲ_u16x4), 3);     \
            svuint16_t sve_ಗುರಿ_u16 = svget4((ma_ಗುರಿ_u16x4), 1);     \
            (ಶೂನ್ಯ)sve_ಮೂಲ_u16;                                         \
            (ಶೂನ್ಯ)sve_ಗುರಿ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ಗುರಿ_u16x4 = svset4(ma_ಗುರಿ_u16x4, 1, sve_ಗುರಿ_u16); \
        } ಆಗ (0);                                                      \
    } ಆಗ (0)

#ವ್ಯಾಖ್ಯಾನಿಸು sdl_sve_pixel_u16x4_foreach_chn_argb_rgb565(ma_ಮೂಲ_u16x4,      \
                                                    ma_ಗುರಿ_u16x3,      \
                                                    ...)                  \
    ಮಾಡು {                                                                  \
        svuint16x4_t sve_ಮೂಲ_u16x4 = ma_ಮೂಲ_u16x4;                  \
        (ಶೂನ್ಯ)sve_ಮೂಲ_u16x4;                                           \
        ಮಾಡು {                                                              \
            ಸ್ಥಿರಾಂಕ uint8_t sve_src_chn_idx = 0;                            \
            ಸ್ಥಿರಾಂಕ uint8_t sve_dst_chn_idx = 0;                            \
            (ಶೂನ್ಯ)sve_src_chn_idx;                                        \
            (ಶೂನ್ಯ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ಮೂಲ_u16 = svget4((ma_ಮೂಲ_u16x4), 0);     \
            svuint16_t sve_ಗುರಿ_u16 = svget3((ma_ಗುರಿ_u16x3), 0);     \
            (ಶೂನ್ಯ)sve_ಮೂಲ_u16;                                         \
            (ಶೂನ್ಯ)sve_ಗುರಿ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ಗುರಿ_u16x3 = svset3(ma_ಗುರಿ_u16x3, 0, sve_ಗುರಿ_u16); \
        } ಆಗ (0);                                                      \
        ಮಾಡು {                                                              \
            ಸ್ಥಿರಾಂಕ uint8_t sve_src_chn_idx = 1;                            \
            ಸ್ಥಿರಾಂಕ uint8_t sve_dst_chn_idx = 1;                            \
            (ಶೂನ್ಯ)sve_src_chn_idx;                                        \
            (ಶೂನ್ಯ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ಮೂಲ_u16 = svget4((ma_ಮೂಲ_u16x4), 1);     \
            svuint16_t sve_ಗುರಿ_u16 = svget3((ma_ಗುರಿ_u16x3), 1);     \
            (ಶೂನ್ಯ)sve_ಮೂಲ_u16;                                         \
            (ಶೂನ್ಯ)sve_ಗುರಿ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ಗುರಿ_u16x3 = svset3(ma_ಗುರಿ_u16x3, 1, sve_ಗುರಿ_u16); \
        } ಆಗ (0);                                                      \
        ಮಾಡು {                                                              \
            ಸ್ಥಿರಾಂಕ uint8_t sve_src_chn_idx = 2;                            \
            ಸ್ಥಿರಾಂಕ uint8_t sve_dst_chn_idx = 2;                            \
            (ಶೂನ್ಯ)sve_src_chn_idx;                                        \
            (ಶೂನ್ಯ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ಮೂಲ_u16 = svget4((ma_ಮೂಲ_u16x4), 2);     \
            svuint16_t sve_ಗುರಿ_u16 = svget3((ma_ಗುರಿ_u16x3), 2);     \
            (ಶೂನ್ಯ)sve_ಮೂಲ_u16;                                         \
            (ಶೂನ್ಯ)sve_ಗುರಿ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ಗುರಿ_u16x3 = svset3(ma_ಗುರಿ_u16x3, 2, sve_ಗುರಿ_u16); \
        } ಆಗ (0);                                                      \
    } ಆಗ (0)

#ವ್ಯಾಖ್ಯಾನಿಸು sdl_sve_pixel_u16x4_foreach_chn_rgba_rgb565(ma_ಮೂಲ_u16x4,      \
                                                    ma_ಗುರಿ_u16x3,      \
                                                    ...)                  \
    ಮಾಡು {                                                                  \
        svuint16x4_t sve_ಮೂಲ_u16x4 = ma_ಮೂಲ_u16x4;                  \
        (ಶೂನ್ಯ)sve_ಮೂಲ_u16x4;                                           \
        ಮಾಡು {                                                              \
            ಸ್ಥಿರಾಂಕ uint8_t sve_src_chn_idx = 1;                            \
            ಸ್ಥಿರಾಂಕ uint8_t sve_dst_chn_idx = 0;                            \
            (ಶೂನ್ಯ)sve_src_chn_idx;                                        \
            (ಶೂನ್ಯ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ಮೂಲ_u16 = svget4((ma_ಮೂಲ_u16x4), 1);     \
            svuint16_t sve_ಗುರಿ_u16 = svget3((ma_ಗುರಿ_u16x3), 0);     \
            (ಶೂನ್ಯ)sve_ಮೂಲ_u16;                                         \
            (ಶೂನ್ಯ)sve_ಗುರಿ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ಗುರಿ_u16x3 = svset3(ma_ಗುರಿ_u16x3, 0, sve_ಗುರಿ_u16); \
        } ಆಗ (0);                                                      \
        ಮಾಡು {                                                              \
            ಸ್ಥಿರಾಂಕ uint8_t sve_src_chn_idx = 2;                            \
            ಸ್ಥಿರಾಂಕ uint8_t sve_dst_chn_idx = 1;                            \
            (ಶೂನ್ಯ)sve_src_chn_idx;                                        \
            (ಶೂನ್ಯ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ಮೂಲ_u16 = svget4((ma_ಮೂಲ_u16x4), 2);     \
            svuint16_t sve_ಗುರಿ_u16 = svget3((ma_ಗುರಿ_u16x3), 1);     \
            (ಶೂನ್ಯ)sve_ಮೂಲ_u16;                                         \
            (ಶೂನ್ಯ)sve_ಗುರಿ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ಗುರಿ_u16x3 = svset3(ma_ಗುರಿ_u16x3, 1, sve_ಗುರಿ_u16); \
        } ಆಗ (0);                                                      \
        ಮಾಡು {                                                              \
            ಸ್ಥಿರಾಂಕ uint8_t sve_src_chn_idx = 3;                            \
            ಸ್ಥಿರಾಂಕ uint8_t sve_dst_chn_idx = 2;                            \
            (ಶೂನ್ಯ)sve_src_chn_idx;                                        \
            (ಶೂನ್ಯ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ಮೂಲ_u16 = svget4((ma_ಮೂಲ_u16x4), 3);     \
            svuint16_t sve_ಗುರಿ_u16 = svget3((ma_ಗುರಿ_u16x3), 2);     \
            (ಶೂನ್ಯ)sve_ಮೂಲ_u16;                                         \
            (ಶೂನ್ಯ)sve_ಗುರಿ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ಗುರಿ_u16x3 = svset3(ma_ಗುರಿ_u16x3, 2, sve_ಗುರಿ_u16); \
        } ಆಗ (0);                                                      \
    } ಆಗ (0)

#ವ್ಯಾಖ್ಯಾನಿಸು sdl_sve_pixel_u16x4_foreach_chn_bgra_rgb565(ma_ಮೂಲ_u16x4,      \
                                                    ma_ಗುರಿ_u16x3,      \
                                                    ...)                  \
    ಮಾಡು {                                                                  \
        svuint16x4_t sve_ಮೂಲ_u16x4 = ma_ಮೂಲ_u16x4;                  \
        (ಶೂನ್ಯ)sve_ಮೂಲ_u16x4;                                           \
        ಮಾಡು {                                                              \
            ಸ್ಥಿರಾಂಕ uint8_t sve_src_chn_idx = 3;                            \
            ಸ್ಥಿರಾಂಕ uint8_t sve_dst_chn_idx = 0;                            \
            (ಶೂನ್ಯ)sve_src_chn_idx;                                        \
            (ಶೂನ್ಯ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ಮೂಲ_u16 = svget4((ma_ಮೂಲ_u16x4), 3);     \
            svuint16_t sve_ಗುರಿ_u16 = svget3((ma_ಗುರಿ_u16x3), 0);     \
            (ಶೂನ್ಯ)sve_ಮೂಲ_u16;                                         \
            (ಶೂನ್ಯ)sve_ಗುರಿ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ಗುರಿ_u16x3 = svset3(ma_ಗುರಿ_u16x3, 0, sve_ಗುರಿ_u16); \
        } ಆಗ (0);                                                      \
        ಮಾಡು {                                                              \
            ಸ್ಥಿರಾಂಕ uint8_t sve_src_chn_idx = 2;                            \
            ಸ್ಥಿರಾಂಕ uint8_t sve_dst_chn_idx = 1;                            \
            (ಶೂನ್ಯ)sve_src_chn_idx;                                        \
            (ಶೂನ್ಯ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ಮೂಲ_u16 = svget4((ma_ಮೂಲ_u16x4), 2);     \
            svuint16_t sve_ಗುರಿ_u16 = svget3((ma_ಗುರಿ_u16x3), 1);     \
            (ಶೂನ್ಯ)sve_ಮೂಲ_u16;                                         \
            (ಶೂನ್ಯ)sve_ಗುರಿ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ಗುರಿ_u16x3 = svset3(ma_ಗುರಿ_u16x3, 1, sve_ಗುರಿ_u16); \
        } ಆಗ (0);                                                      \
        ಮಾಡು {                                                              \
            ಸ್ಥಿರಾಂಕ uint8_t sve_src_chn_idx = 1;                            \
            ಸ್ಥಿರಾಂಕ uint8_t sve_dst_chn_idx = 2;                            \
            (ಶೂನ್ಯ)sve_src_chn_idx;                                        \
            (ಶೂನ್ಯ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ಮೂಲ_u16 = svget4((ma_ಮೂಲ_u16x4), 1);     \
            svuint16_t sve_ಗುರಿ_u16 = svget3((ma_ಗುರಿ_u16x3), 2);     \
            (ಶೂನ್ಯ)sve_ಮೂಲ_u16;                                         \
            (ಶೂನ್ಯ)sve_ಗುರಿ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ಗುರಿ_u16x3 = svset3(ma_ಗುರಿ_u16x3, 2, sve_ಗುರಿ_u16); \
        } ಆಗ (0);                                                      \
    } ಆಗ (0)

#ವ್ಯಾಖ್ಯಾನಿಸು sdl_sve_pixel_u16x4_foreach_chn_abgr_rgb565(ma_ಮೂಲ_u16x4,      \
                                                    ma_ಗುರಿ_u16x3,      \
                                                    ...)                  \
    ಮಾಡು {                                                                  \
        svuint16x4_t sve_ಮೂಲ_u16x4 = ma_ಮೂಲ_u16x4;                  \
        (ಶೂನ್ಯ)sve_ಮೂಲ_u16x4;                                           \
        ಮಾಡು {                                                              \
            ಸ್ಥಿರಾಂಕ uint8_t sve_src_chn_idx = 2;                            \
            ಸ್ಥಿರಾಂಕ uint8_t sve_dst_chn_idx = 0;                            \
            (ಶೂನ್ಯ)sve_src_chn_idx;                                        \
            (ಶೂನ್ಯ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ಮೂಲ_u16 = svget4((ma_ಮೂಲ_u16x4), 2);     \
            svuint16_t sve_ಗುರಿ_u16 = svget3((ma_ಗುರಿ_u16x3), 0);     \
            (ಶೂನ್ಯ)sve_ಮೂಲ_u16;                                         \
            (ಶೂನ್ಯ)sve_ಗುರಿ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ಗುರಿ_u16x3 = svset3(ma_ಗುರಿ_u16x3, 0, sve_ಗುರಿ_u16); \
        } ಆಗ (0);                                                      \
        ಮಾಡು {                                                              \
            ಸ್ಥಿರಾಂಕ uint8_t sve_src_chn_idx = 1;                            \
            ಸ್ಥಿರಾಂಕ uint8_t sve_dst_chn_idx = 1;                            \
            (ಶೂನ್ಯ)sve_src_chn_idx;                                        \
            (ಶೂನ್ಯ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ಮೂಲ_u16 = svget4((ma_ಮೂಲ_u16x4), 1);     \
            svuint16_t sve_ಗುರಿ_u16 = svget3((ma_ಗುರಿ_u16x3), 1);     \
            (ಶೂನ್ಯ)sve_ಮೂಲ_u16;                                         \
            (ಶೂನ್ಯ)sve_ಗುರಿ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ಗುರಿ_u16x3 = svset3(ma_ಗುರಿ_u16x3, 1, sve_ಗುರಿ_u16); \
        } ಆಗ (0);                                                      \
        ಮಾಡು {                                                              \
            ಸ್ಥಿರಾಂಕ uint8_t sve_src_chn_idx = 0;                            \
            ಸ್ಥಿರಾಂಕ uint8_t sve_dst_chn_idx = 2;                            \
            (ಶೂನ್ಯ)sve_src_chn_idx;                                        \
            (ಶೂನ್ಯ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ಮೂಲ_u16 = svget4((ma_ಮೂಲ_u16x4), 0);     \
            svuint16_t sve_ಗುರಿ_u16 = svget3((ma_ಗುರಿ_u16x3), 2);     \
            (ಶೂನ್ಯ)sve_ಮೂಲ_u16;                                         \
            (ಶೂನ್ಯ)sve_ಗುರಿ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ಗುರಿ_u16x3 = svset3(ma_ಗುರಿ_u16x3, 2, sve_ಗುರಿ_u16); \
        } ಆಗ (0);                                                      \
    } ಆಗ (0)

SDL_TARGETING("arch=armv8-a+sve2")
ಸ್ಥಿರ ಸಾಲೊಳಗೆ svuint16x3_t sdl_sve_rgb565_unpack(svuint16_t vPixels)
{
    svuint16_t vBlue = svand_n_u16_m(svptrue_b16(), vPixels, 0x1F);
    svuint16_t vGreen = svand_n_u16_m(svptrue_b16(), vPixels, (0x3F << 5));
    svuint16_t vRed = svand_n_u16_m(svptrue_b16(), vPixels, (0x1F << 11));

    ಹಿಂತಿರುಗಿ svcreate3_u16(svlsl_n_u16_m(svptrue_b16(), vBlue, 3),
                         svlsr_n_u16_m(svptrue_b16(), vGreen, 3),
                         svlsr_n_u16_m(svptrue_b16(), vRed, 8));
}

SDL_TARGETING("arch=armv8-a+sve2")
ಸ್ಥಿರ ಸಾಲೊಳಗೆ svuint16_t sdl_sve_rgb565_pack(svuint16x3_t vRGB16x3)
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
    ಹಿಂತಿರುಗಿ svorr_u16_m(svptrue_b16(), vPixel, vBlue);

    // return  (svget3_u16(vRGB16x3, 0) >> 3)
    //     |   ((svget3_u16(vRGB16x3, 1) & (0x3F << 2)) << 3)
    //     |   ((svget3_u16(vRGB16x3, 2) & (0x1F << 3)) << 8);
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(2, 3, 4)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ svld3rgb565_u16(svbool_t vPredu8,
                                   uint16_t *phw_ಮೂಲ,
                                   svuint16x3_t *pv_ಕೆಳಗಿನ,
                                   svuint16x3_t *pv_ಮೇಲಿನ)
{
    svuint8x2_t vInput8x2 = svld2_u8(vPredu8, (uint8_t *)phw_ಮೂಲ);

    svuint16_t v_ಕೆಳಗಿನ_Byte_ಕೆಳಗಿನ_Half = svunpklo_u16(svget2_u8(vInput8x2, 0));
    svuint16_t v_ಕೆಳಗಿನ_Byte_ಮೇಲಿನ_Half = svunpkhi_u16(svget2_u8(vInput8x2, 0));

    svuint16_t v_ಮೇಲಿನ_Byte_ಕೆಳಗಿನ_Half = svunpklo_u16(svget2_u8(vInput8x2, 1));
    svuint16_t v_ಮೇಲಿನ_Byte_ಮೇಲಿನ_Half = svunpkhi_u16(svget2_u8(vInput8x2, 1));

    //*pvLow = sdl_sve_rgb565_unpack  (   vLowByteLowHalf
    //                                |   (vHighByteLowHalf << 8));
    *pv_ಕೆಳಗಿನ = sdl_sve_rgb565_unpack(
        svorr_u16_m(svptrue_b16(),
                    v_ಕೆಳಗಿನ_Byte_ಕೆಳಗಿನ_Half,
                    //(vHighByteLowHalf << 8)
                    svlsl_n_u16_m(svptrue_b16(), v_ಮೇಲಿನ_Byte_ಕೆಳಗಿನ_Half, 8)));

    //*pvHigh = sdl_sve_rgb565_unpack (   vLowByteHighHalf
    //                                |   (vHighByteHighHalf << 8));
    *pv_ಮೇಲಿನ = sdl_sve_rgb565_unpack(
        svorr_u16_m(svptrue_b16(),
                    v_ಕೆಳಗಿನ_Byte_ಮೇಲಿನ_Half,
                    //(vHighByteHighHalf << 8)
                    svlsl_n_u16_m(svptrue_b16(), v_ಮೇಲಿನ_Byte_ಮೇಲಿನ_Half, 8)));
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(2)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ svst3rgb565_u16(svbool_t vPredu8,
                                   uint16_t *phw_ಗುರಿ,
                                   svuint16x3_t v_ಕೆಳಗಿನ,
                                   svuint16x3_t v_ಮೇಲಿನ)
{
    svuint16_t v_ಕೆಳಗಿನ_Byte_ಕೆಳಗಿನ_Half = svundef_u16();
    svuint16_t v_ಮೇಲಿನ_Byte_ಕೆಳಗಿನ_Half = svundef_u16();

    /* pack low half pixels */
    ಮಾಡು {
        svuint16_t vPixel = sdl_sve_rgb565_pack(v_ಕೆಳಗಿನ);

        // vLowByteLowHalf = vPixel & 0xFF;
        v_ಕೆಳಗಿನ_Byte_ಕೆಳಗಿನ_Half = svand_n_u16_m(svptrue_b16(), vPixel, 0xFF);

        // vHighByteLowHalf = vPixel >> 8;
        v_ಮೇಲಿನ_Byte_ಕೆಳಗಿನ_Half = svlsr_n_u16_m(svptrue_b16(), vPixel, 8);
    } ಆಗ (0);

    svuint16_t v_ಕೆಳಗಿನ_Byte_ಮೇಲಿನ_Half = svundef_u16();
    svuint16_t v_ಮೇಲಿನ_Byte_ಮೇಲಿನ_Half = svundef_u16();

    /* pack high half pixels */
    ಮಾಡು {
        svuint16_t vPixel = sdl_sve_rgb565_pack(v_ಮೇಲಿನ);

        // vLowByteHighHalf = vPixel & 0xFF;
        v_ಕೆಳಗಿನ_Byte_ಮೇಲಿನ_Half = svand_n_u16_m(svptrue_b16(), vPixel, 0xFF);

        // vHighByteHighHalf = vPixel >> 8;
        v_ಮೇಲಿನ_Byte_ಮೇಲಿನ_Half = svlsr_n_u16_m(svptrue_b16(), vPixel, 8);
    } ಆಗ (0);

    /* save rgb565 pixels */
    svuint8_t v_ಕೆಳಗಿನ_Byte = svuzp1_u8(svreinterpret_u8(v_ಕೆಳಗಿನ_Byte_ಕೆಳಗಿನ_Half),
                                   svreinterpret_u8(v_ಕೆಳಗಿನ_Byte_ಮೇಲಿನ_Half));

    svuint8_t v_ಮೇಲಿನ_Byte = svuzp1_u8(svreinterpret_u8(v_ಮೇಲಿನ_Byte_ಕೆಳಗಿನ_Half),
                                    svreinterpret_u8(v_ಮೇಲಿನ_Byte_ಮೇಲಿನ_Half));

    svst2_u8(vPredu8, (uint8_t *)phw_ಗುರಿ, svcreate2_u8(v_ಕೆಳಗಿನ_Byte, v_ಮೇಲಿನ_Byte));
}

#ಆದರೆ defined(__GNUC__) && !defined(__clang__)
#ವ್ಯಾಖ್ಯಾನಿಸು svld4ub_u16(ma_pred,                                                                                         \
                    ma_src_ptr,                                                                                      \
                    ma_svuint16x4_ಕೆಳಗಿನ_ptr,                                                                           \
                    ma_svuint16x4_ಮೇಲಿನ_ptr)                                                                          \
    ಮಾಡು {                                                                                                             \
        svuint8x4_t vInput8x4 = svld4_u8((ma_pred), (ma_src_ptr));                                                   \
                                                                                                                     \
        *(ma_svuint16x4_ಕೆಳಗಿನ_ptr) = svset4_u16(*(ma_svuint16x4_ಕೆಳಗಿನ_ptr), 0, svunpklo_u16(svget4_u8(vInput8x4, 0)));   \
        *(ma_svuint16x4_ಕೆಳಗಿನ_ptr) = svset4_u16(*(ma_svuint16x4_ಕೆಳಗಿನ_ptr), 1, svunpklo_u16(svget4_u8(vInput8x4, 1)));   \
        *(ma_svuint16x4_ಕೆಳಗಿನ_ptr) = svset4_u16(*(ma_svuint16x4_ಕೆಳಗಿನ_ptr), 2, svunpklo_u16(svget4_u8(vInput8x4, 2)));   \
        *(ma_svuint16x4_ಕೆಳಗಿನ_ptr) = svset4_u16(*(ma_svuint16x4_ಕೆಳಗಿನ_ptr), 3, svunpklo_u16(svget4_u8(vInput8x4, 3)));   \
                                                                                                                     \
        *(ma_svuint16x4_ಮೇಲಿನ_ptr) = svset4_u16(*(ma_svuint16x4_ಮೇಲಿನ_ptr), 0, svunpkhi_u16(svget4_u8(vInput8x4, 0))); \
        *(ma_svuint16x4_ಮೇಲಿನ_ptr) = svset4_u16(*(ma_svuint16x4_ಮೇಲಿನ_ptr), 1, svunpkhi_u16(svget4_u8(vInput8x4, 1))); \
        *(ma_svuint16x4_ಮೇಲಿನ_ptr) = svset4_u16(*(ma_svuint16x4_ಮೇಲಿನ_ptr), 2, svunpkhi_u16(svget4_u8(vInput8x4, 2))); \
        *(ma_svuint16x4_ಮೇಲಿನ_ptr) = svset4_u16(*(ma_svuint16x4_ಮೇಲಿನ_ptr), 3, svunpkhi_u16(svget4_u8(vInput8x4, 3))); \
    } ಆಗ (0)

#ವ್ಯಾಖ್ಯಾನಿಸು svst4ub_u16(ma_pred,                                                                 \
                    ma_dst_ptr,                                                              \
                    ma_svuint16x4_ಕೆಳಗಿನ,                                                       \
                    ma_svuint16x4_ಮೇಲಿನ)                                                      \
    ಮಾಡು {                                                                                     \
        svuint8_t vCH0u8 = svuzp1_u8(svreinterpret_u8(svget4_u16((ma_svuint16x4_ಕೆಳಗಿನ), 0)),   \
                                     svreinterpret_u8(svget4_u16((ma_svuint16x4_ಮೇಲಿನ), 0))); \
                                                                                             \
        svuint8_t vCH1u8 = svuzp1_u8(svreinterpret_u8(svget4_u16((ma_svuint16x4_ಕೆಳಗಿನ), 1)),   \
                                     svreinterpret_u8(svget4_u16((ma_svuint16x4_ಮೇಲಿನ), 1))); \
                                                                                             \
        svuint8_t vCH2u8 = svuzp1_u8(svreinterpret_u8(svget4_u16((ma_svuint16x4_ಕೆಳಗಿನ), 2)),   \
                                     svreinterpret_u8(svget4_u16((ma_svuint16x4_ಮೇಲಿನ), 2))); \
                                                                                             \
        svuint8_t vCH3u8 = svuzp1_u8(svreinterpret_u8(svget4_u16((ma_svuint16x4_ಕೆಳಗಿನ), 3)),   \
                                     svreinterpret_u8(svget4_u16((ma_svuint16x4_ಮೇಲಿನ), 3))); \
                                                                                             \
        svst4_u8((ma_pred), (ma_dst_ptr), svcreate4_u8(vCH0u8, vCH1u8, vCH2u8, vCH3u8));     \
    } ಆಗ (0)
#ಇಲ್ಲದಿದ್ದರೆ
SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(2, 3, 4)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ svld4ub_u16(svbool_t vPredu8,
                               uint8_t *pch_ಮೂಲ,
                               svuint16x4_t *pv_ಕೆಳಗಿನ,
                               svuint16x4_t *pv_ಮೇಲಿನ)
{
    svuint8x4_t vInput8x4 = svld4_u8(vPredu8, pch_ಮೂಲ);

    *pv_ಕೆಳಗಿನ = svset4_u16(*pv_ಕೆಳಗಿನ, 0, svunpklo_u16(svget4_u8(vInput8x4, 0)));
    *pv_ಕೆಳಗಿನ = svset4_u16(*pv_ಕೆಳಗಿನ, 1, svunpklo_u16(svget4_u8(vInput8x4, 1)));
    *pv_ಕೆಳಗಿನ = svset4_u16(*pv_ಕೆಳಗಿನ, 2, svunpklo_u16(svget4_u8(vInput8x4, 2)));
    *pv_ಕೆಳಗಿನ = svset4_u16(*pv_ಕೆಳಗಿನ, 3, svunpklo_u16(svget4_u8(vInput8x4, 3)));

    *pv_ಮೇಲಿನ = svset4_u16(*pv_ಮೇಲಿನ, 0, svunpkhi_u16(svget4_u8(vInput8x4, 0)));
    *pv_ಮೇಲಿನ = svset4_u16(*pv_ಮೇಲಿನ, 1, svunpkhi_u16(svget4_u8(vInput8x4, 1)));
    *pv_ಮೇಲಿನ = svset4_u16(*pv_ಮೇಲಿನ, 2, svunpkhi_u16(svget4_u8(vInput8x4, 2)));
    *pv_ಮೇಲಿನ = svset4_u16(*pv_ಮೇಲಿನ, 3, svunpkhi_u16(svget4_u8(vInput8x4, 3)));
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(2)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ svst4ub_u16(svbool_t vPredu8,
                               uint8_t *pch_ಗುರಿ,
                               svuint16x4_t v_ಕೆಳಗಿನ,
                               svuint16x4_t v_ಮೇಲಿನ)
{

    svuint8_t vCH0u8 = svuzp1_u8(svreinterpret_u8(svget4_u16(v_ಕೆಳಗಿನ, 0)),
                                 svreinterpret_u8(svget4_u16(v_ಮೇಲಿನ, 0)));

    svuint8_t vCH1u8 = svuzp1_u8(svreinterpret_u8(svget4_u16(v_ಕೆಳಗಿನ, 1)),
                                 svreinterpret_u8(svget4_u16(v_ಮೇಲಿನ, 1)));

    svuint8_t vCH2u8 = svuzp1_u8(svreinterpret_u8(svget4_u16(v_ಕೆಳಗಿನ, 2)),
                                 svreinterpret_u8(svget4_u16(v_ಮೇಲಿನ, 2)));

    svuint8_t vCH3u8 = svuzp1_u8(svreinterpret_u8(svget4_u16(v_ಕೆಳಗಿನ, 3)),
                                 svreinterpret_u8(svget4_u16(v_ಮೇಲಿನ, 3)));

    svst4_u8(vPredu8, pch_ಗುರಿ, svcreate4_u8(vCH0u8, vCH1u8, vCH2u8, vCH3u8));
}
#ಆದರೆ_ಅಂತ್ಯ

/*! \note the Element range of vMask is [0, 0xFF]
 */
SDL_TARGETING("arch=armv8-a+sve2")
ಸ್ಥಿರ ಸಾಲೊಳಗೆ svuint16_t sdl_sve_chn_blend_with_ಮುಖವಾಡ(svuint16_t v_ಮೂಲ,
                                                     svuint16_t v_ಗುರಿ,
                                                     svuint16_t v_ಮುಖವಾಡ)
{
    // vTarget = vSource * vMask + vTarget * (255 - vMask);
    svuint16_t vTemp0 = svdup_u16(1);
    vTemp0 = svmla_u16_m(svptrue_b16(), vTemp0, v_ಮೂಲ, v_ಮುಖವಾಡ);
    vTemp0 = svmla_u16_m(svptrue_b16(),
                         vTemp0,
                         v_ಗುರಿ,
                         svsub_u16_m(svptrue_b16(),
                                     svdup_u16(255),
                                     v_ಮುಖವಾಡ));

    /* x += x >> 8 */
    ಹಿಂತಿರುಗಿ svreinterpret_u16_u8(
        svaddhnb_u16(vTemp0,
                     svlsr_n_u16_m(svptrue_b16(),
                                   vTemp0,
                                   8)));
}
/*! \note the Element range of vMask is [0, 0xFF]
 */
SDL_TARGETING("arch=armv8-a+sve2")
ಸ್ಥಿರ ಸಾಲೊಳಗೆ svuint16_t sdl_sve_chn_blend_with_ಮುಖವಾಡ_fast(svuint16_t v_ಮೂಲ,
                                                          svuint16_t v_ಗುರಿ,
                                                          svuint16_t v_ಮುಖವಾಡ)
{
    // vTarget = vSource * vMask + vTarget * (255 - vMask);
    svuint16_t vTemp0 = svmul_u16_m(svptrue_b16(), v_ಮೂಲ, v_ಮುಖವಾಡ);
    vTemp0 = svmla_u16_m(svptrue_b16(),
                         vTemp0,
                         v_ಗುರಿ,
                         svsub_u16_m(svptrue_b16(),
                                     svdup_u16(255),
                                     v_ಮುಖವಾಡ));

    ಹಿಂತಿರುಗಿ svlsr_n_u16_m(svptrue_b16(), vTemp0, 8); // vTarget >> 8;
}

/*! \note the hwOpacity range [0, 0x100]
 */
SDL_TARGETING("arch=armv8-a+sve2")
ಸ್ಥಿರ ಸಾಲೊಳಗೆ svuint16_t sdl_sve_chn_blend_with_opacity(svuint16_t v_ಮೂಲ,
                                                        svuint16_t v_ಗುರಿ,
                                                        uint16_t hwOpacity)
{
    // svuint16_t vOpacity = svdup_u16(hwOpacity);
    // vTarget = vSource * vOpacity + vTarget * (256 - vOpacity);

    svuint16_t vTemp0 = svmul_n_u16_m(svptrue_b16(), v_ಮೂಲ, hwOpacity);
    svuint16_t vTemp1 = svmul_n_u16_m(svptrue_b16(),
                                      v_ಗುರಿ,
                                      256 - hwOpacity);
    v_ಗುರಿ = svadd_u16_m(svptrue_b16(), vTemp0, vTemp1);

    ಹಿಂತಿರುಗಿ svlsr_n_u16_m(svptrue_b16(), v_ಗುರಿ, 8); // vTarget >> 8;
}

/*! \note the hwOpacity range [0, 0x100]
 */
SDL_TARGETING("arch=armv8-a+sve2")
ಸ್ಥಿರ ಸಾಲೊಳಗೆ svuint16_t sdl_sve_chn_blend_with_opacity_fast(svuint16_t v_ಮೂಲ,
                                                             svuint16_t v_ಗುರಿ,
                                                             uint16_t hwOpacity)
{
    // vTarget = vSource * vMask + vTarget * (255 - vMask);
    svuint16_t vTemp0 = svmul_n_u16_m(svptrue_b16(), v_ಮೂಲ, hwOpacity);
    vTemp0 = svmla_n_u16_m(svptrue_b16(),
                           vTemp0,
                           v_ಗುರಿ,
                           256 - hwOpacity);

    ಹಿಂತಿರುಗಿ svlsr_n_u16_m(svptrue_b16(), vTemp0, 8); // vTarget >> 8;
}

/*! \note the Element range of vMask is [0, 0xFF]
 *  \note the hwOpacity range [0, 0x100]
 */
SDL_TARGETING("arch=armv8-a+sve2")
ಸ್ಥಿರ ಸಾಲೊಳಗೆ svuint16_t sdl_sve_chn_blend_with_ಮುಖವಾಡ_and_opacity(svuint16_t v_ಮೂಲ,
                                                                 svuint16_t v_ಗುರಿ,
                                                                 svuint16_t v_ಮುಖವಾಡ,
                                                                 uint16_t hwOpacity)
{
    v_ಮುಖವಾಡ = svsel(svcmpeq_n_u16(svptrue_b16(), v_ಮುಖವಾಡ, 255),
                  svdup_u16(hwOpacity),
                  //(vMask * hwOpacity) >> 8,
                  svlsr_n_u16_m(svptrue_b16(),
                                svmul_n_u16_m(svptrue_b16(), v_ಮುಖವಾಡ, hwOpacity),
                                8));

    // vTarget = vSource * vMask + vTarget * (256 - vMask);
    svuint16_t vTemp0 = svmul_u16_m(svptrue_b16(), v_ಮೂಲ, v_ಮುಖವಾಡ);
    svuint16_t vTemp1 = svmul_u16_m(svptrue_b16(),
                                    v_ಗುರಿ,
                                    svsub_u16_m(svptrue_b16(),
                                                svdup_u16(256),
                                                v_ಮುಖವಾಡ));
    v_ಗುರಿ = svadd_u16_m(svptrue_b16(), vTemp0, vTemp1);

    ಹಿಂತಿರುಗಿ svlsr_n_u16_m(svptrue_b16(), v_ಗುರಿ, 8); // vTarget >> 8;
}

/*! \note the Element range of vMask0/1 is [0, 0xFF]
 */
SDL_TARGETING("arch=armv8-a+sve2")
ಸ್ಥಿರ ಸಾಲೊಳಗೆ svuint16_t sdl_sve_chn_blend_with_masks(svuint16_t v_ಮೂಲ,
                                                      svuint16_t v_ಗುರಿ,
                                                      svuint16_t vMask0,
                                                      svuint16_t vMask1)
{
    vMask1 = svadd_u16_m(svcmpeq_n_u16(svptrue_b16(), vMask1, 255),
                         vMask1,
                         svdup_u16(1));

    svuint16_t v_ಮುಖವಾಡ =
        svsel(svcmpge_n_u16(svptrue_b16(), vMask0, 255),
              vMask1,
              //(vMask0 * vMask1) >> 8,
              svlsr_n_u16_m(svptrue_b16(),
                            svmul_u16_m(svptrue_b16(), vMask0, vMask1),
                            8));

    // vTarget = vSource * vMask + vTarget * (256 - vMask);
    svuint16_t vTemp0 = svmul_u16_m(svptrue_b16(), v_ಮೂಲ, v_ಮುಖವಾಡ);
    svuint16_t vTemp1 = svmul_u16_m(svptrue_b16(),
                                    v_ಗುರಿ,
                                    svsub_u16_m(svptrue_b16(),
                                                svdup_u16(256),
                                                v_ಮುಖವಾಡ));
    v_ಗುರಿ = svadd_u16_m(svptrue_b16(), vTemp0, vTemp1);

    ಹಿಂತಿರುಗಿ svlsr_n_u16_m(svptrue_b16(), v_ಗುರಿ, 8); // vTarget >> 8;
}

/*! \note the Element range of vMask0/1 is [0, 0xFF]
 *  \note the hwOpacity range [0, 0x100]
 */
SDL_TARGETING("arch=armv8-a+sve2")
ಸ್ಥಿರ ಸಾಲೊಳಗೆ svuint16_t sdl_sve_chn_blend_with_masks_and_opacity(
    svuint16_t v_ಮೂಲ,
    svuint16_t v_ಗುರಿ,
    svuint16_t vMask0,
    svuint16_t vMask1,
    uint16_t hwOpacity)
{
    vMask0 = svadd_u16_m(svcmpeq_n_u16(svptrue_b16(), vMask0, 255),
                         vMask0,
                         svdup_u16(1));

    svuint16_t v_ಮುಖವಾಡ =
        svsel(svcmpge_n_u16(svptrue_b16(), vMask1, 255), /* >= 255 */
              vMask0,
              //(vMask0 * vMask1) >> 8
              svlsr_n_u16_m(svptrue_b16(),
                            svmul_u16_m(svptrue_b16(), vMask0, vMask1),
                            8));

    v_ಮುಖವಾಡ =
        svsel(svcmpge_n_u16(svptrue_b16(), v_ಮುಖವಾಡ, 255),
              svdup_u16(hwOpacity),
              //(vMask * hwOpacity) >> 8,
              svlsr_n_u16_m(svptrue_b16(),
                            svmul_n_u16_m(svptrue_b16(), v_ಮುಖವಾಡ, hwOpacity),
                            8));

    // vTarget = vSource * vMask + vTarget * (256 - vMask);
    svuint16_t vTemp0 = svmul_u16_m(svptrue_b16(), v_ಮೂಲ, v_ಮುಖವಾಡ);
    svuint16_t vTemp1 = svmul_u16_m(svptrue_b16(),
                                    v_ಗುರಿ,
                                    svsub_u16_m(svptrue_b16(),
                                                svdup_u16(256),
                                                v_ಮುಖವಾಡ));
    v_ಗುರಿ = svadd_u16_m(svptrue_b16(), vTemp0, vTemp1);

    ಹಿಂತಿರುಗಿ svlsr_n_u16_m(svptrue_b16(), v_ಗುರಿ, 8); // vTarget >> 8;
}

/*! \note the Element range of vMask0/1 is [0, 0xFF]
 */
SDL_TARGETING("arch=armv8-a+sve2")
ಸ್ಥಿರ ಸಾಲೊಳಗೆ svuint16_t sdl_sve_chn_blend_with_3masks(svuint16_t v_ಮೂಲ,
                                                       svuint16_t v_ಗುರಿ,
                                                       svuint16_t vMask0,
                                                       svuint16_t vMask1,
                                                       svuint16_t vMask2)
{
    vMask0 = svadd_u16_m(svcmpeq_n_u16(svptrue_b16(), vMask0, 255),
                         vMask0,
                         svdup_u16(1));

    svuint16_t v_ಮುಖವಾಡ =
        svsel(svcmpge_n_u16(svptrue_b16(), vMask1, 255),
              vMask0,
              //(vMask0 * vMask1) >> 8
              svlsr_n_u16_m(svptrue_b16(),
                            svmul_u16_m(svptrue_b16(), vMask0, vMask1),
                            8));

    v_ಮುಖವಾಡ =
        svsel(svcmpge_n_u16(svptrue_b16(), vMask2, 255),
              v_ಮುಖವಾಡ,
              //(vMask * vMask2) >> 8
              svlsr_n_u16_m(svptrue_b16(),
                            svmul_u16_m(svptrue_b16(), v_ಮುಖವಾಡ, vMask2),
                            8));

    // vTarget = vSource * vMask + vTarget * (256 - vMask);
    svuint16_t vTemp0 = svmul_u16_m(svptrue_b16(), v_ಮೂಲ, v_ಮುಖವಾಡ);
    svuint16_t vTemp1 = svmul_u16_m(svptrue_b16(),
                                    v_ಗುರಿ,
                                    svsub_u16_m(svptrue_b16(),
                                                svdup_u16(256),
                                                v_ಮುಖವಾಡ));
    v_ಗುರಿ = svadd_u16_m(svptrue_b16(), vTemp0, vTemp1);

    ಹಿಂತಿರುಗಿ svlsr_n_u16_m(svptrue_b16(), v_ಗುರಿ, 8); // vTarget >> 8;
}

/*! \note the Element range of vMask0/1 is [0, 0xFF]
 *  \note the hwOpacity range [0, 0x100]
 */
SDL_TARGETING("arch=armv8-a+sve2")
ಸ್ಥಿರ ಸಾಲೊಳಗೆ svuint16_t sdl_sve_chn_blend_with_3masks_and_opacity(
    svuint16_t v_ಮೂಲ,
    svuint16_t v_ಗುರಿ,
    svuint16_t vMask0,
    svuint16_t vMask1,
    svuint16_t vMask2,
    uint16_t hwOpacity)
{
    vMask0 = svadd_u16_m(svcmpeq_n_u16(svptrue_b16(), vMask0, 255),
                         vMask0,
                         svdup_u16(1));

    svuint16_t v_ಮುಖವಾಡ =
        svsel(svcmpge_n_u16(svptrue_b16(), vMask1, 255),
              vMask0,
              //(vMask0 * vMask1) >> 8
              svlsr_n_u16_m(svptrue_b16(),
                            svmul_u16_m(svptrue_b16(), vMask0, vMask1),
                            8));

    v_ಮುಖವಾಡ =
        svsel(svcmpge_n_u16(svptrue_b16(), vMask2, 255),
              v_ಮುಖವಾಡ,
              svlsr_n_u16_m(svptrue_b16(),
                            svmul_u16_m(svptrue_b16(), v_ಮುಖವಾಡ, vMask2),
                            8));
    //(vMask * vMask2) >> 8);

    v_ಮುಖವಾಡ =
        svsel(svcmpge_n_u16(svptrue_b16(), v_ಮುಖವಾಡ, 255),
              svdup_u16(hwOpacity),
              //(vMask * hwOpacity) >> 8
              svlsr_n_u16_m(svptrue_b16(),
                            svmul_n_u16_m(svptrue_b16(), v_ಮುಖವಾಡ, hwOpacity),
                            8));

    // vTarget = vSource * vMask + vTarget * (256 - vMask);
    svuint16_t vTemp0 = svmul_u16_m(svptrue_b16(), v_ಮೂಲ, v_ಮುಖವಾಡ);
    svuint16_t vTemp1 = svmul_u16_m(svptrue_b16(),
                                    v_ಗುರಿ,
                                    svsub_u16_m(svptrue_b16(),
                                                svdup_u16(256),
                                                v_ಮುಖವಾಡ));
    v_ಗುರಿ = svadd_u16_m(svptrue_b16(), vTemp0, vTemp1);

    ಹಿಂತಿರುಗಿ svlsr_n_u16_m(svptrue_b16(), v_ಗುರಿ, 8); // vTarget >> 8;
}

#ಆದರೆ_ಅಂತ್ಯ /* SDL_SVE2_EXTENSION_H */