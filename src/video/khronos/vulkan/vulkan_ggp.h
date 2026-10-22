#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VULKAN_GGP_H_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VULKAN_GGP_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ



// VK_GGP_stream_descriptor_surface is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_GGP_ਧਾਰਾ_descriptor_surface 1

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_GGP_ਧਾਰਾ_DESCRIPTOR_SURFACE_SPEC_ਸੰਸਕਰਣ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_GGP_ਧਾਰਾ_DESCRIPTOR_SURFACE_EXTENSION_NAME "VK_GGP_stream_descriptor_surface"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ VkFlags Vk_ਧਾਰਾ_Descriptor_Surface_Create_Flags_GGP;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_ਧਾਰਾ_Descriptor_Surface_Create_Info_GGP {
    VkStructureType                            sType;
    ਅਚਲ ਖਾਲੀ*                                p_ਅਗਲਾ;
    Vk_ਧਾਰਾ_Descriptor_Surface_Create_Flags_GGP    flags;
    Ggp_ਧਾਰਾ_Descriptor                        ਧਾਰਾ_Descriptor;
} Vk_ਧਾਰਾ_Descriptor_Surface_Create_Info_GGP;


ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vk_Create_ਧਾਰਾ_Descriptor_Surface_GGP)(VkInstance instance, ਅਚਲ Vk_ਧਾਰਾ_Descriptor_Surface_Create_Info_GGP* pCreateInfo, ਅਚਲ Vk_ਵੰਡ_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_NO_PROTOTYPES

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ਨਤੀਜਾ VKAPI_CALL vk_Create_ਧਾਰਾ_Descriptor_Surface_GGP(
    VkInstance                                  instance,
    ਅਚਲ Vk_ਧਾਰਾ_Descriptor_Surface_Create_Info_GGP* pCreateInfo,
    ਅਚਲ Vk_ਵੰਡ_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ


// VK_GGP_frame_token is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_GGP_ਚੌਖਟਾ_token 1

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_GGP_ਚੌਖਟਾ_TOKEN_SPEC_ਸੰਸਕਰਣ   1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_GGP_ਚੌਖਟਾ_TOKEN_EXTENSION_NAME "VK_GGP_frame_token"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_Present_ਚੌਖਟਾ_Token_GGP {
    VkStructureType    sType;
    ਅਚਲ ਖਾਲੀ*        p_ਅਗਲਾ;
    Ggp_ਚੌਖਟਾ_Token      ਚੌਖਟਾ_Token;
} Vk_Present_ਚੌਖਟਾ_Token_GGP;


#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ
