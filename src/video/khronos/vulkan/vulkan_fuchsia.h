#यदि_अपरिभाषितम् VULKAN_FUCHSIA_H_
#परिभाषय VULKAN_FUCHSIA_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#यदि_परिभाषितम् __cplusplus
बाह्य "C" {
#यदि_अन्तः



// VK_FUCHSIA_imagepipe_surface is a preprocessor guard. Do not pass it to API calls.
#परिभाषय VK_FUCHSIA_imagepipe_surface 1

#परिभाषय VK_FUCHSIA_IMAGEPIPE_SURFACE_SPEC_संस्करणम् 1
#परिभाषय VK_FUCHSIA_IMAGEPIPE_SURFACE_EXTENSION_NAME "VK_FUCHSIA_imagepipe_surface"

प्रकारनिर्देश VkFlags VkImagePipeSurfaceCreateFlagsFUCHSIA;

प्रकारनिर्देश संरचना VkImagePipeSurfaceCreateInfoFUCHSIA {
    VkStructureType                         sType;
    ध्रुव शून्य*                             p_अग्र;
    VkImagePipeSurfaceCreateFlagsFUCHSIA    flags;
    zx_handle_t                             imagePipeHandle;
} VkImagePipeSurfaceCreateInfoFUCHSIA;


प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vkCreateImagePipeSurfaceFUCHSIA)(VkInstance instance, ध्रुव VkImagePipeSurfaceCreateInfoFUCHSIA* pCreateInfo, ध्रुव Vk_आवण्टनम्_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#यदि_अपरिभाषितम् VK_NO_PROTOTYPES

#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkCreateImagePipeSurfaceFUCHSIA(
    VkInstance                                  instance,
    ध्रुव VkImagePipeSurfaceCreateInfoFUCHSIA*  pCreateInfo,
    ध्रुव Vk_आवण्टनम्_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#यदि_अन्तः
#यदि_अन्तः


// VK_FUCHSIA_external_memory is a preprocessor guard. Do not pass it to API calls.
#परिभाषय VK_FUCHSIA_external_स्मृतिः 1

#परिभाषय VK_FUCHSIA_EXTERNAL_स्मृतिः_SPEC_संस्करणम् 1
#परिभाषय VK_FUCHSIA_EXTERNAL_स्मृतिः_EXTENSION_NAME "VK_FUCHSIA_external_memory"

प्रकारनिर्देश संरचना Vk_Import_स्मृतिः_Zircon_Handle_Info_FUCHSIA {
    VkStructureType                       sType;
    ध्रुव शून्य*                           p_अग्र;
    Vk_External_स्मृतिः_Handle_Type_Flag_द्वयङ्काः    handleType;
    zx_handle_t                           handle;
} Vk_Import_स्मृतिः_Zircon_Handle_Info_FUCHSIA;

प्रकारनिर्देश संरचना Vk_स्मृतिः_Zircon_Handle_Properties_FUCHSIA {
    VkStructureType    sType;
    शून्य*              p_अग्र;
    uint32_t           स्मृतिः_Type_द्वयङ्काः;
} Vk_स्मृतिः_Zircon_Handle_Properties_FUCHSIA;

प्रकारनिर्देश संरचना Vk_स्मृतिः_Get_Zircon_Handle_Info_FUCHSIA {
    VkStructureType                       sType;
    ध्रुव शून्य*                           p_अग्र;
    Vk_Device_स्मृतिः                        स्मृतिः;
    Vk_External_स्मृतिः_Handle_Type_Flag_द्वयङ्काः    handleType;
} Vk_स्मृतिः_Get_Zircon_Handle_Info_FUCHSIA;


प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vk_Get_स्मृतिः_Zircon_Handle_FUCHSIA)(VkDevice device, ध्रुव Vk_स्मृतिः_Get_Zircon_Handle_Info_FUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle);
प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vk_Get_स्मृतिः_Zircon_Handle_Properties_FUCHSIA)(VkDevice device, Vk_External_स्मृतिः_Handle_Type_Flag_द्वयङ्काः handleType, zx_handle_t zirconHandle, Vk_स्मृतिः_Zircon_Handle_Properties_FUCHSIA* p_स्मृतिः_Zircon_Handle_Properties);

#यदि_अपरिभाषितम् VK_NO_PROTOTYPES

#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vk_Get_स्मृतिः_Zircon_Handle_FUCHSIA(
    VkDevice                                    device,
    ध्रुव Vk_स्मृतिः_Get_Zircon_Handle_Info_FUCHSIA*   pGetZirconHandleInfo,
    zx_handle_t*                                pZirconHandle);
#यदि_अन्तः
#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vk_Get_स्मृतिः_Zircon_Handle_Properties_FUCHSIA(
    VkDevice                                    device,
    Vk_External_स्मृतिः_Handle_Type_Flag_द्वयङ्काः          handleType,
    zx_handle_t                                 zirconHandle,
    Vk_स्मृतिः_Zircon_Handle_Properties_FUCHSIA*      p_स्मृतिः_Zircon_Handle_Properties);
#यदि_अन्तः
#यदि_अन्तः


// VK_FUCHSIA_external_semaphore is a preprocessor guard. Do not pass it to API calls.
#परिभाषय VK_FUCHSIA_external_semaphore 1

#परिभाषय VK_FUCHSIA_EXTERNAL_SEMAPHORE_SPEC_संस्करणम् 1
#परिभाषय VK_FUCHSIA_EXTERNAL_SEMAPHORE_EXTENSION_NAME "VK_FUCHSIA_external_semaphore"

प्रकारनिर्देश संरचना VkImportSemaphoreZirconHandleInfoFUCHSIA {
    VkStructureType                          sType;
    ध्रुव शून्य*                              p_अग्र;
    VkSemaphore                              semaphore;
    VkSemaphoreImportFlags                   flags;
    Vk_External_Semaphore_Handle_Type_Flag_द्वयङ्काः    handleType;
    zx_handle_t                              zirconHandle;
} VkImportSemaphoreZirconHandleInfoFUCHSIA;

प्रकारनिर्देश संरचना VkSemaphoreGetZirconHandleInfoFUCHSIA {
    VkStructureType                          sType;
    ध्रुव शून्य*                              p_अग्र;
    VkSemaphore                              semaphore;
    Vk_External_Semaphore_Handle_Type_Flag_द्वयङ्काः    handleType;
} VkSemaphoreGetZirconHandleInfoFUCHSIA;


प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vkImportSemaphoreZirconHandleFUCHSIA)(VkDevice device, ध्रुव VkImportSemaphoreZirconHandleInfoFUCHSIA* pImportSemaphoreZirconHandleInfo);
प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vkGetSemaphoreZirconHandleFUCHSIA)(VkDevice device, ध्रुव VkSemaphoreGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle);

#यदि_अपरिभाषितम् VK_NO_PROTOTYPES

#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkImportSemaphoreZirconHandleFUCHSIA(
    VkDevice                                    device,
    ध्रुव VkImportSemaphoreZirconHandleInfoFUCHSIA* pImportSemaphoreZirconHandleInfo);
#यदि_अन्तः
#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkGetSemaphoreZirconHandleFUCHSIA(
    VkDevice                                    device,
    ध्रुव VkSemaphoreGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo,
    zx_handle_t*                                pZirconHandle);
#यदि_अन्तः
#यदि_अन्तः


// VK_FUCHSIA_buffer_collection is a preprocessor guard. Do not pass it to API calls.
#परिभाषय VK_FUCHSIA_बफर_collection 1

VK_DEFINE_NON_DISPATCHABLE_HANDLE(Vk_बफर_Collection_FUCHSIA)

#परिभाषय VK_FUCHSIA_बफर_COLLECTION_SPEC_संस्करणम् 2
#परिभाषय VK_FUCHSIA_बफर_COLLECTION_EXTENSION_NAME "VK_FUCHSIA_buffer_collection"

प्रकारनिर्देश VkFlags VkImageFormatConstraintsFlagsFUCHSIA;

प्रकारनिर्देश गणना Vk_Image_Constraints_Info_Flag_द्वयङ्काः_FUCHSIA {
    VK_IMAGE_CONSTRAINTS_INFO_CPU_READ_RARELY_FUCHSIA = 0x00000001,
    VK_IMAGE_CONSTRAINTS_INFO_CPU_READ_OFTEN_FUCHSIA = 0x00000002,
    VK_IMAGE_CONSTRAINTS_INFO_CPU_WRITE_RARELY_FUCHSIA = 0x00000004,
    VK_IMAGE_CONSTRAINTS_INFO_CPU_WRITE_OFTEN_FUCHSIA = 0x00000008,
    VK_IMAGE_CONSTRAINTS_INFO_PROTECTED_OPTIONAL_FUCHSIA = 0x00000010,
    VK_IMAGE_CONSTRAINTS_INFO_FLAG_द्वयङ्काः_MAX_ENUM_FUCHSIA = 0x7FFFFFFF
} Vk_Image_Constraints_Info_Flag_द्वयङ्काः_FUCHSIA;
प्रकारनिर्देश VkFlags VkImageConstraintsInfoFlagsFUCHSIA;

प्रकारनिर्देश संरचना Vk_बफर_Collection_Create_Info_FUCHSIA {
    VkStructureType    sType;
    ध्रुव शून्य*        p_अग्र;
    zx_handle_t        collectionToken;
} Vk_बफर_Collection_Create_Info_FUCHSIA;

प्रकारनिर्देश संरचना Vk_Import_स्मृतिः_बफर_Collection_FUCHSIA {
    VkStructureType              sType;
    ध्रुव शून्य*                  p_अग्र;
    Vk_बफर_Collection_FUCHSIA    collection;
    uint32_t                     सूचकांक;
} Vk_Import_स्मृतिः_बफर_Collection_FUCHSIA;

प्रकारनिर्देश संरचना Vk_बफर_Collection_Image_Create_Info_FUCHSIA {
    VkStructureType              sType;
    ध्रुव शून्य*                  p_अग्र;
    Vk_बफर_Collection_FUCHSIA    collection;
    uint32_t                     सूचकांक;
} Vk_बफर_Collection_Image_Create_Info_FUCHSIA;

प्रकारनिर्देश संरचना Vk_बफर_Collection_Constraints_Info_FUCHSIA {
    VkStructureType    sType;
    ध्रुव शून्य*        p_अग्र;
    uint32_t           min_बफर_गणनम्;
    uint32_t           max_बफर_गणनम्;
    uint32_t           min_बफर_गणनम्_For_Camping;
    uint32_t           min_बफर_गणनम्_For_Dedicated_Slack;
    uint32_t           min_बफर_गणनम्_For_Shared_Slack;
} Vk_बफर_Collection_Constraints_Info_FUCHSIA;

प्रकारनिर्देश संरचना Vk_बफर_Constraints_Info_FUCHSIA {
    VkStructureType                             sType;
    ध्रुव शून्य*                                 p_अग्र;
    Vk_बफर_Create_Info                          createInfo;
    VkFormatFeatureFlags                        requiredFormatFeatures;
    Vk_बफर_Collection_Constraints_Info_FUCHSIA    बफर_Collection_Constraints;
} Vk_बफर_Constraints_Info_FUCHSIA;

प्रकारनिर्देश संरचना Vk_बफर_Collection_बफर_Create_Info_FUCHSIA {
    VkStructureType              sType;
    ध्रुव शून्य*                  p_अग्र;
    Vk_बफर_Collection_FUCHSIA    collection;
    uint32_t                     सूचकांक;
} Vk_बफर_Collection_बफर_Create_Info_FUCHSIA;

प्रकारनिर्देश संरचना VkSysmemColorSpaceFUCHSIA {
    VkStructureType    sType;
    ध्रुव शून्य*        p_अग्र;
    uint32_t           colorSpace;
} VkSysmemColorSpaceFUCHSIA;

प्रकारनिर्देश संरचना Vk_बफर_Collection_Properties_FUCHSIA {
    VkStructureType                  sType;
    शून्य*                            p_अग्र;
    uint32_t                         स्मृतिः_Type_द्वयङ्काः;
    uint32_t                         बफर_गणनम्;
    uint32_t                         create_Info_सूचकांक;
    uint64_t                         sysmemPixelFormat;
    VkFormatFeatureFlags             formatFeatures;
    VkSysmemColorSpaceFUCHSIA        sysmem_Color_Space_सूचकांक;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggested_XChroma_विस्थापनम्;
    VkChromaLocation                 suggested_YChroma_विस्थापनम्;
} Vk_बफर_Collection_Properties_FUCHSIA;

प्रकारनिर्देश संरचना VkImageFormatConstraintsInfoFUCHSIA {
    VkStructureType                         sType;
    ध्रुव शून्य*                             p_अग्र;
    VkImageCreateInfo                       imageCreateInfo;
    VkFormatFeatureFlags                    requiredFormatFeatures;
    VkImageFormatConstraintsFlagsFUCHSIA    flags;
    uint64_t                                sysmemPixelFormat;
    uint32_t                                color_Space_गणनम्;
    ध्रुव VkSysmemColorSpaceFUCHSIA*        pColorSpaces;
} VkImageFormatConstraintsInfoFUCHSIA;

प्रकारनिर्देश संरचना VkImageConstraintsInfoFUCHSIA {
    VkStructureType                               sType;
    ध्रुव शून्य*                                   p_अग्र;
    uint32_t                                      format_Constraints_गणनम्;
    ध्रुव VkImageFormatConstraintsInfoFUCHSIA*    pFormatConstraints;
    Vk_बफर_Collection_Constraints_Info_FUCHSIA      बफर_Collection_Constraints;
    VkImageConstraintsInfoFlagsFUCHSIA            flags;
} VkImageConstraintsInfoFUCHSIA;


प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vk_Create_बफर_Collection_FUCHSIA)(VkDevice device, ध्रुव Vk_बफर_Collection_Create_Info_FUCHSIA* pCreateInfo, ध्रुव Vk_आवण्टनम्_Callbacks* pAllocator, Vk_बफर_Collection_FUCHSIA* pCollection);
प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vk_समुच्चयः_बफर_Collection_Image_Constraints_FUCHSIA)(VkDevice device, Vk_बफर_Collection_FUCHSIA collection, ध्रुव VkImageConstraintsInfoFUCHSIA* pImageConstraintsInfo);
प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vk_समुच्चयः_बफर_Collection_बफर_Constraints_FUCHSIA)(VkDevice device, Vk_बफर_Collection_FUCHSIA collection, ध्रुव Vk_बफर_Constraints_Info_FUCHSIA* p_बफर_Constraints_Info);
प्रकारनिर्देश शून्य (VKAPI_PTR *PFN_vk_Destroy_बफर_Collection_FUCHSIA)(VkDevice device, Vk_बफर_Collection_FUCHSIA collection, ध्रुव Vk_आवण्टनम्_Callbacks* pAllocator);
प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vk_Get_बफर_Collection_Properties_FUCHSIA)(VkDevice device, Vk_बफर_Collection_FUCHSIA collection, Vk_बफर_Collection_Properties_FUCHSIA* pProperties);

#यदि_अपरिभाषितम् VK_NO_PROTOTYPES

#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vk_Create_बफर_Collection_FUCHSIA(
    VkDevice                                    device,
    ध्रुव Vk_बफर_Collection_Create_Info_FUCHSIA*  pCreateInfo,
    ध्रुव Vk_आवण्टनम्_Callbacks*                pAllocator,
    Vk_बफर_Collection_FUCHSIA*                  pCollection);
#यदि_अन्तः
#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vk_समुच्चयः_बफर_Collection_Image_Constraints_FUCHSIA(
    VkDevice                                    device,
    Vk_बफर_Collection_FUCHSIA                   collection,
    ध्रुव VkImageConstraintsInfoFUCHSIA*        pImageConstraintsInfo);
#यदि_अन्तः
#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vk_समुच्चयः_बफर_Collection_बफर_Constraints_FUCHSIA(
    VkDevice                                    device,
    Vk_बफर_Collection_FUCHSIA                   collection,
    ध्रुव Vk_बफर_Constraints_Info_FUCHSIA*       p_बफर_Constraints_Info);
#यदि_अन्तः
#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR शून्य VKAPI_CALL vk_Destroy_बफर_Collection_FUCHSIA(
    VkDevice                                    device,
    Vk_बफर_Collection_FUCHSIA                   collection,
    ध्रुव Vk_आवण्टनम्_Callbacks*                pAllocator);
#यदि_अन्तः
#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vk_Get_बफर_Collection_Properties_FUCHSIA(
    VkDevice                                    device,
    Vk_बफर_Collection_FUCHSIA                   collection,
    Vk_बफर_Collection_Properties_FUCHSIA*        pProperties);
#यदि_अन्तः
#यदि_अन्तः

#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

#यदि_अन्तः
