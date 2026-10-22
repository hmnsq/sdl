#ifndef VULKAN_H_
#define VULKAN_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

#அந்தர்பாவ "vk_platform.h"
#அந்தர்பாவ "vulkan_core.h"

#ifdef VK_USE_PLATFORM_ANDROID_KHR
#அந்தர்பாவ "vulkan_android.h"
#endif

#ifdef VK_USE_PLATFORM_FUCHSIA
#அந்தர்பாவ <zircon/types.h>
#அந்தர்பாவ "vulkan_fuchsia.h"
#endif

#ifdef VK_USE_PLATFORM_IOS_MVK
#அந்தர்பாவ "vulkan_ios.h"
#endif


#ifdef VK_USE_PLATFORM_MACOS_MVK
#அந்தர்பாவ "vulkan_macos.h"
#endif

#ifdef VK_USE_PLATFORM_METAL_EXT
#அந்தர்பாவ "vulkan_metal.h"
#endif

#ifdef VK_USE_PLATFORM_VI_NN
#அந்தர்பாவ "vulkan_vi.h"
#endif

#ifdef VK_USE_PLATFORM_UBM_SEC
#அந்தர்பாவ "vulkan_ubm.h"
#endif

#ifdef VK_USE_PLATFORM_WAYLAND_KHR
#அந்தர்பாவ "vulkan_wayland.h"
#endif


#ifdef VK_USE_PLATFORM_WIN32_KHR
#அந்தர்பாவ <windows.h>
#அந்தர்பாவ "vulkan_win32.h"
#endif


#ifdef VK_USE_PLATFORM_XCB_KHR
#அந்தர்பாவ <xcb/xcb.h>
#அந்தர்பாவ "vulkan_xcb.h"
#endif


#ifdef VK_USE_PLATFORM_XLIB_KHR
#அந்தர்பாவ <X11/Xlib.h>
#அந்தர்பாவ "vulkan_xlib.h"
#endif


#ifdef VK_USE_PLATFORM_DIRECTFB_EXT
#அந்தர்பாவ <directfb.h>
#அந்தர்பாவ "vulkan_directfb.h"
#endif


#ifdef VK_USE_PLATFORM_XLIB_XRANDR_EXT
#அந்தர்பாவ <X11/Xlib.h>
#அந்தர்பாவ <X11/extensions/Xrandr.h>
#அந்தர்பாவ "vulkan_xlib_xrandr.h"
#endif


#ifdef VK_USE_PLATFORM_GGP
#அந்தர்பாவ <ggp_c/vulkan_types.h>
#அந்தர்பாவ "vulkan_ggp.h"
#endif


#ifdef VK_USE_PLATFORM_SCREEN_QNX
#அந்தர்பாவ <screen/screen.h>
#அந்தர்பாவ "vulkan_screen.h"
#endif


#ifdef VK_USE_PLATFORM_SCI
#அந்தர்பாவ <nvscisync.h>
#அந்தர்பாவ <nvscibuf.h>
#அந்தர்பாவ "vulkan_sci.h"
#endif


#ifdef VK_USE_PLATFORM_OHOS
#அந்தர்பாவ "vulkan_ohos.h"
#endif

/* vulkan_beta.h should go last in the event any beta extension interactions
 * with platform extensions exist.
 */
#ifdef VK_ENABLE_BETA_EXTENSIONS
#அந்தர்பாவ "vulkan_beta.h"
#endif

#endif // VULKAN_H_
