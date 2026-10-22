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
#جيڪڏهن_وصف_نه_ٿيل SDL_vulkan_اندروني_h
#وصف_ڪريو SDL_vulkan_اندروني_h

#ضمن "SDL_internal.h"

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_VULKAN
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_ANDROID
#وصف_ڪريو VK_USE_PLATFORM_ANDROID_KHR
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_OPENHARMONY
#وصف_ڪريو VK_USE_PLATFORM_OHOS
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_COCOA
#وصف_ڪريو VK_USE_PLATFORM_METAL_EXT
#وصف_ڪريو VK_USE_PLATFORM_MACOS_MVK
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_UIKIT
#وصف_ڪريو VK_USE_PLATFORM_METAL_EXT
#وصف_ڪريو VK_USE_PLATFORM_IOS_MVK
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_WAYLAND
#وصف_ڪريو VK_USE_PLATFORM_WAYLAND_KHR
#ضمن "wayland/SDL_waylanddyn.h"
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_WINDOWS
#وصف_ڪريو VK_USE_PLATFORM_WIN32_KHR
#ضمن "../core/windows/SDL_windows.h"
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11
#وصف_ڪريو VK_USE_PLATFORM_XLIB_KHR
#وصف_ڪريو VK_USE_PLATFORM_XCB_KHR
#جيڪڏهن_پورو

#وصف_ڪريو VK_NO_PROTOTYPES
#ضمن "./khronos/vulkan/vulkan.h"

#ضمن <SDL3/SDL_vulkan.h>

خارجي ثابت حرف *SDL_Vulkan_Get_نتيجو_String(Vk_نتيجو نتيجو);

خارجي VkExtensionProperties *SDL_Vulkan_CreateInstanceExtensionsList(
    PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties,
    Uint32 *extension_ڳڻپ); // free returned list with SDL_free

/* Create a surface directly from a display connected to a physical device
 * using the DisplayKHR extension.
 * This needs to be passed an instance that was created with the VK_KHR_DISPLAY_EXTENSION_NAME
 * extension. */
خارجي bool SDL_Vulkan_Display_CreateSurface(فراغ *vkGetInstanceProcAddr,
                                             VkInstance instance,
                                             ثابت بنية Vk_ورهاست_Callbacks *allocator,
                                             VkSurfaceKHR *surface);

/* Platform independent base function for destroying the Vulkan surface. Unlike surface
 * creation, surface destruction doesn't require platform specific extensions like
 * VK_KHR_wayland_surface, VK_KHR_android_surface or VK_EXT_metal_surface. The only
 * necessary extension is cross platform VK_KHR_surface, which is a dependency to all
 * WSI platform extensions, so we can handle surface destruction in an platform-independent
 * manner. */
خارجي فراغ SDL_Vulkan_Destroy_Surface_اندروني(فراغ *vkGetInstanceProcAddr,
                                               VkInstance instance,
                                               VkSurfaceKHR surface,
                                               ثابت بنية Vk_ورهاست_Callbacks *allocator);
#وإلا

// No SDL Vulkan support, just include the header for typedefs
#ضمن <SDL3/SDL_vulkan.h>

تعريفنوع فراغ (*PFN_vkGetInstanceProcAddr)(فراغ);
تعريفنوع صحيح (*PFN_vkEnumerateInstanceExtensionProperties)(فراغ);

#جيڪڏهن_پورو // SDL_VIDEO_VULKAN

#جيڪڏهن_پورو // SDL_vulkan_internal_h_
