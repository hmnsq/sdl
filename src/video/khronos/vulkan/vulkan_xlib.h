#اگر_تعریف_نشده VULKAN_XLIB_H_
#تعریف_کن VULKAN_XLIB_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#اگر_تعریف_شده __cplusplus
خارجي "C" {
#پایان_اگر



// VK_KHR_xlib_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کن VK_KHR_xlib_surface 1

#تعریف_کن VK_KHR_XLIB_SURFACE_SPEC_نسخه  6
#تعریف_کن VK_KHR_XLIB_SURFACE_EXTENSION_NAME "VK_KHR_xlib_surface"

تعريفنوع VkFlags VkXlibSurfaceCreateFlagsKHR;

تعريفنوع بنية VkXlibSurfaceCreateInfoKHR {
    VkStructureType                sType;
    ثابت فراغ*                    p_بعدی;
    VkXlibSurfaceCreateFlagsKHR    flags;
    Display*                       dpy;
    پنجره_2                         پنجره;
} VkXlibSurfaceCreateInfoKHR;


تعريفنوع Vk_نتیجه (VKAPI_PTR *PFN_vkCreateXlibSurfaceKHR)(VkInstance instance, ثابت VkXlibSurfaceCreateInfoKHR* pCreateInfo, ثابت Vk_تخصیص_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
تعريفنوع VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR)(VkPhysicalDevice physicalDevice, uint32_t صف_Family_شاخص, Display* dpy, VisualID visualID);

#اگر_تعریف_نشده VK_NO_PROTOTYPES

#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجه VKAPI_CALL vkCreateXlibSurfaceKHR(
    VkInstance                                  instance,
    ثابت VkXlibSurfaceCreateInfoKHR*           pCreateInfo,
    ثابت Vk_تخصیص_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#پایان_اگر
#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceXlibPresentationSupportKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    صف_Family_شاخص,
    Display*                                    dpy,
    VisualID                                    visualID);
#پایان_اگر
#پایان_اگر

#اگر_تعریف_شده __cplusplus
}
#پایان_اگر

#پایان_اگر
