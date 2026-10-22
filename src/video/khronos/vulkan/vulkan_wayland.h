#اگر_غیر_تعریف_شدہ VULKAN_WAYLAND_H_
#تعریف_کرو VULKAN_WAYLAND_H_ 1

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



// VK_KHR_wayland_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_KHR_wayland_surface 1

#تعریف_کرو VK_KHR_WAYLAND_SURFACE_SPEC_نسخہ 6
#تعریف_کرو VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME "VK_KHR_wayland_surface"

قسمتعریف VkFlags VkWaylandSurfaceCreateFlagsKHR;

قسمتعریف ساخت VkWaylandSurfaceCreateInfoKHR {
    VkStructureType                   sType;
    ثابت خالی*                       p_اگلا;
    VkWaylandSurfaceCreateFlagsKHR    flags;
    ساخت wl_display*                display;
    ساخت wl_surface*                surface;
} VkWaylandSurfaceCreateInfoKHR;


قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vkCreateWaylandSurfaceKHR)(VkInstance instance, ثابت VkWaylandSurfaceCreateInfoKHR* pCreateInfo, ثابت Vk_تخصیص_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
قسمتعریف VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR)(VkPhysicalDevice physicalDevice, uint32_t قطار_Family_اشاریہ, ساخت wl_display* display);

#اگر_غیر_تعریف_شدہ VK_NO_PROTOTYPES

#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vkCreateWaylandSurfaceKHR(
    VkInstance                                  instance,
    ثابت VkWaylandSurfaceCreateInfoKHR*        pCreateInfo,
    ثابت Vk_تخصیص_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#اگر_ختم
#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceWaylandPresentationSupportKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    قطار_Family_اشاریہ,
    ساخت wl_display*                          display);
#اگر_ختم
#اگر_ختم

#اگر_تعریف_شدہ __cplusplus
}
#اگر_ختم

#اگر_ختم
