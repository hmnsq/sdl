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
خارجي "C" {
#endif



// VK_OHOS_external_memory is a preprocessor guard. Do not pass it to API calls.
#define VK_OHOS_external_memory 1

بنية OH_NativeBuffer;

#define VK_OHOS_EXTERNAL_MEMORY_SPEC_VERSION 1
#define VK_OHOS_EXTERNAL_MEMORY_EXTENSION_NAME "VK_OHOS_external_memory"

تعريفنوع بنية VkNativeBufferUsageOHOS {
    VkStructureType    sType;
    فراغ*              pNext;
    uint64_t           OHOSNativeBufferUsage;
} VkNativeBufferUsageOHOS;

تعريفنوع بنية VkNativeBufferPropertiesOHOS {
    VkStructureType    sType;
    فراغ*              pNext;
    VkDeviceSize       allocationSize;
    uint32_t           memoryTypeBits;
} VkNativeBufferPropertiesOHOS;

تعريفنوع بنية VkNativeBufferFormatPropertiesOHOS {
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
} VkNativeBufferFormatPropertiesOHOS;

تعريفنوع بنية VkImportNativeBufferInfoOHOS {
    VkStructureType            sType;
    ثابت فراغ*                pNext;
    بنية OH_NativeBuffer*    buffer;
} VkImportNativeBufferInfoOHOS;

تعريفنوع بنية VkMemoryGetNativeBufferInfoOHOS {
    VkStructureType    sType;
    ثابت فراغ*        pNext;
    VkDeviceMemory     memory;
} VkMemoryGetNativeBufferInfoOHOS;

تعريفنوع بنية VkExternalFormatOHOS {
    VkStructureType    sType;
    فراغ*              pNext;
    uint64_t           externalFormat;
} VkExternalFormatOHOS;


تعريفنوع VkResult (VKAPI_PTR *PFN_vkGetNativeBufferPropertiesOHOS)(VkDevice device, ثابت بنية OH_NativeBuffer* buffer, VkNativeBufferPropertiesOHOS* pProperties);
تعريفنوع VkResult (VKAPI_PTR *PFN_vkGetMemoryNativeBufferOHOS)(VkDevice device, ثابت VkMemoryGetNativeBufferInfoOHOS* pInfo, بنية OH_NativeBuffer** pBuffer);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetNativeBufferPropertiesOHOS(
    VkDevice                                    device,
    ثابت بنية OH_NativeBuffer*               buffer,
    VkNativeBufferPropertiesOHOS*               pProperties);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryNativeBufferOHOS(
    VkDevice                                    device,
    ثابت VkMemoryGetNativeBufferInfoOHOS*      pInfo,
    بنية OH_NativeBuffer**                    pBuffer);
#endif
#endif


// VK_OHOS_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_OHOS_surface 1

تعريفنوع بنية NativeWindow OHNativeWindow;

#define VK_OHOS_SURFACE_SPEC_VERSION      1
#define VK_OHOS_SURFACE_EXTENSION_NAME    "VK_OHOS_surface"

تعريفنوع VkFlags VkSurfaceCreateFlagsOHOS;

تعريفنوع بنية VkSurfaceCreateInfoOHOS {
    VkStructureType             sType;
    ثابت فراغ*                 pNext;
    VkSurfaceCreateFlagsOHOS    flags;
    OHNativeWindow*             window;
} VkSurfaceCreateInfoOHOS;


تعريفنوع VkResult (VKAPI_PTR *PFN_vkCreateSurfaceOHOS)(VkInstance instance, ثابت VkSurfaceCreateInfoOHOS* pCreateInfo, ثابت VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateSurfaceOHOS(
    VkInstance                                  instance,
    ثابت VkSurfaceCreateInfoOHOS*              pCreateInfo,
    ثابت VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif
