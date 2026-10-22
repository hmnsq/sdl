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

#अगर !defined(SDL_SVE2_EXTENSION_H) //&& (defined(__ARM_FEATURE_SVE2) && __ARM_FEATURE_SVE2)
#घोषणा SDL_SVE2_EXTENSION_H

#समावेश "SDL_sve2_util.h"

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
#अगर_घोषित SDL_PLATFORM_ANDROID
#अगर_अघोषित __ARM_FEATURE_SVE
#घोषणा __ARM_FEATURE_SVE 1
#पूर्ण_अगर
#पूर्ण_अगर
#समावेश <arm_sve.h>
#समावेश <stdint.h>

/*!
 * \brief a wrapper for __attribute__((nonnull))
 */
#अगर_अघोषित ARM_NONNULL
#घोषणा ARM_NONNULL(...) __attribute__((nonnull(__VA_ARGS__)))
#पूर्ण_अगर

#घोषणा svlenu8()  svcntb_pat(SV_ALL)
#घोषणा svlenu16() (svcntb_pat(SV_ALL) / माप(uint16_t))
#घोषणा svlenu32() (svcntb_pat(SV_ALL) / माप(uint32_t))
#घोषणा svlenu64() (svcntb_pat(SV_ALL) / माप(uint64_t))

#घोषणा svlens8()  svlenu8()
#घोषणा svlens16() svlenu16()
#घोषणा svlens32() svlenu32()
#घोषणा svlens64() svlenu64()

#घोषणा sdl_sve_stride_loop_pixel(ma_stride_आकार, ma_pred_name)          \
    क्रम (svbool_t ma_pred_name, *p_अस्थायी = &ma_pred_name;                  \
         p_अस्थायी != शून्य;                                                  \
         p_अस्थायी = शून्य)                                                   \
        क्रम (माप_प्रकार SVE_SAFE_NAME(n) = 0,                                \
                    sve_iteration_advance = svlenu8();                   \
             ({                                                          \
                 ma_pred_name = svwhilelt_b8((int32_t)SVE_SAFE_NAME(n),  \
                                             (int32_t)(ma_stride_आकार)); \
                 SVE_SAFE_NAME(n) < (ma_stride_आकार);                    \
             });                                                         \
             SVE_SAFE_NAME(n) += sve_iteration_advance)

#घोषणा sdl_sve_stride_loop_u8 sdl_sve_stride_loop_pixel

#घोषणा sdl_sve_stride_loop_u16(ma_stride_आकार, ma_pred_name)             \
    क्रम (svbool_t ma_pred_name, *p_अस्थायी = &ma_pred_name;                   \
         p_अस्थायी != शून्य;                                                   \
         p_अस्थायी = शून्य)                                                    \
        क्रम (माप_प्रकार SVE_SAFE_NAME(n) = 0,                                 \
                    sve_iteration_advance = svlenu16();                   \
             ({                                                           \
                 ma_pred_name = svwhilelt_b16((int32_t)SVE_SAFE_NAME(n),  \
                                              (int32_t)(ma_stride_आकार)); \
                 SVE_SAFE_NAME(n) < (ma_stride_आकार);                     \
             });                                                          \
             SVE_SAFE_NAME(n) += sve_iteration_advance)

#घोषणा sdl_sve_stride_loop_u32(ma_stride_आकार, ma_pred_name)             \
    क्रम (svbool_t ma_pred_name, *p_अस्थायी = &ma_pred_name;                   \
         p_अस्थायी != शून्य;                                                   \
         p_अस्थायी = शून्य)                                                    \
        क्रम (माप_प्रकार SVE_SAFE_NAME(n) = 0,                                 \
                    sve_iteration_advance = svlenu32();                   \
             ({                                                           \
                 ma_pred_name = svwhilelt_b16((int32_t)SVE_SAFE_NAME(n),  \
                                              (int32_t)(ma_stride_आकार)); \
                 SVE_SAFE_NAME(n) < (ma_stride_आकार);                     \
             });                                                          \
             SVE_SAFE_NAME(n) += sve_iteration_advance)

#घोषणा sdl_sve_pixel_ccc_foreach_chn(ma_source_u16x3,                    \
                                      ma_target_u16x3,                    \
                                      ...)                                \
    करो {                                                                  \
        svuint16x3_t sve_source_u16x3 = ma_source_u16x3;                  \
        (व्योम)sve_source_u16x3;                                           \
        करो {                                                              \
            स्थिर uint8_t sve_src_chn_idx = 0;                            \
            (व्योम)sve_src_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget3((ma_source_u16x3), 0);     \
            svuint16_t sve_target_u16 = svget3((ma_target_u16x3), 0);     \
            (व्योम)sve_source_u16;                                         \
            (व्योम)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x3 = svset3(ma_target_u16x3, 0, sve_target_u16); \
        } जबतक (0);                                                      \
        करो {                                                              \
            स्थिर uint8_t sve_src_chn_idx = 1;                            \
            (व्योम)sve_src_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget3((ma_source_u16x3), 1);     \
            svuint16_t sve_target_u16 = svget3((ma_target_u16x3), 1);     \
            (व्योम)sve_source_u16;                                         \
            (व्योम)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x3 = svset3(ma_target_u16x3, 1, sve_target_u16); \
        } जबतक (0);                                                      \
        करो {                                                              \
            स्थिर uint8_t sve_src_chn_idx = 2;                            \
            (व्योम)sve_src_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget3((ma_source_u16x3), 2);     \
            svuint16_t sve_target_u16 = svget3((ma_target_u16x3), 2);     \
            (व्योम)sve_source_u16;                                         \
            (व्योम)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x3 = svset3(ma_target_u16x3, 2, sve_target_u16); \
        } जबतक (0);                                                      \
    } जबतक (0)

#घोषणा sdl_sve_pixel_accc_foreach_chn012(ma_source_u16x4,                \
                                          ma_target_u16x4,                \
                                          ...)                            \
    करो {                                                                  \
        svuint16x4_t sve_source_u16x4 = ma_source_u16x4;                  \
        (व्योम)sve_source_u16x4;                                           \
        करो {                                                              \
            स्थिर uint8_t sve_src_chn_idx = 0;                            \
            (व्योम)sve_src_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 0);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 0);     \
            (व्योम)sve_source_u16;                                         \
            (व्योम)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 0, sve_target_u16); \
        } जबतक (0);                                                      \
        करो {                                                              \
            स्थिर uint8_t sve_src_chn_idx = 1;                            \
            (व्योम)sve_src_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 1);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 1);     \
            (व्योम)sve_source_u16;                                         \
            (व्योम)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 1, sve_target_u16); \
        } जबतक (0);                                                      \
        करो {                                                              \
            स्थिर uint8_t sve_src_chn_idx = 2;                            \
            (व्योम)sve_src_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 2);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 2);     \
            (व्योम)sve_source_u16;                                         \
            (व्योम)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 2, sve_target_u16); \
        } जबतक (0);                                                      \
    } जबतक (0)

#घोषणा sdl_sve_pixel_accc_foreach_chn(ma_source_u16x4,                   \
                                       ma_target_u16x4,                   \
                                       ...)                               \
    करो {                                                                  \
        svuint16x4_t sve_source_u16x4 = ma_source_u16x4;                  \
        (व्योम)sve_source_u16x4;                                           \
        करो {                                                              \
            स्थिर uint8_t sve_src_chn_idx = 0;                            \
            (व्योम)sve_src_chn_idx;                                        \
            (व्योम)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 0);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 0);     \
            (व्योम)sve_source_u16;                                         \
            (व्योम)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 0, sve_target_u16); \
        } जबतक (0);                                                      \
        करो {                                                              \
            स्थिर uint8_t sve_src_chn_idx = 1;                            \
            (व्योम)sve_src_chn_idx;                                        \
            (व्योम)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 1);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 1);     \
            (व्योम)sve_source_u16;                                         \
            (व्योम)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 1, sve_target_u16); \
        } जबतक (0);                                                      \
        करो {                                                              \
            स्थिर uint8_t sve_src_chn_idx = 2;                            \
            (व्योम)sve_src_chn_idx;                                        \
            (व्योम)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 2);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 2);     \
            (व्योम)sve_source_u16;                                         \
            (व्योम)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 2, sve_target_u16); \
        } जबतक (0);                                                      \
        करो {                                                              \
            स्थिर uint8_t sve_src_chn_idx = 3;                            \
            (व्योम)sve_src_chn_idx;                                        \
            (व्योम)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 3);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 3);     \
            (व्योम)sve_source_u16;                                         \
            (व्योम)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 3, sve_target_u16); \
        } जबतक (0);                                                      \
    } जबतक (0)

#घोषणा sdl_sve_pixel_u16x4_foreach_chn(ma_source_u16x4,                  \
                                        ma_target_u16x4,                  \
                                        ...)                              \
    करो {                                                                  \
        svuint16x4_t sve_source_u16x4 = ma_source_u16x4;                  \
        (व्योम)sve_source_u16x4;                                           \
        करो {                                                              \
            स्थिर uint8_t sve_src_chn_idx = 0;                            \
            (व्योम)sve_src_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 0);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 0);     \
            (व्योम)sve_source_u16;                                         \
            (व्योम)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 0, sve_target_u16); \
        } जबतक (0);                                                      \
        करो {                                                              \
            स्थिर uint8_t sve_src_chn_idx = 1;                            \
            (व्योम)sve_src_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 1);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 1);     \
            (व्योम)sve_source_u16;                                         \
            (व्योम)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 1, sve_target_u16); \
        } जबतक (0);                                                      \
        करो {                                                              \
            स्थिर uint8_t sve_src_chn_idx = 2;                            \
            (व्योम)sve_src_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 2);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 2);     \
            (व्योम)sve_source_u16;                                         \
            (व्योम)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 2, sve_target_u16); \
        } जबतक (0);                                                      \
        करो {                                                              \
            स्थिर uint8_t sve_src_chn_idx = 3;                            \
            (व्योम)sve_src_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 3);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 3);     \
            (व्योम)sve_source_u16;                                         \
            (व्योम)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 3, sve_target_u16); \
        } जबतक (0);                                                      \
    } जबतक (0)

#घोषणा sdl_sve_pixel_u16x4_foreach_chn_src_dst_rev(ma_source_u16x4,      \
                                                    ma_target_u16x4,      \
                                                    ...)                  \
    करो {                                                                  \
        svuint16x4_t sve_source_u16x4 = ma_source_u16x4;                  \
        (व्योम)sve_source_u16x4;                                           \
        करो {                                                              \
            स्थिर uint8_t sve_src_chn_idx = 0;                            \
            स्थिर uint8_t sve_dst_chn_idx = 3;                            \
            (व्योम)sve_src_chn_idx;                                        \
            (व्योम)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 0);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 3);     \
            (व्योम)sve_source_u16;                                         \
            (व्योम)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 3, sve_target_u16); \
        } जबतक (0);                                                      \
        करो {                                                              \
            स्थिर uint8_t sve_src_chn_idx = 1;                            \
            स्थिर uint8_t sve_dst_chn_idx = 2;                            \
            (व्योम)sve_src_chn_idx;                                        \
            (व्योम)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 1);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 2);     \
            (व्योम)sve_source_u16;                                         \
            (व्योम)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 2, sve_target_u16); \
        } जबतक (0);                                                      \
        करो {                                                              \
            स्थिर uint8_t sve_src_chn_idx = 2;                            \
            स्थिर uint8_t sve_dst_chn_idx = 1;                            \
            (व्योम)sve_src_chn_idx;                                        \
            (व्योम)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 2);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 1);     \
            (व्योम)sve_source_u16;                                         \
            (व्योम)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 1, sve_target_u16); \
        } जबतक (0);                                                      \
        करो {                                                              \
            स्थिर uint8_t sve_src_chn_idx = 3;                            \
            स्थिर uint8_t sve_dst_chn_idx = 0;                            \
            (व्योम)sve_src_chn_idx;                                        \
            (व्योम)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 3);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 0);     \
            (व्योम)sve_source_u16;                                         \
            (व्योम)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 0, sve_target_u16); \
        } जबतक (0);                                                      \
    } जबतक (0)

#घोषणा sdl_sve_pixel_u16x4_foreach_chn_accc_ccca(ma_source_u16x4,        \
                                                  ma_target_u16x4,        \
                                                  ...)                    \
    करो {                                                                  \
        svuint16x4_t sve_source_u16x4 = ma_source_u16x4;                  \
        (व्योम)sve_source_u16x4;                                           \
        करो {                                                              \
            स्थिर uint8_t sve_src_chn_idx = 0;                            \
            स्थिर uint8_t sve_dst_chn_idx = 1;                            \
            (व्योम)sve_src_chn_idx;                                        \
            (व्योम)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 0);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 1);     \
            (व्योम)sve_source_u16;                                         \
            (व्योम)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 1, sve_target_u16); \
        } जबतक (0);                                                      \
        करो {                                                              \
            स्थिर uint8_t sve_src_chn_idx = 1;                            \
            स्थिर uint8_t sve_dst_chn_idx = 2;                            \
            (व्योम)sve_src_chn_idx;                                        \
            (व्योम)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 1);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 2);     \
            (व्योम)sve_source_u16;                                         \
            (व्योम)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 2, sve_target_u16); \
        } जबतक (0);                                                      \
        करो {                                                              \
            स्थिर uint8_t sve_src_chn_idx = 2;                            \
            स्थिर uint8_t sve_dst_chn_idx = 3;                            \
            (व्योम)sve_src_chn_idx;                                        \
            (व्योम)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 2);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 3);     \
            (व्योम)sve_source_u16;                                         \
            (व्योम)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 3, sve_target_u16); \
        } जबतक (0);                                                      \
        करो {                                                              \
            स्थिर uint8_t sve_src_chn_idx = 3;                            \
            स्थिर uint8_t sve_dst_chn_idx = 0;                            \
            (व्योम)sve_src_chn_idx;                                        \
            (व्योम)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 3);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 0);     \
            (व्योम)sve_source_u16;                                         \
            (व्योम)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 0, sve_target_u16); \
        } जबतक (0);                                                      \
    } जबतक (0)

#घोषणा sdl_sve_pixel_u16x4_foreach_chn_ccca_accc(ma_source_u16x4,        \
                                                  ma_target_u16x4,        \
                                                  ...)                    \
    करो {                                                                  \
        svuint16x4_t sve_source_u16x4 = ma_source_u16x4;                  \
        (व्योम)sve_source_u16x4;                                           \
        करो {                                                              \
            स्थिर uint8_t sve_src_chn_idx = 1;                            \
            स्थिर uint8_t sve_dst_chn_idx = 0;                            \
            (व्योम)sve_src_chn_idx;                                        \
            (व्योम)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 1);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 0);     \
            (व्योम)sve_source_u16;                                         \
            (व्योम)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 0, sve_target_u16); \
        } जबतक (0);                                                      \
        करो {                                                              \
            स्थिर uint8_t sve_src_chn_idx = 2;                            \
            स्थिर uint8_t sve_dst_chn_idx = 1;                            \
            (व्योम)sve_src_chn_idx;                                        \
            (व्योम)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 2);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 1);     \
            (व्योम)sve_source_u16;                                         \
            (व्योम)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 1, sve_target_u16); \
        } जबतक (0);                                                      \
        करो {                                                              \
            स्थिर uint8_t sve_src_chn_idx = 3;                            \
            स्थिर uint8_t sve_dst_chn_idx = 2;                            \
            (व्योम)sve_src_chn_idx;                                        \
            (व्योम)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 3);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 2);     \
            (व्योम)sve_source_u16;                                         \
            (व्योम)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 2, sve_target_u16); \
        } जबतक (0);                                                      \
        करो {                                                              \
            स्थिर uint8_t sve_src_chn_idx = 0;                            \
            स्थिर uint8_t sve_dst_chn_idx = 3;                            \
            (व्योम)sve_src_chn_idx;                                        \
            (व्योम)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 0);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 3);     \
            (व्योम)sve_source_u16;                                         \
            (व्योम)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 3, sve_target_u16); \
        } जबतक (0);                                                      \
    } जबतक (0)

#घोषणा sdl_sve_pixel_u16x4_foreach_chn_a123_a321(ma_source_u16x4,        \
                                                  ma_target_u16x4,        \
                                                  ...)                    \
    करो {                                                                  \
        svuint16x4_t sve_source_u16x4 = ma_source_u16x4;                  \
        (व्योम)sve_source_u16x4;                                           \
        करो {                                                              \
            स्थिर uint8_t sve_src_chn_idx = 0;                            \
            स्थिर uint8_t sve_dst_chn_idx = 2;                            \
            (व्योम)sve_src_chn_idx;                                        \
            (व्योम)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 0);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 2);     \
            (व्योम)sve_source_u16;                                         \
            (व्योम)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 2, sve_target_u16); \
        } जबतक (0);                                                      \
        करो {                                                              \
            स्थिर uint8_t sve_src_chn_idx = 1;                            \
            स्थिर uint8_t sve_dst_chn_idx = 1;                            \
            (व्योम)sve_src_chn_idx;                                        \
            (व्योम)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 1);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 1);     \
            (व्योम)sve_source_u16;                                         \
            (व्योम)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 1, sve_target_u16); \
        } जबतक (0);                                                      \
        करो {                                                              \
            स्थिर uint8_t sve_src_chn_idx = 2;                            \
            स्थिर uint8_t sve_dst_chn_idx = 0;                            \
            (व्योम)sve_src_chn_idx;                                        \
            (व्योम)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 2);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 0);     \
            (व्योम)sve_source_u16;                                         \
            (व्योम)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 0, sve_target_u16); \
        } जबतक (0);                                                      \
        करो {                                                              \
            स्थिर uint8_t sve_src_chn_idx = 3;                            \
            स्थिर uint8_t sve_dst_chn_idx = 3;                            \
            (व्योम)sve_src_chn_idx;                                        \
            (व्योम)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 3);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 3);     \
            (व्योम)sve_source_u16;                                         \
            (व्योम)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 3, sve_target_u16); \
        } जबतक (0);                                                      \
    } जबतक (0)

#घोषणा sdl_sve_pixel_u16x4_foreach_chn_123a_321a(ma_source_u16x4,        \
                                                  ma_target_u16x4,        \
                                                  ...)                    \
    करो {                                                                  \
        svuint16x4_t sve_source_u16x4 = ma_source_u16x4;                  \
        (व्योम)sve_source_u16x4;                                           \
        करो {                                                              \
            स्थिर uint8_t sve_src_chn_idx = 0;                            \
            स्थिर uint8_t sve_dst_chn_idx = 0;                            \
            (व्योम)sve_src_chn_idx;                                        \
            (व्योम)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 0);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 0);     \
            (व्योम)sve_source_u16;                                         \
            (व्योम)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 0, sve_target_u16); \
        } जबतक (0);                                                      \
        करो {                                                              \
            स्थिर uint8_t sve_src_chn_idx = 1;                            \
            स्थिर uint8_t sve_dst_chn_idx = 3;                            \
            (व्योम)sve_src_chn_idx;                                        \
            (व्योम)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 1);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 3);     \
            (व्योम)sve_source_u16;                                         \
            (व्योम)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 3, sve_target_u16); \
        } जबतक (0);                                                      \
        करो {                                                              \
            स्थिर uint8_t sve_src_chn_idx = 2;                            \
            स्थिर uint8_t sve_dst_chn_idx = 2;                            \
            (व्योम)sve_src_chn_idx;                                        \
            (व्योम)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 2);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 2);     \
            (व्योम)sve_source_u16;                                         \
            (व्योम)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 2, sve_target_u16); \
        } जबतक (0);                                                      \
        करो {                                                              \
            स्थिर uint8_t sve_src_chn_idx = 3;                            \
            स्थिर uint8_t sve_dst_chn_idx = 1;                            \
            (व्योम)sve_src_chn_idx;                                        \
            (व्योम)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 3);     \
            svuint16_t sve_target_u16 = svget4((ma_target_u16x4), 1);     \
            (व्योम)sve_source_u16;                                         \
            (व्योम)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x4 = svset4(ma_target_u16x4, 1, sve_target_u16); \
        } जबतक (0);                                                      \
    } जबतक (0)

#घोषणा sdl_sve_pixel_u16x4_foreach_chn_argb_rgb565(ma_source_u16x4,      \
                                                    ma_target_u16x3,      \
                                                    ...)                  \
    करो {                                                                  \
        svuint16x4_t sve_source_u16x4 = ma_source_u16x4;                  \
        (व्योम)sve_source_u16x4;                                           \
        करो {                                                              \
            स्थिर uint8_t sve_src_chn_idx = 0;                            \
            स्थिर uint8_t sve_dst_chn_idx = 0;                            \
            (व्योम)sve_src_chn_idx;                                        \
            (व्योम)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 0);     \
            svuint16_t sve_target_u16 = svget3((ma_target_u16x3), 0);     \
            (व्योम)sve_source_u16;                                         \
            (व्योम)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x3 = svset3(ma_target_u16x3, 0, sve_target_u16); \
        } जबतक (0);                                                      \
        करो {                                                              \
            स्थिर uint8_t sve_src_chn_idx = 1;                            \
            स्थिर uint8_t sve_dst_chn_idx = 1;                            \
            (व्योम)sve_src_chn_idx;                                        \
            (व्योम)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 1);     \
            svuint16_t sve_target_u16 = svget3((ma_target_u16x3), 1);     \
            (व्योम)sve_source_u16;                                         \
            (व्योम)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x3 = svset3(ma_target_u16x3, 1, sve_target_u16); \
        } जबतक (0);                                                      \
        करो {                                                              \
            स्थिर uint8_t sve_src_chn_idx = 2;                            \
            स्थिर uint8_t sve_dst_chn_idx = 2;                            \
            (व्योम)sve_src_chn_idx;                                        \
            (व्योम)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 2);     \
            svuint16_t sve_target_u16 = svget3((ma_target_u16x3), 2);     \
            (व्योम)sve_source_u16;                                         \
            (व्योम)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x3 = svset3(ma_target_u16x3, 2, sve_target_u16); \
        } जबतक (0);                                                      \
    } जबतक (0)

#घोषणा sdl_sve_pixel_u16x4_foreach_chn_rgba_rgb565(ma_source_u16x4,      \
                                                    ma_target_u16x3,      \
                                                    ...)                  \
    करो {                                                                  \
        svuint16x4_t sve_source_u16x4 = ma_source_u16x4;                  \
        (व्योम)sve_source_u16x4;                                           \
        करो {                                                              \
            स्थिर uint8_t sve_src_chn_idx = 1;                            \
            स्थिर uint8_t sve_dst_chn_idx = 0;                            \
            (व्योम)sve_src_chn_idx;                                        \
            (व्योम)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 1);     \
            svuint16_t sve_target_u16 = svget3((ma_target_u16x3), 0);     \
            (व्योम)sve_source_u16;                                         \
            (व्योम)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x3 = svset3(ma_target_u16x3, 0, sve_target_u16); \
        } जबतक (0);                                                      \
        करो {                                                              \
            स्थिर uint8_t sve_src_chn_idx = 2;                            \
            स्थिर uint8_t sve_dst_chn_idx = 1;                            \
            (व्योम)sve_src_chn_idx;                                        \
            (व्योम)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 2);     \
            svuint16_t sve_target_u16 = svget3((ma_target_u16x3), 1);     \
            (व्योम)sve_source_u16;                                         \
            (व्योम)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x3 = svset3(ma_target_u16x3, 1, sve_target_u16); \
        } जबतक (0);                                                      \
        करो {                                                              \
            स्थिर uint8_t sve_src_chn_idx = 3;                            \
            स्थिर uint8_t sve_dst_chn_idx = 2;                            \
            (व्योम)sve_src_chn_idx;                                        \
            (व्योम)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 3);     \
            svuint16_t sve_target_u16 = svget3((ma_target_u16x3), 2);     \
            (व्योम)sve_source_u16;                                         \
            (व्योम)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x3 = svset3(ma_target_u16x3, 2, sve_target_u16); \
        } जबतक (0);                                                      \
    } जबतक (0)

#घोषणा sdl_sve_pixel_u16x4_foreach_chn_bgra_rgb565(ma_source_u16x4,      \
                                                    ma_target_u16x3,      \
                                                    ...)                  \
    करो {                                                                  \
        svuint16x4_t sve_source_u16x4 = ma_source_u16x4;                  \
        (व्योम)sve_source_u16x4;                                           \
        करो {                                                              \
            स्थिर uint8_t sve_src_chn_idx = 3;                            \
            स्थिर uint8_t sve_dst_chn_idx = 0;                            \
            (व्योम)sve_src_chn_idx;                                        \
            (व्योम)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 3);     \
            svuint16_t sve_target_u16 = svget3((ma_target_u16x3), 0);     \
            (व्योम)sve_source_u16;                                         \
            (व्योम)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x3 = svset3(ma_target_u16x3, 0, sve_target_u16); \
        } जबतक (0);                                                      \
        करो {                                                              \
            स्थिर uint8_t sve_src_chn_idx = 2;                            \
            स्थिर uint8_t sve_dst_chn_idx = 1;                            \
            (व्योम)sve_src_chn_idx;                                        \
            (व्योम)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 2);     \
            svuint16_t sve_target_u16 = svget3((ma_target_u16x3), 1);     \
            (व्योम)sve_source_u16;                                         \
            (व्योम)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x3 = svset3(ma_target_u16x3, 1, sve_target_u16); \
        } जबतक (0);                                                      \
        करो {                                                              \
            स्थिर uint8_t sve_src_chn_idx = 1;                            \
            स्थिर uint8_t sve_dst_chn_idx = 2;                            \
            (व्योम)sve_src_chn_idx;                                        \
            (व्योम)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 1);     \
            svuint16_t sve_target_u16 = svget3((ma_target_u16x3), 2);     \
            (व्योम)sve_source_u16;                                         \
            (व्योम)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x3 = svset3(ma_target_u16x3, 2, sve_target_u16); \
        } जबतक (0);                                                      \
    } जबतक (0)

#घोषणा sdl_sve_pixel_u16x4_foreach_chn_abgr_rgb565(ma_source_u16x4,      \
                                                    ma_target_u16x3,      \
                                                    ...)                  \
    करो {                                                                  \
        svuint16x4_t sve_source_u16x4 = ma_source_u16x4;                  \
        (व्योम)sve_source_u16x4;                                           \
        करो {                                                              \
            स्थिर uint8_t sve_src_chn_idx = 2;                            \
            स्थिर uint8_t sve_dst_chn_idx = 0;                            \
            (व्योम)sve_src_chn_idx;                                        \
            (व्योम)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 2);     \
            svuint16_t sve_target_u16 = svget3((ma_target_u16x3), 0);     \
            (व्योम)sve_source_u16;                                         \
            (व्योम)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x3 = svset3(ma_target_u16x3, 0, sve_target_u16); \
        } जबतक (0);                                                      \
        करो {                                                              \
            स्थिर uint8_t sve_src_chn_idx = 1;                            \
            स्थिर uint8_t sve_dst_chn_idx = 1;                            \
            (व्योम)sve_src_chn_idx;                                        \
            (व्योम)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 1);     \
            svuint16_t sve_target_u16 = svget3((ma_target_u16x3), 1);     \
            (व्योम)sve_source_u16;                                         \
            (व्योम)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x3 = svset3(ma_target_u16x3, 1, sve_target_u16); \
        } जबतक (0);                                                      \
        करो {                                                              \
            स्थिर uint8_t sve_src_chn_idx = 0;                            \
            स्थिर uint8_t sve_dst_chn_idx = 2;                            \
            (व्योम)sve_src_chn_idx;                                        \
            (व्योम)sve_dst_chn_idx;                                        \
            svuint16_t sve_source_u16 = svget4((ma_source_u16x4), 0);     \
            svuint16_t sve_target_u16 = svget3((ma_target_u16x3), 2);     \
            (व्योम)sve_source_u16;                                         \
            (व्योम)sve_target_u16;                                         \
            __VA_ARGS__                                                   \
            ma_target_u16x3 = svset3(ma_target_u16x3, 2, sve_target_u16); \
        } जबतक (0);                                                      \
    } जबतक (0)

SDL_TARGETING("arch=armv8-a+sve2")
अटल अंतरभूत svuint16x3_t sdl_sve_rgb565_unpack(svuint16_t vPixels)
{
    svuint16_t vBlue = svand_n_u16_m(svptrue_b16(), vPixels, 0x1F);
    svuint16_t vGreen = svand_n_u16_m(svptrue_b16(), vPixels, (0x3F << 5));
    svuint16_t vRed = svand_n_u16_m(svptrue_b16(), vPixels, (0x1F << 11));

    वापस svcreate3_u16(svlsl_n_u16_m(svptrue_b16(), vBlue, 3),
                         svlsr_n_u16_m(svptrue_b16(), vGreen, 3),
                         svlsr_n_u16_m(svptrue_b16(), vRed, 8));
}

SDL_TARGETING("arch=armv8-a+sve2")
अटल अंतरभूत svuint16_t sdl_sve_rgb565_pack(svuint16x3_t vRGB16x3)
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
    वापस svorr_u16_m(svptrue_b16(), vPixel, vBlue);

    // return  (svget3_u16(vRGB16x3, 0) >> 3)
    //     |   ((svget3_u16(vRGB16x3, 1) & (0x3F << 2)) << 3)
    //     |   ((svget3_u16(vRGB16x3, 2) & (0x1F << 3)) << 8);
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(2, 3, 4)
अटल अंतरभूत व्योम svld3rgb565_u16(svbool_t vPredu8,
                                   uint16_t *phwSource,
                                   svuint16x3_t *pv_निचला,
                                   svuint16x3_t *pv_ऊपरी)
{
    svuint8x2_t vInput8x2 = svld2_u8(vPredu8, (uint8_t *)phwSource);

    svuint16_t v_निचला_Byte_निचला_Half = svunpklo_u16(svget2_u8(vInput8x2, 0));
    svuint16_t v_निचला_Byte_ऊपरी_Half = svunpkhi_u16(svget2_u8(vInput8x2, 0));

    svuint16_t v_ऊपरी_Byte_निचला_Half = svunpklo_u16(svget2_u8(vInput8x2, 1));
    svuint16_t v_ऊपरी_Byte_ऊपरी_Half = svunpkhi_u16(svget2_u8(vInput8x2, 1));

    //*pvLow = sdl_sve_rgb565_unpack  (   vLowByteLowHalf
    //                                |   (vHighByteLowHalf << 8));
    *pv_निचला = sdl_sve_rgb565_unpack(
        svorr_u16_m(svptrue_b16(),
                    v_निचला_Byte_निचला_Half,
                    //(vHighByteLowHalf << 8)
                    svlsl_n_u16_m(svptrue_b16(), v_ऊपरी_Byte_निचला_Half, 8)));

    //*pvHigh = sdl_sve_rgb565_unpack (   vLowByteHighHalf
    //                                |   (vHighByteHighHalf << 8));
    *pv_ऊपरी = sdl_sve_rgb565_unpack(
        svorr_u16_m(svptrue_b16(),
                    v_निचला_Byte_ऊपरी_Half,
                    //(vHighByteHighHalf << 8)
                    svlsl_n_u16_m(svptrue_b16(), v_ऊपरी_Byte_ऊपरी_Half, 8)));
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(2)
अटल अंतरभूत व्योम svst3rgb565_u16(svbool_t vPredu8,
                                   uint16_t *phwTarget,
                                   svuint16x3_t v_निचला,
                                   svuint16x3_t v_ऊपरी)
{
    svuint16_t v_निचला_Byte_निचला_Half = svundef_u16();
    svuint16_t v_ऊपरी_Byte_निचला_Half = svundef_u16();

    /* pack low half pixels */
    करो {
        svuint16_t vPixel = sdl_sve_rgb565_pack(v_निचला);

        // vLowByteLowHalf = vPixel & 0xFF;
        v_निचला_Byte_निचला_Half = svand_n_u16_m(svptrue_b16(), vPixel, 0xFF);

        // vHighByteLowHalf = vPixel >> 8;
        v_ऊपरी_Byte_निचला_Half = svlsr_n_u16_m(svptrue_b16(), vPixel, 8);
    } जबतक (0);

    svuint16_t v_निचला_Byte_ऊपरी_Half = svundef_u16();
    svuint16_t v_ऊपरी_Byte_ऊपरी_Half = svundef_u16();

    /* pack high half pixels */
    करो {
        svuint16_t vPixel = sdl_sve_rgb565_pack(v_ऊपरी);

        // vLowByteHighHalf = vPixel & 0xFF;
        v_निचला_Byte_ऊपरी_Half = svand_n_u16_m(svptrue_b16(), vPixel, 0xFF);

        // vHighByteHighHalf = vPixel >> 8;
        v_ऊपरी_Byte_ऊपरी_Half = svlsr_n_u16_m(svptrue_b16(), vPixel, 8);
    } जबतक (0);

    /* save rgb565 pixels */
    svuint8_t v_निचला_Byte = svuzp1_u8(svreinterpret_u8(v_निचला_Byte_निचला_Half),
                                   svreinterpret_u8(v_निचला_Byte_ऊपरी_Half));

    svuint8_t v_ऊपरी_Byte = svuzp1_u8(svreinterpret_u8(v_ऊपरी_Byte_निचला_Half),
                                    svreinterpret_u8(v_ऊपरी_Byte_ऊपरी_Half));

    svst2_u8(vPredu8, (uint8_t *)phwTarget, svcreate2_u8(v_निचला_Byte, v_ऊपरी_Byte));
}

#अगर defined(__GNUC__) && !defined(__clang__)
#घोषणा svld4ub_u16(ma_pred,                                                                                         \
                    ma_src_ptr,                                                                                      \
                    ma_svuint16x4_निचला_ptr,                                                                           \
                    ma_svuint16x4_ऊपरी_ptr)                                                                          \
    करो {                                                                                                             \
        svuint8x4_t vInput8x4 = svld4_u8((ma_pred), (ma_src_ptr));                                                   \
                                                                                                                     \
        *(ma_svuint16x4_निचला_ptr) = svset4_u16(*(ma_svuint16x4_निचला_ptr), 0, svunpklo_u16(svget4_u8(vInput8x4, 0)));   \
        *(ma_svuint16x4_निचला_ptr) = svset4_u16(*(ma_svuint16x4_निचला_ptr), 1, svunpklo_u16(svget4_u8(vInput8x4, 1)));   \
        *(ma_svuint16x4_निचला_ptr) = svset4_u16(*(ma_svuint16x4_निचला_ptr), 2, svunpklo_u16(svget4_u8(vInput8x4, 2)));   \
        *(ma_svuint16x4_निचला_ptr) = svset4_u16(*(ma_svuint16x4_निचला_ptr), 3, svunpklo_u16(svget4_u8(vInput8x4, 3)));   \
                                                                                                                     \
        *(ma_svuint16x4_ऊपरी_ptr) = svset4_u16(*(ma_svuint16x4_ऊपरी_ptr), 0, svunpkhi_u16(svget4_u8(vInput8x4, 0))); \
        *(ma_svuint16x4_ऊपरी_ptr) = svset4_u16(*(ma_svuint16x4_ऊपरी_ptr), 1, svunpkhi_u16(svget4_u8(vInput8x4, 1))); \
        *(ma_svuint16x4_ऊपरी_ptr) = svset4_u16(*(ma_svuint16x4_ऊपरी_ptr), 2, svunpkhi_u16(svget4_u8(vInput8x4, 2))); \
        *(ma_svuint16x4_ऊपरी_ptr) = svset4_u16(*(ma_svuint16x4_ऊपरी_ptr), 3, svunpkhi_u16(svget4_u8(vInput8x4, 3))); \
    } जबतक (0)

#घोषणा svst4ub_u16(ma_pred,                                                                 \
                    ma_dst_ptr,                                                              \
                    ma_svuint16x4_निचला,                                                       \
                    ma_svuint16x4_ऊपरी)                                                      \
    करो {                                                                                     \
        svuint8_t vCH0u8 = svuzp1_u8(svreinterpret_u8(svget4_u16((ma_svuint16x4_निचला), 0)),   \
                                     svreinterpret_u8(svget4_u16((ma_svuint16x4_ऊपरी), 0))); \
                                                                                             \
        svuint8_t vCH1u8 = svuzp1_u8(svreinterpret_u8(svget4_u16((ma_svuint16x4_निचला), 1)),   \
                                     svreinterpret_u8(svget4_u16((ma_svuint16x4_ऊपरी), 1))); \
                                                                                             \
        svuint8_t vCH2u8 = svuzp1_u8(svreinterpret_u8(svget4_u16((ma_svuint16x4_निचला), 2)),   \
                                     svreinterpret_u8(svget4_u16((ma_svuint16x4_ऊपरी), 2))); \
                                                                                             \
        svuint8_t vCH3u8 = svuzp1_u8(svreinterpret_u8(svget4_u16((ma_svuint16x4_निचला), 3)),   \
                                     svreinterpret_u8(svget4_u16((ma_svuint16x4_ऊपरी), 3))); \
                                                                                             \
        svst4_u8((ma_pred), (ma_dst_ptr), svcreate4_u8(vCH0u8, vCH1u8, vCH2u8, vCH3u8));     \
    } जबतक (0)
#अन्यथा
SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(2, 3, 4)
अटल अंतरभूत व्योम svld4ub_u16(svbool_t vPredu8,
                               uint8_t *pchSource,
                               svuint16x4_t *pv_निचला,
                               svuint16x4_t *pv_ऊपरी)
{
    svuint8x4_t vInput8x4 = svld4_u8(vPredu8, pchSource);

    *pv_निचला = svset4_u16(*pv_निचला, 0, svunpklo_u16(svget4_u8(vInput8x4, 0)));
    *pv_निचला = svset4_u16(*pv_निचला, 1, svunpklo_u16(svget4_u8(vInput8x4, 1)));
    *pv_निचला = svset4_u16(*pv_निचला, 2, svunpklo_u16(svget4_u8(vInput8x4, 2)));
    *pv_निचला = svset4_u16(*pv_निचला, 3, svunpklo_u16(svget4_u8(vInput8x4, 3)));

    *pv_ऊपरी = svset4_u16(*pv_ऊपरी, 0, svunpkhi_u16(svget4_u8(vInput8x4, 0)));
    *pv_ऊपरी = svset4_u16(*pv_ऊपरी, 1, svunpkhi_u16(svget4_u8(vInput8x4, 1)));
    *pv_ऊपरी = svset4_u16(*pv_ऊपरी, 2, svunpkhi_u16(svget4_u8(vInput8x4, 2)));
    *pv_ऊपरी = svset4_u16(*pv_ऊपरी, 3, svunpkhi_u16(svget4_u8(vInput8x4, 3)));
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(2)
अटल अंतरभूत व्योम svst4ub_u16(svbool_t vPredu8,
                               uint8_t *pchTarget,
                               svuint16x4_t v_निचला,
                               svuint16x4_t v_ऊपरी)
{

    svuint8_t vCH0u8 = svuzp1_u8(svreinterpret_u8(svget4_u16(v_निचला, 0)),
                                 svreinterpret_u8(svget4_u16(v_ऊपरी, 0)));

    svuint8_t vCH1u8 = svuzp1_u8(svreinterpret_u8(svget4_u16(v_निचला, 1)),
                                 svreinterpret_u8(svget4_u16(v_ऊपरी, 1)));

    svuint8_t vCH2u8 = svuzp1_u8(svreinterpret_u8(svget4_u16(v_निचला, 2)),
                                 svreinterpret_u8(svget4_u16(v_ऊपरी, 2)));

    svuint8_t vCH3u8 = svuzp1_u8(svreinterpret_u8(svget4_u16(v_निचला, 3)),
                                 svreinterpret_u8(svget4_u16(v_ऊपरी, 3)));

    svst4_u8(vPredu8, pchTarget, svcreate4_u8(vCH0u8, vCH1u8, vCH2u8, vCH3u8));
}
#पूर्ण_अगर

/*! \note the Element range of vMask is [0, 0xFF]
 */
SDL_TARGETING("arch=armv8-a+sve2")
अटल अंतरभूत svuint16_t sdl_sve_chn_blend_with_mask(svuint16_t vSource,
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
    वापस svreinterpret_u16_u8(
        svaddhnb_u16(vTemp0,
                     svlsr_n_u16_m(svptrue_b16(),
                                   vTemp0,
                                   8)));
}
/*! \note the Element range of vMask is [0, 0xFF]
 */
SDL_TARGETING("arch=armv8-a+sve2")
अटल अंतरभूत svuint16_t sdl_sve_chn_blend_with_mask_fast(svuint16_t vSource,
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

    वापस svlsr_n_u16_m(svptrue_b16(), vTemp0, 8); // vTarget >> 8;
}

/*! \note the hwOpacity range [0, 0x100]
 */
SDL_TARGETING("arch=armv8-a+sve2")
अटल अंतरभूत svuint16_t sdl_sve_chn_blend_with_opacity(svuint16_t vSource,
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

    वापस svlsr_n_u16_m(svptrue_b16(), vTarget, 8); // vTarget >> 8;
}

/*! \note the hwOpacity range [0, 0x100]
 */
SDL_TARGETING("arch=armv8-a+sve2")
अटल अंतरभूत svuint16_t sdl_sve_chn_blend_with_opacity_fast(svuint16_t vSource,
                                                             svuint16_t vTarget,
                                                             uint16_t hwOpacity)
{
    // vTarget = vSource * vMask + vTarget * (255 - vMask);
    svuint16_t vTemp0 = svmul_n_u16_m(svptrue_b16(), vSource, hwOpacity);
    vTemp0 = svmla_n_u16_m(svptrue_b16(),
                           vTemp0,
                           vTarget,
                           256 - hwOpacity);

    वापस svlsr_n_u16_m(svptrue_b16(), vTemp0, 8); // vTarget >> 8;
}

/*! \note the Element range of vMask is [0, 0xFF]
 *  \note the hwOpacity range [0, 0x100]
 */
SDL_TARGETING("arch=armv8-a+sve2")
अटल अंतरभूत svuint16_t sdl_sve_chn_blend_with_mask_and_opacity(svuint16_t vSource,
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

    वापस svlsr_n_u16_m(svptrue_b16(), vTarget, 8); // vTarget >> 8;
}

/*! \note the Element range of vMask0/1 is [0, 0xFF]
 */
SDL_TARGETING("arch=armv8-a+sve2")
अटल अंतरभूत svuint16_t sdl_sve_chn_blend_with_masks(svuint16_t vSource,
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

    वापस svlsr_n_u16_m(svptrue_b16(), vTarget, 8); // vTarget >> 8;
}

/*! \note the Element range of vMask0/1 is [0, 0xFF]
 *  \note the hwOpacity range [0, 0x100]
 */
SDL_TARGETING("arch=armv8-a+sve2")
अटल अंतरभूत svuint16_t sdl_sve_chn_blend_with_masks_and_opacity(
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

    वापस svlsr_n_u16_m(svptrue_b16(), vTarget, 8); // vTarget >> 8;
}

/*! \note the Element range of vMask0/1 is [0, 0xFF]
 */
SDL_TARGETING("arch=armv8-a+sve2")
अटल अंतरभूत svuint16_t sdl_sve_chn_blend_with_3masks(svuint16_t vSource,
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

    वापस svlsr_n_u16_m(svptrue_b16(), vTarget, 8); // vTarget >> 8;
}

/*! \note the Element range of vMask0/1 is [0, 0xFF]
 *  \note the hwOpacity range [0, 0x100]
 */
SDL_TARGETING("arch=armv8-a+sve2")
अटल अंतरभूत svuint16_t sdl_sve_chn_blend_with_3masks_and_opacity(
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

    वापस svlsr_n_u16_m(svptrue_b16(), vTarget, 8); // vTarget >> 8;
}

#पूर्ण_अगर /* SDL_SVE2_EXTENSION_H */