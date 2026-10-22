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
ಬಾಹ್ಯ "C" {
#endif



// VK_QNX_screen_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_QNX_screen_surface 1

#define VK_QNX_SCREEN_SURFACE_SPEC_VERSION 1
#define VK_QNX_SCREEN_SURFACE_EXTENSION_NAME "VK_QNX_screen_surface"

ಪ್ರಕಾರನಿರ್ದೇಶ VkFlags VkScreenSurfaceCreateFlagsQNX;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkScreenSurfaceCreateInfoQNX {
    VkStructureType                  sType;
    ಧ್ರುವ ಶೂನ್ಯ*                      pNext;
    VkScreenSurfaceCreateFlagsQNX    flags;
    ಸಂರಚನಾ _screen_context*          context;
    ಸಂರಚನಾ _screen_window*           window;
} VkScreenSurfaceCreateInfoQNX;


ಪ್ರಕಾರನಿರ್ದೇಶ VkResult (VKAPI_PTR *PFN_vkCreateScreenSurfaceQNX)(VkInstance instance, ಧ್ರುವ VkScreenSurfaceCreateInfoQNX* pCreateInfo, ಧ್ರುವ VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
ಪ್ರಕಾರನಿರ್ದೇಶ VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceScreenPresentationSupportQNX)(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, ಸಂರಚನಾ _screen_window* window);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateScreenSurfaceQNX(
    VkInstance                                  instance,
    ಧ್ರುವ VkScreenSurfaceCreateInfoQNX*         pCreateInfo,
    ಧ್ರುವ VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceScreenPresentationSupportQNX(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queueFamilyIndex,
    ಸಂರಚನಾ _screen_window*                      window);
#endif
#endif


// VK_QNX_external_memory_screen_buffer is a preprocessor guard. Do not pass it to API calls.
#define VK_QNX_external_memory_screen_buffer 1

#define VK_QNX_EXTERNAL_MEMORY_SCREEN_BUFFER_SPEC_VERSION 1
#define VK_QNX_EXTERNAL_MEMORY_SCREEN_BUFFER_EXTENSION_NAME "VK_QNX_external_memory_screen_buffer"

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkScreenBufferPropertiesQNX {
    VkStructureType    sType;
    ಶೂನ್ಯ*              pNext;
    VkDeviceSize       allocationSize;
    uint32_t           memoryTypeBits;
} VkScreenBufferPropertiesQNX;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkScreenBufferFormatPropertiesQNX {
    VkStructureType                  sType;
    ಶೂನ್ಯ*                            pNext;
    VkFormat                         format;
    uint64_t                         externalFormat;
    uint64_t                         screenUsage;
    VkFormatFeatureFlags             formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggestedXChromaOffset;
    VkChromaLocation                 suggestedYChromaOffset;
} VkScreenBufferFormatPropertiesQNX;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkImportScreenBufferInfoQNX {
    VkStructureType           sType;
    ಧ್ರುವ ಶೂನ್ಯ*               pNext;
    ಸಂರಚನಾ _screen_buffer*    buffer;
} VkImportScreenBufferInfoQNX;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkExternalFormatQNX {
    VkStructureType    sType;
    ಶೂನ್ಯ*              pNext;
    uint64_t           externalFormat;
} VkExternalFormatQNX;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkPhysicalDeviceExternalMemoryScreenBufferFeaturesQNX {
    VkStructureType    sType;
    ಶೂನ್ಯ*              pNext;
    VkBool32           screenBufferImport;
} VkPhysicalDeviceExternalMemoryScreenBufferFeaturesQNX;


ಪ್ರಕಾರನಿರ್ದೇಶ VkResult (VKAPI_PTR *PFN_vkGetScreenBufferPropertiesQNX)(VkDevice device, ಧ್ರುವ ಸಂರಚನಾ _screen_buffer* buffer, VkScreenBufferPropertiesQNX* pProperties);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetScreenBufferPropertiesQNX(
    VkDevice                                    device,
    ಧ್ರುವ ಸಂರಚನಾ _screen_buffer*                buffer,
    VkScreenBufferPropertiesQNX*                pProperties);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif
