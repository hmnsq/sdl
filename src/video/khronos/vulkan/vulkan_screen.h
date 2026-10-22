#جے_بنا_تعریف VULKAN_SCREEN_H_
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


#جے_تعریف_شدہ __cplusplus
خارجي "C" {
#جے_انت



// VK_QNX_screen_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_QNX_screen_surface 1

#تعریف_کرو VK_QNX_SCREEN_SURFACE_SPEC_نسخہ 1
#تعریف_کرو VK_QNX_SCREEN_SURFACE_EXTENSION_NAME "VK_QNX_screen_surface"

تعريفنوع VkFlags VkScreenSurfaceCreateFlagsQNX;

تعريفنوع بنية VkScreenSurfaceCreateInfoQNX {
    VkStructureType                  sType;
    ثابت فراغ*                      p_اگلا;
    VkScreenSurfaceCreateFlagsQNX    flags;
    بنية _screen_context*          context;
    بنية screen_کھڑکی*           کھڑکی;
} VkScreenSurfaceCreateInfoQNX;


تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vkCreateScreenSurfaceQNX)(VkInstance instance, ثابت VkScreenSurfaceCreateInfoQNX* pCreateInfo, ثابت Vk_ونڈ_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
تعريفنوع VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceScreenPresentationSupportQNX)(VkPhysicalDevice physicalDevice, uint32_t قطار_Family_اشاریہ, بنية screen_کھڑکی* کھڑکی);

#جے_بنا_تعریف VK_NO_PROTOTYPES

#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vkCreateScreenSurfaceQNX(
    VkInstance                                  instance,
    ثابت VkScreenSurfaceCreateInfoQNX*         pCreateInfo,
    ثابت Vk_ونڈ_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#جے_انت
#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceScreenPresentationSupportQNX(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    قطار_Family_اشاریہ,
    بنية screen_کھڑکی*                      کھڑکی);
#جے_انت
#جے_انت


// VK_QNX_external_memory_screen_buffer is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_QNX_external_حافظہ_screen_بفر 1

#تعریف_کرو VK_QNX_EXTERNAL_حافظہ_SCREEN_بفر_SPEC_نسخہ 1
#تعریف_کرو VK_QNX_EXTERNAL_حافظہ_SCREEN_بفر_EXTENSION_NAME "VK_QNX_external_memory_screen_buffer"

تعريفنوع بنية Vk_Screen_بفر_Properties_QNX {
    VkStructureType    sType;
    فراغ*              p_اگلا;
    Vk_Device_ناپ       ونڈ_ناپ;
    uint32_t           حافظہ_Type_بٹ;
} Vk_Screen_بفر_Properties_QNX;

تعريفنوع بنية Vk_Screen_بفر_Format_Properties_QNX {
    VkStructureType                  sType;
    فراغ*                            p_اگلا;
    VkFormat                         format;
    uint64_t                         externalFormat;
    uint64_t                         screenUsage;
    VkFormatFeatureFlags             formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggested_XChroma_وتھ;
    VkChromaLocation                 suggested_YChroma_وتھ;
} Vk_Screen_بفر_Format_Properties_QNX;

تعريفنوع بنية Vk_Import_Screen_بفر_Info_QNX {
    VkStructureType           sType;
    ثابت فراغ*               p_اگلا;
    بنية screen_بفر*    بفر_2;
} Vk_Import_Screen_بفر_Info_QNX;

تعريفنوع بنية VkExternalFormatQNX {
    VkStructureType    sType;
    فراغ*              p_اگلا;
    uint64_t           externalFormat;
} VkExternalFormatQNX;

تعريفنوع بنية Vk_Physical_Device_External_حافظہ_Screen_بفر_Features_QNX {
    VkStructureType    sType;
    فراغ*              p_اگلا;
    VkBool32           screen_بفر_Import;
} Vk_Physical_Device_External_حافظہ_Screen_بفر_Features_QNX;


تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vk_Get_Screen_بفر_Properties_QNX)(VkDevice device, ثابت بنية screen_بفر* بفر_2, Vk_Screen_بفر_Properties_QNX* pProperties);

#جے_بنا_تعریف VK_NO_PROTOTYPES

#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_Get_Screen_بفر_Properties_QNX(
    VkDevice                                    device,
    ثابت بنية screen_بفر*                بفر_2,
    Vk_Screen_بفر_Properties_QNX*                pProperties);
#جے_انت
#جے_انت

#جے_تعریف_شدہ __cplusplus
}
#جے_انت

#جے_انت
