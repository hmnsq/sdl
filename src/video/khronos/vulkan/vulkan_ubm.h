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
বাহ্যিক "C" {
#endif



// VK_SEC_ubm_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_SEC_ubm_surface 1

#define VK_SEC_UBM_SURFACE_SPEC_VERSION   1
#define VK_SEC_UBM_SURFACE_EXTENSION_NAME "VK_SEC_ubm_surface"

প্রকারলেখ VkFlags VkUbmSurfaceCreateFlagsSEC;

প্রকারলেখ কাঠামো VkUbmSurfaceCreateInfoSEC {
    VkStructureType               sType;
    ধ্রুবক শূন্য*                   p_পরবর্তী;
    VkUbmSurfaceCreateFlagsSEC    flags;
    কাঠামো ubm_device*            device;
    কাঠামো ubm_surface*           surface;
} VkUbmSurfaceCreateInfoSEC;


প্রকারলেখ Vk_ফলাফল (VKAPI_PTR *PFN_vkCreateUbmSurfaceSEC)(VkInstance instance, ধ্রুবক VkUbmSurfaceCreateInfoSEC* pCreateInfo, ধ্রুবক VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
প্রকারলেখ VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceUbmPresentationSupportSEC)(VkPhysicalDevice physicalDevice, uint32_t queue_Family_সূচক, কাঠামো ubm_device* device);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ফলাফল VKAPI_CALL vkCreateUbmSurfaceSEC(
    VkInstance                                  instance,
    ধ্রুবক VkUbmSurfaceCreateInfoSEC*            pCreateInfo,
    ধ্রুবক VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceUbmPresentationSupportSEC(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queue_Family_সূচক,
    কাঠামো ubm_device*                          device);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif
