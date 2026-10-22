#جے_بنا_تعریف VULKAN_FUCHSIA_H_
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


#جے_تعریف_شدہ __cplusplus
خارجي "C" {
#جے_انت



// VK_FUCHSIA_imagepipe_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_FUCHSIA_imagepipe_surface 1

#تعریف_کرو VK_FUCHSIA_IMAGEPIPE_SURFACE_SPEC_نسخہ 1
#تعریف_کرو VK_FUCHSIA_IMAGEPIPE_SURFACE_EXTENSION_NAME "VK_FUCHSIA_imagepipe_surface"

تعريفنوع VkFlags VkImagePipeSurfaceCreateFlagsFUCHSIA;

تعريفنوع بنية VkImagePipeSurfaceCreateInfoFUCHSIA {
    VkStructureType                         sType;
    ثابت فراغ*                             p_اگلا;
    VkImagePipeSurfaceCreateFlagsFUCHSIA    flags;
    zx_handle_t                             imagePipeHandle;
} VkImagePipeSurfaceCreateInfoFUCHSIA;


تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vkCreateImagePipeSurfaceFUCHSIA)(VkInstance instance, ثابت VkImagePipeSurfaceCreateInfoFUCHSIA* pCreateInfo, ثابت Vk_ونڈ_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#جے_بنا_تعریف VK_NO_PROTOTYPES

#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vkCreateImagePipeSurfaceFUCHSIA(
    VkInstance                                  instance,
    ثابت VkImagePipeSurfaceCreateInfoFUCHSIA*  pCreateInfo,
    ثابت Vk_ونڈ_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#جے_انت
#جے_انت


// VK_FUCHSIA_external_memory is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_FUCHSIA_external_حافظہ 1

#تعریف_کرو VK_FUCHSIA_EXTERNAL_حافظہ_SPEC_نسخہ 1
#تعریف_کرو VK_FUCHSIA_EXTERNAL_حافظہ_EXTENSION_NAME "VK_FUCHSIA_external_memory"

تعريفنوع بنية Vk_Import_حافظہ_Zircon_Handle_Info_FUCHSIA {
    VkStructureType                       sType;
    ثابت فراغ*                           p_اگلا;
    Vk_External_حافظہ_Handle_Type_Flag_بٹ    handleType;
    zx_handle_t                           handle;
} Vk_Import_حافظہ_Zircon_Handle_Info_FUCHSIA;

تعريفنوع بنية Vk_حافظہ_Zircon_Handle_Properties_FUCHSIA {
    VkStructureType    sType;
    فراغ*              p_اگلا;
    uint32_t           حافظہ_Type_بٹ;
} Vk_حافظہ_Zircon_Handle_Properties_FUCHSIA;

تعريفنوع بنية Vk_حافظہ_Get_Zircon_Handle_Info_FUCHSIA {
    VkStructureType                       sType;
    ثابت فراغ*                           p_اگلا;
    Vk_Device_حافظہ                        حافظہ;
    Vk_External_حافظہ_Handle_Type_Flag_بٹ    handleType;
} Vk_حافظہ_Get_Zircon_Handle_Info_FUCHSIA;


تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vk_Get_حافظہ_Zircon_Handle_FUCHSIA)(VkDevice device, ثابت Vk_حافظہ_Get_Zircon_Handle_Info_FUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle);
تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vk_Get_حافظہ_Zircon_Handle_Properties_FUCHSIA)(VkDevice device, Vk_External_حافظہ_Handle_Type_Flag_بٹ handleType, zx_handle_t zirconHandle, Vk_حافظہ_Zircon_Handle_Properties_FUCHSIA* p_حافظہ_Zircon_Handle_Properties);

#جے_بنا_تعریف VK_NO_PROTOTYPES

#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_Get_حافظہ_Zircon_Handle_FUCHSIA(
    VkDevice                                    device,
    ثابت Vk_حافظہ_Get_Zircon_Handle_Info_FUCHSIA*   pGetZirconHandleInfo,
    zx_handle_t*                                pZirconHandle);
#جے_انت
#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_Get_حافظہ_Zircon_Handle_Properties_FUCHSIA(
    VkDevice                                    device,
    Vk_External_حافظہ_Handle_Type_Flag_بٹ          handleType,
    zx_handle_t                                 zirconHandle,
    Vk_حافظہ_Zircon_Handle_Properties_FUCHSIA*      p_حافظہ_Zircon_Handle_Properties);
#جے_انت
#جے_انت


// VK_FUCHSIA_external_semaphore is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_FUCHSIA_external_semaphore 1

#تعریف_کرو VK_FUCHSIA_EXTERNAL_SEMAPHORE_SPEC_نسخہ 1
#تعریف_کرو VK_FUCHSIA_EXTERNAL_SEMAPHORE_EXTENSION_NAME "VK_FUCHSIA_external_semaphore"

تعريفنوع بنية VkImportSemaphoreZirconHandleInfoFUCHSIA {
    VkStructureType                          sType;
    ثابت فراغ*                              p_اگلا;
    VkSemaphore                              semaphore;
    VkSemaphoreImportFlags                   flags;
    Vk_External_Semaphore_Handle_Type_Flag_بٹ    handleType;
    zx_handle_t                              zirconHandle;
} VkImportSemaphoreZirconHandleInfoFUCHSIA;

تعريفنوع بنية VkSemaphoreGetZirconHandleInfoFUCHSIA {
    VkStructureType                          sType;
    ثابت فراغ*                              p_اگلا;
    VkSemaphore                              semaphore;
    Vk_External_Semaphore_Handle_Type_Flag_بٹ    handleType;
} VkSemaphoreGetZirconHandleInfoFUCHSIA;


تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vkImportSemaphoreZirconHandleFUCHSIA)(VkDevice device, ثابت VkImportSemaphoreZirconHandleInfoFUCHSIA* pImportSemaphoreZirconHandleInfo);
تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vkGetSemaphoreZirconHandleFUCHSIA)(VkDevice device, ثابت VkSemaphoreGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle);

#جے_بنا_تعریف VK_NO_PROTOTYPES

#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vkImportSemaphoreZirconHandleFUCHSIA(
    VkDevice                                    device,
    ثابت VkImportSemaphoreZirconHandleInfoFUCHSIA* pImportSemaphoreZirconHandleInfo);
#جے_انت
#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vkGetSemaphoreZirconHandleFUCHSIA(
    VkDevice                                    device,
    ثابت VkSemaphoreGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo,
    zx_handle_t*                                pZirconHandle);
#جے_انت
#جے_انت


// VK_FUCHSIA_buffer_collection is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_FUCHSIA_بفر_collection 1

VK_DEFINE_NON_DISPATCHABLE_HANDLE(Vk_بفر_Collection_FUCHSIA)

#تعریف_کرو VK_FUCHSIA_بفر_COLLECTION_SPEC_نسخہ 2
#تعریف_کرو VK_FUCHSIA_بفر_COLLECTION_EXTENSION_NAME "VK_FUCHSIA_buffer_collection"

تعريفنوع VkFlags VkImageFormatConstraintsFlagsFUCHSIA;

تعريفنوع تعداد Vk_Image_Constraints_Info_Flag_بٹ_FUCHSIA {
    VK_IMAGE_CONSTRAINTS_INFO_CPU_READ_RARELY_FUCHSIA = 0x00000001,
    VK_IMAGE_CONSTRAINTS_INFO_CPU_READ_OFTEN_FUCHSIA = 0x00000002,
    VK_IMAGE_CONSTRAINTS_INFO_CPU_WRITE_RARELY_FUCHSIA = 0x00000004,
    VK_IMAGE_CONSTRAINTS_INFO_CPU_WRITE_OFTEN_FUCHSIA = 0x00000008,
    VK_IMAGE_CONSTRAINTS_INFO_PROTECTED_OPTIONAL_FUCHSIA = 0x00000010,
    VK_IMAGE_CONSTRAINTS_INFO_FLAG_بٹ_MAX_ENUM_FUCHSIA = 0x7FFFFFFF
} Vk_Image_Constraints_Info_Flag_بٹ_FUCHSIA;
تعريفنوع VkFlags VkImageConstraintsInfoFlagsFUCHSIA;

تعريفنوع بنية Vk_بفر_Collection_Create_Info_FUCHSIA {
    VkStructureType    sType;
    ثابت فراغ*        p_اگلا;
    zx_handle_t        collectionToken;
} Vk_بفر_Collection_Create_Info_FUCHSIA;

تعريفنوع بنية Vk_Import_حافظہ_بفر_Collection_FUCHSIA {
    VkStructureType              sType;
    ثابت فراغ*                  p_اگلا;
    Vk_بفر_Collection_FUCHSIA    collection;
    uint32_t                     اشاریہ;
} Vk_Import_حافظہ_بفر_Collection_FUCHSIA;

تعريفنوع بنية Vk_بفر_Collection_Image_Create_Info_FUCHSIA {
    VkStructureType              sType;
    ثابت فراغ*                  p_اگلا;
    Vk_بفر_Collection_FUCHSIA    collection;
    uint32_t                     اشاریہ;
} Vk_بفر_Collection_Image_Create_Info_FUCHSIA;

تعريفنوع بنية Vk_بفر_Collection_Constraints_Info_FUCHSIA {
    VkStructureType    sType;
    ثابت فراغ*        p_اگلا;
    uint32_t           min_بفر_گنتی;
    uint32_t           max_بفر_گنتی;
    uint32_t           min_بفر_گنتی_For_Camping;
    uint32_t           min_بفر_گنتی_For_Dedicated_Slack;
    uint32_t           min_بفر_گنتی_For_Shared_Slack;
} Vk_بفر_Collection_Constraints_Info_FUCHSIA;

تعريفنوع بنية Vk_بفر_Constraints_Info_FUCHSIA {
    VkStructureType                             sType;
    ثابت فراغ*                                 p_اگلا;
    Vk_بفر_Create_Info                          createInfo;
    VkFormatFeatureFlags                        requiredFormatFeatures;
    Vk_بفر_Collection_Constraints_Info_FUCHSIA    بفر_Collection_Constraints;
} Vk_بفر_Constraints_Info_FUCHSIA;

تعريفنوع بنية Vk_بفر_Collection_بفر_Create_Info_FUCHSIA {
    VkStructureType              sType;
    ثابت فراغ*                  p_اگلا;
    Vk_بفر_Collection_FUCHSIA    collection;
    uint32_t                     اشاریہ;
} Vk_بفر_Collection_بفر_Create_Info_FUCHSIA;

تعريفنوع بنية VkSysmemColorSpaceFUCHSIA {
    VkStructureType    sType;
    ثابت فراغ*        p_اگلا;
    uint32_t           colorSpace;
} VkSysmemColorSpaceFUCHSIA;

تعريفنوع بنية Vk_بفر_Collection_Properties_FUCHSIA {
    VkStructureType                  sType;
    فراغ*                            p_اگلا;
    uint32_t                         حافظہ_Type_بٹ;
    uint32_t                         بفر_گنتی;
    uint32_t                         create_Info_اشاریہ;
    uint64_t                         sysmemPixelFormat;
    VkFormatFeatureFlags             formatFeatures;
    VkSysmemColorSpaceFUCHSIA        sysmem_Color_Space_اشاریہ;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggested_XChroma_وتھ;
    VkChromaLocation                 suggested_YChroma_وتھ;
} Vk_بفر_Collection_Properties_FUCHSIA;

تعريفنوع بنية VkImageFormatConstraintsInfoFUCHSIA {
    VkStructureType                         sType;
    ثابت فراغ*                             p_اگلا;
    VkImageCreateInfo                       imageCreateInfo;
    VkFormatFeatureFlags                    requiredFormatFeatures;
    VkImageFormatConstraintsFlagsFUCHSIA    flags;
    uint64_t                                sysmemPixelFormat;
    uint32_t                                color_Space_گنتی;
    ثابت VkSysmemColorSpaceFUCHSIA*        pColorSpaces;
} VkImageFormatConstraintsInfoFUCHSIA;

تعريفنوع بنية VkImageConstraintsInfoFUCHSIA {
    VkStructureType                               sType;
    ثابت فراغ*                                   p_اگلا;
    uint32_t                                      format_Constraints_گنتی;
    ثابت VkImageFormatConstraintsInfoFUCHSIA*    pFormatConstraints;
    Vk_بفر_Collection_Constraints_Info_FUCHSIA      بفر_Collection_Constraints;
    VkImageConstraintsInfoFlagsFUCHSIA            flags;
} VkImageConstraintsInfoFUCHSIA;


تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vk_Create_بفر_Collection_FUCHSIA)(VkDevice device, ثابت Vk_بفر_Collection_Create_Info_FUCHSIA* pCreateInfo, ثابت Vk_ونڈ_Callbacks* pAllocator, Vk_بفر_Collection_FUCHSIA* pCollection);
تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vk_سیٹ_بفر_Collection_Image_Constraints_FUCHSIA)(VkDevice device, Vk_بفر_Collection_FUCHSIA collection, ثابت VkImageConstraintsInfoFUCHSIA* pImageConstraintsInfo);
تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vk_سیٹ_بفر_Collection_بفر_Constraints_FUCHSIA)(VkDevice device, Vk_بفر_Collection_FUCHSIA collection, ثابت Vk_بفر_Constraints_Info_FUCHSIA* p_بفر_Constraints_Info);
تعريفنوع فراغ (VKAPI_PTR *PFN_vk_Destroy_بفر_Collection_FUCHSIA)(VkDevice device, Vk_بفر_Collection_FUCHSIA collection, ثابت Vk_ونڈ_Callbacks* pAllocator);
تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vk_Get_بفر_Collection_Properties_FUCHSIA)(VkDevice device, Vk_بفر_Collection_FUCHSIA collection, Vk_بفر_Collection_Properties_FUCHSIA* pProperties);

#جے_بنا_تعریف VK_NO_PROTOTYPES

#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_Create_بفر_Collection_FUCHSIA(
    VkDevice                                    device,
    ثابت Vk_بفر_Collection_Create_Info_FUCHSIA*  pCreateInfo,
    ثابت Vk_ونڈ_Callbacks*                pAllocator,
    Vk_بفر_Collection_FUCHSIA*                  pCollection);
#جے_انت
#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_سیٹ_بفر_Collection_Image_Constraints_FUCHSIA(
    VkDevice                                    device,
    Vk_بفر_Collection_FUCHSIA                   collection,
    ثابت VkImageConstraintsInfoFUCHSIA*        pImageConstraintsInfo);
#جے_انت
#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_سیٹ_بفر_Collection_بفر_Constraints_FUCHSIA(
    VkDevice                                    device,
    Vk_بفر_Collection_FUCHSIA                   collection,
    ثابت Vk_بفر_Constraints_Info_FUCHSIA*       p_بفر_Constraints_Info);
#جے_انت
#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR فراغ VKAPI_CALL vk_Destroy_بفر_Collection_FUCHSIA(
    VkDevice                                    device,
    Vk_بفر_Collection_FUCHSIA                   collection,
    ثابت Vk_ونڈ_Callbacks*                pAllocator);
#جے_انت
#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_Get_بفر_Collection_Properties_FUCHSIA(
    VkDevice                                    device,
    Vk_بفر_Collection_FUCHSIA                   collection,
    Vk_بفر_Collection_Properties_FUCHSIA*        pProperties);
#جے_انت
#جے_انت

#جے_تعریف_شدہ __cplusplus
}
#جے_انت

#جے_انت
