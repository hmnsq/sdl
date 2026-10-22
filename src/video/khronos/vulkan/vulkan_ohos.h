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
বাহ্যিক "C" {
#endif



// VK_OHOS_external_memory is a preprocessor guard. Do not pass it to API calls.
#define VK_OHOS_external_memory 1

কাঠামো OH_Native_বাফার;

#define VK_OHOS_EXTERNAL_MEMORY_SPEC_VERSION 1
#define VK_OHOS_EXTERNAL_MEMORY_EXTENSION_NAME "VK_OHOS_external_memory"

প্রকারলেখ কাঠামো Vk_Native_বাফার_Usage_OHOS {
    VkStructureType    sType;
    শূন্য*              p_পরবর্তী;
    uint64_t           OHOSNative_বাফার_Usage;
} Vk_Native_বাফার_Usage_OHOS;

প্রকারলেখ কাঠামো Vk_Native_বাফার_Properties_OHOS {
    VkStructureType    sType;
    শূন্য*              p_পরবর্তী;
    Vk_Device_আকার       allocation_আকার;
    uint32_t           memoryTypeBits;
} Vk_Native_বাফার_Properties_OHOS;

প্রকারলেখ কাঠামো Vk_Native_বাফার_Format_Properties_OHOS {
    VkStructureType                  sType;
    শূন্য*                            p_পরবর্তী;
    VkFormat                         format;
    uint64_t                         externalFormat;
    VkFormatFeatureFlags             formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggestedXChromaOffset;
    VkChromaLocation                 suggestedYChromaOffset;
} Vk_Native_বাফার_Format_Properties_OHOS;

প্রকারলেখ কাঠামো Vk_Import_Native_বাফার_Info_OHOS {
    VkStructureType            sType;
    ধ্রুবক শূন্য*                p_পরবর্তী;
    কাঠামো OH_Native_বাফার*    বাফার_2;
} Vk_Import_Native_বাফার_Info_OHOS;

প্রকারলেখ কাঠামো Vk_Memory_Get_Native_বাফার_Info_OHOS {
    VkStructureType    sType;
    ধ্রুবক শূন্য*        p_পরবর্তী;
    VkDeviceMemory     memory;
} Vk_Memory_Get_Native_বাফার_Info_OHOS;

প্রকারলেখ কাঠামো VkExternalFormatOHOS {
    VkStructureType    sType;
    শূন্য*              p_পরবর্তী;
    uint64_t           externalFormat;
} VkExternalFormatOHOS;


প্রকারলেখ Vk_ফলাফল (VKAPI_PTR *PFN_vk_Get_Native_বাফার_Properties_OHOS)(VkDevice device, ধ্রুবক কাঠামো OH_Native_বাফার* বাফার_2, Vk_Native_বাফার_Properties_OHOS* pProperties);
প্রকারলেখ Vk_ফলাফল (VKAPI_PTR *PFN_vk_Get_Memory_Native_বাফার_OHOS)(VkDevice device, ধ্রুবক Vk_Memory_Get_Native_বাফার_Info_OHOS* pInfo, কাঠামো OH_Native_বাফার** p_বাফার);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ফলাফল VKAPI_CALL vk_Get_Native_বাফার_Properties_OHOS(
    VkDevice                                    device,
    ধ্রুবক কাঠামো OH_Native_বাফার*               বাফার_2,
    Vk_Native_বাফার_Properties_OHOS*               pProperties);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ফলাফল VKAPI_CALL vk_Get_Memory_Native_বাফার_OHOS(
    VkDevice                                    device,
    ধ্রুবক Vk_Memory_Get_Native_বাফার_Info_OHOS*      pInfo,
    কাঠামো OH_Native_বাফার**                    p_বাফার);
#endif
#endif


// VK_OHOS_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_OHOS_surface 1

প্রকারলেখ কাঠামো NativeWindow OHNativeWindow;

#define VK_OHOS_SURFACE_SPEC_VERSION      1
#define VK_OHOS_SURFACE_EXTENSION_NAME    "VK_OHOS_surface"

প্রকারলেখ VkFlags VkSurfaceCreateFlagsOHOS;

প্রকারলেখ কাঠামো VkSurfaceCreateInfoOHOS {
    VkStructureType             sType;
    ধ্রুবক শূন্য*                 p_পরবর্তী;
    VkSurfaceCreateFlagsOHOS    flags;
    OHNativeWindow*             window;
} VkSurfaceCreateInfoOHOS;


প্রকারলেখ Vk_ফলাফল (VKAPI_PTR *PFN_vkCreateSurfaceOHOS)(VkInstance instance, ধ্রুবক VkSurfaceCreateInfoOHOS* pCreateInfo, ধ্রুবক VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ফলাফল VKAPI_CALL vkCreateSurfaceOHOS(
    VkInstance                                  instance,
    ধ্রুবক VkSurfaceCreateInfoOHOS*              pCreateInfo,
    ধ্রুবক VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif
