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

#అన్తర్భావ "SDL_internal.h"

#నిర్వచితం_కాకపోతే SDL_waylandvulkan_h_
#నిర్వచించు SDL_waylandvulkan_h_

#అన్తర్భావ <SDL3/SDL_vulkan.h>

#ఒకవేళ defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_WAYLAND)

బాహ్య bool Wayland_Vulkan_ఎక్కించు_Library(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *మార్గం);
బాహ్య శూన్య Wayland_Vulkan_UnloadLibrary(SDL_VideoDevice *_this);
బాహ్య అక్షరం స్థిరరాశి * స్థిరరాశి *Wayland_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *లెక్క);
బాహ్య bool Wayland_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                                      SDL_కిటికీ *కిటికీ,
                                      VkInstance instance,
                                      స్థిరరాశి నిర్మాణం Vk_కేటాయింపు_Callbacks *allocator,
                                      VkSurfaceKHR *surface);
బాహ్య శూన్య Wayland_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                   VkInstance instance,
                                   VkSurfaceKHR surface,
                                   స్థిరరాశి నిర్మాణం Vk_కేటాయింపు_Callbacks *allocator);
బాహ్య bool Wayland_Vulkan_GetPresentationSupport(SDL_VideoDevice *_this,
                                               VkInstance instance,
                                               VkPhysicalDevice physicalDevice,
                                               Uint32 వరుస_Family_సూచీ);

#అయితే_ముగింపు

#అయితే_ముగింపు // SDL_waylandvulkan_h_
