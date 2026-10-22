#که_نه_تعریف_شوی VULKAN_GGP_H_
#تعریف_کړه VULKAN_GGP_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#که_تعریف_شوی __cplusplus
خارجي "C" {
#د_که_پای



// VK_GGP_stream_descriptor_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه VK_GGP_بهیر_descriptor_surface 1

#تعریف_کړه VK_GGP_بهیر_DESCRIPTOR_SURFACE_SPEC_نسخه 1
#تعریف_کړه VK_GGP_بهیر_DESCRIPTOR_SURFACE_EXTENSION_NAME "VK_GGP_stream_descriptor_surface"

تعريفنوع VkFlags Vk_بهیر_Descriptor_Surface_Create_Flags_GGP;

تعريفنوع بنية Vk_بهیر_Descriptor_Surface_Create_Info_GGP {
    VkStructureType                            sType;
    ثابت فراغ*                                p_بل;
    Vk_بهیر_Descriptor_Surface_Create_Flags_GGP    flags;
    Ggp_بهیر_Descriptor                        بهیر_Descriptor;
} Vk_بهیر_Descriptor_Surface_Create_Info_GGP;


تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vk_Create_بهیر_Descriptor_Surface_GGP)(VkInstance instance, ثابت Vk_بهیر_Descriptor_Surface_Create_Info_GGP* pCreateInfo, ثابت Vk_ویش_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#که_نه_تعریف_شوی VK_NO_PROTOTYPES

#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_پایله VKAPI_CALL vk_Create_بهیر_Descriptor_Surface_GGP(
    VkInstance                                  instance,
    ثابت Vk_بهیر_Descriptor_Surface_Create_Info_GGP* pCreateInfo,
    ثابت Vk_ویش_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#د_که_پای
#د_که_پای


// VK_GGP_frame_token is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه VK_GGP_چوکاټ_token 1

#تعریف_کړه VK_GGP_چوکاټ_TOKEN_SPEC_نسخه   1
#تعریف_کړه VK_GGP_چوکاټ_TOKEN_EXTENSION_NAME "VK_GGP_frame_token"

تعريفنوع بنية Vk_Present_چوکاټ_Token_GGP {
    VkStructureType    sType;
    ثابت فراغ*        p_بل;
    Ggp_چوکاټ_Token      چوکاټ_Token;
} Vk_Present_چوکاټ_Token_GGP;


#که_تعریف_شوی __cplusplus
}
#د_که_پای

#د_که_پای
