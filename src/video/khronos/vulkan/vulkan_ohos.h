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
வெளி "C" {
#endif



// VK_OHOS_external_memory is a preprocessor guard. Do not pass it to API calls.
#define VK_OHOS_external_memory 1

கட்டமைப்பு OH_NativeBuffer;

#define VK_OHOS_EXTERNAL_MEMORY_SPEC_VERSION 1
#define VK_OHOS_EXTERNAL_MEMORY_EXTENSION_NAME "VK_OHOS_external_memory"

வகைவரை கட்டமைப்பு VkNativeBufferUsageOHOS {
    VkStructureType    sType;
    வெறுமை*              pNext;
    uint64_t           OHOSNativeBufferUsage;
} VkNativeBufferUsageOHOS;

வகைவரை கட்டமைப்பு VkNativeBufferPropertiesOHOS {
    VkStructureType    sType;
    வெறுமை*              pNext;
    VkDeviceSize       allocationSize;
    uint32_t           memoryTypeBits;
} VkNativeBufferPropertiesOHOS;

வகைவரை கட்டமைப்பு VkNativeBufferFormatPropertiesOHOS {
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
} VkNativeBufferFormatPropertiesOHOS;

வகைவரை கட்டமைப்பு VkImportNativeBufferInfoOHOS {
    VkStructureType            sType;
    மாறிலி வெறுமை*                pNext;
    கட்டமைப்பு OH_NativeBuffer*    buffer;
} VkImportNativeBufferInfoOHOS;

வகைவரை கட்டமைப்பு VkMemoryGetNativeBufferInfoOHOS {
    VkStructureType    sType;
    மாறிலி வெறுமை*        pNext;
    VkDeviceMemory     memory;
} VkMemoryGetNativeBufferInfoOHOS;

வகைவரை கட்டமைப்பு VkExternalFormatOHOS {
    VkStructureType    sType;
    வெறுமை*              pNext;
    uint64_t           externalFormat;
} VkExternalFormatOHOS;


வகைவரை VkResult (VKAPI_PTR *PFN_vkGetNativeBufferPropertiesOHOS)(VkDevice device, மாறிலி கட்டமைப்பு OH_NativeBuffer* buffer, VkNativeBufferPropertiesOHOS* pProperties);
வகைவரை VkResult (VKAPI_PTR *PFN_vkGetMemoryNativeBufferOHOS)(VkDevice device, மாறிலி VkMemoryGetNativeBufferInfoOHOS* pInfo, கட்டமைப்பு OH_NativeBuffer** pBuffer);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetNativeBufferPropertiesOHOS(
    VkDevice                                    device,
    மாறிலி கட்டமைப்பு OH_NativeBuffer*               buffer,
    VkNativeBufferPropertiesOHOS*               pProperties);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryNativeBufferOHOS(
    VkDevice                                    device,
    மாறிலி VkMemoryGetNativeBufferInfoOHOS*      pInfo,
    கட்டமைப்பு OH_NativeBuffer**                    pBuffer);
#endif
#endif


// VK_OHOS_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_OHOS_surface 1

வகைவரை கட்டமைப்பு NativeWindow OHNativeWindow;

#define VK_OHOS_SURFACE_SPEC_VERSION      1
#define VK_OHOS_SURFACE_EXTENSION_NAME    "VK_OHOS_surface"

வகைவரை VkFlags VkSurfaceCreateFlagsOHOS;

வகைவரை கட்டமைப்பு VkSurfaceCreateInfoOHOS {
    VkStructureType             sType;
    மாறிலி வெறுமை*                 pNext;
    VkSurfaceCreateFlagsOHOS    flags;
    OHNativeWindow*             window;
} VkSurfaceCreateInfoOHOS;


வகைவரை VkResult (VKAPI_PTR *PFN_vkCreateSurfaceOHOS)(VkInstance instance, மாறிலி VkSurfaceCreateInfoOHOS* pCreateInfo, மாறிலி VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateSurfaceOHOS(
    VkInstance                                  instance,
    மாறிலி VkSurfaceCreateInfoOHOS*              pCreateInfo,
    மாறிலி VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif
