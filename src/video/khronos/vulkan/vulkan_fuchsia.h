#నిర్వచితం_కాకపోతే VULKAN_FUCHSIA_H_
#నిర్వచించు VULKAN_FUCHSIA_H_ 1

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



// VK_FUCHSIA_imagepipe_surface is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు VK_FUCHSIA_imagepipe_surface 1

#నిర్వచించు VK_FUCHSIA_IMAGEPIPE_SURFACE_SPEC_సంస్కరణ 1
#నిర్వచించు VK_FUCHSIA_IMAGEPIPE_SURFACE_EXTENSION_NAME "VK_FUCHSIA_imagepipe_surface"

రకనిర్వచనం VkFlags VkImagePipeSurfaceCreateFlagsFUCHSIA;

రకనిర్వచనం నిర్మాణం VkImagePipeSurfaceCreateInfoFUCHSIA {
    VkStructureType                         sType;
    స్థిరరాశి శూన్య*                             p_తదుపరి;
    VkImagePipeSurfaceCreateFlagsFUCHSIA    flags;
    zx_handle_t                             imagePipeHandle;
} VkImagePipeSurfaceCreateInfoFUCHSIA;


రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vkCreateImagePipeSurfaceFUCHSIA)(VkInstance instance, స్థిరరాశి VkImagePipeSurfaceCreateInfoFUCHSIA* pCreateInfo, స్థిరరాశి Vk_కేటాయింపు_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#నిర్వచితం_కాకపోతే VK_NO_PROTOTYPES

#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vkCreateImagePipeSurfaceFUCHSIA(
    VkInstance                                  instance,
    స్థిరరాశి VkImagePipeSurfaceCreateInfoFUCHSIA*  pCreateInfo,
    స్థిరరాశి Vk_కేటాయింపు_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#అయితే_ముగింపు
#అయితే_ముగింపు


// VK_FUCHSIA_external_memory is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు VK_FUCHSIA_external_జ్ఞాపకం 1

#నిర్వచించు VK_FUCHSIA_EXTERNAL_జ్ఞాపకం_SPEC_సంస్కరణ 1
#నిర్వచించు VK_FUCHSIA_EXTERNAL_జ్ఞాపకం_EXTENSION_NAME "VK_FUCHSIA_external_memory"

రకనిర్వచనం నిర్మాణం Vk_Import_జ్ఞాపకం_Zircon_Handle_Info_FUCHSIA {
    VkStructureType                       sType;
    స్థిరరాశి శూన్య*                           p_తదుపరి;
    Vk_External_జ్ఞాపకం_Handle_Type_Flag_బిట్లు    handleType;
    zx_handle_t                           handle;
} Vk_Import_జ్ఞాపకం_Zircon_Handle_Info_FUCHSIA;

రకనిర్వచనం నిర్మాణం Vk_జ్ఞాపకం_Zircon_Handle_Properties_FUCHSIA {
    VkStructureType    sType;
    శూన్య*              p_తదుపరి;
    uint32_t           జ్ఞాపకం_Type_బిట్లు;
} Vk_జ్ఞాపకం_Zircon_Handle_Properties_FUCHSIA;

రకనిర్వచనం నిర్మాణం Vk_జ్ఞాపకం_Get_Zircon_Handle_Info_FUCHSIA {
    VkStructureType                       sType;
    స్థిరరాశి శూన్య*                           p_తదుపరి;
    Vk_Device_జ్ఞాపకం                        జ్ఞాపకం;
    Vk_External_జ్ఞాపకం_Handle_Type_Flag_బిట్లు    handleType;
} Vk_జ్ఞాపకం_Get_Zircon_Handle_Info_FUCHSIA;


రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vk_Get_జ్ఞాపకం_Zircon_Handle_FUCHSIA)(VkDevice device, స్థిరరాశి Vk_జ్ఞాపకం_Get_Zircon_Handle_Info_FUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle);
రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vk_Get_జ్ఞాపకం_Zircon_Handle_Properties_FUCHSIA)(VkDevice device, Vk_External_జ్ఞాపకం_Handle_Type_Flag_బిట్లు handleType, zx_handle_t zirconHandle, Vk_జ్ఞాపకం_Zircon_Handle_Properties_FUCHSIA* p_జ్ఞాపకం_Zircon_Handle_Properties);

#నిర్వచితం_కాకపోతే VK_NO_PROTOTYPES

#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vk_Get_జ్ఞాపకం_Zircon_Handle_FUCHSIA(
    VkDevice                                    device,
    స్థిరరాశి Vk_జ్ఞాపకం_Get_Zircon_Handle_Info_FUCHSIA*   pGetZirconHandleInfo,
    zx_handle_t*                                pZirconHandle);
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vk_Get_జ్ఞాపకం_Zircon_Handle_Properties_FUCHSIA(
    VkDevice                                    device,
    Vk_External_జ్ఞాపకం_Handle_Type_Flag_బిట్లు          handleType,
    zx_handle_t                                 zirconHandle,
    Vk_జ్ఞాపకం_Zircon_Handle_Properties_FUCHSIA*      p_జ్ఞాపకం_Zircon_Handle_Properties);
#అయితే_ముగింపు
#అయితే_ముగింపు


// VK_FUCHSIA_external_semaphore is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు VK_FUCHSIA_external_semaphore 1

#నిర్వచించు VK_FUCHSIA_EXTERNAL_SEMAPHORE_SPEC_సంస్కరణ 1
#నిర్వచించు VK_FUCHSIA_EXTERNAL_SEMAPHORE_EXTENSION_NAME "VK_FUCHSIA_external_semaphore"

రకనిర్వచనం నిర్మాణం VkImportSemaphoreZirconHandleInfoFUCHSIA {
    VkStructureType                          sType;
    స్థిరరాశి శూన్య*                              p_తదుపరి;
    VkSemaphore                              semaphore;
    VkSemaphoreImportFlags                   flags;
    Vk_External_Semaphore_Handle_Type_Flag_బిట్లు    handleType;
    zx_handle_t                              zirconHandle;
} VkImportSemaphoreZirconHandleInfoFUCHSIA;

రకనిర్వచనం నిర్మాణం VkSemaphoreGetZirconHandleInfoFUCHSIA {
    VkStructureType                          sType;
    స్థిరరాశి శూన్య*                              p_తదుపరి;
    VkSemaphore                              semaphore;
    Vk_External_Semaphore_Handle_Type_Flag_బిట్లు    handleType;
} VkSemaphoreGetZirconHandleInfoFUCHSIA;


రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vkImportSemaphoreZirconHandleFUCHSIA)(VkDevice device, స్థిరరాశి VkImportSemaphoreZirconHandleInfoFUCHSIA* pImportSemaphoreZirconHandleInfo);
రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vkGetSemaphoreZirconHandleFUCHSIA)(VkDevice device, స్థిరరాశి VkSemaphoreGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle);

#నిర్వచితం_కాకపోతే VK_NO_PROTOTYPES

#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vkImportSemaphoreZirconHandleFUCHSIA(
    VkDevice                                    device,
    స్థిరరాశి VkImportSemaphoreZirconHandleInfoFUCHSIA* pImportSemaphoreZirconHandleInfo);
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vkGetSemaphoreZirconHandleFUCHSIA(
    VkDevice                                    device,
    స్థిరరాశి VkSemaphoreGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo,
    zx_handle_t*                                pZirconHandle);
#అయితే_ముగింపు
#అయితే_ముగింపు


// VK_FUCHSIA_buffer_collection is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు VK_FUCHSIA_బఫరు_collection 1

VK_DEFINE_NON_DISPATCHABLE_HANDLE(Vk_బఫరు_Collection_FUCHSIA)

#నిర్వచించు VK_FUCHSIA_బఫరు_COLLECTION_SPEC_సంస్కరణ 2
#నిర్వచించు VK_FUCHSIA_బఫరు_COLLECTION_EXTENSION_NAME "VK_FUCHSIA_buffer_collection"

రకనిర్వచనం VkFlags VkImageFormatConstraintsFlagsFUCHSIA;

రకనిర్వచనం గణన Vk_Image_Constraints_Info_Flag_బిట్లు_FUCHSIA {
    VK_IMAGE_CONSTRAINTS_INFO_CPU_READ_RARELY_FUCHSIA = 0x00000001,
    VK_IMAGE_CONSTRAINTS_INFO_CPU_READ_OFTEN_FUCHSIA = 0x00000002,
    VK_IMAGE_CONSTRAINTS_INFO_CPU_WRITE_RARELY_FUCHSIA = 0x00000004,
    VK_IMAGE_CONSTRAINTS_INFO_CPU_WRITE_OFTEN_FUCHSIA = 0x00000008,
    VK_IMAGE_CONSTRAINTS_INFO_PROTECTED_OPTIONAL_FUCHSIA = 0x00000010,
    VK_IMAGE_CONSTRAINTS_INFO_FLAG_బిట్లు_MAX_ENUM_FUCHSIA = 0x7FFFFFFF
} Vk_Image_Constraints_Info_Flag_బిట్లు_FUCHSIA;
రకనిర్వచనం VkFlags VkImageConstraintsInfoFlagsFUCHSIA;

రకనిర్వచనం నిర్మాణం Vk_బఫరు_Collection_Create_Info_FUCHSIA {
    VkStructureType    sType;
    స్థిరరాశి శూన్య*        p_తదుపరి;
    zx_handle_t        collectionToken;
} Vk_బఫరు_Collection_Create_Info_FUCHSIA;

రకనిర్వచనం నిర్మాణం Vk_Import_జ్ఞాపకం_బఫరు_Collection_FUCHSIA {
    VkStructureType              sType;
    స్థిరరాశి శూన్య*                  p_తదుపరి;
    Vk_బఫరు_Collection_FUCHSIA    collection;
    uint32_t                     సూచీ;
} Vk_Import_జ్ఞాపకం_బఫరు_Collection_FUCHSIA;

రకనిర్వచనం నిర్మాణం Vk_బఫరు_Collection_Image_Create_Info_FUCHSIA {
    VkStructureType              sType;
    స్థిరరాశి శూన్య*                  p_తదుపరి;
    Vk_బఫరు_Collection_FUCHSIA    collection;
    uint32_t                     సూచీ;
} Vk_బఫరు_Collection_Image_Create_Info_FUCHSIA;

రకనిర్వచనం నిర్మాణం Vk_బఫరు_Collection_Constraints_Info_FUCHSIA {
    VkStructureType    sType;
    స్థిరరాశి శూన్య*        p_తదుపరి;
    uint32_t           min_బఫరు_లెక్క;
    uint32_t           max_బఫరు_లెక్క;
    uint32_t           min_బఫరు_లెక్క_For_Camping;
    uint32_t           min_బఫరు_లెక్క_For_Dedicated_Slack;
    uint32_t           min_బఫరు_లెక్క_For_Shared_Slack;
} Vk_బఫరు_Collection_Constraints_Info_FUCHSIA;

రకనిర్వచనం నిర్మాణం Vk_బఫరు_Constraints_Info_FUCHSIA {
    VkStructureType                             sType;
    స్థిరరాశి శూన్య*                                 p_తదుపరి;
    Vk_బఫరు_Create_Info                          createInfo;
    VkFormatFeatureFlags                        requiredFormatFeatures;
    Vk_బఫరు_Collection_Constraints_Info_FUCHSIA    బఫరు_Collection_Constraints;
} Vk_బఫరు_Constraints_Info_FUCHSIA;

రకనిర్వచనం నిర్మాణం Vk_బఫరు_Collection_బఫరు_Create_Info_FUCHSIA {
    VkStructureType              sType;
    స్థిరరాశి శూన్య*                  p_తదుపరి;
    Vk_బఫరు_Collection_FUCHSIA    collection;
    uint32_t                     సూచీ;
} Vk_బఫరు_Collection_బఫరు_Create_Info_FUCHSIA;

రకనిర్వచనం నిర్మాణం VkSysmemColorSpaceFUCHSIA {
    VkStructureType    sType;
    స్థిరరాశి శూన్య*        p_తదుపరి;
    uint32_t           colorSpace;
} VkSysmemColorSpaceFUCHSIA;

రకనిర్వచనం నిర్మాణం Vk_బఫరు_Collection_Properties_FUCHSIA {
    VkStructureType                  sType;
    శూన్య*                            p_తదుపరి;
    uint32_t                         జ్ఞాపకం_Type_బిట్లు;
    uint32_t                         బఫరు_లెక్క;
    uint32_t                         create_Info_సూచీ;
    uint64_t                         sysmemPixelFormat;
    VkFormatFeatureFlags             formatFeatures;
    VkSysmemColorSpaceFUCHSIA        sysmem_Color_Space_సూచీ;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggested_XChroma_స్థానభ్రంశం;
    VkChromaLocation                 suggested_YChroma_స్థానభ్రంశం;
} Vk_బఫరు_Collection_Properties_FUCHSIA;

రకనిర్వచనం నిర్మాణం VkImageFormatConstraintsInfoFUCHSIA {
    VkStructureType                         sType;
    స్థిరరాశి శూన్య*                             p_తదుపరి;
    VkImageCreateInfo                       imageCreateInfo;
    VkFormatFeatureFlags                    requiredFormatFeatures;
    VkImageFormatConstraintsFlagsFUCHSIA    flags;
    uint64_t                                sysmemPixelFormat;
    uint32_t                                color_Space_లెక్క;
    స్థిరరాశి VkSysmemColorSpaceFUCHSIA*        pColorSpaces;
} VkImageFormatConstraintsInfoFUCHSIA;

రకనిర్వచనం నిర్మాణం VkImageConstraintsInfoFUCHSIA {
    VkStructureType                               sType;
    స్థిరరాశి శూన్య*                                   p_తదుపరి;
    uint32_t                                      format_Constraints_లెక్క;
    స్థిరరాశి VkImageFormatConstraintsInfoFUCHSIA*    pFormatConstraints;
    Vk_బఫరు_Collection_Constraints_Info_FUCHSIA      బఫరు_Collection_Constraints;
    VkImageConstraintsInfoFlagsFUCHSIA            flags;
} VkImageConstraintsInfoFUCHSIA;


రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vk_Create_బఫరు_Collection_FUCHSIA)(VkDevice device, స్థిరరాశి Vk_బఫరు_Collection_Create_Info_FUCHSIA* pCreateInfo, స్థిరరాశి Vk_కేటాయింపు_Callbacks* pAllocator, Vk_బఫరు_Collection_FUCHSIA* pCollection);
రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vk_సమితి_బఫరు_Collection_Image_Constraints_FUCHSIA)(VkDevice device, Vk_బఫరు_Collection_FUCHSIA collection, స్థిరరాశి VkImageConstraintsInfoFUCHSIA* pImageConstraintsInfo);
రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vk_సమితి_బఫరు_Collection_బఫరు_Constraints_FUCHSIA)(VkDevice device, Vk_బఫరు_Collection_FUCHSIA collection, స్థిరరాశి Vk_బఫరు_Constraints_Info_FUCHSIA* p_బఫరు_Constraints_Info);
రకనిర్వచనం శూన్య (VKAPI_PTR *PFN_vk_Destroy_బఫరు_Collection_FUCHSIA)(VkDevice device, Vk_బఫరు_Collection_FUCHSIA collection, స్థిరరాశి Vk_కేటాయింపు_Callbacks* pAllocator);
రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vk_Get_బఫరు_Collection_Properties_FUCHSIA)(VkDevice device, Vk_బఫరు_Collection_FUCHSIA collection, Vk_బఫరు_Collection_Properties_FUCHSIA* pProperties);

#నిర్వచితం_కాకపోతే VK_NO_PROTOTYPES

#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vk_Create_బఫరు_Collection_FUCHSIA(
    VkDevice                                    device,
    స్థిరరాశి Vk_బఫరు_Collection_Create_Info_FUCHSIA*  pCreateInfo,
    స్థిరరాశి Vk_కేటాయింపు_Callbacks*                pAllocator,
    Vk_బఫరు_Collection_FUCHSIA*                  pCollection);
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vk_సమితి_బఫరు_Collection_Image_Constraints_FUCHSIA(
    VkDevice                                    device,
    Vk_బఫరు_Collection_FUCHSIA                   collection,
    స్థిరరాశి VkImageConstraintsInfoFUCHSIA*        pImageConstraintsInfo);
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vk_సమితి_బఫరు_Collection_బఫరు_Constraints_FUCHSIA(
    VkDevice                                    device,
    Vk_బఫరు_Collection_FUCHSIA                   collection,
    స్థిరరాశి Vk_బఫరు_Constraints_Info_FUCHSIA*       p_బఫరు_Constraints_Info);
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR శూన్య VKAPI_CALL vk_Destroy_బఫరు_Collection_FUCHSIA(
    VkDevice                                    device,
    Vk_బఫరు_Collection_FUCHSIA                   collection,
    స్థిరరాశి Vk_కేటాయింపు_Callbacks*                pAllocator);
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vk_Get_బఫరు_Collection_Properties_FUCHSIA(
    VkDevice                                    device,
    Vk_బఫరు_Collection_FUCHSIA                   collection,
    Vk_బఫరు_Collection_Properties_FUCHSIA*        pProperties);
#అయితే_ముగింపు
#అయితే_ముగింపు

#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు
