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
ബാഹ്യ "C" {
#endif



// VK_GGP_stream_descriptor_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_GGP_stream_descriptor_surface 1

#define VK_GGP_STREAM_DESCRIPTOR_SURFACE_SPEC_VERSION 1
#define VK_GGP_STREAM_DESCRIPTOR_SURFACE_EXTENSION_NAME "VK_GGP_stream_descriptor_surface"

തരനിർവചനം VkFlags VkStreamDescriptorSurfaceCreateFlagsGGP;

തരനിർവചനം ഘടന VkStreamDescriptorSurfaceCreateInfoGGP {
    VkStructureType                            sType;
    സ്ഥിരം ശൂന്യം*                                pNext;
    VkStreamDescriptorSurfaceCreateFlagsGGP    flags;
    GgpStreamDescriptor                        streamDescriptor;
} VkStreamDescriptorSurfaceCreateInfoGGP;


തരനിർവചനം VkResult (VKAPI_PTR *PFN_vkCreateStreamDescriptorSurfaceGGP)(VkInstance instance, സ്ഥിരം VkStreamDescriptorSurfaceCreateInfoGGP* pCreateInfo, സ്ഥിരം VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateStreamDescriptorSurfaceGGP(
    VkInstance                                  instance,
    സ്ഥിരം VkStreamDescriptorSurfaceCreateInfoGGP* pCreateInfo,
    സ്ഥിരം VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#endif


// VK_GGP_frame_token is a preprocessor guard. Do not pass it to API calls.
#define VK_GGP_frame_token 1

#define VK_GGP_FRAME_TOKEN_SPEC_VERSION   1
#define VK_GGP_FRAME_TOKEN_EXTENSION_NAME "VK_GGP_frame_token"

തരനിർവചനം ഘടന VkPresentFrameTokenGGP {
    VkStructureType    sType;
    സ്ഥിരം ശൂന്യം*        pNext;
    GgpFrameToken      frameToken;
} VkPresentFrameTokenGGP;


#ifdef __cplusplus
}
#endif

#endif
