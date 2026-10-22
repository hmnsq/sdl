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

#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ଯଦି defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_KMSDRM)

#ଅନ୍ତର୍ଭାଵ "../SDL_vulkan_internal.h"

#ଅନ୍ତର୍ଭାଵ "SDL_kmsdrmvideo.h"
#ଅନ୍ତର୍ଭାଵ "SDL_kmsdrmdyn.h"
#ଅନ୍ତର୍ଭାଵ "SDL_kmsdrmvulkan.h"

#ଅନ୍ତର୍ଭାଵ <sys/ioctl.h>

#ifdef SDL_PLATFORM_OPENBSD
#define DEFAULT_VULKAN "libvulkan.so"
#ଅନ୍ୟଥା
#define DEFAULT_VULKAN "libvulkan.so.1"
#endif

SDL_ELF_NOTE_DLOPEN(
    "kmsdrm-vulkan",
    "Support for Vulkan on KMSDRM",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_SUGGESTED,
    DEFAULT_VULKAN
)

bool KMSDRM_Vulkan_LoadLibrary(SDL_VideoDevice *_this, ଅଚଳ ଅକ୍ଷର *path)
{
    VkExtensionProperties *extensions = ଖାଲି;
    Uint32 i, extension_ଗଣନା = 0;
    bool hasSurfaceExtension = false;
    bool hasDisplayExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = ଖାଲି;

    ଯଦି (_this->vulkan_config.loader_handle) {
        ଫେରନ୍ତୁ SDL_SetError("Vulkan already loaded");
    }

    // Load the Vulkan library
    ଯଦି (!path) {
        path = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }
    ଯଦି (!path) {
        path = DEFAULT_VULKAN;
    }

    _this->vulkan_config.loader_handle = SDL_LoadObject(path);

    ଯଦି (!_this->vulkan_config.loader_handle) {
        ଫେରନ୍ତୁ false;
    }

    SDL_strlcpy(_this->vulkan_config.loader_path, path,
                SDL_arraysize(_this->vulkan_config.loader_path));

    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)SDL_LoadFunction(
        _this->vulkan_config.loader_handle, "vkGetInstanceProcAddr");

    ଯଦି (!vkGetInstanceProcAddr) {
        ଯାଅ fail;
    }

    _this->vulkan_config.vkGetInstanceProcAddr = (ଶୂନ୍ୟ *)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties =
        (ଶୂନ୍ୟ *)((PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr)(
            VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties");

    ଯଦି (!_this->vulkan_config.vkEnumerateInstanceExtensionProperties) {
        ଯାଅ fail;
    }

    extensions = SDL_Vulkan_CreateInstanceExtensionsList(
        (PFN_vkEnumerateInstanceExtensionProperties)
            _this->vulkan_config.vkEnumerateInstanceExtensionProperties,
        &extension_ଗଣନା);

    ଯଦି (!extensions) {
        ଯାଅ fail;
    }

    ପାଇଁ (i = 0; i < extension_ଗଣନା; i++) {
        ଯଦି (SDL_strcmp(VK_KHR_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasSurfaceExtension = true;
        } ଅନ୍ୟଥା ଯଦି (SDL_strcmp(VK_KHR_DISPLAY_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasDisplayExtension = true;
        }
    }

    SDL_free(extensions);

    ଯଦି (!hasSurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        ଯାଅ fail;
    } ଅନ୍ୟଥା ଯଦି (!hasDisplayExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_DISPLAY_EXTENSION_NAME " extension");
        ଯାଅ fail;
    }

    ଫେରନ୍ତୁ true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = ଖାଲି;
    ଫେରନ୍ତୁ false;
}

ଶୂନ୍ୟ KMSDRM_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    ଯଦି (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = ଖାଲି;
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
ଅକ୍ଷର ଅଚଳ * ଅଚଳ *KMSDRM_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *ଗଣନା_2)
{
    ସ୍ଥିର ଅଚଳ ଅକ୍ଷର *ଅଚଳ extensionsForKMSDRM[] = {
        VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_DISPLAY_EXTENSION_NAME
    };
    *ଗଣନା_2 = SDL_arraysize(extensionsForKMSDRM);
    ଫେରନ୍ତୁ extensionsForKMSDRM;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା SDLCALL display_mode_comparator(ଅଚଳ ଶୂନ୍ୟ *a_opaque, ଅଚଳ ଶୂନ୍ୟ *b_opaque)
{
    ଅଚଳ VkDisplayModePropertiesKHR *a = a_opaque;
    ଅଚଳ VkDisplayModePropertiesKHR *b = b_opaque;

    ଯଦି (a->parameters.refreshRate > b->parameters.refreshRate)
        ଫେରନ୍ତୁ -1;
    ଅନ୍ୟଥା ଯଦି (a->parameters.refreshRate < b->parameters.refreshRate)
        ଫେରନ୍ତୁ 1;
    ଅନ୍ୟଥା
        ଫେରନ୍ତୁ 0;
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
                                ଅଚଳ ସଂରଚନା VkAllocationCallbacks *allocator,
                                VkSurfaceKHR *surface)
{
    VkPhysicalDevice gpu = ଖାଲି;
    uint32_t gpu_ଗଣନା;
    uint32_t display_ଗଣନା;
    uint32_t mode_ଗଣନା;
    uint32_t plane_ଗଣନା_2;
    uint32_t _plane = UINT32_MAX;

    VkPhysicalDevice *physical_devices = ଖାଲି;
    VkPhysicalDeviceProperties *device_props = ଖାଲି;
    VkDisplayPropertiesKHR *display_props = ଖାଲି;
    VkDisplayModePropertiesKHR *mode_props = ଖାଲି;
    VkDisplayPlanePropertiesKHR *plane_props = ଖାଲି;
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
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା display_index = SDL_GetDisplayIndex(SDL_GetDisplayForWindow(window));
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, j;

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

    ଯଦି (!_this->vulkan_config.loader_handle) {
        SDL_SetError("Vulkan is not loaded");
        ଯାଅ clean;
    }

    /*************************************/
    // Block for vulkan surface creation
    /*************************************/

    /****************************************************************/
    // If we got vkCreateDisplayPlaneSurfaceKHR() pointer, it means
    // that the VK_KHR_Display extension is active on the instance.
    // That's the central extension we need for x-less VK!
    /****************************************************************/
    ଯଦି (!vkCreateDisplayPlaneSurfaceKHR) {
        SDL_SetError(VK_KHR_DISPLAY_EXTENSION_NAME
                     " extension is not enabled in the Vulkan instance.");
        ଯାଅ clean;
    }

    /* A GPU (or physical_device, in vkcube terms) is a physical GPU.
       A machine with more than one video output doesn't need to have more than one GPU,
       like the Pi4 which has 1 GPU and 2 video outputs.
       Just in case, we test that the GPU we choose is Vulkan-capable.
       If there are new reports about VK init failures, hardcode
       gpu = physical_devices[0], instead of probing, and go with that.
    */

    // Get the physical device count.
    vkEnumeratePhysicalDevices(instance, &gpu_ଗଣନା, ଖାଲି);

    ଯଦି (gpu_ଗଣନା == 0) {
        SDL_SetError("Vulkan can't find physical devices (gpus).");
        ଯାଅ clean;
    }

    // Get the physical devices.
    physical_devices = SDL_malloc(ଆକାର(VkPhysicalDevice) * gpu_ଗଣନା);
    device_props = SDL_malloc(ଆକାର(VkPhysicalDeviceProperties));
    vkEnumeratePhysicalDevices(instance, &gpu_ଗଣନା, physical_devices);

    // Iterate on the physical devices.
    ପାଇଁ (i = 0; i < gpu_ଗଣନା; i++) {

        // Get the physical device properties.
        vkGetPhysicalDeviceProperties(
            physical_devices[i],
            device_props);

        // Is this device a real GPU that supports API version 1 at least?
        ଯଦି (device_props->apiVersion >= 1 &&
            (device_props->deviceType == 1 || device_props->deviceType == 2)) {
            gpu = physical_devices[i];
            valid_gpu = true;
            ଭାଙ୍ଗ;
        }
    }

    ଯଦି (!valid_gpu) {
        SDL_SetError("Vulkan can't find a valid physical device (gpu).");
        ଯାଅ clean;
    }

    /* A display is a video output. 1 GPU can have N displays.
       Vulkan only counts the connected displays.
       Get the display count of the GPU. */
    vkGetPhysicalDeviceDisplayPropertiesKHR(gpu, &display_ଗଣନା, ଖାଲି);
    ଯଦି (display_ଗଣନା == 0) {
        SDL_SetError("Vulkan can't find any displays.");
        ଯାଅ clean;
    }

    // Get the props of the displays of the physical device.
    display_props = (VkDisplayPropertiesKHR *)SDL_malloc(display_ଗଣନା * ଆକାର(*display_props));
    vkGetPhysicalDeviceDisplayPropertiesKHR(gpu,
                                            &display_ଗଣନା,
                                            display_props);

    // Get the chosen display based on the display index.
    display = display_props[display_index].display;

    // Get the list of the display videomodes.
    vkGetDisplayModePropertiesKHR(gpu,
                                  display,
                                  &mode_ଗଣନା, ଖାଲି);

    ଯଦି (mode_ଗଣନା == 0) {
        SDL_SetError("Vulkan can't find any video modes for display %i (%s)", 0,
                     display_props[display_index].displayName);
        ଯାଅ clean;
    }

    mode_props = (VkDisplayModePropertiesKHR *)SDL_malloc(mode_ଗଣନା * ଆକାର(*mode_props));
    vkGetDisplayModePropertiesKHR(gpu,
                                  display,
                                  &mode_ଗଣନା, mode_props);

    /* Sort the modes so that larger refresh rates come first. */
    SDL_qsort(mode_props, mode_ଗଣନା, ଆକାର(*mode_props), display_mode_comparator);

    /* Get a video mode equal to the window size among the predefined ones,
       if possible.
       REMEMBER: We have to get a small enough videomode for the window size,
       because videomode determines how big the scanout region is and we can't
       scanout a region bigger than the window (we would be reading past the
       buffer, and Vulkan would give us a confusing VK_ERROR_SURFACE_LOST_KHR). */
    ପାଇଁ (i = 0; i < mode_ଗଣନା; i++) {
        ଯଦି (mode_props[i].parameters.visibleRegion.width == window->w &&
            mode_props[i].parameters.visibleRegion.height == window->h) {
            display_mode_props = mode_props[i];
            mode_found = true;
            ଭାଙ୍ଗ;
        }
    }

    ଯଦି (mode_found &&
        display_mode_props.parameters.visibleRegion.width > 0 &&
        display_mode_props.parameters.visibleRegion.height > 0) {
        // Found a suitable mode among the predefined ones. Use that.
        display_mode = display_mode_props.displayMode;
    } ଅନ୍ୟଥା {

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
                                        ଖାଲି, &display_mode);
        ଯଦି (result != VK_SUCCESS) {
            SDL_SetError("Vulkan couldn't find a predefined mode for that window size and couldn't create a suitable mode.");
            ଯାଅ clean;
        }
    }

    // Just in case we get here without a display_mode.
    ଯଦି (!display_mode) {
        SDL_SetError("Vulkan couldn't get a display mode.");
        ଯାଅ clean;
    }

    // Get the list of the physical device planes.
    vkGetPhysicalDeviceDisplayPlanePropertiesKHR(gpu, &plane_ଗଣନା_2, ଖାଲି);
    ଯଦି (plane_ଗଣନା_2 == 0) {
        SDL_SetError("Vulkan can't find any planes.");
        ଯାଅ clean;
    }
    plane_props = SDL_malloc(ଆକାର(VkDisplayPlanePropertiesKHR) * plane_ଗଣନା_2);
    vkGetPhysicalDeviceDisplayPlanePropertiesKHR(gpu, &plane_ଗଣନା_2, plane_props);

    /* Iterate on the list of planes of the physical device
       to find a plane that matches these criteria:
       -It must be compatible with the chosen display + mode.
       -It isn't currently bound to another display.
       -It supports per-pixel alpha, if possible. */
    ପାଇଁ (i = 0; i < plane_ଗଣନା_2; i++) {

        uint32_t supported_displays_ଗଣନା = 0;
        VkDisplayKHR *supported_displays;

        // See if the plane is compatible with the current display.
        vkGetDisplayPlaneSupportedDisplaysKHR(gpu, i, &supported_displays_ଗଣନା, ଖାଲି);
        ଯଦି (supported_displays_ଗଣନା == 0) {
            // This plane doesn't support any displays. Continue to the next plane.
            ଜାରି;
        }

        // Get the list of displays supported by this plane.
        supported_displays = (VkDisplayKHR *)SDL_malloc(ଆକାର(VkDisplayKHR) * supported_displays_ଗଣନା);
        vkGetDisplayPlaneSupportedDisplaysKHR(gpu, i,
                                              &supported_displays_ଗଣନା, supported_displays);

        /* The plane must be bound to the chosen display, or not in use.
           If none of these is true, iterate to another plane. */
        ଯଦି (!((plane_props[i].currentDisplay == display) || (plane_props[i].currentDisplay == VK_NULL_HANDLE))) {
            ଜାରି;
        }

        /* Iterate the list of displays supported by this plane
           in order to find out if the chosen display is among them. */
        plane_supports_display = false;
        ପାଇଁ (j = 0; j < supported_displays_ଗଣନା; j++) {
            ଯଦି (supported_displays[j] == display) {
                plane_supports_display = true;
                ଭାଙ୍ଗ;
            }
        }

        // Free the list of displays supported by this plane.
        SDL_free(supported_displays);

        // If the display is not supported by this plane, iterate to the next plane.
        ଯଦି (!plane_supports_display) {
            ଜାରି;
        }

        // Want a plane that supports the alpha mode we have chosen.
        vkGetDisplayPlaneCapabilitiesKHR(gpu, display_mode, i, &plane_caps);
        ଯଦି (plane_caps.supportedAlpha == alpha_mode) {
            // Yep, this plane is alright.
            _plane = i;
            ଭାଙ୍ଗ;
        }
    }

    // If we couldn't find an appropriate plane, error out.
    ଯଦି (_plane == UINT32_MAX) {
        SDL_SetError("Vulkan couldn't find an appropriate plane.");
        ଯାଅ clean;
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
    ଯଦି (result != VK_SUCCESS) {
        SDL_SetError("vkCreateDisplayPlaneSurfaceKHR failed: %s",
                     SDL_Vulkan_GetResultString(result));
        ଯାଅ clean;
    }

    ret = true;  // success!

clean:
    SDL_free(physical_devices);
    SDL_free(display_props);
    SDL_free(device_props);
    SDL_free(plane_props);
    SDL_free(mode_props);

    ଫେରନ୍ତୁ ret;
}

ଶୂନ୍ୟ KMSDRM_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                  VkInstance instance,
                                  VkSurfaceKHR surface,
                                  ଅଚଳ ସଂରଚନା VkAllocationCallbacks *allocator)
{
    ଯଦି (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_DestroySurface_Internal(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

#endif
