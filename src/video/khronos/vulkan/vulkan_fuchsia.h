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
बाह्य "C" {
#endif



// VK_FUCHSIA_imagepipe_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_FUCHSIA_imagepipe_surface 1

#define VK_FUCHSIA_IMAGEPIPE_SURFACE_SPEC_VERSION 1
#define VK_FUCHSIA_IMAGEPIPE_SURFACE_EXTENSION_NAME "VK_FUCHSIA_imagepipe_surface"

प्रकारनिर्देश VkFlags VkImagePipeSurfaceCreateFlagsFUCHSIA;

प्रकारनिर्देश संरचना VkImagePipeSurfaceCreateInfoFUCHSIA {
    VkStructureType                         sType;
    ध्रुव शून्य*                             pNext;
    VkImagePipeSurfaceCreateFlagsFUCHSIA    flags;
    zx_handle_t                             imagePipeHandle;
} VkImagePipeSurfaceCreateInfoFUCHSIA;


प्रकारनिर्देश VkResult (VKAPI_PTR *PFN_vkCreateImagePipeSurfaceFUCHSIA)(VkInstance instance, ध्रुव VkImagePipeSurfaceCreateInfoFUCHSIA* pCreateInfo, ध्रुव VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateImagePipeSurfaceFUCHSIA(
    VkInstance                                  instance,
    ध्रुव VkImagePipeSurfaceCreateInfoFUCHSIA*  pCreateInfo,
    ध्रुव VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#endif


// VK_FUCHSIA_external_memory is a preprocessor guard. Do not pass it to API calls.
#define VK_FUCHSIA_external_memory 1

#define VK_FUCHSIA_EXTERNAL_MEMORY_SPEC_VERSION 1
#define VK_FUCHSIA_EXTERNAL_MEMORY_EXTENSION_NAME "VK_FUCHSIA_external_memory"

प्रकारनिर्देश संरचना VkImportMemoryZirconHandleInfoFUCHSIA {
    VkStructureType                       sType;
    ध्रुव शून्य*                           pNext;
    VkExternalMemoryHandleTypeFlagBits    handleType;
    zx_handle_t                           handle;
} VkImportMemoryZirconHandleInfoFUCHSIA;

प्रकारनिर्देश संरचना VkMemoryZirconHandlePropertiesFUCHSIA {
    VkStructureType    sType;
    शून्य*              pNext;
    uint32_t           memoryTypeBits;
} VkMemoryZirconHandlePropertiesFUCHSIA;

प्रकारनिर्देश संरचना VkMemoryGetZirconHandleInfoFUCHSIA {
    VkStructureType                       sType;
    ध्रुव शून्य*                           pNext;
    VkDeviceMemory                        memory;
    VkExternalMemoryHandleTypeFlagBits    handleType;
} VkMemoryGetZirconHandleInfoFUCHSIA;


प्रकारनिर्देश VkResult (VKAPI_PTR *PFN_vkGetMemoryZirconHandleFUCHSIA)(VkDevice device, ध्रुव VkMemoryGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle);
प्रकारनिर्देश VkResult (VKAPI_PTR *PFN_vkGetMemoryZirconHandlePropertiesFUCHSIA)(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, zx_handle_t zirconHandle, VkMemoryZirconHandlePropertiesFUCHSIA* pMemoryZirconHandleProperties);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryZirconHandleFUCHSIA(
    VkDevice                                    device,
    ध्रुव VkMemoryGetZirconHandleInfoFUCHSIA*   pGetZirconHandleInfo,
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

प्रकारनिर्देश संरचना VkImportSemaphoreZirconHandleInfoFUCHSIA {
    VkStructureType                          sType;
    ध्रुव शून्य*                              pNext;
    VkSemaphore                              semaphore;
    VkSemaphoreImportFlags                   flags;
    VkExternalSemaphoreHandleTypeFlagBits    handleType;
    zx_handle_t                              zirconHandle;
} VkImportSemaphoreZirconHandleInfoFUCHSIA;

प्रकारनिर्देश संरचना VkSemaphoreGetZirconHandleInfoFUCHSIA {
    VkStructureType                          sType;
    ध्रुव शून्य*                              pNext;
    VkSemaphore                              semaphore;
    VkExternalSemaphoreHandleTypeFlagBits    handleType;
} VkSemaphoreGetZirconHandleInfoFUCHSIA;


प्रकारनिर्देश VkResult (VKAPI_PTR *PFN_vkImportSemaphoreZirconHandleFUCHSIA)(VkDevice device, ध्रुव VkImportSemaphoreZirconHandleInfoFUCHSIA* pImportSemaphoreZirconHandleInfo);
प्रकारनिर्देश VkResult (VKAPI_PTR *PFN_vkGetSemaphoreZirconHandleFUCHSIA)(VkDevice device, ध्रुव VkSemaphoreGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkImportSemaphoreZirconHandleFUCHSIA(
    VkDevice                                    device,
    ध्रुव VkImportSemaphoreZirconHandleInfoFUCHSIA* pImportSemaphoreZirconHandleInfo);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetSemaphoreZirconHandleFUCHSIA(
    VkDevice                                    device,
    ध्रुव VkSemaphoreGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo,
    zx_handle_t*                                pZirconHandle);
#endif
#endif


// VK_FUCHSIA_buffer_collection is a preprocessor guard. Do not pass it to API calls.
#define VK_FUCHSIA_buffer_collection 1

VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkBufferCollectionFUCHSIA)

#define VK_FUCHSIA_BUFFER_COLLECTION_SPEC_VERSION 2
#define VK_FUCHSIA_BUFFER_COLLECTION_EXTENSION_NAME "VK_FUCHSIA_buffer_collection"

प्रकारनिर्देश VkFlags VkImageFormatConstraintsFlagsFUCHSIA;

प्रकारनिर्देश गणना VkImageConstraintsInfoFlagBitsFUCHSIA {
    VK_IMAGE_CONSTRAINTS_INFO_CPU_READ_RARELY_FUCHSIA = 0x00000001,
    VK_IMAGE_CONSTRAINTS_INFO_CPU_READ_OFTEN_FUCHSIA = 0x00000002,
    VK_IMAGE_CONSTRAINTS_INFO_CPU_WRITE_RARELY_FUCHSIA = 0x00000004,
    VK_IMAGE_CONSTRAINTS_INFO_CPU_WRITE_OFTEN_FUCHSIA = 0x00000008,
    VK_IMAGE_CONSTRAINTS_INFO_PROTECTED_OPTIONAL_FUCHSIA = 0x00000010,
    VK_IMAGE_CONSTRAINTS_INFO_FLAG_BITS_MAX_ENUM_FUCHSIA = 0x7FFFFFFF
} VkImageConstraintsInfoFlagBitsFUCHSIA;
प्रकारनिर्देश VkFlags VkImageConstraintsInfoFlagsFUCHSIA;

प्रकारनिर्देश संरचना VkBufferCollectionCreateInfoFUCHSIA {
    VkStructureType    sType;
    ध्रुव शून्य*        pNext;
    zx_handle_t        collectionToken;
} VkBufferCollectionCreateInfoFUCHSIA;

प्रकारनिर्देश संरचना VkImportMemoryBufferCollectionFUCHSIA {
    VkStructureType              sType;
    ध्रुव शून्य*                  pNext;
    VkBufferCollectionFUCHSIA    collection;
    uint32_t                     index;
} VkImportMemoryBufferCollectionFUCHSIA;

प्रकारनिर्देश संरचना VkBufferCollectionImageCreateInfoFUCHSIA {
    VkStructureType              sType;
    ध्रुव शून्य*                  pNext;
    VkBufferCollectionFUCHSIA    collection;
    uint32_t                     index;
} VkBufferCollectionImageCreateInfoFUCHSIA;

प्रकारनिर्देश संरचना VkBufferCollectionConstraintsInfoFUCHSIA {
    VkStructureType    sType;
    ध्रुव शून्य*        pNext;
    uint32_t           min_Buffer_मोजणी;
    uint32_t           max_Buffer_मोजणी;
    uint32_t           min_Buffer_मोजणी_For_Camping;
    uint32_t           min_Buffer_मोजणी_For_Dedicated_Slack;
    uint32_t           min_Buffer_मोजणी_For_Shared_Slack;
} VkBufferCollectionConstraintsInfoFUCHSIA;

प्रकारनिर्देश संरचना VkBufferConstraintsInfoFUCHSIA {
    VkStructureType                             sType;
    ध्रुव शून्य*                                 pNext;
    VkBufferCreateInfo                          createInfo;
    VkFormatFeatureFlags                        requiredFormatFeatures;
    VkBufferCollectionConstraintsInfoFUCHSIA    bufferCollectionConstraints;
} VkBufferConstraintsInfoFUCHSIA;

प्रकारनिर्देश संरचना VkBufferCollectionBufferCreateInfoFUCHSIA {
    VkStructureType              sType;
    ध्रुव शून्य*                  pNext;
    VkBufferCollectionFUCHSIA    collection;
    uint32_t                     index;
} VkBufferCollectionBufferCreateInfoFUCHSIA;

प्रकारनिर्देश संरचना VkSysmemColorSpaceFUCHSIA {
    VkStructureType    sType;
    ध्रुव शून्य*        pNext;
    uint32_t           colorSpace;
} VkSysmemColorSpaceFUCHSIA;

प्रकारनिर्देश संरचना VkBufferCollectionPropertiesFUCHSIA {
    VkStructureType                  sType;
    शून्य*                            pNext;
    uint32_t                         memoryTypeBits;
    uint32_t                         buffer_मोजणी;
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

प्रकारनिर्देश संरचना VkImageFormatConstraintsInfoFUCHSIA {
    VkStructureType                         sType;
    ध्रुव शून्य*                             pNext;
    VkImageCreateInfo                       imageCreateInfo;
    VkFormatFeatureFlags                    requiredFormatFeatures;
    VkImageFormatConstraintsFlagsFUCHSIA    flags;
    uint64_t                                sysmemPixelFormat;
    uint32_t                                color_Space_मोजणी;
    ध्रुव VkSysmemColorSpaceFUCHSIA*        pColorSpaces;
} VkImageFormatConstraintsInfoFUCHSIA;

प्रकारनिर्देश संरचना VkImageConstraintsInfoFUCHSIA {
    VkStructureType                               sType;
    ध्रुव शून्य*                                   pNext;
    uint32_t                                      format_Constraints_मोजणी;
    ध्रुव VkImageFormatConstraintsInfoFUCHSIA*    pFormatConstraints;
    VkBufferCollectionConstraintsInfoFUCHSIA      bufferCollectionConstraints;
    VkImageConstraintsInfoFlagsFUCHSIA            flags;
} VkImageConstraintsInfoFUCHSIA;


प्रकारनिर्देश VkResult (VKAPI_PTR *PFN_vkCreateBufferCollectionFUCHSIA)(VkDevice device, ध्रुव VkBufferCollectionCreateInfoFUCHSIA* pCreateInfo, ध्रुव VkAllocationCallbacks* pAllocator, VkBufferCollectionFUCHSIA* pCollection);
प्रकारनिर्देश VkResult (VKAPI_PTR *PFN_vkSetBufferCollectionImageConstraintsFUCHSIA)(VkDevice device, VkBufferCollectionFUCHSIA collection, ध्रुव VkImageConstraintsInfoFUCHSIA* pImageConstraintsInfo);
प्रकारनिर्देश VkResult (VKAPI_PTR *PFN_vkSetBufferCollectionBufferConstraintsFUCHSIA)(VkDevice device, VkBufferCollectionFUCHSIA collection, ध्रुव VkBufferConstraintsInfoFUCHSIA* pBufferConstraintsInfo);
प्रकारनिर्देश शून्य (VKAPI_PTR *PFN_vkDestroyBufferCollectionFUCHSIA)(VkDevice device, VkBufferCollectionFUCHSIA collection, ध्रुव VkAllocationCallbacks* pAllocator);
प्रकारनिर्देश VkResult (VKAPI_PTR *PFN_vkGetBufferCollectionPropertiesFUCHSIA)(VkDevice device, VkBufferCollectionFUCHSIA collection, VkBufferCollectionPropertiesFUCHSIA* pProperties);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateBufferCollectionFUCHSIA(
    VkDevice                                    device,
    ध्रुव VkBufferCollectionCreateInfoFUCHSIA*  pCreateInfo,
    ध्रुव VkAllocationCallbacks*                pAllocator,
    VkBufferCollectionFUCHSIA*                  pCollection);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkSetBufferCollectionImageConstraintsFUCHSIA(
    VkDevice                                    device,
    VkBufferCollectionFUCHSIA                   collection,
    ध्रुव VkImageConstraintsInfoFUCHSIA*        pImageConstraintsInfo);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkSetBufferCollectionBufferConstraintsFUCHSIA(
    VkDevice                                    device,
    VkBufferCollectionFUCHSIA                   collection,
    ध्रुव VkBufferConstraintsInfoFUCHSIA*       pBufferConstraintsInfo);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR शून्य VKAPI_CALL vkDestroyBufferCollectionFUCHSIA(
    VkDevice                                    device,
    VkBufferCollectionFUCHSIA                   collection,
    ध्रुव VkAllocationCallbacks*                pAllocator);
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
