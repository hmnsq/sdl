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

#ضمن "SDL_internal.h"

#إذا defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_OPENHARMONY)

#ضمن "../SDL_vulkan_internal.h"

#ضمن "SDL_openharmonyvideo.h"
#ضمن "SDL_openharmonywindow.h"

#ضمن "SDL_openharmonyvulkan.h"


bool OPENHARMONY_Vulkan_لدو_Library(SDL_VideoDevice *_this, ثابت حرف *رستہ)
{
    VkExtensionProperties *extensions = عدم;
    Uint32 extension_گنتی = 0;
    bool hasSurfaceExtension = false;
    bool hasOHOSSurfaceExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = عدم;

    إذا (_this->vulkan_config.loader_handle) {
        أرجع SDL_سیٹ_Error("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    إذا (!رستہ) {
        رستہ = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
        إذا (!رستہ) {
            رستہ = "libvulkan.so";
        }
    }

    SDL_SharedObject *lib = SDL_لدو_Object(رستہ);
    _this->vulkan_config.loader_handle = lib;
    إذا (!lib) {
        أرجع false;
    }

    SDL_strlcpy(_this->vulkan_config.loader_رستہ, رستہ, حجم (_this->vulkan_config.loader_رستہ));
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr) SDL_لدو_Function(lib, "vkGetInstanceProcAddr");
    إذا (!vkGetInstanceProcAddr) {
        اذهب fail;
    }

    _this->vulkan_config.vkGetInstanceProcAddr = (فراغ *)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties = (فراغ *)((PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr)(VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties");
    إذا (!_this->vulkan_config.vkEnumerateInstanceExtensionProperties) {
        اذهب fail;
    }

    extensions = SDL_Vulkan_CreateInstanceExtensionsList((PFN_vkEnumerateInstanceExtensionProperties) _this->vulkan_config.vkEnumerateInstanceExtensionProperties, &extension_گنتی);
    إذا (!extensions) {
        اذهب fail;
    }

    لكل (Uint32 i = 0; i < extension_گنتی; i++) {
        إذا (SDL_strcmp(VK_KHR_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasSurfaceExtension = true;
        } وإلا إذا (SDL_strcmp(VK_OHOS_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasOHOSSurfaceExtension = true;
        }
    }

    SDL_free(extensions);

    إذا (!hasSurfaceExtension) {
        SDL_سیٹ_Error("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        اذهب fail;
    } وإلا إذا (!hasOHOSSurfaceExtension) {
        SDL_سیٹ_Error("Installed Vulkan doesn't implement the " VK_OHOS_SURFACE_EXTENSION_NAME " extension");
        اذهب fail;
    }

    أرجع true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = عدم;
    أرجع false;
}

فراغ OPENHARMONY_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    إذا (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = عدم;
    }
}

حرف ثابت * ثابت *OPENHARMONY_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *گنتی)
{
    ساكن ثابت حرف *ثابت extensionsForOpenHarmony[] = {
        VK_KHR_SURFACE_EXTENSION_NAME, VK_OHOS_SURFACE_EXTENSION_NAME
    };
    إذا (گنتی) {
        *گنتی = SDL_arraysize(extensionsForOpenHarmony);
    }
    أرجع extensionsForOpenHarmony;
}

bool OPENHARMONY_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                                 SDL_کھڑکی *کھڑکی,
                                 VkInstance instance,
                                 ثابت بنية Vk_ونڈ_Callbacks *allocator,
                                 VkSurfaceKHR *surface)
{
    SDL_کھڑکی_انکڑے *کھڑکی_انکڑے = کھڑکی->اندرونی;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    PFN_vkCreateSurfaceOHOS vkCreateSurfaceOHOS = (PFN_vkCreateSurfaceOHOS ) vkGetInstanceProcAddr(instance, "vkCreateSurfaceOHOS");
    VkSurfaceCreateInfoOHOS createInfo;
    Vk_نتیجہ نتیجہ;

    إذا (!_this->vulkan_config.loader_handle) {
        أرجع SDL_سیٹ_Error("Vulkan is not loaded");
    }

    إذا (!vkCreateSurfaceOHOS) {
        أرجع SDL_سیٹ_Error(VK_OHOS_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
    }

    SDL_zero(createInfo);
    createInfo.sType = VK_STRUCTURE_TYPE_SURFACE_CREATE_INFO_OHOS;
    createInfo.p_اگلا = عدم;
    createInfo.flags = 0;
    createInfo.کھڑکی = (OHNative_کھڑکی *) کھڑکی_انکڑے->native_کھڑکی;
    نتیجہ = vkCreateSurfaceOHOS(instance, &createInfo, allocator, surface);
    إذا (نتیجہ != VK_SUCCESS) {
        إذا (نتیجہ == VK_ERROR_NATIVE_کھڑکی_وچ_USE_KHR) {
            أرجع SDL_سیٹ_Error("vkCreateSurfaceOHOS failed: %s, was the window created with SDL_WINDOW_VULKAN?", SDL_Vulkan_Get_نتیجہ_String(نتیجہ));
        } وإلا {
            أرجع SDL_سیٹ_Error("vkCreateSurfaceOHOS failed: %s", SDL_Vulkan_Get_نتیجہ_String(نتیجہ));
        }
    }
    أرجع true;
}

فراغ OPENHARMONY_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                   VkInstance instance,
                                   VkSurfaceKHR surface,
                                   ثابت بنية Vk_ونڈ_Callbacks *allocator)
{
    إذا (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_Destroy_Surface_اندرونی(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

#جے_انت

