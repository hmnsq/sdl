#اگر_تعریف_نشده VULKAN_UBM_H_
#تعریف_کن VULKAN_UBM_H_ 1

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



// VK_SEC_ubm_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کن VK_SEC_ubm_surface 1

#تعریف_کن VK_SEC_UBM_SURFACE_SPEC_نسخه   1
#تعریف_کن VK_SEC_UBM_SURFACE_EXTENSION_NAME "VK_SEC_ubm_surface"

تعريفنوع VkFlags VkUbmSurfaceCreateFlagsSEC;

تعريفنوع بنية VkUbmSurfaceCreateInfoSEC {
    VkStructureType               sType;
    ثابت فراغ*                   p_بعدی;
    VkUbmSurfaceCreateFlagsSEC    flags;
    بنية ubm_device*            device;
    بنية ubm_surface*           surface;
} VkUbmSurfaceCreateInfoSEC;


تعريفنوع Vk_نتیجه (VKAPI_PTR *PFN_vkCreateUbmSurfaceSEC)(VkInstance instance, ثابت VkUbmSurfaceCreateInfoSEC* pCreateInfo, ثابت Vk_تخصیص_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
تعريفنوع VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceUbmPresentationSupportSEC)(VkPhysicalDevice physicalDevice, uint32_t صف_Family_شاخص, بنية ubm_device* device);

#اگر_تعریف_نشده VK_NO_PROTOTYPES

#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجه VKAPI_CALL vkCreateUbmSurfaceSEC(
    VkInstance                                  instance,
    ثابت VkUbmSurfaceCreateInfoSEC*            pCreateInfo,
    ثابت Vk_تخصیص_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#پایان_اگر
#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceUbmPresentationSupportSEC(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    صف_Family_شاخص,
    بنية ubm_device*                          device);
#پایان_اگر
#پایان_اگر

#اگر_تعریف_شده __cplusplus
}
#پایان_اگر

#پایان_اگر
