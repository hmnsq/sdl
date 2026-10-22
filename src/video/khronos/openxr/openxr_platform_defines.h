/*
** Copyright (c) 2017-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

#अगर_अघोषित OPENXR_PLATFORM_DEFINES_H_
#घोषणा OPENXR_PLATFORM_DEFINES_H_ 1

#अगर_घोषित __cplusplus
बाह्य "C" {
#पूर्ण_अगर

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
#अगर defined(_WIN32)
#घोषणा XRAPI_ATTR
// On Windows, functions use the stdcall convention
#घोषणा XRAPI_CALL __stdcall
#घोषणा XRAPI_PTR XRAPI_CALL
#या_अगर defined(__ANDROID__) && defined(__ARM_ARCH) && __ARM_ARCH < 7
#त्रुटि "API not supported for the 'armeabi' NDK ABI"
#या_अगर defined(__ANDROID__) && defined(__ARM_ARCH) && __ARM_ARCH >= 7 && defined(__ARM_32BIT_STATE)
// On Android 32-bit ARM targets, functions use the "hardfloat"
// calling convention, i.e. float parameters are passed in registers. This
// is true even if the rest of the application passes floats on the stack,
// as it does by default when compiling for the armeabi-v7a NDK ABI.
#घोषणा XRAPI_ATTR __attribute__((pcs("aapcs-vfp")))
#घोषणा XRAPI_CALL
#घोषणा XRAPI_PTR XRAPI_ATTR
#अन्यथा
// On other platforms, use the default calling convention
#घोषणा XRAPI_ATTR
#घोषणा XRAPI_CALL
#घोषणा XRAPI_PTR
#पूर्ण_अगर

#समावेश <stddef.h>

#अगर !defined(XR_NO_STDINT_H)
#अगर defined(_MSC_VER) && (_MSC_VER < 1600)
प्रकार चिन्हित __int8 int8_t;
प्रकार अचिन्हित __int8 uint8_t;
प्रकार चिन्हित __int16 int16_t;
प्रकार अचिन्हित __int16 uint16_t;
प्रकार चिन्हित __int32 int32_t;
प्रकार अचिन्हित __int32 uint32_t;
प्रकार चिन्हित __int64 int64_t;
प्रकार अचिन्हित __int64 uint64_t;
#अन्यथा
#समावेश <stdint.h>
#पूर्ण_अगर
#पूर्ण_अगर  // !defined( XR_NO_STDINT_H )

// XR_PTR_SIZE (in bytes)
#अगर (defined(__LP64__) || defined(_WIN64) || (defined(__x86_64__) && !defined(__ILP32__) ) || defined(_M_X64) || defined(__ia64) || defined(_M_IA64) || defined(__aarch64__) || defined(__powerpc64__))
#घोषणा XR_PTR_आकार 8
#अन्यथा
#घोषणा XR_PTR_आकार 4
#पूर्ण_अगर

// Needed so we can use clang __has_feature portably.
#अगर !defined(XR_COMPILER_HAS_FEATURE)
#अगर defined(__clang__)
#घोषणा XR_COMPILER_HAS_FEATURE(x) __has_feature(x)
#अन्यथा
#घोषणा XR_COMPILER_HAS_FEATURE(x) 0
#पूर्ण_अगर
#पूर्ण_अगर

// Identifies if the current compiler has C++11 support enabled.
// Does not by itself identify if any given C++11 feature is present.
#अगर !defined(XR_CPP11_ENABLED) && defined(__cplusplus)
#अगर defined(__GNUC__) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#घोषणा XR_CPP11_ENABLED 1
#या_अगर defined(_MSC_VER) && (_MSC_VER >= 1600)
#घोषणा XR_CPP11_ENABLED 1
#या_अगर (__cplusplus >= 201103L) // 201103 is the first C++11 version.
#घोषणा XR_CPP11_ENABLED 1
#पूर्ण_अगर
#पूर्ण_अगर

// Identifies if the current compiler supports C++11 nullptr.
#अगर !defined(XR_CPP_NULLPTR_SUPPORTED)
#अगर defined(XR_CPP11_ENABLED) &&                                              \
    ((defined(__clang__) && XR_COMPILER_HAS_FEATURE(cxx_nullptr)) ||          \
     (defined(__GNUC__) && (((__GNUC__ * 1000) + __GNUC_MINOR__) >= 4006)) || \
     (defined(_MSC_VER) && (_MSC_VER >= 1600)) ||                             \
     (defined(__EDG_VERSION__) && (__EDG_VERSION__ >= 403)))
#घोषणा XR_CPP_NULLPTR_SUPPORTED 1
#पूर्ण_अगर
#पूर्ण_अगर

#अगर !defined(XR_CPP_NULLPTR_SUPPORTED)
#घोषणा XR_CPP_NULLPTR_SUPPORTED 0
#पूर्ण_अगर  // !defined(XR_CPP_NULLPTR_SUPPORTED)

#अगर_घोषित __cplusplus
}
#पूर्ण_अगर

#पूर्ण_अगर
