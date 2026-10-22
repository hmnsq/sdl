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
#अगर_अघोषित SDL_vulkan_internal_h_
#घोषणा SDL_vulkan_internal_h_

#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_VULKAN
#अगर_घोषित SDL_VIDEO_DRIVER_ANDROID
#घोषणा VK_USE_PLATFORM_ANDROID_KHR
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_DRIVER_OPENHARMONY
#घोषणा VK_USE_PLATFORM_OHOS
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_DRIVER_COCOA
#घोषणा VK_USE_PLATFORM_METAL_EXT
#घोषणा VK_USE_PLATFORM_MACOS_MVK
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_DRIVER_UIKIT
#घोषणा VK_USE_PLATFORM_METAL_EXT
#घोषणा VK_USE_PLATFORM_IOS_MVK
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_DRIVER_WAYLAND
#घोषणा VK_USE_PLATFORM_WAYLAND_KHR
#समावेश "wayland/SDL_waylanddyn.h"
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_DRIVER_WINDOWS
#घोषणा VK_USE_PLATFORM_WIN32_KHR
#समावेश "../core/windows/SDL_windows.h"
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_DRIVER_X11
#घोषणा VK_USE_PLATFORM_XLIB_KHR
#घोषणा VK_USE_PLATFORM_XCB_KHR
#पूर्ण_अगर

#घोषणा VK_NO_PROTOTYPES
#समावेश "./khronos/vulkan/vulkan.h"

#समावेश <SDL3/SDL_vulkan.h>

बाह्य स्थिर अक्षर *SDL_Vulkan_Get_परिणाम_String(Vk_परिणाम परिणाम);

बाह्य VkExtensionProperties *SDL_Vulkan_CreateInstanceExtensionsList(
    PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties,
    Uint32 *extension_गिनती); // free returned list with SDL_free

/* Create a surface directly from a display connected to a physical device
 * using the DisplayKHR extension.
 * This needs to be passed an instance that was created with the VK_KHR_DISPLAY_EXTENSION_NAME
 * extension. */
बाह्य bool SDL_Vulkan_Display_CreateSurface(व्योम *vkGetInstanceProcAddr,
                                             VkInstance instance,
                                             स्थिर काष्ठा VkAllocationCallbacks *allocator,
                                             VkSurfaceKHR *surface);

/* Platform independent base function for destroying the Vulkan surface. Unlike surface
 * creation, surface destruction doesn't require platform specific extensions like
 * VK_KHR_wayland_surface, VK_KHR_android_surface or VK_EXT_metal_surface. The only
 * necessary extension is cross platform VK_KHR_surface, which is a dependency to all
 * WSI platform extensions, so we can handle surface destruction in an platform-independent
 * manner. */
बाह्य व्योम SDL_Vulkan_DestroySurface_Internal(व्योम *vkGetInstanceProcAddr,
                                               VkInstance instance,
                                               VkSurfaceKHR surface,
                                               स्थिर काष्ठा VkAllocationCallbacks *allocator);
#अन्यथा

// No SDL Vulkan support, just include the header for typedefs
#समावेश <SDL3/SDL_vulkan.h>

प्रकार व्योम (*PFN_vkGetInstanceProcAddr)(व्योम);
प्रकार पूर्णांक (*PFN_vkEnumerateInstanceExtensionProperties)(व्योम);

#पूर्ण_अगर // SDL_VIDEO_VULKAN

#पूर्ण_अगर // SDL_vulkan_internal_h_
