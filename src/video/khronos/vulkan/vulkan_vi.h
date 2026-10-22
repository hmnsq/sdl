#جيڪڏهن_وصف_نه_ٿيل VULKAN_VI_H_
#وصف_ڪريو VULKAN_VI_H_ 1

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



// VK_NN_vi_surface is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو VK_NN_vi_surface 1

#وصف_ڪريو VK_NN_VI_SURFACE_SPEC_نسخو     1
#وصف_ڪريو VK_NN_VI_SURFACE_EXTENSION_NAME   "VK_NN_vi_surface"

تعريفنوع VkFlags VkViSurfaceCreateFlagsNN;

تعريفنوع بنية VkViSurfaceCreateInfoNN {
    VkStructureType             sType;
    ثابت فراغ*                 p_ايندڙ;
    VkViSurfaceCreateFlagsNN    flags;
    فراغ*                       دري;
} VkViSurfaceCreateInfoNN;


تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vkCreateViSurfaceNN)(VkInstance instance, ثابت VkViSurfaceCreateInfoNN* pCreateInfo, ثابت Vk_ورهاست_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#جيڪڏهن_وصف_نه_ٿيل VK_NO_PROTOTYPES

#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتيجو VKAPI_CALL vkCreateViSurfaceNN(
    VkInstance                                  instance,
    ثابت VkViSurfaceCreateInfoNN*              pCreateInfo,
    ثابت Vk_ورهاست_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#جيڪڏهن_پورو
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل __cplusplus
}
#جيڪڏهن_پورو

#جيڪڏهن_پورو
