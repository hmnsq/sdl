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
 * Copied from the Android implementation, which was done by Mark Callow,
 * www.edgewise-consulting.com, and originally based on Jacob Lifshay's SDL_x11vulkan.h.
 */

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_OPENHARMONY)

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_vulkan_internal.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_openharmonyvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_openharmonywindow.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_openharmonyvulkan.h"


bool OPENHARMONY_Vulkan_ਲੱਦੋ_Library(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *ਰਸਤਾ)
{
    VkExtensionProperties *extensions = ਨਿਰਾ;
    Uint32 extension_ਗਿਣਤੀ = 0;
    bool hasSurfaceExtension = false;
    bool hasOHOSSurfaceExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = ਨਿਰਾ;

    ਜੇ (_this->vulkan_config.loader_handle) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    ਜੇ (!ਰਸਤਾ) {
        ਰਸਤਾ = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
        ਜੇ (!ਰਸਤਾ) {
            ਰਸਤਾ = "libvulkan.so";
        }
    }

    SDL_SharedObject *lib = SDL_ਲੱਦੋ_Object(ਰਸਤਾ);
    _this->vulkan_config.loader_handle = lib;
    ਜੇ (!lib) {
        ਵਾਪਸ false;
    }

    SDL_strlcpy(_this->vulkan_config.loader_ਰਸਤਾ, ਰਸਤਾ, ਆਕਾਰ (_this->vulkan_config.loader_ਰਸਤਾ));
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr) SDL_ਲੱਦੋ_Function(lib, "vkGetInstanceProcAddr");
    ਜੇ (!vkGetInstanceProcAddr) {
        ਜਾਓ fail;
    }

    _this->vulkan_config.vkGetInstanceProcAddr = (ਖਾਲੀ *)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties = (ਖਾਲੀ *)((PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr)(VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties");
    ਜੇ (!_this->vulkan_config.vkEnumerateInstanceExtensionProperties) {
        ਜਾਓ fail;
    }

    extensions = SDL_Vulkan_CreateInstanceExtensionsList((PFN_vkEnumerateInstanceExtensionProperties) _this->vulkan_config.vkEnumerateInstanceExtensionProperties, &extension_ਗਿਣਤੀ);
    ਜੇ (!extensions) {
        ਜਾਓ fail;
    }

    ਲਈ (Uint32 i = 0; i < extension_ਗਿਣਤੀ; i++) {
        ਜੇ (SDL_strcmp(VK_KHR_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasSurfaceExtension = true;
        } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(VK_OHOS_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasOHOSSurfaceExtension = true;
        }
    }

    SDL_free(extensions);

    ਜੇ (!hasSurfaceExtension) {
        SDL_ਸੈੱਟ_Error("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        ਜਾਓ fail;
    } ਨਹੀਂਤਾਂ ਜੇ (!hasOHOSSurfaceExtension) {
        SDL_ਸੈੱਟ_Error("Installed Vulkan doesn't implement the " VK_OHOS_SURFACE_EXTENSION_NAME " extension");
        ਜਾਓ fail;
    }

    ਵਾਪਸ true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = ਨਿਰਾ;
    ਵਾਪਸ false;
}

ਖਾਲੀ OPENHARMONY_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    ਜੇ (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = ਨਿਰਾ;
    }
}

ਅੱਖਰ ਅਚਲ * ਅਚਲ *OPENHARMONY_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *ਗਿਣਤੀ_2)
{
    ਸਥਿਰ ਅਚਲ ਅੱਖਰ *ਅਚਲ extensionsForOpenHarmony[] = {
        VK_KHR_SURFACE_EXTENSION_NAME, VK_OHOS_SURFACE_EXTENSION_NAME
    };
    ਜੇ (ਗਿਣਤੀ_2) {
        *ਗਿਣਤੀ_2 = SDL_arraysize(extensionsForOpenHarmony);
    }
    ਵਾਪਸ extensionsForOpenHarmony;
}

bool OPENHARMONY_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                                 SDL_ਖਿੜਕੀ *ਖਿੜਕੀ,
                                 VkInstance instance,
                                 ਅਚਲ ਬਣਤਰ Vk_ਵੰਡ_Callbacks *allocator,
                                 VkSurfaceKHR *surface)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ_ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    PFN_vkCreateSurfaceOHOS vkCreateSurfaceOHOS = (PFN_vkCreateSurfaceOHOS ) vkGetInstanceProcAddr(instance, "vkCreateSurfaceOHOS");
    VkSurfaceCreateInfoOHOS createInfo;
    Vk_ਨਤੀਜਾ ਨਤੀਜਾ;

    ਜੇ (!_this->vulkan_config.loader_handle) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Vulkan is not loaded");
    }

    ਜੇ (!vkCreateSurfaceOHOS) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error(VK_OHOS_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
    }

    SDL_zero(createInfo);
    createInfo.sType = VK_STRUCTURE_TYPE_SURFACE_CREATE_INFO_OHOS;
    createInfo.p_ਅਗਲਾ = ਨਿਰਾ;
    createInfo.flags = 0;
    createInfo.ਖਿੜਕੀ = (OHNative_ਖਿੜਕੀ *) ਖਿੜਕੀ_ਅੰਕੜੇ->native_ਖਿੜਕੀ;
    ਨਤੀਜਾ = vkCreateSurfaceOHOS(instance, &createInfo, allocator, surface);
    ਜੇ (ਨਤੀਜਾ != VK_SUCCESS) {
        ਜੇ (ਨਤੀਜਾ == VK_ERROR_NATIVE_ਖਿੜਕੀ_ਵਿੱਚ_USE_KHR) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("vkCreateSurfaceOHOS failed: %s, was the window created with SDL_WINDOW_VULKAN?", SDL_Vulkan_Get_ਨਤੀਜਾ_String(ਨਤੀਜਾ));
        } ਨਹੀਂਤਾਂ {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("vkCreateSurfaceOHOS failed: %s", SDL_Vulkan_Get_ਨਤੀਜਾ_String(ਨਤੀਜਾ));
        }
    }
    ਵਾਪਸ true;
}

ਖਾਲੀ OPENHARMONY_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                   VkInstance instance,
                                   VkSurfaceKHR surface,
                                   ਅਚਲ ਬਣਤਰ Vk_ਵੰਡ_Callbacks *allocator)
{
    ਜੇ (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_Destroy_Surface_ਅੰਦਰੂਨੀ(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

#ਜੇ_ਅੰਤ

