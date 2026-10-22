#నిర్వచితం_కాకపోతే VULKAN_XLIB_H_
#నిర్వచించు VULKAN_XLIB_H_ 1

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



// VK_KHR_xlib_surface is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు VK_KHR_xlib_surface 1

#నిర్వచించు VK_KHR_XLIB_SURFACE_SPEC_సంస్కరణ  6
#నిర్వచించు VK_KHR_XLIB_SURFACE_EXTENSION_NAME "VK_KHR_xlib_surface"

రకనిర్వచనం VkFlags VkXlibSurfaceCreateFlagsKHR;

రకనిర్వచనం నిర్మాణం VkXlibSurfaceCreateInfoKHR {
    VkStructureType                sType;
    స్థిరరాశి శూన్య*                    p_తదుపరి;
    VkXlibSurfaceCreateFlagsKHR    flags;
    Display*                       dpy;
    కిటికీ_2                         కిటికీ;
} VkXlibSurfaceCreateInfoKHR;


రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vkCreateXlibSurfaceKHR)(VkInstance instance, స్థిరరాశి VkXlibSurfaceCreateInfoKHR* pCreateInfo, స్థిరరాశి Vk_కేటాయింపు_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
రకనిర్వచనం VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR)(VkPhysicalDevice physicalDevice, uint32_t వరుస_Family_సూచీ, Display* dpy, VisualID visualID);

#నిర్వచితం_కాకపోతే VK_NO_PROTOTYPES

#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vkCreateXlibSurfaceKHR(
    VkInstance                                  instance,
    స్థిరరాశి VkXlibSurfaceCreateInfoKHR*           pCreateInfo,
    స్థిరరాశి Vk_కేటాయింపు_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceXlibPresentationSupportKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    వరుస_Family_సూచీ,
    Display*                                    dpy,
    VisualID                                    visualID);
#అయితే_ముగింపు
#అయితే_ముగింపు

#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు
