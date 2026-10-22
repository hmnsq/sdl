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

#ಆದರೆ defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_WINDOWS)

#ಅನ್ತರ್ಭಾವ "../SDL_vulkan_internal.h"

#ಅನ್ತರ್ಭಾವ "SDL_windowsvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_windowswindow.h"

#ಅನ್ತರ್ಭಾವ "SDL_windowsvulkan.h"

bool WIN_Vulkan_ತುಂಬು_Library(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಮಾರ್ಗ)
{
    VkExtensionProperties *extensions = ಖಾಲಿ;
    Uint32 extension_ಎಣಿಕೆ = 0;
    Uint32 i;
    bool hasSurfaceExtension = false;
    bool hasWin32SurfaceExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = ಖಾಲಿ;
    ಆದರೆ (_this->vulkan_config.loader_handle) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    ಆದರೆ (!ಮಾರ್ಗ) {
        ಮಾರ್ಗ = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }
    ಆದರೆ (!ಮಾರ್ಗ) {
        ಮಾರ್ಗ = "vulkan-1.dll";
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
    _this->vulkan_config.vkGetInstanceProcAddr = (SDL_Function_ಸೂಚಕ)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties =
        (SDL_Function_ಸೂಚಕ)vkGetInstanceProcAddr(
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
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(VK_KHR_WIN32_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasWin32SurfaceExtension = true;
        }
    }
    SDL_free(extensions);
    ಆದರೆ (!hasSurfaceExtension) {
        SDL_ಗಣ_Error("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        ಹೋಗು fail;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!hasWin32SurfaceExtension) {
        SDL_ಗಣ_Error("Installed Vulkan doesn't implement the " VK_KHR_WIN32_SURFACE_EXTENSION_NAME " extension");
        ಹೋಗು fail;
    }
    ಹಿಂತಿರುಗಿ true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = ಖಾಲಿ;
    ಹಿಂತಿರುಗಿ false;
}

ಶೂನ್ಯ WIN_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    ಆದರೆ (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = ಖಾಲಿ;
    }
}

ಅಕ್ಷರ ಸ್ಥಿರಾಂಕ * ಸ್ಥಿರಾಂಕ *WIN_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *ಎಣಿಕೆ_2)
{
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸ್ಥಿರಾಂಕ extensionsForWin32[] = {
        VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_WIN32_SURFACE_EXTENSION_NAME
    };
    *ಎಣಿಕೆ_2 = SDL_arraysize(extensionsForWin32);
    ಹಿಂತಿರುಗಿ extensionsForWin32;
}

bool WIN_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                             SDL_ಕಿಟಕಿ *ಕಿಟಕಿ,
                             VkInstance instance,
                             ಸ್ಥಿರಾಂಕ ರಚನೆ Vk_ಹಂಚಿಕೆ_Callbacks *allocator,
                             VkSurfaceKHR *surface)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    PFN_vkCreateWin32SurfaceKHR vkCreateWin32SurfaceKHR =
        (PFN_vkCreateWin32SurfaceKHR)vkGetInstanceProcAddr(
            instance,
            "vkCreateWin32SurfaceKHR");
    VkWin32SurfaceCreateInfoKHR createInfo;
    Vk_ಫಲಿತಾಂಶ ಫಲಿತಾಂಶ;

    ಆದರೆ (!_this->vulkan_config.loader_handle) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Vulkan is not loaded");
    }

    ಆದರೆ (!vkCreateWin32SurfaceKHR) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error(VK_KHR_WIN32_SURFACE_EXTENSION_NAME
                            " extension is not enabled in the Vulkan instance.");
    }
    createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    createInfo.p_ಮುಂದಿನ = ಖಾಲಿ;
    createInfo.flags = 0;
    createInfo.hinstance = ಕಿಟಕಿ_ದತ್ತಾಂಶ->hinstance;
    createInfo.hwnd = ಕಿಟಕಿ_ದತ್ತಾಂಶ->hwnd;
    ಫಲಿತಾಂಶ = vkCreateWin32SurfaceKHR(instance, &createInfo, allocator, surface);
    ಆದರೆ (ಫಲಿತಾಂಶ != VK_SUCCESS) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("vkCreateWin32SurfaceKHR failed: %s", SDL_Vulkan_Get_ಫಲಿತಾಂಶ_String(ಫಲಿತಾಂಶ));
    }
    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ WIN_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                               VkInstance instance,
                               VkSurfaceKHR surface,
                               ಸ್ಥಿರಾಂಕ ರಚನೆ Vk_ಹಂಚಿಕೆ_Callbacks *allocator)
{
    ಆದರೆ (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_Destroy_Surface_ಆಂತರಿಕ(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

bool WIN_Vulkan_GetPresentationSupport(SDL_VideoDevice *_this,
                                           VkInstance instance,
                                           VkPhysicalDevice physicalDevice,
                                           Uint32 ಸರತಿ_Family_ಸೂಚ್ಯಂಕ)
{
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR vkGetPhysicalDeviceWin32PresentationSupportKHR =
        (PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR)vkGetInstanceProcAddr(
            instance,
            "vkGetPhysicalDeviceWin32PresentationSupportKHR");

    ಆದರೆ (!_this->vulkan_config.loader_handle) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Vulkan is not loaded");
    }

    ಆದರೆ (!vkGetPhysicalDeviceWin32PresentationSupportKHR) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error(VK_KHR_WIN32_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
    }

    ಹಿಂತಿರುಗಿ vkGetPhysicalDeviceWin32PresentationSupportKHR(physicalDevice,
                                                          ಸರತಿ_Family_ಸೂಚ್ಯಂಕ);
}

#ಆದರೆ_ಅಂತ್ಯ
