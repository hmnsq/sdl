#यदि_अपरिभाषितम् VULKAN_GGP_H_
#परिभाषय VULKAN_GGP_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#यदि_परिभाषितम् __cplusplus
बाह्य "C" {
#यदि_अन्तः



// VK_GGP_stream_descriptor_surface is a preprocessor guard. Do not pass it to API calls.
#परिभाषय VK_GGP_प्रवाहः_descriptor_surface 1

#परिभाषय VK_GGP_प्रवाहः_DESCRIPTOR_SURFACE_SPEC_संस्करणम् 1
#परिभाषय VK_GGP_प्रवाहः_DESCRIPTOR_SURFACE_EXTENSION_NAME "VK_GGP_stream_descriptor_surface"

प्रकारनिर्देश VkFlags Vk_प्रवाहः_Descriptor_Surface_Create_Flags_GGP;

प्रकारनिर्देश संरचना Vk_प्रवाहः_Descriptor_Surface_Create_Info_GGP {
    VkStructureType                            sType;
    ध्रुव शून्य*                                p_अग्र;
    Vk_प्रवाहः_Descriptor_Surface_Create_Flags_GGP    flags;
    Ggp_प्रवाहः_Descriptor                        प्रवाहः_Descriptor;
} Vk_प्रवाहः_Descriptor_Surface_Create_Info_GGP;


प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vk_Create_प्रवाहः_Descriptor_Surface_GGP)(VkInstance instance, ध्रुव Vk_प्रवाहः_Descriptor_Surface_Create_Info_GGP* pCreateInfo, ध्रुव Vk_आवण्टनम्_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#यदि_अपरिभाषितम् VK_NO_PROTOTYPES

#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vk_Create_प्रवाहः_Descriptor_Surface_GGP(
    VkInstance                                  instance,
    ध्रुव Vk_प्रवाहः_Descriptor_Surface_Create_Info_GGP* pCreateInfo,
    ध्रुव Vk_आवण्टनम्_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#यदि_अन्तः
#यदि_अन्तः


// VK_GGP_frame_token is a preprocessor guard. Do not pass it to API calls.
#परिभाषय VK_GGP_frame_token 1

#परिभाषय VK_GGP_FRAME_TOKEN_SPEC_संस्करणम्   1
#परिभाषय VK_GGP_FRAME_TOKEN_EXTENSION_NAME "VK_GGP_frame_token"

प्रकारनिर्देश संरचना VkPresentFrameTokenGGP {
    VkStructureType    sType;
    ध्रुव शून्य*        p_अग्र;
    GgpFrameToken      frameToken;
} VkPresentFrameTokenGGP;


#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

#यदि_अन्तः
