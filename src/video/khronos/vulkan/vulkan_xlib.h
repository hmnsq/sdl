#यदि_अपरिभाषितम् VULKAN_XLIB_H_
#परिभाषय VULKAN_XLIB_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#यदि_परिभाषितम् __cplusplus
बाह्य "C" {
#यदि_अन्तः



// VK_KHR_xlib_surface is a preprocessor guard. Do not pass it to API calls.
#परिभाषय VK_KHR_xlib_surface 1

#परिभाषय VK_KHR_XLIB_SURFACE_SPEC_संस्करणम्  6
#परिभाषय VK_KHR_XLIB_SURFACE_EXTENSION_NAME "VK_KHR_xlib_surface"

प्रकारनिर्देश VkFlags VkXlibSurfaceCreateFlagsKHR;

प्रकारनिर्देश संरचना VkXlibSurfaceCreateInfoKHR {
    VkStructureType                sType;
    ध्रुव शून्य*                    p_अग्र;
    VkXlibSurfaceCreateFlagsKHR    flags;
    Display*                       dpy;
    गवाक्षः_2                         गवाक्षः;
} VkXlibSurfaceCreateInfoKHR;


प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vkCreateXlibSurfaceKHR)(VkInstance instance, ध्रुव VkXlibSurfaceCreateInfoKHR* pCreateInfo, ध्रुव Vk_आवण्टनम्_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
प्रकारनिर्देश VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR)(VkPhysicalDevice physicalDevice, uint32_t queue_Family_सूचकांक, Display* dpy, VisualID visualID);

#यदि_अपरिभाषितम् VK_NO_PROTOTYPES

#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkCreateXlibSurfaceKHR(
    VkInstance                                  instance,
    ध्रुव VkXlibSurfaceCreateInfoKHR*           pCreateInfo,
    ध्रुव Vk_आवण्टनम्_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#यदि_अन्तः
#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceXlibPresentationSupportKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queue_Family_सूचकांक,
    Display*                                    dpy,
    VisualID                                    visualID);
#यदि_अन्तः
#यदि_अन्तः

#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

#यदि_अन्तः
