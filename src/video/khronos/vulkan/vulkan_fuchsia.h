#اگر_تعریف_نشده VULKAN_FUCHSIA_H_
#تعریف_کن VULKAN_FUCHSIA_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#اگر_تعریف_شده __cplusplus
خارجي "C" {
#پایان_اگر



// VK_FUCHSIA_imagepipe_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کن VK_FUCHSIA_imagepipe_surface 1

#تعریف_کن VK_FUCHSIA_IMAGEPIPE_SURFACE_SPEC_نسخه 1
#تعریف_کن VK_FUCHSIA_IMAGEPIPE_SURFACE_EXTENSION_NAME "VK_FUCHSIA_imagepipe_surface"

تعريفنوع VkFlags VkImagePipeSurfaceCreateFlagsFUCHSIA;

تعريفنوع بنية VkImagePipeSurfaceCreateInfoFUCHSIA {
    VkStructureType                         sType;
    ثابت فراغ*                             p_بعدی;
    VkImagePipeSurfaceCreateFlagsFUCHSIA    flags;
    zx_handle_t                             imagePipeHandle;
} VkImagePipeSurfaceCreateInfoFUCHSIA;


تعريفنوع Vk_نتیجه (VKAPI_PTR *PFN_vkCreateImagePipeSurfaceFUCHSIA)(VkInstance instance, ثابت VkImagePipeSurfaceCreateInfoFUCHSIA* pCreateInfo, ثابت Vk_تخصیص_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#اگر_تعریف_نشده VK_NO_PROTOTYPES

#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجه VKAPI_CALL vkCreateImagePipeSurfaceFUCHSIA(
    VkInstance                                  instance,
    ثابت VkImagePipeSurfaceCreateInfoFUCHSIA*  pCreateInfo,
    ثابت Vk_تخصیص_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#پایان_اگر
#پایان_اگر


// VK_FUCHSIA_external_memory is a preprocessor guard. Do not pass it to API calls.
#تعریف_کن VK_FUCHSIA_external_حافظه 1

#تعریف_کن VK_FUCHSIA_EXTERNAL_حافظه_SPEC_نسخه 1
#تعریف_کن VK_FUCHSIA_EXTERNAL_حافظه_EXTENSION_NAME "VK_FUCHSIA_external_memory"

تعريفنوع بنية Vk_Import_حافظه_Zircon_Handle_Info_FUCHSIA {
    VkStructureType                       sType;
    ثابت فراغ*                           p_بعدی;
    Vk_External_حافظه_Handle_Type_Flag_بیتها    handleType;
    zx_handle_t                           handle;
} Vk_Import_حافظه_Zircon_Handle_Info_FUCHSIA;

تعريفنوع بنية Vk_حافظه_Zircon_Handle_Properties_FUCHSIA {
    VkStructureType    sType;
    فراغ*              p_بعدی;
    uint32_t           حافظه_Type_بیتها;
} Vk_حافظه_Zircon_Handle_Properties_FUCHSIA;

تعريفنوع بنية Vk_حافظه_Get_Zircon_Handle_Info_FUCHSIA {
    VkStructureType                       sType;
    ثابت فراغ*                           p_بعدی;
    Vk_Device_حافظه                        حافظه;
    Vk_External_حافظه_Handle_Type_Flag_بیتها    handleType;
} Vk_حافظه_Get_Zircon_Handle_Info_FUCHSIA;


تعريفنوع Vk_نتیجه (VKAPI_PTR *PFN_vk_Get_حافظه_Zircon_Handle_FUCHSIA)(VkDevice device, ثابت Vk_حافظه_Get_Zircon_Handle_Info_FUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle);
تعريفنوع Vk_نتیجه (VKAPI_PTR *PFN_vk_Get_حافظه_Zircon_Handle_Properties_FUCHSIA)(VkDevice device, Vk_External_حافظه_Handle_Type_Flag_بیتها handleType, zx_handle_t zirconHandle, Vk_حافظه_Zircon_Handle_Properties_FUCHSIA* p_حافظه_Zircon_Handle_Properties);

#اگر_تعریف_نشده VK_NO_PROTOTYPES

#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجه VKAPI_CALL vk_Get_حافظه_Zircon_Handle_FUCHSIA(
    VkDevice                                    device,
    ثابت Vk_حافظه_Get_Zircon_Handle_Info_FUCHSIA*   pGetZirconHandleInfo,
    zx_handle_t*                                pZirconHandle);
#پایان_اگر
#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجه VKAPI_CALL vk_Get_حافظه_Zircon_Handle_Properties_FUCHSIA(
    VkDevice                                    device,
    Vk_External_حافظه_Handle_Type_Flag_بیتها          handleType,
    zx_handle_t                                 zirconHandle,
    Vk_حافظه_Zircon_Handle_Properties_FUCHSIA*      p_حافظه_Zircon_Handle_Properties);
#پایان_اگر
#پایان_اگر


// VK_FUCHSIA_external_semaphore is a preprocessor guard. Do not pass it to API calls.
#تعریف_کن VK_FUCHSIA_external_semaphore 1

#تعریف_کن VK_FUCHSIA_EXTERNAL_SEMAPHORE_SPEC_نسخه 1
#تعریف_کن VK_FUCHSIA_EXTERNAL_SEMAPHORE_EXTENSION_NAME "VK_FUCHSIA_external_semaphore"

تعريفنوع بنية VkImportSemaphoreZirconHandleInfoFUCHSIA {
    VkStructureType                          sType;
    ثابت فراغ*                              p_بعدی;
    VkSemaphore                              semaphore;
    VkSemaphoreImportFlags                   flags;
    Vk_External_Semaphore_Handle_Type_Flag_بیتها    handleType;
    zx_handle_t                              zirconHandle;
} VkImportSemaphoreZirconHandleInfoFUCHSIA;

تعريفنوع بنية VkSemaphoreGetZirconHandleInfoFUCHSIA {
    VkStructureType                          sType;
    ثابت فراغ*                              p_بعدی;
    VkSemaphore                              semaphore;
    Vk_External_Semaphore_Handle_Type_Flag_بیتها    handleType;
} VkSemaphoreGetZirconHandleInfoFUCHSIA;


تعريفنوع Vk_نتیجه (VKAPI_PTR *PFN_vkImportSemaphoreZirconHandleFUCHSIA)(VkDevice device, ثابت VkImportSemaphoreZirconHandleInfoFUCHSIA* pImportSemaphoreZirconHandleInfo);
تعريفنوع Vk_نتیجه (VKAPI_PTR *PFN_vkGetSemaphoreZirconHandleFUCHSIA)(VkDevice device, ثابت VkSemaphoreGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle);

#اگر_تعریف_نشده VK_NO_PROTOTYPES

#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجه VKAPI_CALL vkImportSemaphoreZirconHandleFUCHSIA(
    VkDevice                                    device,
    ثابت VkImportSemaphoreZirconHandleInfoFUCHSIA* pImportSemaphoreZirconHandleInfo);
#پایان_اگر
#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجه VKAPI_CALL vkGetSemaphoreZirconHandleFUCHSIA(
    VkDevice                                    device,
    ثابت VkSemaphoreGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo,
    zx_handle_t*                                pZirconHandle);
#پایان_اگر
#پایان_اگر


// VK_FUCHSIA_buffer_collection is a preprocessor guard. Do not pass it to API calls.
#تعریف_کن VK_FUCHSIA_میانگیر_collection 1

VK_DEFINE_NON_DISPATCHABLE_HANDLE(Vk_میانگیر_Collection_FUCHSIA)

#تعریف_کن VK_FUCHSIA_میانگیر_COLLECTION_SPEC_نسخه 2
#تعریف_کن VK_FUCHSIA_میانگیر_COLLECTION_EXTENSION_NAME "VK_FUCHSIA_buffer_collection"

تعريفنوع VkFlags VkImageFormatConstraintsFlagsFUCHSIA;

تعريفنوع تعداد Vk_Image_Constraints_Info_Flag_بیتها_FUCHSIA {
    VK_IMAGE_CONSTRAINTS_INFO_CPU_READ_RARELY_FUCHSIA = 0x00000001,
    VK_IMAGE_CONSTRAINTS_INFO_CPU_READ_OFTEN_FUCHSIA = 0x00000002,
    VK_IMAGE_CONSTRAINTS_INFO_CPU_WRITE_RARELY_FUCHSIA = 0x00000004,
    VK_IMAGE_CONSTRAINTS_INFO_CPU_WRITE_OFTEN_FUCHSIA = 0x00000008,
    VK_IMAGE_CONSTRAINTS_INFO_PROTECTED_OPTIONAL_FUCHSIA = 0x00000010,
    VK_IMAGE_CONSTRAINTS_INFO_FLAG_بیتها_MAX_ENUM_FUCHSIA = 0x7FFFFFFF
} Vk_Image_Constraints_Info_Flag_بیتها_FUCHSIA;
تعريفنوع VkFlags VkImageConstraintsInfoFlagsFUCHSIA;

تعريفنوع بنية Vk_میانگیر_Collection_Create_Info_FUCHSIA {
    VkStructureType    sType;
    ثابت فراغ*        p_بعدی;
    zx_handle_t        collectionToken;
} Vk_میانگیر_Collection_Create_Info_FUCHSIA;

تعريفنوع بنية Vk_Import_حافظه_میانگیر_Collection_FUCHSIA {
    VkStructureType              sType;
    ثابت فراغ*                  p_بعدی;
    Vk_میانگیر_Collection_FUCHSIA    collection;
    uint32_t                     شاخص;
} Vk_Import_حافظه_میانگیر_Collection_FUCHSIA;

تعريفنوع بنية Vk_میانگیر_Collection_Image_Create_Info_FUCHSIA {
    VkStructureType              sType;
    ثابت فراغ*                  p_بعدی;
    Vk_میانگیر_Collection_FUCHSIA    collection;
    uint32_t                     شاخص;
} Vk_میانگیر_Collection_Image_Create_Info_FUCHSIA;

تعريفنوع بنية Vk_میانگیر_Collection_Constraints_Info_FUCHSIA {
    VkStructureType    sType;
    ثابت فراغ*        p_بعدی;
    uint32_t           min_میانگیر_شمار;
    uint32_t           max_میانگیر_شمار;
    uint32_t           min_میانگیر_شمار_For_Camping;
    uint32_t           min_میانگیر_شمار_For_Dedicated_Slack;
    uint32_t           min_میانگیر_شمار_For_Shared_Slack;
} Vk_میانگیر_Collection_Constraints_Info_FUCHSIA;

تعريفنوع بنية Vk_میانگیر_Constraints_Info_FUCHSIA {
    VkStructureType                             sType;
    ثابت فراغ*                                 p_بعدی;
    Vk_میانگیر_Create_Info                          createInfo;
    VkFormatFeatureFlags                        requiredFormatFeatures;
    Vk_میانگیر_Collection_Constraints_Info_FUCHSIA    میانگیر_Collection_Constraints;
} Vk_میانگیر_Constraints_Info_FUCHSIA;

تعريفنوع بنية Vk_میانگیر_Collection_میانگیر_Create_Info_FUCHSIA {
    VkStructureType              sType;
    ثابت فراغ*                  p_بعدی;
    Vk_میانگیر_Collection_FUCHSIA    collection;
    uint32_t                     شاخص;
} Vk_میانگیر_Collection_میانگیر_Create_Info_FUCHSIA;

تعريفنوع بنية VkSysmemColorSpaceFUCHSIA {
    VkStructureType    sType;
    ثابت فراغ*        p_بعدی;
    uint32_t           colorSpace;
} VkSysmemColorSpaceFUCHSIA;

تعريفنوع بنية Vk_میانگیر_Collection_Properties_FUCHSIA {
    VkStructureType                  sType;
    فراغ*                            p_بعدی;
    uint32_t                         حافظه_Type_بیتها;
    uint32_t                         میانگیر_شمار;
    uint32_t                         create_Info_شاخص;
    uint64_t                         sysmemPixelFormat;
    VkFormatFeatureFlags             formatFeatures;
    VkSysmemColorSpaceFUCHSIA        sysmem_Color_Space_شاخص;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggested_XChroma_جابه_جایی;
    VkChromaLocation                 suggested_YChroma_جابه_جایی;
} Vk_میانگیر_Collection_Properties_FUCHSIA;

تعريفنوع بنية VkImageFormatConstraintsInfoFUCHSIA {
    VkStructureType                         sType;
    ثابت فراغ*                             p_بعدی;
    VkImageCreateInfo                       imageCreateInfo;
    VkFormatFeatureFlags                    requiredFormatFeatures;
    VkImageFormatConstraintsFlagsFUCHSIA    flags;
    uint64_t                                sysmemPixelFormat;
    uint32_t                                color_Space_شمار;
    ثابت VkSysmemColorSpaceFUCHSIA*        pColorSpaces;
} VkImageFormatConstraintsInfoFUCHSIA;

تعريفنوع بنية VkImageConstraintsInfoFUCHSIA {
    VkStructureType                               sType;
    ثابت فراغ*                                   p_بعدی;
    uint32_t                                      format_Constraints_شمار;
    ثابت VkImageFormatConstraintsInfoFUCHSIA*    pFormatConstraints;
    Vk_میانگیر_Collection_Constraints_Info_FUCHSIA      میانگیر_Collection_Constraints;
    VkImageConstraintsInfoFlagsFUCHSIA            flags;
} VkImageConstraintsInfoFUCHSIA;


تعريفنوع Vk_نتیجه (VKAPI_PTR *PFN_vk_Create_میانگیر_Collection_FUCHSIA)(VkDevice device, ثابت Vk_میانگیر_Collection_Create_Info_FUCHSIA* pCreateInfo, ثابت Vk_تخصیص_Callbacks* pAllocator, Vk_میانگیر_Collection_FUCHSIA* pCollection);
تعريفنوع Vk_نتیجه (VKAPI_PTR *PFN_vk_مجموعه_میانگیر_Collection_Image_Constraints_FUCHSIA)(VkDevice device, Vk_میانگیر_Collection_FUCHSIA collection, ثابت VkImageConstraintsInfoFUCHSIA* pImageConstraintsInfo);
تعريفنوع Vk_نتیجه (VKAPI_PTR *PFN_vk_مجموعه_میانگیر_Collection_میانگیر_Constraints_FUCHSIA)(VkDevice device, Vk_میانگیر_Collection_FUCHSIA collection, ثابت Vk_میانگیر_Constraints_Info_FUCHSIA* p_میانگیر_Constraints_Info);
تعريفنوع فراغ (VKAPI_PTR *PFN_vk_Destroy_میانگیر_Collection_FUCHSIA)(VkDevice device, Vk_میانگیر_Collection_FUCHSIA collection, ثابت Vk_تخصیص_Callbacks* pAllocator);
تعريفنوع Vk_نتیجه (VKAPI_PTR *PFN_vk_Get_میانگیر_Collection_Properties_FUCHSIA)(VkDevice device, Vk_میانگیر_Collection_FUCHSIA collection, Vk_میانگیر_Collection_Properties_FUCHSIA* pProperties);

#اگر_تعریف_نشده VK_NO_PROTOTYPES

#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجه VKAPI_CALL vk_Create_میانگیر_Collection_FUCHSIA(
    VkDevice                                    device,
    ثابت Vk_میانگیر_Collection_Create_Info_FUCHSIA*  pCreateInfo,
    ثابت Vk_تخصیص_Callbacks*                pAllocator,
    Vk_میانگیر_Collection_FUCHSIA*                  pCollection);
#پایان_اگر
#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجه VKAPI_CALL vk_مجموعه_میانگیر_Collection_Image_Constraints_FUCHSIA(
    VkDevice                                    device,
    Vk_میانگیر_Collection_FUCHSIA                   collection,
    ثابت VkImageConstraintsInfoFUCHSIA*        pImageConstraintsInfo);
#پایان_اگر
#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجه VKAPI_CALL vk_مجموعه_میانگیر_Collection_میانگیر_Constraints_FUCHSIA(
    VkDevice                                    device,
    Vk_میانگیر_Collection_FUCHSIA                   collection,
    ثابت Vk_میانگیر_Constraints_Info_FUCHSIA*       p_میانگیر_Constraints_Info);
#پایان_اگر
#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR فراغ VKAPI_CALL vk_Destroy_میانگیر_Collection_FUCHSIA(
    VkDevice                                    device,
    Vk_میانگیر_Collection_FUCHSIA                   collection,
    ثابت Vk_تخصیص_Callbacks*                pAllocator);
#پایان_اگر
#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجه VKAPI_CALL vk_Get_میانگیر_Collection_Properties_FUCHSIA(
    VkDevice                                    device,
    Vk_میانگیر_Collection_FUCHSIA                   collection,
    Vk_میانگیر_Collection_Properties_FUCHSIA*        pProperties);
#پایان_اگر
#پایان_اگر

#اگر_تعریف_شده __cplusplus
}
#پایان_اگر

#پایان_اگر
