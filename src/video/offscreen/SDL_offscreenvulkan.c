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
#समावेश "SDL_internal.h"

#अगर defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_OFFSCREEN)

#समावेश "../SDL_vulkan_internal.h"
#समावेश "../SDL_sysvideo.h"


अटल स्थिर अक्षर *s_defaultPaths[] = {
#अगर defined(SDL_PLATFORM_WINDOWS)
    "vulkan-1.dll"
#या_अगर defined(SDL_PLATFORM_APPLE)
    "vulkan.framework/vulkan",
    "libvulkan.1.dylib",
    "libvulkan.dylib",
    "MoltenVK.framework/MoltenVK",
    "libMoltenVK.dylib"
#या_अगर defined(SDL_PLATFORM_OPENBSD)
    "libvulkan.so"
#अन्यथा
    "libvulkan.so.1"
#पूर्ण_अगर
};

SDL_ELF_NOTE_DLOPEN(
    "offscreen-vulkan",
    "Support for offscreen Vulkan",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_SUGGESTED,
    "libvulkan.so.1"
)

#अगर defined( SDL_PLATFORM_APPLE )
#समावेश <dlfcn.h>

// Since libSDL is most likely a .dylib, need RTLD_DEFAULT not RTLD_SELF.
#घोषणा DEFAULT_HANDLE RTLD_DEFAULT
#पूर्ण_अगर

/*Should the whole driver fail if it can't create a surface? Rendering to an offscreen buffer is still possible without a surface.
    At the time of writing. I need the driver to minimally work even if the surface extension isn't present.
    And account for the inability to create a surface on the consumer side.
    So for now I'm targeting my specific use case -Dave Kircher*/
#घोषणा HEADLESS_SURFACE_EXTENSION_REQUIRED_TO_LOAD 0


bool OFFSCREEN_Vulkan_LoadLibrary(SDL_VideoDevice *_this, स्थिर अक्षर *path)
{
    VkExtensionProperties *extensions = शून्य;
    Uint32 extension_गिनती = 0;
    bool hasSurfaceExtension = false;
    bool hasHeadlessSurfaceExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = शून्य;
    Uint32 i;
    स्थिर अक्षर **paths;
    स्थिर अक्षर *foundPath = शून्य;
    Uint32 अंक_Paths;

    अगर (_this->vulkan_config.loader_handle) {
        वापस SDL_SetError("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    अगर (!path) {
        path = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }

#अगर defined(SDL_PLATFORM_APPLE)
    अगर (!path) {
        // Handle the case where Vulkan Portability is linked statically.
        vkGetInstanceProcAddr =
            (PFN_vkGetInstanceProcAddr)dlsym(DEFAULT_HANDLE,
                                             "vkGetInstanceProcAddr");
    }

    अगर (vkGetInstanceProcAddr) {
        _this->vulkan_config.loader_handle = DEFAULT_HANDLE;
    } अन्यथा
#पूर्ण_अगर
    {
        अगर (path) {
            paths = &path;
            अंक_Paths = 1;
        } अन्यथा {
            paths = s_defaultPaths;
            अंक_Paths = SDL_arraysize(s_defaultPaths);
        }

        क्रम (i = 0; i < अंक_Paths && _this->vulkan_config.loader_handle == शून्य; i++) {
            foundPath = paths[i];
            _this->vulkan_config.loader_handle = SDL_LoadObject(foundPath);
        }

        अगर (_this->vulkan_config.loader_handle == शून्य) {
            वापस SDL_SetError("Failed to load Vulkan Portability library");
        }

        SDL_strlcpy(_this->vulkan_config.loader_path, foundPath,
                    SDL_arraysize(_this->vulkan_config.loader_path));
        vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)SDL_LoadFunction(
            _this->vulkan_config.loader_handle, "vkGetInstanceProcAddr");

        अगर (!vkGetInstanceProcAddr) {
            SDL_SetError("Failed to load vkGetInstanceProcAddr from Vulkan Portability library");
            जाओ fail;
        }
    }

    _this->vulkan_config.vkGetInstanceProcAddr = (SDL_FunctionPointer)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties =
        (SDL_FunctionPointer)((PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr)(
            VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties");
    अगर (!_this->vulkan_config.vkEnumerateInstanceExtensionProperties) {
        जाओ fail;
    }
    extensions = SDL_Vulkan_CreateInstanceExtensionsList(
        (PFN_vkEnumerateInstanceExtensionProperties)
            _this->vulkan_config.vkEnumerateInstanceExtensionProperties,
        &extension_गिनती);
    अगर (!extensions) {
        जाओ fail;
    }
    क्रम (i = 0; i < extension_गिनती; i++) {
        अगर (SDL_strcmp(VK_KHR_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasSurfaceExtension = true;
        } अन्यथा अगर (SDL_strcmp(VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasHeadlessSurfaceExtension = true;
        }
    }
    SDL_free(extensions);
    अगर (!hasSurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        जाओ fail;
    }
    अगर (!hasHeadlessSurfaceExtension) {
#अगर (HEADLESS_SURFACE_EXTENSION_REQUIRED_TO_LOAD != 0)
        SDL_SetError("Installed Vulkan doesn't implement the " VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME " extension");
        जाओ fail;
#अन्यथा
        // Let's at least leave a breadcrumb for people to find if they have issues
        SDL_Log("Installed Vulkan doesn't implement the " VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME " extension");
#पूर्ण_अगर
    }
    वापस true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = शून्य;
    वापस false;
}

व्योम OFFSCREEN_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    अगर (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = शून्य;
    }
}

अक्षर स्थिर *स्थिर *OFFSCREEN_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this,
                                                          Uint32 *गिनती)
{
    अटल स्थिर अक्षर *स्थिर returnExtensions[] = { VK_KHR_SURFACE_EXTENSION_NAME, VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME };

    *गिनती = SDL_arraysize(returnExtensions);

#अगर (HEADLESS_SURFACE_EXTENSION_REQUIRED_TO_LOAD == 0)
    VkExtensionProperties *enumerateExtensions = शून्य;
    Uint32 enumerate_Extension_गिनती = 0;
    bool hasHeadlessSurfaceExtension = false;
    Uint32 i;

    /* In optional mode, only return VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME if it's already supported by the instance
       There's probably a better way to cache the presence of the extension during OFFSCREEN_Vulkan_LoadLibrary().
       But both SDL_VideoData and SDL_VideoDevice::vulkan_config seem like I'd need to touch a bunch of code to do properly.
       And I want a smaller footprint for the first pass*/
    अगर ( _this->vulkan_config.vkEnumerateInstanceExtensionProperties ) {
        enumerateExtensions = SDL_Vulkan_CreateInstanceExtensionsList((PFN_vkEnumerateInstanceExtensionProperties) _this->vulkan_config.vkEnumerateInstanceExtensionProperties, &enumerate_Extension_गिनती);
        क्रम (i = 0; i < enumerate_Extension_गिनती; i++) {
            अगर (SDL_strcmp(VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME, enumerateExtensions[i].extensionName) == 0) {
                hasHeadlessSurfaceExtension = true;
            }
        }
        SDL_free(enumerateExtensions);
    }

    अगर (!hasHeadlessSurfaceExtension) {
        (*गिनती)--;  // assumes VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME is last
    }
#पूर्ण_अगर

    वापस returnExtensions;
}

bool OFFSCREEN_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                                   SDL_Window *window,
                                   VkInstance instance,
                                   स्थिर काष्ठा VkAllocationCallbacks *allocator,
                                   VkSurfaceKHR *surface)
{
    *surface = VK_NULL_HANDLE;

    अगर (!_this->vulkan_config.loader_handle) {
        वापस SDL_SetError("Vulkan is not loaded");
    }

    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    PFN_vkCreateHeadlessSurfaceEXT vkCreateHeadlessSurfaceEXT =
        (PFN_vkCreateHeadlessSurfaceEXT)vkGetInstanceProcAddr(instance, "vkCreateHeadlessSurfaceEXT");
    VkHeadlessSurfaceCreateInfoEXT createInfo;
    Vk_परिणाम परिणाम;
    अगर (!vkCreateHeadlessSurfaceEXT) {
        /* This may be surprising to the consumer when HEADLESS_SURFACE_EXTENSION_REQUIRED_TO_LOAD == 0
           But this is the tradeoff for allowing offscreen rendering to a buffer to continue working without requiring the extension during driver load */
        वापस SDL_SetError(VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME
                            " extension is not enabled in the Vulkan instance.");
    }
    SDL_zero(createInfo);
    createInfo.sType = VK_STRUCTURE_TYPE_HEADLESS_SURFACE_CREATE_INFO_EXT;
    createInfo.p_अग्र = शून्य;
    createInfo.flags = 0;
    परिणाम = vkCreateHeadlessSurfaceEXT(instance, &createInfo, allocator, surface);
    अगर (परिणाम != VK_SUCCESS) {
        वापस SDL_SetError("vkCreateHeadlessSurfaceEXT failed: %s", SDL_Vulkan_Get_परिणाम_String(परिणाम));
    }
    वापस true;
}

व्योम OFFSCREEN_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                     VkInstance instance,
                                     VkSurfaceKHR surface,
                                     स्थिर काष्ठा VkAllocationCallbacks *allocator)
{
    अगर (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_DestroySurface_Internal(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

#पूर्ण_अगर
