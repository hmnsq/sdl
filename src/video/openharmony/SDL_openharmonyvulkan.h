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
 * Copied from the Android implementation, which was done by Mark Callow,
 * www.edgewise-consulting.com, and originally based on Jacob Lifshay's SDL_x11vulkan.h.
 */

#अन्तर्भाव "SDL_internal.h"

#यदि_अपरिभाषितम् SDL_openharmonyvulkan_h_
#परिभाषय SDL_openharmonyvulkan_h_

#अन्तर्भाव "../SDL_vulkan_internal.h"
#अन्तर्भाव "../SDL_sysvideo.h"

#यदि defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_OPENHARMONY)

बाह्य bool OPENHARMONY_Vulkan_आरोपय_Library(SDL_VideoDevice *_this, ध्रुव वर्ण *मार्गः);
बाह्य शून्य OPENHARMONY_Vulkan_UnloadLibrary(SDL_VideoDevice *_this);
बाह्य वर्ण ध्रुव * ध्रुव *OPENHARMONY_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *गणनम्);
बाह्य bool OPENHARMONY_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                                         SDL_गवाक्षः *गवाक्षः,
                                         VkInstance instance,
                                         ध्रुव संरचना Vk_आवण्टनम्_Callbacks *allocator,
                                         VkSurfaceKHR *surface);
बाह्य शून्य OPENHARMONY_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                          VkInstance instance,
                                          VkSurfaceKHR surface,
                                          ध्रुव संरचना Vk_आवण्टनम्_Callbacks *allocator);

#यदि_अन्तः

#यदि_अन्तः // SDL_openharmonyvulkan_h_
