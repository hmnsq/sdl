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
#അന്തര്ഭാവ "SDL_internal.h"

/*
 * @author Wladimir J. van der Laan. Based on Jacob Lifshay's
 * SDL_x11vulkan.c, Mark Callow's SDL_androidvulkan.c, and
 * the FSL demo framework.
 */

#എങ്കിൽ defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_VIVANTE)

#അന്തര്ഭാവ "../SDL_vulkan_internal.h"

#അന്തര്ഭാവ "SDL_vivantevideo.h"

#അന്തര്ഭാവ "SDL_vivantevulkan.h"

bool VIVANTE_Vulkan_LoadLibrary(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *path)
{
    VkExtensionProperties *extensions = ശൂന്യ;
    Uint32 i, extension_എണ്ണം = 0;
    bool hasSurfaceExtension = false;
    bool hasDisplayExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = ശൂന്യ;
    എങ്കിൽ (_this->vulkan_config.loader_handle) {
        തിരികെ SDL_SetError("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    എങ്കിൽ (!path) {
        path = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }
    എങ്കിൽ (!path) {
        // If no path set, try Vivante fb vulkan driver explicitly
        path = "libvulkan-fb.so";
        _this->vulkan_config.loader_handle = SDL_LoadObject(path);
        എങ്കിൽ (!_this->vulkan_config.loader_handle) {
            // If that couldn't be loaded, fall back to default name
            path = "libvulkan.so";
            _this->vulkan_config.loader_handle = SDL_LoadObject(path);
        }
    } അല്ലെങ്കിൽ {
        _this->vulkan_config.loader_handle = SDL_LoadObject(path);
    }
    എങ്കിൽ (!_this->vulkan_config.loader_handle) {
        തിരികെ false;
    }
    SDL_strlcpy(_this->vulkan_config.loader_path, path,
                SDL_arraysize(_this->vulkan_config.loader_path));
    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vivante: Loaded vulkan driver %s", path);
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)SDL_LoadFunction(
        _this->vulkan_config.loader_handle, "vkGetInstanceProcAddr");
    എങ്കിൽ (!vkGetInstanceProcAddr) {
        പോകുക fail;
    }
    _this->vulkan_config.vkGetInstanceProcAddr = (ശൂന്യം *)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties =
        (ശൂന്യം *)((PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr)(
            VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties");
    എങ്കിൽ (!_this->vulkan_config.vkEnumerateInstanceExtensionProperties) {
        പോകുക fail;
    }
    extensions = SDL_Vulkan_CreateInstanceExtensionsList(
        (PFN_vkEnumerateInstanceExtensionProperties)
            _this->vulkan_config.vkEnumerateInstanceExtensionProperties,
        &extension_എണ്ണം);
    എങ്കിൽ (!extensions) {
        പോകുക fail;
    }
    വേണ്ടി (i = 0; i < extension_എണ്ണം; i++) {
        എങ്കിൽ (SDL_strcmp(VK_KHR_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasSurfaceExtension = true;
        } അല്ലെങ്കിൽ എങ്കിൽ (SDL_strcmp(VK_KHR_DISPLAY_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasDisplayExtension = true;
        }
    }
    SDL_free(extensions);
    എങ്കിൽ (!hasSurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        പോകുക fail;
    } അല്ലെങ്കിൽ എങ്കിൽ (!hasDisplayExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_DISPLAY_EXTENSION_NAME " extension");
        പോകുക fail;
    }
    തിരികെ true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = ശൂന്യ;
    തിരികെ false;
}

ശൂന്യം VIVANTE_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    എങ്കിൽ (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = ശൂന്യ;
    }
}

അക്ഷരം സ്ഥിരം * സ്ഥിരം *VIVANTE_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *എണ്ണം)
{
    സ്ഥിതം സ്ഥിരം അക്ഷരം *സ്ഥിരം extensionsForVivante[] = {
        VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_DISPLAY_EXTENSION_NAME
    };
    *എണ്ണം = SDL_arraysize(extensionsForVivante);
    തിരികെ extensionsForVivante;
}

bool VIVANTE_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                                 SDL_Window *window,
                                 VkInstance instance,
                                 സ്ഥിരം ഘടന VkAllocationCallbacks *allocator,
                                 VkSurfaceKHR *surface)
{
    എങ്കിൽ (!_this->vulkan_config.loader_handle) {
        തിരികെ SDL_SetError("Vulkan is not loaded");
    }
    തിരികെ SDL_Vulkan_Display_CreateSurface(_this->vulkan_config.vkGetInstanceProcAddr, instance, allocator, surface);
}

ശൂന്യം VIVANTE_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                   VkInstance instance,
                                   VkSurfaceKHR surface,
                                   സ്ഥിരം ഘടന VkAllocationCallbacks *allocator)
{
    എങ്കിൽ (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_DestroySurface_Internal(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

#endif
