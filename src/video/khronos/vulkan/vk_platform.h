//
// File: vk_platform.h
//
/*
** Copyright 2014-2026 The Khronos Group Inc.
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/


#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_PLATFORM_H_
#ವ್ಯಾಖ್ಯಾನಿಸು VK_PLATFORM_H_

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
ಬಾಹ್ಯ "C"
{
#ಆದರೆ_ಅಂತ್ಯ // __cplusplus

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
#ಆದರೆ defined(_WIN32) || defined(__CYGWIN__) /* __CYGWIN__ added by SDL */
    // On Windows, Vulkan commands use the stdcall convention
    #ವ್ಯಾಖ್ಯಾನಿಸು VKAPI_ATTR
    #ವ್ಯಾಖ್ಯಾನಿಸು VKAPI_CALL __stdcall
    #ವ್ಯಾಖ್ಯಾನಿಸು VKAPI_PTR  VKAPI_CALL
#ಅಥವಾಆದರೆ defined(__ANDROID__) && defined(__ARM_ARCH) && __ARM_ARCH < 7
    #ದೋಷ "Vulkan is not supported for the 'armeabi' NDK ABI"
#ಅಥವಾಆದರೆ defined(__ANDROID__) && defined(__ARM_ARCH) && __ARM_ARCH >= 7 && defined(__ARM_32BIT_STATE)
    // On Android 32-bit ARM targets, Vulkan functions use the "hardfloat"
    // calling convention, i.e. float parameters are passed in registers. This
    // is true even if the rest of the application passes floats on the stack,
    // as it does by default when compiling for the armeabi-v7a NDK ABI.
    #ವ್ಯಾಖ್ಯಾನಿಸು VKAPI_ATTR __attribute__((pcs("aapcs-vfp")))
    #ವ್ಯಾಖ್ಯಾನಿಸು VKAPI_CALL
    #ವ್ಯಾಖ್ಯಾನಿಸು VKAPI_PTR  VKAPI_ATTR
#ಇಲ್ಲದಿದ್ದರೆ
    // On other platforms, use the default calling convention
    #ವ್ಯಾಖ್ಯಾನಿಸು VKAPI_ATTR
    #ವ್ಯಾಖ್ಯಾನಿಸು VKAPI_CALL
    #ವ್ಯಾಖ್ಯಾನಿಸು VKAPI_PTR
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ !defined(VK_NO_STDDEF_H)
    #ಅನ್ತರ್ಭಾವ <stddef.h>
#ಆದರೆ_ಅಂತ್ಯ // !defined(VK_NO_STDDEF_H)

#ಆದರೆ !defined(VK_NO_STDINT_H)
    #ಆದರೆ defined(_MSC_VER) && (_MSC_VER < 1600)
        ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆಯುಳ್ಳ   __int8  int8_t;
        ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆರಹಿತ __int8  uint8_t;
        ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆಯುಳ್ಳ   __int16 int16_t;
        ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆರಹಿತ __int16 uint16_t;
        ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆಯುಳ್ಳ   __int32 int32_t;
        ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆರಹಿತ __int32 uint32_t;
        ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆಯುಳ್ಳ   __int64 int64_t;
        ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆರಹಿತ __int64 uint64_t;
    #ಇಲ್ಲದಿದ್ದರೆ
        #ಅನ್ತರ್ಭಾವ <stdint.h>
    #ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ // !defined(VK_NO_STDINT_H)

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
} // extern "C"
#ಆದರೆ_ಅಂತ್ಯ // __cplusplus

#ಆದರೆ_ಅಂತ್ಯ
