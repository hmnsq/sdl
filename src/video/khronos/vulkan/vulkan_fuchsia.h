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
ಬಾಹ್ಯ "C" {
#endif



// VK_FUCHSIA_imagepipe_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_FUCHSIA_imagepipe_surface 1

#define VK_FUCHSIA_IMAGEPIPE_SURFACE_SPEC_VERSION 1
#define VK_FUCHSIA_IMAGEPIPE_SURFACE_EXTENSION_NAME "VK_FUCHSIA_imagepipe_surface"

ಪ್ರಕಾರನಿರ್ದೇಶ VkFlags VkImagePipeSurfaceCreateFlagsFUCHSIA;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkImagePipeSurfaceCreateInfoFUCHSIA {
    VkStructureType                         sType;
    ಧ್ರುವ ಶೂನ್ಯ*                             pNext;
    VkImagePipeSurfaceCreateFlagsFUCHSIA    flags;
    zx_handle_t                             imagePipeHandle;
} VkImagePipeSurfaceCreateInfoFUCHSIA;


ಪ್ರಕಾರನಿರ್ದೇಶ VkResult (VKAPI_PTR *PFN_vkCreateImagePipeSurfaceFUCHSIA)(VkInstance instance, ಧ್ರುವ VkImagePipeSurfaceCreateInfoFUCHSIA* pCreateInfo, ಧ್ರುವ VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateImagePipeSurfaceFUCHSIA(
    VkInstance                                  instance,
    ಧ್ರುವ VkImagePipeSurfaceCreateInfoFUCHSIA*  pCreateInfo,
    ಧ್ರುವ VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#endif


// VK_FUCHSIA_external_memory is a preprocessor guard. Do not pass it to API calls.
#define VK_FUCHSIA_external_memory 1

#define VK_FUCHSIA_EXTERNAL_MEMORY_SPEC_VERSION 1
#define VK_FUCHSIA_EXTERNAL_MEMORY_EXTENSION_NAME "VK_FUCHSIA_external_memory"

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkImportMemoryZirconHandleInfoFUCHSIA {
    VkStructureType                       sType;
    ಧ್ರುವ ಶೂನ್ಯ*                           pNext;
    VkExternalMemoryHandleTypeFlagBits    handleType;
    zx_handle_t                           handle;
} VkImportMemoryZirconHandleInfoFUCHSIA;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkMemoryZirconHandlePropertiesFUCHSIA {
    VkStructureType    sType;
    ಶೂನ್ಯ*              pNext;
    uint32_t           memoryTypeBits;
} VkMemoryZirconHandlePropertiesFUCHSIA;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkMemoryGetZirconHandleInfoFUCHSIA {
    VkStructureType                       sType;
    ಧ್ರುವ ಶೂನ್ಯ*                           pNext;
    VkDeviceMemory                        memory;
    VkExternalMemoryHandleTypeFlagBits    handleType;
} VkMemoryGetZirconHandleInfoFUCHSIA;


ಪ್ರಕಾರನಿರ್ದೇಶ VkResult (VKAPI_PTR *PFN_vkGetMemoryZirconHandleFUCHSIA)(VkDevice device, ಧ್ರುವ VkMemoryGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle);
ಪ್ರಕಾರನಿರ್ದೇಶ VkResult (VKAPI_PTR *PFN_vkGetMemoryZirconHandlePropertiesFUCHSIA)(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, zx_handle_t zirconHandle, VkMemoryZirconHandlePropertiesFUCHSIA* pMemoryZirconHandleProperties);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryZirconHandleFUCHSIA(
    VkDevice                                    device,
    ಧ್ರುವ VkMemoryGetZirconHandleInfoFUCHSIA*   pGetZirconHandleInfo,
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

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkImportSemaphoreZirconHandleInfoFUCHSIA {
    VkStructureType                          sType;
    ಧ್ರುವ ಶೂನ್ಯ*                              pNext;
    VkSemaphore                              semaphore;
    VkSemaphoreImportFlags                   flags;
    VkExternalSemaphoreHandleTypeFlagBits    handleType;
    zx_handle_t                              zirconHandle;
} VkImportSemaphoreZirconHandleInfoFUCHSIA;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkSemaphoreGetZirconHandleInfoFUCHSIA {
    VkStructureType                          sType;
    ಧ್ರುವ ಶೂನ್ಯ*                              pNext;
    VkSemaphore                              semaphore;
    VkExternalSemaphoreHandleTypeFlagBits    handleType;
} VkSemaphoreGetZirconHandleInfoFUCHSIA;


ಪ್ರಕಾರನಿರ್ದೇಶ VkResult (VKAPI_PTR *PFN_vkImportSemaphoreZirconHandleFUCHSIA)(VkDevice device, ಧ್ರುವ VkImportSemaphoreZirconHandleInfoFUCHSIA* pImportSemaphoreZirconHandleInfo);
ಪ್ರಕಾರನಿರ್ದೇಶ VkResult (VKAPI_PTR *PFN_vkGetSemaphoreZirconHandleFUCHSIA)(VkDevice device, ಧ್ರುವ VkSemaphoreGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkImportSemaphoreZirconHandleFUCHSIA(
    VkDevice                                    device,
    ಧ್ರುವ VkImportSemaphoreZirconHandleInfoFUCHSIA* pImportSemaphoreZirconHandleInfo);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetSemaphoreZirconHandleFUCHSIA(
    VkDevice                                    device,
    ಧ್ರುವ VkSemaphoreGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo,
    zx_handle_t*                                pZirconHandle);
#endif
#endif


// VK_FUCHSIA_buffer_collection is a preprocessor guard. Do not pass it to API calls.
#define VK_FUCHSIA_buffer_collection 1

VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkBufferCollectionFUCHSIA)

#define VK_FUCHSIA_BUFFER_COLLECTION_SPEC_VERSION 2
#define VK_FUCHSIA_BUFFER_COLLECTION_EXTENSION_NAME "VK_FUCHSIA_buffer_collection"

ಪ್ರಕಾರನಿರ್ದೇಶ VkFlags VkImageFormatConstraintsFlagsFUCHSIA;

ಪ್ರಕಾರನಿರ್ದೇಶ ಗಣನಾ VkImageConstraintsInfoFlagBitsFUCHSIA {
    VK_IMAGE_CONSTRAINTS_INFO_CPU_READ_RARELY_FUCHSIA = 0x00000001,
    VK_IMAGE_CONSTRAINTS_INFO_CPU_READ_OFTEN_FUCHSIA = 0x00000002,
    VK_IMAGE_CONSTRAINTS_INFO_CPU_WRITE_RARELY_FUCHSIA = 0x00000004,
    VK_IMAGE_CONSTRAINTS_INFO_CPU_WRITE_OFTEN_FUCHSIA = 0x00000008,
    VK_IMAGE_CONSTRAINTS_INFO_PROTECTED_OPTIONAL_FUCHSIA = 0x00000010,
    VK_IMAGE_CONSTRAINTS_INFO_FLAG_BITS_MAX_ENUM_FUCHSIA = 0x7FFFFFFF
} VkImageConstraintsInfoFlagBitsFUCHSIA;
ಪ್ರಕಾರನಿರ್ದೇಶ VkFlags VkImageConstraintsInfoFlagsFUCHSIA;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkBufferCollectionCreateInfoFUCHSIA {
    VkStructureType    sType;
    ಧ್ರುವ ಶೂನ್ಯ*        pNext;
    zx_handle_t        collectionToken;
} VkBufferCollectionCreateInfoFUCHSIA;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkImportMemoryBufferCollectionFUCHSIA {
    VkStructureType              sType;
    ಧ್ರುವ ಶೂನ್ಯ*                  pNext;
    VkBufferCollectionFUCHSIA    collection;
    uint32_t                     index;
} VkImportMemoryBufferCollectionFUCHSIA;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkBufferCollectionImageCreateInfoFUCHSIA {
    VkStructureType              sType;
    ಧ್ರುವ ಶೂನ್ಯ*                  pNext;
    VkBufferCollectionFUCHSIA    collection;
    uint32_t                     index;
} VkBufferCollectionImageCreateInfoFUCHSIA;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkBufferCollectionConstraintsInfoFUCHSIA {
    VkStructureType    sType;
    ಧ್ರುವ ಶೂನ್ಯ*        pNext;
    uint32_t           min_Buffer_ಎಣಿಕೆ;
    uint32_t           max_Buffer_ಎಣಿಕೆ;
    uint32_t           min_Buffer_ಎಣಿಕೆ_For_Camping;
    uint32_t           min_Buffer_ಎಣಿಕೆ_For_Dedicated_Slack;
    uint32_t           min_Buffer_ಎಣಿಕೆ_For_Shared_Slack;
} VkBufferCollectionConstraintsInfoFUCHSIA;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkBufferConstraintsInfoFUCHSIA {
    VkStructureType                             sType;
    ಧ್ರುವ ಶೂನ್ಯ*                                 pNext;
    VkBufferCreateInfo                          createInfo;
    VkFormatFeatureFlags                        requiredFormatFeatures;
    VkBufferCollectionConstraintsInfoFUCHSIA    bufferCollectionConstraints;
} VkBufferConstraintsInfoFUCHSIA;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkBufferCollectionBufferCreateInfoFUCHSIA {
    VkStructureType              sType;
    ಧ್ರುವ ಶೂನ್ಯ*                  pNext;
    VkBufferCollectionFUCHSIA    collection;
    uint32_t                     index;
} VkBufferCollectionBufferCreateInfoFUCHSIA;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkSysmemColorSpaceFUCHSIA {
    VkStructureType    sType;
    ಧ್ರುವ ಶೂನ್ಯ*        pNext;
    uint32_t           colorSpace;
} VkSysmemColorSpaceFUCHSIA;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkBufferCollectionPropertiesFUCHSIA {
    VkStructureType                  sType;
    ಶೂನ್ಯ*                            pNext;
    uint32_t                         memoryTypeBits;
    uint32_t                         buffer_ಎಣಿಕೆ;
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

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkImageFormatConstraintsInfoFUCHSIA {
    VkStructureType                         sType;
    ಧ್ರುವ ಶೂನ್ಯ*                             pNext;
    VkImageCreateInfo                       imageCreateInfo;
    VkFormatFeatureFlags                    requiredFormatFeatures;
    VkImageFormatConstraintsFlagsFUCHSIA    flags;
    uint64_t                                sysmemPixelFormat;
    uint32_t                                color_Space_ಎಣಿಕೆ;
    ಧ್ರುವ VkSysmemColorSpaceFUCHSIA*        pColorSpaces;
} VkImageFormatConstraintsInfoFUCHSIA;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkImageConstraintsInfoFUCHSIA {
    VkStructureType                               sType;
    ಧ್ರುವ ಶೂನ್ಯ*                                   pNext;
    uint32_t                                      format_Constraints_ಎಣಿಕೆ;
    ಧ್ರುವ VkImageFormatConstraintsInfoFUCHSIA*    pFormatConstraints;
    VkBufferCollectionConstraintsInfoFUCHSIA      bufferCollectionConstraints;
    VkImageConstraintsInfoFlagsFUCHSIA            flags;
} VkImageConstraintsInfoFUCHSIA;


ಪ್ರಕಾರನಿರ್ದೇಶ VkResult (VKAPI_PTR *PFN_vkCreateBufferCollectionFUCHSIA)(VkDevice device, ಧ್ರುವ VkBufferCollectionCreateInfoFUCHSIA* pCreateInfo, ಧ್ರುವ VkAllocationCallbacks* pAllocator, VkBufferCollectionFUCHSIA* pCollection);
ಪ್ರಕಾರನಿರ್ದೇಶ VkResult (VKAPI_PTR *PFN_vkSetBufferCollectionImageConstraintsFUCHSIA)(VkDevice device, VkBufferCollectionFUCHSIA collection, ಧ್ರುವ VkImageConstraintsInfoFUCHSIA* pImageConstraintsInfo);
ಪ್ರಕಾರನಿರ್ದೇಶ VkResult (VKAPI_PTR *PFN_vkSetBufferCollectionBufferConstraintsFUCHSIA)(VkDevice device, VkBufferCollectionFUCHSIA collection, ಧ್ರುವ VkBufferConstraintsInfoFUCHSIA* pBufferConstraintsInfo);
ಪ್ರಕಾರನಿರ್ದೇಶ ಶೂನ್ಯ (VKAPI_PTR *PFN_vkDestroyBufferCollectionFUCHSIA)(VkDevice device, VkBufferCollectionFUCHSIA collection, ಧ್ರುವ VkAllocationCallbacks* pAllocator);
ಪ್ರಕಾರನಿರ್ದೇಶ VkResult (VKAPI_PTR *PFN_vkGetBufferCollectionPropertiesFUCHSIA)(VkDevice device, VkBufferCollectionFUCHSIA collection, VkBufferCollectionPropertiesFUCHSIA* pProperties);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateBufferCollectionFUCHSIA(
    VkDevice                                    device,
    ಧ್ರುವ VkBufferCollectionCreateInfoFUCHSIA*  pCreateInfo,
    ಧ್ರುವ VkAllocationCallbacks*                pAllocator,
    VkBufferCollectionFUCHSIA*                  pCollection);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkSetBufferCollectionImageConstraintsFUCHSIA(
    VkDevice                                    device,
    VkBufferCollectionFUCHSIA                   collection,
    ಧ್ರುವ VkImageConstraintsInfoFUCHSIA*        pImageConstraintsInfo);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkSetBufferCollectionBufferConstraintsFUCHSIA(
    VkDevice                                    device,
    VkBufferCollectionFUCHSIA                   collection,
    ಧ್ರುವ VkBufferConstraintsInfoFUCHSIA*       pBufferConstraintsInfo);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR ಶೂನ್ಯ VKAPI_CALL vkDestroyBufferCollectionFUCHSIA(
    VkDevice                                    device,
    VkBufferCollectionFUCHSIA                   collection,
    ಧ್ರುವ VkAllocationCallbacks*                pAllocator);
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
