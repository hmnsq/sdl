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
வெளி "C" {
#endif



// VK_KHR_android_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_android_surface 1

கட்டமைப்பு ANativeWindow;

#define VK_KHR_ANDROID_SURFACE_SPEC_VERSION 6
#define VK_KHR_ANDROID_SURFACE_EXTENSION_NAME "VK_KHR_android_surface"

வகைவரை VkFlags VkAndroidSurfaceCreateFlagsKHR;

வகைவரை கட்டமைப்பு VkAndroidSurfaceCreateInfoKHR {
    VkStructureType                   sType;
    மாறிலி வெறுமை*                       pNext;
    VkAndroidSurfaceCreateFlagsKHR    flags;
    கட்டமைப்பு ANativeWindow*             window;
} VkAndroidSurfaceCreateInfoKHR;


வகைவரை VkResult (VKAPI_PTR *PFN_vkCreateAndroidSurfaceKHR)(VkInstance instance, மாறிலி VkAndroidSurfaceCreateInfoKHR* pCreateInfo, மாறிலி VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateAndroidSurfaceKHR(
    VkInstance                                  instance,
    மாறிலி VkAndroidSurfaceCreateInfoKHR*        pCreateInfo,
    மாறிலி VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#endif


// VK_ANDROID_external_memory_android_hardware_buffer is a preprocessor guard. Do not pass it to API calls.
#define VK_ANDROID_external_memory_android_hardware_buffer 1

கட்டமைப்பு AHardwareBuffer;

#define VK_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_SPEC_VERSION 5
#define VK_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_EXTENSION_NAME "VK_ANDROID_external_memory_android_hardware_buffer"

வகைவரை கட்டமைப்பு VkAndroidHardwareBufferUsageANDROID {
    VkStructureType    sType;
    வெறுமை*              pNext;
    uint64_t           androidHardwareBufferUsage;
} VkAndroidHardwareBufferUsageANDROID;

வகைவரை கட்டமைப்பு VkAndroidHardwareBufferPropertiesANDROID {
    VkStructureType    sType;
    வெறுமை*              pNext;
    VkDeviceSize       allocationSize;
    uint32_t           memoryTypeBits;
} VkAndroidHardwareBufferPropertiesANDROID;

வகைவரை கட்டமைப்பு VkAndroidHardwareBufferFormatPropertiesANDROID {
    VkStructureType                  sType;
    வெறுமை*                            pNext;
    VkFormat                         format;
    uint64_t                         externalFormat;
    VkFormatFeatureFlags             formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggestedXChromaOffset;
    VkChromaLocation                 suggestedYChromaOffset;
} VkAndroidHardwareBufferFormatPropertiesANDROID;

வகைவரை கட்டமைப்பு VkImportAndroidHardwareBufferInfoANDROID {
    VkStructureType            sType;
    மாறிலி வெறுமை*                pNext;
    கட்டமைப்பு AHardwareBuffer*    buffer;
} VkImportAndroidHardwareBufferInfoANDROID;

வகைவரை கட்டமைப்பு VkMemoryGetAndroidHardwareBufferInfoANDROID {
    VkStructureType    sType;
    மாறிலி வெறுமை*        pNext;
    VkDeviceMemory     memory;
} VkMemoryGetAndroidHardwareBufferInfoANDROID;

வகைவரை கட்டமைப்பு VkExternalFormatANDROID {
    VkStructureType    sType;
    வெறுமை*              pNext;
    uint64_t           externalFormat;
} VkExternalFormatANDROID;

வகைவரை கட்டமைப்பு VkAndroidHardwareBufferFormatProperties2ANDROID {
    VkStructureType                  sType;
    வெறுமை*                            pNext;
    VkFormat                         format;
    uint64_t                         externalFormat;
    VkFormatFeatureFlags2            formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggestedXChromaOffset;
    VkChromaLocation                 suggestedYChromaOffset;
} VkAndroidHardwareBufferFormatProperties2ANDROID;


வகைவரை VkResult (VKAPI_PTR *PFN_vkGetAndroidHardwareBufferPropertiesANDROID)(VkDevice device, மாறிலி கட்டமைப்பு AHardwareBuffer* buffer, VkAndroidHardwareBufferPropertiesANDROID* pProperties);
வகைவரை VkResult (VKAPI_PTR *PFN_vkGetMemoryAndroidHardwareBufferANDROID)(VkDevice device, மாறிலி VkMemoryGetAndroidHardwareBufferInfoANDROID* pInfo, கட்டமைப்பு AHardwareBuffer** pBuffer);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetAndroidHardwareBufferPropertiesANDROID(
    VkDevice                                    device,
    மாறிலி கட்டமைப்பு AHardwareBuffer*               buffer,
    VkAndroidHardwareBufferPropertiesANDROID*   pProperties);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryAndroidHardwareBufferANDROID(
    VkDevice                                    device,
    மாறிலி VkMemoryGetAndroidHardwareBufferInfoANDROID* pInfo,
    கட்டமைப்பு AHardwareBuffer**                    pBuffer);
#endif
#endif


// VK_ANDROID_external_format_resolve is a preprocessor guard. Do not pass it to API calls.
#define VK_ANDROID_external_format_resolve 1

#define VK_ANDROID_EXTERNAL_FORMAT_RESOLVE_SPEC_VERSION 1
#define VK_ANDROID_EXTERNAL_FORMAT_RESOLVE_EXTENSION_NAME "VK_ANDROID_external_format_resolve"

வகைவரை கட்டமைப்பு VkPhysicalDeviceExternalFormatResolveFeaturesANDROID {
    VkStructureType    sType;
    வெறுமை*              pNext;
    VkBool32           externalFormatResolve;
} VkPhysicalDeviceExternalFormatResolveFeaturesANDROID;

வகைவரை கட்டமைப்பு VkPhysicalDeviceExternalFormatResolvePropertiesANDROID {
    VkStructureType     sType;
    வெறுமை*               pNext;
    VkBool32            nullColorAttachmentWithExternalFormatResolve;
    VkChromaLocation    externalFormatResolveChromaOffsetX;
    VkChromaLocation    externalFormatResolveChromaOffsetY;
} VkPhysicalDeviceExternalFormatResolvePropertiesANDROID;

வகைவரை கட்டமைப்பு VkAndroidHardwareBufferFormatResolvePropertiesANDROID {
    VkStructureType    sType;
    வெறுமை*              pNext;
    VkFormat           colorAttachmentFormat;
} VkAndroidHardwareBufferFormatResolvePropertiesANDROID;


#ifdef __cplusplus
}
#endif

#endif
