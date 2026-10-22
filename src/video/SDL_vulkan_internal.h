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
#నిర్వచితం_కాకపోతే SDL_vulkan_అంతర్గత_h
#నిర్వచించు SDL_vulkan_అంతర్గత_h

#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_VULKAN
#నిర్వచితమైతే SDL_VIDEO_DRIVER_ANDROID
#నిర్వచించు VK_USE_PLATFORM_ANDROID_KHR
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_OPENHARMONY
#నిర్వచించు VK_USE_PLATFORM_OHOS
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_COCOA
#నిర్వచించు VK_USE_PLATFORM_METAL_EXT
#నిర్వచించు VK_USE_PLATFORM_MACOS_MVK
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_UIKIT
#నిర్వచించు VK_USE_PLATFORM_METAL_EXT
#నిర్వచించు VK_USE_PLATFORM_IOS_MVK
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_WAYLAND
#నిర్వచించు VK_USE_PLATFORM_WAYLAND_KHR
#అన్తర్భావ "wayland/SDL_waylanddyn.h"
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_WINDOWS
#నిర్వచించు VK_USE_PLATFORM_WIN32_KHR
#అన్తర్భావ "../core/windows/SDL_windows.h"
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11
#నిర్వచించు VK_USE_PLATFORM_XLIB_KHR
#నిర్వచించు VK_USE_PLATFORM_XCB_KHR
#అయితే_ముగింపు

#నిర్వచించు VK_NO_PROTOTYPES
#అన్తర్భావ "./khronos/vulkan/vulkan.h"

#అన్తర్భావ <SDL3/SDL_vulkan.h>

బాహ్య స్థిరరాశి అక్షరం *SDL_Vulkan_Get_ఫలితం_String(Vk_ఫలితం ఫలితం);

బాహ్య VkExtensionProperties *SDL_Vulkan_CreateInstanceExtensionsList(
    PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties,
    Uint32 *extension_లెక్క); // free returned list with SDL_free

/* Create a surface directly from a display connected to a physical device
 * using the DisplayKHR extension.
 * This needs to be passed an instance that was created with the VK_KHR_DISPLAY_EXTENSION_NAME
 * extension. */
బాహ్య bool SDL_Vulkan_Display_CreateSurface(శూన్య *vkGetInstanceProcAddr,
                                             VkInstance instance,
                                             స్థిరరాశి నిర్మాణం Vk_కేటాయింపు_Callbacks *allocator,
                                             VkSurfaceKHR *surface);

/* Platform independent base function for destroying the Vulkan surface. Unlike surface
 * creation, surface destruction doesn't require platform specific extensions like
 * VK_KHR_wayland_surface, VK_KHR_android_surface or VK_EXT_metal_surface. The only
 * necessary extension is cross platform VK_KHR_surface, which is a dependency to all
 * WSI platform extensions, so we can handle surface destruction in an platform-independent
 * manner. */
బాహ్య శూన్య SDL_Vulkan_Destroy_Surface_అంతర్గత(శూన్య *vkGetInstanceProcAddr,
                                               VkInstance instance,
                                               VkSurfaceKHR surface,
                                               స్థిరరాశి నిర్మాణం Vk_కేటాయింపు_Callbacks *allocator);
#లేకపోతే

// No SDL Vulkan support, just include the header for typedefs
#అన్తర్భావ <SDL3/SDL_vulkan.h>

రకనిర్వచనం శూన్య (*PFN_vkGetInstanceProcAddr)(శూన్య);
రకనిర్వచనం పూర్ణాంకం (*PFN_vkEnumerateInstanceExtensionProperties)(శూన్య);

#అయితే_ముగింపు // SDL_VIDEO_VULKAN

#అయితే_ముగింపు // SDL_vulkan_internal_h_
