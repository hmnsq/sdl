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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifndef SDL_x11vulkan_h_
#define SDL_x11vulkan_h_

#ଅନ୍ତର୍ଭାଵ <SDL3/SDL_vulkan.h>

#ଯଦି defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_X11)

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା xcb_connection_t xcb_connection_t;
ପ୍ରକାରବ୍ୟାଖ୍ୟା xcb_connection_t *(*PFN_XGetXCBConnection)(Display *dpy);

ବାହ୍ୟ bool X11_Vulkan_LoadLibrary(SDL_VideoDevice *_this, ଅଚଳ ଅକ୍ଷର *path);
ବାହ୍ୟ ଶୂନ୍ୟ X11_Vulkan_UnloadLibrary(SDL_VideoDevice *_this);
ବାହ୍ୟ ଅକ୍ଷର ଅଚଳ * ଅଚଳ *X11_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *ଗଣନା_2);
ବାହ୍ୟ bool X11_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                             SDL_Window *window,
                             VkInstance instance,
                             ଅଚଳ ସଂରଚନା VkAllocationCallbacks *allocator,
                             VkSurfaceKHR *surface);
ବାହ୍ୟ ଶୂନ୍ୟ X11_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                               VkInstance instance,
                               VkSurfaceKHR surface,
                               ଅଚଳ ସଂରଚନା VkAllocationCallbacks *allocator);
ବାହ୍ୟ bool X11_Vulkan_GetPresentationSupport(SDL_VideoDevice *_this,
                                           VkInstance instance,
                                           VkPhysicalDevice physicalDevice,
                                           Uint32 queueFamilyIndex);

#endif

#endif // SDL_x11vulkan_h_
