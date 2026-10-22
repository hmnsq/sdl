#اگر_غیر_تعریف_شدہ VULKAN_GGP_H_
#تعریف_کرو VULKAN_GGP_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#اگر_تعریف_شدہ __cplusplus
خارجی "C" {
#اگر_ختم



// VK_GGP_stream_descriptor_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_GGP_دھارا_descriptor_surface 1

#تعریف_کرو VK_GGP_دھارا_DESCRIPTOR_SURFACE_SPEC_نسخہ 1
#تعریف_کرو VK_GGP_دھارا_DESCRIPTOR_SURFACE_EXTENSION_NAME "VK_GGP_stream_descriptor_surface"

قسمتعریف VkFlags Vk_دھارا_Descriptor_Surface_Create_Flags_GGP;

قسمتعریف ساخت Vk_دھارا_Descriptor_Surface_Create_Info_GGP {
    VkStructureType                            sType;
    ثابت خالی*                                p_اگلا;
    Vk_دھارا_Descriptor_Surface_Create_Flags_GGP    flags;
    Ggp_دھارا_Descriptor                        دھارا_Descriptor;
} Vk_دھارا_Descriptor_Surface_Create_Info_GGP;


قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vk_Create_دھارا_Descriptor_Surface_GGP)(VkInstance instance, ثابت Vk_دھارا_Descriptor_Surface_Create_Info_GGP* pCreateInfo, ثابت Vk_تخصیص_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#اگر_غیر_تعریف_شدہ VK_NO_PROTOTYPES

#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_Create_دھارا_Descriptor_Surface_GGP(
    VkInstance                                  instance,
    ثابت Vk_دھارا_Descriptor_Surface_Create_Info_GGP* pCreateInfo,
    ثابت Vk_تخصیص_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#اگر_ختم
#اگر_ختم


// VK_GGP_frame_token is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_GGP_چوکھٹا_token 1

#تعریف_کرو VK_GGP_چوکھٹا_TOKEN_SPEC_نسخہ   1
#تعریف_کرو VK_GGP_چوکھٹا_TOKEN_EXTENSION_NAME "VK_GGP_frame_token"

قسمتعریف ساخت Vk_Present_چوکھٹا_Token_GGP {
    VkStructureType    sType;
    ثابت خالی*        p_اگلا;
    Ggp_چوکھٹا_Token      چوکھٹا_Token;
} Vk_Present_چوکھٹا_Token_GGP;


#اگر_تعریف_شدہ __cplusplus
}
#اگر_ختم

#اگر_ختم
