#که_نه_تعریف_شوی VULKAN_H_
#تعریف_کړه VULKAN_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

#ضمن "vk_platform.h"
#ضمن "vulkan_core.h"

#که_تعریف_شوی VK_USE_PLATFORM_ANDROID_KHR
#ضمن "vulkan_android.h"
#د_که_پای

#که_تعریف_شوی VK_USE_PLATFORM_FUCHSIA
#ضمن <zircon/types.h>
#ضمن "vulkan_fuchsia.h"
#د_که_پای

#که_تعریف_شوی VK_USE_PLATFORM_IOS_MVK
#ضمن "vulkan_ios.h"
#د_که_پای


#که_تعریف_شوی VK_USE_PLATFORM_MACOS_MVK
#ضمن "vulkan_macos.h"
#د_که_پای

#که_تعریف_شوی VK_USE_PLATFORM_METAL_EXT
#ضمن "vulkan_metal.h"
#د_که_پای

#که_تعریف_شوی VK_USE_PLATFORM_VI_NN
#ضمن "vulkan_vi.h"
#د_که_پای

#که_تعریف_شوی VK_USE_PLATFORM_UBM_SEC
#ضمن "vulkan_ubm.h"
#د_که_پای

#که_تعریف_شوی VK_USE_PLATFORM_WAYLAND_KHR
#ضمن "vulkan_wayland.h"
#د_که_پای


#که_تعریف_شوی VK_USE_PLATFORM_WIN32_KHR
#ضمن <windows.h>
#ضمن "vulkan_win32.h"
#د_که_پای


#که_تعریف_شوی VK_USE_PLATFORM_XCB_KHR
#ضمن <xcb/xcb.h>
#ضمن "vulkan_xcb.h"
#د_که_پای


#که_تعریف_شوی VK_USE_PLATFORM_XLIB_KHR
#ضمن <X11/Xlib.h>
#ضمن "vulkan_xlib.h"
#د_که_پای


#که_تعریف_شوی VK_USE_PLATFORM_DIRECTFB_EXT
#ضمن <directfb.h>
#ضمن "vulkan_directfb.h"
#د_که_پای


#که_تعریف_شوی VK_USE_PLATFORM_XLIB_XRANDR_EXT
#ضمن <X11/Xlib.h>
#ضمن <X11/extensions/Xrandr.h>
#ضمن "vulkan_xlib_xrandr.h"
#د_که_پای


#که_تعریف_شوی VK_USE_PLATFORM_GGP
#ضمن <ggp_c/vulkan_types.h>
#ضمن "vulkan_ggp.h"
#د_که_پای


#که_تعریف_شوی VK_USE_PLATFORM_SCREEN_QNX
#ضمن <screen/screen.h>
#ضمن "vulkan_screen.h"
#د_که_پای


#که_تعریف_شوی VK_USE_PLATFORM_SCI
#ضمن <nvscisync.h>
#ضمن <nvscibuf.h>
#ضمن "vulkan_sci.h"
#د_که_پای


#که_تعریف_شوی VK_USE_PLATFORM_OHOS
#ضمن "vulkan_ohos.h"
#د_که_پای

/* vulkan_beta.h should go last in the event any beta extension interactions
 * with platform extensions exist.
 */
#که_تعریف_شوی VK_ENABLE_BETA_EXTENSIONS
#ضمن "vulkan_beta.h"
#د_که_پای

#د_که_پای // VULKAN_H_
