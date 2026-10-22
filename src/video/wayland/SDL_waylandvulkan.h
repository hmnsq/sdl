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

#ضمن "SDL_internal.h"

#که_نه_تعریف_شوی SDL_waylandvulkan_h_
#تعریف_کړه SDL_waylandvulkan_h_

#ضمن <SDL3/SDL_vulkan.h>

#إذا defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_WAYLAND)

خارجي bool Wayland_Vulkan_بارول_Library(SDL_VideoDevice *_this, ثابت حرف *لار);
خارجي فراغ Wayland_Vulkan_UnloadLibrary(SDL_VideoDevice *_this);
خارجي حرف ثابت * ثابت *Wayland_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *شمېر);
خارجي bool Wayland_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                                      SDL_کړکۍ *کړکۍ,
                                      VkInstance instance,
                                      ثابت بنية Vk_ویش_Callbacks *allocator,
                                      VkSurfaceKHR *surface);
خارجي فراغ Wayland_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                   VkInstance instance,
                                   VkSurfaceKHR surface,
                                   ثابت بنية Vk_ویش_Callbacks *allocator);
خارجي bool Wayland_Vulkan_GetPresentationSupport(SDL_VideoDevice *_this,
                                               VkInstance instance,
                                               VkPhysicalDevice physicalDevice,
                                               Uint32 کتار_Family_شاخص);

#د_که_پای

#د_که_پای // SDL_waylandvulkan_h_
