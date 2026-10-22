#यदि_अपरिभाषितम् VULKAN_SCREEN_H_
#परिभाषय VULKAN_SCREEN_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#यदि_परिभाषितम् __cplusplus
बाह्य "C" {
#यदि_अन्तः



// VK_QNX_screen_surface is a preprocessor guard. Do not pass it to API calls.
#परिभाषय VK_QNX_screen_surface 1

#परिभाषय VK_QNX_SCREEN_SURFACE_SPEC_संस्करणम् 1
#परिभाषय VK_QNX_SCREEN_SURFACE_EXTENSION_NAME "VK_QNX_screen_surface"

प्रकारनिर्देश VkFlags VkScreenSurfaceCreateFlagsQNX;

प्रकारनिर्देश संरचना VkScreenSurfaceCreateInfoQNX {
    VkStructureType                  sType;
    ध्रुव शून्य*                      p_अग्र;
    VkScreenSurfaceCreateFlagsQNX    flags;
    संरचना _screen_context*          context;
    संरचना screen_गवाक्षः*           गवाक्षः;
} VkScreenSurfaceCreateInfoQNX;


प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vkCreateScreenSurfaceQNX)(VkInstance instance, ध्रुव VkScreenSurfaceCreateInfoQNX* pCreateInfo, ध्रुव Vk_आवण्टनम्_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
प्रकारनिर्देश VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceScreenPresentationSupportQNX)(VkPhysicalDevice physicalDevice, uint32_t queue_Family_सूचकांक, संरचना screen_गवाक्षः* गवाक्षः);

#यदि_अपरिभाषितम् VK_NO_PROTOTYPES

#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkCreateScreenSurfaceQNX(
    VkInstance                                  instance,
    ध्रुव VkScreenSurfaceCreateInfoQNX*         pCreateInfo,
    ध्रुव Vk_आवण्टनम्_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#यदि_अन्तः
#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceScreenPresentationSupportQNX(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queue_Family_सूचकांक,
    संरचना screen_गवाक्षः*                      गवाक्षः);
#यदि_अन्तः
#यदि_अन्तः


// VK_QNX_external_memory_screen_buffer is a preprocessor guard. Do not pass it to API calls.
#परिभाषय VK_QNX_external_स्मृतिः_screen_बफर 1

#परिभाषय VK_QNX_EXTERNAL_स्मृतिः_SCREEN_बफर_SPEC_संस्करणम् 1
#परिभाषय VK_QNX_EXTERNAL_स्मृतिः_SCREEN_बफर_EXTENSION_NAME "VK_QNX_external_memory_screen_buffer"

प्रकारनिर्देश संरचना Vk_Screen_बफर_Properties_QNX {
    VkStructureType    sType;
    शून्य*              p_अग्र;
    Vk_Device_आकार       आवण्टनम्_आकार;
    uint32_t           स्मृतिः_Type_द्वयङ्काः;
} Vk_Screen_बफर_Properties_QNX;

प्रकारनिर्देश संरचना Vk_Screen_बफर_Format_Properties_QNX {
    VkStructureType                  sType;
    शून्य*                            p_अग्र;
    VkFormat                         format;
    uint64_t                         externalFormat;
    uint64_t                         screenUsage;
    VkFormatFeatureFlags             formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggested_XChroma_विस्थापनम्;
    VkChromaLocation                 suggested_YChroma_विस्थापनम्;
} Vk_Screen_बफर_Format_Properties_QNX;

प्रकारनिर्देश संरचना Vk_Import_Screen_बफर_Info_QNX {
    VkStructureType           sType;
    ध्रुव शून्य*               p_अग्र;
    संरचना screen_बफर*    बफर_2;
} Vk_Import_Screen_बफर_Info_QNX;

प्रकारनिर्देश संरचना VkExternalFormatQNX {
    VkStructureType    sType;
    शून्य*              p_अग्र;
    uint64_t           externalFormat;
} VkExternalFormatQNX;

प्रकारनिर्देश संरचना Vk_Physical_Device_External_स्मृतिः_Screen_बफर_Features_QNX {
    VkStructureType    sType;
    शून्य*              p_अग्र;
    VkBool32           screen_बफर_Import;
} Vk_Physical_Device_External_स्मृतिः_Screen_बफर_Features_QNX;


प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vk_Get_Screen_बफर_Properties_QNX)(VkDevice device, ध्रुव संरचना screen_बफर* बफर_2, Vk_Screen_बफर_Properties_QNX* pProperties);

#यदि_अपरिभाषितम् VK_NO_PROTOTYPES

#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vk_Get_Screen_बफर_Properties_QNX(
    VkDevice                                    device,
    ध्रुव संरचना screen_बफर*                बफर_2,
    Vk_Screen_बफर_Properties_QNX*                pProperties);
#यदि_अन्तः
#यदि_अन्तः

#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

#यदि_अन्तः
