#अगर_अघोषित VULKAN_SCREEN_H_
#घोषणा VULKAN_SCREEN_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#अगर_घोषित __cplusplus
बाह्य "C" {
#पूर्ण_अगर



// VK_QNX_screen_surface is a preprocessor guard. Do not pass it to API calls.
#घोषणा VK_QNX_screen_surface 1

#घोषणा VK_QNX_SCREEN_SURFACE_SPEC_VERSION 1
#घोषणा VK_QNX_SCREEN_SURFACE_EXTENSION_NAME "VK_QNX_screen_surface"

प्रकार VkFlags VkScreenSurfaceCreateFlagsQNX;

प्रकार काष्ठा VkScreenSurfaceCreateInfoQNX {
    VkStructureType                  sType;
    स्थिर व्योम*                      p_अग्र;
    VkScreenSurfaceCreateFlagsQNX    flags;
    काष्ठा _screen_context*          context;
    काष्ठा _screen_window*           window;
} VkScreenSurfaceCreateInfoQNX;


प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vkCreateScreenSurfaceQNX)(VkInstance instance, स्थिर VkScreenSurfaceCreateInfoQNX* pCreateInfo, स्थिर VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
प्रकार VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceScreenPresentationSupportQNX)(VkPhysicalDevice physicalDevice, uint32_t queue_Family_सूचकांक, काष्ठा _screen_window* window);

#अगर_अघोषित VK_NO_PROTOTYPES

#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkCreateScreenSurfaceQNX(
    VkInstance                                  instance,
    स्थिर VkScreenSurfaceCreateInfoQNX*         pCreateInfo,
    स्थिर VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#पूर्ण_अगर
#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceScreenPresentationSupportQNX(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queue_Family_सूचकांक,
    काष्ठा _screen_window*                      window);
#पूर्ण_अगर
#पूर्ण_अगर


// VK_QNX_external_memory_screen_buffer is a preprocessor guard. Do not pass it to API calls.
#घोषणा VK_QNX_external_memory_screen_बफर 1

#घोषणा VK_QNX_EXTERNAL_MEMORY_SCREEN_बफर_SPEC_VERSION 1
#घोषणा VK_QNX_EXTERNAL_MEMORY_SCREEN_बफर_EXTENSION_NAME "VK_QNX_external_memory_screen_buffer"

प्रकार काष्ठा Vk_Screen_बफर_Properties_QNX {
    VkStructureType    sType;
    व्योम*              p_अग्र;
    Vk_Device_आकार       allocation_आकार;
    uint32_t           memoryTypeBits;
} Vk_Screen_बफर_Properties_QNX;

प्रकार काष्ठा Vk_Screen_बफर_Format_Properties_QNX {
    VkStructureType                  sType;
    व्योम*                            p_अग्र;
    VkFormat                         format;
    uint64_t                         externalFormat;
    uint64_t                         screenUsage;
    VkFormatFeatureFlags             formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggestedXChromaOffset;
    VkChromaLocation                 suggestedYChromaOffset;
} Vk_Screen_बफर_Format_Properties_QNX;

प्रकार काष्ठा Vk_Import_Screen_बफर_Info_QNX {
    VkStructureType           sType;
    स्थिर व्योम*               p_अग्र;
    काष्ठा screen_बफर*    बफर_2;
} Vk_Import_Screen_बफर_Info_QNX;

प्रकार काष्ठा VkExternalFormatQNX {
    VkStructureType    sType;
    व्योम*              p_अग्र;
    uint64_t           externalFormat;
} VkExternalFormatQNX;

प्रकार काष्ठा Vk_Physical_Device_External_Memory_Screen_बफर_Features_QNX {
    VkStructureType    sType;
    व्योम*              p_अग्र;
    VkBool32           screen_बफर_Import;
} Vk_Physical_Device_External_Memory_Screen_बफर_Features_QNX;


प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vk_Get_Screen_बफर_Properties_QNX)(VkDevice device, स्थिर काष्ठा screen_बफर* बफर_2, Vk_Screen_बफर_Properties_QNX* pProperties);

#अगर_अघोषित VK_NO_PROTOTYPES

#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vk_Get_Screen_बफर_Properties_QNX(
    VkDevice                                    device,
    स्थिर काष्ठा screen_बफर*                बफर_2,
    Vk_Screen_बफर_Properties_QNX*                pProperties);
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_घोषित __cplusplus
}
#पूर्ण_अगर

#पूर्ण_अगर
