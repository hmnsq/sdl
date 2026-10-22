#ifndef VULKAN_UBM_H_
#define VULKAN_UBM_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#ifdef __cplusplus
வெளி "C" {
#endif



// VK_SEC_ubm_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_SEC_ubm_surface 1

#define VK_SEC_UBM_SURFACE_SPEC_VERSION   1
#define VK_SEC_UBM_SURFACE_EXTENSION_NAME "VK_SEC_ubm_surface"

வகைவரை VkFlags VkUbmSurfaceCreateFlagsSEC;

வகைவரை கட்டமைப்பு VkUbmSurfaceCreateInfoSEC {
    VkStructureType               sType;
    மாறிலி வெறுமை*                   pNext;
    VkUbmSurfaceCreateFlagsSEC    flags;
    கட்டமைப்பு ubm_device*            device;
    கட்டமைப்பு ubm_surface*           surface;
} VkUbmSurfaceCreateInfoSEC;


வகைவரை VkResult (VKAPI_PTR *PFN_vkCreateUbmSurfaceSEC)(VkInstance instance, மாறிலி VkUbmSurfaceCreateInfoSEC* pCreateInfo, மாறிலி VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
வகைவரை VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceUbmPresentationSupportSEC)(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, கட்டமைப்பு ubm_device* device);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateUbmSurfaceSEC(
    VkInstance                                  instance,
    மாறிலி VkUbmSurfaceCreateInfoSEC*            pCreateInfo,
    மாறிலி VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceUbmPresentationSupportSEC(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queueFamilyIndex,
    கட்டமைப்பு ubm_device*                          device);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif
