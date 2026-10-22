#اگر_تعریف_نشده VULKAN_H_
#تعریف_کن VULKAN_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

#ضمن "vk_platform.h"
#ضمن "vulkan_core.h"

#اگر_تعریف_شده VK_USE_PLATFORM_ANDROID_KHR
#ضمن "vulkan_android.h"
#پایان_اگر

#اگر_تعریف_شده VK_USE_PLATFORM_FUCHSIA
#ضمن <zircon/types.h>
#ضمن "vulkan_fuchsia.h"
#پایان_اگر

#اگر_تعریف_شده VK_USE_PLATFORM_IOS_MVK
#ضمن "vulkan_ios.h"
#پایان_اگر


#اگر_تعریف_شده VK_USE_PLATFORM_MACOS_MVK
#ضمن "vulkan_macos.h"
#پایان_اگر

#اگر_تعریف_شده VK_USE_PLATFORM_METAL_EXT
#ضمن "vulkan_metal.h"
#پایان_اگر

#اگر_تعریف_شده VK_USE_PLATFORM_VI_NN
#ضمن "vulkan_vi.h"
#پایان_اگر

#اگر_تعریف_شده VK_USE_PLATFORM_UBM_SEC
#ضمن "vulkan_ubm.h"
#پایان_اگر

#اگر_تعریف_شده VK_USE_PLATFORM_WAYLAND_KHR
#ضمن "vulkan_wayland.h"
#پایان_اگر


#اگر_تعریف_شده VK_USE_PLATFORM_WIN32_KHR
#ضمن <windows.h>
#ضمن "vulkan_win32.h"
#پایان_اگر


#اگر_تعریف_شده VK_USE_PLATFORM_XCB_KHR
#ضمن <xcb/xcb.h>
#ضمن "vulkan_xcb.h"
#پایان_اگر


#اگر_تعریف_شده VK_USE_PLATFORM_XLIB_KHR
#ضمن <X11/Xlib.h>
#ضمن "vulkan_xlib.h"
#پایان_اگر


#اگر_تعریف_شده VK_USE_PLATFORM_DIRECTFB_EXT
#ضمن <directfb.h>
#ضمن "vulkan_directfb.h"
#پایان_اگر


#اگر_تعریف_شده VK_USE_PLATFORM_XLIB_XRANDR_EXT
#ضمن <X11/Xlib.h>
#ضمن <X11/extensions/Xrandr.h>
#ضمن "vulkan_xlib_xrandr.h"
#پایان_اگر


#اگر_تعریف_شده VK_USE_PLATFORM_GGP
#ضمن <ggp_c/vulkan_types.h>
#ضمن "vulkan_ggp.h"
#پایان_اگر


#اگر_تعریف_شده VK_USE_PLATFORM_SCREEN_QNX
#ضمن <screen/screen.h>
#ضمن "vulkan_screen.h"
#پایان_اگر


#اگر_تعریف_شده VK_USE_PLATFORM_SCI
#ضمن <nvscisync.h>
#ضمن <nvscibuf.h>
#ضمن "vulkan_sci.h"
#پایان_اگر


#اگر_تعریف_شده VK_USE_PLATFORM_OHOS
#ضمن "vulkan_ohos.h"
#پایان_اگر

/* vulkan_beta.h should go last in the event any beta extension interactions
 * with platform extensions exist.
 */
#اگر_تعریف_شده VK_ENABLE_BETA_EXTENSIONS
#ضمن "vulkan_beta.h"
#پایان_اگر

#پایان_اگر // VULKAN_H_
