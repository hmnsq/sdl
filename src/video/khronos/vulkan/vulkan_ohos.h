#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VULKAN_OHOS_H_
#ವ್ಯಾಖ್ಯಾನಿಸು VULKAN_OHOS_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
ಬಾಹ್ಯ "C" {
#ಆದರೆ_ಅಂತ್ಯ



// VK_OHOS_external_memory is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು VK_OHOS_external_ಸ್ಮರಣೆ 1

ರಚನೆ OH_Native_ಬಫರ್;

#ವ್ಯಾಖ್ಯಾನಿಸು VK_OHOS_EXTERNAL_ಸ್ಮರಣೆ_SPEC_ಆವೃತ್ತಿ 1
#ವ್ಯಾಖ್ಯಾನಿಸು VK_OHOS_EXTERNAL_ಸ್ಮರಣೆ_EXTENSION_NAME "VK_OHOS_external_memory"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_Native_ಬಫರ್_Usage_OHOS {
    VkStructureType    sType;
    ಶೂನ್ಯ*              p_ಮುಂದಿನ;
    uint64_t           OHOSNative_ಬಫರ್_Usage;
} Vk_Native_ಬಫರ್_Usage_OHOS;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_Native_ಬಫರ್_Properties_OHOS {
    VkStructureType    sType;
    ಶೂನ್ಯ*              p_ಮುಂದಿನ;
    Vk_Device_ಗಾತ್ರ       ಹಂಚಿಕೆ_ಗಾತ್ರ;
    uint32_t           ಸ್ಮರಣೆ_Type_ಬಿಟ್ಟುಗಳು;
} Vk_Native_ಬಫರ್_Properties_OHOS;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_Native_ಬಫರ್_Format_Properties_OHOS {
    VkStructureType                  sType;
    ಶೂನ್ಯ*                            p_ಮುಂದಿನ;
    VkFormat                         format;
    uint64_t                         externalFormat;
    VkFormatFeatureFlags             formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggested_XChroma_ಸ್ಥಾನಾಂತರ;
    VkChromaLocation                 suggested_YChroma_ಸ್ಥಾನಾಂತರ;
} Vk_Native_ಬಫರ್_Format_Properties_OHOS;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_Import_Native_ಬಫರ್_Info_OHOS {
    VkStructureType            sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*                p_ಮುಂದಿನ;
    ರಚನೆ OH_Native_ಬಫರ್*    ಬಫರ್_2;
} Vk_Import_Native_ಬಫರ್_Info_OHOS;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_ಸ್ಮರಣೆ_Get_Native_ಬಫರ್_Info_OHOS {
    VkStructureType    sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*        p_ಮುಂದಿನ;
    Vk_Device_ಸ್ಮರಣೆ     ಸ್ಮರಣೆ;
} Vk_ಸ್ಮರಣೆ_Get_Native_ಬಫರ್_Info_OHOS;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkExternalFormatOHOS {
    VkStructureType    sType;
    ಶೂನ್ಯ*              p_ಮುಂದಿನ;
    uint64_t           externalFormat;
} VkExternalFormatOHOS;


ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vk_Get_Native_ಬಫರ್_Properties_OHOS)(VkDevice device, ಸ್ಥಿರಾಂಕ ರಚನೆ OH_Native_ಬಫರ್* ಬಫರ್_2, Vk_Native_ಬಫರ್_Properties_OHOS* pProperties);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vk_Get_ಸ್ಮರಣೆ_Native_ಬಫರ್_OHOS)(VkDevice device, ಸ್ಥಿರಾಂಕ Vk_ಸ್ಮರಣೆ_Get_Native_ಬಫರ್_Info_OHOS* pInfo, ರಚನೆ OH_Native_ಬಫರ್** p_ಬಫರ್);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_NO_PROTOTYPES

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ಫಲಿತಾಂಶ VKAPI_CALL vk_Get_Native_ಬಫರ್_Properties_OHOS(
    VkDevice                                    device,
    ಸ್ಥಿರಾಂಕ ರಚನೆ OH_Native_ಬಫರ್*               ಬಫರ್_2,
    Vk_Native_ಬಫರ್_Properties_OHOS*               pProperties);
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ಫಲಿತಾಂಶ VKAPI_CALL vk_Get_ಸ್ಮರಣೆ_Native_ಬಫರ್_OHOS(
    VkDevice                                    device,
    ಸ್ಥಿರಾಂಕ Vk_ಸ್ಮರಣೆ_Get_Native_ಬಫರ್_Info_OHOS*      pInfo,
    ರಚನೆ OH_Native_ಬಫರ್**                    p_ಬಫರ್);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ


// VK_OHOS_surface is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು VK_OHOS_surface 1

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Native_ಕಿಟಕಿ OHNative_ಕಿಟಕಿ;

#ವ್ಯಾಖ್ಯಾನಿಸು VK_OHOS_SURFACE_SPEC_ಆವೃತ್ತಿ      1
#ವ್ಯಾಖ್ಯಾನಿಸು VK_OHOS_SURFACE_EXTENSION_NAME    "VK_OHOS_surface"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ VkFlags VkSurfaceCreateFlagsOHOS;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkSurfaceCreateInfoOHOS {
    VkStructureType             sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*                 p_ಮುಂದಿನ;
    VkSurfaceCreateFlagsOHOS    flags;
    OHNative_ಕಿಟಕಿ*             ಕಿಟಕಿ;
} VkSurfaceCreateInfoOHOS;


ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vkCreateSurfaceOHOS)(VkInstance instance, ಸ್ಥಿರಾಂಕ VkSurfaceCreateInfoOHOS* pCreateInfo, ಸ್ಥಿರಾಂಕ Vk_ಹಂಚಿಕೆ_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_NO_PROTOTYPES

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ಫಲಿತಾಂಶ VKAPI_CALL vkCreateSurfaceOHOS(
    VkInstance                                  instance,
    ಸ್ಥಿರಾಂಕ VkSurfaceCreateInfoOHOS*              pCreateInfo,
    ಸ್ಥಿರಾಂಕ Vk_ಹಂಚಿಕೆ_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ
