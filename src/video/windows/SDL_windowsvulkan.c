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

#अन्तर्भाव "SDL_internal.h"

#यदि defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_WINDOWS)

#अन्तर्भाव "../SDL_vulkan_internal.h"

#अन्तर्भाव "SDL_windowsvideo.h"
#अन्तर्भाव "SDL_windowswindow.h"

#अन्तर्भाव "SDL_windowsvulkan.h"

bool WIN_Vulkan_आरोपय_Library(SDL_VideoDevice *_this, ध्रुव वर्ण *मार्गः)
{
    VkExtensionProperties *extensions = रिक्त;
    Uint32 extension_गणनम् = 0;
    Uint32 i;
    bool hasSurfaceExtension = false;
    bool hasWin32SurfaceExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = रिक्त;
    यदि (_this->vulkan_config.loader_handle) {
        प्रत्यागम SDL_समुच्चयः_Error("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    यदि (!मार्गः) {
        मार्गः = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }
    यदि (!मार्गः) {
        मार्गः = "vulkan-1.dll";
    }
    _this->vulkan_config.loader_handle = SDL_आरोपय_Object(मार्गः);
    यदि (!_this->vulkan_config.loader_handle) {
        प्रत्यागम false;
    }
    SDL_strlcpy(_this->vulkan_config.loader_मार्गः, मार्गः,
                SDL_arraysize(_this->vulkan_config.loader_मार्गः));
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)SDL_आरोपय_Function(
        _this->vulkan_config.loader_handle, "vkGetInstanceProcAddr");
    यदि (!vkGetInstanceProcAddr) {
        गच्छ fail;
    }
    _this->vulkan_config.vkGetInstanceProcAddr = (SDL_FunctionPointer)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties =
        (SDL_FunctionPointer)vkGetInstanceProcAddr(
            VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties");
    यदि (!_this->vulkan_config.vkEnumerateInstanceExtensionProperties) {
        गच्छ fail;
    }
    extensions = SDL_Vulkan_CreateInstanceExtensionsList(
        (PFN_vkEnumerateInstanceExtensionProperties)
            _this->vulkan_config.vkEnumerateInstanceExtensionProperties,
        &extension_गणनम्);
    यदि (!extensions) {
        गच्छ fail;
    }
    प्रति (i = 0; i < extension_गणनम्; i++) {
        यदि (SDL_strcmp(VK_KHR_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasSurfaceExtension = true;
        } अन्यथा यदि (SDL_strcmp(VK_KHR_WIN32_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasWin32SurfaceExtension = true;
        }
    }
    SDL_free(extensions);
    यदि (!hasSurfaceExtension) {
        SDL_समुच्चयः_Error("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        गच्छ fail;
    } अन्यथा यदि (!hasWin32SurfaceExtension) {
        SDL_समुच्चयः_Error("Installed Vulkan doesn't implement the " VK_KHR_WIN32_SURFACE_EXTENSION_NAME " extension");
        गच्छ fail;
    }
    प्रत्यागम true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = रिक्त;
    प्रत्यागम false;
}

शून्य WIN_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    यदि (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = रिक्त;
    }
}

वर्ण ध्रुव * ध्रुव *WIN_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *गणनम्)
{
    स्थिर ध्रुव वर्ण *ध्रुव extensionsForWin32[] = {
        VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_WIN32_SURFACE_EXTENSION_NAME
    };
    *गणनम् = SDL_arraysize(extensionsForWin32);
    प्रत्यागम extensionsForWin32;
}

bool WIN_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                             SDL_गवाक्षः *गवाक्षः,
                             VkInstance instance,
                             ध्रुव संरचना Vk_आवण्टनम्_Callbacks *allocator,
                             VkSurfaceKHR *surface)
{
    SDL_गवाक्षः_दत्त *गवाक्षः_दत्त = गवाक्षः->आन्तरिकम्;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    PFN_vkCreateWin32SurfaceKHR vkCreateWin32SurfaceKHR =
        (PFN_vkCreateWin32SurfaceKHR)vkGetInstanceProcAddr(
            instance,
            "vkCreateWin32SurfaceKHR");
    VkWin32SurfaceCreateInfoKHR createInfo;
    Vk_परिणाम परिणाम;

    यदि (!_this->vulkan_config.loader_handle) {
        प्रत्यागम SDL_समुच्चयः_Error("Vulkan is not loaded");
    }

    यदि (!vkCreateWin32SurfaceKHR) {
        प्रत्यागम SDL_समुच्चयः_Error(VK_KHR_WIN32_SURFACE_EXTENSION_NAME
                            " extension is not enabled in the Vulkan instance.");
    }
    createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    createInfo.p_अग्र = रिक्त;
    createInfo.flags = 0;
    createInfo.hinstance = गवाक्षः_दत्त->hinstance;
    createInfo.hwnd = गवाक्षः_दत्त->hwnd;
    परिणाम = vkCreateWin32SurfaceKHR(instance, &createInfo, allocator, surface);
    यदि (परिणाम != VK_SUCCESS) {
        प्रत्यागम SDL_समुच्चयः_Error("vkCreateWin32SurfaceKHR failed: %s", SDL_Vulkan_Get_परिणाम_String(परिणाम));
    }
    प्रत्यागम true;
}

शून्य WIN_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                               VkInstance instance,
                               VkSurfaceKHR surface,
                               ध्रुव संरचना Vk_आवण्टनम्_Callbacks *allocator)
{
    यदि (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_Destroy_Surface_आन्तरिकम्(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

bool WIN_Vulkan_GetPresentationSupport(SDL_VideoDevice *_this,
                                           VkInstance instance,
                                           VkPhysicalDevice physicalDevice,
                                           Uint32 queue_Family_सूचकांक)
{
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR vkGetPhysicalDeviceWin32PresentationSupportKHR =
        (PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR)vkGetInstanceProcAddr(
            instance,
            "vkGetPhysicalDeviceWin32PresentationSupportKHR");

    यदि (!_this->vulkan_config.loader_handle) {
        प्रत्यागम SDL_समुच्चयः_Error("Vulkan is not loaded");
    }

    यदि (!vkGetPhysicalDeviceWin32PresentationSupportKHR) {
        प्रत्यागम SDL_समुच्चयः_Error(VK_KHR_WIN32_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
    }

    प्रत्यागम vkGetPhysicalDeviceWin32PresentationSupportKHR(physicalDevice,
                                                          queue_Family_सूचकांक);
}

#यदि_अन्तः
