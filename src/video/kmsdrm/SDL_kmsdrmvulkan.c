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

#अन्तर्भाव "SDL_internal.h"

#यदि defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_KMSDRM)

#अन्तर्भाव "../SDL_vulkan_internal.h"

#अन्तर्भाव "SDL_kmsdrmvideo.h"
#अन्तर्भाव "SDL_kmsdrmdyn.h"
#अन्तर्भाव "SDL_kmsdrmvulkan.h"

#अन्तर्भाव <sys/ioctl.h>

#यदि_परिभाषितम् SDL_PLATFORM_OPENBSD
#परिभाषय DEFAULT_VULKAN "libvulkan.so"
#अन्यथा
#परिभाषय DEFAULT_VULKAN "libvulkan.so.1"
#यदि_अन्तः

SDL_ELF_NOTE_DLOPEN(
    "kmsdrm-vulkan",
    "Support for Vulkan on KMSDRM",
    SDL_ELF_NOTE_DLOPEN_प्राथमिकता_SUGGESTED,
    DEFAULT_VULKAN
)

bool KMSDRM_Vulkan_आरोपय_Library(SDL_VideoDevice *_this, ध्रुव वर्ण *मार्गः)
{
    VkExtensionProperties *extensions = रिक्त;
    Uint32 i, extension_गणनम् = 0;
    bool hasSurfaceExtension = false;
    bool hasDisplayExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = रिक्त;

    यदि (_this->vulkan_config.loader_handle) {
        प्रत्यागम SDL_समुच्चयः_Error("Vulkan already loaded");
    }

    // Load the Vulkan library
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

    SDL_strlcpy(_this->vulkan_config.loader_मार्गः, मार्गः,
                SDL_arraysize(_this->vulkan_config.loader_मार्गः));

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
        } अन्यथा यदि (SDL_strcmp(VK_KHR_DISPLAY_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasDisplayExtension = true;
        }
    }

    SDL_free(extensions);

    यदि (!hasSurfaceExtension) {
        SDL_समुच्चयः_Error("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        गच्छ fail;
    } अन्यथा यदि (!hasDisplayExtension) {
        SDL_समुच्चयः_Error("Installed Vulkan doesn't implement the " VK_KHR_DISPLAY_EXTENSION_NAME " extension");
        गच्छ fail;
    }

    प्रत्यागम true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = रिक्त;
    प्रत्यागम false;
}

शून्य KMSDRM_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    यदि (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = रिक्त;
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
वर्ण ध्रुव * ध्रुव *KMSDRM_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *गणनम्)
{
    स्थिर ध्रुव वर्ण *ध्रुव extensionsForKMSDRM[] = {
        VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_DISPLAY_EXTENSION_NAME
    };
    *गणनम् = SDL_arraysize(extensionsForKMSDRM);
    प्रत्यागम extensionsForKMSDRM;
}

स्थिर पूर्णाङ्क SDLCALL display_बहुलकम्_comparator(ध्रुव शून्य *a_opaque, ध्रुव शून्य *b_opaque)
{
    ध्रुव Vk_Display_बहुलकम्_Properties_KHR *a = a_opaque;
    ध्रुव Vk_Display_बहुलकम्_Properties_KHR *b = b_opaque;

    यदि (a->parameters.refresh_दरः_2 > b->parameters.refresh_दरः_2)
        प्रत्यागम -1;
    अन्यथा यदि (a->parameters.refresh_दरः_2 < b->parameters.refresh_दरः_2)
        प्रत्यागम 1;
    अन्यथा
        प्रत्यागम 0;
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
                                SDL_गवाक्षः *गवाक्षः,
                                VkInstance instance,
                                ध्रुव संरचना Vk_आवण्टनम्_Callbacks *allocator,
                                VkSurfaceKHR *surface)
{
    VkPhysicalDevice gpu = रिक्त;
    uint32_t gpu_गणनम्;
    uint32_t display_गणनम्;
    uint32_t बहुलकम्_गणनम्;
    uint32_t plane_गणनम्_2;
    uint32_t _plane = UINT32_MAX;

    VkPhysicalDevice *physical_devices = रिक्त;
    VkPhysicalDeviceProperties *device_props = रिक्त;
    VkDisplayPropertiesKHR *display_props = रिक्त;
    Vk_Display_बहुलकम्_Properties_KHR *बहुलकम्_props = रिक्त;
    VkDisplayPlanePropertiesKHR *plane_props = रिक्त;
    VkDisplayPlaneCapabilitiesKHR plane_caps;

    Vk_Display_बहुलकम्_Create_Info_KHR display_बहुलकम्_create_info;
    VkDisplaySurfaceCreateInfoKHR display_plane_surface_create_info;

    VkExtent2D image_आकार_2;
    VkDisplayKHR display;
    Vk_Display_बहुलकम्_KHR display_बहुलकम्_2 = (Vk_Display_बहुलकम्_KHR)0;
    Vk_Display_बहुलकम्_Properties_KHR display_बहुलकम्_props = { 0 };
    Vk_Display_बहुलकम्_Parameters_KHR new_बहुलकम्_parameters = { { 0, 0 }, 0 };
    // Prefer a plane that supports per-pixel alpha.
    Vk_Display_Plane_Alpha_Flag_द्वयङ्काः_KHR alpha_बहुलकम्_2 = VK_DISPLAY_PLANE_ALPHA_OPAQUE_BIT_KHR;

    Vk_परिणाम परिणाम;
    bool ret = false;
    bool valid_gpu = false;
    bool बहुलकम्_प्राप्तम् = false;
    bool plane_supports_display = false;

    // Get the display index from the display being used by the window.
    पूर्णाङ्क display_सूचकांक = SDL_Get_Display_सूचकांक(SDL_Get_Display_For_गवाक्षः(गवाक्षः));
    पूर्णाङ्क i, j;

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

    PFN_vk_Get_Display_बहुलकम्_Properties_KHR vk_Get_Display_बहुलकम्_Properties_KHR =
        (PFN_vk_Get_Display_बहुलकम्_Properties_KHR)vkGetInstanceProcAddr(
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

    PFN_vk_Create_Display_बहुलकम्_KHR vk_Create_Display_बहुलकम्_KHR =
        (PFN_vk_Create_Display_बहुलकम्_KHR)vkGetInstanceProcAddr(
            instance, "vkCreateDisplayModeKHR");

    यदि (!_this->vulkan_config.loader_handle) {
        SDL_समुच्चयः_Error("Vulkan is not loaded");
        गच्छ clean;
    }

    /*************************************/
    // Block for vulkan surface creation
    /*************************************/

    /****************************************************************/
    // If we got vkCreateDisplayPlaneSurfaceKHR() pointer, it means
    // that the VK_KHR_Display extension is active on the instance.
    // That's the central extension we need for x-less VK!
    /****************************************************************/
    यदि (!vkCreateDisplayPlaneSurfaceKHR) {
        SDL_समुच्चयः_Error(VK_KHR_DISPLAY_EXTENSION_NAME
                     " extension is not enabled in the Vulkan instance.");
        गच्छ clean;
    }

    /* A GPU (or physical_device, in vkcube terms) is a physical GPU.
       A machine with more than one video output doesn't need to have more than one GPU,
       like the Pi4 which has 1 GPU and 2 video outputs.
       Just in case, we test that the GPU we choose is Vulkan-capable.
       If there are new reports about VK init failures, hardcode
       gpu = physical_devices[0], instead of probing, and go with that.
    */

    // Get the physical device count.
    vkEnumeratePhysicalDevices(instance, &gpu_गणनम्, रिक्त);

    यदि (gpu_गणनम् == 0) {
        SDL_समुच्चयः_Error("Vulkan can't find physical devices (gpus).");
        गच्छ clean;
    }

    // Get the physical devices.
    physical_devices = SDL_malloc(परिमाण(VkPhysicalDevice) * gpu_गणनम्);
    device_props = SDL_malloc(परिमाण(VkPhysicalDeviceProperties));
    vkEnumeratePhysicalDevices(instance, &gpu_गणनम्, physical_devices);

    // Iterate on the physical devices.
    प्रति (i = 0; i < gpu_गणनम्; i++) {

        // Get the physical device properties.
        vkGetPhysicalDeviceProperties(
            physical_devices[i],
            device_props);

        // Is this device a real GPU that supports API version 1 at least?
        यदि (device_props->api_संस्करणम् >= 1 &&
            (device_props->deviceType == 1 || device_props->deviceType == 2)) {
            gpu = physical_devices[i];
            valid_gpu = true;
            भङ्ग;
        }
    }

    यदि (!valid_gpu) {
        SDL_समुच्चयः_Error("Vulkan can't find a valid physical device (gpu).");
        गच्छ clean;
    }

    /* A display is a video output. 1 GPU can have N displays.
       Vulkan only counts the connected displays.
       Get the display count of the GPU. */
    vkGetPhysicalDeviceDisplayPropertiesKHR(gpu, &display_गणनम्, रिक्त);
    यदि (display_गणनम् == 0) {
        SDL_समुच्चयः_Error("Vulkan can't find any displays.");
        गच्छ clean;
    }

    // Get the props of the displays of the physical device.
    display_props = (VkDisplayPropertiesKHR *)SDL_malloc(display_गणनम् * परिमाण(*display_props));
    vkGetPhysicalDeviceDisplayPropertiesKHR(gpu,
                                            &display_गणनम्,
                                            display_props);

    // Get the chosen display based on the display index.
    display = display_props[display_सूचकांक].display;

    // Get the list of the display videomodes.
    vk_Get_Display_बहुलकम्_Properties_KHR(gpu,
                                  display,
                                  &बहुलकम्_गणनम्, रिक्त);

    यदि (बहुलकम्_गणनम् == 0) {
        SDL_समुच्चयः_Error("Vulkan can't find any video modes for display %i (%s)", 0,
                     display_props[display_सूचकांक].displayName);
        गच्छ clean;
    }

    बहुलकम्_props = (Vk_Display_बहुलकम्_Properties_KHR *)SDL_malloc(बहुलकम्_गणनम् * परिमाण(*बहुलकम्_props));
    vk_Get_Display_बहुलकम्_Properties_KHR(gpu,
                                  display,
                                  &बहुलकम्_गणनम्, बहुलकम्_props);

    /* Sort the modes so that larger refresh rates come first. */
    SDL_qsort(बहुलकम्_props, बहुलकम्_गणनम्, परिमाण(*बहुलकम्_props), display_बहुलकम्_comparator);

    /* Get a video mode equal to the window size among the predefined ones,
       if possible.
       REMEMBER: We have to get a small enough videomode for the window size,
       because videomode determines how big the scanout region is and we can't
       scanout a region bigger than the window (we would be reading past the
       buffer, and Vulkan would give us a confusing VK_ERROR_SURFACE_LOST_KHR). */
    प्रति (i = 0; i < बहुलकम्_गणनम्; i++) {
        यदि (बहुलकम्_props[i].parameters.visibleRegion.विस्तारः == गवाक्षः->w &&
            बहुलकम्_props[i].parameters.visibleRegion.height == गवाक्षः->h) {
            display_बहुलकम्_props = बहुलकम्_props[i];
            बहुलकम्_प्राप्तम् = true;
            भङ्ग;
        }
    }

    यदि (बहुलकम्_प्राप्तम् &&
        display_बहुलकम्_props.parameters.visibleRegion.विस्तारः > 0 &&
        display_बहुलकम्_props.parameters.visibleRegion.height > 0) {
        // Found a suitable mode among the predefined ones. Use that.
        display_बहुलकम्_2 = display_बहुलकम्_props.display_बहुलकम्;
    } अन्यथा {

        /* Couldn't find a suitable mode among the predefined ones, so try to create our own.
           This won't work for some video chips atm (like Pi's VideoCore) so these are limited
           to supported resolutions. Don't try to use "closest" resolutions either, because
           those are often bigger than the window size, thus causing out-of-bunds scanout. */
        new_बहुलकम्_parameters.visibleRegion.विस्तारः = गवाक्षः->w;
        new_बहुलकम्_parameters.visibleRegion.height = गवाक्षः->h;
        /* SDL (and DRM, if we look at drmModeModeInfo vrefresh) uses plain integer Hz for
           display mode refresh rate, but Vulkan expects higher precision. */
        new_बहुलकम्_parameters.refresh_दरः_2 = (uint32_t)(गवाक्षः->current_fullscreen_बहुलकम्.refresh_दरः * 1000);

        SDL_zero(display_बहुलकम्_create_info);
        display_बहुलकम्_create_info.sType = VK_STRUCTURE_TYPE_DISPLAY_बहुलकम्_CREATE_INFO_KHR;
        display_बहुलकम्_create_info.parameters = new_बहुलकम्_parameters;
        परिणाम = vk_Create_Display_बहुलकम्_KHR(gpu,
                                        display,
                                        &display_बहुलकम्_create_info,
                                        रिक्त, &display_बहुलकम्_2);
        यदि (परिणाम != VK_SUCCESS) {
            SDL_समुच्चयः_Error("Vulkan couldn't find a predefined mode for that window size and couldn't create a suitable mode.");
            गच्छ clean;
        }
    }

    // Just in case we get here without a display_mode.
    यदि (!display_बहुलकम्_2) {
        SDL_समुच्चयः_Error("Vulkan couldn't get a display mode.");
        गच्छ clean;
    }

    // Get the list of the physical device planes.
    vkGetPhysicalDeviceDisplayPlanePropertiesKHR(gpu, &plane_गणनम्_2, रिक्त);
    यदि (plane_गणनम्_2 == 0) {
        SDL_समुच्चयः_Error("Vulkan can't find any planes.");
        गच्छ clean;
    }
    plane_props = SDL_malloc(परिमाण(VkDisplayPlanePropertiesKHR) * plane_गणनम्_2);
    vkGetPhysicalDeviceDisplayPlanePropertiesKHR(gpu, &plane_गणनम्_2, plane_props);

    /* Iterate on the list of planes of the physical device
       to find a plane that matches these criteria:
       -It must be compatible with the chosen display + mode.
       -It isn't currently bound to another display.
       -It supports per-pixel alpha, if possible. */
    प्रति (i = 0; i < plane_गणनम्_2; i++) {

        uint32_t supported_displays_गणनम् = 0;
        VkDisplayKHR *supported_displays;

        // See if the plane is compatible with the current display.
        vkGetDisplayPlaneSupportedDisplaysKHR(gpu, i, &supported_displays_गणनम्, रिक्त);
        यदि (supported_displays_गणनम् == 0) {
            // This plane doesn't support any displays. Continue to the next plane.
            अनुवर्त;
        }

        // Get the list of displays supported by this plane.
        supported_displays = (VkDisplayKHR *)SDL_malloc(परिमाण(VkDisplayKHR) * supported_displays_गणनम्);
        vkGetDisplayPlaneSupportedDisplaysKHR(gpu, i,
                                              &supported_displays_गणनम्, supported_displays);

        /* The plane must be bound to the chosen display, or not in use.
           If none of these is true, iterate to another plane. */
        यदि (!((plane_props[i].currentDisplay == display) || (plane_props[i].currentDisplay == VK_NULL_HANDLE))) {
            अनुवर्त;
        }

        /* Iterate the list of displays supported by this plane
           in order to find out if the chosen display is among them. */
        plane_supports_display = false;
        प्रति (j = 0; j < supported_displays_गणनम्; j++) {
            यदि (supported_displays[j] == display) {
                plane_supports_display = true;
                भङ्ग;
            }
        }

        // Free the list of displays supported by this plane.
        SDL_free(supported_displays);

        // If the display is not supported by this plane, iterate to the next plane.
        यदि (!plane_supports_display) {
            अनुवर्त;
        }

        // Want a plane that supports the alpha mode we have chosen.
        vkGetDisplayPlaneCapabilitiesKHR(gpu, display_बहुलकम्_2, i, &plane_caps);
        यदि (plane_caps.supportedAlpha == alpha_बहुलकम्_2) {
            // Yep, this plane is alright.
            _plane = i;
            भङ्ग;
        }
    }

    // If we couldn't find an appropriate plane, error out.
    यदि (_plane == UINT32_MAX) {
        SDL_समुच्चयः_Error("Vulkan couldn't find an appropriate plane.");
        गच्छ clean;
    }

    /********************************************/
    // Let's finally create the Vulkan surface!
    /********************************************/

    image_आकार_2.विस्तारः = गवाक्षः->w;
    image_आकार_2.height = गवाक्षः->h;

    SDL_zero(display_plane_surface_create_info);
    display_plane_surface_create_info.sType = VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR;
    display_plane_surface_create_info.display_बहुलकम् = display_बहुलकम्_2;
    display_plane_surface_create_info.plane_सूचकांक = _plane;
    display_plane_surface_create_info.imageExtent = image_आकार_2;
    display_plane_surface_create_info.transform = VK_SURFACE_TRANSFORM_तटस्थः_BIT_KHR;
    display_plane_surface_create_info.alpha_बहुलकम् = alpha_बहुलकम्_2;
    परिणाम = vkCreateDisplayPlaneSurfaceKHR(instance,
                                            &display_plane_surface_create_info,
                                            allocator,
                                            surface);
    यदि (परिणाम != VK_SUCCESS) {
        SDL_समुच्चयः_Error("vkCreateDisplayPlaneSurfaceKHR failed: %s",
                     SDL_Vulkan_Get_परिणाम_String(परिणाम));
        गच्छ clean;
    }

    ret = true;  // success!

clean:
    SDL_free(physical_devices);
    SDL_free(display_props);
    SDL_free(device_props);
    SDL_free(plane_props);
    SDL_free(बहुलकम्_props);

    प्रत्यागम ret;
}

शून्य KMSDRM_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                  VkInstance instance,
                                  VkSurfaceKHR surface,
                                  ध्रुव संरचना Vk_आवण्टनम्_Callbacks *allocator)
{
    यदि (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_Destroy_Surface_आन्तरिकम्(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

#यदि_अन्तः
