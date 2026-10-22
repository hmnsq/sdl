#ifndef VULKAN_H_
#define VULKAN_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

#অন্তর্ভাৱ "vk_platform.h"
#অন্তর্ভাৱ "vulkan_core.h"

#ifdef VK_USE_PLATFORM_ANDROID_KHR
#অন্তর্ভাৱ "vulkan_android.h"
#endif

#ifdef VK_USE_PLATFORM_FUCHSIA
#অন্তর্ভাৱ <zircon/types.h>
#অন্তর্ভাৱ "vulkan_fuchsia.h"
#endif

#ifdef VK_USE_PLATFORM_IOS_MVK
#অন্তর্ভাৱ "vulkan_ios.h"
#endif


#ifdef VK_USE_PLATFORM_MACOS_MVK
#অন্তর্ভাৱ "vulkan_macos.h"
#endif

#ifdef VK_USE_PLATFORM_METAL_EXT
#অন্তর্ভাৱ "vulkan_metal.h"
#endif

#ifdef VK_USE_PLATFORM_VI_NN
#অন্তর্ভাৱ "vulkan_vi.h"
#endif

#ifdef VK_USE_PLATFORM_UBM_SEC
#অন্তর্ভাৱ "vulkan_ubm.h"
#endif

#ifdef VK_USE_PLATFORM_WAYLAND_KHR
#অন্তর্ভাৱ "vulkan_wayland.h"
#endif


#ifdef VK_USE_PLATFORM_WIN32_KHR
#অন্তর্ভাৱ <windows.h>
#অন্তর্ভাৱ "vulkan_win32.h"
#endif


#ifdef VK_USE_PLATFORM_XCB_KHR
#অন্তর্ভাৱ <xcb/xcb.h>
#অন্তর্ভাৱ "vulkan_xcb.h"
#endif


#ifdef VK_USE_PLATFORM_XLIB_KHR
#অন্তর্ভাৱ <X11/Xlib.h>
#অন্তর্ভাৱ "vulkan_xlib.h"
#endif


#ifdef VK_USE_PLATFORM_DIRECTFB_EXT
#অন্তর্ভাৱ <directfb.h>
#অন্তর্ভাৱ "vulkan_directfb.h"
#endif


#ifdef VK_USE_PLATFORM_XLIB_XRANDR_EXT
#অন্তর্ভাৱ <X11/Xlib.h>
#অন্তর্ভাৱ <X11/extensions/Xrandr.h>
#অন্তর্ভাৱ "vulkan_xlib_xrandr.h"
#endif


#ifdef VK_USE_PLATFORM_GGP
#অন্তর্ভাৱ <ggp_c/vulkan_types.h>
#অন্তর্ভাৱ "vulkan_ggp.h"
#endif


#ifdef VK_USE_PLATFORM_SCREEN_QNX
#অন্তর্ভাৱ <screen/screen.h>
#অন্তর্ভাৱ "vulkan_screen.h"
#endif


#ifdef VK_USE_PLATFORM_SCI
#অন্তর্ভাৱ <nvscisync.h>
#অন্তর্ভাৱ <nvscibuf.h>
#অন্তর্ভাৱ "vulkan_sci.h"
#endif


#ifdef VK_USE_PLATFORM_OHOS
#অন্তর্ভাৱ "vulkan_ohos.h"
#endif

/* vulkan_beta.h should go last in the event any beta extension interactions
 * with platform extensions exist.
 */
#ifdef VK_ENABLE_BETA_EXTENSIONS
#অন্তর্ভাৱ "vulkan_beta.h"
#endif

#endif // VULKAN_H_
