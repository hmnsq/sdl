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

#অন্তর্ভাব "SDL_internal.h"

#যদি defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_ANDROID)

#অন্তর্ভাব "../SDL_vulkan_internal.h"

#অন্তর্ভাব "SDL_androidvideo.h"
#অন্তর্ভাব "SDL_androidwindow.h"

#অন্তর্ভাব "SDL_androidvulkan.h"


bool Android_Vulkan_LoadLibrary(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *path)
{
    VkExtensionProperties *extensions = ফাঁকা;
    Uint32 i, extension_গুনতি = 0;
    bool hasSurfaceExtension = false;
    bool hasAndroidSurfaceExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = ফাঁকা;
    যদি (_this->vulkan_config.loader_handle) {
        ফেরত SDL_SetError("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    যদি (!path) {
        path = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }
    যদি (!path) {
        path = "libvulkan.so";
    }
    _this->vulkan_config.loader_handle = SDL_LoadObject(path);
    যদি (!_this->vulkan_config.loader_handle) {
        ফেরত false;
    }
    SDL_strlcpy(_this->vulkan_config.loader_path, path,
                SDL_arraysize(_this->vulkan_config.loader_path));
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)SDL_LoadFunction(
        _this->vulkan_config.loader_handle, "vkGetInstanceProcAddr");
    যদি (!vkGetInstanceProcAddr) {
        যাও fail;
    }
    _this->vulkan_config.vkGetInstanceProcAddr = (শূন্য *)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties =
        (শূন্য *)((PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr)(
            VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties");
    যদি (!_this->vulkan_config.vkEnumerateInstanceExtensionProperties) {
        যাও fail;
    }
    extensions = SDL_Vulkan_CreateInstanceExtensionsList(
        (PFN_vkEnumerateInstanceExtensionProperties)
            _this->vulkan_config.vkEnumerateInstanceExtensionProperties,
        &extension_গুনতি);
    যদি (!extensions) {
        যাও fail;
    }
    জন্য (i = 0; i < extension_গুনতি; i++) {
        যদি (SDL_strcmp(VK_KHR_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasSurfaceExtension = true;
        } অন্যথা যদি (SDL_strcmp(VK_KHR_ANDROID_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasAndroidSurfaceExtension = true;
        }
    }
    SDL_free(extensions);
    যদি (!hasSurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        যাও fail;
    } অন্যথা যদি (!hasAndroidSurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_ANDROID_SURFACE_EXTENSION_NAME " extension");
        যাও fail;
    }
    ফেরত true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = ফাঁকা;
    ফেরত false;
}

শূন্য Android_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    যদি (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = ফাঁকা;
    }
}

অক্ষর ধ্রুবক * ধ্রুবক *Android_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *গুনতি)
{
    স্থির ধ্রুবক অক্ষর *ধ্রুবক extensionsForAndroid[] = {
        VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_ANDROID_SURFACE_EXTENSION_NAME
    };
    *গুনতি = SDL_arraysize(extensionsForAndroid);
    ফেরত extensionsForAndroid;
}

bool Android_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                                 SDL_Window *window,
                                 VkInstance instance,
                                 ধ্রুবক কাঠামো VkAllocationCallbacks *allocator,
                                 VkSurfaceKHR *surface)
{
    SDL_Window_তথ্য *window_তথ্য = window->internal;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    PFN_vkCreateAndroidSurfaceKHR vkCreateAndroidSurfaceKHR =
        (PFN_vkCreateAndroidSurfaceKHR)vkGetInstanceProcAddr(
            instance,
            "vkCreateAndroidSurfaceKHR");
    VkAndroidSurfaceCreateInfoKHR createInfo;
    Vk_ফলাফল ফলাফল;

    যদি (!_this->vulkan_config.loader_handle) {
        ফেরত SDL_SetError("Vulkan is not loaded");
    }

    যদি (!vkCreateAndroidSurfaceKHR) {
        ফেরত SDL_SetError(VK_KHR_ANDROID_SURFACE_EXTENSION_NAME
                            " extension is not enabled in the Vulkan instance.");
    }

    যদি (!window_তথ্য->native_window) {
        // passing a NULL window violates Vulkan spec
        ফেরত SDL_SetError("Android native window is not available for surface creation, usually because of backgrounding");
    }

    SDL_zero(createInfo);
    createInfo.sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR;
    createInfo.p_পরবর্তী = ফাঁকা;
    createInfo.flags = 0;
    createInfo.window = window_তথ্য->native_window;
    ফলাফল = vkCreateAndroidSurfaceKHR(instance, &createInfo, allocator, surface);
    যদি (ফলাফল != VK_SUCCESS) {
        যদি (ফলাফল == VK_ERROR_NATIVE_WINDOW_IN_USE_KHR) {
            ফেরত SDL_SetError("vkCreateAndroidSurfaceKHR failed: %s, was the window created with SDL_WINDOW_VULKAN?", SDL_Vulkan_Get_ফলাফল_String(ফলাফল));
        } অন্যথা {
            ফেরত SDL_SetError("vkCreateAndroidSurfaceKHR failed: %s", SDL_Vulkan_Get_ফলাফল_String(ফলাফল));
        }
    }
    ফেরত true;
}

শূন্য Android_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                   VkInstance instance,
                                   VkSurfaceKHR surface,
                                   ধ্রুবক কাঠামো VkAllocationCallbacks *allocator)
{
    যদি (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_DestroySurface_Internal(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

#endif
