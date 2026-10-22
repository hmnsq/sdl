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
#यदि_अपरिभाषितम् SDL_vulkan_आन्तरिकम्_h
#परिभाषय SDL_vulkan_आन्तरिकम्_h

#अन्तर्भाव "SDL_internal.h"

#यदि_परिभाषितम् SDL_VIDEO_VULKAN
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_ANDROID
#परिभाषय VK_USE_PLATFORM_ANDROID_KHR
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_OPENHARMONY
#परिभाषय VK_USE_PLATFORM_OHOS
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_COCOA
#परिभाषय VK_USE_PLATFORM_METAL_EXT
#परिभाषय VK_USE_PLATFORM_MACOS_MVK
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_UIKIT
#परिभाषय VK_USE_PLATFORM_METAL_EXT
#परिभाषय VK_USE_PLATFORM_IOS_MVK
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_WAYLAND
#परिभाषय VK_USE_PLATFORM_WAYLAND_KHR
#अन्तर्भाव "wayland/SDL_waylanddyn.h"
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_WINDOWS
#परिभाषय VK_USE_PLATFORM_WIN32_KHR
#अन्तर्भाव "../core/windows/SDL_windows.h"
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11
#परिभाषय VK_USE_PLATFORM_XLIB_KHR
#परिभाषय VK_USE_PLATFORM_XCB_KHR
#यदि_अन्तः

#परिभाषय VK_NO_PROTOTYPES
#अन्तर्भाव "./khronos/vulkan/vulkan.h"

#अन्तर्भाव <SDL3/SDL_vulkan.h>

बाह्य ध्रुव वर्ण *SDL_Vulkan_Get_परिणाम_String(Vk_परिणाम परिणाम);

बाह्य VkExtensionProperties *SDL_Vulkan_CreateInstanceExtensionsList(
    PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties,
    Uint32 *extension_गणनम्); // free returned list with SDL_free

/* Create a surface directly from a display connected to a physical device
 * using the DisplayKHR extension.
 * This needs to be passed an instance that was created with the VK_KHR_DISPLAY_EXTENSION_NAME
 * extension. */
बाह्य bool SDL_Vulkan_Display_CreateSurface(शून्य *vkGetInstanceProcAddr,
                                             VkInstance instance,
                                             ध्रुव संरचना Vk_आवण्टनम्_Callbacks *allocator,
                                             VkSurfaceKHR *surface);

/* Platform independent base function for destroying the Vulkan surface. Unlike surface
 * creation, surface destruction doesn't require platform specific extensions like
 * VK_KHR_wayland_surface, VK_KHR_android_surface or VK_EXT_metal_surface. The only
 * necessary extension is cross platform VK_KHR_surface, which is a dependency to all
 * WSI platform extensions, so we can handle surface destruction in an platform-independent
 * manner. */
बाह्य शून्य SDL_Vulkan_Destroy_Surface_आन्तरिकम्(शून्य *vkGetInstanceProcAddr,
                                               VkInstance instance,
                                               VkSurfaceKHR surface,
                                               ध्रुव संरचना Vk_आवण्टनम्_Callbacks *allocator);
#अन्यथा

// No SDL Vulkan support, just include the header for typedefs
#अन्तर्भाव <SDL3/SDL_vulkan.h>

प्रकारनिर्देश शून्य (*PFN_vkGetInstanceProcAddr)(शून्य);
प्रकारनिर्देश पूर्णाङ्क (*PFN_vkEnumerateInstanceExtensionProperties)(शून्य);

#यदि_अन्तः // SDL_VIDEO_VULKAN

#यदि_अन्तः // SDL_vulkan_internal_h_
