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

#समावेश "SDL_internal.h"

#अगर defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_KMSDRM)

#समावेश "../SDL_vulkan_internal.h"

#समावेश "SDL_kmsdrmvideo.h"
#समावेश "SDL_kmsdrmdyn.h"
#समावेश "SDL_kmsdrmvulkan.h"

#समावेश <sys/ioctl.h>

#अगर_घोषित SDL_PLATFORM_OPENBSD
#घोषणा DEFAULT_VULKAN "libvulkan.so"
#अन्यथा
#घोषणा DEFAULT_VULKAN "libvulkan.so.1"
#पूर्ण_अगर

SDL_ELF_NOTE_DLOPEN(
    "kmsdrm-vulkan",
    "Support for Vulkan on KMSDRM",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_SUGGESTED,
    DEFAULT_VULKAN
)

bool KMSDRM_Vulkan_LoadLibrary(SDL_VideoDevice *_this, स्थिर अक्षर *path)
{
    VkExtensionProperties *extensions = शून्य;
    Uint32 i, extension_गिनती = 0;
    bool hasSurfaceExtension = false;
    bool hasDisplayExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = शून्य;

    अगर (_this->vulkan_config.loader_handle) {
        वापस SDL_SetError("Vulkan already loaded");
    }

    // Load the Vulkan library
    अगर (!path) {
        path = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
    }
    अगर (!path) {
        path = DEFAULT_VULKAN;
    }

    _this->vulkan_config.loader_handle = SDL_LoadObject(path);

    अगर (!_this->vulkan_config.loader_handle) {
        वापस false;
    }

    SDL_strlcpy(_this->vulkan_config.loader_path, path,
                SDL_arraysize(_this->vulkan_config.loader_path));

    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)SDL_LoadFunction(
        _this->vulkan_config.loader_handle, "vkGetInstanceProcAddr");

    अगर (!vkGetInstanceProcAddr) {
        जाओ fail;
    }

    _this->vulkan_config.vkGetInstanceProcAddr = (व्योम *)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties =
        (व्योम *)((PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr)(
            VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties");

    अगर (!_this->vulkan_config.vkEnumerateInstanceExtensionProperties) {
        जाओ fail;
    }

    extensions = SDL_Vulkan_CreateInstanceExtensionsList(
        (PFN_vkEnumerateInstanceExtensionProperties)
            _this->vulkan_config.vkEnumerateInstanceExtensionProperties,
        &extension_गिनती);

    अगर (!extensions) {
        जाओ fail;
    }

    क्रम (i = 0; i < extension_गिनती; i++) {
        अगर (SDL_strcmp(VK_KHR_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasSurfaceExtension = true;
        } अन्यथा अगर (SDL_strcmp(VK_KHR_DISPLAY_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasDisplayExtension = true;
        }
    }

    SDL_free(extensions);

    अगर (!hasSurfaceExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        जाओ fail;
    } अन्यथा अगर (!hasDisplayExtension) {
        SDL_SetError("Installed Vulkan doesn't implement the " VK_KHR_DISPLAY_EXTENSION_NAME " extension");
        जाओ fail;
    }

    वापस true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = शून्य;
    वापस false;
}

व्योम KMSDRM_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    अगर (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = शून्य;
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
अक्षर स्थिर * स्थिर *KMSDRM_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *गिनती)
{
    अटल स्थिर अक्षर *स्थिर extensionsForKMSDRM[] = {
        VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_DISPLAY_EXTENSION_NAME
    };
    *गिनती = SDL_arraysize(extensionsForKMSDRM);
    वापस extensionsForKMSDRM;
}

अटल पूर्णांक SDLCALL display_mode_comparator(स्थिर व्योम *a_opaque, स्थिर व्योम *b_opaque)
{
    स्थिर VkDisplayModePropertiesKHR *a = a_opaque;
    स्थिर VkDisplayModePropertiesKHR *b = b_opaque;

    अगर (a->parameters.refreshRate > b->parameters.refreshRate)
        वापस -1;
    अन्यथा अगर (a->parameters.refreshRate < b->parameters.refreshRate)
        वापस 1;
    अन्यथा
        वापस 0;
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
                                स्थिर काष्ठा VkAllocationCallbacks *allocator,
                                VkSurfaceKHR *surface)
{
    VkPhysicalDevice gpu = शून्य;
    uint32_t gpu_गिनती;
    uint32_t display_गिनती;
    uint32_t mode_गिनती;
    uint32_t plane_गिनती_2;
    uint32_t _plane = UINT32_MAX;

    VkPhysicalDevice *physical_devices = शून्य;
    VkPhysicalDeviceProperties *device_props = शून्य;
    VkDisplayPropertiesKHR *display_props = शून्य;
    VkDisplayModePropertiesKHR *mode_props = शून्य;
    VkDisplayPlanePropertiesKHR *plane_props = शून्य;
    VkDisplayPlaneCapabilitiesKHR plane_caps;

    VkDisplayModeCreateInfoKHR display_mode_create_info;
    VkDisplaySurfaceCreateInfoKHR display_plane_surface_create_info;

    VkExtent2D image_आकार_2;
    VkDisplayKHR display;
    VkDisplayModeKHR display_mode = (VkDisplayModeKHR)0;
    VkDisplayModePropertiesKHR display_mode_props = { 0 };
    VkDisplayModeParametersKHR new_mode_parameters = { { 0, 0 }, 0 };
    // Prefer a plane that supports per-pixel alpha.
    VkDisplayPlaneAlphaFlagBitsKHR alpha_mode = VK_DISPLAY_PLANE_ALPHA_OPAQUE_BIT_KHR;

    Vk_परिणाम परिणाम;
    bool ret = false;
    bool valid_gpu = false;
    bool mode_found = false;
    bool plane_supports_display = false;

    // Get the display index from the display being used by the window.
    पूर्णांक display_सूचकांक = SDL_Get_Display_सूचकांक(SDL_GetDisplayForWindow(window));
    पूर्णांक i, j;

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

    अगर (!_this->vulkan_config.loader_handle) {
        SDL_SetError("Vulkan is not loaded");
        जाओ clean;
    }

    /*************************************/
    // Block for vulkan surface creation
    /*************************************/

    /****************************************************************/
    // If we got vkCreateDisplayPlaneSurfaceKHR() pointer, it means
    // that the VK_KHR_Display extension is active on the instance.
    // That's the central extension we need for x-less VK!
    /****************************************************************/
    अगर (!vkCreateDisplayPlaneSurfaceKHR) {
        SDL_SetError(VK_KHR_DISPLAY_EXTENSION_NAME
                     " extension is not enabled in the Vulkan instance.");
        जाओ clean;
    }

    /* A GPU (or physical_device, in vkcube terms) is a physical GPU.
       A machine with more than one video output doesn't need to have more than one GPU,
       like the Pi4 which has 1 GPU and 2 video outputs.
       Just in case, we test that the GPU we choose is Vulkan-capable.
       If there are new reports about VK init failures, hardcode
       gpu = physical_devices[0], instead of probing, and go with that.
    */

    // Get the physical device count.
    vkEnumeratePhysicalDevices(instance, &gpu_गिनती, शून्य);

    अगर (gpu_गिनती == 0) {
        SDL_SetError("Vulkan can't find physical devices (gpus).");
        जाओ clean;
    }

    // Get the physical devices.
    physical_devices = SDL_malloc(माप(VkPhysicalDevice) * gpu_गिनती);
    device_props = SDL_malloc(माप(VkPhysicalDeviceProperties));
    vkEnumeratePhysicalDevices(instance, &gpu_गिनती, physical_devices);

    // Iterate on the physical devices.
    क्रम (i = 0; i < gpu_गिनती; i++) {

        // Get the physical device properties.
        vkGetPhysicalDeviceProperties(
            physical_devices[i],
            device_props);

        // Is this device a real GPU that supports API version 1 at least?
        अगर (device_props->apiVersion >= 1 &&
            (device_props->deviceType == 1 || device_props->deviceType == 2)) {
            gpu = physical_devices[i];
            valid_gpu = true;
            अवरोध;
        }
    }

    अगर (!valid_gpu) {
        SDL_SetError("Vulkan can't find a valid physical device (gpu).");
        जाओ clean;
    }

    /* A display is a video output. 1 GPU can have N displays.
       Vulkan only counts the connected displays.
       Get the display count of the GPU. */
    vkGetPhysicalDeviceDisplayPropertiesKHR(gpu, &display_गिनती, शून्य);
    अगर (display_गिनती == 0) {
        SDL_SetError("Vulkan can't find any displays.");
        जाओ clean;
    }

    // Get the props of the displays of the physical device.
    display_props = (VkDisplayPropertiesKHR *)SDL_malloc(display_गिनती * माप(*display_props));
    vkGetPhysicalDeviceDisplayPropertiesKHR(gpu,
                                            &display_गिनती,
                                            display_props);

    // Get the chosen display based on the display index.
    display = display_props[display_सूचकांक].display;

    // Get the list of the display videomodes.
    vkGetDisplayModePropertiesKHR(gpu,
                                  display,
                                  &mode_गिनती, शून्य);

    अगर (mode_गिनती == 0) {
        SDL_SetError("Vulkan can't find any video modes for display %i (%s)", 0,
                     display_props[display_सूचकांक].displayName);
        जाओ clean;
    }

    mode_props = (VkDisplayModePropertiesKHR *)SDL_malloc(mode_गिनती * माप(*mode_props));
    vkGetDisplayModePropertiesKHR(gpu,
                                  display,
                                  &mode_गिनती, mode_props);

    /* Sort the modes so that larger refresh rates come first. */
    SDL_qsort(mode_props, mode_गिनती, माप(*mode_props), display_mode_comparator);

    /* Get a video mode equal to the window size among the predefined ones,
       if possible.
       REMEMBER: We have to get a small enough videomode for the window size,
       because videomode determines how big the scanout region is and we can't
       scanout a region bigger than the window (we would be reading past the
       buffer, and Vulkan would give us a confusing VK_ERROR_SURFACE_LOST_KHR). */
    क्रम (i = 0; i < mode_गिनती; i++) {
        अगर (mode_props[i].parameters.visibleRegion.width == window->w &&
            mode_props[i].parameters.visibleRegion.height == window->h) {
            display_mode_props = mode_props[i];
            mode_found = true;
            अवरोध;
        }
    }

    अगर (mode_found &&
        display_mode_props.parameters.visibleRegion.width > 0 &&
        display_mode_props.parameters.visibleRegion.height > 0) {
        // Found a suitable mode among the predefined ones. Use that.
        display_mode = display_mode_props.displayMode;
    } अन्यथा {

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
        परिणाम = vkCreateDisplayModeKHR(gpu,
                                        display,
                                        &display_mode_create_info,
                                        शून्य, &display_mode);
        अगर (परिणाम != VK_SUCCESS) {
            SDL_SetError("Vulkan couldn't find a predefined mode for that window size and couldn't create a suitable mode.");
            जाओ clean;
        }
    }

    // Just in case we get here without a display_mode.
    अगर (!display_mode) {
        SDL_SetError("Vulkan couldn't get a display mode.");
        जाओ clean;
    }

    // Get the list of the physical device planes.
    vkGetPhysicalDeviceDisplayPlanePropertiesKHR(gpu, &plane_गिनती_2, शून्य);
    अगर (plane_गिनती_2 == 0) {
        SDL_SetError("Vulkan can't find any planes.");
        जाओ clean;
    }
    plane_props = SDL_malloc(माप(VkDisplayPlanePropertiesKHR) * plane_गिनती_2);
    vkGetPhysicalDeviceDisplayPlanePropertiesKHR(gpu, &plane_गिनती_2, plane_props);

    /* Iterate on the list of planes of the physical device
       to find a plane that matches these criteria:
       -It must be compatible with the chosen display + mode.
       -It isn't currently bound to another display.
       -It supports per-pixel alpha, if possible. */
    क्रम (i = 0; i < plane_गिनती_2; i++) {

        uint32_t supported_displays_गिनती = 0;
        VkDisplayKHR *supported_displays;

        // See if the plane is compatible with the current display.
        vkGetDisplayPlaneSupportedDisplaysKHR(gpu, i, &supported_displays_गिनती, शून्य);
        अगर (supported_displays_गिनती == 0) {
            // This plane doesn't support any displays. Continue to the next plane.
            जारी;
        }

        // Get the list of displays supported by this plane.
        supported_displays = (VkDisplayKHR *)SDL_malloc(माप(VkDisplayKHR) * supported_displays_गिनती);
        vkGetDisplayPlaneSupportedDisplaysKHR(gpu, i,
                                              &supported_displays_गिनती, supported_displays);

        /* The plane must be bound to the chosen display, or not in use.
           If none of these is true, iterate to another plane. */
        अगर (!((plane_props[i].currentDisplay == display) || (plane_props[i].currentDisplay == VK_NULL_HANDLE))) {
            जारी;
        }

        /* Iterate the list of displays supported by this plane
           in order to find out if the chosen display is among them. */
        plane_supports_display = false;
        क्रम (j = 0; j < supported_displays_गिनती; j++) {
            अगर (supported_displays[j] == display) {
                plane_supports_display = true;
                अवरोध;
            }
        }

        // Free the list of displays supported by this plane.
        SDL_free(supported_displays);

        // If the display is not supported by this plane, iterate to the next plane.
        अगर (!plane_supports_display) {
            जारी;
        }

        // Want a plane that supports the alpha mode we have chosen.
        vkGetDisplayPlaneCapabilitiesKHR(gpu, display_mode, i, &plane_caps);
        अगर (plane_caps.supportedAlpha == alpha_mode) {
            // Yep, this plane is alright.
            _plane = i;
            अवरोध;
        }
    }

    // If we couldn't find an appropriate plane, error out.
    अगर (_plane == UINT32_MAX) {
        SDL_SetError("Vulkan couldn't find an appropriate plane.");
        जाओ clean;
    }

    /********************************************/
    // Let's finally create the Vulkan surface!
    /********************************************/

    image_आकार_2.width = window->w;
    image_आकार_2.height = window->h;

    SDL_zero(display_plane_surface_create_info);
    display_plane_surface_create_info.sType = VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR;
    display_plane_surface_create_info.displayMode = display_mode;
    display_plane_surface_create_info.plane_सूचकांक = _plane;
    display_plane_surface_create_info.imageExtent = image_आकार_2;
    display_plane_surface_create_info.transform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    display_plane_surface_create_info.alphaMode = alpha_mode;
    परिणाम = vkCreateDisplayPlaneSurfaceKHR(instance,
                                            &display_plane_surface_create_info,
                                            allocator,
                                            surface);
    अगर (परिणाम != VK_SUCCESS) {
        SDL_SetError("vkCreateDisplayPlaneSurfaceKHR failed: %s",
                     SDL_Vulkan_Get_परिणाम_String(परिणाम));
        जाओ clean;
    }

    ret = true;  // success!

clean:
    SDL_free(physical_devices);
    SDL_free(display_props);
    SDL_free(device_props);
    SDL_free(plane_props);
    SDL_free(mode_props);

    वापस ret;
}

व्योम KMSDRM_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                  VkInstance instance,
                                  VkSurfaceKHR surface,
                                  स्थिर काष्ठा VkAllocationCallbacks *allocator)
{
    अगर (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_DestroySurface_Internal(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

#पूर्ण_अगर
