/*
** Copyright (c) 2017-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

#यदि_अपरिभाषितम् OPENXR_PLATFORM_परिभाषते_H
#परिभाषय OPENXR_PLATFORM_परिभाषते_H 1

#यदि_परिभाषितम् __cplusplus
बाह्य "C" {
#यदि_अन्तः

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
#यदि defined(_WIN32)
#परिभाषय XRAPI_ATTR
// On Windows, functions use the stdcall convention
#परिभाषय XRAPI_CALL __stdcall
#परिभाषय XRAPI_PTR XRAPI_CALL
#नोचेद्यदि defined(__ANDROID__) && defined(__ARM_ARCH) && __ARM_ARCH < 7
#दोषः "API not supported for the 'armeabi' NDK ABI"
#नोचेद्यदि defined(__ANDROID__) && defined(__ARM_ARCH) && __ARM_ARCH >= 7 && defined(__ARM_32BIT_STATE)
// On Android 32-bit ARM targets, functions use the "hardfloat"
// calling convention, i.e. float parameters are passed in registers. This
// is true even if the rest of the application passes floats on the stack,
// as it does by default when compiling for the armeabi-v7a NDK ABI.
#परिभाषय XRAPI_ATTR __attribute__((pcs("aapcs-vfp")))
#परिभाषय XRAPI_CALL
#परिभाषय XRAPI_PTR XRAPI_ATTR
#अन्यथा
// On other platforms, use the default calling convention
#परिभाषय XRAPI_ATTR
#परिभाषय XRAPI_CALL
#परिभाषय XRAPI_PTR
#यदि_अन्तः

#अन्तर्भाव <stddef.h>

#यदि !defined(XR_NO_STDINT_H)
#यदि defined(_MSC_VER) && (_MSC_VER < 1600)
प्रकारनिर्देश चिह्नित __int8 int8_t;
प्रकारनिर्देश अचिह्नित __int8 uint8_t;
प्रकारनिर्देश चिह्नित __int16 int16_t;
प्रकारनिर्देश अचिह्नित __int16 uint16_t;
प्रकारनिर्देश चिह्नित __int32 int32_t;
प्रकारनिर्देश अचिह्नित __int32 uint32_t;
प्रकारनिर्देश चिह्नित __int64 int64_t;
प्रकारनिर्देश अचिह्नित __int64 uint64_t;
#अन्यथा
#अन्तर्भाव <stdint.h>
#यदि_अन्तः
#यदि_अन्तः  // !defined( XR_NO_STDINT_H )

// XR_PTR_SIZE (in bytes)
#यदि (defined(__LP64__) || defined(_WIN64) || (defined(__x86_64__) && !defined(__ILP32__) ) || defined(_M_X64) || defined(__ia64) || defined(_M_IA64) || defined(__aarch64__) || defined(__powerpc64__))
#परिभाषय XR_PTR_आकार 8
#अन्यथा
#परिभाषय XR_PTR_आकार 4
#यदि_अन्तः

// Needed so we can use clang __has_feature portably.
#यदि !defined(XR_COMPILER_HAS_FEATURE)
#यदि defined(__clang__)
#परिभाषय XR_COMPILER_HAS_FEATURE(x) __has_feature(x)
#अन्यथा
#परिभाषय XR_COMPILER_HAS_FEATURE(x) 0
#यदि_अन्तः
#यदि_अन्तः

// Identifies if the current compiler has C++11 support enabled.
// Does not by itself identify if any given C++11 feature is present.
#यदि !defined(XR_CPP11_ENABLED) && defined(__cplusplus)
#यदि defined(__GNUC__) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#परिभाषय XR_CPP11_ENABLED 1
#नोचेद्यदि defined(_MSC_VER) && (_MSC_VER >= 1600)
#परिभाषय XR_CPP11_ENABLED 1
#नोचेद्यदि (__cplusplus >= 201103L) // 201103 is the first C++11 version.
#परिभाषय XR_CPP11_ENABLED 1
#यदि_अन्तः
#यदि_अन्तः

// Identifies if the current compiler supports C++11 nullptr.
#यदि !defined(XR_CPP_NULLPTR_SUPPORTED)
#यदि defined(XR_CPP11_ENABLED) &&                                              \
    ((defined(__clang__) && XR_COMPILER_HAS_FEATURE(cxx_nullptr)) ||          \
     (defined(__GNUC__) && (((__GNUC__ * 1000) + __GNUC_MINOR__) >= 4006)) || \
     (defined(_MSC_VER) && (_MSC_VER >= 1600)) ||                             \
     (defined(__EDG_VERSION__) && (__EDG_VERSION__ >= 403)))
#परिभाषय XR_CPP_NULLPTR_SUPPORTED 1
#यदि_अन्तः
#यदि_अन्तः

#यदि !defined(XR_CPP_NULLPTR_SUPPORTED)
#परिभाषय XR_CPP_NULLPTR_SUPPORTED 0
#यदि_अन्तः  // !defined(XR_CPP_NULLPTR_SUPPORTED)

#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

#यदि_अन्तः
