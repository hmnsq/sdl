#నిర్వచితం_కాకపోతే VULKAN_ANDROID_H_
#నిర్వచించు VULKAN_ANDROID_H_ 1

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



// VK_KHR_android_surface is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు VK_KHR_android_surface 1

నిర్మాణం ANative_కిటికీ;

#నిర్వచించు VK_KHR_ANDROID_SURFACE_SPEC_సంస్కరణ 6
#నిర్వచించు VK_KHR_ANDROID_SURFACE_EXTENSION_NAME "VK_KHR_android_surface"

రకనిర్వచనం VkFlags VkAndroidSurfaceCreateFlagsKHR;

రకనిర్వచనం నిర్మాణం VkAndroidSurfaceCreateInfoKHR {
    VkStructureType                   sType;
    స్థిరరాశి శూన్య*                       p_తదుపరి;
    VkAndroidSurfaceCreateFlagsKHR    flags;
    నిర్మాణం ANative_కిటికీ*             కిటికీ;
} VkAndroidSurfaceCreateInfoKHR;


రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vkCreateAndroidSurfaceKHR)(VkInstance instance, స్థిరరాశి VkAndroidSurfaceCreateInfoKHR* pCreateInfo, స్థిరరాశి Vk_కేటాయింపు_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#నిర్వచితం_కాకపోతే VK_NO_PROTOTYPES

#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vkCreateAndroidSurfaceKHR(
    VkInstance                                  instance,
    స్థిరరాశి VkAndroidSurfaceCreateInfoKHR*        pCreateInfo,
    స్థిరరాశి Vk_కేటాయింపు_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#అయితే_ముగింపు
#అయితే_ముగింపు


// VK_ANDROID_external_memory_android_hardware_buffer is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు VK_ANDROID_external_జ్ఞాపకం_android_hardware_బఫరు 1

నిర్మాణం AHardware_బఫరు;

#నిర్వచించు VK_ANDROID_EXTERNAL_జ్ఞాపకం_ANDROID_HARDWARE_బఫరు_SPEC_సంస్కరణ 5
#నిర్వచించు VK_ANDROID_EXTERNAL_జ్ఞాపకం_ANDROID_HARDWARE_బఫరు_EXTENSION_NAME "VK_ANDROID_external_memory_android_hardware_buffer"

రకనిర్వచనం నిర్మాణం Vk_Android_Hardware_బఫరు_Usage_ANDROID {
    VkStructureType    sType;
    శూన్య*              p_తదుపరి;
    uint64_t           android_Hardware_బఫరు_Usage;
} Vk_Android_Hardware_బఫరు_Usage_ANDROID;

రకనిర్వచనం నిర్మాణం Vk_Android_Hardware_బఫరు_Properties_ANDROID {
    VkStructureType    sType;
    శూన్య*              p_తదుపరి;
    Vk_Device_కొలత       కేటాయింపు_కొలత;
    uint32_t           జ్ఞాపకం_Type_బిట్లు;
} Vk_Android_Hardware_బఫరు_Properties_ANDROID;

రకనిర్వచనం నిర్మాణం Vk_Android_Hardware_బఫరు_Format_Properties_ANDROID {
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
} Vk_Android_Hardware_బఫరు_Format_Properties_ANDROID;

రకనిర్వచనం నిర్మాణం Vk_Import_Android_Hardware_బఫరు_Info_ANDROID {
    VkStructureType            sType;
    స్థిరరాశి శూన్య*                p_తదుపరి;
    నిర్మాణం AHardware_బఫరు*    బఫరు_2;
} Vk_Import_Android_Hardware_బఫరు_Info_ANDROID;

రకనిర్వచనం నిర్మాణం Vk_జ్ఞాపకం_Get_Android_Hardware_బఫరు_Info_ANDROID {
    VkStructureType    sType;
    స్థిరరాశి శూన్య*        p_తదుపరి;
    Vk_Device_జ్ఞాపకం     జ్ఞాపకం;
} Vk_జ్ఞాపకం_Get_Android_Hardware_బఫరు_Info_ANDROID;

రకనిర్వచనం నిర్మాణం VkExternalFormatANDROID {
    VkStructureType    sType;
    శూన్య*              p_తదుపరి;
    uint64_t           externalFormat;
} VkExternalFormatANDROID;

రకనిర్వచనం నిర్మాణం Vk_Android_Hardware_బఫరు_Format_Properties2_ANDROID {
    VkStructureType                  sType;
    శూన్య*                            p_తదుపరి;
    VkFormat                         format;
    uint64_t                         externalFormat;
    VkFormatFeatureFlags2            formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggested_XChroma_స్థానభ్రంశం;
    VkChromaLocation                 suggested_YChroma_స్థానభ్రంశం;
} Vk_Android_Hardware_బఫరు_Format_Properties2_ANDROID;


రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vk_Get_Android_Hardware_బఫరు_Properties_ANDROID)(VkDevice device, స్థిరరాశి నిర్మాణం AHardware_బఫరు* బఫరు_2, Vk_Android_Hardware_బఫరు_Properties_ANDROID* pProperties);
రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vk_Get_జ్ఞాపకం_Android_Hardware_బఫరు_ANDROID)(VkDevice device, స్థిరరాశి Vk_జ్ఞాపకం_Get_Android_Hardware_బఫరు_Info_ANDROID* pInfo, నిర్మాణం AHardware_బఫరు** p_బఫరు);

#నిర్వచితం_కాకపోతే VK_NO_PROTOTYPES

#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vk_Get_Android_Hardware_బఫరు_Properties_ANDROID(
    VkDevice                                    device,
    స్థిరరాశి నిర్మాణం AHardware_బఫరు*               బఫరు_2,
    Vk_Android_Hardware_బఫరు_Properties_ANDROID*   pProperties);
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vk_Get_జ్ఞాపకం_Android_Hardware_బఫరు_ANDROID(
    VkDevice                                    device,
    స్థిరరాశి Vk_జ్ఞాపకం_Get_Android_Hardware_బఫరు_Info_ANDROID* pInfo,
    నిర్మాణం AHardware_బఫరు**                    p_బఫరు);
#అయితే_ముగింపు
#అయితే_ముగింపు


// VK_ANDROID_external_format_resolve is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు VK_ANDROID_external_format_resolve 1

#నిర్వచించు VK_ANDROID_EXTERNAL_FORMAT_RESOLVE_SPEC_సంస్కరణ 1
#నిర్వచించు VK_ANDROID_EXTERNAL_FORMAT_RESOLVE_EXTENSION_NAME "VK_ANDROID_external_format_resolve"

రకనిర్వచనం నిర్మాణం VkPhysicalDeviceExternalFormatResolveFeaturesANDROID {
    VkStructureType    sType;
    శూన్య*              p_తదుపరి;
    VkBool32           externalFormatResolve;
} VkPhysicalDeviceExternalFormatResolveFeaturesANDROID;

రకనిర్వచనం నిర్మాణం VkPhysicalDeviceExternalFormatResolvePropertiesANDROID {
    VkStructureType     sType;
    శూన్య*               p_తదుపరి;
    VkBool32            nullColorAttachmentWithExternalFormatResolve;
    VkChromaLocation    external_Format_Resolve_Chroma_స్థానభ్రంశం_X;
    VkChromaLocation    external_Format_Resolve_Chroma_స్థానభ్రంశం_Y;
} VkPhysicalDeviceExternalFormatResolvePropertiesANDROID;

రకనిర్వచనం నిర్మాణం Vk_Android_Hardware_బఫరు_Format_Resolve_Properties_ANDROID {
    VkStructureType    sType;
    శూన్య*              p_తదుపరి;
    VkFormat           colorAttachmentFormat;
} Vk_Android_Hardware_బఫరు_Format_Resolve_Properties_ANDROID;


#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు
