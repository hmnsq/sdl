#నిర్వచితం_కాకపోతే VULKAN_XCB_H_
#నిర్వచించు VULKAN_XCB_H_ 1

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



// VK_KHR_xcb_surface is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు VK_KHR_xcb_surface 1

#నిర్వచించు VK_KHR_XCB_SURFACE_SPEC_సంస్కరణ   6
#నిర్వచించు VK_KHR_XCB_SURFACE_EXTENSION_NAME "VK_KHR_xcb_surface"

రకనిర్వచనం VkFlags VkXcbSurfaceCreateFlagsKHR;

రకనిర్వచనం నిర్మాణం VkXcbSurfaceCreateInfoKHR {
    VkStructureType               sType;
    స్థిరరాశి శూన్య*                   p_తదుపరి;
    VkXcbSurfaceCreateFlagsKHR    flags;
    xcb_connection_t*             connection;
    xcb_కిటికీ_t                  కిటికీ;
} VkXcbSurfaceCreateInfoKHR;


రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vkCreateXcbSurfaceKHR)(VkInstance instance, స్థిరరాశి VkXcbSurfaceCreateInfoKHR* pCreateInfo, స్థిరరాశి Vk_కేటాయింపు_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
రకనిర్వచనం VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR)(VkPhysicalDevice physicalDevice, uint32_t వరుస_Family_సూచీ, xcb_connection_t* connection, xcb_visualid_t visual_id);

#నిర్వచితం_కాకపోతే VK_NO_PROTOTYPES

#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vkCreateXcbSurfaceKHR(
    VkInstance                                  instance,
    స్థిరరాశి VkXcbSurfaceCreateInfoKHR*            pCreateInfo,
    స్థిరరాశి Vk_కేటాయింపు_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceXcbPresentationSupportKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    వరుస_Family_సూచీ,
    xcb_connection_t*                           connection,
    xcb_visualid_t                              visual_id);
#అయితే_ముగింపు
#అయితే_ముగింపు

#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు
