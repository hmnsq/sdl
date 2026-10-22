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
ବାହ୍ୟ "C" {
#endif



// VK_KHR_android_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_android_surface 1

ସଂରଚନା ANativeWindow;

#define VK_KHR_ANDROID_SURFACE_SPEC_VERSION 6
#define VK_KHR_ANDROID_SURFACE_EXTENSION_NAME "VK_KHR_android_surface"

ପ୍ରକାରବ୍ୟାଖ୍ୟା VkFlags VkAndroidSurfaceCreateFlagsKHR;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkAndroidSurfaceCreateInfoKHR {
    VkStructureType                   sType;
    ଅଚଳ ଶୂନ୍ୟ*                       pNext;
    VkAndroidSurfaceCreateFlagsKHR    flags;
    ସଂରଚନା ANativeWindow*             window;
} VkAndroidSurfaceCreateInfoKHR;


ପ୍ରକାରବ୍ୟାଖ୍ୟା VkResult (VKAPI_PTR *PFN_vkCreateAndroidSurfaceKHR)(VkInstance instance, ଅଚଳ VkAndroidSurfaceCreateInfoKHR* pCreateInfo, ଅଚଳ VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateAndroidSurfaceKHR(
    VkInstance                                  instance,
    ଅଚଳ VkAndroidSurfaceCreateInfoKHR*        pCreateInfo,
    ଅଚଳ VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#endif


// VK_ANDROID_external_memory_android_hardware_buffer is a preprocessor guard. Do not pass it to API calls.
#define VK_ANDROID_external_memory_android_hardware_buffer 1

ସଂରଚନା AHardwareBuffer;

#define VK_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_SPEC_VERSION 5
#define VK_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_EXTENSION_NAME "VK_ANDROID_external_memory_android_hardware_buffer"

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkAndroidHardwareBufferUsageANDROID {
    VkStructureType    sType;
    ଶୂନ୍ୟ*              pNext;
    uint64_t           androidHardwareBufferUsage;
} VkAndroidHardwareBufferUsageANDROID;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkAndroidHardwareBufferPropertiesANDROID {
    VkStructureType    sType;
    ଶୂନ୍ୟ*              pNext;
    VkDeviceSize       allocationSize;
    uint32_t           memoryTypeBits;
} VkAndroidHardwareBufferPropertiesANDROID;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkAndroidHardwareBufferFormatPropertiesANDROID {
    VkStructureType                  sType;
    ଶୂନ୍ୟ*                            pNext;
    VkFormat                         format;
    uint64_t                         externalFormat;
    VkFormatFeatureFlags             formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggestedXChromaOffset;
    VkChromaLocation                 suggestedYChromaOffset;
} VkAndroidHardwareBufferFormatPropertiesANDROID;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkImportAndroidHardwareBufferInfoANDROID {
    VkStructureType            sType;
    ଅଚଳ ଶୂନ୍ୟ*                pNext;
    ସଂରଚନା AHardwareBuffer*    buffer;
} VkImportAndroidHardwareBufferInfoANDROID;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkMemoryGetAndroidHardwareBufferInfoANDROID {
    VkStructureType    sType;
    ଅଚଳ ଶୂନ୍ୟ*        pNext;
    VkDeviceMemory     memory;
} VkMemoryGetAndroidHardwareBufferInfoANDROID;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkExternalFormatANDROID {
    VkStructureType    sType;
    ଶୂନ୍ୟ*              pNext;
    uint64_t           externalFormat;
} VkExternalFormatANDROID;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkAndroidHardwareBufferFormatProperties2ANDROID {
    VkStructureType                  sType;
    ଶୂନ୍ୟ*                            pNext;
    VkFormat                         format;
    uint64_t                         externalFormat;
    VkFormatFeatureFlags2            formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggestedXChromaOffset;
    VkChromaLocation                 suggestedYChromaOffset;
} VkAndroidHardwareBufferFormatProperties2ANDROID;


ପ୍ରକାରବ୍ୟାଖ୍ୟା VkResult (VKAPI_PTR *PFN_vkGetAndroidHardwareBufferPropertiesANDROID)(VkDevice device, ଅଚଳ ସଂରଚନା AHardwareBuffer* buffer, VkAndroidHardwareBufferPropertiesANDROID* pProperties);
ପ୍ରକାରବ୍ୟାଖ୍ୟା VkResult (VKAPI_PTR *PFN_vkGetMemoryAndroidHardwareBufferANDROID)(VkDevice device, ଅଚଳ VkMemoryGetAndroidHardwareBufferInfoANDROID* pInfo, ସଂରଚନା AHardwareBuffer** pBuffer);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetAndroidHardwareBufferPropertiesANDROID(
    VkDevice                                    device,
    ଅଚଳ ସଂରଚନା AHardwareBuffer*               buffer,
    VkAndroidHardwareBufferPropertiesANDROID*   pProperties);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryAndroidHardwareBufferANDROID(
    VkDevice                                    device,
    ଅଚଳ VkMemoryGetAndroidHardwareBufferInfoANDROID* pInfo,
    ସଂରଚନା AHardwareBuffer**                    pBuffer);
#endif
#endif


// VK_ANDROID_external_format_resolve is a preprocessor guard. Do not pass it to API calls.
#define VK_ANDROID_external_format_resolve 1

#define VK_ANDROID_EXTERNAL_FORMAT_RESOLVE_SPEC_VERSION 1
#define VK_ANDROID_EXTERNAL_FORMAT_RESOLVE_EXTENSION_NAME "VK_ANDROID_external_format_resolve"

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkPhysicalDeviceExternalFormatResolveFeaturesANDROID {
    VkStructureType    sType;
    ଶୂନ୍ୟ*              pNext;
    VkBool32           externalFormatResolve;
} VkPhysicalDeviceExternalFormatResolveFeaturesANDROID;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkPhysicalDeviceExternalFormatResolvePropertiesANDROID {
    VkStructureType     sType;
    ଶୂନ୍ୟ*               pNext;
    VkBool32            nullColorAttachmentWithExternalFormatResolve;
    VkChromaLocation    externalFormatResolveChromaOffsetX;
    VkChromaLocation    externalFormatResolveChromaOffsetY;
} VkPhysicalDeviceExternalFormatResolvePropertiesANDROID;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkAndroidHardwareBufferFormatResolvePropertiesANDROID {
    VkStructureType    sType;
    ଶୂନ୍ୟ*              pNext;
    VkFormat           colorAttachmentFormat;
} VkAndroidHardwareBufferFormatResolvePropertiesANDROID;


#ifdef __cplusplus
}
#endif

#endif
