#جے_بنا_تعریف VULKAN_UBM_H_
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


#جے_تعریف_شدہ __cplusplus
خارجي "C" {
#جے_انت



// VK_SEC_ubm_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_SEC_ubm_surface 1

#تعریف_کرو VK_SEC_UBM_SURFACE_SPEC_نسخہ   1
#تعریف_کرو VK_SEC_UBM_SURFACE_EXTENSION_NAME "VK_SEC_ubm_surface"

تعريفنوع VkFlags VkUbmSurfaceCreateFlagsSEC;

تعريفنوع بنية VkUbmSurfaceCreateInfoSEC {
    VkStructureType               sType;
    ثابت فراغ*                   p_اگلا;
    VkUbmSurfaceCreateFlagsSEC    flags;
    بنية ubm_device*            device;
    بنية ubm_surface*           surface;
} VkUbmSurfaceCreateInfoSEC;


تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vkCreateUbmSurfaceSEC)(VkInstance instance, ثابت VkUbmSurfaceCreateInfoSEC* pCreateInfo, ثابت Vk_ونڈ_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
تعريفنوع VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceUbmPresentationSupportSEC)(VkPhysicalDevice physicalDevice, uint32_t قطار_Family_اشاریہ, بنية ubm_device* device);

#جے_بنا_تعریف VK_NO_PROTOTYPES

#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vkCreateUbmSurfaceSEC(
    VkInstance                                  instance,
    ثابت VkUbmSurfaceCreateInfoSEC*            pCreateInfo,
    ثابت Vk_ونڈ_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#جے_انت
#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceUbmPresentationSupportSEC(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    قطار_Family_اشاریہ,
    بنية ubm_device*                          device);
#جے_انت
#جے_انت

#جے_تعریف_شدہ __cplusplus
}
#جے_انت

#جے_انت
