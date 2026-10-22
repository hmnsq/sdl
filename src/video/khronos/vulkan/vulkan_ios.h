#جے_بنا_تعریف VULKAN_IOS_H_
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


#جے_تعریف_شدہ __cplusplus
خارجي "C" {
#جے_انت



// VK_MVK_ios_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_MVK_ios_surface 1

#تعریف_کرو VK_MVK_IOS_SURFACE_SPEC_نسخہ   3
#تعریف_کرو VK_MVK_IOS_SURFACE_EXTENSION_NAME "VK_MVK_ios_surface"

تعريفنوع VkFlags VkIOSSurfaceCreateFlagsMVK;

تعريفنوع بنية VkIOSSurfaceCreateInfoMVK {
    VkStructureType               sType;
    ثابت فراغ*                   p_اگلا;
    VkIOSSurfaceCreateFlagsMVK    flags;
    ثابت فراغ*                   pView;
} VkIOSSurfaceCreateInfoMVK;


تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vkCreateIOSSurfaceMVK)(VkInstance instance, ثابت VkIOSSurfaceCreateInfoMVK* pCreateInfo, ثابت Vk_ونڈ_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#جے_بنا_تعریف VK_NO_PROTOTYPES

#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vkCreateIOSSurfaceMVK(
    VkInstance                                  instance,
    ثابت VkIOSSurfaceCreateInfoMVK*            pCreateInfo,
    ثابت Vk_ونڈ_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#جے_انت
#جے_انت

#جے_تعریف_شدہ __cplusplus
}
#جے_انت

#جے_انت
