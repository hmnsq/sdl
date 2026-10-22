#جيڪڏهن_وصف_نه_ٿيل VULKAN_SCREEN_H_
#وصف_ڪريو VULKAN_SCREEN_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#جيڪڏهن_وصف_ٿيل __cplusplus
خارجي "C" {
#جيڪڏهن_پورو



// VK_QNX_screen_surface is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو VK_QNX_screen_surface 1

#وصف_ڪريو VK_QNX_SCREEN_SURFACE_SPEC_نسخو 1
#وصف_ڪريو VK_QNX_SCREEN_SURFACE_EXTENSION_NAME "VK_QNX_screen_surface"

تعريفنوع VkFlags VkScreenSurfaceCreateFlagsQNX;

تعريفنوع بنية VkScreenSurfaceCreateInfoQNX {
    VkStructureType                  sType;
    ثابت فراغ*                      p_ايندڙ;
    VkScreenSurfaceCreateFlagsQNX    flags;
    بنية _screen_context*          context;
    بنية screen_دري*           دري;
} VkScreenSurfaceCreateInfoQNX;


تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vkCreateScreenSurfaceQNX)(VkInstance instance, ثابت VkScreenSurfaceCreateInfoQNX* pCreateInfo, ثابت Vk_ورهاست_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
تعريفنوع VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceScreenPresentationSupportQNX)(VkPhysicalDevice physicalDevice, uint32_t قطار_Family_اشاريو, بنية screen_دري* دري);

#جيڪڏهن_وصف_نه_ٿيل VK_NO_PROTOTYPES

#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتيجو VKAPI_CALL vkCreateScreenSurfaceQNX(
    VkInstance                                  instance,
    ثابت VkScreenSurfaceCreateInfoQNX*         pCreateInfo,
    ثابت Vk_ورهاست_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceScreenPresentationSupportQNX(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    قطار_Family_اشاريو,
    بنية screen_دري*                      دري);
#جيڪڏهن_پورو
#جيڪڏهن_پورو


// VK_QNX_external_memory_screen_buffer is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو VK_QNX_external_يادگيري_screen_بفر 1

#وصف_ڪريو VK_QNX_EXTERNAL_يادگيري_SCREEN_بفر_SPEC_نسخو 1
#وصف_ڪريو VK_QNX_EXTERNAL_يادگيري_SCREEN_بفر_EXTENSION_NAME "VK_QNX_external_memory_screen_buffer"

تعريفنوع بنية Vk_Screen_بفر_Properties_QNX {
    VkStructureType    sType;
    فراغ*              p_ايندڙ;
    Vk_Device_سائيز       ورهاست_سائيز;
    uint32_t           يادگيري_Type_بٽ;
} Vk_Screen_بفر_Properties_QNX;

تعريفنوع بنية Vk_Screen_بفر_Format_Properties_QNX {
    VkStructureType                  sType;
    فراغ*                            p_ايندڙ;
    VkFormat                         format;
    uint64_t                         externalFormat;
    uint64_t                         screenUsage;
    VkFormatFeatureFlags             formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggested_XChroma_وٿي;
    VkChromaLocation                 suggested_YChroma_وٿي;
} Vk_Screen_بفر_Format_Properties_QNX;

تعريفنوع بنية Vk_Import_Screen_بفر_Info_QNX {
    VkStructureType           sType;
    ثابت فراغ*               p_ايندڙ;
    بنية screen_بفر*    بفر_2;
} Vk_Import_Screen_بفر_Info_QNX;

تعريفنوع بنية VkExternalFormatQNX {
    VkStructureType    sType;
    فراغ*              p_ايندڙ;
    uint64_t           externalFormat;
} VkExternalFormatQNX;

تعريفنوع بنية Vk_Physical_Device_External_يادگيري_Screen_بفر_Features_QNX {
    VkStructureType    sType;
    فراغ*              p_ايندڙ;
    VkBool32           screen_بفر_Import;
} Vk_Physical_Device_External_يادگيري_Screen_بفر_Features_QNX;


تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vk_Get_Screen_بفر_Properties_QNX)(VkDevice device, ثابت بنية screen_بفر* بفر_2, Vk_Screen_بفر_Properties_QNX* pProperties);

#جيڪڏهن_وصف_نه_ٿيل VK_NO_PROTOTYPES

#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتيجو VKAPI_CALL vk_Get_Screen_بفر_Properties_QNX(
    VkDevice                                    device,
    ثابت بنية screen_بفر*                بفر_2,
    Vk_Screen_بفر_Properties_QNX*                pProperties);
#جيڪڏهن_پورو
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل __cplusplus
}
#جيڪڏهن_پورو

#جيڪڏهن_پورو
