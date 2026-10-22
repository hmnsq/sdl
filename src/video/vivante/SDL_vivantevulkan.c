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
#అన్తర్భావ "SDL_internal.h"

/*
 * @author Wladimir J. van der Laan. Based on Jacob Lifshay's
 * SDL_x11vulkan.c, Mark Callow's SDL_androidvulkan.c, and
 * the FSL demo framework.
 */

#ఒకవేళ defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_VIVANTE)

#అన్తర్భావ "../SDL_vulkan_internal.h"

#అన్తర్భావ "SDL_vivantevideo.h"

#అన్తర్భావ "SDL_vivantevulkan.h"

bool VIVANTE_Vulkan_ఎక్కించు_Library(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *మార్గం)
{
    VkExtensionProperties *extensions = ఖాళీ;
    Uint32 i, extension_లెక్క = 0;
    bool hasSurfaceExtension = false;
    bool hasDisplayExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = ఖాళీ;
    ఒకవేళ (_this->vulkan_config.loader_handle) {
        తిరిగి SDL_సమితి_Error("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    ఒకవేళ (!మార్గం) {
        మార్గం = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }
    ఒకవేళ (!మార్గం) {
        // If no path set, try Vivante fb vulkan driver explicitly
        మార్గం = "libvulkan-fb.so";
        _this->vulkan_config.loader_handle = SDL_ఎక్కించు_Object(మార్గం);
        ఒకవేళ (!_this->vulkan_config.loader_handle) {
            // If that couldn't be loaded, fall back to default name
            మార్గం = "libvulkan.so";
            _this->vulkan_config.loader_handle = SDL_ఎక్కించు_Object(మార్గం);
        }
    } లేకపోతే {
        _this->vulkan_config.loader_handle = SDL_ఎక్కించు_Object(మార్గం);
    }
    ఒకవేళ (!_this->vulkan_config.loader_handle) {
        తిరిగి false;
    }
    SDL_strlcpy(_this->vulkan_config.loader_మార్గం, మార్గం,
                SDL_arraysize(_this->vulkan_config.loader_మార్గం));
    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vivante: Loaded vulkan driver %s", మార్గం);
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)SDL_ఎక్కించు_Function(
        _this->vulkan_config.loader_handle, "vkGetInstanceProcAddr");
    ఒకవేళ (!vkGetInstanceProcAddr) {
        వెళ్ళు fail;
    }
    _this->vulkan_config.vkGetInstanceProcAddr = (శూన్య *)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties =
        (శూన్య *)((PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr)(
            VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties");
    ఒకవేళ (!_this->vulkan_config.vkEnumerateInstanceExtensionProperties) {
        వెళ్ళు fail;
    }
    extensions = SDL_Vulkan_CreateInstanceExtensionsList(
        (PFN_vkEnumerateInstanceExtensionProperties)
            _this->vulkan_config.vkEnumerateInstanceExtensionProperties,
        &extension_లెక్క);
    ఒకవేళ (!extensions) {
        వెళ్ళు fail;
    }
    కొరకు (i = 0; i < extension_లెక్క; i++) {
        ఒకవేళ (SDL_strcmp(VK_KHR_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasSurfaceExtension = true;
        } లేకపోతే ఒకవేళ (SDL_strcmp(VK_KHR_DISPLAY_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasDisplayExtension = true;
        }
    }
    SDL_free(extensions);
    ఒకవేళ (!hasSurfaceExtension) {
        SDL_సమితి_Error("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        వెళ్ళు fail;
    } లేకపోతే ఒకవేళ (!hasDisplayExtension) {
        SDL_సమితి_Error("Installed Vulkan doesn't implement the " VK_KHR_DISPLAY_EXTENSION_NAME " extension");
        వెళ్ళు fail;
    }
    తిరిగి true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = ఖాళీ;
    తిరిగి false;
}

శూన్య VIVANTE_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    ఒకవేళ (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = ఖాళీ;
    }
}

అక్షరం స్థిరరాశి * స్థిరరాశి *VIVANTE_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *లెక్క)
{
    స్థిర స్థిరరాశి అక్షరం *స్థిరరాశి extensionsForVivante[] = {
        VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_DISPLAY_EXTENSION_NAME
    };
    *లెక్క = SDL_arraysize(extensionsForVivante);
    తిరిగి extensionsForVivante;
}

bool VIVANTE_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                                 SDL_కిటికీ *కిటికీ,
                                 VkInstance instance,
                                 స్థిరరాశి నిర్మాణం Vk_కేటాయింపు_Callbacks *allocator,
                                 VkSurfaceKHR *surface)
{
    ఒకవేళ (!_this->vulkan_config.loader_handle) {
        తిరిగి SDL_సమితి_Error("Vulkan is not loaded");
    }
    తిరిగి SDL_Vulkan_Display_CreateSurface(_this->vulkan_config.vkGetInstanceProcAddr, instance, allocator, surface);
}

శూన్య VIVANTE_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                   VkInstance instance,
                                   VkSurfaceKHR surface,
                                   స్థిరరాశి నిర్మాణం Vk_కేటాయింపు_Callbacks *allocator)
{
    ఒకవేళ (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_Destroy_Surface_అంతర్గత(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

#అయితే_ముగింపు
