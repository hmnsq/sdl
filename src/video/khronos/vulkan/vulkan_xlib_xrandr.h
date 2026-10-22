#अगर_अघोषित VULKAN_XLIB_XRANDR_H_
#घोषणा VULKAN_XLIB_XRANDR_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#अगर_घोषित __cplusplus
बाह्य "C" {
#पूर्ण_अगर



// VK_EXT_acquire_xlib_display is a preprocessor guard. Do not pass it to API calls.
#घोषणा VK_EXT_acquire_xlib_display 1

#घोषणा VK_EXT_ACQUIRE_XLIB_DISPLAY_SPEC_VERSION 1
#घोषणा VK_EXT_ACQUIRE_XLIB_DISPLAY_EXTENSION_NAME "VK_EXT_acquire_xlib_display"

प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vkAcquireXlibDisplayEXT)(VkPhysicalDevice physicalDevice, Display* dpy, VkDisplayKHR display);
प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vkGetRandROutputDisplayEXT)(VkPhysicalDevice physicalDevice, Display* dpy, RROutput rrOutput, VkDisplayKHR* pDisplay);

#अगर_अघोषित VK_NO_PROTOTYPES

#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkAcquireXlibDisplayEXT(
    VkPhysicalDevice                            physicalDevice,
    Display*                                    dpy,
    VkDisplayKHR                                display);
#पूर्ण_अगर
#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkGetRandROutputDisplayEXT(
    VkPhysicalDevice                            physicalDevice,
    Display*                                    dpy,
    RROutput                                    rrOutput,
    VkDisplayKHR*                               pDisplay);
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_घोषित __cplusplus
}
#पूर्ण_अगर

#पूर्ण_अगर
