#अगर_अघोषित VULKAN_FUCHSIA_H_
#घोषणा VULKAN_FUCHSIA_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#अगर_घोषित __cplusplus
बाह्य "C" {
#पूर्ण_अगर



// VK_FUCHSIA_imagepipe_surface is a preprocessor guard. Do not pass it to API calls.
#घोषणा VK_FUCHSIA_imagepipe_surface 1

#घोषणा VK_FUCHSIA_IMAGEPIPE_SURFACE_SPEC_VERSION 1
#घोषणा VK_FUCHSIA_IMAGEPIPE_SURFACE_EXTENSION_NAME "VK_FUCHSIA_imagepipe_surface"

प्रकार VkFlags VkImagePipeSurfaceCreateFlagsFUCHSIA;

प्रकार काष्ठा VkImagePipeSurfaceCreateInfoFUCHSIA {
    VkStructureType                         sType;
    स्थिर व्योम*                             p_अग्र;
    VkImagePipeSurfaceCreateFlagsFUCHSIA    flags;
    zx_handle_t                             imagePipeHandle;
} VkImagePipeSurfaceCreateInfoFUCHSIA;


प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vkCreateImagePipeSurfaceFUCHSIA)(VkInstance instance, स्थिर VkImagePipeSurfaceCreateInfoFUCHSIA* pCreateInfo, स्थिर VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

#अगर_अघोषित VK_NO_PROTOTYPES

#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkCreateImagePipeSurfaceFUCHSIA(
    VkInstance                                  instance,
    स्थिर VkImagePipeSurfaceCreateInfoFUCHSIA*  pCreateInfo,
    स्थिर VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#पूर्ण_अगर
#पूर्ण_अगर


// VK_FUCHSIA_external_memory is a preprocessor guard. Do not pass it to API calls.
#घोषणा VK_FUCHSIA_external_memory 1

#घोषणा VK_FUCHSIA_EXTERNAL_MEMORY_SPEC_VERSION 1
#घोषणा VK_FUCHSIA_EXTERNAL_MEMORY_EXTENSION_NAME "VK_FUCHSIA_external_memory"

प्रकार काष्ठा VkImportMemoryZirconHandleInfoFUCHSIA {
    VkStructureType                       sType;
    स्थिर व्योम*                           p_अग्र;
    VkExternalMemoryHandleTypeFlagBits    handleType;
    zx_handle_t                           handle;
} VkImportMemoryZirconHandleInfoFUCHSIA;

प्रकार काष्ठा VkMemoryZirconHandlePropertiesFUCHSIA {
    VkStructureType    sType;
    व्योम*              p_अग्र;
    uint32_t           memoryTypeBits;
} VkMemoryZirconHandlePropertiesFUCHSIA;

प्रकार काष्ठा VkMemoryGetZirconHandleInfoFUCHSIA {
    VkStructureType                       sType;
    स्थिर व्योम*                           p_अग्र;
    VkDeviceMemory                        memory;
    VkExternalMemoryHandleTypeFlagBits    handleType;
} VkMemoryGetZirconHandleInfoFUCHSIA;


प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vkGetMemoryZirconHandleFUCHSIA)(VkDevice device, स्थिर VkMemoryGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle);
प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vkGetMemoryZirconHandlePropertiesFUCHSIA)(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, zx_handle_t zirconHandle, VkMemoryZirconHandlePropertiesFUCHSIA* pMemoryZirconHandleProperties);

#अगर_अघोषित VK_NO_PROTOTYPES

#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkGetMemoryZirconHandleFUCHSIA(
    VkDevice                                    device,
    स्थिर VkMemoryGetZirconHandleInfoFUCHSIA*   pGetZirconHandleInfo,
    zx_handle_t*                                pZirconHandle);
#पूर्ण_अगर
#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkGetMemoryZirconHandlePropertiesFUCHSIA(
    VkDevice                                    device,
    VkExternalMemoryHandleTypeFlagBits          handleType,
    zx_handle_t                                 zirconHandle,
    VkMemoryZirconHandlePropertiesFUCHSIA*      pMemoryZirconHandleProperties);
#पूर्ण_अगर
#पूर्ण_अगर


// VK_FUCHSIA_external_semaphore is a preprocessor guard. Do not pass it to API calls.
#घोषणा VK_FUCHSIA_external_semaphore 1

#घोषणा VK_FUCHSIA_EXTERNAL_SEMAPHORE_SPEC_VERSION 1
#घोषणा VK_FUCHSIA_EXTERNAL_SEMAPHORE_EXTENSION_NAME "VK_FUCHSIA_external_semaphore"

प्रकार काष्ठा VkImportSemaphoreZirconHandleInfoFUCHSIA {
    VkStructureType                          sType;
    स्थिर व्योम*                              p_अग्र;
    VkSemaphore                              semaphore;
    VkSemaphoreImportFlags                   flags;
    VkExternalSemaphoreHandleTypeFlagBits    handleType;
    zx_handle_t                              zirconHandle;
} VkImportSemaphoreZirconHandleInfoFUCHSIA;

प्रकार काष्ठा VkSemaphoreGetZirconHandleInfoFUCHSIA {
    VkStructureType                          sType;
    स्थिर व्योम*                              p_अग्र;
    VkSemaphore                              semaphore;
    VkExternalSemaphoreHandleTypeFlagBits    handleType;
} VkSemaphoreGetZirconHandleInfoFUCHSIA;


प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vkImportSemaphoreZirconHandleFUCHSIA)(VkDevice device, स्थिर VkImportSemaphoreZirconHandleInfoFUCHSIA* pImportSemaphoreZirconHandleInfo);
प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vkGetSemaphoreZirconHandleFUCHSIA)(VkDevice device, स्थिर VkSemaphoreGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle);

#अगर_अघोषित VK_NO_PROTOTYPES

#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkImportSemaphoreZirconHandleFUCHSIA(
    VkDevice                                    device,
    स्थिर VkImportSemaphoreZirconHandleInfoFUCHSIA* pImportSemaphoreZirconHandleInfo);
#पूर्ण_अगर
#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkGetSemaphoreZirconHandleFUCHSIA(
    VkDevice                                    device,
    स्थिर VkSemaphoreGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo,
    zx_handle_t*                                pZirconHandle);
#पूर्ण_अगर
#पूर्ण_अगर


// VK_FUCHSIA_buffer_collection is a preprocessor guard. Do not pass it to API calls.
#घोषणा VK_FUCHSIA_बफर_collection 1

VK_DEFINE_NON_DISPATCHABLE_HANDLE(Vk_बफर_Collection_FUCHSIA)

#घोषणा VK_FUCHSIA_बफर_COLLECTION_SPEC_VERSION 2
#घोषणा VK_FUCHSIA_बफर_COLLECTION_EXTENSION_NAME "VK_FUCHSIA_buffer_collection"

प्रकार VkFlags VkImageFormatConstraintsFlagsFUCHSIA;

प्रकार क्रमागत VkImageConstraintsInfoFlagBitsFUCHSIA {
    VK_IMAGE_CONSTRAINTS_INFO_CPU_READ_RARELY_FUCHSIA = 0x00000001,
    VK_IMAGE_CONSTRAINTS_INFO_CPU_READ_OFTEN_FUCHSIA = 0x00000002,
    VK_IMAGE_CONSTRAINTS_INFO_CPU_WRITE_RARELY_FUCHSIA = 0x00000004,
    VK_IMAGE_CONSTRAINTS_INFO_CPU_WRITE_OFTEN_FUCHSIA = 0x00000008,
    VK_IMAGE_CONSTRAINTS_INFO_PROTECTED_OPTIONAL_FUCHSIA = 0x00000010,
    VK_IMAGE_CONSTRAINTS_INFO_FLAG_BITS_MAX_ENUM_FUCHSIA = 0x7FFFFFFF
} VkImageConstraintsInfoFlagBitsFUCHSIA;
प्रकार VkFlags VkImageConstraintsInfoFlagsFUCHSIA;

प्रकार काष्ठा Vk_बफर_Collection_Create_Info_FUCHSIA {
    VkStructureType    sType;
    स्थिर व्योम*        p_अग्र;
    zx_handle_t        collectionToken;
} Vk_बफर_Collection_Create_Info_FUCHSIA;

प्रकार काष्ठा Vk_Import_Memory_बफर_Collection_FUCHSIA {
    VkStructureType              sType;
    स्थिर व्योम*                  p_अग्र;
    Vk_बफर_Collection_FUCHSIA    collection;
    uint32_t                     सूचकांक;
} Vk_Import_Memory_बफर_Collection_FUCHSIA;

प्रकार काष्ठा Vk_बफर_Collection_Image_Create_Info_FUCHSIA {
    VkStructureType              sType;
    स्थिर व्योम*                  p_अग्र;
    Vk_बफर_Collection_FUCHSIA    collection;
    uint32_t                     सूचकांक;
} Vk_बफर_Collection_Image_Create_Info_FUCHSIA;

प्रकार काष्ठा Vk_बफर_Collection_Constraints_Info_FUCHSIA {
    VkStructureType    sType;
    स्थिर व्योम*        p_अग्र;
    uint32_t           min_बफर_गिनती;
    uint32_t           max_बफर_गिनती;
    uint32_t           min_बफर_गिनती_For_Camping;
    uint32_t           min_बफर_गिनती_For_Dedicated_Slack;
    uint32_t           min_बफर_गिनती_For_Shared_Slack;
} Vk_बफर_Collection_Constraints_Info_FUCHSIA;

प्रकार काष्ठा Vk_बफर_Constraints_Info_FUCHSIA {
    VkStructureType                             sType;
    स्थिर व्योम*                                 p_अग्र;
    Vk_बफर_Create_Info                          createInfo;
    VkFormatFeatureFlags                        requiredFormatFeatures;
    Vk_बफर_Collection_Constraints_Info_FUCHSIA    बफर_Collection_Constraints;
} Vk_बफर_Constraints_Info_FUCHSIA;

प्रकार काष्ठा Vk_बफर_Collection_बफर_Create_Info_FUCHSIA {
    VkStructureType              sType;
    स्थिर व्योम*                  p_अग्र;
    Vk_बफर_Collection_FUCHSIA    collection;
    uint32_t                     सूचकांक;
} Vk_बफर_Collection_बफर_Create_Info_FUCHSIA;

प्रकार काष्ठा VkSysmemColorSpaceFUCHSIA {
    VkStructureType    sType;
    स्थिर व्योम*        p_अग्र;
    uint32_t           colorSpace;
} VkSysmemColorSpaceFUCHSIA;

प्रकार काष्ठा Vk_बफर_Collection_Properties_FUCHSIA {
    VkStructureType                  sType;
    व्योम*                            p_अग्र;
    uint32_t                         memoryTypeBits;
    uint32_t                         बफर_गिनती;
    uint32_t                         create_Info_सूचकांक;
    uint64_t                         sysmemPixelFormat;
    VkFormatFeatureFlags             formatFeatures;
    VkSysmemColorSpaceFUCHSIA        sysmem_Color_Space_सूचकांक;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggestedXChromaOffset;
    VkChromaLocation                 suggestedYChromaOffset;
} Vk_बफर_Collection_Properties_FUCHSIA;

प्रकार काष्ठा VkImageFormatConstraintsInfoFUCHSIA {
    VkStructureType                         sType;
    स्थिर व्योम*                             p_अग्र;
    VkImageCreateInfo                       imageCreateInfo;
    VkFormatFeatureFlags                    requiredFormatFeatures;
    VkImageFormatConstraintsFlagsFUCHSIA    flags;
    uint64_t                                sysmemPixelFormat;
    uint32_t                                color_Space_गिनती;
    स्थिर VkSysmemColorSpaceFUCHSIA*        pColorSpaces;
} VkImageFormatConstraintsInfoFUCHSIA;

प्रकार काष्ठा VkImageConstraintsInfoFUCHSIA {
    VkStructureType                               sType;
    स्थिर व्योम*                                   p_अग्र;
    uint32_t                                      format_Constraints_गिनती;
    स्थिर VkImageFormatConstraintsInfoFUCHSIA*    pFormatConstraints;
    Vk_बफर_Collection_Constraints_Info_FUCHSIA      बफर_Collection_Constraints;
    VkImageConstraintsInfoFlagsFUCHSIA            flags;
} VkImageConstraintsInfoFUCHSIA;


प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vk_Create_बफर_Collection_FUCHSIA)(VkDevice device, स्थिर Vk_बफर_Collection_Create_Info_FUCHSIA* pCreateInfo, स्थिर VkAllocationCallbacks* pAllocator, Vk_बफर_Collection_FUCHSIA* pCollection);
प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vk_Set_बफर_Collection_Image_Constraints_FUCHSIA)(VkDevice device, Vk_बफर_Collection_FUCHSIA collection, स्थिर VkImageConstraintsInfoFUCHSIA* pImageConstraintsInfo);
प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vk_Set_बफर_Collection_बफर_Constraints_FUCHSIA)(VkDevice device, Vk_बफर_Collection_FUCHSIA collection, स्थिर Vk_बफर_Constraints_Info_FUCHSIA* p_बफर_Constraints_Info);
प्रकार व्योम (VKAPI_PTR *PFN_vk_Destroy_बफर_Collection_FUCHSIA)(VkDevice device, Vk_बफर_Collection_FUCHSIA collection, स्थिर VkAllocationCallbacks* pAllocator);
प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vk_Get_बफर_Collection_Properties_FUCHSIA)(VkDevice device, Vk_बफर_Collection_FUCHSIA collection, Vk_बफर_Collection_Properties_FUCHSIA* pProperties);

#अगर_अघोषित VK_NO_PROTOTYPES

#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vk_Create_बफर_Collection_FUCHSIA(
    VkDevice                                    device,
    स्थिर Vk_बफर_Collection_Create_Info_FUCHSIA*  pCreateInfo,
    स्थिर VkAllocationCallbacks*                pAllocator,
    Vk_बफर_Collection_FUCHSIA*                  pCollection);
#पूर्ण_अगर
#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vk_Set_बफर_Collection_Image_Constraints_FUCHSIA(
    VkDevice                                    device,
    Vk_बफर_Collection_FUCHSIA                   collection,
    स्थिर VkImageConstraintsInfoFUCHSIA*        pImageConstraintsInfo);
#पूर्ण_अगर
#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vk_Set_बफर_Collection_बफर_Constraints_FUCHSIA(
    VkDevice                                    device,
    Vk_बफर_Collection_FUCHSIA                   collection,
    स्थिर Vk_बफर_Constraints_Info_FUCHSIA*       p_बफर_Constraints_Info);
#पूर्ण_अगर
#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR व्योम VKAPI_CALL vk_Destroy_बफर_Collection_FUCHSIA(
    VkDevice                                    device,
    Vk_बफर_Collection_FUCHSIA                   collection,
    स्थिर VkAllocationCallbacks*                pAllocator);
#पूर्ण_अगर
#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vk_Get_बफर_Collection_Properties_FUCHSIA(
    VkDevice                                    device,
    Vk_बफर_Collection_FUCHSIA                   collection,
    Vk_बफर_Collection_Properties_FUCHSIA*        pProperties);
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_घोषित __cplusplus
}
#पूर्ण_अगर

#पूर्ण_अगर
