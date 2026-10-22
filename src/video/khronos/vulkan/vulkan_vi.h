#جے_بنا_تعریف VULKAN_VI_H_
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


#جے_تعریف_شدہ __cplusplus
خارجي "C" {
#جے_انت



// VK_NN_vi_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_NN_vi_surface 1

#تعریف_کرو VK_NN_VI_SURFACE_SPEC_نسخہ     1
#تعریف_کرو VK_NN_VI_SURFACE_EXTENSION_NAME   "VK_NN_vi_surface"

تعريفنوع VkFlags VkViSurfaceCreateFlagsNN;

تعريفنوع بنية VkViSurfaceCreateInfoNN {
    VkStructureType             sType;
    ثابت فراغ*                 p_اگلا;
    VkViSurfaceCreateFlagsNN    flags;
    فراغ*                       کھڑکی;
} VkViSurfaceCreateInfoNN;


تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vkCreateViSurfaceNN)(VkInstance instance, ثابت VkViSurfaceCreateInfoNN* pCreateInfo, ثابت Vk_ونڈ_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#جے_بنا_تعریف VK_NO_PROTOTYPES

#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vkCreateViSurfaceNN(
    VkInstance                                  instance,
    ثابت VkViSurfaceCreateInfoNN*              pCreateInfo,
    ثابت Vk_ونڈ_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#جے_انت
#جے_انت

#جے_تعریف_شدہ __cplusplus
}
#جے_انت

#جے_انت
