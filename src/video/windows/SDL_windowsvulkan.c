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

#अगर defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_WINDOWS)

#समावेश "../SDL_vulkan_internal.h"

#समावेश "SDL_windowsvideo.h"
#समावेश "SDL_windowswindow.h"

#समावेश "SDL_windowsvulkan.h"

bool WIN_Vulkan_LoadLibrary(SDL_VideoDevice *_this, स्थिर अक्षर *path)
{
    VkExtensionProperties *extensions = शून्य;
    Uint32 extension_गिनती = 0;
    Uint32 i;
    bool hasSurfaceExtension = false;
    bool hasWin32SurfaceExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = शून्य;
    अगर (_this->vulkan_config.loader_handle) {
        वापस SDL_SetError("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    अगर (!path) {
        path = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }
    अगर (!path) {
        path = "vulkan-1.dll";
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
    _this->vulkan_config.vkGetInstanceProcAddr = (SDL_FunctionPointer)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties =
        (SDL_FunctionPointer)vkGetInstanceProcAddr(
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
        } अन्यथा अगर (SDL_strcmp(VK_KHR_WIN32_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasWin32SurfaceExtension = true;
        }
    }
    SDL_free(extensions);
    अगर (!hasSurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        जाओ fail;
    } अन्यथा अगर (!hasWin32SurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_WIN32_SURFACE_EXTENSION_NAME " extension");
        जाओ fail;
    }
    वापस true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = शून्य;
    वापस false;
}

व्योम WIN_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    अगर (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = शून्य;
    }
}

अक्षर स्थिर * स्थिर *WIN_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *गिनती)
{
    अटल स्थिर अक्षर *स्थिर extensionsForWin32[] = {
        VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_WIN32_SURFACE_EXTENSION_NAME
    };
    *गिनती = SDL_arraysize(extensionsForWin32);
    वापस extensionsForWin32;
}

bool WIN_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                             SDL_Window *window,
                             VkInstance instance,
                             स्थिर काष्ठा VkAllocationCallbacks *allocator,
                             VkSurfaceKHR *surface)
{
    SDL_Window_तथ्य *window_तथ्य = window->internal;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    PFN_vkCreateWin32SurfaceKHR vkCreateWin32SurfaceKHR =
        (PFN_vkCreateWin32SurfaceKHR)vkGetInstanceProcAddr(
            instance,
            "vkCreateWin32SurfaceKHR");
    VkWin32SurfaceCreateInfoKHR createInfo;
    Vk_परिणाम परिणाम;

    अगर (!_this->vulkan_config.loader_handle) {
        वापस SDL_SetError("Vulkan is not loaded");
    }

    अगर (!vkCreateWin32SurfaceKHR) {
        वापस SDL_SetError(VK_KHR_WIN32_SURFACE_EXTENSION_NAME
                            " extension is not enabled in the Vulkan instance.");
    }
    createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    createInfo.p_अग्र = शून्य;
    createInfo.flags = 0;
    createInfo.hinstance = window_तथ्य->hinstance;
    createInfo.hwnd = window_तथ्य->hwnd;
    परिणाम = vkCreateWin32SurfaceKHR(instance, &createInfo, allocator, surface);
    अगर (परिणाम != VK_SUCCESS) {
        वापस SDL_SetError("vkCreateWin32SurfaceKHR failed: %s", SDL_Vulkan_Get_परिणाम_String(परिणाम));
    }
    वापस true;
}

व्योम WIN_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                               VkInstance instance,
                               VkSurfaceKHR surface,
                               स्थिर काष्ठा VkAllocationCallbacks *allocator)
{
    अगर (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_DestroySurface_Internal(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

bool WIN_Vulkan_GetPresentationSupport(SDL_VideoDevice *_this,
                                           VkInstance instance,
                                           VkPhysicalDevice physicalDevice,
                                           Uint32 queue_Family_सूचकांक)
{
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR vkGetPhysicalDeviceWin32PresentationSupportKHR =
        (PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR)vkGetInstanceProcAddr(
            instance,
            "vkGetPhysicalDeviceWin32PresentationSupportKHR");

    अगर (!_this->vulkan_config.loader_handle) {
        वापस SDL_SetError("Vulkan is not loaded");
    }

    अगर (!vkGetPhysicalDeviceWin32PresentationSupportKHR) {
        वापस SDL_SetError(VK_KHR_WIN32_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
    }

    वापस vkGetPhysicalDeviceWin32PresentationSupportKHR(physicalDevice,
                                                          queue_Family_सूचकांक);
}

#पूर्ण_अगर
