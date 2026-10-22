#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VULKAN_UBM_H_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VULKAN_UBM_H_ 1

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



// VK_SEC_ubm_surface is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_SEC_ubm_surface 1

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_SEC_UBM_SURFACE_SPEC_ਸੰਸਕਰਣ   1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_SEC_UBM_SURFACE_EXTENSION_NAME "VK_SEC_ubm_surface"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ VkFlags VkUbmSurfaceCreateFlagsSEC;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkUbmSurfaceCreateInfoSEC {
    VkStructureType               sType;
    ਅਚਲ ਖਾਲੀ*                   p_ਅਗਲਾ;
    VkUbmSurfaceCreateFlagsSEC    flags;
    ਬਣਤਰ ubm_device*            device;
    ਬਣਤਰ ubm_surface*           surface;
} VkUbmSurfaceCreateInfoSEC;


ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vkCreateUbmSurfaceSEC)(VkInstance instance, ਅਚਲ VkUbmSurfaceCreateInfoSEC* pCreateInfo, ਅਚਲ Vk_ਵੰਡ_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceUbmPresentationSupportSEC)(VkPhysicalDevice physicalDevice, uint32_t ਕਤਾਰ_Family_ਸੂਚਕਾਂਕ, ਬਣਤਰ ubm_device* device);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_NO_PROTOTYPES

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ਨਤੀਜਾ VKAPI_CALL vkCreateUbmSurfaceSEC(
    VkInstance                                  instance,
    ਅਚਲ VkUbmSurfaceCreateInfoSEC*            pCreateInfo,
    ਅਚਲ Vk_ਵੰਡ_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceUbmPresentationSupportSEC(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    ਕਤਾਰ_Family_ਸੂਚਕਾਂਕ,
    ਬਣਤਰ ubm_device*                          device);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ
