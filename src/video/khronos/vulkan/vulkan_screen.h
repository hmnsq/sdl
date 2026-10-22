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
ବାହ୍ୟ "C" {
#endif



// VK_QNX_screen_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_QNX_screen_surface 1

#define VK_QNX_SCREEN_SURFACE_SPEC_VERSION 1
#define VK_QNX_SCREEN_SURFACE_EXTENSION_NAME "VK_QNX_screen_surface"

ପ୍ରକାରବ୍ୟାଖ୍ୟା VkFlags VkScreenSurfaceCreateFlagsQNX;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkScreenSurfaceCreateInfoQNX {
    VkStructureType                  sType;
    ଅଚଳ ଶୂନ୍ୟ*                      pNext;
    VkScreenSurfaceCreateFlagsQNX    flags;
    ସଂରଚନା _screen_context*          context;
    ସଂରଚନା _screen_window*           window;
} VkScreenSurfaceCreateInfoQNX;


ପ୍ରକାରବ୍ୟାଖ୍ୟା VkResult (VKAPI_PTR *PFN_vkCreateScreenSurfaceQNX)(VkInstance instance, ଅଚଳ VkScreenSurfaceCreateInfoQNX* pCreateInfo, ଅଚଳ VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
ପ୍ରକାରବ୍ୟାଖ୍ୟା VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceScreenPresentationSupportQNX)(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, ସଂରଚନା _screen_window* window);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateScreenSurfaceQNX(
    VkInstance                                  instance,
    ଅଚଳ VkScreenSurfaceCreateInfoQNX*         pCreateInfo,
    ଅଚଳ VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceScreenPresentationSupportQNX(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queueFamilyIndex,
    ସଂରଚନା _screen_window*                      window);
#endif
#endif


// VK_QNX_external_memory_screen_buffer is a preprocessor guard. Do not pass it to API calls.
#define VK_QNX_external_memory_screen_buffer 1

#define VK_QNX_EXTERNAL_MEMORY_SCREEN_BUFFER_SPEC_VERSION 1
#define VK_QNX_EXTERNAL_MEMORY_SCREEN_BUFFER_EXTENSION_NAME "VK_QNX_external_memory_screen_buffer"

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkScreenBufferPropertiesQNX {
    VkStructureType    sType;
    ଶୂନ୍ୟ*              pNext;
    VkDeviceSize       allocationSize;
    uint32_t           memoryTypeBits;
} VkScreenBufferPropertiesQNX;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkScreenBufferFormatPropertiesQNX {
    VkStructureType                  sType;
    ଶୂନ୍ୟ*                            pNext;
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

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkImportScreenBufferInfoQNX {
    VkStructureType           sType;
    ଅଚଳ ଶୂନ୍ୟ*               pNext;
    ସଂରଚନା _screen_buffer*    buffer;
} VkImportScreenBufferInfoQNX;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkExternalFormatQNX {
    VkStructureType    sType;
    ଶୂନ୍ୟ*              pNext;
    uint64_t           externalFormat;
} VkExternalFormatQNX;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkPhysicalDeviceExternalMemoryScreenBufferFeaturesQNX {
    VkStructureType    sType;
    ଶୂନ୍ୟ*              pNext;
    VkBool32           screenBufferImport;
} VkPhysicalDeviceExternalMemoryScreenBufferFeaturesQNX;


ପ୍ରକାରବ୍ୟାଖ୍ୟା VkResult (VKAPI_PTR *PFN_vkGetScreenBufferPropertiesQNX)(VkDevice device, ଅଚଳ ସଂରଚନା _screen_buffer* buffer, VkScreenBufferPropertiesQNX* pProperties);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetScreenBufferPropertiesQNX(
    VkDevice                                    device,
    ଅଚଳ ସଂରଚନା _screen_buffer*                buffer,
    VkScreenBufferPropertiesQNX*                pProperties);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif
