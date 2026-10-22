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
बाह्य "C" {
#endif



// VK_KHR_xlib_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_xlib_surface 1

#define VK_KHR_XLIB_SURFACE_SPEC_VERSION  6
#define VK_KHR_XLIB_SURFACE_EXTENSION_NAME "VK_KHR_xlib_surface"

प्रकारव्याख्या VkFlags VkXlibSurfaceCreateFlagsKHR;

प्रकारव्याख्या संरचना VkXlibSurfaceCreateInfoKHR {
    VkStructureType                sType;
    स्थिरांक शून्य*                    pNext;
    VkXlibSurfaceCreateFlagsKHR    flags;
    Display*                       dpy;
    Window                         window;
} VkXlibSurfaceCreateInfoKHR;


प्रकारव्याख्या VkResult (VKAPI_PTR *PFN_vkCreateXlibSurfaceKHR)(VkInstance instance, स्थिरांक VkXlibSurfaceCreateInfoKHR* pCreateInfo, स्थिरांक VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
प्रकारव्याख्या VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR)(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, Display* dpy, VisualID visualID);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateXlibSurfaceKHR(
    VkInstance                                  instance,
    स्थिरांक VkXlibSurfaceCreateInfoKHR*           pCreateInfo,
    स्थिरांक VkAllocationCallbacks*                pAllocator,
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
