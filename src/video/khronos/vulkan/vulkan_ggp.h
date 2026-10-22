#अगर_अघोषित VULKAN_GGP_H_
#घोषणा VULKAN_GGP_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#अगर_घोषित __cplusplus
बाह्य "C" {
#पूर्ण_अगर



// VK_GGP_stream_descriptor_surface is a preprocessor guard. Do not pass it to API calls.
#घोषणा VK_GGP_stream_descriptor_surface 1

#घोषणा VK_GGP_STREAM_DESCRIPTOR_SURFACE_SPEC_VERSION 1
#घोषणा VK_GGP_STREAM_DESCRIPTOR_SURFACE_EXTENSION_NAME "VK_GGP_stream_descriptor_surface"

प्रकार VkFlags VkStreamDescriptorSurfaceCreateFlagsGGP;

प्रकार काष्ठा VkStreamDescriptorSurfaceCreateInfoGGP {
    VkStructureType                            sType;
    स्थिर व्योम*                                p_अग्र;
    VkStreamDescriptorSurfaceCreateFlagsGGP    flags;
    GgpStreamDescriptor                        streamDescriptor;
} VkStreamDescriptorSurfaceCreateInfoGGP;


प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vkCreateStreamDescriptorSurfaceGGP)(VkInstance instance, स्थिर VkStreamDescriptorSurfaceCreateInfoGGP* pCreateInfo, स्थिर VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

#अगर_अघोषित VK_NO_PROTOTYPES

#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkCreateStreamDescriptorSurfaceGGP(
    VkInstance                                  instance,
    स्थिर VkStreamDescriptorSurfaceCreateInfoGGP* pCreateInfo,
    स्थिर VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#पूर्ण_अगर
#पूर्ण_अगर


// VK_GGP_frame_token is a preprocessor guard. Do not pass it to API calls.
#घोषणा VK_GGP_frame_token 1

#घोषणा VK_GGP_FRAME_TOKEN_SPEC_VERSION   1
#घोषणा VK_GGP_FRAME_TOKEN_EXTENSION_NAME "VK_GGP_frame_token"

प्रकार काष्ठा VkPresentFrameTokenGGP {
    VkStructureType    sType;
    स्थिर व्योम*        p_अग्र;
    GgpFrameToken      frameToken;
} VkPresentFrameTokenGGP;


#अगर_घोषित __cplusplus
}
#पूर्ण_अगर

#पूर्ण_अगर
