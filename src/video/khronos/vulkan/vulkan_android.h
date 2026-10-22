#جے_بنا_تعریف VULKAN_ANDROID_H_
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


#جے_تعریف_شدہ __cplusplus
خارجي "C" {
#جے_انت



// VK_KHR_android_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_KHR_android_surface 1

بنية ANative_کھڑکی;

#تعریف_کرو VK_KHR_ANDROID_SURFACE_SPEC_نسخہ 6
#تعریف_کرو VK_KHR_ANDROID_SURFACE_EXTENSION_NAME "VK_KHR_android_surface"

تعريفنوع VkFlags VkAndroidSurfaceCreateFlagsKHR;

تعريفنوع بنية VkAndroidSurfaceCreateInfoKHR {
    VkStructureType                   sType;
    ثابت فراغ*                       p_اگلا;
    VkAndroidSurfaceCreateFlagsKHR    flags;
    بنية ANative_کھڑکی*             کھڑکی;
} VkAndroidSurfaceCreateInfoKHR;


تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vkCreateAndroidSurfaceKHR)(VkInstance instance, ثابت VkAndroidSurfaceCreateInfoKHR* pCreateInfo, ثابت Vk_ونڈ_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#جے_بنا_تعریف VK_NO_PROTOTYPES

#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vkCreateAndroidSurfaceKHR(
    VkInstance                                  instance,
    ثابت VkAndroidSurfaceCreateInfoKHR*        pCreateInfo,
    ثابت Vk_ونڈ_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#جے_انت
#جے_انت


// VK_ANDROID_external_memory_android_hardware_buffer is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_ANDROID_external_حافظہ_android_hardware_بفر 1

بنية AHardware_بفر;

#تعریف_کرو VK_ANDROID_EXTERNAL_حافظہ_ANDROID_HARDWARE_بفر_SPEC_نسخہ 5
#تعریف_کرو VK_ANDROID_EXTERNAL_حافظہ_ANDROID_HARDWARE_بفر_EXTENSION_NAME "VK_ANDROID_external_memory_android_hardware_buffer"

تعريفنوع بنية Vk_Android_Hardware_بفر_Usage_ANDROID {
    VkStructureType    sType;
    فراغ*              p_اگلا;
    uint64_t           android_Hardware_بفر_Usage;
} Vk_Android_Hardware_بفر_Usage_ANDROID;

تعريفنوع بنية Vk_Android_Hardware_بفر_Properties_ANDROID {
    VkStructureType    sType;
    فراغ*              p_اگلا;
    Vk_Device_ناپ       ونڈ_ناپ;
    uint32_t           حافظہ_Type_بٹ;
} Vk_Android_Hardware_بفر_Properties_ANDROID;

تعريفنوع بنية Vk_Android_Hardware_بفر_Format_Properties_ANDROID {
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
} Vk_Android_Hardware_بفر_Format_Properties_ANDROID;

تعريفنوع بنية Vk_Import_Android_Hardware_بفر_Info_ANDROID {
    VkStructureType            sType;
    ثابت فراغ*                p_اگلا;
    بنية AHardware_بفر*    بفر_2;
} Vk_Import_Android_Hardware_بفر_Info_ANDROID;

تعريفنوع بنية Vk_حافظہ_Get_Android_Hardware_بفر_Info_ANDROID {
    VkStructureType    sType;
    ثابت فراغ*        p_اگلا;
    Vk_Device_حافظہ     حافظہ;
} Vk_حافظہ_Get_Android_Hardware_بفر_Info_ANDROID;

تعريفنوع بنية VkExternalFormatANDROID {
    VkStructureType    sType;
    فراغ*              p_اگلا;
    uint64_t           externalFormat;
} VkExternalFormatANDROID;

تعريفنوع بنية Vk_Android_Hardware_بفر_Format_Properties2_ANDROID {
    VkStructureType                  sType;
    فراغ*                            p_اگلا;
    VkFormat                         format;
    uint64_t                         externalFormat;
    VkFormatFeatureFlags2            formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggested_XChroma_وتھ;
    VkChromaLocation                 suggested_YChroma_وتھ;
} Vk_Android_Hardware_بفر_Format_Properties2_ANDROID;


تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vk_Get_Android_Hardware_بفر_Properties_ANDROID)(VkDevice device, ثابت بنية AHardware_بفر* بفر_2, Vk_Android_Hardware_بفر_Properties_ANDROID* pProperties);
تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vk_Get_حافظہ_Android_Hardware_بفر_ANDROID)(VkDevice device, ثابت Vk_حافظہ_Get_Android_Hardware_بفر_Info_ANDROID* pInfo, بنية AHardware_بفر** p_بفر);

#جے_بنا_تعریف VK_NO_PROTOTYPES

#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_Get_Android_Hardware_بفر_Properties_ANDROID(
    VkDevice                                    device,
    ثابت بنية AHardware_بفر*               بفر_2,
    Vk_Android_Hardware_بفر_Properties_ANDROID*   pProperties);
#جے_انت
#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_Get_حافظہ_Android_Hardware_بفر_ANDROID(
    VkDevice                                    device,
    ثابت Vk_حافظہ_Get_Android_Hardware_بفر_Info_ANDROID* pInfo,
    بنية AHardware_بفر**                    p_بفر);
#جے_انت
#جے_انت


// VK_ANDROID_external_format_resolve is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_ANDROID_external_format_resolve 1

#تعریف_کرو VK_ANDROID_EXTERNAL_FORMAT_RESOLVE_SPEC_نسخہ 1
#تعریف_کرو VK_ANDROID_EXTERNAL_FORMAT_RESOLVE_EXTENSION_NAME "VK_ANDROID_external_format_resolve"

تعريفنوع بنية VkPhysicalDeviceExternalFormatResolveFeaturesANDROID {
    VkStructureType    sType;
    فراغ*              p_اگلا;
    VkBool32           externalFormatResolve;
} VkPhysicalDeviceExternalFormatResolveFeaturesANDROID;

تعريفنوع بنية VkPhysicalDeviceExternalFormatResolvePropertiesANDROID {
    VkStructureType     sType;
    فراغ*               p_اگلا;
    VkBool32            nullColorAttachmentWithExternalFormatResolve;
    VkChromaLocation    external_Format_Resolve_Chroma_وتھ_X;
    VkChromaLocation    external_Format_Resolve_Chroma_وتھ_Y;
} VkPhysicalDeviceExternalFormatResolvePropertiesANDROID;

تعريفنوع بنية Vk_Android_Hardware_بفر_Format_Resolve_Properties_ANDROID {
    VkStructureType    sType;
    فراغ*              p_اگلا;
    VkFormat           colorAttachmentFormat;
} Vk_Android_Hardware_بفر_Format_Resolve_Properties_ANDROID;


#جے_تعریف_شدہ __cplusplus
}
#جے_انت

#جے_انت
