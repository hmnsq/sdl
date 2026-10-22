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

#অন্তর্ভাব "SDL_internal.h"

#যদি defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_OPENHARMONY)

#অন্তর্ভাব "../SDL_vulkan_internal.h"

#অন্তর্ভাব "SDL_openharmonyvideo.h"
#অন্তর্ভাব "SDL_openharmonywindow.h"

#অন্তর্ভাব "SDL_openharmonyvulkan.h"


bool OPENHARMONY_Vulkan_LoadLibrary(SDL_VideoDevice *_this, ধ্রুব বর্ণ *path)
{
    VkExtensionProperties *extensions = রিক্ত;
    Uint32 extension_গুনতি = 0;
    bool hasSurfaceExtension = false;
    bool hasOHOSSurfaceExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = রিক্ত;

    যদি (_this->vulkan_config.loader_handle) {
        প্রত্যাগম SDL_SetError("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    যদি (!path) {
        path = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
        যদি (!path) {
            path = "libvulkan.so";
        }
    }

    SDL_SharedObject *lib = SDL_LoadObject(path);
    _this->vulkan_config.loader_handle = lib;
    যদি (!lib) {
        প্রত্যাগম false;
    }

    SDL_strlcpy(_this->vulkan_config.loader_path, path, পরিমাণ (_this->vulkan_config.loader_path));
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr) SDL_LoadFunction(lib, "vkGetInstanceProcAddr");
    যদি (!vkGetInstanceProcAddr) {
        গচ্ছ fail;
    }

    _this->vulkan_config.vkGetInstanceProcAddr = (শূন্য *)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties = (শূন্য *)((PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr)(VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties");
    যদি (!_this->vulkan_config.vkEnumerateInstanceExtensionProperties) {
        গচ্ছ fail;
    }

    extensions = SDL_Vulkan_CreateInstanceExtensionsList((PFN_vkEnumerateInstanceExtensionProperties) _this->vulkan_config.vkEnumerateInstanceExtensionProperties, &extension_গুনতি);
    যদি (!extensions) {
        গচ্ছ fail;
    }

    প্রতি (Uint32 i = 0; i < extension_গুনতি; i++) {
        যদি (SDL_strcmp(VK_KHR_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasSurfaceExtension = true;
        } অন্যথা যদি (SDL_strcmp(VK_OHOS_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasOHOSSurfaceExtension = true;
        }
    }

    SDL_free(extensions);

    যদি (!hasSurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        গচ্ছ fail;
    } অন্যথা যদি (!hasOHOSSurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_OHOS_SURFACE_EXTENSION_NAME " extension");
        গচ্ছ fail;
    }

    প্রত্যাগম true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = রিক্ত;
    প্রত্যাগম false;
}

শূন্য OPENHARMONY_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    যদি (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = রিক্ত;
    }
}

বর্ণ ধ্রুব * ধ্রুব *OPENHARMONY_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *গুনতি)
{
    স্থির ধ্রুব বর্ণ *ধ্রুব extensionsForOpenHarmony[] = {
        VK_KHR_SURFACE_EXTENSION_NAME, VK_OHOS_SURFACE_EXTENSION_NAME
    };
    যদি (গুনতি) {
        *গুনতি = SDL_arraysize(extensionsForOpenHarmony);
    }
    প্রত্যাগম extensionsForOpenHarmony;
}

bool OPENHARMONY_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                                 SDL_Window *window,
                                 VkInstance instance,
                                 ধ্রুব সংরচনা VkAllocationCallbacks *allocator,
                                 VkSurfaceKHR *surface)
{
    SDL_WindowData *windowData = window->internal;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    PFN_vkCreateSurfaceOHOS vkCreateSurfaceOHOS = (PFN_vkCreateSurfaceOHOS ) vkGetInstanceProcAddr(instance, "vkCreateSurfaceOHOS");
    VkSurfaceCreateInfoOHOS createInfo;
    VkResult result;

    যদি (!_this->vulkan_config.loader_handle) {
        প্রত্যাগম SDL_SetError("Vulkan is not loaded");
    }

    যদি (!vkCreateSurfaceOHOS) {
        প্রত্যাগম SDL_SetError(VK_OHOS_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
    }

    SDL_zero(createInfo);
    createInfo.sType = VK_STRUCTURE_TYPE_SURFACE_CREATE_INFO_OHOS;
    createInfo.pNext = রিক্ত;
    createInfo.flags = 0;
    createInfo.window = (OHNativeWindow *) windowData->native_window;
    result = vkCreateSurfaceOHOS(instance, &createInfo, allocator, surface);
    যদি (result != VK_SUCCESS) {
        যদি (result == VK_ERROR_NATIVE_WINDOW_IN_USE_KHR) {
            প্রত্যাগম SDL_SetError("vkCreateSurfaceOHOS failed: %s, was the window created with SDL_WINDOW_VULKAN?", SDL_Vulkan_GetResultString(result));
        } অন্যথা {
            প্রত্যাগম SDL_SetError("vkCreateSurfaceOHOS failed: %s", SDL_Vulkan_GetResultString(result));
        }
    }
    প্রত্যাগম true;
}

শূন্য OPENHARMONY_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                   VkInstance instance,
                                   VkSurfaceKHR surface,
                                   ধ্রুব সংরচনা VkAllocationCallbacks *allocator)
{
    যদি (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_DestroySurface_Internal(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

#endif

