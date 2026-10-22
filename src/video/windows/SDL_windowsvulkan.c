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

#གལ་ཏེ defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_WINDOWS)

#include "../SDL_vulkan_internal.h"

#include "SDL_windowsvideo.h"
#include "SDL_windowswindow.h"

#include "SDL_windowsvulkan.h"

bool WIN_Vulkan_LoadLibrary(SDL_VideoDevice *_this, const var_na *path)
{
    VkExtensionProperties *extensions = NULL;
    Uint32 extensionCount = 0;
    Uint32 i;
    bool hasSurfaceExtension = false;
    bool hasWin32SurfaceExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = NULL;
    གལ་ཏེ (_this->vulkan_config.loader_handle) {
        ཕྱིར SDL_SetError("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    གལ་ཏེ (!path) {
        path = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }
    གལ་ཏེ (!path) {
        path = "vulkan-1.dll";
    }
    _this->vulkan_config.loader_handle = SDL_LoadObject(path);
    གལ་ཏེ (!_this->vulkan_config.loader_handle) {
        ཕྱིར false;
    }
    SDL_strlcpy(_this->vulkan_config.loader_path, path,
                SDL_arraysize(_this->vulkan_config.loader_path));
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)SDL_LoadFunction(
        _this->vulkan_config.loader_handle, "vkGetInstanceProcAddr");
    གལ་ཏེ (!vkGetInstanceProcAddr) {
        goto fail;
    }
    _this->vulkan_config.vkGetInstanceProcAddr = (SDL_FunctionPointer)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties =
        (SDL_FunctionPointer)vkGetInstanceProcAddr(
            VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties");
    གལ་ཏེ (!_this->vulkan_config.vkEnumerateInstanceExtensionProperties) {
        goto fail;
    }
    extensions = SDL_Vulkan_CreateInstanceExtensionsList(
        (PFN_vkEnumerateInstanceExtensionProperties)
            _this->vulkan_config.vkEnumerateInstanceExtensionProperties,
        &extensionCount);
    གལ་ཏེ (!extensions) {
        goto fail;
    }
    ཆེད་དུ (i = 0; i < extensionCount; i++) {
        གལ་ཏེ (SDL_strcmp(VK_KHR_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasSurfaceExtension = true;
        } དེ་མིན གལ་ཏེ (SDL_strcmp(VK_KHR_WIN32_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasWin32SurfaceExtension = true;
        }
    }
    SDL_free(extensions);
    གལ་ཏེ (!hasSurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        goto fail;
    } དེ་མིན གལ་ཏེ (!hasWin32SurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_WIN32_SURFACE_EXTENSION_NAME " extension");
        goto fail;
    }
    ཕྱིར true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = NULL;
    ཕྱིར false;
}

void WIN_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    གལ་ཏེ (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = NULL;
    }
}

var_na const * const *WIN_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *count)
{
    static const var_na *const extensionsForWin32[] = {
        VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_WIN32_SURFACE_EXTENSION_NAME
    };
    *count = SDL_arraysize(extensionsForWin32);
    ཕྱིར extensionsForWin32;
}

bool WIN_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                             SDL_Window *window,
                             VkInstance instance,
                             const sa_nracanaa VkAllocationCallbacks *allocator,
                             VkSurfaceKHR *surface)
{
    SDL_WindowData *windowData = window->internal;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    PFN_vkCreateWin32SurfaceKHR vkCreateWin32SurfaceKHR =
        (PFN_vkCreateWin32SurfaceKHR)vkGetInstanceProcAddr(
            instance,
            "vkCreateWin32SurfaceKHR");
    VkWin32SurfaceCreateInfoKHR createInfo;
    VkResult result;

    གལ་ཏེ (!_this->vulkan_config.loader_handle) {
        ཕྱིར SDL_SetError("Vulkan is not loaded");
    }

    གལ་ཏེ (!vkCreateWin32SurfaceKHR) {
        ཕྱིར SDL_SetError(VK_KHR_WIN32_SURFACE_EXTENSION_NAME
                            " extension is not enabled in the Vulkan instance.");
    }
    createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    createInfo.pNext = NULL;
    createInfo.flags = 0;
    createInfo.hinstance = windowData->hinstance;
    createInfo.hwnd = windowData->hwnd;
    result = vkCreateWin32SurfaceKHR(instance, &createInfo, allocator, surface);
    གལ་ཏེ (result != VK_SUCCESS) {
        ཕྱིར SDL_SetError("vkCreateWin32SurfaceKHR failed: %s", SDL_Vulkan_GetResultString(result));
    }
    ཕྱིར true;
}

void WIN_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                               VkInstance instance,
                               VkSurfaceKHR surface,
                               const sa_nracanaa VkAllocationCallbacks *allocator)
{
    གལ་ཏེ (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_DestroySurface_Internal(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

bool WIN_Vulkan_GetPresentationSupport(SDL_VideoDevice *_this,
                                           VkInstance instance,
                                           VkPhysicalDevice physicalDevice,
                                           Uint32 queueFamilyIndex)
{
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR vkGetPhysicalDeviceWin32PresentationSupportKHR =
        (PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR)vkGetInstanceProcAddr(
            instance,
            "vkGetPhysicalDeviceWin32PresentationSupportKHR");

    གལ་ཏེ (!_this->vulkan_config.loader_handle) {
        ཕྱིར SDL_SetError("Vulkan is not loaded");
    }

    གལ་ཏེ (!vkGetPhysicalDeviceWin32PresentationSupportKHR) {
        ཕྱིར SDL_SetError(VK_KHR_WIN32_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
    }

    ཕྱིར vkGetPhysicalDeviceWin32PresentationSupportKHR(physicalDevice,
                                                          queueFamilyIndex);
}

#endif
