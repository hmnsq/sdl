#अगर_अघोषित VULKAN_XCB_H_
#घोषणा VULKAN_XCB_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#अगर_घोषित __cplusplus
बाह्य "C" {
#पूर्ण_अगर



// VK_KHR_xcb_surface is a preprocessor guard. Do not pass it to API calls.
#घोषणा VK_KHR_xcb_surface 1

#घोषणा VK_KHR_XCB_SURFACE_SPEC_VERSION   6
#घोषणा VK_KHR_XCB_SURFACE_EXTENSION_NAME "VK_KHR_xcb_surface"

प्रकार VkFlags VkXcbSurfaceCreateFlagsKHR;

प्रकार काष्ठा VkXcbSurfaceCreateInfoKHR {
    VkStructureType               sType;
    स्थिर व्योम*                   p_अग्र;
    VkXcbSurfaceCreateFlagsKHR    flags;
    xcb_connection_t*             connection;
    xcb_window_t                  window;
} VkXcbSurfaceCreateInfoKHR;


प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vkCreateXcbSurfaceKHR)(VkInstance instance, स्थिर VkXcbSurfaceCreateInfoKHR* pCreateInfo, स्थिर VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
प्रकार VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR)(VkPhysicalDevice physicalDevice, uint32_t queue_Family_सूचकांक, xcb_connection_t* connection, xcb_visualid_t visual_id);

#अगर_अघोषित VK_NO_PROTOTYPES

#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkCreateXcbSurfaceKHR(
    VkInstance                                  instance,
    स्थिर VkXcbSurfaceCreateInfoKHR*            pCreateInfo,
    स्थिर VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#पूर्ण_अगर
#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceXcbPresentationSupportKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queue_Family_सूचकांक,
    xcb_connection_t*                           connection,
    xcb_visualid_t                              visual_id);
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_घोषित __cplusplus
}
#पूर्ण_अगर

#पूर्ण_अगर
