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

#जर defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_OPENHARMONY)

#अन्तर्भाव "../SDL_vulkan_internal.h"

#अन्तर्भाव "SDL_openharmonyvideo.h"
#अन्तर्भाव "SDL_openharmonywindow.h"

#अन्तर्भाव "SDL_openharmonyvulkan.h"


bool OPENHARMONY_Vulkan_LoadLibrary(SDL_VideoDevice *_this, स्थिरांक अक्षर *path)
{
    VkExtensionProperties *extensions = रिक्त;
    Uint32 extension_मोजणी = 0;
    bool hasSurfaceExtension = false;
    bool hasOHOSSurfaceExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = रिक्त;

    जर (_this->vulkan_config.loader_handle) {
        परत SDL_SetError("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    जर (!path) {
        path = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
        जर (!path) {
            path = "libvulkan.so";
        }
    }

    SDL_SharedObject *lib = SDL_LoadObject(path);
    _this->vulkan_config.loader_handle = lib;
    जर (!lib) {
        परत false;
    }

    SDL_strlcpy(_this->vulkan_config.loader_path, path, आकार (_this->vulkan_config.loader_path));
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr) SDL_LoadFunction(lib, "vkGetInstanceProcAddr");
    जर (!vkGetInstanceProcAddr) {
        जा fail;
    }

    _this->vulkan_config.vkGetInstanceProcAddr = (शून्य *)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties = (शून्य *)((PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr)(VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties");
    जर (!_this->vulkan_config.vkEnumerateInstanceExtensionProperties) {
        जा fail;
    }

    extensions = SDL_Vulkan_CreateInstanceExtensionsList((PFN_vkEnumerateInstanceExtensionProperties) _this->vulkan_config.vkEnumerateInstanceExtensionProperties, &extension_मोजणी);
    जर (!extensions) {
        जा fail;
    }

    साठी (Uint32 i = 0; i < extension_मोजणी; i++) {
        जर (SDL_strcmp(VK_KHR_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasSurfaceExtension = true;
        } अन्यथा जर (SDL_strcmp(VK_OHOS_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasOHOSSurfaceExtension = true;
        }
    }

    SDL_free(extensions);

    जर (!hasSurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        जा fail;
    } अन्यथा जर (!hasOHOSSurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_OHOS_SURFACE_EXTENSION_NAME " extension");
        जा fail;
    }

    परत true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = रिक्त;
    परत false;
}

शून्य OPENHARMONY_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    जर (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = रिक्त;
    }
}

अक्षर स्थिरांक * स्थिरांक *OPENHARMONY_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *मोजणी)
{
    स्थिर स्थिरांक अक्षर *स्थिरांक extensionsForOpenHarmony[] = {
        VK_KHR_SURFACE_EXTENSION_NAME, VK_OHOS_SURFACE_EXTENSION_NAME
    };
    जर (मोजणी) {
        *मोजणी = SDL_arraysize(extensionsForOpenHarmony);
    }
    परत extensionsForOpenHarmony;
}

bool OPENHARMONY_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                                 SDL_Window *window,
                                 VkInstance instance,
                                 स्थिरांक संरचना VkAllocationCallbacks *allocator,
                                 VkSurfaceKHR *surface)
{
    SDL_WindowData *windowData = window->internal;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    PFN_vkCreateSurfaceOHOS vkCreateSurfaceOHOS = (PFN_vkCreateSurfaceOHOS ) vkGetInstanceProcAddr(instance, "vkCreateSurfaceOHOS");
    VkSurfaceCreateInfoOHOS createInfo;
    VkResult result;

    जर (!_this->vulkan_config.loader_handle) {
        परत SDL_SetError("Vulkan is not loaded");
    }

    जर (!vkCreateSurfaceOHOS) {
        परत SDL_SetError(VK_OHOS_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
    }

    SDL_zero(createInfo);
    createInfo.sType = VK_STRUCTURE_TYPE_SURFACE_CREATE_INFO_OHOS;
    createInfo.pNext = रिक्त;
    createInfo.flags = 0;
    createInfo.window = (OHNativeWindow *) windowData->native_window;
    result = vkCreateSurfaceOHOS(instance, &createInfo, allocator, surface);
    जर (result != VK_SUCCESS) {
        जर (result == VK_ERROR_NATIVE_WINDOW_IN_USE_KHR) {
            परत SDL_SetError("vkCreateSurfaceOHOS failed: %s, was the window created with SDL_WINDOW_VULKAN?", SDL_Vulkan_GetResultString(result));
        } अन्यथा {
            परत SDL_SetError("vkCreateSurfaceOHOS failed: %s", SDL_Vulkan_GetResultString(result));
        }
    }
    परत true;
}

शून्य OPENHARMONY_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                   VkInstance instance,
                                   VkSurfaceKHR surface,
                                   स्थिरांक संरचना VkAllocationCallbacks *allocator)
{
    जर (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_DestroySurface_Internal(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

#endif

