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

#समावेश "SDL_internal.h"

#अगर defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_WAYLAND)

#समावेश "../SDL_vulkan_internal.h"

#समावेश "SDL_waylandvideo.h"
#समावेश "SDL_waylandwindow.h"

#समावेश "SDL_waylandvulkan.h"

#अगर_घोषित SDL_PLATFORM_OPENBSD
#घोषणा DEFAULT_VULKAN "libvulkan.so"
#अन्यथा
#घोषणा DEFAULT_VULKAN "libvulkan.so.1"
#पूर्ण_अगर

SDL_ELF_NOTE_DLOPEN(
    "wayland-vulkan",
    "Support for Vulkan on wayland backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_SUGGESTED,
    DEFAULT_VULKAN
)

bool Wayland_Vulkan_LoadLibrary(SDL_VideoDevice *_this, स्थिर अक्षर *path)
{
    VkExtensionProperties *extensions = शून्य;
    Uint32 i, extension_गिनती = 0;
    bool hasSurfaceExtension = false;
    bool hasWaylandSurfaceExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = शून्य;
    अगर (_this->vulkan_config.loader_handle) {
        वापस SDL_SetError("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    अगर (!path) {
        path = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }
    अगर (!path) {
        path = DEFAULT_VULKAN;
    }
    _this->vulkan_config.loader_handle = SDL_LoadObject(path);
    अगर (!_this->vulkan_config.loader_handle) {
        वापस false;
    }
    SDL_strlcpy(_this->vulkan_config.loader_path, path,
                SDL_arraysize(_this->vulkan_config.loader_path));
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)SDL_LoadFunction(
        _this->vulkan_config.loader_handle, "vkGetInstanceProcAddr");
    अगर (!vkGetInstanceProcAddr) {
        जाओ fail;
    }
    _this->vulkan_config.vkGetInstanceProcAddr = (व्योम *)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties =
        (व्योम *)((PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr)(
            VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties");
    अगर (!_this->vulkan_config.vkEnumerateInstanceExtensionProperties) {
        जाओ fail;
    }
    extensions = SDL_Vulkan_CreateInstanceExtensionsList(
        (PFN_vkEnumerateInstanceExtensionProperties)
            _this->vulkan_config.vkEnumerateInstanceExtensionProperties,
        &extension_गिनती);
    अगर (!extensions) {
        जाओ fail;
    }
    क्रम (i = 0; i < extension_गिनती; i++) {
        अगर (SDL_strcmp(VK_KHR_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasSurfaceExtension = true;
        } अन्यथा अगर (SDL_strcmp(VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasWaylandSurfaceExtension = true;
        }
    }
    SDL_free(extensions);
    अगर (!hasSurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        जाओ fail;
    } अन्यथा अगर (!hasWaylandSurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME " extension");
        जाओ fail;
    }
    वापस true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = शून्य;
    वापस false;
}

व्योम Wayland_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    अगर (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = शून्य;
    }
}

अक्षर स्थिर * स्थिर *Wayland_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *गिनती)
{
    अटल स्थिर अक्षर *स्थिर extensionsForWayland[] = {
        VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME
    };

    *गिनती = SDL_arraysize(extensionsForWayland);
    वापस extensionsForWayland;
}

bool Wayland_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                                 SDL_Window *window,
                                 VkInstance instance,
                                 स्थिर काष्ठा VkAllocationCallbacks *allocator,
                                 VkSurfaceKHR *surface)
{
    SDL_Window_तथ्य *window_तथ्य = window->internal;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    PFN_vkCreateWaylandSurfaceKHR vkCreateWaylandSurfaceKHR =
        (PFN_vkCreateWaylandSurfaceKHR)vkGetInstanceProcAddr(
            instance,
            "vkCreateWaylandSurfaceKHR");
    VkWaylandSurfaceCreateInfoKHR createInfo;
    Vk_परिणाम परिणाम;

    अगर (!_this->vulkan_config.loader_handle) {
        वापस SDL_SetError("Vulkan is not loaded");
    }

    अगर (!vkCreateWaylandSurfaceKHR) {
        वापस SDL_SetError(VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME
                            " extension is not enabled in the Vulkan instance.");
    }
    SDL_zero(createInfo);
    createInfo.sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR;
    createInfo.p_अग्र = शून्य;
    createInfo.flags = 0;
    createInfo.display = window_तथ्य->wayland_तथ्य->display;
    createInfo.surface = window_तथ्य->surface;
    परिणाम = vkCreateWaylandSurfaceKHR(instance, &createInfo, allocator, surface);
    अगर (परिणाम != VK_SUCCESS) {
        वापस SDL_SetError("vkCreateWaylandSurfaceKHR failed: %s", SDL_Vulkan_Get_परिणाम_String(परिणाम));
    }
    वापस true;
}

व्योम Wayland_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                   VkInstance instance,
                                   VkSurfaceKHR surface,
                                   स्थिर काष्ठा VkAllocationCallbacks *allocator)
{
    अगर (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_DestroySurface_Internal(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

bool Wayland_Vulkan_GetPresentationSupport(SDL_VideoDevice *_this,
                                               VkInstance instance,
                                               VkPhysicalDevice physicalDevice,
                                               Uint32 queue_Family_सूचकांक)
{
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR vkGetPhysicalDeviceWaylandPresentationSupportKHR =
        (PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR)vkGetInstanceProcAddr(
            instance,
            "vkGetPhysicalDeviceWaylandPresentationSupportKHR");

    अगर (!_this->vulkan_config.loader_handle) {
        वापस SDL_SetError("Vulkan is not loaded");
    }

    अगर (!vkGetPhysicalDeviceWaylandPresentationSupportKHR) {
        वापस SDL_SetError(VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
    }

    वापस vkGetPhysicalDeviceWaylandPresentationSupportKHR(physicalDevice,
                                                            queue_Family_सूचकांक,
                                                            _this->internal->display);
}

#पूर्ण_अगर
