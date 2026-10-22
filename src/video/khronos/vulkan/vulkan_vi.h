#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VULKAN_VI_H_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VULKAN_VI_H_ 1

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



// VK_NN_vi_surface is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_NN_vi_surface 1

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_NN_VI_SURFACE_SPEC_ਸੰਸਕਰਣ     1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_NN_VI_SURFACE_EXTENSION_NAME   "VK_NN_vi_surface"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ VkFlags VkViSurfaceCreateFlagsNN;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkViSurfaceCreateInfoNN {
    VkStructureType             sType;
    ਅਚਲ ਖਾਲੀ*                 p_ਅਗਲਾ;
    VkViSurfaceCreateFlagsNN    flags;
    ਖਾਲੀ*                       ਖਿੜਕੀ;
} VkViSurfaceCreateInfoNN;


ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vkCreateViSurfaceNN)(VkInstance instance, ਅਚਲ VkViSurfaceCreateInfoNN* pCreateInfo, ਅਚਲ Vk_ਵੰਡ_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_NO_PROTOTYPES

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ਨਤੀਜਾ VKAPI_CALL vkCreateViSurfaceNN(
    VkInstance                                  instance,
    ਅਚਲ VkViSurfaceCreateInfoNN*              pCreateInfo,
    ਅਚਲ Vk_ਵੰਡ_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ
