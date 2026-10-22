#यदि_अपरिभाषितम् VULKAN_DIRECTFB_H_
#परिभाषय VULKAN_DIRECTFB_H_ 1

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



// VK_EXT_directfb_surface is a preprocessor guard. Do not pass it to API calls.
#परिभाषय VK_EXT_directfb_surface 1

#परिभाषय VK_EXT_DIRECTFB_SURFACE_SPEC_संस्करणम् 1
#परिभाषय VK_EXT_DIRECTFB_SURFACE_EXTENSION_NAME "VK_EXT_directfb_surface"

प्रकारनिर्देश VkFlags Vk_प्रत्यक्षम्_FBSurface_Create_Flags_EXT;

प्रकारनिर्देश संरचना Vk_प्रत्यक्षम्_FBSurface_Create_Info_EXT {
    VkStructureType                    sType;
    ध्रुव शून्य*                        p_अग्र;
    Vk_प्रत्यक्षम्_FBSurface_Create_Flags_EXT    flags;
    IDirectFB*                         dfb;
    IDirectFBSurface*                  surface;
} Vk_प्रत्यक्षम्_FBSurface_Create_Info_EXT;


प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vk_Create_प्रत्यक्षम्_FBSurface_EXT)(VkInstance instance, ध्रुव Vk_प्रत्यक्षम्_FBSurface_Create_Info_EXT* pCreateInfo, ध्रुव Vk_आवण्टनम्_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
प्रकारनिर्देश VkBool32 (VKAPI_PTR *PFN_vk_Get_Physical_Device_प्रत्यक्षम्_FBPresentation_Support_EXT)(VkPhysicalDevice physicalDevice, uint32_t queue_Family_सूचकांक, IDirectFB* dfb);

#यदि_अपरिभाषितम् VK_NO_PROTOTYPES

#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vk_Create_प्रत्यक्षम्_FBSurface_EXT(
    VkInstance                                  instance,
    ध्रुव Vk_प्रत्यक्षम्_FBSurface_Create_Info_EXT*       pCreateInfo,
    ध्रुव Vk_आवण्टनम्_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#यदि_अन्तः
#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vk_Get_Physical_Device_प्रत्यक्षम्_FBPresentation_Support_EXT(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queue_Family_सूचकांक,
    IDirectFB*                                  dfb);
#यदि_अन्तः
#यदि_अन्तः

#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

#यदि_अन्तः
