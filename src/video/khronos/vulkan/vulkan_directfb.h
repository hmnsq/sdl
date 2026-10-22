#अगर_अघोषित VULKAN_DIRECTFB_H_
#घोषणा VULKAN_DIRECTFB_H_ 1

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



// VK_EXT_directfb_surface is a preprocessor guard. Do not pass it to API calls.
#घोषणा VK_EXT_directfb_surface 1

#घोषणा VK_EXT_DIRECTFB_SURFACE_SPEC_VERSION 1
#घोषणा VK_EXT_DIRECTFB_SURFACE_EXTENSION_NAME "VK_EXT_directfb_surface"

प्रकार VkFlags VkDirectFBSurfaceCreateFlagsEXT;

प्रकार काष्ठा VkDirectFBSurfaceCreateInfoEXT {
    VkStructureType                    sType;
    स्थिर व्योम*                        p_अग्र;
    VkDirectFBSurfaceCreateFlagsEXT    flags;
    IDirectFB*                         dfb;
    IDirectFBSurface*                  surface;
} VkDirectFBSurfaceCreateInfoEXT;


प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vkCreateDirectFBSurfaceEXT)(VkInstance instance, स्थिर VkDirectFBSurfaceCreateInfoEXT* pCreateInfo, स्थिर VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
प्रकार VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceDirectFBPresentationSupportEXT)(VkPhysicalDevice physicalDevice, uint32_t queue_Family_सूचकांक, IDirectFB* dfb);

#अगर_अघोषित VK_NO_PROTOTYPES

#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkCreateDirectFBSurfaceEXT(
    VkInstance                                  instance,
    स्थिर VkDirectFBSurfaceCreateInfoEXT*       pCreateInfo,
    स्थिर VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#पूर्ण_अगर
#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceDirectFBPresentationSupportEXT(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queue_Family_सूचकांक,
    IDirectFB*                                  dfb);
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_घोषित __cplusplus
}
#पूर्ण_अगर

#पूर्ण_अगर
