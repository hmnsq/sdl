#अगर_अघोषित VULKAN_VI_H_
#घोषणा VULKAN_VI_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#अगर_घोषित __cplusplus
बाह्य "C" {
#पूर्ण_अगर



// VK_NN_vi_surface is a preprocessor guard. Do not pass it to API calls.
#घोषणा VK_NN_vi_surface 1

#घोषणा VK_NN_VI_SURFACE_SPEC_VERSION     1
#घोषणा VK_NN_VI_SURFACE_EXTENSION_NAME   "VK_NN_vi_surface"

प्रकार VkFlags VkViSurfaceCreateFlagsNN;

प्रकार काष्ठा VkViSurfaceCreateInfoNN {
    VkStructureType             sType;
    स्थिर व्योम*                 p_अग्र;
    VkViSurfaceCreateFlagsNN    flags;
    व्योम*                       window;
} VkViSurfaceCreateInfoNN;


प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vkCreateViSurfaceNN)(VkInstance instance, स्थिर VkViSurfaceCreateInfoNN* pCreateInfo, स्थिर VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

#अगर_अघोषित VK_NO_PROTOTYPES

#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkCreateViSurfaceNN(
    VkInstance                                  instance,
    स्थिर VkViSurfaceCreateInfoNN*              pCreateInfo,
    स्थिर VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_घोषित __cplusplus
}
#पूर्ण_अगर

#पूर्ण_अगर
