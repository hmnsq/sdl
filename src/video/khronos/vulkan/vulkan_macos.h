#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VULKAN_MACOS_H_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VULKAN_MACOS_H_ 1

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



// VK_MVK_macos_surface is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_MVK_macos_surface 1

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_MVK_MACOS_SURFACE_SPEC_ਸੰਸਕਰਣ 3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_MVK_MACOS_SURFACE_EXTENSION_NAME "VK_MVK_macos_surface"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ VkFlags VkMacOSSurfaceCreateFlagsMVK;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkMacOSSurfaceCreateInfoMVK {
    VkStructureType                 sType;
    ਅਚਲ ਖਾਲੀ*                     p_ਅਗਲਾ;
    VkMacOSSurfaceCreateFlagsMVK    flags;
    ਅਚਲ ਖਾਲੀ*                     pView;
} VkMacOSSurfaceCreateInfoMVK;


ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vkCreateMacOSSurfaceMVK)(VkInstance instance, ਅਚਲ VkMacOSSurfaceCreateInfoMVK* pCreateInfo, ਅਚਲ Vk_ਵੰਡ_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_NO_PROTOTYPES

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ਨਤੀਜਾ VKAPI_CALL vkCreateMacOSSurfaceMVK(
    VkInstance                                  instance,
    ਅਚਲ VkMacOSSurfaceCreateInfoMVK*          pCreateInfo,
    ਅਚਲ Vk_ਵੰਡ_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ
