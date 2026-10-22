#جيڪڏهن_وصف_نه_ٿيل VULKAN_ANDROID_H_
#وصف_ڪريو VULKAN_ANDROID_H_ 1

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



// VK_KHR_android_surface is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو VK_KHR_android_surface 1

بنية ANative_دري;

#وصف_ڪريو VK_KHR_ANDROID_SURFACE_SPEC_نسخو 6
#وصف_ڪريو VK_KHR_ANDROID_SURFACE_EXTENSION_NAME "VK_KHR_android_surface"

تعريفنوع VkFlags VkAndroidSurfaceCreateFlagsKHR;

تعريفنوع بنية VkAndroidSurfaceCreateInfoKHR {
    VkStructureType                   sType;
    ثابت فراغ*                       p_ايندڙ;
    VkAndroidSurfaceCreateFlagsKHR    flags;
    بنية ANative_دري*             دري;
} VkAndroidSurfaceCreateInfoKHR;


تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vkCreateAndroidSurfaceKHR)(VkInstance instance, ثابت VkAndroidSurfaceCreateInfoKHR* pCreateInfo, ثابت Vk_ورهاست_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#جيڪڏهن_وصف_نه_ٿيل VK_NO_PROTOTYPES

#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتيجو VKAPI_CALL vkCreateAndroidSurfaceKHR(
    VkInstance                                  instance,
    ثابت VkAndroidSurfaceCreateInfoKHR*        pCreateInfo,
    ثابت Vk_ورهاست_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#جيڪڏهن_پورو
#جيڪڏهن_پورو


// VK_ANDROID_external_memory_android_hardware_buffer is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو VK_ANDROID_external_يادگيري_android_hardware_بفر 1

بنية AHardware_بفر;

#وصف_ڪريو VK_ANDROID_EXTERNAL_يادگيري_ANDROID_HARDWARE_بفر_SPEC_نسخو 5
#وصف_ڪريو VK_ANDROID_EXTERNAL_يادگيري_ANDROID_HARDWARE_بفر_EXTENSION_NAME "VK_ANDROID_external_memory_android_hardware_buffer"

تعريفنوع بنية Vk_Android_Hardware_بفر_Usage_ANDROID {
    VkStructureType    sType;
    فراغ*              p_ايندڙ;
    uint64_t           android_Hardware_بفر_Usage;
} Vk_Android_Hardware_بفر_Usage_ANDROID;

تعريفنوع بنية Vk_Android_Hardware_بفر_Properties_ANDROID {
    VkStructureType    sType;
    فراغ*              p_ايندڙ;
    Vk_Device_سائيز       ورهاست_سائيز;
    uint32_t           يادگيري_Type_بٽ;
} Vk_Android_Hardware_بفر_Properties_ANDROID;

تعريفنوع بنية Vk_Android_Hardware_بفر_Format_Properties_ANDROID {
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
} Vk_Android_Hardware_بفر_Format_Properties_ANDROID;

تعريفنوع بنية Vk_Import_Android_Hardware_بفر_Info_ANDROID {
    VkStructureType            sType;
    ثابت فراغ*                p_ايندڙ;
    بنية AHardware_بفر*    بفر_2;
} Vk_Import_Android_Hardware_بفر_Info_ANDROID;

تعريفنوع بنية Vk_يادگيري_Get_Android_Hardware_بفر_Info_ANDROID {
    VkStructureType    sType;
    ثابت فراغ*        p_ايندڙ;
    Vk_Device_يادگيري     يادگيري;
} Vk_يادگيري_Get_Android_Hardware_بفر_Info_ANDROID;

تعريفنوع بنية VkExternalFormatANDROID {
    VkStructureType    sType;
    فراغ*              p_ايندڙ;
    uint64_t           externalFormat;
} VkExternalFormatANDROID;

تعريفنوع بنية Vk_Android_Hardware_بفر_Format_Properties2_ANDROID {
    VkStructureType                  sType;
    فراغ*                            p_ايندڙ;
    VkFormat                         format;
    uint64_t                         externalFormat;
    VkFormatFeatureFlags2            formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggested_XChroma_وٿي;
    VkChromaLocation                 suggested_YChroma_وٿي;
} Vk_Android_Hardware_بفر_Format_Properties2_ANDROID;


تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vk_Get_Android_Hardware_بفر_Properties_ANDROID)(VkDevice device, ثابت بنية AHardware_بفر* بفر_2, Vk_Android_Hardware_بفر_Properties_ANDROID* pProperties);
تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vk_Get_يادگيري_Android_Hardware_بفر_ANDROID)(VkDevice device, ثابت Vk_يادگيري_Get_Android_Hardware_بفر_Info_ANDROID* pInfo, بنية AHardware_بفر** p_بفر);

#جيڪڏهن_وصف_نه_ٿيل VK_NO_PROTOTYPES

#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتيجو VKAPI_CALL vk_Get_Android_Hardware_بفر_Properties_ANDROID(
    VkDevice                                    device,
    ثابت بنية AHardware_بفر*               بفر_2,
    Vk_Android_Hardware_بفر_Properties_ANDROID*   pProperties);
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتيجو VKAPI_CALL vk_Get_يادگيري_Android_Hardware_بفر_ANDROID(
    VkDevice                                    device,
    ثابت Vk_يادگيري_Get_Android_Hardware_بفر_Info_ANDROID* pInfo,
    بنية AHardware_بفر**                    p_بفر);
#جيڪڏهن_پورو
#جيڪڏهن_پورو


// VK_ANDROID_external_format_resolve is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو VK_ANDROID_external_format_resolve 1

#وصف_ڪريو VK_ANDROID_EXTERNAL_FORMAT_RESOLVE_SPEC_نسخو 1
#وصف_ڪريو VK_ANDROID_EXTERNAL_FORMAT_RESOLVE_EXTENSION_NAME "VK_ANDROID_external_format_resolve"

تعريفنوع بنية VkPhysicalDeviceExternalFormatResolveFeaturesANDROID {
    VkStructureType    sType;
    فراغ*              p_ايندڙ;
    VkBool32           externalFormatResolve;
} VkPhysicalDeviceExternalFormatResolveFeaturesANDROID;

تعريفنوع بنية VkPhysicalDeviceExternalFormatResolvePropertiesANDROID {
    VkStructureType     sType;
    فراغ*               p_ايندڙ;
    VkBool32            nullColorAttachmentWithExternalFormatResolve;
    VkChromaLocation    external_Format_Resolve_Chroma_وٿي_X;
    VkChromaLocation    external_Format_Resolve_Chroma_وٿي_Y;
} VkPhysicalDeviceExternalFormatResolvePropertiesANDROID;

تعريفنوع بنية Vk_Android_Hardware_بفر_Format_Resolve_Properties_ANDROID {
    VkStructureType    sType;
    فراغ*              p_ايندڙ;
    VkFormat           colorAttachmentFormat;
} Vk_Android_Hardware_بفر_Format_Resolve_Properties_ANDROID;


#جيڪڏهن_وصف_ٿيل __cplusplus
}
#جيڪڏهن_پورو

#جيڪڏهن_پورو
