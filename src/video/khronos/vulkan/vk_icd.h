/*
 * Copyright 2015-2023 The Khronos Group Inc.
 * Copyright 2015-2023 Valve Corporation
 * Copyright 2015-2023 LunarG, Inc.
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 */
#رهنمود once

#ضمن "vulkan.h"
#ضمن <stdbool.h>

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

#تعریف_کن CURRENT_LOADER_ICD_INTERFACE_نسخه 7
#تعریف_کن MIN_SUPPORTED_LOADER_ICD_INTERFACE_نسخه 0
#تعریف_کن MIN_PHYS_DEV_EXTENSION_ICD_INTERFACE_نسخه 4

// Old typedefs that don't follow a proper naming convention but are preserved for compatibility
تعريفنوع Vk_نتیجه(VKAPI_PTR *PFN_vk_Negotiate_Loader_ICDInterface_نسخه)(uint32_t *p_نسخه);
// This is defined in vk_layer.h which will be found by the loader, but if an ICD is building against this
// file directly, it won't be found.
#اگر_تعریف_نشده IS_DEFINED_PFN_GetPhysicalDeviceProcAddr
تعريفنوع PFN_vkVoidFunction(VKAPI_PTR *PFN_GetPhysicalDeviceProcAddr)(VkInstance instance, ثابت حرف *pName);
#تعریف_کن IS_DEFINED_PFN_GetPhysicalDeviceProcAddr
#پایان_اگر

// Typedefs for loader/ICD interface
تعريفنوع Vk_نتیجه (VKAPI_PTR *PFN_vk_icd_Negotiate_Loader_ICDInterface_نسخه)(uint32_t* p_نسخه);
تعريفنوع PFN_vkVoidFunction (VKAPI_PTR *PFN_vk_icdGetInstanceProcAddr)(VkInstance instance, ثابت حرف* pName);
تعريفنوع PFN_vkVoidFunction (VKAPI_PTR *PFN_vk_icdGetPhysicalDeviceProcAddr)(VkInstance instance, ثابت حرف* pName);
#إذا defined(VK_USE_PLATFORM_WIN32_KHR)
تعريفنوع Vk_نتیجه (VKAPI_PTR *PFN_vk_icdEnumerateAdapterPhysicalDevices)(VkInstance instance, LUID adapterLUID,
    uint32_t* p_Physical_Device_شمار, VkPhysicalDevice* pPhysicalDevices);
#پایان_اگر

// Prototypes for loader/ICD interface
#إذا !defined(VK_NO_PROTOTYPES)
#اگر_تعریف_شده __cplusplus
خارجي "C" {
#پایان_اگر
    VKAPI_ATTR Vk_نتیجه VKAPI_CALL vk_icd_Negotiate_Loader_ICDInterface_نسخه(uint32_t* p_نسخه);
    VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vk_icdGetInstanceProcAddr(VkInstance instance, ثابت حرف* pName);
    VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vk_icdGetPhysicalDeviceProcAddr(VkInstance instance, ثابت حرف* pName);
#إذا defined(VK_USE_PLATFORM_WIN32_KHR)
    VKAPI_ATTR Vk_نتیجه VKAPI_CALL vk_icdEnumerateAdapterPhysicalDevices(VkInstance instance, LUID adapterLUID,
        uint32_t* p_Physical_Device_شمار, VkPhysicalDevice* pPhysicalDevices);
#پایان_اگر
#اگر_تعریف_شده __cplusplus
}
#پایان_اگر
#پایان_اگر

/*
 * The ICD must reserve space for a pointer for the loader's dispatch
 * table, at the start of <each object>.
 * The ICD must initialize this variable using the SET_LOADER_MAGIC_VALUE macro.
 */

#تعریف_کن ICD_LOADER_MAGIC 0x01CDC0DE

تعريفنوع اتحاد {
    uintptr_t loaderMagic;
    فراغ *loader_داده;
} VK_LOADER_داده;

ساكن مضمن فراغ مجموعه_loader_magic_مقدار(فراغ *pNewObject) {
    VK_LOADER_داده *loader_info = (VK_LOADER_داده *)pNewObject;
    loader_info->loaderMagic = ICD_LOADER_MAGIC;
}

ساكن مضمن bool valid_loader_magic_مقدار(فراغ *pNewObject) {
    ثابت VK_LOADER_داده *loader_info = (VK_LOADER_داده *)pNewObject;
    أرجع (loader_info->loaderMagic & 0xffffffff) == ICD_LOADER_MAGIC;
}

/*
 * Windows and Linux ICDs will treat VkSurfaceKHR as a pointer to a struct that
 * contains the platform-specific connection and surface information.
 */
تعريفنوع تعداد {
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

تعريفنوع بنية {
    VkIcdWsiPlatform platform;
} Vk_Icd_Surface_پایه;

#اگر_تعریف_شده VK_USE_PLATFORM_MIR_KHR
تعريفنوع بنية {
    Vk_Icd_Surface_پایه پایه;
    MirConnection *connection;
    MirSurface *mirSurface;
} VkIcdSurfaceMir;
#پایان_اگر  // VK_USE_PLATFORM_MIR_KHR

#اگر_تعریف_شده VK_USE_PLATFORM_WAYLAND_KHR
تعريفنوع بنية {
    Vk_Icd_Surface_پایه پایه;
    بنية wl_display *display;
    بنية wl_surface *surface;
} VkIcdSurfaceWayland;
#پایان_اگر  // VK_USE_PLATFORM_WAYLAND_KHR

#اگر_تعریف_شده VK_USE_PLATFORM_WIN32_KHR
تعريفنوع بنية {
    Vk_Icd_Surface_پایه پایه;
    HINSTANCE hinstance;
    HWND hwnd;
} VkIcdSurfaceWin32;
#پایان_اگر  // VK_USE_PLATFORM_WIN32_KHR

#اگر_تعریف_شده VK_USE_PLATFORM_XCB_KHR
تعريفنوع بنية {
    Vk_Icd_Surface_پایه پایه;
    xcb_connection_t *connection;
    xcb_پنجره_t پنجره;
} VkIcdSurfaceXcb;
#پایان_اگر  // VK_USE_PLATFORM_XCB_KHR

#اگر_تعریف_شده VK_USE_PLATFORM_XLIB_KHR
تعريفنوع بنية {
    Vk_Icd_Surface_پایه پایه;
    Display *dpy;
    پنجره_2 پنجره;
} VkIcdSurfaceXlib;
#پایان_اگر  // VK_USE_PLATFORM_XLIB_KHR

#اگر_تعریف_شده VK_USE_PLATFORM_DIRECTFB_EXT
تعريفنوع بنية {
    Vk_Icd_Surface_پایه پایه;
    IDirectFB *dfb;
    IDirectFBSurface *surface;
} Vk_Icd_Surface_مستقیم_FB;
#پایان_اگر  // VK_USE_PLATFORM_DIRECTFB_EXT

#اگر_تعریف_شده VK_USE_PLATFORM_ANDROID_KHR
تعريفنوع بنية {
    Vk_Icd_Surface_پایه پایه;
    بنية ANative_پنجره *پنجره;
} VkIcdSurfaceAndroid;
#پایان_اگر  // VK_USE_PLATFORM_ANDROID_KHR

#اگر_تعریف_شده VK_USE_PLATFORM_MACOS_MVK
تعريفنوع بنية {
    Vk_Icd_Surface_پایه پایه;
    ثابت فراغ *pView;
} VkIcdSurfaceMacOS;
#پایان_اگر  // VK_USE_PLATFORM_MACOS_MVK

#اگر_تعریف_شده VK_USE_PLATFORM_IOS_MVK
تعريفنوع بنية {
    Vk_Icd_Surface_پایه پایه;
    ثابت فراغ *pView;
} VkIcdSurfaceIOS;
#پایان_اگر  // VK_USE_PLATFORM_IOS_MVK

#اگر_تعریف_شده VK_USE_PLATFORM_GGP
تعريفنوع بنية {
    Vk_Icd_Surface_پایه پایه;
    Ggp_جریان_Descriptor جریان_Descriptor;
} VkIcdSurfaceGgp;
#پایان_اگر  // VK_USE_PLATFORM_GGP

تعريفنوع بنية {
    Vk_Icd_Surface_پایه پایه;
    Vk_Display_نما_KHR display_نما;
    uint32_t plane_شاخص;
    uint32_t plane_پشته_شاخص;
    Vk_Surface_Transform_Flag_بیتها_KHR transform;
    عائم globalAlpha;
    Vk_Display_Plane_Alpha_Flag_بیتها_KHR alpha_نما;
    VkExtent2D imageExtent;
} VkIcdSurfaceDisplay;

تعريفنوع بنية {
    Vk_Icd_Surface_پایه پایه;
} VkIcdSurfaceHeadless;

#اگر_تعریف_شده VK_USE_PLATFORM_METAL_EXT
تعريفنوع بنية {
    Vk_Icd_Surface_پایه پایه;
    ثابت CAMetalLayer *pLayer;
} VkIcdSurfaceMetal;
#پایان_اگر // VK_USE_PLATFORM_METAL_EXT

#اگر_تعریف_شده VK_USE_PLATFORM_VI_NN
تعريفنوع بنية {
    Vk_Icd_Surface_پایه پایه;
    فراغ *پنجره;
} VkIcdSurfaceVi;
#پایان_اگر // VK_USE_PLATFORM_VI_NN

#اگر_تعریف_شده VK_USE_PLATFORM_SCREEN_QNX
تعريفنوع بنية {
    Vk_Icd_Surface_پایه پایه;
    بنية _screen_context *context;
    بنية screen_پنجره *پنجره;
} VkIcdSurfaceScreen;
#پایان_اگر  // VK_USE_PLATFORM_SCREEN_QNX

#اگر_تعریف_شده VK_USE_PLATFORM_FUCHSIA
تعريفنوع بنية {
  Vk_Icd_Surface_پایه پایه;
} VkIcdSurfaceImagePipe;
#پایان_اگر // VK_USE_PLATFORM_FUCHSIA
