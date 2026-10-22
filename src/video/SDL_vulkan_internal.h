/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2026 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/
#اگر_غیر_تعریف_شدہ SDL_vulkan_اندرونی_h
#تعریف_کرو SDL_vulkan_اندرونی_h

#شامل "SDL_internal.h"

#اگر_تعریف_شدہ SDL_VIDEO_VULKAN
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_ANDROID
#تعریف_کرو VK_USE_PLATFORM_ANDROID_KHR
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_OPENHARMONY
#تعریف_کرو VK_USE_PLATFORM_OHOS
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_COCOA
#تعریف_کرو VK_USE_PLATFORM_METAL_EXT
#تعریف_کرو VK_USE_PLATFORM_MACOS_MVK
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_UIKIT
#تعریف_کرو VK_USE_PLATFORM_METAL_EXT
#تعریف_کرو VK_USE_PLATFORM_IOS_MVK
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_WAYLAND
#تعریف_کرو VK_USE_PLATFORM_WAYLAND_KHR
#شامل "wayland/SDL_waylanddyn.h"
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_WINDOWS
#تعریف_کرو VK_USE_PLATFORM_WIN32_KHR
#شامل "../core/windows/SDL_windows.h"
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11
#تعریف_کرو VK_USE_PLATFORM_XLIB_KHR
#تعریف_کرو VK_USE_PLATFORM_XCB_KHR
#اگر_ختم

#تعریف_کرو VK_NO_PROTOTYPES
#شامل "./khronos/vulkan/vulkan.h"

#شامل <SDL3/SDL_vulkan.h>

خارجی ثابت حرف *SDL_Vulkan_Get_نتیجہ_String(Vk_نتیجہ نتیجہ);

خارجی VkExtensionProperties *SDL_Vulkan_CreateInstanceExtensionsList(
    PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties,
    Uint32 *extension_گنتی); // free returned list with SDL_free

/* Create a surface directly from a display connected to a physical device
 * using the DisplayKHR extension.
 * This needs to be passed an instance that was created with the VK_KHR_DISPLAY_EXTENSION_NAME
 * extension. */
خارجی bool SDL_Vulkan_Display_CreateSurface(خالی *vkGetInstanceProcAddr,
                                             VkInstance instance,
                                             ثابت ساخت Vk_تخصیص_Callbacks *allocator,
                                             VkSurfaceKHR *surface);

/* Platform independent base function for destroying the Vulkan surface. Unlike surface
 * creation, surface destruction doesn't require platform specific extensions like
 * VK_KHR_wayland_surface, VK_KHR_android_surface or VK_EXT_metal_surface. The only
 * necessary extension is cross platform VK_KHR_surface, which is a dependency to all
 * WSI platform extensions, so we can handle surface destruction in an platform-independent
 * manner. */
خارجی خالی SDL_Vulkan_Destroy_Surface_اندرونی(خالی *vkGetInstanceProcAddr,
                                               VkInstance instance,
                                               VkSurfaceKHR surface,
                                               ثابت ساخت Vk_تخصیص_Callbacks *allocator);
#ورنہ

// No SDL Vulkan support, just include the header for typedefs
#شامل <SDL3/SDL_vulkan.h>

قسمتعریف خالی (*PFN_vkGetInstanceProcAddr)(خالی);
قسمتعریف صحیح (*PFN_vkEnumerateInstanceExtensionProperties)(خالی);

#اگر_ختم // SDL_VIDEO_VULKAN

#اگر_ختم // SDL_vulkan_internal_h_
