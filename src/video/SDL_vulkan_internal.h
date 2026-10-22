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
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_vulkan_ਅੰਦਰੂਨੀ_h
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_vulkan_ਅੰਦਰੂਨੀ_h

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_VULKAN
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_ANDROID
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_USE_PLATFORM_ANDROID_KHR
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_OPENHARMONY
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_USE_PLATFORM_OHOS
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_COCOA
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_USE_PLATFORM_METAL_EXT
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_USE_PLATFORM_MACOS_MVK
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_UIKIT
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_USE_PLATFORM_METAL_EXT
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_USE_PLATFORM_IOS_MVK
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_WAYLAND
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_USE_PLATFORM_WAYLAND_KHR
#ਅਨ੍ਤਰ੍ਭਾਵ "wayland/SDL_waylanddyn.h"
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_WINDOWS
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_USE_PLATFORM_WIN32_KHR
#ਅਨ੍ਤਰ੍ਭਾਵ "../core/windows/SDL_windows.h"
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_USE_PLATFORM_XLIB_KHR
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_USE_PLATFORM_XCB_KHR
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_NO_PROTOTYPES
#ਅਨ੍ਤਰ੍ਭਾਵ "./khronos/vulkan/vulkan.h"

#ਅਨ੍ਤਰ੍ਭਾਵ <SDL3/SDL_vulkan.h>

ਬਾਹਰੀ ਅਚਲ ਅੱਖਰ *SDL_Vulkan_Get_ਨਤੀਜਾ_String(Vk_ਨਤੀਜਾ ਨਤੀਜਾ);

ਬਾਹਰੀ VkExtensionProperties *SDL_Vulkan_CreateInstanceExtensionsList(
    PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties,
    Uint32 *extension_ਗਿਣਤੀ); // free returned list with SDL_free

/* Create a surface directly from a display connected to a physical device
 * using the DisplayKHR extension.
 * This needs to be passed an instance that was created with the VK_KHR_DISPLAY_EXTENSION_NAME
 * extension. */
ਬਾਹਰੀ bool SDL_Vulkan_Display_CreateSurface(ਖਾਲੀ *vkGetInstanceProcAddr,
                                             VkInstance instance,
                                             ਅਚਲ ਬਣਤਰ Vk_ਵੰਡ_Callbacks *allocator,
                                             VkSurfaceKHR *surface);

/* Platform independent base function for destroying the Vulkan surface. Unlike surface
 * creation, surface destruction doesn't require platform specific extensions like
 * VK_KHR_wayland_surface, VK_KHR_android_surface or VK_EXT_metal_surface. The only
 * necessary extension is cross platform VK_KHR_surface, which is a dependency to all
 * WSI platform extensions, so we can handle surface destruction in an platform-independent
 * manner. */
ਬਾਹਰੀ ਖਾਲੀ SDL_Vulkan_Destroy_Surface_ਅੰਦਰੂਨੀ(ਖਾਲੀ *vkGetInstanceProcAddr,
                                               VkInstance instance,
                                               VkSurfaceKHR surface,
                                               ਅਚਲ ਬਣਤਰ Vk_ਵੰਡ_Callbacks *allocator);
#ਨਹੀਂਤਾਂ

// No SDL Vulkan support, just include the header for typedefs
#ਅਨ੍ਤਰ੍ਭਾਵ <SDL3/SDL_vulkan.h>

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (*PFN_vkGetInstanceProcAddr)(ਖਾਲੀ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਪੂਰਨ (*PFN_vkEnumerateInstanceExtensionProperties)(ਖਾਲੀ);

#ਜੇ_ਅੰਤ // SDL_VIDEO_VULKAN

#ਜੇ_ਅੰਤ // SDL_vulkan_internal_h_
