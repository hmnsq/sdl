#ifndef VULKAN_XLIB_H_
#define VULKAN_XLIB_H_ 1

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



// VK_KHR_xlib_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_xlib_surface 1

#define VK_KHR_XLIB_SURFACE_SPEC_VERSION  6
#define VK_KHR_XLIB_SURFACE_EXTENSION_NAME "VK_KHR_xlib_surface"

ಪ್ರಕಾರನಿರ್ದೇಶ VkFlags VkXlibSurfaceCreateFlagsKHR;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkXlibSurfaceCreateInfoKHR {
    VkStructureType                sType;
    ಧ್ರುವ ಶೂನ್ಯ*                    pNext;
    VkXlibSurfaceCreateFlagsKHR    flags;
    Display*                       dpy;
    Window                         window;
} VkXlibSurfaceCreateInfoKHR;


ಪ್ರಕಾರನಿರ್ದೇಶ VkResult (VKAPI_PTR *PFN_vkCreateXlibSurfaceKHR)(VkInstance instance, ಧ್ರುವ VkXlibSurfaceCreateInfoKHR* pCreateInfo, ಧ್ರುವ VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
ಪ್ರಕಾರನಿರ್ದೇಶ VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR)(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, Display* dpy, VisualID visualID);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateXlibSurfaceKHR(
    VkInstance                                  instance,
    ಧ್ರುವ VkXlibSurfaceCreateInfoKHR*           pCreateInfo,
    ಧ್ರುವ VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceXlibPresentationSupportKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queueFamilyIndex,
    Display*                                    dpy,
    VisualID                                    visualID);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif
