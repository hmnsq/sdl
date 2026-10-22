/*
 * Copyright 2015-2023 The Khronos Group Inc.
 * Copyright 2015-2023 Valve Corporation
 * Copyright 2015-2023 LunarG, Inc.
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 */
#pragma once

#ଅନ୍ତର୍ଭାଵ "vulkan.h"
#ଅନ୍ତର୍ଭାଵ <stdbool.h>

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
ପ୍ରକାରବ୍ୟାଖ୍ୟା VkResult(VKAPI_PTR *PFN_vkNegotiateLoaderICDInterfaceVersion)(uint32_t *pVersion);
// This is defined in vk_layer.h which will be found by the loader, but if an ICD is building against this
// file directly, it won't be found.
#ifndef IS_DEFINED_PFN_GetPhysicalDeviceProcAddr
ପ୍ରକାରବ୍ୟାଖ୍ୟା PFN_vkVoidFunction(VKAPI_PTR *PFN_GetPhysicalDeviceProcAddr)(VkInstance instance, ଅଚଳ ଅକ୍ଷର *pName);
#define IS_DEFINED_PFN_GetPhysicalDeviceProcAddr
#endif

// Typedefs for loader/ICD interface
ପ୍ରକାରବ୍ୟାଖ୍ୟା VkResult (VKAPI_PTR *PFN_vk_icdNegotiateLoaderICDInterfaceVersion)(uint32_t* pVersion);
ପ୍ରକାରବ୍ୟାଖ୍ୟା PFN_vkVoidFunction (VKAPI_PTR *PFN_vk_icdGetInstanceProcAddr)(VkInstance instance, ଅଚଳ ଅକ୍ଷର* pName);
ପ୍ରକାରବ୍ୟାଖ୍ୟା PFN_vkVoidFunction (VKAPI_PTR *PFN_vk_icdGetPhysicalDeviceProcAddr)(VkInstance instance, ଅଚଳ ଅକ୍ଷର* pName);
#ଯଦି defined(VK_USE_PLATFORM_WIN32_KHR)
ପ୍ରକାରବ୍ୟାଖ୍ୟା VkResult (VKAPI_PTR *PFN_vk_icdEnumerateAdapterPhysicalDevices)(VkInstance instance, LUID adapterLUID,
    uint32_t* p_Physical_Device_ଗଣନା, VkPhysicalDevice* pPhysicalDevices);
#endif

// Prototypes for loader/ICD interface
#ଯଦି !defined(VK_NO_PROTOTYPES)
#ifdef __cplusplus
ବାହ୍ୟ "C" {
#endif
    VKAPI_ATTR VkResult VKAPI_CALL vk_icdNegotiateLoaderICDInterfaceVersion(uint32_t* pVersion);
    VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vk_icdGetInstanceProcAddr(VkInstance instance, ଅଚଳ ଅକ୍ଷର* pName);
    VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vk_icdGetPhysicalDeviceProcAddr(VkInstance instance, ଅଚଳ ଅକ୍ଷର* pName);
#ଯଦି defined(VK_USE_PLATFORM_WIN32_KHR)
    VKAPI_ATTR VkResult VKAPI_CALL vk_icdEnumerateAdapterPhysicalDevices(VkInstance instance, LUID adapterLUID,
        uint32_t* p_Physical_Device_ଗଣନା, VkPhysicalDevice* pPhysicalDevices);
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

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂଘ {
    uintptr_t loaderMagic;
    ଶୂନ୍ୟ *loaderData;
} VK_LOADER_DATA;

ସ୍ଥିର ଧାଡ଼ିଭିତରେ ଶୂନ୍ୟ set_loader_magic_ମୂଲ୍ୟ(ଶୂନ୍ୟ *pNewObject) {
    VK_LOADER_DATA *loader_info = (VK_LOADER_DATA *)pNewObject;
    loader_info->loaderMagic = ICD_LOADER_MAGIC;
}

ସ୍ଥିର ଧାଡ଼ିଭିତରେ bool valid_loader_magic_ମୂଲ୍ୟ(ଶୂନ୍ୟ *pNewObject) {
    ଅଚଳ VK_LOADER_DATA *loader_info = (VK_LOADER_DATA *)pNewObject;
    ଫେରନ୍ତୁ (loader_info->loaderMagic & 0xffffffff) == ICD_LOADER_MAGIC;
}

/*
 * Windows and Linux ICDs will treat VkSurfaceKHR as a pointer to a struct that
 * contains the platform-specific connection and surface information.
 */
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଗଣନା {
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

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା {
    VkIcdWsiPlatform platform;
} VkIcdSurfaceBase;

#ifdef VK_USE_PLATFORM_MIR_KHR
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା {
    VkIcdSurfaceBase base;
    MirConnection *connection;
    MirSurface *mirSurface;
} VkIcdSurfaceMir;
#endif  // VK_USE_PLATFORM_MIR_KHR

#ifdef VK_USE_PLATFORM_WAYLAND_KHR
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା {
    VkIcdSurfaceBase base;
    ସଂରଚନା wl_display *display;
    ସଂରଚନା wl_surface *surface;
} VkIcdSurfaceWayland;
#endif  // VK_USE_PLATFORM_WAYLAND_KHR

#ifdef VK_USE_PLATFORM_WIN32_KHR
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା {
    VkIcdSurfaceBase base;
    HINSTANCE hinstance;
    HWND hwnd;
} VkIcdSurfaceWin32;
#endif  // VK_USE_PLATFORM_WIN32_KHR

#ifdef VK_USE_PLATFORM_XCB_KHR
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା {
    VkIcdSurfaceBase base;
    xcb_connection_t *connection;
    xcb_window_t window;
} VkIcdSurfaceXcb;
#endif  // VK_USE_PLATFORM_XCB_KHR

#ifdef VK_USE_PLATFORM_XLIB_KHR
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା {
    VkIcdSurfaceBase base;
    Display *dpy;
    Window window;
} VkIcdSurfaceXlib;
#endif  // VK_USE_PLATFORM_XLIB_KHR

#ifdef VK_USE_PLATFORM_DIRECTFB_EXT
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା {
    VkIcdSurfaceBase base;
    IDirectFB *dfb;
    IDirectFBSurface *surface;
} VkIcdSurfaceDirectFB;
#endif  // VK_USE_PLATFORM_DIRECTFB_EXT

#ifdef VK_USE_PLATFORM_ANDROID_KHR
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା {
    VkIcdSurfaceBase base;
    ସଂରଚନା ANativeWindow *window;
} VkIcdSurfaceAndroid;
#endif  // VK_USE_PLATFORM_ANDROID_KHR

#ifdef VK_USE_PLATFORM_MACOS_MVK
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା {
    VkIcdSurfaceBase base;
    ଅଚଳ ଶୂନ୍ୟ *pView;
} VkIcdSurfaceMacOS;
#endif  // VK_USE_PLATFORM_MACOS_MVK

#ifdef VK_USE_PLATFORM_IOS_MVK
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା {
    VkIcdSurfaceBase base;
    ଅଚଳ ଶୂନ୍ୟ *pView;
} VkIcdSurfaceIOS;
#endif  // VK_USE_PLATFORM_IOS_MVK

#ifdef VK_USE_PLATFORM_GGP
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା {
    VkIcdSurfaceBase base;
    GgpStreamDescriptor streamDescriptor;
} VkIcdSurfaceGgp;
#endif  // VK_USE_PLATFORM_GGP

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା {
    VkIcdSurfaceBase base;
    VkDisplayModeKHR displayMode;
    uint32_t planeIndex;
    uint32_t plane_ଗଦା_Index;
    VkSurfaceTransformFlagBitsKHR transform;
    ଦଶମିକ globalAlpha;
    VkDisplayPlaneAlphaFlagBitsKHR alphaMode;
    VkExtent2D imageExtent;
} VkIcdSurfaceDisplay;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା {
    VkIcdSurfaceBase base;
} VkIcdSurfaceHeadless;

#ifdef VK_USE_PLATFORM_METAL_EXT
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା {
    VkIcdSurfaceBase base;
    ଅଚଳ CAMetalLayer *pLayer;
} VkIcdSurfaceMetal;
#endif // VK_USE_PLATFORM_METAL_EXT

#ifdef VK_USE_PLATFORM_VI_NN
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା {
    VkIcdSurfaceBase base;
    ଶୂନ୍ୟ *window;
} VkIcdSurfaceVi;
#endif // VK_USE_PLATFORM_VI_NN

#ifdef VK_USE_PLATFORM_SCREEN_QNX
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା {
    VkIcdSurfaceBase base;
    ସଂରଚନା _screen_context *context;
    ସଂରଚନା _screen_window *window;
} VkIcdSurfaceScreen;
#endif  // VK_USE_PLATFORM_SCREEN_QNX

#ifdef VK_USE_PLATFORM_FUCHSIA
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା {
  VkIcdSurfaceBase base;
} VkIcdSurfaceImagePipe;
#endif // VK_USE_PLATFORM_FUCHSIA
