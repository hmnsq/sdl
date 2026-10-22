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
ಬಾಹ್ಯ "C" {
#endif



// VK_OHOS_external_memory is a preprocessor guard. Do not pass it to API calls.
#define VK_OHOS_external_memory 1

ಸಂರಚನಾ OH_NativeBuffer;

#define VK_OHOS_EXTERNAL_MEMORY_SPEC_VERSION 1
#define VK_OHOS_EXTERNAL_MEMORY_EXTENSION_NAME "VK_OHOS_external_memory"

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkNativeBufferUsageOHOS {
    VkStructureType    sType;
    ಶೂನ್ಯ*              pNext;
    uint64_t           OHOSNativeBufferUsage;
} VkNativeBufferUsageOHOS;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkNativeBufferPropertiesOHOS {
    VkStructureType    sType;
    ಶೂನ್ಯ*              pNext;
    VkDeviceSize       allocationSize;
    uint32_t           memoryTypeBits;
} VkNativeBufferPropertiesOHOS;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkNativeBufferFormatPropertiesOHOS {
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
} VkNativeBufferFormatPropertiesOHOS;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkImportNativeBufferInfoOHOS {
    VkStructureType            sType;
    ಧ್ರುವ ಶೂನ್ಯ*                pNext;
    ಸಂರಚನಾ OH_NativeBuffer*    buffer;
} VkImportNativeBufferInfoOHOS;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkMemoryGetNativeBufferInfoOHOS {
    VkStructureType    sType;
    ಧ್ರುವ ಶೂನ್ಯ*        pNext;
    VkDeviceMemory     memory;
} VkMemoryGetNativeBufferInfoOHOS;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkExternalFormatOHOS {
    VkStructureType    sType;
    ಶೂನ್ಯ*              pNext;
    uint64_t           externalFormat;
} VkExternalFormatOHOS;


ಪ್ರಕಾರನಿರ್ದೇಶ VkResult (VKAPI_PTR *PFN_vkGetNativeBufferPropertiesOHOS)(VkDevice device, ಧ್ರುವ ಸಂರಚನಾ OH_NativeBuffer* buffer, VkNativeBufferPropertiesOHOS* pProperties);
ಪ್ರಕಾರನಿರ್ದೇಶ VkResult (VKAPI_PTR *PFN_vkGetMemoryNativeBufferOHOS)(VkDevice device, ಧ್ರುವ VkMemoryGetNativeBufferInfoOHOS* pInfo, ಸಂರಚನಾ OH_NativeBuffer** pBuffer);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetNativeBufferPropertiesOHOS(
    VkDevice                                    device,
    ಧ್ರುವ ಸಂರಚನಾ OH_NativeBuffer*               buffer,
    VkNativeBufferPropertiesOHOS*               pProperties);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryNativeBufferOHOS(
    VkDevice                                    device,
    ಧ್ರುವ VkMemoryGetNativeBufferInfoOHOS*      pInfo,
    ಸಂರಚನಾ OH_NativeBuffer**                    pBuffer);
#endif
#endif


// VK_OHOS_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_OHOS_surface 1

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ NativeWindow OHNativeWindow;

#define VK_OHOS_SURFACE_SPEC_VERSION      1
#define VK_OHOS_SURFACE_EXTENSION_NAME    "VK_OHOS_surface"

ಪ್ರಕಾರನಿರ್ದೇಶ VkFlags VkSurfaceCreateFlagsOHOS;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkSurfaceCreateInfoOHOS {
    VkStructureType             sType;
    ಧ್ರುವ ಶೂನ್ಯ*                 pNext;
    VkSurfaceCreateFlagsOHOS    flags;
    OHNativeWindow*             window;
} VkSurfaceCreateInfoOHOS;


ಪ್ರಕಾರನಿರ್ದೇಶ VkResult (VKAPI_PTR *PFN_vkCreateSurfaceOHOS)(VkInstance instance, ಧ್ರುವ VkSurfaceCreateInfoOHOS* pCreateInfo, ಧ್ರುವ VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateSurfaceOHOS(
    VkInstance                                  instance,
    ಧ್ರುವ VkSurfaceCreateInfoOHOS*              pCreateInfo,
    ಧ್ರುವ VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif
