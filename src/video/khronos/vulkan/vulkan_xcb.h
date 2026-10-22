#ifndef VULKAN_XCB_H_
#define VULKAN_XCB_H_ 1

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



// VK_KHR_xcb_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_xcb_surface 1

#define VK_KHR_XCB_SURFACE_SPEC_VERSION   6
#define VK_KHR_XCB_SURFACE_EXTENSION_NAME "VK_KHR_xcb_surface"

প্রকারনির্দেশ VkFlags VkXcbSurfaceCreateFlagsKHR;

প্রকারনির্দেশ সংরচনা VkXcbSurfaceCreateInfoKHR {
    VkStructureType               sType;
    ধ্রুব শূন্য*                   pNext;
    VkXcbSurfaceCreateFlagsKHR    flags;
    xcb_connection_t*             connection;
    xcb_window_t                  window;
} VkXcbSurfaceCreateInfoKHR;


প্রকারনির্দেশ VkResult (VKAPI_PTR *PFN_vkCreateXcbSurfaceKHR)(VkInstance instance, ধ্রুব VkXcbSurfaceCreateInfoKHR* pCreateInfo, ধ্রুব VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
প্রকারনির্দেশ VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR)(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, xcb_connection_t* connection, xcb_visualid_t visual_id);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateXcbSurfaceKHR(
    VkInstance                                  instance,
    ধ্রুব VkXcbSurfaceCreateInfoKHR*            pCreateInfo,
    ধ্রুব VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceXcbPresentationSupportKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queueFamilyIndex,
    xcb_connection_t*                           connection,
    xcb_visualid_t                              visual_id);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif
