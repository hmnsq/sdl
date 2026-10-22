#నిర్వచితం_కాకపోతే VULKAN_H_
#నిర్వచించు VULKAN_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

#అన్తర్భావ "vk_platform.h"
#అన్తర్భావ "vulkan_core.h"

#నిర్వచితమైతే VK_USE_PLATFORM_ANDROID_KHR
#అన్తర్భావ "vulkan_android.h"
#అయితే_ముగింపు

#నిర్వచితమైతే VK_USE_PLATFORM_FUCHSIA
#అన్తర్భావ <zircon/types.h>
#అన్తర్భావ "vulkan_fuchsia.h"
#అయితే_ముగింపు

#నిర్వచితమైతే VK_USE_PLATFORM_IOS_MVK
#అన్తర్భావ "vulkan_ios.h"
#అయితే_ముగింపు


#నిర్వచితమైతే VK_USE_PLATFORM_MACOS_MVK
#అన్తర్భావ "vulkan_macos.h"
#అయితే_ముగింపు

#నిర్వచితమైతే VK_USE_PLATFORM_METAL_EXT
#అన్తర్భావ "vulkan_metal.h"
#అయితే_ముగింపు

#నిర్వచితమైతే VK_USE_PLATFORM_VI_NN
#అన్తర్భావ "vulkan_vi.h"
#అయితే_ముగింపు

#నిర్వచితమైతే VK_USE_PLATFORM_UBM_SEC
#అన్తర్భావ "vulkan_ubm.h"
#అయితే_ముగింపు

#నిర్వచితమైతే VK_USE_PLATFORM_WAYLAND_KHR
#అన్తర్భావ "vulkan_wayland.h"
#అయితే_ముగింపు


#నిర్వచితమైతే VK_USE_PLATFORM_WIN32_KHR
#అన్తర్భావ <windows.h>
#అన్తర్భావ "vulkan_win32.h"
#అయితే_ముగింపు


#నిర్వచితమైతే VK_USE_PLATFORM_XCB_KHR
#అన్తర్భావ <xcb/xcb.h>
#అన్తర్భావ "vulkan_xcb.h"
#అయితే_ముగింపు


#నిర్వచితమైతే VK_USE_PLATFORM_XLIB_KHR
#అన్తర్భావ <X11/Xlib.h>
#అన్తర్భావ "vulkan_xlib.h"
#అయితే_ముగింపు


#నిర్వచితమైతే VK_USE_PLATFORM_DIRECTFB_EXT
#అన్తర్భావ <directfb.h>
#అన్తర్భావ "vulkan_directfb.h"
#అయితే_ముగింపు


#నిర్వచితమైతే VK_USE_PLATFORM_XLIB_XRANDR_EXT
#అన్తర్భావ <X11/Xlib.h>
#అన్తర్భావ <X11/extensions/Xrandr.h>
#అన్తర్భావ "vulkan_xlib_xrandr.h"
#అయితే_ముగింపు


#నిర్వచితమైతే VK_USE_PLATFORM_GGP
#అన్తర్భావ <ggp_c/vulkan_types.h>
#అన్తర్భావ "vulkan_ggp.h"
#అయితే_ముగింపు


#నిర్వచితమైతే VK_USE_PLATFORM_SCREEN_QNX
#అన్తర్భావ <screen/screen.h>
#అన్తర్భావ "vulkan_screen.h"
#అయితే_ముగింపు


#నిర్వచితమైతే VK_USE_PLATFORM_SCI
#అన్తర్భావ <nvscisync.h>
#అన్తర్భావ <nvscibuf.h>
#అన్తర్భావ "vulkan_sci.h"
#అయితే_ముగింపు


#నిర్వచితమైతే VK_USE_PLATFORM_OHOS
#అన్తర్భావ "vulkan_ohos.h"
#అయితే_ముగింపు

/* vulkan_beta.h should go last in the event any beta extension interactions
 * with platform extensions exist.
 */
#నిర్వచితమైతే VK_ENABLE_BETA_EXTENSIONS
#అన్తర్భావ "vulkan_beta.h"
#అయితే_ముగింపు

#అయితే_ముగింపు // VULKAN_H_
