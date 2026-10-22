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

#अन्तर्भाव "SDL_internal.h"

#यदि defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_OPENHARMONY)

#अन्तर्भाव "../SDL_vulkan_internal.h"

#अन्तर्भाव "SDL_openharmonyvideo.h"
#अन्तर्भाव "SDL_openharmonywindow.h"

#अन्तर्भाव "SDL_openharmonyvulkan.h"


bool OPENHARMONY_Vulkan_आरोपय_Library(SDL_VideoDevice *_this, ध्रुव वर्ण *मार्गः)
{
    VkExtensionProperties *extensions = रिक्त;
    Uint32 extension_गणनम् = 0;
    bool hasSurfaceExtension = false;
    bool hasOHOSSurfaceExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = रिक्त;

    यदि (_this->vulkan_config.loader_handle) {
        प्रत्यागम SDL_समुच्चयः_Error("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    यदि (!मार्गः) {
        मार्गः = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
        यदि (!मार्गः) {
            मार्गः = "libvulkan.so";
        }
    }

    SDL_SharedObject *lib = SDL_आरोपय_Object(मार्गः);
    _this->vulkan_config.loader_handle = lib;
    यदि (!lib) {
        प्रत्यागम false;
    }

    SDL_strlcpy(_this->vulkan_config.loader_मार्गः, मार्गः, परिमाण (_this->vulkan_config.loader_मार्गः));
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr) SDL_आरोपय_Function(lib, "vkGetInstanceProcAddr");
    यदि (!vkGetInstanceProcAddr) {
        गच्छ fail;
    }

    _this->vulkan_config.vkGetInstanceProcAddr = (शून्य *)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties = (शून्य *)((PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr)(VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties");
    यदि (!_this->vulkan_config.vkEnumerateInstanceExtensionProperties) {
        गच्छ fail;
    }

    extensions = SDL_Vulkan_CreateInstanceExtensionsList((PFN_vkEnumerateInstanceExtensionProperties) _this->vulkan_config.vkEnumerateInstanceExtensionProperties, &extension_गणनम्);
    यदि (!extensions) {
        गच्छ fail;
    }

    प्रति (Uint32 i = 0; i < extension_गणनम्; i++) {
        यदि (SDL_strcmp(VK_KHR_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasSurfaceExtension = true;
        } अन्यथा यदि (SDL_strcmp(VK_OHOS_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasOHOSSurfaceExtension = true;
        }
    }

    SDL_free(extensions);

    यदि (!hasSurfaceExtension) {
        SDL_समुच्चयः_Error("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        गच्छ fail;
    } अन्यथा यदि (!hasOHOSSurfaceExtension) {
        SDL_समुच्चयः_Error("Installed Vulkan doesn't implement the " VK_OHOS_SURFACE_EXTENSION_NAME " extension");
        गच्छ fail;
    }

    प्रत्यागम true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = रिक्त;
    प्रत्यागम false;
}

शून्य OPENHARMONY_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    यदि (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = रिक्त;
    }
}

वर्ण ध्रुव * ध्रुव *OPENHARMONY_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *गणनम्)
{
    स्थिर ध्रुव वर्ण *ध्रुव extensionsForOpenHarmony[] = {
        VK_KHR_SURFACE_EXTENSION_NAME, VK_OHOS_SURFACE_EXTENSION_NAME
    };
    यदि (गणनम्) {
        *गणनम् = SDL_arraysize(extensionsForOpenHarmony);
    }
    प्रत्यागम extensionsForOpenHarmony;
}

bool OPENHARMONY_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                                 SDL_गवाक्षः *गवाक्षः,
                                 VkInstance instance,
                                 ध्रुव संरचना Vk_आवण्टनम्_Callbacks *allocator,
                                 VkSurfaceKHR *surface)
{
    SDL_गवाक्षः_दत्त *गवाक्षः_दत्त = गवाक्षः->आन्तरिकम्;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    PFN_vkCreateSurfaceOHOS vkCreateSurfaceOHOS = (PFN_vkCreateSurfaceOHOS ) vkGetInstanceProcAddr(instance, "vkCreateSurfaceOHOS");
    VkSurfaceCreateInfoOHOS createInfo;
    Vk_परिणाम परिणाम;

    यदि (!_this->vulkan_config.loader_handle) {
        प्रत्यागम SDL_समुच्चयः_Error("Vulkan is not loaded");
    }

    यदि (!vkCreateSurfaceOHOS) {
        प्रत्यागम SDL_समुच्चयः_Error(VK_OHOS_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
    }

    SDL_zero(createInfo);
    createInfo.sType = VK_STRUCTURE_TYPE_SURFACE_CREATE_INFO_OHOS;
    createInfo.p_अग्र = रिक्त;
    createInfo.flags = 0;
    createInfo.गवाक्षः = (OHNative_गवाक्षः *) गवाक्षः_दत्त->native_गवाक्षः;
    परिणाम = vkCreateSurfaceOHOS(instance, &createInfo, allocator, surface);
    यदि (परिणाम != VK_SUCCESS) {
        यदि (परिणाम == VK_ERROR_NATIVE_गवाक्षः_अन्तर्_USE_KHR) {
            प्रत्यागम SDL_समुच्चयः_Error("vkCreateSurfaceOHOS failed: %s, was the window created with SDL_WINDOW_VULKAN?", SDL_Vulkan_Get_परिणाम_String(परिणाम));
        } अन्यथा {
            प्रत्यागम SDL_समुच्चयः_Error("vkCreateSurfaceOHOS failed: %s", SDL_Vulkan_Get_परिणाम_String(परिणाम));
        }
    }
    प्रत्यागम true;
}

शून्य OPENHARMONY_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                   VkInstance instance,
                                   VkSurfaceKHR surface,
                                   ध्रुव संरचना Vk_आवण्टनम्_Callbacks *allocator)
{
    यदि (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_Destroy_Surface_आन्तरिकम्(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

#यदि_अन्तः

