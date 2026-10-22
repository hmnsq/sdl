#నిర్వచితం_కాకపోతే VULKAN_OHOS_H_
#నిర్వచించు VULKAN_OHOS_H_ 1

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



// VK_OHOS_external_memory is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు VK_OHOS_external_జ్ఞాపకం 1

నిర్మాణం OH_Native_బఫరు;

#నిర్వచించు VK_OHOS_EXTERNAL_జ్ఞాపకం_SPEC_సంస్కరణ 1
#నిర్వచించు VK_OHOS_EXTERNAL_జ్ఞాపకం_EXTENSION_NAME "VK_OHOS_external_memory"

రకనిర్వచనం నిర్మాణం Vk_Native_బఫరు_Usage_OHOS {
    VkStructureType    sType;
    శూన్య*              p_తదుపరి;
    uint64_t           OHOSNative_బఫరు_Usage;
} Vk_Native_బఫరు_Usage_OHOS;

రకనిర్వచనం నిర్మాణం Vk_Native_బఫరు_Properties_OHOS {
    VkStructureType    sType;
    శూన్య*              p_తదుపరి;
    Vk_Device_కొలత       కేటాయింపు_కొలత;
    uint32_t           జ్ఞాపకం_Type_బిట్లు;
} Vk_Native_బఫరు_Properties_OHOS;

రకనిర్వచనం నిర్మాణం Vk_Native_బఫరు_Format_Properties_OHOS {
    VkStructureType                  sType;
    శూన్య*                            p_తదుపరి;
    VkFormat                         format;
    uint64_t                         externalFormat;
    VkFormatFeatureFlags             formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggested_XChroma_స్థానభ్రంశం;
    VkChromaLocation                 suggested_YChroma_స్థానభ్రంశం;
} Vk_Native_బఫరు_Format_Properties_OHOS;

రకనిర్వచనం నిర్మాణం Vk_Import_Native_బఫరు_Info_OHOS {
    VkStructureType            sType;
    స్థిరరాశి శూన్య*                p_తదుపరి;
    నిర్మాణం OH_Native_బఫరు*    బఫరు_2;
} Vk_Import_Native_బఫరు_Info_OHOS;

రకనిర్వచనం నిర్మాణం Vk_జ్ఞాపకం_Get_Native_బఫరు_Info_OHOS {
    VkStructureType    sType;
    స్థిరరాశి శూన్య*        p_తదుపరి;
    Vk_Device_జ్ఞాపకం     జ్ఞాపకం;
} Vk_జ్ఞాపకం_Get_Native_బఫరు_Info_OHOS;

రకనిర్వచనం నిర్మాణం VkExternalFormatOHOS {
    VkStructureType    sType;
    శూన్య*              p_తదుపరి;
    uint64_t           externalFormat;
} VkExternalFormatOHOS;


రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vk_Get_Native_బఫరు_Properties_OHOS)(VkDevice device, స్థిరరాశి నిర్మాణం OH_Native_బఫరు* బఫరు_2, Vk_Native_బఫరు_Properties_OHOS* pProperties);
రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vk_Get_జ్ఞాపకం_Native_బఫరు_OHOS)(VkDevice device, స్థిరరాశి Vk_జ్ఞాపకం_Get_Native_బఫరు_Info_OHOS* pInfo, నిర్మాణం OH_Native_బఫరు** p_బఫరు);

#నిర్వచితం_కాకపోతే VK_NO_PROTOTYPES

#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vk_Get_Native_బఫరు_Properties_OHOS(
    VkDevice                                    device,
    స్థిరరాశి నిర్మాణం OH_Native_బఫరు*               బఫరు_2,
    Vk_Native_బఫరు_Properties_OHOS*               pProperties);
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vk_Get_జ్ఞాపకం_Native_బఫరు_OHOS(
    VkDevice                                    device,
    స్థిరరాశి Vk_జ్ఞాపకం_Get_Native_బఫరు_Info_OHOS*      pInfo,
    నిర్మాణం OH_Native_బఫరు**                    p_బఫరు);
#అయితే_ముగింపు
#అయితే_ముగింపు


// VK_OHOS_surface is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు VK_OHOS_surface 1

రకనిర్వచనం నిర్మాణం Native_కిటికీ OHNative_కిటికీ;

#నిర్వచించు VK_OHOS_SURFACE_SPEC_సంస్కరణ      1
#నిర్వచించు VK_OHOS_SURFACE_EXTENSION_NAME    "VK_OHOS_surface"

రకనిర్వచనం VkFlags VkSurfaceCreateFlagsOHOS;

రకనిర్వచనం నిర్మాణం VkSurfaceCreateInfoOHOS {
    VkStructureType             sType;
    స్థిరరాశి శూన్య*                 p_తదుపరి;
    VkSurfaceCreateFlagsOHOS    flags;
    OHNative_కిటికీ*             కిటికీ;
} VkSurfaceCreateInfoOHOS;


రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vkCreateSurfaceOHOS)(VkInstance instance, స్థిరరాశి VkSurfaceCreateInfoOHOS* pCreateInfo, స్థిరరాశి Vk_కేటాయింపు_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#నిర్వచితం_కాకపోతే VK_NO_PROTOTYPES

#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vkCreateSurfaceOHOS(
    VkInstance                                  instance,
    స్థిరరాశి VkSurfaceCreateInfoOHOS*              pCreateInfo,
    స్థిరరాశి Vk_కేటాయింపు_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#అయితే_ముగింపు
#అయితే_ముగింపు

#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు
