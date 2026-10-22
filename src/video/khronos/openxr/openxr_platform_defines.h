/*
** Copyright (c) 2017-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

#నిర్వచితం_కాకపోతే OPENXR_PLATFORM_నిర్వచిస్తుంది_H
#నిర్వచించు OPENXR_PLATFORM_నిర్వచిస్తుంది_H 1

#నిర్వచితమైతే __cplusplus
బాహ్య "C" {
#అయితే_ముగింపు

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
#ఒకవేళ defined(_WIN32)
#నిర్వచించు XRAPI_ATTR
// On Windows, functions use the stdcall convention
#నిర్వచించు XRAPI_CALL __stdcall
#నిర్వచించు XRAPI_PTR XRAPI_CALL
#లేదావేళ defined(__ANDROID__) && defined(__ARM_ARCH) && __ARM_ARCH < 7
#దోషం "API not supported for the 'armeabi' NDK ABI"
#లేదావేళ defined(__ANDROID__) && defined(__ARM_ARCH) && __ARM_ARCH >= 7 && defined(__ARM_32BIT_STATE)
// On Android 32-bit ARM targets, functions use the "hardfloat"
// calling convention, i.e. float parameters are passed in registers. This
// is true even if the rest of the application passes floats on the stack,
// as it does by default when compiling for the armeabi-v7a NDK ABI.
#నిర్వచించు XRAPI_ATTR __attribute__((pcs("aapcs-vfp")))
#నిర్వచించు XRAPI_CALL
#నిర్వచించు XRAPI_PTR XRAPI_ATTR
#లేకపోతే
// On other platforms, use the default calling convention
#నిర్వచించు XRAPI_ATTR
#నిర్వచించు XRAPI_CALL
#నిర్వచించు XRAPI_PTR
#అయితే_ముగింపు

#అన్తర్భావ <stddef.h>

#ఒకవేళ !defined(XR_NO_STDINT_H)
#ఒకవేళ defined(_MSC_VER) && (_MSC_VER < 1600)
రకనిర్వచనం గుర్తుగల __int8 int8_t;
రకనిర్వచనం గుర్తులేని __int8 uint8_t;
రకనిర్వచనం గుర్తుగల __int16 int16_t;
రకనిర్వచనం గుర్తులేని __int16 uint16_t;
రకనిర్వచనం గుర్తుగల __int32 int32_t;
రకనిర్వచనం గుర్తులేని __int32 uint32_t;
రకనిర్వచనం గుర్తుగల __int64 int64_t;
రకనిర్వచనం గుర్తులేని __int64 uint64_t;
#లేకపోతే
#అన్తర్భావ <stdint.h>
#అయితే_ముగింపు
#అయితే_ముగింపు  // !defined( XR_NO_STDINT_H )

// XR_PTR_SIZE (in bytes)
#ఒకవేళ (defined(__LP64__) || defined(_WIN64) || (defined(__x86_64__) && !defined(__ILP32__) ) || defined(_M_X64) || defined(__ia64) || defined(_M_IA64) || defined(__aarch64__) || defined(__powerpc64__))
#నిర్వచించు XR_PTR_కొలత 8
#లేకపోతే
#నిర్వచించు XR_PTR_కొలత 4
#అయితే_ముగింపు

// Needed so we can use clang __has_feature portably.
#ఒకవేళ !defined(XR_COMPILER_HAS_FEATURE)
#ఒకవేళ defined(__clang__)
#నిర్వచించు XR_COMPILER_HAS_FEATURE(x) __has_feature(x)
#లేకపోతే
#నిర్వచించు XR_COMPILER_HAS_FEATURE(x) 0
#అయితే_ముగింపు
#అయితే_ముగింపు

// Identifies if the current compiler has C++11 support enabled.
// Does not by itself identify if any given C++11 feature is present.
#ఒకవేళ !defined(XR_CPP11_ENABLED) && defined(__cplusplus)
#ఒకవేళ defined(__GNUC__) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#నిర్వచించు XR_CPP11_ENABLED 1
#లేదావేళ defined(_MSC_VER) && (_MSC_VER >= 1600)
#నిర్వచించు XR_CPP11_ENABLED 1
#లేదావేళ (__cplusplus >= 201103L) // 201103 is the first C++11 version.
#నిర్వచించు XR_CPP11_ENABLED 1
#అయితే_ముగింపు
#అయితే_ముగింపు

// Identifies if the current compiler supports C++11 nullptr.
#ఒకవేళ !defined(XR_CPP_NULLPTR_SUPPORTED)
#ఒకవేళ defined(XR_CPP11_ENABLED) &&                                              \
    ((defined(__clang__) && XR_COMPILER_HAS_FEATURE(cxx_nullptr)) ||          \
     (defined(__GNUC__) && (((__GNUC__ * 1000) + __GNUC_MINOR__) >= 4006)) || \
     (defined(_MSC_VER) && (_MSC_VER >= 1600)) ||                             \
     (defined(__EDG_VERSION__) && (__EDG_VERSION__ >= 403)))
#నిర్వచించు XR_CPP_NULLPTR_SUPPORTED 1
#అయితే_ముగింపు
#అయితే_ముగింపు

#ఒకవేళ !defined(XR_CPP_NULLPTR_SUPPORTED)
#నిర్వచించు XR_CPP_NULLPTR_SUPPORTED 0
#అయితే_ముగింపు  // !defined(XR_CPP_NULLPTR_SUPPORTED)

#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు
