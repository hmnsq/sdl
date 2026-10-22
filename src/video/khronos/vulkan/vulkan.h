#ifndef VULKAN_H_
#define VULKAN_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

#അന്തര്ഭാവ "vk_platform.h"
#അന്തര്ഭാവ "vulkan_core.h"

#ifdef VK_USE_PLATFORM_ANDROID_KHR
#അന്തര്ഭാവ "vulkan_android.h"
#endif

#ifdef VK_USE_PLATFORM_FUCHSIA
#അന്തര്ഭാവ <zircon/types.h>
#അന്തര്ഭാവ "vulkan_fuchsia.h"
#endif

#ifdef VK_USE_PLATFORM_IOS_MVK
#അന്തര്ഭാവ "vulkan_ios.h"
#endif


#ifdef VK_USE_PLATFORM_MACOS_MVK
#അന്തര്ഭാവ "vulkan_macos.h"
#endif

#ifdef VK_USE_PLATFORM_METAL_EXT
#അന്തര്ഭാവ "vulkan_metal.h"
#endif

#ifdef VK_USE_PLATFORM_VI_NN
#അന്തര്ഭാവ "vulkan_vi.h"
#endif

#ifdef VK_USE_PLATFORM_UBM_SEC
#അന്തര്ഭാവ "vulkan_ubm.h"
#endif

#ifdef VK_USE_PLATFORM_WAYLAND_KHR
#അന്തര്ഭാവ "vulkan_wayland.h"
#endif


#ifdef VK_USE_PLATFORM_WIN32_KHR
#അന്തര്ഭാവ <windows.h>
#അന്തര്ഭാവ "vulkan_win32.h"
#endif


#ifdef VK_USE_PLATFORM_XCB_KHR
#അന്തര്ഭാവ <xcb/xcb.h>
#അന്തര്ഭാവ "vulkan_xcb.h"
#endif


#ifdef VK_USE_PLATFORM_XLIB_KHR
#അന്തര്ഭാവ <X11/Xlib.h>
#അന്തര്ഭാവ "vulkan_xlib.h"
#endif


#ifdef VK_USE_PLATFORM_DIRECTFB_EXT
#അന്തര്ഭാവ <directfb.h>
#അന്തര്ഭാവ "vulkan_directfb.h"
#endif


#ifdef VK_USE_PLATFORM_XLIB_XRANDR_EXT
#അന്തര്ഭാവ <X11/Xlib.h>
#അന്തര്ഭാവ <X11/extensions/Xrandr.h>
#അന്തര്ഭാവ "vulkan_xlib_xrandr.h"
#endif


#ifdef VK_USE_PLATFORM_GGP
#അന്തര്ഭാവ <ggp_c/vulkan_types.h>
#അന്തര്ഭാവ "vulkan_ggp.h"
#endif


#ifdef VK_USE_PLATFORM_SCREEN_QNX
#അന്തര്ഭാവ <screen/screen.h>
#അന്തര്ഭാവ "vulkan_screen.h"
#endif


#ifdef VK_USE_PLATFORM_SCI
#അന്തര്ഭാവ <nvscisync.h>
#അന്തര്ഭാവ <nvscibuf.h>
#അന്തര്ഭാവ "vulkan_sci.h"
#endif


#ifdef VK_USE_PLATFORM_OHOS
#അന്തര്ഭാവ "vulkan_ohos.h"
#endif

/* vulkan_beta.h should go last in the event any beta extension interactions
 * with platform extensions exist.
 */
#ifdef VK_ENABLE_BETA_EXTENSIONS
#അന്തര്ഭാവ "vulkan_beta.h"
#endif

#endif // VULKAN_H_
