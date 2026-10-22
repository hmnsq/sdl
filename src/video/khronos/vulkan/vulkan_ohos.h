#اگر_تعریف_نشده VULKAN_OHOS_H_
#تعریف_کن VULKAN_OHOS_H_ 1

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



// VK_OHOS_external_memory is a preprocessor guard. Do not pass it to API calls.
#تعریف_کن VK_OHOS_external_حافظه 1

بنية OH_Native_میانگیر;

#تعریف_کن VK_OHOS_EXTERNAL_حافظه_SPEC_نسخه 1
#تعریف_کن VK_OHOS_EXTERNAL_حافظه_EXTENSION_NAME "VK_OHOS_external_memory"

تعريفنوع بنية Vk_Native_میانگیر_Usage_OHOS {
    VkStructureType    sType;
    فراغ*              p_بعدی;
    uint64_t           OHOSNative_میانگیر_Usage;
} Vk_Native_میانگیر_Usage_OHOS;

تعريفنوع بنية Vk_Native_میانگیر_Properties_OHOS {
    VkStructureType    sType;
    فراغ*              p_بعدی;
    Vk_Device_اندازه       تخصیص_اندازه;
    uint32_t           حافظه_Type_بیتها;
} Vk_Native_میانگیر_Properties_OHOS;

تعريفنوع بنية Vk_Native_میانگیر_Format_Properties_OHOS {
    VkStructureType                  sType;
    فراغ*                            p_بعدی;
    VkFormat                         format;
    uint64_t                         externalFormat;
    VkFormatFeatureFlags             formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggested_XChroma_جابه_جایی;
    VkChromaLocation                 suggested_YChroma_جابه_جایی;
} Vk_Native_میانگیر_Format_Properties_OHOS;

تعريفنوع بنية Vk_Import_Native_میانگیر_Info_OHOS {
    VkStructureType            sType;
    ثابت فراغ*                p_بعدی;
    بنية OH_Native_میانگیر*    میانگیر_2;
} Vk_Import_Native_میانگیر_Info_OHOS;

تعريفنوع بنية Vk_حافظه_Get_Native_میانگیر_Info_OHOS {
    VkStructureType    sType;
    ثابت فراغ*        p_بعدی;
    Vk_Device_حافظه     حافظه;
} Vk_حافظه_Get_Native_میانگیر_Info_OHOS;

تعريفنوع بنية VkExternalFormatOHOS {
    VkStructureType    sType;
    فراغ*              p_بعدی;
    uint64_t           externalFormat;
} VkExternalFormatOHOS;


تعريفنوع Vk_نتیجه (VKAPI_PTR *PFN_vk_Get_Native_میانگیر_Properties_OHOS)(VkDevice device, ثابت بنية OH_Native_میانگیر* میانگیر_2, Vk_Native_میانگیر_Properties_OHOS* pProperties);
تعريفنوع Vk_نتیجه (VKAPI_PTR *PFN_vk_Get_حافظه_Native_میانگیر_OHOS)(VkDevice device, ثابت Vk_حافظه_Get_Native_میانگیر_Info_OHOS* pInfo, بنية OH_Native_میانگیر** p_میانگیر);

#اگر_تعریف_نشده VK_NO_PROTOTYPES

#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجه VKAPI_CALL vk_Get_Native_میانگیر_Properties_OHOS(
    VkDevice                                    device,
    ثابت بنية OH_Native_میانگیر*               میانگیر_2,
    Vk_Native_میانگیر_Properties_OHOS*               pProperties);
#پایان_اگر
#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجه VKAPI_CALL vk_Get_حافظه_Native_میانگیر_OHOS(
    VkDevice                                    device,
    ثابت Vk_حافظه_Get_Native_میانگیر_Info_OHOS*      pInfo,
    بنية OH_Native_میانگیر**                    p_میانگیر);
#پایان_اگر
#پایان_اگر


// VK_OHOS_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کن VK_OHOS_surface 1

تعريفنوع بنية Native_پنجره OHNative_پنجره;

#تعریف_کن VK_OHOS_SURFACE_SPEC_نسخه      1
#تعریف_کن VK_OHOS_SURFACE_EXTENSION_NAME    "VK_OHOS_surface"

تعريفنوع VkFlags VkSurfaceCreateFlagsOHOS;

تعريفنوع بنية VkSurfaceCreateInfoOHOS {
    VkStructureType             sType;
    ثابت فراغ*                 p_بعدی;
    VkSurfaceCreateFlagsOHOS    flags;
    OHNative_پنجره*             پنجره;
} VkSurfaceCreateInfoOHOS;


تعريفنوع Vk_نتیجه (VKAPI_PTR *PFN_vkCreateSurfaceOHOS)(VkInstance instance, ثابت VkSurfaceCreateInfoOHOS* pCreateInfo, ثابت Vk_تخصیص_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#اگر_تعریف_نشده VK_NO_PROTOTYPES

#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجه VKAPI_CALL vkCreateSurfaceOHOS(
    VkInstance                                  instance,
    ثابت VkSurfaceCreateInfoOHOS*              pCreateInfo,
    ثابت Vk_تخصیص_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#پایان_اگر
#پایان_اگر

#اگر_تعریف_شده __cplusplus
}
#پایان_اگر

#پایان_اگر
