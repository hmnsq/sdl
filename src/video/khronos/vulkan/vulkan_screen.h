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
வெளி "C" {
#endif



// VK_QNX_screen_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_QNX_screen_surface 1

#define VK_QNX_SCREEN_SURFACE_SPEC_VERSION 1
#define VK_QNX_SCREEN_SURFACE_EXTENSION_NAME "VK_QNX_screen_surface"

வகைவரை VkFlags VkScreenSurfaceCreateFlagsQNX;

வகைவரை கட்டமைப்பு VkScreenSurfaceCreateInfoQNX {
    VkStructureType                  sType;
    மாறிலி வெறுமை*                      pNext;
    VkScreenSurfaceCreateFlagsQNX    flags;
    கட்டமைப்பு _screen_context*          context;
    கட்டமைப்பு _screen_window*           window;
} VkScreenSurfaceCreateInfoQNX;


வகைவரை VkResult (VKAPI_PTR *PFN_vkCreateScreenSurfaceQNX)(VkInstance instance, மாறிலி VkScreenSurfaceCreateInfoQNX* pCreateInfo, மாறிலி VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
வகைவரை VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceScreenPresentationSupportQNX)(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, கட்டமைப்பு _screen_window* window);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateScreenSurfaceQNX(
    VkInstance                                  instance,
    மாறிலி VkScreenSurfaceCreateInfoQNX*         pCreateInfo,
    மாறிலி VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceScreenPresentationSupportQNX(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queueFamilyIndex,
    கட்டமைப்பு _screen_window*                      window);
#endif
#endif


// VK_QNX_external_memory_screen_buffer is a preprocessor guard. Do not pass it to API calls.
#define VK_QNX_external_memory_screen_buffer 1

#define VK_QNX_EXTERNAL_MEMORY_SCREEN_BUFFER_SPEC_VERSION 1
#define VK_QNX_EXTERNAL_MEMORY_SCREEN_BUFFER_EXTENSION_NAME "VK_QNX_external_memory_screen_buffer"

வகைவரை கட்டமைப்பு VkScreenBufferPropertiesQNX {
    VkStructureType    sType;
    வெறுமை*              pNext;
    VkDeviceSize       allocationSize;
    uint32_t           memoryTypeBits;
} VkScreenBufferPropertiesQNX;

வகைவரை கட்டமைப்பு VkScreenBufferFormatPropertiesQNX {
    VkStructureType                  sType;
    வெறுமை*                            pNext;
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

வகைவரை கட்டமைப்பு VkImportScreenBufferInfoQNX {
    VkStructureType           sType;
    மாறிலி வெறுமை*               pNext;
    கட்டமைப்பு _screen_buffer*    buffer;
} VkImportScreenBufferInfoQNX;

வகைவரை கட்டமைப்பு VkExternalFormatQNX {
    VkStructureType    sType;
    வெறுமை*              pNext;
    uint64_t           externalFormat;
} VkExternalFormatQNX;

வகைவரை கட்டமைப்பு VkPhysicalDeviceExternalMemoryScreenBufferFeaturesQNX {
    VkStructureType    sType;
    வெறுமை*              pNext;
    VkBool32           screenBufferImport;
} VkPhysicalDeviceExternalMemoryScreenBufferFeaturesQNX;


வகைவரை VkResult (VKAPI_PTR *PFN_vkGetScreenBufferPropertiesQNX)(VkDevice device, மாறிலி கட்டமைப்பு _screen_buffer* buffer, VkScreenBufferPropertiesQNX* pProperties);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetScreenBufferPropertiesQNX(
    VkDevice                                    device,
    மாறிலி கட்டமைப்பு _screen_buffer*                buffer,
    VkScreenBufferPropertiesQNX*                pProperties);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif
