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

#إذا defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_WINDOWS)

#ضمن "../SDL_vulkan_internal.h"

#ضمن "SDL_windowsvideo.h"
#ضمن "SDL_windowswindow.h"

#ضمن "SDL_windowsvulkan.h"

bool WIN_Vulkan_لدو_Library(SDL_VideoDevice *_this, ثابت حرف *رستہ)
{
    VkExtensionProperties *extensions = عدم;
    Uint32 extension_گنتی = 0;
    Uint32 i;
    bool hasSurfaceExtension = false;
    bool hasWin32SurfaceExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = عدم;
    إذا (_this->vulkan_config.loader_handle) {
        أرجع SDL_سیٹ_Error("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    إذا (!رستہ) {
        رستہ = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }
    إذا (!رستہ) {
        رستہ = "vulkan-1.dll";
    }
    _this->vulkan_config.loader_handle = SDL_لدو_Object(رستہ);
    إذا (!_this->vulkan_config.loader_handle) {
        أرجع false;
    }
    SDL_strlcpy(_this->vulkan_config.loader_رستہ, رستہ,
                SDL_arraysize(_this->vulkan_config.loader_رستہ));
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)SDL_لدو_Function(
        _this->vulkan_config.loader_handle, "vkGetInstanceProcAddr");
    إذا (!vkGetInstanceProcAddr) {
        اذهب fail;
    }
    _this->vulkan_config.vkGetInstanceProcAddr = (SDL_Function_اشارہ_گر)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties =
        (SDL_Function_اشارہ_گر)vkGetInstanceProcAddr(
            VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties");
    إذا (!_this->vulkan_config.vkEnumerateInstanceExtensionProperties) {
        اذهب fail;
    }
    extensions = SDL_Vulkan_CreateInstanceExtensionsList(
        (PFN_vkEnumerateInstanceExtensionProperties)
            _this->vulkan_config.vkEnumerateInstanceExtensionProperties,
        &extension_گنتی);
    إذا (!extensions) {
        اذهب fail;
    }
    لكل (i = 0; i < extension_گنتی; i++) {
        إذا (SDL_strcmp(VK_KHR_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasSurfaceExtension = true;
        } وإلا إذا (SDL_strcmp(VK_KHR_WIN32_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasWin32SurfaceExtension = true;
        }
    }
    SDL_free(extensions);
    إذا (!hasSurfaceExtension) {
        SDL_سیٹ_Error("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        اذهب fail;
    } وإلا إذا (!hasWin32SurfaceExtension) {
        SDL_سیٹ_Error("Installed Vulkan doesn't implement the " VK_KHR_WIN32_SURFACE_EXTENSION_NAME " extension");
        اذهب fail;
    }
    أرجع true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = عدم;
    أرجع false;
}

فراغ WIN_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    إذا (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = عدم;
    }
}

حرف ثابت * ثابت *WIN_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *گنتی)
{
    ساكن ثابت حرف *ثابت extensionsForWin32[] = {
        VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_WIN32_SURFACE_EXTENSION_NAME
    };
    *گنتی = SDL_arraysize(extensionsForWin32);
    أرجع extensionsForWin32;
}

bool WIN_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                             SDL_کھڑکی *کھڑکی,
                             VkInstance instance,
                             ثابت بنية Vk_ونڈ_Callbacks *allocator,
                             VkSurfaceKHR *surface)
{
    SDL_کھڑکی_انکڑے *کھڑکی_انکڑے = کھڑکی->اندرونی;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    PFN_vkCreateWin32SurfaceKHR vkCreateWin32SurfaceKHR =
        (PFN_vkCreateWin32SurfaceKHR)vkGetInstanceProcAddr(
            instance,
            "vkCreateWin32SurfaceKHR");
    VkWin32SurfaceCreateInfoKHR createInfo;
    Vk_نتیجہ نتیجہ;

    إذا (!_this->vulkan_config.loader_handle) {
        أرجع SDL_سیٹ_Error("Vulkan is not loaded");
    }

    إذا (!vkCreateWin32SurfaceKHR) {
        أرجع SDL_سیٹ_Error(VK_KHR_WIN32_SURFACE_EXTENSION_NAME
                            " extension is not enabled in the Vulkan instance.");
    }
    createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    createInfo.p_اگلا = عدم;
    createInfo.flags = 0;
    createInfo.hinstance = کھڑکی_انکڑے->hinstance;
    createInfo.hwnd = کھڑکی_انکڑے->hwnd;
    نتیجہ = vkCreateWin32SurfaceKHR(instance, &createInfo, allocator, surface);
    إذا (نتیجہ != VK_SUCCESS) {
        أرجع SDL_سیٹ_Error("vkCreateWin32SurfaceKHR failed: %s", SDL_Vulkan_Get_نتیجہ_String(نتیجہ));
    }
    أرجع true;
}

فراغ WIN_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                               VkInstance instance,
                               VkSurfaceKHR surface,
                               ثابت بنية Vk_ونڈ_Callbacks *allocator)
{
    إذا (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_Destroy_Surface_اندرونی(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

bool WIN_Vulkan_GetPresentationSupport(SDL_VideoDevice *_this,
                                           VkInstance instance,
                                           VkPhysicalDevice physicalDevice,
                                           Uint32 قطار_Family_اشاریہ)
{
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR vkGetPhysicalDeviceWin32PresentationSupportKHR =
        (PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR)vkGetInstanceProcAddr(
            instance,
            "vkGetPhysicalDeviceWin32PresentationSupportKHR");

    إذا (!_this->vulkan_config.loader_handle) {
        أرجع SDL_سیٹ_Error("Vulkan is not loaded");
    }

    إذا (!vkGetPhysicalDeviceWin32PresentationSupportKHR) {
        أرجع SDL_سیٹ_Error(VK_KHR_WIN32_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
    }

    أرجع vkGetPhysicalDeviceWin32PresentationSupportKHR(physicalDevice,
                                                          قطار_Family_اشاریہ);
}

#جے_انت
