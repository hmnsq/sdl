#నిర్వచితం_కాకపోతే VULKAN_VI_H_
#నిర్వచించు VULKAN_VI_H_ 1

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



// VK_NN_vi_surface is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు VK_NN_vi_surface 1

#నిర్వచించు VK_NN_VI_SURFACE_SPEC_సంస్కరణ     1
#నిర్వచించు VK_NN_VI_SURFACE_EXTENSION_NAME   "VK_NN_vi_surface"

రకనిర్వచనం VkFlags VkViSurfaceCreateFlagsNN;

రకనిర్వచనం నిర్మాణం VkViSurfaceCreateInfoNN {
    VkStructureType             sType;
    స్థిరరాశి శూన్య*                 p_తదుపరి;
    VkViSurfaceCreateFlagsNN    flags;
    శూన్య*                       కిటికీ;
} VkViSurfaceCreateInfoNN;


రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vkCreateViSurfaceNN)(VkInstance instance, స్థిరరాశి VkViSurfaceCreateInfoNN* pCreateInfo, స్థిరరాశి Vk_కేటాయింపు_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#నిర్వచితం_కాకపోతే VK_NO_PROTOTYPES

#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vkCreateViSurfaceNN(
    VkInstance                                  instance,
    స్థిరరాశి VkViSurfaceCreateInfoNN*              pCreateInfo,
    స్థిరరాశి Vk_కేటాయింపు_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#అయితే_ముగింపు
#అయితే_ముగింపు

#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు
