#جے_بنا_تعریف VULKAN_XCB_H_
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


#جے_تعریف_شدہ __cplusplus
خارجي "C" {
#جے_انت



// VK_KHR_xcb_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_KHR_xcb_surface 1

#تعریف_کرو VK_KHR_XCB_SURFACE_SPEC_نسخہ   6
#تعریف_کرو VK_KHR_XCB_SURFACE_EXTENSION_NAME "VK_KHR_xcb_surface"

تعريفنوع VkFlags VkXcbSurfaceCreateFlagsKHR;

تعريفنوع بنية VkXcbSurfaceCreateInfoKHR {
    VkStructureType               sType;
    ثابت فراغ*                   p_اگلا;
    VkXcbSurfaceCreateFlagsKHR    flags;
    xcb_connection_t*             connection;
    xcb_کھڑکی_t                  کھڑکی;
} VkXcbSurfaceCreateInfoKHR;


تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vkCreateXcbSurfaceKHR)(VkInstance instance, ثابت VkXcbSurfaceCreateInfoKHR* pCreateInfo, ثابت Vk_ونڈ_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
تعريفنوع VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR)(VkPhysicalDevice physicalDevice, uint32_t قطار_Family_اشاریہ, xcb_connection_t* connection, xcb_visualid_t visual_id);

#جے_بنا_تعریف VK_NO_PROTOTYPES

#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vkCreateXcbSurfaceKHR(
    VkInstance                                  instance,
    ثابت VkXcbSurfaceCreateInfoKHR*            pCreateInfo,
    ثابت Vk_ونڈ_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#جے_انت
#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceXcbPresentationSupportKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    قطار_Family_اشاریہ,
    xcb_connection_t*                           connection,
    xcb_visualid_t                              visual_id);
#جے_انت
#جے_انت

#جے_تعریف_شدہ __cplusplus
}
#جے_انت

#جے_انت
