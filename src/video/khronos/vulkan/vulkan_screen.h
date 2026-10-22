#اگر_غیر_تعریف_شدہ VULKAN_SCREEN_H_
#تعریف_کرو VULKAN_SCREEN_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#اگر_تعریف_شدہ __cplusplus
خارجی "C" {
#اگر_ختم



// VK_QNX_screen_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_QNX_screen_surface 1

#تعریف_کرو VK_QNX_SCREEN_SURFACE_SPEC_نسخہ 1
#تعریف_کرو VK_QNX_SCREEN_SURFACE_EXTENSION_NAME "VK_QNX_screen_surface"

قسمتعریف VkFlags VkScreenSurfaceCreateFlagsQNX;

قسمتعریف ساخت VkScreenSurfaceCreateInfoQNX {
    VkStructureType                  sType;
    ثابت خالی*                      p_اگلا;
    VkScreenSurfaceCreateFlagsQNX    flags;
    ساخت _screen_context*          context;
    ساخت screen_کھڑکی*           کھڑکی;
} VkScreenSurfaceCreateInfoQNX;


قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vkCreateScreenSurfaceQNX)(VkInstance instance, ثابت VkScreenSurfaceCreateInfoQNX* pCreateInfo, ثابت Vk_تخصیص_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
قسمتعریف VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceScreenPresentationSupportQNX)(VkPhysicalDevice physicalDevice, uint32_t قطار_Family_اشاریہ, ساخت screen_کھڑکی* کھڑکی);

#اگر_غیر_تعریف_شدہ VK_NO_PROTOTYPES

#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vkCreateScreenSurfaceQNX(
    VkInstance                                  instance,
    ثابت VkScreenSurfaceCreateInfoQNX*         pCreateInfo,
    ثابت Vk_تخصیص_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#اگر_ختم
#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceScreenPresentationSupportQNX(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    قطار_Family_اشاریہ,
    ساخت screen_کھڑکی*                      کھڑکی);
#اگر_ختم
#اگر_ختم


// VK_QNX_external_memory_screen_buffer is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_QNX_external_حافظہ_screen_بفر 1

#تعریف_کرو VK_QNX_EXTERNAL_حافظہ_SCREEN_بفر_SPEC_نسخہ 1
#تعریف_کرو VK_QNX_EXTERNAL_حافظہ_SCREEN_بفر_EXTENSION_NAME "VK_QNX_external_memory_screen_buffer"

قسمتعریف ساخت Vk_Screen_بفر_Properties_QNX {
    VkStructureType    sType;
    خالی*              p_اگلا;
    Vk_Device_سائز       تخصیص_سائز;
    uint32_t           حافظہ_Type_بٹ;
} Vk_Screen_بفر_Properties_QNX;

قسمتعریف ساخت Vk_Screen_بفر_Format_Properties_QNX {
    VkStructureType                  sType;
    خالی*                            p_اگلا;
    VkFormat                         format;
    uint64_t                         externalFormat;
    uint64_t                         screenUsage;
    VkFormatFeatureFlags             formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggested_XChroma_انحراف;
    VkChromaLocation                 suggested_YChroma_انحراف;
} Vk_Screen_بفر_Format_Properties_QNX;

قسمتعریف ساخت Vk_Import_Screen_بفر_Info_QNX {
    VkStructureType           sType;
    ثابت خالی*               p_اگلا;
    ساخت screen_بفر*    بفر_2;
} Vk_Import_Screen_بفر_Info_QNX;

قسمتعریف ساخت VkExternalFormatQNX {
    VkStructureType    sType;
    خالی*              p_اگلا;
    uint64_t           externalFormat;
} VkExternalFormatQNX;

قسمتعریف ساخت Vk_Physical_Device_External_حافظہ_Screen_بفر_Features_QNX {
    VkStructureType    sType;
    خالی*              p_اگلا;
    VkBool32           screen_بفر_Import;
} Vk_Physical_Device_External_حافظہ_Screen_بفر_Features_QNX;


قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vk_Get_Screen_بفر_Properties_QNX)(VkDevice device, ثابت ساخت screen_بفر* بفر_2, Vk_Screen_بفر_Properties_QNX* pProperties);

#اگر_غیر_تعریف_شدہ VK_NO_PROTOTYPES

#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_Get_Screen_بفر_Properties_QNX(
    VkDevice                                    device,
    ثابت ساخت screen_بفر*                بفر_2,
    Vk_Screen_بفر_Properties_QNX*                pProperties);
#اگر_ختم
#اگر_ختم

#اگر_تعریف_شدہ __cplusplus
}
#اگر_ختم

#اگر_ختم
