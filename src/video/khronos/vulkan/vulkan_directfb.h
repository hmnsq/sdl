#اگر_غیر_تعریف_شدہ VULKAN_DIRECTFB_H_
#تعریف_کرو VULKAN_DIRECTFB_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#اگر_تعریف_شدہ __cplusplus
خارجی "C" {
#اگر_ختم



// VK_EXT_directfb_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_EXT_directfb_surface 1

#تعریف_کرو VK_EXT_DIRECTFB_SURFACE_SPEC_نسخہ 1
#تعریف_کرو VK_EXT_DIRECTFB_SURFACE_EXTENSION_NAME "VK_EXT_directfb_surface"

قسمتعریف VkFlags Vk_براہ_راست_FBSurface_Create_Flags_EXT;

قسمتعریف ساخت Vk_براہ_راست_FBSurface_Create_Info_EXT {
    VkStructureType                    sType;
    ثابت خالی*                        p_اگلا;
    Vk_براہ_راست_FBSurface_Create_Flags_EXT    flags;
    IDirectFB*                         dfb;
    IDirectFBSurface*                  surface;
} Vk_براہ_راست_FBSurface_Create_Info_EXT;


قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vk_Create_براہ_راست_FBSurface_EXT)(VkInstance instance, ثابت Vk_براہ_راست_FBSurface_Create_Info_EXT* pCreateInfo, ثابت Vk_تخصیص_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
قسمتعریف VkBool32 (VKAPI_PTR *PFN_vk_Get_Physical_Device_براہ_راست_FBPresentation_Support_EXT)(VkPhysicalDevice physicalDevice, uint32_t قطار_Family_اشاریہ, IDirectFB* dfb);

#اگر_غیر_تعریف_شدہ VK_NO_PROTOTYPES

#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_Create_براہ_راست_FBSurface_EXT(
    VkInstance                                  instance,
    ثابت Vk_براہ_راست_FBSurface_Create_Info_EXT*       pCreateInfo,
    ثابت Vk_تخصیص_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#اگر_ختم
#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vk_Get_Physical_Device_براہ_راست_FBPresentation_Support_EXT(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    قطار_Family_اشاریہ,
    IDirectFB*                                  dfb);
#اگر_ختم
#اگر_ختم

#اگر_تعریف_شدہ __cplusplus
}
#اگر_ختم

#اگر_ختم
