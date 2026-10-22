#अगर_अघोषित VULKAN_WAYLAND_H_
#घोषणा VULKAN_WAYLAND_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#अगर_घोषित __cplusplus
बाह्य "C" {
#पूर्ण_अगर



// VK_KHR_wayland_surface is a preprocessor guard. Do not pass it to API calls.
#घोषणा VK_KHR_wayland_surface 1

#घोषणा VK_KHR_WAYLAND_SURFACE_SPEC_VERSION 6
#घोषणा VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME "VK_KHR_wayland_surface"

प्रकार VkFlags VkWaylandSurfaceCreateFlagsKHR;

प्रकार काष्ठा VkWaylandSurfaceCreateInfoKHR {
    VkStructureType                   sType;
    स्थिर व्योम*                       p_अग्र;
    VkWaylandSurfaceCreateFlagsKHR    flags;
    काष्ठा wl_display*                display;
    काष्ठा wl_surface*                surface;
} VkWaylandSurfaceCreateInfoKHR;


प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vkCreateWaylandSurfaceKHR)(VkInstance instance, स्थिर VkWaylandSurfaceCreateInfoKHR* pCreateInfo, स्थिर VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
प्रकार VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR)(VkPhysicalDevice physicalDevice, uint32_t queue_Family_सूचकांक, काष्ठा wl_display* display);

#अगर_अघोषित VK_NO_PROTOTYPES

#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkCreateWaylandSurfaceKHR(
    VkInstance                                  instance,
    स्थिर VkWaylandSurfaceCreateInfoKHR*        pCreateInfo,
    स्थिर VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#पूर्ण_अगर
#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceWaylandPresentationSupportKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queue_Family_सूचकांक,
    काष्ठा wl_display*                          display);
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_घोषित __cplusplus
}
#पूर्ण_अगर

#पूर्ण_अगर
