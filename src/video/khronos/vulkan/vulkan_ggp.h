#ifndef VULKAN_GGP_H_
#define VULKAN_GGP_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#ifdef __cplusplus
ಬಾಹ್ಯ "C" {
#endif



// VK_GGP_stream_descriptor_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_GGP_stream_descriptor_surface 1

#define VK_GGP_STREAM_DESCRIPTOR_SURFACE_SPEC_VERSION 1
#define VK_GGP_STREAM_DESCRIPTOR_SURFACE_EXTENSION_NAME "VK_GGP_stream_descriptor_surface"

ಪ್ರಕಾರನಿರ್ದೇಶ VkFlags VkStreamDescriptorSurfaceCreateFlagsGGP;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkStreamDescriptorSurfaceCreateInfoGGP {
    VkStructureType                            sType;
    ಧ್ರುವ ಶೂನ್ಯ*                                pNext;
    VkStreamDescriptorSurfaceCreateFlagsGGP    flags;
    GgpStreamDescriptor                        streamDescriptor;
} VkStreamDescriptorSurfaceCreateInfoGGP;


ಪ್ರಕಾರನಿರ್ದೇಶ VkResult (VKAPI_PTR *PFN_vkCreateStreamDescriptorSurfaceGGP)(VkInstance instance, ಧ್ರುವ VkStreamDescriptorSurfaceCreateInfoGGP* pCreateInfo, ಧ್ರುವ VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateStreamDescriptorSurfaceGGP(
    VkInstance                                  instance,
    ಧ್ರುವ VkStreamDescriptorSurfaceCreateInfoGGP* pCreateInfo,
    ಧ್ರುವ VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#endif


// VK_GGP_frame_token is a preprocessor guard. Do not pass it to API calls.
#define VK_GGP_frame_token 1

#define VK_GGP_FRAME_TOKEN_SPEC_VERSION   1
#define VK_GGP_FRAME_TOKEN_EXTENSION_NAME "VK_GGP_frame_token"

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkPresentFrameTokenGGP {
    VkStructureType    sType;
    ಧ್ರುವ ಶೂನ್ಯ*        pNext;
    GgpFrameToken      frameToken;
} VkPresentFrameTokenGGP;


#ifdef __cplusplus
}
#endif

#endif
