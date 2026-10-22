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
বাহ্যিক "C" {
#endif



// VK_NN_vi_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_NN_vi_surface 1

#define VK_NN_VI_SURFACE_SPEC_VERSION     1
#define VK_NN_VI_SURFACE_EXTENSION_NAME   "VK_NN_vi_surface"

প্রকারলেখ VkFlags VkViSurfaceCreateFlagsNN;

প্রকারলেখ কাঠামো VkViSurfaceCreateInfoNN {
    VkStructureType             sType;
    ধ্রুবক শূন্য*                 p_পরবর্তী;
    VkViSurfaceCreateFlagsNN    flags;
    শূন্য*                       window;
} VkViSurfaceCreateInfoNN;


প্রকারলেখ Vk_ফলাফল (VKAPI_PTR *PFN_vkCreateViSurfaceNN)(VkInstance instance, ধ্রুবক VkViSurfaceCreateInfoNN* pCreateInfo, ধ্রুবক VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ফলাফল VKAPI_CALL vkCreateViSurfaceNN(
    VkInstance                                  instance,
    ধ্রুবক VkViSurfaceCreateInfoNN*              pCreateInfo,
    ধ্রুবক VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif
