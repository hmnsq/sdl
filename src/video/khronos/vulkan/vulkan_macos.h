#جيڪڏهن_وصف_نه_ٿيل VULKAN_MACOS_H_
#وصف_ڪريو VULKAN_MACOS_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#جيڪڏهن_وصف_ٿيل __cplusplus
خارجي "C" {
#جيڪڏهن_پورو



// VK_MVK_macos_surface is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو VK_MVK_macos_surface 1

#وصف_ڪريو VK_MVK_MACOS_SURFACE_SPEC_نسخو 3
#وصف_ڪريو VK_MVK_MACOS_SURFACE_EXTENSION_NAME "VK_MVK_macos_surface"

تعريفنوع VkFlags VkMacOSSurfaceCreateFlagsMVK;

تعريفنوع بنية VkMacOSSurfaceCreateInfoMVK {
    VkStructureType                 sType;
    ثابت فراغ*                     p_ايندڙ;
    VkMacOSSurfaceCreateFlagsMVK    flags;
    ثابت فراغ*                     pView;
} VkMacOSSurfaceCreateInfoMVK;


تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vkCreateMacOSSurfaceMVK)(VkInstance instance, ثابت VkMacOSSurfaceCreateInfoMVK* pCreateInfo, ثابت Vk_ورهاست_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#جيڪڏهن_وصف_نه_ٿيل VK_NO_PROTOTYPES

#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتيجو VKAPI_CALL vkCreateMacOSSurfaceMVK(
    VkInstance                                  instance,
    ثابت VkMacOSSurfaceCreateInfoMVK*          pCreateInfo,
    ثابت Vk_ورهاست_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#جيڪڏهن_پورو
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل __cplusplus
}
#جيڪڏهن_پورو

#جيڪڏهن_پورو
