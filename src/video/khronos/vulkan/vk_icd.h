/*
 * Copyright 2015-2023 The Khronos Group Inc.
 * Copyright 2015-2023 Valve Corporation
 * Copyright 2015-2023 LunarG, Inc.
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 */
#आशय once

#समावेश "vulkan.h"
#समावेश <stdbool.h>

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

#घोषणा CURRENT_LOADER_ICD_INTERFACE_VERSION 7
#घोषणा MIN_SUPPORTED_LOADER_ICD_INTERFACE_VERSION 0
#घोषणा MIN_PHYS_DEV_EXTENSION_ICD_INTERFACE_VERSION 4

// Old typedefs that don't follow a proper naming convention but are preserved for compatibility
प्रकार Vk_परिणाम(VKAPI_PTR *PFN_vkNegotiateLoaderICDInterfaceVersion)(uint32_t *pVersion);
// This is defined in vk_layer.h which will be found by the loader, but if an ICD is building against this
// file directly, it won't be found.
#अगर_अघोषित IS_DEFINED_PFN_GetPhysicalDeviceProcAddr
प्रकार PFN_vkVoidFunction(VKAPI_PTR *PFN_GetPhysicalDeviceProcAddr)(VkInstance instance, स्थिर अक्षर *pName);
#घोषणा IS_DEFINED_PFN_GetPhysicalDeviceProcAddr
#पूर्ण_अगर

// Typedefs for loader/ICD interface
प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vk_icdNegotiateLoaderICDInterfaceVersion)(uint32_t* pVersion);
प्रकार PFN_vkVoidFunction (VKAPI_PTR *PFN_vk_icdGetInstanceProcAddr)(VkInstance instance, स्थिर अक्षर* pName);
प्रकार PFN_vkVoidFunction (VKAPI_PTR *PFN_vk_icdGetPhysicalDeviceProcAddr)(VkInstance instance, स्थिर अक्षर* pName);
#अगर defined(VK_USE_PLATFORM_WIN32_KHR)
प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vk_icdEnumerateAdapterPhysicalDevices)(VkInstance instance, LUID adapterLUID,
    uint32_t* p_Physical_Device_गिनती, VkPhysicalDevice* pPhysicalDevices);
#पूर्ण_अगर

// Prototypes for loader/ICD interface
#अगर !defined(VK_NO_PROTOTYPES)
#अगर_घोषित __cplusplus
बाह्य "C" {
#पूर्ण_अगर
    VKAPI_ATTR Vk_परिणाम VKAPI_CALL vk_icdNegotiateLoaderICDInterfaceVersion(uint32_t* pVersion);
    VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vk_icdGetInstanceProcAddr(VkInstance instance, स्थिर अक्षर* pName);
    VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vk_icdGetPhysicalDeviceProcAddr(VkInstance instance, स्थिर अक्षर* pName);
#अगर defined(VK_USE_PLATFORM_WIN32_KHR)
    VKAPI_ATTR Vk_परिणाम VKAPI_CALL vk_icdEnumerateAdapterPhysicalDevices(VkInstance instance, LUID adapterLUID,
        uint32_t* p_Physical_Device_गिनती, VkPhysicalDevice* pPhysicalDevices);
#पूर्ण_अगर
#अगर_घोषित __cplusplus
}
#पूर्ण_अगर
#पूर्ण_अगर

/*
 * The ICD must reserve space for a pointer for the loader's dispatch
 * table, at the start of <each object>.
 * The ICD must initialize this variable using the SET_LOADER_MAGIC_VALUE macro.
 */

#घोषणा ICD_LOADER_MAGIC 0x01CDC0DE

प्रकार जोड़ {
    uintptr_t loaderMagic;
    व्योम *loader_तथ्य;
} VK_LOADER_तथ्य;

अटल अंतरभूत व्योम set_loader_magic_मूल्य(व्योम *pNewObject) {
    VK_LOADER_तथ्य *loader_info = (VK_LOADER_तथ्य *)pNewObject;
    loader_info->loaderMagic = ICD_LOADER_MAGIC;
}

अटल अंतरभूत bool valid_loader_magic_मूल्य(व्योम *pNewObject) {
    स्थिर VK_LOADER_तथ्य *loader_info = (VK_LOADER_तथ्य *)pNewObject;
    वापस (loader_info->loaderMagic & 0xffffffff) == ICD_LOADER_MAGIC;
}

/*
 * Windows and Linux ICDs will treat VkSurfaceKHR as a pointer to a struct that
 * contains the platform-specific connection and surface information.
 */
प्रकार क्रमागत {
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

प्रकार काष्ठा {
    VkIcdWsiPlatform platform;
} VkIcdSurfaceBase;

#अगर_घोषित VK_USE_PLATFORM_MIR_KHR
प्रकार काष्ठा {
    VkIcdSurfaceBase base;
    MirConnection *connection;
    MirSurface *mirSurface;
} VkIcdSurfaceMir;
#पूर्ण_अगर  // VK_USE_PLATFORM_MIR_KHR

#अगर_घोषित VK_USE_PLATFORM_WAYLAND_KHR
प्रकार काष्ठा {
    VkIcdSurfaceBase base;
    काष्ठा wl_display *display;
    काष्ठा wl_surface *surface;
} VkIcdSurfaceWayland;
#पूर्ण_अगर  // VK_USE_PLATFORM_WAYLAND_KHR

#अगर_घोषित VK_USE_PLATFORM_WIN32_KHR
प्रकार काष्ठा {
    VkIcdSurfaceBase base;
    HINSTANCE hinstance;
    HWND hwnd;
} VkIcdSurfaceWin32;
#पूर्ण_अगर  // VK_USE_PLATFORM_WIN32_KHR

#अगर_घोषित VK_USE_PLATFORM_XCB_KHR
प्रकार काष्ठा {
    VkIcdSurfaceBase base;
    xcb_connection_t *connection;
    xcb_window_t window;
} VkIcdSurfaceXcb;
#पूर्ण_अगर  // VK_USE_PLATFORM_XCB_KHR

#अगर_घोषित VK_USE_PLATFORM_XLIB_KHR
प्रकार काष्ठा {
    VkIcdSurfaceBase base;
    Display *dpy;
    Window window;
} VkIcdSurfaceXlib;
#पूर्ण_अगर  // VK_USE_PLATFORM_XLIB_KHR

#अगर_घोषित VK_USE_PLATFORM_DIRECTFB_EXT
प्रकार काष्ठा {
    VkIcdSurfaceBase base;
    IDirectFB *dfb;
    IDirectFBSurface *surface;
} VkIcdSurfaceDirectFB;
#पूर्ण_अगर  // VK_USE_PLATFORM_DIRECTFB_EXT

#अगर_घोषित VK_USE_PLATFORM_ANDROID_KHR
प्रकार काष्ठा {
    VkIcdSurfaceBase base;
    काष्ठा ANativeWindow *window;
} VkIcdSurfaceAndroid;
#पूर्ण_अगर  // VK_USE_PLATFORM_ANDROID_KHR

#अगर_घोषित VK_USE_PLATFORM_MACOS_MVK
प्रकार काष्ठा {
    VkIcdSurfaceBase base;
    स्थिर व्योम *pView;
} VkIcdSurfaceMacOS;
#पूर्ण_अगर  // VK_USE_PLATFORM_MACOS_MVK

#अगर_घोषित VK_USE_PLATFORM_IOS_MVK
प्रकार काष्ठा {
    VkIcdSurfaceBase base;
    स्थिर व्योम *pView;
} VkIcdSurfaceIOS;
#पूर्ण_अगर  // VK_USE_PLATFORM_IOS_MVK

#अगर_घोषित VK_USE_PLATFORM_GGP
प्रकार काष्ठा {
    VkIcdSurfaceBase base;
    GgpStreamDescriptor streamDescriptor;
} VkIcdSurfaceGgp;
#पूर्ण_अगर  // VK_USE_PLATFORM_GGP

प्रकार काष्ठा {
    VkIcdSurfaceBase base;
    VkDisplayModeKHR displayMode;
    uint32_t plane_सूचकांक;
    uint32_t plane_ढेर_सूचकांक;
    VkSurfaceTransformFlagBitsKHR transform;
    भग्न globalAlpha;
    VkDisplayPlaneAlphaFlagBitsKHR alphaMode;
    VkExtent2D imageExtent;
} VkIcdSurfaceDisplay;

प्रकार काष्ठा {
    VkIcdSurfaceBase base;
} VkIcdSurfaceHeadless;

#अगर_घोषित VK_USE_PLATFORM_METAL_EXT
प्रकार काष्ठा {
    VkIcdSurfaceBase base;
    स्थिर CAMetalLayer *pLayer;
} VkIcdSurfaceMetal;
#पूर्ण_अगर // VK_USE_PLATFORM_METAL_EXT

#अगर_घोषित VK_USE_PLATFORM_VI_NN
प्रकार काष्ठा {
    VkIcdSurfaceBase base;
    व्योम *window;
} VkIcdSurfaceVi;
#पूर्ण_अगर // VK_USE_PLATFORM_VI_NN

#अगर_घोषित VK_USE_PLATFORM_SCREEN_QNX
प्रकार काष्ठा {
    VkIcdSurfaceBase base;
    काष्ठा _screen_context *context;
    काष्ठा _screen_window *window;
} VkIcdSurfaceScreen;
#पूर्ण_अगर  // VK_USE_PLATFORM_SCREEN_QNX

#अगर_घोषित VK_USE_PLATFORM_FUCHSIA
प्रकार काष्ठा {
  VkIcdSurfaceBase base;
} VkIcdSurfaceImagePipe;
#पूर्ण_अगर // VK_USE_PLATFORM_FUCHSIA
