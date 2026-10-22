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
#അന്തര്ഭാവ "SDL_internal.h"

#എങ്കിൽ defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_OFFSCREEN)

#അന്തര്ഭാവ "../SDL_vulkan_internal.h"
#അന്തര്ഭാവ "../SDL_sysvideo.h"


സ്ഥിതം സ്ഥിരം അക്ഷരം *s_defaultPaths[] = {
#എങ്കിൽ defined(SDL_PLATFORM_WINDOWS)
    "vulkan-1.dll"
#അല്ലെങ്കിലെങ്കിൽ defined(SDL_PLATFORM_APPLE)
    "vulkan.framework/vulkan",
    "libvulkan.1.dylib",
    "libvulkan.dylib",
    "MoltenVK.framework/MoltenVK",
    "libMoltenVK.dylib"
#അല്ലെങ്കിലെങ്കിൽ defined(SDL_PLATFORM_OPENBSD)
    "libvulkan.so"
#അല്ലെങ്കിൽ
    "libvulkan.so.1"
#endif
};

SDL_ELF_NOTE_DLOPEN(
    "offscreen-vulkan",
    "Support for offscreen Vulkan",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_SUGGESTED,
    "libvulkan.so.1"
)

#എങ്കിൽ defined( SDL_PLATFORM_APPLE )
#അന്തര്ഭാവ <dlfcn.h>

// Since libSDL is most likely a .dylib, need RTLD_DEFAULT not RTLD_SELF.
#define DEFAULT_HANDLE RTLD_DEFAULT
#endif

/*Should the whole driver fail if it can't create a surface? Rendering to an offscreen buffer is still possible without a surface.
    At the time of writing. I need the driver to minimally work even if the surface extension isn't present.
    And account for the inability to create a surface on the consumer side.
    So for now I'm targeting my specific use case -Dave Kircher*/
#define HEADLESS_SURFACE_EXTENSION_REQUIRED_TO_LOAD 0


bool OFFSCREEN_Vulkan_LoadLibrary(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *path)
{
    VkExtensionProperties *extensions = ശൂന്യ;
    Uint32 extension_എണ്ണം = 0;
    bool hasSurfaceExtension = false;
    bool hasHeadlessSurfaceExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = ശൂന്യ;
    Uint32 i;
    സ്ഥിരം അക്ഷരം **paths;
    സ്ഥിരം അക്ഷരം *foundPath = ശൂന്യ;
    Uint32 അക്കം_Paths;

    എങ്കിൽ (_this->vulkan_config.loader_handle) {
        തിരികെ SDL_SetError("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    എങ്കിൽ (!path) {
        path = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }

#എങ്കിൽ defined(SDL_PLATFORM_APPLE)
    എങ്കിൽ (!path) {
        // Handle the case where Vulkan Portability is linked statically.
        vkGetInstanceProcAddr =
            (PFN_vkGetInstanceProcAddr)dlsym(DEFAULT_HANDLE,
                                             "vkGetInstanceProcAddr");
    }

    എങ്കിൽ (vkGetInstanceProcAddr) {
        _this->vulkan_config.loader_handle = DEFAULT_HANDLE;
    } അല്ലെങ്കിൽ
#endif
    {
        എങ്കിൽ (path) {
            paths = &path;
            അക്കം_Paths = 1;
        } അല്ലെങ്കിൽ {
            paths = s_defaultPaths;
            അക്കം_Paths = SDL_arraysize(s_defaultPaths);
        }

        വേണ്ടി (i = 0; i < അക്കം_Paths && _this->vulkan_config.loader_handle == ശൂന്യ; i++) {
            foundPath = paths[i];
            _this->vulkan_config.loader_handle = SDL_LoadObject(foundPath);
        }

        എങ്കിൽ (_this->vulkan_config.loader_handle == ശൂന്യ) {
            തിരികെ SDL_SetError("Failed to load Vulkan Portability library");
        }

        SDL_strlcpy(_this->vulkan_config.loader_path, foundPath,
                    SDL_arraysize(_this->vulkan_config.loader_path));
        vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)SDL_LoadFunction(
            _this->vulkan_config.loader_handle, "vkGetInstanceProcAddr");

        എങ്കിൽ (!vkGetInstanceProcAddr) {
            SDL_SetError("Failed to load vkGetInstanceProcAddr from Vulkan Portability library");
            പോകുക fail;
        }
    }

    _this->vulkan_config.vkGetInstanceProcAddr = (SDL_FunctionPointer)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties =
        (SDL_FunctionPointer)((PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr)(
            VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties");
    എങ്കിൽ (!_this->vulkan_config.vkEnumerateInstanceExtensionProperties) {
        പോകുക fail;
    }
    extensions = SDL_Vulkan_CreateInstanceExtensionsList(
        (PFN_vkEnumerateInstanceExtensionProperties)
            _this->vulkan_config.vkEnumerateInstanceExtensionProperties,
        &extension_എണ്ണം);
    എങ്കിൽ (!extensions) {
        പോകുക fail;
    }
    വേണ്ടി (i = 0; i < extension_എണ്ണം; i++) {
        എങ്കിൽ (SDL_strcmp(VK_KHR_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasSurfaceExtension = true;
        } അല്ലെങ്കിൽ എങ്കിൽ (SDL_strcmp(VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasHeadlessSurfaceExtension = true;
        }
    }
    SDL_free(extensions);
    എങ്കിൽ (!hasSurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        പോകുക fail;
    }
    എങ്കിൽ (!hasHeadlessSurfaceExtension) {
#എങ്കിൽ (HEADLESS_SURFACE_EXTENSION_REQUIRED_TO_LOAD != 0)
        SDL_SetError("Installed Vulkan doesn't implement the " VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME " extension");
        പോകുക fail;
#അല്ലെങ്കിൽ
        // Let's at least leave a breadcrumb for people to find if they have issues
        SDL_Log("Installed Vulkan doesn't implement the " VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME " extension");
#endif
    }
    തിരികെ true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = ശൂന്യ;
    തിരികെ false;
}

ശൂന്യം OFFSCREEN_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    എങ്കിൽ (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = ശൂന്യ;
    }
}

അക്ഷരം സ്ഥിരം *സ്ഥിരം *OFFSCREEN_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this,
                                                          Uint32 *എണ്ണം)
{
    സ്ഥിതം സ്ഥിരം അക്ഷരം *സ്ഥിരം returnExtensions[] = { VK_KHR_SURFACE_EXTENSION_NAME, VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME };

    *എണ്ണം = SDL_arraysize(returnExtensions);

#എങ്കിൽ (HEADLESS_SURFACE_EXTENSION_REQUIRED_TO_LOAD == 0)
    VkExtensionProperties *enumerateExtensions = ശൂന്യ;
    Uint32 enumerate_Extension_എണ്ണം = 0;
    bool hasHeadlessSurfaceExtension = false;
    Uint32 i;

    /* In optional mode, only return VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME if it's already supported by the instance
       There's probably a better way to cache the presence of the extension during OFFSCREEN_Vulkan_LoadLibrary().
       But both SDL_VideoData and SDL_VideoDevice::vulkan_config seem like I'd need to touch a bunch of code to do properly.
       And I want a smaller footprint for the first pass*/
    എങ്കിൽ ( _this->vulkan_config.vkEnumerateInstanceExtensionProperties ) {
        enumerateExtensions = SDL_Vulkan_CreateInstanceExtensionsList((PFN_vkEnumerateInstanceExtensionProperties) _this->vulkan_config.vkEnumerateInstanceExtensionProperties, &enumerate_Extension_എണ്ണം);
        വേണ്ടി (i = 0; i < enumerate_Extension_എണ്ണം; i++) {
            എങ്കിൽ (SDL_strcmp(VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME, enumerateExtensions[i].extensionName) == 0) {
                hasHeadlessSurfaceExtension = true;
            }
        }
        SDL_free(enumerateExtensions);
    }

    എങ്കിൽ (!hasHeadlessSurfaceExtension) {
        (*എണ്ണം)--;  // assumes VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME is last
    }
#endif

    തിരികെ returnExtensions;
}

bool OFFSCREEN_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                                   SDL_Window *window,
                                   VkInstance instance,
                                   സ്ഥിരം ഘടന VkAllocationCallbacks *allocator,
                                   VkSurfaceKHR *surface)
{
    *surface = VK_NULL_HANDLE;

    എങ്കിൽ (!_this->vulkan_config.loader_handle) {
        തിരികെ SDL_SetError("Vulkan is not loaded");
    }

    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    PFN_vkCreateHeadlessSurfaceEXT vkCreateHeadlessSurfaceEXT =
        (PFN_vkCreateHeadlessSurfaceEXT)vkGetInstanceProcAddr(instance, "vkCreateHeadlessSurfaceEXT");
    VkHeadlessSurfaceCreateInfoEXT createInfo;
    VkResult result;
    എങ്കിൽ (!vkCreateHeadlessSurfaceEXT) {
        /* This may be surprising to the consumer when HEADLESS_SURFACE_EXTENSION_REQUIRED_TO_LOAD == 0
           But this is the tradeoff for allowing offscreen rendering to a buffer to continue working without requiring the extension during driver load */
        തിരികെ SDL_SetError(VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME
                            " extension is not enabled in the Vulkan instance.");
    }
    SDL_zero(createInfo);
    createInfo.sType = VK_STRUCTURE_TYPE_HEADLESS_SURFACE_CREATE_INFO_EXT;
    createInfo.pNext = ശൂന്യ;
    createInfo.flags = 0;
    result = vkCreateHeadlessSurfaceEXT(instance, &createInfo, allocator, surface);
    എങ്കിൽ (result != VK_SUCCESS) {
        തിരികെ SDL_SetError("vkCreateHeadlessSurfaceEXT failed: %s", SDL_Vulkan_GetResultString(result));
    }
    തിരികെ true;
}

ശൂന്യം OFFSCREEN_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                     VkInstance instance,
                                     VkSurfaceKHR surface,
                                     സ്ഥിരം ഘടന VkAllocationCallbacks *allocator)
{
    എങ്കിൽ (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_DestroySurface_Internal(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

#endif
