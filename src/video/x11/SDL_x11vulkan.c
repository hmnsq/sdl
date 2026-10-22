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
#ضمن "SDL_internal.h"

#إذا defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_X11)

#ضمن "../SDL_vulkan_internal.h"

#ضمن "SDL_x11video.h"

#ضمن "SDL_x11vulkan.h"

#ضمن <X11/Xlib.h>
// #include <xcb/xcb.h>

#جے_تعریف_شدہ SDL_PLATFORM_OPENBSD
#تعریف_کرو DEFAULT_VULKAN "libvulkan.so"
#تعریف_کرو DEFAULT_X11_XCB "libX11-xcb.so"
#وإلا
#تعریف_کرو DEFAULT_VULKAN "libvulkan.so.1"
#تعریف_کرو DEFAULT_X11_XCB "libX11-xcb.so.1"
#جے_انت

SDL_ELF_NOTE_DLOPEN(
    "x11-vulkan",
    "Support for vulkan on X11",
    SDL_ELF_NOTE_DLOPEN_ترجیح_SUGGESTED,
    DEFAULT_VULKAN
)

SDL_ELF_NOTE_DLOPEN(
    "x11-vulkan",
    "Support for vulkan on X11",
    SDL_ELF_NOTE_DLOPEN_ترجیح_SUGGESTED,
    DEFAULT_X11_XCB
)

/*
typedef uint32_t xcb_window_t;
typedef uint32_t xcb_visualid_t;
*/

bool X11_Vulkan_لدو_Library(SDL_VideoDevice *_this, ثابت حرف *رستہ)
{
    SDL_Video_انکڑے *video_انکڑے_2 = _this->اندرونی;
    VkExtensionProperties *extensions = عدم;
    Uint32 extension_گنتی = 0;
    bool hasSurfaceExtension = false;
    bool hasXlibSurfaceExtension = false;
    bool hasXCBSurfaceExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = عدم;
    Uint32 i;
    إذا (_this->vulkan_config.loader_handle) {
        أرجع SDL_سیٹ_Error("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    إذا (!رستہ) {
        رستہ = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }
    إذا (!رستہ) {
        رستہ = DEFAULT_VULKAN;
    }
    _this->vulkan_config.loader_handle = SDL_لدو_Object(رستہ);
    إذا (!_this->vulkan_config.loader_handle) {
        أرجع false;
    }
    SDL_strlcpy(_this->vulkan_config.loader_رستہ, رستہ, SDL_arraysize(_this->vulkan_config.loader_رستہ));
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)SDL_لدو_Function(
        _this->vulkan_config.loader_handle, "vkGetInstanceProcAddr");
    إذا (!vkGetInstanceProcAddr) {
        اذهب fail;
    }
    _this->vulkan_config.vkGetInstanceProcAddr = (فراغ *)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties =
        (فراغ *)((PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr)(
            VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties");
    إذا (!_this->vulkan_config.vkEnumerateInstanceExtensionProperties) {
        اذهب fail;
    }
    extensions = SDL_Vulkan_CreateInstanceExtensionsList(
        (PFN_vkEnumerateInstanceExtensionProperties)
            _this->vulkan_config.vkEnumerateInstanceExtensionProperties,
        &extension_گنتی);
    إذا (!extensions) {
        اذهب fail;
    }
    لكل (i = 0; i < extension_گنتی; i++) {
        إذا (SDL_strcmp(VK_KHR_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasSurfaceExtension = true;
        } وإلا إذا (SDL_strcmp(VK_KHR_XCB_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasXCBSurfaceExtension = true;
        } وإلا إذا (SDL_strcmp(VK_KHR_XLIB_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasXlibSurfaceExtension = true;
        }
    }
    SDL_free(extensions);
    إذا (!hasSurfaceExtension) {
        SDL_سیٹ_Error("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        اذهب fail;
    }
    إذا (hasXlibSurfaceExtension) {
        video_انکڑے_2->vulkan_xlib_xcb_library = عدم;
    } وإلا إذا (!hasXCBSurfaceExtension) {
        SDL_سیٹ_Error("Installed Vulkan doesn't implement either the " VK_KHR_XCB_SURFACE_EXTENSION_NAME " extension or the " VK_KHR_XLIB_SURFACE_EXTENSION_NAME " extension");
        اذهب fail;
    } وإلا {
        ثابت حرف *libX11XCBLibraryName = SDL_GetHint(SDL_HINT_X11_XCB_LIBRARY);
        إذا (!libX11XCBLibraryName || !*libX11XCBLibraryName) {
            libX11XCBLibraryName = DEFAULT_X11_XCB;
        }
        video_انکڑے_2->vulkan_xlib_xcb_library = SDL_لدو_Object(libX11XCBLibraryName);
        إذا (!video_انکڑے_2->vulkan_xlib_xcb_library) {
            اذهب fail;
        }
        video_انکڑے_2->vulkan_XGetXCBConnection =
            (PFN_XGetXCBConnection)SDL_لدو_Function(video_انکڑے_2->vulkan_xlib_xcb_library, "XGetXCBConnection");
        إذا (!video_انکڑے_2->vulkan_XGetXCBConnection) {
            SDL_UnloadObject(video_انکڑے_2->vulkan_xlib_xcb_library);
            اذهب fail;
        }
    }
    أرجع true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = عدم;
    أرجع false;
}

فراغ X11_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_Video_انکڑے *video_انکڑے_2 = _this->اندرونی;
    إذا (_this->vulkan_config.loader_handle) {
        إذا (video_انکڑے_2->vulkan_xlib_xcb_library) {
            SDL_UnloadObject(video_انکڑے_2->vulkan_xlib_xcb_library);
        }
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = عدم;
    }
}

حرف ثابت * ثابت *X11_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *گنتی)
{
    SDL_Video_انکڑے *video_انکڑے_2 = _this->اندرونی;
    إذا (video_انکڑے_2->vulkan_xlib_xcb_library) {
        ساكن ثابت حرف *ثابت extensionsForXCB[] = {
            VK_KHR_SURFACE_EXTENSION_NAME,
            VK_KHR_XCB_SURFACE_EXTENSION_NAME,
        };
        *گنتی = SDL_arraysize(extensionsForXCB);
        أرجع extensionsForXCB;
    } وإلا {
        ساكن ثابت حرف *ثابت extensionsForXlib[] = {
            VK_KHR_SURFACE_EXTENSION_NAME,
            VK_KHR_XLIB_SURFACE_EXTENSION_NAME,
        };
        *گنتی = SDL_arraysize(extensionsForXlib);
        أرجع extensionsForXlib;
    }
}

bool X11_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                             SDL_کھڑکی *کھڑکی,
                             VkInstance instance,
                             ثابت بنية Vk_ونڈ_Callbacks *allocator,
                             VkSurfaceKHR *surface)
{
    SDL_Video_انکڑے *video_انکڑے_2 = _this->اندرونی;
    SDL_کھڑکی_انکڑے *کھڑکی_انکڑے = کھڑکی->اندرونی;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;
    إذا (!_this->vulkan_config.loader_handle) {
        أرجع SDL_سیٹ_Error("Vulkan is not loaded");
    }
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    إذا (video_انکڑے_2->vulkan_xlib_xcb_library) {
        PFN_vkCreateXcbSurfaceKHR vkCreateXcbSurfaceKHR =
            (PFN_vkCreateXcbSurfaceKHR)vkGetInstanceProcAddr(instance,
                                                             "vkCreateXcbSurfaceKHR");
        VkXcbSurfaceCreateInfoKHR createInfo;
        Vk_نتیجہ نتیجہ;
        إذا (!vkCreateXcbSurfaceKHR) {
            أرجع SDL_سیٹ_Error(VK_KHR_XCB_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        }
        SDL_zero(createInfo);
        createInfo.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
        createInfo.connection = video_انکڑے_2->vulkan_XGetXCBConnection(video_انکڑے_2->display);
        إذا (!createInfo.connection) {
            أرجع SDL_سیٹ_Error("XGetXCBConnection failed");
        }
        createInfo.کھڑکی = (xcb_کھڑکی_t)کھڑکی_انکڑے->xwindow;
        نتیجہ = vkCreateXcbSurfaceKHR(instance, &createInfo, allocator, surface);
        إذا (نتیجہ != VK_SUCCESS) {
            أرجع SDL_سیٹ_Error("vkCreateXcbSurfaceKHR failed: %s", SDL_Vulkan_Get_نتیجہ_String(نتیجہ));
        }
    } وإلا {
        PFN_vkCreateXlibSurfaceKHR vkCreateXlibSurfaceKHR =
            (PFN_vkCreateXlibSurfaceKHR)vkGetInstanceProcAddr(instance,
                                                              "vkCreateXlibSurfaceKHR");
        VkXlibSurfaceCreateInfoKHR createInfo;
        Vk_نتیجہ نتیجہ;
        إذا (!vkCreateXlibSurfaceKHR) {
            أرجع SDL_سیٹ_Error(VK_KHR_XLIB_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        }
        SDL_zero(createInfo);
        createInfo.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
        createInfo.dpy = video_انکڑے_2->display;
        createInfo.کھڑکی = (xcb_کھڑکی_t)کھڑکی_انکڑے->xwindow;
        نتیجہ = vkCreateXlibSurfaceKHR(instance, &createInfo, allocator, surface);
        إذا (نتیجہ != VK_SUCCESS) {
            أرجع SDL_سیٹ_Error("vkCreateXlibSurfaceKHR failed: %s", SDL_Vulkan_Get_نتیجہ_String(نتیجہ));
        }
    }

    أرجع true;  // success!
}

فراغ X11_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                               VkInstance instance,
                               VkSurfaceKHR surface,
                               ثابت بنية Vk_ونڈ_Callbacks *allocator)
{
    إذا (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_Destroy_Surface_اندرونی(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

bool X11_Vulkan_GetPresentationSupport(SDL_VideoDevice *_this,
                                           VkInstance instance,
                                           VkPhysicalDevice physicalDevice,
                                           Uint32 قطار_Family_اشاریہ)
{
    SDL_Video_انکڑے *video_انکڑے_2 = _this->اندرونی;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;
    ثابت حرف *forced_visual_id;
    VisualID visualid;

    إذا (!_this->vulkan_config.loader_handle) {
        أرجع SDL_سیٹ_Error("Vulkan is not loaded");
    }
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;

    forced_visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_کھڑکی_VISUALID);
    إذا (forced_visual_id) {
        visualid = SDL_strtol(forced_visual_id, عدم, 0);
    } وإلا {
        visualid = X11_XVisualIDFromVisual(DefaultVisual(video_انکڑے_2->display, DefaultScreen(video_انکڑے_2->display)));
    }

    إذا (video_انکڑے_2->vulkan_xlib_xcb_library) {
        PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR vkGetPhysicalDeviceXcbPresentationSupportKHR =
            (PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR)vkGetInstanceProcAddr(
                instance,
                "vkGetPhysicalDeviceXcbPresentationSupportKHR");

        إذا (!vkGetPhysicalDeviceXcbPresentationSupportKHR) {
            أرجع SDL_سیٹ_Error(VK_KHR_XCB_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        }

        أرجع vkGetPhysicalDeviceXcbPresentationSupportKHR(physicalDevice,
                                                            قطار_Family_اشاریہ,
                                                            video_انکڑے_2->vulkan_XGetXCBConnection(video_انکڑے_2->display),
                                                            visualid);
    } وإلا {
        PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR vkGetPhysicalDeviceXlibPresentationSupportKHR =
            (PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR)vkGetInstanceProcAddr(
                instance,
                "vkGetPhysicalDeviceXlibPresentationSupportKHR");

        إذا (!vkGetPhysicalDeviceXlibPresentationSupportKHR) {
            أرجع SDL_سیٹ_Error(VK_KHR_XLIB_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        }

        أرجع vkGetPhysicalDeviceXlibPresentationSupportKHR(physicalDevice,
                                                             قطار_Family_اشاریہ,
                                                             video_انکڑے_2->display,
                                                             visualid);
    }
}

#جے_انت
