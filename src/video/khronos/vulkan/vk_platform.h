//
// File: vk_platform.h
//
/*
** Copyright 2014-2026 The Khronos Group Inc.
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/


#अगर_अघोषित VK_PLATFORM_H_
#घोषणा VK_PLATFORM_H_

#अगर_घोषित __cplusplus
बाह्य "C"
{
#पूर्ण_अगर // __cplusplus

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
#अगर defined(_WIN32) || defined(__CYGWIN__) /* __CYGWIN__ added by SDL */
    // On Windows, Vulkan commands use the stdcall convention
    #घोषणा VKAPI_ATTR
    #घोषणा VKAPI_CALL __stdcall
    #घोषणा VKAPI_PTR  VKAPI_CALL
#या_अगर defined(__ANDROID__) && defined(__ARM_ARCH) && __ARM_ARCH < 7
    #त्रुटि "Vulkan is not supported for the 'armeabi' NDK ABI"
#या_अगर defined(__ANDROID__) && defined(__ARM_ARCH) && __ARM_ARCH >= 7 && defined(__ARM_32BIT_STATE)
    // On Android 32-bit ARM targets, Vulkan functions use the "hardfloat"
    // calling convention, i.e. float parameters are passed in registers. This
    // is true even if the rest of the application passes floats on the stack,
    // as it does by default when compiling for the armeabi-v7a NDK ABI.
    #घोषणा VKAPI_ATTR __attribute__((pcs("aapcs-vfp")))
    #घोषणा VKAPI_CALL
    #घोषणा VKAPI_PTR  VKAPI_ATTR
#अन्यथा
    // On other platforms, use the default calling convention
    #घोषणा VKAPI_ATTR
    #घोषणा VKAPI_CALL
    #घोषणा VKAPI_PTR
#पूर्ण_अगर

#अगर !defined(VK_NO_STDDEF_H)
    #समावेश <stddef.h>
#पूर्ण_अगर // !defined(VK_NO_STDDEF_H)

#अगर !defined(VK_NO_STDINT_H)
    #अगर defined(_MSC_VER) && (_MSC_VER < 1600)
        प्रकार चिन्हित   __int8  int8_t;
        प्रकार अचिन्हित __int8  uint8_t;
        प्रकार चिन्हित   __int16 int16_t;
        प्रकार अचिन्हित __int16 uint16_t;
        प्रकार चिन्हित   __int32 int32_t;
        प्रकार अचिन्हित __int32 uint32_t;
        प्रकार चिन्हित   __int64 int64_t;
        प्रकार अचिन्हित __int64 uint64_t;
    #अन्यथा
        #समावेश <stdint.h>
    #पूर्ण_अगर
#पूर्ण_अगर // !defined(VK_NO_STDINT_H)

#अगर_घोषित __cplusplus
} // extern "C"
#पूर्ण_अगर // __cplusplus

#पूर्ण_अगर
