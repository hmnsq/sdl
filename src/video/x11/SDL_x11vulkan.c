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

#اگر defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_X11)

#شامل "../SDL_vulkan_internal.h"

#شامل "SDL_x11video.h"

#شامل "SDL_x11vulkan.h"

#شامل <X11/Xlib.h>
// #include <xcb/xcb.h>

#ifdef SDL_PLATFORM_OPENBSD
#define DEFAULT_VULKAN "libvulkan.so"
#define DEFAULT_X11_XCB "libX11-xcb.so"
#وگرنه
#define DEFAULT_VULKAN "libvulkan.so.1"
#define DEFAULT_X11_XCB "libX11-xcb.so.1"
#endif

SDL_ELF_NOTE_DLOPEN(
    "x11-vulkan",
    "Support for vulkan on X11",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_SUGGESTED,
    DEFAULT_VULKAN
)

SDL_ELF_NOTE_DLOPEN(
    "x11-vulkan",
    "Support for vulkan on X11",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_SUGGESTED,
    DEFAULT_X11_XCB
)

/*
typedef uint32_t xcb_window_t;
typedef uint32_t xcb_visualid_t;
*/

bool X11_Vulkan_LoadLibrary(SDL_VideoDevice *_this, ثابت نویسه *path)
{
    SDL_VideoData *videoData = _this->internal;
    VkExtensionProperties *extensions = پوچ;
    Uint32 extension_شمار = 0;
    bool hasSurfaceExtension = false;
    bool hasXlibSurfaceExtension = false;
    bool hasXCBSurfaceExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = پوچ;
    Uint32 i;
    اگر (_this->vulkan_config.loader_handle) {
        بازگشت SDL_SetError("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    اگر (!path) {
        path = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }
    اگر (!path) {
        path = DEFAULT_VULKAN;
    }
    _this->vulkan_config.loader_handle = SDL_LoadObject(path);
    اگر (!_this->vulkan_config.loader_handle) {
        بازگشت false;
    }
    SDL_strlcpy(_this->vulkan_config.loader_path, path, SDL_arraysize(_this->vulkan_config.loader_path));
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)SDL_LoadFunction(
        _this->vulkan_config.loader_handle, "vkGetInstanceProcAddr");
    اگر (!vkGetInstanceProcAddr) {
        برو fail;
    }
    _this->vulkan_config.vkGetInstanceProcAddr = (تهی *)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties =
        (تهی *)((PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr)(
            VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties");
    اگر (!_this->vulkan_config.vkEnumerateInstanceExtensionProperties) {
        برو fail;
    }
    extensions = SDL_Vulkan_CreateInstanceExtensionsList(
        (PFN_vkEnumerateInstanceExtensionProperties)
            _this->vulkan_config.vkEnumerateInstanceExtensionProperties,
        &extension_شمار);
    اگر (!extensions) {
        برو fail;
    }
    برای (i = 0; i < extension_شمار; i++) {
        اگر (SDL_strcmp(VK_KHR_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasSurfaceExtension = true;
        } وگرنه اگر (SDL_strcmp(VK_KHR_XCB_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasXCBSurfaceExtension = true;
        } وگرنه اگر (SDL_strcmp(VK_KHR_XLIB_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasXlibSurfaceExtension = true;
        }
    }
    SDL_free(extensions);
    اگر (!hasSurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        برو fail;
    }
    اگر (hasXlibSurfaceExtension) {
        videoData->vulkan_xlib_xcb_library = پوچ;
    } وگرنه اگر (!hasXCBSurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement either the " VK_KHR_XCB_SURFACE_EXTENSION_NAME " extension or the " VK_KHR_XLIB_SURFACE_EXTENSION_NAME " extension");
        برو fail;
    } وگرنه {
        ثابت نویسه *libX11XCBLibraryName = SDL_GetHint(SDL_HINT_X11_XCB_LIBRARY);
        اگر (!libX11XCBLibraryName || !*libX11XCBLibraryName) {
            libX11XCBLibraryName = DEFAULT_X11_XCB;
        }
        videoData->vulkan_xlib_xcb_library = SDL_LoadObject(libX11XCBLibraryName);
        اگر (!videoData->vulkan_xlib_xcb_library) {
            برو fail;
        }
        videoData->vulkan_XGetXCBConnection =
            (PFN_XGetXCBConnection)SDL_LoadFunction(videoData->vulkan_xlib_xcb_library, "XGetXCBConnection");
        اگر (!videoData->vulkan_XGetXCBConnection) {
            SDL_UnloadObject(videoData->vulkan_xlib_xcb_library);
            برو fail;
        }
    }
    بازگشت true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = پوچ;
    بازگشت false;
}

تهی X11_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_VideoData *videoData = _this->internal;
    اگر (_this->vulkan_config.loader_handle) {
        اگر (videoData->vulkan_xlib_xcb_library) {
            SDL_UnloadObject(videoData->vulkan_xlib_xcb_library);
        }
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = پوچ;
    }
}

نویسه ثابت * ثابت *X11_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *شمار)
{
    SDL_VideoData *videoData = _this->internal;
    اگر (videoData->vulkan_xlib_xcb_library) {
        ایستا ثابت نویسه *ثابت extensionsForXCB[] = {
            VK_KHR_SURFACE_EXTENSION_NAME,
            VK_KHR_XCB_SURFACE_EXTENSION_NAME,
        };
        *شمار = SDL_arraysize(extensionsForXCB);
        بازگشت extensionsForXCB;
    } وگرنه {
        ایستا ثابت نویسه *ثابت extensionsForXlib[] = {
            VK_KHR_SURFACE_EXTENSION_NAME,
            VK_KHR_XLIB_SURFACE_EXTENSION_NAME,
        };
        *شمار = SDL_arraysize(extensionsForXlib);
        بازگشت extensionsForXlib;
    }
}

bool X11_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                             SDL_Window *window,
                             VkInstance instance,
                             ثابت ساختار VkAllocationCallbacks *allocator,
                             VkSurfaceKHR *surface)
{
    SDL_VideoData *videoData = _this->internal;
    SDL_WindowData *windowData = window->internal;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;
    اگر (!_this->vulkan_config.loader_handle) {
        بازگشت SDL_SetError("Vulkan is not loaded");
    }
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    اگر (videoData->vulkan_xlib_xcb_library) {
        PFN_vkCreateXcbSurfaceKHR vkCreateXcbSurfaceKHR =
            (PFN_vkCreateXcbSurfaceKHR)vkGetInstanceProcAddr(instance,
                                                             "vkCreateXcbSurfaceKHR");
        VkXcbSurfaceCreateInfoKHR createInfo;
        VkResult result;
        اگر (!vkCreateXcbSurfaceKHR) {
            بازگشت SDL_SetError(VK_KHR_XCB_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        }
        SDL_zero(createInfo);
        createInfo.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
        createInfo.connection = videoData->vulkan_XGetXCBConnection(videoData->display);
        اگر (!createInfo.connection) {
            بازگشت SDL_SetError("XGetXCBConnection failed");
        }
        createInfo.window = (xcb_window_t)windowData->xwindow;
        result = vkCreateXcbSurfaceKHR(instance, &createInfo, allocator, surface);
        اگر (result != VK_SUCCESS) {
            بازگشت SDL_SetError("vkCreateXcbSurfaceKHR failed: %s", SDL_Vulkan_GetResultString(result));
        }
    } وگرنه {
        PFN_vkCreateXlibSurfaceKHR vkCreateXlibSurfaceKHR =
            (PFN_vkCreateXlibSurfaceKHR)vkGetInstanceProcAddr(instance,
                                                              "vkCreateXlibSurfaceKHR");
        VkXlibSurfaceCreateInfoKHR createInfo;
        VkResult result;
        اگر (!vkCreateXlibSurfaceKHR) {
            بازگشت SDL_SetError(VK_KHR_XLIB_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        }
        SDL_zero(createInfo);
        createInfo.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
        createInfo.dpy = videoData->display;
        createInfo.window = (xcb_window_t)windowData->xwindow;
        result = vkCreateXlibSurfaceKHR(instance, &createInfo, allocator, surface);
        اگر (result != VK_SUCCESS) {
            بازگشت SDL_SetError("vkCreateXlibSurfaceKHR failed: %s", SDL_Vulkan_GetResultString(result));
        }
    }

    بازگشت true;  // success!
}

تهی X11_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                               VkInstance instance,
                               VkSurfaceKHR surface,
                               ثابت ساختار VkAllocationCallbacks *allocator)
{
    اگر (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_DestroySurface_Internal(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

bool X11_Vulkan_GetPresentationSupport(SDL_VideoDevice *_this,
                                           VkInstance instance,
                                           VkPhysicalDevice physicalDevice,
                                           Uint32 queueFamilyIndex)
{
    SDL_VideoData *videoData = _this->internal;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;
    ثابت نویسه *forced_visual_id;
    VisualID visualid;

    اگر (!_this->vulkan_config.loader_handle) {
        بازگشت SDL_SetError("Vulkan is not loaded");
    }
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;

    forced_visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_WINDOW_VISUALID);
    اگر (forced_visual_id) {
        visualid = SDL_strtol(forced_visual_id, پوچ, 0);
    } وگرنه {
        visualid = X11_XVisualIDFromVisual(DefaultVisual(videoData->display, DefaultScreen(videoData->display)));
    }

    اگر (videoData->vulkan_xlib_xcb_library) {
        PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR vkGetPhysicalDeviceXcbPresentationSupportKHR =
            (PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR)vkGetInstanceProcAddr(
                instance,
                "vkGetPhysicalDeviceXcbPresentationSupportKHR");

        اگر (!vkGetPhysicalDeviceXcbPresentationSupportKHR) {
            بازگشت SDL_SetError(VK_KHR_XCB_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        }

        بازگشت vkGetPhysicalDeviceXcbPresentationSupportKHR(physicalDevice,
                                                            queueFamilyIndex,
                                                            videoData->vulkan_XGetXCBConnection(videoData->display),
                                                            visualid);
    } وگرنه {
        PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR vkGetPhysicalDeviceXlibPresentationSupportKHR =
            (PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR)vkGetInstanceProcAddr(
                instance,
                "vkGetPhysicalDeviceXlibPresentationSupportKHR");

        اگر (!vkGetPhysicalDeviceXlibPresentationSupportKHR) {
            بازگشت SDL_SetError(VK_KHR_XLIB_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        }

        بازگشت vkGetPhysicalDeviceXlibPresentationSupportKHR(physicalDevice,
                                                             queueFamilyIndex,
                                                             videoData->display,
                                                             visualid);
    }
}

#endif
