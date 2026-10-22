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

#شامل "SDL_internal.h"

#اگر defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_KMSDRM)

#شامل "../SDL_vulkan_internal.h"

#شامل "SDL_kmsdrmvideo.h"
#شامل "SDL_kmsdrmdyn.h"
#شامل "SDL_kmsdrmvulkan.h"

#شامل <sys/ioctl.h>

#اگر_تعریف_شدہ SDL_PLATFORM_OPENBSD
#تعریف_کرو DEFAULT_VULKAN "libvulkan.so"
#ورنہ
#تعریف_کرو DEFAULT_VULKAN "libvulkan.so.1"
#اگر_ختم

SDL_ELF_NOTE_DLOPEN(
    "kmsdrm-vulkan",
    "Support for Vulkan on KMSDRM",
    SDL_ELF_NOTE_DLOPEN_ترجیح_SUGGESTED,
    DEFAULT_VULKAN
)

bool KMSDRM_Vulkan_بھرو_Library(SDL_VideoDevice *_this, ثابت حرف *راستہ)
{
    VkExtensionProperties *extensions = تہی;
    Uint32 i, extension_گنتی = 0;
    bool hasSurfaceExtension = false;
    bool hasDisplayExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = تہی;

    اگر (_this->vulkan_config.loader_handle) {
        واپس SDL_سیٹ_Error("Vulkan already loaded");
    }

    // Load the Vulkan library
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

    SDL_strlcpy(_this->vulkan_config.loader_راستہ, راستہ,
                SDL_arraysize(_this->vulkan_config.loader_راستہ));

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
        } ورنہ اگر (SDL_strcmp(VK_KHR_DISPLAY_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasDisplayExtension = true;
        }
    }

    SDL_free(extensions);

    اگر (!hasSurfaceExtension) {
        SDL_سیٹ_Error("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        جاؤ fail;
    } ورنہ اگر (!hasDisplayExtension) {
        SDL_سیٹ_Error("Installed Vulkan doesn't implement the " VK_KHR_DISPLAY_EXTENSION_NAME " extension");
        جاؤ fail;
    }

    واپس true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = تہی;
    واپس false;
}

خالی KMSDRM_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    اگر (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = تہی;
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
حرف ثابت * ثابت *KMSDRM_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *گنتی)
{
    ساکن ثابت حرف *ثابت extensionsForKMSDRM[] = {
        VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_DISPLAY_EXTENSION_NAME
    };
    *گنتی = SDL_arraysize(extensionsForKMSDRM);
    واپس extensionsForKMSDRM;
}

ساکن صحیح SDLCALL display_منوال_comparator(ثابت خالی *a_opaque, ثابت خالی *b_opaque)
{
    ثابت Vk_Display_منوال_Properties_KHR *a = a_opaque;
    ثابت Vk_Display_منوال_Properties_KHR *b = b_opaque;

    اگر (a->parameters.refresh_شرح_2 > b->parameters.refresh_شرح_2)
        واپس -1;
    ورنہ اگر (a->parameters.refresh_شرح_2 < b->parameters.refresh_شرح_2)
        واپس 1;
    ورنہ
        واپس 0;
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
                                SDL_کھڑکی *کھڑکی,
                                VkInstance instance,
                                ثابت ساخت Vk_تخصیص_Callbacks *allocator,
                                VkSurfaceKHR *surface)
{
    VkPhysicalDevice gpu = تہی;
    uint32_t gpu_گنتی;
    uint32_t display_گنتی;
    uint32_t منوال_گنتی;
    uint32_t plane_گنتی_2;
    uint32_t _plane = UINT32_MAX;

    VkPhysicalDevice *physical_devices = تہی;
    VkPhysicalDeviceProperties *device_props = تہی;
    VkDisplayPropertiesKHR *display_props = تہی;
    Vk_Display_منوال_Properties_KHR *منوال_props = تہی;
    VkDisplayPlanePropertiesKHR *plane_props = تہی;
    VkDisplayPlaneCapabilitiesKHR plane_caps;

    Vk_Display_منوال_Create_Info_KHR display_منوال_create_info;
    VkDisplaySurfaceCreateInfoKHR display_plane_surface_create_info;

    VkExtent2D image_سائز_2;
    VkDisplayKHR display;
    Vk_Display_منوال_KHR display_منوال_2 = (Vk_Display_منوال_KHR)0;
    Vk_Display_منوال_Properties_KHR display_منوال_props = { 0 };
    Vk_Display_منوال_Parameters_KHR new_منوال_parameters = { { 0, 0 }, 0 };
    // Prefer a plane that supports per-pixel alpha.
    Vk_Display_Plane_Alpha_Flag_بٹ_KHR alpha_منوال_2 = VK_DISPLAY_PLANE_ALPHA_OPAQUE_ثنائی_ہندسہ_KHR;

    Vk_نتیجہ نتیجہ;
    bool ret = false;
    bool valid_gpu = false;
    bool منوال_ملا = false;
    bool plane_supports_display = false;

    // Get the display index from the display being used by the window.
    صحیح display_اشاریہ = SDL_Get_Display_اشاریہ(SDL_Get_Display_For_کھڑکی(کھڑکی));
    صحیح i, j;

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

    PFN_vk_Get_Display_منوال_Properties_KHR vk_Get_Display_منوال_Properties_KHR =
        (PFN_vk_Get_Display_منوال_Properties_KHR)vkGetInstanceProcAddr(
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

    PFN_vk_Create_Display_منوال_KHR vk_Create_Display_منوال_KHR =
        (PFN_vk_Create_Display_منوال_KHR)vkGetInstanceProcAddr(
            instance, "vkCreateDisplayModeKHR");

    اگر (!_this->vulkan_config.loader_handle) {
        SDL_سیٹ_Error("Vulkan is not loaded");
        جاؤ clean;
    }

    /*************************************/
    // Block for vulkan surface creation
    /*************************************/

    /****************************************************************/
    // If we got vkCreateDisplayPlaneSurfaceKHR() pointer, it means
    // that the VK_KHR_Display extension is active on the instance.
    // That's the central extension we need for x-less VK!
    /****************************************************************/
    اگر (!vkCreateDisplayPlaneSurfaceKHR) {
        SDL_سیٹ_Error(VK_KHR_DISPLAY_EXTENSION_NAME
                     " extension is not enabled in the Vulkan instance.");
        جاؤ clean;
    }

    /* A GPU (or physical_device, in vkcube terms) is a physical GPU.
       A machine with more than one video output doesn't need to have more than one GPU,
       like the Pi4 which has 1 GPU and 2 video outputs.
       Just in case, we test that the GPU we choose is Vulkan-capable.
       If there are new reports about VK init failures, hardcode
       gpu = physical_devices[0], instead of probing, and go with that.
    */

    // Get the physical device count.
    vkEnumeratePhysicalDevices(instance, &gpu_گنتی, تہی);

    اگر (gpu_گنتی == 0) {
        SDL_سیٹ_Error("Vulkan can't find physical devices (gpus).");
        جاؤ clean;
    }

    // Get the physical devices.
    physical_devices = SDL_malloc(حجم(VkPhysicalDevice) * gpu_گنتی);
    device_props = SDL_malloc(حجم(VkPhysicalDeviceProperties));
    vkEnumeratePhysicalDevices(instance, &gpu_گنتی, physical_devices);

    // Iterate on the physical devices.
    برائے (i = 0; i < gpu_گنتی; i++) {

        // Get the physical device properties.
        vkGetPhysicalDeviceProperties(
            physical_devices[i],
            device_props);

        // Is this device a real GPU that supports API version 1 at least?
        اگر (device_props->api_نسخہ >= 1 &&
            (device_props->deviceType == 1 || device_props->deviceType == 2)) {
            gpu = physical_devices[i];
            valid_gpu = true;
            توڑو;
        }
    }

    اگر (!valid_gpu) {
        SDL_سیٹ_Error("Vulkan can't find a valid physical device (gpu).");
        جاؤ clean;
    }

    /* A display is a video output. 1 GPU can have N displays.
       Vulkan only counts the connected displays.
       Get the display count of the GPU. */
    vkGetPhysicalDeviceDisplayPropertiesKHR(gpu, &display_گنتی, تہی);
    اگر (display_گنتی == 0) {
        SDL_سیٹ_Error("Vulkan can't find any displays.");
        جاؤ clean;
    }

    // Get the props of the displays of the physical device.
    display_props = (VkDisplayPropertiesKHR *)SDL_malloc(display_گنتی * حجم(*display_props));
    vkGetPhysicalDeviceDisplayPropertiesKHR(gpu,
                                            &display_گنتی,
                                            display_props);

    // Get the chosen display based on the display index.
    display = display_props[display_اشاریہ].display;

    // Get the list of the display videomodes.
    vk_Get_Display_منوال_Properties_KHR(gpu,
                                  display,
                                  &منوال_گنتی, تہی);

    اگر (منوال_گنتی == 0) {
        SDL_سیٹ_Error("Vulkan can't find any video modes for display %i (%s)", 0,
                     display_props[display_اشاریہ].displayName);
        جاؤ clean;
    }

    منوال_props = (Vk_Display_منوال_Properties_KHR *)SDL_malloc(منوال_گنتی * حجم(*منوال_props));
    vk_Get_Display_منوال_Properties_KHR(gpu,
                                  display,
                                  &منوال_گنتی, منوال_props);

    /* Sort the modes so that larger refresh rates come first. */
    SDL_qsort(منوال_props, منوال_گنتی, حجم(*منوال_props), display_منوال_comparator);

    /* Get a video mode equal to the window size among the predefined ones,
       if possible.
       REMEMBER: We have to get a small enough videomode for the window size,
       because videomode determines how big the scanout region is and we can't
       scanout a region bigger than the window (we would be reading past the
       buffer, and Vulkan would give us a confusing VK_ERROR_SURFACE_LOST_KHR). */
    برائے (i = 0; i < منوال_گنتی; i++) {
        اگر (منوال_props[i].parameters.visibleRegion.چوڑائی == کھڑکی->w &&
            منوال_props[i].parameters.visibleRegion.اونچائی == کھڑکی->h) {
            display_منوال_props = منوال_props[i];
            منوال_ملا = true;
            توڑو;
        }
    }

    اگر (منوال_ملا &&
        display_منوال_props.parameters.visibleRegion.چوڑائی > 0 &&
        display_منوال_props.parameters.visibleRegion.اونچائی > 0) {
        // Found a suitable mode among the predefined ones. Use that.
        display_منوال_2 = display_منوال_props.display_منوال;
    } ورنہ {

        /* Couldn't find a suitable mode among the predefined ones, so try to create our own.
           This won't work for some video chips atm (like Pi's VideoCore) so these are limited
           to supported resolutions. Don't try to use "closest" resolutions either, because
           those are often bigger than the window size, thus causing out-of-bunds scanout. */
        new_منوال_parameters.visibleRegion.چوڑائی = کھڑکی->w;
        new_منوال_parameters.visibleRegion.اونچائی = کھڑکی->h;
        /* SDL (and DRM, if we look at drmModeModeInfo vrefresh) uses plain integer Hz for
           display mode refresh rate, but Vulkan expects higher precision. */
        new_منوال_parameters.refresh_شرح_2 = (uint32_t)(کھڑکی->current_fullscreen_منوال.refresh_شرح * 1000);

        SDL_zero(display_منوال_create_info);
        display_منوال_create_info.sType = VK_STRUCTURE_TYPE_DISPLAY_منوال_CREATE_INFO_KHR;
        display_منوال_create_info.parameters = new_منوال_parameters;
        نتیجہ = vk_Create_Display_منوال_KHR(gpu,
                                        display,
                                        &display_منوال_create_info,
                                        تہی, &display_منوال_2);
        اگر (نتیجہ != VK_SUCCESS) {
            SDL_سیٹ_Error("Vulkan couldn't find a predefined mode for that window size and couldn't create a suitable mode.");
            جاؤ clean;
        }
    }

    // Just in case we get here without a display_mode.
    اگر (!display_منوال_2) {
        SDL_سیٹ_Error("Vulkan couldn't get a display mode.");
        جاؤ clean;
    }

    // Get the list of the physical device planes.
    vkGetPhysicalDeviceDisplayPlanePropertiesKHR(gpu, &plane_گنتی_2, تہی);
    اگر (plane_گنتی_2 == 0) {
        SDL_سیٹ_Error("Vulkan can't find any planes.");
        جاؤ clean;
    }
    plane_props = SDL_malloc(حجم(VkDisplayPlanePropertiesKHR) * plane_گنتی_2);
    vkGetPhysicalDeviceDisplayPlanePropertiesKHR(gpu, &plane_گنتی_2, plane_props);

    /* Iterate on the list of planes of the physical device
       to find a plane that matches these criteria:
       -It must be compatible with the chosen display + mode.
       -It isn't currently bound to another display.
       -It supports per-pixel alpha, if possible. */
    برائے (i = 0; i < plane_گنتی_2; i++) {

        uint32_t supported_displays_گنتی = 0;
        VkDisplayKHR *supported_displays;

        // See if the plane is compatible with the current display.
        vkGetDisplayPlaneSupportedDisplaysKHR(gpu, i, &supported_displays_گنتی, تہی);
        اگر (supported_displays_گنتی == 0) {
            // This plane doesn't support any displays. Continue to the next plane.
            جاری;
        }

        // Get the list of displays supported by this plane.
        supported_displays = (VkDisplayKHR *)SDL_malloc(حجم(VkDisplayKHR) * supported_displays_گنتی);
        vkGetDisplayPlaneSupportedDisplaysKHR(gpu, i,
                                              &supported_displays_گنتی, supported_displays);

        /* The plane must be bound to the chosen display, or not in use.
           If none of these is true, iterate to another plane. */
        اگر (!((plane_props[i].currentDisplay == display) || (plane_props[i].currentDisplay == VK_NULL_HANDLE))) {
            جاری;
        }

        /* Iterate the list of displays supported by this plane
           in order to find out if the chosen display is among them. */
        plane_supports_display = false;
        برائے (j = 0; j < supported_displays_گنتی; j++) {
            اگر (supported_displays[j] == display) {
                plane_supports_display = true;
                توڑو;
            }
        }

        // Free the list of displays supported by this plane.
        SDL_free(supported_displays);

        // If the display is not supported by this plane, iterate to the next plane.
        اگر (!plane_supports_display) {
            جاری;
        }

        // Want a plane that supports the alpha mode we have chosen.
        vkGetDisplayPlaneCapabilitiesKHR(gpu, display_منوال_2, i, &plane_caps);
        اگر (plane_caps.supportedAlpha == alpha_منوال_2) {
            // Yep, this plane is alright.
            _plane = i;
            توڑو;
        }
    }

    // If we couldn't find an appropriate plane, error out.
    اگر (_plane == UINT32_MAX) {
        SDL_سیٹ_Error("Vulkan couldn't find an appropriate plane.");
        جاؤ clean;
    }

    /********************************************/
    // Let's finally create the Vulkan surface!
    /********************************************/

    image_سائز_2.چوڑائی = کھڑکی->w;
    image_سائز_2.اونچائی = کھڑکی->h;

    SDL_zero(display_plane_surface_create_info);
    display_plane_surface_create_info.sType = VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR;
    display_plane_surface_create_info.display_منوال = display_منوال_2;
    display_plane_surface_create_info.plane_اشاریہ = _plane;
    display_plane_surface_create_info.imageExtent = image_سائز_2;
    display_plane_surface_create_info.transform = VK_SURFACE_TRANSFORM_شناختی_عنصر_ثنائی_ہندسہ_KHR;
    display_plane_surface_create_info.alpha_منوال = alpha_منوال_2;
    نتیجہ = vkCreateDisplayPlaneSurfaceKHR(instance,
                                            &display_plane_surface_create_info,
                                            allocator,
                                            surface);
    اگر (نتیجہ != VK_SUCCESS) {
        SDL_سیٹ_Error("vkCreateDisplayPlaneSurfaceKHR failed: %s",
                     SDL_Vulkan_Get_نتیجہ_String(نتیجہ));
        جاؤ clean;
    }

    ret = true;  // success!

clean:
    SDL_free(physical_devices);
    SDL_free(display_props);
    SDL_free(device_props);
    SDL_free(plane_props);
    SDL_free(منوال_props);

    واپس ret;
}

خالی KMSDRM_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                  VkInstance instance,
                                  VkSurfaceKHR surface,
                                  ثابت ساخت Vk_تخصیص_Callbacks *allocator)
{
    اگر (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_Destroy_Surface_اندرونی(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

#اگر_ختم
