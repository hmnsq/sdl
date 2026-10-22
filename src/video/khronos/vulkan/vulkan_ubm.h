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
બાહ્ય "C" {
#endif



// VK_SEC_ubm_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_SEC_ubm_surface 1

#define VK_SEC_UBM_SURFACE_SPEC_VERSION   1
#define VK_SEC_UBM_SURFACE_EXTENSION_NAME "VK_SEC_ubm_surface"

પ્રકારવ્યાખ્યા VkFlags VkUbmSurfaceCreateFlagsSEC;

પ્રકારવ્યાખ્યા સંરચના VkUbmSurfaceCreateInfoSEC {
    VkStructureType               sType;
    અચલ શૂન્ય*                   pNext;
    VkUbmSurfaceCreateFlagsSEC    flags;
    સંરચના ubm_device*            device;
    સંરચના ubm_surface*           surface;
} VkUbmSurfaceCreateInfoSEC;


પ્રકારવ્યાખ્યા VkResult (VKAPI_PTR *PFN_vkCreateUbmSurfaceSEC)(VkInstance instance, અચલ VkUbmSurfaceCreateInfoSEC* pCreateInfo, અચલ VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
પ્રકારવ્યાખ્યા VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceUbmPresentationSupportSEC)(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, સંરચના ubm_device* device);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateUbmSurfaceSEC(
    VkInstance                                  instance,
    અચલ VkUbmSurfaceCreateInfoSEC*            pCreateInfo,
    અચલ VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceUbmPresentationSupportSEC(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queueFamilyIndex,
    સંરચના ubm_device*                          device);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif
