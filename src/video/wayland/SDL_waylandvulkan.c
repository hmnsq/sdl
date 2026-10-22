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

#அந்தர்பாவ "SDL_internal.h"

#எனில் defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_WAYLAND)

#அந்தர்பாவ "../SDL_vulkan_internal.h"

#அந்தர்பாவ "SDL_waylandvideo.h"
#அந்தர்பாவ "SDL_waylandwindow.h"

#அந்தர்பாவ "SDL_waylandvulkan.h"

#ifdef SDL_PLATFORM_OPENBSD
#define DEFAULT_VULKAN "libvulkan.so"
#இல்லையெனில்
#define DEFAULT_VULKAN "libvulkan.so.1"
#endif

SDL_ELF_NOTE_DLOPEN(
    "wayland-vulkan",
    "Support for Vulkan on wayland backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_SUGGESTED,
    DEFAULT_VULKAN
)

bool Wayland_Vulkan_LoadLibrary(SDL_VideoDevice *_this, மாறிலி எழுத்து *path)
{
    VkExtensionProperties *extensions = வெற்று;
    Uint32 i, extension_மொத்தம் = 0;
    bool hasSurfaceExtension = false;
    bool hasWaylandSurfaceExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = வெற்று;
    எனில் (_this->vulkan_config.loader_handle) {
        திரும்பு SDL_SetError("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    எனில் (!path) {
        path = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }
    எனில் (!path) {
        path = DEFAULT_VULKAN;
    }
    _this->vulkan_config.loader_handle = SDL_LoadObject(path);
    எனில் (!_this->vulkan_config.loader_handle) {
        திரும்பு false;
    }
    SDL_strlcpy(_this->vulkan_config.loader_path, path,
                SDL_arraysize(_this->vulkan_config.loader_path));
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)SDL_LoadFunction(
        _this->vulkan_config.loader_handle, "vkGetInstanceProcAddr");
    எனில் (!vkGetInstanceProcAddr) {
        செல் fail;
    }
    _this->vulkan_config.vkGetInstanceProcAddr = (வெறுமை *)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties =
        (வெறுமை *)((PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr)(
            VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties");
    எனில் (!_this->vulkan_config.vkEnumerateInstanceExtensionProperties) {
        செல் fail;
    }
    extensions = SDL_Vulkan_CreateInstanceExtensionsList(
        (PFN_vkEnumerateInstanceExtensionProperties)
            _this->vulkan_config.vkEnumerateInstanceExtensionProperties,
        &extension_மொத்தம்);
    எனில் (!extensions) {
        செல் fail;
    }
    க்கு (i = 0; i < extension_மொத்தம்; i++) {
        எனில் (SDL_strcmp(VK_KHR_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasSurfaceExtension = true;
        } இல்லையெனில் எனில் (SDL_strcmp(VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasWaylandSurfaceExtension = true;
        }
    }
    SDL_free(extensions);
    எனில் (!hasSurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        செல் fail;
    } இல்லையெனில் எனில் (!hasWaylandSurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME " extension");
        செல் fail;
    }
    திரும்பு true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = வெற்று;
    திரும்பு false;
}

வெறுமை Wayland_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    எனில் (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = வெற்று;
    }
}

எழுத்து மாறிலி * மாறிலி *Wayland_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *மொத்தம்)
{
    நிலையான மாறிலி எழுத்து *மாறிலி extensionsForWayland[] = {
        VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME
    };

    *மொத்தம் = SDL_arraysize(extensionsForWayland);
    திரும்பு extensionsForWayland;
}

bool Wayland_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                                 SDL_Window *window,
                                 VkInstance instance,
                                 மாறிலி கட்டமைப்பு VkAllocationCallbacks *allocator,
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

    எனில் (!_this->vulkan_config.loader_handle) {
        திரும்பு SDL_SetError("Vulkan is not loaded");
    }

    எனில் (!vkCreateWaylandSurfaceKHR) {
        திரும்பு SDL_SetError(VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME
                            " extension is not enabled in the Vulkan instance.");
    }
    SDL_zero(createInfo);
    createInfo.sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR;
    createInfo.pNext = வெற்று;
    createInfo.flags = 0;
    createInfo.display = windowData->waylandData->display;
    createInfo.surface = windowData->surface;
    result = vkCreateWaylandSurfaceKHR(instance, &createInfo, allocator, surface);
    எனில் (result != VK_SUCCESS) {
        திரும்பு SDL_SetError("vkCreateWaylandSurfaceKHR failed: %s", SDL_Vulkan_GetResultString(result));
    }
    திரும்பு true;
}

வெறுமை Wayland_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                   VkInstance instance,
                                   VkSurfaceKHR surface,
                                   மாறிலி கட்டமைப்பு VkAllocationCallbacks *allocator)
{
    எனில் (_this->vulkan_config.loader_handle) {
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

    எனில் (!_this->vulkan_config.loader_handle) {
        திரும்பு SDL_SetError("Vulkan is not loaded");
    }

    எனில் (!vkGetPhysicalDeviceWaylandPresentationSupportKHR) {
        திரும்பு SDL_SetError(VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
    }

    திரும்பு vkGetPhysicalDeviceWaylandPresentationSupportKHR(physicalDevice,
                                                            queueFamilyIndex,
                                                            _this->internal->display);
}

#endif
