#جيڪڏهن_وصف_نه_ٿيل VULKAN_XLIB_H_
#وصف_ڪريو VULKAN_XLIB_H_ 1

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



// VK_KHR_xlib_surface is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو VK_KHR_xlib_surface 1

#وصف_ڪريو VK_KHR_XLIB_SURFACE_SPEC_نسخو  6
#وصف_ڪريو VK_KHR_XLIB_SURFACE_EXTENSION_NAME "VK_KHR_xlib_surface"

تعريفنوع VkFlags VkXlibSurfaceCreateFlagsKHR;

تعريفنوع بنية VkXlibSurfaceCreateInfoKHR {
    VkStructureType                sType;
    ثابت فراغ*                    p_ايندڙ;
    VkXlibSurfaceCreateFlagsKHR    flags;
    Display*                       dpy;
    دري_2                         دري;
} VkXlibSurfaceCreateInfoKHR;


تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vkCreateXlibSurfaceKHR)(VkInstance instance, ثابت VkXlibSurfaceCreateInfoKHR* pCreateInfo, ثابت Vk_ورهاست_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
تعريفنوع VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR)(VkPhysicalDevice physicalDevice, uint32_t قطار_Family_اشاريو, Display* dpy, VisualID visualID);

#جيڪڏهن_وصف_نه_ٿيل VK_NO_PROTOTYPES

#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتيجو VKAPI_CALL vkCreateXlibSurfaceKHR(
    VkInstance                                  instance,
    ثابت VkXlibSurfaceCreateInfoKHR*           pCreateInfo,
    ثابت Vk_ورهاست_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceXlibPresentationSupportKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    قطار_Family_اشاريو,
    Display*                                    dpy,
    VisualID                                    visualID);
#جيڪڏهن_پورو
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل __cplusplus
}
#جيڪڏهن_پورو

#جيڪڏهن_پورو
