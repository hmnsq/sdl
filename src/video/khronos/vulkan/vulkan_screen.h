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
બાહ્ય "C" {
#endif



// VK_QNX_screen_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_QNX_screen_surface 1

#define VK_QNX_SCREEN_SURFACE_SPEC_VERSION 1
#define VK_QNX_SCREEN_SURFACE_EXTENSION_NAME "VK_QNX_screen_surface"

પ્રકારવ્યાખ્યા VkFlags VkScreenSurfaceCreateFlagsQNX;

પ્રકારવ્યાખ્યા સંરચના VkScreenSurfaceCreateInfoQNX {
    VkStructureType                  sType;
    અચલ શૂન્ય*                      pNext;
    VkScreenSurfaceCreateFlagsQNX    flags;
    સંરચના _screen_context*          context;
    સંરચના _screen_window*           window;
} VkScreenSurfaceCreateInfoQNX;


પ્રકારવ્યાખ્યા VkResult (VKAPI_PTR *PFN_vkCreateScreenSurfaceQNX)(VkInstance instance, અચલ VkScreenSurfaceCreateInfoQNX* pCreateInfo, અચલ VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
પ્રકારવ્યાખ્યા VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceScreenPresentationSupportQNX)(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, સંરચના _screen_window* window);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateScreenSurfaceQNX(
    VkInstance                                  instance,
    અચલ VkScreenSurfaceCreateInfoQNX*         pCreateInfo,
    અચલ VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceScreenPresentationSupportQNX(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queueFamilyIndex,
    સંરચના _screen_window*                      window);
#endif
#endif


// VK_QNX_external_memory_screen_buffer is a preprocessor guard. Do not pass it to API calls.
#define VK_QNX_external_memory_screen_buffer 1

#define VK_QNX_EXTERNAL_MEMORY_SCREEN_BUFFER_SPEC_VERSION 1
#define VK_QNX_EXTERNAL_MEMORY_SCREEN_BUFFER_EXTENSION_NAME "VK_QNX_external_memory_screen_buffer"

પ્રકારવ્યાખ્યા સંરચના VkScreenBufferPropertiesQNX {
    VkStructureType    sType;
    શૂન્ય*              pNext;
    VkDeviceSize       allocationSize;
    uint32_t           memoryTypeBits;
} VkScreenBufferPropertiesQNX;

પ્રકારવ્યાખ્યા સંરચના VkScreenBufferFormatPropertiesQNX {
    VkStructureType                  sType;
    શૂન્ય*                            pNext;
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

પ્રકારવ્યાખ્યા સંરચના VkImportScreenBufferInfoQNX {
    VkStructureType           sType;
    અચલ શૂન્ય*               pNext;
    સંરચના _screen_buffer*    buffer;
} VkImportScreenBufferInfoQNX;

પ્રકારવ્યાખ્યા સંરચના VkExternalFormatQNX {
    VkStructureType    sType;
    શૂન્ય*              pNext;
    uint64_t           externalFormat;
} VkExternalFormatQNX;

પ્રકારવ્યાખ્યા સંરચના VkPhysicalDeviceExternalMemoryScreenBufferFeaturesQNX {
    VkStructureType    sType;
    શૂન્ય*              pNext;
    VkBool32           screenBufferImport;
} VkPhysicalDeviceExternalMemoryScreenBufferFeaturesQNX;


પ્રકારવ્યાખ્યા VkResult (VKAPI_PTR *PFN_vkGetScreenBufferPropertiesQNX)(VkDevice device, અચલ સંરચના _screen_buffer* buffer, VkScreenBufferPropertiesQNX* pProperties);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetScreenBufferPropertiesQNX(
    VkDevice                                    device,
    અચલ સંરચના _screen_buffer*                buffer,
    VkScreenBufferPropertiesQNX*                pProperties);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif
