#جيڪڏهن_وصف_نه_ٿيل VULKAN_XCB_H_
#وصف_ڪريو VULKAN_XCB_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#جيڪڏهن_وصف_ٿيل __cplusplus
خارجي "C" {
#جيڪڏهن_پورو



// VK_KHR_xcb_surface is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو VK_KHR_xcb_surface 1

#وصف_ڪريو VK_KHR_XCB_SURFACE_SPEC_نسخو   6
#وصف_ڪريو VK_KHR_XCB_SURFACE_EXTENSION_NAME "VK_KHR_xcb_surface"

تعريفنوع VkFlags VkXcbSurfaceCreateFlagsKHR;

تعريفنوع بنية VkXcbSurfaceCreateInfoKHR {
    VkStructureType               sType;
    ثابت فراغ*                   p_ايندڙ;
    VkXcbSurfaceCreateFlagsKHR    flags;
    xcb_connection_t*             connection;
    xcb_دري_t                  دري;
} VkXcbSurfaceCreateInfoKHR;


تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vkCreateXcbSurfaceKHR)(VkInstance instance, ثابت VkXcbSurfaceCreateInfoKHR* pCreateInfo, ثابت Vk_ورهاست_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
تعريفنوع VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR)(VkPhysicalDevice physicalDevice, uint32_t قطار_Family_اشاريو, xcb_connection_t* connection, xcb_visualid_t visual_id);

#جيڪڏهن_وصف_نه_ٿيل VK_NO_PROTOTYPES

#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتيجو VKAPI_CALL vkCreateXcbSurfaceKHR(
    VkInstance                                  instance,
    ثابت VkXcbSurfaceCreateInfoKHR*            pCreateInfo,
    ثابت Vk_ورهاست_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceXcbPresentationSupportKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    قطار_Family_اشاريو,
    xcb_connection_t*                           connection,
    xcb_visualid_t                              visual_id);
#جيڪڏهن_پورو
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل __cplusplus
}
#جيڪڏهن_پورو

#جيڪڏهن_پورو
