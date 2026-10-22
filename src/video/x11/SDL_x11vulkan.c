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
#அந்தர்பாவ "SDL_internal.h"

#எனில் defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_X11)

#அந்தர்பாவ "../SDL_vulkan_internal.h"

#அந்தர்பாவ "SDL_x11video.h"

#அந்தர்பாவ "SDL_x11vulkan.h"

#அந்தர்பாவ <X11/Xlib.h>
// #include <xcb/xcb.h>

#ifdef SDL_PLATFORM_OPENBSD
#define DEFAULT_VULKAN "libvulkan.so"
#define DEFAULT_X11_XCB "libX11-xcb.so"
#இல்லையெனில்
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

bool X11_Vulkan_LoadLibrary(SDL_VideoDevice *_this, மாறிலி எழுத்து *path)
{
    SDL_VideoData *videoData = _this->internal;
    VkExtensionProperties *extensions = வெற்று;
    Uint32 extension_மொத்தம் = 0;
    bool hasSurfaceExtension = false;
    bool hasXlibSurfaceExtension = false;
    bool hasXCBSurfaceExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = வெற்று;
    Uint32 i;
    எனில் (_this->vulkan_config.loader_handle) {
        திரும்பு SDL_SetError("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    எனில் (!path) {
        path = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }
    எனில் (!path) {
        path = DEFAULT_VULKAN;
    }
    _this->vulkan_config.loader_handle = SDL_LoadObject(path);
    எனில் (!_this->vulkan_config.loader_handle) {
        திரும்பு false;
    }
    SDL_strlcpy(_this->vulkan_config.loader_path, path, SDL_arraysize(_this->vulkan_config.loader_path));
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)SDL_LoadFunction(
        _this->vulkan_config.loader_handle, "vkGetInstanceProcAddr");
    எனில் (!vkGetInstanceProcAddr) {
        செல் fail;
    }
    _this->vulkan_config.vkGetInstanceProcAddr = (வெறுமை *)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties =
        (வெறுமை *)((PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr)(
            VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties");
    எனில் (!_this->vulkan_config.vkEnumerateInstanceExtensionProperties) {
        செல் fail;
    }
    extensions = SDL_Vulkan_CreateInstanceExtensionsList(
        (PFN_vkEnumerateInstanceExtensionProperties)
            _this->vulkan_config.vkEnumerateInstanceExtensionProperties,
        &extension_மொத்தம்);
    எனில் (!extensions) {
        செல் fail;
    }
    க்கு (i = 0; i < extension_மொத்தம்; i++) {
        எனில் (SDL_strcmp(VK_KHR_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasSurfaceExtension = true;
        } இல்லையெனில் எனில் (SDL_strcmp(VK_KHR_XCB_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasXCBSurfaceExtension = true;
        } இல்லையெனில் எனில் (SDL_strcmp(VK_KHR_XLIB_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasXlibSurfaceExtension = true;
        }
    }
    SDL_free(extensions);
    எனில் (!hasSurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        செல் fail;
    }
    எனில் (hasXlibSurfaceExtension) {
        videoData->vulkan_xlib_xcb_library = வெற்று;
    } இல்லையெனில் எனில் (!hasXCBSurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement either the " VK_KHR_XCB_SURFACE_EXTENSION_NAME " extension or the " VK_KHR_XLIB_SURFACE_EXTENSION_NAME " extension");
        செல் fail;
    } இல்லையெனில் {
        மாறிலி எழுத்து *libX11XCBLibraryName = SDL_GetHint(SDL_HINT_X11_XCB_LIBRARY);
        எனில் (!libX11XCBLibraryName || !*libX11XCBLibraryName) {
            libX11XCBLibraryName = DEFAULT_X11_XCB;
        }
        videoData->vulkan_xlib_xcb_library = SDL_LoadObject(libX11XCBLibraryName);
        எனில் (!videoData->vulkan_xlib_xcb_library) {
            செல் fail;
        }
        videoData->vulkan_XGetXCBConnection =
            (PFN_XGetXCBConnection)SDL_LoadFunction(videoData->vulkan_xlib_xcb_library, "XGetXCBConnection");
        எனில் (!videoData->vulkan_XGetXCBConnection) {
            SDL_UnloadObject(videoData->vulkan_xlib_xcb_library);
            செல் fail;
        }
    }
    திரும்பு true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = வெற்று;
    திரும்பு false;
}

வெறுமை X11_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_VideoData *videoData = _this->internal;
    எனில் (_this->vulkan_config.loader_handle) {
        எனில் (videoData->vulkan_xlib_xcb_library) {
            SDL_UnloadObject(videoData->vulkan_xlib_xcb_library);
        }
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = வெற்று;
    }
}

எழுத்து மாறிலி * மாறிலி *X11_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *மொத்தம்)
{
    SDL_VideoData *videoData = _this->internal;
    எனில் (videoData->vulkan_xlib_xcb_library) {
        நிலையான மாறிலி எழுத்து *மாறிலி extensionsForXCB[] = {
            VK_KHR_SURFACE_EXTENSION_NAME,
            VK_KHR_XCB_SURFACE_EXTENSION_NAME,
        };
        *மொத்தம் = SDL_arraysize(extensionsForXCB);
        திரும்பு extensionsForXCB;
    } இல்லையெனில் {
        நிலையான மாறிலி எழுத்து *மாறிலி extensionsForXlib[] = {
            VK_KHR_SURFACE_EXTENSION_NAME,
            VK_KHR_XLIB_SURFACE_EXTENSION_NAME,
        };
        *மொத்தம் = SDL_arraysize(extensionsForXlib);
        திரும்பு extensionsForXlib;
    }
}

bool X11_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                             SDL_Window *window,
                             VkInstance instance,
                             மாறிலி கட்டமைப்பு VkAllocationCallbacks *allocator,
                             VkSurfaceKHR *surface)
{
    SDL_VideoData *videoData = _this->internal;
    SDL_WindowData *windowData = window->internal;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;
    எனில் (!_this->vulkan_config.loader_handle) {
        திரும்பு SDL_SetError("Vulkan is not loaded");
    }
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    எனில் (videoData->vulkan_xlib_xcb_library) {
        PFN_vkCreateXcbSurfaceKHR vkCreateXcbSurfaceKHR =
            (PFN_vkCreateXcbSurfaceKHR)vkGetInstanceProcAddr(instance,
                                                             "vkCreateXcbSurfaceKHR");
        VkXcbSurfaceCreateInfoKHR createInfo;
        VkResult result;
        எனில் (!vkCreateXcbSurfaceKHR) {
            திரும்பு SDL_SetError(VK_KHR_XCB_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        }
        SDL_zero(createInfo);
        createInfo.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
        createInfo.connection = videoData->vulkan_XGetXCBConnection(videoData->display);
        எனில் (!createInfo.connection) {
            திரும்பு SDL_SetError("XGetXCBConnection failed");
        }
        createInfo.window = (xcb_window_t)windowData->xwindow;
        result = vkCreateXcbSurfaceKHR(instance, &createInfo, allocator, surface);
        எனில் (result != VK_SUCCESS) {
            திரும்பு SDL_SetError("vkCreateXcbSurfaceKHR failed: %s", SDL_Vulkan_GetResultString(result));
        }
    } இல்லையெனில் {
        PFN_vkCreateXlibSurfaceKHR vkCreateXlibSurfaceKHR =
            (PFN_vkCreateXlibSurfaceKHR)vkGetInstanceProcAddr(instance,
                                                              "vkCreateXlibSurfaceKHR");
        VkXlibSurfaceCreateInfoKHR createInfo;
        VkResult result;
        எனில் (!vkCreateXlibSurfaceKHR) {
            திரும்பு SDL_SetError(VK_KHR_XLIB_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        }
        SDL_zero(createInfo);
        createInfo.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
        createInfo.dpy = videoData->display;
        createInfo.window = (xcb_window_t)windowData->xwindow;
        result = vkCreateXlibSurfaceKHR(instance, &createInfo, allocator, surface);
        எனில் (result != VK_SUCCESS) {
            திரும்பு SDL_SetError("vkCreateXlibSurfaceKHR failed: %s", SDL_Vulkan_GetResultString(result));
        }
    }

    திரும்பு true;  // success!
}

வெறுமை X11_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                               VkInstance instance,
                               VkSurfaceKHR surface,
                               மாறிலி கட்டமைப்பு VkAllocationCallbacks *allocator)
{
    எனில் (_this->vulkan_config.loader_handle) {
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
    மாறிலி எழுத்து *forced_visual_id;
    VisualID visualid;

    எனில் (!_this->vulkan_config.loader_handle) {
        திரும்பு SDL_SetError("Vulkan is not loaded");
    }
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;

    forced_visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_WINDOW_VISUALID);
    எனில் (forced_visual_id) {
        visualid = SDL_strtol(forced_visual_id, வெற்று, 0);
    } இல்லையெனில் {
        visualid = X11_XVisualIDFromVisual(DefaultVisual(videoData->display, DefaultScreen(videoData->display)));
    }

    எனில் (videoData->vulkan_xlib_xcb_library) {
        PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR vkGetPhysicalDeviceXcbPresentationSupportKHR =
            (PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR)vkGetInstanceProcAddr(
                instance,
                "vkGetPhysicalDeviceXcbPresentationSupportKHR");

        எனில் (!vkGetPhysicalDeviceXcbPresentationSupportKHR) {
            திரும்பு SDL_SetError(VK_KHR_XCB_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        }

        திரும்பு vkGetPhysicalDeviceXcbPresentationSupportKHR(physicalDevice,
                                                            queueFamilyIndex,
                                                            videoData->vulkan_XGetXCBConnection(videoData->display),
                                                            visualid);
    } இல்லையெனில் {
        PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR vkGetPhysicalDeviceXlibPresentationSupportKHR =
            (PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR)vkGetInstanceProcAddr(
                instance,
                "vkGetPhysicalDeviceXlibPresentationSupportKHR");

        எனில் (!vkGetPhysicalDeviceXlibPresentationSupportKHR) {
            திரும்பு SDL_SetError(VK_KHR_XLIB_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        }

        திரும்பு vkGetPhysicalDeviceXlibPresentationSupportKHR(physicalDevice,
                                                             queueFamilyIndex,
                                                             videoData->display,
                                                             visualid);
    }
}

#endif
