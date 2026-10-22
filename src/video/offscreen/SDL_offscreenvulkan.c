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
#అన్తర్భావ "SDL_internal.h"

#ఒకవేళ defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_OFFSCREEN)

#అన్తర్భావ "../SDL_vulkan_internal.h"
#అన్తర్భావ "../SDL_sysvideo.h"


స్థిర స్థిరరాశి అక్షరం *s_defaultPaths[] = {
#ఒకవేళ defined(SDL_PLATFORM_WINDOWS)
    "vulkan-1.dll"
#లేదావేళ defined(SDL_PLATFORM_APPLE)
    "vulkan.framework/vulkan",
    "libvulkan.1.dylib",
    "libvulkan.dylib",
    "MoltenVK.framework/MoltenVK",
    "libMoltenVK.dylib"
#లేదావేళ defined(SDL_PLATFORM_OPENBSD)
    "libvulkan.so"
#లేకపోతే
    "libvulkan.so.1"
#అయితే_ముగింపు
};

SDL_ELF_NOTE_DLOPEN(
    "offscreen-vulkan",
    "Support for offscreen Vulkan",
    SDL_ELF_NOTE_DLOPEN_ప్రాధాన్యత_SUGGESTED,
    "libvulkan.so.1"
)

#ఒకవేళ defined( SDL_PLATFORM_APPLE )
#అన్తర్భావ <dlfcn.h>

// Since libSDL is most likely a .dylib, need RTLD_DEFAULT not RTLD_SELF.
#నిర్వచించు DEFAULT_HANDLE RTLD_DEFAULT
#అయితే_ముగింపు

/*Should the whole driver fail if it can't create a surface? Rendering to an offscreen buffer is still possible without a surface.
    At the time of writing. I need the driver to minimally work even if the surface extension isn't present.
    And account for the inability to create a surface on the consumer side.
    So for now I'm targeting my specific use case -Dave Kircher*/
#నిర్వచించు HEADLESS_SURFACE_EXTENSION_REQUIRED_గమ్యం_ఎక్కించు 0


bool OFFSCREEN_Vulkan_ఎక్కించు_Library(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *మార్గం)
{
    VkExtensionProperties *extensions = ఖాళీ;
    Uint32 extension_లెక్క = 0;
    bool hasSurfaceExtension = false;
    bool hasHeadlessSurfaceExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = ఖాళీ;
    Uint32 i;
    స్థిరరాశి అక్షరం **paths;
    స్థిరరాశి అక్షరం *దొరికింది_మార్గం = ఖాళీ;
    Uint32 అంకె_Paths;

    ఒకవేళ (_this->vulkan_config.loader_handle) {
        తిరిగి SDL_సమితి_Error("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    ఒకవేళ (!మార్గం) {
        మార్గం = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }

#ఒకవేళ defined(SDL_PLATFORM_APPLE)
    ఒకవేళ (!మార్గం) {
        // Handle the case where Vulkan Portability is linked statically.
        vkGetInstanceProcAddr =
            (PFN_vkGetInstanceProcAddr)dlsym(DEFAULT_HANDLE,
                                             "vkGetInstanceProcAddr");
    }

    ఒకవేళ (vkGetInstanceProcAddr) {
        _this->vulkan_config.loader_handle = DEFAULT_HANDLE;
    } లేకపోతే
#అయితే_ముగింపు
    {
        ఒకవేళ (మార్గం) {
            paths = &మార్గం;
            అంకె_Paths = 1;
        } లేకపోతే {
            paths = s_defaultPaths;
            అంకె_Paths = SDL_arraysize(s_defaultPaths);
        }

        కొరకు (i = 0; i < అంకె_Paths && _this->vulkan_config.loader_handle == ఖాళీ; i++) {
            దొరికింది_మార్గం = paths[i];
            _this->vulkan_config.loader_handle = SDL_ఎక్కించు_Object(దొరికింది_మార్గం);
        }

        ఒకవేళ (_this->vulkan_config.loader_handle == ఖాళీ) {
            తిరిగి SDL_సమితి_Error("Failed to load Vulkan Portability library");
        }

        SDL_strlcpy(_this->vulkan_config.loader_మార్గం, దొరికింది_మార్గం,
                    SDL_arraysize(_this->vulkan_config.loader_మార్గం));
        vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)SDL_ఎక్కించు_Function(
            _this->vulkan_config.loader_handle, "vkGetInstanceProcAddr");

        ఒకవేళ (!vkGetInstanceProcAddr) {
            SDL_సమితి_Error("Failed to load vkGetInstanceProcAddr from Vulkan Portability library");
            వెళ్ళు fail;
        }
    }

    _this->vulkan_config.vkGetInstanceProcAddr = (SDL_Function_సూచిక)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties =
        (SDL_Function_సూచిక)((PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr)(
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
        } లేకపోతే ఒకవేళ (SDL_strcmp(VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasHeadlessSurfaceExtension = true;
        }
    }
    SDL_free(extensions);
    ఒకవేళ (!hasSurfaceExtension) {
        SDL_సమితి_Error("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        వెళ్ళు fail;
    }
    ఒకవేళ (!hasHeadlessSurfaceExtension) {
#ఒకవేళ (HEADLESS_SURFACE_EXTENSION_REQUIRED_గమ్యం_ఎక్కించు != 0)
        SDL_సమితి_Error("Installed Vulkan doesn't implement the " VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME " extension");
        వెళ్ళు fail;
#లేకపోతే
        // Let's at least leave a breadcrumb for people to find if they have issues
        SDL_Log("Installed Vulkan doesn't implement the " VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME " extension");
#అయితే_ముగింపు
    }
    తిరిగి true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = ఖాళీ;
    తిరిగి false;
}

శూన్య OFFSCREEN_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    ఒకవేళ (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = ఖాళీ;
    }
}

అక్షరం స్థిరరాశి *స్థిరరాశి *OFFSCREEN_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this,
                                                          Uint32 *లెక్క)
{
    స్థిర స్థిరరాశి అక్షరం *స్థిరరాశి returnExtensions[] = { VK_KHR_SURFACE_EXTENSION_NAME, VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME };

    *లెక్క = SDL_arraysize(returnExtensions);

#ఒకవేళ (HEADLESS_SURFACE_EXTENSION_REQUIRED_గమ్యం_ఎక్కించు == 0)
    VkExtensionProperties *enumerateExtensions = ఖాళీ;
    Uint32 enumerate_Extension_లెక్క = 0;
    bool hasHeadlessSurfaceExtension = false;
    Uint32 i;

    /* In optional mode, only return VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME if it's already supported by the instance
       There's probably a better way to cache the presence of the extension during OFFSCREEN_Vulkan_LoadLibrary().
       But both SDL_VideoData and SDL_VideoDevice::vulkan_config seem like I'd need to touch a bunch of code to do properly.
       And I want a smaller footprint for the first pass*/
    ఒకవేళ ( _this->vulkan_config.vkEnumerateInstanceExtensionProperties ) {
        enumerateExtensions = SDL_Vulkan_CreateInstanceExtensionsList((PFN_vkEnumerateInstanceExtensionProperties) _this->vulkan_config.vkEnumerateInstanceExtensionProperties, &enumerate_Extension_లెక్క);
        కొరకు (i = 0; i < enumerate_Extension_లెక్క; i++) {
            ఒకవేళ (SDL_strcmp(VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME, enumerateExtensions[i].extensionName) == 0) {
                hasHeadlessSurfaceExtension = true;
            }
        }
        SDL_free(enumerateExtensions);
    }

    ఒకవేళ (!hasHeadlessSurfaceExtension) {
        (*లెక్క)--;  // assumes VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME is last
    }
#అయితే_ముగింపు

    తిరిగి returnExtensions;
}

bool OFFSCREEN_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                                   SDL_కిటికీ *కిటికీ,
                                   VkInstance instance,
                                   స్థిరరాశి నిర్మాణం Vk_కేటాయింపు_Callbacks *allocator,
                                   VkSurfaceKHR *surface)
{
    *surface = VK_NULL_HANDLE;

    ఒకవేళ (!_this->vulkan_config.loader_handle) {
        తిరిగి SDL_సమితి_Error("Vulkan is not loaded");
    }

    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    PFN_vkCreateHeadlessSurfaceEXT vkCreateHeadlessSurfaceEXT =
        (PFN_vkCreateHeadlessSurfaceEXT)vkGetInstanceProcAddr(instance, "vkCreateHeadlessSurfaceEXT");
    VkHeadlessSurfaceCreateInfoEXT createInfo;
    Vk_ఫలితం ఫలితం;
    ఒకవేళ (!vkCreateHeadlessSurfaceEXT) {
        /* This may be surprising to the consumer when HEADLESS_SURFACE_EXTENSION_REQUIRED_TO_LOAD == 0
           But this is the tradeoff for allowing offscreen rendering to a buffer to continue working without requiring the extension during driver load */
        తిరిగి SDL_సమితి_Error(VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME
                            " extension is not enabled in the Vulkan instance.");
    }
    SDL_zero(createInfo);
    createInfo.sType = VK_STRUCTURE_TYPE_HEADLESS_SURFACE_CREATE_INFO_EXT;
    createInfo.p_తదుపరి = ఖాళీ;
    createInfo.flags = 0;
    ఫలితం = vkCreateHeadlessSurfaceEXT(instance, &createInfo, allocator, surface);
    ఒకవేళ (ఫలితం != VK_SUCCESS) {
        తిరిగి SDL_సమితి_Error("vkCreateHeadlessSurfaceEXT failed: %s", SDL_Vulkan_Get_ఫలితం_String(ఫలితం));
    }
    తిరిగి true;
}

శూన్య OFFSCREEN_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                     VkInstance instance,
                                     VkSurfaceKHR surface,
                                     స్థిరరాశి నిర్మాణం Vk_కేటాయింపు_Callbacks *allocator)
{
    ఒకవేళ (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_Destroy_Surface_అంతర్గత(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

#అయితే_ముగింపు
