#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VULKAN_FUCHSIA_H_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VULKAN_FUCHSIA_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ



// VK_FUCHSIA_imagepipe_surface is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_FUCHSIA_imagepipe_surface 1

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_FUCHSIA_IMAGEPIPE_SURFACE_SPEC_ਸੰਸਕਰਣ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_FUCHSIA_IMAGEPIPE_SURFACE_EXTENSION_NAME "VK_FUCHSIA_imagepipe_surface"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ VkFlags VkImagePipeSurfaceCreateFlagsFUCHSIA;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkImagePipeSurfaceCreateInfoFUCHSIA {
    VkStructureType                         sType;
    ਅਚਲ ਖਾਲੀ*                             p_ਅਗਲਾ;
    VkImagePipeSurfaceCreateFlagsFUCHSIA    flags;
    zx_handle_t                             imagePipeHandle;
} VkImagePipeSurfaceCreateInfoFUCHSIA;


ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vkCreateImagePipeSurfaceFUCHSIA)(VkInstance instance, ਅਚਲ VkImagePipeSurfaceCreateInfoFUCHSIA* pCreateInfo, ਅਚਲ Vk_ਵੰਡ_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_NO_PROTOTYPES

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ਨਤੀਜਾ VKAPI_CALL vkCreateImagePipeSurfaceFUCHSIA(
    VkInstance                                  instance,
    ਅਚਲ VkImagePipeSurfaceCreateInfoFUCHSIA*  pCreateInfo,
    ਅਚਲ Vk_ਵੰਡ_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ


// VK_FUCHSIA_external_memory is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_FUCHSIA_external_ਸਮ੍ਰਿਤੀ 1

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_FUCHSIA_EXTERNAL_ਸਮ੍ਰਿਤੀ_SPEC_ਸੰਸਕਰਣ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_FUCHSIA_EXTERNAL_ਸਮ੍ਰਿਤੀ_EXTENSION_NAME "VK_FUCHSIA_external_memory"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_Import_ਸਮ੍ਰਿਤੀ_Zircon_Handle_Info_FUCHSIA {
    VkStructureType                       sType;
    ਅਚਲ ਖਾਲੀ*                           p_ਅਗਲਾ;
    Vk_External_ਸਮ੍ਰਿਤੀ_Handle_Type_Flag_ਬਿੱਟ    handleType;
    zx_handle_t                           handle;
} Vk_Import_ਸਮ੍ਰਿਤੀ_Zircon_Handle_Info_FUCHSIA;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_ਸਮ੍ਰਿਤੀ_Zircon_Handle_Properties_FUCHSIA {
    VkStructureType    sType;
    ਖਾਲੀ*              p_ਅਗਲਾ;
    uint32_t           ਸਮ੍ਰਿਤੀ_Type_ਬਿੱਟ;
} Vk_ਸਮ੍ਰਿਤੀ_Zircon_Handle_Properties_FUCHSIA;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_ਸਮ੍ਰਿਤੀ_Get_Zircon_Handle_Info_FUCHSIA {
    VkStructureType                       sType;
    ਅਚਲ ਖਾਲੀ*                           p_ਅਗਲਾ;
    Vk_Device_ਸਮ੍ਰਿਤੀ                        ਸਮ੍ਰਿਤੀ;
    Vk_External_ਸਮ੍ਰਿਤੀ_Handle_Type_Flag_ਬਿੱਟ    handleType;
} Vk_ਸਮ੍ਰਿਤੀ_Get_Zircon_Handle_Info_FUCHSIA;


ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vk_Get_ਸਮ੍ਰਿਤੀ_Zircon_Handle_FUCHSIA)(VkDevice device, ਅਚਲ Vk_ਸਮ੍ਰਿਤੀ_Get_Zircon_Handle_Info_FUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vk_Get_ਸਮ੍ਰਿਤੀ_Zircon_Handle_Properties_FUCHSIA)(VkDevice device, Vk_External_ਸਮ੍ਰਿਤੀ_Handle_Type_Flag_ਬਿੱਟ handleType, zx_handle_t zirconHandle, Vk_ਸਮ੍ਰਿਤੀ_Zircon_Handle_Properties_FUCHSIA* p_ਸਮ੍ਰਿਤੀ_Zircon_Handle_Properties);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_NO_PROTOTYPES

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ਨਤੀਜਾ VKAPI_CALL vk_Get_ਸਮ੍ਰਿਤੀ_Zircon_Handle_FUCHSIA(
    VkDevice                                    device,
    ਅਚਲ Vk_ਸਮ੍ਰਿਤੀ_Get_Zircon_Handle_Info_FUCHSIA*   pGetZirconHandleInfo,
    zx_handle_t*                                pZirconHandle);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ਨਤੀਜਾ VKAPI_CALL vk_Get_ਸਮ੍ਰਿਤੀ_Zircon_Handle_Properties_FUCHSIA(
    VkDevice                                    device,
    Vk_External_ਸਮ੍ਰਿਤੀ_Handle_Type_Flag_ਬਿੱਟ          handleType,
    zx_handle_t                                 zirconHandle,
    Vk_ਸਮ੍ਰਿਤੀ_Zircon_Handle_Properties_FUCHSIA*      p_ਸਮ੍ਰਿਤੀ_Zircon_Handle_Properties);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ


// VK_FUCHSIA_external_semaphore is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_FUCHSIA_external_semaphore 1

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_FUCHSIA_EXTERNAL_SEMAPHORE_SPEC_ਸੰਸਕਰਣ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_FUCHSIA_EXTERNAL_SEMAPHORE_EXTENSION_NAME "VK_FUCHSIA_external_semaphore"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkImportSemaphoreZirconHandleInfoFUCHSIA {
    VkStructureType                          sType;
    ਅਚਲ ਖਾਲੀ*                              p_ਅਗਲਾ;
    VkSemaphore                              semaphore;
    VkSemaphoreImportFlags                   flags;
    Vk_External_Semaphore_Handle_Type_Flag_ਬਿੱਟ    handleType;
    zx_handle_t                              zirconHandle;
} VkImportSemaphoreZirconHandleInfoFUCHSIA;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkSemaphoreGetZirconHandleInfoFUCHSIA {
    VkStructureType                          sType;
    ਅਚਲ ਖਾਲੀ*                              p_ਅਗਲਾ;
    VkSemaphore                              semaphore;
    Vk_External_Semaphore_Handle_Type_Flag_ਬਿੱਟ    handleType;
} VkSemaphoreGetZirconHandleInfoFUCHSIA;


ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vkImportSemaphoreZirconHandleFUCHSIA)(VkDevice device, ਅਚਲ VkImportSemaphoreZirconHandleInfoFUCHSIA* pImportSemaphoreZirconHandleInfo);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vkGetSemaphoreZirconHandleFUCHSIA)(VkDevice device, ਅਚਲ VkSemaphoreGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_NO_PROTOTYPES

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ਨਤੀਜਾ VKAPI_CALL vkImportSemaphoreZirconHandleFUCHSIA(
    VkDevice                                    device,
    ਅਚਲ VkImportSemaphoreZirconHandleInfoFUCHSIA* pImportSemaphoreZirconHandleInfo);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ਨਤੀਜਾ VKAPI_CALL vkGetSemaphoreZirconHandleFUCHSIA(
    VkDevice                                    device,
    ਅਚਲ VkSemaphoreGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo,
    zx_handle_t*                                pZirconHandle);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ


// VK_FUCHSIA_buffer_collection is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_FUCHSIA_ਬਫਰ_collection 1

VK_DEFINE_NON_DISPATCHABLE_HANDLE(Vk_ਬਫਰ_Collection_FUCHSIA)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_FUCHSIA_ਬਫਰ_COLLECTION_SPEC_ਸੰਸਕਰਣ 2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_FUCHSIA_ਬਫਰ_COLLECTION_EXTENSION_NAME "VK_FUCHSIA_buffer_collection"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ VkFlags VkImageFormatConstraintsFlagsFUCHSIA;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ Vk_Image_Constraints_Info_Flag_ਬਿੱਟ_FUCHSIA {
    VK_IMAGE_CONSTRAINTS_INFO_CPU_READ_RARELY_FUCHSIA = 0x00000001,
    VK_IMAGE_CONSTRAINTS_INFO_CPU_READ_OFTEN_FUCHSIA = 0x00000002,
    VK_IMAGE_CONSTRAINTS_INFO_CPU_WRITE_RARELY_FUCHSIA = 0x00000004,
    VK_IMAGE_CONSTRAINTS_INFO_CPU_WRITE_OFTEN_FUCHSIA = 0x00000008,
    VK_IMAGE_CONSTRAINTS_INFO_PROTECTED_OPTIONAL_FUCHSIA = 0x00000010,
    VK_IMAGE_CONSTRAINTS_INFO_FLAG_ਬਿੱਟ_MAX_ENUM_FUCHSIA = 0x7FFFFFFF
} Vk_Image_Constraints_Info_Flag_ਬਿੱਟ_FUCHSIA;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ VkFlags VkImageConstraintsInfoFlagsFUCHSIA;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_ਬਫਰ_Collection_Create_Info_FUCHSIA {
    VkStructureType    sType;
    ਅਚਲ ਖਾਲੀ*        p_ਅਗਲਾ;
    zx_handle_t        collectionToken;
} Vk_ਬਫਰ_Collection_Create_Info_FUCHSIA;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_Import_ਸਮ੍ਰਿਤੀ_ਬਫਰ_Collection_FUCHSIA {
    VkStructureType              sType;
    ਅਚਲ ਖਾਲੀ*                  p_ਅਗਲਾ;
    Vk_ਬਫਰ_Collection_FUCHSIA    collection;
    uint32_t                     ਸੂਚਕਾਂਕ;
} Vk_Import_ਸਮ੍ਰਿਤੀ_ਬਫਰ_Collection_FUCHSIA;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_ਬਫਰ_Collection_Image_Create_Info_FUCHSIA {
    VkStructureType              sType;
    ਅਚਲ ਖਾਲੀ*                  p_ਅਗਲਾ;
    Vk_ਬਫਰ_Collection_FUCHSIA    collection;
    uint32_t                     ਸੂਚਕਾਂਕ;
} Vk_ਬਫਰ_Collection_Image_Create_Info_FUCHSIA;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_ਬਫਰ_Collection_Constraints_Info_FUCHSIA {
    VkStructureType    sType;
    ਅਚਲ ਖਾਲੀ*        p_ਅਗਲਾ;
    uint32_t           min_ਬਫਰ_ਗਿਣਤੀ;
    uint32_t           max_ਬਫਰ_ਗਿਣਤੀ;
    uint32_t           min_ਬਫਰ_ਗਿਣਤੀ_For_Camping;
    uint32_t           min_ਬਫਰ_ਗਿਣਤੀ_For_Dedicated_Slack;
    uint32_t           min_ਬਫਰ_ਗਿਣਤੀ_For_Shared_Slack;
} Vk_ਬਫਰ_Collection_Constraints_Info_FUCHSIA;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_ਬਫਰ_Constraints_Info_FUCHSIA {
    VkStructureType                             sType;
    ਅਚਲ ਖਾਲੀ*                                 p_ਅਗਲਾ;
    Vk_ਬਫਰ_Create_Info                          createInfo;
    VkFormatFeatureFlags                        requiredFormatFeatures;
    Vk_ਬਫਰ_Collection_Constraints_Info_FUCHSIA    ਬਫਰ_Collection_Constraints;
} Vk_ਬਫਰ_Constraints_Info_FUCHSIA;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_ਬਫਰ_Collection_ਬਫਰ_Create_Info_FUCHSIA {
    VkStructureType              sType;
    ਅਚਲ ਖਾਲੀ*                  p_ਅਗਲਾ;
    Vk_ਬਫਰ_Collection_FUCHSIA    collection;
    uint32_t                     ਸੂਚਕਾਂਕ;
} Vk_ਬਫਰ_Collection_ਬਫਰ_Create_Info_FUCHSIA;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkSysmemColorSpaceFUCHSIA {
    VkStructureType    sType;
    ਅਚਲ ਖਾਲੀ*        p_ਅਗਲਾ;
    uint32_t           colorSpace;
} VkSysmemColorSpaceFUCHSIA;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_ਬਫਰ_Collection_Properties_FUCHSIA {
    VkStructureType                  sType;
    ਖਾਲੀ*                            p_ਅਗਲਾ;
    uint32_t                         ਸਮ੍ਰਿਤੀ_Type_ਬਿੱਟ;
    uint32_t                         ਬਫਰ_ਗਿਣਤੀ;
    uint32_t                         create_Info_ਸੂਚਕਾਂਕ;
    uint64_t                         sysmemPixelFormat;
    VkFormatFeatureFlags             formatFeatures;
    VkSysmemColorSpaceFUCHSIA        sysmem_Color_Space_ਸੂਚਕਾਂਕ;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggested_XChroma_ਵਿੱਥ;
    VkChromaLocation                 suggested_YChroma_ਵਿੱਥ;
} Vk_ਬਫਰ_Collection_Properties_FUCHSIA;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkImageFormatConstraintsInfoFUCHSIA {
    VkStructureType                         sType;
    ਅਚਲ ਖਾਲੀ*                             p_ਅਗਲਾ;
    VkImageCreateInfo                       imageCreateInfo;
    VkFormatFeatureFlags                    requiredFormatFeatures;
    VkImageFormatConstraintsFlagsFUCHSIA    flags;
    uint64_t                                sysmemPixelFormat;
    uint32_t                                color_Space_ਗਿਣਤੀ;
    ਅਚਲ VkSysmemColorSpaceFUCHSIA*        pColorSpaces;
} VkImageFormatConstraintsInfoFUCHSIA;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkImageConstraintsInfoFUCHSIA {
    VkStructureType                               sType;
    ਅਚਲ ਖਾਲੀ*                                   p_ਅਗਲਾ;
    uint32_t                                      format_Constraints_ਗਿਣਤੀ;
    ਅਚਲ VkImageFormatConstraintsInfoFUCHSIA*    pFormatConstraints;
    Vk_ਬਫਰ_Collection_Constraints_Info_FUCHSIA      ਬਫਰ_Collection_Constraints;
    VkImageConstraintsInfoFlagsFUCHSIA            flags;
} VkImageConstraintsInfoFUCHSIA;


ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vk_Create_ਬਫਰ_Collection_FUCHSIA)(VkDevice device, ਅਚਲ Vk_ਬਫਰ_Collection_Create_Info_FUCHSIA* pCreateInfo, ਅਚਲ Vk_ਵੰਡ_Callbacks* pAllocator, Vk_ਬਫਰ_Collection_FUCHSIA* pCollection);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vk_ਸੈੱਟ_ਬਫਰ_Collection_Image_Constraints_FUCHSIA)(VkDevice device, Vk_ਬਫਰ_Collection_FUCHSIA collection, ਅਚਲ VkImageConstraintsInfoFUCHSIA* pImageConstraintsInfo);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vk_ਸੈੱਟ_ਬਫਰ_Collection_ਬਫਰ_Constraints_FUCHSIA)(VkDevice device, Vk_ਬਫਰ_Collection_FUCHSIA collection, ਅਚਲ Vk_ਬਫਰ_Constraints_Info_FUCHSIA* p_ਬਫਰ_Constraints_Info);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (VKAPI_PTR *PFN_vk_Destroy_ਬਫਰ_Collection_FUCHSIA)(VkDevice device, Vk_ਬਫਰ_Collection_FUCHSIA collection, ਅਚਲ Vk_ਵੰਡ_Callbacks* pAllocator);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vk_Get_ਬਫਰ_Collection_Properties_FUCHSIA)(VkDevice device, Vk_ਬਫਰ_Collection_FUCHSIA collection, Vk_ਬਫਰ_Collection_Properties_FUCHSIA* pProperties);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_NO_PROTOTYPES

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ਨਤੀਜਾ VKAPI_CALL vk_Create_ਬਫਰ_Collection_FUCHSIA(
    VkDevice                                    device,
    ਅਚਲ Vk_ਬਫਰ_Collection_Create_Info_FUCHSIA*  pCreateInfo,
    ਅਚਲ Vk_ਵੰਡ_Callbacks*                pAllocator,
    Vk_ਬਫਰ_Collection_FUCHSIA*                  pCollection);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ਨਤੀਜਾ VKAPI_CALL vk_ਸੈੱਟ_ਬਫਰ_Collection_Image_Constraints_FUCHSIA(
    VkDevice                                    device,
    Vk_ਬਫਰ_Collection_FUCHSIA                   collection,
    ਅਚਲ VkImageConstraintsInfoFUCHSIA*        pImageConstraintsInfo);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ਨਤੀਜਾ VKAPI_CALL vk_ਸੈੱਟ_ਬਫਰ_Collection_ਬਫਰ_Constraints_FUCHSIA(
    VkDevice                                    device,
    Vk_ਬਫਰ_Collection_FUCHSIA                   collection,
    ਅਚਲ Vk_ਬਫਰ_Constraints_Info_FUCHSIA*       p_ਬਫਰ_Constraints_Info);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR ਖਾਲੀ VKAPI_CALL vk_Destroy_ਬਫਰ_Collection_FUCHSIA(
    VkDevice                                    device,
    Vk_ਬਫਰ_Collection_FUCHSIA                   collection,
    ਅਚਲ Vk_ਵੰਡ_Callbacks*                pAllocator);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ਨਤੀਜਾ VKAPI_CALL vk_Get_ਬਫਰ_Collection_Properties_FUCHSIA(
    VkDevice                                    device,
    Vk_ਬਫਰ_Collection_FUCHSIA                   collection,
    Vk_ਬਫਰ_Collection_Properties_FUCHSIA*        pProperties);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ
