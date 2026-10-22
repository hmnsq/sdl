#جيڪڏهن_وصف_نه_ٿيل VULKAN_FUCHSIA_H_
#وصف_ڪريو VULKAN_FUCHSIA_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#جيڪڏهن_وصف_ٿيل __cplusplus
خارجي "C" {
#جيڪڏهن_پورو



// VK_FUCHSIA_imagepipe_surface is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو VK_FUCHSIA_imagepipe_surface 1

#وصف_ڪريو VK_FUCHSIA_IMAGEPIPE_SURFACE_SPEC_نسخو 1
#وصف_ڪريو VK_FUCHSIA_IMAGEPIPE_SURFACE_EXTENSION_NAME "VK_FUCHSIA_imagepipe_surface"

تعريفنوع VkFlags VkImagePipeSurfaceCreateFlagsFUCHSIA;

تعريفنوع بنية VkImagePipeSurfaceCreateInfoFUCHSIA {
    VkStructureType                         sType;
    ثابت فراغ*                             p_ايندڙ;
    VkImagePipeSurfaceCreateFlagsFUCHSIA    flags;
    zx_handle_t                             imagePipeHandle;
} VkImagePipeSurfaceCreateInfoFUCHSIA;


تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vkCreateImagePipeSurfaceFUCHSIA)(VkInstance instance, ثابت VkImagePipeSurfaceCreateInfoFUCHSIA* pCreateInfo, ثابت Vk_ورهاست_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#جيڪڏهن_وصف_نه_ٿيل VK_NO_PROTOTYPES

#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتيجو VKAPI_CALL vkCreateImagePipeSurfaceFUCHSIA(
    VkInstance                                  instance,
    ثابت VkImagePipeSurfaceCreateInfoFUCHSIA*  pCreateInfo,
    ثابت Vk_ورهاست_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#جيڪڏهن_پورو
#جيڪڏهن_پورو


// VK_FUCHSIA_external_memory is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو VK_FUCHSIA_external_يادگيري 1

#وصف_ڪريو VK_FUCHSIA_EXTERNAL_يادگيري_SPEC_نسخو 1
#وصف_ڪريو VK_FUCHSIA_EXTERNAL_يادگيري_EXTENSION_NAME "VK_FUCHSIA_external_memory"

تعريفنوع بنية Vk_Import_يادگيري_Zircon_Handle_Info_FUCHSIA {
    VkStructureType                       sType;
    ثابت فراغ*                           p_ايندڙ;
    Vk_External_يادگيري_Handle_Type_Flag_بٽ    handleType;
    zx_handle_t                           handle;
} Vk_Import_يادگيري_Zircon_Handle_Info_FUCHSIA;

تعريفنوع بنية Vk_يادگيري_Zircon_Handle_Properties_FUCHSIA {
    VkStructureType    sType;
    فراغ*              p_ايندڙ;
    uint32_t           يادگيري_Type_بٽ;
} Vk_يادگيري_Zircon_Handle_Properties_FUCHSIA;

تعريفنوع بنية Vk_يادگيري_Get_Zircon_Handle_Info_FUCHSIA {
    VkStructureType                       sType;
    ثابت فراغ*                           p_ايندڙ;
    Vk_Device_يادگيري                        يادگيري;
    Vk_External_يادگيري_Handle_Type_Flag_بٽ    handleType;
} Vk_يادگيري_Get_Zircon_Handle_Info_FUCHSIA;


تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vk_Get_يادگيري_Zircon_Handle_FUCHSIA)(VkDevice device, ثابت Vk_يادگيري_Get_Zircon_Handle_Info_FUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle);
تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vk_Get_يادگيري_Zircon_Handle_Properties_FUCHSIA)(VkDevice device, Vk_External_يادگيري_Handle_Type_Flag_بٽ handleType, zx_handle_t zirconHandle, Vk_يادگيري_Zircon_Handle_Properties_FUCHSIA* p_يادگيري_Zircon_Handle_Properties);

#جيڪڏهن_وصف_نه_ٿيل VK_NO_PROTOTYPES

#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتيجو VKAPI_CALL vk_Get_يادگيري_Zircon_Handle_FUCHSIA(
    VkDevice                                    device,
    ثابت Vk_يادگيري_Get_Zircon_Handle_Info_FUCHSIA*   pGetZirconHandleInfo,
    zx_handle_t*                                pZirconHandle);
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتيجو VKAPI_CALL vk_Get_يادگيري_Zircon_Handle_Properties_FUCHSIA(
    VkDevice                                    device,
    Vk_External_يادگيري_Handle_Type_Flag_بٽ          handleType,
    zx_handle_t                                 zirconHandle,
    Vk_يادگيري_Zircon_Handle_Properties_FUCHSIA*      p_يادگيري_Zircon_Handle_Properties);
#جيڪڏهن_پورو
#جيڪڏهن_پورو


// VK_FUCHSIA_external_semaphore is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو VK_FUCHSIA_external_semaphore 1

#وصف_ڪريو VK_FUCHSIA_EXTERNAL_SEMAPHORE_SPEC_نسخو 1
#وصف_ڪريو VK_FUCHSIA_EXTERNAL_SEMAPHORE_EXTENSION_NAME "VK_FUCHSIA_external_semaphore"

تعريفنوع بنية VkImportSemaphoreZirconHandleInfoFUCHSIA {
    VkStructureType                          sType;
    ثابت فراغ*                              p_ايندڙ;
    VkSemaphore                              semaphore;
    VkSemaphoreImportFlags                   flags;
    Vk_External_Semaphore_Handle_Type_Flag_بٽ    handleType;
    zx_handle_t                              zirconHandle;
} VkImportSemaphoreZirconHandleInfoFUCHSIA;

تعريفنوع بنية VkSemaphoreGetZirconHandleInfoFUCHSIA {
    VkStructureType                          sType;
    ثابت فراغ*                              p_ايندڙ;
    VkSemaphore                              semaphore;
    Vk_External_Semaphore_Handle_Type_Flag_بٽ    handleType;
} VkSemaphoreGetZirconHandleInfoFUCHSIA;


تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vkImportSemaphoreZirconHandleFUCHSIA)(VkDevice device, ثابت VkImportSemaphoreZirconHandleInfoFUCHSIA* pImportSemaphoreZirconHandleInfo);
تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vkGetSemaphoreZirconHandleFUCHSIA)(VkDevice device, ثابت VkSemaphoreGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle);

#جيڪڏهن_وصف_نه_ٿيل VK_NO_PROTOTYPES

#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتيجو VKAPI_CALL vkImportSemaphoreZirconHandleFUCHSIA(
    VkDevice                                    device,
    ثابت VkImportSemaphoreZirconHandleInfoFUCHSIA* pImportSemaphoreZirconHandleInfo);
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتيجو VKAPI_CALL vkGetSemaphoreZirconHandleFUCHSIA(
    VkDevice                                    device,
    ثابت VkSemaphoreGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo,
    zx_handle_t*                                pZirconHandle);
#جيڪڏهن_پورو
#جيڪڏهن_پورو


// VK_FUCHSIA_buffer_collection is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو VK_FUCHSIA_بفر_collection 1

VK_DEFINE_NON_DISPATCHABLE_HANDLE(Vk_بفر_Collection_FUCHSIA)

#وصف_ڪريو VK_FUCHSIA_بفر_COLLECTION_SPEC_نسخو 2
#وصف_ڪريو VK_FUCHSIA_بفر_COLLECTION_EXTENSION_NAME "VK_FUCHSIA_buffer_collection"

تعريفنوع VkFlags VkImageFormatConstraintsFlagsFUCHSIA;

تعريفنوع تعداد Vk_Image_Constraints_Info_Flag_بٽ_FUCHSIA {
    VK_IMAGE_CONSTRAINTS_INFO_CPU_READ_RARELY_FUCHSIA = 0x00000001,
    VK_IMAGE_CONSTRAINTS_INFO_CPU_READ_OFTEN_FUCHSIA = 0x00000002,
    VK_IMAGE_CONSTRAINTS_INFO_CPU_WRITE_RARELY_FUCHSIA = 0x00000004,
    VK_IMAGE_CONSTRAINTS_INFO_CPU_WRITE_OFTEN_FUCHSIA = 0x00000008,
    VK_IMAGE_CONSTRAINTS_INFO_PROTECTED_OPTIONAL_FUCHSIA = 0x00000010,
    VK_IMAGE_CONSTRAINTS_INFO_FLAG_بٽ_MAX_ENUM_FUCHSIA = 0x7FFFFFFF
} Vk_Image_Constraints_Info_Flag_بٽ_FUCHSIA;
تعريفنوع VkFlags VkImageConstraintsInfoFlagsFUCHSIA;

تعريفنوع بنية Vk_بفر_Collection_Create_Info_FUCHSIA {
    VkStructureType    sType;
    ثابت فراغ*        p_ايندڙ;
    zx_handle_t        collectionToken;
} Vk_بفر_Collection_Create_Info_FUCHSIA;

تعريفنوع بنية Vk_Import_يادگيري_بفر_Collection_FUCHSIA {
    VkStructureType              sType;
    ثابت فراغ*                  p_ايندڙ;
    Vk_بفر_Collection_FUCHSIA    collection;
    uint32_t                     اشاريو;
} Vk_Import_يادگيري_بفر_Collection_FUCHSIA;

تعريفنوع بنية Vk_بفر_Collection_Image_Create_Info_FUCHSIA {
    VkStructureType              sType;
    ثابت فراغ*                  p_ايندڙ;
    Vk_بفر_Collection_FUCHSIA    collection;
    uint32_t                     اشاريو;
} Vk_بفر_Collection_Image_Create_Info_FUCHSIA;

تعريفنوع بنية Vk_بفر_Collection_Constraints_Info_FUCHSIA {
    VkStructureType    sType;
    ثابت فراغ*        p_ايندڙ;
    uint32_t           min_بفر_ڳڻپ;
    uint32_t           max_بفر_ڳڻپ;
    uint32_t           min_بفر_ڳڻپ_For_Camping;
    uint32_t           min_بفر_ڳڻپ_For_Dedicated_Slack;
    uint32_t           min_بفر_ڳڻپ_For_Shared_Slack;
} Vk_بفر_Collection_Constraints_Info_FUCHSIA;

تعريفنوع بنية Vk_بفر_Constraints_Info_FUCHSIA {
    VkStructureType                             sType;
    ثابت فراغ*                                 p_ايندڙ;
    Vk_بفر_Create_Info                          createInfo;
    VkFormatFeatureFlags                        requiredFormatFeatures;
    Vk_بفر_Collection_Constraints_Info_FUCHSIA    بفر_Collection_Constraints;
} Vk_بفر_Constraints_Info_FUCHSIA;

تعريفنوع بنية Vk_بفر_Collection_بفر_Create_Info_FUCHSIA {
    VkStructureType              sType;
    ثابت فراغ*                  p_ايندڙ;
    Vk_بفر_Collection_FUCHSIA    collection;
    uint32_t                     اشاريو;
} Vk_بفر_Collection_بفر_Create_Info_FUCHSIA;

تعريفنوع بنية VkSysmemColorSpaceFUCHSIA {
    VkStructureType    sType;
    ثابت فراغ*        p_ايندڙ;
    uint32_t           colorSpace;
} VkSysmemColorSpaceFUCHSIA;

تعريفنوع بنية Vk_بفر_Collection_Properties_FUCHSIA {
    VkStructureType                  sType;
    فراغ*                            p_ايندڙ;
    uint32_t                         يادگيري_Type_بٽ;
    uint32_t                         بفر_ڳڻپ;
    uint32_t                         create_Info_اشاريو;
    uint64_t                         sysmemPixelFormat;
    VkFormatFeatureFlags             formatFeatures;
    VkSysmemColorSpaceFUCHSIA        sysmem_Color_Space_اشاريو;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggested_XChroma_وٿي;
    VkChromaLocation                 suggested_YChroma_وٿي;
} Vk_بفر_Collection_Properties_FUCHSIA;

تعريفنوع بنية VkImageFormatConstraintsInfoFUCHSIA {
    VkStructureType                         sType;
    ثابت فراغ*                             p_ايندڙ;
    VkImageCreateInfo                       imageCreateInfo;
    VkFormatFeatureFlags                    requiredFormatFeatures;
    VkImageFormatConstraintsFlagsFUCHSIA    flags;
    uint64_t                                sysmemPixelFormat;
    uint32_t                                color_Space_ڳڻپ;
    ثابت VkSysmemColorSpaceFUCHSIA*        pColorSpaces;
} VkImageFormatConstraintsInfoFUCHSIA;

تعريفنوع بنية VkImageConstraintsInfoFUCHSIA {
    VkStructureType                               sType;
    ثابت فراغ*                                   p_ايندڙ;
    uint32_t                                      format_Constraints_ڳڻپ;
    ثابت VkImageFormatConstraintsInfoFUCHSIA*    pFormatConstraints;
    Vk_بفر_Collection_Constraints_Info_FUCHSIA      بفر_Collection_Constraints;
    VkImageConstraintsInfoFlagsFUCHSIA            flags;
} VkImageConstraintsInfoFUCHSIA;


تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vk_Create_بفر_Collection_FUCHSIA)(VkDevice device, ثابت Vk_بفر_Collection_Create_Info_FUCHSIA* pCreateInfo, ثابت Vk_ورهاست_Callbacks* pAllocator, Vk_بفر_Collection_FUCHSIA* pCollection);
تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vk_سيٽ_بفر_Collection_Image_Constraints_FUCHSIA)(VkDevice device, Vk_بفر_Collection_FUCHSIA collection, ثابت VkImageConstraintsInfoFUCHSIA* pImageConstraintsInfo);
تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vk_سيٽ_بفر_Collection_بفر_Constraints_FUCHSIA)(VkDevice device, Vk_بفر_Collection_FUCHSIA collection, ثابت Vk_بفر_Constraints_Info_FUCHSIA* p_بفر_Constraints_Info);
تعريفنوع فراغ (VKAPI_PTR *PFN_vk_Destroy_بفر_Collection_FUCHSIA)(VkDevice device, Vk_بفر_Collection_FUCHSIA collection, ثابت Vk_ورهاست_Callbacks* pAllocator);
تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vk_Get_بفر_Collection_Properties_FUCHSIA)(VkDevice device, Vk_بفر_Collection_FUCHSIA collection, Vk_بفر_Collection_Properties_FUCHSIA* pProperties);

#جيڪڏهن_وصف_نه_ٿيل VK_NO_PROTOTYPES

#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتيجو VKAPI_CALL vk_Create_بفر_Collection_FUCHSIA(
    VkDevice                                    device,
    ثابت Vk_بفر_Collection_Create_Info_FUCHSIA*  pCreateInfo,
    ثابت Vk_ورهاست_Callbacks*                pAllocator,
    Vk_بفر_Collection_FUCHSIA*                  pCollection);
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتيجو VKAPI_CALL vk_سيٽ_بفر_Collection_Image_Constraints_FUCHSIA(
    VkDevice                                    device,
    Vk_بفر_Collection_FUCHSIA                   collection,
    ثابت VkImageConstraintsInfoFUCHSIA*        pImageConstraintsInfo);
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتيجو VKAPI_CALL vk_سيٽ_بفر_Collection_بفر_Constraints_FUCHSIA(
    VkDevice                                    device,
    Vk_بفر_Collection_FUCHSIA                   collection,
    ثابت Vk_بفر_Constraints_Info_FUCHSIA*       p_بفر_Constraints_Info);
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR فراغ VKAPI_CALL vk_Destroy_بفر_Collection_FUCHSIA(
    VkDevice                                    device,
    Vk_بفر_Collection_FUCHSIA                   collection,
    ثابت Vk_ورهاست_Callbacks*                pAllocator);
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتيجو VKAPI_CALL vk_Get_بفر_Collection_Properties_FUCHSIA(
    VkDevice                                    device,
    Vk_بفر_Collection_FUCHSIA                   collection,
    Vk_بفر_Collection_Properties_FUCHSIA*        pProperties);
#جيڪڏهن_پورو
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل __cplusplus
}
#جيڪڏهن_پورو

#جيڪڏهن_پورو
