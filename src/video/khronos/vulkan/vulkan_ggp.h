#جيڪڏهن_وصف_نه_ٿيل VULKAN_GGP_H_
#وصف_ڪريو VULKAN_GGP_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#جيڪڏهن_وصف_ٿيل __cplusplus
خارجي "C" {
#جيڪڏهن_پورو



// VK_GGP_stream_descriptor_surface is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو VK_GGP_وهڪرو_descriptor_surface 1

#وصف_ڪريو VK_GGP_وهڪرو_DESCRIPTOR_SURFACE_SPEC_نسخو 1
#وصف_ڪريو VK_GGP_وهڪرو_DESCRIPTOR_SURFACE_EXTENSION_NAME "VK_GGP_stream_descriptor_surface"

تعريفنوع VkFlags Vk_وهڪرو_Descriptor_Surface_Create_Flags_GGP;

تعريفنوع بنية Vk_وهڪرو_Descriptor_Surface_Create_Info_GGP {
    VkStructureType                            sType;
    ثابت فراغ*                                p_ايندڙ;
    Vk_وهڪرو_Descriptor_Surface_Create_Flags_GGP    flags;
    Ggp_وهڪرو_Descriptor                        وهڪرو_Descriptor;
} Vk_وهڪرو_Descriptor_Surface_Create_Info_GGP;


تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vk_Create_وهڪرو_Descriptor_Surface_GGP)(VkInstance instance, ثابت Vk_وهڪرو_Descriptor_Surface_Create_Info_GGP* pCreateInfo, ثابت Vk_ورهاست_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#جيڪڏهن_وصف_نه_ٿيل VK_NO_PROTOTYPES

#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتيجو VKAPI_CALL vk_Create_وهڪرو_Descriptor_Surface_GGP(
    VkInstance                                  instance,
    ثابت Vk_وهڪرو_Descriptor_Surface_Create_Info_GGP* pCreateInfo,
    ثابت Vk_ورهاست_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#جيڪڏهن_پورو
#جيڪڏهن_پورو


// VK_GGP_frame_token is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو VK_GGP_چوکٺو_token 1

#وصف_ڪريو VK_GGP_چوکٺو_TOKEN_SPEC_نسخو   1
#وصف_ڪريو VK_GGP_چوکٺو_TOKEN_EXTENSION_NAME "VK_GGP_frame_token"

تعريفنوع بنية Vk_Present_چوکٺو_Token_GGP {
    VkStructureType    sType;
    ثابت فراغ*        p_ايندڙ;
    Ggp_چوکٺو_Token      چوکٺو_Token;
} Vk_Present_چوکٺو_Token_GGP;


#جيڪڏهن_وصف_ٿيل __cplusplus
}
#جيڪڏهن_پورو

#جيڪڏهن_پورو
