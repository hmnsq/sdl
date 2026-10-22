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
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_vulkan_ಆಂತರಿಕ_h
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_vulkan_ಆಂತರಿಕ_h

#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_VULKAN
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_ANDROID
#ವ್ಯಾಖ್ಯಾನಿಸು VK_USE_PLATFORM_ANDROID_KHR
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_OPENHARMONY
#ವ್ಯಾಖ್ಯಾನಿಸು VK_USE_PLATFORM_OHOS
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_COCOA
#ವ್ಯಾಖ್ಯಾನಿಸು VK_USE_PLATFORM_METAL_EXT
#ವ್ಯಾಖ್ಯಾನಿಸು VK_USE_PLATFORM_MACOS_MVK
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_UIKIT
#ವ್ಯಾಖ್ಯಾನಿಸು VK_USE_PLATFORM_METAL_EXT
#ವ್ಯಾಖ್ಯಾನಿಸು VK_USE_PLATFORM_IOS_MVK
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_WAYLAND
#ವ್ಯಾಖ್ಯಾನಿಸು VK_USE_PLATFORM_WAYLAND_KHR
#ಅನ್ತರ್ಭಾವ "wayland/SDL_waylanddyn.h"
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_WINDOWS
#ವ್ಯಾಖ್ಯಾನಿಸು VK_USE_PLATFORM_WIN32_KHR
#ಅನ್ತರ್ಭಾವ "../core/windows/SDL_windows.h"
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11
#ವ್ಯಾಖ್ಯಾನಿಸು VK_USE_PLATFORM_XLIB_KHR
#ವ್ಯಾಖ್ಯಾನಿಸು VK_USE_PLATFORM_XCB_KHR
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿಸು VK_NO_PROTOTYPES
#ಅನ್ತರ್ಭಾವ "./khronos/vulkan/vulkan.h"

#ಅನ್ತರ್ಭಾವ <SDL3/SDL_vulkan.h>

ಬಾಹ್ಯ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *SDL_Vulkan_Get_ಫಲಿತಾಂಶ_String(Vk_ಫಲಿತಾಂಶ ಫಲಿತಾಂಶ);

ಬಾಹ್ಯ VkExtensionProperties *SDL_Vulkan_CreateInstanceExtensionsList(
    PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties,
    Uint32 *extension_ಎಣಿಕೆ); // free returned list with SDL_free

/* Create a surface directly from a display connected to a physical device
 * using the DisplayKHR extension.
 * This needs to be passed an instance that was created with the VK_KHR_DISPLAY_EXTENSION_NAME
 * extension. */
ಬಾಹ್ಯ bool SDL_Vulkan_Display_CreateSurface(ಶೂನ್ಯ *vkGetInstanceProcAddr,
                                             VkInstance instance,
                                             ಸ್ಥಿರಾಂಕ ರಚನೆ Vk_ಹಂಚಿಕೆ_Callbacks *allocator,
                                             VkSurfaceKHR *surface);

/* Platform independent base function for destroying the Vulkan surface. Unlike surface
 * creation, surface destruction doesn't require platform specific extensions like
 * VK_KHR_wayland_surface, VK_KHR_android_surface or VK_EXT_metal_surface. The only
 * necessary extension is cross platform VK_KHR_surface, which is a dependency to all
 * WSI platform extensions, so we can handle surface destruction in an platform-independent
 * manner. */
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_Vulkan_Destroy_Surface_ಆಂತರಿಕ(ಶೂನ್ಯ *vkGetInstanceProcAddr,
                                               VkInstance instance,
                                               VkSurfaceKHR surface,
                                               ಸ್ಥಿರಾಂಕ ರಚನೆ Vk_ಹಂಚಿಕೆ_Callbacks *allocator);
#ಇಲ್ಲದಿದ್ದರೆ

// No SDL Vulkan support, just include the header for typedefs
#ಅನ್ತರ್ಭಾವ <SDL3/SDL_vulkan.h>

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (*PFN_vkGetInstanceProcAddr)(ಶೂನ್ಯ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಪೂರ್ಣಾಂಕ (*PFN_vkEnumerateInstanceExtensionProperties)(ಶೂನ್ಯ);

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_VULKAN

#ಆದರೆ_ಅಂತ್ಯ // SDL_vulkan_internal_h_
