/*
** Copyright (c) 2017-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

#اگر_تعریف_نشده OPENXR_PLATFORM_تعریف_میکند_H
#تعریف_کن OPENXR_PLATFORM_تعریف_میکند_H 1

#اگر_تعریف_شده __cplusplus
خارجي "C" {
#پایان_اگر

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
#إذا defined(_WIN32)
#تعریف_کن XRAPI_ATTR
// On Windows, functions use the stdcall convention
#تعریف_کن XRAPI_CALL __stdcall
#تعریف_کن XRAPI_PTR XRAPI_CALL
#وإلاإذا defined(__ANDROID__) && defined(__ARM_ARCH) && __ARM_ARCH < 7
#خطا "API not supported for the 'armeabi' NDK ABI"
#وإلاإذا defined(__ANDROID__) && defined(__ARM_ARCH) && __ARM_ARCH >= 7 && defined(__ARM_32BIT_STATE)
// On Android 32-bit ARM targets, functions use the "hardfloat"
// calling convention, i.e. float parameters are passed in registers. This
// is true even if the rest of the application passes floats on the stack,
// as it does by default when compiling for the armeabi-v7a NDK ABI.
#تعریف_کن XRAPI_ATTR __attribute__((pcs("aapcs-vfp")))
#تعریف_کن XRAPI_CALL
#تعریف_کن XRAPI_PTR XRAPI_ATTR
#وإلا
// On other platforms, use the default calling convention
#تعریف_کن XRAPI_ATTR
#تعریف_کن XRAPI_CALL
#تعریف_کن XRAPI_PTR
#پایان_اگر

#ضمن <stddef.h>

#إذا !defined(XR_NO_STDINT_H)
#إذا defined(_MSC_VER) && (_MSC_VER < 1600)
تعريفنوع علامتدار __int8 int8_t;
تعريفنوع بیعلامت __int8 uint8_t;
تعريفنوع علامتدار __int16 int16_t;
تعريفنوع بیعلامت __int16 uint16_t;
تعريفنوع علامتدار __int32 int32_t;
تعريفنوع بیعلامت __int32 uint32_t;
تعريفنوع علامتدار __int64 int64_t;
تعريفنوع بیعلامت __int64 uint64_t;
#وإلا
#ضمن <stdint.h>
#پایان_اگر
#پایان_اگر  // !defined( XR_NO_STDINT_H )

// XR_PTR_SIZE (in bytes)
#إذا (defined(__LP64__) || defined(_WIN64) || (defined(__x86_64__) && !defined(__ILP32__) ) || defined(_M_X64) || defined(__ia64) || defined(_M_IA64) || defined(__aarch64__) || defined(__powerpc64__))
#تعریف_کن XR_PTR_اندازه 8
#وإلا
#تعریف_کن XR_PTR_اندازه 4
#پایان_اگر

// Needed so we can use clang __has_feature portably.
#إذا !defined(XR_COMPILER_HAS_FEATURE)
#إذا defined(__clang__)
#تعریف_کن XR_COMPILER_HAS_FEATURE(x) __has_feature(x)
#وإلا
#تعریف_کن XR_COMPILER_HAS_FEATURE(x) 0
#پایان_اگر
#پایان_اگر

// Identifies if the current compiler has C++11 support enabled.
// Does not by itself identify if any given C++11 feature is present.
#إذا !defined(XR_CPP11_ENABLED) && defined(__cplusplus)
#إذا defined(__GNUC__) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#تعریف_کن XR_CPP11_ENABLED 1
#وإلاإذا defined(_MSC_VER) && (_MSC_VER >= 1600)
#تعریف_کن XR_CPP11_ENABLED 1
#وإلاإذا (__cplusplus >= 201103L) // 201103 is the first C++11 version.
#تعریف_کن XR_CPP11_ENABLED 1
#پایان_اگر
#پایان_اگر

// Identifies if the current compiler supports C++11 nullptr.
#إذا !defined(XR_CPP_NULLPTR_SUPPORTED)
#إذا defined(XR_CPP11_ENABLED) &&                                              \
    ((defined(__clang__) && XR_COMPILER_HAS_FEATURE(cxx_nullptr)) ||          \
     (defined(__GNUC__) && (((__GNUC__ * 1000) + __GNUC_MINOR__) >= 4006)) || \
     (defined(_MSC_VER) && (_MSC_VER >= 1600)) ||                             \
     (defined(__EDG_VERSION__) && (__EDG_VERSION__ >= 403)))
#تعریف_کن XR_CPP_NULLPTR_SUPPORTED 1
#پایان_اگر
#پایان_اگر

#إذا !defined(XR_CPP_NULLPTR_SUPPORTED)
#تعریف_کن XR_CPP_NULLPTR_SUPPORTED 0
#پایان_اگر  // !defined(XR_CPP_NULLPTR_SUPPORTED)

#اگر_تعریف_شده __cplusplus
}
#پایان_اگر

#پایان_اگر
