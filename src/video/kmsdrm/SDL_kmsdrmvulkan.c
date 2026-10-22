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

#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ಆದರೆ defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_KMSDRM)

#ಅನ್ತರ್ಭಾವ "../SDL_vulkan_internal.h"

#ಅನ್ತರ್ಭಾವ "SDL_kmsdrmvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_kmsdrmdyn.h"
#ಅನ್ತರ್ಭಾವ "SDL_kmsdrmvulkan.h"

#ಅನ್ತರ್ಭಾವ <sys/ioctl.h>

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_PLATFORM_OPENBSD
#ವ್ಯಾಖ್ಯಾನಿಸು DEFAULT_VULKAN "libvulkan.so"
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು DEFAULT_VULKAN "libvulkan.so.1"
#ಆದರೆ_ಅಂತ್ಯ

SDL_ELF_NOTE_DLOPEN(
    "kmsdrm-vulkan",
    "Support for Vulkan on KMSDRM",
    SDL_ELF_NOTE_DLOPEN_ಆದ್ಯತೆ_SUGGESTED,
    DEFAULT_VULKAN
)

bool KMSDRM_Vulkan_ತುಂಬು_Library(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಮಾರ್ಗ)
{
    VkExtensionProperties *extensions = ಖಾಲಿ;
    Uint32 i, extension_ಎಣಿಕೆ = 0;
    bool hasSurfaceExtension = false;
    bool hasDisplayExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = ಖಾಲಿ;

    ಆದರೆ (_this->vulkan_config.loader_handle) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Vulkan already loaded");
    }

    // Load the Vulkan library
    ಆದರೆ (!ಮಾರ್ಗ) {
        ಮಾರ್ಗ = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }
    ಆದರೆ (!ಮಾರ್ಗ) {
        ಮಾರ್ಗ = DEFAULT_VULKAN;
    }

    _this->vulkan_config.loader_handle = SDL_ತುಂಬು_Object(ಮಾರ್ಗ);

    ಆದರೆ (!_this->vulkan_config.loader_handle) {
        ಹಿಂತಿರುಗಿ false;
    }

    SDL_strlcpy(_this->vulkan_config.loader_ಮಾರ್ಗ, ಮಾರ್ಗ,
                SDL_arraysize(_this->vulkan_config.loader_ಮಾರ್ಗ));

    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)SDL_ತುಂಬು_Function(
        _this->vulkan_config.loader_handle, "vkGetInstanceProcAddr");

    ಆದರೆ (!vkGetInstanceProcAddr) {
        ಹೋಗು fail;
    }

    _this->vulkan_config.vkGetInstanceProcAddr = (ಶೂನ್ಯ *)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties =
        (ಶೂನ್ಯ *)((PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr)(
            VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties");

    ಆದರೆ (!_this->vulkan_config.vkEnumerateInstanceExtensionProperties) {
        ಹೋಗು fail;
    }

    extensions = SDL_Vulkan_CreateInstanceExtensionsList(
        (PFN_vkEnumerateInstanceExtensionProperties)
            _this->vulkan_config.vkEnumerateInstanceExtensionProperties,
        &extension_ಎಣಿಕೆ);

    ಆದರೆ (!extensions) {
        ಹೋಗು fail;
    }

    ಗಾಗಿ (i = 0; i < extension_ಎಣಿಕೆ; i++) {
        ಆದರೆ (SDL_strcmp(VK_KHR_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasSurfaceExtension = true;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(VK_KHR_DISPLAY_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasDisplayExtension = true;
        }
    }

    SDL_free(extensions);

    ಆದರೆ (!hasSurfaceExtension) {
        SDL_ಗಣ_Error("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        ಹೋಗು fail;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!hasDisplayExtension) {
        SDL_ಗಣ_Error("Installed Vulkan doesn't implement the " VK_KHR_DISPLAY_EXTENSION_NAME " extension");
        ಹೋಗು fail;
    }

    ಹಿಂತಿರುಗಿ true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = ಖಾಲಿ;
    ಹಿಂತಿರುಗಿ false;
}

ಶೂನ್ಯ KMSDRM_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    ಆದರೆ (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = ಖಾಲಿ;
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
ಅಕ್ಷರ ಸ್ಥಿರಾಂಕ * ಸ್ಥಿರಾಂಕ *KMSDRM_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *ಎಣಿಕೆ_2)
{
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸ್ಥಿರಾಂಕ extensionsForKMSDRM[] = {
        VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_DISPLAY_EXTENSION_NAME
    };
    *ಎಣಿಕೆ_2 = SDL_arraysize(extensionsForKMSDRM);
    ಹಿಂತಿರುಗಿ extensionsForKMSDRM;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ SDLCALL display_ಬಹುಲಕ_comparator(ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *a_opaque, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *b_opaque)
{
    ಸ್ಥಿರಾಂಕ Vk_Display_ಬಹುಲಕ_Properties_KHR *a = a_opaque;
    ಸ್ಥಿರಾಂಕ Vk_Display_ಬಹುಲಕ_Properties_KHR *b = b_opaque;

    ಆದರೆ (a->parameters.refresh_ದರ_2 > b->parameters.refresh_ದರ_2)
        ಹಿಂತಿರುಗಿ -1;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (a->parameters.refresh_ದರ_2 < b->parameters.refresh_ದರ_2)
        ಹಿಂತಿರುಗಿ 1;
    ಇಲ್ಲದಿದ್ದರೆ
        ಹಿಂತಿರುಗಿ 0;
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
                                SDL_ಕಿಟಕಿ *ಕಿಟಕಿ,
                                VkInstance instance,
                                ಸ್ಥಿರಾಂಕ ರಚನೆ Vk_ಹಂಚಿಕೆ_Callbacks *allocator,
                                VkSurfaceKHR *surface)
{
    VkPhysicalDevice gpu = ಖಾಲಿ;
    uint32_t gpu_ಎಣಿಕೆ;
    uint32_t display_ಎಣಿಕೆ;
    uint32_t ಬಹುಲಕ_ಎಣಿಕೆ;
    uint32_t plane_ಎಣಿಕೆ_2;
    uint32_t _plane = UINT32_MAX;

    VkPhysicalDevice *physical_devices = ಖಾಲಿ;
    VkPhysicalDeviceProperties *device_props = ಖಾಲಿ;
    VkDisplayPropertiesKHR *display_props = ಖಾಲಿ;
    Vk_Display_ಬಹುಲಕ_Properties_KHR *ಬಹುಲಕ_props = ಖಾಲಿ;
    VkDisplayPlanePropertiesKHR *plane_props = ಖಾಲಿ;
    VkDisplayPlaneCapabilitiesKHR plane_caps;

    Vk_Display_ಬಹುಲಕ_Create_Info_KHR display_ಬಹುಲಕ_create_info;
    VkDisplaySurfaceCreateInfoKHR display_plane_surface_create_info;

    VkExtent2D image_ಗಾತ್ರ_2;
    VkDisplayKHR display;
    Vk_Display_ಬಹುಲಕ_KHR display_ಬಹುಲಕ_2 = (Vk_Display_ಬಹುಲಕ_KHR)0;
    Vk_Display_ಬಹುಲಕ_Properties_KHR display_ಬಹುಲಕ_props = { 0 };
    Vk_Display_ಬಹುಲಕ_Parameters_KHR new_ಬಹುಲಕ_parameters = { { 0, 0 }, 0 };
    // Prefer a plane that supports per-pixel alpha.
    Vk_Display_Plane_Alpha_Flag_ಬಿಟ್ಟುಗಳು_KHR alpha_ಬಹುಲಕ_2 = VK_DISPLAY_PLANE_ALPHA_OPAQUE_ಬಿಟ್_KHR;

    Vk_ಫಲಿತಾಂಶ ಫಲಿತಾಂಶ;
    bool ret = false;
    bool valid_gpu = false;
    bool ಬಹುಲಕ_ಸಿಕ್ಕಿತು = false;
    bool plane_supports_display = false;

    // Get the display index from the display being used by the window.
    ಪೂರ್ಣಾಂಕ display_ಸೂಚ್ಯಂಕ = SDL_Get_Display_ಸೂಚ್ಯಂಕ(SDL_Get_Display_For_ಕಿಟಕಿ(ಕಿಟಕಿ));
    ಪೂರ್ಣಾಂಕ i, j;

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

    PFN_vk_Get_Display_ಬಹುಲಕ_Properties_KHR vk_Get_Display_ಬಹುಲಕ_Properties_KHR =
        (PFN_vk_Get_Display_ಬಹುಲಕ_Properties_KHR)vkGetInstanceProcAddr(
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

    PFN_vk_Create_Display_ಬಹುಲಕ_KHR vk_Create_Display_ಬಹುಲಕ_KHR =
        (PFN_vk_Create_Display_ಬಹುಲಕ_KHR)vkGetInstanceProcAddr(
            instance, "vkCreateDisplayModeKHR");

    ಆದರೆ (!_this->vulkan_config.loader_handle) {
        SDL_ಗಣ_Error("Vulkan is not loaded");
        ಹೋಗು clean;
    }

    /*************************************/
    // Block for vulkan surface creation
    /*************************************/

    /****************************************************************/
    // If we got vkCreateDisplayPlaneSurfaceKHR() pointer, it means
    // that the VK_KHR_Display extension is active on the instance.
    // That's the central extension we need for x-less VK!
    /****************************************************************/
    ಆದರೆ (!vkCreateDisplayPlaneSurfaceKHR) {
        SDL_ಗಣ_Error(VK_KHR_DISPLAY_EXTENSION_NAME
                     " extension is not enabled in the Vulkan instance.");
        ಹೋಗು clean;
    }

    /* A GPU (or physical_device, in vkcube terms) is a physical GPU.
       A machine with more than one video output doesn't need to have more than one GPU,
       like the Pi4 which has 1 GPU and 2 video outputs.
       Just in case, we test that the GPU we choose is Vulkan-capable.
       If there are new reports about VK init failures, hardcode
       gpu = physical_devices[0], instead of probing, and go with that.
    */

    // Get the physical device count.
    vkEnumeratePhysicalDevices(instance, &gpu_ಎಣಿಕೆ, ಖಾಲಿ);

    ಆದರೆ (gpu_ಎಣಿಕೆ == 0) {
        SDL_ಗಣ_Error("Vulkan can't find physical devices (gpus).");
        ಹೋಗು clean;
    }

    // Get the physical devices.
    physical_devices = SDL_malloc(ಗಾತ್ರ(VkPhysicalDevice) * gpu_ಎಣಿಕೆ);
    device_props = SDL_malloc(ಗಾತ್ರ(VkPhysicalDeviceProperties));
    vkEnumeratePhysicalDevices(instance, &gpu_ಎಣಿಕೆ, physical_devices);

    // Iterate on the physical devices.
    ಗಾಗಿ (i = 0; i < gpu_ಎಣಿಕೆ; i++) {

        // Get the physical device properties.
        vkGetPhysicalDeviceProperties(
            physical_devices[i],
            device_props);

        // Is this device a real GPU that supports API version 1 at least?
        ಆದರೆ (device_props->api_ಆವೃತ್ತಿ >= 1 &&
            (device_props->deviceType == 1 || device_props->deviceType == 2)) {
            gpu = physical_devices[i];
            valid_gpu = true;
            ನಿಲ್ಲಿಸು;
        }
    }

    ಆದರೆ (!valid_gpu) {
        SDL_ಗಣ_Error("Vulkan can't find a valid physical device (gpu).");
        ಹೋಗು clean;
    }

    /* A display is a video output. 1 GPU can have N displays.
       Vulkan only counts the connected displays.
       Get the display count of the GPU. */
    vkGetPhysicalDeviceDisplayPropertiesKHR(gpu, &display_ಎಣಿಕೆ, ಖಾಲಿ);
    ಆದರೆ (display_ಎಣಿಕೆ == 0) {
        SDL_ಗಣ_Error("Vulkan can't find any displays.");
        ಹೋಗು clean;
    }

    // Get the props of the displays of the physical device.
    display_props = (VkDisplayPropertiesKHR *)SDL_malloc(display_ಎಣಿಕೆ * ಗಾತ್ರ(*display_props));
    vkGetPhysicalDeviceDisplayPropertiesKHR(gpu,
                                            &display_ಎಣಿಕೆ,
                                            display_props);

    // Get the chosen display based on the display index.
    display = display_props[display_ಸೂಚ್ಯಂಕ].display;

    // Get the list of the display videomodes.
    vk_Get_Display_ಬಹುಲಕ_Properties_KHR(gpu,
                                  display,
                                  &ಬಹುಲಕ_ಎಣಿಕೆ, ಖಾಲಿ);

    ಆದರೆ (ಬಹುಲಕ_ಎಣಿಕೆ == 0) {
        SDL_ಗಣ_Error("Vulkan can't find any video modes for display %i (%s)", 0,
                     display_props[display_ಸೂಚ್ಯಂಕ].displayName);
        ಹೋಗು clean;
    }

    ಬಹುಲಕ_props = (Vk_Display_ಬಹುಲಕ_Properties_KHR *)SDL_malloc(ಬಹುಲಕ_ಎಣಿಕೆ * ಗಾತ್ರ(*ಬಹುಲಕ_props));
    vk_Get_Display_ಬಹುಲಕ_Properties_KHR(gpu,
                                  display,
                                  &ಬಹುಲಕ_ಎಣಿಕೆ, ಬಹುಲಕ_props);

    /* Sort the modes so that larger refresh rates come first. */
    SDL_qsort(ಬಹುಲಕ_props, ಬಹುಲಕ_ಎಣಿಕೆ, ಗಾತ್ರ(*ಬಹುಲಕ_props), display_ಬಹುಲಕ_comparator);

    /* Get a video mode equal to the window size among the predefined ones,
       if possible.
       REMEMBER: We have to get a small enough videomode for the window size,
       because videomode determines how big the scanout region is and we can't
       scanout a region bigger than the window (we would be reading past the
       buffer, and Vulkan would give us a confusing VK_ERROR_SURFACE_LOST_KHR). */
    ಗಾಗಿ (i = 0; i < ಬಹುಲಕ_ಎಣಿಕೆ; i++) {
        ಆದರೆ (ಬಹುಲಕ_props[i].parameters.visibleRegion.ಅಗಲ == ಕಿಟಕಿ->w &&
            ಬಹುಲಕ_props[i].parameters.visibleRegion.ಎತ್ತರ == ಕಿಟಕಿ->h) {
            display_ಬಹುಲಕ_props = ಬಹುಲಕ_props[i];
            ಬಹುಲಕ_ಸಿಕ್ಕಿತು = true;
            ನಿಲ್ಲಿಸು;
        }
    }

    ಆದರೆ (ಬಹುಲಕ_ಸಿಕ್ಕಿತು &&
        display_ಬಹುಲಕ_props.parameters.visibleRegion.ಅಗಲ > 0 &&
        display_ಬಹುಲಕ_props.parameters.visibleRegion.ಎತ್ತರ > 0) {
        // Found a suitable mode among the predefined ones. Use that.
        display_ಬಹುಲಕ_2 = display_ಬಹುಲಕ_props.display_ಬಹುಲಕ;
    } ಇಲ್ಲದಿದ್ದರೆ {

        /* Couldn't find a suitable mode among the predefined ones, so try to create our own.
           This won't work for some video chips atm (like Pi's VideoCore) so these are limited
           to supported resolutions. Don't try to use "closest" resolutions either, because
           those are often bigger than the window size, thus causing out-of-bunds scanout. */
        new_ಬಹುಲಕ_parameters.visibleRegion.ಅಗಲ = ಕಿಟಕಿ->w;
        new_ಬಹುಲಕ_parameters.visibleRegion.ಎತ್ತರ = ಕಿಟಕಿ->h;
        /* SDL (and DRM, if we look at drmModeModeInfo vrefresh) uses plain integer Hz for
           display mode refresh rate, but Vulkan expects higher precision. */
        new_ಬಹುಲಕ_parameters.refresh_ದರ_2 = (uint32_t)(ಕಿಟಕಿ->current_fullscreen_ಬಹುಲಕ.refresh_ದರ * 1000);

        SDL_zero(display_ಬಹುಲಕ_create_info);
        display_ಬಹುಲಕ_create_info.sType = VK_STRUCTURE_TYPE_DISPLAY_ಬಹುಲಕ_CREATE_INFO_KHR;
        display_ಬಹುಲಕ_create_info.parameters = new_ಬಹುಲಕ_parameters;
        ಫಲಿತಾಂಶ = vk_Create_Display_ಬಹುಲಕ_KHR(gpu,
                                        display,
                                        &display_ಬಹುಲಕ_create_info,
                                        ಖಾಲಿ, &display_ಬಹುಲಕ_2);
        ಆದರೆ (ಫಲಿತಾಂಶ != VK_SUCCESS) {
            SDL_ಗಣ_Error("Vulkan couldn't find a predefined mode for that window size and couldn't create a suitable mode.");
            ಹೋಗು clean;
        }
    }

    // Just in case we get here without a display_mode.
    ಆದರೆ (!display_ಬಹುಲಕ_2) {
        SDL_ಗಣ_Error("Vulkan couldn't get a display mode.");
        ಹೋಗು clean;
    }

    // Get the list of the physical device planes.
    vkGetPhysicalDeviceDisplayPlanePropertiesKHR(gpu, &plane_ಎಣಿಕೆ_2, ಖಾಲಿ);
    ಆದರೆ (plane_ಎಣಿಕೆ_2 == 0) {
        SDL_ಗಣ_Error("Vulkan can't find any planes.");
        ಹೋಗು clean;
    }
    plane_props = SDL_malloc(ಗಾತ್ರ(VkDisplayPlanePropertiesKHR) * plane_ಎಣಿಕೆ_2);
    vkGetPhysicalDeviceDisplayPlanePropertiesKHR(gpu, &plane_ಎಣಿಕೆ_2, plane_props);

    /* Iterate on the list of planes of the physical device
       to find a plane that matches these criteria:
       -It must be compatible with the chosen display + mode.
       -It isn't currently bound to another display.
       -It supports per-pixel alpha, if possible. */
    ಗಾಗಿ (i = 0; i < plane_ಎಣಿಕೆ_2; i++) {

        uint32_t supported_displays_ಎಣಿಕೆ = 0;
        VkDisplayKHR *supported_displays;

        // See if the plane is compatible with the current display.
        vkGetDisplayPlaneSupportedDisplaysKHR(gpu, i, &supported_displays_ಎಣಿಕೆ, ಖಾಲಿ);
        ಆದರೆ (supported_displays_ಎಣಿಕೆ == 0) {
            // This plane doesn't support any displays. Continue to the next plane.
            ಮುಂದುವರಿ;
        }

        // Get the list of displays supported by this plane.
        supported_displays = (VkDisplayKHR *)SDL_malloc(ಗಾತ್ರ(VkDisplayKHR) * supported_displays_ಎಣಿಕೆ);
        vkGetDisplayPlaneSupportedDisplaysKHR(gpu, i,
                                              &supported_displays_ಎಣಿಕೆ, supported_displays);

        /* The plane must be bound to the chosen display, or not in use.
           If none of these is true, iterate to another plane. */
        ಆದರೆ (!((plane_props[i].currentDisplay == display) || (plane_props[i].currentDisplay == VK_NULL_HANDLE))) {
            ಮುಂದುವರಿ;
        }

        /* Iterate the list of displays supported by this plane
           in order to find out if the chosen display is among them. */
        plane_supports_display = false;
        ಗಾಗಿ (j = 0; j < supported_displays_ಎಣಿಕೆ; j++) {
            ಆದರೆ (supported_displays[j] == display) {
                plane_supports_display = true;
                ನಿಲ್ಲಿಸು;
            }
        }

        // Free the list of displays supported by this plane.
        SDL_free(supported_displays);

        // If the display is not supported by this plane, iterate to the next plane.
        ಆದರೆ (!plane_supports_display) {
            ಮುಂದುವರಿ;
        }

        // Want a plane that supports the alpha mode we have chosen.
        vkGetDisplayPlaneCapabilitiesKHR(gpu, display_ಬಹುಲಕ_2, i, &plane_caps);
        ಆದರೆ (plane_caps.supportedAlpha == alpha_ಬಹುಲಕ_2) {
            // Yep, this plane is alright.
            _plane = i;
            ನಿಲ್ಲಿಸು;
        }
    }

    // If we couldn't find an appropriate plane, error out.
    ಆದರೆ (_plane == UINT32_MAX) {
        SDL_ಗಣ_Error("Vulkan couldn't find an appropriate plane.");
        ಹೋಗು clean;
    }

    /********************************************/
    // Let's finally create the Vulkan surface!
    /********************************************/

    image_ಗಾತ್ರ_2.ಅಗಲ = ಕಿಟಕಿ->w;
    image_ಗಾತ್ರ_2.ಎತ್ತರ = ಕಿಟಕಿ->h;

    SDL_zero(display_plane_surface_create_info);
    display_plane_surface_create_info.sType = VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR;
    display_plane_surface_create_info.display_ಬಹುಲಕ = display_ಬಹುಲಕ_2;
    display_plane_surface_create_info.plane_ಸೂಚ್ಯಂಕ = _plane;
    display_plane_surface_create_info.imageExtent = image_ಗಾತ್ರ_2;
    display_plane_surface_create_info.transform = VK_SURFACE_TRANSFORM_ತಟಸ್ಥ_ಬಿಟ್_KHR;
    display_plane_surface_create_info.alpha_ಬಹುಲಕ = alpha_ಬಹುಲಕ_2;
    ಫಲಿತಾಂಶ = vkCreateDisplayPlaneSurfaceKHR(instance,
                                            &display_plane_surface_create_info,
                                            allocator,
                                            surface);
    ಆದರೆ (ಫಲಿತಾಂಶ != VK_SUCCESS) {
        SDL_ಗಣ_Error("vkCreateDisplayPlaneSurfaceKHR failed: %s",
                     SDL_Vulkan_Get_ಫಲಿತಾಂಶ_String(ಫಲಿತಾಂಶ));
        ಹೋಗು clean;
    }

    ret = true;  // success!

clean:
    SDL_free(physical_devices);
    SDL_free(display_props);
    SDL_free(device_props);
    SDL_free(plane_props);
    SDL_free(ಬಹುಲಕ_props);

    ಹಿಂತಿರುಗಿ ret;
}

ಶೂನ್ಯ KMSDRM_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                  VkInstance instance,
                                  VkSurfaceKHR surface,
                                  ಸ್ಥಿರಾಂಕ ರಚನೆ Vk_ಹಂಚಿಕೆ_Callbacks *allocator)
{
    ಆದರೆ (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_Destroy_Surface_ಆಂತರಿಕ(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

#ಆದರೆ_ಅಂತ್ಯ
