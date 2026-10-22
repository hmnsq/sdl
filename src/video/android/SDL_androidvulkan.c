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

#അന്തര്ഭാവ "SDL_internal.h"

#എങ്കിൽ defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_ANDROID)

#അന്തര്ഭാവ "../SDL_vulkan_internal.h"

#അന്തര്ഭാവ "SDL_androidvideo.h"
#അന്തര്ഭാവ "SDL_androidwindow.h"

#അന്തര്ഭാവ "SDL_androidvulkan.h"


bool Android_Vulkan_LoadLibrary(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *path)
{
    VkExtensionProperties *extensions = ശൂന്യ;
    Uint32 i, extension_എണ്ണം = 0;
    bool hasSurfaceExtension = false;
    bool hasAndroidSurfaceExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = ശൂന്യ;
    എങ്കിൽ (_this->vulkan_config.loader_handle) {
        തിരികെ SDL_SetError("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    എങ്കിൽ (!path) {
        path = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }
    എങ്കിൽ (!path) {
        path = "libvulkan.so";
    }
    _this->vulkan_config.loader_handle = SDL_LoadObject(path);
    എങ്കിൽ (!_this->vulkan_config.loader_handle) {
        തിരികെ false;
    }
    SDL_strlcpy(_this->vulkan_config.loader_path, path,
                SDL_arraysize(_this->vulkan_config.loader_path));
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)SDL_LoadFunction(
        _this->vulkan_config.loader_handle, "vkGetInstanceProcAddr");
    എങ്കിൽ (!vkGetInstanceProcAddr) {
        പോകുക fail;
    }
    _this->vulkan_config.vkGetInstanceProcAddr = (ശൂന്യം *)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties =
        (ശൂന്യം *)((PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr)(
            VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties");
    എങ്കിൽ (!_this->vulkan_config.vkEnumerateInstanceExtensionProperties) {
        പോകുക fail;
    }
    extensions = SDL_Vulkan_CreateInstanceExtensionsList(
        (PFN_vkEnumerateInstanceExtensionProperties)
            _this->vulkan_config.vkEnumerateInstanceExtensionProperties,
        &extension_എണ്ണം);
    എങ്കിൽ (!extensions) {
        പോകുക fail;
    }
    വേണ്ടി (i = 0; i < extension_എണ്ണം; i++) {
        എങ്കിൽ (SDL_strcmp(VK_KHR_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasSurfaceExtension = true;
        } അല്ലെങ്കിൽ എങ്കിൽ (SDL_strcmp(VK_KHR_ANDROID_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasAndroidSurfaceExtension = true;
        }
    }
    SDL_free(extensions);
    എങ്കിൽ (!hasSurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        പോകുക fail;
    } അല്ലെങ്കിൽ എങ്കിൽ (!hasAndroidSurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_ANDROID_SURFACE_EXTENSION_NAME " extension");
        പോകുക fail;
    }
    തിരികെ true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = ശൂന്യ;
    തിരികെ false;
}

ശൂന്യം Android_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    എങ്കിൽ (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = ശൂന്യ;
    }
}

അക്ഷരം സ്ഥിരം * സ്ഥിരം *Android_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *എണ്ണം)
{
    സ്ഥിതം സ്ഥിരം അക്ഷരം *സ്ഥിരം extensionsForAndroid[] = {
        VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_ANDROID_SURFACE_EXTENSION_NAME
    };
    *എണ്ണം = SDL_arraysize(extensionsForAndroid);
    തിരികെ extensionsForAndroid;
}

bool Android_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                                 SDL_Window *window,
                                 VkInstance instance,
                                 സ്ഥിരം ഘടന VkAllocationCallbacks *allocator,
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

    എങ്കിൽ (!_this->vulkan_config.loader_handle) {
        തിരികെ SDL_SetError("Vulkan is not loaded");
    }

    എങ്കിൽ (!vkCreateAndroidSurfaceKHR) {
        തിരികെ SDL_SetError(VK_KHR_ANDROID_SURFACE_EXTENSION_NAME
                            " extension is not enabled in the Vulkan instance.");
    }

    എങ്കിൽ (!windowData->native_window) {
        // passing a NULL window violates Vulkan spec
        തിരികെ SDL_SetError("Android native window is not available for surface creation, usually because of backgrounding");
    }

    SDL_zero(createInfo);
    createInfo.sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR;
    createInfo.pNext = ശൂന്യ;
    createInfo.flags = 0;
    createInfo.window = windowData->native_window;
    result = vkCreateAndroidSurfaceKHR(instance, &createInfo, allocator, surface);
    എങ്കിൽ (result != VK_SUCCESS) {
        എങ്കിൽ (result == VK_ERROR_NATIVE_WINDOW_IN_USE_KHR) {
            തിരികെ SDL_SetError("vkCreateAndroidSurfaceKHR failed: %s, was the window created with SDL_WINDOW_VULKAN?", SDL_Vulkan_GetResultString(result));
        } അല്ലെങ്കിൽ {
            തിരികെ SDL_SetError("vkCreateAndroidSurfaceKHR failed: %s", SDL_Vulkan_GetResultString(result));
        }
    }
    തിരികെ true;
}

ശൂന്യം Android_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                   VkInstance instance,
                                   VkSurfaceKHR surface,
                                   സ്ഥിരം ഘടന VkAllocationCallbacks *allocator)
{
    എങ്കിൽ (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_DestroySurface_Internal(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

#endif
