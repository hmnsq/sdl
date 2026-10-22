/*
 * Copyright 2015-2023 The Khronos Group Inc.
 * Copyright 2015-2023 Valve Corporation
 * Copyright 2015-2023 LunarG, Inc.
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 */
#ਹਦਾਇਤ once

#ਅਨ੍ਤਰ੍ਭਾਵ "vulkan.h"
#ਅਨ੍ਤਰ੍ਭਾਵ <stdbool.h>

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

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CURRENT_LOADER_ICD_INTERFACE_ਸੰਸਕਰਣ 7
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MIN_SUPPORTED_LOADER_ICD_INTERFACE_ਸੰਸਕਰਣ 0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MIN_PHYS_DEV_EXTENSION_ICD_INTERFACE_ਸੰਸਕਰਣ 4

// Old typedefs that don't follow a proper naming convention but are preserved for compatibility
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ(VKAPI_PTR *PFN_vk_Negotiate_Loader_ICDInterface_ਸੰਸਕਰਣ)(uint32_t *p_ਸੰਸਕਰਣ);
// This is defined in vk_layer.h which will be found by the loader, but if an ICD is building against this
// file directly, it won't be found.
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ IS_DEFINED_PFN_GetPhysicalDeviceProcAddr
ਕਿਸਮਪਰਿਭਾਸ਼ਾ PFN_vkVoidFunction(VKAPI_PTR *PFN_GetPhysicalDeviceProcAddr)(VkInstance instance, ਅਚਲ ਅੱਖਰ *pName);
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IS_DEFINED_PFN_GetPhysicalDeviceProcAddr
#ਜੇ_ਅੰਤ

// Typedefs for loader/ICD interface
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vk_icd_Negotiate_Loader_ICDInterface_ਸੰਸਕਰਣ)(uint32_t* p_ਸੰਸਕਰਣ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ PFN_vkVoidFunction (VKAPI_PTR *PFN_vk_icdGetInstanceProcAddr)(VkInstance instance, ਅਚਲ ਅੱਖਰ* pName);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ PFN_vkVoidFunction (VKAPI_PTR *PFN_vk_icdGetPhysicalDeviceProcAddr)(VkInstance instance, ਅਚਲ ਅੱਖਰ* pName);
#ਜੇ defined(VK_USE_PLATFORM_WIN32_KHR)
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vk_icdEnumerateAdapterPhysicalDevices)(VkInstance instance, LUID adapterLUID,
    uint32_t* p_Physical_Device_ਗਿਣਤੀ, VkPhysicalDevice* pPhysicalDevices);
#ਜੇ_ਅੰਤ

// Prototypes for loader/ICD interface
#ਜੇ !defined(VK_NO_PROTOTYPES)
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ
    VKAPI_ATTR Vk_ਨਤੀਜਾ VKAPI_CALL vk_icd_Negotiate_Loader_ICDInterface_ਸੰਸਕਰਣ(uint32_t* p_ਸੰਸਕਰਣ);
    VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vk_icdGetInstanceProcAddr(VkInstance instance, ਅਚਲ ਅੱਖਰ* pName);
    VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vk_icdGetPhysicalDeviceProcAddr(VkInstance instance, ਅਚਲ ਅੱਖਰ* pName);
#ਜੇ defined(VK_USE_PLATFORM_WIN32_KHR)
    VKAPI_ATTR Vk_ਨਤੀਜਾ VKAPI_CALL vk_icdEnumerateAdapterPhysicalDevices(VkInstance instance, LUID adapterLUID,
        uint32_t* p_Physical_Device_ਗਿਣਤੀ, VkPhysicalDevice* pPhysicalDevices);
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ

/*
 * The ICD must reserve space for a pointer for the loader's dispatch
 * table, at the start of <each object>.
 * The ICD must initialize this variable using the SET_LOADER_MAGIC_VALUE macro.
 */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ICD_LOADER_MAGIC 0x01CDC0DE

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਸੰਘ {
    uintptr_t loaderMagic;
    ਖਾਲੀ *loader_ਅੰਕੜੇ;
} VK_LOADER_ਅੰਕੜੇ;

ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ ਸੈੱਟ_loader_magic_ਮੁੱਲ(ਖਾਲੀ *pNewObject) {
    VK_LOADER_ਅੰਕੜੇ *loader_info = (VK_LOADER_ਅੰਕੜੇ *)pNewObject;
    loader_info->loaderMagic = ICD_LOADER_MAGIC;
}

ਸਥਿਰ ਸਤਰਅੰਦਰ bool valid_loader_magic_ਮੁੱਲ(ਖਾਲੀ *pNewObject) {
    ਅਚਲ VK_LOADER_ਅੰਕੜੇ *loader_info = (VK_LOADER_ਅੰਕੜੇ *)pNewObject;
    ਵਾਪਸ (loader_info->loaderMagic & 0xffffffff) == ICD_LOADER_MAGIC;
}

/*
 * Windows and Linux ICDs will treat VkSurfaceKHR as a pointer to a struct that
 * contains the platform-specific connection and surface information.
 */
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ {
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

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ {
    VkIcdWsiPlatform platform;
} Vk_Icd_Surface_ਅਧਾਰ;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_USE_PLATFORM_MIR_KHR
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ {
    Vk_Icd_Surface_ਅਧਾਰ ਅਧਾਰ;
    MirConnection *connection;
    MirSurface *mirSurface;
} VkIcdSurfaceMir;
#ਜੇ_ਅੰਤ  // VK_USE_PLATFORM_MIR_KHR

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_USE_PLATFORM_WAYLAND_KHR
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ {
    Vk_Icd_Surface_ਅਧਾਰ ਅਧਾਰ;
    ਬਣਤਰ wl_display *display;
    ਬਣਤਰ wl_surface *surface;
} VkIcdSurfaceWayland;
#ਜੇ_ਅੰਤ  // VK_USE_PLATFORM_WAYLAND_KHR

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_USE_PLATFORM_WIN32_KHR
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ {
    Vk_Icd_Surface_ਅਧਾਰ ਅਧਾਰ;
    HINSTANCE hinstance;
    HWND hwnd;
} VkIcdSurfaceWin32;
#ਜੇ_ਅੰਤ  // VK_USE_PLATFORM_WIN32_KHR

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_USE_PLATFORM_XCB_KHR
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ {
    Vk_Icd_Surface_ਅਧਾਰ ਅਧਾਰ;
    xcb_connection_t *connection;
    xcb_ਖਿੜਕੀ_t ਖਿੜਕੀ;
} VkIcdSurfaceXcb;
#ਜੇ_ਅੰਤ  // VK_USE_PLATFORM_XCB_KHR

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_USE_PLATFORM_XLIB_KHR
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ {
    Vk_Icd_Surface_ਅਧਾਰ ਅਧਾਰ;
    Display *dpy;
    ਖਿੜਕੀ_2 ਖਿੜਕੀ;
} VkIcdSurfaceXlib;
#ਜੇ_ਅੰਤ  // VK_USE_PLATFORM_XLIB_KHR

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_USE_PLATFORM_DIRECTFB_EXT
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ {
    Vk_Icd_Surface_ਅਧਾਰ ਅਧਾਰ;
    IDirectFB *dfb;
    IDirectFBSurface *surface;
} Vk_Icd_Surface_ਸਿੱਧਾ_FB;
#ਜੇ_ਅੰਤ  // VK_USE_PLATFORM_DIRECTFB_EXT

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_USE_PLATFORM_ANDROID_KHR
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ {
    Vk_Icd_Surface_ਅਧਾਰ ਅਧਾਰ;
    ਬਣਤਰ ANative_ਖਿੜਕੀ *ਖਿੜਕੀ;
} VkIcdSurfaceAndroid;
#ਜੇ_ਅੰਤ  // VK_USE_PLATFORM_ANDROID_KHR

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_USE_PLATFORM_MACOS_MVK
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ {
    Vk_Icd_Surface_ਅਧਾਰ ਅਧਾਰ;
    ਅਚਲ ਖਾਲੀ *pView;
} VkIcdSurfaceMacOS;
#ਜੇ_ਅੰਤ  // VK_USE_PLATFORM_MACOS_MVK

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_USE_PLATFORM_IOS_MVK
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ {
    Vk_Icd_Surface_ਅਧਾਰ ਅਧਾਰ;
    ਅਚਲ ਖਾਲੀ *pView;
} VkIcdSurfaceIOS;
#ਜੇ_ਅੰਤ  // VK_USE_PLATFORM_IOS_MVK

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_USE_PLATFORM_GGP
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ {
    Vk_Icd_Surface_ਅਧਾਰ ਅਧਾਰ;
    Ggp_ਧਾਰਾ_Descriptor ਧਾਰਾ_Descriptor;
} VkIcdSurfaceGgp;
#ਜੇ_ਅੰਤ  // VK_USE_PLATFORM_GGP

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ {
    Vk_Icd_Surface_ਅਧਾਰ ਅਧਾਰ;
    Vk_Display_ਬਹੁਲਕ_KHR display_ਬਹੁਲਕ;
    uint32_t plane_ਸੂਚਕਾਂਕ;
    uint32_t plane_ਢੇਰ_ਸੂਚਕਾਂਕ;
    Vk_Surface_Transform_Flag_ਬਿੱਟ_KHR transform;
    ਦਸ਼ਮਲਵ globalAlpha;
    Vk_Display_Plane_Alpha_Flag_ਬਿੱਟ_KHR alpha_ਬਹੁਲਕ;
    VkExtent2D imageExtent;
} VkIcdSurfaceDisplay;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ {
    Vk_Icd_Surface_ਅਧਾਰ ਅਧਾਰ;
} VkIcdSurfaceHeadless;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_USE_PLATFORM_METAL_EXT
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ {
    Vk_Icd_Surface_ਅਧਾਰ ਅਧਾਰ;
    ਅਚਲ CAMetalLayer *pLayer;
} VkIcdSurfaceMetal;
#ਜੇ_ਅੰਤ // VK_USE_PLATFORM_METAL_EXT

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_USE_PLATFORM_VI_NN
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ {
    Vk_Icd_Surface_ਅਧਾਰ ਅਧਾਰ;
    ਖਾਲੀ *ਖਿੜਕੀ;
} VkIcdSurfaceVi;
#ਜੇ_ਅੰਤ // VK_USE_PLATFORM_VI_NN

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_USE_PLATFORM_SCREEN_QNX
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ {
    Vk_Icd_Surface_ਅਧਾਰ ਅਧਾਰ;
    ਬਣਤਰ _screen_context *context;
    ਬਣਤਰ screen_ਖਿੜਕੀ *ਖਿੜਕੀ;
} VkIcdSurfaceScreen;
#ਜੇ_ਅੰਤ  // VK_USE_PLATFORM_SCREEN_QNX

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_USE_PLATFORM_FUCHSIA
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ {
  Vk_Icd_Surface_ਅਧਾਰ ਅਧਾਰ;
} VkIcdSurfaceImagePipe;
#ਜੇ_ਅੰਤ // VK_USE_PLATFORM_FUCHSIA
