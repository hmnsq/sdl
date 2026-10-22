#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VULKAN_OHOS_H_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VULKAN_OHOS_H_ 1

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



// VK_OHOS_external_memory is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_OHOS_external_ਸਮ੍ਰਿਤੀ 1

ਬਣਤਰ OH_Native_ਬਫਰ;

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_OHOS_EXTERNAL_ਸਮ੍ਰਿਤੀ_SPEC_ਸੰਸਕਰਣ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_OHOS_EXTERNAL_ਸਮ੍ਰਿਤੀ_EXTENSION_NAME "VK_OHOS_external_memory"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_Native_ਬਫਰ_Usage_OHOS {
    VkStructureType    sType;
    ਖਾਲੀ*              p_ਅਗਲਾ;
    uint64_t           OHOSNative_ਬਫਰ_Usage;
} Vk_Native_ਬਫਰ_Usage_OHOS;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_Native_ਬਫਰ_Properties_OHOS {
    VkStructureType    sType;
    ਖਾਲੀ*              p_ਅਗਲਾ;
    Vk_Device_ਮਾਪ       ਵੰਡ_ਮਾਪ;
    uint32_t           ਸਮ੍ਰਿਤੀ_Type_ਬਿੱਟ;
} Vk_Native_ਬਫਰ_Properties_OHOS;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_Native_ਬਫਰ_Format_Properties_OHOS {
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
} Vk_Native_ਬਫਰ_Format_Properties_OHOS;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_Import_Native_ਬਫਰ_Info_OHOS {
    VkStructureType            sType;
    ਅਚਲ ਖਾਲੀ*                p_ਅਗਲਾ;
    ਬਣਤਰ OH_Native_ਬਫਰ*    ਬਫਰ_2;
} Vk_Import_Native_ਬਫਰ_Info_OHOS;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_ਸਮ੍ਰਿਤੀ_Get_Native_ਬਫਰ_Info_OHOS {
    VkStructureType    sType;
    ਅਚਲ ਖਾਲੀ*        p_ਅਗਲਾ;
    Vk_Device_ਸਮ੍ਰਿਤੀ     ਸਮ੍ਰਿਤੀ;
} Vk_ਸਮ੍ਰਿਤੀ_Get_Native_ਬਫਰ_Info_OHOS;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkExternalFormatOHOS {
    VkStructureType    sType;
    ਖਾਲੀ*              p_ਅਗਲਾ;
    uint64_t           externalFormat;
} VkExternalFormatOHOS;


ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vk_Get_Native_ਬਫਰ_Properties_OHOS)(VkDevice device, ਅਚਲ ਬਣਤਰ OH_Native_ਬਫਰ* ਬਫਰ_2, Vk_Native_ਬਫਰ_Properties_OHOS* pProperties);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vk_Get_ਸਮ੍ਰਿਤੀ_Native_ਬਫਰ_OHOS)(VkDevice device, ਅਚਲ Vk_ਸਮ੍ਰਿਤੀ_Get_Native_ਬਫਰ_Info_OHOS* pInfo, ਬਣਤਰ OH_Native_ਬਫਰ** p_ਬਫਰ);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_NO_PROTOTYPES

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ਨਤੀਜਾ VKAPI_CALL vk_Get_Native_ਬਫਰ_Properties_OHOS(
    VkDevice                                    device,
    ਅਚਲ ਬਣਤਰ OH_Native_ਬਫਰ*               ਬਫਰ_2,
    Vk_Native_ਬਫਰ_Properties_OHOS*               pProperties);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ਨਤੀਜਾ VKAPI_CALL vk_Get_ਸਮ੍ਰਿਤੀ_Native_ਬਫਰ_OHOS(
    VkDevice                                    device,
    ਅਚਲ Vk_ਸਮ੍ਰਿਤੀ_Get_Native_ਬਫਰ_Info_OHOS*      pInfo,
    ਬਣਤਰ OH_Native_ਬਫਰ**                    p_ਬਫਰ);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ


// VK_OHOS_surface is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_OHOS_surface 1

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Native_ਖਿੜਕੀ OHNative_ਖਿੜਕੀ;

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_OHOS_SURFACE_SPEC_ਸੰਸਕਰਣ      1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_OHOS_SURFACE_EXTENSION_NAME    "VK_OHOS_surface"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ VkFlags VkSurfaceCreateFlagsOHOS;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkSurfaceCreateInfoOHOS {
    VkStructureType             sType;
    ਅਚਲ ਖਾਲੀ*                 p_ਅਗਲਾ;
    VkSurfaceCreateFlagsOHOS    flags;
    OHNative_ਖਿੜਕੀ*             ਖਿੜਕੀ;
} VkSurfaceCreateInfoOHOS;


ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vkCreateSurfaceOHOS)(VkInstance instance, ਅਚਲ VkSurfaceCreateInfoOHOS* pCreateInfo, ਅਚਲ Vk_ਵੰਡ_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_NO_PROTOTYPES

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ਨਤੀਜਾ VKAPI_CALL vkCreateSurfaceOHOS(
    VkInstance                                  instance,
    ਅਚਲ VkSurfaceCreateInfoOHOS*              pCreateInfo,
    ਅਚਲ Vk_ਵੰਡ_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ
