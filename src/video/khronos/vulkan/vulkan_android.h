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
ಬಾಹ್ಯ "C" {
#endif



// VK_KHR_android_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_android_surface 1

ಸಂರಚನಾ ANativeWindow;

#define VK_KHR_ANDROID_SURFACE_SPEC_VERSION 6
#define VK_KHR_ANDROID_SURFACE_EXTENSION_NAME "VK_KHR_android_surface"

ಪ್ರಕಾರನಿರ್ದೇಶ VkFlags VkAndroidSurfaceCreateFlagsKHR;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkAndroidSurfaceCreateInfoKHR {
    VkStructureType                   sType;
    ಧ್ರುವ ಶೂನ್ಯ*                       pNext;
    VkAndroidSurfaceCreateFlagsKHR    flags;
    ಸಂರಚನಾ ANativeWindow*             window;
} VkAndroidSurfaceCreateInfoKHR;


ಪ್ರಕಾರನಿರ್ದೇಶ VkResult (VKAPI_PTR *PFN_vkCreateAndroidSurfaceKHR)(VkInstance instance, ಧ್ರುವ VkAndroidSurfaceCreateInfoKHR* pCreateInfo, ಧ್ರುವ VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateAndroidSurfaceKHR(
    VkInstance                                  instance,
    ಧ್ರುವ VkAndroidSurfaceCreateInfoKHR*        pCreateInfo,
    ಧ್ರುವ VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#endif


// VK_ANDROID_external_memory_android_hardware_buffer is a preprocessor guard. Do not pass it to API calls.
#define VK_ANDROID_external_memory_android_hardware_buffer 1

ಸಂರಚನಾ AHardwareBuffer;

#define VK_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_SPEC_VERSION 5
#define VK_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_EXTENSION_NAME "VK_ANDROID_external_memory_android_hardware_buffer"

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkAndroidHardwareBufferUsageANDROID {
    VkStructureType    sType;
    ಶೂನ್ಯ*              pNext;
    uint64_t           androidHardwareBufferUsage;
} VkAndroidHardwareBufferUsageANDROID;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkAndroidHardwareBufferPropertiesANDROID {
    VkStructureType    sType;
    ಶೂನ್ಯ*              pNext;
    VkDeviceSize       allocationSize;
    uint32_t           memoryTypeBits;
} VkAndroidHardwareBufferPropertiesANDROID;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkAndroidHardwareBufferFormatPropertiesANDROID {
    VkStructureType                  sType;
    ಶೂನ್ಯ*                            pNext;
    VkFormat                         format;
    uint64_t                         externalFormat;
    VkFormatFeatureFlags             formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggestedXChromaOffset;
    VkChromaLocation                 suggestedYChromaOffset;
} VkAndroidHardwareBufferFormatPropertiesANDROID;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkImportAndroidHardwareBufferInfoANDROID {
    VkStructureType            sType;
    ಧ್ರುವ ಶೂನ್ಯ*                pNext;
    ಸಂರಚನಾ AHardwareBuffer*    buffer;
} VkImportAndroidHardwareBufferInfoANDROID;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkMemoryGetAndroidHardwareBufferInfoANDROID {
    VkStructureType    sType;
    ಧ್ರುವ ಶೂನ್ಯ*        pNext;
    VkDeviceMemory     memory;
} VkMemoryGetAndroidHardwareBufferInfoANDROID;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkExternalFormatANDROID {
    VkStructureType    sType;
    ಶೂನ್ಯ*              pNext;
    uint64_t           externalFormat;
} VkExternalFormatANDROID;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkAndroidHardwareBufferFormatProperties2ANDROID {
    VkStructureType                  sType;
    ಶೂನ್ಯ*                            pNext;
    VkFormat                         format;
    uint64_t                         externalFormat;
    VkFormatFeatureFlags2            formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggestedXChromaOffset;
    VkChromaLocation                 suggestedYChromaOffset;
} VkAndroidHardwareBufferFormatProperties2ANDROID;


ಪ್ರಕಾರನಿರ್ದೇಶ VkResult (VKAPI_PTR *PFN_vkGetAndroidHardwareBufferPropertiesANDROID)(VkDevice device, ಧ್ರುವ ಸಂರಚನಾ AHardwareBuffer* buffer, VkAndroidHardwareBufferPropertiesANDROID* pProperties);
ಪ್ರಕಾರನಿರ್ದೇಶ VkResult (VKAPI_PTR *PFN_vkGetMemoryAndroidHardwareBufferANDROID)(VkDevice device, ಧ್ರುವ VkMemoryGetAndroidHardwareBufferInfoANDROID* pInfo, ಸಂರಚನಾ AHardwareBuffer** pBuffer);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetAndroidHardwareBufferPropertiesANDROID(
    VkDevice                                    device,
    ಧ್ರುವ ಸಂರಚನಾ AHardwareBuffer*               buffer,
    VkAndroidHardwareBufferPropertiesANDROID*   pProperties);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryAndroidHardwareBufferANDROID(
    VkDevice                                    device,
    ಧ್ರುವ VkMemoryGetAndroidHardwareBufferInfoANDROID* pInfo,
    ಸಂರಚನಾ AHardwareBuffer**                    pBuffer);
#endif
#endif


// VK_ANDROID_external_format_resolve is a preprocessor guard. Do not pass it to API calls.
#define VK_ANDROID_external_format_resolve 1

#define VK_ANDROID_EXTERNAL_FORMAT_RESOLVE_SPEC_VERSION 1
#define VK_ANDROID_EXTERNAL_FORMAT_RESOLVE_EXTENSION_NAME "VK_ANDROID_external_format_resolve"

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkPhysicalDeviceExternalFormatResolveFeaturesANDROID {
    VkStructureType    sType;
    ಶೂನ್ಯ*              pNext;
    VkBool32           externalFormatResolve;
} VkPhysicalDeviceExternalFormatResolveFeaturesANDROID;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkPhysicalDeviceExternalFormatResolvePropertiesANDROID {
    VkStructureType     sType;
    ಶೂನ್ಯ*               pNext;
    VkBool32            nullColorAttachmentWithExternalFormatResolve;
    VkChromaLocation    externalFormatResolveChromaOffsetX;
    VkChromaLocation    externalFormatResolveChromaOffsetY;
} VkPhysicalDeviceExternalFormatResolvePropertiesANDROID;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkAndroidHardwareBufferFormatResolvePropertiesANDROID {
    VkStructureType    sType;
    ಶೂನ್ಯ*              pNext;
    VkFormat           colorAttachmentFormat;
} VkAndroidHardwareBufferFormatResolvePropertiesANDROID;


#ifdef __cplusplus
}
#endif

#endif
