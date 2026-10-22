#اگر_تعریف_نشده VULKAN_WAYLAND_H_
#تعریف_کن VULKAN_WAYLAND_H_ 1

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



// VK_KHR_wayland_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کن VK_KHR_wayland_surface 1

#تعریف_کن VK_KHR_WAYLAND_SURFACE_SPEC_نسخه 6
#تعریف_کن VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME "VK_KHR_wayland_surface"

تعريفنوع VkFlags VkWaylandSurfaceCreateFlagsKHR;

تعريفنوع بنية VkWaylandSurfaceCreateInfoKHR {
    VkStructureType                   sType;
    ثابت فراغ*                       p_بعدی;
    VkWaylandSurfaceCreateFlagsKHR    flags;
    بنية wl_display*                display;
    بنية wl_surface*                surface;
} VkWaylandSurfaceCreateInfoKHR;


تعريفنوع Vk_نتیجه (VKAPI_PTR *PFN_vkCreateWaylandSurfaceKHR)(VkInstance instance, ثابت VkWaylandSurfaceCreateInfoKHR* pCreateInfo, ثابت Vk_تخصیص_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
تعريفنوع VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR)(VkPhysicalDevice physicalDevice, uint32_t صف_Family_شاخص, بنية wl_display* display);

#اگر_تعریف_نشده VK_NO_PROTOTYPES

#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجه VKAPI_CALL vkCreateWaylandSurfaceKHR(
    VkInstance                                  instance,
    ثابت VkWaylandSurfaceCreateInfoKHR*        pCreateInfo,
    ثابت Vk_تخصیص_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#پایان_اگر
#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceWaylandPresentationSupportKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    صف_Family_شاخص,
    بنية wl_display*                          display);
#پایان_اگر
#پایان_اگر

#اگر_تعریف_شده __cplusplus
}
#پایان_اگر

#پایان_اگر
