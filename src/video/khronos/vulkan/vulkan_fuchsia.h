#ifndef VULKAN_FUCHSIA_H_
#define VULKAN_FUCHSIA_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#ifdef __cplusplus
বাহ্যিক "C" {
#endif



// VK_FUCHSIA_imagepipe_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_FUCHSIA_imagepipe_surface 1

#define VK_FUCHSIA_IMAGEPIPE_SURFACE_SPEC_VERSION 1
#define VK_FUCHSIA_IMAGEPIPE_SURFACE_EXTENSION_NAME "VK_FUCHSIA_imagepipe_surface"

প্রকারলেখ VkFlags VkImagePipeSurfaceCreateFlagsFUCHSIA;

প্রকারলেখ কাঠামো VkImagePipeSurfaceCreateInfoFUCHSIA {
    VkStructureType                         sType;
    ধ্রুবক শূন্য*                             p_পরবর্তী;
    VkImagePipeSurfaceCreateFlagsFUCHSIA    flags;
    zx_handle_t                             imagePipeHandle;
} VkImagePipeSurfaceCreateInfoFUCHSIA;


প্রকারলেখ Vk_ফলাফল (VKAPI_PTR *PFN_vkCreateImagePipeSurfaceFUCHSIA)(VkInstance instance, ধ্রুবক VkImagePipeSurfaceCreateInfoFUCHSIA* pCreateInfo, ধ্রুবক VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ফলাফল VKAPI_CALL vkCreateImagePipeSurfaceFUCHSIA(
    VkInstance                                  instance,
    ধ্রুবক VkImagePipeSurfaceCreateInfoFUCHSIA*  pCreateInfo,
    ধ্রুবক VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#endif


// VK_FUCHSIA_external_memory is a preprocessor guard. Do not pass it to API calls.
#define VK_FUCHSIA_external_memory 1

#define VK_FUCHSIA_EXTERNAL_MEMORY_SPEC_VERSION 1
#define VK_FUCHSIA_EXTERNAL_MEMORY_EXTENSION_NAME "VK_FUCHSIA_external_memory"

প্রকারলেখ কাঠামো VkImportMemoryZirconHandleInfoFUCHSIA {
    VkStructureType                       sType;
    ধ্রুবক শূন্য*                           p_পরবর্তী;
    VkExternalMemoryHandleTypeFlagBits    handleType;
    zx_handle_t                           handle;
} VkImportMemoryZirconHandleInfoFUCHSIA;

প্রকারলেখ কাঠামো VkMemoryZirconHandlePropertiesFUCHSIA {
    VkStructureType    sType;
    শূন্য*              p_পরবর্তী;
    uint32_t           memoryTypeBits;
} VkMemoryZirconHandlePropertiesFUCHSIA;

প্রকারলেখ কাঠামো VkMemoryGetZirconHandleInfoFUCHSIA {
    VkStructureType                       sType;
    ধ্রুবক শূন্য*                           p_পরবর্তী;
    VkDeviceMemory                        memory;
    VkExternalMemoryHandleTypeFlagBits    handleType;
} VkMemoryGetZirconHandleInfoFUCHSIA;


প্রকারলেখ Vk_ফলাফল (VKAPI_PTR *PFN_vkGetMemoryZirconHandleFUCHSIA)(VkDevice device, ধ্রুবক VkMemoryGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle);
প্রকারলেখ Vk_ফলাফল (VKAPI_PTR *PFN_vkGetMemoryZirconHandlePropertiesFUCHSIA)(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, zx_handle_t zirconHandle, VkMemoryZirconHandlePropertiesFUCHSIA* pMemoryZirconHandleProperties);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ফলাফল VKAPI_CALL vkGetMemoryZirconHandleFUCHSIA(
    VkDevice                                    device,
    ধ্রুবক VkMemoryGetZirconHandleInfoFUCHSIA*   pGetZirconHandleInfo,
    zx_handle_t*                                pZirconHandle);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ফলাফল VKAPI_CALL vkGetMemoryZirconHandlePropertiesFUCHSIA(
    VkDevice                                    device,
    VkExternalMemoryHandleTypeFlagBits          handleType,
    zx_handle_t                                 zirconHandle,
    VkMemoryZirconHandlePropertiesFUCHSIA*      pMemoryZirconHandleProperties);
#endif
#endif


// VK_FUCHSIA_external_semaphore is a preprocessor guard. Do not pass it to API calls.
#define VK_FUCHSIA_external_semaphore 1

#define VK_FUCHSIA_EXTERNAL_SEMAPHORE_SPEC_VERSION 1
#define VK_FUCHSIA_EXTERNAL_SEMAPHORE_EXTENSION_NAME "VK_FUCHSIA_external_semaphore"

প্রকারলেখ কাঠামো VkImportSemaphoreZirconHandleInfoFUCHSIA {
    VkStructureType                          sType;
    ধ্রুবক শূন্য*                              p_পরবর্তী;
    VkSemaphore                              semaphore;
    VkSemaphoreImportFlags                   flags;
    VkExternalSemaphoreHandleTypeFlagBits    handleType;
    zx_handle_t                              zirconHandle;
} VkImportSemaphoreZirconHandleInfoFUCHSIA;

প্রকারলেখ কাঠামো VkSemaphoreGetZirconHandleInfoFUCHSIA {
    VkStructureType                          sType;
    ধ্রুবক শূন্য*                              p_পরবর্তী;
    VkSemaphore                              semaphore;
    VkExternalSemaphoreHandleTypeFlagBits    handleType;
} VkSemaphoreGetZirconHandleInfoFUCHSIA;


প্রকারলেখ Vk_ফলাফল (VKAPI_PTR *PFN_vkImportSemaphoreZirconHandleFUCHSIA)(VkDevice device, ধ্রুবক VkImportSemaphoreZirconHandleInfoFUCHSIA* pImportSemaphoreZirconHandleInfo);
প্রকারলেখ Vk_ফলাফল (VKAPI_PTR *PFN_vkGetSemaphoreZirconHandleFUCHSIA)(VkDevice device, ধ্রুবক VkSemaphoreGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ফলাফল VKAPI_CALL vkImportSemaphoreZirconHandleFUCHSIA(
    VkDevice                                    device,
    ধ্রুবক VkImportSemaphoreZirconHandleInfoFUCHSIA* pImportSemaphoreZirconHandleInfo);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ফলাফল VKAPI_CALL vkGetSemaphoreZirconHandleFUCHSIA(
    VkDevice                                    device,
    ধ্রুবক VkSemaphoreGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo,
    zx_handle_t*                                pZirconHandle);
#endif
#endif


// VK_FUCHSIA_buffer_collection is a preprocessor guard. Do not pass it to API calls.
#define VK_FUCHSIA_বাফার_collection 1

VK_DEFINE_NON_DISPATCHABLE_HANDLE(Vk_বাফার_Collection_FUCHSIA)

#define VK_FUCHSIA_বাফার_COLLECTION_SPEC_VERSION 2
#define VK_FUCHSIA_বাফার_COLLECTION_EXTENSION_NAME "VK_FUCHSIA_buffer_collection"

প্রকারলেখ VkFlags VkImageFormatConstraintsFlagsFUCHSIA;

প্রকারলেখ গণনা VkImageConstraintsInfoFlagBitsFUCHSIA {
    VK_IMAGE_CONSTRAINTS_INFO_CPU_READ_RARELY_FUCHSIA = 0x00000001,
    VK_IMAGE_CONSTRAINTS_INFO_CPU_READ_OFTEN_FUCHSIA = 0x00000002,
    VK_IMAGE_CONSTRAINTS_INFO_CPU_WRITE_RARELY_FUCHSIA = 0x00000004,
    VK_IMAGE_CONSTRAINTS_INFO_CPU_WRITE_OFTEN_FUCHSIA = 0x00000008,
    VK_IMAGE_CONSTRAINTS_INFO_PROTECTED_OPTIONAL_FUCHSIA = 0x00000010,
    VK_IMAGE_CONSTRAINTS_INFO_FLAG_BITS_MAX_ENUM_FUCHSIA = 0x7FFFFFFF
} VkImageConstraintsInfoFlagBitsFUCHSIA;
প্রকারলেখ VkFlags VkImageConstraintsInfoFlagsFUCHSIA;

প্রকারলেখ কাঠামো Vk_বাফার_Collection_Create_Info_FUCHSIA {
    VkStructureType    sType;
    ধ্রুবক শূন্য*        p_পরবর্তী;
    zx_handle_t        collectionToken;
} Vk_বাফার_Collection_Create_Info_FUCHSIA;

প্রকারলেখ কাঠামো Vk_Import_Memory_বাফার_Collection_FUCHSIA {
    VkStructureType              sType;
    ধ্রুবক শূন্য*                  p_পরবর্তী;
    Vk_বাফার_Collection_FUCHSIA    collection;
    uint32_t                     সূচক;
} Vk_Import_Memory_বাফার_Collection_FUCHSIA;

প্রকারলেখ কাঠামো Vk_বাফার_Collection_Image_Create_Info_FUCHSIA {
    VkStructureType              sType;
    ধ্রুবক শূন্য*                  p_পরবর্তী;
    Vk_বাফার_Collection_FUCHSIA    collection;
    uint32_t                     সূচক;
} Vk_বাফার_Collection_Image_Create_Info_FUCHSIA;

প্রকারলেখ কাঠামো Vk_বাফার_Collection_Constraints_Info_FUCHSIA {
    VkStructureType    sType;
    ধ্রুবক শূন্য*        p_পরবর্তী;
    uint32_t           min_বাফার_গুনতি;
    uint32_t           max_বাফার_গুনতি;
    uint32_t           min_বাফার_গুনতি_For_Camping;
    uint32_t           min_বাফার_গুনতি_For_Dedicated_Slack;
    uint32_t           min_বাফার_গুনতি_For_Shared_Slack;
} Vk_বাফার_Collection_Constraints_Info_FUCHSIA;

প্রকারলেখ কাঠামো Vk_বাফার_Constraints_Info_FUCHSIA {
    VkStructureType                             sType;
    ধ্রুবক শূন্য*                                 p_পরবর্তী;
    Vk_বাফার_Create_Info                          createInfo;
    VkFormatFeatureFlags                        requiredFormatFeatures;
    Vk_বাফার_Collection_Constraints_Info_FUCHSIA    বাফার_Collection_Constraints;
} Vk_বাফার_Constraints_Info_FUCHSIA;

প্রকারলেখ কাঠামো Vk_বাফার_Collection_বাফার_Create_Info_FUCHSIA {
    VkStructureType              sType;
    ধ্রুবক শূন্য*                  p_পরবর্তী;
    Vk_বাফার_Collection_FUCHSIA    collection;
    uint32_t                     সূচক;
} Vk_বাফার_Collection_বাফার_Create_Info_FUCHSIA;

প্রকারলেখ কাঠামো VkSysmemColorSpaceFUCHSIA {
    VkStructureType    sType;
    ধ্রুবক শূন্য*        p_পরবর্তী;
    uint32_t           colorSpace;
} VkSysmemColorSpaceFUCHSIA;

প্রকারলেখ কাঠামো Vk_বাফার_Collection_Properties_FUCHSIA {
    VkStructureType                  sType;
    শূন্য*                            p_পরবর্তী;
    uint32_t                         memoryTypeBits;
    uint32_t                         বাফার_গুনতি;
    uint32_t                         create_Info_সূচক;
    uint64_t                         sysmemPixelFormat;
    VkFormatFeatureFlags             formatFeatures;
    VkSysmemColorSpaceFUCHSIA        sysmem_Color_Space_সূচক;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggestedXChromaOffset;
    VkChromaLocation                 suggestedYChromaOffset;
} Vk_বাফার_Collection_Properties_FUCHSIA;

প্রকারলেখ কাঠামো VkImageFormatConstraintsInfoFUCHSIA {
    VkStructureType                         sType;
    ধ্রুবক শূন্য*                             p_পরবর্তী;
    VkImageCreateInfo                       imageCreateInfo;
    VkFormatFeatureFlags                    requiredFormatFeatures;
    VkImageFormatConstraintsFlagsFUCHSIA    flags;
    uint64_t                                sysmemPixelFormat;
    uint32_t                                color_Space_গুনতি;
    ধ্রুবক VkSysmemColorSpaceFUCHSIA*        pColorSpaces;
} VkImageFormatConstraintsInfoFUCHSIA;

প্রকারলেখ কাঠামো VkImageConstraintsInfoFUCHSIA {
    VkStructureType                               sType;
    ধ্রুবক শূন্য*                                   p_পরবর্তী;
    uint32_t                                      format_Constraints_গুনতি;
    ধ্রুবক VkImageFormatConstraintsInfoFUCHSIA*    pFormatConstraints;
    Vk_বাফার_Collection_Constraints_Info_FUCHSIA      বাফার_Collection_Constraints;
    VkImageConstraintsInfoFlagsFUCHSIA            flags;
} VkImageConstraintsInfoFUCHSIA;


প্রকারলেখ Vk_ফলাফল (VKAPI_PTR *PFN_vk_Create_বাফার_Collection_FUCHSIA)(VkDevice device, ধ্রুবক Vk_বাফার_Collection_Create_Info_FUCHSIA* pCreateInfo, ধ্রুবক VkAllocationCallbacks* pAllocator, Vk_বাফার_Collection_FUCHSIA* pCollection);
প্রকারলেখ Vk_ফলাফল (VKAPI_PTR *PFN_vk_Set_বাফার_Collection_Image_Constraints_FUCHSIA)(VkDevice device, Vk_বাফার_Collection_FUCHSIA collection, ধ্রুবক VkImageConstraintsInfoFUCHSIA* pImageConstraintsInfo);
প্রকারলেখ Vk_ফলাফল (VKAPI_PTR *PFN_vk_Set_বাফার_Collection_বাফার_Constraints_FUCHSIA)(VkDevice device, Vk_বাফার_Collection_FUCHSIA collection, ধ্রুবক Vk_বাফার_Constraints_Info_FUCHSIA* p_বাফার_Constraints_Info);
প্রকারলেখ শূন্য (VKAPI_PTR *PFN_vk_Destroy_বাফার_Collection_FUCHSIA)(VkDevice device, Vk_বাফার_Collection_FUCHSIA collection, ধ্রুবক VkAllocationCallbacks* pAllocator);
প্রকারলেখ Vk_ফলাফল (VKAPI_PTR *PFN_vk_Get_বাফার_Collection_Properties_FUCHSIA)(VkDevice device, Vk_বাফার_Collection_FUCHSIA collection, Vk_বাফার_Collection_Properties_FUCHSIA* pProperties);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ফলাফল VKAPI_CALL vk_Create_বাফার_Collection_FUCHSIA(
    VkDevice                                    device,
    ধ্রুবক Vk_বাফার_Collection_Create_Info_FUCHSIA*  pCreateInfo,
    ধ্রুবক VkAllocationCallbacks*                pAllocator,
    Vk_বাফার_Collection_FUCHSIA*                  pCollection);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ফলাফল VKAPI_CALL vk_Set_বাফার_Collection_Image_Constraints_FUCHSIA(
    VkDevice                                    device,
    Vk_বাফার_Collection_FUCHSIA                   collection,
    ধ্রুবক VkImageConstraintsInfoFUCHSIA*        pImageConstraintsInfo);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ফলাফল VKAPI_CALL vk_Set_বাফার_Collection_বাফার_Constraints_FUCHSIA(
    VkDevice                                    device,
    Vk_বাফার_Collection_FUCHSIA                   collection,
    ধ্রুবক Vk_বাফার_Constraints_Info_FUCHSIA*       p_বাফার_Constraints_Info);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR শূন্য VKAPI_CALL vk_Destroy_বাফার_Collection_FUCHSIA(
    VkDevice                                    device,
    Vk_বাফার_Collection_FUCHSIA                   collection,
    ধ্রুবক VkAllocationCallbacks*                pAllocator);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ফলাফল VKAPI_CALL vk_Get_বাফার_Collection_Properties_FUCHSIA(
    VkDevice                                    device,
    Vk_বাফার_Collection_FUCHSIA                   collection,
    Vk_বাফার_Collection_Properties_FUCHSIA*        pProperties);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif
