/*
 * Copyright 2015-2023 The Khronos Group Inc.
 * Copyright 2015-2023 Valve Corporation
 * Copyright 2015-2023 LunarG, Inc.
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 */
#निर्देशः once

#अन्तर्भाव "vulkan.h"
#अन्तर्भाव <stdbool.h>

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

#परिभाषय CURRENT_LOADER_ICD_INTERFACE_संस्करणम् 7
#परिभाषय MIN_SUPPORTED_LOADER_ICD_INTERFACE_संस्करणम् 0
#परिभाषय MIN_PHYS_DEV_EXTENSION_ICD_INTERFACE_संस्करणम् 4

// Old typedefs that don't follow a proper naming convention but are preserved for compatibility
प्रकारनिर्देश Vk_परिणाम(VKAPI_PTR *PFN_vk_Negotiate_Loader_ICDInterface_संस्करणम्)(uint32_t *p_संस्करणम्);
// This is defined in vk_layer.h which will be found by the loader, but if an ICD is building against this
// file directly, it won't be found.
#यदि_अपरिभाषितम् IS_DEFINED_PFN_GetPhysicalDeviceProcAddr
प्रकारनिर्देश PFN_vkVoidFunction(VKAPI_PTR *PFN_GetPhysicalDeviceProcAddr)(VkInstance instance, ध्रुव वर्ण *pName);
#परिभाषय IS_DEFINED_PFN_GetPhysicalDeviceProcAddr
#यदि_अन्तः

// Typedefs for loader/ICD interface
प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vk_icd_Negotiate_Loader_ICDInterface_संस्करणम्)(uint32_t* p_संस्करणम्);
प्रकारनिर्देश PFN_vkVoidFunction (VKAPI_PTR *PFN_vk_icdGetInstanceProcAddr)(VkInstance instance, ध्रुव वर्ण* pName);
प्रकारनिर्देश PFN_vkVoidFunction (VKAPI_PTR *PFN_vk_icdGetPhysicalDeviceProcAddr)(VkInstance instance, ध्रुव वर्ण* pName);
#यदि defined(VK_USE_PLATFORM_WIN32_KHR)
प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vk_icdEnumerateAdapterPhysicalDevices)(VkInstance instance, LUID adapterLUID,
    uint32_t* p_Physical_Device_गणनम्, VkPhysicalDevice* pPhysicalDevices);
#यदि_अन्तः

// Prototypes for loader/ICD interface
#यदि !defined(VK_NO_PROTOTYPES)
#यदि_परिभाषितम् __cplusplus
बाह्य "C" {
#यदि_अन्तः
    VKAPI_ATTR Vk_परिणाम VKAPI_CALL vk_icd_Negotiate_Loader_ICDInterface_संस्करणम्(uint32_t* p_संस्करणम्);
    VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vk_icdGetInstanceProcAddr(VkInstance instance, ध्रुव वर्ण* pName);
    VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vk_icdGetPhysicalDeviceProcAddr(VkInstance instance, ध्रुव वर्ण* pName);
#यदि defined(VK_USE_PLATFORM_WIN32_KHR)
    VKAPI_ATTR Vk_परिणाम VKAPI_CALL vk_icdEnumerateAdapterPhysicalDevices(VkInstance instance, LUID adapterLUID,
        uint32_t* p_Physical_Device_गणनम्, VkPhysicalDevice* pPhysicalDevices);
#यदि_अन्तः
#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः
#यदि_अन्तः

/*
 * The ICD must reserve space for a pointer for the loader's dispatch
 * table, at the start of <each object>.
 * The ICD must initialize this variable using the SET_LOADER_MAGIC_VALUE macro.
 */

#परिभाषय ICD_LOADER_MAGIC 0x01CDC0DE

प्रकारनिर्देश सङ्घ {
    uintptr_t loaderMagic;
    शून्य *loader_दत्त;
} VK_LOADER_दत्त;

स्थिर अन्तःस्थ शून्य समुच्चयः_loader_magic_मानम्(शून्य *pNewObject) {
    VK_LOADER_दत्त *loader_info = (VK_LOADER_दत्त *)pNewObject;
    loader_info->loaderMagic = ICD_LOADER_MAGIC;
}

स्थिर अन्तःस्थ bool valid_loader_magic_मानम्(शून्य *pNewObject) {
    ध्रुव VK_LOADER_दत्त *loader_info = (VK_LOADER_दत्त *)pNewObject;
    प्रत्यागम (loader_info->loaderMagic & 0xffffffff) == ICD_LOADER_MAGIC;
}

/*
 * Windows and Linux ICDs will treat VkSurfaceKHR as a pointer to a struct that
 * contains the platform-specific connection and surface information.
 */
प्रकारनिर्देश गणना {
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

प्रकारनिर्देश संरचना {
    VkIcdWsiPlatform platform;
} Vk_Icd_Surface_आधारः;

#यदि_परिभाषितम् VK_USE_PLATFORM_MIR_KHR
प्रकारनिर्देश संरचना {
    Vk_Icd_Surface_आधारः आधारः;
    MirConnection *connection;
    MirSurface *mirSurface;
} VkIcdSurfaceMir;
#यदि_अन्तः  // VK_USE_PLATFORM_MIR_KHR

#यदि_परिभाषितम् VK_USE_PLATFORM_WAYLAND_KHR
प्रकारनिर्देश संरचना {
    Vk_Icd_Surface_आधारः आधारः;
    संरचना wl_display *display;
    संरचना wl_surface *surface;
} VkIcdSurfaceWayland;
#यदि_अन्तः  // VK_USE_PLATFORM_WAYLAND_KHR

#यदि_परिभाषितम् VK_USE_PLATFORM_WIN32_KHR
प्रकारनिर्देश संरचना {
    Vk_Icd_Surface_आधारः आधारः;
    HINSTANCE hinstance;
    HWND hwnd;
} VkIcdSurfaceWin32;
#यदि_अन्तः  // VK_USE_PLATFORM_WIN32_KHR

#यदि_परिभाषितम् VK_USE_PLATFORM_XCB_KHR
प्रकारनिर्देश संरचना {
    Vk_Icd_Surface_आधारः आधारः;
    xcb_connection_t *connection;
    xcb_गवाक्षः_t गवाक्षः;
} VkIcdSurfaceXcb;
#यदि_अन्तः  // VK_USE_PLATFORM_XCB_KHR

#यदि_परिभाषितम् VK_USE_PLATFORM_XLIB_KHR
प्रकारनिर्देश संरचना {
    Vk_Icd_Surface_आधारः आधारः;
    Display *dpy;
    गवाक्षः_2 गवाक्षः;
} VkIcdSurfaceXlib;
#यदि_अन्तः  // VK_USE_PLATFORM_XLIB_KHR

#यदि_परिभाषितम् VK_USE_PLATFORM_DIRECTFB_EXT
प्रकारनिर्देश संरचना {
    Vk_Icd_Surface_आधारः आधारः;
    IDirectFB *dfb;
    IDirectFBSurface *surface;
} Vk_Icd_Surface_प्रत्यक्षम्_FB;
#यदि_अन्तः  // VK_USE_PLATFORM_DIRECTFB_EXT

#यदि_परिभाषितम् VK_USE_PLATFORM_ANDROID_KHR
प्रकारनिर्देश संरचना {
    Vk_Icd_Surface_आधारः आधारः;
    संरचना ANative_गवाक्षः *गवाक्षः;
} VkIcdSurfaceAndroid;
#यदि_अन्तः  // VK_USE_PLATFORM_ANDROID_KHR

#यदि_परिभाषितम् VK_USE_PLATFORM_MACOS_MVK
प्रकारनिर्देश संरचना {
    Vk_Icd_Surface_आधारः आधारः;
    ध्रुव शून्य *pView;
} VkIcdSurfaceMacOS;
#यदि_अन्तः  // VK_USE_PLATFORM_MACOS_MVK

#यदि_परिभाषितम् VK_USE_PLATFORM_IOS_MVK
प्रकारनिर्देश संरचना {
    Vk_Icd_Surface_आधारः आधारः;
    ध्रुव शून्य *pView;
} VkIcdSurfaceIOS;
#यदि_अन्तः  // VK_USE_PLATFORM_IOS_MVK

#यदि_परिभाषितम् VK_USE_PLATFORM_GGP
प्रकारनिर्देश संरचना {
    Vk_Icd_Surface_आधारः आधारः;
    Ggp_प्रवाहः_Descriptor प्रवाहः_Descriptor;
} VkIcdSurfaceGgp;
#यदि_अन्तः  // VK_USE_PLATFORM_GGP

प्रकारनिर्देश संरचना {
    Vk_Icd_Surface_आधारः आधारः;
    Vk_Display_बहुलकम्_KHR display_बहुलकम्;
    uint32_t plane_सूचकांक;
    uint32_t plane_राशिः_सूचकांक;
    Vk_Surface_Transform_Flag_द्वयङ्काः_KHR transform;
    भिन्न globalAlpha;
    Vk_Display_Plane_Alpha_Flag_द्वयङ्काः_KHR alpha_बहुलकम्;
    VkExtent2D imageExtent;
} VkIcdSurfaceDisplay;

प्रकारनिर्देश संरचना {
    Vk_Icd_Surface_आधारः आधारः;
} VkIcdSurfaceHeadless;

#यदि_परिभाषितम् VK_USE_PLATFORM_METAL_EXT
प्रकारनिर्देश संरचना {
    Vk_Icd_Surface_आधारः आधारः;
    ध्रुव CAMetalLayer *pLayer;
} VkIcdSurfaceMetal;
#यदि_अन्तः // VK_USE_PLATFORM_METAL_EXT

#यदि_परिभाषितम् VK_USE_PLATFORM_VI_NN
प्रकारनिर्देश संरचना {
    Vk_Icd_Surface_आधारः आधारः;
    शून्य *गवाक्षः;
} VkIcdSurfaceVi;
#यदि_अन्तः // VK_USE_PLATFORM_VI_NN

#यदि_परिभाषितम् VK_USE_PLATFORM_SCREEN_QNX
प्रकारनिर्देश संरचना {
    Vk_Icd_Surface_आधारः आधारः;
    संरचना _screen_context *context;
    संरचना screen_गवाक्षः *गवाक्षः;
} VkIcdSurfaceScreen;
#यदि_अन्तः  // VK_USE_PLATFORM_SCREEN_QNX

#यदि_परिभाषितम् VK_USE_PLATFORM_FUCHSIA
प्रकारनिर्देश संरचना {
  Vk_Icd_Surface_आधारः आधारः;
} VkIcdSurfaceImagePipe;
#यदि_अन्तः // VK_USE_PLATFORM_FUCHSIA
