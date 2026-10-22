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

/*
 * @author Manuel Alfayate Corchere <redwindwanderer@gmail.com>.
 * Based on Jacob Lifshay's SDL_x11vulkan.c.
 */

#അന്തര്ഭാവ "SDL_internal.h"

#എങ്കിൽ defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_KMSDRM)

#അന്തര്ഭാവ "../SDL_vulkan_internal.h"

#അന്തര്ഭാവ "SDL_kmsdrmvideo.h"
#അന്തര്ഭാവ "SDL_kmsdrmdyn.h"
#അന്തര്ഭാവ "SDL_kmsdrmvulkan.h"

#അന്തര്ഭാവ <sys/ioctl.h>

#ifdef SDL_PLATFORM_OPENBSD
#define DEFAULT_VULKAN "libvulkan.so"
#അല്ലെങ്കിൽ
#define DEFAULT_VULKAN "libvulkan.so.1"
#endif

SDL_ELF_NOTE_DLOPEN(
    "kmsdrm-vulkan",
    "Support for Vulkan on KMSDRM",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_SUGGESTED,
    DEFAULT_VULKAN
)

bool KMSDRM_Vulkan_LoadLibrary(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *path)
{
    VkExtensionProperties *extensions = ശൂന്യ;
    Uint32 i, extension_എണ്ണം = 0;
    bool hasSurfaceExtension = false;
    bool hasDisplayExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = ശൂന്യ;

    എങ്കിൽ (_this->vulkan_config.loader_handle) {
        തിരികെ SDL_SetError("Vulkan already loaded");
    }

    // Load the Vulkan library
    എങ്കിൽ (!path) {
        path = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }
    എങ്കിൽ (!path) {
        path = DEFAULT_VULKAN;
    }

    _this->vulkan_config.loader_handle = SDL_LoadObject(path);

    എങ്കിൽ (!_this->vulkan_config.loader_handle) {
        തിരികെ false;
    }

    SDL_strlcpy(_this->vulkan_config.loader_path, path,
                SDL_arraysize(_this->vulkan_config.loader_path));

    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)SDL_LoadFunction(
        _this->vulkan_config.loader_handle, "vkGetInstanceProcAddr");

    എങ്കിൽ (!vkGetInstanceProcAddr) {
        പോകുക fail;
    }

    _this->vulkan_config.vkGetInstanceProcAddr = (ശൂന്യം *)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties =
        (ശൂന്യം *)((PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr)(
            VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties");

    എങ്കിൽ (!_this->vulkan_config.vkEnumerateInstanceExtensionProperties) {
        പോകുക fail;
    }

    extensions = SDL_Vulkan_CreateInstanceExtensionsList(
        (PFN_vkEnumerateInstanceExtensionProperties)
            _this->vulkan_config.vkEnumerateInstanceExtensionProperties,
        &extension_എണ്ണം);

    എങ്കിൽ (!extensions) {
        പോകുക fail;
    }

    വേണ്ടി (i = 0; i < extension_എണ്ണം; i++) {
        എങ്കിൽ (SDL_strcmp(VK_KHR_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasSurfaceExtension = true;
        } അല്ലെങ്കിൽ എങ്കിൽ (SDL_strcmp(VK_KHR_DISPLAY_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasDisplayExtension = true;
        }
    }

    SDL_free(extensions);

    എങ്കിൽ (!hasSurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        പോകുക fail;
    } അല്ലെങ്കിൽ എങ്കിൽ (!hasDisplayExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_DISPLAY_EXTENSION_NAME " extension");
        പോകുക fail;
    }

    തിരികെ true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = ശൂന്യ;
    തിരികെ false;
}

ശൂന്യം KMSDRM_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    എങ്കിൽ (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = ശൂന്യ;
    }
}

/*********************************************************************/
// Here we can put whatever Vulkan extensions we want to be enabled
// at instance creation, which is done in the programs, not in SDL.
// So: programs call SDL_Vulkan_GetInstanceExtensions() and here
// we put the extensions specific to this backend so the programs
// get a list with the extension we want, so they can include that
// list in the ppEnabledExtensionNames and EnabledExtensionCount
// members of the VkInstanceCreateInfo struct passed to
// vkCreateInstance().
/*********************************************************************/
അക്ഷരം സ്ഥിരം * സ്ഥിരം *KMSDRM_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *എണ്ണം)
{
    സ്ഥിതം സ്ഥിരം അക്ഷരം *സ്ഥിരം extensionsForKMSDRM[] = {
        VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_DISPLAY_EXTENSION_NAME
    };
    *എണ്ണം = SDL_arraysize(extensionsForKMSDRM);
    തിരികെ extensionsForKMSDRM;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ SDLCALL display_mode_comparator(സ്ഥിരം ശൂന്യം *a_opaque, സ്ഥിരം ശൂന്യം *b_opaque)
{
    സ്ഥിരം VkDisplayModePropertiesKHR *a = a_opaque;
    സ്ഥിരം VkDisplayModePropertiesKHR *b = b_opaque;

    എങ്കിൽ (a->parameters.refreshRate > b->parameters.refreshRate)
        തിരികെ -1;
    അല്ലെങ്കിൽ എങ്കിൽ (a->parameters.refreshRate < b->parameters.refreshRate)
        തിരികെ 1;
    അല്ലെങ്കിൽ
        തിരികെ 0;
}

/***********************************************************************/
// First thing to know is that we don't call vkCreateInstance() here.
// Instead, programs using SDL and Vulkan create their Vulkan instance
// and we get it here, ready to use.
// Extensions specific for this platform are activated in
// KMSDRM_Vulkan_GetInstanceExtensions(), like we do with
// VK_KHR_DISPLAY_EXTENSION_NAME, which is what we need for x-less VK.
/***********************************************************************/
bool KMSDRM_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                                SDL_Window *window,
                                VkInstance instance,
                                സ്ഥിരം ഘടന VkAllocationCallbacks *allocator,
                                VkSurfaceKHR *surface)
{
    VkPhysicalDevice gpu = ശൂന്യ;
    uint32_t gpu_എണ്ണം;
    uint32_t display_എണ്ണം;
    uint32_t mode_എണ്ണം;
    uint32_t plane_എണ്ണം_2;
    uint32_t _plane = UINT32_MAX;

    VkPhysicalDevice *physical_devices = ശൂന്യ;
    VkPhysicalDeviceProperties *device_props = ശൂന്യ;
    VkDisplayPropertiesKHR *display_props = ശൂന്യ;
    VkDisplayModePropertiesKHR *mode_props = ശൂന്യ;
    VkDisplayPlanePropertiesKHR *plane_props = ശൂന്യ;
    VkDisplayPlaneCapabilitiesKHR plane_caps;

    VkDisplayModeCreateInfoKHR display_mode_create_info;
    VkDisplaySurfaceCreateInfoKHR display_plane_surface_create_info;

    VkExtent2D image_size;
    VkDisplayKHR display;
    VkDisplayModeKHR display_mode = (VkDisplayModeKHR)0;
    VkDisplayModePropertiesKHR display_mode_props = { 0 };
    VkDisplayModeParametersKHR new_mode_parameters = { { 0, 0 }, 0 };
    // Prefer a plane that supports per-pixel alpha.
    VkDisplayPlaneAlphaFlagBitsKHR alpha_mode = VK_DISPLAY_PLANE_ALPHA_OPAQUE_BIT_KHR;

    VkResult result;
    bool ret = false;
    bool valid_gpu = false;
    bool mode_found = false;
    bool plane_supports_display = false;

    // Get the display index from the display being used by the window.
    പൂർണ്ണസംഖ്യ display_index = SDL_GetDisplayIndex(SDL_GetDisplayForWindow(window));
    പൂർണ്ണസംഖ്യ i, j;

    // Get the function pointers for the functions we will use.
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;

    PFN_vkCreateDisplayPlaneSurfaceKHR vkCreateDisplayPlaneSurfaceKHR =
        (PFN_vkCreateDisplayPlaneSurfaceKHR)vkGetInstanceProcAddr(
            instance, "vkCreateDisplayPlaneSurfaceKHR");

    PFN_vkEnumeratePhysicalDevices vkEnumeratePhysicalDevices =
        (PFN_vkEnumeratePhysicalDevices)vkGetInstanceProcAddr(
            instance, "vkEnumeratePhysicalDevices");

    PFN_vkGetPhysicalDeviceProperties vkGetPhysicalDeviceProperties =
        (PFN_vkGetPhysicalDeviceProperties)vkGetInstanceProcAddr(
            instance, "vkGetPhysicalDeviceProperties");

    PFN_vkGetPhysicalDeviceDisplayPropertiesKHR vkGetPhysicalDeviceDisplayPropertiesKHR =
        (PFN_vkGetPhysicalDeviceDisplayPropertiesKHR)vkGetInstanceProcAddr(
            instance, "vkGetPhysicalDeviceDisplayPropertiesKHR");

    PFN_vkGetDisplayModePropertiesKHR vkGetDisplayModePropertiesKHR =
        (PFN_vkGetDisplayModePropertiesKHR)vkGetInstanceProcAddr(
            instance, "vkGetDisplayModePropertiesKHR");

    PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR vkGetPhysicalDeviceDisplayPlanePropertiesKHR =
        (PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR)vkGetInstanceProcAddr(
            instance, "vkGetPhysicalDeviceDisplayPlanePropertiesKHR");

    PFN_vkGetDisplayPlaneSupportedDisplaysKHR vkGetDisplayPlaneSupportedDisplaysKHR =
        (PFN_vkGetDisplayPlaneSupportedDisplaysKHR)vkGetInstanceProcAddr(
            instance, "vkGetDisplayPlaneSupportedDisplaysKHR");

    PFN_vkGetDisplayPlaneCapabilitiesKHR vkGetDisplayPlaneCapabilitiesKHR =
        (PFN_vkGetDisplayPlaneCapabilitiesKHR)vkGetInstanceProcAddr(
            instance, "vkGetDisplayPlaneCapabilitiesKHR");

    PFN_vkCreateDisplayModeKHR vkCreateDisplayModeKHR =
        (PFN_vkCreateDisplayModeKHR)vkGetInstanceProcAddr(
            instance, "vkCreateDisplayModeKHR");

    എങ്കിൽ (!_this->vulkan_config.loader_handle) {
        SDL_SetError("Vulkan is not loaded");
        പോകുക clean;
    }

    /*************************************/
    // Block for vulkan surface creation
    /*************************************/

    /****************************************************************/
    // If we got vkCreateDisplayPlaneSurfaceKHR() pointer, it means
    // that the VK_KHR_Display extension is active on the instance.
    // That's the central extension we need for x-less VK!
    /****************************************************************/
    എങ്കിൽ (!vkCreateDisplayPlaneSurfaceKHR) {
        SDL_SetError(VK_KHR_DISPLAY_EXTENSION_NAME
                     " extension is not enabled in the Vulkan instance.");
        പോകുക clean;
    }

    /* A GPU (or physical_device, in vkcube terms) is a physical GPU.
       A machine with more than one video output doesn't need to have more than one GPU,
       like the Pi4 which has 1 GPU and 2 video outputs.
       Just in case, we test that the GPU we choose is Vulkan-capable.
       If there are new reports about VK init failures, hardcode
       gpu = physical_devices[0], instead of probing, and go with that.
    */

    // Get the physical device count.
    vkEnumeratePhysicalDevices(instance, &gpu_എണ്ണം, ശൂന്യ);

    എങ്കിൽ (gpu_എണ്ണം == 0) {
        SDL_SetError("Vulkan can't find physical devices (gpus).");
        പോകുക clean;
    }

    // Get the physical devices.
    physical_devices = SDL_malloc(വലുപ്പം(VkPhysicalDevice) * gpu_എണ്ണം);
    device_props = SDL_malloc(വലുപ്പം(VkPhysicalDeviceProperties));
    vkEnumeratePhysicalDevices(instance, &gpu_എണ്ണം, physical_devices);

    // Iterate on the physical devices.
    വേണ്ടി (i = 0; i < gpu_എണ്ണം; i++) {

        // Get the physical device properties.
        vkGetPhysicalDeviceProperties(
            physical_devices[i],
            device_props);

        // Is this device a real GPU that supports API version 1 at least?
        എങ്കിൽ (device_props->apiVersion >= 1 &&
            (device_props->deviceType == 1 || device_props->deviceType == 2)) {
            gpu = physical_devices[i];
            valid_gpu = true;
            നിർത്തുക;
        }
    }

    എങ്കിൽ (!valid_gpu) {
        SDL_SetError("Vulkan can't find a valid physical device (gpu).");
        പോകുക clean;
    }

    /* A display is a video output. 1 GPU can have N displays.
       Vulkan only counts the connected displays.
       Get the display count of the GPU. */
    vkGetPhysicalDeviceDisplayPropertiesKHR(gpu, &display_എണ്ണം, ശൂന്യ);
    എങ്കിൽ (display_എണ്ണം == 0) {
        SDL_SetError("Vulkan can't find any displays.");
        പോകുക clean;
    }

    // Get the props of the displays of the physical device.
    display_props = (VkDisplayPropertiesKHR *)SDL_malloc(display_എണ്ണം * വലുപ്പം(*display_props));
    vkGetPhysicalDeviceDisplayPropertiesKHR(gpu,
                                            &display_എണ്ണം,
                                            display_props);

    // Get the chosen display based on the display index.
    display = display_props[display_index].display;

    // Get the list of the display videomodes.
    vkGetDisplayModePropertiesKHR(gpu,
                                  display,
                                  &mode_എണ്ണം, ശൂന്യ);

    എങ്കിൽ (mode_എണ്ണം == 0) {
        SDL_SetError("Vulkan can't find any video modes for display %i (%s)", 0,
                     display_props[display_index].displayName);
        പോകുക clean;
    }

    mode_props = (VkDisplayModePropertiesKHR *)SDL_malloc(mode_എണ്ണം * വലുപ്പം(*mode_props));
    vkGetDisplayModePropertiesKHR(gpu,
                                  display,
                                  &mode_എണ്ണം, mode_props);

    /* Sort the modes so that larger refresh rates come first. */
    SDL_qsort(mode_props, mode_എണ്ണം, വലുപ്പം(*mode_props), display_mode_comparator);

    /* Get a video mode equal to the window size among the predefined ones,
       if possible.
       REMEMBER: We have to get a small enough videomode for the window size,
       because videomode determines how big the scanout region is and we can't
       scanout a region bigger than the window (we would be reading past the
       buffer, and Vulkan would give us a confusing VK_ERROR_SURFACE_LOST_KHR). */
    വേണ്ടി (i = 0; i < mode_എണ്ണം; i++) {
        എങ്കിൽ (mode_props[i].parameters.visibleRegion.width == window->w &&
            mode_props[i].parameters.visibleRegion.height == window->h) {
            display_mode_props = mode_props[i];
            mode_found = true;
            നിർത്തുക;
        }
    }

    എങ്കിൽ (mode_found &&
        display_mode_props.parameters.visibleRegion.width > 0 &&
        display_mode_props.parameters.visibleRegion.height > 0) {
        // Found a suitable mode among the predefined ones. Use that.
        display_mode = display_mode_props.displayMode;
    } അല്ലെങ്കിൽ {

        /* Couldn't find a suitable mode among the predefined ones, so try to create our own.
           This won't work for some video chips atm (like Pi's VideoCore) so these are limited
           to supported resolutions. Don't try to use "closest" resolutions either, because
           those are often bigger than the window size, thus causing out-of-bunds scanout. */
        new_mode_parameters.visibleRegion.width = window->w;
        new_mode_parameters.visibleRegion.height = window->h;
        /* SDL (and DRM, if we look at drmModeModeInfo vrefresh) uses plain integer Hz for
           display mode refresh rate, but Vulkan expects higher precision. */
        new_mode_parameters.refreshRate = (uint32_t)(window->current_fullscreen_mode.refresh_rate * 1000);

        SDL_zero(display_mode_create_info);
        display_mode_create_info.sType = VK_STRUCTURE_TYPE_DISPLAY_MODE_CREATE_INFO_KHR;
        display_mode_create_info.parameters = new_mode_parameters;
        result = vkCreateDisplayModeKHR(gpu,
                                        display,
                                        &display_mode_create_info,
                                        ശൂന്യ, &display_mode);
        എങ്കിൽ (result != VK_SUCCESS) {
            SDL_SetError("Vulkan couldn't find a predefined mode for that window size and couldn't create a suitable mode.");
            പോകുക clean;
        }
    }

    // Just in case we get here without a display_mode.
    എങ്കിൽ (!display_mode) {
        SDL_SetError("Vulkan couldn't get a display mode.");
        പോകുക clean;
    }

    // Get the list of the physical device planes.
    vkGetPhysicalDeviceDisplayPlanePropertiesKHR(gpu, &plane_എണ്ണം_2, ശൂന്യ);
    എങ്കിൽ (plane_എണ്ണം_2 == 0) {
        SDL_SetError("Vulkan can't find any planes.");
        പോകുക clean;
    }
    plane_props = SDL_malloc(വലുപ്പം(VkDisplayPlanePropertiesKHR) * plane_എണ്ണം_2);
    vkGetPhysicalDeviceDisplayPlanePropertiesKHR(gpu, &plane_എണ്ണം_2, plane_props);

    /* Iterate on the list of planes of the physical device
       to find a plane that matches these criteria:
       -It must be compatible with the chosen display + mode.
       -It isn't currently bound to another display.
       -It supports per-pixel alpha, if possible. */
    വേണ്ടി (i = 0; i < plane_എണ്ണം_2; i++) {

        uint32_t supported_displays_എണ്ണം = 0;
        VkDisplayKHR *supported_displays;

        // See if the plane is compatible with the current display.
        vkGetDisplayPlaneSupportedDisplaysKHR(gpu, i, &supported_displays_എണ്ണം, ശൂന്യ);
        എങ്കിൽ (supported_displays_എണ്ണം == 0) {
            // This plane doesn't support any displays. Continue to the next plane.
            തുടരുക;
        }

        // Get the list of displays supported by this plane.
        supported_displays = (VkDisplayKHR *)SDL_malloc(വലുപ്പം(VkDisplayKHR) * supported_displays_എണ്ണം);
        vkGetDisplayPlaneSupportedDisplaysKHR(gpu, i,
                                              &supported_displays_എണ്ണം, supported_displays);

        /* The plane must be bound to the chosen display, or not in use.
           If none of these is true, iterate to another plane. */
        എങ്കിൽ (!((plane_props[i].currentDisplay == display) || (plane_props[i].currentDisplay == VK_NULL_HANDLE))) {
            തുടരുക;
        }

        /* Iterate the list of displays supported by this plane
           in order to find out if the chosen display is among them. */
        plane_supports_display = false;
        വേണ്ടി (j = 0; j < supported_displays_എണ്ണം; j++) {
            എങ്കിൽ (supported_displays[j] == display) {
                plane_supports_display = true;
                നിർത്തുക;
            }
        }

        // Free the list of displays supported by this plane.
        SDL_free(supported_displays);

        // If the display is not supported by this plane, iterate to the next plane.
        എങ്കിൽ (!plane_supports_display) {
            തുടരുക;
        }

        // Want a plane that supports the alpha mode we have chosen.
        vkGetDisplayPlaneCapabilitiesKHR(gpu, display_mode, i, &plane_caps);
        എങ്കിൽ (plane_caps.supportedAlpha == alpha_mode) {
            // Yep, this plane is alright.
            _plane = i;
            നിർത്തുക;
        }
    }

    // If we couldn't find an appropriate plane, error out.
    എങ്കിൽ (_plane == UINT32_MAX) {
        SDL_SetError("Vulkan couldn't find an appropriate plane.");
        പോകുക clean;
    }

    /********************************************/
    // Let's finally create the Vulkan surface!
    /********************************************/

    image_size.width = window->w;
    image_size.height = window->h;

    SDL_zero(display_plane_surface_create_info);
    display_plane_surface_create_info.sType = VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR;
    display_plane_surface_create_info.displayMode = display_mode;
    display_plane_surface_create_info.planeIndex = _plane;
    display_plane_surface_create_info.imageExtent = image_size;
    display_plane_surface_create_info.transform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    display_plane_surface_create_info.alphaMode = alpha_mode;
    result = vkCreateDisplayPlaneSurfaceKHR(instance,
                                            &display_plane_surface_create_info,
                                            allocator,
                                            surface);
    എങ്കിൽ (result != VK_SUCCESS) {
        SDL_SetError("vkCreateDisplayPlaneSurfaceKHR failed: %s",
                     SDL_Vulkan_GetResultString(result));
        പോകുക clean;
    }

    ret = true;  // success!

clean:
    SDL_free(physical_devices);
    SDL_free(display_props);
    SDL_free(device_props);
    SDL_free(plane_props);
    SDL_free(mode_props);

    തിരികെ ret;
}

ശൂന്യം KMSDRM_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                  VkInstance instance,
                                  VkSurfaceKHR surface,
                                  സ്ഥിരം ഘടന VkAllocationCallbacks *allocator)
{
    എങ്കിൽ (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_DestroySurface_Internal(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

#endif
