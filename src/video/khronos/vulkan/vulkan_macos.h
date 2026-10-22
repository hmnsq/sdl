#جے_بنا_تعریف VULKAN_MACOS_H_
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


#جے_تعریف_شدہ __cplusplus
خارجي "C" {
#جے_انت



// VK_MVK_macos_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_MVK_macos_surface 1

#تعریف_کرو VK_MVK_MACOS_SURFACE_SPEC_نسخہ 3
#تعریف_کرو VK_MVK_MACOS_SURFACE_EXTENSION_NAME "VK_MVK_macos_surface"

تعريفنوع VkFlags VkMacOSSurfaceCreateFlagsMVK;

تعريفنوع بنية VkMacOSSurfaceCreateInfoMVK {
    VkStructureType                 sType;
    ثابت فراغ*                     p_اگلا;
    VkMacOSSurfaceCreateFlagsMVK    flags;
    ثابت فراغ*                     pView;
} VkMacOSSurfaceCreateInfoMVK;


تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vkCreateMacOSSurfaceMVK)(VkInstance instance, ثابت VkMacOSSurfaceCreateInfoMVK* pCreateInfo, ثابت Vk_ونڈ_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#جے_بنا_تعریف VK_NO_PROTOTYPES

#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vkCreateMacOSSurfaceMVK(
    VkInstance                                  instance,
    ثابت VkMacOSSurfaceCreateInfoMVK*          pCreateInfo,
    ثابت Vk_ونڈ_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#جے_انت
#جے_انت

#جے_تعریف_شدہ __cplusplus
}
#جے_انت

#جے_انت
