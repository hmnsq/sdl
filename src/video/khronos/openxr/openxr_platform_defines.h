/*
** Copyright (c) 2017-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

#جيڪڏهن_وصف_نه_ٿيل OPENXR_PLATFORM_مقرر_ڪري_H
#وصف_ڪريو OPENXR_PLATFORM_مقرر_ڪري_H 1

#جيڪڏهن_وصف_ٿيل __cplusplus
خارجي "C" {
#جيڪڏهن_پورو

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
#وصف_ڪريو XRAPI_ATTR
// On Windows, functions use the stdcall convention
#وصف_ڪريو XRAPI_CALL __stdcall
#وصف_ڪريو XRAPI_PTR XRAPI_CALL
#وإلاإذا defined(__ANDROID__) && defined(__ARM_ARCH) && __ARM_ARCH < 7
#غلطي "API not supported for the 'armeabi' NDK ABI"
#وإلاإذا defined(__ANDROID__) && defined(__ARM_ARCH) && __ARM_ARCH >= 7 && defined(__ARM_32BIT_STATE)
// On Android 32-bit ARM targets, functions use the "hardfloat"
// calling convention, i.e. float parameters are passed in registers. This
// is true even if the rest of the application passes floats on the stack,
// as it does by default when compiling for the armeabi-v7a NDK ABI.
#وصف_ڪريو XRAPI_ATTR __attribute__((pcs("aapcs-vfp")))
#وصف_ڪريو XRAPI_CALL
#وصف_ڪريو XRAPI_PTR XRAPI_ATTR
#وإلا
// On other platforms, use the default calling convention
#وصف_ڪريو XRAPI_ATTR
#وصف_ڪريو XRAPI_CALL
#وصف_ڪريو XRAPI_PTR
#جيڪڏهن_پورو

#ضمن <stddef.h>

#إذا !defined(XR_NO_STDINT_H)
#إذا defined(_MSC_VER) && (_MSC_VER < 1600)
تعريفنوع نشانوارو __int8 int8_t;
تعريفنوع بنانشان __int8 uint8_t;
تعريفنوع نشانوارو __int16 int16_t;
تعريفنوع بنانشان __int16 uint16_t;
تعريفنوع نشانوارو __int32 int32_t;
تعريفنوع بنانشان __int32 uint32_t;
تعريفنوع نشانوارو __int64 int64_t;
تعريفنوع بنانشان __int64 uint64_t;
#وإلا
#ضمن <stdint.h>
#جيڪڏهن_پورو
#جيڪڏهن_پورو  // !defined( XR_NO_STDINT_H )

// XR_PTR_SIZE (in bytes)
#إذا (defined(__LP64__) || defined(_WIN64) || (defined(__x86_64__) && !defined(__ILP32__) ) || defined(_M_X64) || defined(__ia64) || defined(_M_IA64) || defined(__aarch64__) || defined(__powerpc64__))
#وصف_ڪريو XR_PTR_سائيز 8
#وإلا
#وصف_ڪريو XR_PTR_سائيز 4
#جيڪڏهن_پورو

// Needed so we can use clang __has_feature portably.
#إذا !defined(XR_COMPILER_HAS_FEATURE)
#إذا defined(__clang__)
#وصف_ڪريو XR_COMPILER_HAS_FEATURE(x) __has_feature(x)
#وإلا
#وصف_ڪريو XR_COMPILER_HAS_FEATURE(x) 0
#جيڪڏهن_پورو
#جيڪڏهن_پورو

// Identifies if the current compiler has C++11 support enabled.
// Does not by itself identify if any given C++11 feature is present.
#إذا !defined(XR_CPP11_ENABLED) && defined(__cplusplus)
#إذا defined(__GNUC__) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#وصف_ڪريو XR_CPP11_ENABLED 1
#وإلاإذا defined(_MSC_VER) && (_MSC_VER >= 1600)
#وصف_ڪريو XR_CPP11_ENABLED 1
#وإلاإذا (__cplusplus >= 201103L) // 201103 is the first C++11 version.
#وصف_ڪريو XR_CPP11_ENABLED 1
#جيڪڏهن_پورو
#جيڪڏهن_پورو

// Identifies if the current compiler supports C++11 nullptr.
#إذا !defined(XR_CPP_NULLPTR_SUPPORTED)
#إذا defined(XR_CPP11_ENABLED) &&                                              \
    ((defined(__clang__) && XR_COMPILER_HAS_FEATURE(cxx_nullptr)) ||          \
     (defined(__GNUC__) && (((__GNUC__ * 1000) + __GNUC_MINOR__) >= 4006)) || \
     (defined(_MSC_VER) && (_MSC_VER >= 1600)) ||                             \
     (defined(__EDG_VERSION__) && (__EDG_VERSION__ >= 403)))
#وصف_ڪريو XR_CPP_NULLPTR_SUPPORTED 1
#جيڪڏهن_پورو
#جيڪڏهن_پورو

#إذا !defined(XR_CPP_NULLPTR_SUPPORTED)
#وصف_ڪريو XR_CPP_NULLPTR_SUPPORTED 0
#جيڪڏهن_پورو  // !defined(XR_CPP_NULLPTR_SUPPORTED)

#جيڪڏهن_وصف_ٿيل __cplusplus
}
#جيڪڏهن_پورو

#جيڪڏهن_پورو
