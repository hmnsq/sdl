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
خارجي "C" {
#endif



// VK_KHR_android_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_android_surface 1

بنية ANativeWindow;

#define VK_KHR_ANDROID_SURFACE_SPEC_VERSION 6
#define VK_KHR_ANDROID_SURFACE_EXTENSION_NAME "VK_KHR_android_surface"

تعريفنوع VkFlags VkAndroidSurfaceCreateFlagsKHR;

تعريفنوع بنية VkAndroidSurfaceCreateInfoKHR {
    VkStructureType                   sType;
    ثابت فراغ*                       pNext;
    VkAndroidSurfaceCreateFlagsKHR    flags;
    بنية ANativeWindow*             window;
} VkAndroidSurfaceCreateInfoKHR;


تعريفنوع VkResult (VKAPI_PTR *PFN_vkCreateAndroidSurfaceKHR)(VkInstance instance, ثابت VkAndroidSurfaceCreateInfoKHR* pCreateInfo, ثابت VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

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

بنية AHardwareBuffer;

#define VK_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_SPEC_VERSION 5
#define VK_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_EXTENSION_NAME "VK_ANDROID_external_memory_android_hardware_buffer"

تعريفنوع بنية VkAndroidHardwareBufferUsageANDROID {
    VkStructureType    sType;
    فراغ*              pNext;
    uint64_t           androidHardwareBufferUsage;
} VkAndroidHardwareBufferUsageANDROID;

تعريفنوع بنية VkAndroidHardwareBufferPropertiesANDROID {
    VkStructureType    sType;
    فراغ*              pNext;
    VkDeviceSize       allocationSize;
    uint32_t           memoryTypeBits;
} VkAndroidHardwareBufferPropertiesANDROID;

تعريفنوع بنية VkAndroidHardwareBufferFormatPropertiesANDROID {
    VkStructureType                  sType;
    فراغ*                            pNext;
    VkFormat                         format;
    uint64_t                         externalFormat;
    VkFormatFeatureFlags             formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggestedXChromaOffset;
    VkChromaLocation                 suggestedYChromaOffset;
} VkAndroidHardwareBufferFormatPropertiesANDROID;

تعريفنوع بنية VkImportAndroidHardwareBufferInfoANDROID {
    VkStructureType            sType;
    ثابت فراغ*                pNext;
    بنية AHardwareBuffer*    buffer;
} VkImportAndroidHardwareBufferInfoANDROID;

تعريفنوع بنية VkMemoryGetAndroidHardwareBufferInfoANDROID {
    VkStructureType    sType;
    ثابت فراغ*        pNext;
    VkDeviceMemory     memory;
} VkMemoryGetAndroidHardwareBufferInfoANDROID;

تعريفنوع بنية VkExternalFormatANDROID {
    VkStructureType    sType;
    فراغ*              pNext;
    uint64_t           externalFormat;
} VkExternalFormatANDROID;

تعريفنوع بنية VkAndroidHardwareBufferFormatProperties2ANDROID {
    VkStructureType                  sType;
    فراغ*                            pNext;
    VkFormat                         format;
    uint64_t                         externalFormat;
    VkFormatFeatureFlags2            formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggestedXChromaOffset;
    VkChromaLocation                 suggestedYChromaOffset;
} VkAndroidHardwareBufferFormatProperties2ANDROID;


تعريفنوع VkResult (VKAPI_PTR *PFN_vkGetAndroidHardwareBufferPropertiesANDROID)(VkDevice device, ثابت بنية AHardwareBuffer* buffer, VkAndroidHardwareBufferPropertiesANDROID* pProperties);
تعريفنوع VkResult (VKAPI_PTR *PFN_vkGetMemoryAndroidHardwareBufferANDROID)(VkDevice device, ثابت VkMemoryGetAndroidHardwareBufferInfoANDROID* pInfo, بنية AHardwareBuffer** pBuffer);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetAndroidHardwareBufferPropertiesANDROID(
    VkDevice                                    device,
    ثابت بنية AHardwareBuffer*               buffer,
    VkAndroidHardwareBufferPropertiesANDROID*   pProperties);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryAndroidHardwareBufferANDROID(
    VkDevice                                    device,
    ثابت VkMemoryGetAndroidHardwareBufferInfoANDROID* pInfo,
    بنية AHardwareBuffer**                    pBuffer);
#endif
#endif


// VK_ANDROID_external_format_resolve is a preprocessor guard. Do not pass it to API calls.
#define VK_ANDROID_external_format_resolve 1

#define VK_ANDROID_EXTERNAL_FORMAT_RESOLVE_SPEC_VERSION 1
#define VK_ANDROID_EXTERNAL_FORMAT_RESOLVE_EXTENSION_NAME "VK_ANDROID_external_format_resolve"

تعريفنوع بنية VkPhysicalDeviceExternalFormatResolveFeaturesANDROID {
    VkStructureType    sType;
    فراغ*              pNext;
    VkBool32           externalFormatResolve;
} VkPhysicalDeviceExternalFormatResolveFeaturesANDROID;

تعريفنوع بنية VkPhysicalDeviceExternalFormatResolvePropertiesANDROID {
    VkStructureType     sType;
    فراغ*               pNext;
    VkBool32            nullColorAttachmentWithExternalFormatResolve;
    VkChromaLocation    externalFormatResolveChromaOffsetX;
    VkChromaLocation    externalFormatResolveChromaOffsetY;
} VkPhysicalDeviceExternalFormatResolvePropertiesANDROID;

تعريفنوع بنية VkAndroidHardwareBufferFormatResolvePropertiesANDROID {
    VkStructureType    sType;
    فراغ*              pNext;
    VkFormat           colorAttachmentFormat;
} VkAndroidHardwareBufferFormatResolvePropertiesANDROID;


#ifdef __cplusplus
}
#endif

#endif
