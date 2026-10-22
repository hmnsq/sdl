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

#ਜੇ defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_X11)

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_vulkan_internal.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11video.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11vulkan.h"

#ਅਨ੍ਤਰ੍ਭਾਵ <X11/Xlib.h>
// #include <xcb/xcb.h>

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_PLATFORM_OPENBSD
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFAULT_VULKAN "libvulkan.so"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFAULT_X11_XCB "libX11-xcb.so"
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFAULT_VULKAN "libvulkan.so.1"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFAULT_X11_XCB "libX11-xcb.so.1"
#ਜੇ_ਅੰਤ

SDL_ELF_NOTE_DLOPEN(
    "x11-vulkan",
    "Support for vulkan on X11",
    SDL_ELF_NOTE_DLOPEN_ਤਰਜੀਹ_SUGGESTED,
    DEFAULT_VULKAN
)

SDL_ELF_NOTE_DLOPEN(
    "x11-vulkan",
    "Support for vulkan on X11",
    SDL_ELF_NOTE_DLOPEN_ਤਰਜੀਹ_SUGGESTED,
    DEFAULT_X11_XCB
)

/*
typedef uint32_t xcb_window_t;
typedef uint32_t xcb_visualid_t;
*/

bool X11_Vulkan_ਲੱਦੋ_Library(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *ਰਸਤਾ)
{
    SDL_Video_ਅੰਕੜੇ *video_ਅੰਕੜੇ_2 = _this->ਅੰਦਰੂਨੀ;
    VkExtensionProperties *extensions = ਨਿਰਾ;
    Uint32 extension_ਗਿਣਤੀ = 0;
    bool hasSurfaceExtension = false;
    bool hasXlibSurfaceExtension = false;
    bool hasXCBSurfaceExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = ਨਿਰਾ;
    Uint32 i;
    ਜੇ (_this->vulkan_config.loader_handle) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    ਜੇ (!ਰਸਤਾ) {
        ਰਸਤਾ = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }
    ਜੇ (!ਰਸਤਾ) {
        ਰਸਤਾ = DEFAULT_VULKAN;
    }
    _this->vulkan_config.loader_handle = SDL_ਲੱਦੋ_Object(ਰਸਤਾ);
    ਜੇ (!_this->vulkan_config.loader_handle) {
        ਵਾਪਸ false;
    }
    SDL_strlcpy(_this->vulkan_config.loader_ਰਸਤਾ, ਰਸਤਾ, SDL_arraysize(_this->vulkan_config.loader_ਰਸਤਾ));
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)SDL_ਲੱਦੋ_Function(
        _this->vulkan_config.loader_handle, "vkGetInstanceProcAddr");
    ਜੇ (!vkGetInstanceProcAddr) {
        ਜਾਓ fail;
    }
    _this->vulkan_config.vkGetInstanceProcAddr = (ਖਾਲੀ *)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties =
        (ਖਾਲੀ *)((PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr)(
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
        } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(VK_KHR_XCB_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasXCBSurfaceExtension = true;
        } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(VK_KHR_XLIB_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasXlibSurfaceExtension = true;
        }
    }
    SDL_free(extensions);
    ਜੇ (!hasSurfaceExtension) {
        SDL_ਸੈੱਟ_Error("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        ਜਾਓ fail;
    }
    ਜੇ (hasXlibSurfaceExtension) {
        video_ਅੰਕੜੇ_2->vulkan_xlib_xcb_library = ਨਿਰਾ;
    } ਨਹੀਂਤਾਂ ਜੇ (!hasXCBSurfaceExtension) {
        SDL_ਸੈੱਟ_Error("Installed Vulkan doesn't implement either the " VK_KHR_XCB_SURFACE_EXTENSION_NAME " extension or the " VK_KHR_XLIB_SURFACE_EXTENSION_NAME " extension");
        ਜਾਓ fail;
    } ਨਹੀਂਤਾਂ {
        ਅਚਲ ਅੱਖਰ *libX11XCBLibraryName = SDL_GetHint(SDL_HINT_X11_XCB_LIBRARY);
        ਜੇ (!libX11XCBLibraryName || !*libX11XCBLibraryName) {
            libX11XCBLibraryName = DEFAULT_X11_XCB;
        }
        video_ਅੰਕੜੇ_2->vulkan_xlib_xcb_library = SDL_ਲੱਦੋ_Object(libX11XCBLibraryName);
        ਜੇ (!video_ਅੰਕੜੇ_2->vulkan_xlib_xcb_library) {
            ਜਾਓ fail;
        }
        video_ਅੰਕੜੇ_2->vulkan_XGetXCBConnection =
            (PFN_XGetXCBConnection)SDL_ਲੱਦੋ_Function(video_ਅੰਕੜੇ_2->vulkan_xlib_xcb_library, "XGetXCBConnection");
        ਜੇ (!video_ਅੰਕੜੇ_2->vulkan_XGetXCBConnection) {
            SDL_UnloadObject(video_ਅੰਕੜੇ_2->vulkan_xlib_xcb_library);
            ਜਾਓ fail;
        }
    }
    ਵਾਪਸ true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = ਨਿਰਾ;
    ਵਾਪਸ false;
}

ਖਾਲੀ X11_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *video_ਅੰਕੜੇ_2 = _this->ਅੰਦਰੂਨੀ;
    ਜੇ (_this->vulkan_config.loader_handle) {
        ਜੇ (video_ਅੰਕੜੇ_2->vulkan_xlib_xcb_library) {
            SDL_UnloadObject(video_ਅੰਕੜੇ_2->vulkan_xlib_xcb_library);
        }
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = ਨਿਰਾ;
    }
}

ਅੱਖਰ ਅਚਲ * ਅਚਲ *X11_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *ਗਿਣਤੀ_2)
{
    SDL_Video_ਅੰਕੜੇ *video_ਅੰਕੜੇ_2 = _this->ਅੰਦਰੂਨੀ;
    ਜੇ (video_ਅੰਕੜੇ_2->vulkan_xlib_xcb_library) {
        ਸਥਿਰ ਅਚਲ ਅੱਖਰ *ਅਚਲ extensionsForXCB[] = {
            VK_KHR_SURFACE_EXTENSION_NAME,
            VK_KHR_XCB_SURFACE_EXTENSION_NAME,
        };
        *ਗਿਣਤੀ_2 = SDL_arraysize(extensionsForXCB);
        ਵਾਪਸ extensionsForXCB;
    } ਨਹੀਂਤਾਂ {
        ਸਥਿਰ ਅਚਲ ਅੱਖਰ *ਅਚਲ extensionsForXlib[] = {
            VK_KHR_SURFACE_EXTENSION_NAME,
            VK_KHR_XLIB_SURFACE_EXTENSION_NAME,
        };
        *ਗਿਣਤੀ_2 = SDL_arraysize(extensionsForXlib);
        ਵਾਪਸ extensionsForXlib;
    }
}

bool X11_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                             SDL_ਖਿੜਕੀ *ਖਿੜਕੀ,
                             VkInstance instance,
                             ਅਚਲ ਬਣਤਰ Vk_ਵੰਡ_Callbacks *allocator,
                             VkSurfaceKHR *surface)
{
    SDL_Video_ਅੰਕੜੇ *video_ਅੰਕੜੇ_2 = _this->ਅੰਦਰੂਨੀ;
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ_ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;
    ਜੇ (!_this->vulkan_config.loader_handle) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Vulkan is not loaded");
    }
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    ਜੇ (video_ਅੰਕੜੇ_2->vulkan_xlib_xcb_library) {
        PFN_vkCreateXcbSurfaceKHR vkCreateXcbSurfaceKHR =
            (PFN_vkCreateXcbSurfaceKHR)vkGetInstanceProcAddr(instance,
                                                             "vkCreateXcbSurfaceKHR");
        VkXcbSurfaceCreateInfoKHR createInfo;
        Vk_ਨਤੀਜਾ ਨਤੀਜਾ;
        ਜੇ (!vkCreateXcbSurfaceKHR) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error(VK_KHR_XCB_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        }
        SDL_zero(createInfo);
        createInfo.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
        createInfo.connection = video_ਅੰਕੜੇ_2->vulkan_XGetXCBConnection(video_ਅੰਕੜੇ_2->display);
        ਜੇ (!createInfo.connection) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("XGetXCBConnection failed");
        }
        createInfo.ਖਿੜਕੀ = (xcb_ਖਿੜਕੀ_t)ਖਿੜਕੀ_ਅੰਕੜੇ->xwindow;
        ਨਤੀਜਾ = vkCreateXcbSurfaceKHR(instance, &createInfo, allocator, surface);
        ਜੇ (ਨਤੀਜਾ != VK_SUCCESS) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("vkCreateXcbSurfaceKHR failed: %s", SDL_Vulkan_Get_ਨਤੀਜਾ_String(ਨਤੀਜਾ));
        }
    } ਨਹੀਂਤਾਂ {
        PFN_vkCreateXlibSurfaceKHR vkCreateXlibSurfaceKHR =
            (PFN_vkCreateXlibSurfaceKHR)vkGetInstanceProcAddr(instance,
                                                              "vkCreateXlibSurfaceKHR");
        VkXlibSurfaceCreateInfoKHR createInfo;
        Vk_ਨਤੀਜਾ ਨਤੀਜਾ;
        ਜੇ (!vkCreateXlibSurfaceKHR) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error(VK_KHR_XLIB_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        }
        SDL_zero(createInfo);
        createInfo.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
        createInfo.dpy = video_ਅੰਕੜੇ_2->display;
        createInfo.ਖਿੜਕੀ = (xcb_ਖਿੜਕੀ_t)ਖਿੜਕੀ_ਅੰਕੜੇ->xwindow;
        ਨਤੀਜਾ = vkCreateXlibSurfaceKHR(instance, &createInfo, allocator, surface);
        ਜੇ (ਨਤੀਜਾ != VK_SUCCESS) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("vkCreateXlibSurfaceKHR failed: %s", SDL_Vulkan_Get_ਨਤੀਜਾ_String(ਨਤੀਜਾ));
        }
    }

    ਵਾਪਸ true;  // success!
}

ਖਾਲੀ X11_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                               VkInstance instance,
                               VkSurfaceKHR surface,
                               ਅਚਲ ਬਣਤਰ Vk_ਵੰਡ_Callbacks *allocator)
{
    ਜੇ (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_Destroy_Surface_ਅੰਦਰੂਨੀ(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

bool X11_Vulkan_GetPresentationSupport(SDL_VideoDevice *_this,
                                           VkInstance instance,
                                           VkPhysicalDevice physicalDevice,
                                           Uint32 ਕਤਾਰ_Family_ਸੂਚਕਾਂਕ)
{
    SDL_Video_ਅੰਕੜੇ *video_ਅੰਕੜੇ_2 = _this->ਅੰਦਰੂਨੀ;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;
    ਅਚਲ ਅੱਖਰ *forced_visual_id;
    VisualID visualid;

    ਜੇ (!_this->vulkan_config.loader_handle) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Vulkan is not loaded");
    }
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;

    forced_visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_ਖਿੜਕੀ_VISUALID);
    ਜੇ (forced_visual_id) {
        visualid = SDL_strtol(forced_visual_id, ਨਿਰਾ, 0);
    } ਨਹੀਂਤਾਂ {
        visualid = X11_XVisualIDFromVisual(DefaultVisual(video_ਅੰਕੜੇ_2->display, DefaultScreen(video_ਅੰਕੜੇ_2->display)));
    }

    ਜੇ (video_ਅੰਕੜੇ_2->vulkan_xlib_xcb_library) {
        PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR vkGetPhysicalDeviceXcbPresentationSupportKHR =
            (PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR)vkGetInstanceProcAddr(
                instance,
                "vkGetPhysicalDeviceXcbPresentationSupportKHR");

        ਜੇ (!vkGetPhysicalDeviceXcbPresentationSupportKHR) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error(VK_KHR_XCB_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        }

        ਵਾਪਸ vkGetPhysicalDeviceXcbPresentationSupportKHR(physicalDevice,
                                                            ਕਤਾਰ_Family_ਸੂਚਕਾਂਕ,
                                                            video_ਅੰਕੜੇ_2->vulkan_XGetXCBConnection(video_ਅੰਕੜੇ_2->display),
                                                            visualid);
    } ਨਹੀਂਤਾਂ {
        PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR vkGetPhysicalDeviceXlibPresentationSupportKHR =
            (PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR)vkGetInstanceProcAddr(
                instance,
                "vkGetPhysicalDeviceXlibPresentationSupportKHR");

        ਜੇ (!vkGetPhysicalDeviceXlibPresentationSupportKHR) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error(VK_KHR_XLIB_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        }

        ਵਾਪਸ vkGetPhysicalDeviceXlibPresentationSupportKHR(physicalDevice,
                                                             ਕਤਾਰ_Family_ਸੂਚਕਾਂਕ,
                                                             video_ਅੰਕੜੇ_2->display,
                                                             visualid);
    }
}

#ਜੇ_ਅੰਤ
