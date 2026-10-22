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

#ಆದರೆ defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_X11)

#ಅನ್ತರ್ಭಾವ "../SDL_vulkan_internal.h"

#ಅನ್ತರ್ಭಾವ "SDL_x11video.h"

#ಅನ್ತರ್ಭಾವ "SDL_x11vulkan.h"

#ಅನ್ತರ್ಭಾವ <X11/Xlib.h>
// #include <xcb/xcb.h>

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_PLATFORM_OPENBSD
#ವ್ಯಾಖ್ಯಾನಿಸು DEFAULT_VULKAN "libvulkan.so"
#ವ್ಯಾಖ್ಯಾನಿಸು DEFAULT_X11_XCB "libX11-xcb.so"
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು DEFAULT_VULKAN "libvulkan.so.1"
#ವ್ಯಾಖ್ಯಾನಿಸು DEFAULT_X11_XCB "libX11-xcb.so.1"
#ಆದರೆ_ಅಂತ್ಯ

SDL_ELF_NOTE_DLOPEN(
    "x11-vulkan",
    "Support for vulkan on X11",
    SDL_ELF_NOTE_DLOPEN_ಆದ್ಯತೆ_SUGGESTED,
    DEFAULT_VULKAN
)

SDL_ELF_NOTE_DLOPEN(
    "x11-vulkan",
    "Support for vulkan on X11",
    SDL_ELF_NOTE_DLOPEN_ಆದ್ಯತೆ_SUGGESTED,
    DEFAULT_X11_XCB
)

/*
typedef uint32_t xcb_window_t;
typedef uint32_t xcb_visualid_t;
*/

bool X11_Vulkan_ತುಂಬು_Library(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಮಾರ್ಗ)
{
    SDL_Video_ದತ್ತಾಂಶ *video_ದತ್ತಾಂಶ_2 = _this->ಆಂತರಿಕ;
    VkExtensionProperties *extensions = ಖಾಲಿ;
    Uint32 extension_ಎಣಿಕೆ = 0;
    bool hasSurfaceExtension = false;
    bool hasXlibSurfaceExtension = false;
    bool hasXCBSurfaceExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = ಖಾಲಿ;
    Uint32 i;
    ಆದರೆ (_this->vulkan_config.loader_handle) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    ಆದರೆ (!ಮಾರ್ಗ) {
        ಮಾರ್ಗ = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }
    ಆದರೆ (!ಮಾರ್ಗ) {
        ಮಾರ್ಗ = DEFAULT_VULKAN;
    }
    _this->vulkan_config.loader_handle = SDL_ತುಂಬು_Object(ಮಾರ್ಗ);
    ಆದರೆ (!_this->vulkan_config.loader_handle) {
        ಹಿಂತಿರುಗಿ false;
    }
    SDL_strlcpy(_this->vulkan_config.loader_ಮಾರ್ಗ, ಮಾರ್ಗ, SDL_arraysize(_this->vulkan_config.loader_ಮಾರ್ಗ));
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)SDL_ತುಂಬು_Function(
        _this->vulkan_config.loader_handle, "vkGetInstanceProcAddr");
    ಆದರೆ (!vkGetInstanceProcAddr) {
        ಹೋಗು fail;
    }
    _this->vulkan_config.vkGetInstanceProcAddr = (ಶೂನ್ಯ *)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties =
        (ಶೂನ್ಯ *)((PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr)(
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
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(VK_KHR_XCB_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasXCBSurfaceExtension = true;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(VK_KHR_XLIB_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasXlibSurfaceExtension = true;
        }
    }
    SDL_free(extensions);
    ಆದರೆ (!hasSurfaceExtension) {
        SDL_ಗಣ_Error("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        ಹೋಗು fail;
    }
    ಆದರೆ (hasXlibSurfaceExtension) {
        video_ದತ್ತಾಂಶ_2->vulkan_xlib_xcb_library = ಖಾಲಿ;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!hasXCBSurfaceExtension) {
        SDL_ಗಣ_Error("Installed Vulkan doesn't implement either the " VK_KHR_XCB_SURFACE_EXTENSION_NAME " extension or the " VK_KHR_XLIB_SURFACE_EXTENSION_NAME " extension");
        ಹೋಗು fail;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *libX11XCBLibraryName = SDL_GetHint(SDL_HINT_X11_XCB_LIBRARY);
        ಆದರೆ (!libX11XCBLibraryName || !*libX11XCBLibraryName) {
            libX11XCBLibraryName = DEFAULT_X11_XCB;
        }
        video_ದತ್ತಾಂಶ_2->vulkan_xlib_xcb_library = SDL_ತುಂಬು_Object(libX11XCBLibraryName);
        ಆದರೆ (!video_ದತ್ತಾಂಶ_2->vulkan_xlib_xcb_library) {
            ಹೋಗು fail;
        }
        video_ದತ್ತಾಂಶ_2->vulkan_XGetXCBConnection =
            (PFN_XGetXCBConnection)SDL_ತುಂಬು_Function(video_ದತ್ತಾಂಶ_2->vulkan_xlib_xcb_library, "XGetXCBConnection");
        ಆದರೆ (!video_ದತ್ತಾಂಶ_2->vulkan_XGetXCBConnection) {
            SDL_UnloadObject(video_ದತ್ತಾಂಶ_2->vulkan_xlib_xcb_library);
            ಹೋಗು fail;
        }
    }
    ಹಿಂತಿರುಗಿ true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = ಖಾಲಿ;
    ಹಿಂತಿರುಗಿ false;
}

ಶೂನ್ಯ X11_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_Video_ದತ್ತಾಂಶ *video_ದತ್ತಾಂಶ_2 = _this->ಆಂತರಿಕ;
    ಆದರೆ (_this->vulkan_config.loader_handle) {
        ಆದರೆ (video_ದತ್ತಾಂಶ_2->vulkan_xlib_xcb_library) {
            SDL_UnloadObject(video_ದತ್ತಾಂಶ_2->vulkan_xlib_xcb_library);
        }
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = ಖಾಲಿ;
    }
}

ಅಕ್ಷರ ಸ್ಥಿರಾಂಕ * ಸ್ಥಿರಾಂಕ *X11_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *ಎಣಿಕೆ_2)
{
    SDL_Video_ದತ್ತಾಂಶ *video_ದತ್ತಾಂಶ_2 = _this->ಆಂತರಿಕ;
    ಆದರೆ (video_ದತ್ತಾಂಶ_2->vulkan_xlib_xcb_library) {
        ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸ್ಥಿರಾಂಕ extensionsForXCB[] = {
            VK_KHR_SURFACE_EXTENSION_NAME,
            VK_KHR_XCB_SURFACE_EXTENSION_NAME,
        };
        *ಎಣಿಕೆ_2 = SDL_arraysize(extensionsForXCB);
        ಹಿಂತಿರುಗಿ extensionsForXCB;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸ್ಥಿರಾಂಕ extensionsForXlib[] = {
            VK_KHR_SURFACE_EXTENSION_NAME,
            VK_KHR_XLIB_SURFACE_EXTENSION_NAME,
        };
        *ಎಣಿಕೆ_2 = SDL_arraysize(extensionsForXlib);
        ಹಿಂತಿರುಗಿ extensionsForXlib;
    }
}

bool X11_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                             SDL_ಕಿಟಕಿ *ಕಿಟಕಿ,
                             VkInstance instance,
                             ಸ್ಥಿರಾಂಕ ರಚನೆ Vk_ಹಂಚಿಕೆ_Callbacks *allocator,
                             VkSurfaceKHR *surface)
{
    SDL_Video_ದತ್ತಾಂಶ *video_ದತ್ತಾಂಶ_2 = _this->ಆಂತರಿಕ;
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;
    ಆದರೆ (!_this->vulkan_config.loader_handle) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Vulkan is not loaded");
    }
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    ಆದರೆ (video_ದತ್ತಾಂಶ_2->vulkan_xlib_xcb_library) {
        PFN_vkCreateXcbSurfaceKHR vkCreateXcbSurfaceKHR =
            (PFN_vkCreateXcbSurfaceKHR)vkGetInstanceProcAddr(instance,
                                                             "vkCreateXcbSurfaceKHR");
        VkXcbSurfaceCreateInfoKHR createInfo;
        Vk_ಫಲಿತಾಂಶ ಫಲಿತಾಂಶ;
        ಆದರೆ (!vkCreateXcbSurfaceKHR) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error(VK_KHR_XCB_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        }
        SDL_zero(createInfo);
        createInfo.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
        createInfo.connection = video_ದತ್ತಾಂಶ_2->vulkan_XGetXCBConnection(video_ದತ್ತಾಂಶ_2->display);
        ಆದರೆ (!createInfo.connection) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("XGetXCBConnection failed");
        }
        createInfo.ಕಿಟಕಿ = (xcb_ಕಿಟಕಿ_t)ಕಿಟಕಿ_ದತ್ತಾಂಶ->xwindow;
        ಫಲಿತಾಂಶ = vkCreateXcbSurfaceKHR(instance, &createInfo, allocator, surface);
        ಆದರೆ (ಫಲಿತಾಂಶ != VK_SUCCESS) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("vkCreateXcbSurfaceKHR failed: %s", SDL_Vulkan_Get_ಫಲಿತಾಂಶ_String(ಫಲಿತಾಂಶ));
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        PFN_vkCreateXlibSurfaceKHR vkCreateXlibSurfaceKHR =
            (PFN_vkCreateXlibSurfaceKHR)vkGetInstanceProcAddr(instance,
                                                              "vkCreateXlibSurfaceKHR");
        VkXlibSurfaceCreateInfoKHR createInfo;
        Vk_ಫಲಿತಾಂಶ ಫಲಿತಾಂಶ;
        ಆದರೆ (!vkCreateXlibSurfaceKHR) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error(VK_KHR_XLIB_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        }
        SDL_zero(createInfo);
        createInfo.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
        createInfo.dpy = video_ದತ್ತಾಂಶ_2->display;
        createInfo.ಕಿಟಕಿ = (xcb_ಕಿಟಕಿ_t)ಕಿಟಕಿ_ದತ್ತಾಂಶ->xwindow;
        ಫಲಿತಾಂಶ = vkCreateXlibSurfaceKHR(instance, &createInfo, allocator, surface);
        ಆದರೆ (ಫಲಿತಾಂಶ != VK_SUCCESS) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("vkCreateXlibSurfaceKHR failed: %s", SDL_Vulkan_Get_ಫಲಿತಾಂಶ_String(ಫಲಿತಾಂಶ));
        }
    }

    ಹಿಂತಿರುಗಿ true;  // success!
}

ಶೂನ್ಯ X11_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                               VkInstance instance,
                               VkSurfaceKHR surface,
                               ಸ್ಥಿರಾಂಕ ರಚನೆ Vk_ಹಂಚಿಕೆ_Callbacks *allocator)
{
    ಆದರೆ (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_Destroy_Surface_ಆಂತರಿಕ(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

bool X11_Vulkan_GetPresentationSupport(SDL_VideoDevice *_this,
                                           VkInstance instance,
                                           VkPhysicalDevice physicalDevice,
                                           Uint32 ಸರತಿ_Family_ಸೂಚ್ಯಂಕ)
{
    SDL_Video_ದತ್ತಾಂಶ *video_ದತ್ತಾಂಶ_2 = _this->ಆಂತರಿಕ;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *forced_visual_id;
    VisualID visualid;

    ಆದರೆ (!_this->vulkan_config.loader_handle) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Vulkan is not loaded");
    }
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;

    forced_visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_ಕಿಟಕಿ_VISUALID);
    ಆದರೆ (forced_visual_id) {
        visualid = SDL_strtol(forced_visual_id, ಖಾಲಿ, 0);
    } ಇಲ್ಲದಿದ್ದರೆ {
        visualid = X11_XVisualIDFromVisual(DefaultVisual(video_ದತ್ತಾಂಶ_2->display, DefaultScreen(video_ದತ್ತಾಂಶ_2->display)));
    }

    ಆದರೆ (video_ದತ್ತಾಂಶ_2->vulkan_xlib_xcb_library) {
        PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR vkGetPhysicalDeviceXcbPresentationSupportKHR =
            (PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR)vkGetInstanceProcAddr(
                instance,
                "vkGetPhysicalDeviceXcbPresentationSupportKHR");

        ಆದರೆ (!vkGetPhysicalDeviceXcbPresentationSupportKHR) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error(VK_KHR_XCB_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        }

        ಹಿಂತಿರುಗಿ vkGetPhysicalDeviceXcbPresentationSupportKHR(physicalDevice,
                                                            ಸರತಿ_Family_ಸೂಚ್ಯಂಕ,
                                                            video_ದತ್ತಾಂಶ_2->vulkan_XGetXCBConnection(video_ದತ್ತಾಂಶ_2->display),
                                                            visualid);
    } ಇಲ್ಲದಿದ್ದರೆ {
        PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR vkGetPhysicalDeviceXlibPresentationSupportKHR =
            (PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR)vkGetInstanceProcAddr(
                instance,
                "vkGetPhysicalDeviceXlibPresentationSupportKHR");

        ಆದರೆ (!vkGetPhysicalDeviceXlibPresentationSupportKHR) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error(VK_KHR_XLIB_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        }

        ಹಿಂತಿರುಗಿ vkGetPhysicalDeviceXlibPresentationSupportKHR(physicalDevice,
                                                             ಸರತಿ_Family_ಸೂಚ್ಯಂಕ,
                                                             video_ದತ್ತಾಂಶ_2->display,
                                                             visualid);
    }
}

#ಆದರೆ_ಅಂತ್ಯ
