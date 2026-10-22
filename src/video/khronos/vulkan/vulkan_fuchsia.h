#که_نه_تعریف_شوی VULKAN_FUCHSIA_H_
#تعریف_کړه VULKAN_FUCHSIA_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#که_تعریف_شوی __cplusplus
خارجي "C" {
#د_که_پای



// VK_FUCHSIA_imagepipe_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه VK_FUCHSIA_imagepipe_surface 1

#تعریف_کړه VK_FUCHSIA_IMAGEPIPE_SURFACE_SPEC_نسخه 1
#تعریف_کړه VK_FUCHSIA_IMAGEPIPE_SURFACE_EXTENSION_NAME "VK_FUCHSIA_imagepipe_surface"

تعريفنوع VkFlags VkImagePipeSurfaceCreateFlagsFUCHSIA;

تعريفنوع بنية VkImagePipeSurfaceCreateInfoFUCHSIA {
    VkStructureType                         sType;
    ثابت فراغ*                             p_بل;
    VkImagePipeSurfaceCreateFlagsFUCHSIA    flags;
    zx_handle_t                             imagePipeHandle;
} VkImagePipeSurfaceCreateInfoFUCHSIA;


تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vkCreateImagePipeSurfaceFUCHSIA)(VkInstance instance, ثابت VkImagePipeSurfaceCreateInfoFUCHSIA* pCreateInfo, ثابت Vk_ویش_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#که_نه_تعریف_شوی VK_NO_PROTOTYPES

#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_پایله VKAPI_CALL vkCreateImagePipeSurfaceFUCHSIA(
    VkInstance                                  instance,
    ثابت VkImagePipeSurfaceCreateInfoFUCHSIA*  pCreateInfo,
    ثابت Vk_ویش_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#د_که_پای
#د_که_پای


// VK_FUCHSIA_external_memory is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه VK_FUCHSIA_external_حافظه 1

#تعریف_کړه VK_FUCHSIA_EXTERNAL_حافظه_SPEC_نسخه 1
#تعریف_کړه VK_FUCHSIA_EXTERNAL_حافظه_EXTENSION_NAME "VK_FUCHSIA_external_memory"

تعريفنوع بنية Vk_Import_حافظه_Zircon_Handle_Info_FUCHSIA {
    VkStructureType                       sType;
    ثابت فراغ*                           p_بل;
    Vk_External_حافظه_Handle_Type_Flag_بټونه    handleType;
    zx_handle_t                           handle;
} Vk_Import_حافظه_Zircon_Handle_Info_FUCHSIA;

تعريفنوع بنية Vk_حافظه_Zircon_Handle_Properties_FUCHSIA {
    VkStructureType    sType;
    فراغ*              p_بل;
    uint32_t           حافظه_Type_بټونه;
} Vk_حافظه_Zircon_Handle_Properties_FUCHSIA;

تعريفنوع بنية Vk_حافظه_Get_Zircon_Handle_Info_FUCHSIA {
    VkStructureType                       sType;
    ثابت فراغ*                           p_بل;
    Vk_Device_حافظه                        حافظه;
    Vk_External_حافظه_Handle_Type_Flag_بټونه    handleType;
} Vk_حافظه_Get_Zircon_Handle_Info_FUCHSIA;


تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vk_Get_حافظه_Zircon_Handle_FUCHSIA)(VkDevice device, ثابت Vk_حافظه_Get_Zircon_Handle_Info_FUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle);
تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vk_Get_حافظه_Zircon_Handle_Properties_FUCHSIA)(VkDevice device, Vk_External_حافظه_Handle_Type_Flag_بټونه handleType, zx_handle_t zirconHandle, Vk_حافظه_Zircon_Handle_Properties_FUCHSIA* p_حافظه_Zircon_Handle_Properties);

#که_نه_تعریف_شوی VK_NO_PROTOTYPES

#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_پایله VKAPI_CALL vk_Get_حافظه_Zircon_Handle_FUCHSIA(
    VkDevice                                    device,
    ثابت Vk_حافظه_Get_Zircon_Handle_Info_FUCHSIA*   pGetZirconHandleInfo,
    zx_handle_t*                                pZirconHandle);
#د_که_پای
#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_پایله VKAPI_CALL vk_Get_حافظه_Zircon_Handle_Properties_FUCHSIA(
    VkDevice                                    device,
    Vk_External_حافظه_Handle_Type_Flag_بټونه          handleType,
    zx_handle_t                                 zirconHandle,
    Vk_حافظه_Zircon_Handle_Properties_FUCHSIA*      p_حافظه_Zircon_Handle_Properties);
#د_که_پای
#د_که_پای


// VK_FUCHSIA_external_semaphore is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه VK_FUCHSIA_external_semaphore 1

#تعریف_کړه VK_FUCHSIA_EXTERNAL_SEMAPHORE_SPEC_نسخه 1
#تعریف_کړه VK_FUCHSIA_EXTERNAL_SEMAPHORE_EXTENSION_NAME "VK_FUCHSIA_external_semaphore"

تعريفنوع بنية VkImportSemaphoreZirconHandleInfoFUCHSIA {
    VkStructureType                          sType;
    ثابت فراغ*                              p_بل;
    VkSemaphore                              semaphore;
    VkSemaphoreImportFlags                   flags;
    Vk_External_Semaphore_Handle_Type_Flag_بټونه    handleType;
    zx_handle_t                              zirconHandle;
} VkImportSemaphoreZirconHandleInfoFUCHSIA;

تعريفنوع بنية VkSemaphoreGetZirconHandleInfoFUCHSIA {
    VkStructureType                          sType;
    ثابت فراغ*                              p_بل;
    VkSemaphore                              semaphore;
    Vk_External_Semaphore_Handle_Type_Flag_بټونه    handleType;
} VkSemaphoreGetZirconHandleInfoFUCHSIA;


تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vkImportSemaphoreZirconHandleFUCHSIA)(VkDevice device, ثابت VkImportSemaphoreZirconHandleInfoFUCHSIA* pImportSemaphoreZirconHandleInfo);
تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vkGetSemaphoreZirconHandleFUCHSIA)(VkDevice device, ثابت VkSemaphoreGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle);

#که_نه_تعریف_شوی VK_NO_PROTOTYPES

#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_پایله VKAPI_CALL vkImportSemaphoreZirconHandleFUCHSIA(
    VkDevice                                    device,
    ثابت VkImportSemaphoreZirconHandleInfoFUCHSIA* pImportSemaphoreZirconHandleInfo);
#د_که_پای
#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_پایله VKAPI_CALL vkGetSemaphoreZirconHandleFUCHSIA(
    VkDevice                                    device,
    ثابت VkSemaphoreGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo,
    zx_handle_t*                                pZirconHandle);
#د_که_پای
#د_که_پای


// VK_FUCHSIA_buffer_collection is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه VK_FUCHSIA_بفر_collection 1

VK_DEFINE_NON_DISPATCHABLE_HANDLE(Vk_بفر_Collection_FUCHSIA)

#تعریف_کړه VK_FUCHSIA_بفر_COLLECTION_SPEC_نسخه 2
#تعریف_کړه VK_FUCHSIA_بفر_COLLECTION_EXTENSION_NAME "VK_FUCHSIA_buffer_collection"

تعريفنوع VkFlags VkImageFormatConstraintsFlagsFUCHSIA;

تعريفنوع تعداد Vk_Image_Constraints_Info_Flag_بټونه_FUCHSIA {
    VK_IMAGE_CONSTRAINTS_INFO_CPU_READ_RARELY_FUCHSIA = 0x00000001,
    VK_IMAGE_CONSTRAINTS_INFO_CPU_READ_OFTEN_FUCHSIA = 0x00000002,
    VK_IMAGE_CONSTRAINTS_INFO_CPU_WRITE_RARELY_FUCHSIA = 0x00000004,
    VK_IMAGE_CONSTRAINTS_INFO_CPU_WRITE_OFTEN_FUCHSIA = 0x00000008,
    VK_IMAGE_CONSTRAINTS_INFO_PROTECTED_OPTIONAL_FUCHSIA = 0x00000010,
    VK_IMAGE_CONSTRAINTS_INFO_FLAG_بټونه_MAX_ENUM_FUCHSIA = 0x7FFFFFFF
} Vk_Image_Constraints_Info_Flag_بټونه_FUCHSIA;
تعريفنوع VkFlags VkImageConstraintsInfoFlagsFUCHSIA;

تعريفنوع بنية Vk_بفر_Collection_Create_Info_FUCHSIA {
    VkStructureType    sType;
    ثابت فراغ*        p_بل;
    zx_handle_t        collectionToken;
} Vk_بفر_Collection_Create_Info_FUCHSIA;

تعريفنوع بنية Vk_Import_حافظه_بفر_Collection_FUCHSIA {
    VkStructureType              sType;
    ثابت فراغ*                  p_بل;
    Vk_بفر_Collection_FUCHSIA    collection;
    uint32_t                     شاخص;
} Vk_Import_حافظه_بفر_Collection_FUCHSIA;

تعريفنوع بنية Vk_بفر_Collection_Image_Create_Info_FUCHSIA {
    VkStructureType              sType;
    ثابت فراغ*                  p_بل;
    Vk_بفر_Collection_FUCHSIA    collection;
    uint32_t                     شاخص;
} Vk_بفر_Collection_Image_Create_Info_FUCHSIA;

تعريفنوع بنية Vk_بفر_Collection_Constraints_Info_FUCHSIA {
    VkStructureType    sType;
    ثابت فراغ*        p_بل;
    uint32_t           min_بفر_شمېر;
    uint32_t           max_بفر_شمېر;
    uint32_t           min_بفر_شمېر_For_Camping;
    uint32_t           min_بفر_شمېر_For_Dedicated_Slack;
    uint32_t           min_بفر_شمېر_For_Shared_Slack;
} Vk_بفر_Collection_Constraints_Info_FUCHSIA;

تعريفنوع بنية Vk_بفر_Constraints_Info_FUCHSIA {
    VkStructureType                             sType;
    ثابت فراغ*                                 p_بل;
    Vk_بفر_Create_Info                          createInfo;
    VkFormatFeatureFlags                        requiredFormatFeatures;
    Vk_بفر_Collection_Constraints_Info_FUCHSIA    بفر_Collection_Constraints;
} Vk_بفر_Constraints_Info_FUCHSIA;

تعريفنوع بنية Vk_بفر_Collection_بفر_Create_Info_FUCHSIA {
    VkStructureType              sType;
    ثابت فراغ*                  p_بل;
    Vk_بفر_Collection_FUCHSIA    collection;
    uint32_t                     شاخص;
} Vk_بفر_Collection_بفر_Create_Info_FUCHSIA;

تعريفنوع بنية VkSysmemColorSpaceFUCHSIA {
    VkStructureType    sType;
    ثابت فراغ*        p_بل;
    uint32_t           colorSpace;
} VkSysmemColorSpaceFUCHSIA;

تعريفنوع بنية Vk_بفر_Collection_Properties_FUCHSIA {
    VkStructureType                  sType;
    فراغ*                            p_بل;
    uint32_t                         حافظه_Type_بټونه;
    uint32_t                         بفر_شمېر;
    uint32_t                         create_Info_شاخص;
    uint64_t                         sysmemPixelFormat;
    VkFormatFeatureFlags             formatFeatures;
    VkSysmemColorSpaceFUCHSIA        sysmem_Color_Space_شاخص;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggested_XChroma_دننه_واټن;
    VkChromaLocation                 suggested_YChroma_دننه_واټن;
} Vk_بفر_Collection_Properties_FUCHSIA;

تعريفنوع بنية VkImageFormatConstraintsInfoFUCHSIA {
    VkStructureType                         sType;
    ثابت فراغ*                             p_بل;
    VkImageCreateInfo                       imageCreateInfo;
    VkFormatFeatureFlags                    requiredFormatFeatures;
    VkImageFormatConstraintsFlagsFUCHSIA    flags;
    uint64_t                                sysmemPixelFormat;
    uint32_t                                color_Space_شمېر;
    ثابت VkSysmemColorSpaceFUCHSIA*        pColorSpaces;
} VkImageFormatConstraintsInfoFUCHSIA;

تعريفنوع بنية VkImageConstraintsInfoFUCHSIA {
    VkStructureType                               sType;
    ثابت فراغ*                                   p_بل;
    uint32_t                                      format_Constraints_شمېر;
    ثابت VkImageFormatConstraintsInfoFUCHSIA*    pFormatConstraints;
    Vk_بفر_Collection_Constraints_Info_FUCHSIA      بفر_Collection_Constraints;
    VkImageConstraintsInfoFlagsFUCHSIA            flags;
} VkImageConstraintsInfoFUCHSIA;


تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vk_Create_بفر_Collection_FUCHSIA)(VkDevice device, ثابت Vk_بفر_Collection_Create_Info_FUCHSIA* pCreateInfo, ثابت Vk_ویش_Callbacks* pAllocator, Vk_بفر_Collection_FUCHSIA* pCollection);
تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vk_سېټ_بفر_Collection_Image_Constraints_FUCHSIA)(VkDevice device, Vk_بفر_Collection_FUCHSIA collection, ثابت VkImageConstraintsInfoFUCHSIA* pImageConstraintsInfo);
تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vk_سېټ_بفر_Collection_بفر_Constraints_FUCHSIA)(VkDevice device, Vk_بفر_Collection_FUCHSIA collection, ثابت Vk_بفر_Constraints_Info_FUCHSIA* p_بفر_Constraints_Info);
تعريفنوع فراغ (VKAPI_PTR *PFN_vk_Destroy_بفر_Collection_FUCHSIA)(VkDevice device, Vk_بفر_Collection_FUCHSIA collection, ثابت Vk_ویش_Callbacks* pAllocator);
تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vk_Get_بفر_Collection_Properties_FUCHSIA)(VkDevice device, Vk_بفر_Collection_FUCHSIA collection, Vk_بفر_Collection_Properties_FUCHSIA* pProperties);

#که_نه_تعریف_شوی VK_NO_PROTOTYPES

#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_پایله VKAPI_CALL vk_Create_بفر_Collection_FUCHSIA(
    VkDevice                                    device,
    ثابت Vk_بفر_Collection_Create_Info_FUCHSIA*  pCreateInfo,
    ثابت Vk_ویش_Callbacks*                pAllocator,
    Vk_بفر_Collection_FUCHSIA*                  pCollection);
#د_که_پای
#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_پایله VKAPI_CALL vk_سېټ_بفر_Collection_Image_Constraints_FUCHSIA(
    VkDevice                                    device,
    Vk_بفر_Collection_FUCHSIA                   collection,
    ثابت VkImageConstraintsInfoFUCHSIA*        pImageConstraintsInfo);
#د_که_پای
#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_پایله VKAPI_CALL vk_سېټ_بفر_Collection_بفر_Constraints_FUCHSIA(
    VkDevice                                    device,
    Vk_بفر_Collection_FUCHSIA                   collection,
    ثابت Vk_بفر_Constraints_Info_FUCHSIA*       p_بفر_Constraints_Info);
#د_که_پای
#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR فراغ VKAPI_CALL vk_Destroy_بفر_Collection_FUCHSIA(
    VkDevice                                    device,
    Vk_بفر_Collection_FUCHSIA                   collection,
    ثابت Vk_ویش_Callbacks*                pAllocator);
#د_که_پای
#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_پایله VKAPI_CALL vk_Get_بفر_Collection_Properties_FUCHSIA(
    VkDevice                                    device,
    Vk_بفر_Collection_FUCHSIA                   collection,
    Vk_بفر_Collection_Properties_FUCHSIA*        pProperties);
#د_که_پای
#د_که_پای

#که_تعریف_شوی __cplusplus
}
#د_که_پای

#د_که_پای
