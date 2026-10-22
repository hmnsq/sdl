#که_نه_تعریف_شوی VULKAN_UBM_H_
#تعریف_کړه VULKAN_UBM_H_ 1

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



// VK_SEC_ubm_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه VK_SEC_ubm_surface 1

#تعریف_کړه VK_SEC_UBM_SURFACE_SPEC_نسخه   1
#تعریف_کړه VK_SEC_UBM_SURFACE_EXTENSION_NAME "VK_SEC_ubm_surface"

تعريفنوع VkFlags VkUbmSurfaceCreateFlagsSEC;

تعريفنوع بنية VkUbmSurfaceCreateInfoSEC {
    VkStructureType               sType;
    ثابت فراغ*                   p_بل;
    VkUbmSurfaceCreateFlagsSEC    flags;
    بنية ubm_device*            device;
    بنية ubm_surface*           surface;
} VkUbmSurfaceCreateInfoSEC;


تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vkCreateUbmSurfaceSEC)(VkInstance instance, ثابت VkUbmSurfaceCreateInfoSEC* pCreateInfo, ثابت Vk_ویش_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
تعريفنوع VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceUbmPresentationSupportSEC)(VkPhysicalDevice physicalDevice, uint32_t کتار_Family_شاخص, بنية ubm_device* device);

#که_نه_تعریف_شوی VK_NO_PROTOTYPES

#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_پایله VKAPI_CALL vkCreateUbmSurfaceSEC(
    VkInstance                                  instance,
    ثابت VkUbmSurfaceCreateInfoSEC*            pCreateInfo,
    ثابت Vk_ویش_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#د_که_پای
#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceUbmPresentationSupportSEC(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    کتار_Family_شاخص,
    بنية ubm_device*                          device);
#د_که_پای
#د_که_پای

#که_تعریف_شوی __cplusplus
}
#د_که_پای

#د_که_پای
