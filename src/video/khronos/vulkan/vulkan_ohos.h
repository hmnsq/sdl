#ifndef VULKAN_OHOS_H_
#define VULKAN_OHOS_H_ 1

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
বাহ্য "C" {
#endif



// VK_OHOS_external_memory is a preprocessor guard. Do not pass it to API calls.
#define VK_OHOS_external_memory 1

সংরচনা OH_NativeBuffer;

#define VK_OHOS_EXTERNAL_MEMORY_SPEC_VERSION 1
#define VK_OHOS_EXTERNAL_MEMORY_EXTENSION_NAME "VK_OHOS_external_memory"

প্রকারনির্দেশ সংরচনা VkNativeBufferUsageOHOS {
    VkStructureType    sType;
    শূন্য*              pNext;
    uint64_t           OHOSNativeBufferUsage;
} VkNativeBufferUsageOHOS;

প্রকারনির্দেশ সংরচনা VkNativeBufferPropertiesOHOS {
    VkStructureType    sType;
    শূন্য*              pNext;
    VkDeviceSize       allocationSize;
    uint32_t           memoryTypeBits;
} VkNativeBufferPropertiesOHOS;

প্রকারনির্দেশ সংরচনা VkNativeBufferFormatPropertiesOHOS {
    VkStructureType                  sType;
    শূন্য*                            pNext;
    VkFormat                         format;
    uint64_t                         externalFormat;
    VkFormatFeatureFlags             formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggestedXChromaOffset;
    VkChromaLocation                 suggestedYChromaOffset;
} VkNativeBufferFormatPropertiesOHOS;

প্রকারনির্দেশ সংরচনা VkImportNativeBufferInfoOHOS {
    VkStructureType            sType;
    ধ্রুৱ শূন্য*                pNext;
    সংরচনা OH_NativeBuffer*    buffer;
} VkImportNativeBufferInfoOHOS;

প্রকারনির্দেশ সংরচনা VkMemoryGetNativeBufferInfoOHOS {
    VkStructureType    sType;
    ধ্রুৱ শূন্য*        pNext;
    VkDeviceMemory     memory;
} VkMemoryGetNativeBufferInfoOHOS;

প্রকারনির্দেশ সংরচনা VkExternalFormatOHOS {
    VkStructureType    sType;
    শূন্য*              pNext;
    uint64_t           externalFormat;
} VkExternalFormatOHOS;


প্রকারনির্দেশ VkResult (VKAPI_PTR *PFN_vkGetNativeBufferPropertiesOHOS)(VkDevice device, ধ্রুৱ সংরচনা OH_NativeBuffer* buffer, VkNativeBufferPropertiesOHOS* pProperties);
প্রকারনির্দেশ VkResult (VKAPI_PTR *PFN_vkGetMemoryNativeBufferOHOS)(VkDevice device, ধ্রুৱ VkMemoryGetNativeBufferInfoOHOS* pInfo, সংরচনা OH_NativeBuffer** pBuffer);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetNativeBufferPropertiesOHOS(
    VkDevice                                    device,
    ধ্রুৱ সংরচনা OH_NativeBuffer*               buffer,
    VkNativeBufferPropertiesOHOS*               pProperties);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryNativeBufferOHOS(
    VkDevice                                    device,
    ধ্রুৱ VkMemoryGetNativeBufferInfoOHOS*      pInfo,
    সংরচনা OH_NativeBuffer**                    pBuffer);
#endif
#endif


// VK_OHOS_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_OHOS_surface 1

প্রকারনির্দেশ সংরচনা NativeWindow OHNativeWindow;

#define VK_OHOS_SURFACE_SPEC_VERSION      1
#define VK_OHOS_SURFACE_EXTENSION_NAME    "VK_OHOS_surface"

প্রকারনির্দেশ VkFlags VkSurfaceCreateFlagsOHOS;

প্রকারনির্দেশ সংরচনা VkSurfaceCreateInfoOHOS {
    VkStructureType             sType;
    ধ্রুৱ শূন্য*                 pNext;
    VkSurfaceCreateFlagsOHOS    flags;
    OHNativeWindow*             window;
} VkSurfaceCreateInfoOHOS;


প্রকারনির্দেশ VkResult (VKAPI_PTR *PFN_vkCreateSurfaceOHOS)(VkInstance instance, ধ্রুৱ VkSurfaceCreateInfoOHOS* pCreateInfo, ধ্রুৱ VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateSurfaceOHOS(
    VkInstance                                  instance,
    ধ্রুৱ VkSurfaceCreateInfoOHOS*              pCreateInfo,
    ধ্রুৱ VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif
