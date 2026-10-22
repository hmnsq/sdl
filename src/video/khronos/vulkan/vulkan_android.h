#که_نه_تعریف_شوی VULKAN_ANDROID_H_
#تعریف_کړه VULKAN_ANDROID_H_ 1

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



// VK_KHR_android_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه VK_KHR_android_surface 1

بنية ANative_کړکۍ;

#تعریف_کړه VK_KHR_ANDROID_SURFACE_SPEC_نسخه 6
#تعریف_کړه VK_KHR_ANDROID_SURFACE_EXTENSION_NAME "VK_KHR_android_surface"

تعريفنوع VkFlags VkAndroidSurfaceCreateFlagsKHR;

تعريفنوع بنية VkAndroidSurfaceCreateInfoKHR {
    VkStructureType                   sType;
    ثابت فراغ*                       p_بل;
    VkAndroidSurfaceCreateFlagsKHR    flags;
    بنية ANative_کړکۍ*             کړکۍ;
} VkAndroidSurfaceCreateInfoKHR;


تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vkCreateAndroidSurfaceKHR)(VkInstance instance, ثابت VkAndroidSurfaceCreateInfoKHR* pCreateInfo, ثابت Vk_ویش_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#که_نه_تعریف_شوی VK_NO_PROTOTYPES

#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_پایله VKAPI_CALL vkCreateAndroidSurfaceKHR(
    VkInstance                                  instance,
    ثابت VkAndroidSurfaceCreateInfoKHR*        pCreateInfo,
    ثابت Vk_ویش_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#د_که_پای
#د_که_پای


// VK_ANDROID_external_memory_android_hardware_buffer is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه VK_ANDROID_external_حافظه_android_hardware_بفر 1

بنية AHardware_بفر;

#تعریف_کړه VK_ANDROID_EXTERNAL_حافظه_ANDROID_HARDWARE_بفر_SPEC_نسخه 5
#تعریف_کړه VK_ANDROID_EXTERNAL_حافظه_ANDROID_HARDWARE_بفر_EXTENSION_NAME "VK_ANDROID_external_memory_android_hardware_buffer"

تعريفنوع بنية Vk_Android_Hardware_بفر_Usage_ANDROID {
    VkStructureType    sType;
    فراغ*              p_بل;
    uint64_t           android_Hardware_بفر_Usage;
} Vk_Android_Hardware_بفر_Usage_ANDROID;

تعريفنوع بنية Vk_Android_Hardware_بفر_Properties_ANDROID {
    VkStructureType    sType;
    فراغ*              p_بل;
    Vk_Device_اندازه       ویش_اندازه;
    uint32_t           حافظه_Type_بټونه;
} Vk_Android_Hardware_بفر_Properties_ANDROID;

تعريفنوع بنية Vk_Android_Hardware_بفر_Format_Properties_ANDROID {
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
} Vk_Android_Hardware_بفر_Format_Properties_ANDROID;

تعريفنوع بنية Vk_Import_Android_Hardware_بفر_Info_ANDROID {
    VkStructureType            sType;
    ثابت فراغ*                p_بل;
    بنية AHardware_بفر*    بفر_2;
} Vk_Import_Android_Hardware_بفر_Info_ANDROID;

تعريفنوع بنية Vk_حافظه_Get_Android_Hardware_بفر_Info_ANDROID {
    VkStructureType    sType;
    ثابت فراغ*        p_بل;
    Vk_Device_حافظه     حافظه;
} Vk_حافظه_Get_Android_Hardware_بفر_Info_ANDROID;

تعريفنوع بنية VkExternalFormatANDROID {
    VkStructureType    sType;
    فراغ*              p_بل;
    uint64_t           externalFormat;
} VkExternalFormatANDROID;

تعريفنوع بنية Vk_Android_Hardware_بفر_Format_Properties2_ANDROID {
    VkStructureType                  sType;
    فراغ*                            p_بل;
    VkFormat                         format;
    uint64_t                         externalFormat;
    VkFormatFeatureFlags2            formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggested_XChroma_دننه_واټن;
    VkChromaLocation                 suggested_YChroma_دننه_واټن;
} Vk_Android_Hardware_بفر_Format_Properties2_ANDROID;


تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vk_Get_Android_Hardware_بفر_Properties_ANDROID)(VkDevice device, ثابت بنية AHardware_بفر* بفر_2, Vk_Android_Hardware_بفر_Properties_ANDROID* pProperties);
تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vk_Get_حافظه_Android_Hardware_بفر_ANDROID)(VkDevice device, ثابت Vk_حافظه_Get_Android_Hardware_بفر_Info_ANDROID* pInfo, بنية AHardware_بفر** p_بفر);

#که_نه_تعریف_شوی VK_NO_PROTOTYPES

#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_پایله VKAPI_CALL vk_Get_Android_Hardware_بفر_Properties_ANDROID(
    VkDevice                                    device,
    ثابت بنية AHardware_بفر*               بفر_2,
    Vk_Android_Hardware_بفر_Properties_ANDROID*   pProperties);
#د_که_پای
#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_پایله VKAPI_CALL vk_Get_حافظه_Android_Hardware_بفر_ANDROID(
    VkDevice                                    device,
    ثابت Vk_حافظه_Get_Android_Hardware_بفر_Info_ANDROID* pInfo,
    بنية AHardware_بفر**                    p_بفر);
#د_که_پای
#د_که_پای


// VK_ANDROID_external_format_resolve is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه VK_ANDROID_external_format_resolve 1

#تعریف_کړه VK_ANDROID_EXTERNAL_FORMAT_RESOLVE_SPEC_نسخه 1
#تعریف_کړه VK_ANDROID_EXTERNAL_FORMAT_RESOLVE_EXTENSION_NAME "VK_ANDROID_external_format_resolve"

تعريفنوع بنية VkPhysicalDeviceExternalFormatResolveFeaturesANDROID {
    VkStructureType    sType;
    فراغ*              p_بل;
    VkBool32           externalFormatResolve;
} VkPhysicalDeviceExternalFormatResolveFeaturesANDROID;

تعريفنوع بنية VkPhysicalDeviceExternalFormatResolvePropertiesANDROID {
    VkStructureType     sType;
    فراغ*               p_بل;
    VkBool32            nullColorAttachmentWithExternalFormatResolve;
    VkChromaLocation    external_Format_Resolve_Chroma_دننه_واټن_X;
    VkChromaLocation    external_Format_Resolve_Chroma_دننه_واټن_Y;
} VkPhysicalDeviceExternalFormatResolvePropertiesANDROID;

تعريفنوع بنية Vk_Android_Hardware_بفر_Format_Resolve_Properties_ANDROID {
    VkStructureType    sType;
    فراغ*              p_بل;
    VkFormat           colorAttachmentFormat;
} Vk_Android_Hardware_بفر_Format_Resolve_Properties_ANDROID;


#که_تعریف_شوی __cplusplus
}
#د_که_پای

#د_که_پای
