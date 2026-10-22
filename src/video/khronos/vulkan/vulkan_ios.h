#اگر_غیر_تعریف_شدہ VULKAN_IOS_H_
#تعریف_کرو VULKAN_IOS_H_ 1

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



// VK_MVK_ios_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_MVK_ios_surface 1

#تعریف_کرو VK_MVK_IOS_SURFACE_SPEC_نسخہ   3
#تعریف_کرو VK_MVK_IOS_SURFACE_EXTENSION_NAME "VK_MVK_ios_surface"

قسمتعریف VkFlags VkIOSSurfaceCreateFlagsMVK;

قسمتعریف ساخت VkIOSSurfaceCreateInfoMVK {
    VkStructureType               sType;
    ثابت خالی*                   p_اگلا;
    VkIOSSurfaceCreateFlagsMVK    flags;
    ثابت خالی*                   pView;
} VkIOSSurfaceCreateInfoMVK;


قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vkCreateIOSSurfaceMVK)(VkInstance instance, ثابت VkIOSSurfaceCreateInfoMVK* pCreateInfo, ثابت Vk_تخصیص_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#اگر_غیر_تعریف_شدہ VK_NO_PROTOTYPES

#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vkCreateIOSSurfaceMVK(
    VkInstance                                  instance,
    ثابت VkIOSSurfaceCreateInfoMVK*            pCreateInfo,
    ثابت Vk_تخصیص_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#اگر_ختم
#اگر_ختم

#اگر_تعریف_شدہ __cplusplus
}
#اگر_ختم

#اگر_ختم
