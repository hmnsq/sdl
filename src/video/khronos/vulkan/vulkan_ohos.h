#که_نه_تعریف_شوی VULKAN_OHOS_H_
#تعریف_کړه VULKAN_OHOS_H_ 1

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



// VK_OHOS_external_memory is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه VK_OHOS_external_حافظه 1

بنية OH_Native_بفر;

#تعریف_کړه VK_OHOS_EXTERNAL_حافظه_SPEC_نسخه 1
#تعریف_کړه VK_OHOS_EXTERNAL_حافظه_EXTENSION_NAME "VK_OHOS_external_memory"

تعريفنوع بنية Vk_Native_بفر_Usage_OHOS {
    VkStructureType    sType;
    فراغ*              p_بل;
    uint64_t           OHOSNative_بفر_Usage;
} Vk_Native_بفر_Usage_OHOS;

تعريفنوع بنية Vk_Native_بفر_Properties_OHOS {
    VkStructureType    sType;
    فراغ*              p_بل;
    Vk_Device_اندازه       ویش_اندازه;
    uint32_t           حافظه_Type_بټونه;
} Vk_Native_بفر_Properties_OHOS;

تعريفنوع بنية Vk_Native_بفر_Format_Properties_OHOS {
    VkStructureType                  sType;
    فراغ*                            p_بل;
    VkFormat                         format;
    uint64_t                         externalFormat;
    VkFormatFeatureFlags             formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggested_XChroma_دننه_واټن;
    VkChromaLocation                 suggested_YChroma_دننه_واټن;
} Vk_Native_بفر_Format_Properties_OHOS;

تعريفنوع بنية Vk_Import_Native_بفر_Info_OHOS {
    VkStructureType            sType;
    ثابت فراغ*                p_بل;
    بنية OH_Native_بفر*    بفر_2;
} Vk_Import_Native_بفر_Info_OHOS;

تعريفنوع بنية Vk_حافظه_Get_Native_بفر_Info_OHOS {
    VkStructureType    sType;
    ثابت فراغ*        p_بل;
    Vk_Device_حافظه     حافظه;
} Vk_حافظه_Get_Native_بفر_Info_OHOS;

تعريفنوع بنية VkExternalFormatOHOS {
    VkStructureType    sType;
    فراغ*              p_بل;
    uint64_t           externalFormat;
} VkExternalFormatOHOS;


تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vk_Get_Native_بفر_Properties_OHOS)(VkDevice device, ثابت بنية OH_Native_بفر* بفر_2, Vk_Native_بفر_Properties_OHOS* pProperties);
تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vk_Get_حافظه_Native_بفر_OHOS)(VkDevice device, ثابت Vk_حافظه_Get_Native_بفر_Info_OHOS* pInfo, بنية OH_Native_بفر** p_بفر);

#که_نه_تعریف_شوی VK_NO_PROTOTYPES

#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_پایله VKAPI_CALL vk_Get_Native_بفر_Properties_OHOS(
    VkDevice                                    device,
    ثابت بنية OH_Native_بفر*               بفر_2,
    Vk_Native_بفر_Properties_OHOS*               pProperties);
#د_که_پای
#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_پایله VKAPI_CALL vk_Get_حافظه_Native_بفر_OHOS(
    VkDevice                                    device,
    ثابت Vk_حافظه_Get_Native_بفر_Info_OHOS*      pInfo,
    بنية OH_Native_بفر**                    p_بفر);
#د_که_پای
#د_که_پای


// VK_OHOS_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه VK_OHOS_surface 1

تعريفنوع بنية Native_کړکۍ OHNative_کړکۍ;

#تعریف_کړه VK_OHOS_SURFACE_SPEC_نسخه      1
#تعریف_کړه VK_OHOS_SURFACE_EXTENSION_NAME    "VK_OHOS_surface"

تعريفنوع VkFlags VkSurfaceCreateFlagsOHOS;

تعريفنوع بنية VkSurfaceCreateInfoOHOS {
    VkStructureType             sType;
    ثابت فراغ*                 p_بل;
    VkSurfaceCreateFlagsOHOS    flags;
    OHNative_کړکۍ*             کړکۍ;
} VkSurfaceCreateInfoOHOS;


تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vkCreateSurfaceOHOS)(VkInstance instance, ثابت VkSurfaceCreateInfoOHOS* pCreateInfo, ثابت Vk_ویش_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#که_نه_تعریف_شوی VK_NO_PROTOTYPES

#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_پایله VKAPI_CALL vkCreateSurfaceOHOS(
    VkInstance                                  instance,
    ثابت VkSurfaceCreateInfoOHOS*              pCreateInfo,
    ثابت Vk_ویش_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#د_که_پای
#د_که_پای

#که_تعریف_شوی __cplusplus
}
#د_که_پای

#د_که_پای
