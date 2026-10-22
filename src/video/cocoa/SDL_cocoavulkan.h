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

#شامل "SDL_internal.h"

#اگر_غیر_تعریف_شدہ SDL_cocoavulkan_h_
#تعریف_کرو SDL_cocoavulkan_h_

#شامل "../SDL_vulkan_internal.h"
#شامل "../SDL_sysvideo.h"

#اگر defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_COCOA)

خارجی bool Cocoa_Vulkan_بھرو_Library(SDL_VideoDevice *_this, ثابت حرف *راستہ);
خارجی خالی Cocoa_Vulkan_UnloadLibrary(SDL_VideoDevice *_this);
خارجی حرف ثابت * ثابت *Cocoa_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *گنتی);
خارجی bool Cocoa_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                               SDL_کھڑکی *کھڑکی,
                               VkInstance instance,
                               ثابت ساخت Vk_تخصیص_Callbacks *allocator,
                               VkSurfaceKHR *surface);
خارجی خالی Cocoa_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                 VkInstance instance,
                                 VkSurfaceKHR surface,
                                 ثابت ساخت Vk_تخصیص_Callbacks *allocator);

#اگر_ختم

#اگر_ختم // SDL_cocoavulkan_h_
