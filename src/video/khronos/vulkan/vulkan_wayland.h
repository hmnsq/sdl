#నిర్వచితం_కాకపోతే VULKAN_WAYLAND_H_
#నిర్వచించు VULKAN_WAYLAND_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#నిర్వచితమైతే __cplusplus
బాహ్య "C" {
#అయితే_ముగింపు



// VK_KHR_wayland_surface is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు VK_KHR_wayland_surface 1

#నిర్వచించు VK_KHR_WAYLAND_SURFACE_SPEC_సంస్కరణ 6
#నిర్వచించు VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME "VK_KHR_wayland_surface"

రకనిర్వచనం VkFlags VkWaylandSurfaceCreateFlagsKHR;

రకనిర్వచనం నిర్మాణం VkWaylandSurfaceCreateInfoKHR {
    VkStructureType                   sType;
    స్థిరరాశి శూన్య*                       p_తదుపరి;
    VkWaylandSurfaceCreateFlagsKHR    flags;
    నిర్మాణం wl_display*                display;
    నిర్మాణం wl_surface*                surface;
} VkWaylandSurfaceCreateInfoKHR;


రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vkCreateWaylandSurfaceKHR)(VkInstance instance, స్థిరరాశి VkWaylandSurfaceCreateInfoKHR* pCreateInfo, స్థిరరాశి Vk_కేటాయింపు_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
రకనిర్వచనం VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR)(VkPhysicalDevice physicalDevice, uint32_t వరుస_Family_సూచీ, నిర్మాణం wl_display* display);

#నిర్వచితం_కాకపోతే VK_NO_PROTOTYPES

#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vkCreateWaylandSurfaceKHR(
    VkInstance                                  instance,
    స్థిరరాశి VkWaylandSurfaceCreateInfoKHR*        pCreateInfo,
    స్థిరరాశి Vk_కేటాయింపు_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceWaylandPresentationSupportKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    వరుస_Family_సూచీ,
    నిర్మాణం wl_display*                          display);
#అయితే_ముగింపు
#అయితే_ముగింపు

#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు
