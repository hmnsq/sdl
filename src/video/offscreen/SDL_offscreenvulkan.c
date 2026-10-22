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
#अन्तर्भाव "SDL_internal.h"

#जर defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_OFFSCREEN)

#अन्तर्भाव "../SDL_vulkan_internal.h"
#अन्तर्भाव "../SDL_sysvideo.h"


स्थिर स्थिरांक अक्षर *s_defaultPaths[] = {
#जर defined(SDL_PLATFORM_WINDOWS)
    "vulkan-1.dll"
#किंवाजर defined(SDL_PLATFORM_APPLE)
    "vulkan.framework/vulkan",
    "libvulkan.1.dylib",
    "libvulkan.dylib",
    "MoltenVK.framework/MoltenVK",
    "libMoltenVK.dylib"
#किंवाजर defined(SDL_PLATFORM_OPENBSD)
    "libvulkan.so"
#अन्यथा
    "libvulkan.so.1"
#endif
};

SDL_ELF_NOTE_DLOPEN(
    "offscreen-vulkan",
    "Support for offscreen Vulkan",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_SUGGESTED,
    "libvulkan.so.1"
)

#जर defined( SDL_PLATFORM_APPLE )
#अन्तर्भाव <dlfcn.h>

// Since libSDL is most likely a .dylib, need RTLD_DEFAULT not RTLD_SELF.
#define DEFAULT_HANDLE RTLD_DEFAULT
#endif

/*Should the whole driver fail if it can't create a surface? Rendering to an offscreen buffer is still possible without a surface.
    At the time of writing. I need the driver to minimally work even if the surface extension isn't present.
    And account for the inability to create a surface on the consumer side.
    So for now I'm targeting my specific use case -Dave Kircher*/
#define HEADLESS_SURFACE_EXTENSION_REQUIRED_TO_LOAD 0


bool OFFSCREEN_Vulkan_LoadLibrary(SDL_VideoDevice *_this, स्थिरांक अक्षर *path)
{
    VkExtensionProperties *extensions = रिक्त;
    Uint32 extension_मोजणी = 0;
    bool hasSurfaceExtension = false;
    bool hasHeadlessSurfaceExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = रिक्त;
    Uint32 i;
    स्थिरांक अक्षर **paths;
    स्थिरांक अक्षर *foundPath = रिक्त;
    Uint32 अंक_Paths;

    जर (_this->vulkan_config.loader_handle) {
        परत SDL_SetError("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    जर (!path) {
        path = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }

#जर defined(SDL_PLATFORM_APPLE)
    जर (!path) {
        // Handle the case where Vulkan Portability is linked statically.
        vkGetInstanceProcAddr =
            (PFN_vkGetInstanceProcAddr)dlsym(DEFAULT_HANDLE,
                                             "vkGetInstanceProcAddr");
    }

    जर (vkGetInstanceProcAddr) {
        _this->vulkan_config.loader_handle = DEFAULT_HANDLE;
    } अन्यथा
#endif
    {
        जर (path) {
            paths = &path;
            अंक_Paths = 1;
        } अन्यथा {
            paths = s_defaultPaths;
            अंक_Paths = SDL_arraysize(s_defaultPaths);
        }

        साठी (i = 0; i < अंक_Paths && _this->vulkan_config.loader_handle == रिक्त; i++) {
            foundPath = paths[i];
            _this->vulkan_config.loader_handle = SDL_LoadObject(foundPath);
        }

        जर (_this->vulkan_config.loader_handle == रिक्त) {
            परत SDL_SetError("Failed to load Vulkan Portability library");
        }

        SDL_strlcpy(_this->vulkan_config.loader_path, foundPath,
                    SDL_arraysize(_this->vulkan_config.loader_path));
        vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)SDL_LoadFunction(
            _this->vulkan_config.loader_handle, "vkGetInstanceProcAddr");

        जर (!vkGetInstanceProcAddr) {
            SDL_SetError("Failed to load vkGetInstanceProcAddr from Vulkan Portability library");
            जा fail;
        }
    }

    _this->vulkan_config.vkGetInstanceProcAddr = (SDL_FunctionPointer)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties =
        (SDL_FunctionPointer)((PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr)(
            VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties");
    जर (!_this->vulkan_config.vkEnumerateInstanceExtensionProperties) {
        जा fail;
    }
    extensions = SDL_Vulkan_CreateInstanceExtensionsList(
        (PFN_vkEnumerateInstanceExtensionProperties)
            _this->vulkan_config.vkEnumerateInstanceExtensionProperties,
        &extension_मोजणी);
    जर (!extensions) {
        जा fail;
    }
    साठी (i = 0; i < extension_मोजणी; i++) {
        जर (SDL_strcmp(VK_KHR_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasSurfaceExtension = true;
        } अन्यथा जर (SDL_strcmp(VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasHeadlessSurfaceExtension = true;
        }
    }
    SDL_free(extensions);
    जर (!hasSurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        जा fail;
    }
    जर (!hasHeadlessSurfaceExtension) {
#जर (HEADLESS_SURFACE_EXTENSION_REQUIRED_TO_LOAD != 0)
        SDL_SetError("Installed Vulkan doesn't implement the " VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME " extension");
        जा fail;
#अन्यथा
        // Let's at least leave a breadcrumb for people to find if they have issues
        SDL_Log("Installed Vulkan doesn't implement the " VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME " extension");
#endif
    }
    परत true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = रिक्त;
    परत false;
}

शून्य OFFSCREEN_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    जर (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = रिक्त;
    }
}

अक्षर स्थिरांक *स्थिरांक *OFFSCREEN_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this,
                                                          Uint32 *मोजणी)
{
    स्थिर स्थिरांक अक्षर *स्थिरांक returnExtensions[] = { VK_KHR_SURFACE_EXTENSION_NAME, VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME };

    *मोजणी = SDL_arraysize(returnExtensions);

#जर (HEADLESS_SURFACE_EXTENSION_REQUIRED_TO_LOAD == 0)
    VkExtensionProperties *enumerateExtensions = रिक्त;
    Uint32 enumerate_Extension_मोजणी = 0;
    bool hasHeadlessSurfaceExtension = false;
    Uint32 i;

    /* In optional mode, only return VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME if it's already supported by the instance
       There's probably a better way to cache the presence of the extension during OFFSCREEN_Vulkan_LoadLibrary().
       But both SDL_VideoData and SDL_VideoDevice::vulkan_config seem like I'd need to touch a bunch of code to do properly.
       And I want a smaller footprint for the first pass*/
    जर ( _this->vulkan_config.vkEnumerateInstanceExtensionProperties ) {
        enumerateExtensions = SDL_Vulkan_CreateInstanceExtensionsList((PFN_vkEnumerateInstanceExtensionProperties) _this->vulkan_config.vkEnumerateInstanceExtensionProperties, &enumerate_Extension_मोजणी);
        साठी (i = 0; i < enumerate_Extension_मोजणी; i++) {
            जर (SDL_strcmp(VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME, enumerateExtensions[i].extensionName) == 0) {
                hasHeadlessSurfaceExtension = true;
            }
        }
        SDL_free(enumerateExtensions);
    }

    जर (!hasHeadlessSurfaceExtension) {
        (*मोजणी)--;  // assumes VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME is last
    }
#endif

    परत returnExtensions;
}

bool OFFSCREEN_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                                   SDL_Window *window,
                                   VkInstance instance,
                                   स्थिरांक संरचना VkAllocationCallbacks *allocator,
                                   VkSurfaceKHR *surface)
{
    *surface = VK_NULL_HANDLE;

    जर (!_this->vulkan_config.loader_handle) {
        परत SDL_SetError("Vulkan is not loaded");
    }

    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    PFN_vkCreateHeadlessSurfaceEXT vkCreateHeadlessSurfaceEXT =
        (PFN_vkCreateHeadlessSurfaceEXT)vkGetInstanceProcAddr(instance, "vkCreateHeadlessSurfaceEXT");
    VkHeadlessSurfaceCreateInfoEXT createInfo;
    VkResult result;
    जर (!vkCreateHeadlessSurfaceEXT) {
        /* This may be surprising to the consumer when HEADLESS_SURFACE_EXTENSION_REQUIRED_TO_LOAD == 0
           But this is the tradeoff for allowing offscreen rendering to a buffer to continue working without requiring the extension during driver load */
        परत SDL_SetError(VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME
                            " extension is not enabled in the Vulkan instance.");
    }
    SDL_zero(createInfo);
    createInfo.sType = VK_STRUCTURE_TYPE_HEADLESS_SURFACE_CREATE_INFO_EXT;
    createInfo.pNext = रिक्त;
    createInfo.flags = 0;
    result = vkCreateHeadlessSurfaceEXT(instance, &createInfo, allocator, surface);
    जर (result != VK_SUCCESS) {
        परत SDL_SetError("vkCreateHeadlessSurfaceEXT failed: %s", SDL_Vulkan_GetResultString(result));
    }
    परत true;
}

शून्य OFFSCREEN_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                     VkInstance instance,
                                     VkSurfaceKHR surface,
                                     स्थिरांक संरचना VkAllocationCallbacks *allocator)
{
    जर (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_DestroySurface_Internal(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

#endif
