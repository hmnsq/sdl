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
બાહ્ય "C" {
#endif



// VK_KHR_android_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_android_surface 1

સંરચના ANativeWindow;

#define VK_KHR_ANDROID_SURFACE_SPEC_VERSION 6
#define VK_KHR_ANDROID_SURFACE_EXTENSION_NAME "VK_KHR_android_surface"

પ્રકારવ્યાખ્યા VkFlags VkAndroidSurfaceCreateFlagsKHR;

પ્રકારવ્યાખ્યા સંરચના VkAndroidSurfaceCreateInfoKHR {
    VkStructureType                   sType;
    અચલ શૂન્ય*                       pNext;
    VkAndroidSurfaceCreateFlagsKHR    flags;
    સંરચના ANativeWindow*             window;
} VkAndroidSurfaceCreateInfoKHR;


પ્રકારવ્યાખ્યા VkResult (VKAPI_PTR *PFN_vkCreateAndroidSurfaceKHR)(VkInstance instance, અચલ VkAndroidSurfaceCreateInfoKHR* pCreateInfo, અચલ VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateAndroidSurfaceKHR(
    VkInstance                                  instance,
    અચલ VkAndroidSurfaceCreateInfoKHR*        pCreateInfo,
    અચલ VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#endif


// VK_ANDROID_external_memory_android_hardware_buffer is a preprocessor guard. Do not pass it to API calls.
#define VK_ANDROID_external_memory_android_hardware_buffer 1

સંરચના AHardwareBuffer;

#define VK_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_SPEC_VERSION 5
#define VK_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_EXTENSION_NAME "VK_ANDROID_external_memory_android_hardware_buffer"

પ્રકારવ્યાખ્યા સંરચના VkAndroidHardwareBufferUsageANDROID {
    VkStructureType    sType;
    શૂન્ય*              pNext;
    uint64_t           androidHardwareBufferUsage;
} VkAndroidHardwareBufferUsageANDROID;

પ્રકારવ્યાખ્યા સંરચના VkAndroidHardwareBufferPropertiesANDROID {
    VkStructureType    sType;
    શૂન્ય*              pNext;
    VkDeviceSize       allocationSize;
    uint32_t           memoryTypeBits;
} VkAndroidHardwareBufferPropertiesANDROID;

પ્રકારવ્યાખ્યા સંરચના VkAndroidHardwareBufferFormatPropertiesANDROID {
    VkStructureType                  sType;
    શૂન્ય*                            pNext;
    VkFormat                         format;
    uint64_t                         externalFormat;
    VkFormatFeatureFlags             formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggestedXChromaOffset;
    VkChromaLocation                 suggestedYChromaOffset;
} VkAndroidHardwareBufferFormatPropertiesANDROID;

પ્રકારવ્યાખ્યા સંરચના VkImportAndroidHardwareBufferInfoANDROID {
    VkStructureType            sType;
    અચલ શૂન્ય*                pNext;
    સંરચના AHardwareBuffer*    buffer;
} VkImportAndroidHardwareBufferInfoANDROID;

પ્રકારવ્યાખ્યા સંરચના VkMemoryGetAndroidHardwareBufferInfoANDROID {
    VkStructureType    sType;
    અચલ શૂન્ય*        pNext;
    VkDeviceMemory     memory;
} VkMemoryGetAndroidHardwareBufferInfoANDROID;

પ્રકારવ્યાખ્યા સંરચના VkExternalFormatANDROID {
    VkStructureType    sType;
    શૂન્ય*              pNext;
    uint64_t           externalFormat;
} VkExternalFormatANDROID;

પ્રકારવ્યાખ્યા સંરચના VkAndroidHardwareBufferFormatProperties2ANDROID {
    VkStructureType                  sType;
    શૂન્ય*                            pNext;
    VkFormat                         format;
    uint64_t                         externalFormat;
    VkFormatFeatureFlags2            formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggestedXChromaOffset;
    VkChromaLocation                 suggestedYChromaOffset;
} VkAndroidHardwareBufferFormatProperties2ANDROID;


પ્રકારવ્યાખ્યા VkResult (VKAPI_PTR *PFN_vkGetAndroidHardwareBufferPropertiesANDROID)(VkDevice device, અચલ સંરચના AHardwareBuffer* buffer, VkAndroidHardwareBufferPropertiesANDROID* pProperties);
પ્રકારવ્યાખ્યા VkResult (VKAPI_PTR *PFN_vkGetMemoryAndroidHardwareBufferANDROID)(VkDevice device, અચલ VkMemoryGetAndroidHardwareBufferInfoANDROID* pInfo, સંરચના AHardwareBuffer** pBuffer);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetAndroidHardwareBufferPropertiesANDROID(
    VkDevice                                    device,
    અચલ સંરચના AHardwareBuffer*               buffer,
    VkAndroidHardwareBufferPropertiesANDROID*   pProperties);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryAndroidHardwareBufferANDROID(
    VkDevice                                    device,
    અચલ VkMemoryGetAndroidHardwareBufferInfoANDROID* pInfo,
    સંરચના AHardwareBuffer**                    pBuffer);
#endif
#endif


// VK_ANDROID_external_format_resolve is a preprocessor guard. Do not pass it to API calls.
#define VK_ANDROID_external_format_resolve 1

#define VK_ANDROID_EXTERNAL_FORMAT_RESOLVE_SPEC_VERSION 1
#define VK_ANDROID_EXTERNAL_FORMAT_RESOLVE_EXTENSION_NAME "VK_ANDROID_external_format_resolve"

પ્રકારવ્યાખ્યા સંરચના VkPhysicalDeviceExternalFormatResolveFeaturesANDROID {
    VkStructureType    sType;
    શૂન્ય*              pNext;
    VkBool32           externalFormatResolve;
} VkPhysicalDeviceExternalFormatResolveFeaturesANDROID;

પ્રકારવ્યાખ્યા સંરચના VkPhysicalDeviceExternalFormatResolvePropertiesANDROID {
    VkStructureType     sType;
    શૂન્ય*               pNext;
    VkBool32            nullColorAttachmentWithExternalFormatResolve;
    VkChromaLocation    externalFormatResolveChromaOffsetX;
    VkChromaLocation    externalFormatResolveChromaOffsetY;
} VkPhysicalDeviceExternalFormatResolvePropertiesANDROID;

પ્રકારવ્યાખ્યા સંરચના VkAndroidHardwareBufferFormatResolvePropertiesANDROID {
    VkStructureType    sType;
    શૂન્ય*              pNext;
    VkFormat           colorAttachmentFormat;
} VkAndroidHardwareBufferFormatResolvePropertiesANDROID;


#ifdef __cplusplus
}
#endif

#endif
