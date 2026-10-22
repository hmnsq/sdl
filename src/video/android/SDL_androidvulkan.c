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

#अगर defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_ANDROID)

#समावेश "../SDL_vulkan_internal.h"

#समावेश "SDL_androidvideo.h"
#समावेश "SDL_androidwindow.h"

#समावेश "SDL_androidvulkan.h"


bool Android_Vulkan_LoadLibrary(SDL_VideoDevice *_this, स्थिर अक्षर *path)
{
    VkExtensionProperties *extensions = शून्य;
    Uint32 i, extension_गिनती = 0;
    bool hasSurfaceExtension = false;
    bool hasAndroidSurfaceExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = शून्य;
    अगर (_this->vulkan_config.loader_handle) {
        वापस SDL_SetError("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    अगर (!path) {
        path = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }
    अगर (!path) {
        path = "libvulkan.so";
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
        } अन्यथा अगर (SDL_strcmp(VK_KHR_ANDROID_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasAndroidSurfaceExtension = true;
        }
    }
    SDL_free(extensions);
    अगर (!hasSurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        जाओ fail;
    } अन्यथा अगर (!hasAndroidSurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_ANDROID_SURFACE_EXTENSION_NAME " extension");
        जाओ fail;
    }
    वापस true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = शून्य;
    वापस false;
}

व्योम Android_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    अगर (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = शून्य;
    }
}

अक्षर स्थिर * स्थिर *Android_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *गिनती)
{
    अटल स्थिर अक्षर *स्थिर extensionsForAndroid[] = {
        VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_ANDROID_SURFACE_EXTENSION_NAME
    };
    *गिनती = SDL_arraysize(extensionsForAndroid);
    वापस extensionsForAndroid;
}

bool Android_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                                 SDL_Window *window,
                                 VkInstance instance,
                                 स्थिर काष्ठा VkAllocationCallbacks *allocator,
                                 VkSurfaceKHR *surface)
{
    SDL_Window_तथ्य *window_तथ्य = window->internal;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    PFN_vkCreateAndroidSurfaceKHR vkCreateAndroidSurfaceKHR =
        (PFN_vkCreateAndroidSurfaceKHR)vkGetInstanceProcAddr(
            instance,
            "vkCreateAndroidSurfaceKHR");
    VkAndroidSurfaceCreateInfoKHR createInfo;
    Vk_परिणाम परिणाम;

    अगर (!_this->vulkan_config.loader_handle) {
        वापस SDL_SetError("Vulkan is not loaded");
    }

    अगर (!vkCreateAndroidSurfaceKHR) {
        वापस SDL_SetError(VK_KHR_ANDROID_SURFACE_EXTENSION_NAME
                            " extension is not enabled in the Vulkan instance.");
    }

    अगर (!window_तथ्य->native_window) {
        // passing a NULL window violates Vulkan spec
        वापस SDL_SetError("Android native window is not available for surface creation, usually because of backgrounding");
    }

    SDL_zero(createInfo);
    createInfo.sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR;
    createInfo.p_अग्र = शून्य;
    createInfo.flags = 0;
    createInfo.window = window_तथ्य->native_window;
    परिणाम = vkCreateAndroidSurfaceKHR(instance, &createInfo, allocator, surface);
    अगर (परिणाम != VK_SUCCESS) {
        अगर (परिणाम == VK_ERROR_NATIVE_WINDOW_IN_USE_KHR) {
            वापस SDL_SetError("vkCreateAndroidSurfaceKHR failed: %s, was the window created with SDL_WINDOW_VULKAN?", SDL_Vulkan_Get_परिणाम_String(परिणाम));
        } अन्यथा {
            वापस SDL_SetError("vkCreateAndroidSurfaceKHR failed: %s", SDL_Vulkan_Get_परिणाम_String(परिणाम));
        }
    }
    वापस true;
}

व्योम Android_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                   VkInstance instance,
                                   VkSurfaceKHR surface,
                                   स्थिर काष्ठा VkAllocationCallbacks *allocator)
{
    अगर (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_DestroySurface_Internal(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

#पूर्ण_अगर
