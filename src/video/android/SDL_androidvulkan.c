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
 * SDL_x11vulkan.c.
 */

#include "SDL_internal.h"

#ᱡᱩᱫᱤ defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_ANDROID)

#include "../SDL_vulkan_internal.h"

#include "SDL_androidvideo.h"
#include "SDL_androidwindow.h"

#include "SDL_androidvulkan.h"


bool Android_Vulkan_LoadLibrary(SDL_VideoDevice *_this, const var_na *path)
{
    VkExtensionProperties *extensions = NULL;
    Uint32 i, extensionCount = 0;
    bool hasSurfaceExtension = false;
    bool hasAndroidSurfaceExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = NULL;
    ᱡᱩᱫᱤ (_this->vulkan_config.loader_handle) {
        ᱨᱩᱣᱟᱹᱲ SDL_SetError("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    ᱡᱩᱫᱤ (!path) {
        path = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }
    ᱡᱩᱫᱤ (!path) {
        path = "libvulkan.so";
    }
    _this->vulkan_config.loader_handle = SDL_LoadObject(path);
    ᱡᱩᱫᱤ (!_this->vulkan_config.loader_handle) {
        ᱨᱩᱣᱟᱹᱲ false;
    }
    SDL_strlcpy(_this->vulkan_config.loader_path, path,
                SDL_arraysize(_this->vulkan_config.loader_path));
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)SDL_LoadFunction(
        _this->vulkan_config.loader_handle, "vkGetInstanceProcAddr");
    ᱡᱩᱫᱤ (!vkGetInstanceProcAddr) {
        goto fail;
    }
    _this->vulkan_config.vkGetInstanceProcAddr = (void *)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties =
        (void *)((PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr)(
            VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties");
    ᱡᱩᱫᱤ (!_this->vulkan_config.vkEnumerateInstanceExtensionProperties) {
        goto fail;
    }
    extensions = SDL_Vulkan_CreateInstanceExtensionsList(
        (PFN_vkEnumerateInstanceExtensionProperties)
            _this->vulkan_config.vkEnumerateInstanceExtensionProperties,
        &extensionCount);
    ᱡᱩᱫᱤ (!extensions) {
        goto fail;
    }
    for (i = 0; i < extensionCount; i++) {
        ᱡᱩᱫᱤ (SDL_strcmp(VK_KHR_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasSurfaceExtension = true;
        } ᱵᱟᱝ ᱡᱩᱫᱤ (SDL_strcmp(VK_KHR_ANDROID_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasAndroidSurfaceExtension = true;
        }
    }
    SDL_free(extensions);
    ᱡᱩᱫᱤ (!hasSurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        goto fail;
    } ᱵᱟᱝ ᱡᱩᱫᱤ (!hasAndroidSurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_ANDROID_SURFACE_EXTENSION_NAME " extension");
        goto fail;
    }
    ᱨᱩᱣᱟᱹᱲ true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = NULL;
    ᱨᱩᱣᱟᱹᱲ false;
}

void Android_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    ᱡᱩᱫᱤ (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = NULL;
    }
}

var_na const * const *Android_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *count)
{
    static const var_na *const extensionsForAndroid[] = {
        VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_ANDROID_SURFACE_EXTENSION_NAME
    };
    *count = SDL_arraysize(extensionsForAndroid);
    ᱨᱩᱣᱟᱹᱲ extensionsForAndroid;
}

bool Android_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                                 SDL_Window *window,
                                 VkInstance instance,
                                 const sa_nracanaa VkAllocationCallbacks *allocator,
                                 VkSurfaceKHR *surface)
{
    SDL_WindowData *windowData = window->internal;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    PFN_vkCreateAndroidSurfaceKHR vkCreateAndroidSurfaceKHR =
        (PFN_vkCreateAndroidSurfaceKHR)vkGetInstanceProcAddr(
            instance,
            "vkCreateAndroidSurfaceKHR");
    VkAndroidSurfaceCreateInfoKHR createInfo;
    VkResult result;

    ᱡᱩᱫᱤ (!_this->vulkan_config.loader_handle) {
        ᱨᱩᱣᱟᱹᱲ SDL_SetError("Vulkan is not loaded");
    }

    ᱡᱩᱫᱤ (!vkCreateAndroidSurfaceKHR) {
        ᱨᱩᱣᱟᱹᱲ SDL_SetError(VK_KHR_ANDROID_SURFACE_EXTENSION_NAME
                            " extension is not enabled in the Vulkan instance.");
    }

    ᱡᱩᱫᱤ (!windowData->native_window) {
        // passing a NULL window violates Vulkan spec
        ᱨᱩᱣᱟᱹᱲ SDL_SetError("Android native window is not available for surface creation, usually because of backgrounding");
    }

    SDL_zero(createInfo);
    createInfo.sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR;
    createInfo.pNext = NULL;
    createInfo.flags = 0;
    createInfo.window = windowData->native_window;
    result = vkCreateAndroidSurfaceKHR(instance, &createInfo, allocator, surface);
    ᱡᱩᱫᱤ (result != VK_SUCCESS) {
        ᱡᱩᱫᱤ (result == VK_ERROR_NATIVE_WINDOW_IN_USE_KHR) {
            ᱨᱩᱣᱟᱹᱲ SDL_SetError("vkCreateAndroidSurfaceKHR failed: %s, was the window created with SDL_WINDOW_VULKAN?", SDL_Vulkan_GetResultString(result));
        } ᱵᱟᱝ {
            ᱨᱩᱣᱟᱹᱲ SDL_SetError("vkCreateAndroidSurfaceKHR failed: %s", SDL_Vulkan_GetResultString(result));
        }
    }
    ᱨᱩᱣᱟᱹᱲ true;
}

void Android_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                   VkInstance instance,
                                   VkSurfaceKHR surface,
                                   const sa_nracanaa VkAllocationCallbacks *allocator)
{
    ᱡᱩᱫᱤ (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_DestroySurface_Internal(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

#endif
