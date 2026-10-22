#اگر_غیر_تعریف_شدہ VULKAN_UBM_H_
#تعریف_کرو VULKAN_UBM_H_ 1

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



// VK_SEC_ubm_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_SEC_ubm_surface 1

#تعریف_کرو VK_SEC_UBM_SURFACE_SPEC_نسخہ   1
#تعریف_کرو VK_SEC_UBM_SURFACE_EXTENSION_NAME "VK_SEC_ubm_surface"

قسمتعریف VkFlags VkUbmSurfaceCreateFlagsSEC;

قسمتعریف ساخت VkUbmSurfaceCreateInfoSEC {
    VkStructureType               sType;
    ثابت خالی*                   p_اگلا;
    VkUbmSurfaceCreateFlagsSEC    flags;
    ساخت ubm_device*            device;
    ساخت ubm_surface*           surface;
} VkUbmSurfaceCreateInfoSEC;


قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vkCreateUbmSurfaceSEC)(VkInstance instance, ثابت VkUbmSurfaceCreateInfoSEC* pCreateInfo, ثابت Vk_تخصیص_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
قسمتعریف VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceUbmPresentationSupportSEC)(VkPhysicalDevice physicalDevice, uint32_t قطار_Family_اشاریہ, ساخت ubm_device* device);

#اگر_غیر_تعریف_شدہ VK_NO_PROTOTYPES

#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vkCreateUbmSurfaceSEC(
    VkInstance                                  instance,
    ثابت VkUbmSurfaceCreateInfoSEC*            pCreateInfo,
    ثابت Vk_تخصیص_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#اگر_ختم
#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceUbmPresentationSupportSEC(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    قطار_Family_اشاریہ,
    ساخت ubm_device*                          device);
#اگر_ختم
#اگر_ختم

#اگر_تعریف_شدہ __cplusplus
}
#اگر_ختم

#اگر_ختم
