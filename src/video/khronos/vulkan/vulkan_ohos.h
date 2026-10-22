#جيڪڏهن_وصف_نه_ٿيل VULKAN_OHOS_H_
#وصف_ڪريو VULKAN_OHOS_H_ 1

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



// VK_OHOS_external_memory is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو VK_OHOS_external_يادگيري 1

بنية OH_Native_بفر;

#وصف_ڪريو VK_OHOS_EXTERNAL_يادگيري_SPEC_نسخو 1
#وصف_ڪريو VK_OHOS_EXTERNAL_يادگيري_EXTENSION_NAME "VK_OHOS_external_memory"

تعريفنوع بنية Vk_Native_بفر_Usage_OHOS {
    VkStructureType    sType;
    فراغ*              p_ايندڙ;
    uint64_t           OHOSNative_بفر_Usage;
} Vk_Native_بفر_Usage_OHOS;

تعريفنوع بنية Vk_Native_بفر_Properties_OHOS {
    VkStructureType    sType;
    فراغ*              p_ايندڙ;
    Vk_Device_سائيز       ورهاست_سائيز;
    uint32_t           يادگيري_Type_بٽ;
} Vk_Native_بفر_Properties_OHOS;

تعريفنوع بنية Vk_Native_بفر_Format_Properties_OHOS {
    VkStructureType                  sType;
    فراغ*                            p_ايندڙ;
    VkFormat                         format;
    uint64_t                         externalFormat;
    VkFormatFeatureFlags             formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggested_XChroma_وٿي;
    VkChromaLocation                 suggested_YChroma_وٿي;
} Vk_Native_بفر_Format_Properties_OHOS;

تعريفنوع بنية Vk_Import_Native_بفر_Info_OHOS {
    VkStructureType            sType;
    ثابت فراغ*                p_ايندڙ;
    بنية OH_Native_بفر*    بفر_2;
} Vk_Import_Native_بفر_Info_OHOS;

تعريفنوع بنية Vk_يادگيري_Get_Native_بفر_Info_OHOS {
    VkStructureType    sType;
    ثابت فراغ*        p_ايندڙ;
    Vk_Device_يادگيري     يادگيري;
} Vk_يادگيري_Get_Native_بفر_Info_OHOS;

تعريفنوع بنية VkExternalFormatOHOS {
    VkStructureType    sType;
    فراغ*              p_ايندڙ;
    uint64_t           externalFormat;
} VkExternalFormatOHOS;


تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vk_Get_Native_بفر_Properties_OHOS)(VkDevice device, ثابت بنية OH_Native_بفر* بفر_2, Vk_Native_بفر_Properties_OHOS* pProperties);
تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vk_Get_يادگيري_Native_بفر_OHOS)(VkDevice device, ثابت Vk_يادگيري_Get_Native_بفر_Info_OHOS* pInfo, بنية OH_Native_بفر** p_بفر);

#جيڪڏهن_وصف_نه_ٿيل VK_NO_PROTOTYPES

#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتيجو VKAPI_CALL vk_Get_Native_بفر_Properties_OHOS(
    VkDevice                                    device,
    ثابت بنية OH_Native_بفر*               بفر_2,
    Vk_Native_بفر_Properties_OHOS*               pProperties);
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتيجو VKAPI_CALL vk_Get_يادگيري_Native_بفر_OHOS(
    VkDevice                                    device,
    ثابت Vk_يادگيري_Get_Native_بفر_Info_OHOS*      pInfo,
    بنية OH_Native_بفر**                    p_بفر);
#جيڪڏهن_پورو
#جيڪڏهن_پورو


// VK_OHOS_surface is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو VK_OHOS_surface 1

تعريفنوع بنية Native_دري OHNative_دري;

#وصف_ڪريو VK_OHOS_SURFACE_SPEC_نسخو      1
#وصف_ڪريو VK_OHOS_SURFACE_EXTENSION_NAME    "VK_OHOS_surface"

تعريفنوع VkFlags VkSurfaceCreateFlagsOHOS;

تعريفنوع بنية VkSurfaceCreateInfoOHOS {
    VkStructureType             sType;
    ثابت فراغ*                 p_ايندڙ;
    VkSurfaceCreateFlagsOHOS    flags;
    OHNative_دري*             دري;
} VkSurfaceCreateInfoOHOS;


تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vkCreateSurfaceOHOS)(VkInstance instance, ثابت VkSurfaceCreateInfoOHOS* pCreateInfo, ثابت Vk_ورهاست_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#جيڪڏهن_وصف_نه_ٿيل VK_NO_PROTOTYPES

#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتيجو VKAPI_CALL vkCreateSurfaceOHOS(
    VkInstance                                  instance,
    ثابت VkSurfaceCreateInfoOHOS*              pCreateInfo,
    ثابت Vk_ورهاست_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#جيڪڏهن_پورو
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل __cplusplus
}
#جيڪڏهن_پورو

#جيڪڏهن_پورو
