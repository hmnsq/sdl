#اگر_غیر_تعریف_شدہ VULKAN_ANDROID_H_
#تعریف_کرو VULKAN_ANDROID_H_ 1

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



// VK_KHR_android_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_KHR_android_surface 1

ساخت ANative_کھڑکی;

#تعریف_کرو VK_KHR_ANDROID_SURFACE_SPEC_نسخہ 6
#تعریف_کرو VK_KHR_ANDROID_SURFACE_EXTENSION_NAME "VK_KHR_android_surface"

قسمتعریف VkFlags VkAndroidSurfaceCreateFlagsKHR;

قسمتعریف ساخت VkAndroidSurfaceCreateInfoKHR {
    VkStructureType                   sType;
    ثابت خالی*                       p_اگلا;
    VkAndroidSurfaceCreateFlagsKHR    flags;
    ساخت ANative_کھڑکی*             کھڑکی;
} VkAndroidSurfaceCreateInfoKHR;


قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vkCreateAndroidSurfaceKHR)(VkInstance instance, ثابت VkAndroidSurfaceCreateInfoKHR* pCreateInfo, ثابت Vk_تخصیص_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#اگر_غیر_تعریف_شدہ VK_NO_PROTOTYPES

#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vkCreateAndroidSurfaceKHR(
    VkInstance                                  instance,
    ثابت VkAndroidSurfaceCreateInfoKHR*        pCreateInfo,
    ثابت Vk_تخصیص_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#اگر_ختم
#اگر_ختم


// VK_ANDROID_external_memory_android_hardware_buffer is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_ANDROID_external_حافظہ_android_hardware_بفر 1

ساخت AHardware_بفر;

#تعریف_کرو VK_ANDROID_EXTERNAL_حافظہ_ANDROID_HARDWARE_بفر_SPEC_نسخہ 5
#تعریف_کرو VK_ANDROID_EXTERNAL_حافظہ_ANDROID_HARDWARE_بفر_EXTENSION_NAME "VK_ANDROID_external_memory_android_hardware_buffer"

قسمتعریف ساخت Vk_Android_Hardware_بفر_Usage_ANDROID {
    VkStructureType    sType;
    خالی*              p_اگلا;
    uint64_t           android_Hardware_بفر_Usage;
} Vk_Android_Hardware_بفر_Usage_ANDROID;

قسمتعریف ساخت Vk_Android_Hardware_بفر_Properties_ANDROID {
    VkStructureType    sType;
    خالی*              p_اگلا;
    Vk_Device_سائز       تخصیص_سائز;
    uint32_t           حافظہ_Type_بٹ;
} Vk_Android_Hardware_بفر_Properties_ANDROID;

قسمتعریف ساخت Vk_Android_Hardware_بفر_Format_Properties_ANDROID {
    VkStructureType                  sType;
    خالی*                            p_اگلا;
    VkFormat                         format;
    uint64_t                         externalFormat;
    VkFormatFeatureFlags             formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggested_XChroma_انحراف;
    VkChromaLocation                 suggested_YChroma_انحراف;
} Vk_Android_Hardware_بفر_Format_Properties_ANDROID;

قسمتعریف ساخت Vk_Import_Android_Hardware_بفر_Info_ANDROID {
    VkStructureType            sType;
    ثابت خالی*                p_اگلا;
    ساخت AHardware_بفر*    بفر_2;
} Vk_Import_Android_Hardware_بفر_Info_ANDROID;

قسمتعریف ساخت Vk_حافظہ_Get_Android_Hardware_بفر_Info_ANDROID {
    VkStructureType    sType;
    ثابت خالی*        p_اگلا;
    Vk_Device_حافظہ     حافظہ;
} Vk_حافظہ_Get_Android_Hardware_بفر_Info_ANDROID;

قسمتعریف ساخت VkExternalFormatANDROID {
    VkStructureType    sType;
    خالی*              p_اگلا;
    uint64_t           externalFormat;
} VkExternalFormatANDROID;

قسمتعریف ساخت Vk_Android_Hardware_بفر_Format_Properties2_ANDROID {
    VkStructureType                  sType;
    خالی*                            p_اگلا;
    VkFormat                         format;
    uint64_t                         externalFormat;
    VkFormatFeatureFlags2            formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggested_XChroma_انحراف;
    VkChromaLocation                 suggested_YChroma_انحراف;
} Vk_Android_Hardware_بفر_Format_Properties2_ANDROID;


قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vk_Get_Android_Hardware_بفر_Properties_ANDROID)(VkDevice device, ثابت ساخت AHardware_بفر* بفر_2, Vk_Android_Hardware_بفر_Properties_ANDROID* pProperties);
قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vk_Get_حافظہ_Android_Hardware_بفر_ANDROID)(VkDevice device, ثابت Vk_حافظہ_Get_Android_Hardware_بفر_Info_ANDROID* pInfo, ساخت AHardware_بفر** p_بفر);

#اگر_غیر_تعریف_شدہ VK_NO_PROTOTYPES

#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_Get_Android_Hardware_بفر_Properties_ANDROID(
    VkDevice                                    device,
    ثابت ساخت AHardware_بفر*               بفر_2,
    Vk_Android_Hardware_بفر_Properties_ANDROID*   pProperties);
#اگر_ختم
#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_Get_حافظہ_Android_Hardware_بفر_ANDROID(
    VkDevice                                    device,
    ثابت Vk_حافظہ_Get_Android_Hardware_بفر_Info_ANDROID* pInfo,
    ساخت AHardware_بفر**                    p_بفر);
#اگر_ختم
#اگر_ختم


// VK_ANDROID_external_format_resolve is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_ANDROID_external_format_resolve 1

#تعریف_کرو VK_ANDROID_EXTERNAL_FORMAT_RESOLVE_SPEC_نسخہ 1
#تعریف_کرو VK_ANDROID_EXTERNAL_FORMAT_RESOLVE_EXTENSION_NAME "VK_ANDROID_external_format_resolve"

قسمتعریف ساخت VkPhysicalDeviceExternalFormatResolveFeaturesANDROID {
    VkStructureType    sType;
    خالی*              p_اگلا;
    VkBool32           externalFormatResolve;
} VkPhysicalDeviceExternalFormatResolveFeaturesANDROID;

قسمتعریف ساخت VkPhysicalDeviceExternalFormatResolvePropertiesANDROID {
    VkStructureType     sType;
    خالی*               p_اگلا;
    VkBool32            nullColorAttachmentWithExternalFormatResolve;
    VkChromaLocation    external_Format_Resolve_Chroma_انحراف_X;
    VkChromaLocation    external_Format_Resolve_Chroma_انحراف_Y;
} VkPhysicalDeviceExternalFormatResolvePropertiesANDROID;

قسمتعریف ساخت Vk_Android_Hardware_بفر_Format_Resolve_Properties_ANDROID {
    VkStructureType    sType;
    خالی*              p_اگلا;
    VkFormat           colorAttachmentFormat;
} Vk_Android_Hardware_بفر_Format_Resolve_Properties_ANDROID;


#اگر_تعریف_شدہ __cplusplus
}
#اگر_ختم

#اگر_ختم
