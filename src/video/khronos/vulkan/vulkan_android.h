#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VULKAN_ANDROID_H_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VULKAN_ANDROID_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ



// VK_KHR_android_surface is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_KHR_android_surface 1

ਬਣਤਰ ANative_ਖਿੜਕੀ;

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_KHR_ANDROID_SURFACE_SPEC_ਸੰਸਕਰਣ 6
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_KHR_ANDROID_SURFACE_EXTENSION_NAME "VK_KHR_android_surface"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ VkFlags VkAndroidSurfaceCreateFlagsKHR;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkAndroidSurfaceCreateInfoKHR {
    VkStructureType                   sType;
    ਅਚਲ ਖਾਲੀ*                       p_ਅਗਲਾ;
    VkAndroidSurfaceCreateFlagsKHR    flags;
    ਬਣਤਰ ANative_ਖਿੜਕੀ*             ਖਿੜਕੀ;
} VkAndroidSurfaceCreateInfoKHR;


ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vkCreateAndroidSurfaceKHR)(VkInstance instance, ਅਚਲ VkAndroidSurfaceCreateInfoKHR* pCreateInfo, ਅਚਲ Vk_ਵੰਡ_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_NO_PROTOTYPES

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ਨਤੀਜਾ VKAPI_CALL vkCreateAndroidSurfaceKHR(
    VkInstance                                  instance,
    ਅਚਲ VkAndroidSurfaceCreateInfoKHR*        pCreateInfo,
    ਅਚਲ Vk_ਵੰਡ_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ


// VK_ANDROID_external_memory_android_hardware_buffer is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_ANDROID_external_ਸਮ੍ਰਿਤੀ_android_hardware_ਬਫਰ 1

ਬਣਤਰ AHardware_ਬਫਰ;

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_ANDROID_EXTERNAL_ਸਮ੍ਰਿਤੀ_ANDROID_HARDWARE_ਬਫਰ_SPEC_ਸੰਸਕਰਣ 5
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_ANDROID_EXTERNAL_ਸਮ੍ਰਿਤੀ_ANDROID_HARDWARE_ਬਫਰ_EXTENSION_NAME "VK_ANDROID_external_memory_android_hardware_buffer"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_Android_Hardware_ਬਫਰ_Usage_ANDROID {
    VkStructureType    sType;
    ਖਾਲੀ*              p_ਅਗਲਾ;
    uint64_t           android_Hardware_ਬਫਰ_Usage;
} Vk_Android_Hardware_ਬਫਰ_Usage_ANDROID;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_Android_Hardware_ਬਫਰ_Properties_ANDROID {
    VkStructureType    sType;
    ਖਾਲੀ*              p_ਅਗਲਾ;
    Vk_Device_ਮਾਪ       ਵੰਡ_ਮਾਪ;
    uint32_t           ਸਮ੍ਰਿਤੀ_Type_ਬਿੱਟ;
} Vk_Android_Hardware_ਬਫਰ_Properties_ANDROID;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_Android_Hardware_ਬਫਰ_Format_Properties_ANDROID {
    VkStructureType                  sType;
    ਖਾਲੀ*                            p_ਅਗਲਾ;
    VkFormat                         format;
    uint64_t                         externalFormat;
    VkFormatFeatureFlags             formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggested_XChroma_ਵਿੱਥ;
    VkChromaLocation                 suggested_YChroma_ਵਿੱਥ;
} Vk_Android_Hardware_ਬਫਰ_Format_Properties_ANDROID;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_Import_Android_Hardware_ਬਫਰ_Info_ANDROID {
    VkStructureType            sType;
    ਅਚਲ ਖਾਲੀ*                p_ਅਗਲਾ;
    ਬਣਤਰ AHardware_ਬਫਰ*    ਬਫਰ_2;
} Vk_Import_Android_Hardware_ਬਫਰ_Info_ANDROID;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_ਸਮ੍ਰਿਤੀ_Get_Android_Hardware_ਬਫਰ_Info_ANDROID {
    VkStructureType    sType;
    ਅਚਲ ਖਾਲੀ*        p_ਅਗਲਾ;
    Vk_Device_ਸਮ੍ਰਿਤੀ     ਸਮ੍ਰਿਤੀ;
} Vk_ਸਮ੍ਰਿਤੀ_Get_Android_Hardware_ਬਫਰ_Info_ANDROID;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkExternalFormatANDROID {
    VkStructureType    sType;
    ਖਾਲੀ*              p_ਅਗਲਾ;
    uint64_t           externalFormat;
} VkExternalFormatANDROID;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_Android_Hardware_ਬਫਰ_Format_Properties2_ANDROID {
    VkStructureType                  sType;
    ਖਾਲੀ*                            p_ਅਗਲਾ;
    VkFormat                         format;
    uint64_t                         externalFormat;
    VkFormatFeatureFlags2            formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggested_XChroma_ਵਿੱਥ;
    VkChromaLocation                 suggested_YChroma_ਵਿੱਥ;
} Vk_Android_Hardware_ਬਫਰ_Format_Properties2_ANDROID;


ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vk_Get_Android_Hardware_ਬਫਰ_Properties_ANDROID)(VkDevice device, ਅਚਲ ਬਣਤਰ AHardware_ਬਫਰ* ਬਫਰ_2, Vk_Android_Hardware_ਬਫਰ_Properties_ANDROID* pProperties);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vk_Get_ਸਮ੍ਰਿਤੀ_Android_Hardware_ਬਫਰ_ANDROID)(VkDevice device, ਅਚਲ Vk_ਸਮ੍ਰਿਤੀ_Get_Android_Hardware_ਬਫਰ_Info_ANDROID* pInfo, ਬਣਤਰ AHardware_ਬਫਰ** p_ਬਫਰ);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_NO_PROTOTYPES

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ਨਤੀਜਾ VKAPI_CALL vk_Get_Android_Hardware_ਬਫਰ_Properties_ANDROID(
    VkDevice                                    device,
    ਅਚਲ ਬਣਤਰ AHardware_ਬਫਰ*               ਬਫਰ_2,
    Vk_Android_Hardware_ਬਫਰ_Properties_ANDROID*   pProperties);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ਨਤੀਜਾ VKAPI_CALL vk_Get_ਸਮ੍ਰਿਤੀ_Android_Hardware_ਬਫਰ_ANDROID(
    VkDevice                                    device,
    ਅਚਲ Vk_ਸਮ੍ਰਿਤੀ_Get_Android_Hardware_ਬਫਰ_Info_ANDROID* pInfo,
    ਬਣਤਰ AHardware_ਬਫਰ**                    p_ਬਫਰ);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ


// VK_ANDROID_external_format_resolve is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_ANDROID_external_format_resolve 1

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_ANDROID_EXTERNAL_FORMAT_RESOLVE_SPEC_ਸੰਸਕਰਣ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_ANDROID_EXTERNAL_FORMAT_RESOLVE_EXTENSION_NAME "VK_ANDROID_external_format_resolve"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkPhysicalDeviceExternalFormatResolveFeaturesANDROID {
    VkStructureType    sType;
    ਖਾਲੀ*              p_ਅਗਲਾ;
    VkBool32           externalFormatResolve;
} VkPhysicalDeviceExternalFormatResolveFeaturesANDROID;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkPhysicalDeviceExternalFormatResolvePropertiesANDROID {
    VkStructureType     sType;
    ਖਾਲੀ*               p_ਅਗਲਾ;
    VkBool32            nullColorAttachmentWithExternalFormatResolve;
    VkChromaLocation    external_Format_Resolve_Chroma_ਵਿੱਥ_X;
    VkChromaLocation    external_Format_Resolve_Chroma_ਵਿੱਥ_Y;
} VkPhysicalDeviceExternalFormatResolvePropertiesANDROID;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_Android_Hardware_ਬਫਰ_Format_Resolve_Properties_ANDROID {
    VkStructureType    sType;
    ਖਾਲੀ*              p_ਅਗਲਾ;
    VkFormat           colorAttachmentFormat;
} Vk_Android_Hardware_ਬਫਰ_Format_Resolve_Properties_ANDROID;


#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ
