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
بیرونی "C" {
#endif



// VK_OHOS_external_memory is a preprocessor guard. Do not pass it to API calls.
#define VK_OHOS_external_memory 1

ساختار OH_NativeBuffer;

#define VK_OHOS_EXTERNAL_MEMORY_SPEC_VERSION 1
#define VK_OHOS_EXTERNAL_MEMORY_EXTENSION_NAME "VK_OHOS_external_memory"

تعریفنوع ساختار VkNativeBufferUsageOHOS {
    VkStructureType    sType;
    تهی*              pNext;
    uint64_t           OHOSNativeBufferUsage;
} VkNativeBufferUsageOHOS;

تعریفنوع ساختار VkNativeBufferPropertiesOHOS {
    VkStructureType    sType;
    تهی*              pNext;
    VkDeviceSize       allocationSize;
    uint32_t           memoryTypeBits;
} VkNativeBufferPropertiesOHOS;

تعریفنوع ساختار VkNativeBufferFormatPropertiesOHOS {
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
} VkNativeBufferFormatPropertiesOHOS;

تعریفنوع ساختار VkImportNativeBufferInfoOHOS {
    VkStructureType            sType;
    ثابت تهی*                pNext;
    ساختار OH_NativeBuffer*    buffer;
} VkImportNativeBufferInfoOHOS;

تعریفنوع ساختار VkMemoryGetNativeBufferInfoOHOS {
    VkStructureType    sType;
    ثابت تهی*        pNext;
    VkDeviceMemory     memory;
} VkMemoryGetNativeBufferInfoOHOS;

تعریفنوع ساختار VkExternalFormatOHOS {
    VkStructureType    sType;
    تهی*              pNext;
    uint64_t           externalFormat;
} VkExternalFormatOHOS;


تعریفنوع VkResult (VKAPI_PTR *PFN_vkGetNativeBufferPropertiesOHOS)(VkDevice device, ثابت ساختار OH_NativeBuffer* buffer, VkNativeBufferPropertiesOHOS* pProperties);
تعریفنوع VkResult (VKAPI_PTR *PFN_vkGetMemoryNativeBufferOHOS)(VkDevice device, ثابت VkMemoryGetNativeBufferInfoOHOS* pInfo, ساختار OH_NativeBuffer** pBuffer);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetNativeBufferPropertiesOHOS(
    VkDevice                                    device,
    ثابت ساختار OH_NativeBuffer*               buffer,
    VkNativeBufferPropertiesOHOS*               pProperties);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryNativeBufferOHOS(
    VkDevice                                    device,
    ثابت VkMemoryGetNativeBufferInfoOHOS*      pInfo,
    ساختار OH_NativeBuffer**                    pBuffer);
#endif
#endif


// VK_OHOS_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_OHOS_surface 1

تعریفنوع ساختار NativeWindow OHNativeWindow;

#define VK_OHOS_SURFACE_SPEC_VERSION      1
#define VK_OHOS_SURFACE_EXTENSION_NAME    "VK_OHOS_surface"

تعریفنوع VkFlags VkSurfaceCreateFlagsOHOS;

تعریفنوع ساختار VkSurfaceCreateInfoOHOS {
    VkStructureType             sType;
    ثابت تهی*                 pNext;
    VkSurfaceCreateFlagsOHOS    flags;
    OHNativeWindow*             window;
} VkSurfaceCreateInfoOHOS;


تعریفنوع VkResult (VKAPI_PTR *PFN_vkCreateSurfaceOHOS)(VkInstance instance, ثابت VkSurfaceCreateInfoOHOS* pCreateInfo, ثابت VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

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
