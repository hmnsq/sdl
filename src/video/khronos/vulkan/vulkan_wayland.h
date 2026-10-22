#که_نه_تعریف_شوی VULKAN_WAYLAND_H_
#تعریف_کړه VULKAN_WAYLAND_H_ 1

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



// VK_KHR_wayland_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه VK_KHR_wayland_surface 1

#تعریف_کړه VK_KHR_WAYLAND_SURFACE_SPEC_نسخه 6
#تعریف_کړه VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME "VK_KHR_wayland_surface"

تعريفنوع VkFlags VkWaylandSurfaceCreateFlagsKHR;

تعريفنوع بنية VkWaylandSurfaceCreateInfoKHR {
    VkStructureType                   sType;
    ثابت فراغ*                       p_بل;
    VkWaylandSurfaceCreateFlagsKHR    flags;
    بنية wl_display*                display;
    بنية wl_surface*                surface;
} VkWaylandSurfaceCreateInfoKHR;


تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vkCreateWaylandSurfaceKHR)(VkInstance instance, ثابت VkWaylandSurfaceCreateInfoKHR* pCreateInfo, ثابت Vk_ویش_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
تعريفنوع VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR)(VkPhysicalDevice physicalDevice, uint32_t کتار_Family_شاخص, بنية wl_display* display);

#که_نه_تعریف_شوی VK_NO_PROTOTYPES

#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_پایله VKAPI_CALL vkCreateWaylandSurfaceKHR(
    VkInstance                                  instance,
    ثابت VkWaylandSurfaceCreateInfoKHR*        pCreateInfo,
    ثابت Vk_ویش_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#د_که_پای
#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceWaylandPresentationSupportKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    کتار_Family_شاخص,
    بنية wl_display*                          display);
#د_که_پای
#د_که_پای

#که_تعریف_شوی __cplusplus
}
#د_که_پای

#د_که_پای
