#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VULKAN_SCREEN_H_
#ವ್ಯಾಖ್ಯಾನಿಸು VULKAN_SCREEN_H_ 1

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



// VK_QNX_screen_surface is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು VK_QNX_screen_surface 1

#ವ್ಯಾಖ್ಯಾನಿಸು VK_QNX_SCREEN_SURFACE_SPEC_ಆವೃತ್ತಿ 1
#ವ್ಯಾಖ್ಯಾನಿಸು VK_QNX_SCREEN_SURFACE_EXTENSION_NAME "VK_QNX_screen_surface"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ VkFlags VkScreenSurfaceCreateFlagsQNX;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkScreenSurfaceCreateInfoQNX {
    VkStructureType                  sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*                      p_ಮುಂದಿನ;
    VkScreenSurfaceCreateFlagsQNX    flags;
    ರಚನೆ _screen_context*          context;
    ರಚನೆ screen_ಕಿಟಕಿ*           ಕಿಟಕಿ;
} VkScreenSurfaceCreateInfoQNX;


ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vkCreateScreenSurfaceQNX)(VkInstance instance, ಸ್ಥಿರಾಂಕ VkScreenSurfaceCreateInfoQNX* pCreateInfo, ಸ್ಥಿರಾಂಕ Vk_ಹಂಚಿಕೆ_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceScreenPresentationSupportQNX)(VkPhysicalDevice physicalDevice, uint32_t ಸರತಿ_Family_ಸೂಚ್ಯಂಕ, ರಚನೆ screen_ಕಿಟಕಿ* ಕಿಟಕಿ);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_NO_PROTOTYPES

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ಫಲಿತಾಂಶ VKAPI_CALL vkCreateScreenSurfaceQNX(
    VkInstance                                  instance,
    ಸ್ಥಿರಾಂಕ VkScreenSurfaceCreateInfoQNX*         pCreateInfo,
    ಸ್ಥಿರಾಂಕ Vk_ಹಂಚಿಕೆ_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceScreenPresentationSupportQNX(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    ಸರತಿ_Family_ಸೂಚ್ಯಂಕ,
    ರಚನೆ screen_ಕಿಟಕಿ*                      ಕಿಟಕಿ);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ


// VK_QNX_external_memory_screen_buffer is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು VK_QNX_external_ಸ್ಮರಣೆ_screen_ಬಫರ್ 1

#ವ್ಯಾಖ್ಯಾನಿಸು VK_QNX_EXTERNAL_ಸ್ಮರಣೆ_SCREEN_ಬಫರ್_SPEC_ಆವೃತ್ತಿ 1
#ವ್ಯಾಖ್ಯಾನಿಸು VK_QNX_EXTERNAL_ಸ್ಮರಣೆ_SCREEN_ಬಫರ್_EXTENSION_NAME "VK_QNX_external_memory_screen_buffer"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_Screen_ಬಫರ್_Properties_QNX {
    VkStructureType    sType;
    ಶೂನ್ಯ*              p_ಮುಂದಿನ;
    Vk_Device_ಗಾತ್ರ       ಹಂಚಿಕೆ_ಗಾತ್ರ;
    uint32_t           ಸ್ಮರಣೆ_Type_ಬಿಟ್ಟುಗಳು;
} Vk_Screen_ಬಫರ್_Properties_QNX;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_Screen_ಬಫರ್_Format_Properties_QNX {
    VkStructureType                  sType;
    ಶೂನ್ಯ*                            p_ಮುಂದಿನ;
    VkFormat                         format;
    uint64_t                         externalFormat;
    uint64_t                         screenUsage;
    VkFormatFeatureFlags             formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggested_XChroma_ಸ್ಥಾನಾಂತರ;
    VkChromaLocation                 suggested_YChroma_ಸ್ಥಾನಾಂತರ;
} Vk_Screen_ಬಫರ್_Format_Properties_QNX;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_Import_Screen_ಬಫರ್_Info_QNX {
    VkStructureType           sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*               p_ಮುಂದಿನ;
    ರಚನೆ screen_ಬಫರ್*    ಬಫರ್_2;
} Vk_Import_Screen_ಬಫರ್_Info_QNX;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkExternalFormatQNX {
    VkStructureType    sType;
    ಶೂನ್ಯ*              p_ಮುಂದಿನ;
    uint64_t           externalFormat;
} VkExternalFormatQNX;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_Physical_Device_External_ಸ್ಮರಣೆ_Screen_ಬಫರ್_Features_QNX {
    VkStructureType    sType;
    ಶೂನ್ಯ*              p_ಮುಂದಿನ;
    VkBool32           screen_ಬಫರ್_Import;
} Vk_Physical_Device_External_ಸ್ಮರಣೆ_Screen_ಬಫರ್_Features_QNX;


ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vk_Get_Screen_ಬಫರ್_Properties_QNX)(VkDevice device, ಸ್ಥಿರಾಂಕ ರಚನೆ screen_ಬಫರ್* ಬಫರ್_2, Vk_Screen_ಬಫರ್_Properties_QNX* pProperties);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_NO_PROTOTYPES

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ಫಲಿತಾಂಶ VKAPI_CALL vk_Get_Screen_ಬಫರ್_Properties_QNX(
    VkDevice                                    device,
    ಸ್ಥಿರಾಂಕ ರಚನೆ screen_ಬಫರ್*                ಬಫರ್_2,
    Vk_Screen_ಬಫರ್_Properties_QNX*                pProperties);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ
