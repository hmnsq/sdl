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
ବାହ୍ୟ "C" {
#endif



// VK_OHOS_external_memory is a preprocessor guard. Do not pass it to API calls.
#define VK_OHOS_external_memory 1

ସଂରଚନା OH_NativeBuffer;

#define VK_OHOS_EXTERNAL_MEMORY_SPEC_VERSION 1
#define VK_OHOS_EXTERNAL_MEMORY_EXTENSION_NAME "VK_OHOS_external_memory"

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkNativeBufferUsageOHOS {
    VkStructureType    sType;
    ଶୂନ୍ୟ*              pNext;
    uint64_t           OHOSNativeBufferUsage;
} VkNativeBufferUsageOHOS;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkNativeBufferPropertiesOHOS {
    VkStructureType    sType;
    ଶୂନ୍ୟ*              pNext;
    VkDeviceSize       allocationSize;
    uint32_t           memoryTypeBits;
} VkNativeBufferPropertiesOHOS;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkNativeBufferFormatPropertiesOHOS {
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
} VkNativeBufferFormatPropertiesOHOS;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkImportNativeBufferInfoOHOS {
    VkStructureType            sType;
    ଅଚଳ ଶୂନ୍ୟ*                pNext;
    ସଂରଚନା OH_NativeBuffer*    buffer;
} VkImportNativeBufferInfoOHOS;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkMemoryGetNativeBufferInfoOHOS {
    VkStructureType    sType;
    ଅଚଳ ଶୂନ୍ୟ*        pNext;
    VkDeviceMemory     memory;
} VkMemoryGetNativeBufferInfoOHOS;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkExternalFormatOHOS {
    VkStructureType    sType;
    ଶୂନ୍ୟ*              pNext;
    uint64_t           externalFormat;
} VkExternalFormatOHOS;


ପ୍ରକାରବ୍ୟାଖ୍ୟା VkResult (VKAPI_PTR *PFN_vkGetNativeBufferPropertiesOHOS)(VkDevice device, ଅଚଳ ସଂରଚନା OH_NativeBuffer* buffer, VkNativeBufferPropertiesOHOS* pProperties);
ପ୍ରକାରବ୍ୟାଖ୍ୟା VkResult (VKAPI_PTR *PFN_vkGetMemoryNativeBufferOHOS)(VkDevice device, ଅଚଳ VkMemoryGetNativeBufferInfoOHOS* pInfo, ସଂରଚନା OH_NativeBuffer** pBuffer);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetNativeBufferPropertiesOHOS(
    VkDevice                                    device,
    ଅଚଳ ସଂରଚନା OH_NativeBuffer*               buffer,
    VkNativeBufferPropertiesOHOS*               pProperties);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryNativeBufferOHOS(
    VkDevice                                    device,
    ଅଚଳ VkMemoryGetNativeBufferInfoOHOS*      pInfo,
    ସଂରଚନା OH_NativeBuffer**                    pBuffer);
#endif
#endif


// VK_OHOS_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_OHOS_surface 1

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା NativeWindow OHNativeWindow;

#define VK_OHOS_SURFACE_SPEC_VERSION      1
#define VK_OHOS_SURFACE_EXTENSION_NAME    "VK_OHOS_surface"

ପ୍ରକାରବ୍ୟାଖ୍ୟା VkFlags VkSurfaceCreateFlagsOHOS;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkSurfaceCreateInfoOHOS {
    VkStructureType             sType;
    ଅଚଳ ଶୂନ୍ୟ*                 pNext;
    VkSurfaceCreateFlagsOHOS    flags;
    OHNativeWindow*             window;
} VkSurfaceCreateInfoOHOS;


ପ୍ରକାରବ୍ୟାଖ୍ୟା VkResult (VKAPI_PTR *PFN_vkCreateSurfaceOHOS)(VkInstance instance, ଅଚଳ VkSurfaceCreateInfoOHOS* pCreateInfo, ଅଚଳ VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateSurfaceOHOS(
    VkInstance                                  instance,
    ଅଚଳ VkSurfaceCreateInfoOHOS*              pCreateInfo,
    ଅଚଳ VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif
