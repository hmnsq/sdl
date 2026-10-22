#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VULKAN_UBM_H_
#ವ್ಯಾಖ್ಯಾನಿಸು VULKAN_UBM_H_ 1

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



// VK_SEC_ubm_surface is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು VK_SEC_ubm_surface 1

#ವ್ಯಾಖ್ಯಾನಿಸು VK_SEC_UBM_SURFACE_SPEC_ಆವೃತ್ತಿ   1
#ವ್ಯಾಖ್ಯಾನಿಸು VK_SEC_UBM_SURFACE_EXTENSION_NAME "VK_SEC_ubm_surface"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ VkFlags VkUbmSurfaceCreateFlagsSEC;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkUbmSurfaceCreateInfoSEC {
    VkStructureType               sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*                   p_ಮುಂದಿನ;
    VkUbmSurfaceCreateFlagsSEC    flags;
    ರಚನೆ ubm_device*            device;
    ರಚನೆ ubm_surface*           surface;
} VkUbmSurfaceCreateInfoSEC;


ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vkCreateUbmSurfaceSEC)(VkInstance instance, ಸ್ಥಿರಾಂಕ VkUbmSurfaceCreateInfoSEC* pCreateInfo, ಸ್ಥಿರಾಂಕ Vk_ಹಂಚಿಕೆ_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceUbmPresentationSupportSEC)(VkPhysicalDevice physicalDevice, uint32_t ಸರತಿ_Family_ಸೂಚ್ಯಂಕ, ರಚನೆ ubm_device* device);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_NO_PROTOTYPES

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ಫಲಿತಾಂಶ VKAPI_CALL vkCreateUbmSurfaceSEC(
    VkInstance                                  instance,
    ಸ್ಥಿರಾಂಕ VkUbmSurfaceCreateInfoSEC*            pCreateInfo,
    ಸ್ಥಿರಾಂಕ Vk_ಹಂಚಿಕೆ_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceUbmPresentationSupportSEC(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    ಸರತಿ_Family_ಸೂಚ್ಯಂಕ,
    ರಚನೆ ubm_device*                          device);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ
