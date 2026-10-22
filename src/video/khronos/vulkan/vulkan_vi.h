#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VULKAN_VI_H_
#ವ್ಯಾಖ್ಯಾನಿಸು VULKAN_VI_H_ 1

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



// VK_NN_vi_surface is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು VK_NN_vi_surface 1

#ವ್ಯಾಖ್ಯಾನಿಸು VK_NN_VI_SURFACE_SPEC_ಆವೃತ್ತಿ     1
#ವ್ಯಾಖ್ಯಾನಿಸು VK_NN_VI_SURFACE_EXTENSION_NAME   "VK_NN_vi_surface"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ VkFlags VkViSurfaceCreateFlagsNN;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkViSurfaceCreateInfoNN {
    VkStructureType             sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*                 p_ಮುಂದಿನ;
    VkViSurfaceCreateFlagsNN    flags;
    ಶೂನ್ಯ*                       ಕಿಟಕಿ;
} VkViSurfaceCreateInfoNN;


ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vkCreateViSurfaceNN)(VkInstance instance, ಸ್ಥಿರಾಂಕ VkViSurfaceCreateInfoNN* pCreateInfo, ಸ್ಥಿರಾಂಕ Vk_ಹಂಚಿಕೆ_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_NO_PROTOTYPES

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ಫಲಿತಾಂಶ VKAPI_CALL vkCreateViSurfaceNN(
    VkInstance                                  instance,
    ಸ್ಥಿರಾಂಕ VkViSurfaceCreateInfoNN*              pCreateInfo,
    ಸ್ಥಿರಾಂಕ Vk_ಹಂಚಿಕೆ_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ
