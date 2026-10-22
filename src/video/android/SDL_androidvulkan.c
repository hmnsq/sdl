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

#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ಆದರೆ defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_ANDROID)

#ಅನ್ತರ್ಭಾವ "../SDL_vulkan_internal.h"

#ಅನ್ತರ್ಭಾವ "SDL_androidvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_androidwindow.h"

#ಅನ್ತರ್ಭಾವ "SDL_androidvulkan.h"


bool Android_Vulkan_ತುಂಬು_Library(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಮಾರ್ಗ)
{
    VkExtensionProperties *extensions = ಖಾಲಿ;
    Uint32 i, extension_ಎಣಿಕೆ = 0;
    bool hasSurfaceExtension = false;
    bool hasAndroidSurfaceExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = ಖಾಲಿ;
    ಆದರೆ (_this->vulkan_config.loader_handle) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    ಆದರೆ (!ಮಾರ್ಗ) {
        ಮಾರ್ಗ = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }
    ಆದರೆ (!ಮಾರ್ಗ) {
        ಮಾರ್ಗ = "libvulkan.so";
    }
    _this->vulkan_config.loader_handle = SDL_ತುಂಬು_Object(ಮಾರ್ಗ);
    ಆದರೆ (!_this->vulkan_config.loader_handle) {
        ಹಿಂತಿರುಗಿ false;
    }
    SDL_strlcpy(_this->vulkan_config.loader_ಮಾರ್ಗ, ಮಾರ್ಗ,
                SDL_arraysize(_this->vulkan_config.loader_ಮಾರ್ಗ));
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)SDL_ತುಂಬು_Function(
        _this->vulkan_config.loader_handle, "vkGetInstanceProcAddr");
    ಆದರೆ (!vkGetInstanceProcAddr) {
        ಹೋಗು fail;
    }
    _this->vulkan_config.vkGetInstanceProcAddr = (ಶೂನ್ಯ *)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties =
        (ಶೂನ್ಯ *)((PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr)(
            VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties");
    ಆದರೆ (!_this->vulkan_config.vkEnumerateInstanceExtensionProperties) {
        ಹೋಗು fail;
    }
    extensions = SDL_Vulkan_CreateInstanceExtensionsList(
        (PFN_vkEnumerateInstanceExtensionProperties)
            _this->vulkan_config.vkEnumerateInstanceExtensionProperties,
        &extension_ಎಣಿಕೆ);
    ಆದರೆ (!extensions) {
        ಹೋಗು fail;
    }
    ಗಾಗಿ (i = 0; i < extension_ಎಣಿಕೆ; i++) {
        ಆದರೆ (SDL_strcmp(VK_KHR_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasSurfaceExtension = true;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(VK_KHR_ANDROID_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasAndroidSurfaceExtension = true;
        }
    }
    SDL_free(extensions);
    ಆದರೆ (!hasSurfaceExtension) {
        SDL_ಗಣ_Error("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        ಹೋಗು fail;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!hasAndroidSurfaceExtension) {
        SDL_ಗಣ_Error("Installed Vulkan doesn't implement the " VK_KHR_ANDROID_SURFACE_EXTENSION_NAME " extension");
        ಹೋಗು fail;
    }
    ಹಿಂತಿರುಗಿ true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = ಖಾಲಿ;
    ಹಿಂತಿರುಗಿ false;
}

ಶೂನ್ಯ Android_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    ಆದರೆ (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = ಖಾಲಿ;
    }
}

ಅಕ್ಷರ ಸ್ಥಿರಾಂಕ * ಸ್ಥಿರಾಂಕ *Android_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *ಎಣಿಕೆ_2)
{
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸ್ಥಿರಾಂಕ extensionsForAndroid[] = {
        VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_ANDROID_SURFACE_EXTENSION_NAME
    };
    *ಎಣಿಕೆ_2 = SDL_arraysize(extensionsForAndroid);
    ಹಿಂತಿರುಗಿ extensionsForAndroid;
}

bool Android_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                                 SDL_ಕಿಟಕಿ *ಕಿಟಕಿ,
                                 VkInstance instance,
                                 ಸ್ಥಿರಾಂಕ ರಚನೆ Vk_ಹಂಚಿಕೆ_Callbacks *allocator,
                                 VkSurfaceKHR *surface)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    PFN_vkCreateAndroidSurfaceKHR vkCreateAndroidSurfaceKHR =
        (PFN_vkCreateAndroidSurfaceKHR)vkGetInstanceProcAddr(
            instance,
            "vkCreateAndroidSurfaceKHR");
    VkAndroidSurfaceCreateInfoKHR createInfo;
    Vk_ಫಲಿತಾಂಶ ಫಲಿತಾಂಶ;

    ಆದರೆ (!_this->vulkan_config.loader_handle) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Vulkan is not loaded");
    }

    ಆದರೆ (!vkCreateAndroidSurfaceKHR) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error(VK_KHR_ANDROID_SURFACE_EXTENSION_NAME
                            " extension is not enabled in the Vulkan instance.");
    }

    ಆದರೆ (!ಕಿಟಕಿ_ದತ್ತಾಂಶ->native_ಕಿಟಕಿ) {
        // passing a NULL window violates Vulkan spec
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Android native window is not available for surface creation, usually because of backgrounding");
    }

    SDL_zero(createInfo);
    createInfo.sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR;
    createInfo.p_ಮುಂದಿನ = ಖಾಲಿ;
    createInfo.flags = 0;
    createInfo.ಕಿಟಕಿ = ಕಿಟಕಿ_ದತ್ತಾಂಶ->native_ಕಿಟಕಿ;
    ಫಲಿತಾಂಶ = vkCreateAndroidSurfaceKHR(instance, &createInfo, allocator, surface);
    ಆದರೆ (ಫಲಿತಾಂಶ != VK_SUCCESS) {
        ಆದರೆ (ಫಲಿತಾಂಶ == VK_ERROR_NATIVE_ಕಿಟಕಿ_ಒಳ_USE_KHR) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("vkCreateAndroidSurfaceKHR failed: %s, was the window created with SDL_WINDOW_VULKAN?", SDL_Vulkan_Get_ಫಲಿತಾಂಶ_String(ಫಲಿತಾಂಶ));
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("vkCreateAndroidSurfaceKHR failed: %s", SDL_Vulkan_Get_ಫಲಿತಾಂಶ_String(ಫಲಿತಾಂಶ));
        }
    }
    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ Android_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                   VkInstance instance,
                                   VkSurfaceKHR surface,
                                   ಸ್ಥಿರಾಂಕ ರಚನೆ Vk_ಹಂಚಿಕೆ_Callbacks *allocator)
{
    ಆದರೆ (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_Destroy_Surface_ಆಂತರಿಕ(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

#ಆದರೆ_ಅಂತ್ಯ
