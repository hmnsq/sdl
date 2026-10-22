#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VULKAN_ANDROID_H_
#ವ್ಯಾಖ್ಯಾನಿಸು VULKAN_ANDROID_H_ 1

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



// VK_KHR_android_surface is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು VK_KHR_android_surface 1

ರಚನೆ ANative_ಕಿಟಕಿ;

#ವ್ಯಾಖ್ಯಾನಿಸು VK_KHR_ANDROID_SURFACE_SPEC_ಆವೃತ್ತಿ 6
#ವ್ಯಾಖ್ಯಾನಿಸು VK_KHR_ANDROID_SURFACE_EXTENSION_NAME "VK_KHR_android_surface"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ VkFlags VkAndroidSurfaceCreateFlagsKHR;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkAndroidSurfaceCreateInfoKHR {
    VkStructureType                   sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*                       p_ಮುಂದಿನ;
    VkAndroidSurfaceCreateFlagsKHR    flags;
    ರಚನೆ ANative_ಕಿಟಕಿ*             ಕಿಟಕಿ;
} VkAndroidSurfaceCreateInfoKHR;


ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vkCreateAndroidSurfaceKHR)(VkInstance instance, ಸ್ಥಿರಾಂಕ VkAndroidSurfaceCreateInfoKHR* pCreateInfo, ಸ್ಥಿರಾಂಕ Vk_ಹಂಚಿಕೆ_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_NO_PROTOTYPES

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ಫಲಿತಾಂಶ VKAPI_CALL vkCreateAndroidSurfaceKHR(
    VkInstance                                  instance,
    ಸ್ಥಿರಾಂಕ VkAndroidSurfaceCreateInfoKHR*        pCreateInfo,
    ಸ್ಥಿರಾಂಕ Vk_ಹಂಚಿಕೆ_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ


// VK_ANDROID_external_memory_android_hardware_buffer is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು VK_ANDROID_external_ಸ್ಮರಣೆ_android_hardware_ಬಫರ್ 1

ರಚನೆ AHardware_ಬಫರ್;

#ವ್ಯಾಖ್ಯಾನಿಸು VK_ANDROID_EXTERNAL_ಸ್ಮರಣೆ_ANDROID_HARDWARE_ಬಫರ್_SPEC_ಆವೃತ್ತಿ 5
#ವ್ಯಾಖ್ಯಾನಿಸು VK_ANDROID_EXTERNAL_ಸ್ಮರಣೆ_ANDROID_HARDWARE_ಬಫರ್_EXTENSION_NAME "VK_ANDROID_external_memory_android_hardware_buffer"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_Android_Hardware_ಬಫರ್_Usage_ANDROID {
    VkStructureType    sType;
    ಶೂನ್ಯ*              p_ಮುಂದಿನ;
    uint64_t           android_Hardware_ಬಫರ್_Usage;
} Vk_Android_Hardware_ಬಫರ್_Usage_ANDROID;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_Android_Hardware_ಬಫರ್_Properties_ANDROID {
    VkStructureType    sType;
    ಶೂನ್ಯ*              p_ಮುಂದಿನ;
    Vk_Device_ಗಾತ್ರ       ಹಂಚಿಕೆ_ಗಾತ್ರ;
    uint32_t           ಸ್ಮರಣೆ_Type_ಬಿಟ್ಟುಗಳು;
} Vk_Android_Hardware_ಬಫರ್_Properties_ANDROID;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_Android_Hardware_ಬಫರ್_Format_Properties_ANDROID {
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
} Vk_Android_Hardware_ಬಫರ್_Format_Properties_ANDROID;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_Import_Android_Hardware_ಬಫರ್_Info_ANDROID {
    VkStructureType            sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*                p_ಮುಂದಿನ;
    ರಚನೆ AHardware_ಬಫರ್*    ಬಫರ್_2;
} Vk_Import_Android_Hardware_ಬಫರ್_Info_ANDROID;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_ಸ್ಮರಣೆ_Get_Android_Hardware_ಬಫರ್_Info_ANDROID {
    VkStructureType    sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*        p_ಮುಂದಿನ;
    Vk_Device_ಸ್ಮರಣೆ     ಸ್ಮರಣೆ;
} Vk_ಸ್ಮರಣೆ_Get_Android_Hardware_ಬಫರ್_Info_ANDROID;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkExternalFormatANDROID {
    VkStructureType    sType;
    ಶೂನ್ಯ*              p_ಮುಂದಿನ;
    uint64_t           externalFormat;
} VkExternalFormatANDROID;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_Android_Hardware_ಬಫರ್_Format_Properties2_ANDROID {
    VkStructureType                  sType;
    ಶೂನ್ಯ*                            p_ಮುಂದಿನ;
    VkFormat                         format;
    uint64_t                         externalFormat;
    VkFormatFeatureFlags2            formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggested_XChroma_ಸ್ಥಾನಾಂತರ;
    VkChromaLocation                 suggested_YChroma_ಸ್ಥಾನಾಂತರ;
} Vk_Android_Hardware_ಬಫರ್_Format_Properties2_ANDROID;


ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vk_Get_Android_Hardware_ಬಫರ್_Properties_ANDROID)(VkDevice device, ಸ್ಥಿರಾಂಕ ರಚನೆ AHardware_ಬಫರ್* ಬಫರ್_2, Vk_Android_Hardware_ಬಫರ್_Properties_ANDROID* pProperties);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vk_Get_ಸ್ಮರಣೆ_Android_Hardware_ಬಫರ್_ANDROID)(VkDevice device, ಸ್ಥಿರಾಂಕ Vk_ಸ್ಮರಣೆ_Get_Android_Hardware_ಬಫರ್_Info_ANDROID* pInfo, ರಚನೆ AHardware_ಬಫರ್** p_ಬಫರ್);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_NO_PROTOTYPES

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ಫಲಿತಾಂಶ VKAPI_CALL vk_Get_Android_Hardware_ಬಫರ್_Properties_ANDROID(
    VkDevice                                    device,
    ಸ್ಥಿರಾಂಕ ರಚನೆ AHardware_ಬಫರ್*               ಬಫರ್_2,
    Vk_Android_Hardware_ಬಫರ್_Properties_ANDROID*   pProperties);
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ಫಲಿತಾಂಶ VKAPI_CALL vk_Get_ಸ್ಮರಣೆ_Android_Hardware_ಬಫರ್_ANDROID(
    VkDevice                                    device,
    ಸ್ಥಿರಾಂಕ Vk_ಸ್ಮರಣೆ_Get_Android_Hardware_ಬಫರ್_Info_ANDROID* pInfo,
    ರಚನೆ AHardware_ಬಫರ್**                    p_ಬಫರ್);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ


// VK_ANDROID_external_format_resolve is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು VK_ANDROID_external_format_resolve 1

#ವ್ಯಾಖ್ಯಾನಿಸು VK_ANDROID_EXTERNAL_FORMAT_RESOLVE_SPEC_ಆವೃತ್ತಿ 1
#ವ್ಯಾಖ್ಯಾನಿಸು VK_ANDROID_EXTERNAL_FORMAT_RESOLVE_EXTENSION_NAME "VK_ANDROID_external_format_resolve"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkPhysicalDeviceExternalFormatResolveFeaturesANDROID {
    VkStructureType    sType;
    ಶೂನ್ಯ*              p_ಮುಂದಿನ;
    VkBool32           externalFormatResolve;
} VkPhysicalDeviceExternalFormatResolveFeaturesANDROID;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkPhysicalDeviceExternalFormatResolvePropertiesANDROID {
    VkStructureType     sType;
    ಶೂನ್ಯ*               p_ಮುಂದಿನ;
    VkBool32            nullColorAttachmentWithExternalFormatResolve;
    VkChromaLocation    external_Format_Resolve_Chroma_ಸ್ಥಾನಾಂತರ_X;
    VkChromaLocation    external_Format_Resolve_Chroma_ಸ್ಥಾನಾಂತರ_Y;
} VkPhysicalDeviceExternalFormatResolvePropertiesANDROID;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_Android_Hardware_ಬಫರ್_Format_Resolve_Properties_ANDROID {
    VkStructureType    sType;
    ಶೂನ್ಯ*              p_ಮುಂದಿನ;
    VkFormat           colorAttachmentFormat;
} Vk_Android_Hardware_ಬಫರ್_Format_Resolve_Properties_ANDROID;


#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ
