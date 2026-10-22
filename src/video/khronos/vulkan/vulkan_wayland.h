#جے_بنا_تعریف VULKAN_WAYLAND_H_
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


#جے_تعریف_شدہ __cplusplus
خارجي "C" {
#جے_انت



// VK_KHR_wayland_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_KHR_wayland_surface 1

#تعریف_کرو VK_KHR_WAYLAND_SURFACE_SPEC_نسخہ 6
#تعریف_کرو VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME "VK_KHR_wayland_surface"

تعريفنوع VkFlags VkWaylandSurfaceCreateFlagsKHR;

تعريفنوع بنية VkWaylandSurfaceCreateInfoKHR {
    VkStructureType                   sType;
    ثابت فراغ*                       p_اگلا;
    VkWaylandSurfaceCreateFlagsKHR    flags;
    بنية wl_display*                display;
    بنية wl_surface*                surface;
} VkWaylandSurfaceCreateInfoKHR;


تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vkCreateWaylandSurfaceKHR)(VkInstance instance, ثابت VkWaylandSurfaceCreateInfoKHR* pCreateInfo, ثابت Vk_ونڈ_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
تعريفنوع VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR)(VkPhysicalDevice physicalDevice, uint32_t قطار_Family_اشاریہ, بنية wl_display* display);

#جے_بنا_تعریف VK_NO_PROTOTYPES

#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vkCreateWaylandSurfaceKHR(
    VkInstance                                  instance,
    ثابت VkWaylandSurfaceCreateInfoKHR*        pCreateInfo,
    ثابت Vk_ونڈ_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#جے_انت
#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceWaylandPresentationSupportKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    قطار_Family_اشاریہ,
    بنية wl_display*                          display);
#جے_انت
#جے_انت

#جے_تعریف_شدہ __cplusplus
}
#جے_انت

#جے_انت
