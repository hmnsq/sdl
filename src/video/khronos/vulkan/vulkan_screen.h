#که_نه_تعریف_شوی VULKAN_SCREEN_H_
#تعریف_کړه VULKAN_SCREEN_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#که_تعریف_شوی __cplusplus
خارجي "C" {
#د_که_پای



// VK_QNX_screen_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه VK_QNX_screen_surface 1

#تعریف_کړه VK_QNX_SCREEN_SURFACE_SPEC_نسخه 1
#تعریف_کړه VK_QNX_SCREEN_SURFACE_EXTENSION_NAME "VK_QNX_screen_surface"

تعريفنوع VkFlags VkScreenSurfaceCreateFlagsQNX;

تعريفنوع بنية VkScreenSurfaceCreateInfoQNX {
    VkStructureType                  sType;
    ثابت فراغ*                      p_بل;
    VkScreenSurfaceCreateFlagsQNX    flags;
    بنية _screen_context*          context;
    بنية screen_کړکۍ*           کړکۍ;
} VkScreenSurfaceCreateInfoQNX;


تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vkCreateScreenSurfaceQNX)(VkInstance instance, ثابت VkScreenSurfaceCreateInfoQNX* pCreateInfo, ثابت Vk_ویش_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
تعريفنوع VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceScreenPresentationSupportQNX)(VkPhysicalDevice physicalDevice, uint32_t کتار_Family_شاخص, بنية screen_کړکۍ* کړکۍ);

#که_نه_تعریف_شوی VK_NO_PROTOTYPES

#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_پایله VKAPI_CALL vkCreateScreenSurfaceQNX(
    VkInstance                                  instance,
    ثابت VkScreenSurfaceCreateInfoQNX*         pCreateInfo,
    ثابت Vk_ویش_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#د_که_پای
#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceScreenPresentationSupportQNX(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    کتار_Family_شاخص,
    بنية screen_کړکۍ*                      کړکۍ);
#د_که_پای
#د_که_پای


// VK_QNX_external_memory_screen_buffer is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه VK_QNX_external_حافظه_screen_بفر 1

#تعریف_کړه VK_QNX_EXTERNAL_حافظه_SCREEN_بفر_SPEC_نسخه 1
#تعریف_کړه VK_QNX_EXTERNAL_حافظه_SCREEN_بفر_EXTENSION_NAME "VK_QNX_external_memory_screen_buffer"

تعريفنوع بنية Vk_Screen_بفر_Properties_QNX {
    VkStructureType    sType;
    فراغ*              p_بل;
    Vk_Device_اندازه       ویش_اندازه;
    uint32_t           حافظه_Type_بټونه;
} Vk_Screen_بفر_Properties_QNX;

تعريفنوع بنية Vk_Screen_بفر_Format_Properties_QNX {
    VkStructureType                  sType;
    فراغ*                            p_بل;
    VkFormat                         format;
    uint64_t                         externalFormat;
    uint64_t                         screenUsage;
    VkFormatFeatureFlags             formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggested_XChroma_دننه_واټن;
    VkChromaLocation                 suggested_YChroma_دننه_واټن;
} Vk_Screen_بفر_Format_Properties_QNX;

تعريفنوع بنية Vk_Import_Screen_بفر_Info_QNX {
    VkStructureType           sType;
    ثابت فراغ*               p_بل;
    بنية screen_بفر*    بفر_2;
} Vk_Import_Screen_بفر_Info_QNX;

تعريفنوع بنية VkExternalFormatQNX {
    VkStructureType    sType;
    فراغ*              p_بل;
    uint64_t           externalFormat;
} VkExternalFormatQNX;

تعريفنوع بنية Vk_Physical_Device_External_حافظه_Screen_بفر_Features_QNX {
    VkStructureType    sType;
    فراغ*              p_بل;
    VkBool32           screen_بفر_Import;
} Vk_Physical_Device_External_حافظه_Screen_بفر_Features_QNX;


تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vk_Get_Screen_بفر_Properties_QNX)(VkDevice device, ثابت بنية screen_بفر* بفر_2, Vk_Screen_بفر_Properties_QNX* pProperties);

#که_نه_تعریف_شوی VK_NO_PROTOTYPES

#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_پایله VKAPI_CALL vk_Get_Screen_بفر_Properties_QNX(
    VkDevice                                    device,
    ثابت بنية screen_بفر*                بفر_2,
    Vk_Screen_بفر_Properties_QNX*                pProperties);
#د_که_پای
#د_که_پای

#که_تعریف_شوی __cplusplus
}
#د_که_پای

#د_که_پای
