#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VULKAN_GGP_H_
#ವ್ಯಾಖ್ಯಾನಿಸು VULKAN_GGP_H_ 1

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



// VK_GGP_stream_descriptor_surface is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು VK_GGP_ಹರಿವು_descriptor_surface 1

#ವ್ಯಾಖ್ಯಾನಿಸು VK_GGP_ಹರಿವು_DESCRIPTOR_SURFACE_SPEC_ಆವೃತ್ತಿ 1
#ವ್ಯಾಖ್ಯಾನಿಸು VK_GGP_ಹರಿವು_DESCRIPTOR_SURFACE_EXTENSION_NAME "VK_GGP_stream_descriptor_surface"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ VkFlags Vk_ಹರಿವು_Descriptor_Surface_Create_Flags_GGP;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_ಹರಿವು_Descriptor_Surface_Create_Info_GGP {
    VkStructureType                            sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*                                p_ಮುಂದಿನ;
    Vk_ಹರಿವು_Descriptor_Surface_Create_Flags_GGP    flags;
    Ggp_ಹರಿವು_Descriptor                        ಹರಿವು_Descriptor;
} Vk_ಹರಿವು_Descriptor_Surface_Create_Info_GGP;


ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vk_Create_ಹರಿವು_Descriptor_Surface_GGP)(VkInstance instance, ಸ್ಥಿರಾಂಕ Vk_ಹರಿವು_Descriptor_Surface_Create_Info_GGP* pCreateInfo, ಸ್ಥಿರಾಂಕ Vk_ಹಂಚಿಕೆ_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_NO_PROTOTYPES

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ಫಲಿತಾಂಶ VKAPI_CALL vk_Create_ಹರಿವು_Descriptor_Surface_GGP(
    VkInstance                                  instance,
    ಸ್ಥಿರಾಂಕ Vk_ಹರಿವು_Descriptor_Surface_Create_Info_GGP* pCreateInfo,
    ಸ್ಥಿರಾಂಕ Vk_ಹಂಚಿಕೆ_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ


// VK_GGP_frame_token is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು VK_GGP_ಚೌಕಟ್ಟು_token 1

#ವ್ಯಾಖ್ಯಾನಿಸು VK_GGP_ಚೌಕಟ್ಟು_TOKEN_SPEC_ಆವೃತ್ತಿ   1
#ವ್ಯಾಖ್ಯಾನಿಸು VK_GGP_ಚೌಕಟ್ಟು_TOKEN_EXTENSION_NAME "VK_GGP_frame_token"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_Present_ಚೌಕಟ್ಟು_Token_GGP {
    VkStructureType    sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*        p_ಮುಂದಿನ;
    Ggp_ಚೌಕಟ್ಟು_Token      ಚೌಕಟ್ಟು_Token;
} Vk_Present_ಚೌಕಟ್ಟು_Token_GGP;


#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ
