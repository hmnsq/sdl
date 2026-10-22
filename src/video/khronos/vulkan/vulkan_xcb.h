#اگر_تعریف_نشده VULKAN_XCB_H_
#تعریف_کن VULKAN_XCB_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#اگر_تعریف_شده __cplusplus
خارجي "C" {
#پایان_اگر



// VK_KHR_xcb_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کن VK_KHR_xcb_surface 1

#تعریف_کن VK_KHR_XCB_SURFACE_SPEC_نسخه   6
#تعریف_کن VK_KHR_XCB_SURFACE_EXTENSION_NAME "VK_KHR_xcb_surface"

تعريفنوع VkFlags VkXcbSurfaceCreateFlagsKHR;

تعريفنوع بنية VkXcbSurfaceCreateInfoKHR {
    VkStructureType               sType;
    ثابت فراغ*                   p_بعدی;
    VkXcbSurfaceCreateFlagsKHR    flags;
    xcb_connection_t*             connection;
    xcb_پنجره_t                  پنجره;
} VkXcbSurfaceCreateInfoKHR;


تعريفنوع Vk_نتیجه (VKAPI_PTR *PFN_vkCreateXcbSurfaceKHR)(VkInstance instance, ثابت VkXcbSurfaceCreateInfoKHR* pCreateInfo, ثابت Vk_تخصیص_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
تعريفنوع VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR)(VkPhysicalDevice physicalDevice, uint32_t صف_Family_شاخص, xcb_connection_t* connection, xcb_visualid_t visual_id);

#اگر_تعریف_نشده VK_NO_PROTOTYPES

#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجه VKAPI_CALL vkCreateXcbSurfaceKHR(
    VkInstance                                  instance,
    ثابت VkXcbSurfaceCreateInfoKHR*            pCreateInfo,
    ثابت Vk_تخصیص_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#پایان_اگر
#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceXcbPresentationSupportKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    صف_Family_شاخص,
    xcb_connection_t*                           connection,
    xcb_visualid_t                              visual_id);
#پایان_اگر
#پایان_اگر

#اگر_تعریف_شده __cplusplus
}
#پایان_اگر

#پایان_اگر
