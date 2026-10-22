#ifndef VULKAN_SCREEN_H_
#define VULKAN_SCREEN_H_ 1

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



// VK_QNX_screen_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_QNX_screen_surface 1

#define VK_QNX_SCREEN_SURFACE_SPEC_VERSION 1
#define VK_QNX_SCREEN_SURFACE_EXTENSION_NAME "VK_QNX_screen_surface"

প্রকারলেখ VkFlags VkScreenSurfaceCreateFlagsQNX;

প্রকারলেখ কাঠামো VkScreenSurfaceCreateInfoQNX {
    VkStructureType                  sType;
    ধ্রুবক শূন্য*                      p_পরবর্তী;
    VkScreenSurfaceCreateFlagsQNX    flags;
    কাঠামো _screen_context*          context;
    কাঠামো _screen_window*           window;
} VkScreenSurfaceCreateInfoQNX;


প্রকারলেখ Vk_ফলাফল (VKAPI_PTR *PFN_vkCreateScreenSurfaceQNX)(VkInstance instance, ধ্রুবক VkScreenSurfaceCreateInfoQNX* pCreateInfo, ধ্রুবক VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
প্রকারলেখ VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceScreenPresentationSupportQNX)(VkPhysicalDevice physicalDevice, uint32_t queue_Family_সূচক, কাঠামো _screen_window* window);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ফলাফল VKAPI_CALL vkCreateScreenSurfaceQNX(
    VkInstance                                  instance,
    ধ্রুবক VkScreenSurfaceCreateInfoQNX*         pCreateInfo,
    ধ্রুবক VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceScreenPresentationSupportQNX(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queue_Family_সূচক,
    কাঠামো _screen_window*                      window);
#endif
#endif


// VK_QNX_external_memory_screen_buffer is a preprocessor guard. Do not pass it to API calls.
#define VK_QNX_external_memory_screen_বাফার 1

#define VK_QNX_EXTERNAL_MEMORY_SCREEN_বাফার_SPEC_VERSION 1
#define VK_QNX_EXTERNAL_MEMORY_SCREEN_বাফার_EXTENSION_NAME "VK_QNX_external_memory_screen_buffer"

প্রকারলেখ কাঠামো Vk_Screen_বাফার_Properties_QNX {
    VkStructureType    sType;
    শূন্য*              p_পরবর্তী;
    Vk_Device_আকার       allocation_আকার;
    uint32_t           memoryTypeBits;
} Vk_Screen_বাফার_Properties_QNX;

প্রকারলেখ কাঠামো Vk_Screen_বাফার_Format_Properties_QNX {
    VkStructureType                  sType;
    শূন্য*                            p_পরবর্তী;
    VkFormat                         format;
    uint64_t                         externalFormat;
    uint64_t                         screenUsage;
    VkFormatFeatureFlags             formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggestedXChromaOffset;
    VkChromaLocation                 suggestedYChromaOffset;
} Vk_Screen_বাফার_Format_Properties_QNX;

প্রকারলেখ কাঠামো Vk_Import_Screen_বাফার_Info_QNX {
    VkStructureType           sType;
    ধ্রুবক শূন্য*               p_পরবর্তী;
    কাঠামো screen_বাফার*    বাফার_2;
} Vk_Import_Screen_বাফার_Info_QNX;

প্রকারলেখ কাঠামো VkExternalFormatQNX {
    VkStructureType    sType;
    শূন্য*              p_পরবর্তী;
    uint64_t           externalFormat;
} VkExternalFormatQNX;

প্রকারলেখ কাঠামো Vk_Physical_Device_External_Memory_Screen_বাফার_Features_QNX {
    VkStructureType    sType;
    শূন্য*              p_পরবর্তী;
    VkBool32           screen_বাফার_Import;
} Vk_Physical_Device_External_Memory_Screen_বাফার_Features_QNX;


প্রকারলেখ Vk_ফলাফল (VKAPI_PTR *PFN_vk_Get_Screen_বাফার_Properties_QNX)(VkDevice device, ধ্রুবক কাঠামো screen_বাফার* বাফার_2, Vk_Screen_বাফার_Properties_QNX* pProperties);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ফলাফল VKAPI_CALL vk_Get_Screen_বাফার_Properties_QNX(
    VkDevice                                    device,
    ধ্রুবক কাঠামো screen_বাফার*                বাফার_2,
    Vk_Screen_বাফার_Properties_QNX*                pProperties);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif
