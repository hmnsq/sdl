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

#जर defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_X11)

#अन्तर्भाव "../SDL_vulkan_internal.h"

#अन्तर्भाव "SDL_x11video.h"

#अन्तर्भाव "SDL_x11vulkan.h"

#अन्तर्भाव <X11/Xlib.h>
// #include <xcb/xcb.h>

#ifdef SDL_PLATFORM_OPENBSD
#define DEFAULT_VULKAN "libvulkan.so"
#define DEFAULT_X11_XCB "libX11-xcb.so"
#अन्यथा
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

bool X11_Vulkan_LoadLibrary(SDL_VideoDevice *_this, स्थिरांक अक्षर *path)
{
    SDL_VideoData *videoData = _this->internal;
    VkExtensionProperties *extensions = रिक्त;
    Uint32 extension_मोजणी = 0;
    bool hasSurfaceExtension = false;
    bool hasXlibSurfaceExtension = false;
    bool hasXCBSurfaceExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = रिक्त;
    Uint32 i;
    जर (_this->vulkan_config.loader_handle) {
        परत SDL_SetError("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    जर (!path) {
        path = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }
    जर (!path) {
        path = DEFAULT_VULKAN;
    }
    _this->vulkan_config.loader_handle = SDL_LoadObject(path);
    जर (!_this->vulkan_config.loader_handle) {
        परत false;
    }
    SDL_strlcpy(_this->vulkan_config.loader_path, path, SDL_arraysize(_this->vulkan_config.loader_path));
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)SDL_LoadFunction(
        _this->vulkan_config.loader_handle, "vkGetInstanceProcAddr");
    जर (!vkGetInstanceProcAddr) {
        जा fail;
    }
    _this->vulkan_config.vkGetInstanceProcAddr = (शून्य *)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties =
        (शून्य *)((PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr)(
            VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties");
    जर (!_this->vulkan_config.vkEnumerateInstanceExtensionProperties) {
        जा fail;
    }
    extensions = SDL_Vulkan_CreateInstanceExtensionsList(
        (PFN_vkEnumerateInstanceExtensionProperties)
            _this->vulkan_config.vkEnumerateInstanceExtensionProperties,
        &extension_मोजणी);
    जर (!extensions) {
        जा fail;
    }
    साठी (i = 0; i < extension_मोजणी; i++) {
        जर (SDL_strcmp(VK_KHR_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasSurfaceExtension = true;
        } अन्यथा जर (SDL_strcmp(VK_KHR_XCB_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasXCBSurfaceExtension = true;
        } अन्यथा जर (SDL_strcmp(VK_KHR_XLIB_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasXlibSurfaceExtension = true;
        }
    }
    SDL_free(extensions);
    जर (!hasSurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        जा fail;
    }
    जर (hasXlibSurfaceExtension) {
        videoData->vulkan_xlib_xcb_library = रिक्त;
    } अन्यथा जर (!hasXCBSurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement either the " VK_KHR_XCB_SURFACE_EXTENSION_NAME " extension or the " VK_KHR_XLIB_SURFACE_EXTENSION_NAME " extension");
        जा fail;
    } अन्यथा {
        स्थिरांक अक्षर *libX11XCBLibraryName = SDL_GetHint(SDL_HINT_X11_XCB_LIBRARY);
        जर (!libX11XCBLibraryName || !*libX11XCBLibraryName) {
            libX11XCBLibraryName = DEFAULT_X11_XCB;
        }
        videoData->vulkan_xlib_xcb_library = SDL_LoadObject(libX11XCBLibraryName);
        जर (!videoData->vulkan_xlib_xcb_library) {
            जा fail;
        }
        videoData->vulkan_XGetXCBConnection =
            (PFN_XGetXCBConnection)SDL_LoadFunction(videoData->vulkan_xlib_xcb_library, "XGetXCBConnection");
        जर (!videoData->vulkan_XGetXCBConnection) {
            SDL_UnloadObject(videoData->vulkan_xlib_xcb_library);
            जा fail;
        }
    }
    परत true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = रिक्त;
    परत false;
}

शून्य X11_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_VideoData *videoData = _this->internal;
    जर (_this->vulkan_config.loader_handle) {
        जर (videoData->vulkan_xlib_xcb_library) {
            SDL_UnloadObject(videoData->vulkan_xlib_xcb_library);
        }
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = रिक्त;
    }
}

अक्षर स्थिरांक * स्थिरांक *X11_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *मोजणी)
{
    SDL_VideoData *videoData = _this->internal;
    जर (videoData->vulkan_xlib_xcb_library) {
        स्थिर स्थिरांक अक्षर *स्थिरांक extensionsForXCB[] = {
            VK_KHR_SURFACE_EXTENSION_NAME,
            VK_KHR_XCB_SURFACE_EXTENSION_NAME,
        };
        *मोजणी = SDL_arraysize(extensionsForXCB);
        परत extensionsForXCB;
    } अन्यथा {
        स्थिर स्थिरांक अक्षर *स्थिरांक extensionsForXlib[] = {
            VK_KHR_SURFACE_EXTENSION_NAME,
            VK_KHR_XLIB_SURFACE_EXTENSION_NAME,
        };
        *मोजणी = SDL_arraysize(extensionsForXlib);
        परत extensionsForXlib;
    }
}

bool X11_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                             SDL_Window *window,
                             VkInstance instance,
                             स्थिरांक संरचना VkAllocationCallbacks *allocator,
                             VkSurfaceKHR *surface)
{
    SDL_VideoData *videoData = _this->internal;
    SDL_WindowData *windowData = window->internal;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;
    जर (!_this->vulkan_config.loader_handle) {
        परत SDL_SetError("Vulkan is not loaded");
    }
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    जर (videoData->vulkan_xlib_xcb_library) {
        PFN_vkCreateXcbSurfaceKHR vkCreateXcbSurfaceKHR =
            (PFN_vkCreateXcbSurfaceKHR)vkGetInstanceProcAddr(instance,
                                                             "vkCreateXcbSurfaceKHR");
        VkXcbSurfaceCreateInfoKHR createInfo;
        VkResult result;
        जर (!vkCreateXcbSurfaceKHR) {
            परत SDL_SetError(VK_KHR_XCB_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        }
        SDL_zero(createInfo);
        createInfo.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
        createInfo.connection = videoData->vulkan_XGetXCBConnection(videoData->display);
        जर (!createInfo.connection) {
            परत SDL_SetError("XGetXCBConnection failed");
        }
        createInfo.window = (xcb_window_t)windowData->xwindow;
        result = vkCreateXcbSurfaceKHR(instance, &createInfo, allocator, surface);
        जर (result != VK_SUCCESS) {
            परत SDL_SetError("vkCreateXcbSurfaceKHR failed: %s", SDL_Vulkan_GetResultString(result));
        }
    } अन्यथा {
        PFN_vkCreateXlibSurfaceKHR vkCreateXlibSurfaceKHR =
            (PFN_vkCreateXlibSurfaceKHR)vkGetInstanceProcAddr(instance,
                                                              "vkCreateXlibSurfaceKHR");
        VkXlibSurfaceCreateInfoKHR createInfo;
        VkResult result;
        जर (!vkCreateXlibSurfaceKHR) {
            परत SDL_SetError(VK_KHR_XLIB_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        }
        SDL_zero(createInfo);
        createInfo.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
        createInfo.dpy = videoData->display;
        createInfo.window = (xcb_window_t)windowData->xwindow;
        result = vkCreateXlibSurfaceKHR(instance, &createInfo, allocator, surface);
        जर (result != VK_SUCCESS) {
            परत SDL_SetError("vkCreateXlibSurfaceKHR failed: %s", SDL_Vulkan_GetResultString(result));
        }
    }

    परत true;  // success!
}

शून्य X11_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                               VkInstance instance,
                               VkSurfaceKHR surface,
                               स्थिरांक संरचना VkAllocationCallbacks *allocator)
{
    जर (_this->vulkan_config.loader_handle) {
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
    स्थिरांक अक्षर *forced_visual_id;
    VisualID visualid;

    जर (!_this->vulkan_config.loader_handle) {
        परत SDL_SetError("Vulkan is not loaded");
    }
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;

    forced_visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_WINDOW_VISUALID);
    जर (forced_visual_id) {
        visualid = SDL_strtol(forced_visual_id, रिक्त, 0);
    } अन्यथा {
        visualid = X11_XVisualIDFromVisual(DefaultVisual(videoData->display, DefaultScreen(videoData->display)));
    }

    जर (videoData->vulkan_xlib_xcb_library) {
        PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR vkGetPhysicalDeviceXcbPresentationSupportKHR =
            (PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR)vkGetInstanceProcAddr(
                instance,
                "vkGetPhysicalDeviceXcbPresentationSupportKHR");

        जर (!vkGetPhysicalDeviceXcbPresentationSupportKHR) {
            परत SDL_SetError(VK_KHR_XCB_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        }

        परत vkGetPhysicalDeviceXcbPresentationSupportKHR(physicalDevice,
                                                            queueFamilyIndex,
                                                            videoData->vulkan_XGetXCBConnection(videoData->display),
                                                            visualid);
    } अन्यथा {
        PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR vkGetPhysicalDeviceXlibPresentationSupportKHR =
            (PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR)vkGetInstanceProcAddr(
                instance,
                "vkGetPhysicalDeviceXlibPresentationSupportKHR");

        जर (!vkGetPhysicalDeviceXlibPresentationSupportKHR) {
            परत SDL_SetError(VK_KHR_XLIB_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        }

        परत vkGetPhysicalDeviceXlibPresentationSupportKHR(physicalDevice,
                                                             queueFamilyIndex,
                                                             videoData->display,
                                                             visualid);
    }
}

#endif
