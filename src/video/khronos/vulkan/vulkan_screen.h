#اگر_تعریف_نشده VULKAN_SCREEN_H_
#تعریف_کن VULKAN_SCREEN_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#اگر_تعریف_شده __cplusplus
خارجي "C" {
#پایان_اگر



// VK_QNX_screen_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کن VK_QNX_screen_surface 1

#تعریف_کن VK_QNX_SCREEN_SURFACE_SPEC_نسخه 1
#تعریف_کن VK_QNX_SCREEN_SURFACE_EXTENSION_NAME "VK_QNX_screen_surface"

تعريفنوع VkFlags VkScreenSurfaceCreateFlagsQNX;

تعريفنوع بنية VkScreenSurfaceCreateInfoQNX {
    VkStructureType                  sType;
    ثابت فراغ*                      p_بعدی;
    VkScreenSurfaceCreateFlagsQNX    flags;
    بنية _screen_context*          context;
    بنية screen_پنجره*           پنجره;
} VkScreenSurfaceCreateInfoQNX;


تعريفنوع Vk_نتیجه (VKAPI_PTR *PFN_vkCreateScreenSurfaceQNX)(VkInstance instance, ثابت VkScreenSurfaceCreateInfoQNX* pCreateInfo, ثابت Vk_تخصیص_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
تعريفنوع VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceScreenPresentationSupportQNX)(VkPhysicalDevice physicalDevice, uint32_t صف_Family_شاخص, بنية screen_پنجره* پنجره);

#اگر_تعریف_نشده VK_NO_PROTOTYPES

#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجه VKAPI_CALL vkCreateScreenSurfaceQNX(
    VkInstance                                  instance,
    ثابت VkScreenSurfaceCreateInfoQNX*         pCreateInfo,
    ثابت Vk_تخصیص_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#پایان_اگر
#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceScreenPresentationSupportQNX(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    صف_Family_شاخص,
    بنية screen_پنجره*                      پنجره);
#پایان_اگر
#پایان_اگر


// VK_QNX_external_memory_screen_buffer is a preprocessor guard. Do not pass it to API calls.
#تعریف_کن VK_QNX_external_حافظه_screen_میانگیر 1

#تعریف_کن VK_QNX_EXTERNAL_حافظه_SCREEN_میانگیر_SPEC_نسخه 1
#تعریف_کن VK_QNX_EXTERNAL_حافظه_SCREEN_میانگیر_EXTENSION_NAME "VK_QNX_external_memory_screen_buffer"

تعريفنوع بنية Vk_Screen_میانگیر_Properties_QNX {
    VkStructureType    sType;
    فراغ*              p_بعدی;
    Vk_Device_اندازه       تخصیص_اندازه;
    uint32_t           حافظه_Type_بیتها;
} Vk_Screen_میانگیر_Properties_QNX;

تعريفنوع بنية Vk_Screen_میانگیر_Format_Properties_QNX {
    VkStructureType                  sType;
    فراغ*                            p_بعدی;
    VkFormat                         format;
    uint64_t                         externalFormat;
    uint64_t                         screenUsage;
    VkFormatFeatureFlags             formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggested_XChroma_جابه_جایی;
    VkChromaLocation                 suggested_YChroma_جابه_جایی;
} Vk_Screen_میانگیر_Format_Properties_QNX;

تعريفنوع بنية Vk_Import_Screen_میانگیر_Info_QNX {
    VkStructureType           sType;
    ثابت فراغ*               p_بعدی;
    بنية screen_میانگیر*    میانگیر_2;
} Vk_Import_Screen_میانگیر_Info_QNX;

تعريفنوع بنية VkExternalFormatQNX {
    VkStructureType    sType;
    فراغ*              p_بعدی;
    uint64_t           externalFormat;
} VkExternalFormatQNX;

تعريفنوع بنية Vk_Physical_Device_External_حافظه_Screen_میانگیر_Features_QNX {
    VkStructureType    sType;
    فراغ*              p_بعدی;
    VkBool32           screen_میانگیر_Import;
} Vk_Physical_Device_External_حافظه_Screen_میانگیر_Features_QNX;


تعريفنوع Vk_نتیجه (VKAPI_PTR *PFN_vk_Get_Screen_میانگیر_Properties_QNX)(VkDevice device, ثابت بنية screen_میانگیر* میانگیر_2, Vk_Screen_میانگیر_Properties_QNX* pProperties);

#اگر_تعریف_نشده VK_NO_PROTOTYPES

#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجه VKAPI_CALL vk_Get_Screen_میانگیر_Properties_QNX(
    VkDevice                                    device,
    ثابت بنية screen_میانگیر*                میانگیر_2,
    Vk_Screen_میانگیر_Properties_QNX*                pProperties);
#پایان_اگر
#پایان_اگر

#اگر_تعریف_شده __cplusplus
}
#پایان_اگر

#پایان_اگر
