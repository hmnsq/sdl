#यदि_अपरिभाषितम् VULKAN_H_
#परिभाषय VULKAN_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

#अन्तर्भाव "vk_platform.h"
#अन्तर्भाव "vulkan_core.h"

#यदि_परिभाषितम् VK_USE_PLATFORM_ANDROID_KHR
#अन्तर्भाव "vulkan_android.h"
#यदि_अन्तः

#यदि_परिभाषितम् VK_USE_PLATFORM_FUCHSIA
#अन्तर्भाव <zircon/types.h>
#अन्तर्भाव "vulkan_fuchsia.h"
#यदि_अन्तः

#यदि_परिभाषितम् VK_USE_PLATFORM_IOS_MVK
#अन्तर्भाव "vulkan_ios.h"
#यदि_अन्तः


#यदि_परिभाषितम् VK_USE_PLATFORM_MACOS_MVK
#अन्तर्भाव "vulkan_macos.h"
#यदि_अन्तः

#यदि_परिभाषितम् VK_USE_PLATFORM_METAL_EXT
#अन्तर्भाव "vulkan_metal.h"
#यदि_अन्तः

#यदि_परिभाषितम् VK_USE_PLATFORM_VI_NN
#अन्तर्भाव "vulkan_vi.h"
#यदि_अन्तः

#यदि_परिभाषितम् VK_USE_PLATFORM_UBM_SEC
#अन्तर्भाव "vulkan_ubm.h"
#यदि_अन्तः

#यदि_परिभाषितम् VK_USE_PLATFORM_WAYLAND_KHR
#अन्तर्भाव "vulkan_wayland.h"
#यदि_अन्तः


#यदि_परिभाषितम् VK_USE_PLATFORM_WIN32_KHR
#अन्तर्भाव <windows.h>
#अन्तर्भाव "vulkan_win32.h"
#यदि_अन्तः


#यदि_परिभाषितम् VK_USE_PLATFORM_XCB_KHR
#अन्तर्भाव <xcb/xcb.h>
#अन्तर्भाव "vulkan_xcb.h"
#यदि_अन्तः


#यदि_परिभाषितम् VK_USE_PLATFORM_XLIB_KHR
#अन्तर्भाव <X11/Xlib.h>
#अन्तर्भाव "vulkan_xlib.h"
#यदि_अन्तः


#यदि_परिभाषितम् VK_USE_PLATFORM_DIRECTFB_EXT
#अन्तर्भाव <directfb.h>
#अन्तर्भाव "vulkan_directfb.h"
#यदि_अन्तः


#यदि_परिभाषितम् VK_USE_PLATFORM_XLIB_XRANDR_EXT
#अन्तर्भाव <X11/Xlib.h>
#अन्तर्भाव <X11/extensions/Xrandr.h>
#अन्तर्भाव "vulkan_xlib_xrandr.h"
#यदि_अन्तः


#यदि_परिभाषितम् VK_USE_PLATFORM_GGP
#अन्तर्भाव <ggp_c/vulkan_types.h>
#अन्तर्भाव "vulkan_ggp.h"
#यदि_अन्तः


#यदि_परिभाषितम् VK_USE_PLATFORM_SCREEN_QNX
#अन्तर्भाव <screen/screen.h>
#अन्तर्भाव "vulkan_screen.h"
#यदि_अन्तः


#यदि_परिभाषितम् VK_USE_PLATFORM_SCI
#अन्तर्भाव <nvscisync.h>
#अन्तर्भाव <nvscibuf.h>
#अन्तर्भाव "vulkan_sci.h"
#यदि_अन्तः


#यदि_परिभाषितम् VK_USE_PLATFORM_OHOS
#अन्तर्भाव "vulkan_ohos.h"
#यदि_अन्तः

/* vulkan_beta.h should go last in the event any beta extension interactions
 * with platform extensions exist.
 */
#यदि_परिभाषितम् VK_ENABLE_BETA_EXTENSIONS
#अन्तर्भाव "vulkan_beta.h"
#यदि_अन्तः

#यदि_अन्तः // VULKAN_H_
