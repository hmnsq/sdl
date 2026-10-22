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

#إذا !defined(SDL_SVE2_EXTENSION_H) //&& (defined(__ARM_FEATURE_SVE2) && __ARM_FEATURE_SVE2)
#تعریف_کن SDL_SVE2_EXTENSION_H

#ضمن "SDL_sve2_util.h"

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
#اگر_تعریف_شده SDL_PLATFORM_ANDROID
#اگر_تعریف_نشده __ARM_FEATURE_SVE
#تعریف_کن __ARM_FEATURE_SVE 1
#پایان_اگر
#پایان_اگر
#ضمن <arm_sve.h>
#ضمن <stdint.h>

/*!
 * \brief a wrapper for __attribute__((nonnull))
 */
#اگر_تعریف_نشده ARM_NONNULL
#تعریف_کن ARM_NONNULL(...) __attribute__((nonnull(__VA_ARGS__)))
#پایان_اگر

#تعریف_کن svlenu8()  svcntb_pat(SV_ALL)
#تعریف_کن svlenu16() (svcntb_pat(SV_ALL) / حجم(uint16_t))
#تعریف_کن svlenu32() (svcntb_pat(SV_ALL) / حجم(uint32_t))
#تعریف_کن svlenu64() (svcntb_pat(SV_ALL) / حجم(uint64_t))

#تعریف_کن svlens8()  svlenu8()
#تعریف_کن svlens16() svlenu16()
#تعریف_کن svlens32() svlenu32()
#تعریف_کن svlens64() svlenu64()

#تعریف_کن sdl_sve_stride_loop_pixel(ma_stride_اندازه, ma_pred_name)          \
    لكل (svbool_t ma_pred_name, *p_موقت = &ma_pred_name;                  \
         p_موقت != عدم;                                                  \
         p_موقت = عدم)                                                   \
        لكل (size_t SVE_امن_NAME(n) = 0,                                \
                    sve_iteration_advance = svlenu8();                   \
             ({                                                          \
                 ma_pred_name = svwhilelt_b8((int32_t)SVE_امن_NAME(n),  \
                                             (int32_t)(ma_stride_اندازه)); \
                 SVE_امن_NAME(n) < (ma_stride_اندازه);                    \
             });                                                         \
             SVE_امن_NAME(n) += sve_iteration_advance)

#تعریف_کن sdl_sve_stride_loop_u8 sdl_sve_stride_loop_pixel

#تعریف_کن sdl_sve_stride_loop_u16(ma_stride_اندازه, ma_pred_name)             \
    لكل (svbool_t ma_pred_name, *p_موقت = &ma_pred_name;                   \
         p_موقت != عدم;                                                   \
         p_موقت = عدم)                                                    \
        لكل (size_t SVE_امن_NAME(n) = 0,                                 \
                    sve_iteration_advance = svlenu16();                   \
             ({                                                           \
                 ma_pred_name = svwhilelt_b16((int32_t)SVE_امن_NAME(n),  \
                                              (int32_t)(ma_stride_اندازه)); \
                 SVE_امن_NAME(n) < (ma_stride_اندازه);                     \
             });                                                          \
             SVE_امن_NAME(n) += sve_iteration_advance)

#تعریف_کن sdl_sve_stride_loop_u32(ma_stride_اندازه, ma_pred_name)             \
    لكل (svbool_t ma_pred_name, *p_موقت = &ma_pred_name;                   \
         p_موقت != عدم;                                                   \
         p_موقت = عدم)                                                    \
        لكل (size_t SVE_امن_NAME(n) = 0,                                 \
                    sve_iteration_advance = svlenu32();                   \
             ({                                                           \
                 ma_pred_name = svwhilelt_b16((int32_t)SVE_امن_NAME(n),  \
                                              (int32_t)(ma_stride_اندازه)); \
                 SVE_امن_NAME(n) < (ma_stride_اندازه);                     \
             });                                                          \
             SVE_امن_NAME(n) += sve_iteration_advance)

#تعریف_کن sdl_sve_pixel_ccc_foreach_chn(ma_منبع_u16x3,                    \
                                      ma_هدف_u16x3,                    \
                                      ...)                                \
    افعل {                                                                  \
        svuint16x3_t sve_منبع_u16x3 = ma_منبع_u16x3;                  \
        (فراغ)sve_منبع_u16x3;                                           \
        افعل {                                                              \
            ثابت uint8_t sve_src_chn_idx = 0;                            \
            (فراغ)sve_src_chn_idx;                                        \
            svuint16_t sve_منبع_u16 = svget3((ma_منبع_u16x3), 0);     \
            svuint16_t sve_هدف_u16 = svget3((ma_هدف_u16x3), 0);     \
            (فراغ)sve_منبع_u16;                                         \
            (فراغ)sve_هدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_هدف_u16x3 = svset3(ma_هدف_u16x3, 0, sve_هدف_u16); \
        } طالما (0);                                                      \
        افعل {                                                              \
            ثابت uint8_t sve_src_chn_idx = 1;                            \
            (فراغ)sve_src_chn_idx;                                        \
            svuint16_t sve_منبع_u16 = svget3((ma_منبع_u16x3), 1);     \
            svuint16_t sve_هدف_u16 = svget3((ma_هدف_u16x3), 1);     \
            (فراغ)sve_منبع_u16;                                         \
            (فراغ)sve_هدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_هدف_u16x3 = svset3(ma_هدف_u16x3, 1, sve_هدف_u16); \
        } طالما (0);                                                      \
        افعل {                                                              \
            ثابت uint8_t sve_src_chn_idx = 2;                            \
            (فراغ)sve_src_chn_idx;                                        \
            svuint16_t sve_منبع_u16 = svget3((ma_منبع_u16x3), 2);     \
            svuint16_t sve_هدف_u16 = svget3((ma_هدف_u16x3), 2);     \
            (فراغ)sve_منبع_u16;                                         \
            (فراغ)sve_هدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_هدف_u16x3 = svset3(ma_هدف_u16x3, 2, sve_هدف_u16); \
        } طالما (0);                                                      \
    } طالما (0)

#تعریف_کن sdl_sve_pixel_accc_foreach_chn012(ma_منبع_u16x4,                \
                                          ma_هدف_u16x4,                \
                                          ...)                            \
    افعل {                                                                  \
        svuint16x4_t sve_منبع_u16x4 = ma_منبع_u16x4;                  \
        (فراغ)sve_منبع_u16x4;                                           \
        افعل {                                                              \
            ثابت uint8_t sve_src_chn_idx = 0;                            \
            (فراغ)sve_src_chn_idx;                                        \
            svuint16_t sve_منبع_u16 = svget4((ma_منبع_u16x4), 0);     \
            svuint16_t sve_هدف_u16 = svget4((ma_هدف_u16x4), 0);     \
            (فراغ)sve_منبع_u16;                                         \
            (فراغ)sve_هدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_هدف_u16x4 = svset4(ma_هدف_u16x4, 0, sve_هدف_u16); \
        } طالما (0);                                                      \
        افعل {                                                              \
            ثابت uint8_t sve_src_chn_idx = 1;                            \
            (فراغ)sve_src_chn_idx;                                        \
            svuint16_t sve_منبع_u16 = svget4((ma_منبع_u16x4), 1);     \
            svuint16_t sve_هدف_u16 = svget4((ma_هدف_u16x4), 1);     \
            (فراغ)sve_منبع_u16;                                         \
            (فراغ)sve_هدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_هدف_u16x4 = svset4(ma_هدف_u16x4, 1, sve_هدف_u16); \
        } طالما (0);                                                      \
        افعل {                                                              \
            ثابت uint8_t sve_src_chn_idx = 2;                            \
            (فراغ)sve_src_chn_idx;                                        \
            svuint16_t sve_منبع_u16 = svget4((ma_منبع_u16x4), 2);     \
            svuint16_t sve_هدف_u16 = svget4((ma_هدف_u16x4), 2);     \
            (فراغ)sve_منبع_u16;                                         \
            (فراغ)sve_هدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_هدف_u16x4 = svset4(ma_هدف_u16x4, 2, sve_هدف_u16); \
        } طالما (0);                                                      \
    } طالما (0)

#تعریف_کن sdl_sve_pixel_accc_foreach_chn(ma_منبع_u16x4,                   \
                                       ma_هدف_u16x4,                   \
                                       ...)                               \
    افعل {                                                                  \
        svuint16x4_t sve_منبع_u16x4 = ma_منبع_u16x4;                  \
        (فراغ)sve_منبع_u16x4;                                           \
        افعل {                                                              \
            ثابت uint8_t sve_src_chn_idx = 0;                            \
            (فراغ)sve_src_chn_idx;                                        \
            (فراغ)sve_dst_chn_idx;                                        \
            svuint16_t sve_منبع_u16 = svget4((ma_منبع_u16x4), 0);     \
            svuint16_t sve_هدف_u16 = svget4((ma_هدف_u16x4), 0);     \
            (فراغ)sve_منبع_u16;                                         \
            (فراغ)sve_هدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_هدف_u16x4 = svset4(ma_هدف_u16x4, 0, sve_هدف_u16); \
        } طالما (0);                                                      \
        افعل {                                                              \
            ثابت uint8_t sve_src_chn_idx = 1;                            \
            (فراغ)sve_src_chn_idx;                                        \
            (فراغ)sve_dst_chn_idx;                                        \
            svuint16_t sve_منبع_u16 = svget4((ma_منبع_u16x4), 1);     \
            svuint16_t sve_هدف_u16 = svget4((ma_هدف_u16x4), 1);     \
            (فراغ)sve_منبع_u16;                                         \
            (فراغ)sve_هدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_هدف_u16x4 = svset4(ma_هدف_u16x4, 1, sve_هدف_u16); \
        } طالما (0);                                                      \
        افعل {                                                              \
            ثابت uint8_t sve_src_chn_idx = 2;                            \
            (فراغ)sve_src_chn_idx;                                        \
            (فراغ)sve_dst_chn_idx;                                        \
            svuint16_t sve_منبع_u16 = svget4((ma_منبع_u16x4), 2);     \
            svuint16_t sve_هدف_u16 = svget4((ma_هدف_u16x4), 2);     \
            (فراغ)sve_منبع_u16;                                         \
            (فراغ)sve_هدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_هدف_u16x4 = svset4(ma_هدف_u16x4, 2, sve_هدف_u16); \
        } طالما (0);                                                      \
        افعل {                                                              \
            ثابت uint8_t sve_src_chn_idx = 3;                            \
            (فراغ)sve_src_chn_idx;                                        \
            (فراغ)sve_dst_chn_idx;                                        \
            svuint16_t sve_منبع_u16 = svget4((ma_منبع_u16x4), 3);     \
            svuint16_t sve_هدف_u16 = svget4((ma_هدف_u16x4), 3);     \
            (فراغ)sve_منبع_u16;                                         \
            (فراغ)sve_هدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_هدف_u16x4 = svset4(ma_هدف_u16x4, 3, sve_هدف_u16); \
        } طالما (0);                                                      \
    } طالما (0)

#تعریف_کن sdl_sve_pixel_u16x4_foreach_chn(ma_منبع_u16x4,                  \
                                        ma_هدف_u16x4,                  \
                                        ...)                              \
    افعل {                                                                  \
        svuint16x4_t sve_منبع_u16x4 = ma_منبع_u16x4;                  \
        (فراغ)sve_منبع_u16x4;                                           \
        افعل {                                                              \
            ثابت uint8_t sve_src_chn_idx = 0;                            \
            (فراغ)sve_src_chn_idx;                                        \
            svuint16_t sve_منبع_u16 = svget4((ma_منبع_u16x4), 0);     \
            svuint16_t sve_هدف_u16 = svget4((ma_هدف_u16x4), 0);     \
            (فراغ)sve_منبع_u16;                                         \
            (فراغ)sve_هدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_هدف_u16x4 = svset4(ma_هدف_u16x4, 0, sve_هدف_u16); \
        } طالما (0);                                                      \
        افعل {                                                              \
            ثابت uint8_t sve_src_chn_idx = 1;                            \
            (فراغ)sve_src_chn_idx;                                        \
            svuint16_t sve_منبع_u16 = svget4((ma_منبع_u16x4), 1);     \
            svuint16_t sve_هدف_u16 = svget4((ma_هدف_u16x4), 1);     \
            (فراغ)sve_منبع_u16;                                         \
            (فراغ)sve_هدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_هدف_u16x4 = svset4(ma_هدف_u16x4, 1, sve_هدف_u16); \
        } طالما (0);                                                      \
        افعل {                                                              \
            ثابت uint8_t sve_src_chn_idx = 2;                            \
            (فراغ)sve_src_chn_idx;                                        \
            svuint16_t sve_منبع_u16 = svget4((ma_منبع_u16x4), 2);     \
            svuint16_t sve_هدف_u16 = svget4((ma_هدف_u16x4), 2);     \
            (فراغ)sve_منبع_u16;                                         \
            (فراغ)sve_هدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_هدف_u16x4 = svset4(ma_هدف_u16x4, 2, sve_هدف_u16); \
        } طالما (0);                                                      \
        افعل {                                                              \
            ثابت uint8_t sve_src_chn_idx = 3;                            \
            (فراغ)sve_src_chn_idx;                                        \
            svuint16_t sve_منبع_u16 = svget4((ma_منبع_u16x4), 3);     \
            svuint16_t sve_هدف_u16 = svget4((ma_هدف_u16x4), 3);     \
            (فراغ)sve_منبع_u16;                                         \
            (فراغ)sve_هدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_هدف_u16x4 = svset4(ma_هدف_u16x4, 3, sve_هدف_u16); \
        } طالما (0);                                                      \
    } طالما (0)

#تعریف_کن sdl_sve_pixel_u16x4_foreach_chn_src_dst_rev(ma_منبع_u16x4,      \
                                                    ma_هدف_u16x4,      \
                                                    ...)                  \
    افعل {                                                                  \
        svuint16x4_t sve_منبع_u16x4 = ma_منبع_u16x4;                  \
        (فراغ)sve_منبع_u16x4;                                           \
        افعل {                                                              \
            ثابت uint8_t sve_src_chn_idx = 0;                            \
            ثابت uint8_t sve_dst_chn_idx = 3;                            \
            (فراغ)sve_src_chn_idx;                                        \
            (فراغ)sve_dst_chn_idx;                                        \
            svuint16_t sve_منبع_u16 = svget4((ma_منبع_u16x4), 0);     \
            svuint16_t sve_هدف_u16 = svget4((ma_هدف_u16x4), 3);     \
            (فراغ)sve_منبع_u16;                                         \
            (فراغ)sve_هدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_هدف_u16x4 = svset4(ma_هدف_u16x4, 3, sve_هدف_u16); \
        } طالما (0);                                                      \
        افعل {                                                              \
            ثابت uint8_t sve_src_chn_idx = 1;                            \
            ثابت uint8_t sve_dst_chn_idx = 2;                            \
            (فراغ)sve_src_chn_idx;                                        \
            (فراغ)sve_dst_chn_idx;                                        \
            svuint16_t sve_منبع_u16 = svget4((ma_منبع_u16x4), 1);     \
            svuint16_t sve_هدف_u16 = svget4((ma_هدف_u16x4), 2);     \
            (فراغ)sve_منبع_u16;                                         \
            (فراغ)sve_هدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_هدف_u16x4 = svset4(ma_هدف_u16x4, 2, sve_هدف_u16); \
        } طالما (0);                                                      \
        افعل {                                                              \
            ثابت uint8_t sve_src_chn_idx = 2;                            \
            ثابت uint8_t sve_dst_chn_idx = 1;                            \
            (فراغ)sve_src_chn_idx;                                        \
            (فراغ)sve_dst_chn_idx;                                        \
            svuint16_t sve_منبع_u16 = svget4((ma_منبع_u16x4), 2);     \
            svuint16_t sve_هدف_u16 = svget4((ma_هدف_u16x4), 1);     \
            (فراغ)sve_منبع_u16;                                         \
            (فراغ)sve_هدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_هدف_u16x4 = svset4(ma_هدف_u16x4, 1, sve_هدف_u16); \
        } طالما (0);                                                      \
        افعل {                                                              \
            ثابت uint8_t sve_src_chn_idx = 3;                            \
            ثابت uint8_t sve_dst_chn_idx = 0;                            \
            (فراغ)sve_src_chn_idx;                                        \
            (فراغ)sve_dst_chn_idx;                                        \
            svuint16_t sve_منبع_u16 = svget4((ma_منبع_u16x4), 3);     \
            svuint16_t sve_هدف_u16 = svget4((ma_هدف_u16x4), 0);     \
            (فراغ)sve_منبع_u16;                                         \
            (فراغ)sve_هدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_هدف_u16x4 = svset4(ma_هدف_u16x4, 0, sve_هدف_u16); \
        } طالما (0);                                                      \
    } طالما (0)

#تعریف_کن sdl_sve_pixel_u16x4_foreach_chn_accc_ccca(ma_منبع_u16x4,        \
                                                  ma_هدف_u16x4,        \
                                                  ...)                    \
    افعل {                                                                  \
        svuint16x4_t sve_منبع_u16x4 = ma_منبع_u16x4;                  \
        (فراغ)sve_منبع_u16x4;                                           \
        افعل {                                                              \
            ثابت uint8_t sve_src_chn_idx = 0;                            \
            ثابت uint8_t sve_dst_chn_idx = 1;                            \
            (فراغ)sve_src_chn_idx;                                        \
            (فراغ)sve_dst_chn_idx;                                        \
            svuint16_t sve_منبع_u16 = svget4((ma_منبع_u16x4), 0);     \
            svuint16_t sve_هدف_u16 = svget4((ma_هدف_u16x4), 1);     \
            (فراغ)sve_منبع_u16;                                         \
            (فراغ)sve_هدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_هدف_u16x4 = svset4(ma_هدف_u16x4, 1, sve_هدف_u16); \
        } طالما (0);                                                      \
        افعل {                                                              \
            ثابت uint8_t sve_src_chn_idx = 1;                            \
            ثابت uint8_t sve_dst_chn_idx = 2;                            \
            (فراغ)sve_src_chn_idx;                                        \
            (فراغ)sve_dst_chn_idx;                                        \
            svuint16_t sve_منبع_u16 = svget4((ma_منبع_u16x4), 1);     \
            svuint16_t sve_هدف_u16 = svget4((ma_هدف_u16x4), 2);     \
            (فراغ)sve_منبع_u16;                                         \
            (فراغ)sve_هدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_هدف_u16x4 = svset4(ma_هدف_u16x4, 2, sve_هدف_u16); \
        } طالما (0);                                                      \
        افعل {                                                              \
            ثابت uint8_t sve_src_chn_idx = 2;                            \
            ثابت uint8_t sve_dst_chn_idx = 3;                            \
            (فراغ)sve_src_chn_idx;                                        \
            (فراغ)sve_dst_chn_idx;                                        \
            svuint16_t sve_منبع_u16 = svget4((ma_منبع_u16x4), 2);     \
            svuint16_t sve_هدف_u16 = svget4((ma_هدف_u16x4), 3);     \
            (فراغ)sve_منبع_u16;                                         \
            (فراغ)sve_هدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_هدف_u16x4 = svset4(ma_هدف_u16x4, 3, sve_هدف_u16); \
        } طالما (0);                                                      \
        افعل {                                                              \
            ثابت uint8_t sve_src_chn_idx = 3;                            \
            ثابت uint8_t sve_dst_chn_idx = 0;                            \
            (فراغ)sve_src_chn_idx;                                        \
            (فراغ)sve_dst_chn_idx;                                        \
            svuint16_t sve_منبع_u16 = svget4((ma_منبع_u16x4), 3);     \
            svuint16_t sve_هدف_u16 = svget4((ma_هدف_u16x4), 0);     \
            (فراغ)sve_منبع_u16;                                         \
            (فراغ)sve_هدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_هدف_u16x4 = svset4(ma_هدف_u16x4, 0, sve_هدف_u16); \
        } طالما (0);                                                      \
    } طالما (0)

#تعریف_کن sdl_sve_pixel_u16x4_foreach_chn_ccca_accc(ma_منبع_u16x4,        \
                                                  ma_هدف_u16x4,        \
                                                  ...)                    \
    افعل {                                                                  \
        svuint16x4_t sve_منبع_u16x4 = ma_منبع_u16x4;                  \
        (فراغ)sve_منبع_u16x4;                                           \
        افعل {                                                              \
            ثابت uint8_t sve_src_chn_idx = 1;                            \
            ثابت uint8_t sve_dst_chn_idx = 0;                            \
            (فراغ)sve_src_chn_idx;                                        \
            (فراغ)sve_dst_chn_idx;                                        \
            svuint16_t sve_منبع_u16 = svget4((ma_منبع_u16x4), 1);     \
            svuint16_t sve_هدف_u16 = svget4((ma_هدف_u16x4), 0);     \
            (فراغ)sve_منبع_u16;                                         \
            (فراغ)sve_هدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_هدف_u16x4 = svset4(ma_هدف_u16x4, 0, sve_هدف_u16); \
        } طالما (0);                                                      \
        افعل {                                                              \
            ثابت uint8_t sve_src_chn_idx = 2;                            \
            ثابت uint8_t sve_dst_chn_idx = 1;                            \
            (فراغ)sve_src_chn_idx;                                        \
            (فراغ)sve_dst_chn_idx;                                        \
            svuint16_t sve_منبع_u16 = svget4((ma_منبع_u16x4), 2);     \
            svuint16_t sve_هدف_u16 = svget4((ma_هدف_u16x4), 1);     \
            (فراغ)sve_منبع_u16;                                         \
            (فراغ)sve_هدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_هدف_u16x4 = svset4(ma_هدف_u16x4, 1, sve_هدف_u16); \
        } طالما (0);                                                      \
        افعل {                                                              \
            ثابت uint8_t sve_src_chn_idx = 3;                            \
            ثابت uint8_t sve_dst_chn_idx = 2;                            \
            (فراغ)sve_src_chn_idx;                                        \
            (فراغ)sve_dst_chn_idx;                                        \
            svuint16_t sve_منبع_u16 = svget4((ma_منبع_u16x4), 3);     \
            svuint16_t sve_هدف_u16 = svget4((ma_هدف_u16x4), 2);     \
            (فراغ)sve_منبع_u16;                                         \
            (فراغ)sve_هدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_هدف_u16x4 = svset4(ma_هدف_u16x4, 2, sve_هدف_u16); \
        } طالما (0);                                                      \
        افعل {                                                              \
            ثابت uint8_t sve_src_chn_idx = 0;                            \
            ثابت uint8_t sve_dst_chn_idx = 3;                            \
            (فراغ)sve_src_chn_idx;                                        \
            (فراغ)sve_dst_chn_idx;                                        \
            svuint16_t sve_منبع_u16 = svget4((ma_منبع_u16x4), 0);     \
            svuint16_t sve_هدف_u16 = svget4((ma_هدف_u16x4), 3);     \
            (فراغ)sve_منبع_u16;                                         \
            (فراغ)sve_هدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_هدف_u16x4 = svset4(ma_هدف_u16x4, 3, sve_هدف_u16); \
        } طالما (0);                                                      \
    } طالما (0)

#تعریف_کن sdl_sve_pixel_u16x4_foreach_chn_a123_a321(ma_منبع_u16x4,        \
                                                  ma_هدف_u16x4,        \
                                                  ...)                    \
    افعل {                                                                  \
        svuint16x4_t sve_منبع_u16x4 = ma_منبع_u16x4;                  \
        (فراغ)sve_منبع_u16x4;                                           \
        افعل {                                                              \
            ثابت uint8_t sve_src_chn_idx = 0;                            \
            ثابت uint8_t sve_dst_chn_idx = 2;                            \
            (فراغ)sve_src_chn_idx;                                        \
            (فراغ)sve_dst_chn_idx;                                        \
            svuint16_t sve_منبع_u16 = svget4((ma_منبع_u16x4), 0);     \
            svuint16_t sve_هدف_u16 = svget4((ma_هدف_u16x4), 2);     \
            (فراغ)sve_منبع_u16;                                         \
            (فراغ)sve_هدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_هدف_u16x4 = svset4(ma_هدف_u16x4, 2, sve_هدف_u16); \
        } طالما (0);                                                      \
        افعل {                                                              \
            ثابت uint8_t sve_src_chn_idx = 1;                            \
            ثابت uint8_t sve_dst_chn_idx = 1;                            \
            (فراغ)sve_src_chn_idx;                                        \
            (فراغ)sve_dst_chn_idx;                                        \
            svuint16_t sve_منبع_u16 = svget4((ma_منبع_u16x4), 1);     \
            svuint16_t sve_هدف_u16 = svget4((ma_هدف_u16x4), 1);     \
            (فراغ)sve_منبع_u16;                                         \
            (فراغ)sve_هدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_هدف_u16x4 = svset4(ma_هدف_u16x4, 1, sve_هدف_u16); \
        } طالما (0);                                                      \
        افعل {                                                              \
            ثابت uint8_t sve_src_chn_idx = 2;                            \
            ثابت uint8_t sve_dst_chn_idx = 0;                            \
            (فراغ)sve_src_chn_idx;                                        \
            (فراغ)sve_dst_chn_idx;                                        \
            svuint16_t sve_منبع_u16 = svget4((ma_منبع_u16x4), 2);     \
            svuint16_t sve_هدف_u16 = svget4((ma_هدف_u16x4), 0);     \
            (فراغ)sve_منبع_u16;                                         \
            (فراغ)sve_هدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_هدف_u16x4 = svset4(ma_هدف_u16x4, 0, sve_هدف_u16); \
        } طالما (0);                                                      \
        افعل {                                                              \
            ثابت uint8_t sve_src_chn_idx = 3;                            \
            ثابت uint8_t sve_dst_chn_idx = 3;                            \
            (فراغ)sve_src_chn_idx;                                        \
            (فراغ)sve_dst_chn_idx;                                        \
            svuint16_t sve_منبع_u16 = svget4((ma_منبع_u16x4), 3);     \
            svuint16_t sve_هدف_u16 = svget4((ma_هدف_u16x4), 3);     \
            (فراغ)sve_منبع_u16;                                         \
            (فراغ)sve_هدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_هدف_u16x4 = svset4(ma_هدف_u16x4, 3, sve_هدف_u16); \
        } طالما (0);                                                      \
    } طالما (0)

#تعریف_کن sdl_sve_pixel_u16x4_foreach_chn_123a_321a(ma_منبع_u16x4,        \
                                                  ma_هدف_u16x4,        \
                                                  ...)                    \
    افعل {                                                                  \
        svuint16x4_t sve_منبع_u16x4 = ma_منبع_u16x4;                  \
        (فراغ)sve_منبع_u16x4;                                           \
        افعل {                                                              \
            ثابت uint8_t sve_src_chn_idx = 0;                            \
            ثابت uint8_t sve_dst_chn_idx = 0;                            \
            (فراغ)sve_src_chn_idx;                                        \
            (فراغ)sve_dst_chn_idx;                                        \
            svuint16_t sve_منبع_u16 = svget4((ma_منبع_u16x4), 0);     \
            svuint16_t sve_هدف_u16 = svget4((ma_هدف_u16x4), 0);     \
            (فراغ)sve_منبع_u16;                                         \
            (فراغ)sve_هدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_هدف_u16x4 = svset4(ma_هدف_u16x4, 0, sve_هدف_u16); \
        } طالما (0);                                                      \
        افعل {                                                              \
            ثابت uint8_t sve_src_chn_idx = 1;                            \
            ثابت uint8_t sve_dst_chn_idx = 3;                            \
            (فراغ)sve_src_chn_idx;                                        \
            (فراغ)sve_dst_chn_idx;                                        \
            svuint16_t sve_منبع_u16 = svget4((ma_منبع_u16x4), 1);     \
            svuint16_t sve_هدف_u16 = svget4((ma_هدف_u16x4), 3);     \
            (فراغ)sve_منبع_u16;                                         \
            (فراغ)sve_هدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_هدف_u16x4 = svset4(ma_هدف_u16x4, 3, sve_هدف_u16); \
        } طالما (0);                                                      \
        افعل {                                                              \
            ثابت uint8_t sve_src_chn_idx = 2;                            \
            ثابت uint8_t sve_dst_chn_idx = 2;                            \
            (فراغ)sve_src_chn_idx;                                        \
            (فراغ)sve_dst_chn_idx;                                        \
            svuint16_t sve_منبع_u16 = svget4((ma_منبع_u16x4), 2);     \
            svuint16_t sve_هدف_u16 = svget4((ma_هدف_u16x4), 2);     \
            (فراغ)sve_منبع_u16;                                         \
            (فراغ)sve_هدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_هدف_u16x4 = svset4(ma_هدف_u16x4, 2, sve_هدف_u16); \
        } طالما (0);                                                      \
        افعل {                                                              \
            ثابت uint8_t sve_src_chn_idx = 3;                            \
            ثابت uint8_t sve_dst_chn_idx = 1;                            \
            (فراغ)sve_src_chn_idx;                                        \
            (فراغ)sve_dst_chn_idx;                                        \
            svuint16_t sve_منبع_u16 = svget4((ma_منبع_u16x4), 3);     \
            svuint16_t sve_هدف_u16 = svget4((ma_هدف_u16x4), 1);     \
            (فراغ)sve_منبع_u16;                                         \
            (فراغ)sve_هدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_هدف_u16x4 = svset4(ma_هدف_u16x4, 1, sve_هدف_u16); \
        } طالما (0);                                                      \
    } طالما (0)

#تعریف_کن sdl_sve_pixel_u16x4_foreach_chn_argb_rgb565(ma_منبع_u16x4,      \
                                                    ma_هدف_u16x3,      \
                                                    ...)                  \
    افعل {                                                                  \
        svuint16x4_t sve_منبع_u16x4 = ma_منبع_u16x4;                  \
        (فراغ)sve_منبع_u16x4;                                           \
        افعل {                                                              \
            ثابت uint8_t sve_src_chn_idx = 0;                            \
            ثابت uint8_t sve_dst_chn_idx = 0;                            \
            (فراغ)sve_src_chn_idx;                                        \
            (فراغ)sve_dst_chn_idx;                                        \
            svuint16_t sve_منبع_u16 = svget4((ma_منبع_u16x4), 0);     \
            svuint16_t sve_هدف_u16 = svget3((ma_هدف_u16x3), 0);     \
            (فراغ)sve_منبع_u16;                                         \
            (فراغ)sve_هدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_هدف_u16x3 = svset3(ma_هدف_u16x3, 0, sve_هدف_u16); \
        } طالما (0);                                                      \
        افعل {                                                              \
            ثابت uint8_t sve_src_chn_idx = 1;                            \
            ثابت uint8_t sve_dst_chn_idx = 1;                            \
            (فراغ)sve_src_chn_idx;                                        \
            (فراغ)sve_dst_chn_idx;                                        \
            svuint16_t sve_منبع_u16 = svget4((ma_منبع_u16x4), 1);     \
            svuint16_t sve_هدف_u16 = svget3((ma_هدف_u16x3), 1);     \
            (فراغ)sve_منبع_u16;                                         \
            (فراغ)sve_هدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_هدف_u16x3 = svset3(ma_هدف_u16x3, 1, sve_هدف_u16); \
        } طالما (0);                                                      \
        افعل {                                                              \
            ثابت uint8_t sve_src_chn_idx = 2;                            \
            ثابت uint8_t sve_dst_chn_idx = 2;                            \
            (فراغ)sve_src_chn_idx;                                        \
            (فراغ)sve_dst_chn_idx;                                        \
            svuint16_t sve_منبع_u16 = svget4((ma_منبع_u16x4), 2);     \
            svuint16_t sve_هدف_u16 = svget3((ma_هدف_u16x3), 2);     \
            (فراغ)sve_منبع_u16;                                         \
            (فراغ)sve_هدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_هدف_u16x3 = svset3(ma_هدف_u16x3, 2, sve_هدف_u16); \
        } طالما (0);                                                      \
    } طالما (0)

#تعریف_کن sdl_sve_pixel_u16x4_foreach_chn_rgba_rgb565(ma_منبع_u16x4,      \
                                                    ma_هدف_u16x3,      \
                                                    ...)                  \
    افعل {                                                                  \
        svuint16x4_t sve_منبع_u16x4 = ma_منبع_u16x4;                  \
        (فراغ)sve_منبع_u16x4;                                           \
        افعل {                                                              \
            ثابت uint8_t sve_src_chn_idx = 1;                            \
            ثابت uint8_t sve_dst_chn_idx = 0;                            \
            (فراغ)sve_src_chn_idx;                                        \
            (فراغ)sve_dst_chn_idx;                                        \
            svuint16_t sve_منبع_u16 = svget4((ma_منبع_u16x4), 1);     \
            svuint16_t sve_هدف_u16 = svget3((ma_هدف_u16x3), 0);     \
            (فراغ)sve_منبع_u16;                                         \
            (فراغ)sve_هدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_هدف_u16x3 = svset3(ma_هدف_u16x3, 0, sve_هدف_u16); \
        } طالما (0);                                                      \
        افعل {                                                              \
            ثابت uint8_t sve_src_chn_idx = 2;                            \
            ثابت uint8_t sve_dst_chn_idx = 1;                            \
            (فراغ)sve_src_chn_idx;                                        \
            (فراغ)sve_dst_chn_idx;                                        \
            svuint16_t sve_منبع_u16 = svget4((ma_منبع_u16x4), 2);     \
            svuint16_t sve_هدف_u16 = svget3((ma_هدف_u16x3), 1);     \
            (فراغ)sve_منبع_u16;                                         \
            (فراغ)sve_هدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_هدف_u16x3 = svset3(ma_هدف_u16x3, 1, sve_هدف_u16); \
        } طالما (0);                                                      \
        افعل {                                                              \
            ثابت uint8_t sve_src_chn_idx = 3;                            \
            ثابت uint8_t sve_dst_chn_idx = 2;                            \
            (فراغ)sve_src_chn_idx;                                        \
            (فراغ)sve_dst_chn_idx;                                        \
            svuint16_t sve_منبع_u16 = svget4((ma_منبع_u16x4), 3);     \
            svuint16_t sve_هدف_u16 = svget3((ma_هدف_u16x3), 2);     \
            (فراغ)sve_منبع_u16;                                         \
            (فراغ)sve_هدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_هدف_u16x3 = svset3(ma_هدف_u16x3, 2, sve_هدف_u16); \
        } طالما (0);                                                      \
    } طالما (0)

#تعریف_کن sdl_sve_pixel_u16x4_foreach_chn_bgra_rgb565(ma_منبع_u16x4,      \
                                                    ma_هدف_u16x3,      \
                                                    ...)                  \
    افعل {                                                                  \
        svuint16x4_t sve_منبع_u16x4 = ma_منبع_u16x4;                  \
        (فراغ)sve_منبع_u16x4;                                           \
        افعل {                                                              \
            ثابت uint8_t sve_src_chn_idx = 3;                            \
            ثابت uint8_t sve_dst_chn_idx = 0;                            \
            (فراغ)sve_src_chn_idx;                                        \
            (فراغ)sve_dst_chn_idx;                                        \
            svuint16_t sve_منبع_u16 = svget4((ma_منبع_u16x4), 3);     \
            svuint16_t sve_هدف_u16 = svget3((ma_هدف_u16x3), 0);     \
            (فراغ)sve_منبع_u16;                                         \
            (فراغ)sve_هدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_هدف_u16x3 = svset3(ma_هدف_u16x3, 0, sve_هدف_u16); \
        } طالما (0);                                                      \
        افعل {                                                              \
            ثابت uint8_t sve_src_chn_idx = 2;                            \
            ثابت uint8_t sve_dst_chn_idx = 1;                            \
            (فراغ)sve_src_chn_idx;                                        \
            (فراغ)sve_dst_chn_idx;                                        \
            svuint16_t sve_منبع_u16 = svget4((ma_منبع_u16x4), 2);     \
            svuint16_t sve_هدف_u16 = svget3((ma_هدف_u16x3), 1);     \
            (فراغ)sve_منبع_u16;                                         \
            (فراغ)sve_هدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_هدف_u16x3 = svset3(ma_هدف_u16x3, 1, sve_هدف_u16); \
        } طالما (0);                                                      \
        افعل {                                                              \
            ثابت uint8_t sve_src_chn_idx = 1;                            \
            ثابت uint8_t sve_dst_chn_idx = 2;                            \
            (فراغ)sve_src_chn_idx;                                        \
            (فراغ)sve_dst_chn_idx;                                        \
            svuint16_t sve_منبع_u16 = svget4((ma_منبع_u16x4), 1);     \
            svuint16_t sve_هدف_u16 = svget3((ma_هدف_u16x3), 2);     \
            (فراغ)sve_منبع_u16;                                         \
            (فراغ)sve_هدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_هدف_u16x3 = svset3(ma_هدف_u16x3, 2, sve_هدف_u16); \
        } طالما (0);                                                      \
    } طالما (0)

#تعریف_کن sdl_sve_pixel_u16x4_foreach_chn_abgr_rgb565(ma_منبع_u16x4,      \
                                                    ma_هدف_u16x3,      \
                                                    ...)                  \
    افعل {                                                                  \
        svuint16x4_t sve_منبع_u16x4 = ma_منبع_u16x4;                  \
        (فراغ)sve_منبع_u16x4;                                           \
        افعل {                                                              \
            ثابت uint8_t sve_src_chn_idx = 2;                            \
            ثابت uint8_t sve_dst_chn_idx = 0;                            \
            (فراغ)sve_src_chn_idx;                                        \
            (فراغ)sve_dst_chn_idx;                                        \
            svuint16_t sve_منبع_u16 = svget4((ma_منبع_u16x4), 2);     \
            svuint16_t sve_هدف_u16 = svget3((ma_هدف_u16x3), 0);     \
            (فراغ)sve_منبع_u16;                                         \
            (فراغ)sve_هدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_هدف_u16x3 = svset3(ma_هدف_u16x3, 0, sve_هدف_u16); \
        } طالما (0);                                                      \
        افعل {                                                              \
            ثابت uint8_t sve_src_chn_idx = 1;                            \
            ثابت uint8_t sve_dst_chn_idx = 1;                            \
            (فراغ)sve_src_chn_idx;                                        \
            (فراغ)sve_dst_chn_idx;                                        \
            svuint16_t sve_منبع_u16 = svget4((ma_منبع_u16x4), 1);     \
            svuint16_t sve_هدف_u16 = svget3((ma_هدف_u16x3), 1);     \
            (فراغ)sve_منبع_u16;                                         \
            (فراغ)sve_هدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_هدف_u16x3 = svset3(ma_هدف_u16x3, 1, sve_هدف_u16); \
        } طالما (0);                                                      \
        افعل {                                                              \
            ثابت uint8_t sve_src_chn_idx = 0;                            \
            ثابت uint8_t sve_dst_chn_idx = 2;                            \
            (فراغ)sve_src_chn_idx;                                        \
            (فراغ)sve_dst_chn_idx;                                        \
            svuint16_t sve_منبع_u16 = svget4((ma_منبع_u16x4), 0);     \
            svuint16_t sve_هدف_u16 = svget3((ma_هدف_u16x3), 2);     \
            (فراغ)sve_منبع_u16;                                         \
            (فراغ)sve_هدف_u16;                                         \
            __VA_ARGS__                                                   \
            ma_هدف_u16x3 = svset3(ma_هدف_u16x3, 2, sve_هدف_u16); \
        } طالما (0);                                                      \
    } طالما (0)

SDL_TARGETING("arch=armv8-a+sve2")
ساكن مضمن svuint16x3_t sdl_sve_rgb565_unpack(svuint16_t vPixels)
{
    svuint16_t vBlue = svand_n_u16_m(svptrue_b16(), vPixels, 0x1F);
    svuint16_t vGreen = svand_n_u16_m(svptrue_b16(), vPixels, (0x3F << 5));
    svuint16_t vRed = svand_n_u16_m(svptrue_b16(), vPixels, (0x1F << 11));

    أرجع svcreate3_u16(svlsl_n_u16_m(svptrue_b16(), vBlue, 3),
                         svlsr_n_u16_m(svptrue_b16(), vGreen, 3),
                         svlsr_n_u16_m(svptrue_b16(), vRed, 8));
}

SDL_TARGETING("arch=armv8-a+sve2")
ساكن مضمن svuint16_t sdl_sve_rgb565_pack(svuint16x3_t vRGB16x3)
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
    أرجع svorr_u16_m(svptrue_b16(), vPixel, vBlue);

    // return  (svget3_u16(vRGB16x3, 0) >> 3)
    //     |   ((svget3_u16(vRGB16x3, 1) & (0x3F << 2)) << 3)
    //     |   ((svget3_u16(vRGB16x3, 2) & (0x1F << 3)) << 8);
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(2, 3, 4)
ساكن مضمن فراغ svld3rgb565_u16(svbool_t vPredu8,
                                   uint16_t *phw_منبع,
                                   svuint16x3_t *pv_کم,
                                   svuint16x3_t *pv_بالا)
{
    svuint8x2_t vInput8x2 = svld2_u8(vPredu8, (uint8_t *)phw_منبع);

    svuint16_t v_کم_Byte_کم_Half = svunpklo_u16(svget2_u8(vInput8x2, 0));
    svuint16_t v_کم_Byte_بالا_Half = svunpkhi_u16(svget2_u8(vInput8x2, 0));

    svuint16_t v_بالا_Byte_کم_Half = svunpklo_u16(svget2_u8(vInput8x2, 1));
    svuint16_t v_بالا_Byte_بالا_Half = svunpkhi_u16(svget2_u8(vInput8x2, 1));

    //*pvLow = sdl_sve_rgb565_unpack  (   vLowByteLowHalf
    //                                |   (vHighByteLowHalf << 8));
    *pv_کم = sdl_sve_rgb565_unpack(
        svorr_u16_m(svptrue_b16(),
                    v_کم_Byte_کم_Half,
                    //(vHighByteLowHalf << 8)
                    svlsl_n_u16_m(svptrue_b16(), v_بالا_Byte_کم_Half, 8)));

    //*pvHigh = sdl_sve_rgb565_unpack (   vLowByteHighHalf
    //                                |   (vHighByteHighHalf << 8));
    *pv_بالا = sdl_sve_rgb565_unpack(
        svorr_u16_m(svptrue_b16(),
                    v_کم_Byte_بالا_Half,
                    //(vHighByteHighHalf << 8)
                    svlsl_n_u16_m(svptrue_b16(), v_بالا_Byte_بالا_Half, 8)));
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(2)
ساكن مضمن فراغ svst3rgb565_u16(svbool_t vPredu8,
                                   uint16_t *phw_هدف,
                                   svuint16x3_t v_کم,
                                   svuint16x3_t v_بالا)
{
    svuint16_t v_کم_Byte_کم_Half = svundef_u16();
    svuint16_t v_بالا_Byte_کم_Half = svundef_u16();

    /* pack low half pixels */
    افعل {
        svuint16_t vPixel = sdl_sve_rgb565_pack(v_کم);

        // vLowByteLowHalf = vPixel & 0xFF;
        v_کم_Byte_کم_Half = svand_n_u16_m(svptrue_b16(), vPixel, 0xFF);

        // vHighByteLowHalf = vPixel >> 8;
        v_بالا_Byte_کم_Half = svlsr_n_u16_m(svptrue_b16(), vPixel, 8);
    } طالما (0);

    svuint16_t v_کم_Byte_بالا_Half = svundef_u16();
    svuint16_t v_بالا_Byte_بالا_Half = svundef_u16();

    /* pack high half pixels */
    افعل {
        svuint16_t vPixel = sdl_sve_rgb565_pack(v_بالا);

        // vLowByteHighHalf = vPixel & 0xFF;
        v_کم_Byte_بالا_Half = svand_n_u16_m(svptrue_b16(), vPixel, 0xFF);

        // vHighByteHighHalf = vPixel >> 8;
        v_بالا_Byte_بالا_Half = svlsr_n_u16_m(svptrue_b16(), vPixel, 8);
    } طالما (0);

    /* save rgb565 pixels */
    svuint8_t v_کم_Byte = svuzp1_u8(svreinterpret_u8(v_کم_Byte_کم_Half),
                                   svreinterpret_u8(v_کم_Byte_بالا_Half));

    svuint8_t v_بالا_Byte = svuzp1_u8(svreinterpret_u8(v_بالا_Byte_کم_Half),
                                    svreinterpret_u8(v_بالا_Byte_بالا_Half));

    svst2_u8(vPredu8, (uint8_t *)phw_هدف, svcreate2_u8(v_کم_Byte, v_بالا_Byte));
}

#إذا defined(__GNUC__) && !defined(__clang__)
#تعریف_کن svld4ub_u16(ma_pred,                                                                                         \
                    ma_src_ptr,                                                                                      \
                    ma_svuint16x4_کم_ptr,                                                                           \
                    ma_svuint16x4_بالا_ptr)                                                                          \
    افعل {                                                                                                             \
        svuint8x4_t vInput8x4 = svld4_u8((ma_pred), (ma_src_ptr));                                                   \
                                                                                                                     \
        *(ma_svuint16x4_کم_ptr) = svset4_u16(*(ma_svuint16x4_کم_ptr), 0, svunpklo_u16(svget4_u8(vInput8x4, 0)));   \
        *(ma_svuint16x4_کم_ptr) = svset4_u16(*(ma_svuint16x4_کم_ptr), 1, svunpklo_u16(svget4_u8(vInput8x4, 1)));   \
        *(ma_svuint16x4_کم_ptr) = svset4_u16(*(ma_svuint16x4_کم_ptr), 2, svunpklo_u16(svget4_u8(vInput8x4, 2)));   \
        *(ma_svuint16x4_کم_ptr) = svset4_u16(*(ma_svuint16x4_کم_ptr), 3, svunpklo_u16(svget4_u8(vInput8x4, 3)));   \
                                                                                                                     \
        *(ma_svuint16x4_بالا_ptr) = svset4_u16(*(ma_svuint16x4_بالا_ptr), 0, svunpkhi_u16(svget4_u8(vInput8x4, 0))); \
        *(ma_svuint16x4_بالا_ptr) = svset4_u16(*(ma_svuint16x4_بالا_ptr), 1, svunpkhi_u16(svget4_u8(vInput8x4, 1))); \
        *(ma_svuint16x4_بالا_ptr) = svset4_u16(*(ma_svuint16x4_بالا_ptr), 2, svunpkhi_u16(svget4_u8(vInput8x4, 2))); \
        *(ma_svuint16x4_بالا_ptr) = svset4_u16(*(ma_svuint16x4_بالا_ptr), 3, svunpkhi_u16(svget4_u8(vInput8x4, 3))); \
    } طالما (0)

#تعریف_کن svst4ub_u16(ma_pred,                                                                 \
                    ma_dst_ptr,                                                              \
                    ma_svuint16x4_کم,                                                       \
                    ma_svuint16x4_بالا)                                                      \
    افعل {                                                                                     \
        svuint8_t vCH0u8 = svuzp1_u8(svreinterpret_u8(svget4_u16((ma_svuint16x4_کم), 0)),   \
                                     svreinterpret_u8(svget4_u16((ma_svuint16x4_بالا), 0))); \
                                                                                             \
        svuint8_t vCH1u8 = svuzp1_u8(svreinterpret_u8(svget4_u16((ma_svuint16x4_کم), 1)),   \
                                     svreinterpret_u8(svget4_u16((ma_svuint16x4_بالا), 1))); \
                                                                                             \
        svuint8_t vCH2u8 = svuzp1_u8(svreinterpret_u8(svget4_u16((ma_svuint16x4_کم), 2)),   \
                                     svreinterpret_u8(svget4_u16((ma_svuint16x4_بالا), 2))); \
                                                                                             \
        svuint8_t vCH3u8 = svuzp1_u8(svreinterpret_u8(svget4_u16((ma_svuint16x4_کم), 3)),   \
                                     svreinterpret_u8(svget4_u16((ma_svuint16x4_بالا), 3))); \
                                                                                             \
        svst4_u8((ma_pred), (ma_dst_ptr), svcreate4_u8(vCH0u8, vCH1u8, vCH2u8, vCH3u8));     \
    } طالما (0)
#وإلا
SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(2, 3, 4)
ساكن مضمن فراغ svld4ub_u16(svbool_t vPredu8,
                               uint8_t *pch_منبع,
                               svuint16x4_t *pv_کم,
                               svuint16x4_t *pv_بالا)
{
    svuint8x4_t vInput8x4 = svld4_u8(vPredu8, pch_منبع);

    *pv_کم = svset4_u16(*pv_کم, 0, svunpklo_u16(svget4_u8(vInput8x4, 0)));
    *pv_کم = svset4_u16(*pv_کم, 1, svunpklo_u16(svget4_u8(vInput8x4, 1)));
    *pv_کم = svset4_u16(*pv_کم, 2, svunpklo_u16(svget4_u8(vInput8x4, 2)));
    *pv_کم = svset4_u16(*pv_کم, 3, svunpklo_u16(svget4_u8(vInput8x4, 3)));

    *pv_بالا = svset4_u16(*pv_بالا, 0, svunpkhi_u16(svget4_u8(vInput8x4, 0)));
    *pv_بالا = svset4_u16(*pv_بالا, 1, svunpkhi_u16(svget4_u8(vInput8x4, 1)));
    *pv_بالا = svset4_u16(*pv_بالا, 2, svunpkhi_u16(svget4_u8(vInput8x4, 2)));
    *pv_بالا = svset4_u16(*pv_بالا, 3, svunpkhi_u16(svget4_u8(vInput8x4, 3)));
}

SDL_TARGETING("arch=armv8-a+sve2")
ARM_NONNULL(2)
ساكن مضمن فراغ svst4ub_u16(svbool_t vPredu8,
                               uint8_t *pch_هدف,
                               svuint16x4_t v_کم,
                               svuint16x4_t v_بالا)
{

    svuint8_t vCH0u8 = svuzp1_u8(svreinterpret_u8(svget4_u16(v_کم, 0)),
                                 svreinterpret_u8(svget4_u16(v_بالا, 0)));

    svuint8_t vCH1u8 = svuzp1_u8(svreinterpret_u8(svget4_u16(v_کم, 1)),
                                 svreinterpret_u8(svget4_u16(v_بالا, 1)));

    svuint8_t vCH2u8 = svuzp1_u8(svreinterpret_u8(svget4_u16(v_کم, 2)),
                                 svreinterpret_u8(svget4_u16(v_بالا, 2)));

    svuint8_t vCH3u8 = svuzp1_u8(svreinterpret_u8(svget4_u16(v_کم, 3)),
                                 svreinterpret_u8(svget4_u16(v_بالا, 3)));

    svst4_u8(vPredu8, pch_هدف, svcreate4_u8(vCH0u8, vCH1u8, vCH2u8, vCH3u8));
}
#پایان_اگر

/*! \note the Element range of vMask is [0, 0xFF]
 */
SDL_TARGETING("arch=armv8-a+sve2")
ساكن مضمن svuint16_t sdl_sve_chn_blend_with_ماسک(svuint16_t v_منبع,
                                                     svuint16_t v_هدف,
                                                     svuint16_t v_ماسک)
{
    // vTarget = vSource * vMask + vTarget * (255 - vMask);
    svuint16_t vTemp0 = svdup_u16(1);
    vTemp0 = svmla_u16_m(svptrue_b16(), vTemp0, v_منبع, v_ماسک);
    vTemp0 = svmla_u16_m(svptrue_b16(),
                         vTemp0,
                         v_هدف,
                         svsub_u16_m(svptrue_b16(),
                                     svdup_u16(255),
                                     v_ماسک));

    /* x += x >> 8 */
    أرجع svreinterpret_u16_u8(
        svaddhnb_u16(vTemp0,
                     svlsr_n_u16_m(svptrue_b16(),
                                   vTemp0,
                                   8)));
}
/*! \note the Element range of vMask is [0, 0xFF]
 */
SDL_TARGETING("arch=armv8-a+sve2")
ساكن مضمن svuint16_t sdl_sve_chn_blend_with_ماسک_fast(svuint16_t v_منبع,
                                                          svuint16_t v_هدف,
                                                          svuint16_t v_ماسک)
{
    // vTarget = vSource * vMask + vTarget * (255 - vMask);
    svuint16_t vTemp0 = svmul_u16_m(svptrue_b16(), v_منبع, v_ماسک);
    vTemp0 = svmla_u16_m(svptrue_b16(),
                         vTemp0,
                         v_هدف,
                         svsub_u16_m(svptrue_b16(),
                                     svdup_u16(255),
                                     v_ماسک));

    أرجع svlsr_n_u16_m(svptrue_b16(), vTemp0, 8); // vTarget >> 8;
}

/*! \note the hwOpacity range [0, 0x100]
 */
SDL_TARGETING("arch=armv8-a+sve2")
ساكن مضمن svuint16_t sdl_sve_chn_blend_with_opacity(svuint16_t v_منبع,
                                                        svuint16_t v_هدف,
                                                        uint16_t hwOpacity)
{
    // svuint16_t vOpacity = svdup_u16(hwOpacity);
    // vTarget = vSource * vOpacity + vTarget * (256 - vOpacity);

    svuint16_t vTemp0 = svmul_n_u16_m(svptrue_b16(), v_منبع, hwOpacity);
    svuint16_t vTemp1 = svmul_n_u16_m(svptrue_b16(),
                                      v_هدف,
                                      256 - hwOpacity);
    v_هدف = svadd_u16_m(svptrue_b16(), vTemp0, vTemp1);

    أرجع svlsr_n_u16_m(svptrue_b16(), v_هدف, 8); // vTarget >> 8;
}

/*! \note the hwOpacity range [0, 0x100]
 */
SDL_TARGETING("arch=armv8-a+sve2")
ساكن مضمن svuint16_t sdl_sve_chn_blend_with_opacity_fast(svuint16_t v_منبع,
                                                             svuint16_t v_هدف,
                                                             uint16_t hwOpacity)
{
    // vTarget = vSource * vMask + vTarget * (255 - vMask);
    svuint16_t vTemp0 = svmul_n_u16_m(svptrue_b16(), v_منبع, hwOpacity);
    vTemp0 = svmla_n_u16_m(svptrue_b16(),
                           vTemp0,
                           v_هدف,
                           256 - hwOpacity);

    أرجع svlsr_n_u16_m(svptrue_b16(), vTemp0, 8); // vTarget >> 8;
}

/*! \note the Element range of vMask is [0, 0xFF]
 *  \note the hwOpacity range [0, 0x100]
 */
SDL_TARGETING("arch=armv8-a+sve2")
ساكن مضمن svuint16_t sdl_sve_chn_blend_with_ماسک_and_opacity(svuint16_t v_منبع,
                                                                 svuint16_t v_هدف,
                                                                 svuint16_t v_ماسک,
                                                                 uint16_t hwOpacity)
{
    v_ماسک = svsel(svcmpeq_n_u16(svptrue_b16(), v_ماسک, 255),
                  svdup_u16(hwOpacity),
                  //(vMask * hwOpacity) >> 8,
                  svlsr_n_u16_m(svptrue_b16(),
                                svmul_n_u16_m(svptrue_b16(), v_ماسک, hwOpacity),
                                8));

    // vTarget = vSource * vMask + vTarget * (256 - vMask);
    svuint16_t vTemp0 = svmul_u16_m(svptrue_b16(), v_منبع, v_ماسک);
    svuint16_t vTemp1 = svmul_u16_m(svptrue_b16(),
                                    v_هدف,
                                    svsub_u16_m(svptrue_b16(),
                                                svdup_u16(256),
                                                v_ماسک));
    v_هدف = svadd_u16_m(svptrue_b16(), vTemp0, vTemp1);

    أرجع svlsr_n_u16_m(svptrue_b16(), v_هدف, 8); // vTarget >> 8;
}

/*! \note the Element range of vMask0/1 is [0, 0xFF]
 */
SDL_TARGETING("arch=armv8-a+sve2")
ساكن مضمن svuint16_t sdl_sve_chn_blend_with_masks(svuint16_t v_منبع,
                                                      svuint16_t v_هدف,
                                                      svuint16_t vMask0,
                                                      svuint16_t vMask1)
{
    vMask1 = svadd_u16_m(svcmpeq_n_u16(svptrue_b16(), vMask1, 255),
                         vMask1,
                         svdup_u16(1));

    svuint16_t v_ماسک =
        svsel(svcmpge_n_u16(svptrue_b16(), vMask0, 255),
              vMask1,
              //(vMask0 * vMask1) >> 8,
              svlsr_n_u16_m(svptrue_b16(),
                            svmul_u16_m(svptrue_b16(), vMask0, vMask1),
                            8));

    // vTarget = vSource * vMask + vTarget * (256 - vMask);
    svuint16_t vTemp0 = svmul_u16_m(svptrue_b16(), v_منبع, v_ماسک);
    svuint16_t vTemp1 = svmul_u16_m(svptrue_b16(),
                                    v_هدف,
                                    svsub_u16_m(svptrue_b16(),
                                                svdup_u16(256),
                                                v_ماسک));
    v_هدف = svadd_u16_m(svptrue_b16(), vTemp0, vTemp1);

    أرجع svlsr_n_u16_m(svptrue_b16(), v_هدف, 8); // vTarget >> 8;
}

/*! \note the Element range of vMask0/1 is [0, 0xFF]
 *  \note the hwOpacity range [0, 0x100]
 */
SDL_TARGETING("arch=armv8-a+sve2")
ساكن مضمن svuint16_t sdl_sve_chn_blend_with_masks_and_opacity(
    svuint16_t v_منبع,
    svuint16_t v_هدف,
    svuint16_t vMask0,
    svuint16_t vMask1,
    uint16_t hwOpacity)
{
    vMask0 = svadd_u16_m(svcmpeq_n_u16(svptrue_b16(), vMask0, 255),
                         vMask0,
                         svdup_u16(1));

    svuint16_t v_ماسک =
        svsel(svcmpge_n_u16(svptrue_b16(), vMask1, 255), /* >= 255 */
              vMask0,
              //(vMask0 * vMask1) >> 8
              svlsr_n_u16_m(svptrue_b16(),
                            svmul_u16_m(svptrue_b16(), vMask0, vMask1),
                            8));

    v_ماسک =
        svsel(svcmpge_n_u16(svptrue_b16(), v_ماسک, 255),
              svdup_u16(hwOpacity),
              //(vMask * hwOpacity) >> 8,
              svlsr_n_u16_m(svptrue_b16(),
                            svmul_n_u16_m(svptrue_b16(), v_ماسک, hwOpacity),
                            8));

    // vTarget = vSource * vMask + vTarget * (256 - vMask);
    svuint16_t vTemp0 = svmul_u16_m(svptrue_b16(), v_منبع, v_ماسک);
    svuint16_t vTemp1 = svmul_u16_m(svptrue_b16(),
                                    v_هدف,
                                    svsub_u16_m(svptrue_b16(),
                                                svdup_u16(256),
                                                v_ماسک));
    v_هدف = svadd_u16_m(svptrue_b16(), vTemp0, vTemp1);

    أرجع svlsr_n_u16_m(svptrue_b16(), v_هدف, 8); // vTarget >> 8;
}

/*! \note the Element range of vMask0/1 is [0, 0xFF]
 */
SDL_TARGETING("arch=armv8-a+sve2")
ساكن مضمن svuint16_t sdl_sve_chn_blend_with_3masks(svuint16_t v_منبع,
                                                       svuint16_t v_هدف,
                                                       svuint16_t vMask0,
                                                       svuint16_t vMask1,
                                                       svuint16_t vMask2)
{
    vMask0 = svadd_u16_m(svcmpeq_n_u16(svptrue_b16(), vMask0, 255),
                         vMask0,
                         svdup_u16(1));

    svuint16_t v_ماسک =
        svsel(svcmpge_n_u16(svptrue_b16(), vMask1, 255),
              vMask0,
              //(vMask0 * vMask1) >> 8
              svlsr_n_u16_m(svptrue_b16(),
                            svmul_u16_m(svptrue_b16(), vMask0, vMask1),
                            8));

    v_ماسک =
        svsel(svcmpge_n_u16(svptrue_b16(), vMask2, 255),
              v_ماسک,
              //(vMask * vMask2) >> 8
              svlsr_n_u16_m(svptrue_b16(),
                            svmul_u16_m(svptrue_b16(), v_ماسک, vMask2),
                            8));

    // vTarget = vSource * vMask + vTarget * (256 - vMask);
    svuint16_t vTemp0 = svmul_u16_m(svptrue_b16(), v_منبع, v_ماسک);
    svuint16_t vTemp1 = svmul_u16_m(svptrue_b16(),
                                    v_هدف,
                                    svsub_u16_m(svptrue_b16(),
                                                svdup_u16(256),
                                                v_ماسک));
    v_هدف = svadd_u16_m(svptrue_b16(), vTemp0, vTemp1);

    أرجع svlsr_n_u16_m(svptrue_b16(), v_هدف, 8); // vTarget >> 8;
}

/*! \note the Element range of vMask0/1 is [0, 0xFF]
 *  \note the hwOpacity range [0, 0x100]
 */
SDL_TARGETING("arch=armv8-a+sve2")
ساكن مضمن svuint16_t sdl_sve_chn_blend_with_3masks_and_opacity(
    svuint16_t v_منبع,
    svuint16_t v_هدف,
    svuint16_t vMask0,
    svuint16_t vMask1,
    svuint16_t vMask2,
    uint16_t hwOpacity)
{
    vMask0 = svadd_u16_m(svcmpeq_n_u16(svptrue_b16(), vMask0, 255),
                         vMask0,
                         svdup_u16(1));

    svuint16_t v_ماسک =
        svsel(svcmpge_n_u16(svptrue_b16(), vMask1, 255),
              vMask0,
              //(vMask0 * vMask1) >> 8
              svlsr_n_u16_m(svptrue_b16(),
                            svmul_u16_m(svptrue_b16(), vMask0, vMask1),
                            8));

    v_ماسک =
        svsel(svcmpge_n_u16(svptrue_b16(), vMask2, 255),
              v_ماسک,
              svlsr_n_u16_m(svptrue_b16(),
                            svmul_u16_m(svptrue_b16(), v_ماسک, vMask2),
                            8));
    //(vMask * vMask2) >> 8);

    v_ماسک =
        svsel(svcmpge_n_u16(svptrue_b16(), v_ماسک, 255),
              svdup_u16(hwOpacity),
              //(vMask * hwOpacity) >> 8
              svlsr_n_u16_m(svptrue_b16(),
                            svmul_n_u16_m(svptrue_b16(), v_ماسک, hwOpacity),
                            8));

    // vTarget = vSource * vMask + vTarget * (256 - vMask);
    svuint16_t vTemp0 = svmul_u16_m(svptrue_b16(), v_منبع, v_ماسک);
    svuint16_t vTemp1 = svmul_u16_m(svptrue_b16(),
                                    v_هدف,
                                    svsub_u16_m(svptrue_b16(),
                                                svdup_u16(256),
                                                v_ماسک));
    v_هدف = svadd_u16_m(svptrue_b16(), vTemp0, vTemp1);

    أرجع svlsr_n_u16_m(svptrue_b16(), v_هدف, 8); // vTarget >> 8;
}

#پایان_اگر /* SDL_SVE2_EXTENSION_H */