#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VULKAN_MACOS_H_
#ವ್ಯಾಖ್ಯಾನಿಸು VULKAN_MACOS_H_ 1

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



// VK_MVK_macos_surface is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು VK_MVK_macos_surface 1

#ವ್ಯಾಖ್ಯಾನಿಸು VK_MVK_MACOS_SURFACE_SPEC_ಆವೃತ್ತಿ 3
#ವ್ಯಾಖ್ಯಾನಿಸು VK_MVK_MACOS_SURFACE_EXTENSION_NAME "VK_MVK_macos_surface"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ VkFlags VkMacOSSurfaceCreateFlagsMVK;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkMacOSSurfaceCreateInfoMVK {
    VkStructureType                 sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*                     p_ಮುಂದಿನ;
    VkMacOSSurfaceCreateFlagsMVK    flags;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*                     pView;
} VkMacOSSurfaceCreateInfoMVK;


ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vkCreateMacOSSurfaceMVK)(VkInstance instance, ಸ್ಥಿರಾಂಕ VkMacOSSurfaceCreateInfoMVK* pCreateInfo, ಸ್ಥಿರಾಂಕ Vk_ಹಂಚಿಕೆ_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_NO_PROTOTYPES

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ಫಲಿತಾಂಶ VKAPI_CALL vkCreateMacOSSurfaceMVK(
    VkInstance                                  instance,
    ಸ್ಥಿರಾಂಕ VkMacOSSurfaceCreateInfoMVK*          pCreateInfo,
    ಸ್ಥಿರಾಂಕ Vk_ಹಂಚಿಕೆ_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ
