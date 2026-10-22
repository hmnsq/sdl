#ifndef VULKAN_H_
#define VULKAN_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

#شامل "vk_platform.h"
#شامل "vulkan_core.h"

#ifdef VK_USE_PLATFORM_ANDROID_KHR
#شامل "vulkan_android.h"
#endif

#ifdef VK_USE_PLATFORM_FUCHSIA
#شامل <zircon/types.h>
#شامل "vulkan_fuchsia.h"
#endif

#ifdef VK_USE_PLATFORM_IOS_MVK
#شامل "vulkan_ios.h"
#endif


#ifdef VK_USE_PLATFORM_MACOS_MVK
#شامل "vulkan_macos.h"
#endif

#ifdef VK_USE_PLATFORM_METAL_EXT
#شامل "vulkan_metal.h"
#endif

#ifdef VK_USE_PLATFORM_VI_NN
#شامل "vulkan_vi.h"
#endif

#ifdef VK_USE_PLATFORM_UBM_SEC
#شامل "vulkan_ubm.h"
#endif

#ifdef VK_USE_PLATFORM_WAYLAND_KHR
#شامل "vulkan_wayland.h"
#endif


#ifdef VK_USE_PLATFORM_WIN32_KHR
#شامل <windows.h>
#شامل "vulkan_win32.h"
#endif


#ifdef VK_USE_PLATFORM_XCB_KHR
#شامل <xcb/xcb.h>
#شامل "vulkan_xcb.h"
#endif


#ifdef VK_USE_PLATFORM_XLIB_KHR
#شامل <X11/Xlib.h>
#شامل "vulkan_xlib.h"
#endif


#ifdef VK_USE_PLATFORM_DIRECTFB_EXT
#شامل <directfb.h>
#شامل "vulkan_directfb.h"
#endif


#ifdef VK_USE_PLATFORM_XLIB_XRANDR_EXT
#شامل <X11/Xlib.h>
#شامل <X11/extensions/Xrandr.h>
#شامل "vulkan_xlib_xrandr.h"
#endif


#ifdef VK_USE_PLATFORM_GGP
#شامل <ggp_c/vulkan_types.h>
#شامل "vulkan_ggp.h"
#endif


#ifdef VK_USE_PLATFORM_SCREEN_QNX
#شامل <screen/screen.h>
#شامل "vulkan_screen.h"
#endif


#ifdef VK_USE_PLATFORM_SCI
#شامل <nvscisync.h>
#شامل <nvscibuf.h>
#شامل "vulkan_sci.h"
#endif


#ifdef VK_USE_PLATFORM_OHOS
#شامل "vulkan_ohos.h"
#endif

/* vulkan_beta.h should go last in the event any beta extension interactions
 * with platform extensions exist.
 */
#ifdef VK_ENABLE_BETA_EXTENSIONS
#شامل "vulkan_beta.h"
#endif

#endif // VULKAN_H_
