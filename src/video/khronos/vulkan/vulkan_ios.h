#ifndef VULKAN_IOS_H_
#define VULKAN_IOS_H_ 1

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



// VK_MVK_ios_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_MVK_ios_surface 1

#define VK_MVK_IOS_SURFACE_SPEC_VERSION   3
#define VK_MVK_IOS_SURFACE_EXTENSION_NAME "VK_MVK_ios_surface"

প্রকারনির্দেশ VkFlags VkIOSSurfaceCreateFlagsMVK;

প্রকারনির্দেশ সংরচনা VkIOSSurfaceCreateInfoMVK {
    VkStructureType               sType;
    ধ্রুৱ শূন্য*                   pNext;
    VkIOSSurfaceCreateFlagsMVK    flags;
    ধ্রুৱ শূন্য*                   pView;
} VkIOSSurfaceCreateInfoMVK;


প্রকারনির্দেশ VkResult (VKAPI_PTR *PFN_vkCreateIOSSurfaceMVK)(VkInstance instance, ধ্রুৱ VkIOSSurfaceCreateInfoMVK* pCreateInfo, ধ্রুৱ VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateIOSSurfaceMVK(
    VkInstance                                  instance,
    ধ্রুৱ VkIOSSurfaceCreateInfoMVK*            pCreateInfo,
    ধ্রুৱ VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif
