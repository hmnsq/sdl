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

#ਜੇ !defined(SDL_SVE2_EXTENSION_H) //&& (defined(__ARM_FEATURE_SVE2) && __ARM_FEATURE_SVE2)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_SVE2_EXTENSION_H

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_sve2_util.h"

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
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_PLATFORM_ANDROID
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ __ARM_FEATURE_SVE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ __ARM_FEATURE_SVE 1
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ
#ਅਨ੍ਤਰ੍ਭਾਵ <arm_sve.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>

/*!
 * \brief a wrapper for __attribute__((nonnull))
 */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ ARM_NONNULL
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ARM_NONNULL(...) __attribute__((nonnull(__VA_ARGS__)))
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ svlenu8()  svcntb_pat(SV_ALL)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ svlenu16() (svcntb_pat(SV_ALL) / ਆਕਾਰ(uint16_t))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ svlenu32() (svcntb_pat(SV_ALL) / ਆਕਾਰ(uint32_t))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ svlenu64() (svcntb_pat(SV_ALL) / ਆਕਾਰ(uint64_t))

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ svlens8()  svlenu8()
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ svlens16() svlenu16()
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ svlens32() svlenu32()
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ svlens64() svlenu64()

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ sdl_sve_stride_loop_pixel(ma_stride_ਮਾਪ, ma_pred_name)          \
    ਲਈ (svbool_t ma_pred_name, *p_ਆਰਜ਼ੀ = &ma_pred_name;                  \
         p_ਆਰਜ਼ੀ != ਨਿਰਾ;                                                  \
         p_ਆਰਜ਼ੀ = ਨਿਰਾ)                                                   \
        ਲਈ (size_t SVE_ਸੁਰੱਖਿਅਤ_NAME(n) = 0,                                \
                    sve_iteration_advance = svlenu8();                   \
             ({                                                          \
                 ma_pred_name = svwhilelt_b8((int32_t)SVE_ਸੁਰੱਖਿਅਤ_NAME(n),  \
                                             (int32_t)(ma_stride_ਮਾਪ)); \
                 SVE_ਸੁਰੱਖਿਅਤ_NAME(n) < (ma_stride_ਮਾਪ);                    \
             });                                                         \
             SVE_ਸੁਰੱਖਿਅਤ_NAME(n) += sve_iteration_advance)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ sdl_sve_stride_loop_u8 sdl_sve_stride_loop_pixel

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ sdl_sve_stride_loop_u16(ma_stride_ਮਾਪ, ma_pred_name)             \
    ਲਈ (svbool_t ma_pred_name, *p_ਆਰਜ਼ੀ = &ma_pred_name;                   \
         p_ਆਰਜ਼ੀ != ਨਿਰਾ;                                                   \
         p_ਆਰਜ਼ੀ = ਨਿਰਾ)                                                    \
        ਲਈ (size_t SVE_ਸੁਰੱਖਿਅਤ_NAME(n) = 0,                                 \
                    sve_iteration_advance = svlenu16();                   \
             ({                                                           \
                 ma_pred_name = svwhilelt_b16((int32_t)SVE_ਸੁਰੱਖਿਅਤ_NAME(n),  \
                                              (int32_t)(ma_stride_ਮਾਪ)); \
                 SVE_ਸੁਰੱਖਿਅਤ_NAME(n) < (ma_stride_ਮਾਪ);                     \
             });                                                          \
             SVE_ਸੁਰੱਖਿਅਤ_NAME(n) += sve_iteration_advance)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ sdl_sve_stride_loop_u32(ma_stride_ਮਾਪ, ma_pred_name)             \
    ਲਈ (svbool_t ma_pred_name, *p_ਆਰਜ਼ੀ = &ma_pred_name;                   \
         p_ਆਰਜ਼ੀ != ਨਿਰਾ;                                                   \
         p_ਆਰਜ਼ੀ = ਨਿਰਾ)                                                    \
        ਲਈ (size_t SVE_ਸੁਰੱਖਿਅਤ_NAME(n) = 0,                                 \
                    sve_iteration_advance = svlenu32();                   \
             ({                                                           \
                 ma_pred_name = svwhilelt_b16((int32_t)SVE_ਸੁਰੱਖਿਅਤ_NAME(n),  \
                                              (int32_t)(ma_stride_ਮਾਪ)); \
                 SVE_ਸੁਰੱਖਿਅਤ_NAME(n) < (ma_stride_ਮਾਪ);                     \
             });                                                          \
             SVE_ਸੁਰੱਖਿਅਤ_NAME(n) += sve_iteration_advance)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ sdl_sve_pixel_ccc_foreach_chn(ma_ਸਰੋਤ_u16x3,                    \
                                      ma_ਨਿਸ਼ਾਨਾ_u16x3,                    \
                                      ...)                                \
    ਕਰੋ {                                                                  \
        svuint16x3_t sve_ਸਰੋਤ_u16x3 = ma_ਸਰੋਤ_u16x3;                  \
        (ਖਾਲੀ)sve_ਸਰੋਤ_u16x3;                                           \
        ਕਰੋ {                                                              \
            ਅਚਲ uint8_t sve_src_chn_idx = 0;                            \
            (ਖਾਲੀ)sve_src_chn_idx;                                        \
            svuint16_t sve_ਸਰੋਤ_u16 = svget3((ma_ਸਰੋਤ_u16x3), 0);     \
            svuint16_t sve_ਨਿਸ਼ਾਨਾ_u16 = svget3((ma_ਨਿਸ਼ਾਨਾ_u16x3), 0);     \
            (ਖਾਲੀ)sve_ਸਰੋਤ_u16;                                         \
            (ਖਾਲੀ)sve_ਨਿਸ਼ਾਨਾ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ਨਿਸ਼ਾਨਾ_u16x3 = svset3(ma_ਨਿਸ਼ਾਨਾ_u16x3, 0, sve_ਨਿਸ਼ਾਨਾ_u16); \
        } ਜਦੋਂ (0);                                                      \
        ਕਰੋ {                                                              \
            ਅਚਲ uint8_t sve_src_chn_idx = 1;                            \
            (ਖਾਲੀ)sve_src_chn_idx;                                        \
            svuint16_t sve_ਸਰੋਤ_u16 = svget3((ma_ਸਰੋਤ_u16x3), 1);     \
            svuint16_t sve_ਨਿਸ਼ਾਨਾ_u16 = svget3((ma_ਨਿਸ਼ਾਨਾ_u16x3), 1);     \
            (ਖਾਲੀ)sve_ਸਰੋਤ_u16;                                         \
            (ਖਾਲੀ)sve_ਨਿਸ਼ਾਨਾ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ਨਿਸ਼ਾਨਾ_u16x3 = svset3(ma_ਨਿਸ਼ਾਨਾ_u16x3, 1, sve_ਨਿਸ਼ਾਨਾ_u16); \
        } ਜਦੋਂ (0);                                                      \
        ਕਰੋ {                                                              \
            ਅਚਲ uint8_t sve_src_chn_idx = 2;                            \
            (ਖਾਲੀ)sve_src_chn_idx;                                        \
            svuint16_t sve_ਸਰੋਤ_u16 = svget3((ma_ਸਰੋਤ_u16x3), 2);     \
            svuint16_t sve_ਨਿਸ਼ਾਨਾ_u16 = svget3((ma_ਨਿਸ਼ਾਨਾ_u16x3), 2);     \
            (ਖਾਲੀ)sve_ਸਰੋਤ_u16;                                         \
            (ਖਾਲੀ)sve_ਨਿਸ਼ਾਨਾ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ਨਿਸ਼ਾਨਾ_u16x3 = svset3(ma_ਨਿਸ਼ਾਨਾ_u16x3, 2, sve_ਨਿਸ਼ਾਨਾ_u16); \
        } ਜਦੋਂ (0);                                                      \
    } ਜਦੋਂ (0)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ sdl_sve_pixel_accc_foreach_chn012(ma_ਸਰੋਤ_u16x4,                \
                                          ma_ਨਿਸ਼ਾਨਾ_u16x4,                \
                                          ...)                            \
    ਕਰੋ {                                                                  \
        svuint16x4_t sve_ਸਰੋਤ_u16x4 = ma_ਸਰੋਤ_u16x4;                  \
        (ਖਾਲੀ)sve_ਸਰੋਤ_u16x4;                                           \
        ਕਰੋ {                                                              \
            ਅਚਲ uint8_t sve_src_chn_idx = 0;                            \
            (ਖਾਲੀ)sve_src_chn_idx;                                        \
            svuint16_t sve_ਸਰੋਤ_u16 = svget4((ma_ਸਰੋਤ_u16x4), 0);     \
            svuint16_t sve_ਨਿਸ਼ਾਨਾ_u16 = svget4((ma_ਨਿਸ਼ਾਨਾ_u16x4), 0);     \
            (ਖਾਲੀ)sve_ਸਰੋਤ_u16;                                         \
            (ਖਾਲੀ)sve_ਨਿਸ਼ਾਨਾ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ਨਿਸ਼ਾਨਾ_u16x4 = svset4(ma_ਨਿਸ਼ਾਨਾ_u16x4, 0, sve_ਨਿਸ਼ਾਨਾ_u16); \
        } ਜਦੋਂ (0);                                                      \
        ਕਰੋ {                                                              \
            ਅਚਲ uint8_t sve_src_chn_idx = 1;                            \
            (ਖਾਲੀ)sve_src_chn_idx;                                        \
            svuint16_t sve_ਸਰੋਤ_u16 = svget4((ma_ਸਰੋਤ_u16x4), 1);     \
            svuint16_t sve_ਨਿਸ਼ਾਨਾ_u16 = svget4((ma_ਨਿਸ਼ਾਨਾ_u16x4), 1);     \
            (ਖਾਲੀ)sve_ਸਰੋਤ_u16;                                         \
            (ਖਾਲੀ)sve_ਨਿਸ਼ਾਨਾ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ਨਿਸ਼ਾਨਾ_u16x4 = svset4(ma_ਨਿਸ਼ਾਨਾ_u16x4, 1, sve_ਨਿਸ਼ਾਨਾ_u16); \
        } ਜਦੋਂ (0);                                                      \
        ਕਰੋ {                                                              \
            ਅਚਲ uint8_t sve_src_chn_idx = 2;                            \
            (ਖਾਲੀ)sve_src_chn_idx;                                        \
            svuint16_t sve_ਸਰੋਤ_u16 = svget4((ma_ਸਰੋਤ_u16x4), 2);     \
            svuint16_t sve_ਨਿਸ਼ਾਨਾ_u16 = svget4((ma_ਨਿਸ਼ਾਨਾ_u16x4), 2);     \
            (ਖਾਲੀ)sve_ਸਰੋਤ_u16;                                         \
            (ਖਾਲੀ)sve_ਨਿਸ਼ਾਨਾ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ਨਿਸ਼ਾਨਾ_u16x4 = svset4(ma_ਨਿਸ਼ਾਨਾ_u16x4, 2, sve_ਨਿਸ਼ਾਨਾ_u16); \
        } ਜਦੋਂ (0);                                                      \
    } ਜਦੋਂ (0)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ sdl_sve_pixel_accc_foreach_chn(ma_ਸਰੋਤ_u16x4,                   \
                                       ma_ਨਿਸ਼ਾਨਾ_u16x4,                   \
                                       ...)                               \
    ਕਰੋ {                                                                  \
        svuint16x4_t sve_ਸਰੋਤ_u16x4 = ma_ਸਰੋਤ_u16x4;                  \
        (ਖਾਲੀ)sve_ਸਰੋਤ_u16x4;                                           \
        ਕਰੋ {                                                              \
            ਅਚਲ uint8_t sve_src_chn_idx = 0;                            \
            (ਖਾਲੀ)sve_src_chn_idx;                                        \
            (ਖਾਲੀ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ਸਰੋਤ_u16 = svget4((ma_ਸਰੋਤ_u16x4), 0);     \
            svuint16_t sve_ਨਿਸ਼ਾਨਾ_u16 = svget4((ma_ਨਿਸ਼ਾਨਾ_u16x4), 0);     \
            (ਖਾਲੀ)sve_ਸਰੋਤ_u16;                                         \
            (ਖਾਲੀ)sve_ਨਿਸ਼ਾਨਾ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ਨਿਸ਼ਾਨਾ_u16x4 = svset4(ma_ਨਿਸ਼ਾਨਾ_u16x4, 0, sve_ਨਿਸ਼ਾਨਾ_u16); \
        } ਜਦੋਂ (0);                                                      \
        ਕਰੋ {                                                              \
            ਅਚਲ uint8_t sve_src_chn_idx = 1;                            \
            (ਖਾਲੀ)sve_src_chn_idx;                                        \
            (ਖਾਲੀ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ਸਰੋਤ_u16 = svget4((ma_ਸਰੋਤ_u16x4), 1);     \
            svuint16_t sve_ਨਿਸ਼ਾਨਾ_u16 = svget4((ma_ਨਿਸ਼ਾਨਾ_u16x4), 1);     \
            (ਖਾਲੀ)sve_ਸਰੋਤ_u16;                                         \
            (ਖਾਲੀ)sve_ਨਿਸ਼ਾਨਾ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ਨਿਸ਼ਾਨਾ_u16x4 = svset4(ma_ਨਿਸ਼ਾਨਾ_u16x4, 1, sve_ਨਿਸ਼ਾਨਾ_u16); \
        } ਜਦੋਂ (0);                                                      \
        ਕਰੋ {                                                              \
            ਅਚਲ uint8_t sve_src_chn_idx = 2;                            \
            (ਖਾਲੀ)sve_src_chn_idx;                                        \
            (ਖਾਲੀ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ਸਰੋਤ_u16 = svget4((ma_ਸਰੋਤ_u16x4), 2);     \
            svuint16_t sve_ਨਿਸ਼ਾਨਾ_u16 = svget4((ma_ਨਿਸ਼ਾਨਾ_u16x4), 2);     \
            (ਖਾਲੀ)sve_ਸਰੋਤ_u16;                                         \
            (ਖਾਲੀ)sve_ਨਿਸ਼ਾਨਾ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ਨਿਸ਼ਾਨਾ_u16x4 = svset4(ma_ਨਿਸ਼ਾਨਾ_u16x4, 2, sve_ਨਿਸ਼ਾਨਾ_u16); \
        } ਜਦੋਂ (0);                                                      \
        ਕਰੋ {                                                              \
            ਅਚਲ uint8_t sve_src_chn_idx = 3;                            \
            (ਖਾਲੀ)sve_src_chn_idx;                                        \
            (ਖਾਲੀ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ਸਰੋਤ_u16 = svget4((ma_ਸਰੋਤ_u16x4), 3);     \
            svuint16_t sve_ਨਿਸ਼ਾਨਾ_u16 = svget4((ma_ਨਿਸ਼ਾਨਾ_u16x4), 3);     \
            (ਖਾਲੀ)sve_ਸਰੋਤ_u16;                                         \
            (ਖਾਲੀ)sve_ਨਿਸ਼ਾਨਾ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ਨਿਸ਼ਾਨਾ_u16x4 = svset4(ma_ਨਿਸ਼ਾਨਾ_u16x4, 3, sve_ਨਿਸ਼ਾਨਾ_u16); \
        } ਜਦੋਂ (0);                                                      \
    } ਜਦੋਂ (0)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ sdl_sve_pixel_u16x4_foreach_chn(ma_ਸਰੋਤ_u16x4,                  \
                                        ma_ਨਿਸ਼ਾਨਾ_u16x4,                  \
                                        ...)                              \
    ਕਰੋ {                                                                  \
        svuint16x4_t sve_ਸਰੋਤ_u16x4 = ma_ਸਰੋਤ_u16x4;                  \
        (ਖਾਲੀ)sve_ਸਰੋਤ_u16x4;                                           \
        ਕਰੋ {                                                              \
            ਅਚਲ uint8_t sve_src_chn_idx = 0;                            \
            (ਖਾਲੀ)sve_src_chn_idx;                                        \
            svuint16_t sve_ਸਰੋਤ_u16 = svget4((ma_ਸਰੋਤ_u16x4), 0);     \
            svuint16_t sve_ਨਿਸ਼ਾਨਾ_u16 = svget4((ma_ਨਿਸ਼ਾਨਾ_u16x4), 0);     \
            (ਖਾਲੀ)sve_ਸਰੋਤ_u16;                                         \
            (ਖਾਲੀ)sve_ਨਿਸ਼ਾਨਾ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ਨਿਸ਼ਾਨਾ_u16x4 = svset4(ma_ਨਿਸ਼ਾਨਾ_u16x4, 0, sve_ਨਿਸ਼ਾਨਾ_u16); \
        } ਜਦੋਂ (0);                                                      \
        ਕਰੋ {                                                              \
            ਅਚਲ uint8_t sve_src_chn_idx = 1;                            \
            (ਖਾਲੀ)sve_src_chn_idx;                                        \
            svuint16_t sve_ਸਰੋਤ_u16 = svget4((ma_ਸਰੋਤ_u16x4), 1);     \
            svuint16_t sve_ਨਿਸ਼ਾਨਾ_u16 = svget4((ma_ਨਿਸ਼ਾਨਾ_u16x4), 1);     \
            (ਖਾਲੀ)sve_ਸਰੋਤ_u16;                                         \
            (ਖਾਲੀ)sve_ਨਿਸ਼ਾਨਾ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ਨਿਸ਼ਾਨਾ_u16x4 = svset4(ma_ਨਿਸ਼ਾਨਾ_u16x4, 1, sve_ਨਿਸ਼ਾਨਾ_u16); \
        } ਜਦੋਂ (0);                                                      \
        ਕਰੋ {                                                              \
            ਅਚਲ uint8_t sve_src_chn_idx = 2;                            \
            (ਖਾਲੀ)sve_src_chn_idx;                                        \
            svuint16_t sve_ਸਰੋਤ_u16 = svget4((ma_ਸਰੋਤ_u16x4), 2);     \
            svuint16_t sve_ਨਿਸ਼ਾਨਾ_u16 = svget4((ma_ਨਿਸ਼ਾਨਾ_u16x4), 2);     \
            (ਖਾਲੀ)sve_ਸਰੋਤ_u16;                                         \
            (ਖਾਲੀ)sve_ਨਿਸ਼ਾਨਾ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ਨਿਸ਼ਾਨਾ_u16x4 = svset4(ma_ਨਿਸ਼ਾਨਾ_u16x4, 2, sve_ਨਿਸ਼ਾਨਾ_u16); \
        } ਜਦੋਂ (0);                                                      \
        ਕਰੋ {                                                              \
            ਅਚਲ uint8_t sve_src_chn_idx = 3;                            \
            (ਖਾਲੀ)sve_src_chn_idx;                                        \
            svuint16_t sve_ਸਰੋਤ_u16 = svget4((ma_ਸਰੋਤ_u16x4), 3);     \
            svuint16_t sve_ਨਿਸ਼ਾਨਾ_u16 = svget4((ma_ਨਿਸ਼ਾਨਾ_u16x4), 3);     \
            (ਖਾਲੀ)sve_ਸਰੋਤ_u16;                                         \
            (ਖਾਲੀ)sve_ਨਿਸ਼ਾਨਾ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ਨਿਸ਼ਾਨਾ_u16x4 = svset4(ma_ਨਿਸ਼ਾਨਾ_u16x4, 3, sve_ਨਿਸ਼ਾਨਾ_u16); \
        } ਜਦੋਂ (0);                                                      \
    } ਜਦੋਂ (0)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ sdl_sve_pixel_u16x4_foreach_chn_src_dst_rev(ma_ਸਰੋਤ_u16x4,      \
                                                    ma_ਨਿਸ਼ਾਨਾ_u16x4,      \
                                                    ...)                  \
    ਕਰੋ {                                                                  \
        svuint16x4_t sve_ਸਰੋਤ_u16x4 = ma_ਸਰੋਤ_u16x4;                  \
        (ਖਾਲੀ)sve_ਸਰੋਤ_u16x4;                                           \
        ਕਰੋ {                                                              \
            ਅਚਲ uint8_t sve_src_chn_idx = 0;                            \
            ਅਚਲ uint8_t sve_dst_chn_idx = 3;                            \
            (ਖਾਲੀ)sve_src_chn_idx;                                        \
            (ਖਾਲੀ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ਸਰੋਤ_u16 = svget4((ma_ਸਰੋਤ_u16x4), 0);     \
            svuint16_t sve_ਨਿਸ਼ਾਨਾ_u16 = svget4((ma_ਨਿਸ਼ਾਨਾ_u16x4), 3);     \
            (ਖਾਲੀ)sve_ਸਰੋਤ_u16;                                         \
            (ਖਾਲੀ)sve_ਨਿਸ਼ਾਨਾ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ਨਿਸ਼ਾਨਾ_u16x4 = svset4(ma_ਨਿਸ਼ਾਨਾ_u16x4, 3, sve_ਨਿਸ਼ਾਨਾ_u16); \
        } ਜਦੋਂ (0);                                                      \
        ਕਰੋ {                                                              \
            ਅਚਲ uint8_t sve_src_chn_idx = 1;                            \
            ਅਚਲ uint8_t sve_dst_chn_idx = 2;                            \
            (ਖਾਲੀ)sve_src_chn_idx;                                        \
            (ਖਾਲੀ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ਸਰੋਤ_u16 = svget4((ma_ਸਰੋਤ_u16x4), 1);     \
            svuint16_t sve_ਨਿਸ਼ਾਨਾ_u16 = svget4((ma_ਨਿਸ਼ਾਨਾ_u16x4), 2);     \
            (ਖਾਲੀ)sve_ਸਰੋਤ_u16;                                         \
            (ਖਾਲੀ)sve_ਨਿਸ਼ਾਨਾ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ਨਿਸ਼ਾਨਾ_u16x4 = svset4(ma_ਨਿਸ਼ਾਨਾ_u16x4, 2, sve_ਨਿਸ਼ਾਨਾ_u16); \
        } ਜਦੋਂ (0);                                                      \
        ਕਰੋ {                                                              \
            ਅਚਲ uint8_t sve_src_chn_idx = 2;                            \
            ਅਚਲ uint8_t sve_dst_chn_idx = 1;                            \
            (ਖਾਲੀ)sve_src_chn_idx;                                        \
            (ਖਾਲੀ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ਸਰੋਤ_u16 = svget4((ma_ਸਰੋਤ_u16x4), 2);     \
            svuint16_t sve_ਨਿਸ਼ਾਨਾ_u16 = svget4((ma_ਨਿਸ਼ਾਨਾ_u16x4), 1);     \
            (ਖਾਲੀ)sve_ਸਰੋਤ_u16;                                         \
            (ਖਾਲੀ)sve_ਨਿਸ਼ਾਨਾ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ਨਿਸ਼ਾਨਾ_u16x4 = svset4(ma_ਨਿਸ਼ਾਨਾ_u16x4, 1, sve_ਨਿਸ਼ਾਨਾ_u16); \
        } ਜਦੋਂ (0);                                                      \
        ਕਰੋ {                                                              \
            ਅਚਲ uint8_t sve_src_chn_idx = 3;                            \
            ਅਚਲ uint8_t sve_dst_chn_idx = 0;                            \
            (ਖਾਲੀ)sve_src_chn_idx;                                        \
            (ਖਾਲੀ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ਸਰੋਤ_u16 = svget4((ma_ਸਰੋਤ_u16x4), 3);     \
            svuint16_t sve_ਨਿਸ਼ਾਨਾ_u16 = svget4((ma_ਨਿਸ਼ਾਨਾ_u16x4), 0);     \
            (ਖਾਲੀ)sve_ਸਰੋਤ_u16;                                         \
            (ਖਾਲੀ)sve_ਨਿਸ਼ਾਨਾ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ਨਿਸ਼ਾਨਾ_u16x4 = svset4(ma_ਨਿਸ਼ਾਨਾ_u16x4, 0, sve_ਨਿਸ਼ਾਨਾ_u16); \
        } ਜਦੋਂ (0);                                                      \
    } ਜਦੋਂ (0)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ sdl_sve_pixel_u16x4_foreach_chn_accc_ccca(ma_ਸਰੋਤ_u16x4,        \
                                                  ma_ਨਿਸ਼ਾਨਾ_u16x4,        \
                                                  ...)                    \
    ਕਰੋ {                                                                  \
        svuint16x4_t sve_ਸਰੋਤ_u16x4 = ma_ਸਰੋਤ_u16x4;                  \
        (ਖਾਲੀ)sve_ਸਰੋਤ_u16x4;                                           \
        ਕਰੋ {                                                              \
            ਅਚਲ uint8_t sve_src_chn_idx = 0;                            \
            ਅਚਲ uint8_t sve_dst_chn_idx = 1;                            \
            (ਖਾਲੀ)sve_src_chn_idx;                                        \
            (ਖਾਲੀ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ਸਰੋਤ_u16 = svget4((ma_ਸਰੋਤ_u16x4), 0);     \
            svuint16_t sve_ਨਿਸ਼ਾਨਾ_u16 = svget4((ma_ਨਿਸ਼ਾਨਾ_u16x4), 1);     \
            (ਖਾਲੀ)sve_ਸਰੋਤ_u16;                                         \
            (ਖਾਲੀ)sve_ਨਿਸ਼ਾਨਾ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ਨਿਸ਼ਾਨਾ_u16x4 = svset4(ma_ਨਿਸ਼ਾਨਾ_u16x4, 1, sve_ਨਿਸ਼ਾਨਾ_u16); \
        } ਜਦੋਂ (0);                                                      \
        ਕਰੋ {                                                              \
            ਅਚਲ uint8_t sve_src_chn_idx = 1;                            \
            ਅਚਲ uint8_t sve_dst_chn_idx = 2;                            \
            (ਖਾਲੀ)sve_src_chn_idx;                                        \
            (ਖਾਲੀ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ਸਰੋਤ_u16 = svget4((ma_ਸਰੋਤ_u16x4), 1);     \
            svuint16_t sve_ਨਿਸ਼ਾਨਾ_u16 = svget4((ma_ਨਿਸ਼ਾਨਾ_u16x4), 2);     \
            (ਖਾਲੀ)sve_ਸਰੋਤ_u16;                                         \
            (ਖਾਲੀ)sve_ਨਿਸ਼ਾਨਾ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ਨਿਸ਼ਾਨਾ_u16x4 = svset4(ma_ਨਿਸ਼ਾਨਾ_u16x4, 2, sve_ਨਿਸ਼ਾਨਾ_u16); \
        } ਜਦੋਂ (0);                                                      \
        ਕਰੋ {                                                              \
            ਅਚਲ uint8_t sve_src_chn_idx = 2;                            \
            ਅਚਲ uint8_t sve_dst_chn_idx = 3;                            \
            (ਖਾਲੀ)sve_src_chn_idx;                                        \
            (ਖਾਲੀ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ਸਰੋਤ_u16 = svget4((ma_ਸਰੋਤ_u16x4), 2);     \
            svuint16_t sve_ਨਿਸ਼ਾਨਾ_u16 = svget4((ma_ਨਿਸ਼ਾਨਾ_u16x4), 3);     \
            (ਖਾਲੀ)sve_ਸਰੋਤ_u16;                                         \
            (ਖਾਲੀ)sve_ਨਿਸ਼ਾਨਾ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ਨਿਸ਼ਾਨਾ_u16x4 = svset4(ma_ਨਿਸ਼ਾਨਾ_u16x4, 3, sve_ਨਿਸ਼ਾਨਾ_u16); \
        } ਜਦੋਂ (0);                                                      \
        ਕਰੋ {                                                              \
            ਅਚਲ uint8_t sve_src_chn_idx = 3;                            \
            ਅਚਲ uint8_t sve_dst_chn_idx = 0;                            \
            (ਖਾਲੀ)sve_src_chn_idx;                                        \
            (ਖਾਲੀ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ਸਰੋਤ_u16 = svget4((ma_ਸਰੋਤ_u16x4), 3);     \
            svuint16_t sve_ਨਿਸ਼ਾਨਾ_u16 = svget4((ma_ਨਿਸ਼ਾਨਾ_u16x4), 0);     \
            (ਖਾਲੀ)sve_ਸਰੋਤ_u16;                                         \
            (ਖਾਲੀ)sve_ਨਿਸ਼ਾਨਾ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ਨਿਸ਼ਾਨਾ_u16x4 = svset4(ma_ਨਿਸ਼ਾਨਾ_u16x4, 0, sve_ਨਿਸ਼ਾਨਾ_u16); \
        } ਜਦੋਂ (0);                                                      \
    } ਜਦੋਂ (0)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ sdl_sve_pixel_u16x4_foreach_chn_ccca_accc(ma_ਸਰੋਤ_u16x4,        \
                                                  ma_ਨਿਸ਼ਾਨਾ_u16x4,        \
                                                  ...)                    \
    ਕਰੋ {                                                                  \
        svuint16x4_t sve_ਸਰੋਤ_u16x4 = ma_ਸਰੋਤ_u16x4;                  \
        (ਖਾਲੀ)sve_ਸਰੋਤ_u16x4;                                           \
        ਕਰੋ {                                                              \
            ਅਚਲ uint8_t sve_src_chn_idx = 1;                            \
            ਅਚਲ uint8_t sve_dst_chn_idx = 0;                            \
            (ਖਾਲੀ)sve_src_chn_idx;                                        \
            (ਖਾਲੀ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ਸਰੋਤ_u16 = svget4((ma_ਸਰੋਤ_u16x4), 1);     \
            svuint16_t sve_ਨਿਸ਼ਾਨਾ_u16 = svget4((ma_ਨਿਸ਼ਾਨਾ_u16x4), 0);     \
            (ਖਾਲੀ)sve_ਸਰੋਤ_u16;                                         \
            (ਖਾਲੀ)sve_ਨਿਸ਼ਾਨਾ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ਨਿਸ਼ਾਨਾ_u16x4 = svset4(ma_ਨਿਸ਼ਾਨਾ_u16x4, 0, sve_ਨਿਸ਼ਾਨਾ_u16); \
        } ਜਦੋਂ (0);                                                      \
        ਕਰੋ {                                                              \
            ਅਚਲ uint8_t sve_src_chn_idx = 2;                            \
            ਅਚਲ uint8_t sve_dst_chn_idx = 1;                            \
            (ਖਾਲੀ)sve_src_chn_idx;                                        \
            (ਖਾਲੀ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ਸਰੋਤ_u16 = svget4((ma_ਸਰੋਤ_u16x4), 2);     \
            svuint16_t sve_ਨਿਸ਼ਾਨਾ_u16 = svget4((ma_ਨਿਸ਼ਾਨਾ_u16x4), 1);     \
            (ਖਾਲੀ)sve_ਸਰੋਤ_u16;                                         \
            (ਖਾਲੀ)sve_ਨਿਸ਼ਾਨਾ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ਨਿਸ਼ਾਨਾ_u16x4 = svset4(ma_ਨਿਸ਼ਾਨਾ_u16x4, 1, sve_ਨਿਸ਼ਾਨਾ_u16); \
        } ਜਦੋਂ (0);                                                      \
        ਕਰੋ {                                                              \
            ਅਚਲ uint8_t sve_src_chn_idx = 3;                            \
            ਅਚਲ uint8_t sve_dst_chn_idx = 2;                            \
            (ਖਾਲੀ)sve_src_chn_idx;                                        \
            (ਖਾਲੀ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ਸਰੋਤ_u16 = svget4((ma_ਸਰੋਤ_u16x4), 3);     \
            svuint16_t sve_ਨਿਸ਼ਾਨਾ_u16 = svget4((ma_ਨਿਸ਼ਾਨਾ_u16x4), 2);     \
            (ਖਾਲੀ)sve_ਸਰੋਤ_u16;                                         \
            (ਖਾਲੀ)sve_ਨਿਸ਼ਾਨਾ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ਨਿਸ਼ਾਨਾ_u16x4 = svset4(ma_ਨਿਸ਼ਾਨਾ_u16x4, 2, sve_ਨਿਸ਼ਾਨਾ_u16); \
        } ਜਦੋਂ (0);                                                      \
        ਕਰੋ {                                                              \
            ਅਚਲ uint8_t sve_src_chn_idx = 0;                            \
            ਅਚਲ uint8_t sve_dst_chn_idx = 3;                            \
            (ਖਾਲੀ)sve_src_chn_idx;                                        \
            (ਖਾਲੀ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ਸਰੋਤ_u16 = svget4((ma_ਸਰੋਤ_u16x4), 0);     \
            svuint16_t sve_ਨਿਸ਼ਾਨਾ_u16 = svget4((ma_ਨਿਸ਼ਾਨਾ_u16x4), 3);     \
            (ਖਾਲੀ)sve_ਸਰੋਤ_u16;                                         \
            (ਖਾਲੀ)sve_ਨਿਸ਼ਾਨਾ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ਨਿਸ਼ਾਨਾ_u16x4 = svset4(ma_ਨਿਸ਼ਾਨਾ_u16x4, 3, sve_ਨਿਸ਼ਾਨਾ_u16); \
        } ਜਦੋਂ (0);                                                      \
    } ਜਦੋਂ (0)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ sdl_sve_pixel_u16x4_foreach_chn_a123_a321(ma_ਸਰੋਤ_u16x4,        \
                                                  ma_ਨਿਸ਼ਾਨਾ_u16x4,        \
                                                  ...)                    \
    ਕਰੋ {                                                                  \
        svuint16x4_t sve_ਸਰੋਤ_u16x4 = ma_ਸਰੋਤ_u16x4;                  \
        (ਖਾਲੀ)sve_ਸਰੋਤ_u16x4;                                           \
        ਕਰੋ {                                                              \
            ਅਚਲ uint8_t sve_src_chn_idx = 0;                            \
            ਅਚਲ uint8_t sve_dst_chn_idx = 2;                            \
            (ਖਾਲੀ)sve_src_chn_idx;                                        \
            (ਖਾਲੀ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ਸਰੋਤ_u16 = svget4((ma_ਸਰੋਤ_u16x4), 0);     \
            svuint16_t sve_ਨਿਸ਼ਾਨਾ_u16 = svget4((ma_ਨਿਸ਼ਾਨਾ_u16x4), 2);     \
            (ਖਾਲੀ)sve_ਸਰੋਤ_u16;                                         \
            (ਖਾਲੀ)sve_ਨਿਸ਼ਾਨਾ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ਨਿਸ਼ਾਨਾ_u16x4 = svset4(ma_ਨਿਸ਼ਾਨਾ_u16x4, 2, sve_ਨਿਸ਼ਾਨਾ_u16); \
        } ਜਦੋਂ (0);                                                      \
        ਕਰੋ {                                                              \
            ਅਚਲ uint8_t sve_src_chn_idx = 1;                            \
            ਅਚਲ uint8_t sve_dst_chn_idx = 1;                            \
            (ਖਾਲੀ)sve_src_chn_idx;                                        \
            (ਖਾਲੀ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ਸਰੋਤ_u16 = svget4((ma_ਸਰੋਤ_u16x4), 1);     \
            svuint16_t sve_ਨਿਸ਼ਾਨਾ_u16 = svget4((ma_ਨਿਸ਼ਾਨਾ_u16x4), 1);     \
            (ਖਾਲੀ)sve_ਸਰੋਤ_u16;                                         \
            (ਖਾਲੀ)sve_ਨਿਸ਼ਾਨਾ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ਨਿਸ਼ਾਨਾ_u16x4 = svset4(ma_ਨਿਸ਼ਾਨਾ_u16x4, 1, sve_ਨਿਸ਼ਾਨਾ_u16); \
        } ਜਦੋਂ (0);                                                      \
        ਕਰੋ {                                                              \
            ਅਚਲ uint8_t sve_src_chn_idx = 2;                            \
            ਅਚਲ uint8_t sve_dst_chn_idx = 0;                            \
            (ਖਾਲੀ)sve_src_chn_idx;                                        \
            (ਖਾਲੀ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ਸਰੋਤ_u16 = svget4((ma_ਸਰੋਤ_u16x4), 2);     \
            svuint16_t sve_ਨਿਸ਼ਾਨਾ_u16 = svget4((ma_ਨਿਸ਼ਾਨਾ_u16x4), 0);     \
            (ਖਾਲੀ)sve_ਸਰੋਤ_u16;                                         \
            (ਖਾਲੀ)sve_ਨਿਸ਼ਾਨਾ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ਨਿਸ਼ਾਨਾ_u16x4 = svset4(ma_ਨਿਸ਼ਾਨਾ_u16x4, 0, sve_ਨਿਸ਼ਾਨਾ_u16); \
        } ਜਦੋਂ (0);                                                      \
        ਕਰੋ {                                                              \
            ਅਚਲ uint8_t sve_src_chn_idx = 3;                            \
            ਅਚਲ uint8_t sve_dst_chn_idx = 3;                            \
            (ਖਾਲੀ)sve_src_chn_idx;                                        \
            (ਖਾਲੀ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ਸਰੋਤ_u16 = svget4((ma_ਸਰੋਤ_u16x4), 3);     \
            svuint16_t sve_ਨਿਸ਼ਾਨਾ_u16 = svget4((ma_ਨਿਸ਼ਾਨਾ_u16x4), 3);     \
            (ਖਾਲੀ)sve_ਸਰੋਤ_u16;                                         \
            (ਖਾਲੀ)sve_ਨਿਸ਼ਾਨਾ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ਨਿਸ਼ਾਨਾ_u16x4 = svset4(ma_ਨਿਸ਼ਾਨਾ_u16x4, 3, sve_ਨਿਸ਼ਾਨਾ_u16); \
        } ਜਦੋਂ (0);                                                      \
    } ਜਦੋਂ (0)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ sdl_sve_pixel_u16x4_foreach_chn_123a_321a(ma_ਸਰੋਤ_u16x4,        \
                                                  ma_ਨਿਸ਼ਾਨਾ_u16x4,        \
                                                  ...)                    \
    ਕਰੋ {                                                                  \
        svuint16x4_t sve_ਸਰੋਤ_u16x4 = ma_ਸਰੋਤ_u16x4;                  \
        (ਖਾਲੀ)sve_ਸਰੋਤ_u16x4;                                           \
        ਕਰੋ {                                                              \
            ਅਚਲ uint8_t sve_src_chn_idx = 0;                            \
            ਅਚਲ uint8_t sve_dst_chn_idx = 0;                            \
            (ਖਾਲੀ)sve_src_chn_idx;                                        \
            (ਖਾਲੀ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ਸਰੋਤ_u16 = svget4((ma_ਸਰੋਤ_u16x4), 0);     \
            svuint16_t sve_ਨਿਸ਼ਾਨਾ_u16 = svget4((ma_ਨਿਸ਼ਾਨਾ_u16x4), 0);     \
            (ਖਾਲੀ)sve_ਸਰੋਤ_u16;                                         \
            (ਖਾਲੀ)sve_ਨਿਸ਼ਾਨਾ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ਨਿਸ਼ਾਨਾ_u16x4 = svset4(ma_ਨਿਸ਼ਾਨਾ_u16x4, 0, sve_ਨਿਸ਼ਾਨਾ_u16); \
        } ਜਦੋਂ (0);                                                      \
        ਕਰੋ {                                                              \
            ਅਚਲ uint8_t sve_src_chn_idx = 1;                            \
            ਅਚਲ uint8_t sve_dst_chn_idx = 3;                            \
            (ਖਾਲੀ)sve_src_chn_idx;                                        \
            (ਖਾਲੀ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ਸਰੋਤ_u16 = svget4((ma_ਸਰੋਤ_u16x4), 1);     \
            svuint16_t sve_ਨਿਸ਼ਾਨਾ_u16 = svget4((ma_ਨਿਸ਼ਾਨਾ_u16x4), 3);     \
            (ਖਾਲੀ)sve_ਸਰੋਤ_u16;                                         \
            (ਖਾਲੀ)sve_ਨਿਸ਼ਾਨਾ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ਨਿਸ਼ਾਨਾ_u16x4 = svset4(ma_ਨਿਸ਼ਾਨਾ_u16x4, 3, sve_ਨਿਸ਼ਾਨਾ_u16); \
        } ਜਦੋਂ (0);                                                      \
        ਕਰੋ {                                                              \
            ਅਚਲ uint8_t sve_src_chn_idx = 2;                            \
            ਅਚਲ uint8_t sve_dst_chn_idx = 2;                            \
            (ਖਾਲੀ)sve_src_chn_idx;                                        \
            (ਖਾਲੀ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ਸਰੋਤ_u16 = svget4((ma_ਸਰੋਤ_u16x4), 2);     \
            svuint16_t sve_ਨਿਸ਼ਾਨਾ_u16 = svget4((ma_ਨਿਸ਼ਾਨਾ_u16x4), 2);     \
            (ਖਾਲੀ)sve_ਸਰੋਤ_u16;                                         \
            (ਖਾਲੀ)sve_ਨਿਸ਼ਾਨਾ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ਨਿਸ਼ਾਨਾ_u16x4 = svset4(ma_ਨਿਸ਼ਾਨਾ_u16x4, 2, sve_ਨਿਸ਼ਾਨਾ_u16); \
        } ਜਦੋਂ (0);                                                      \
        ਕਰੋ {                                                              \
            ਅਚਲ uint8_t sve_src_chn_idx = 3;                            \
            ਅਚਲ uint8_t sve_dst_chn_idx = 1;                            \
            (ਖਾਲੀ)sve_src_chn_idx;                                        \
            (ਖਾਲੀ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ਸਰੋਤ_u16 = svget4((ma_ਸਰੋਤ_u16x4), 3);     \
            svuint16_t sve_ਨਿਸ਼ਾਨਾ_u16 = svget4((ma_ਨਿਸ਼ਾਨਾ_u16x4), 1);     \
            (ਖਾਲੀ)sve_ਸਰੋਤ_u16;                                         \
            (ਖਾਲੀ)sve_ਨਿਸ਼ਾਨਾ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ਨਿਸ਼ਾਨਾ_u16x4 = svset4(ma_ਨਿਸ਼ਾਨਾ_u16x4, 1, sve_ਨਿਸ਼ਾਨਾ_u16); \
        } ਜਦੋਂ (0);                                                      \
    } ਜਦੋਂ (0)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ sdl_sve_pixel_u16x4_foreach_chn_argb_rgb565(ma_ਸਰੋਤ_u16x4,      \
                                                    ma_ਨਿਸ਼ਾਨਾ_u16x3,      \
                                                    ...)                  \
    ਕਰੋ {                                                                  \
        svuint16x4_t sve_ਸਰੋਤ_u16x4 = ma_ਸਰੋਤ_u16x4;                  \
        (ਖਾਲੀ)sve_ਸਰੋਤ_u16x4;                                           \
        ਕਰੋ {                                                              \
            ਅਚਲ uint8_t sve_src_chn_idx = 0;                            \
            ਅਚਲ uint8_t sve_dst_chn_idx = 0;                            \
            (ਖਾਲੀ)sve_src_chn_idx;                                        \
            (ਖਾਲੀ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ਸਰੋਤ_u16 = svget4((ma_ਸਰੋਤ_u16x4), 0);     \
            svuint16_t sve_ਨਿਸ਼ਾਨਾ_u16 = svget3((ma_ਨਿਸ਼ਾਨਾ_u16x3), 0);     \
            (ਖਾਲੀ)sve_ਸਰੋਤ_u16;                                         \
            (ਖਾਲੀ)sve_ਨਿਸ਼ਾਨਾ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ਨਿਸ਼ਾਨਾ_u16x3 = svset3(ma_ਨਿਸ਼ਾਨਾ_u16x3, 0, sve_ਨਿਸ਼ਾਨਾ_u16); \
        } ਜਦੋਂ (0);                                                      \
        ਕਰੋ {                                                              \
            ਅਚਲ uint8_t sve_src_chn_idx = 1;                            \
            ਅਚਲ uint8_t sve_dst_chn_idx = 1;                            \
            (ਖਾਲੀ)sve_src_chn_idx;                                        \
            (ਖਾਲੀ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ਸਰੋਤ_u16 = svget4((ma_ਸਰੋਤ_u16x4), 1);     \
            svuint16_t sve_ਨਿਸ਼ਾਨਾ_u16 = svget3((ma_ਨਿਸ਼ਾਨਾ_u16x3), 1);     \
            (ਖਾਲੀ)sve_ਸਰੋਤ_u16;                                         \
            (ਖਾਲੀ)sve_ਨਿਸ਼ਾਨਾ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ਨਿਸ਼ਾਨਾ_u16x3 = svset3(ma_ਨਿਸ਼ਾਨਾ_u16x3, 1, sve_ਨਿਸ਼ਾਨਾ_u16); \
        } ਜਦੋਂ (0);                                                      \
        ਕਰੋ {                                                              \
            ਅਚਲ uint8_t sve_src_chn_idx = 2;                            \
            ਅਚਲ uint8_t sve_dst_chn_idx = 2;                            \
            (ਖਾਲੀ)sve_src_chn_idx;                                        \
            (ਖਾਲੀ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ਸਰੋਤ_u16 = svget4((ma_ਸਰੋਤ_u16x4), 2);     \
            svuint16_t sve_ਨਿਸ਼ਾਨਾ_u16 = svget3((ma_ਨਿਸ਼ਾਨਾ_u16x3), 2);     \
            (ਖਾਲੀ)sve_ਸਰੋਤ_u16;                                         \
            (ਖਾਲੀ)sve_ਨਿਸ਼ਾਨਾ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ਨਿਸ਼ਾਨਾ_u16x3 = svset3(ma_ਨਿਸ਼ਾਨਾ_u16x3, 2, sve_ਨਿਸ਼ਾਨਾ_u16); \
        } ਜਦੋਂ (0);                                                      \
    } ਜਦੋਂ (0)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ sdl_sve_pixel_u16x4_foreach_chn_rgba_rgb565(ma_ਸਰੋਤ_u16x4,      \
                                                    ma_ਨਿਸ਼ਾਨਾ_u16x3,      \
                                                    ...)                  \
    ਕਰੋ {                                                                  \
        svuint16x4_t sve_ਸਰੋਤ_u16x4 = ma_ਸਰੋਤ_u16x4;                  \
        (ਖਾਲੀ)sve_ਸਰੋਤ_u16x4;                                           \
        ਕਰੋ {                                                              \
            ਅਚਲ uint8_t sve_src_chn_idx = 1;                            \
            ਅਚਲ uint8_t sve_dst_chn_idx = 0;                            \
            (ਖਾਲੀ)sve_src_chn_idx;                                        \
            (ਖਾਲੀ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ਸਰੋਤ_u16 = svget4((ma_ਸਰੋਤ_u16x4), 1);     \
            svuint16_t sve_ਨਿਸ਼ਾਨਾ_u16 = svget3((ma_ਨਿਸ਼ਾਨਾ_u16x3), 0);     \
            (ਖਾਲੀ)sve_ਸਰੋਤ_u16;                                         \
            (ਖਾਲੀ)sve_ਨਿਸ਼ਾਨਾ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ਨਿਸ਼ਾਨਾ_u16x3 = svset3(ma_ਨਿਸ਼ਾਨਾ_u16x3, 0, sve_ਨਿਸ਼ਾਨਾ_u16); \
        } ਜਦੋਂ (0);                                                      \
        ਕਰੋ {                                                              \
            ਅਚਲ uint8_t sve_src_chn_idx = 2;                            \
            ਅਚਲ uint8_t sve_dst_chn_idx = 1;                            \
            (ਖਾਲੀ)sve_src_chn_idx;                                        \
            (ਖਾਲੀ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ਸਰੋਤ_u16 = svget4((ma_ਸਰੋਤ_u16x4), 2);     \
            svuint16_t sve_ਨਿਸ਼ਾਨਾ_u16 = svget3((ma_ਨਿਸ਼ਾਨਾ_u16x3), 1);     \
            (ਖਾਲੀ)sve_ਸਰੋਤ_u16;                                         \
            (ਖਾਲੀ)sve_ਨਿਸ਼ਾਨਾ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ਨਿਸ਼ਾਨਾ_u16x3 = svset3(ma_ਨਿਸ਼ਾਨਾ_u16x3, 1, sve_ਨਿਸ਼ਾਨਾ_u16); \
        } ਜਦੋਂ (0);                                                      \
        ਕਰੋ {                                                              \
            ਅਚਲ uint8_t sve_src_chn_idx = 3;                            \
            ਅਚਲ uint8_t sve_dst_chn_idx = 2;                            \
            (ਖਾਲੀ)sve_src_chn_idx;                                        \
            (ਖਾਲੀ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ਸਰੋਤ_u16 = svget4((ma_ਸਰੋਤ_u16x4), 3);     \
            svuint16_t sve_ਨਿਸ਼ਾਨਾ_u16 = svget3((ma_ਨਿਸ਼ਾਨਾ_u16x3), 2);     \
            (ਖਾਲੀ)sve_ਸਰੋਤ_u16;                                         \
            (ਖਾਲੀ)sve_ਨਿਸ਼ਾਨਾ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ਨਿਸ਼ਾਨਾ_u16x3 = svset3(ma_ਨਿਸ਼ਾਨਾ_u16x3, 2, sve_ਨਿਸ਼ਾਨਾ_u16); \
        } ਜਦੋਂ (0);                                                      \
    } ਜਦੋਂ (0)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ sdl_sve_pixel_u16x4_foreach_chn_bgra_rgb565(ma_ਸਰੋਤ_u16x4,      \
                                                    ma_ਨਿਸ਼ਾਨਾ_u16x3,      \
                                                    ...)                  \
    ਕਰੋ {                                                                  \
        svuint16x4_t sve_ਸਰੋਤ_u16x4 = ma_ਸਰੋਤ_u16x4;                  \
        (ਖਾਲੀ)sve_ਸਰੋਤ_u16x4;                                           \
        ਕਰੋ {                                                              \
            ਅਚਲ uint8_t sve_src_chn_idx = 3;                            \
            ਅਚਲ uint8_t sve_dst_chn_idx = 0;                            \
            (ਖਾਲੀ)sve_src_chn_idx;                                        \
            (ਖਾਲੀ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ਸਰੋਤ_u16 = svget4((ma_ਸਰੋਤ_u16x4), 3);     \
            svuint16_t sve_ਨਿਸ਼ਾਨਾ_u16 = svget3((ma_ਨਿਸ਼ਾਨਾ_u16x3), 0);     \
            (ਖਾਲੀ)sve_ਸਰੋਤ_u16;                                         \
            (ਖਾਲੀ)sve_ਨਿਸ਼ਾਨਾ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ਨਿਸ਼ਾਨਾ_u16x3 = svset3(ma_ਨਿਸ਼ਾਨਾ_u16x3, 0, sve_ਨਿਸ਼ਾਨਾ_u16); \
        } ਜਦੋਂ (0);                                                      \
        ਕਰੋ {                                                              \
            ਅਚਲ uint8_t sve_src_chn_idx = 2;                            \
            ਅਚਲ uint8_t sve_dst_chn_idx = 1;                            \
            (ਖਾਲੀ)sve_src_chn_idx;                                        \
            (ਖਾਲੀ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ਸਰੋਤ_u16 = svget4((ma_ਸਰੋਤ_u16x4), 2);     \
            svuint16_t sve_ਨਿਸ਼ਾਨਾ_u16 = svget3((ma_ਨਿਸ਼ਾਨਾ_u16x3), 1);     \
            (ਖਾਲੀ)sve_ਸਰੋਤ_u16;                                         \
            (ਖਾਲੀ)sve_ਨਿਸ਼ਾਨਾ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ਨਿਸ਼ਾਨਾ_u16x3 = svset3(ma_ਨਿਸ਼ਾਨਾ_u16x3, 1, sve_ਨਿਸ਼ਾਨਾ_u16); \
        } ਜਦੋਂ (0);                                                      \
        ਕਰੋ {                                                              \
            ਅਚਲ uint8_t sve_src_chn_idx = 1;                            \
            ਅਚਲ uint8_t sve_dst_chn_idx = 2;                            \
            (ਖਾਲੀ)sve_src_chn_idx;                                        \
            (ਖਾਲੀ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ਸਰੋਤ_u16 = svget4((ma_ਸਰੋਤ_u16x4), 1);     \
            svuint16_t sve_ਨਿਸ਼ਾਨਾ_u16 = svget3((ma_ਨਿਸ਼ਾਨਾ_u16x3), 2);     \
            (ਖਾਲੀ)sve_ਸਰੋਤ_u16;                                         \
            (ਖਾਲੀ)sve_ਨਿਸ਼ਾਨਾ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ਨਿਸ਼ਾਨਾ_u16x3 = svset3(ma_ਨਿਸ਼ਾਨਾ_u16x3, 2, sve_ਨਿਸ਼ਾਨਾ_u16); \
        } ਜਦੋਂ (0);                                                      \
    } ਜਦੋਂ (0)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ sdl_sve_pixel_u16x4_foreach_chn_abgr_rgb565(ma_ਸਰੋਤ_u16x4,      \
                                                    ma_ਨਿਸ਼ਾਨਾ_u16x3,      \
                                                    ...)                  \
    ਕਰੋ {                                                                  \
        svuint16x4_t sve_ਸਰੋਤ_u16x4 = ma_ਸਰੋਤ_u16x4;                  \
        (ਖਾਲੀ)sve_ਸਰੋਤ_u16x4;                                           \
        ਕਰੋ {                                                              \
            ਅਚਲ uint8_t sve_src_chn_idx = 2;                            \
            ਅਚਲ uint8_t sve_dst_chn_idx = 0;                            \
            (ਖਾਲੀ)sve_src_chn_idx;                                        \
            (ਖਾਲੀ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ਸਰੋਤ_u16 = svget4((ma_ਸਰੋਤ_u16x4), 2);     \
            svuint16_t sve_ਨਿਸ਼ਾਨਾ_u16 = svget3((ma_ਨਿਸ਼ਾਨਾ_u16x3), 0);     \
            (ਖਾਲੀ)sve_ਸਰੋਤ_u16;                                         \
            (ਖਾਲੀ)sve_ਨਿਸ਼ਾਨਾ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ਨਿਸ਼ਾਨਾ_u16x3 = svset3(ma_ਨਿਸ਼ਾਨਾ_u16x3, 0, sve_ਨਿਸ਼ਾਨਾ_u16); \
        } ਜਦੋਂ (0);                                                      \
        ਕਰੋ {                                                              \
            ਅਚਲ uint8_t sve_src_chn_idx = 1;                            \
            ਅਚਲ uint8_t sve_dst_chn_idx = 1;                            \
            (ਖਾਲੀ)sve_src_chn_idx;                                        \
            (ਖਾਲੀ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ਸਰੋਤ_u16 = svget4((ma_ਸਰੋਤ_u16x4), 1);     \
            svuint16_t sve_ਨਿਸ਼ਾਨਾ_u16 = svget3((ma_ਨਿਸ਼ਾਨਾ_u16x3), 1);     \
            (ਖਾਲੀ)sve_ਸਰੋਤ_u16;                                         \
            (ਖਾਲੀ)sve_ਨਿਸ਼ਾਨਾ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ਨਿਸ਼ਾਨਾ_u16x3 = svset3(ma_ਨਿਸ਼ਾਨਾ_u16x3, 1, sve_ਨਿਸ਼ਾਨਾ_u16); \
        } ਜਦੋਂ (0);                                                      \
        ਕਰੋ {                                                              \
            ਅਚਲ uint8_t sve_src_chn_idx = 0;                            \
            ਅਚਲ uint8_t sve_dst_chn_idx = 2;                            \
            (ਖਾਲੀ)sve_src_chn_idx;                                        \
            (ਖਾਲੀ)sve_dst_chn_idx;                                        \
            svuint16_t sve_ਸਰੋਤ_u16 = svget4((ma_ਸਰੋਤ_u16x4), 0);     \
            svuint16_t sve_ਨਿਸ਼ਾਨਾ_u16 = svget3((ma_ਨਿਸ਼ਾਨਾ_u16x3), 2);     \
            (ਖਾਲੀ)sve_ਸਰੋਤ_u16;                                         \
            (ਖਾਲੀ)sve_ਨਿਸ਼ਾਨਾ_u16;                                         \
            __VA_ARGS__                                                   \
            ma_ਨਿਸ਼ਾਨਾ_u16x3 = svset3(ma_ਨਿਸ਼ਾਨਾ_u16x3, 2, sve_ਨਿਸ਼ਾਨਾ_u16); \
        } ਜਦੋਂ (0);                                                      \
    } ਜਦੋਂ (0)

SDL_TARGETING("arch=armv8-a+sve2")
ਸਥਿਰ ਸਤਰਅੰਦਰ svuint16x3_t sdl_sve_rgb565_unpack(svuint16_t vPixels)
{
    svuint16_t vBlue = svand_n_u16_m(svptrue_b16(), vPixels, 0x1F);
    svuint16_t vGreen = svand_n_u16_m(svptrue_b16(), vPixels, (0x3F << 5));
    svuint16_t vRed = svand_n_u16_m(svptrue_b16(), vPixels, (0x1F << 11));

    ਵਾਪਸ svcreate3_u16(svlsl_n_u16_m(svptrue_b16(), vBlue, 3),
                         svlsr_n_u16_m(svptrue_b16(), vGreen, 3),
                         svlsr_n_u16_m(svptrue_b16(), vRed, 8));
}

SDL_TARGETING("arch=armv8-a+sve2")
ਸਥਿਰ ਸਤਰਅੰਦਰ svuint16_t sdl_sve_rgb565_pack(svuint16x3_t vRGB16x3)
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
    ਵਾਪਸ svorr_u16_m(svptrue_b16(), vPixel, vBlue);

    // return  (svget3_u16(vRGB16x3, 0) >> 3)
    //     |   ((svget3_u16(vRGB16x3, 1) & (0x3F << 2)) << 3)
    //     |   ((svget3_u16(vRGB16x3, 2) & (0x1F << 3)) << 8);
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(2, 3, 4)
ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ svld3rgb565_u16(svbool_t vPredu8,
                                   uint16_t *phw_ਸਰੋਤ,
                                   svuint16x3_t *pv_ਨੀਵਾਂ,
                                   svuint16x3_t *pv_ਉੱਚਾ)
{
    svuint8x2_t vInput8x2 = svld2_u8(vPredu8, (uint8_t *)phw_ਸਰੋਤ);

    svuint16_t v_ਨੀਵਾਂ_Byte_ਨੀਵਾਂ_Half = svunpklo_u16(svget2_u8(vInput8x2, 0));
    svuint16_t v_ਨੀਵਾਂ_Byte_ਉੱਚਾ_Half = svunpkhi_u16(svget2_u8(vInput8x2, 0));

    svuint16_t v_ਉੱਚਾ_Byte_ਨੀਵਾਂ_Half = svunpklo_u16(svget2_u8(vInput8x2, 1));
    svuint16_t v_ਉੱਚਾ_Byte_ਉੱਚਾ_Half = svunpkhi_u16(svget2_u8(vInput8x2, 1));

    //*pvLow = sdl_sve_rgb565_unpack  (   vLowByteLowHalf
    //                                |   (vHighByteLowHalf << 8));
    *pv_ਨੀਵਾਂ = sdl_sve_rgb565_unpack(
        svorr_u16_m(svptrue_b16(),
                    v_ਨੀਵਾਂ_Byte_ਨੀਵਾਂ_Half,
                    //(vHighByteLowHalf << 8)
                    svlsl_n_u16_m(svptrue_b16(), v_ਉੱਚਾ_Byte_ਨੀਵਾਂ_Half, 8)));

    //*pvHigh = sdl_sve_rgb565_unpack (   vLowByteHighHalf
    //                                |   (vHighByteHighHalf << 8));
    *pv_ਉੱਚਾ = sdl_sve_rgb565_unpack(
        svorr_u16_m(svptrue_b16(),
                    v_ਨੀਵਾਂ_Byte_ਉੱਚਾ_Half,
                    //(vHighByteHighHalf << 8)
                    svlsl_n_u16_m(svptrue_b16(), v_ਉੱਚਾ_Byte_ਉੱਚਾ_Half, 8)));
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(2)
ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ svst3rgb565_u16(svbool_t vPredu8,
                                   uint16_t *phw_ਨਿਸ਼ਾਨਾ,
                                   svuint16x3_t v_ਨੀਵਾਂ,
                                   svuint16x3_t v_ਉੱਚਾ)
{
    svuint16_t v_ਨੀਵਾਂ_Byte_ਨੀਵਾਂ_Half = svundef_u16();
    svuint16_t v_ਉੱਚਾ_Byte_ਨੀਵਾਂ_Half = svundef_u16();

    /* pack low half pixels */
    ਕਰੋ {
        svuint16_t vPixel = sdl_sve_rgb565_pack(v_ਨੀਵਾਂ);

        // vLowByteLowHalf = vPixel & 0xFF;
        v_ਨੀਵਾਂ_Byte_ਨੀਵਾਂ_Half = svand_n_u16_m(svptrue_b16(), vPixel, 0xFF);

        // vHighByteLowHalf = vPixel >> 8;
        v_ਉੱਚਾ_Byte_ਨੀਵਾਂ_Half = svlsr_n_u16_m(svptrue_b16(), vPixel, 8);
    } ਜਦੋਂ (0);

    svuint16_t v_ਨੀਵਾਂ_Byte_ਉੱਚਾ_Half = svundef_u16();
    svuint16_t v_ਉੱਚਾ_Byte_ਉੱਚਾ_Half = svundef_u16();

    /* pack high half pixels */
    ਕਰੋ {
        svuint16_t vPixel = sdl_sve_rgb565_pack(v_ਉੱਚਾ);

        // vLowByteHighHalf = vPixel & 0xFF;
        v_ਨੀਵਾਂ_Byte_ਉੱਚਾ_Half = svand_n_u16_m(svptrue_b16(), vPixel, 0xFF);

        // vHighByteHighHalf = vPixel >> 8;
        v_ਉੱਚਾ_Byte_ਉੱਚਾ_Half = svlsr_n_u16_m(svptrue_b16(), vPixel, 8);
    } ਜਦੋਂ (0);

    /* save rgb565 pixels */
    svuint8_t v_ਨੀਵਾਂ_Byte = svuzp1_u8(svreinterpret_u8(v_ਨੀਵਾਂ_Byte_ਨੀਵਾਂ_Half),
                                   svreinterpret_u8(v_ਨੀਵਾਂ_Byte_ਉੱਚਾ_Half));

    svuint8_t v_ਉੱਚਾ_Byte = svuzp1_u8(svreinterpret_u8(v_ਉੱਚਾ_Byte_ਨੀਵਾਂ_Half),
                                    svreinterpret_u8(v_ਉੱਚਾ_Byte_ਉੱਚਾ_Half));

    svst2_u8(vPredu8, (uint8_t *)phw_ਨਿਸ਼ਾਨਾ, svcreate2_u8(v_ਨੀਵਾਂ_Byte, v_ਉੱਚਾ_Byte));
}

#ਜੇ defined(__GNUC__) && !defined(__clang__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ svld4ub_u16(ma_pred,                                                                                         \
                    ma_src_ptr,                                                                                      \
                    ma_svuint16x4_ਨੀਵਾਂ_ptr,                                                                           \
                    ma_svuint16x4_ਉੱਚਾ_ptr)                                                                          \
    ਕਰੋ {                                                                                                             \
        svuint8x4_t vInput8x4 = svld4_u8((ma_pred), (ma_src_ptr));                                                   \
                                                                                                                     \
        *(ma_svuint16x4_ਨੀਵਾਂ_ptr) = svset4_u16(*(ma_svuint16x4_ਨੀਵਾਂ_ptr), 0, svunpklo_u16(svget4_u8(vInput8x4, 0)));   \
        *(ma_svuint16x4_ਨੀਵਾਂ_ptr) = svset4_u16(*(ma_svuint16x4_ਨੀਵਾਂ_ptr), 1, svunpklo_u16(svget4_u8(vInput8x4, 1)));   \
        *(ma_svuint16x4_ਨੀਵਾਂ_ptr) = svset4_u16(*(ma_svuint16x4_ਨੀਵਾਂ_ptr), 2, svunpklo_u16(svget4_u8(vInput8x4, 2)));   \
        *(ma_svuint16x4_ਨੀਵਾਂ_ptr) = svset4_u16(*(ma_svuint16x4_ਨੀਵਾਂ_ptr), 3, svunpklo_u16(svget4_u8(vInput8x4, 3)));   \
                                                                                                                     \
        *(ma_svuint16x4_ਉੱਚਾ_ptr) = svset4_u16(*(ma_svuint16x4_ਉੱਚਾ_ptr), 0, svunpkhi_u16(svget4_u8(vInput8x4, 0))); \
        *(ma_svuint16x4_ਉੱਚਾ_ptr) = svset4_u16(*(ma_svuint16x4_ਉੱਚਾ_ptr), 1, svunpkhi_u16(svget4_u8(vInput8x4, 1))); \
        *(ma_svuint16x4_ਉੱਚਾ_ptr) = svset4_u16(*(ma_svuint16x4_ਉੱਚਾ_ptr), 2, svunpkhi_u16(svget4_u8(vInput8x4, 2))); \
        *(ma_svuint16x4_ਉੱਚਾ_ptr) = svset4_u16(*(ma_svuint16x4_ਉੱਚਾ_ptr), 3, svunpkhi_u16(svget4_u8(vInput8x4, 3))); \
    } ਜਦੋਂ (0)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ svst4ub_u16(ma_pred,                                                                 \
                    ma_dst_ptr,                                                              \
                    ma_svuint16x4_ਨੀਵਾਂ,                                                       \
                    ma_svuint16x4_ਉੱਚਾ)                                                      \
    ਕਰੋ {                                                                                     \
        svuint8_t vCH0u8 = svuzp1_u8(svreinterpret_u8(svget4_u16((ma_svuint16x4_ਨੀਵਾਂ), 0)),   \
                                     svreinterpret_u8(svget4_u16((ma_svuint16x4_ਉੱਚਾ), 0))); \
                                                                                             \
        svuint8_t vCH1u8 = svuzp1_u8(svreinterpret_u8(svget4_u16((ma_svuint16x4_ਨੀਵਾਂ), 1)),   \
                                     svreinterpret_u8(svget4_u16((ma_svuint16x4_ਉੱਚਾ), 1))); \
                                                                                             \
        svuint8_t vCH2u8 = svuzp1_u8(svreinterpret_u8(svget4_u16((ma_svuint16x4_ਨੀਵਾਂ), 2)),   \
                                     svreinterpret_u8(svget4_u16((ma_svuint16x4_ਉੱਚਾ), 2))); \
                                                                                             \
        svuint8_t vCH3u8 = svuzp1_u8(svreinterpret_u8(svget4_u16((ma_svuint16x4_ਨੀਵਾਂ), 3)),   \
                                     svreinterpret_u8(svget4_u16((ma_svuint16x4_ਉੱਚਾ), 3))); \
                                                                                             \
        svst4_u8((ma_pred), (ma_dst_ptr), svcreate4_u8(vCH0u8, vCH1u8, vCH2u8, vCH3u8));     \
    } ਜਦੋਂ (0)
#ਨਹੀਂਤਾਂ
SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(2, 3, 4)
ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ svld4ub_u16(svbool_t vPredu8,
                               uint8_t *pch_ਸਰੋਤ,
                               svuint16x4_t *pv_ਨੀਵਾਂ,
                               svuint16x4_t *pv_ਉੱਚਾ)
{
    svuint8x4_t vInput8x4 = svld4_u8(vPredu8, pch_ਸਰੋਤ);

    *pv_ਨੀਵਾਂ = svset4_u16(*pv_ਨੀਵਾਂ, 0, svunpklo_u16(svget4_u8(vInput8x4, 0)));
    *pv_ਨੀਵਾਂ = svset4_u16(*pv_ਨੀਵਾਂ, 1, svunpklo_u16(svget4_u8(vInput8x4, 1)));
    *pv_ਨੀਵਾਂ = svset4_u16(*pv_ਨੀਵਾਂ, 2, svunpklo_u16(svget4_u8(vInput8x4, 2)));
    *pv_ਨੀਵਾਂ = svset4_u16(*pv_ਨੀਵਾਂ, 3, svunpklo_u16(svget4_u8(vInput8x4, 3)));

    *pv_ਉੱਚਾ = svset4_u16(*pv_ਉੱਚਾ, 0, svunpkhi_u16(svget4_u8(vInput8x4, 0)));
    *pv_ਉੱਚਾ = svset4_u16(*pv_ਉੱਚਾ, 1, svunpkhi_u16(svget4_u8(vInput8x4, 1)));
    *pv_ਉੱਚਾ = svset4_u16(*pv_ਉੱਚਾ, 2, svunpkhi_u16(svget4_u8(vInput8x4, 2)));
    *pv_ਉੱਚਾ = svset4_u16(*pv_ਉੱਚਾ, 3, svunpkhi_u16(svget4_u8(vInput8x4, 3)));
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(2)
ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ svst4ub_u16(svbool_t vPredu8,
                               uint8_t *pch_ਨਿਸ਼ਾਨਾ,
                               svuint16x4_t v_ਨੀਵਾਂ,
                               svuint16x4_t v_ਉੱਚਾ)
{

    svuint8_t vCH0u8 = svuzp1_u8(svreinterpret_u8(svget4_u16(v_ਨੀਵਾਂ, 0)),
                                 svreinterpret_u8(svget4_u16(v_ਉੱਚਾ, 0)));

    svuint8_t vCH1u8 = svuzp1_u8(svreinterpret_u8(svget4_u16(v_ਨੀਵਾਂ, 1)),
                                 svreinterpret_u8(svget4_u16(v_ਉੱਚਾ, 1)));

    svuint8_t vCH2u8 = svuzp1_u8(svreinterpret_u8(svget4_u16(v_ਨੀਵਾਂ, 2)),
                                 svreinterpret_u8(svget4_u16(v_ਉੱਚਾ, 2)));

    svuint8_t vCH3u8 = svuzp1_u8(svreinterpret_u8(svget4_u16(v_ਨੀਵਾਂ, 3)),
                                 svreinterpret_u8(svget4_u16(v_ਉੱਚਾ, 3)));

    svst4_u8(vPredu8, pch_ਨਿਸ਼ਾਨਾ, svcreate4_u8(vCH0u8, vCH1u8, vCH2u8, vCH3u8));
}
#ਜੇ_ਅੰਤ

/*! \note the Element range of vMask is [0, 0xFF]
 */
SDL_TARGETING("arch=armv8-a+sve2")
ਸਥਿਰ ਸਤਰਅੰਦਰ svuint16_t sdl_sve_chn_blend_with_ਨਕਾਬ(svuint16_t v_ਸਰੋਤ,
                                                     svuint16_t v_ਨਿਸ਼ਾਨਾ,
                                                     svuint16_t v_ਨਕਾਬ)
{
    // vTarget = vSource * vMask + vTarget * (255 - vMask);
    svuint16_t vTemp0 = svdup_u16(1);
    vTemp0 = svmla_u16_m(svptrue_b16(), vTemp0, v_ਸਰੋਤ, v_ਨਕਾਬ);
    vTemp0 = svmla_u16_m(svptrue_b16(),
                         vTemp0,
                         v_ਨਿਸ਼ਾਨਾ,
                         svsub_u16_m(svptrue_b16(),
                                     svdup_u16(255),
                                     v_ਨਕਾਬ));

    /* x += x >> 8 */
    ਵਾਪਸ svreinterpret_u16_u8(
        svaddhnb_u16(vTemp0,
                     svlsr_n_u16_m(svptrue_b16(),
                                   vTemp0,
                                   8)));
}
/*! \note the Element range of vMask is [0, 0xFF]
 */
SDL_TARGETING("arch=armv8-a+sve2")
ਸਥਿਰ ਸਤਰਅੰਦਰ svuint16_t sdl_sve_chn_blend_with_ਨਕਾਬ_fast(svuint16_t v_ਸਰੋਤ,
                                                          svuint16_t v_ਨਿਸ਼ਾਨਾ,
                                                          svuint16_t v_ਨਕਾਬ)
{
    // vTarget = vSource * vMask + vTarget * (255 - vMask);
    svuint16_t vTemp0 = svmul_u16_m(svptrue_b16(), v_ਸਰੋਤ, v_ਨਕਾਬ);
    vTemp0 = svmla_u16_m(svptrue_b16(),
                         vTemp0,
                         v_ਨਿਸ਼ਾਨਾ,
                         svsub_u16_m(svptrue_b16(),
                                     svdup_u16(255),
                                     v_ਨਕਾਬ));

    ਵਾਪਸ svlsr_n_u16_m(svptrue_b16(), vTemp0, 8); // vTarget >> 8;
}

/*! \note the hwOpacity range [0, 0x100]
 */
SDL_TARGETING("arch=armv8-a+sve2")
ਸਥਿਰ ਸਤਰਅੰਦਰ svuint16_t sdl_sve_chn_blend_with_opacity(svuint16_t v_ਸਰੋਤ,
                                                        svuint16_t v_ਨਿਸ਼ਾਨਾ,
                                                        uint16_t hwOpacity)
{
    // svuint16_t vOpacity = svdup_u16(hwOpacity);
    // vTarget = vSource * vOpacity + vTarget * (256 - vOpacity);

    svuint16_t vTemp0 = svmul_n_u16_m(svptrue_b16(), v_ਸਰੋਤ, hwOpacity);
    svuint16_t vTemp1 = svmul_n_u16_m(svptrue_b16(),
                                      v_ਨਿਸ਼ਾਨਾ,
                                      256 - hwOpacity);
    v_ਨਿਸ਼ਾਨਾ = svadd_u16_m(svptrue_b16(), vTemp0, vTemp1);

    ਵਾਪਸ svlsr_n_u16_m(svptrue_b16(), v_ਨਿਸ਼ਾਨਾ, 8); // vTarget >> 8;
}

/*! \note the hwOpacity range [0, 0x100]
 */
SDL_TARGETING("arch=armv8-a+sve2")
ਸਥਿਰ ਸਤਰਅੰਦਰ svuint16_t sdl_sve_chn_blend_with_opacity_fast(svuint16_t v_ਸਰੋਤ,
                                                             svuint16_t v_ਨਿਸ਼ਾਨਾ,
                                                             uint16_t hwOpacity)
{
    // vTarget = vSource * vMask + vTarget * (255 - vMask);
    svuint16_t vTemp0 = svmul_n_u16_m(svptrue_b16(), v_ਸਰੋਤ, hwOpacity);
    vTemp0 = svmla_n_u16_m(svptrue_b16(),
                           vTemp0,
                           v_ਨਿਸ਼ਾਨਾ,
                           256 - hwOpacity);

    ਵਾਪਸ svlsr_n_u16_m(svptrue_b16(), vTemp0, 8); // vTarget >> 8;
}

/*! \note the Element range of vMask is [0, 0xFF]
 *  \note the hwOpacity range [0, 0x100]
 */
SDL_TARGETING("arch=armv8-a+sve2")
ਸਥਿਰ ਸਤਰਅੰਦਰ svuint16_t sdl_sve_chn_blend_with_ਨਕਾਬ_and_opacity(svuint16_t v_ਸਰੋਤ,
                                                                 svuint16_t v_ਨਿਸ਼ਾਨਾ,
                                                                 svuint16_t v_ਨਕਾਬ,
                                                                 uint16_t hwOpacity)
{
    v_ਨਕਾਬ = svsel(svcmpeq_n_u16(svptrue_b16(), v_ਨਕਾਬ, 255),
                  svdup_u16(hwOpacity),
                  //(vMask * hwOpacity) >> 8,
                  svlsr_n_u16_m(svptrue_b16(),
                                svmul_n_u16_m(svptrue_b16(), v_ਨਕਾਬ, hwOpacity),
                                8));

    // vTarget = vSource * vMask + vTarget * (256 - vMask);
    svuint16_t vTemp0 = svmul_u16_m(svptrue_b16(), v_ਸਰੋਤ, v_ਨਕਾਬ);
    svuint16_t vTemp1 = svmul_u16_m(svptrue_b16(),
                                    v_ਨਿਸ਼ਾਨਾ,
                                    svsub_u16_m(svptrue_b16(),
                                                svdup_u16(256),
                                                v_ਨਕਾਬ));
    v_ਨਿਸ਼ਾਨਾ = svadd_u16_m(svptrue_b16(), vTemp0, vTemp1);

    ਵਾਪਸ svlsr_n_u16_m(svptrue_b16(), v_ਨਿਸ਼ਾਨਾ, 8); // vTarget >> 8;
}

/*! \note the Element range of vMask0/1 is [0, 0xFF]
 */
SDL_TARGETING("arch=armv8-a+sve2")
ਸਥਿਰ ਸਤਰਅੰਦਰ svuint16_t sdl_sve_chn_blend_with_masks(svuint16_t v_ਸਰੋਤ,
                                                      svuint16_t v_ਨਿਸ਼ਾਨਾ,
                                                      svuint16_t vMask0,
                                                      svuint16_t vMask1)
{
    vMask1 = svadd_u16_m(svcmpeq_n_u16(svptrue_b16(), vMask1, 255),
                         vMask1,
                         svdup_u16(1));

    svuint16_t v_ਨਕਾਬ =
        svsel(svcmpge_n_u16(svptrue_b16(), vMask0, 255),
              vMask1,
              //(vMask0 * vMask1) >> 8,
              svlsr_n_u16_m(svptrue_b16(),
                            svmul_u16_m(svptrue_b16(), vMask0, vMask1),
                            8));

    // vTarget = vSource * vMask + vTarget * (256 - vMask);
    svuint16_t vTemp0 = svmul_u16_m(svptrue_b16(), v_ਸਰੋਤ, v_ਨਕਾਬ);
    svuint16_t vTemp1 = svmul_u16_m(svptrue_b16(),
                                    v_ਨਿਸ਼ਾਨਾ,
                                    svsub_u16_m(svptrue_b16(),
                                                svdup_u16(256),
                                                v_ਨਕਾਬ));
    v_ਨਿਸ਼ਾਨਾ = svadd_u16_m(svptrue_b16(), vTemp0, vTemp1);

    ਵਾਪਸ svlsr_n_u16_m(svptrue_b16(), v_ਨਿਸ਼ਾਨਾ, 8); // vTarget >> 8;
}

/*! \note the Element range of vMask0/1 is [0, 0xFF]
 *  \note the hwOpacity range [0, 0x100]
 */
SDL_TARGETING("arch=armv8-a+sve2")
ਸਥਿਰ ਸਤਰਅੰਦਰ svuint16_t sdl_sve_chn_blend_with_masks_and_opacity(
    svuint16_t v_ਸਰੋਤ,
    svuint16_t v_ਨਿਸ਼ਾਨਾ,
    svuint16_t vMask0,
    svuint16_t vMask1,
    uint16_t hwOpacity)
{
    vMask0 = svadd_u16_m(svcmpeq_n_u16(svptrue_b16(), vMask0, 255),
                         vMask0,
                         svdup_u16(1));

    svuint16_t v_ਨਕਾਬ =
        svsel(svcmpge_n_u16(svptrue_b16(), vMask1, 255), /* >= 255 */
              vMask0,
              //(vMask0 * vMask1) >> 8
              svlsr_n_u16_m(svptrue_b16(),
                            svmul_u16_m(svptrue_b16(), vMask0, vMask1),
                            8));

    v_ਨਕਾਬ =
        svsel(svcmpge_n_u16(svptrue_b16(), v_ਨਕਾਬ, 255),
              svdup_u16(hwOpacity),
              //(vMask * hwOpacity) >> 8,
              svlsr_n_u16_m(svptrue_b16(),
                            svmul_n_u16_m(svptrue_b16(), v_ਨਕਾਬ, hwOpacity),
                            8));

    // vTarget = vSource * vMask + vTarget * (256 - vMask);
    svuint16_t vTemp0 = svmul_u16_m(svptrue_b16(), v_ਸਰੋਤ, v_ਨਕਾਬ);
    svuint16_t vTemp1 = svmul_u16_m(svptrue_b16(),
                                    v_ਨਿਸ਼ਾਨਾ,
                                    svsub_u16_m(svptrue_b16(),
                                                svdup_u16(256),
                                                v_ਨਕਾਬ));
    v_ਨਿਸ਼ਾਨਾ = svadd_u16_m(svptrue_b16(), vTemp0, vTemp1);

    ਵਾਪਸ svlsr_n_u16_m(svptrue_b16(), v_ਨਿਸ਼ਾਨਾ, 8); // vTarget >> 8;
}

/*! \note the Element range of vMask0/1 is [0, 0xFF]
 */
SDL_TARGETING("arch=armv8-a+sve2")
ਸਥਿਰ ਸਤਰਅੰਦਰ svuint16_t sdl_sve_chn_blend_with_3masks(svuint16_t v_ਸਰੋਤ,
                                                       svuint16_t v_ਨਿਸ਼ਾਨਾ,
                                                       svuint16_t vMask0,
                                                       svuint16_t vMask1,
                                                       svuint16_t vMask2)
{
    vMask0 = svadd_u16_m(svcmpeq_n_u16(svptrue_b16(), vMask0, 255),
                         vMask0,
                         svdup_u16(1));

    svuint16_t v_ਨਕਾਬ =
        svsel(svcmpge_n_u16(svptrue_b16(), vMask1, 255),
              vMask0,
              //(vMask0 * vMask1) >> 8
              svlsr_n_u16_m(svptrue_b16(),
                            svmul_u16_m(svptrue_b16(), vMask0, vMask1),
                            8));

    v_ਨਕਾਬ =
        svsel(svcmpge_n_u16(svptrue_b16(), vMask2, 255),
              v_ਨਕਾਬ,
              //(vMask * vMask2) >> 8
              svlsr_n_u16_m(svptrue_b16(),
                            svmul_u16_m(svptrue_b16(), v_ਨਕਾਬ, vMask2),
                            8));

    // vTarget = vSource * vMask + vTarget * (256 - vMask);
    svuint16_t vTemp0 = svmul_u16_m(svptrue_b16(), v_ਸਰੋਤ, v_ਨਕਾਬ);
    svuint16_t vTemp1 = svmul_u16_m(svptrue_b16(),
                                    v_ਨਿਸ਼ਾਨਾ,
                                    svsub_u16_m(svptrue_b16(),
                                                svdup_u16(256),
                                                v_ਨਕਾਬ));
    v_ਨਿਸ਼ਾਨਾ = svadd_u16_m(svptrue_b16(), vTemp0, vTemp1);

    ਵਾਪਸ svlsr_n_u16_m(svptrue_b16(), v_ਨਿਸ਼ਾਨਾ, 8); // vTarget >> 8;
}

/*! \note the Element range of vMask0/1 is [0, 0xFF]
 *  \note the hwOpacity range [0, 0x100]
 */
SDL_TARGETING("arch=armv8-a+sve2")
ਸਥਿਰ ਸਤਰਅੰਦਰ svuint16_t sdl_sve_chn_blend_with_3masks_and_opacity(
    svuint16_t v_ਸਰੋਤ,
    svuint16_t v_ਨਿਸ਼ਾਨਾ,
    svuint16_t vMask0,
    svuint16_t vMask1,
    svuint16_t vMask2,
    uint16_t hwOpacity)
{
    vMask0 = svadd_u16_m(svcmpeq_n_u16(svptrue_b16(), vMask0, 255),
                         vMask0,
                         svdup_u16(1));

    svuint16_t v_ਨਕਾਬ =
        svsel(svcmpge_n_u16(svptrue_b16(), vMask1, 255),
              vMask0,
              //(vMask0 * vMask1) >> 8
              svlsr_n_u16_m(svptrue_b16(),
                            svmul_u16_m(svptrue_b16(), vMask0, vMask1),
                            8));

    v_ਨਕਾਬ =
        svsel(svcmpge_n_u16(svptrue_b16(), vMask2, 255),
              v_ਨਕਾਬ,
              svlsr_n_u16_m(svptrue_b16(),
                            svmul_u16_m(svptrue_b16(), v_ਨਕਾਬ, vMask2),
                            8));
    //(vMask * vMask2) >> 8);

    v_ਨਕਾਬ =
        svsel(svcmpge_n_u16(svptrue_b16(), v_ਨਕਾਬ, 255),
              svdup_u16(hwOpacity),
              //(vMask * hwOpacity) >> 8
              svlsr_n_u16_m(svptrue_b16(),
                            svmul_n_u16_m(svptrue_b16(), v_ਨਕਾਬ, hwOpacity),
                            8));

    // vTarget = vSource * vMask + vTarget * (256 - vMask);
    svuint16_t vTemp0 = svmul_u16_m(svptrue_b16(), v_ਸਰੋਤ, v_ਨਕਾਬ);
    svuint16_t vTemp1 = svmul_u16_m(svptrue_b16(),
                                    v_ਨਿਸ਼ਾਨਾ,
                                    svsub_u16_m(svptrue_b16(),
                                                svdup_u16(256),
                                                v_ਨਕਾਬ));
    v_ਨਿਸ਼ਾਨਾ = svadd_u16_m(svptrue_b16(), vTemp0, vTemp1);

    ਵਾਪਸ svlsr_n_u16_m(svptrue_b16(), v_ਨਿਸ਼ਾਨਾ, 8); // vTarget >> 8;
}

#ਜੇ_ਅੰਤ /* SDL_SVE2_EXTENSION_H */