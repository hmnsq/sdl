#ifndef VULKAN_H_
#define VULKAN_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

#અન્તર્ભાવ "vk_platform.h"
#અન્તર્ભાવ "vulkan_core.h"

#ifdef VK_USE_PLATFORM_ANDROID_KHR
#અન્તર્ભાવ "vulkan_android.h"
#endif

#ifdef VK_USE_PLATFORM_FUCHSIA
#અન્તર્ભાવ <zircon/types.h>
#અન્તર્ભાવ "vulkan_fuchsia.h"
#endif

#ifdef VK_USE_PLATFORM_IOS_MVK
#અન્તર્ભાવ "vulkan_ios.h"
#endif


#ifdef VK_USE_PLATFORM_MACOS_MVK
#અન્તર્ભાવ "vulkan_macos.h"
#endif

#ifdef VK_USE_PLATFORM_METAL_EXT
#અન્તર્ભાવ "vulkan_metal.h"
#endif

#ifdef VK_USE_PLATFORM_VI_NN
#અન્તર્ભાવ "vulkan_vi.h"
#endif

#ifdef VK_USE_PLATFORM_UBM_SEC
#અન્તર્ભાવ "vulkan_ubm.h"
#endif

#ifdef VK_USE_PLATFORM_WAYLAND_KHR
#અન્તર્ભાવ "vulkan_wayland.h"
#endif


#ifdef VK_USE_PLATFORM_WIN32_KHR
#અન્તર્ભાવ <windows.h>
#અન્તર્ભાવ "vulkan_win32.h"
#endif


#ifdef VK_USE_PLATFORM_XCB_KHR
#અન્તર્ભાવ <xcb/xcb.h>
#અન્તર્ભાવ "vulkan_xcb.h"
#endif


#ifdef VK_USE_PLATFORM_XLIB_KHR
#અન્તર્ભાવ <X11/Xlib.h>
#અન્તર્ભાવ "vulkan_xlib.h"
#endif


#ifdef VK_USE_PLATFORM_DIRECTFB_EXT
#અન્તર્ભાવ <directfb.h>
#અન્તર્ભાવ "vulkan_directfb.h"
#endif


#ifdef VK_USE_PLATFORM_XLIB_XRANDR_EXT
#અન્તર્ભાવ <X11/Xlib.h>
#અન્તર્ભાવ <X11/extensions/Xrandr.h>
#અન્તર્ભાવ "vulkan_xlib_xrandr.h"
#endif


#ifdef VK_USE_PLATFORM_GGP
#અન્તર્ભાવ <ggp_c/vulkan_types.h>
#અન્તર્ભાવ "vulkan_ggp.h"
#endif


#ifdef VK_USE_PLATFORM_SCREEN_QNX
#અન્તર્ભાવ <screen/screen.h>
#અન્તર્ભાવ "vulkan_screen.h"
#endif


#ifdef VK_USE_PLATFORM_SCI
#અન્તર્ભાવ <nvscisync.h>
#અન્તર્ભાવ <nvscibuf.h>
#અન્તર્ભાવ "vulkan_sci.h"
#endif


#ifdef VK_USE_PLATFORM_OHOS
#અન્તર્ભાવ "vulkan_ohos.h"
#endif

/* vulkan_beta.h should go last in the event any beta extension interactions
 * with platform extensions exist.
 */
#ifdef VK_ENABLE_BETA_EXTENSIONS
#અન્તર્ભાવ "vulkan_beta.h"
#endif

#endif // VULKAN_H_
