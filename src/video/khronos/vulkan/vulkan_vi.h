#اگر_تعریف_نشده VULKAN_VI_H_
#تعریف_کن VULKAN_VI_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#اگر_تعریف_شده __cplusplus
خارجي "C" {
#پایان_اگر



// VK_NN_vi_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کن VK_NN_vi_surface 1

#تعریف_کن VK_NN_VI_SURFACE_SPEC_نسخه     1
#تعریف_کن VK_NN_VI_SURFACE_EXTENSION_NAME   "VK_NN_vi_surface"

تعريفنوع VkFlags VkViSurfaceCreateFlagsNN;

تعريفنوع بنية VkViSurfaceCreateInfoNN {
    VkStructureType             sType;
    ثابت فراغ*                 p_بعدی;
    VkViSurfaceCreateFlagsNN    flags;
    فراغ*                       پنجره;
} VkViSurfaceCreateInfoNN;


تعريفنوع Vk_نتیجه (VKAPI_PTR *PFN_vkCreateViSurfaceNN)(VkInstance instance, ثابت VkViSurfaceCreateInfoNN* pCreateInfo, ثابت Vk_تخصیص_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#اگر_تعریف_نشده VK_NO_PROTOTYPES

#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجه VKAPI_CALL vkCreateViSurfaceNN(
    VkInstance                                  instance,
    ثابت VkViSurfaceCreateInfoNN*              pCreateInfo,
    ثابت Vk_تخصیص_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#پایان_اگر
#پایان_اگر

#اگر_تعریف_شده __cplusplus
}
#پایان_اگر

#پایان_اگر
