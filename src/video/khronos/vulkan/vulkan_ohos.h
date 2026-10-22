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
बाह्य "C" {
#endif



// VK_OHOS_external_memory is a preprocessor guard. Do not pass it to API calls.
#define VK_OHOS_external_memory 1

संरचना OH_NativeBuffer;

#define VK_OHOS_EXTERNAL_MEMORY_SPEC_VERSION 1
#define VK_OHOS_EXTERNAL_MEMORY_EXTENSION_NAME "VK_OHOS_external_memory"

प्रकारव्याख्या संरचना VkNativeBufferUsageOHOS {
    VkStructureType    sType;
    शून्य*              pNext;
    uint64_t           OHOSNativeBufferUsage;
} VkNativeBufferUsageOHOS;

प्रकारव्याख्या संरचना VkNativeBufferPropertiesOHOS {
    VkStructureType    sType;
    शून्य*              pNext;
    VkDeviceSize       allocationSize;
    uint32_t           memoryTypeBits;
} VkNativeBufferPropertiesOHOS;

प्रकारव्याख्या संरचना VkNativeBufferFormatPropertiesOHOS {
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
} VkNativeBufferFormatPropertiesOHOS;

प्रकारव्याख्या संरचना VkImportNativeBufferInfoOHOS {
    VkStructureType            sType;
    स्थिरांक शून्य*                pNext;
    संरचना OH_NativeBuffer*    buffer;
} VkImportNativeBufferInfoOHOS;

प्रकारव्याख्या संरचना VkMemoryGetNativeBufferInfoOHOS {
    VkStructureType    sType;
    स्थिरांक शून्य*        pNext;
    VkDeviceMemory     memory;
} VkMemoryGetNativeBufferInfoOHOS;

प्रकारव्याख्या संरचना VkExternalFormatOHOS {
    VkStructureType    sType;
    शून्य*              pNext;
    uint64_t           externalFormat;
} VkExternalFormatOHOS;


प्रकारव्याख्या VkResult (VKAPI_PTR *PFN_vkGetNativeBufferPropertiesOHOS)(VkDevice device, स्थिरांक संरचना OH_NativeBuffer* buffer, VkNativeBufferPropertiesOHOS* pProperties);
प्रकारव्याख्या VkResult (VKAPI_PTR *PFN_vkGetMemoryNativeBufferOHOS)(VkDevice device, स्थिरांक VkMemoryGetNativeBufferInfoOHOS* pInfo, संरचना OH_NativeBuffer** pBuffer);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetNativeBufferPropertiesOHOS(
    VkDevice                                    device,
    स्थिरांक संरचना OH_NativeBuffer*               buffer,
    VkNativeBufferPropertiesOHOS*               pProperties);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryNativeBufferOHOS(
    VkDevice                                    device,
    स्थिरांक VkMemoryGetNativeBufferInfoOHOS*      pInfo,
    संरचना OH_NativeBuffer**                    pBuffer);
#endif
#endif


// VK_OHOS_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_OHOS_surface 1

प्रकारव्याख्या संरचना NativeWindow OHNativeWindow;

#define VK_OHOS_SURFACE_SPEC_VERSION      1
#define VK_OHOS_SURFACE_EXTENSION_NAME    "VK_OHOS_surface"

प्रकारव्याख्या VkFlags VkSurfaceCreateFlagsOHOS;

प्रकारव्याख्या संरचना VkSurfaceCreateInfoOHOS {
    VkStructureType             sType;
    स्थिरांक शून्य*                 pNext;
    VkSurfaceCreateFlagsOHOS    flags;
    OHNativeWindow*             window;
} VkSurfaceCreateInfoOHOS;


प्रकारव्याख्या VkResult (VKAPI_PTR *PFN_vkCreateSurfaceOHOS)(VkInstance instance, स्थिरांक VkSurfaceCreateInfoOHOS* pCreateInfo, स्थिरांक VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateSurfaceOHOS(
    VkInstance                                  instance,
    स्थिरांक VkSurfaceCreateInfoOHOS*              pCreateInfo,
    स्थिरांक VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif
