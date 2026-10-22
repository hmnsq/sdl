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
बाह्य "C" {
#endif



// VK_MVK_ios_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_MVK_ios_surface 1

#define VK_MVK_IOS_SURFACE_SPEC_VERSION   3
#define VK_MVK_IOS_SURFACE_EXTENSION_NAME "VK_MVK_ios_surface"

प्रकारनिर्देश VkFlags VkIOSSurfaceCreateFlagsMVK;

प्रकारनिर्देश संरचना VkIOSSurfaceCreateInfoMVK {
    VkStructureType               sType;
    अचर शून्य*                   pNext;
    VkIOSSurfaceCreateFlagsMVK    flags;
    अचर शून्य*                   pView;
} VkIOSSurfaceCreateInfoMVK;


प्रकारनिर्देश VkResult (VKAPI_PTR *PFN_vkCreateIOSSurfaceMVK)(VkInstance instance, अचर VkIOSSurfaceCreateInfoMVK* pCreateInfo, अचर VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateIOSSurfaceMVK(
    VkInstance                                  instance,
    अचर VkIOSSurfaceCreateInfoMVK*            pCreateInfo,
    अचर VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif
