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

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_ANDROID)

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_vulkan_internal.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_androidvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_androidwindow.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_androidvulkan.h"


bool Android_Vulkan_ਲੱਦੋ_Library(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *ਰਸਤਾ)
{
    VkExtensionProperties *extensions = ਨਿਰਾ;
    Uint32 i, extension_ਗਿਣਤੀ = 0;
    bool hasSurfaceExtension = false;
    bool hasAndroidSurfaceExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = ਨਿਰਾ;
    ਜੇ (_this->vulkan_config.loader_handle) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    ਜੇ (!ਰਸਤਾ) {
        ਰਸਤਾ = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }
    ਜੇ (!ਰਸਤਾ) {
        ਰਸਤਾ = "libvulkan.so";
    }
    _this->vulkan_config.loader_handle = SDL_ਲੱਦੋ_Object(ਰਸਤਾ);
    ਜੇ (!_this->vulkan_config.loader_handle) {
        ਵਾਪਸ false;
    }
    SDL_strlcpy(_this->vulkan_config.loader_ਰਸਤਾ, ਰਸਤਾ,
                SDL_arraysize(_this->vulkan_config.loader_ਰਸਤਾ));
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)SDL_ਲੱਦੋ_Function(
        _this->vulkan_config.loader_handle, "vkGetInstanceProcAddr");
    ਜੇ (!vkGetInstanceProcAddr) {
        ਜਾਓ fail;
    }
    _this->vulkan_config.vkGetInstanceProcAddr = (ਖਾਲੀ *)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties =
        (ਖਾਲੀ *)((PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr)(
            VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties");
    ਜੇ (!_this->vulkan_config.vkEnumerateInstanceExtensionProperties) {
        ਜਾਓ fail;
    }
    extensions = SDL_Vulkan_CreateInstanceExtensionsList(
        (PFN_vkEnumerateInstanceExtensionProperties)
            _this->vulkan_config.vkEnumerateInstanceExtensionProperties,
        &extension_ਗਿਣਤੀ);
    ਜੇ (!extensions) {
        ਜਾਓ fail;
    }
    ਲਈ (i = 0; i < extension_ਗਿਣਤੀ; i++) {
        ਜੇ (SDL_strcmp(VK_KHR_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasSurfaceExtension = true;
        } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(VK_KHR_ANDROID_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasAndroidSurfaceExtension = true;
        }
    }
    SDL_free(extensions);
    ਜੇ (!hasSurfaceExtension) {
        SDL_ਸੈੱਟ_Error("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        ਜਾਓ fail;
    } ਨਹੀਂਤਾਂ ਜੇ (!hasAndroidSurfaceExtension) {
        SDL_ਸੈੱਟ_Error("Installed Vulkan doesn't implement the " VK_KHR_ANDROID_SURFACE_EXTENSION_NAME " extension");
        ਜਾਓ fail;
    }
    ਵਾਪਸ true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = ਨਿਰਾ;
    ਵਾਪਸ false;
}

ਖਾਲੀ Android_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    ਜੇ (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = ਨਿਰਾ;
    }
}

ਅੱਖਰ ਅਚਲ * ਅਚਲ *Android_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *ਗਿਣਤੀ_2)
{
    ਸਥਿਰ ਅਚਲ ਅੱਖਰ *ਅਚਲ extensionsForAndroid[] = {
        VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_ANDROID_SURFACE_EXTENSION_NAME
    };
    *ਗਿਣਤੀ_2 = SDL_arraysize(extensionsForAndroid);
    ਵਾਪਸ extensionsForAndroid;
}

bool Android_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                                 SDL_ਖਿੜਕੀ *ਖਿੜਕੀ,
                                 VkInstance instance,
                                 ਅਚਲ ਬਣਤਰ Vk_ਵੰਡ_Callbacks *allocator,
                                 VkSurfaceKHR *surface)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ_ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    PFN_vkCreateAndroidSurfaceKHR vkCreateAndroidSurfaceKHR =
        (PFN_vkCreateAndroidSurfaceKHR)vkGetInstanceProcAddr(
            instance,
            "vkCreateAndroidSurfaceKHR");
    VkAndroidSurfaceCreateInfoKHR createInfo;
    Vk_ਨਤੀਜਾ ਨਤੀਜਾ;

    ਜੇ (!_this->vulkan_config.loader_handle) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Vulkan is not loaded");
    }

    ਜੇ (!vkCreateAndroidSurfaceKHR) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error(VK_KHR_ANDROID_SURFACE_EXTENSION_NAME
                            " extension is not enabled in the Vulkan instance.");
    }

    ਜੇ (!ਖਿੜਕੀ_ਅੰਕੜੇ->native_ਖਿੜਕੀ) {
        // passing a NULL window violates Vulkan spec
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Android native window is not available for surface creation, usually because of backgrounding");
    }

    SDL_zero(createInfo);
    createInfo.sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR;
    createInfo.p_ਅਗਲਾ = ਨਿਰਾ;
    createInfo.flags = 0;
    createInfo.ਖਿੜਕੀ = ਖਿੜਕੀ_ਅੰਕੜੇ->native_ਖਿੜਕੀ;
    ਨਤੀਜਾ = vkCreateAndroidSurfaceKHR(instance, &createInfo, allocator, surface);
    ਜੇ (ਨਤੀਜਾ != VK_SUCCESS) {
        ਜੇ (ਨਤੀਜਾ == VK_ERROR_NATIVE_ਖਿੜਕੀ_ਵਿੱਚ_USE_KHR) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("vkCreateAndroidSurfaceKHR failed: %s, was the window created with SDL_WINDOW_VULKAN?", SDL_Vulkan_Get_ਨਤੀਜਾ_String(ਨਤੀਜਾ));
        } ਨਹੀਂਤਾਂ {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("vkCreateAndroidSurfaceKHR failed: %s", SDL_Vulkan_Get_ਨਤੀਜਾ_String(ਨਤੀਜਾ));
        }
    }
    ਵਾਪਸ true;
}

ਖਾਲੀ Android_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                   VkInstance instance,
                                   VkSurfaceKHR surface,
                                   ਅਚਲ ਬਣਤਰ Vk_ਵੰਡ_Callbacks *allocator)
{
    ਜੇ (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_Destroy_Surface_ਅੰਦਰੂਨੀ(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

#ਜੇ_ਅੰਤ
