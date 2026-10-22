#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VULKAN_WAYLAND_H_
#ವ್ಯಾಖ್ಯಾನಿಸು VULKAN_WAYLAND_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
ಬಾಹ್ಯ "C" {
#ಆದರೆ_ಅಂತ್ಯ



// VK_KHR_wayland_surface is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು VK_KHR_wayland_surface 1

#ವ್ಯಾಖ್ಯಾನಿಸು VK_KHR_WAYLAND_SURFACE_SPEC_ಆವೃತ್ತಿ 6
#ವ್ಯಾಖ್ಯಾನಿಸು VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME "VK_KHR_wayland_surface"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ VkFlags VkWaylandSurfaceCreateFlagsKHR;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkWaylandSurfaceCreateInfoKHR {
    VkStructureType                   sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*                       p_ಮುಂದಿನ;
    VkWaylandSurfaceCreateFlagsKHR    flags;
    ರಚನೆ wl_display*                display;
    ರಚನೆ wl_surface*                surface;
} VkWaylandSurfaceCreateInfoKHR;


ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vkCreateWaylandSurfaceKHR)(VkInstance instance, ಸ್ಥಿರಾಂಕ VkWaylandSurfaceCreateInfoKHR* pCreateInfo, ಸ್ಥಿರಾಂಕ Vk_ಹಂಚಿಕೆ_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR)(VkPhysicalDevice physicalDevice, uint32_t ಸರತಿ_Family_ಸೂಚ್ಯಂಕ, ರಚನೆ wl_display* display);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_NO_PROTOTYPES

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ಫಲಿತಾಂಶ VKAPI_CALL vkCreateWaylandSurfaceKHR(
    VkInstance                                  instance,
    ಸ್ಥಿರಾಂಕ VkWaylandSurfaceCreateInfoKHR*        pCreateInfo,
    ಸ್ಥಿರಾಂಕ Vk_ಹಂಚಿಕೆ_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceWaylandPresentationSupportKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    ಸರತಿ_Family_ಸೂಚ್ಯಂಕ,
    ರಚನೆ wl_display*                          display);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ
