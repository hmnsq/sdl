/*
 * Copyright 2015-2023 The Khronos Group Inc.
 * Copyright 2015-2023 Valve Corporation
 * Copyright 2015-2023 LunarG, Inc.
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 */
#pragma once

#অন্তর্ভাৱ "vulkan.h"
#অন্তর্ভাৱ <stdbool.h>

// Loader-ICD version negotiation API.  Versions add the following features:
//   Version 0 - Initial.  Doesn't support vk_icdGetInstanceProcAddr
//               or vk_icdNegotiateLoaderICDInterfaceVersion.
//   Version 1 - Add support for vk_icdGetInstanceProcAddr.
//   Version 2 - Add Loader/ICD Interface version negotiation
//               via vk_icdNegotiateLoaderICDInterfaceVersion.
//   Version 3 - Add ICD creation/destruction of KHR_surface objects.
//   Version 4 - Add unknown physical device extension querying via
//               vk_icdGetPhysicalDeviceProcAddr.
//   Version 5 - Tells ICDs that the loader is now paying attention to the
//               application version of Vulkan passed into the ApplicationInfo
//               structure during vkCreateInstance.  This will tell the ICD
//               that if the loader is older, it should automatically fail a
//               call for any API version > 1.0.  Otherwise, the loader will
//               manually determine if it can support the expected version.
//   Version 6 - Add support for vk_icdEnumerateAdapterPhysicalDevices.
//   Version 7 - If an ICD supports any of the following functions, they must be
//               queryable with vk_icdGetInstanceProcAddr:
//                   vk_icdNegotiateLoaderICDInterfaceVersion
//                   vk_icdGetPhysicalDeviceProcAddr
//                   vk_icdEnumerateAdapterPhysicalDevices (Windows only)
//               In addition, these functions no longer need to be exported directly.
//               This version allows drivers provided through the extension
//               VK_LUNARG_direct_driver_loading be able to support the entire
//               Driver-Loader interface.

#define CURRENT_LOADER_ICD_INTERFACE_VERSION 7
#define MIN_SUPPORTED_LOADER_ICD_INTERFACE_VERSION 0
#define MIN_PHYS_DEV_EXTENSION_ICD_INTERFACE_VERSION 4

// Old typedefs that don't follow a proper naming convention but are preserved for compatibility
প্রকারনির্দেশ VkResult(VKAPI_PTR *PFN_vkNegotiateLoaderICDInterfaceVersion)(uint32_t *pVersion);
// This is defined in vk_layer.h which will be found by the loader, but if an ICD is building against this
// file directly, it won't be found.
#ifndef IS_DEFINED_PFN_GetPhysicalDeviceProcAddr
প্রকারনির্দেশ PFN_vkVoidFunction(VKAPI_PTR *PFN_GetPhysicalDeviceProcAddr)(VkInstance instance, ধ্রুৱ ৱর্ণ *pName);
#define IS_DEFINED_PFN_GetPhysicalDeviceProcAddr
#endif

// Typedefs for loader/ICD interface
প্রকারনির্দেশ VkResult (VKAPI_PTR *PFN_vk_icdNegotiateLoaderICDInterfaceVersion)(uint32_t* pVersion);
প্রকারনির্দেশ PFN_vkVoidFunction (VKAPI_PTR *PFN_vk_icdGetInstanceProcAddr)(VkInstance instance, ধ্রুৱ ৱর্ণ* pName);
প্রকারনির্দেশ PFN_vkVoidFunction (VKAPI_PTR *PFN_vk_icdGetPhysicalDeviceProcAddr)(VkInstance instance, ধ্রুৱ ৱর্ণ* pName);
#যদি defined(VK_USE_PLATFORM_WIN32_KHR)
প্রকারনির্দেশ VkResult (VKAPI_PTR *PFN_vk_icdEnumerateAdapterPhysicalDevices)(VkInstance instance, LUID adapterLUID,
    uint32_t* p_Physical_Device_গুনতি, VkPhysicalDevice* pPhysicalDevices);
#endif

// Prototypes for loader/ICD interface
#যদি !defined(VK_NO_PROTOTYPES)
#ifdef __cplusplus
বাহ্য "C" {
#endif
    VKAPI_ATTR VkResult VKAPI_CALL vk_icdNegotiateLoaderICDInterfaceVersion(uint32_t* pVersion);
    VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vk_icdGetInstanceProcAddr(VkInstance instance, ধ্রুৱ ৱর্ণ* pName);
    VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vk_icdGetPhysicalDeviceProcAddr(VkInstance instance, ধ্রুৱ ৱর্ণ* pName);
#যদি defined(VK_USE_PLATFORM_WIN32_KHR)
    VKAPI_ATTR VkResult VKAPI_CALL vk_icdEnumerateAdapterPhysicalDevices(VkInstance instance, LUID adapterLUID,
        uint32_t* p_Physical_Device_গুনতি, VkPhysicalDevice* pPhysicalDevices);
#endif
#ifdef __cplusplus
}
#endif
#endif

/*
 * The ICD must reserve space for a pointer for the loader's dispatch
 * table, at the start of <each object>.
 * The ICD must initialize this variable using the SET_LOADER_MAGIC_VALUE macro.
 */

#define ICD_LOADER_MAGIC 0x01CDC0DE

প্রকারনির্দেশ সঙ্ঘ {
    uintptr_t loaderMagic;
    শূন্য *loaderData;
} VK_LOADER_DATA;

স্থির অন্তঃস্থ শূন্য set_loader_magic_মান(শূন্য *pNewObject) {
    VK_LOADER_DATA *loader_info = (VK_LOADER_DATA *)pNewObject;
    loader_info->loaderMagic = ICD_LOADER_MAGIC;
}

স্থির অন্তঃস্থ bool valid_loader_magic_মান(শূন্য *pNewObject) {
    ধ্রুৱ VK_LOADER_DATA *loader_info = (VK_LOADER_DATA *)pNewObject;
    ঘূৰাই (loader_info->loaderMagic & 0xffffffff) == ICD_LOADER_MAGIC;
}

/*
 * Windows and Linux ICDs will treat VkSurfaceKHR as a pointer to a struct that
 * contains the platform-specific connection and surface information.
 */
প্রকারনির্দেশ গণনা {
    VK_ICD_WSI_PLATFORM_MIR,
    VK_ICD_WSI_PLATFORM_WAYLAND,
    VK_ICD_WSI_PLATFORM_WIN32,
    VK_ICD_WSI_PLATFORM_XCB,
    VK_ICD_WSI_PLATFORM_XLIB,
    VK_ICD_WSI_PLATFORM_ANDROID,
    VK_ICD_WSI_PLATFORM_MACOS,
    VK_ICD_WSI_PLATFORM_IOS,
    VK_ICD_WSI_PLATFORM_DISPLAY,
    VK_ICD_WSI_PLATFORM_HEADLESS,
    VK_ICD_WSI_PLATFORM_METAL,
    VK_ICD_WSI_PLATFORM_DIRECTFB,
    VK_ICD_WSI_PLATFORM_VI,
    VK_ICD_WSI_PLATFORM_GGP,
    VK_ICD_WSI_PLATFORM_SCREEN,
    VK_ICD_WSI_PLATFORM_FUCHSIA,
} VkIcdWsiPlatform;

প্রকারনির্দেশ সংরচনা {
    VkIcdWsiPlatform platform;
} VkIcdSurfaceBase;

#ifdef VK_USE_PLATFORM_MIR_KHR
প্রকারনির্দেশ সংরচনা {
    VkIcdSurfaceBase base;
    MirConnection *connection;
    MirSurface *mirSurface;
} VkIcdSurfaceMir;
#endif  // VK_USE_PLATFORM_MIR_KHR

#ifdef VK_USE_PLATFORM_WAYLAND_KHR
প্রকারনির্দেশ সংরচনা {
    VkIcdSurfaceBase base;
    সংরচনা wl_display *display;
    সংরচনা wl_surface *surface;
} VkIcdSurfaceWayland;
#endif  // VK_USE_PLATFORM_WAYLAND_KHR

#ifdef VK_USE_PLATFORM_WIN32_KHR
প্রকারনির্দেশ সংরচনা {
    VkIcdSurfaceBase base;
    HINSTANCE hinstance;
    HWND hwnd;
} VkIcdSurfaceWin32;
#endif  // VK_USE_PLATFORM_WIN32_KHR

#ifdef VK_USE_PLATFORM_XCB_KHR
প্রকারনির্দেশ সংরচনা {
    VkIcdSurfaceBase base;
    xcb_connection_t *connection;
    xcb_window_t window;
} VkIcdSurfaceXcb;
#endif  // VK_USE_PLATFORM_XCB_KHR

#ifdef VK_USE_PLATFORM_XLIB_KHR
প্রকারনির্দেশ সংরচনা {
    VkIcdSurfaceBase base;
    Display *dpy;
    Window window;
} VkIcdSurfaceXlib;
#endif  // VK_USE_PLATFORM_XLIB_KHR

#ifdef VK_USE_PLATFORM_DIRECTFB_EXT
প্রকারনির্দেশ সংরচনা {
    VkIcdSurfaceBase base;
    IDirectFB *dfb;
    IDirectFBSurface *surface;
} VkIcdSurfaceDirectFB;
#endif  // VK_USE_PLATFORM_DIRECTFB_EXT

#ifdef VK_USE_PLATFORM_ANDROID_KHR
প্রকারনির্দেশ সংরচনা {
    VkIcdSurfaceBase base;
    সংরচনা ANativeWindow *window;
} VkIcdSurfaceAndroid;
#endif  // VK_USE_PLATFORM_ANDROID_KHR

#ifdef VK_USE_PLATFORM_MACOS_MVK
প্রকারনির্দেশ সংরচনা {
    VkIcdSurfaceBase base;
    ধ্রুৱ শূন্য *pView;
} VkIcdSurfaceMacOS;
#endif  // VK_USE_PLATFORM_MACOS_MVK

#ifdef VK_USE_PLATFORM_IOS_MVK
প্রকারনির্দেশ সংরচনা {
    VkIcdSurfaceBase base;
    ধ্রুৱ শূন্য *pView;
} VkIcdSurfaceIOS;
#endif  // VK_USE_PLATFORM_IOS_MVK

#ifdef VK_USE_PLATFORM_GGP
প্রকারনির্দেশ সংরচনা {
    VkIcdSurfaceBase base;
    GgpStreamDescriptor streamDescriptor;
} VkIcdSurfaceGgp;
#endif  // VK_USE_PLATFORM_GGP

প্রকারনির্দেশ সংরচনা {
    VkIcdSurfaceBase base;
    VkDisplayModeKHR displayMode;
    uint32_t planeIndex;
    uint32_t plane_স্তূপ_Index;
    VkSurfaceTransformFlagBitsKHR transform;
    ভিন্ন globalAlpha;
    VkDisplayPlaneAlphaFlagBitsKHR alphaMode;
    VkExtent2D imageExtent;
} VkIcdSurfaceDisplay;

প্রকারনির্দেশ সংরচনা {
    VkIcdSurfaceBase base;
} VkIcdSurfaceHeadless;

#ifdef VK_USE_PLATFORM_METAL_EXT
প্রকারনির্দেশ সংরচনা {
    VkIcdSurfaceBase base;
    ধ্রুৱ CAMetalLayer *pLayer;
} VkIcdSurfaceMetal;
#endif // VK_USE_PLATFORM_METAL_EXT

#ifdef VK_USE_PLATFORM_VI_NN
প্রকারনির্দেশ সংরচনা {
    VkIcdSurfaceBase base;
    শূন্য *window;
} VkIcdSurfaceVi;
#endif // VK_USE_PLATFORM_VI_NN

#ifdef VK_USE_PLATFORM_SCREEN_QNX
প্রকারনির্দেশ সংরচনা {
    VkIcdSurfaceBase base;
    সংরচনা _screen_context *context;
    সংরচনা _screen_window *window;
} VkIcdSurfaceScreen;
#endif  // VK_USE_PLATFORM_SCREEN_QNX

#ifdef VK_USE_PLATFORM_FUCHSIA
প্রকারনির্দেশ সংরচনা {
  VkIcdSurfaceBase base;
} VkIcdSurfaceImagePipe;
#endif // VK_USE_PLATFORM_FUCHSIA
