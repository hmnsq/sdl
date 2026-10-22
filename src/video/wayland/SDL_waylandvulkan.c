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

#شامل "SDL_internal.h"

#اگر defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_WAYLAND)

#شامل "../SDL_vulkan_internal.h"

#شامل "SDL_waylandvideo.h"
#شامل "SDL_waylandwindow.h"

#شامل "SDL_waylandvulkan.h"

#ifdef SDL_PLATFORM_OPENBSD
#define DEFAULT_VULKAN "libvulkan.so"
#وگرنه
#define DEFAULT_VULKAN "libvulkan.so.1"
#endif

SDL_ELF_NOTE_DLOPEN(
    "wayland-vulkan",
    "Support for Vulkan on wayland backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_SUGGESTED,
    DEFAULT_VULKAN
)

bool Wayland_Vulkan_LoadLibrary(SDL_VideoDevice *_this, ثابت نویسه *path)
{
    VkExtensionProperties *extensions = پوچ;
    Uint32 i, extension_شمار = 0;
    bool hasSurfaceExtension = false;
    bool hasWaylandSurfaceExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = پوچ;
    اگر (_this->vulkan_config.loader_handle) {
        بازگشت SDL_SetError("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    اگر (!path) {
        path = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }
    اگر (!path) {
        path = DEFAULT_VULKAN;
    }
    _this->vulkan_config.loader_handle = SDL_LoadObject(path);
    اگر (!_this->vulkan_config.loader_handle) {
        بازگشت false;
    }
    SDL_strlcpy(_this->vulkan_config.loader_path, path,
                SDL_arraysize(_this->vulkan_config.loader_path));
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)SDL_LoadFunction(
        _this->vulkan_config.loader_handle, "vkGetInstanceProcAddr");
    اگر (!vkGetInstanceProcAddr) {
        برو fail;
    }
    _this->vulkan_config.vkGetInstanceProcAddr = (تهی *)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties =
        (تهی *)((PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr)(
            VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties");
    اگر (!_this->vulkan_config.vkEnumerateInstanceExtensionProperties) {
        برو fail;
    }
    extensions = SDL_Vulkan_CreateInstanceExtensionsList(
        (PFN_vkEnumerateInstanceExtensionProperties)
            _this->vulkan_config.vkEnumerateInstanceExtensionProperties,
        &extension_شمار);
    اگر (!extensions) {
        برو fail;
    }
    برای (i = 0; i < extension_شمار; i++) {
        اگر (SDL_strcmp(VK_KHR_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasSurfaceExtension = true;
        } وگرنه اگر (SDL_strcmp(VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasWaylandSurfaceExtension = true;
        }
    }
    SDL_free(extensions);
    اگر (!hasSurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        برو fail;
    } وگرنه اگر (!hasWaylandSurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME " extension");
        برو fail;
    }
    بازگشت true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = پوچ;
    بازگشت false;
}

تهی Wayland_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    اگر (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = پوچ;
    }
}

نویسه ثابت * ثابت *Wayland_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *شمار)
{
    ایستا ثابت نویسه *ثابت extensionsForWayland[] = {
        VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME
    };

    *شمار = SDL_arraysize(extensionsForWayland);
    بازگشت extensionsForWayland;
}

bool Wayland_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                                 SDL_Window *window,
                                 VkInstance instance,
                                 ثابت ساختار VkAllocationCallbacks *allocator,
                                 VkSurfaceKHR *surface)
{
    SDL_WindowData *windowData = window->internal;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    PFN_vkCreateWaylandSurfaceKHR vkCreateWaylandSurfaceKHR =
        (PFN_vkCreateWaylandSurfaceKHR)vkGetInstanceProcAddr(
            instance,
            "vkCreateWaylandSurfaceKHR");
    VkWaylandSurfaceCreateInfoKHR createInfo;
    VkResult result;

    اگر (!_this->vulkan_config.loader_handle) {
        بازگشت SDL_SetError("Vulkan is not loaded");
    }

    اگر (!vkCreateWaylandSurfaceKHR) {
        بازگشت SDL_SetError(VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME
                            " extension is not enabled in the Vulkan instance.");
    }
    SDL_zero(createInfo);
    createInfo.sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR;
    createInfo.pNext = پوچ;
    createInfo.flags = 0;
    createInfo.display = windowData->waylandData->display;
    createInfo.surface = windowData->surface;
    result = vkCreateWaylandSurfaceKHR(instance, &createInfo, allocator, surface);
    اگر (result != VK_SUCCESS) {
        بازگشت SDL_SetError("vkCreateWaylandSurfaceKHR failed: %s", SDL_Vulkan_GetResultString(result));
    }
    بازگشت true;
}

تهی Wayland_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                   VkInstance instance,
                                   VkSurfaceKHR surface,
                                   ثابت ساختار VkAllocationCallbacks *allocator)
{
    اگر (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_DestroySurface_Internal(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

bool Wayland_Vulkan_GetPresentationSupport(SDL_VideoDevice *_this,
                                               VkInstance instance,
                                               VkPhysicalDevice physicalDevice,
                                               Uint32 queueFamilyIndex)
{
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR vkGetPhysicalDeviceWaylandPresentationSupportKHR =
        (PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR)vkGetInstanceProcAddr(
            instance,
            "vkGetPhysicalDeviceWaylandPresentationSupportKHR");

    اگر (!_this->vulkan_config.loader_handle) {
        بازگشت SDL_SetError("Vulkan is not loaded");
    }

    اگر (!vkGetPhysicalDeviceWaylandPresentationSupportKHR) {
        بازگشت SDL_SetError(VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
    }

    بازگشت vkGetPhysicalDeviceWaylandPresentationSupportKHR(physicalDevice,
                                                            queueFamilyIndex,
                                                            _this->internal->display);
}

#endif
