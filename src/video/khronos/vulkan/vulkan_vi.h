#यदि_अपरिभाषितम् VULKAN_VI_H_
#परिभाषय VULKAN_VI_H_ 1

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



// VK_NN_vi_surface is a preprocessor guard. Do not pass it to API calls.
#परिभाषय VK_NN_vi_surface 1

#परिभाषय VK_NN_VI_SURFACE_SPEC_संस्करणम्     1
#परिभाषय VK_NN_VI_SURFACE_EXTENSION_NAME   "VK_NN_vi_surface"

प्रकारनिर्देश VkFlags VkViSurfaceCreateFlagsNN;

प्रकारनिर्देश संरचना VkViSurfaceCreateInfoNN {
    VkStructureType             sType;
    ध्रुव शून्य*                 p_अग्र;
    VkViSurfaceCreateFlagsNN    flags;
    शून्य*                       गवाक्षः;
} VkViSurfaceCreateInfoNN;


प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vkCreateViSurfaceNN)(VkInstance instance, ध्रुव VkViSurfaceCreateInfoNN* pCreateInfo, ध्रुव Vk_आवण्टनम्_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#यदि_अपरिभाषितम् VK_NO_PROTOTYPES

#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkCreateViSurfaceNN(
    VkInstance                                  instance,
    ध्रुव VkViSurfaceCreateInfoNN*              pCreateInfo,
    ध्रुव Vk_आवण्टनम्_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#यदि_अन्तः
#यदि_अन्तः

#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

#यदि_अन्तः
