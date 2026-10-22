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

#यदि defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_OFFSCREEN)

#अन्तर्भाव "../SDL_vulkan_internal.h"
#अन्तर्भाव "../SDL_sysvideo.h"


स्थिर ध्रुव वर्ण *s_defaultPaths[] = {
#यदि defined(SDL_PLATFORM_WINDOWS)
    "vulkan-1.dll"
#नोचेद्यदि defined(SDL_PLATFORM_APPLE)
    "vulkan.framework/vulkan",
    "libvulkan.1.dylib",
    "libvulkan.dylib",
    "MoltenVK.framework/MoltenVK",
    "libMoltenVK.dylib"
#नोचेद्यदि defined(SDL_PLATFORM_OPENBSD)
    "libvulkan.so"
#अन्यथा
    "libvulkan.so.1"
#यदि_अन्तः
};

SDL_ELF_NOTE_DLOPEN(
    "offscreen-vulkan",
    "Support for offscreen Vulkan",
    SDL_ELF_NOTE_DLOPEN_प्राथमिकता_SUGGESTED,
    "libvulkan.so.1"
)

#यदि defined( SDL_PLATFORM_APPLE )
#अन्तर्भाव <dlfcn.h>

// Since libSDL is most likely a .dylib, need RTLD_DEFAULT not RTLD_SELF.
#परिभाषय DEFAULT_HANDLE RTLD_DEFAULT
#यदि_अन्तः

/*Should the whole driver fail if it can't create a surface? Rendering to an offscreen buffer is still possible without a surface.
    At the time of writing. I need the driver to minimally work even if the surface extension isn't present.
    And account for the inability to create a surface on the consumer side.
    So for now I'm targeting my specific use case -Dave Kircher*/
#परिभाषय HEADLESS_SURFACE_EXTENSION_REQUIRED_गन्तव्यम्_आरोपय 0


bool OFFSCREEN_Vulkan_आरोपय_Library(SDL_VideoDevice *_this, ध्रुव वर्ण *मार्गः)
{
    VkExtensionProperties *extensions = रिक्त;
    Uint32 extension_गणनम् = 0;
    bool hasSurfaceExtension = false;
    bool hasHeadlessSurfaceExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = रिक्त;
    Uint32 i;
    ध्रुव वर्ण **paths;
    ध्रुव वर्ण *प्राप्तम्_मार्गः = रिक्त;
    Uint32 अङ्कः_Paths;

    यदि (_this->vulkan_config.loader_handle) {
        प्रत्यागम SDL_समुच्चयः_Error("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    यदि (!मार्गः) {
        मार्गः = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }

#यदि defined(SDL_PLATFORM_APPLE)
    यदि (!मार्गः) {
        // Handle the case where Vulkan Portability is linked statically.
        vkGetInstanceProcAddr =
            (PFN_vkGetInstanceProcAddr)dlsym(DEFAULT_HANDLE,
                                             "vkGetInstanceProcAddr");
    }

    यदि (vkGetInstanceProcAddr) {
        _this->vulkan_config.loader_handle = DEFAULT_HANDLE;
    } अन्यथा
#यदि_अन्तः
    {
        यदि (मार्गः) {
            paths = &मार्गः;
            अङ्कः_Paths = 1;
        } अन्यथा {
            paths = s_defaultPaths;
            अङ्कः_Paths = SDL_arraysize(s_defaultPaths);
        }

        प्रति (i = 0; i < अङ्कः_Paths && _this->vulkan_config.loader_handle == रिक्त; i++) {
            प्राप्तम्_मार्गः = paths[i];
            _this->vulkan_config.loader_handle = SDL_आरोपय_Object(प्राप्तम्_मार्गः);
        }

        यदि (_this->vulkan_config.loader_handle == रिक्त) {
            प्रत्यागम SDL_समुच्चयः_Error("Failed to load Vulkan Portability library");
        }

        SDL_strlcpy(_this->vulkan_config.loader_मार्गः, प्राप्तम्_मार्गः,
                    SDL_arraysize(_this->vulkan_config.loader_मार्गः));
        vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)SDL_आरोपय_Function(
            _this->vulkan_config.loader_handle, "vkGetInstanceProcAddr");

        यदि (!vkGetInstanceProcAddr) {
            SDL_समुच्चयः_Error("Failed to load vkGetInstanceProcAddr from Vulkan Portability library");
            गच्छ fail;
        }
    }

    _this->vulkan_config.vkGetInstanceProcAddr = (SDL_FunctionPointer)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties =
        (SDL_FunctionPointer)((PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr)(
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
        } अन्यथा यदि (SDL_strcmp(VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasHeadlessSurfaceExtension = true;
        }
    }
    SDL_free(extensions);
    यदि (!hasSurfaceExtension) {
        SDL_समुच्चयः_Error("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        गच्छ fail;
    }
    यदि (!hasHeadlessSurfaceExtension) {
#यदि (HEADLESS_SURFACE_EXTENSION_REQUIRED_गन्तव्यम्_आरोपय != 0)
        SDL_समुच्चयः_Error("Installed Vulkan doesn't implement the " VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME " extension");
        गच्छ fail;
#अन्यथा
        // Let's at least leave a breadcrumb for people to find if they have issues
        SDL_Log("Installed Vulkan doesn't implement the " VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME " extension");
#यदि_अन्तः
    }
    प्रत्यागम true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = रिक्त;
    प्रत्यागम false;
}

शून्य OFFSCREEN_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    यदि (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = रिक्त;
    }
}

वर्ण ध्रुव *ध्रुव *OFFSCREEN_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this,
                                                          Uint32 *गणनम्)
{
    स्थिर ध्रुव वर्ण *ध्रुव returnExtensions[] = { VK_KHR_SURFACE_EXTENSION_NAME, VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME };

    *गणनम् = SDL_arraysize(returnExtensions);

#यदि (HEADLESS_SURFACE_EXTENSION_REQUIRED_गन्तव्यम्_आरोपय == 0)
    VkExtensionProperties *enumerateExtensions = रिक्त;
    Uint32 enumerate_Extension_गणनम् = 0;
    bool hasHeadlessSurfaceExtension = false;
    Uint32 i;

    /* In optional mode, only return VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME if it's already supported by the instance
       There's probably a better way to cache the presence of the extension during OFFSCREEN_Vulkan_LoadLibrary().
       But both SDL_VideoData and SDL_VideoDevice::vulkan_config seem like I'd need to touch a bunch of code to do properly.
       And I want a smaller footprint for the first pass*/
    यदि ( _this->vulkan_config.vkEnumerateInstanceExtensionProperties ) {
        enumerateExtensions = SDL_Vulkan_CreateInstanceExtensionsList((PFN_vkEnumerateInstanceExtensionProperties) _this->vulkan_config.vkEnumerateInstanceExtensionProperties, &enumerate_Extension_गणनम्);
        प्रति (i = 0; i < enumerate_Extension_गणनम्; i++) {
            यदि (SDL_strcmp(VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME, enumerateExtensions[i].extensionName) == 0) {
                hasHeadlessSurfaceExtension = true;
            }
        }
        SDL_free(enumerateExtensions);
    }

    यदि (!hasHeadlessSurfaceExtension) {
        (*गणनम्)--;  // assumes VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME is last
    }
#यदि_अन्तः

    प्रत्यागम returnExtensions;
}

bool OFFSCREEN_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                                   SDL_गवाक्षः *गवाक्षः,
                                   VkInstance instance,
                                   ध्रुव संरचना Vk_आवण्टनम्_Callbacks *allocator,
                                   VkSurfaceKHR *surface)
{
    *surface = VK_NULL_HANDLE;

    यदि (!_this->vulkan_config.loader_handle) {
        प्रत्यागम SDL_समुच्चयः_Error("Vulkan is not loaded");
    }

    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    PFN_vkCreateHeadlessSurfaceEXT vkCreateHeadlessSurfaceEXT =
        (PFN_vkCreateHeadlessSurfaceEXT)vkGetInstanceProcAddr(instance, "vkCreateHeadlessSurfaceEXT");
    VkHeadlessSurfaceCreateInfoEXT createInfo;
    Vk_परिणाम परिणाम;
    यदि (!vkCreateHeadlessSurfaceEXT) {
        /* This may be surprising to the consumer when HEADLESS_SURFACE_EXTENSION_REQUIRED_TO_LOAD == 0
           But this is the tradeoff for allowing offscreen rendering to a buffer to continue working without requiring the extension during driver load */
        प्रत्यागम SDL_समुच्चयः_Error(VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME
                            " extension is not enabled in the Vulkan instance.");
    }
    SDL_zero(createInfo);
    createInfo.sType = VK_STRUCTURE_TYPE_HEADLESS_SURFACE_CREATE_INFO_EXT;
    createInfo.p_अग्र = रिक्त;
    createInfo.flags = 0;
    परिणाम = vkCreateHeadlessSurfaceEXT(instance, &createInfo, allocator, surface);
    यदि (परिणाम != VK_SUCCESS) {
        प्रत्यागम SDL_समुच्चयः_Error("vkCreateHeadlessSurfaceEXT failed: %s", SDL_Vulkan_Get_परिणाम_String(परिणाम));
    }
    प्रत्यागम true;
}

शून्य OFFSCREEN_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                     VkInstance instance,
                                     VkSurfaceKHR surface,
                                     ध्रुव संरचना Vk_आवण्टनम्_Callbacks *allocator)
{
    यदि (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_Destroy_Surface_आन्तरिकम्(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

#यदि_अन्तः
