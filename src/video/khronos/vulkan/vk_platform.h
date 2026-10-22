//
// File: vk_platform.h
//
/*
** Copyright 2014-2026 The Khronos Group Inc.
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/


#నిర్వచితం_కాకపోతే VK_PLATFORM_H_
#నిర్వచించు VK_PLATFORM_H_

#నిర్వచితమైతే __cplusplus
బాహ్య "C"
{
#అయితే_ముగింపు // __cplusplus

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
#ఒకవేళ defined(_WIN32) || defined(__CYGWIN__) /* __CYGWIN__ added by SDL */
    // On Windows, Vulkan commands use the stdcall convention
    #నిర్వచించు VKAPI_ATTR
    #నిర్వచించు VKAPI_CALL __stdcall
    #నిర్వచించు VKAPI_PTR  VKAPI_CALL
#లేదావేళ defined(__ANDROID__) && defined(__ARM_ARCH) && __ARM_ARCH < 7
    #దోషం "Vulkan is not supported for the 'armeabi' NDK ABI"
#లేదావేళ defined(__ANDROID__) && defined(__ARM_ARCH) && __ARM_ARCH >= 7 && defined(__ARM_32BIT_STATE)
    // On Android 32-bit ARM targets, Vulkan functions use the "hardfloat"
    // calling convention, i.e. float parameters are passed in registers. This
    // is true even if the rest of the application passes floats on the stack,
    // as it does by default when compiling for the armeabi-v7a NDK ABI.
    #నిర్వచించు VKAPI_ATTR __attribute__((pcs("aapcs-vfp")))
    #నిర్వచించు VKAPI_CALL
    #నిర్వచించు VKAPI_PTR  VKAPI_ATTR
#లేకపోతే
    // On other platforms, use the default calling convention
    #నిర్వచించు VKAPI_ATTR
    #నిర్వచించు VKAPI_CALL
    #నిర్వచించు VKAPI_PTR
#అయితే_ముగింపు

#ఒకవేళ !defined(VK_NO_STDDEF_H)
    #అన్తర్భావ <stddef.h>
#అయితే_ముగింపు // !defined(VK_NO_STDDEF_H)

#ఒకవేళ !defined(VK_NO_STDINT_H)
    #ఒకవేళ defined(_MSC_VER) && (_MSC_VER < 1600)
        రకనిర్వచనం గుర్తుగల   __int8  int8_t;
        రకనిర్వచనం గుర్తులేని __int8  uint8_t;
        రకనిర్వచనం గుర్తుగల   __int16 int16_t;
        రకనిర్వచనం గుర్తులేని __int16 uint16_t;
        రకనిర్వచనం గుర్తుగల   __int32 int32_t;
        రకనిర్వచనం గుర్తులేని __int32 uint32_t;
        రకనిర్వచనం గుర్తుగల   __int64 int64_t;
        రకనిర్వచనం గుర్తులేని __int64 uint64_t;
    #లేకపోతే
        #అన్తర్భావ <stdint.h>
    #అయితే_ముగింపు
#అయితే_ముగింపు // !defined(VK_NO_STDINT_H)

#నిర్వచితమైతే __cplusplus
} // extern "C"
#అయితే_ముగింపు // __cplusplus

#అయితే_ముగింపు
