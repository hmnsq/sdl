#جے_بنا_تعریف VULKAN_OHOS_H_
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


#جے_تعریف_شدہ __cplusplus
خارجي "C" {
#جے_انت



// VK_OHOS_external_memory is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_OHOS_external_حافظہ 1

بنية OH_Native_بفر;

#تعریف_کرو VK_OHOS_EXTERNAL_حافظہ_SPEC_نسخہ 1
#تعریف_کرو VK_OHOS_EXTERNAL_حافظہ_EXTENSION_NAME "VK_OHOS_external_memory"

تعريفنوع بنية Vk_Native_بفر_Usage_OHOS {
    VkStructureType    sType;
    فراغ*              p_اگلا;
    uint64_t           OHOSNative_بفر_Usage;
} Vk_Native_بفر_Usage_OHOS;

تعريفنوع بنية Vk_Native_بفر_Properties_OHOS {
    VkStructureType    sType;
    فراغ*              p_اگلا;
    Vk_Device_ناپ       ونڈ_ناپ;
    uint32_t           حافظہ_Type_بٹ;
} Vk_Native_بفر_Properties_OHOS;

تعريفنوع بنية Vk_Native_بفر_Format_Properties_OHOS {
    VkStructureType                  sType;
    فراغ*                            p_اگلا;
    VkFormat                         format;
    uint64_t                         externalFormat;
    VkFormatFeatureFlags             formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggested_XChroma_وتھ;
    VkChromaLocation                 suggested_YChroma_وتھ;
} Vk_Native_بفر_Format_Properties_OHOS;

تعريفنوع بنية Vk_Import_Native_بفر_Info_OHOS {
    VkStructureType            sType;
    ثابت فراغ*                p_اگلا;
    بنية OH_Native_بفر*    بفر_2;
} Vk_Import_Native_بفر_Info_OHOS;

تعريفنوع بنية Vk_حافظہ_Get_Native_بفر_Info_OHOS {
    VkStructureType    sType;
    ثابت فراغ*        p_اگلا;
    Vk_Device_حافظہ     حافظہ;
} Vk_حافظہ_Get_Native_بفر_Info_OHOS;

تعريفنوع بنية VkExternalFormatOHOS {
    VkStructureType    sType;
    فراغ*              p_اگلا;
    uint64_t           externalFormat;
} VkExternalFormatOHOS;


تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vk_Get_Native_بفر_Properties_OHOS)(VkDevice device, ثابت بنية OH_Native_بفر* بفر_2, Vk_Native_بفر_Properties_OHOS* pProperties);
تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vk_Get_حافظہ_Native_بفر_OHOS)(VkDevice device, ثابت Vk_حافظہ_Get_Native_بفر_Info_OHOS* pInfo, بنية OH_Native_بفر** p_بفر);

#جے_بنا_تعریف VK_NO_PROTOTYPES

#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_Get_Native_بفر_Properties_OHOS(
    VkDevice                                    device,
    ثابت بنية OH_Native_بفر*               بفر_2,
    Vk_Native_بفر_Properties_OHOS*               pProperties);
#جے_انت
#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_Get_حافظہ_Native_بفر_OHOS(
    VkDevice                                    device,
    ثابت Vk_حافظہ_Get_Native_بفر_Info_OHOS*      pInfo,
    بنية OH_Native_بفر**                    p_بفر);
#جے_انت
#جے_انت


// VK_OHOS_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_OHOS_surface 1

تعريفنوع بنية Native_کھڑکی OHNative_کھڑکی;

#تعریف_کرو VK_OHOS_SURFACE_SPEC_نسخہ      1
#تعریف_کرو VK_OHOS_SURFACE_EXTENSION_NAME    "VK_OHOS_surface"

تعريفنوع VkFlags VkSurfaceCreateFlagsOHOS;

تعريفنوع بنية VkSurfaceCreateInfoOHOS {
    VkStructureType             sType;
    ثابت فراغ*                 p_اگلا;
    VkSurfaceCreateFlagsOHOS    flags;
    OHNative_کھڑکی*             کھڑکی;
} VkSurfaceCreateInfoOHOS;


تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vkCreateSurfaceOHOS)(VkInstance instance, ثابت VkSurfaceCreateInfoOHOS* pCreateInfo, ثابت Vk_ونڈ_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#جے_بنا_تعریف VK_NO_PROTOTYPES

#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vkCreateSurfaceOHOS(
    VkInstance                                  instance,
    ثابت VkSurfaceCreateInfoOHOS*              pCreateInfo,
    ثابت Vk_ونڈ_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#جے_انت
#جے_انت

#جے_تعریف_شدہ __cplusplus
}
#جے_انت

#جے_انت
