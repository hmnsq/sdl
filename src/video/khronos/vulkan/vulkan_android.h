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
বাহ্য "C" {
#endif



// VK_KHR_android_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_android_surface 1

সংরচনা ANativeWindow;

#define VK_KHR_ANDROID_SURFACE_SPEC_VERSION 6
#define VK_KHR_ANDROID_SURFACE_EXTENSION_NAME "VK_KHR_android_surface"

প্রকারনির্দেশ VkFlags VkAndroidSurfaceCreateFlagsKHR;

প্রকারনির্দেশ সংরচনা VkAndroidSurfaceCreateInfoKHR {
    VkStructureType                   sType;
    ধ্রুৱ শূন্য*                       pNext;
    VkAndroidSurfaceCreateFlagsKHR    flags;
    সংরচনা ANativeWindow*             window;
} VkAndroidSurfaceCreateInfoKHR;


প্রকারনির্দেশ VkResult (VKAPI_PTR *PFN_vkCreateAndroidSurfaceKHR)(VkInstance instance, ধ্রুৱ VkAndroidSurfaceCreateInfoKHR* pCreateInfo, ধ্রুৱ VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateAndroidSurfaceKHR(
    VkInstance                                  instance,
    ধ্রুৱ VkAndroidSurfaceCreateInfoKHR*        pCreateInfo,
    ধ্রুৱ VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#endif


// VK_ANDROID_external_memory_android_hardware_buffer is a preprocessor guard. Do not pass it to API calls.
#define VK_ANDROID_external_memory_android_hardware_buffer 1

সংরচনা AHardwareBuffer;

#define VK_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_SPEC_VERSION 5
#define VK_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_EXTENSION_NAME "VK_ANDROID_external_memory_android_hardware_buffer"

প্রকারনির্দেশ সংরচনা VkAndroidHardwareBufferUsageANDROID {
    VkStructureType    sType;
    শূন্য*              pNext;
    uint64_t           androidHardwareBufferUsage;
} VkAndroidHardwareBufferUsageANDROID;

প্রকারনির্দেশ সংরচনা VkAndroidHardwareBufferPropertiesANDROID {
    VkStructureType    sType;
    শূন্য*              pNext;
    VkDeviceSize       allocationSize;
    uint32_t           memoryTypeBits;
} VkAndroidHardwareBufferPropertiesANDROID;

প্রকারনির্দেশ সংরচনা VkAndroidHardwareBufferFormatPropertiesANDROID {
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
} VkAndroidHardwareBufferFormatPropertiesANDROID;

প্রকারনির্দেশ সংরচনা VkImportAndroidHardwareBufferInfoANDROID {
    VkStructureType            sType;
    ধ্রুৱ শূন্য*                pNext;
    সংরচনা AHardwareBuffer*    buffer;
} VkImportAndroidHardwareBufferInfoANDROID;

প্রকারনির্দেশ সংরচনা VkMemoryGetAndroidHardwareBufferInfoANDROID {
    VkStructureType    sType;
    ধ্রুৱ শূন্য*        pNext;
    VkDeviceMemory     memory;
} VkMemoryGetAndroidHardwareBufferInfoANDROID;

প্রকারনির্দেশ সংরচনা VkExternalFormatANDROID {
    VkStructureType    sType;
    শূন্য*              pNext;
    uint64_t           externalFormat;
} VkExternalFormatANDROID;

প্রকারনির্দেশ সংরচনা VkAndroidHardwareBufferFormatProperties2ANDROID {
    VkStructureType                  sType;
    শূন্য*                            pNext;
    VkFormat                         format;
    uint64_t                         externalFormat;
    VkFormatFeatureFlags2            formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggestedXChromaOffset;
    VkChromaLocation                 suggestedYChromaOffset;
} VkAndroidHardwareBufferFormatProperties2ANDROID;


প্রকারনির্দেশ VkResult (VKAPI_PTR *PFN_vkGetAndroidHardwareBufferPropertiesANDROID)(VkDevice device, ধ্রুৱ সংরচনা AHardwareBuffer* buffer, VkAndroidHardwareBufferPropertiesANDROID* pProperties);
প্রকারনির্দেশ VkResult (VKAPI_PTR *PFN_vkGetMemoryAndroidHardwareBufferANDROID)(VkDevice device, ধ্রুৱ VkMemoryGetAndroidHardwareBufferInfoANDROID* pInfo, সংরচনা AHardwareBuffer** pBuffer);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetAndroidHardwareBufferPropertiesANDROID(
    VkDevice                                    device,
    ধ্রুৱ সংরচনা AHardwareBuffer*               buffer,
    VkAndroidHardwareBufferPropertiesANDROID*   pProperties);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryAndroidHardwareBufferANDROID(
    VkDevice                                    device,
    ধ্রুৱ VkMemoryGetAndroidHardwareBufferInfoANDROID* pInfo,
    সংরচনা AHardwareBuffer**                    pBuffer);
#endif
#endif


// VK_ANDROID_external_format_resolve is a preprocessor guard. Do not pass it to API calls.
#define VK_ANDROID_external_format_resolve 1

#define VK_ANDROID_EXTERNAL_FORMAT_RESOLVE_SPEC_VERSION 1
#define VK_ANDROID_EXTERNAL_FORMAT_RESOLVE_EXTENSION_NAME "VK_ANDROID_external_format_resolve"

প্রকারনির্দেশ সংরচনা VkPhysicalDeviceExternalFormatResolveFeaturesANDROID {
    VkStructureType    sType;
    শূন্য*              pNext;
    VkBool32           externalFormatResolve;
} VkPhysicalDeviceExternalFormatResolveFeaturesANDROID;

প্রকারনির্দেশ সংরচনা VkPhysicalDeviceExternalFormatResolvePropertiesANDROID {
    VkStructureType     sType;
    শূন্য*               pNext;
    VkBool32            nullColorAttachmentWithExternalFormatResolve;
    VkChromaLocation    externalFormatResolveChromaOffsetX;
    VkChromaLocation    externalFormatResolveChromaOffsetY;
} VkPhysicalDeviceExternalFormatResolvePropertiesANDROID;

প্রকারনির্দেশ সংরচনা VkAndroidHardwareBufferFormatResolvePropertiesANDROID {
    VkStructureType    sType;
    শূন্য*              pNext;
    VkFormat           colorAttachmentFormat;
} VkAndroidHardwareBufferFormatResolvePropertiesANDROID;


#ifdef __cplusplus
}
#endif

#endif
