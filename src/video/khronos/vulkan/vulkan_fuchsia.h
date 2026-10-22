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
ବାହ୍ୟ "C" {
#endif



// VK_FUCHSIA_imagepipe_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_FUCHSIA_imagepipe_surface 1

#define VK_FUCHSIA_IMAGEPIPE_SURFACE_SPEC_VERSION 1
#define VK_FUCHSIA_IMAGEPIPE_SURFACE_EXTENSION_NAME "VK_FUCHSIA_imagepipe_surface"

ପ୍ରକାରବ୍ୟାଖ୍ୟା VkFlags VkImagePipeSurfaceCreateFlagsFUCHSIA;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkImagePipeSurfaceCreateInfoFUCHSIA {
    VkStructureType                         sType;
    ଅଚଳ ଶୂନ୍ୟ*                             pNext;
    VkImagePipeSurfaceCreateFlagsFUCHSIA    flags;
    zx_handle_t                             imagePipeHandle;
} VkImagePipeSurfaceCreateInfoFUCHSIA;


ପ୍ରକାରବ୍ୟାଖ୍ୟା VkResult (VKAPI_PTR *PFN_vkCreateImagePipeSurfaceFUCHSIA)(VkInstance instance, ଅଚଳ VkImagePipeSurfaceCreateInfoFUCHSIA* pCreateInfo, ଅଚଳ VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateImagePipeSurfaceFUCHSIA(
    VkInstance                                  instance,
    ଅଚଳ VkImagePipeSurfaceCreateInfoFUCHSIA*  pCreateInfo,
    ଅଚଳ VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#endif


// VK_FUCHSIA_external_memory is a preprocessor guard. Do not pass it to API calls.
#define VK_FUCHSIA_external_memory 1

#define VK_FUCHSIA_EXTERNAL_MEMORY_SPEC_VERSION 1
#define VK_FUCHSIA_EXTERNAL_MEMORY_EXTENSION_NAME "VK_FUCHSIA_external_memory"

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkImportMemoryZirconHandleInfoFUCHSIA {
    VkStructureType                       sType;
    ଅଚଳ ଶୂନ୍ୟ*                           pNext;
    VkExternalMemoryHandleTypeFlagBits    handleType;
    zx_handle_t                           handle;
} VkImportMemoryZirconHandleInfoFUCHSIA;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkMemoryZirconHandlePropertiesFUCHSIA {
    VkStructureType    sType;
    ଶୂନ୍ୟ*              pNext;
    uint32_t           memoryTypeBits;
} VkMemoryZirconHandlePropertiesFUCHSIA;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkMemoryGetZirconHandleInfoFUCHSIA {
    VkStructureType                       sType;
    ଅଚଳ ଶୂନ୍ୟ*                           pNext;
    VkDeviceMemory                        memory;
    VkExternalMemoryHandleTypeFlagBits    handleType;
} VkMemoryGetZirconHandleInfoFUCHSIA;


ପ୍ରକାରବ୍ୟାଖ୍ୟା VkResult (VKAPI_PTR *PFN_vkGetMemoryZirconHandleFUCHSIA)(VkDevice device, ଅଚଳ VkMemoryGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle);
ପ୍ରକାରବ୍ୟାଖ୍ୟା VkResult (VKAPI_PTR *PFN_vkGetMemoryZirconHandlePropertiesFUCHSIA)(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, zx_handle_t zirconHandle, VkMemoryZirconHandlePropertiesFUCHSIA* pMemoryZirconHandleProperties);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryZirconHandleFUCHSIA(
    VkDevice                                    device,
    ଅଚଳ VkMemoryGetZirconHandleInfoFUCHSIA*   pGetZirconHandleInfo,
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

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkImportSemaphoreZirconHandleInfoFUCHSIA {
    VkStructureType                          sType;
    ଅଚଳ ଶୂନ୍ୟ*                              pNext;
    VkSemaphore                              semaphore;
    VkSemaphoreImportFlags                   flags;
    VkExternalSemaphoreHandleTypeFlagBits    handleType;
    zx_handle_t                              zirconHandle;
} VkImportSemaphoreZirconHandleInfoFUCHSIA;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkSemaphoreGetZirconHandleInfoFUCHSIA {
    VkStructureType                          sType;
    ଅଚଳ ଶୂନ୍ୟ*                              pNext;
    VkSemaphore                              semaphore;
    VkExternalSemaphoreHandleTypeFlagBits    handleType;
} VkSemaphoreGetZirconHandleInfoFUCHSIA;


ପ୍ରକାରବ୍ୟାଖ୍ୟା VkResult (VKAPI_PTR *PFN_vkImportSemaphoreZirconHandleFUCHSIA)(VkDevice device, ଅଚଳ VkImportSemaphoreZirconHandleInfoFUCHSIA* pImportSemaphoreZirconHandleInfo);
ପ୍ରକାରବ୍ୟାଖ୍ୟା VkResult (VKAPI_PTR *PFN_vkGetSemaphoreZirconHandleFUCHSIA)(VkDevice device, ଅଚଳ VkSemaphoreGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkImportSemaphoreZirconHandleFUCHSIA(
    VkDevice                                    device,
    ଅଚଳ VkImportSemaphoreZirconHandleInfoFUCHSIA* pImportSemaphoreZirconHandleInfo);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetSemaphoreZirconHandleFUCHSIA(
    VkDevice                                    device,
    ଅଚଳ VkSemaphoreGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo,
    zx_handle_t*                                pZirconHandle);
#endif
#endif


// VK_FUCHSIA_buffer_collection is a preprocessor guard. Do not pass it to API calls.
#define VK_FUCHSIA_buffer_collection 1

VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkBufferCollectionFUCHSIA)

#define VK_FUCHSIA_BUFFER_COLLECTION_SPEC_VERSION 2
#define VK_FUCHSIA_BUFFER_COLLECTION_EXTENSION_NAME "VK_FUCHSIA_buffer_collection"

ପ୍ରକାରବ୍ୟାଖ୍ୟା VkFlags VkImageFormatConstraintsFlagsFUCHSIA;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ଗଣନା VkImageConstraintsInfoFlagBitsFUCHSIA {
    VK_IMAGE_CONSTRAINTS_INFO_CPU_READ_RARELY_FUCHSIA = 0x00000001,
    VK_IMAGE_CONSTRAINTS_INFO_CPU_READ_OFTEN_FUCHSIA = 0x00000002,
    VK_IMAGE_CONSTRAINTS_INFO_CPU_WRITE_RARELY_FUCHSIA = 0x00000004,
    VK_IMAGE_CONSTRAINTS_INFO_CPU_WRITE_OFTEN_FUCHSIA = 0x00000008,
    VK_IMAGE_CONSTRAINTS_INFO_PROTECTED_OPTIONAL_FUCHSIA = 0x00000010,
    VK_IMAGE_CONSTRAINTS_INFO_FLAG_BITS_MAX_ENUM_FUCHSIA = 0x7FFFFFFF
} VkImageConstraintsInfoFlagBitsFUCHSIA;
ପ୍ରକାରବ୍ୟାଖ୍ୟା VkFlags VkImageConstraintsInfoFlagsFUCHSIA;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkBufferCollectionCreateInfoFUCHSIA {
    VkStructureType    sType;
    ଅଚଳ ଶୂନ୍ୟ*        pNext;
    zx_handle_t        collectionToken;
} VkBufferCollectionCreateInfoFUCHSIA;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkImportMemoryBufferCollectionFUCHSIA {
    VkStructureType              sType;
    ଅଚଳ ଶୂନ୍ୟ*                  pNext;
    VkBufferCollectionFUCHSIA    collection;
    uint32_t                     index;
} VkImportMemoryBufferCollectionFUCHSIA;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkBufferCollectionImageCreateInfoFUCHSIA {
    VkStructureType              sType;
    ଅଚଳ ଶୂନ୍ୟ*                  pNext;
    VkBufferCollectionFUCHSIA    collection;
    uint32_t                     index;
} VkBufferCollectionImageCreateInfoFUCHSIA;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkBufferCollectionConstraintsInfoFUCHSIA {
    VkStructureType    sType;
    ଅଚଳ ଶୂନ୍ୟ*        pNext;
    uint32_t           min_Buffer_ଗଣନା;
    uint32_t           max_Buffer_ଗଣନା;
    uint32_t           min_Buffer_ଗଣନା_For_Camping;
    uint32_t           min_Buffer_ଗଣନା_For_Dedicated_Slack;
    uint32_t           min_Buffer_ଗଣନା_For_Shared_Slack;
} VkBufferCollectionConstraintsInfoFUCHSIA;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkBufferConstraintsInfoFUCHSIA {
    VkStructureType                             sType;
    ଅଚଳ ଶୂନ୍ୟ*                                 pNext;
    VkBufferCreateInfo                          createInfo;
    VkFormatFeatureFlags                        requiredFormatFeatures;
    VkBufferCollectionConstraintsInfoFUCHSIA    bufferCollectionConstraints;
} VkBufferConstraintsInfoFUCHSIA;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkBufferCollectionBufferCreateInfoFUCHSIA {
    VkStructureType              sType;
    ଅଚଳ ଶୂନ୍ୟ*                  pNext;
    VkBufferCollectionFUCHSIA    collection;
    uint32_t                     index;
} VkBufferCollectionBufferCreateInfoFUCHSIA;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkSysmemColorSpaceFUCHSIA {
    VkStructureType    sType;
    ଅଚଳ ଶୂନ୍ୟ*        pNext;
    uint32_t           colorSpace;
} VkSysmemColorSpaceFUCHSIA;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkBufferCollectionPropertiesFUCHSIA {
    VkStructureType                  sType;
    ଶୂନ୍ୟ*                            pNext;
    uint32_t                         memoryTypeBits;
    uint32_t                         buffer_ଗଣନା;
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

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkImageFormatConstraintsInfoFUCHSIA {
    VkStructureType                         sType;
    ଅଚଳ ଶୂନ୍ୟ*                             pNext;
    VkImageCreateInfo                       imageCreateInfo;
    VkFormatFeatureFlags                    requiredFormatFeatures;
    VkImageFormatConstraintsFlagsFUCHSIA    flags;
    uint64_t                                sysmemPixelFormat;
    uint32_t                                color_Space_ଗଣନା;
    ଅଚଳ VkSysmemColorSpaceFUCHSIA*        pColorSpaces;
} VkImageFormatConstraintsInfoFUCHSIA;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkImageConstraintsInfoFUCHSIA {
    VkStructureType                               sType;
    ଅଚଳ ଶୂନ୍ୟ*                                   pNext;
    uint32_t                                      format_Constraints_ଗଣନା;
    ଅଚଳ VkImageFormatConstraintsInfoFUCHSIA*    pFormatConstraints;
    VkBufferCollectionConstraintsInfoFUCHSIA      bufferCollectionConstraints;
    VkImageConstraintsInfoFlagsFUCHSIA            flags;
} VkImageConstraintsInfoFUCHSIA;


ପ୍ରକାରବ୍ୟାଖ୍ୟା VkResult (VKAPI_PTR *PFN_vkCreateBufferCollectionFUCHSIA)(VkDevice device, ଅଚଳ VkBufferCollectionCreateInfoFUCHSIA* pCreateInfo, ଅଚଳ VkAllocationCallbacks* pAllocator, VkBufferCollectionFUCHSIA* pCollection);
ପ୍ରକାରବ୍ୟାଖ୍ୟା VkResult (VKAPI_PTR *PFN_vkSetBufferCollectionImageConstraintsFUCHSIA)(VkDevice device, VkBufferCollectionFUCHSIA collection, ଅଚଳ VkImageConstraintsInfoFUCHSIA* pImageConstraintsInfo);
ପ୍ରକାରବ୍ୟାଖ୍ୟା VkResult (VKAPI_PTR *PFN_vkSetBufferCollectionBufferConstraintsFUCHSIA)(VkDevice device, VkBufferCollectionFUCHSIA collection, ଅଚଳ VkBufferConstraintsInfoFUCHSIA* pBufferConstraintsInfo);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (VKAPI_PTR *PFN_vkDestroyBufferCollectionFUCHSIA)(VkDevice device, VkBufferCollectionFUCHSIA collection, ଅଚଳ VkAllocationCallbacks* pAllocator);
ପ୍ରକାରବ୍ୟାଖ୍ୟା VkResult (VKAPI_PTR *PFN_vkGetBufferCollectionPropertiesFUCHSIA)(VkDevice device, VkBufferCollectionFUCHSIA collection, VkBufferCollectionPropertiesFUCHSIA* pProperties);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateBufferCollectionFUCHSIA(
    VkDevice                                    device,
    ଅଚଳ VkBufferCollectionCreateInfoFUCHSIA*  pCreateInfo,
    ଅଚଳ VkAllocationCallbacks*                pAllocator,
    VkBufferCollectionFUCHSIA*                  pCollection);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkSetBufferCollectionImageConstraintsFUCHSIA(
    VkDevice                                    device,
    VkBufferCollectionFUCHSIA                   collection,
    ଅଚଳ VkImageConstraintsInfoFUCHSIA*        pImageConstraintsInfo);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkSetBufferCollectionBufferConstraintsFUCHSIA(
    VkDevice                                    device,
    VkBufferCollectionFUCHSIA                   collection,
    ଅଚଳ VkBufferConstraintsInfoFUCHSIA*       pBufferConstraintsInfo);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR ଶୂନ୍ୟ VKAPI_CALL vkDestroyBufferCollectionFUCHSIA(
    VkDevice                                    device,
    VkBufferCollectionFUCHSIA                   collection,
    ଅଚଳ VkAllocationCallbacks*                pAllocator);
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
