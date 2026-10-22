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
#ضمن "SDL_internal.h"

#إذا defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_OFFSCREEN)

#ضمن "../SDL_vulkan_internal.h"
#ضمن "../SDL_sysvideo.h"


ساكن ثابت حرف *s_defaultPaths[] = {
#إذا defined(SDL_PLATFORM_WINDOWS)
    "vulkan-1.dll"
#وإلاإذا defined(SDL_PLATFORM_APPLE)
    "vulkan.framework/vulkan",
    "libvulkan.1.dylib",
    "libvulkan.dylib",
    "MoltenVK.framework/MoltenVK",
    "libMoltenVK.dylib"
#وإلاإذا defined(SDL_PLATFORM_OPENBSD)
    "libvulkan.so"
#وإلا
    "libvulkan.so.1"
#د_که_پای
};

SDL_ELF_NOTE_DLOPEN(
    "offscreen-vulkan",
    "Support for offscreen Vulkan",
    SDL_ELF_NOTE_DLOPEN_لومړیتوب_SUGGESTED,
    "libvulkan.so.1"
)

#إذا defined( SDL_PLATFORM_APPLE )
#ضمن <dlfcn.h>

// Since libSDL is most likely a .dylib, need RTLD_DEFAULT not RTLD_SELF.
#تعریف_کړه DEFAULT_HANDLE RTLD_DEFAULT
#د_که_پای

/*Should the whole driver fail if it can't create a surface? Rendering to an offscreen buffer is still possible without a surface.
    At the time of writing. I need the driver to minimally work even if the surface extension isn't present.
    And account for the inability to create a surface on the consumer side.
    So for now I'm targeting my specific use case -Dave Kircher*/
#تعریف_کړه HEADLESS_SURFACE_EXTENSION_REQUIRED_منزل_بارول 0


bool OFFSCREEN_Vulkan_بارول_Library(SDL_VideoDevice *_this, ثابت حرف *لار)
{
    VkExtensionProperties *extensions = عدم;
    Uint32 extension_شمېر = 0;
    bool hasSurfaceExtension = false;
    bool hasHeadlessSurfaceExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = عدم;
    Uint32 i;
    ثابت حرف **paths;
    ثابت حرف *وموندل_لار = عدم;
    Uint32 عدد_Paths;

    إذا (_this->vulkan_config.loader_handle) {
        أرجع SDL_سېټ_Error("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    إذا (!لار) {
        لار = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }

#إذا defined(SDL_PLATFORM_APPLE)
    إذا (!لار) {
        // Handle the case where Vulkan Portability is linked statically.
        vkGetInstanceProcAddr =
            (PFN_vkGetInstanceProcAddr)dlsym(DEFAULT_HANDLE,
                                             "vkGetInstanceProcAddr");
    }

    إذا (vkGetInstanceProcAddr) {
        _this->vulkan_config.loader_handle = DEFAULT_HANDLE;
    } وإلا
#د_که_پای
    {
        إذا (لار) {
            paths = &لار;
            عدد_Paths = 1;
        } وإلا {
            paths = s_defaultPaths;
            عدد_Paths = SDL_arraysize(s_defaultPaths);
        }

        لكل (i = 0; i < عدد_Paths && _this->vulkan_config.loader_handle == عدم; i++) {
            وموندل_لار = paths[i];
            _this->vulkan_config.loader_handle = SDL_بارول_Object(وموندل_لار);
        }

        إذا (_this->vulkan_config.loader_handle == عدم) {
            أرجع SDL_سېټ_Error("Failed to load Vulkan Portability library");
        }

        SDL_strlcpy(_this->vulkan_config.loader_لار, وموندل_لار,
                    SDL_arraysize(_this->vulkan_config.loader_لار));
        vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)SDL_بارول_Function(
            _this->vulkan_config.loader_handle, "vkGetInstanceProcAddr");

        إذا (!vkGetInstanceProcAddr) {
            SDL_سېټ_Error("Failed to load vkGetInstanceProcAddr from Vulkan Portability library");
            اذهب fail;
        }
    }

    _this->vulkan_config.vkGetInstanceProcAddr = (SDL_Function_اشاره_ګر)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties =
        (SDL_Function_اشاره_ګر)((PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr)(
            VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties");
    إذا (!_this->vulkan_config.vkEnumerateInstanceExtensionProperties) {
        اذهب fail;
    }
    extensions = SDL_Vulkan_CreateInstanceExtensionsList(
        (PFN_vkEnumerateInstanceExtensionProperties)
            _this->vulkan_config.vkEnumerateInstanceExtensionProperties,
        &extension_شمېر);
    إذا (!extensions) {
        اذهب fail;
    }
    لكل (i = 0; i < extension_شمېر; i++) {
        إذا (SDL_strcmp(VK_KHR_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasSurfaceExtension = true;
        } وإلا إذا (SDL_strcmp(VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasHeadlessSurfaceExtension = true;
        }
    }
    SDL_free(extensions);
    إذا (!hasSurfaceExtension) {
        SDL_سېټ_Error("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        اذهب fail;
    }
    إذا (!hasHeadlessSurfaceExtension) {
#إذا (HEADLESS_SURFACE_EXTENSION_REQUIRED_منزل_بارول != 0)
        SDL_سېټ_Error("Installed Vulkan doesn't implement the " VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME " extension");
        اذهب fail;
#وإلا
        // Let's at least leave a breadcrumb for people to find if they have issues
        SDL_Log("Installed Vulkan doesn't implement the " VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME " extension");
#د_که_پای
    }
    أرجع true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = عدم;
    أرجع false;
}

فراغ OFFSCREEN_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    إذا (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = عدم;
    }
}

حرف ثابت *ثابت *OFFSCREEN_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this,
                                                          Uint32 *شمېر)
{
    ساكن ثابت حرف *ثابت returnExtensions[] = { VK_KHR_SURFACE_EXTENSION_NAME, VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME };

    *شمېر = SDL_arraysize(returnExtensions);

#إذا (HEADLESS_SURFACE_EXTENSION_REQUIRED_منزل_بارول == 0)
    VkExtensionProperties *enumerateExtensions = عدم;
    Uint32 enumerate_Extension_شمېر = 0;
    bool hasHeadlessSurfaceExtension = false;
    Uint32 i;

    /* In optional mode, only return VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME if it's already supported by the instance
       There's probably a better way to cache the presence of the extension during OFFSCREEN_Vulkan_LoadLibrary().
       But both SDL_VideoData and SDL_VideoDevice::vulkan_config seem like I'd need to touch a bunch of code to do properly.
       And I want a smaller footprint for the first pass*/
    إذا ( _this->vulkan_config.vkEnumerateInstanceExtensionProperties ) {
        enumerateExtensions = SDL_Vulkan_CreateInstanceExtensionsList((PFN_vkEnumerateInstanceExtensionProperties) _this->vulkan_config.vkEnumerateInstanceExtensionProperties, &enumerate_Extension_شمېر);
        لكل (i = 0; i < enumerate_Extension_شمېر; i++) {
            إذا (SDL_strcmp(VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME, enumerateExtensions[i].extensionName) == 0) {
                hasHeadlessSurfaceExtension = true;
            }
        }
        SDL_free(enumerateExtensions);
    }

    إذا (!hasHeadlessSurfaceExtension) {
        (*شمېر)--;  // assumes VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME is last
    }
#د_که_پای

    أرجع returnExtensions;
}

bool OFFSCREEN_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                                   SDL_کړکۍ *کړکۍ,
                                   VkInstance instance,
                                   ثابت بنية Vk_ویش_Callbacks *allocator,
                                   VkSurfaceKHR *surface)
{
    *surface = VK_NULL_HANDLE;

    إذا (!_this->vulkan_config.loader_handle) {
        أرجع SDL_سېټ_Error("Vulkan is not loaded");
    }

    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    PFN_vkCreateHeadlessSurfaceEXT vkCreateHeadlessSurfaceEXT =
        (PFN_vkCreateHeadlessSurfaceEXT)vkGetInstanceProcAddr(instance, "vkCreateHeadlessSurfaceEXT");
    VkHeadlessSurfaceCreateInfoEXT createInfo;
    Vk_پایله پایله;
    إذا (!vkCreateHeadlessSurfaceEXT) {
        /* This may be surprising to the consumer when HEADLESS_SURFACE_EXTENSION_REQUIRED_TO_LOAD == 0
           But this is the tradeoff for allowing offscreen rendering to a buffer to continue working without requiring the extension during driver load */
        أرجع SDL_سېټ_Error(VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME
                            " extension is not enabled in the Vulkan instance.");
    }
    SDL_zero(createInfo);
    createInfo.sType = VK_STRUCTURE_TYPE_HEADLESS_SURFACE_CREATE_INFO_EXT;
    createInfo.p_بل = عدم;
    createInfo.flags = 0;
    پایله = vkCreateHeadlessSurfaceEXT(instance, &createInfo, allocator, surface);
    إذا (پایله != VK_SUCCESS) {
        أرجع SDL_سېټ_Error("vkCreateHeadlessSurfaceEXT failed: %s", SDL_Vulkan_Get_پایله_String(پایله));
    }
    أرجع true;
}

فراغ OFFSCREEN_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                     VkInstance instance,
                                     VkSurfaceKHR surface,
                                     ثابت بنية Vk_ویش_Callbacks *allocator)
{
    إذا (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_Destroy_Surface_دننی(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

#د_که_پای
