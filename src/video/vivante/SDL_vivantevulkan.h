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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

/*
 * @author Wladimir J. van der Laan. Based on Jacob Lifshay's
 * SDL_x11vulkan.h and Mark Callow's SDL_vivantevulkan.h
 */

#ifndef SDL_vivantevulkan_h_
#define SDL_vivantevulkan_h_

#ಅನ್ತರ್ಭಾವ "../SDL_vulkan_internal.h"
#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"

#ಯದಿ defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_VIVANTE)

ಬಾಹ್ಯ bool VIVANTE_Vulkan_LoadLibrary(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *path);
ಬಾಹ್ಯ ಶೂನ್ಯ VIVANTE_Vulkan_UnloadLibrary(SDL_VideoDevice *_this);
ಬಾಹ್ಯ ವರ್ಣ ಧ್ರುವ * ಧ್ರುವ *VIVANTE_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *ಎಣಿಕೆ);
ಬಾಹ್ಯ bool VIVANTE_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                                 SDL_Window *window,
                                 VkInstance instance,
                                 ಧ್ರುವ ಸಂರಚನಾ VkAllocationCallbacks *allocator,
                                 VkSurfaceKHR *surface);
ಬಾಹ್ಯ ಶೂನ್ಯ VIVANTE_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                   VkInstance instance,
                                   VkSurfaceKHR surface,
                                   ಧ್ರುವ ಸಂರಚನಾ VkAllocationCallbacks *allocator);

#endif

#endif // SDL_vivantevulkan_h_
