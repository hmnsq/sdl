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
بیرونی "C" {
#endif



// VK_MVK_macos_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_MVK_macos_surface 1

#define VK_MVK_MACOS_SURFACE_SPEC_VERSION 3
#define VK_MVK_MACOS_SURFACE_EXTENSION_NAME "VK_MVK_macos_surface"

تعریفنوع VkFlags VkMacOSSurfaceCreateFlagsMVK;

تعریفنوع ساختار VkMacOSSurfaceCreateInfoMVK {
    VkStructureType                 sType;
    ثابت تهی*                     pNext;
    VkMacOSSurfaceCreateFlagsMVK    flags;
    ثابت تهی*                     pView;
} VkMacOSSurfaceCreateInfoMVK;


تعریفنوع VkResult (VKAPI_PTR *PFN_vkCreateMacOSSurfaceMVK)(VkInstance instance, ثابت VkMacOSSurfaceCreateInfoMVK* pCreateInfo, ثابت VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateMacOSSurfaceMVK(
    VkInstance                                  instance,
    ثابت VkMacOSSurfaceCreateInfoMVK*          pCreateInfo,
    ثابت VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif
