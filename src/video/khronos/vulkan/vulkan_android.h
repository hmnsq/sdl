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
बाह्य "C" {
#endif



// VK_KHR_android_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_android_surface 1

संरचना ANativeWindow;

#define VK_KHR_ANDROID_SURFACE_SPEC_VERSION 6
#define VK_KHR_ANDROID_SURFACE_EXTENSION_NAME "VK_KHR_android_surface"

प्रकारव्याख्या VkFlags VkAndroidSurfaceCreateFlagsKHR;

प्रकारव्याख्या संरचना VkAndroidSurfaceCreateInfoKHR {
    VkStructureType                   sType;
    स्थिरांक शून्य*                       pNext;
    VkAndroidSurfaceCreateFlagsKHR    flags;
    संरचना ANativeWindow*             window;
} VkAndroidSurfaceCreateInfoKHR;


प्रकारव्याख्या VkResult (VKAPI_PTR *PFN_vkCreateAndroidSurfaceKHR)(VkInstance instance, स्थिरांक VkAndroidSurfaceCreateInfoKHR* pCreateInfo, स्थिरांक VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateAndroidSurfaceKHR(
    VkInstance                                  instance,
    स्थिरांक VkAndroidSurfaceCreateInfoKHR*        pCreateInfo,
    स्थिरांक VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#endif


// VK_ANDROID_external_memory_android_hardware_buffer is a preprocessor guard. Do not pass it to API calls.
#define VK_ANDROID_external_memory_android_hardware_buffer 1

संरचना AHardwareBuffer;

#define VK_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_SPEC_VERSION 5
#define VK_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_EXTENSION_NAME "VK_ANDROID_external_memory_android_hardware_buffer"

प्रकारव्याख्या संरचना VkAndroidHardwareBufferUsageANDROID {
    VkStructureType    sType;
    शून्य*              pNext;
    uint64_t           androidHardwareBufferUsage;
} VkAndroidHardwareBufferUsageANDROID;

प्रकारव्याख्या संरचना VkAndroidHardwareBufferPropertiesANDROID {
    VkStructureType    sType;
    शून्य*              pNext;
    VkDeviceSize       allocationSize;
    uint32_t           memoryTypeBits;
} VkAndroidHardwareBufferPropertiesANDROID;

प्रकारव्याख्या संरचना VkAndroidHardwareBufferFormatPropertiesANDROID {
    VkStructureType                  sType;
    शून्य*                            pNext;
    VkFormat                         format;
    uint64_t                         externalFormat;
    VkFormatFeatureFlags             formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggestedXChromaOffset;
    VkChromaLocation                 suggestedYChromaOffset;
} VkAndroidHardwareBufferFormatPropertiesANDROID;

प्रकारव्याख्या संरचना VkImportAndroidHardwareBufferInfoANDROID {
    VkStructureType            sType;
    स्थिरांक शून्य*                pNext;
    संरचना AHardwareBuffer*    buffer;
} VkImportAndroidHardwareBufferInfoANDROID;

प्रकारव्याख्या संरचना VkMemoryGetAndroidHardwareBufferInfoANDROID {
    VkStructureType    sType;
    स्थिरांक शून्य*        pNext;
    VkDeviceMemory     memory;
} VkMemoryGetAndroidHardwareBufferInfoANDROID;

प्रकारव्याख्या संरचना VkExternalFormatANDROID {
    VkStructureType    sType;
    शून्य*              pNext;
    uint64_t           externalFormat;
} VkExternalFormatANDROID;

प्रकारव्याख्या संरचना VkAndroidHardwareBufferFormatProperties2ANDROID {
    VkStructureType                  sType;
    शून्य*                            pNext;
    VkFormat                         format;
    uint64_t                         externalFormat;
    VkFormatFeatureFlags2            formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggestedXChromaOffset;
    VkChromaLocation                 suggestedYChromaOffset;
} VkAndroidHardwareBufferFormatProperties2ANDROID;


प्रकारव्याख्या VkResult (VKAPI_PTR *PFN_vkGetAndroidHardwareBufferPropertiesANDROID)(VkDevice device, स्थिरांक संरचना AHardwareBuffer* buffer, VkAndroidHardwareBufferPropertiesANDROID* pProperties);
प्रकारव्याख्या VkResult (VKAPI_PTR *PFN_vkGetMemoryAndroidHardwareBufferANDROID)(VkDevice device, स्थिरांक VkMemoryGetAndroidHardwareBufferInfoANDROID* pInfo, संरचना AHardwareBuffer** pBuffer);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetAndroidHardwareBufferPropertiesANDROID(
    VkDevice                                    device,
    स्थिरांक संरचना AHardwareBuffer*               buffer,
    VkAndroidHardwareBufferPropertiesANDROID*   pProperties);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryAndroidHardwareBufferANDROID(
    VkDevice                                    device,
    स्थिरांक VkMemoryGetAndroidHardwareBufferInfoANDROID* pInfo,
    संरचना AHardwareBuffer**                    pBuffer);
#endif
#endif


// VK_ANDROID_external_format_resolve is a preprocessor guard. Do not pass it to API calls.
#define VK_ANDROID_external_format_resolve 1

#define VK_ANDROID_EXTERNAL_FORMAT_RESOLVE_SPEC_VERSION 1
#define VK_ANDROID_EXTERNAL_FORMAT_RESOLVE_EXTENSION_NAME "VK_ANDROID_external_format_resolve"

प्रकारव्याख्या संरचना VkPhysicalDeviceExternalFormatResolveFeaturesANDROID {
    VkStructureType    sType;
    शून्य*              pNext;
    VkBool32           externalFormatResolve;
} VkPhysicalDeviceExternalFormatResolveFeaturesANDROID;

प्रकारव्याख्या संरचना VkPhysicalDeviceExternalFormatResolvePropertiesANDROID {
    VkStructureType     sType;
    शून्य*               pNext;
    VkBool32            nullColorAttachmentWithExternalFormatResolve;
    VkChromaLocation    externalFormatResolveChromaOffsetX;
    VkChromaLocation    externalFormatResolveChromaOffsetY;
} VkPhysicalDeviceExternalFormatResolvePropertiesANDROID;

प्रकारव्याख्या संरचना VkAndroidHardwareBufferFormatResolvePropertiesANDROID {
    VkStructureType    sType;
    शून्य*              pNext;
    VkFormat           colorAttachmentFormat;
} VkAndroidHardwareBufferFormatResolvePropertiesANDROID;


#ifdef __cplusplus
}
#endif

#endif
