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
بیرونی "C" {
#endif



// VK_SEC_ubm_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_SEC_ubm_surface 1

#define VK_SEC_UBM_SURFACE_SPEC_VERSION   1
#define VK_SEC_UBM_SURFACE_EXTENSION_NAME "VK_SEC_ubm_surface"

تعریفنوع VkFlags VkUbmSurfaceCreateFlagsSEC;

تعریفنوع ساختار VkUbmSurfaceCreateInfoSEC {
    VkStructureType               sType;
    ثابت تهی*                   pNext;
    VkUbmSurfaceCreateFlagsSEC    flags;
    ساختار ubm_device*            device;
    ساختار ubm_surface*           surface;
} VkUbmSurfaceCreateInfoSEC;


تعریفنوع VkResult (VKAPI_PTR *PFN_vkCreateUbmSurfaceSEC)(VkInstance instance, ثابت VkUbmSurfaceCreateInfoSEC* pCreateInfo, ثابت VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
تعریفنوع VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceUbmPresentationSupportSEC)(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, ساختار ubm_device* device);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateUbmSurfaceSEC(
    VkInstance                                  instance,
    ثابت VkUbmSurfaceCreateInfoSEC*            pCreateInfo,
    ثابت VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceUbmPresentationSupportSEC(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queueFamilyIndex,
    ساختار ubm_device*                          device);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif
