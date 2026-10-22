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
#समावेश "SDL_internal.h"

/*
 * @author Wladimir J. van der Laan. Based on Jacob Lifshay's
 * SDL_x11vulkan.c, Mark Callow's SDL_androidvulkan.c, and
 * the FSL demo framework.
 */

#अगर defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_VIVANTE)

#समावेश "../SDL_vulkan_internal.h"

#समावेश "SDL_vivantevideo.h"

#समावेश "SDL_vivantevulkan.h"

bool VIVANTE_Vulkan_LoadLibrary(SDL_VideoDevice *_this, स्थिर अक्षर *path)
{
    VkExtensionProperties *extensions = शून्य;
    Uint32 i, extension_गिनती = 0;
    bool hasSurfaceExtension = false;
    bool hasDisplayExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = शून्य;
    अगर (_this->vulkan_config.loader_handle) {
        वापस SDL_SetError("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    अगर (!path) {
        path = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }
    अगर (!path) {
        // If no path set, try Vivante fb vulkan driver explicitly
        path = "libvulkan-fb.so";
        _this->vulkan_config.loader_handle = SDL_LoadObject(path);
        अगर (!_this->vulkan_config.loader_handle) {
            // If that couldn't be loaded, fall back to default name
            path = "libvulkan.so";
            _this->vulkan_config.loader_handle = SDL_LoadObject(path);
        }
    } अन्यथा {
        _this->vulkan_config.loader_handle = SDL_LoadObject(path);
    }
    अगर (!_this->vulkan_config.loader_handle) {
        वापस false;
    }
    SDL_strlcpy(_this->vulkan_config.loader_path, path,
                SDL_arraysize(_this->vulkan_config.loader_path));
    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vivante: Loaded vulkan driver %s", path);
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
        } अन्यथा अगर (SDL_strcmp(VK_KHR_DISPLAY_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasDisplayExtension = true;
        }
    }
    SDL_free(extensions);
    अगर (!hasSurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        जाओ fail;
    } अन्यथा अगर (!hasDisplayExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_DISPLAY_EXTENSION_NAME " extension");
        जाओ fail;
    }
    वापस true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = शून्य;
    वापस false;
}

व्योम VIVANTE_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    अगर (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = शून्य;
    }
}

अक्षर स्थिर * स्थिर *VIVANTE_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *गिनती)
{
    अटल स्थिर अक्षर *स्थिर extensionsForVivante[] = {
        VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_DISPLAY_EXTENSION_NAME
    };
    *गिनती = SDL_arraysize(extensionsForVivante);
    वापस extensionsForVivante;
}

bool VIVANTE_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                                 SDL_Window *window,
                                 VkInstance instance,
                                 स्थिर काष्ठा VkAllocationCallbacks *allocator,
                                 VkSurfaceKHR *surface)
{
    अगर (!_this->vulkan_config.loader_handle) {
        वापस SDL_SetError("Vulkan is not loaded");
    }
    वापस SDL_Vulkan_Display_CreateSurface(_this->vulkan_config.vkGetInstanceProcAddr, instance, allocator, surface);
}

व्योम VIVANTE_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                   VkInstance instance,
                                   VkSurfaceKHR surface,
                                   स्थिर काष्ठा VkAllocationCallbacks *allocator)
{
    अगर (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_DestroySurface_Internal(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

#पूर्ण_अगर
