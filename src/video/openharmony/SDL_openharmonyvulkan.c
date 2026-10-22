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

#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ଯଦି defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_OPENHARMONY)

#ଅନ୍ତର୍ଭାଵ "../SDL_vulkan_internal.h"

#ଅନ୍ତର୍ଭାଵ "SDL_openharmonyvideo.h"
#ଅନ୍ତର୍ଭାଵ "SDL_openharmonywindow.h"

#ଅନ୍ତର୍ଭାଵ "SDL_openharmonyvulkan.h"


bool OPENHARMONY_Vulkan_LoadLibrary(SDL_VideoDevice *_this, ଅଚଳ ଅକ୍ଷର *path)
{
    VkExtensionProperties *extensions = ଖାଲି;
    Uint32 extension_ଗଣନା = 0;
    bool hasSurfaceExtension = false;
    bool hasOHOSSurfaceExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = ଖାଲି;

    ଯଦି (_this->vulkan_config.loader_handle) {
        ଫେରନ୍ତୁ SDL_SetError("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    ଯଦି (!path) {
        path = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
        ଯଦି (!path) {
            path = "libvulkan.so";
        }
    }

    SDL_SharedObject *lib = SDL_LoadObject(path);
    _this->vulkan_config.loader_handle = lib;
    ଯଦି (!lib) {
        ଫେରନ୍ତୁ false;
    }

    SDL_strlcpy(_this->vulkan_config.loader_path, path, ଆକାର (_this->vulkan_config.loader_path));
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr) SDL_LoadFunction(lib, "vkGetInstanceProcAddr");
    ଯଦି (!vkGetInstanceProcAddr) {
        ଯାଅ fail;
    }

    _this->vulkan_config.vkGetInstanceProcAddr = (ଶୂନ୍ୟ *)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties = (ଶୂନ୍ୟ *)((PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr)(VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties");
    ଯଦି (!_this->vulkan_config.vkEnumerateInstanceExtensionProperties) {
        ଯାଅ fail;
    }

    extensions = SDL_Vulkan_CreateInstanceExtensionsList((PFN_vkEnumerateInstanceExtensionProperties) _this->vulkan_config.vkEnumerateInstanceExtensionProperties, &extension_ଗଣନା);
    ଯଦି (!extensions) {
        ଯାଅ fail;
    }

    ପାଇଁ (Uint32 i = 0; i < extension_ଗଣନା; i++) {
        ଯଦି (SDL_strcmp(VK_KHR_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasSurfaceExtension = true;
        } ଅନ୍ୟଥା ଯଦି (SDL_strcmp(VK_OHOS_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasOHOSSurfaceExtension = true;
        }
    }

    SDL_free(extensions);

    ଯଦି (!hasSurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        ଯାଅ fail;
    } ଅନ୍ୟଥା ଯଦି (!hasOHOSSurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_OHOS_SURFACE_EXTENSION_NAME " extension");
        ଯାଅ fail;
    }

    ଫେରନ୍ତୁ true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = ଖାଲି;
    ଫେରନ୍ତୁ false;
}

ଶୂନ୍ୟ OPENHARMONY_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    ଯଦି (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = ଖାଲି;
    }
}

ଅକ୍ଷର ଅଚଳ * ଅଚଳ *OPENHARMONY_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *ଗଣନା_2)
{
    ସ୍ଥିର ଅଚଳ ଅକ୍ଷର *ଅଚଳ extensionsForOpenHarmony[] = {
        VK_KHR_SURFACE_EXTENSION_NAME, VK_OHOS_SURFACE_EXTENSION_NAME
    };
    ଯଦି (ଗଣନା_2) {
        *ଗଣନା_2 = SDL_arraysize(extensionsForOpenHarmony);
    }
    ଫେରନ୍ତୁ extensionsForOpenHarmony;
}

bool OPENHARMONY_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                                 SDL_Window *window,
                                 VkInstance instance,
                                 ଅଚଳ ସଂରଚନା VkAllocationCallbacks *allocator,
                                 VkSurfaceKHR *surface)
{
    SDL_WindowData *windowData = window->internal;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    PFN_vkCreateSurfaceOHOS vkCreateSurfaceOHOS = (PFN_vkCreateSurfaceOHOS ) vkGetInstanceProcAddr(instance, "vkCreateSurfaceOHOS");
    VkSurfaceCreateInfoOHOS createInfo;
    VkResult result;

    ଯଦି (!_this->vulkan_config.loader_handle) {
        ଫେରନ୍ତୁ SDL_SetError("Vulkan is not loaded");
    }

    ଯଦି (!vkCreateSurfaceOHOS) {
        ଫେରନ୍ତୁ SDL_SetError(VK_OHOS_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
    }

    SDL_zero(createInfo);
    createInfo.sType = VK_STRUCTURE_TYPE_SURFACE_CREATE_INFO_OHOS;
    createInfo.pNext = ଖାଲି;
    createInfo.flags = 0;
    createInfo.window = (OHNativeWindow *) windowData->native_window;
    result = vkCreateSurfaceOHOS(instance, &createInfo, allocator, surface);
    ଯଦି (result != VK_SUCCESS) {
        ଯଦି (result == VK_ERROR_NATIVE_WINDOW_IN_USE_KHR) {
            ଫେରନ୍ତୁ SDL_SetError("vkCreateSurfaceOHOS failed: %s, was the window created with SDL_WINDOW_VULKAN?", SDL_Vulkan_GetResultString(result));
        } ଅନ୍ୟଥା {
            ଫେରନ୍ତୁ SDL_SetError("vkCreateSurfaceOHOS failed: %s", SDL_Vulkan_GetResultString(result));
        }
    }
    ଫେରନ୍ତୁ true;
}

ଶୂନ୍ୟ OPENHARMONY_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                   VkInstance instance,
                                   VkSurfaceKHR surface,
                                   ଅଚଳ ସଂରଚନା VkAllocationCallbacks *allocator)
{
    ଯଦି (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_DestroySurface_Internal(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

#endif

