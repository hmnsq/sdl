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

#अगर defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_X11)

#समावेश "../SDL_vulkan_internal.h"

#समावेश "SDL_x11video.h"

#समावेश "SDL_x11vulkan.h"

#समावेश <X11/Xlib.h>
// #include <xcb/xcb.h>

#अगर_घोषित SDL_PLATFORM_OPENBSD
#घोषणा DEFAULT_VULKAN "libvulkan.so"
#घोषणा DEFAULT_X11_XCB "libX11-xcb.so"
#अन्यथा
#घोषणा DEFAULT_VULKAN "libvulkan.so.1"
#घोषणा DEFAULT_X11_XCB "libX11-xcb.so.1"
#पूर्ण_अगर

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

bool X11_Vulkan_LoadLibrary(SDL_VideoDevice *_this, स्थिर अक्षर *path)
{
    SDL_Video_तथ्य *video_तथ्य_2 = _this->internal;
    VkExtensionProperties *extensions = शून्य;
    Uint32 extension_गिनती = 0;
    bool hasSurfaceExtension = false;
    bool hasXlibSurfaceExtension = false;
    bool hasXCBSurfaceExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = शून्य;
    Uint32 i;
    अगर (_this->vulkan_config.loader_handle) {
        वापस SDL_SetError("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    अगर (!path) {
        path = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }
    अगर (!path) {
        path = DEFAULT_VULKAN;
    }
    _this->vulkan_config.loader_handle = SDL_LoadObject(path);
    अगर (!_this->vulkan_config.loader_handle) {
        वापस false;
    }
    SDL_strlcpy(_this->vulkan_config.loader_path, path, SDL_arraysize(_this->vulkan_config.loader_path));
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)SDL_LoadFunction(
        _this->vulkan_config.loader_handle, "vkGetInstanceProcAddr");
    अगर (!vkGetInstanceProcAddr) {
        जाओ fail;
    }
    _this->vulkan_config.vkGetInstanceProcAddr = (व्योम *)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties =
        (व्योम *)((PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr)(
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
        } अन्यथा अगर (SDL_strcmp(VK_KHR_XCB_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasXCBSurfaceExtension = true;
        } अन्यथा अगर (SDL_strcmp(VK_KHR_XLIB_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasXlibSurfaceExtension = true;
        }
    }
    SDL_free(extensions);
    अगर (!hasSurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        जाओ fail;
    }
    अगर (hasXlibSurfaceExtension) {
        video_तथ्य_2->vulkan_xlib_xcb_library = शून्य;
    } अन्यथा अगर (!hasXCBSurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement either the " VK_KHR_XCB_SURFACE_EXTENSION_NAME " extension or the " VK_KHR_XLIB_SURFACE_EXTENSION_NAME " extension");
        जाओ fail;
    } अन्यथा {
        स्थिर अक्षर *libX11XCBLibraryName = SDL_GetHint(SDL_HINT_X11_XCB_LIBRARY);
        अगर (!libX11XCBLibraryName || !*libX11XCBLibraryName) {
            libX11XCBLibraryName = DEFAULT_X11_XCB;
        }
        video_तथ्य_2->vulkan_xlib_xcb_library = SDL_LoadObject(libX11XCBLibraryName);
        अगर (!video_तथ्य_2->vulkan_xlib_xcb_library) {
            जाओ fail;
        }
        video_तथ्य_2->vulkan_XGetXCBConnection =
            (PFN_XGetXCBConnection)SDL_LoadFunction(video_तथ्य_2->vulkan_xlib_xcb_library, "XGetXCBConnection");
        अगर (!video_तथ्य_2->vulkan_XGetXCBConnection) {
            SDL_UnloadObject(video_तथ्य_2->vulkan_xlib_xcb_library);
            जाओ fail;
        }
    }
    वापस true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = शून्य;
    वापस false;
}

व्योम X11_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_Video_तथ्य *video_तथ्य_2 = _this->internal;
    अगर (_this->vulkan_config.loader_handle) {
        अगर (video_तथ्य_2->vulkan_xlib_xcb_library) {
            SDL_UnloadObject(video_तथ्य_2->vulkan_xlib_xcb_library);
        }
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = शून्य;
    }
}

अक्षर स्थिर * स्थिर *X11_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *गिनती)
{
    SDL_Video_तथ्य *video_तथ्य_2 = _this->internal;
    अगर (video_तथ्य_2->vulkan_xlib_xcb_library) {
        अटल स्थिर अक्षर *स्थिर extensionsForXCB[] = {
            VK_KHR_SURFACE_EXTENSION_NAME,
            VK_KHR_XCB_SURFACE_EXTENSION_NAME,
        };
        *गिनती = SDL_arraysize(extensionsForXCB);
        वापस extensionsForXCB;
    } अन्यथा {
        अटल स्थिर अक्षर *स्थिर extensionsForXlib[] = {
            VK_KHR_SURFACE_EXTENSION_NAME,
            VK_KHR_XLIB_SURFACE_EXTENSION_NAME,
        };
        *गिनती = SDL_arraysize(extensionsForXlib);
        वापस extensionsForXlib;
    }
}

bool X11_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                             SDL_Window *window,
                             VkInstance instance,
                             स्थिर काष्ठा VkAllocationCallbacks *allocator,
                             VkSurfaceKHR *surface)
{
    SDL_Video_तथ्य *video_तथ्य_2 = _this->internal;
    SDL_Window_तथ्य *window_तथ्य = window->internal;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;
    अगर (!_this->vulkan_config.loader_handle) {
        वापस SDL_SetError("Vulkan is not loaded");
    }
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    अगर (video_तथ्य_2->vulkan_xlib_xcb_library) {
        PFN_vkCreateXcbSurfaceKHR vkCreateXcbSurfaceKHR =
            (PFN_vkCreateXcbSurfaceKHR)vkGetInstanceProcAddr(instance,
                                                             "vkCreateXcbSurfaceKHR");
        VkXcbSurfaceCreateInfoKHR createInfo;
        Vk_परिणाम परिणाम;
        अगर (!vkCreateXcbSurfaceKHR) {
            वापस SDL_SetError(VK_KHR_XCB_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        }
        SDL_zero(createInfo);
        createInfo.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
        createInfo.connection = video_तथ्य_2->vulkan_XGetXCBConnection(video_तथ्य_2->display);
        अगर (!createInfo.connection) {
            वापस SDL_SetError("XGetXCBConnection failed");
        }
        createInfo.window = (xcb_window_t)window_तथ्य->xwindow;
        परिणाम = vkCreateXcbSurfaceKHR(instance, &createInfo, allocator, surface);
        अगर (परिणाम != VK_SUCCESS) {
            वापस SDL_SetError("vkCreateXcbSurfaceKHR failed: %s", SDL_Vulkan_Get_परिणाम_String(परिणाम));
        }
    } अन्यथा {
        PFN_vkCreateXlibSurfaceKHR vkCreateXlibSurfaceKHR =
            (PFN_vkCreateXlibSurfaceKHR)vkGetInstanceProcAddr(instance,
                                                              "vkCreateXlibSurfaceKHR");
        VkXlibSurfaceCreateInfoKHR createInfo;
        Vk_परिणाम परिणाम;
        अगर (!vkCreateXlibSurfaceKHR) {
            वापस SDL_SetError(VK_KHR_XLIB_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        }
        SDL_zero(createInfo);
        createInfo.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
        createInfo.dpy = video_तथ्य_2->display;
        createInfo.window = (xcb_window_t)window_तथ्य->xwindow;
        परिणाम = vkCreateXlibSurfaceKHR(instance, &createInfo, allocator, surface);
        अगर (परिणाम != VK_SUCCESS) {
            वापस SDL_SetError("vkCreateXlibSurfaceKHR failed: %s", SDL_Vulkan_Get_परिणाम_String(परिणाम));
        }
    }

    वापस true;  // success!
}

व्योम X11_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                               VkInstance instance,
                               VkSurfaceKHR surface,
                               स्थिर काष्ठा VkAllocationCallbacks *allocator)
{
    अगर (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_DestroySurface_Internal(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

bool X11_Vulkan_GetPresentationSupport(SDL_VideoDevice *_this,
                                           VkInstance instance,
                                           VkPhysicalDevice physicalDevice,
                                           Uint32 queue_Family_सूचकांक)
{
    SDL_Video_तथ्य *video_तथ्य_2 = _this->internal;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;
    स्थिर अक्षर *forced_visual_id;
    VisualID visualid;

    अगर (!_this->vulkan_config.loader_handle) {
        वापस SDL_SetError("Vulkan is not loaded");
    }
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;

    forced_visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_WINDOW_VISUALID);
    अगर (forced_visual_id) {
        visualid = SDL_strtol(forced_visual_id, शून्य, 0);
    } अन्यथा {
        visualid = X11_XVisualIDFromVisual(DefaultVisual(video_तथ्य_2->display, DefaultScreen(video_तथ्य_2->display)));
    }

    अगर (video_तथ्य_2->vulkan_xlib_xcb_library) {
        PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR vkGetPhysicalDeviceXcbPresentationSupportKHR =
            (PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR)vkGetInstanceProcAddr(
                instance,
                "vkGetPhysicalDeviceXcbPresentationSupportKHR");

        अगर (!vkGetPhysicalDeviceXcbPresentationSupportKHR) {
            वापस SDL_SetError(VK_KHR_XCB_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        }

        वापस vkGetPhysicalDeviceXcbPresentationSupportKHR(physicalDevice,
                                                            queue_Family_सूचकांक,
                                                            video_तथ्य_2->vulkan_XGetXCBConnection(video_तथ्य_2->display),
                                                            visualid);
    } अन्यथा {
        PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR vkGetPhysicalDeviceXlibPresentationSupportKHR =
            (PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR)vkGetInstanceProcAddr(
                instance,
                "vkGetPhysicalDeviceXlibPresentationSupportKHR");

        अगर (!vkGetPhysicalDeviceXlibPresentationSupportKHR) {
            वापस SDL_SetError(VK_KHR_XLIB_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        }

        वापस vkGetPhysicalDeviceXlibPresentationSupportKHR(physicalDevice,
                                                             queue_Family_सूचकांक,
                                                             video_तथ्य_2->display,
                                                             visualid);
    }
}

#पूर्ण_अगर
