#اگر_غیر_تعریف_شدہ VULKAN_OHOS_H_
#تعریف_کرو VULKAN_OHOS_H_ 1

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



// VK_OHOS_external_memory is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_OHOS_external_حافظہ 1

ساخت OH_Native_بفر;

#تعریف_کرو VK_OHOS_EXTERNAL_حافظہ_SPEC_نسخہ 1
#تعریف_کرو VK_OHOS_EXTERNAL_حافظہ_EXTENSION_NAME "VK_OHOS_external_memory"

قسمتعریف ساخت Vk_Native_بفر_Usage_OHOS {
    VkStructureType    sType;
    خالی*              p_اگلا;
    uint64_t           OHOSNative_بفر_Usage;
} Vk_Native_بفر_Usage_OHOS;

قسمتعریف ساخت Vk_Native_بفر_Properties_OHOS {
    VkStructureType    sType;
    خالی*              p_اگلا;
    Vk_Device_سائز       تخصیص_سائز;
    uint32_t           حافظہ_Type_بٹ;
} Vk_Native_بفر_Properties_OHOS;

قسمتعریف ساخت Vk_Native_بفر_Format_Properties_OHOS {
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
} Vk_Native_بفر_Format_Properties_OHOS;

قسمتعریف ساخت Vk_Import_Native_بفر_Info_OHOS {
    VkStructureType            sType;
    ثابت خالی*                p_اگلا;
    ساخت OH_Native_بفر*    بفر_2;
} Vk_Import_Native_بفر_Info_OHOS;

قسمتعریف ساخت Vk_حافظہ_Get_Native_بفر_Info_OHOS {
    VkStructureType    sType;
    ثابت خالی*        p_اگلا;
    Vk_Device_حافظہ     حافظہ;
} Vk_حافظہ_Get_Native_بفر_Info_OHOS;

قسمتعریف ساخت VkExternalFormatOHOS {
    VkStructureType    sType;
    خالی*              p_اگلا;
    uint64_t           externalFormat;
} VkExternalFormatOHOS;


قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vk_Get_Native_بفر_Properties_OHOS)(VkDevice device, ثابت ساخت OH_Native_بفر* بفر_2, Vk_Native_بفر_Properties_OHOS* pProperties);
قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vk_Get_حافظہ_Native_بفر_OHOS)(VkDevice device, ثابت Vk_حافظہ_Get_Native_بفر_Info_OHOS* pInfo, ساخت OH_Native_بفر** p_بفر);

#اگر_غیر_تعریف_شدہ VK_NO_PROTOTYPES

#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_Get_Native_بفر_Properties_OHOS(
    VkDevice                                    device,
    ثابت ساخت OH_Native_بفر*               بفر_2,
    Vk_Native_بفر_Properties_OHOS*               pProperties);
#اگر_ختم
#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_Get_حافظہ_Native_بفر_OHOS(
    VkDevice                                    device,
    ثابت Vk_حافظہ_Get_Native_بفر_Info_OHOS*      pInfo,
    ساخت OH_Native_بفر**                    p_بفر);
#اگر_ختم
#اگر_ختم


// VK_OHOS_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_OHOS_surface 1

قسمتعریف ساخت Native_کھڑکی OHNative_کھڑکی;

#تعریف_کرو VK_OHOS_SURFACE_SPEC_نسخہ      1
#تعریف_کرو VK_OHOS_SURFACE_EXTENSION_NAME    "VK_OHOS_surface"

قسمتعریف VkFlags VkSurfaceCreateFlagsOHOS;

قسمتعریف ساخت VkSurfaceCreateInfoOHOS {
    VkStructureType             sType;
    ثابت خالی*                 p_اگلا;
    VkSurfaceCreateFlagsOHOS    flags;
    OHNative_کھڑکی*             کھڑکی;
} VkSurfaceCreateInfoOHOS;


قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vkCreateSurfaceOHOS)(VkInstance instance, ثابت VkSurfaceCreateInfoOHOS* pCreateInfo, ثابت Vk_تخصیص_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#اگر_غیر_تعریف_شدہ VK_NO_PROTOTYPES

#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vkCreateSurfaceOHOS(
    VkInstance                                  instance,
    ثابت VkSurfaceCreateInfoOHOS*              pCreateInfo,
    ثابت Vk_تخصیص_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#اگر_ختم
#اگر_ختم

#اگر_تعریف_شدہ __cplusplus
}
#اگر_ختم

#اگر_ختم
