#ifndef VULKAN_WAYLAND_H_
#define VULKAN_WAYLAND_H_ 1

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



// VK_KHR_wayland_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_wayland_surface 1

#define VK_KHR_WAYLAND_SURFACE_SPEC_VERSION 6
#define VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME "VK_KHR_wayland_surface"

प्रकारनिर्देश VkFlags VkWaylandSurfaceCreateFlagsKHR;

प्रकारनिर्देश संरचना VkWaylandSurfaceCreateInfoKHR {
    VkStructureType                   sType;
    अचर शून्य*                       pNext;
    VkWaylandSurfaceCreateFlagsKHR    flags;
    संरचना wl_display*                display;
    संरचना wl_surface*                surface;
} VkWaylandSurfaceCreateInfoKHR;


प्रकारनिर्देश VkResult (VKAPI_PTR *PFN_vkCreateWaylandSurfaceKHR)(VkInstance instance, अचर VkWaylandSurfaceCreateInfoKHR* pCreateInfo, अचर VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
प्रकारनिर्देश VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR)(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, संरचना wl_display* display);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateWaylandSurfaceKHR(
    VkInstance                                  instance,
    अचर VkWaylandSurfaceCreateInfoKHR*        pCreateInfo,
    अचर VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceWaylandPresentationSupportKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queueFamilyIndex,
    संरचना wl_display*                          display);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif
