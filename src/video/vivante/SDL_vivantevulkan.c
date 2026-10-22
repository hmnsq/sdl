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
#شامل "SDL_internal.h"

/*
 * @author Wladimir J. van der Laan. Based on Jacob Lifshay's
 * SDL_x11vulkan.c, Mark Callow's SDL_androidvulkan.c, and
 * the FSL demo framework.
 */

#اگر defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_VIVANTE)

#شامل "../SDL_vulkan_internal.h"

#شامل "SDL_vivantevideo.h"

#شامل "SDL_vivantevulkan.h"

bool VIVANTE_Vulkan_LoadLibrary(SDL_VideoDevice *_this, ثابت نویسه *path)
{
    VkExtensionProperties *extensions = پوچ;
    Uint32 i, extension_شمار = 0;
    bool hasSurfaceExtension = false;
    bool hasDisplayExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = پوچ;
    اگر (_this->vulkan_config.loader_handle) {
        بازگشت SDL_SetError("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    اگر (!path) {
        path = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }
    اگر (!path) {
        // If no path set, try Vivante fb vulkan driver explicitly
        path = "libvulkan-fb.so";
        _this->vulkan_config.loader_handle = SDL_LoadObject(path);
        اگر (!_this->vulkan_config.loader_handle) {
            // If that couldn't be loaded, fall back to default name
            path = "libvulkan.so";
            _this->vulkan_config.loader_handle = SDL_LoadObject(path);
        }
    } وگرنه {
        _this->vulkan_config.loader_handle = SDL_LoadObject(path);
    }
    اگر (!_this->vulkan_config.loader_handle) {
        بازگشت false;
    }
    SDL_strlcpy(_this->vulkan_config.loader_path, path,
                SDL_arraysize(_this->vulkan_config.loader_path));
    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vivante: Loaded vulkan driver %s", path);
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
        } وگرنه اگر (SDL_strcmp(VK_KHR_DISPLAY_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasDisplayExtension = true;
        }
    }
    SDL_free(extensions);
    اگر (!hasSurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        برو fail;
    } وگرنه اگر (!hasDisplayExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_DISPLAY_EXTENSION_NAME " extension");
        برو fail;
    }
    بازگشت true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = پوچ;
    بازگشت false;
}

تهی VIVANTE_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    اگر (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = پوچ;
    }
}

نویسه ثابت * ثابت *VIVANTE_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *شمار)
{
    ایستا ثابت نویسه *ثابت extensionsForVivante[] = {
        VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_DISPLAY_EXTENSION_NAME
    };
    *شمار = SDL_arraysize(extensionsForVivante);
    بازگشت extensionsForVivante;
}

bool VIVANTE_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                                 SDL_Window *window,
                                 VkInstance instance,
                                 ثابت ساختار VkAllocationCallbacks *allocator,
                                 VkSurfaceKHR *surface)
{
    اگر (!_this->vulkan_config.loader_handle) {
        بازگشت SDL_SetError("Vulkan is not loaded");
    }
    بازگشت SDL_Vulkan_Display_CreateSurface(_this->vulkan_config.vkGetInstanceProcAddr, instance, allocator, surface);
}

تهی VIVANTE_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                   VkInstance instance,
                                   VkSurfaceKHR surface,
                                   ثابت ساختار VkAllocationCallbacks *allocator)
{
    اگر (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_DestroySurface_Internal(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

#endif
