//
// File: vk_platform.h
//
/*
** Copyright 2014-2026 The Khronos Group Inc.
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/


#यदि_अपरिभाषितम् VK_PLATFORM_H_
#परिभाषय VK_PLATFORM_H_

#यदि_परिभाषितम् __cplusplus
बाह्य "C"
{
#यदि_अन्तः // __cplusplus

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
#यदि defined(_WIN32) || defined(__CYGWIN__) /* __CYGWIN__ added by SDL */
    // On Windows, Vulkan commands use the stdcall convention
    #परिभाषय VKAPI_ATTR
    #परिभाषय VKAPI_CALL __stdcall
    #परिभाषय VKAPI_PTR  VKAPI_CALL
#नोचेद्यदि defined(__ANDROID__) && defined(__ARM_ARCH) && __ARM_ARCH < 7
    #दोषः "Vulkan is not supported for the 'armeabi' NDK ABI"
#नोचेद्यदि defined(__ANDROID__) && defined(__ARM_ARCH) && __ARM_ARCH >= 7 && defined(__ARM_32BIT_STATE)
    // On Android 32-bit ARM targets, Vulkan functions use the "hardfloat"
    // calling convention, i.e. float parameters are passed in registers. This
    // is true even if the rest of the application passes floats on the stack,
    // as it does by default when compiling for the armeabi-v7a NDK ABI.
    #परिभाषय VKAPI_ATTR __attribute__((pcs("aapcs-vfp")))
    #परिभाषय VKAPI_CALL
    #परिभाषय VKAPI_PTR  VKAPI_ATTR
#अन्यथा
    // On other platforms, use the default calling convention
    #परिभाषय VKAPI_ATTR
    #परिभाषय VKAPI_CALL
    #परिभाषय VKAPI_PTR
#यदि_अन्तः

#यदि !defined(VK_NO_STDDEF_H)
    #अन्तर्भाव <stddef.h>
#यदि_अन्तः // !defined(VK_NO_STDDEF_H)

#यदि !defined(VK_NO_STDINT_H)
    #यदि defined(_MSC_VER) && (_MSC_VER < 1600)
        प्रकारनिर्देश चिह्नित   __int8  int8_t;
        प्रकारनिर्देश अचिह्नित __int8  uint8_t;
        प्रकारनिर्देश चिह्नित   __int16 int16_t;
        प्रकारनिर्देश अचिह्नित __int16 uint16_t;
        प्रकारनिर्देश चिह्नित   __int32 int32_t;
        प्रकारनिर्देश अचिह्नित __int32 uint32_t;
        प्रकारनिर्देश चिह्नित   __int64 int64_t;
        प्रकारनिर्देश अचिह्नित __int64 uint64_t;
    #अन्यथा
        #अन्तर्भाव <stdint.h>
    #यदि_अन्तः
#यदि_अन्तः // !defined(VK_NO_STDINT_H)

#यदि_परिभाषितम् __cplusplus
} // extern "C"
#यदि_अन्तः // __cplusplus

#यदि_अन्तः
