//
// File: vk_platform.h
//
/*
** Copyright 2014-2026 The Khronos Group Inc.
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/


#اگر_غیر_تعریف_شدہ VK_PLATFORM_H_
#تعریف_کرو VK_PLATFORM_H_

#اگر_تعریف_شدہ __cplusplus
خارجی "C"
{
#اگر_ختم // __cplusplus

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
#اگر defined(_WIN32) || defined(__CYGWIN__) /* __CYGWIN__ added by SDL */
    // On Windows, Vulkan commands use the stdcall convention
    #تعریف_کرو VKAPI_ATTR
    #تعریف_کرو VKAPI_CALL __stdcall
    #تعریف_کرو VKAPI_PTR  VKAPI_CALL
#وگرنہ_اگر defined(__ANDROID__) && defined(__ARM_ARCH) && __ARM_ARCH < 7
    #غلطی "Vulkan is not supported for the 'armeabi' NDK ABI"
#وگرنہ_اگر defined(__ANDROID__) && defined(__ARM_ARCH) && __ARM_ARCH >= 7 && defined(__ARM_32BIT_STATE)
    // On Android 32-bit ARM targets, Vulkan functions use the "hardfloat"
    // calling convention, i.e. float parameters are passed in registers. This
    // is true even if the rest of the application passes floats on the stack,
    // as it does by default when compiling for the armeabi-v7a NDK ABI.
    #تعریف_کرو VKAPI_ATTR __attribute__((pcs("aapcs-vfp")))
    #تعریف_کرو VKAPI_CALL
    #تعریف_کرو VKAPI_PTR  VKAPI_ATTR
#ورنہ
    // On other platforms, use the default calling convention
    #تعریف_کرو VKAPI_ATTR
    #تعریف_کرو VKAPI_CALL
    #تعریف_کرو VKAPI_PTR
#اگر_ختم

#اگر !defined(VK_NO_STDDEF_H)
    #شامل <stddef.h>
#اگر_ختم // !defined(VK_NO_STDDEF_H)

#اگر !defined(VK_NO_STDINT_H)
    #اگر defined(_MSC_VER) && (_MSC_VER < 1600)
        قسمتعریف علامتی   __int8  int8_t;
        قسمتعریف غیرعلامتی __int8  uint8_t;
        قسمتعریف علامتی   __int16 int16_t;
        قسمتعریف غیرعلامتی __int16 uint16_t;
        قسمتعریف علامتی   __int32 int32_t;
        قسمتعریف غیرعلامتی __int32 uint32_t;
        قسمتعریف علامتی   __int64 int64_t;
        قسمتعریف غیرعلامتی __int64 uint64_t;
    #ورنہ
        #شامل <stdint.h>
    #اگر_ختم
#اگر_ختم // !defined(VK_NO_STDINT_H)

#اگر_تعریف_شدہ __cplusplus
} // extern "C"
#اگر_ختم // __cplusplus

#اگر_ختم
