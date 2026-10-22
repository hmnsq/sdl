#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VULKAN_DIRECTFB_H_
#ವ್ಯಾಖ್ಯಾನಿಸು VULKAN_DIRECTFB_H_ 1

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



// VK_EXT_directfb_surface is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು VK_EXT_directfb_surface 1

#ವ್ಯಾಖ್ಯಾನಿಸು VK_EXT_DIRECTFB_SURFACE_SPEC_ಆವೃತ್ತಿ 1
#ವ್ಯಾಖ್ಯಾನಿಸು VK_EXT_DIRECTFB_SURFACE_EXTENSION_NAME "VK_EXT_directfb_surface"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ VkFlags Vk_ನೇರ_FBSurface_Create_Flags_EXT;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_ನೇರ_FBSurface_Create_Info_EXT {
    VkStructureType                    sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*                        p_ಮುಂದಿನ;
    Vk_ನೇರ_FBSurface_Create_Flags_EXT    flags;
    IDirectFB*                         dfb;
    IDirectFBSurface*                  surface;
} Vk_ನೇರ_FBSurface_Create_Info_EXT;


ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vk_Create_ನೇರ_FBSurface_EXT)(VkInstance instance, ಸ್ಥಿರಾಂಕ Vk_ನೇರ_FBSurface_Create_Info_EXT* pCreateInfo, ಸ್ಥಿರಾಂಕ Vk_ಹಂಚಿಕೆ_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ VkBool32 (VKAPI_PTR *PFN_vk_Get_Physical_Device_ನೇರ_FBPresentation_Support_EXT)(VkPhysicalDevice physicalDevice, uint32_t ಸರತಿ_Family_ಸೂಚ್ಯಂಕ, IDirectFB* dfb);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_NO_PROTOTYPES

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ಫಲಿತಾಂಶ VKAPI_CALL vk_Create_ನೇರ_FBSurface_EXT(
    VkInstance                                  instance,
    ಸ್ಥಿರಾಂಕ Vk_ನೇರ_FBSurface_Create_Info_EXT*       pCreateInfo,
    ಸ್ಥಿರಾಂಕ Vk_ಹಂಚಿಕೆ_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vk_Get_Physical_Device_ನೇರ_FBPresentation_Support_EXT(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    ಸರತಿ_Family_ಸೂಚ್ಯಂಕ,
    IDirectFB*                                  dfb);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ
