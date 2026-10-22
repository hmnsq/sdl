#جيڪڏهن_وصف_نه_ٿيل VULKAN_UBM_H_
#وصف_ڪريو VULKAN_UBM_H_ 1

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



// VK_SEC_ubm_surface is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو VK_SEC_ubm_surface 1

#وصف_ڪريو VK_SEC_UBM_SURFACE_SPEC_نسخو   1
#وصف_ڪريو VK_SEC_UBM_SURFACE_EXTENSION_NAME "VK_SEC_ubm_surface"

تعريفنوع VkFlags VkUbmSurfaceCreateFlagsSEC;

تعريفنوع بنية VkUbmSurfaceCreateInfoSEC {
    VkStructureType               sType;
    ثابت فراغ*                   p_ايندڙ;
    VkUbmSurfaceCreateFlagsSEC    flags;
    بنية ubm_device*            device;
    بنية ubm_surface*           surface;
} VkUbmSurfaceCreateInfoSEC;


تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vkCreateUbmSurfaceSEC)(VkInstance instance, ثابت VkUbmSurfaceCreateInfoSEC* pCreateInfo, ثابت Vk_ورهاست_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
تعريفنوع VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceUbmPresentationSupportSEC)(VkPhysicalDevice physicalDevice, uint32_t قطار_Family_اشاريو, بنية ubm_device* device);

#جيڪڏهن_وصف_نه_ٿيل VK_NO_PROTOTYPES

#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتيجو VKAPI_CALL vkCreateUbmSurfaceSEC(
    VkInstance                                  instance,
    ثابت VkUbmSurfaceCreateInfoSEC*            pCreateInfo,
    ثابت Vk_ورهاست_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceUbmPresentationSupportSEC(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    قطار_Family_اشاريو,
    بنية ubm_device*                          device);
#جيڪڏهن_پورو
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل __cplusplus
}
#جيڪڏهن_پورو

#جيڪڏهن_پورو
