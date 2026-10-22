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
બાહ્ય "C" {
#endif



// VK_OHOS_external_memory is a preprocessor guard. Do not pass it to API calls.
#define VK_OHOS_external_memory 1

સંરચના OH_NativeBuffer;

#define VK_OHOS_EXTERNAL_MEMORY_SPEC_VERSION 1
#define VK_OHOS_EXTERNAL_MEMORY_EXTENSION_NAME "VK_OHOS_external_memory"

પ્રકારવ્યાખ્યા સંરચના VkNativeBufferUsageOHOS {
    VkStructureType    sType;
    શૂન્ય*              pNext;
    uint64_t           OHOSNativeBufferUsage;
} VkNativeBufferUsageOHOS;

પ્રકારવ્યાખ્યા સંરચના VkNativeBufferPropertiesOHOS {
    VkStructureType    sType;
    શૂન્ય*              pNext;
    VkDeviceSize       allocationSize;
    uint32_t           memoryTypeBits;
} VkNativeBufferPropertiesOHOS;

પ્રકારવ્યાખ્યા સંરચના VkNativeBufferFormatPropertiesOHOS {
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
} VkNativeBufferFormatPropertiesOHOS;

પ્રકારવ્યાખ્યા સંરચના VkImportNativeBufferInfoOHOS {
    VkStructureType            sType;
    અચલ શૂન્ય*                pNext;
    સંરચના OH_NativeBuffer*    buffer;
} VkImportNativeBufferInfoOHOS;

પ્રકારવ્યાખ્યા સંરચના VkMemoryGetNativeBufferInfoOHOS {
    VkStructureType    sType;
    અચલ શૂન્ય*        pNext;
    VkDeviceMemory     memory;
} VkMemoryGetNativeBufferInfoOHOS;

પ્રકારવ્યાખ્યા સંરચના VkExternalFormatOHOS {
    VkStructureType    sType;
    શૂન્ય*              pNext;
    uint64_t           externalFormat;
} VkExternalFormatOHOS;


પ્રકારવ્યાખ્યા VkResult (VKAPI_PTR *PFN_vkGetNativeBufferPropertiesOHOS)(VkDevice device, અચલ સંરચના OH_NativeBuffer* buffer, VkNativeBufferPropertiesOHOS* pProperties);
પ્રકારવ્યાખ્યા VkResult (VKAPI_PTR *PFN_vkGetMemoryNativeBufferOHOS)(VkDevice device, અચલ VkMemoryGetNativeBufferInfoOHOS* pInfo, સંરચના OH_NativeBuffer** pBuffer);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetNativeBufferPropertiesOHOS(
    VkDevice                                    device,
    અચલ સંરચના OH_NativeBuffer*               buffer,
    VkNativeBufferPropertiesOHOS*               pProperties);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryNativeBufferOHOS(
    VkDevice                                    device,
    અચલ VkMemoryGetNativeBufferInfoOHOS*      pInfo,
    સંરચના OH_NativeBuffer**                    pBuffer);
#endif
#endif


// VK_OHOS_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_OHOS_surface 1

પ્રકારવ્યાખ્યા સંરચના NativeWindow OHNativeWindow;

#define VK_OHOS_SURFACE_SPEC_VERSION      1
#define VK_OHOS_SURFACE_EXTENSION_NAME    "VK_OHOS_surface"

પ્રકારવ્યાખ્યા VkFlags VkSurfaceCreateFlagsOHOS;

પ્રકારવ્યાખ્યા સંરચના VkSurfaceCreateInfoOHOS {
    VkStructureType             sType;
    અચલ શૂન્ય*                 pNext;
    VkSurfaceCreateFlagsOHOS    flags;
    OHNativeWindow*             window;
} VkSurfaceCreateInfoOHOS;


પ્રકારવ્યાખ્યા VkResult (VKAPI_PTR *PFN_vkCreateSurfaceOHOS)(VkInstance instance, અચલ VkSurfaceCreateInfoOHOS* pCreateInfo, અચલ VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateSurfaceOHOS(
    VkInstance                                  instance,
    અચલ VkSurfaceCreateInfoOHOS*              pCreateInfo,
    અચલ VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif
