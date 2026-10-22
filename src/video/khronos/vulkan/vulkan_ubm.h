#यदि_अपरिभाषितम् VULKAN_UBM_H_
#परिभाषय VULKAN_UBM_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#यदि_परिभाषितम् __cplusplus
बाह्य "C" {
#यदि_अन्तः



// VK_SEC_ubm_surface is a preprocessor guard. Do not pass it to API calls.
#परिभाषय VK_SEC_ubm_surface 1

#परिभाषय VK_SEC_UBM_SURFACE_SPEC_संस्करणम्   1
#परिभाषय VK_SEC_UBM_SURFACE_EXTENSION_NAME "VK_SEC_ubm_surface"

प्रकारनिर्देश VkFlags VkUbmSurfaceCreateFlagsSEC;

प्रकारनिर्देश संरचना VkUbmSurfaceCreateInfoSEC {
    VkStructureType               sType;
    ध्रुव शून्य*                   p_अग्र;
    VkUbmSurfaceCreateFlagsSEC    flags;
    संरचना ubm_device*            device;
    संरचना ubm_surface*           surface;
} VkUbmSurfaceCreateInfoSEC;


प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vkCreateUbmSurfaceSEC)(VkInstance instance, ध्रुव VkUbmSurfaceCreateInfoSEC* pCreateInfo, ध्रुव Vk_आवण्टनम्_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
प्रकारनिर्देश VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceUbmPresentationSupportSEC)(VkPhysicalDevice physicalDevice, uint32_t queue_Family_सूचकांक, संरचना ubm_device* device);

#यदि_अपरिभाषितम् VK_NO_PROTOTYPES

#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkCreateUbmSurfaceSEC(
    VkInstance                                  instance,
    ध्रुव VkUbmSurfaceCreateInfoSEC*            pCreateInfo,
    ध्रुव Vk_आवण्टनम्_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#यदि_अन्तः
#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceUbmPresentationSupportSEC(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queue_Family_सूचकांक,
    संरचना ubm_device*                          device);
#यदि_अन्तः
#यदि_अन्तः

#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

#यदि_अन्तः
