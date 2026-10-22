/*
 * Copyright 2015-2023 The Khronos Group Inc.
 * Copyright 2015-2023 Valve Corporation
 * Copyright 2015-2023 LunarG, Inc.
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 */
#هدايت once

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

#وصف_ڪريو CURRENT_LOADER_ICD_INTERFACE_نسخو 7
#وصف_ڪريو MIN_SUPPORTED_LOADER_ICD_INTERFACE_نسخو 0
#وصف_ڪريو MIN_PHYS_DEV_EXTENSION_ICD_INTERFACE_نسخو 4

// Old typedefs that don't follow a proper naming convention but are preserved for compatibility
تعريفنوع Vk_نتيجو(VKAPI_PTR *PFN_vk_Negotiate_Loader_ICDInterface_نسخو)(uint32_t *p_نسخو);
// This is defined in vk_layer.h which will be found by the loader, but if an ICD is building against this
// file directly, it won't be found.
#جيڪڏهن_وصف_نه_ٿيل IS_DEFINED_PFN_GetPhysicalDeviceProcAddr
تعريفنوع PFN_vkVoidFunction(VKAPI_PTR *PFN_GetPhysicalDeviceProcAddr)(VkInstance instance, ثابت حرف *pName);
#وصف_ڪريو IS_DEFINED_PFN_GetPhysicalDeviceProcAddr
#جيڪڏهن_پورو

// Typedefs for loader/ICD interface
تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vk_icd_Negotiate_Loader_ICDInterface_نسخو)(uint32_t* p_نسخو);
تعريفنوع PFN_vkVoidFunction (VKAPI_PTR *PFN_vk_icdGetInstanceProcAddr)(VkInstance instance, ثابت حرف* pName);
تعريفنوع PFN_vkVoidFunction (VKAPI_PTR *PFN_vk_icdGetPhysicalDeviceProcAddr)(VkInstance instance, ثابت حرف* pName);
#إذا defined(VK_USE_PLATFORM_WIN32_KHR)
تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vk_icdEnumerateAdapterPhysicalDevices)(VkInstance instance, LUID adapterLUID,
    uint32_t* p_Physical_Device_ڳڻپ, VkPhysicalDevice* pPhysicalDevices);
#جيڪڏهن_پورو

// Prototypes for loader/ICD interface
#إذا !defined(VK_NO_PROTOTYPES)
#جيڪڏهن_وصف_ٿيل __cplusplus
خارجي "C" {
#جيڪڏهن_پورو
    VKAPI_ATTR Vk_نتيجو VKAPI_CALL vk_icd_Negotiate_Loader_ICDInterface_نسخو(uint32_t* p_نسخو);
    VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vk_icdGetInstanceProcAddr(VkInstance instance, ثابت حرف* pName);
    VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vk_icdGetPhysicalDeviceProcAddr(VkInstance instance, ثابت حرف* pName);
#إذا defined(VK_USE_PLATFORM_WIN32_KHR)
    VKAPI_ATTR Vk_نتيجو VKAPI_CALL vk_icdEnumerateAdapterPhysicalDevices(VkInstance instance, LUID adapterLUID,
        uint32_t* p_Physical_Device_ڳڻپ, VkPhysicalDevice* pPhysicalDevices);
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل __cplusplus
}
#جيڪڏهن_پورو
#جيڪڏهن_پورو

/*
 * The ICD must reserve space for a pointer for the loader's dispatch
 * table, at the start of <each object>.
 * The ICD must initialize this variable using the SET_LOADER_MAGIC_VALUE macro.
 */

#وصف_ڪريو ICD_LOADER_MAGIC 0x01CDC0DE

تعريفنوع اتحاد {
    uintptr_t loaderMagic;
    فراغ *loader_معلومات;
} VK_LOADER_معلومات;

ساكن مضمن فراغ سيٽ_loader_magic_قدر(فراغ *pNewObject) {
    VK_LOADER_معلومات *loader_info = (VK_LOADER_معلومات *)pNewObject;
    loader_info->loaderMagic = ICD_LOADER_MAGIC;
}

ساكن مضمن bool valid_loader_magic_قدر(فراغ *pNewObject) {
    ثابت VK_LOADER_معلومات *loader_info = (VK_LOADER_معلومات *)pNewObject;
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
} Vk_Icd_Surface_بنياد;

#جيڪڏهن_وصف_ٿيل VK_USE_PLATFORM_MIR_KHR
تعريفنوع بنية {
    Vk_Icd_Surface_بنياد بنياد;
    MirConnection *connection;
    MirSurface *mirSurface;
} VkIcdSurfaceMir;
#جيڪڏهن_پورو  // VK_USE_PLATFORM_MIR_KHR

#جيڪڏهن_وصف_ٿيل VK_USE_PLATFORM_WAYLAND_KHR
تعريفنوع بنية {
    Vk_Icd_Surface_بنياد بنياد;
    بنية wl_display *display;
    بنية wl_surface *surface;
} VkIcdSurfaceWayland;
#جيڪڏهن_پورو  // VK_USE_PLATFORM_WAYLAND_KHR

#جيڪڏهن_وصف_ٿيل VK_USE_PLATFORM_WIN32_KHR
تعريفنوع بنية {
    Vk_Icd_Surface_بنياد بنياد;
    HINSTANCE hinstance;
    HWND hwnd;
} VkIcdSurfaceWin32;
#جيڪڏهن_پورو  // VK_USE_PLATFORM_WIN32_KHR

#جيڪڏهن_وصف_ٿيل VK_USE_PLATFORM_XCB_KHR
تعريفنوع بنية {
    Vk_Icd_Surface_بنياد بنياد;
    xcb_connection_t *connection;
    xcb_دري_t دري;
} VkIcdSurfaceXcb;
#جيڪڏهن_پورو  // VK_USE_PLATFORM_XCB_KHR

#جيڪڏهن_وصف_ٿيل VK_USE_PLATFORM_XLIB_KHR
تعريفنوع بنية {
    Vk_Icd_Surface_بنياد بنياد;
    Display *dpy;
    دري_2 دري;
} VkIcdSurfaceXlib;
#جيڪڏهن_پورو  // VK_USE_PLATFORM_XLIB_KHR

#جيڪڏهن_وصف_ٿيل VK_USE_PLATFORM_DIRECTFB_EXT
تعريفنوع بنية {
    Vk_Icd_Surface_بنياد بنياد;
    IDirectFB *dfb;
    IDirectFBSurface *surface;
} Vk_Icd_Surface_سڌو_FB;
#جيڪڏهن_پورو  // VK_USE_PLATFORM_DIRECTFB_EXT

#جيڪڏهن_وصف_ٿيل VK_USE_PLATFORM_ANDROID_KHR
تعريفنوع بنية {
    Vk_Icd_Surface_بنياد بنياد;
    بنية ANative_دري *دري;
} VkIcdSurfaceAndroid;
#جيڪڏهن_پورو  // VK_USE_PLATFORM_ANDROID_KHR

#جيڪڏهن_وصف_ٿيل VK_USE_PLATFORM_MACOS_MVK
تعريفنوع بنية {
    Vk_Icd_Surface_بنياد بنياد;
    ثابت فراغ *pView;
} VkIcdSurfaceMacOS;
#جيڪڏهن_پورو  // VK_USE_PLATFORM_MACOS_MVK

#جيڪڏهن_وصف_ٿيل VK_USE_PLATFORM_IOS_MVK
تعريفنوع بنية {
    Vk_Icd_Surface_بنياد بنياد;
    ثابت فراغ *pView;
} VkIcdSurfaceIOS;
#جيڪڏهن_پورو  // VK_USE_PLATFORM_IOS_MVK

#جيڪڏهن_وصف_ٿيل VK_USE_PLATFORM_GGP
تعريفنوع بنية {
    Vk_Icd_Surface_بنياد بنياد;
    Ggp_وهڪرو_Descriptor وهڪرو_Descriptor;
} VkIcdSurfaceGgp;
#جيڪڏهن_پورو  // VK_USE_PLATFORM_GGP

تعريفنوع بنية {
    Vk_Icd_Surface_بنياد بنياد;
    Vk_Display_گهڻائي_KHR display_گهڻائي;
    uint32_t plane_اشاريو;
    uint32_t plane_ڍير_اشاريو;
    Vk_Surface_Transform_Flag_بٽ_KHR transform;
    عائم globalAlpha;
    Vk_Display_Plane_Alpha_Flag_بٽ_KHR alpha_گهڻائي;
    VkExtent2D imageExtent;
} VkIcdSurfaceDisplay;

تعريفنوع بنية {
    Vk_Icd_Surface_بنياد بنياد;
} VkIcdSurfaceHeadless;

#جيڪڏهن_وصف_ٿيل VK_USE_PLATFORM_METAL_EXT
تعريفنوع بنية {
    Vk_Icd_Surface_بنياد بنياد;
    ثابت CAMetalLayer *pLayer;
} VkIcdSurfaceMetal;
#جيڪڏهن_پورو // VK_USE_PLATFORM_METAL_EXT

#جيڪڏهن_وصف_ٿيل VK_USE_PLATFORM_VI_NN
تعريفنوع بنية {
    Vk_Icd_Surface_بنياد بنياد;
    فراغ *دري;
} VkIcdSurfaceVi;
#جيڪڏهن_پورو // VK_USE_PLATFORM_VI_NN

#جيڪڏهن_وصف_ٿيل VK_USE_PLATFORM_SCREEN_QNX
تعريفنوع بنية {
    Vk_Icd_Surface_بنياد بنياد;
    بنية _screen_context *context;
    بنية screen_دري *دري;
} VkIcdSurfaceScreen;
#جيڪڏهن_پورو  // VK_USE_PLATFORM_SCREEN_QNX

#جيڪڏهن_وصف_ٿيل VK_USE_PLATFORM_FUCHSIA
تعريفنوع بنية {
  Vk_Icd_Surface_بنياد بنياد;
} VkIcdSurfaceImagePipe;
#جيڪڏهن_پورو // VK_USE_PLATFORM_FUCHSIA
