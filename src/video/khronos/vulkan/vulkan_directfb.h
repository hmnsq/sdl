#که_نه_تعریف_شوی VULKAN_DIRECTFB_H_
#تعریف_کړه VULKAN_DIRECTFB_H_ 1

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



// VK_EXT_directfb_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه VK_EXT_directfb_surface 1

#تعریف_کړه VK_EXT_DIRECTFB_SURFACE_SPEC_نسخه 1
#تعریف_کړه VK_EXT_DIRECTFB_SURFACE_EXTENSION_NAME "VK_EXT_directfb_surface"

تعريفنوع VkFlags Vk_مستقیم_FBSurface_Create_Flags_EXT;

تعريفنوع بنية Vk_مستقیم_FBSurface_Create_Info_EXT {
    VkStructureType                    sType;
    ثابت فراغ*                        p_بل;
    Vk_مستقیم_FBSurface_Create_Flags_EXT    flags;
    IDirectFB*                         dfb;
    IDirectFBSurface*                  surface;
} Vk_مستقیم_FBSurface_Create_Info_EXT;


تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vk_Create_مستقیم_FBSurface_EXT)(VkInstance instance, ثابت Vk_مستقیم_FBSurface_Create_Info_EXT* pCreateInfo, ثابت Vk_ویش_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
تعريفنوع VkBool32 (VKAPI_PTR *PFN_vk_Get_Physical_Device_مستقیم_FBPresentation_Support_EXT)(VkPhysicalDevice physicalDevice, uint32_t کتار_Family_شاخص, IDirectFB* dfb);

#که_نه_تعریف_شوی VK_NO_PROTOTYPES

#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_پایله VKAPI_CALL vk_Create_مستقیم_FBSurface_EXT(
    VkInstance                                  instance,
    ثابت Vk_مستقیم_FBSurface_Create_Info_EXT*       pCreateInfo,
    ثابت Vk_ویش_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#د_که_پای
#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vk_Get_Physical_Device_مستقیم_FBPresentation_Support_EXT(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    کتار_Family_شاخص,
    IDirectFB*                                  dfb);
#د_که_پای
#د_که_پای

#که_تعریف_شوی __cplusplus
}
#د_که_پای

#د_که_پای
