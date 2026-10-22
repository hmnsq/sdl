#جے_بنا_تعریف VULKAN_DIRECTFB_H_
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


#جے_تعریف_شدہ __cplusplus
خارجي "C" {
#جے_انت



// VK_EXT_directfb_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_EXT_directfb_surface 1

#تعریف_کرو VK_EXT_DIRECTFB_SURFACE_SPEC_نسخہ 1
#تعریف_کرو VK_EXT_DIRECTFB_SURFACE_EXTENSION_NAME "VK_EXT_directfb_surface"

تعريفنوع VkFlags Vk_سدھا_FBSurface_Create_Flags_EXT;

تعريفنوع بنية Vk_سدھا_FBSurface_Create_Info_EXT {
    VkStructureType                    sType;
    ثابت فراغ*                        p_اگلا;
    Vk_سدھا_FBSurface_Create_Flags_EXT    flags;
    IDirectFB*                         dfb;
    IDirectFBSurface*                  surface;
} Vk_سدھا_FBSurface_Create_Info_EXT;


تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vk_Create_سدھا_FBSurface_EXT)(VkInstance instance, ثابت Vk_سدھا_FBSurface_Create_Info_EXT* pCreateInfo, ثابت Vk_ونڈ_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
تعريفنوع VkBool32 (VKAPI_PTR *PFN_vk_Get_Physical_Device_سدھا_FBPresentation_Support_EXT)(VkPhysicalDevice physicalDevice, uint32_t قطار_Family_اشاریہ, IDirectFB* dfb);

#جے_بنا_تعریف VK_NO_PROTOTYPES

#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_Create_سدھا_FBSurface_EXT(
    VkInstance                                  instance,
    ثابت Vk_سدھا_FBSurface_Create_Info_EXT*       pCreateInfo,
    ثابت Vk_ونڈ_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#جے_انت
#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vk_Get_Physical_Device_سدھا_FBPresentation_Support_EXT(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    قطار_Family_اشاریہ,
    IDirectFB*                                  dfb);
#جے_انت
#جے_انت

#جے_تعریف_شدہ __cplusplus
}
#جے_انت

#جے_انت
