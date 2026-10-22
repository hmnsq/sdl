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
#include "SDL_internal.h"

#གལ་སྲིད defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_X11)

#include "../SDL_vulkan_internal.h"

#include "SDL_x11video.h"

#include "SDL_x11vulkan.h"

#include <X11/Xlib.h>
// #include <xcb/xcb.h>

#ifdef SDL_PLATFORM_OPENBSD
#define DEFAULT_VULKAN "libvulkan.so"
#define DEFAULT_X11_XCB "libX11-xcb.so"
#དེ་མིན
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

bool X11_Vulkan_LoadLibrary(SDL_VideoDevice *_this, const var_na *path)
{
    SDL_VideoData *videoData = _this->internal;
    VkExtensionProperties *extensions = NULL;
    Uint32 extensionCount = 0;
    bool hasSurfaceExtension = false;
    bool hasXlibSurfaceExtension = false;
    bool hasXCBSurfaceExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = NULL;
    Uint32 i;
    གལ་སྲིད (_this->vulkan_config.loader_handle) {
        ལོག SDL_SetError("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    གལ་སྲིད (!path) {
        path = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }
    གལ་སྲིད (!path) {
        path = DEFAULT_VULKAN;
    }
    _this->vulkan_config.loader_handle = SDL_LoadObject(path);
    གལ་སྲིད (!_this->vulkan_config.loader_handle) {
        ལོག false;
    }
    SDL_strlcpy(_this->vulkan_config.loader_path, path, SDL_arraysize(_this->vulkan_config.loader_path));
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)SDL_LoadFunction(
        _this->vulkan_config.loader_handle, "vkGetInstanceProcAddr");
    གལ་སྲིད (!vkGetInstanceProcAddr) {
        goto fail;
    }
    _this->vulkan_config.vkGetInstanceProcAddr = (void *)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties =
        (void *)((PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr)(
            VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties");
    གལ་སྲིད (!_this->vulkan_config.vkEnumerateInstanceExtensionProperties) {
        goto fail;
    }
    extensions = SDL_Vulkan_CreateInstanceExtensionsList(
        (PFN_vkEnumerateInstanceExtensionProperties)
            _this->vulkan_config.vkEnumerateInstanceExtensionProperties,
        &extensionCount);
    གལ་སྲིད (!extensions) {
        goto fail;
    }
    དོན་ལུ (i = 0; i < extensionCount; i++) {
        གལ་སྲིད (SDL_strcmp(VK_KHR_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasSurfaceExtension = true;
        } དེ་མིན གལ་སྲིད (SDL_strcmp(VK_KHR_XCB_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasXCBSurfaceExtension = true;
        } དེ་མིན གལ་སྲིད (SDL_strcmp(VK_KHR_XLIB_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasXlibSurfaceExtension = true;
        }
    }
    SDL_free(extensions);
    གལ་སྲིད (!hasSurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        goto fail;
    }
    གལ་སྲིད (hasXlibSurfaceExtension) {
        videoData->vulkan_xlib_xcb_library = NULL;
    } དེ་མིན གལ་སྲིད (!hasXCBSurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement either the " VK_KHR_XCB_SURFACE_EXTENSION_NAME " extension or the " VK_KHR_XLIB_SURFACE_EXTENSION_NAME " extension");
        goto fail;
    } དེ་མིན {
        const var_na *libX11XCBLibraryName = SDL_GetHint(SDL_HINT_X11_XCB_LIBRARY);
        གལ་སྲིད (!libX11XCBLibraryName || !*libX11XCBLibraryName) {
            libX11XCBLibraryName = DEFAULT_X11_XCB;
        }
        videoData->vulkan_xlib_xcb_library = SDL_LoadObject(libX11XCBLibraryName);
        གལ་སྲིད (!videoData->vulkan_xlib_xcb_library) {
            goto fail;
        }
        videoData->vulkan_XGetXCBConnection =
            (PFN_XGetXCBConnection)SDL_LoadFunction(videoData->vulkan_xlib_xcb_library, "XGetXCBConnection");
        གལ་སྲིད (!videoData->vulkan_XGetXCBConnection) {
            SDL_UnloadObject(videoData->vulkan_xlib_xcb_library);
            goto fail;
        }
    }
    ལོག true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = NULL;
    ལོག false;
}

void X11_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_VideoData *videoData = _this->internal;
    གལ་སྲིད (_this->vulkan_config.loader_handle) {
        གལ་སྲིད (videoData->vulkan_xlib_xcb_library) {
            SDL_UnloadObject(videoData->vulkan_xlib_xcb_library);
        }
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = NULL;
    }
}

var_na const * const *X11_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *count)
{
    SDL_VideoData *videoData = _this->internal;
    གལ་སྲིད (videoData->vulkan_xlib_xcb_library) {
        static const var_na *const extensionsForXCB[] = {
            VK_KHR_SURFACE_EXTENSION_NAME,
            VK_KHR_XCB_SURFACE_EXTENSION_NAME,
        };
        *count = SDL_arraysize(extensionsForXCB);
        ལོག extensionsForXCB;
    } དེ་མིན {
        static const var_na *const extensionsForXlib[] = {
            VK_KHR_SURFACE_EXTENSION_NAME,
            VK_KHR_XLIB_SURFACE_EXTENSION_NAME,
        };
        *count = SDL_arraysize(extensionsForXlib);
        ལོག extensionsForXlib;
    }
}

bool X11_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                             SDL_Window *window,
                             VkInstance instance,
                             const sa_nracanaa VkAllocationCallbacks *allocator,
                             VkSurfaceKHR *surface)
{
    SDL_VideoData *videoData = _this->internal;
    SDL_WindowData *windowData = window->internal;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;
    གལ་སྲིད (!_this->vulkan_config.loader_handle) {
        ལོག SDL_SetError("Vulkan is not loaded");
    }
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    གལ་སྲིད (videoData->vulkan_xlib_xcb_library) {
        PFN_vkCreateXcbSurfaceKHR vkCreateXcbSurfaceKHR =
            (PFN_vkCreateXcbSurfaceKHR)vkGetInstanceProcAddr(instance,
                                                             "vkCreateXcbSurfaceKHR");
        VkXcbSurfaceCreateInfoKHR createInfo;
        VkResult result;
        གལ་སྲིད (!vkCreateXcbSurfaceKHR) {
            ལོག SDL_SetError(VK_KHR_XCB_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        }
        SDL_zero(createInfo);
        createInfo.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
        createInfo.connection = videoData->vulkan_XGetXCBConnection(videoData->display);
        གལ་སྲིད (!createInfo.connection) {
            ལོག SDL_SetError("XGetXCBConnection failed");
        }
        createInfo.window = (xcb_window_t)windowData->xwindow;
        result = vkCreateXcbSurfaceKHR(instance, &createInfo, allocator, surface);
        གལ་སྲིད (result != VK_SUCCESS) {
            ལོག SDL_SetError("vkCreateXcbSurfaceKHR failed: %s", SDL_Vulkan_GetResultString(result));
        }
    } དེ་མིན {
        PFN_vkCreateXlibSurfaceKHR vkCreateXlibSurfaceKHR =
            (PFN_vkCreateXlibSurfaceKHR)vkGetInstanceProcAddr(instance,
                                                              "vkCreateXlibSurfaceKHR");
        VkXlibSurfaceCreateInfoKHR createInfo;
        VkResult result;
        གལ་སྲིད (!vkCreateXlibSurfaceKHR) {
            ལོག SDL_SetError(VK_KHR_XLIB_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        }
        SDL_zero(createInfo);
        createInfo.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
        createInfo.dpy = videoData->display;
        createInfo.window = (xcb_window_t)windowData->xwindow;
        result = vkCreateXlibSurfaceKHR(instance, &createInfo, allocator, surface);
        གལ་སྲིད (result != VK_SUCCESS) {
            ལོག SDL_SetError("vkCreateXlibSurfaceKHR failed: %s", SDL_Vulkan_GetResultString(result));
        }
    }

    ལོག true;  // success!
}

void X11_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                               VkInstance instance,
                               VkSurfaceKHR surface,
                               const sa_nracanaa VkAllocationCallbacks *allocator)
{
    གལ་སྲིད (_this->vulkan_config.loader_handle) {
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
    const var_na *forced_visual_id;
    VisualID visualid;

    གལ་སྲིད (!_this->vulkan_config.loader_handle) {
        ལོག SDL_SetError("Vulkan is not loaded");
    }
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;

    forced_visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_WINDOW_VISUALID);
    གལ་སྲིད (forced_visual_id) {
        visualid = SDL_strtol(forced_visual_id, NULL, 0);
    } དེ་མིན {
        visualid = X11_XVisualIDFromVisual(DefaultVisual(videoData->display, DefaultScreen(videoData->display)));
    }

    གལ་སྲིད (videoData->vulkan_xlib_xcb_library) {
        PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR vkGetPhysicalDeviceXcbPresentationSupportKHR =
            (PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR)vkGetInstanceProcAddr(
                instance,
                "vkGetPhysicalDeviceXcbPresentationSupportKHR");

        གལ་སྲིད (!vkGetPhysicalDeviceXcbPresentationSupportKHR) {
            ལོག SDL_SetError(VK_KHR_XCB_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        }

        ལོག vkGetPhysicalDeviceXcbPresentationSupportKHR(physicalDevice,
                                                            queueFamilyIndex,
                                                            videoData->vulkan_XGetXCBConnection(videoData->display),
                                                            visualid);
    } དེ་མིན {
        PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR vkGetPhysicalDeviceXlibPresentationSupportKHR =
            (PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR)vkGetInstanceProcAddr(
                instance,
                "vkGetPhysicalDeviceXlibPresentationSupportKHR");

        གལ་སྲིད (!vkGetPhysicalDeviceXlibPresentationSupportKHR) {
            ལོག SDL_SetError(VK_KHR_XLIB_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        }

        ལོག vkGetPhysicalDeviceXlibPresentationSupportKHR(physicalDevice,
                                                             queueFamilyIndex,
                                                             videoData->display,
                                                             visualid);
    }
}

#endif
