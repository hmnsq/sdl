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

#ضمن "SDL_internal.h"

#إذا defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_KMSDRM)

#ضمن "../SDL_vulkan_internal.h"

#ضمن "SDL_kmsdrmvideo.h"
#ضمن "SDL_kmsdrmdyn.h"
#ضمن "SDL_kmsdrmvulkan.h"

#ضمن <sys/ioctl.h>

#جيڪڏهن_وصف_ٿيل SDL_PLATFORM_OPENBSD
#وصف_ڪريو DEFAULT_VULKAN "libvulkan.so"
#وإلا
#وصف_ڪريو DEFAULT_VULKAN "libvulkan.so.1"
#جيڪڏهن_پورو

SDL_ELF_NOTE_DLOPEN(
    "kmsdrm-vulkan",
    "Support for Vulkan on KMSDRM",
    SDL_ELF_NOTE_DLOPEN_ترجيح_SUGGESTED,
    DEFAULT_VULKAN
)

bool KMSDRM_Vulkan_ڀريو_Library(SDL_VideoDevice *_this, ثابت حرف *رستو)
{
    VkExtensionProperties *extensions = عدم;
    Uint32 i, extension_ڳڻپ = 0;
    bool hasSurfaceExtension = false;
    bool hasDisplayExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = عدم;

    إذا (_this->vulkan_config.loader_handle) {
        أرجع SDL_سيٽ_Error("Vulkan already loaded");
    }

    // Load the Vulkan library
    إذا (!رستو) {
        رستو = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }
    إذا (!رستو) {
        رستو = DEFAULT_VULKAN;
    }

    _this->vulkan_config.loader_handle = SDL_ڀريو_Object(رستو);

    إذا (!_this->vulkan_config.loader_handle) {
        أرجع false;
    }

    SDL_strlcpy(_this->vulkan_config.loader_رستو, رستو,
                SDL_arraysize(_this->vulkan_config.loader_رستو));

    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)SDL_ڀريو_Function(
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
        &extension_ڳڻپ);

    إذا (!extensions) {
        اذهب fail;
    }

    لكل (i = 0; i < extension_ڳڻپ; i++) {
        إذا (SDL_strcmp(VK_KHR_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasSurfaceExtension = true;
        } وإلا إذا (SDL_strcmp(VK_KHR_DISPLAY_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasDisplayExtension = true;
        }
    }

    SDL_free(extensions);

    إذا (!hasSurfaceExtension) {
        SDL_سيٽ_Error("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        اذهب fail;
    } وإلا إذا (!hasDisplayExtension) {
        SDL_سيٽ_Error("Installed Vulkan doesn't implement the " VK_KHR_DISPLAY_EXTENSION_NAME " extension");
        اذهب fail;
    }

    أرجع true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = عدم;
    أرجع false;
}

فراغ KMSDRM_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    إذا (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = عدم;
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
حرف ثابت * ثابت *KMSDRM_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *ڳڻپ)
{
    ساكن ثابت حرف *ثابت extensionsForKMSDRM[] = {
        VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_DISPLAY_EXTENSION_NAME
    };
    *ڳڻپ = SDL_arraysize(extensionsForKMSDRM);
    أرجع extensionsForKMSDRM;
}

ساكن صحيح SDLCALL display_گهڻائي_comparator(ثابت فراغ *a_opaque, ثابت فراغ *b_opaque)
{
    ثابت Vk_Display_گهڻائي_Properties_KHR *a = a_opaque;
    ثابت Vk_Display_گهڻائي_Properties_KHR *b = b_opaque;

    إذا (a->parameters.refresh_شرح_2 > b->parameters.refresh_شرح_2)
        أرجع -1;
    وإلا إذا (a->parameters.refresh_شرح_2 < b->parameters.refresh_شرح_2)
        أرجع 1;
    وإلا
        أرجع 0;
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
                                SDL_دري *دري,
                                VkInstance instance,
                                ثابت بنية Vk_ورهاست_Callbacks *allocator,
                                VkSurfaceKHR *surface)
{
    VkPhysicalDevice gpu = عدم;
    uint32_t gpu_ڳڻپ;
    uint32_t display_ڳڻپ;
    uint32_t گهڻائي_ڳڻپ;
    uint32_t plane_ڳڻپ_2;
    uint32_t _plane = UINT32_MAX;

    VkPhysicalDevice *physical_devices = عدم;
    VkPhysicalDeviceProperties *device_props = عدم;
    VkDisplayPropertiesKHR *display_props = عدم;
    Vk_Display_گهڻائي_Properties_KHR *گهڻائي_props = عدم;
    VkDisplayPlanePropertiesKHR *plane_props = عدم;
    VkDisplayPlaneCapabilitiesKHR plane_caps;

    Vk_Display_گهڻائي_Create_Info_KHR display_گهڻائي_create_info;
    VkDisplaySurfaceCreateInfoKHR display_plane_surface_create_info;

    VkExtent2D image_سائيز_2;
    VkDisplayKHR display;
    Vk_Display_گهڻائي_KHR display_گهڻائي_2 = (Vk_Display_گهڻائي_KHR)0;
    Vk_Display_گهڻائي_Properties_KHR display_گهڻائي_props = { 0 };
    Vk_Display_گهڻائي_Parameters_KHR new_گهڻائي_parameters = { { 0, 0 }, 0 };
    // Prefer a plane that supports per-pixel alpha.
    Vk_Display_Plane_Alpha_Flag_بٽ_KHR alpha_گهڻائي_2 = VK_DISPLAY_PLANE_ALPHA_OPAQUE_ٻٽو_انگ_KHR;

    Vk_نتيجو نتيجو;
    bool ret = false;
    bool valid_gpu = false;
    bool گهڻائي_مليو = false;
    bool plane_supports_display = false;

    // Get the display index from the display being used by the window.
    صحيح display_اشاريو = SDL_Get_Display_اشاريو(SDL_Get_Display_For_دري(دري));
    صحيح i, j;

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

    PFN_vk_Get_Display_گهڻائي_Properties_KHR vk_Get_Display_گهڻائي_Properties_KHR =
        (PFN_vk_Get_Display_گهڻائي_Properties_KHR)vkGetInstanceProcAddr(
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

    PFN_vk_Create_Display_گهڻائي_KHR vk_Create_Display_گهڻائي_KHR =
        (PFN_vk_Create_Display_گهڻائي_KHR)vkGetInstanceProcAddr(
            instance, "vkCreateDisplayModeKHR");

    إذا (!_this->vulkan_config.loader_handle) {
        SDL_سيٽ_Error("Vulkan is not loaded");
        اذهب clean;
    }

    /*************************************/
    // Block for vulkan surface creation
    /*************************************/

    /****************************************************************/
    // If we got vkCreateDisplayPlaneSurfaceKHR() pointer, it means
    // that the VK_KHR_Display extension is active on the instance.
    // That's the central extension we need for x-less VK!
    /****************************************************************/
    إذا (!vkCreateDisplayPlaneSurfaceKHR) {
        SDL_سيٽ_Error(VK_KHR_DISPLAY_EXTENSION_NAME
                     " extension is not enabled in the Vulkan instance.");
        اذهب clean;
    }

    /* A GPU (or physical_device, in vkcube terms) is a physical GPU.
       A machine with more than one video output doesn't need to have more than one GPU,
       like the Pi4 which has 1 GPU and 2 video outputs.
       Just in case, we test that the GPU we choose is Vulkan-capable.
       If there are new reports about VK init failures, hardcode
       gpu = physical_devices[0], instead of probing, and go with that.
    */

    // Get the physical device count.
    vkEnumeratePhysicalDevices(instance, &gpu_ڳڻپ, عدم);

    إذا (gpu_ڳڻپ == 0) {
        SDL_سيٽ_Error("Vulkan can't find physical devices (gpus).");
        اذهب clean;
    }

    // Get the physical devices.
    physical_devices = SDL_malloc(حجم(VkPhysicalDevice) * gpu_ڳڻپ);
    device_props = SDL_malloc(حجم(VkPhysicalDeviceProperties));
    vkEnumeratePhysicalDevices(instance, &gpu_ڳڻپ, physical_devices);

    // Iterate on the physical devices.
    لكل (i = 0; i < gpu_ڳڻپ; i++) {

        // Get the physical device properties.
        vkGetPhysicalDeviceProperties(
            physical_devices[i],
            device_props);

        // Is this device a real GPU that supports API version 1 at least?
        إذا (device_props->api_نسخو >= 1 &&
            (device_props->deviceType == 1 || device_props->deviceType == 2)) {
            gpu = physical_devices[i];
            valid_gpu = true;
            اكسر;
        }
    }

    إذا (!valid_gpu) {
        SDL_سيٽ_Error("Vulkan can't find a valid physical device (gpu).");
        اذهب clean;
    }

    /* A display is a video output. 1 GPU can have N displays.
       Vulkan only counts the connected displays.
       Get the display count of the GPU. */
    vkGetPhysicalDeviceDisplayPropertiesKHR(gpu, &display_ڳڻپ, عدم);
    إذا (display_ڳڻپ == 0) {
        SDL_سيٽ_Error("Vulkan can't find any displays.");
        اذهب clean;
    }

    // Get the props of the displays of the physical device.
    display_props = (VkDisplayPropertiesKHR *)SDL_malloc(display_ڳڻپ * حجم(*display_props));
    vkGetPhysicalDeviceDisplayPropertiesKHR(gpu,
                                            &display_ڳڻپ,
                                            display_props);

    // Get the chosen display based on the display index.
    display = display_props[display_اشاريو].display;

    // Get the list of the display videomodes.
    vk_Get_Display_گهڻائي_Properties_KHR(gpu,
                                  display,
                                  &گهڻائي_ڳڻپ, عدم);

    إذا (گهڻائي_ڳڻپ == 0) {
        SDL_سيٽ_Error("Vulkan can't find any video modes for display %i (%s)", 0,
                     display_props[display_اشاريو].displayName);
        اذهب clean;
    }

    گهڻائي_props = (Vk_Display_گهڻائي_Properties_KHR *)SDL_malloc(گهڻائي_ڳڻپ * حجم(*گهڻائي_props));
    vk_Get_Display_گهڻائي_Properties_KHR(gpu,
                                  display,
                                  &گهڻائي_ڳڻپ, گهڻائي_props);

    /* Sort the modes so that larger refresh rates come first. */
    SDL_qsort(گهڻائي_props, گهڻائي_ڳڻپ, حجم(*گهڻائي_props), display_گهڻائي_comparator);

    /* Get a video mode equal to the window size among the predefined ones,
       if possible.
       REMEMBER: We have to get a small enough videomode for the window size,
       because videomode determines how big the scanout region is and we can't
       scanout a region bigger than the window (we would be reading past the
       buffer, and Vulkan would give us a confusing VK_ERROR_SURFACE_LOST_KHR). */
    لكل (i = 0; i < گهڻائي_ڳڻپ; i++) {
        إذا (گهڻائي_props[i].parameters.visibleRegion.ويڪر == دري->w &&
            گهڻائي_props[i].parameters.visibleRegion.اوچائي == دري->h) {
            display_گهڻائي_props = گهڻائي_props[i];
            گهڻائي_مليو = true;
            اكسر;
        }
    }

    إذا (گهڻائي_مليو &&
        display_گهڻائي_props.parameters.visibleRegion.ويڪر > 0 &&
        display_گهڻائي_props.parameters.visibleRegion.اوچائي > 0) {
        // Found a suitable mode among the predefined ones. Use that.
        display_گهڻائي_2 = display_گهڻائي_props.display_گهڻائي;
    } وإلا {

        /* Couldn't find a suitable mode among the predefined ones, so try to create our own.
           This won't work for some video chips atm (like Pi's VideoCore) so these are limited
           to supported resolutions. Don't try to use "closest" resolutions either, because
           those are often bigger than the window size, thus causing out-of-bunds scanout. */
        new_گهڻائي_parameters.visibleRegion.ويڪر = دري->w;
        new_گهڻائي_parameters.visibleRegion.اوچائي = دري->h;
        /* SDL (and DRM, if we look at drmModeModeInfo vrefresh) uses plain integer Hz for
           display mode refresh rate, but Vulkan expects higher precision. */
        new_گهڻائي_parameters.refresh_شرح_2 = (uint32_t)(دري->current_fullscreen_گهڻائي.refresh_شرح * 1000);

        SDL_zero(display_گهڻائي_create_info);
        display_گهڻائي_create_info.sType = VK_STRUCTURE_TYPE_DISPLAY_گهڻائي_CREATE_INFO_KHR;
        display_گهڻائي_create_info.parameters = new_گهڻائي_parameters;
        نتيجو = vk_Create_Display_گهڻائي_KHR(gpu,
                                        display,
                                        &display_گهڻائي_create_info,
                                        عدم, &display_گهڻائي_2);
        إذا (نتيجو != VK_SUCCESS) {
            SDL_سيٽ_Error("Vulkan couldn't find a predefined mode for that window size and couldn't create a suitable mode.");
            اذهب clean;
        }
    }

    // Just in case we get here without a display_mode.
    إذا (!display_گهڻائي_2) {
        SDL_سيٽ_Error("Vulkan couldn't get a display mode.");
        اذهب clean;
    }

    // Get the list of the physical device planes.
    vkGetPhysicalDeviceDisplayPlanePropertiesKHR(gpu, &plane_ڳڻپ_2, عدم);
    إذا (plane_ڳڻپ_2 == 0) {
        SDL_سيٽ_Error("Vulkan can't find any planes.");
        اذهب clean;
    }
    plane_props = SDL_malloc(حجم(VkDisplayPlanePropertiesKHR) * plane_ڳڻپ_2);
    vkGetPhysicalDeviceDisplayPlanePropertiesKHR(gpu, &plane_ڳڻپ_2, plane_props);

    /* Iterate on the list of planes of the physical device
       to find a plane that matches these criteria:
       -It must be compatible with the chosen display + mode.
       -It isn't currently bound to another display.
       -It supports per-pixel alpha, if possible. */
    لكل (i = 0; i < plane_ڳڻپ_2; i++) {

        uint32_t supported_displays_ڳڻپ = 0;
        VkDisplayKHR *supported_displays;

        // See if the plane is compatible with the current display.
        vkGetDisplayPlaneSupportedDisplaysKHR(gpu, i, &supported_displays_ڳڻپ, عدم);
        إذا (supported_displays_ڳڻپ == 0) {
            // This plane doesn't support any displays. Continue to the next plane.
            استمر;
        }

        // Get the list of displays supported by this plane.
        supported_displays = (VkDisplayKHR *)SDL_malloc(حجم(VkDisplayKHR) * supported_displays_ڳڻپ);
        vkGetDisplayPlaneSupportedDisplaysKHR(gpu, i,
                                              &supported_displays_ڳڻپ, supported_displays);

        /* The plane must be bound to the chosen display, or not in use.
           If none of these is true, iterate to another plane. */
        إذا (!((plane_props[i].currentDisplay == display) || (plane_props[i].currentDisplay == VK_NULL_HANDLE))) {
            استمر;
        }

        /* Iterate the list of displays supported by this plane
           in order to find out if the chosen display is among them. */
        plane_supports_display = false;
        لكل (j = 0; j < supported_displays_ڳڻپ; j++) {
            إذا (supported_displays[j] == display) {
                plane_supports_display = true;
                اكسر;
            }
        }

        // Free the list of displays supported by this plane.
        SDL_free(supported_displays);

        // If the display is not supported by this plane, iterate to the next plane.
        إذا (!plane_supports_display) {
            استمر;
        }

        // Want a plane that supports the alpha mode we have chosen.
        vkGetDisplayPlaneCapabilitiesKHR(gpu, display_گهڻائي_2, i, &plane_caps);
        إذا (plane_caps.supportedAlpha == alpha_گهڻائي_2) {
            // Yep, this plane is alright.
            _plane = i;
            اكسر;
        }
    }

    // If we couldn't find an appropriate plane, error out.
    إذا (_plane == UINT32_MAX) {
        SDL_سيٽ_Error("Vulkan couldn't find an appropriate plane.");
        اذهب clean;
    }

    /********************************************/
    // Let's finally create the Vulkan surface!
    /********************************************/

    image_سائيز_2.ويڪر = دري->w;
    image_سائيز_2.اوچائي = دري->h;

    SDL_zero(display_plane_surface_create_info);
    display_plane_surface_create_info.sType = VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR;
    display_plane_surface_create_info.display_گهڻائي = display_گهڻائي_2;
    display_plane_surface_create_info.plane_اشاريو = _plane;
    display_plane_surface_create_info.imageExtent = image_سائيز_2;
    display_plane_surface_create_info.transform = VK_SURFACE_TRANSFORM_سڃاڻپ_عنصر_ٻٽو_انگ_KHR;
    display_plane_surface_create_info.alpha_گهڻائي = alpha_گهڻائي_2;
    نتيجو = vkCreateDisplayPlaneSurfaceKHR(instance,
                                            &display_plane_surface_create_info,
                                            allocator,
                                            surface);
    إذا (نتيجو != VK_SUCCESS) {
        SDL_سيٽ_Error("vkCreateDisplayPlaneSurfaceKHR failed: %s",
                     SDL_Vulkan_Get_نتيجو_String(نتيجو));
        اذهب clean;
    }

    ret = true;  // success!

clean:
    SDL_free(physical_devices);
    SDL_free(display_props);
    SDL_free(device_props);
    SDL_free(plane_props);
    SDL_free(گهڻائي_props);

    أرجع ret;
}

فراغ KMSDRM_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                  VkInstance instance,
                                  VkSurfaceKHR surface,
                                  ثابت بنية Vk_ورهاست_Callbacks *allocator)
{
    إذا (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_Destroy_Surface_اندروني(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

#جيڪڏهن_پورو
