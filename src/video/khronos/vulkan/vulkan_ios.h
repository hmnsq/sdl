#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VULKAN_IOS_H_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VULKAN_IOS_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ



// VK_MVK_ios_surface is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_MVK_ios_surface 1

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_MVK_IOS_SURFACE_SPEC_ਸੰਸਕਰਣ   3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_MVK_IOS_SURFACE_EXTENSION_NAME "VK_MVK_ios_surface"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ VkFlags VkIOSSurfaceCreateFlagsMVK;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkIOSSurfaceCreateInfoMVK {
    VkStructureType               sType;
    ਅਚਲ ਖਾਲੀ*                   p_ਅਗਲਾ;
    VkIOSSurfaceCreateFlagsMVK    flags;
    ਅਚਲ ਖਾਲੀ*                   pView;
} VkIOSSurfaceCreateInfoMVK;


ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vkCreateIOSSurfaceMVK)(VkInstance instance, ਅਚਲ VkIOSSurfaceCreateInfoMVK* pCreateInfo, ਅਚਲ Vk_ਵੰਡ_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_NO_PROTOTYPES

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ਨਤੀਜਾ VKAPI_CALL vkCreateIOSSurfaceMVK(
    VkInstance                                  instance,
    ਅਚਲ VkIOSSurfaceCreateInfoMVK*            pCreateInfo,
    ਅਚਲ Vk_ਵੰਡ_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ
