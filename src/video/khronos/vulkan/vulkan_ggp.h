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
বাহ্য "C" {
#endif



// VK_GGP_stream_descriptor_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_GGP_stream_descriptor_surface 1

#define VK_GGP_STREAM_DESCRIPTOR_SURFACE_SPEC_VERSION 1
#define VK_GGP_STREAM_DESCRIPTOR_SURFACE_EXTENSION_NAME "VK_GGP_stream_descriptor_surface"

প্রকারনির্দেশ VkFlags VkStreamDescriptorSurfaceCreateFlagsGGP;

প্রকারনির্দেশ সংরচনা VkStreamDescriptorSurfaceCreateInfoGGP {
    VkStructureType                            sType;
    ধ্রুব শূন্য*                                pNext;
    VkStreamDescriptorSurfaceCreateFlagsGGP    flags;
    GgpStreamDescriptor                        streamDescriptor;
} VkStreamDescriptorSurfaceCreateInfoGGP;


প্রকারনির্দেশ VkResult (VKAPI_PTR *PFN_vkCreateStreamDescriptorSurfaceGGP)(VkInstance instance, ধ্রুব VkStreamDescriptorSurfaceCreateInfoGGP* pCreateInfo, ধ্রুব VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateStreamDescriptorSurfaceGGP(
    VkInstance                                  instance,
    ধ্রুব VkStreamDescriptorSurfaceCreateInfoGGP* pCreateInfo,
    ধ্রুব VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#endif


// VK_GGP_frame_token is a preprocessor guard. Do not pass it to API calls.
#define VK_GGP_frame_token 1

#define VK_GGP_FRAME_TOKEN_SPEC_VERSION   1
#define VK_GGP_FRAME_TOKEN_EXTENSION_NAME "VK_GGP_frame_token"

প্রকারনির্দেশ সংরচনা VkPresentFrameTokenGGP {
    VkStructureType    sType;
    ধ্রুব শূন্য*        pNext;
    GgpFrameToken      frameToken;
} VkPresentFrameTokenGGP;


#ifdef __cplusplus
}
#endif

#endif
