#ifndef VULKAN_DIRECTFB_H_
#define VULKAN_DIRECTFB_H_ 1

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
ಬಾಹ್ಯ "C" {
#endif



// VK_EXT_directfb_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_directfb_surface 1

#define VK_EXT_DIRECTFB_SURFACE_SPEC_VERSION 1
#define VK_EXT_DIRECTFB_SURFACE_EXTENSION_NAME "VK_EXT_directfb_surface"

ಪ್ರಕಾರನಿರ್ದೇಶ VkFlags VkDirectFBSurfaceCreateFlagsEXT;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkDirectFBSurfaceCreateInfoEXT {
    VkStructureType                    sType;
    ಧ್ರುವ ಶೂನ್ಯ*                        pNext;
    VkDirectFBSurfaceCreateFlagsEXT    flags;
    IDirectFB*                         dfb;
    IDirectFBSurface*                  surface;
} VkDirectFBSurfaceCreateInfoEXT;


ಪ್ರಕಾರನಿರ್ದೇಶ VkResult (VKAPI_PTR *PFN_vkCreateDirectFBSurfaceEXT)(VkInstance instance, ಧ್ರುವ VkDirectFBSurfaceCreateInfoEXT* pCreateInfo, ಧ್ರುವ VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
ಪ್ರಕಾರನಿರ್ದೇಶ VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceDirectFBPresentationSupportEXT)(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, IDirectFB* dfb);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateDirectFBSurfaceEXT(
    VkInstance                                  instance,
    ಧ್ರುವ VkDirectFBSurfaceCreateInfoEXT*       pCreateInfo,
    ಧ್ರುವ VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceDirectFBPresentationSupportEXT(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queueFamilyIndex,
    IDirectFB*                                  dfb);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif
