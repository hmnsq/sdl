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
বাহ্যিক "C" {
#endif



// VK_KHR_wayland_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_wayland_surface 1

#define VK_KHR_WAYLAND_SURFACE_SPEC_VERSION 6
#define VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME "VK_KHR_wayland_surface"

প্রকারলেখ VkFlags VkWaylandSurfaceCreateFlagsKHR;

প্রকারলেখ কাঠামো VkWaylandSurfaceCreateInfoKHR {
    VkStructureType                   sType;
    ধ্রুবক শূন্য*                       p_পরবর্তী;
    VkWaylandSurfaceCreateFlagsKHR    flags;
    কাঠামো wl_display*                display;
    কাঠামো wl_surface*                surface;
} VkWaylandSurfaceCreateInfoKHR;


প্রকারলেখ Vk_ফলাফল (VKAPI_PTR *PFN_vkCreateWaylandSurfaceKHR)(VkInstance instance, ধ্রুবক VkWaylandSurfaceCreateInfoKHR* pCreateInfo, ধ্রুবক VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
প্রকারলেখ VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR)(VkPhysicalDevice physicalDevice, uint32_t queue_Family_সূচক, কাঠামো wl_display* display);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ফলাফল VKAPI_CALL vkCreateWaylandSurfaceKHR(
    VkInstance                                  instance,
    ধ্রুবক VkWaylandSurfaceCreateInfoKHR*        pCreateInfo,
    ধ্রুবক VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceWaylandPresentationSupportKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queue_Family_সূচক,
    কাঠামো wl_display*                          display);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif
