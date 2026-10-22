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
বাহ্যিক "C" {
#endif



// VK_KHR_xlib_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_xlib_surface 1

#define VK_KHR_XLIB_SURFACE_SPEC_VERSION  6
#define VK_KHR_XLIB_SURFACE_EXTENSION_NAME "VK_KHR_xlib_surface"

প্রকারলেখ VkFlags VkXlibSurfaceCreateFlagsKHR;

প্রকারলেখ কাঠামো VkXlibSurfaceCreateInfoKHR {
    VkStructureType                sType;
    ধ্রুবক শূন্য*                    p_পরবর্তী;
    VkXlibSurfaceCreateFlagsKHR    flags;
    Display*                       dpy;
    Window                         window;
} VkXlibSurfaceCreateInfoKHR;


প্রকারলেখ Vk_ফলাফল (VKAPI_PTR *PFN_vkCreateXlibSurfaceKHR)(VkInstance instance, ধ্রুবক VkXlibSurfaceCreateInfoKHR* pCreateInfo, ধ্রুবক VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
প্রকারলেখ VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR)(VkPhysicalDevice physicalDevice, uint32_t queue_Family_সূচক, Display* dpy, VisualID visualID);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ফলাফল VKAPI_CALL vkCreateXlibSurfaceKHR(
    VkInstance                                  instance,
    ধ্রুবক VkXlibSurfaceCreateInfoKHR*           pCreateInfo,
    ধ্রুবক VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceXlibPresentationSupportKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queue_Family_সূচক,
    Display*                                    dpy,
    VisualID                                    visualID);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif
