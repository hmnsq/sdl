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

#समावेश "SDL_internal.h"

#अगर_अघोषित SDL_waylandvulkan_h_
#घोषणा SDL_waylandvulkan_h_

#समावेश <SDL3/SDL_vulkan.h>

#अगर defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_WAYLAND)

बाह्य bool Wayland_Vulkan_LoadLibrary(SDL_VideoDevice *_this, स्थिर अक्षर *path);
बाह्य व्योम Wayland_Vulkan_UnloadLibrary(SDL_VideoDevice *_this);
बाह्य अक्षर स्थिर * स्थिर *Wayland_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *गिनती);
बाह्य bool Wayland_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                                      SDL_Window *window,
                                      VkInstance instance,
                                      स्थिर काष्ठा VkAllocationCallbacks *allocator,
                                      VkSurfaceKHR *surface);
बाह्य व्योम Wayland_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                   VkInstance instance,
                                   VkSurfaceKHR surface,
                                   स्थिर काष्ठा VkAllocationCallbacks *allocator);
बाह्य bool Wayland_Vulkan_GetPresentationSupport(SDL_VideoDevice *_this,
                                               VkInstance instance,
                                               VkPhysicalDevice physicalDevice,
                                               Uint32 queue_Family_सूचकांक);

#पूर्ण_अगर

#पूर्ण_अगर // SDL_waylandvulkan_h_
