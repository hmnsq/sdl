#నిర్వచితం_కాకపోతే VULKAN_DIRECTFB_H_
#నిర్వచించు VULKAN_DIRECTFB_H_ 1

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



// VK_EXT_directfb_surface is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు VK_EXT_directfb_surface 1

#నిర్వచించు VK_EXT_DIRECTFB_SURFACE_SPEC_సంస్కరణ 1
#నిర్వచించు VK_EXT_DIRECTFB_SURFACE_EXTENSION_NAME "VK_EXT_directfb_surface"

రకనిర్వచనం VkFlags Vk_ప్రత్యక్ష_FBSurface_Create_Flags_EXT;

రకనిర్వచనం నిర్మాణం Vk_ప్రత్యక్ష_FBSurface_Create_Info_EXT {
    VkStructureType                    sType;
    స్థిరరాశి శూన్య*                        p_తదుపరి;
    Vk_ప్రత్యక్ష_FBSurface_Create_Flags_EXT    flags;
    IDirectFB*                         dfb;
    IDirectFBSurface*                  surface;
} Vk_ప్రత్యక్ష_FBSurface_Create_Info_EXT;


రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vk_Create_ప్రత్యక్ష_FBSurface_EXT)(VkInstance instance, స్థిరరాశి Vk_ప్రత్యక్ష_FBSurface_Create_Info_EXT* pCreateInfo, స్థిరరాశి Vk_కేటాయింపు_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
రకనిర్వచనం VkBool32 (VKAPI_PTR *PFN_vk_Get_Physical_Device_ప్రత్యక్ష_FBPresentation_Support_EXT)(VkPhysicalDevice physicalDevice, uint32_t వరుస_Family_సూచీ, IDirectFB* dfb);

#నిర్వచితం_కాకపోతే VK_NO_PROTOTYPES

#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vk_Create_ప్రత్యక్ష_FBSurface_EXT(
    VkInstance                                  instance,
    స్థిరరాశి Vk_ప్రత్యక్ష_FBSurface_Create_Info_EXT*       pCreateInfo,
    స్థిరరాశి Vk_కేటాయింపు_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vk_Get_Physical_Device_ప్రత్యక్ష_FBPresentation_Support_EXT(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    వరుస_Family_సూచీ,
    IDirectFB*                                  dfb);
#అయితే_ముగింపు
#అయితే_ముగింపు

#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు
