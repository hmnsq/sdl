#جے_بنا_تعریف VULKAN_H_
#تعریف_کرو VULKAN_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

#ضمن "vk_platform.h"
#ضمن "vulkan_core.h"

#جے_تعریف_شدہ VK_USE_PLATFORM_ANDROID_KHR
#ضمن "vulkan_android.h"
#جے_انت

#جے_تعریف_شدہ VK_USE_PLATFORM_FUCHSIA
#ضمن <zircon/types.h>
#ضمن "vulkan_fuchsia.h"
#جے_انت

#جے_تعریف_شدہ VK_USE_PLATFORM_IOS_MVK
#ضمن "vulkan_ios.h"
#جے_انت


#جے_تعریف_شدہ VK_USE_PLATFORM_MACOS_MVK
#ضمن "vulkan_macos.h"
#جے_انت

#جے_تعریف_شدہ VK_USE_PLATFORM_METAL_EXT
#ضمن "vulkan_metal.h"
#جے_انت

#جے_تعریف_شدہ VK_USE_PLATFORM_VI_NN
#ضمن "vulkan_vi.h"
#جے_انت

#جے_تعریف_شدہ VK_USE_PLATFORM_UBM_SEC
#ضمن "vulkan_ubm.h"
#جے_انت

#جے_تعریف_شدہ VK_USE_PLATFORM_WAYLAND_KHR
#ضمن "vulkan_wayland.h"
#جے_انت


#جے_تعریف_شدہ VK_USE_PLATFORM_WIN32_KHR
#ضمن <windows.h>
#ضمن "vulkan_win32.h"
#جے_انت


#جے_تعریف_شدہ VK_USE_PLATFORM_XCB_KHR
#ضمن <xcb/xcb.h>
#ضمن "vulkan_xcb.h"
#جے_انت


#جے_تعریف_شدہ VK_USE_PLATFORM_XLIB_KHR
#ضمن <X11/Xlib.h>
#ضمن "vulkan_xlib.h"
#جے_انت


#جے_تعریف_شدہ VK_USE_PLATFORM_DIRECTFB_EXT
#ضمن <directfb.h>
#ضمن "vulkan_directfb.h"
#جے_انت


#جے_تعریف_شدہ VK_USE_PLATFORM_XLIB_XRANDR_EXT
#ضمن <X11/Xlib.h>
#ضمن <X11/extensions/Xrandr.h>
#ضمن "vulkan_xlib_xrandr.h"
#جے_انت


#جے_تعریف_شدہ VK_USE_PLATFORM_GGP
#ضمن <ggp_c/vulkan_types.h>
#ضمن "vulkan_ggp.h"
#جے_انت


#جے_تعریف_شدہ VK_USE_PLATFORM_SCREEN_QNX
#ضمن <screen/screen.h>
#ضمن "vulkan_screen.h"
#جے_انت


#جے_تعریف_شدہ VK_USE_PLATFORM_SCI
#ضمن <nvscisync.h>
#ضمن <nvscibuf.h>
#ضمن "vulkan_sci.h"
#جے_انت


#جے_تعریف_شدہ VK_USE_PLATFORM_OHOS
#ضمن "vulkan_ohos.h"
#جے_انت

/* vulkan_beta.h should go last in the event any beta extension interactions
 * with platform extensions exist.
 */
#جے_تعریف_شدہ VK_ENABLE_BETA_EXTENSIONS
#ضمن "vulkan_beta.h"
#جے_انت

#جے_انت // VULKAN_H_
