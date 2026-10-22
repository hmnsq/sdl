#اگر_تعریف_نشده VULKAN_IOS_H_
#تعریف_کن VULKAN_IOS_H_ 1

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



// VK_MVK_ios_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کن VK_MVK_ios_surface 1

#تعریف_کن VK_MVK_IOS_SURFACE_SPEC_نسخه   3
#تعریف_کن VK_MVK_IOS_SURFACE_EXTENSION_NAME "VK_MVK_ios_surface"

تعريفنوع VkFlags VkIOSSurfaceCreateFlagsMVK;

تعريفنوع بنية VkIOSSurfaceCreateInfoMVK {
    VkStructureType               sType;
    ثابت فراغ*                   p_بعدی;
    VkIOSSurfaceCreateFlagsMVK    flags;
    ثابت فراغ*                   pView;
} VkIOSSurfaceCreateInfoMVK;


تعريفنوع Vk_نتیجه (VKAPI_PTR *PFN_vkCreateIOSSurfaceMVK)(VkInstance instance, ثابت VkIOSSurfaceCreateInfoMVK* pCreateInfo, ثابت Vk_تخصیص_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#اگر_تعریف_نشده VK_NO_PROTOTYPES

#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجه VKAPI_CALL vkCreateIOSSurfaceMVK(
    VkInstance                                  instance,
    ثابت VkIOSSurfaceCreateInfoMVK*            pCreateInfo,
    ثابت Vk_تخصیص_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#پایان_اگر
#پایان_اگر

#اگر_تعریف_شده __cplusplus
}
#پایان_اگر

#پایان_اگر
