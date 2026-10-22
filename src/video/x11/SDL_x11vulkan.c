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
#అన్తర్భావ "SDL_internal.h"

#ఒకవేళ defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_X11)

#అన్తర్భావ "../SDL_vulkan_internal.h"

#అన్తర్భావ "SDL_x11video.h"

#అన్తర్భావ "SDL_x11vulkan.h"

#అన్తర్భావ <X11/Xlib.h>
// #include <xcb/xcb.h>

#నిర్వచితమైతే SDL_PLATFORM_OPENBSD
#నిర్వచించు DEFAULT_VULKAN "libvulkan.so"
#నిర్వచించు DEFAULT_X11_XCB "libX11-xcb.so"
#లేకపోతే
#నిర్వచించు DEFAULT_VULKAN "libvulkan.so.1"
#నిర్వచించు DEFAULT_X11_XCB "libX11-xcb.so.1"
#అయితే_ముగింపు

SDL_ELF_NOTE_DLOPEN(
    "x11-vulkan",
    "Support for vulkan on X11",
    SDL_ELF_NOTE_DLOPEN_ప్రాధాన్యత_SUGGESTED,
    DEFAULT_VULKAN
)

SDL_ELF_NOTE_DLOPEN(
    "x11-vulkan",
    "Support for vulkan on X11",
    SDL_ELF_NOTE_DLOPEN_ప్రాధాన్యత_SUGGESTED,
    DEFAULT_X11_XCB
)

/*
typedef uint32_t xcb_window_t;
typedef uint32_t xcb_visualid_t;
*/

bool X11_Vulkan_ఎక్కించు_Library(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *మార్గం)
{
    SDL_Video_దత్తాంశం *video_దత్తాంశం_2 = _this->అంతర్గత;
    VkExtensionProperties *extensions = ఖాళీ;
    Uint32 extension_లెక్క = 0;
    bool hasSurfaceExtension = false;
    bool hasXlibSurfaceExtension = false;
    bool hasXCBSurfaceExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = ఖాళీ;
    Uint32 i;
    ఒకవేళ (_this->vulkan_config.loader_handle) {
        తిరిగి SDL_సమితి_Error("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    ఒకవేళ (!మార్గం) {
        మార్గం = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }
    ఒకవేళ (!మార్గం) {
        మార్గం = DEFAULT_VULKAN;
    }
    _this->vulkan_config.loader_handle = SDL_ఎక్కించు_Object(మార్గం);
    ఒకవేళ (!_this->vulkan_config.loader_handle) {
        తిరిగి false;
    }
    SDL_strlcpy(_this->vulkan_config.loader_మార్గం, మార్గం, SDL_arraysize(_this->vulkan_config.loader_మార్గం));
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)SDL_ఎక్కించు_Function(
        _this->vulkan_config.loader_handle, "vkGetInstanceProcAddr");
    ఒకవేళ (!vkGetInstanceProcAddr) {
        వెళ్ళు fail;
    }
    _this->vulkan_config.vkGetInstanceProcAddr = (శూన్య *)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties =
        (శూన్య *)((PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr)(
            VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties");
    ఒకవేళ (!_this->vulkan_config.vkEnumerateInstanceExtensionProperties) {
        వెళ్ళు fail;
    }
    extensions = SDL_Vulkan_CreateInstanceExtensionsList(
        (PFN_vkEnumerateInstanceExtensionProperties)
            _this->vulkan_config.vkEnumerateInstanceExtensionProperties,
        &extension_లెక్క);
    ఒకవేళ (!extensions) {
        వెళ్ళు fail;
    }
    కొరకు (i = 0; i < extension_లెక్క; i++) {
        ఒకవేళ (SDL_strcmp(VK_KHR_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasSurfaceExtension = true;
        } లేకపోతే ఒకవేళ (SDL_strcmp(VK_KHR_XCB_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasXCBSurfaceExtension = true;
        } లేకపోతే ఒకవేళ (SDL_strcmp(VK_KHR_XLIB_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasXlibSurfaceExtension = true;
        }
    }
    SDL_free(extensions);
    ఒకవేళ (!hasSurfaceExtension) {
        SDL_సమితి_Error("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        వెళ్ళు fail;
    }
    ఒకవేళ (hasXlibSurfaceExtension) {
        video_దత్తాంశం_2->vulkan_xlib_xcb_library = ఖాళీ;
    } లేకపోతే ఒకవేళ (!hasXCBSurfaceExtension) {
        SDL_సమితి_Error("Installed Vulkan doesn't implement either the " VK_KHR_XCB_SURFACE_EXTENSION_NAME " extension or the " VK_KHR_XLIB_SURFACE_EXTENSION_NAME " extension");
        వెళ్ళు fail;
    } లేకపోతే {
        స్థిరరాశి అక్షరం *libX11XCBLibraryName = SDL_GetHint(SDL_HINT_X11_XCB_LIBRARY);
        ఒకవేళ (!libX11XCBLibraryName || !*libX11XCBLibraryName) {
            libX11XCBLibraryName = DEFAULT_X11_XCB;
        }
        video_దత్తాంశం_2->vulkan_xlib_xcb_library = SDL_ఎక్కించు_Object(libX11XCBLibraryName);
        ఒకవేళ (!video_దత్తాంశం_2->vulkan_xlib_xcb_library) {
            వెళ్ళు fail;
        }
        video_దత్తాంశం_2->vulkan_XGetXCBConnection =
            (PFN_XGetXCBConnection)SDL_ఎక్కించు_Function(video_దత్తాంశం_2->vulkan_xlib_xcb_library, "XGetXCBConnection");
        ఒకవేళ (!video_దత్తాంశం_2->vulkan_XGetXCBConnection) {
            SDL_UnloadObject(video_దత్తాంశం_2->vulkan_xlib_xcb_library);
            వెళ్ళు fail;
        }
    }
    తిరిగి true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = ఖాళీ;
    తిరిగి false;
}

శూన్య X11_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *video_దత్తాంశం_2 = _this->అంతర్గత;
    ఒకవేళ (_this->vulkan_config.loader_handle) {
        ఒకవేళ (video_దత్తాంశం_2->vulkan_xlib_xcb_library) {
            SDL_UnloadObject(video_దత్తాంశం_2->vulkan_xlib_xcb_library);
        }
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = ఖాళీ;
    }
}

అక్షరం స్థిరరాశి * స్థిరరాశి *X11_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *లెక్క)
{
    SDL_Video_దత్తాంశం *video_దత్తాంశం_2 = _this->అంతర్గత;
    ఒకవేళ (video_దత్తాంశం_2->vulkan_xlib_xcb_library) {
        స్థిర స్థిరరాశి అక్షరం *స్థిరరాశి extensionsForXCB[] = {
            VK_KHR_SURFACE_EXTENSION_NAME,
            VK_KHR_XCB_SURFACE_EXTENSION_NAME,
        };
        *లెక్క = SDL_arraysize(extensionsForXCB);
        తిరిగి extensionsForXCB;
    } లేకపోతే {
        స్థిర స్థిరరాశి అక్షరం *స్థిరరాశి extensionsForXlib[] = {
            VK_KHR_SURFACE_EXTENSION_NAME,
            VK_KHR_XLIB_SURFACE_EXTENSION_NAME,
        };
        *లెక్క = SDL_arraysize(extensionsForXlib);
        తిరిగి extensionsForXlib;
    }
}

bool X11_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                             SDL_కిటికీ *కిటికీ,
                             VkInstance instance,
                             స్థిరరాశి నిర్మాణం Vk_కేటాయింపు_Callbacks *allocator,
                             VkSurfaceKHR *surface)
{
    SDL_Video_దత్తాంశం *video_దత్తాంశం_2 = _this->అంతర్గత;
    SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం = కిటికీ->అంతర్గత;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;
    ఒకవేళ (!_this->vulkan_config.loader_handle) {
        తిరిగి SDL_సమితి_Error("Vulkan is not loaded");
    }
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    ఒకవేళ (video_దత్తాంశం_2->vulkan_xlib_xcb_library) {
        PFN_vkCreateXcbSurfaceKHR vkCreateXcbSurfaceKHR =
            (PFN_vkCreateXcbSurfaceKHR)vkGetInstanceProcAddr(instance,
                                                             "vkCreateXcbSurfaceKHR");
        VkXcbSurfaceCreateInfoKHR createInfo;
        Vk_ఫలితం ఫలితం;
        ఒకవేళ (!vkCreateXcbSurfaceKHR) {
            తిరిగి SDL_సమితి_Error(VK_KHR_XCB_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        }
        SDL_zero(createInfo);
        createInfo.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
        createInfo.connection = video_దత్తాంశం_2->vulkan_XGetXCBConnection(video_దత్తాంశం_2->display);
        ఒకవేళ (!createInfo.connection) {
            తిరిగి SDL_సమితి_Error("XGetXCBConnection failed");
        }
        createInfo.కిటికీ = (xcb_కిటికీ_t)కిటికీ_దత్తాంశం->xwindow;
        ఫలితం = vkCreateXcbSurfaceKHR(instance, &createInfo, allocator, surface);
        ఒకవేళ (ఫలితం != VK_SUCCESS) {
            తిరిగి SDL_సమితి_Error("vkCreateXcbSurfaceKHR failed: %s", SDL_Vulkan_Get_ఫలితం_String(ఫలితం));
        }
    } లేకపోతే {
        PFN_vkCreateXlibSurfaceKHR vkCreateXlibSurfaceKHR =
            (PFN_vkCreateXlibSurfaceKHR)vkGetInstanceProcAddr(instance,
                                                              "vkCreateXlibSurfaceKHR");
        VkXlibSurfaceCreateInfoKHR createInfo;
        Vk_ఫలితం ఫలితం;
        ఒకవేళ (!vkCreateXlibSurfaceKHR) {
            తిరిగి SDL_సమితి_Error(VK_KHR_XLIB_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        }
        SDL_zero(createInfo);
        createInfo.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
        createInfo.dpy = video_దత్తాంశం_2->display;
        createInfo.కిటికీ = (xcb_కిటికీ_t)కిటికీ_దత్తాంశం->xwindow;
        ఫలితం = vkCreateXlibSurfaceKHR(instance, &createInfo, allocator, surface);
        ఒకవేళ (ఫలితం != VK_SUCCESS) {
            తిరిగి SDL_సమితి_Error("vkCreateXlibSurfaceKHR failed: %s", SDL_Vulkan_Get_ఫలితం_String(ఫలితం));
        }
    }

    తిరిగి true;  // success!
}

శూన్య X11_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                               VkInstance instance,
                               VkSurfaceKHR surface,
                               స్థిరరాశి నిర్మాణం Vk_కేటాయింపు_Callbacks *allocator)
{
    ఒకవేళ (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_Destroy_Surface_అంతర్గత(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

bool X11_Vulkan_GetPresentationSupport(SDL_VideoDevice *_this,
                                           VkInstance instance,
                                           VkPhysicalDevice physicalDevice,
                                           Uint32 వరుస_Family_సూచీ)
{
    SDL_Video_దత్తాంశం *video_దత్తాంశం_2 = _this->అంతర్గత;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;
    స్థిరరాశి అక్షరం *forced_visual_id;
    VisualID visualid;

    ఒకవేళ (!_this->vulkan_config.loader_handle) {
        తిరిగి SDL_సమితి_Error("Vulkan is not loaded");
    }
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;

    forced_visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_కిటికీ_VISUALID);
    ఒకవేళ (forced_visual_id) {
        visualid = SDL_strtol(forced_visual_id, ఖాళీ, 0);
    } లేకపోతే {
        visualid = X11_XVisualIDFromVisual(DefaultVisual(video_దత్తాంశం_2->display, DefaultScreen(video_దత్తాంశం_2->display)));
    }

    ఒకవేళ (video_దత్తాంశం_2->vulkan_xlib_xcb_library) {
        PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR vkGetPhysicalDeviceXcbPresentationSupportKHR =
            (PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR)vkGetInstanceProcAddr(
                instance,
                "vkGetPhysicalDeviceXcbPresentationSupportKHR");

        ఒకవేళ (!vkGetPhysicalDeviceXcbPresentationSupportKHR) {
            తిరిగి SDL_సమితి_Error(VK_KHR_XCB_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        }

        తిరిగి vkGetPhysicalDeviceXcbPresentationSupportKHR(physicalDevice,
                                                            వరుస_Family_సూచీ,
                                                            video_దత్తాంశం_2->vulkan_XGetXCBConnection(video_దత్తాంశం_2->display),
                                                            visualid);
    } లేకపోతే {
        PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR vkGetPhysicalDeviceXlibPresentationSupportKHR =
            (PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR)vkGetInstanceProcAddr(
                instance,
                "vkGetPhysicalDeviceXlibPresentationSupportKHR");

        ఒకవేళ (!vkGetPhysicalDeviceXlibPresentationSupportKHR) {
            తిరిగి SDL_సమితి_Error(VK_KHR_XLIB_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        }

        తిరిగి vkGetPhysicalDeviceXlibPresentationSupportKHR(physicalDevice,
                                                             వరుస_Family_సూచీ,
                                                             video_దత్తాంశం_2->display,
                                                             visualid);
    }
}

#అయితే_ముగింపు
