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

#అన్తర్భావ "SDL_internal.h"

#ఒకవేళ defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_WINDOWS)

#అన్తర్భావ "../SDL_vulkan_internal.h"

#అన్తర్భావ "SDL_windowsvideo.h"
#అన్తర్భావ "SDL_windowswindow.h"

#అన్తర్భావ "SDL_windowsvulkan.h"

bool WIN_Vulkan_ఎక్కించు_Library(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *మార్గం)
{
    VkExtensionProperties *extensions = ఖాళీ;
    Uint32 extension_లెక్క = 0;
    Uint32 i;
    bool hasSurfaceExtension = false;
    bool hasWin32SurfaceExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = ఖాళీ;
    ఒకవేళ (_this->vulkan_config.loader_handle) {
        తిరిగి SDL_సమితి_Error("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    ఒకవేళ (!మార్గం) {
        మార్గం = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }
    ఒకవేళ (!మార్గం) {
        మార్గం = "vulkan-1.dll";
    }
    _this->vulkan_config.loader_handle = SDL_ఎక్కించు_Object(మార్గం);
    ఒకవేళ (!_this->vulkan_config.loader_handle) {
        తిరిగి false;
    }
    SDL_strlcpy(_this->vulkan_config.loader_మార్గం, మార్గం,
                SDL_arraysize(_this->vulkan_config.loader_మార్గం));
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)SDL_ఎక్కించు_Function(
        _this->vulkan_config.loader_handle, "vkGetInstanceProcAddr");
    ఒకవేళ (!vkGetInstanceProcAddr) {
        వెళ్ళు fail;
    }
    _this->vulkan_config.vkGetInstanceProcAddr = (SDL_Function_సూచిక)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties =
        (SDL_Function_సూచిక)vkGetInstanceProcAddr(
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
        } లేకపోతే ఒకవేళ (SDL_strcmp(VK_KHR_WIN32_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasWin32SurfaceExtension = true;
        }
    }
    SDL_free(extensions);
    ఒకవేళ (!hasSurfaceExtension) {
        SDL_సమితి_Error("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        వెళ్ళు fail;
    } లేకపోతే ఒకవేళ (!hasWin32SurfaceExtension) {
        SDL_సమితి_Error("Installed Vulkan doesn't implement the " VK_KHR_WIN32_SURFACE_EXTENSION_NAME " extension");
        వెళ్ళు fail;
    }
    తిరిగి true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = ఖాళీ;
    తిరిగి false;
}

శూన్య WIN_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    ఒకవేళ (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = ఖాళీ;
    }
}

అక్షరం స్థిరరాశి * స్థిరరాశి *WIN_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *లెక్క)
{
    స్థిర స్థిరరాశి అక్షరం *స్థిరరాశి extensionsForWin32[] = {
        VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_WIN32_SURFACE_EXTENSION_NAME
    };
    *లెక్క = SDL_arraysize(extensionsForWin32);
    తిరిగి extensionsForWin32;
}

bool WIN_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                             SDL_కిటికీ *కిటికీ,
                             VkInstance instance,
                             స్థిరరాశి నిర్మాణం Vk_కేటాయింపు_Callbacks *allocator,
                             VkSurfaceKHR *surface)
{
    SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం = కిటికీ->అంతర్గత;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    PFN_vkCreateWin32SurfaceKHR vkCreateWin32SurfaceKHR =
        (PFN_vkCreateWin32SurfaceKHR)vkGetInstanceProcAddr(
            instance,
            "vkCreateWin32SurfaceKHR");
    VkWin32SurfaceCreateInfoKHR createInfo;
    Vk_ఫలితం ఫలితం;

    ఒకవేళ (!_this->vulkan_config.loader_handle) {
        తిరిగి SDL_సమితి_Error("Vulkan is not loaded");
    }

    ఒకవేళ (!vkCreateWin32SurfaceKHR) {
        తిరిగి SDL_సమితి_Error(VK_KHR_WIN32_SURFACE_EXTENSION_NAME
                            " extension is not enabled in the Vulkan instance.");
    }
    createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    createInfo.p_తదుపరి = ఖాళీ;
    createInfo.flags = 0;
    createInfo.hinstance = కిటికీ_దత్తాంశం->hinstance;
    createInfo.hwnd = కిటికీ_దత్తాంశం->hwnd;
    ఫలితం = vkCreateWin32SurfaceKHR(instance, &createInfo, allocator, surface);
    ఒకవేళ (ఫలితం != VK_SUCCESS) {
        తిరిగి SDL_సమితి_Error("vkCreateWin32SurfaceKHR failed: %s", SDL_Vulkan_Get_ఫలితం_String(ఫలితం));
    }
    తిరిగి true;
}

శూన్య WIN_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                               VkInstance instance,
                               VkSurfaceKHR surface,
                               స్థిరరాశి నిర్మాణం Vk_కేటాయింపు_Callbacks *allocator)
{
    ఒకవేళ (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_Destroy_Surface_అంతర్గత(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

bool WIN_Vulkan_GetPresentationSupport(SDL_VideoDevice *_this,
                                           VkInstance instance,
                                           VkPhysicalDevice physicalDevice,
                                           Uint32 వరుస_Family_సూచీ)
{
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR vkGetPhysicalDeviceWin32PresentationSupportKHR =
        (PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR)vkGetInstanceProcAddr(
            instance,
            "vkGetPhysicalDeviceWin32PresentationSupportKHR");

    ఒకవేళ (!_this->vulkan_config.loader_handle) {
        తిరిగి SDL_సమితి_Error("Vulkan is not loaded");
    }

    ఒకవేళ (!vkGetPhysicalDeviceWin32PresentationSupportKHR) {
        తిరిగి SDL_సమితి_Error(VK_KHR_WIN32_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
    }

    తిరిగి vkGetPhysicalDeviceWin32PresentationSupportKHR(physicalDevice,
                                                          వరుస_Family_సూచీ);
}

#అయితే_ముగింపు
