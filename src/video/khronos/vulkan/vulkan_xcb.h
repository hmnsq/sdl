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
বাহ্যিক "C" {
#endif



// VK_KHR_xcb_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_xcb_surface 1

#define VK_KHR_XCB_SURFACE_SPEC_VERSION   6
#define VK_KHR_XCB_SURFACE_EXTENSION_NAME "VK_KHR_xcb_surface"

প্রকারলেখ VkFlags VkXcbSurfaceCreateFlagsKHR;

প্রকারলেখ কাঠামো VkXcbSurfaceCreateInfoKHR {
    VkStructureType               sType;
    ধ্রুবক শূন্য*                   p_পরবর্তী;
    VkXcbSurfaceCreateFlagsKHR    flags;
    xcb_connection_t*             connection;
    xcb_window_t                  window;
} VkXcbSurfaceCreateInfoKHR;


প্রকারলেখ Vk_ফলাফল (VKAPI_PTR *PFN_vkCreateXcbSurfaceKHR)(VkInstance instance, ধ্রুবক VkXcbSurfaceCreateInfoKHR* pCreateInfo, ধ্রুবক VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
প্রকারলেখ VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR)(VkPhysicalDevice physicalDevice, uint32_t queue_Family_সূচক, xcb_connection_t* connection, xcb_visualid_t visual_id);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ফলাফল VKAPI_CALL vkCreateXcbSurfaceKHR(
    VkInstance                                  instance,
    ধ্রুবক VkXcbSurfaceCreateInfoKHR*            pCreateInfo,
    ধ্রুবক VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceXcbPresentationSupportKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queue_Family_সূচক,
    xcb_connection_t*                           connection,
    xcb_visualid_t                              visual_id);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif
