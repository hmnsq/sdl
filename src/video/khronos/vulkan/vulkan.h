#ifndef VULKAN_H_
#define VULKAN_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

#ଅନ୍ତର୍ଭାଵ "vk_platform.h"
#ଅନ୍ତର୍ଭାଵ "vulkan_core.h"

#ifdef VK_USE_PLATFORM_ANDROID_KHR
#ଅନ୍ତର୍ଭାଵ "vulkan_android.h"
#endif

#ifdef VK_USE_PLATFORM_FUCHSIA
#ଅନ୍ତର୍ଭାଵ <zircon/types.h>
#ଅନ୍ତର୍ଭାଵ "vulkan_fuchsia.h"
#endif

#ifdef VK_USE_PLATFORM_IOS_MVK
#ଅନ୍ତର୍ଭାଵ "vulkan_ios.h"
#endif


#ifdef VK_USE_PLATFORM_MACOS_MVK
#ଅନ୍ତର୍ଭାଵ "vulkan_macos.h"
#endif

#ifdef VK_USE_PLATFORM_METAL_EXT
#ଅନ୍ତର୍ଭାଵ "vulkan_metal.h"
#endif

#ifdef VK_USE_PLATFORM_VI_NN
#ଅନ୍ତର୍ଭାଵ "vulkan_vi.h"
#endif

#ifdef VK_USE_PLATFORM_UBM_SEC
#ଅନ୍ତର୍ଭାଵ "vulkan_ubm.h"
#endif

#ifdef VK_USE_PLATFORM_WAYLAND_KHR
#ଅନ୍ତର୍ଭାଵ "vulkan_wayland.h"
#endif


#ifdef VK_USE_PLATFORM_WIN32_KHR
#ଅନ୍ତର୍ଭାଵ <windows.h>
#ଅନ୍ତର୍ଭାଵ "vulkan_win32.h"
#endif


#ifdef VK_USE_PLATFORM_XCB_KHR
#ଅନ୍ତର୍ଭାଵ <xcb/xcb.h>
#ଅନ୍ତର୍ଭାଵ "vulkan_xcb.h"
#endif


#ifdef VK_USE_PLATFORM_XLIB_KHR
#ଅନ୍ତର୍ଭାଵ <X11/Xlib.h>
#ଅନ୍ତର୍ଭାଵ "vulkan_xlib.h"
#endif


#ifdef VK_USE_PLATFORM_DIRECTFB_EXT
#ଅନ୍ତର୍ଭାଵ <directfb.h>
#ଅନ୍ତର୍ଭାଵ "vulkan_directfb.h"
#endif


#ifdef VK_USE_PLATFORM_XLIB_XRANDR_EXT
#ଅନ୍ତର୍ଭାଵ <X11/Xlib.h>
#ଅନ୍ତର୍ଭାଵ <X11/extensions/Xrandr.h>
#ଅନ୍ତର୍ଭାଵ "vulkan_xlib_xrandr.h"
#endif


#ifdef VK_USE_PLATFORM_GGP
#ଅନ୍ତର୍ଭାଵ <ggp_c/vulkan_types.h>
#ଅନ୍ତର୍ଭାଵ "vulkan_ggp.h"
#endif


#ifdef VK_USE_PLATFORM_SCREEN_QNX
#ଅନ୍ତର୍ଭାଵ <screen/screen.h>
#ଅନ୍ତର୍ଭାଵ "vulkan_screen.h"
#endif


#ifdef VK_USE_PLATFORM_SCI
#ଅନ୍ତର୍ଭାଵ <nvscisync.h>
#ଅନ୍ତର୍ଭାଵ <nvscibuf.h>
#ଅନ୍ତର୍ଭାଵ "vulkan_sci.h"
#endif


#ifdef VK_USE_PLATFORM_OHOS
#ଅନ୍ତର୍ଭାଵ "vulkan_ohos.h"
#endif

/* vulkan_beta.h should go last in the event any beta extension interactions
 * with platform extensions exist.
 */
#ifdef VK_ENABLE_BETA_EXTENSIONS
#ଅନ୍ତର୍ଭାଵ "vulkan_beta.h"
#endif

#endif // VULKAN_H_
