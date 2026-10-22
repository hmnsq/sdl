#که_نه_تعریف_شوی VULKAN_XCB_H_
#تعریف_کړه VULKAN_XCB_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#که_تعریف_شوی __cplusplus
خارجي "C" {
#د_که_پای



// VK_KHR_xcb_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه VK_KHR_xcb_surface 1

#تعریف_کړه VK_KHR_XCB_SURFACE_SPEC_نسخه   6
#تعریف_کړه VK_KHR_XCB_SURFACE_EXTENSION_NAME "VK_KHR_xcb_surface"

تعريفنوع VkFlags VkXcbSurfaceCreateFlagsKHR;

تعريفنوع بنية VkXcbSurfaceCreateInfoKHR {
    VkStructureType               sType;
    ثابت فراغ*                   p_بل;
    VkXcbSurfaceCreateFlagsKHR    flags;
    xcb_connection_t*             connection;
    xcb_کړکۍ_t                  کړکۍ;
} VkXcbSurfaceCreateInfoKHR;


تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vkCreateXcbSurfaceKHR)(VkInstance instance, ثابت VkXcbSurfaceCreateInfoKHR* pCreateInfo, ثابت Vk_ویش_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
تعريفنوع VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR)(VkPhysicalDevice physicalDevice, uint32_t کتار_Family_شاخص, xcb_connection_t* connection, xcb_visualid_t visual_id);

#که_نه_تعریف_شوی VK_NO_PROTOTYPES

#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_پایله VKAPI_CALL vkCreateXcbSurfaceKHR(
    VkInstance                                  instance,
    ثابت VkXcbSurfaceCreateInfoKHR*            pCreateInfo,
    ثابت Vk_ویش_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#د_که_پای
#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceXcbPresentationSupportKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    کتار_Family_شاخص,
    xcb_connection_t*                           connection,
    xcb_visualid_t                              visual_id);
#د_که_پای
#د_که_پای

#که_تعریف_شوی __cplusplus
}
#د_که_پای

#د_که_پای
