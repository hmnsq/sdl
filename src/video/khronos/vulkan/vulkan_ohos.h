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

प्रकारनिर्देश संरचना VkNativeBufferUsageOHOS {
    VkStructureType    sType;
    शून्य*              pNext;
    uint64_t           OHOSNativeBufferUsage;
} VkNativeBufferUsageOHOS;

प्रकारनिर्देश संरचना VkNativeBufferPropertiesOHOS {
    VkStructureType    sType;
    शून्य*              pNext;
    VkDeviceSize       allocationSize;
    uint32_t           memoryTypeBits;
} VkNativeBufferPropertiesOHOS;

प्रकारनिर्देश संरचना VkNativeBufferFormatPropertiesOHOS {
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

प्रकारनिर्देश संरचना VkImportNativeBufferInfoOHOS {
    VkStructureType            sType;
    ध्रुव शून्य*                pNext;
    संरचना OH_NativeBuffer*    buffer;
} VkImportNativeBufferInfoOHOS;

प्रकारनिर्देश संरचना VkMemoryGetNativeBufferInfoOHOS {
    VkStructureType    sType;
    ध्रुव शून्य*        pNext;
    VkDeviceMemory     memory;
} VkMemoryGetNativeBufferInfoOHOS;

प्रकारनिर्देश संरचना VkExternalFormatOHOS {
    VkStructureType    sType;
    शून्य*              pNext;
    uint64_t           externalFormat;
} VkExternalFormatOHOS;


प्रकारनिर्देश VkResult (VKAPI_PTR *PFN_vkGetNativeBufferPropertiesOHOS)(VkDevice device, ध्रुव संरचना OH_NativeBuffer* buffer, VkNativeBufferPropertiesOHOS* pProperties);
प्रकारनिर्देश VkResult (VKAPI_PTR *PFN_vkGetMemoryNativeBufferOHOS)(VkDevice device, ध्रुव VkMemoryGetNativeBufferInfoOHOS* pInfo, संरचना OH_NativeBuffer** pBuffer);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetNativeBufferPropertiesOHOS(
    VkDevice                                    device,
    ध्रुव संरचना OH_NativeBuffer*               buffer,
    VkNativeBufferPropertiesOHOS*               pProperties);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryNativeBufferOHOS(
    VkDevice                                    device,
    ध्रुव VkMemoryGetNativeBufferInfoOHOS*      pInfo,
    संरचना OH_NativeBuffer**                    pBuffer);
#endif
#endif


// VK_OHOS_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_OHOS_surface 1

प्रकारनिर्देश संरचना NativeWindow OHNativeWindow;

#define VK_OHOS_SURFACE_SPEC_VERSION      1
#define VK_OHOS_SURFACE_EXTENSION_NAME    "VK_OHOS_surface"

प्रकारनिर्देश VkFlags VkSurfaceCreateFlagsOHOS;

प्रकारनिर्देश संरचना VkSurfaceCreateInfoOHOS {
    VkStructureType             sType;
    ध्रुव शून्य*                 pNext;
    VkSurfaceCreateFlagsOHOS    flags;
    OHNativeWindow*             window;
} VkSurfaceCreateInfoOHOS;


प्रकारनिर्देश VkResult (VKAPI_PTR *PFN_vkCreateSurfaceOHOS)(VkInstance instance, ध्रुव VkSurfaceCreateInfoOHOS* pCreateInfo, ध्रुव VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateSurfaceOHOS(
    VkInstance                                  instance,
    ध्रुव VkSurfaceCreateInfoOHOS*              pCreateInfo,
    ध्रुव VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif
