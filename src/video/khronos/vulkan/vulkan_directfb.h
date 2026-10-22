#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VULKAN_DIRECTFB_H_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VULKAN_DIRECTFB_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ



// VK_EXT_directfb_surface is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_EXT_directfb_surface 1

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_EXT_DIRECTFB_SURFACE_SPEC_ਸੰਸਕਰਣ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_EXT_DIRECTFB_SURFACE_EXTENSION_NAME "VK_EXT_directfb_surface"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ VkFlags Vk_ਸਿੱਧਾ_FBSurface_Create_Flags_EXT;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_ਸਿੱਧਾ_FBSurface_Create_Info_EXT {
    VkStructureType                    sType;
    ਅਚਲ ਖਾਲੀ*                        p_ਅਗਲਾ;
    Vk_ਸਿੱਧਾ_FBSurface_Create_Flags_EXT    flags;
    IDirectFB*                         dfb;
    IDirectFBSurface*                  surface;
} Vk_ਸਿੱਧਾ_FBSurface_Create_Info_EXT;


ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vk_Create_ਸਿੱਧਾ_FBSurface_EXT)(VkInstance instance, ਅਚਲ Vk_ਸਿੱਧਾ_FBSurface_Create_Info_EXT* pCreateInfo, ਅਚਲ Vk_ਵੰਡ_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ VkBool32 (VKAPI_PTR *PFN_vk_Get_Physical_Device_ਸਿੱਧਾ_FBPresentation_Support_EXT)(VkPhysicalDevice physicalDevice, uint32_t ਕਤਾਰ_Family_ਸੂਚਕਾਂਕ, IDirectFB* dfb);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_NO_PROTOTYPES

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ਨਤੀਜਾ VKAPI_CALL vk_Create_ਸਿੱਧਾ_FBSurface_EXT(
    VkInstance                                  instance,
    ਅਚਲ Vk_ਸਿੱਧਾ_FBSurface_Create_Info_EXT*       pCreateInfo,
    ਅਚਲ Vk_ਵੰਡ_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vk_Get_Physical_Device_ਸਿੱਧਾ_FBPresentation_Support_EXT(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    ਕਤਾਰ_Family_ਸੂਚਕਾਂਕ,
    IDirectFB*                                  dfb);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ
