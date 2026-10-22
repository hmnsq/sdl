#ifndef VULKAN_VI_H_
#define VULKAN_VI_H_ 1

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
બાહ્ય "C" {
#endif



// VK_NN_vi_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_NN_vi_surface 1

#define VK_NN_VI_SURFACE_SPEC_VERSION     1
#define VK_NN_VI_SURFACE_EXTENSION_NAME   "VK_NN_vi_surface"

પ્રકારવ્યાખ્યા VkFlags VkViSurfaceCreateFlagsNN;

પ્રકારવ્યાખ્યા સંરચના VkViSurfaceCreateInfoNN {
    VkStructureType             sType;
    અચલ શૂન્ય*                 pNext;
    VkViSurfaceCreateFlagsNN    flags;
    શૂન્ય*                       window;
} VkViSurfaceCreateInfoNN;


પ્રકારવ્યાખ્યા VkResult (VKAPI_PTR *PFN_vkCreateViSurfaceNN)(VkInstance instance, અચલ VkViSurfaceCreateInfoNN* pCreateInfo, અચલ VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateViSurfaceNN(
    VkInstance                                  instance,
    અચલ VkViSurfaceCreateInfoNN*              pCreateInfo,
    અચલ VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif
