#جيڪڏهن_وصف_نه_ٿيل VULKAN_DIRECTFB_H_
#وصف_ڪريو VULKAN_DIRECTFB_H_ 1

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



// VK_EXT_directfb_surface is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو VK_EXT_directfb_surface 1

#وصف_ڪريو VK_EXT_DIRECTFB_SURFACE_SPEC_نسخو 1
#وصف_ڪريو VK_EXT_DIRECTFB_SURFACE_EXTENSION_NAME "VK_EXT_directfb_surface"

تعريفنوع VkFlags Vk_سڌو_FBSurface_Create_Flags_EXT;

تعريفنوع بنية Vk_سڌو_FBSurface_Create_Info_EXT {
    VkStructureType                    sType;
    ثابت فراغ*                        p_ايندڙ;
    Vk_سڌو_FBSurface_Create_Flags_EXT    flags;
    IDirectFB*                         dfb;
    IDirectFBSurface*                  surface;
} Vk_سڌو_FBSurface_Create_Info_EXT;


تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vk_Create_سڌو_FBSurface_EXT)(VkInstance instance, ثابت Vk_سڌو_FBSurface_Create_Info_EXT* pCreateInfo, ثابت Vk_ورهاست_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
تعريفنوع VkBool32 (VKAPI_PTR *PFN_vk_Get_Physical_Device_سڌو_FBPresentation_Support_EXT)(VkPhysicalDevice physicalDevice, uint32_t قطار_Family_اشاريو, IDirectFB* dfb);

#جيڪڏهن_وصف_نه_ٿيل VK_NO_PROTOTYPES

#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتيجو VKAPI_CALL vk_Create_سڌو_FBSurface_EXT(
    VkInstance                                  instance,
    ثابت Vk_سڌو_FBSurface_Create_Info_EXT*       pCreateInfo,
    ثابت Vk_ورهاست_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vk_Get_Physical_Device_سڌو_FBPresentation_Support_EXT(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    قطار_Family_اشاريو,
    IDirectFB*                                  dfb);
#جيڪڏهن_پورو
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل __cplusplus
}
#جيڪڏهن_پورو

#جيڪڏهن_پورو
