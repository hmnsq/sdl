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

#यदि defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_X11)

#अन्तर्भाव "../SDL_vulkan_internal.h"

#अन्तर्भाव "SDL_x11video.h"

#अन्तर्भाव "SDL_x11vulkan.h"

#अन्तर्भाव <X11/Xlib.h>
// #include <xcb/xcb.h>

#यदि_परिभाषितम् SDL_PLATFORM_OPENBSD
#परिभाषय DEFAULT_VULKAN "libvulkan.so"
#परिभाषय DEFAULT_X11_XCB "libX11-xcb.so"
#अन्यथा
#परिभाषय DEFAULT_VULKAN "libvulkan.so.1"
#परिभाषय DEFAULT_X11_XCB "libX11-xcb.so.1"
#यदि_अन्तः

SDL_ELF_NOTE_DLOPEN(
    "x11-vulkan",
    "Support for vulkan on X11",
    SDL_ELF_NOTE_DLOPEN_प्राथमिकता_SUGGESTED,
    DEFAULT_VULKAN
)

SDL_ELF_NOTE_DLOPEN(
    "x11-vulkan",
    "Support for vulkan on X11",
    SDL_ELF_NOTE_DLOPEN_प्राथमिकता_SUGGESTED,
    DEFAULT_X11_XCB
)

/*
typedef uint32_t xcb_window_t;
typedef uint32_t xcb_visualid_t;
*/

bool X11_Vulkan_आरोपय_Library(SDL_VideoDevice *_this, ध्रुव वर्ण *मार्गः)
{
    SDL_Video_दत्त *video_दत्त_2 = _this->आन्तरिकम्;
    VkExtensionProperties *extensions = रिक्त;
    Uint32 extension_गणनम् = 0;
    bool hasSurfaceExtension = false;
    bool hasXlibSurfaceExtension = false;
    bool hasXCBSurfaceExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = रिक्त;
    Uint32 i;
    यदि (_this->vulkan_config.loader_handle) {
        प्रत्यागम SDL_समुच्चयः_Error("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    यदि (!मार्गः) {
        मार्गः = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }
    यदि (!मार्गः) {
        मार्गः = DEFAULT_VULKAN;
    }
    _this->vulkan_config.loader_handle = SDL_आरोपय_Object(मार्गः);
    यदि (!_this->vulkan_config.loader_handle) {
        प्रत्यागम false;
    }
    SDL_strlcpy(_this->vulkan_config.loader_मार्गः, मार्गः, SDL_arraysize(_this->vulkan_config.loader_मार्गः));
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)SDL_आरोपय_Function(
        _this->vulkan_config.loader_handle, "vkGetInstanceProcAddr");
    यदि (!vkGetInstanceProcAddr) {
        गच्छ fail;
    }
    _this->vulkan_config.vkGetInstanceProcAddr = (शून्य *)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties =
        (शून्य *)((PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr)(
            VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties");
    यदि (!_this->vulkan_config.vkEnumerateInstanceExtensionProperties) {
        गच्छ fail;
    }
    extensions = SDL_Vulkan_CreateInstanceExtensionsList(
        (PFN_vkEnumerateInstanceExtensionProperties)
            _this->vulkan_config.vkEnumerateInstanceExtensionProperties,
        &extension_गणनम्);
    यदि (!extensions) {
        गच्छ fail;
    }
    प्रति (i = 0; i < extension_गणनम्; i++) {
        यदि (SDL_strcmp(VK_KHR_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasSurfaceExtension = true;
        } अन्यथा यदि (SDL_strcmp(VK_KHR_XCB_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasXCBSurfaceExtension = true;
        } अन्यथा यदि (SDL_strcmp(VK_KHR_XLIB_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasXlibSurfaceExtension = true;
        }
    }
    SDL_free(extensions);
    यदि (!hasSurfaceExtension) {
        SDL_समुच्चयः_Error("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        गच्छ fail;
    }
    यदि (hasXlibSurfaceExtension) {
        video_दत्त_2->vulkan_xlib_xcb_library = रिक्त;
    } अन्यथा यदि (!hasXCBSurfaceExtension) {
        SDL_समुच्चयः_Error("Installed Vulkan doesn't implement either the " VK_KHR_XCB_SURFACE_EXTENSION_NAME " extension or the " VK_KHR_XLIB_SURFACE_EXTENSION_NAME " extension");
        गच्छ fail;
    } अन्यथा {
        ध्रुव वर्ण *libX11XCBLibraryName = SDL_GetHint(SDL_HINT_X11_XCB_LIBRARY);
        यदि (!libX11XCBLibraryName || !*libX11XCBLibraryName) {
            libX11XCBLibraryName = DEFAULT_X11_XCB;
        }
        video_दत्त_2->vulkan_xlib_xcb_library = SDL_आरोपय_Object(libX11XCBLibraryName);
        यदि (!video_दत्त_2->vulkan_xlib_xcb_library) {
            गच्छ fail;
        }
        video_दत्त_2->vulkan_XGetXCBConnection =
            (PFN_XGetXCBConnection)SDL_आरोपय_Function(video_दत्त_2->vulkan_xlib_xcb_library, "XGetXCBConnection");
        यदि (!video_दत्त_2->vulkan_XGetXCBConnection) {
            SDL_UnloadObject(video_दत्त_2->vulkan_xlib_xcb_library);
            गच्छ fail;
        }
    }
    प्रत्यागम true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = रिक्त;
    प्रत्यागम false;
}

शून्य X11_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_Video_दत्त *video_दत्त_2 = _this->आन्तरिकम्;
    यदि (_this->vulkan_config.loader_handle) {
        यदि (video_दत्त_2->vulkan_xlib_xcb_library) {
            SDL_UnloadObject(video_दत्त_2->vulkan_xlib_xcb_library);
        }
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = रिक्त;
    }
}

वर्ण ध्रुव * ध्रुव *X11_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *गणनम्)
{
    SDL_Video_दत्त *video_दत्त_2 = _this->आन्तरिकम्;
    यदि (video_दत्त_2->vulkan_xlib_xcb_library) {
        स्थिर ध्रुव वर्ण *ध्रुव extensionsForXCB[] = {
            VK_KHR_SURFACE_EXTENSION_NAME,
            VK_KHR_XCB_SURFACE_EXTENSION_NAME,
        };
        *गणनम् = SDL_arraysize(extensionsForXCB);
        प्रत्यागम extensionsForXCB;
    } अन्यथा {
        स्थिर ध्रुव वर्ण *ध्रुव extensionsForXlib[] = {
            VK_KHR_SURFACE_EXTENSION_NAME,
            VK_KHR_XLIB_SURFACE_EXTENSION_NAME,
        };
        *गणनम् = SDL_arraysize(extensionsForXlib);
        प्रत्यागम extensionsForXlib;
    }
}

bool X11_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                             SDL_गवाक्षः *गवाक्षः,
                             VkInstance instance,
                             ध्रुव संरचना Vk_आवण्टनम्_Callbacks *allocator,
                             VkSurfaceKHR *surface)
{
    SDL_Video_दत्त *video_दत्त_2 = _this->आन्तरिकम्;
    SDL_गवाक्षः_दत्त *गवाक्षः_दत्त = गवाक्षः->आन्तरिकम्;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;
    यदि (!_this->vulkan_config.loader_handle) {
        प्रत्यागम SDL_समुच्चयः_Error("Vulkan is not loaded");
    }
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    यदि (video_दत्त_2->vulkan_xlib_xcb_library) {
        PFN_vkCreateXcbSurfaceKHR vkCreateXcbSurfaceKHR =
            (PFN_vkCreateXcbSurfaceKHR)vkGetInstanceProcAddr(instance,
                                                             "vkCreateXcbSurfaceKHR");
        VkXcbSurfaceCreateInfoKHR createInfo;
        Vk_परिणाम परिणाम;
        यदि (!vkCreateXcbSurfaceKHR) {
            प्रत्यागम SDL_समुच्चयः_Error(VK_KHR_XCB_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        }
        SDL_zero(createInfo);
        createInfo.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
        createInfo.connection = video_दत्त_2->vulkan_XGetXCBConnection(video_दत्त_2->display);
        यदि (!createInfo.connection) {
            प्रत्यागम SDL_समुच्चयः_Error("XGetXCBConnection failed");
        }
        createInfo.गवाक्षः = (xcb_गवाक्षः_t)गवाक्षः_दत्त->xwindow;
        परिणाम = vkCreateXcbSurfaceKHR(instance, &createInfo, allocator, surface);
        यदि (परिणाम != VK_SUCCESS) {
            प्रत्यागम SDL_समुच्चयः_Error("vkCreateXcbSurfaceKHR failed: %s", SDL_Vulkan_Get_परिणाम_String(परिणाम));
        }
    } अन्यथा {
        PFN_vkCreateXlibSurfaceKHR vkCreateXlibSurfaceKHR =
            (PFN_vkCreateXlibSurfaceKHR)vkGetInstanceProcAddr(instance,
                                                              "vkCreateXlibSurfaceKHR");
        VkXlibSurfaceCreateInfoKHR createInfo;
        Vk_परिणाम परिणाम;
        यदि (!vkCreateXlibSurfaceKHR) {
            प्रत्यागम SDL_समुच्चयः_Error(VK_KHR_XLIB_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        }
        SDL_zero(createInfo);
        createInfo.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
        createInfo.dpy = video_दत्त_2->display;
        createInfo.गवाक्षः = (xcb_गवाक्षः_t)गवाक्षः_दत्त->xwindow;
        परिणाम = vkCreateXlibSurfaceKHR(instance, &createInfo, allocator, surface);
        यदि (परिणाम != VK_SUCCESS) {
            प्रत्यागम SDL_समुच्चयः_Error("vkCreateXlibSurfaceKHR failed: %s", SDL_Vulkan_Get_परिणाम_String(परिणाम));
        }
    }

    प्रत्यागम true;  // success!
}

शून्य X11_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                               VkInstance instance,
                               VkSurfaceKHR surface,
                               ध्रुव संरचना Vk_आवण्टनम्_Callbacks *allocator)
{
    यदि (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_Destroy_Surface_आन्तरिकम्(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

bool X11_Vulkan_GetPresentationSupport(SDL_VideoDevice *_this,
                                           VkInstance instance,
                                           VkPhysicalDevice physicalDevice,
                                           Uint32 queue_Family_सूचकांक)
{
    SDL_Video_दत्त *video_दत्त_2 = _this->आन्तरिकम्;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;
    ध्रुव वर्ण *forced_visual_id;
    VisualID visualid;

    यदि (!_this->vulkan_config.loader_handle) {
        प्रत्यागम SDL_समुच्चयः_Error("Vulkan is not loaded");
    }
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;

    forced_visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_गवाक्षः_VISUALID);
    यदि (forced_visual_id) {
        visualid = SDL_strtol(forced_visual_id, रिक्त, 0);
    } अन्यथा {
        visualid = X11_XVisualIDFromVisual(DefaultVisual(video_दत्त_2->display, DefaultScreen(video_दत्त_2->display)));
    }

    यदि (video_दत्त_2->vulkan_xlib_xcb_library) {
        PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR vkGetPhysicalDeviceXcbPresentationSupportKHR =
            (PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR)vkGetInstanceProcAddr(
                instance,
                "vkGetPhysicalDeviceXcbPresentationSupportKHR");

        यदि (!vkGetPhysicalDeviceXcbPresentationSupportKHR) {
            प्रत्यागम SDL_समुच्चयः_Error(VK_KHR_XCB_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        }

        प्रत्यागम vkGetPhysicalDeviceXcbPresentationSupportKHR(physicalDevice,
                                                            queue_Family_सूचकांक,
                                                            video_दत्त_2->vulkan_XGetXCBConnection(video_दत्त_2->display),
                                                            visualid);
    } अन्यथा {
        PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR vkGetPhysicalDeviceXlibPresentationSupportKHR =
            (PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR)vkGetInstanceProcAddr(
                instance,
                "vkGetPhysicalDeviceXlibPresentationSupportKHR");

        यदि (!vkGetPhysicalDeviceXlibPresentationSupportKHR) {
            प्रत्यागम SDL_समुच्चयः_Error(VK_KHR_XLIB_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        }

        प्रत्यागम vkGetPhysicalDeviceXlibPresentationSupportKHR(physicalDevice,
                                                             queue_Family_सूचकांक,
                                                             video_दत्त_2->display,
                                                             visualid);
    }
}

#यदि_अन्तः
