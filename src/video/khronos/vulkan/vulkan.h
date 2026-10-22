#अगर_अघोषित VULKAN_H_
#घोषणा VULKAN_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

#समावेश "vk_platform.h"
#समावेश "vulkan_core.h"

#अगर_घोषित VK_USE_PLATFORM_ANDROID_KHR
#समावेश "vulkan_android.h"
#पूर्ण_अगर

#अगर_घोषित VK_USE_PLATFORM_FUCHSIA
#समावेश <zircon/types.h>
#समावेश "vulkan_fuchsia.h"
#पूर्ण_अगर

#अगर_घोषित VK_USE_PLATFORM_IOS_MVK
#समावेश "vulkan_ios.h"
#पूर्ण_अगर


#अगर_घोषित VK_USE_PLATFORM_MACOS_MVK
#समावेश "vulkan_macos.h"
#पूर्ण_अगर

#अगर_घोषित VK_USE_PLATFORM_METAL_EXT
#समावेश "vulkan_metal.h"
#पूर्ण_अगर

#अगर_घोषित VK_USE_PLATFORM_VI_NN
#समावेश "vulkan_vi.h"
#पूर्ण_अगर

#अगर_घोषित VK_USE_PLATFORM_UBM_SEC
#समावेश "vulkan_ubm.h"
#पूर्ण_अगर

#अगर_घोषित VK_USE_PLATFORM_WAYLAND_KHR
#समावेश "vulkan_wayland.h"
#पूर्ण_अगर


#अगर_घोषित VK_USE_PLATFORM_WIN32_KHR
#समावेश <windows.h>
#समावेश "vulkan_win32.h"
#पूर्ण_अगर


#अगर_घोषित VK_USE_PLATFORM_XCB_KHR
#समावेश <xcb/xcb.h>
#समावेश "vulkan_xcb.h"
#पूर्ण_अगर


#अगर_घोषित VK_USE_PLATFORM_XLIB_KHR
#समावेश <X11/Xlib.h>
#समावेश "vulkan_xlib.h"
#पूर्ण_अगर


#अगर_घोषित VK_USE_PLATFORM_DIRECTFB_EXT
#समावेश <directfb.h>
#समावेश "vulkan_directfb.h"
#पूर्ण_अगर


#अगर_घोषित VK_USE_PLATFORM_XLIB_XRANDR_EXT
#समावेश <X11/Xlib.h>
#समावेश <X11/extensions/Xrandr.h>
#समावेश "vulkan_xlib_xrandr.h"
#पूर्ण_अगर


#अगर_घोषित VK_USE_PLATFORM_GGP
#समावेश <ggp_c/vulkan_types.h>
#समावेश "vulkan_ggp.h"
#पूर्ण_अगर


#अगर_घोषित VK_USE_PLATFORM_SCREEN_QNX
#समावेश <screen/screen.h>
#समावेश "vulkan_screen.h"
#पूर्ण_अगर


#अगर_घोषित VK_USE_PLATFORM_SCI
#समावेश <nvscisync.h>
#समावेश <nvscibuf.h>
#समावेश "vulkan_sci.h"
#पूर्ण_अगर


#अगर_घोषित VK_USE_PLATFORM_OHOS
#समावेश "vulkan_ohos.h"
#पूर्ण_अगर

/* vulkan_beta.h should go last in the event any beta extension interactions
 * with platform extensions exist.
 */
#अगर_घोषित VK_ENABLE_BETA_EXTENSIONS
#समावेश "vulkan_beta.h"
#पूर्ण_अगर

#पूर्ण_अगर // VULKAN_H_
