/*
 * Copyright 2015-2023 The Khronos Group Inc.
 * Copyright 2015-2023 Valve Corporation
 * Copyright 2015-2023 LunarG, Inc.
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 */
#ಸೂಚನೆ once

#ಅನ್ತರ್ಭಾವ "vulkan.h"
#ಅನ್ತರ್ಭಾವ <stdbool.h>

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

#ವ್ಯಾಖ್ಯಾನಿಸು CURRENT_LOADER_ICD_INTERFACE_ಆವೃತ್ತಿ 7
#ವ್ಯಾಖ್ಯಾನಿಸು MIN_SUPPORTED_LOADER_ICD_INTERFACE_ಆವೃತ್ತಿ 0
#ವ್ಯಾಖ್ಯಾನಿಸು MIN_PHYS_DEV_EXTENSION_ICD_INTERFACE_ಆವೃತ್ತಿ 4

// Old typedefs that don't follow a proper naming convention but are preserved for compatibility
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ(VKAPI_PTR *PFN_vk_Negotiate_Loader_ICDInterface_ಆವೃತ್ತಿ)(uint32_t *p_ಆವೃತ್ತಿ);
// This is defined in vk_layer.h which will be found by the loader, but if an ICD is building against this
// file directly, it won't be found.
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ IS_DEFINED_PFN_GetPhysicalDeviceProcAddr
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ PFN_vkVoidFunction(VKAPI_PTR *PFN_GetPhysicalDeviceProcAddr)(VkInstance instance, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pName);
#ವ್ಯಾಖ್ಯಾನಿಸು IS_DEFINED_PFN_GetPhysicalDeviceProcAddr
#ಆದರೆ_ಅಂತ್ಯ

// Typedefs for loader/ICD interface
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vk_icd_Negotiate_Loader_ICDInterface_ಆವೃತ್ತಿ)(uint32_t* p_ಆವೃತ್ತಿ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ PFN_vkVoidFunction (VKAPI_PTR *PFN_vk_icdGetInstanceProcAddr)(VkInstance instance, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ* pName);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ PFN_vkVoidFunction (VKAPI_PTR *PFN_vk_icdGetPhysicalDeviceProcAddr)(VkInstance instance, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ* pName);
#ಆದರೆ defined(VK_USE_PLATFORM_WIN32_KHR)
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vk_icdEnumerateAdapterPhysicalDevices)(VkInstance instance, LUID adapterLUID,
    uint32_t* p_Physical_Device_ಎಣಿಕೆ, VkPhysicalDevice* pPhysicalDevices);
#ಆದರೆ_ಅಂತ್ಯ

// Prototypes for loader/ICD interface
#ಆದರೆ !defined(VK_NO_PROTOTYPES)
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
ಬಾಹ್ಯ "C" {
#ಆದರೆ_ಅಂತ್ಯ
    VKAPI_ATTR Vk_ಫಲಿತಾಂಶ VKAPI_CALL vk_icd_Negotiate_Loader_ICDInterface_ಆವೃತ್ತಿ(uint32_t* p_ಆವೃತ್ತಿ);
    VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vk_icdGetInstanceProcAddr(VkInstance instance, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ* pName);
    VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vk_icdGetPhysicalDeviceProcAddr(VkInstance instance, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ* pName);
#ಆದರೆ defined(VK_USE_PLATFORM_WIN32_KHR)
    VKAPI_ATTR Vk_ಫಲಿತಾಂಶ VKAPI_CALL vk_icdEnumerateAdapterPhysicalDevices(VkInstance instance, LUID adapterLUID,
        uint32_t* p_Physical_Device_ಎಣಿಕೆ, VkPhysicalDevice* pPhysicalDevices);
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ

/*
 * The ICD must reserve space for a pointer for the loader's dispatch
 * table, at the start of <each object>.
 * The ICD must initialize this variable using the SET_LOADER_MAGIC_VALUE macro.
 */

#ವ್ಯಾಖ್ಯಾನಿಸು ICD_LOADER_MAGIC 0x01CDC0DE

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಒಕ್ಕೂಟ {
    uintptr_t loaderMagic;
    ಶೂನ್ಯ *loader_ದತ್ತಾಂಶ;
} VK_LOADER_ದತ್ತಾಂಶ;

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ ಗಣ_loader_magic_ಮೌಲ್ಯ(ಶೂನ್ಯ *pNewObject) {
    VK_LOADER_ದತ್ತಾಂಶ *loader_info = (VK_LOADER_ದತ್ತಾಂಶ *)pNewObject;
    loader_info->loaderMagic = ICD_LOADER_MAGIC;
}

ಸ್ಥಿರ ಸಾಲೊಳಗೆ bool valid_loader_magic_ಮೌಲ್ಯ(ಶೂನ್ಯ *pNewObject) {
    ಸ್ಥಿರಾಂಕ VK_LOADER_ದತ್ತಾಂಶ *loader_info = (VK_LOADER_ದತ್ತಾಂಶ *)pNewObject;
    ಹಿಂತಿರುಗಿ (loader_info->loaderMagic & 0xffffffff) == ICD_LOADER_MAGIC;
}

/*
 * Windows and Linux ICDs will treat VkSurfaceKHR as a pointer to a struct that
 * contains the platform-specific connection and surface information.
 */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ {
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

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ {
    VkIcdWsiPlatform platform;
} Vk_Icd_Surface_ತಳ;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_USE_PLATFORM_MIR_KHR
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ {
    Vk_Icd_Surface_ತಳ ತಳ;
    MirConnection *connection;
    MirSurface *mirSurface;
} VkIcdSurfaceMir;
#ಆದರೆ_ಅಂತ್ಯ  // VK_USE_PLATFORM_MIR_KHR

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_USE_PLATFORM_WAYLAND_KHR
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ {
    Vk_Icd_Surface_ತಳ ತಳ;
    ರಚನೆ wl_display *display;
    ರಚನೆ wl_surface *surface;
} VkIcdSurfaceWayland;
#ಆದರೆ_ಅಂತ್ಯ  // VK_USE_PLATFORM_WAYLAND_KHR

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_USE_PLATFORM_WIN32_KHR
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ {
    Vk_Icd_Surface_ತಳ ತಳ;
    HINSTANCE hinstance;
    HWND hwnd;
} VkIcdSurfaceWin32;
#ಆದರೆ_ಅಂತ್ಯ  // VK_USE_PLATFORM_WIN32_KHR

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_USE_PLATFORM_XCB_KHR
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ {
    Vk_Icd_Surface_ತಳ ತಳ;
    xcb_connection_t *connection;
    xcb_ಕಿಟಕಿ_t ಕಿಟಕಿ;
} VkIcdSurfaceXcb;
#ಆದರೆ_ಅಂತ್ಯ  // VK_USE_PLATFORM_XCB_KHR

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_USE_PLATFORM_XLIB_KHR
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ {
    Vk_Icd_Surface_ತಳ ತಳ;
    Display *dpy;
    ಕಿಟಕಿ_2 ಕಿಟಕಿ;
} VkIcdSurfaceXlib;
#ಆದರೆ_ಅಂತ್ಯ  // VK_USE_PLATFORM_XLIB_KHR

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_USE_PLATFORM_DIRECTFB_EXT
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ {
    Vk_Icd_Surface_ತಳ ತಳ;
    IDirectFB *dfb;
    IDirectFBSurface *surface;
} Vk_Icd_Surface_ನೇರ_FB;
#ಆದರೆ_ಅಂತ್ಯ  // VK_USE_PLATFORM_DIRECTFB_EXT

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_USE_PLATFORM_ANDROID_KHR
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ {
    Vk_Icd_Surface_ತಳ ತಳ;
    ರಚನೆ ANative_ಕಿಟಕಿ *ಕಿಟಕಿ;
} VkIcdSurfaceAndroid;
#ಆದರೆ_ಅಂತ್ಯ  // VK_USE_PLATFORM_ANDROID_KHR

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_USE_PLATFORM_MACOS_MVK
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ {
    Vk_Icd_Surface_ತಳ ತಳ;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *pView;
} VkIcdSurfaceMacOS;
#ಆದರೆ_ಅಂತ್ಯ  // VK_USE_PLATFORM_MACOS_MVK

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_USE_PLATFORM_IOS_MVK
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ {
    Vk_Icd_Surface_ತಳ ತಳ;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *pView;
} VkIcdSurfaceIOS;
#ಆದರೆ_ಅಂತ್ಯ  // VK_USE_PLATFORM_IOS_MVK

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_USE_PLATFORM_GGP
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ {
    Vk_Icd_Surface_ತಳ ತಳ;
    Ggp_ಹರಿವು_Descriptor ಹರಿವು_Descriptor;
} VkIcdSurfaceGgp;
#ಆದರೆ_ಅಂತ್ಯ  // VK_USE_PLATFORM_GGP

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ {
    Vk_Icd_Surface_ತಳ ತಳ;
    Vk_Display_ಬಹುಲಕ_KHR display_ಬಹುಲಕ;
    uint32_t plane_ಸೂಚ್ಯಂಕ;
    uint32_t plane_ರಾಶಿ_ಸೂಚ್ಯಂಕ;
    Vk_Surface_Transform_Flag_ಬಿಟ್ಟುಗಳು_KHR transform;
    ದಶಮಾಂಶ globalAlpha;
    Vk_Display_Plane_Alpha_Flag_ಬಿಟ್ಟುಗಳು_KHR alpha_ಬಹುಲಕ;
    VkExtent2D imageExtent;
} VkIcdSurfaceDisplay;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ {
    Vk_Icd_Surface_ತಳ ತಳ;
} VkIcdSurfaceHeadless;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_USE_PLATFORM_METAL_EXT
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ {
    Vk_Icd_Surface_ತಳ ತಳ;
    ಸ್ಥಿರಾಂಕ CAMetalLayer *pLayer;
} VkIcdSurfaceMetal;
#ಆದರೆ_ಅಂತ್ಯ // VK_USE_PLATFORM_METAL_EXT

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_USE_PLATFORM_VI_NN
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ {
    Vk_Icd_Surface_ತಳ ತಳ;
    ಶೂನ್ಯ *ಕಿಟಕಿ;
} VkIcdSurfaceVi;
#ಆದರೆ_ಅಂತ್ಯ // VK_USE_PLATFORM_VI_NN

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_USE_PLATFORM_SCREEN_QNX
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ {
    Vk_Icd_Surface_ತಳ ತಳ;
    ರಚನೆ _screen_context *context;
    ರಚನೆ screen_ಕಿಟಕಿ *ಕಿಟಕಿ;
} VkIcdSurfaceScreen;
#ಆದರೆ_ಅಂತ್ಯ  // VK_USE_PLATFORM_SCREEN_QNX

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_USE_PLATFORM_FUCHSIA
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ {
  Vk_Icd_Surface_ತಳ ತಳ;
} VkIcdSurfaceImagePipe;
#ಆದರೆ_ಅಂತ್ಯ // VK_USE_PLATFORM_FUCHSIA
