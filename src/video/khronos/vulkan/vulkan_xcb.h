#اگر_غیر_تعریف_شدہ VULKAN_XCB_H_
#تعریف_کرو VULKAN_XCB_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#اگر_تعریف_شدہ __cplusplus
خارجی "C" {
#اگر_ختم



// VK_KHR_xcb_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_KHR_xcb_surface 1

#تعریف_کرو VK_KHR_XCB_SURFACE_SPEC_نسخہ   6
#تعریف_کرو VK_KHR_XCB_SURFACE_EXTENSION_NAME "VK_KHR_xcb_surface"

قسمتعریف VkFlags VkXcbSurfaceCreateFlagsKHR;

قسمتعریف ساخت VkXcbSurfaceCreateInfoKHR {
    VkStructureType               sType;
    ثابت خالی*                   p_اگلا;
    VkXcbSurfaceCreateFlagsKHR    flags;
    xcb_connection_t*             connection;
    xcb_کھڑکی_t                  کھڑکی;
} VkXcbSurfaceCreateInfoKHR;


قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vkCreateXcbSurfaceKHR)(VkInstance instance, ثابت VkXcbSurfaceCreateInfoKHR* pCreateInfo, ثابت Vk_تخصیص_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
قسمتعریف VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR)(VkPhysicalDevice physicalDevice, uint32_t قطار_Family_اشاریہ, xcb_connection_t* connection, xcb_visualid_t visual_id);

#اگر_غیر_تعریف_شدہ VK_NO_PROTOTYPES

#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vkCreateXcbSurfaceKHR(
    VkInstance                                  instance,
    ثابت VkXcbSurfaceCreateInfoKHR*            pCreateInfo,
    ثابت Vk_تخصیص_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#اگر_ختم
#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceXcbPresentationSupportKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    قطار_Family_اشاریہ,
    xcb_connection_t*                           connection,
    xcb_visualid_t                              visual_id);
#اگر_ختم
#اگر_ختم

#اگر_تعریف_شدہ __cplusplus
}
#اگر_ختم

#اگر_ختم
