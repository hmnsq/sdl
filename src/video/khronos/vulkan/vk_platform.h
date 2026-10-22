//
// File: vk_platform.h
//
/*
** Copyright 2014-2026 The Khronos Group Inc.
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/


#جے_بنا_تعریف VK_PLATFORM_H_
#تعریف_کرو VK_PLATFORM_H_

#جے_تعریف_شدہ __cplusplus
خارجي "C"
{
#جے_انت // __cplusplus

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
#إذا defined(_WIN32) || defined(__CYGWIN__) /* __CYGWIN__ added by SDL */
    // On Windows, Vulkan commands use the stdcall convention
    #تعریف_کرو VKAPI_ATTR
    #تعریف_کرو VKAPI_CALL __stdcall
    #تعریف_کرو VKAPI_PTR  VKAPI_CALL
#وإلاإذا defined(__ANDROID__) && defined(__ARM_ARCH) && __ARM_ARCH < 7
    #غلطی "Vulkan is not supported for the 'armeabi' NDK ABI"
#وإلاإذا defined(__ANDROID__) && defined(__ARM_ARCH) && __ARM_ARCH >= 7 && defined(__ARM_32BIT_STATE)
    // On Android 32-bit ARM targets, Vulkan functions use the "hardfloat"
    // calling convention, i.e. float parameters are passed in registers. This
    // is true even if the rest of the application passes floats on the stack,
    // as it does by default when compiling for the armeabi-v7a NDK ABI.
    #تعریف_کرو VKAPI_ATTR __attribute__((pcs("aapcs-vfp")))
    #تعریف_کرو VKAPI_CALL
    #تعریف_کرو VKAPI_PTR  VKAPI_ATTR
#وإلا
    // On other platforms, use the default calling convention
    #تعریف_کرو VKAPI_ATTR
    #تعریف_کرو VKAPI_CALL
    #تعریف_کرو VKAPI_PTR
#جے_انت

#إذا !defined(VK_NO_STDDEF_H)
    #ضمن <stddef.h>
#جے_انت // !defined(VK_NO_STDDEF_H)

#إذا !defined(VK_NO_STDINT_H)
    #إذا defined(_MSC_VER) && (_MSC_VER < 1600)
        تعريفنوع نشانیوالا   __int8  int8_t;
        تعريفنوع بنانشانی __int8  uint8_t;
        تعريفنوع نشانیوالا   __int16 int16_t;
        تعريفنوع بنانشانی __int16 uint16_t;
        تعريفنوع نشانیوالا   __int32 int32_t;
        تعريفنوع بنانشانی __int32 uint32_t;
        تعريفنوع نشانیوالا   __int64 int64_t;
        تعريفنوع بنانشانی __int64 uint64_t;
    #وإلا
        #ضمن <stdint.h>
    #جے_انت
#جے_انت // !defined(VK_NO_STDINT_H)

#جے_تعریف_شدہ __cplusplus
} // extern "C"
#جے_انت // __cplusplus

#جے_انت
