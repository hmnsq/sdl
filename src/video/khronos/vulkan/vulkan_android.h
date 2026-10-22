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
বাহ্যিক "C" {
#endif



// VK_KHR_android_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_android_surface 1

কাঠামো ANativeWindow;

#define VK_KHR_ANDROID_SURFACE_SPEC_VERSION 6
#define VK_KHR_ANDROID_SURFACE_EXTENSION_NAME "VK_KHR_android_surface"

প্রকারলেখ VkFlags VkAndroidSurfaceCreateFlagsKHR;

প্রকারলেখ কাঠামো VkAndroidSurfaceCreateInfoKHR {
    VkStructureType                   sType;
    ধ্রুবক শূন্য*                       p_পরবর্তী;
    VkAndroidSurfaceCreateFlagsKHR    flags;
    কাঠামো ANativeWindow*             window;
} VkAndroidSurfaceCreateInfoKHR;


প্রকারলেখ Vk_ফলাফল (VKAPI_PTR *PFN_vkCreateAndroidSurfaceKHR)(VkInstance instance, ধ্রুবক VkAndroidSurfaceCreateInfoKHR* pCreateInfo, ধ্রুবক VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ফলাফল VKAPI_CALL vkCreateAndroidSurfaceKHR(
    VkInstance                                  instance,
    ধ্রুবক VkAndroidSurfaceCreateInfoKHR*        pCreateInfo,
    ধ্রুবক VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#endif


// VK_ANDROID_external_memory_android_hardware_buffer is a preprocessor guard. Do not pass it to API calls.
#define VK_ANDROID_external_memory_android_hardware_বাফার 1

কাঠামো AHardware_বাফার;

#define VK_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_বাফার_SPEC_VERSION 5
#define VK_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_বাফার_EXTENSION_NAME "VK_ANDROID_external_memory_android_hardware_buffer"

প্রকারলেখ কাঠামো Vk_Android_Hardware_বাফার_Usage_ANDROID {
    VkStructureType    sType;
    শূন্য*              p_পরবর্তী;
    uint64_t           android_Hardware_বাফার_Usage;
} Vk_Android_Hardware_বাফার_Usage_ANDROID;

প্রকারলেখ কাঠামো Vk_Android_Hardware_বাফার_Properties_ANDROID {
    VkStructureType    sType;
    শূন্য*              p_পরবর্তী;
    Vk_Device_আকার       allocation_আকার;
    uint32_t           memoryTypeBits;
} Vk_Android_Hardware_বাফার_Properties_ANDROID;

প্রকারলেখ কাঠামো Vk_Android_Hardware_বাফার_Format_Properties_ANDROID {
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
} Vk_Android_Hardware_বাফার_Format_Properties_ANDROID;

প্রকারলেখ কাঠামো Vk_Import_Android_Hardware_বাফার_Info_ANDROID {
    VkStructureType            sType;
    ধ্রুবক শূন্য*                p_পরবর্তী;
    কাঠামো AHardware_বাফার*    বাফার_2;
} Vk_Import_Android_Hardware_বাফার_Info_ANDROID;

প্রকারলেখ কাঠামো Vk_Memory_Get_Android_Hardware_বাফার_Info_ANDROID {
    VkStructureType    sType;
    ধ্রুবক শূন্য*        p_পরবর্তী;
    VkDeviceMemory     memory;
} Vk_Memory_Get_Android_Hardware_বাফার_Info_ANDROID;

প্রকারলেখ কাঠামো VkExternalFormatANDROID {
    VkStructureType    sType;
    শূন্য*              p_পরবর্তী;
    uint64_t           externalFormat;
} VkExternalFormatANDROID;

প্রকারলেখ কাঠামো Vk_Android_Hardware_বাফার_Format_Properties2_ANDROID {
    VkStructureType                  sType;
    শূন্য*                            p_পরবর্তী;
    VkFormat                         format;
    uint64_t                         externalFormat;
    VkFormatFeatureFlags2            formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggestedXChromaOffset;
    VkChromaLocation                 suggestedYChromaOffset;
} Vk_Android_Hardware_বাফার_Format_Properties2_ANDROID;


প্রকারলেখ Vk_ফলাফল (VKAPI_PTR *PFN_vk_Get_Android_Hardware_বাফার_Properties_ANDROID)(VkDevice device, ধ্রুবক কাঠামো AHardware_বাফার* বাফার_2, Vk_Android_Hardware_বাফার_Properties_ANDROID* pProperties);
প্রকারলেখ Vk_ফলাফল (VKAPI_PTR *PFN_vk_Get_Memory_Android_Hardware_বাফার_ANDROID)(VkDevice device, ধ্রুবক Vk_Memory_Get_Android_Hardware_বাফার_Info_ANDROID* pInfo, কাঠামো AHardware_বাফার** p_বাফার);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ফলাফল VKAPI_CALL vk_Get_Android_Hardware_বাফার_Properties_ANDROID(
    VkDevice                                    device,
    ধ্রুবক কাঠামো AHardware_বাফার*               বাফার_2,
    Vk_Android_Hardware_বাফার_Properties_ANDROID*   pProperties);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ফলাফল VKAPI_CALL vk_Get_Memory_Android_Hardware_বাফার_ANDROID(
    VkDevice                                    device,
    ধ্রুবক Vk_Memory_Get_Android_Hardware_বাফার_Info_ANDROID* pInfo,
    কাঠামো AHardware_বাফার**                    p_বাফার);
#endif
#endif


// VK_ANDROID_external_format_resolve is a preprocessor guard. Do not pass it to API calls.
#define VK_ANDROID_external_format_resolve 1

#define VK_ANDROID_EXTERNAL_FORMAT_RESOLVE_SPEC_VERSION 1
#define VK_ANDROID_EXTERNAL_FORMAT_RESOLVE_EXTENSION_NAME "VK_ANDROID_external_format_resolve"

প্রকারলেখ কাঠামো VkPhysicalDeviceExternalFormatResolveFeaturesANDROID {
    VkStructureType    sType;
    শূন্য*              p_পরবর্তী;
    VkBool32           externalFormatResolve;
} VkPhysicalDeviceExternalFormatResolveFeaturesANDROID;

প্রকারলেখ কাঠামো VkPhysicalDeviceExternalFormatResolvePropertiesANDROID {
    VkStructureType     sType;
    শূন্য*               p_পরবর্তী;
    VkBool32            nullColorAttachmentWithExternalFormatResolve;
    VkChromaLocation    externalFormatResolveChromaOffsetX;
    VkChromaLocation    externalFormatResolveChromaOffsetY;
} VkPhysicalDeviceExternalFormatResolvePropertiesANDROID;

প্রকারলেখ কাঠামো Vk_Android_Hardware_বাফার_Format_Resolve_Properties_ANDROID {
    VkStructureType    sType;
    শূন্য*              p_পরবর্তী;
    VkFormat           colorAttachmentFormat;
} Vk_Android_Hardware_বাফার_Format_Resolve_Properties_ANDROID;


#ifdef __cplusplus
}
#endif

#endif
