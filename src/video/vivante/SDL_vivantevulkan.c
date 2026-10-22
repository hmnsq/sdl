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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

/*
 * @author Wladimir J. van der Laan. Based on Jacob Lifshay's
 * SDL_x11vulkan.c, Mark Callow's SDL_androidvulkan.c, and
 * the FSL demo framework.
 */

#ਜੇ defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_VIVANTE)

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_vulkan_internal.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_vivantevideo.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_vivantevulkan.h"

bool VIVANTE_Vulkan_ਲੱਦੋ_Library(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *ਰਸਤਾ)
{
    VkExtensionProperties *extensions = ਨਿਰਾ;
    Uint32 i, extension_ਗਿਣਤੀ = 0;
    bool hasSurfaceExtension = false;
    bool hasDisplayExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = ਨਿਰਾ;
    ਜੇ (_this->vulkan_config.loader_handle) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    ਜੇ (!ਰਸਤਾ) {
        ਰਸਤਾ = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }
    ਜੇ (!ਰਸਤਾ) {
        // If no path set, try Vivante fb vulkan driver explicitly
        ਰਸਤਾ = "libvulkan-fb.so";
        _this->vulkan_config.loader_handle = SDL_ਲੱਦੋ_Object(ਰਸਤਾ);
        ਜੇ (!_this->vulkan_config.loader_handle) {
            // If that couldn't be loaded, fall back to default name
            ਰਸਤਾ = "libvulkan.so";
            _this->vulkan_config.loader_handle = SDL_ਲੱਦੋ_Object(ਰਸਤਾ);
        }
    } ਨਹੀਂਤਾਂ {
        _this->vulkan_config.loader_handle = SDL_ਲੱਦੋ_Object(ਰਸਤਾ);
    }
    ਜੇ (!_this->vulkan_config.loader_handle) {
        ਵਾਪਸ false;
    }
    SDL_strlcpy(_this->vulkan_config.loader_ਰਸਤਾ, ਰਸਤਾ,
                SDL_arraysize(_this->vulkan_config.loader_ਰਸਤਾ));
    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vivante: Loaded vulkan driver %s", ਰਸਤਾ);
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
        } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(VK_KHR_DISPLAY_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasDisplayExtension = true;
        }
    }
    SDL_free(extensions);
    ਜੇ (!hasSurfaceExtension) {
        SDL_ਸੈੱਟ_Error("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        ਜਾਓ fail;
    } ਨਹੀਂਤਾਂ ਜੇ (!hasDisplayExtension) {
        SDL_ਸੈੱਟ_Error("Installed Vulkan doesn't implement the " VK_KHR_DISPLAY_EXTENSION_NAME " extension");
        ਜਾਓ fail;
    }
    ਵਾਪਸ true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = ਨਿਰਾ;
    ਵਾਪਸ false;
}

ਖਾਲੀ VIVANTE_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    ਜੇ (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = ਨਿਰਾ;
    }
}

ਅੱਖਰ ਅਚਲ * ਅਚਲ *VIVANTE_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *ਗਿਣਤੀ_2)
{
    ਸਥਿਰ ਅਚਲ ਅੱਖਰ *ਅਚਲ extensionsForVivante[] = {
        VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_DISPLAY_EXTENSION_NAME
    };
    *ਗਿਣਤੀ_2 = SDL_arraysize(extensionsForVivante);
    ਵਾਪਸ extensionsForVivante;
}

bool VIVANTE_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                                 SDL_ਖਿੜਕੀ *ਖਿੜਕੀ,
                                 VkInstance instance,
                                 ਅਚਲ ਬਣਤਰ Vk_ਵੰਡ_Callbacks *allocator,
                                 VkSurfaceKHR *surface)
{
    ਜੇ (!_this->vulkan_config.loader_handle) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Vulkan is not loaded");
    }
    ਵਾਪਸ SDL_Vulkan_Display_CreateSurface(_this->vulkan_config.vkGetInstanceProcAddr, instance, allocator, surface);
}

ਖਾਲੀ VIVANTE_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                   VkInstance instance,
                                   VkSurfaceKHR surface,
                                   ਅਚਲ ਬਣਤਰ Vk_ਵੰਡ_Callbacks *allocator)
{
    ਜੇ (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_Destroy_Surface_ਅੰਦਰੂਨੀ(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

#ਜੇ_ਅੰਤ
