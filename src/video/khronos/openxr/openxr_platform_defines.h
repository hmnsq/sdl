/*
** Copyright (c) 2017-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ OPENXR_PLATFORM_ನಿರೂಪಿಸುತ್ತದೆ_H
#ವ್ಯಾಖ್ಯಾನಿಸು OPENXR_PLATFORM_ನಿರೂಪಿಸುತ್ತದೆ_H 1

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
ಬಾಹ್ಯ "C" {
#ಆದರೆ_ಅಂತ್ಯ

/* Platform-specific calling convention macros.
 *
 * Platforms should define these so that OpenXR clients call OpenXR functions
 * with the same calling conventions that the OpenXR implementation expects.
 *
 * XRAPI_ATTR - Placed before the return type in function declarations.
 *              Useful for C++11 and GCC/Clang-style function attribute syntax.
 * XRAPI_CALL - Placed after the return type in function declarations.
 *              Useful for MSVC-style calling convention syntax.
 * XRAPI_PTR  - Placed between the '(' and '*' in function pointer types.
 *
 * Function declaration:  XRAPI_ATTR void XRAPI_CALL xrFunction(void);
 * Function pointer type: typedef void (XRAPI_PTR *PFN_xrFunction)(void);
 */
#ಆದರೆ defined(_WIN32)
#ವ್ಯಾಖ್ಯಾನಿಸು XRAPI_ATTR
// On Windows, functions use the stdcall convention
#ವ್ಯಾಖ್ಯಾನಿಸು XRAPI_CALL __stdcall
#ವ್ಯಾಖ್ಯಾನಿಸು XRAPI_PTR XRAPI_CALL
#ಅಥವಾಆದರೆ defined(__ANDROID__) && defined(__ARM_ARCH) && __ARM_ARCH < 7
#ದೋಷ "API not supported for the 'armeabi' NDK ABI"
#ಅಥವಾಆದರೆ defined(__ANDROID__) && defined(__ARM_ARCH) && __ARM_ARCH >= 7 && defined(__ARM_32BIT_STATE)
// On Android 32-bit ARM targets, functions use the "hardfloat"
// calling convention, i.e. float parameters are passed in registers. This
// is true even if the rest of the application passes floats on the stack,
// as it does by default when compiling for the armeabi-v7a NDK ABI.
#ವ್ಯಾಖ್ಯಾನಿಸು XRAPI_ATTR __attribute__((pcs("aapcs-vfp")))
#ವ್ಯಾಖ್ಯಾನಿಸು XRAPI_CALL
#ವ್ಯಾಖ್ಯಾನಿಸು XRAPI_PTR XRAPI_ATTR
#ಇಲ್ಲದಿದ್ದರೆ
// On other platforms, use the default calling convention
#ವ್ಯಾಖ್ಯಾನಿಸು XRAPI_ATTR
#ವ್ಯಾಖ್ಯಾನಿಸು XRAPI_CALL
#ವ್ಯಾಖ್ಯಾನಿಸು XRAPI_PTR
#ಆದರೆ_ಅಂತ್ಯ

#ಅನ್ತರ್ಭಾವ <stddef.h>

#ಆದರೆ !defined(XR_NO_STDINT_H)
#ಆದರೆ defined(_MSC_VER) && (_MSC_VER < 1600)
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆಯುಳ್ಳ __int8 int8_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆರಹಿತ __int8 uint8_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆಯುಳ್ಳ __int16 int16_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆರಹಿತ __int16 uint16_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆಯುಳ್ಳ __int32 int32_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆರಹಿತ __int32 uint32_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆಯುಳ್ಳ __int64 int64_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆರಹಿತ __int64 uint64_t;
#ಇಲ್ಲದಿದ್ದರೆ
#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ  // !defined( XR_NO_STDINT_H )

// XR_PTR_SIZE (in bytes)
#ಆದರೆ (defined(__LP64__) || defined(_WIN64) || (defined(__x86_64__) && !defined(__ILP32__) ) || defined(_M_X64) || defined(__ia64) || defined(_M_IA64) || defined(__aarch64__) || defined(__powerpc64__))
#ವ್ಯಾಖ್ಯಾನಿಸು XR_PTR_ಗಾತ್ರ 8
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು XR_PTR_ಗಾತ್ರ 4
#ಆದರೆ_ಅಂತ್ಯ

// Needed so we can use clang __has_feature portably.
#ಆದರೆ !defined(XR_COMPILER_HAS_FEATURE)
#ಆದರೆ defined(__clang__)
#ವ್ಯಾಖ್ಯಾನಿಸು XR_COMPILER_HAS_FEATURE(x) __has_feature(x)
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು XR_COMPILER_HAS_FEATURE(x) 0
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ

// Identifies if the current compiler has C++11 support enabled.
// Does not by itself identify if any given C++11 feature is present.
#ಆದರೆ !defined(XR_CPP11_ENABLED) && defined(__cplusplus)
#ಆದರೆ defined(__GNUC__) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#ವ್ಯಾಖ್ಯಾನಿಸು XR_CPP11_ENABLED 1
#ಅಥವಾಆದರೆ defined(_MSC_VER) && (_MSC_VER >= 1600)
#ವ್ಯಾಖ್ಯಾನಿಸು XR_CPP11_ENABLED 1
#ಅಥವಾಆದರೆ (__cplusplus >= 201103L) // 201103 is the first C++11 version.
#ವ್ಯಾಖ್ಯಾನಿಸು XR_CPP11_ENABLED 1
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ

// Identifies if the current compiler supports C++11 nullptr.
#ಆದರೆ !defined(XR_CPP_NULLPTR_SUPPORTED)
#ಆದರೆ defined(XR_CPP11_ENABLED) &&                                              \
    ((defined(__clang__) && XR_COMPILER_HAS_FEATURE(cxx_nullptr)) ||          \
     (defined(__GNUC__) && (((__GNUC__ * 1000) + __GNUC_MINOR__) >= 4006)) || \
     (defined(_MSC_VER) && (_MSC_VER >= 1600)) ||                             \
     (defined(__EDG_VERSION__) && (__EDG_VERSION__ >= 403)))
#ವ್ಯಾಖ್ಯಾನಿಸು XR_CPP_NULLPTR_SUPPORTED 1
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ !defined(XR_CPP_NULLPTR_SUPPORTED)
#ವ್ಯಾಖ್ಯಾನಿಸು XR_CPP_NULLPTR_SUPPORTED 0
#ಆದರೆ_ಅಂತ್ಯ  // !defined(XR_CPP_NULLPTR_SUPPORTED)

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ
