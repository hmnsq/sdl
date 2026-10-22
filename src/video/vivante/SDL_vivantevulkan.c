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

bool VIVANTE_Vulkan_بھرو_Library(SDL_VideoDevice *_this, ثابت حرف *راستہ)
{
    VkExtensionProperties *extensions = تہی;
    Uint32 i, extension_گنتی = 0;
    bool hasSurfaceExtension = false;
    bool hasDisplayExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = تہی;
    اگر (_this->vulkan_config.loader_handle) {
        واپس SDL_سیٹ_Error("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    اگر (!راستہ) {
        راستہ = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }
    اگر (!راستہ) {
        // If no path set, try Vivante fb vulkan driver explicitly
        راستہ = "libvulkan-fb.so";
        _this->vulkan_config.loader_handle = SDL_بھرو_Object(راستہ);
        اگر (!_this->vulkan_config.loader_handle) {
            // If that couldn't be loaded, fall back to default name
            راستہ = "libvulkan.so";
            _this->vulkan_config.loader_handle = SDL_بھرو_Object(راستہ);
        }
    } ورنہ {
        _this->vulkan_config.loader_handle = SDL_بھرو_Object(راستہ);
    }
    اگر (!_this->vulkan_config.loader_handle) {
        واپس false;
    }
    SDL_strlcpy(_this->vulkan_config.loader_راستہ, راستہ,
                SDL_arraysize(_this->vulkan_config.loader_راستہ));
    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vivante: Loaded vulkan driver %s", راستہ);
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)SDL_بھرو_Function(
        _this->vulkan_config.loader_handle, "vkGetInstanceProcAddr");
    اگر (!vkGetInstanceProcAddr) {
        جاؤ fail;
    }
    _this->vulkan_config.vkGetInstanceProcAddr = (خالی *)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties =
        (خالی *)((PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr)(
            VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties");
    اگر (!_this->vulkan_config.vkEnumerateInstanceExtensionProperties) {
        جاؤ fail;
    }
    extensions = SDL_Vulkan_CreateInstanceExtensionsList(
        (PFN_vkEnumerateInstanceExtensionProperties)
            _this->vulkan_config.vkEnumerateInstanceExtensionProperties,
        &extension_گنتی);
    اگر (!extensions) {
        جاؤ fail;
    }
    برائے (i = 0; i < extension_گنتی; i++) {
        اگر (SDL_strcmp(VK_KHR_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasSurfaceExtension = true;
        } ورنہ اگر (SDL_strcmp(VK_KHR_DISPLAY_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasDisplayExtension = true;
        }
    }
    SDL_free(extensions);
    اگر (!hasSurfaceExtension) {
        SDL_سیٹ_Error("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        جاؤ fail;
    } ورنہ اگر (!hasDisplayExtension) {
        SDL_سیٹ_Error("Installed Vulkan doesn't implement the " VK_KHR_DISPLAY_EXTENSION_NAME " extension");
        جاؤ fail;
    }
    واپس true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = تہی;
    واپس false;
}

خالی VIVANTE_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    اگر (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = تہی;
    }
}

حرف ثابت * ثابت *VIVANTE_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *گنتی)
{
    ساکن ثابت حرف *ثابت extensionsForVivante[] = {
        VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_DISPLAY_EXTENSION_NAME
    };
    *گنتی = SDL_arraysize(extensionsForVivante);
    واپس extensionsForVivante;
}

bool VIVANTE_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                                 SDL_کھڑکی *کھڑکی,
                                 VkInstance instance,
                                 ثابت ساخت Vk_تخصیص_Callbacks *allocator,
                                 VkSurfaceKHR *surface)
{
    اگر (!_this->vulkan_config.loader_handle) {
        واپس SDL_سیٹ_Error("Vulkan is not loaded");
    }
    واپس SDL_Vulkan_Display_CreateSurface(_this->vulkan_config.vkGetInstanceProcAddr, instance, allocator, surface);
}

خالی VIVANTE_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                   VkInstance instance,
                                   VkSurfaceKHR surface,
                                   ثابت ساخت Vk_تخصیص_Callbacks *allocator)
{
    اگر (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_Destroy_Surface_اندرونی(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

#اگر_ختم
