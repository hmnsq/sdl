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
बाह्य "C" {
#endif



// VK_SEC_ubm_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_SEC_ubm_surface 1

#define VK_SEC_UBM_SURFACE_SPEC_VERSION   1
#define VK_SEC_UBM_SURFACE_EXTENSION_NAME "VK_SEC_ubm_surface"

प्रकारव्याख्या VkFlags VkUbmSurfaceCreateFlagsSEC;

प्रकारव्याख्या संरचना VkUbmSurfaceCreateInfoSEC {
    VkStructureType               sType;
    स्थिरांक शून्य*                   pNext;
    VkUbmSurfaceCreateFlagsSEC    flags;
    संरचना ubm_device*            device;
    संरचना ubm_surface*           surface;
} VkUbmSurfaceCreateInfoSEC;


प्रकारव्याख्या VkResult (VKAPI_PTR *PFN_vkCreateUbmSurfaceSEC)(VkInstance instance, स्थिरांक VkUbmSurfaceCreateInfoSEC* pCreateInfo, स्थिरांक VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
प्रकारव्याख्या VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceUbmPresentationSupportSEC)(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, संरचना ubm_device* device);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateUbmSurfaceSEC(
    VkInstance                                  instance,
    स्थिरांक VkUbmSurfaceCreateInfoSEC*            pCreateInfo,
    स्थिरांक VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceUbmPresentationSupportSEC(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queueFamilyIndex,
    संरचना ubm_device*                          device);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif
