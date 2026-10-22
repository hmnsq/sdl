#ifndef VULKAN_H_
#define VULKAN_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

#ಅನ್ತರ್ಭಾವ "vk_platform.h"
#ಅನ್ತರ್ಭಾವ "vulkan_core.h"

#ifdef VK_USE_PLATFORM_ANDROID_KHR
#ಅನ್ತರ್ಭಾವ "vulkan_android.h"
#endif

#ifdef VK_USE_PLATFORM_FUCHSIA
#ಅನ್ತರ್ಭಾವ <zircon/types.h>
#ಅನ್ತರ್ಭಾವ "vulkan_fuchsia.h"
#endif

#ifdef VK_USE_PLATFORM_IOS_MVK
#ಅನ್ತರ್ಭಾವ "vulkan_ios.h"
#endif


#ifdef VK_USE_PLATFORM_MACOS_MVK
#ಅನ್ತರ್ಭಾವ "vulkan_macos.h"
#endif

#ifdef VK_USE_PLATFORM_METAL_EXT
#ಅನ್ತರ್ಭಾವ "vulkan_metal.h"
#endif

#ifdef VK_USE_PLATFORM_VI_NN
#ಅನ್ತರ್ಭಾವ "vulkan_vi.h"
#endif

#ifdef VK_USE_PLATFORM_UBM_SEC
#ಅನ್ತರ್ಭಾವ "vulkan_ubm.h"
#endif

#ifdef VK_USE_PLATFORM_WAYLAND_KHR
#ಅನ್ತರ್ಭಾವ "vulkan_wayland.h"
#endif


#ifdef VK_USE_PLATFORM_WIN32_KHR
#ಅನ್ತರ್ಭಾವ <windows.h>
#ಅನ್ತರ್ಭಾವ "vulkan_win32.h"
#endif


#ifdef VK_USE_PLATFORM_XCB_KHR
#ಅನ್ತರ್ಭಾವ <xcb/xcb.h>
#ಅನ್ತರ್ಭಾವ "vulkan_xcb.h"
#endif


#ifdef VK_USE_PLATFORM_XLIB_KHR
#ಅನ್ತರ್ಭಾವ <X11/Xlib.h>
#ಅನ್ತರ್ಭಾವ "vulkan_xlib.h"
#endif


#ifdef VK_USE_PLATFORM_DIRECTFB_EXT
#ಅನ್ತರ್ಭಾವ <directfb.h>
#ಅನ್ತರ್ಭಾವ "vulkan_directfb.h"
#endif


#ifdef VK_USE_PLATFORM_XLIB_XRANDR_EXT
#ಅನ್ತರ್ಭಾವ <X11/Xlib.h>
#ಅನ್ತರ್ಭಾವ <X11/extensions/Xrandr.h>
#ಅನ್ತರ್ಭಾವ "vulkan_xlib_xrandr.h"
#endif


#ifdef VK_USE_PLATFORM_GGP
#ಅನ್ತರ್ಭಾವ <ggp_c/vulkan_types.h>
#ಅನ್ತರ್ಭಾವ "vulkan_ggp.h"
#endif


#ifdef VK_USE_PLATFORM_SCREEN_QNX
#ಅನ್ತರ್ಭಾವ <screen/screen.h>
#ಅನ್ತರ್ಭಾವ "vulkan_screen.h"
#endif


#ifdef VK_USE_PLATFORM_SCI
#ಅನ್ತರ್ಭಾವ <nvscisync.h>
#ಅನ್ತರ್ಭಾವ <nvscibuf.h>
#ಅನ್ತರ್ಭಾವ "vulkan_sci.h"
#endif


#ifdef VK_USE_PLATFORM_OHOS
#ಅನ್ತರ್ಭಾವ "vulkan_ohos.h"
#endif

/* vulkan_beta.h should go last in the event any beta extension interactions
 * with platform extensions exist.
 */
#ifdef VK_ENABLE_BETA_EXTENSIONS
#ಅನ್ತರ್ಭಾವ "vulkan_beta.h"
#endif

#endif // VULKAN_H_
