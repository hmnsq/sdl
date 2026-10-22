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

#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ಯದಿ defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_WINDOWS)

#ಅನ್ತರ್ಭಾವ "../SDL_vulkan_internal.h"

#ಅನ್ತರ್ಭಾವ "SDL_windowsvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_windowswindow.h"

#ಅನ್ತರ್ಭಾವ "SDL_windowsvulkan.h"

bool WIN_Vulkan_LoadLibrary(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *path)
{
    VkExtensionProperties *extensions = ರಿಕ್ತ;
    Uint32 extension_ಎಣಿಕೆ = 0;
    Uint32 i;
    bool hasSurfaceExtension = false;
    bool hasWin32SurfaceExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = ರಿಕ್ತ;
    ಯದಿ (_this->vulkan_config.loader_handle) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    ಯದಿ (!path) {
        path = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }
    ಯದಿ (!path) {
        path = "vulkan-1.dll";
    }
    _this->vulkan_config.loader_handle = SDL_LoadObject(path);
    ಯದಿ (!_this->vulkan_config.loader_handle) {
        ಪ್ರತ್ಯಾಗಮ false;
    }
    SDL_strlcpy(_this->vulkan_config.loader_path, path,
                SDL_arraysize(_this->vulkan_config.loader_path));
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)SDL_LoadFunction(
        _this->vulkan_config.loader_handle, "vkGetInstanceProcAddr");
    ಯದಿ (!vkGetInstanceProcAddr) {
        ಗಚ್ಛ fail;
    }
    _this->vulkan_config.vkGetInstanceProcAddr = (SDL_FunctionPointer)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties =
        (SDL_FunctionPointer)vkGetInstanceProcAddr(
            VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties");
    ಯದಿ (!_this->vulkan_config.vkEnumerateInstanceExtensionProperties) {
        ಗಚ್ಛ fail;
    }
    extensions = SDL_Vulkan_CreateInstanceExtensionsList(
        (PFN_vkEnumerateInstanceExtensionProperties)
            _this->vulkan_config.vkEnumerateInstanceExtensionProperties,
        &extension_ಎಣಿಕೆ);
    ಯದಿ (!extensions) {
        ಗಚ್ಛ fail;
    }
    ಪ್ರತಿ (i = 0; i < extension_ಎಣಿಕೆ; i++) {
        ಯದಿ (SDL_strcmp(VK_KHR_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasSurfaceExtension = true;
        } ಅನ್ಯಥಾ ಯದಿ (SDL_strcmp(VK_KHR_WIN32_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasWin32SurfaceExtension = true;
        }
    }
    SDL_free(extensions);
    ಯದಿ (!hasSurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        ಗಚ್ಛ fail;
    } ಅನ್ಯಥಾ ಯದಿ (!hasWin32SurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_WIN32_SURFACE_EXTENSION_NAME " extension");
        ಗಚ್ಛ fail;
    }
    ಪ್ರತ್ಯಾಗಮ true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = ರಿಕ್ತ;
    ಪ್ರತ್ಯಾಗಮ false;
}

ಶೂನ್ಯ WIN_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    ಯದಿ (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = ರಿಕ್ತ;
    }
}

ವರ್ಣ ಧ್ರುವ * ಧ್ರುವ *WIN_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *ಎಣಿಕೆ)
{
    ಸ್ಥಿರ ಧ್ರುವ ವರ್ಣ *ಧ್ರುವ extensionsForWin32[] = {
        VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_WIN32_SURFACE_EXTENSION_NAME
    };
    *ಎಣಿಕೆ = SDL_arraysize(extensionsForWin32);
    ಪ್ರತ್ಯಾಗಮ extensionsForWin32;
}

bool WIN_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                             SDL_Window *window,
                             VkInstance instance,
                             ಧ್ರುವ ಸಂರಚನಾ VkAllocationCallbacks *allocator,
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

    ಯದಿ (!_this->vulkan_config.loader_handle) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Vulkan is not loaded");
    }

    ಯದಿ (!vkCreateWin32SurfaceKHR) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError(VK_KHR_WIN32_SURFACE_EXTENSION_NAME
                            " extension is not enabled in the Vulkan instance.");
    }
    createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    createInfo.pNext = ರಿಕ್ತ;
    createInfo.flags = 0;
    createInfo.hinstance = windowData->hinstance;
    createInfo.hwnd = windowData->hwnd;
    result = vkCreateWin32SurfaceKHR(instance, &createInfo, allocator, surface);
    ಯದಿ (result != VK_SUCCESS) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("vkCreateWin32SurfaceKHR failed: %s", SDL_Vulkan_GetResultString(result));
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

ಶೂನ್ಯ WIN_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                               VkInstance instance,
                               VkSurfaceKHR surface,
                               ಧ್ರುವ ಸಂರಚನಾ VkAllocationCallbacks *allocator)
{
    ಯದಿ (_this->vulkan_config.loader_handle) {
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

    ಯದಿ (!_this->vulkan_config.loader_handle) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Vulkan is not loaded");
    }

    ಯದಿ (!vkGetPhysicalDeviceWin32PresentationSupportKHR) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError(VK_KHR_WIN32_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
    }

    ಪ್ರತ್ಯಾಗಮ vkGetPhysicalDeviceWin32PresentationSupportKHR(physicalDevice,
                                                          queueFamilyIndex);
}

#endif
