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
ବାହ୍ୟ "C" {
#endif



// VK_SEC_ubm_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_SEC_ubm_surface 1

#define VK_SEC_UBM_SURFACE_SPEC_VERSION   1
#define VK_SEC_UBM_SURFACE_EXTENSION_NAME "VK_SEC_ubm_surface"

ପ୍ରକାରବ୍ୟାଖ୍ୟା VkFlags VkUbmSurfaceCreateFlagsSEC;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkUbmSurfaceCreateInfoSEC {
    VkStructureType               sType;
    ଅଚଳ ଶୂନ୍ୟ*                   pNext;
    VkUbmSurfaceCreateFlagsSEC    flags;
    ସଂରଚନା ubm_device*            device;
    ସଂରଚନା ubm_surface*           surface;
} VkUbmSurfaceCreateInfoSEC;


ପ୍ରକାରବ୍ୟାଖ୍ୟା VkResult (VKAPI_PTR *PFN_vkCreateUbmSurfaceSEC)(VkInstance instance, ଅଚଳ VkUbmSurfaceCreateInfoSEC* pCreateInfo, ଅଚଳ VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
ପ୍ରକାରବ୍ୟାଖ୍ୟା VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceUbmPresentationSupportSEC)(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, ସଂରଚନା ubm_device* device);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateUbmSurfaceSEC(
    VkInstance                                  instance,
    ଅଚଳ VkUbmSurfaceCreateInfoSEC*            pCreateInfo,
    ଅଚଳ VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceUbmPresentationSupportSEC(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queueFamilyIndex,
    ସଂରଚନା ubm_device*                          device);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif
