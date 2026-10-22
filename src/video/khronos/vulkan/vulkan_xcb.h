#यदि_अपरिभाषितम् VULKAN_XCB_H_
#परिभाषय VULKAN_XCB_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#यदि_परिभाषितम् __cplusplus
बाह्य "C" {
#यदि_अन्तः



// VK_KHR_xcb_surface is a preprocessor guard. Do not pass it to API calls.
#परिभाषय VK_KHR_xcb_surface 1

#परिभाषय VK_KHR_XCB_SURFACE_SPEC_संस्करणम्   6
#परिभाषय VK_KHR_XCB_SURFACE_EXTENSION_NAME "VK_KHR_xcb_surface"

प्रकारनिर्देश VkFlags VkXcbSurfaceCreateFlagsKHR;

प्रकारनिर्देश संरचना VkXcbSurfaceCreateInfoKHR {
    VkStructureType               sType;
    ध्रुव शून्य*                   p_अग्र;
    VkXcbSurfaceCreateFlagsKHR    flags;
    xcb_connection_t*             connection;
    xcb_गवाक्षः_t                  गवाक्षः;
} VkXcbSurfaceCreateInfoKHR;


प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vkCreateXcbSurfaceKHR)(VkInstance instance, ध्रुव VkXcbSurfaceCreateInfoKHR* pCreateInfo, ध्रुव Vk_आवण्टनम्_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
प्रकारनिर्देश VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR)(VkPhysicalDevice physicalDevice, uint32_t queue_Family_सूचकांक, xcb_connection_t* connection, xcb_visualid_t visual_id);

#यदि_अपरिभाषितम् VK_NO_PROTOTYPES

#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkCreateXcbSurfaceKHR(
    VkInstance                                  instance,
    ध्रुव VkXcbSurfaceCreateInfoKHR*            pCreateInfo,
    ध्रुव Vk_आवण्टनम्_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#यदि_अन्तः
#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceXcbPresentationSupportKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queue_Family_सूचकांक,
    xcb_connection_t*                           connection,
    xcb_visualid_t                              visual_id);
#यदि_अन्तः
#यदि_अन्तः

#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

#यदि_अन्तः
