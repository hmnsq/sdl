/*
 * Copyright 2015-2023 The Khronos Group Inc.
 * Copyright 2015-2023 Valve Corporation
 * Copyright 2015-2023 LunarG, Inc.
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 */
#ہدایت once

#شامل "vulkan.h"
#شامل <stdbool.h>

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

#تعریف_کرو CURRENT_LOADER_ICD_INTERFACE_نسخہ 7
#تعریف_کرو MIN_SUPPORTED_LOADER_ICD_INTERFACE_نسخہ 0
#تعریف_کرو MIN_PHYS_DEV_EXTENSION_ICD_INTERFACE_نسخہ 4

// Old typedefs that don't follow a proper naming convention but are preserved for compatibility
قسمتعریف Vk_نتیجہ(VKAPI_PTR *PFN_vk_Negotiate_Loader_ICDInterface_نسخہ)(uint32_t *p_نسخہ);
// This is defined in vk_layer.h which will be found by the loader, but if an ICD is building against this
// file directly, it won't be found.
#اگر_غیر_تعریف_شدہ IS_DEFINED_PFN_GetPhysicalDeviceProcAddr
قسمتعریف PFN_vkVoidFunction(VKAPI_PTR *PFN_GetPhysicalDeviceProcAddr)(VkInstance instance, ثابت حرف *pName);
#تعریف_کرو IS_DEFINED_PFN_GetPhysicalDeviceProcAddr
#اگر_ختم

// Typedefs for loader/ICD interface
قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vk_icd_Negotiate_Loader_ICDInterface_نسخہ)(uint32_t* p_نسخہ);
قسمتعریف PFN_vkVoidFunction (VKAPI_PTR *PFN_vk_icdGetInstanceProcAddr)(VkInstance instance, ثابت حرف* pName);
قسمتعریف PFN_vkVoidFunction (VKAPI_PTR *PFN_vk_icdGetPhysicalDeviceProcAddr)(VkInstance instance, ثابت حرف* pName);
#اگر defined(VK_USE_PLATFORM_WIN32_KHR)
قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vk_icdEnumerateAdapterPhysicalDevices)(VkInstance instance, LUID adapterLUID,
    uint32_t* p_Physical_Device_گنتی, VkPhysicalDevice* pPhysicalDevices);
#اگر_ختم

// Prototypes for loader/ICD interface
#اگر !defined(VK_NO_PROTOTYPES)
#اگر_تعریف_شدہ __cplusplus
خارجی "C" {
#اگر_ختم
    VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_icd_Negotiate_Loader_ICDInterface_نسخہ(uint32_t* p_نسخہ);
    VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vk_icdGetInstanceProcAddr(VkInstance instance, ثابت حرف* pName);
    VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vk_icdGetPhysicalDeviceProcAddr(VkInstance instance, ثابت حرف* pName);
#اگر defined(VK_USE_PLATFORM_WIN32_KHR)
    VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_icdEnumerateAdapterPhysicalDevices(VkInstance instance, LUID adapterLUID,
        uint32_t* p_Physical_Device_گنتی, VkPhysicalDevice* pPhysicalDevices);
#اگر_ختم
#اگر_تعریف_شدہ __cplusplus
}
#اگر_ختم
#اگر_ختم

/*
 * The ICD must reserve space for a pointer for the loader's dispatch
 * table, at the start of <each object>.
 * The ICD must initialize this variable using the SET_LOADER_MAGIC_VALUE macro.
 */

#تعریف_کرو ICD_LOADER_MAGIC 0x01CDC0DE

قسمتعریف اتحاد {
    uintptr_t loaderMagic;
    خالی *loader_ڈیٹا;
} VK_LOADER_ڈیٹا;

ساکن اندرونی خالی سیٹ_loader_magic_قدر(خالی *pNewObject) {
    VK_LOADER_ڈیٹا *loader_info = (VK_LOADER_ڈیٹا *)pNewObject;
    loader_info->loaderMagic = ICD_LOADER_MAGIC;
}

ساکن اندرونی bool valid_loader_magic_قدر(خالی *pNewObject) {
    ثابت VK_LOADER_ڈیٹا *loader_info = (VK_LOADER_ڈیٹا *)pNewObject;
    واپس (loader_info->loaderMagic & 0xffffffff) == ICD_LOADER_MAGIC;
}

/*
 * Windows and Linux ICDs will treat VkSurfaceKHR as a pointer to a struct that
 * contains the platform-specific connection and surface information.
 */
قسمتعریف شمار {
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

قسمتعریف ساخت {
    VkIcdWsiPlatform platform;
} Vk_Icd_Surface_بنیاد;

#اگر_تعریف_شدہ VK_USE_PLATFORM_MIR_KHR
قسمتعریف ساخت {
    Vk_Icd_Surface_بنیاد بنیاد;
    MirConnection *connection;
    MirSurface *mirSurface;
} VkIcdSurfaceMir;
#اگر_ختم  // VK_USE_PLATFORM_MIR_KHR

#اگر_تعریف_شدہ VK_USE_PLATFORM_WAYLAND_KHR
قسمتعریف ساخت {
    Vk_Icd_Surface_بنیاد بنیاد;
    ساخت wl_display *display;
    ساخت wl_surface *surface;
} VkIcdSurfaceWayland;
#اگر_ختم  // VK_USE_PLATFORM_WAYLAND_KHR

#اگر_تعریف_شدہ VK_USE_PLATFORM_WIN32_KHR
قسمتعریف ساخت {
    Vk_Icd_Surface_بنیاد بنیاد;
    HINSTANCE hinstance;
    HWND hwnd;
} VkIcdSurfaceWin32;
#اگر_ختم  // VK_USE_PLATFORM_WIN32_KHR

#اگر_تعریف_شدہ VK_USE_PLATFORM_XCB_KHR
قسمتعریف ساخت {
    Vk_Icd_Surface_بنیاد بنیاد;
    xcb_connection_t *connection;
    xcb_کھڑکی_t کھڑکی;
} VkIcdSurfaceXcb;
#اگر_ختم  // VK_USE_PLATFORM_XCB_KHR

#اگر_تعریف_شدہ VK_USE_PLATFORM_XLIB_KHR
قسمتعریف ساخت {
    Vk_Icd_Surface_بنیاد بنیاد;
    Display *dpy;
    کھڑکی_2 کھڑکی;
} VkIcdSurfaceXlib;
#اگر_ختم  // VK_USE_PLATFORM_XLIB_KHR

#اگر_تعریف_شدہ VK_USE_PLATFORM_DIRECTFB_EXT
قسمتعریف ساخت {
    Vk_Icd_Surface_بنیاد بنیاد;
    IDirectFB *dfb;
    IDirectFBSurface *surface;
} Vk_Icd_Surface_براہ_راست_FB;
#اگر_ختم  // VK_USE_PLATFORM_DIRECTFB_EXT

#اگر_تعریف_شدہ VK_USE_PLATFORM_ANDROID_KHR
قسمتعریف ساخت {
    Vk_Icd_Surface_بنیاد بنیاد;
    ساخت ANative_کھڑکی *کھڑکی;
} VkIcdSurfaceAndroid;
#اگر_ختم  // VK_USE_PLATFORM_ANDROID_KHR

#اگر_تعریف_شدہ VK_USE_PLATFORM_MACOS_MVK
قسمتعریف ساخت {
    Vk_Icd_Surface_بنیاد بنیاد;
    ثابت خالی *pView;
} VkIcdSurfaceMacOS;
#اگر_ختم  // VK_USE_PLATFORM_MACOS_MVK

#اگر_تعریف_شدہ VK_USE_PLATFORM_IOS_MVK
قسمتعریف ساخت {
    Vk_Icd_Surface_بنیاد بنیاد;
    ثابت خالی *pView;
} VkIcdSurfaceIOS;
#اگر_ختم  // VK_USE_PLATFORM_IOS_MVK

#اگر_تعریف_شدہ VK_USE_PLATFORM_GGP
قسمتعریف ساخت {
    Vk_Icd_Surface_بنیاد بنیاد;
    Ggp_دھارا_Descriptor دھارا_Descriptor;
} VkIcdSurfaceGgp;
#اگر_ختم  // VK_USE_PLATFORM_GGP

قسمتعریف ساخت {
    Vk_Icd_Surface_بنیاد بنیاد;
    Vk_Display_منوال_KHR display_منوال;
    uint32_t plane_اشاریہ;
    uint32_t plane_ڈھیر_اشاریہ;
    Vk_Surface_Transform_Flag_بٹ_KHR transform;
    اعشاری globalAlpha;
    Vk_Display_Plane_Alpha_Flag_بٹ_KHR alpha_منوال;
    VkExtent2D imageExtent;
} VkIcdSurfaceDisplay;

قسمتعریف ساخت {
    Vk_Icd_Surface_بنیاد بنیاد;
} VkIcdSurfaceHeadless;

#اگر_تعریف_شدہ VK_USE_PLATFORM_METAL_EXT
قسمتعریف ساخت {
    Vk_Icd_Surface_بنیاد بنیاد;
    ثابت CAMetalLayer *pLayer;
} VkIcdSurfaceMetal;
#اگر_ختم // VK_USE_PLATFORM_METAL_EXT

#اگر_تعریف_شدہ VK_USE_PLATFORM_VI_NN
قسمتعریف ساخت {
    Vk_Icd_Surface_بنیاد بنیاد;
    خالی *کھڑکی;
} VkIcdSurfaceVi;
#اگر_ختم // VK_USE_PLATFORM_VI_NN

#اگر_تعریف_شدہ VK_USE_PLATFORM_SCREEN_QNX
قسمتعریف ساخت {
    Vk_Icd_Surface_بنیاد بنیاد;
    ساخت _screen_context *context;
    ساخت screen_کھڑکی *کھڑکی;
} VkIcdSurfaceScreen;
#اگر_ختم  // VK_USE_PLATFORM_SCREEN_QNX

#اگر_تعریف_شدہ VK_USE_PLATFORM_FUCHSIA
قسمتعریف ساخت {
  Vk_Icd_Surface_بنیاد بنیاد;
} VkIcdSurfaceImagePipe;
#اگر_ختم // VK_USE_PLATFORM_FUCHSIA
