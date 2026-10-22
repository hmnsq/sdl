#నిర్వచితం_కాకపోతే VULKAN_MACOS_H_
#నిర్వచించు VULKAN_MACOS_H_ 1

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



// VK_MVK_macos_surface is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు VK_MVK_macos_surface 1

#నిర్వచించు VK_MVK_MACOS_SURFACE_SPEC_సంస్కరణ 3
#నిర్వచించు VK_MVK_MACOS_SURFACE_EXTENSION_NAME "VK_MVK_macos_surface"

రకనిర్వచనం VkFlags VkMacOSSurfaceCreateFlagsMVK;

రకనిర్వచనం నిర్మాణం VkMacOSSurfaceCreateInfoMVK {
    VkStructureType                 sType;
    స్థిరరాశి శూన్య*                     p_తదుపరి;
    VkMacOSSurfaceCreateFlagsMVK    flags;
    స్థిరరాశి శూన్య*                     pView;
} VkMacOSSurfaceCreateInfoMVK;


రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vkCreateMacOSSurfaceMVK)(VkInstance instance, స్థిరరాశి VkMacOSSurfaceCreateInfoMVK* pCreateInfo, స్థిరరాశి Vk_కేటాయింపు_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#నిర్వచితం_కాకపోతే VK_NO_PROTOTYPES

#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vkCreateMacOSSurfaceMVK(
    VkInstance                                  instance,
    స్థిరరాశి VkMacOSSurfaceCreateInfoMVK*          pCreateInfo,
    స్థిరరాశి Vk_కేటాయింపు_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#అయితే_ముగింపు
#అయితే_ముగింపు

#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు
