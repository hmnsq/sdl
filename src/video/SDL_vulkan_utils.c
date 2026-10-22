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
#ضمن "SDL_internal.h"

#ضمن "SDL_vulkan_internal.h"

#جے_تعریف_شدہ SDL_VIDEO_VULKAN

ثابت حرف *SDL_Vulkan_Get_نتیجہ_String(Vk_نتیجہ نتیجہ)
{
    بدل ((صحيح)نتیجہ) {
    حالة VK_SUCCESS:
        أرجع "VK_SUCCESS";
    حالة VK_NOT_READY:
        أرجع "VK_NOT_READY";
    حالة VK_TIMEOUT:
        أرجع "VK_TIMEOUT";
    حالة VK_EVENT_سیٹ:
        أرجع "VK_EVENT_SET";
    حالة VK_EVENT_RESET:
        أرجع "VK_EVENT_RESET";
    حالة VK_INCOMPLETE:
        أرجع "VK_INCOMPLETE";
    حالة VK_ERROR_باہرلا_دا_HOST_حافظہ:
        أرجع "VK_ERROR_OUT_OF_HOST_MEMORY";
    حالة VK_ERROR_باہرلا_دا_DEVICE_حافظہ:
        أرجع "VK_ERROR_OUT_OF_DEVICE_MEMORY";
    حالة VK_ERROR_INITIALIZATION_FAILED:
        أرجع "VK_ERROR_INITIALIZATION_FAILED";
    حالة VK_ERROR_DEVICE_گواچا:
        أرجع "VK_ERROR_DEVICE_LOST";
    حالة VK_ERROR_حافظہ_MAP_FAILED:
        أرجع "VK_ERROR_MEMORY_MAP_FAILED";
    حالة VK_ERROR_LAYER_NOT_PRESENT:
        أرجع "VK_ERROR_LAYER_NOT_PRESENT";
    حالة VK_ERROR_EXTENSION_NOT_PRESENT:
        أرجع "VK_ERROR_EXTENSION_NOT_PRESENT";
    حالة VK_ERROR_FEATURE_NOT_PRESENT:
        أرجع "VK_ERROR_FEATURE_NOT_PRESENT";
    حالة VK_ERROR_INCOMPATIBLE_DRIVER:
        أرجع "VK_ERROR_INCOMPATIBLE_DRIVER";
    حالة VK_ERROR_TOO_MANY_OBJECTS:
        أرجع "VK_ERROR_TOO_MANY_OBJECTS";
    حالة VK_ERROR_FORMAT_NOT_SUPPORTED:
        أرجع "VK_ERROR_FORMAT_NOT_SUPPORTED";
    حالة VK_ERROR_FRAGMENTED_POOL:
        أرجع "VK_ERROR_FRAGMENTED_POOL";
    حالة VK_ERROR_UNKNOWN:
        أرجع "VK_ERROR_UNKNOWN";
    حالة VK_ERROR_باہرلا_دا_POOL_حافظہ:
        أرجع "VK_ERROR_OUT_OF_POOL_MEMORY";
    حالة VK_ERROR_INVALID_EXTERNAL_HANDLE:
        أرجع "VK_ERROR_INVALID_EXTERNAL_HANDLE";
    حالة VK_ERROR_FRAGMENTATION:
        أرجع "VK_ERROR_FRAGMENTATION";
    حالة VK_ERROR_INVALID_OPAQUE_CAPTURE_پتہ:
        أرجع "VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS";
    حالة VK_ERROR_SURFACE_گواچا_KHR:
        أرجع "VK_ERROR_SURFACE_LOST_KHR";
    حالة VK_ERROR_NATIVE_کھڑکی_وچ_USE_KHR:
        أرجع "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
    حالة VK_SUBOPTIMAL_KHR:
        أرجع "VK_SUBOPTIMAL_KHR";
    حالة VK_ERROR_باہرلا_دا_DATE_KHR:
        أرجع "VK_ERROR_OUT_OF_DATE_KHR";
    حالة VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
        أرجع "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
    حالة VK_ERROR_VALIDATION_FAILED_EXT:
        أرجع "VK_ERROR_VALIDATION_FAILED_EXT";
    حالة VK_ERROR_INVALID_SHADER_NV:
        أرجع "VK_ERROR_INVALID_SHADER_NV";
#إذا VK_سرخی_نسخہ >= 135 && VK_سرخی_نسخہ < 162
    حالة VK_ERROR_INCOMPATIBLE_نسخہ_KHR:
        أرجع "VK_ERROR_INCOMPATIBLE_VERSION_KHR";
#جے_انت
    حالة VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT:
        أرجع "VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT";
    حالة VK_ERROR_NOT_PERMITTED_EXT:
        أرجع "VK_ERROR_NOT_PERMITTED_EXT";
    حالة VK_ERROR_بھریا_SCREEN_EXCLUSIVE_منوال_گواچا_EXT:
        أرجع "VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT";
    حالة VK_THREAD_IDLE_KHR:
        أرجع "VK_THREAD_IDLE_KHR";
    حالة VK_THREAD_پورا_KHR:
        أرجع "VK_THREAD_DONE_KHR";
    حالة VK_OPERATION_DEFERRED_KHR:
        أرجع "VK_OPERATION_DEFERRED_KHR";
    حالة VK_OPERATION_NOT_DEFERRED_KHR:
        أرجع "VK_OPERATION_NOT_DEFERRED_KHR";
    حالة VK_PIPELINE_COMPILE_REQUIRED_EXT:
        أرجع "VK_PIPELINE_COMPILE_REQUIRED_EXT";
    افتراضي:
        اكسر;
    }
    إذا (نتیجہ < 0) {
        أرجع "VK_ERROR_<Unknown>";
    }
    أرجع "VK_<Unknown>";
}

VkExtensionProperties *SDL_Vulkan_CreateInstanceExtensionsList(
    PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties,
    Uint32 *extension_گنتی)
{
    Uint32 گنتی = 0;
    Vk_نتیجہ rc = vkEnumerateInstanceExtensionProperties(عدم, &گنتی, عدم);
    VkExtensionProperties *نتیجہ;

    إذا (rc == VK_ERROR_INCOMPATIBLE_DRIVER) {
        // Avoid the ERR_MAX_STRLEN limit by passing part of the message as a string argument.
        SDL_سیٹ_Error(
            "You probably don't have a working Vulkan driver installed. %s %s %s(%d)",
            "Getting Vulkan extensions failed:",
            "vkEnumerateInstanceExtensionProperties returned",
            SDL_Vulkan_Get_نتیجہ_String(rc),
            (صحيح)rc);
        أرجع عدم;
    } وإلا إذا (rc != VK_SUCCESS) {
        SDL_سیٹ_Error(
            "Getting Vulkan extensions failed: vkEnumerateInstanceExtensionProperties returned "
            "%s(%d)",
            SDL_Vulkan_Get_نتیجہ_String(rc),
            (صحيح)rc);
        أرجع عدم;
    }

    إذا (گنتی == 0) {
        نتیجہ = (VkExtensionProperties *)SDL_calloc(1, حجم(VkExtensionProperties)); // so we can return non-null
    } وإلا {
        نتیجہ = (VkExtensionProperties *)SDL_calloc(گنتی, حجم(VkExtensionProperties));
    }

    إذا (!نتیجہ) {
        أرجع عدم;
    }

    rc = vkEnumerateInstanceExtensionProperties(عدم, &گنتی, نتیجہ);
    إذا (rc != VK_SUCCESS) {
        SDL_سیٹ_Error(
            "Getting Vulkan extensions failed: vkEnumerateInstanceExtensionProperties returned "
            "%s(%d)",
            SDL_Vulkan_Get_نتیجہ_String(rc),
            (صحيح)rc);
        SDL_free(نتیجہ);
        أرجع عدم;
    }
    *extension_گنتی = گنتی;
    أرجع نتیجہ;
}

// Alpha modes, in order of preference
ساكن ثابت Vk_Display_Plane_Alpha_Flag_بٹ_KHR alphaModes[4] = {
    VK_DISPLAY_PLANE_ALPHA_OPAQUE_ثنائی_ہندسہ_KHR,
    VK_DISPLAY_PLANE_ALPHA_GLOBAL_ثنائی_ہندسہ_KHR,
    VK_DISPLAY_PLANE_ALPHA_فی_PIXEL_ثنائی_ہندسہ_KHR,
    VK_DISPLAY_PLANE_ALPHA_فی_PIXEL_PREMULTIPLIED_ثنائی_ہندسہ_KHR,
};

bool SDL_Vulkan_Display_CreateSurface(فراغ *vkGetInstanceProcAddr_,
                                      VkInstance instance,
                                      ثابت بنية Vk_ونڈ_Callbacks *allocator,
                                      VkSurfaceKHR *surface)
{
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)vkGetInstanceProcAddr_;
#تعریف_کرو VULKAN_INSTANCE_FUNCTION(name) \
    PFN_##name name = (PFN_##name)vkGetInstanceProcAddr((VkInstance)instance, #name)
    VULKAN_INSTANCE_FUNCTION(vkEnumeratePhysicalDevices);
    VULKAN_INSTANCE_FUNCTION(vkGetPhysicalDeviceDisplayPropertiesKHR);
    VULKAN_INSTANCE_FUNCTION(vk_Get_Display_منوال_Properties_KHR);
    VULKAN_INSTANCE_FUNCTION(vkGetPhysicalDeviceDisplayPlanePropertiesKHR);
    VULKAN_INSTANCE_FUNCTION(vkGetDisplayPlaneCapabilitiesKHR);
    VULKAN_INSTANCE_FUNCTION(vkGetDisplayPlaneSupportedDisplaysKHR);
    VULKAN_INSTANCE_FUNCTION(vkCreateDisplayPlaneSurfaceKHR);
#تعریف_رد VULKAN_INSTANCE_FUNCTION
    VkDisplaySurfaceCreateInfoKHR createInfo;
    Vk_نتیجہ rc;
    uint32_t physical_Device_گنتی = 0;
    VkPhysicalDevice *physicalDevices = عدم;
    uint32_t physical_Device_اشاریہ;
    ثابت حرف *chosenDisplayId;
    صحيح displayId = 0; // Counting from physical device 0, display 0

    إذا (!vkEnumeratePhysicalDevices ||
        !vkGetPhysicalDeviceDisplayPropertiesKHR ||
        !vk_Get_Display_منوال_Properties_KHR ||
        !vkGetPhysicalDeviceDisplayPlanePropertiesKHR ||
        !vkGetDisplayPlaneCapabilitiesKHR ||
        !vkGetDisplayPlaneSupportedDisplaysKHR ||
        !vkCreateDisplayPlaneSurfaceKHR) {
        SDL_سیٹ_Error(VK_KHR_DISPLAY_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        اذهب error;
    }
    chosenDisplayId = SDL_GetHint(SDL_HINT_VULKAN_DISPLAY);
    إذا (chosenDisplayId) {
        displayId = SDL_atoi(chosenDisplayId);
    }

    // Enumerate physical devices
    rc = vkEnumeratePhysicalDevices(instance, &physical_Device_گنتی, عدم);
    إذا (rc != VK_SUCCESS) {
        SDL_سیٹ_Error("Could not enumerate Vulkan physical devices");
        اذهب error;
    }

    إذا (physical_Device_گنتی == 0) {
        SDL_سیٹ_Error("No Vulkan physical devices");
        اذهب error;
    }

    physicalDevices = (VkPhysicalDevice *)SDL_malloc(حجم(VkPhysicalDevice) * physical_Device_گنتی);
    إذا (!physicalDevices) {
        اذهب error;
    }

    rc = vkEnumeratePhysicalDevices(instance, &physical_Device_گنتی, physicalDevices);
    إذا (rc != VK_SUCCESS) {
        SDL_سیٹ_Error("Error enumerating physical devices");
        اذهب error;
    }

    لكل (physical_Device_اشاریہ = 0; physical_Device_اشاریہ < physical_Device_گنتی; physical_Device_اشاریہ++) {
        VkPhysicalDevice physicalDevice = physicalDevices[physical_Device_اشاریہ];
        uint32_t display_Properties_گنتی = 0;
        VkDisplayPropertiesKHR *displayProperties = عدم;
        uint32_t display_منوال_Properties_گنتی = 0;
        Vk_Display_منوال_Properties_KHR *display_منوال_Properties = عدم;
        صحيح بہترین_میل_اشاریہ = -1;
        uint32_t refresh_شرح_2 = 0;
        uint32_t i;
        uint32_t display_Plane_Properties_گنتی = 0;
        صحيح plane_اشاریہ = -1;
        VkDisplayKHR display;
        VkDisplayPlanePropertiesKHR *displayPlaneProperties = عدم;
        VkExtent2D extent;
        VkDisplayPlaneCapabilitiesKHR planeCaps = { 0 };

        // Get information about the physical displays
        rc = vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &display_Properties_گنتی, عدم);
        إذا (rc != VK_SUCCESS || display_Properties_گنتی == 0) {
            // This device has no physical device display properties, move on to next.
            استمر;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display properties for device %u: %u",
                     physical_Device_اشاریہ, display_Properties_گنتی);

        إذا (displayId < 0 || (uint32_t)displayId >= display_Properties_گنتی) {
            // Display id specified was higher than number of available displays, move to next physical device.
            displayId -= display_Properties_گنتی;
            استمر;
        }

        displayProperties = (VkDisplayPropertiesKHR *)SDL_malloc(حجم(VkDisplayPropertiesKHR) * display_Properties_گنتی);
        إذا (!displayProperties) {
            اذهب error;
        }

        rc = vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &display_Properties_گنتی, displayProperties);
        إذا (rc != VK_SUCCESS || display_Properties_گنتی == 0) {
            SDL_free(displayProperties);
            SDL_سیٹ_Error("Error enumerating physical device displays");
            اذهب error;
        }

        display = displayProperties[displayId].display;
        extent = displayProperties[displayId].physicalResolution;
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Display: %s Native resolution: %ux%u",
                     displayProperties[displayId].displayName, extent.چوڑائی, extent.اچائی);

        SDL_free(displayProperties);
        displayProperties = عدم;

        // Get display mode properties for the chosen display
        rc = vk_Get_Display_منوال_Properties_KHR(physicalDevice, display, &display_منوال_Properties_گنتی, عدم);
        إذا (rc != VK_SUCCESS || display_منوال_Properties_گنتی == 0) {
            SDL_سیٹ_Error("Error enumerating display modes");
            اذهب error;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display modes: %u", display_منوال_Properties_گنتی);

        display_منوال_Properties = (Vk_Display_منوال_Properties_KHR *)SDL_malloc(حجم(Vk_Display_منوال_Properties_KHR) * display_منوال_Properties_گنتی);
        إذا (!display_منوال_Properties) {
            اذهب error;
        }

        rc = vk_Get_Display_منوال_Properties_KHR(physicalDevice, display, &display_منوال_Properties_گنتی, display_منوال_Properties);
        إذا (rc != VK_SUCCESS || display_منوال_Properties_گنتی == 0) {
            SDL_سیٹ_Error("Error enumerating display modes");
            SDL_free(display_منوال_Properties);
            اذهب error;
        }

        // Try to find a display mode that matches the native resolution
        لكل (i = 0; i < display_منوال_Properties_گنتی; ++i) {
            إذا (display_منوال_Properties[i].parameters.visibleRegion.چوڑائی == extent.چوڑائی &&
                display_منوال_Properties[i].parameters.visibleRegion.اچائی == extent.اچائی &&
                display_منوال_Properties[i].parameters.refresh_شرح_2 > refresh_شرح_2) {
                بہترین_میل_اشاریہ = i;
                refresh_شرح_2 = display_منوال_Properties[i].parameters.refresh_شرح_2;
            }
        }

        إذا (بہترین_میل_اشاریہ < 0) {
            SDL_سیٹ_Error("Found no matching display mode");
            SDL_free(display_منوال_Properties);
            اذهب error;
        }

        SDL_zero(createInfo);
        createInfo.display_منوال = display_منوال_Properties[بہترین_میل_اشاریہ].display_منوال;
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Matching mode %ux%u with refresh rate %u",
                     display_منوال_Properties[بہترین_میل_اشاریہ].parameters.visibleRegion.چوڑائی,
                     display_منوال_Properties[بہترین_میل_اشاریہ].parameters.visibleRegion.اچائی,
                     refresh_شرح_2);

        SDL_free(display_منوال_Properties);
        display_منوال_Properties = عدم;

        // Try to find a plane index that supports our display
        rc = vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &display_Plane_Properties_گنتی, عدم);
        إذا (rc != VK_SUCCESS || display_Plane_Properties_گنتی == 0) {
            SDL_سیٹ_Error("Error enumerating display planes");
            اذهب error;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display planes: %u", display_Plane_Properties_گنتی);

        displayPlaneProperties = (VkDisplayPlanePropertiesKHR *)SDL_malloc(حجم(VkDisplayPlanePropertiesKHR) * display_Plane_Properties_گنتی);
        إذا (!displayPlaneProperties) {
            اذهب error;
        }

        rc = vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &display_Plane_Properties_گنتی, displayPlaneProperties);
        إذا (rc != VK_SUCCESS || display_Plane_Properties_گنتی == 0) {
            SDL_سیٹ_Error("Error enumerating display plane properties");
            SDL_free(displayPlaneProperties);
            اذهب error;
        }

        لكل (i = 0; i < display_Plane_Properties_گنتی; ++i) {
            uint32_t plane_Supported_Displays_گنتی = 0;
            VkDisplayKHR *planeSupportedDisplays = عدم;
            uint32_t j;

            // Check if plane is attached to a display, if not, continue.
            إذا (displayPlaneProperties[i].currentDisplay == VK_NULL_HANDLE) {
                استمر;
            }

            // Check supported displays for this plane.
            rc = vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, i, &plane_Supported_Displays_گنتی, عدم);
            إذا (rc != VK_SUCCESS || plane_Supported_Displays_گنتی == 0) {
                استمر; // No supported displays, on to next plane.
            }

            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of supported displays for plane %u: %u", i, plane_Supported_Displays_گنتی);

            planeSupportedDisplays = (VkDisplayKHR *)SDL_malloc(حجم(VkDisplayKHR) * plane_Supported_Displays_گنتی);
            إذا (!planeSupportedDisplays) {
                SDL_free(displayPlaneProperties);
                اذهب error;
            }

            rc = vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, i, &plane_Supported_Displays_گنتی, planeSupportedDisplays);
            إذا (rc != VK_SUCCESS || plane_Supported_Displays_گنتی == 0) {
                SDL_سیٹ_Error("Error enumerating supported displays, or no supported displays");
                SDL_free(planeSupportedDisplays);
                SDL_free(displayPlaneProperties);
                اذهب error;
            }

            لكل (j = 0; j < plane_Supported_Displays_گنتی && planeSupportedDisplays[j] != display; ++j) {
            }

            SDL_free(planeSupportedDisplays);
            planeSupportedDisplays = عدم;

            إذا (j == plane_Supported_Displays_گنتی) {
                // This display is not supported for this plane, move on.
                استمر;
            }

            rc = vkGetDisplayPlaneCapabilitiesKHR(physicalDevice, createInfo.display_منوال, i, &planeCaps);
            إذا (rc != VK_SUCCESS) {
                SDL_سیٹ_Error("Error getting display plane capabilities");
                SDL_free(displayPlaneProperties);
                اذهب error;
            }

            // Check if plane fulfills extent requirements.
            إذا (extent.چوڑائی >= planeCaps.minDstExtent.چوڑائی && extent.اچائی >= planeCaps.minDstExtent.اچائی &&
                extent.چوڑائی <= planeCaps.maxDstExtent.چوڑائی && extent.اچائی <= planeCaps.maxDstExtent.اچائی) {
                // If it does, choose this plane.
                SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Choosing plane %u, minimum extent %ux%u maximum extent %ux%u", i,
                             planeCaps.minDstExtent.چوڑائی, planeCaps.minDstExtent.اچائی,
                             planeCaps.maxDstExtent.چوڑائی, planeCaps.maxDstExtent.اچائی);
                plane_اشاریہ = i;
                اكسر;
            }
        }

        إذا (plane_اشاریہ < 0) {
            SDL_سیٹ_Error("No plane supports the selected resolution");
            SDL_free(displayPlaneProperties);
            اذهب error;
        }

        createInfo.plane_اشاریہ = plane_اشاریہ;
        createInfo.plane_ڈھیر_اشاریہ = displayPlaneProperties[plane_اشاریہ].current_ڈھیر_اشاریہ;
        SDL_free(displayPlaneProperties);
        displayPlaneProperties = عدم;

        // Find a supported alpha mode. Not all planes support OPAQUE
        createInfo.alpha_منوال = VK_DISPLAY_PLANE_ALPHA_OPAQUE_ثنائی_ہندسہ_KHR;
        لكل (i = 0; i < SDL_arraysize(alphaModes); i++) {
            إذا (planeCaps.supportedAlpha & alphaModes[i]) {
                createInfo.alpha_منوال = alphaModes[i];
                اكسر;
            }
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Chose alpha mode 0x%x", createInfo.alpha_منوال);

        // Found a match, finally! Fill in extent, and break from loop
        createInfo.imageExtent = extent;
        اكسر;
    }

    SDL_free(physicalDevices);
    physicalDevices = عدم;

    إذا (physical_Device_اشاریہ == physical_Device_گنتی) {
        SDL_سیٹ_Error("No usable displays found or requested display out of range");
        اذهب error;
    }

    createInfo.sType = VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR;
    createInfo.transform = VK_SURFACE_TRANSFORM_پچھان_تت_ثنائی_ہندسہ_KHR;
    createInfo.globalAlpha = 1.0f;

    rc = vkCreateDisplayPlaneSurfaceKHR(instance, &createInfo, allocator, surface);
    إذا (rc != VK_SUCCESS) {
        SDL_سیٹ_Error("vkCreateDisplayPlaneSurfaceKHR failed: %s", SDL_Vulkan_Get_نتیجہ_String(rc));
        اذهب error;
    }
    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Created surface");
    أرجع true;

error:
    SDL_free(physicalDevices);
    أرجع false;
}

فراغ SDL_Vulkan_Destroy_Surface_اندرونی(فراغ *vkGetInstanceProcAddr_,
                                        VkInstance instance,
                                        VkSurfaceKHR surface,
                                        ثابت بنية Vk_ونڈ_Callbacks *allocator)
{
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)vkGetInstanceProcAddr_;
    PFN_vkDestroySurfaceKHR vkDestroySurfaceKHR =
        (PFN_vkDestroySurfaceKHR)vkGetInstanceProcAddr(
            instance,
            "vkDestroySurfaceKHR");

    إذا (vkDestroySurfaceKHR) {
        vkDestroySurfaceKHR(instance, surface, allocator);
    }
}

#جے_انت
