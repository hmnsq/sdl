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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ಆದರೆ defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_OFFSCREEN)

#ಅನ್ತರ್ಭಾವ "../SDL_vulkan_internal.h"
#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"


ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *s_defaultPaths[] = {
#ಆದರೆ defined(SDL_PLATFORM_WINDOWS)
    "vulkan-1.dll"
#ಅಥವಾಆದರೆ defined(SDL_PLATFORM_APPLE)
    "vulkan.framework/vulkan",
    "libvulkan.1.dylib",
    "libvulkan.dylib",
    "MoltenVK.framework/MoltenVK",
    "libMoltenVK.dylib"
#ಅಥವಾಆದರೆ defined(SDL_PLATFORM_OPENBSD)
    "libvulkan.so"
#ಇಲ್ಲದಿದ್ದರೆ
    "libvulkan.so.1"
#ಆದರೆ_ಅಂತ್ಯ
};

SDL_ELF_NOTE_DLOPEN(
    "offscreen-vulkan",
    "Support for offscreen Vulkan",
    SDL_ELF_NOTE_DLOPEN_ಆದ್ಯತೆ_SUGGESTED,
    "libvulkan.so.1"
)

#ಆದರೆ defined( SDL_PLATFORM_APPLE )
#ಅನ್ತರ್ಭಾವ <dlfcn.h>

// Since libSDL is most likely a .dylib, need RTLD_DEFAULT not RTLD_SELF.
#ವ್ಯಾಖ್ಯಾನಿಸು DEFAULT_HANDLE RTLD_DEFAULT
#ಆದರೆ_ಅಂತ್ಯ

/*Should the whole driver fail if it can't create a surface? Rendering to an offscreen buffer is still possible without a surface.
    At the time of writing. I need the driver to minimally work even if the surface extension isn't present.
    And account for the inability to create a surface on the consumer side.
    So for now I'm targeting my specific use case -Dave Kircher*/
#ವ್ಯಾಖ್ಯಾನಿಸು HEADLESS_SURFACE_EXTENSION_REQUIRED_ಗಮ್ಯ_ತುಂಬು 0


bool OFFSCREEN_Vulkan_ತುಂಬು_Library(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಮಾರ್ಗ)
{
    VkExtensionProperties *extensions = ಖಾಲಿ;
    Uint32 extension_ಎಣಿಕೆ = 0;
    bool hasSurfaceExtension = false;
    bool hasHeadlessSurfaceExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = ಖಾಲಿ;
    Uint32 i;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ **paths;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸಿಕ್ಕಿತು_ಮಾರ್ಗ = ಖಾಲಿ;
    Uint32 ಅಂಕೆ_Paths;

    ಆದರೆ (_this->vulkan_config.loader_handle) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    ಆದರೆ (!ಮಾರ್ಗ) {
        ಮಾರ್ಗ = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }

#ಆದರೆ defined(SDL_PLATFORM_APPLE)
    ಆದರೆ (!ಮಾರ್ಗ) {
        // Handle the case where Vulkan Portability is linked statically.
        vkGetInstanceProcAddr =
            (PFN_vkGetInstanceProcAddr)dlsym(DEFAULT_HANDLE,
                                             "vkGetInstanceProcAddr");
    }

    ಆದರೆ (vkGetInstanceProcAddr) {
        _this->vulkan_config.loader_handle = DEFAULT_HANDLE;
    } ಇಲ್ಲದಿದ್ದರೆ
#ಆದರೆ_ಅಂತ್ಯ
    {
        ಆದರೆ (ಮಾರ್ಗ) {
            paths = &ಮಾರ್ಗ;
            ಅಂಕೆ_Paths = 1;
        } ಇಲ್ಲದಿದ್ದರೆ {
            paths = s_defaultPaths;
            ಅಂಕೆ_Paths = SDL_arraysize(s_defaultPaths);
        }

        ಗಾಗಿ (i = 0; i < ಅಂಕೆ_Paths && _this->vulkan_config.loader_handle == ಖಾಲಿ; i++) {
            ಸಿಕ್ಕಿತು_ಮಾರ್ಗ = paths[i];
            _this->vulkan_config.loader_handle = SDL_ತುಂಬು_Object(ಸಿಕ್ಕಿತು_ಮಾರ್ಗ);
        }

        ಆದರೆ (_this->vulkan_config.loader_handle == ಖಾಲಿ) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Failed to load Vulkan Portability library");
        }

        SDL_strlcpy(_this->vulkan_config.loader_ಮಾರ್ಗ, ಸಿಕ್ಕಿತು_ಮಾರ್ಗ,
                    SDL_arraysize(_this->vulkan_config.loader_ಮಾರ್ಗ));
        vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)SDL_ತುಂಬು_Function(
            _this->vulkan_config.loader_handle, "vkGetInstanceProcAddr");

        ಆದರೆ (!vkGetInstanceProcAddr) {
            SDL_ಗಣ_Error("Failed to load vkGetInstanceProcAddr from Vulkan Portability library");
            ಹೋಗು fail;
        }
    }

    _this->vulkan_config.vkGetInstanceProcAddr = (SDL_Function_ಸೂಚಕ)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties =
        (SDL_Function_ಸೂಚಕ)((PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr)(
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
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasHeadlessSurfaceExtension = true;
        }
    }
    SDL_free(extensions);
    ಆದರೆ (!hasSurfaceExtension) {
        SDL_ಗಣ_Error("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        ಹೋಗು fail;
    }
    ಆದರೆ (!hasHeadlessSurfaceExtension) {
#ಆದರೆ (HEADLESS_SURFACE_EXTENSION_REQUIRED_ಗಮ್ಯ_ತುಂಬು != 0)
        SDL_ಗಣ_Error("Installed Vulkan doesn't implement the " VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME " extension");
        ಹೋಗು fail;
#ಇಲ್ಲದಿದ್ದರೆ
        // Let's at least leave a breadcrumb for people to find if they have issues
        SDL_Log("Installed Vulkan doesn't implement the " VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME " extension");
#ಆದರೆ_ಅಂತ್ಯ
    }
    ಹಿಂತಿರುಗಿ true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = ಖಾಲಿ;
    ಹಿಂತಿರುಗಿ false;
}

ಶೂನ್ಯ OFFSCREEN_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    ಆದರೆ (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = ಖಾಲಿ;
    }
}

ಅಕ್ಷರ ಸ್ಥಿರಾಂಕ *ಸ್ಥಿರಾಂಕ *OFFSCREEN_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this,
                                                          Uint32 *ಎಣಿಕೆ_2)
{
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸ್ಥಿರಾಂಕ returnExtensions[] = { VK_KHR_SURFACE_EXTENSION_NAME, VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME };

    *ಎಣಿಕೆ_2 = SDL_arraysize(returnExtensions);

#ಆದರೆ (HEADLESS_SURFACE_EXTENSION_REQUIRED_ಗಮ್ಯ_ತುಂಬು == 0)
    VkExtensionProperties *enumerateExtensions = ಖಾಲಿ;
    Uint32 enumerate_Extension_ಎಣಿಕೆ = 0;
    bool hasHeadlessSurfaceExtension = false;
    Uint32 i;

    /* In optional mode, only return VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME if it's already supported by the instance
       There's probably a better way to cache the presence of the extension during OFFSCREEN_Vulkan_LoadLibrary().
       But both SDL_VideoData and SDL_VideoDevice::vulkan_config seem like I'd need to touch a bunch of code to do properly.
       And I want a smaller footprint for the first pass*/
    ಆದರೆ ( _this->vulkan_config.vkEnumerateInstanceExtensionProperties ) {
        enumerateExtensions = SDL_Vulkan_CreateInstanceExtensionsList((PFN_vkEnumerateInstanceExtensionProperties) _this->vulkan_config.vkEnumerateInstanceExtensionProperties, &enumerate_Extension_ಎಣಿಕೆ);
        ಗಾಗಿ (i = 0; i < enumerate_Extension_ಎಣಿಕೆ; i++) {
            ಆದರೆ (SDL_strcmp(VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME, enumerateExtensions[i].extensionName) == 0) {
                hasHeadlessSurfaceExtension = true;
            }
        }
        SDL_free(enumerateExtensions);
    }

    ಆದರೆ (!hasHeadlessSurfaceExtension) {
        (*ಎಣಿಕೆ_2)--;  // assumes VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME is last
    }
#ಆದರೆ_ಅಂತ್ಯ

    ಹಿಂತಿರುಗಿ returnExtensions;
}

bool OFFSCREEN_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                                   SDL_ಕಿಟಕಿ *ಕಿಟಕಿ,
                                   VkInstance instance,
                                   ಸ್ಥಿರಾಂಕ ರಚನೆ Vk_ಹಂಚಿಕೆ_Callbacks *allocator,
                                   VkSurfaceKHR *surface)
{
    *surface = VK_NULL_HANDLE;

    ಆದರೆ (!_this->vulkan_config.loader_handle) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Vulkan is not loaded");
    }

    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    PFN_vkCreateHeadlessSurfaceEXT vkCreateHeadlessSurfaceEXT =
        (PFN_vkCreateHeadlessSurfaceEXT)vkGetInstanceProcAddr(instance, "vkCreateHeadlessSurfaceEXT");
    VkHeadlessSurfaceCreateInfoEXT createInfo;
    Vk_ಫಲಿತಾಂಶ ಫಲಿತಾಂಶ;
    ಆದರೆ (!vkCreateHeadlessSurfaceEXT) {
        /* This may be surprising to the consumer when HEADLESS_SURFACE_EXTENSION_REQUIRED_TO_LOAD == 0
           But this is the tradeoff for allowing offscreen rendering to a buffer to continue working without requiring the extension during driver load */
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error(VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME
                            " extension is not enabled in the Vulkan instance.");
    }
    SDL_zero(createInfo);
    createInfo.sType = VK_STRUCTURE_TYPE_HEADLESS_SURFACE_CREATE_INFO_EXT;
    createInfo.p_ಮುಂದಿನ = ಖಾಲಿ;
    createInfo.flags = 0;
    ಫಲಿತಾಂಶ = vkCreateHeadlessSurfaceEXT(instance, &createInfo, allocator, surface);
    ಆದರೆ (ಫಲಿತಾಂಶ != VK_SUCCESS) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("vkCreateHeadlessSurfaceEXT failed: %s", SDL_Vulkan_Get_ಫಲಿತಾಂಶ_String(ಫಲಿತಾಂಶ));
    }
    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ OFFSCREEN_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                     VkInstance instance,
                                     VkSurfaceKHR surface,
                                     ಸ್ಥಿರಾಂಕ ರಚನೆ Vk_ಹಂಚಿಕೆ_Callbacks *allocator)
{
    ಆದರೆ (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_Destroy_Surface_ಆಂತರಿಕ(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

#ಆದರೆ_ಅಂತ್ಯ
