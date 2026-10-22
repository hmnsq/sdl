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

/*
 * @author Mark Callow, www.edgewise-consulting.com. Based on Jacob Lifshay's
 * SDL_x11vulkan.h.
 */

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_waylandvulkan_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_waylandvulkan_h_

#ਅਨ੍ਤਰ੍ਭਾਵ <SDL3/SDL_vulkan.h>

#ਜੇ defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_WAYLAND)

ਬਾਹਰੀ bool Wayland_Vulkan_ਲੱਦੋ_Library(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *ਰਸਤਾ);
ਬਾਹਰੀ ਖਾਲੀ Wayland_Vulkan_UnloadLibrary(SDL_VideoDevice *_this);
ਬਾਹਰੀ ਅੱਖਰ ਅਚਲ * ਅਚਲ *Wayland_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *ਗਿਣਤੀ_2);
ਬਾਹਰੀ bool Wayland_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                                      SDL_ਖਿੜਕੀ *ਖਿੜਕੀ,
                                      VkInstance instance,
                                      ਅਚਲ ਬਣਤਰ Vk_ਵੰਡ_Callbacks *allocator,
                                      VkSurfaceKHR *surface);
ਬਾਹਰੀ ਖਾਲੀ Wayland_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                   VkInstance instance,
                                   VkSurfaceKHR surface,
                                   ਅਚਲ ਬਣਤਰ Vk_ਵੰਡ_Callbacks *allocator);
ਬਾਹਰੀ bool Wayland_Vulkan_GetPresentationSupport(SDL_VideoDevice *_this,
                                               VkInstance instance,
                                               VkPhysicalDevice physicalDevice,
                                               Uint32 ਕਤਾਰ_Family_ਸੂਚਕਾਂਕ);

#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ // SDL_waylandvulkan_h_
