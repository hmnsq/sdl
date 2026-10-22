#که_نه_تعریف_شوی VULKAN_VI_H_
#تعریف_کړه VULKAN_VI_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#که_تعریف_شوی __cplusplus
خارجي "C" {
#د_که_پای



// VK_NN_vi_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه VK_NN_vi_surface 1

#تعریف_کړه VK_NN_VI_SURFACE_SPEC_نسخه     1
#تعریف_کړه VK_NN_VI_SURFACE_EXTENSION_NAME   "VK_NN_vi_surface"

تعريفنوع VkFlags VkViSurfaceCreateFlagsNN;

تعريفنوع بنية VkViSurfaceCreateInfoNN {
    VkStructureType             sType;
    ثابت فراغ*                 p_بل;
    VkViSurfaceCreateFlagsNN    flags;
    فراغ*                       کړکۍ;
} VkViSurfaceCreateInfoNN;


تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vkCreateViSurfaceNN)(VkInstance instance, ثابت VkViSurfaceCreateInfoNN* pCreateInfo, ثابت Vk_ویش_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#که_نه_تعریف_شوی VK_NO_PROTOTYPES

#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_پایله VKAPI_CALL vkCreateViSurfaceNN(
    VkInstance                                  instance,
    ثابت VkViSurfaceCreateInfoNN*              pCreateInfo,
    ثابت Vk_ویش_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#د_که_پای
#د_که_پای

#که_تعریف_شوی __cplusplus
}
#د_که_پای

#د_که_پای
