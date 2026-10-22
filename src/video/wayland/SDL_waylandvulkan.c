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

#અન્તર્ભાવ "SDL_internal.h"

#જો defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_WAYLAND)

#અન્તર્ભાવ "../SDL_vulkan_internal.h"

#અન્તર્ભાવ "SDL_waylandvideo.h"
#અન્તર્ભાવ "SDL_waylandwindow.h"

#અન્તર્ભાવ "SDL_waylandvulkan.h"

#ifdef SDL_PLATFORM_OPENBSD
#define DEFAULT_VULKAN "libvulkan.so"
#નહીંતર
#define DEFAULT_VULKAN "libvulkan.so.1"
#endif

SDL_ELF_NOTE_DLOPEN(
    "wayland-vulkan",
    "Support for Vulkan on wayland backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_SUGGESTED,
    DEFAULT_VULKAN
)

bool Wayland_Vulkan_LoadLibrary(SDL_VideoDevice *_this, અચલ અક્ષર *path)
{
    VkExtensionProperties *extensions = ખાલી;
    Uint32 i, extension_ગણતરી = 0;
    bool hasSurfaceExtension = false;
    bool hasWaylandSurfaceExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = ખાલી;
    જો (_this->vulkan_config.loader_handle) {
        પાછા SDL_SetError("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    જો (!path) {
        path = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }
    જો (!path) {
        path = DEFAULT_VULKAN;
    }
    _this->vulkan_config.loader_handle = SDL_LoadObject(path);
    જો (!_this->vulkan_config.loader_handle) {
        પાછા false;
    }
    SDL_strlcpy(_this->vulkan_config.loader_path, path,
                SDL_arraysize(_this->vulkan_config.loader_path));
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)SDL_LoadFunction(
        _this->vulkan_config.loader_handle, "vkGetInstanceProcAddr");
    જો (!vkGetInstanceProcAddr) {
        જાઓ fail;
    }
    _this->vulkan_config.vkGetInstanceProcAddr = (શૂન્ય *)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties =
        (શૂન્ય *)((PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr)(
            VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties");
    જો (!_this->vulkan_config.vkEnumerateInstanceExtensionProperties) {
        જાઓ fail;
    }
    extensions = SDL_Vulkan_CreateInstanceExtensionsList(
        (PFN_vkEnumerateInstanceExtensionProperties)
            _this->vulkan_config.vkEnumerateInstanceExtensionProperties,
        &extension_ગણતરી);
    જો (!extensions) {
        જાઓ fail;
    }
    માટે (i = 0; i < extension_ગણતરી; i++) {
        જો (SDL_strcmp(VK_KHR_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasSurfaceExtension = true;
        } નહીંતર જો (SDL_strcmp(VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasWaylandSurfaceExtension = true;
        }
    }
    SDL_free(extensions);
    જો (!hasSurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        જાઓ fail;
    } નહીંતર જો (!hasWaylandSurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME " extension");
        જાઓ fail;
    }
    પાછા true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = ખાલી;
    પાછા false;
}

શૂન્ય Wayland_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    જો (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = ખાલી;
    }
}

અક્ષર અચલ * અચલ *Wayland_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *ગણતરી)
{
    સ્થિર અચલ અક્ષર *અચલ extensionsForWayland[] = {
        VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME
    };

    *ગણતરી = SDL_arraysize(extensionsForWayland);
    પાછા extensionsForWayland;
}

bool Wayland_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                                 SDL_Window *window,
                                 VkInstance instance,
                                 અચલ સંરચના VkAllocationCallbacks *allocator,
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

    જો (!_this->vulkan_config.loader_handle) {
        પાછા SDL_SetError("Vulkan is not loaded");
    }

    જો (!vkCreateWaylandSurfaceKHR) {
        પાછા SDL_SetError(VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME
                            " extension is not enabled in the Vulkan instance.");
    }
    SDL_zero(createInfo);
    createInfo.sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR;
    createInfo.pNext = ખાલી;
    createInfo.flags = 0;
    createInfo.display = windowData->waylandData->display;
    createInfo.surface = windowData->surface;
    result = vkCreateWaylandSurfaceKHR(instance, &createInfo, allocator, surface);
    જો (result != VK_SUCCESS) {
        પાછા SDL_SetError("vkCreateWaylandSurfaceKHR failed: %s", SDL_Vulkan_GetResultString(result));
    }
    પાછા true;
}

શૂન્ય Wayland_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                   VkInstance instance,
                                   VkSurfaceKHR surface,
                                   અચલ સંરચના VkAllocationCallbacks *allocator)
{
    જો (_this->vulkan_config.loader_handle) {
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

    જો (!_this->vulkan_config.loader_handle) {
        પાછા SDL_SetError("Vulkan is not loaded");
    }

    જો (!vkGetPhysicalDeviceWaylandPresentationSupportKHR) {
        પાછા SDL_SetError(VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
    }

    પાછા vkGetPhysicalDeviceWaylandPresentationSupportKHR(physicalDevice,
                                                            queueFamilyIndex,
                                                            _this->internal->display);
}

#endif
