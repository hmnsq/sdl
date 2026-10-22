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
बाह्य "C" {
#endif



// VK_EXT_directfb_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_directfb_surface 1

#define VK_EXT_DIRECTFB_SURFACE_SPEC_VERSION 1
#define VK_EXT_DIRECTFB_SURFACE_EXTENSION_NAME "VK_EXT_directfb_surface"

प्रकारव्याख्या VkFlags VkDirectFBSurfaceCreateFlagsEXT;

प्रकारव्याख्या संरचना VkDirectFBSurfaceCreateInfoEXT {
    VkStructureType                    sType;
    स्थिरांक शून्य*                        pNext;
    VkDirectFBSurfaceCreateFlagsEXT    flags;
    IDirectFB*                         dfb;
    IDirectFBSurface*                  surface;
} VkDirectFBSurfaceCreateInfoEXT;


प्रकारव्याख्या VkResult (VKAPI_PTR *PFN_vkCreateDirectFBSurfaceEXT)(VkInstance instance, स्थिरांक VkDirectFBSurfaceCreateInfoEXT* pCreateInfo, स्थिरांक VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
प्रकारव्याख्या VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceDirectFBPresentationSupportEXT)(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, IDirectFB* dfb);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateDirectFBSurfaceEXT(
    VkInstance                                  instance,
    स्थिरांक VkDirectFBSurfaceCreateInfoEXT*       pCreateInfo,
    स्थिरांक VkAllocationCallbacks*                pAllocator,
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
