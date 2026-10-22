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

#అన్తర్భావ "SDL_internal.h"

#ఒకవేళ defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_KMSDRM)

#అన్తర్భావ "../SDL_vulkan_internal.h"

#అన్తర్భావ "SDL_kmsdrmvideo.h"
#అన్తర్భావ "SDL_kmsdrmdyn.h"
#అన్తర్భావ "SDL_kmsdrmvulkan.h"

#అన్తర్భావ <sys/ioctl.h>

#నిర్వచితమైతే SDL_PLATFORM_OPENBSD
#నిర్వచించు DEFAULT_VULKAN "libvulkan.so"
#లేకపోతే
#నిర్వచించు DEFAULT_VULKAN "libvulkan.so.1"
#అయితే_ముగింపు

SDL_ELF_NOTE_DLOPEN(
    "kmsdrm-vulkan",
    "Support for Vulkan on KMSDRM",
    SDL_ELF_NOTE_DLOPEN_ప్రాధాన్యత_SUGGESTED,
    DEFAULT_VULKAN
)

bool KMSDRM_Vulkan_ఎక్కించు_Library(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *మార్గం)
{
    VkExtensionProperties *extensions = ఖాళీ;
    Uint32 i, extension_లెక్క = 0;
    bool hasSurfaceExtension = false;
    bool hasDisplayExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = ఖాళీ;

    ఒకవేళ (_this->vulkan_config.loader_handle) {
        తిరిగి SDL_సమితి_Error("Vulkan already loaded");
    }

    // Load the Vulkan library
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

    SDL_strlcpy(_this->vulkan_config.loader_మార్గం, మార్గం,
                SDL_arraysize(_this->vulkan_config.loader_మార్గం));

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
        } లేకపోతే ఒకవేళ (SDL_strcmp(VK_KHR_DISPLAY_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasDisplayExtension = true;
        }
    }

    SDL_free(extensions);

    ఒకవేళ (!hasSurfaceExtension) {
        SDL_సమితి_Error("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        వెళ్ళు fail;
    } లేకపోతే ఒకవేళ (!hasDisplayExtension) {
        SDL_సమితి_Error("Installed Vulkan doesn't implement the " VK_KHR_DISPLAY_EXTENSION_NAME " extension");
        వెళ్ళు fail;
    }

    తిరిగి true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = ఖాళీ;
    తిరిగి false;
}

శూన్య KMSDRM_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    ఒకవేళ (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = ఖాళీ;
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
అక్షరం స్థిరరాశి * స్థిరరాశి *KMSDRM_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *లెక్క)
{
    స్థిర స్థిరరాశి అక్షరం *స్థిరరాశి extensionsForKMSDRM[] = {
        VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_DISPLAY_EXTENSION_NAME
    };
    *లెక్క = SDL_arraysize(extensionsForKMSDRM);
    తిరిగి extensionsForKMSDRM;
}

స్థిర పూర్ణాంకం SDLCALL display_బహుళకం_comparator(స్థిరరాశి శూన్య *a_opaque, స్థిరరాశి శూన్య *b_opaque)
{
    స్థిరరాశి Vk_Display_బహుళకం_Properties_KHR *a = a_opaque;
    స్థిరరాశి Vk_Display_బహుళకం_Properties_KHR *b = b_opaque;

    ఒకవేళ (a->parameters.refresh_రేటు_2 > b->parameters.refresh_రేటు_2)
        తిరిగి -1;
    లేకపోతే ఒకవేళ (a->parameters.refresh_రేటు_2 < b->parameters.refresh_రేటు_2)
        తిరిగి 1;
    లేకపోతే
        తిరిగి 0;
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
                                SDL_కిటికీ *కిటికీ,
                                VkInstance instance,
                                స్థిరరాశి నిర్మాణం Vk_కేటాయింపు_Callbacks *allocator,
                                VkSurfaceKHR *surface)
{
    VkPhysicalDevice gpu = ఖాళీ;
    uint32_t gpu_లెక్క;
    uint32_t display_లెక్క;
    uint32_t బహుళకం_లెక్క;
    uint32_t plane_లెక్క_2;
    uint32_t _plane = UINT32_MAX;

    VkPhysicalDevice *physical_devices = ఖాళీ;
    VkPhysicalDeviceProperties *device_props = ఖాళీ;
    VkDisplayPropertiesKHR *display_props = ఖాళీ;
    Vk_Display_బహుళకం_Properties_KHR *బహుళకం_props = ఖాళీ;
    VkDisplayPlanePropertiesKHR *plane_props = ఖాళీ;
    VkDisplayPlaneCapabilitiesKHR plane_caps;

    Vk_Display_బహుళకం_Create_Info_KHR display_బహుళకం_create_info;
    VkDisplaySurfaceCreateInfoKHR display_plane_surface_create_info;

    VkExtent2D image_కొలత_2;
    VkDisplayKHR display;
    Vk_Display_బహుళకం_KHR display_బహుళకం_2 = (Vk_Display_బహుళకం_KHR)0;
    Vk_Display_బహుళకం_Properties_KHR display_బహుళకం_props = { 0 };
    Vk_Display_బహుళకం_Parameters_KHR new_బహుళకం_parameters = { { 0, 0 }, 0 };
    // Prefer a plane that supports per-pixel alpha.
    Vk_Display_Plane_Alpha_Flag_బిట్లు_KHR alpha_బహుళకం_2 = VK_DISPLAY_PLANE_ALPHA_OPAQUE_బిట్టు_KHR;

    Vk_ఫలితం ఫలితం;
    bool ret = false;
    bool valid_gpu = false;
    bool బహుళకం_దొరికింది = false;
    bool plane_supports_display = false;

    // Get the display index from the display being used by the window.
    పూర్ణాంకం display_సూచీ = SDL_Get_Display_సూచీ(SDL_Get_Display_For_కిటికీ(కిటికీ));
    పూర్ణాంకం i, j;

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

    PFN_vk_Get_Display_బహుళకం_Properties_KHR vk_Get_Display_బహుళకం_Properties_KHR =
        (PFN_vk_Get_Display_బహుళకం_Properties_KHR)vkGetInstanceProcAddr(
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

    PFN_vk_Create_Display_బహుళకం_KHR vk_Create_Display_బహుళకం_KHR =
        (PFN_vk_Create_Display_బహుళకం_KHR)vkGetInstanceProcAddr(
            instance, "vkCreateDisplayModeKHR");

    ఒకవేళ (!_this->vulkan_config.loader_handle) {
        SDL_సమితి_Error("Vulkan is not loaded");
        వెళ్ళు clean;
    }

    /*************************************/
    // Block for vulkan surface creation
    /*************************************/

    /****************************************************************/
    // If we got vkCreateDisplayPlaneSurfaceKHR() pointer, it means
    // that the VK_KHR_Display extension is active on the instance.
    // That's the central extension we need for x-less VK!
    /****************************************************************/
    ఒకవేళ (!vkCreateDisplayPlaneSurfaceKHR) {
        SDL_సమితి_Error(VK_KHR_DISPLAY_EXTENSION_NAME
                     " extension is not enabled in the Vulkan instance.");
        వెళ్ళు clean;
    }

    /* A GPU (or physical_device, in vkcube terms) is a physical GPU.
       A machine with more than one video output doesn't need to have more than one GPU,
       like the Pi4 which has 1 GPU and 2 video outputs.
       Just in case, we test that the GPU we choose is Vulkan-capable.
       If there are new reports about VK init failures, hardcode
       gpu = physical_devices[0], instead of probing, and go with that.
    */

    // Get the physical device count.
    vkEnumeratePhysicalDevices(instance, &gpu_లెక్క, ఖాళీ);

    ఒకవేళ (gpu_లెక్క == 0) {
        SDL_సమితి_Error("Vulkan can't find physical devices (gpus).");
        వెళ్ళు clean;
    }

    // Get the physical devices.
    physical_devices = SDL_malloc(పరిమాణం(VkPhysicalDevice) * gpu_లెక్క);
    device_props = SDL_malloc(పరిమాణం(VkPhysicalDeviceProperties));
    vkEnumeratePhysicalDevices(instance, &gpu_లెక్క, physical_devices);

    // Iterate on the physical devices.
    కొరకు (i = 0; i < gpu_లెక్క; i++) {

        // Get the physical device properties.
        vkGetPhysicalDeviceProperties(
            physical_devices[i],
            device_props);

        // Is this device a real GPU that supports API version 1 at least?
        ఒకవేళ (device_props->api_సంస్కరణ >= 1 &&
            (device_props->deviceType == 1 || device_props->deviceType == 2)) {
            gpu = physical_devices[i];
            valid_gpu = true;
            ఆపు;
        }
    }

    ఒకవేళ (!valid_gpu) {
        SDL_సమితి_Error("Vulkan can't find a valid physical device (gpu).");
        వెళ్ళు clean;
    }

    /* A display is a video output. 1 GPU can have N displays.
       Vulkan only counts the connected displays.
       Get the display count of the GPU. */
    vkGetPhysicalDeviceDisplayPropertiesKHR(gpu, &display_లెక్క, ఖాళీ);
    ఒకవేళ (display_లెక్క == 0) {
        SDL_సమితి_Error("Vulkan can't find any displays.");
        వెళ్ళు clean;
    }

    // Get the props of the displays of the physical device.
    display_props = (VkDisplayPropertiesKHR *)SDL_malloc(display_లెక్క * పరిమాణం(*display_props));
    vkGetPhysicalDeviceDisplayPropertiesKHR(gpu,
                                            &display_లెక్క,
                                            display_props);

    // Get the chosen display based on the display index.
    display = display_props[display_సూచీ].display;

    // Get the list of the display videomodes.
    vk_Get_Display_బహుళకం_Properties_KHR(gpu,
                                  display,
                                  &బహుళకం_లెక్క, ఖాళీ);

    ఒకవేళ (బహుళకం_లెక్క == 0) {
        SDL_సమితి_Error("Vulkan can't find any video modes for display %i (%s)", 0,
                     display_props[display_సూచీ].displayName);
        వెళ్ళు clean;
    }

    బహుళకం_props = (Vk_Display_బహుళకం_Properties_KHR *)SDL_malloc(బహుళకం_లెక్క * పరిమాణం(*బహుళకం_props));
    vk_Get_Display_బహుళకం_Properties_KHR(gpu,
                                  display,
                                  &బహుళకం_లెక్క, బహుళకం_props);

    /* Sort the modes so that larger refresh rates come first. */
    SDL_qsort(బహుళకం_props, బహుళకం_లెక్క, పరిమాణం(*బహుళకం_props), display_బహుళకం_comparator);

    /* Get a video mode equal to the window size among the predefined ones,
       if possible.
       REMEMBER: We have to get a small enough videomode for the window size,
       because videomode determines how big the scanout region is and we can't
       scanout a region bigger than the window (we would be reading past the
       buffer, and Vulkan would give us a confusing VK_ERROR_SURFACE_LOST_KHR). */
    కొరకు (i = 0; i < బహుళకం_లెక్క; i++) {
        ఒకవేళ (బహుళకం_props[i].parameters.visibleRegion.వెడల్పు == కిటికీ->w &&
            బహుళకం_props[i].parameters.visibleRegion.ఎత్తు == కిటికీ->h) {
            display_బహుళకం_props = బహుళకం_props[i];
            బహుళకం_దొరికింది = true;
            ఆపు;
        }
    }

    ఒకవేళ (బహుళకం_దొరికింది &&
        display_బహుళకం_props.parameters.visibleRegion.వెడల్పు > 0 &&
        display_బహుళకం_props.parameters.visibleRegion.ఎత్తు > 0) {
        // Found a suitable mode among the predefined ones. Use that.
        display_బహుళకం_2 = display_బహుళకం_props.display_బహుళకం;
    } లేకపోతే {

        /* Couldn't find a suitable mode among the predefined ones, so try to create our own.
           This won't work for some video chips atm (like Pi's VideoCore) so these are limited
           to supported resolutions. Don't try to use "closest" resolutions either, because
           those are often bigger than the window size, thus causing out-of-bunds scanout. */
        new_బహుళకం_parameters.visibleRegion.వెడల్పు = కిటికీ->w;
        new_బహుళకం_parameters.visibleRegion.ఎత్తు = కిటికీ->h;
        /* SDL (and DRM, if we look at drmModeModeInfo vrefresh) uses plain integer Hz for
           display mode refresh rate, but Vulkan expects higher precision. */
        new_బహుళకం_parameters.refresh_రేటు_2 = (uint32_t)(కిటికీ->current_fullscreen_బహుళకం.refresh_రేటు * 1000);

        SDL_zero(display_బహుళకం_create_info);
        display_బహుళకం_create_info.sType = VK_STRUCTURE_TYPE_DISPLAY_బహుళకం_CREATE_INFO_KHR;
        display_బహుళకం_create_info.parameters = new_బహుళకం_parameters;
        ఫలితం = vk_Create_Display_బహుళకం_KHR(gpu,
                                        display,
                                        &display_బహుళకం_create_info,
                                        ఖాళీ, &display_బహుళకం_2);
        ఒకవేళ (ఫలితం != VK_SUCCESS) {
            SDL_సమితి_Error("Vulkan couldn't find a predefined mode for that window size and couldn't create a suitable mode.");
            వెళ్ళు clean;
        }
    }

    // Just in case we get here without a display_mode.
    ఒకవేళ (!display_బహుళకం_2) {
        SDL_సమితి_Error("Vulkan couldn't get a display mode.");
        వెళ్ళు clean;
    }

    // Get the list of the physical device planes.
    vkGetPhysicalDeviceDisplayPlanePropertiesKHR(gpu, &plane_లెక్క_2, ఖాళీ);
    ఒకవేళ (plane_లెక్క_2 == 0) {
        SDL_సమితి_Error("Vulkan can't find any planes.");
        వెళ్ళు clean;
    }
    plane_props = SDL_malloc(పరిమాణం(VkDisplayPlanePropertiesKHR) * plane_లెక్క_2);
    vkGetPhysicalDeviceDisplayPlanePropertiesKHR(gpu, &plane_లెక్క_2, plane_props);

    /* Iterate on the list of planes of the physical device
       to find a plane that matches these criteria:
       -It must be compatible with the chosen display + mode.
       -It isn't currently bound to another display.
       -It supports per-pixel alpha, if possible. */
    కొరకు (i = 0; i < plane_లెక్క_2; i++) {

        uint32_t supported_displays_లెక్క = 0;
        VkDisplayKHR *supported_displays;

        // See if the plane is compatible with the current display.
        vkGetDisplayPlaneSupportedDisplaysKHR(gpu, i, &supported_displays_లెక్క, ఖాళీ);
        ఒకవేళ (supported_displays_లెక్క == 0) {
            // This plane doesn't support any displays. Continue to the next plane.
            కొనసాగు;
        }

        // Get the list of displays supported by this plane.
        supported_displays = (VkDisplayKHR *)SDL_malloc(పరిమాణం(VkDisplayKHR) * supported_displays_లెక్క);
        vkGetDisplayPlaneSupportedDisplaysKHR(gpu, i,
                                              &supported_displays_లెక్క, supported_displays);

        /* The plane must be bound to the chosen display, or not in use.
           If none of these is true, iterate to another plane. */
        ఒకవేళ (!((plane_props[i].currentDisplay == display) || (plane_props[i].currentDisplay == VK_NULL_HANDLE))) {
            కొనసాగు;
        }

        /* Iterate the list of displays supported by this plane
           in order to find out if the chosen display is among them. */
        plane_supports_display = false;
        కొరకు (j = 0; j < supported_displays_లెక్క; j++) {
            ఒకవేళ (supported_displays[j] == display) {
                plane_supports_display = true;
                ఆపు;
            }
        }

        // Free the list of displays supported by this plane.
        SDL_free(supported_displays);

        // If the display is not supported by this plane, iterate to the next plane.
        ఒకవేళ (!plane_supports_display) {
            కొనసాగు;
        }

        // Want a plane that supports the alpha mode we have chosen.
        vkGetDisplayPlaneCapabilitiesKHR(gpu, display_బహుళకం_2, i, &plane_caps);
        ఒకవేళ (plane_caps.supportedAlpha == alpha_బహుళకం_2) {
            // Yep, this plane is alright.
            _plane = i;
            ఆపు;
        }
    }

    // If we couldn't find an appropriate plane, error out.
    ఒకవేళ (_plane == UINT32_MAX) {
        SDL_సమితి_Error("Vulkan couldn't find an appropriate plane.");
        వెళ్ళు clean;
    }

    /********************************************/
    // Let's finally create the Vulkan surface!
    /********************************************/

    image_కొలత_2.వెడల్పు = కిటికీ->w;
    image_కొలత_2.ఎత్తు = కిటికీ->h;

    SDL_zero(display_plane_surface_create_info);
    display_plane_surface_create_info.sType = VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR;
    display_plane_surface_create_info.display_బహుళకం = display_బహుళకం_2;
    display_plane_surface_create_info.plane_సూచీ = _plane;
    display_plane_surface_create_info.imageExtent = image_కొలత_2;
    display_plane_surface_create_info.transform = VK_SURFACE_TRANSFORM_తటస్థం_బిట్టు_KHR;
    display_plane_surface_create_info.alpha_బహుళకం = alpha_బహుళకం_2;
    ఫలితం = vkCreateDisplayPlaneSurfaceKHR(instance,
                                            &display_plane_surface_create_info,
                                            allocator,
                                            surface);
    ఒకవేళ (ఫలితం != VK_SUCCESS) {
        SDL_సమితి_Error("vkCreateDisplayPlaneSurfaceKHR failed: %s",
                     SDL_Vulkan_Get_ఫలితం_String(ఫలితం));
        వెళ్ళు clean;
    }

    ret = true;  // success!

clean:
    SDL_free(physical_devices);
    SDL_free(display_props);
    SDL_free(device_props);
    SDL_free(plane_props);
    SDL_free(బహుళకం_props);

    తిరిగి ret;
}

శూన్య KMSDRM_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                  VkInstance instance,
                                  VkSurfaceKHR surface,
                                  స్థిరరాశి నిర్మాణం Vk_కేటాయింపు_Callbacks *allocator)
{
    ఒకవేళ (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_Destroy_Surface_అంతర్గత(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

#అయితే_ముగింపు
