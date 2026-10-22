#جيڪڏهن_وصف_نه_ٿيل VULKAN_WAYLAND_H_
#وصف_ڪريو VULKAN_WAYLAND_H_ 1

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



// VK_KHR_wayland_surface is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو VK_KHR_wayland_surface 1

#وصف_ڪريو VK_KHR_WAYLAND_SURFACE_SPEC_نسخو 6
#وصف_ڪريو VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME "VK_KHR_wayland_surface"

تعريفنوع VkFlags VkWaylandSurfaceCreateFlagsKHR;

تعريفنوع بنية VkWaylandSurfaceCreateInfoKHR {
    VkStructureType                   sType;
    ثابت فراغ*                       p_ايندڙ;
    VkWaylandSurfaceCreateFlagsKHR    flags;
    بنية wl_display*                display;
    بنية wl_surface*                surface;
} VkWaylandSurfaceCreateInfoKHR;


تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vkCreateWaylandSurfaceKHR)(VkInstance instance, ثابت VkWaylandSurfaceCreateInfoKHR* pCreateInfo, ثابت Vk_ورهاست_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
تعريفنوع VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR)(VkPhysicalDevice physicalDevice, uint32_t قطار_Family_اشاريو, بنية wl_display* display);

#جيڪڏهن_وصف_نه_ٿيل VK_NO_PROTOTYPES

#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتيجو VKAPI_CALL vkCreateWaylandSurfaceKHR(
    VkInstance                                  instance,
    ثابت VkWaylandSurfaceCreateInfoKHR*        pCreateInfo,
    ثابت Vk_ورهاست_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceWaylandPresentationSupportKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    قطار_Family_اشاريو,
    بنية wl_display*                          display);
#جيڪڏهن_پورو
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل __cplusplus
}
#جيڪڏهن_پورو

#جيڪڏهن_پورو
