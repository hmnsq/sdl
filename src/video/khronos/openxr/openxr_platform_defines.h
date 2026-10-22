/*
** Copyright (c) 2017-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

#ifndef OPENXR_PLATFORM_DEFINES_H_
#define OPENXR_PLATFORM_DEFINES_H_ 1

#ifdef __cplusplus
வெளி "C" {
#endif

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
#எனில் defined(_WIN32)
#define XRAPI_ATTR
// On Windows, functions use the stdcall convention
#define XRAPI_CALL __stdcall
#define XRAPI_PTR XRAPI_CALL
#அல்லதெனில் defined(__ANDROID__) && defined(__ARM_ARCH) && __ARM_ARCH < 7
#error "API not supported for the 'armeabi' NDK ABI"
#அல்லதெனில் defined(__ANDROID__) && defined(__ARM_ARCH) && __ARM_ARCH >= 7 && defined(__ARM_32BIT_STATE)
// On Android 32-bit ARM targets, functions use the "hardfloat"
// calling convention, i.e. float parameters are passed in registers. This
// is true even if the rest of the application passes floats on the stack,
// as it does by default when compiling for the armeabi-v7a NDK ABI.
#define XRAPI_ATTR __attribute__((pcs("aapcs-vfp")))
#define XRAPI_CALL
#define XRAPI_PTR XRAPI_ATTR
#இல்லையெனில்
// On other platforms, use the default calling convention
#define XRAPI_ATTR
#define XRAPI_CALL
#define XRAPI_PTR
#endif

#அந்தர்பாவ <stddef.h>

#எனில் !defined(XR_NO_STDINT_H)
#எனில் defined(_MSC_VER) && (_MSC_VER < 1600)
வகைவரை signed __int8 int8_t;
வகைவரை unsigned __int8 uint8_t;
வகைவரை signed __int16 int16_t;
வகைவரை unsigned __int16 uint16_t;
வகைவரை signed __int32 int32_t;
வகைவரை unsigned __int32 uint32_t;
வகைவரை signed __int64 int64_t;
வகைவரை unsigned __int64 uint64_t;
#இல்லையெனில்
#அந்தர்பாவ <stdint.h>
#endif
#endif  // !defined( XR_NO_STDINT_H )

// XR_PTR_SIZE (in bytes)
#எனில் (defined(__LP64__) || defined(_WIN64) || (defined(__x86_64__) && !defined(__ILP32__) ) || defined(_M_X64) || defined(__ia64) || defined(_M_IA64) || defined(__aarch64__) || defined(__powerpc64__))
#define XR_PTR_SIZE 8
#இல்லையெனில்
#define XR_PTR_SIZE 4
#endif

// Needed so we can use clang __has_feature portably.
#எனில் !defined(XR_COMPILER_HAS_FEATURE)
#எனில் defined(__clang__)
#define XR_COMPILER_HAS_FEATURE(x) __has_feature(x)
#இல்லையெனில்
#define XR_COMPILER_HAS_FEATURE(x) 0
#endif
#endif

// Identifies if the current compiler has C++11 support enabled.
// Does not by itself identify if any given C++11 feature is present.
#எனில் !defined(XR_CPP11_ENABLED) && defined(__cplusplus)
#எனில் defined(__GNUC__) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#define XR_CPP11_ENABLED 1
#அல்லதெனில் defined(_MSC_VER) && (_MSC_VER >= 1600)
#define XR_CPP11_ENABLED 1
#அல்லதெனில் (__cplusplus >= 201103L) // 201103 is the first C++11 version.
#define XR_CPP11_ENABLED 1
#endif
#endif

// Identifies if the current compiler supports C++11 nullptr.
#எனில் !defined(XR_CPP_NULLPTR_SUPPORTED)
#எனில் defined(XR_CPP11_ENABLED) &&                                              \
    ((defined(__clang__) && XR_COMPILER_HAS_FEATURE(cxx_nullptr)) ||          \
     (defined(__GNUC__) && (((__GNUC__ * 1000) + __GNUC_MINOR__) >= 4006)) || \
     (defined(_MSC_VER) && (_MSC_VER >= 1600)) ||                             \
     (defined(__EDG_VERSION__) && (__EDG_VERSION__ >= 403)))
#define XR_CPP_NULLPTR_SUPPORTED 1
#endif
#endif

#எனில் !defined(XR_CPP_NULLPTR_SUPPORTED)
#define XR_CPP_NULLPTR_SUPPORTED 0
#endif  // !defined(XR_CPP_NULLPTR_SUPPORTED)

#ifdef __cplusplus
}
#endif

#endif
