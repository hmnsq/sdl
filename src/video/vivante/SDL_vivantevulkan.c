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
#अन्तर्भाव "SDL_internal.h"

/*
 * @author Wladimir J. van der Laan. Based on Jacob Lifshay's
 * SDL_x11vulkan.c, Mark Callow's SDL_androidvulkan.c, and
 * the FSL demo framework.
 */

#यदि defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_VIVANTE)

#अन्तर्भाव "../SDL_vulkan_internal.h"

#अन्तर्भाव "SDL_vivantevideo.h"

#अन्तर्भाव "SDL_vivantevulkan.h"

bool VIVANTE_Vulkan_LoadLibrary(SDL_VideoDevice *_this, ध्रुव वर्ण *path)
{
    VkExtensionProperties *extensions = रिक्त;
    Uint32 i, extension_मोजणी = 0;
    bool hasSurfaceExtension = false;
    bool hasDisplayExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = रिक्त;
    यदि (_this->vulkan_config.loader_handle) {
        प्रत्यागम SDL_SetError("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    यदि (!path) {
        path = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }
    यदि (!path) {
        // If no path set, try Vivante fb vulkan driver explicitly
        path = "libvulkan-fb.so";
        _this->vulkan_config.loader_handle = SDL_LoadObject(path);
        यदि (!_this->vulkan_config.loader_handle) {
            // If that couldn't be loaded, fall back to default name
            path = "libvulkan.so";
            _this->vulkan_config.loader_handle = SDL_LoadObject(path);
        }
    } अन्यथा {
        _this->vulkan_config.loader_handle = SDL_LoadObject(path);
    }
    यदि (!_this->vulkan_config.loader_handle) {
        प्रत्यागम false;
    }
    SDL_strlcpy(_this->vulkan_config.loader_path, path,
                SDL_arraysize(_this->vulkan_config.loader_path));
    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vivante: Loaded vulkan driver %s", path);
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)SDL_LoadFunction(
        _this->vulkan_config.loader_handle, "vkGetInstanceProcAddr");
    यदि (!vkGetInstanceProcAddr) {
        गच्छ fail;
    }
    _this->vulkan_config.vkGetInstanceProcAddr = (शून्य *)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties =
        (शून्य *)((PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr)(
            VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties");
    यदि (!_this->vulkan_config.vkEnumerateInstanceExtensionProperties) {
        गच्छ fail;
    }
    extensions = SDL_Vulkan_CreateInstanceExtensionsList(
        (PFN_vkEnumerateInstanceExtensionProperties)
            _this->vulkan_config.vkEnumerateInstanceExtensionProperties,
        &extension_मोजणी);
    यदि (!extensions) {
        गच्छ fail;
    }
    प्रति (i = 0; i < extension_मोजणी; i++) {
        यदि (SDL_strcmp(VK_KHR_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasSurfaceExtension = true;
        } अन्यथा यदि (SDL_strcmp(VK_KHR_DISPLAY_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasDisplayExtension = true;
        }
    }
    SDL_free(extensions);
    यदि (!hasSurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        गच्छ fail;
    } अन्यथा यदि (!hasDisplayExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_DISPLAY_EXTENSION_NAME " extension");
        गच्छ fail;
    }
    प्रत्यागम true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = रिक्त;
    प्रत्यागम false;
}

शून्य VIVANTE_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    यदि (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = रिक्त;
    }
}

वर्ण ध्रुव * ध्रुव *VIVANTE_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *मोजणी)
{
    स्थिर ध्रुव वर्ण *ध्रुव extensionsForVivante[] = {
        VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_DISPLAY_EXTENSION_NAME
    };
    *मोजणी = SDL_arraysize(extensionsForVivante);
    प्रत्यागम extensionsForVivante;
}

bool VIVANTE_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                                 SDL_Window *window,
                                 VkInstance instance,
                                 ध्रुव संरचना VkAllocationCallbacks *allocator,
                                 VkSurfaceKHR *surface)
{
    यदि (!_this->vulkan_config.loader_handle) {
        प्रत्यागम SDL_SetError("Vulkan is not loaded");
    }
    प्रत्यागम SDL_Vulkan_Display_CreateSurface(_this->vulkan_config.vkGetInstanceProcAddr, instance, allocator, surface);
}

शून्य VIVANTE_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                   VkInstance instance,
                                   VkSurfaceKHR surface,
                                   ध्रुव संरचना VkAllocationCallbacks *allocator)
{
    यदि (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_DestroySurface_Internal(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

#endif
