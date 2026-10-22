//
// File: vk_platform.h
//
/*
** Copyright 2014-2026 The Khronos Group Inc.
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/


#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_PLATFORM_H_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_PLATFORM_H_

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
ਬਾਹਰੀ "C"
{
#ਜੇ_ਅੰਤ // __cplusplus

/*
***************************************************************************************************
*   Platform-specific directives and type declarations
***************************************************************************************************
*/

/* Platform-specific calling convention macros.
 *
 * Platforms should define these so that Vulkan clients call Vulkan commands
 * with the same calling conventions that the Vulkan implementation expects.
 *
 * VKAPI_ATTR - Placed before the return type in function declarations.
 *              Useful for C++11 and GCC/Clang-style function attribute syntax.
 * VKAPI_CALL - Placed after the return type in function declarations.
 *              Useful for MSVC-style calling convention syntax.
 * VKAPI_PTR  - Placed between the '(' and '*' in function pointer types.
 *
 * Function declaration:  VKAPI_ATTR void VKAPI_CALL vkCommand(void);
 * Function pointer type: typedef void (VKAPI_PTR *PFN_vkCommand)(void);
 */
#ਜੇ defined(_WIN32) || defined(__CYGWIN__) /* __CYGWIN__ added by SDL */
    // On Windows, Vulkan commands use the stdcall convention
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VKAPI_ATTR
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VKAPI_CALL __stdcall
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VKAPI_PTR  VKAPI_CALL
#ਜਾਂਜੇ defined(__ANDROID__) && defined(__ARM_ARCH) && __ARM_ARCH < 7
    #ਗਲਤੀ "Vulkan is not supported for the 'armeabi' NDK ABI"
#ਜਾਂਜੇ defined(__ANDROID__) && defined(__ARM_ARCH) && __ARM_ARCH >= 7 && defined(__ARM_32BIT_STATE)
    // On Android 32-bit ARM targets, Vulkan functions use the "hardfloat"
    // calling convention, i.e. float parameters are passed in registers. This
    // is true even if the rest of the application passes floats on the stack,
    // as it does by default when compiling for the armeabi-v7a NDK ABI.
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VKAPI_ATTR __attribute__((pcs("aapcs-vfp")))
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VKAPI_CALL
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VKAPI_PTR  VKAPI_ATTR
#ਨਹੀਂਤਾਂ
    // On other platforms, use the default calling convention
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VKAPI_ATTR
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VKAPI_CALL
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VKAPI_PTR
#ਜੇ_ਅੰਤ

#ਜੇ !defined(VK_NO_STDDEF_H)
    #ਅਨ੍ਤਰ੍ਭਾਵ <stddef.h>
#ਜੇ_ਅੰਤ // !defined(VK_NO_STDDEF_H)

#ਜੇ !defined(VK_NO_STDINT_H)
    #ਜੇ defined(_MSC_VER) && (_MSC_VER < 1600)
        ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਨਿਸ਼ਾਨੀਵਾਲਾ   __int8  int8_t;
        ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਿਨਾਨਿਸ਼ਾਨੀ __int8  uint8_t;
        ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਨਿਸ਼ਾਨੀਵਾਲਾ   __int16 int16_t;
        ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਿਨਾਨਿਸ਼ਾਨੀ __int16 uint16_t;
        ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਨਿਸ਼ਾਨੀਵਾਲਾ   __int32 int32_t;
        ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਿਨਾਨਿਸ਼ਾਨੀ __int32 uint32_t;
        ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਨਿਸ਼ਾਨੀਵਾਲਾ   __int64 int64_t;
        ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਿਨਾਨਿਸ਼ਾਨੀ __int64 uint64_t;
    #ਨਹੀਂਤਾਂ
        #ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
    #ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ // !defined(VK_NO_STDINT_H)

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
} // extern "C"
#ਜੇ_ਅੰਤ // __cplusplus

#ਜੇ_ਅੰਤ
