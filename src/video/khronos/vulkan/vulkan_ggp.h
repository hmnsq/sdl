#جے_بنا_تعریف VULKAN_GGP_H_
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


#جے_تعریف_شدہ __cplusplus
خارجي "C" {
#جے_انت



// VK_GGP_stream_descriptor_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_GGP_دھارا_descriptor_surface 1

#تعریف_کرو VK_GGP_دھارا_DESCRIPTOR_SURFACE_SPEC_نسخہ 1
#تعریف_کرو VK_GGP_دھارا_DESCRIPTOR_SURFACE_EXTENSION_NAME "VK_GGP_stream_descriptor_surface"

تعريفنوع VkFlags Vk_دھارا_Descriptor_Surface_Create_Flags_GGP;

تعريفنوع بنية Vk_دھارا_Descriptor_Surface_Create_Info_GGP {
    VkStructureType                            sType;
    ثابت فراغ*                                p_اگلا;
    Vk_دھارا_Descriptor_Surface_Create_Flags_GGP    flags;
    Ggp_دھارا_Descriptor                        دھارا_Descriptor;
} Vk_دھارا_Descriptor_Surface_Create_Info_GGP;


تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vk_Create_دھارا_Descriptor_Surface_GGP)(VkInstance instance, ثابت Vk_دھارا_Descriptor_Surface_Create_Info_GGP* pCreateInfo, ثابت Vk_ونڈ_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#جے_بنا_تعریف VK_NO_PROTOTYPES

#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_Create_دھارا_Descriptor_Surface_GGP(
    VkInstance                                  instance,
    ثابت Vk_دھارا_Descriptor_Surface_Create_Info_GGP* pCreateInfo,
    ثابت Vk_ونڈ_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#جے_انت
#جے_انت


// VK_GGP_frame_token is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_GGP_چوکھٹا_token 1

#تعریف_کرو VK_GGP_چوکھٹا_TOKEN_SPEC_نسخہ   1
#تعریف_کرو VK_GGP_چوکھٹا_TOKEN_EXTENSION_NAME "VK_GGP_frame_token"

تعريفنوع بنية Vk_Present_چوکھٹا_Token_GGP {
    VkStructureType    sType;
    ثابت فراغ*        p_اگلا;
    Ggp_چوکھٹا_Token      چوکھٹا_Token;
} Vk_Present_چوکھٹا_Token_GGP;


#جے_تعریف_شدہ __cplusplus
}
#جے_انت

#جے_انت
