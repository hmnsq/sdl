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
#অন্তর্ভাব "SDL_internal.h"

#ifndef SDL_offscreenvulkan_h
#define SDL_offscreenvulkan_h

#যদি defined(SDL_VIDEO_DRIVER_OFFSCREEN) && defined(SDL_VIDEO_VULKAN)

#অন্তর্ভাব "../SDL_sysvideo.h"

বাহ্য bool OFFSCREEN_Vulkan_LoadLibrary(SDL_VideoDevice *_this, ধ্রুব বর্ণ *path);
বাহ্য শূন্য OFFSCREEN_Vulkan_UnloadLibrary(SDL_VideoDevice *_this);
বাহ্য বর্ণ ধ্রুব *ধ্রুব *OFFSCREEN_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *গুনতি);
বাহ্য bool OFFSCREEN_Vulkan_CreateSurface(SDL_VideoDevice *_this, SDL_Window *window, VkInstance instance, ধ্রুব সংরচনা VkAllocationCallbacks *allocator, VkSurfaceKHR *surface);
বাহ্য শূন্য OFFSCREEN_Vulkan_DestroySurface(SDL_VideoDevice *_this, VkInstance instance, VkSurfaceKHR surface, ধ্রুব সংরচনা VkAllocationCallbacks *allocator);

#endif // SDL_VIDEO_DRIVER_OFFSCREEN && SDL_VIDEO_VULKAN

#endif // SDL_offscreenvulkan_h
