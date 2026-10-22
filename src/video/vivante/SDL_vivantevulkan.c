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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

/*
 * @author Wladimir J. van der Laan. Based on Jacob Lifshay's
 * SDL_x11vulkan.c, Mark Callow's SDL_androidvulkan.c, and
 * the FSL demo framework.
 */

#ಯದಿ defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_VIVANTE)

#ಅನ್ತರ್ಭಾವ "../SDL_vulkan_internal.h"

#ಅನ್ತರ್ಭಾವ "SDL_vivantevideo.h"

#ಅನ್ತರ್ಭಾವ "SDL_vivantevulkan.h"

bool VIVANTE_Vulkan_LoadLibrary(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *path)
{
    VkExtensionProperties *extensions = ರಿಕ್ತ;
    Uint32 i, extension_ಎಣಿಕೆ = 0;
    bool hasSurfaceExtension = false;
    bool hasDisplayExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = ರಿಕ್ತ;
    ಯದಿ (_this->vulkan_config.loader_handle) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    ಯದಿ (!path) {
        path = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }
    ಯದಿ (!path) {
        // If no path set, try Vivante fb vulkan driver explicitly
        path = "libvulkan-fb.so";
        _this->vulkan_config.loader_handle = SDL_LoadObject(path);
        ಯದಿ (!_this->vulkan_config.loader_handle) {
            // If that couldn't be loaded, fall back to default name
            path = "libvulkan.so";
            _this->vulkan_config.loader_handle = SDL_LoadObject(path);
        }
    } ಅನ್ಯಥಾ {
        _this->vulkan_config.loader_handle = SDL_LoadObject(path);
    }
    ಯದಿ (!_this->vulkan_config.loader_handle) {
        ಪ್ರತ್ಯಾಗಮ false;
    }
    SDL_strlcpy(_this->vulkan_config.loader_path, path,
                SDL_arraysize(_this->vulkan_config.loader_path));
    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vivante: Loaded vulkan driver %s", path);
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)SDL_LoadFunction(
        _this->vulkan_config.loader_handle, "vkGetInstanceProcAddr");
    ಯದಿ (!vkGetInstanceProcAddr) {
        ಗಚ್ಛ fail;
    }
    _this->vulkan_config.vkGetInstanceProcAddr = (ಶೂನ್ಯ *)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties =
        (ಶೂನ್ಯ *)((PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr)(
            VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties");
    ಯದಿ (!_this->vulkan_config.vkEnumerateInstanceExtensionProperties) {
        ಗಚ್ಛ fail;
    }
    extensions = SDL_Vulkan_CreateInstanceExtensionsList(
        (PFN_vkEnumerateInstanceExtensionProperties)
            _this->vulkan_config.vkEnumerateInstanceExtensionProperties,
        &extension_ಎಣಿಕೆ);
    ಯದಿ (!extensions) {
        ಗಚ್ಛ fail;
    }
    ಪ್ರತಿ (i = 0; i < extension_ಎಣಿಕೆ; i++) {
        ಯದಿ (SDL_strcmp(VK_KHR_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasSurfaceExtension = true;
        } ಅನ್ಯಥಾ ಯದಿ (SDL_strcmp(VK_KHR_DISPLAY_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasDisplayExtension = true;
        }
    }
    SDL_free(extensions);
    ಯದಿ (!hasSurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        ಗಚ್ಛ fail;
    } ಅನ್ಯಥಾ ಯದಿ (!hasDisplayExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_DISPLAY_EXTENSION_NAME " extension");
        ಗಚ್ಛ fail;
    }
    ಪ್ರತ್ಯಾಗಮ true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = ರಿಕ್ತ;
    ಪ್ರತ್ಯಾಗಮ false;
}

ಶೂನ್ಯ VIVANTE_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    ಯದಿ (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = ರಿಕ್ತ;
    }
}

ವರ್ಣ ಧ್ರುವ * ಧ್ರುವ *VIVANTE_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *ಎಣಿಕೆ)
{
    ಸ್ಥಿರ ಧ್ರುವ ವರ್ಣ *ಧ್ರುವ extensionsForVivante[] = {
        VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_DISPLAY_EXTENSION_NAME
    };
    *ಎಣಿಕೆ = SDL_arraysize(extensionsForVivante);
    ಪ್ರತ್ಯಾಗಮ extensionsForVivante;
}

bool VIVANTE_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                                 SDL_Window *window,
                                 VkInstance instance,
                                 ಧ್ರುವ ಸಂರಚನಾ VkAllocationCallbacks *allocator,
                                 VkSurfaceKHR *surface)
{
    ಯದಿ (!_this->vulkan_config.loader_handle) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Vulkan is not loaded");
    }
    ಪ್ರತ್ಯಾಗಮ SDL_Vulkan_Display_CreateSurface(_this->vulkan_config.vkGetInstanceProcAddr, instance, allocator, surface);
}

ಶೂನ್ಯ VIVANTE_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                   VkInstance instance,
                                   VkSurfaceKHR surface,
                                   ಧ್ರುವ ಸಂರಚನಾ VkAllocationCallbacks *allocator)
{
    ಯದಿ (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_DestroySurface_Internal(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

#endif
