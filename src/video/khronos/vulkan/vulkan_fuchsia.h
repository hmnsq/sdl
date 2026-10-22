#اگر_غیر_تعریف_شدہ VULKAN_FUCHSIA_H_
#تعریف_کرو VULKAN_FUCHSIA_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#اگر_تعریف_شدہ __cplusplus
خارجی "C" {
#اگر_ختم



// VK_FUCHSIA_imagepipe_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_FUCHSIA_imagepipe_surface 1

#تعریف_کرو VK_FUCHSIA_IMAGEPIPE_SURFACE_SPEC_نسخہ 1
#تعریف_کرو VK_FUCHSIA_IMAGEPIPE_SURFACE_EXTENSION_NAME "VK_FUCHSIA_imagepipe_surface"

قسمتعریف VkFlags VkImagePipeSurfaceCreateFlagsFUCHSIA;

قسمتعریف ساخت VkImagePipeSurfaceCreateInfoFUCHSIA {
    VkStructureType                         sType;
    ثابت خالی*                             p_اگلا;
    VkImagePipeSurfaceCreateFlagsFUCHSIA    flags;
    zx_handle_t                             imagePipeHandle;
} VkImagePipeSurfaceCreateInfoFUCHSIA;


قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vkCreateImagePipeSurfaceFUCHSIA)(VkInstance instance, ثابت VkImagePipeSurfaceCreateInfoFUCHSIA* pCreateInfo, ثابت Vk_تخصیص_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#اگر_غیر_تعریف_شدہ VK_NO_PROTOTYPES

#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vkCreateImagePipeSurfaceFUCHSIA(
    VkInstance                                  instance,
    ثابت VkImagePipeSurfaceCreateInfoFUCHSIA*  pCreateInfo,
    ثابت Vk_تخصیص_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#اگر_ختم
#اگر_ختم


// VK_FUCHSIA_external_memory is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_FUCHSIA_external_حافظہ 1

#تعریف_کرو VK_FUCHSIA_EXTERNAL_حافظہ_SPEC_نسخہ 1
#تعریف_کرو VK_FUCHSIA_EXTERNAL_حافظہ_EXTENSION_NAME "VK_FUCHSIA_external_memory"

قسمتعریف ساخت Vk_Import_حافظہ_Zircon_Handle_Info_FUCHSIA {
    VkStructureType                       sType;
    ثابت خالی*                           p_اگلا;
    Vk_External_حافظہ_Handle_Type_Flag_بٹ    handleType;
    zx_handle_t                           handle;
} Vk_Import_حافظہ_Zircon_Handle_Info_FUCHSIA;

قسمتعریف ساخت Vk_حافظہ_Zircon_Handle_Properties_FUCHSIA {
    VkStructureType    sType;
    خالی*              p_اگلا;
    uint32_t           حافظہ_Type_بٹ;
} Vk_حافظہ_Zircon_Handle_Properties_FUCHSIA;

قسمتعریف ساخت Vk_حافظہ_Get_Zircon_Handle_Info_FUCHSIA {
    VkStructureType                       sType;
    ثابت خالی*                           p_اگلا;
    Vk_Device_حافظہ                        حافظہ;
    Vk_External_حافظہ_Handle_Type_Flag_بٹ    handleType;
} Vk_حافظہ_Get_Zircon_Handle_Info_FUCHSIA;


قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vk_Get_حافظہ_Zircon_Handle_FUCHSIA)(VkDevice device, ثابت Vk_حافظہ_Get_Zircon_Handle_Info_FUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle);
قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vk_Get_حافظہ_Zircon_Handle_Properties_FUCHSIA)(VkDevice device, Vk_External_حافظہ_Handle_Type_Flag_بٹ handleType, zx_handle_t zirconHandle, Vk_حافظہ_Zircon_Handle_Properties_FUCHSIA* p_حافظہ_Zircon_Handle_Properties);

#اگر_غیر_تعریف_شدہ VK_NO_PROTOTYPES

#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_Get_حافظہ_Zircon_Handle_FUCHSIA(
    VkDevice                                    device,
    ثابت Vk_حافظہ_Get_Zircon_Handle_Info_FUCHSIA*   pGetZirconHandleInfo,
    zx_handle_t*                                pZirconHandle);
#اگر_ختم
#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_Get_حافظہ_Zircon_Handle_Properties_FUCHSIA(
    VkDevice                                    device,
    Vk_External_حافظہ_Handle_Type_Flag_بٹ          handleType,
    zx_handle_t                                 zirconHandle,
    Vk_حافظہ_Zircon_Handle_Properties_FUCHSIA*      p_حافظہ_Zircon_Handle_Properties);
#اگر_ختم
#اگر_ختم


// VK_FUCHSIA_external_semaphore is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_FUCHSIA_external_semaphore 1

#تعریف_کرو VK_FUCHSIA_EXTERNAL_SEMAPHORE_SPEC_نسخہ 1
#تعریف_کرو VK_FUCHSIA_EXTERNAL_SEMAPHORE_EXTENSION_NAME "VK_FUCHSIA_external_semaphore"

قسمتعریف ساخت VkImportSemaphoreZirconHandleInfoFUCHSIA {
    VkStructureType                          sType;
    ثابت خالی*                              p_اگلا;
    VkSemaphore                              semaphore;
    VkSemaphoreImportFlags                   flags;
    Vk_External_Semaphore_Handle_Type_Flag_بٹ    handleType;
    zx_handle_t                              zirconHandle;
} VkImportSemaphoreZirconHandleInfoFUCHSIA;

قسمتعریف ساخت VkSemaphoreGetZirconHandleInfoFUCHSIA {
    VkStructureType                          sType;
    ثابت خالی*                              p_اگلا;
    VkSemaphore                              semaphore;
    Vk_External_Semaphore_Handle_Type_Flag_بٹ    handleType;
} VkSemaphoreGetZirconHandleInfoFUCHSIA;


قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vkImportSemaphoreZirconHandleFUCHSIA)(VkDevice device, ثابت VkImportSemaphoreZirconHandleInfoFUCHSIA* pImportSemaphoreZirconHandleInfo);
قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vkGetSemaphoreZirconHandleFUCHSIA)(VkDevice device, ثابت VkSemaphoreGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle);

#اگر_غیر_تعریف_شدہ VK_NO_PROTOTYPES

#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vkImportSemaphoreZirconHandleFUCHSIA(
    VkDevice                                    device,
    ثابت VkImportSemaphoreZirconHandleInfoFUCHSIA* pImportSemaphoreZirconHandleInfo);
#اگر_ختم
#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vkGetSemaphoreZirconHandleFUCHSIA(
    VkDevice                                    device,
    ثابت VkSemaphoreGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo,
    zx_handle_t*                                pZirconHandle);
#اگر_ختم
#اگر_ختم


// VK_FUCHSIA_buffer_collection is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_FUCHSIA_بفر_collection 1

VK_DEFINE_NON_DISPATCHABLE_HANDLE(Vk_بفر_Collection_FUCHSIA)

#تعریف_کرو VK_FUCHSIA_بفر_COLLECTION_SPEC_نسخہ 2
#تعریف_کرو VK_FUCHSIA_بفر_COLLECTION_EXTENSION_NAME "VK_FUCHSIA_buffer_collection"

قسمتعریف VkFlags VkImageFormatConstraintsFlagsFUCHSIA;

قسمتعریف شمار Vk_Image_Constraints_Info_Flag_بٹ_FUCHSIA {
    VK_IMAGE_CONSTRAINTS_INFO_CPU_READ_RARELY_FUCHSIA = 0x00000001,
    VK_IMAGE_CONSTRAINTS_INFO_CPU_READ_OFTEN_FUCHSIA = 0x00000002,
    VK_IMAGE_CONSTRAINTS_INFO_CPU_WRITE_RARELY_FUCHSIA = 0x00000004,
    VK_IMAGE_CONSTRAINTS_INFO_CPU_WRITE_OFTEN_FUCHSIA = 0x00000008,
    VK_IMAGE_CONSTRAINTS_INFO_PROTECTED_OPTIONAL_FUCHSIA = 0x00000010,
    VK_IMAGE_CONSTRAINTS_INFO_FLAG_بٹ_MAX_ENUM_FUCHSIA = 0x7FFFFFFF
} Vk_Image_Constraints_Info_Flag_بٹ_FUCHSIA;
قسمتعریف VkFlags VkImageConstraintsInfoFlagsFUCHSIA;

قسمتعریف ساخت Vk_بفر_Collection_Create_Info_FUCHSIA {
    VkStructureType    sType;
    ثابت خالی*        p_اگلا;
    zx_handle_t        collectionToken;
} Vk_بفر_Collection_Create_Info_FUCHSIA;

قسمتعریف ساخت Vk_Import_حافظہ_بفر_Collection_FUCHSIA {
    VkStructureType              sType;
    ثابت خالی*                  p_اگلا;
    Vk_بفر_Collection_FUCHSIA    collection;
    uint32_t                     اشاریہ;
} Vk_Import_حافظہ_بفر_Collection_FUCHSIA;

قسمتعریف ساخت Vk_بفر_Collection_Image_Create_Info_FUCHSIA {
    VkStructureType              sType;
    ثابت خالی*                  p_اگلا;
    Vk_بفر_Collection_FUCHSIA    collection;
    uint32_t                     اشاریہ;
} Vk_بفر_Collection_Image_Create_Info_FUCHSIA;

قسمتعریف ساخت Vk_بفر_Collection_Constraints_Info_FUCHSIA {
    VkStructureType    sType;
    ثابت خالی*        p_اگلا;
    uint32_t           min_بفر_گنتی;
    uint32_t           max_بفر_گنتی;
    uint32_t           min_بفر_گنتی_For_Camping;
    uint32_t           min_بفر_گنتی_For_Dedicated_Slack;
    uint32_t           min_بفر_گنتی_For_Shared_Slack;
} Vk_بفر_Collection_Constraints_Info_FUCHSIA;

قسمتعریف ساخت Vk_بفر_Constraints_Info_FUCHSIA {
    VkStructureType                             sType;
    ثابت خالی*                                 p_اگلا;
    Vk_بفر_Create_Info                          createInfo;
    VkFormatFeatureFlags                        requiredFormatFeatures;
    Vk_بفر_Collection_Constraints_Info_FUCHSIA    بفر_Collection_Constraints;
} Vk_بفر_Constraints_Info_FUCHSIA;

قسمتعریف ساخت Vk_بفر_Collection_بفر_Create_Info_FUCHSIA {
    VkStructureType              sType;
    ثابت خالی*                  p_اگلا;
    Vk_بفر_Collection_FUCHSIA    collection;
    uint32_t                     اشاریہ;
} Vk_بفر_Collection_بفر_Create_Info_FUCHSIA;

قسمتعریف ساخت VkSysmemColorSpaceFUCHSIA {
    VkStructureType    sType;
    ثابت خالی*        p_اگلا;
    uint32_t           colorSpace;
} VkSysmemColorSpaceFUCHSIA;

قسمتعریف ساخت Vk_بفر_Collection_Properties_FUCHSIA {
    VkStructureType                  sType;
    خالی*                            p_اگلا;
    uint32_t                         حافظہ_Type_بٹ;
    uint32_t                         بفر_گنتی;
    uint32_t                         create_Info_اشاریہ;
    uint64_t                         sysmemPixelFormat;
    VkFormatFeatureFlags             formatFeatures;
    VkSysmemColorSpaceFUCHSIA        sysmem_Color_Space_اشاریہ;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggested_XChroma_انحراف;
    VkChromaLocation                 suggested_YChroma_انحراف;
} Vk_بفر_Collection_Properties_FUCHSIA;

قسمتعریف ساخت VkImageFormatConstraintsInfoFUCHSIA {
    VkStructureType                         sType;
    ثابت خالی*                             p_اگلا;
    VkImageCreateInfo                       imageCreateInfo;
    VkFormatFeatureFlags                    requiredFormatFeatures;
    VkImageFormatConstraintsFlagsFUCHSIA    flags;
    uint64_t                                sysmemPixelFormat;
    uint32_t                                color_Space_گنتی;
    ثابت VkSysmemColorSpaceFUCHSIA*        pColorSpaces;
} VkImageFormatConstraintsInfoFUCHSIA;

قسمتعریف ساخت VkImageConstraintsInfoFUCHSIA {
    VkStructureType                               sType;
    ثابت خالی*                                   p_اگلا;
    uint32_t                                      format_Constraints_گنتی;
    ثابت VkImageFormatConstraintsInfoFUCHSIA*    pFormatConstraints;
    Vk_بفر_Collection_Constraints_Info_FUCHSIA      بفر_Collection_Constraints;
    VkImageConstraintsInfoFlagsFUCHSIA            flags;
} VkImageConstraintsInfoFUCHSIA;


قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vk_Create_بفر_Collection_FUCHSIA)(VkDevice device, ثابت Vk_بفر_Collection_Create_Info_FUCHSIA* pCreateInfo, ثابت Vk_تخصیص_Callbacks* pAllocator, Vk_بفر_Collection_FUCHSIA* pCollection);
قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vk_سیٹ_بفر_Collection_Image_Constraints_FUCHSIA)(VkDevice device, Vk_بفر_Collection_FUCHSIA collection, ثابت VkImageConstraintsInfoFUCHSIA* pImageConstraintsInfo);
قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vk_سیٹ_بفر_Collection_بفر_Constraints_FUCHSIA)(VkDevice device, Vk_بفر_Collection_FUCHSIA collection, ثابت Vk_بفر_Constraints_Info_FUCHSIA* p_بفر_Constraints_Info);
قسمتعریف خالی (VKAPI_PTR *PFN_vk_Destroy_بفر_Collection_FUCHSIA)(VkDevice device, Vk_بفر_Collection_FUCHSIA collection, ثابت Vk_تخصیص_Callbacks* pAllocator);
قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vk_Get_بفر_Collection_Properties_FUCHSIA)(VkDevice device, Vk_بفر_Collection_FUCHSIA collection, Vk_بفر_Collection_Properties_FUCHSIA* pProperties);

#اگر_غیر_تعریف_شدہ VK_NO_PROTOTYPES

#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_Create_بفر_Collection_FUCHSIA(
    VkDevice                                    device,
    ثابت Vk_بفر_Collection_Create_Info_FUCHSIA*  pCreateInfo,
    ثابت Vk_تخصیص_Callbacks*                pAllocator,
    Vk_بفر_Collection_FUCHSIA*                  pCollection);
#اگر_ختم
#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_سیٹ_بفر_Collection_Image_Constraints_FUCHSIA(
    VkDevice                                    device,
    Vk_بفر_Collection_FUCHSIA                   collection,
    ثابت VkImageConstraintsInfoFUCHSIA*        pImageConstraintsInfo);
#اگر_ختم
#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_سیٹ_بفر_Collection_بفر_Constraints_FUCHSIA(
    VkDevice                                    device,
    Vk_بفر_Collection_FUCHSIA                   collection,
    ثابت Vk_بفر_Constraints_Info_FUCHSIA*       p_بفر_Constraints_Info);
#اگر_ختم
#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR خالی VKAPI_CALL vk_Destroy_بفر_Collection_FUCHSIA(
    VkDevice                                    device,
    Vk_بفر_Collection_FUCHSIA                   collection,
    ثابت Vk_تخصیص_Callbacks*                pAllocator);
#اگر_ختم
#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_Get_بفر_Collection_Properties_FUCHSIA(
    VkDevice                                    device,
    Vk_بفر_Collection_FUCHSIA                   collection,
    Vk_بفر_Collection_Properties_FUCHSIA*        pProperties);
#اگر_ختم
#اگر_ختم

#اگر_تعریف_شدہ __cplusplus
}
#اگر_ختم

#اگر_ختم
