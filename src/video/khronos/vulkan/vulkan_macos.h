#اگر_غیر_تعریف_شدہ VULKAN_MACOS_H_
#تعریف_کرو VULKAN_MACOS_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#اگر_تعریف_شدہ __cplusplus
خارجی "C" {
#اگر_ختم



// VK_MVK_macos_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_MVK_macos_surface 1

#تعریف_کرو VK_MVK_MACOS_SURFACE_SPEC_نسخہ 3
#تعریف_کرو VK_MVK_MACOS_SURFACE_EXTENSION_NAME "VK_MVK_macos_surface"

قسمتعریف VkFlags VkMacOSSurfaceCreateFlagsMVK;

قسمتعریف ساخت VkMacOSSurfaceCreateInfoMVK {
    VkStructureType                 sType;
    ثابت خالی*                     p_اگلا;
    VkMacOSSurfaceCreateFlagsMVK    flags;
    ثابت خالی*                     pView;
} VkMacOSSurfaceCreateInfoMVK;


قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vkCreateMacOSSurfaceMVK)(VkInstance instance, ثابت VkMacOSSurfaceCreateInfoMVK* pCreateInfo, ثابت Vk_تخصیص_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#اگر_غیر_تعریف_شدہ VK_NO_PROTOTYPES

#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vkCreateMacOSSurfaceMVK(
    VkInstance                                  instance,
    ثابت VkMacOSSurfaceCreateInfoMVK*          pCreateInfo,
    ثابت Vk_تخصیص_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#اگر_ختم
#اگر_ختم

#اگر_تعریف_شدہ __cplusplus
}
#اگر_ختم

#اگر_ختم
