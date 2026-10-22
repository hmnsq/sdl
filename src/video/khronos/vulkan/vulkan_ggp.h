#నిర్వచితం_కాకపోతే VULKAN_GGP_H_
#నిర్వచించు VULKAN_GGP_H_ 1

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



// VK_GGP_stream_descriptor_surface is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు VK_GGP_ప్రవాహం_descriptor_surface 1

#నిర్వచించు VK_GGP_ప్రవాహం_DESCRIPTOR_SURFACE_SPEC_సంస్కరణ 1
#నిర్వచించు VK_GGP_ప్రవాహం_DESCRIPTOR_SURFACE_EXTENSION_NAME "VK_GGP_stream_descriptor_surface"

రకనిర్వచనం VkFlags Vk_ప్రవాహం_Descriptor_Surface_Create_Flags_GGP;

రకనిర్వచనం నిర్మాణం Vk_ప్రవాహం_Descriptor_Surface_Create_Info_GGP {
    VkStructureType                            sType;
    స్థిరరాశి శూన్య*                                p_తదుపరి;
    Vk_ప్రవాహం_Descriptor_Surface_Create_Flags_GGP    flags;
    Ggp_ప్రవాహం_Descriptor                        ప్రవాహం_Descriptor;
} Vk_ప్రవాహం_Descriptor_Surface_Create_Info_GGP;


రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vk_Create_ప్రవాహం_Descriptor_Surface_GGP)(VkInstance instance, స్థిరరాశి Vk_ప్రవాహం_Descriptor_Surface_Create_Info_GGP* pCreateInfo, స్థిరరాశి Vk_కేటాయింపు_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#నిర్వచితం_కాకపోతే VK_NO_PROTOTYPES

#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vk_Create_ప్రవాహం_Descriptor_Surface_GGP(
    VkInstance                                  instance,
    స్థిరరాశి Vk_ప్రవాహం_Descriptor_Surface_Create_Info_GGP* pCreateInfo,
    స్థిరరాశి Vk_కేటాయింపు_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#అయితే_ముగింపు
#అయితే_ముగింపు


// VK_GGP_frame_token is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు VK_GGP_చట్రం_token 1

#నిర్వచించు VK_GGP_చట్రం_TOKEN_SPEC_సంస్కరణ   1
#నిర్వచించు VK_GGP_చట్రం_TOKEN_EXTENSION_NAME "VK_GGP_frame_token"

రకనిర్వచనం నిర్మాణం Vk_Present_చట్రం_Token_GGP {
    VkStructureType    sType;
    స్థిరరాశి శూన్య*        p_తదుపరి;
    Ggp_చట్రం_Token      చట్రం_Token;
} Vk_Present_చట్రం_Token_GGP;


#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు
