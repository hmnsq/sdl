#اگر_تعریف_نشده VULKAN_ANDROID_H_
#تعریف_کن VULKAN_ANDROID_H_ 1

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



// VK_KHR_android_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کن VK_KHR_android_surface 1

بنية ANative_پنجره;

#تعریف_کن VK_KHR_ANDROID_SURFACE_SPEC_نسخه 6
#تعریف_کن VK_KHR_ANDROID_SURFACE_EXTENSION_NAME "VK_KHR_android_surface"

تعريفنوع VkFlags VkAndroidSurfaceCreateFlagsKHR;

تعريفنوع بنية VkAndroidSurfaceCreateInfoKHR {
    VkStructureType                   sType;
    ثابت فراغ*                       p_بعدی;
    VkAndroidSurfaceCreateFlagsKHR    flags;
    بنية ANative_پنجره*             پنجره;
} VkAndroidSurfaceCreateInfoKHR;


تعريفنوع Vk_نتیجه (VKAPI_PTR *PFN_vkCreateAndroidSurfaceKHR)(VkInstance instance, ثابت VkAndroidSurfaceCreateInfoKHR* pCreateInfo, ثابت Vk_تخصیص_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#اگر_تعریف_نشده VK_NO_PROTOTYPES

#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجه VKAPI_CALL vkCreateAndroidSurfaceKHR(
    VkInstance                                  instance,
    ثابت VkAndroidSurfaceCreateInfoKHR*        pCreateInfo,
    ثابت Vk_تخصیص_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#پایان_اگر
#پایان_اگر


// VK_ANDROID_external_memory_android_hardware_buffer is a preprocessor guard. Do not pass it to API calls.
#تعریف_کن VK_ANDROID_external_حافظه_android_hardware_میانگیر 1

بنية AHardware_میانگیر;

#تعریف_کن VK_ANDROID_EXTERNAL_حافظه_ANDROID_HARDWARE_میانگیر_SPEC_نسخه 5
#تعریف_کن VK_ANDROID_EXTERNAL_حافظه_ANDROID_HARDWARE_میانگیر_EXTENSION_NAME "VK_ANDROID_external_memory_android_hardware_buffer"

تعريفنوع بنية Vk_Android_Hardware_میانگیر_Usage_ANDROID {
    VkStructureType    sType;
    فراغ*              p_بعدی;
    uint64_t           android_Hardware_میانگیر_Usage;
} Vk_Android_Hardware_میانگیر_Usage_ANDROID;

تعريفنوع بنية Vk_Android_Hardware_میانگیر_Properties_ANDROID {
    VkStructureType    sType;
    فراغ*              p_بعدی;
    Vk_Device_اندازه       تخصیص_اندازه;
    uint32_t           حافظه_Type_بیتها;
} Vk_Android_Hardware_میانگیر_Properties_ANDROID;

تعريفنوع بنية Vk_Android_Hardware_میانگیر_Format_Properties_ANDROID {
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
} Vk_Android_Hardware_میانگیر_Format_Properties_ANDROID;

تعريفنوع بنية Vk_Import_Android_Hardware_میانگیر_Info_ANDROID {
    VkStructureType            sType;
    ثابت فراغ*                p_بعدی;
    بنية AHardware_میانگیر*    میانگیر_2;
} Vk_Import_Android_Hardware_میانگیر_Info_ANDROID;

تعريفنوع بنية Vk_حافظه_Get_Android_Hardware_میانگیر_Info_ANDROID {
    VkStructureType    sType;
    ثابت فراغ*        p_بعدی;
    Vk_Device_حافظه     حافظه;
} Vk_حافظه_Get_Android_Hardware_میانگیر_Info_ANDROID;

تعريفنوع بنية VkExternalFormatANDROID {
    VkStructureType    sType;
    فراغ*              p_بعدی;
    uint64_t           externalFormat;
} VkExternalFormatANDROID;

تعريفنوع بنية Vk_Android_Hardware_میانگیر_Format_Properties2_ANDROID {
    VkStructureType                  sType;
    فراغ*                            p_بعدی;
    VkFormat                         format;
    uint64_t                         externalFormat;
    VkFormatFeatureFlags2            formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggested_XChroma_جابه_جایی;
    VkChromaLocation                 suggested_YChroma_جابه_جایی;
} Vk_Android_Hardware_میانگیر_Format_Properties2_ANDROID;


تعريفنوع Vk_نتیجه (VKAPI_PTR *PFN_vk_Get_Android_Hardware_میانگیر_Properties_ANDROID)(VkDevice device, ثابت بنية AHardware_میانگیر* میانگیر_2, Vk_Android_Hardware_میانگیر_Properties_ANDROID* pProperties);
تعريفنوع Vk_نتیجه (VKAPI_PTR *PFN_vk_Get_حافظه_Android_Hardware_میانگیر_ANDROID)(VkDevice device, ثابت Vk_حافظه_Get_Android_Hardware_میانگیر_Info_ANDROID* pInfo, بنية AHardware_میانگیر** p_میانگیر);

#اگر_تعریف_نشده VK_NO_PROTOTYPES

#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجه VKAPI_CALL vk_Get_Android_Hardware_میانگیر_Properties_ANDROID(
    VkDevice                                    device,
    ثابت بنية AHardware_میانگیر*               میانگیر_2,
    Vk_Android_Hardware_میانگیر_Properties_ANDROID*   pProperties);
#پایان_اگر
#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجه VKAPI_CALL vk_Get_حافظه_Android_Hardware_میانگیر_ANDROID(
    VkDevice                                    device,
    ثابت Vk_حافظه_Get_Android_Hardware_میانگیر_Info_ANDROID* pInfo,
    بنية AHardware_میانگیر**                    p_میانگیر);
#پایان_اگر
#پایان_اگر


// VK_ANDROID_external_format_resolve is a preprocessor guard. Do not pass it to API calls.
#تعریف_کن VK_ANDROID_external_format_resolve 1

#تعریف_کن VK_ANDROID_EXTERNAL_FORMAT_RESOLVE_SPEC_نسخه 1
#تعریف_کن VK_ANDROID_EXTERNAL_FORMAT_RESOLVE_EXTENSION_NAME "VK_ANDROID_external_format_resolve"

تعريفنوع بنية VkPhysicalDeviceExternalFormatResolveFeaturesANDROID {
    VkStructureType    sType;
    فراغ*              p_بعدی;
    VkBool32           externalFormatResolve;
} VkPhysicalDeviceExternalFormatResolveFeaturesANDROID;

تعريفنوع بنية VkPhysicalDeviceExternalFormatResolvePropertiesANDROID {
    VkStructureType     sType;
    فراغ*               p_بعدی;
    VkBool32            nullColorAttachmentWithExternalFormatResolve;
    VkChromaLocation    external_Format_Resolve_Chroma_جابه_جایی_X;
    VkChromaLocation    external_Format_Resolve_Chroma_جابه_جایی_Y;
} VkPhysicalDeviceExternalFormatResolvePropertiesANDROID;

تعريفنوع بنية Vk_Android_Hardware_میانگیر_Format_Resolve_Properties_ANDROID {
    VkStructureType    sType;
    فراغ*              p_بعدی;
    VkFormat           colorAttachmentFormat;
} Vk_Android_Hardware_میانگیر_Format_Resolve_Properties_ANDROID;


#اگر_تعریف_شده __cplusplus
}
#پایان_اگر

#پایان_اگر
