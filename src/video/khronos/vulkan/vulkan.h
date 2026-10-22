#جيڪڏهن_وصف_نه_ٿيل VULKAN_H_
#وصف_ڪريو VULKAN_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

#ضمن "vk_platform.h"
#ضمن "vulkan_core.h"

#جيڪڏهن_وصف_ٿيل VK_USE_PLATFORM_ANDROID_KHR
#ضمن "vulkan_android.h"
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل VK_USE_PLATFORM_FUCHSIA
#ضمن <zircon/types.h>
#ضمن "vulkan_fuchsia.h"
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل VK_USE_PLATFORM_IOS_MVK
#ضمن "vulkan_ios.h"
#جيڪڏهن_پورو


#جيڪڏهن_وصف_ٿيل VK_USE_PLATFORM_MACOS_MVK
#ضمن "vulkan_macos.h"
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل VK_USE_PLATFORM_METAL_EXT
#ضمن "vulkan_metal.h"
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل VK_USE_PLATFORM_VI_NN
#ضمن "vulkan_vi.h"
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل VK_USE_PLATFORM_UBM_SEC
#ضمن "vulkan_ubm.h"
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل VK_USE_PLATFORM_WAYLAND_KHR
#ضمن "vulkan_wayland.h"
#جيڪڏهن_پورو


#جيڪڏهن_وصف_ٿيل VK_USE_PLATFORM_WIN32_KHR
#ضمن <windows.h>
#ضمن "vulkan_win32.h"
#جيڪڏهن_پورو


#جيڪڏهن_وصف_ٿيل VK_USE_PLATFORM_XCB_KHR
#ضمن <xcb/xcb.h>
#ضمن "vulkan_xcb.h"
#جيڪڏهن_پورو


#جيڪڏهن_وصف_ٿيل VK_USE_PLATFORM_XLIB_KHR
#ضمن <X11/Xlib.h>
#ضمن "vulkan_xlib.h"
#جيڪڏهن_پورو


#جيڪڏهن_وصف_ٿيل VK_USE_PLATFORM_DIRECTFB_EXT
#ضمن <directfb.h>
#ضمن "vulkan_directfb.h"
#جيڪڏهن_پورو


#جيڪڏهن_وصف_ٿيل VK_USE_PLATFORM_XLIB_XRANDR_EXT
#ضمن <X11/Xlib.h>
#ضمن <X11/extensions/Xrandr.h>
#ضمن "vulkan_xlib_xrandr.h"
#جيڪڏهن_پورو


#جيڪڏهن_وصف_ٿيل VK_USE_PLATFORM_GGP
#ضمن <ggp_c/vulkan_types.h>
#ضمن "vulkan_ggp.h"
#جيڪڏهن_پورو


#جيڪڏهن_وصف_ٿيل VK_USE_PLATFORM_SCREEN_QNX
#ضمن <screen/screen.h>
#ضمن "vulkan_screen.h"
#جيڪڏهن_پورو


#جيڪڏهن_وصف_ٿيل VK_USE_PLATFORM_SCI
#ضمن <nvscisync.h>
#ضمن <nvscibuf.h>
#ضمن "vulkan_sci.h"
#جيڪڏهن_پورو


#جيڪڏهن_وصف_ٿيل VK_USE_PLATFORM_OHOS
#ضمن "vulkan_ohos.h"
#جيڪڏهن_پورو

/* vulkan_beta.h should go last in the event any beta extension interactions
 * with platform extensions exist.
 */
#جيڪڏهن_وصف_ٿيل VK_ENABLE_BETA_EXTENSIONS
#ضمن "vulkan_beta.h"
#جيڪڏهن_پورو

#جيڪڏهن_پورو // VULKAN_H_
