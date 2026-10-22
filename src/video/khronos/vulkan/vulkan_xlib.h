#جے_بنا_تعریف VULKAN_XLIB_H_
#تعریف_کرو VULKAN_XLIB_H_ 1

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



// VK_KHR_xlib_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_KHR_xlib_surface 1

#تعریف_کرو VK_KHR_XLIB_SURFACE_SPEC_نسخہ  6
#تعریف_کرو VK_KHR_XLIB_SURFACE_EXTENSION_NAME "VK_KHR_xlib_surface"

تعريفنوع VkFlags VkXlibSurfaceCreateFlagsKHR;

تعريفنوع بنية VkXlibSurfaceCreateInfoKHR {
    VkStructureType                sType;
    ثابت فراغ*                    p_اگلا;
    VkXlibSurfaceCreateFlagsKHR    flags;
    Display*                       dpy;
    کھڑکی_2                         کھڑکی;
} VkXlibSurfaceCreateInfoKHR;


تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vkCreateXlibSurfaceKHR)(VkInstance instance, ثابت VkXlibSurfaceCreateInfoKHR* pCreateInfo, ثابت Vk_ونڈ_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
تعريفنوع VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR)(VkPhysicalDevice physicalDevice, uint32_t قطار_Family_اشاریہ, Display* dpy, VisualID visualID);

#جے_بنا_تعریف VK_NO_PROTOTYPES

#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vkCreateXlibSurfaceKHR(
    VkInstance                                  instance,
    ثابت VkXlibSurfaceCreateInfoKHR*           pCreateInfo,
    ثابت Vk_ونڈ_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#جے_انت
#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceXlibPresentationSupportKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    قطار_Family_اشاریہ,
    Display*                                    dpy,
    VisualID                                    visualID);
#جے_انت
#جے_انت

#جے_تعریف_شدہ __cplusplus
}
#جے_انت

#جے_انت
