#ifndef VULKAN_MACOS_H_
#define VULKAN_MACOS_H_ 1

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



// VK_MVK_macos_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_MVK_macos_surface 1

#define VK_MVK_MACOS_SURFACE_SPEC_VERSION 3
#define VK_MVK_MACOS_SURFACE_EXTENSION_NAME "VK_MVK_macos_surface"

ପ୍ରକାରବ୍ୟାଖ୍ୟା VkFlags VkMacOSSurfaceCreateFlagsMVK;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkMacOSSurfaceCreateInfoMVK {
    VkStructureType                 sType;
    ଅଚଳ ଶୂନ୍ୟ*                     pNext;
    VkMacOSSurfaceCreateFlagsMVK    flags;
    ଅଚଳ ଶୂନ୍ୟ*                     pView;
} VkMacOSSurfaceCreateInfoMVK;


ପ୍ରକାରବ୍ୟାଖ୍ୟା VkResult (VKAPI_PTR *PFN_vkCreateMacOSSurfaceMVK)(VkInstance instance, ଅଚଳ VkMacOSSurfaceCreateInfoMVK* pCreateInfo, ଅଚଳ VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateMacOSSurfaceMVK(
    VkInstance                                  instance,
    ଅଚଳ VkMacOSSurfaceCreateInfoMVK*          pCreateInfo,
    ଅଚଳ VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif
