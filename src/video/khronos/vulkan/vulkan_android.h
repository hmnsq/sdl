#ifndef VULKAN_ANDROID_H_
#define VULKAN_ANDROID_H_ 1

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



// VK_KHR_android_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_android_surface 1

ഘടന ANativeWindow;

#define VK_KHR_ANDROID_SURFACE_SPEC_VERSION 6
#define VK_KHR_ANDROID_SURFACE_EXTENSION_NAME "VK_KHR_android_surface"

തരനിർവചനം VkFlags VkAndroidSurfaceCreateFlagsKHR;

തരനിർവചനം ഘടന VkAndroidSurfaceCreateInfoKHR {
    VkStructureType                   sType;
    സ്ഥിരം ശൂന്യം*                       pNext;
    VkAndroidSurfaceCreateFlagsKHR    flags;
    ഘടന ANativeWindow*             window;
} VkAndroidSurfaceCreateInfoKHR;


തരനിർവചനം VkResult (VKAPI_PTR *PFN_vkCreateAndroidSurfaceKHR)(VkInstance instance, സ്ഥിരം VkAndroidSurfaceCreateInfoKHR* pCreateInfo, സ്ഥിരം VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateAndroidSurfaceKHR(
    VkInstance                                  instance,
    സ്ഥിരം VkAndroidSurfaceCreateInfoKHR*        pCreateInfo,
    സ്ഥിരം VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#endif


// VK_ANDROID_external_memory_android_hardware_buffer is a preprocessor guard. Do not pass it to API calls.
#define VK_ANDROID_external_memory_android_hardware_buffer 1

ഘടന AHardwareBuffer;

#define VK_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_SPEC_VERSION 5
#define VK_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_EXTENSION_NAME "VK_ANDROID_external_memory_android_hardware_buffer"

തരനിർവചനം ഘടന VkAndroidHardwareBufferUsageANDROID {
    VkStructureType    sType;
    ശൂന്യം*              pNext;
    uint64_t           androidHardwareBufferUsage;
} VkAndroidHardwareBufferUsageANDROID;

തരനിർവചനം ഘടന VkAndroidHardwareBufferPropertiesANDROID {
    VkStructureType    sType;
    ശൂന്യം*              pNext;
    VkDeviceSize       allocationSize;
    uint32_t           memoryTypeBits;
} VkAndroidHardwareBufferPropertiesANDROID;

തരനിർവചനം ഘടന VkAndroidHardwareBufferFormatPropertiesANDROID {
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
} VkAndroidHardwareBufferFormatPropertiesANDROID;

തരനിർവചനം ഘടന VkImportAndroidHardwareBufferInfoANDROID {
    VkStructureType            sType;
    സ്ഥിരം ശൂന്യം*                pNext;
    ഘടന AHardwareBuffer*    buffer;
} VkImportAndroidHardwareBufferInfoANDROID;

തരനിർവചനം ഘടന VkMemoryGetAndroidHardwareBufferInfoANDROID {
    VkStructureType    sType;
    സ്ഥിരം ശൂന്യം*        pNext;
    VkDeviceMemory     memory;
} VkMemoryGetAndroidHardwareBufferInfoANDROID;

തരനിർവചനം ഘടന VkExternalFormatANDROID {
    VkStructureType    sType;
    ശൂന്യം*              pNext;
    uint64_t           externalFormat;
} VkExternalFormatANDROID;

തരനിർവചനം ഘടന VkAndroidHardwareBufferFormatProperties2ANDROID {
    VkStructureType                  sType;
    ശൂന്യം*                            pNext;
    VkFormat                         format;
    uint64_t                         externalFormat;
    VkFormatFeatureFlags2            formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggestedXChromaOffset;
    VkChromaLocation                 suggestedYChromaOffset;
} VkAndroidHardwareBufferFormatProperties2ANDROID;


തരനിർവചനം VkResult (VKAPI_PTR *PFN_vkGetAndroidHardwareBufferPropertiesANDROID)(VkDevice device, സ്ഥിരം ഘടന AHardwareBuffer* buffer, VkAndroidHardwareBufferPropertiesANDROID* pProperties);
തരനിർവചനം VkResult (VKAPI_PTR *PFN_vkGetMemoryAndroidHardwareBufferANDROID)(VkDevice device, സ്ഥിരം VkMemoryGetAndroidHardwareBufferInfoANDROID* pInfo, ഘടന AHardwareBuffer** pBuffer);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetAndroidHardwareBufferPropertiesANDROID(
    VkDevice                                    device,
    സ്ഥിരം ഘടന AHardwareBuffer*               buffer,
    VkAndroidHardwareBufferPropertiesANDROID*   pProperties);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryAndroidHardwareBufferANDROID(
    VkDevice                                    device,
    സ്ഥിരം VkMemoryGetAndroidHardwareBufferInfoANDROID* pInfo,
    ഘടന AHardwareBuffer**                    pBuffer);
#endif
#endif


// VK_ANDROID_external_format_resolve is a preprocessor guard. Do not pass it to API calls.
#define VK_ANDROID_external_format_resolve 1

#define VK_ANDROID_EXTERNAL_FORMAT_RESOLVE_SPEC_VERSION 1
#define VK_ANDROID_EXTERNAL_FORMAT_RESOLVE_EXTENSION_NAME "VK_ANDROID_external_format_resolve"

തരനിർവചനം ഘടന VkPhysicalDeviceExternalFormatResolveFeaturesANDROID {
    VkStructureType    sType;
    ശൂന്യം*              pNext;
    VkBool32           externalFormatResolve;
} VkPhysicalDeviceExternalFormatResolveFeaturesANDROID;

തരനിർവചനം ഘടന VkPhysicalDeviceExternalFormatResolvePropertiesANDROID {
    VkStructureType     sType;
    ശൂന്യം*               pNext;
    VkBool32            nullColorAttachmentWithExternalFormatResolve;
    VkChromaLocation    externalFormatResolveChromaOffsetX;
    VkChromaLocation    externalFormatResolveChromaOffsetY;
} VkPhysicalDeviceExternalFormatResolvePropertiesANDROID;

തരനിർവചനം ഘടന VkAndroidHardwareBufferFormatResolvePropertiesANDROID {
    VkStructureType    sType;
    ശൂന്യം*              pNext;
    VkFormat           colorAttachmentFormat;
} VkAndroidHardwareBufferFormatResolvePropertiesANDROID;


#ifdef __cplusplus
}
#endif

#endif
