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
બાહ્ય "C" {
#endif



// VK_EXT_directfb_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_directfb_surface 1

#define VK_EXT_DIRECTFB_SURFACE_SPEC_VERSION 1
#define VK_EXT_DIRECTFB_SURFACE_EXTENSION_NAME "VK_EXT_directfb_surface"

પ્રકારવ્યાખ્યા VkFlags VkDirectFBSurfaceCreateFlagsEXT;

પ્રકારવ્યાખ્યા સંરચના VkDirectFBSurfaceCreateInfoEXT {
    VkStructureType                    sType;
    અચલ શૂન્ય*                        pNext;
    VkDirectFBSurfaceCreateFlagsEXT    flags;
    IDirectFB*                         dfb;
    IDirectFBSurface*                  surface;
} VkDirectFBSurfaceCreateInfoEXT;


પ્રકારવ્યાખ્યા VkResult (VKAPI_PTR *PFN_vkCreateDirectFBSurfaceEXT)(VkInstance instance, અચલ VkDirectFBSurfaceCreateInfoEXT* pCreateInfo, અચલ VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
પ્રકારવ્યાખ્યા VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceDirectFBPresentationSupportEXT)(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, IDirectFB* dfb);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateDirectFBSurfaceEXT(
    VkInstance                                  instance,
    અચલ VkDirectFBSurfaceCreateInfoEXT*       pCreateInfo,
    અચલ VkAllocationCallbacks*                pAllocator,
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
