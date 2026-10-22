#నిర్వచితం_కాకపోతే VULKAN_SCREEN_H_
#నిర్వచించు VULKAN_SCREEN_H_ 1

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



// VK_QNX_screen_surface is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు VK_QNX_screen_surface 1

#నిర్వచించు VK_QNX_SCREEN_SURFACE_SPEC_సంస్కరణ 1
#నిర్వచించు VK_QNX_SCREEN_SURFACE_EXTENSION_NAME "VK_QNX_screen_surface"

రకనిర్వచనం VkFlags VkScreenSurfaceCreateFlagsQNX;

రకనిర్వచనం నిర్మాణం VkScreenSurfaceCreateInfoQNX {
    VkStructureType                  sType;
    స్థిరరాశి శూన్య*                      p_తదుపరి;
    VkScreenSurfaceCreateFlagsQNX    flags;
    నిర్మాణం _screen_context*          context;
    నిర్మాణం screen_కిటికీ*           కిటికీ;
} VkScreenSurfaceCreateInfoQNX;


రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vkCreateScreenSurfaceQNX)(VkInstance instance, స్థిరరాశి VkScreenSurfaceCreateInfoQNX* pCreateInfo, స్థిరరాశి Vk_కేటాయింపు_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
రకనిర్వచనం VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceScreenPresentationSupportQNX)(VkPhysicalDevice physicalDevice, uint32_t వరుస_Family_సూచీ, నిర్మాణం screen_కిటికీ* కిటికీ);

#నిర్వచితం_కాకపోతే VK_NO_PROTOTYPES

#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vkCreateScreenSurfaceQNX(
    VkInstance                                  instance,
    స్థిరరాశి VkScreenSurfaceCreateInfoQNX*         pCreateInfo,
    స్థిరరాశి Vk_కేటాయింపు_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceScreenPresentationSupportQNX(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    వరుస_Family_సూచీ,
    నిర్మాణం screen_కిటికీ*                      కిటికీ);
#అయితే_ముగింపు
#అయితే_ముగింపు


// VK_QNX_external_memory_screen_buffer is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు VK_QNX_external_జ్ఞాపకం_screen_బఫరు 1

#నిర్వచించు VK_QNX_EXTERNAL_జ్ఞాపకం_SCREEN_బఫరు_SPEC_సంస్కరణ 1
#నిర్వచించు VK_QNX_EXTERNAL_జ్ఞాపకం_SCREEN_బఫరు_EXTENSION_NAME "VK_QNX_external_memory_screen_buffer"

రకనిర్వచనం నిర్మాణం Vk_Screen_బఫరు_Properties_QNX {
    VkStructureType    sType;
    శూన్య*              p_తదుపరి;
    Vk_Device_కొలత       కేటాయింపు_కొలత;
    uint32_t           జ్ఞాపకం_Type_బిట్లు;
} Vk_Screen_బఫరు_Properties_QNX;

రకనిర్వచనం నిర్మాణం Vk_Screen_బఫరు_Format_Properties_QNX {
    VkStructureType                  sType;
    శూన్య*                            p_తదుపరి;
    VkFormat                         format;
    uint64_t                         externalFormat;
    uint64_t                         screenUsage;
    VkFormatFeatureFlags             formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggested_XChroma_స్థానభ్రంశం;
    VkChromaLocation                 suggested_YChroma_స్థానభ్రంశం;
} Vk_Screen_బఫరు_Format_Properties_QNX;

రకనిర్వచనం నిర్మాణం Vk_Import_Screen_బఫరు_Info_QNX {
    VkStructureType           sType;
    స్థిరరాశి శూన్య*               p_తదుపరి;
    నిర్మాణం screen_బఫరు*    బఫరు_2;
} Vk_Import_Screen_బఫరు_Info_QNX;

రకనిర్వచనం నిర్మాణం VkExternalFormatQNX {
    VkStructureType    sType;
    శూన్య*              p_తదుపరి;
    uint64_t           externalFormat;
} VkExternalFormatQNX;

రకనిర్వచనం నిర్మాణం Vk_Physical_Device_External_జ్ఞాపకం_Screen_బఫరు_Features_QNX {
    VkStructureType    sType;
    శూన్య*              p_తదుపరి;
    VkBool32           screen_బఫరు_Import;
} Vk_Physical_Device_External_జ్ఞాపకం_Screen_బఫరు_Features_QNX;


రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vk_Get_Screen_బఫరు_Properties_QNX)(VkDevice device, స్థిరరాశి నిర్మాణం screen_బఫరు* బఫరు_2, Vk_Screen_బఫరు_Properties_QNX* pProperties);

#నిర్వచితం_కాకపోతే VK_NO_PROTOTYPES

#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vk_Get_Screen_బఫరు_Properties_QNX(
    VkDevice                                    device,
    స్థిరరాశి నిర్మాణం screen_బఫరు*                బఫరు_2,
    Vk_Screen_బఫరు_Properties_QNX*                pProperties);
#అయితే_ముగింపు
#అయితే_ముగింపు

#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు
