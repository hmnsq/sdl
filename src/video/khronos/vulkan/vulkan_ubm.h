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
বাহ্য "C" {
#endif



// VK_SEC_ubm_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_SEC_ubm_surface 1

#define VK_SEC_UBM_SURFACE_SPEC_VERSION   1
#define VK_SEC_UBM_SURFACE_EXTENSION_NAME "VK_SEC_ubm_surface"

প্রকারনির্দেশ VkFlags VkUbmSurfaceCreateFlagsSEC;

প্রকারনির্দেশ সংরচনা VkUbmSurfaceCreateInfoSEC {
    VkStructureType               sType;
    ধ্রুৱ শূন্য*                   pNext;
    VkUbmSurfaceCreateFlagsSEC    flags;
    সংরচনা ubm_device*            device;
    সংরচনা ubm_surface*           surface;
} VkUbmSurfaceCreateInfoSEC;


প্রকারনির্দেশ VkResult (VKAPI_PTR *PFN_vkCreateUbmSurfaceSEC)(VkInstance instance, ধ্রুৱ VkUbmSurfaceCreateInfoSEC* pCreateInfo, ধ্রুৱ VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
প্রকারনির্দেশ VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceUbmPresentationSupportSEC)(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, সংরচনা ubm_device* device);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateUbmSurfaceSEC(
    VkInstance                                  instance,
    ধ্রুৱ VkUbmSurfaceCreateInfoSEC*            pCreateInfo,
    ধ্রুৱ VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceUbmPresentationSupportSEC(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queueFamilyIndex,
    সংরচনা ubm_device*                          device);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif
