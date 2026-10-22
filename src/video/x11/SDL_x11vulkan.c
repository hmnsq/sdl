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
#অন্তর্ভাব "SDL_internal.h"

#যদি defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_X11)

#অন্তর্ভাব "../SDL_vulkan_internal.h"

#অন্তর্ভাব "SDL_x11video.h"

#অন্তর্ভাব "SDL_x11vulkan.h"

#অন্তর্ভাব <X11/Xlib.h>
// #include <xcb/xcb.h>

#ifdef SDL_PLATFORM_OPENBSD
#define DEFAULT_VULKAN "libvulkan.so"
#define DEFAULT_X11_XCB "libX11-xcb.so"
#অন্যথা
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

bool X11_Vulkan_LoadLibrary(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *path)
{
    SDL_Video_তথ্য *video_তথ্য_2 = _this->internal;
    VkExtensionProperties *extensions = ফাঁকা;
    Uint32 extension_গুনতি = 0;
    bool hasSurfaceExtension = false;
    bool hasXlibSurfaceExtension = false;
    bool hasXCBSurfaceExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = ফাঁকা;
    Uint32 i;
    যদি (_this->vulkan_config.loader_handle) {
        ফেরত SDL_SetError("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    যদি (!path) {
        path = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }
    যদি (!path) {
        path = DEFAULT_VULKAN;
    }
    _this->vulkan_config.loader_handle = SDL_LoadObject(path);
    যদি (!_this->vulkan_config.loader_handle) {
        ফেরত false;
    }
    SDL_strlcpy(_this->vulkan_config.loader_path, path, SDL_arraysize(_this->vulkan_config.loader_path));
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)SDL_LoadFunction(
        _this->vulkan_config.loader_handle, "vkGetInstanceProcAddr");
    যদি (!vkGetInstanceProcAddr) {
        যাও fail;
    }
    _this->vulkan_config.vkGetInstanceProcAddr = (শূন্য *)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties =
        (শূন্য *)((PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr)(
            VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties");
    যদি (!_this->vulkan_config.vkEnumerateInstanceExtensionProperties) {
        যাও fail;
    }
    extensions = SDL_Vulkan_CreateInstanceExtensionsList(
        (PFN_vkEnumerateInstanceExtensionProperties)
            _this->vulkan_config.vkEnumerateInstanceExtensionProperties,
        &extension_গুনতি);
    যদি (!extensions) {
        যাও fail;
    }
    জন্য (i = 0; i < extension_গুনতি; i++) {
        যদি (SDL_strcmp(VK_KHR_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasSurfaceExtension = true;
        } অন্যথা যদি (SDL_strcmp(VK_KHR_XCB_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasXCBSurfaceExtension = true;
        } অন্যথা যদি (SDL_strcmp(VK_KHR_XLIB_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasXlibSurfaceExtension = true;
        }
    }
    SDL_free(extensions);
    যদি (!hasSurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        যাও fail;
    }
    যদি (hasXlibSurfaceExtension) {
        video_তথ্য_2->vulkan_xlib_xcb_library = ফাঁকা;
    } অন্যথা যদি (!hasXCBSurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement either the " VK_KHR_XCB_SURFACE_EXTENSION_NAME " extension or the " VK_KHR_XLIB_SURFACE_EXTENSION_NAME " extension");
        যাও fail;
    } অন্যথা {
        ধ্রুবক অক্ষর *libX11XCBLibraryName = SDL_GetHint(SDL_HINT_X11_XCB_LIBRARY);
        যদি (!libX11XCBLibraryName || !*libX11XCBLibraryName) {
            libX11XCBLibraryName = DEFAULT_X11_XCB;
        }
        video_তথ্য_2->vulkan_xlib_xcb_library = SDL_LoadObject(libX11XCBLibraryName);
        যদি (!video_তথ্য_2->vulkan_xlib_xcb_library) {
            যাও fail;
        }
        video_তথ্য_2->vulkan_XGetXCBConnection =
            (PFN_XGetXCBConnection)SDL_LoadFunction(video_তথ্য_2->vulkan_xlib_xcb_library, "XGetXCBConnection");
        যদি (!video_তথ্য_2->vulkan_XGetXCBConnection) {
            SDL_UnloadObject(video_তথ্য_2->vulkan_xlib_xcb_library);
            যাও fail;
        }
    }
    ফেরত true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = ফাঁকা;
    ফেরত false;
}

শূন্য X11_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_Video_তথ্য *video_তথ্য_2 = _this->internal;
    যদি (_this->vulkan_config.loader_handle) {
        যদি (video_তথ্য_2->vulkan_xlib_xcb_library) {
            SDL_UnloadObject(video_তথ্য_2->vulkan_xlib_xcb_library);
        }
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = ফাঁকা;
    }
}

অক্ষর ধ্রুবক * ধ্রুবক *X11_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *গুনতি)
{
    SDL_Video_তথ্য *video_তথ্য_2 = _this->internal;
    যদি (video_তথ্য_2->vulkan_xlib_xcb_library) {
        স্থির ধ্রুবক অক্ষর *ধ্রুবক extensionsForXCB[] = {
            VK_KHR_SURFACE_EXTENSION_NAME,
            VK_KHR_XCB_SURFACE_EXTENSION_NAME,
        };
        *গুনতি = SDL_arraysize(extensionsForXCB);
        ফেরত extensionsForXCB;
    } অন্যথা {
        স্থির ধ্রুবক অক্ষর *ধ্রুবক extensionsForXlib[] = {
            VK_KHR_SURFACE_EXTENSION_NAME,
            VK_KHR_XLIB_SURFACE_EXTENSION_NAME,
        };
        *গুনতি = SDL_arraysize(extensionsForXlib);
        ফেরত extensionsForXlib;
    }
}

bool X11_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                             SDL_Window *window,
                             VkInstance instance,
                             ধ্রুবক কাঠামো VkAllocationCallbacks *allocator,
                             VkSurfaceKHR *surface)
{
    SDL_Video_তথ্য *video_তথ্য_2 = _this->internal;
    SDL_Window_তথ্য *window_তথ্য = window->internal;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;
    যদি (!_this->vulkan_config.loader_handle) {
        ফেরত SDL_SetError("Vulkan is not loaded");
    }
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    যদি (video_তথ্য_2->vulkan_xlib_xcb_library) {
        PFN_vkCreateXcbSurfaceKHR vkCreateXcbSurfaceKHR =
            (PFN_vkCreateXcbSurfaceKHR)vkGetInstanceProcAddr(instance,
                                                             "vkCreateXcbSurfaceKHR");
        VkXcbSurfaceCreateInfoKHR createInfo;
        Vk_ফলাফল ফলাফল;
        যদি (!vkCreateXcbSurfaceKHR) {
            ফেরত SDL_SetError(VK_KHR_XCB_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        }
        SDL_zero(createInfo);
        createInfo.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
        createInfo.connection = video_তথ্য_2->vulkan_XGetXCBConnection(video_তথ্য_2->display);
        যদি (!createInfo.connection) {
            ফেরত SDL_SetError("XGetXCBConnection failed");
        }
        createInfo.window = (xcb_window_t)window_তথ্য->xwindow;
        ফলাফল = vkCreateXcbSurfaceKHR(instance, &createInfo, allocator, surface);
        যদি (ফলাফল != VK_SUCCESS) {
            ফেরত SDL_SetError("vkCreateXcbSurfaceKHR failed: %s", SDL_Vulkan_Get_ফলাফল_String(ফলাফল));
        }
    } অন্যথা {
        PFN_vkCreateXlibSurfaceKHR vkCreateXlibSurfaceKHR =
            (PFN_vkCreateXlibSurfaceKHR)vkGetInstanceProcAddr(instance,
                                                              "vkCreateXlibSurfaceKHR");
        VkXlibSurfaceCreateInfoKHR createInfo;
        Vk_ফলাফল ফলাফল;
        যদি (!vkCreateXlibSurfaceKHR) {
            ফেরত SDL_SetError(VK_KHR_XLIB_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        }
        SDL_zero(createInfo);
        createInfo.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
        createInfo.dpy = video_তথ্য_2->display;
        createInfo.window = (xcb_window_t)window_তথ্য->xwindow;
        ফলাফল = vkCreateXlibSurfaceKHR(instance, &createInfo, allocator, surface);
        যদি (ফলাফল != VK_SUCCESS) {
            ফেরত SDL_SetError("vkCreateXlibSurfaceKHR failed: %s", SDL_Vulkan_Get_ফলাফল_String(ফলাফল));
        }
    }

    ফেরত true;  // success!
}

শূন্য X11_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                               VkInstance instance,
                               VkSurfaceKHR surface,
                               ধ্রুবক কাঠামো VkAllocationCallbacks *allocator)
{
    যদি (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_DestroySurface_Internal(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

bool X11_Vulkan_GetPresentationSupport(SDL_VideoDevice *_this,
                                           VkInstance instance,
                                           VkPhysicalDevice physicalDevice,
                                           Uint32 queue_Family_সূচক)
{
    SDL_Video_তথ্য *video_তথ্য_2 = _this->internal;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;
    ধ্রুবক অক্ষর *forced_visual_id;
    VisualID visualid;

    যদি (!_this->vulkan_config.loader_handle) {
        ফেরত SDL_SetError("Vulkan is not loaded");
    }
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;

    forced_visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_WINDOW_VISUALID);
    যদি (forced_visual_id) {
        visualid = SDL_strtol(forced_visual_id, ফাঁকা, 0);
    } অন্যথা {
        visualid = X11_XVisualIDFromVisual(DefaultVisual(video_তথ্য_2->display, DefaultScreen(video_তথ্য_2->display)));
    }

    যদি (video_তথ্য_2->vulkan_xlib_xcb_library) {
        PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR vkGetPhysicalDeviceXcbPresentationSupportKHR =
            (PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR)vkGetInstanceProcAddr(
                instance,
                "vkGetPhysicalDeviceXcbPresentationSupportKHR");

        যদি (!vkGetPhysicalDeviceXcbPresentationSupportKHR) {
            ফেরত SDL_SetError(VK_KHR_XCB_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        }

        ফেরত vkGetPhysicalDeviceXcbPresentationSupportKHR(physicalDevice,
                                                            queue_Family_সূচক,
                                                            video_তথ্য_2->vulkan_XGetXCBConnection(video_তথ্য_2->display),
                                                            visualid);
    } অন্যথা {
        PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR vkGetPhysicalDeviceXlibPresentationSupportKHR =
            (PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR)vkGetInstanceProcAddr(
                instance,
                "vkGetPhysicalDeviceXlibPresentationSupportKHR");

        যদি (!vkGetPhysicalDeviceXlibPresentationSupportKHR) {
            ফেরত SDL_SetError(VK_KHR_XLIB_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        }

        ফেরত vkGetPhysicalDeviceXlibPresentationSupportKHR(physicalDevice,
                                                             queue_Family_সূচক,
                                                             video_তথ্য_2->display,
                                                             visualid);
    }
}

#endif
