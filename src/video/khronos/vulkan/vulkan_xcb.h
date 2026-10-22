#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VULKAN_XCB_H_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VULKAN_XCB_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ



// VK_KHR_xcb_surface is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_KHR_xcb_surface 1

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_KHR_XCB_SURFACE_SPEC_ਸੰਸਕਰਣ   6
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_KHR_XCB_SURFACE_EXTENSION_NAME "VK_KHR_xcb_surface"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ VkFlags VkXcbSurfaceCreateFlagsKHR;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkXcbSurfaceCreateInfoKHR {
    VkStructureType               sType;
    ਅਚਲ ਖਾਲੀ*                   p_ਅਗਲਾ;
    VkXcbSurfaceCreateFlagsKHR    flags;
    xcb_connection_t*             connection;
    xcb_ਖਿੜਕੀ_t                  ਖਿੜਕੀ;
} VkXcbSurfaceCreateInfoKHR;


ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vkCreateXcbSurfaceKHR)(VkInstance instance, ਅਚਲ VkXcbSurfaceCreateInfoKHR* pCreateInfo, ਅਚਲ Vk_ਵੰਡ_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR)(VkPhysicalDevice physicalDevice, uint32_t ਕਤਾਰ_Family_ਸੂਚਕਾਂਕ, xcb_connection_t* connection, xcb_visualid_t visual_id);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_NO_PROTOTYPES

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ਨਤੀਜਾ VKAPI_CALL vkCreateXcbSurfaceKHR(
    VkInstance                                  instance,
    ਅਚਲ VkXcbSurfaceCreateInfoKHR*            pCreateInfo,
    ਅਚਲ Vk_ਵੰਡ_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceXcbPresentationSupportKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    ਕਤਾਰ_Family_ਸੂਚਕਾਂਕ,
    xcb_connection_t*                           connection,
    xcb_visualid_t                              visual_id);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ
