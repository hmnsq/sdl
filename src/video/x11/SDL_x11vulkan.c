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

#اگر_تعریف_شدہ SDL_PLATFORM_OPENBSD
#تعریف_کرو DEFAULT_VULKAN "libvulkan.so"
#تعریف_کرو DEFAULT_X11_XCB "libX11-xcb.so"
#ورنہ
#تعریف_کرو DEFAULT_VULKAN "libvulkan.so.1"
#تعریف_کرو DEFAULT_X11_XCB "libX11-xcb.so.1"
#اگر_ختم

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

bool X11_Vulkan_بھرو_Library(SDL_VideoDevice *_this, ثابت حرف *راستہ)
{
    SDL_Video_ڈیٹا *video_ڈیٹا_2 = _this->اندرونی_2;
    VkExtensionProperties *extensions = تہی;
    Uint32 extension_گنتی = 0;
    bool hasSurfaceExtension = false;
    bool hasXlibSurfaceExtension = false;
    bool hasXCBSurfaceExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = تہی;
    Uint32 i;
    اگر (_this->vulkan_config.loader_handle) {
        واپس SDL_سیٹ_Error("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    اگر (!راستہ) {
        راستہ = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }
    اگر (!راستہ) {
        راستہ = DEFAULT_VULKAN;
    }
    _this->vulkan_config.loader_handle = SDL_بھرو_Object(راستہ);
    اگر (!_this->vulkan_config.loader_handle) {
        واپس false;
    }
    SDL_strlcpy(_this->vulkan_config.loader_راستہ, راستہ, SDL_arraysize(_this->vulkan_config.loader_راستہ));
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)SDL_بھرو_Function(
        _this->vulkan_config.loader_handle, "vkGetInstanceProcAddr");
    اگر (!vkGetInstanceProcAddr) {
        جاؤ fail;
    }
    _this->vulkan_config.vkGetInstanceProcAddr = (خالی *)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties =
        (خالی *)((PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr)(
            VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties");
    اگر (!_this->vulkan_config.vkEnumerateInstanceExtensionProperties) {
        جاؤ fail;
    }
    extensions = SDL_Vulkan_CreateInstanceExtensionsList(
        (PFN_vkEnumerateInstanceExtensionProperties)
            _this->vulkan_config.vkEnumerateInstanceExtensionProperties,
        &extension_گنتی);
    اگر (!extensions) {
        جاؤ fail;
    }
    برائے (i = 0; i < extension_گنتی; i++) {
        اگر (SDL_strcmp(VK_KHR_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasSurfaceExtension = true;
        } ورنہ اگر (SDL_strcmp(VK_KHR_XCB_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasXCBSurfaceExtension = true;
        } ورنہ اگر (SDL_strcmp(VK_KHR_XLIB_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasXlibSurfaceExtension = true;
        }
    }
    SDL_free(extensions);
    اگر (!hasSurfaceExtension) {
        SDL_سیٹ_Error("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        جاؤ fail;
    }
    اگر (hasXlibSurfaceExtension) {
        video_ڈیٹا_2->vulkan_xlib_xcb_library = تہی;
    } ورنہ اگر (!hasXCBSurfaceExtension) {
        SDL_سیٹ_Error("Installed Vulkan doesn't implement either the " VK_KHR_XCB_SURFACE_EXTENSION_NAME " extension or the " VK_KHR_XLIB_SURFACE_EXTENSION_NAME " extension");
        جاؤ fail;
    } ورنہ {
        ثابت حرف *libX11XCBLibraryName = SDL_GetHint(SDL_HINT_X11_XCB_LIBRARY);
        اگر (!libX11XCBLibraryName || !*libX11XCBLibraryName) {
            libX11XCBLibraryName = DEFAULT_X11_XCB;
        }
        video_ڈیٹا_2->vulkan_xlib_xcb_library = SDL_بھرو_Object(libX11XCBLibraryName);
        اگر (!video_ڈیٹا_2->vulkan_xlib_xcb_library) {
            جاؤ fail;
        }
        video_ڈیٹا_2->vulkan_XGetXCBConnection =
            (PFN_XGetXCBConnection)SDL_بھرو_Function(video_ڈیٹا_2->vulkan_xlib_xcb_library, "XGetXCBConnection");
        اگر (!video_ڈیٹا_2->vulkan_XGetXCBConnection) {
            SDL_UnloadObject(video_ڈیٹا_2->vulkan_xlib_xcb_library);
            جاؤ fail;
        }
    }
    واپس true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = تہی;
    واپس false;
}

خالی X11_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_Video_ڈیٹا *video_ڈیٹا_2 = _this->اندرونی_2;
    اگر (_this->vulkan_config.loader_handle) {
        اگر (video_ڈیٹا_2->vulkan_xlib_xcb_library) {
            SDL_UnloadObject(video_ڈیٹا_2->vulkan_xlib_xcb_library);
        }
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = تہی;
    }
}

حرف ثابت * ثابت *X11_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *گنتی)
{
    SDL_Video_ڈیٹا *video_ڈیٹا_2 = _this->اندرونی_2;
    اگر (video_ڈیٹا_2->vulkan_xlib_xcb_library) {
        ساکن ثابت حرف *ثابت extensionsForXCB[] = {
            VK_KHR_SURFACE_EXTENSION_NAME,
            VK_KHR_XCB_SURFACE_EXTENSION_NAME,
        };
        *گنتی = SDL_arraysize(extensionsForXCB);
        واپس extensionsForXCB;
    } ورنہ {
        ساکن ثابت حرف *ثابت extensionsForXlib[] = {
            VK_KHR_SURFACE_EXTENSION_NAME,
            VK_KHR_XLIB_SURFACE_EXTENSION_NAME,
        };
        *گنتی = SDL_arraysize(extensionsForXlib);
        واپس extensionsForXlib;
    }
}

bool X11_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                             SDL_کھڑکی *کھڑکی,
                             VkInstance instance,
                             ثابت ساخت Vk_تخصیص_Callbacks *allocator,
                             VkSurfaceKHR *surface)
{
    SDL_Video_ڈیٹا *video_ڈیٹا_2 = _this->اندرونی_2;
    SDL_کھڑکی_ڈیٹا *کھڑکی_ڈیٹا = کھڑکی->اندرونی_2;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;
    اگر (!_this->vulkan_config.loader_handle) {
        واپس SDL_سیٹ_Error("Vulkan is not loaded");
    }
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    اگر (video_ڈیٹا_2->vulkan_xlib_xcb_library) {
        PFN_vkCreateXcbSurfaceKHR vkCreateXcbSurfaceKHR =
            (PFN_vkCreateXcbSurfaceKHR)vkGetInstanceProcAddr(instance,
                                                             "vkCreateXcbSurfaceKHR");
        VkXcbSurfaceCreateInfoKHR createInfo;
        Vk_نتیجہ نتیجہ;
        اگر (!vkCreateXcbSurfaceKHR) {
            واپس SDL_سیٹ_Error(VK_KHR_XCB_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        }
        SDL_zero(createInfo);
        createInfo.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
        createInfo.connection = video_ڈیٹا_2->vulkan_XGetXCBConnection(video_ڈیٹا_2->display);
        اگر (!createInfo.connection) {
            واپس SDL_سیٹ_Error("XGetXCBConnection failed");
        }
        createInfo.کھڑکی = (xcb_کھڑکی_t)کھڑکی_ڈیٹا->xwindow;
        نتیجہ = vkCreateXcbSurfaceKHR(instance, &createInfo, allocator, surface);
        اگر (نتیجہ != VK_SUCCESS) {
            واپس SDL_سیٹ_Error("vkCreateXcbSurfaceKHR failed: %s", SDL_Vulkan_Get_نتیجہ_String(نتیجہ));
        }
    } ورنہ {
        PFN_vkCreateXlibSurfaceKHR vkCreateXlibSurfaceKHR =
            (PFN_vkCreateXlibSurfaceKHR)vkGetInstanceProcAddr(instance,
                                                              "vkCreateXlibSurfaceKHR");
        VkXlibSurfaceCreateInfoKHR createInfo;
        Vk_نتیجہ نتیجہ;
        اگر (!vkCreateXlibSurfaceKHR) {
            واپس SDL_سیٹ_Error(VK_KHR_XLIB_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        }
        SDL_zero(createInfo);
        createInfo.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
        createInfo.dpy = video_ڈیٹا_2->display;
        createInfo.کھڑکی = (xcb_کھڑکی_t)کھڑکی_ڈیٹا->xwindow;
        نتیجہ = vkCreateXlibSurfaceKHR(instance, &createInfo, allocator, surface);
        اگر (نتیجہ != VK_SUCCESS) {
            واپس SDL_سیٹ_Error("vkCreateXlibSurfaceKHR failed: %s", SDL_Vulkan_Get_نتیجہ_String(نتیجہ));
        }
    }

    واپس true;  // success!
}

خالی X11_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                               VkInstance instance,
                               VkSurfaceKHR surface,
                               ثابت ساخت Vk_تخصیص_Callbacks *allocator)
{
    اگر (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_Destroy_Surface_اندرونی(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

bool X11_Vulkan_GetPresentationSupport(SDL_VideoDevice *_this,
                                           VkInstance instance,
                                           VkPhysicalDevice physicalDevice,
                                           Uint32 قطار_Family_اشاریہ)
{
    SDL_Video_ڈیٹا *video_ڈیٹا_2 = _this->اندرونی_2;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;
    ثابت حرف *forced_visual_id;
    VisualID visualid;

    اگر (!_this->vulkan_config.loader_handle) {
        واپس SDL_سیٹ_Error("Vulkan is not loaded");
    }
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;

    forced_visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_کھڑکی_VISUALID);
    اگر (forced_visual_id) {
        visualid = SDL_strtol(forced_visual_id, تہی, 0);
    } ورنہ {
        visualid = X11_XVisualIDFromVisual(DefaultVisual(video_ڈیٹا_2->display, DefaultScreen(video_ڈیٹا_2->display)));
    }

    اگر (video_ڈیٹا_2->vulkan_xlib_xcb_library) {
        PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR vkGetPhysicalDeviceXcbPresentationSupportKHR =
            (PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR)vkGetInstanceProcAddr(
                instance,
                "vkGetPhysicalDeviceXcbPresentationSupportKHR");

        اگر (!vkGetPhysicalDeviceXcbPresentationSupportKHR) {
            واپس SDL_سیٹ_Error(VK_KHR_XCB_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        }

        واپس vkGetPhysicalDeviceXcbPresentationSupportKHR(physicalDevice,
                                                            قطار_Family_اشاریہ,
                                                            video_ڈیٹا_2->vulkan_XGetXCBConnection(video_ڈیٹا_2->display),
                                                            visualid);
    } ورنہ {
        PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR vkGetPhysicalDeviceXlibPresentationSupportKHR =
            (PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR)vkGetInstanceProcAddr(
                instance,
                "vkGetPhysicalDeviceXlibPresentationSupportKHR");

        اگر (!vkGetPhysicalDeviceXlibPresentationSupportKHR) {
            واپس SDL_سیٹ_Error(VK_KHR_XLIB_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        }

        واپس vkGetPhysicalDeviceXlibPresentationSupportKHR(physicalDevice,
                                                             قطار_Family_اشاریہ,
                                                             video_ڈیٹا_2->display,
                                                             visualid);
    }
}

#اگر_ختم
