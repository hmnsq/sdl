#که_نه_تعریف_شوی VULKAN_XLIB_XRANDR_H_
#تعریف_کړه VULKAN_XLIB_XRANDR_H_ 1

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



// VK_EXT_acquire_xlib_display is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه VK_EXT_acquire_xlib_display 1

#تعریف_کړه VK_EXT_ACQUIRE_XLIB_DISPLAY_SPEC_نسخه 1
#تعریف_کړه VK_EXT_ACQUIRE_XLIB_DISPLAY_EXTENSION_NAME "VK_EXT_acquire_xlib_display"

تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vkAcquireXlibDisplayEXT)(VkPhysicalDevice physicalDevice, Display* dpy, VkDisplayKHR display);
تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vkGetRandROutputDisplayEXT)(VkPhysicalDevice physicalDevice, Display* dpy, RROutput rrOutput, VkDisplayKHR* pDisplay);

#که_نه_تعریف_شوی VK_NO_PROTOTYPES

#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_پایله VKAPI_CALL vkAcquireXlibDisplayEXT(
    VkPhysicalDevice                            physicalDevice,
    Display*                                    dpy,
    VkDisplayKHR                                display);
#د_که_پای
#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_پایله VKAPI_CALL vkGetRandROutputDisplayEXT(
    VkPhysicalDevice                            physicalDevice,
    Display*                                    dpy,
    RROutput                                    rrOutput,
    VkDisplayKHR*                               pDisplay);
#د_که_پای
#د_که_پای

#که_تعریف_شوی __cplusplus
}
#د_که_پای

#د_که_پای
