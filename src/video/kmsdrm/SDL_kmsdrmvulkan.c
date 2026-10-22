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

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_KMSDRM)

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_vulkan_internal.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_kmsdrmvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_kmsdrmdyn.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_kmsdrmvulkan.h"

#ਅਨ੍ਤਰ੍ਭਾਵ <sys/ioctl.h>

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_PLATFORM_OPENBSD
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFAULT_VULKAN "libvulkan.so"
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFAULT_VULKAN "libvulkan.so.1"
#ਜੇ_ਅੰਤ

SDL_ELF_NOTE_DLOPEN(
    "kmsdrm-vulkan",
    "Support for Vulkan on KMSDRM",
    SDL_ELF_NOTE_DLOPEN_ਤਰਜੀਹ_SUGGESTED,
    DEFAULT_VULKAN
)

bool KMSDRM_Vulkan_ਲੱਦੋ_Library(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *ਰਸਤਾ)
{
    VkExtensionProperties *extensions = ਨਿਰਾ;
    Uint32 i, extension_ਗਿਣਤੀ = 0;
    bool hasSurfaceExtension = false;
    bool hasDisplayExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = ਨਿਰਾ;

    ਜੇ (_this->vulkan_config.loader_handle) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Vulkan already loaded");
    }

    // Load the Vulkan library
    ਜੇ (!ਰਸਤਾ) {
        ਰਸਤਾ = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }
    ਜੇ (!ਰਸਤਾ) {
        ਰਸਤਾ = DEFAULT_VULKAN;
    }

    _this->vulkan_config.loader_handle = SDL_ਲੱਦੋ_Object(ਰਸਤਾ);

    ਜੇ (!_this->vulkan_config.loader_handle) {
        ਵਾਪਸ false;
    }

    SDL_strlcpy(_this->vulkan_config.loader_ਰਸਤਾ, ਰਸਤਾ,
                SDL_arraysize(_this->vulkan_config.loader_ਰਸਤਾ));

    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)SDL_ਲੱਦੋ_Function(
        _this->vulkan_config.loader_handle, "vkGetInstanceProcAddr");

    ਜੇ (!vkGetInstanceProcAddr) {
        ਜਾਓ fail;
    }

    _this->vulkan_config.vkGetInstanceProcAddr = (ਖਾਲੀ *)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties =
        (ਖਾਲੀ *)((PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr)(
            VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties");

    ਜੇ (!_this->vulkan_config.vkEnumerateInstanceExtensionProperties) {
        ਜਾਓ fail;
    }

    extensions = SDL_Vulkan_CreateInstanceExtensionsList(
        (PFN_vkEnumerateInstanceExtensionProperties)
            _this->vulkan_config.vkEnumerateInstanceExtensionProperties,
        &extension_ਗਿਣਤੀ);

    ਜੇ (!extensions) {
        ਜਾਓ fail;
    }

    ਲਈ (i = 0; i < extension_ਗਿਣਤੀ; i++) {
        ਜੇ (SDL_strcmp(VK_KHR_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasSurfaceExtension = true;
        } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(VK_KHR_DISPLAY_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasDisplayExtension = true;
        }
    }

    SDL_free(extensions);

    ਜੇ (!hasSurfaceExtension) {
        SDL_ਸੈੱਟ_Error("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        ਜਾਓ fail;
    } ਨਹੀਂਤਾਂ ਜੇ (!hasDisplayExtension) {
        SDL_ਸੈੱਟ_Error("Installed Vulkan doesn't implement the " VK_KHR_DISPLAY_EXTENSION_NAME " extension");
        ਜਾਓ fail;
    }

    ਵਾਪਸ true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = ਨਿਰਾ;
    ਵਾਪਸ false;
}

ਖਾਲੀ KMSDRM_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    ਜੇ (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = ਨਿਰਾ;
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
ਅੱਖਰ ਅਚਲ * ਅਚਲ *KMSDRM_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *ਗਿਣਤੀ_2)
{
    ਸਥਿਰ ਅਚਲ ਅੱਖਰ *ਅਚਲ extensionsForKMSDRM[] = {
        VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_DISPLAY_EXTENSION_NAME
    };
    *ਗਿਣਤੀ_2 = SDL_arraysize(extensionsForKMSDRM);
    ਵਾਪਸ extensionsForKMSDRM;
}

ਸਥਿਰ ਪੂਰਨ SDLCALL display_ਬਹੁਲਕ_comparator(ਅਚਲ ਖਾਲੀ *a_opaque, ਅਚਲ ਖਾਲੀ *b_opaque)
{
    ਅਚਲ Vk_Display_ਬਹੁਲਕ_Properties_KHR *a = a_opaque;
    ਅਚਲ Vk_Display_ਬਹੁਲਕ_Properties_KHR *b = b_opaque;

    ਜੇ (a->parameters.refresh_ਦਰ_2 > b->parameters.refresh_ਦਰ_2)
        ਵਾਪਸ -1;
    ਨਹੀਂਤਾਂ ਜੇ (a->parameters.refresh_ਦਰ_2 < b->parameters.refresh_ਦਰ_2)
        ਵਾਪਸ 1;
    ਨਹੀਂਤਾਂ
        ਵਾਪਸ 0;
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
                                SDL_ਖਿੜਕੀ *ਖਿੜਕੀ,
                                VkInstance instance,
                                ਅਚਲ ਬਣਤਰ Vk_ਵੰਡ_Callbacks *allocator,
                                VkSurfaceKHR *surface)
{
    VkPhysicalDevice gpu = ਨਿਰਾ;
    uint32_t gpu_ਗਿਣਤੀ;
    uint32_t display_ਗਿਣਤੀ;
    uint32_t ਬਹੁਲਕ_ਗਿਣਤੀ;
    uint32_t plane_ਗਿਣਤੀ_2;
    uint32_t _plane = UINT32_MAX;

    VkPhysicalDevice *physical_devices = ਨਿਰਾ;
    VkPhysicalDeviceProperties *device_props = ਨਿਰਾ;
    VkDisplayPropertiesKHR *display_props = ਨਿਰਾ;
    Vk_Display_ਬਹੁਲਕ_Properties_KHR *ਬਹੁਲਕ_props = ਨਿਰਾ;
    VkDisplayPlanePropertiesKHR *plane_props = ਨਿਰਾ;
    VkDisplayPlaneCapabilitiesKHR plane_caps;

    Vk_Display_ਬਹੁਲਕ_Create_Info_KHR display_ਬਹੁਲਕ_create_info;
    VkDisplaySurfaceCreateInfoKHR display_plane_surface_create_info;

    VkExtent2D image_ਮਾਪ_2;
    VkDisplayKHR display;
    Vk_Display_ਬਹੁਲਕ_KHR display_ਬਹੁਲਕ_2 = (Vk_Display_ਬਹੁਲਕ_KHR)0;
    Vk_Display_ਬਹੁਲਕ_Properties_KHR display_ਬਹੁਲਕ_props = { 0 };
    Vk_Display_ਬਹੁਲਕ_Parameters_KHR new_ਬਹੁਲਕ_parameters = { { 0, 0 }, 0 };
    // Prefer a plane that supports per-pixel alpha.
    Vk_Display_Plane_Alpha_Flag_ਬਿੱਟ_KHR alpha_ਬਹੁਲਕ_2 = VK_DISPLAY_PLANE_ALPHA_OPAQUE_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR;

    Vk_ਨਤੀਜਾ ਨਤੀਜਾ;
    bool ret = false;
    bool valid_gpu = false;
    bool ਬਹੁਲਕ_ਮਿਲਿਆ = false;
    bool plane_supports_display = false;

    // Get the display index from the display being used by the window.
    ਪੂਰਨ display_ਸੂਚਕਾਂਕ = SDL_Get_Display_ਸੂਚਕਾਂਕ(SDL_Get_Display_For_ਖਿੜਕੀ(ਖਿੜਕੀ));
    ਪੂਰਨ i, j;

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

    PFN_vk_Get_Display_ਬਹੁਲਕ_Properties_KHR vk_Get_Display_ਬਹੁਲਕ_Properties_KHR =
        (PFN_vk_Get_Display_ਬਹੁਲਕ_Properties_KHR)vkGetInstanceProcAddr(
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

    PFN_vk_Create_Display_ਬਹੁਲਕ_KHR vk_Create_Display_ਬਹੁਲਕ_KHR =
        (PFN_vk_Create_Display_ਬਹੁਲਕ_KHR)vkGetInstanceProcAddr(
            instance, "vkCreateDisplayModeKHR");

    ਜੇ (!_this->vulkan_config.loader_handle) {
        SDL_ਸੈੱਟ_Error("Vulkan is not loaded");
        ਜਾਓ clean;
    }

    /*************************************/
    // Block for vulkan surface creation
    /*************************************/

    /****************************************************************/
    // If we got vkCreateDisplayPlaneSurfaceKHR() pointer, it means
    // that the VK_KHR_Display extension is active on the instance.
    // That's the central extension we need for x-less VK!
    /****************************************************************/
    ਜੇ (!vkCreateDisplayPlaneSurfaceKHR) {
        SDL_ਸੈੱਟ_Error(VK_KHR_DISPLAY_EXTENSION_NAME
                     " extension is not enabled in the Vulkan instance.");
        ਜਾਓ clean;
    }

    /* A GPU (or physical_device, in vkcube terms) is a physical GPU.
       A machine with more than one video output doesn't need to have more than one GPU,
       like the Pi4 which has 1 GPU and 2 video outputs.
       Just in case, we test that the GPU we choose is Vulkan-capable.
       If there are new reports about VK init failures, hardcode
       gpu = physical_devices[0], instead of probing, and go with that.
    */

    // Get the physical device count.
    vkEnumeratePhysicalDevices(instance, &gpu_ਗਿਣਤੀ, ਨਿਰਾ);

    ਜੇ (gpu_ਗਿਣਤੀ == 0) {
        SDL_ਸੈੱਟ_Error("Vulkan can't find physical devices (gpus).");
        ਜਾਓ clean;
    }

    // Get the physical devices.
    physical_devices = SDL_malloc(ਆਕਾਰ(VkPhysicalDevice) * gpu_ਗਿਣਤੀ);
    device_props = SDL_malloc(ਆਕਾਰ(VkPhysicalDeviceProperties));
    vkEnumeratePhysicalDevices(instance, &gpu_ਗਿਣਤੀ, physical_devices);

    // Iterate on the physical devices.
    ਲਈ (i = 0; i < gpu_ਗਿਣਤੀ; i++) {

        // Get the physical device properties.
        vkGetPhysicalDeviceProperties(
            physical_devices[i],
            device_props);

        // Is this device a real GPU that supports API version 1 at least?
        ਜੇ (device_props->api_ਸੰਸਕਰਣ >= 1 &&
            (device_props->deviceType == 1 || device_props->deviceType == 2)) {
            gpu = physical_devices[i];
            valid_gpu = true;
            ਰੋਕੋ;
        }
    }

    ਜੇ (!valid_gpu) {
        SDL_ਸੈੱਟ_Error("Vulkan can't find a valid physical device (gpu).");
        ਜਾਓ clean;
    }

    /* A display is a video output. 1 GPU can have N displays.
       Vulkan only counts the connected displays.
       Get the display count of the GPU. */
    vkGetPhysicalDeviceDisplayPropertiesKHR(gpu, &display_ਗਿਣਤੀ, ਨਿਰਾ);
    ਜੇ (display_ਗਿਣਤੀ == 0) {
        SDL_ਸੈੱਟ_Error("Vulkan can't find any displays.");
        ਜਾਓ clean;
    }

    // Get the props of the displays of the physical device.
    display_props = (VkDisplayPropertiesKHR *)SDL_malloc(display_ਗਿਣਤੀ * ਆਕਾਰ(*display_props));
    vkGetPhysicalDeviceDisplayPropertiesKHR(gpu,
                                            &display_ਗਿਣਤੀ,
                                            display_props);

    // Get the chosen display based on the display index.
    display = display_props[display_ਸੂਚਕਾਂਕ].display;

    // Get the list of the display videomodes.
    vk_Get_Display_ਬਹੁਲਕ_Properties_KHR(gpu,
                                  display,
                                  &ਬਹੁਲਕ_ਗਿਣਤੀ, ਨਿਰਾ);

    ਜੇ (ਬਹੁਲਕ_ਗਿਣਤੀ == 0) {
        SDL_ਸੈੱਟ_Error("Vulkan can't find any video modes for display %i (%s)", 0,
                     display_props[display_ਸੂਚਕਾਂਕ].displayName);
        ਜਾਓ clean;
    }

    ਬਹੁਲਕ_props = (Vk_Display_ਬਹੁਲਕ_Properties_KHR *)SDL_malloc(ਬਹੁਲਕ_ਗਿਣਤੀ * ਆਕਾਰ(*ਬਹੁਲਕ_props));
    vk_Get_Display_ਬਹੁਲਕ_Properties_KHR(gpu,
                                  display,
                                  &ਬਹੁਲਕ_ਗਿਣਤੀ, ਬਹੁਲਕ_props);

    /* Sort the modes so that larger refresh rates come first. */
    SDL_qsort(ਬਹੁਲਕ_props, ਬਹੁਲਕ_ਗਿਣਤੀ, ਆਕਾਰ(*ਬਹੁਲਕ_props), display_ਬਹੁਲਕ_comparator);

    /* Get a video mode equal to the window size among the predefined ones,
       if possible.
       REMEMBER: We have to get a small enough videomode for the window size,
       because videomode determines how big the scanout region is and we can't
       scanout a region bigger than the window (we would be reading past the
       buffer, and Vulkan would give us a confusing VK_ERROR_SURFACE_LOST_KHR). */
    ਲਈ (i = 0; i < ਬਹੁਲਕ_ਗਿਣਤੀ; i++) {
        ਜੇ (ਬਹੁਲਕ_props[i].parameters.visibleRegion.ਚੌੜਾਈ == ਖਿੜਕੀ->w &&
            ਬਹੁਲਕ_props[i].parameters.visibleRegion.ਉਚਾਈ == ਖਿੜਕੀ->h) {
            display_ਬਹੁਲਕ_props = ਬਹੁਲਕ_props[i];
            ਬਹੁਲਕ_ਮਿਲਿਆ = true;
            ਰੋਕੋ;
        }
    }

    ਜੇ (ਬਹੁਲਕ_ਮਿਲਿਆ &&
        display_ਬਹੁਲਕ_props.parameters.visibleRegion.ਚੌੜਾਈ > 0 &&
        display_ਬਹੁਲਕ_props.parameters.visibleRegion.ਉਚਾਈ > 0) {
        // Found a suitable mode among the predefined ones. Use that.
        display_ਬਹੁਲਕ_2 = display_ਬਹੁਲਕ_props.display_ਬਹੁਲਕ;
    } ਨਹੀਂਤਾਂ {

        /* Couldn't find a suitable mode among the predefined ones, so try to create our own.
           This won't work for some video chips atm (like Pi's VideoCore) so these are limited
           to supported resolutions. Don't try to use "closest" resolutions either, because
           those are often bigger than the window size, thus causing out-of-bunds scanout. */
        new_ਬਹੁਲਕ_parameters.visibleRegion.ਚੌੜਾਈ = ਖਿੜਕੀ->w;
        new_ਬਹੁਲਕ_parameters.visibleRegion.ਉਚਾਈ = ਖਿੜਕੀ->h;
        /* SDL (and DRM, if we look at drmModeModeInfo vrefresh) uses plain integer Hz for
           display mode refresh rate, but Vulkan expects higher precision. */
        new_ਬਹੁਲਕ_parameters.refresh_ਦਰ_2 = (uint32_t)(ਖਿੜਕੀ->current_fullscreen_ਬਹੁਲਕ.refresh_ਦਰ * 1000);

        SDL_zero(display_ਬਹੁਲਕ_create_info);
        display_ਬਹੁਲਕ_create_info.sType = VK_STRUCTURE_TYPE_DISPLAY_ਬਹੁਲਕ_CREATE_INFO_KHR;
        display_ਬਹੁਲਕ_create_info.parameters = new_ਬਹੁਲਕ_parameters;
        ਨਤੀਜਾ = vk_Create_Display_ਬਹੁਲਕ_KHR(gpu,
                                        display,
                                        &display_ਬਹੁਲਕ_create_info,
                                        ਨਿਰਾ, &display_ਬਹੁਲਕ_2);
        ਜੇ (ਨਤੀਜਾ != VK_SUCCESS) {
            SDL_ਸੈੱਟ_Error("Vulkan couldn't find a predefined mode for that window size and couldn't create a suitable mode.");
            ਜਾਓ clean;
        }
    }

    // Just in case we get here without a display_mode.
    ਜੇ (!display_ਬਹੁਲਕ_2) {
        SDL_ਸੈੱਟ_Error("Vulkan couldn't get a display mode.");
        ਜਾਓ clean;
    }

    // Get the list of the physical device planes.
    vkGetPhysicalDeviceDisplayPlanePropertiesKHR(gpu, &plane_ਗਿਣਤੀ_2, ਨਿਰਾ);
    ਜੇ (plane_ਗਿਣਤੀ_2 == 0) {
        SDL_ਸੈੱਟ_Error("Vulkan can't find any planes.");
        ਜਾਓ clean;
    }
    plane_props = SDL_malloc(ਆਕਾਰ(VkDisplayPlanePropertiesKHR) * plane_ਗਿਣਤੀ_2);
    vkGetPhysicalDeviceDisplayPlanePropertiesKHR(gpu, &plane_ਗਿਣਤੀ_2, plane_props);

    /* Iterate on the list of planes of the physical device
       to find a plane that matches these criteria:
       -It must be compatible with the chosen display + mode.
       -It isn't currently bound to another display.
       -It supports per-pixel alpha, if possible. */
    ਲਈ (i = 0; i < plane_ਗਿਣਤੀ_2; i++) {

        uint32_t supported_displays_ਗਿਣਤੀ = 0;
        VkDisplayKHR *supported_displays;

        // See if the plane is compatible with the current display.
        vkGetDisplayPlaneSupportedDisplaysKHR(gpu, i, &supported_displays_ਗਿਣਤੀ, ਨਿਰਾ);
        ਜੇ (supported_displays_ਗਿਣਤੀ == 0) {
            // This plane doesn't support any displays. Continue to the next plane.
            ਜਾਰੀ;
        }

        // Get the list of displays supported by this plane.
        supported_displays = (VkDisplayKHR *)SDL_malloc(ਆਕਾਰ(VkDisplayKHR) * supported_displays_ਗਿਣਤੀ);
        vkGetDisplayPlaneSupportedDisplaysKHR(gpu, i,
                                              &supported_displays_ਗਿਣਤੀ, supported_displays);

        /* The plane must be bound to the chosen display, or not in use.
           If none of these is true, iterate to another plane. */
        ਜੇ (!((plane_props[i].currentDisplay == display) || (plane_props[i].currentDisplay == VK_NULL_HANDLE))) {
            ਜਾਰੀ;
        }

        /* Iterate the list of displays supported by this plane
           in order to find out if the chosen display is among them. */
        plane_supports_display = false;
        ਲਈ (j = 0; j < supported_displays_ਗਿਣਤੀ; j++) {
            ਜੇ (supported_displays[j] == display) {
                plane_supports_display = true;
                ਰੋਕੋ;
            }
        }

        // Free the list of displays supported by this plane.
        SDL_free(supported_displays);

        // If the display is not supported by this plane, iterate to the next plane.
        ਜੇ (!plane_supports_display) {
            ਜਾਰੀ;
        }

        // Want a plane that supports the alpha mode we have chosen.
        vkGetDisplayPlaneCapabilitiesKHR(gpu, display_ਬਹੁਲਕ_2, i, &plane_caps);
        ਜੇ (plane_caps.supportedAlpha == alpha_ਬਹੁਲਕ_2) {
            // Yep, this plane is alright.
            _plane = i;
            ਰੋਕੋ;
        }
    }

    // If we couldn't find an appropriate plane, error out.
    ਜੇ (_plane == UINT32_MAX) {
        SDL_ਸੈੱਟ_Error("Vulkan couldn't find an appropriate plane.");
        ਜਾਓ clean;
    }

    /********************************************/
    // Let's finally create the Vulkan surface!
    /********************************************/

    image_ਮਾਪ_2.ਚੌੜਾਈ = ਖਿੜਕੀ->w;
    image_ਮਾਪ_2.ਉਚਾਈ = ਖਿੜਕੀ->h;

    SDL_zero(display_plane_surface_create_info);
    display_plane_surface_create_info.sType = VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR;
    display_plane_surface_create_info.display_ਬਹੁਲਕ = display_ਬਹੁਲਕ_2;
    display_plane_surface_create_info.plane_ਸੂਚਕਾਂਕ = _plane;
    display_plane_surface_create_info.imageExtent = image_ਮਾਪ_2;
    display_plane_surface_create_info.transform = VK_SURFACE_TRANSFORM_ਪਛਾਣ_ਤੱਤ_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR;
    display_plane_surface_create_info.alpha_ਬਹੁਲਕ = alpha_ਬਹੁਲਕ_2;
    ਨਤੀਜਾ = vkCreateDisplayPlaneSurfaceKHR(instance,
                                            &display_plane_surface_create_info,
                                            allocator,
                                            surface);
    ਜੇ (ਨਤੀਜਾ != VK_SUCCESS) {
        SDL_ਸੈੱਟ_Error("vkCreateDisplayPlaneSurfaceKHR failed: %s",
                     SDL_Vulkan_Get_ਨਤੀਜਾ_String(ਨਤੀਜਾ));
        ਜਾਓ clean;
    }

    ret = true;  // success!

clean:
    SDL_free(physical_devices);
    SDL_free(display_props);
    SDL_free(device_props);
    SDL_free(plane_props);
    SDL_free(ਬਹੁਲਕ_props);

    ਵਾਪਸ ret;
}

ਖਾਲੀ KMSDRM_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                  VkInstance instance,
                                  VkSurfaceKHR surface,
                                  ਅਚਲ ਬਣਤਰ Vk_ਵੰਡ_Callbacks *allocator)
{
    ਜੇ (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_Destroy_Surface_ਅੰਦਰੂਨੀ(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

#ਜੇ_ਅੰਤ
