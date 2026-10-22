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
बाह्य "C" {
#endif



// VK_QNX_screen_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_QNX_screen_surface 1

#define VK_QNX_SCREEN_SURFACE_SPEC_VERSION 1
#define VK_QNX_SCREEN_SURFACE_EXTENSION_NAME "VK_QNX_screen_surface"

प्रकारव्याख्या VkFlags VkScreenSurfaceCreateFlagsQNX;

प्रकारव्याख्या संरचना VkScreenSurfaceCreateInfoQNX {
    VkStructureType                  sType;
    स्थिरांक शून्य*                      pNext;
    VkScreenSurfaceCreateFlagsQNX    flags;
    संरचना _screen_context*          context;
    संरचना _screen_window*           window;
} VkScreenSurfaceCreateInfoQNX;


प्रकारव्याख्या VkResult (VKAPI_PTR *PFN_vkCreateScreenSurfaceQNX)(VkInstance instance, स्थिरांक VkScreenSurfaceCreateInfoQNX* pCreateInfo, स्थिरांक VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
प्रकारव्याख्या VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceScreenPresentationSupportQNX)(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, संरचना _screen_window* window);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateScreenSurfaceQNX(
    VkInstance                                  instance,
    स्थिरांक VkScreenSurfaceCreateInfoQNX*         pCreateInfo,
    स्थिरांक VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceScreenPresentationSupportQNX(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queueFamilyIndex,
    संरचना _screen_window*                      window);
#endif
#endif


// VK_QNX_external_memory_screen_buffer is a preprocessor guard. Do not pass it to API calls.
#define VK_QNX_external_memory_screen_buffer 1

#define VK_QNX_EXTERNAL_MEMORY_SCREEN_BUFFER_SPEC_VERSION 1
#define VK_QNX_EXTERNAL_MEMORY_SCREEN_BUFFER_EXTENSION_NAME "VK_QNX_external_memory_screen_buffer"

प्रकारव्याख्या संरचना VkScreenBufferPropertiesQNX {
    VkStructureType    sType;
    शून्य*              pNext;
    VkDeviceSize       allocationSize;
    uint32_t           memoryTypeBits;
} VkScreenBufferPropertiesQNX;

प्रकारव्याख्या संरचना VkScreenBufferFormatPropertiesQNX {
    VkStructureType                  sType;
    शून्य*                            pNext;
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

प्रकारव्याख्या संरचना VkImportScreenBufferInfoQNX {
    VkStructureType           sType;
    स्थिरांक शून्य*               pNext;
    संरचना _screen_buffer*    buffer;
} VkImportScreenBufferInfoQNX;

प्रकारव्याख्या संरचना VkExternalFormatQNX {
    VkStructureType    sType;
    शून्य*              pNext;
    uint64_t           externalFormat;
} VkExternalFormatQNX;

प्रकारव्याख्या संरचना VkPhysicalDeviceExternalMemoryScreenBufferFeaturesQNX {
    VkStructureType    sType;
    शून्य*              pNext;
    VkBool32           screenBufferImport;
} VkPhysicalDeviceExternalMemoryScreenBufferFeaturesQNX;


प्रकारव्याख्या VkResult (VKAPI_PTR *PFN_vkGetScreenBufferPropertiesQNX)(VkDevice device, स्थिरांक संरचना _screen_buffer* buffer, VkScreenBufferPropertiesQNX* pProperties);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetScreenBufferPropertiesQNX(
    VkDevice                                    device,
    स्थिरांक संरचना _screen_buffer*                buffer,
    VkScreenBufferPropertiesQNX*                pProperties);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif
