#यदि_अपरिभाषितम् VULKAN_IOS_H_
#परिभाषय VULKAN_IOS_H_ 1

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



// VK_MVK_ios_surface is a preprocessor guard. Do not pass it to API calls.
#परिभाषय VK_MVK_ios_surface 1

#परिभाषय VK_MVK_IOS_SURFACE_SPEC_संस्करणम्   3
#परिभाषय VK_MVK_IOS_SURFACE_EXTENSION_NAME "VK_MVK_ios_surface"

प्रकारनिर्देश VkFlags VkIOSSurfaceCreateFlagsMVK;

प्रकारनिर्देश संरचना VkIOSSurfaceCreateInfoMVK {
    VkStructureType               sType;
    ध्रुव शून्य*                   p_अग्र;
    VkIOSSurfaceCreateFlagsMVK    flags;
    ध्रुव शून्य*                   pView;
} VkIOSSurfaceCreateInfoMVK;


प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vkCreateIOSSurfaceMVK)(VkInstance instance, ध्रुव VkIOSSurfaceCreateInfoMVK* pCreateInfo, ध्रुव Vk_आवण्टनम्_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#यदि_अपरिभाषितम् VK_NO_PROTOTYPES

#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkCreateIOSSurfaceMVK(
    VkInstance                                  instance,
    ध्रुव VkIOSSurfaceCreateInfoMVK*            pCreateInfo,
    ध्रुव Vk_आवण्टनम्_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#यदि_अन्तः
#यदि_अन्तः

#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

#यदि_अन्तः
