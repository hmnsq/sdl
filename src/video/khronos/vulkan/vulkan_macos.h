#که_نه_تعریف_شوی VULKAN_MACOS_H_
#تعریف_کړه VULKAN_MACOS_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#که_تعریف_شوی __cplusplus
خارجي "C" {
#د_که_پای



// VK_MVK_macos_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه VK_MVK_macos_surface 1

#تعریف_کړه VK_MVK_MACOS_SURFACE_SPEC_نسخه 3
#تعریف_کړه VK_MVK_MACOS_SURFACE_EXTENSION_NAME "VK_MVK_macos_surface"

تعريفنوع VkFlags VkMacOSSurfaceCreateFlagsMVK;

تعريفنوع بنية VkMacOSSurfaceCreateInfoMVK {
    VkStructureType                 sType;
    ثابت فراغ*                     p_بل;
    VkMacOSSurfaceCreateFlagsMVK    flags;
    ثابت فراغ*                     pView;
} VkMacOSSurfaceCreateInfoMVK;


تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vkCreateMacOSSurfaceMVK)(VkInstance instance, ثابت VkMacOSSurfaceCreateInfoMVK* pCreateInfo, ثابت Vk_ویش_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#که_نه_تعریف_شوی VK_NO_PROTOTYPES

#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_پایله VKAPI_CALL vkCreateMacOSSurfaceMVK(
    VkInstance                                  instance,
    ثابت VkMacOSSurfaceCreateInfoMVK*          pCreateInfo,
    ثابت Vk_ویش_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#د_که_پای
#د_که_پای

#که_تعریف_شوی __cplusplus
}
#د_که_پای

#د_که_پای
