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

#include "SDL_internal.h"

#もし defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_OPENHARMONY)

#include "../SDL_vulkan_internal.h"

#include "SDL_openharmonyvideo.h"
#include "SDL_openharmonywindow.h"

#include "SDL_openharmonyvulkan.h"


bool OPENHARMONY_Vulkan_LoadLibrary(SDL_VideoDevice *_this, const char *path)
{
    VkExtensionProperties *extensions = NULL;
    Uint32 extensionCount = 0;
    bool hasSurfaceExtension = false;
    bool hasOHOSSurfaceExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = NULL;

    もし (_this->vulkan_config.loader_handle) {
        戻る SDL_SetError("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    もし (!path) {
        path = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
        もし (!path) {
            path = "libvulkan.so";
        }
    }

    SDL_SharedObject *lib = SDL_LoadObject(path);
    _this->vulkan_config.loader_handle = lib;
    もし (!lib) {
        戻る false;
    }

    SDL_strlcpy(_this->vulkan_config.loader_path, path, sizeof (_this->vulkan_config.loader_path));
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr) SDL_LoadFunction(lib, "vkGetInstanceProcAddr");
    もし (!vkGetInstanceProcAddr) {
        goto fail;
    }

    _this->vulkan_config.vkGetInstanceProcAddr = (void *)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties = (void *)((PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr)(VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties");
    もし (!_this->vulkan_config.vkEnumerateInstanceExtensionProperties) {
        goto fail;
    }

    extensions = SDL_Vulkan_CreateInstanceExtensionsList((PFN_vkEnumerateInstanceExtensionProperties) _this->vulkan_config.vkEnumerateInstanceExtensionProperties, &extensionCount);
    もし (!extensions) {
        goto fail;
    }

    ために (Uint32 i = 0; i < extensionCount; i++) {
        もし (SDL_strcmp(VK_KHR_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasSurfaceExtension = true;
        } 否则 もし (SDL_strcmp(VK_OHOS_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasOHOSSurfaceExtension = true;
        }
    }

    SDL_free(extensions);

    もし (!hasSurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        goto fail;
    } 否则 もし (!hasOHOSSurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_OHOS_SURFACE_EXTENSION_NAME " extension");
        goto fail;
    }

    戻る true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = NULL;
    戻る false;
}

void OPENHARMONY_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    もし (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = NULL;
    }
}

char const * const *OPENHARMONY_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *count)
{
    static const char *const extensionsForOpenHarmony[] = {
        VK_KHR_SURFACE_EXTENSION_NAME, VK_OHOS_SURFACE_EXTENSION_NAME
    };
    もし (count) {
        *count = SDL_arraysize(extensionsForOpenHarmony);
    }
    戻る extensionsForOpenHarmony;
}

bool OPENHARMONY_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                                 SDL_Window *window,
                                 VkInstance instance,
                                 const struct VkAllocationCallbacks *allocator,
                                 VkSurfaceKHR *surface)
{
    SDL_WindowData *windowData = window->internal;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    PFN_vkCreateSurfaceOHOS vkCreateSurfaceOHOS = (PFN_vkCreateSurfaceOHOS ) vkGetInstanceProcAddr(instance, "vkCreateSurfaceOHOS");
    VkSurfaceCreateInfoOHOS createInfo;
    VkResult result;

    もし (!_this->vulkan_config.loader_handle) {
        戻る SDL_SetError("Vulkan is not loaded");
    }

    もし (!vkCreateSurfaceOHOS) {
        戻る SDL_SetError(VK_OHOS_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
    }

    SDL_zero(createInfo);
    createInfo.sType = VK_STRUCTURE_TYPE_SURFACE_CREATE_INFO_OHOS;
    createInfo.pNext = NULL;
    createInfo.flags = 0;
    createInfo.window = (OHNativeWindow *) windowData->native_window;
    result = vkCreateSurfaceOHOS(instance, &createInfo, allocator, surface);
    もし (result != VK_SUCCESS) {
        もし (result == VK_ERROR_NATIVE_WINDOW_IN_USE_KHR) {
            戻る SDL_SetError("vkCreateSurfaceOHOS failed: %s, was the window created with SDL_WINDOW_VULKAN?", SDL_Vulkan_GetResultString(result));
        } 否则 {
            戻る SDL_SetError("vkCreateSurfaceOHOS failed: %s", SDL_Vulkan_GetResultString(result));
        }
    }
    戻る true;
}

void OPENHARMONY_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                   VkInstance instance,
                                   VkSurfaceKHR surface,
                                   const struct VkAllocationCallbacks *allocator)
{
    もし (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_DestroySurface_Internal(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

#endif

