#اگر_تعریف_نشده VULKAN_GGP_H_
#تعریف_کن VULKAN_GGP_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#اگر_تعریف_شده __cplusplus
خارجي "C" {
#پایان_اگر



// VK_GGP_stream_descriptor_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کن VK_GGP_جریان_descriptor_surface 1

#تعریف_کن VK_GGP_جریان_DESCRIPTOR_SURFACE_SPEC_نسخه 1
#تعریف_کن VK_GGP_جریان_DESCRIPTOR_SURFACE_EXTENSION_NAME "VK_GGP_stream_descriptor_surface"

تعريفنوع VkFlags Vk_جریان_Descriptor_Surface_Create_Flags_GGP;

تعريفنوع بنية Vk_جریان_Descriptor_Surface_Create_Info_GGP {
    VkStructureType                            sType;
    ثابت فراغ*                                p_بعدی;
    Vk_جریان_Descriptor_Surface_Create_Flags_GGP    flags;
    Ggp_جریان_Descriptor                        جریان_Descriptor;
} Vk_جریان_Descriptor_Surface_Create_Info_GGP;


تعريفنوع Vk_نتیجه (VKAPI_PTR *PFN_vk_Create_جریان_Descriptor_Surface_GGP)(VkInstance instance, ثابت Vk_جریان_Descriptor_Surface_Create_Info_GGP* pCreateInfo, ثابت Vk_تخصیص_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#اگر_تعریف_نشده VK_NO_PROTOTYPES

#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجه VKAPI_CALL vk_Create_جریان_Descriptor_Surface_GGP(
    VkInstance                                  instance,
    ثابت Vk_جریان_Descriptor_Surface_Create_Info_GGP* pCreateInfo,
    ثابت Vk_تخصیص_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#پایان_اگر
#پایان_اگر


// VK_GGP_frame_token is a preprocessor guard. Do not pass it to API calls.
#تعریف_کن VK_GGP_قاب_token 1

#تعریف_کن VK_GGP_قاب_TOKEN_SPEC_نسخه   1
#تعریف_کن VK_GGP_قاب_TOKEN_EXTENSION_NAME "VK_GGP_frame_token"

تعريفنوع بنية Vk_Present_قاب_Token_GGP {
    VkStructureType    sType;
    ثابت فراغ*        p_بعدی;
    Ggp_قاب_Token      قاب_Token;
} Vk_Present_قاب_Token_GGP;


#اگر_تعریف_شده __cplusplus
}
#پایان_اگر

#پایان_اگر
