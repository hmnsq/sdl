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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_OFFSCREEN)

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_vulkan_internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"


ਸਥਿਰ ਅਚਲ ਅੱਖਰ *s_defaultPaths[] = {
#ਜੇ defined(SDL_PLATFORM_WINDOWS)
    "vulkan-1.dll"
#ਜਾਂਜੇ defined(SDL_PLATFORM_APPLE)
    "vulkan.framework/vulkan",
    "libvulkan.1.dylib",
    "libvulkan.dylib",
    "MoltenVK.framework/MoltenVK",
    "libMoltenVK.dylib"
#ਜਾਂਜੇ defined(SDL_PLATFORM_OPENBSD)
    "libvulkan.so"
#ਨਹੀਂਤਾਂ
    "libvulkan.so.1"
#ਜੇ_ਅੰਤ
};

SDL_ELF_NOTE_DLOPEN(
    "offscreen-vulkan",
    "Support for offscreen Vulkan",
    SDL_ELF_NOTE_DLOPEN_ਤਰਜੀਹ_SUGGESTED,
    "libvulkan.so.1"
)

#ਜੇ defined( SDL_PLATFORM_APPLE )
#ਅਨ੍ਤਰ੍ਭਾਵ <dlfcn.h>

// Since libSDL is most likely a .dylib, need RTLD_DEFAULT not RTLD_SELF.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFAULT_HANDLE RTLD_DEFAULT
#ਜੇ_ਅੰਤ

/*Should the whole driver fail if it can't create a surface? Rendering to an offscreen buffer is still possible without a surface.
    At the time of writing. I need the driver to minimally work even if the surface extension isn't present.
    And account for the inability to create a surface on the consumer side.
    So for now I'm targeting my specific use case -Dave Kircher*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HEADLESS_SURFACE_EXTENSION_REQUIRED_ਮੰਜ਼ਿਲ_ਲੱਦੋ 0


bool OFFSCREEN_Vulkan_ਲੱਦੋ_Library(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *ਰਸਤਾ)
{
    VkExtensionProperties *extensions = ਨਿਰਾ;
    Uint32 extension_ਗਿਣਤੀ = 0;
    bool hasSurfaceExtension = false;
    bool hasHeadlessSurfaceExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = ਨਿਰਾ;
    Uint32 i;
    ਅਚਲ ਅੱਖਰ **paths;
    ਅਚਲ ਅੱਖਰ *ਮਿਲਿਆ_ਰਸਤਾ = ਨਿਰਾ;
    Uint32 ਅੰਕ_Paths;

    ਜੇ (_this->vulkan_config.loader_handle) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    ਜੇ (!ਰਸਤਾ) {
        ਰਸਤਾ = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }

#ਜੇ defined(SDL_PLATFORM_APPLE)
    ਜੇ (!ਰਸਤਾ) {
        // Handle the case where Vulkan Portability is linked statically.
        vkGetInstanceProcAddr =
            (PFN_vkGetInstanceProcAddr)dlsym(DEFAULT_HANDLE,
                                             "vkGetInstanceProcAddr");
    }

    ਜੇ (vkGetInstanceProcAddr) {
        _this->vulkan_config.loader_handle = DEFAULT_HANDLE;
    } ਨਹੀਂਤਾਂ
#ਜੇ_ਅੰਤ
    {
        ਜੇ (ਰਸਤਾ) {
            paths = &ਰਸਤਾ;
            ਅੰਕ_Paths = 1;
        } ਨਹੀਂਤਾਂ {
            paths = s_defaultPaths;
            ਅੰਕ_Paths = SDL_arraysize(s_defaultPaths);
        }

        ਲਈ (i = 0; i < ਅੰਕ_Paths && _this->vulkan_config.loader_handle == ਨਿਰਾ; i++) {
            ਮਿਲਿਆ_ਰਸਤਾ = paths[i];
            _this->vulkan_config.loader_handle = SDL_ਲੱਦੋ_Object(ਮਿਲਿਆ_ਰਸਤਾ);
        }

        ਜੇ (_this->vulkan_config.loader_handle == ਨਿਰਾ) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("Failed to load Vulkan Portability library");
        }

        SDL_strlcpy(_this->vulkan_config.loader_ਰਸਤਾ, ਮਿਲਿਆ_ਰਸਤਾ,
                    SDL_arraysize(_this->vulkan_config.loader_ਰਸਤਾ));
        vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)SDL_ਲੱਦੋ_Function(
            _this->vulkan_config.loader_handle, "vkGetInstanceProcAddr");

        ਜੇ (!vkGetInstanceProcAddr) {
            SDL_ਸੈੱਟ_Error("Failed to load vkGetInstanceProcAddr from Vulkan Portability library");
            ਜਾਓ fail;
        }
    }

    _this->vulkan_config.vkGetInstanceProcAddr = (SDL_Function_ਸੂਚਕ)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties =
        (SDL_Function_ਸੂਚਕ)((PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr)(
            VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties");
    ਜੇ (!_this->vulkan_config.vkEnumerateInstanceExtensionProperties) {
        ਜਾਓ fail;
    }
    extensions = SDL_Vulkan_CreateInstanceExtensionsList(
        (PFN_vkEnumerateInstanceExtensionProperties)
            _this->vulkan_config.vkEnumerateInstanceExtensionProperties,
        &extension_ਗਿਣਤੀ);
    ਜੇ (!extensions) {
        ਜਾਓ fail;
    }
    ਲਈ (i = 0; i < extension_ਗਿਣਤੀ; i++) {
        ਜੇ (SDL_strcmp(VK_KHR_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasSurfaceExtension = true;
        } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasHeadlessSurfaceExtension = true;
        }
    }
    SDL_free(extensions);
    ਜੇ (!hasSurfaceExtension) {
        SDL_ਸੈੱਟ_Error("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        ਜਾਓ fail;
    }
    ਜੇ (!hasHeadlessSurfaceExtension) {
#ਜੇ (HEADLESS_SURFACE_EXTENSION_REQUIRED_ਮੰਜ਼ਿਲ_ਲੱਦੋ != 0)
        SDL_ਸੈੱਟ_Error("Installed Vulkan doesn't implement the " VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME " extension");
        ਜਾਓ fail;
#ਨਹੀਂਤਾਂ
        // Let's at least leave a breadcrumb for people to find if they have issues
        SDL_Log("Installed Vulkan doesn't implement the " VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME " extension");
#ਜੇ_ਅੰਤ
    }
    ਵਾਪਸ true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = ਨਿਰਾ;
    ਵਾਪਸ false;
}

ਖਾਲੀ OFFSCREEN_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    ਜੇ (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = ਨਿਰਾ;
    }
}

ਅੱਖਰ ਅਚਲ *ਅਚਲ *OFFSCREEN_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this,
                                                          Uint32 *ਗਿਣਤੀ_2)
{
    ਸਥਿਰ ਅਚਲ ਅੱਖਰ *ਅਚਲ returnExtensions[] = { VK_KHR_SURFACE_EXTENSION_NAME, VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME };

    *ਗਿਣਤੀ_2 = SDL_arraysize(returnExtensions);

#ਜੇ (HEADLESS_SURFACE_EXTENSION_REQUIRED_ਮੰਜ਼ਿਲ_ਲੱਦੋ == 0)
    VkExtensionProperties *enumerateExtensions = ਨਿਰਾ;
    Uint32 enumerate_Extension_ਗਿਣਤੀ = 0;
    bool hasHeadlessSurfaceExtension = false;
    Uint32 i;

    /* In optional mode, only return VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME if it's already supported by the instance
       There's probably a better way to cache the presence of the extension during OFFSCREEN_Vulkan_LoadLibrary().
       But both SDL_VideoData and SDL_VideoDevice::vulkan_config seem like I'd need to touch a bunch of code to do properly.
       And I want a smaller footprint for the first pass*/
    ਜੇ ( _this->vulkan_config.vkEnumerateInstanceExtensionProperties ) {
        enumerateExtensions = SDL_Vulkan_CreateInstanceExtensionsList((PFN_vkEnumerateInstanceExtensionProperties) _this->vulkan_config.vkEnumerateInstanceExtensionProperties, &enumerate_Extension_ਗਿਣਤੀ);
        ਲਈ (i = 0; i < enumerate_Extension_ਗਿਣਤੀ; i++) {
            ਜੇ (SDL_strcmp(VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME, enumerateExtensions[i].extensionName) == 0) {
                hasHeadlessSurfaceExtension = true;
            }
        }
        SDL_free(enumerateExtensions);
    }

    ਜੇ (!hasHeadlessSurfaceExtension) {
        (*ਗਿਣਤੀ_2)--;  // assumes VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME is last
    }
#ਜੇ_ਅੰਤ

    ਵਾਪਸ returnExtensions;
}

bool OFFSCREEN_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                                   SDL_ਖਿੜਕੀ *ਖਿੜਕੀ,
                                   VkInstance instance,
                                   ਅਚਲ ਬਣਤਰ Vk_ਵੰਡ_Callbacks *allocator,
                                   VkSurfaceKHR *surface)
{
    *surface = VK_NULL_HANDLE;

    ਜੇ (!_this->vulkan_config.loader_handle) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Vulkan is not loaded");
    }

    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    PFN_vkCreateHeadlessSurfaceEXT vkCreateHeadlessSurfaceEXT =
        (PFN_vkCreateHeadlessSurfaceEXT)vkGetInstanceProcAddr(instance, "vkCreateHeadlessSurfaceEXT");
    VkHeadlessSurfaceCreateInfoEXT createInfo;
    Vk_ਨਤੀਜਾ ਨਤੀਜਾ;
    ਜੇ (!vkCreateHeadlessSurfaceEXT) {
        /* This may be surprising to the consumer when HEADLESS_SURFACE_EXTENSION_REQUIRED_TO_LOAD == 0
           But this is the tradeoff for allowing offscreen rendering to a buffer to continue working without requiring the extension during driver load */
        ਵਾਪਸ SDL_ਸੈੱਟ_Error(VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME
                            " extension is not enabled in the Vulkan instance.");
    }
    SDL_zero(createInfo);
    createInfo.sType = VK_STRUCTURE_TYPE_HEADLESS_SURFACE_CREATE_INFO_EXT;
    createInfo.p_ਅਗਲਾ = ਨਿਰਾ;
    createInfo.flags = 0;
    ਨਤੀਜਾ = vkCreateHeadlessSurfaceEXT(instance, &createInfo, allocator, surface);
    ਜੇ (ਨਤੀਜਾ != VK_SUCCESS) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("vkCreateHeadlessSurfaceEXT failed: %s", SDL_Vulkan_Get_ਨਤੀਜਾ_String(ਨਤੀਜਾ));
    }
    ਵਾਪਸ true;
}

ਖਾਲੀ OFFSCREEN_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                     VkInstance instance,
                                     VkSurfaceKHR surface,
                                     ਅਚਲ ਬਣਤਰ Vk_ਵੰਡ_Callbacks *allocator)
{
    ਜੇ (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_Destroy_Surface_ਅੰਦਰੂਨੀ(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

#ਜੇ_ਅੰਤ
