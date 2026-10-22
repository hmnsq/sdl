/*
 * Copyright 2015-2023 The Khronos Group Inc.
 * Copyright 2015-2023 Valve Corporation
 * Copyright 2015-2023 LunarG, Inc.
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 */
#సూచన once

#అన్తర్భావ "vulkan.h"
#అన్తర్భావ <stdbool.h>

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

#నిర్వచించు CURRENT_LOADER_ICD_INTERFACE_సంస్కరణ 7
#నిర్వచించు MIN_SUPPORTED_LOADER_ICD_INTERFACE_సంస్కరణ 0
#నిర్వచించు MIN_PHYS_DEV_EXTENSION_ICD_INTERFACE_సంస్కరణ 4

// Old typedefs that don't follow a proper naming convention but are preserved for compatibility
రకనిర్వచనం Vk_ఫలితం(VKAPI_PTR *PFN_vk_Negotiate_Loader_ICDInterface_సంస్కరణ)(uint32_t *p_సంస్కరణ);
// This is defined in vk_layer.h which will be found by the loader, but if an ICD is building against this
// file directly, it won't be found.
#నిర్వచితం_కాకపోతే IS_DEFINED_PFN_GetPhysicalDeviceProcAddr
రకనిర్వచనం PFN_vkVoidFunction(VKAPI_PTR *PFN_GetPhysicalDeviceProcAddr)(VkInstance instance, స్థిరరాశి అక్షరం *pName);
#నిర్వచించు IS_DEFINED_PFN_GetPhysicalDeviceProcAddr
#అయితే_ముగింపు

// Typedefs for loader/ICD interface
రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vk_icd_Negotiate_Loader_ICDInterface_సంస్కరణ)(uint32_t* p_సంస్కరణ);
రకనిర్వచనం PFN_vkVoidFunction (VKAPI_PTR *PFN_vk_icdGetInstanceProcAddr)(VkInstance instance, స్థిరరాశి అక్షరం* pName);
రకనిర్వచనం PFN_vkVoidFunction (VKAPI_PTR *PFN_vk_icdGetPhysicalDeviceProcAddr)(VkInstance instance, స్థిరరాశి అక్షరం* pName);
#ఒకవేళ defined(VK_USE_PLATFORM_WIN32_KHR)
రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vk_icdEnumerateAdapterPhysicalDevices)(VkInstance instance, LUID adapterLUID,
    uint32_t* p_Physical_Device_లెక్క, VkPhysicalDevice* pPhysicalDevices);
#అయితే_ముగింపు

// Prototypes for loader/ICD interface
#ఒకవేళ !defined(VK_NO_PROTOTYPES)
#నిర్వచితమైతే __cplusplus
బాహ్య "C" {
#అయితే_ముగింపు
    VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vk_icd_Negotiate_Loader_ICDInterface_సంస్కరణ(uint32_t* p_సంస్కరణ);
    VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vk_icdGetInstanceProcAddr(VkInstance instance, స్థిరరాశి అక్షరం* pName);
    VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vk_icdGetPhysicalDeviceProcAddr(VkInstance instance, స్థిరరాశి అక్షరం* pName);
#ఒకవేళ defined(VK_USE_PLATFORM_WIN32_KHR)
    VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vk_icdEnumerateAdapterPhysicalDevices(VkInstance instance, LUID adapterLUID,
        uint32_t* p_Physical_Device_లెక్క, VkPhysicalDevice* pPhysicalDevices);
#అయితే_ముగింపు
#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు
#అయితే_ముగింపు

/*
 * The ICD must reserve space for a pointer for the loader's dispatch
 * table, at the start of <each object>.
 * The ICD must initialize this variable using the SET_LOADER_MAGIC_VALUE macro.
 */

#నిర్వచించు ICD_LOADER_MAGIC 0x01CDC0DE

రకనిర్వచనం సంఘం {
    uintptr_t loaderMagic;
    శూన్య *loader_దత్తాంశం;
} VK_LOADER_దత్తాంశం;

స్థిర అంతఃవరుస శూన్య సమితి_loader_magic_విలువ(శూన్య *pNewObject) {
    VK_LOADER_దత్తాంశం *loader_info = (VK_LOADER_దత్తాంశం *)pNewObject;
    loader_info->loaderMagic = ICD_LOADER_MAGIC;
}

స్థిర అంతఃవరుస bool valid_loader_magic_విలువ(శూన్య *pNewObject) {
    స్థిరరాశి VK_LOADER_దత్తాంశం *loader_info = (VK_LOADER_దత్తాంశం *)pNewObject;
    తిరిగి (loader_info->loaderMagic & 0xffffffff) == ICD_LOADER_MAGIC;
}

/*
 * Windows and Linux ICDs will treat VkSurfaceKHR as a pointer to a struct that
 * contains the platform-specific connection and surface information.
 */
రకనిర్వచనం గణన {
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

రకనిర్వచనం నిర్మాణం {
    VkIcdWsiPlatform platform;
} Vk_Icd_Surface_పునాది;

#నిర్వచితమైతే VK_USE_PLATFORM_MIR_KHR
రకనిర్వచనం నిర్మాణం {
    Vk_Icd_Surface_పునాది పునాది;
    MirConnection *connection;
    MirSurface *mirSurface;
} VkIcdSurfaceMir;
#అయితే_ముగింపు  // VK_USE_PLATFORM_MIR_KHR

#నిర్వచితమైతే VK_USE_PLATFORM_WAYLAND_KHR
రకనిర్వచనం నిర్మాణం {
    Vk_Icd_Surface_పునాది పునాది;
    నిర్మాణం wl_display *display;
    నిర్మాణం wl_surface *surface;
} VkIcdSurfaceWayland;
#అయితే_ముగింపు  // VK_USE_PLATFORM_WAYLAND_KHR

#నిర్వచితమైతే VK_USE_PLATFORM_WIN32_KHR
రకనిర్వచనం నిర్మాణం {
    Vk_Icd_Surface_పునాది పునాది;
    HINSTANCE hinstance;
    HWND hwnd;
} VkIcdSurfaceWin32;
#అయితే_ముగింపు  // VK_USE_PLATFORM_WIN32_KHR

#నిర్వచితమైతే VK_USE_PLATFORM_XCB_KHR
రకనిర్వచనం నిర్మాణం {
    Vk_Icd_Surface_పునాది పునాది;
    xcb_connection_t *connection;
    xcb_కిటికీ_t కిటికీ;
} VkIcdSurfaceXcb;
#అయితే_ముగింపు  // VK_USE_PLATFORM_XCB_KHR

#నిర్వచితమైతే VK_USE_PLATFORM_XLIB_KHR
రకనిర్వచనం నిర్మాణం {
    Vk_Icd_Surface_పునాది పునాది;
    Display *dpy;
    కిటికీ_2 కిటికీ;
} VkIcdSurfaceXlib;
#అయితే_ముగింపు  // VK_USE_PLATFORM_XLIB_KHR

#నిర్వచితమైతే VK_USE_PLATFORM_DIRECTFB_EXT
రకనిర్వచనం నిర్మాణం {
    Vk_Icd_Surface_పునాది పునాది;
    IDirectFB *dfb;
    IDirectFBSurface *surface;
} Vk_Icd_Surface_ప్రత్యక్ష_FB;
#అయితే_ముగింపు  // VK_USE_PLATFORM_DIRECTFB_EXT

#నిర్వచితమైతే VK_USE_PLATFORM_ANDROID_KHR
రకనిర్వచనం నిర్మాణం {
    Vk_Icd_Surface_పునాది పునాది;
    నిర్మాణం ANative_కిటికీ *కిటికీ;
} VkIcdSurfaceAndroid;
#అయితే_ముగింపు  // VK_USE_PLATFORM_ANDROID_KHR

#నిర్వచితమైతే VK_USE_PLATFORM_MACOS_MVK
రకనిర్వచనం నిర్మాణం {
    Vk_Icd_Surface_పునాది పునాది;
    స్థిరరాశి శూన్య *pView;
} VkIcdSurfaceMacOS;
#అయితే_ముగింపు  // VK_USE_PLATFORM_MACOS_MVK

#నిర్వచితమైతే VK_USE_PLATFORM_IOS_MVK
రకనిర్వచనం నిర్మాణం {
    Vk_Icd_Surface_పునాది పునాది;
    స్థిరరాశి శూన్య *pView;
} VkIcdSurfaceIOS;
#అయితే_ముగింపు  // VK_USE_PLATFORM_IOS_MVK

#నిర్వచితమైతే VK_USE_PLATFORM_GGP
రకనిర్వచనం నిర్మాణం {
    Vk_Icd_Surface_పునాది పునాది;
    Ggp_ప్రవాహం_Descriptor ప్రవాహం_Descriptor;
} VkIcdSurfaceGgp;
#అయితే_ముగింపు  // VK_USE_PLATFORM_GGP

రకనిర్వచనం నిర్మాణం {
    Vk_Icd_Surface_పునాది పునాది;
    Vk_Display_బహుళకం_KHR display_బహుళకం;
    uint32_t plane_సూచీ;
    uint32_t plane_దొంతర_సూచీ;
    Vk_Surface_Transform_Flag_బిట్లు_KHR transform;
    దశాంశం globalAlpha;
    Vk_Display_Plane_Alpha_Flag_బిట్లు_KHR alpha_బహుళకం;
    VkExtent2D imageExtent;
} VkIcdSurfaceDisplay;

రకనిర్వచనం నిర్మాణం {
    Vk_Icd_Surface_పునాది పునాది;
} VkIcdSurfaceHeadless;

#నిర్వచితమైతే VK_USE_PLATFORM_METAL_EXT
రకనిర్వచనం నిర్మాణం {
    Vk_Icd_Surface_పునాది పునాది;
    స్థిరరాశి CAMetalLayer *pLayer;
} VkIcdSurfaceMetal;
#అయితే_ముగింపు // VK_USE_PLATFORM_METAL_EXT

#నిర్వచితమైతే VK_USE_PLATFORM_VI_NN
రకనిర్వచనం నిర్మాణం {
    Vk_Icd_Surface_పునాది పునాది;
    శూన్య *కిటికీ;
} VkIcdSurfaceVi;
#అయితే_ముగింపు // VK_USE_PLATFORM_VI_NN

#నిర్వచితమైతే VK_USE_PLATFORM_SCREEN_QNX
రకనిర్వచనం నిర్మాణం {
    Vk_Icd_Surface_పునాది పునాది;
    నిర్మాణం _screen_context *context;
    నిర్మాణం screen_కిటికీ *కిటికీ;
} VkIcdSurfaceScreen;
#అయితే_ముగింపు  // VK_USE_PLATFORM_SCREEN_QNX

#నిర్వచితమైతే VK_USE_PLATFORM_FUCHSIA
రకనిర్వచనం నిర్మాణం {
  Vk_Icd_Surface_పునాది పునాది;
} VkIcdSurfaceImagePipe;
#అయితే_ముగింపు // VK_USE_PLATFORM_FUCHSIA
