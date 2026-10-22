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
બાહ્ય "C" {
#endif



// VK_FUCHSIA_imagepipe_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_FUCHSIA_imagepipe_surface 1

#define VK_FUCHSIA_IMAGEPIPE_SURFACE_SPEC_VERSION 1
#define VK_FUCHSIA_IMAGEPIPE_SURFACE_EXTENSION_NAME "VK_FUCHSIA_imagepipe_surface"

પ્રકારવ્યાખ્યા VkFlags VkImagePipeSurfaceCreateFlagsFUCHSIA;

પ્રકારવ્યાખ્યા સંરચના VkImagePipeSurfaceCreateInfoFUCHSIA {
    VkStructureType                         sType;
    અચલ શૂન્ય*                             pNext;
    VkImagePipeSurfaceCreateFlagsFUCHSIA    flags;
    zx_handle_t                             imagePipeHandle;
} VkImagePipeSurfaceCreateInfoFUCHSIA;


પ્રકારવ્યાખ્યા VkResult (VKAPI_PTR *PFN_vkCreateImagePipeSurfaceFUCHSIA)(VkInstance instance, અચલ VkImagePipeSurfaceCreateInfoFUCHSIA* pCreateInfo, અચલ VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateImagePipeSurfaceFUCHSIA(
    VkInstance                                  instance,
    અચલ VkImagePipeSurfaceCreateInfoFUCHSIA*  pCreateInfo,
    અચલ VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#endif


// VK_FUCHSIA_external_memory is a preprocessor guard. Do not pass it to API calls.
#define VK_FUCHSIA_external_memory 1

#define VK_FUCHSIA_EXTERNAL_MEMORY_SPEC_VERSION 1
#define VK_FUCHSIA_EXTERNAL_MEMORY_EXTENSION_NAME "VK_FUCHSIA_external_memory"

પ્રકારવ્યાખ્યા સંરચના VkImportMemoryZirconHandleInfoFUCHSIA {
    VkStructureType                       sType;
    અચલ શૂન્ય*                           pNext;
    VkExternalMemoryHandleTypeFlagBits    handleType;
    zx_handle_t                           handle;
} VkImportMemoryZirconHandleInfoFUCHSIA;

પ્રકારવ્યાખ્યા સંરચના VkMemoryZirconHandlePropertiesFUCHSIA {
    VkStructureType    sType;
    શૂન્ય*              pNext;
    uint32_t           memoryTypeBits;
} VkMemoryZirconHandlePropertiesFUCHSIA;

પ્રકારવ્યાખ્યા સંરચના VkMemoryGetZirconHandleInfoFUCHSIA {
    VkStructureType                       sType;
    અચલ શૂન્ય*                           pNext;
    VkDeviceMemory                        memory;
    VkExternalMemoryHandleTypeFlagBits    handleType;
} VkMemoryGetZirconHandleInfoFUCHSIA;


પ્રકારવ્યાખ્યા VkResult (VKAPI_PTR *PFN_vkGetMemoryZirconHandleFUCHSIA)(VkDevice device, અચલ VkMemoryGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle);
પ્રકારવ્યાખ્યા VkResult (VKAPI_PTR *PFN_vkGetMemoryZirconHandlePropertiesFUCHSIA)(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, zx_handle_t zirconHandle, VkMemoryZirconHandlePropertiesFUCHSIA* pMemoryZirconHandleProperties);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryZirconHandleFUCHSIA(
    VkDevice                                    device,
    અચલ VkMemoryGetZirconHandleInfoFUCHSIA*   pGetZirconHandleInfo,
    zx_handle_t*                                pZirconHandle);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryZirconHandlePropertiesFUCHSIA(
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

પ્રકારવ્યાખ્યા સંરચના VkImportSemaphoreZirconHandleInfoFUCHSIA {
    VkStructureType                          sType;
    અચલ શૂન્ય*                              pNext;
    VkSemaphore                              semaphore;
    VkSemaphoreImportFlags                   flags;
    VkExternalSemaphoreHandleTypeFlagBits    handleType;
    zx_handle_t                              zirconHandle;
} VkImportSemaphoreZirconHandleInfoFUCHSIA;

પ્રકારવ્યાખ્યા સંરચના VkSemaphoreGetZirconHandleInfoFUCHSIA {
    VkStructureType                          sType;
    અચલ શૂન્ય*                              pNext;
    VkSemaphore                              semaphore;
    VkExternalSemaphoreHandleTypeFlagBits    handleType;
} VkSemaphoreGetZirconHandleInfoFUCHSIA;


પ્રકારવ્યાખ્યા VkResult (VKAPI_PTR *PFN_vkImportSemaphoreZirconHandleFUCHSIA)(VkDevice device, અચલ VkImportSemaphoreZirconHandleInfoFUCHSIA* pImportSemaphoreZirconHandleInfo);
પ્રકારવ્યાખ્યા VkResult (VKAPI_PTR *PFN_vkGetSemaphoreZirconHandleFUCHSIA)(VkDevice device, અચલ VkSemaphoreGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkImportSemaphoreZirconHandleFUCHSIA(
    VkDevice                                    device,
    અચલ VkImportSemaphoreZirconHandleInfoFUCHSIA* pImportSemaphoreZirconHandleInfo);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetSemaphoreZirconHandleFUCHSIA(
    VkDevice                                    device,
    અચલ VkSemaphoreGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo,
    zx_handle_t*                                pZirconHandle);
#endif
#endif


// VK_FUCHSIA_buffer_collection is a preprocessor guard. Do not pass it to API calls.
#define VK_FUCHSIA_buffer_collection 1

VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkBufferCollectionFUCHSIA)

#define VK_FUCHSIA_BUFFER_COLLECTION_SPEC_VERSION 2
#define VK_FUCHSIA_BUFFER_COLLECTION_EXTENSION_NAME "VK_FUCHSIA_buffer_collection"

પ્રકારવ્યાખ્યા VkFlags VkImageFormatConstraintsFlagsFUCHSIA;

પ્રકારવ્યાખ્યા ગણના VkImageConstraintsInfoFlagBitsFUCHSIA {
    VK_IMAGE_CONSTRAINTS_INFO_CPU_READ_RARELY_FUCHSIA = 0x00000001,
    VK_IMAGE_CONSTRAINTS_INFO_CPU_READ_OFTEN_FUCHSIA = 0x00000002,
    VK_IMAGE_CONSTRAINTS_INFO_CPU_WRITE_RARELY_FUCHSIA = 0x00000004,
    VK_IMAGE_CONSTRAINTS_INFO_CPU_WRITE_OFTEN_FUCHSIA = 0x00000008,
    VK_IMAGE_CONSTRAINTS_INFO_PROTECTED_OPTIONAL_FUCHSIA = 0x00000010,
    VK_IMAGE_CONSTRAINTS_INFO_FLAG_BITS_MAX_ENUM_FUCHSIA = 0x7FFFFFFF
} VkImageConstraintsInfoFlagBitsFUCHSIA;
પ્રકારવ્યાખ્યા VkFlags VkImageConstraintsInfoFlagsFUCHSIA;

પ્રકારવ્યાખ્યા સંરચના VkBufferCollectionCreateInfoFUCHSIA {
    VkStructureType    sType;
    અચલ શૂન્ય*        pNext;
    zx_handle_t        collectionToken;
} VkBufferCollectionCreateInfoFUCHSIA;

પ્રકારવ્યાખ્યા સંરચના VkImportMemoryBufferCollectionFUCHSIA {
    VkStructureType              sType;
    અચલ શૂન્ય*                  pNext;
    VkBufferCollectionFUCHSIA    collection;
    uint32_t                     index;
} VkImportMemoryBufferCollectionFUCHSIA;

પ્રકારવ્યાખ્યા સંરચના VkBufferCollectionImageCreateInfoFUCHSIA {
    VkStructureType              sType;
    અચલ શૂન્ય*                  pNext;
    VkBufferCollectionFUCHSIA    collection;
    uint32_t                     index;
} VkBufferCollectionImageCreateInfoFUCHSIA;

પ્રકારવ્યાખ્યા સંરચના VkBufferCollectionConstraintsInfoFUCHSIA {
    VkStructureType    sType;
    અચલ શૂન્ય*        pNext;
    uint32_t           min_Buffer_ગણતરી;
    uint32_t           max_Buffer_ગણતરી;
    uint32_t           min_Buffer_ગણતરી_For_Camping;
    uint32_t           min_Buffer_ગણતરી_For_Dedicated_Slack;
    uint32_t           min_Buffer_ગણતરી_For_Shared_Slack;
} VkBufferCollectionConstraintsInfoFUCHSIA;

પ્રકારવ્યાખ્યા સંરચના VkBufferConstraintsInfoFUCHSIA {
    VkStructureType                             sType;
    અચલ શૂન્ય*                                 pNext;
    VkBufferCreateInfo                          createInfo;
    VkFormatFeatureFlags                        requiredFormatFeatures;
    VkBufferCollectionConstraintsInfoFUCHSIA    bufferCollectionConstraints;
} VkBufferConstraintsInfoFUCHSIA;

પ્રકારવ્યાખ્યા સંરચના VkBufferCollectionBufferCreateInfoFUCHSIA {
    VkStructureType              sType;
    અચલ શૂન્ય*                  pNext;
    VkBufferCollectionFUCHSIA    collection;
    uint32_t                     index;
} VkBufferCollectionBufferCreateInfoFUCHSIA;

પ્રકારવ્યાખ્યા સંરચના VkSysmemColorSpaceFUCHSIA {
    VkStructureType    sType;
    અચલ શૂન્ય*        pNext;
    uint32_t           colorSpace;
} VkSysmemColorSpaceFUCHSIA;

પ્રકારવ્યાખ્યા સંરચના VkBufferCollectionPropertiesFUCHSIA {
    VkStructureType                  sType;
    શૂન્ય*                            pNext;
    uint32_t                         memoryTypeBits;
    uint32_t                         buffer_ગણતરી;
    uint32_t                         createInfoIndex;
    uint64_t                         sysmemPixelFormat;
    VkFormatFeatureFlags             formatFeatures;
    VkSysmemColorSpaceFUCHSIA        sysmemColorSpaceIndex;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggestedXChromaOffset;
    VkChromaLocation                 suggestedYChromaOffset;
} VkBufferCollectionPropertiesFUCHSIA;

પ્રકારવ્યાખ્યા સંરચના VkImageFormatConstraintsInfoFUCHSIA {
    VkStructureType                         sType;
    અચલ શૂન્ય*                             pNext;
    VkImageCreateInfo                       imageCreateInfo;
    VkFormatFeatureFlags                    requiredFormatFeatures;
    VkImageFormatConstraintsFlagsFUCHSIA    flags;
    uint64_t                                sysmemPixelFormat;
    uint32_t                                color_Space_ગણતરી;
    અચલ VkSysmemColorSpaceFUCHSIA*        pColorSpaces;
} VkImageFormatConstraintsInfoFUCHSIA;

પ્રકારવ્યાખ્યા સંરચના VkImageConstraintsInfoFUCHSIA {
    VkStructureType                               sType;
    અચલ શૂન્ય*                                   pNext;
    uint32_t                                      format_Constraints_ગણતરી;
    અચલ VkImageFormatConstraintsInfoFUCHSIA*    pFormatConstraints;
    VkBufferCollectionConstraintsInfoFUCHSIA      bufferCollectionConstraints;
    VkImageConstraintsInfoFlagsFUCHSIA            flags;
} VkImageConstraintsInfoFUCHSIA;


પ્રકારવ્યાખ્યા VkResult (VKAPI_PTR *PFN_vkCreateBufferCollectionFUCHSIA)(VkDevice device, અચલ VkBufferCollectionCreateInfoFUCHSIA* pCreateInfo, અચલ VkAllocationCallbacks* pAllocator, VkBufferCollectionFUCHSIA* pCollection);
પ્રકારવ્યાખ્યા VkResult (VKAPI_PTR *PFN_vkSetBufferCollectionImageConstraintsFUCHSIA)(VkDevice device, VkBufferCollectionFUCHSIA collection, અચલ VkImageConstraintsInfoFUCHSIA* pImageConstraintsInfo);
પ્રકારવ્યાખ્યા VkResult (VKAPI_PTR *PFN_vkSetBufferCollectionBufferConstraintsFUCHSIA)(VkDevice device, VkBufferCollectionFUCHSIA collection, અચલ VkBufferConstraintsInfoFUCHSIA* pBufferConstraintsInfo);
પ્રકારવ્યાખ્યા શૂન્ય (VKAPI_PTR *PFN_vkDestroyBufferCollectionFUCHSIA)(VkDevice device, VkBufferCollectionFUCHSIA collection, અચલ VkAllocationCallbacks* pAllocator);
પ્રકારવ્યાખ્યા VkResult (VKAPI_PTR *PFN_vkGetBufferCollectionPropertiesFUCHSIA)(VkDevice device, VkBufferCollectionFUCHSIA collection, VkBufferCollectionPropertiesFUCHSIA* pProperties);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateBufferCollectionFUCHSIA(
    VkDevice                                    device,
    અચલ VkBufferCollectionCreateInfoFUCHSIA*  pCreateInfo,
    અચલ VkAllocationCallbacks*                pAllocator,
    VkBufferCollectionFUCHSIA*                  pCollection);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkSetBufferCollectionImageConstraintsFUCHSIA(
    VkDevice                                    device,
    VkBufferCollectionFUCHSIA                   collection,
    અચલ VkImageConstraintsInfoFUCHSIA*        pImageConstraintsInfo);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkSetBufferCollectionBufferConstraintsFUCHSIA(
    VkDevice                                    device,
    VkBufferCollectionFUCHSIA                   collection,
    અચલ VkBufferConstraintsInfoFUCHSIA*       pBufferConstraintsInfo);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR શૂન્ય VKAPI_CALL vkDestroyBufferCollectionFUCHSIA(
    VkDevice                                    device,
    VkBufferCollectionFUCHSIA                   collection,
    અચલ VkAllocationCallbacks*                pAllocator);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetBufferCollectionPropertiesFUCHSIA(
    VkDevice                                    device,
    VkBufferCollectionFUCHSIA                   collection,
    VkBufferCollectionPropertiesFUCHSIA*        pProperties);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif
