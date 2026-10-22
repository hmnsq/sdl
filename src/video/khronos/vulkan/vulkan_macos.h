#اگر_تعریف_نشده VULKAN_MACOS_H_
#تعریف_کن VULKAN_MACOS_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#اگر_تعریف_شده __cplusplus
خارجي "C" {
#پایان_اگر



// VK_MVK_macos_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کن VK_MVK_macos_surface 1

#تعریف_کن VK_MVK_MACOS_SURFACE_SPEC_نسخه 3
#تعریف_کن VK_MVK_MACOS_SURFACE_EXTENSION_NAME "VK_MVK_macos_surface"

تعريفنوع VkFlags VkMacOSSurfaceCreateFlagsMVK;

تعريفنوع بنية VkMacOSSurfaceCreateInfoMVK {
    VkStructureType                 sType;
    ثابت فراغ*                     p_بعدی;
    VkMacOSSurfaceCreateFlagsMVK    flags;
    ثابت فراغ*                     pView;
} VkMacOSSurfaceCreateInfoMVK;


تعريفنوع Vk_نتیجه (VKAPI_PTR *PFN_vkCreateMacOSSurfaceMVK)(VkInstance instance, ثابت VkMacOSSurfaceCreateInfoMVK* pCreateInfo, ثابت Vk_تخصیص_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#اگر_تعریف_نشده VK_NO_PROTOTYPES

#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجه VKAPI_CALL vkCreateMacOSSurfaceMVK(
    VkInstance                                  instance,
    ثابت VkMacOSSurfaceCreateInfoMVK*          pCreateInfo,
    ثابت Vk_تخصیص_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#پایان_اگر
#پایان_اگر

#اگر_تعریف_شده __cplusplus
}
#پایان_اگر

#پایان_اگر
