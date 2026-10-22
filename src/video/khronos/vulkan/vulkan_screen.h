#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VULKAN_SCREEN_H_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VULKAN_SCREEN_H_ 1

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



// VK_QNX_screen_surface is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_QNX_screen_surface 1

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_QNX_SCREEN_SURFACE_SPEC_ਸੰਸਕਰਣ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_QNX_SCREEN_SURFACE_EXTENSION_NAME "VK_QNX_screen_surface"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ VkFlags VkScreenSurfaceCreateFlagsQNX;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkScreenSurfaceCreateInfoQNX {
    VkStructureType                  sType;
    ਅਚਲ ਖਾਲੀ*                      p_ਅਗਲਾ;
    VkScreenSurfaceCreateFlagsQNX    flags;
    ਬਣਤਰ _screen_context*          context;
    ਬਣਤਰ screen_ਖਿੜਕੀ*           ਖਿੜਕੀ;
} VkScreenSurfaceCreateInfoQNX;


ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vkCreateScreenSurfaceQNX)(VkInstance instance, ਅਚਲ VkScreenSurfaceCreateInfoQNX* pCreateInfo, ਅਚਲ Vk_ਵੰਡ_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceScreenPresentationSupportQNX)(VkPhysicalDevice physicalDevice, uint32_t ਕਤਾਰ_Family_ਸੂਚਕਾਂਕ, ਬਣਤਰ screen_ਖਿੜਕੀ* ਖਿੜਕੀ);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_NO_PROTOTYPES

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ਨਤੀਜਾ VKAPI_CALL vkCreateScreenSurfaceQNX(
    VkInstance                                  instance,
    ਅਚਲ VkScreenSurfaceCreateInfoQNX*         pCreateInfo,
    ਅਚਲ Vk_ਵੰਡ_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceScreenPresentationSupportQNX(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    ਕਤਾਰ_Family_ਸੂਚਕਾਂਕ,
    ਬਣਤਰ screen_ਖਿੜਕੀ*                      ਖਿੜਕੀ);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ


// VK_QNX_external_memory_screen_buffer is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_QNX_external_ਸਮ੍ਰਿਤੀ_screen_ਬਫਰ 1

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_QNX_EXTERNAL_ਸਮ੍ਰਿਤੀ_SCREEN_ਬਫਰ_SPEC_ਸੰਸਕਰਣ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_QNX_EXTERNAL_ਸਮ੍ਰਿਤੀ_SCREEN_ਬਫਰ_EXTENSION_NAME "VK_QNX_external_memory_screen_buffer"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_Screen_ਬਫਰ_Properties_QNX {
    VkStructureType    sType;
    ਖਾਲੀ*              p_ਅਗਲਾ;
    Vk_Device_ਮਾਪ       ਵੰਡ_ਮਾਪ;
    uint32_t           ਸਮ੍ਰਿਤੀ_Type_ਬਿੱਟ;
} Vk_Screen_ਬਫਰ_Properties_QNX;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_Screen_ਬਫਰ_Format_Properties_QNX {
    VkStructureType                  sType;
    ਖਾਲੀ*                            p_ਅਗਲਾ;
    VkFormat                         format;
    uint64_t                         externalFormat;
    uint64_t                         screenUsage;
    VkFormatFeatureFlags             formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggested_XChroma_ਵਿੱਥ;
    VkChromaLocation                 suggested_YChroma_ਵਿੱਥ;
} Vk_Screen_ਬਫਰ_Format_Properties_QNX;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_Import_Screen_ਬਫਰ_Info_QNX {
    VkStructureType           sType;
    ਅਚਲ ਖਾਲੀ*               p_ਅਗਲਾ;
    ਬਣਤਰ screen_ਬਫਰ*    ਬਫਰ_2;
} Vk_Import_Screen_ਬਫਰ_Info_QNX;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkExternalFormatQNX {
    VkStructureType    sType;
    ਖਾਲੀ*              p_ਅਗਲਾ;
    uint64_t           externalFormat;
} VkExternalFormatQNX;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_Physical_Device_External_ਸਮ੍ਰਿਤੀ_Screen_ਬਫਰ_Features_QNX {
    VkStructureType    sType;
    ਖਾਲੀ*              p_ਅਗਲਾ;
    VkBool32           screen_ਬਫਰ_Import;
} Vk_Physical_Device_External_ਸਮ੍ਰਿਤੀ_Screen_ਬਫਰ_Features_QNX;


ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vk_Get_Screen_ਬਫਰ_Properties_QNX)(VkDevice device, ਅਚਲ ਬਣਤਰ screen_ਬਫਰ* ਬਫਰ_2, Vk_Screen_ਬਫਰ_Properties_QNX* pProperties);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_NO_PROTOTYPES

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ਨਤੀਜਾ VKAPI_CALL vk_Get_Screen_ਬਫਰ_Properties_QNX(
    VkDevice                                    device,
    ਅਚਲ ਬਣਤਰ screen_ਬਫਰ*                ਬਫਰ_2,
    Vk_Screen_ਬਫਰ_Properties_QNX*                pProperties);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ
