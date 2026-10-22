#اگر_غیر_تعریف_شدہ VULKAN_VI_H_
#تعریف_کرو VULKAN_VI_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#اگر_تعریف_شدہ __cplusplus
خارجی "C" {
#اگر_ختم



// VK_NN_vi_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_NN_vi_surface 1

#تعریف_کرو VK_NN_VI_SURFACE_SPEC_نسخہ     1
#تعریف_کرو VK_NN_VI_SURFACE_EXTENSION_NAME   "VK_NN_vi_surface"

قسمتعریف VkFlags VkViSurfaceCreateFlagsNN;

قسمتعریف ساخت VkViSurfaceCreateInfoNN {
    VkStructureType             sType;
    ثابت خالی*                 p_اگلا;
    VkViSurfaceCreateFlagsNN    flags;
    خالی*                       کھڑکی;
} VkViSurfaceCreateInfoNN;


قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vkCreateViSurfaceNN)(VkInstance instance, ثابت VkViSurfaceCreateInfoNN* pCreateInfo, ثابت Vk_تخصیص_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#اگر_غیر_تعریف_شدہ VK_NO_PROTOTYPES

#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vkCreateViSurfaceNN(
    VkInstance                                  instance,
    ثابت VkViSurfaceCreateInfoNN*              pCreateInfo,
    ثابت Vk_تخصیص_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#اگر_ختم
#اگر_ختم

#اگر_تعریف_شدہ __cplusplus
}
#اگر_ختم

#اگر_ختم
