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
بیرونی "C" {
#endif



// VK_KHR_android_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_android_surface 1

ساختار ANativeWindow;

#define VK_KHR_ANDROID_SURFACE_SPEC_VERSION 6
#define VK_KHR_ANDROID_SURFACE_EXTENSION_NAME "VK_KHR_android_surface"

تعریفنوع VkFlags VkAndroidSurfaceCreateFlagsKHR;

تعریفنوع ساختار VkAndroidSurfaceCreateInfoKHR {
    VkStructureType                   sType;
    ثابت تهی*                       pNext;
    VkAndroidSurfaceCreateFlagsKHR    flags;
    ساختار ANativeWindow*             window;
} VkAndroidSurfaceCreateInfoKHR;


تعریفنوع VkResult (VKAPI_PTR *PFN_vkCreateAndroidSurfaceKHR)(VkInstance instance, ثابت VkAndroidSurfaceCreateInfoKHR* pCreateInfo, ثابت VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateAndroidSurfaceKHR(
    VkInstance                                  instance,
    ثابت VkAndroidSurfaceCreateInfoKHR*        pCreateInfo,
    ثابت VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#endif


// VK_ANDROID_external_memory_android_hardware_buffer is a preprocessor guard. Do not pass it to API calls.
#define VK_ANDROID_external_memory_android_hardware_buffer 1

ساختار AHardwareBuffer;

#define VK_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_SPEC_VERSION 5
#define VK_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_EXTENSION_NAME "VK_ANDROID_external_memory_android_hardware_buffer"

تعریفنوع ساختار VkAndroidHardwareBufferUsageANDROID {
    VkStructureType    sType;
    تهی*              pNext;
    uint64_t           androidHardwareBufferUsage;
} VkAndroidHardwareBufferUsageANDROID;

تعریفنوع ساختار VkAndroidHardwareBufferPropertiesANDROID {
    VkStructureType    sType;
    تهی*              pNext;
    VkDeviceSize       allocationSize;
    uint32_t           memoryTypeBits;
} VkAndroidHardwareBufferPropertiesANDROID;

تعریفنوع ساختار VkAndroidHardwareBufferFormatPropertiesANDROID {
    VkStructureType                  sType;
    تهی*                            pNext;
    VkFormat                         format;
    uint64_t                         externalFormat;
    VkFormatFeatureFlags             formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggestedXChromaOffset;
    VkChromaLocation                 suggestedYChromaOffset;
} VkAndroidHardwareBufferFormatPropertiesANDROID;

تعریفنوع ساختار VkImportAndroidHardwareBufferInfoANDROID {
    VkStructureType            sType;
    ثابت تهی*                pNext;
    ساختار AHardwareBuffer*    buffer;
} VkImportAndroidHardwareBufferInfoANDROID;

تعریفنوع ساختار VkMemoryGetAndroidHardwareBufferInfoANDROID {
    VkStructureType    sType;
    ثابت تهی*        pNext;
    VkDeviceMemory     memory;
} VkMemoryGetAndroidHardwareBufferInfoANDROID;

تعریفنوع ساختار VkExternalFormatANDROID {
    VkStructureType    sType;
    تهی*              pNext;
    uint64_t           externalFormat;
} VkExternalFormatANDROID;

تعریفنوع ساختار VkAndroidHardwareBufferFormatProperties2ANDROID {
    VkStructureType                  sType;
    تهی*                            pNext;
    VkFormat                         format;
    uint64_t                         externalFormat;
    VkFormatFeatureFlags2            formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggestedXChromaOffset;
    VkChromaLocation                 suggestedYChromaOffset;
} VkAndroidHardwareBufferFormatProperties2ANDROID;


تعریفنوع VkResult (VKAPI_PTR *PFN_vkGetAndroidHardwareBufferPropertiesANDROID)(VkDevice device, ثابت ساختار AHardwareBuffer* buffer, VkAndroidHardwareBufferPropertiesANDROID* pProperties);
تعریفنوع VkResult (VKAPI_PTR *PFN_vkGetMemoryAndroidHardwareBufferANDROID)(VkDevice device, ثابت VkMemoryGetAndroidHardwareBufferInfoANDROID* pInfo, ساختار AHardwareBuffer** pBuffer);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetAndroidHardwareBufferPropertiesANDROID(
    VkDevice                                    device,
    ثابت ساختار AHardwareBuffer*               buffer,
    VkAndroidHardwareBufferPropertiesANDROID*   pProperties);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryAndroidHardwareBufferANDROID(
    VkDevice                                    device,
    ثابت VkMemoryGetAndroidHardwareBufferInfoANDROID* pInfo,
    ساختار AHardwareBuffer**                    pBuffer);
#endif
#endif


// VK_ANDROID_external_format_resolve is a preprocessor guard. Do not pass it to API calls.
#define VK_ANDROID_external_format_resolve 1

#define VK_ANDROID_EXTERNAL_FORMAT_RESOLVE_SPEC_VERSION 1
#define VK_ANDROID_EXTERNAL_FORMAT_RESOLVE_EXTENSION_NAME "VK_ANDROID_external_format_resolve"

تعریفنوع ساختار VkPhysicalDeviceExternalFormatResolveFeaturesANDROID {
    VkStructureType    sType;
    تهی*              pNext;
    VkBool32           externalFormatResolve;
} VkPhysicalDeviceExternalFormatResolveFeaturesANDROID;

تعریفنوع ساختار VkPhysicalDeviceExternalFormatResolvePropertiesANDROID {
    VkStructureType     sType;
    تهی*               pNext;
    VkBool32            nullColorAttachmentWithExternalFormatResolve;
    VkChromaLocation    externalFormatResolveChromaOffsetX;
    VkChromaLocation    externalFormatResolveChromaOffsetY;
} VkPhysicalDeviceExternalFormatResolvePropertiesANDROID;

تعریفنوع ساختار VkAndroidHardwareBufferFormatResolvePropertiesANDROID {
    VkStructureType    sType;
    تهی*              pNext;
    VkFormat           colorAttachmentFormat;
} VkAndroidHardwareBufferFormatResolvePropertiesANDROID;


#ifdef __cplusplus
}
#endif

#endif
