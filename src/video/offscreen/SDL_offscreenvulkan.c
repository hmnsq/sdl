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
#شامل "SDL_internal.h"

#اگر defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_OFFSCREEN)

#شامل "../SDL_vulkan_internal.h"
#شامل "../SDL_sysvideo.h"


ساکن ثابت حرف *s_defaultPaths[] = {
#اگر defined(SDL_PLATFORM_WINDOWS)
    "vulkan-1.dll"
#وگرنہ_اگر defined(SDL_PLATFORM_APPLE)
    "vulkan.framework/vulkan",
    "libvulkan.1.dylib",
    "libvulkan.dylib",
    "MoltenVK.framework/MoltenVK",
    "libMoltenVK.dylib"
#وگرنہ_اگر defined(SDL_PLATFORM_OPENBSD)
    "libvulkan.so"
#ورنہ
    "libvulkan.so.1"
#اگر_ختم
};

SDL_ELF_NOTE_DLOPEN(
    "offscreen-vulkan",
    "Support for offscreen Vulkan",
    SDL_ELF_NOTE_DLOPEN_ترجیح_SUGGESTED,
    "libvulkan.so.1"
)

#اگر defined( SDL_PLATFORM_APPLE )
#شامل <dlfcn.h>

// Since libSDL is most likely a .dylib, need RTLD_DEFAULT not RTLD_SELF.
#تعریف_کرو DEFAULT_HANDLE RTLD_DEFAULT
#اگر_ختم

/*Should the whole driver fail if it can't create a surface? Rendering to an offscreen buffer is still possible without a surface.
    At the time of writing. I need the driver to minimally work even if the surface extension isn't present.
    And account for the inability to create a surface on the consumer side.
    So for now I'm targeting my specific use case -Dave Kircher*/
#تعریف_کرو HEADLESS_SURFACE_EXTENSION_REQUIRED_مقصد_بھرو 0


bool OFFSCREEN_Vulkan_بھرو_Library(SDL_VideoDevice *_this, ثابت حرف *راستہ)
{
    VkExtensionProperties *extensions = تہی;
    Uint32 extension_گنتی = 0;
    bool hasSurfaceExtension = false;
    bool hasHeadlessSurfaceExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = تہی;
    Uint32 i;
    ثابت حرف **paths;
    ثابت حرف *ملا_راستہ = تہی;
    Uint32 عدد_Paths;

    اگر (_this->vulkan_config.loader_handle) {
        واپس SDL_سیٹ_Error("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    اگر (!راستہ) {
        راستہ = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }

#اگر defined(SDL_PLATFORM_APPLE)
    اگر (!راستہ) {
        // Handle the case where Vulkan Portability is linked statically.
        vkGetInstanceProcAddr =
            (PFN_vkGetInstanceProcAddr)dlsym(DEFAULT_HANDLE,
                                             "vkGetInstanceProcAddr");
    }

    اگر (vkGetInstanceProcAddr) {
        _this->vulkan_config.loader_handle = DEFAULT_HANDLE;
    } ورنہ
#اگر_ختم
    {
        اگر (راستہ) {
            paths = &راستہ;
            عدد_Paths = 1;
        } ورنہ {
            paths = s_defaultPaths;
            عدد_Paths = SDL_arraysize(s_defaultPaths);
        }

        برائے (i = 0; i < عدد_Paths && _this->vulkan_config.loader_handle == تہی; i++) {
            ملا_راستہ = paths[i];
            _this->vulkan_config.loader_handle = SDL_بھرو_Object(ملا_راستہ);
        }

        اگر (_this->vulkan_config.loader_handle == تہی) {
            واپس SDL_سیٹ_Error("Failed to load Vulkan Portability library");
        }

        SDL_strlcpy(_this->vulkan_config.loader_راستہ, ملا_راستہ,
                    SDL_arraysize(_this->vulkan_config.loader_راستہ));
        vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)SDL_بھرو_Function(
            _this->vulkan_config.loader_handle, "vkGetInstanceProcAddr");

        اگر (!vkGetInstanceProcAddr) {
            SDL_سیٹ_Error("Failed to load vkGetInstanceProcAddr from Vulkan Portability library");
            جاؤ fail;
        }
    }

    _this->vulkan_config.vkGetInstanceProcAddr = (SDL_Function_اشارہ_گر)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties =
        (SDL_Function_اشارہ_گر)((PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr)(
            VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties");
    اگر (!_this->vulkan_config.vkEnumerateInstanceExtensionProperties) {
        جاؤ fail;
    }
    extensions = SDL_Vulkan_CreateInstanceExtensionsList(
        (PFN_vkEnumerateInstanceExtensionProperties)
            _this->vulkan_config.vkEnumerateInstanceExtensionProperties,
        &extension_گنتی);
    اگر (!extensions) {
        جاؤ fail;
    }
    برائے (i = 0; i < extension_گنتی; i++) {
        اگر (SDL_strcmp(VK_KHR_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasSurfaceExtension = true;
        } ورنہ اگر (SDL_strcmp(VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasHeadlessSurfaceExtension = true;
        }
    }
    SDL_free(extensions);
    اگر (!hasSurfaceExtension) {
        SDL_سیٹ_Error("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        جاؤ fail;
    }
    اگر (!hasHeadlessSurfaceExtension) {
#اگر (HEADLESS_SURFACE_EXTENSION_REQUIRED_مقصد_بھرو != 0)
        SDL_سیٹ_Error("Installed Vulkan doesn't implement the " VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME " extension");
        جاؤ fail;
#ورنہ
        // Let's at least leave a breadcrumb for people to find if they have issues
        SDL_Log("Installed Vulkan doesn't implement the " VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME " extension");
#اگر_ختم
    }
    واپس true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = تہی;
    واپس false;
}

خالی OFFSCREEN_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    اگر (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = تہی;
    }
}

حرف ثابت *ثابت *OFFSCREEN_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this,
                                                          Uint32 *گنتی)
{
    ساکن ثابت حرف *ثابت returnExtensions[] = { VK_KHR_SURFACE_EXTENSION_NAME, VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME };

    *گنتی = SDL_arraysize(returnExtensions);

#اگر (HEADLESS_SURFACE_EXTENSION_REQUIRED_مقصد_بھرو == 0)
    VkExtensionProperties *enumerateExtensions = تہی;
    Uint32 enumerate_Extension_گنتی = 0;
    bool hasHeadlessSurfaceExtension = false;
    Uint32 i;

    /* In optional mode, only return VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME if it's already supported by the instance
       There's probably a better way to cache the presence of the extension during OFFSCREEN_Vulkan_LoadLibrary().
       But both SDL_VideoData and SDL_VideoDevice::vulkan_config seem like I'd need to touch a bunch of code to do properly.
       And I want a smaller footprint for the first pass*/
    اگر ( _this->vulkan_config.vkEnumerateInstanceExtensionProperties ) {
        enumerateExtensions = SDL_Vulkan_CreateInstanceExtensionsList((PFN_vkEnumerateInstanceExtensionProperties) _this->vulkan_config.vkEnumerateInstanceExtensionProperties, &enumerate_Extension_گنتی);
        برائے (i = 0; i < enumerate_Extension_گنتی; i++) {
            اگر (SDL_strcmp(VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME, enumerateExtensions[i].extensionName) == 0) {
                hasHeadlessSurfaceExtension = true;
            }
        }
        SDL_free(enumerateExtensions);
    }

    اگر (!hasHeadlessSurfaceExtension) {
        (*گنتی)--;  // assumes VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME is last
    }
#اگر_ختم

    واپس returnExtensions;
}

bool OFFSCREEN_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                                   SDL_کھڑکی *کھڑکی,
                                   VkInstance instance,
                                   ثابت ساخت Vk_تخصیص_Callbacks *allocator,
                                   VkSurfaceKHR *surface)
{
    *surface = VK_NULL_HANDLE;

    اگر (!_this->vulkan_config.loader_handle) {
        واپس SDL_سیٹ_Error("Vulkan is not loaded");
    }

    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    PFN_vkCreateHeadlessSurfaceEXT vkCreateHeadlessSurfaceEXT =
        (PFN_vkCreateHeadlessSurfaceEXT)vkGetInstanceProcAddr(instance, "vkCreateHeadlessSurfaceEXT");
    VkHeadlessSurfaceCreateInfoEXT createInfo;
    Vk_نتیجہ نتیجہ;
    اگر (!vkCreateHeadlessSurfaceEXT) {
        /* This may be surprising to the consumer when HEADLESS_SURFACE_EXTENSION_REQUIRED_TO_LOAD == 0
           But this is the tradeoff for allowing offscreen rendering to a buffer to continue working without requiring the extension during driver load */
        واپس SDL_سیٹ_Error(VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME
                            " extension is not enabled in the Vulkan instance.");
    }
    SDL_zero(createInfo);
    createInfo.sType = VK_STRUCTURE_TYPE_HEADLESS_SURFACE_CREATE_INFO_EXT;
    createInfo.p_اگلا = تہی;
    createInfo.flags = 0;
    نتیجہ = vkCreateHeadlessSurfaceEXT(instance, &createInfo, allocator, surface);
    اگر (نتیجہ != VK_SUCCESS) {
        واپس SDL_سیٹ_Error("vkCreateHeadlessSurfaceEXT failed: %s", SDL_Vulkan_Get_نتیجہ_String(نتیجہ));
    }
    واپس true;
}

خالی OFFSCREEN_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                     VkInstance instance,
                                     VkSurfaceKHR surface,
                                     ثابت ساخت Vk_تخصیص_Callbacks *allocator)
{
    اگر (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_Destroy_Surface_اندرونی(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

#اگر_ختم
