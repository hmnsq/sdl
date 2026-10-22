#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VULKAN_IOS_H_
#ವ್ಯಾಖ್ಯಾನಿಸು VULKAN_IOS_H_ 1

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



// VK_MVK_ios_surface is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು VK_MVK_ios_surface 1

#ವ್ಯಾಖ್ಯಾನಿಸು VK_MVK_IOS_SURFACE_SPEC_ಆವೃತ್ತಿ   3
#ವ್ಯಾಖ್ಯಾನಿಸು VK_MVK_IOS_SURFACE_EXTENSION_NAME "VK_MVK_ios_surface"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ VkFlags VkIOSSurfaceCreateFlagsMVK;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkIOSSurfaceCreateInfoMVK {
    VkStructureType               sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*                   p_ಮುಂದಿನ;
    VkIOSSurfaceCreateFlagsMVK    flags;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*                   pView;
} VkIOSSurfaceCreateInfoMVK;


ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vkCreateIOSSurfaceMVK)(VkInstance instance, ಸ್ಥಿರಾಂಕ VkIOSSurfaceCreateInfoMVK* pCreateInfo, ಸ್ಥಿರಾಂಕ Vk_ಹಂಚಿಕೆ_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_NO_PROTOTYPES

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ಫಲಿತಾಂಶ VKAPI_CALL vkCreateIOSSurfaceMVK(
    VkInstance                                  instance,
    ಸ್ಥಿರಾಂಕ VkIOSSurfaceCreateInfoMVK*            pCreateInfo,
    ಸ್ಥಿರಾಂಕ Vk_ಹಂಚಿಕೆ_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ
