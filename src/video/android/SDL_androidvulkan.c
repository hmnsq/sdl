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
 * @author Mark Callow, www.edgewise-consulting.com. Based on Jacob Lifshay's
 * SDL_x11vulkan.c.
 */

#ضمن "SDL_internal.h"

#إذا defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_ANDROID)

#ضمن "../SDL_vulkan_internal.h"

#ضمن "SDL_androidvideo.h"
#ضمن "SDL_androidwindow.h"

#ضمن "SDL_androidvulkan.h"


bool Android_Vulkan_بارول_Library(SDL_VideoDevice *_this, ثابت حرف *لار)
{
    VkExtensionProperties *extensions = عدم;
    Uint32 i, extension_شمېر = 0;
    bool hasSurfaceExtension = false;
    bool hasAndroidSurfaceExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = عدم;
    إذا (_this->vulkan_config.loader_handle) {
        أرجع SDL_سېټ_Error("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    إذا (!لار) {
        لار = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }
    إذا (!لار) {
        لار = "libvulkan.so";
    }
    _this->vulkan_config.loader_handle = SDL_بارول_Object(لار);
    إذا (!_this->vulkan_config.loader_handle) {
        أرجع false;
    }
    SDL_strlcpy(_this->vulkan_config.loader_لار, لار,
                SDL_arraysize(_this->vulkan_config.loader_لار));
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)SDL_بارول_Function(
        _this->vulkan_config.loader_handle, "vkGetInstanceProcAddr");
    إذا (!vkGetInstanceProcAddr) {
        اذهب fail;
    }
    _this->vulkan_config.vkGetInstanceProcAddr = (فراغ *)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties =
        (فراغ *)((PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr)(
            VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties");
    إذا (!_this->vulkan_config.vkEnumerateInstanceExtensionProperties) {
        اذهب fail;
    }
    extensions = SDL_Vulkan_CreateInstanceExtensionsList(
        (PFN_vkEnumerateInstanceExtensionProperties)
            _this->vulkan_config.vkEnumerateInstanceExtensionProperties,
        &extension_شمېر);
    إذا (!extensions) {
        اذهب fail;
    }
    لكل (i = 0; i < extension_شمېر; i++) {
        إذا (SDL_strcmp(VK_KHR_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasSurfaceExtension = true;
        } وإلا إذا (SDL_strcmp(VK_KHR_ANDROID_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasAndroidSurfaceExtension = true;
        }
    }
    SDL_free(extensions);
    إذا (!hasSurfaceExtension) {
        SDL_سېټ_Error("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        اذهب fail;
    } وإلا إذا (!hasAndroidSurfaceExtension) {
        SDL_سېټ_Error("Installed Vulkan doesn't implement the " VK_KHR_ANDROID_SURFACE_EXTENSION_NAME " extension");
        اذهب fail;
    }
    أرجع true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = عدم;
    أرجع false;
}

فراغ Android_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    إذا (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = عدم;
    }
}

حرف ثابت * ثابت *Android_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *شمېر)
{
    ساكن ثابت حرف *ثابت extensionsForAndroid[] = {
        VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_ANDROID_SURFACE_EXTENSION_NAME
    };
    *شمېر = SDL_arraysize(extensionsForAndroid);
    أرجع extensionsForAndroid;
}

bool Android_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                                 SDL_کړکۍ *کړکۍ,
                                 VkInstance instance,
                                 ثابت بنية Vk_ویش_Callbacks *allocator,
                                 VkSurfaceKHR *surface)
{
    SDL_کړکۍ_معلومات *کړکۍ_معلومات = کړکۍ->دننی;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    PFN_vkCreateAndroidSurfaceKHR vkCreateAndroidSurfaceKHR =
        (PFN_vkCreateAndroidSurfaceKHR)vkGetInstanceProcAddr(
            instance,
            "vkCreateAndroidSurfaceKHR");
    VkAndroidSurfaceCreateInfoKHR createInfo;
    Vk_پایله پایله;

    إذا (!_this->vulkan_config.loader_handle) {
        أرجع SDL_سېټ_Error("Vulkan is not loaded");
    }

    إذا (!vkCreateAndroidSurfaceKHR) {
        أرجع SDL_سېټ_Error(VK_KHR_ANDROID_SURFACE_EXTENSION_NAME
                            " extension is not enabled in the Vulkan instance.");
    }

    إذا (!کړکۍ_معلومات->native_کړکۍ) {
        // passing a NULL window violates Vulkan spec
        أرجع SDL_سېټ_Error("Android native window is not available for surface creation, usually because of backgrounding");
    }

    SDL_zero(createInfo);
    createInfo.sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR;
    createInfo.p_بل = عدم;
    createInfo.flags = 0;
    createInfo.کړکۍ = کړکۍ_معلومات->native_کړکۍ;
    پایله = vkCreateAndroidSurfaceKHR(instance, &createInfo, allocator, surface);
    إذا (پایله != VK_SUCCESS) {
        إذا (پایله == VK_ERROR_NATIVE_کړکۍ_دننه_USE_KHR) {
            أرجع SDL_سېټ_Error("vkCreateAndroidSurfaceKHR failed: %s, was the window created with SDL_WINDOW_VULKAN?", SDL_Vulkan_Get_پایله_String(پایله));
        } وإلا {
            أرجع SDL_سېټ_Error("vkCreateAndroidSurfaceKHR failed: %s", SDL_Vulkan_Get_پایله_String(پایله));
        }
    }
    أرجع true;
}

فراغ Android_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                   VkInstance instance,
                                   VkSurfaceKHR surface,
                                   ثابت بنية Vk_ویش_Callbacks *allocator)
{
    إذا (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_Destroy_Surface_دننی(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

#د_که_پای
