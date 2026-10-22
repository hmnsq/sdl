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
ബാഹ്യ "C" {
#endif



// VK_OHOS_external_memory is a preprocessor guard. Do not pass it to API calls.
#define VK_OHOS_external_memory 1

ഘടന OH_NativeBuffer;

#define VK_OHOS_EXTERNAL_MEMORY_SPEC_VERSION 1
#define VK_OHOS_EXTERNAL_MEMORY_EXTENSION_NAME "VK_OHOS_external_memory"

തരനിർവചനം ഘടന VkNativeBufferUsageOHOS {
    VkStructureType    sType;
    ശൂന്യം*              pNext;
    uint64_t           OHOSNativeBufferUsage;
} VkNativeBufferUsageOHOS;

തരനിർവചനം ഘടന VkNativeBufferPropertiesOHOS {
    VkStructureType    sType;
    ശൂന്യം*              pNext;
    VkDeviceSize       allocationSize;
    uint32_t           memoryTypeBits;
} VkNativeBufferPropertiesOHOS;

തരനിർവചനം ഘടന VkNativeBufferFormatPropertiesOHOS {
    VkStructureType                  sType;
    ശൂന്യം*                            pNext;
    VkFormat                         format;
    uint64_t                         externalFormat;
    VkFormatFeatureFlags             formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggestedXChromaOffset;
    VkChromaLocation                 suggestedYChromaOffset;
} VkNativeBufferFormatPropertiesOHOS;

തരനിർവചനം ഘടന VkImportNativeBufferInfoOHOS {
    VkStructureType            sType;
    സ്ഥിരം ശൂന്യം*                pNext;
    ഘടന OH_NativeBuffer*    buffer;
} VkImportNativeBufferInfoOHOS;

തരനിർവചനം ഘടന VkMemoryGetNativeBufferInfoOHOS {
    VkStructureType    sType;
    സ്ഥിരം ശൂന്യം*        pNext;
    VkDeviceMemory     memory;
} VkMemoryGetNativeBufferInfoOHOS;

തരനിർവചനം ഘടന VkExternalFormatOHOS {
    VkStructureType    sType;
    ശൂന്യം*              pNext;
    uint64_t           externalFormat;
} VkExternalFormatOHOS;


തരനിർവചനം VkResult (VKAPI_PTR *PFN_vkGetNativeBufferPropertiesOHOS)(VkDevice device, സ്ഥിരം ഘടന OH_NativeBuffer* buffer, VkNativeBufferPropertiesOHOS* pProperties);
തരനിർവചനം VkResult (VKAPI_PTR *PFN_vkGetMemoryNativeBufferOHOS)(VkDevice device, സ്ഥിരം VkMemoryGetNativeBufferInfoOHOS* pInfo, ഘടന OH_NativeBuffer** pBuffer);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetNativeBufferPropertiesOHOS(
    VkDevice                                    device,
    സ്ഥിരം ഘടന OH_NativeBuffer*               buffer,
    VkNativeBufferPropertiesOHOS*               pProperties);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryNativeBufferOHOS(
    VkDevice                                    device,
    സ്ഥിരം VkMemoryGetNativeBufferInfoOHOS*      pInfo,
    ഘടന OH_NativeBuffer**                    pBuffer);
#endif
#endif


// VK_OHOS_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_OHOS_surface 1

തരനിർവചനം ഘടന NativeWindow OHNativeWindow;

#define VK_OHOS_SURFACE_SPEC_VERSION      1
#define VK_OHOS_SURFACE_EXTENSION_NAME    "VK_OHOS_surface"

തരനിർവചനം VkFlags VkSurfaceCreateFlagsOHOS;

തരനിർവചനം ഘടന VkSurfaceCreateInfoOHOS {
    VkStructureType             sType;
    സ്ഥിരം ശൂന്യം*                 pNext;
    VkSurfaceCreateFlagsOHOS    flags;
    OHNativeWindow*             window;
} VkSurfaceCreateInfoOHOS;


തരനിർവചനം VkResult (VKAPI_PTR *PFN_vkCreateSurfaceOHOS)(VkInstance instance, സ്ഥിരം VkSurfaceCreateInfoOHOS* pCreateInfo, സ്ഥിരം VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateSurfaceOHOS(
    VkInstance                                  instance,
    സ്ഥിരം VkSurfaceCreateInfoOHOS*              pCreateInfo,
    സ്ഥിരം VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif
